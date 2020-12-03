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

#include "datasource.h"

#include "dataseries.h"
#include "plugin.h"
#include "pluginsocket.h"

QT_CHARTS_USE_NAMESPACE

Q_DECLARE_METATYPE(QAbstractSeries*)
Q_DECLARE_METATYPE(QAbstractAxis*)

DataSource::DataSource(QObject *parent)
    : QObject(parent)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    connectPlugins();
}

void DataSource::connectPlugins()
{
    for (Plugin* plugin : PluginSocket::instance().getPlugins()) {
        qCDebug(cat) << "connectPlugins" << *plugin;
        connect(plugin, &Plugin::seriesCreated, [=](const QString& name, DataSeries* series) {
            qCDebug(cat) << "received seriesCreated(" << name << ", " << series << ")";
            m_dataSeries[name] = series;
            emit seriesCreated(name);
        });
    }
}

void DataSource::init(int cols)
{
    m_dataSeries.clear();

    for (Plugin* plugin : PluginSocket::instance().getPlugins())
    {
        qCDebug(cat) << "init" << *plugin;
        plugin->init(cols);
    }
}

void DataSource::setCols(int cols)
{
    for (DataSeries* series : m_dataSeries.values())
    {
        series->setCols(cols);
    }
}

QString DataSource::getSeriesName(int n) const
{
    return m_dataSeries.keys().at(n);
}

void DataSource::update(QAbstractSeries* series)
{
    if (series)
    {
//        qCDebug(cat) << "DataSource::update 1: " << series->name();
        if (m_dataSeries.contains(series->name()))
        {
//            qCDebug(cat) << "DataSource::update 2";
            m_dataSeries[series->name()]->update(series);
        }
    }
}

DataSeries& DataSource::series(QString name) const
{
//    if (m_dataSeries.contains(name))
        return *m_dataSeries[name];

//    return new DataSeries();
}
