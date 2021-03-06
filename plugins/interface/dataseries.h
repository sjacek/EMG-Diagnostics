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

#ifndef DATASERIES_H
#define DATASERIES_H

#include "plugin_global.h"

class INTERFACEPLUGINSHARED_EXPORT DataSeries : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int getCols READ getCols WRITE setCols NOTIFY colsChanged)
    Q_LOGGING_CATEGORY(cat, typeid(this).name())
public:
    explicit DataSeries(QObject* parent, const QString& name)
        : QObject(parent)
        , name(name)
        , cols(0)
    {}

    virtual void setCols(int cols) { this->cols = cols; }
    virtual int getCols() const { return cols; }

    virtual void setSeriesName(QString name) { this->name = name; }
    virtual QString getName() const { return name; }

    static int calculateAxisXMin()
    {
        QMutexLocker lock(&m_mutexStartTime);
        return m_startTime.msecsTo(QTime::currentTime()) / STROKE_X;
    }

    static const int STROKE_X = 10;

private:
    QString name;
    int cols;

    static inline QMutex m_mutexStartTime;
    static inline QTime m_startTime = QTime::currentTime();

signals:
    void colsChanged();
    void pointAdded(const QPointF& point);
};

inline QDebug operator<< (QDebug debug, const DataSeries& series)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << typeid(series).name() << "(" << series.getName() << ")";

    return debug;
}

Q_DECLARE_METATYPE(DataSeries*)

#endif // DATASERIES_H
