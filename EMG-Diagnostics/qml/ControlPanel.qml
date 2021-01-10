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
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15

ColumnLayout {
    spacing: 8
    Layout.fillHeight: true
    signal seriesTypeChanged(string type)
    signal refreshRateChanged(variant rate);
    signal antialiasingEnabled(bool enabled)
    signal openGlChanged(bool enabled)

    MultiButton {
        text: qsTr("Graph: ")
        items: [qsTr("line"), qsTr("scatter"), qsTr("spline")]
        currentSelection: 0
        onSelectionChanged: seriesTypeChanged(items[currentSelection]);
    }

    MultiButton {
        text: qsTr("Refresh rate: ")
        items: ["1", "24", "60"]
        currentSelection: 2
        onSelectionChanged: refreshRateChanged(items[currentSelection]);
    }

    GridLayout {
        width: 100
        height: 100
        Layout.fillHeight: false
        Layout.fillWidth: true
        rows: 2
        columns: 2

        Text {
            text: qsTr("OpenGL")
        }

        Switch {
            id: openGLSwitch
            checked: true
            onToggled: openGlChanged(checked)
        }

        Text {
            text: qsTr("Refresh rate")
            Layout.columnSpan: 2
        }

        Text {
            text: refreshRateSlider.value
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            fontSizeMode: Text.FixedSize
        }

        Slider {
            id: refreshRateSlider
            height: 40
            stepSize: 5
            to: 60
            value: 24
        }

        Text {
            text: qsTr("Antialias")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        }

        Switch {
            id: antialiasSwitch
            checked: false
            onToggled: antialiasingEnabled(checked)
        }
    }
}
