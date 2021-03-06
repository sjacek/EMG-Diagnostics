#ifndef LIBUECG_H
#define LIBUECG_H

#include <uecg_global.h>

#ifdef __cplusplus
extern "C"
{
#endif

void LIBUECG_EXPORT serial_functions_init();
void LIBUECG_EXPORT serial_main_init();
void LIBUECG_EXPORT open_device(const char* deviceName);
int LIBUECG_EXPORT serial_main_loop();

#ifdef __cplusplus
}
#endif

#endif // LIBUECG_H
