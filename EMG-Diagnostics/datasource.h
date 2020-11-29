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

#ifndef DATASOURCE_H
#define DATASOURCE_H

#include <QtCore/QObject>
#include <QtCharts/QAbstractSeries>
#include <QtCore/QLoggingCategory>

QT_BEGIN_NAMESPACE
class DataSeries;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class DataSource : public QObject
{
    Q_OBJECT
    Q_LOGGING_CATEGORY(cat, "DataSource")
public:
    explicit DataSource(QObject* parent);

    Q_INVOKABLE int count() { return m_dataSeries.count(); }

    Q_INVOKABLE void init(int colCount);
    Q_INVOKABLE void update(QAbstractSeries* series);

    Q_INVOKABLE QString getSeriesName(int n) const;

    Q_INVOKABLE DataSeries& series(QString name) const;

private slots:
    void onSeriesCreated(QString name, DataSeries* series);

private:
    QMap<QString, DataSeries*> m_dataSeries;

    void connectPlugins();

//    QList<DataSeries*> getSeries() const;
};

#endif // DATASOURCE_H
