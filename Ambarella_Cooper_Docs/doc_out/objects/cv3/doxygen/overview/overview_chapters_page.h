/*!
 * @file sys_overview.h
 * @brief This is a dummy header file for doxygen
 * @version 0.1
 * @date 2022-05-15
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
 * @page overview_proj System Overview
 *
 * @section overview_hw 1. SoC Hardware Overview
 *
 * The Ambarella CV5x / CV7x devices are implemented using system on chip (SoC) architecture. The
 * platform is driven by a 64-bit Linux OS that runs on the Arm® Dual-Cortex® A76 core of the
 * CV5x / CV7x processors. The digital signal processor (DSP) core empowers imaging signal processing
 * and the codecs. The CVflow® engine on the CV5x / CV7x SoCs supports hardware acceleration for neural
 * network implementation. Peripheral controllers, such as I2C, Ethernet, and SDIO support the
 * cooperation with external devices.
 *
 * @image html cv5x_soc_hw.png "Figure 1-1. CV5x Hardware Block Diagram."
 *
 * @image html cv7x_soc_hw.png "Figure 1-2. CV7x Hardware Block Diagram."
 *
 * - CV5x (CV5 and CV52) includes up to 4 independent VINs, which can be extended to 14 VINs through MIPI virtual channels.
 *
 * - CV7x (CV72) includes up to 3 independent VINs, which can be extended to 10 VINs through MIPI virtual channels.
 *
 * - - - -
 *
 * @section overview_sw 2. Cooper Linux SDK Software Overview
 *
 * The Cooper Linux SDK is a universal SDK for multiple markets, including professional and consumer IP cameras,
 * robotics cameras, video conferencing cameras, machine vision cameras, and more.
 *
 * Additionally, the Cooper Linux SDK software is implemented with DSP firmware, drivers, and middleware,
 * as well as the CVflow firmware, drivers, and library.
 *
 * The CV5x / CV7x series share the same software framework, as shown in Figure 2-1.
 *
 * The following refers to Figure 2-1 and describes Ambarella's responsibilies related to the CV series software framework.
 *
 * - The files outside the GREEN outline are released in binary format only. Ambarella is fully
 *   responsible for these binary files, and will provide solutions and fixes to customers, should issues arise.
 *
 * - Select files inside the PURPLE outline are released in binary format, and others are released as source code.
 *   Ambarella is fully responsible for both the binary and source code files,
 *   and will provide support to customers, should issues arise.
 *
 * - For the Linux kernel code, the Cooper Linux SDK selects one of the kernel LTS versions to maintain and support.
 *   Ambarella is responsible for the private drivers (for IAV, DSP, IMGPROC, and HWTIMER) and
 *   the public driver for the chip-related parts. Customers are responsible for maintaining the
 *   Linux kernel itself and other external device drivers (for WiFi, the audio codec, etc).
 *
 * - For open source software (OSS) modules, Ambarella provides the pre-build binary files inside the Cooper Linux SDK,
 *   but does not provide support for issues related to the OSS modules.
 *
 * @image html cv_soft_framework.png "Figure 2-1. CV Series Software Framework."
 *
 * - - - -
 *
 * @section overview_support_scope 3. Cooper Linux SDK Support Scope
 *
 * The Cooper Linux SDK includes three categories of content and support, as shown below.
 *
 * @image html cooper_support_scope.png "Figure 3-1. Cooper SDK Support Scope."
 *
 *
 * @subsection overview_support_list 3.1 Support Scope List
 * Below is the list of the license info and support scope for most of the deliverable software modules,
 * including drivers, libraries, demos and test applications.
 * | Module                                                       | License      | Support Category|
 * | :-- | :--   | :---   |
 * | AMBoot                                                       | Proprietary  | Category A      |
 * | AMRTOS                                                       | Proprietary  | Category A      |
 * | Uboot                                                        | GPLv2        | Category C      |
 * | Linux Kernel                                                 | GPLv2        | Category C      |
 * | Platform drivers                                             | GPLv2        | Category A      |
 * | IAV driver                                                   | GPLv2        | Category A      |
 * | Cavalry driver                                               | GPLv2        | Category A      |
 * | DSP, VIN, and VOUT drivers                                   | GPLv2        | Category A      |
 * | Sensor drivers                                               | GPLv2        | Category A      |
 * | Image processing driver                                      | GPLv2        | Category A      |
 * | Image processing (AE / AWB) library (libimg_algo.so)         | Proprietary  | Category A      |
 * | Image processing flow library (libimg_aaa_flow.so)           | Proprietary  | Category A      |
 * | Multi-channel Lua parser library (libmcl.so)                 | Proprietary  | Category A      |
 * | Neural network flow control library (libnnctrl.so)           | Apache-v2    | Category A      |
 * | Neural network data processing library (libvproc.so)         | Apache-v2    | Category A      |
 * | Neural network memory management library (libcavalry_mem.so) | Apache-v2    | Category A      |
 * | CNNGen pre-processing library (libcgpp.so)                   | Proprietary  | Category A      |
 * | Base component of easy artificial intelligence (AI) library  | Proprietary  | Category A      |
 * | Lens distortion correction library (libdewarp.so)            | Proprietary  | Category A      |
 * | Electronic image stabilization library (libeis.so)           | Proprietary  | Category A      |
 * | Smart rate control (SRC) library (libsmartrc.so)             | Proprietary  | Category A      |
 * | Text insertion library (libtextinsert.a)                     | Proprietary  | Category A      |
 * | Arbitrary blur library (libblur.so)                          | Proprietary  | Category A      |
 * | Base components of Oryx                                      | Proprietary  | Category A      |
 * | Unit test app under unit_test/private                        | Proprietary  | Category B      |
 * | Sample code of EazyAI library                                | Proprietary  | Category B      |
 * | Sample code of Oryx                                          | Proprietary  | Category B      |
 * | Amba-GST-Plugin                                              | Proprietary  | Category B      |
 * | ALSA library                                                 | LGPLv2+      | Category C      |
 * | OSS libraries                                                | By module    | Category C      |
 * | OSS libraries CVE fixes                                      | By module    | Category B      |
 * | Gstreamer                                                    | LGPLv2+      | Category C      |
 * | NNstreamer                                                   | LGPLv2       | Category C      |
 * | OpenCV                                                       | BSD          | Category C      |
 *
 */

/*!
 * @file doc_read_guide.h
 * @brief This is a dummy header file for Doxygen
 * @version 0.1
 * @date 2022-04-25
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
 * @page doc_read_guide Document Reading Guide
 *
 * @section doc_start 1. Evaluation: Where to Start?
 * When using the Ambarella Cooper Linux software development kit (SDK) for the first time,
 * Ambarella recommends starting with the following documents:<br>
 *  - @ref page_getting_start_guide
 *  - @ref ov_code_build
 *  - <em>Ambarella Cooper Linux SDK Release Notes</em>
 *
 * The two webpage documents provide information that familiarizes the user with
 * the basic environment and functions of the CV5x / CV7x evaluation kit (EVK) and SDK.
 * The release note PDF document offers the detailed feature updates information for the
 * SDK release. The key updates, sent with the release mail, is an abstract of
 * the release note document.
 *
 * @note
 *  - Most CV5x and CV7x documents share the same Doxygen content because most of
 *    their software architectures and hardware components are identical or similar; however,
 *    their performance aspects are different.
 *
 * - - - -
 *
 * @section doc_linux 2. Development: Linux SDK Documents
 * In this section, the Ambarella Cooper Linux SDK documents are divided into
 * four main categories:
 * - Platform
 * - Camera
 * - CVflow®
 * - Security
 *
 * @subsection doc_plat 2.1 Platform Documents
 * Some platform documents are released together with the SDK source code. They can be
 * accessed from the webpage @ref page_sysdoc_amboot_doc and @ref page_sysdoc_kernel_doc.
 *
 * There are multiple chapters in the document <em>Peripherals</em>, which provide more
 * descriptions for the different peripheral devices and their operations.
 *
 * The following are PDF-format documents:<br>
 * - <em>Ambarella DG Flexible Linux SDK JTAG Setup</em>
 * - <em>Ambarella AN SDK Approved Vendor List</em>
 *
 * @subsection doc_cam 2.2 Camera Documents
 * In the Ambarella Cooper Linux SDK, cameras can be made to function using either input / output
 * controls (IOCTLs) or using Oryx middleware.
 *
 * @ref page_drv_iav_doc "IAV Driver API" introduces the image audio video (IAV) driver application
 * programming interface (API) information, and offers some examples demonstrating the basic API
 * calling sequence.<br>
 * @ref fs_basic_vin "Feature Sets" provides more details and examples
 * from the feature wise perspective. Users can explore these webpages
 * to obtain more information on the different drivers, libraries, and features.
 *
 * Oryx documents can be generated using the commands below.
 * @code
 * build$ cd board/THE_SPECIFIC_BOARD
 * build$ make xxxx_oryx_v2_ipcam_config
 * build$ make oryx_v2_doc
 * @endcode
 *
 * @subsection doc_cv 2.3 CVflow® Documents
 * CVflow documents are in webpage and PDF formats. Users can refer to
 * [<i>Overview -> How To Start</i>] for more information in the Doxygen webpage documents.
 * Users can follow the commands below to generate the Doxygen webpage documents with the
 * CVflow CNNGen sample package.
 *
 * @code
 * build $ cd cvflow_cnngen_samples_<*.*>/
 * build $ export TV2_CONFIG=1
 * build $ make cnngen_doc
 * @endcode
 *
 * A series of CNNGen training videos are available for users in addition to the documents.
 * Contact the Ambarella support team to obtain these training videos.
 *
 * The videos are based on the <em>Ambarella CNNGen Introduction Customer</em> PDF document.
 * - Ambarella_CNNGen_Training_Video_Introduction_1.mp4
 * - Ambarella_CNNGen_Training_Video_Porting_Workflow_2.mp4
 * - Ambarella_CNNGen_Training_Video_Porting_Workflow_3.mp4
 * - Ambarella_CNNGen_Training_Video_deployment_4.mp4
 * - Ambarella_CNNGen_Training_Video_GSG_5.mp4
 * - Ambarella_CNNGen_Training_Video_GSG_6.mp4
 *
 * @subsection doc_sec 2.4 Security Documents
 * Ambarella provides two major security documents, currently maintained in Doxygen format:
 * - @ref security_overview "Security Overview"
 * - @ref one_time_programmable "OTP Operations"
 *
 * The security document <em>Ambarella DG Flexible Linux SDK Secure Boot by Built-In Hardware Engine</em> is in PDF format.
 *
 */


/*!
 * @file market_segments.h
 * @brief This is a dummy header file for doxygen
 * @version 0.1
 * @date 2022-05-15
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
 * @page market_segments Market Segments
 *
 * This page introduces some typical product features of different market segments, like
 * IP security cameras, consumer security cameras, video conferencing cameras, robotics cameras, automotive cameras, and more.
 *
 * - - - -
 *
 * @section ms_ipcam 1. IP Camera Market
 *
 * @subsection ms_ipcam_features 1.1 Features
 * Typical product features for IP camera market are as follows:
 * <table>
 * <caption id="Market_IPCam_Features">Table 1-1. IPCam Features.</caption>
 * <tr><th>Video Features                                  <th align="left"> Description
 * <tr><td>@ref fs_basic_vin "Video Input"                 <td> Configures video input, including resolution, fps, mode, interface, and more
 * <tr><td>@ref fs_basic_vout "Video Output"               <td> Configures video output, including resolution, fps, mode, device, and more
 * <tr><td>@ref fs_basic_canvas "Canvas"                   <td> Configures canvas, including resolution, source, type, and fps
 * <tr><td>@ref fs_basic_pyramid "Pyramid"                 <td> Generates multi-layer YUV frames for CV analysis
 * <tr><td>@ref fs_basic_stream "Stream"                   <td> Configures stream, including resolution, source, format, fps, and more
 * <tr><td>@ref fs_basic_hdr "HDR"                         <td> Configures HDR-related options
 * <tr><td>@ref fs_basic_codec "H.264/H.265 Codec"         <td> Configures Codec-related options
 * <tr><td>@ref fs_others_dsp_monitor_service "DSP Monitor Service" <td> DSP monitor service
 * <tr><td>@ref fs_adv_enc_mode "Encode Mode"              <td> Selects the proper encode mode and IDSP pipeline for different products
 * <tr><td>@ref channel_rotation "Channel IDSP Rotation / Flip" <td> Corridor scenarios. Only supported by "Encode Mode 3"
 * <tr><td>@ref fs_adv_efm "Encode from Memory"            <td> Encodes bit stream from prepared YUV420 data in memory
 * <tr><td>@ref fs_adv_efr "Encode from Raw"               <td> Feeds RAW (Bayer or YUV) data from memory into IDSP pipeline, then encode
 * <tr><td>@ref fs_adv_ldc "Lens Distortion Correction"    <td> Lens geometry distortion correction
 * <tr><td>@ref fs_adv_dewarp "Multi-Region Warp"          <td> Fisheye multi-region dewarp product
 * <tr><td>@ref fs_adv_arb_img_scaler "Arbitrary Image Scaler" <td> Allows the Arm® user app to perform up / down-scaling with the hardware scaler
 * <tr><td>@ref page_lib_stitch_doc "Stitch"               <td> Multi-channel stitching product
 * <tr><td>@ref page_lib_sensor_calib_doc "Sensor Calibration" <td> Sensor calibration needed by multi-channel stitching
 * <tr><td>@ref page_lib_src_v3 "SmartRC-v3"               <td> Smart Rate Control v3 (with CV analysis enabled)
 * <tr><td>@ref page_lib_eis_doc "EIS"                     <td> Electronic image stabilization
 * <tr><td>@ref fd_adv_multi_vin "Multi-Channel"           <td> Multi-VIN and multi-channel configuration
 * <tr><td>@ref fs_adv_vl "Vsync Loss"                     <td> VIN signal loss detection and recovery
 * <tr><td>@ref dram_opt_history "DRAM Optimization"       <td> DRAM capacity and bandwidth
 * <tr><td>@ref page_sys_pm "Power Management"             <td> Power management and optimization methods
 * </table>
 *
 * @subsection ms_ipcam_sensors 1.2 Sensors
 * The supported sensor list is as follows:
 *   - @ref img_cv5x_table_ipc "Sensors for CV5x IP Camera"
 *   - @ref img_cv72_table_ipc "Sensors for CV7x IP Camera"
 *
 * @subsection ms_ipcam_prod 1.3 Types of IP Cameras
 * There are many different product types of IP Cameras. Here are some examples for the most common ones:
 * <table>
 * <caption id="Market_IPCam_Products">Table 1-2. IPCam Products.</caption>
 * <tr><th>Products                       <th align="left"> Description
 * <tr><td>Single channel camera          <td> Regular single channel camera for different resolutions (from 2MP to 32MP)
 * <tr><td>Fisheye dewarp camera          <td> Fisheye lens camera with multiple regions of dewarp views
 * <tr><td>Dual channel stereo camera     <td> Two channels of stereo camera design
 * <tr><td>Multi-directional camera       <td> Multi-channel design with the same type sensors for different directions<br>
 *                                             Different channels can be configured with different 3A parameters
 * <tr><td>Multi-channel stitch camera    <td> Multi-channel stitching design with the same type sensors for larger stitched FoV.<br>
 *                                             All channels must be configured with similar 3A parameters
 * </table>
 *
 * - - - -
 *
 * @section ms_robo 2. Robotics Camera Market
 *
 * @subsection ms_robo_features 2.1 Features
 * Typical product features for robotics camera market are as follows:
 * <table>
 * <caption id="Market_Robot_Features">Table 2-1. Robotics Features.</caption>
 * <tr><th>Video Features                                  <th align="left"> Description
 * <tr><td>@ref fs_basic_vin "Video Input"                 <td> Configures video input, including resolution, fps, mode, interface, and more
 * <tr><td>@ref fs_basic_vout "Video Output"               <td> Configures video output, including resolution, fps, mode, device, and more
 * <tr><td>@ref fs_basic_canvas "Canvas"                   <td> Configures canvas, including resolution, source, type, and fps
 * <tr><td>@ref fs_basic_pyramid "Pyramid"                 <td> Generates multi-layer YUV frames for CV analysis
 * <tr><td>@ref fs_basic_stream "Stream"                   <td> Configures stream, including resolution, source, format, fps, and more
 * <tr><td>@ref fs_basic_codec "H.264/H.265 Codec"         <td> Configures Codec-related options
 * <tr><td>@ref fs_others_dsp_monitor_service "DSP Monitor Service" <td> DSP monitor service
 * <tr><td>@ref mode_normal_iso "Encode Mode 0"            <td> Recommended for Robotics products
 * <tr><td>@ref fs_adv_ldc "Lens Distortion Correction"    <td> Lens rectify and geometry distortion correction
 * </table>
 *
 * @subsection ms_robo_sensors 2.2 Sensors
 * The supported sensor list is as follows:
 *   - @ref img_cv72_table_stereo "Sensors for CV72 stereo"
 *
 * @subsection ms_robo_prod 2.3 Types of Robotics Cameras
 * There are many types of camera for robotics usage. Here are some examples for the most common ones:
 * <table>
 * <caption id="Market_Robot_Products">Table 2-2. Robotics Products.</caption>
 * <tr><th>Products               <th align="left"> Description
 * <tr><td>Stereo camera          <td> Two channels stereo camera design
 * <tr><td>RGB-D camera           <td> "RGB-Depth" fusion camera design.<br>
 *                                     The depth sensor can be either ToF or structure light sensors
 * </table>
 *
 * - - - -
 *
 * @section ms_conf 3. Video Conferencing Camera Market
 *
 * @subsection ms_conf_features 3.1 Features
 * Typical product features for the video conferencing camera market are as follows:
 * <table>
 * <caption id="Market_Conf_Features">Table 3-1. Video Conference Features.</caption>
 * <tr><th>Video Features                                  <th align="left"> Description
 * <tr><td>@ref fs_basic_vin "Video Input"                 <td> Configures video input, including resolution, fps, mode, interface, and more
 * <tr><td>@ref fs_basic_vout "Video Output"               <td> Configures video output, including resolution, fps, mode, device, and more
 * <tr><td>@ref fs_basic_canvas "Canvas"                   <td> Configures canvas, including resolution, source, type, and fps
 * <tr><td>@ref fs_basic_pyramid "Pyramid"                 <td> Generates multi-layer YUV frames for CV analysis
 * <tr><td>@ref fs_basic_stream "Stream"                   <td> Configures stream, including resolution, source, format, fps, and more
 * <tr><td>@ref fs_basic_codec "H.264/H.265 Codec"         <td> Configures Codec-related options
 * <tr><td>@ref fs_others_dsp_monitor_service "DSP Monitor Service" <td> DSP monitor service
 * <tr><td>@ref mode_normal_iso "Encode Mode 0"            <td> Recommended to meet the shortest latency from VIN to VOUT
 * <tr><td>@ref channel_rotation "Channel IDSP Rotation / Flip" <td> For corridor scenarios. Only supported by "Encode Mode 3"
 * <tr><td>@ref fs_adv_efm "Encode from Memory"            <td> Encodes bit stream from prepared YUV420 data in memory
 * <tr><td>@ref fs_adv_efr "Encode from Raw"               <td> Feeds RAW (Bayer or YUV) data from memory into IDSP pipeline, then encode
 * <tr><td>@ref fs_adv_ldc "Lens Distortion Correction"    <td> Lens geometry distortion correction
 * <tr><td>@ref fs_adv_dewarp "Multi-Region Warp"          <td> Fisheye multi-region dewarp product
 * <tr><td>@ref fs_adv_arb_img_scaler "Arbitrary Image Scaler" <td> Allows Arm® user app to perform up / down-scaling with the hardware scaler
 * <tr><td>@ref page_lib_stitch_doc "Stitch"               <td> Multi-channel stitching product
 * <tr><td>@ref page_lib_sensor_calib_doc "Sensor Calibration" <td> Sensor calibration needed by multi-channel stitching
 * <tr><td>@ref capture_display_latency "VIN-VOUT low latency" <td> Keeps the shortest latency from VIN capture done to VOUT display done
 * <tr><td>@ref vin_vout_precise_sync "VIN-VOUT precise sync"  <td> Synchronize VIN and VOUT from the beginning and adjust VIN
 *                                                                  frame rate on the fly to keep the precise sync
 * <tr><td>@ref vout_underflow_prevention "VOUT underflow prevention" <td> Prevents VOUT from underflow cases, which could
 *                                                                         potentially cause VOUT flickering
 * <tr><td>@ref amba_uvc_camera "UVAC"                     <td> Describes the guidelines for UVAC features
 * </table>
 *
 * @subsection ms_conf_sensors 3.2 Sensors
 * The supported sensor list is as follows:
 *   - @ref img_cv72_table_ipc "Sensors for video conference"
 *
 * @subsection ms_conf_prod 3.3 Types of Video Conferencing Cameras
 * There are many types of video conferencing cameras. Here are some examples for the most common ones:
 * <table>
 * <caption id="Market_Conf_Products">Table 3-2. Video Conference Products.</caption>
 * <tr><th>Products                 <th align="left"> Description
 * <tr><td>Single channel camera    <td> Video conferencing camera design for 1080p60, 4Kp30, 4Kp60, and more
 * <tr><td>Multi-channel camera     <td> Multiple channels video conferencing camera design.<br>
 *                                       It includes two channels stitching for 180 panorama view, and four channels stitching for 360 panorama view
 * </table>
 *
 * - - - -
 *
 * @section ms_auto 4. Automotive Camera Market
 *
 * @subsection ms_auto_features 4.1 Features
 * Typical product features for the automotive market is as follows:
 * <table>
 * <caption id="Market_Auto_Features">Table 4-1. Automotive Features.</caption>
 * <tr><th>Video Features                                  <th align="left"> Description
 * <tr><td>@ref fs_basic_vin "Video Input"                 <td> Configures video input, including resolution, fps, mode, interface, and more
 * <tr><td>@ref fs_basic_vout "Video Output"               <td> Configures video output, including resolution, fps, mode, device, and more
 * <tr><td>@ref fs_basic_canvas "Canvas"                   <td> Configures canvas, including resolution, source, type, and fps
 * <tr><td>@ref fs_basic_pyramid "Pyramid"                 <td> Generates multi-layer YUV frames for CV analysis
 * <tr><td>@ref fs_basic_stream "Stream"                   <td> Configures stream, including resolution, source, format, fps, and more
 * <tr><td>@ref fs_others_dsp_monitor_service "DSP Monitor Service" <td> DSP monitor service
 * <tr><td>@ref mode_normal_iso "Encode Mode 0"            <td> Recommended for all automotive products
 * <tr><td>@ref fs_adv_ldc "Lens Distortion Correction"    <td> Lens rectify and distortion correction
 * <tr><td>@ref capture_display_latency "VIN-VOUT low latency" <td> e-mirror products and more
 * <tr><td>@ref fd_adv_multi_vin "Multi-Channel"           <td> Multi-VIN and multi-channel configuration
 * <tr><td>@ref fs_adv_vl "Vsync Loss"                     <td> VIN signal loss detection and recovery
 * <tr><td>@ref Sensors_with_SERDES_Bridge "Sensors with SERDES bridge" <td> Installs multiple sensors connected through one or more SERDES
 * </table>
 *
 * @subsection ms_auto_sensors 4.2 Sensors
 * The supported sensor list is as follows:
 *   - @ref img_cv72_table_adas "Sensors for ADAS"
 *
 * @subsection ms_auto_prod 4.3 Types of Automotive Cameras
 * There are many product types of automotive usage. Here are some examples for the most common ones:
 * <table>
 * <caption id="Market_Auto_Products">Table 4-2. Automotive Products.</caption>
 * <tr><th>Products                 <th align="left"> Description
 * <tr><td>ADAS camera              <td> Front advanced driver assistance systems (ADAS) camera design
 * </table>
 *
 * - - - -
 *
 * @section ms_mach 5. Machine Vision Camera Market
 *
 * @subsection ms_mach_features 5.1 Features
 * Typical product features for machine vision market is as follows:
 * <table>
 * <caption id="Market_Mach_Features">Table 5-1. Machine Vision Features.</caption>
 * <tr><th>Video Features                                  <th align="left"> Description
 * <tr><td>@ref fs_basic_vin "Video Input"                 <td> Configures video input, including resolution, fps, mode, interface, and more
 * <tr><td>@ref fs_basic_vout "Video Output"               <td> Configures video output, including resolution, fps, mode, device, and more
 * <tr><td>@ref fs_basic_canvas "Canvas"                   <td> Configures canvas, including resolution, source, type, and fps
 * <tr><td>@ref fs_basic_pyramid "Pyramid"                 <td> Generates multi-layer YUV frames for CV analysis
 * <tr><td>@ref fs_basic_stream "Stream"                   <td> Configures stream, including resolution, source, format, fps, and more
 * <tr><td>@ref fs_others_dsp_monitor_service "DSP Monitor Service" <td> DSP monitor service
 * <tr><td>@ref fs_adv_ldc "Lens Distortion Correction"    <td> Lens rectify and distortion correction
 * <tr><td>@ref mode_normal_iso "Encode Mode 0"            <td> Recommended to meet the shortest latency from VIN to VOUT
 * <tr><td>@ref capture_display_latency "VIN-VOUT low latency" <td> e-mirror products and more
 * <tr><td>@ref fs_adv_efm "Encode from Memory"            <td> Encodes bit stream from prepared YUV420 data in memory
 * <tr><td>@ref fs_adv_efr "Encode from Raw"               <td> Feeds RAW (Bayer or YUV) data from memory into IDSP pipeline, then encode
 * </table>
 *
 * @subsection ms_mach_sensors 5.2 Sensors
 * The supported sensor list is as follows:
 *   - @ref img_cv72_table_ipc "Sensors for machine vision"
 *
 * - - - -
 *
 */

/*!
 * @file getting_start_guide.h
 * @brief This file defines the Doxygen structure of the getting started guide (GSG).
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
 */

/*!
 * @page page_getting_start_guide Getting Started Guide
 *
 * @section getting_guide_history 0. Revision History
 *
 * <table>
 * <caption id="getting_guide_history"></caption>
 * <tr><th> SDK Version                <th> Updated Date           <th> Modification
 * <tr><td> CV5x_SDK_0.1               <td> 20211021               <td> Initial Version
 * <tr><td rowspan="5"> CV5x_SDK_0.5   <td rowspan="5"> 20220114   <td> Updated Section @ref sub_guide_firmware_down
 * <tr>                                                            <td> Updated Section @ref sub_guide_firmware_fastboot_ubu
 * <tr>                                                            <td> Updated Section @ref sub_guide_firmware_fastboot_win
 * <tr>                                                            <td> Added Section @ref sub_guide_firmware_ambausb_ubu
 * <tr>                                                            <td> Added Section @ref sub_guide_firmware_ambausb_win Updated Chapter @ref
 * <tr><td rowspan="5"> CV5x_SDK_1.0   <td rowspan="5"> 20220415   <td> Updated Chapter @ref getting_guide_hardware_cv5 "2. Setting up the CV5 EVK Hardware"
 * <tr>                                                            <td> Added Chapter @ref getting_guide_hardware_cv52N "3. Setting up the CV52N EVK Hardware"
 * <tr>                                                            <td> Added Chapter @ref getting_guide_hardware_cv52 "4. Setting up the CV52 EVK Hardware"
 * <tr>                                                            <td> Updated Section @ref sub_guide_demo_build
 * <tr>                                                            <td> Updated Chapter @ref getting_guide_document "8. SDK Documents on the Website"
 * <tr><td rowspan="5"> CV5x_SDK_1.5   <td rowspan="5"> 20220720   <td> Removed Section CV5 EVK Rev 1.x /2.0 System I/O and Hardware Control
 * <tr>                                                            <td> Updated Chapter @ref getting_guide_hardware_cv5 "2. Setting up the CV5 EVK Hardware"
 * <tr>                                                            <td> Updated Chapter @ref getting_guide_hardware_cv52 "4. Setting up the CV52 EVK Hardware"
 * <tr>                                                            <td> Updated Section @ref sub_guide_firmware_fastboot_win
 * <tr>                                                            <td> Updated Chapter @ref getting_guide_document "8. SDK Documents on the Website"
 * <tr><td rowspan="4"> CV5x_SDK_2.0   <td rowspan="2"> 20220829   <td> Migrate this Getting Started Guide document from Word form into Doxygen form
 * <tr>                                                            <td> Updated Section @ref sub_guide_demo_cnn
 * <tr>                                <td> 20220916               <td> Added Chapter @ref getting_guide_cpu "9. CPU Performance Benchmarks"
 * <tr>                                <td> 20221025               <td> Upgrade Cortex Toolchain to 12.1
 * <tr><td rowspan="3"> Cooper_SDK_0.5 <td rowspan="3"> 20230420   <td> Added Chapter @ref getting_guide_sd_card "10. SD Card"
 * <tr>                                                            <td> Added Chapter @ref getting_guide_hardware_cv72 "5. Setting Up the CV72 EVK Hardware"
 * <tr>                                                            <td> Initial Version of Cooper SDK
 * <tr><td> Cooper_SDK_1.0             <td> 20230726               <td> Added new building method to support both Amba-Build-v2 and Yocto-Build.<br>
 *                                                                      Since SDK 1.0, it supports CV2x, CV5x and CV72 chips
 * <tr><td rowspan="2"> Cooper_SDK_1.6 <td> 20231228               <td> Updated Section @ref sub_guide_document_cnngen_cv5
 * <tr>                                <td> 20240105               <td> Updated Section @ref dsub_guide_demo_evaluation
 * </table>
 *
 * - - - -
 *
 * @section getting_guide_overview 1. Overview
 *
 * This document guides users through the environment setup process for evaluating the Ambarella
 * Cooper Linux Evaluation Kit (EVK) and the system on chip (SoC).
 *
 * Users with little or no previous experience using Ambarella devices are encouraged
 * to proceed sequentially through this guide and become familiar with the complete
 * range of hardware and software features.
 *
 * For users with prior experience setting up Ambarella devices, this document provides a quick
 * introduction to EVK board setup before starting hands-on work with the Cooper chip family.
 *
 * @subsection sub_guide_over_pc 1.1 PC Requirements
 *
 * A PC connected to the internet is used to download the software development kit (SDK)
 * and / or upgrade the firmware. For more details on upgrading the firmware, refer
 * to @ref getting_guide_upgrade_firmware "Upgrading the Firmware".
 *
 * The PC must be equipped with the following:
 *
 * <table>
 * <caption id="getting_guide_pc_require_usage">Table 1-1. PC Requirements.</caption>
 * <tr><th> Category          <th> Requirement
 * <tr><td> CPU               <td> Intel® i7 or higher grade
 * <tr><td> Memory            <td> 8 GB system memory or more
 * <tr><td> Hard disk         <td> 120 GB or more
 * <tr><td> Video card        <td> 3D hardware accelerator card required - 100% DirectX 9.0c compatible
 *                                 NVIDIA® GeForce GT520 or above to assure full frame rate of HD
 * <tr><td> Monitor           <td> 24-inch LCD or larger with a digital visual interface (DVI) input.
 *                                 A Dell UltraSharp 2709W (VA panel) is preferred
 * <tr><td> LCD TV            <td> 29-inch LCD TV or larger with YPbPr input (1080p resolution)
 * <tr><td> Ethernet card     <td> 1000 Mbps (adaptive)
 * <tr><td> I/O interfaces    <td> RS232
 * <tr><td> Operating system  <td> Windows 7 / 8 64 bit or Ubuntu 20.04 LTS 64 bit
 * <tr><td> Virtual machine   <td> Oracle® VirtualBox 5.0.32 or later
 * </table>
 *
 * - - - -
 *
 * @section getting_guide_hardware_cv5 2. Setting Up the CV5 EVK Hardware
 * For more information about setting up the CV5 EVK hardware, refer to @ref page_cv5_timn.
 *
 * - - - -
 *
 * @section getting_guide_hardware_cv52 3. Setting Up the CV52 EVK Hardware
 * For more information about setting up the CV52 EVK hardware, refer to @ref page_cv52_cocr.
 *
 * - - - -
 *
 * @section getting_guide_hardware_cv72 4. Setting Up the CV72 EVK Hardware
 * For more information about setting up the CV72 EVK hardware, refer to @ref page_cv72_gage.
 *
 * - - - -
 *
 * @section getting_guide_setting_pc 5. Setting Up the PC
 * Before proceeding to the steps in this chapter, review the software and PC requirements
 * listed in @ref sub_guide_over_pc and set up the EVK hardware following the steps in:
 *  - @ref getting_guide_hardware_cv5 "Chapter 2: Setting up the CV5 EVK Hardware"
 *  - @ref getting_guide_hardware_cv52 "Chapter 3: Setting up the CV52 EVK Hardware"
 *  - @ref getting_guide_hardware_cv72 "Chapter 4: Setting up the CV72 EVK Hardware"
 *
 * This chapter describes how to perform the following:
 *
 *   - Section @ref sub_guide_setting_pc_install
 *   - Section @ref sub_guide_setting_pc_network
 *   - Section @ref sub_guide_setting_pc_console
 *
 * @subsection sub_guide_setting_pc_install 5.1 Installing the EVK Software
 *
 * The following tools / folders will be installed on the host PC:
 *   - <b>AmbaUSB</b> (for Windows, Linux, and Mac) for upgrading firmware via USB.
 *     Contact Ambarella for tool release
 *   - <b>UART / Serial Console Tool</b>: Users can download and install any
 *     universal asynchronous receiver / transmitter (UART) /
 *     serial terminal tool for console access such as PuTTY, mini-com, MobaXterm, and more
 *   - <b>Google USB driver</b> for the fastboot device
 *   - <b>CH340 driver</b> for USB to serial drivers, including Windows, Linux, and Mac versions
 *
 * @note
 * When a CV5x / CV7x board connects to an Ubuntu PC, USB-to-serial chip may use the default Linux
 * driver and this driver cannot receive any input. To let serial accept input, CH343 driver needs
 * to download, compile, and load manually :
 *   -# Download the driver from https://github.com/WCHSoftGroup/ch343ser_linux
 *   -# Run `make` command to compile source code and generate `ch343.ko`
 *   -# Remove the default driver (usually contains with "cdc" or "acm") by executing command `sudo rmmod $module_name`
 *   -# Using command `sudo insmod ch343.ko` to load the new driver<br>
 * If there are no issues in commands above, users will find a new UART device: `/dev/ttyCH343USB0`
 *
 * @subsection sub_guide_setting_pc_network 5.2 Setting Up the Network
 *
 * This section details the procedure for using a static IP. Use the following steps to
 * enable access for the host PC to the EVK board via Ethernet.
 *
 * 1. Change the IP address of the PC network adaptor connected to the EVK board to 10.0.0.1.
 * Note that the default IP address of the EVK board is 10.0.0.2. The following figure
 * provides an example of the IP configuration on a Windows PC.
 * @image html getting_guide_ip_of_windows.png "Figure 5-1. IP Address of Windows Host PC."
 *
 * The destination is the IP address of the EVK board, 10.0.0.2.
 * @code {.c}
 * C:\Users\XXX\> ping 10.0.0.2
 *
 * Pinging 10.0.0.2 with 32 bytes of data:
 * Reply from 10.0.0.2: bytes=32 time=1ms TTL=64
 * Reply from 10.0.0.2: bytes=32 time<1ms TTL=64
 * Reply from 10.0.0.2: bytes=32 time<1ms TTL=64
 * Reply from 10.0.0.2: bytes=32 time<1ms TTL=64
 *
 * Ping statistics for 10.0.0.2:
 *     Packets: Sent = 4, Received = 4, Lost = 0 <0% loss>,
 * Approximate round trip times in milli-seconds:
 *     Minimum = 0ms, Maximum = 1ms, Average = 0ms
 * @endcode
 *
 * @subsection sub_guide_setting_pc_console 5.3 Connecting to a Console Window
 *
 * The console window enables users to view the system boot sequence messages and
 * run the demonstration applications from the Linux shell.
 *
 * @subsubsection dsub_guide_pc_console_serial 5.3.1 Serial
 *
 * 1. Connect a serial cable between the serial port on the EVK
 *    and the serial port (for example, COM1) on the host PC.
 *
 * 2. Open a terminal emulator (such as <b>Minicom</b> on Linux or <b>PuTTY / HyperTerminal</b>
 *    on Windows) on the host PC. Ambarella recommends using <b>PuTTY</b> on Windows. <b>PuTTY</b>
 *    can be found in the EVK tools.
 *
 * 3. Configure the terminal emulator to connect to the serial port using the following data:
 *    - <b>Speed</b>:        115200 (baud)
 *    - <b>Data Bits</b>:    8
 *    - <b>Parity</b>:       None
 *    - <b>Stop Bits</b>:    1
 *    - <b>Flow Control</b>: None
 *
 * The following provides the steps for connecting to a console window using <b>PuTTY</b> as an example:
 *
 * 1. From the <b>PuTTY</b> Configuration dialogue, choose <b>Category > Connection >
 *    Serial</b>. For <b>Serial Line to Connect To</b>, enter the correct port (for example, COM1).
 *    Use the settings below for <b>speed</b>, <b>data bits</b>, <b>parity</b>, <b>stop bits</b>, and <b>flow control</b>.
 * @image html getting_guide_serial_conf_1.png "Figure 5-2. PuTTY Serial Configuration (1)."
 *
 * 2. Using the <b>PuTTY</b> Configuration dialogue, choose <b>Category > Session</b>
 * for the Connection type. Then, enter in the following parameters:
 *   - <b>Connection type</b>: Serial
 *   - <b>Serial line</b>: COM 1
 *   - <b>Speed</b>: 11520
 * @image html getting_guide_serial_conf_2.png "Figure 5-3. PuTTY Serial Configuration (2)."
 *
 * 3. <b>Save</b> the current session (for example, Amba Serial) so it can be reused.
 *
 * 4. Click <b>Open</b> and the following console will appear:
 * @image html getting_guide_serial_connect.png "Figure 5-4. Connecting to a Serial Console."
 *
 * 5. Power on the EVK board and wait for the console to read the boot
 * sequence messages. After Linux boots up, log in as root.
 * @image html getting_guide_serial_boot.png "Figure 5-5. Boot Sequence Messages on the Serial Console."
 *
 * @subsubsection dsub_guide_pc_console_telent 5.3.2 Telnet
 * 1. Connect the EVK and the host PC using an Ethernet cable.
 *
 * 2. Open a terminal emulator (such as <b>Minicom</b> on Linux or <b>PuTTY / HyperTerminal</b>
 *    on Windows) on the host PC. Ambarella recommends using <b>PuTTY</b> on Windows, which can be
 *    found in the EVK tools.
 *
 * 3. Configure the terminal emulator to the Telnet connection type using:
 *   - <b>Host Name (or IP address)</b>:   10.0.0.2 (default)
 *   - <b>Port</b>:                        23
 *
 * The following provides steps for connecting to a console window, using <b>PuTTY</b> as an example:
 *
 * 1. From the <b>PuTTY</b> Configuration window, choose <b>Session</b>. In the right panel, select <b>Telnet</b>
 *    as the <b>connection type</b>. For <b>Host Name (or IP address)</b>, enter 10.0.0.2. For <b>Port</b>, enter 23.
 *    <b>Save</b> the session and click <b>Open</b>.
 *
 * 2. Log in as root.
 * @image html getting_guide_telent_conf.png "Figure 5-6. PuTTY Telnet Configuration."
 *
 * - - - -
 *
 * @section getting_guide_run_demo 6. Running Demo Applications
 *
 * This chapter describes how to perform the following:
 *
 *   - Section @ref sub_guide_demo_build
 *   - Section @ref sub_guide_demo_init
 *   - Section @ref sub_guide_demo_lua
 *   - Section @ref sub_guide_demo_preview
 *   - Section @ref sub_guide_demo_record
 *   - Section @ref sub_guide_demo_view
 *   - Section @ref sub_guide_demo_cnn
 *
 *  Users new to the Linux SDK demo applications are encouraged to carefully follow the
 *  instructions in this chapter.
 *  Advanced options with unit tests are explained in the Doxygen document within the SDK
 *  package. The applications referenced in this EVK getting started guide demonstrate the
 *  use of IAV input / output control (IOCTL).
 *  The benefits of the unit test include the following:
 *   - Minimizes the number of steps required to configure an individual feature, such as the
 *     configuration of the stream and starting the encoding process.
 *   - Stream a video that does not require application-level streaming protocol (such as
 *     real-time streaming protocol (RTSP)), as it is possible to save the video on the host PC.
 *   - Advanced options, such as on-screen display (OSD), privacy mask, and region of interest (ROI).
 *   - Hands-on experience with the unit test applications and source codes.
 *
 * @subsection sub_guide_demo_build 6.1 Building the Binary for the Board
 *
 * @subsubsection dsub_guide_demo_full 6.1.1 Full SDK Package
 *
 * 1. Decompress the SDK package file on the appropriate Linux building server.
 * @code {.c}
 * build $ cp cooper_linux_sdk_********.tar.xz workspace/.
 * build $ cd workspace/
 * build $ tar xvfJp cooper_linux_sdk_********.tar.xz
 * build $ ls -al
 * @endcode
 *
 * 2. Verify that <b>Arm® Linux</b> Toolchain is installed before compiling the SDK:
 * @par For Cooper Amba build
 * @code {.c}
 * build $ cd cooper_linux_sdk/ambarella/
 * build $ source build/env/amba-build.env
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build $ cd cooper_linux_sdk/ambarella/
 * build $ source build/env/yocto-build.env
 * @endcode
 *
 * 3. Enter the board directory. 'BOARD_NAME' can be be cv5_timn, cv52_crco, or cv72_gage.
 * @code {.c}
 * build $ cd boards/$BOARD_NAME
 * @endcode
 *
 * 4. There are several default configuration files in the directory `ambarella/boards/$BOARD_NAME/config`
 * @par For Cooper Amba build
 * @code {.c}
 * build $ ls -al config/amba/
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build $ ls -al config/yocto/
 * @endcode
 *
 * 5. Compile the binary for the specified CV5x / CV7x chips. Different chips will vary
 *    in their clock frequencies and performance.
 *   To evaluate CV5_Timn, use ipcam_config.
 * @code {.c}
 * build $ make ipcam_config
 * @endcode
 *
 *   To evaluate CV52_Cr, use ipcam_lp5_config, and to evaluate CV52_Co, use ipcam_lp4_config.
 * @code {.c}
 * build $ make ipcam_lp5_config
 * @endcode
 *
 *   To evaluate CV72_Ga, use ipcam_lp5_config, and to evaluate CV72_Ge, use ipcam_lp4_config.
 * @code {.c}
 * build $ make ipcam_config
 * @endcode
 *
 * 6. Begin compiling the binary for the specified CV5x / CV7x chips.
 * @code {.c}
 * build $ make -j 8
 * @endcode
 *
 * 7. For more details, refer to the page @ref ov_code_build.
 *
 * @subsubsection dsub_guide_demo_evaluation 6.1.2 Evaluation Package
 *
 * The purpose of evaluation SDK package is to help initial customers to
 * evaluate the standard SDK features with prebuild firmware (FW) on EVK.
 *
 * As long as customers kick off the formal project with Cooper
 * SDK, they will receive the formal SDK package release.
 *
 * This evaluation package provides the necessary header files and prebuild libraries for the user's
 * application. Because the package cannot generate a full binary that can run
 * on the EVK board, users must flash the binary in the package to the board,
 * upload the application to the board, and then run it.
 *
 * What users @b can do with evaluation package:
 * - Run the existing unit test utility and applications with instructions on EVK board for the standard SDK features.
 * - Convert the open source model or their own neural network (NN) model with CV toolchain and run one EVK board.
 * - Build their own application or unit test from the evaluation package.
 *
 *
 * What users @b cannot do with evaluation package :
 * - Verify advanced features such as secure boot, eMMC boot, or others.
 * - Upgrade the software modules with new versions of bug fixes.
 * - Build the entire FW with the updated driver, Linux kernel, and bootloader.
 *
 * Here are the steps for users to build applications:
 *
 * 1. Decompress the SDK package file on the Linux-based building server. Ensure that the folder
 *    name is not "CV5x" or "CV7x". Using the same build name as CV5x / CV7x creates a conflict
 *    with the build script.
 * @code {.c}
 * build $ cp cooper_linux_evaluation_sdk_********.tar.xz workspace/
 * build $ cd workspace/
 * build $ tar xf cooper_linux_evaluation_sdk_********.tar.xz
 * build $ ls -al
 * @endcode
 *
 * 2. Verify that the <b>Arm® Linux</b> toolchain is installed before compiling the SDK:
 * @par For Cooper Amba build
 * @code {.c}
 * build $ cd cooper_linux_sdk/ambarella/
 * build $ source build/env/amba-build.env
 * @endcode
 *
 * 3. Change the configuration options and rebuild the application, following the same steps as in CV5_Timn.
 * @par For Cooper Amba build
 * @code {.c}
 * build $ cd boards/cv5_timn
 * build $ make ipcam_config
 * build $ make menuconfig
 *     drv_modules  --->
 *          private  --->
 *           -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *               (4)   Max VIN Channel Number
 * build $ make <app_name>
 * @endcode
 *
 * @note
 *  - User is required to configure the max video input (VIN) channel
 *    number as it is configured in the prebuild binary for a four-sensor VIN.
 *  - For more details, refer to the page @ref ov_code_build.
 *
 * @subsection sub_guide_demo_init 6.2 Initializing the Board
 *
 * 1. Open a console window connected to the evaluation board and log in as root; no password is
 * required. Refer to Section @ref sub_guide_setting_pc_console for how to connect to a console window.
 *
 * 2. Initialize the board. Load the `script init.sh` into the essential drivers and microcode.<br>
 *
 *    The command for imx274_mipi is as follows:
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board # init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * @endcode
 *
 * 3. The following messages will print if the initialization is successful. Confirm that the sensor
 *    name is in the message.
 * @code {.c}
 * /bin:/sbin:/usr/bin:/usr/sbin:/usr/bin/X11:/usr/local/bin:/usr/local/sbin
 * Init without VIN drivers...
 * Default init without lens driver
 * Use default settings
 * map_size = 0xa00000, nr_item = 9
 * addr_offset = 0x00000000, filename = orccode.bin
 * addr_offset = 0x00200000, filename = orcvin.bin
 * addr_offset = 0x00300000, filename = orcidsp0.bin
 * addr_offset = 0x00500000, filename = orcidsp1.bin
 * addr_offset = 0x00700000, filename = orcme0.bin
 * addr_offset = 0x00740000, filename = orcme1.bin
 * addr_offset = 0x00780000, filename = orcmdxf0.bin
 * addr_offset = 0x007c0000, filename = orcmdxf1.bin
 * addr_offset = 0x00800000, filename = default_binary.bin
 * mmap returns 0x7fbd9f3000
 * loading /lib/firmware/orccode.bin...addr = 0x7fbd9f3000, size = 0x101a38
 * loading /lib/firmware/orcvin.bin...addr = 0x7fbdbf3000, size = 0x9b684
 * loading /lib/firmware/orcidsp0.bin...addr = 0x7fbdcf3000, size = 0x13f094
 * loading /lib/firmware/orcidsp1.bin...addr = 0x7fbdef3000, size = 0x13f094
 * loading /lib/firmware/orcme0.bin...addr = 0x7fbe0f3000, size = 0x9618
 * loading /lib/firmware/orcme1.bin...addr = 0x7fbe133000, size = 0x9618
 * loading /lib/firmware/orcmdxf0.bin...addr = 0x7fbe173000, size = 0x1690c
 * loading /lib/firmware/orcmdxf1.bin...addr = 0x7fbe1b3000, size = 0x16878
 * loading /lib/firmware/default_binary.bin...addr = 0x7fbe1f3000, size = 0x79e60
 * ===============================================
 * ucode (CV5) version = 2021/8/6 (hash : 0x8504240a)
 * @endcode
 *
 * @subsection sub_guide_demo_lua 6.3 Lua Introduction
 *
 * This section provides examples of how CV5x or CV7x uses a Lua script to configure the system.
 * Locate `cv5_vin0_1080p_linear.lua` for the 720p example in
 * `ambarella/unit_test/private/iav_test/dsp_v6/scripts/cv5`.
 *
 *  1. Configure the VIN. The following example uses VIN0 as a linear 1080p30.
 * @code {.c}
 * vsrc_0 = {
 * 	vsrc_id = 0,
 * 	mode = "1080p",
 * 	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 * 	fps = 30,
 * }
 * @endcode
 *
 *  2. Configure the channel buffer. The example below uses VIN0 for the input
 *     source of channel0, which includes three buffers. The main buffer is 1080p,
 *     the second buffer is 480p, and the third buffer is 720p. The pyramid buffer
 *     is used for the vector processor (VP) input.
 * @code {.c}
 * chan_0 = {
 * 	id = 0,
 * 	vsrc = vsrc_0,
 * 	... ...
 * 	main = {
 * 		max_output = {1920, 0},
 * 		input      = {0, 0, 1920, 1080},
 * 		output     = {0, 0, 1920, 1080},
 * 	},
 * 	second = {
 * 		max_output = {720, 0},
 * 		input      = {0, 0, 1920, 1080},
 * 		output     = {0, 0, 720, 480},
 * 	},
 * 	third = {
 * 		max_output = {1280, 0},
 * 		input      = {0, 0, 1920, 1080},
 * 		output     = {0, 0, 1280, 720},
 * 	},
 * 	... ...
 * }
 * @endcode
 *
 *  3. Configure the stream. The following example uses three streams: two streams as 1080p
 *     and one stream as 480p. This is a basic stream setting that does not specify
 *     the canvas buffer or encode solution.
 * @code {.c}
 * stream_0 = {
 * 	id = 0,
 * 	max_size = {1920, 1080},
 * 	max_M = 1,
 * 	max_N = 30,
 * 	fast_seek_enable = 0,
 * 	two_ref_enable = 0,
 * 	max_svct_layers_minus_1 = 0,
 * 	max_num_minus_1_ltrs = 0,
 * 	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
 * }
 *
 * stream_1 = {
 * 	id = 1,
 * 	max_size = {1920, 1080},
 * 	max_M = 1,
 * 	max_N = 30,
 * 	fast_seek_enable = 0,
 * 	two_ref_enable = 0,
 * 	max_svct_layers_minus_1 = 0,
 * 	max_num_minus_1_ltrs = 0,
 * 	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
 * }
 *
 * stream_2 = {
 * 	id = 2,
 * 	max_size = {720, 480},
 * 	max_M = 1,
 * 	max_N = 30,
 * 	fast_seek_enable = 0,
 * 	two_ref_enable = 0,
 * 	max_svct_layers_minus_1 = 0,
 * 	max_num_minus_1_ltrs = 0,
 * 	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
 * }
 * @endcode
 *
 *  4. Configure the canvas buffer. The following example shows three configured buffers:
 *     two buffers that are used for encoding, and one buffer used for preview. This setting binds the
 *     canvas buffer to two different places, the channel buffer and the stream or preview buffer.
 * @code {.c}
 * _resource_config_ = {
 * 	version = 1,
 * 	channels = {
 * 		chan_0,
 * 		chan_1,
 * 	},
 * 	canvas = {
 * 		{
 * 			type = "encode",
 * 			size = {1920, 1080},
 * 			source = {"chan_0.main",},
 * 			extra_dram_buf = 0,
 * 		},
 * 		{
 * 			type = "encode",
 * 			size = {720, 480},
 * 			source = {"chan_0.second",},
 * 			extra_dram_buf = 0,
 * 		},
 * 		{
 * 			type = "prev",
 * 			size = {1280, 720},
 * 			source = {"chan_0.third", },
 * 			vout_id = 2,
 * 			extra_dram_buf = 0,
 * 		},
 * 	},
 * 	streams = {
 * 		stream_0,
 * 		stream_1,
 * 		stream_2,
 * 	},
 * }
 * @endcode
 *
 * The setting shown above is for the 720p preview. To use the 1080p preview, modify the
 * script as shown in the example below:
 * @code {.c}
 * chan_0 = {
 * 	id = 0,
 * 	vsrc = vsrc_0,
 * 	... ...
 * 	third = {
 * 		max_output = {1080, 0},
 * 		input      = {0, 0, 1920, 1080},
 * 		output     = {0, 0, 1920, 1080},
 * 	},
 * 	... ...
 * }
 *
 * _resource_config_ = {
 * 	version = 1,
 * 	channels = {
 * 		chan_0,
 * 		chan_1,
 * 	},
 * 	canvas = {
 * 		... ...
 * 		{
 * 			type = "prev",
 * 			size = {1920, 1080},
 * 			source = {"chan_0.third", },
 * 			vout_id = 2,
 * 			extra_dram_buf = 0,
 * 		},
 * 	},
 * 	... ...
 * }
 * @endcode
 *
 * The script can be adapted to fit additional resolutions in the same manner.
 * For more information about this script, refer to Section @ref sub_guide_demo_record.
 *
 * @subsection sub_guide_demo_preview 6.4 Previewing HDMI / CVBS
 *
 * In order to obtain a video preview, the board must be initialized as described in Section @ref sub_guide_demo_build
 *
 * Additionally, users must prepare the Lua script. Refer to Section @ref sub_guide_demo_lua.
 *
 * For the preview, ensure that the high-definition multimedia interface (HDMI®) cable is connected to the board.
 *
 * The serial console sends the message "Video output (VOUT) notice: HDMI Device Connected!". The
 * demo below is only applicable for running image digital signal processing (IDSP).
 *
 * HDMI preview 720p:
 * @code {.c}
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 * @endcode
 *
 * HDMI preview 1080p:
 * @code {.c}
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * HDMI preview 4K:
 * @code {.c}
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_4k.lua
 * @endcode
 *
 * @note
 *  If the user possesses a different version of the Lua script from those shown above,
 *  the script must be modified to accommodate a different solution.
 *
 * @subsection sub_guide_demo_record 6.5 Recording a Stream
 *
 * The following steps demonstrate how to record a stream in H.264 / H.265 file formats:
 *
 * 1. Initialize the board.
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board # init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * @endcode
 *  - See Section @ref sub_guide_demo_build for detailed steps on how to initialize other sensors.
 *
 * 2. Enter preview to start the image process.
 * @code {.c}
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 * @endcode
 *
 * 3. See section @ref sub_guide_demo_lua for more details on how to get previews of other resolutions.
 *
 * 4. Start the streaming application and specify the record directory on the Cooper platform.
 * @code {.c}
 * board # test_stream -A -f /tmp/
 * @endcode
 *
 * 5. Start the encoding stream(s) in H.264 format.
 * @code {.c}
 * board # test_encode -A -h 1080p -e
 * @endcode
 *
 * @note
 *  The default value for the canvas buffer is 0; therefore, it is important to pick a specific
 *  canvas buffer. Additionally, if two streams use the same buffer, add  `extra_dram_buf`.
 *
 * 6. Switch to the test_stream console. The message shown below indicates that the
 *    stream(s) is starting to encode and record the stream.
 *
 *   Successfully begin the encoding for stream 0x1.
 * @code {.c}
 * board #
 * new session file name [/tmp/_A_1216133253_f9656517.h264], fd [6]
 * stream A:       30 frames, 31.23 fps,             972794        bytes,  7912 kbps, enc_pipe_time [ 3969: 4542]
 * stream A:       60 frames, 30.00 fps,            2058917        bytes,  8485 kbps, enc_pipe_time [ 3969: 4617]
 * stream A:       90 frames, 30.00 fps,            3108975        bytes,  8204 kbps, enc_pipe_time [ 3969: 4617]
 * @endcode
 *
 * 7. Stop encoding.
 * @code {.c}
 * board # test_encode -A -s
 * @endcode
 *
 *  Or
 * @code {.c}
 * board # test_encode -A -s -B -s
 * @endcode
 *
 * 8. Once the stream has been terminated, users can check the record file and send the file
 * to the PC through file transfer protocol (FTP). The video file can be played via VideoLAN Client (VLC).
 * Ensure that the VLC configuration is as per @ref sub_guide_demo_view.
 *
 * 9. To restart encoding for a new stream, repeat steps 4 through 7.
 *
 * @subsection sub_guide_demo_view 6.6 Viewing Streams through VLC
 *
 * When the RTSP server is running, view livestreams using the VLC media player as an RTSP client.
 *
 * The following steps describe viewing streams through VLC:
 *
 * 1. Initialize, run the RTSP server, and start encoding.
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board # init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua        // For CV5 or CV52
 * (Or board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua)  // For CV72
 * board # rtsp_server &
 * board # test_encode -A -h1080p -e
 * @endcode
 *
 * 2. Launch VLC. Confirm that the VLC is configured as described in Section @ref sub_guide_setting_pc_network.
 *
 * 3. Select Media > Open Network Stream.
 * @image html getting_guide_network_vlc.png "Figure 6-1. Open Network Stream in VLC."
 *
 * 4. Input the RTSP URL that coordinates with the desired stream:
 *  - rtsp://10.0.0.2/stream1 identifies the first stream.
 *  - rtsp://10.0.0.2/stream2 identifies the second stream.
 *  - rtsp://10.0.0.2/stream3 identifies the third stream.
 *  - rtsp://10.0.0.2/stream4 identifies the fourth stream.
 *
 * 5. Select "Show more options". Enter a smaller value for caching (such as 200 ms). Click "Play".
 * @image html getting_guide_rtsl_vlc.png "Figure 6-2. RTSP URL of the First Stream in VLC."
 *
 * 6. The livestream plays in VLC.
 * @image html getting_guide_view_vlc.png "Figure 6-3. View the First Stream in VLC."
 *
 * @subsection sub_guide_demo_cnn 6.7 Run CNN
 *
 * The computer vision (CV) demonstrations below are based on public network files with public
 * data sets, except <b>OpenNet</b> and <b>BiSeNet</b>, which are trained with Ambarella data.
 *
 *   - For public network use, follow the original license statement for the model files.
 * For the detailed URL of these model files, refer to the CNNGen samples package.
 *
 * Contact the Ambarella support team for assistance with Ambarella models.
 *
 * @subsubsection dsub_guide_demo_cnn_full 6.7.1 Full SDK Package
 *
 * Compile the binary with "cv5x_ipcam_config" for CV5x, and "cv7x_ipcam_config" for CV7x.
 * The default configuration file is located in `$SDK_ROOT/ambarella/$BOARD_NAME/config`.
 *
 * The demonstration network models are not included in the SDK package. The
 * following text provides two methods to get the network deployment binaries:
 *
 *   - Use the CNNGen samples package to generate the network deployment binaries. For more details,
 *     refer to `fs_cnngen_samples_pacakge.html` in the Doxygen document, which can be found in the
 *     CNNGen samples package. Users can also use <b>CNNGUI</b> to easily set up these
 *     demos, which is described in this section.
 *   - Contact the Ambarella support team to share the pre-converted network binary.
 *
 * <b>Resnet50</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p
 * board # osd_server_imagenet -p 27182 -n imagenet_1000.txt &
 * board # test_nnctrl_live -p 27182 -b resnet50_cavalry_fix8_full.bin --in data --out prob -s 0 -i 0 -t 1
 * @endcode
 *
 * This demonstration is not selected in the default configuration. Select the option below to enable it.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  app  --->
 *    ai_cam  --->
 *      [*] cvflow-test (app/ai_cam/cvflow)  --->
 *        [*]   Build imagenet unit tests
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambaapp --->
 *       recipes-test --->
 *          [*] cvflow-test (meta-ambaapp/recipes-test/cvflow-test)  --->
 *                [*]   Build imagenet unit tests
 * @endcode
 *
 * @note
 *  - Use `make resnet50` to generate `resnet50_cavalry_fix8_full.bin` in the CNNGen samples package.
 *  - The `imagenet_1000.txt` is located in the folder path `ambarella/app/ai_cam/cvflow/imagenet`.
 *
 * <b>YOLO-v3</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 720p
 * board # osd_server_yolov3 -p 27182 -f /usr/share/ambarella/eazyai/lua/yolov3_sp50_full.lua &
 * board # test_nnctrl_live -p 27182 -b yolo_v3_cavalry_fix8_sp50.bin -s 0 -i 1 --in data --out conv59 --out conv67 --out conv75 -t 0 -r 0.00390625
 * @endcode
 *
 * This demonstration is not selected in the default configuration. Select the option below to enable it.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  app  --->
 *    ai_cam  --->
 *      [*] cvflow-test (app/ai_cam/cvflow)  --->
 *        [*]   Build yolov3 unit tests
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambaapp --->
 *       recipes-test --->
 *          [*] cvflow-test (meta-ambaapp/recipes-test/cvflow-test)  --->
 *                 [*]   Build yolov3 unit tests
 * @endcode
 *
 * @note
 *  Use `make yolo_v3_sp50_amb_quant` to generate `yolo_v3_sp50_amb_quant_cavalry.bin` in the CNNGen samples package.
 *
 * <b>YOLO-v3</b> with YUV input:
 * @code {.c}
 * board # eazyai_video.sh --vin lt6911 --hdmi 720p
 * board # osd_server_yolov3 -p 27182 -f /usr/share/ambarella/eazyai/lua/yolov3_sp50_full.lua &
 * board # test_nnctrl_live -p 27182 -b yolo_v3_cavalry_fix8_sp50.bin -s 0 -i 1 --in data --out conv59 --out conv67 --out conv75 -t 0 -r 0.00390625
 * @endcode
 *
 * @note
 *  - If LT6911 is unstable, delete the LT6911 default microcontroller unit (MCU) code using the command `test_vin -w 0xffff`.
 *  - If the YUV input is selected, set the mode to "0" for the `vsrc_id` option in the Lua script.
 *
 * <b>FD (MTCNN)</b> with the sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p
 * board # test_mtcnn -m 0 -i /sdcard/mtcnn/in -o /sdcard/mtcnn/out -b 0 -a 0
 * @endcode
 *
 * This demonstration is not selected in the default configuration. To enable it, select the option below.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  packages  --->
 *   eazyai --->
 *     apps --->
 *        eazyai-apps-test-face (packages/eazyai/apps/face) --->
 *         [*]   Build MTCNN EazyAI apps
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *   meta-ambaapp --->
 *       recipes-test --->
 *           [*] eazyai-test@virtual (meta-ambaapp/recipes-test/eazyai-test) --->
 *               [*] eazyai-apps-test@virtual (meta-ambaapp/recipes-test/eazyai-test/eazyai-apps-test) --->
 *                   [*] eazyai-apps-test-face (meta-ambaapp/recipes-test/eazyai-test/eazyai-apps-test) --->
 *                        [*]   Build MTCNN EazyAI apps
 * @endcode
 *
 * Place the files on the SD card with the following structure:
 * @code {.c}
 * /sdcard/mtcnn
 * ├───in
 * │       faces01.jpg
 * │       faces02.jpg
 * │       pnet_216x384_cavalry.bin
 * │       pnet_154x273_cavalry.bin
 * │       pnet_109x194_cavalry.bin
 * │       pnet_77x137_cavalry.bin
 * │       pnet_55x98_cavalry.bin
 * │       pnet_39x69_cavalry.bin
 * │       pnet_28x49_cavalry.bin
 * │       pnet_20x35_cavalry.bin
 * │       pnet_14x25_cavalry.bin
 * │       rnet_cavalry.bin
 * │       onet_cavalry.bin
 * │
 * └───out
 * @endcode
 *
 * @note
 *  - Use `make pnet` to generate ten PNet binaries with the input resolution modification
 *    for `prototxt` and `make menuconfig` in the CNNGen samples package.
 *  - Then, use `make onet` and `make rnet` for onet and rnet. For more details, refer to
 *    <em>fs_cnngen_caffe_demos.html#sec_caffe_mtcnn</em> in the Doxygen document in the CNNGen samples package.
 *  - Use the CNNGen samples package to generate ten PNet models with different input resolutions,
 *    one RNet model, and one ONet model. The PNet models' name must be `pnet*.bin`, the RNet model
 *    name must be `rnet*.bin`, and the ONet model name must be `onet*.bin` to be read by the `test_mtcnn` demonstration.
 *  - Place all Cavalry bin models on the SD card, such as under `/sdcard/mtcnn/in`.
 *
 * <b>Face detection and face recognition (FDFR) (RetinaFace and MobileFaceNet)</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p
 * board # test_fdfr_v2 -m 0 -i /sdcard/fdfr/in -o /sdcard/fdfr/out -b 0 -a 0 -f 0.8,0.7
 * @endcode
 *
 * This demonstration is not selected in the default configuration. To enable the demonstration, select the option below.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  packages  --->
 *   eazyai --->
 *     apps --->
 *        eazyai-apps-test-face (packages/eazyai/apps/face) --->
 *         [*]  Build FDFR V2 EazyAI apps
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *   meta-ambaapp --->
 *       recipes-test --->
 *           [*] eazyai-test@virtual (meta-ambaapp/recipes-test/eazyai-test) --->
 *               [*] eazyai-apps-test@virtual (meta-ambaapp/recipes-test/eazyai-test/eazyai-apps-test) --->
 *                   [*] eazyai-apps-test-face (meta-ambaapp/recipes-test/eazyai-test/eazyai-apps-test) --->
 *                         [*]  Build FDFR V2 EazyAI apps
 * @endcode
 *
 * Place the files on the SD card with the following structure:
 * @code {.c}
 *     /sdcard/fdfr
 *     ├───in
 *     │       faces01.jpg
 *     │       faces02.jpg
 *     │       onnx_retinaface_cavalry.bin
 *     │       mobilefacenets_cavalry.bin
 *     │
 *     └───out
 * @endcode
 *
 * @note
 *  - Use `make onnx_retinaface` to generate the Cavalry binary in the CNNGen samples package
 *    and rename it to `onnx_retinaface_cavalry.bin`. Then, place it in `/sdcard/fdfr/in`.
 *  - Use `make mobilefacenets` to generate the Cavalry binary in the CNNGen samples package
 *    and rename it to `mobilefacenets_cavalry.bin`. Then, place it in `/sdcard/fdfr/in`.
 *
 * <b>BiSeNet</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 720p --fb_res 320x180
 * board # test_eazyai -m 0 -d 1 --model_path bisenet_cavalry.bin -n bisenet --lua_file /usr/share/ambarella/eazyai/lua/bisenet.lua -c 2 --roi 0,0,512,1280
 * @endcode
 *
 * This demonstration is not selected in the default configuration. Select the option below to enable it.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  packages  --->
 *   eazyai --->
 *     -*- libeazyai-arm-postprocess (packages/eazyai/unit_test)  --->
 *        [*]   Build Ambarella custom postprocess library with bisenet
 *     [*] eazyai-unit-test (packages/eazyai/unit_test)
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambaapp --->
 *        recipes-test --->
 *           [*] eazyai-test@virtual (meta-ambaapp/recipes-test/eazyai-test) --->
 *                [*]   eazyai-unit-test (meta-ambaapp/recipes-test/eazyai-test/eazyai-unit-test)
 *    meta-ambalib --->
 *        recipes-eazyai --->
 *           -*- libeazyai-arm-postprocess (meta-ambalib/recipes-eazyai/libeazyai)  --->
 *                 [*]   Build Ambarella custom postprocess library with bisenet
 * @endcode
 *
 * @note
 *  - Use `make bisenet` to generate `bisenet_cavalry.bin` in the CNNGen samples package.
 *  - Set the input buffer resolution to 1280x720 and the frame buffer to 320x180. The real
 *    network input is 1280x512, and the network output is 320x128. The bottom has no detection
 *    as it is the headstock. On the top of the screen, it will detect "freespace", "lanemark",
 *    and "curb", which are used for auto-driving.
 *  - Ambarella recommends using HDMI VIN as a test case.
 *
 * <b>OpenNet</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 720p
 * board # test_eazyai -m 0 -d 0 --model_path opennet.bin -n opennet --lua_file /usr/share/ambarella/eazyai/lua/opennet.lua --extra_input arm_priorbox.bin
 * @endcode
 *
 * This demonstration is not selected in the default configuration. Select the option below to enable it.
 * @par For Cooper amba build
 * @code {.language-id}
 * build $ make menuconfig
 *  packages  --->
 *   eazyai --->
 *     -*- libeazyai-arm-postprocess (packages/eazyai/unit_test)  --->
 *        [*]   Build Ambarella custom postprocess library with opennet
 *     [*] eazyai-unit-test (packages/eazyai/unit_test)
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *   meta-ambalib --->
 *      recipes-eazyai --->
 *         -*- libeazyai-arm-postprocess (meta-ambalib/recipes-eazyai/libeazyai) --->
 *               [*]   Build Ambarella custom postprocess library with opennet
 *    meta-ambaapp --->
 *        recipes-test --->
 *           [*] eazyai-test@virtual (meta-ambaapp/recipes-test/eazyai-test) --->
 *                [*]   eazyai-unit-test (meta-ambaapp/recipes-test/eazyai-test/eazyai-unit-test)
 * @endcode
 *
 * @note
 *  - Use `make opennet` to generate `opennet_cavalry.bin` in the CNNGen samples package.
 *  - The `arm_priorbox.bin` is located in the path `cnngen_samples\caffe\demo_networks\opennet\models`,
 *    and demonstrated in the following example.
 *  - The code is similar to BiSeNet. Do not modify any of the commands.
 *
  * @subsubsection dsub_guide_demo_cnn_eva 6.7.2 Evaluation Package
 *
 * Follow the steps below to run the demonstration using the evaluation package.
 *
 * 1. Flash the binary released together with the evaluation package.
 *   - `cv5_ipcam_config_evaluation_sdk_*.bin`: For the CV5 EVK board that is compiled into a maximum of four channels
 *   - `cv52_ipcam_lp4/lp5_config_evaluation_sdk_*.bin`: For the CV52 EVK board that is compiled into a maximum of four channels
 *   - `cv72_ipcam_lp4/lp5_config_evaluation_sdk_*.bin`: For the CV72 EVK board that is compiled into a maximum of four channels
 * 2. Run the applications using the EVK board.
 *
 * @note
 * The demonstration network models are not included in the SDK package. The following text
 * provides two methods for the user to get the network deployment binary.
 * - Use the CNNGen samples package to generate. For more details, refer to <em>fs_cnngen_samples_pacakge.html</em>
 *   in the Doxygen document in the CNNGen samples package. Users also can use <b>CNNGUI</b> to easily set up
 *   these demos, which are mentioned in this section.
 * - Contact the Ambarella support team to share the pre-converted network binary.
 *
 * <b>Resnet50</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p
 * board # osd_server_imagenet -p 27182 -n imagenet_1000.txt &
 * board # test_nnctrl_live -p 27182 -b resnet50_cavalry_fix8_full.bin --in data --out prob -s 0 -i 0 -t 1
 * @endcode
 *
 * This demonstration is not selected in the default configuration. Select the option below to enable it.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  app  --->
 *    ai_cam  --->
 *      [*] cvflow-test (app/ai_cam/cvflow)  --->
 *        [*]   Build imagenet unit tests
 * @endcode
 * @note
 *  - Use `make resnet50` to generate `resnet50_cavalry_fix8_full.bin` in the CNNGen samples package.
 *  - The `imagenet_1000.txt` is located in the folder path `ambarella/app/ai_cam/cvflow/imagenet`.
 *
 * <b>YOLO-v3</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 720p
 * board # osd_server_yolov3 -p 27182 -f /usr/share/ambarella/eazyai/lua/yolov3_sp50_full.lua &
 * board # test_nnctrl_live -p 27182 -b yolo_v3_cavalry_fix8_sp50.bin -s 0 -i 1 --in data --out conv59 --out conv67 --out conv75 -t 0 -r 0.00390625
 * @endcode
 *
 * This demonstration is not selected in the default configuration. Select the option below to enable it.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  app  --->
 *    ai_cam  --->
 *      [*] cvflow-test (app/ai_cam/cvflow)  --->
 *        [*]   Build yolov3 unit tests
 * @endcode
 *
 * @note
 *  Use `make yolo_v3_sp50_amb_quant` to generate `yolo_v3_sp50_amb_quant_cavalry.bin` in the CNNGen samples package.
 *
 * <b>YOLO-v3</b> with YUV input:
 * @code {.c}
 * board # eazyai_video.sh --vin lt6911 --hdmi 720p
 * board # osd_server_yolov3 -p 27182 -f /usr/share/ambarella/eazyai/lua/yolov3_sp50_full.lua &
 * board # test_nnctrl_live -p 27182 -b yolo_v3_cavalry_fix8_sp50.bin -s 0 -i 1 --in data --out conv59 --out conv67 --out conv75  -t 0 -r 0.00390625
 * @endcode
 *
 * @note
 *  - If LT6911 is unstable, delete the LT6911 default MCU code using the command `test_vin -w 0xffff`.
 *  - If YUV input is selected, set the mode to "0" for the `vsrc_id` option in the Lua script.
 *
 * <b>FD (MTCNN)</b> with the sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p
 * board # test_mtcnn -m 0 -i /sdcard/mtcnn/in -o /sdcard/mtcnn/out -b 0 -a 0
 * @endcode
 *
 * This demonstration is not selected in the default configuration. To enable it, select the option below.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  packages  --->
 *   eazyai --->
 *     apps --->
 *        eazyai-apps-test-face (packages/eazyai/apps/face) --->
 *         [*]   Build MTCNN EazyAI apps
 * @endcode
 *
 * Place the files on the SD card with the following structure:
 * @code {.c}
 * /sdcard/mtcnn
 * ├───in
 * │       faces01.jpg
 * │       faces02.jpg
 * │       pnet_216x384_cavalry.bin
 * │       pnet_154x273_cavalry.bin
 * │       pnet_109x194_cavalry.bin
 * │       pnet_77x137_cavalry.bin
 * │       pnet_55x98_cavalry.bin
 * │       pnet_39x69_cavalry.bin
 * │       pnet_28x49_cavalry.bin
 * │       pnet_20x35_cavalry.bin
 * │       pnet_14x25_cavalry.bin
 * │       rnet_cavalry.bin
 * │       onet_cavalry.bin
 * │
 * └───out
 * @endcode
 *
 * @note
 *  - Use `make pnet` to generate ten PNet binaries with the input resolution modification
 *    for `prototxt` and `make menuconfig` in the CNNGen samples package.
 *  - Then, use `make onet` and `make rnet` for onet and rnet. For more details, refer to
 *    <em>fs_cnngen_caffe_demos.html#sec_caffe_mtcnn</em> in the Doxygen document in the CNNGen samples package.
 *  - Use the CNNGen samples package to generate ten PNet models with different input resolutions,
 *    one RNet model, and one ONet model.  The PNet models' name must be `pnet*.bin`, the RNet model
 *    name must be `rnet*.bin`, and the ONet model name must be `onet*.bin` to be read by the `test_mtcnn` demonstration.
 *  - Place all Cavalry bin models on the SD card, such as under `/sdcard/mtcnn/in`.
 *
 * <b>FDFR (RetinaFace and MobileFaceNet)</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p
 * board # test_fdfr_v2 -m 0 -i /sdcard/fdfr/in -o /sdcard/fdfr/out -b 0 -a 0 -f 0.8,0.7
 * @endcode
 *
 * This demonstration is not selected in the default configuration. To enable the demonstration, select the option below.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  packages  --->
 *   eazyai --->
 *     apps --->
 *        eazyai-apps-test-face (packages/eazyai/apps/face) --->
 *         [*]   Build FDFR V2 EazyAI apps
 * @endcode
 * Place the files on the SD card with the following structure:
 * @code {.c}
 *     /sdcard/fdfr
 *     ├───in
 *     │       faces01.jpg
 *     │       faces02.jpg
 *     │       onnx_retinaface_cavalry.bin
 *     │       mobilefacenets_cavalry.bin
 *     │
 *     └───out
 * @endcode
 *
 * @note
 *  - Use `make onnx_retinaface` to generate the Cavalry binary in the CNNGen samples package
 *    and rename it to `onnx_retinaface_cavalry.bin`. Then, place it in `/sdcard/fdfr/in`.
 *  - Use `make mobilefacenets` to generate the Cavalry binary in the CNNGen samples package
 *    and rename it to `mobilefacenets_cavalry.bin`. Then, place it in `/sdcard/fdfr/in`.
 *
 * <b>BiSeNet</b> with the sensor input:
 * @code {.c}
 * board  # eazyai_video.sh --hdmi 720p --fb_res 320x180
 * board  # test_eazyai -m 0 -d 1 --model_path bisenet_cavalry.bin -n bisenet --lua_file /usr/share/ambarella/eazyai/lua/bisenet.lua -c 2 --roi 0,0,512,1280
 * @endcode
 *
 * This demonstration is not selected in the default configuration. Select the option below to enable it.
 * @par For Cooper amba build
 * @code {.language-id}
 * build $ make menuconfig
 *  packages  --->
 *   eazyai --->
 *     -*- libeazyai-arm-postprocess (packages/eazyai/unit_test)  --->
 *        [*]   Build Ambarella custom postprocess library with opennet
 *     [*] eazyai-unit-test (packages/eazyai/unit_test)
 * @endcode
 *
 * @note
 *  - Use `make bisenet` to generate `bisenet_cavalry.bin` in the CNNGen samples package.
 *  - Set the input buffer resolution to 1280x720 and the frame buffer to 320x180. The real
 *    network input is 1280x512, and the network output is 320x128. The bottom has no detection,
 *    as it is the headstock. On the top of the screen, it will detect "freespace", "lanemark",
 *    and "curb", which are used for auto-driving.
 *  - Ambarella recommends using HDMI VIN as a test case.
 *
 * <b>OpenNet</b> with sensor input:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 720p
 * board # test_eazyai -m 0 -d 0 --model_path opennet.bin -n opennet --lua_file /usr/share/ambarella/eazyai/lua/opennet.lua --extra_input arm_priorbox.bin
 * @endcode
 *
 * This demonstration is not selected in the default configuration. Select the option below to enable it.
 * @par For Cooper Amba build
 * @code {.language-id}
 * build $ make menuconfig
 *  packages  --->
 *   eazyai --->
 *     -*- libeazyai-arm-postprocess (packages/eazyai/unit_test)  --->
 *        [*]   Build Ambarella custom postprocess library with opennet
 *     [*] eazyai-unit-test (packages/eazyai/unit_test)
 * @endcode
 *
 * @note
 *  - Use `make opennet` to generate `opennet_cavalry.bin` in the CNNGen samples package.
 *  - The `arm_priorbox.bin` is located in the path `cnngen_samples\caffe\demo_networks\opennet\models`,
 *    and demonstrated in the following example.
 *  - The code is similar to BiSeNet. Do not modify any of the commands.
 *
 *
 * - - - -
 *
 * @section getting_guide_upgrade_firmware 7. Upgrading the Firmware
 *
 * This chapter includes the following sections:
 *
 *   - Section @ref sub_guide_firmware_down
 *   - Section @ref sub_guide_firmware_fastboot_ubu
 *   - Section @ref sub_guide_firmware_fastboot_win
 *   - Section @ref sub_guide_firmware_ambausb_ubu
 *   - Section @ref sub_guide_firmware_ambausb_win
 *
 * @subsection sub_guide_firmware_down 7.1 Enter USB Download Mode
 *
 * There are two ways to switch the platform to USB download mode:
 * 	- Enter USB download mode from <b>AMBoot</b> shell.
 * 	- Enter USB download mode from USB boot, which is used when the bootloader (BLD) malfunctions.
 *
 * Steps 1 through 3 below describe how to enter USB download mode from the <b>AMBoot</b> shell.
 * If the console shows no response from the platform, proceed to step 4.
 *
 * 1. Connect the platform and the PC using a USB cable.
 *
 * 2. Verify that the dual in-line package (DIP) switches are in NAND boot mode.
 * @image html getting_guide_dip_cv5.png "Figure 7-1. DIP Switches in NAND Boot Mode."
 *
 * 3. Connect to the serial console.
 *
 * 4. In the serial console, press and hold the <b>Enter</b> key on the keyboard, and then press
 * the hardware <b>RESET</b> button. The development platform will switch to the <b>AMBoot</b> shell,
 * as shown in the below.
 * @code {.c}
 *              ___  ___  _________                _
 *             / _ \ |  \/  || ___ \              | |
 *            / /_\ \| .  . || |_/ /  ___    ___  | |_
 *            |  _  || |\/| || ___ \ / _ \  / _ \ | __|
 *            | | | || |  | || |_/ /| (_) || (_) || |_
 *            \_| |_/\_|  |_/\____/  \___/  \___/  \__|
 * ----------------------------------------------------------
 * Amboot(R) Ambarella(R) Copyright (C) 2004-2024
 * Version: 3.9 - 2021年07月16日 14:18:03 - 9e0b644a
 * Boot From: SPINAND 2048.128 RC 8K-Boot
 * SYS_CONFIG: 0x8013401e, POC: 111
 * Cortex freq: 1608000000
 * iDSP freq: 46400000
 * Dram freq: 2016000000
 * Core freq: 960000000
 * AHB freq: 480000000
 * APB freq: 240000000
 * amboot>
 * @endcode
 *
 *    If the readout above appears on the console, the platform has successfully entered USB download mode.
 *    If the development platform does not respond, or fails to enter the AMBoot shell, proceed to step 6.
 *
 * 5. Commands to be typed in the AMBoot shell are indicated by the AMBoot prompt.
 *   Type "fastboot" or "fa" to enter USB download mode for fastboot tools.
 * @code {.c}
 * amboot> fa
 *
 *      _____   ___    _____________________                _
 *     |  ___| / _ \  /  __ \|__   __|| ___ \              | |
 *     | |___ / /_\ \ \ (  )/   | |   | |_/ /  ___    ___  | |_
 *     |  ___||  _  |   \ \     | |   | ___ \ / _ \  / _ \ | __|
 *     | |    | | | |/(__) /    | |   | |_/ /| (_) || (_) || |_
 *     |_|    \_| |_/\____/     |_|   \____/  \___/  \___/  \__|
 * ---------------------------------------------------------------
 * Fastboot(R) Ambarella(R) Copyright (C) 2004-2099
 * Enumerated HIGH speed ...
 * @endcode
 *
 *   Or, type "usbdl" or "u" to enter USB download mode for AmbaUSB.
 * @code {.c}
 * amboot> u
 * Start transferring using USB...
 * init_usb_dev done
 * init_usb_hardware done
 * entering usb_task
 * Start to send data 24 bytes...
 * Send completed!
 * entering usb_task
 * Start to send data 4096 bytes...
 * Send completed!
 * entering usb_task
 * @endcode
 *
 * 6. If the platform fails to enter USB download mode from the AMBoot shell, set the DIP switches as
 *    shown in the figures below. Then, power on the platform. The platform enters USB download mode
 *    using the USB Boot.
 * @image html getting_guide_dip_usb_cv5.png "Figure 7-2. DIP Switches in USB Boot Mode."
 *
 * 7. After the development platform enters USB download mode, the PC will recognize the USB device.
 *    The PC display will pop up a message to indicate that the platform is connected as a USB device.
 *
 * If the PC cannot recognize the platform, upgrade the Ambarella USB driver.
 *
 * On a Windows 7 PC, select <b>Device Manager > Universal Serial Bus controllers > Unknown device</b>. Update
 * the driver from this device. The Ambarella USB driver can be found in `$(Where AmbaUSB is installed)\Driver\`.
 *
 * @subsection sub_guide_firmware_fastboot_ubu 7.2 Fastboot Tool (for Ubuntu)
 *
 * AmbaUSB is the tool used to upgrade the platform on Ubuntu PC using a USB.
 * Locate the installation programs in `Tools/AmbaUSB`.
 *
 * Operating system (OS) requirement: Ubuntu 16.04 LTS / 18.04 LTS
 *
 * If this is the first time connecting the CV5 or CV72 EVK to Ubuntu, proceed with the following commands to set
 * up a basic burning environment:
 * @code {.c}
 * export amba_udev_file=/var/tmp/51-ambarella.rules
 * echo 'SUBSYSTEM=="usb", ATTR{idVendor}=="18d1|4255", MODE="0666",GROUP="plugdev"'> $amba_udev_file
 * chmod a+rx $amba_udev_file
 * sudo mv $amba_udev_file /etc/udev/rules.d/
 * sudo /etc/init.d/udev restart
 * @endcode
 *
 * Refer to the following steps to download new firmware if the EVK enters into download mode by setting DIP
 * switches. If the EVK enters into download mode by typing "fastboot" or "fa" in AMBoot, proceed to step 4.
 *
 * Open a new console and switch to the fastboot tool folder (in the folder `platform-tools_rxx.x.x-linux`).
 *
 *   1. Connect the board to the PC using a USB cable and ensure that the board enters into USB download mode.
 *
 *   2. Ensure that the USB can successfully identify the USB device with "4255:0018".
 * @code {.c}
 * build $ lsusb
 * Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
 * Bus 001 Device 003: ID 046d:c52b Logitech, Inc. Unifying Receiver
 * Bus 001 Device 045: ID 4255:0018 GoPro
 * Bus 001 Device 014: ID 1a86:7523 QinHeng Electronics HL-340 USB-Serial adapter
 * Bus 001 Device 013: ID 0424:2422 Standard Microsystems Corp.
 * Bus 001 Device 002: ID 413c:2107 Dell Computer Corp.
 * Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
 * @endcode
 *
 *   3. Execute pack_image_usb to bring up fastboot.
 * @code {.c}
 * pack_image_usb -f  <prebuild binary>
 *
 * example:
 * pack_image_usb -f  ambust_lpddr5_signed.bin
 * @endcode
 *
 *   4.	Once the EVK enters fastboot, "18d1:4ee0" is the critical word to find the
 *      correct device recognized by Ubuntu.
 * @code {.c}
 * build $ lsusb
 * Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
 * Bus 001 Device 003: ID 046d:c52b Logitech, Inc. Unifying Receiver
 * Bus 001 Device 047: ID 18d1:4ee0 Google Inc.
 * Bus 001 Device 014: ID 1a86:7523 QinHeng Electronics HL-340 USB-Serial adapter
 * Bus 001 Device 013: ID 0424:2422 Standard Microsystems Corp.
 * Bus 001 Device 002: ID 413c:2107 Dell Computer Corp.
 * Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
 * @endcode
 *
 *   5.	Execute fastboot to download the binary firmware.
 * @code {.c}
 * fastboot boot <path to binary firmare> --base 0x4000000
 *
 * Example:
 * fastboot boot bst_bld_atf_kernel_lnx_release.bin --base 0x4000000
 * @endcode
 *
 *   6.	The serial console of the development platform indicates the upgrading progress.
 * @code {.c}
 * ------ Report ------
 * bst:    success
 * bld:    success
 * pri:    success
 * lnx:    success.
 * @endcode
 *
 * @subsection sub_guide_firmware_fastboot_win 7.3 Fastboot Tool (for Windows)
 * The fastboot tool (`platform-tools_rxx.x.x-windows`) is used to upgrade the platform on a PC via USB.
 *
 * OS requirement: 32-bit or 64-bit Windows 7 or above
 *
 * Refer to the following steps to download the new firmware if the EVK enters download mode by setting DIP
 * switches. If the EVK enters into download mode by typing "fastboot" or "fa" in AMBoot, proceed to step 4.
 *
 * Open a new console and switch to the fastboot tool folder (found in the folder `platform-tools_rxx.x.x-windows`).
 *
 *   1.	Connect the board to the PC using a USB cable and ensure that the board enters into USB download mode.
 *
 *   2. Ensure that the driver has been updated by checking the driver version.
 * @image html getting_guide_cv5_usb_driver.png "Figure 7-3. AmbaUSB Driver."
 *
 *   3. Execute `pack_image_usb.exe` to initiate fastboot.
 * @code {.c}
 * pack_image_usb.exe -f  <prebuild binary>
 *
 * example:
 * pack_image_usb.exe -f  ambust_lpddr5_signed.bin
 * @endcode
 *
 *   4. Once the EVK enters fastboot, the word "Android" is required to ensure that the correct device is recognized by the PC.
 * @image html getting_guide_cv5_fastboot_and.png "Figure 7-4. Fastboot Android Device."
 *
 *   5.	Execute `fastboot.exe` to download the binary firmware.
 * @code {.c}
 * fastboot.exe boot <path to binary firmware> --base 0x4000000
 *
 * Example:
 * fastboot.exe boot bst_bld_atf_kernel_lnx_release.bin --base 0x4000000
 * @endcode
 *
 *   6. The serial console of the development platform indicates the upgrading progress.
 * @code {.c}
 * ------ Report ------
 * bst:    success
 * bld:    success
 * pri:    success
 * lnx:    success.
 * @endcode
 *
 * @subsection sub_guide_firmware_ambausb_ubu 7.4 AmbaUSB (for Ubuntu)
 *
 * AmbaUSB is the tool used to upgrade the platform on Ubuntu PC using the USB.
 * Locate the installation programs in `Tools/AmbaUSB`.
 *
 * OS Requirement: Ubuntu 16.04 LTS / 18.04 LTS
 *
 * Select the appropriate installation program, then double-click to install it.
 *
 * 1. Connect the board to the PC using a USB cable.
 *
 * 2. Before burning the firmware to the platform, ensure that the platform has entered USB download
 *    mode as described in Section @ref sub_guide_firmware_down.
 * @image html getting_guide_assign_virture.png "Figure 7-5. Assign the Ambarella USB Device to the Virtual Machine."
 *
 * 3. Before using AmbaUSB in the Linux virtual machine, assign the
 *    Ambarella USB device to the virtual machine.
 *
 * 4. Launch AmbaUSB. Select the proper chip model for the boards's filter and flash configuration,
 *    according to the table below. AmbaUSB will recognize the connected board automatically if all
 *    options are consistent with the board connected to the host in the figure below.
 *
 *   <table>
 *   <caption id="getting_guide_board_config"></caption>
 *   <tr><th> Core Board            <th> Titanium         <th> Manganese        <th> Cr                      <th> Co
 *   <tr><td> Chip                  <td> CV5              <td> CV5              <td> CV52                    <td> CV52
 *   <tr><td> Board configuration   <td> CV5.LPDDR5.NAND  <td> CV5.LPDDR4.NAND  <td> CV52_DDRC1.LPDDR5.NAND  <td> CV52_DDRC1.LPDDR4.NAND
 *   </table>
 *
 * 5. Click the <b>Find</b> button beside the firmware to browse the images that will be flashed to the board.
 * @image html getting_guide_download_firmware_CV5.png "Figure 7-6. Downloading the Firmware."
 *
 * 6. Click the button with the blue arrow icon on the right to start downloading the firmware.
 *
 * 7. The serial console of the development platform will indicate the upgrading process. When the image is
 *    downloaded, the message "Program Terminated" appears on the serial console. Refer to the code below.:
 * @code {.c}
 * ------ Report ------
 * bst:    success
 * bld:    success
 * hal:    success
 * pri:    success
 * lnx:    success
 * - Program Terminated -
 * @endcode
 *
 * 8. The firmware will reboot automatically and load after it is downloaded with the DIP settings in NAND
 *    boot mode. If it fails to flash the firmware into the board from the AMBoot shell, enter
 *    USB boot mode as described in the previous section and try again.
 *
 * 9. If the DIP switches have been set to USB boot mode (see the previous section), set the DIP
 *    switches to NAND boot mode in Figure @ref sub_guide_firmware_down. and reboot.
 *
 * @subsection sub_guide_firmware_ambausb_win 7.5 AmbaUSB (for Windows)
 *
 * AmbaUSB is used to upgrade the platform on a PC via USB. The installation programs,
 * located in `Tools/AmbaUSB`, include 32-bit and 64-bit PC versions of AmbaUSB.
 *
 * OS Requirement: 32-bit or 64-bit Windows 7
 *
 * Choose the correct OS and double-click the installation program to install.
 *
 * 1. Connect the board and PC using a USB cable. Verify that the board can enter USB download mode.
 *
 * 2. Ensure that the driver has been updated. Check the driver version, as shown in the following figure.
 *    Select the proper chip model for the boards's filter and the proper flash configuration according to
 *    the table @ref getting_guide_board_config "Board Configuration". AmbaUSB will recognize the board
 *    automatically if the options are consistent with the board connected to the host, as shown in the figure below.
 * @image html getting_guide_ambausb_driver.png "Figure 7-7. AmbaUSB Driver."
 *
 * 3. Locate the firmware and click on the blue download icon to start the download. See the following figure.
 * @image html getting_guide_auto_detection_CV5.png "Figure 7-8. Auto-detection of the CV5 Timn Board."
 * @image html getting_guide_auto_detection_CV52.png "Figure 7-9. Auto-detection of the CV52 CR / CO Board."
 * @image html getting_guide_auto_detection_CV72.png "Figure 7-10. Auto-detection of the CV72 GA / GE Board."
 *
 *    <b>Notes for CV52 boards:</b> <br>
 *       - Select <b>CV5</b> for the board in the middle right.<br>
 *       - Select <b>LINUX.CV52_DDRC1.LPDDR4.NAND.540MHz</b> for the CV52 CO board, and select
 *         <b>LINUX.CV52_DDRC1.LPDDR5.NAND.540MHz</b> for the CV52 CR board.
 *
 * 4. The serial console of the development platform will indicate the upgrading process. When the download
 *    is complete, the message "Program Terminated" will be displayed on the serial console:
 * @code {.c}
 * ------ Report ------
 * bst:    success
 * bld:    success
 * hal:    success
 * pri:    success
 * lnx:    success.
 * - Program Terminated -
 * @endcode
 *
 * - - - -
 *
 * @section getting_guide_document 8. SDK Documents on Webpages
 *
 * Ambarella uses Doxygen, a tool for writing software documentation, to generate SDK documents from the
 * source code, ensuring their alignment with rapid code development. The SDK documents appear on webpages.
 * Currently, Ambarella uses Doxygen to create webpages for the following:
 *
 * <table>
 * <caption id="getting_guide_amba_dox_pag">Table 8-1. Ambarella Doxygen Webpages.</caption>
 * <tr><th> Catalog                           <th> Content
 * <tr><td rowspan="7"> Ambarella Linux SDK   <td> System Overview
 * <tr>                                       <td> Document Reading Guide
 * <tr>                                       <td> Market Segments
 * <tr>                                       <td> Getting Start Guide
 * <tr>                                       <td> SDK Deliverables
 * <tr>                                       <td> SDK Code Building
 * <tr>                                       <td> Glossary and Abbreviations
 * <tr><td rowspan="4"> Hardware              <td> Hardware (HW) Modules
 * <tr>                                       <td> Board - CV5 Titanium
 * <tr>                                       <td> Board - CV52 Co / Cr
 * <tr>                                       <td> Board - CV72 Ga / Ge
 * <tr><td rowspan="3"> Build System          <td> Building System Introduction and Guidance
 * <tr>                                       <td> Yocto Recipe
 * <tr>                                       <td> Yocto FAQ
 * <tr><td rowspan="5"> Driver                <td> Cavalry Driver Application Programming Interface (API)
 * <tr>                                       <td> Continuous Memory Allocator (CMA) Driver API
 * <tr>                                       <td> IAV Driver API
 * <tr>                                       <td> Sensor Parameters and Tuning Table
 * <tr>                                       <td> Sensor and SERDES Driver Installation
 * <tr><td rowspan="18"> Library              <td> Advanced Software Framework (ASF) Library API
 * <tr>                                       <td> Cavalry_Mem Library API
 * <tr>                                       <td> Amba GStreamer Plugins
 * <tr>                                       <td> Cavalry Opt Layers Library API
 * <tr>                                       <td> CGPP Library API
 * <tr>                                       <td> Data Process Library API
 * <tr>                                       <td> EazyAI Library API
 * <tr>                                       <td> Electronic Image Stabilization (EIS) Library API
 * <tr>                                       <td> FAST_IO Library API
 * <tr>                                       <td> Image Library API
 * <tr>                                       <td> Image Flow Library API
 * <tr>                                       <td> Neural Network Control (NNCtrl) Library API
 * <tr>                                       <td> NNStreamer Library API
 * <tr>                                       <td> Sensor Calibration Library API
 * <tr>                                       <td> SmartFB Library API
 * <tr>                                       <td> Smart Rate Control (SmartRC) V3 Library API
 * <tr>                                       <td> Stitch Library API
 * <tr>                                       <td> VPROC Library API
 * <tr><td rowspan="29"> Video                <td> BASIC - Video Input
 * <tr>                                       <td> BASIC - Video Output
 * <tr>                                       <td> BASIC - RAW
 * <tr>                                       <td> BASIC - Channel
 * <tr>                                       <td> BASIC - Source Buffer
 * <tr>                                       <td> BASIC - Pyramid
 * <tr>                                       <td> BASIC - Canvas
 * <tr>                                       <td> BASIC - Stream
 * <tr>                                       <td> BASIC - H.264 / H.265 Codec
 * <tr>                                       <td> BASIC - Group of Pictures (GOP)
 * <tr>                                       <td> BASIC - On the Fly Settings
 * <tr>                                       <td> BASIC - Privacy Mask
 * <tr>                                       <td> BASIC - Blur on Streams
 * <tr>                                       <td> BASIC - Overlay on Streams
 * <tr>                                       <td> BASIC - Data Dumping
 * <tr>                                       <td> BASIC - Frame Rate
 * <tr>                                       <td> BASIC - High Dynamic Range (HDR)
 * <tr>                                       <td> ADVANCED - Encode Mode
 * <tr>                                       <td> ADVANCED - Configure with Lua Script
 * <tr>                                       <td> ADVANCED - Lens Distortion Correction (LDC)
 * <tr>                                       <td> ADVANCED - Vsync Loss
 * <tr>                                       <td> ADVANCED - Arbitrary Image Scaler
 * <tr>                                       <td> ADVANCED - Encode from Memory
 * <tr>                                       <td> ADVANCED - Encode from RAW
 * <tr>                                       <td> ADVANCED - Pipeline Latency
 * <tr>                                       <td> ADVANCED - Poll Interface
 * <tr>                                       <td> ADVANCED - Bypass IDSP for YUV input
 * <tr>                                       <td> OTHER - Debug Option
 * <tr>                                       <td> OTHER - Miscellaneous
 * <tr>                                       <td> OTHER - Dynamic Random-Access Memory (DRAM) Bandwidth Statistics
 * <tr><td> Security                          <td> Overview
 * <tr><td rowspan="11"> System               <td> Migration Guide from CV2x
 * <tr>                                       <td> Boot and Upgrade
 * <tr>                                       <td> DRAM Optimization
 * <tr>                                       <td> Hardware Presentation Time Stamp (PTS)
 * <tr>                                       <td> Power Management
 * <tr>                                       <td> Sensor Calibration User Guide
 * <tr>                                       <td> Multi-VIN Design
 * <tr>                                       <td> AMBoot Documents
 * <tr>                                       <td> AMBA System Document
 * <tr>                                       <td> PDF Documents
 * <tr>                                       <td> Kernel Documents
 * <tr><td rowspan="15"> Peripherals          <td> Audio
 * <tr>                                       <td> File System
 * <tr>                                       <td> NAND
 * <tr>                                       <td> eMMC
 * <tr>                                       <td> Debugfs
 * <tr>                                       <td> USB
 * <tr>                                       <td> SD Card
 * <tr>                                       <td> WiFi
 * <tr>                                       <td> Bluetooth
 * <tr>                                       <td> SPI
 * <tr>                                       <td> I2C
 * <tr>                                       <td> Peripheral Component Interconnect Express (PCIe) Express
 * <tr>                                       <td> Ethernet
 * <tr>                                       <td> Misellaneous
 * <tr>                                       <td> Joint Test Action Group (JTAG)
 * <tr><td rowspan="2"> Applications          <td> Ambarella Applications Document
 * <tr>                                       <td> Access Control Camera
 * </table>
 *
 * @note
 * Future SDK versions will include additional webpages.
 * Users can visit http://doxygen.nl/ for more information about the Doxygen software.
 *
 * This chapter includes the following sections:
 *
 *   - Section @ref sub_guide_document_sdk_cv5
 *   - Section @ref sub_guide_document_cnngen_cv5
 *
 * @subsection sub_guide_document_sdk_cv5 8.1 Generating the SDK Document Website
 *
 * To view the document webpages:
 *
 * 1. Go to http://www.doxygen.nl/download.html, download a suitable binary, and install the Doxygen
 *    software. Ensure that the software is functioning correctly.
 *
 * 2. In the build PC, go to the CNNGen samples package build folder.
 * @code {.c}
 * build $ cd ambarella/
 * build $ export TOOLCHAIN_PATH=1
 * build $ cd boards/cv5_timn
 * build $ make ipcam_config
 * build $ make sdk_doc
 * @endcode
 *
 * 3. Webpages are located in `ambarella/out/doc_out/cv5x_doc/doc/overview/`. Use the browser
 *    to open the `index.html` and display the webpage as shown below:
 * @image html getting_guide_document_web_cv5.png "Figure 8-1. Generated Document Webpages."
 *
 *
 * @subsection sub_guide_document_cnngen_cv5 8.2 Generated CNNGen Document Website
 *
 * Follow the steps below to find the document website:
 * 1. Download the `cvflow_cnngen_samples_<version>_<date>.tar.xz` from PRO system.
 *
 * 2. Find `cvflow_cnngen_documents_<version>_<date>.tar.bz2` in above package.
 * @code {.c}
 * build $ tar xvfp cvflow_cnngen_documents_<version>_<date>.tar.bz2
 * @endcode
 *
 * 3. And open `feature_sets/index.html` with browser. Then, the document is displayed, as in the example below.
 * @image html getting_guide_cnngen_document_web.png "Figure 8-2. Generated CNNGen Document Websites."
 *
 *
 * - - - -
 *
 * @section getting_guide_cpu 9. CPU Performance Benchmarks
 *
 * @subsection sub_guide_cpu_dmips 9.1 Dhrystone to Check CPU DMIPS
 *
 * Dhrystone is a synthetic computing benchmark program developed in 1984 by Reinhold P.
 * Weicker, intended to be representative of system (integer) programming. Dhrystone
 * grew to become representative of general processor (CPU) performance.
 *
 * The Dhrystone benchmark contains no floating point operations; thus the name is a pun
 * on the then-popular Whetstone benchmark for floating point operations. The output
 * from the benchmark is the number of Dhrystones per second (the number of iterations
 * of the main code loop per second). Both Whetstone and Dhrystone are synthetic benchmarks,
 * meaning that they are simple programs that are carefully designed to statistically mimic
 * the processor usage of some common sets of programs.
 *
 * Dhrystone may represent a result more meaningfully than millions of instructions
 * per second (MIPS). A common representation of the Dhrystone benchmark is the DMIPS
 * (Dhrystone MIPS) obtained when the Dhrystone score is divided by 1757 (the number of
 * Dhrystones per second obtained on the VAX 11/780, nominally a 1-MIPS machine).
 *
 * Dhrystone's open source code has been introduced into the Ambarella SDKs. It is located in the
 * `ambarella/unit_test/linux/benchmark/dhrystone` folder. Users can enable the Dhrystone
 * compile when building the firmware.
 *
 * @code {.c}
 * build $ make menuconfig
 *    unit_test --->
 *        linux --->
 *             benchmark --->
 *                [*] test-dhrystone (unit_test/linux/benchmark/dhrystone)
 * @endcode
 *
 * Use the following command to perform the test.
 * @code {.c}
 * board # find / -name dhrystone
 * /usr/local/bin/dhrystone
 * board # dhrystone
 * Dhrystone BenchMark, Version 2.1(Language:C)
 * ===================/proc/cpuinfo==============
 * .
 * .
 * .
 * Total DMIPS:26569.30
 * @endcode
 *
 * @subsection sub_guide_cpu_coremark 9.2 Coremark-pro to Check CPU Performance
 *
 * CoreMark®-PRO is a comprehensive, advanced processor benchmark that functions with
 * and enhances the market-proven industry-standard EEMBC CoreMark® benchmark.
 * While CoreMark stresses the CPU pipeline, CoreMark-PRO tests the entire processor,
 * adding comprehensive support for multicore technology,
 * a combination of integer and floating-point workloads,
 * and data sets for utilizing larger memory subsystems.
 * Together, EEMBC CoreMark and CoreMark-PRO provide a standard benchmark
 * covering the spectrum from low-end microcontrollers to high-performance computing processors.
 *
 * The EEMBC CoreMark-PRO benchmark contains five prevalent integer workloads
 * and four popular floating-point workloads.
 *
 * The integer workloads include:
 *  - JPEG compression
 *  - ZIP compression
 *  - XML parsing
 *  - SHA-256 Secure Hash Algorithm
 *  - A more memory-intensive version of the original CoreMark
 *
 * The floating-point workloads include:
 *  - Radix-2 Fast Fourier Transform (FFT)
 *  - Gaussian elimination with partial pivoting derived from LINPACK
 *  - A simple neural-net
 *  - A greatly improved version of the Livermore loops benchmark using the following 24 FORTRAN kernels
 *
 * CoreMark-PRO's open source code has been introduced into the Ambarella SDKs.
 * It is located in the `ambarella/unit_test/linux/benchmark/coremark-pro` folder.
 * Users can enable the CoreMark-PRO compile when building the firmware.
 *
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *    unit_test --->
 *        linux --->
 *             benchmark --->
 *                [*] coremark-pro (unit_test/linux/benchmark/coremark-pro)
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build $ make menuconfig
 *    meta-ambaapp --->
 *        recipes-linuxtest --->
 *            [*] coremark-pro (meta-ambaapp/recipes-linuxtest/coremark-pro)
 * @endcode
 *
 * Use the following command to execute the test, where 6 represents the number of runs, and the default is 1.
 * @code {.c}
 * board # /usr/local/bin/coremark.sh 6
 *
 * WORKLOAD RESULTS TABLE
 *
 *                                                  MultiCore SingleCore
 * Workload Name                                     (iter/s)   (iter/s)    Scaling
 * -----------------------------------------------------
 * cjpeg-rose7-preset                                181.8180    91.7431     1.9818
 * core                                                1.6308     0.8167     1.9969
 * linear_alg-mid-100x100-sp                         188.6790    94.3396     2.0000
 * loops-all-mid-10k-sp                                3.7327     3.5273     1.0582
 * nnet_test                                          11.1359     5.5586     2.0033
 * parser-125k                                        26.7380    14.0647     1.9011
 * radix2-big-64k                                    357.1430   294.1180     1.2143
 * sha-test                                          303.0300   151.5150     2.0000
 * zip-test                                          119.0480    66.2252     1.7976
 *
 * WORKLOAD RESULTS TABLE
 *
 * Mark Name                                        MultiCore SingleCore    Scaling
 * -----------------------------------------------------
 * CoreMark-PRO                                     5210.1118  3010.5315     1.7306
 * @endcode
 *
 * - - - -
 *
 * @section getting_guide_sd_card 10. SD Card
 *
 * The CV5x EVK board has two secure digital (SD) interfaces. The larger slot is used for the SD card, and the
 * smaller slot is used for the secure digital input output (SDIO) WiFi card. The two SD slots are
 * independent; they possess their own SD controllers. The SDIO controller does not support
 * the UHS-I mode. SD slot 0 can support booting with embedded multi-media controller
 * / card (eMMC), while SD slot 1 cannot.
 *
 * The maximum frequency of the SD controller is 150 MHz.
 *
 * This chapter includes the following sections:
 *
 *   - Section @ref sub_guide_sd_card_slot
 *   - Section @ref sub_guide_sd_card_type
 *   - Section @ref sub_guide_sd_card_pre
 *   - Section @ref sub_guide_sd_card_format
 *
 * @subsection sub_guide_sd_card_slot 10.1 SD Slot
 *
 * The following figure shows the bottom of the CV5 Timn board. The SD card
 * is visible in the top slot.
 * @image html getting_guide_sd_slots_cv5.png "Figure 10-1. SD Slots."
 *
 * The default value of fixed_cd is -1. -1: Auto detect, 0: No detection, 1: Force detect once.
 *
 * 1. Turn off the slot if it is not in use. Too many unused SD interrupts can lead to a
 * heavy system load, impacting network performance.
 * @code {.c}
 * board # mount -t debugfs debugfs /debug
 * board # echo 0 > /debug/mmc0/ambhost/fixed_cd
 * @endcode
 *
 * 2. To trigger the CD to scan the SD bus manually, modify the value of fixed_cd.
 * @code {.c}
 * board # echo 1 > /debug/mmc0/ambhost/fixed_cd
 * @endcode
 *
 * For the CV5 Timn board, the "mmc0" must be
 * modified to "mmc1"(to TF card) or "mmc2"(to SD card).
 *
 * @subsection sub_guide_sd_card_type 10.2 SD Card Type
 *
 * SD is a non-volatile memory card format developed by the SD Card Association for use in
 * portable devices. See https://www.sdcard.org/home/ for further details. Users can also
 * refer to http://en.wikipedia.org/wiki/SD_card for SD card standards.
 * @image html getting_guide_sd_various.png "Figure 10-2. SD / SDHC / SDXC / MMC Cards from Various Vendors."
 * @image html getting_guide_pins_sd.png "Figure 10-3. Pins on an SD Card."
 *
 * If the application requires continuous data storage, Ambarella recommends using high
 * speed / high quality SD cards. High speed / high quality SD cards write data in less
 * time and require less CPU for I/O.
 *
 * The following sections provide information about SD card format, speed, and design notes.
 * Ambarella does not recommend normal-speed SD cards, low-speed SD cards, low-speed
 * multi-media cards (MMC), or small-capacity SD cards for typical internet protocol
 * camera (IPCAM) system designs, or car DV designs. As an alternative, Ambarella recommends using
 * the secure digital high capacity (SDHC) class 4 or above for continuous data writing applications.
 *
 * If applications require long-time, continuous data writing, Ambarella recommends using
 * SDHC class 4 or above for typical IPCAM or car DV products.
 *
 * Although various SD cards may be usable with CV5x / CV7x, only the SD cards in the
 * following list are verified on the CV5x / CV7x EVK board.
 *
 * <table>
 * <caption id="gsg_verified_sd">Table 10-1. Verified SD Card.</caption>
 * <tr><th> Brand                  <th> Class     <th> Capacity       <th> Type
 * <tr><td rowspan="5"> Kingston   <td> Normal    <td> 2 GB           <td> MicroSD card
 * <tr>                            <td> Class 4   <td> 4 GB           <td> MicroSD card
 * <tr>                            <td>           <td> 2 GB           <td> SD card
 * <tr>                            <td>           <td> 4 GB           <td> SD card
 * <tr>                            <td> Class 4   <td> 4 GB           <td> SDHC card
 * <tr><td rowspan="2"> Kingmax    <td> Normal    <td> 2 GB           <td> MicroSD card
 * <tr>                            <td> Class 6   <td> 4 GB           <td> Micro-SDHC card
 * <tr><td rowspan="5"> SanDisk    <td> Class 2   <td> 4 GB           <td> MicroSD card
 * <tr>                            <td> Class 4   <td> 4 GB           <td> MicroSD card
 * <tr>                            <td> Normal    <td> 512 MB         <td> SD card
 * <tr>                            <td> Class 2   <td> 4 GB           <td> SDHC card
 * <tr>                            <td> Class 4   <td> 4 GB           <td> SDHC card
 * <tr><td rowspan="2"> Toshiba    <td> Class 4   <td> 4 GB           <td> MicroSD card
 * <tr>                            <td> Class 10  <td> 16 GB          <td> SDHC card
 * <tr><td rowspan="2"> Apacer     <td>           <td> 2 GB           <td> MicroSD card
 * <tr>                            <td> Class 4   <td> 4 GB           <td> MicroSD card
 * <tr><td rowspan="2"> PNY        <td>           <td> 2 GB           <td> MicroSD card
 * <tr>                            <td> Class 4   <td> 4 GB           <td> MicroSD card
 * <tr><td> PQI                    <td>           <td> 2 GB           <td> MicroSD card
 * <tr><td> Esuninfo               <td>           <td> 2 GB           <td> MicroSD card
 * <tr><td> Verbatim               <td>           <td> 2 GB           <td> MicroSD card
 * <tr><td> SONY                   <td> Class 4   <td> 32 GB          <td> MicroSD card
 * <tr><td> Lenovo                 <td>           <td> 1 GB           <td> SD card
 * <tr><td> Adata                  <td>           <td> 256 MB         <td> SD card
 * <tr><td rowspan="2"> Transcend  <td> Class 10  <td> 8 GB           <td> SDHC card
 * <tr>                            <td> Class 10  <td> 32 GB          <td> SDHC card
 * </table>
 *
 * @subsection sub_guide_sd_card_pre 10.3 Hardware and Software Preparation
 *
 * @subsubsection dsub_guide_sd_card_pre_cv2 10.3.1 CV5 Timn EVK
 *
 * For CV5 Timn EVK, the pin function of the SD card and the TransFlash (TF) card are multiplexed with I2C / VSYNC / SPI bus.
 * With the default settings, the I2C / VSYNC / SPI bus are enabled. Follow the steps below to
 * enable the SD card or TF card function:
 *
 * - SD card
 *
 * 1. Enable SDIO0 before building the firmware.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  [*] bootmenu@virtual (boot)  --->
 *    [*]   boot (boot)  --->
 *      Bootloader  --->
 *         Ambarella Firmware Configuration  --->
 *            SDIO0 and I2C1/VSYNC Selection (SDIO0)  --->
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build $ make menuconfig
 *   meta-ambabsp --->
 *      recipes-bsp --->
 *          boot (meta-ambabsp/recipes-bsp/boot) --->
 *            Bootloader --->
 *               Ambarella Firmware Configuration  --->
 *                  SDIO0 and I2C1/VSYNC Selection (SDIO0)  --->
 * @endcode
 *
 * 2. Modify the hardware power-on configuration (POC) and jumpers:<br>
 * Set SW2_1, SW2_2, SW2_3 off (SW2 is close to the senor slots);<br>
 * Switch the jumper from J18 to J16.
 *
 * - TF card
 *
 * 1. Enable SDIO1 before building the firmware.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *  [*] bootmenu@virtual (boot)  --->
 *    [*]   boot (boot)  --->
 *      Bootloader  --->
 *         Ambarella Firmware Configuration  --->
 *            SDIO1 and SPI3/I2C5 Selection (SDIO1)  --->
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build $ make menuconfig
 *   meta-ambabsp --->
 *      recipes-bsp --->
 *          boot (meta-ambabsp/recipes-bsp/boot) --->
 *            Bootloader --->
 *               Ambarella Firmware Configuration  --->
 *                  SDIO1 and SPI3/I2C5 Selection (SDIO1)  --->
 * @endcode
 *
 * 2. Modify hardware POC and Jumpers:<br>
 * Set SW2_1, SW2_2, SW2_4 off;<br>
 * Switch the jumper from J24 to J22.
 *
 * @subsection sub_guide_sd_card_format 10.4 Format and Mount
 *
 * @subsubsection dsub_guide_sd_card_format_enable 10.4.1 Enable FAT32 / exFAT for Windows OS or EXT4 for Linux OS
 *
 * Although the Cooper SDK has an integrated common file system, users must open
 * the corresponding configuration when building the firmware.
 *
 *  - exFAT
 * @code {.c}
 * build $ make menuconfig
 *     prebuild  --->
 *           oss  --->
 *       Filesystem Tools >
 *         [*] prebuild-fuse-exfat (prebuild/oss/armv8-a/fuse-exfat)
 * @endcode
 *  - EXT4
 * @code {.c}
 * build $ make menuconfig_public_linux
 * File systems >
 *    <*>The Extended 4 (ext4) filesystem >
 *    [*] Use ext4 for ext2 file systems >
 *    [*] Ext4 POSIX Access Control Lists >
 *    [*] Ext4 Security Labels >
 * @endcode
 *
 * @subsubsection dsub_guide_sd_card_format_mount 10.4.2 Mount an SD Card
 *
 * The CV5x / CV7x board recognizes the SD card after the card is inserted into the SD card
 * slot, and it is automatically mounted to `/sdcard/***`. Enter "mount" on the CV5x / CV7x
 * board to see the mounting information.
 *
 * @code {.c}
 * board # mount
 * /dev/mmcblk1p1 on /sdcard/mmcblk1p1 type vfat
 * (rw,noatime,nodiratime,gid=100,fmask=0022,dmask=0000,allow_utime=0022,
 * codepage=437,iocharset=iso8859-1,shortname=mixed,utf8,flush,errors=remount-ro)
 * @endcode
 *
 * @subsubsection dsub_guide_sd_card_format_unmount 10.4.3 Unmount an SD Card
 *
 * Before removing the SD card, close all files, and then unmount the SD card (see the following).
 * @code {.c}
 * board # cd /
 * board # umount /dev/mmcblk1p1
 * @endcode
 *
 * If the message "Device or resource busy" appears, ensure that all files on the SD card are
 * closed and `/mnt/sdcard` is not being accessed (type "cd /" to go to the root directory).
 *
 * @subsubsection dsub_guide_sd_card_format_format 10.4.4 Format an SD Card
 *
 * 1. Format an SD card.<br>
 * Although the SD card may come pre-formatted, Ambarella recommends formatting the
 * card manually to avoid potential errors and to maximize the performance.
 *
 *   The SD card can be formatted to FAT32, NTFS, ext3, and other file systems. For
 *   SD cards equal to or less than 32 GB, Ambarella recommends FAT32.  For SD cards
 *   greater than 32 GB, NTFS is preferred, as Windows limits FAT32 partitions to 32 GB.
 *
 *   Windows 7 also supports exFAT, but exFAT is not formally supported by the Linux kernel.
 *   Ext3 is supported by Linux to support big SDHC (or SDXC) cards, but Windows does
 *   not recognize ext3.
 *
 *   There are three main options to format the SD cards to the required format. To successfully
 *   format an SD card, the write protection lock on the side of the card must be in the
 *   "unlock" position. SD mini and micro SD cards must be used with an adapter or specialized
 *   USB card reader when a computer is formatting them.
 *
 * 2. Use a format utility.<br>
 *   Most computer systems include generic formatting utilities for nearly every format of
 *   writable media. For example, in Windows OS, users can access the format option by
 *   right-clicking an "SD card" driver in the "My Computer" folder. Use the default
 *   settings to format the SD card.
 *
 *   The SD Association SD Formatter is the recommended option for the Windows OS platform.
 *   The SD Formatter is recommended because the generic format utilities are not designed
 *   to format the SD cards to their official SD memory format requirements that enable them
 *   to run on devices at their optimum performance. The SD formatter offered by the SD
 *   Association is free and can be found at SDcard.org:
 *   https://www.sdcard.org/downloads/formatter_3/.
 *
 * 3. The tool mkdosfs is included in the Cooper Linux SDK.<br>
 *   The tool mkdosfs can format an SD card to the FAT32 format. It is used to create
 *   a disk operating system (DOS) file system under Linux.
 * @code {.c}
 * board # umount /dev/mmcblk1p1 (Unmount the SD card first)
 * board # mkdosfs -v -n LOCAL /dev/mmcblk1p1
 * board # mount /dev/mmcblk1p1 /tmp/mmcblk1p1
 * @endcode
 *
 *   If users intend to use an SD card as common data storage, they must format the card in
 *   their products (under Linux) using mkdosfs to ensure the optimal performance.  An
 *   SD card formatted by a different tool on Windows can potentially result in lower performance.
 *
 * 4. Check file system integrity.<br>
 *   The tool fsck is used to check and repair the MS-DOS file system.
 * @code {.c}
 * board # fsck /dev/mmcblk1p1
 * @endcode
 *
 *   @note
 *   If the SD card is removed before unmounting, users must check the integrity of the file
 *   system again before using the card. Removing the SD card before unmounting can cause
 *   inconsistent data storage and reduce the integrity of the file system. To avoid this
 *   potential issue, good product design should include unmounting the SD card before removing.
 *   Alternatively, it should call the power-off command to enable the system to close all
 *   open files and flush the data to synchronize, and then unmount.
 *
 * 5. Partition an SD card.<br>
 *   Occasionally, users must partition the SD card.  For example, if a user must format a
 *   64-GB secure digital extended capacity (SDXC) card to the FAT32 file system, note the
 *   following: because Windows limits FAT32 to 32 GB, multiple partitions are required.
 *   However, only the first partition can be seen on Windows, while Linux can display all partitions.
 *
 *   Gparted is a software utility which scans a storage device. It examines the data in
 *   order to detect partitions which may exist, but are absent from the disk's partition
 *   tables. For more details, go to http://gparted.sourceforge.net/.
 *
 *   @note
 *   If users must access all partitions in Windows, Ambarella does not recommend using the
 *   Linux tool to partition. As an alternative, users can attempt to port exFAT to Linux or use NTFS
 *   on the SD card to support large partitions that can be recognized on Windows.
 *
 * - - - -
 *
 * @section getting_guide_license 11. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
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
 * - - - -
 *
 */

/*!
 * @file doc_ov_deliverables.h
 * @brief
 * @version 1.0
 * @date 2022-08-12
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
 * @page ov_deliverables SDK Deliverables
 *
 * @section ov_softewares_drv_lib 1. Linux Drivers and Libraries
 *
 * @subsection ov_private_drv 1.1 Private Linux Drivers
 * <table>
 * <caption id="Private_Drivers">Table 1-1. Private Drivers.</caption>
 * <tr><th>Module / Package                               <th>Note
 * <tr><td>Image audio video (IAV) driver                 <td>Calls coder / decoder (codec) functions. GPLv2 Linux modules
 * <tr><td>Cavalry driver                                 <td>Calls vector processor (VP) functions. GPLv2 Linux modules
 * <tr><td>Digital signal processor (DSP), video input (VIN), and video output (VOUT) drivers   <td>GPLv2 Linux modules
 * <tr><td>Sensor driver                                  <td>GPLv2 Linux modules
 * <tr><td>Image processing driver                        <td>GPLv2 Linux modules
 * </table>
 *
 * @subsection ov_plat_drv 1.2 Peripheral Linux Drivers
 * <table>
 * <caption id="Peripheral_Drivers">Table 1-2. Peripheral Drivers.</caption>
 * <tr><th>Module / Package                               <th>Note
 * <tr><td>GPIO driver                                    <td>GPLv2 Linux modules
 * <tr><td>I2C driver                                     <td>GPLv2 Linux modules
 * <tr><td>GMDA driver                                    <td>GPLv2 Linux modules
 * <tr><td>SPI driver                                     <td>GPLv2 Linux modules
 * <tr><td>RNG driver                                     <td>GPLv2 Linux modules
 * <tr><td>WDT driver                                     <td>GPLv2 Linux modules
 * <tr><td>SPINAND driver                                 <td>GPLv2 Linux modules
 * <tr><td>SPINOR driver                                  <td>GPLv2 Linux modules
 * <tr><td>SDIO driver                                    <td>GPLv2 Linux modules
 * <tr><td>EMMC driver                                    <td>GPLv2 Linux modules
 * <tr><td>ETH driver                                     <td>GPLv2 Linux modules
 * <tr><td>USB driver                                     <td>GPLv2 Linux modules
 * <tr><td>PCIE driver                                    <td>GPLv2 Linux modules
 * <tr><td>UART driver                                    <td>GPLv2 Linux modules
 * </table>
 *
 * @subsection ov_private_lib 1.3 Private Libraries
 * <table>
 * <caption id="Private_Libraries">Table 1-3. Private Libraries.</caption>
 * <tr><th>Module / Package                               <th>Library File
 * <tr><td>Image processing (AE / AWB) library            <td>libimg_algo_v6.a / libimg_dsp_v6_hf.a
 * <tr><td>Image processing flow library                  <td>libimg_aaa_flow_v6.so
 * <tr><td>Multi-channel Lua parser library               <td>libmcl.so
 * <tr><td>Neural network (NN) flow control library       <td>libnnctrl.so
 * <tr><td>NN data processing library                     <td>libvproc.so
 * <tr><td>NN memory management library                   <td>libcavalry_mem.so
 * <tr><td>CNNGen pre-processing library                  <td>libcgpp.so
 * <tr><td>Easy artificial intelligence (AI) library      <td>libeazyai.so
 * <tr><td>Smart video output (VOUT) framebuffer library  <td>libsmartfb.so
 * <tr><td>Lens distortion correction (LDC) library       <td>libdewarp.so
 * <tr><td>Electronic image stabilization (EIS) library   <td>libeis.so
 * <tr><td>Smart rate control (SRC) library               <td>libsmartrc_3_0.so
 * <tr><td>Text insertion library                         <td>libtextinsert.a
 * <tr><td>Arbitrary blur library                         <td>libblur.so
 * <tr><td>Audio codec library                            <td>ALSA,libasound.a
 * </table>
 *
 * - - - -
 *
 * @section ov_softewares_demo_test 2. Demo and Test Applications
 *
 * <table>
 * <caption id="Demo and Apps">Table 2-1. Applications.</caption>
 * <tr><th>Application                         <th>Description
 * <tr><td>dsplog_cap                          <td>Capture / parse the DSP log
 * <tr><td>test_encode, test_stream            <td>Test encode and streaming
 * <tr><td>test_dptz                           <td>Exercise digital pan / tilt / zoom (DPTZ)
 * <tr><td>test_privacymask                    <td>Exercise the privacy mask (PM) functionality
 * <tr><td>test_overlay, test_textinsert       <td>Exercise the overlay insert functionality
 * <tr><td>test_blur                           <td>Exercise the blur insert functionality
 * <tr><td>test_yuvcap                         <td>Capture RAW / YUV / ME1 / ME0 data
 * <tr><td>test_frame_sync, test_qproi         <td>Exercise the smart encoding functionality
 * <tr><td>test_aaa_service                    <td>Run 3A (AE / AWB / AF) processes
 * <tr><td>test_aacdec, test_aacenc            <td>Encode / decode the advanced audio coding (AAC) audio
 * <tr><td>test_efm                            <td>Exercise the encode from memory (EFM) functionality
 * <tr><td>test_ldc                            <td>Exercise the LDC functionality
 * <tr><td>test_eis                            <td>Exercise the EIS functionality
 * <tr><td>test_multi_chan                     <td>Run the multi-channel functionality
 * <tr><td>test_vin_cap                        <td>Exercise the VIN signal suspend / recovery functionality
 * <tr><td>test_manual_feed                    <td>Exercise the canvas and pyramid manual feed functionality
 * <tr><td>test_netlink                        <td>Exercise the Netlink functionality
 * <tr><td>test_img_scale                      <td>Exercise the image scale functionality
 * <tr><td>test_statistics                     <td>Exercise the stream statistics functionality
 * <tr><td>test_poll                           <td>Exercise the IAV data poll functionality
 * <tr><td>test_custom_vout                    <td>Exercise the customized VOUT functionality
 * <tr><td>test_stitch                         <td>Run the multi-VIN stitching functionality
 * <tr><td>test_smartrc_v3                     <td>Run the SmartRC functionality
 * <tr><td>cavalry_load                        <td>Load CVflow® firmware
 * <tr><td>cavalry_log                         <td>Capture / parse the CVflow log
 * <tr><td>test_nnctrl, test_nnctrl_live       <td>Exercise the NN flow control functionality
 * <tr><td>test_cavalry_mem                    <td>Exercise the NN memory management functionality
 * <tr><td>rtsp_server                         <td>Run the real-time streaming protocol (RTSP) streaming
 * <tr><td>load_ucode                          <td>Load the DSP microcode
 * </table>
 *
 * The application can run a variety of networks, including the following:
 *     - Object classification
 *     - Detection for objects, face, hands, and more
 *     - Face recognition
 *     - Segmentation
 *     - Tracking
 *     - Audio
 *     - Long short-term memory (LSTM)
 *
 * - - - -
 *
 * @section ov_deliverable_list 3. SDK Deliverable List
 *
 * Some documents, training video clips, and tools are released together with the software
 * development kit (SDK) source code package.
 * The following are the deliverable lists for different chip families. Users can find more detailed
 * information from the <em>Cooper Linux SDK General Deliverable List</em> PDF documents.
 *
 * @subsection ov_deliverable_list_cv5x 3.1 Cooper CV5x SDK Deliverables List
 *
 * Below is the Cooper Linux SDK CV5x general deliverables list.
 * 1. CNNGen - Toolchain, Source Codes, and User Guide
 * | No.  | Type          | Name                                                                            | Version | Date     |
 * | :--: | :--:          | :---                                                                            | :--:    | :--:     |
 * | 1    | Toolchain     | **Ambarella Toolchain CNNGen \<version\> \<date\>.tar.xz**                      | 2.5.5   | 2023.08  |
 * | 2    | Source Codes  | **cvflow cnngen samples \<version\> \<date\>.tar.xz**                           | 1.6     | 20230406 |
 * | 3    | Source Codes  | **cvflow cnngen samples \<version\> \<date\>.tar**                              | 1.6.2   | 20230731 |
 * | 4    | Videos        | CNNGen Training Video 1 Introduction.mp4                                        | 0.3     |          |
 * | 5    | Videos        | CNNGen Training Video 2 Porting Workflow.mp4                                    | 0.3     |          |
 * | 6    | Videos        | CNNGen Training Video 3 Porting Workflow.mp4                                    | 0.3     |          |
 * | 7    | Videos        | CNNGen Training Video 4 Deployment.mp4                                          | 0.3     |          |
 * | 8    | Videos        | CNNGen Training Video 5 GSG.mp4                                                 | 0.3     |          |
 * | 9    | Videos        | CNNGen Training Video 6 GSG.mp4                                                 | 0.3     |          |
 * | 10   | Doc           | Ambarella CVflow CNNGen Simple Introduction Customer                            | 0.1     | 20210324 |
 * | 11   | Webpage Doc   | CNNGen User Guide in Doxygen Format                                             | 1.6     |          |
 *
 * 2. Software - Cooper Linux SDK Source Codes, User Guide, GCC Toolchain, and AmbaUSB
 * | No.  | Type          | Name                                                                            | Version | Date     |
 * | :--: | :--:          | :---                                                                            | :--:    | :--:     |
 * | 1    | Source Codes  | **cooper linux sdk \<version\> \<date\>.tar.xz**                                | 1.0     | 20230801 |
 * | 2    | Doc           | Ambarella Cooper Linux SDK1.0 CV5x Release Notes                                | 0.1     | 20230720 |
 * | 3    | Doc           | Ambarella Cooper Linux SDK Getting Started Guide                                | 0.1     | 20230726 |
 * | 4    | Doc           | Ambarella Cooper Linux SDK Code Building                                        | 0.2     | 20230804 |
 * | 5    | Doc           | Ambarella CV5x DG Flexible Linux SDK0.5 CVflow FAQ                              | 0.1     | 20220114 |
 * | 6    | Doc           | Ambarella DG Cooper Linux SDK CV5x CV7x Security                                | 1.0     | 20231010 |
 * | 7    | Doc           | Ambarella DG Flexible Linux SDK JTAG Setup                                      | 3.1     | 20210924 |
 * | 8    | Doc           | Ambarella CV5x UG Flexible Linux DRAM Tuning                                    | 1.0     | 20230919 |
 * | 9    | Doc           | Ambarella AN SDK Approved Vendor List                                           | 0.7     | 20230702 |
 * | 10   | Webpage Doc   | Linux SDK User Guide in Doxygen Format                                          | NA      |          |
 * | 11   | ARM Linaro Toolchain | **Ambarella CortexA76 Toolchain \<version\> \<date\>.tar.xz**            | 12.2.1  | 2023.04  |
 * | 12   | Flash Tool    | **Ambarella AmbaUSB <version>.zip**                                             | v5.0.8  |          |
 *
 * 3. Hardware - Hardware Programming Manual
 * | No.  | Type          | Name                                                                            | Version |
 * | :--: | :--:          | :---                                                                            | :--:    |
 * | 1    | Doc           | AMBARELLA CV5 HW PRM                                                            | 0.9     |
 * | 2    | Doc           | AMBARELLA CV52 HW PRM                                                           | 0.8     |
 *
 *
 * @subsection ov_deliverable_list_cv7x 3.2 Cooper CV7x SDK Deliverables List
 *
 * Below is the Cooper Linux SDK CV7x general deliverables list.
 * 1. CNNGen - Toolchain, Source Codes, and User Guide
 * | No.  | Type          | Name                                                                            | Version | Date     |
 * | :--: | :--:          | :---                                                                            | :--:    | :--:     |
 * | 1    | Toolchain     | **Ambarella Toolchain CNNGen \<version\> \<date\>.tar.xz**                      | 3.5.5   | 2023.08  |
 * | 2    | Source Codes  | **cvflow cnngen samples \<version\> \<date\>.tar.xz**                           | 1.6     | 20230406 |
 * | 3    | Source Codes  | **cvflow cnngen samples \<version\> \<date\>.tar**                              | 1.6.2   | 20230731 |
 * | 4    | Videos        | CNNGen Training Video 1 Introduction.mp4                                        | 0.3     |          |
 * | 5    | Videos        | CNNGen Training Video 2 Porting Workflow.mp4                                    | 0.3     |          |
 * | 6    | Videos        | CNNGen Training Video 3 Porting Workflow.mp4                                    | 0.3     |          |
 * | 7    | Videos        | CNNGen Training Video 4 Deployment.mp4                                          | 0.3     |          |
 * | 8    | Videos        | CNNGen Training Video 5 GSG.mp4                                                 | 0.3     |          |
 * | 9    | Videos        | CNNGen Training Video 6 GSG.mp4                                                 | 0.3     |          |
 * | 10   | Doc           | Ambarella CVflow CNNGen Simple Introduction Customer                            | 0.1     | 20210324 |
 * | 11   | Webpage Doc   | CNNGen User Guide in Doxygen Format                                             | 1.6     |          |
 *
 * 2. Software - Cooper Linux SDK Source Codes, User Guide, GCC Toolchain, and AmbaUSB
 * | No.  | Type          | Name                                                                            | Version | Date     |
 * | :--: | :--:          | :---                                                                            | :--:    | :--:     |
 * | 1    | Source Codes  | **cooper linux sdk \<version\> \<date\>.tar.xz**                                | 1.0     | 20230801 |
 * | 2    | Doc           | Ambarella Cooper Linux SDK1.0 CV72 Release Notes                                | 0.1     | 20230720 |
 * | 3    | Doc           | Ambarella Cooper Linux SDK Getting Started Guide                                | 0.1     | 20230726 |
 * | 4    | Doc           | Ambarella Cooper Linux SDK Code Building                                        | 0.2     | 20230804 |
 * | 5    | Doc           | Ambarella DG Cooper Linux SDK CV5x CV7x Security                                | 1.0     | 20231010 |
 * | 6    | Doc           | Ambarella DG Flexible Linux SDK JTAG Setup                                      | 3.1     | 20210924 |
 * | 7    | Doc           | Ambarella CV7x UG Flexible Linux DRAM Tuning                                    | 1.0     | 20230919 |
 * | 8    | Doc           | Ambarella AN SDK Approved Vendor List                                           | 0.7     | 20230702 |
 * | 9    | Webpage Doc   | Linux SDK User Guide in Doxygen Format                                          | NA      |          |
 * | 10   | ARM Linaro Toolchain | **Ambarella CortexA76 Toolchain \<version\> \<date\>.tar.xz**            | 12.2.1  | 2023.04  |
 * | 11   | Flash Tool    | **Ambarella AmbaUSB <version>.zip**                                             | v5.0.8  |          |
 *
 * 3. Hardware - Hardware Programming Manual
 * | No.  | Type          | Name                                                                            | Version |
 * | :--: | :--:          | :---                                                                            | :--:    |
 * | 1    | Doc           | AMBARELLA CV72 HW PRM                                                           | 0.4     |
 *
 * - - - -
 *
 * @section ov_ambahotfix 4. Ambarella Hotfix
 *
 * After the SDK is released, hotfixes are used to fix bugs or support new features.
 * Ambarella maintains two threads of hotfixes for every SDK version: generic hotfix and
 * customer specific hotfix.
 * - Ambarella will release generic hotfixes to all customers on standard SDK, when there are
 *   bugs or features that affect all customers.
 * - When a bug or feature affects certain use cases for some customers, a specific hotfix
 *   is released to those customers.
 *
 * The hotfix content is source code files that need to be updated rather than the diff of the changes.
 *
 * @subsection ov_ambahotfix_name 4.1 Hotfix Name
 * A hotfix name at least contains SDK version, hotfix number, and create date.
 *
 * Take `cooper_linux_sdk_1.0.0.5_CV72_Update_codec..._20231102.tar.bz2` for example,
 * - "cooper_linux_sdk_1.0.0" is the SDK version.
 * - The "5" after SDK version is the hotfix number, which means there were 4 hotfixes before this version.
 * - "CV72_Update_codec..." is a brief description about this hotfix.
 * - "20231102" is the date when the hotfix is created.
 *
 * @note
 * - Generic and customer specific hotfixes are maintained in individual thread,
 *   so the hotfix numbers grow separately.
 * - If a customer sepecific hotfix is dated later than the generic hotfix,
 *   it means that the customer specific hotfix is based on the generic hotfix.
 *
 * @subsection ov_ambahotfix_prepare 4.2 How Ambarella Creates Hotfix
 * When Ambarella prepares a hotfix for a specific customer, Ambarella assumes the customer has applied
 * both generic and customer specific hotfixes, so the code base is clean SDK code plus generic
 * and customer specific hotfixes for that customer.
 *
 * When creating a generic hotfix, the code base is clean SDK code plus previous generic hotfixes.
 *
 * @subsection ov_ambahotfix_apply 4.3 How to Apply Hotfix
 * User can refer to `readme.txt` in hotfix tarball file to apply the hotfix. The `apply.sh`
 * script simply does file replacement, it cannot detect the conflict in code.
 * Usually, executing the `apply.sh` script is enough.
 *
 * Given the fact that Ambarella creates hotfixes based on previous generic and customer specific
 * hotfixes, customers should ensure that previous hotfixes are all applied before applying
 * a new one.
 * Since generic and customer specific hotfixes are maintained in different threads, they
 * have different code bases. There might be a conflict when merging them into the customer code.
 * Contact Ambarella support team if there is a conflict.
 *
 * @note
 * - After applying a hotfix, please always do `make distclean`. It is important when files
 *   are removed or changed to another folder after applying a hotfix because the change is not
 *   synchronized to the compile output folder of `ambarella/out/`.
 * - If `make distclean` is not executed, customers may see the unexpected compiling errors
 *   or changes that do not take effect.
 *
 *//*!
 * @file doc_ov_code_build.h
 * @brief
 * @date 2022-09-15
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
 * @page ov_code_build SDK Code Building
 *
 * @section code_build_history 0. Revision History
 *
 * <table>
 * <caption id="code_build_history">Revision History</caption>
 * <tr><th> SDK Version                <th> Updated Date           <th> Modification
 * <tr><td> CV5x_SDK_0.2               <td> 20211021               <td> Initial Version
 * <tr><td> CV5x_SDK_0.5               <td> 20220114               <td> Updated Section @ref sub_code_build_set_arm
 * <tr><td rowspan="2"> CV5x_SDK_1.0   <td rowspan="2"> 20220415   <td> Updated Section @ref sub_code_build_set_arm
 * <tr>                                                            <td> Updated Section @ref sub_code_build_full_build
 * <tr><td rowspan="2"> CV5x_SDK_2.0   <td> 20220915               <td> Migrated this Code Building document from Word form into Doxygen form
 * <tr>                                <td> 20221025               <td> Update Cortex Toolchain to 12.1 in Section @ref sub_code_build_set_arm
 * <tr><td> CV5x_SDK_2.5               <td> 20230227               <td> Updated Section @ref sub_code_build_pc_evk_nfs
 * <tr><td> Cooper_SDK_0.5             <td> 20230420               <td> Initial Version of Cooper SDK
 * <tr><td rowspan="5"> Cooper_SDK_1.0 <td rowspan="4"> 20230720   <td> Update Section @ref sub_code_build_set_ubu
 * <tr>                                                            <td> Updated Section @ref sub_code_build_set_tool
 * <tr>                                                            <td> Updated Section @ref sub_code_build_set_doc
 * <tr>                                                            <td> Updated Section @ref sub_code_build_set_pod
 * <tr>                                <td> 20230811               <td> Added Section @ref code_build_oss "8. Build OSS Libraries"
 * </table>
 *
 * - - - -
 *
 * @section code_build_overview 1. Overview
 *
 * This document provides information to help users navigate through the Ambarella Cooper
 * Linux software development kit (SDK), prepare a build machine, build the SDK, and
 * share it during product development.
 *
 * The Ambarella Cooper Linux SDK development environment requires a host that uses the
 * Linux operating system (OS). This document guides the reader through the installation and
 * configuration of the Linux environment to assist in the compilation of the Cooper
 * Linux SDK. A cross-compile tool suite is used to compile the Linux images.
 *
 * @note
 * The configurations described in this document are provided as recommendations only.
 *
 * This chapter describes how to perform the following:
 * <ul>
 * <li> Section @ref sub_code_build_ove_scope
 * <li> Section @ref sub_code_build_ove_flex
 * <li> Section @ref sub_code_build_ove_soft
 * <li> Section @ref sub_code_build_ove_sou
 * </ul>
 *
 * @subsection sub_code_build_ove_scope 1.1 Scope of Document
 *
 * Included in this document are the hardware, software, and network requirements
 * for building the SDK and instructions for setting up the Ubuntu machine and PC.
 *
 * The following describes the contents of each chapter:<br>
 *  - Chapter @ref code_build_overview includes a table of key document updates and
 *     an introduction to the SDK package contents, software architecture, and source code.<br>
 *  - Chapter @ref code_build_requirement lists the development environment requirements.<br>
 *  - Chapter @ref code_build_setup_linux provides instructions on setting up
 *     the Ubuntu machine for building codes.<br>
 *  - Chapter @ref code_build_full_sdk "4. Build Full SDK Code" provides
 *    instructions for building new firmware with the full SDK code.<br>
 *  - Chapter @ref code_build_eva_sdk provides instructions for building new
 *     firmware with the evaluation SDK package.<br>
 *  - Chapter @ref code_build_setup_pc provides instructions for setting up the PC.<br>
 *  - Chapter @ref code_build_upgrade provides methods for upgrading the
 *     firmware on the CV5x / CV7x board.<br>
 *  - Chapter @ref code_build_oss provdies instructions for building open source software (OSS) libraries.<br>
 *
 * @subsection sub_code_build_ove_flex 1.2 Cooper Linux SDK
 *
 * Ambarella Cooper Linux SDK can be downloaded from the Ambarella Customer Portal site.
 * Contact the Ambarella support team for details on downloading the SDK.
 *
 * The SDK includes the following:
 *  - <b>Evaluation:</b> Evaluation package
 *  - <b>SDKx.x</b> SDK package, which includes code and documentation
 *    - Package: Source code package
 *    - Document: Hardware and software documentation
 *  - <b>Tools:</b> Ambarella tools
 *
 * @subsection sub_code_build_ove_soft 1.3 Software Architecture
 *
 * The following figure shows the system architecture for the CV5x / CV7x chip. The Ambarella
 * CV5x / CV7x platform uses the flexible, open source Linux operating system. Developers
 * can customize the Linux OS for many purposes, including using a novel graphical user
 * interface (GUI) engine such as <b>Qt</b>, enhancing networking, simplifying WiFi use,
 * and reusing available source libraries such as <b>WebServer</b> and <b>HostAP</b>.
 * Additionally, users can easily port a variety of Linux video frameworks such as <b>FFmpeg</b>,
 * <b>GStreamer</b>, and <b>IPV6</b>.
 *
 * @anchor code_build_soft_arch_fig
 * @image html code_build_soft_arch.png "Figure 1-1. Cooper Software Architecture."
 *
 * @subsection sub_code_build_ove_sou 1.4 Source Code
 *
 * @subsubsection dsub_code_build_ove_dir 1.4.1 Code Directory
 *
 * The top directory of the Cooper Linux SDK package is `ambarella/`.
 * Subdirectories are listed below. Chapter @ref code_build_full_sdk "4. Build Full SDK Code"
 * introduces build commands to extract the code from the package.
 *
 * <table>
 * <caption id="code_build_code_diretory">Table 1-1. Code Directory.</caption>
 * <tr><th> Directory                 <th> Content
 * <tr><td> <b>amboot/</b>            <td> Bootloader (BLD), board support toolkit, and file system information about the partitions
 * <tr><td> <b>app/</b>               <td> Demo applications
 * <tr><td> <b>boards/</b>            <td> The compile configuration files, DDR configuration, and bootstrap (BST)
 * <tr><td> <b>build/</b>             <td> Rules for makefile and AmbaConfig
 * <tr><td> <b>document/</b>          <td> Doxygen content and configuration rules
 * <tr><td> <b>include/</b>           <td> Header files
 * <tr><td> <b>kernel/</b>            <td> Linux kernel, digital signal processor (DSP) firmware, image audio
 *                                         video (IAV) / DSP / sensor and peripheral devices drivers
 * <tr><td> <b>external</b>           <td> External WiFi modules codes
 * <tr><td> <b>linux-5.15</b>         <td> Linux kernel and patch codes
 * <tr><td> <b>private</b>            <td> Ambarella propriety drivers / modules codes and binaries
 * <tr><td> <b>license/</b>           <td> License files of each component
 * <tr><td> <b>out/</b>               <td> The build target and intermediate objects
 * <tr><td> <b>packages/</b>          <td> Libraries that assist in video processing, streaming, or transferring
 * <tr><td> <b>data_transfer</b>      <td> Code for data storage over NFS and code for data transferring via USB / TCP
 * <tr><td> <b>img_algo</b>           <td> Image algorithm library; the pre-built binary is in
 *                                         `ambarella/prebuild/imgproc` (Source codes are not released)
 * <tr><td> <b>utils</b>              <td> Utility library codes
 * <tr><td> <b>nnctrl</b>             <td> Initial Cavalry binary, which is generated by cavalry_gen
 * <tr><td> <b>vproc</b>              <td> Pre-defined directed acyclic graphs (DAGs) used to convert the data format
 * <tr><td> <b>prebuild/</b>          <td> Pre-built binaries, including Ambarella libraries and third-party libraries
 * <tr><td> <b>ambarella/library</b>  <td> Binary format of various Ambarella proprietary libraries
 * <tr><td> <b>imgproc</b>            <td> Binary format of library file and image tuning parameter files
 * <tr><td> <b>third-party</b>        <td> Binary format of third party-library files
 * <tr><td> <b>rootfs/</b>            <td> System (Rootfs)
 * <tr><td> <b>unit_test/</b>         <td> Unit test tools
 * </table>
 *
 * @subsubsection dsub_code_build_ove_sou 1.4.2 Source Code and Software Layers
 *
 * The following shows the relationship between the software architecture
 * (figure @ref code_build_soft_arch_fig "Figure 1-1. Cooper Software Architecture") and
 * the source code directories. Additional software modules will be added in later SDK versions.
 *
 * <table>
 * <caption id="code_build_soft_arch_dirt">Table 1-2. Code Category.</caption>
 * <tr><th> Category                        <th> Architecture                    <th> Directory
 * <tr><td rowspan="5"> <b>System</b>       <td> Bootstrap and BootLoader        <td> ambarella/boot/amboot
 * <tr>                                     <td> Linux kernel and device driver  <td> ambarella/kernel/linux
 * <tr>              <td> DSP / IAV / video input (VIN) / video output (VOUT)    <td> ambarella/drv_modules
 * <tr>                                     <td> File system                     <td> ambarella/rootfs
 * <tr>                                     <td> System configuration            <td> ambarella/boards
 * <tr><td rowspan="2"> <b>Middleware</b>   <td> Neural network control (NNCtrl) <td> ambarella/packages/nnctrl
 * <tr>                                     <td> VProc                           <td> ambarella/packages/vproc
 * <tr><td rowspan="2"> <b>Application</b>  <td> Unit test tools                 <td> ambarella/unit_test
 * <tr>                                     <td> Demo applications               <td> ambarella/app
 * </table>
 *
 * @subsubsection dsub_code_build_ove_ava 1.4.3 Source Code Availability
 *
 * The source code for the software shown in the application, middleware, and system frames down in
 * @ref code_build_soft_arch_fig "Figure 1-1. Cooper Software Architecture" are included in the SDK
 * package. Third-party libraries (such as the image processing library, the dewarp library, (fisheye
 * and lens distortion correction (LDC)), and the BST) are provided as pre-built binaries. Users can
 * obtain the source code for each library from the internet.
 *
 * Ambarella warrants the source code for the software shown in the middleware and system frames shown in
 * figure @ref code_build_soft_arch_fig "Figure 1-1. Cooper Software Architecture". Ambarella does not
 * warrant the source code shown in the application frame. Users can modify the unit test and
 * applications source codes in order to meet product requirements. The software shown in the application
 * frame is provided to enhance the user experience and streamline application development.
 *
 * @subsubsection dsub_code_build_ove_cv2x 1.4.4 Comparison to CV2x SDK
 *
 * Due to the similarity between the code directories and software layers of the CV2x SDK and the
 * Cooper SDK, upgrading to the Cooper SDK from the CV2x SDK is straightforward. For more details,
 * refer to page @ref page_sys_mg_cv2x "Migration Guide From CV2x SDK".
 *
 * - - - -
 *
 * @section code_build_requirement 2. Requirements for the Development Environment
 *
 * This chapter includes the following sections:
 * <ul>
 * <li> Section @ref sub_code_build_req_ove
 * <li> Section @ref sub_code_build_req_lin
 * <li> Section @ref sub_code_build_req_win
 * <li> Section @ref sub_code_build_req_net
 * </ul>
 *
 * @subsection sub_code_build_req_ove 2.1 Overview
 *
 * Using the Ambarella SDK requires three machines:
 *   - Portal release order (PRO) release server (https://customer.ambarella.com/)
 *   - Linux build machine to cross-compile the binary
 *   - Windows PC to download the binary
 *
 * The PRO server (1) is organized and supported by Ambarella. Developers are expected
 * to arrange and organize the Linux build machine (2) and the Windows PC (3).
 * @image html code_build_sdk_upgrade_pipeline.png "Figure 2-1. SDK Download / Build / Firmware Upgrade Pipeline."
 *
 * The developer downloads the SDK package from the Ambarella PRO server to the
 * PC and transfers the files to a Linux build machine that runs the <b>Ubuntu</b> server
 * (Chapter @ref code_build_setup_linux "3. Set Up the Linux Build Machine").
 * The <b>toolchain</b> can be used to build the code (Chapter
 * @ref code_build_full_sdk "4. Build Full SDK Code") when it is
 * installed in the build machine.
 *
 * After the SDK is built, the firmware is available to the build machine.
 * The development PC is prepared (Chapter
 * @ref code_build_eva_sdk "5. Build Evaluation SDK Code"), and the firmware
 * binary is transmitted to the PC (described below). The binary is then burned to flash
 * on the development board using the Ambarella <b>AmbaUSB</b> tool (Chapter
 * @ref code_build_upgrade "7. Upgrade the Firmware to the Development Platform").
 * Contact an Ambarella support team member for development board setup and use.
 *
 * Ambarella recommends using a <b>Samba</b> server that has been set up on
 * the build machine to transmit the firmware binary to the PC.
 *
 * <b>Samba</b> setup is outside the scope of this document. For pertinent
 * information, refer to
 * http://www.samba.org/samba/docs/man/Samba-HOWTO-Collection.
 *
 * @subsection sub_code_build_req_lin 2.2 Linux Build Machine
 *
 * The following are the hardware requirements for the Linux build environment;
 * refer to Chapter @ref code_build_setup_linux "3. Set Up the Linux Build Machine"
 * for more information:
 *  - 64-bit capable
 *  - Two Intel(R)® Xeon(R)® X 5670, 2.93-GHz, 12-M cache
 *  - 32-GB memory (8 x 4 GB), 1333-MHz, dual-rank RDIMMs for two processors
 *  - 600-GB, 3.5-inch 15 K RPM, 6-Gbps SAS hot plug hard drive
 *  - Dual-port gigabit Ethernet
 *
 * @subsection sub_code_build_req_win 2.3 Windows PC
 *
 * A Windows PC connected to the Internet is used to download the SDK and / or
 * upgrade the firmware (Chapter @ref code_build_eva_sdk "5. Build Evaluation SDK Code").
 * For more details about upgrading the firmware, refer to (Chapter @ref code_build_upgrade
 * "7. Upgrade the Firmware to the Development Platform").
 *
 * The PC must support the following:
 * <table>
 * <caption id="code_build_pc_support">Table 2-1. PC Requirements.</caption>
 * <tr><th> Category           <th> Requirement
 * <tr><td> CPU                <td> Intel i5 or higher grade
 * <tr><td> Memory             <td> 8-GB system memory or more
 * <tr><td> Hard disk          <td> 120 GB or more
 * <tr><td> Video card         <td> 3D hardware accelerator card required – 100% DirectX 9.0c compatible.
 *                                  AMD / ATI HD2600 Pro or NVidia 9800 GT or above to assure the full
 *                                  frame rate of high-definition (HD) playback is preferred
 * <tr><td> Monitor            <td> 19-inches LCD or larger with digital video interface (DVI) input.
 *                                  DELL UltraSharp 2709W (VA panel) is preferred
 * <tr><td> LCD TV             <td> 24-inch LCD TV or larger with YPbPr input (1080p resolution)
 * <tr><td> Ethernet card      <td> 1000 Mbps (adaptive)
 * <tr><td> I/O interfaces     <td> RS232
 * <tr><td> Operating system   <td> 64-bit Windows 7 / 8 or 64-bit Ubuntu 16.04 LTS
 * <tr><td> Virtual machine    <td> Oracle Virtualbox 4.4.30 or later
 * </table>
 *
 * @subsection sub_code_build_req_net 2.4 Network Topology
 *
 * If multiple developers are working on a network, Ambarella recommends
 * acquiring a powerful build machine and sharing it on each developer's
 * PC. Developers A, B, and C can connect to the building server using SSH
 * protocols in a local area network (LAN) (LAN 1). All developer PCs should have two network
 * cards: the first card connected to a public LAN (LAN 1) and the second to a private
 * LAN (LAN 2, 3, 4) between the local PC and the development board.
 *
 * Because the SDK includes tools for Windows OS, and the
 * development board is based on Linux OS, Ambarella suggests using a Linux
 * virtual machine (VM) on a Windows PC to install the Ambarella SDK. See the
 * figure below for a diagram of the network topology for the development
 * team with server sharing.
 *
 * Section @ref sub_code_build_pc_linux provides instructions on installing
 * the Linux virtual machine on Windows PCs, and Section @ref sub_code_build_pc_cifs
 * provides details on sharing the build machine between the PCs and the
 * development boards.
 * @image html code_build_network_topology.png "Figure 2-2. Network Topology for the Development Team with Server Sharing."
 *
 * - - - -
 *
 * @section code_build_setup_linux 3. Set Up the Linux Build Machine
 *
 * This chapter includes the following sections:
 * <ul>
 * <li> Section @ref sub_code_build_set_ubu
 * <li> Section @ref sub_code_build_set_dow
 * <li> Section @ref sub_code_build_set_arm
 * <li> Section @ref sub_code_build_set_tool
 * <li> Section @ref sub_code_build_set_doc
 * <li> Section @ref sub_code_build_set_pod
 * </ul>
 *
 * @subsection sub_code_build_set_ubu 3.1 Install Ubuntu OS
 *
 * @subsubsection dsub_code_build_set_pag 3.1.1 Download Ubuntu
 *
 * 1. Access the Ubuntu official website: http://www.ubuntu.com/download/server.
 *
 * 2. At <b>Download Options</b>, select <b>Ubuntu Server 20.04.6 LTS</b>. Only
 * <b>64-bit</b> Ubuntu is supported.
 *
 * 3. To download the ISO file, click the <b>Download</b> button.
 * @image html code_build_linux_ubn_down.png "Figure 3-1. Linux Ubuntu Download Selection and Download Button."
 *
 *
 * A common method for installing Ubuntu consists of creating a compact disk (CD) to install
 * it after downloading the ISO file. Many applications enable burning data to
 * a disk, including <b>Rufus</b>, <b>Ventoy</b>, <b>UltraISO</b>, <b>Nero
 * Burning</b>, and <b>Infra Recorder</b>. For further application recommendations,
 * refer to the following Ubuntu website: https://help.ubuntu.com/community/BurningIsoHowto.
 *
 * To install Ubuntu using another form of media, refer to the following links:
 *   - https://help.ubuntu.com/20.04/installation-guide/
 *   - http://www.ubuntu.com/
 *
 * @subsubsection dsub_code_build_set_ins 3.1.2 Ubuntu Installation
 *
 * 1. A <b>64-bit</b> server is recommended for installing Ubuntu. Refer to the hardware
 *    recommendations described in Section @ref sub_code_build_req_lin. Additionally,
 *    note the following:
 *    - Prior to installation, the machine should have no OS or data,
 *      as the installation process erases all existing data.
 *    - Using a virtual machine is not recommended as it lengthens the SDK build time.
 *    - To build the Ambarella SDK, the machine requires at least 1.5 GB of RAM and at
 *      least 15 GB of disk space if <b>Ubuntu</b> is running on a virtual machine.
 *
 * 2. Load the CD with the Ubuntu ISO file in the drive and restart the machine. Verify that
 *    the basic input / output system (BIOS) configuration and the machine settings are consistent
 *    with a boot from CD ROM.
 *
 * 3. From the Ubuntu installation start screen, choose the preferred <b>Language</b> (see the following figure).
 *
 * 4. Next, choose <b>Install Ubuntu Server</b> (see the following figure).
 * @image html code_build_install_start.png "Figure 3-2. Ubuntu Installation Start Screen."
 *
 * 5. Follow the instructions on the screen. Typically, the <b>Default</b> settings will suffice.
 *
 * 6. At the <b>Guided storage configuration</b> prompt, select <b>Set up this disk as an LVM group</b>
 *    and choose <b>Done</b>.
 * @image html code_build_install_set_lvm.png "Figure 3-3.Ubuntu Installation LVM Setup."
 *
 * 7. For the prompt <b>Storage configuration</b>, choose <b>Done</b>.
 * @image html code_build_install_storage_config.png "Figure 3-4. Ubuntu Installation Storage Configuration."
 *
 * 8. For the <b>Confirm</b> prompt and choose <b>Yes</b>.
 * @image html code_build_install_confirm_destruct.png "Figure 3-5. Ubuntu Installation Confirm Destructive Action."
 *
 * 9. At the <b>Profile setup</b> screen, enter the username and password, and choose <b>Done</b>.
 * @image html code_build_install_profile_setup.png "Figure 3-6. Ubuntu Installation Profile Setup."
 *
 * 10. At the <b>SSH Setup</b> prompt, select <b>Install OpenSSH server</b> and choose <b>Done</b>.
 * @image html code_build_install_ssh.png "Figure 3-7. Ubuntu Installation SSH Setup."
 *
 * 11. The following interface indicates that the installation is complete.
 * @image html code_build_install_complete.png "Figure 3-8. Ubuntu Installation Complete."
 *
 * @subsubsection dsub_code_build_set_net 3.1.3 Ubuntu Network Configuration
 *
 * Configure the network with DHCP or static IP.
 *
 * 1. Log in to the server and configure the network according to the machine environment.
 *   - IP Address:          $ sudo vim /etc/network/interfaces  (edit files …)
 *   - DNS server:          $ sudo vim /etc/resolv.conf	        (edit files …)
 *   - Restart networking:  $ sudo /etc/init.d/networking restart
 *
 * 2. Use the following command to verify that the network is connected.
 * (Ensure that the root is correct.)
 * @code {.c}
 * build $ ping www.google.com
 * @endcode
 *
 * @note
 * Users can access another website, such as www.ubuntu.com, to confirm the network connection.
 *
 * @subsection sub_code_build_set_dow 3.2 Install Development Packages
 *
 * Users must install several packages before beginning the development process.
 * In the <b>Ambarella release for the Toolchain</b> package, users can locate the
 * installation script to automatically install the required packages.
 *
 * Ensure that the building workstation has Internet access, then run the scripts below,
 * which are mentioned in the following sections.
 *
 * @subsection sub_code_build_set_arm 3.3 Install the Arm® Toolchain
 *
 * The toolchain binary is <b>PRO server</b>, which is named
 * `Ambarella_CortexA76_Toolchain_GCC*>*_<Date>.tar.xz`.
 *
 * The toolchain source code can be downloaded from the GCC official
 * website and Git. The version and commit ID used in the latest SDK
 * are as follows:
 *
 *       GCC: 12.2.1  git://gcc.gnu.org/git/gcc.git
 *       Revision:  64efeac03cb9fa2603bb6628712f3a2541aef1cb
 *       GLIBC: 2.37  git://sourceware.org/git/glibc.git
 *       Revision:  1d63573f81945a489ea169636fa11850bc74716b
 *       GDB: 13.1   git://sourceware.org/git/binutils-gdb.git
 *       Revision: b3eff3e15576229af9bae026c5c23ee694b90389
 *       Binutils: 2.40  git://sourceware.org/git/binutils-gdb.git
 *       Revision: ded035f913e4d8c989880cf5928b6b5fca9466ae
 *
 * @note
 * The toolchain is often upgraded during SDK development. Refer to the
 * <em>Ambarella Cooper Linux SDK - Release Notes</em>
 * document for the exact toolchain version.
 *
 * The following lists the steps for installing Arm Toolchain:
 *
 *   1. Download the toolchain package
 *      `Ambarella_CortexA76_Toolchain_GCC*.*_<Date>.tar.xz` from the PRO server.
 *
 *   2. Install the toolchain. For Ubuntu Linux, the commands are as follows:
 * @code {.c}
 * build $ tar xvfJp Ambarella_CortexA76_Toolchain_GCC*.*_<Date>.tar.xz
 * build $ cd Ambarella_CortexA76_Toolchain_GCC*.*_<Date>
 * build $ sudo chmod +x ubuntuToolChain-Linux*.*_<Date>
 * build $ ./ubuntuToolChain-Linux*.*_<Date>
 * @endcode
 *
 *   3. (Optional) Write a simple program and run it on the development platform.
 *     - Create a file hello.c with the following content:
 * @code {.c}
 * #include <stdio.h>
 * int main()
 * {
 *     printf("Hello World!\n");
 *     return 0;
 * }
 * @endcode
 *     - Compile the file:
 * @code {.c}
 * build $ export PATH=$PATH:/usr/local/cortex-a76-2023.04-gcc12.2-linux5.15/bin/
 * build $ aarch64-linux-gnu-gcc hello.c -o hello
 * @endcode
 *     - Put the executable program "hello" in the development
 *       platform and run the following command:
 * @code {.c}
 * board # ./hello
 * Hello World!
 * @endcode
 *
 * @subsection sub_code_build_set_tool 3.4 Install the Computer Vision (CV) Toolchain
 *
 * There are two CNNGen packages for CVflow_v2 and CVflow_v3, both of which use Ubuntu 2004 system:
 * - `Ambarella_Toolchain_CNNGen_2.*.*_2023****.tar.xz`: used is for CVflow_v2 (CV2x and CV5x) conversion;
 *   AmbaCaffe is included for retaining purpose
 * - `Ambarella_Toolchain_CNNGen_cv7x.3.*.*_2023****.tar.xz`: used for CVflow_v3 (CV7x) conversion;
 *   users can use the AmbaCaffe in the CVflow_v2 CNNGen toolchain package
 *
 * Before running the installation script for the toolchain, run the following command:
 * @code {.c}
 * build $ sudo apt-get update
 * @endcode
 *
 * Users should regularly upgrade the operating system as shown below, as the
 * toolchain is developed using the latest version OS.
 * @code {.c}
 * Build $ sudo apt-get upgrade
 * @endcode
 *
 * Although the command above is included in the installation script, Ambarella
 * recommends noting it and assigning it to an independent machine to avoid
 * a possible build conflict.
 *
 * Install the toolchain as shown below. For Ubuntu Linux, the commands are as follows:
 * @code {.c}
 * build $ cd Ubuntu-20.04
 * build $ sudo chmod +x ubuntuToolChain-<version>.ubuntu-20.04
 * build $ ./ubuntuToolChain-<version>.ubuntu-20.04
 * @endcode
 *
 * @note
 *  Users can use the official Caffe from https://github.com/BVLC/caffe.git compile,
 *  or they can use AmbaCaffe included in the package.  Additionally, users can use
 *  `AmbaCaffe_<version>/build_script/build-caffe-ubuntu20.04-cpu` to build both
 *  the public Caffe and AmbaCaffe.  Note that in the user's system, the user may be
 *  required to modify the script.
 *    @code {.c}
 *    build $ git clone https://github.com/BVLC/caffe.git
 *    build $ cd AmbaCaffe_<version>/
 *    build $ chmod u+x ./build_script/build-caffe-ubuntu20.04
 *    build $ ./build_script/build-caffe-ubuntu20.04-cpu caffe
 *    @endcode
 *  - For more details, refer to `readme.txt` in the CNNGen toolchain package.
 *
 * @subsection sub_code_build_set_doc 3.5 Install the CV Toolchain on Docker
 *
 * Docker is an open source, application-container engine that enables
 * developers to package their applications and dependencies into a
 * portable container, then publish or virtualize them to any Linux
 * machine. Containers are completely sandboxed and do not interface
 * with each other. Docker also provides another method for users to
 * deploy and run CNNGen.
 *
 * The following sections describe how to install the CV Toolchain on Docker.
 *
 * For more information about Docker, refer to https://docs.docker.com/.
 *
 * @subsubsection dsub_code_build_set_ins_doc 3.5.1 Docker Installation
 *
 * Dockers supports a variety of Ubuntu OS versions. Docker can be installed on both physical and virtual machines.
 *
 * The following steps for installing Docker are for reference only,
 * as users might have systems that require different Docker installations.
 *
 * 1. Install Docker using the following commands:
 *    @code {.c}
 *    build $ sudo apt-get install Docker
 *    build $ sudo apt-get install Docker.io
 *    @endcode
 *
 * 2. Add the current user to the Docker group and log in again (or reboot
 *    if using a virtual machine); otherwise, Docker requires root privilege.
 *    @code {.c}
 *    build $ sudo groupadd docker
 *    build $ sudo usermod –aG docker $USER
 *    @endcode
 *
 *    @note
 *    If users must deploy Docker on a server, Ambarella recommends using secure shell (SSH)
 *    service for various users, and not adding all users to the Docker
 *    group. Docker includes a "sudo" permission, enabling users in this group
 *    to add any folder in this server to the Docker container and use "root"
 *    to operate it.
 *
 * 3. Use the following command to verify the installation. If the
 *    subsequent messages appear, Docker is functioning correctly.
 *    @code {.c}
 *    build $ docker run hello-world
 *    Unable to find image 'hello-world:latest' locally
 *    latest: Pulling from library/hello-world
 *    1b930d010525: Pull complete
 *    Digest: sha256:9572f7cdcee8591948c2963463447a53466950b3fc15a247fcad1917ca215a2f
 *    Status: Downloaded newer image for hello-world:latest
 *
 *    Hello from Docker!
 *    This message shows that your installation appears to be working correctly.
 *
 *    To generate this message, Docker took the following steps:
 *      1. The Docker client contacted the Docker daemon.
 *      2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
 *         (amd64)
 *      3. The Docker daemon created a new container from that image which runs the
 *         executable that produces the output you are currently reading.
 *      4. The Docker daemon streamed that output to the Docker client, which sent it
 *         to your terminal.
 *
 *    To try something more ambitious, users can run an Ubuntu container with:
 *      $ docker run -it ubuntu bash
 *
 *    Share images, automate workflows, and more with a free Docker ID:
 *      https://hub.docker.com/
 *
 *    For more examples and ideas, visit:
 *      https://docs.docker.com/get-started/
 *    @endcode
 *
 * Users can then install Ubuntu and CNNGen toolchain with Dockerfile file, as follows.
 * If users used below Docker file to install the environment, please skip the steps in @ref dsub_code_build_set_ubu_doc.
 * @code {.c}
 * build $ docker build -t cv_tool_cpu . -f ./Docker_Files/Dockerfile_CNNGen_<full_version>_ubu2004_CPU
 * @endcode
 * For more details, refer to the `readme.txt` in CNNGen Toolchain pacakge. Users can also refer
 * to the following sections to install the package manually.
 *
 * @subsubsection dsub_code_build_set_ubu_doc 3.5.2 Install Ubuntu on Docker
 *
 * Docker supports a variety of operating systems and applications running in independent containers.
 * When a container begins, Docker automatically downloads the Docker image from
 * the Docker image repository (if it does not exist locally). The default
 * repository of Docker image is DockerHub.
 *
 * To create an <b>Ubuntu 20.04</b> container:
 *
 * 1. Pull the Docker image of Ubuntu 20.04 using the following command:
 * @code {.c}
 * build $ docker pull ubuntu:focal
 * @endcode
 * @note
 *  - Docker supports many versions of Ubuntu.  Users can find the corresponding
 *   commands for pulling images from https://hub.docker.com/_/ubuntu.
 *  - If users want to use <b>Cuda</b> in Docker, NVIDIA-Docker should be installed.
 *    NVIDIA-Docker is similar in usage to Docker.
 *  - Ambarella recommends using Ubuntu 18.04 to run CNNGen.
 *
 * 2. List local images using the following command:
 * @code {.c}
 * build $ docker images
 * REPOSITORY          TAG                 IMAGE ID            CREATED             SIZE
 * ubuntu              focal              ccc6e87d482b        3 weeks ago         64.2MB
 * @endcode
 *
 * 3. Create a new folder for sharing files between the build machine
 * and the container. Then, start a container and run a terminal as root. Install sudo and vim
 * using the following commands:
 * @code {.c}
 * build $ mkdir share_host
 * build $ docker run -v <Full Path>/share_host:/share_docker -itd --name ubuntu ubuntu:focal
 * build $ docker exec -it ubuntu /bin/bash
 * root # apt-get update
 * root # apt-get install sudo vim make
 * @endcode
 * @note
 *  - The option "-v <Full Path>/share_host:/share_docker" specifies the shared folders.
 *    "/share_host" in the build machine requires a full path.
 *    "/share_docker" is in the container.
 *  - The option "--name ubuntu" specifies the name of container.
 *  - The parameter "ubuntu:focal" specifies the Docker image which
 *    is pulled by step 1.
 *
 * 4. Add a user account, and add it to the "sudo" group using the following commands:
 * @code {.c}
 * root # useradd -d /home/docker -m docker
 * root # passwd docker
 * root # usermod -aG sudo docker
 * @endcode
 *
 * 5. Exit the terminal, and begin again with a new user account:
 * @code {.c}
 * root # exit
 * build $ docker exec --user docker -it ubuntu /bin/bash
 * docker $
 * @endcode
 * @note
 *  - The option "--user docker" specifies the username.
 *  - The usage above is an example; any name can be used.
 *  - For more details about Docker usage, refer to Section
 *    @ref dsub_code_build_set_com_doc.
 *
 * @subsubsection dsub_code_build_set_cnn_doc 3.5.3 Install CNNGen on Docker
 *
 * This section describes installing and setting up the environment for
 * <b>CNNGen</b> in a <b>Docker</b> container.
 *
 * 1. Copy the toolchain package via the shared folders and locate it
 * in the container. Install the toolchain using the following commands:
 * @code {.c}
 * docker $ cd Ubuntu-20.04
 * docker $ sudo chmod +x ubuntuToolChain-<version>.ubuntu-20.04
 * docker $ ./ubuntuToolChain-<version>.ubuntu-20.04
 * @endcode
 *
 * 2. Because the image is pulled from DockerHub, which does not include
 * third-party tools, users should install the tools using the following command:
 * @code {.c}
 * docker $ sudo apt-get install libncurses5-dev
 * @endcode
 *
 * 3. Set the environment for CNNGen, as follows:
 * @code {.c}
 * docker $ source /usr/local/amba-cv-tools-<version>.ubuntu-20.04/env/cv<*chip_name*>.env
 * @endcode
 *
 * @note
 * - If any of the following installations are unsuccessful, repeatedly run
 *   the installed script to ensure successful installation of all programs.
 * - For step 2 in particular, various systems may require different components;
 *   if errors occur during installation, follow the error information and
 *   install the required components.
 * - For more information about CNNGen, refer to the <em>CNNGen Doxygen Document</em>
 *   in the CVflow® CNNGen Samples package.
 *
 * @subsubsection dsub_code_build_set_con_doc 3.5.4 Close and Save a Container
 *
 * To close and save a container:
 *
 * 1. Exit and check a container ID using the following commands:
 * @code {.c}
 * docker $ exit
 * build $ docker ps
 * CONTAINER ID        IMAGE                      COMMAND             CREATED
 * 64040448833c        bigbrain/ubuntu20:latest   "/bin/bash"     4 hours ago
 * @endcode
 *
 * 2. Save the container as a Docker image using the following commands:
 * @code {.c}
 * build $ docker commit <CONTAINER ID> <IMAGE NAME:TAG>
 * for example:
 * build $ docker commit 64040448833c ubuntu:CNNGen
 * @endcode
 *
 * 3. To begin a container with the saved Docker image, use the following commands:
 * @code {.c}
 * build $ docker images
 * REPOSITORY          TAG                 IMAGE ID            CREATED            SIZE
 * ubuntu    		  cnngen             d94e16b302d1       18 minutes ago     4.21GB
 * build $ docker run –v /share_host:/share_docker –itd --name cnngen ubuntu:CNNGen
 * @endcode
 *
 * @note
 * - Because the container does not automatically save changes, changes must be saved manually.
 * - For common commands used with Docker, refer to the following section.
 *
 * @subsubsection dsub_code_build_set_com_doc 3.5.5 Common Docker Commands
 *
 * This section provides examples of commonly used Docker commands. For more
 * details about Docker usage, refer to https://www.docker.com/play-with-docker.
 *
 *  - Docker <b>pull</b>: pulls Docker images from DockerHub
 *    - Command
 * @code {.c}
 * Build $ docker pull <IMAGE NAME:TAG>
 * @endcode
 *    - Example
 * @code {.c}
 * Build $ docker pull ubuntu:latest
 * @endcode
 *
 *  - Docker <b>run</b>: starts a new container
 *    with an existing Docker image.
 *    - Command:
 * @code {.c}
 * Build $ docker pull <IMAGE NAME:TAG>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ docker pull ubuntu:latest
 * @endcode
 *    - Options description:
 * @code {.c}
 * -i option: run container in interactive mode.
 * -t option: assign a fake terminal for container.
 * -d option: run container in the background.
 * --name option: specify the Docker image.
 * @endcode
 *
 *  - Docker <b>exec</b>: executes an application in a container
 *    - Command:
 * @code {.c}
 * Build $ docker exec -it <CONTAINER NAME> <APPLICATION>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ docker exec -it Ubuntu /bin/bash
 * @endcode
 *    - Options description:
 * @code {.c}
 * -i option: run container in interactive mode.
 * -t option: assign a fake terminal for container
 * @endcode
 *
 *  - Docker <b>commit</b>: saves a container as a Docker image
 *    - Command:
 * @code {.c}
 * Build $ docker commit <CONTAINER ID> <IMAGE NAME:TAG>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ docker commit cb634ac9eb81 ubuntu:update
 * @endcode
 *    - Options description:
 * @code {.c}
 * -a option: add an author name of image.
 * -m option: add description of image.
 * -p option: pause the container when it is committing
 * @endcode
 *
 *  - Docker <b>images</b>: lists local Docker images
 * @code {.c}
 * Build $ docker commit <CONTAINER ID> <IMAGE NAME:TAG>
 * @endcode
 *
 *  - Docker <b>ps</b>: lists local containers
 * @code {.c}
 * Build $ docker ps (Active containers)
 * docker ps -a (All containers)
 * @endcode
 *
 *  - Docker <b>stop</b>: stops a container
 *    - Command:
 * @code {.c}
 * Build $ docker stop <CONTAINER ID>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ docker stop cb634ac9eb81Options Description
 * @endcode
 *
 *  - Docker <b>rm</b>: removes the Docker container
 *    - Command:
 * @code {.c}
 * Build $ docker rm <CONTAINER ID>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ docker rm cb634ac9eb81
 * @endcode
 *
 *  - Docker <b>rmi</b>: removes the local Docker container
 *    - Command:
 * @code {.c}
 * Build $ docker rmi <IMAGE ID>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ docker rmi ccc6e87d482b
 * @endcode
 *
 * @subsection sub_code_build_set_pod 3.6 Install the CV Toolchain on Podman
 *
 * Podman is an open source management tool for running Linux containers, which
 * is similar to and compatible with Docker. The advantage of Podman is that Podman
 * can run in rootless mode and daemonless mode. Normal users can use
 * Podman to deploy containers in Linux servers.
 *
 * The following sections describe how to install the CV toolchain on Podman.
 *
 * For more details about Podman, refer to https://podman.io/.
 *
 * @subsubsection dsub_code_build_set_ins_pod 3.6.1 Podman Installation
 *
 * Podman supports a variety of systems for Ubuntu OS.
 * Podman can be installed on both physical and virtual machines.
 *
 * Refer to the following steps, which are for Podman installation on
 * Focal 20.04. Note that it is only for reference as users might have
 * different system requirements for different Podman installations.
 *
 * 1. For Podman installation commands, refer to
 * https://podman.io/getting-started/installation.
 *
 * 2. Use the following command to verify the installation. If the
 *    subsequent messages appear, Podman is functioning correctly.
 *    @code {.c}
 *    build $ podman run hello-world
 *    Resolved "hello-world" as an alias (/etc/containers/registries.conf.d/000-shortnames.conf)
 *    Trying to pull docker.io/library/hello-world:latest...
 *    Getting image source signatures
 *    Copying blob b8dfde127a29 done
 *    Copying config d1165f2212 done
 *    Writing manifest to image destination
 *    Storing signatures
 *
 *    Hello from Docker!
 *    This message shows that your installation appears to be working correctly.
 *
 *    To generate this message, Docker took the following steps:
 *      1. The Docker client contacted the Docker daemon.
 *      2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
 *         (amd64)
 *      3. The Docker daemon created a new container from that image which runs the
 *         executable that produces the output you are currently reading.
 *      4. The Docker daemon streamed that output to the Docker client, which sent it
 *         to your terminal.
 *
 *    To try something more ambitious, you can run an Ubuntu container with:
 *      $ docker run -it ubuntu bash
 *
 *    Share images, automate workflows, and more with a free Docker ID:
 *      https://hub.docker.com/
 *
 *    For more examples and ideas, visit:
 *      https://docs.docker.com/get-started/
 *    @endcode
 *
 * Next, users can install the Ubuntu and CNNGen toolchains with Dockerfile file, as shown below.
 * If users used below Docker file to install the environment, please skip the steps in @ref dsub_code_build_set_ubu_pod.
 * @code {.c}
 * build $ podman build -t cv_tool_cpu . -f ./Docker_Files/Dockerfile_CNNGen_<full_version>_ubu2004_CPU
 * @endcode
 * For more details, refer to `readme.txt` in the CNNGen toolchain pacakge. Users can refer to the
 * following sections to install the program manually.
 *
 * @subsubsection dsub_code_build_set_ubu_pod 3.6.2 Install Ubuntu on Podman
 *
 * Podman supports various OSs and applications running in independent containers.
 * When a container begins, Podman automatically downloads the Docker image from
 * DockerHub (if it does not exist locally).
 *
 * To create an <b>Ubuntu 20.04</b> container:
 *
 * 1. Pull Ubuntu 20.04 Docker image using the following command:
 * @code {.c}
 * build $ podman pull ubuntu:focal
 * @endcode
 * @note
 *  - Podman supports many versions of Ubuntu. Users can find the corresponding
 *    commands for pulling images from https://hub.docker.com/_/ubuntu.
 *  - To run CNNGen, Ambarella recommends using Ubuntu 20.04.
 *
 * 2. List local images using the following command:
 * @code {.c}
 * build $ podman images
 * REPOSITORY                      TAG          IMAGE ID             CREATED            SIZE
 * docker.io/library/ubuntu       focal       81bcf752ac3d       6 days ago         65.5MB
 * @endcode
 *
 * 3. Create a new folder for sharing files between the build machine and the
 * container. Start a container, then run a terminal as root. Install sudo and
 * vim using the following commands:
 * @code {.c}
 * build $ mkdir share_host
 * build $ podman run -v <Full Path>/share_host:/share_podman -itd --name ubuntu ubuntu:focal
 * build $ podman exec -it ubuntu /bin/bash
 * root # apt-get update
 * root # apt-get install sudo vim make
 * @endcode
 * @note
 *  - The option "-v <Full Path>/share_host:/share_podman" specifies the shared folders.
 *    "/share_host" is in the build machine and requires a full path.
 *    "/share_podman" is in the container.
 *  - The option "--name ubuntu" specifies the name of container.
 *  - The parameter "ubuntu:focal" specifies the Docker image, which is pulled by step 1.
 *
 * 4. Add a user account, and add it to the "sudo" group using the following commands.
 * @code {.c}
 * root # useradd -d /home/podman -m podman
 * root # passwd podman
 * root # usermod -aG sudo podman
 * @endcode
 *
 * 5. Exit the terminal, and restart with a new user account:
 * @code {.c}
 * root # exit
 * build $ podman exec --user podman -it ubuntu /bin/bash
 * podman $
 * @endcode
 * @note
 *  - The option "--user podman" specifies the user name.
 *  - The usage above is an example; customers can use any name.
 *  - For more details about Podman usage, refer to Section
 *    @ref dsub_code_build_set_com_pod.
 *
 * @subsubsection dsub_code_build_set_cnn_pod 3.6.3 Install CNNGen on Podman
 *
 * This section describes how to install and set up the environment for
 * <b>CNNGen</b> in a <b>Podman</b> container.
 *
 * 1. Copy the toolchain package via the shared folders and locate it
 *    in the container. Install the toolchain using the following commands:
 * @code {.c}
 * podman $ cd Ubuntu-20.04
 * podman $ sudo chmod +x ubuntuToolChain-<version>.ubuntu-20.04
 * podman $ ./ubuntuToolChain-<version>.ubuntu-20.04
 * @endcode
 *
 * 2. Because the image is pulled from DockerHub, which does not include
 *    third-party tools, users should install the tools using the following command:
 * @code {.c}
 * podman $ sudo apt-get install libncurses5-dev
 * @endcode
 *
 * 3. Set the environment for CNNGen as follows:
 * @code {.c}
 * podman $ source /usr/local/amba-cv-tools-<version>.ubuntu-20.04/env/cv<*chip_name*>.env
 * @endcode
 *
 * @note
 * - If any of the following installations are unsuccessful, repeatedly run
 *   the installed script to ensure successful installation of all programs.
 * - For steps 2 and 3 in particular, various systems might require different
 *   components; if errors occur during installation, follow the error
 *   information and install the required components.
 * - For more information about CNNGen, refer to the <em>CNNGen Doxygen Document</em>
 *   in the CVflow CNNGen Samples package.
 *
 * @subsubsection dsub_code_build_set_con_pod 3.6.4 Close and Save a Container
 *
 * To close and save a container:
 *
 * 1. Exit and check the container ID using the following commands:
 * @code {.c}
 * podman $ exit
 * build $ podman ps
 * CONTAINER ID     IMAGE                              COMMAND    CREATED       STATUS
 * 2335bf51b43e  docker.io/library/ubuntu:bionic  /bin/bash  4 hours ago  Up
 * @endcode
 *
 * 2. Save the container as a Docker image using the following commands:
 * @code {.c}
 * build $ podman commit <CONTAINER ID> <IMAGE NAME:TAG>
 * for example:
 * build $ podman commit 2335bf51b43e ubuntu:CNNGen
 * @endcode
 *
 * 3. To initialize a container with the saved Podman image, use the following commands:
 * @code {.c}
 * build $ podman images
 * REPOSITORY                       TAG           IMAGE ID           CREATED             SIZE
 * Docker.io/library/ubuntu    CNNGen       0db979ef8578       3 hours ago        1.65GB
 * build $ podman run –v /share_host:/share_podman –itd --name cnngen ubuntu:CNNGen
 * @endcode
 *
 * @note
 *  - As Podman does not automatically save system modifications, users must save them manually.
 *  - For common commands in Podman, refer to Section @ref dsub_code_build_set_com_pod.
 *
 * @subsubsection dsub_code_build_set_com_pod 3.6.5 Common Podman Commands
 *
 * This section provides examples of commonly-used Podman commands. For more further
 * details about Podman usage, refer to http://docs.podman.io/en/latest/Commands.html.
 *  - Podman <b>Pull</b>: pulls Docker images from DockerHub
 *    - Command:
 * @code {.c}
 * Build $ podman pull <IMAGE NAME:TAG>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ podman pull ubuntu:latest
 * @endcode
 *
 *  - Podman <b>Run</b>: starts a new container with an existing Podman image
 *    - Command:
 * @code {.c}
 * Build $ podman run -itd --name <CONTAINER NAME> <IMAGE NAME>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ podman run -itd --name Ubuntu ubuntu:latest
 * @endcode
 *    - Options description:
 * @code {.c}
 * -i option: run container in interactive mode.
 * -t option: assign a fake terminal for container.
 * -d option: run container in the background.
 * --name option: specify the Docker image.
 * @endcode
 *
 *  - Podman <b>exec</b>: executes an application in a container
 *    - Command:
 * @code {.c}
 * Build $ podman exec -it <CONTAINER NAME> <APPLICATION>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ podman exec -it Ubuntu /bin/bash
 * @endcode
 *    - Options description:
 * @code {.c}
 * -i option: run container in interactive mode.
 * -t option: assign a fake terminal for container
 * @endcode
 *
 *  - Podman <b>commit</b>: saves a container as a Docker image
 *    - Command:
 * @code {.c}
 * Build $ podman commit <CONTAINER ID> <IMAGE NAME:TAG>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ podman commit cb634ac9eb81 ubuntu:update
 * @endcode
 *    - Options description:
 * @code {.c}
 * -a option: add an author name of image.
 * -m option: add description of image.
 * -p option: pause the container when it is committing
 * @endcode
 *
 *  - Podman <b>images</b>: lists local Docker images
 * @code {.c}
 * Build $ docker commit <CONTAINER ID> <IMAGE NAME:TAG>
 * @endcode
 *
 *  - Podman <b>ps</b>: lists local containers
 * @code {.c}
 * Build $ podman ps (Active containers)
 * podman ps -a (All containers)
 * @endcode
 *
 *  - Podman <b>stop</b>: stops a container
 *    - Command:
 * @code {.c}
 * Build $ podman stop <CONTAINER ID>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ podman stop cb634ac9eb81
 * @endcode
 *
 *  - Podman <b>rm</b>: removes local Podman containers
 *    - Command:
 * @code {.c}
 * Build $ podman rm <CONTAINER ID>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ podman rm cb634ac9eb81
 * @endcode
 *
 *  - Podman <b>rmi</b>: removes local images
 *    - Command:
 * @code {.c}
 * Build $ podman rmi <IMAGE ID>
 * @endcode
 *    - Example:
 * @code {.c}
 * Build $ podman rmi ccc6e87d482b
 * @endcode
 *
 * - - - -
 *
 * @section code_build_full_sdk 4. Build Full SDK Code
 *
 * This chapter includes the following sections:
 * <ul>
 * <li> Section @ref sub_code_build_full_down
 * <li> Section @ref sub_code_build_full_import
 * <li> Section @ref sub_code_build_full_build
 * <li> Section @ref sub_code_build_full_cus
 * <li> Section @ref sub_code_build_full_make
 * </ul>
 *
 * @subsection sub_code_build_full_down 4.1 Download the SDK Package
 *
 * To allow access to the Cooper SDK tarred files, Ambarella provides users
 * with a file transfer protocol (FTP) account and directions for logging in to the
 * Ambarella FTP server using an account password. Users should not modify the SDK
 * within the download directory. If users must modify the SDK, Ambarella
 * recommends making a copy of the SDK and using the copied version instead.
 *
 * The Ambarella Cooper Linux SDK code package includes:
 *  - <b>cooper_linux_sdk</b>: This SDK is the formal release and contains the reference
 * application, static / dynamic library files, private drivers, Linux kernel, and file system.
 *  - <b>Patches</b> (Optional): This part contains the patches to the formal package.
 *
 * Users can access an example (with no patches provided) using the Cooper SDK release
 * file cooper_linux_sdk_******.tar.xz.
 *
 * @subsection sub_code_build_full_import 4.2 Important SDK Folders
 *
 * The folders listed in this section include the locations of several important
 * components of the SDK. To learn more information about a component, refer to
 * the documents listed below.
 *
 *   - `ambarella/drv_modules/private/video/dsp_v6/iav`: includes all DSP-related
 *      application programming interface (API) codes used for the video process pipeline.
 *      Related Ambarella documentation includes the following:
 *     - Page @ref fd_adv_multi_vin "Multi-VIN Design"
 *     - <em>AMBA Flexible Linux SDK Document Doxygen</em>
 *
 *   - `ambarella/unit_test/private/iav_test`: this folder contains the demo applications
 *     for testing the DSP. Related Ambarella documentation includes the following:
 *     - Page @ref page_getting_start_guide "Getting Started Guide"
 *     - <em>AMBA Cooper Linux SDK Document Doxygen Feature Sets</em>
 *
 *   - `ambarella/drv_modules/private/cavalry`: this folder includes the Cavalry-related
 *     API codes used for convolutional neural network (CNN) network cases. Related Ambarella
 *     documentation is in the <em>SDK Doxygen document of the SDK package</em>.
 *
 *   - `ambarella/packages/vproc`: this folder includes the VProc code used to prepare the
 *     network input frame. Related Ambarella documentation is in the <em>SDK Doxygen document
 *     of the SDK package</em>.
 *
 *   - `ambarella/packages/nnctrl`: this folder includes the NNCtrl code used to load the
 *     Cavalry binary converted by the CNNGen tool. Related Ambarella documentation is
 *     in the <em>SDK Doxygen document of the SDK package</em>.
 *
 *   - `ambarella/packages/cavalry_mem`: this folder includes the Cavalry memory code
 *     used to allocate memory for Cavalry cases. Related Ambarella documentation
 *     is in the <em>SDK Doxygen document of the SDK package</em>. This folder uses APIs found in
 *     the continuous memory allocator (CMA) function.
 *
 *   - `ambarella/unit_test/private/cv_test`: this folder includes the demo application
 *     for testing CVflow® applications. Related Ambarella documentation includes
 *     - Page @ref page_getting_start_guide "Getting Started Guide"
 *     - <em>Doxygen document of CNNGen Samples package</em>
 *
 *   - `ambarella/prebuild/library/idsp`: this folder contains relevant information
 *     about the image process library. For more details, refer to Page
 *     @ref page_lib_img_doc "Image Library API"
 *
 *   - `ambarella/packages/security`: this folder includes all of the codes related
 *     to security functions. Related Ambarella documentation includes <em>Ambarella
 *     CV5x DG Flexible Linux SDK Security Features</em>.
 *
 *   - `ambarella/prebuild/ambarella/library/dewarp`: this folder includes the
 *     prebuild library for dewarp. Related Ambarella documentation includes
 *     - Page @ref page_lib_dewarp_doc "Dewarp Library API"
 *     - <em>AMBA Cooper Linux SDK Document Doxygen Feature Sets</em>
 *
 *   - `ambarella/prebuild/library/eis`: this folder holds the electronic image
 *     stabilization (EIS) prebuild library. For more details, refer to Page
 *     @ref page_lib_eis_doc "EIS Library API".
 *
 *   - `ambarella/drv_modules/private/video/dsp_v6/ambcma`: this folder contains all of
 *     the information about the CMA function. For more details, refer to
 *     Page @ref page_drv_cma_doc "CMA Driver API".
 *
 * @subsection sub_code_build_full_build 4.3 Build Firmware
 *
 * Follow the steps below to build the flexible Linux SDK.
 *
 * 1. Extract the SDK package `cooper_linux_sdk_xxxxxx.tar.xz`.
 * @code {.c}
 * build $ tar xvfJp cooper_linux_sdk_********.tar.xz
 * build $ cd cooper_linux_sdk_*
 * @endcode
 *
 * 2. Configure the <b>Arm® Toolchain</b> under `ambarella/`.
 * - amba-build
 * @code {.c}
 * build $ cd ambarella
 * build $ source build/env/amba-build.env
 * @endcode
 * - yocto-build
 * @code {.c}
 * build $ cd ambarella
 * build $ source build/env/yocto-build.env
 * @endcode
 *
 * 3. Configure the image under `boards/<board_type>`.
 *  - For example, to build the CV5x /CV7x IP camera firmware, use the following commands:
 * @code {.c}
 * build $ cd boards/<board_type>
 * build $ ls -al config/amba/
 * (Or build $ ls -al config/yocto/)
 * build $ make ipcam_config
 * build $ make
 * @endcode
 *  - Refer to Section @ref sub_code_build_full_cus for details on how to customize the
 *    compile configuration.
 *
 * 4. Build the firmware.
 * @code {.c}
 * build $ make
 * @endcode
 * If the build system has multi-core CPUs, use the "-jN" option to reduce the building
 * time. Users can use the command <b>"nproc"</b> to get the number of CPU cores. For example,
 * if using eight-core CPUs, use the following command:
 * @code {.c}
 * build $ make -j8
 * @endcode
 *
 * 5. After the building process is complete, the image is located at:
 * @code {.c}
 * ../../<build_type>_out/<board_type>/firmware/bst_bld_*_kernel_*_release.bin.
 * @endcode
 * For example, the built firmware for CV5x IP camera EVK board is located at:
 * @code {.c}
 * ../../<build_type>_out/cv5x_<board_name>/firmware/bst_bld_kernel_lnx_release.bin (or bst_bld_atf_kernel_lnx_release.bin).
 * @endcode
 * And the built firmware for CV7x IP camera EVK board is located at:
 * @code {.c}
 * ../../<build_type>_out/cv7x_<board_name>/firmware/bst_bld_env_dtb_kernel_rootfs_release.bin.
 * @endcode
 *
 * 6. Upgrade the image to the board. Refer to Chapter
 * @ref code_build_upgrade "7. Upgrade the Firmware to the Development Platform".
 *
 * @subsection sub_code_build_full_cus 4.4 Customize the Build Configuration
 *
 * @subsubsection dsub_code_build_full_amba 4.4.1 Modify the Ambarella Add-Ons Configuration
 *
 * To remove the Ambarella add-on libraries, drivers, or applications, follow these steps:
 *
 * 1. Go to ambarella/boards/<board_type> folder.
 * @code {.c}
 * build $ cd ambarella/boards/cv5x_<board_name>
 * (Or build $ cd ambarella/boards/cv7x_<board_name>)
 * @endcode
 *
 * 2. Clean the previous target template.
 * @code
 * build $ make clean
 * @endcode
 *
 * 3. Apply the default Ambarella configuration or chip-related configuration files.
 * The different configuration files for various chips and the build binary show
 * different clock frequencies and performances.
 * @code {.c}
 * build $ ls -al config/amba/
 * build $ make ipcam_config
 * @endcode
 *
 * 4. Display and modify the kernel configuration according to the product requirement.
 * @code {.c}
 * build $ make menuconfig
 * @endcode
 *
 * 5. Rebuild the firmware. See Section @ref sub_code_build_full_make
 *    for details on compiling specific targets.
 * @code {.c}
 * build $ make -j8
 * @endcode
 *
 * @subsubsection dsub_code_build_full_linux 4.4.2 Modify the Linux Kernel Configuration
 *
 * To modify the Linux kernel configuration, follow these steps:
 *
 * 1. Go to `ambarella/boards/<board_type>` folder.
 * @code {.c}
 * build $ cd ambarella/boards/cv5x_<board_name>
 * (Or build $ cd ambarella/boards/cv7x_<board_name>)
 * @endcode
 *
 * 2. Clean up the old target template.
 * @code {.c}
 * build $ make clean
 * @endcode
 *
 * 3. Apply the default kernel configuration.
 * @code {.c}
 * build $ make linux_defconfig
 * @endcode
 *
 * 4. Display and modify the kernel configuration according to the requirements.
 * @code {.c}
 * build $ make linux_menuconfig
 * @endcode
 *
 * 5. Create the specific kernel configuration. Below example is with amba-build method.
 * @code {.c}
 * build $ mkdir config/kernel
 * build $ cp -dpRf ../../amba_out/cv5x_<board_name>/kernel/linux-5.15_cv5x/.config config/kernel/ambarella_xxx_config
 * (Or build $ cp -dpRf ../../amba_out/cv7x_<board_name>/kernel/linux-5.15_cv7x/.config config/kernel/ambarella_xxx_config)
 * build $ make menuconfig
 *     kernel  --->
 *         [*] linux (kernel)  --->
 *             (ambarella_xxx_config) Linux Default Configuration
 * @endcode
 *
 * 6. Rebuild the firmware.
 * @code {.c}
 * build $ make -j8
 * @endcode
 *
 * @subsection sub_code_build_full_make 4.5 Make Target Options
 *
 * The make commands are as follows:
 * <table>
 * <caption id="code_build_make_command">Table 4-1. Building Commands.</caption>
 * <tr><th> Command                <th> Content
 * <tr><td> make <Tab> <Tab>       <td> Lists the supported targets
 * <tr><td>make <Target>           <td> Compiles a specific target
 * <tr><td>make -jN                <td> Builds with the multi-core CPUs
 * </table>
 *
 * The following target options are examples of the most commonly used targets:
 * <table>
 * <caption id="code_build_make_targets">Table 4-2. Building Targets.</caption>
 * <tr><th> Command                                <th> Target
 * <tr><td> make linux_defconfig                   <td> Apply the default kernel configuration
 * <tr><td> make linux_menuconfig                  <td> Display the kernel menuconfig
 * <tr><td> make menuconfig                        <td> Display the menuconfig
 * <tr><td> make boot                              <td> Build AMBoot
 * <tr><td> make linux                             <td> Build the Linux kernel
 * <tr><td> make kernel-module-ambvideo            <td> Build the private video drivers
 * <tr><td> make clean kernel-module-ambvideo      <td> Clean the private video drivers
 * <tr><td> make clean                             <td> Delete the directory
 * <tr><td> make distclean                         <td> Delete all temporary objects in compilation
 * <tr><td> make iav-test                          <td> Compile the IAV unit test tools, such as test_encode
 * <tr><td> make idsp-test                         <td> Compile the IDSP unit test toos, such as test_aaa_service
 * <tr><td> make lwmedia-test                      <td> Compile the media test tools, such as rtsp_server
 * <tr><td> make libimgflow                        <td> Compile the library libimgflow.so
 * </table>
 *
 * - - - -
 *
 * @section code_build_eva_sdk 5. Build Evaluation SDK Code
 *
 * This chapter includes the following sections:
 * <ul>
 * <li> Section @ref sub_code_build_eva_down
 * <li> Section @ref sub_code_build_eva_build
 * <li> Section @ref sub_code_build_eva_run
 * </ul>
 *
 * @subsection sub_code_build_eva_down 5.1 Download SDK Package
 *
 * To enable access to the Cooper SDK tarred files, Ambarella provides users with
 * an FTP account and directions for logging in to the Ambarella FTP server using
 * an account password. Users should not modify the SDK within the download directory.
 * If users must modify the SDK, Ambarella recommends making a copy of the SDK and using
 * the copied version instead.
 *
 * The Ambarella Cooper Linux SDK evaluation code package includes:
 *
 *  - <b>cooper_linux_evaluation_sdk</b>: This SDK is the formal release and contains
 *    all reference applications, the static / dynamic library files, and the header files.
 *
 * @subsection sub_code_build_eva_build 5.2 Build Application
 *
 * To build the application, follow the steps below:
 *
 * 1. Extract the formal SDK package `cooper_linux_evaluation_sdk__xxxxxx.tar.xz`.
 * @code {.c}
 * build $ tar xvfJp cooper_linux_evaluation_sdk_********.tar.xz
 * build $ cd cooper_linux_evaluation_sdk_*
 * @endcode
 *
 * 2. Configure the Arm® Toolchain.
 * - amba-build
 * @code {.c}
 * build $ cd ambarella
 * build $ source build/env/amba-build.env
 * @endcode
 *
 * 3. Configure the image under `boards/<board_type>`.
 * - For Cooper Amba build:
 * @code {.c}
 * build $ cd boards/<board_name>
 * build $ make ipcam_config
 * build $ make menuconfig
 *     drv_modules  --->
 *          private  --->
 *           -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *               (4)   Max VIN Channel Number
 * build $ make <app_name>
 * @endcode
 *
 * 4. Upload the application and files to board as this package has no Linux
 *    kernel or file system. The application can be found in
 *    `ambarella/amba_out/cv5x_<board_name>/sysroot/usr/local/bin/<app_name>` or
 *    `ambarella/amba_out/cv7x_<board_name>/sysroot/usr/local/bin/<app_name>`.
 *
 * @subsection sub_code_build_eva_run 5.3 Run Application
 *
 * For more information about running the application, refer to the page
 * @ref page_getting_start_guide "Getting Started Guide".
 *
 * - - - -
 *
 * @section code_build_setup_pc 6. Set Up the PC
 *
 * The <b>SSH</b> and <b>Telnet</b> tools are used to access the build machine and
 * the development platform. <b>AmbaUSB</b> is used to upgrade the firmware to
 * the development platform from the PC.
 *
 * This chapter includes the following sections:
 * <ul>
 * <li> Section @ref sub_code_build_pc_con
 * <li> Section @ref sub_code_build_pc_up
 * <li> Section @ref sub_code_build_pc_linux
 * <li> Section @ref sub_code_build_pc_cifs
 * <li> Section @ref sub_code_build_pc_nfs
 * </ul>
 *
 * @subsection sub_code_build_pc_con 6.1 Connect to a Console Window - PuTTY
 *
 * Ambarella recommends using the <b>SSH</b> and Telnet tool <b>PuTTY</b> from
 * http://www.PuTTY.org to connect to a console window. The <b>PuTTY</b> executable
 * and source code is distributed under the Massachusetts Institute of Technology
 * (MIT) license.
 *
 * To connect to a console window, use the RS232 serial cable included with the SDK.
 * If the cable is not available, use a female-to-female RS232 receiver /
 * transmitter (RX / TX) crossover cable instead.
 *
 * 1. Run <b>putty.exe</b>. For a serial connection, configure PuTTY as follows
 * and as shown in the following figures:
 *    - Speed (baud rate in bits per second):  <b>115200</b>
 *    - Data Bits:                             <b>8</b>
 *    - Parity:                                <b>None</b>
 *    - Stop Bits:                             <b>1</b>
 *    - Flow Control:                          <b>None</b>
 *
 * @image html getting_guide_serial_conf_1.png "Figure 6-1. PuTTY Serial Configuration (1)."
 *
 * 2. From the PuTTY Configuration dialog, choose <b>Category > Connection > Serial</b>
 *    and for <b>Serial line to Connect To</b>, enter the correct port (for example, COM1). For <b>Speed,
 *    Data Bits, Parity, Stop Bits, and Flow Control</b>, use the settings above.
 *
 * 3. From <b>Category > Session</b> in the PuTTY Configuration dialog, choose <b>Serial</b> for
 *   <b>Connection Type</b>. Set <b>Serial Line</b> to <b>COM1</b> and <b>Speed</b> to <b>115200</b>.
 *   Save the current session (for example, Amba Serial in Figure 6-2), so that it can be reused.
 * @image html getting_guide_serial_conf_2.png "Figure 6-2. PuTTY Serial Configuration (2)."
 *
 * @subsection sub_code_build_pc_up 6.2 Upgrade Firmware - AmbaUSB
 *
 * <b>AmbaUSB</b> is the tool which enables users to upgrade the platform on the <b>Ubuntu</b>
 * / Windows PC through the USB. The installation programs can be found in the
 * folder `Tools/AmbaUSB`, and include 32-bit and 64-bit PC versions.
 *
 * <b>OS Requirement</b>:  18.04 LTS / 20.04 LTS, Windows 7 32-bit / 64-bit
 *
 * Select the appropriate OS and double-click the program to begin installation.
 *
 * @subsection sub_code_build_pc_linux 6.3 Linux Virtual Machine
 *
 * Ambarella recommends installing the Linux virtual machine on the Windows PC to
 * enable direct access to the Linux development platform. For more details on setting
 * up network sharing between the build machine, a Windows PC, and the development
 * platform, see Section @ref sub_code_build_pc_cifs.
 *
 * This section provides instructions to install Ubuntu on Windows using
 * virtualization software, such as VirtualBox. <b>VirtualBox</b> is freely available
 * and recommended by Ambarella.
 *
 * The following instructions use VirtualBox to install Ubuntu on Windows.
 *
 * 1. Obtain the VirtualBox and Ubuntu 20.04 LTS disk images.
 *    - VirtualBox downloading page: https://www.virtualbox.org/wiki/Downloads
 *    - Ubuntu 20.04 LTS: http://www.ubuntu.com/download/ubuntu/download
 *
 * 2. Create a virtual machine.
 *    - After launching VirtualBox, click <b>New</b> to create a new virtual machine (VM).
 *     @image html code_build_vm_new.png "Figure 6-3. Create a New VM."
 *    - VM Name and OS Type
 *       - <b>Name</b>:             (whatever the developer likes)
 *       - <b>Operating System</b>: Linux
 *       - <b>Version</b>:          Ubuntu
 *    @image html code_build_vm_name_os.png "Figure 6-4. VM Name and OS Type."
 *    - Memory
 *       - If the RAM on the machine used for development is less than 1 GB,
 *         Ambarella recommends using VirtualBox. Note that if the RAM exceeds
 *         1 GB, only a quarter of RAM will be accessed.
 *    @image html code_build_vm_ram.png "Figure 6-5. Memory Size."
 *    - Virtual hard disk (VHD)
 *       - Select <b>Create a new hard disk</b>, click <b>Create</b>, choose
 *         <b>VHD</b>, and then click <b>Next</b>.
 *    @image html code_build_vm_vhd.png "Figure 6-6. Hard Disk File Type."
 *    - Hard disk storage type
 *       - Both <b>dynamically expanding storage</b> and <b>fixed-size storage</b> can be used.
 *    @image html code_build_vm_storage.png "Figure 6-7. Storage on Physical Hard Disk."
 *    - Virtual disk location and size
 *       - Using the default values is acceptable: more than <b>40 GB</b> is suggested
 *    @image html code_build_vm_loc_size.png "Figure 6-8. File Location and Size."
 *
 * 3. Configure the virtual machine.
 *    - Click <b>Settings > Storage > Empty</b> under the Controller: IDE. Next to
 *      the <b>Optical Drive</b>, click <b>Browse</b> and <b>Choose a disk
 *      file ...</b>.Select the Ubuntu.iso downloaded by the user. Click <b>OK</b>.
 *    @image html code_build_vm_ubn_iso.png "Figure 6-9. Choose a Disk File."
 *    - If a PC comes equipped with two network interface controllers (NICs), one connected to the Internet and
 *      other to the platform, use the <b>Oracle VM VirtualBox Manager</b>, select
 *      the virtual machine, and click Settings > Network.
 *    - Within <b>Adapter 1</b>, select <b>Enable Network Adapter</b>.
 *       - Attached to: <b>Bridged</b> Adapter
 *       - Name: (NIC that is connected to the Internet)
 *    @image html code_build_vm_net_adap_1.png "Figure 6-10. Configuaration of Adapter 1."
 *    - Within <b>Adapter 2</b>, select <b>Enable Network Adapter</b>.
 *       - Attached to:  <b>Bridged</b> Adapter
 *       - Name:  (NIC that is connected to the development board)
 *     @image html code_build_vm_net_adap_2.png "Figure 6-11. Configuaration of Adapter 2."
 *
 * 4. Install Ubuntu on the virtual machine.
 *    - Start the virtual machine.  After Ubuntu loads, select <b>Install Ubuntu</b>.
 *    @image html code_build_vm_install_ubun.png "Figure 6-12. Install Ubuntu."
 *    - When the installation finishes, shut down the virtual machine. Click
 *      <b>Settings > Storage > .iso</b> (Ubuntu disk image). Then, click the <b>Browse</b> button beside
 *      <b>Optical Drive</b> and <b>Remove disk from virtual drive</b>. The entry field will clear
 *      its contents.
 *    @image html code_build_vm_rm_iso.png "Figure 6-13. Remove Disk from Virtual Drive."
 *
 * 5. Install guest additions.
 *   VirtualBox Guest Additions improves mouse integration, screen resolution options,
 *   and other features for the guest operation system.
 *    - Click <b>Settings > Storage > Empty</b> under the <b>Controller: IDE</b>. Click
 *      the browse button beside <b>Optical Drive</b> and <b>Choose a virtual CD / DVD
 *      file</b>. Browse the file for <b>VBoxGuestAdditions.iso</b> (this can usually
 *      be found under C:\Program Files \Oracle\VirtualBox). Click <b>OK</b> to continue.
 *    @image html code_build_vm_vbox_gst.png "Figure 6-14. Install VirtualBox Guest Additions."
 *    - Start the virtual machine and change to the directory where the CD-ROM is mounted.
 *      For example: /media.
 * @code {.c}
 * host $ sudo ./VBoxLinuxAdditions.run
 * @endcode
 *
 * @note
 * If it is necessary to attach a USB device, such as AmbaUSB, to the virtual machine,
 * ensure that the USB port is USB 2.0 to avoid the following error message, as shown below.
 *   @code {.c}
 * Failed to attach the USB device xxxx to the virtual machine xxxxx. USB device xxxx with
 * UUID {xxxxxx} is busy with a previous request. Please try again later.
 * @endcode
 *
 * @subsection sub_code_build_pc_cifs 6.4 Network Sharing: CIFS
 *
 * See Section @ref sub_code_build_req_net for details on setting up the network
 * topology for sharing the building machine.
 *
 * @subsubsection dsub_code_build_pc_linux 6.4.1 Access Linux Folders from the Development Platform
 *
 * The following figure illustrates how common internet file systems (CIFS) accesses Linux
 * folders from the development platform.
 * @image html code_build_cifs_linux.png "Figure 6-15. CIFS Between Linux."
 *
 * To enable access of Linux folders from the development platform, perform the following steps:
 *
 * <b>On the host Linux PC:</b>
 *
 * 1. Install <b>Samba</b> and <b>CIFS</b> on the host Linux PC.
 * @code {.c}
 * host $ sudo apt-get install samba cifs-utils
 * @endcode
 *
 * 2. Create the folder on the host machine that will be shared.
 * @code {.c}
 * host $ mkdir /home/linux_share
 * host $ cd /home/linux_share && touch abc.txt
 * @endcode
 *
 * 3. Modify the <b>Samba</b> configuration file. Add "security=user" to the configuration
 * if the Linux kernel version of the development platform is equal to or later than 3.8.
 * @code {.c}
 * host $ sudo vim /etc/samba/smb.conf
 *
 * security = user
 *
 * [linux_share]
 *       path = /home/linux_share
 *       writable = yes
 *       valid users = myusername
 * @endcode
 *
 * 4. Restart the <b>Samba</b> service on the host PC.
 * @code {.c}
 * host $ sudo service smbd restart
 * @endcode
 *
 * <b>On the development platform:</b>
 *
 * 1. Attach the Linux folder to `/mnt` on the development platform.
 * @code {.c}
 * board # mount –t cifs –o user=myusername,password=mypassword,sec=ntlm  //10.0.0.3/linux_share /mnt
 * board # ls /mnt
 * abc.txt
 * @endcode
 *
 * 2. To detach the Linux folder, use the following command:
 * @code {.c}
 * board # umount /mnt
 * @endcode
 *
 * @subsubsection dsub_code_build_pc_win 6.4.2 Access Windows Folders from the Development Platform
 *
 * The following figure illustrates how CIFS accesses Windows folders from
 * the development platform.
 * @image html code_build_cifs_win_linux.png "Figure 6-16. CIFS between Windows and Linux."
 *
 * To enable access of Windows folders from the development platform, perform the
 * following steps:
 *
 * <b>On the Windows PC:</b>
 *
 * 1. Set up the security options for the network connection. (Assume that the
 * connection between the PC and the platform is on a public network.)
 *
 * 2. Go to <b>Control Panel > Network and Internet > Choose homegroup and
 * sharing options > Change advanced Sharing setting… > Public</b>.
 *   - Network Discovery:  		Turn on network discovery
 *   - File and printer sharing:  	Turn on
 *   - Public folder sharing:  		Developer's choice, acceptable to have it on or off
 *
 * 3. Set up the folder you want share on Windows 10. Right click the folder ->
 * <b>chose "Properties" menu -> click "Sharing" tab -> click "Advanced Sharing…"
 * -> check "share this folder" box</b> -> enter a share name. The following
 * figure provides an example of the share folder setting.
 * @image html code_build_share_win_host.png "Figure 6-17. Share Folder Settings of Windows Host PC."
 *
 * <b>On the development platform:</b>
 *
 * 1. Here, the username is the Windows user name, and the password is for the
 * Windows user account.
 * @code {.c}
 * board # mount -t cifs  -o  domain=ambarella,sec=ntlmssp,username=xxx,password=xxxxxx,uid=0,gid=0,file_mode=0755,dir_mode=0755  //10.0.0.1/myshare  /mnt
 * board # ls /mnt
 * this_is_a_share_file
 * @endcode
 *
 * 2. To detach the Linux folder, use the following command:
 * @code {.c}
 * baord # umount /mnt
 * @endcode
 *
 * @subsubsection dsub_code_build_pc_fold 6.4.3 Access the Folder on the Building Machine from the Development Platform
 *
 * Users can compile the application on the building machine and run it directly
 * on the development platform without burning the binary; this benefits the
 * driver and the debug process for the applications.
 *
 * The following figure shows an example of the CIFS process.
 * @image html code_build_cifs_example.png "Figure 6-18. CIFS Example."
 *
 * To enable access of the folders on the building machine from the development
 * platform, enter the following commands and perform the following steps:
 *
 * <b>On the building workstation:</b>
 * @code {.c}
 * build $ sudo apt-get install samba cifs-utils
 * build $ mkdir –p /home/build_share
 * build $ sudo vim /etc/samba/smb.conf
 * <A simple example>
 * [build_share]
 *        path = /home/build_share
 *       writable = yes
 *       valid users = mybuildusername
 * build $ sudo service smbd restart
 * @endcode
 *
 * <b>On the Linux PC:</b>
 *
 * @code {.c}
 * host $ sudo apt-get install samba cifs-utils
 * host $ mkdir -p /home/linux_share
 * host $ sudo vim /etc/fstab
 * @endcode
 *
 * 1. Add the following line (all in one line) in `/etc/fstab`:
 *  `//10.4.8.155/build_share /home/linux_share cifs username=mydomain\mybuildusername,
 * password=mybuildpasswd`
 * @code {.c}
 * host $ sudo mount -a
 * host $ sudo vim /etc/samba/smb.conf
 * <A simple example>
 * security = user
 * [linux_share]
 *        path = /home/linux_share
 *        writable = yes
 *        valid users = myhostname
 * host $ sudo service smbd restart
 * @endcode
 *
 * 2. On the development board, run the following command.
 * @code {.c}
 * board # mkdir -p /mnt/build_share
 * board # mount -t cifs //10.0.0.3/linux_share /mnt/shares -o user=myhostname, password=myhostpasswd
 * @endcode
 *
 * 3. If the above configurations are successful, build_share can be accessed from
 * the development platform as shown in the following:
 * @code {.c}
 * build $ cd /home/build_share
 * build $ touch abc.txt
 * board # ls /mnt/shares
 * abc.txt
 * @endcode
 *
 * 4. To remove the shares, type the following command:
 * @code {.c}
 * board # umount /mnt/shares
 * @endcode
 *
 * @subsection sub_code_build_pc_evk_nfs 6.5 Network Sharing: NFS
 *
 * The network file system (NFS) is a protocol that enables users on a client
 * computer to access files over a network. If the PC that connects to the
 * development platform includes an NFS server, then the platform can access
 * the PC's hard drive through the network.
 *
 * This section includes procedures for setting up the system with NFS to
 * enable users to access files over a network. The following figure shows an example of the NFS process.
 * @image html code_build_nfs_example.png "Figure 6-19. NFS Example."
 *
 * For more information on setting up the NFS, go to the official web
 * site: http://tldp.org/HOWTO/NFS-HOWTO/.
 *
 * @subsubsection sub_code_build_pc_nfs_server 6.5.1 Setting Up an NFS Server on a Linux PC
 *
 * To set up an NFS server on a linux PC, perform the following steps:
 *
 * 1. Install the NFS server on the Linux PC.
 * @code {.c}
 * host $ sudo apt-get install nfs-kernel-server
 * @endcode
 *
 * 2. Set the NFS server's configuration and start the server.
 * @code {.c}
 * host $ mkdir -p /home/linux_share
 * host $ sudo vim /etc/exports
 * host $ sudo echo "/home/linux_share 10.0.0.2(rw,root_squash)" > /etc/exports
 * host $ sudo /etc/init.d/nfs-kernel-server restart
 * @endcode
 *
 * @subsubsection sub_code_build_evk_nfs_cs 6.5.2 Setting Up the NFS Client and Server on a Development Platform
 *
 * To set up an NFS server on a development platform, perform the following steps:
 *
 * 1. Select `NFS utils` and `rpcbind` in the rootfs and select the kernel NFS support.
 * - For Cooper Amba build
 * @code {.c}
 * build $ make ipcam_config
 * build $ make menuconfig
 *       prebuild  --->
 *              oss  --->
 *                 [*] prebuild-nfs-utils (prebuild/oss/armv8-a/nfs-utils)  --->
 *
 * build $ make menuconfig_public_linux
 *           File systems >
 *             [*] Network File Systems >
 *                <*>   NFS client support
 *                <*>     NFS client support for NFS version 3
 *                <*>   NFS server support
 *                [*]     NFS server support for NFS version 3
 * @endcode
 *
 * 2. Set the directory for NFS sharing in `/etc/exports` When the platform boots up.
 * @code {.c}
 * board # mkdir /nfs
 * board # echo "/nfs *(rw,sync,fsid=0,no_root_squash,no_subtree_check)" > /etc/exports
 * board # chmod 777 /nfs
 * @endcode
 * @note
 *   - Because UBIFS cannot support NFS, users cannot export UBIFS file-systems via NFS.
 *   - If UBIFS is used, the NFS share folder can be set in tmpfs(/tmp/nfs),
 *     VFAT (/sdcard/mmcblk0p1/nfs), or other file-systems.
 *
 * 3. Set the NFS ports and the rpcbind ports in `/etc/services`.
 * @code {.c}
 * nfs     2049/tcp        nfsd
 * nfs     2049/udp        nfsd
 * sunrpc  111/tcp         rpcbind portmap
 * sunrpc  111/udp         rpcbind portmap
 * @endcode
 *
 * 4. Check if NFS and NFSD are supported by the kernel.
 * @code {.c}
 * board # cat /proc/filesystems | grep nfs
 * nodev   nfs
 * nodev   nfsd
 * @endcode
 * @note
 *   - `nodev nfs` is for the NFS client.
 *   - `nodev nfsd` is for the NFS server.
 *
 * 5. Start the NFS server.
 *   - If the system is started with `systemd`, the following commands can be used:
 * @code {.c}
 * systemctl start nfs-server.service
 * @endcode
 *   - If the system is started with `linuxrc`, the following commands can be used:
 * @code {.c}
 * board # rpcbind
 * board # rpc.statd --no-notify
 * board # rpc.nfsd
 * board # rpc.mountd
 * board # exportfs -rv
 * @endcode
 *
 *   @note
 *     - If the NFS server share folder is already created and `/etc/exports` is set
 *       properly before compiling, there is no need to start or restart the NFS server manully
 *       when `CONFIG_AMBARELLA_NFS_SERVER_AUTO_START` is selected in menuconfig.
 *
 * 6. Mount to the NFS server share folder from the NFS client platform.
 *   - <b>Temporary Mount</b>
 *     - After each reboot of the development platform, type the following commands:
 * @code {.c}
 * board # mkdir -p /mnt/shares
 * board # mount -t nfs -o nolock <NFS_SERVER_IP>:/nfs /mnt/shares
 * @endcode
 *     - <NFS_SERVER_IP> is the IP address of the NFS server.
 *
 *   - <b>Permanent Mount</b>
 *     - When the platform boots up, the NFS mounts automatically. (Note that NFS server
 *       on the other platform should be functioning before this platform boots up.)
 * @code {.c}
 * build $ make <platform>_ipcam_config
 * build $ make menuconfig
 *           Ambarella File System Configuration >
 *             ()Mount configuration for /mnt >
 *               <NFS_SERVER_IP>:/nfs /mnt/shares nfs defaults,nolock 0 0
 * @endcode
 *     - <NFS_SERVER_IP> is the IP address of the Linux PC.
 *
 *
 * 7. Share files between the NFS server and the NFS client.
 *   If the configurations listed in the previous steps are successful, the NFS server share folder `/nfs`
 *   can be accessed from the development platform. The following commands show the sharing processes:
 *   - NFS server:
 * @code {.c}
 * board # $ cd /nfs
 * board $ touch abcd.txt
 * @endcode
 *   - NFS client:
 * @code {.c}
 * board # ls /mnt/shares
 * abcd.txt
 * board # $ cd /mnt/shares
 * board $ touch 1234.txt
 * @endcode
 *   - NFS server:
 * @code {.c}
 * board # ls /nfs
 * abcd.txt 1234.txt
 * @endcode
 *
 * 8. Remove the client shares using the following command:
 * @code {.c}
 * board # umount /mnt/shares
 * @endcode
 *
 * 9. Stop the NFS server.
 *   - If the system is started with `systemd`, the following commands can be used:
 * @code {.c}
 * systemctl stop nfs-server.service
 * @endcode
 *   - If the system is started with `linuxrc`, the following commands can be used:
 * @code {.c}
 * board # rpc.nfsd 0
 * board # killall rpc.mountd
 * board # exportfs -rv
 * board # exportfs -f
 * board # killall rpc.statd
 * board # killall rpcbind
 * @endcode
 *
 *
 * - - - -
 *
 * @section code_build_upgrade 7. Upgrade the Firmware to the Development Platform
 *
 * For more details on installing the firmware through <b>AmbaUSB</b> on <b>Linux</b>
 * or <b>Windows</b>, refer to Chapter @ref getting_guide_upgrade_firmware "7. Upgrading the Firmware".
 *
 * - - - -
 *
 * @section code_build_oss 8. Build OSS Libraries
 * Cross-compiled open source software (OSS) libraries prepared by Ambarella are included in the SDK.
 *
 * The pre-built libraries can be used directly by Amba build. Users can request
 * the RPM and SRPM packages from Ambarella, which are separate and not included
 * the standard Linux SDK, if cross-compiling the libraries themselves.
 *
 * Below are the available source RPM packages.
 * | Date     | Source Package Name                      |
 * | :---     | :--------------------------------------- |
 * | 20210419 | ambarella-oss-src-20210419.tar.bz2       |
 * | 20220215 | ambarella-oss-src-srpms-20220215.tar     |
 * | 20220719 | ambarella-oss-src-srpms-20220719.tar.xz  |
 * | 20230308 | ambarella-oss-src-srpms-20230308.tar.xz  |
 *
 * Below are the reference steps.
 * @code
 * 1. Prepare the host PC
 * 1.1 Install CentOS7
 * 1.2 Install EPEL release for better software support.
 * 	host $ sudo yum install epel-release
 * 1.3 Install new package software dnf
 * 	host $ sudo yum install dnf
 * 1.4 update the system to the latest
 * 	host $ sudo dnf update
 *
 * 2. Build the src rpm package
 * 2.1 Extract the tool chain
 * 2.2 Add the toolchain path into PATH.
 * 2.3 Install the aarch64-filesystem.rpm in the rpms folder
 * 	host $ sudo dnf install ./aarch64-filesystem-18-el7.rpm
 * 2.4 Rebuild the target src.rpm. Take bzip2 as example:
 * 	host $ rpmbuild --rebuild aarch64-bzip2-1.0.8-1.amba.src.rpm
 *     The target rpm is under the folder: rpmbuild/RPMS/
 *     If the package has dependencies, the dependency rpm packages need to be built first, then install them by command.
 * 	host $ rpmbuild --rebuild aarch64-xxx-xxx.src.rpm
 * 	host $ sudo dnf install aarch64-xxx-xxx-xxx.rpm
 *
 *     After resolving all the dependency, use below command to build the package.
 * 	host $ rpmbuild --rebuild aarch64-xxx-xxx.src.rpm
 * @endcode
 *
 * @note
 * - Ambarella collects the source codes from the community.
 *   Ambarella does not change any code for the OSS libraries.
 * - The toolchain version used by Ambarella in the step 2.1 above is <b>linaro-aarch64-2019.11-gcc7.5</b>
 *   in order to avoid the potential glibc compatibility issue. If users want to re-build the
 *   libraries, they can choose a newer toolchain (the toolchain must be released with the SDK).
 *   The toolchain version used for buliding the application must be newer than or the same as
 *   (but not older than) the toolchain version used for building OSS.
 *
 * - - - -
 *
 * @section code_build_license 9. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
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
 * - - - -
 *
 */

/*!
 * @file doc_ov_sensor_bringup_guide.h
 * @brief
 * @version 1.0
 * @date 2023-02-02
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
 * @page ov_sensor_bringup_guide Sensor Bring-Up Guide
 *
 * @section sensor_bringup_overview 1. Overview
 *
 * This document guides users through the video input (VIN) bring-up process on the Ambarella platform.
 *
 * This section is divided into the following sections:<br>
 *
 *   - @ref sensor_bringup_key_updates
 *
 * @subsection sensor_bringup_key_updates 1.1 Key Updates
 *
 * <table>
 * <caption id="key_updates">Table 1-1. Key Updates.</caption>
 * <tr><th> Version <th> Updated Date <th> Modification
 * <tr><td align="center"> 1.0
 *     <td align="center"> 20230202
 *     <td> Initial Version
 * <tr><td align="center"> 1.1
 *     <td align="center"> 20230922
 *     <td> Move to common directory and add other SoC support
 * </table>
 *
 * - - - -
 *
 * @section sensor_bringup_background 2. Background Introduction
 *
 * To aid customers through bringing-up the VIN and sensor, Ambarella provides the following guide to prepare,
 * configure, and test the VIN and sensor on the Ambarella platform.<br>
 *
 * - - - -
 *
 * @section sensor_bringup_sensor_bringup 3. Sensor Bring-Up
 *
 * This section describes the general Vin / sensor bring-up steps.<br>
 *
 * @subsection sensor_bringup_preparation 3.1 Preparation
 *
 * Upon the arrival of a new sensor, the following steps must be performed:
 *
 *   1. Verify that the sensor driver exists in the software development kit (SDK). If not, Ambarella will add the sensor driver
 *   2. Connect the sensor to the main board
 *   3. Verify that the sensor module uses an internal crystal or an external clock.
 *   4. Check if the sensor module's output format can be supported by the serializer / deserializer (SERDES)
 *      For example, a sensor module's output may be 16-bit RAW, but SERDES can only accept 14-bit RAW. To remedy this situation,
 *      users must modify the sensor's configuration or replace the SERDES group
 *   5. Check if the sensor module includes an image signal processor (ISP). If the ISP is in the YUV module,
 *      the dummy sensor driver can be attempted; for example:
 *     @code {.c}
 *     board # modprobe ambds_brg mipi=1 w=1920 h=1080
 *     @endcode
 *
 * @subsection sensor_bringup_non_serdes_bring_up 3.2 Non-SERDES Sensor Bring-Up
 *
 * @subsubsection sensor_bringup_hardware_information 3.2.1 Collect Sensor Hardware Information
 *
 *   - Sensor type: AR0231, AR0239, OV9706, ...
 *   - Sensor interface: mobile industry processer interface (MIPI®), parallel, HiSPi™, ...
 *   - Sensor bits: 10 bits, 12 bits, 16 bits, ...
 *   - Sensor work voltage: 5 V, 12 V
 *   - Sensor clock: 24 MHz, 27 MHz; external oscillator or from another source, such as from the CV2x clock source gclk_so and from the serializer
 *   - Sensor reset pin: RC circuit or controlled by another general purpose input / output (GPIO)
 *   - Sensor I2C address
 *
 * @subsubsection sensor_bringup_configure_dts 3.2.2 Device Tree Configuration
 *
 * Similar to configuring most devices in Linux, VIN must be configured in the device trees (DTS).<br>
 * For example, when a sensor module is connected in I2C bus 3, the module should be configured as shown below:<br>
 *
 * @image html sensor_bringup_dts_local_sensor.png "Figure 3-1. DTS Configuration of Local Sensor."
 *
 * @subsubsection sensor_bringup_load_driver 3.2.3 Load Sensor Driver
 *
 * There are many sensors that can be supported in the Ambarella platform. The user must select the
 * corresponding sensor driver when compiling the Ambarella SDK. An IMX335 sensor is used in the example below:<br>
 *
 * @par For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build$ make menuconfig
 *   [*] Ambarella Linux Configuration --->
 *     [*] Ambarella Private Drivers Configuration --->
 *       [*] Build Ambarella private Vin modules --->
 *         [*] Ambarella Sensor Configuration --->
 *           [*] Sony IMX335 5.14M CMOS sensor(MIPI)
 * @endcode
 *
 * @par For Cooper SDK Amba build:
 * @code {.c}
 * build$ make menuconfig
 *   drv_modules  --->
 *     platform  --->
 *       vin  --->
 *         sensors  --->
 *           [*] kernel-module-imx335-mipi (drv_modules/platform/vin/sensors/sony_imx335_mipi)
 * @endcode
 *
 * @par For Cooper SDK Yocto build:
 * @code {.c}
 * build$ make menuconfig
 *   meta-ambabsp  --->
 *     recipes-sensor  --->
 *       [*] kernel-module-imx335-mipi (meta-ambabsp/recipes-sensor/kernel-module-imx335-mipi)
 * @endcode
 *
 * When the firmware is generated and downloaded onto the board, all sensor drivers are located in `/lib/modules/$(KERN_VERSION)/extra`.
 * Users can use the insmod or modprobe commands to load the correct sensor driver.<br>
 *
 * @code {.c}
 * board # modprobe imx335_mipi
 * @endcode
 *
 * Some parameters (such as bus_id, addr, vinc_id ...) can be specified when a sensor driver is loaded.
 *
 * @code {.c}
 * board# modprobe imx335_mipi bus_id=xxx addr=xxx
 * @endcode
 *
 * @subsection sensor_bringup_serdes_bringup 3.3 SERDES Sensor Bring-Up
 *
 * @subsubsection sensor_bringup_hardware_information_three 3.3.1 Collect Sensor Hardware Information
 *
 * @par Serializer
 *
 * - Serializer type: MAX96705, TI953, TI913, TI935, ...
 * - Serializer power source: power can come from a coaxial cable via power-on configuration (POC)
 * - Important pins for serializer:
 *
 * - MAX96705:
 *   - BWS and HIM pins: connecting the HIM pin to IOVDD is prefered
 *   - LCCEN pin: LCCEN typically connects to IOVDD. It can also connect to MAX96705's GPIO
 *   - Other pins include PWDNB, CONF0, CONF1, ...
 *
 * - TI953 / TI913 / TI935:
 *   - PDB pin: MODE_SET, CLK_IN, ...
 *   - Clock source can be an external oscillator or be supplied by deserializer through BC-ward
 *
 * @par Deserializer
 *
 * - Deserializer type: MAX9286, TI954, TI936, ...
 * - Power to deserializer
 * - Important pins for deserializer:
 *
 * - MAX9286:
 *   - BWS and HIM pins: connecting HIM pin to IOVDD is preferred
 * 	 - Others pins include PWDNB, CONF0, CONF1, ...
 *
 * - TI954(clock, PDB pin, IDX, MODE, ...):
 * 	 - IDX determines TI954's I2C bus address
 *   - MODE pin determines the TI954's receiver (RX) mode, and it can be programmed by the driver
 *
 * @subsubsection sensor_bringup_serdes_config_dts 3.3.2 Configuration of Device Tree
 *
 * For more information on how to configure the SERDES driver, users can take reference from @ref Sensors_with_SERDES_Bridge
 *
 * @subsubsection sensor_bringup_load_serdes_driver 3.3.3 Load Sensor Driver
 *
 * Select the correct SERDES driver (such as B8 + imx290_brg). <br>
 *
 * @par For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build$ make menuconfig
 *   [*] Ambarella Linux Configuration --->
 *     [*] Ambarella Private Drivers Configuration --->
 *       [*] Build Ambarella private Vin modules --->
 *         [*] Build Ambarella VIN bridge modules --->
 *           [*] Ambarella B8
 *           [*] Ambarella Sensor Configuration --->
 *           [*] Bridge sensor --->
 *             [*] Sony IMX290 2.13M CMOS Sensor(MIPI)(Bridge)
 * @endcode
 *
 * @par For Cooper SDK Amba build:
 * @code {.c}
 * build$ make menuconfig
 *   drv_modules  --->
 *     platform  --->
 *       vin  --->
 *         bridges  --->
 *           [*] kernel-module-ambrg (drv_modules/platform/vin/bridges/ambrg)
 *           [*]   kernel-module-b8 (drv_modules/platform/vin/bridges/b8)
 *         sensors  --->
 *           [*] kernel-module-imx290-brg (drv_modules/platform/vin/sensors/sony_imx290_brg)
 * @endcode
 *
 * @par For Cooper SDK Yocto build:
 * @code {.c}
 * build$ make menuconfig
 *   meta-ambabsp  --->
 *     recipes-bridge  --->
 *       [*] kernel-module-ambrg (meta-ambabsp/recipes-bridge/kernel-module-ambrg)
 *       [*]   kernel-module-b8 (meta-ambabsp/recipes-bridge/kernel-module-b8)
 *     recipes-sensor  --->
 *       [*] kernel-module-imx290-mipi-brg (meta-ambabsp/recipes-sensor/kernel-module-imx290-mipi-brg)
 * @endcode
 *
 * When the firmware is generated and downloaded into board, all sensor drivers are located in `/lib/modules/$(KERN_VERSION)/extra`.
 * Users can use insmod or modprobe command to load the correct sensor driver.<br>
 *
 * For information on  how to load the SERDES driver, users can reference @ref driver_installation_guide.
 *
 * - - - -
 *
 * @section sensor_bringup_driver_introduction 4. Sensor and SERDES Driver Introduction
 *
 * @subsection sensor_bringup_iav_driver_structure 4.1 IAV Driver Structure
 *
 * The Ambarella video driver is called the image audio video (IAV) device driver. It includes a set of Linux device
 * drivers that encapsulate the lower-level complexities of digital signal processor (DSP) core functionalities. The driver exposes
 * a series of APIs that can be invoked using device IOCTL system calls.
 * @ref fig_iav_driver_structure "Figure 4-1" displays the IAV structure.
 *
 * @anchor fig_iav_driver_structure
 * @image html iav_driver_structure.png "Figure 4-1. IAV Driver Structure."
 *
 * @subsection sensor_bringup_sensor_driver 4.2 Sensor Driver
 *
 * The following figure is the system architecture of the sensor driver:
 *
 * @image html sensor_driver_architecture.png "Figure 4-2. Sensor Driver Architecture."
 *
 * Because there are so many sensor drivers, IMX335 is used as an example. The sensor ID is defined
 * in `ambarella/include/iav_vin_common.h` for CV2x SDK 3.0 and `ambarella/drv_modules/private/video/dsp_$(ARCH)/uapi/iav_vin_common.h` for Cooper SDK.
 *
 * @code {.c}
 *
 * enum sensor_list {
 *   ...
 *   SENSOR_IMX335 = 0x0000301A,
 *   ...
 * };
 * @endcode
 *
 * When a new sensor driver is added, for Cooper SDK, `ambarella/build/bin/common/gen_build_chain.py` automatically manages
 * the configuration of the compile switch; for CV2x SDK 3.0, the configuration for "menuconfig" must be added
 * into `ambarella/kernel/private/platform/vin/sensors/AmbaConfig`.
 *
 * @code {.c}
 * config CONFIG_SENSOR_IMX335_MIPI
 *   bool "Sony IMX335 5.14M CMOS sensor(MIPI)"
 *   default n
 *   help
 * 	   Select Sony IMX335 5.14M CMOS sensor.
 * @endcode
 *
 * There are five files for sony_imx335_mipi listed below.
 *
 * @image html tree_local_sensor_imx335.png "Figure 4-3. Tree of IMX335 Driver on CV2x SDK 3.0."
 * @image html tree_local_sensor_imx335_cooper.png "Figure 4-4. Tree of IMX335 Driver on Cooper SDK."
 *
 * Many constants are defined in imx335.h. The register table and video modes that can be supported
 * by IMX335 are listed in imx335_table.c.<br>
 *
 * @code {.c}
 * static struct vin_video_format imx335_formats[] = {
 *   ...
 * 	 {  // 2x2 binning linear: 720p60 12bits
 *       .video_mode            = AMBA_VIDEO_MODE_720P,
 *       .def_start_x           = (6+6+1296-1280) / 2,
 *       .def_start_y           = (4+4+972-720)/2 + 4,
 *       .def_width             = 1280,
 *       .def_height            = 720,
 *      //  sensor mode
 *       .hdr_mode              = AMBA_VIDEO_LINEAR_MODE,
 *       .device_mode           = 2,
 *       .pll_idx               = 1,
 *       .width                 = 1280,
 *       .height                = 720,
 *       .format                = AMBA_VIDEO_FORMAT_PROGRESSIVE,
 *       .type                  = AMBA_VIDEO_TYPE_RGB_RAW,
 *       .bits                  = AMBA_VIDEO_BITS_12, // output format
 *       .ratio                 = AMBA_VIDEO_RATIO_16_9,
 *       .max_fps               = AMBA_VIDEO_FPS_60, // sensor's frame rate
 *       .default_fps           = AMBA_VIDEO_FPS_29_97,
 *       .default_agc           = 0,
 *       .default_shutter_time  = AMBA_VIDEO_FPS_60,
 *       .default_bayer_pattern = VINDEV_BAYER_PATTERN_RG,
 * 	 },
 *   ...
 * };
 * @endcode
 *
 * the main source code of the IMX335 sensor driver is included in imx335.c. The entry point of this driver is imx335_probe;
 * it will be called when the user loads this driver. After initialization operations are completed
 * in the probe function, the sensor driver will register the current sensor driver into the IAV module by calling the
 * ambarella_vin_register_device interface. This interface passes an important parameter, imx335_ops,
 * to the VIN module.<br>
 *
 * @image html imx335_mipi_ops.png "Figure 4-5. IMX335_MIPI OPS."
 *
 * Users can find the declaration of the vin_ops structure in `ambarella/kernel/private/include/vin_api.h` for CV2x SDK 3.0 and
 * `ambarella/drv_modules/private/video/dsp_$(ARCH)/include/driver/vin_api.h` for Cooper SDK.<br>
 *
 * @image html vin_ops.png "Figure 4-6. VIN OPS."
 *
 * When the user wants to execute an operation, such as adjusting the frame rate of a sensor, an IOCTL system call
 * must be executed at the application level. Then, the IAV's VIN module accepts this IOCTL system call,
 * and the function pointer set_frame_rate in vin_ops is called. Finally, imx335_set_fps is executed
 * because it is assigned to the set_frame_rate function pointer.
 *
 * @subsection sensor_bringup_serdes_driver 4.3 SERDES Driver
 *
 * The following figure is the system architecture of SERDES driver:
 *
 * @image html serdes_driver_architecture.png "Figure 4-7. SERDES Driver Architecture."
 *
 * @subsubsection sensor_bringup_sensor_bridge_driver 4.3.1 Bridge Sensor Driver
 *
 * Similar to imx335_mipi, imx335_mipi_brg is used as an example. The sensor ID is defined in `ambarella/include/iav_vin_common.h` for
 * CV2x SDK 3.0 and `ambarella/drv_modules/private/video/dsp_$(ARCH)/uapi/iav_vin_common.h` for Cooper SDK.
 *
 * @code{.c}
 * enum sensor_list {
 *   ...
 *   SENSOR_IMX335 = 0x0000301A,
 * 	 ...
 * };
 * @endcode
 *
 * When a new bridge sensor driver is added, for Cooper SDK, `ambarella/build/bin/common/gen_build_chain.py` automatically manages
 * the configuration of the compile switch; for CV2x SDK 3.0, the configuration for "menuconfig" must be added
 * into `ambarella/kernel/private/platform/vin/sensors/AmbaConfig`.
 *
 * @code {.c}
 * config CONFIG_SENSOR_IMX335_MIPI_BRG
 * 	 bool "Sony IMX335 5.14M CMOS sensor(MIPI)(Bridge)"
 * 	 default n
 * 	 help
 * 		 Select Sony IMX335 5.14M CMOS sensor, with MIPI output, for bridge driver.
 * @endcode
 *
 * Video modes and operations are similar to IMX335; the differences of IMX335_BRG are located in imx335_probe.
 * For imx335_mipi, after initialization operations are completed in the probe interface, ambarella_vin_register_device
 * is called to create a connection with the IAV's VIN module. For imx335_mipi_brg, the VIN module calls amba_brg_register_device to create
 * a connection with the bridge driver. Then, the bridge driver (ambrg.c) calls ambarella_vin_register_device with imx335_mipi_brg's OPS
 * to create a connection with the IAV's VIN module.
 *
 * @subsubsection sensor_bringup_serdes_driver_sub 4.3.2 SERDES Driver
 *
 * @par Device Tree
 *
 * @image html dts_serdes.png "Figure 4-8. SERDES Device Trees."
 *
 * - brgpwr-gpios: power GPIO for deserializer
 * - brgrst-gpios: reset GPIO for deserializer
 * - bus-addr: related to the specified driver's parameter dts_addr
 * - vinc_id: related to the bridge driver parameter vinc_id
 *
 * @par Power-on and Reset
 *
 * In the amba_register_vin_brg (ambrg.c) function, ambrg_init_pwr_rst_gpio will be called to get GPIO
 * definitions from the device table.
 *
 * Power-on and reset operations are executed in the ambarella_vin_register_device function:
 *
 * @code {.c}
 * ambarella_vin_register_device
 *   --> init_vsrc_device
 *      --> vdev->ops->init_device (ambrg_init_device is assigned to this function pointer)
 *        --> ambrg_hw_init
 *          --> ambrg_hw_reset
 * @endcode
 *
 * @par Bridge Driver Operations
 *
 * - Interfaces to read and write registers:
 *
 * <table>
 * <caption id="read_write_interface"> Table 4-1. Interfaces to Read and Write Registers.</caption>
 * <tr><th> Hardware <th> Read / Write <th> Interfaces Name
 * <tr><td align="center" rowspan="2"> Serializer + Deserializer
 *     <td align="center"> Read
 *     <td align="center"> brg_read_reg
 * <tr><td align="center"> Write
 *     <td align="center"> brg_write_reg
 * <tr><td align="center" rowspan="2"> Sensor
 *     <td align="center"> Read
 *     <td align="center"> brg_read_chan_reg
 * <tr><td align="center"> Write
 *     <td align="center"> brg_write_chan_reg
 * </table>
 *
 * - brg_hw_init_pre
 *
 * This interface is used to initialize SERDES and remap the I2C address of the serializer and sensor.
 *
 * <table>
 * <caption id="brg_hw_init_pre"> Table 4-2. Hardware Address and Remapping I2C Address.</caption>
 * <tr><th> Hardware <th> Hardware Address <th> I2C Address (Remapping)
 * <tr><td align="center"> Serializer
 *     <td align="center"> pinfo->i2c_ctrl.addr.ser_def
 *     <td align="center"> pinfo->i2c_ctrl.addr.ser_chan0/ser_chan1
 * <tr><td align="center"> Sensor
 *     <td align="center"> pinfo->sensor_ctrl.dev_addr
 *     <td align="left"> 1 pinfo->i2c_ctrl.add.sen_all<br>
 *                       2 IDC_ADDR_SEN_BASE + ...
 * </table>
 *
 * @note
 *   - Texas Instrument's (TI) deserializer can automatically obtain the I2C address. Before remapping the I2C address, the deserializer will choose one port
 *     and turn off others.<br>
 *   - MAXIM requires software to specify the hardware address. Before remapping the i2c address, MAXIM will choose one link
 *     and turn off others.<br>
 *   - MAX9296 is used as an example:
 *     @code{.c}
 *     board# test_vin -r 0xffff
 *       [0xffff: 0x8272a560]
 *     board# dmesg | tail -n 20
 *       VIN: max9296[0] I2C address mapping
 *       DES:0x90 <-- 8 bit i2c address and real address needs to be shift 1 bit to right(0x48)
 *       SER A:0x82
 *       SER B:0xa2
 *       SEN base:0x60 <-- IDC_ADDR_SEN_BASE
 *       SEN all:0x74 <-- address after remapping
 *       CMU:locked!
 *       ERRB:off!
 *       GMSL2 link:locked! <-- needs to check whether SerDes is locked or not firstly
 *       Active link mode:0x60!
 *       Link A Decoding:pass!
 *       Link B Decoding:pass!
 *       Idle word:pass!
 *       Line Fault:pass!
 *       Remote side:pass!
 *     @endcode
 *
 * - brg_set_clk_si
 *
 * Some sensors do not use a crystal to provide a clock but instead require SERDES to output an external clock.
 *
 * - brg_vin_config_pre
 *
 * This interface is used to initialize connecting the configuration for the serializer and sensor.
 *
 * <table>
 * <caption id="brg_vin_config_pre"> Table 4-3. Parameters in brg_vin_config_pre.</caption>
 * <tr><th> Parameter Name <th> Description
 * <tr><td align="center"> Lane_number
 *     <td align="center"> SENSOR_2_LANE / SENSOR_4_LANE
 * <tr><td align="center"> Lane mapping
 *     <td align="center"> Lane order can change
 * <tr><td align="center"> Lane speed
 *     <td align="center"> Bandwidth to receive sensor data
 * <tr><td align="center"> Pipeline / streamID
 *     <td align="center"> Related to vender
 * </table>
 *
 * - brg_vout_config
 *
 * This interface is used to configure parameters between the deserializer and the SoC:
 *
 * <table>
 * <caption id="brg_vout_config"> Table 4-4. Parameters in brg_vout_config.</caption>
 * <tr><th> Parameter Name <th> Description
 * <tr><td align="center"> lane_number
 *     <td align="center"> SENSOR_2_LANE / SENSOR_4_LANE
 * <tr><td align="center"> interface_type
 *     <td align="center"> SENSOR_MIPI / SENSOR_MIPI_VC / ...
 * <tr><td align="center"> data_rate
 *     <td align="left"> Choose the closest speed; otherwise, the video frame may be a single line.<br>
 *                       enum { <br>
 *                         SENSOR_MIPI_BIT_RATE_M = 0, // default, ~ 400Mbps<br>
 *                         SENSOR_MIPI_BIT_RATE_H,     // ~ 800Mbps<br>
 *                         SENSOR_MIPI_BIT_RATE_L,     // ~ 200Mbps<br>
 *                         SENSOR_MIPI_BIT_RATE_UH,    // ~ 2200Mbps<br>
 *                         SENSOR_MIPI_BIT_RATE_NA,    // for non-MIPI sensor<br>
 *                       };
 * </table>
 *
 * - brg_get_status
 *
 * This interface is used to check SERDES status. When SERDES is locked, the serializer registers can be read.
 *
 * - - - -
 *
 * @section sensor_bringup_debug 5. Debug
 *
 * @subsection sensor_bringup_measure_signal 5.1 Sensor Signal
 *
 * When a new sensor cannot function normally, MIPI CLK / DATA and SYNC signals must be checked first.<br>
 *
 * @subsection sensor_bringup_i2c_tool 5.2 I2C Tools
 *
 * Certain I2C tools can be used to debug, such as i2cdetect and i2ctranfer.
 *
 * @code {.c}
 * board # echo 0 > /proc/sys/kernel/printk
 * board # modprobe i2c-dev
 * board # i2cdetect -ya 2
 * @endcode
 *
 * The command "i2cdetect -ya 2" scans all I2C devices mounted on I2C bus 2.
 *
 * @code {.c}
 * board # i2ctransfer -yf 2 w1@0x38 0x5b r1
 * @endcode
 *
 * The command "i2ctransfer -yf 2 w1@0x38 0x5b r1" reads register 0x5b's data from I2C device,
 * which is mounted on I2C bus 2 with an I2C address equal to 0x38.
 *
 * @code {.c}
 * board # i2ctransfer -yf 2 w2@0x38 0x11 0x13
 * @endcode
 *
 * The command "i2ctransfer -yf 2 w2@0x38 0x11 0x13 " writes 0x13 to the register 0x11 of the I2C device,
 * which is mounted on I2C bus 2 with an I2C address equal to 0x38.
 *
 * @code {.c}
 * board # modprobe ambad
 * board # amba_debug -g 81 -d 1
 * @endcode
 *
 * The command "amba_debug -g 81 -d 1" manually pulls GPIO 81 to a high level.
 *
 * @subsection sensor_bringup_test_vin 5.3 test_vin
 *
 * The unit test program test_vin is located in `ambarella/unit_test/private/vin_test/test_vin.c` for CV2x SDK 3.0 and
 * `ambarella/unit_test/private/iav_test/dsp_$(ARCH)/vin/test_vin.c`. By default, it is
 * compiled into te firmware with $board_ipcam_config selected.<br>
 *
 * The following is the usage information of test_vin:
 *
 * @code {.c}
 * # test_vin
 * test_vin usage:
 * -i --vin [vin mode]             change vin mode
 * -S --src [source]               select source(vsrc_id)
 * -h --switch-reg-ctx [vsrc_id]   switch vsrc context
 * -f --frame-rate [frate]         set encoding frame rate
 * -m --mirror-pattern [0~3]       set vin mirror pattern, 0:none, 1:flip, 2:mirror, 3:mirror&flip, 255:auto
 * -b --bayer-pattern [0~3]        set vin bayer pattern, 0:RG, 1:BG, 2:GR, 3:GB, 255:AUTO
 * -t --test-fps [vinc_id]         test vin fps
 * -r --read-reg [addr]            read regisger
 * -w --write-reg [addr]           write register
 * -d --reg-data [data]            the register data to write
 * -n --reg-count [count]          register count to read/write
 * -s --shutter [1-8000]           set shutter time in 1/n sec format
 * -g --agc-index [index]          set agc index, -n for index count
 * -c --ae-check [0 or 1]          enable/disable shutter/agc check
 * -e --set-stream [0 or 1]        set sensor streaming mode
 * -p --set-tp [tp_mode]           set sensor test pattern
 * -A --awb [set awb]              set sensor awb gain
 *    --rgain [1024~6144]          set sensor r gain, 1024 stand for 1X gain
 *    --bgain [1024~6144]          set sensor b gain, 1024 stand for 1X gain
 *    --hdr-mode [0~3|15]          set VIN HDR mode
 *    --max-fps [max fps]          set VIN max fps
 *    --bits [8|10|12]             set VIN bit
 *    --dual-gain [0~2]            set dual gain mode, 0:off, 1:hcg+lcg, 2:hcg+lcg combined
 *    --runtime-switch             Runtime switch vin mode
 * @endcode
 *
 * Here, users can use the `test_vin` options "-r" and "-w" to read and write registers:
 *
 * @code {.c}
 * board # test_vin -r $register_address -n $registers_amount
 * board # test_vin -w $register_address -d $value
 * @endcode
 *
 * @subsection sensor_bringup_soc_registers 5.4 Check SoC Registers
 *
 * Users can use amba_debug to dump SoC's registers, as follows:
 *
 * @code {.c}
 * // VIN0
 * board # amba_debug -w 0xed1c8000   -d 0x1000 && amba_debug -r 0xed1c0000   -s 0x120 (CV2x)
 * board # amba_debug -w 0x20ed1e8000 -d 0x1000 && amba_debug -r 0x20ed1e0000 -s 0x140 (CV5x)
 * board # amba_debug -w 0xffed1e8000 -d 0x1000 && amba_debug -r 0xffed1e0000 -s 0x140 (CV7x)
 * // VIN1
 * board # amba_debug -w 0xed1c8000   -d 0xa000 && amba_debug -r 0xed1c0000   -s 0x120 (CV2x)
 * board # amba_debug -w 0x20ed1e8000 -d 0x2000 && amba_debug -r 0x20ed1e0000 -s 0x140 (CV5x)
 * board # amba_debug -w 0xffed1e8000 -d 0x2000 && amba_debug -r 0xffed1e0000 -s 0x140 (CV7x)
 * @endcode
 *
 * When the system is abnormal or in reset status, value of register 0xed1c800 (CV2x), 0x20ed1e8000 (CV5x) and 0xffed1e8000 are 0x00000001.
 *
 * - The normal value of register 0xed1c00c8 in master mode is 0x2841 (CV2x);
 * - The normal value of register 0x20ed1e00bc in master mode is 0xf (CV5x);
 * - The normal value of register 0xffed1e00bc in master mode is 0xf (CV7x);
 *
 * - the normal value in slave mode is 0x3841; (CV2x)
 * - the normal value in slave mode is 0x40f; (CV5x and CV7x)
 *
 * @subsection sensor_bringup_debug_dsp_log 5.5 Capture DSP Log
 *
 * Ambarella provides the tool dsplog_cap to capture the DSP log. Detailed debug information can help
 * users locate issues. Following steps will display how to configure and use this tool:
 *
 * 1). Enable building `dsplog_cap`
 *
 * @par For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build$ make menuconfig
 *   [*] Ambarella Linux Configuration --->
 *     [*] Ambarella Private Drivers Configuration --->
 *       [*] Build Ambarella DSP Log Driver module
 * @code {.c}
 *
 * @par For Cooper SDK Amba build:
 * @code {.c}
 * build$ make menuconfig
 *   drv_modules  --->
 *     platform  --->
 *       [*] kernel-module-dsplog (drv_modules/platform/dsplog)  --->
 * @endcode
 *
 * @par For Cooper SDK Yocto build:
 * @code {.c}
 * build$ make menuconfig
 *   meta-ambabsp  --->
 *     recipes-dbgtool  --->
 *       [*] kernel-module-dsplog (meta-ambabsp/recipes-dbgtool/kernel-module-dsplog)  --->
 * @endcode
 *
 * 2). Start to capture the DSP log
 *
 * @endcode
 * board # init.sh --na
 * board # modprobe ambad
 * board # modprobe dsplog
 * board # dsplog_cap -m all -b all -l 3 -r 0 -o /tmp/dsplog.bin -p 10000000 &
 * @endcode
 *
 * 3). When DSP enters into abnormal status:
 *
 * @code {.c}
 * board # killall dsplog_cap
 * board # dsplog_cap -i /tmp/dsplog.bin -f /tmp/dsplog.txt
 * @endcode
 *
 * 4). Then, users can send dsplog.txt to the Ambarella support team to receive help.
 *
 * @subsection sensor_bringup_vin_synchronization_fail 5.6 VIN: Port[0] Synchronization Fail
 *
 * When this issue occurs, check if:
 *
 * - FSYNC pin is connected
 * - The wait time before synchronization is insufficient
 *
 * @subsection sensor_bringup_video_black 5.7 Video Frame is Completely Black
 *
 * When this issue occurs, follow the steps below:
 *
 * 1. Enssure that auto white balance (AWB) / auto exposure (AE) / auto focus (AF) (3A) parameters are correct
 * 2. Verify if VIN outputs video data, dump the VIN register, and check the number of lanes
 * 3. Ensure that SERDES has data
 * 4. Ensure that the sensor has data and check the data pin wave
 * 5. If multiple sensors are connected, ensure that FSYNC / TRIGGER pins are connected
 *
 * @subsection sensor_bringup_drop_frame 5.8 Frame Drop
 *
 * Users can use the unit test programs test_encode and test_stream to check if frame drop issues occur.
 * Below is an example on CV25 Hazelnut Evaluation Kit (EVK) with an IMX274 sensor:
 *
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx274_mipi
 * board # test_aaa_service -a &
 * board # test_encode -i1080p --hdmi 720p -X --bmaxsize 1080p --bsize 1080p
 * board # test_encode -A -h1080p -e
 * board # test_stream --nofile
 * @endcode
 *
 * Then, users can watch the average frames per second (FPS) printed by test_stream unit test commands.
 *
 * Along with the method mentioned above, the feature "IDSP drop audit function" detects frame drops.
 * For more details about this feature, refer to @ref example3_audit_function for CV2x and @ref frame_drop_aud for other SoCs.
 *
 * - - - -
 *
 * @section sensor_bringup_license 6. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
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
 * - - - -
 *
 */

/*!
 * @file doc_ov_new_board_bringup_guide.h
 * @brief
 * @version 1.0
 * @date 2022-10-09
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
 * @page ov_new_board_bringup_guide New Board Bring-Up Guide
 *
 * @section new_board_bringup_overview 1. Overview
 *
 * This document guides users through bringing up a new board on the Ambarella platform.<br>
 *
 * This chapter contains the following section:<br>
 *
 *   - Section @ref new_board_bringup_key_updates
 *
 * @subsection new_board_bringup_key_updates 1.1 Key Updates
 *
 * <table>
 * <caption id="key_updates">Table 1-1. Key Updates.</caption>
 * <tr><th> Version <th> Date <th> Modification
 * <tr><td align="center"> 1.0
 *     <td align="center"> 20221009
 *     <td> Initial Version
 * <tr><td align="center"> 1.1
 *     <td align="center"> 20230914
 *     <td> Move to common part and add CV5x support
 * <tr><td align="center"> 1.2
 *     <td align="center"> 20240112
 *     <td> Updated Section @ref new_board_bringup_modify_gpio_configuration "3.3.3 GPIO configuration"
 * </table>
 *
 * - - - -
 *
 * @section new_board_bringup_background 2. Background Introduction
 *
 * To aid customers in bringing up new boards for the start of their projects, Ambarella provides
 * the following guide to prepare, configure, and test new boards using the Ambarella platform.<br>
 *
 * - - - -
 *
 * @section new_board_bringup_common_steps 3. Common System Bring-Up Steps
 *
 * This chapter describes the general steps used during system bring-up, and consists of the following sections:<br>
 *
 *   - Section @ref new_board_bringup_preparation
 *   - Section @ref new_board_bringup_download_firmware_through_ambausb
 *   - Section @ref new_board_bringup_configuration_instructions_of_amboot
 *   - Section @ref new_board_bringup_configuration_instructions_of_kernel
 *
 * @subsection new_board_bringup_preparation 3.1 Bring-Up Preparation
 *
 * Upon the arrival of a new board, the following steps must be performed:<br>
 *
 *   -# Verify that power-up timing meets the required specifications.
 *   -# Check the power of all hardware modules.
 *   -# Verify that the power-on configuration (POC) settings are as expected in the design.
 *      This step is critical because the POC settings decide the boot options, such as boot
 *      media (NAND, embedded multi-media controller (eMMC), SPI, or SPI-NOR), boot method (normal or secure boot) and more.
 *      For more details, refer to the POC table in the hardware schematic diagram.
 *   -# Check the double data rate (DDR) voltage. This step is important because the firmware
 *      must first be moved into memory. If the new board is empty, the firmware must first be
 *      downloaded into dynamic random access memory (DRAM) using the tool AmbaUSB;
 *      otherwise, the firmware will be read from boot media and translated to memory.
 *   -# Verify that the USB is functioning, as the firmware must be downloaded to the board via USB.
 *
 * Contact the Ambarella hardware support team for assitance.<br>
 *
 * @subsection new_board_bringup_download_firmware_through_ambausb 3.2 Download Firmware Through AmbaUSB
 *
 * Before bring-up, users must install the AmbaUSB tool and understand how it is used. This tool is
 * released through Ambarella’s portal release order (PRO) system. Users can find the installation
 * package in PRO.<br>
 *
 * The following steps help users download the firmware onto a new board:
 *
 * -# Pull-high POC[10] of the board. The system enters into force USB boot mode.<br>
 * -# If the users’s operating system (OS) is Windows, open the device manager and check if the Ambarella
 *    evaluation board devices have been detected. If the Ambarella evaluation board devices were not
 *    previously installed, they should be installed automatically when the board powers up with the USB
 *    connected.<br>
 *
 * @image html board_bringup_ambarella_evaluation_board_device.png "Figure 3-1. Ambarella Evaluation Board Device."
 *
 * -# Launch AmbaUSB and choose the correct chip (marked as red box 1 in @ref fig_ambausb_force_usb_mode "Figure 3-2" for
 *    CV22 and @ref fig_ambausb_force_usb_mode_cv5 "Figure 3-3" for CV5). Here, the CV22 Walnut and CV5 Timn evaluation kit (EVK)
 *    boards are used as examples. Then, the CV22 / CV5 USB device is detected by AmbaUSB (marked in red box 2
 *    in @ref fig_ambausb_force_usb_mode "Figure 3-2" and @ref fig_ambausb_force_usb_mode_cv5 "Figure 3-3").<br>
 *
 * @anchor fig_ambausb_force_usb_mode
 * @image html board_bringup_amba_usb_force_usb_display.png "Figure 3-2. AmbaUSB with Force USB Mode for CV22 Walnut."
 *
 * @anchor fig_ambausb_force_usb_mode_cv5
 * @image html board_bringup_amba_usb_force_usb_cv5.png "Figure 3-3. AmbaUSB with Force USB Mode for CV5 Timn."
 *
 * -# Use AmbaUSB to verify if the POC settings are correct. If the POC settings are not correctly set,
 *    they must be adjusted.<br>
 *
 * @anchor fig_ambausb_read_register
 * @image html board_bringup_amba_usb_read_register.png "Figure 3-4. Read Registers Using AmbaUSB in CV22 Walnut."
 *
 * When the CV22 Walnut board enters into force USB boot mode, users can click the magic
 * icon (marked as a red 1 in @ref fig_ambausb_read_register "Figure 3-4"). Then, AmbaUSB will go to the
 * “AMBoot tool wizard” page. After choosing the “Read Register” checkbox and specifying the address and
 * length of the POC register (marked as red boxes 2, 3, and 4 respectively in @ref fig_ambausb_read_register "Figure 3-4"),
 * AmbaUSB can read the value of the POC register (shown in @ref fig_ambausb_read_register_result "Figure 3-5")
 * by clicking the <b>Ok</b> button.
 *
 * @anchor fig_ambausb_read_register_result
 * @image html board_bringup_amba_usb_read_register_result.png "Figure 3-5. POC Register Value Displayed in AmbaUSB on CV22 Walnut."
 *
 * On the CV5x platform, for the sake of security consideration, AmbaUSB must load a usbstrap file (end with `.ust`) to initialize the
 * board first. Then, it can execute operations such as reading registers, reading / writing memory, and more.
 * @ref fig_ambausb_load_ust_cv5 "Figure 3-6. Loading UST Files in AmbaUSB."
 *
 * @anchor fig_ambausb_load_ust_cv5
 * @image html board_bringup_amba_usb_load_ust_cv5.png "Figure 3-6. Load UST File in AmbaUSB on CV5 Timn."
 *
 * AmbaUSB has some `.ust` files and users can select them from the installing directory (`cv5_lpddr5_540MHz.ust` is used here).
 * When a correct `.ust` file has been loaded successfully, AmbaUSB will check and execute it. Then, it will enter into UST mode. Refer to
 * @ref fig_ambausb_ust_mode_cv5 "Figure 3-7".
 *
 * @anchor fig_ambausb_ust_mode_cv5
 * @image html board_bringup_amba_usb_ust_mode_cv5.png "Figure 3-7. UST Mode in AmbaUSB on CV5 Timn."
 *
 * Reading POC registers in UST mode is similar to the operations used on the CV22 Walnut board; the only difference is the address of the POC register.
 * On the CV5 platform, the value is <b>0x20ed080034</b> (40 bits, not 32 bits). @ref fig_ambausb_ust_mode_cv5 "Figure 3-8" shows
 * the reading POC register operations on CV5 Timn and @ref fig_ambausb_ust_mode_cv5 "Figure 3-9" displays the result.
 *
 * @anchor fig_ambausb_read_poc_cv5
 * @image html board_bringup_amba_usb_read_poc_register_cv5.png "Figure 3-8. Read POC Registers on CV5 Timn."
 *
 * @anchor fig_ambausb_poc_value_cv5
 * @image html board_bringup_amba_usb_poc_value_cv5.png "Figure 3-9. Display POC Register Values in AmbaUSB on CV5 Timn."
 *
 * -# AmbaUSB can test memory access operations and check if there are DRAM hardware issues.<br>
 *
 * @anchor fig_ambausb_memory_test
 * @image html board_bringup_amba_usb_memory_test.png "Figure 3-10. Memory Tests in AmbaUSB on CV22 Walnut."
 *
 * As shown in the figure above, when the CV22 Walnut board enters into force USB boot mode, users can click the magic
 * icon (marked as a red 1 in @ref fig_ambausb_memory_test "Figure 3-10"). Then, AmbaUSB will go to the
 * “AMBoot tool wizard” page. Users can test memory in this page:
 *
 *   - Select the memory test in the top-left corner.
 *   - Input the accessing address correctly, such as 0x100000.
 *   - Input the data to be written into the memory, such as 0x55aa55aa.
 *   - Input the data length.
 *
 * When all parameters for memory testing are ready, users can click the <b>Ok</b> button to enable AmbaUSB to
 * perform memory tests by attempting to read the data that has been written into memory. If data read
 * from the memory is the same as what users input in the “AMBoot tool wizard”(see @ref fig_ambausb_memory_test_result "Figure 3-11"),
 * there is no issue regarding memory read / write. Otherwise, users can refer to
 * <b>FAQ 2</b> to find the root cause.
 *
 * @anchor fig_ambausb_memory_test_result
 * @image html board_bringup_amba_usb_memory_test_result.png "Figure 3-11. Memory Test Results in AmbaUSB on CV22 Walnut."
 *
 * On the CV5x platform, AmbaUSB disables the "Test Memory" operation, and the user must split the into two steps:
 * "write memory" and "read memory". The following figures demonstrate the process of writing and reading memory.
 *
 * @image html board_bringup_amba_usb_write_memory_cv5.png "Figure 3-11. Write Memory Operation in AmbaUSB On CV5 Timn."
 *
 * @image html board_bringup_amba_usb_write_memory_result_cv5.png "Figure 3-12. Result of the Writing Memory Operation in AmbaUSB On CV5 Timn."
 *
 * @image html board_bringup_amba_usb_read_memory_cv5.png "Figure 3-13. Read Memory Operation in AmbaUSB On CV5 Timn."
 *
 * @image html board_bringup_amba_usb_read_memory_result_cv5.png "Figure 3-14. Result of the Reading Memory Operation in AmbaUSB On CV5 Timn."
 *
 * -# Users can manually load the Ambarella bootloader (BLD) to enter into the BLD’s command line mode.
 *
 * The following figure and steps provide instructions for the CV22 Walnut board (similar process on CV5 Timn):
 *
 * @anchor fig_ambausb_load_bld_manually
 * @image html board_bringup_amba_usb_load_bld_manually.png "Figure 3-15. Load Ambarella Bootloader Manually in AmbaUSB."
 *
 *   -# Choose the board configuration (marked as red box 1 in @ref fig_ambausb_load_bld_manually "Figure 3-15");
 *      for CV22 Walnut, LINUX.CV22.LPDDR4.NAND is selected.
 *   -# Click the magic icon (marked as red box 2 in @ref fig_ambausb_load_bld_manually "Figure 3-15").
 *      Then, AmbaUSB will go to the “AMBoot tool wizard” page.
 *   -# Choose the Ambarella bootloader (marked as red box 3 in @ref fig_ambausb_load_bld_manually "Figure 3-15").
 *      When the board firmware is compiled, the Ambarella bootloader bld_release.elf will
 *      be generated in the directory `ambarella/out/board_name/amboot`.
 *
 * @note
 *   In order for AmbaUSB to successfully load the BLD, Ambarella recommends disabling the Arm® TrustZone® feature (in the configuration file) at the bring-up stage.
 *   @code {.c}
 *   # For SDK 3.0:
 *   $ make menuconfig
 *       Ambarella Boot Configuration --->
 *         Bootloader --->
 *           Ambarella Firmware Configuration --->
 *             Memory Options --->
 *               (0x00000000) AMBoot starting address
 *             AMBoot Options --->
 *               [] Boot with TrustZone ----
 *
 *   # For Cooper SDK:
 *   $ make menuconfig
 *       boot --->
 *         [*] amboot (boot/ambamk) --->
 *           Ambarella Firmware Configuration --->
 *             Memory Options --->
 *               (0x00000000) AMBoot starting address
 *             AMBoot Options --->
 *               [] Boot with TrustZone ----
 *   @endcode
 *
 * Click the <b>Ok</b> button, then press the <b>Enter</b> key in the serial port. When this bootloader is loaded
 * completely by AmbaUSB, it will be executed in memory and the command line mode appears in the serial
 * port, as shown below.<br>
 *
 * @image html board_bringup_bld_command_line_mode.png "Figure 3-16. Ambarella Bootloader Command Line Mode."
 *
 * Many commands in the BLD can be used for debugging purposes. The “help” command shows all applications
 * supported in the Ambarella bootloader.<br>
 *
 * @image html board_bringup_bld_command_line_mode_help.png "Figure 3-17. Ambarella Bootloader Help Command."
 *
 * After successfully completing the previous steps, users can now burn the firmware onto the board.
 *
 *   -# Choose the board configuration (marked as red box 1 in @ref fig_ambausb_download_fw "Figure 3-18").
 *      For CV22 Walnut, LINUX.CV22.LPDDR4.NAND is selected.
 *   -# Specify the firmware's location (marked as red box 2 in @ref fig_ambausb_download_fw "Figure 3-18").
 *   -# Download the firmware onto the board (marked as red box 3 in @ref fig_ambausb_download_fw "Figure 3-18").
 *
 * @anchor fig_ambausb_download_fw
 * @image html board_bringup_amba_usb_download_firmware.png "Figure 3-18. Download Firmware in AmbaUSB on CV22 Walnut."
 *
 * To build and burn the firmware, users can take reference from @ref ov_code_build and @ref page_getting_start_guide.
 *
 * @subsection new_board_bringup_configuration_instructions_of_amboot 3.3 Configuration Instructions for AMBoot
 *
 * Per different hardware designs, the bootloader and kernel must be configured accordingly when
 * building a firmware for users’ boards.<br>
 *
 * This section introduces how to prepare AMBoot (the bootloader of Ambarella systems on chip (SoCs)).
 * The two parts of the Ambarella SoC bootloader are the bootstrapper (BST) and the bootloader (BLD).<br>
 *
 *   - BST: initializes DDR and loads the BLD from storage media to DRAM
 *   - BLD: loads and runs the kernel. Additionally, the Ambarella BLD provides many applications
 *     when users enter into BLD command line mode. Users can enter into this command line mode
 *     by pressing the “Enter” key in the serial port while the BLD is loading
 *
 * @subsubsection new_board_bringup_ini_file_for_bst 3.3.1 INI Files for BST
 *
 * Before compiling the software development kit (SDK), an `.ini` file must be provided for the BST.
 * All parameters configured in this `.ini` file will be parsed and passed to the BST module. The tool
 * bstiniparser is located in `ambarella/amboot/src/bst/tools` (SDK 3.0) and `ambarella/boot/amboot/src/bst/tools` (Cooper SDK).
 * This tool analyzes the `.ini file` and translates it into a C header file. Here, the `cv22aq_walnut_76_lpddr4.ini` of the
 * CV22 Walnut EVK board is used as an example (CV5 is similar). <br>
 *
 * @image html board_bringup_ddr_parameter_ini.png "Figure 3-19. DDR Parameters in cv22aq_walnut_76_lpdd4.ini."
 *
 * @code {.c}
 * # For SDK 3.0:
 * board $ cd ambarella/amboot/src/bst/tools
 * board $ ./bstiniparser ../../../../boards/cv22_walnut/bsp/cv22aq_walnut_76_lpddr4.ini | grep DRAM
 *
 * # For Cooper SDK:
 * board $ cd ambarella/boot/amboot/src/bst/tools
 * board $ ./bstiniparser ../../../../../boards/cv22_walnut/bsp/cv22aq_walnut_76_lpddr4.ini | grep DRAM
 *
 * #define PARAM_DRAM_TRAINING_VAL                   0x00fa007d
 * #define DRAM_CONTROL_DDRC0_VAL                    0x6dc02a80
 * #define DRAM_RSVD_SPACE_DDRC0_VAL                 0x7ff00000
 * #define DRAM_CONFIG_DDRC0_VAL                     0x702842d8
 * #define DRAM_TIMING1_DDRC0_VAL                    0x76ace30c
 * #define DRAM_TIMING2_DDRC0_VAL                    0x1ce30d89
 * #define DRAM_TIMING3_DDRC0_VAL                    0x20000153
 * #define DRAM_TIMING4_DDRC0_VAL                    0x12d8c7b6
 * #define DRAM_TIMING5_LP4TRAIN_DDRC0_VAL           0x6c588000
 * #define DRAM_PAD_TERM_DDRC0_VAL                   0x0002009c
 * #define DRAM_PAD_TERM2_DDRC0_VAL                  0x090f990f
 * #define DRAM_PAD_TERM3_DDRC0_VAL                  0x00987000
 * #define DRAM_BYTE_MAP_DDRC0_VAL                   0x000000e4
 * #define DRAM_DQS_SYNC_DDRC0_VAL                   0x00001ea0
 * #define DRAM_ZQ_CALIB_DDRC0_VAL                   0x00000860
 * #define DRAM_DLL_CALIB_DDRC0_VAL                  0x001e3204
 * #define DRAM_SELF_REFRESH_DDRC0_VAL               0x00000001
 * #define DRAM_POWER_DOWN_DDRC0_VAL                 0x00000030
 * #define DRAM_MODE_REG_VAL                         0x00000010
 *
 * @endcode
 *
 * As there are too many parameters, select the last macro, DRAM_MODE_REG_VAL to display where
 * it is used in the BLD:<br>
 *
 * @code {.c}
 *
 * # For SDK 3.0
 * board $ cd ambarella/amboot
 *
 * # For Cooper SDK:
 * board $ cd ambarella/boot/amboot
 *
 * board $ grep -n "DRAM_MODE_REG_VAL" -r ./src | grep cv22
 * ./src/bst/cv22/parameters.S:167:dram_mode_param:                .int DRAM_MODE_REG_VAL
 *
 * board $ grep -n "dram_mode_param" -r ./src | grep cv22
 * ./src/bst/cv22/parameters.S:119:.globl dram_mode_param
 * ./src/bst/cv22/parameters.S:167:dram_mode_param:                .int DRAM_MODE_REG_VAL
 * ./src/bst/cv22/memsetup_lpddr4.S:59:    ldr     w0, dram_mode_param
 *
 * @endcode
 *
 * Before compiling Ambarella SDK, users can choose `.ini` file through “make menuconfig” in the SDK:<br>
 * @code {.c}
 *
 * # For SDK 3.0
 * Build $ make menuconfig
 *         [*] Ambarella Board Configuration --->
 *            [*] Board Revision (CV22 WALTNUT AUTO AQ76 with micron 16Git LPDDR4 @1392MHz) --->
 *
 * # For Cooper SDK:
 * Build $ make menuconfig
 *           boot --->
 *             amboot (boot/ambamk) --->
 *               Ambarella Firmware Configuration --->
 *                 Board --->
 *                   Board Revision (CV22 WALTNUT AUTO (AQ76 with micron 16Git LPDDR4 @1392MHz)) --->
 * @endcode
 *
 * The DRAM size also must be adjusted by changing MACRO “DRAM_SIZE”, which is defined in
 * `ambarella/boards/cv22_walnut/bsp/bsp.h`. The default value of this macro is 0x80000000 (2 GB).
 * Users must set it according to the real DDR capacity of the board.<br>
 *
 * @subsubsection new_board_bringup_modify_partition_size_flash 3.3.2 Modify Partition Flash Size
 *
 * The definition of each partition flash size is located in `ambarella/boards/cv22_walnut/bsp/bsp.h`.
 * Users can modify the sizes according to the actual capacity of storage media:<br>
 *
 * @code {.c}
 * #ifdef CONFIG_BOOT_MEDIA_SPINOR
 * #include "partition/spinor.h"
 * #elif defined(CONFIG_AMBARELLA_ROOTFS_CPIO)
 * #include "partition/cpio.h"
 * #elif defined(CONFIG_BOOT_MEDIA_EMMC)
 * #if defined(CONFIG_RTOS_MINDSP)
 * #include "partition/fastboot_emmc.h"
 * #else
 * #include "partition/emmc.h"
 * #endif
 * #elif defined(AMBOOT_THAW_HIBERNATION)
 * #include "partition/hibernation.h"
 * #elif defined(CONFIG_AMBARELLA_INIT_LINUXRC_FAST)
 * #include "partition/fastinit.h"
 * #elif defined(BUILD_FIRMWARE_RECOVERY)
 * #if defined(BUILD_AMBARELLA_ORYX_V2_SWAP_UPGRADE) || \
 *     defined(BUILD_AMBARELLA_ORYX_V2_UPGRADE_FIRMWARE_SIMPLE_SWAP_UPGRADE_DEMO) || \
 *     defined(BUILD_AMBARELLA_ORYX_V2_UPGRADE_FIRMWARE_SECURITY_SWAP_UPGRADE_DEMO)
 * #include "partition/swap_upgrade.h"
 * #elif defined(BUILD_AMBARELLA_ORYX_V2_PBA_UPGRADE) || \
 *       defined(BUILD_AMBARELLA_ORYX_V2_UPGRADE_FIRMWARE_SIMPLE_PBA_UPGRADE_DEMO) || \
 *       defined(BUILD_AMBARELLA_ORYX_V2_UPGRADE_FIRMWARE_SECURITY_PBA_UPGRADE_DEMO)
 * #include "partition/pba_upgrade.h"
 * #else
 * #include "partition/recovery.h"
 * #endif
 * #elif defined(CONFIG_RTOS_MINDSP)
 * #include "partition/fastboot_v5.h"
 * #else
 * #define AMBOOT_BST_SIZE		(AMBOOT_BST_FIXED_SIZE)
 * #define AMBOOT_BLD_SIZE		(AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PTB_SIZE		(AMBOOT_MIN_PART_SIZE * 7)
 * #define AMBOOT_ATF_SIZE		(AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PBA_SIZE		(16 * 1024 * 1024)
 * #define AMBOOT_PRI_SIZE		(16 * 1024 * 1024)
 * #define AMBOOT_SEC_SIZE		(0  * 1024 * 1024)
 * #define AMBOOT_BAK_SIZE		(0  * 1024 * 1024)
 * #define AMBOOT_RMD_SIZE		(0  * 1024 * 1024)
 * #define AMBOOT_ROM_SIZE		(0  * 1024 * 1024)
 * #define AMBOOT_DSP_SIZE		(0  * 1024 * 1024)
 * #define AMBOOT_LNX_SIZE		(144 * 1024 * 1024)
 * #define AMBOOT_SWP_SIZE		(0  * 1024 * 1024)
 * #define AMBOOT_ADD_SIZE		(12  * 1024 * 1024)
 * #define AMBOOT_ADC_SIZE		(0  * 1024 * 1024)
 * #endif
 *
 * @endcode
 *
 * For more information about flash partitions, users can refer to @ref si_fs and @ref si_nand.
 *
 * @subsubsection new_board_bringup_modify_gpio_configuration 3.3.3 GPIO Configuration
 *
 * There are two ways to configure general purpose input / output (GPIO).
 * - The first way is the legacy method, where the configurations are maintained in the `bsp.h` file.
 * - The second way is a new method, where the configurations are maintained in the device trees (DTS).
 *
 * The user can use "CONFIG_SUPPORT_OF_FDT" configuration. When this configuration is enabled, the new
 * method will be used. When disabled, the legacy method is used.
 *
 * For the legacy method, the user operation process is as follows:
 *   1. Based on the hardware design, generate the complete GPIO configurations. There is a dedicated
 *      Excel tool from Ambarella.
 *   2. Capture the GPIO configurations into the `bsp.h` under the board folder.
 *   3. Update the AMBoot or kernel modules to use these GPIOs when necessary.
 *   4. Generate a firmware, and apply the configurations.
 *
 * The working flow for the legacy method is as follows:
 *   1. AMBoot loads all the configurations in `bsp.h`, and sets to the hardware.
 *   2. AMBoot and Linux uses these initialized GPIOs for different purposes.
 *
 * The potential issues for the legacy method:
 *   - Users are required to generate the entire GPIO configuration map. It is easy 
 *     to make mistakes for GPIO settings.
 *   - These incorrect GPIO settings can cause potential hardware failures, or power increases.
 *   - Sometimes users directly copy GPIO configurations from the Ambarella evaluation kit (EVK)
 *     that do not match their board. Locating and fixing these hardware or power-related issues
 *     will take a long time.
 *
 * For the legacy method, the CV22 GPIO settings are located in `ambarella/boards/cv22_walnut/bsp/bsp.h`.
 * Ambarella provides an Excel tool to aid hardware engineers in configuring the GPIOs (column marked as red box 2
 * of the hardware page in @ref fig_gpio_mux_table "Figure 3-20").
 *
 * @anchor fig_gpio_mux_table
 * @image html board_bringup_pin_mux.png "Figure 3-20. GPIO Mux Table."
 *
 * If users encounter any issues while obtaining this tool, contact the Ambarella hardware support team for assitance.<br>
 *
 * After the application of each GPIO is configured properly, contents of the remaining four
 * pages (control, pull, IOMUX, and GPIO_DS) will be generated automatically. Then, users can
 * update these configurations into `ambarella/boards/cv22_walnut/bsp/bsp.h`.<br>
 *
 * @image html board_bringup_pin_mux_bsp.png "Figure 3-21. GPIO Configuration."
 *
 * For the new method, the user operation process is as follows:
 *   1. Configure the necessary GPIO configurations into the device tree.
 *   2. Update the AMBoot or kernel modules to use these GPIOs when necessary.
 *   3. For those unused GPIOs, it would be reserved as GPIO input and the configurations
 *      from device tree will be ignored.
 *
 * The working flow for the new method is as follows:
 *   1. AMBoot reads the used GPIO settings from the device tree, initializes the hardware
 *      and use it. Normally, AMBoot only reads.
 *   2. For those GPIO that are not configured in the device tree, they are initialized
 *      as "INPUT" and pulled to "LOW" by default.
 *   3. AMBoot and Linux uses these initialized GPIOs for different purposes.
 *
 * Improvements for the new method are as follows:
 *   - Users are only required to specify the necessary GPIO settings in the device tree.
 *     This avoids potential issues if the complete GPIO settings are incorrectly configured.
 *   - For these unused GPIOs, initializing to "INPUT" avoids unnecessary power consumptions.
 *
 * Normally AMBoot will only initialize NAND / SPIOR / eMMC related pins according to the
 * boot media. So these relevant GPIOs can be used in AMBoot. For example, if the boot media
 * is eMMC, then AMBoot loads and uses eMMC-related GPIO configurations.
 *
 * Compared with the legacy method, the new method only requires to ensure that the used GPIOs are properly
 * configured in the device tree.
 *
 * The following is an example of I2S configurations in the device tree.
 *
 *  @code {.c}
 *        i2s0: i2s@e001c000 {
 *                compatible = "ambarella,i2s";
 *                …
 *                pinctrl-names = "default";
 *                pinctrl-0 = <&i2s0_pins>;
 *                …
 *                status = "ok";
 *        };
 *        i2s0_pins: i2s0@0 {
 *               reg = <0>;
 *               amb,pinmux-ids = <0x1030 0x1031 0x1032 0x1033>;
 *        };
 *  @endcode
 *
 * So in AMBoot, the I2S pins will be configured as I2S mode, when the code below is called. And related GPIOs
 * will be parsed and configured.
 *  @code {.c}
 *      of_pin_init(of_find_node("ambarella,i2s"), "default");
 *  @endcode
 *
 * For Linux, the I2S pins will be configured as I2S mode, when status = "ok". But when status = "disabled",
 * the I2S pins then will not be configured as I2S mode, and related GPIOs will be parsed and configured.
 *
 *
 * @subsection new_board_bringup_configuration_instructions_of_kernel 3.4 Kernel Configuration Instructions
 *
 * The main function of configuring the kernel is to modify DTS. This can be divided into two parts:
 * common configuration of the SoC and specific configuration for the user’s board. This example uses the CV22 Walnut EVK board.<br>
 *
 *   - Common configuration: the corresponding DTS file is located in
 *     `ambarella/kernel/linux-$(kernle_version)/arch/arm64/boot/dts/ambarella/ambarella-cv22.dtsi`.
 *     For information regarding how to configure each node, users can refer to the kernel document
 *     `ambarella/kernel/linux-$(kernel_version)/Documentation/devicetree/bingings/arm/ambarella.txt`
 *   - Board-specific configuration: the corresponding DTS file is located in `ambarella/boards/cv22_walnut/bsp/cv22_walnut.dts`
 *
 * Further, @ref page_peripheral_main "Peripheral" provides instructions for usage of peripheral hardware
 * based on the Ambarella platform. <em>AMBARELLA_CV2x_HW_PRM.pdf</em> is the programming reference manual, which
 * provides a detailed description pf each module’s registers. Contact the ambarella hardware support team
 * to obtain this document.
 *
 * - - - -
 *
 * @section new_board_bringup_faq 4. FAQ
 *
 * @subsection new_board_bringup_can_not_enter_force_usb_mode 4.1 Board Cannot Enter into Force USB Mode
 *
 * -# Check if POC[10] is pulled high. To enter force USB mode, POC[10] must be pulled high.
 * -# Verify that the power sequence and power supply for each hardware are normal.
 * -# Check if POC[6] is pulled low. When POC[6] is pulled low, the secure boot feature will be
 *    enabled and the board cannot enter into force USB mode.
 * -# Check if POC[3:1] are configured. The configuration of POC[3:1] decides the clocks
 *    of main components (IDSP, VDSP, DRAM, VISION, and CORTEX) and system cannot boot up when POC[3:1]
 *    is not configured correctly.
 * -# Check if there are issues in the USB circuit design.
 *
 * The checks above should remedy the issue.
 * For more information on setting POCs, users can refer to <em>Ambarella_CV_POC_UG.pdf</em>.
 * Contact the Ambarella hardware support team to obtain this document.
 *
 * @subsection new_board_bringup_failed_to_test_memory 4.2 Failed to Perform Memory Test in AmbaUSB
 *
 * -# Verify that DDR power is normal.
 * -# Verify that the selection of the developing board (marked in a red box in the figure below) is correct.
 * -# Verify that the HDMI_REXT pin connects tightly. This pin cannot dangle because the chip current
 *    internal phase-locked loop (PLL) is obtained from this pin.
 *
 * @image html board_bringup_choose_board_configure.png "Figure 4-1. Board Selection in AmbaUSB."
 *
 * If the checks above do not resolve the issue, the problem may be related to the default DDR parameters
 * configured in the AmbaUSB tool. The parameters may not be suitable; contact the Ambarella
 * support team for help.
 *
 * - - - -
 *
 * @section board_bringup_license 5. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
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
 * - - - -
 *
 */

/*!
 * @file abbreviation.h
 * @brief This is a dummy header file for doxygen
 * @version 0.1
 * @date 2022-05-27
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
 * @page doc_abbr Glossary and Abbreviations
 * This page provides a table of abbreviations and terminologies used throughout
 * the Ambarella CV2x / CV5x Flexible Linux Software Development Kit (SDK).
 *
 * <table>
 * <caption id="ov_abbr_list"></caption>
 * <tr><th> Initial&nbsp;&nbsp;     <th> Abbreviation&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;     <th align="left"> Full Name
 * <tr><td rowspan="1" align="center"> 0-9
 *                  <td> 3A          <td> AE / AWB / ADJ
 * <tr><td rowspan="7" align="center"> A
 *                  <td> ADJ         <td> Auto adjustment
 * <tr>             <td> AE          <td> Auto exposure
 * <tr>             <td> AF          <td> Auto focus
 * <tr>             <td> AGC         <td> Automatic gain control
 * <tr>             <td> AR          <td> Aspect ratio
 * <tr>             <td> AVC         <td> Advanced video coding (H.264)
 * <tr>             <td> AWB         <td> Auto white balance
 * <tr><td rowspan="5" align="center"> B
 *                  <td> BLD         <td> Boot loader
 * <tr>             <td> BPC         <td> Bad pixel correction
 * <tr>             <td> BSB         <td> Bitstream buffer
 * <tr>             <td> BST         <td> Bootstrap
 * <tr>             <td> BW          <td> Bandwidth
 * <tr><td rowspan="15" align="center"> C
 *                  <td> CBR         <td> Constant bit rate (a rate control method)
 * <tr>             <td> CCM         <td> Color conversion matrix (converts color space, typically from the YUV domain to RGB domain)
 * <tr>             <td> CE          <td> Contrast enhancement
 * <tr>             <td> CEC         <td> Consumer electronics control
 * <tr>             <td> CFA         <td> Color filter array
 * <tr>             <td> CIF         <td> Common intermediate format; resolution is 352x288
 * <tr>             <td> CLUT        <td> Color look-up table
 * <tr>             <td> CMA         <td> Contiguous memory allocation
 * <tr>             <td> CMOS        <td> Complementary metal-oxide semiconductor
 * <tr>             <td> CNN         <td> Convolutional neural network
 * <tr>             <td> codec       <td> Refers to COmpressor / DECompressor or COder / DECoder
 * <tr>             <td> CTB         <td> Coding tree block (H.265 (HEVC) coding block)
 * <tr>             <td> CTU         <td> Coding tree unit (minimum coding unit of H.265 (HEVC))
 * <tr>             <td> CV          <td> Computer Vision
 * <tr>             <td> CVBS        <td> Composite video with blanking and sync (VOUT format)
 * <tr><td rowspan="7" align="center"> D
 *                  <td> DAG         <td> Directed acylic graphs
 * <tr>             <td> DCG         <td> Dual conversion gain (related to HCG-LCG)
 * <tr>             <td> DIS         <td> Digital image stabilization
 * <tr>             <td> DOL         <td> Digital overlap (HDR technology related to LEF-SEF)
 * <tr>             <td> DPTZ        <td> Digital pan / tilt / zoom
 * <tr>             <td> DRA         <td> Dynamic range analysis (CNN processing method)
 * <tr>             <td> DSP         <td> Digital signal processor
 * <tr><td rowspan="8" align="center"> E
 *                  <td> ECC         <td> Error-correcting code
 * <tr>             <td> EFM         <td> Encode from memory
 * <tr>             <td> EFR         <td> Encode from RAW
 * <tr>             <td> EIS         <td> Electronic image stabilization
 * <tr>             <td> EoF         <td> End of frame (describes the end of a VIN frame; similar to SoF)
 * <tr>             <td> ES          <td> Elementary stream (raw bitstream content without a file container)
 * <tr>             <td> EV          <td> Evaluation
 * <tr>             <td> EVK         <td> Evaluation kit
 * <tr><td rowspan="2" align="center"> F
 *                  <td> FoV         <td> Field of view
 * <tr>             <td> FPS         <td> Frames per second
 * <tr><td rowspan="2" align="center"> G
 *                  <td> GDC         <td> Geometry distortion correction (same as LDC)
 * <tr>             <td> GOP         <td> Group of pictures. (AVC / HEVC encode term)
 * <tr><td rowspan="3" align="center"> H
 *                  <td> HCG         <td> High-conversion gain (type of gain in sensor DCG mode)
 * <tr>             <td> HDR         <td> High dynamic range
 * <tr>             <td> HEVC        <td> High-efficiency video coding (H.265)
 * <tr><td rowspan="4" align="center"> I
 *                  <td> IAV         <td> Image audio video
 * <tr>             <td> ICE         <td> Inception convolution engine (hardware block inside the vision processor)
 * <tr>             <td> IDR         <td> Instantaneous decoding refresh (AVC / HEVC frame type)
 * <tr>             <td> ISO         <td> Light sensibility ordinance
 * <tr><td rowspan="3" align="center"> L
 *                  <td> LCG         <td> Low conversion gain (type of gain in sensor DCG mode)
 * <tr>             <td> LEF         <td> Long exposure frame (type of frame in sensor DOL-HDR mode)
 * <tr>             <td> LDC         <td> Lens distortion correction (same as GDC)
 * <tr><td rowspan="6" align="center"> M
 *                  <td> MB          <td> Macroblock (H.264 (AVC) coding block)
 * <tr>             <td> MCTF        <td> Motion-compensated temporal filter
 * <tr>             <td> MD          <td> Motion detection
 * <tr>             <td> ME          <td> Motion estimation (codec term)
 * <tr>             <td> MMB         <td> Memory management block
 * <tr>             <td> MV          <td> Motion vector (codec term)
 * <tr><td rowspan="1" align="center"> N
 *                  <td> NTP         <td> Network time protocol
 * <tr><td rowspan="2" align="center"> O
 *                  <td> Oryx        <td> Camera middleware in the Linux SDK
 * <tr>             <td> OSD         <td> Onscreen display (means that the content is displayed onscreen above the video layer)
 * <tr><td rowspan="2" align="center"> P
 *                  <td> PM          <td> Privacy mask
 * <tr>             <td> PWC         <td> Power controller
 * <tr><td rowspan="2" align="center"> Q
 *                  <td> QP          <td> Quantization parameter. (AVC / HEVC encoding term)
 * <tr>             <td> QPM         <td> QP matrix (controls AVC / HEVC encode quality; MB- or CTB-level)
 * <tr><td rowspan="4" align="center"> R
 *                  <td> RC          <td> Rate control
 * <tr>             <td> RGB-IR      <td> Red / green / blue / infrared (CMOS sensor format)
 * <tr>             <td> ROI         <td> Region of interest
 * <tr>             <td> RTC         <td> Real-time clock
 * <tr><td rowspan="7" align="center"> S
 *                  <td> SDK         <td> Software development kit
 * <tr>             <td> SEF         <td> Short exposure frame (type of frame in sensor DOL-HDR mode)
 * <tr>             <td> SNR         <td> Signal-noise ratio
 * <tr>             <td> SoC         <td> System on chip
 * <tr>             <td> SoF         <td> Start of frame (describe the start of the VIN frame; similar to EoF)
 * <tr>             <td> SPU         <td> Stereo processing unit
 * <tr>             <td> SVC         <td> Scalable video coding. (AVC / HEVC encoding term)
 * <tr><td rowspan="1" align="center"> W
 *                  <td> WDT         <td> Watchdog timer
 * <tr><td rowspan="1" align="center"> Z
 *                  <td> ZMV         <td> Zero motion vector (related to MV)
 * </table>
 *
 */
