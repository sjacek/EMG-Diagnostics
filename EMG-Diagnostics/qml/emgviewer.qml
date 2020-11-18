/****************************************************************************
 **
 ** Copyright (C) 2020 Jacek Sztajnke.
 ** Contact: jacek.sztajnke@gl.com
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

import QtQuick 2.0

Item {
    id: emgviewer
    width: 600
    height: 400

    ScopeView {
        id: scopeView
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: controlPanel.left
        height: emgviewer.height

        onOpenGLSupportedChanged: {
            if (!openGLSupported) {
                controlPanel.openGLButton.enabled = false
                controlPanel.openGLButton.currentSelection = 0
            }
        }
    }

    ControlPanel {
        id: controlPanel
        anchors.top: parent.top
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.right: parent.right

        onSignalSourceChanged: {
            switch (source) {
            case "sin":
                dataSource.generateData(0, signalCount, sampleCount);
                break;
            case "linear":
                dataSource.generateData(1, signalCount, sampleCount);
                break;
            }

            scopeView.axisX().max = sampleCount;
        }
        onSeriesTypeChanged: scopeView.changeSeriesType(type);
        onRefreshRateChanged: scopeView.changeRefreshRate(rate);
        onAntialiasingEnabled: scopeView.antialiasing = enabled;
        onOpenGlChanged: {
            scopeView.openGL = enabled;
        }
    }

}
