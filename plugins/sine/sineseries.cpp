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

SineSeries::SineSeries(QObject* parent)
    : DataSeries(parent)
    , m_x(0.0)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();

    m_timerPaintSine = startTimer(1ms);
}

void SineSeries::init()
{
    qCDebug(cat) << "init(" << cols() << ")";
    // Remove previous data
    m_data.clear();
    m_data.reserve(cols());

}

void SineSeries::update(QAbstractSeries* series)
{
//    qCDebug(cat) << this << "index:" << m_index << "; series:" << series->name() << series << "; m_data.count:" << m_data.count();
//    if (m_data.empty() || cols() != m_data.count())
//        init();

//    Q_ASSERT(m_data.count());
    if (series) {
        QXYSeries* xySeries = static_cast<QXYSeries*>(series);

        // Use replace instead of clear + append, it's optimized for performance
        xySeries->replace(m_data);
    }
}

void SineSeries::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_timerPaintSine)
    {
        paintSine();
    }
}

void SineSeries::paintSine()
{
    qCDebug(cat) << m_x;

    for (QPointF& point : m_data)
        point.setX(point.x() + 1);

    qreal y = qSin(M_PI / 50 * m_x);
    m_data.append(QPointF(0, y));
    m_x++;
}
