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

#ifndef PLUGIN_H
#define PLUGIN_H

#include "plugin_global.h"

#include <QtCore/QPluginLoader>
#include <QtCore/QLoggingCategory>

QT_BEGIN_NAMESPACE
class DataSeries;
QT_END_NAMESPACE

class INTERFACEPLUGINSHARED_EXPORT Plugin : public QObject
{
    Q_OBJECT
    Q_LOGGING_CATEGORY(cat, typeid(this).name())
public:
    explicit Plugin(QObject* parent) : QObject(parent), m_pPluginLoader(nullptr) {}

    virtual void init(int colCount) = 0;

    virtual ~Plugin() = default;

    QString getName() const {
        return getMetaDataValue("Name");
    }

    QString getVersion() const {
        return getMetaDataValue("Version");
    }

    QString getFileName() const {
        return getPluginLoader()->fileName();
    }

    friend class PluginSocket;

protected:
    void setPluginLoader(QPluginLoader* pluginLoader) {
        m_pPluginLoader = pluginLoader;
    }

    const QPluginLoader* getPluginLoader() const {
        return m_pPluginLoader;
    }

    QString getMetaDataValue(QString valueName) const {
        return getPluginLoader()->metaData().value("MetaData").toObject().value(valueName).toString();
    }

private:
    const QPluginLoader* m_pPluginLoader;

signals:
    void seriesCreated(QString name, DataSeries* series);
};

inline QDebug operator<< (QDebug debug, const Plugin& plugin)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "Plugin(" << plugin.getName() << ", " << plugin.getVersion() << ")";

    return debug;
}

QT_BEGIN_NAMESPACE
#define Plugin_iid "com.github.sjacek.EMG-Diagnostics.Plugin"
Q_DECLARE_INTERFACE(Plugin, Plugin_iid)
QT_END_NAMESPACE

#endif // PLUGIN_H
