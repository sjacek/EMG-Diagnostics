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
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.15

ColumnLayout {
    property alias openGLButton: openGLButton
    property alias antialiasButton: antialiasButton
    spacing: 8
    Layout.fillHeight: true
    signal seriesTypeChanged(string type)
    signal refreshRateChanged(variant rate);
    signal signalSourceChanged(int sampleCount);
    signal antialiasingEnabled(bool enabled)
    signal openGlChanged(bool enabled)

    MultiButton {
        id: openGLButton
        text: qsTr("OpenGL: ")
        items: [qsTr("false"), qsTr("true")]
        currentSelection: 1
        onSelectionChanged: openGlChanged(currentSelection == 1);
    }

    MultiButton {
        text: qsTr("Graph: ")
        items: [qsTr("line"), qsTr("scatter"), qsTr("spline")]
        currentSelection: 0
        onSelectionChanged: seriesTypeChanged(items[currentSelection]);
    }

    MultiButton {
        id: sampleCountButton
        text: qsTr("Samples: ")
        items: ["6", "128", "1024", "10000"]
        currentSelection: 1
        onSelectionChanged: signalSourceChanged(selection);
    }

    MultiButton {
        text: qsTr("Refresh rate: ")
        items: ["1", "24", "60"]
        currentSelection: 2
        onSelectionChanged: refreshRateChanged(items[currentSelection]);
    }

    GridLayout {
        id: gridLayout
        width: 100
        height: 100
        Layout.fillHeight: false
        Layout.fillWidth: true
        rows: 2
        columns: 2

        Text {
            id: text1
            text: qsTr("Samples:")
            font.pixelSize: 12
            Layout.columnSpan: 2
        }

        Text {
            id: textSamples
            text: sliderSamples.value
            font.pixelSize: 12
            fontSizeMode: Text.FixedSize
        }

        Slider {
            id: sliderSamples
            height: 40
            stepSize: 5
            to: 10000
            value: 6
        }

        Text {
            id: text2
            text: qsTr("Refresh rate:")
            font.pixelSize: 12
            Layout.columnSpan: 2
        }

        Text {
            id: textRefreshRate
            text: sliderRefreshRate.value
            font.pixelSize: 12
            fontSizeMode: Text.FixedSize
        }

        Slider {
            id: sliderRefreshRate
            height: 40
            stepSize: 5
            to: 60
            value: 24
        }
    }

    MultiButton {
        id: antialiasButton
        text: qsTr("Antialias: ")
        items: [qsTr("OFF"), qsTr("ON")]
        enabled: true
        currentSelection: 0
        onSelectionChanged: antialiasingEnabled(currentSelection == 1);
    }

}
