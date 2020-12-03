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

#ifndef FAKEPLUGIN_H
#define FAKEPLUGIN_H

#include "plugin.h"

class SinePlugin : public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.github.sjacek.EMG-Diagnostics.Plugin" FILE "fakeplugin.json")
    Q_INTERFACES(Plugin)
    Q_LOGGING_CATEGORY(cat, typeid(this).name())

public:
    explicit SinePlugin(QObject* parent = nullptr);

    void init(int cols) override;

private:
    QList<DataSeries*> m_series;
};

#endif // FAKEPLUGIN_H
