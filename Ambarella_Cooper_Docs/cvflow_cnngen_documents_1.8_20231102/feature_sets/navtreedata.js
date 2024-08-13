/*
@licstart  The following is the entire license notice for the
JavaScript code in this file.

Copyright (C) 1997-2019 by Dimitri van Heesch

This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as published by
the Free Software Foundation

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

@licend  The above is the entire license notice
for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "CNNGen Development", "index.html", [
    [ "Overview", "d9/d7e/fs_ov.html", [
      [ "1 CVflow Gen2 for CV2x & CV5x", "d9/d7e/fs_ov.html#sec_ov_intro_gen2", null ],
      [ "2 CVflow Gen3 for CV72", "d9/d7e/fs_ov.html#sec_ov_intro_gen3", null ]
    ] ],
    [ "Work Flow", "d1/d82/fs_workflow.html", [
      [ "1 Network and Framework Selection", "d1/d82/fs_workflow.html#sec_pre_cnn_model", [
        [ "1.1 Network Selection", "d1/d82/fs_workflow.html#sub_sec_network_selection", null ],
        [ "1.2 Frameworks Selection", "d1/d82/fs_workflow.html#sub_sec_framework_support", null ],
        [ "1.3 Retrain Related Frameworks", "d1/d82/fs_workflow.html#sub_sec_framework_retrain", null ]
      ] ],
      [ "2 Network Optimization", "d1/d82/fs_workflow.html#sec_model_opt", [
        [ "2.1 Pruning", "d1/d82/fs_workflow.html#sub_sec_1_model_prune", null ],
        [ "2.2 Quantization", "d1/d82/fs_workflow.html#sub_sec_model_quant", null ]
      ] ],
      [ "3 Converter", "d1/d82/fs_workflow.html#sec_port_procedure", [
        [ "3.1 Dynamic Range Analysis(DRA)", "d1/d82/fs_workflow.html#sub_sec_dra", null ],
        [ "3.2 Basic Accuracy Evaluation", "d1/d82/fs_workflow.html#sub_sec_accuracy_debug", null ]
      ] ],
      [ "4 Accuracy Evaluation", "d1/d82/fs_workflow.html#fs_accuracy_tool_test", [
        [ "4.1 Workflow", "d1/d82/fs_workflow.html#sec_accuracy_workflow", null ],
        [ "4.2 Run steps", "d1/d82/fs_workflow.html#sec_accuracy_run_steps", [
          [ "4.2.1 Build the SDK", "d1/d82/fs_workflow.html#sub_sec_accuracy_build_the_SDK", null ],
          [ "4.2.2 Environment Configuration", "d1/d82/fs_workflow.html#sub_sec_accuracy_env_config", null ],
          [ "4.2.3 Download the Test Dataset", "d1/d82/fs_workflow.html#sub_sec_accuracy_download_dataset", null ],
          [ "4.2.4 Convert With CNNGen toolchain", "d1/d82/fs_workflow.html#sub_sec_accuracy_convert_network", null ],
          [ "4.2.5 Inference and Evaluation", "d1/d82/fs_workflow.html#sub_sec_accuracy_execution", null ]
        ] ],
        [ "4.3 Usage Demonstration", "d1/d82/fs_workflow.html#sec_accuarcy_usage", null ],
        [ "4.4 Some Important Notes", "d1/d82/fs_workflow.html#sec_accuarcy_notice", [
          [ "4.4.1 Replace Data Prepare Module", "d1/d82/fs_workflow.html#sub_sec_accuracy_replace_data_prepare", null ],
          [ "4.4.2 Replace Post Processing Module", "d1/d82/fs_workflow.html#sub_sec_accuracy_replace_post-processing", null ]
        ] ],
        [ "4.5 FAQ", "d1/d82/fs_workflow.html#sec_accuarcy_FAQ", null ]
      ] ],
      [ "5 Deployment", "d1/d82/fs_workflow.html#sec_deploy_nn", null ],
      [ "6 Performance Table", "d1/d82/fs_workflow.html#sec_sample_perf", null ],
      [ "7 Accuracy Table", "d1/d82/fs_workflow.html#sec_accuarcy_table", null ]
    ] ],
    [ "Quick Start", "da/dc5/fs_quick_start.html", [
      [ "1 Prepare", "da/dc5/fs_quick_start.html#sec_qs_prepare", [
        [ "1.1 Packages", "da/dc5/fs_quick_start.html#sub_qs_pre_package", null ],
        [ "1.2 HW", "da/dc5/fs_quick_start.html#sub_qs_pre_hw", null ],
        [ "1.3 Installation", "da/dc5/fs_quick_start.html#sub_qs_pre_install", null ],
        [ "1.4 Download Models", "da/dc5/fs_quick_start.html#sub_qs_pre_dm", null ],
        [ "1.5 EVK Connection", "da/dc5/fs_quick_start.html#sub_qs_pre_evk_conn", null ],
        [ "1.6 Reference Materials", "da/dc5/fs_quick_start.html#sub_qs_pre_ref_files", null ]
      ] ],
      [ "2 Live Demos", "da/dc5/fs_quick_start.html#sec_qs_live_demos", null ],
      [ "3 EazyAI CFlite Python Tools", "da/dc5/fs_quick_start.html#sec_eazyai_gsg", [
        [ "3.1 Quick Performance Evaluation", "da/dc5/fs_quick_start.html#subsec_eazyai_gsg_perf", null ],
        [ "3.2 Basic Accuracy Evaluation", "da/dc5/fs_quick_start.html#subsec_eazyai_gsg_basic_acc", null ],
        [ "3.3 Full Accuracy Evaluation", "da/dc5/fs_quick_start.html#subsec_eazyai_gsg_full_acc", null ],
        [ "3.4 Efficiency Evaluation", "da/dc5/fs_quick_start.html#subsec_eazyai_gsg_efe", null ],
        [ "3.5 Product Deployment", "da/dc5/fs_quick_start.html#subsec_eazyai_gsg_mp", null ]
      ] ],
      [ "4 CNNGUI", "da/dc5/fs_quick_start.html#sec_cnngui", [
        [ "4.1 Environment Setting", "da/dc5/fs_quick_start.html#sub_sec_cnngui_env_setting", null ],
        [ "4.2 How To Use", "da/dc5/fs_quick_start.html#sub_sec_cnngui_usage", null ],
        [ "4.3 Choose Model Page", "da/dc5/fs_quick_start.html#sub_sec_cnngui_model_page", null ],
        [ "4.4 Port Information Page", "da/dc5/fs_quick_start.html#sub_sec_cnngui_port_page", null ],
        [ "4.5 Convert Model Page", "da/dc5/fs_quick_start.html#sub_sec_cnngui_convert_page", null ],
        [ "4.6 Simulation Tools page", "da/dc5/fs_quick_start.html#sub_sec_cnngui_simulation_page", null ],
        [ "4.7 Deploy Model Page", "da/dc5/fs_quick_start.html#sub_sec_cnngui_deploy_page", null ],
        [ "4.8 Accuracy Tools page", "da/dc5/fs_quick_start.html#sub_sec_cnngui_accuracy_page", null ],
        [ "4.9 Import Config and Export Config buttons", "da/dc5/fs_quick_start.html#sub_sec_cnngui_config_page", null ]
      ] ],
      [ "5 Quick Shell Script", "da/dc5/fs_quick_start.html#sec_quick_start", [
        [ "5.1 Normal Method", "da/dc5/fs_quick_start.html#sec_quick_start_parser", null ],
        [ "5.2 CVFlowBackend", "da/dc5/fs_quick_start.html#sec_quick_start_cvb", null ]
      ] ],
      [ "6 Simple Tools", "da/dc5/fs_quick_start.html#sec_simple_tools", [
        [ "6.1 im2bin", "da/dc5/fs_quick_start.html#sub_sec_sample_tool_imx2bin", null ],
        [ "6.2 bin2val", "da/dc5/fs_quick_start.html#sub_sec_sample_tool_bin2val", null ],
        [ "6.3 bincmp", "da/dc5/fs_quick_start.html#sub_sec_sample_tool_bincmp", null ],
        [ "6.4 get_mean", "da/dc5/fs_quick_start.html#sub_sec_sample_tool_get_mean", null ],
        [ "6.5 fp32_2_fp16_convert", "da/dc5/fs_quick_start.html#sub_sec_sample_tool_fp32_to_fp16", null ],
        [ "6.6 gen_fp16_mean", "da/dc5/fs_quick_start.html#sub_sec_sample_tool_gen_fp16_mean", null ],
        [ "6.7 cvflow_perf_eval.py", "da/dc5/fs_quick_start.html#sub_sec_cvflow_perf_eval", null ]
      ] ]
    ] ],
    [ "EazyAI Framework", "dd/de5/fs_eazyai.html", [
      [ "1 EazyAI CVflow Lite Python Library", "dd/de5/fs_eazyai.html#sec_eazyai_cflite", null ],
      [ "2 EazyAI Python Tools", "dd/de5/fs_eazyai.html#sec_eazyai_python_tools", [
        [ "2.1 EazyAI Helper Tool", "dd/de5/fs_eazyai.html#subsec_eazyai_python_tools_helper", null ],
        [ "2.2 EazyAI Configuration Tool", "dd/de5/fs_eazyai.html#subsec_eazyai_python_tools_cfg", [
          [ "2.2.1 Basic Convert Parameters", "dd/de5/fs_eazyai.html#subsubsec_eazyai_python_tools_cfg_basic", null ],
          [ "2.2.2 Full Convert Parameters", "dd/de5/fs_eazyai.html#subsubsec_eazyai_python_tools_cfg_adv", null ],
          [ "2.2.3 Convert Parameters Without Comments", "dd/de5/fs_eazyai.html#subsubsec_eazyai_python_tools_cfg_comment", null ]
        ] ],
        [ "2.3 EazyAI Convert Tool", "dd/de5/fs_eazyai.html#subsec_eazyai_python_tools_cvt", null ],
        [ "2.4 EazyAI Inference Tool", "dd/de5/fs_eazyai.html#subsec_eazyai_python_tools_inf", [
          [ "2.4.1 Inference Yaml File", "dd/de5/fs_eazyai.html#ssubsec_eazyai_python_tools_inf_yaml", null ],
          [ "2.4.2 Enbale GPU For Simulator", "dd/de5/fs_eazyai.html#ssubsec_eazyai_python_tools_inf_gpu", null ]
        ] ],
        [ "2.5 CVflow Simple Inference Tool", "dd/de5/fs_eazyai.html#subsec_eazyai_python_tools_cvflow_inf", null ],
        [ "2.6 Video Control Tool", "dd/de5/fs_eazyai.html#subsec_eazyai_python_tools_video", null ],
        [ "2.7 CVflow Layer Profiler Tool", "dd/de5/fs_eazyai.html#subsec_eazyai_python_tools_profiler", null ],
        [ "2.8 Simple PyTools", "dd/de5/fs_eazyai.html#subsec_eazyai_python_tools_simple", null ]
      ] ],
      [ "3 Eazyai Video", "dd/de5/fs_eazyai.html#sec_eazyai_vi_sh", null ],
      [ "4 EazyAI Inference C Library", "dd/de5/fs_eazyai.html#sec_eazyai_deploy_c_library", null ],
      [ "5 EazyAI Postprocess C Library", "dd/de5/fs_eazyai.html#sec_eazyai_cpu_postproc", null ],
      [ "6 EazyAI Unit Test", "dd/de5/fs_eazyai.html#sec_eazyai_unit_test", null ],
      [ "7 EazyAI Live Application", "dd/de5/fs_eazyai.html#sec_eazyai_live_application", null ]
    ] ],
    [ "Deployment", "d7/d53/fs_deployment.html", [
      [ "1 Prepare the Binary", "d7/d53/fs_deployment.html#sec_deploy_evk_binary", [
        [ "1.1 Full Software Development Kit (SDK)", "d7/d53/fs_deployment.html#sub_sec_deploy_full_sdk", null ],
        [ "1.2 Evaluation Software Development Kit (SDK)", "d7/d53/fs_deployment.html#sub_sec_deploy_eva_sdk", null ]
      ] ],
      [ "2 Applications", "d7/d53/fs_deployment.html#sec_deploy_applications", [
        [ "2.1 Location", "d7/d53/fs_deployment.html#sub_sec_deploy_app_location", null ],
        [ "2.2 File Mode", "d7/d53/fs_deployment.html#sub_sec_deploy_file_mode", [
          [ "2.2.1 Prepare a Test Input with Image", "d7/d53/fs_deployment.html#subb_sec_deploy_in_file", null ],
          [ "2.2.2 Prepare Test Input with Sensor", "d7/d53/fs_deployment.html#subb_sec_deploy_in_live", null ],
          [ "2.2.3 Run Inference Test", "d7/d53/fs_deployment.html#subb_sec_deploy_run_inference", null ]
        ] ],
        [ "2.3 Live Mode", "d7/d53/fs_deployment.html#sub_sec_deploy_live_mode", [
          [ "2.3.1 Calling Sequence", "d7/d53/fs_deployment.html#subb_sec_deploy_call_seq", null ],
          [ "2.3.2 test_nnctrl_live", "d7/d53/fs_deployment.html#subb_sec_deploy_test_nnctrl_live", null ],
          [ "2.3.3 test_eazyai", "d7/d53/fs_deployment.html#subb_sec_deploy_test_eazyai", null ],
          [ "2.3.4 PVANET Application", "d7/d53/fs_deployment.html#subb_sec_deploy_pvanet_app", null ]
        ] ],
        [ "2.4 Add New Network", "d7/d53/fs_deployment.html#sub_sec_deploy_easy_add", null ]
      ] ],
      [ "3 Libraries", "d7/d53/fs_deployment.html#sec_deploy_libraries", [
        [ "3.1 Vproc Library", "d7/d53/fs_deployment.html#sub_sec_deploy_vproc", null ],
        [ "3.2 NNCtrl Library", "d7/d53/fs_deployment.html#sub_sec_deploy_nnctrl", null ],
        [ "3.3 EazyAI Library", "d7/d53/fs_deployment.html#sub_sec_deploy_eazyai", null ]
      ] ],
      [ "4 Input Process", "d7/d53/fs_deployment.html#sec_deploy_input_process", [
        [ "4.1 Rotate", "d7/d53/fs_deployment.html#sub_sec_deploy_input_process_rotate", null ],
        [ "4.2 Convert YUV to RGB", "d7/d53/fs_deployment.html#sub_sec_deploy_input_process_convert_yuv2rgb", null ]
      ] ],
      [ "5 Output Process", "d7/d53/fs_deployment.html#sec_deploy_out_process", [
        [ "5.1 Random", "d7/d53/fs_deployment.html#sub_sec_deploy_out_random", null ],
        [ "5.2 Mandatory", "d7/d53/fs_deployment.html#sub_sec_deploy_out_mandatory", null ],
        [ "5.3 Alignment", "d7/d53/fs_deployment.html#sub_sec_deploy_out_align", null ]
      ] ],
      [ "6 Cavalry DRAM", "d7/d53/fs_deployment.html#sec_deploy_cavalry_dram", [
        [ "6.1 AMA", "d7/d53/fs_deployment.html#sub_sec_deploy_cavalry_ama", null ],
        [ "6.2 Network Cost", "d7/d53/fs_deployment.html#sub_sec_deploy_cma_nn_cost", null ],
        [ "6.3 CMA Allocate Fail", "d7/d53/fs_deployment.html#sub_sec_deploy_cma_alloc", null ],
        [ "6.4 Cache", "d7/d53/fs_deployment.html#sub_sec_deploy_cache", null ],
        [ "6.5 DVI Memory Protection", "d7/d53/fs_deployment.html#sub_sec_deploy_mprotect", null ],
        [ "6.6 CV2 High Address DRAM", "d7/d53/fs_deployment.html#sub_sec_deploy_cv2_high_addr_dram", null ],
        [ "6.7 Print Cavalry Memory Summary", "d7/d53/fs_deployment.html#sub_sec_deploy_show_cavalry_cma", null ],
        [ "6.8 Auto Recycle", "d7/d53/fs_deployment.html#sub_sec_deploy_show_cavalry_auto_recycle", null ],
        [ "6.9 CV5x DRAM Limitation", "d7/d53/fs_deployment.html#sub_sec_deploy_cv5x_dram_limitation", null ],
        [ "6.10 Network Bandwidth", "d7/d53/fs_deployment.html#sub_sec_deploy_nn_bw", null ]
      ] ],
      [ "7 Performance Optimization", "d7/d53/fs_deployment.html#sec_deploy_perf_opt", [
        [ "7.1 Memory Copy", "d7/d53/fs_deployment.html#sub_sec_deploy_mem_cp", null ],
        [ "7.2 Batch for Vproc and NNCtrl", "d7/d53/fs_deployment.html#sub_sec_deploy_batch", null ],
        [ "7.3 Crop and Resize", "d7/d53/fs_deployment.html#sub_sec_deploy_reszie_crop", null ],
        [ "7.4 OpenMP for Post Processing", "d7/d53/fs_deployment.html#sub_sec_deploy_openmp", null ]
      ] ],
      [ "8 Show the Result", "d7/d53/fs_deployment.html#sec_deploy_show_result", [
        [ "8.1 Frame Buffer on VOUT", "d7/d53/fs_deployment.html#sub_sec_deploy_fb_vout", null ],
        [ "8.2 Blur on Stream", "d7/d53/fs_deployment.html#sub_sec_deploy_blur", null ]
      ] ],
      [ "9 VP Hang Debug", "d7/d53/fs_deployment.html#sec_deploy_vp_hang", [
        [ "9.1 Cavalry Log", "d7/d53/fs_deployment.html#sub_sec_deploy_cavalry_log", null ],
        [ "9.2 VAS Problems", "d7/d53/fs_deployment.html#sub_sec_deploy_vas_problem", null ],
        [ "9.3 DRAM Problems", "d7/d53/fs_deployment.html#sub_sec_deploy_dram_problem", null ],
        [ "9.4 DAG Check in DRAM", "d7/d53/fs_deployment.html#sub_sec_deploy_dag_check", null ]
      ] ],
      [ "10 Compatibility", "d7/d53/fs_deployment.html#sec_deploy_compatibility", [
        [ "10.1 Primitive Code", "d7/d53/fs_deployment.html#sub_sec_deploy_primitive_code", null ],
        [ "10.2 VAS", "d7/d53/fs_deployment.html#sub_sec_deploy_vas", null ],
        [ "10.3 SDK API", "d7/d53/fs_deployment.html#sub_sec_deploy_sdk_api", null ],
        [ "10.4 CV72 Limitation", "d7/d53/fs_deployment.html#sub_sec_deploy_cv72_limit", null ]
      ] ],
      [ "11 NN Model Protection", "d7/d53/fs_deployment.html#sec_deploy_nn_protect", null ],
      [ "12 Unit License Protection", "d7/d53/fs_deployment.html#sec_deploy_per_unit", null ],
      [ "13 VP Task Priority", "d7/d53/fs_deployment.html#sec_deploy_task_priority", [
        [ "13.1 Manually Resume", "d7/d53/fs_deployment.html#sub_sec_deploy_manual_resume", null ],
        [ "13.2 How to Handle Big DAG", "d7/d53/fs_deployment.html#sub_sec_deploy_big_dag", null ]
      ] ],
      [ "14 Eazyai Video", "d7/d53/fs_deployment.html#sec_deploy_eazyai_video", null ],
      [ "15 HDMI YUV Input", "d7/d53/fs_deployment.html#sec_deploy_yuv_input", null ],
      [ "16 Cavalry Profiler", "d7/d53/fs_deployment.html#sec_deploy_cavalry_profiler", null ],
      [ "17 VP Reload and Clock Modification", "d7/d53/fs_deployment.html#sec_deploy_vp_clock", null ],
      [ "18 VProc Performance", "d7/d53/fs_deployment.html#sec_deploy_vproc_perf", null ],
      [ "19 DRAM Bandwidth Statistics", "d7/d53/fs_deployment.html#sec_deploy_dram_bw_stat", null ]
    ] ],
    [ "CNNGen Toolkits", "d2/d67/fs_cnngen.html", [
      [ "1 Interface", "d2/d67/fs_cnngen.html#sec_cnngen_interface", null ],
      [ "2 Installation", "d2/d67/fs_cnngen.html#sec_cnngen_install", null ],
      [ "3 Environment Setting", "d2/d67/fs_cnngen.html#sec_cnngen_env_set", null ],
      [ "4 Data Format", "d2/d67/fs_cnngen.html#sec_data_format", [
        [ "4.1 Input Data Format", "d2/d67/fs_cnngen.html#sub_sec_in_data_format", null ]
      ] ],
      [ "5 DRA List Generation", "d2/d67/fs_cnngen.html#sec_dra_list_gen", null ],
      [ "6 Parsers", "d2/d67/fs_cnngen.html#sec_cnngen_parser", [
        [ "6.1 DRA Version History", "d2/d67/fs_cnngen.html#sub_sec_dra_ver_history", null ]
      ] ],
      [ "7 Caffe Parser", "d2/d67/fs_cnngen.html#sec_cnngen_caffe_parser", null ],
      [ "8 TensorFlow Parser", "d2/d67/fs_cnngen.html#sec_cnngen_tf_parser", [
        [ "8.1 Known Error in checkpoint_to_pb.py", "d2/d67/fs_cnngen.html#sub_sec_tf_known_error", null ],
        [ "8.2 Input Transpose", "d2/d67/fs_cnngen.html#sub_sec_tf_in_tranpose", null ],
        [ "8.3 TFlite", "d2/d67/fs_cnngen.html#sub_sec_tflite", null ],
        [ "8.4 NCHW Model", "d2/d67/fs_cnngen.html#sub_sec_tf_nchw", null ],
        [ "8.5 Tensorflow 2.x", "d2/d67/fs_cnngen.html#sub_sec_tf_2x", null ]
      ] ],
      [ "9 Onnx Parser", "d2/d67/fs_cnngen.html#sec_cnngen_onnx_parser", null ],
      [ "10 x86 Simulator", "d2/d67/fs_cnngen.html#sec_cnngen_x86_simulator", [
        [ "10.1 EazayAI", "d2/d67/fs_cnngen.html#sub_sec_cnngen_eazyai", null ],
        [ "10.2 Acinference", "d2/d67/fs_cnngen.html#sub_sec_cnngen_acinf", [
          [ "10.2.1 Acinference Binary", "d2/d67/fs_cnngen.html#ssub_sec_acinf_binary", null ],
          [ "10.2.2 Acinference Library", "d2/d67/fs_cnngen.html#ssub_sec_acinf_library", null ],
          [ "10.2.3 Enable GPU", "d2/d67/fs_cnngen.html#ssub_sec_acinf_gpu", null ],
          [ "10.2.4 Quantization Inference Library Sample", "d2/d67/fs_cnngen.html#sec_sample_quant", null ]
        ] ],
        [ "10.3 Ades", "d2/d67/fs_cnngen.html#sub_sec_cnngen_ades", [
          [ "10.3.1 ADES Binary", "d2/d67/fs_cnngen.html#ssub_sec_ades_binary", null ],
          [ "10.3.2 ADES Library", "d2/d67/fs_cnngen.html#ssub_sec_ades_library", null ],
          [ "10.3.3 Enable GPU", "d2/d67/fs_cnngen.html#ssub_sec_ades_gpu", null ],
          [ "10.3.4 Ades Library Sample", "d2/d67/fs_cnngen.html#sec_sample_ades", null ]
        ] ]
      ] ],
      [ "11 Cavalry_gen", "d2/d67/fs_cnngen.html#sec_cnngen_cavalry_gen", [
        [ "11.1 Compatibility", "d2/d67/fs_cnngen.html#sub_sec_cavalry_compatibility", null ],
        [ "11.2 Convert Between Different Versions", "d2/d67/fs_cnngen.html#sub_cnngen_cavalry_versions_convert", null ],
        [ "11.3 Mismatch Between SDK And Cavalry_gen", "d2/d67/fs_cnngen.html#sub_cnngen_cavalry_versions_mismatch", null ]
      ] ],
      [ "12 layer_compare.py", "d2/d67/fs_cnngen.html#sec_cnngen_layer_comapre", null ],
      [ "13 Pre-Process Model Tools", "d2/d67/fs_cnngen.html#sec_cnngen_preprocess_tools", [
        [ "13.1 Print Summary", "d2/d67/fs_cnngen.html#sub_sec_print_summary", null ],
        [ "13.2 Graph Surgery", "d2/d67/fs_cnngen.html#sub_sec_graph_surgery", null ],
        [ "13.3 Replace Subgraph", "d2/d67/fs_cnngen.html#sub_sec_replace_subgraph", null ],
        [ "13.4 Register Custom Operator", "d2/d67/fs_cnngen.html#sub_sec_register_custom_operator", null ]
      ] ],
      [ "14 eval_surgery.py", "d2/d67/fs_cnngen.html#sec_cnngen_eval_surgey", null ],
      [ "15 Supplementary Documents", "d2/d67/fs_cnngen.html#sec_cnngen_supplementary_docs", [
        [ "15.1 UG CNNGen User Guide", "d2/d67/fs_cnngen.html#sub_sec_cnngen_ug_cnn", null ],
        [ "15.2 API CNNGen Python Application Programming Interface", "d2/d67/fs_cnngen.html#sub_sec_cnngen_python_api", null ],
        [ "15.3 UG Tools", "d2/d67/fs_cnngen.html#sub_sec_cnngen_ug_tools", null ],
        [ "15.4 UG Dynamic Range Analysis", "d2/d67/fs_cnngen.html#sub_sec_cnngen_ug_dra", null ],
        [ "15.5 Linux SDK CVflow FAQ", "d2/d67/fs_cnngen.html#sub_sec_cnngen_sdk_faq", null ]
      ] ],
      [ "16 External Tools", "d2/d67/fs_cnngen.html#sec_cnngen_ecternal_tools", [
        [ "16.1 cv_f2vp_convert", "d2/d67/fs_cnngen.html#sub_sec_cnngen_cv_f2vp_convert", null ],
        [ "16.2 keras_converter", "d2/d67/fs_cnngen.html#sub_sec_cnngen_keras_converter", null ],
        [ "16.3 torch2onnx", "d2/d67/fs_cnngen.html#sub_sec_cnngen_torch_converter", null ]
      ] ],
      [ "17 Pruning Test Tools", "d2/d67/fs_cnngen.html#sec_cnngen_pruning_tool", null ],
      [ "18 CVflow Layer Profiler", "d2/d67/fs_cnngen.html#sec_cnngen_cvflow_layer_profiler", null ],
      [ "19 CVFlowBackend", "d2/d67/fs_cnngen.html#sec_cnngen_cvflowbackend", null ],
      [ "20 Custom Node", "d2/d67/fs_cnngen.html#fs_custom_node", [
        [ "20.1 Introduction", "d2/d67/fs_cnngen.html#sec_custom_introduction", [
          [ "20.1.1 Defining the Custom Node", "d2/d67/fs_cnngen.html#sub_sec_custom_define", null ],
          [ "20.1.2 Workflow", "d2/d67/fs_cnngen.html#sub_sec_custom_workflow", null ],
          [ "20.1.3 Usage", "d2/d67/fs_cnngen.html#sub_sec_custom_usage", null ]
        ] ],
        [ "20.2 Special APIs", "d2/d67/fs_cnngen.html#sec_custom_spec_apis", [
          [ "20.2.1 init() Function", "d2/d67/fs_cnngen.html#sub_sec_custom_api_init", [
            [ "Example 1: Two Algorithms in Dependence", "dd/de5/fs_eazyai.html#autotoc_md16", null ],
            [ "Example 2: Two Independent Algorithms", "dd/de5/fs_eazyai.html#autotoc_md17", null ],
            [ "Data Format", "d7/d53/fs_deployment.html#autotoc_md26", null ],
            [ "Data Dimension", "d7/d53/fs_deployment.html#autotoc_md27", null ],
            [ "Example: Place DVI and blob memory to high address", "d7/d53/fs_deployment.html#autotoc_md29", null ],
            [ "Example 1. On the CV22 board, the commands below show chip versions in NET.bin.", "d7/d53/fs_deployment.html#autotoc_md34", null ],
            [ "Example 2. On the CV22 board, the commands below report error messages when running CV2 NET.bin", "d7/d53/fs_deployment.html#autotoc_md35", null ],
            [ "Example 3. On the CV22 board, the commands below can force bypass chip check.", "d7/d53/fs_deployment.html#autotoc_md36", null ],
            [ "Example 1: Convert images to binaries and generate the DRA list.", "d2/d67/fs_cnngen.html#autotoc_md50", null ],
            [ "Examples 2: Generate the DRA list with binary.", "d2/d67/fs_cnngen.html#autotoc_md51", null ],
            [ "Example 1: load the MaxPooling2D in CPU.", "d2/d67/fs_cnngen.html#autotoc_md55", null ],
            [ "Example 2: tf_print_graph_summay.py will show the recommendation below for NCHW model.", "d2/d67/fs_cnngen.html#autotoc_md56", null ],
            [ "Example 3: error in tfparser.py.", "d2/d67/fs_cnngen.html#autotoc_md57", null ],
            [ "Function Prototype:", "d2/d67/fs_cnngen.html#autotoc_md68", null ],
            [ "Parameters:", "d2/d67/fs_cnngen.html#autotoc_md69", null ],
            [ "Returns:", "d2/d67/fs_cnngen.html#autotoc_md70", null ],
            [ "Example:", "d2/d67/fs_cnngen.html#autotoc_md71", null ]
          ] ],
          [ "20.2.2 expand() Function", "d2/d67/fs_cnngen.html#sub_sec_custom_api_expand", [
            [ "Function Prototype:", "d2/d67/fs_cnngen.html#autotoc_md72", null ],
            [ "Parameters:", "d2/d67/fs_cnngen.html#autotoc_md73", null ],
            [ "Returns:", "d2/d67/fs_cnngen.html#autotoc_md74", null ],
            [ "Example:", "d2/d67/fs_cnngen.html#autotoc_md75", null ]
          ] ],
          [ "20.2.3 release() Function", "d2/d67/fs_cnngen.html#sub_sec_custom_api_release", [
            [ "Function Prototype:", "d2/d67/fs_cnngen.html#autotoc_md76", null ],
            [ "Parameters:", "d2/d67/fs_cnngen.html#autotoc_md77", null ],
            [ "Returns:", "d2/d67/fs_cnngen.html#autotoc_md78", null ],
            [ "Example:", "d2/d67/fs_cnngen.html#autotoc_md79", null ]
          ] ],
          [ "20.2.4 query() Function", "d2/d67/fs_cnngen.html#sub_sec_custom_api_query", [
            [ "Function Prototype", "d2/d67/fs_cnngen.html#autotoc_md80", null ],
            [ "Parameters:", "d2/d67/fs_cnngen.html#autotoc_md81", null ],
            [ "Returns:", "d2/d67/fs_cnngen.html#autotoc_md82", null ]
          ] ]
        ] ],
        [ "20.3 API Calling Sequence", "d2/d67/fs_cnngen.html#sec_custom_call_seq", null ]
      ] ]
    ] ],
    [ "Caffe Demos", "d6/d57/fs_cnngen_caffe_demos.html", [
      [ "CGPP Deployment for Yolov3", "d6/d57/fs_cnngen_caffe_demos.html#sec_cgpp_deployment_for_yolov3", [
        [ "1 Input Data", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_input_data", null ],
        [ "2 Prepare the JSON File", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_prepare_the_json_file", null ],
        [ "3 Convert", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_convert", null ],
        [ "4 ADES", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_ades", null ],
        [ "5 Build EVK Binary", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_build_evk_binary", null ],
        [ "6 Run File Mode with CGPP", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_run_file_mode_with_cgpp", null ],
        [ "7 Run Live Mode with CGPP", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_run_live_mode_with_cgpp", null ]
      ] ],
      [ "Car License Plate Detection and Recognition", "d6/d57/fs_cnngen_caffe_demos.html#sec_hyperlpr", [
        [ "1 Convert Model File", "d6/d57/fs_cnngen_caffe_demos.html#subsec_hyperlpr_convert_model", null ],
        [ "2 Build EVK Binary", "d6/d57/fs_cnngen_caffe_demos.html#subsec_hyperlpr_build_evk_bin", null ],
        [ "3 Run Python Inference", "d6/d57/fs_cnngen_caffe_demos.html#subsec_hyperlpr_run_python_inference", null ],
        [ "4 Run C inference", "d6/d57/fs_cnngen_caffe_demos.html#subsec_hyperlpr_run_c_inference", null ],
        [ "5 Performance Optimization", "d6/d57/fs_cnngen_caffe_demos.html#subsec_hyperlpr_optimization", null ]
      ] ],
      [ "Custom Node Example", "d6/d57/fs_cnngen_caffe_demos.html#sec_custom_node_example", [
        [ "1 Implement Permute", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_custom_example_implement_permute", [
          [ "1.1 example_node.cc", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_example_node_cc", null ],
          [ "1.2 example_node.h", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_example_node_h", null ],
          [ "1.3 export.cc", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_export_cc", null ],
          [ "1.4 export.h", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_export_h", null ],
          [ "1.5 Makefile", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_example_makefile", null ],
          [ "1.6 Custom_nodes.py", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_nodes_py", null ]
        ] ],
        [ "2 Caffe model", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_custom_example_caffe_model", [
          [ "2.1 Re-compile Caffe", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_example_recompile_caffe", null ],
          [ "2.2 Prepare Prototxt Files", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_example_prepare_prototxt_files", null ],
          [ "2.3 Get caffemodel File", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_example_get_caffemodel_file", null ]
        ] ],
        [ "3 Convert", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_custom_example_convert", [
          [ "3.1 Compile custom.so", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_example_compile_custom_so", null ],
          [ "3.2 Prepare DRA Image", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_example_prepare_dra_image", null ],
          [ "3.3 Generate the VAS Code", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_generate_the_vas_code", null ],
          [ "3.4 Compile VAS Code", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_compile_vas_code", null ],
          [ "3.5 Generate the ADES Command", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_generate_the_ades_command", null ],
          [ "3.6 Run ADES Command", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_custom_run_ades_command", null ]
        ] ]
      ] ],
      [ "Deployment for Quantization Retrained Yolov3", "d6/d57/fs_cnngen_caffe_demos.html#sec_yolov3_quant_deploy", [
        [ "1 Deployment", "d6/d57/fs_cnngen_caffe_demos.html#subsec_yolov3_quant_deployment", null ],
        [ "2 Layer_compare", "d6/d57/fs_cnngen_caffe_demos.html#subsec_yolov3_quant_layer_compare", null ],
        [ "3 Accuracy", "d6/d57/fs_cnngen_caffe_demos.html#subsec_yolov3_quant_accuracy", null ]
      ] ],
      [ "Face Alignment", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_face_landmarks_68", [
        [ "1 Download Model", "d6/d57/fs_cnngen_caffe_demos.html#caffe_face_landmarks_68_download_model", null ],
        [ "2 Generate Cavalry Binary", "d6/d57/fs_cnngen_caffe_demos.html#caffe_face_landmarks_68_generate_cavalry_binary", null ],
        [ "3 Build EVK Binary", "d6/d57/fs_cnngen_caffe_demos.html#caffe_face_landmarks_68_build_evk_binary", null ],
        [ "4 Run Python Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_face_landmarks_68_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_face_landmarks_68_run_c_inference", null ]
      ] ],
      [ "Face Recognition", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_mobilefacenets", [
        [ "1 Download Model", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mobilefacenets_download_model", null ],
        [ "2 Generate Cavalry Binary", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mobilefacenets_generate_cavalry_binary", null ],
        [ "3 Build EVK Binary", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mobilefacenets_build_evk_binary", null ],
        [ "4 Run Python Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_mobilefacenets_run_python_inference", null ],
        [ "5 Run C Inference With V1", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mobilefacenets_run_c_inference_with_v1", null ],
        [ "6 Run C Inference With V2", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mobilefacenets_run_c_inference_with_v2", null ],
        [ "7 Record Face Data", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mobilefacenets_record_face_data", null ],
        [ "8 Run with Pyramid Buffer", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mobilefacenets_run_with_pyramid_buffer", null ]
      ] ],
      [ "GoogLeNet", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_googlenet", [
        [ "1 gen_image_list.py", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_googlenet_gen_image_list_py", null ],
        [ "2 caffeparser.py", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_googlenet_caffeparser_py", null ],
        [ "3 VAS Compile", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_googlenet_vas_compile", null ],
        [ "4 ades_autogen.py", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_googlenet_ades_autogen_py", null ],
        [ "5 cavalry_gen", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_googlenet_cavalry_gen", null ],
        [ "6 Prepare the input", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_googlenet_prepare_the_input", null ],
        [ "7 test_nnctrl", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_googlenet_test_nnctrl", null ]
      ] ],
      [ "LSTM Warp-CTC", "d6/d57/fs_cnngen_caffe_demos.html#sec_lstm_warpctc", [
        [ "1 Download Warp-CTC Caffe", "d6/d57/fs_cnngen_caffe_demos.html#subsec_download_warpctc_caffe", null ],
        [ "2 Modify Prototxt", "d6/d57/fs_cnngen_caffe_demos.html#subsec_warpctc_modify_prototxt", null ],
        [ "3 Convert and Compile", "d6/d57/fs_cnngen_caffe_demos.html#subsec_warpctc_convert_compile", null ],
        [ "4 SDK Preparation", "d6/d57/fs_cnngen_caffe_demos.html#subsec_warpctc_SDK_preparation", null ],
        [ "5 Run on Board", "d6/d57/fs_cnngen_caffe_demos.html#subsec_warpctc_run_on_board", null ]
      ] ],
      [ "LSTM Warp-CTC with One Shot", "d6/d57/fs_cnngen_caffe_demos.html#sec_lstm_warpctc_with_one_shot", [
        [ "1 Prepare Environment", "d6/d57/fs_cnngen_caffe_demos.html#sec_prepare_environment", null ],
        [ "2 File Preparation", "d6/d57/fs_cnngen_caffe_demos.html#subsec_file_preparation", [
          [ "2.1 Pretrained Model", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_prepare_pretrained_model", null ],
          [ "2.2 DRA Files", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_prepare_dra_files", null ],
          [ "2.3 Model Graph Description File", "d6/d57/fs_cnngen_caffe_demos.html#subb_sec_prepare_mode_graph_description_file", null ]
        ] ],
        [ "3 Build LSTM in One Shot", "d6/d57/fs_cnngen_caffe_demos.html#subsec_build_lstm_in_one_shot", null ],
        [ "4 Run LSTM on Board", "d6/d57/fs_cnngen_caffe_demos.html#subsec_run_lstm_on_board", null ],
        [ "5 Compare Result", "d6/d57/fs_cnngen_caffe_demos.html#subsec_compare_result", null ]
      ] ],
      [ "Light Yolo", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_light_yolo", [
        [ "1 Export Caffe model", "d6/d57/fs_cnngen_caffe_demos.html#caffe_light_yolo_export_caffe_model", null ],
        [ "2 CNNGen Conversion", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_light_yolo_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_light_yolo_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_light_yolo_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_light_yolo_run_c_inference", null ]
      ] ],
      [ "MTCNN", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_mtcnn", [
        [ "1 Download Model", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mtcnn_download_model", null ],
        [ "2 Generate Cavalry Binary", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mtcnn_generate_cavalry_binary", null ],
        [ "3 Build EVK Binary", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mtcnn_build_evk_binary", null ],
        [ "4 Run Python Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_mtcnn_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d57/fs_cnngen_caffe_demos.html#caffe_mtcnn_run_c_inference", null ]
      ] ],
      [ "Mobilenet Runtime Rotation", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_mobilenetv1", null ],
      [ "PVANET Demo", "d6/d57/fs_cnngen_caffe_demos.html#fs_caffe_pvanet", [
        [ "1 Download", "d6/d57/fs_cnngen_caffe_demos.html#sec_pvanet_download", null ],
        [ "2 Network Split", "d6/d57/fs_cnngen_caffe_demos.html#sec_pvanet_network_split", [
          [ "2.1 FEN and RPN", "d6/d57/fs_cnngen_caffe_demos.html#sub_pvanetfen_rpn", null ],
          [ "2.2 ROI Pooling", "d6/d57/fs_cnngen_caffe_demos.html#sub_pvanet_roi_pooling", null ],
          [ "2.3 Split:  FC Classifier", "d6/d57/fs_cnngen_caffe_demos.html#sub_pvanet_fc_classifier", null ],
          [ "2.4 Split:  Post-Processing", "d6/d57/fs_cnngen_caffe_demos.html#sub_pvanet_post_process", null ]
        ] ],
        [ "3 Integration", "d6/d57/fs_cnngen_caffe_demos.html#sec_pvanet_integration", null ],
        [ "4 Deployment", "d6/d57/fs_cnngen_caffe_demos.html#sec_pvanet_deployment", [
          [ "4.1 Pipeline Flow", "d6/d57/fs_cnngen_caffe_demos.html#sub_pvanet_pipeline_flow", null ],
          [ "4.2 Pipeline Dependency", "d6/d57/fs_cnngen_caffe_demos.html#sub_pvanet_pipeline_dependency", null ],
          [ "4.3 Pipeline Ring Buffer Number", "d6/d57/fs_cnngen_caffe_demos.html#sub_pvanet_pipeline_ring_buf", null ]
        ] ],
        [ "5 Generate Cavalry Binary", "d6/d57/fs_cnngen_caffe_demos.html#sec_pvanet_cavalry_binary", null ],
        [ "6 Build EVK Binary", "d6/d57/fs_cnngen_caffe_demos.html#sec_pvanet_evk_binary", null ],
        [ "7 Run on Board", "d6/d57/fs_cnngen_caffe_demos.html#sec_pvanet_run_on_board", null ],
        [ "8 Overall Performance", "d6/d57/fs_cnngen_caffe_demos.html#sec_pvanet_pverall_perf", null ]
      ] ],
      [ "QR Code", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_qrcode", [
        [ "1 Download SSD Caffe", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_qrcode_download_ssd_caffe", null ],
        [ "2 Extract Parameters of PriorBox Layer", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_qrcode_extract_params", null ],
        [ "3 CNNGen Conversion", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_qrcode_cnngen_conversion", null ],
        [ "4 Build Unit Test", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_qrcode_build_unit_test", null ],
        [ "5 Run Python Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_qrcode_run_python_inference", null ],
        [ "6 Run C Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_qrcode_run_c_inference", null ]
      ] ],
      [ "Regression for VGG16-SSD", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_vgg16_ssd", [
        [ "1 Context", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_vgg16_ssd_context", null ],
        [ "2 VGG-SSD Model Optimization", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_vgg16_ssd_model_optimization", null ],
        [ "3 VGG-SSD Accuracy Regression Workflow", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_vgg16_ssd_accuracy_regression_workflow", null ],
        [ "4 Ground Truth File", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_vgg16_ssd_ground_truth_file", null ],
        [ "5 Run Regression Test", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_vgg16_ssd_configuration", null ]
      ] ],
      [ "ResNet50 with DRAv3", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_resnet50_with_drav3", [
        [ "1 Prepare GPU Environment", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_resnet50_with_drav3_prepare_gpu_env", null ],
        [ "2 Run DRAv3 with CNNGen Samples", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_resnet50_with_drav3_run_drav3", null ],
        [ "3 Final Tuning with DRAv3", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_resnet50_with_drav3_final_tuning", null ]
      ] ],
      [ "ResNet50 with Json Pre-Processing", "d6/d57/fs_cnngen_caffe_demos.html#sec_resnet50_with_json_preprocessing", [
        [ "1 Prepare Mean file", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_resnet50_json_prepare_mean_file", null ],
        [ "2 Prepare the Json File", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_resnet50_json_prepare_json_file", null ],
        [ "3 Convert", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_resnet50_json_Convert", null ],
        [ "4 ADES", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_resnet50_json_ades", null ],
        [ "5 Accuracy", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_resnet50_json_accuracy", null ],
        [ "6 Build EVK Binary", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_resnet50_json_build_evk_binary", null ],
        [ "7 Run on Board", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_resnet50_json_run_on_board", null ]
      ] ],
      [ "SSD MobileNetV1", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_mobilenetv1_ssd", [
        [ "1 Download SSD Caffe", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_mobilenetv1_ssd_download_ssd_caffe", null ],
        [ "2 Extract Parameters of PriorBox Layer", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_mobilenetv1_ssd_extract_params", null ],
        [ "3 CNNGen Conversion", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_mobilenetv1_ssd_cnngen_conversion", null ],
        [ "4 Build Unit Test", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_mobilenetv1_ssd_build_unit_test", null ],
        [ "5 Run Python Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_mobilenetv1_ssd_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_mobilenetv1_ssd_run_c_inference", null ]
      ] ],
      [ "YOLO V2 and V3", "d6/d57/fs_cnngen_caffe_demos.html#sec_caffe_yolo_v2", [
        [ "1. Re-compile Caffe", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolo_v2_recompile_caffe", null ],
        [ "2 Prepare Caffe Model", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolo_v2_prepare_caffe_model", null ],
        [ "3 Convert", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolo_v2_convert", null ],
        [ "4 Deploy with Live Mode", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolo_v2_deploy_with_live_mode", null ],
        [ "5 YOLOV3 Demonstration", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolo_v2_yolo_v3_demo", [
          [ "5.1 CNNGen Conversion", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolov3_sp50_full_cnngen_conversion", null ],
          [ "5.2 Build Unit Test", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolo_v3_sp50_full_build_unit_test", null ],
          [ "5.3 Run Python Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolo_v3_sp50_full_run_python_inference", null ],
          [ "5.4 Run C Inference", "d6/d57/fs_cnngen_caffe_demos.html#sub_sec_caffe_yolov3_sp50_full_run_c_inference", null ]
        ] ]
      ] ]
    ] ],
    [ "Tensorflow Demos", "d7/d0a/fs_cnngen_tf_demos.html", [
      [ "Audio with DS_CNN_KWS", "d7/d0a/fs_cnngen_tf_demos.html#sec_tf_audio_ds_cnn_kws", [
        [ "1 Preprocess Model", "d7/d0a/fs_cnngen_tf_demos.html#ds_cnn_kws_preprcess_model", null ],
        [ "2 Prepare DRA Binaries", "d7/d0a/fs_cnngen_tf_demos.html#ds_cnn_kws_prepare_dra_binaries", null ],
        [ "3 Generate Cavalry Binary", "d7/d0a/fs_cnngen_tf_demos.html#ds_cnn_kws_generate_cavalry_binary", null ],
        [ "4 Run Python Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_ds_cnn_kws_run_python_inference", null ],
        [ "5 Run C Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_ds_cnn_kws_run_c_inference", null ]
      ] ],
      [ "Bodypix", "d7/d0a/fs_cnngen_tf_demos.html#sec_tf_bodypix", [
        [ "1 Download and Export Model File", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_bodypix_download_model_file", null ],
        [ "2 Model preprocessing", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_bodypix_model_preprocessing", null ],
        [ "3 Generate Cavalry Binary", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_bodypix_generate_cavalry_binary", null ],
        [ "4 Build SDK Binary", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_bodypix_build_binary", null ],
        [ "5 Run Python Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_bodypix_run_python_inference", null ],
        [ "6 Run C Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_bodypix_run_c_inference", null ]
      ] ],
      [ "Hand Landmark", "d7/d0a/fs_cnngen_tf_demos.html#sec_tf_hand_landmark", [
        [ "1 Download the Model Files", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hand_landmark_download_model_file", null ],
        [ "2 Generate Cavalry Binary", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hand_landmark_generate_cavalry_binary", null ],
        [ "3 Build SDK Binary", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hand_landmark_build_binary", null ],
        [ "4 Run Python Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hand_landmark_run_python_inference", null ],
        [ "5 Run C Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hand_landmark_run_c_inference", null ]
      ] ],
      [ "HF-Net", "d7/d0a/fs_cnngen_tf_demos.html#sec_tf_hfnet", [
        [ "1 Export Model", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hfnet_export_model", null ],
        [ "2 CNNGen Conversion", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hfnet_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hfnet_build_unit_test", null ],
        [ "4 Run Python Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hfnet_run_python_inference", null ],
        [ "5 Run C Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_hfnet_run_c_inference", null ]
      ] ],
      [ "Mobilenetv2_NV12", "d7/d0a/fs_cnngen_tf_demos.html#sec_tf_model_with_mobilenetv2_nv12", [
        [ "1 Convert DRA Image", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_convert_DRA_image", null ],
        [ "2 CNNGen Conversion", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_nv12_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_nv12_build_unit_test", null ],
        [ "4 Run Python Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_nv12_run_python_inference", null ],
        [ "5 Run C Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_nv12_run_c_inference", null ]
      ] ],
      [ "Regression for DeepLabv3", "d7/d0a/fs_cnngen_tf_demos.html#sec_tf_deeplab_v3", [
        [ "1 Context", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_deeplab_v3_context", null ],
        [ "2 Export Model", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_deeplab_v3_export_model", null ],
        [ "3 CNNGen Conversion", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_deeplab_v3_cnngen_conversion", null ],
        [ "4 Build Unit Test", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_deeplab_v3_build_unit_test", null ],
        [ "5 Run Python Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_deeplab_v3_run_python_inference", null ],
        [ "6 Run C Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_deeplab_v3_run_c_inference", null ],
        [ "7 Run Accuracy Test", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_deeplab_v3_run_accuracy_test", null ]
      ] ],
      [ "SSD Mobilenetv2", "d7/d0a/fs_cnngen_tf_demos.html#sec_tf_mobilenetv2_ssd", [
        [ "1 Download Model File", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_ssd_download_model_file", null ],
        [ "2 Pre-Process Model", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_ssd_preprocess_model", null ],
        [ "3 Post Process", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_ssd_post_process", null ],
        [ "4 CNNGen_Conversion", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_ssd_cnngen_conversion", null ],
        [ "5 Build Unit Test", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_ssd_build_unit_test", null ],
        [ "6 Run Python Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_ssd_run_python_inference", null ],
        [ "7 Run C Inference", "d7/d0a/fs_cnngen_tf_demos.html#sub_sec_tf_mobilenetv2_ssd_run_c_inference", null ]
      ] ]
    ] ],
    [ "ONNX Demos", "d6/d99/fs_cnngen_onnx_demos.html", [
      [ "ByteTrack", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_bytetrack", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_bytetrack_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_bytetrack_cnngen_conversion", null ],
        [ "3 Build EVK Binary", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_bytetrack_build_evk_binary", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_bytetrack_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_bytetrack_run_c_inference", null ]
      ] ],
      [ "CenterNet", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_centernet", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_centernet_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_centernet_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_centernet_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_centernet_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_centernet_run_c_inference", null ]
      ] ],
      [ "DDRNet", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_ddrnet", [
        [ "1 Download and Export Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_ddrnet_download_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_ddrnet_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_ddrnet_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_ddrnet_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_ddrnet_run_c_inference", null ]
      ] ],
      [ "Face Detection and Blur Function", "d6/d99/fs_cnngen_onnx_demos.html#sec_face_detection_and_blur_function", [
        [ "1 Download Model File", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_fd_blur_down_model_file", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_fdfd_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_fd_blur_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_fgfd_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_fd_blur_run_c_inference", null ],
        [ "6 DSP Blur Function", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_fd_blur_dsp_blur_function", null ]
      ] ],
      [ "FairMOT", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_fairmot", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_fairmot_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_fairmot_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_fairmot_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_fairmot_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_fairmot_run_c_inference", null ]
      ] ],
      [ "LFFD", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_lffd", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_lffd_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_lffd_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_lffd_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_lffd_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_lffd_run_c_inference", null ]
      ] ],
      [ "RetinaFace", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_retinaface", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_retinaface_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_retinaface_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_retinaface_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_retinaface_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_retinaface_run_c_Inference", null ]
      ] ],
      [ "Robust Video Matting", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_robust_video_matting", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_robust_video_matting_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#onnx_robust_video_matting_cnngen_conversion", null ],
        [ "3 Build EVK Binary", "d6/d99/fs_cnngen_onnx_demos.html#onnx_robust_video_matting_build_evk_binary", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_robust_video_matting_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_robust_video_matting_run_c_inference", null ]
      ] ],
      [ "SWIN Transformer", "d6/d99/fs_cnngen_onnx_demos.html#sec_swin_tiny", [
        [ "1 Introduction", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_swin_tiny_introduction", null ],
        [ "2 Generate ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_swin_tiny_genertate_onnx_model", null ],
        [ "3 Model Convert", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_swin_tiny_model_convert", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_swin_tiny_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_swin_tiny_run_c_inference", null ]
      ] ],
      [ "YOLOv3", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_yolov3", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_yolov3_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov3_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov3_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov3_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov3_run_c_inference", null ]
      ] ],
      [ "YOLOv5", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_yolov5", [
        [ "1 Export ONNX model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_yolov5_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov5_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov5_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov5_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov5_run_c_inference", null ]
      ] ],
      [ "YOLOv7", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_yolov7", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_yolov7_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov7_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov7_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov7_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov7_run_c_inference", null ]
      ] ],
      [ "YOLOv8", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_yolov8", [
        [ "1 Export ONNX Model", "d6/d99/fs_cnngen_onnx_demos.html#onnx_yolov8_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov8_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov8_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov8_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolov8_run_c_Inference", null ]
      ] ],
      [ "YOLOX", "d6/d99/fs_cnngen_onnx_demos.html#sec_onnx_yolox", [
        [ "1 Export ONNX Models", "d6/d99/fs_cnngen_onnx_demos.html#onnx_yolox_export_onnx_model", null ],
        [ "2 CNNGen Conversion", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolox_cnngen_conversion", null ],
        [ "3 Build Unit Test", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolox_build_unit_test", null ],
        [ "4 Run Python Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolox_run_python_inference", null ],
        [ "5 Run C Inference", "d6/d99/fs_cnngen_onnx_demos.html#sub_sec_onnx_yolox_run_c_inference", null ]
      ] ]
    ] ],
    [ "Historical Updates", "db/d40/fs_history_updates.html", null ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"d1/d82/fs_workflow.html",
"d6/d57/fs_cnngen_caffe_demos.html#subsec_hyperlpr_run_python_inference",
"da/dc5/fs_quick_start.html#sub_sec_sample_tool_imx2bin"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';