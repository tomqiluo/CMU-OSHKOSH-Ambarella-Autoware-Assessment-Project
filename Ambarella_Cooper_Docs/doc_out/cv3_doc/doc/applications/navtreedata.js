/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Applications", "index.html", [
    [ "Access Control Camera", "d2/d89/acc_ctrl_page.html", [
      [ "0. Revision History", "d2/d89/acc_ctrl_page.html#acc_ctrl_history", null ],
      [ "1. Overview", "d2/d89/acc_ctrl_page.html#acc_ctrl_ov", [
        [ "1.1 EVK Package", "d2/d89/acc_ctrl_page.html#acc_ctrl_evk_pkg", null ],
        [ "1.2 PC Requirement", "d2/d89/acc_ctrl_page.html#acc_ctrl_pc_req", null ],
        [ "1.3 Detection Range and Accuracy", "d2/d89/acc_ctrl_page.html#acc_ctrl_accuracy", null ],
        [ "1.4 Depth Generation", "d2/d89/acc_ctrl_page.html#acc_ctrl_depth_gen", null ],
        [ "1.5 Liveness Detection", "d2/d89/acc_ctrl_page.html#acc_ctrl_liveness_det", null ]
      ] ],
      [ "2. Demo Application", "d2/d89/acc_ctrl_page.html#acc_ctrl_demo", [
        [ "2.1 Build Image for Access Control EVK", "d2/d89/acc_ctrl_page.html#acc_ctrl_bulid_image", null ],
        [ "2.2 Initialize the System and Video Pipeline", "d2/d89/acc_ctrl_page.html#acc_ctrl_initialize", null ],
        [ "2.3 Run Demo Applications", "d2/d89/acc_ctrl_page.html#acc_ctrl_run_demo", [
          [ "2.3.1 Capture the Disparity, Depth, and Point Cloud Data", "d2/d89/acc_ctrl_page.html#acc_ctrl_depth_cap_demo", null ],
          [ "2.3.2 Run the FDFR Liveness Test Demo", "d2/d89/acc_ctrl_page.html#acc_ctrl_liveness_demo", null ]
        ] ]
      ] ],
      [ "3. Software Design", "d2/d89/acc_ctrl_page.html#acc_ctrl_soft_design", [
        [ "3.1 Structured-Light Control", "d2/d89/acc_ctrl_page.html#acc_ctrl_sl_control", null ],
        [ "3.2 RGB and IR Data Flow for Streaming", "d2/d89/acc_ctrl_page.html#acc_ctrl_data_flow", null ],
        [ "3.3 Advanced Features", "d2/d89/acc_ctrl_page.html#acc_ctrl_adv_feature", [
          [ "3.3.1 Dynamic Trigger of Structured Light", "d2/d89/acc_ctrl_page.html#acc_ctrl_dyn_trigger", null ],
          [ "3.3.2 AI Metering Mode", "d2/d89/acc_ctrl_page.html#acc_ctrl_ai_metering", null ],
          [ "3.3.3 Depth Generation Method Selection", "d2/d89/acc_ctrl_page.html#acc_ctrl_depth_option", null ]
        ] ],
        [ "3.4 IR / RGB Data Flow for the Algorithm Library", "d2/d89/acc_ctrl_page.html#acc_ctrl_algo_data_flow", null ],
        [ "3.5 Customize the Board Configuration File", "d2/d89/acc_ctrl_page.html#acc_ctrl_board_config", null ],
        [ "3.6 Demo Preparation ― Quick IPC on CV25M Janus", "d2/d89/acc_ctrl_page.html#acc_ctrl_quick_ipc_janus", [
          [ "3.6.1 Options", "d2/d89/acc_ctrl_page.html#acc_ctrl_quick_ipc_janus_options", null ],
          [ "3.6.2 Configurations", "d2/d89/acc_ctrl_page.html#acc_ctrl_quick_ipc_janus_config", null ]
        ] ],
        [ "3.7 Demo Preparation ― Quick IPC on CV22 Vision+", "d2/d89/acc_ctrl_page.html#acc_ctrl_quick_ipc_vision_plus", [
          [ "3.7.1 Options", "d2/d89/acc_ctrl_page.html#acc_ctrl_quick_ipc_vision_plus_options", null ],
          [ "3.7.2 Configurations", "d2/d89/acc_ctrl_page.html#acc_ctrl_quick_ipc_vision_plus_config", null ]
        ] ],
        [ "3.8 Software Design of test_sl_liveness_v2", "d2/d89/acc_ctrl_page.html#acc_ctrl_sl_liveness_demo", [
          [ "3.8.1 Data Flow of the test_sl_liveness_v2 Demo", "d2/d89/acc_ctrl_page.html#acc_ctrl_sl_liveness_data_flow", null ],
          [ "3.8.2 Customize the Demo", "d2/d89/acc_ctrl_page.html#acc_ctrl_sl_livenss_customize", null ]
        ] ]
      ] ],
      [ "4. Unit Test Usage", "d2/d89/acc_ctrl_page.html#acc_ctrl_unit_test", [
        [ "4.1 Configuring the Parameters", "d2/d89/acc_ctrl_page.html#acc_ctrl_unit_test_cfg", null ],
        [ "4.2 Unit_test: test_encode (New Parameters)", "d2/d89/acc_ctrl_page.html#acc_ctrl_test_encode", null ],
        [ "4.3 Unit_test: test_aaa_service (New Parameters)", "d2/d89/acc_ctrl_page.html#acc_ctrl_test_aaa_service", null ],
        [ "4.4 Unit_test: test_blade_runner", "d2/d89/acc_ctrl_page.html#acc_ctrl_test_blade_runner", [
          [ "4.4.1 Introduction to test_blade_runner", "d2/d89/acc_ctrl_page.html#acc_ctrl_tbr_intro", null ],
          [ "4.4.2 Capture the Disparity, Depth, and Point Cloud Data", "d2/d89/acc_ctrl_page.html#acc_ctrl_tbr_demo", null ]
        ] ],
        [ "4.5 Unit_test: test_sl_liveness_v2", "d2/d89/acc_ctrl_page.html#acc_ctrl_test_sl_liveness", [
          [ "4.5.1 Introduction of test_sl_liveness_v2", "d2/d89/acc_ctrl_page.html#acc_ctrl_tsll_v2_intro", null ],
          [ "4.5.2 Run the Face Detection, Face Recognition, and Liveness Test Demo", "d2/d89/acc_ctrl_page.html#acc_ctrl_tsll_v2_demo", null ]
        ] ],
        [ "4.6 Unit_test: test_calibrate_deviation", "d2/d89/acc_ctrl_page.html#acc_ctrl_test_calib_deviation", [
          [ "4.6.1 Introduction to test_calibrate_deviation", "d2/d89/acc_ctrl_page.html#acc_ctrl_tcd_intro", null ],
          [ "4.6.2 Run the Calibration Deviation to Check the Demo", "d2/d89/acc_ctrl_page.html#acc_ctrl_tcd_demo", null ]
        ] ],
        [ "4.7 Unit_test: test_structured_light", "d2/d89/acc_ctrl_page.html#acc_ctrl_test_sl", [
          [ "4.7.1 Introduction to test_structured_light", "d2/d89/acc_ctrl_page.html#acc_ctrl_tsl_intro", null ],
          [ "4.7.2 Run the Structured Light Test to Check the Demo", "d2/d89/acc_ctrl_page.html#acc_ctrl_tsl_demo", null ]
        ] ],
        [ "4.8 Unit_test: test_reference_yuv", "d2/d89/acc_ctrl_page.html#acc_ctrl_test_ref_yuv", [
          [ "4.8.1 Introduction to test_reference_yuv", "d2/d89/acc_ctrl_page.html#acc_ctrl_try_intro", null ],
          [ "4.8.2 Run the Reference YUV to Check the Demo", "d2/d89/acc_ctrl_page.html#acc_ctrl_try_demo", null ]
        ] ]
      ] ],
      [ "5. Lens Calibration", "d2/d89/acc_ctrl_page.html#acc_ctrl_len_calib", [
        [ "5.1 Mono Calibration Tool Version", "d2/d89/acc_ctrl_page.html#acc_ctrl_mon_calib_tool", null ],
        [ "5.2 PC Environment Setup", "d2/d89/acc_ctrl_page.html#acc_ctrl_calib_pkg_install", null ],
        [ "5.3 Calibration Board Preparation", "d2/d89/acc_ctrl_page.html#acc_ctrl_calib_board", null ],
        [ "5.4 Warp Table Generation", "d2/d89/acc_ctrl_page.html#acc_ctrl_gen_warp_table", null ]
      ] ],
      [ "6. Reference Capture", "d2/d89/acc_ctrl_page.html#acc_ctrl_ref_cap", null ],
      [ "7. FAQ", "d2/d89/acc_ctrl_page.html#acc_ctrl_faq", [
        [ "Question 1: How can frame rates of a structured light (SL) channel be increased?", "d2/d89/acc_ctrl_page.html#acc_ctrl_faq_q1", null ],
        [ "Question 2: What is dynamic mode? How is SL dynamic mode enabled?", "d2/d89/acc_ctrl_page.html#acc_ctrl_faq_q2", null ],
        [ "Question 3: What are users required to take care of in the mechanical design?", "d2/d89/acc_ctrl_page.html#acc_ctrl_faq_q3", null ],
        [ "Question 4: How is the on-board SDIO WiFi set up?", "d2/d89/acc_ctrl_page.html#acc_ctrl_faq_q4", null ]
      ] ],
      [ "8. License", "d2/d89/acc_ctrl_page.html#acc_ctrl_license", null ]
    ] ],
    [ "Beetle Demo", "d1/d4c/beetle_page.html", [
      [ "0. Revision History", "d1/d4c/beetle_page.html#beetle_history", null ],
      [ "1. Overview", "d1/d4c/beetle_page.html#beetle_ov", null ],
      [ "2. Demonstration Application", "d1/d4c/beetle_page.html#beetle_demo", [
        [ "2.1 Install and Set Up Lychee", "d1/d4c/beetle_page.html#build_install_lychee", null ],
        [ "2.2 Install Required Dependencies", "d1/d4c/beetle_page.html#build_install_dependecy", null ],
        [ "2.3 Compile the Beetle Demo", "d1/d4c/beetle_page.html#build_compile_demo", [
          [ "2.3.1 ROS2", "d1/d4c/beetle_page.html#build_demo_ros2", null ],
          [ "2.3.2 Apollo", "d1/d4c/beetle_page.html#build_demo_applo", null ]
        ] ],
        [ "2.4 Beetle Demo Presets", "d1/d4c/beetle_page.html#build_demo_presets", [
          [ "2.4.1 Set Up Dual-Video Output", "d1/d4c/beetle_page.html#preset_dual_vout", null ],
          [ "2.4.2 Prepare Required Test Files", "d1/d4c/beetle_page.html#preset_prepare_files", null ]
        ] ],
        [ "2.5 Run Beetle Demo", "d1/d4c/beetle_page.html#run_demo", [
          [ "2.5.1 Run Demo with ROS2", "d1/d4c/beetle_page.html#run_demo_ros2", null ],
          [ "2.5.2 Run Demo with Apollo", "d1/d4c/beetle_page.html#run_demo_appllo", null ]
        ] ]
      ] ],
      [ "3. Hardware Design", "d1/d4c/beetle_page.html#beetle_hw_design", null ],
      [ "4. Software Design", "d1/d4c/beetle_page.html#beetle_soft_design", null ],
      [ "5. Performance", "d1/d4c/beetle_page.html#beetle_performance", null ],
      [ "6. License", "d1/d4c/beetle_page.html#beetle_license", null ]
    ] ],
    [ "AIbox Demo", "da/d5a/aibox_page.html", [
      [ "0. Revision History", "da/d5a/aibox_page.html#aibox_history", null ],
      [ "1. Overview", "da/d5a/aibox_page.html#aibox_ov", null ],
      [ "2. Demo Application", "da/d5a/aibox_page.html#aibox_demo", [
        [ "2.1 Hardware Preparation", "da/d5a/aibox_page.html#build_hardware_prepare", null ],
        [ "2.2 Firmware Preparation", "da/d5a/aibox_page.html#build_firmware_prepare", [
          [ "2.2.1 Compile CV3 Firmware", "da/d5a/aibox_page.html#build_firmware_cv3", null ],
          [ "2.2.2 Compile RTSP-Boards Firmware", "da/d5a/aibox_page.html#build_firmware_rtsp", null ],
          [ "2.2.3 Burn Firmware", "da/d5a/aibox_page.html#burn_firmware", null ],
          [ "2.2.4 Set Up IP Address on RTSP Board", "da/d5a/aibox_page.html#set_ip_rtsp", null ],
          [ "2.3.1 Test RTSP", "da/d5a/aibox_page.html#test_rtsp", null ],
          [ "2.3.2 Test Filesrc", "da/d5a/aibox_page.html#test_filesrc", null ],
          [ "2.3.2 Test RTSP with Downscale and Machine Learning", "da/d5a/aibox_page.html#test_rtsp_ds_ml", null ],
          [ "2.3.2 Test Filesrc with Downscale and Machine Learning", "da/d5a/aibox_page.html#test_filesrc_ds_ml", null ]
        ] ]
      ] ],
      [ "3. Hardware Design", "da/d5a/aibox_page.html#aibox_hw_design", null ],
      [ "4. Software Design", "da/d5a/aibox_page.html#aibox_soft_design", null ],
      [ "5. Performance", "da/d5a/aibox_page.html#aibox_performance", null ],
      [ "6. License", "da/d5a/aibox_page.html#aibox_license", null ]
    ] ],
    [ "Multi-View Video Conference", "dc/dce/mvvc_page.html", [
      [ "0. Revision History", "dc/dce/mvvc_page.html#mvvc_history", null ],
      [ "1. Overview", "dc/dce/mvvc_page.html#mvvc_ov", null ],
      [ "2. Demo Application", "dc/dce/mvvc_page.html#mvvc_demo", null ],
      [ "3. Hardware Design", "dc/dce/mvvc_page.html#mvvc_hw_design", null ],
      [ "4. Software Design", "dc/dce/mvvc_page.html#mvvc_soft_design", null ],
      [ "5. Advanced Features", "dc/dce/mvvc_page.html#mvvc_advanced_features", [
        [ "5.1 Generate ME Image", "dc/dce/mvvc_page.html#mvvc_strategy_of_me_img", null ]
      ] ],
      [ "6. License", "dc/dce/mvvc_page.html#mvvc_license", null ]
    ] ],
    [ "Multi-VIN Binding Single Channel", "d5/dac/multi_vin_bind_page.html", [
      [ "0. Revision History", "d5/dac/multi_vin_bind_page.html#mvbc_history", null ],
      [ "1. Overview", "d5/dac/multi_vin_bind_page.html#mvbc_ov", null ],
      [ "2. Demo Application", "d5/dac/multi_vin_bind_page.html#mvbc_demo", null ],
      [ "3. Software Design", "d5/dac/multi_vin_bind_page.html#mvbc_hw_design", null ],
      [ "4. License", "d5/dac/multi_vin_bind_page.html#mvbc_license", null ]
    ] ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Variables", "functions_vars.html", "functions_vars" ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "Globals", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
        [ "Enumerator", "globals_eval.html", null ],
        [ "Macros", "globals_defs.html", null ]
      ] ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"annotated.html",
"d3/d33/structld__algo__op__s.html#ad183a184beda08d489376ad115d852d8",
"da/d33/params_8h.html#afba894e83a8a7c7ff02c23caf7cf7399",
"dd/d82/structvl__input__s.html#a8e7f2a01783571ba9cddb2ccd8ea37f7"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';