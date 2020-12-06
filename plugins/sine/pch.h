#ifndef PCH_H
#define PCH_H

#include <QtConcurrent/QtConcurrent>
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QLoggingCategory>
#include <QtCore/QtMath>
#include <QtCore/QMutexLocker>
#include <QtCore/QtPlugin>
#include <QtCharts/QXYSeries>

QT_CHARTS_USE_NAMESPACE

#include <chrono>
using namespace std::chrono;

#include "interface_pch.h"

#endif // PCH_H
