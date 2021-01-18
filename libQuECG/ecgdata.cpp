/****************************************************************************
 **
 ** Copyright (C) 2021 Jacek Sztajnke.
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

#include "ecgdata.h"

EcgData::EcgData(QObject *parent)
    : QObject(parent)
{
}

EcgData::EcgData(const EcgData& ecg)
    : QObject(ecg.parent())
    , data(ecg.data)
    , rssi(ecg.rssi)
    , packetId(ecg.packetId)
    , messageLength(ecg.messageLength)
    , deviceId(ecg.deviceId)
    , numberOfDataPoints(ecg.numberOfDataPoints)
    , batteryLevel(ecg.batteryLevel)
    , dataId(ecg.dataId)
    , muscleActivity(ecg.muscleActivity)
    , scale(ecg.scale)
    , ffts(ecg.ffts)
    , accX(ecg.accX)
    , accY(ecg.accY)
    , accZ(ecg.accZ)
    , gyroX(ecg.gyroX)
    , gyroY(ecg.gyroY)
    , gyroZ(ecg.gyroZ)
{
}

EcgData EcgData::fromByteArray(const QByteArray& data, QObject *parent)
{
    EcgData ret(parent);
    ret.data = data;

//    ret.rssi = data[2];
//    ret.packetId = data[3];
//    ret.messageLength = data[4];
//    ret.deviceId = (data[5] << 24) | (data[6] << 16) | (data[7] << 8) | data[8];
//    ret.numberOfDataPoints = data[9] + 200;
//    ret.batteryLevel = data[10] * 10 + 2000;
//    ret.dataId = data[11];
//    ret.muscleActivity = (data[12] << 8) | data[13];
//    ret.scale = (data[14] << 8) | data[15];

//    uint pos = 16;
//    for (uint i(0); i < ret.numberOfDataPoints; i++, pos += 2) {
//        quint32 fft = (data[pos] << 8) | data[pos + 1];
//        fft = ret.scale/32768 * fft;
//        ret.ffts.append(fft);
//    }

//    ret.accX = data[pos++];
//    ret.accY = data[pos++];
//    ret.accZ = data[pos++];
//    ret.gyroX = data[pos++];
//    ret.gyroY = data[pos++];
//    ret.gyroZ = data[pos++];

    return ret;
}

