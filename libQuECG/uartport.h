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

#ifndef UARTPORT_H
#define UARTPORT_H

#include "libquecg_global.h"
#include "uecg.h"

class LIBQUECG_EXPORT UartPort : public QextSerialPort
{
    Q_OBJECT
    Q_LOGGING_CATEGORY(cat, typeid(this).name())
public:
    UartPort(QObject* parent, const QString& device);

    void openDevice(const QString& device);

    void serial_main_loop();

private slots:
    void onReadyRead();

private:
    enum param_sends
    {
        param_batt_bpm = 0,
        param_sdnn,
        param_skin_res,
        param_lastRR,
        param_imu_acc,
        param_imu_steps,
        param_pnn_bins,
        param_end,
        param_emg_spectrum
    };

    // imported from original
    int device = 0;
    speed_t baudrate = B921600;

    struct timeval curTime, prevTime, zeroTime;
    int hex_mode_pos = 0;

    double real_time = 0;

    bool response_inited = false;
    uint8_t *response_buf;
    int response_pos = 0;
    int response_buf_len = 4096;

    uint8_t uart_prefix[2] = { 79, 213 };
    uint8_t uart_suffix[2] = { 76, 203 };

    uint32_t device_ids[8] = { 0, 0, 0, 0, 0, 0, 0, 0};

    float device_batt[8];
    float batt_voltage = 0;

    float bmi_ax;
    float bmi_ay;
    float bmi_az;
    int bmi_steps;

    void device_parse_response(uint8_t *buf, int len);
    float decode_acc(float acc);
    void serial_main_init();

private:
    QMap<quint32, Uecg*> m_mapUecg;
};

#endif // UARTPORT_H
