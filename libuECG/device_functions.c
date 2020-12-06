#include "device_functions.h"
#include "serial_functions.h"
//#include "drawing.h"

#include "packet_parser.h"

#include <sys/time.h>
#include <fcntl.h>

#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

struct timeval bpm_time;

float bmi_ax;
float bmi_ay;
float bmi_az;
int bmi_steps;

float device_get_ax(){return bmi_ax;}
float device_get_ay(){return bmi_ay;}
float device_get_az(){return bmi_az;}
int device_get_steps(){return bmi_steps;}

uint8_t *response_buf;
int response_pos = 0;
int response_buf_len = 4096;
int response_inited = 0;

int device_count = 0;

#define IMU_CHANNELS 9

uint8_t uart_prefix[2] = {79, 213};
uint8_t uart_suffix[2] = {76, 203};

float batt_voltage = 0;

float avg_rssi = 0;

float device_get_rssi()
{
	return avg_rssi;
}

int records[300];
int record_ids[300];
int max_records = 25;
int cur_record = 0;
int record_size = 9;
int last_read_id = 0;
int last_read_record = 0;
int show_integrated = 0;

#define BPM_TIME_HIST 30
int bpm_times_s[BPM_TIME_HIST];
int bpm_times_us[BPM_TIME_HIST];

int bpm_chart_length = 300;
int bpm_data[300];

uint8_t last_pack_id = 0;
int err_conseq = 0;

int save_file = -1;
int save_file_RR = -1;
int save_file_skin = -1;
int save_turned_on = 0;

int ble_mode = 0;


void device_toggle_file_save()
{
	save_turned_on = !save_turned_on;
}

int device_get_mode()
{
	return ble_mode;
}
int stress_mode = 0;
int stress_hist_mode = 0;
void device_toggle_stress_mode()
{
	stress_mode = !stress_mode;
}
void device_toggle_stress_hist()
{
	stress_hist_mode = !stress_hist_mode;
}
int get_ble_draw_mode()
{
	return stress_mode;
}
int get_ble_draw_hist()
{
	return stress_hist_mode;
} 
void device_toggle_ble_mode()
{
	if(ble_mode == 0)
	{
		uint8_t cmd[8];
		cmd[0] = 177;
		cmd[1] = 103;
		cmd[2] = 41;		
		send_data(cmd, 3);
		ble_mode = 1;
	}
	else
	{
		uint8_t cmd[64];
		cmd[0] = 103;
		cmd[1] = 177;
		cmd[2] = 39;
		send_data(cmd, 3);
		ble_mode = 0;
	}
}

void device_close_log_file()
{
	if(save_file > 0)
	{
		close(save_file);
		close(save_file_RR);
		close(save_file_skin);
		save_file_skin = -1;
		save_file = -1;
		save_file_RR = -1;
	}
}

long last_bpm_out_sec = 0;
int last_skin_v = 0;

typedef struct sdevice_data
{
	uECG_data data;
	int *RR_hist;
	int rr_hist_len;
	int rr_hist_pos;
	float stress;
	float score;
	int on_screen_id;
	int last_saved_rr_id;
}sdevice_data;

uint32_t device_ids[8] = {0,0,0,0,0,0,0,0};
float device_batt[8];

void device_parse_response(uint8_t *buf, int len)
//we should be prepared that bytestream has missed bytes - it happens too often to ignore,
//so each data transfer from base starts with 2 fixed prefix bytes. But it could happen that
//actual data contents occasionally matches these prefix bytes, so we can't just treat them
//as guaranteed packet start - so we assume it _could_ be a packet start and try to parse
//the result, and see if it makes sense
{
	if(!response_inited) //init buffer for storing bytestream data ("response")
	{
		response_inited = 1;
		response_buf = (uint8_t*)malloc(response_buf_len);
		response_pos = 0;
	}
	//file saving requires rework - not intended for saving multiple streams
/*	if(save_turned_on && save_file < 0) //if saving into file was just requested - init it
	{
		time_t rawtime;
		time (&rawtime);
		struct tm * curTm = localtime(&rawtime);
		char repfname[256];
		sprintf(repfname, "ecg_log_y%d_m%d_d%d_h%d_m%d_s%d.txt", (2000+curTm->tm_year-100), curTm->tm_mon, curTm->tm_mday, curTm->tm_hour, curTm->tm_min, curTm->tm_sec);
		save_file = open(repfname, O_WRONLY | O_CREAT, 0b110110110);
		sprintf(repfname, "ecg_RR_y%d_m%d_d%d_h%d_m%d_s%d.txt", (2000+curTm->tm_year-100), curTm->tm_mon, curTm->tm_mday, curTm->tm_hour, curTm->tm_min, curTm->tm_sec);
		save_file_RR = open(repfname, O_WRONLY | O_CREAT, 0b110110110);
		sprintf(repfname, "ecg_skin_y%d_m%d_d%d_h%d_m%d_s%d.txt", (2000+curTm->tm_year-100), curTm->tm_mon, curTm->tm_mday, curTm->tm_hour, curTm->tm_min, curTm->tm_sec);
		save_file_skin = open(repfname, O_WRONLY | O_CREAT, 0b110110110);
	}
	if(!save_turned_on && save_file > 0) //if saving was just disabled - close files
	{
		close(save_file);
		close(save_file_skin);
		close(save_file_RR);
		save_file = -1;
		save_file_RR = -1;
		save_file_skin = -1;
	}*/
	//===========
	//buffer for storing bytestream, if buffer is overfilled - older half of the buffer is dropped
	if(len > response_buf_len/2) len = response_buf_len/2;
	if(response_pos > response_buf_len/2)
	{
		int dl = response_buf_len/4;
		memcpy(response_buf, response_buf+response_pos-dl, dl);
		response_pos = dl;
	}
	memcpy(response_buf+response_pos, buf, len);
	response_pos += len;
	//======= at this point, response_buf contains most recent unprocessed data, starting from 0
	int processed_pos = 0;
	for(int x = 0; x < response_pos-25; x++) //25 - always less than minimum valid packet length
	{
		if(response_buf[x] == uart_prefix[0] && response_buf[x+1] == uart_prefix[1])
		{//we detected possible start of the packet, trying to make sense of it
			uint8_t rssi_level = response_buf[x+2];
			uint8_t *pack = response_buf + x + 3;
			uint8_t message_length = pack[0];
			if(x + 3 + message_length >= response_pos) break;
			
			uint8_t check = 0;
			for(int x = 0; x < message_length-1; x++)
			{
				check += pack[x];
			}
			if(check != pack[message_length-1])
			{
				printf("check %d pack check %d length %d\n", check, pack[message_length-1], message_length);
				processed_pos = x + message_length - 1;
				continue;
			}
			
			printf("parsing...\n");
			uint8_t packet_id = pack[1];
			uint8_t ppos = 2;
			uint32_t unit_id = (pack[ppos++]<<24);
			unit_id |= (pack[ppos++]<<16);
			unit_id |= (pack[ppos++]<<8);
			unit_id |= pack[ppos++];
			printf("unit id %lu\n", unit_id);
			
			int unit_idx = -1;
			for(int n = 0; n < 8; n++)
			{
				if(unit_id == device_ids[n])
					unit_idx = n;
			}
			if(unit_idx < 0)
			{
				for(int n = 0; n < 8; n++)
				{
					if(device_ids[n] == 0)
					{
						device_ids[n] = unit_id;
						unit_idx = n;
						break;
					}
				}
			}
			
//			if(unit_idx < 0)
				printf("dev id %d unit idx %d\n", unit_id, unit_idx);

			uint8_t data_points = pack[ppos++];
			uint8_t emg_packet = 0;
			if(data_points > 200) //emg data are encoded as 200 + number of points
			{
				emg_packet = 1;
				data_points -= 200;
			}
			if(!emg_packet)
			{ 
				int param_id = pack[ppos++];
				
				uint8_t param_hb = pack[ppos++];
				uint8_t param_lb = pack[ppos++];
				uint8_t param_tb = pack[ppos++];
				
				uint8_t battery_level = 0;
				
				int data_pos = ppos;
									
				if(param_id == param_batt_bpm)
				{
					battery_level = param_hb;
					int bat_v = 0;
					bat_v = 2000 + battery_level * 10;
	//				if(battery_level > 147)
	//					bat_v = 4200;
	//				else bat_v = 4200 - (147 - battery_level)*35;
					if(unit_idx >= 0)
						device_batt[unit_idx] = bat_v;
	//				ble_devices[dev_by_mac].bpm = param_tb;
				}
				if(param_id == param_imu_steps)
				{
					bmi_steps = (param_hb<<8) | param_lb;
				}
				if(param_id == param_imu_acc)
				{					
					bmi_ax = decode_acc(param_hb);
					bmi_ay = decode_acc(param_lb);
					bmi_az = decode_acc(param_tb);
				}
				
				uint8_t check = 0;
				
				int16_t ch0[64];
				int16_t ch1[64];
				
				int pos = data_pos;

				for(int n = 0; n < data_points; n++)
				{
					int16_t val = (pack[pos]<<8) | (pack[pos+1]);
					ch0[n] = val; pos += 2;
					ch1[n] = ch0[x];

                    // UI begin
//					if(unit_idx >= 0)
//						sc_addV(ecg_charts + unit_idx, ch0[n]);
                    // UI end

					//saving logic requires rework
/*					if(save_file > 0 && save_turned_on)
					{
						char out_line[256];
						int len = 0;
						if(has_skin_data)
						{
							static int skin_dec_cnt = 0;
							skin_dec_cnt++;
							if(skin_dec_cnt >= 10)
							{
								len = sprintf(out_line, "%d\n", last_skin_v);
								write(save_file_skin, out_line, len);
								skin_dec_cnt = 0;
							}
						}
						struct timespec spec;
						clock_gettime(CLOCK_REALTIME, &spec);
						len = sprintf(out_line, "%d.%d %d\n", spec.tv_sec, (int)(spec.tv_nsec / 1.0e6), (int)ch0[n]);
						write(save_file, out_line, len);
					}*/
				}
			}
			else
			{
				int battery_level = pack[ppos++];
				int bat_v = 0;
				bat_v = 2000 + battery_level * 10;
				printf("bat_v %d idx %d\n", bat_v, unit_idx);
//				if(battery_level > 147)
//					bat_v = 4200;
//				else bat_v = 4200 - (147 - battery_level)*35;
				batt_voltage = bat_v;
				batt_voltage /= 1000.0;
				if(unit_idx >= 0)
					device_batt[unit_idx] = bat_v;
					
				int data_id = pack[ppos++];
				int emg_level = (pack[ppos]<<8) | pack[ppos+1]; ppos += 2;

				int spectr_scale = (pack[ppos]<<8) | pack[ppos+1]; ppos += 2;
				float sp_sc = 1.0+spectr_scale;
				float spvals[32];
				for(int n = 0; n < 8; n++)
				{
					spvals[n] = (pack[ppos+n*2])<<8 | (pack[ppos+n*2+1]);
					spvals[n] *= 100.0*sp_sc / 32760.0;
				}

                // UI begin
//              if(unit_idx >= 0)
//				{
//					spg_add_spectr(emg_charts+unit_idx, spvals);
//					sc_addV(ecg_charts + unit_idx, emg_level);
//				}
                // UI end
            }
			processed_pos = x + message_length - 1;
		}
	}
	memcpy(response_buf, response_buf+processed_pos, response_pos-processed_pos);
	response_pos -= processed_pos;
//	printf("processed to %d, new buf end %d\n", processed_pos, response_pos);
}

int device_get_skin_res()
{
	return 0;//(int)skin_d_avg;
}

int device_get_bpm()
{
	return 0;
}

int device_get_radio_quality()
{
	return 0;
}

float device_get_battery()
{
	return 0;
}

float device_get_batteryN(int N)
{
	return device_batt[N];
}

// UI begin
//void device_draw_time()
//{
//	draw_spectr = 0;
//}
//void device_draw_phase()
//{
//	draw_spectr = 1;
//}

//void device_draw_centered()
//{
	
//}
// UI end
