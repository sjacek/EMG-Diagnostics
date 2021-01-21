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

#include "application.h"

#include "emgviewer.h"
#include "datasource.h"

Application::Application(int& argc, char** argv, int flags)
    : QApplication(argc, argv, flags)
{
    setOrganizationName("Grinnotech");
    setOrganizationDomain("sjacek.github.com");
    setApplicationName("EMG-Diagnostics");

//    oldMessageHandler = qInstallMessageHandler(messageOutput);

    // qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz t} %{if-debug}Debug%{endif}%{if-info}Info%{endif}%{if-warning}Warning%{endif}%{if-critical}Critical%{endif}%{if-fatal}Fatal%{endif}] %{file}:%{line} - %{message}");
//    qSetMessagePattern("[%{time yyyyMMdd h:mm:ss.zzz t} %{type}] %{category}::%{function}:%{line} - %{message}");

    // alternative to non-working declaration in the .pro file
    qmlRegisterSingletonInstance("com.github.sjacek.emgdiagnostics", 1, 0, "DataSource", &DataSource::instance());

    initializeRootLogger();
    logStartup();
}

//QtMessageHandler Application::oldMessageHandler;

void Application::init()
{
}

Application::~Application()
{
    logShutdown();
    shutdownRootLogger();
}

int Application::exec()
{
    EmgViewer viewer;
    viewer.show();

   return QApplication::exec();
}

//void Application::messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    QByteArray localMsg = msg.toLocal8Bit();
//    const char* file = context.file ? context.file : "";
//    const char* function = context.function ? context.function : "";
//    const char* category = context.category ? context.category : "";

//    oldMessageHandler(type, context, msg);
////    switch (type) {
////    case QtDebugMsg:
////        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
////        break;
////    case QtInfoMsg:
////        fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
////        break;
////    case QtWarningMsg:
////        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
////        break;
////    case QtCriticalMsg:
////        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
////        break;
////    case QtFatalMsg:
////        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
////        break;
////    }
//}

void Application::logStartup()
{
    auto logger = Log4Qt::Logger::rootLogger();

    logger->info(QStringLiteral("################################################################"));
    logger->info(QStringLiteral("#                          START                               #"));
    logger->info(QStringLiteral("################################################################"));
}

void Application::logShutdown()
{
    auto logger = Log4Qt::Logger::rootLogger();

    logger->info(QStringLiteral("################################################################"));
    logger->info(QStringLiteral("#                          STOP                                #"));
    logger->info(QStringLiteral("################################################################"));
}

void Application::setupRootLogger(const QString &introMessage)
{
    QString configFile = applicationFilePath() + QStringLiteral(".log4qt.properties");
    if (QFile::exists(configFile))
        Log4Qt::PropertyConfigurator::configureAndWatch(configFile);
    else
    {
        configFile = applicationDirPath() + QStringLiteral(".log4qt.properties");
        if (QFile::exists(configFile))
            Log4Qt::PropertyConfigurator::configureAndWatch(configFile);
    }
    if (!introMessage.isEmpty())
        Log4Qt::Logger::rootLogger()->info(introMessage);
}

void Application::shutDownRootLogger(const QString &extroMessage)
{
    auto logger = Log4Qt::Logger::rootLogger();

    if (!extroMessage.isEmpty())
        logger->info(extroMessage);
    logger->removeAllAppenders();
    logger->loggerRepository()->shutdown();
}

void Application::initializeRootLogger()
{
    setupRootLogger(QStringLiteral("Root logger is setup."));
}

void Application::shutdownRootLogger()
{
    shutDownRootLogger(QStringLiteral("Root logger was shutdown."));
}
