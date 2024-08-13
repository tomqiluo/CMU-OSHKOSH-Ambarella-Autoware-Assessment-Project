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
  [ "Driver", "index.html", [
    [ "Cavalry V3 (CV72) Driver API", "d4/d86/page_drv_cavalry_doc.html", [
      [ "0. Revision History", "d4/d86/page_drv_cavalry_doc.html#cavalry_history", null ],
      [ "1. Introduction", "d4/d86/page_drv_cavalry_doc.html#cavalry_intro", null ],
      [ "2. Cavalry Usage", "d4/d86/page_drv_cavalry_doc.html#cavalry_usage", [
        [ "2.1 cavalry_load", "d4/d86/page_drv_cavalry_doc.html#cavalry_usage_load_ucode", null ],
        [ "2.2 cavalry_clock", "d4/d86/page_drv_cavalry_doc.html#cavalry_usage_clock", null ],
        [ "2.3 cavalry_log", "d4/d86/page_drv_cavalry_doc.html#cavalry_usage_ucode_log", null ],
        [ "2.4 cavalry_top", "d4/d86/page_drv_cavalry_doc.html#cavalry_usage_top", null ]
      ] ],
      [ "3. Cavalry Debug", "d4/d86/page_drv_cavalry_doc.html#cavalry_debug", [
        [ "3.1 cavalry_core_dump", "d4/d86/page_drv_cavalry_doc.html#cavalry_debug_core_dump", null ],
        [ "3.2 vpstatus", "d4/d86/page_drv_cavalry_doc.html#cavalry_debug_vpstatus", null ],
        [ "3.3 cavalry_monitor", "d4/d86/page_drv_cavalry_doc.html#cavalry_debug_monitor", null ]
      ] ],
      [ "4. Cavalry API", "d4/d86/page_drv_cavalry_doc.html#sec_cavalry_api", null ],
      [ "5. License", "d4/d86/page_drv_cavalry_doc.html#cavalry_license", null ]
    ] ],
    [ "CMA Driver API", "d8/d84/page_drv_cma_doc.html", [
      [ "0. Revision History", "d8/d84/page_drv_cma_doc.html#cma_driver_history", null ],
      [ "1. Memory Layout Introduction", "d8/d84/page_drv_cma_doc.html#cma_layout_intr", [
        [ "1.1 4-GB Memory Layout", "d8/d84/page_drv_cma_doc.html#cma_4g_layout", null ],
        [ "1.2 8-GB Memory Layout", "d8/d84/page_drv_cma_doc.html#cma_8g_layout", null ]
      ] ],
      [ "2. Memory Management of IAV / DSP Partitions", "d8/d84/page_drv_cma_doc.html#cma_memory", [
        [ "2.1 Reserved Memory Management", "d8/d84/page_drv_cma_doc.html#reserved_memory_management", null ]
      ] ],
      [ "3. CMA Driver", "d8/d84/page_drv_cma_doc.html#cma_driver", [
        [ "3.1 Ambarella CMA Driver", "d8/d84/page_drv_cma_doc.html#sec_ambarella_cma_driver", null ],
        [ "3.2 Specifying CMA Partitions through Device Trees", "d8/d84/page_drv_cma_doc.html#sec_specify_cma_partion", null ],
        [ "3.3 Memory Management Block", "d8/d84/page_drv_cma_doc.html#sec_memory_mangement_block", [
          [ "3.3.1 Anonymous MMB", "d8/d84/page_drv_cma_doc.html#sub_sec_anon", null ],
          [ "3.3.2 User-Customized MMB", "d8/d84/page_drv_cma_doc.html#sub_sec_custom", null ],
          [ "3.3.3 Enabling and Synchronizing the Cache for MMBs", "d8/d84/page_drv_cma_doc.html#sub_sec_enable", null ]
        ] ],
        [ "3.4 Pre-Allocated MMBs", "d8/d84/page_drv_cma_doc.html#sec_pre_allocate_mmbs", null ],
        [ "3.5 IAV / DSP Private and Shared MMBs", "d8/d84/page_drv_cma_doc.html#sec_driver_private_share", null ],
        [ "3.6 Driver Module Parameters", "d8/d84/page_drv_cma_doc.html#sec_driver_module_parameters", null ],
        [ "3.7 Dump MMB Information", "d8/d84/page_drv_cma_doc.html#sec_dump_mmb_info", [
          [ "Example 1. Dumping the MMB information of a CV5 Timn board.", "d8/d84/page_drv_cma_doc.html#cmd_example_1", null ]
        ] ],
        [ "3.8 Private Memory Allocator AMA", "d8/d84/page_drv_cma_doc.html#sec_private_mem_allocator", [
          [ "3.8.1 Enable AMA", "d8/d84/page_drv_cma_doc.html#sub_sec_ama", null ],
          [ "Example 2. Enabling AMA through the module parameter \"ama_enable\" of Ambarella CMA driver.", "d8/d84/page_drv_cma_doc.html#cmd_example_2", null ]
        ] ]
      ] ],
      [ "4. Examples", "d8/d84/page_drv_cma_doc.html#cma_example", [
        [ "4.1 Specifying the IAV / DSP Sub-partition Size", "d8/d84/page_drv_cma_doc.html#specify_sub_partion_size", [
          [ "4.1.1 Compile Configuration", "d8/d84/page_drv_cma_doc.html#sub_sec_compile", null ],
          [ "4.1.2 Module Parameters Configuration", "d8/d84/page_drv_cma_doc.html#sub_sec_mod_conf", null ],
          [ "Example 3. Specifying the size of the IAV / DSP sub-partitions through the module parameters of Ambarella CMA driver.", "d8/d84/page_drv_cma_doc.html#cmd_example_3", null ],
          [ "4.1.3 IOCTL Configuration", "d8/d84/page_drv_cma_doc.html#sub_sec_ioctl", null ],
          [ "Example 4. Resizing the bitstream buffer (IAV_PART_BSB) through test_mempart.", "d8/d84/page_drv_cma_doc.html#cmd_example_4", null ]
        ] ],
        [ "4.2 Specifying the Pre-allocated MMBs", "d8/d84/page_drv_cma_doc.html#specify_pre_allocate_mmbs", [
          [ "4.2.1 Compile Configuration", "d8/d84/page_drv_cma_doc.html#sub_sec_compile_configuration", null ],
          [ "4.2.2 Configuring the Module Parameters", "d8/d84/page_drv_cma_doc.html#sub_sec_conf_mod", null ],
          [ "Example 5. Specifying the bitmap of the IAV / DSP sub-partitions through the module parameters \"prealloc_buf_map\" and \"nofree_prealloc_buf_map\" of the Ambarella CMA driver.", "d8/d84/page_drv_cma_doc.html#cmd_example_5", null ]
        ] ],
        [ "4.3 Specifying Cached MMBs", "d8/d84/page_drv_cma_doc.html#specify_cache_mmbs", [
          [ "4.3.1 Configuring Module Parameters", "d8/d84/page_drv_cma_doc.html#sub_sec_conf_mod_para", null ],
          [ "Example 6. Specifying the bitmap of the IAV / DSP sub-partitions through the module parameters \"cached_buf_map\" of the Ambarella CMA driver.", "d8/d84/page_drv_cma_doc.html#cmd_Example_6", null ]
        ] ],
        [ "4.4 Allocating/Freeing Anonymous Memory Partitions", "d8/d84/page_drv_cma_doc.html#mange_memory_partition", [
          [ "Example 7. Allocating or freeing the anonymous memory partition through test_mempart.", "d8/d84/page_drv_cma_doc.html#cmd_example_7", null ]
        ] ]
      ] ],
      [ "5. FAQ", "d8/d84/page_drv_cma_doc.html#cma_faq", null ],
      [ "6. License", "d8/d84/page_drv_cma_doc.html#cma_license", null ]
    ] ],
    [ "IAV Driver API", "df/d3f/page_drv_iav_doc.html", [
      [ "0. Revision History", "df/d3f/page_drv_iav_doc.html#iav_history", null ],
      [ "1. Introduction", "df/d3f/page_drv_iav_doc.html#iav_intro", null ],
      [ "2. Key Features of the APIs", "df/d3f/page_drv_iav_doc.html#iav_key_feature", null ],
      [ "3. IAV Driver State Model", "df/d3f/page_drv_iav_doc.html#iav_state_model", [
        [ "3.1 IAV Driver State Machine", "df/d3f/page_drv_iav_doc.html#iav_driver_state_machine", null ],
        [ "3.2 IAV driver boot param", "df/d3f/page_drv_iav_doc.html#iav_driver_boot_param", null ]
      ] ],
      [ "4. IAV Interrrupts", "df/d3f/page_drv_iav_doc.html#iav_interrupts", null ],
      [ "5. Encoding Data Flow", "df/d3f/page_drv_iav_doc.html#iav_encode_flow", [
        [ "5.1 Concepts", "df/d3f/page_drv_iav_doc.html#sec_encode_concepts", [
          [ "Encode Mode", "df/d3f/page_drv_iav_doc.html#autotoc_md1", null ],
          [ "Channel", "df/d3f/page_drv_iav_doc.html#autotoc_md2", null ],
          [ "Source Buffer", "df/d3f/page_drv_iav_doc.html#autotoc_md3", null ],
          [ "Canvas Buffer", "df/d3f/page_drv_iav_doc.html#autotoc_md4", null ],
          [ "Encode Stream", "df/d3f/page_drv_iav_doc.html#autotoc_md5", null ]
        ] ],
        [ "5.2 Relationships and Data Flow", "df/d3f/page_drv_iav_doc.html#sec_encode_relation", [
          [ "A. Source Canvas and Encode Stream Relationship", "df/d3f/page_drv_iav_doc.html#autotoc_md6", null ],
          [ "B. Multiple Source Buffer Relationship", "df/d3f/page_drv_iav_doc.html#autotoc_md7", null ],
          [ "C. Synonyms/Exchangeable Terms", "df/d3f/page_drv_iav_doc.html#autotoc_md8", null ]
        ] ],
        [ "5.3 Encoding States", "df/d3f/page_drv_iav_doc.html#sec_encode_states", null ],
        [ "5.4 Stream States", "df/d3f/page_drv_iav_doc.html#sec_encode_stream", null ]
      ] ],
      [ "6. Decoding Data Flow", "df/d3f/page_drv_iav_doc.html#iav_decode", null ],
      [ "7. IAV Sysfs Info", "df/d3f/page_drv_iav_doc.html#iav_sysfs_info", [
        [ "7.1 IAV sysfs files", "df/d3f/page_drv_iav_doc.html#iav_sysfs_file", null ]
      ] ],
      [ "8. IAV Procfs Info", "df/d3f/page_drv_iav_doc.html#iav_proc_info", [
        [ "8.1 IAV State Info", "df/d3f/page_drv_iav_doc.html#iav_state_info", null ],
        [ "8.2 IAV Memory Info", "df/d3f/page_drv_iav_doc.html#iav_memory_info", null ],
        [ "8.3 IAV Feature Debug", "df/d3f/page_drv_iav_doc.html#iav_feature_debug", null ],
        [ "8.4 IAV IOCTL Arguments Print", "df/d3f/page_drv_iav_doc.html#iav_ioctl_arg_print_function", null ]
      ] ],
      [ "9. DSP Procfs Info", "df/d3f/page_drv_iav_doc.html#dsp_proc_info", [
        [ "9.1 Optional DSP command printing", "df/d3f/page_drv_iav_doc.html#iav_optional_dsp_cmd_print", null ],
        [ "9.2 DSP state", "df/d3f/page_drv_iav_doc.html#iav_dsp_state_proc_file", null ]
      ] ],
      [ "10. Poll interface", "df/d3f/page_drv_iav_doc.html#iav_poll", [
        [ "10.1 Poll interface to query IAV data", "df/d3f/page_drv_iav_doc.html#drv_query_iav_data", null ],
        [ "10.2 Poll interface to sync irq", "df/d3f/page_drv_iav_doc.html#drv_irq_sync", null ]
      ] ],
      [ "11. Example Usage of APIs", "df/d3f/page_drv_iav_doc.html#iav_example", [
        [ "11.1 Open the Device", "df/d3f/page_drv_iav_doc.html#usage_open", null ],
        [ "11.2 Memory Management", "df/d3f/page_drv_iav_doc.html#usage_mem", null ],
        [ "11.3 Configure VIN", "df/d3f/page_drv_iav_doc.html#usage_vin", null ],
        [ "11.4 Configure VOUT", "df/d3f/page_drv_iav_doc.html#usage_vout_config", null ],
        [ "11.5 Go To Idle State", "df/d3f/page_drv_iav_doc.html#usage_go_to_idle", null ],
        [ "11.6 Configure DSP Resources", "df/d3f/page_drv_iav_doc.html#usage_dsp_configuration", [
          [ "11.6.1 Set System Resources Limitations", "df/d3f/page_drv_iav_doc.html#ioc_configure_resource", null ],
          [ "11.6.2 Configure DPTZ for Source Buffer", "df/d3f/page_drv_iav_doc.html#ioc_configure_dptz", null ],
          [ "11.6.3 Configure Pyramid", "df/d3f/page_drv_iav_doc.html#ioc_configure_pyramid", null ]
        ] ],
        [ "11.7 Enter Preview State", "df/d3f/page_drv_iav_doc.html#usage_enter_preview", null ],
        [ "11.8 Configure Stream", "df/d3f/page_drv_iav_doc.html#usage_stream_configuration", null ],
        [ "11.9 Start Encoding", "df/d3f/page_drv_iav_doc.html#usage_start_encode", null ],
        [ "11.10 Stop Encoding", "df/d3f/page_drv_iav_doc.html#usage_stop_encode", null ],
        [ "11.11 Query Bit Stream Information", "df/d3f/page_drv_iav_doc.html#usage_bsb", null ],
        [ "11.12 Sysfs Usage", "df/d3f/page_drv_iav_doc.html#usage_sysfs", null ],
        [ "11.13 Poll Interface Usage.", "df/d3f/page_drv_iav_doc.html#usage_poll_interface_drv", [
          [ "11.13.1 Usage of Querying IAV Data", "df/d3f/page_drv_iav_doc.html#poll_iav_data_usage_drv", null ],
          [ "11.13.2 Usage of Interrupt Synchronization", "df/d3f/page_drv_iav_doc.html#poll_irq_sync_usage_drv", null ]
        ] ],
        [ "11.14 Return Value of APIs", "df/d3f/page_drv_iav_doc.html#usage_return_value", null ]
      ] ],
      [ "12. IAV API", "df/d3f/page_drv_iav_doc.html#sec_iav_api", [
        [ "12.1 IAV IOCTL API: VIN", "df/d3f/page_drv_iav_doc.html#sec_iav_api_vin", null ],
        [ "12.2 IAV IOCTL API: VOUT", "df/d3f/page_drv_iav_doc.html#sec_iav_api_vout", null ],
        [ "12.3 IAV IOCTL API: Load Ucode", "df/d3f/page_drv_iav_doc.html#sec_iav_api_ucode", null ],
        [ "12.4 IAV IOCTL API: DSP & Driver Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_drv", null ],
        [ "12.5 IAV IOCTL API: Encode Pyramid Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_enc", null ],
        [ "12.6 IAV IOCTL API: System Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_sys", null ],
        [ "12.7 IAV IOCTL API: EFM", "df/d3f/page_drv_iav_doc.html#sec_iav_api_efm", null ],
        [ "12.8 IAV IOCTL API: EFR", "df/d3f/page_drv_iav_doc.html#sec_iav_api_efr", null ],
        [ "12.9 IAV IOCTL API: Memory Management Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_mem", null ],
        [ "12.10 IAV IOCTL API: Stream Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_stm", null ],
        [ "12.11 IAV IOCTL API: Overlay Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_ovl", null ],
        [ "12.12 IAV IOCTL API: Vcap Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_vcap", null ],
        [ "12.13 IAV IOCTL API: VProc Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_vproc", null ],
        [ "12.14 IAV IOCTL API: VIN & IDSP Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_vind", null ],
        [ "12.15 IAV IOCTL API: Debug IOCTL", "df/d3f/page_drv_iav_doc.html#sec_iav_api_dbg", null ],
        [ "12.16 IAV IOCTL API: Decoder Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_dec", null ],
        [ "12.17 IAV IOCTL API: Arbitrary Image Scaler Control", "df/d3f/page_drv_iav_doc.html#sec_iav_api_img_scale", null ]
      ] ],
      [ "13. License", "df/d3f/page_drv_iav_doc.html#iav_license", null ]
    ] ],
    [ "Sensor Parameters & Tuning Table", "d4/d64/page_drv_sensor.html", [
      [ "0. Revision History", "d4/d64/page_drv_sensor.html#sensor_history", null ],
      [ "1. Sensor Module Parameters", "d4/d64/page_drv_sensor.html#sensor_parm", null ],
      [ "2. Sensor Module Parameters Table", "d4/d64/page_drv_sensor.html#sensor_parm_table", [
        [ "2.1 CMOS Sensor Parameters Table", "d4/d64/page_drv_sensor.html#cmos_parm_table", null ],
        [ "2.2 TOF Sensor Parameters Table", "d4/d64/page_drv_sensor.html#tof_parm_table", null ]
      ] ],
      [ "3. Bridge Sensor Parameters Table", "d4/d64/page_drv_sensor.html#brg_sensor_parm_table", null ],
      [ "4. CV5x Sensor Tuning Table", "d4/d64/page_drv_sensor.html#CV5x_sensor_tuning_table", [
        [ "4.1 Sensor tuning table for IPC", "d4/d64/page_drv_sensor.html#img_cv5x_table_ipc", null ]
      ] ],
      [ "5. CV72 Sensor Tuning Table", "d4/d64/page_drv_sensor.html#CV72_sensor_tuning_table", [
        [ "5.1 Sensor tuning table for DVR", "d4/d64/page_drv_sensor.html#img_cv72_table_dvr", null ],
        [ "5.2 Sensor tuning table for EMIRROR", "d4/d64/page_drv_sensor.html#img_cv72_table_emirror", null ],
        [ "5.3 Sensor tuning table for IPC", "d4/d64/page_drv_sensor.html#img_cv72_table_ipc", null ],
        [ "5.4 Sensor tuning table for STEREO", "d4/d64/page_drv_sensor.html#img_cv72_table_stereo", null ]
      ] ],
      [ "6. CV3 Sensor Tuning Table", "d4/d64/page_drv_sensor.html#CV3_sensor_tuning_table", [
        [ "6.1 Sensor tuning table for ROBOT", "d4/d64/page_drv_sensor.html#img_cv3_table_robot", null ],
        [ "6.2 Sensor tuning table for STEREO", "d4/d64/page_drv_sensor.html#img_cv3_table_stereo", null ]
      ] ],
      [ "7. License", "d4/d64/page_drv_sensor.html#sensor_lic", null ]
    ] ],
    [ "Sensor & SERDES Driver Installation", "d2/dcb/page_sys_sensor_driver_installation.html", [
      [ "0. Revision History", "d2/dcb/page_sys_sensor_driver_installation.html#Sensor_driver_installation_history", null ],
      [ "1. Sensor Driver Module Parameters", "d2/dcb/page_sys_sensor_driver_installation.html#sensor_driver_module_parameters", null ],
      [ "2. SERDES Driver Module Parameters", "d2/dcb/page_sys_sensor_driver_installation.html#serdes_driver_module_parameters", null ],
      [ "3. Driver Installation Guide", "d2/dcb/page_sys_sensor_driver_installation.html#driver_installation_guide", [
        [ "3.1 Dummy Sensor Driver Usage", "d2/dcb/page_sys_sensor_driver_installation.html#ambds_usage", null ],
        [ "3.2 Multiple Sensors with Different Sensor Types", "d2/dcb/page_sys_sensor_driver_installation.html#Multiple_Sensors_with_Different_Sensor_Types", null ],
        [ "3.3 Multiple Sensors with the Same Sensor Type", "d2/dcb/page_sys_sensor_driver_installation.html#Multiple_Sensors_with_the_same_sensor_type", null ],
        [ "3.4 Sensors with SERDES Bridge", "d2/dcb/page_sys_sensor_driver_installation.html#Sensors_with_SERDES_Bridge", [
          [ "Example 1.  Single ar0233_mipi_brg connects to MAX9296.", "d2/dcb/page_sys_sensor_driver_installation.html#example_serdes_connect1", null ],
          [ "Example 2 Dual ar0231_mipi_brg connects to ds90ub954.", "d2/dcb/page_sys_sensor_driver_installation.html#example_serdes_connect2", null ],
          [ "Example 3 Dual ar0231_mipi_brg connects to dual ds90ub954.", "d2/dcb/page_sys_sensor_driver_installation.html#example_serdes_connect3", null ],
          [ "Example 4 Single ar0231_mipi_brg and ar0239_mipi_brg connect to dual ds90ub954.", "d2/dcb/page_sys_sensor_driver_installation.html#example_serdes_connect4", null ],
          [ "Example 5 Single ar0231_mipi_brg and ar0239_mipi_brg connect to dual ds90ub954; ar0144_brg connects to max9288.", "d2/dcb/page_sys_sensor_driver_installation.html#example_serdes_connect5", null ],
          [ "Example 6 Quad os08a10_mipi_brg connects to dual MAX9296.", "d2/dcb/page_sys_sensor_driver_installation.html#example_serdes_connect6", null ],
          [ "Example 7 Set up dual sensors with different modes from MAX9296.", "d2/dcb/page_sys_sensor_driver_installation.html#example_serdes_connect7", null ]
        ] ],
        [ "3.5 Vsrc_id Reordering", "d2/dcb/page_sys_sensor_driver_installation.html#Vsrc_id_recordering", null ],
        [ "3.6 Keep Broken Vsrc_id", "d2/dcb/page_sys_sensor_driver_installation.html#keep_broken_vsrc_id", null ],
        [ "3.7 Specify Target Vsrc_num", "d2/dcb/page_sys_sensor_driver_installation.html#Specify_Target_Vsrc_num", null ]
      ] ],
      [ "4. Cooper EVK with Multi-VIN support", "d2/dcb/page_sys_sensor_driver_installation.html#cv5x_multi_vin_support", [
        [ "4.1 CV5 Multi-VIN Design", "d2/dcb/page_sys_sensor_driver_installation.html#CV5_Multi_VIN_Design", null ],
        [ "4.2 CV52 Multi-VIN Design", "d2/dcb/page_sys_sensor_driver_installation.html#CV52_Multi_VIN_Design", null ],
        [ "4.3 CV72 Multi-VIN Design", "d2/dcb/page_sys_sensor_driver_installation.html#CV72_Multi_VIN_Design", null ]
      ] ]
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
        [ "Functions", "globals_func.html", null ],
        [ "Variables", "globals_vars.html", null ],
        [ "Typedefs", "globals_type.html", null ],
        [ "Enumerations", "globals_enum.html", null ],
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
"d1/d7c/structiav__h26x__pskip.html",
"d2/d30/structamba__video__source__scale__analog__info.html#a284f607e598bbe87cc0239877ea0c944",
"d3/d21/structamba__video__source__info.html",
"d3/d5a/group__iav-common-helper.html#gga20dd04994a71c85d582d1e840001da92a3b18a9f58f2fb78460a39f66ca22fb93",
"d3/d5a/group__iav-common-helper.html#ggae1713c20e46dd967b9d34e7f8343f82ca47a8362b86e71e7c698e1a131dede5e1",
"d3/d5a/group__iav-common-helper.html#ggae1713c20e46dd967b9d34e7f8343f82cab3d3c746c4886cada156ecbeea6df65f",
"d3/d78/structvin__device.html#a053c255f65c46b4439c6b45b8b25b2bc",
"d3/de3/group__iav-ioctl-general-helper.html#ga9a2cebe518fc44379edfc76e214373ca",
"d3/de3/group__iav-ioctl-general-helper.html#gga0d4aa56417117a810935674737c2f2e7af9d47da19b1ccc4ec60a9e8af2d3bbe4",
"d3/de3/group__iav-ioctl-general-helper.html#gga2b04bbf59c35130f7771997d92f17b77a95fd99ac07882d63ba949ca916ed7555",
"d3/de3/group__iav-ioctl-general-helper.html#gga428a08cf3c46e0bd3847533c8a58e108a384dc06fbc99698e0a9f8bf991c85d9b",
"d3/de3/group__iav-ioctl-general-helper.html#gga68d3c468f240c5ea85764670809e8e1dab473578d1b8a29aeaad0d7b6d3b02c5e",
"d3/de3/group__iav-ioctl-general-helper.html#gga7179377f02346bad95a397884cdd1d62ad2d3acce1ee8b4e4b7962412817e7d1f",
"d3/de3/group__iav-ioctl-general-helper.html#gga9a2cebe518fc44379edfc76e214373caa93474ba2ea943e55482953af7bae3216",
"d3/de3/group__iav-ioctl-general-helper.html#ggab7b43864aa0865f1519a666c90870043a746e62d09436fe6139bc89f3813e3db7",
"d3/de3/group__iav-ioctl-general-helper.html#ggae758a91a8923f531a735d7dfb72ed361ae0a3a57cff4764516a6c8837db339b9a",
"d3/de9/vout__api_8h.html#ab533e57104080e6ec6f0847aaf8af011a565eeb4429eae7e67e9d64d555ddf610",
"d4/d86/page_drv_cavalry_doc.html#cavalry_license",
"d5/dfb/structiav__canvasdesc.html#a6174724560c4025946fb0498c0022a84",
"d6/d9f/group__cavalry-ioctl-helper.html#ga3c27dce892c18537712196ae1f508647",
"d6/da8/group__iav-ioctl-vout-helper.html#gga16685eea158879e41b101ca3634de462af971cb7f52b77c20209503bf4af15419",
"d6/da8/group__iav-ioctl-vout-helper.html#ggac81fbcefa2e12c0df5a3011c4de7d176add9f81bd5f19aa77be30ef021ab533e5",
"d7/d28/structvin__global__info.html",
"d8/d54/structamba__video__sink__mode.html#a6309fb7927b75e344191d7ceaf8150eb",
"d8/d8c/group__iav-ioctl-vin-helper.html#gga4caf8d8f829279fba122163d961608a4a0ac49390d847c5a765ae30da816dc7d5",
"d8/d8c/group__iav-ioctl-vin-helper.html#ggabe47c58eecc0d607bd1f67835c9bc18aa18d00775b244d9d484d749d88a1d3ee2",
"d8/d8c/group__iav-ioctl-vin-helper.html#ggabe47c58eecc0d607bd1f67835c9bc18aa75972500fe4d8acf985b054158def7e7",
"d8/d8c/group__iav-ioctl-vin-helper.html#ggabe47c58eecc0d607bd1f67835c9bc18aac14a8dc89311d77590c63f7df398ba14",
"d8/da5/structiav__vout__rotate__video__s.html#a0b95db0f87fcbe71c3bbda1fa359606f",
"d8/df3/ambas__stream__texture_8h.html#a5c3e31f5be9e3b951bff3db5eaf81caea97026dcf8428486716764dce55d1bcc9",
"d9/d42/structcavalry__status.html#aed93283265f941dc1d2bf8d634164493",
"d9/dbd/structamba__video__source__osd__clut__info.html",
"da/dae/structamba__video__info.html#add40f8a56ae8cc650f92a3aa4d2bac99",
"db/d87/vin__sensors_8h.html#af93e100dfa3a9e16ee98a55220e6f7a3",
"dc/d78/structiav__debug__cfg.html#a304b40c66feb75baeaca80cec543d241",
"dd/d71/structcavalry__clock__cfg.html#a523add199ececeb516171bbb139c41aa",
"de/d2c/structiav__h265__qproi__data.html#a28796ea8b2f99002f83d7e324a80083d",
"de/de0/structvin__ops.html#ad5a25c50368d4990a3e591c2017ef423",
"df/d7c/structio__descriptor__s.html#a1e7ec898642173fd06f13e64554d9399",
"functions_k.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';