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
  [ "Library", "index.html", [
    [ "Amba GStreamer Solution", "d5/d12/page_lib_gstreamer_doc.html", [
      [ "0. Revision History", "d5/d12/page_lib_gstreamer_doc.html#gstreamer_doc_history", null ],
      [ "1. Introduction", "d5/d12/page_lib_gstreamer_doc.html#introduction", [
        [ "1.1 GStreamer", "d5/d12/page_lib_gstreamer_doc.html#gstreamer", [
          [ "1.1.1 Library Revision History", "d5/d12/page_lib_gstreamer_doc.html#gstreamer_history", null ],
          [ "1.1.2 GStreamer Core Library", "d5/d12/page_lib_gstreamer_doc.html#gstreamer_core_library", null ],
          [ "1.1.3 GStreamer Community Library", "d5/d12/page_lib_gstreamer_doc.html#gstreamer_community_library", null ]
        ] ],
        [ "1.2 GStreamer Daemon", "d5/d12/page_lib_gstreamer_doc.html#gstreamer_daemon", [
          [ "1.2.1 Library Revision History", "d5/d12/page_lib_gstreamer_doc.html#gstd_history", null ],
          [ "1.2.2 Introduction", "d5/d12/page_lib_gstreamer_doc.html#gstd_introduction", null ]
        ] ],
        [ "1.3 NNStreamer", "d5/d12/page_lib_gstreamer_doc.html#nnstreamer", [
          [ "1.3.1 Library Revision History", "d5/d12/page_lib_gstreamer_doc.html#nns_history", null ],
          [ "1.3.2 Introduction", "d5/d12/page_lib_gstreamer_doc.html#nns_introduction", null ],
          [ "1.3.3 Ambarella CVflow® in NNStreamer", "d5/d12/page_lib_gstreamer_doc.html#amba_cvflow_in_nns", null ]
        ] ],
        [ "1.4 Amba GStreamer Plugins", "d5/d12/page_lib_gstreamer_doc.html#amba_gstreamer_plugins", [
          [ "1.4.1 Library Revision History", "d5/d12/page_lib_gstreamer_doc.html#amba_gst_plugin_history", null ],
          [ "1.4.2 List of Supported Elements", "d5/d12/page_lib_gstreamer_doc.html#amba_gst_plugin_element", null ],
          [ "1.4.3 amba_camsrc", "d5/d12/page_lib_gstreamer_doc.html#element_amba_camsrc", null ],
          [ "1.4.4 amba_hwvdec", "d5/d12/page_lib_gstreamer_doc.html#element_amba_hwvdec", null ],
          [ "1.4.5 amba_venccap", "d5/d12/page_lib_gstreamer_doc.html#element_amba_venccap", null ],
          [ "1.4.6 amba_vencdemux", "d5/d12/page_lib_gstreamer_doc.html#element_amba_vencdemux", null ],
          [ "1.4.7 amba_venc_overlay", "d5/d12/page_lib_gstreamer_doc.html#element_amba_venc_overlay", null ],
          [ "1.4.8 mlinference", "d5/d12/page_lib_gstreamer_doc.html#element_amba_mlinference", null ],
          [ "1.4.9 amba_heicfilesink", "d5/d12/page_lib_gstreamer_doc.html#element_amba_heicfilesink", null ],
          [ "1.4.10 amba_vsink", "d5/d12/page_lib_gstreamer_doc.html#element_amba_vsink", null ]
        ] ]
      ] ],
      [ "2. User Guide", "d5/d12/page_lib_gstreamer_doc.html#gstreamer_user_guide", [
        [ "2.1 Compilation", "d5/d12/page_lib_gstreamer_doc.html#compilation", null ],
        [ "2.2 Command Line Tools", "d5/d12/page_lib_gstreamer_doc.html#command_line_tools", [
          [ "2.2.1 gst-inspect-1.0", "d5/d12/page_lib_gstreamer_doc.html#gst_inspect_x", null ],
          [ "2.2.2 gst-launch-1.0", "d5/d12/page_lib_gstreamer_doc.html#gst_launch_x", null ],
          [ "2.2.3 GStreamer Daemon Commandline", "d5/d12/page_lib_gstreamer_doc.html#gstd_cmdline", null ]
        ] ],
        [ "2.3 Debugging", "d5/d12/page_lib_gstreamer_doc.html#debug", [
          [ "2.3.1 Debug with gst-launch-1.0", "d5/d12/page_lib_gstreamer_doc.html#gst_launch_x_debug", null ],
          [ "2.3.2 GstD Debug", "d5/d12/page_lib_gstreamer_doc.html#gstd_debug", null ]
        ] ],
        [ "2.4 Ambarella Test Cases", "d5/d12/page_lib_gstreamer_doc.html#amba_test_cases", [
          [ "2.4.1 Record Scenarios", "d5/d12/page_lib_gstreamer_doc.html#record_scenario", null ],
          [ "Example 1: Record One or Two Streams", "d5/d12/page_lib_gstreamer_doc.html#example_record_2_streams", null ],
          [ "Example 2: Record Six Streams", "d5/d12/page_lib_gstreamer_doc.html#example_record_6_streams", null ],
          [ "2.4.2 Playback Scenario", "d5/d12/page_lib_gstreamer_doc.html#playback_scenario", null ],
          [ "2.4.3 Machine Learning Scenarios", "d5/d12/page_lib_gstreamer_doc.html#machine_learning_scenario", null ],
          [ "Example 3: Machine Learning in the Amba Gst Plugin", "d5/d12/page_lib_gstreamer_doc.html#example_ml_in_amba_plugin", null ],
          [ "Example 4: Machine Learning in NNStreamer", "d5/d12/page_lib_gstreamer_doc.html#example_ml_in_nnstreamer", null ],
          [ "2.4.4 Set Up Encoding Parameters", "d5/d12/page_lib_gstreamer_doc.html#setup_encoding_params", null ],
          [ "2.4.5 Mimic Dual Video Input Scenarios", "d5/d12/page_lib_gstreamer_doc.html#mimic_dual_vin_scenarios", null ],
          [ "Example 5: Mimic Dual-VIN with 12 Streams", "d5/d12/page_lib_gstreamer_doc.html#example_mimic_dualvin_with_12s", null ],
          [ "Example 6: Mimic Dual-VIN with Eight Streams", "d5/d12/page_lib_gstreamer_doc.html#example_mimic_dualvin_with_8s", null ],
          [ "2.4.6 JPEG Scenarios", "d5/d12/page_lib_gstreamer_doc.html#jpeg_scenarios", null ],
          [ "2.4.7 RTSP Scenarios", "d5/d12/page_lib_gstreamer_doc.html#rtsp_scenarios", null ],
          [ "2.4.8 Debug Cases", "d5/d12/page_lib_gstreamer_doc.html#debug_cases", null ],
          [ "2.4.9 Use GStreamer in Lychee OS", "d5/d12/page_lib_gstreamer_doc.html#use_in_lychee", null ],
          [ "Example 7: Video Decode and Display", "d5/d12/page_lib_gstreamer_doc.html#example_file_playback_display", null ],
          [ "Example 8: Capture Live Camera and Display", "d5/d12/page_lib_gstreamer_doc.html#example_camera_capture", null ],
          [ "Example 9: NNStreamer Inference and Result Display", "d5/d12/page_lib_gstreamer_doc.html#example_fileinput_nn_inference_display", null ],
          [ "2.4.10 Known Issues", "d5/d12/page_lib_gstreamer_doc.html#known_issues", null ],
          [ "2.4.11 Notice", "d5/d12/page_lib_gstreamer_doc.html#notice", null ]
        ] ]
      ] ]
    ] ],
    [ "Ambarella Simulation Framework Library API", "d2/df5/page_lib_asf_doc.html", [
      [ "0. Revision History", "d2/df5/page_lib_asf_doc.html#asf_history", null ],
      [ "1. ASF Introduction", "d2/df5/page_lib_asf_doc.html#asf_intro", [
        [ "1.1 Overview", "d2/df5/page_lib_asf_doc.html#asf_intro_overview", null ],
        [ "1.2 Record, Repack, and Replay", "d2/df5/page_lib_asf_doc.html#asf_intro_3r", null ],
        [ "1.3 Data Structure", "d2/df5/page_lib_asf_doc.html#asf_intro_structure", null ]
      ] ],
      [ "2. Record", "d2/df5/page_lib_asf_doc.html#asf_record", [
        [ "2.1 Supported Record Data Types", "d2/df5/page_lib_asf_doc.html#asf_record_type", null ],
        [ "2.2 Record Plugins", "d2/df5/page_lib_asf_doc.html#asf_record_plugin", [
          [ "2.2.1 Customized Record Data Types", "d2/df5/page_lib_asf_doc.html#asf_record_plugin_type", null ],
          [ "2.2.2 Adding New Customized Plugins", "d2/df5/page_lib_asf_doc.html#asf_record_plugin_add_new", null ]
        ] ],
        [ "2.3 Record Configuration", "d2/df5/page_lib_asf_doc.html#asf_record_json", [
          [ "2.3.1 Record Mode and Event", "d2/df5/page_lib_asf_doc.html#asf_record_json_mode", null ],
          [ "2.3.2 Configuration", "d2/df5/page_lib_asf_doc.html#asf_record_json_config", null ],
          [ "2.3.3 Record in Trigger Mode", "d2/df5/page_lib_asf_doc.html#asf_record_trigger_mode", null ]
        ] ],
        [ "2.4 Compilation", "d2/df5/page_lib_asf_doc.html#asf_record_compile", null ]
      ] ],
      [ "3. Repack", "d2/df5/page_lib_asf_doc.html#asf_repack", [
        [ "3.1 Supported Repack Operations", "d2/df5/page_lib_asf_doc.html#asf_repack_opt", null ],
        [ "3.2 Repack Configuration", "d2/df5/page_lib_asf_doc.html#asf_repack_json", null ],
        [ "3.3 Compilation", "d2/df5/page_lib_asf_doc.html#asf_repack_compile", null ]
      ] ],
      [ "4. Replay", "d2/df5/page_lib_asf_doc.html#asf_replay", [
        [ "4.1 Replay Flow", "d2/df5/page_lib_asf_doc.html#asf_replay_flow", null ],
        [ "4.2 Supported Replay Cases", "d2/df5/page_lib_asf_doc.html#asf_replay_case", null ]
      ] ],
      [ "5. Application Examples", "d2/df5/page_lib_asf_doc.html#asf_example", [
        [ "5.1 EIS Simulation", "d2/df5/page_lib_asf_doc.html#asf_exmaple_eis", [
          [ "5.1.1 EIS Simulation Record", "d2/df5/page_lib_asf_doc.html#asf_example_eis_record", null ],
          [ "5.1.2 EIS Simulation Repack", "d2/df5/page_lib_asf_doc.html#asf_example_eis_repack", null ],
          [ "5.1.3 EIS Simulation Replay", "d2/df5/page_lib_asf_doc.html#asf_example_eis_replay", null ]
        ] ]
      ] ],
      [ "6. Troubleshooting", "d2/df5/page_lib_asf_doc.html#asf_qa", [
        [ "Question 1: What record mode should the customer use?", "d2/df5/page_lib_asf_doc.html#asf_q1", null ],
        [ "Question 2: How is an \"Invalid event id 1\" issue on the repack stage managed?", "d2/df5/page_lib_asf_doc.html#asf_q2", null ],
        [ "Question 3: In the record stage, what is \"shift_realtime_enable\" used for?", "d2/df5/page_lib_asf_doc.html#asf_q3", null ],
        [ "Question 4: How can users confirm that the record data has not been corrupted?", "d2/df5/page_lib_asf_doc.html#asf_q4", null ],
        [ "Question 5: How are record binaries split?", "d2/df5/page_lib_asf_doc.html#asf_q5", null ],
        [ "Question 6: What does the \"Invalid items found:\" message mean in the repack stage?", "d2/df5/page_lib_asf_doc.html#asf_q6", null ],
        [ "Question 7: Why does data loss occur in the record stage?", "d2/df5/page_lib_asf_doc.html#asf_q7", null ],
        [ "Question 8: Should the recording stream resolution and VIN resolution be the same in EIS cases?", "d2/df5/page_lib_asf_doc.html#asf_q8", null ],
        [ "Question 9: In EIS cases, why does the \"IAV_IOC_IMG_GET_STATISTICS\" error print in the console?", "d2/df5/page_lib_asf_doc.html#asf_q9", null ],
        [ "Question 10: In EIS cases, what does the \"Set RAW failed\" error message mean in the replay stage?", "d2/df5/page_lib_asf_doc.html#asf_q10", null ],
        [ "Qustion 11: Why is replay slow in EIS cases?", "d2/df5/page_lib_asf_doc.html#asf_q11", null ],
        [ "Qustion 12: In EIS cases, why is the number of frames replayed less than the recorded ones?", "d2/df5/page_lib_asf_doc.html#asf_q12", null ]
      ] ],
      [ "7. ASF Library API", "d2/df5/page_lib_asf_doc.html#asf_api", null ],
      [ "8. License", "d2/df5/page_lib_asf_doc.html#asf_license", null ]
    ] ],
    [ "Cavalry_Mem Library API", "d5/d42/page_lib_cavalry_mem_doc.html", [
      [ "0. Revision History", "d5/d42/page_lib_cavalry_mem_doc.html#cavalry_mem_history", null ],
      [ "1. Introduction", "d5/d42/page_lib_cavalry_mem_doc.html#cavalry_mem_introduction", null ],
      [ "2. Example Usage", "d5/d42/page_lib_cavalry_mem_doc.html#cavalry_mem_example", [
        [ "2.1 Debug Information", "d5/d42/page_lib_cavalry_mem_doc.html#cavalry_mem_usage", null ],
        [ "2.2 Allocate Memory", "d5/d42/page_lib_cavalry_mem_doc.html#cavalry_mem_alloc", null ],
        [ "2.3 Free Memory", "d5/d42/page_lib_cavalry_mem_doc.html#cavalry_mem_free", null ],
        [ "2.4 Sync Cached Memory", "d5/d42/page_lib_cavalry_mem_doc.html#cavalry_mem_sync_cache", null ]
      ] ],
      [ "3. Cavalry_Mem API", "d5/d42/page_lib_cavalry_mem_doc.html#sec_cavalry_mem_api", null ],
      [ "4. License", "d5/d42/page_lib_cavalry_mem_doc.html#sec_cavalry_mem_lic", null ]
    ] ],
    [ "Cavalry Opt Layers Library API", "dc/d21/page_lib_cavalry_opt_layers_doc.html", [
      [ "0. Revision History", "dc/d21/page_lib_cavalry_opt_layers_doc.html#cavalry_opt_layers_history", null ],
      [ "1. Introduction", "dc/d21/page_lib_cavalry_opt_layers_doc.html#cavalry_opt_layers_introduction", null ],
      [ "2. Example Usage", "dc/d21/page_lib_cavalry_opt_layers_doc.html#cavalry_opt_layers_example", [
        [ "2.1 test_pvanet", "dc/d21/page_lib_cavalry_opt_layers_doc.html#cavalry_opt_layers_test_pvanet", null ],
        [ "2.2 test_roi_align_arm", "dc/d21/page_lib_cavalry_opt_layers_doc.html#cavalry_opt_layers_test_roi_align_arm", null ],
        [ "2.3 test_psroipooling", "dc/d21/page_lib_cavalry_opt_layers_doc.html#cavalry_opt_layers_test_psroipooling", null ],
        [ "2.3 test_float_dtcvt", "dc/d21/page_lib_cavalry_opt_layers_doc.html#cavalry_opt_layers_test_float_dtcvt", null ]
      ] ],
      [ "3. Cavalry Opt Layers API", "dc/d21/page_lib_cavalry_opt_layers_doc.html#sec_cavalry_opt_layers_api", null ],
      [ "4. License", "dc/d21/page_lib_cavalry_opt_layers_doc.html#sec_cavalry_opt_layers_lic", null ]
    ] ],
    [ "CGPP Library API", "d8/d5f/page_lib_cgpp_doc.html", [
      [ "0. Revision History", "d8/d5f/page_lib_cgpp_doc.html#cgpp_history", null ],
      [ "1. Introduction", "d8/d5f/page_lib_cgpp_doc.html#cgpp_introduction", null ],
      [ "2. Example Usage", "d8/d5f/page_lib_cgpp_doc.html#cgpp_library_example_usage", [
        [ "2.1 test_cgpp Application", "d8/d5f/page_lib_cgpp_doc.html#cgpp_library_test_cgpp", null ],
        [ "2.1.1 test_cgpp in Resize Mode", "d8/d5f/page_lib_cgpp_doc.html#cgpp_library_test_cgpp_in_resize_mode", null ],
        [ "2.1.2 test_cgpp in WarpAffine Mode", "d8/d5f/page_lib_cgpp_doc.html#cgpp_library_test_cgpp_in_warp_mode", null ],
        [ "2.2 test_cgpp_live Application", "d8/d5f/page_lib_cgpp_doc.html#cgpp_library_test_cgpp_live", null ],
        [ "2.2.1 test_cgpp_live in Resize Mode", "d8/d5f/page_lib_cgpp_doc.html#cgpp_library_test_cgpp_live_in_resize_mode", null ],
        [ "2.2.2 test_cgpp_live in WarpAffine Mode", "d8/d5f/page_lib_cgpp_doc.html#cgpp_library_test_cgpp_live_in_warp_mode", null ],
        [ "2.3 CGPP Runtime Rotate / Flip", "d8/d5f/page_lib_cgpp_doc.html#cgpp_library_test_cgpp_runtime_rotate_flip", null ]
      ] ],
      [ "3. CGPP API", "d8/d5f/page_lib_cgpp_doc.html#sec_cgpp_api", null ],
      [ "4. License", "d8/d5f/page_lib_cgpp_doc.html#sec_cgpp_lic", null ]
    ] ],
    [ "Data Process Library API", "dc/d4f/page_lib_dproc_doc.html", [
      [ "0. Revision History", "dc/d4f/page_lib_dproc_doc.html#sec_dproc_history", null ],
      [ "1 Overview", "dc/d4f/page_lib_dproc_doc.html#sec_dproc_overview", null ],
      [ "2 Dproc Library Process", "dc/d4f/page_lib_dproc_doc.html#sec_dproc_proc", [
        [ "2.1 Build Dproc Library", "dc/d4f/page_lib_dproc_doc.html#dproc_proc_build", null ],
        [ "2.2 Dproc Library Usage Process", "dc/d4f/page_lib_dproc_doc.html#dproc_proc_proc", [
          [ "2.2.1 Process For SSD", "dc/d4f/page_lib_dproc_doc.html#dproc_proc_proc_ssd", null ],
          [ "2.2.2 Process For YOLOV3(TINY_YOLOV3)", "dc/d4f/page_lib_dproc_doc.html#dproc_proc_proc_yolov3", null ]
        ] ]
      ] ],
      [ "3 Unit Test", "dc/d4f/page_lib_dproc_doc.html#sec_dproc_test", null ],
      [ "4 Dproc API", "dc/d4f/page_lib_dproc_doc.html#sec_dproc_api", null ],
      [ "5 License", "dc/d4f/page_lib_dproc_doc.html#sec_dproc_lic", null ]
    ] ],
    [ "Depth Sensing Framework", "df/d58/page_lib_depth_fw_doc.html", [
      [ "0. Revision History", "df/d58/page_lib_depth_fw_doc.html#depth_history", null ],
      [ "1. Depth Sensing Framework", "df/d58/page_lib_depth_fw_doc.html#depth_framework", [
        [ "1.1 Depth Sensing Framework Introduction", "df/d58/page_lib_depth_fw_doc.html#depth_framework_introduction", [
          [ "1.1.1 Depth Sensing Framework Architecture", "df/d58/page_lib_depth_fw_doc.html#depth_framework_architecture", null ],
          [ "1.1.2 Depth Sensing Framework Software Stack", "df/d58/page_lib_depth_fw_doc.html#depth_framework_software_stack", null ],
          [ "1.1.3 Depth Sensing Framework Typical Flow", "df/d58/page_lib_depth_fw_doc.html#depth_framework_typical_processing_flow", null ],
          [ "1.1.4 Depth Sensing Framework Code Hierarchy", "df/d58/page_lib_depth_fw_doc.html#depth_framework_code_hierarchy", null ],
          [ "1.1.5 Depth Sensing Framework Required Menuconfig", "df/d58/page_lib_depth_fw_doc.html#depth_framework_required_menuconfig", null ]
        ] ],
        [ "1.2 Depth Sensing Framework Programming Guide", "df/d58/page_lib_depth_fw_doc.html#depth_framework_programming_guide", null ],
        [ "1.3 Depth Sensing Framework Unit Test", "df/d58/page_lib_depth_fw_doc.html#depth_framework_unit_test", [
          [ "1.3.1 Depth Sensing Framework Run-time Commands", "df/d58/page_lib_depth_fw_doc.html#dsf_runtime_commands", null ],
          [ "1.3.2 Depth Sensing Framework Example Usage", "df/d58/page_lib_depth_fw_doc.html#dsf_example_usage", null ]
        ] ],
        [ "1.4 Depth Sensing Framework Customization", "df/d58/page_lib_depth_fw_doc.html#depth_framework_customization", null ],
        [ "1.5 Depth Sensing Framework Profiling and Debug", "df/d58/page_lib_depth_fw_doc.html#depth_framework_profiling_and_debug", [
          [ "1.5.1 Depth Sensing Framework Log System", "df/d58/page_lib_depth_fw_doc.html#dsf_log_system", null ],
          [ "1.5.2 Depth Sensing Framework Performance Profiling", "df/d58/page_lib_depth_fw_doc.html#dsf_performance_profiling", null ],
          [ "1.5.3 Depth Sensing Framework Diagnosis", "df/d58/page_lib_depth_fw_doc.html#dsf_diagnosis", null ]
        ] ],
        [ "1.6 Depth Sensing Framework Graph Viewer", "df/d58/page_lib_depth_fw_doc.html#depth_framework_graph_viewer", null ],
        [ "1.7 Depth Sensing Framework Configuration Files Description", "df/d58/page_lib_depth_fw_doc.html#depth_framework_lc_explanation", null ],
        [ "1.8 Depth Sensing Framework API", "df/d58/page_lib_depth_fw_doc.html#depth_framework_api", null ]
      ] ],
      [ "2. Components for Depth Sensing Framework", "df/d58/page_lib_depth_fw_doc.html#dsf_components", [
        [ "2.1 Overview of DSF Components", "df/d58/page_lib_depth_fw_doc.html#dsf_components_overview", null ],
        [ "2.2 DSF C Components", "df/d58/page_lib_depth_fw_doc.html#dsf_c_components", [
          [ "2.2.1 C iToF Decoder", "df/d58/page_lib_depth_fw_doc.html#c_itof_decoder", null ],
          [ "2.2.2 C iToF Dual Frequency Decoder", "df/d58/page_lib_depth_fw_doc.html#c_dual_freq_decoder", null ],
          [ "2.2.3 C Compensation", "df/d58/page_lib_depth_fw_doc.html#c_compensation", null ],
          [ "2.2.4 C Spatial Median Filter", "df/d58/page_lib_depth_fw_doc.html#c_spatial_median_filter", null ],
          [ "2.2.5 C Spatial Gaussian Filter", "df/d58/page_lib_depth_fw_doc.html#c_spatial_gaussian_filter", null ],
          [ "2.2.6 C Normalization JET", "df/d58/page_lib_depth_fw_doc.html#c_normalization_jet", null ],
          [ "2.2.7 C Temporal Filter", "df/d58/page_lib_depth_fw_doc.html#c_temporal_filter", null ],
          [ "2.2.8 C Temporal IIR Filter", "df/d58/page_lib_depth_fw_doc.html#c_temporal_iir_filter", null ],
          [ "2.2.9 C Flying Pixel Removal", "df/d58/page_lib_depth_fw_doc.html#c_flying_pixel_removal", null ]
        ] ],
        [ "2.3 DSF AMBA Components", "df/d58/page_lib_depth_fw_doc.html#dsf_amba_components", [
          [ "2.3.1 AMBA iToF Sensor Input", "df/d58/page_lib_depth_fw_doc.html#amba_itof_sensor_input", null ],
          [ "2.3.2 AMBA dToF Sensor Input", "df/d58/page_lib_depth_fw_doc.html#amba_dtof_sensor_input", null ],
          [ "2.3.3 AMBA iToF Decoder", "df/d58/page_lib_depth_fw_doc.html#amba_itof_decoder", null ],
          [ "2.3.4 AMBA iToF Dual Frequency Decoder", "df/d58/page_lib_depth_fw_doc.html#amba_dual_freq_decoder", null ],
          [ "2.3.5 AMBA iToF Decoder for Calibration", "df/d58/page_lib_depth_fw_doc.html#amba_itof_dec_for_calib", null ],
          [ "2.3.6 AMBA Compensation", "df/d58/page_lib_depth_fw_doc.html#amba_compensation", null ],
          [ "2.3.7 AMBA AE Control", "df/d58/page_lib_depth_fw_doc.html#amba_ae_control", null ],
          [ "2.3.8 AMBA Depth Registration", "df/d58/page_lib_depth_fw_doc.html#amba_depth_registration", null ],
          [ "2.3.9 AMBA IDSP Phase IR", "df/d58/page_lib_depth_fw_doc.html#amba_idsp_phase_ir", null ],
          [ "2.3.10 AMBA Phase to Depth", "df/d58/page_lib_depth_fw_doc.html#amba_phase_to_depth", null ],
          [ "2.3.11 AMBA LDC", "df/d58/page_lib_depth_fw_doc.html#amba_ldc", null ],
          [ "2.3.12 AMBA Spatial Median Filter", "df/d58/page_lib_depth_fw_doc.html#amba_spatial_median_filter", null ],
          [ "2.3.13 AMBA Flying Pixel Removal", "df/d58/page_lib_depth_fw_doc.html#amba_flying_pixel_removal", null ]
        ] ],
        [ "2.4 DSF Display Components", "df/d58/page_lib_depth_fw_doc.html#dsf_display_components", [
          [ "2.4.1 Send to ROS", "df/d58/page_lib_depth_fw_doc.html#send_to_ros", null ],
          [ "2.4.2 Draw Depth on Linux Frame Buffer", "df/d58/page_lib_depth_fw_doc.html#draw_depth", null ],
          [ "2.4.3 Draw Overlay for Video Stream Encoding", "df/d58/page_lib_depth_fw_doc.html#draw_osd", null ]
        ] ],
        [ "2.5 DSF by External Library Components", "df/d58/page_lib_depth_fw_doc.html#dsf_by_extern_lib_components", [
          [ "2.5.1 OpenCV Flying Pixel Removal", "df/d58/page_lib_depth_fw_doc.html#opencv_flying_pixel_removal", null ],
          [ "2.5.2 OpenCV Normalization JET", "df/d58/page_lib_depth_fw_doc.html#opencv_normalization_jet", null ]
        ] ],
        [ "2.6 DSF Customized Components", "df/d58/page_lib_depth_fw_doc.html#dsf_customized_components", [
          [ "2.6.1 Yolov5", "df/d58/page_lib_depth_fw_doc.html#yolov5", null ],
          [ "2.6.2 Feed to EFM", "df/d58/page_lib_depth_fw_doc.html#feed_to_efm", null ],
          [ "2.6.3 Combine Depth and BBox", "df/d58/page_lib_depth_fw_doc.html#combine_depth_nv12_bbox", null ],
          [ "2.6.4 Draw detection result on Linux Frame Buffer", "df/d58/page_lib_depth_fw_doc.html#draw_det_fb", null ]
        ] ]
      ] ],
      [ "3. ToF Sensor", "df/d58/page_lib_depth_fw_doc.html#depth_tof", [
        [ "3.1 ToF Introduction", "df/d58/page_lib_depth_fw_doc.html#tof_introduction", null ],
        [ "3.2 Supported Sensor List", "df/d58/page_lib_depth_fw_doc.html#tof_supported_sensor_list", null ],
        [ "3.3 ToF Calibration", "df/d58/page_lib_depth_fw_doc.html#tof_calibration", [
          [ "3.3.1 ToF Build Steps", "df/d58/page_lib_depth_fw_doc.html#tof_calib_build_step", null ],
          [ "3.3.2 Calibration Dataset Capturing", "df/d58/page_lib_depth_fw_doc.html#tof_calib_capture", null ],
          [ "3.3.3 Lens Calibration", "df/d58/page_lib_depth_fw_doc.html#tof_lens_calib", null ],
          [ "3.3.4 Temperature Offset Calibration", "df/d58/page_lib_depth_fw_doc.html#tof_temperature_calib", null ],
          [ "3.3.5 Global Offset Calibration", "df/d58/page_lib_depth_fw_doc.html#tof_global_calib", null ],
          [ "3.3.6 Wiggling Calibration", "df/d58/page_lib_depth_fw_doc.html#tof_wiggle_calib", null ],
          [ "3.3.7 ToF and RGB Sensors Registration Calibration", "df/d58/page_lib_depth_fw_doc.html#tof_rgb_registration_calib", null ]
        ] ],
        [ "3.4 ToF Process Modules", "df/d58/page_lib_depth_fw_doc.html#tof_process", null ],
        [ "3.5 ToF Components", "df/d58/page_lib_depth_fw_doc.html#tof_pro_stages", [
          [ "3.5.1 ToF Process Input", "df/d58/page_lib_depth_fw_doc.html#tof_input", null ],
          [ "3.5.2 ToF Temporal Filter", "df/d58/page_lib_depth_fw_doc.html#tof_temporal_filter", null ],
          [ "3.5.3 ToF Spatial Filter", "df/d58/page_lib_depth_fw_doc.html#tof_spatial_filter", null ],
          [ "3.5.4 ToF Process Decode", "df/d58/page_lib_depth_fw_doc.html#tof_pro_decode", null ],
          [ "3.5.5 ToF Phase / Amplitude Raw Encode", "df/d58/page_lib_depth_fw_doc.html#tof_idsp_phase_ir", null ],
          [ "3.5.6 ToF LDC", "df/d58/page_lib_depth_fw_doc.html#tof_ldc", null ],
          [ "3.5.7 ToF Compensation", "df/d58/page_lib_depth_fw_doc.html#tof_compensation", null ],
          [ "3.5.8 ToF Phase Transformed To Depth", "df/d58/page_lib_depth_fw_doc.html#tof_phase_to_depth", null ],
          [ "3.5.9 ToF Auto Exposure Control", "df/d58/page_lib_depth_fw_doc.html#tof_ae_control", null ],
          [ "3.5.10 ToF RGBD Alignment", "df/d58/page_lib_depth_fw_doc.html#tof_rgbd_alignment", null ],
          [ "3.5.11 ToF Draw Depth", "df/d58/page_lib_depth_fw_doc.html#tof_draw_depth", null ],
          [ "3.5.12 ToF Live Point Cloud Shown On Ros", "df/d58/page_lib_depth_fw_doc.html#tof_live_show_ros", null ],
          [ "3.5.13 ToF Dual Frequency Decoding", "df/d58/page_lib_depth_fw_doc.html#tof_dual_frequency_decoder", null ],
          [ "3.5.14 ToF Flying Pixel Removal", "df/d58/page_lib_depth_fw_doc.html#tof_flying_pixel_removing", null ],
          [ "3.5.15 ToF Convert Depth Format", "df/d58/page_lib_depth_fw_doc.html#tof_convert_depth", null ],
          [ "3.5.16 ToF Draw OSD", "df/d58/page_lib_depth_fw_doc.html#tof_draw_osd", null ]
        ] ]
      ] ],
      [ "4. Display Point Cloud on ROS", "df/d58/page_lib_depth_fw_doc.html#sec_depth_disp_pc_on_ros", [
        [ "4.1 Host PC Preparation", "df/d58/page_lib_depth_fw_doc.html#host_prepare", [
          [ "4.1.1 Hardware Preparation", "df/d58/page_lib_depth_fw_doc.html#hardware_prepare", null ],
          [ "4.1.2 Software Preparation", "df/d58/page_lib_depth_fw_doc.html#software_prepare", null ]
        ] ],
        [ "4.2 ROS Preparation", "df/d58/page_lib_depth_fw_doc.html#ros_prepare", [
          [ "4.2.1 Install ROS", "df/d58/page_lib_depth_fw_doc.html#install_ros", null ],
          [ "4.2.2 Run ROS Core", "df/d58/page_lib_depth_fw_doc.html#run_ros_core", null ],
          [ "4.2.3 Run ROS Application", "df/d58/page_lib_depth_fw_doc.html#run_ros_app", null ],
          [ "4.2.4 Run Application in EVK", "df/d58/page_lib_depth_fw_doc.html#run_app_evk", null ],
          [ "4.2.5 Show Point Cloud in ROS", "df/d58/page_lib_depth_fw_doc.html#show_pt_ros", null ]
        ] ]
      ] ],
      [ "5. Display Point Cloud on Windows", "df/d58/page_lib_depth_fw_doc.html#sec_display_on_windows", null ],
      [ "6. Demo Application", "df/d58/page_lib_depth_fw_doc.html#sec_demo_app", [
        [ "6.1 CV22 Vision D EVK + IMX528", "df/d58/page_lib_depth_fw_doc.html#demo_visiond", [
          [ "6.1.1 Build Image on the Vision D EVK", "df/d58/page_lib_depth_fw_doc.html#cv22_vision_d_build_img", null ],
          [ "6.1.2 Compile Options", "df/d58/page_lib_depth_fw_doc.html#cv22_vision_d_compile_opts", null ],
          [ "6.1.3 Running Demo Applications", "df/d58/page_lib_depth_fw_doc.html#cv22_vision_d_run_demo_app", null ],
          [ "6.1.4 Display Point Cloud on Windows (Amba 3D Viewer)", "df/d58/page_lib_depth_fw_doc.html#cv22_vision_d_display_point_cloud", null ],
          [ "6.1.5 Display Depth with Yolov5 on VLC (Streaming)", "df/d58/page_lib_depth_fw_doc.html#cv22_vision_d_display_depth_yolov5_vlc", null ]
        ] ],
        [ "6.2 CV25_hazelnut + ADI3500 Sensor", "df/d58/page_lib_depth_fw_doc.html#demo_cv25_adi3500", [
          [ "6.2.1 Build Image on CV25_hazelnut", "df/d58/page_lib_depth_fw_doc.html#demo_adi3500_build", null ],
          [ "6.2.2 Prepare Related Files", "df/d58/page_lib_depth_fw_doc.html#demo_adi3500_prepare", null ],
          [ "6.2.3 Running Demo Applications", "df/d58/page_lib_depth_fw_doc.html#demo_adi3500_run", null ],
          [ "6.2.4 Performance on Boards", "df/d58/page_lib_depth_fw_doc.html#demo_adi3500_performance", null ],
          [ "6.2.5 Time of Flight (ToF) Depth Compute Engine NXP", "df/d58/page_lib_depth_fw_doc.html#demo_adi3500_TOFEngine", null ]
        ] ]
      ] ],
      [ "7. Performance", "df/d58/page_lib_depth_fw_doc.html#sec_depth_performance", null ],
      [ "8. ToF API", "df/d58/page_lib_depth_fw_doc.html#sec_depth_api", null ],
      [ "9. License", "df/d58/page_lib_depth_fw_doc.html#sec_depth_lic", null ]
    ] ],
    [ "Dewarp Library API", "da/d8b/page_lib_dewarp_doc.html", [
      [ "Important Declaration about Dewarp Support", "da/d8b/page_lib_dewarp_doc.html#dewarp_support", null ],
      [ "0. Revision History", "da/d8b/page_lib_dewarp_doc.html#dewarp_history", null ],
      [ "1. Overview", "da/d8b/page_lib_dewarp_doc.html#dewarp_overview", [
        [ "1.1 CV5x / CV7x Multi-Region Warp Mode Introduction", "da/d8b/page_lib_dewarp_doc.html#v6_fisheye_intro", null ],
        [ "1.2 CV5x / CV7x Lens Distortion Correction Introduction", "da/d8b/page_lib_dewarp_doc.html#v6_ldc_intro", null ],
        [ "1.3 LDC and Multi-Region Warp", "da/d8b/page_lib_dewarp_doc.html#LDC_and_dewarp", null ],
        [ "1.4 Warping Vector (Area) / Corrected View", "da/d8b/page_lib_dewarp_doc.html#warp_vector_view", null ]
      ] ],
      [ "2. Correction Mode", "da/d8b/page_lib_dewarp_doc.html#dewarp_correction_mode", [
        [ "2.1 No Transform", "da/d8b/page_lib_dewarp_doc.html#no_transform", null ],
        [ "2.2 No Transform Rotate", "da/d8b/page_lib_dewarp_doc.html#no_transform_rotate", null ],
        [ "2.3 Wall Rectilinear", "da/d8b/page_lib_dewarp_doc.html#wall_rectilinear", [
          [ "2.3.1 Advance Polar Warp", "da/d8b/page_lib_dewarp_doc.html#wall_adv_polar_warp", null ],
          [ "2.3.2 Tilt / Pan / Rotate or ROI / Rotate", "da/d8b/page_lib_dewarp_doc.html#wall_eyeball_rotation", null ],
          [ "2.3.3 Advanced Pitch / Yaw", "da/d8b/page_lib_dewarp_doc.html#wall_adv_py", null ]
        ] ],
        [ "2.4 Wall Panorama", "da/d8b/page_lib_dewarp_doc.html#wall_panorama", [
          [ "2.4.1 General Cylindrical and Panorama", "da/d8b/page_lib_dewarp_doc.html#wall_cylinder_panorama", null ],
          [ "2.4.2 Mercator", "da/d8b/page_lib_dewarp_doc.html#wall_mercator", null ],
          [ "2.4.3 Equirectangular", "da/d8b/page_lib_dewarp_doc.html#wall_equirectangular", null ],
          [ "2.4.4 Squircular", "da/d8b/page_lib_dewarp_doc.html#wall_squircular", null ],
          [ "2.4.5 Fan Warp", "da/d8b/page_lib_dewarp_doc.html#wall_pano_fan", null ]
        ] ],
        [ "2.5 Wall Vertical Panorama", "da/d8b/page_lib_dewarp_doc.html#wall_vertical_panorama", [
          [ "2.5.1 Transverse Mercator", "da/d8b/page_lib_dewarp_doc.html#wall_transverse_mercator", null ],
          [ "2.5.2 Transverse General Cylindrical", "da/d8b/page_lib_dewarp_doc.html#wall_transverse_cylinder", null ]
        ] ],
        [ "2.6 Wall Pannini", "da/d8b/page_lib_dewarp_doc.html#wall_pannini", null ],
        [ "2.7 Wall Pincushion", "da/d8b/page_lib_dewarp_doc.html#wall_pincushion", null ],
        [ "2.8 Ceiling / Desktop Panorama and Full Frame", "da/d8b/page_lib_dewarp_doc.html#ceiling_desktop_panorama_fulframe", null ],
        [ "2.9 Ceiling / Desktop Rectilinear", "da/d8b/page_lib_dewarp_doc.html#ceiling_desktop_rectilinear", null ],
        [ "2.10 Ceiling / Desktop Sub-Region", "da/d8b/page_lib_dewarp_doc.html#ceiling_desktop_sub", null ],
        [ "2.11 Transform 2D Vector to 1D+1D", "da/d8b/page_lib_dewarp_doc.html#transform_twin_vector_to_idsp_format", [
          [ "lens_warp_from_twin_vector", "da/d8b/page_lib_dewarp_doc.html#autotoc_md0", null ],
          [ "lens_warp_from_twin_coord", "da/d8b/page_lib_dewarp_doc.html#autotoc_md1", null ]
        ] ],
        [ "2.12 Loading Zhang Zhengyou Calibration Parameters", "da/d8b/page_lib_dewarp_doc.html#load_zzy_calib_param", null ],
        [ "2.13 Warp by Perspective Matrix", "da/d8b/page_lib_dewarp_doc.html#perspective_matrix", null ],
        [ "2.14 Point Mapping", "da/d8b/page_lib_dewarp_doc.html#point_mapping", [
          [ "2.14.1 Point Mapping with Warp Parameters", "da/d8b/page_lib_dewarp_doc.html#point_mapping_warp_param", null ],
          [ "2.14.2 Point Mapping with 1D+1D Warp Table", "da/d8b/page_lib_dewarp_doc.html#point_mapping_warp_table", null ]
        ] ]
      ] ],
      [ "3. Dewarp Lua Parser", "da/d8b/page_lib_dewarp_doc.html#dewarp_lua_parser", [
        [ "3.1 Dewarp Lua for Wall Rectilinear", "da/d8b/page_lib_dewarp_doc.html#dlp_wall_rectilinear", null ],
        [ "3.2 Dewarp Lua for Ceiling Double Panorama", "da/d8b/page_lib_dewarp_doc.html#dlp_double_panorama", null ]
      ] ],
      [ "4. Lens and Sensor", "da/d8b/page_lib_dewarp_doc.html#lens_sensor", [
        [ "4.1 Lens", "da/d8b/page_lib_dewarp_doc.html#lens_info", [
          [ "4.1.1 Attributes in Lens Datasheet", "da/d8b/page_lib_dewarp_doc.html#lens_attribute", null ],
          [ "4.1.2 Focal length and incident angle:", "da/d8b/page_lib_dewarp_doc.html#lens_info_fl_inc_angle", null ],
          [ "4.1.3 Field of view (FoV):", "da/d8b/page_lib_dewarp_doc.html#lens_info_fov", null ],
          [ "4.1.4 Image circle:", "da/d8b/page_lib_dewarp_doc.html#lens_info_img_circle", null ],
          [ "4.1.5 Lens projection function:", "da/d8b/page_lib_dewarp_doc.html#lens_info_proj_func", null ],
          [ "4.1.6 Lens LUT Mode", "da/d8b/page_lib_dewarp_doc.html#lens_lut", null ],
          [ "4.1.7 Lens LUT Examples", "da/d8b/page_lib_dewarp_doc.html#lens_lut_example", null ]
        ] ],
        [ "4.2 Sensor Selection", "da/d8b/page_lib_dewarp_doc.html#sensor_select", [
          [ "4.2.1 Full Fisheye Circle", "da/d8b/page_lib_dewarp_doc.html#full_fisheye_circle", null ],
          [ "4.2.2 Fisheye Image Quality", "da/d8b/page_lib_dewarp_doc.html#fisheye_IQ", null ],
          [ "4.2.3 Mounting Lens", "da/d8b/page_lib_dewarp_doc.html#mount_lens", null ]
        ] ],
        [ "4.3 Fisheye Center", "da/d8b/page_lib_dewarp_doc.html#fisheye_center", null ]
      ] ],
      [ "5. System Configuration", "da/d8b/page_lib_dewarp_doc.html#warp_system_config", [
        [ "5.1 Dual Channel for Multi-Region Warp", "da/d8b/page_lib_dewarp_doc.html#warp_dual_chan", [
          [ "Pros and Cons", "da/d8b/page_lib_dewarp_doc.html#autotoc_md2", null ],
          [ "EFR with YUV for warped channel:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md3", null ],
          [ "Fake pre-main:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md4", null ]
        ] ],
        [ "5.2 Warp Hardware Resource", "da/d8b/page_lib_dewarp_doc.html#warp_hw_res", [
          [ "Maximum Warp Input / Output Width:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md5", null ],
          [ "max_padding_width / lens_warp:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md6", null ],
          [ "max_vwarp_blk_height:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md7", null ],
          [ "max_vwarp_wait_lines:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md8", null ]
        ] ],
        [ "5.3 Warp Alignment", "da/d8b/page_lib_dewarp_doc.html#warp_align", null ],
        [ "5.4 Privacy Mask (PM) on Warp View", "da/d8b/page_lib_dewarp_doc.html#pm_on_warp", [
          [ "Privacy Mask with LDC:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md9", null ],
          [ "Circle PM on Fisheye:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md10", null ]
        ] ],
        [ "5.5 Main Buffer Layout Design", "da/d8b/page_lib_dewarp_doc.html#post_buffer_layout", [
          [ "Main Buffer Size:", "da/d8b/page_lib_dewarp_doc.html#autotoc_md11", null ],
          [ "Wall Mount: Rectilinear", "da/d8b/page_lib_dewarp_doc.html#autotoc_md12", null ]
        ] ],
        [ "5.6 Warp DPTZ", "da/d8b/page_lib_dewarp_doc.html#warp_dptz", null ],
        [ "5.7 Warp Input Mode", "da/d8b/page_lib_dewarp_doc.html#warp_input_mode", null ],
        [ "5.8 ME1 H/V for Lens Warp", "da/d8b/page_lib_dewarp_doc.html#ldc_me1", null ]
      ] ],
      [ "6. Dewarp Development", "da/d8b/page_lib_dewarp_doc.html#dewarp_development", [
        [ "6.1 Introduction to \"dewarp_init_param\"", "da/d8b/page_lib_dewarp_doc.html#dewarp_intro_init_param", null ],
        [ "6.2 LDC Development", "da/d8b/page_lib_dewarp_doc.html#dewarp_ldc_dev", null ],
        [ "6.3 Multi-Region Warp Development", "da/d8b/page_lib_dewarp_doc.html#multi_region_warp", null ]
      ] ],
      [ "7. Dewarp Trouble Shooting", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa", [
        [ "Question 1: What is the difference between LDC and multi-region dewarp?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q1", null ],
        [ "Question 2: Why there are artifacts in the warp results when performing rotation in large angles?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q2", null ],
        [ "Question 3: How can users get a panning effect from ceiling-mount 360 panorama?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q3", null ],
        [ "Question 4: What are easy ways to configure parameters for different warp views using test_dewarp?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q4", null ],
        [ "Question 5: Are there examples for each correction mode?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q5", null ],
        [ "Question 6: How do users sharpen a fisheye edge?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q6", null ],
        [ "Question 7: Does multi-region warp mode function with multiple VIN sources?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q7", null ],
        [ "Question 8: How can the warp view aspect ratio be maintained?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q8", null ],
        [ "Question 9: How to get the vertical warp waitlines under encode mode 0?", "da/d8b/page_lib_dewarp_doc.html#dewarp_qa_q9", null ]
      ] ],
      [ "8. Dewarp API", "da/d8b/page_lib_dewarp_doc.html#dewarp_api_sec", null ],
      [ "9. License", "da/d8b/page_lib_dewarp_doc.html#dewarp_license", null ]
    ] ],
    [ "EazyAI Library API", "d3/d0c/page_lib_eazyai_doc.html", [
      [ "0 Revision History", "d3/d0c/page_lib_eazyai_doc.html#eazyai_history", null ],
      [ "1 Introduction", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction", [
        [ "1.1 Overview", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_overview", null ],
        [ "1.2 NN CVflow Inference", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_cvflow", null ],
        [ "1.3 NN Simulator Inference", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_simulator", null ],
        [ "1.4 NN Postprocess", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_arm_postprocess", null ],
        [ "1.5 Traditional Algorithms Acceleration", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_cvflow_traditional_accl", null ],
        [ "1.6 Unit Test", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_unit_test", null ],
        [ "1.7 Application", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_apps", null ],
        [ "1.8 Folder Structure", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_folder_structure", null ],
        [ "1.9 API Updates", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_api_new", null ],
        [ "2.0 API Compatibility Violation", "d3/d0c/page_lib_eazyai_doc.html#eazyai_introduction_api_break", null ]
      ] ],
      [ "2 EazyAI Deployment", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow", [
        [ "2.1 Build", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_build", [
          [ "2.1.1 Include", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_build_include", null ],
          [ "2.1.2 Makefile", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_build_makefile", null ],
          [ "2.1.3 Configuration", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_build_configuration", null ]
        ] ],
        [ "2.2 Core Library", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_core", [
          [ "2.2.1 Core Library - ea_env", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_core_env", null ],
          [ "2.2.2 Core Library - ea_tensor", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_core_tensor", null ],
          [ "2.2.3 Core Library - ea_img_resource", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_core_img_resource", null ],
          [ "2.2.4 Core Library - ea_preprocess", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_core_preprocess", null ],
          [ "2.2.5 Core Library - ea_net", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_core_net", null ],
          [ "2.2.6 Core Library - ea_osd", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_core_osd", null ],
          [ "2.2.7 Core Library - ea_log", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_core_log", null ]
        ] ],
        [ "2.3 Utils Library", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_utils", [
          [ "2.3.1 Utils Library - ea_display", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_utils_display", null ],
          [ "2.3.2 Utils Library - ea_utils", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_sub_utils", null ],
          [ "2.3.3 Utils Library - ea_orb_extractor", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_sub_orb_extractor", null ],
          [ "2.3.3 Utils Library - ea_topic", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_sub_topic", null ]
        ] ],
        [ "2.4 Communication Library", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_comm", [
          [ "2.4.1 Comm Library - ea_queue", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_comm_queue", null ],
          [ "2.4.2 Comm Library - ea_socket", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_comm_socket", null ]
        ] ],
        [ "2.5 Acceleration Library", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_accl", [
          [ "2.5.1 ACCL Library - ea_fast", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_accl_fast", null ],
          [ "2.5.2 ACCL Library - ea_angle", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_accl_angle", null ],
          [ "2.5.3 ACCL Library - ea_brief", "d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_accl_brief", null ]
        ] ]
      ] ],
      [ "3 EazyAI Simulator", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator", [
        [ "3.1 Build", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_build", [
          [ "3.1.1 Include", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_build_include", null ],
          [ "3.1.2 Compile", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_build_compile", null ]
        ] ],
        [ "3.2 Components", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_components", [
          [ "3.2.1 ea_env", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_components_env", null ],
          [ "3.2.2 ea_tensor", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_components_tensor", null ],
          [ "3.2.3 ea_img_resource", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_components_img_resource", null ],
          [ "3.2.4 ea_preprocess", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_components_preprocess", null ],
          [ "3.2.5 ea_net", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_components_net", null ],
          [ "3.2.6 ea_display", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_components_display", null ],
          [ "3.2.7 ea_log", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_components_log", null ],
          [ "3.2.8 ea_utils", "d3/d0c/page_lib_eazyai_doc.html#eazyai_simulator_simulator_components_utils", null ]
        ] ]
      ] ],
      [ "4 EazyAI Arm Postprocess", "d3/d0c/page_lib_eazyai_doc.html#eazyai_arm_postprocess", [
        [ "4.1 Build", "d3/d0c/page_lib_eazyai_doc.html#eazyai_arm_postprocess_build", null ],
        [ "4.2 How to Add Customized Postprocess", "d3/d0c/page_lib_eazyai_doc.html#eazyai_arm_postprocess_customize_postprocess", [
          [ "4.2.1 Implement", "d3/d0c/page_lib_eazyai_doc.html#eazyai_arm_postprocess_customize_postprocess_implement", null ],
          [ "4.2.2 Include", "d3/d0c/page_lib_eazyai_doc.html#eazyai_arm_postprocesss_custmoize_postprocess_include", null ],
          [ "4.2.3 Register Postprocess", "d3/d0c/page_lib_eazyai_doc.html#eazyai_arm_postprocess_customize_postprocess_register", null ],
          [ "4.2.4 Configure", "d3/d0c/page_lib_eazyai_doc.html#eazyai_arm_postprocess_custmoize_postprocess_configure", null ],
          [ "4.2.5 Makefile", "d3/d0c/page_lib_eazyai_doc.html#eazyai_arm_postprocess_customize_postprocess_makefile", null ]
        ] ]
      ] ],
      [ "5 EazyAI Unit Test", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test", [
        [ "5.1 CVflow Inference Test", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test_cvflow", [
          [ "5.1.1 Build", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test_cvflow_build", null ],
          [ "5.1.2 Unit Test Usage", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test_cvflow_usage", null ],
          [ "5.1.3 Examples", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test_cvflow__example", null ]
        ] ],
        [ "5.2 Simulator Inference Test", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test_simulator", [
          [ "5.2.1 Build", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test_simulator_build", null ],
          [ "5.2.2 Usage", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test_simulator_usage", null ],
          [ "5.2.3 Examples", "d3/d0c/page_lib_eazyai_doc.html#eazyai_unit_test_simulator_example", null ]
        ] ],
        [ "5.3 Core API Test", "d3/d0c/page_lib_eazyai_doc.html#eazyai_core_api_test", null ],
        [ "5.4 Display Test", "d3/d0c/page_lib_eazyai_doc.html#eazyai_display_unit_test_cvflow", [
          [ "5.4.1 Build", "d3/d0c/page_lib_eazyai_doc.html#eazyai_display_unit_test_cvflow_build", null ],
          [ "5.4.2 Usage", "d3/d0c/page_lib_eazyai_doc.html#eazyai_display_unit_test_cvflow_usage", null ],
          [ "5.4.3 Examples", "d3/d0c/page_lib_eazyai_doc.html#eazyai_display_unit_test_cvflow_examples", null ]
        ] ],
        [ "5.5 ORB Extractor Test", "d3/d0c/page_lib_eazyai_doc.html#eazyai_orb_extractor_unit_test", null ],
        [ "5.6 Topic Test", "d3/d0c/page_lib_eazyai_doc.html#eazyai_topic_unit_test", null ]
      ] ],
      [ "6 EazyAI API", "d3/d0c/page_lib_eazyai_doc.html#eazyai_api", null ],
      [ "7 License", "d3/d0c/page_lib_eazyai_doc.html#eazyai_license", null ]
    ] ],
    [ "EIS Library API", "d6/db6/page_lib_eis_doc.html", [
      [ "0. Revision History", "d6/db6/page_lib_eis_doc.html#eis_history", null ],
      [ "1. Overview", "d6/db6/page_lib_eis_doc.html#eis_overview", [
        [ "1.1. EIS Introduction", "d6/db6/page_lib_eis_doc.html#eis_intro", null ],
        [ "1.2. EIS Specification", "d6/db6/page_lib_eis_doc.html#eis_spec", null ]
      ] ],
      [ "2. Implementation", "d6/db6/page_lib_eis_doc.html#eis_implementation", [
        [ "2.1 Rolling Shaking", "d6/db6/page_lib_eis_doc.html#eis_rolling_shaking", null ],
        [ "2.2 Definition of Pitch / Roll / Yaw", "d6/db6/page_lib_eis_doc.html#eis_pry_def", null ],
        [ "2.3 Virtual Axis Mapping", "d6/db6/page_lib_eis_doc.html#eis_va_map", null ],
        [ "2.4 Encode Mode", "d6/db6/page_lib_eis_doc.html#eis_enc", null ],
        [ "2.5 Warp Vector", "d6/db6/page_lib_eis_doc.html#eis_warp_vector", null ],
        [ "2.6 Building", "d6/db6/page_lib_eis_doc.html#eis_build", [
          [ "2.6.1 Board", "d6/db6/page_lib_eis_doc.html#eis_build_board", null ],
          [ "2.6.2 Driver", "d6/db6/page_lib_eis_doc.html#eis_build_drv", null ],
          [ "2.6.3 Unit test", "d6/db6/page_lib_eis_doc.html#eis_build_test", null ],
          [ "2.6.4 IAV Memory — IK Buffer Size", "d6/db6/page_lib_eis_doc.html#eis_build_iav_mem", null ]
        ] ],
        [ "2.7 EIS with Privacy Mask", "d6/db6/page_lib_eis_doc.html#eis_pm", null ]
      ] ],
      [ "3. Design", "d6/db6/page_lib_eis_doc.html#eis_design", [
        [ "3.1 Device Tree Configuration", "d6/db6/page_lib_eis_doc.html#gyro_dev_tree", null ],
        [ "3.2 IMU Selection", "d6/db6/page_lib_eis_doc.html#eis_imu", null ],
        [ "3.3 CMOS Sensor", "d6/db6/page_lib_eis_doc.html#eis_sensor", null ],
        [ "3.4 Window", "d6/db6/page_lib_eis_doc.html#eis_window", [
          [ "3.4.1 VIN Window", "d6/db6/page_lib_eis_doc.html#eis_res_vin", null ],
          [ "3.4.2 EIS Window", "d6/db6/page_lib_eis_doc.html#eis_res_eis", null ]
        ] ],
        [ "3.5 EIS Filter Mode", "d6/db6/page_lib_eis_doc.html#eis_filter_mode", null ],
        [ "3.6 Lens", "d6/db6/page_lib_eis_doc.html#eis_des_lens", null ],
        [ "3.7 Real Time Update", "d6/db6/page_lib_eis_doc.html#eis_rt_change", null ],
        [ "3.8 Example", "d6/db6/page_lib_eis_doc.html#eis_des_example", [
          [ "3.8.1 IMX274 + EVK + Enable \"--eis-output\"", "d6/db6/page_lib_eis_doc.html#eis_ex_1", null ],
          [ "3.8.2 IMX274 + EVK + Dual VIN EIS", "d6/db6/page_lib_eis_doc.html#eis_ex_2", null ],
          [ "3.8.3 IMX274 + EVK + Enable EIS and LDC", "d6/db6/page_lib_eis_doc.html#eis_ex_3", null ],
          [ "3.8.4 IMX274 + EIS + Rotation", "d6/db6/page_lib_eis_doc.html#eis_ex_4", null ]
        ] ]
      ] ],
      [ "4. EIS Development", "d6/db6/page_lib_eis_doc.html#eis_development", null ],
      [ "5. Tuning", "d6/db6/page_lib_eis_doc.html#eis_tuning", [
        [ "5.1 Gyro", "d6/db6/page_lib_eis_doc.html#gyro_tuning", null ],
        [ "5.2 Lens", "d6/db6/page_lib_eis_doc.html#lens_tuning", null ],
        [ "5.3 Timing", "d6/db6/page_lib_eis_doc.html#timing_tuning", null ],
        [ "5.4 Margin", "d6/db6/page_lib_eis_doc.html#margin_tuning", null ],
        [ "5.5 Filter Mode", "d6/db6/page_lib_eis_doc.html#filter_mode_tuning", null ],
        [ "5.6 Filter Scale", "d6/db6/page_lib_eis_doc.html#filter_scale_tuning", null ],
        [ "5.7 Debug Method", "d6/db6/page_lib_eis_doc.html#debug_method", null ]
      ] ],
      [ "6. FAQ", "d6/db6/page_lib_eis_doc.html#eis_qa", [
        [ "Question 1. How can users ensure that the gyro is functioning as per the design?", "d6/db6/page_lib_eis_doc.html#eis_qa_q1", null ],
        [ "Question 2. Why is the EIS effect not as good as the EVK reference design solution?", "d6/db6/page_lib_eis_doc.html#eis_qa_q2", null ],
        [ "Question 3. Does EIS function with the LDC feature?", "d6/db6/page_lib_eis_doc.html#eis_qa_q3", null ],
        [ "Question 4. Does EIS function with the HDR feature?", "d6/db6/page_lib_eis_doc.html#eis_qa_q4", null ],
        [ "Question 5. Does EIS function with the fisheye dewarp feature?", "d6/db6/page_lib_eis_doc.html#eis_qa_q5", null ],
        [ "Question 6. Which gyro sensor is supported? If there is a new gyro sensor not included in the list, can it be supported ?", "d6/db6/page_lib_eis_doc.html#eis_qa_q6", null ],
        [ "Question 7. How do users define the size of the margin between the VIN window and the EIS output window?", "d6/db6/page_lib_eis_doc.html#eis_qa_q7", null ],
        [ "Question 8. What is the process to re-configure the EIS library when the VIN resolution or frame rate changes?", "d6/db6/page_lib_eis_doc.html#eis_qa_q8", null ],
        [ "Question 9. When EIS is enabled, why does DPTZ type I fail?", "d6/db6/page_lib_eis_doc.html#eis_qa_q9", null ],
        [ "Question 10. Does Ambarella support IMU sensors that are not in included in the standard SDK?", "d6/db6/page_lib_eis_doc.html#eis_qa_q10", null ],
        [ "Question 11. Does EIS require calibration?", "d6/db6/page_lib_eis_doc.html#eis_qa_q11", null ],
        [ "Question 12. What are the steps to configure the main buffer size of the EIS source channel and the EIS effective channel?", "d6/db6/page_lib_eis_doc.html#eis_qa_q12", null ],
        [ "Question 13. How do you know the maximum correction angles with specific EIS output window size?", "d6/db6/page_lib_eis_doc.html#eis_qa_q13", null ],
        [ "Question 14. Why does EIS cache a certain number of frames in external memory?", "d6/db6/page_lib_eis_doc.html#eis_qa_q14", null ]
      ] ],
      [ "7. EIS Application Programming Interface", "d6/db6/page_lib_eis_doc.html#sec_eis_api", null ],
      [ "8. License", "d6/db6/page_lib_eis_doc.html#sec_eis_lic", null ]
    ] ],
    [ "Image Flow Library API", "d5/d4f/page_lib_img_flow_doc.html", [
      [ "0. Revision History", "d5/d4f/page_lib_img_flow_doc.html#img_flow_history", null ],
      [ "1. Introduction", "d5/d4f/page_lib_img_flow_doc.html#img_flow_introduction", null ],
      [ "2. Image Flow Usage", "d5/d4f/page_lib_img_flow_doc.html#img_flow_usage", [
        [ "2.1 How to Enable Image Flow Library", "d5/d4f/page_lib_img_flow_doc.html#img_flow_lib_usage_enable", null ],
        [ "2.2 How to Run test_aaa_service Application", "d5/d4f/page_lib_img_flow_doc.html#img_flow_lib_usage_run_app", null ],
        [ "2.3 How to Use Image Flow Library Better", "d5/d4f/page_lib_img_flow_doc.html#img_flow_lib_usage_advanced_func", null ],
        [ "2.4 How to Make Lua Files for Multi-channel Cases", "d5/d4f/page_lib_img_flow_doc.html#img_flow_lib_usage_lua_file", null ],
        [ "2.5 How to Add a New Sensor or an Application Type", "d5/d4f/page_lib_img_flow_doc.html#img_flow_lib_usage_add_new_app_type", [
          [ "2.5.1 How to Add a New Application Type", "d5/d4f/page_lib_img_flow_doc.html#img_flow_lib_usage_add_type", null ],
          [ "2.5.2 How to Add a New Sensor", "d5/d4f/page_lib_img_flow_doc.html#img_flow_lib_usage_add_sensor", null ]
        ] ]
      ] ],
      [ "3. Image Flow API", "d5/d4f/page_lib_img_flow_doc.html#img_flow_api", null ],
      [ "4. License", "d5/d4f/page_lib_img_flow_doc.html#img_flow_lic", null ]
    ] ],
    [ "Image Library API", "d7/de0/page_lib_img_doc.html", [
      [ "0. Revision History", "d7/de0/page_lib_img_doc.html#img_lib_history", null ],
      [ "1. Introduction", "d7/de0/page_lib_img_doc.html#img_lib_introduction", null ],
      [ "2. Image Pipeline", "d7/de0/page_lib_img_doc.html#img_lib_pipeline", null ],
      [ "3. AAA Statistics Information", "d7/de0/page_lib_img_doc.html#aaa_statistics", [
        [ "3.1 AAA Statistics Tile Number", "d7/de0/page_lib_img_doc.html#aaa_statistics_tile_num", null ],
        [ "3.2 Considerations", "d7/de0/page_lib_img_doc.html#considerations_of_aaa", null ]
      ] ],
      [ "4. Image Library API", "d7/de0/page_lib_img_doc.html#img_lib_api", null ],
      [ "5. License", "d7/de0/page_lib_img_doc.html#img_lib_lic", null ]
    ] ],
    [ "NNCtrl Library API", "d7/d46/page_lib_nnctrl_doc.html", [
      [ "0. Revision History", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_history", null ],
      [ "1. Introduction", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_introduction", null ],
      [ "2. Example Usage", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_example_usage", [
        [ "2.1 cavalry_gen", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_cavalry_gen", null ],
        [ "2.1.1 cavalry_gen_api_version", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_cavalry_gen_api_version", null ],
        [ "2.1.2 cavalry_gen_chip_version", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_cavalry_gen_chip_version", null ],
        [ "2.2 test_nnctrl Application", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl", null ],
        [ "2.2.1 test_nnctrl Show IO Information", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl_show_io_info", null ],
        [ "2.2.2 test_nnctrl Reuse Port Memory", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl_reuse_mem", null ],
        [ "2.2.3 test_nnctrl Dump Net", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl_dump_net", null ],
        [ "2.2.3 test_nnctrl io no_mem", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl_no_mem", null ],
        [ "2.2.4 test_nnctrl multi-io", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl_multi_io", null ],
        [ "2.2.5 test_nnctrl Multi-net", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl_multi_net", null ],
        [ "2.2.6 test_nnctrl IO Rotate Flip", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl_io_rotate_flip", null ],
        [ "2.3 Vector Processor (VP) DRAM Bandwidth", "d7/d46/page_lib_nnctrl_doc.html#nnctrl_library_test_nnctrl_dram_bandwith", null ]
      ] ],
      [ "3. NNCtrl API", "d7/d46/page_lib_nnctrl_doc.html#sec_nnctrl_api", null ],
      [ "4. License", "d7/d46/page_lib_nnctrl_doc.html#sec_nnctrl_lic", null ]
    ] ],
    [ "Sensor Calibration Library API", "d1/d1e/page_lib_sensor_calib_doc.html", [
      [ "Introduction", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_introduction", null ],
      [ "1. Calibration Configration File Descriptions", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_cfg", null ],
      [ "2. Stitching Pose Calibration", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_stitch", [
        [ "2.1 Stitching Pose Calibration Flow", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_chip", null ]
      ] ],
      [ "3. Thermal and RGB Sensors Calibration", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_thermal_rgb", null ],
      [ "4. Mono and RGB Sensor Calibration", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_mono_rgb", null ],
      [ "5. Tool Usage", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_tool_usage", [
        [ "5.1 Feature Usage", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_tool_usage_function", null ],
        [ "5.2 Generate 2D Warp Table via Calib-Param", "d1/d1e/page_lib_sensor_calib_doc.html#calib_2dwarp_gen_tool_usage", null ]
      ] ],
      [ "6. Sensor Calibration API", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_api", null ],
      [ "7. License", "d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_lic", null ]
    ] ],
    [ "SmartFB Library API", "dc/d67/page_lib_smartfb_doc.html", [
      [ "0. Revision History", "dc/d67/page_lib_smartfb_doc.html#SmartFB_history", null ],
      [ "1. Overview", "dc/d67/page_lib_smartfb_doc.html#SmartFB_overview", null ],
      [ "2. SmartFB Library Process", "dc/d67/page_lib_smartfb_doc.html#SmartFB_proc", [
        [ "2.1   Dependency Library", "dc/d67/page_lib_smartfb_doc.html#SmartFB_proc_dep", null ],
        [ "2.2 Color Mode", "dc/d67/page_lib_smartfb_doc.html#SmartFB_color_mode", null ],
        [ "2.3 CLUT", "dc/d67/page_lib_smartfb_doc.html#SmartFB_clut", null ],
        [ "2.4 Cycle-buffer Mechanism", "dc/d67/page_lib_smartfb_doc.html#SmartFB_cycle_buffer", null ],
        [ "2.5 FrameBuffer Common Structure", "dc/d67/page_lib_smartfb_doc.html#SmartFB_structure", null ],
        [ "2.6 FrameBuffer Usage Process", "dc/d67/page_lib_smartfb_doc.html#SmartFB_proc_usage", null ]
      ] ],
      [ "3. Unit Test", "dc/d67/page_lib_smartfb_doc.html#sec_SmartFB_test", [
        [ "3.1 Main Loop", "dc/d67/page_lib_smartfb_doc.html#SmartFB_test_lp", null ],
        [ "3.2 Examples", "dc/d67/page_lib_smartfb_doc.html#SmartFB_test_examp", [
          [ "3.2.1 Draw Solid Box", "dc/d67/page_lib_smartfb_doc.html#SmartFB_test_examp_solid_box", null ],
          [ "3.2.2 Draw Mosaic", "dc/d67/page_lib_smartfb_doc.html#SmartFB_test_examp_mosaic", null ],
          [ "3.2.3 Draw Other Objects", "dc/d67/page_lib_smartfb_doc.html#SmartFB_test_examp_other_objects", null ]
        ] ]
      ] ],
      [ "4. SmartFB API", "dc/d67/page_lib_smartfb_doc.html#sec_SmartFB_api", null ],
      [ "5. License", "dc/d67/page_lib_smartfb_doc.html#sec_SmartFB_lic", null ]
    ] ],
    [ "SmartRC V3 Library API", "dc/d70/page_lib_src_v3.html", [
      [ "0. Revision History", "dc/d70/page_lib_src_v3.html#srcv3_history", null ],
      [ "1. Overview", "dc/d70/page_lib_src_v3.html#srcv3_overview", null ],
      [ "2. Building", "dc/d70/page_lib_src_v3.html#srcv3_build", null ],
      [ "3. Design", "dc/d70/page_lib_src_v3.html#srcv3_design", [
        [ "3.1 Preanalysis", "dc/d70/page_lib_src_v3.html#srcv3_preanalysis", null ],
        [ "3.2 Frame-Level Control", "dc/d70/page_lib_src_v3.html#srcv3_fctl", null ],
        [ "3.3 ROI-Level Control", "dc/d70/page_lib_src_v3.html#srcv3_roictl", null ],
        [ "3.4 Computer Vision (CV) Control", "dc/d70/page_lib_src_v3.html#srcv3_cvctl", null ]
      ] ],
      [ "4. Parameter Adjustment", "dc/d70/page_lib_src_v3.html#srcv3_padj", [
        [ "4.1 Frame-Level Parameters", "dc/d70/page_lib_src_v3.html#srcv3_frame_level_params", null ],
        [ "4.2 ROI-Level Parameters", "dc/d70/page_lib_src_v3.html#srcv3_roi_level_params", null ]
      ] ],
      [ "5. Lua Parser", "dc/d70/page_lib_src_v3.html#srcv3_lp", [
        [ "5.1 Lua Description", "dc/d70/page_lib_src_v3.html#srcv3_lp_fw", null ]
      ] ],
      [ "6. Unit Test", "dc/d70/page_lib_src_v3.html#srcv3_ut", [
        [ "6.1 Smart Rate Control Application", "dc/d70/page_lib_src_v3.html#srcv3_ut_src", null ],
        [ "6.2 Computer Vision Application", "dc/d70/page_lib_src_v3.html#srcv3_ut_cv", null ],
        [ "6.3 Lua Application", "dc/d70/page_lib_src_v3.html#srcv3_ut_lp", null ]
      ] ],
      [ "7. Examples", "dc/d70/page_lib_src_v3.html#srcv3_exp", [
        [ "7.1 Enter Preview", "dc/d70/page_lib_src_v3.html#srcv3_exp_prev", null ],
        [ "7.2 Frame-Level Control", "dc/d70/page_lib_src_v3.html#srcv3_exp_frame", null ],
        [ "7.3 ROI-level Control", "dc/d70/page_lib_src_v3.html#srcv3_exp_roi", null ],
        [ "7.4 Apply ROI Matrix for B Frames", "dc/d70/page_lib_src_v3.html#srcv3_exp_roi_for_B", null ],
        [ "7.5 Draw Spots", "dc/d70/page_lib_src_v3.html#srcv3_exp_drwspt", null ],
        [ "7.6 Dump Maps", "dc/d70/page_lib_src_v3.html#srcv3_exp_dm", null ],
        [ "7.7 Auto Tests", "dc/d70/page_lib_src_v3.html#srcv3_exp_at", null ],
        [ "7.8 Lua Script", "dc/d70/page_lib_src_v3.html#srcv3_exp_lp", null ],
        [ "7.9 Disable Low-Light Profiles", "dc/d70/page_lib_src_v3.html#srcv3_exp_disable_low_light", null ],
        [ "7.10 Threshold of Motion and Noise in the Lua Script", "dc/d70/page_lib_src_v3.html#srcv3_exp_thres", null ],
        [ "7.11 Apply CV Output with Non-Frame Sync Mode", "dc/d70/page_lib_src_v3.html#srcv3_exp_apply_cv_output_with_non_frame_sync", null ],
        [ "7.12 Cooperate with CV", "dc/d70/page_lib_src_v3.html#srcv3_exp_cv", null ],
        [ "7.13 Draw CV Boxes", "dc/d70/page_lib_src_v3.html#srcv3_exp_cvo", null ],
        [ "7.14 Choose Motion from CV Bbox or PA Library", "dc/d70/page_lib_src_v3.html#srcv3_exp_motion", null ]
      ] ],
      [ "8. Tuning Guide", "dc/d70/page_lib_src_v3.html#srcv3_tuning", [
        [ "8.1 Tuning Frame-Level Parameters", "dc/d70/page_lib_src_v3.html#srcv3_frame_level_tuning", [
          [ "8.1.1 GOP Length", "dc/d70/page_lib_src_v3.html#srcv3_gop_tuning", null ],
          [ "8.1.2 Bit Rate", "dc/d70/page_lib_src_v3.html#srcv3_bitrate_tuning", null ],
          [ "8.1.3 QP Limitation", "dc/d70/page_lib_src_v3.html#srcv3_qp_limitation_tuning", null ],
          [ "8.1.4 QP Reduction", "dc/d70/page_lib_src_v3.html#srcv3_qp_reduce_tuning", null ],
          [ "8.1.5 Skip_frame and Drop_frame", "dc/d70/page_lib_src_v3.html#srcv3_skip_frame_drop_frame_tuning", null ],
          [ "8.1.6 Chroma_qp_offset", "dc/d70/page_lib_src_v3.html#srcv3_chroma_qp_offset_tuning", null ],
          [ "8.1.7 Zmv_threshold_qp_offset", "dc/d70/page_lib_src_v3.html#srcv3_zmv_threshold_qp_offset_tuning", null ]
        ] ],
        [ "8.2 Tuning ROI-Level Parameters", "dc/d70/page_lib_src_v3.html#srcv3_roi_level_tuning", [
          [ "8.2.1 QP Adjust (QP Offset)", "dc/d70/page_lib_src_v3.html#srcv3_qp_adjust_tuning", null ],
          [ "8.2.2 User Class", "dc/d70/page_lib_src_v3.html#srcv3_user_class_tuning", null ],
          [ "8.2.3 Category", "dc/d70/page_lib_src_v3.html#srcv3_category_tuning", null ],
          [ "8.2.4 ZMV Threshold", "dc/d70/page_lib_src_v3.html#srcv3_zmv_threshold_tuning", null ]
        ] ],
        [ "8.3 Fine-Tuning by EFR", "dc/d70/page_lib_src_v3.html#srcv3_fine_tuning", null ]
      ] ],
      [ "9. FAQ", "dc/d70/page_lib_src_v3.html#srcv3_faq", null ],
      [ "10. SmartRC APIs", "dc/d70/page_lib_src_v3.html#srcv3_api", null ],
      [ "11. License", "dc/d70/page_lib_src_v3.html#srcv3_lic", null ]
    ] ],
    [ "Stitch Library API", "dd/da8/page_lib_stitch_doc.html", [
      [ "0. Revision History", "dd/da8/page_lib_stitch_doc.html#stitch_history", null ],
      [ "1. Introduction", "dd/da8/page_lib_stitch_doc.html#stitch_introduction", [
        [ "1.1 Ambarella Stitching Features", "dd/da8/page_lib_stitch_doc.html#stitch_features", null ],
        [ "1.2 Image Stitching", "dd/da8/page_lib_stitch_doc.html#stitch_concept", null ],
        [ "1.3 Stitching without Alpha Blending", "dd/da8/page_lib_stitch_doc.html#stitch_solutions", null ],
        [ "1.4 Stitching with Alpha Blending", "dd/da8/page_lib_stitch_doc.html#stitch_blending_solution", [
          [ "1.4.1 Linear-Blending Stitching", "dd/da8/page_lib_stitch_doc.html#stitch_solutions_linear", null ],
          [ "1.4.2 Dynamic Seam Line Blending Stitching", "dd/da8/page_lib_stitch_doc.html#stitch_solutions_dyna", null ]
        ] ],
        [ "1.5 Stitching Result Comparison", "dd/da8/page_lib_stitch_doc.html#stitch_solutions_blend", null ]
      ] ],
      [ "2. Design", "dd/da8/page_lib_stitch_doc.html#stitch_design", [
        [ "2.1 Capture Device Structure", "dd/da8/page_lib_stitch_doc.html#stitch_cap", null ],
        [ "2.2 Software Structure", "dd/da8/page_lib_stitch_doc.html#stitch_soft", null ],
        [ "2.3  System Flow", "dd/da8/page_lib_stitch_doc.html#stitch_sys", null ],
        [ "2.4 Calibration Process", "dd/da8/page_lib_stitch_doc.html#stitch_calib", [
          [ "2.4.1 Lens Shading Calibration (on Host Windows Side)", "dd/da8/page_lib_stitch_doc.html#stitch_calib_lsc", null ],
          [ "2.4.2 Lens Calibration (on Host Windows Side)", "dd/da8/page_lib_stitch_doc.html#stitch_calib_lens", null ],
          [ "2.4.3 Stitch Pose Calibration (on Chip)", "dd/da8/page_lib_stitch_doc.html#stitch_calib_chip", null ],
          [ "2.4.4 Stitch Calibration Example", "dd/da8/page_lib_stitch_doc.html#stitch_calib_example", null ]
        ] ],
        [ "2.5 Stitching Process", "dd/da8/page_lib_stitch_doc.html#stitch_pro", [
          [ "2.5.1 Stitching Configration File Descriptions", "dd/da8/page_lib_stitch_doc.html#stitch_pro_parameters", null ],
          [ "2.5.2 Run Multi-channel Stitching Cases", "dd/da8/page_lib_stitch_doc.html#stitch_pro_pre", null ],
          [ "2.5.3 Stitch in Horizontal Direction", "dd/da8/page_lib_stitch_doc.html#stitch_pro_hor", null ],
          [ "2.5.4 Stitch in Vertical Direction on CV2x", "dd/da8/page_lib_stitch_doc.html#stitch_pro_ver", null ],
          [ "2.5.5 Stitch with Rotate Input on CV2x", "dd/da8/page_lib_stitch_doc.html#stitch_pro_rotate", null ],
          [ "2.5.6 Stitch with Rotated Channels on CV5x", "dd/da8/page_lib_stitch_doc.html#stitch_channel_rotate", null ],
          [ "2.5.7 Stitch with Six / Eight Channels on CV5x", "dd/da8/page_lib_stitch_doc.html#stitch_eight_channels_stitching", null ],
          [ "2.5.8 Stitch Digital Pan / Tilt / Zoom on CV2x", "dd/da8/page_lib_stitch_doc.html#stitch_pro_dptz", null ],
          [ "2.5.9 Stitch Skip Source Buffer Blend", "dd/da8/page_lib_stitch_doc.html#stitch_skip_blend", null ],
          [ "2.5.10 Stitch Privacy Mask", "dd/da8/page_lib_stitch_doc.html#stitch_insert_pm", null ],
          [ "2.5.11 Stitch Blur on CV5x / CV72", "dd/da8/page_lib_stitch_doc.html#stitch_insert_blur", null ],
          [ "2.5.12 Stitch Dual Fisheyes for 360-Degree Panorama", "dd/da8/page_lib_stitch_doc.html#stitch_pro_dual", null ],
          [ "2.5.13 Stitch-Backward / Forward Mapping", "dd/da8/page_lib_stitch_doc.html#stitch_backwarp_map", null ],
          [ "2.5.14 Stitch Simulation with EFM", "dd/da8/page_lib_stitch_doc.html#stitch_simulation_efm", null ],
          [ "2.5.15 Stitch with Users' Warp Table and Alpha Table", "dd/da8/page_lib_stitch_doc.html#stitch_user_warp_alpha", null ],
          [ "2.5.16 Stitch with Updating Warp Table on the Fly", "dd/da8/page_lib_stitch_doc.html#stitch_update_warp_table", null ],
          [ "2.5.17 Stitch Simulation with Pose Calibration Results", "dd/da8/page_lib_stitch_doc.html#stitch_simulate_with_pose_results", null ],
          [ "2.5.18 Stitch in Horizontal Direction with Angles below the Horizon", "dd/da8/page_lib_stitch_doc.html#stitch_pro_tilt", null ],
          [ "2.5.19 Stitch in Vertical-Horizontal-Vertical-Horizontal Direction with Angles below the Horizon", "dd/da8/page_lib_stitch_doc.html#stitch_pro_tilt_vhvh", null ]
        ] ]
      ] ],
      [ "3. Stitch Application Programming Interface", "dd/da8/page_lib_stitch_doc.html#sec_stitch_api", null ],
      [ "4. Stitch FAQ", "dd/da8/page_lib_stitch_doc.html#sec_stitch_faq", [
        [ "Question 1: How can green artifacts in the overlap area be avoided?", "dd/da8/page_lib_stitch_doc.html#sec_stitch_faq_q1", null ],
        [ "Question 2: When there are visible straight lines in sub-buffer stitching, but normal in main-buffer stitching, how can the lines be mitigated?", "dd/da8/page_lib_stitch_doc.html#sec_stitch_faq_q2", null ],
        [ "Question 3: How can artifacts in the horizontal and vertical directions after applying LDC be avoided?", "dd/da8/page_lib_stitch_doc.html#sec_stitch_faq_q3", null ],
        [ "Question 4: How is the warp table size reduced?", "dd/da8/page_lib_stitch_doc.html#sec_stitch_faq_q4", null ],
        [ "Question 5: How to capture images to avoid pose calibration fail?", "dd/da8/page_lib_stitch_doc.html#sec_stitch_faq_q5", null ],
        [ "Question 6: How is the shared ID chosen?", "dd/da8/page_lib_stitch_doc.html#sec_stitch_faq_q6", null ],
        [ "Question 7: How is calibration data made compatible with the new SDK version?", "dd/da8/page_lib_stitch_doc.html#sec_stitch_faq_q7", null ]
      ] ],
      [ "5. License", "dd/da8/page_lib_stitch_doc.html#sec_stitch_lic", null ]
    ] ],
    [ "VPROC Library API", "d1/d66/page_lib_vproc_doc.html", [
      [ "0. Revision History", "d1/d66/page_lib_vproc_doc.html#vproc_history", null ],
      [ "1. Introduction", "d1/d66/page_lib_vproc_doc.html#vproc_introduction", null ],
      [ "2. Example Usage", "d1/d66/page_lib_vproc_doc.html#vproc_library_example_usage", [
        [ "2.1 VProc Unit Test Application", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc", [
          [ "2.1.1 test_vproc_yuv2rgb", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_yuv2rgb", null ],
          [ "2.1.2 test_vproc_resize", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_resize", null ],
          [ "2.1.3 test_vproc_submean", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_submean", null ],
          [ "2.1.4 test_vproc_scale", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_scale", null ],
          [ "2.1.5 test_vproc_dtcvt", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_dtcvt", null ],
          [ "2.1.6 test_vproc_rotate", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_rotate", null ],
          [ "2.1.7 test_vproc_preproc", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_preproc", null ],
          [ "2.1.8 test_vproc_harris", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_harris", null ],
          [ "2.1.9 test_vproc_harris_live", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_harris_live", null ],
          [ "2.1.10 test_vproc_perspective", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_perspective", null ],
          [ "2.1.11 test_vproc_perspective_live", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_perspective_live", null ],
          [ "2.1.12 test_vproc_cdist", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_cdist", null ],
          [ "2.1.13 test_vproc_imhist", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_imhist", null ],
          [ "2.1.14 test_vproc_imcvt", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_imcvt", null ],
          [ "2.1.15 test_vproc_cvfilter", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_cvfilter", null ],
          [ "2.1.16 test_vproc_morph", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_morph", null ],
          [ "2.1.17 test_vproc_optlk", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_optlk", null ],
          [ "2.1.18 test_vproc_optlk_flow_live", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_optlk_flow_live", null ],
          [ "2.1.19 test_vproc_optlk_tracking_live", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_optlk_tracking_live", null ],
          [ "2.1.20 test_vproc_edge_det", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_edge_det", null ],
          [ "2.1.21 test_vproc_memcpy", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_memcpy", null ],
          [ "2.1.22 test_vproc_memset", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_memset", null ],
          [ "2.1.23 test_vproc_statistics", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_statistics", null ],
          [ "2.1.24 test_vproc_warp", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_warp", null ],
          [ "2.1.25 test_vproc_epnr", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_epnr", null ],
          [ "2.1.26 test_vproc_epnr_live", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_epnr_live", null ],
          [ "2.1.27 test_vproc_bayer2bgr", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_bayer2bgr", null ],
          [ "2.1.28 test_vproc_cclb", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_cclb", null ],
          [ "2.1.29 test_vproc_alpha_blend", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_alpha_blend", null ],
          [ "2.1.30 test_vproc_abs", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_abs", null ],
          [ "2.1.31 test_vproc_rgb2yuv", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_rgb2yuv", null ],
          [ "2.1.32 test_vproc_transpose", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_transpose", null ],
          [ "2.1.33 test_vproc_render3d_live", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_render3d", null ],
          [ "2.1.34 test_vproc_bitwise", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_bitwise", null ],
          [ "2.1.35 test_vproc_fbm", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_fbm", null ],
          [ "2.1.36 test_vproc_fbm_live", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_fbm_live", null ],
          [ "2.1.37 test_vproc_fbm_render_live", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_fbm_render_live", null ],
          [ "2.1.38 test_vproc_flatten", "d1/d66/page_lib_vproc_doc.html#vproc_library_test_vproc_flatten", null ]
        ] ]
      ] ],
      [ "3. VProc Performance", "d1/d66/page_lib_vproc_doc.html#sec_vproc", null ],
      [ "4. VProc API", "d1/d66/page_lib_vproc_doc.html#sec_vproc_api", null ],
      [ "5. License", "d1/d66/page_lib_vproc_doc.html#sec_vproc_lic", null ]
    ] ],
    [ "VFUNC Library API", "df/d36/page_lib_vfunc_doc.html", [
      [ "0. Revision History", "df/d36/page_lib_vfunc_doc.html#vfunc_history", null ],
      [ "1. Introduction", "df/d36/page_lib_vfunc_doc.html#vfunc_introduction", null ],
      [ "2. Example Usage", "df/d36/page_lib_vfunc_doc.html#vfunc_library_example_usage", [
        [ "2.1 VFunc Unit Test Application", "df/d36/page_lib_vfunc_doc.html#vfunc_library_test_vfunc", [
          [ "2.1.1 test_vfunc_fma", "df/d36/page_lib_vfunc_doc.html#vfunc_library_test_vfunc_fma", null ],
          [ "2.1.2 test_vfunc_fma_live", "df/d36/page_lib_vfunc_doc.html#vfunc_library_test_vfunc_fma_live", null ],
          [ "2.1.3 test_vfunc_ffpydlk_tracking", "df/d36/page_lib_vfunc_doc.html#vfunc_library_test_vfunc_ffpydlk_tracking", null ],
          [ "2.1.4 test_vfunc_ffpydlk_tracking_live", "df/d36/page_lib_vfunc_doc.html#vfunc_library_test_vfunc_ffpydlk_tracking_live", null ]
        ] ]
      ] ],
      [ "3. VFunc Performance", "df/d36/page_lib_vfunc_doc.html#sec_vfunc", null ],
      [ "4. VFunc API", "df/d36/page_lib_vfunc_doc.html#sec_vfunc_api", null ],
      [ "5. License", "df/d36/page_lib_vfunc_doc.html#sec_vfunc_lic", null ]
    ] ],
    [ "Video Sharing Service Library API", "df/d98/page_lib_vss_doc.html", [
      [ "0. Revision History", "df/d98/page_lib_vss_doc.html#vss_history", null ],
      [ "1. Video Sharing Service Introduction", "df/d98/page_lib_vss_doc.html#vss_intro", null ],
      [ "2. Video Sharing Service Library Application Programming Interface (API)", "df/d98/page_lib_vss_doc.html#vss_lib_api", null ],
      [ "3. VSS Usage", "df/d98/page_lib_vss_doc.html#vss_usage", null ],
      [ "4. Data Distribution Service Introduction", "df/d98/page_lib_vss_doc.html#dds_brief", null ],
      [ "5. License", "df/d98/page_lib_vss_doc.html#pm_license", null ]
    ] ],
    [ "PrivacyMask Library API", "d5/d2d/page_lib_pm_doc.html", [
      [ "0. Revision History", "d5/d2d/page_lib_pm_doc.html#privacymask_history", null ],
      [ "1. Introduction", "d5/d2d/page_lib_pm_doc.html#privacymask_intro", null ],
      [ "2. Privacy Mask Usage Guide", "d5/d2d/page_lib_pm_doc.html#pm_lib_process", null ],
      [ "3. Privacy Mask Examples", "d5/d2d/page_lib_pm_doc.html#pm_example", null ],
      [ "4. Privacy Mask Library API", "d5/d2d/page_lib_pm_doc.html#pm_lib_api", null ]
    ] ],
    [ "Vsrc Guard Library API", "dd/d44/page_lib_vg_doc.html", [
      [ "0. Revision History", "dd/d44/page_lib_vg_doc.html#vg_history", null ],
      [ "1. VSRC Guard Library", "dd/d44/page_lib_vg_doc.html#vg_lib", [
        [ "1.1 VSRC Guard Library Introduction", "dd/d44/page_lib_vg_doc.html#vg_intro", null ],
        [ "1.2 VSRC Guard Library Application Programming Interface (API)", "dd/d44/page_lib_vg_doc.html#vg_lib_api", null ],
        [ "1.3 VSRC Guard Library Usage", "dd/d44/page_lib_vg_doc.html#vg_lib_usage", null ]
      ] ],
      [ "2. VSRC Guard Service", "dd/d44/page_lib_vg_doc.html#vg_service", [
        [ "2.1 VSRC Guard Service Introduction", "dd/d44/page_lib_vg_doc.html#vg_service_intro", null ],
        [ "2.2 VSRC Guard Service Usage", "dd/d44/page_lib_vg_doc.html#vg_service_usage", null ],
        [ "2.3 VSRC Guard Service Application Notes", "dd/d44/page_lib_vg_doc.html#vg_service_effect", null ],
        [ "2.4 Example Cases", "dd/d44/page_lib_vg_doc.html#vg_service_case", null ]
      ] ],
      [ "3. License", "dd/d44/page_lib_vg_doc.html#vg_license", null ]
    ] ],
    [ "Modules", "modules.html", "modules" ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Structure Index", "classes.html", null ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
        [ "Functions", "functions_func.html", null ],
        [ "Variables", "functions_vars.html", "functions_vars" ]
      ] ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ],
      [ "Globals", "globals.html", [
        [ "All", "globals.html", "globals_dup" ],
        [ "Functions", "globals_func.html", "globals_func" ],
        [ "Variables", "globals_vars.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", "globals_enum" ],
        [ "Enumerator", "globals_eval.html", "globals_eval" ],
        [ "Macros", "globals_defs.html", "globals_defs" ]
      ] ]
    ] ],
    [ "Examples", "examples.html", "examples" ]
  ] ]
];

var NAVTREEINDEX =
[
"annotated.html",
"d0/d20/AmbaDSP__ImgFilter_8h.html#aac38a757356b629bb366083b95184221",
"d0/d7d/AmbaDSP__ImgUtility_8h.html#a9c17955c2945f529da0448dc6b7f32bf",
"d0/dae/structotp__query__setting.html#aa2b28a5b4f067415406ac2d006570a6f",
"d1/d1e/page_lib_sensor_calib_doc.html#sensor_calib_cfg",
"d1/d41/depth__sensing__framework_2include_2common__err__code__c_8h.html#af59884e0530cbb02c74dd0a7f6036e5c",
"d1/d7e/group__img__lib-helper.html#ga24a5d735fa623960692b61b3d068ae58",
"d1/d81/structiav__h26x__slice.html#a307e65ffd58b067088b9f00cbd9ca09c",
"d1/df3/structiav__stream__cfg.html#a7eb50103ead09f3fb04707fc18aaeada",
"d2/d21/structiav__decode__status.html#a8fe18adfb6ef5cb69382d7e16e59ba84",
"d2/d60/otp__ioctl_8h.html#af732bc91a6392cf87ad6f122b2b0a099",
"d2/dcb/structawb__lut__idx__t.html",
"d3/d0c/page_lib_eazyai_doc.html#eazyai_cvflow_accl_angle",
"d3/d1f/structdetection__result__t.html",
"d3/d5a/group__iav-common-helper.html#gga09812ec4ee4468ebaa0864878a08e2eaacc74a20d4e44c056577d46cd25093b51",
"d3/d5a/group__iav-common-helper.html#ggaf59c3be8ead49fdc339e6ea0d09e3d8faa7c3f8e0b5ebc820bba4bed0d144e7d6",
"d3/d98/video__sharing__service_2include_2common__err__code__c_8h.html#ad3f7930a252136572e4209cd2a201c0d",
"d3/de3/group__iav-ioctl-general-helper.html#ga87c667ac915349fb58b7c9e065b6e248",
"d3/de3/group__iav-ioctl-general-helper.html#gga3606b35b652dca594dc455dfb0b9f172ab234c23d693d9123f8161dfd92315dc8",
"d3/de3/group__iav-ioctl-general-helper.html#gga795e36150507895033cdb97b40e6b1b8ab7c490d65b46b0e5cfd367274191b0cf",
"d3/de3/group__iav-ioctl-general-helper.html#ggaf270e2154242c10302df5fca9c62b356ac3e976442b8f52eeb3d5f5f53087824b",
"d4/d47/group__iav-ioctl-vin-struct.html#gga2b322997779cb5e7aa4394545ed51e2daee023b527b13ebc54f377f79cd80522a",
"d4/d91/amba__netlink_8h.html#a8a7576722b95f6047d276f3909d84c49a95b348114925c1c7c9f1a4cc7ee86f6a",
"d4/ddb/structiav__driver__dsp__info.html#a43b587617e69791758821fea5ae9c9fa",
"d5/d12/page_lib_gstreamer_doc.html#element_amba_mlinference",
"d5/d5f/structiav__enc__buf__cap.html#a2830ebfe6ef0797f46e9fcc1945f4c01",
"d5/dec/structpyramid__publish__cfg__list__t.html",
"d6/d46/structiav__privacy__mask.html#a7f0c82e1f055e95da8a702634c3e56b0",
"d6/da8/group__iav-ioctl-vout-helper.html",
"d6/db6/page_lib_eis_doc.html#eis_enc",
"d7/d23/structdsf__buffer__t.html#a33abd4d4ca364cebef608725d7c3882b",
"d7/db6/structsmartrc__profile__thres__t.html",
"d8/d29/structimg__cal__ca__cfg__t.html#a572cf44fe11e9e664fca04b6a672ed72",
"d8/d89/lib__pm__priv_8h.html#a90d77adb23ff0bf504385677014d7cd9af1331e29f4d5652271a46e061ef18bef",
"d8/d8c/group__iav-ioctl-vin-helper.html#ggabe47c58eecc0d607bd1f67835c9bc18aa794653bae862d115aee02b834f66ddb5",
"d8/dc4/group__iav-ioc-enc-use-sys.html#gae6895f70e85c2580ff95c0cdb0337046",
"d9/d2b/structiav__framedesc.html#a4e04f3eb60d24e83a45c6bbbc1ced648",
"d9/d65/group__VSRC__GUARD__ENUM__GROUP.html#gga34b63206a005b0ab0ee4f426063a4f3aa09bfdb27cd4ab6642cdab78a7f4af3ed",
"d9/d8d/group__srcv3-general-helper.html#ggaa162da38bd1d097f8865ac95341dffaaa5b76dd51db62558b1952158ba38b723f",
"d9/dc1/group__img__lib-high-level-api-details.html#ga2b99e331785eef2e2c3846c955fadaf5",
"da/d16/structvindev__video__format.html",
"da/d8b/page_lib_dewarp_doc.html#ceiling_desktop_panorama_fulframe",
"da/db1/AmbaDSP__Img3astatistic_8h.html#a5abf10a2519b367ef25e8cde3c8413d6",
"db/d15/group__srcv3-helper.html",
"db/d7d/nn__arm__result_8h.html#a89613c5e136ffeee9b96d0bed449bfee",
"db/dc2/iav__netlink_8h.html#aa28db1322165f8b401c1bfa121ec187ea7e75ef0f9769276976b13aef9a0ff65f",
"dc/d21/page_lib_cavalry_opt_layers_doc.html",
"dc/d70/page_lib_src_v3.html#srcv3_exp_apply_cv_output_with_non_frame_sync",
"dc/dc8/structcvker__mfd__t.html#a953d14da18626985b8b0046baf76fbf5",
"dd/d3f/struct____attribute____.html#ac2f70ae69681fd5cfb5bccb9002c9678",
"dd/d59/structfilter__container__pkg__t.html#a22b046d01bcda025c6b090988ba2c2ed",
"dd/da0/structdsf__option__t.html#a3c013e90a581efe82c820f0a52f3a30c",
"dd/dfe/structpolish__extra__t.html#a1d28dec57cce925ad92342891bd71e7c",
"de/d22/group__iav-ioctl-dec-helper.html#gga4d802348aef9a034f8ac00cd8fdcf7bfa0faa57ce9f9f2f1f3fb8c14ee4547f9f",
"de/d6e/structik__cfa__noise__filter__t.html#a76379881bae5f15346c7589025355690",
"de/dc6/structik__chroma__median__filter__t.html#a854b76bf6521b21b287476a25324ebd4",
"df/d14/structdsi__to__depth__cfg__t.html",
"df/d39/group__img__flow-api-details.html#ga9c98bd82d155158e825a63e638759279",
"df/d58/page_lib_depth_fw_doc.html#sec_depth_lic",
"df/dc6/structea__osd__refresh__efm__params__s.html#ada5871d266c274600f72d5331ad1068f",
"dir_a4f88cb0e4eb8e91da60d2b29a644423.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';