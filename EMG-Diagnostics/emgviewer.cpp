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

#include "emgviewer.h"

#include <QtWidgets/QApplication>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtWidgets/QMessageBox>
#include <QtQml/QQmlContext>
#include <QtQml/QQmlEngine>
#include <QtCore/QPluginLoader>

#include "emginterface.h"

EmgViewer::EmgViewer()
{
    loadPlugins();
    {
//        QMessageBox::information((QWidget*)this, "Error", "Could not load the plugin");
//        lineEdit->setEnabled(false);
//        button->setEnabled(false);
    }

    initGUI();
}

void EmgViewer::loadPlugins()
{
    QDir dir(QCoreApplication::applicationDirPath());
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
    if (dir.dirName() == "bin")
        dir.cdUp();
    qDebug() << "Base dir:" << dir;

    QDir pluginsDir = dir;
    if (pluginsDir.cd("lib/plugins")) {
        loadPluginsFromDir(pluginsDir);
    }

    pluginsDir = dir;
    if (pluginsDir.cd("plugins")) {
        loadPluginsFromDir(pluginsDir);

        for (const QFileInfo &fileinfo : pluginsDir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
            loadPluginsFromDir(fileinfo.absoluteFilePath());
        }
    }
}

void EmgViewer::loadPluginsFromDir(const QDir& dir)
{
    qDebug() << "Plugins dir:" << dir;

    const QStringList entries = dir.entryList(QDir::Files);
    qDebug() << "entries:"  << entries;

    for (const QString &fileName : entries) {
        QPluginLoader pluginLoader(dir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin) {
            EmgInterface* emgInterface = qobject_cast<EmgInterface*>(plugin);
            if (emgInterface)
            {
                qInfo() << "loaded plugin" << fileName;
                m_ListPlugins.append(emgInterface);
            }
            else
            {
                qWarning() << "failed loading plugin" << fileName;
                pluginLoader.unload();
            }
        }
    }
}

void EmgViewer::initGUI()
{
    // TODO: remove in Release profile
    // The following are needed to make the app run without having to install the module
    // in desktop environments.
#ifdef Q_OS_WIN
    QString extraImportPath(QStringLiteral("%1/../../../../%2"));
#else
    QString extraImportPath(QStringLiteral("%1/../../../%2"));
#endif
    engine()->addImportPath(extraImportPath.arg(
                                QGuiApplication::applicationDirPath(),
                                QString::fromLatin1("qml")));
    QObject::connect(engine(), &QQmlEngine::quit, this, &QWindow::close);

    setTitle(QStringLiteral("EMG Diagnostics"));

    rootContext()->setContextProperty("dataSource", &m_dataSource);

    setSource(QUrl("qrc:/qml/emgviewer.qml"));
    setResizeMode(QQuickView::SizeRootObjectToView);
    setColor(QColor("#404040"));
}
