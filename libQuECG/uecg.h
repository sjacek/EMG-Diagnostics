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

#ifndef UECG_H
#define UECG_H

#include "libquecg_global.h"
#include "ecgdata.h"

class LIBQUECG_EXPORT Uecg
{
public:
    Uecg();

private:
//    var cur_ecg_data = [];
//    var last_frame_id = 0;

//    var cur_id = 0;
//    var prev_id = 0;

//    var ecg_data_queue = [];
//    var ecg_data_queue_init = 0;
//    var sample_length = 0;
//    var queue_length = 800;
//    var response_length = 1200;

    EcgData ecgData;

//    var history_pos = 0;
//    var max_history_len = 12*3600*update_rate;
//    var bpm_history = [];
//    var hrv_history = [];
//    var gsr_history = [];
//    var step_rate_history = [];
//    var temp_history = [];
//    var batt_history = [];
//    var acc_x_history = [];
//    var acc_y_history = [];
//    var acc_z_history = [];

//    var rr_history_pos = 0;
//    var rr_prev_id = -1;
//    var rr_cur_history = [];
//    var rr_prev_history = [];

//    var prev_steps = 0;
};

#endif // UECG_H
