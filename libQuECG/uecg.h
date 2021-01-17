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

#ifndef UECG_H
#define UECG_H

#include "ecgdata.h"

class Uecg : public QObject
{
    Q_OBJECT
    Q_LOGGING_CATEGORY(cat, typeid(this).name())
public:
//    explicit Uecg(QObject *parent = nullptr) : QObject(parent) {};

//    Uecg(Uecg& uecg);

    explicit Uecg(quint32 deviceId, QObject *parent = nullptr);

    ~Uecg();

//    Uecg& operator = (const Uecg& uecg);

    quint32 deviceId() const { return m_deviceId; }

//    void process(const QByteArray& data);
    void add(const EcgData& ecg);

private:
    quint32 m_deviceId;

    QDateTime m_lastSeen;

    QMap<QDateTime,EcgData> m_ecgLog;

signals:

};

#endif // UECG_H
