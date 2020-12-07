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

#include "seriesmodel.h"

SeriesModel::SeriesModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void SeriesModel::addPoint(const QString& series, const QPointF &point)
{
    int row = m_vPoints.size();

    beginInsertRows(QModelIndex(), row, row);
    m_vSeries.append(series);
    m_vPoints.append(point);
    endInsertRows();
}

QVariant SeriesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

//    if (role == Qt::DecorationRole)
//        return QIcon(points.value(index.row()), m_PieceSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
//    else if (role == Qt::UserRole)
//        return pixmaps.value(index.row());
//    else if (role == Qt::UserRole + 1)
//        return locations.value(index.row());
    switch (role) {
    case Qt::DecorationRole:
//        return QIcon(points.value(index.row()), m_PieceSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    case Qt::UserRole:
        return m_vSeries.value(index.row());
    case Qt::UserRole + 1:
        return m_vPoints.value(index.row());
    }

    return QVariant();
}

int SeriesModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_vPoints.count();
}
