/*!
 * @file doc_system_main.h
 * @brief This file defines the doxygen structure of system chapter
 * @version 0.1
 * @date 2022-07-05
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


/*!
 * @mainpage notitle
 * <h1>AMBA System Document</h1>
 * - - - -
 * <h2>Revision History</h2>
 *
 *
 * <table>
 * <caption id="sys_rev_history"></caption>
 * <tr><th> Updated Date                <th align="left"> Modification
 * <tr><td> 20220705                    <td> Initial Version
 * <tr><td> 20220722                    <td> Remove CMA Driver, check @ref page_drv_cma_doc for detailed information.
 * <tr><td> 20220729                    <td> Remove DRAM Optimization, check @ref page_sys_dram_opt_doc for detailed information.
 * <tr><td> 20220809                    <td> Added new page @ref page_sys_pm "Power Management"
 * <tr><td> 20220812                    <td> Added new page @ref page_sys_mg "Migration Guide From CV2x"
 * <tr><td> 20220829                    <td> Added new page @ref page_sys_dram_stat "DRAM Bandwidth Statistics"
 * <tr><td> 20220922                    <td> Added new structure for this doxygen project content
 * <tr><td> 20230901                    <td> Added new page @ref page_sys_cooperhome "CooperHome"
 * <tr><td> 20231123                    <td> Updated Section @ref page_sys_docker "Docker Guide"
 * <tr><td> 20231226                    <td> Updated Page @ref sys_debug_tool "DEBUG - Tools"
 * </table>
 *
 * - - - -
 * <h2>Migration Guide from CV2x Document Overview</h2>
 * This document provides guidelines for the mirgration from CV2x SDK to the Cooper Linux SDK.
 *
 * The outline of @ref page_sys_mg_cv2x is listed as follows:
 * - Section @ref sys_mg_cv2x_history 
 * - Section @ref sys_mg_overview 
 * - Section @ref sys_mg_hw 
 * - Section @ref sys_mg_sw 
 * - Section @ref sys_mg_ioctl_interface 
 * - Section @ref sys_mg_unit_test 
 * - Section @ref sys_mg_tools 
 * - Section @ref sys_mg_faq 
 * - Section @ref sys_mg_license 
 *
 * - - - -
 * <h2>Migration Guide from CV5x legacy SDK Document Overview</h2>
 * This document provides guidelines for the mirgration from CV5x legacy SDK to the Cooper Linux SDK.
 *
 * The outline of @ref page_sys_mg_legacy is listed as follows:
 * - Section @ref sys_mg_lgc_history 
 * - Section @ref sys_mg_lgc_overview 
 * - Section @ref sys_mg_lgc_highlights 
 * - Section @ref sys_mg_lgc_sw 
 * - Section @ref sys_mg_lgc_ioctl_interface 
 * - Section @ref sys_mg_lgc_tools 
 * - Section @ref sys_mg_lgc_faq 
 * - Section @ref sys_mg_lgc_license 
 *
 * - - - -
 * <h2>AMBoot Documents Overview</h2>
 * This document introduces AMBoot documents in the Flexible Linux SDK.
 *
 * The outline of @ref page_sysdoc_amboot_doc is listed as follows:
 * - Section @ref amboot_doc_history 
 * - Section @ref amboot_doc_intro 
 * - Section @ref amboot_doc_license 
 *
 * - - - -
 * <h2>Kernel Documents Overview</h2>
 * This document introduces Kernel documents in the Flexible Linux SDK.
 *
 * The outline of @ref page_sysdoc_kernel_doc is listed as follows:
 * - Section @ref kernel_doc_license 
 *
 * - - - -
 * <h2>AMBoot Documents Overview</h2>
 * This document introduces root file system (Rootfs) documents in the Flexible Linux SDK.
 *
 * The outline of @ref page_sysdoc_rootfs_doc is listed as follows:
 * - Section @ref rootfs_doc_history 
 * - Section @ref si_rootfs_doc_intro 
 * - Section @ref si_rootfs_build 
 * - Section @ref si_rootfs_doc_license 
 *
 * - - - -
 * <h2>CM3 Documents Overview</h2>
 * This document introduces CM3 documents in the Flexible Linux SDK.
 *
 * The outline of @ref page_sysdoc_cm3_doc is listed as follows:
 * - Section @ref cm3_history 
 * - Section @ref cm3_overview 
 * - Section @ref cm3_freertos 
 * - Section @ref cm3_configuration 
 * - Section @ref cm3_driver 
 * - Section @ref cm3_license 
 *
 * - - - -
 * <h2>Multi-Clusters Documents Overview</h2>
 * This document introduces Multi-Clusters in the Cooper Linux SDK.
 *
 * The outline of @ref page_sysdoc_multi_cluster is listed as follows:
 * - Section @ref multi_cluster_doc_history 
 * - Section @ref multi_cluster_intro 
 * - Section @ref multi_cluster_design 
 * - Section @ref multi_cluster_blazenet_driver 
 * - Section @ref multi_cluster_nfs_rootfs 
 * - Section @ref multi_cluster_boot 
 * - Section @ref multi_cluster_cavalry 
 * - Section @ref multi_cluster_license 
 *
 * - - - -
 * <h2>Lychee OS Documents Overview</h2>
 * This document introduces Lychee OS in the Cooper Linux SDK.
 *
 * The outline of @ref page_sysdoc_lychee_os is listed as follows:
 * - Section @ref multi_cluster_doc_history 
 * - Section @ref lychee_os_intro 
 * - Section @ref lychee_os_install_lycheeos_on_cv3 
 * - Section @ref lychee_os_the_first_login_settings 
 * - Section @ref lychee_os_the_local_sdk_repo_setup_guide 
 * - Section @ref lychee_os_dnf_command_reference 
 * - Section @ref lychee_os_license 
 *
 * - - - -
 * <h2>Boot and Upgrade Documents Overview</h2>
 * This document introduces Boot and Upgrade documents in the Flexible Linux SDK.
 *
 * The outline of @ref si_boot_upgrade is listed as follows:
 * - Section @ref boot_upgrade_doc_history 
 * - Section @ref si_partition 
 * - Section @ref si_boot 
 * - Section @ref si_upgrade 
 * - Section @ref si_partition_auto_recovery 
 *
 * - - - -
 * <h2>Hardware PTS Document Overview</h2>
 * This document provides guidelines for the hardware PTS on the Flexible Linux SDK.
 *
 * The outline of @ref page_sys_hw_pts_doc is listed as follows:
 * - Section @ref hw_pts_history 
 * - Section @ref hw_pts_overview 
 * - Section @ref hw_pts_hw 
 * - Section @ref hw_pts_clock_source 
 * - Section @ref hw_pts_audio 
 * - Section @ref hw_pts_video 
 * - Section @ref hw_pts_use_scenario 
 * - Section @ref hw_pts_encode 
 * - Section @ref hw_pts_license 
 *
 * - - - -
 * <h2>Fast Boot Design Overview</h2>
 * This document provides guidelines for the fast boot design in the Flexible Linux SDK.
 *
 * The outline of @ref page_sys_fastboot is listed as follows:
 * - Section @ref fastboot_history 
 * - Section @ref sys_fb_intro 
 * - Section @ref sys_fb_cold_boot 
 * - Section @ref sys_fb_dram_refresh 
 * - Section @ref fastboot_license 
 *
 * - - - -
 * <h2>Sensor Calibration User Guide Document Overview</h2>
 * This document provides guidelines for the system and software design, and also includes
 * information on implementation with the CV2x Flexible Linux SDK.
 *
 * The outline of @ref page_sensor_calib_user_guide_doc is listed as follows:
 * - Section @ref guide_sensor_calib_history 
 * - Section @ref guide_sensor_calib_introduction 
 * - Section @ref guide_sensor_calib_preparation 
 * - Section @ref guide_sensor_calib_lens 
 * - Section @ref guide_sensor_calib_tof 
 * - Section @ref guide_sensor_calib_tof_rgbd 
 * - Section @ref guide_sensor_calib_stitch 
 * - Section @ref guide_sensor_calib_thermal_rgb 
 * - Section @ref guide_sensor_calib_mono_rgb 
 * - Section @ref guide_sensor_calib_structure_light 
 * - Section @ref guide_sensor_calib_dual_fish 
 * - Section @ref guide_sensor_calib_faq 
 * - Section @ref guide_sensor_calib_lic 
 *
 * - - - -
 * ### Docker User Specified Document
 *
 * Docker is an open source, application-container engine that enables developers
 * to package their applications and dependencies into a portable container,
 * then publish or virtualize them to any Linux machine.
 * Containers are completely sandboxed and do not interface with each other.
 * This document provides guidance to run docker tool for CV5x chips
 * and demonstrates how to run the SDK function in Docker. <br>
 *
 * The outline of @ref page_sys_docker is listed as follows:
 * - Section @ref docker_history 
 * - Section @ref docker_ov 
 * - Section @ref docker_build_cv5 
 * - Section @ref docker_build_cv72 
 * - Section @ref docker_build_cv3 
 * - Section @ref docker_network_set 
 * - Section @ref docker_configure 
 * - Section @ref docker_run_daemons 
 * - Section @ref docker_load_ubuntu 
 * - Section @ref docker_run_ubuntu 
 * - Section @ref docker_implement_sdk 
 * - Section @ref docker_ssh_server 
 * - Section @ref docker_ROS2 
 * - Section @ref docker_qa 
 * - Section @ref docker_license 
 *
 * - - - -
 * <h2>Porting Ubuntu Core System Guide</h2>
 * This document provides guidelines for porting Ubuntu core system on the Flexible Linux SDK.
 *
 * The outline of @ref page_sys_porting_ubuntu_doc is listed as follows:
 * - Section @ref porting_ubuntu_system_history 
 * - Section @ref porting_ubuntu_system_ov 
 * - Section @ref porting_ubuntu_system_bg 
 * - Section @ref porting_ubuntu_system_preparation 
 * - Section @ref porting_ubuntu_system_burn_system 
 * - Section @ref porting_ubuntu_system_faq 
 * - Section @ref porting_ubuntu_system_license 
 *
 * - - - -
 * <h2>Memory Layout & Optimization Document Overview</h2>
 *
 * These web pages provides guidelines for image digital signal processing
 * (DSP) DRAM optimization using the Cooper Linux SDK. It includes
 * descriptions of the dynamic random-access memory (DRAM) partitions, as well as
 * instructions for using and reducing partition sizes for the small DRAMs provided.
 *
 * The outline of @ref page_sys_dram_opt_doc is listed as follows:
 * - Section @ref dram_opt_history 
 * - Section @ref dram_opt_introduction 
 * - Section @ref dram_opt 
 * - Section @ref dram_opt_example 
 * - Section @ref dram_opt_bandwidth 
 * - Section @ref dram_opt_license 
 *
 * - - - -
 * <h2>Power Management Document Overview</h2>
 * This document provides guidelines for the power management on the Flexible Linux SDK.
 *
 * The outline of @ref page_sys_pm is listed as follows:
 * - Section @ref sys_pm_history 
 * - Section @ref sys_pm_overview 
 * - Section @ref sys_pm_power_optimization 
 * - Section @ref sys_pm_atf 
 * - Section @ref sys_pm_license 
 *
 * - - - -
 * <h2>CooperHome Overview</h2>
 *
 * CooperHome is an Ambarella web application that runs on the Ambarella CV2x,
 * CV5x, CV7x, and CV3 systems on chip (SoCs) using the Cooper software development kit (SDK). CooperHome provides overview
 * information of the SoC and development board; monitors the status of the system;
 * starts CPU tasks, digital signal processor (DSP) pipelines, and CVflow® tasks with simple clicks;
 * profiles the performance of various use cases; and captures output data.
 *
 * The outline of @ref page_sys_cooperhome is listed as follows:
 * - Section @ref cooperhome_history 
 * - Section @ref cooperhome_ov 
 * - Section @ref cooperhome_build 
 * - Section @ref cooperhome_run 
 * - Section @ref cooperhome_pages 
 * - Section @ref cooperhome_prerequisite 
 * - Section @ref cooperhome_license 
 *
 * - - - -
 * <h2>Dram Bandwidth Statistics Overview</h2>
 * This document provides guidelines for the dram bandwidth statistics on the Flexible Linux SDK.
 *
 * The outline of @ref page_sys_dram_stat is listed as follows:
 * - Section @ref section_dram_bandwidth_statistics_features 
 * - Section @ref section_dram_bandwitdh_statistics_examples 
 *
 * - - - -
 * <h2>SDK Debug Tools And Linux Programming Guide</h2>
 * This document provides guidelines for the SDK debug tools and Linux programming guide on the Flexible Linux SDK.
 *
 * The outline of @ref sys_debug_tool is listed as follows:
 * - Section @ref debug_tool_history 
 * - Section @ref sys_debug_tool_sdk 
 * - Section @ref sys_debug_tool_license 
 *
 * - - - -
 * <h2>FAQ Document Overview</h2>
 * This document provides guidelines for the frequently asked questions (FAQ) on the Flexible Linux SDK.
 *
 * The outline of @ref page_sys_faq_doc is listed as follows:
 * - Section @ref faq_choosing_the_appropriate_chip 
 * - Section @ref faq_system_change 
 * - Section @ref faq_how_to_obtain_audio_data 
 * - Section @ref faq_full_duplex_communication_for_audio 
 * - Section @ref faq_flash_usage 
 * - Section @ref faq_gpio_configuration 
 * - Section @ref faq_adc_usage 
 * - Section @ref faq_lcd_in_cv5x 
 * - Section @ref faq_chip_id_check 
 * - Section @ref faq_protection_against_overcurrent_in_the_usb_host 
 * - Section @ref faq_watchdog 
 * - Section @ref faq_spinor_flash 
 * - Section @ref faq_sensor_driver_init 
 * - Section @ref faq_supporting_chinese_ssid 
 * - Section @ref faq_firmware_upgrade 
 * - Section @ref faq_mptool 
 * - Section @ref faq_how_to_patch 
 * - Section @ref faq_configuration_file 
 * - Section @ref faq_emmc_usage 
 * - Section @ref faq_cma_for_iav_cv_memory_partitions 
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
