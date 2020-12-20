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

#include "renderthread.h"

RenderThread::RenderThread(QObject* parent)
    : QThread(parent)
    , uecgEnumerator(this)
{
    setObjectName(typeid(this).name());

    init();
}

void RenderThread::init()
{
    connect(&uecgEnumerator, &UecgEnumerator::deviceDiscovered, [=](const QextPortInfo& port)
    {
        qCDebug(cat) << "******************** deviceDiscovered:"
                     << "enumName" << port.enumName << "friendName" << port.friendName << "physName" << port.physName
                     << "portName" << port.portName << "productID" << port.productID << "vendorID" << port.vendorID;
    });

    connect(&uecgEnumerator, &UecgEnumerator::deviceRemoved, [=](const QextPortInfo& port)
    {
        qCDebug(cat) << "******************** deviceRemoved:"
                     << "enumName" << port.enumName << "friendName" << port.friendName << "physName" << port.physName
                     << "portName" << port.portName << "productID" << port.productID << "vendorID" << port.vendorID;
    });
}

RenderThread::~RenderThread()
{
    m_Abort = true;
}

void RenderThread::render()
{
    QMutexLocker locker(&m_Mutex);

    if (!isRunning()) {
        start(LowPriority);
    } else {
        m_Restart = true;
        m_Condition.wakeOne();
    }
}

void RenderThread::run()
{
    QMutexLocker locker(&m_Mutex);

    while (!m_Abort && !isInterruptionRequested() )
    {
        drawChart();
        msleep(10);
    }
}

void RenderThread::drawChart()
{
    qreal y = qSin(M_PI / 50 * m_X + 20);
    emit pointAdded(QPointF(m_X++, y));
}
