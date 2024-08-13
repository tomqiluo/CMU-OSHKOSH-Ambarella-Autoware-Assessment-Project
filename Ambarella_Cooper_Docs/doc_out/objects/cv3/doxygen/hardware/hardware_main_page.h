/*!
 * @file doc_hardware_main.h
 * @brief This file defines the Doxygen structure of hardware project
 * @version 1.0
 * @date 2022-08-05
 *
 * @copyright Copyright (c) 2024 Ambarella International LP.
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights. This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors. You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Ambarella International LP.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL AMBARELLA INTERNATIONAL LP OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; COMPUTER FAILURE OR MALFUNCTION; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


/*! @mainpage notitle
 * <h1>Ambarella Hardware Document</h1>
 * - - - -
 * <h2>Revision History</h2>
 *
 *
 * <table>
 * <caption id="hardware_rev_history"></caption>
 * <tr><th> Updated Date                <th align="left"> Modification
 * <tr><td> 20220805                    <td> Initial Version
 * <tr><td> 20220822                    <td> Added new page @ref hw_modules
 * <tr><td> 20230726                    <td> Added new page @ref page_cv72_gage
 * <tr><td> 20230817                    <td> Added new page @ref page_cv72_xiezhi
 * <tr><td> 20231010                    <td> Added new page @ref page_cv3_dk_mini
 * </table>
 *
 * - - - -

 * <h2>HW Modules</h2>
 *
 * The outline of @ref hw_modules is listed as follows:
 * - Section @ref hw_video_input 
 * - Section @ref hw_video_output 
 * - Section @ref hw_idsp_pipeline 
 * - Section @ref hw_video_codec 
 * - Section @ref hw_audio 
 * - Section @ref hw_system 
 * - Section @ref hw_interfaces 
 *
 * - - - -
 * <h2>CV5 Titanium</h2>
 *
 * This document provides users with details about hardware design of the CV5 Titanium board.
 *
 * The outline of @ref page_cv5_timn is listed as follows:
 * - Section @ref cv5_timn_evk_package 
 * - Section @ref cv5_timn_overview 
 * - Section @ref cv5_timn_setting_up 
 * - Section @ref cv5_timn_system_io_hardware_control 
 * - Section @ref cv5_timn_doc_license 
 *
 * - - - -
 * <h2>CV52 Co/Cr</h2>
 *
 * This document provides users with details about hardware design of the CV52 Co/Cr board.
 *
 * The outline of @ref page_cv52_cocr is listed as follows:
 * - Section @ref cv52_co_evk_package 
 * - Section @ref cv52_co_overview 
 * - Section @ref cv52_co_setting_up 
 * - Section @ref cv52_co_lpddr4x_system_io_hardware_control 
 * - Section @ref cv52_cr_lpddr5_system_io_hardware_control 
 * - Section @ref cv52_co_doc_license 
 *
 * - - - -
 * <h2>CV72 Ga/Ge</h2>
 *
 * This document provides users with details about hardware design of the CV72 Ga / Ge board.
 *
 * The outline of @ref page_cv72_gage is listed as follows:
 * - Section @ref cv72_ga_evk_package 
 * - Section @ref cv72_ga_overview 
 * - Section @ref cv72_ga_setting_up 
 * - Section @ref cv72_ga_system_io_hardware_control 
 * - Section @ref cv72_ga_design_notes 
 * - Section @ref cv72_ga_doc_license 
 *
 * - - - -
 * <h2>CV72 Xiezhi</h2>
 *
 * This document provides users with details about hardware design of the CV72 Xiezhi board.
 *
 * The outline of @ref page_cv72_xiezhi is listed as follows:
 * - Section @ref cv72_xiezhi_evk_package 
 * - Section @ref cv72_xiezhi_overview 
 * - Section @ref cv72_xiezhi_setting_up 
 * - Section @ref cv72_xiezhi_system_io_hardware_control 
 * - Section @ref cv72_xiezhi_design_notes 
 * - Section @ref cv72_xiezhi_doc_license 
 *
 * - - - -
 * <h2>CV3 Dk_mini</h2>
 *
 * This document provides users with details about hardware design of the CV3 Dk_mini board.
 *
 * The outline of @ref page_cv3_dk_mini is listed as follows:
 * - Section @ref cv3_dk_mini_evk_package 
 * - Section @ref cv3_dk_mini_overview 
 * - Section @ref cv3_hd_data_flow_overview 
 * - Section @ref cv3_dk_mini_setting_up 
 * - Section @ref cv3_dk_mini_system_io_hardware_control 
 * - Section @ref cv3_dk_mini_vin_map 
 * - Section @ref cv3_dk_mini_typical_case 
 * - Section @ref cv3_dk_mini_doc_license 
 *
 * - - - -

 *
 * <h2>License</h2>
 *
 *
 * Copyright (c) 2024 Ambarella International LP.
 *
 * This file and its contents ( "Software" ) are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights. This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors. You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Ambarella International LP.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF NON-INFRINGEMENT,
 * MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL AMBARELLA INTERNATIONAL LP OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; COMPUTER FAILURE OR MALFUNCTION; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.

 *
 */
