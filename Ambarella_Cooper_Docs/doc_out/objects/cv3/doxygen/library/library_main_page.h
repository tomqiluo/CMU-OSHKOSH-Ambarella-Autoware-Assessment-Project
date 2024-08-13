/*!
 * @file doc_library_main.h
 * @brief This file defines the whole structure of ambarella sdk usage document.
 * @version 0.1
 * @date 2021-10-21
 *
 * @copyright Copyright (c) 2024 Ambarella International LP
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights. This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors. You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Ambarella International LP
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
 */

/*!
 * @mainpage notitle
 * <h1>AMBA Flexible Linux SDK Document</h1>
 * - - - -
 * <h2>Overview</h2>
 * The Ambarella CV5x devices are implemented as a system-on-chip (SoC) architecture. The
 * platform is driven by a Linux 64-bit OS that runs on the Arm® Dual-Cortex® A76 core of the CV5x
 * processor. With DSP firmware, driver and middlewares, as well as VP firmware, driver and
 * library, AMBA Flexible Linux SDK offers a powerful software platform for IPCam and automotive
 * application software.
 *
 *
 *
 * - - - -

 * <h2>Amba GStreamer Plugins Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x / CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_gstreamer_doc is listed as follows:
 * - Section @ref gstreamer_doc_history 
 * - Section @ref introduction 
 * - Section @ref gstreamer_user_guide 
 *
 * - - - -
 * <h2>ASF Library Document Overview</h2>
 * This document provides guidelines for the ASF Library on the Flexible Linux
 * SDK. It also gives an introduction to the various functions of the ASF Library, and describes how
 * to modify it to run separate applications.
 *
 * The outline of @ref page_lib_asf_doc is listed as follows:
 * - Section @ref asf_history 
 * - Section @ref asf_intro 
 * - Section @ref asf_record 
 * - Section @ref asf_repack 
 * - Section @ref asf_replay 
 * - Section @ref asf_example 
 * - Section @ref asf_qa 
 * - Section @ref asf_api 
 * - Section @ref asf_license 
 *
 * - - - -
 * <h2>Cavalry_Mem Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x / CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_cavalry_mem_doc is listed as follows:
 * - Section @ref cavalry_mem_history 
 * - Section @ref cavalry_mem_introduction 
 * - Section @ref cavalry_mem_example 
 * - Section @ref sec_cavalry_mem_api 
 * - Section @ref sec_cavalry_mem_lic 
 *
 * - - - -
 * <h2>Cavalry Opt Layers Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x / CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_cavalry_opt_layers_doc is listed as follows:
 * - Section @ref cavalry_opt_layers_history 
 * - Section @ref cavalry_opt_layers_introduction 
 * - Section @ref cavalry_opt_layers_example 
 * - Section @ref sec_cavalry_opt_layers_api 
 * - Section @ref sec_cavalry_opt_layers_lic 
 *
 * - - - -
 * <h2>CGPP Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x / CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_cgpp_doc is listed as follows:
 * - Section @ref cgpp_history 
 * - Section @ref cgpp_introduction 
 * - Section @ref cgpp_library_example_usage 
 * - Section @ref sec_cgpp_api 
 * - Section @ref sec_cgpp_lic 
 *
 * - - - -
 * <h2>Data Process Library Document Overview</h2>
 * This document provides guidelines for the Data Process(dproc) Library on the Flexible Linux
 * SDK.  It also gives an introduction to the various functions of the dproc Library, and describes how
 * to modify it to run separate applications.
 *
 * The outline of @ref page_lib_dproc_doc is listed as follows:
 * - Section @ref sec_dproc_history 
 * - Section @ref sec_dproc_overview 
 * - Section @ref sec_dproc_proc 
 * - Section @ref sec_dproc_test 
 * - Section @ref sec_dproc_api 
 * - Section @ref sec_dproc_lic 
 *
 * - - - -
 * <h2>Depth Sensing Framework Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_depth_fw_doc is listed as follows:
 * - Section @ref depth_history 
 * - Section @ref depth_framework 
 * - Section @ref dsf_components 
 * - Section @ref depth_tof 
 * - Section @ref sec_depth_disp_pc_on_ros 
 * - Section @ref sec_display_on_windows 
 * - Section @ref sec_demo_app 
 * - Section @ref sec_depth_performance 
 * - Section @ref sec_depth_api 
 * - Section @ref sec_depth_lic 
 *
 * - - - -
 * <h2>Dewarp Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_dewarp_doc is listed as follows:
 * - Section @ref dewarp_support 
 * - Section @ref dewarp_history 
 * - Section @ref dewarp_overview 
 * - Section @ref dewarp_correction_mode 
 * - Section @ref dewarp_lua_parser 
 * - Section @ref lens_sensor 
 * - Section @ref warp_system_config 
 * - Section @ref dewarp_development 
 * - Section @ref dewarp_qa 
 * - Section @ref dewarp_api_sec 
 * - Section @ref dewarp_license 
 *
 * - - - -
 * <h2>EazyAI Library Document Overview</h2>
 *
 * This document provides API information of the EazyAI library.
 *
 * The outline of @ref page_lib_eazyai_doc is listed as follows:
 * - Section @ref eazyai_history 
 * - Section @ref eazyai_introduction 
 * - Section @ref eazyai_cvflow 
 * - Section @ref eazyai_simulator 
 * - Section @ref eazyai_arm_postprocess 
 * - Section @ref eazyai_unit_test 
 * - Section @ref eazyai_api 
 * - Section @ref eazyai_license 
 *
 * Definition of functions can be found in @ref eazyai-api-details.
 *
 * Definition of macros, enumerations and structures can be found in @ref eazyai-api-helper.
 * - - - -
 * <h2>EIS Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_eis_doc is listed as follows:
 * - Section @ref eis_history 
 * - Section @ref eis_overview 
 * - Section @ref eis_implementation 
 * - Section @ref eis_design 
 * - Section @ref eis_development 
 * - Section @ref eis_tuning 
 * - Section @ref eis_qa 
 * - Section @ref sec_eis_api 
 * - Section @ref sec_eis_lic 
 *
 * - - - -
 * <h2>Image Flow Library Document Overview</h2>
 * This document provides the guideline of image flow library usage for the CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_img_flow_doc is listed as follows:
 * - Section @ref img_flow_history 
 * - Section @ref img_flow_introduction 
 * - Section @ref img_flow_usage 
 * - Section @ref img_flow_api 
 * - Section @ref img_flow_lic 
 *
 * - - - -

 * <h2>Image Library Document Overview</h2>
 * This document provides the guidline of image processing DSP group of APIs, which enables users
 * to configure various image tuning parameters in the CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_img_doc is listed as follows:
 * - Section @ref img_lib_history 
 * - Section @ref img_lib_introduction 
 * - Section @ref img_lib_pipeline 
 * - Section @ref aaa_statistics 
 * - Section @ref img_lib_api 
 * - Section @ref img_lib_lic 
 *
 * - - - -

 * <h2>NNCtrl Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x / CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_nnctrl_doc is listed as follows:
 * - Section @ref nnctrl_history 
 * - Section @ref nnctrl_introduction 
 * - Section @ref nnctrl_library_example_usage 
 * - Section @ref sec_nnctrl_api 
 * - Section @ref sec_nnctrl_lic 
 *
 * - - - -
 * <h2>Sensor Calibration Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_sensor_calib_doc is listed as follows:
 * - Section @ref sensor_calib_introduction 
 * - Section @ref sensor_calib_cfg 
 * - Section @ref sensor_calib_stitch 
 * - Section @ref sensor_calib_thermal_rgb 
 * - Section @ref sensor_calib_mono_rgb 
 * - Section @ref sensor_calib_tool_usage 
 * - Section @ref sensor_calib_api 
 * - Section @ref sensor_calib_lic 
 *
 * - - - -
 * <h2>SmartFB Library Document Overview</h2>
 * This document provides guidelines for the Smart Frame Buffer (SmartFB) Library on the Flexible Linux
 * SDK.  It also gives an introduction to the various functions of the SmartFB Library, and describes how
 * to modify it to run separate applications.
 *
 * The outline of @ref page_lib_smartfb_doc is listed as follows:
 * - Section @ref SmartFB_history 
 * - Section @ref SmartFB_overview 
 * - Section @ref SmartFB_proc 
 * - Section @ref sec_SmartFB_test 
 * - Section @ref sec_SmartFB_api 
 * - Section @ref sec_SmartFB_lic 
 *
 * - - - -
 * <h2>SmartRC V3 Library Document Overview</h2>
 * This document provides guidelines for the smart rate control (SmartRC) V3 Library on the Flexible Linux
 * SDK. It also gives an introduction to the various functions of the SRC V3 Library, and describes how
 * to modify it to run separate applications.
 *
 * The outline of @ref page_lib_src_v3 is listed as follows:
 * - Section @ref srcv3_history 
 * - Section @ref srcv3_overview 
 * - Section @ref srcv3_build 
 * - Section @ref srcv3_design 
 * - Section @ref srcv3_padj 
 * - Section @ref srcv3_lp 
 * - Section @ref srcv3_ut 
 * - Section @ref srcv3_exp 
 * - Section @ref srcv3_tuning 
 * - Section @ref srcv3_faq 
 * - Section @ref srcv3_api 
 * - Section @ref srcv3_lic 
 *
 * - - - -
 * <h2>Stitch Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_stitch_doc is listed as follows:
 * - Section @ref stitch_history 
 * - Section @ref stitch_introduction 
 * - Section @ref stitch_design 
 * - Section @ref sec_stitch_api 
 * - Section @ref sec_stitch_faq 
 * - Section @ref sec_stitch_lic 
 *
 * - - - -
 * <h2>VProc Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x / CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_vproc_doc is listed as follows:
 * - Section @ref vproc_history 
 * - Section @ref vproc_introduction 
 * - Section @ref vproc_library_example_usage 
 * - Section @ref sec_vproc 
 * - Section @ref sec_vproc_api 
 * - Section @ref sec_vproc_lic 
 *
 * - - - -
 * <h2>VFunc Library Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x / CV5x Flexible Linux SDK.
 *
 * The outline of @ref page_lib_vfunc_doc is listed as follows:
 * - Section @ref vfunc_history 
 * - Section @ref vfunc_introduction 
 * - Section @ref vfunc_library_example_usage 
 * - Section @ref sec_vfunc 
 * - Section @ref sec_vfunc_api 
 * - Section @ref sec_vfunc_lic 
 *
 * - - - -
 * <h2>VSS Library Document Overview</h2>
 * This document provides guidelines for the video sharing service (VSS) Library on the Flexible Linux
 * Software Development Kit (SDK). It also provides an introduction to the various functions of the VSS Library,
 * and describes how to modify configurations to run separate cases.
 *
 * The outline of @ref page_lib_vss_doc is listed as follows:
 * - Section @ref vss_history 
 * - Section @ref vss_intro 
 * - Section @ref vss_lib_api 
 * - Section @ref vss_usage 
 * - Section @ref dds_brief 
 * - Section @ref pm_license 
 *
 * - - - - * ### PrivacyMask Library Document Overview
 * This document provides guidelines for the privacy mask library on the Flexible Linux
 * SDK.
 *
 * The outline of @ref page_lib_pm_doc is listed as follows:
 * - Section @ref privacymask_history 
 * - Section @ref privacymask_intro 
 * - Section @ref pm_lib_process 
 * - Section @ref pm_example 
 * - Section @ref pm_lib_api 
 * - Section @ref pm_license 
 *
 * - - - -
 * <h2>VSRC Guard Library Document Overview</h2>
 * This document provides guidelines for the video source (VSRC) guard (VG) library on the Flexible Linux
 * Software Development Kit (SDK). It also provides an introduction to the various functions of the VG library,
 * and describes how to modify configurations to run separate cases.
 *
 * The outline of @ref page_lib_vg_doc is listed as follows:
 * - Section @ref vg_history 
 * - Section @ref vg_lib 
 * - Section @ref vg_service 
 * - Section @ref vg_license 
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
