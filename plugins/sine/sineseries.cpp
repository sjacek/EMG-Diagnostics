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

#include "sineseries.h"

Q_DECLARE_METATYPE(QAbstractSeries *)
Q_DECLARE_METATYPE(QAbstractAxis *)

SineSeries::SineSeries(QObject* parent, const QString& name)
    : DataSeries(parent, name)
    , m_Thread(this)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    connect(&m_Thread, &RenderThread::pointAdded, this, &SineSeries::pointAdded);
}

SineSeries::~SineSeries()
{
    m_Thread.quit();
    m_Thread.wait();
}

void SineSeries::init()
{
    m_Thread.render();
}

void SineSeries::update(QAbstractSeries* series)
{
    QList<QPointF> points = m_Thread.copyPoints();
    if (!points.count())
        init();
    else
    {
        if (series) {
            QXYSeries* xySeries = static_cast<QXYSeries*>(series);

            // Use replace instead of clear + append, it's optimized for performance
            xySeries->replace(points);
        }
    }
}
