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

#ifndef POINTMODEL_H
#define POINTMODEL_H

class SeriesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SeriesModel() = default;
    explicit SeriesModel(QObject* parent);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

//    Qt::ItemFlags flags(const QModelIndex &index) const override;
//    bool removeRows(int row, int count, const QModelIndex &parent) override;

//    bool dropMimeData(const QMimeData *data, Qt::DropAction action,
//                      int row, int column, const QModelIndex &parent) override;
//    QMimeData *mimeData(const QModelIndexList &indexes) const override;
//    QStringList mimeTypes() const override;
    int rowCount(const QModelIndex &parent) const override;
//    Qt::DropActions supportedDropActions() const override;

//    void addPiece(const QPixmap &pixmap, const QPoint &location);
//    void addPieces(const QPixmap &pixmap);

    void addPoint(const QString& series, const QPointF& point);

private:
    QVector<QString> m_vSeries;
    QVector<QPointF> m_vPoints;

signals:

};

#endif // POINTMODEL_H
