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

#include "pch.h"
#include "emgviewer.h"

EmgViewer::EmgViewer(QWindow* parent)
    : QQuickView(parent)
{
    initGUI();

//    connect(this, &QQuickWindow::closing, [=](QQuickCloseEvent*) {
//        saveSettings();
//    });

    loadSettings();
}

void EmgViewer::initGUI()
{
    qCDebug(cat) << "initGUI()";

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
    connect(engine(), &QQmlEngine::quit, this, &QWindow::close);

    setTitle(QStringLiteral("EMG Diagnostics"));
    setSource(QUrl("qrc:/EmgViewerItem.qml"));
    setResizeMode(QQuickView::SizeRootObjectToView);
    setColor(QColor("#404040"));
}

void EmgViewer::loadSettings()
{
    QSettings settings;
    QVariant size = settings.value("emgviewer/size");
    if (!size.isNull()) resize(size.toSize());
}

void EmgViewer::saveSettings()
{
    QSettings settings;
    settings.setValue("emgviewer/size", size());
}
