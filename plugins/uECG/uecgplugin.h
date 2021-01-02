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

#ifndef UECGPLUGIN_H
#define UECGPLUGIN_H

#include "plugin.h"
#include "uecgenumerator.h"
class UecgThread;

class UecgPlugin : public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.github.sjacek.EMG-Diagnostics.Plugin" FILE "uecgplugin.json")
    Q_INTERFACES(Plugin)
    Q_LOGGING_CATEGORY(cat, typeid(this).name())

public:
    explicit UecgPlugin(QObject* parent = nullptr);

    void init(int cols) override;

    static inline int getSeriesCounter()
    {
        QMutexLocker ml(&m_seriesCounterMutex);
        return seriesCounter++;
    }

private:
    static inline int seriesCounter = 0;
    static inline QMutex m_seriesCounterMutex;

    int m_cols = -1;

    QList<DataSeries*> m_series;
    UecgEnumerator uecgEnumerator;
    QMap<QString, UecgThread*> threadMap;

    void initDevice();
    void initSeries();

private slots:
    void deviceDiscovered(const QextPortInfo& port);
    void deviceRemoved(const QextPortInfo& port);
};

#endif // UECGPLUGIN_H
