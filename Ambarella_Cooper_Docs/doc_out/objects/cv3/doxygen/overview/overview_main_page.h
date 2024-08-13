
/*!
 * @mainpage notitle
 *
 * <h1>Cooper Linux SDK Overview</h1>
 *
 * - - - -
 * The Cooper Amba Linux SDK Overview's outline is below:
 * - @ref overview_proj 
 * - @ref doc_read_guide 
 * - @ref market_segments 
 * - @ref page_getting_start_guide 
 * - @ref ov_deliverables 
 * - @ref ov_code_build 
 * - @ref ov_sensor_bringup_guide 
 * - @ref ov_new_board_bringup_guide 
 * - @ref doc_abbr 

 *  - - - -
 *
 * The Cooper Hardware Documents will be organized as below:
 * - @ref hw_modules 
 * - @ref page_cv5_timn 
 * - @ref page_cv52_cocr 
 * - @ref page_cv72_gage 
 * - @ref page_cv72_xiezhi 
 * - @ref page_cv3_dk_mini 

 *  - - - -
 *
 * The Cooper Amyoc Documents will be organized as below:
 * - @ref doc_amyoc_introduction 
 * - @ref doc_amyoc_target 
 * - @ref doc_amyoc_ros2 
 * - @ref doc_amyoc_genv 
 * - @ref doc_amyoc_makefile 
 * - @ref doc_amyoc_dep 
 * - @ref doc_amyoc_oss 
 * - @ref doc_yocto_recipes 
 * - @ref doc_yocto_faq 

 *  - - - -
 *
 * The Cooper Driver Documents will be organized as below:
 * - @ref page_drv_cavalry_doc 
 * - @ref page_drv_cma_doc 
 * - @ref page_drv_iav_doc 
 * - @ref page_drv_sensor 
 * - @ref page_sys_sensor_driver_installation 

 *  - - - -
 *
 * The Cooper Library Documents will be organized as below:
 * - @ref page_lib_gstreamer_doc 
 * - @ref page_lib_asf_doc 
 * - @ref page_lib_cavalry_mem_doc 
 * - @ref page_lib_cavalry_opt_layers_doc 
 * - @ref page_lib_cgpp_doc 
 * - @ref page_lib_dproc_doc 
 * - @ref page_lib_depth_fw_doc 
 * - @ref page_lib_dewarp_doc 
 * - @ref page_lib_eazyai_doc 
 * - @ref page_lib_eis_doc 
 * - @ref page_lib_img_flow_doc 
 * - @ref page_lib_img_doc 
 * - @ref page_lib_nnctrl_doc 
 * - @ref page_lib_sensor_calib_doc 
 * - @ref page_lib_smartfb_doc 
 * - @ref page_lib_src_v3 
 * - @ref page_lib_stitch_doc 
 * - @ref page_lib_vproc_doc 
 * - @ref page_lib_vfunc_doc 
 * - @ref page_lib_vss_doc 
 * - @ref page_lib_pm_doc 
 * - @ref page_lib_vg_doc 

 *  - - - -
 *
 * The Cooper Video Documents will be organized as below:
 * - @ref fs_basic_vin 
 * - @ref fs_basic_vout 
 * - @ref fs_basic_raw 
 * - @ref fs_basic_channel 
 * - @ref fs_basic_source_buffer 
 * - @ref fs_basic_pyramid 
 * - @ref fs_basic_canvas 
 * - @ref fs_basic_stream 
 * - @ref fs_basic_codec 
 * - @ref fs_basic_gop 
 * - @ref fs_basic_on_the_fly 
 * - @ref fs_basic_pm 
 * - @ref fs_basic_blur 
 * - @ref fs_basic_overlay 
 * - @ref fs_basic_playback 
 * - @ref fs_basic_duplex 
 * - @ref fs_basic_data_dump 
 * - @ref fs_basic_fps 
 * - @ref fs_basic_hdr 
 * - @ref fs_adv_enc_mode 
 * - @ref fs_adv_lua 
 * - @ref fd_adv_multi_vin 
 * - @ref fs_adv_multi_pass 
 * - @ref fs_adv_ldc 
 * - @ref fs_adv_dewarp 
 * - @ref fs_adv_vl 
 * - @ref fs_adv_arb_img_scaler 
 * - @ref fs_adv_efm 
 * - @ref fs_adv_efr 
 * - @ref fs_adv_pl_latency 
 * - @ref fs_adv_iav_poll 
 * - @ref fs_adv_customized_features 
 * - @ref fs_adv_bypass_idsp_for_yuv_input 
 * - @ref iq_lite_nn 
 * - @ref fs_others_debug 
 * - @ref fs_others_miscellaneous 
 * - @ref fs_others_faq 
 * - @ref fs_others_dsp_monitor_service 
 * - @ref fs_others_ucode 

 *  - - - -
 *
 * The Cooper Security Documents will be organized as below:
 * - @ref security_overview 
 * - @ref sys_integrity_protection 
 * - @ref system_reinforcement 
 * - @ref data_storage_protection 
 * - @ref data_transfer_protection 
 * - @ref system_integrity_protection 
 * - @ref user_privacy_protection 
 * - @ref secure_hardware 
 * - @ref key_management 
 * - @ref crypto_performance 
 * - @ref design_guide 
 * - @ref security_validation_guide 
 * - @ref migration_guide 

 *  - - - -
 *
 * The Cooper System Documents will be organized as below:
 * - @ref page_sys_mg_cv2x 
 * - @ref page_sys_mg_legacy 
 * - @ref page_sysdoc_amboot_doc 
 * - @ref page_sysdoc_kernel_doc 
 * - @ref page_sysdoc_rootfs_doc 
 * - @ref page_sysdoc_cm3_doc 
 * - @ref page_sysdoc_multi_cluster 
 * - @ref page_sysdoc_lychee_os 
 * - @ref si_boot_upgrade 
 * - @ref page_sys_hw_pts_doc 
 * - @ref page_sys_fastboot 
 * - @ref page_sensor_calib_user_guide_doc 
 * - @ref page_sys_docker 
 * - @ref page_sys_porting_ubuntu_doc 
 * - @ref page_sys_dram_opt_doc 
 * - @ref page_sys_pm 
 * - @ref page_sys_cooperhome 
 * - @ref page_sys_dram_stat 
 * - @ref sys_debug_tool 
 * - @ref page_sys_faq_doc 

 *  - - - -
 *
 * The Cooper Peripherals Documents will be organized as below:
 * - @ref si_audio 
 * - @ref si_fs 
 * - @ref si_nand 
 * - @ref si_emmc 
 * - @ref si_debugfs 
 * - @ref si_usb 
 * - @ref si_sd_card 
 * - @ref si_wifi 
 * - @ref si_bluetooth 
 * - @ref si_spi 
 * - @ref si_i2c 
 * - @ref pci_express 
 * - @ref si_ethernet 
 * - @ref si_ptp 
 * - @ref si_miscellaneous 
 * - @ref si_jtag 
 * - @ref si_temperature 

 *  - - - -
 *
 * The Cooper Applications Documents will be organized as below:
 * - @ref acc_ctrl_page 
 * - @ref beetle_page 
 * - @ref aibox_page 
 * - @ref mvvc_page 
 * - @ref multi_vin_bind_page 

 *  - - - -
 *
 * The Cooper Doxygen Style Guide Documents will be organized as below:
 * - @ref doc_style_guide 
 *
 */
