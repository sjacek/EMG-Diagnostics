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

#include "uecgplugin.h"

#include "sineseries.h"
#include "uecgseries.h"
//#include <uecg.h>
#include "uecgthread.h"

UecgPlugin::UecgPlugin(QObject* parent)
    : Plugin(parent)
    , uecgEnumerator(this)
{
}

void UecgPlugin::init(int cols)
{
    initDevice();
    m_cols = cols;
    initSeries();
}

void UecgPlugin::initDevice()
{
//    serial_functions_init();
//    serial_main_init();

    const QList<QextPortInfo>& ports = QextSerialEnumerator::getPorts();
    for(const QextPortInfo& port : ports)
    {
        if ((port.vendorID == UecgEnumerator::VENDOR_SILICON_LABS) &&
            (port.productID == UecgEnumerator::PRODUCT_CP210X_UART_BRIDGE))
        {
            deviceDiscovered(port);
        }
    }

    connect(&uecgEnumerator, &UecgEnumerator::deviceDiscovered, this, &UecgPlugin::deviceDiscovered);
    connect(&uecgEnumerator, &UecgEnumerator::deviceRemoved, this, &UecgPlugin::deviceRemoved);
}

void UecgPlugin::deviceDiscovered(const QextPortInfo& port)
{
    qCDebug(cat) << "******************** deviceDiscovered:"
                 << "enumName" << port.enumName << "friendName" << port.friendName << "physName" << port.physName
                 << "portName" << port.portName << "productID" << Qt::hex << port.productID << "vendorID" << Qt::hex << port.vendorID;
    threadMap.insert(port.portName, new UecgThread(this, port.portName));

//    {
//        const QString seriesName = QString("uecg%0").arg(getSeriesCounter());

//        UecgSeries* series = new UecgSeries(this, seriesName);
//        series->setCols(m_cols);
//        m_series.append(series);
//        emit seriesCreated(seriesName, series);
//    }
}

void UecgPlugin::deviceRemoved(const QextPortInfo& port)
{
    qCDebug(cat) << "******************** deviceRemoved:"
                 << "enumName" << port.enumName << "friendName" << port.friendName << "physName" << port.physName
                 << "portName" << port.portName << "productID" << port.productID << "vendorID" << port.vendorID;
    threadMap.remove(port.portName);
//    threadMap.insert(port.portName, new UecgThread(this, port.portName));
}

void UecgPlugin::initSeries()
{
    const QString seriesName = QString("uecg%0").arg(getSeriesCounter());

    SineSeries* series = new SineSeries(this, seriesName);
    series->setCols(m_cols);
    m_series.append(series);
    emit seriesCreated(seriesName, series);
}
