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
  [ "System", "index.html", [
    [ "Migration Guide From CV2x", "d9/dc6/page_sys_mg_cv2x.html", [
      [ "0. Revision History", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_cv2x_history", null ],
      [ "1. Overview", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_overview", null ],
      [ "2. Hardware", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_hw", [
        [ "2.1 Main Differences", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_hw_main_diff", null ],
        [ "2.2 Digital Signal Processor Differences", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_hw_dsp_diff", null ],
        [ "2.3 CV5 Timn Board", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_hw_timn_board", [
          [ "2.3.1 Board Configuration", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_hw_timn_board_cfg", null ]
        ] ],
        [ "2.4 CV72 Ga Board", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_hw_ga_board", null ]
      ] ],
      [ "3. Software", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw", [
        [ "3.1 Application Programming Interface Differences", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff", [
          [ "3.1.1 System Resources", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_sysres", null ],
          [ "3.1.2 Canvas Number", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_canvas_num", null ],
          [ "3.1.3 Stream Number", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_stream_num", null ],
          [ "3.1.4 Blur Insertion", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_blur_insertion", null ],
          [ "3.1.5 Electronic Image Stabilization", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_eis", null ],
          [ "3.1.6 Arbitrary Image Scaler", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_img_scale", null ],
          [ "3.1.7 Multi-Pass", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_multi_pass", null ],
          [ "3.1.8 Custom SEI", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_custom_sei", null ],
          [ "3.1.9 RAW fps", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_api_diff_raw_fps", null ]
        ] ],
        [ "3.2 Memory Access", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_mem_access", [
          [ "3.2.1 Accessing Canvas Data from CV Applications", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_sw_mem_access_cv", null ]
        ] ]
      ] ],
      [ "4. Input / Output Control Interface", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface", [
        [ "4.1 IAV_IOC_QUERY_INFO", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_query_info", null ],
        [ "4.2 IAV_IOC_SET_DSP_LOG", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_set_dsp_log", null ],
        [ "4.3 IAV_IOC_DRV_DSP_INFO", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_drv_dsp_info", null ],
        [ "4.4 IAV_IOC_SET_SYSTEM_RESOURCE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_sys_res", null ],
        [ "4.5 IAV_IOC_GET_SYSTEM_RESOURCE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_sys_res", null ],
        [ "4.6 IAV_IOC_SET_CHAN_CONFIG", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_chan_cfg", null ],
        [ "4.7 IAV_IOC_GET_CHAN_CONFIG", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_chan_cfg", null ],
        [ "4.8 IAV_IOC_SET_CANVAS_CONFIG", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_canvas_cfg", null ],
        [ "4.9 IAV_IOC_GET_CANVAS_CONFIG", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_canvas_cfg", null ],
        [ "4.10 IAV_IOC_SET_STREAM_RESOURCE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_stream_res", null ],
        [ "4.11 IAV_IOC_GET_STREAM_RESOURCE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_stream_res", null ],
        [ "4.12 IAV_IOC_QUERY_ENC_MODE_CAP", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_query_encmode", null ],
        [ "4.13 IAV_IOC_ENTER_IDLE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_enter_idle", null ],
        [ "4.14 IAV_IOC_SET_MEM_LAYOUT_RESOURCE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_mem_layout_res", null ],
        [ "4.15 IAV_IOC_GET_MEM_LAYOUT_RESOURCE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_mem_layout_res", null ],
        [ "4.16 IAV_IOC_QUERY_MEM_LAYOUT_INFO", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_query_mem_layout", null ],
        [ "4.17 IAV_IOC_QUERY_DESC", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_query_desc", null ],
        [ "4.18 IAV_IOC_CFG_VIDEO_PROC", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_cfg_video_proc", null ],
        [ "4.19 IAV_IOC_GET_VIDEO_PROC", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_video_proc", null ],
        [ "4.20 IAV_IOC_SET_RAW_ENC_CFG", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_raw_enc_cfg", null ],
        [ "4.21 IAV_IOC_SET_RAW_ENCODE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_raw_encode", null ],
        [ "4.22 IAV_IOC_GET_RAW_ENCODE", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_raw_encode", null ],
        [ "4.23 IAV_IOC_SET_STREAM_CONFIG", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_stream_cfg", null ],
        [ "4.24 IAV_IOC_GET_ STREAM_CONFIG", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_stream_cfg", null ],
        [ "4.25 IAV_IOC_SET_BLUR_INSERT", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_s_blur_insert", null ],
        [ "4.26 IAV_IOC_GET_BLUR_INSERT", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_g_blur_insert", null ],
        [ "4.27 IAV_IOC_APPLY_FRAME_SYNC_PROC", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_fram_sync_proc", null ],
        [ "4.28 IAV_IOC_QUERY_MEMBLOCK", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_query_memblock", null ],
        [ "4.29 IAV_IOC_EFM_HANDSHAKE_FRAME", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_efm_hsk_frm", null ],
        [ "4.30 IAV_IOC_EFM_SET_EXT_POOL", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_efm_set_ext_pool", null ],
        [ "4.31 Deprecated or Unsupported IOCTLs", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_ioctl_interface_depre_or_unsupport_ioc", null ]
      ] ],
      [ "5. Unit Test", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_unit_test", [
        [ "5.1 test_encode", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_unit_test_encode", null ]
      ] ],
      [ "6. Tools", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_tools", [
        [ "6.1 Firmware Upgrade", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_tools_fw_upgrade", null ],
        [ "6.2 Toolchain for Linux", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_tools_linux", null ],
        [ "6.3 Toolchain for the CVflow Processor", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_tools_cvflow_processor", null ]
      ] ],
      [ "7. Frequently Asked Questions (FAQ)", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_faq", null ],
      [ "8. License", "d9/dc6/page_sys_mg_cv2x.html#sys_mg_license", null ]
    ] ],
    [ "Migration Guide from CV5x Legacy SDK", "dc/dd9/page_sys_mg_legacy.html", [
      [ "0. Revision History", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_history", null ],
      [ "1. Overview", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_overview", null ],
      [ "2. Highlights for DSP APIs", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_highlights", [
        [ "2.1 Highlights for DSP APIs in SDK 1.6", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_highlights_1_6", null ],
        [ "2.2 Highlights for DSP APIs in SDK 1.5", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_highlights_1_5", null ]
      ] ],
      [ "3. Software", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw", [
        [ "3.1 Application Programming Interface (API) Differences", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw_api_diff", [
          [ "3.1.1 Blur Insertion", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw_api_diff_blur_insertion", null ],
          [ "3.1.2 Multi-VIN Stitching", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw_api_diff_multi_vin", null ],
          [ "3.1.3 Arbitrary Image Scaler", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw_api_diff_img_scale", null ],
          [ "3.1.4 Seventh Preview Buffer", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw_api_diff_seventh_buf", null ],
          [ "3.1.5 Electronic Image Stabilization", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw_api_diff_eis", null ],
          [ "3.1.6 Overlay", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw_api_diff_overlay", null ],
          [ "3.1.7 VOUT", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_sw_api_diff_vout", null ]
        ] ]
      ] ],
      [ "4. Input / Output Control (IOCTL) Interface", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_ioctl_interface", [
        [ "4.1 IAV_IOC_SET_CHAN_CONFIG", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_ioctl_interface_s_chan_cfg", null ],
        [ "4.2 IAV_IOC_GET_CHAN_CONFIG", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_ioctl_interface_g_chan_cfg", null ],
        [ "4.3 IAV_IOC_SET_SYSTEM_RESOURCE", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_ioctl_interface_s_system_resource", null ],
        [ "4.4 IAV_IOC_GET_SYSTEM_RESOURCE", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_ioctl_interface_g_system_resource", null ]
      ] ],
      [ "5. Tools", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_tools", null ],
      [ "6. Frequently Asked Questions (FAQ)", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_faq", null ],
      [ "7. License", "dc/dd9/page_sys_mg_legacy.html#sys_mg_lgc_license", null ]
    ] ],
    [ "BASE - AMBoot", "d6/d3a/page_sysdoc_amboot_doc.html", [
      [ "0. Revision History", "d6/d3a/page_sysdoc_amboot_doc.html#amboot_doc_history", null ],
      [ "1. AMBoot Documents Introduction", "d6/d3a/page_sysdoc_amboot_doc.html#amboot_doc_intro", [
        [ "1.1 BST & Memory Documents", "d6/d3a/page_sysdoc_amboot_doc.html#amboot_mem", null ],
        [ "1.2 Amrtos Documents", "d6/d3a/page_sysdoc_amboot_doc.html#amboot_amrtos", null ],
        [ "1.3 Security Documents", "d6/d3a/page_sysdoc_amboot_doc.html#amboot_secure", null ],
        [ "1.4 Storage & File System Documents", "d6/d3a/page_sysdoc_amboot_doc.html#amboot_fs", null ]
      ] ],
      [ "2. License", "d6/d3a/page_sysdoc_amboot_doc.html#amboot_doc_license", null ]
    ] ],
    [ "BASE - Kernel", "d3/d7b/page_sysdoc_kernel_doc.html", [
      [ "2. License", "d3/d7b/page_sysdoc_kernel_doc.html#kernel_doc_license", null ]
    ] ],
    [ "BASE - Rootfs", "df/d7f/page_sysdoc_rootfs_doc.html", [
      [ "0. Revision History", "df/d7f/page_sysdoc_rootfs_doc.html#rootfs_doc_history", null ],
      [ "1. Rootfs Introduction", "df/d7f/page_sysdoc_rootfs_doc.html#si_rootfs_doc_intro", null ],
      [ "2. Rootfs Guidance", "df/d7f/page_sysdoc_rootfs_doc.html#si_rootfs_build", [
        [ "2.1 UBIFS Guidance", "df/d7f/page_sysdoc_rootfs_doc.html#si_ubifs_guide", null ],
        [ "2.2 RAMDisk Guidance", "df/d7f/page_sysdoc_rootfs_doc.html#si_ramdisk_guide", null ]
      ] ],
      [ "3. License", "df/d7f/page_sysdoc_rootfs_doc.html#si_rootfs_doc_license", null ]
    ] ],
    [ "BASE - CM3", "d1/d5e/page_sysdoc_cm3_doc.html", [
      [ "0. Revision History", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_history", null ],
      [ "1. Overview", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_overview", null ],
      [ "2. FreeRTOS", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_freertos", null ],
      [ "3. Configuration", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_configuration", [
        [ "3.1 Toolchain", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_toolchain", null ],
        [ "3.2 Board Configuration", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_board_config", null ]
      ] ],
      [ "4. Driver", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver", [
        [ "4.1 Remote Processor Messaging Framework", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver_rpmsg", [
          [ "4.1.1 Board Configuration", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver_rpmsg_board_config", null ],
          [ "4.1.2 Kernel Configuration", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver_rpmsg_kernel_config", null ],
          [ "4.1.3 Device Tree", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver_rpmsg_device_tree", null ],
          [ "4.1.4 Unit Test", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver_rpmsg_unit_test", null ]
        ] ],
        [ "4.2 Serial Peripheral Interface", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver_spi", [
          [ "4.2.1 Device Tree", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver_spi_device_tree", null ],
          [ "4.2.2 Unit Test", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_driver_spi_unit_test", null ]
        ] ]
      ] ],
      [ "5. License", "d1/d5e/page_sysdoc_cm3_doc.html#cm3_license", null ]
    ] ],
    [ "BASE - Multi-Clusters", "df/d1e/page_sysdoc_multi_cluster.html", [
      [ "0. Revision History", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_doc_history", null ],
      [ "1. Multi-Clusters Introduction", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_intro", [
        [ "1.1 Introduction", "df/d1e/page_sysdoc_multi_cluster.html#Multi-multi_cluster_s1", null ]
      ] ],
      [ "2. Design", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_design", [
        [ "2.1 Memory Layout", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_design_mem_layout", null ],
        [ "2.2 IO Resource", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_design_io_res", null ],
        [ "2.3 Boot Flow", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_design_boot_flow", null ]
      ] ],
      [ "3. Blazenet", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_blazenet_driver", null ],
      [ "4. NFS Rootfs", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_nfs_rootfs", null ],
      [ "5. Boot Multiple Clusters for CV3 Dk_mini", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_boot", [
        [ "5.1 Build", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_boot_build", null ],
        [ "5.2 Burn the Firmware", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_boot_burn_fw", null ],
        [ "5.3 Make Rootfs", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_boot_make_rootfs", null ]
      ] ],
      [ "6. Cavalry in Multi-Cluster", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_cavalry", [
        [ "6.1 Memory Setup", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_cvr_mem_setup", null ],
        [ "6.2 Limitations", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_cvr_limitations", null ]
      ] ],
      [ "7. License", "df/d1e/page_sysdoc_multi_cluster.html#multi_cluster_license", null ]
    ] ],
    [ "BASE - Lychee OS", "dc/da7/page_sysdoc_lychee_os.html", [
      [ "1. Lychee OS Introduction", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_intro", [
        [ "1.1 What is LycheeOS", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_what_is_lycheeos", null ],
        [ "1.2 Deploy and Develop in One Box", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_deploy_and_develop_in_one_box", null ],
        [ "1.3 Native Compile Ambarella private Drivers and Application", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_native_compile_amba_private_drivers_and_app", null ]
      ] ],
      [ "2. Install Lychee OS on CV3", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_install_lycheeos_on_cv3", [
        [ "2.1 Flash Uboot", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_burn_uboot", null ],
        [ "2.2 Install Lychee OS to an SD Card", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_install_lychee_to_sd_card", null ],
        [ "2.3 The First Boot Lychee OS", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_install_lychee_the_first_boot_lychee_os", null ]
      ] ],
      [ "3. Login Settings", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_the_first_login_settings", null ],
      [ "4. Setup Local SDK Repo", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_the_local_sdk_repo_setup_guide", null ],
      [ "5. Command Reference : dnf / rpm", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_dnf_command_reference", null ],
      [ "6. License", "dc/da7/page_sysdoc_lychee_os.html#lychee_os_license", null ]
    ] ],
    [ "DESIGN - Boot & Upgrade", "dc/d8f/si_boot_upgrade.html", [
      [ "0. Revision History", "dc/d8f/si_boot_upgrade.html#boot_upgrade_doc_history", null ],
      [ "1. Partition", "dc/d8f/si_boot_upgrade.html#si_partition", [
        [ "1.1 Flexible Firmware Layout", "dc/d8f/si_boot_upgrade.html#si_flexible_firmware_layout", null ],
        [ "1.2 Legacy Firmware Layout", "dc/d8f/si_boot_upgrade.html#si_legacy_firmware_layout", null ]
      ] ],
      [ "2. Boot", "dc/d8f/si_boot_upgrade.html#si_boot", [
        [ "2.1 Normal Boot", "dc/d8f/si_boot_upgrade.html#si_normal_boot", [
          [ "2.1.1 Normal Boot Flow", "dc/d8f/si_boot_upgrade.html#si_normal_boot_flow", null ]
        ] ],
        [ "2.2 Secure Boot", "dc/d8f/si_boot_upgrade.html#si_secure_boot", [
          [ "2.2.1 Secure Boot Flow", "dc/d8f/si_boot_upgrade.html#si_secure_boot_flow", null ],
          [ "2.2.2 Key Management", "dc/d8f/si_boot_upgrade.html#si_secure_boot_key_mgr", null ],
          [ "2.2.3 Enable OTP", "dc/d8f/si_boot_upgrade.html#si_secure_boot_en_otp", null ]
        ] ]
      ] ],
      [ "3. Upgrade", "dc/d8f/si_boot_upgrade.html#si_upgrade", [
        [ "3.1 Firmware and Image", "dc/d8f/si_boot_upgrade.html#si_fw_and_image", null ],
        [ "3.2 TFTP Upgrade", "dc/d8f/si_boot_upgrade.html#si_tftp_upgrade", [
          [ "3.2.1 TFTP Upgrade Methods", "dc/d8f/si_boot_upgrade.html#si_tftp_upgrade_methods", null ],
          [ "3.2.2 Example: TFTP Upgrade", "dc/d8f/si_boot_upgrade.html#si_tftp_upgrade_example", null ]
        ] ],
        [ "3.3 SD Upgrade", "dc/d8f/si_boot_upgrade.html#si_sd_upgrade", [
          [ "3.3.1 Images for SD Upgrade", "dc/d8f/si_boot_upgrade.html#si_sd_upgrade_images", null ],
          [ "3.3.2 Example: SD Upgrading the Partitions", "dc/d8f/si_boot_upgrade.html#si_sd_upgrade_example", null ]
        ] ],
        [ "3.4 Image Upgrade", "dc/d8f/si_boot_upgrade.html#si_image_upgrade", [
          [ "3.4.1 Image Upgrade Modes", "dc/d8f/si_boot_upgrade.html#si_image_upgrade_modes", null ],
          [ "3.4.2 Images for Upgrading", "dc/d8f/si_boot_upgrade.html#si_images_for_upgrading", null ],
          [ "3.4.3 The Upgrade Tool", "dc/d8f/si_boot_upgrade.html#si_image_upgrade_tool", null ],
          [ "3.4.4 Digital Signature (Optional)", "dc/d8f/si_boot_upgrade.html#si_image_upgrade_signature", null ],
          [ "3.4.5 AB Upgrade Example for Flexible Firmware Layout", "dc/d8f/si_boot_upgrade.html#si_ab_flex_upgrade", null ],
          [ "3.4.6 PBA Upgrade Example for Flexible Firmware Layout", "dc/d8f/si_boot_upgrade.html#si_pba_flex_upgrade", null ],
          [ "3.4.7 AB Upgrade Example for Legacy Firmware Layout", "dc/d8f/si_boot_upgrade.html#si_ab_legacy_upgrade", null ],
          [ "3.4.8 PBA Upgrade Example for Legacy Firmware Layout", "dc/d8f/si_boot_upgrade.html#si_pba_legacy_upgrade", null ]
        ] ]
      ] ],
      [ "4. Partition Auto Recovery", "dc/d8f/si_boot_upgrade.html#si_partition_auto_recovery", [
        [ "4.1 Partition Auto-Recovery Introduction", "dc/d8f/si_boot_upgrade.html#si_partition_auto_recovery_introduction", [
          [ "4.2 Example: Build the Recovery Image", "dc/d8f/si_boot_upgrade.html#si_build_recovery_image_example", null ],
          [ "4.3 Example: Partition Auto-Recovery Test", "dc/d8f/si_boot_upgrade.html#si_partition_auto_recovery_test", null ],
          [ "4.4 MCU Communication Protocol Introduction", "dc/d8f/si_boot_upgrade.html#si_mcu_communication_protocol_introduction", null ]
        ] ]
      ] ]
    ] ],
    [ "DESIGN - Timer & PTS", "d2/dcb/page_sys_hw_pts_doc.html", [
      [ "0. Revision History", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_history", null ],
      [ "1. Overview", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_overview", null ],
      [ "2. Hardware Timer", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_hw", [
        [ "2.1 Implementation", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_hw_implementation", null ],
        [ "2.2 Sychronized with System Timer", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_timer_sync", null ],
        [ "2.3 Usage", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_hw_usage", null ]
      ] ],
      [ "3. Clock Sources", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_clock_source", null ],
      [ "4. Audio PTS", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_audio", [
        [ "4.1 Implementation", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_audio_implementation", null ]
      ] ],
      [ "5. Video PTS", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_video", [
        [ "5.1 Implementation", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_video_implementation", null ],
        [ "5.2 PTS for Output Data in Each Stage", "d2/dcb/page_sys_hw_pts_doc.html#pts_in_each_idsp_vdsp_domain", null ],
        [ "5.3 PTS Clock Sources", "d2/dcb/page_sys_hw_pts_doc.html#PTS_clock_source", null ],
        [ "5.4 Different PTS Categories", "d2/dcb/page_sys_hw_pts_doc.html#different_PTS_categories", null ],
        [ "5.5 PTS for Different Sychronization Scenarios", "d2/dcb/page_sys_hw_pts_doc.html#PTS_for_different_sychronization_scenarios", null ]
      ] ],
      [ "6. Use Scenarios for PTS", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_use_scenario", [
        [ "6.1 Audio and Video Synchronization", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_av_sync", null ],
        [ "6.2 Frame Synchronization Mechanism", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_frame_sync", null ]
      ] ],
      [ "7. Stream Encode Done PTS", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_encode", [
        [ "7.1 Information", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_encode_info", null ],
        [ "7.2 Usage", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_encode_usage", null ]
      ] ],
      [ "8. License", "d2/dcb/page_sys_hw_pts_doc.html#hw_pts_license", null ]
    ] ],
    [ "DESIGN - Fast Boot", "d1/dd3/page_sys_fastboot.html", [
      [ "0. Revision History", "d1/dd3/page_sys_fastboot.html#fastboot_history", null ],
      [ "1. Introduction", "d1/dd3/page_sys_fastboot.html#sys_fb_intro", null ],
      [ "2. Cold Boot", "d1/dd3/page_sys_fastboot.html#sys_fb_cold_boot", [
        [ "2.1 Outline", "d1/dd3/page_sys_fastboot.html#clean_boot_outline", null ],
        [ "2.2 System Startup Script Optimization Method", "d1/dd3/page_sys_fastboot.html#clean_boot_script", [
          [ "2.2.1 Load Necessary Module Drivers in Parallel", "d1/dd3/page_sys_fastboot.html#script_optimization_parallel", null ],
          [ "2.2.2 Compile Optimized Scripts in the SDK", "d1/dd3/page_sys_fastboot.html#script_optimization_compile", null ]
        ] ],
        [ "2.3 System Tailoring", "d1/dd3/page_sys_fastboot.html#clean_boot_system", [
          [ "2.3.1 Reduce File System Size", "d1/dd3/page_sys_fastboot.html#file_system_size", null ],
          [ "2.3.2 Reduce Linux Kernel Size", "d1/dd3/page_sys_fastboot.html#kernel_size", null ],
          [ "2.3.3 Select SquashFS as Rootfs", "d1/dd3/page_sys_fastboot.html#squashfs_select", null ],
          [ "2.3.4 Reduce System Startup Serial Port Printing", "d1/dd3/page_sys_fastboot.html#console_log", null ]
        ] ],
        [ "2.4 Other Optimization Measures", "d1/dd3/page_sys_fastboot.html#clean_boot_others", [
          [ "2.4.1 Reduce Delay of Peripheral Driver Loading", "d1/dd3/page_sys_fastboot.html#others_reduce_delay", null ],
          [ "2.4.2 Increase I2C Clock Frequency", "d1/dd3/page_sys_fastboot.html#others_increase_i2c_clock", null ],
          [ "2.4.3 Adjust NAND Timing", "d1/dd3/page_sys_fastboot.html#others_nand_timing", null ],
          [ "2.4.4 Adjust eMMC Power-On Configuration as HS200 8-bit Mode", "d1/dd3/page_sys_fastboot.html#others_emmc_boot", null ]
        ] ],
        [ "2.5 Testing Process", "d1/dd3/page_sys_fastboot.html#clean_boot_test", null ],
        [ "2.6 Example", "d1/dd3/page_sys_fastboot.html#clean_boot_example", null ]
      ] ],
      [ "3. DRAM Self-Refresh", "d1/dd3/page_sys_fastboot.html#sys_fb_dram_refresh", [
        [ "3.1 Self-Refresh Workflow", "d1/dd3/page_sys_fastboot.html#sys_pm_dram_flow", [
          [ "3.1.1 Self-Refresh Resume Workflow", "d1/dd3/page_sys_fastboot.html#sys_pm_dram_resume_flow", null ],
          [ "3.1.2 Self-Refresh Suspend Workflow", "d1/dd3/page_sys_fastboot.html#sys_pm_dram_suspend_flow", null ]
        ] ],
        [ "3.2 Hardware Configuration", "d1/dd3/page_sys_fastboot.html#sys_pm_hw_config", [
          [ "3.2.1 Power Control", "d1/dd3/page_sys_fastboot.html#sys_pm_hw_powctl", null ],
          [ "3.2.2 INI File", "d1/dd3/page_sys_fastboot.html#sys_pm_hw_ini", null ]
        ] ],
        [ "3.3 Prepare the Image", "d1/dd3/page_sys_fastboot.html#sys_pm_preimg", null ],
        [ "3.4 Running DRAM Self-Refresh", "d1/dd3/page_sys_fastboot.html#sys_pm_run_dram", [
          [ "3.4.1 Preparing the Hardware", "d1/dd3/page_sys_fastboot.html#sys_pm_run_dram_prehw", null ],
          [ "3.4.2 Enter Into Self-Refresh", "d1/dd3/page_sys_fastboot.html#sys_pm_run_dram_entersr", null ],
          [ "3.4.3 Resume from Self-Refresh", "d1/dd3/page_sys_fastboot.html#sys_pm_run_dram_resume", null ]
        ] ]
      ] ],
      [ "4. License", "d1/dd3/page_sys_fastboot.html#fastboot_license", null ]
    ] ],
    [ "DESIGN - Multiple Sensors Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html", [
      [ "0. Revision History", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_history", null ],
      [ "1. Introduction", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_introduction", null ],
      [ "2. Calibration Preparation Work", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_preparation", [
        [ "2.1 Preparing Work", "d9/d68/page_sensor_calib_user_guide_doc.html#sensor_calib_prepare", [
          [ "2.1.1 Host Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#sensor_calib_prepare_host", null ],
          [ "2.1.2 Board Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#sensor_calib_prepare_board", null ],
          [ "2.1.3 Pattern Preparing Work", "d9/d68/page_sensor_calib_user_guide_doc.html#sensor_calib_prepare_pat", null ]
        ] ]
      ] ],
      [ "3. Lens Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_lens", [
        [ "3.1 Lens Calibration Principle", "d9/d68/page_sensor_calib_user_guide_doc.html#lens_calib_principle", null ],
        [ "3.2 Lens Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#lens_calib_tool", null ],
        [ "3.3 Lens Calibration Flow", "d9/d68/page_sensor_calib_user_guide_doc.html#lens_calib_flow", null ],
        [ "3.4 Lens Calibration Result", "d9/d68/page_sensor_calib_user_guide_doc.html#lens_calib_result", null ]
      ] ],
      [ "4. ToF Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_tof", [
        [ "4.1 ToF Calibration Principle", "d9/d68/page_sensor_calib_user_guide_doc.html#tof_principle", null ],
        [ "4.2 ToF Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#tof_tool", null ],
        [ "4.3 ToF Calibration Flow", "d9/d68/page_sensor_calib_user_guide_doc.html#tof_flow", [
          [ "4.3.1 Temperature Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#sensor_calibtof_temp_calib", null ],
          [ "4.3.2 Global Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#sensor_calibtof_global_calib", null ],
          [ "4.3.3 Wiggling Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#sensor_calibtof_wiggle_calib", null ]
        ] ],
        [ "4.4 ToF Calibration Result", "d9/d68/page_sensor_calib_user_guide_doc.html#tof_result", null ]
      ] ],
      [ "5. RGBD Registration Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_tof_rgbd", [
        [ "5.1 RGBD Registration Calibration Principle", "d9/d68/page_sensor_calib_user_guide_doc.html#rgbd_principle", null ],
        [ "5.2 RGBD Registration Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#rgbd_tool", null ],
        [ "5.3 RGBD Registration Flow", "d9/d68/page_sensor_calib_user_guide_doc.html#rgbd_flow", null ],
        [ "5.4 RGBD Registration Result", "d9/d68/page_sensor_calib_user_guide_doc.html#rgbd_result", null ]
      ] ],
      [ "6. Multi-sensor Stitching Pose Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_stitch", [
        [ "6.1 Multi-sensor Stitching Pose Calibration Principle", "d9/d68/page_sensor_calib_user_guide_doc.html#stitching_pose_principle", null ],
        [ "6.2 Multi-sensor Stitching Pose Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#stitching_pose_tool", null ],
        [ "6.3 Stitching Pose Calibration Flow", "d9/d68/page_sensor_calib_user_guide_doc.html#stitching_pose_flow", null ],
        [ "6.4 Multi-Channel Stitching Example", "d9/d68/page_sensor_calib_user_guide_doc.html#stitching_cmd_list", [
          [ "6.4.1 Four-channel Stitching Example", "d9/d68/page_sensor_calib_user_guide_doc.html#stitching_pose_result", null ]
        ] ]
      ] ],
      [ "7. Thermal-RGB Fusion FoV-Alignment Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_thermal_rgb", [
        [ "7.1 Thermal-RGB Fusion FoV-Alignment Calibration Principle", "d9/d68/page_sensor_calib_user_guide_doc.html#thermal_rgb_principle", null ],
        [ "7.2 Thermal-RGB Fusion FoV-Alignment Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#thermal_rgb_tool", null ],
        [ "7.3 Thermal-RGB Fusion FoV-Alignment Calibration Flow", "d9/d68/page_sensor_calib_user_guide_doc.html#thermal_rgb_flow", null ],
        [ "7.4 Thermal-RGB Fusion FoV-Alignment Calibration Result", "d9/d68/page_sensor_calib_user_guide_doc.html#thermal_rgb_result", null ]
      ] ],
      [ "8. Mono-RGB Fusion FoV-Alignment Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_mono_rgb", [
        [ "8.1 Mono-RGB Fusion FoV-Alignment Calibration Principle", "d9/d68/page_sensor_calib_user_guide_doc.html#mono_rgb_principle", null ],
        [ "8.2 Mono-RGB Fusion FoV-Alignment Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#mono_rgb_tool", null ],
        [ "8.3 Mono-RGB Fusion FoV-Alignment Calibration Flow", "d9/d68/page_sensor_calib_user_guide_doc.html#mono_rgb_flow", null ],
        [ "8.4 Mono-RGB Fusion FoV-Alignment Calibration Result", "d9/d68/page_sensor_calib_user_guide_doc.html#mono_rgb_result", null ]
      ] ],
      [ "9. Structured-light Parameters Pose Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_structure_light", [
        [ "9.1 Structured-light Pose Parameters Calibration Principle", "d9/d68/page_sensor_calib_user_guide_doc.html#sl_pose_principle", null ],
        [ "9.2 Structured-light Pose Parameters Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#sl_pose_tool", null ],
        [ "9.3 Structured-light Pose Parameters Calibration Flow", "d9/d68/page_sensor_calib_user_guide_doc.html#sl_pose_flow", null ],
        [ "9.4 Structured-light Pose Parameters Calibration Result", "d9/d68/page_sensor_calib_user_guide_doc.html#sl_pose_result", null ]
      ] ],
      [ "10. Dual-fisheye back to back Pose Calibration", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_dual_fish", [
        [ "10.1 Dual-fisheye Pose Calibration Principle", "d9/d68/page_sensor_calib_user_guide_doc.html#ds_pose_principle", null ],
        [ "10.2 Dual-fisheye Pose Calibration Tool", "d9/d68/page_sensor_calib_user_guide_doc.html#ds_pose_tool", null ],
        [ "10.3 Dual-fisheye Pose Calibration Flow", "d9/d68/page_sensor_calib_user_guide_doc.html#ds_pose_flow", null ],
        [ "10.4 Dual-fisheye Pose Calibration Result", "d9/d68/page_sensor_calib_user_guide_doc.html#ds_pose_result", null ]
      ] ],
      [ "11. Sensor Calibration FAQ", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_faq", [
        [ "Question 1 How to ensure the lens calibration quality?", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_faq_q1", null ],
        [ "Question 2 What is the minimum number of images required for the fast lens calibration?", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_faq_q2", null ],
        [ "Question 3 Can Lens calibration work well with multiple patterns in one image?", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_faq_q3", null ],
        [ "Question 4 How to ensure the stitching pose calibration quality?", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_faq_q4", null ],
        [ "Question 5 What's the mass production strategy for multi-VIN stitching?", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_faq_q5", null ],
        [ "Question 6 How to ensure the thermal-RGB fusion FoV-alignment calibration quality?", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_faq_q6", null ],
        [ "Question 7 How to avoid image size mismatching between different channels for multi-VIN stitching?", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_faq_q7", null ]
      ] ],
      [ "12. License", "d9/d68/page_sensor_calib_user_guide_doc.html#guide_sensor_calib_lic", null ]
    ] ],
    [ "DESIGN - Docker Usage Guide", "dc/d4a/page_sys_docker.html", [
      [ "0. Revision History", "dc/d4a/page_sys_docker.html#docker_history", null ],
      [ "1. Overview", "dc/d4a/page_sys_docker.html#docker_ov", [
        [ "1.1 About Docker", "dc/d4a/page_sys_docker.html#docker_about", null ]
      ] ],
      [ "2. Build the Firmware for the CV5x Evaluation Kit (EVK)", "dc/d4a/page_sys_docker.html#docker_build_cv5", null ],
      [ "3. Build the Firmware for the CV72 EVK", "dc/d4a/page_sys_docker.html#docker_build_cv72", null ],
      [ "4. Build the Firmware for the CV3x EVK", "dc/d4a/page_sys_docker.html#docker_build_cv3", null ],
      [ "5. Network Setup", "dc/d4a/page_sys_docker.html#docker_network_set", null ],
      [ "6. Configure Docker Image", "dc/d4a/page_sys_docker.html#docker_configure", null ],
      [ "7. Run Docker Daemons", "dc/d4a/page_sys_docker.html#docker_run_daemons", null ],
      [ "8. Load Ubuntu", "dc/d4a/page_sys_docker.html#docker_load_ubuntu", null ],
      [ "9. Run Ubuntu", "dc/d4a/page_sys_docker.html#docker_run_ubuntu", null ],
      [ "10. Implement SDK", "dc/d4a/page_sys_docker.html#docker_implement_sdk", null ],
      [ "11. Support Secure Shell (SSH) Server", "dc/d4a/page_sys_docker.html#docker_ssh_server", null ],
      [ "12. Support ROS2", "dc/d4a/page_sys_docker.html#docker_ROS2", null ],
      [ "13. Docker Q & A", "dc/d4a/page_sys_docker.html#docker_qa", null ],
      [ "14. License", "dc/d4a/page_sys_docker.html#docker_license", null ]
    ] ],
    [ "DESIGN - Porting Ubuntu System", "d0/de4/page_sys_porting_ubuntu_doc.html", [
      [ "0. Revision History", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_history", null ],
      [ "1. Overview", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_ov", null ],
      [ "2. Background Introduction", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_bg", null ],
      [ "3. Preparation of Ubuntu's Root File System (Rootfs)", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_preparation", [
        [ "3.1 Download and Extract Ubuntu Core System", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_download_core_sys", null ],
        [ "3.2 Download QEMU Simulator and Run Arm Ubuntu Core System", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_download_qemu", null ],
        [ "3.3 Configure Ubuntu Core System", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_configure_ubuntu_core", null ]
      ] ],
      [ "4. Burn Root File System into the Device", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_burn_system", [
        [ "4.1 Burn the Root File System to eMMC", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_burn_system_emmc", null ],
        [ "4.2 Burn Root File System onto SD Card", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_burn_system_sd", null ]
      ] ],
      [ "5. Frequently Asked Questions (FAQ)", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_faq", null ],
      [ "6. License", "d0/de4/page_sys_porting_ubuntu_doc.html#porting_ubuntu_system_license", null ]
    ] ],
    [ "DESIGN - Memory Layout & Optimization", "d4/d3e/page_sys_dram_opt_doc.html", [
      [ "0. Revision History", "d4/d3e/page_sys_dram_opt_doc.html#dram_opt_history", null ],
      [ "1. Introduction", "d4/d3e/page_sys_dram_opt_doc.html#dram_opt_introduction", [
        [ "1.1 Memory Layout Introduction", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_mem_intr", [
          [ "1.1.1 4 GB Memory Layout", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_4g_layout", null ],
          [ "1.1.2 8 GB (or > 8 GB) Memory Layout", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_8g_layout", null ]
        ] ]
      ] ],
      [ "2. DRAM Optimization", "d4/d3e/page_sys_dram_opt_doc.html#dram_opt", [
        [ "2.2 IAV Partition", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_iav", [
          [ "2.2.1 Bitstream Buffer", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_bsb", null ],
          [ "2.2.2 User Data Buffer", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_user", null ],
          [ "2.2.3 Motion Vector Buffer", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_mv", null ],
          [ "2.2.4 Overlay", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_over", null ],
          [ "2.2.5 QP Matrix", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_qp", null ],
          [ "2.2.6 Warp", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_warp", null ],
          [ "2.2.7 Image", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_img", null ],
          [ "2.2.8 QUANT", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_quant", null ],
          [ "2.2.9 Mask", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_mask", null ],
          [ "2.2.10 PYRAMID_POOL", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_py", null ],
          [ "2.2.11 CANVAS_POOL", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_can", null ],
          [ "2.2.12 RAW_POOL", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_raw", null ],
          [ "2.2.13 BLEND_ALPHA", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_blend", null ],
          [ "2.2.14 Blur", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_blur", null ],
          [ "2.2.15 Arbitrary Blur", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_arblur", null ]
        ] ],
        [ "2.3 Digital Signal Processor Partition", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_dsp", [
          [ "2.3.1 Composition", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_comp", null ],
          [ "2.3.2 Examples", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_exampl_23", null ],
          [ "Example 1 IMX274_mipi / Mode 5 / 4Kp H.265 + 1080p H.265 + 4Kp MJPEG.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_1", null ]
        ] ],
        [ "2.4 CV Partition", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_cv", [
          [ "2.4.1 Examples", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_exampl_24", null ],
          [ "Example 2 MTCNN on the Timn (CV5) Board.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_2", null ]
        ] ],
        [ "2.5 Resource Memory Layout Configuration", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_res", [
          [ "2.5.1 Examples", "d4/d3e/page_sys_dram_opt_doc.html#sub_sec_exampl_25", null ],
          [ "Example 3 Enables the Memory Layout Resource Configuration.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_3", null ],
          [ "Example 4 Set Warp Memory Layout through Lua.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_4", null ],
          [ "Example 5 Set Single-Color Privacy Mask Memory Layout through Lua.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_5", null ],
          [ "Example 6 Set QP Matrix Memory Layout through Lua.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_6", null ],
          [ "Example 7 Reset Memory Layout through Lua.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_7", null ]
        ] ]
      ] ],
      [ "3. Examples of Memory Allocation", "d4/d3e/page_sys_dram_opt_doc.html#dram_opt_example", [
        [ "3.1 Single 5MP VIN", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_s5mp", [
          [ "Example 8 Single VIN 5MP with Stream Overlay and Single-Color PM.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_8", null ]
        ] ],
        [ "3.2 Single 4K VIN", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_s4k", [
          [ "Example 9 Single VIN 4K with Stream Overlay and Single-color PM.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_9", null ]
        ] ],
        [ "3.3 Single 8K VIN", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_s8k", [
          [ "Example 10 Single VIN 8K with Stream Overlay and a Single-color PM.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_10", null ]
        ] ],
        [ "3.4 Quad 5 MP VIN", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_q5mp", [
          [ "Example 11 Quad VIN 5MP with Stream Overlay and a Single-color PM.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_11", null ]
        ] ],
        [ "3.5 Quad 4K VIN", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_q4k", [
          [ "Example 12 Quad VIN 4K with Stream Overlay and Single-color PM.", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_12", null ]
        ] ]
      ] ],
      [ "4. Bandwidth", "d4/d3e/page_sys_dram_opt_doc.html#dram_opt_bandwidth", [
        [ "4.1 CV5 Bandwidth Limitation", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_cv5", [
          [ "Example 13 IMX274_mipi / Mode 5 / 4Kp H.265 + 1080p H.265 + 4Kp MJPEG (CV5_Timn).", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_13", null ]
        ] ],
        [ "4.2 CV52 Bandwidth Limitation", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_cv52", [
          [ "Example 14 IMX274_mipi / Mode 5 / 4Kp H.265 + 1080p H.265 + 4Kp MJPEG (CV52_zr).", "d4/d3e/page_sys_dram_opt_doc.html#dram_example_14", null ]
        ] ],
        [ "4.3 Bandwidth Optimization", "d4/d3e/page_sys_dram_opt_doc.html#sec_dram_band_opt", null ]
      ] ],
      [ "5. License", "d4/d3e/page_sys_dram_opt_doc.html#dram_opt_license", null ]
    ] ],
    [ "OPTIMIZATION - Power Management", "d2/d90/page_sys_pm.html", [
      [ "0. Revision History", "d2/d90/page_sys_pm.html#sys_pm_history", null ],
      [ "1. Overview", "d2/d90/page_sys_pm.html#sys_pm_overview", null ],
      [ "2. Power Optimization", "d2/d90/page_sys_pm.html#sys_pm_power_optimization", [
        [ "2.1 Core Numbers", "d2/d90/page_sys_pm.html#sys_pm_po_core_numbers", [
          [ "2.1.1 Linux Boot Arguments Modification", "d2/d90/page_sys_pm.html#sys_pm_po_core_linux", null ]
        ] ],
        [ "2.2 CPU, Core, and IDSP Clock Runtime Update", "d2/d90/page_sys_pm.html#sys_pm_ccidsp", [
          [ "2.2.1 Build the Firmware", "d2/d90/page_sys_pm.html#sys_pm_ccidsp_bF", null ],
          [ "2.2.2 Change CPU, Core, and IDSP Clock", "d2/d90/page_sys_pm.html#sys_pm_change_clock", null ],
          [ "2.2.3 Measure Clock Runtime-Switch Time", "d2/d90/page_sys_pm.html#sys_pm_measure_clock", null ]
        ] ],
        [ "2.3 Vector Processor Clock Runtime Update", "d2/d90/page_sys_pm.html#sys_pm_vector_processor", null ],
        [ "2.4 Video Input", "d2/d90/page_sys_pm.html#sys_pm_vin", null ],
        [ "2.5 Mobile Industry Processor Interface", "d2/d90/page_sys_pm.html#sys_pm_mipi_interface", null ],
        [ "2.6 General Purpose Input / Output", "d2/d90/page_sys_pm.html#sys_pm_gpio", null ],
        [ "2.7 Video Output", "d2/d90/page_sys_pm.html#sys_pm_vout", [
          [ "2.7.1 Composite Video Broadcast Signal", "d2/d90/page_sys_pm.html#sys_pm_vout_cvbs", null ],
          [ "2.7.2 HDMI", "d2/d90/page_sys_pm.html#sys_pm_vout_hdmi", null ],
          [ "2.7.3 MIPI DSI", "d2/d90/page_sys_pm.html#sys_pm_vout_mipidsi", null ],
          [ "2.7.4 Video (LCD)", "d2/d90/page_sys_pm.html#sys_pm_vout_video", null ]
        ] ],
        [ "2.8 Computer Vision", "d2/d90/page_sys_pm.html#sys_pm_cv", null ],
        [ "2.9 Secure Digital Input / Output", "d2/d90/page_sys_pm.html#sys_pm_sdio", null ],
        [ "2.10 Audio", "d2/d90/page_sys_pm.html#sys_pm_audio", null ],
        [ "2.11 Analog-to-Digital Converter", "d2/d90/page_sys_pm.html#sys_pm_adc", null ],
        [ "2.12 Peripheral Component Interconnect Express", "d2/d90/page_sys_pm.html#sys_pm_pcie", null ],
        [ "2.13 High Efficiency Video Coding (HEVC)", "d2/d90/page_sys_pm.html#sys_pm_hevc", null ]
      ] ],
      [ "3. Arm Trusted Firmware", "d2/d90/page_sys_pm.html#sys_pm_atf", null ],
      [ "4. License", "d2/d90/page_sys_pm.html#sys_pm_license", null ]
    ] ],
    [ "TOOL - CooperHome", "d0/d78/page_sys_cooperhome.html", [
      [ "0. Revision History", "d0/d78/page_sys_cooperhome.html#cooperhome_history", null ],
      [ "1. Overview", "d0/d78/page_sys_cooperhome.html#cooperhome_ov", null ],
      [ "2. Build Method and Installation", "d0/d78/page_sys_cooperhome.html#cooperhome_build", [
        [ "2.1 Build CooperHome with Yocto-build Firmware", "d0/d78/page_sys_cooperhome.html#cooperhome_yocto_build", null ],
        [ "2.2 Build CooperHome Installation Package", "d0/d78/page_sys_cooperhome.html#cooperhome_build_installation_pack", null ],
        [ "2.3 Install CooperHome on Existing Amba-Build or Yocto-Build Firmware", "d0/d78/page_sys_cooperhome.html#cooperhome_installation", null ],
        [ "2.4 Install CooperHome on Lychee", "d0/d78/page_sys_cooperhome.html#cooperhome_lychee_installation", null ]
      ] ],
      [ "3. Run CooperHome", "d0/d78/page_sys_cooperhome.html#cooperhome_run", [
        [ "3.1 Run CooperHome on Amba-build or Yocto-build Firmware", "d0/d78/page_sys_cooperhome.html#cooperhome_run_amba_yocto", null ],
        [ "3.2 Run CooperHome on Lychee", "d0/d78/page_sys_cooperhome.html#cooperhome_run_lychee", null ]
      ] ],
      [ "4. CooperHome Webpages", "d0/d78/page_sys_cooperhome.html#cooperhome_pages", [
        [ "4.1 Dashboard", "d0/d78/page_sys_cooperhome.html#cooperhome_dashboard_page", [
          [ "4.1.1 Device Information", "d0/d78/page_sys_cooperhome.html#cooperhome_dashboard_devinfo", null ],
          [ "4.1.2 CPU Loading", "d0/d78/page_sys_cooperhome.html#cooperhome_dashboard_cpustat", null ],
          [ "4.1.3 CVflow Loading", "d0/d78/page_sys_cooperhome.html#cooperhome_dashboard_cvflowstat", null ],
          [ "4.1.4 Video Input Information", "d0/d78/page_sys_cooperhome.html#cooperhome_dashboard_vininfo", null ],
          [ "4.1.5 Stream Information", "d0/d78/page_sys_cooperhome.html#cooperhome_dashboard_streaminfo", null ]
        ] ],
        [ "4.2 Startup", "d0/d78/page_sys_cooperhome.html#cooperhome_startup_page", [
          [ "4.2.1 CPU", "d0/d78/page_sys_cooperhome.html#cooperhome_startup_cpu", null ]
        ] ],
        [ "4.3 Performance", "d0/d78/page_sys_cooperhome.html#cooperhome_performance_page", [
          [ "4.3.1 DRAM Bandwidth", "d0/d78/page_sys_cooperhome.html#cooperhome_performance_drambw", null ],
          [ "4.3.2 Interrupts", "d0/d78/page_sys_cooperhome.html#cooperhome_performance_itrp", null ],
          [ "4.3.3 Video Pipeline Analysis", "d0/d78/page_sys_cooperhome.html#cooperhome_performance_latency", null ],
          [ "4.3.4 CPU Profile", "d0/d78/page_sys_cooperhome.html#cooperhome_performance_cpuprofile", null ],
          [ "4.3.5 DSP Profile", "d0/d78/page_sys_cooperhome.html#cooperhome_performance_dspprofile", null ],
          [ "4.3.6 CVflow Profile", "d0/d78/page_sys_cooperhome.html#cooperhome_performance_cvflowprofile", null ]
        ] ],
        [ "4.4 Image Quality", "d0/d78/page_sys_cooperhome.html#cooperhome_iq_page", [
          [ "4.4.1 Image Processs Information", "d0/d78/page_sys_cooperhome.html#cooperhome_iq_info", null ],
          [ "4.4.2 Image Process Configuration", "d0/d78/page_sys_cooperhome.html#cooperhome_iq_config", null ]
        ] ],
        [ "4.5 Geometric Distortion Correction", "d0/d78/page_sys_cooperhome.html#cooperhome_gdc_page", [
          [ "4.5.1 General Configuration", "d0/d78/page_sys_cooperhome.html#cooperhome_gdc_gen", null ],
          [ "4.5.2 Correction Mode Configuration", "d0/d78/page_sys_cooperhome.html#cooperhome_gdc_cm", null ]
        ] ],
        [ "4.6 Video Capture", "d0/d78/page_sys_cooperhome.html#cooperhome_vcap_page", [
          [ "4.6.1 Live stream", "d0/d78/page_sys_cooperhome.html#cooperhome_vcap_livestream", null ]
        ] ],
        [ "4.7 About", "d0/d78/page_sys_cooperhome.html#cooperhome_about_page", null ]
      ] ],
      [ "5. CooperHome Prerequisite", "d0/d78/page_sys_cooperhome.html#cooperhome_prerequisite", [
        [ "5.1 Command Line", "d0/d78/page_sys_cooperhome.html#cooperhome_prerequisite_cl", null ],
        [ "5.2 Environment Variable", "d0/d78/page_sys_cooperhome.html#cooperhome_prerequisite_ev", null ],
        [ "5.3 Driver", "d0/d78/page_sys_cooperhome.html#cooperhome_prerequisite_drv", null ],
        [ "5.4 Unit Test", "d0/d78/page_sys_cooperhome.html#cooperhome_prerequisite_ut", null ],
        [ "5.5 System File", "d0/d78/page_sys_cooperhome.html#cooperhome_prerequisite_sysfs", null ]
      ] ],
      [ "6. License", "d0/d78/page_sys_cooperhome.html#cooperhome_license", null ]
    ] ],
    [ "DEBUG - DRAM Bandwidth Statistics", "d9/dea/page_sys_dram_stat.html", [
      [ "1. DRAM Bandwidth Statistics Features", "d9/dea/page_sys_dram_stat.html#section_dram_bandwidth_statistics_features", [
        [ "1.1 Preparations", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_preparations", null ],
        [ "1.2 Configuration", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_configuration", null ],
        [ "1.3 Statistics Result", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_result", [
          [ "1.3.1 Usage", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_result_usage", null ],
          [ "1.3.2 DRAM Info", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_result_dram_info", null ],
          [ "1.3.3 Average BW", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_result_average_bw", null ],
          [ "1.3.4 Minimal BW among Each Interval", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_result_minimal", null ],
          [ "1.3.5 Maximal BW among Each Interval", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_result_maximal", null ],
          [ "1.3.6 Interval BW", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_result_interval", null ],
          [ "1.3.7 Statistics Info", "d9/dea/page_sys_dram_stat.html#dram_bandwidth_statistics_result_statistics", null ]
        ] ]
      ] ],
      [ "2. DRAM Bandwidth Statistics Example", "d9/dea/page_sys_dram_stat.html#section_dram_bandwitdh_statistics_examples", [
        [ "Example 1: 1080p encode case", "d9/dea/page_sys_dram_stat.html#example_dram_bandwitdh_statistics_example1", null ],
        [ "Example 2: memcpy 1M buffer", "d9/dea/page_sys_dram_stat.html#example_dram_bandwitdh_statistics_example2", null ]
      ] ]
    ] ],
    [ "DEBUG - Tools", "d9/dc9/sys_debug_tool.html", [
      [ "1. Software Development Kit (SDK) Debug Tools", "d9/dc9/sys_debug_tool.html#sys_debug_tool_sdk", [
        [ "1.1 General Debug Method", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_gen", null ],
        [ "1.2 Kernel Log", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_ker", null ],
        [ "1.3 Capture the DSP Log and Parse", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_cap", null ],
        [ "1.4 Debug with the Script", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_scr", null ],
        [ "1.5 Kernel Message Module", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_mes", null ],
        [ "1.6 Gnu DeBugger (GDB) Debug", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_gdb", [
          [ "1.6.1 Debug on the Board", "d9/dc9/sys_debug_tool.html#dsub_sys_debug_tool_sdk_board", null ],
          [ "1.6.2 Debug on the Host", "d9/dc9/sys_debug_tool.html#dsub_sys_debug_tool_sdk_host", null ]
        ] ],
        [ "1.7 Memory Debug", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_mem", null ],
        [ "1.8 Capture the Cavalry Log", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_cav", null ],
        [ "1.9 Stream Diff", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_str", null ],
        [ "1.10 Cavalry Top", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_top", null ],
        [ "1.11 Cavalry Core Dump", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_cor", null ],
        [ "1.12 Performance Debugging", "d9/dc9/sys_debug_tool.html#sub_sys_debug_tool_sdk_perf", null ]
      ] ],
      [ "2. License", "d9/dc9/sys_debug_tool.html#sys_debug_tool_license", null ]
    ] ],
    [ "DEBUG - FAQ", "d3/df5/page_sys_faq_doc.html", [
      [ "1. Choosing the Appropriate Chip", "d3/df5/page_sys_faq_doc.html#faq_choosing_the_appropriate_chip", null ],
      [ "2. System Change", "d3/df5/page_sys_faq_doc.html#faq_system_change", null ],
      [ "3. How to Obtain Audio Data", "d3/df5/page_sys_faq_doc.html#faq_how_to_obtain_audio_data", null ],
      [ "4. Full Duplex Communication For Audio", "d3/df5/page_sys_faq_doc.html#faq_full_duplex_communication_for_audio", null ],
      [ "5 Flash Usage", "d3/df5/page_sys_faq_doc.html#faq_flash_usage", [
        [ "5.1 Type Confirm", "d3/df5/page_sys_faq_doc.html#faq_flash_type", null ],
        [ "5.2 ECC Confirm", "d3/df5/page_sys_faq_doc.html#faq_flash_ecc", null ],
        [ "5.3 File System Format and ECC Level", "d3/df5/page_sys_faq_doc.html#faq_flash_format_level", null ],
        [ "5.4 Notice for Flash Programmer", "d3/df5/page_sys_faq_doc.html#faq_flash_notice", null ]
      ] ],
      [ "6 GPIO Configuration", "d3/df5/page_sys_faq_doc.html#faq_gpio_configuration", [
        [ "6.1 System Startup with Default Configuration", "d3/df5/page_sys_faq_doc.html#faq_gpio_default", null ],
        [ "6.2 GPIO Control in User Space", "d3/df5/page_sys_faq_doc.html#faq_gpio_control", null ]
      ] ],
      [ "7. ADC Usage", "d3/df5/page_sys_faq_doc.html#faq_adc_usage", null ],
      [ "8. LCD in CV5x", "d3/df5/page_sys_faq_doc.html#faq_lcd_in_cv5x", null ],
      [ "9. Chip ID Check", "d3/df5/page_sys_faq_doc.html#faq_chip_id_check", null ],
      [ "10. Protection Against Overcurrent in the USB Host", "d3/df5/page_sys_faq_doc.html#faq_protection_against_overcurrent_in_the_usb_host", null ],
      [ "11. Watchdog", "d3/df5/page_sys_faq_doc.html#faq_watchdog", null ],
      [ "12. SPI NOR Flash", "d3/df5/page_sys_faq_doc.html#faq_spinor_flash", null ],
      [ "13. Sensor Driver Initialization", "d3/df5/page_sys_faq_doc.html#faq_sensor_driver_init", null ],
      [ "14. Supporting Chinese SSID", "d3/df5/page_sys_faq_doc.html#faq_supporting_chinese_ssid", null ],
      [ "15. Firmware Upgrade", "d3/df5/page_sys_faq_doc.html#faq_firmware_upgrade", null ],
      [ "16. MPtool", "d3/df5/page_sys_faq_doc.html#faq_mptool", null ],
      [ "17. How to Patch", "d3/df5/page_sys_faq_doc.html#faq_how_to_patch", null ],
      [ "18. Configuration File", "d3/df5/page_sys_faq_doc.html#faq_configuration_file", [
        [ "18.1 DTS", "d3/df5/page_sys_faq_doc.html#faq_configuration_dts", null ],
        [ "18.2 DDR", "d3/df5/page_sys_faq_doc.html#faq_configuration_ddr", null ],
        [ "18.3 Menuconfig", "d3/df5/page_sys_faq_doc.html#faq_configuration_menuconfig", null ],
        [ "18.4 CVflow® Issues", "d3/df5/page_sys_faq_doc.html#faq_configuration_cvflow_issues", null ]
      ] ],
      [ "19. eMMC Usage", "d3/df5/page_sys_faq_doc.html#faq_emmc_usage", null ],
      [ "20. CMA for IAV / CV Memory Partitions", "d3/df5/page_sys_faq_doc.html#faq_cma_for_iav_cv_memory_partitions", null ]
    ] ],
    [ "Modules", "modules.html", "modules" ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ]
    ] ],
    [ "Examples", "examples.html", "examples" ]
  ] ]
];

var NAVTREEINDEX =
[
"d0/d78/page_sys_cooperhome.html",
"d6/d3a/page_sysdoc_amboot_doc.html#amboot_doc_license",
"df/d1e/page_sysdoc_multi_cluster.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';