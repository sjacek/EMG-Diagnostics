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

#include "pluginsocket.h"

#include "plugin.h"

PluginSocket::PluginSocket(QObject* parent)
    : QObject(parent)
{
    loadPlugins();
}

void PluginSocket::loadPlugins()
{
//    const QVector<QStaticPlugin> staticPlugins = QPluginLoader::staticPlugins();
//    for (const QStaticPlugin& staticPlugin : staticPlugins)
//    {
//        // TODO:
//    }

    qCDebug(cat) << "library Paths" << qApp->libraryPaths();

    QDir dir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)
    if (dir.dirName().toLower() == "debug" || dir.dirName().toLower() == "release")
        dir.cdUp();
#elif defined(Q_OS_MAC)
    if (dir.dirName() == "MacOS") {
        dir.cdUp();
        dir.cdUp();
        dir.cdUp();
    }
#endif
//    if (dir.dirName() == "bin")
//    dir.cdUp();
    qCDebug(cat) << "Base dir:" << dir;

    QDir pluginsDir = dir;
    if (pluginsDir.cd("lib/plugins")) {
        loadPluginsFromDir(pluginsDir);
    }

    pluginsDir = dir;
    if (pluginsDir.cd("plugins")) {
        loadPluginsFromDir(pluginsDir);

        for (const QFileInfo& fileinfo : pluginsDir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
            loadPluginsFromDir(fileinfo.absoluteFilePath());
        }
    }
}

void PluginSocket::loadPluginsFromDir(const QDir& dir)
{
    const QStringList entries = dir.entryList(QDir::Files);
    qCDebug(cat) << "Plugins dir:" << dir.absolutePath() << "; entries:"  << entries;

    for (QString fileName : entries)
    {
        QPluginLoader* pluginLoader = new QPluginLoader(dir.absoluteFilePath(fileName));
        if (QObject* object = pluginLoader->instance())
        {
            if (Plugin* plugin = qobject_cast<Plugin*>(object))
            {
                plugin->setPluginLoader(pluginLoader);
                qCInfo(cat) << "loaded plugin" << fileName << *plugin;
                m_Plugins.append(plugin);
            }
            else
            {
                qCWarning(cat) << "failed loading plugin" << fileName;
                pluginLoader->unload();
            }
        }
    }
}
