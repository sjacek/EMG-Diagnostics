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

import QtQuick 2.1
import QtCharts 2.15

ChartView {
    id: chartView
    animationOptions: ChartView.NoAnimation
    theme: ChartView.ChartThemeDark
    property bool openGL: true
    property bool openGLSupported: true
    onOpenGLChanged: {
        if (openGLSupported)
            for (var i = 0; i <= chartView.count; i++)
                dataSource.update(chartView.series(i));
    }
    Component.onCompleted: {
//        setupAllSeries("line")
    }

    Connections {
        target: dataSource

        function onSeriesCreated(name) {
            console.log("series ", name, " created")
            setupSeries(name, "line")
        }
    }

    ValueAxis {
        id: axisY1
        min: -1
        max: 4
    }

    ValueAxis {
        id: axisY2
        min: -10
        max: 5
    }

    ValueAxis {
        id: axisX
        min: 0
        max: 1024
    }

    Timer {
        id: refreshTimer
        interval: 1 / 60 * 1000 // 60 Hz
        running: true
        repeat: true
        onTriggered: {
            for (var i = 0; i < chartView.count; i++)
                dataSource.update(chartView.series(i));
        }
    }


    function setupAllSeries(type) {
        var seriesNames = []
        for (var i = 0; i < chartView.count; i++) {
            seriesNames.push(chartView.series(i).name)
        }

        for (var i = 0; i < seriesNames.length; i++) {
            setupSeries(seriesNames[i], type)
        }
    }

    function setupSeries(name, type) {
        console.log("setupSeries(", name, ",", type, ")")
        var series = chartView.series(name)
        if (series !== null)
            chartView.removeSeries(series)

        var seriesType;
        switch (type) {
        case "line":
            seriesType = ChartView.SeriesTypeLine;
            break;
        case "scatter":
            seriesType = ChartView.SeriesTypeScatter;
            break;
        case "spline":
            seriesType = ChartView.SeriesTypeSpline;
            break;
        }

        series = chartView.createSeries(seriesType, name, axisX, axisY1);

        series.useOpenGL = chartView.openGL
        if (type === "scatter") {
            series.markerSize = 2;
            series.borderColor = "transparent";
        }
    }

    function setAnimations(enabled) {
        chartView.animationOptions = enabled ? ChartView.SeriesAnimations : ChartView.NoAnimation;
    }

    function changeRefreshRate(rate) {
        refreshTimer.interval = 1 / Number(rate) * 1000;
    }
}
