#include <sys/stat.h>
#include <termios.h>

#include <errno.h>

#include <stdint.h>
// UI begin
//#include "widget_list.h"
// UI end

int write_to_device(uint8_t *buf, int len);

void serial_functions_init();
void open_device();
void close_device();

void serial_main_init();
int serial_main_loop();
void send_line();

void device_changed();

void toggle_auto_scale();
void toggle_integrate();

void send_data(uint8_t *data, int len);