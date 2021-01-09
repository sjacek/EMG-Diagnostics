/****************************************************************************
 **
 ** Copyright (C) 2020 Jacek Sztajnke.
 ** Contact: jacek.sztajnke@gmail.com
 **
 ** This file is part of the EMG-Diagnostics project.
 **
 ** $QT_BEGIN_LICENSE:GPL$
 ** Commercial License Usage
 ** Licensees holding valid commercial Qt licenses may use this file in
 ** accordance with the commercial license agreement provided with the
 ** Software or, alternatively, in accordance with the terms contained in
 ** a written agreement between you and The Qt Company. For licensing terms
 ** and conditions see https://www.qt.io/terms-conditions. For further
 ** information use the contact form at https://www.qt.io/contact-us.
 **
 ** GNU General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU
 ** General Public License version 3 or (at your option) any later version
 ** approved by the KDE Free Qt Foundation. The licenses are as published by
 ** the Free Software Foundation and appearing in the file LICENSE.GPL3
 ** included in the packaging of this file. Please review the following
 ** information to ensure the GNU General Public License requirements will
 ** be met: https://www.gnu.org/licenses/gpl-3.0.html.
 **
 ** $QT_END_LICENSE$
 **
 ****************************************************************************/

#include "uartport.h"

UartPort::UartPort(QObject* parent, const QString& device)
    : QextSerialPort(device,
                     { BAUD921600 /*BAUD1152000*/, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10 },
                     EventDriven, parent)
{
//    serial_main_init();
//    openDevice(device);

    connect(this, &QextSerialPort::readyRead, this, &UartPort::onReadyRead);

    open(ReadWrite);
}

void UartPort::onReadyRead()
{
    const QByteArray& data = readAll();

    qCDebug(cat) << data.length() << ":" << data.toHex();

    if ((data[0] == (char)0x4f) && (data[1] == (char)0xd5)) {
        qCDebug(cat()) << "OK";

        quint32 device_id = (data[5] << 24) | (data[6] << 16) | (data[7] << 8) | data[8];

        if (!m_mapUecg.contains(device_id))
            m_mapUecg.insert(device_id, new Uecg(device_id));

        m_mapUecg[device_id]->process(data);
    }
    else
    {
        qCWarning(cat) << "Bad data";
    }
}

void UartPort::serial_main_init()
{
    gettimeofday(&prevTime, NULL);
    gettimeofday(&zeroTime, NULL);
}

void UartPort::openDevice(const QString& deviceName)
{
//	uint8_t *dev = gtk_entry_get_text(GTK_ENTRY(serial_entry_device));
    struct termios newtio;
    device = ::open(deviceName.toStdString().c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    bzero(&newtio, sizeof(newtio));

    newtio.c_cflag = baudrate | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = 0;//IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;//ICANON;

    newtio.c_cc[VTIME] = 1;
    newtio.c_cc[VMIN] = 1;

    tcflush(device, TCIOFLUSH);
    tcsetattr(device, TCSANOW, &newtio);
    // UI begin
//    char txt[128];
//    sprintf(txt, "device port open result: %d\n", device);
//    qCDebug(cat, "%s", txt);
//	add_text_to_main_serial_log(txt);
    // UI end
}


//decode 8-bit acceleration value: we need more precision around 0 and less at high g
float UartPort::decode_acc(float acc)
{
    float vv = acc - 128.0;
    int vm = vv;
    if (vm < 0) vm = -vm;
    float res = 0;
    if (vm > 100) //for values less than -12 and more than 12 m/s^2 precision is 0.5
    {
        res = 12.0 + (vm - 100) / 2.0;
    }
    else if (vm > 50) //for values from -12...-2 and 2...12 m/s^2 precision is 0.2
    {
        res = 2.0 + (vm - 50) / 5.0;
    }
    else
        res = vm / 25.0; //for values from -2 to 2 m/s^2 precision is 0.04
    if (vv < 0) res = -res;
    return res;
}

void UartPort::device_parse_response(uint8_t *buf, int len)
//we should be prepared that bytestream has missed bytes - it happens too often to ignore,
//so each data transfer from base starts with 2 fixed prefix bytes. But it could happen that
//actual data contents occasionally matches these prefix bytes, so we can't just treat them
//as guaranteed packet start - so we assume it _could_ be a packet start and try to parse
//the result, and see if it makes sense
{
    if(!response_inited) //init buffer for storing bytestream data ("response")
    {
        response_inited = true;
        response_buf = (uint8_t*)malloc(response_buf_len);
        response_pos = 0;
    }
    //file saving requires rework - not intended for saving multiple streams
    // TODO:
//	if(save_turned_on && save_file < 0) //if saving into file was just requested - init it
//	{
//		time_t rawtime;
////		time (&rawtime);
//		struct tm * curTm = localtime(&rawtime);
//		char repfname[256];
//		sprintf(repfname, "emg_log_y%d_m%d_d%d_h%d_m%d_s%d.txt", (2000+curTm->tm_year-100), curTm->tm_mon, curTm->tm_mday, curTm->tm_hour, curTm->tm_min, curTm->tm_sec);
//		save_file = open(repfname, O_WRONLY | O_CREAT, 0b110110110);
//	}

    // SPARE begin
//    time_t rawtime;
//    struct tm* curTm = localtime(&rawtime);
//    qCDebug(cat, "emg_log_y%d_m%d_d%d_h%d_m%d_s%d.txt",
//            2000 + curTm->tm_year - 100,
//            curTm->tm_mon, curTm->tm_mday, curTm->tm_hour, curTm->tm_min, curTm->tm_sec);
    // SPARE end
/*	if(!save_turned_on && save_file > 0) //if saving was just disabled - close files
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
        if(response_buf[x] == uart_prefix[0] && response_buf[x + 1] == uart_prefix[1])
        {
            //we detected possible start of the packet, trying to make sense of it
            uint8_t rssi_level = response_buf[x+2];
            uint8_t *pack = response_buf + x + 3;
            uint8_t message_length = pack[1];
            if(x + 3 + message_length >= response_pos)
                break;

            uint8_t check = 0;
            for(int x = 0; x < message_length-1; x++)
            {
                check += pack[x];
            }
            check = pack[message_length-1];
            if(check != pack[message_length-1])
            {
                qCDebug(cat, "check %d pack check %d length %d\n", check, pack[message_length-1], message_length);
//				processed_pos = x + message_length - 1;
//				continue;
            }

            qCDebug(cat) << "parsing...\n";
            uint8_t packet_id = pack[0];
            uint8_t ppos = 2;
            uint32_t unit_id = (pack[ppos++]<<24);
            unit_id |= (pack[ppos++]<<16);
            unit_id |= (pack[ppos++]<<8);
            unit_id |= pack[ppos++];
            qCDebug(cat) << "unit id" << unit_id;

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
                qCDebug(cat, "dev id %d unit idx %d\n", unit_id, unit_idx);

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
                    if (unit_idx >= 0)
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

//					if(unit_idx >= 0)
//						sc_addV(ecg_charts + unit_idx, ch0[n]);

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
                qCDebug(cat, "bat_v %d idx %d\n", bat_v, unit_idx);
//				if(battery_level > 147)
//					bat_v = 4200;
//				else bat_v = 4200 - (147 - battery_level)*35;
                batt_voltage = bat_v;
                batt_voltage /= 1000.0;
                if (unit_idx >= 0)
                    device_batt[unit_idx] = bat_v;

                int data_id = pack[ppos++];
                int emg_level = (pack[ppos]<<8) | pack[ppos+1]; ppos += 2;

                int spectr_scale = (pack[ppos]<<8) | pack[ppos+1]; ppos += 2;
                float sp_sc = 1.0+spectr_scale;
                float spvals[32];
                for (int n = 0; n < 8; n++)
                {
                    spvals[n] = (pack[ppos+n*2])<<8 | (pack[ppos+n*2+1]);
                    spvals[n] *= 1000.0*sp_sc / 32760.0;
                }
                // UI begin
//				if(unit_idx >= 0 && unit_idx < 8)
//				{
//					spg_add_spectr(emg_charts+unit_idx, spvals);
//					if(emg_level < 10000 && emg_level >= 0)
//						sc_addV(ecg_charts + unit_idx, emg_level);
//				}
                // UI end
                // SPARE begin
//				if(save_file > 0)
//				{
//					uint8_t linebuf[1024];
//					int linelen = sprintf(linebuf, "%lu %d %d %g %g %g %g %g %g %g %g\n", unit_id, emg_level, spectr_scale, spvals[0], spvals[1], spvals[2], spvals[3], spvals[4], spvals[5], spvals[6], spvals[7]);
//					write(save_file, linebuf, linelen);
//				}
                // SPARE end
                qCDebug(cat, "%lu %d %d %g %g %g %g %g %g %g %g\n",
                        unit_id, emg_level, spectr_scale, spvals[0], spvals[1], spvals[2], spvals[3], spvals[4], spvals[5], spvals[6], spvals[7]);
            }
            processed_pos = x + message_length - 1;
        }
    }
    memcpy(response_buf, response_buf+processed_pos, response_pos-processed_pos);
    response_pos -= processed_pos;
//	printf("processed to %d, new buf end %d\n", processed_pos, response_pos);
}

void UartPort::serial_main_loop()
{
    gettimeofday(&curTime, NULL);
    int dT = (curTime.tv_sec - prevTime.tv_sec) * 1000000 + (curTime.tv_usec - prevTime.tv_usec);
    real_time += (double)dT * 0.000001;

    prevTime = curTime;

    if(device > 0)
    {
        struct pollfd pfdS;
        pfdS.fd = device;
        pfdS.events = POLLIN | POLLPRI;
//		char tmbuf[64];
//		int len = sprintf(tmbuf, "%g", real_time);
//		gtk_entry_set_text(GTK_ENTRY(entry_line), tmbuf);

        int poll_ret = poll( &pfdS, 1, 1 );
        QString error;
        if (poll_ret == -1)
            error = QString(strerror(errno));

        if(poll_ret)
        {
//            qCDebug(cat) << "poll_ret:" << poll_ret;
            int lng = 0;
            uint8_t bbf[4096];
            lng = ::read(device, bbf, 4096);
            if(lng > 0)
            {
                qCDebug(cat) << lng;
                for (int i(0); i < lng; i++)
                {
                    qCDebug(cat) << i << ":" << Qt::hex << (int)bbf[i];
                }
                device_parse_response(bbf, lng);
            }
        }
    }
}

