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
    , m_index(-1)
{
    qRegisterMetaType<QAbstractSeries*>();
    qRegisterMetaType<QAbstractAxis*>();
}

void SineSeries::init()
{
    qCDebug(cat) << "init(" << cols() << ")";
    // Remove previous data
    m_data.clear();
    m_data.reserve(DATA_SIZE);

    // Append the new data depending on the type
    for (int i(0); i < DATA_SIZE; i++) {
        QList<QPointF> points;
        points.reserve(cols());
        for (int j(0); j < cols(); j++) {
            // data with sin + random component
            qreal y = qSin(M_PI / 50 * j) + 0.5 + QRandomGenerator::global()->generateDouble();
            qreal x = j;
            points.append(QPointF(x, y));
        }
        m_data.insert(i, points);
    }
}

void SineSeries::update(QAbstractSeries* series)
{
//    qCDebug(cat) << this << "index:" << m_index << "; series:" << series->name() << series << "; m_data.count:" << m_data.count();
    if (m_data.empty() || cols() != m_data.begin()->count())
        init();

    Q_ASSERT(m_data.count());
    if (series) {
        QXYSeries *xySeries = static_cast<QXYSeries *>(series);
        if (++m_index > DATA_SIZE - 1)
            m_index = 0;

        QList<QPointF> points = m_data.at(m_index);
        // Use replace instead of clear + append, it's optimized for performance
        xySeries->replace(points);
    }
}
