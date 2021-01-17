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

#ifndef ECGDATA_H
#define ECGDATA_H

class EcgData : public QObject
{
    Q_OBJECT
    Q_LOGGING_CATEGORY(cat, typeid(this).name())
public:
    EcgData(const EcgData& ecg);

    EcgData& operator =(const EcgData& ecg);

    static EcgData fromByteArray1(const QByteArray& data, QObject* parent = nullptr);
    static EcgData fromByteArray2(const QByteArray& data, QObject* parent = nullptr);

    const QByteArray& getData() const     { return data; }
    qint8 getRssi() const                 { return rssi; }
    qint8 getPacketId() const             { return packetId; }
    qint8 getMessageLength() const        { return messageLength; }
    qint32 getDeviceId() const            { return deviceId; }
//    uint getNumberOfDataPoints() const    { return dataPoints; }
    uint getBatteryLevel() const          { return batteryLevel; }
    uint getDataId() const                { return dataId; }
    uint getMuscleactivity() const        { return muscleActivity; }
    uint getScale() const                 { return scale; }
    const QList<quint32>& getFfts() const { return ffts; }
    quint8 getAccX() const                { return accX; }
    quint8 getAccY() const                { return accY; }
    quint8 getAccZ() const                { return accZ; }
    quint8 getGyroX() const               { return gyroX; }
    quint8 getGyroY() const               { return gyroY; }
    quint8 getGyroZ() const               { return gyroZ; }

private:
    explicit EcgData(QObject *parent = nullptr);

    QByteArray data;

    // RSSI level (might not work in this firmware version, but will be there later)
    quint8 rssi;

    // packet ID. Normally, each device sends consequent IDs, from 0 to 127 and back to 0 (so by checking difference in IDs you can see if there were missed data)
    quint8 packetId;

    // message length _starting from byte 3_ - so if message length is 20, the last data byte has number 23 starting from UART sync (that is because sync and RSSI are added by the base, while device sends bytes starting from packet ID)
    quint8 messageLength;

    // device ID
    quint32 deviceId;

    // number of data points + 200 (200 indicates that this is EMG data). So if byte 9 is equal to 220, there are 20 data points
//    uint dataPoints;

    // battery level, encoded. Battery voltage in mV = [byte 10] * 10 + 2000
    uint batteryLevel;

    // data ID. Is similar to packet ID but each time is increased by the actual amount of data points sent (can be used to precisely estimate the amount of lost data points)
    uint dataId;

    // 16-bit "muscle activity" level calculated on the device by analysing 8-bin FFT
    uint muscleActivity;

    // scale factor for following spectral values, each value should be transformed in the way: true value = received value * scale / 32768
    uint scale;

    // FFT values, there must be either 4, 8, 12 or other multiply of 4 number of values, where each consequent 4 values represent 4 spectral bins obtained by 8-bin FFT. Must be transformed using scale factor
    QList<quint32> ffts;

    // x,y,z accelerometer values and x,y,z gyro values (gyro is turned off in current firmware but will be on later)
    quint8 accX;
    quint8 accY;
    quint8 accZ;
    quint8 gyroX;
    quint8 gyroY;
    quint8 gyroZ;
};

inline QDebug operator<< (QDebug debug, const EcgData& ecg)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "data:" << ecg.getData() << Qt::endl;
    debug << "rssi:" << ecg.getRssi()
          << "packet_id" << ecg.getDeviceId()
          << "message length:" << ecg.getMessageLength()
          << "device id:" << ecg.getDeviceId()
//          << "number of data points:" << ecg.getNumberOfDataPoints()
          << "battery level:" << ecg.getBatteryLevel()
          << "data Id:" << ecg.getDataId()
          << "muscle activity:" << ecg.getMuscleactivity()
          << "scale:" << ecg.getScale()
          << "FFTS: TODO"
          << "accX:" << ecg.getAccX()
          << "accY:" << ecg.getAccY()
          << "accZ:" << ecg.getAccZ()
          << "gyroX:" << ecg.getGyroX()
          << "gyroY:" << ecg.getGyroY()
          << "gyroZ:" << ecg.getGyroZ()
    ;

    return debug;
}

#endif // ECGDATA_H
