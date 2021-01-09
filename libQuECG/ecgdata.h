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
    static EcgData fromByteArray(const QByteArray& data, QObject *parent = nullptr);

    const QByteArray& getData() const     { return data; }
    qint8 getRssi() const                 { return rssi; }
    qint8 getPacketId() const             { return packetId; }
    qint8 getMessageLength() const        { return messageLength; }
    qint32 getDeviceId() const            { return deviceId; }

signals:

private:
    explicit EcgData(QObject *parent = nullptr);

    EcgData(const EcgData& ecg);

    QByteArray data;
    qint8 rssi;
    qint8 packetId;
    qint8 messageLength;
    qint32 deviceId;

};

inline QDebug operator<< (QDebug debug, const EcgData& ecg)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "data:" << ecg.getData();
    debug.nospace() << "rssi:" << ecg.getRssi() << "packet_id" << ecg.getDeviceId() << "message length:" << ecg.getMessageLength() << "device id:" << ecg.getDeviceId();

    return debug;
}

#endif // ECGDATA_H
