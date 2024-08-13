/*!
 * @file doc_peripherals_main.h
 * @brief This is a dummy header file for doxygen
 * @version 0.1
 * @date 2021-09-15
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
 *
 *
 * <h1>Outline</h1>
 *
 * The following revision history table summarizes changes contained in this document.
 *
 * <table>
 * <caption id="feature_sets_rev_history"></caption>
 * <tr><th> Updated Date          <th align="left"> Modification
 * <tr><td> 20211014              <td> Initial Version
 * <tr><td> 20211223              <td> Updated Section @ref amba_uvc_camera "4. Ambarella UVC Camera"
 * <tr><td> 20220222              <td> Updated Section @ref amba_uvc_camera "4. Ambarella UVC Camera"
 * <tr><td> 20220406              <td> Added Section @ref si_boot_upgrade "Boot and Upgrade".
 * <tr><td> 20220505              <td> Updated Section @ref configuration_and_compile "Configuration and Compile".
 * <tr><td> 20220516              <td> Updated Section @ref amba_uvc_camera "4. Ambarella UVC Camera"
 * <tr><td> 20220620              <td> Added Section @ref si_i2c "I2C".
 * <tr><td> 20220630              <td> Updated Section @ref si_partition_rmd_example "1.4 Example: Build the Ramdisk System".
 * <tr><td rowspan="2"> 20220701  <td> 1. Added Section @ref audio_mic_sup "CV5x EVK with Analog and Digital MIC Support".
 * <tr>                           <td> 2. Updated Section @ref poc_setting "1.1 POC Setting".
 * <tr><td> 20220720              <td> Updated Section @ref poc_setting "1.1 POC Setting".
 * <tr><td> 20220725              <td> Added Section @ref si_jtag "JTAG".
 * <tr><td> 20220727              <td> Deleted Section @ref si_boot_upgrade "Boot and Upgrade".
 * <tr><td> 20220915              <td> Added Section @ref si_ptp "PTP".
 * <tr><td> 20221010              <td> Added Section @ref configure_VLAN_function "6.Configure VLAN Function".
 * <tr><td> 20221012              <td> Deleted Section "Setup JTAG I-Jet with Chameleon" in page @ref si_jtag "JTAG".
 * <tr><td> 20221017              <td> Updated Section @ref uvc_cam_specifications "4.1 Specifications".
 * <tr><td> 20221021              <td> Updated Doc Overview @ref si_usb "USB".
 * <tr><td> 20221216              <td> Added Page @ref si_temperature "Temperature".
 * <tr><td rowspan="2"> 20230216  <td> 1. Added Section @ref ud_usb_device_uvc_gadget "4.5 Test uvc-gadget".
 * <tr>                           <td> 2. Updated Section @ref uvc_cam_specifications "4.1 Specifications".
 * <tr><td> 20230307              <td> Updated Section @ref uvc_cam_stream_ambarella_uvc "4.3 Stream Ambarella UVC".
 * <tr><td> 20230725              <td> Added Section @ref boot_from_rootfs_in_sd_card "6. Boot from Rootfs in SD Card".
 * <tr><td> 20230731              <td> Updated Section @ref uvc_cam_specifications "4.1 Specifications".
 * <tr><td rowspan="2"> 20230816  <td> 1. Updated Section @ref uvc_cam_build_firmware "4.2 Build the Firmware to Support UVAC".
 * <tr>                           <td> 2. Added Section @ref ud_usb_ffs_device "4.6 USB FunctionFS Device".
 * </table>
 *
 * ---
 *

This Document will be organized as below:
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

 *
 * --- 
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
