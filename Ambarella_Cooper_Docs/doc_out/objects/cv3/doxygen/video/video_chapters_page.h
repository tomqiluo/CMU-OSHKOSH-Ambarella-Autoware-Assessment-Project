/*!
 * @file vin.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_vin BASIC - Video Input
 *
 * @section section_vsrc_features 1. Video Input Features
 *
 * This section describes video input (VIN) features, such as frame rate, bit rate, and resolution.
 *
 * CV5x / CV72 receives the video input and send it to the VIN controller.
 * Once the video source is ready, CV5x / CV72 then distributes the video source to the
 * @ref fs_basic_source_buffer "source buffer" for "preview" and / or "encode" purposes.
 *
 * @image html video_input_pipeline.png "Figure 1-1. Video Process Pipeline."
 *
 *
 * @subsection vsrc_resolution 1.1 Resolution
 *
 * Typically, the sensor supports multiple resolutions. Users can choose different
 * resolutions according to their requirements.
 *
 * By default, the maximum supported VIN resolution for CV5x is <B>7680x4320</B>, and
 * the maximum supported VIN resolution for CV72 is <B>3840x2160</B>.
 *
 *
 * @subsection vsrc_frame_rate 1.2 Frame Rate
 *
 * Users can control the frame rate of a sensor for different resolutions.
 *
 * @subsection vsrc_mirror_filp 1.3 Mirror / Flip
 *
 * The VIN controller supports performing mirror / flip operations on the input video source.
 *
 * @subsection vsrc_hdr 1.4 High Dynamic Range Mode
 *
 * Users can apply high dynamic range (HDR) on the input video source, including HDR 2x and HDR 3x.
 *
 * @subsection vsrc_yuv 1.5 YUV Input
 *
 * The VIN controller processes YUV data. The following image demonstrates two typical usages for
 * YUV input. In the first case, a high-definition multimedia interface (HDMI®) signal is converted
 * into YUV format via LT6911. In the second case, a native YUV sensor is supported by the VIN
 * controller. For the first case, an advanced feature is supported: users can connect multiple
 * YUV resolution inputs on the fly. Each time when connecting a new YUV resolution input, users
 * should perform a recovery first and then revise the main buffer input resolution.
 *
 * @image html video_input_yuv.png "Figure 1-2. YUV Input."
 *
 *
 * @subsection vsrc_multi_vin 1.6 Multi-VIN
 *
 * The Cooper family of chips supports multiple independent sensors, as they are equipped with more
 * than one VIN controller. They support independent 3A (auto white balance (AWB) / auto exposure (AE) / auto focus (AF)) control processes for each VIN.
 * This enables the camera to function as if there are multiple independent cameras operating
 * within a single system on chip (SoC).
 *
 * The figure below shows two real VINs and a virtual VIN.
 *
 * @image html multi_vin_controller.png "Figure 1-3. Multi-VIN."
 *
 * The table below lists the number of VIN controllers for each chip in the Cooper family.
 * <table>
 * <caption id="table_vsrc_lua">Table 1-1. Number of VIN Controllers in the Cooper family.</caption>
 * <tr><th> Chip
 * <th> <div style="width:240px"><B>VIN Controller</B></div>
 * <th> <div style="width:240px"><B>Virtual VIN</B></div>
 * <tr><td> CV5   <td align="center"> 14 <td align="center"> 12
 * <tr><td> CV52  <td align="center"> 14 <td align="center"> 12
 * <tr><td> CV72  <td align="center"> 10 <td align="center"> 12
 * </table>
 *
 * <br>
 *
 * @subsection vin_vout_precise_sync 1.7 VIN-VOUT Precise Synchronization
 * In some use cases (such as video conference), there should be no repeated / skipped VIN frames on
 * in the video output (VOUT), which means that each VIN frame should be displayed on VOUT.
 * However, VIN and VOUT do not share the same clock source, so there is a small difference in the frames per second (fps)
 * between the two. This difference leads to repeated / skipped frames on VOUT after a period of time.
 *
 * For example, if users set VIN / image digital signal processor (IDSP) / VOUT to 30.000 fps,
 * the real VIN fps is 29.999 on the VOUT clock due to the different clock sources. Users will observe a repeated frame
 * on VOUT about every 33.3 seconds (1/(30.000-29.999)=1000 frames).
 *
 * The VIN-VOUT precise syncronization feature adjusts the VIN fps dynamically according to the observed VOUT fps
 * information. This closed-loop feedback system aids maintaining the same frame rate for both VIN and VOUT.
 *
 * @note
 * - This feature depends on the VOUT message from the digital signal processor (DSP), which is reported
 * from the DSP by default. Additionally, users must enable "vin-precise-sync" when entering the preview state.
 * - This feature only supports VIN / IDSP / VOUT in the same fps.
 * - This feature only supports the cases below, and only adjusts the VIN fps, which is the source of the VOUT.
 * <table>
 * <caption id="table_vin_precise_sync_supported_casess">Table 1-2. VIN Precise Sync Support Cases.</caption>
 * <tr><th> Cases
 * <th> Description
 * <tr><td> Single VIN and single VOUT <td> Adjust VIN fps dynamically according to the VOUT fps
 * <tr><td> Single VIN and multiple VOUT <td> Users should set "sync-first-vout-frame-mode = 3" first when entering
 * the preview state. This means that DSP will keep VOUT0 synchronized with VOUT1. The driver tunes the VIN fps dynamically
 * according to VOUT0's fps to prevent any repeated / skipped frames on both VOUT0 and VOUT1.
 * See @ref example_first_vout_frame_sync_mode
 * <tr><td> Multiple VIN and single VOUT <td> If VOUT is from one VIN, adjust the single VIN fps dynamically according
 * to the VOUT fps. If VOUT is from multiple VINs, users should first maintain the multi-VIN synchronization
 * <tr><td> Multiple VIN and multiple VOUT, and each VOUT is from different VINs <td> Adjust the VIN fps dynamically
 * according to the VOUT fps
 * </table>
 *
 * See @ref example_vin_vout_precise_sync "VIN-VOUT Precise Sync".
 *
 * @subsection cam_seamless_switch 1.8 Camera Seamless Switch (CSS)
 *
 * To meet user requirements (especially for multi-VIN cases), if one VIN is disabled or broken,
 * the DSP can still enter the preview with that specific VIN. The disabled / broken VIN can switch
 * to enable (or recover) on the fly if the user connects an active sensor to the video
 * source (VSRC). If there are other active channels running in parallel, this channel runtime
 * switch does not affect other channels.
 *
 * @note
 * - When the DSP enters the preview with a broken VIN, the buffer from the broken VIN is filled
 *   with a black privacy mask (PM). The user must specify the option "vsrc_status = 1"
 *   for the broken VIN when the DSP enters the preview, and specify the memory for a single-color PM.
 * - If the user starts encoding from the broken VIN, the encoding fps is not guaranteed.
 * - If the VIN is suddenly broken during the preview or encode state, the VIN-related buffers
 *   will also be filled with a black PM.
 *
 * See @ref example_broken_vin "Enter Preview with a Broken VIN Example".
 *
 * @subsection vin_repeat_frame 1.9 VIN repeat frame
 * DSP can repeat previous good frame when there is VIN short line or short frame error.
 * Short line error is usually caused by VIN interface h/w signal issue.
 *
 * For example, there is noise or static interference on VIN interface. This error will make DSP hang.
 * The image audio video (IAV) introduces the feature of checking short line to detect this issue,
 * and replaces the "broken frame" with a duplicated previous good frame.
 *
 * See @ref example_vin_repeat_frm "VIN repeat frame".
 *
 * @subsection scale_VIN 1.10 Scale VIN
 * Scale VIN is only supported on CV72 with VIN0. Scale VIN is doing downscale from original RAW input
 * to generate a smaller RAW, which can save the IDSP performance and DRAM bandwidth. Users can enable scale
 * VIN by setting the option "scale_type". Scale VIN is not supported with YUV input.
 *
 * For example, when there is a 8MP sensor input, users can specify the option "scale_type = 1" to get
 * a 2MP raw. Specify "scale_type = 1" can do 2X downscale for both VIN width and height. For introductions on
 * all supported scale type, refer to @ref lua_vsrc_configuration " Video Input Configuration".
 *
 * See @ref example_scale_VIN "Scale VIN".
 *
 * @subsection Roi_VIN 1.11 ROI VIN
 * ROI VIN is supported on CV5x / CV72. User can get several cropped vin from original RAW input.
 * ROI VIN can also save IDSP performance and DRAM bandwidth. The maximum supported ROI VIN number depends
 * on virtual VIN number extended from one real VIN. Users can specify the option "roi_enable = 1"
 * to enable ROI VIN, and specify "roi_list" for each ROI VIN windows. The option "vin_roi_idx" in
 * channel configuration specify the index of ROI VIN in "roi_list". ROI VIN is not supported
 * with YUV input.
 *
 * For example, when there is a 8MP sensor input, users can specify the option "roi_enable = 1"
 * and "roi_list = {{480, 480, 1920, 1080},}" to get a cropped 2MP raw, which the offset is {480, 480}.
 *
 * See @ref example_Roi_VIN "Roi VIN".
 *
 * @subsection dual_vin_slice 1.12 Dual VIN Slicing
 * To get lower pipeline latency, we supports dual vertical slicing for sensor raw on mode 0.
 * The sensor raw image will be cut into top and bottom slices. Once the top slice is
 * captured by VINC, it will be fed into IDSP right away for the next processing.
 * Benefit from this, the pipeline latency can reduce by around half frame time
 * (slightly smaller due to vertical padding) comparing with single idsp slice.
 *
 * The figure below briefly illustrates the workflow of dual vertical slicing.
 * As shown in the figure, when the raw data in vinc reaches the position of the
 * dotted line (The height of each slice is calculated by dividing the raw height by the idsp vertical slice number),
 * vinc will grab the top slice data and send it to the next processing session of IDSP.
 * Then, the rest of a frame's data is sent to the next IDSP session by the vinc
 * after it has been fully received.
 *
 * @image html dual_vin_slice.png "Figure 1-4. dual vin silcing."
 *
 * The following parameters need to be configured to enable low delay vout.
 * The idsp vertical slice num(ver_slice_num) and raw slice num must be set to the same value, we only support 2 vertical slices now.
 * We also need to set "low_delay_enable = 1" on the prev canvas to enable low delay vout.
 * @code
 * chan_0 = {
 *	....
 *	ver_slice_num = 2,
 *	raw_padding_height = 0,
 *	raw_slice_num = 2,
 *	....
 * }
 * 
 * canvas = {
 * ....
 *    {
 *	     type = "prev",
 *	     ...
 *	     low_delay_enable = 1,
 *    },
 * ....
 * }
 * @endcode
 *
 * The following is a comparison of vin-vout latency with low-delay disabled and enabled.
 *
 * @code
 * Resolutoin: vin-4k, vout-1080p; FPS: vin = vout = 60; IDSP core mdoe: single core.
 *
 * ======= Audit video info within 300s ========
 *
 * 2x idsp vertical slice:
 * === [VOUT-VIN Latency Info] : From "raw capture done" to "vout display start"
 * Vout     Canvas     Sync Cnt     Avg (us)     Max (us)     Min (us)   Delta (us)
 * 2        2          18657        15529        23607        6941       16666
 *
 * 1x idsp vertical slice:
 * === [VOUT-VIN Latency Info] : From "raw capture done" to "vout display start"
 * Vout     Canvas     Sync Cnt     Avg (us)     Max (us)     Min (us)   Delta (us)
 * 2        2          18779        25389        33426        16759      16667
 * @endcode
 *
 * From the audit results, we can see that the average vin-vout latency is reduced by about 10ms.
 *
 * ---
 *
 * @section lua_vsrc_configuration 2. Video Input Configuration
 *
 * Users can configure the video source via Lua script. Each input source is configured as an independent
 * "VSRC" instance in the Lua script. Each VSRC can have a different resolution, frame rate,
 * HDR mode, and more. Below are the VSRC parameters.<br>
 *
 * <table>
 * <caption id="table_vsrc_lua"><B>Table 2-1. Parameters for VIN Configuration.</B></caption>
 * <tr><th>Item <th><div style="width:120px"><B>Parameter</B></div> <th>Description
 * <tr><td> @anchor anchor_vsrc_id vsrc_id
 *     <td> id >= 0
 *     <td> Specifies the sensor input ID. Ambarella suggests keeping the
 *          same value as the sensor index, which is automatically generated during the
 *          sensor driver probe process that corresponds to a real sensor
 * <tr><td> @anchor anchor_vsrc_status vsrc_status
 *     <td> 0 (default): active <br>
 *          1: broken or not-connected
 *     <td> Specifies if the sensor is active or broken / not connected
 * <tr><td> @anchor anchor_vsrc_mode mode
 *     <td> Resolution mode
 *     <td> Specifies the sensor resolution mode
 * <tr><td> hdr_mode
 *     <td> "linear", "2x", "3x"
 *     <td> Specifies the HDR mode for the input sensor
 * <tr><td> fps
 *     <td> fps >= 1
 *     <td> Specifies the frame rate of the video source
 * <tr><td> max_fps
 *     <td> 1 <= max_fps <= 480
 *     <td> Specifies the maximum frame rate of the video source
 * <tr><td> vsrc_ctx_switch
 *     <td> 0: disable <br>
 *          1: enable
 *     <td> Specifies the sensor register context's auto-switch flag; it only functions
 *          for some sensors (such as AR0230 and AR0237) which support
 *          multiple register groups of the shutter and automatic gain control (AGC)
 * <tr><td> @anchor anchor_vsrc_bit bit
 *     <td> 0: auto <br>
 *          8~16: pixel depth
 *     <td> Specifies the sensor RGB bits
 * <tr><td> Mirror
 *     <td> 0: none <br>
 *          1: flip <br>
 *          2: mirror <br>
 *          3: mirror and flip
 *     <td> Specifies the sensor mirror pattern
 * <tr><td> bayer
 *     <td> 0: RG <br>
 *          1: BG <br>
 *          2: GR <br>
 *          3: GB <br>
 *          255: AUTO
 *     <td> Specifies the sensor Bayer pattern
 * <tr><td> virt_mode_cfg_enable
 *     <td> 0: disable <br>
 *          1: enable
 *     <td> Specifies the virtual sensor mode customization flag
 * <tr><td> virt_mode_cfg
 *     <td> virt_mode_cfg_{vsrc_id}
 *     <td> Specifies the virtual sensor mode Lua structure; it only takes effect when virt_mode_cfg_enable is set to 1
 * <tr><td> scale_type
 *     <td> 0: no scale <br>
 *          1: 1/2 for both width and height <br>
 *          2: 1/4 for width and 1/2 for height <br>
 *          3: 1/2 only for width <br>
 *          4: 1/4 only for width
 *     <td> Specifies the vin scale type
 * <tr><td> roi_enable
 *     <td> 0: disable <br>
 *          1: enable
 *     <td> Flag to enable roi VIN
 * <tr><td> roi_list
 *     <td> {{offset_x, offset_y, width, height}} <br>
 *     <td> Specifies the crop window of each roi VIN
 * </table>
 *
 * For encode from RAW (EFR) cases, the RAW data files are fed to VIN buffer via dummy sensor.
 * Dummy sensor is implemented through the "ambds" driver, it is designed to simulate real sensor,
 * users can configure the virtual VIN mode via lua script.
 * -# Each virtual VIN mode corresponds to a specific VSRC instance in the Lua script.
 * -# Each virtual VIN mode can have a different resolution, frame rate, high dynamic range (HDR) mode,
 *    video type, and so on. Below are the parameters for virtual VIN mode.<br>
 *
 * <table>
 * <caption id="table_virt_mode_cfg_lua">Table 2-2. Parameters for Virtual VIN Mode.</caption>
 * <tr><th>Item <th><div style="width:120px"><B>Parameter</B></div> <th>Description
 * <tr><td> @anchor anchor_vsrc_id width
 *     <td> width >= 0
 *     <td> VSRC output window width
 * <tr><td> @anchor anchor_vsrc_status height
 *     <td> height >= 0
 *     <td> VSRC output window height
 * <tr><td> hdr_mode
 *     <td> "linear", "2x", "3x"
 *     <td> Specifies HDR mode for the virtual sensor
 * <tr><td> default_fps
 *     <td> fps >= 1
 *     <td> Specifies the default frame rate of the virtual sensor
 * <tr><td> max_fps
 *     <td> 1 <= max_fps <= 480
 *     <td> Specifies the maximum frame rate of the virtual sensor
 * <tr><td> @anchor anchor_vsrc_bit bits
 *     <td> 8~16: pixel depth
 *     <td> Specifies the virtual sensor RGB bits
 * <tr><td> hdr_offset_long
 *     <td> hdr_offset_long >= 0
 *     <td> Line offset of the longest exposure frame
 * <tr><td> hdr_offset_short1
 *     <td> hdr_offset_short1 >= 0
 *     <td> Line offset of the medium exposure frame
 * <tr><td> hdr_offset_short2
 *     <td> hdr_offset_short2 >= 0
 *     <td> Line offset of the above medium exposure frame
 * <tr><td> hdr_offset_short3
 *     <td> hdr_offset_short3 >= 0
 *     <td> Line offset of the shortest exposure frame
 * <tr><td> sensor_id
 *     <td> sensor_id >= 0
 *     <td> Specifies the sensor_id of the virtual sensor
 * <tr><td> agc_db_step
 *     <td> agc_db_step >= 0
 *     <td> Specifies the agc_db_step of the virtual sensor
 * <tr><td> dual_gain_mode
 *     <td> 0: off <br>
 *			1: HCG LCG <br>
 *			2: DCG (HCG+LCG combined)
 *     <td> Flag to indicate if the current VIN supports dual-gain mode
 * <tr><td> video_type
 *     <td> "yuv_601" <br>
 *			"yuv_656" <br>
 *			"rgb_601" <br>
 *			"rgb_656" <br>
 *			"rgb_raw" <br>
 *			"yuv_bt1120" <br>
 *			"rgb_bt1120"
 *     <td> Specifies the video type of the virtual sensor
 * </table>
 *
 * <B>Example for Video Source Lua Configuration</B><br>
 *
 * @code
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 30,
 *    max_fps = 60,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 *
 * vsrc_1 = {
 *    vsrc_id = 1,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 30,
 *    max_fps = 60,
 *    bits = 0,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 * @endcode
 *
 * <B>Example Virtual Sensor Mode Configuration for Dummy Sensor Lua Configuration</B><br>
 *
 * @code
 * virt_mode_cfg_0 = {
 *	 width = 1920,
 *	 height = 1080,
 *	 bits = 12,
 *	 max_fps = 30,
 *	 default_fps = 30,
 *	 hdr_mode = "linear",
 *	 video_type = "rgb_raw", -- options: "yuv_601", "yuv_656", "rgb_601", "rgb_656", "rgb_raw", "yuv_bt1120", "rgb_bt1120"
 *	 sensor_id = 0x3014,
 *	 agc_db_step = 0x00180000,
 * }
 *
 * vsrc_0 = {
 *	vsrc_id = 0,
 *	vsrc_status = 0,
 *	mode = "1080p",
 *	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *	fps = 30,
 *	vsrc_ctx_switch = 0,
 *	bits = 0,
 *	virt_mode_cfg_enable = 1,
 *	virt_mode_cfg = virt_mode_cfg_0,
 * }
 * @endcode
 *
 * @note
 *   - The virt_mode_cfg setting takes effect only when virt_mode_cfg_enable in the VSRC configuration
 *     is set to 1 and VSRC is a virtual sensor.
 *   - When loading the ambds driver, the custom_format_enable parameter must be set to 1.
 *
 * For more use cases for virtual VIN mode and the EFR feature,
 * refer to @ref custom_virtual_vin_mode "Custom virtual VIN mode".<br>
 *
 * ---
 *
 * @section section_vsrc_example 3. Video Input Examples
 *
 * @note
 * Ambarella highly recommends changing all parameters by modifying the Lua scripts.
 *
 * @subsection example_vsrc_resolution Example 1: Resolution Control
 *
 * First, initialize the evaluation kit (EVK) board to load the essential drivers and microcode,
 * and start the 3A statistics if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * @endcode
 *
 * @par Resolution 1920x1080
 *
 * The 'test_encode' readout message shows all supported VIN modes and the current
 * active mode.
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 * @par Resolution 2592x1944
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_5m_2592x1944_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_5m_2592x1944_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * @subsection example_vsrc_frame_rate Example 2: Frame Rate Control
 *
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start the 3A statistics if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * @endcode
 *
 * @par Frame Rate 25
 *
 * Modify the Lua file for 25 fps.
 *
 * @code {.c}
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 25,
 *    max_fps = 0,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 * @par Frame Rate 30
 *
 * Modify the Lua file for 30 fps.
 *
 * @code {.c}
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 30,
 *    max_fps = 0,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 * @par Frame Rate 60
 *
 * Modify the lua file for 60 fps.
 *
 * @code {.c}
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 60,
 *    max_fps = 0,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 *
 * @subsection example_vsrc_mirror_filp Example 3: Mirror / Filp
 * Initialize the EVK board to load the essential drivers and microcode,
 * and start the 3A statistics if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * @endcode
 *
 * Set mirror and filp mode.
 *
 * Modify the Lua file for mirror and flip mode.
 *
 * @code {.c}
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 60,
 *    max_fps = 0,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 1,
 *    bayer = 0,
 * }
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 * @note
 * Not all sensors support VIN mirror / flip.
 *
 * @subsection example_vsrc_yuv Example 4: YUV Input using LT6911
 *
 *
 * @par Hardware and Software Environment
 *
 * This example has been tested with CV5 Timn board and can be easily ported
 * to any other supported device and development board. In order for the test case to function,
 * users must perform the following:
 * - Board 1 generates HDMI output. Insert the IMX274 MIPI® sensor into the VIN slot
 *   on the board. Log into Board 1 via Telnet and set up the board to preview.
 *   state. The HDMI signal then will be converted to YUV data by LT6911.
 * - Insert LT6911 into the VIN slot on Board 2. Connect Board 2 to a monitor
 *   with HDMI interface. Log into the Board 2 via serial console.
 *
 * @image html sample_vin_lt6911.png "Figure 3-1. LT6911 Hardware Connection."
 *
 * @par Command Step by Step
 *
 * For YUV input, the correct 3A bin files are still required by `test_aaa_service`.
 * Use the commands below to verify if those bin files are included.<br>
 * For Cooper SDK Amba build:
 * @code {.c}
 * build$ make menuconfig
 *        -> packages
 *           -> idsp
 *              [*] sensor-datas@virtual (packages/idsp/data/img_cv5x)
 *                  [*]   ipc-sensor-datas@virtual (packages/idsp/data/img_cv5x/IPC)
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambalib
 *              -> sensor-datas@virtual (meta-ambalib/recipes-sensor)
 *                 [*]   ipc-sensor-datas@virtual (meta-ambalib/recipes-sensor/IPC)
 * @endcode
 * Then, `/usr/share/ambarella/idsp/ipc/cc_bins/yuv_input_3D.bin`,
 * `/usr/share/ambarella/idsp/ipc/adj_params/yuv_input_liso_adj_param_ipc.bin`,
 * and `/usr/share/ambarella/idsp/ipc/adj_params/yuv_input_aeb_param_ipc.bin` are generated.<br>
 *
 * Set up a 1080P HDMI output on any board. This example uses the CV22 Walnut EVK
 * to generate HDMI output.
 *
 * @code {.c}
 * board_cv22# init.sh --imx274_mipi
 * board_cv22# test_aaa_service -a &
 * board_cv22# test_encode -i 0 --hdmi 1080p
 * @endcode
 *
 * For Board 2:<br>
 * An Example for Video Source Lua Configuration
 * @code {.c}
 * vsrc_0 = {
 * 	vsrc_id = 0,
 * 	mode = "0",
 * 	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 * 	fps = 30,
 * 	bits= 0,
 * }
 * ...
 * chan_0 = {
 * 	...
 * 	main = {
 *		max_output = {0, 0}, -- output width
 *		input      = {0, 0, 0, 0}, -- full VIN
 *		output     = {0, 0, 1920, 1080},
 *	},
 *	...
 * }
 * @endcode
 *
 * @code {.c}
 * board_cv5# init.sh --na
 * board_cv5# modprobe lt6911 vinc_id=8 bus_id=3
 * board_cv5# test_aaa_service -a &
 * board_cv5# test_encode --resource-cfg example_1080p.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1
 * IAVIOC_S_IDLE done
 * mode = 13, fps = 60000, interlaced = 0
 *
 * Find Vin Source lt6911 Channel[lt6911]'s type is HDMI
 * The signal is:
 *         1920x1080P(Linear)      60      YUV BT656       8bits   16:9    AUTO    rev[0]
 * Active src 0's mode is:
 *         1920x1080P(Linear)      60      YUV BT656       8bits   16:9    AUTO    rev[0]
 * init_vin done
 * @endcode
 *
 * @par Enable 4K YUV Input
 *
 * The Cooper software development kit (SDK) supports 4K input. In order to use 4K YUV input, set up the CV22 Walnut
 * Board 1 with 4K HDMI output.
 *
 * @code {.c}
 * board_cv22# init.sh --imx274_mipi
 * board_cv22# test_aaa_service -a &
 * board_cv22# test_encode -i0 --hdmi 2160p30 -X --bsize 3840x2160 --bmaxsize 3840x2160 --vout-profile 1
 * @endcode
 *
 * Then, set up Board 2 the same as before.<br>
 * An Example for Video Source Lua Configuration:
 * @code {.c}
 * vsrc_0 = {
 * 	vsrc_id = 0,
 * 	mode = "0",
 * 	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 * 	fps = 30,
 * 	bits= 0,
 * }
 * ...
 * chan_0 = {
 * 	...
 * 	main = {
 *		max_output = {0, 0}, -- output width
 *		input      = {0, 0, 0, 0}, -- full VIN
 *		output     = {0, 0, 3840, 2160},
 *	},
 *	...
 * }
 * @endcode
 *
 * @code {.c}
 * board_cv5# init.sh --na
 * board_cv5# modprobe lt6911 vinc_id=8 bus_id=3
 * board_cv5# test_aaa_service -a &
 * board_cv5# test_encode --resource-cfg example_4k.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1
 * IAVIOC_S_IDLE done
 * mode = 13, fps = 60000, interlaced = 0
 *
 * Find Vin Source lt6911 Channel[lt6911]'s type is HDMI
 * The signal is:
 * The signal is:
 *         3840x2160P(Linear)      30      YUV BT656       8bits   16:9    AUTO    rev[0]
 * Active src 0's mode is:
 *         3840x2160P(Linear)      30      YUV BT656       8bits   16:9    AUTO    rev[0]
 * init_vin done
 * @endcode
 *
 * @subsection example_vin_vout_precise_sync Example 5: VIN-VOUT Precise Sync
 * To enable the VIN-VOUT precise syncronization feature, users must specify "--vin-precise-sync-enable 1".
 * The steps below use CV5 as an example:
 *
 *
 * Modify the Lua file for 1080p60 mode.
 *
 * @code {.c}
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 60,
 *    max_fps = 0,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 * @endcode
 *
 * @code {.c}
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vin-precise-sync-enable 1
 * @endcode
 *
 * Users can use "debug-audit-vv-delay" to show VOUT-VIN delay, which is used to
 * verify if this feature takes effect. When VOUT-VIN delay is in the range
 * (N, N+1) x one VOUT frame time (N is different for different encode mode), it
 * means that this feature takes effect. See @ref example4_audit_function
 * "VOUT-VIN Delay Audit Function".
 *
 * @subsection example_vin_VGA480_FPS Example 6: VIN 480 fps
 * Users must run this case with a sensor that supports 480 VIN fps, such as IMX422,
 * and enable the corresponding sensor support configuration in menuconfig.
 * The example below is verified with the CV5 platform.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> platform
 *              -> vin
 *                 -> sensors
 *                    [*] kernel-module-imx422 (drv_modules/platform/vin/sensors/sony_imx422)
 * @endcode
 *
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-sensor
 *                 [*] kernel-module-imx422 (meta-ambabsp/recipes-sensor/kernel-module-imx422)
 *
 * @endcode
 * Specify the VIN fps and resolution, as well as the corresponding canvas and stream.
 * Refer to <a href="script/vin0_VGA_linear_480fps.lua" target="_blank"><b>vin0_VGA_linear_480fps.lua</b></a>.
 *
 * @code {.c}
 * board# init.sh --na;
 * board# insmod /lib/modules/$(uname -r)/extra/imx422.ko bus_id=3 vinc_id=8 addr=0x1a
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg vin0_VGA_linear_480fps.lua --enc-mode 0
 * board# test_encode -A -h 640x480 -b 0 -e
 * board# test_stream -A --no
 * board# cat /proc/interrupts | grep vin8 && sleep 1 && cat /proc/interrupts | grep vin8
 * @endcode
 *
 * @subsection example_vin_8k Example 7: Single 8K VIN Case
 *
 * This example has been tested with the CV5 platform and can be easily ported
 * to any other supported device and development board.<br>
 * Users must run this case with a sensor that supports 8K VIN, such as IMX586 / IMX492 / IMX455,
 * and enable corresponding sensor support configuration in menuconfig.<br>
 *
 * @par 8K VIN with IMX586
 *
 * @par Hardware and Software Environment
 *
 * Use the commands below to enable the IMX586 sensor.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> platform
 *              -> vin
 *                 -> sensors
 *                    [*] kernel-module-imx586-mipi (drv_modules/platform/vin/sensors/sony_imx586_mipi)
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-sensor
 *                 [*] kernel-module-imx586-mipi (drv_modules/platform/vin/sensors/sony_imx586_mipi)
 * @endcode
 *
 * Modify the dual in-line package (DIP) settings and jumpers on the CV5 Timn board, as shown in the figure below.
 *
 * @image html example_vin_8k_switches_config.png "Figure 3-2. Switches SW1-SW5 Configuration."
 *
 * Insert the IMX586 sensor into the VIN DCPHY slot on the CV5 Timn board shown in the figure below.
 *
 * @image html example_vin_8k_insert_imx586.png "Figure 3-3. Insert IMX586 Sensor in VIN DCHPY0 / DCHPY1."
 *
 * Enter the preview with the following commands:
 *
 * @code {.c}
 * board# init.sh --na;
 * board# modprobe imx586_mipi vinc_id=0 bus_id=5 cphy=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_8k_linear.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @note
 * The second command should be '# modprobe imx586_mipi vinc_id=0 bus_id=5.' if the sensor is designed for MIPI D-PHY.
 *
 * @par 8K VIN with IMX492
 *
 * @par Hardware and Software Environment
 *
 * Use the commands below to enable the IMX492 sensor.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *       -> drv_modules
 *          -> platform
 *             -> vin
 *                -> sensors
 *                   [*] kernel-module-imx492 (drv_modules/platform/vin/sensors/sony_imx492)
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-sensor
 *                 [*] kernel-module-imx492 (meta-ambabsp/recipes-sensor/kernel-module-imx492)
 *
 * @endcode
 * Modify the DIP settings and jumpers on CV5 Timn board, as shown in the figure below.
 *
 * @image html example_vin_8k_switches_config.png "Figure 3-4. Switches SW1-SW5 Configuration."
 *
 * Insert the IMX492 sensor into the VIN SLVS-EC slot on the CV5 Timn board, as shown in the figure below.
 *
 * @image html example_vin_8k_insert_imx492.png "Figure 3-5. Insert IMX492 Sensor in VIN SLVS-EC."
 *
 * Enter the preview with the following commands:
 *
 * @code {.c}
 * board# init.sh --na;
 * board# modprobe imx492 bus_addr=0x30000
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_8k_linear.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @par 8K VIN with IMX455
 *
 * @par Hardware and Software Environment
 *
 * Use the commands below to enable the IMX455 sensor.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> platform
 *              -> vin
 *                 -> sensors
 *                    [*] kernel-module-imx455 (drv_modules/platform/vin/sensors/sony_imx455)
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-sensor
 *                 [*] kernel-module-imx455 (drv_modules/platform/vin/sensors/sony_imx455)
 * @endcode
 *
 *
 * Modify the DIP settings and jumpers on the CV5 Timn board, as shown in the figure below.
 *
 * @image html example_vin_8k_switches_config.png "Figure 3-6. Switches SW1-SW5 Configuration."
 *
 * Insert the IMX492 sensor into the VIN SLVS-EC slot on the CV5 Timn board, as shown in the figure below.
 *
 * @image html example_vin_8k_insert_imx455.png "Figure 3-7. Insert IMX455 Sensor in VIN SLVS-EC."
 *
 * Enter the preview with the following commands:
 *
 * @code {.c}
 * board# init.sh --na;
 * board# modprobe imx455 bus_addr=0x30000 fpga=0
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_8k_linear.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_virtual_vin Example 8: Encode from RGB RAW: Input from RGB (RAW) File to VIN with Custom Virtual VIN Mode
 * The Lua script can be found at <a href="script/cv5_vin0_1080p_linear_efr.lua" target="_blank"><b>cv5_vin0_1080p_linear_efr.lua</b></a>.
 * @code
 * board# init.sh --na;
 * board# modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg cv5_vin0_1080p_linear_efr.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1
 * board# test_efm -t 3 -i cap_raw_raw_1920x1080_3840.raw  -s 1920x1080 -T 1 -r 30 -R 0 --vin-id 14
 * @endcode
 *
 * @subsection example_broken_vin Example 9: Enter Preview with Broken VIN
 * Use cv72_gage + 9296 serdes + 4 x os08a10 as an example.
 * - For Cooper SDK Amba build:
 *   @code
 *   build$ make menuconfig
 *          drv_modules  --->
 *              platform  --->
 *                  vin -->
 *                    sensors  --->
 *                      [*] kernel-module-os08a10-mipi-brg (drv_modules/platform/vin/sensors/omnivision_os08a10_mipi_brg)
 *                    bridges  --->
 *                       [*] kernel-module-ambrg (drv_modules/platform/vin/bridges/ambrg)
 *                             [*]   kernel-module-max9296 (drv_modules/platform/vin/bridges/maxim_9296)
 *   @endcode
 *
 * - For Cooper SDK Yocto build:
 *   @code
 *   build$ make menuconfig
 *          meta-ambabsp  --->
 *              recipes-sensor  --->
 *                 [*] kernel-module-os08a10-mipi-brg (drv_modules/platform/vin/sensors/omnivision_os08a10_mipi_brg)
 *              recipes-bridge  --->
 *                 [*] kernel-module-ambrg (meta-ambabsp/recipes-bridge/kernel-module-ambrg)
 *                 [*]   kernel-module-max9296 (drv_modules/platform/vin/bridges/maxim_9296)
 *   @endcode
 *
 * Users must add the image audio video (IAV) driver probe parameter `keep_broken_vsrc=1` before compiling the SDK code.
 * @code
 * build$ vi rootfs/default/etc/modprobe.d
 *  ...
 *  # Driver options
 *  ...
 *  options iav keep_broken_vsrc=1
 *  ...
 * @endcode
 *
 * If users do not add the `keep_broken_vsrc=1` parameter before compiling, they can add it
 * after the board is booted up, and then reboot it.
 * @code
 * board# vi /etc/modprobe.d/ambarella.conf
 *  ...
 *  # Driver options
 *  ...
 *  options iav keep_broken_vsrc=1
 *  ...
 * board# reboot
 * @endcode
 *
 * Specify `vsrc_status = 1` for vsrc_0 without connecting a sensor to vsrc_0,
 * and `vsrc_status = 0` for vsrc_1, connecting a sensor on vsrc_1.
 * Refer to <a href="script/enter_preview_with_broken_vin.lua" target="_blank"><b>enter_preview_with_broken_vin.lua</b></a>.
 * Place the script in the same folder where users issue the `test_encode` command.
 *
 * @code
 * vsrc_0 = {
 *    ...
 *    vsrc_status = 1,
 *    ...
 * }
 *
 * vsrc_1 = {
 *    ...
 *    vsrc_status = 0,
 *    ...
 * }
 * @endcode
 *
 * Issue the command to enter into preview mode; it will enter the preview with the buffer
 * from vsrc_0 filled with a black privacy mask. The buffer from vsrc_1 is filled with the actual sensor image.
 *
 * @code {.c}
 * board# init.sh --na;
 * board# modprobe max9296 id=0x0303 vinc_id=0xb8;
 * board# modprobe os08a10_mipi_brg fsync=1;
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg enter_preview_with_broken_vin.lua  --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua --vsync-detect-disable 0 --vsync-loss-dummy-frame-enable 1
 * @endcode
 *
 * After entering the preview, users can start encoding from the broken canvas corresponding to the broken VIN.
 * @code {.c}
 * board# test_encode -A -b0 -H 3840x2160 -e;
 * board# test_encode -B -b5 -H 1920x1080 -e;
 * board# rtsp_server
 * @endcode
 *
 * When the sensor hardware is ready, users can switch the broken or unconnected VINs back to
 * recover on the fly. This is the camera seamless switch.
 * Connect an active sensor to vsrc_0 first, then issue the following command.
 * The sensor on vsrc_0 can be recovered successfully, which means the buffer from vsrc_0 will be filled
 * with an actual sensor image rather than a black privacy mask. At the same time, the states of the
 * channel and canvas corresponding to the VIN will be enabled to switch. The output of the
 * encoding and the preview will be restored to the actual sensor image.
 * @code {.c}
 * board# test_vin_cap -r 8 -S 0
 * @endcode
 *
 * @subsection example_vin_repeat_frm Example 10: VIN repeat frame
 * User needs to enable the flag of `--vin-frame-broken-dummy-repeat` when entering preview.
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/local/bin/scripts/cv5_vin0_4k_linear.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua --vin-frame-broken-dummy-repeat 1 --vsync-detect-disable 0
 * @endcode
 *
 * The following command can be used to simulate the generation of short line problems on Sony imx274 sensor.
 * If below command is sent, vin will continuously generate short lines until it restores ：
 * @code {.c}
 * cv5x:
 * board# amba_debug -w 0x20ed1e8000 -d 0x9000 && amba_debug -w 0x20ed1e0038 -d 0x2fff
 * cv72:
 * board# amba_debug -w 0xffed1e8000 -d 0x9000 && amba_debug -w 0xffed1e0038 -d 0x2fff
 * @endcode
 *
 * Currently, user can see that the video output always shows same frame with the same fps.
 * And dmesg will print the following log:
 * @code {.c}
 * [ 464.258099] vin_update_vsync_proc(2980): VIN8: frame broken happened
 * @endcode
 *
 * After sending the below command, vin will restore to normal state ：
 * @code {.c}
 * cv5x:
 * board# amba_debug -w 0x20ed1e0038 -d 0xf0b
 * cv72:
 * board# amba_debug -w 0xffed1e0038 -d 0xf0b
 * @endcode
 *
 * @subsection example_scale_VIN Example 11: Scale VIN
 * User must run this case on CV72 board with VIN0. users can specify "scale_type" in vsrc configuration
 * to enable scale VIN feature.
 *
 * @code {.c}
 * vsrc_0 = {
 * 	vsrc_id = 0,
 * 	mode = "3840x2160",
 * 	hdr_mode = "linear",
 * 	bits= 0,
 * 	scale_type = 1, -- options: "0", "1", "2", "3" or "4"
 * }
 * @endcode
 *
 * The Lua script can be found at <a href="script/cv72_vin0_scale_vin.lua" target="_blank"><b>cv72_vin0_scale_vin.lua</b></a>.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=0   //Scale VIN only supported on CV72 with VIN0.
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg cv72_vin0_scale_vin.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_Roi_VIN Example 12: Roi VIN
 * To enable roi VIN feature, users must specify "roi_enable = 1" and set "roi_list" in vsrc configuration.
 *
 * @code {.c}
 * vsrc_0 = {
 * 	vsrc_id = 0,
 * 	mode = "3840x2160",
 * 	hdr_mode = "linear",
 * 	fps = 30,
 * 	bits= 0,
 * 	roi_enable = 1,
 * 	roi_list = {        -- get three roi VINs
 * 		{
 * 			roi_win = {0, 0, 1920 ,1080},
 * 		},
 * 		{
 * 			roi_win = {960, 540, 1920 ,1080},
 * 		},
 * 		{
 * 			roi_win = {1920, 1080, 1920 ,1080},
 * 		},
 * 	},
 *
 * @endcode
 *
 * The Lua script can be found at <a href="script/cv72_3_roi_vin.lua" target="_blank"><b>cv72_3_roi_vin.lua</b></a>.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg cv72_3_roi_vin.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_scale_vin_with_roi_vin Example 13: Scale VIN with roi VIN
 * If scale VIN and roi VIN are both enabled (user must run this case on CV72 board with VIN0), VIN0 is used as scale VIN, VIN1/2/3 can be used as roi VINs.
 *
 * @code {.c}
 * vsrc_0 = {
 * 	vsrc_id = 0,
 * 	mode = "3840x2160",
 * 	hdr_mode = "linear",
 * 	fps = 30,
 * 	bits= 0,
 * 	scale_type = 1,
 * 	roi_enable = 1,
 * 	roi_list = {
 * 		{
 * 			roi_win = {0, 0, 0 ,0}, -- the first roi_win is not used when scale VIN is enbaled
 * 		},
 * 		{
 * 			roi_win = {960, 540, 1920 ,1080},
 * 		},
 * 	},
 * }
 *
 * @endcode
 *
 * The Lua script can be found at <a href="script/cv72_scale_vin_with_roi_vin.lua" target="_blank"><b>cv72_scale_vin_with_roi_vin.lua</b></a>.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=0   //Scale VIN only supported on CV72 with VIN0.
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg cv72_scale_vin_with_roi_vin.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * @endcode
 *
 */
/*!
 * @file vout.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_vout BASIC - Video Ouput
 *
 * @section section_vout_features 1. Video Output Features
 *
 * CV5x / CV72 has three video output (VOUT) controllers: VOUT A, VOUT B, and VOUT C. VOUT A and VOUT B support
 * mobile industry processor interface (MIPI) CSI® and MIPI DSI. VOUT C supports high-definition multimedia
 * interface (HDMI®) and composite video broadcast signal (CVBS).
 * The maximum resolution of VOUT A is 4K. The maximum resolution of VOUT B and VOUT C is 8K.
 *
 * @image html pipeline_for_vout.png Pipeline for VOUT.
 *
 *
 * @subsection vout_mixer 1.1 Video Output Mixer
 * For CV5x chips, there are two VOUT mixers , "VOUT mixer A" for VOUT A and
 * "VOUT mixer B" for VOUT B/C. This means that VOUT B and C shares the same VOUT mixer.
 * For CV72 chip, there are three VOUT mixers , "VOUT mixer A" for VOUT A and
 * "VOUT mixer B" for VOUT B, and "VOUT mixer C" for VOUT C.
 *
 * VOUT mixer A is affiliated with VOUT A, and VOUT mixer B is affiliated with VOUT B.
 * For CV5x / CV7x platforms, there is no requirement to reuse the VOUT mixer for other purposes,
 * including stream blur. The two VOUT mixers are used only by VOUT modules themselves.
 *
 * @subsection vout_default_image 1.2 Video Output: Default Image
 * VOUT default image is used to display user-specified image. It can support either YUV422(NV16)
 * or YUV420(NV12) image format. When this feature is enabled, users are not required to specify
 * "preview" type canvas for VOUT.
 *
 * See @ref example_vout_default_image.
 * <br>
 *
 * @subsection vout_rotate 1.3 Video Output: VOUT Rotate
 * VOUT rotate is used to run-time rotate the input image at the VOUT stage. When the input
 * resolution is width x height, the VOUT output resolution is height x width. The
 * final display resolution is also height x width.<br>
 * See @ref example_vout_rotate for typical cases.
 *
 * Rotate VOUT size and rotate state support changes on the fly.
 * If users must change the VOUT size, they should change corresponding buffer size before VOUT size.<br>
 * See @ref example_vout_rotate_change_on_the_fly for such cases.
 *
 * One typical use case for the VOUT rotate feature is used together with the image digital signal processor (IDSP) 
 * rotate feature.The input image is already pre-rotated at the IDSP stage. Users can use the VOUT rotate feature
 * to rotate the pre-rotated image and to display the unrotated image. For example, when IDSP
 * rotate is used, the VOUT input size may be 720x1280. With VOUT rotate enabled, the VOUT
 * output size would be 1280x720.
 * The final display size is also 1280x720.<br>
 * See @ref example_vout_rotate_mode3 for such cases.
 *
 *
 * @note
 * - Only progressive VOUT mode can support rotation.
 * - The VOUT rotate feature may require some extra digital signal processor (DSP) internal resources.
 * - VOUT rotate must set an aligned correspond preview buffer size in the Lua file.
 * - VOUT rotate 1080p requires a 1088x1920 preview buffer.
 *
 * @subsection vout_flip 1.4 Video Output: VOUT Flip
 * VOUT flip is used to flip images horizontally or vertically.
 * It can flip the video or on-screen display (OSD).<br>
 * See @ref example_vout_flip for typical cases.
 *
 * @subsection no_vout_for_preview 1.5 Video Output: No VOUT for Preview
 * For some scenarios, users may be required to configure VOUT input when entering the preview state,
 * without the VOUT module configured. Users may enable the VOUT module and the display unit on the fly
 * at later stages.
 *
 * From the DSP perspective, VOUT input data format configuration may be independent from VOUT
 * procedure and output configuration. Users may be required to ensure that the VOUT input format matches 
 * the VOUT output format. Otherwise, the video output may be corrupted.
 *
 *
 * @subsection hdmi_vout_format 1.6 Video Output: HDMI VOUT Format
 *
 * The HDMI controller on CV5x / CV72 systems on chip (SoCs) can support output RGB, YUV422, and YUV444 formats.
 *
 * @subsection vout_no_reset 1.7 Video Output: VOUT No Reset During Mode Switch
 *
 * Normally, VOUT will be switched off when the IDSP is in the idle state, and VOUT will be reset after
 * entering into the preview state again. In this case, VOUT must be reconfigured again after the
 * idle state.
 *
 * For some scenarios, may be required to enable VOUT at all times, even when IDSP is in the idle state.
 * For example, users can configure a VOUT on-screen display (OSD) on the display, while
 * performing mode switch between the DSP idle state and preview state in the background.
 * In this case, VOUT OSD is active all the time, while the VOUT video layer is
 * switched between the live sensor input image (in the preview state) and the VOUT
 * background color (in the idle state).
 *
 * From the DSP perspective, the VOUT module is independent from the IDSP / VDSP modules.
 * This makes it possible to have VOUT functioning with IDSP in the idle state separately.
 * In this case, the VOUT input source will be switched to the VOUT background color.
 * When IDSP is switched to the preview state, VOUT can switch the input source
 * back to the live sensor input.
 *
 * See @ref example_vout_no_reset for typical cases.
 *
 * @subsection vout_osd_sync 1.8 Video Output: VOUT OSD Frame Sync
 * Users can use vout osd frame sync to allows the osd content of each frame can be precisely
 * synchronized with the frame displayed by vout.
 *
 * See @ref example_vout_osd_sync for typical cases.
 *
 * ---
 *
 * @section section_vout_devices 2. Video Output Devices
 *
 * @subsection vout_multi_interface 2.1 Video Output with Multi-Interface
 *
 * The Cooper chip family supports multiple VOUT interfaces, including the following:
 * - HDMI v2.0 output including on-chip PHY with consumer electronic control (CEC) support. HDMI output resolution is up to 8KP60 (no period)
 * - 4-lane MIPI DSI / CSI output (no period)
 * - Video digital-to-analog converter (DAC) for 480i / 576i composite PAL / NTSC output
 * - Full screen frame buffer on the analog / digital video output
 *
 * @subsection vout_support_list 2.2 Video Output: Supported VOUT Interfaces
 * The table below lists the supported VOUT Interfaces for each chip in the Cooper family.
 * <table>
 * <caption id="table_vout_interface"></caption>
 * <tr><th> VOUT Interface <th> CV5 <th> CV52 <th> CV72
 * <tr><td> HDMI <td> Yes <td> Yes <td> Yes
 * <tr><td> CVBS <td> Yes <td> Yes <td> Yes
 * <tr><td> MIPI_DSI <td> Yes <td> Yes <td> Yes
 * <tr><td> MIPI_CSI <td> Yes <td> Yes <td> Yes
 * </table>
 *
 * ---
 *
 * @section section_vout_examples 3. Video Output Examples
 *
 * @subsection example_hdmi_output Example 1: Video Output via HDMI
 *
 * First, initialize the evaluation kit (EVK) board to load the essential drivers and microcode, and
 * begin 3A (AE / AWB / AF) statistics if the following command was not executed previously.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * @endcode
 *
 * @par Output Resolution Control
 *
 * HDMI with 480p resolution:<br>
 * Modification of vout_hdmi.lua file for 480p:
 * @code
 * vout_2 = {
 *      status = "on",
 *      mode = "480p",
 *      input_yuv422 = "yes",
 *      video_output_window = {0, 0, 720, 480},
 *      type = "hdmi",
 * }
 * @endcode
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * HDMI with 720p resolution:
 *
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua)  // For CV72
 * @endcode
 *
 * HDMI with 1080p resolution:
 *
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * @par Disable VOUT:
 *
 * @code
 * board# test_encode -J --btype off
 * @endcode
 *
 *
 * @subsection example_cvbs_output Example 2: Video Output via CVBS
 *
 * First, initialize the EVK board to load the essential drivers and microcode, then
 * start 3A statistics if the following command was not executed previously.
 *
 * @code
 * board# rmmod ambdve
 * board# modprobe ambdve voutid=2
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# modprobe ambarella_fb
 * board# test_aaa_service -a&
 * @endcode
 *
 * Video Output: 480i CVBS
 *
 * @code
 * board# test_encode --resource-cfg ./res_cvbs_2.lua --vout-cfg ./vout2_cvbs.lua
 * @endcode
 *
 *
 * @subsection example_vout_size Example 3: HDMI Output Size Change on the Fly
 *
 * HDMI output size can be changed while encoding or during preview without changing back to
 * the idle state. Before issuing the change command, the preview buffer must
 * be configured to the new output size.
 *
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_multi_chan -c 0 -J --boutsize 1280x720
 * board# test_encode --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 * @endcode
 *
 * @note
 * - VOUT change on the fly in decoding is not supported.
 *
 * @subsection example_vout_default_image Example 4: VOUT Default Image
 *
 * @par Configure the platform to build test_custom_vout
 *
 * @code {.c}
 * build$ make menuconfig
 *  -*- Ambarella Unit Test Configuration  --->
 *    -*- Ambarella Private Linux Unit test configs  --->
 *      -*- Build VOUT unit tests  --->
 *        -*- Build Custom VOUT unit tests
 * @endcode
 *
 * @par 1) Display YUV420(NV12) Image File through VOUT Default Image Function
 *
 * Configure VOUT Lua option "vout-from-image" to enable VOUT default image function,
 * and configure VOUT Lua option "default_img_format" is to set image format to YUV420(NV12).
 *
 * @code
 * vout_2 = {
 * ...........
 * vout-from-image = "enable",
 * default_img_format= "yuv420",
 * ...........
 * }
 * @endcode
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\        // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_custom.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\   // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_custom.lua)
 * board# test_mempart -m 2 -s 0x4000000
 * board# test_custom_vout -i 420.yuv -s 1920x1080
 * @endcode
 *
 * @par 2) Display YUV420(NV12) Canvas in Live through VOUT Default Image Function
 *
 * Configure VOUT Lua option "vout-from-image" to enable VOUT default image function,
 * and configure VOUT Lua option "default_img_format" is to set image format to YUV420(NV12).
 * test_custom_vout option "-b" is used to specify canvas id.
 *
 * @code
 * vout_2 = {
 * ...........
 * vout-from-image = "enable",
 * default_img_format= "yuv420",
 * ...........
 * }
 * @endcode
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\        // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_custom.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\   // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_custom.lua)
 * board# test_custom_vout -b 2
 * @endcode
 *
 * @subsection example_vout_rotate Example 5: VOUT Rotate
 * First, initialize the EVK board to load the essential drivers and microcode,
 * then start 3A process if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * @endcode
 *
 * Next, in this lua script case, modify the preview buffer size.<br>
 * Set the buffer width corresponding to the VOUT height and align to 32.<br>
 * Set the buffer height corresponding to the VOUT width and align to 16.
 *
 * @code
 * ...
 *      third = {
 *              max_output = {0, 0}, -- output width
 *              input      = {0, 0, 0, 0}, -- full main
 *              output     = {0, 0, 720, 1280},
 *      },
 * ...
 * @endcode
 *
 * @code
 * vout_2 = {
 *      ...
 *      video_rotate = "yes",
 *      ...
 * }
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 * @endcode
 *
 *
 * @subsection example_vout_flip Example 6: VOUT Flip
 * First, initialize the EVK board to load the essential drivers and microcode,
 * then start 3A process if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a &
 * @endcode
 *
 * Modification of vout_hdmi.lua file for VOUT flip:
 * @code {.c}
 * vout_2 = {
 *      ...
 *      video_flip_mode = "v",                 --selection: 0:no, 1:hv, 2:h, 3:v
 *      ...
 * }
 * @endcode
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * Modification of vout_hdmi.lua file for VOUT OSD flip:
 * @code {.c}
 * vout_2 = {
 *      ...
 *      osd_flip_mode = "v",                 --selection: 0:no, 1:hv, 2:h, 3:v
 *      ...
 * }
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_hdmi_vout_format Example 7: HDMI VOUT Format
 *
 * Modification of vout_hdmi.lua file for HDMI outputs:
 * @code {.c}
 * vout_2 = {
 *      ...
 *      hdmi_output_format = "rgb",                     --selection: 0:rgb, 1:yuv422, 2:yuv444
 *                                                      --only for hdmi output mode
 *      ...
 * }
 * @endcode
 * @code {.c}
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_vout_no_reset Example 8: VOUT No Reset for Mode Switch
 * This feature is designed to keep VOUT active at all times during mode switch.
 * The option "--no-vout-reset" is used to enable the option for no-VOUT reset
 * when putting DSP into the idle state or preview state.
 *
 * Modification of vout_hdmi.lua file for maximum OSD bit depth:
 * @code {.c}
 * vout_2 = {
 *	  ...
 *	  max_osd_bit_depth = 16,
 *	  ...
 * }
 * @endcode
 *
 * @code {.c}
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3;
 * board# test_aaa_service -&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vout-possible-map 0x4
 * board# test_osd -w 720 -h 480 -c colorbar -t 1000 /dev/fb2             // Run on telnet
 * board# test_encode --idle --nopreview --no-vout-reset
 * board# test_encode -Y --bsize 720p --bmaxsize 720p --no-vout-reset    // OSD still displays during mode switch
 * board# test_encode --idle --nopreview --no-vout-reset         // OSD still displays when iav status switch to idle.
 * @endcode
 *
 * @subsection example_vout_osd_sync Example 9: VOUT OSD Sync
 * Modification of vout_hdmi.lua file for maximum OSD bit depth:
 * @code {.c}
 * vout_2 = {
 *	  ...
 *	  max_osd_bit_depth = 16,
 *	  ...
 * }
 * @endcode
 * Update "enc_dummy_latency = 2" for the preview type canvas
 * @code {.c}
 * canvas = {
 *	  .....
 *   {
 *         type = "prev",
 *         .....
 *         enc_dummy_latency = 2,
 *         .....
 *   },
 * }
 * @endcode
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3	 // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)		 // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_custom_vout -b 2 -o -S
 * @endcode
 *
 * @subsection example_video_output_via_dsi Example 10: Video Output via DSI
 * Modification of `vout_hdmi.lua` file to turn on the DSI output via `vout_0`:
 * @code {.c}
 * vout_0 = {
 *     status = "on",
 *     ...
 * }
 * vout_1 = {
 *     status = "disable",
 *     ...
 * }
 * vout_2 = {
 *     status = "disable",
 *     ...
 * }
 * @endcode
 *
 * Updating option `vout_id` of the preview canvas in the `cv72_vin0_1080p_linear.lua`.
 * @code {.c}
 * canvas = {
 *   .....
 *   {
 *         type = "prev",
 *         .....
 *         vout_id = 0,
 *         .....
 *   },
 * }
 * @endcode
 *
 * After the above preparation, the following steps can launch this feature.
 * @code {.c}
 * board# rmmod ambdve
 * board# modprobe ambdve voutid=2
 * board# modprobe lcd_r69429 voutid=0
 * board# modprobe ambarella_fb
 * board# init.sh --na; modprobe imx678_mipi vinc_id=8
 * (Or board# init.sh --na;modprobe imx678_mipi vinc_id=8 bus_id=3)		 // For CV5
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg cv72_vin0_1080p_linear.lua --vout-cfg vout_hdmi.lua
 * @endcode
 *
 * @subsection example_video_output_via_csi Example 11: Video Output via CSI
 * Modification of `vout_hdmi.lua` file to turn on the CSI output via `vout_0`:
 * @code {.c}
 * vout_0 = {
 *     status = "on",
 *     mode = "1080p",
 *     video_output_window = {0, 0, 1920, 1080},	--{offsetx, offsety, output_width, output_heigh}
 *     type = "mipi_csi",      			--selection: digital, mipi_dsi, fpd_link
 *     ...
 * }
 * vout_1 = {
 *     status = "disable",
 *     ...
 * }
 * vout_2 = {
 *     status = "disable",
 *     ...
 * }
 * @endcode
 *
 * Updating option `vout_id` of the preview canvas in the `cv72_vin0_1080p_linear.lua`.
 * @code {.c}
 * canvas = {
 *   .....
 *   {
 *         type = "prev",
 *         .....
 *         vout_id = 0,
 *         .....
 *   },
 * }
 * @endcode
 *
 * @code {.c}
 * board# rmmod ambdve
 * board# modprobe ambdve voutid=1
 * board# init.sh --na; modprobe imx678_mipi vinc_id=8
 * (Or board# init.sh --na;modprobe imx678_mipi vinc_id=8 bus_id=3)		 // For CV5
 * board# modprobe lcd_r9611 mipi_type=4 dsi_output_mode=11 voutid=0
 * board# modprobe ambarella_fb
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg cv72_vin0_1080p_linear.lua --vout-cfg vout_hdmi.lua --vout-possible-map 7
 * @endcode
 *
 * @subsection example_dual_vout Example 12: Dual Vout
 * Dual Vout is a combination of two individual Vout devices in general.
 *
 * Select `vout_0` and `vout_2` to take an example for this feature.
 * @code {.c}
 * vout_0 = {
 *     status = "on",
 *     ...
 * }
 * vout_1 = {
 *     status = "disable",
 *     ...
 * }
 * vout_2 = {
 *     status = "on",
 *     ...
 * }
 * @endcode
 *
 * There are two preview type canvas as the resource of `vout_id` 0 and 2
 * @code {.c}
 * canvas = {
 *     .....
 *     {
 *         type = "prev",
 *         size = {1920, 1080},
 *         vout_id = 0,
 *         .....
 *     },
 *     {
 *         type = "prev",
 *         size = {1920, 1080},
 *         vout_id = 2,
 *         .....
 *     },
 * }
 * @endcode
 *
 * CV72 HDMI is assigned by `voutid=2` and can be as the one of dual VOUT, the other can use `lcd_r69429` which is assigned by `voutid=0`
 * @code {.c}
 * board# rmmod ambdve
 * board# modprobe ambdve voutid=2
 * board# rmmod ambarella_fb
 * board# modprobe ambarella_fb resolution=1920x1080 mode=clut8bpp
 * board# init.sh --na; modprobe imx678_mipi vinc_id=8
 * (Or board# init.sh --na;modprobe imx678_mipi vinc_id=8 bus_id=3) 	 // For CV5
 * board# modprobe lcd_r69429 voutid=0
 * board# modprobe ambarella_fb
 * board# test_aaa_service -a &
 * test_encode --resource-cfg cv72_vin0_1080p_linear.lua --vout-cfg vout_hdmi.lua --vout-osd-rescale-disable 1 --vout-possible-map 7
 * @endcode
 *
 * @subsection example_vout_switch_multi_chan Example 13: VOUT Switch Multi-Channel on the Fly
 * The VOUT source is able to bind to different channel, so user can switch input source of VOUT on the fly.
 *
 * For an example, below changes in `cv72_vin0_1080p_linear.lua` can support for this feature.
 *
 * User can activate two vin as the video source for two channels.
 *
 * @code {.c}
 * vsrc_0 = {
 *     vsrc_id = 0,
 *     ...
 * }
 * vsrc_1 = {
 *     vsrc_id = 1,
 *     ...
 * }
 * @endcode
 *
 * `vsrc_0` and `vsrc_1` in this example bind to channel 1 and channel 2, respectively.
 * The fourth buffer within both channels will be set into preview canvas.
 * @code {.c}
 * chan_0 = {
 *    id = 0,
 *    vsrc = vsrc_0,
 *    ......
 *    fourth = {
 *        max_output = {1920, 1080},
 *        input		 = {0, 0, 0, 0},
 *        output 	= {0, 0, 1920, 1080},
 *    }
 * }
 * chan_1 = {
 *    id = 1,
 *    vsrc = vsrc_1,
 *    ......
 *    fourth = {
 *        max_output = {1920, 1080},
 *        input		 = {0, 0, 0, 0},
 *        output 	= {0, 0, 1920, 1080},
 *    }
 * }
 * @endcode
 *
 * @code {.c}
 * canvas = {
 *     .....
 *     {
 *         type = "prev",
 *         source = {"chan_0.fourth", "chan_1.fourth"},
 *         vout_id = 2,
 *         .....
 *     },
 * }
 * @endcode
 *
 * The following commands are for VOUT switch.
 * @code {.c}
 * board# init.sh --na;modprobe max9296 id=0x0303 vinc_id=0xb8;modprobe os08a10_mipi_brg fsync=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg cv72_vin0_1080p_linear.lua --vout-cfg vout_hdmi.lua
 * board# test_multi_chan -c 1 -K --boutsize 1920x1080 -c 0 -K --boutsize 0x0
 * board# sleep 2
 * board# test_multi_chan -c 0 -K --boutsize 1920x1080 -c 1 -K --boutsize 0x0
 * @endcode
 *
 * @subsection example_vout_underflow_prevention Example 14: VOUT Underflow Prevention
 * Setting `--vout-underflow-prevention` value to improve VOUT priority that can avoid some
 * display exceptions, such as artifacts and flicking in VOUT.
 *
 * This option has impact on the other modules DMA priority, especially when the device is almost overloaded.
 *
 * @code {.c}
 * board# init.sh --na; modprobe imx678_mipi vinc_id=8
 * (Or board# init.sh --na;modprobe imx678_mipi vinc_id=8 bus_id=3)         // For CV5
 * board# test_aaa_service -a&
 * board# board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vout-underflow-prevention 1  // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vout-underflow-prevention 1)  // For CV72
 * @endcode
 *
 */
/*!
 * @file raw.h
 * @brief document for raw features
 * @version 0.1
 * @date 2021-01-28
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
 * @page fs_basic_raw BASIC - Raw
 *
 * @section section_raw_features 1. Raw Features
 * CV5x chips process raw data from VINs in the unit of channel, and support compressed /
 * uncompressed and unpacking / uncompressed and packing raw data.
 *
 * @subsection VIN_raw_size 1.1 Raw Size
 *
 * 1    compressed raw (VIN is 1080p)
 *
 *      data size = ROUND_UP((1920 x 27 / 32), 64) x 1080 = 1664 x 1080 = 1797120
 *
 * 2    uncompressed and unpacking raw (VIN is 1080p)
 *
 *      data size = ROUND_UP((1920 x 2), 64) x 1080 = 3840 x 1080 = 4147200
 *
 * 3    uncompressed and packing raw (VIN is 1080p@12bit)
 *
 *      data size = ROUND_UP((1920 x 12 / 16 * 2), 64) x 1080 = 2884 x 1080 = 3114720
 *
 * @subsection raw_buffer_manunal_feed 1.2 Raw Buffer Manual Feed
 *
 * Raw buffer is generated and reported to Arm by DSP, and is allocated and maintained using two
 * different methods. In addition, it can be configured through "raw_manual_feed" and "raw_feed_frame_num"
 * item of channel cfg in the Lua script.
 *
 * <ul>
 *   <li><B>Raw buffer Auto-Generation Mode</B>
 *   <li><B>Raw buffer Manual-Feed Mode</B>
 * </ul>
 *
 * In raw buffer auto-generation mode, DSP allocates and maintains the raw buffer.
 * Each time DSP captures raw data, then it is automatically reported to Arm.
 * In auto-generation mode, DSP will guarantee frame rate.<br>
 *
 * In raw buffer manual-feed mode, frame queue is fully driven and controlled
 * by user application. Each time a user application requests a raw buffer, it will trigger
 * IAV driver feeds an empty buffer address to DSP. DSP fills raw data into the
 * buffers, and then reports back to Arm.<br>
 *
 * See also: @ref pyramid_feed_mode
 *
 * @subsection raw_slice_capture 1.3 Raw slice
 *
 * Raw slice buffer can be configured through `raw_slice_num` and `raw_slice_cached_items` item of
 * channel config in the Lua script.
 *
 * When this feature is enabled, DSP will slice RAW data vertically and evenly, so that IDSP
 * can process the slice of RAW data one by one. Once the slice data is ready,
 * DSP will report the slice data to ARM, and user application can capture the slice data of RAW.
 *
 * For some special cases with large resolution, DSP will need more time to process one frame.
 * If the RAW data can be sliced, users will obtain the RAW data processed by DSP earlier.
 *
 * Currently, Cooper SDK has supported the different slice numbers, such as 2 / 4 / 6 / 8.
 *
 * - - - -
 *
 * @section lua_raw_configuration 2. Raw Configuration
 *
 * Users can configure the VIN raw via Lua script. Here are the parameters for
 * raw.<br>
 *
 * <table>
 * <caption id="table_VIN_raw_lua"></caption>
 * <tr><th> Item <th><div style="width:240px"><B>Parameter</B></div> <th>Description
 * <tr><td> mode
 *     <td> a x b
 *     <td> Specify the VIN resolution.
 * <tr><td> @anchor anchor_bits bits
 *     <td> 8: 8bits <br>
 *          10: 10bits <br>
 *          12: 12bits <br>
 *          14: 14bits <br>
 *          16: 16bits <br>
 *           0: Default bits
 *     <td> Specify the VIN bits.
 * <tr><td> @anchor anchor_raw_capture raw_capture
 *     <td> 0: Raw compressed <br>
 *          1: Raw uncompressed
 *     <td> Enable raw uncompressed.
 * <tr><td> @anchor anchor_packing_mode_enable packing_mode_enable
 *     <td> 0: Raw packing disabled <br>
 *          1: Raw packing enabled
 *     <td> Enable Raw packing, only valid when raw_capture = 1.
 * </table>
 *
 * <B>An Example for VIN Raw Lua Configuration</B><br>
 *
 * @code
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    mode = "1920x1080",       -- VIN raw resolution: 1920 x 1080
 *    hdr_mode = "linear",
 *    fps = 30,
 *    bits= 12,       -- VIN raw bits: 12 bits
 * },
 *
 * chan_0 = {
 *    ...
 *    raw_capture = 1,     -- raw uncompressed
 *    packing_mode_enable = 1, -- raw packing
 *    ...
 * },
 *
 * @endcode
 *
 * <br>
 *
 * ---
 *
 * @section section_raw_example 3. Raw Examples
 * Here is an example for uncompressed raw buffer manual feed. Specify "raw_capture = 1",
 * "raw_manual_feed = 1" and "raw_feed_frame_num = 8" in lua
 * @code {.sh}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# vi /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua         // For CV5 or CV52
 * (Or board# vi /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua)   // For CV72
 * ...
 * chan_0 = {
 *     ...
 *     raw_capture = 1,
 *     raw_manual_feed = 1,
 *     raw_feed_frame_num = 8,
 *     ...
 * }
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_manual_feed -r 0 -R 1
 * @endcode
 *
 *
 */
/*!
 * @file channel.h
 * @brief
 * @version 0.1
 * @date 2022-04-22
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
 * @page fs_basic_channel BASIC - Channel
 *
 * @section channel_features 1. Channel and IDSP Pipeline
 *
 * Channel is the software concept of the image digital signal processing (IDSP) pipeline.
 * For each channel, CV5x chips process the input frames captured from a RGB sensor or YUV
 * device, and generate different YUV buffers for further processing. The supported channels
 * are up to eight.
 *
 * In the IDSP pipeline, there are two major stages, RAW processing stage and YUV processing
 * stage. In the RAW processing stage, IDSP has high dynamic range (HDR) blending module to
 * blend multiple exposures into a single frame, various filters for noise reduction and color
 * enhancement, and finally color convertion module to convert RGB format to YUV format.
 * In the YUV processing stage, IDSP has filters for color noise reduction and enhancement,
 * the module for warp and scale functions, the motion-compensated temporal filtering (MCTF)
 * module for 3D noise reduction, and the module for final sharpen processing.
 *
 * For each channel, the RGB or YUV RAW frames will go through the entire IDSP pipeline
 * to generate source buffers. So when there are some features turned off in the IDSP
 * pipeline, the RAW frames still go through the entire pipeline, but the data will pass
 * through some filters or modules without any processing. For example, YUV RAW data will
 * still go through the RAW processing pipeline, but it may pass through these modules
 * inside the RAW processing stage with the data unchanged in this stage.
 *
 * @image html idsp_pipeline.jpg Channel IDSP Pipeline
 *
 *
 * @subsection channel_rotation 1.1 Channel IDSP Rotation / Flip
 *
 * For CV2x chips, there is a dedicated encode mode 3 for IDSP rotation and flip operations.
 * However for CV5x / CV7x chips, the rotation and flip operations can be supported in
 * different encode modes, such as encode mode 0 and encode mode 5. Therefore, this dedicated
 * encode mode 3 is no longer needed for CV5x / CV7x chips.
 *
 * There is a dedicated parameter rotate_cw in channel configurations to achieve 90 degree
 * clockwise rotation. The parameter hflip in channel configurations is to achieve horizontal
 * flip, and the paramter vflip in channel configurations is to achieve vertical flip.
 *
 * The following is the resource configuration.
 * <table>
 * <caption id="table_channel_rotation">Channel Rotation Configurations</caption>
 * <tr><th> Configurations                          <th> <B>Description</B></div>
 * <tr><td> rotate_cw = 1                           <td> 90 degree clockwise rotation
 * <tr><td> hflip = 1 && vflip = 1                  <td> 180 degree clockwise rotation
 * <tr><td> rotate_cw = 1 && hflip = 1 && vflip = 1 <td> 270 degree clockwise rotation
 * </table>
 *
 * @image html cv5_channel_rotation.jpg Channel Rotation / Flip
 *
 * @note
 * Limitations for channel rotation / flip are as follows:
 * - For rotation, Main Buffer must be 16 aligned for width and 32 aligned for height.
 * - For flip, there is no special alignment requirement. It is the same as no flip cases.
 *
 *
 * @subsection channel_idso_dual_cores 1.2 IDSP Dual Cores
 *
 * For CV5x chips, there are two indepenndet IDSP cores to process RAW frames from input RAW
 * frames. For these two IDSP cores, users can be able to configure different Core modes for
 * different channels.
 *
 *
 * There are three IDSP core modes for users to configure for each channel.
 * - The first is to enable IDSP core 0 only for the channel.
 * - The second is to enable IDSP core 1 only for the channel.
 * - The last one is to enable both IDSP cores for the channel.
 *
 * By default, all channels are configured with IDSP dual cores. But this is not most efficient
 * way for all use cases. For the single VIN with 8K senor input, it is highly recommended to
 * enable both IDSP cores to the channel, in order to achieve the best performance by fully
 * utilizing both cores. For the multiple VIN use cases, it is more recommended to use single core
 * for each channel, when the use cases are symmetric. For example, there are four sensor inputs,
 * and each is with 4Kp30 IDSP performance. For such use case, it is highly recommended to use
 * independent IDSP cores for each channel, which means two channels with IDSP core 0 and other two
 * channels with IDSP core 1. This is more efficient than IDSP dual cores, because IDSP dual cores
 * may have performance overhead caused by dual core performance balancing.
 *
 * @note
 * For CV72, there is only one IDSP core.
 *
 * @subsection channel_mctf_compression 1.3 MCTF Compression
 *
 * MCTF compression is used to compress MCTF reference frames, to achieve better dynamic random
 * access memory (DRAM) performance. There is a param "mctf_cmpr" in iav_chan_cfg to configure
 * this. By default, it is enabled. And users may need to tune MCTF compression bitrate related
 * parameters to achieve best image quality. When it is turned off, more DRAM bandwidth is needed
 * for IDSP processing, so it may be expected the overall performance may be slightly lower than
 * the same case when it is turned on.
 *
 * @subsection channel_reuse_src_chan 1.4 IDSP Virtual Channel Frame-Synchronized
 * For the IDSP virtual channel use case, IDSP virtual channels send 3A configurations to IDSP separately
 * from its master channel. Due to the excution latency of 3A application, sometimes the virtual channels
 * might not be frame-synchronized with the sensor shutter/gain settings. As a result, there will be
 * artifacts on IDSP virtual channels. Therefore, Ambarella provides the `reuse_src_chan_iso_cfg` parameter
 * in lua scripts to do the frame synchronization. When this option `reuse_src_chan_iso_cfg` is enabled,
 * the current IDSP virtual channel will use duplicated 3A configuration of master channel
 * to achieve same and frame-synchronized settings as the master channel. This option is only
 * valid when current channel is IDSP virtual channel and sensor control is disabled.
 *
 * ----
 *
 * @section section_channel_example 2. Channel Examples
 *
 * @subsection example_channel_rotate Example 1: Channel Rotation
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start 3A process if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * @endcode
 *
 * Next, in this lua script case, modify the channel related configurations.<br>
 * Enable the rotate_cw flag, to enable 90 degree clockwise rotation.<br>
 * Set the Main Buffer width corresponding to the VIN height and align to 16.
 * Set the Main Buffer height corresponding to the VIN width and align to 32.
 * Adjust other canvas / buffer sizes if needed, due to the rotation on Main Buffer.
 *
 * @code
 * chan_0 = {
 * 	 ...
 *      rotate_cw = 1,
 *      main = {
 *              max_output = {0, 0}, -- output width
 *              input      = {0, 0, 0, 0}, -- full main
 *              output     = {0, 0, 1088, 1920},
 *      },
 *      third = {
 *              max_output = {0, 0}, -- output width
 *              input      = {0, 0, 0, 0}, -- full main
 *              output     = {0, 0, 720, 1280},
 *      },
 * ...
 * @endcode
 *
 * Use video output (VOUT) rotate / flip to view the image data before rotation.
 *
 * @code
 * vout_2 = {
 *      ...
 *      video_rotate = "yes",
 *      video_flip_mode = "hv",
 *      ...
 * }
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua)
 * @endcode
 *
 *
 * @subsection example_channel_flip Example 2: Channel IDSP Flip
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start 3A process if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * @endcode
 *
 * Modify the lua file for Channel IDSP horizontal and vertical flip:
 * @code {.c}
 * chan_0 = {
 *      ...
 *      hflip = "1",
 *      vflip = "1",
 *      ...
 * }
 * @endcode
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * @endcode
 *
 *
 * @subsection example_channel_idsp_cores Example 3: IDSP Dual Cores for CV5x
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start 3A process if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a &
 * @endcode
 *
 * Modify the lua file to enable IDSP dual core configuration, and enable core 0 here:
 * @code {.c}
 * chan_0 = {
 *      ...
 *      idsp_core_cfg_enable = "1",
 *      idsp_core_mode = "0",			-- 0: core 0, 1: core 1, 2: dual cores
 *      ...
 * }
 * @endcode
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_channel_vir_dup Example 4: Virtual Channel Duplicated 3A Configuration of Master Channel.
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start 3A process if the following command was not executed previously.
 *
 * @code {.c}
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a &
 * @endcode
 *
 * Modify the lua file for reuse_src_chan_iso_cfg.
 * @code {.c}
 * chan_0 = {
 * ...
 * img_stats_src_chan = "chan_0",
 * sensor_ctrl = 1,
 * reuse_src_chan_iso_cfg = 0,
 * ...
 * }
 *
 * chan_1 = {
 * ...
 * img_stats_src_chan = "chan_0",
 * sensor_ctrl = 0,
 * reuse_src_chan_iso_cfg = 1,
 * ...
 * }
 * @endcode
 *
 * @note
 * For idsp virtual channel with `sensor_ctrl` disabled and `reuse_src_chan_iso_cfg enabled`,
 * not suggested to specify `img_stats_src_chan` to itself. It is only for IDSP processing with
 * different IDSP config based on each channel's own 3A statistics.
 *
 * <a href="/script/cv5_virtual_channel_duplicate_3A.lua" target="_blank"><b>virtual_channel_duplicate_3A.lua</b></a>
 *
 * @code {.c}
 * board# test_encode --enc-mode 0 --resource-cfg /etc/cv5_virtual_channel_duplicate_3A.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @note
 * This feature also applies to CV72 in the same way.
 *
 */
/*!
 * @file buffer.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_source_buffer BASIC - Source Buffer
 *
 * @section source_buffer_features 1. Source Buffer Features
 *
 * Cooper family chips process raw data from VINs in the unit of @b "Channel".
 * For each channel, digital signal processor (DSP) generates different source buffers, puts
 * them in different canvases, and then sends it to the encoder or video output (VOUT). The
 * source buffers can be placed in the same canvas, and then be encoded or used
 * for preview.
 *
 * From the @b "Channel" perspective of view, video frames captured from a RGB
 * type sensor or YUV device are first generated inside the DSP as source buffer,
 * and then data from the source are flushed to dynamic random access memory (DRAM) to generate
 * the @ref fs_basic_canvas "Canvas", after that canvas data will be processed
 * by the encoder.
 *
 * Basically, the canvas stores the YUV data for encoding. The encoder
 * continuously fetches the video data (in the canvas) and performs the encoding
 * procedure sequentially. With this design, the encoding streams can include
 * different FoVs simultaneously. Source buffers from different
 * channels provide the raw video data to encoders or the video output. The five
 * source buffers for each channel on the platform are denoted as the main,
 * second,third, fourth, and fifth source buffers in the upper layer.
 *
 * @note
 * The sixth source buffer can be enabled when Pyramid buffers are disabled.
 *
 * @image html source_buffer_layout.png Figure 1-1. Source Buffer Layout.
 *
 * @subsection main_buffer_dptz 1.1 Main Buffer: Digital Pan / Tilt / Zoom (DPTZ)
 *
 * The main buffer is cropped and scaled from the video input (VIN) buffer.<br>
 *
 * @image html main_buffer_generation.png Figure 1-2. Digital Pan / Tilt / Zoom for Main Buffer.
 *
 * @par Scalability
 *
 * The scalability of the main buffer re-sampler is (1/4X - 8X]. For example, if
 * the VIN resolution is 2592x1944 and the main capture window is the same as the
 * VIN resolution, the minimum width of the main buffer is 2592/4=648. The main
 * buffer size cannot be set to a 640x480 resolution when the VIN is 2592x1944.
 * If this occurs, Ambarella recommends using other source buffers. If the VIN
 * is 1080p, the minimum width of the main buffer is 1920/4 = 480. Main buffer
 * size can be bigger than the VIN size, and if it is a crop and upscale buffer
 * from VIN, the maximum width can go up to 8x original cropped size.
 *
 * @note
 * Limitations for main buffer's DPTZ.
 * - Main buffer's size is only configurable in @ref iav_state_model "Idle" state.
 * - Main buffer's crop window can be changed in @ref iav_state_model "Idle, Preview, Encoding" state.
 *
 * @subsection sub_buffer_dptz 1.2 Sub-Buffer: Digital Pan / Tilt / Zoom
 *
 * The following diagram shows that the second, third, fourth, fifth and seventh
 * source buffers are cropped or scaled from the main source buffer. As the main
 * buffer changes its field of view (FoV), the FoV of the second, third, fourth, fifth, and seventh
 * buffers are changed accordingly.
 *
 * @image html sub_source_buffer_generation.png "Figure 1-3. Digital Pan / Tilt / Zoom for Sub-Buffer."
 *
 *
 * @subsection section_buffer_type 1.3 Buffer Type
 *
 * The source buffer has the following three types, <b>Off</b>, <b>Preview</b>, and <b>Encode</b>.
 *
 * - @b Off <br>
 *   The hardware buffer is shut down. It is not accessable.
 * - @b Preview <br>
 *   The hardware buffer is enabled. The content in the buffer is for "Preview" purpose.
 * - @b Encode <br>
 *   The hardware buffer is enabled. The content in the buffer is for "Encode" purpose.
 *
 * @note
 * Source buffers' type has the following limitations.
 * - Buffer type is configurable only in the @ref iav_state_model "Idle State".
 * - Main buffer's type should always be "Encode".
 *
 * @par A General Control Flow
 *
 * If users want to change buffers' type, put the image audio video (IAV) driver into "Idle State" first.
 * Users can change the buffer size in "Preview" state. Setting the buffer's size to 0x0
 * will put it into standby mode, which means that the DSP hardward of the source buffer is
 * enabled, but no "DPTZ" will be applied from the source buffer's input to output, and
 * no data copy will occur from the source buffer to its' canvas. The following picture
 * illustrates the process of buffer type and size configuration.
 *
 * @image html buffer_type_size_config.png "Figure 1-4. Buffer Type and Size Configuration Flow."
 *
 * @ref example_buffer_type_resolution "Try this example".
 *
 * @subsection section_buffer_capability 1.4 Buffer Capability
 *
 * This section provides a description of the buffer capability, including buffer
 * input, scalability, encoding support, and more.
 *
 * @subsubsection main_source_buffer 1.4.1 Main Source Buffer
 *
 * <table>
 * <caption id="table_main_buffer">Table 1-1. Main Buffer.</caption>
 * <tr><th> Feature		  <th> <div style="width:650px"><B>Description</B></div>
 * <tr><td> Resolution	  <td> See @ref section_buffer_resolution "Maximum Buffer Resolution"
 * <tr><td> Buffer Type   <td>
 * <ul>
 *    <li> Encoding
 *    <li> Off
 * </ul>
 * <tr><td> Input Window	  <td>
 * <ul>
 *    <li> The main capture window is cropped from the video input (VIN).
 *    <li> The main capture window cannot exceed the VIN size.
 * </ul>
 * <tr><td> Scalability    <td>
 * <ul>
 *    <li> Scale ratio range: 1/4x < ratio < 8x
  * </ul>
 * <tr><td> Alignment     <td>
 * <ul>
 *    <li> Width must be a multiple of 32.
 *    <li> Height must be a multiple of 8.
 * </ul>
 * <tr><td> Encoding      <td>
 * <ul>
 *    <li> H.264
 *    <li> H.265
 *    <li> MJPEG
 * </ul>
 * <tr><td> YUV Dumping <td> Yes
 * <tr><td> ME0/ME1 Dumping <td>
 * <ul>
 *    <li> ME0 is configurable as 1/8X of main buffer resolution both in width and height directions.
 * </ul>
 * </table>
 *
 * @subsubsection second_source_buffer 1.4.2 Second Source Buffer
 *
 * <table>
 * <caption id="table_second_buffer">Table 1-2. Second Source Buffer.</caption>
 * <tr><th> Feature		    <th> <div style="width:650px"><B>Description</B></div>
 * <tr><td> Resolution	    <td> See @ref section_buffer_resolution "Maximum Buffer Resolution"
 * <tr><td> Buffer Type     <td>
 * <ul>
 *    <li> Encoding
 *    <li> Off
 * </ul>
 * <tr><td> Input Window	    <td>
 * <ul>
 *    <li> The input window is cropped from the main source buffer.
 *    <li> The input window size cannot exceed the main buffer size.
 * </ul>
 * <tr><td> Scalability      <td>
 * <ul>
 *    <li> Scale ratio range: 1/16x < ratio <= 1x
 * </ul>
 * <tr><td> Alignment       <td>
 * <ul>
 *    <li> Width must be a multiple of 16.
 *    <li> Height must be a multiple of 8.
 * </ul>
 * <tr><td> Encoding        <td>
 * <ul>
 *    <li> H.264
 *    <li> H.265
 *    <li> MJPEG
 * </ul>
 * <tr><td> YUV Dumping <td> Yes
 * <tr><td> ME0/ME1 Dumping <td> Yes
 * </table>
 *
 * @subsubsection third_source_buffer 1.4.3 Third Source Buffer
 *
 * <table>
 * <caption id="table_third_buffer">Table 1-3. Third Source Buffer.</caption>
 * <tr><th> Feature		    <th> <div style="width:650px"><B>Description</B></div>
 * <tr><td> Resolution	    <td> See @ref section_buffer_resolution "Maximum Buffer Resolution"
 * <tr><td> Buffer Type     <td>
 * <ul>
 *    <li> Encoding
 *    <li> Preview
 *    <li> Off
 * </ul>
 * <tr><td> Input Window	    <td>
 * <ul>
 *    <li> The input window is cropped from the main source buffer.
 *    <li> The input window size cannot exceed the main buffer size.
 * </ul>
 * <tr><td>Scalability      <td>
 * <ul>
 *    <li> Scale ratio range: 1/8x < ratio < 8x
 * </ul>
 * <tr><td> Alignment       <td>
 * <ul>
 *    <li> Width must be a multiple of 16.
 *    <li> Height must be a multiple of 8.
 * </ul>
 * <tr><td> Encoding        <td>
 * <ul>
 *    <li> H.264
 *    <li> H.265
 *    <li> MJPEG
 * </ul>
 * <tr><td> YUV Dumping <td> Yes
 * <tr><td> ME0/ME1 Dumping <td> Yes
 * </table>
 *
 * @subsubsection fourth_source_buffer 1.4.4 Fourth Source Buffer
 *
 * <table>
 * <caption id="table_fourth_buffer">Table 1-4. Fourth Source Buffer.</caption>
 * <tr><th> Feature		    <th> <div style="width:650px"><B>Description</B></div>
 * <tr><td> Resolution	    <td> See @ref section_buffer_resolution "Maximum Buffer Resolution"
 * <tr><td> Buffer Type     <td>
 * <ul>
 *    <li> Encoding
 *    <li> Preview
 *    <li> Off
 * </ul>
 * <tr><td> Input Window	    <td>
 * <ul>
 *    <li> The input window is cropped from the main source buffer.
 *    <li> The input window size cannot exceed the main buffer size.
 * </ul>
 * <tr><td> Scalability      <td>
 * <ul>
 *    <li> Scale ratio range: 1/16x < ratio < 8x
 * </ul>
 * <tr><td> Alignment       <td>
 * <ul>
 *    <li> Width must be a multiple of 16.
 *    <li> Height must be a multiple of 8.
 * </ul>
 * <tr><td> Encoding        <td>
 * <ul>
 *    <li> H.264
 *    <li> H.265
 *    <li> MJPEG
 * </ul>
 * <tr><td> YUV Dumping <td> Yes
 * <tr><td> ME0/ME1 Dumping <td> Yes
 * </table>
 *
 *
 * @subsubsection fifth_source_buffer 1.4.5 Fifth Source Buffer
 *
 * <table>
 * <caption id="table_fifth_buffer">Table 1-5. Fifth Source Buffer.</caption>
 * <tr><th> Feature		  <th> <div style="width:650px"><B>Description</B></div>
 * <tr><td> Resolution	  <td> See @ref section_buffer_resolution "Maximum Buffer Resolution"
 * <tr><td> Buffer Type   <td>
 * <ul>
 *    <li> Encoding
 *    <li> Preview
 *    <li> Off
 * </ul>
 * <tr><td> Input Window	  <td>
 * <ul>
 *    <li> The input window is cropped from the main source buffer.
 *    <li> The input window size cannot exceed the main buffer size.
 * </ul>
 * <tr><td> Scalability    <td>
 * <ul>
 *    <li> Scale ratio range: 1/8x < ratio < 8x
 * </ul>
 * <tr><td> Alignment     <td>
 * <ul>
 *    <li> Width must be a multiple of 16.
 *    <li> Height must be a multiple of 8.
 * </ul>
 * <tr><td> Encoding      <td>
 * <ul>
 *    <li> H.264
 *    <li> H.265
 *    <li> MJPEG
 * </ul>
 * <tr><td> YUV Dumping <td> Yes
 * <tr><td> ME0/ME1 Dumping <td> Yes
 * </table>
 *
 *
 * @subsubsection sixth_source_buffer 1.4.6 Sixth Source Buffer
 *
 * The sixth buffer is multiplexed with pyramid. It is available only when the pyramid is disabled.
 *
 * Refer to @ref example_sixth_buffer "Sixth Buffer Usage" for more details on the sixth buffer case.
 *
 * <table>
 * <caption id="table_sixth_buffer">Table 1-6. Sixth Source Buffer.</caption>
 * <tr><th> Feature		  <th> <div style="width:650px"><B>Description</B></div>
 * <tr><td> Resolution	  <td> 3840 x 2160
 * <tr><td> Buffer Type   <td>
 * <ul>
 *    <li> Encoding
 *    <li> Preview
 *    <li> Off
 * </ul>
 * <tr><td> Input Window  <td>
 * <ul>
 *    <li> The input window is cropped from the main source buffer.
 *    <li> The input window size cannot exceed the main buffer size.
 * </ul>
 * <tr><td> Scalability   <td>
 * <ul>
 *    <li> Scale ratio range: 1/8x < ratio <= 1x
  * </ul>
 * <tr><td> Alignment     <td>
 * <ul>
 *    <li> Width must be a multiple of 16.
 *    <li> Height must be a multiple of 8.
 * </ul>
 * <tr><td> Encoding      <td>
 * <ul>
 *    <li> H.264
 *    <li> H.265
 *    <li> MJPEG
 * </ul>
 * <tr><td> YUV Dumping <td> Yes
 * <tr><td> ME0/ME1 Dumping <td> Yes
 * </table>
 *
 * @subsection section_buffer_resolution 1.5 Maximum Buffer Resolution
 *
 * The maximum size of each source buffer is limited by hardware. In order to
 * accelerate the processing of image data, the cache memory internal image digital signal processor（IDSP） was
 * used, which is called line buffer. Line buffer is capable of holding a single
 * line of image data. So the resolution of source buffer is limited by the line
 * buffer width. Each source buffer has an independent line buffer. That means the
 * resolution limitation for each source buffer is different. The following table
 * provides a description of width limitation for each line buffer.
 *
 * <table>
 * <caption id="table_line_buffer_width">Table 1-7. Line Buffer Width Limitation.</caption>
 * <tr><th> Source Buffer  <th>  <div style="width:400px"><B>Width</B></div>
 * <tr><td> Main Buffer    <td align="center"> 2048
 * <tr><td> Second Buffer  <td align="center"> 1408 (CV5 / CV52 / CV3) <br>
                                               2048 (CV72)
 * <tr><td> Third Buffer   <td align="center"> 2048
 * <tr><td> Fourth Buffer  <td align="center"> 2048
 * <tr><td> Fifth Buffer   <td align="center"> 2048
 * </table>
 *
 * However, IDSP supports multi-tile to enable the higher resolution. The following
 * figure shows an example for multi-tile. In this case, the line cache width is 1408.
 * The total tile for the source buffer is 3. So the maximum width for the
 * source buffer is 4224.
 *
 * @image html multi_tile_buffer.png "Figure 1-5. Buffer with Multi-Tile."
 *
 * The quantity of tile is determinied by the resolution of main buffer. The
 * maximum resolution of source buffer is divided into 3 intervals according to
 * the width of main buffer, (0, 2048], (2048, 3840] and (3840, 8192]. The
 * sub-sections below show detailed resolution limitation for each source buffer
 * in 4k and 8k case.
 *
 *
 * @subsubsection buffer_resolution_4k 1.5.1 Buffer Resolution in 4K Case
 *
 * In the 4Kp case, the kernel configuration and buffer / encoding specifications are as follows.
 *
 * - For SDK 3.0 Amba build:
 *   @code
 *   build $ make menuconfig
 *          [*] Ambarella Linux Configuration	--->
 *           [*] Ambarella Private Drivers Configuration  --->
 *             [*] Build Ambarella private IAV module  --->
 *               [4096] Max VIN width in pixel
 *               [4096] Max VIN height
 *   @endcode
 *
 * - For Cooper SDK Amba build:
 *   @code
 *   build$ make menuconfig
 *          drv_modules  --->
 *              private  --->
 *                 -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *                      [4096] Max VIN width in pixel
 *                      [4096] Max VIN height
 *   @endcode
 *
 * - For Cooper SDK Yocto build:
 *   @code
 *   build$ make menuconfig
 *          meta-ambabsp  --->
 *              recipes-video  --->
 *                 -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)  --->
 *                      [4096] Max VIN width in pixel
 *                      [4096] Max VIN height
 *   @endcode
 *
 * <table>
 * <caption id="table_max_buf_resolution">Table 1-8. Maximum Buffer Resolution.</caption>
 * <tr><th rowspan="2"> Source Buffer <th colspan=3> Max Width                                            <th rowspan=2> Max Height
 * <tr>                   <th> Main Buffer Width <br> (0, 2048] <th> Main Buffer Width <br> (2048, 3840]  <th>Main Buffer Width <br> (3840, 8192]
 * <tr><td> Main Buffer   <td colspan=3 align="center"> 8192                                              <td rowspan=5 align="center">8192
 * <tr><td> Second Buffer <td align="center"> 1408    <td align="center"> 2816  <td align="center"> 4224
 * <tr><td> Third Buffer  <td align="center"> 2048   <td align="center"> 8192  <td align="center"> 8192
 * <tr><td> Fourth Buffer <td align="center"> 2048   <td align="center"> 8192  <td align="center"> 8192
 * <tr><td> Fifth Buffer  <td align="center"> 2048   <td align="center"> 4096  <td align="center"> 4096
 * </table>
 *
 * When users try to allocate the DSP resources for source buffer, the IAV driver
 * checks the resource limitation according to the structure G_buffer_limit.
 * For more details, refer to
 * <em>
 * check_zoom_limit()
 * </em>,
 * which is located in:
 *
 * <em>
 * `$SDK_ROOT_DIR/ambarella/kernel/drv_modules/private/video/dsp_v6/iav/iav_enc_limit.c`
 * </em>
 *
 * ---
 *
 * @section lua_source_buffer_configuration 2. Source Buffer Configuration
 *
 * Every source buffer output window can be arranged in the @ref canvas_layout.
 * The application must use the following rules for the buffer layout design.
 *
 * <table>
 * <caption id="table_source_buffer_lua"></caption>
 * <tr><th> Item <th><div style="width:230px"><B>Parameter</B></div> <th>Description
 * <tr><td> @anchor anchor_buffer_max_output max_output
 *     <td> {width, height}
 *     <td> The maximum resolution of the source buffer. DSP will allocate enough resouces
 *          inside the DSP for the source buffer according to this value.
 * <tr><td> @anchor anchor_buffer_input input
 *     <td> {offset_x, offset_y, width, height}
 *     <td> The input window of each source buffer. Main Buffer input window is cropped
 *          from VIN (vsrc), and Sub-Buffers' input windows are cropped from Main Buffer
 *          output window.
 * <tr><td> @anchor anchor_buffer_output output
 *     <td> {offset_x, offset_y, width, height}
 *     <td> The output window of each source buffer in canvas. The output offset is in
 *          the canvas coordinate. "width, height" is used to specify the resolution
 *          of the source buffer. Source buffer's domain should not cross the canvas's
 *          border.<br>
 *          Also, output can be set to '{0, 0, 0, 0}'. This means the source
 *          buffer is in standby mode. No "DPTZ" will be applied from the source buffer's
 *          input to output, and no data copy will occur from the source buffer to its'
 *          canvas. Later, users can apply none-zero value to resume the buffer from the
 *          standby mode.
 * </table>
 *
 * Please put DSP into the IDLE state before configuring the properties of the main
 * buffer. The main source buffer crops or scales to the sub source buffers
 * (second/third/fourth/fifth/sixth). When the main buffer size is updated, all sub
 * buffers are affected.<br>
 * The size of the sub-buffer can be configured when there is no stream encoding
 * from it. Changing the sub-buffer size does not affect the other sub-buffers.
 *
 * @par Lua Configuration Overview for Source Buffer
 *
 * Each channel has a set of source buffers. Users can configure the source buffer according to
 * the requirements of their projects. The following is a overview for the buffer configuration.
 *
 * @code
 * chan_0 = {
 *		 … … …
 *	 main = {
 *		 max_output = {1920, 0},
 *		 input		= {0, 0, 1920, 1080},
 *		 output 	= {960, 0, 960, 1080},
 *	 },
 *	 second = {
 *		 … … …
 *	 },
 *	 third = {
 *		 … … …
 *	 },
 *	 fourth = {
 *		 … … …
 *	 },
 *	 fifth = {
 *		 … … …
 *	 },
 *	 sixth = {
 *		 … … …
 *	 },
 * }
 * @endcode
 *
 * @par Only enable "Main" & "Third" Buffer
 *
 * In the following example, only "Main" and "Third" buffer are enabled. Other buffers
 * are in the @ref section_buffer_type  "Off" state.
 *
 * @code
 * chan_0 = {
 *     … … …
 *	   main = {
 *		  max_output = {1920, 0},
 *		  input		= {0, 0, 1920, 1080},
 *		  output 	= {960, 0, 960, 1080},
 *	   },
 *	   third = {
 *		  max_output = {1920, 0},
 *		  input		= {0, 0, 960, 1080},
 *		  output 	= {960, 0, 960, 1080},
 *    },
 * }
 * @endcode
 *
 * @par Enable Raw Buffer Manual Feed
 *
 * @note
 * 	  - The source buffers combined into the same canvas must be in the same type
 *      of canvas, either preview or encode.
 * 	  - The source buffers combined into the same canvas must be with the same
 *      buffer ID, such as all buffers are Third buffers.
 * 	  - The source buffer output size and offset should not exceed the canvas
 *      resolution.
 * 	  - The source buffer output size can be 0x0 to act as a turning off source
 *      buffer. When the output size is 0x0, the buffer type is better to set as off.
 * 	  - The source buffer output size can be different for the channels.
 * 	  - The source buffer output region can be overlapped with other source buffer
 *      output regions in the canvas layout to act as a PIP effect.
 * 	  - The source buffer type must be the same for all channels.
 *
 * See @ref fs_adv_lua "Configure with Lua Script".
 *
 * <br>
 *
 * @section section_source_buffer_example 3. Source Buffer Examples
 *
 * @subsection example_source_buffer_preview Example 1: Preview from Third Buffer with HDMI 480i
 *
 * In this example, the input sensor is IMX274 with MIPI interface. The system
 * resource is configured with a Lua script.
 * @anchor system_resource_1080_linear following is an overview of the system
 * resource for example 1.
 *
 * @image html system_resource_1080_linear.png "Figure 3-1. System Resource."
 *
 * In this case, canvas 2 was configured for "Preview" purpose. The video data
 * in canvas 2 is copied from the Third buffer. Finally, canvas 2 will be sent
 * to VOUT_1 for preview. See @ref fs_basic_canvas.<br>
 * Test steps are as follows.<br>
 * Modification of vout_hdmi.lua file for 480i:
 * @code
 * vout_2 = {
 *      status = "on",
 *      mode = "480i",
 *      input_yuv422 = "yes",
 *      video_output_window = {0, 0, 720, 480},
 *      ...
 * }
 * @endcode
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 *
 * @subsection example_main_encode Example 2: Encode from Main Buffer with Resolution 1080p
 *
 * In order to encode a stream, users are required to put the IAV driver into "Preview" state
 * first (See @ref iav_state_model "IAV Driver State Model").
 *
 * If users did not enter preview mode before, enter the preview with the following command.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 * Then start encoding a stream with the following command.
 *
 * @code
 * board# test_encode -A -h 1080p -b 0 -e
 * board# rtsp_server &
 * @endcode
 *
 * Finally users can view the bitstream through VLC media player. The real-time streaming protocol (RTSP) network
 * URL is as follows.<br>
 *
 * <em> rtsp://10.0.0.2/stream1 </em>.
 *
 * In this example, system resources are the same as @ref example_source_buffer_preview
 * "Example 1". As well as stream A is enabled with resolution 1080p. Users can specify the
 * input canvas with the "-b" option for each stream. Here stream A is input from
 * the canvas 0, and the source buffer of canvas 0 is main buffer.
 * See @ref system_resource_1080_linear "System Resource"
 *
 *
 *
 * @subsection example_dptz Example 3: Digital Pan / Tilt / Zoom
 *
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start 3A statistic if the following command was not executed previously.
 *
 * @code {.sh}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a&
 * @endcode
 *
 * Set up the size of the buffer and enable capture raw data.
 *
 * @code {.sh}
 * board# test_encode -i 1920x1080 -f 30 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    --raw-capture 1\
 *                    -X --bsize 1920x1080 --bmaxsize 1080p\
 *                    -Y --bsize   720x480 --bmaxsize 480p\
 *                    -J --bsize   720x480 --bmaxsize 480p
 * @endcode
 *
 * Apply DPTZ on the main buffer and the sub-buffer.
 *
 * @code {.sh}
 * board# test_dptz -X -s 1152x648 -o 500x200
 * board# test_dptz -Y -s  720x480 -o   0x200
 * board# test_dptz -J -s 1440x960 -o 400x100
 * @endcode
 *
 * Capture data from each buffer.
 *
 * @code {.sh}
 * board# test_yuvcap -i 8 -R -f vin8          # capture data from VIN8 buffer
 * board# test_yuvcap -b 0 -Y -f 1.yuv -F 1    # capture data from main buffer
 * board# test_yuvcap -b 1 -Y -f 1.yuv -F 1    # capture data from second buffer
 * board# test_yuvcap -b 2 -Y -f 1.yuv -F 1    # capture data from third buffer
 * @endcode
 *
 * @image html example_dptz.png Figure 3-2. Digital Pan / Tilt / Zoom.
 *
 * In addition, the following case is for applying DPTZ automatically.
 *
 * @code {.sh}
 * board# test_dptz -X -d 2 -m -300~300 -n -200~200 -p  # auto pan/tilt in specified range
 * board# test_dptz -X -r                               # auto zoom 1x ~ 8x
 * @endcode
 *
 *
 *
 * @subsection example_buffer_type_resolution Example 4: Configure Buffer Type and Resolution
 *
 * Initialize the board and start 3A.
 *
 * @code {.sh}
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a&
 * @endcode
 *
 * Configure the buffer type and resolution. VIN resolution is 3840x2160. Main buffer's
 * size is 4k. By default, it will get the full field of view from VIN. Users cannot change
 * the type of main buffer. It should always be "Encode".
 *
 * Third buffer is enabled for "Preview". Fourth buffer is enabled for "Encode". The
 * resolution of fifth buffer is set to 0x0, which means it is set to standby mode.
 * Second buffer and fourth buffer are disabled.
 *
 * @code {.sh}
 * board# test_encode -i 3840x2160 -f 30 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    -X              --bsize 3840x2160 --bmaxsize 3840x2160\
 *                    -J --btype prev --bsize 1920x1080 --bmaxsize 1080p\
 *                    -L --btype enc  --bsize       0x0 --bmaxsize 1080p\
 *                    -Y --btype off\
 *                    -K --btype off
 * @endcode
 *
 * Once the above command returned successfully. The IAV driver is put into the "Preview"
 * state. Users cannot change the buffer type during "Preview" state. However, the buffer size
 * is still configurable.
 *
 * @code {.sh}
 * board# test_encode -J --bsize 720x480 -L --bsize 720x480
 * @endcode
 *
 * Then, enter "Idle" re-configure buffer type. Put IAV driver into "Preview" once again.
 * In the following command, second buffer and fifth buffer are enabled, and configured
 * as "Encode" type.
 *
 * @code {.sh}
 * board# test_encode -i 3840x2160 -f 30 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    -X              --bsize 1920x1080 --bmaxsize 3840x2160\
 *                    -Y --btype enc  --bsize   720x480 --bmaxsize  480p\
 *                    -J --btype prev --bsize   720x480 --bmaxsize  480p\
 *                    -K --btype enc  --bsize   720x480 --bmaxsize  480p\
 *                    -L --btype enc  --bsize   720x480 --bmaxsize  480p
 * @endcode
 *
 *
 * @subsection example_aspect_ratio Example 5: Source Buffer Aspect Ratio
 *
 * The main buffer sets the FoV equal to the VIN window when no digital PTZ is applied.
 * The second / third / fourth / fifth / seventh buffer is cropped or scaled from the main
 * buffer. Thus, all buffers use identical full FoV and VIN window by default.
 *
 * @par Keep the Entire Field of View with Scale
 *
 * Configure the main buffer with resolution 1080p. The second buffer is generated
 * from the main buffer without cropping. Therefore, second buffer achieves the
 * full FoV.
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\        // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize 480p
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\   // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize 480p)
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h  480p -b 1 -e
 * @endcode
 *
 * In this case, the aspect ratio of main buffer is 16:9 (1080p), and the aspect ratio of
 * second buffer is 3:2 (480p). Therefore, an scaler was applied from main buffer to
 * second buffer. It seems there are some distortions in the second buffer.
 *
 * @anchor anchor_image_aspect
 * @image html buffer_aspect_ratio.png Figure 3-3. a) Main Buffer; b) Keep Full FoV; c) Keep Aspect Ratio.
 *
 * Users can print the configuration of the source buffer using the following command.
 *
 * @code {.c}
 * board# test_encode --show-resource-cfg
 *
 * ...
 * chan_0 = {
 * 	id = 0,
 * 	vsrc = vsrc_0,
 * ...
 * 	main = {
 * 		max_output = {1920, 0},
 * 		input 	 = {0, 0, 1920, 1080},
 * 		output	 = {0, 0, 1920, 1080},
 * 	},
 * 	second = {
 * 		max_output = {720, 0},
 * 		input 	 = {0, 0, 1920, 1080},
 * 		output	 = {0, 0, 720, 480},
 * 	},
 * 	third = {
 * 		max_output = {1920, 0},
 * 		input 	 = {0, 0, 1920, 1080},
 * 		output	 = {0, 0, 1920, 1080},
 * 	},
 * 	fourth = {
 * 		max_output = {1280, 0},
 * 		input 	 = {0, 0, 1920, 1080},
 * 		output	 = {0, 0, 1920, 1080},
 * 	},
 * 	fifth = {
 * 		max_output = {1920, 0},
 * 		input 	 = {0, 0, 1920, 1080},
 * 		output	 = {0, 0, 1280, 720},
 * 	},
 * 	sixth = {
 * 		max_output = {0, 0},
 * 		input 	 = {0, 0, 0, 0},
 * 		output	 = {0, 0, 0, 0},
 * 	},
 * ...
 * }
 * ...
 * @endcode
 *
 *
 * @par Keeping Aspect Ratio
 *
 * Users can use the input window of the sub source buffer to maintain the aspect
 * ratio but sacrifice field of view.
 *
 * In this case, The size of main buffer is 1080p (16:9) and the second buffer
 * is 480p (3:2). To keep the aspect ratio for 480p, the input window size for
 * second buffer should be 1620x1080 (3:2).
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\        // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize 480p --binsize 1620x1080
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\   // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize 480p --binsize 1620x1080)
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h 480p -b 1 -e
 * @endcode
 *
 * See @ref anchor_image_aspect "Picture: c) Keep Aspect Ratio" for result.
 *
 * Another case, main buffer 1080p (16:9) and second buffer VGA (4:3).
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\        // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize vga --binsize 1440x1080
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\   // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize vga --binsize 1440x1080)
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h   vga -b 1 -e
 * @endcode
 *
 *
 * @par Customized Aspect Ratio
 *
 * Set customized aspect ratio with 3/2 and start streaming.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A --sar 3/2
 * board# test_encode -A -h 1080p -e
 * @endcode
 *
 */
/*!
 * @file pyramid.h
 * @brief document for pyramid features
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_pyramid BASIC - Pyramid
 *
 * @section section_pyramid_features 1. Pyramid Features
 * CV5x / CV72 chips support pyramid generation for video content analysis (VCA), and
 * support up to 7 layers of pyramid buffers. Each layer of pyramid can be
 * @ref anchor_layer_map "enable/disable" independently. The data format of each
 * pyramid layer is YUV420 (NV12).
 *
 * @image html pyramid_layout_v6.png "Pyramid Block Diagram"
 *
 * @subsection pyramid_input_buffer 1.1 Pyramid Input Buffer
 *
 * The pyramid is generated from one of the source buffers. Users can choose the
 * @ref anchor_input_buf "pyramid input" from the main buffer, or one of the sub
 * buffers. If Layer 0 of the pyramid is enabled, data from the input buffer
 * will be copied to the buffer of pyramid Layer 0. In addition, the size of pyramid
 * Layer 0 is the same as the pyramid input buffer. Ambarella recommends using
 * the sub buffer as the input for the pyramid buffer, as this can save DRAM
 * bandwidth.
 * @note
 * - When main buffer is specified as pyramid input buffer, it can also be used for encoding.
 * - When sub source buffer is specified as pyramid input buffer, it cannot be
 *   used for neither encoding nor VOUT preview.
 *
 * @subsection pyramid_downsampling 1.2 Pyramid Downsampling Rate
 *
 * In addition to Layer 0, there are two types of @ref anchor_scale_type
 * "downsampling rate" to determine the pyramid sizes: For the first one,
 * each layer width / height is 1/sqrt{2} of the previous layer's width / height;
 * for the second one, each layer width / height is
 * 1/2 of the previous layer's size. For example, suppose that the
 * pyramid input buffer is the fifth buffer with the size 1280 x 720. The
 * output of the pyramid layout is as follows.
 *
 * <table>
 * <caption id="table_pyramid_resolution">Pyramid Layout Table</caption>
 * <tr><th> Layer    <th> sqrt{2}                   <th> 1/2
 * <tr><td> Input    <td colspan="2" align="center"> 1280 x 720
 * <tr><td> Layer 0  <td colspan="2"> 1280 x 720 (*Same as the input buffer*)
 * <tr><td> Layer 1  <td align="center"> 906 x 510  <td align="center"> 640 x 360
 * <tr><td> Layer 2  <td align="center"> 640 x 360  <td align="center"> 320 x 180
 * <tr><td> Layer 3  <td align="center"> 456 x 256  <td align="center"> 160 x 90
 * <tr><td> Layer 4  <td align="center"> 320 x 180  <td align="center"> 80 x 46
 * <tr><td> Layer 5  <td align="center"> 228 x 128  <td align="center"> 40 x 24
 * <tr><td> Layer 6  <td align="center"> 160 x 90   <td align="center"> 20 x 12
 * </table>
 *
 * @subsection pyramid_crop 1.3 Crop from Pyramid
 *
 * The full size for each pyramid layer is determined by the Layer 0 size and
 * the scale type. However, users can @ref anchor_crop_win "specify the cropped window"
 * from the full pyramid layer size. Users can also specify the ROI
 * region as the cropped window, and perform VCA based on this ROI. (This can
 * also save DRAM bandwidth.)
 *
 * @subsection pyramid_feed_mode 1.4 Pyramid Feed Mode
 *
 * Each group of pyramid buffers is generated and reported to Arm® by the digital signal processor (DSP),
 * and is allocated and maintained using three different methods. Additionally, it can be configured
 * through @ref anchor_manual_feed "manual_feed" item or "ext_mem" item in the Lua script. In the pyramid
 * auto-generation mode, pyramid buffers cannot be accessed by the VP. In the pyramid  manual feed mode and
 * pyramid external-memory mode, pyramid buffers can be accessed by the VP.
 *
 * <ul>
 *   <li><B>Pyramid Auto-Generation Mode</B>
 *   <li><B>Pyramid Manual-Feed Mode</B>
 *   <li><B>Pyramid External-Memory Mode</B>
 * </ul>
 *
 * In the pyramid auto-generation mode, DSP allocates and maintains the pyramid
 * buffers. Each time DSP generates a group of pyramid buffers, the group is
 * automatically reported to Arm, which uses the buffers to perform the video
 * content analysis (VCA).
 * However, this method has two disadvantages: <br>
 * <VAR>
 *     <ol>
 *     <li>When Arm receives the pyramid buffers, it copies them to additional
 *         memory to prevent data from being overwritten (in case the user's
 *         application VCA algorithm is insufficient).  (DSP reuses the pyramid
 *         buffers several frames later.)  Copying the data requires extra the
 *         dynamic random-access memory (DRAM) size, bandwidth, and CPU cycles. <br>
 *     <li>Because of the processing speed of the VCA algorithm, user applications
 *         typically fetch pyramid buffers at a lower fps; however, DSP generates
 *         pyramid buffers according to its own processing speed.  As a result,
 *         more DRAM bandwidth are required for DSP to generate extra pyramid
 *         buffers. <br>
 *     </ol>
 * </VAR>
 *
 * To avoid the potential disadvantages of using the pyramid auto-generation
 * mode, Ambarella recommends using the pyramid manual-feed mode instead.  The
 * pyramid manual-feed mode enables Arm to allocate and maintain the pyramid
 * buffers.  Each time an user application requests a group of pyramid buffers,
 * it feeds an empty group to DSP. DSP fills pyramid data into the buffers, and
 * then reports back to Arm.  Because Arm is responsible for the maintaining the
 * pyramid buffers, not feeding them to the DSP before they have been processed is
 * to avoid data overwriting. Additionally, Arm does not need to copy the pyramid
 * buffers into its local memory, and it can control the feeding rate of pyramid
 * buffers, making it unnecessary for DSP to generate pyramid buffers at the image
 * digital signal processing (IDSP) fps. Due to these advantages, including reducing
 * the DRAM bandwidth, Ambarella recommends using the pyramid manual-feed mode for
 * user applications.
 *
 * In the pyramid external-memory mode, Arm allocates the pyramid buffers and DSP maintains
 * these pyramid buffers. These pyramid buffers can be accessed by the VP. Each time DSP
 * generates a group of pyramid buffers, the group is automatically reported to Arm.
 * Because of CV5x and CV72's special architecture, VP cannot access the pyramid memory in the pyramid
 * auto-generation mode. If the user wants the DSP to maintain the pyramid buffers and also VP can
 * access these buffers, then the pyramid external-memory mode is a good choice. <br>
 *
 * @subsection pyramid_arbitrary_scale 1.5 Arbitrary Pyramid Size
 *
 * For the pyramid input, users can choose an arbitrary size instead of the
 * input buffer size. To choose an arbitrary size, users would apply the digital
 * zoom operation from the pyramid's input buffer to the pyramid Layer 1. The
 * pyramid Layer 0 is the same size as the pyramid input buffer. Therefore,
 * there are a maximum of six available pyramid layers. The latter pyramid
 * layers size are down-sampled with the fixed ratio of 2; the ratio of sqrt{2} is
 * no longer supported.<br>
 *
 * See the following figure for a diagram of choosing an arbitrary pyramid size.
 *
 * @image html pyramid_arbitrary_size_v6.png "Arbitrary Pyramid Size"
 *
 * @note
 * - For pyramid layers, it is only supports arbitrary downscaling from Layer 0 to Layer 1.
 *   The downscaling ratio can be various from 1/1 (inclusive) to 1/8 (exclusive).
 *
 * Please check @ref lua_pyramid_configuration for more information.<br>
 *
 * <br>
 *
 * ---
 *
 * @section lua_pyramid_configuration 2. Pyramid Configuration
 *
 * Users can configure the pyramid via Lua script. Here is the parameters for
 * pyramid.<br>
 *
 * <table>
 * <caption id="table_pyramid_lua"></caption>
 * <tr><th> Item <th><div style="width:240px"><B>Parameter</B></div> <th>Description
 * <tr><td> @anchor anchor_input_buf input_buf_id
 *     <td> 0: Main Buffer <br>
 *          1: Second Buffer <br>
 *          2: Third Buffer <br>
 *          3: Fourth Buffer <br>
 *          4: Fifth Buffer
 *     <td> Specifying the input source buffer ID in this channel.
 * <tr><td> @anchor anchor_scale_type scale_type
 *     <td> 0: Downsampled by sqrt{2} <br>
 *          1: Downsampled by 2 <br>
 *          2: Arbitrary Scale
 *     <td> Specifying the paramid downsampling rate.
 * <tr><td> buf_addr
 *     <td> Physical Address
 *     <td> Specifying the external buffer address in pyramid auto-generation mode. It is 0
 *          when pyramid is from DSP internal buffer. In pyramid manual-feed
 *          mode, it must be 0 as its pyramid buffer pool is allocated by IAV driver.
 * <tr><td> buf_size
 *     <td> buf_size >= 0
 *     <td> In pyramid auto-generation mode, it is used to specify the total
 *          external buffer size to store all pyramid layers.  It is valid only
 *          when the "buf_addr" is specified. This total buffer size should
 *          include up to 7 layers, with 4x ~ 8x for circular usage. In pyramid
 *          manual-feed mode, it can also be used to specify a fixed pyramid
 *          buffer pool size. When it is specified, IAV driver won't reallocate
 *          pyramid buffer pool again even if the really required pool size is
 *          changed.
 * <tr><td> @anchor anchor_frame_rate frame_rate
 *     <td> 0 <= frame_rate <= idsp_fps
 *     <td> Specify the pyramid frame rate, it must be less than idsp_fps. (This feature is not yet supported.)
 * <tr><td> @anchor anchor_manual_feed manual_feed
 *     <td> 0: Pyramid Auto-generation Mode <br>
 *          1: Pyramid Manual-feed Mode
 *     <td> Enable pyramid manual-feed mode.
 * <tr><td> item_num
 *     <td> [4, 12]
 *     <td> Specifying the number of the manual feed or external buffers. This value should be in the range of [4, 12]. If lower
 *          than 4, it will be set to 4 by IAV driver. If higher than 12, it will
 *          be set to 12 by IAV driver. If value is 0, it will be set to the
 *          default value 6.<br>
 * <tr><td> rescale_size
 *     <td> {width, height}
 *     <td> Specifying rescale size for pyramid Layer 1. The scale ratio of width or height from
 *          Layer 0 to Layer 1 must be in the range of <b>1X to 8X (Downscale)</b>.
 *          The scale ratio from Layer N(N = 1 ~ 5) to Layer N+1 is fixed to 2X (Downscale).
 *          Only valid when <b>"scale_type == IAV_PYRAMID_SCALE_ARBITRARY"</b>.<br>
 * <tr><td> max_rescale_size
 *     <td> {width, height}
 *     <td> Specifying max rescale size for pyramid Layer 1. Used to set the max rescale size of
 *          pyramid Layer 1, <b>"rescale_size"</b> must be within <b>"max_scale_size"</b>. Only valid
 *          when <b>"scale_type == IAV_PYRAMID_SCALE_ARBITRARY"</b>.<br>
 * <tr><td> @anchor anchor_layer_map layer_map
 *     <td> Bits map
 *     <td> Specifying bits map for pyramid layers, one bit for one layer (eg. bit 0 means layer 0,
 *          bit 1 means layer 1, ... , bit 6 means layer 6), can be changed dynamically.
 *          To enable all 7 layers, set this value to 0x7F.
 * <tr><td> max_layer_map
 *     <td> Bits map
 *     <td> Specifying max bits map for pyramid layers, one bit for one layer (eg. bit 0 means layer 0,
 *          bit 1 means layer 1, ... , bit 6 means layer 6), can only be changed before entering preview.
 *          <b>"layer_map"</b> must be within <b>"max_layer_map"</b>.<br>
 * <tr><td> @anchor anchor_crop_win crop_win
 *     <td> {offset_x, offset_y, width, height}
 *     <td> Specifying the output window of pyramid buffer from each layer.
 *          The default value {0,0,0,0} means the pyramid layer's active window
 *          without cropping, rather than the window with size 0x0.
 * <tr><td> @anchor anchor_enable_frame_tag enable_frame_tag
 *     <td> 0: disable<br>
 *          1: enable
 *     <td> Enable pyramid frame-tag.
 * <tr><td> @anchor anchor_frame_tag_value frame_tag_value
 *     <td> [0, 0xFFFFFFFF]
 *     <td> Specifying frame tag value. Only valid when enable_frame_tag is enabled.
 * <tr><td> @anchor anchor_frame_tag_mask frame_tag_mask
 *     <td> [0, 0xFFFFFFFF]
 *     <td> Specifying bitmask of frame tag. Only valid when enable_frame_tag is enabled.
 *          Note: frame_tag_mask must meet the condition: frame_tag_mask & frame_tag_value = frame_tag_value.
 * <tr><td> @anchor anchor_ext_mem ext_mem
 * 	<td> 0(Default): disable<br>
 * 		 1: enable
 * 	<td> is used to enable pyramid external memory mode. Set to 1 to enable pyramid external memory.
 * </table>
 *
 * <B>An Example for Pyramid Lua Configuration</B><br>
 *
 * @code
 * pyramid = {
 *    input_buf_id = 2,     -- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
 *    scale_type = 0,       -- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
 *    buf_addr = 0x0,
 *    buf_size = 0x0,
 *    manual_feed = 0,
 *    item_num = 0,
 *    layer_map = 0x2A,
 *    layers = {
 *       {
 *          crop_win = {0, 0, 0 ,0},
 *       },
 *       {
 *          crop_win = {0, 0, 0, 0},
 *       },
 *       {
 *          crop_win = {0, 0, 0 ,0},
 *       },
 *       {
 *          crop_win = {0, 0, 0 ,0},
 *       },
 *       {
 *          crop_win = {0, 0, 0 ,0},
 *       },
 *       {
 *          crop_win = {0, 0, 0 ,0},
 *       },
 *       {
 *          crop_win = {0, 0, 0 ,0},
 *       },
 *    },
 * },
 * @endcode
 *
 * See @ref fs_adv_lua "Configure with Lua Script".
 *
 * <br>
 *
 * ---
 *
 * @section section_pryamid_example 3. Pyramid Examples
 *
 *
 * @subsection example_pyramid_data_capture Example 1: Pyramid Data Capture
 *
 * Pyramid can be captured by user application. Here pyramid data from Layer 0 to Layer 6
 * will be captured by <VAR>test_yuvcap</VAR>.<br>
 *
 * The following is the resource configuration.
 * <table>
 * <caption id="table_pyramid_scale">Resource Configure</caption>
 * <tr><th> Item              <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Sensor            <td> IMX274_MIPI    3840 x 2160
 * <tr><td> Pyramid Input     <td> Third Buffer   1920 x 1080
 * <tr><td> Scale Type        <td> scale_type = 0. Pyramid downsampling ratio will be
 *                                 sqrt{2}.
 * <tr><td> Feed Mode         <td> manual_feed = 0. Auto-genetation mode.
 * <tr><td> Pyramid Layer Map <td> layer_map = 0x7F. Enable the pyramid from
 *                                 Layer 0 to Layer 6.
 * </table>
 * Test steps are as follows.
 *
 * @code {.sh}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a&
 * board# *here you need to modify Lua script as described above.*
 * board# test_encode --resource-cfg pyramid.lua
 * board# test_yuvcap -c 0 -P 0~6 -f cap_pyramid
 * Capture_Pyramid_buffer: Pyramid layer 0 for chan 0 resolution 1920x1080 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 1 for chan 0 resolution 1360x770 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 2 for chan 0 resolution 960x540 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 3 for chan 0 resolution 680x386 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 4 for chan 0 resolution 480x270 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 5 for chan 0 resolution 340x194 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 6 for chan 0 resolution 240x136 in NV12 format
 * @endcode
 *
 * The following is a full set of the captured pyramid.
 *
 * @image html example_capture_pyramid_archv6.png "Capture Pyramid Data"
 *
 * @subsection example_pyramid_manual_feed Example 2: Pyramid Manual Feed
 *
 * In lua file, pyramid parameters "manual_feed" and "item_num" should be set to
 * support feeding the pyramid manually. The following is the resource configuration.
 *
 * <table>
 * <caption id="table_pyramid_scale">Resource Configure</caption>
 * <tr><th> Item                 <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Sensor               <td> IMX274_MIPI    1920 x 1080
 * <tr><td> Pyramid Input        <td> Main Buffer   1920 x 1080
 * <tr><td> Scale Type           <td> scale_type = 1. Pyramid downsampling ratio will
 *                                    be 2.
 * <tr><td> Feed Mode            <td> manual_feed = 1. Enable pyramid manual feed
 * <tr><td> Pyramid Buffer Item  <td> item_num = 6. Buffer alloced by IAV for pyramid
 *                                    manual feed are set to 6.
 * <tr><td> Pyramid Layer Map    <td> layer_map = 0x2f. Enable pyramid Layer0, Layer1, Layer2,
 *                                    Layer3, and Layer5.
 * </table>
 *
 * Test steps are as follows. As well as the Lua script can be found
 * <a href="script/pyramid_manual_feed.lua" target="_blank"><b>here</b></a>.
 * Put the script in the same folder where you launch the <em> test_encode </em> command.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a&
 * board# *here you need to modify Lua script as described above.*
 * board# test_encode --resource-cfg pyramid_manual_feed.lua
 * board# test_manual_feed -c 0 -q 1
 * Pyramid buffer pool phys_addr 0xf1100000 map to virt_addr 0x7f8c360000, with total size 0x24e4000.
 * Chan_0 Pyramid Layer 0: pts = 0, y_data = 0x7f8c360000, uv_data = 0x7f8c779280, dma_buf_fd = -1.
 * Chan_0 Pyramid Layer 0: pts = 0, y_data = 0x7f8c986000, uv_data = 0x7f8cd9f280, dma_buf_fd = -1.
 * Chan_0 Pyramid Layer 0: pts = 0, y_data = 0x7f8cfac000, uv_data = 0x7f8d3c5280, dma_buf_fd = -1.
 * Chan_0 Pyramid Layer 0: pts = 0, y_data = 0x7f8d5d2000, uv_data = 0x7f8d9eb280, dma_buf_fd = -1.
 *
 * ...
 * @endcode
 *
 * @subsection example_pyramid_arbitrary_scale Example 3: Pyramid Arbitrary Scale
 *
 * In this example Ambarella uses IMX274_MIPI with 4K input resolution. Pyramid input is main
 * buffer, which has a 4K output resolution. Then the pyramid Layer 1 is re-scaled from 4K to 720p.
 * <table>
 * <caption id="table_pyramid_scale">Resource Configure</caption>
 * <tr><th> Item                 <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Sensor               <td> IMX274_MIPI    3840 x 2160
 * <tr><td> Pyramid Input        <td> Main Buffer   3840 x 2160
 * <tr><td> Scale Type           <td> scale_type = 2. Apply pyramid arbitraty scale, and
 *                                    the downsampling ratio will be 2.
 * <tr><td> Pyramid Rescale Size <td> rescale_size = {1280, 720}. Pyramid Layer 1
 *                                    will be re-scaled to 720p.
 * <tr><td> Pyramid Layer Map    <td> layer_map = 0x7F. Enable the pyramid from layer 0 to layer 6.
 * </table>
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a&
 * board# *here you need to modify Lua script as described above.*
 * board# test_encode --resource-cfg pyramid_arbitrary_scale.lua
 * board# test_yuvcap -c 0 -P 0~6 -f cap_pyramid
 * Capture_Pyramid_buffer: Pyramid layer 0 for chan 0 resolution 3840x2160 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 1 for chan 0 resolution 1280x720 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 2 for chan 0 resolution 640x360 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 3 for chan 0 resolution 320x180 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 4 for chan 0 resolution 160x90 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 5 for chan 0 resolution 80x46 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 6 for chan 0 resolution 40x24 in NV12 format
 * @endcode
 *
 * In this case, Layer 0 is copied from the input buffer. The size of Layer 0 is
 * the same as the output of the input buffer. Then Layer 1 is re-scaled from 4K
 * to 720p. After that each layers will be down-sampled with the ratio of 2.<br>.
 *
 * @subsection example_change_pyramid_configurations Example 4: Change Pyramid Rescale Size and Layer Map Dynamically.
 *
 * This example shows the method on how to change the rescale size from 1080p to 720p, and the
 * layer map from "0x1f" to "0x3f" dynamically.
 *
 * In this example, the initial pyramid configurations are set as shown in the following table when
 * entering the preview state.
 *
 * <table>
 * <caption id="table_pyramid_configuration">Preview Resource Configuration</caption>
 * <tr><th> Item                 <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Sensor               <td> IMX274_MIPI   3840 x 2160
 * <tr><td> Pyramid Input        <td> Main Buffer   3840 x 2160
 * <tr><td> Scale Type           <td> scale_type = 2. Apply pyramid arbitraty scale, and
 *                                    downsampling ratio will be 2.
 * <tr><td> Pyramid Rescale Size <td> max_rescale_size = {1920, 1080}. Pyramid Layer 1
 *                                    size should no greater than 1920x1080.<br>
 *                                    rescale_size = {1920, 1080}. Pyramid Layer 1
 *                                    will be re-scaled to 1080p.
 * <tr><td> Pyramid Layer Map    <td> max_layer_map = 0x3F. Only layers within max layers
 *                                    map can be turned on/off dynamically.<br>
 *                                    layer_map = 0x1F. Enable the pyramid
 *                                    from Layer 0 to Layer 4.
 * </table>
 *
 * After entering the preview state, users can change the pyramid rescale size and the layer map
 * dynamically. As an example in following table, the pyramid rescale size is updated to 720p, and
 * the layer map is updated to "0x3f".
 *
 * <table>
 * <caption id="table_pyramid_configuration">Target Resource Configuration</caption>
 * <tr><th> Item                 <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Pyramid Rescale Size <td> rescale_size = {1280, 720}. Pyramid Layer 1
 *                                    will be re-scaled to 720p.
 * <tr><td> Pyramid Layer Map    <td> layer_map = 0x3F. Enable the pyramid
 *                                    from Layer 0 to Layer 5.
 * </table>
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a&
 * board# *here you need to modify Lua script as described above.*
 * board# test_encode --resource-cfg pyramid_change_rescale_size_and_layer_map.lua
 * board# test_multi_chan -c 0 --prescalesize 1280x720 --pLayers 0x3f
 * board# test_yuvcap -c 0 -P 0~6 -f cap_pyramid
 * Capture_Pyramid_buffer: Pyramid layer 0 for chan 0 resolution 3840x2160 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 1 for chan 0 resolution 1280x720 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 2 for chan 0 resolution 640x360 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 3 for chan 0 resolution 320x180 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 4 for chan 0 resolution 160x90 in NV12 format
 * Capture_Pyramid_buffer: Pyramid layer 5 for chan 0 resolution 80x46 in NV12 format
 * Pyramid channel 0: layer 6 is not switched on
 * @endcode
 *
 * @subsection example_pyramid_external_mem Example 5: Pyramid External Memory
 *
 * Here is an example for used external memory for pyramid. As well as the Lua script can be found
 * <a href="script/pyramid_ext_mem.lua" target="_blank"><b>here</b></a>.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg pyramid_ext_mem.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 */
/*!
 * @file canvas.h
 * @brief document for canvas features
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_canvas BASIC - Canvas
 *
 * @section canvas_manual_feed 1. Canvas Features
 * The source buffers for different "channel"
 * can be placed in the same canvas, and then sent to video output (VOUT) for preview, or video digital signal processor (VDSP)
 * for encode.<br>
 * The following figure describes the mapping relationship between VIN, channels,
 * source buffers, and then to canvases.
 *
 * @image html canvas_mapping.png "Figure 1-1. Canvas Mapping."
 *
 * @subsection canvas_layout 1.1 Flexible Canvas Layout
 *
 * The source buffers from different "channel" can be placed in either independent
 * canvases, such as Canvas 2 and Canvas 3, or combined together to the same
 * canvases, such as Canvas 0 and Canvas 1. Blend view enables placement of different
 * source buffers side-by-side, horizontally and vertically. Picture in picture (PIP) view enables
 * placing one or more small source buffers above a large source buffer.<br>
 * The canvases from sub source buffers can have their own frame rates. This requires
 * digital signal processor (DSP) to output the same frame rate for each source buffer, which is put in the same
 * canvas.<br>
 *
 * @note
 * - Users must propose a layout design before entering @ref iav_state_model "Preview".
 *   Change the canvas layout on the fly is not permitted.
 * - Main buffer must be placed in a canvas for encoding purpose.
 *
 * @subsection canvas_feed_mode 1.2 Canvas Feed Mode
 *
 * Each canvas buffer is generated and reported to Arm® by DSP, and is allocated and
 * maintained using three different methods. In addition, it can be configured through
 * @ref anchor_canvas_manual_feed "manual_feed" item or "ext_mem" item in the Lua script.
 * In the canvas auto-generation mode, canvas buffers cannot be accessed by the vector processor (VP). 
 * In the canvas manual feed mode and canvas external-memory mode, canvas buffers can be
 * accessed by VP.
 *
 * <ul>
 *   <li><B>Canvas auto-generation mode</B>
 *   <li><B>Canvas manual-feed mode</B>
 *   <li><B>Canvas external-memory mode</B>
 * </ul>
 * In the canvas auto-generation mode, DSP allocates and maintains the canvas
 * buffers. Each time DSP completes drawing all the canvas buffers, then it is
 * automatically reported to Arm. In auto-generation mode, DSP will guarantee the frame rate.<br>
 *
 * However, users may not need to query the canvas data at the image digital signal processing (IDSP)
 * fps to reduce the system load. In the canvas manual feed mode, the frame queue is fully driven and
 * controlled by user application. Each time a user application requests a canvas buffers, it will trigger
 * the image audio video (IAV) driver to feed an empty buffer address to the DSP. DSP fills canvas
 * data into the buffers, and then reports back to Arm. This feature will significantly save the
 * dynamic random-access memory (DRAM) bandwidth if users need to query canvas at a very low frame rate.<br>
 *
 * In the canvas external-memory mode, Arm allocates the canvas buffers and DSP maintains
 * these canvas buffers. These canvas buffers can be accessed by the VP. Each time DSP
 * completes drawing all the canvas buffers, then it is automatically reported to Arm.
 * Because of CV5x's special architecture, VP cannot access the canvas memory in the canvas
 * auto-generation mode. If the user wants the DSP to maintain the canvas buffers and also VP can
 * access these buffers, then the canvas external-memory mode is a good choice. <br>
 *
 * @note
 * In the canvas manual feed mode, IAV has the following limitations.
 * 	  - Only support "encode" canvas for manual feed.
 * 	  - When canvas is in the manual-feed mode, it cannot be used for VOUT or encoding.
 * 	  - Do not support canvas manual feed in *multi-region dewarp mode*
 *
 *
 * ---
 *
 * @section canvas_configuration 2. Canvas Configuration
 * Users can configure the canvas via Lua script. Here are the canvas parameters.<br>
 *
 * <table>
 * <caption id="table_canvas_lua"></caption>
 * <tr><th>Item     <th><div style="width:180px"><B>Parameter</B></div>      <th>Description
 * <tr><td> @anchor anchor_canvas_type type
 *     <td> "prev"<br>
 *          "encode"<br>
 *     <td> Specifies the canvas type. It can be either "encode"
 *          or "prev". There is no "off" type for canvas. If application needs to turn
 *          off the canvas, it has to reconfigure the system and remove the canvas
 *          definition. If canvas type is preview, it outputs YUV422 or YUV420 format with UV
 *          interleaved data. If canvas type is encoded, it outputs YUV420 format with
 *          UV interleaved data.
 * <tr><td> @anchor anchor_canvas_size size
 *     <td> {width, height}
 *     <td> Specifies the canvas resolution.
 * <tr><td> @anchor anchor_canvas_source source
 *     <td> 1: chan_x.main <br>
 *          2: chan_x.second <br>
 *          3: chan_x.third <br>
 *          4: chan_x.fourth <br>
 *          5: chan_x.fifth <br>
 *          6: chan_x.sixth <br>
 *     <td> Specifies the source buffer of channels to canvas.
 *          DSP follows the source buffer declare order to put channel source buffer
 *          data in this field. The latter source buffer is put in with a higher Z
 *          order and may cover the source buffer with a lower Z order. The channels
 *          whose source buffer are put to the same canvas must have the same
 *          "idsp_fps".<br>
 * <tr><td> @anchor anchor_canvas_vout_id vout_id
 *     <td> 0/1: VOUT1 (CSI, DSI)<br>
 *          2: VOUT2 (HDMI, CVBS)
 *     <td> Specifies VOUT. If setting to 2, VOUT2 (like HDMI,
 *          CVBS) will be used to show preview canvas.  If setting to 0/1, VOUT0/1 (like CSI,
 *          DSI) will be used to show preview canvas.
 * <tr><td> @anchor anchor_canvas_vout_YUV422 vout_YUV422
 *     <td> 0: VOUT format is 420<br>
 *          1: VOUT format is 422
 *     <td> Specifies the YUV format of "prev"
 *          type canvas.  If setting to 1, its YUV format is YUV422.  Then VOUT captures
 *          the display data from it directly to show out. If setting to 0, its YUV format
 *          is YUV420 which is the same as other "encode" type canvases. Then VOUT will
 *          convert it to YUV422 before showing out.<br>
 * <tr><td> @anchor anchor_canvas_vout_back_pressure_margin vout_back_pressure_margin
 *     <td> [0,3]<br>
 *          0 means use the default value 2
 *     <td> Specifies the back pressure margin for the VOUT.
 * <tr><td> @anchor anchor_canvas_manual_feed manual_feed
 *     <td> 0: automic feed mode<br>
 *          1: manual feed mode
 *	   <td> Enables canvas manual feed. Set to 1 to enable manual feed. Set
 *          to 0 to automatically feed by DSP.
 * <tr><td> @anchor anchor_canvas_feed_frame_num feed_frame_num
 *     <td> [4, 12]
 *	   <td> Specifies the manual feed or external buffers. In the canvas manual feed or
 *          the external buffer mode, IAV allocates the YUV buffers in kernel driver memory.
 *          This value should be in the range of [4, 12]. If the value is lower than 4, it will be set
 *          to 4 by IAV driver. If the value is higher than 12, it will be set to 12 by IAV driver.
 * <tr><td> @anchor anchor_canvas_extra_dram_buf extra_dram_buf
 *     <td> i >= 0
 *	   <td> Specifies the extra DRAM frames for the canvas.
 * <tr><td> @anchor anchor_canvas_cached_items cached_items
 *     <td> extra_dram_buf >= 1: [1, extra_dram_buf]<br>
 *          Default: 1
 *	   <td> Specifies cached items for canvas buffer information when it is queried by user application.
 *          By default, cached_items = 1, IAV driver only keeps the latest canvas buffer. When
 *          the latter comes, the former will be discarded.
 *          When cached_items > 1, IAV driver will maintain a FIFO whose depth = cached_items.
 *          So user application can catch up if previous canvas buffer querying is postponed.
 * <tr><td> @anchor anchor_canvas_clear_background clear_background
 *     <td> 0: disable<br>
 *          1: enable
 *     <td> Clears the canvas memory to blackground color after entering preview.
 * <tr><td> @anchor anchor_enable_frame_tag enable_frame_tag
 *     <td> 0: disable<br>
 *          1: enable
 *     <td> Enables canvas frame tag pattern feature.
 * <tr><td> @anchor anchor_frame_tag_value frame_tag_value
 *     <td> [0, 0xFFFFFFFF]
 *     <td> Sets canvas frame tag value. This value is valid when enable_frame_tag flag is enabled.
 * <tr><td> @anchor anchor_frame_tag_mask frame_tag_mask
 *     <td> [0, 0xFFFFFFFF]
 *     <td> Sets canvas frame tag mask. This value is valid when enable_frame_tag flag is enabled.
 * <tr><td> @anchor anchor_zero_fps zero_fps
 *     <td> 0: disable<br>
 *          1: enable
 *     <td> Enables 0 fps canvas frame rate. When setting to 0, "frame_rate = 0" represents idsp_fps.
 *          When setting to 1, "frame_rate = 0" is real 0 fps.
 * <tr><td> @anchor anchor_enc_dummy_latency enc_dummy_latency
 *     <td> i >= 0
 *     <td> Specifies the latency number of encode dummy buffer.
 * <tr><td> @anchor anchor_frame_rate frame_rate
 *     <td> i >= 0
 *     <td> Specifies the canvas frame rate, it must be less than idsp_fps.
 * <tr><td> @anchor anchor_set_min_unlocked_buf_num set_min_unlocked_buf_num
 *     <td> 0: disable<br>
 *          1: enable
 *     <td> Enables set min_unlocked_buf_num config.
 * <tr><td> @anchor anchor_min_unlocked_buf_num min_unlocked_buf_num
 *     <td>
 *     <td> Specifies canvas minimum unlocked buffer number. When users want to set min_unlocked_buf_num accordingly, users need
 *          to enable manual_feed and set_min_unlocked_buf_num first. Meanwhile, item_num > min_unlocked_buf_num.
 * <tr><td> @anchor anchor_blend_stitch_type blend_stitch_type
 *     <td> 0: no blend<br>
 *          1: blend horizontally
 *          2: blend veritically
 *     <td> Specifies canvas blend stitch type. It can be no blending, horizontally blending,
 *          or vertical blending.
 * <tr><td> @anchor anchor_blend_stitch_circular_margin blend_stitch_circular_margin
 *     <td> i >= 0
 *     <td> Specifies the overlap margin of the last channel and first channel.
 *          Only valid when "blend_stitch_type" isn't 0.
 * <tr><td> @anchor anchor_blend_warp_enable blend_warp_enable
 *     <td> 0: disable<br>
 *          1: enable
 *     <td> Enables H warp for blending overlap region. Only valid when "blend_stitch_type" isn't 0.
 * <tr><td> @anchor anchor_disable_yuv_dram disable_yuv_dram
 *     <td> 0(Default): Allocate buffer<br>
 *          1: Not allocate buffer
 *     <td> Allows DSP to allocate canvas YUV buffer or not. It can be used to save DSP DRAM.
 * <tr><td> @anchor anchor_fps_locked_enable fps_locked_enable
 *     <td> 0 (Default): disable<br>
 *          1: enable
 *     <td> If this flag is enabled, canvas fps will be locked. When IDSP fps is changed on the fly, it will not be changed proportionally when it is <= IDSP fps.
 * <tr><td> @anchor anchor_ext_mem ext_mem
 *     <td> 0 (Default): disable<br>
 *          1: enable
 *     <td> Enables the canvas external memory mode. Set to 1 to enable the canvas external memory.
 * <tr><td> @anchor anchor_extra_padding enc_extra_padding_enable
 *     <td> 0 (Default): disable<br>
 *          1: enable
 *     <td> Enables extra padding for streams encoding with offset. Set to 1 to enable extra padding.
 * </table>
 *
 * <B>An Example for Canvas Lua Configuration</B><br>
 *
 * @code
 * canvas = {
 *     {
 *       type = "encode",            -- canvas 0 is for "encode" purpose.
 *       size = {0, 0},              -- min size to contain source buffers.
 *       source = {"chan_0.main",},  -- input from main buffer.
 *       manual_feed = 1,            -- enable manual feed.
 *       feed_frame_num = 8,         -- buffer item mantained by iav driver.
 *       extra_dram_buf = 2,         -- to support multi-stream encoded from the same canvas.
 *       cached_items = 2,           -- to specify 2 cached items for canvas buffer info.
 *     },
 *     {
 *       type = "prev",              -- canvas 1 is for "prev" purpose.
 *       size = {0, 0},              -- min size to contain source buffers.
 *       source = {"chan_0.third",}, -- input from third buffer.
 *       vout_id = 1,                -- use "HDMI" or "CVBS" output.
 *       vout_YUV422 = 0,            -- to specify the YUV format of "prev" type canvas is YUV420.
 *       vout_back_pressure_margin = 3, -- to specify 3 as the current vout[1] input FIFO depth.
 *       extra_dram_buf = 0,         -- to support multi-stream encoded from the same canvas.
 *       cached_items = 1,           -- to specify 1 cached items for canvas buffer info.
 *     },
 *     {
 *       type = "encode",              -- canvas 2 is for "encode" purpose.
 *       size = {0, 0},                -- min size to contain source buffers.
 *       source = {"chan_0.fourth",},  -- input from the fourth buffer.
 *       extra_dram_buf = 2,           -- to support multi-stream encoded from the same canvas.
 *       frame_rate = 0,               -- set canvas frame rate to 0 fps
 *       zero_fps = 1,                 -- When zero_fps is 0, "frame_rate = 0" represents idsp_fps. When zero_fps is 1, "frame_rate = 0" is real 0 fps.
 *     },
 * }
 * @endcode
 *
 * @note
 * 	  - The maximum canvas number is up to 20.
 * 	  - The canvas type must be either preview or encode. There is no off type.
 * 	  - The source buffer outputs combined in the same canvas, must be in the same buffer
 *      type, preview, encode or off.
 * 	  - DSP must output the same frame rate for each source buffer, which are put in
 *      the same canvas.
 *
 * <br>
 *
 * ---
 *
 * @section section_canvas_example 3. Canvas Examples
 *
 * @subsection example_manual_feed_main_buffer Example 1: Manual Feed Main Canvas
 *
 * Here is an example for feeding canvas which is input from the main buffer. As well as the Lua script can be found
 * <a href="script/canvas_manual_feed_main.lua" target="_blank"><b>here</b></a>.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg canvas_manual_feed_main.lua
 * board# test_manual_feed -a 0 -Q 1
 * @endcode
 *
 * @subsection example_manual_feed_second_buffer Example 2: Manual Feed Second Canvas
 *
 * Also, users can feed the second canvas which is input from the second buffer manually. As well as the Lua script can be found
 * <a href="script/canvas_manual_feed_second.lua" target="_blank"><b>here</b></a>.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg canvas_manual_feed_second.lua
 * board# test_manual_feed -a 1 -Q 1
 * @endcode
 *
 * @subsection example_runtime_update_canvas_fps Example 3: Update Canvas Framerate at Runtime
 *
 * -# Update canvas framerate on the fly
 *
 * Use "test_multi_chan", canvas framerate can be updated on the fly.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode -i 0 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_multi_chan -C 2 -F 15
 * @endcode
 *
 * -# Set default framerate of canvas to IDSP
 *
 * In this example, "0" means canvas framerate is set by default to IDSP framerate rather than real 0 fps.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode -i 0 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_multi_chan -C 2 -F 0
 * @endcode
 *
 * -# Set canvas framerate to real 0 fps.
 *
 * Canvas framerate are required to be set to 0 fps at runtime when it is not used temporarily. This can save the DRAM bandwidth.
 * Use "test_multi_chan" option "z", the canvas framerate can be set to real 0 fps.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode -i 0 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_multi_chan -C 2 -F 0 -z
 * @endcode
 *
 * Or the user can set real 0 fps via lua.
 * @code
 *        canvas = {
 *             .....
 *             {
 *                   type = "encode",
 *                   size = {0, 0},
 *                   source = {"chan_0.third",},
 *                   zero_fps = 1,
 *					 .....
 *             },
 *        }
 * @endcode
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * @subsection example_canvas_external_mem Example 4: Canvas External Memory
 *
 * Here is an example for used external memory for canvas0. As well as the Lua script can be found
 * <a href="script/canvas_ext_mem.lua" target="_blank"><b>here</b></a>.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg canvas_ext_mem.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_canvas_extra_padding Example 5: Canvas Extra Padding Enable
 *
 * Sometimes canvas is used for encoding streams with offsets, if the stream aligned size + offset
 * size is larger than the canvas size, enable the option enc_extra_padding_enable to add an extra padding.
 *
 * For example, try the changes below based on the `lua xxx_vin0_1080p_linear_rotate.lua` in the board.
 * @code
 *        fourth = {
 *                max_output = {0, 0},
 *                input      = {0, 0, 0, 0},
 *                output     = {0, 0, 368, 640},
 *        },
 *        .....
 *        canvas = {
 *             .....
 *             {
 *                   type = "encode",
 *                   size = {0, 0},
 *                   source = {"chan_0.fourth",},
 *                   extra_dram_buf = 0,
 *                   enc_extra_padding_enable = 1,
 *             },
 *        }
 * @endcode
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_rotate.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -b 3 -h 360x640 --offset 4x0 -e
 * @endcode
 *
 * In this case, the canvas size is 368x640 and encoding stream size is 360x640 with offset 4x0,
 * then the stream aligned size would be 368x640 (16-pixels alinged) with offset 4x0, so
 * the total size is 372x640, which is larger than canvas size 368x640.
 *
 * @subsection example_canvas_yuv_disable Example 6: Canvas YUV Disable
 *
 * Disabling YUV data output into DRAM for each canvas can reduce the DRAM bandwidth (BW)
 * for some special applications that generally do not require the YUV data.
 *
 * The `disable_yuv_dram` is used for Canvas's YUV disable or enable.
 * This example here is for Canvas to disable YUV from Main Buffer.
 *
 * @code
 * 	   canvas = {
 * 			{
 * 				  .....
 * 				  source = {"chan_0.main",},
 * 				  disable_yuv_dram = 1,
 * 				  .....
 * 			},
 * 			.....
 * 	   }
 * @endcode
 *
 * The case above means that the YUV output is disabled for this canvas and no YUV
 * data will be generated.
 *
 * @note 
 * Disabling YUV is related to encoding, video output, and YUV capture, and all of
 * features which rely on the YUV data generated by this canvas will fail.
 *
 */

/*!
 * @file stream.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_stream BASIC - Stream
 *
 * CV5x / CV72 can encode up to twenty streams simultaneously. The streams can include
 * different configurations for profile, resolution, bit rate, frame rate,
 * group of pictures (GOP) setting, and duration. Each stream can be independently started or stopped.
 *
 * @section section_stream_features 1. Stream Features
 *
 * @subsection section_stream_input 1.1 Stream Input -- from Single Canvas
 *
 * For multi-channel design, each channel's source buffer can output the data
 * with different resolutions independently. Then user application can put the
 * final outputs of these source buffers together into one canvas so that the
 * stream encoded from this canvas can cover several field of views (FoVs) of different video input (VIN) channels.
 * The streams can be encoded from any of the canvases, which are configured as an
 * "encode" type. Alternatively, the application can encode several streams cropped
 * from different areas of one canvas separately.
 *
 * @image html stream_input_from_canvas.png Figure 1-1. Stream Encode from Canvas.
 *
 * The above cases have two possible ways for a stream encoded from a source canvas.
 *
 * <ul>
 *	  <li>Stream is encoded with the same size and FoV as its source canvas
 *	  <li>Stream is encoded with a cropped area and smaller FoV than its source canvas.
 * </ul>
 *
 * Because the source canvas from each channel contains the source buffers that
 * have already been cropped and scaled from its VIN, the video digital signal processor (VDSP) does not support re-scale
 * from canvas anymore. However users can encode from the area of interest, which will
 * sacrifice its FoV.

 * The benefits of using different canvases for streams include the following:<br>
 *
 * <ul>
 *	  <li> Full FoV for streams
 *	  <li> Independent overlays for each stream
 *	  <li> Changing the buffer size (except for the main buffer) does not affect
 *         the other streams
 *	  <li> Independent effect of the digital pan / tilt / zoom (DPTZ)
 * </ul>
 *
 * See @ref fs_basic_canvas "Canvas".
 *
 * @subsection section_stream_multi_input 1.2 Stream Input -- From Multi-Canvas
 *
 * As introduced above, each stream usually is encoded from only one source canvas.
 * Sometimes, there is a special requirement to have one stream encoded from
 * multiple source canvases. The CV5x / CV72 VDSP provides such capability. When these canvases
 * are encoded to the same stream, they will be encoded sequentially in frame-interleaved
 * order.
 *
 * @image html stream_input_from_multi_canvas.png "Figure 1-2. Stream Encode from Multi-Canvas."
 *
 * Canvases that will be encoded to a single stream must meet the following requirements:<br>
 *
 * <ul>
 *	  <li> Have the same canvas size
 *	  <li> Have the same canvas framerate
 * </ul>
 *
 * @subsection section_frame_rate 1.3 Frame Rate
 *
 * The frame rate cannot be larger than the image digital signal processing (IDSP) frame rate or smaller than 1 frames per second (fps).
 *
 * <b> Encoding Frame Rate = IDSP Frame Rate * Frame Factor (0 < Frame Factor ≤ 1) </b>
 *'
 * If a stream's frame rate is scaled by the frame factor, the time interval
 * between two consecutive frames may not be a constant value. The IDSP frame
 * rate can be larger than VIN frame rate if the IDSP frame rate upscaling is
 * enabled.
 *
 * For example, assume that the VIN frame rate is 30 fps, the IDSP frame rate
 * is 30 fps, and stream A is 20 fps. Use a frame factor of 20/30 to scale the
 * IDSP frame rate.  The time interval between two output encoded frames can be
 * 33 MS or 66 MS. However, there are only 20 frames in one second.
 *
 * To obtain identical time intervals between every frame, set the stream
 * frame rate to equal the IDSP frame rate.
 *
 * See @ref fs_basic_fps "Frame Rate".
 *
 * @subsection section_bit_rate 1.4 Bit Rate
 *
 * The bit rate is for H.264 / H.265, and changes with the frame factor.
 *
 * <b>
 * Encoding Bit Rate = Target Bit Rate * Frame Factor (0 < Frame Factor ≤ 1)
 * </b>
 *
 * If a stream's frame rate changes quickly, for example, from 30 fps to fewer,
 * the actual encoded bit rate will decrease proportionally with the frame
 * factor.
 *
 * If an application requires a constant bit rate (CBR), even when the frame
 * rate is changed to other values, it must to configure the bit rate multiplied
 * by the reciprocal of the frame factor with the frame factor together. Then,
 * DSP will output the constant bit rate for the lower frame rate stream.
 *
 * The image audio video (IAV) driver supports the feature of absolute bit rate
 * (@ref example_absolute_bitrate), which can help user applications to achieve
 * this goal automatically when changing the stream frame rate at runtime.
 *
 * The average bit rate calculated inside the DSP is based on the GOP
 * length, not seconds. This is because if the GOP length is longer than one second,
 * the average bit rate computed in seconds would fluctuate for every GOP length.
 *
 * The IAV driver supports the feature of strict constant bit rate (@ref example_strict_constant_bitrate),
 * which is used to keep the actual bit rate around the target bit rate as much as possible
 * whenever the scene is in motion or static.
 *
 * The DSP also supports high bit rate encoding for advanced video coding (AVC) and high-efficiency video
 * coding (HEVC). To achieve the high bit rate, the user application must set a smaller
 * QP-limit value for I / P / B frames. Beause the default QP ranges in the IAV driver are
 * designed for low bit-rate cases rather than high bit-rate cases.
 *
 * The average bit rate calculated in the first second would be higher than
 * the rest of the seconds due to the large frame size of the first I frame.
 *
 *
 * @subsection section_maximum_gop_m 1.5 Maximum GOP M
 *
 * The maximum GOP M field provides information to DSP, as well as information
 * about allocating dynamic random access memory (DRAM) for the reference frames in H.264 / H.265 encoding.
 *
 * For H.264 / H.265 encoding, a valid range is between 1~3. The larger the
 * number is, the more reference frames DSP allocates for encoding are. This results
 * in DSP reserving more DRAM for H.264 / H.265 encoding. If multiple reference
 * frames are not needed in the user applications, Ambarella recommends setting
 * it to 1 to save the DSP DRAM footprint. Additionally, when the value is greater than 1,
 * DSP will also need to allocate extra internal resources.
 * To prevent the DSP from hanging due to the shortage of internal resources, the
 * default configuration is stream A / B enables max_gop_M > 1, while other streams
 * cannot.
 *
 * MJPEG encoding can be set to zero to save DRAM, especially for larger
 * resolutions such as 6 MP, or a small system DRAM.
 *
 *
 * @subsection section_gop_n 1.6 GOP N
 *
 * The GOP N (GOP length) field provides information to DSP on how many frames
 * have one IDR / I frame, and it is a run-time to the changeable parameter for
 * H.264 / H.265 encoding.
 *
 * The longest GOP length (N) is 1800, or about 60 seconds (1800 = 30 * 60)
 * for 30 fps streams.  When the application changes the GOP N value dynamically,
 * the action is immediately applied to the current GOP. Additionally, an IDR frame
 * is immediately generated if the frame number in the current GOP already
 * exceeds the new GOP length. This feature is called "instant GOP change"
 * instead of "run-time GOP change".
 *
 *
 * @subsection section_encode_duration 1.7 Encode Duration
 *
 * The encode duration provides information on the number of frames to be encoded
 * in the stream. A valid range is from 0~65535.
 *
 * For example, if the application sets "encode duration" to a non-zero value,
 * the DSP will automatically stop encoding after these frames are encoded.
 * This eliminates the need for Arm® to issue an encode stop command. If the
 * application sets the "encode duration" as a zero value, the application
 * issues an encode stop command explicitly.
 *
 * This feature supports H.264 / H.265 and MJPEG in all modes. If there is no
 * change, the image audio video (IAV) driver retains the previous value.
 *
 *
 * @subsection section_encode_frame_drop 1.8 Encode Frame Drop
 *
 * The encode frame drop provides information on the number of frames that
 * will be discarded and not be encoded for the specified stream. The valid
 * range is from 1~255.
 *
 * If the application sends "encode frame drop" command,
 * the DSP will discard the upcoming frames and will not encode them into the bit
 * stream. This feature will not change the GOP length. For example, if the
 * application sets N = 30 and issues "frame drop" command with 2 frames, the
 * total frames in this GOP will be still 30 frames. The two dropped frames are
 * discarded directly before encoding; this does not affect the encoding.
 *
 * When this feature works in conjunction with the frame factor, the frames that
 * encode several frames will be discarded; frames that were intended to be
 * discarded are not included.
 *
 * @subsection section_encode_frame_trigger 1.9 Encode Frame Trigger
 *
 * The encode frame trigger provides information on the number of frames that
 * will be encoded for the specified stream. The valid range is from 1~255.
 *
 * If the application sends "encode frame trigger" command, the DSP will encode
 * the upcoming frames into the bit stream. For example, if the application issues
 * "frame trigger" command with 2 frames, the encoder will encode 2 frames. In addition, if
 * the application issues "frame trigger" command with frame-trigger-repeat option
 * and 3 frames, the encoder will encode 3 frames every time after drop one frame.
 *
 * The application can use manual-arm-pts option. With this option, users can get
 * continuous Arm presentation time stamp (PTS) even DSP skip to encode some frames.
 *
 * @subsection section_canvas_stream_sync 1.10 Canvas and Stream Sync
 *
 * There may be two types of synchronization requirements between canvases and streams:
 *      - Locate a specific canvas with the PTS, perform motion analysis or object
 * detection on the frame YUV or ME data, and apply encode parameters accordingly.
 *      - Apply the IDSP and encode parameters to the same frame, not necessarily
 * to a predefined frame with the PTS.
 *
 * For the first one, it is required to implement the frame FIFO to cache several
 * frames, in order to allow applications to have enough time to do analysis and
 * apply the encode parameters. There are two places to implement this FIFO: FIFO
 * between canvas output and encoder, as well as the FIFO inside encoder. Both
 * need to allocate more YUV / ME buffers, and thus requires more DSP DRAM size.
 *
 * For the second one, FIFO is not needed, due to no requirement to specific frame.
 * In this case, no extra DRAM size is required.
 *
 * @subsubsection subsection_encode_dummy_latency 1.10.1 Encode Dummy Latency
 *
 * In order to configure encode parameters or apply overlay / blur effect on the
 * exact frame, IAV driver provides a method called "encode dummy latency" or
 * "frame sync mechanism".
 *
 * This method allows DSP to allocate more frame buffers in the FIFO between
 * the canvas ouput and other modules (such as encoder or VOUT). These new allocated
 * buffers are used to cache frames, so that application has enough time to
 * calculate the encode parameters and configure them on the exact frame.
 * This method helps the application to perform a frame accurate encode control.
 * PTS is used to synchronized between canvas output and other modules, to achieve
 * the frame accurate operations.
 *
 * For CV5x, there are only one way for "encode dummy latency", and the latency is per
 * canvas. The canvas based latency has a good granuarity, by specifying the latency
 * only for the specified canvas, thus only allocating frame buffers for this canvas.
 *
 * When the latency is added between canvas output and encoder input, the encoder
 * will delay n frames to fetch and apply overlay / blur and encode the YUV data when
 * the command is sent to the DSP. The range of n is 0~8, where 0 means no delay.
 *
 * One of the typical use case is to use CVflow® hardware (HW) to perform convolutional neural network (CNN) object detection
 * (people / face / licence plate / objects) on the canvas or pyramid frames, and
 * apply frame accurate results to the encoded stream (including overlay / blur effects and the
 * frame / region of interest (ROI) level encode parameters). The detected results can be drawn on the
 * frame with bonding boxes (overlay) and applied with blur effect (people / face).
 * The detected objects can also apply different ROI encode parameters, to
 * improve the video quality for these specific areas.
 * Check @ref codec_ssync "21. Frame Sync" for usage.
 *
 * @image html enc_dummy_latency.png "Figure 1-3. Encode Dummy Latency."
 *
 * @subsubsection subsection_stream_dummy_latency 1.10.2 Stream Dummy Latency
 *
 * Besides "encode dummy latency", IAV driver provides another way to do
 * synchronization between canvas output and encoder, called "stream dummy latency".
 *
 * Different from "encode dummy latency", "stream dummy latency" adds the latency
 * inside the encoder, which is right before compressor / decompressor (codec) (perform advanced video coding (AVC) / high efficiency video coding (HEVC) / MJPEG encoding)
 * and after overlay / blur / rotate / flip operations. This method enables DSP to report
 * pre-encoding frame data to Arm, and cache several frames to allow the application
 * to do motion analysis and object detecion, and finally apply frame accurate encode
 * parameters to the specified frame.
 *
 * The latency is a per stream parameter, with the range of 0~4, where 0 means no delay.
 * DSP reports the pre-encoded YUV / ME data for Arm to do analysis. Arm needs to apply
 * the frame accurate encode parameters to DSP with the specified latency, using PTS
 * to perform synchronization.
 *
 * This method is user-friendly for the encoder control. The reported pre-encoded
 * YUV / ME has the same FoV as the encoder. The frame rate is also the same as encoder.
 * With "encode dummy latency", the YUV / ME FoV is the full canvas FoV, and the frame
 * rate is full canvas frame rate, which may be different from the encoded stream.
 *
 * The typical use case for "stream dummy latency" is the SmartRC library. It will use
 * the ME data before codec to do motion analysis, and apply frame level and ROI level
 * encode parameters according to the analysis results.
 * Check @ref codec_ssync "23. Stream Sync" for usage.
 *
 * @image html stream_dummy_latency.png "Figure 1-4. Stream Dummy Latency."
 *
 * @subsubsection subsection_latency_comparison 1.10.3 Comparison for Encode/Stream Dummy Latency
 *
 * <table>
 * <caption id="encode_stream_dummy_latency_comparison"></caption>
 * <tr><th> Description <th><B>Encode Dummy Latency</B></div> <th>Stream Dummy Latency
 * <tr><td> FIFO for the buffers
 *		<td> Yes, added between Canvas output and VDSP input
 *		<td> Yes, added inside VDSP, before coded and after overlay / blur / rotate / flip
 * <tr><td> Buffer FoV
 *		<td> The FoV / size is the same as original canvas FoV / size.
 *		<td> The FoV / size is the same as the stream FoV / size, may be cropped / rotated / flipped
 * <tr><td> Overlay/Blur
 *		<td> May not have overlay or blur
 *		<td> With overlay / blur
 * <tr><td> Reported buffer frame rate
 *		<td> The frame rate is the same as the canvas frame rate
 *		<td> The frame rate is the same as the stream frame rate
 * <tr><td> Use scope
 *		<td> Between IDSP and encoder / video output (VOUT) / vector processor (VP).
 *		<td> Mainly for smart rate control, due to encoder friendly
 * </table>
 *
 * @subsubsection subsection_idsp_encode_sync 1.10.4 IDSP Encoder Sync
 *
 * For IDSP Encoder sync mechanism, the target is to apply the IDSP / Encoder operations to
 * the same frame. However, it is not required to apply the operations to the specific
 * frame with the PTS.
 *
 * This is implemented by binding the IDSP / Encoder operations to the same CMD block to DSP.
 * So user applications need to configure IDSP and Encoder operations first, and apply the
 * operations at the same time. IAV would pass the opertions in the same CMD block to DSP.
 * DSP would process and apply them in the same frame time. It will apply to the frame
 * when DSP receives and processes the IDSP operation. So the encoder operation is also
 * applied to this frame. Therefore, this achieves the effect of applying the IDSP / Encoder
 * operations to the same frame.
 *
 * The typical use case for "IDSP / Encoder Sync" is the magic zoom feature. For example, users
 * can apply DPTZ to perform zoom operation to the canvas at IDSP stage, configure the encode
 * offset at Encoder stage, and apply these operations the same frame.
 * Check @ref @ref idsp_enc_fsync "22. Frame Sync between iDSP and Encoder" for usage.
 *
 * @image html idsp_encoder_sync.png "Figure 1-5. IDSP / Encoder Sync."
 *
 * @subsection section_monochrome 1.11 Monochrome
 *
 * In order to encode monochrome streams with AVC / HEVC / MJPEG, the IAV driver
 * provides a new parameter named the "--chrome" format for the application
 * to configure.
 *
 * This parameter enables the DSP to generate monochrome streams
 * and enables the application to change it dynamically.
 *
 * @subsection section_strict_cbr 1.12 Strict Constant Bit Rate
 *
 * In order to configure more strict constant bit rate behavior on the streams,
 * IAV driver provides a new option named "--cbr-stable-br-enable [0|1]" to
 * support this feature. With this option enabled, the DSP will encode the bit
 * stream with smaller bit rate fluctuation.
 *
 * @subsection section_multiple_sltile_enc 1.13 Multiple Tile Encoding
 *
 * For HEVC, it supports multiple-tile encoding.
 * The encoder can divide the frame into 5 tiles at most.
 * These tiles can be encoded in parallel by the hardware. It can increase the encoding
 * performance. However, not all the cases can be divided to 5 tiles, there are some limitations
 * from HEVC standard. The width of each tile should be greater than 256, which means for the cases
 * such as 640x360, the maximum number of tile is 2, otherwise the stream cannot be decoded
 * successfully. In addition, the IAV driver will update the tile number according to the
 * encoding width automatically in `iav_dsp_cmd.c`.  <b> Please note, for mass production, it is not
 * suggested to change the tile number manually. </b>
 *
 * @image html multiple_tile_number_5.png "Figure 1-6. Set Tile Number 5."
 *
 * Bits-info of structure iav_framedesc is used to describe the information about tile.
 * There is tile_id in the structure iav_framedesc. Customers can
 * fetch the tile information by calling IAV_DESC_FRAME.
 *
 * @subsection subsection_encoder_dual_cores 1.14 Encoder Dual Cores
 * CV5x has two VDSP cores and four modes to make use of these two cores.
 *
 * <ul>
 *	  <li> Single core 0: Use VDSP core 0 only.
 *	  <li> Single core 1: Use VDSP core 1 only.
 *	  <li> Dual core temporal: Use VDSP dual cores. To use this mode, streams have to be
 *         configured as 2 layers SVC-T, then stream layer 0 and layer 1 are encoded simultaneously
 *         on two cores. Only H.264 and H.265 streams support this mode.
 *	  <li> Dual core spatial: Use VDSP dual cores. When using this mode, a VDSP input frame
 *         is splited into two halves side by side, then these two halves are encoded simultaneously
 *         on two cores. Only H.265 streams support this mode at the moment.
 *         In dual core spatial mode, multi-slices / tiles encoding will take effect on each
 *         half. For example, setting 3 tiles means that both the left and right halves are
 *         divided into 3 tiles, which is equal to divide one frame into 6 tiles.
 * </ul>
 *
 * The encoder core mode is a per stream configuration, which means it is possible to encode several
 * streams at the same time using different encoder core modes.<br>
 * The VDSP can achieve the best performance only when the work is evenly assigned to two cores.
 * DSP will ensure load balancing between the two cores in dual core temporal and dual core spatial
 * mode. Then it's up to users to assign loadings when streams are configured using a single core.<br>
 * IAV default configures dual core temporal for H.26x streams and single core 0 for MJPEG streams.
 *
 * @note
 * - It is not supported to configure all streams on VDSP core 1.
 * - For CV72, there is only one VDSP core.
 *
 * @subsection section_pjpeg_tile_size 1.15 Encode PJPEG Tile DRAM Size
 * PJPEG tile DRAM buffers are specially used by DSP to store the intermediate process data of video encoding flow.
 * For CV chip (like CV5 & CV3) which have dual VDSP cores, core 0 and core 1 each have
 * their own PJPEG tile DRAM buffer with the following layout, total of 10 buffers are allocated.
 *
 * @image html pjpeg_size.png "Figure 1-7. Encode PJPEG DRAM Layout."
 *
 * Tile 0 can be used for AVC / HEVC, tile 1 can be used for AVC / HEVC / MJPEG, and tile 2/3/4 are only used for HEVC.
 * Each buffer can be allocated up to 16 MB, so the PJPEG tile size can be up to 160 MB in total.
 * However, in practical scenarios, according to the used resolution and coding quality,
 * the appropriate buffer size can be dynamically allocated to save the DRAM usage of DSP.
 *
 * Ambarella has optimized the default PJPEG DRAM size for AVC and HEVC to ensure the best
 * balance between average coding quality and DRAM usage.
 * However, if users see the following artifacts from high-quality or larger resolution
 * MJPEG encoding (such as 4Kp JPEG with high quality, or 8Kp JPEG), it means the PJPEG buffer
 * is insufficient for this case. Users need to increase the PJPEG tile for MJPEG accordingly.
 *
 * @image html artifacts_due_low_pjpeg_tile.png "Figure 1-8. Artifacts Due to Low PJPEG Size."
 *
 * The following three debug options are also provided to set the corresponding
 * PJPEG tile DRAM size to meet the higher DRAM requirements.
 * <table>
 * <caption id="table_stream_lua"></caption>
 * <tr><th> Option <th><div style="width:150px"><B>Range(MB)</B></div> <th>Description
 * <tr><td> avc_pjpeg_size_MB_per_tile
 *	<td> [0~16]
 *	<td> Specifies the tile 0/1 PJPEG tile DRAM size for both core 0/1
 * <tr><td> mjpeg_pjpeg_size_MB_per_tile
 *	<td> [0~16]
 *	<td> Specifies the tile 1 PJPEG tile DRAM size for both core 0/1
 * <tr><td> hevc_pjpeg_size_MB_per_tile
 *	<td> [0~16]
 *	<td> Specifies the tile 2/3/4 PJPEG tile DRAM size for both core 0/1
 * </table>
 *
 * @note
 * - Tile 0 is shared by AVC / HEVC, so the final DRAM size of tile 0 will be the
 *   maximum between avc_pjpeg_size_MB_per_tile and hevc_pjpeg_size_MB_per_tile.
 * - Tile 1 is shared by AVC / HEVC / MJPEG, so the final tile 1 DRAM size will
 *   be the maximum between avc_pjpeg_size_MB_per_tile,
 *   hevc_pjpeg_size_MB_per_tile, and mjpeg_pjpeg_size_MB_per_tile.
 *
 * If users want to use high quailty MJPEG encoding, Ambarella recommends setting the tile 1 size
 * to 16 MB when the maximum resolution is above 4K, 12 MB or above for 5M resolution, and 6 MB
 * or above for 1080p resolution. Here is an example.
 *
 * @code {.c}
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 // For CV5/CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8) // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/local/bin/scripts/cv5_vin0_4k_linear.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua --mjpeg-pjpeg-tile-size 16 // For CV5/CV52
 * (Or board# test_encode --resource-cfg /usr/local/bin/scripts/cv72_vin0_4k_linear.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua --mjpeg-pjpeg-tile-size 16) // For CV72
 * board# test_encode -A -m 3840x2160 --quality 90 -e
 * @endcode
 *
 * @subsection subsection_custom_sei 1.16 Insert User-Customized Data into Bitstream
 *
 * This feature is used for users to insert their own customized data into the bitstream, such as DPTZ information,
 * additional information of the interested objects in the stream scene, and more. The data format and size can be
 * freely defined by users. AVC, HEVC, and MJPEG all can support this feature. For AVC / HEVC bitstream,
 * the customized data is inserted in the form of supplement enhancement information (SEI) data in <b>SEI (users data unregistered) NALU</b>. For MJPEG
 * bitstreams, the customized data is inserted directly into the user's customized field marked as <b>APP0</b>.
 *
 * User need to pre-allocate custom sei memory resources of the stream. Please configure the following parameters:
 * @code
 * stream_0 = {
 *   id = 0,
 *   ...
 *   custom_sei_possible = 1,  // The flag to alloc custom sei buffer memroy for the current stream.
 *   custom_sei_buf_num = 8,  // The custom sei buffer number of custom sei buffer pool for current stream, it determines the queue depth of pts frame sync.
 *   custom_sei_data_max_size = 1024,  // The maximum data size for custom sei, which is used for allocating memory in DSP and iav driver.
 *   ...
 *}
 * @endcode
 * Note that the byte order of the data stored in bitstream is in Big-Endian.
 * For example, if the inserted data (from Byte0 to ByteN) is "0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, ...",
 * its byte-order in the bitstream will be "0x33, 0x22, 0x11, 0x00, 0x77, 0x66, 0x55, 0x44, ...".
 * <table>
 * <caption>Byte-Order of User Customized Data in Bitstream</caption>
 * <tr><th>Byte3<th>Byte2<th>Byte1<th>Byte0<th>Byte3<th>Byte2<th>Byte1<th>Byte0<th>...
 * <tr><td>0x33<td>0x22<td>0x11<td>0x00<td>0x77<td>0x66<td>0x55<td>0x44<td>...
 * </table>
 *
 * @note
 * - "test_custom_sei" is a sample application that demonstrates how to insert users-customized data.
 * In real use cases, users can insert their own customized data in any format and size.
 * - Repeat custom sei data only support no pts sync, random sei data size only support pts sync.
 * - For fixed payload size case, "--custom-sei-data-size" is the real sei payload size in the bitstreams, it can't larger than "custom_sei_data_max_size".
 * In order to provide enough redundant bits space for RBSP preventive byte stuffing process. When user insert the custom sei data,
 * the real data size can't exceed 3/4 of the "custom-sei-data-size", which is 3/4 of the payload size.
 * - For dynamic custom sei data size case, the sei payload size will be adjusted based on the actual data size and
 * the number of preventive byte stuffing (0x03) that need to be inserted into the data.
 * We also need to make sure that the actual data size is not larger than 3/4 of "custom_sei_data_max_size".
 * - Support inserting custom SEI data for I-frame only.
 *
 * @par Insert User-Customized SEI Data into AVC / HEVC / MJPEG Bitstreams
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3	 // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)		 // For CV72
 * board# test_aaa_service -a &
 * board# test_encode -i 1080p --hdmi 1080p
 * board# test_encode --resource-cfg cv5_vin0_1080p_linear_custom_sei.lua  --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * board# rtsp_server --streaming-sei &
 *
 * example 1: Fixed payload size with pts sync:
 * board# test_encode -A -b0 -h/-H/-m 1080p --custom-sei-data-size 256 -e // The user specifies the payload size (256) in all next frames
 * board# test_custom_sei -S 0 -p -d 12x34		 // users customized SEI data(12, 34) is inserted in all next frames by frame sync
 *
 * example 2: Fixed payload size with no pts sync:
 * board# test_encode -A -b0 -h/-H/-m 1080p --custom-sei-data-size 256 -e // The user specifies the payload size (256) in all next frames
 * board# test_custom_sei -S 0 -d 12x34		 // users customized SEI data(12, 34) is inserted in all next frames by no frame sync
 *
 * example 3: Fixed payload size repeat sei data:
 * board# test_encode -A -b0 -h/-H/-m 1080p --custom-sei-data-size 256 -e // The user specifies the payload size (256) in all next frames
 * board# test_custom_sei -S 0 -d 12x34 -r		 // users customized SEI data(12, 34) is inserted repeatedly in all next frames
 *
 * example 4: Dynamic payload size with pts sync:
 * board# test_encode -A -b0 -h/-H/-m 1080p --custom-sei-dynamic-size-enable 1 -e // The user enable the dynamic payload size
 * board# test_custom_sei -S 0 -p -d 1920x1080	 // users customized SEI data(12, 34) is inserted in all next frames by frame sync
 *
 * example 5: Dynamic payload size with random data size::
 * board# test_encode -A -b0 -h/-H/-m 1080p --custom-sei-dynamic-size-enable 1 -e // The user enable the dynamic payload size
 * board# test_custom_sei -S 0 -p -R	// usres can use -R to test different sei data size for each frame.
 *
 * example 6: Insertion for I-frame only:
 * board# test_encode -A -b0 -h/-H 1080p --custom-sei-data-size 256 --custom-sei-I-only 1 -e
 * board# test_custom_sei -S 0 -d 12x34 -r	// users customized SEI data(12, 34) is inserted repeatedly in all next I frames
 * @endcode
 * <BR>
 *
 * ---
 *
 * @section section_stream_configuration 2. Stream Configuration
 * Users can configure the stream resource via Lua script. Here are the parameters for stream resource
 * @ref iav_stream_resource.
 *
 * <table>
 * <caption id="table_stream_lua"></caption>
 * <tr><th> Item <th><div style="width:150px"><B>Parameter</B></div> <th>Description
 * <tr><td> id
 *		<td> id >= 0
 *		<td> Specifies stream ID. It is suggested to keep the same value as
 *           stream index, and it starts from zero.
 * <tr><td> max_size
 *		<td> {width, height}
 *		<td> Specifies the maximum resolution of stream.
 * <tr><td> max_M
 *		<td>
 *		<td> Specifies maximum GOP M for stream. For B frame, max_M > 1.
 *           For MJPEG encoding, max_M = 0.
 * <tr><td> fast_seek_enable
 *		<td> 0: Disable<br>
 *		     1: Enable
 *		<td> Enables / disable fast seek frame.
 * <tr><td> two_ref_enable
 *		<td> 0: No SVC-T<br>
 *		     1: 2 layers SVC-T.
 *		<td> Enable / disable 2 forward reference frames.
 * <tr><td> max_svct_layers_minus_1
 *		<td>
 *		<td> Specifies maximum SVC-T layers options.
 * <tr><td> max_num_minus_1_ltrs
 *		<td>
 *		<td> Specifies maximum long term number minus 1.
 * <tr><td> @anchor anchor_codec_enable codec_enable
 *		<td> 0: HEVC / H264 /MJPEG <br>
 *		     1: HEVC / MJPEG <br>
 *		     2: H264 /M JPEG <br>
 *		     3: MJPEG only
 *		<td> Enables / disable stream codec.
 * <tr><td> efm_enable
 *		<td> 0: Disable <br>
 *		     1: Enable
 *		<td> Enables / disable to do encode from memory (EFM) for current stream.
 * <tr><td> efm_buf_num
 *		<td>
 *		<td> Specifies the number of frame buffers allocated for EFM.
 *           These frame buffers are allocated by DSP and occupies extra DSP memory.
 * <tr><td> efm_size
 *		<td> {width, height}
 *		<td> Specifies the resolution of EFM frame buffer.
 * <tr><td> efm_skip_waiting
 *		<td> 0: Disable<br>
 *		     1: Enable
 *		<td> Enables skipping waiting for DSP's response when starting / stopping EFM streams.
 * <tr><td> efm_extern_src_enable
 *		<td>
 *		<td> Enables sharing EFM buffer from other streams.
 * <tr><td> efm_extern_src_stream
 *		<td>
 *		<td> Specifies the stream ID of shared EFM buffer for the current stream.
 * <tr><td> possible_enc_src_map
 *		<td>
 *		<td> Specifies the possible encoding source canvas map for a stream, which can
 *           deploy DSP encoding resource in a more saving way.
 * <tr><td> stream_mv_statis_enable
 *		<td> 0: Disable<br>
 *		     1: Enable
 *		<td> Enables motion vector (MV) dump for stream.
 * <tr><td> stream_pic_statis_enable
 *		<td> 0: Disable<br>
 *		     1: Enable
 *		<td> Enables picture statistic dump for stream.
 * <tr><td> enc_core_cfg_enable
 *		<td> 0: Disable<br>
 *		     1: Enable
 *		<td> Enables VDSP core mode configuration.
 * <tr><td> enc_core_mode
 *		<td> 0: Single VDSP core 0<br>
 *		     1: Single VDSP core 1<br>
 *		     2: VDSP dual core temporal<br>
 *		     3: VDSP dual core spatial
 *		<td> Specifies the VDSP core mode.
 * </table>
 *
 * <B>An Example for Stream Lua Configuration</B>
 *
 * @code
 * stream_0 = {
 *	  id = 0,
 *	  max_size = {1920, 1080},
 *	  max_M = 1,
 *	  fast_seek_enable = 0,
 *	  two_ref_enable = 0,
 *	  max_svct_layers_minus_1 = 0,
 *	  max_num_minus_1_ltrs = 0,
 *	  possible_enc_src_map = 0,
 *	  codec_enable = 0, 			-- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
 *	  efm_enable = 0,
 *	  efm_buf_num = 0,
 *	  efm_size = {0, 0},
 *	  efm_skip_waiting = 0,
 *	  efm_extern_src_enable = 0,
 *	  efm_extern_src_stream = 0,
 *	  stream_mv_statis_enable = 0,
 *	  stream_pic_statis_enable = 0,
 *	  enc_core_cfg_enable = 0,
 *	  enc_core_mode = 0, 			--0: core0; 1:core1; 2:dual core temporal; 3:dual core spatial
 * }
 * @endcode
 *
 * <br>
 *
 * ---
 *
 * @section section_stream_example 3. Stream Examples
 *
 * @subsection example_get_bit_stream Example 1: Get Bitstream
 *
 * @par Hardware and Software Environment
 *
 * Insert an secure digital memory (SD) card to the SD slot on the board.
 *
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start 3A statistic if the following command was not executed previously.
 * Then, put the IAV driver into "preview" state.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 * @par Record a Stream to the Board
 *
 * Users can record the stream with the unit test tool <em>test_stream</em>.
 * Start test_stream with "-f" option. Then it will query the IAV driver if
 * there is any update for all streams. It will block in the console until
 * there is any stream in encoding state.
 *
 * @code {.c}
 * board# test_stream -f /tmp/test (in console 2)
 * board# test_encode -A -h 1080p -b 0 -e
 * @endcode
 *
 * Wait for a period of time. Then, stop encoding stream A.
 *
 * @code {.c}
 * board# test_encode -A -s
 * @endcode
 *
 * The stream is recorded in the folder `/tmp` with the prefix "test_A".
 *
 * @par Record Streams to the SD card
 *
 * The sdcard is mounted on the "/sdcard" directory by default. Users can
 * record the stream with the unit test tool <em>test_stream</em>.
 *
 * @code {.c}
 * board# test_stream -f /sdcard/test (in console 2)
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h  480p -b 1 -e
 * @endcode
 *
 * Wait for a period of time. Then, stop encoding stream A and stream B.
 *
 * @code {.c}
 * board# test_encode -A -s -B -s
 * @endcode
 *
 * The streams are recorded in the folder `/tmp/mmcblk0p1` with the
 * prefix <em>"test_A"</em> and <em>"test_B"</em>.  Users can view the bit
 * stream via VLC Player.
 *
 * @par Get Bitstream Statistic without Saving Files
 *
 * Sometimes it is very helpful to start the test_stream without saving files.
 * Because test_stream will print a lot of debug information.
 *
 * First, ensure that none process of <em>test_stream</em> is running. Also,
 * do not enable the RTSP server. Then start test_stream with option "--nofile".
 *
 * @code {.c}
 * board# test_stream --nofile (in console 2)
 * board# test_encode -A -h 1080p -e -B -h 480p -e
 * board# test_encode -A -s -B -s
 * @endcode
 *
 * The debug information will be printed in console 2.
 *
 *
 *
 * @subsection example_encoding_control Example 2: Encoding Control
 *
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start 3A statistic if the following command was not executed previously.
 * Then, put the IAV driver into "preview" state.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * @endcode
 *
 * @par Start / Stop Stream Synchronously
 *
 * @code {.c}
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h 480p  -b 1 -e
 * board# test_encode -A -s -B -s
 * @endcode
 *
 *
 * @par Start / Stop Stream Independently
 *
 * Configure stream A & stream B with the following command.
 *
 * @code {.c}
 * board# test_encode -A -h 1080p -b 0\
 *                    -B -h  480p -b 1
 * @endcode
 *
 * Start and stop these two streams independently.
 *
 * @code {.c}
 * board# test_encode -A -e
 * board# test_encode -B -e
 * board# test_encode -B -s
 * board# test_encode -A -s
 * @endcode
 *
 * @par codec Enable
 *
 * If some codec modules are turned off, it will save system resources. See
 * @ref anchor_codec_enable "Codec Enable in Lua".
 *
 * @code {.c}
 * board# test_encode -A --codec-enable 1
 * board# test_encode -A -h 1080p -e
 * 1080p resolution is 1920x1080
 * [  102.185427] check_encode_stream_type(642): Encode type cannot be set as H.264. Change 'codec enable' flag in the system resource!
 * [  102.198275] check_encode_stream_state(677): Invalid encode type for stream A.
 * board# test_encode -A -H 1080p -e
 * @endcode
 *
 * @par Turn Off HEVC Hardware
 *
 * Users can turn off the HEVC hardware to reduce power consumption.
 * The following example turn off the HEVC hardware, then start an AVC stream.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\        // For CV5 or CV52
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize 480p\
 *                    -J --btype enc --bsize 720p --bmaxsize 720p
 *                    --hevc-off 1
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\   // For CV72
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize 480p\
 *                    -J --btype enc --bsize 720p --bmaxsize 720p)
 *                    --hevc-off 1
 * board# test_encode -A -h 1080p -b 0 -e
 * @endcode
 *
 *
 * @subsection example_choose_source_canvas Example 3: Encode from Specified Single Canvas
 *
 * Choose the canvas 0 that contains main buffer for stream A 1080p, the canvas 2
 * that contains the third buffer for stream B 720p, and the canvas 1 that contains
 * the second buffer for stream C.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\        // For CV5 or CV52
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize 480p\
 *                    -J --btype enc --bsize 720p --bmaxsize 720p
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua\   // For CV72
 *                    -X --bsize 1080p --bmaxsize 1080p\
 *                    -Y --bsize 480p\
 *                    -J --btype enc --bsize 720p --bmaxsize 720p)
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h  720p -b 3 -e\
 *                    -C -h  480p -b 1 -e
 * @endcode
 *
 * @subsection example_stream_resolution Example 4: Setting up Maximum Resolution
 *
 * Users can set the maximum resolution for each stream via option "--smaxsize".
 * In this example, the maximum resolutions for stream A, stream B, and stream C
 * are 1080p, 720p, and 480p.
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A --smaxsize 1080p\
 *                    -B --smaxsize 720p\
 *                    -C --smaxsize 480p
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h  720p -b 3 -e\
 *                    -C -h  480p -b 1 -e
 * @endcode
 *
 *
 * @subsection example_crop_from_canvas Example 5: Cropping from Source Canvas
 *
 * In this example, stream A, stream B, and stream C are encoded from canvas 0.
 * The size of canvas 0 is 1920x1080. To enable encoding 3 streams from the
 * same canvas, 2 extra buffers are needed for canvas 0.
 *
 * Modify the lua file for 2 extra buffers for canvas 0.
 *
 * @code {.c}
 * canvas = {
 *    {
 *        type = "encode",
 *        size = {0, 0}, -- min size to contain source buffers
 *        source = {"chan_0.main",},
 *        extra_dram_buf = 2,
 *    },
 *    ......
 * }
 * @endcode
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -b 0 --offset 0x0 -e\
 *                    -B -h  480p -b 0 --offset 100x480 -e\
 *                    -C -h  480p -b 0 --offset 720x300 -e
 * @endcode
 *
 * Stream A is encoded with the same size FoV as canvas 0. Stream B and steam C
 * are cropped from the cavas 0. Field of view for the 3 streams are as follows.
 *
 * @image html example_stream_crop.png Figure 3-1. Stream Cropping from Canvas.
 *
 * @subsection example_stream_frame_rate Example 6: Set Encoding Frame Rate
 *
 * Set up the system resouce limitation on the EVK board first. And then enter
 * "Preview" state. In this example, the input framerate is set to 60.
 *
 * Modify the lua file for 1080p60 mode.
 *
 * @code {.c}
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 60,
 *    max_fps = 0,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 * @endcode
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * Then start encode stream A and stream B. By default, the frame rate of a
 * stream is the same as the input frame rate. In this emample, frame rate
 * of stream A and stream B are 60.
 *
 * @code {.c}
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h  480p -b 1 -e
 * @endcode
 *
 * Users can see the actual frame rate with <em>test_stream</em>. Open another
 * console. And then, start the process test_stream to do stream statistic
 * without saving files.
 *
 * @code {.c}
 * board# test_stream --nofile
 * ...
 * stream A:   2100 frames, 60.00 fps,   35676951   bytes,  7782 kbps, enc_pipe_time [ 2474: 2653]
 * stream B:   1530 frames, 60.00 fps,   12935030   bytes,  3922 kbps, enc_pipe_time [ 2534: 2836]
 * stream A:   2130 frames, 60.00 fps,   36204046   bytes,  8236 kbps, enc_pipe_time [ 2474: 2653]
 * stream B:   1560 frames, 60.00 fps,   13182262   bytes,  3863 kbps, enc_pipe_time [ 2534: 2836]
 * ...
 * @endcode
 *
 * Adjust the frame rate of stream A and stream B on the fly.
 *
 * @code {.c}
 * board# test_encode -A --frame-factor 45/60 -B --frame-factor 30/60
 * @endcode
 *
 * The frame rate of stream A will be adjusted to 45. The frame rate of stream B will be adjusted
 * to 30. For more details, see the output information of the process test_stream.
 *
 * @code {.c}
 * board# test_stream --nofile
 * ...
 * stream A:   180 frames, 45.89 fps,   2994167   bytes,  6897 kbps, enc_pipe_time [ 2474: 2613]
 * stream B:   120 frames, 30.80 fps,   1028681   bytes,  3307 kbps, enc_pipe_time [ 2536: 2670]
 * stream A:   210 frames, 45.01 fps,   3464028   bytes,  5507 kbps, enc_pipe_time [ 2474: 2613]
 * stream B:   150 frames, 30.00 fps,   1247731   bytes,  1711 kbps, enc_pipe_time [ 2536: 2670]
 * ...
 * @endcode
 *
 * By default, the frame rate will be changed immediately after rising the framerate
 * adjusting command. However, users can apply the new frame rate until
 * the next GOP if the option "--fps-update-mode" is set to 1.
 *
 * @code {.c}
 * board# test_encode -A --frame-factor 30/60 --fps-update-mode 1
 * @endcode
 *
 *
 * @subsection example_encode_duration Example 7: Set Encoding Duration
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -b 0 -d 150 -e\
 *                    -B -m  480p -b 1 -d 120 -e
 * @endcode
 *
 * @subsection example_stream_monochrome Example 8: Monochrome Stream
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H 1080p --chrome 1 -e
 * board# test_encode -A --chrome 0
 * @endcode
 *
 * @image html stream_monochrome.png "Figure 3-2. Monochrome Stream: a) Origin Stream b) Monochrome."
 *
 * @subsection example_frame_drop Example 9: Frame Drop
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H 1080p -e
 * board# test_encode -A --frame-drop-repeat 1 --frame-drop 1
 * @endcode
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H 1080p -e
 * board# test_encode -A --frame-drop-repeat 0 --frame-drop 10
 * board# sleep 10
 * board# test_encode -A --frame-drop-repeat 0 --frame-drop 4
 * @endcode
 *
 * @subsection example_frame_trigger Example 10: Frame Trigger
 *
 * Enable the frame trigger. Then set DSP to encode one frame every time
 * after drop one frame.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
  * @endcode
 *
 * Modification of cv5_vin0_1080p_linear.lua or cv72_vin0_1080p_linear.lua file for Canvas 0 dummy latency:
 * @code {.c}
 * canvas = {
 *        {
 *            ...
 *            enc_dummy_latency = 4,
 *            ...
 *        },
 *        ...
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -b 0 -h 1080p --trigger-frame 1 -e
 * board# test_frame_sync -A --frame-trigger 1 --frame-trigger-repeat 1
 * @endcode
 *
 * Enable the frame trigger. Set DSP to encode 10 frames, then set DSP to encode
 * 4 frames after sleeping 10 seconds.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
  * @endcode
 *
 * Modification of cv5_vin0_1080p_linear.lua file for Canvas 0 dummy latency:
 * @code {.c}
 * canvas = {
 *        {
 *            ...
 *            enc_dummy_latency = 4,
 *            ...
 *        },
 *        ...
 * @endcode
 *
 * @code {.c}
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -b 0 -h 1080p --trigger-frame 1 -e
 * board# test_frame_sync -A --frame-trigger 10 --frame-trigger-repeat 0
 * board# sleep 10
 * board# test_frame_sync -A --frame-trigger 4 --frame-trigger-repeat 0
 * @endcode
 *
 * Enable the frame trigger without the frame sync.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -b 0 -h 1080p --trigger-frame 1 -e
 * board# test_encode -A --trigger-frame-num 10
 * @endcode
 *
 * @subsection example_strict_cbr Example 11: Strict Constant Bit Rate
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H 1080p -e
 * board# test_encode -A --bc cbr --bitrate 4000000 --cbr-stable-br-adjust 1
 * @endcode
 *
 * @subsection example_stream_session_id Example 12: Configure Stream Session ID
 *
 * Session ID is used to identify a stream session. Even though there is stream ID, a single stream might
 * be started / stopped repeatedly at runtime. Each time it is restarted, it might be taken as a new session.
 * When stream settings are the same between two successive sessions, it is hard for users to distinguish the
 * bitstream between them, resulting in confusion. Specifying a different session ID when the stream is
 * restarted can properly address this problem.
 *
 * @note
 * Users can specify their own session ID. If it is specified to 0, IAV will generate a random and unique
 * session ID for it automatically.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p --session-id 1234 -e
 * @endcode
 *
 *
 * @subsection example_show_stream_info Example 13: Display System Information
 *
 * @par Show Stream Information
 *
 * Configuration of the stream can be printed to console with option
 * "--show-stream-info". See the following example.
 *
 * @code {.c}
 * board# test_encode -A -h 1080p -e
 * board# test_encode --show-stream-info
 *	[Encode stream info]:
 *	Stream A
 *			    Format : H.264
 *			     State : encoding
 *		     Canvas source : 0
 *			  Duration : 0
 *			Resolution : (1920x1080)
 *		     Encode offset : (0,0)
 *			    H-Flip : Disabled
 *			    V-Flip : Disabled
 *			    Rotate : Disabled
 *			Session id : 1234
 *		      Fake AVG PTS : Disabled
 *			 FPS ratio : 1/1
 *		    ABS FPS enable : Disabled
 *			   Abs FPS : 30
 *			FPS Update : Current GOP
 * @endcode
 *
 * @par Display Resource Information
 *
 * @code {.c}
 * board# test_encode --show-resource-info
 *
 *	[System information]:
 *	      Encode mode : [Advanced ISO]
 *	Channel vcap mode : [Disabled]
 *
 *	[Codec resource limit info]:
 *	  max number of encode streams : 1
 *	  Stream A Max : [1920x1088], M [1].
 *	  Stream A fast_seek : Disabled.
 *	  Stream A two ref : Disabled.
 *	  Stream A max svct layers minus 1 : 1.
 *	  Stream A max num ltrs minus 1 : 0.
 *	  Stream A possible enc src map : 0x0.
 *	  Stream A codec enable : HEVC / H264 / MJPEG
 *
 *	  Stream A mv statis : 0.
 *	  Stream A pic statis : 0.
 *
 *		   Channel-Num : 1
 *		     Sharpen-B : Disabled
 *		       Mixer-A : Disabled
 *		       Mixer-B : Enabled
 *		   RAW capture : Disabled
 *	vsync loss dummy frame : Disabled
 *		     ME0 scale : 1/8 X
 *		    HEVC STATE : Enabled
 *	  Vsync loss detection : Disabled
 * @endcode
 *
 * @subsection example_show_encoded_order Example 14: Encoded Frame Order
 *
 * When enabling B frame encoding, the encoding frame sequence would be different from
 * the frame capture sequence.
 *
 * For user application to query the encoded frames, it is necessary to know whether
 * there are frame dropping behavior happened at Arm side. This can be achieved
 * by keeping checking the frame based encoding sequence number.
 *
 * For the example below, "frame_num" shows the frame capture (or display) order,
 * while "encoded_frame_num" shows the frame encoding order.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -M 3 -N 30 -e
 * board# test_stream -v
 * . . . .
 * type=4, is_skipped 0, size=1366, addr=0x1527808, strm_id=0, sesn_id=3207481868, frame_num=290, encoded_frame_num=292,
 * type=3, is_skipped 0, size=7201, addr=0x1529216, strm_id=0, sesn_id=3207481868, frame_num=294, encoded_frame_num=293,
 * type=4, is_skipped 0, size=1252, addr=0x1536512, strm_id=0, sesn_id=3207481868, frame_num=292, encoded_frame_num=294,
 * type=4, is_skipped 0, size=1599, addr=0x1537792, strm_id=0, sesn_id=3207481868, frame_num=293, encoded_frame_num=295,
 * type=3, is_skipped 0, size=7500, addr=0x1539456, strm_id=0, sesn_id=3207481868, frame_num=297, encoded_frame_num=296,
 * type=4, is_skipped 0, size=1544, addr=0x1547008, strm_id=0, sesn_id=3207481868, frame_num=295, encoded_frame_num=297,
 * type=4, is_skipped 0, size=1711, addr=0x1548672, strm_id=0, sesn_id=3207481868, frame_num=296, encoded_frame_num=298,
 * type=1, is_skipped 0, size=72233, addr=0x1550464, strm_id=0, sesn_id=3207481868, frame_num=300, encoded_frame_num=299,
 * type=4, is_skipped 0, size=2553, addr=0x1622784, strm_id=0, sesn_id=3207481868, frame_num=298, encoded_frame_num=300,
 * . . . .
 * @endcode
 *
 * @subsection example_hevc_width_padding Example 15: HEVC Width Padding
 *
 * The encoder can improve the performance of high efficiency video coding (HEVC) encoding
 * if the stream's width can be align to 128 or 160.
 *
 * Enable `hevc_width_align_enable` to make DSP available to do width padding that will
 * also align HEVC's buffer and stream width to the optimal size.
 *
 * Here is an example of how to enable this improvement.
 * Stream and canvas have the same option `hevc_width_align_enable = 1`, both should be enabled
 * for the width padding.
 *
 * @code
 *  ......
 *  stream_0 = {
 * 	 ......
 * 	 hevc_width_align_enable = 1,
 * 	 ......
 *  }
 *  _resource_config_ = {
 * 	......
 * 	canvas = {
 * 		{
 * 			 .....
 * 			 source = {"chan_0.main",},
 * 			 hevc_width_align_enable = 1,
 * 			 .....
 * 		},
 * 	}
 *  }
 * @endcode
 *
 * This improvement is evident with the HEVC streams that is 5M size such as 2592x1944.
 *
 */
/*!
 * @file codec.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_codec BASIC - H.264 / H.265 Codec
 *
 * @section codec_br 1. BitRate
 * This is the target bitrate and used as a reference for the encoder.
 * <b> Note that the bitrate set to the digital signal processor (DSP) may be different from the one set by IOCTRL.</b>
 * The image audio video (IAV) driver will change it according to the encoding frame
 * factor (fps_multi/fps_div) @ref iav_stream_fps when absolute bitrate flag is not
 * enabled. Besides that, the real bitrate of stream may not be as same as the one
 * set to DSP. The final bitrate depends on a lot of other factors, such as the complexity
 * of scene and so on. The DSP has no limitation for the maximum target bitrate, but in
 * IAV driver, there is a total system bitrate check, which is around 256 Mbps for all
 * streams. This is for the dynamic random access memory (DRAM) bandwidth consideration.
 * In addition, as the BSB buffer is used to save the data of all streams,
 * so it maybe needed to be increased to support larger bitrate cases, otherwise the data may be
 * overwritten.
 *
 * @subsection example_codec_br1 Example 1: Change Bitrate On the Fly
 * H.264 1080p 4Mbps -> 6Mbps -> 2Mbps
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_stream -t  #(Run PortServer/ps.exe on PC)
 * board# test_encode -A -h 1080p --bitrate 4000000 -e
 * board# test_encode -A --bitrate 6000000
 * board# test_encode -A --bitrate 2000000
 * @endcode
 *
 * @subsection example_codec_br2 Example 2: Set Target Bitrate Per Stream
 * H.264 1080p 8Mbps + H.264 480p 4Mbps
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_stream -t  #(Run PortServer/ps.exe on PC)
 * board# test_encode -A -h 1080p --bitrate 8000000 -e -B -h 480p -b 1 --bitrate 4000000 -e
 * @endcode
 *
 * @subsection example_codec_br3 Example 3: Display the Target Bitrate
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --bitrate 6000000 -e
 * board# test_encode --show-encode-config
 *
 * [Encode stream config]:
 *  Stream A
 *         H.264
 *                ...
 *                Average_bitrate = 6000000
 *                ...
 * @endcode
 *
 * @subsection example_codec_br4 Example 4: Bitrate changed according to encoding frame factor
 * Set encoding fps to be 1 fps by frame factor when video input (VIN) is 30 fps.  The bitrate set to DSP will
 * be <b> bitrate*(fps_multi/fps_div).</b>  For example, set the bitrate to be 6Mbps, and the
 * bitrate set to DSP will be 200K bps but not 6 Mbps in this example.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --bitrate 6000000 --frame-factor 1/30 -e
 * board# test_encode --show-encode-config
 *
 * [Encode stream config]:
 *  Stream A
 *         H.264
 *                ...
 *                Average_bitrate = 200000
 *                ...
 * @endcode
 *
 * @subsection example_codec_br5 Example 5: Keep bitrate not affected by encoding frame factor
 * However, the bitrate will not be changed even when the encoding frame factor is not 1, if the
 * absolute bitrate flag is enabled.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --bitrate 6000000 --frame-factor 1/30 --abs-br 1 -e
 * board# test_encode --show-encode-config
 *
 * [Encode stream config]:
 *  Stream A
 *         H.264
 *                ...
 *                Average_bitrate = 6000000
 *                ...
 * @endcode
 *
 * - - - -
 *
 * @section codec_gop 2. Group of Picture (GOP) Length
 * This tool is used to specify the interval of I frames.  Longer GOP means less I frame in one second.
 * Additionally, as the I frame always costs more bits, so longer GOP can decrease the real bitrate.  The value of
 * GOP is supposed to be small for the motion scenes and large for the static scenes.  The reason is that
 * the static scenes do not need too much I frames to refresh the video quality.
 *
 * There is some difference when changing the GOP length on the fly.
 * a) Switch to smaller GOP
 * @image html codec_decrease_gop_length.png "Figure 2-1. H.264 / H.265 Switch to Smaller GOP."
 * The new GOP will take effect immediately no matter force or no-force IDR when changing the GOP.
 * b) Switch to larger GOP
 * @image html codec_increase_gop_length.png "Figure 2-2. H.264 / H.265 Switch to Larger GOP."
 * It makes difference whether to do or not to do force-IDR when changing the GOP.  If do force-IDR when change
 * the GOP, the new GOP will take effect immediately.  However, if there is no force-IDR, the length of the
 * GOP which the current frame in will be extended to the new length.
 *
 *
 * @subsection example_codec_gop1 Example 6: Force IDR at Shorter GOP
 * H.264 1080p, GOP Length 60 -> 30 -> 15(Force IDR)
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p -N 60 -e
 * board# test_encode -A -N 30
 * board# test_encode -A -N 15 --force-idr 1
 * @endcode
 *
 * @subsection example_codec_gop2 Example 7: Force IDR at Longer GOP
 * H.264 1080p, GOP Length 15 -> 30 -> 60(force IDR)
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p -N 15 -e
 * board# test_encode -A -N 30
 * board# test_encode -A -N 60 --force-idr 1
 * @endcode
 *
 * @subsection example_codec_gop3 Example 8: Display Current GOP Length
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p -N 60 -e
 * board# test_encode --show-encode-config
 *
 * [Encode stream config]:
 *  Stream A
 *         H.264
 *                ...
 *                      N = 60
 *                ...
 * @endcode
 *
 * @subsection example_codec_gop4 Example 9: Update at Next GOP
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p -b 0 -N 20 -e
 * board# test_encode -A -N 3 --N-update-mode 1
 * @endcode
 * Difference from the above talking related to IDR, the above example shows the GOP can always be arranged to
 * take effect at next GOP.
 * @image html codec_update_at_next_gop.png "Figure 2-3. H.264 / H.265 Update at Next GOP."
 *
 * - - - -
 *
 * @section codec_idr 3. Instantaneous Decoder Refresh (IDR) Frequency
 * IDR belongs to I frames. Also the difference between I frame and IDR frame is that when the decode receives the IDR frame,
 * it discards all the reference frame queues and update the PPS and SPS structures, while the decoder only discard the reference
 * queues when it received the I frame.
 *
 * @subsection example_codec_idr1 Example 10: Set IDR Interval
 * H.264 1080p, all I Frames are IDR Frames.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --idr 1 -e
 * @endcode
 *
 * @subsection example_codec_idr2 Example 11: Set IDR Interval Per Stream
 * H.264 1080p, all I frames are IDR frames + H.264 480p, one IDR for each two I frames.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --idr 1 -e -B -h 1080p --idr 2 -e
 * @endcode
 *
 * @subsection example_codec_idr3 Example 12: Change IDR Interval On the Fly
 * H.264 1080p, one IDR for each I frames -> one IDR in every three I frames.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --idr 1 -e
 * board# test_encode -A --idr 3
 * @endcode
 *
 * @image html codec_IDR_interval.png "Figure 3-1. H.264 / H.265 IDR Interval."
 *
 * @subsection example_codec_idr4 Example 13: Display Current IDR Frequency
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --idr 3 -e
 * board# test_encode --show-encode-config
 *
 * [Encode stream config]:
 *  Stream A
 *         H.264
 *                ...
 *                idr interval = 3
 *                ...
 * @endcode
 *
 * - - - -
 *
 * @section codec_fidr 4. Force IDR
 *
 * Force IDR is used to generate an IDR frame at once.  When force IDR is inserted in to the stream, it
 * will start a new GOP.
 * @image html codec_force_idr.png "Figure 4-1. H.264 / H.265 Force IDR."
 *
 * @subsection example_codec_fidr Example 14: Generate IDR Frames for H.264 Streams.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p -e
 * board# test_encode -A --force-idr
 * @endcode
 *
 * - - - -
 *
 * @section codec_qp_limit 5. QP Limitation
 *
 * The QP means quantization parameters.  Smaller QP value means more details will be saved.  QP limitation
 * is used to specify the QP range of frame I, Q, P, B, C and D when doing stream encoding.  All the QP
 * of each encoding unit should be in the corresponding range.
 *
 *  | QP Limit Setting  | Frame Type        | Description |
 *  | :---------------: | :---------------: | :---------: |
 *  | --qp-limit-i      | I frame           | The key I frame |
 *  | --qp-limit-q      | Q frame           | Important P frame, such as fast seek P, long term P and some special encoded P frames |
 *  | --qp-limit-p      | P frame           | Normal P frame for non-SVC-T GOP, or level 0 P frame when using SVC-T GOP|
 *  | --qp-limit-b      | B frame           | Normal B frame for non-SVC-T GOP, or level 1 P frame when using SVC-T GOP|
 *  | --qp-limit-c      | C frame           | Level 2 P frame when using SVC-T GOP |
 *
 * @subsection example_codec_qp_limit Example 15: Set QP Range for I Frame.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --qp-limit-i 20~48 -e
 * @endcode
 * @image html codec_QP_limitation.png "Figure 5-1. H.264 / H.265 QP Limitation."
 *
 * - - - -
 *
 * @section codec_qp_adapt 6. Adapt QP
 * It is used to add the robustness for the QP boundaries based on the QP limitations.
 *
 * @subsection example_codec_qp_adapt Example 16: Set Adapt QP
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --qp-limit-i 20~48 --adapt-qp 2 -e
 * @endcode
 * @image html codec_QP_adapt.png "Figure 6-1. H.264 / H.265 QP Adapt."
 *
 * - - - -
 *
 * @section codec_pskip 7. Force P-skip
 * This is used to force the specified frame as full P-skip frame by application.  Additionally, when enabling the
 * repeating function for the P-skip, the encoder will take the skip number as the interval
 * between two P frames, all frames during the interval will be skipped.  If the skip mode
 * is specified as inverted mode, the encoder will take the skip number as the interval
 * between two P-skip frames.  It is primarily for low bit rate control in static scenes.
 *
 * @subsection example_codec_pskip1 Example 17: Add Force P-skip Frame
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1080p -e
 * board# test_encode -A --pskip-repeat 0 --pskip-repeat-intvl 1
 * @endcode
 *
 * @subsection example_codec_pskip2 Example 18: Force P-skip with Normal Mode
 * Insert three P-skip frames repeatedly between every two full P frames.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1080p -e
 * board# test_encode -A --pskip-repeat 1 --pskip-repeat-intvl 3 --pskip-repeat-mode 0
 * @endcode
 * @image html codec_repeate_force_pskip_frame_normal.png "Figure 7-1. H.264 / H.265 Repeat Force P-skip Normal Mode."
 *
 * @subsection example_codec_pskip3 Example 19: Force P-skip with Inverted Mode
 * Encode three P frames repeatedly between every two pskip frames.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1080p -e
 * board# test_encode -A --pskip-repeat 1 --pskip-repeat-intvl 3 --pskip-repeat-mode 1
 * @endcode
 * @image html codec_repeate_force_pskip_frame_revert.png "Figure 7-2. H.264 / H.265 Repeat Force P-skip Inverted Mode."
 *
 * - - - -
 *
 * @section codec_fdrop 8. Force Frame Drop
 * This is used to force the specified YUV dropped to encode by app.  Additionally, when enabling the repeating
 * function for the frame drop, the encoder will take the drop number as the encoding interval, all the
 * YUV during the interval will be dropped.  It will change the I frame interval in the time domain.
 *
 * @subsection example_codec_fdrop1 Example 20: Force Frame Drop
 *
 * @image html codec_force_frame_drop.png "Figure 8-1. H.264 / H.265 Force Frame Drop."
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)          // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1080p -e
 * board# test_encode -A --frame-drop-repeat 0 --frame-drop 1
 * @endcode
 *
 * @subsection example_codec_fdrop2 Example 21: Force Frame Drop Repeatedly
 * Drop the continuous 3 frames repeatedly, after every P frame.
 *
 * @image html codec_force_frame_drop_repeat.png "Figure 8-2. H.264 / H.265 Force Frame Drop Repeatly."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)          // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1080p -e
 * board# test_encode -A --frame-drop-repeat 1 --frame-drop 3
 * @endcode
 *
 * - - - -
 *
 * @section codec_skip_mode 9. Skip Frame Strategy and Mode
 * There are three kinds of strategies for encoder to skip frames.
 * - The first one is based on the size of the compressed picture.  When the bitstream size of one frame
 *   is out of limitation (decided by the real-time average bitrate), the encoder will skip frames.
 * - The second one is based on CPB size. When the CPB size exceeds the maximum value, then the encoder
 *   will skip frames.
 * - The third one is based on the target bitrate and maximum QP value. The encoder will skip frames when
 *   the bitrate is exceeded or the maximum QP value is reached.
 *
 * Currently, there are two modes for encoder to skip frames.
 * - The first one is dropping frames.
 * - The second one is repeating frames.
 *
 * The encoder also supports limiting the number of max skipped frames continuously. This is in case the encoder
 * skips too many frames without encoding a new frame showing the scene change.
 * <b> Kindly note that this skip behavior is decided by the encoder but not the application.</b>
 *
 * @subsection example_codec_smode1 Example 22: Frames Dropped according to Picture Size
 * Skip by dropping frames when the size of the compressed picture is out of limitation.
 * It's usually triggered when the scene changes suddenly.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)          // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1920x1080 --skip-frame-mode 0 --skip-frame 1 --bitrate 100000 -e
 * @endcode
 *
 * @subsection example_codec_smode2 Example 23: Frames Skipped according to Picture Size
 * Skip by repeating frames when the size of the compressed picture is out of limitation.
 * It's usually triggered when the scene changes suddenly.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)          // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1920x1080 --skip-frame-mode 1 --skip-frame 1 --bitrate 100000 -e
 * @endcode
 *
 * @subsection example_codec_smode3 Example 24: Frames Dropped according to CPB Size
 * Skip frames by dropping frames when the CPB size is exceeded.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)          // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1920x1080 --skip-frame-mode 0 --skip-frame 2 --cpb-buf-idc 31 --cpb-user-size 1000 -e
 * @endcode
 *
 * @subsection example_codec_smode4 Example 25: Frames Skipped according to CPB Size
 * Skip frames by repeating frames when the CPB size is exceeded.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)          // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1920x1080 --skip-frame-mode 1 --skip-frame 2 --cpb-buf-idc 31 --cpb-user-size 1000 -e
 * @endcode
 *
 * @subsection example_codec_smode5 Example 26: Frames Dropped according to Target Bitrate
 * Skip frames by dropping frames when bitrate exceeds the target value.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)          // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1920x1080 --skip-frame-mode 0 --skip-frame 4 --bitrate 100000 -e
 * @endcode
 *
 * @subsection example_codec_smode6 Example 27: Frames Skipped according to Target Bitrate
 * Skip frames by repeating frames when bitrate exceeds the target value.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1920x1080 --skip-frame-mode 1 --skip-frame 4 --bitrate 100000 -e
 * @endcode
 *
 * @subsection example_codec_smode7 Example 28: Set Maximum Skipped Frames Number
 * Based on example @ref example_codec_smode6, set the maximum skipped (in continuous) frame number as 5.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1920x1080 --skip-frame-mode 1 --skip-frame 4 --max-skip-num 5 --bitrate 100000 -e
 * @endcode
 *
 * - - - -
 * @section codec_ilimit 10. Maximum I Size Limit
 * When the size of the I frame is too large, the network transfer can be negatively affected. This
 * feature is used to limit the I frame size in the KB unit.
 *
 * @subsection example_codec_ilimit Example 29: Set the Maximum I Size
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)          // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h2560x1440 --smaxsize 2560x1440 --bitrate 4000000 --max-i-size-KB 300 -e
 * @endcode
 *
 * - - - -
 *
 * @section codec_mvdump 11. MV Dump for AVC
 * The following lists important notes about MV dump for advanced video coding (AVC):
 * <br>1)	Because the MV dump memory is immediately before the OSD buffer, ensure that the overlay is
 * correct when the MV dump is enabled.
 * <br>2)	It is preferable to run test_statistics at telnet, rather than serial port. The MV dump data
 * is too long to affect the Linux system timing.
 *
 * Configure menuconfig as shown:
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> private
 *              -> vin
 *                 -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                     (0x0200000) IAV Motion Vector Buffer Size
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-video
 *                 -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                    (0x0200000) IAV Motion Vector Buffer Size
 * @endcode
 *
 * @subsection example_codec_mvdump1 Example 30: Display Frame of MV Dump
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h720p -e
 * board# test_statistics -A -d 1 -b 0 // Enable and display 1 frame of MV dump
 * @endcode
 *
 * @subsection example_codec_mvdump2 Example 31: Capture Continuous MV Data
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h720p -e
 * board# test_statistics -A -d 1 -b 0 -c// Enable and display MV dump continuously
 * @endcode
 *
 * - - - -
 *
 * @section codec_aqp 12. The aqp Type for HEVC
 * The option `"aqp-type"` in `test_encode` is represented as shown below:
 *        <br>0. Use frame level QP for mode decision and size decision.
 *        <br>1. Use frame level QP for mode decision, MB level qp for size decision.
 *        <br>2. Use MB level QP for mode decision and size decision.
 *
 * @subsection example_codec_aqp1 Example 32: Frame Size Decided by QP Limitation
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1080p --aqp-type 0 -e
 * @endcode
 *
 * @subsection example_codec_aqp2 Example 33: Frame Size Decided by QP of MB
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1080p --aqp-type 2 -e
 * @endcode
 *
 * - - - -
 *
 * @section codec_au 13. Stream Structure au Type
 * The option `"--au-type"` can be used to control stream structure, and its detailed information is shown
 * as below:
 * <br>    0.  No AUD, No SEI;
 * <br>    1.  AUD before SPS, PPS, with SEI;
 * <br>    2.  AUD after SPS, PPS, with SEI;
 * <br>    3.  IDR: AUD before SPS & PPS, with BPSEI & PTSEI, P: AUD, PPS, PTSEI;
 * <br>    4.  No AUD, only SPS, PPS, with SEI.
 *
 * <table>
 * <caption id="au_type_table"></caption>
 * <tr>
 * <th align="center"> Streaming
 * <th align="center"> AU Type
 * <th align="center"> NALU Sequence
 * </tr>
 * <tr><td rowspan="6">H.264
 * <tr>     <td>0</td><td>SPS PPS I P P ...</td></tr>
 * <tr>     <td>1</td><td>AUD SPS PPS SEI I AUD SEI P AUD SEI P ...</td></tr>
 * <tr>     <td>2</td><td>SPS PPS AUD SEI I AUD SEI P AUD SEI P ...</td></tr>
 * <tr>     <td>3</td><td>AUD SPS PPS SEI I AUD PPS SEI P AUD PPS SEI P ...</td></tr>
 * <tr>     <td>4</td><td>SPS PPS SEI I SEI P SEI P ...</td></tr>
 * </td></tr>
 * <tr><td rowspan="6">H.265
 * <tr>     <td>0</td><td>VPS SPS PPS Ix3 Px3 Px3 ...</td></tr>
 * <tr>     <td>1</td><td>AUD VPS SPS PPS SEI Ix3 AUD SEI Px3 AUD SEI Px3 ...</td></tr>
 * <tr>     <td>2</td><td>VPS SPS PPS AUD SEI Ix3 AUD SEI Px3 AUD SEI Px3 ...</td></tr>
 * <tr>     <td>3</td><td>AUD VPS SPS PPS SEI Ix3 AUD PPS SEI Px3 AUD PPS SEI Px3 ...</td></tr>
 * <tr>     <td>4</td><td>VPS SPS PPS SEI Ix3 SEI Px3 SEI Px3 ...</td></tr>
 * </td></tr>
 * </table>
 *
 * @subsection example_codec_au1 Example 34: Specify AUD Before SPS / PPS with SEI Syntax
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -H 1080p --au-type 1 -e
 * @endcode
 *
 * @subsection example_codec_au2 Example 35: Set Au-type
 * When specified with `"--au-type=3"`, the structure of H.264 is shown as below:
 * <br>1)	IDR frame: AU delimiter, SPS, PPS, BPSEI, PTSEI
 * <br>2)	P frame:   AU delimiter, PPS, PTSEI
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * board# test_encode -A -h 1080p --au-type 3 -e
 * @endcode
 *
 * - - - -
 *
 * @section codec_roi_enc 14. ROI Encoding Tools
 *
 * Sometimes, it is necessary to process a single sub region of an image while leaving other regions
 * unchanged and a region of interest (ROI) processing is used for this purpose.  A ROI is a selected
 * area in a picture.  These ROIs can be coded in better or worse quality than the rest of the picture
 * with a special group of quantization parameter offset (QP offset), and coding strategy settings.
 * Usually, ROI is trigged by motion and works with external video analysis algorithm.
 *
 * The group of settings is implemented by filling the QP matrixes.  There are up to three QP matrixes
 * configured in the menuconfig.  It can make sure different frame types use different settings.  The
 * relationship between matrix number and frame types are as below:
 * @image html codec_roi_enc_matrix_table.png "Figure 14-1. H.264 / H.265 Matrix Table."
 *
 * For Cooper SDK Amba build:
 * @code
 * build $ make menuconfig
 *         -> drv_modules
 *            -> private
 *               -> vin
 *                  -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                      (1)   IAV ROI Matrix numbers for I/P/B/P2 frames
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-video
 *                 -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *			          (1)   IAV ROI Matrix numbers for I/P/B/P2 frames
 * @endcode
 *
 * The size of each matrix is 1/16x1/16 (for AVC) or 1/32x1/32 (for HEVC) of the encoding resolution.
 * And the each unit of the matrix in memory is filled with @ref iav_h264_qproi_data(for AVC) or
 * @ref iav_h265_qproi_data(for HEVC).  These structures contains the QP offset etc.
 * @image html codec_QP_matrix.png "Figure 14-2. H.264 / H.265 QP Matrix."
 *
 * In order to decide the method of implementation of the ROI, the following information can be used
 * as a reference:
 *      - For the category tool (HEVC only), a category lookup table will be issued to DSP at first, and
 * this table contains 8 categories.  App can pre-set different strategies for different categories.  And
 * then, the category index can be specified for each CTB in QP matrix to make the encoder do corresponding
 * operation according to the strategy of the category.
 *      - There are four kinds of strategies, such as FORCE_ZMV, FORCE_INTRA, FORCE_UC, FORCE_SKIP.  These
 * strategies will affect the encoder coding on the CTB directly.  The FORCE_ZMV means force the motion
 * vector of the CTB to be 0, and it will save the bits when coding for the motion vector.  FORCE_INTRA means
 * that force the encoder to do intra coding for the CTB.  FORCE_UC is used only for Smartrc app.  FORCE_SKIP
 * means that force the encoder to skip coding for the CTB, and it will also save the bits.
 * @image html codec_category_lookup_table.png "Figure 14-3. H.265 Category Lookup Table."
 *
 * @subsection example_codec_roi_enc1 Example 36: Set Category Lookup Table
 * Set category index 1 to be FORCE_ZMV in category lookup table.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_dummy_latency.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A --md-cat 1,2,3,4,0,0,0 -H 1080p -e
 * //the lookup table is 0,1,2,3,4,0,0,0. 0 has been set, it needs to set the other 7 value.
 * @endcode
 *      - For the user class tool(AVC only), the strategies for each class is specified with two kinds of
 * bias values, such as intra bias and direct bias.  The larger the intra bias value is, the less possibility
 * the MB will be done with intra coding. The larger the direct bias is, the less possibility the MB
 * will be done with skip coding.  In addition, as same as the category tool, there are three user classes can be
 * pre-set.  The user class 0 is used as default.  So the class 1 and 2 can be customized.  And then the
 * class index can be specified for each MB to tell the encoder do corresponding operation according to the
 * strategy of the user class.
 * @image html codec_user_class_group.png "Figure 14-4. H.264 User Class Group."
 *      - QP offset is used to apply an offset value based on the QP values of each MB or CTB.  The negative
 * offset will make the quality better if the CTB or MB will not be coded as skip.
 *      - All the ROI tools should be implemented by filling the QP matrixes.  So, frequently updating QP
 * matrix is necessary and it may increase the DRAM bandwidth.
 *      - Users can define several groups of the ROI parameters, and then apply different group settings for
 * different ROIs.
 *
 * @subsection example_codec_roi_enc2 Example 37: Set User Class Type for MB
 * @code
 * board# test_encode -A -h1080p -e
 * board# test_qproi
 * > a.  Config Stream A ROI
 * > 1 - Add Category
 * e.g., x 0, y 0, width 100, height 100, quality level 1	(better)
 * e.g., x 200, y 200, width 200, height 200, quality level 2	(worse)
 * @endcode
 *
 * @subsection example_codec_roi_enc3 Example 38: Set QP Offset for H.264
 * @code
 * board# test_encode -A -h1080p -e
 * board# test_qproi
 * > a.  Config Stream A ROI
 * > 4 - Add QP Adjust
 * e.g., x 0, y 0, width 100, height 100, qp offset -5	    (better)
 * e.g., x 200, y 200, width 200, height 200, qp offset 5	(worse)
 * @endcode
 *
 * @subsection example_codec_roi_enc4 Example 39: Set Category Type for CTB
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H1080p -e
 * board# test_qproi
 * > a.  Config Stream A ROI
 * > 4 - Add Category
 * e.g., x 200, y 200, width 200, height 200, qp offset 3
 * @endcode
 *
 * - - - -
 *
 * @section codec_fsync 15. Frame Sync
 * The frame sync feature is used to set some H.264 / H.265 parameters for the specified frame. It
 * is for the real-time update of H.264 / H.265 parameters on frame accuracy.
 *
 * The DSP requires more memory to cache several frames between source canvases and stream encoding.
 * In this case, the application can perform VCA on the specified frame from the source canvas, then
 * apply the calculated encode parameters on this frame.
 * @image html ut_frame_sync.png "Figure 15-1. Frame Sync Feature Diagram."
 *
 * To do frame sync, the encode dummy latency for the dedicated canvas needs to be set first when
 * entering preview.  There is no global encode dummy latency needed on CV5x any more, which wil
 * waste memory resources due to coarser granuarity.
 * Check @ref subsection_encode_dummy_latency for usage.
 *
 * @subsection example_codec_fsync1 Example 40: Set Encode Dummy Latency for Main Canvas
 * Please refer to <a href="script/encode_dummy_latency.lua" target="_blank"><b>encode_dummy_latency.lua</b></a>
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_dummy_latency.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_codec_fsync2 Example 41: Set Encode Dummy Latency for Specific Canvases
 * Set enc-dummy-latency in canvas config in lua script.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * @subsection example_codec_fsync3 Example 42: Force Insert IDR Frame
 * @code
 * board# test_encode --resource-cfg encode_dummy_latency.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -h1080p -e
 * board# test_frame_sync -A --force-idr
 * @endcode
 *
 * @subsection example_codec_fsync4 Example 43: Set QP Adjust Value
 * Set QP adjust value = -10 for the left top region.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_dummy_latency.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -h1080p -e
 * board# test_frame_sync -A --roi-matrix-idx 0 --roi-qp-adjust -10 --roi-region-qp-adjust 0
 * @endcode
 *
 * @subsection example_codec_fsync5 Example 44: Update QP Limitation for P Frame
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_dummy_latency.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -h1080p -e
 * board# test_frame_sync -A --qp-limit-p 20~20
 * @endcode
 *
 * @subsection example_codec_fsync6 Example 45: Update QP Limitation for I Frame
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_dummy_latency.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -h1080p -e
 * board# test_frame_sync -A --qp-limit-i 20~20
 * @endcode
 *
 * @subsection example_codec_fsync7 Example 46: Force Drop Frames
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_dummy_latency.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -h1080p -e
 * board# test_frame_sync -A --frame-drop 10
 * @endcode
 *
 * @subsection example_codec_fsync8 Example 47: Set Adaptive QP
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_dummy_latency.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -h1080p -e
 * board# test_frame_sync -A --adapt-qp 4
 * @endcode
 *
 * @subsection example_codec_fsync9 Example 48: Add Overlay Insertion
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg encode_dummy_latency.lua
 * board# test_encode -A -b 0 -h 3840x2160 -e
 * board# test_frame_sync -A -o1 -a0 -x0 -y0 -w128 -h64 -a1 -x200 -y100 -w64 -h128 -a2 -x0 -y300 -w48 -h96
 * @endcode
 *
 * @subsection example_codec_fsync10 Example 49: Add Blur Insertion
 * Please refer to  <a href="script/blur.lua" target="_blank"><b>blur.lua</b></a>.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a&
 * board# test_mempart -m 30 -s 0x800000
 * board# test_encode --resource-cfg blur.lua
 * board# test_encode -A -b 0 -h 3840x2160 -e
 * board# test_frame_sync -A -b1 -a0 -x128 -y128 -w128 -h128  -t 1 -a1 -x256 -y256 -w256 -h256 -t 1 -a2 -x512 -y512 -w512 -h512 -t1
 * @endcode
 *
 * @subsection example_codec_long_start_code Example 50: Setting HEVC Long Start Code
 * The user can use "--long-start-code" option to enable or disable the long start code flag for HEVC.
 * When enabling the flag, the frame inner tile starts with 4 bytes start code 0x00000001, meaning that start
 * codes are all with 4 bytes 0x00000001.
 * When disabling the flag, the frame inner tile starts with 3 bytes start code 0x000001, while the frame
 * boundary has start code with 4 bytes 0x00000001.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H1080p --long-start-code 1 -e
 * board# test_stream -f # Save stream and analyze via Vega Media Analyzer.
 * board# test_encode -A -s
 * board# test_encode -A -H1080p --long-start-code 0 -e
 * board# test_stream -f # Save stream and analyze via Vega Media Analyzer.
 * @endcode
 *
 * - - - -
 *
 * @section H26X_scalelist 16. H26x Scalelist
 *
 * H26x scalelist feature is used for users to specify scaling matrix when
 * AVC / HEVC encoding. Scaling matrix will be used inside encoder of DSP to do quantization. There are three options
 * to choose: 0: Disable scalelist, 1: Use the default scalelist, 2: Use the scalelist specified by users.
 * The default is 0.<br>
 *
 * SDK has built-in three sets of scalelist matrices with different strengths for AVC (@ref IAV_H26X_SCALELIST_STRENGTH), allowing users to directly specify the corresponding
 * parameter of "--scalelist-strength" to use scalelist for improve encode quality.
 * @note
 * - Because of hardware limit, the video digital signal processor (VDSP) does not support 32x32 scale list for HEVC Scalelist.
 * - The AVC scalelist only support high level profile for AVC encoding.
 * - By default, SDK enables the high profile for AVC encode, and set scalelist strength to low level.
 *
 * @subsection example_avc_scalelist_strength Example 51: Config Scalelist Strength for AVC
 * Steps are as below.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -b 0 --scalelist-strength 3 -e
 * @endcode
 *
 * @subsection example_avc_scalelist_setting Example 52: Custom Scalelist Matrix for AVC
 * Steps are as below.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -b 0 --profile 2
 * board# test_scalelist -A -h /usr/share/ambarella/lua_scripts/avc_scalelist.lua -s 2 -d
 * board# test_encode -A -e
 * @endcode
 *
 * @subsection example_hevc_scalelist_setting Example 53: Custom Scalelist Matrix for HEVC
 * Steps are as below.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H 1080p -b 0
 * board# test_scalelist -A -H /usr/share/ambarella/lua_scripts/hevc_scalelist.lua -s 2 -d
 * board# test_encode -A -e
 * @endcode
 *
 * @subsection example_avc_scalelist_bin_setting Example 54: Direct Use Scalelist Bin File for AVC
 * Steps are as below.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -b 0 --profile 2
 * board# test_scalelist -A -h avc_scalelist.bin -s 2 -b
 * board# test_encode -A -e
 * @endcode
 *
 * - - - -
 *
 * @section codec_full_range 17. Video Full Range
 *
 * Sometimes, users need to evaluate encoder performance & quality and calculate some
 * objective standard scores, such as PSNR-MSE, MS-SSIM, VMAF and so on.<br>
 * These calculations process all that need to decode the stream data into YUV data,
 * and then calculate the final score based on the golden data.
 * Many users use FFmpeg for decoding, but in the process of decoding,
 * attention should be paid to the conversion of color range.<br>
 *
 * @note
 * There are two color ranges, full-range and limited-range.
 *      - <b>Full-range</b> is mainly used for PC, and the value ranges
 *           of <b>Y/U/V are all [0, 255]</b>.
 *      - <b>Limited-range</b> is mainly used for TV, the range of <b>Y is [16, 235]</b>,
 *           and the range of <b>U/V is [16, 240]</b>.
 *
 * Ambarella encoder runs with the full-range color range by default (it's <b>"vui_info.video_full_range_flag == 1"</b>
 * option), and will not compress the data range during the encoding process.
 * In the process of FFmpeg decoding, users must keep the same range of video content as the encoder option,
 * either both are full range, or both are limited range.<br>
 *
 * FFmpeg decoded the streams into "limited-range" YUV by default,
 * so it is necessary to specify the "full-range" video range of YUV output in the decoding process.
 * Otherwise the color space will be narrowed, the mean square error (MSE) will be increased, and the scores
 * of PSNR and VMAF will be reduced accordingly.
 *
 * @subsection example_codec_decode_by_ffmpeg Example 55: Decode by FFmpeg
 * Set a full-range gray scale pattern YUV as the source YUV.
 * @image html codec_decode_by_ffmpeg_greybar_source.png "Figure 17-1. Gray Bar Pattern Source YUV."
 *
 * If users decode the stream by FFmpeg with defualt parameters (<b>limited-range</b>), the decoded YUV is as below:
 * @code
 * host$ ffmpeg -i case1.h265 -vcodec rawvideo -pix_fmt nv12 -an case1.yuv
 * @endcode
 * @image html codec_decode_by_ffmpeg_greybar_limited_range.png "Figure 17-2. Gray Bar Pattern YUV with Limited Color Range."
 *
 * If users decode the stream by FFmpeg with <b>full-range</b> parameters, the decoded YUV is as below:
 * @code
 * host$ ffmpeg -i case2.h265 -vcodec rawvideo -pix_fmt nv12 -an case2.yuv -lavfi "scale=out_range=full"
 * @endcode
 * @image html codec_decode_by_ffmpeg_greybar_full_range.png "Figure 17-3. Gray Bar Pattern YUV with Full Color Range."
 *
 * - - - -
 *
 * @section codec_qp_offset 18. Chroma QP Offset
 * Users can set diffrent `chroma_qp_offset` value to improve the AVC and HEVC encoding quality of chroma field.
 *
 * @note
 *  - The new chroma_qp_offset value will only take effect for the next GOP.
 *
 * @subsection example_codec_chroma_qp_offset Example 55: Set Chroma QP Offset
 *
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3      // For CV5 or CV52
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_dummy_latency.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * board# test_encode -A -h 1080p -e
 * board# test_encode -A --chroma-qp-offset 9  //users can set other offset value[-12, 12]
 * @endcode
 *
 * Please refer to <a href="script/encode_dummy_latency.lua" target="_blank"><b>encode_dummy_latency.lua</b></a>
 *
 * To check if this value is set successfully, users can download the video stream to use
 * the "MEGA Media Analyzer" to check the parameter.
 *
 * - - - -
 *
 * @section codec_cu_size_control 19. Support CU Size Control for HEVC
 * This feature is used to control the CU size for HEVC.
 * By default CU8 block and CU16 block are enabled, Ambarella can specify `disable-cu*` option in `test_encode`
 * to disable them. The `cu*-bias-level` parameters control the biases for these CU encoding levels. The
 * bigger the bias, the less these cu* will be coded. There are 7 levels for option `cu*-bias-level`
 * in `test_encode` and the range is [0,6].
 *
 * @note
 * - In order to completely turn off CU8, `--disable-cu8 1` can be used.
 * - In order to completely turn off CU16, `--disable-cu16 1` can be used. Be aware that
 * CU8 will also be turned off as well.
 *
 * @subsection example_codec_cu_size_control1 Example 56: Disable CU8 and CU16 Blocks
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H1080p -b0 --disable-cu8 1 --disable-cu16 1 -e
 * @endcode
 *
 * @subsection example_codec_cu_size_control2 Example 57: Set Bias Level for CU8 Block
 * Enable both CU8 block and CU16 block, and specify the biggest bias level for CU8 block.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H1080p -b0 --disable-cu8 0 --disable-cu16 0 --cu8-bias-level 6 -e
 * @endcode
 *
 * @subsection example_codec_cu_size_control3 Example 58: Set Bias Level for CU16 Block
 * Enable both CU8 block and CU16 block, and specify the biggest bias level for CU8 block and CU16 block.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H1080p -b0 --disable-cu8 0 --disable-cu16 0 --cu8-bias-level 6 --cu16-bias-level 6 -e
 * @endcode
 *
 * - - - -
 *
 * @section codec_qframe 20. Q Frame Mechanism
 * Because the I frame size is too large to transfer through an unstable network, the platform provides an alternative
 * method for reducing I frame size, called, "Q frame" (better quality P frame). The Q frame number follows
 * the formula: (2^(log_q_num_minus) -1).
 *
 * @subsection example_codec_qframe1 Example 59: Set Q Frame Number for AVC
 * Set AVC stream, 7 Q frames in one group of pictures (GOP).
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board # test_encode -A -h1080p --qp-limit-q 15~51 --q-qp-reduce 2 --log-q-num-minus-1 3 -N 120// the interval for Q frames is 15
 * board # test_encode -A -e
 * board # test_encode -A -s
 * @endcode
 *
 * @subsection example_codec_qframe2 Example 60: Set Q Frame Number for HEVC
 * Set high efficiency video coding (HEVC) stream, 3 Q frames in one GOP.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board # test_encode -A -H1080p --qp-limit-q 14~51 --q-qp-reduce 3 --log-q-num-minus-1 2 -N 120 // the interval for Q frames is 30
 * board # test_encode -A -e
 * board # test_encode -A -s
 * @endcode
 *
 * - - - -
 *
 */
/*!
 * @file gop.h
 * @brief
 * @version 0.1
 * @date 2022-04-02
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
 * @page fs_basic_gop BASIC - GOP
 *
 * Before GOP (Group of Pictures) introduction, the table below is a simple description for different frame types.
 * The encode priority is I > Q > P > B > C > D.
 *  | Frame Type | Description                                                                   |
 *  | :--------: | :---------------------------------------------------------------------------: |
 *  | I frame    | The key I frame                                                               |
 *  | Q frame    | Important P frame, such as fast seek P, long term P and some special encoded P frames |
 *  | P frame    | Normal P frame when using simple GOP <br>Level 0 P frame when using SVC-T GOP |
 *  | B frame    | Normal B frame when using simple GOP <br>Level 1 P frame when using SVC-T GOP |
 *  | C frame    | Level 2 P frame when using SVC-T GOP                                          |
 *  | D frame    | Level 3 P frame when using SVC-T GOP                                          |
 *
 * Different GOP model means different reference relationship for P frame.
 * These GOP models as below are supported.
 *  | GOP Model                | Description                                                     |
 *  | :----------------------: | :-------------------------------------------------------------: |
 *  | Simple GOP               | 1-ref P without fast-seek                                       |
 *  | Fast seek GOP            | 1-ref P with fast-seek                                          |
 *  | Two ref GOP              | 2-ref P(2 short-ref or short-ref + long-ref) without fast-seek  |
 *  | Fast seek with 2 ref GOP | 2-ref P(short-ref + long-ref) with fast-seek                    |
 *  | 2 level SVC-T GOP         | Scalable video coding temporal GOP with 2 layer                 |
 *  | 3 level SVC-T GOP         | Scalable video coding temporal GOP with 3 layer                 |
 *
 * @note
 * The default encode core mode is "dual core temporal", which only supports SVC-T GOP.<br>
 * Users need to set the core mode as "single core" or "dual core spatial" to run other GOPs.<br>
 * For more dual core mode usage, please refer @ref subsection_encoder_dual_cores.
 * For CV72, there is only one VDSP core, so only "single core" with core 0 is supported.
 *
 * @section gop_simple 1. Simple GOP
 *
 * @subsection gop_simple_without_B 1.1 Simple GOP without B frame
 * The reference relationship in a GOP for a simple reference without B frame is shown below:
 * @image html ut_gop_single_ref.jpg "The Reference Relationship in the GOP for Single Reference without B Frame"
 *
 * @subsubsection example_gop_simple1 Example 1: Simple GOP without B Frame
 * Simple GOP needs to work with dual encode core configurations as below:
 * @code
 * stream_0 = {
 * ...........
 * enc_core_cfg_enable = 1,
 * enc_core_mode = 0, -- or 3
 * ...........
 * }
 * @endcode
 *
 * The Lua script can be found <a href="script/stream_gop.lua" target="_blank"><b>here</b></a>.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg stream_gop.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -D -H 1920x1080 -b 3 --gop 0 -e
 * @endcode
 *
 * @subsection gop_simple_with_B 1.2 Simple GOP With B Frame
 *
 * The reference relationship in a GOP for a simple reference with B frame is shown below:
 * @image html ut_gop_single_ref_withb.jpg "The Reference Relationship in the GOP for a Single Reference with B Frame"
 *
 * @subsubsection example_gop_simple2 Example 2: Simple GOP with B frame
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg stream_gop.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua -D --max-gop-M 3
 * board# test_encode -D -H 1920x1080 -b 3 --gop 0 -M 3 -e
 * @endcode
 *
 * @section gop_fast_seek 2. Fast Seek GOP
 * @subsection gop_simple_fast_seek 2.1 Fast Seek GOP
 * The reference relationship in a GOP for simple references with a fast seek is shown below:
 * @image html ut_gop_single_fastseek.jpg "The Reference Relationship in the GOP for a Single Reference with Fast Seek."
 *
 * Important rules for this GOP structure:
 *      - The fast seek P frame will take the I / IDR frame as a reference.
 *      - The normal P frame will take the I / IDR or fast seek P frame as a reference.
 *
 * @subsubsection example_gop_fast_seek Example 3: Fast seek GOP
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg stream_gop.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -S 3 -H 1920x1080 -b 3 --gop 5 --fast-seek-enable 1 --fast-seek-intvl 3 -e
 * board# test_encode -S 3 --fast-seek-intvl 6
 * @endcode
 *
 * @note
 * - B frame (M > 1) is not supported in fast-seek GOP.
 * - The fast seek interval can be changed on the fly.
 *
 * There is a special case of fast seek GOP structure, if every P frame is fast seek P, it means all
 * P frames are referenced from the I / IDR frames.  This is like the "non-ref-P" GOP structure.
 * @image html ut_gop_non_ref.jpg "The Reference Relationship of \"non-ref-P\" GOP (fast-seek-interval = 1)"
 *
 * @subsubsection example_gop_simple3 Example 4: Special fast seek :"non-ref-P" (fast-seek-interval = 1)
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg stream_gop.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -S 3 -H 1920x1080 -b 3 --gop 5 --fast-seek-enable 1 --fast-seek-intvl 1 -e
 * @endcode
 *
 * @section gop_2ref 3. Two References GOP
 * Two references for P frame (2 Ref) is an advanced feature. Traditionally, one reference is used
 * for each P frame, and this reference frame is used as the short term reference. In order to get a
 * better video quality, the I/IDR frame is added to the reference frame list for each P frame, and
 * treated as the long term reference frame.  The long term reference is used by the encoder to encode
 * the static background areas, and the short-term reference is used to encode the motion areas.
 *
 * @subsection gop_2ref_st_lt	3.1 Two Reference GOP with Short Term Ref and Long Term Ref
 * The reference relationship in a GOP for two simple reference cases is as follows:
 * @image html ut_gop_simple_2ref.jpg "The Reference Relationship in the GOP for Simple 2 Reference"
 * Important rules for this feature:
 *      - The rate control (RC) is enabled by digital signal processor (DSP) for this feature, which means
 * that DSP runs the bitrate control method to meet the target bitrate as much as possible.
 *      - The supported resolution must be no larger than 1080P, due to more internal resources used
 * by DSP in 2-ref over single ref.
 *      - Stream rotation is not supported together with this feature as more internal resources are
 * used by DSP.
 *
 * @subsubsection example_gop_2ref_st_lt Example 5: Two reference GOP with short term ref and long term ref
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg stream_gop.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -S 3 -H 1920x1080 -b 3 --gop 6 --max-gop-M 3 -M 1 --two-ref-enable 1 -e
 * @endcode
 *
 * @subsection gop_2ref_short_term 3.2 Two Short Term References
 * The reference relationship in a GOP for two short term reference cases is as follows:
 * @image html ut_gop_2ref_short_term.jpg "The Reference Relationship in the GOP for 2 Short Term References"
 * Important rule for this feature:
 *      - There are two reference frames for each P frame, the reference frame are I/IDR/P frame.
 *
 * @subsubsection example_gop_2ref_short_term Example 6: Two short term reference GOP
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg stream_gop.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -S 3 -H 1920x1080 -b 3 --gop 6 --two-ref-enable 1 --two-st-ref 1 -e
 * @endcode
 * @note
 * For the 2 reference short term GOP, `--max-gop-M` must be set as 3.
 *
 * @section gop_2ref_fastseek 4. Two References with Fast Seek GOP
 * @note
 * Only "long term ref + short term ref" 2ref mode is supported with fast seek GOP.
 *
 * @subsection gop_2ref_fastseek_without_B 4.1 Two references with Fast Seek without B Frame
 * The advanced two reference cases combine the simple two reference cases together with both fast
 * seek and B frame. The reference relationship in a GOP for the advanced two references case is
 * shown below:
 * @image html ut_gop_simple_adv2ref_without_B.png "The Reference Relationship in the GOP for 2 Ref with Fast-Seek (No B Frames Cases)"
 *
 * The advanced two reference cases are as follows:
 *      - There is only one reference frame for fast seek P frame, and the reference frame is I/IDR
 * frame.  Fast seek function can be implemented based on this single reference relationship.
 *      - For the remaining P frames (normal P frames), there are two reference frames.  One is the
 * previous P frame, which is used as a short-term reference frame for motion area encoding;
 * the other is I/IDR frame, which is used as a long-term reference frame for static area encoding.
 *      - B frames are inserted into the reference frames (I/IDR frame, normal P frame, and fast seek
 * P frame).
 *
 * Important rules for this feature:
 *      - The supported resolution must be no larger than 1080P, due to more internal resources used
 * by DSP in two-references than a single reference.
 *      - Stream rotation is not supported together with this feature, due to more internal resources
 * used by DSP.
 *      - The advanced two reference features are supported in mode 0.
 *      - RC is not enabled for fast seek P frame, which may cause bitrate issue.  The application needs
 * to take the responsibility to do rate control from the Arm® side.
 *
 * @subsubsection example_gop_2ref2 Example 7: Two references with fast seek GOP without B
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg stream_gop.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -S 3 -H 1920x1080 -b 3 --gop 7 --max-gop-M 3 -M 1 --two-ref-enable 1 --fast-seek-enable 1 --fast-seek-intvl 4 -e
 * @endcode
 *
 * @subsection gop_2ref_fastseek_with_B 4.3 Two references with Fast Seek with B
 *
 * @image html ut_gop_simple_adv2ref.jpg "The Reference Relationship in the GOP for 2 Ref with fast-seek (2 B Frames Cases)"
 *
 * @subsubsection example_gop_2ref_fastseek_with_B Example 8: Two references with fast seek GOP with B
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg stream_gop.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -S 3 -H 1920x1080 -b 3 --gop 7 --max-gop-M 3 -M 3 --two-ref-enable 1 --fast-seek-enable 1 --fast-seek-intvl 12 -e
 * @endcode
 *
 * @section gop_svct 5. SVC-T
 * SVC-T is an advanced feature. Scalable video coding (SVC) standardizes the encoding of a
 * high-quality video bit stream that also contains one or more subset bit streams.  There are
 * several ways to implement SVC, such as temporal scalability (frame rate), spatial scalability
 * (picture size), and quality scalability (picture quality).
 *
 * @subsection gop_svct_hp 5.1 Hierarchical P GOP
 * Hierarchical P GOP supports up to three layers, enabling CV5x to encode multiple layers with
 * different reference frames to form a single bit stream.
 *
 * As a rate control tool, Hierarchical P GOP divides the video bit stream into several layers.
 * Because frames in higher layers can reference frames in lower layers, while frames in lower layers
 * cannot reference frames in higher layers, higher layers can be discarded without affecting lower layers.
 * A player that supports SVC-T feature can decide which higher video layers needs to be discarded,
 * and decode the rest of the video layers.  In order to support SVC-T, the application must use a
 * proper N and GOP structure for streams to encode.
 *
 * The following figure is a typical example for three layers.  Frames in Layer 2 are not referenced
 * by any frame in any other layers, so this layer can be discarded directly without affecting other
 * layers.  Frames in Layer 1 are referenced by frames in Layer 2, so the decoder can discard this
 * layer when Layer 2 is already discarded.  Layer 0 is referenced by all the other layers, and it
 * cannot be discarded.
 *
 * @image html ut_gop_hier_p2.jpg "Two Layers Hierarchical P GOP Structure."
 *
 * @image html ut_gop_hier_p3.jpg "Three Layers Hierarchical P GOP Structure."
 *
 * There are some limitations for this GOP:
 * - B frames are not supported, which means that M must keep the value of 1.
 * - For CV5x, SVC-T 2 can only work with "Dual Core Temporal" mode.
 *   For CV72, SVC-T 2 works with "Single Core 0".
 * - For CV5x, SVC-T 3 HEVC can work with "Single Core (0/1)" (enc_core_mode 0/1), or "Dual Core Spatial" (enc_core_mode 3).
 *   For CV72, SVC-T 3 HEVC can work with "Single Core 0".
 * - For CV5x, SVC-T 3 AVC can only work with "Single Core (0/1)" (enc_core_mode 0/1).
 *   For CV72, SVC-T 3  AVC can only work with "Single Core 0".
 *
 * @subsubsection example_gop_svct2 Example 9: SVC-T 2 GOP
 *
 * @endcode
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H 1920x1080 -b0 --gop 2 -e
 * @endcode
 *
 * @subsubsection example_gop_svct3 Example 10: SVC-T 3 GOP
 *
 * SVC-T 3 GOP needs to work with dual encode core configurations.
 * @code
 *  stream_0 = {
 * ...........
 * max_svct_layers_minus_1 = 2,
 * enc_core_cfg_enable = 1,
 * enc_core_mode = 0,
 * ...........
 * }
 * @endcode
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -H 1920x1080 -b0 --gop 3 -e
 * board# test_stream -t --split-svct // Split into 3 files (layer 0 / layer 0+1 / layer 0+1+2)
 * @endcode
 *
 * @subsection gop_svct_fastseek 5.2 Fast Seek in SVC-T 2/3 Layers
 * Fast seek feature is added to 2/3 layers of SVC-T GOP structure
 * this feature.
 *
 * Below is the reference relation for SVC-T 2/3 layers GOP structure with the fast seek.
 * @image html ut_gop_svct_2l_fs.jpg "2 Layers SVC-T + Fast Seek (Fast Seek Interval = 4)"
 *
 * To separate layer / fast seek information in the encoded video, NALU syntax for both AVC and HEVC
 * is used to achieve this.
 * @image html ut_gop_svct_3l_fs.jpg "3 Layers SVC-T + Fast Seek (Fast Seek Interval = 8)"
 *
 * 1.	For AVC, syntax "nal_ref_idc" in NALU header is used to separate different layers and fast seek frames:
 * <br>For above figure, the fast seek interval is 8 for 3 layers SVC-T.  There are 4 different values:
 * 	- For IDR/I frames and fast seek P frames (red and green), nal_ref_idc = 3
 * 	- For Blue Level 0 frames, nal_ref_idc = 2
 * 	- For Yellow Level 1 frames, nal_ref_idc = 1
 * 	- For Purple Level 2 frames, nal_ref_idc = 0
 * 2.	For HEVC, syntax "nuh_temporal_id_plus1" in NALU header is used to separate different layers and fast seek frames:
 * <br>For above figure, the fast seek interval is 8 for 3 layers SVC-T.  There are 4 different values:
 * 	- For IDR/I frames and fast seek P frames (red and green), nuh_temporal_id_plus1 = 1
 * 	- For Blue Level 0 frames, nuh_temporal_id_plus1 = 2
 * 	- For Yellow Level 1 frames, nuh_temporal_id_plus1 = 3
 * 	- For Purple Level 2 frames, nuh_temporal_id_plus1 = 4
 *
 * @subsubsection example_gop_svct4 Example 11: 2 layers SVC-T of HEVC with fast seek interval 6
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A --fast-seek-enable 1 --max-svct-layers-minus-1 1
 * board# test_encode -A -H1080p --gop 2 --fast-seek-intvl 6 -N 30 -e
 * @endcode
 *
 * @subsubsection example_gop_svct5 Example 12: 3 layers SVC-T of AVC with fast seek interval 4
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A --fast-seek-enable 1 --max-svct-layers-minus-1 2
 * board# test_encode -A -h1080p --gop 3 --fast-seek-intvl 4 -N 60 -e
 * @endcode
 */
/*!
 * @file on_the_fly.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_on_the_fly BASIC - On-the-Fly Settings
 *
 * @section on_the_fly 1. On the fly settings
 *
 * On-the-fly settings enable parameters to be changed independently during encoding.
 * The following parameters can be configured on the fly for each stream:
 *      - @ref example_crop_from_canvas  "Crop Offset"
 *      - @ref example_stream_frame_rate "Frame Rate"
 *      - @ref example_stream_monochrome "Monochrome"
 *      - @ref codec_br                  "Bit Rate"
 *      - @ref codec_gop                 "GOP Length"
 *      - @ref codec_idr                 "IDR Frequency or Intervals"
 *      - @ref codec_fidr                "Force IDR"
 *      - @ref codec_qp_limit            "QP limit"
 *      - @ref codec_roi_enc             "ROI Encoding Tools"
 *
 */
/*!
 * @file pm.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_pm BASIC - Privacy Mask
 *
 * @section section_pm 1. Privacy Mask
 *
 * Privacy mask (PM) is used to block sensitive areas, covering them
 * with opaque, single-color boxes, in both the preview and the encoded streams.
 * Privacy mask is widely used for displays, keyboard sequences (such as passwords),
 * and anywhere else where sensitive information needs to be kept invisible. It is possible to
 * retrieve the blocked-out areas during the preview and encoding states.
 *
 * Cooper family chips support privacy mask:
 * - The privacy mask take effect on the video input (VIN) domain.
 * - The precision of the single-color privacy mask varies according to the different
 *   VIN / Main combinations.
 * - The color of the single-color privacy mask can be changed to various Y / U / V combinations.
 *
 * Privacy mask affects all views from the preview (third / fourth / fifth buffer)
 * and the encoded streams (main / second / third / fourth / fifth / seventh buffer).
 *
 * @par Configurable Color of Single-Color Privacy Mask
 * It is possible to set it to various Y / U / V combinations.
 *
 * @par Number of Mask Area
 * The number of masks is unlimited.
 *
 * @par Size of Mask Area
 * The maximum size of masks is up to the VIN size.
 *
 * In privacy mask design, the concept of three domains need to be clear, including VIN domain,
 * main domain, and PM domain. "VIN domain" is the whole VIN capture window, "main domain" is
 * Main source buffer output window, and "PM domain" is the window that finally draws PM in memory.
 * When users need to draw PM, only coordinates and sizes on the "Main domain" are specified.
 * But actually, it needs to be converted to the coordinates and sizes on the "PM domain".
 * In most cases, "PM domain" and "Main domain" are the same size. In particular, if there is
 * rotate or flip enabled, "PM domain" needs to be converted from "Main domain". For example,
 * in the case of rotate, the width and height of "PM domain" are the height and width of
 * "Main domain". The usual way to deal with PM, PM coordinate and size convert is
 * "Main domain" ->"VIN domain" -> "PM domain".
 *
 * @image html VIN_Main_PM_domain.JPG Figure 1-1. VIN, Main, and PM Domain Conversion Diagram.
 *
 * <br>
 *
 * - - - -
 *
 * @section section_sc_pm_examples 2. Privacy Mask Examples
 *
 * @subsection example_pm1 Example 1: Add Two Privacy Masks
 * Add two privacy mask areas (x 100, y 100, width 256, height 256), (x 400, y 200, width 128, height 64) to 1080p.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_privacymask -c 0 -x 100 -y 100 -w 256 -h 256
 * board# test_privacymask -c 0 -x 400 -y 200 -w 128 -h 64
 * board# test_encode -A -h 1080p -b 0 -e
 * @endcode
 * @image html ut_single_color_mask_set.jpg "Figure 2-1. Privacy Mask Setting."
 *
 * @subsection example_pm2 Example 2: Remove One Small Mask Area from Privacy Mask Region
 * Remove a privacy mask area (x 164, y 164, width 128, height 128) from the privacy mask
 * region (x 100, y 100, width 256, height 256).
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_privacymask -c 0 -x 100 -y 100 -w 256 -h 256
 * board# test_privacymask -c 0 -x 164 -y 164 -w 128 -h 128 -d
 * board# test_encode -A -h 1080p -b 0 -e
 * @endcode
 * @image html ut_single_color_mask_remove.jpg "Figure 2-2. Privacy Mask: Remove a Privacy Mask Area."
 *
 * @subsection example_pm3 Example 3: Insert Circular Inner Privacy Mask
 * Insert circular inner privacy mask, circle center point is (960, 540), the radius is 544.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_privacymask -c 0 --radius 544 -C 960x540
 * @endcode
 * @image html ut_single_color_circular_inner_mask.jpg "Figure 2-3. Single-Color Privacy Mask: Insert Circular Inner Privacy Mask."
 *
 * @subsection example_pm4 Example 4: Insert Circular Outer Privacy Mask
 * Insert circular outer privacy mask, circle center point is (960, 540), the radius is 544.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_privacymask -c 0 -x 0 -y 0 -w 1920 -h 1080
 * board# test_privacymask -c 0 --radius 544 -C 960x540 -d
 * @endcode
 * @image html ut_single_color_circular_outer_mask.jpg "Figure 2-4. Single-Color Privacy Mask: Insert Circular Outer Privacy Mask."
 *
 * @subsection example_pm5 Example 5: Insert Triangle Privacy Mask
 * Insert triangle privacy mask, triangle vertex is (300, 500), (1000, 900), (1500, 400).
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_privacymask -c 0 --vertex 300x500 --vertex 1000x900 --vertex 1500x400
 * @endcode
 * @image html ut_single_color_Triangle_mask.jpg "Figure 2-5. Single-Color Privacy Mask: Insert Triangle Privacy Mask."
 *
 * @subsection example_pm6 Example 6: Insert Quadrilateral Privacy Mask
 * Insert quadrilateral privacy mask, quadrilateral vertex is (200, 300), (150, 500), (800, 600), (1000, 400).
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_privacymask -c 0 --vertex 200x300 --vertex 150x500 --vertex 800x600 --vertex 1000x400
 * @endcode
 * @image html ut_single_color_Quadrilateral_mask.jpg "Figure 2-6. Single-Color Privacy Mask: Insert Quadrilateral Privacy Mask."
 *
 * @subsection example_pm7 Example 7: Insert canvas domain PM to support cross-channel stitching case
 * For this use case, users can easily specify the PM offset and size in canvas domain through `test_privacymask`.
 * The PM can cover the areas from one or multiple channels.
 *
 * When the PM areas cross multiple channels, `test_privacymask` will convert the coordinates of the
 * canvas domain to the coordinates of the main buffer for each channel. Comparing with the use
 * experience where users need to manually calculate the coordinates of PM for each channel,
 * this method is much easier to configure.
 *
 * For example, to add one privacy mask area (x 2600, y 500, width 1000, height 900)
 *
 * The Lua script can be found <a href="script/cv5_4_vin_4k_main_horizonal_stitch_rotate_hvf.lua" target="_blank"><b>here</b></a>.
 *
 * @code
 * board# init.sh --na;modprobe ambrg;modprobe max9296 id=0x0303 vinc_id=0xb8;modprobe os08a10_mipi_brg fsync=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg ./cv5_4_vin_4k_main_horizonal_stitch_rotate_hvf.lua\
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -H 5120x1568 -b 0 -e
 * board# test_sensor_calib --mode 2 --channel-num 4 -f ./
 * board# test_stitch --mode 2 -f /root --channel-rotate-cw --hflip --vflip
 * board# test_stitch --mode 3 --overlap 0 --top 30,0 --bottom 30,2880 --overlap 1 --top 30,0 --bottom 30,2880\
 *                    --overlap 2 --top 30,0 --bottom 30,2880
 * board# test_privacymask -b 0 -x 2600 -y 500 -w 1000 -h 900 -Y 112 -U 72 -V 58
 * board# test_privacymask -b 0 --disable
 * @endcode
 * @image html ut_single_color_canvas_domain_mask.jpg "Figure 2-7. Single-Color Privacy Mask: Insert Canvas domain Privacy Mask."
 *
 * @subsection example_pm8 Example 8: Clear All Privacy Masks
 * @code
 * board# test_privacymask -c 0 --disable
 * @endcode
 * 
 * @subsection example_pm9 Example 9: Fill Warp Frame Border Artifact
 * When using LDC, the frame border may get some repeat artifacts. Users can fill and cover it with privacy mask.
 * According to the DSP warp pipeline behavior, privacy mask will be processed after H-Warp and before V-Warp.
 * As the H-warp edge is different in different warp case, the H-warp edge mask is needed, then privacy mask
 * can fill the repeat artifact with the mask.
 * The LDC example case shows as below:
 * @code
 * board# init.sh --imx274_mipi
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --lens-warp 1  --max-vwarp-blk-height 64
 * board# test_ldc -c 0 -F 60 -R 524 -m 1 -z 1.7 --rotate 10
 * @endcode
 * @image html ut_frame_border_artifact.png "Figure 2-8. Frame Border Artifact."
 *
 * Prepare the mask YUV. In mask YUV, border can be filled with black(0) and others can be filled with white(255).
 * Then feed this mask YUV as VIN by using feature EFR @ref example_efr5. Capture the H-Warp only YUV for final mask.
 * Run the LDC case again and using test_privacymask with final mask YUV.
 * @code
 * board# init.sh --na
 * board# modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_efr_yuv.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-nv12 1 --raw-capture 1 --lens-warp 1  --max-vwarp-blk-height 64 // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_efr_yuv.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-nv12 1 --raw-capture 1) --lens-warp 1  --max-vwarp-blk-height 64 // For CV72
 * board# test_efm -t 4 -s 1920x1080 -i frame.yuv -T 1
 * board# test_ldc -c 0 -F 60 -R 524 -m 1 -z 1.7 --rotate 10 --v-disable
 * board# test_yuvcap -b 0 -Y -f mask.yuv
 * @endcode
 *
 * @image html ut_original_mask_yuv.png "Figure 2-9. Original Mask YUV."
 *
 * @image html ut_mask_yuv_with_h_warp.png "Figure 2-10. Mask YUV with H-Warp."
 *
 * @code
 * board# test_privacymask -c 0 --mask-file mask.yuv
 * @endcode
 * @image html ut_frame_border_pm.png "Figure 2-11. Fill Frame Border Privacy Mask with Mask YUV."
 *
 * @note
 * This feature can only be used in LDC warp case not for multi-region warp case.
 *
 */
/*!
 * @file blur.h
 * @brief
 * @version 0.1
 * @date 2022-07-13
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
 * @page fs_basic_blur BASIC - Blur on Streams
 *
 * @section section_blur 1. Blur on Streams
 * In some particular situation, users may need to apply mosaic effect ROI
 * areas on streams. For example, users may need to draw mosaic on human
 * face to avoid the potential legal issue. Or there are some privacy
 * regions on the stream need to be protected. It is supported to insert
 * blur areas into streams. Once blur areas are inserted, the object will
 * be so severely blurred that it cannot be recognized anymore.
 *
 * There are two kinds of blur modes. One is the normal blur which provides
 * the standard rectangle blur area according to the provided size and coordinates.
 * The other is the arbitrary blur, which allows users to customize their blur
 * area shapes through changing specified blur area memory.
 *
 * @note
 * - Users should allocate continuous memory allocator (CMA) memory part
 *   (<B>IAV_PART_BLUR</B>) for blur. For arbitrary blur, the user needs
 *   to allocate one more CMA memory part (<B>IAV_PART_ARB_BLUR</B>).
 *
 * @subsection blur_lua_cfg 1.1 Blur Lua Configuration
 * - Canvas Configuration <br>
 *   Blur is inserted directly into the canvas. @ref lua_canvas_cfg "blur_enable" should
 *   be set for the canvas that will have a blur inserted.
 *   @code
 *   canvas = {
 *      {
 *          type = "encode",
 *          size = {3840, 2160},
 *          source = {"chan_0.main",},
 *          extra_dram_buf = 0,
 *          blur_enable = 1,
 *          max_blur_area_num = 0,
 *      },
 *   },
 *   @endcode
 *
 *   @note
 *   - Blur is inserted directly into the canvas. Therefore, streams encoding from the same
 *     canvas will see the same blur effect. For example, if both stream A and B encode from
 *     the canvas with the main buffer, blur areas on stream A will also be
 *     shown on stream B, and vice versa. If both stream A and B insert blur, the last blur
 *     configuration will take effect.
 *   - Blur is based on canvas coordinate system instead of stream coordinate system.
 *     Blurred areas' position does not vary with stream offset changing.
 *     @image html example_blur_coordinate_system.png "Figure 1-1. Blur is Based on Canvas Coordinate System."
 *
 * - Pyramid Configuration <br>
 *   At least one pyramid layer should be enabled as pyramid is used to accomplish different blur strength.
 *   @code
 *    pyramid = {
 *       input_buf_id = 0,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
 *       scale_type = 1,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
 *       ...
 *       layer_map = 0x70,
 *       layers = {
 *          {
 *             crop_win = {0, 0, 0 ,0},
 *          },
 *          {
 *             crop_win = {0, 0, 0 ,0},
 *          },
 *          {
 *             crop_win = {0, 0, 0 ,0},
 *          },
 *          {
 *             crop_win = {0, 0, 0 ,0},
 *          },
 *          {
 *             crop_win = {0, 0, 0 ,0},
 *          },
 *          {
 *             crop_win = {0, 0, 0 ,0},
 *          },
 *          {
 *             crop_win = {0, 0, 0 ,0},
 *          },
 *       },
 *    },
 *   @endcode
 *
 *   @note
 *   - Pyramid manual-feed mode won't save DRAM bandwidth when blur is enabled.
 *   - Blur strength decides the pyramid layer used as blur source.
 *     Different blur areas in the same canvas must have the same strength.
 *     To set different blurriness for different objects in the same canvas, please use blur coefficients
 *     (See @ref example_blur_coeff_on_stream).
 *   - Each canvas support up to 16 blur regions. Total blur regions of all canvases cannot exceed 64.
 *     Too many blur regions will impact the image digital signal processing (IDSP) performance.
 *
 * <br>
 *
 * ---
 *
 * @section section_blur_example 2. Stream Blur Examples
 *
 * @subsection example_blur_on_stream Example 1: Rectangle Blur on Stream A
 *
 * @par Hardware and Software Environment
 *
 * Please ensure that enough memory for blur is allocated. See the following notes.
 *
 * @note
 * Whenever users need to use the blur feature, it is required to allocate a
 * memory partition in the CMA pool. By default, <B>IAV_PART_BLUR</B> partition
 * size is 0. Users can allocate CMA memory part for blur via menuconfig.<br>
 * For Cooper SDK Amba Build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> private
 *             -> vin
 *                -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                    (0x0600000) IAV Blur Buffer Size //6M memory for blur area
 * @endcode
 * For Cooper SDK Yocto Build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-video
 *                 -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                    (0x0600000) IAV Blur Buffer Size //6M memory for blur area
 * @endcode
 * Alternatively, users are able to change the CMA partition size on the fly.
 * @code
 * board# test_mempart -m 30 -s 0x600000
 * board# cat /proc/ambarella/cma
 * mmb   phys[start-end]          size        virt[start-end]                        attr    buf_id      ref_cnt  dma_buf  usage
 * 0     0x100000000-0x100404000  0x00404000  0xffffffc040000000-0xffffffc040404000  0x0003  21          0        0        IAV_PART_PREALLOC
 * ...   ...                      ...         ...                                    ...     ...         ...      ...      ...
 * 11    0x1C8D00000-0x1C9CC0000  0x00FC0000  0xffffffc108d00000-0xffffffc109cc0000  0x0008  6           0        0        IAV_PART_WARP
 * 14    0x1C9D00000-0x1D3D00000  0x0A000000  0xffffffc109d00000-0xffffffc113d00000  0x0008  9           0        0        IAV_PART_MASK
 * 19    0x1D3D00000-0x1D4300000  0x00600000  0xffffffc113d00000-0xffffffc114300000  0x0000  30          0        0        IAV_PART_BLUR
 * @endcode
 *
 * Here are some example commands to enter preview and set up an AVC stream. The Lua script
 * can be found <a href="script/blur.lua" target="_blank"><b>here</b></a>.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg blur.lua
 * board# test_encode -A -b 0 -h qfhd -e
 * board# rtsp_server &
 * @endcode
 *
 * @par Translucent Blur
 * Mosaic can be applied to specified area(s) with specified color.
 *
 * In order to apply color to the blur area, users must initialize a color table for
 * stream blur. The length of the table is 16. Users can configure each entry in the color table
 * with "-d" option.
 *
 * @code
 * board# test_blur -d  0 -U 128 -V 128\
 *                  -d  1 -U 118 -V 148\
 *                  -d  2 -U 110 -V 180\
 *                  -d  3 -U  90 -V 240\
 *                  -d  4 -U  85 -V 198\
 *                  -d  5 -U  71 -V 182\
 *                  -d  6 -U  47 -V 150\
 *                  -d  7 -U  45 -V 127\
 *                  -d  8 -U  53 -V 104\
 *                  -d  9 -U 139 -V  10\
 *                  -d 11 -U 174 -V  11\
 *                  -d 12 -U 202 -V  46\
 *                  -d 13 -U 237 -V 148\
 *                  -d 14 -U 220 -V 202\
 *                  -d 15 -U 210 -V 227
 * @endcode
 *
 * In this test case, the color table is shown as below.
 *
 * @image html example_color_table.png "Figure 2-1. Color Table."
 *
 * Color of the blur area can be set with "--color-idx" option.
 *
 * In this example, color of the blur area 0 is set to red. Color of the blur
 * area 1 is set to blue.
 *
 * @code
 * board# test_blur -A -a 0 -x 500 -y 600 -w 400 -h 500 --color-idx 3\
                -a 1 -x 2300 -y 800 -w 512 -h 512 -t 2 --color-idx 13
 * @endcode
 *
 * @image html example_stream_blured.png "Figure 2-2. Blur on Stream."
 *
 * @par Blocky Blur
 *
 * Specify blocky blur through option "-b 1"
 *
 * @code
 * board# test_blur -A -a 0 -x 500 -y 600 -w 400 -h 500 \
                       -a 1 -x 2300 -y 800 -w 512 -h 512 -t 1 -b 1
 * @endcode
 *
 * @image html example_stream_blocky_blur_v6.png "Figure 2-3. Blocky Blur on Stream."
 *
 * @par Clear Blur Area
 *
 * Also, all blurred areas can be cleared using the following command.
 *
 * @code
 * board# test_blur -A -s
 * @endcode
 *
 * @subsection example_arbitrary_blur_on_stream Example 2: Run Arbitrary Blur Demo
 * @par Hardware and Software Environment
 *
 * Both IAV_PART_BLUR and IAV_PART_ARB_BLUR memory part are needed to be allocated.
 * See the following notes.
 *
 * @note
 * Besides <B>IAV_PART_BLUR</B> memory partition, users need to allocate another
 * memory partition <B>IAV_PART_ARB_BLUR</B> for arbitrary blur. Users can allocate
 * CMA memory part for arbitrary blur via menuconfig<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> private
 *              -> vin
 *                 -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                     (0x0100000) IAV Blur Buffer Size //1M memory for blur area.
 *                     (0x0500000) IAV Arbitrary Blur Buffer Size //5M memory for arbitrary area.
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-video
 *                 -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                    (0x0100000) IAV Blur Buffer Size //1M memory for blur area.
 *                    (0x0500000) IAV Arbitrary Blur Buffer Size //5M memory for arbitrary area.
 * @endcode
 * Alternatively, users are able to change the CMA partition size on the fly.
 * @code
 * board# test_mempart -m 30 -s 0x100000
 * board# test_mempart -m 31 -s 0x500000
 * board# cat /proc/ambarella/cma
 * mmb   phys[start-end]          size        virt[start-end]                        attr    buf_id      ref_cnt  dma_buf  usage
 * 0     0x100000000-0x100404000  0x00404000  0xffffffc040000000-0xffffffc040404000  0x0003  21          0        0        IAV_PART_PREALLOC
 * ...
 * 7     0x1C5300000-0x1C7300000  0x02000000  0xffffffc105300000-0xffffffc107300000  0x0008  1           0        0        IAV_PART_BSB
 * 17    0x1C7300000-0x1C7400000  0x00100000  0xffffffc107300000-0xffffffc107400000  0x0000  30          0        0        IAV_PART_BLUR
 * 18    0x1C7400000-0x1C7900000  0x00500000  0xffffffc107400000-0xffffffc107900000  0x0000  31          0        0        IAV_PART_ARB_BLUR
 * 10    0x1C8000000-0x1C8C80000  0x00C80000  0xffffffc108000000-0xffffffc108c80000  0x0008  5           0        0        IAV_PART_QPMATRIX
 * @endcode
 *
 * Run arbitrary blur demo. If it succeeds, the random size diamond shape blur area will be set on stream A.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg blur.lua
 * board# test_encode -A -b 0 -h qfhd -e
 * board# rtsp_server &
 * board# test_blur --arb-blur
 * @endcode
 *
 * @image html example_arbitrary_blur_on_stream_v6.png "Figure 2-4. Arbitrary Blur on Stream."
 *
 * @subsection example_blur_coeff_on_stream Example 3: Apply Different Blur Coefficients on Stream
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_mempart -m 30 -s 0x100000
 * board# test_encode --resource-cfg blur.lua
 * board# test_encode -A -b 0 -h qfhd -e
 * board# rtsp_server &
 * board# test_blur -A -a 0 -x 240 -y 0 -w 400 -h 2160 -c 0 \
          -a 1 -x 1120 -y 0 -w 400 -h 2160 -c 1 \
          -a 2 -x 2020 -y 0 -w 400 -h 2160 -c 2 \
          -a 3 -x 2940 -y 0 -w 400 -h 2160 -c 3 -t 2
 * @endcode
 *
 * @image html example_stream_blur_coeff.jpg "Figure 2-5. Different Blur Coefficients on Stream."
 *
 * @subsection example_blur_frame_sync Example 4: Frame Accurate Blur Insertion
 * Blur insertion can synchronize to a specific frame with PTS. To support this feature, canvas enc_dummy_latency
 * option must be enabled first.
 *
 * @code {.c}
 * canvas = {
 *        {
 *            ...
 *            enc_dummy_latency = 2,
 *            ...
 *        },
 *        ...
 * @endcode
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_mempart -m 30 -s 0x600000
 * board# test_encode --resource-cfg blur.lua
 * board# test_encode -A -b 0 -h qfhd -e
 * board# rtsp_server &
 * board# test_frame_sync -A -b1 -a0 -x128 -y128 -w128 -h128 -t 2 \
 *        -a1 -x256 -y256 -w256 -h256 -t 2 \
 *        -a2 -x512 -y512 -w512 -h512 -t 2
 * @endcode
 *
 * If the blur insertion fails to match with the specific PTS frame, there will be error message
 * reported from kernel dmesg log.
 *
 * @code
 * board# test_frame_sync -A -b1 -a0 -x128 -y128 -w128 -h128 -t 2 \
 *        -a1 -x256 -y256 -w256 -h256 -t 2 \
 *        -a2 -x512 -y512 -w512 -h512 -t 2 -s 100  // delay 100ms
 * #iav_error# irq_enc_iproc_status_msg(390): Failed to update frame sync cmd for blur.
 * @endcode
 *
 *//*!
 * @file overlay.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_overlay BASIC - Overlay on Streams
 *
 * @section section_overlay_feature 1. Overlay Features
 *
 * Cooper family chips use overlay hardware to superimpose graphical and/or textual
 * information on video streams. With the CV overlay function, the video is encoded
 * with extra YUV data, which results in overlay data format in YUV. To display the
 * overlay data, DSP refers to a color look-up table (CLUT) to obtain the
 * correct color. The memory is mapped to the application filled with the CLUT
 * information and OSD data. The total memory size depends on the chip version.
 *
 * @par Overlay & Source Buffer
 *
 * The overlay is inserted directly into the source buffer associated with the
 * encoded stream. Adding an overlay when the streams are encoding from the same
 * canvas can cause an overlay flickering, or "overlay leakage". For example,
 * if both stream A and B encode from the canvas with the main buffer, the
 * overlay inserted on stream A will also be shown on stream B, and vice versa.
 * If stream B's frame rate does not match stream A's, the result can be a loss
 * of OSD in the frames on stream B, causing an overlay flickering effect
 * ("overlay leakage").
 *
 * Therefore, if users require to perform overlay blending with more than one
 * stream while avoiding overlay leakage, Ambarella recommends encoding the
 * streams from separate source buffers and configuring overlays for each
 * stream.
 *
 * @par Color Look-up Table
 *
 * Cooper family chips support 16 independent color look-up tables (CLUT). Only
 * CLUT8 mode is supported. Each CLUT requires 1 KB of memory.<br>
 * With CLUT8, each look-up table is an array of 256 entries. The entry is
 * defined for four individual channels: Y, U, V, and alpha (transparency).
 * Alpha 0 is transparent and 255 is non-transparent.
 *
 * @par Coordinate: Position & Size
 *
 * The coordinate space of the overlay window is the same as that of the stream.
 * The following figure shows the overlay area position and size.
 *
 * @image html overlay_coordinate.png Overlay Area Position and Size
 *
 * @note
 * For each overlay area, the following restrictions are mandatory:
 * - The overlay width and height cannot be zero.
 * - The overlay cannot exceed the boundary of the stream.
 * - The width/height and horizontal/vertical offset of the overlay area must be
 *   a multiple of 4. The buffer pitch of the overlay area is suggested to
 *   be aligned to 64 bytes for high DRAM transferring efficiency.
 * - The total overlay size of all the streams should be no larger than the half
 *   of the mapped memory size.
 * For all streams, up to 64 overlay areas are supported.
 *
 * @par Rotated Overlay
 *
 * Because rotation and flip are performed after overlay insertion, the overlay
 * rotates or flips with the stream.
 *
 * To display the overlay in the orientation of the stream, the offset/width/height
 * of the overlay region should be calculated according to rotation degree, and
 * the overlay data should be transformed by a rotation matrix.
 *
 * The following figures show the overlay on the stream, and the overlay buffer
 * before clockwise rotations.
 *
 * @image html overlay_feature_rotate.png Rotated Overlay
 *
 * @par Multiple Buffering
 *
 * To prevent cache pollution, use the multiple buffering strategy to update
 * overlay content. The buffer number is determined by the updating frequency.
 *
 * The following describes when a user assumes that overlay is updated every N
 * frames:
 * - <B>Double Buffering</B><br>
 *   N >= 5. For example, in real time overlay display, the time string is updated
 *   every second. The frequency is much greater than 5 frames.
 * - <B>Quad buffering</B><br>
 *   N < 5. For example, using overlay as time stamp, every frame has different
 *   overlay content. The frequency is 1 frame.
 *
 * @par Insert Always
 *
 * "Insert Always" means that the overlay is inserted into every captured frame,
 * without taking into consideration if the encode frame factor is being used.
 * This feature is used to prevent overlay leakage when different streams with
 * distinct frame factors are encoded from the same source buffer.
 *
 * The following is an example scenario in which two streams are encoding from
 * the same source buffer:<br>
 *
 * @par
 * Both stream A and B are encoding from the main source buffer. Stream A's frame
 * rate is 30, and stream B's frame rate is 15. If the insert overlay to stream B
 * with "insert always" flag is enabled, stream A will also contain the overlay
 * in all frames. Alternatively, if the insert overlay with "insert always" is not
 * enabled, the overlay content will not appear in every frame from stream A,
 * causing stream A to appear as if it contains flash overlay content.
 *
 * @par Text Language Support
 *
 * Because many languages, such as Chinese and Japanese, use character sets larger
 * than the range of values of type char, the GNU C library includes support for
 * extended character sets. Follow this link for details on the GNU C extended
 * characters:
 *
 * http://www.chemie.fu-berlin.de/chemnet/use/info/libc/libc_18.html
 *
 * - <B>Wide Character</B><br>
 *   The text insert package of the CV5x Flexible Linux SDK requires characters to
 *   be represented as wide characters. As a result, users must convert Chinese and
 *   other languages to the wide character type before using the text insert package.
 * - <B>Character Set</B><br>
 *   The behavior of the function "char to wchar" is affected by the current locale.
 *   Users should install the character set and set it up before calling the function
 *   "char to wchar". Locales can be found in the toolchain folder:<br>
 *   <em>linaro-aarch64-2018.08-gcc8.2/aarch64-linux-gnu/libc/usr/share/locale.</em><br>
 *   Put the required locale to /usr/lib on the CV5x board. Before the function
 *   "char to wchar", call setlocale to set the current locale.
 *
 * <br>
 *
 * ---
 *
 * @section section_overlay_example 2. Overlay Examples
 *
 * @subsection example_overlay_rect Example 1: Rectangle Overlay
 *
 * Reboot the EVK board and then set up a stream on the EVK board.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -b 0 -e
 * @endcode
 *
 * @par Set up three rectangle overlay areas.
 *
 * @code
 * board# test_overlay -A -a 0 -x 0 -y 0 -w 128 -h 64\
 *                        -a 1 -x 200 -y 100 -w 64 -h 128\
 *                        -a 2 -x 0 -y 300 -w 48 -h 96
 * @endcode
 *
 * @image html ut_overlay_3rects.jpg "Three Rectangles Overlay on One Stream"
 *
 * @par Update the Overlay Area
 *
 * @code
 * board# test_overlay -A -a 0 -x 0 -y 100 -w 64 -h 128 --update
 * @endcode
 *
 * @par Clear all overlays for multiple streams
 *
 * @code
 * board# test_overlay -A --disable\
 *                     -B --disable\
 *                     -C --disable\
 *                     -D --disable
 * @endcode
 *
 *
 * @subsection example_overlay_always Example 2: Update the Overlay Every Frame
 *
 * Reboot the EVK board and then set up 2 streams on the EVK board.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -b 0 -e\
 *                    -B -h 1080p -b 2 -e
 * @endcode
 *
 * Update the Overlay Every Frame
 *
 * @code
 * board# test_overlay -r 1
 * @endcode
 *
 */

/*!
 * @file playback.h
 * @brief
 * @version 0.1
 * @date 2022-10-24
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
 * @page fs_basic_playback BASIC - Playback
 *
 * This chapter describes how to run the playback function on the CV5x / CV7x board in order to play
 * elementary streams recorded by Ambarella chips. The format of the video can be H.264 or H.265.
 * The digital signal processor (DSP) pipeline are required to be set up by the `test_encode` with lua
 * configuration before running the `test_decode` application. A virtual video input (VIN) is also involved for the
 * DSP pipeline. Other resources such as video output (VOUT) and pyramid are set up during the first step.
 *
 *
 * @section pb_npb 1. Normal Playback
 * <a href="script/dec_1ch.lua" target="_blank"><b>Here</b></a> is a sample lua for setting up the
 * resources with `test_encode`. More detailed explanation is in the following section.
 * @subsection example_pb_npb1 Example 1: Playback H.264 / H.265 stream and show the HDMI VOUT
 * @code
 * board# init.sh --na
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg dec_1ch.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_decode -f [h264/h265 es files]
 * @endcode
 *
 *
 * @subsection example_pb_npb2 Example 2: Multi-channel Playback and Show the HDMI® VOUT
 * Below is an example of decoding 4 HEVC streams at the same time.
 * <a href="script/dec_4ch.lua" target="_blank"><b>dec_4ch.lua</b></a> is a sample lua for setting
 * up 4 decoders and related resources.
 * <a href="script/hevc_4ch.lua" target="_blank"><b>hevc_4ch.lua</b></a> is a sample lua for
 * the stream information for `test_decode`.
 *
 * @code
 * board# init.sh --na
 * board# modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=4 custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg dec_4ch.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_decode -l hevc_4ch.lua
 * @endcode
 *
 * @note
 *  - For CV72, maximum 4 decoders of 4K resolution videos can be supported.
 *  - If decoding more than 2 videos at the same time, all encoding related resources are switched off.
 *
 * @subsection example_pb_npb3 Example 3: Playback Virtual Channels and Show the HDMI VOUT
 * Decoder can support deriving more IDSP channels. For example, 1 decoder can output decoded YUV
 * data to 1~4 image digital signal processing (IDSP) channels and perform different post-processes such as dewarp or LDC.
 * Below is an example of decoding 4 high efficiency video coding (HEVC) streams at the same time and derive to 6 channels.
 * <a href="script/4dec_6ch.lua" target="_blank"><b>4dec_6ch.lua</b></a> is a sample lua for setting
 * up 4 decoders to 6 IDSP channels and related resources.
 *
 * @code
 * board# init.sh --na
 * board# modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=4 custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg 4dec_6ch.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_decode -l hevc_4ch.lua
 * @endcode
 * - - - -
 *
 * @section pb_lua_config 2. Lua File Configuration for Decoder
 * The parameter `pre_dec_enable` is added into the channel lua configuration to indicate that this channel is
 * a decode channel. The parameter `pre_dec_type` is indicating the type of this decoder.
 *
 * @subsection pb_lua_dec_config 2.1 Decoder Configuration
 * For pyramid setup, @ref fs_basic_pyramid describes more details.<br>
 * @b Implementation:
 *      - The application captures the pyramid data using the standard unit test tool `test_yuvcap`.
 *
 * @b Usage:
 *      - The `pre_dec_enable` specifies that it is a decoder channel.
 *      - The `pre_dec_type` specifies the decoder type.
 *
 * @code
 * chan_0 = {
 * 	id = 0,
 * 	vsrc = vsrc_0,
 * 	vsrc_ctx = 0,
 * 	img_stats_src_chan = "chan_0",
 * 	...
 * 	raw_capture = 1,
 * 	pre_dec_enable = 1,
 * 	pre_dec_type = 0,               -- 0: h264, 1: h265
 * 	pyramid = {
 * 		input_buf_id = 3,
 * 		scale_type = 0,			-- 0: 1/sqrt(2)	1: 1/2
 * 		buf_addr = 0x0,
 * 		buf_size = 0x0,
 * 		layer_map = 0x3F,			-- bit field switch of each layer
 * 		layers = {
 * 			{
 * 				crop_win = {0, 0, 0 ,0},
 * 			},
 * 			{
 * 				crop_win = {0, 0, 0 ,0},
 * 			},
 * 			{
 * 				crop_win = {0, 0, 0 ,0},
 * 			},
 * 			{
 * 				crop_win = {0, 0, 0 ,0},
 * 			},
 * 			{
 * 				crop_win = {0, 0, 0 ,0},
 * 			},
 * 			{
 * 				crop_win = {0, 0, 0 ,0},
 * 			},
 * 		},
 * 	},
 * }
 * @endcode
 *
 * @subsection pb_lua_vin_config 2.2 Lua File Configuration for Virtual VIN Mode
 * It is required that the virtual sensor resolution cannot be smaller than the target video
 * file. But the virtual VIN driver cannot cover all the possible resolution. It is now
 * supported to specify the target virtual sensor configuration in the lua file.
 *
 * @b Usage:
 * - The `virt_mode_cfg_enable` specifies that a virtual mode will be sent to ambds driver.
 * - The `virt_mode_cfg_0` specifies the detailed sensor mode configuration.
 *
 * @code
 * virt_mode_cfg_0 = {
 *        width = 2688,
 *        height = 1520,
 *        bits = 12,
 *        max_fps = 60,
 *        default_fps = 30,
 *        hdr_mode = "linear",
 *        video_type = "yuv_656", -- options: "yuv_601", "yuv_656", "rgb_601", "rgb_656", "rgb_raw", "yuv_bt1120", "rgb_bt1120"
 *        sensor_id = 0x3014,
 *        agc_db_step = 0x00180000,
 * }
 *
 * vsrc_0 = {
 *       vsrc_id = 0,
 *        vsrc_status = 0,
 *        mode = "2688x1520",
 *        hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *        fps = 30,
 *        bits= 0,
 *        vsrc_ctx_switch = 0,
 *        virt_mode_cfg_enable = 1,
 *        virt_mode_cfg = virt_mode_cfg_0,
 * }
 * @endcode
 *
 * The sample command sequence is as follows:
 * @code
 * board# init.sh --na
 * board# modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=1  custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg dec_1ch.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_decode -f [h264/h265 es files]
 * @endcode
 *
 * @subsection pb_lua_ut_config 2.3 Lua File Configuration for Multi-channel Decoding
 * For multi-channel decoding, a lua file to specify the video files and the compressor / decompressor (codec) type is needed.
 * <a href="script/hevc_4ch.lua" target="_blank"><b>hevc_4ch.lua</b></a> is a sample lua.
 *
 * @b Usage:
 * - The `file_name` specifies the path of the video file.
 * - The `decoder_type` specifies the codec type.
 *
 * @code
 * chan_0 = {
 *      id = 0,
 *      file_name = "/root/cv2_4k.h265",
 *      decoder_type = 1,	-- 0: avc 1: hevc
 * }
 * @endcode
 *
 * @subsection pb_lua_vc_config 2.4 Lua File Configuration for Decode Virtual Channel
 * For decoding virtual channel, the virtual channel of a decoder needs to specify the
 * target "vsrc" field, and specify the "sensor_control" field to 0.
 *
 * @code
 * chan_3 = {
 *   id = 3,
 *   vsrc = vsrc_3,
 *   vsrc_ctx = 0,
 *   img_stats_src_chan = "chan_3",
 *   sensor_ctrl = 1,
 *   ...
 * }
 * chan_4 = {
 *   id = 4,
 *   vsrc = vsrc_3,
 *   vsrc_ctx = 0,
 *   img_stats_src_chan = "chan_4",
 *   sensor_ctrl = 0,
 *   ...
 * }
 * @endcode
 *
 *
 * - - - -
 *
 * @section pb_perf 3. Software Decoding Performance
 * The table below shows the software decoding performance for CV72.
 *
 * | Encode Type | Resolution | Bitrate | FPS    | CPU Usage |
 * | :-----      | :----      | :----   |  ----: |     ----: |
 * | AVC         | 2MP        | 2Mbps   | 215.57 |   95.26   |
 * |             |            | 3Mbps   | 194.69 |   97.03   |
 * |             |            | 4Mbps   | 183.63 |   97.71   |
 * |             | 5MP        | 3Mbps   | 125.36 |   96.52   |
 * |             |            | 4Mbps   | 117.32 |   96.86   |
 * |             |            | 5Mbps   | 113.5  |   97.24   |
 * |             |            | 6Mbps   | 107.04 |   98.17   |
 * |             | 8MP        | 4Mbps   | 59.92  |   97.76   |
 * |             |            | 6Mbps   | 56.74  |   96.12   |
 * |             |            | 8Mbps   | 54.18  |   97.7    |
 * | HEVC        | 2MP        | 2Mbps   | 45.98  |   59.29   |
 * |             |            | 3Mbps   | 43.07  |   58.73   |
 * |             |            | 4Mbps   | 43.09  |   58.77   |
 * |             | 5MP        | 3Mbps   | 30.08  |   60.55   |
 * |             |            | 4Mbps   | 27.2   |   60.42   |
 * |             |            | 5Mbps   | 25.83  |   60.62   |
 * |             |            | 6Mbps   | 26.37  |   60.38   |
 * |             | 8MP        | 4Mbps   | 13.89  |   60.96   |
 * |             |            | 6Mbps   | 12.42  |   60.29   |
 * |             |            | 8Mbps   | 11.35  |   60.13   |
 *
 */
/*!
 * @file duplex.h
 * @brief
 * @version 0.1
 * @date 2022-10-24
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
 * @page fs_basic_duplex BASIC - Duplex
 *
 * This chapter describes how to run encoding and playback function on the CV5x / CV7x board at the
 * same time.
 * The digital signal processor (DSP) pipeline are required to be set up by the `test_encode` with lua
 * configuration before running the `test_decode` application. A virtual video input (VIN) is also involved for the
 * DSP pipeline. Other resources such as video output (VOUT) and pyramid are set up during the first step.
 * @note
 * - The MB loading of the system is also limited by the MB loading in the chip specification.
 * - Duplex can support up to 2 decoders.
 *
 * @section duplex_sec1 1. Duplex
 * As the playback function sets up the DSP channel as encode from raw (EFR). Now it is possible
 * to run preview / encoding and decoding at the same time. Adding the decoding channel configuration
 * into the lua file can enable the duplex mode. @ref fs_basic_playback "Playback" can be the reference
 * about how to set up the decode channel.
 *
 * Below is an example for one encoding channel and one decoding channel. The lua script can be found
 * <a href="script/duplex_1ch_enc_1ch_dec.lua" target="_blank"><b>here</b></a>
 * The sample command sequence is as follows:
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)            // For CV72
 * board# modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=1  custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg duplex_1ch_enc_1ch_dec.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_decode -f [h264/h265 es files]
 * board# test_encode --idle --no-prev
 * @endcode
 *
 * @note
 * - As the system is running preview / encoding, the system will not automatically enter
 * idle mode when decoding is complete. Users are required to use `test_encode --idle --no-prev` to
 * enter idle mode.
 *
 */
/*!
 * @file data_dump.h
 * @brief
 * @version 0.1
 * @date 2020-02-15
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
 * @page fs_basic_data_dump BASIC - Data Dumping
 *
 * @section data_dump 1. Data Dumping
 * The data is generated by the DSP, including Bayer pattern RAW data, YUV 420
 * and YUV 422 data from source canvases.  ME1 data from source canvases and
 * Motion Vector (MV) data from streams can be dumped for the Arm® application after
 * the DSP enters the preview or the encoding state.
 *
 * @subsection example_data_dump1 Example 1: Getting 1080p Raw Data for Calibration (CFA Input Only)
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua --raw-capture 1
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua --raw-capture 1)
 * board# test_yuvcap -i 8 -R -f /mnt/
 * save raw buffer done!
 * Raw data resolution 1920 x 1080 with pitch 3840.
 * @endcode
 *
 * @subsection example_data_dump2 Example 2: Capture 1080p YUV from Canvas 0 with a Blocking Call
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p)
 * board# test_yuvcap -b 0 -Y -f 1.yuv -F 1
 * Delay 0 frame capture YUV data.
 * Capture YUV cavas(buffer)0: size[1920x1080] in YV12 format
 * @endcode
 *
 * @subsection example_data_dump3 Example 3: Capture 480p YUV from Canvas 1 with a Non-blocking Call
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p -Y --bsize 480p
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p -Y --bsize 480p)
 * board# test_yuvcap -b 1 -B 1 -Y -f 1.yuv -F 1
 * Delay 0 frame capture YUV data.
 * Capture YUV cavas(buffer)1: size[720x480] in YV12 format
 * @endcode
 *
 * @subsection example_data_dump4 Example 4: Capture 480p ME Data from Canvas 0 in 30 Frames with a Blocking Call
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p -Y --bsize 480p
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p -Y --bsize 480p)
 * board# test_yuvcap -b 0 -M -f 2.me1 -r 30
 * Delay 0 frame capture me data.
 * Save_me_buffer: resolution 240x136 with Luma only.
 * @endcode
 *
 * @subsection example_data_dump5 Example 5: Capture 480p ME Data from Canvas 1 in 30 Frames with a Blocking Call
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p -Y --bsize 480p
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                    -X --bsize 1080p --bmaxsize 1080p -Y --bsize 480p)
 * board# test_yuvcap -b 1 -m -f /tmp/1.me1 -r 30
 * Delay 0 frame capture me data.
 * Save_me_buffer: resolution 180x120 with Luma only.
 * @endcode
 *
 * @subsection example_data_dump6 Example 6: Capture Raw slice Data
 * Config "raw_slice_num" and "raw_slice_cached_items" in "chan" section of lua.
 * @code
 * ...
 * chan_0 = {
 * ...
 *     raw_slice_num = 4,
 *     raw_slice_cached_items = 4,
 * ...
 * }
 * @endcode
 * @code
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear.lua --raw-capture 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * ## For the slice data info only
 * board# test_yuvcap -i 8 -S -f cap_raw_slice -r 20 --info-only
 * # For the slice image data
 * board# test_yuvcap -i 8 -S -f cap_raw_slice -r 20
 * # For raw slice data and contrast enhance data
 * board# test_yuvcap -i 8 -S -E 1 -f cap_raw_slice -r 20
 * @endcode
 *
 * - - - -
 *
 * @section data_dump_raw_dio 2. Data Dumping: Capture Raw Data via Direct IO
 * For the 4K or bigger resolution raw picture, the io with buffer is too slow to write into
 * solid-state drive (SSD) of peripheral component interconnect express (PCIe). To avoid
 * losing the frame due to the low speed, the direct io without buffer is available.
 * It can get the maximum performance of SSD.
 *
 * @Note: For SSD performance, it is affected by multiple factors such as overheating,
 * insufficient write space and insufficient internal cache, so getting slower in the
 * write process may be caused by the above reasons.
 *
 * Enable raw pool direct io feature via menuconfig option, clean, and rebuild the SDK.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> kernel
 *           -> linux-patch-rmem-dio-choice@virtual (kernel/linux-patch) (linux-patch-rmem-dio)
 *              (X) linux-patch-rmem-dio
 *        -> drv_modules
 *           -> private
 *             -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                 [*]   Enable Direct IO feature for raw pool.
 * @endcode
 * @code
 * build$ make menuconfig_public_linux
 *    Device Drivers  --->
 *        -*- Device Tree and Open Firmware support  --->
 *            [*]   Add dio support to rmem
 * @endcode
 *
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-kernel
 *                 -> linux-patch-rmem-dio-choice@virtual (meta-ambabsp/recipes-kernel/linux-patch)
 *                    (X) linux-unpatch-rmem-dio
 *           -> meta-ambabsp
 *              -> recipes-video
 *                 -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                    [*]   Enable Direct IO feature for raw pool.
 * @endcode
 * @subsection example_data_8K_raw_dump_via_direct_io Example 6: Capture 8K Raw Data from CV5x via Direct IO
 * Configure "ext_mem" and "raw_feed_frame_num" in "chan" section of lua.
 * For 8k raw data, the DSP need more memory to cache the frame, so the user should increase
 * "shared" region size, the Lua script can be found
 * <a href="script/cv5_vin0_8k_linear_dio.lua" target="_blank"><b>here</b></a>.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> board (boards)
 *           -> Memory
 *              (680) DSP Shared Memory size in MB
 * @endcode
 *
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-bsp
 *                 -> board (meta-ambabsp/recipes-bsp/board)
 *                    -> Memory
 *                       (680) DSP Shared Memory size in MB
 * @endcode
 * @code
 * board# init.sh --na;modprobe imx586_mipi vinc_id=0 bus_id=5 cphy=1;test_aaa_service -a&
 * board# test_encode --resource-cfg cv5_vin0_8k_linear_dio.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# mkdir /amba -p;mount /dev/nvme0n1 /amba/ -t ext4; cd /amba/
 * board# test_yuvcap -i 0 -R -f cap_raw -r 1 -D
 * @endcode
 *
 * - - - -
 *
 * @section data_dump_mv 3. Data Dumping:  MV Dump
 * To use MV dump, users should specify the size of MV buffer first as below.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> private
 *              -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                  (0x0200000) IAV Motion Vector Buffer Size
 * @endcode
 *
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-bsp
 *                 -> recipes-video
 *                    -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                       (0x0200000) IAV Motion Vector Buffer Size
 * @endcode
 * @subsection example_mv_dump1 Example 7: Capture 720p MV Data with Blocking Way
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\        // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 * board# test_encode -X --bsize 1080p --bmaxsize 1080p -A --mv-statis-enable 1
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\   // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 *     board# test_encode -X --bsize 1080p --bmaxsize 1080p -A --mv-statis-enable 1)
 * board# test_encode -A -h720p -e
 * board# test_statistics -A -d 1 -b 0
 * @endcode
 *
 * @subsection example_mv_dump2 Example 8: Capture 720p Continuous MV Data with Blocking Way
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\        // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 * board# test_encode -X --bsize 1080p --bmaxsize 1080p -A --mv-statis-enable 1
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\   // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 *     board# test_encode -X --bsize 1080p --bmaxsize 1080p -A --mv-statis-enable 1)
 * board# test_encode -A -h720p -e
 * board# test_statistics -A -d 1 -b 0 -c
 * @endcode
 *
 * - - - -
 *
 * @section data_dump_qp_hist 4. QP Histogram Dump for AVC and HEVC
 * Before dumping, specify the number of streams that need to dump QP histogram as image audio video (IAV)
 * driver needs to allocate extra memory to store QP histogram data. Configure menuconfig as follows:<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> private
 *              -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                  (1)   IAV Pic Statistics Dump Stream Num
 * @endcode
 *
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-bsp
 *                 -> recipes-video
 *                    -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                       (1)   IAV Pic Statistics Dump Stream Num
 * @endcode
 * @subsection example_avc_qp_hist_dump Example 9: Display QP Histogram Dump of 1 Frame for AVC
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua \        // For CV5 or CV52
 *             --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua \   // For CV72
 *             --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode -A -b 0 -h 1080p --pic-statis-enable 1 -e
 * board# test_statistics -A -d 2 -b 0
 * @endcode
 * The result is as follows:
 * @code
 *	data offset:    8000
 *	width:  1920    height: 1080    pitch:  1920
 *	start_pts:      879430730
 *	arm_pts:        5589958
 *	******************raw data******************
 *	QP histogram:
 *	------------------------
 *	QP value  |  mbs_per_cat
 *	------------------------
 *	   21      |     421
 *	   22      |     3778
 *	   23      |     1706
 *	   24      |     2255
 * @endcode
 *  | Param | Information |
 *  | :--- | :--------- |
 *  | width | The frame width |
 *  | height | The frame height |
 *  | pitch | The frame pitch |
 *  | QP_value[4] | QP values. The AVC / HEVC encoder uses 4 QP values in one encoded frame |
 *  | mbs_per_cat[4] | The macro blocks number with corresponding QP value |
 *
 * @subsection example_hevc_qp_hist_dump Example 10: Display QP Histogram Dump of 1 Frame for CV5x HEVC with Dual Core Spatial Mode
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua \
 *             --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_encode -A -b 0 -H 1080p --pic-statis-enable 1 -e
 * board# test_statistics -A -d 2 -b 0
 * @endcode
 *
 * The result is as follows:
 * @code
 *	core_0 data offset:     a000
 *	core_1 data offset:     c000
 *	width:  1920    height: 1080    pitch:  1920
 *	start_pts:      2766288538
 *	arm_pts:        19409717
 *
 *	********************************************
 *	qp_histogram:
 *	-----------------------------
 *	QP value   |  mbs_per_cat
 *	-----------------------------
 *	   21      |     148
 *	   22      |     9234
 *	   23      |     16786
 *	   24      |     6232
 * @endcode
 *  | Param | Information |
 *  | :--- | :--------- |
 *  | width | The frame width |
 *  | height | The frame height |
 *  | pitch | The frame pitch |
 *  | QP_value[4] | QP values. The AVC / HEVC encoder uses 4 QP values in one encoded frame |
 *  | mbs_per_cat[4] | The macro blocks number with corresponding QP value |
 *
 * - - - -
 *
 * @section data_dump_idsp_motion 5. Dump and Display IDSP Motion Data with Encode Mode 5/9
 * Currently, only encode mode 5 and mode 9 support dump motion data.
 * Before dumping, user need to enable the flag of "motion_output_enable" in lua.
 *
 * @code
 * ...
 * chan_0 = {
 * ...
 *     motion_output_enable = 1,
 * ...
 * }
 * @endcode
 *
 * Eaxmple: Motion data dump and display on mode 5:
 *
 * The VOUT lua script for motion display can be found in <a href="script/motion_data_display_vout_hdmi.lua" target="_blank"><b>vout_hdmi.lua</b></a>.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear.lua \        // For CV5 or CV52
 *             --vout-cfg /root/vout_hdmi.lua --enc-mode 5
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear.lua \   // For CV72
 *             --vout-cfg /root/vout_hdmi.lua --enc-mode 5)
 *
 * # For motion data dump
 * board# test_yuvcap -c 0 --motion -f mo_test -r 20
 *
 * # For motion data display on vout by osd
 * board# rmmod ambarella_fb;modprobe ambarella_fb mode=ayuv8888  buffernum=3
 * board# test_idsp_motion -t 1 -v 2 -c 0 -m 0 -S1 -a 255
 *
 * # For motion data display on stream by overlay
 * board# test_encode --resource-cfg --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear.lua --enc-mode 5 --raw-capture 1 --vout-cfg /root/vout_hdmi.lua \
 *             --img-scale 1 --img-scale-format 2 --img-scale-max-in 1920x1080 --img-scale-max-out 1920x1080 --img-scale-job-queue-depth 8
 * board# test_encode -C -b3 -H480p -e
 * board# test_idsp_motion -t0 -s2 -e1 -c0 -m 0 -d 0 -a 255
 * @endcode
 *
 * Below is an illustration of motion data mapped to YUV400 format.
 *
 * @image html motion_data.png "Figure 5-1. Motion Data Image."
 *
 * @note
 * - The motion data size is 1/256 of the vin resolution (width and height divided by 16).
 * - Every byte of motion data represents the intensity of motion mapped to the vin region
 *   at that index location.
 * - The value of motion data (0 to 255) indicates the motion intensity. "0" indicates that
 *   there is no motion, and "255" indicates that the motion is the strongest.
 */
/*!
 * @file fps.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_basic_fps BASIC - Frame Rate
 *
 * @section section_fps_features 1. Frame Rate
 * Each processing stage can have a different frame rate.  The variance in the
 * frame rate can occur in any of the following components.
 *
 * @image html frame_rate_at_stages.png Figure 1-1. Frame Rate at Different Stages.
 * @par VIN fps
 * Each sensor can be configured at different frame rate. The video input (VIN) frames per second (fps) are
 * used as the input frame rate for VIN stage inside digital signal processor (DSP).
 *
 * @par RAW fps
 * At VIN stage, it can output different frame rates for RAW data from VIN fps.
 * The RAW fps must be no larger than VIN fps, which means that VIN can choose
 * to skip sending RAW data to dynamic random access memory (DRAM). This can save DRAM bandwidth for RAW data.
 * Normally, RAW fps is equal to VIN fps. But it may be different for some
 * scenarios, such as scale or region of interest (ROI) VIN cases. For scale or ROI VIN cases, it may
 * possibly generate multiple RAW data from the same sensor input frame.
 *
 * @par Channel fps (or IDSP fps)
 * For each processing channel, the output frame rate (image digital signal processing (IDSP) fps) can vary from
 * the input frame rate (RAW fps). This frame rate can be larger or smaller
 * than the original RAW fps.  When it is larger than RAW fps, IDSP
 * periodically generates intermediated frames.  When the rate is smaller
 * than RAW fps, IDSP periodically skips RAW frames.
 *
 * @par Canvas fps
 * Each canvas can have a different frame rate. The input fps for the canvas
 * is its channel IDSP fps, and the output fps is the canvas fps. The output
 * fps can be equal to or smaller than the channel IDSP fps. IDSP periodically
 * skips frames to generate smaller canvas fps out of the channel IDSP fps.
 *
 * @par Pyramid fps
 * If manual feeding is not used, the pyramid fps should have the same frame
 * rate as the channel IDSP fps. If manual feeding is used, the pyramid
 * fps is dependent on Arm's feeding speed (up to the channel IDSP fps).
 *
 * @par Stream fps
 * The stream fps is the actual encoding frame rate, and its input frame rate
 * is canvas fps.  The stream fps can be equal to or smaller than its input
 * canvas frame rate.  Users can use the frame factor (based on the canvas fps)
 * to specify the stream fps. Video digital signal processor (VDSP) periodically skips frames to generate the
 * smaller stream fps. Users can also use `stream-abs-fps-enable` and `stream-abs-fps`
 * option to enable a fixed smaller stream fps.
 *
 * @par VOUT fps 
 * The video output (VOUT) fps is the actual VOUT display output frame rate, and its input
 * frame rate is canvas fps.  The VOUT fps can be larger or smaller than its input
 * canvas fps.  When VOUT fps is smaller than its input canvas fps, VOUT will
 * periodically skips frames to meet the fps for the actual display device.
 * When VOUT fps is larger than its input canvas fps, VOUT will display repeated
 * frames periodically to meet the fps for the actual display device.
 *
 * <table>
 * <caption id="table_fps_comparison">Table 1-1. Different fps Comparison.</caption>
 * <tr><th> fps type      <th> Stage         <th> Input fps     <th> fps Up-Sample      <th> fps Down-Sample   <th> Description
 * <tr><td> VIN fps       <td> VIN input     <td> Sensor fps    <td> No                 <td> No                <td> The same as sensor output fps.
 * <tr><td> RAW fps       <td> VIN output    <td> VIN fps       <td> No                 <td> Yes               <td> No larger than VIN fps, achieved by dropping frames periodically.
 * <tr><td> Channel fps   <td> IDSP input    <td> RAW fps       <td> Yes, up to 3.99x   <td> Yes               <td> No limit for down-sample rate.
 * <tr><td> Canvas fps    <td> IDSP output   <td> Channel fps   <td> No                 <td> Yes               <td> No limit for down-sample rate.
 * <tr><td> Pyramid fps   <td> IDSP output   <td> Channel fps   <td> No                 <td> No                <td> fps down-sample possible with pyramid manual feed.
 * <tr><td> Stream fps    <td> VDSP input    <td> Canvas fps    <td> No                 <td> Yes               <td> No limit for down-sample rate.
 * <tr><td> VOUT fps      <td> VOUT output   <td> Canvas fps    <td> Yes                <td> Yes               <td> Decided by the display configuration.
 * </table>
 *
 * @note
 * For frame rates across different stages, more descriptions / limitations are listed as follows：
 * - Each VIN / sensor can have a different fps.
 * - Each RAW (VIN output) can have a different fps.
 * - Each channel can have a different IDSP fps.
 * - Each canvas can have a different fps.
 * - When putting source buffers from different channels / passes into the same
 *   canvas, all these source buffers should have the same fps, which should
 *   be equal to the final canvas fps.
 *
 *
 * - - - -
 *
 * @section hp_fps 2. High Precision Frame Rate
 *
 * @subsection hp_fps_intro 2.1 Introduction
 * The image audio video (IAV) module introduces the feature of high precision fps to express VIN,
 * IDSP and canvas framerate. It is to support decimal fps like 0.5 or 7.5.  By default, this feature
 * is <b>disabled</b>. IAV can only support integral fps.
 *
 * High precision fps is expressed by "hp_fps = real_fps * 1000", where
 * hp_fps is high precision fps, real_fps is real fps.
 *
 * For example, "hp_fps = 500" represents 0.5 fps, "hp_fps = 7500" represents 7.5 fps.
 *
 * @subsection hp_fps_enable 2.2 Enable High Precison Frame Rate
 * There are two methods to enable high precision frame rate.
 *      - IOCTL: IAV_IOC_SET_SYSTEM_RESOURCE with "enable_hp_fps" member in struct iav_system_resource
 *      - Lua scripts as below:
 * @code
 * _resource_config_ = {
 *     version = 1,
 *     log_level = 0, -- 0: error; 1: warning; 2: info; 3: debug
 *     enable_hp_fps = 1 ,
 * ...
 * }
 * @endcode
 *
 * @subsection hp_fps_apply 2.3 Using High Precison Frame Rate
 * When this flag is enabled, IAV will accept a frame rate value from structure high precision member (with suffix
 * "_hp") not normal frame rate member.  The related structures show as below:
 * - iav_pyramid_cfg <B>(frame_rate, frame_rate_hp)</B>\n
 * Related IOCTL: @ref IAV_IOC_SET_PYRAMID_CFG, @ref IAV_IOC_GET_PYRAMID_CFG
 * - iav_canvas_fps <B>(frame_rate, frame_rate_hp)</B>\n
 * Related IOCTL: @ref IAV_IOC_GET_VIDEO_PROC, @ref IAV_IOC_CFG_VIDEO_PROC
 * - iav_canvas_cfg <B>(frame_rate, frame_rate_hp)</B>\n
 * Related IOCTL: @ref IAV_IOC_GET_SYSTEM_RESOURCE, @ref IAV_IOC_SET_SYSTEM_RESOURCE
 * - iav_chan_cfg <B>(idsp_fps, idsp_fps_hp)</B>\n
 * Related IOCTL: @ref IAV_IOC_GET_SYSTEM_RESOURCE, @ref IAV_IOC_SET_SYSTEM_RESOURCE
 * - iav_stream_fps <B>(abs_fps, abs_fps_hp)</B>\n
 * Related IOCTL: @ref IAV_IOC_SET_STREAM_CONFIG, @ref IAV_IOC_GET_STREAM_CONFIG
 *
 * @note
 * IAV will always report the frame rate to both high precision and normal frame rate member, whether the "high
 * precision enable" flag is enabled or not.  For example, when querying system resource through
 * @ref IAV_IOC_GET_SYSTEM_RESOURCE, users can always get valid values in the structure iav_chan_cfg
 * (idsp_fps = 30, idsp_fps_hp = 30000).
 *
 *
 * - - - -
 *
 * @section framerate_example 3. Frame Rate Examples
 *
 * @subsection example_fps1 Example 1: fps suggestion
 * This tool is used to query encode frame rate through the "fps suggestion" function, and obtain
 * the proper fps for the encoded stream for encoding.

 * The following example uses chip CV5S66.<br>
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /cv5_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua -A --smax 3840x2160 -h 3840x2160 -B --smax 3840x2160 -h 3840x2160 -C --smax 3840x2160 -h 3840x2160 --frame-factor 1/30 -D --smax 3840x2160 -h 3840x2160 -E --smax 3840x2160 -h 3840x2160 -S5 --smax 3840x2160 -h 3840x2160 --max-stream-num 6
 * board# test_fps_suggest -A -f 30 --> "-f 30" mean target fps for this stream
 * Suggested stream [0], fps [22]
 * Suggested stream [1], fps [22]
 * Suggested stream [2], fps [1]
 * Suggested stream [3], fps [22]
 * Suggested stream [4], fps [22]
 * Suggested stream [5], fps [21]
 * board# test_fps_suggest -A -f 30 -k 1 --> "-k 1" mean keep fps for this stream, "-f 30" mean target fps for this stream
 * Fixed stream [0], fps [30]
 * Suggested stream [1], fps [20]
 * Suggested stream [2], fps [1]
 * Suggested stream [3], fps [20]
 * Suggested stream [4], fps [20]
 * Suggested stream [5], fps [19]
 * board# test_fps_suggest -A -e 1 -B -e 1 -C -e 1 --> "-e 1" mean excldue currect stream
 * Suggested stream [0], fps [0]
 * Suggested stream [1], fps [0]
 * Suggested stream [2], fps [0]
 * Suggested stream [3], fps [30]
 * Suggested stream [4], fps [30]
 * Suggested stream [5], fps [30]
 * board# test_fps_suggest -V 8 -t 25 --> "-V 8" mean set vin ID, "-t 25" mean set input fps for the vin
 * Suggested stream [0], fps [25]
 * Suggested stream [1], fps [25]
 * Suggested stream [2], fps [22]
 * Suggested stream [3], fps [25]
 * Suggested stream [4], fps [25]
 * Suggested stream [5], fps [25]
 * @endcode
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /cv5_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua -A --smax 3840x2160 -h 3840x2160 -B --smax 3840x2160 -h 3840x2160 -C --smax 3840x2160 -h 3840x2160 --frame-factor 1/30 -D --smax 3840x2160 -h 3840x2160 -E --smax 3840x2160 -h 3840x2160 -S5 --smax 3840x2160 -m 3840x2160 --max-stream-num 6
 * board# test_fps_suggest -A -k 1
 * Fixed stream [0], fps [30]
 * Suggested stream [1], fps [26]
 * Suggested stream [2], fps [1]
 * Suggested stream [3], fps [26]
 * Suggested stream [4], fps [26]
 * Suggested stream [5], fps [21]
 * @endcode
 *
 * @subsection example_high_precision_fps Example 2: High Precision fps
 * This feature allows the user to set non-integer VIN fps. With "enable_hp_fps" option, the IAV can set arbitrary fps.
 * For more details, refer to <a href="script/vin0_4k_linear_hps.lua" target="_blank"><b>vin0_4k_linear_hps.lua</b></a>.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg vin0_4k_linear_hps.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_canvas_zero_fps Example 3: Canvas Zero fps
 *
 * See @ref example_runtime_update_canvas_fps for this feature.
 *
 * @subsection example_stream_abs_fps Example 4: Stream Absolute fps
 * When the VIN fps is changed, the user wants to keep the stream fps stable. With
 * `stream-abs-fps-enable` and `stream-abs-fps` options, stream fps can keep unchanged.
 *
 * @code
 * (terminal 1)
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3        // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3)   // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/local/bin/scripts/cv5_vin0_4k_linear.lua  --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -h 1080p -b 0 --stream-abs-fps-enable 1 --stream-abs-fps 15 -e  -> enable abs fps for stream A
 *
 * (terminal 2)
 * board# test_stream --no
 * .....
 * stream A:   4200 frames, 15.00 fps,          175975810      bytes,  4682 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4230 frames, 15.00 fps,          177176542      bytes,  4690 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4260 frames, 15.00 fps,          178390041      bytes,  4740 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4290 frames, 15.00 fps,          179574833      bytes,  4627 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4320 frames, 15.00 fps,          180785629      bytes,  4729 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4350 frames, 15.00 fps,          181990192      bytes,  4705 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4380 frames, 15.00 fps,          183177827      bytes,  4639 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4410 frames, 15.00 fps,          184383976      bytes,  4711 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4440 frames, 15.00 fps,          185569105      bytes,  4629 kbps, enc_pipe_time [ 1190:10145]
 * stream A:       4470 frames, 15.00 fps,          186767130      bytes,  4679 kbps, enc_pipe_time [ 1190:10145]
 * AVG FPS = 15.00 fps
 * .....
 *
 * @endcode
 *
 * Change the VIN fps, the stream fps is unchanged.
 *
 * @code
 * (terminal 1)
 * board# test_vin -S 0 -f 25
 *
 * (terminal 2)
 * .....
 * stream A:   1200 frames, 15.00 fps,           53554563      bytes,  5573 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1230 frames, 15.00 fps,           54921295      bytes,  5338 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1260 frames, 15.00 fps,           56216080      bytes,  5057 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1290 frames, 15.00 fps,           57500004      bytes,  5015 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1320 frames, 15.00 fps,           58759789      bytes,  4921 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1350 frames, 15.00 fps,           60013455      bytes,  4896 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1380 frames, 15.00 fps,           61239816      bytes,  4790 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1410 frames, 15.00 fps,           62462869      bytes,  4777 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1440 frames, 15.00 fps,           63690188      bytes,  4793 kbps, enc_pipe_time [ 1197: 8352]
 * stream A:       1470 frames, 15.00 fps,           64911792      bytes,  4771 kbps, enc_pipe_time [ 1197: 8352]
 * AVG FPS = 15.00 fps
 * .....
 *
 * @endcode
 *
 * @note
 * The IAV requests that the input fps cannot be smaller than stream abs fps. If the encoding input fps is smaller than the target fps,
 * the real fps of the encoding stream will be the same as the input fps.
 *
 *
 * - - - -
 *
 * @subsection example_raw_fps Example 5: RAW fps
 * Modify the Lua file for RAW fps, set VIN fps to 30, RAW fps and IDSP fps to 15:
 * @code
 * vsrc_0 = {
 *     ...
 *     fps = 30,
 *     ...
 * }
 * chan_0 = {
 *     ...
 *     raw_fps = 15,
 *     idsp_fps = 15,
 *     ...
 * }
 * @endcode
 *
 * The Lua script can be found at <a href="script/raw_fps.lua" target="_blank"><b>raw_fps.lua</b></a>.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3   // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)       // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg ./raw_fps.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_raw_fps_scale_roi_vin Example 6: Set different RAW fps for scale VIN and ROI VIN
 * Users can set different RAW fps for scale VIN and ROI VIN. Modify the Lua file:
 * @code
 * vsrc_0 = {
 *     ...
 *     mode = "3840x2160",
 *     fps = 30,
 *     scale_type = 1,
 *     roi_enable = 1,
 *     roi_list = {
 *     	  {
 *     	  	  roi_win = {0, 0, 0 ,0},
 *     	  },
 *     	  {
 *     	  	  roi_win = {0, 0, 1920 ,1080},
 *     	  },
 *     	  {
 *     	  	  roi_win = {960, 540, 1920 ,1080},
 *     	  },
 *     },
 *     ...
 * }
 * chan_0 = {
 *     ...
 *     vin_roi_idx = 0, -- use scale VIN
 *     raw_fps = 15,
 *     idsp_fps = 5,
 *     ...
 * }
 * chan_1 = {
 *     ...
 *     vin_roi_idx = 1, -- use roi VIN
 *     raw_fps = 25,
 *     idsp_fps = 25,
 *     ...
 * }
 * chan_2 = {
 *     ...
 *     vin_roi_idx = 2,  -- use roi VIN
 *     raw_fps = 30,
 *     idsp_fps = 20,
 *     ...
 * }
 * @endcode
 *
 * The Lua script can be found at <a href="script/cv72_scale_crop_vin_raw_fps.lua" target="_blank"><b>cv72_scale_crop_vin_raw_fps.lua</b></a>.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=0   // Scale VIN only supported on CV72 with VIN0.
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg ./cv72_scale_crop_vin_raw_fps.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection exampe_update_vin_fps Example 7: Update VIN fps on the fly
 * VIN framerate can be updated on the fly.
 * `test_vin` option "-f" is used to specify the new framerate, and option "S" is used to specify
 * vsrc_id when there are multi VINs.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3   // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)       // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/local/bin/scripts/cv5_vin0_4k_linear.lua  --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_vin -S 0 -f 25                                   // Update VIN framerate of vsrc 0 to 25
 * @endcode
 */
/*!
 * @file hdr.h
 * @brief
 * @version 0.1
 * @date 2021-12-21
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
 * @page fs_basic_hdr BASIC - HDR
 *
 * @section line_intlv_hdr 1. Line-Interleaved High Dynamic Range
 * Line-Interleaved high dynamic range (HDR) is also named as DOL HDR. In this HDR mode, sensor outputs multiple
 * sub-exposure frames to CV5x VIN controller in line-interleaved format. There are usually
 * dummy lines between two adjacent sub-exposure frames. Additionally the count of the dummy lines depends
 * on the maximum exposure time of middle or short sub-exposure frame.
 *
 * @subsection example_line_intlv_hdr1 Example 1. imx274_mipi 1080p30 2X HDR VIN mode.
 * @code
 * board # init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board # init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_hdr.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_hdr.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * @subsection example_line_intlv_hdr2 Example 2. imx274_mipi 5MP30 2X HDR VIN mode.
 * @code
 * board # init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board # init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_5m_2592x1944_hdr.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_5m_2592x1944_hdr.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * @subsection example_line_intlv_hdr4 Example 3. imx290_mipi 3X HDR + 1080p30 VIN mode.
 * @code
 * board # init.sh --na; modprobe imx290_mipi vinc_id=8 bus_id=3    // For CV5 or CV52
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\
 *                     --hdr-mode 2 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection example_dcg_hdr2 Example 4. imx678_mipi 2X HDR (DCG) + 3840x2160 VIN mode.
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx678_mipi vinc_id=8 bus_id=3 inck_mode=1      // For CV5 or CV52
 * board # modprobe imx678_mipi vinc_id=8 inck_mode=1               // For CV72
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg vin0_4k_dcg_hdr.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * board # test_encode -A -H 3840x2160 -b 0 -e
 * @endcode
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is as follows:
 * <a href="script/vin0_4k_dcg_hdr.lua" target="_blank"><b>vin0_4k_dcg_hdr.lua.lua</b></a>.
 *
 */
/*!
 * @file encode_mode.h
 * @brief
 * @version 1.0
 * @date 2022-04-18
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
 * @page fs_adv_enc_mode ADVANCED - Encode Mode
 *
 * @section section_encode_mode 1. Encode Mode
 *
 * There are several encoding modes in the CV5x / CV72 chips that provide different
 * functionalities and performances for various products. Although the CV5x / CV72
 * platform currently has fewer encoding modes than CV2x platform, additional
 * modes are expected to be released in later versions. For both the CV5x / CV72 and
 * CV2x chip series, the field of the encoding mode must be explicitly specified.
 *
 * @subsection mode_comparision 1.1 Comparison
 *
 * The following table lists the differences in functions for encode mode comparison.
 *
 * <table>
 * <caption id="table_enc_mode_comparison">Table 1-1. Encode Mode Comparison.</caption>
 * <tr><th> Function                  <th> Mode 0 <th> Mode 1 <th> Mode 5     <th> Mode 127
 * <tr><td> IQ in low light           <td> Good   <td> Good   <td> Excellent  <td> No
 * <tr><td> Single region LDC         <td> Yes    <td> No     <td> Yes        <td> No
 * <tr><td> EIS                       <td> Yes    <td> No     <td> Yes        <td> No
 * <tr><td> Multi-Region dewarp       <td> No     <td> Yes    <td> No         <td> No
 * <tr><td> HDR 2X                    <td> Yes    <td> Yes    <td> Yes        <td> No
 * <tr><td> HDR 3X                    <td> No     <td> No     <td> Yes        <td> No
 * <tr><td> Multi-VIN                 <td> Yes    <td> No     <td> Yes        <td> No
 * <tr><td> Multiple YUV input        <td> Yes    <td> Yes    <td> Yes        <td> No
 * <tr><td> Single-Color privacy mask <td> Yes    <td> Yes    <td> Yes        <td> No
 * <tr><td> Multi-Color privacy mask  <td> No     <td> No     <td> No         <td> No
 * </table>
 *
 * @note
 *   - For mode 0, the DSP pipeline latency is lower than mode 5.
 *   - Compared with mode 0/1, mode 5 has better image quality with better MCTF effects for low light conditions.
 *   - Mode 0 and mode 1 has the same image quality.
 *   - For mode 127, it is VIN only mode, and it is normally used for RAW data capture purpose.
 *
 * @subsection mode_normal_iso 1.2 Mode 0: Normal ISO Mode
 *
 * <table>
 * <caption id="table_normal_ISO">Table 1-2. Normal ISO Mode.</caption>
 * <tr><th> Feature		       <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Sensor Type	       <td> CFA / YUV Input
 * <tr><td> Main Buffer Size   <td> Width <= 8192
 * <tr><td> Stream Number      <td> Up to 20 streams
 * <tr><td> Feature Included   <td>
 * <ul>
 *    <li> All normal ISO features
 *    <li> Encoding
 *    <li> Overlay
 *    <li> Electronic image stabilization (EIS)
 *    <li> Single-Color privacy mask
 *    <li> Digital PTZ (type I and II)
 *    <li> Up to 3 layers SVC-T for H.264 and H.265
 *    <li> Capturing RAW / YUV / ME1 / ME0 data
 *    <li> High MPixel encoding (width > 1920)
 *    <li> Up to 4K 2X line interleaved HDR
 *    <li> MB level encode tools for H.264 and H.265
 *    <li> Frame sync mechanism
 *    <li> Lens distortion correction
 *    <li> Multi-VIN design
 *    <li> IDSP rotate / flip
 * </ul>
 * <tr><td> Feature Not Included  <td>
 * <ul>
 *    <li> Fisheye dewarping
 *    <li> Multi-Pass scalers
 *    <li> Fusion for RGB and IR channel
 *    <li> Fusion for RGB and thermal channel
 * </ul>
 * </table>
 *
 * @subsection mode_multi_region_warp 1.3 Mode 1: Multi-Region Warp
 *
 * <table>
 * <caption id="table_multi_region_warp">Table 1-3. Multi-Region Warp.</caption>
 * <tr><th> Feature		       <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Sensor Type	       <td> CFA / YUV Input
 * <tr><td> Main Buffer Size   <td> Width <= 4096
 * <tr><td> Stream Number      <td> Up to 20 streams
 * <tr><td> Feature Included   <td>
 * <ul>
 *    <li> All advanced ISO features
 *    <li> Encoding
 *    <li> Overlay
 *    <li> Single-Color privacy mask
 *    <li> Up to 3 layers of SVC-T for H.264 and H.265
 *    <li> Captures RAW / YUV / ME1 / ME0 data
 *    <li> High megapixel encoding (width > 1920)
 *    <li> MB level encode tools for H.264 and H.265
 *    <li> Frame sync mechanism
 *    <li> Fisheye dewarping
 *    <li> Digital PTZ (Type II) when the sub buffer is dewarped
 *    <li> Warp DPTZ for each region
 *    <li> Extra sharpen after Dewarp
 * </ul>
 * <tr><td> Feature Not Included  <td>
 * <ul>
 *    <li> Electronic image Stabilization (EIS)
 *    <li> 3X line interleaved HDR
 *    <li> Digital PTZ (type I and II)
 *    <li> Lens Distortion Correction
 *    <li> Fusion for RGB and IR channel
 *    <li> Fusion for RGB and thermal channel
 * </ul>
 * </table>
 *
 * Refer to @ref fs_adv_dewarp for more details and examples.
 *
 * @subsection mode_advanced_hdr 1.4 Mode 5: Advanced HDR
 *
 * <table>
 * <caption id="table_advanced_hdr">Table 1-4. Advanced HDR.</caption>
 * <tr><th> Feature		       <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Sensor Type	       <td> CFA / YUV Input
 * <tr><td> Main Buffer Size   <td> Width <= 8192
 * <tr><td> Stream Number      <td> Up to 16 streams
 * <tr><td> Feature Included   <td>
 * <ul>
 *    <li> All advanced ISO features
 *    <li> Encoding
 *    <li> Overlay
 *    <li> Electronic image stabilization
 *    <li> Single-Color privacy mask
 *    <li> Digital PTZ (type I and II)
 *    <li> Up to 3 layers SVC-T for H.264 and H.265
 *    <li> Capturing RAW / YUV / ME1 / ME0 data
 *    <li> High MPixel encoding (width > 1920)
 *    <li> Up to 4KP 3X line interleaved HDR
 *    <li> MB level Encode tools for H.264 and H.265
 *    <li> Frame sync mechanism
 *    <li> Lens distortion correction
 *    <li> Multi-VIN design
 *    <li> IDSP rotate/flip
 * </ul>
 * <tr><td> Feature Not Included  <td>
 * <ul>
 *    <li> Fisheye dewarping
 *    <li> Fusion for RGB and IR channel
 *    <li> Fusion for RGB and thermal channel
 * </ul>
 * </table>
 *
 * <br>
 *
 * @subsection mode_vin_only 1.5 Mode 127: VIN Only Mode
 *
 * <table>
 * <caption id="table_vin_only">Table 1-5. VIN Only Mode.</caption>
 * <tr><th> Feature		       <th> <div style="width:500px"><B>Description</B></div>
 * <tr><td> Sensor Type	       <td> CFA / YUV input
 * <tr><td> Main Buffer Size   <td> Width <= 8192
 * <tr><td> Feature Included   <td>
 * <ul>
 *    <li> Capturing RAW
 * </ul>
 * <tr><td> Features Not Included  <td>
 * <ul>
 *    <li> All normal ISO features
 *    <li> Encoding
 *    <li> Overlay
 *    <li> EIS
 *    <li> Single-color privacy mask
 *    <li> DPTZ (type I and II)
 *    <li> Stream rotation / flip
 *    <li> Up to three layers of SVC-T for H.264 and H.265
 *    <li> Capturing YUV / ME1 / ME0 data
 *    <li> High MPixel encoding (width > 1920)
 *    <li> Up to 4K 2x line-interleaved HDR
 *    <li> MB-level encode tools for H.264 and H.265
 *    <li> Frame sync mechanism
 *    <li> Lens distortion correction
 *    <li> 3x HDR with any resolution
 *    <li> Fisheye dewarping
 *    <li> Multi-pass scalers
 *    <li> IDSP rotate / flip
 *    <li> Multi-color privacy mask
 *    <li> Fusion for RGB and IR channels
 *    <li> Fusion for RGB and thermal channels
 * </ul>
 * </table>
 *
 * @note
 *  - This mode only captures data raw for use cases such as time of flight (ToF), Lidar, and others.
 *
 * <br>
 *
 * ---
 *
 * @section section_enc_mode_examples 2. Encode Mode Examples
 *
 * @subsection example_iso Example 1: Normal ISO mode example
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * @endcode
 *
 * @subsection example_hdr Example 2: Advanced HDR mode example
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 5        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 5)  // For CV72
 * @endcode
 *
 */
/*!
 * @file lua.h
 * @brief
 * @version 0.1
 * @date 2022-01-10
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
 * @page fs_adv_lua ADVANCED - Configure with Lua Script
 *
 * @section lua_lua 1. Introduction to Lua Configuration
 * For a specific product design, user applications must configure the various
 * resource and layout settings, including video input (VIN) (multi-VIN), canvas, stream, and video output (VOUT).
 * In order to make the parameters easier to parse, the Lua script file is introduced
 * as the configuration file for these resource and layout settings.  The Lua script improves the organization
 * of parameters and multi-VIN design options.
 * This Lua script format is an excellent reference for users to configure their own
 * implementation and file formats to organize these options.
 *
 * Generally, a Lua script is comprised of five main sections:
 *
 * <ul>
 *   <li> <B>Video source (VSRC) configuration:</B> Each sensor (either an RGB sensor, such as "IMX274", or
 *        a YUV input device, such as "Lt6911") is enumerated as a "VSRC" instance. In the
 *        Lua script, all sensor-related configurations are included in this section.
 *   <li> <B>Channel configuration:</B> A channel is an independent unit for the image digital signal processor (IDSP) to process
 *        image data generated by "VSRC" (sensor). Each channel possesses its own 3A
 *        parameters, including a different IDSP pipeline. It also has a set of source buffers
 *        (main / second / third /...) and its own Pyramid buffers. In the Lua script, all channel-related
 *        configurations are included in this section.
 *   <li> <B>Canvas configuration:</B> The canvas maintains the channels' source buffers.
 *        It can be either outputed through video output (VOUT) or encoded to streams. User applications
 *        can combine the field of view (FoV) of each channel's source buffer together into one canvas
 *        so that the stream encoded from this canvas can cover several FoVs from different
 *        VIN channels. Alternatively, each source buffer can have its own canvas.
 *   <li> <B>Stream configuration:</B> Canvases can be encoded as streams with various stream
 *        numbers and configurations. In the Lua script, all stream-related configurations are
 *        included in this section.
 *   <li> <B>Resource:</B> All configurations mentioned above will be collected into this section.
 * </ul>
 *
 * - - - -
 *
 * @section lua_vsrc_cfg 2. VSRC Configuration
 *
 * @subsection lua_vsrc_cfg_common 2.1 VSRC Common Configuration
 * <table>
 * <caption id="vsrc_cfg">Table 2-1. VSRC Common Configuration.</caption>
 * <tr><th align="left"> Item       <th align="left"> Description
 * <tr><td> <B>vsrc_id</B>          <td> Specify the sensor input ID. Ambarella suggests keeping the
 * same value as a sensor index, which is automatically generated during sensor driver probing and
 * corresponds to a real sensor
 * <tr><td> <B>vsrc_status</B>      <td> Specify if the sensor is active or broken / not connected
 * <tr><td> <B>mode</B>             <td> Specify the sensor resolutions
 * <tr><td> <B>hdr_mode</B>         <td> Specify the HDR mode or linear mode, such "linear", "2x", "3x" or wide dynamic range "wdr"
 * <tr><td> <B>fps</B>              <td> Specify the sensor framerate
 * <tr><td> <B>vsrc_ctx_switch</B>  <td> Enable vsrc_ctx by switching the VIN driver. It is required for some sensors,
 * such as AR0230 and AR0237, which can support multiple register groups of the shutter and active gain contol (AGC) (vsrc_ctx), but
 * must switch among them manually via the VIN driver
 * <tr><td> <B>bits</B>             <td> Specify the sensor RGB bits. 0 for AUTO, 8 ~ 16 for specified bits
 * <tr><td> <B>mirror</B>           <td> Specify the sensor mirror pattern. 0: none, 1: flip, 2: mirror, 3: mirror and flip, 255: AUTO
 * <tr><td> <B>bayer</B>            <td> Specify the sensor Bayer pattern. 0: RG, 1: BG, 2: GR, 3: GB, 255: AUTO
 * <tr><td> <B>scale_type</B>            <td> Specify the VIN scale type. 0: no scale, 1: 1/2 for both width and height,
 * 2: 1/4 for width and 1/2 for height, 3: 1/2 only for width, 4: 1/4 only for width, the default is 0.
 * <tr><td> <B>roi_enable</B>            <td> Flag to enable ROI VIN
 * <tr><td> <B>roi_list</B>            <td> Specifies the crop window of each ROI VIN
 * </table>
 *
 * <B>Example</B><br>
 * @code
 * vsrc_0 = {
 *    vsrc_id = 0,
 *    vsrc_status = 0,
 *    mode = "1080p",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 30,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 *
 * vsrc_1 = {
 *    vsrc_id = 1,
 *    vsrc_status = 0,
 *    mode = "3840x2160",
 *    hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *    fps = 30,
 *    bits = 0,
 *    vsrc_ctx_switch = 0,
 *    bits = 0,
 *    mirror = 0,
 *    bayer = 0,
 * }
 * @endcode
 *
 * <br>
 * @subsection lua_src_virtual_cfg 2.2 Custom Virtual VIN Mode Configuration
 * <table>
 * <caption id="virt_mode_cfg">Table 2-2. Custom Virtual VIN Mode Configuration.</caption>
 * <tr><th align="left"> Item       <th align="left"> Description
 * <tr><td> <B>width</B>
 *     <td> VSRC output window width
 * <tr><td> <B>height</B>
 *     <td> VSRC output window height
 * <tr><td> <B>hdr_mode</B>
 *     <td> Specify HDR mode for the virtual sensor
 * <tr><td> <B>default_fps</B>
 *     <td> Specify the default frame rate of the virtual sensor
 * <tr><td> <B>max_fps</B>
 *     <td> Specify the maximum frame rate of the virtual sensor
 * <tr><td> <B>bits</B>
 *     <td> Specify the virtual sensor RGB bits
 * <tr><td> <B>hdr_offset_long</B>
 *     <td> Line offset of the longest exposure frame
 * <tr><td> <B>hdr_offset_short1</B>
 *     <td> Line offset of the medium exposure frame
 * <tr><td> <B>hdr_offset_short2</B>
 *     <td> Line offset of the above-medium exposure frame
 * <tr><td> <B>hdr_offset_short3</B>
 *     <td> Line offset of the shortest exposure frame
 * <tr><td> <B>sensor_id</B>
 *     <td> Specify the sensor_id of the virtual sensor
 * <tr><td> <B>agc_db_step</B>
 *     <td> Specify the agc_db_step of the virtual sensor
 * <tr><td> <B>dual_gain_mode</B>
 *     <td> Flag to indicate if the current VIN supports dual-gain mode
 * <tr><td> <B>video_type</B>
 *     <td> Specify the virtual sensor video type
 * </table>
 *
 *<B>Example for Virtual VIN Mode Lua Configuration:</B><br>
 *
 * @code
 * virt_mode_cfg_0 = {
 *	 width = 1920,
 *	 height = 1080,
 *	 bits = 12,
 *	 max_fps = 30,
 *	 default_fps = 30,
 *	 hdr_mode = "linear",
 *	 video_type = "rgb_raw", -- options: "yuv_601", "yuv_656", "rgb_601", "rgb_656", "rgb_raw", "yuv_bt1120", "rgb_bt1120"
 *	 sensor_id = 0x3014,
 *	 agc_db_step = 0x00180000,
 * }
 *
 * vsrc_0 = {
 *	vsrc_id = 0,
 *	vsrc_status = 0,
 *	mode = "1080p",
 *	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *	fps = 30,
 *	vsrc_ctx_switch = 0,
 *	bits = 0,
 *	virt_mode_cfg_enable = 1,
 *	virt_mode_cfg = virt_mode_cfg_0,
 * }
 * @endcode
 *
 * - - - -
 *
 * @section lua_chan_cfg 3. Channel Configuration
 * <table>
 * <caption id="chan_cfg">Table 3-1. Channel Configuration.</caption>
 * <tr><th align="left"> Item       <th align="left"> Description
 * <tr><td> <B>id</B>                      <td> Specify the channel ID. Ambarella recommends that users keep
 * the same value as the channel index starting from zero
 * <tr><td> <B>vsrc</B>                    <td> Specify the channel VSRC. The content
 * must be declared before the channel definition in the Lua script
 * <tr><td> <B>idsp_fps</B>                <td> Specify the resample IDSP output framerate
 * <tr><td> <B>idsp_fps_locked_enable</B>  <td> Enable locking IDSP output framerate. If it is disabled, idsp_fps is
 * updated proportionally when the VIN framerate is changed at runtime. While it is enabled, idsp_fps will remain constant,
 * regardless of how the VIN framerate is changed
 * <tr><td> <B>vsrc_ctx</B>                <td> Specify the sensor register context of the VSRC
 * for the channel. It only functions for some sensors, such as AR0230, which support multiple register groups for
 * shutter and AGC
 * <tr><td> <B>use_vsrc_ctx_pattern</B>    <td> Specify if the IDSP splits the VIN frame into the current channel
 * according to its "vsrc_ctx_pattern"
 * <tr><td> <B>vsrc_ctx_pattern</B>        <td> Specify the data pattern, which is embedded in the first line of
 * sensor data
 * <tr><td> <B>vsrc_ctx_pattern_mask</B>   <td> Specify valid bits in "vsrc_ctx_pattern"
 * <tr><td> <B>sensor_ctrl</B>             <td> Tells the sensor driver which channel is allowed to configure the
 * shutter and AGC.  It is only used for special "IDSP virtual channel" cases
 * <tr><td> <B>img_stats_src_chan</B>      <td> Tells the 3A process which channel's statistics are used to perform
 * 3A control for the channel. It is used for multi-channel stitching and IDSP virtual channel cases
 * <tr><td> <B>app_img_profile</B>         <td> Specify 3A image profile mode. 0: IPC, 1: BWC, 2: ITS, 3: DVR, 4: DMS,
 * 5: ADAS, 6: OMC, 7: eMIRROR
 * <tr><td> <B>packing_mode_enable</B>     <td> Enable VIN packing mode only when VIN RAW compression is disabled
 * to save dynamic random-access memory (DRAM) bandwidth
 * <tr><td> <B>raw_capture</B>             <td> Enable capture of RAW data or RAW slice data from the RGB sensor. Users can get more
 * information from the help message of the unit test application, test_yucap
 * <tr><td> <B>ext_mem</B>                 <td> Enable RAW external memory
 * <tr><td> <B>raw_manual_feed</B>         <td> Enable RAW manual feed
 * <tr><td> <B>raw_feed_frame_num</B>      <td> Specify the RAW feed buffer number
 * <tr><td> <B>raw_cached_items</B>        <td> Specify the RAW cache buffer number. The system will not discard RAW data immediately
 * but place it in the cache buffer if raw_cached_items > 0. This provides users with a greater time margin to query it
 * <tr><td> <B>raw_slice_num</B>      <td> Specify the captured number of RAW slice data.
 * If raw_slice_num > 1, it will be enabled, and raw_slice_num should be in range [1, 8].
 * <tr><td> <B>raw_slice_cached_items</B>        <td> Specify the RAW slice cache buffer number. The
 * system will not discard RAW slice data immediately but place it in the cache buffer
 * if raw_slice_num > 1. This provides users with a greater time margin to query it
 * <tr><td> <B>y12_enable</B>              <td> Enable C2Y Y12 output
 * <tr><td> <B>y12_cached_items</B>        <td> Specify Y12 cached items for user to query with blocking call
 * <tr><td> <B>mctf_cmpr</B>               <td> Enable motion-compensated temporal filtering (MCTF) compression
 * <tr><td> <B>expo_num</B>                <td> Specify the DOLHDR exposure frames number
 * <tr><td rowspan="8"> <B>vcap_mode_flags</B> <td> Specify vcap_mode for each channel. The following are the vcap modes for different cases:
 * <tr>                                         <td> 0x00:  Advanced ISO mode. This is the mode for lowest latency from VIN to VOUT
 * <tr>                                         <td> 0x05:  Line-interleaved HDR mode. This is the mode for 3X HDR and multi-pass scale
 * <tr>                                         <td> 0x08:  Image Pipeline Only mode. This is the mode for EIS source channel
 * <tr>                                         <td> 0x09:  AI ISP mode. This is the mode for AI ISP
 * <tr>                                         <td> 0x0B:  Custom AI ISP mode. This is the mode for Custom AI ISP
 * <tr>                                         <td> 0x7F:  Mode none. This is the mode to skip ISP processing for current channel
 * <tr>                                         <td> 0x80:  Automatic mode. This flag enables vcap_mode_flags to follow encode_mode
 * <tr><td> <B>vsrc_region_num</B>         <td> Specify the total region number of the source sensor. Multiple
 * vsrc_region must be stored in line-interleaved format in sensor data
 * <tr><td> <B>vsrc_region_map</B>         <td> Specify region index map from which the current channel captures the sensor data
 * <tr><td> <B>enable_group</B>            <td> Enable channel grouping
 * <tr><td> <B>group_idx</B>               <td> Specify channel group index
 * <tr><td> <B>group_order_idx</B>         <td> Specify channel order idx inside the group with the group index "group_idx"
 * <tr><td> <B>group_sync</B>              <td> Enable group synchronization among channels of same group
 * Only valid when "group_enable" and "group_idx" are set
 * <tr><td> <B>reuse_src_chan_iso_cfg</B>  <td> Reuse ISO cfg from its source channel for current channel
 * <tr><td> <B>extra_iso_cfg</B>           <td> Specify the extra ISO cfg num for current channel
 * <tr><td> <B>lens_warp</B>               <td> Enable the lens distortion correction (LDC) function
 * <tr><td> <B>max_padding_width</B>       <td> Specify the padding width at C2Y stage (RAW processing stage) for LDC on this channel
 * It must function with the "lens_warp" option
 * <tr><td> <B>max_warp_input_width</B>    <td> Specify the maximum input width for dewarp
 * <tr><td> <B>max_warp_output_width</B>   <td> Specify the maximum output width for dewarp
 * <tr><td> <B>max_vwarp_wait_lines</B>    <td> Specify the waiting lines for vwarp
 * <tr><td> <B>max_vwarp_blk_height</B>    <td> Specify maximum vwarp block height for LDC use case
 * <tr><td> <B>rotate_cw</B>               <td> Enable 90-degree clockwise rotation
 * <tr><td> <B>hflip</B>                   <td> Enable horizontal flipping
 * <tr><td> <B>vflip</B>                   <td> Enable vertical flipping
 * <tr><td> <B>extra_downscale</B>         <td> Enable the large down-scale.  When the downscale ratio is larger than
 * or equal than 6X, it should be set to 1
 * <tr><td> <B>eis_delay_count</B>         <td> Specify electronic image stabilization (EIS) delay frame number before IDSP pipeline for each channel
 * <tr><td> <B>raw_src_chan</B>            <td> Specify RAW source channel for EIS channel. For EIS, it is implemented with dual channels
 * <tr><td> <B>c2y_burst_tile</B>          <td> Enable C2Y burst tile mode. By default, it is 1
 * <tr><td> <B>max_main_input_width</B>    <td> Specify the maximum main buffer input width. It can help the DSP
 * to allocate the proper resources from various cases.  It must be configured when the user application requires a
 * small main buffer input size (such as 720x480) with a large VIN size (such as 3840x2160). If it is set, the main
 * buffer input width cannot exceed it through the run-time update during Preview / Encoding
 * <tr><td> <B>slice_cfg_enable</B>        <td> Enable slice-related configurations
 * <tr><td> <B>slice_num</B>               <td> Specify the slice number at the Y2Y stage (YUV domain processing stage).
 * Only valid when "slice_cfg_enable" is enabled
 * <tr><td> <B>slice_width</B>             <td> Specify single-slice width at the Y2Y stage (YUV domain processing stage).
 * Only valid when "slice_cfg_enable" is enabled
 * <tr><td> <B>warp_padding_width</B>      <td> Specify the padding width for YUV data at the Y2Y stage
 * (YUV domain processing stage) when IDSP stitching is used. Only valid when "slice_cfg_enable" is enabled
 * <tr><td> <B>chan_input_src</B>          <td> Specify the channel input source. 0: RAW data, 1: CE data, 2: Low-resolution data
 * This parameter should be 0 for most cases. Only for EIS use cases; it can be 1 or 2 to improve IDSP performance
 * <tr><td> <B>idsp_core_cfg_enable</B>    <td> Enable IDSP dual-core configurations for this channel. By default, it is 0
 * <tr><td> <B>idsp_core_mode</B>          <td> Specify the IDSP core modes for this channel
 * Only valid when "idsp_core_cfg_enable" is enabled. 0: single-core 0, 1: single-core 1, 2: dual-cores
 * <tr><td> <B>pre_dec_enable</B>          <td> Enable decoding function before channel processing. Only enable it for decoding channel
 * <tr><td> <B>pre_dec_type</B>            <td> Specify the decoder type for the decoding. Only valid when pre_dec_enable is 1
 * <tr><td> <B>pass_num</B>                <td> Specify the pass number for which IDSP generates source buffers
 * <tr><td> <B>premain / main / second / third / fourth / fifth / sixth</B> <td> Specify the buffer output of each channel
 * <tr><td> <B>vin_roi_idx</B>             <td> Specify the index of ROI VIN.
 * Only valid when "roi_enable" in vsrc configuration is enabled.
 * <tr><td> <B>ver_slice_num</B>           <td> Specify the IDSP vertical slice number. Default is 1.
 * <tr><td> <B>raw_padding_height </B>     <td> Specify the padding height of the raw image. Default is 0.
 * </table>
 *
 * <B>Example</B><br>
 * @code
 * chan_0 = {
 *     id = 0,
 *     vsrc = vsrc_0,
 *     raw_capture = 1,
 *     vsrc_ctx = 0,
 *     img_stats_src_chan = "chan_0",
 *     sensor_ctrl = 1,
 *     max_padding_width = 0,
 *     idsp_fps = 0,
 *     lens_warp = 0,
 *     max_main_input_width = 0, -- 0: VIN raw width
 *     mctf_cmpr = 0,
 *     c2y_burst_tile = 1,
 *     extra_downscale = 0,
 *     main = {
 *         max_output = {0, 0}, -- output width
 *         input      = {0, 0, 0, 0}, -- full VIN
 *         output     = {0, 0, 1920, 1080},
 *     },
 *     second = {
 *         max_output = {0, 0}, -- output width
 *         input      = {0, 0, 0, 0}, -- full main
 *         output     = {0, 0, 720, 480},
 *     },
 *     third = {
 *         ... ... ...
 *     },
 *     fourth = {
 *         ... ... ...
 *     },
 *     fifth = {
 *         ... ... ...
 *     },
 *     pyramid = {
 *         input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
 *         scale_type = 0,		-- 0: 1/sqrt(2)	1: 1/2
 *         layer_map = 0x7F,
 *         layers = {
 *             {
 *                 crop_win = {0, 0, 0 ,0},
 *             },
 *             ... ... ...
 *         },
 *     },
 * }
 * @endcode
 *
 * @subsection lua_buf_cfg 3.1 Buffer Configuration
 * <table>
 * <caption id="buf_cfg">Table 3-2. Buffer Configuration.</caption>
 * <tr><th align="left"> Item       <th align="left"> Description
 * <tr><td> <B>max_output {width, height}</B>                 <td> Specify the maximum output width / height of each source buffer
 * <tr><td> <B>input {offset_x, offset_y, width, height}</B>  <td> Specify the input window of each source buffer. The main buffer input
 * window is cropped from sensor (VSRC) resolution, and other source buffer input windows are cropped from the main buffer output window
 * <tr><td> <B>output {offset_x, offset_y, width, height}</B> <td> Specify the output window of each source buffer in the canvas. The output
 * offset is in the canvas coordinate
 * </table>
 *
 * @code
 * chan_0 = {
 *     ... ... ...
 *     main = {
 *         max_output = {1920, 1080},
 *         input      = {0, 0, 1920, 1080},
 *         output     = {0, 0, 1920, 1080},
 *     },
 *     second = {
 *         ... ... ...
 *     },
 *     third = {
 *         max_output = {1920, 1080},
 *         input      = {0, 0, 960, 1080},
 *         output     = {960, 0, 960, 1080},
 *     },
 *     fourth = {
 *         ... ... ...
 *     },
 *     fifth = {
 *         ... ... ...
 *     },
 * }
 * @endcode
 *
 * <br>
 * @subsection lua_pyramid_cfg 3.2 Pyramid Configuration
 * <table>
 * <caption id="pyramid_cfg">Table 3-3. Pyramid Configuration.</caption>
 * <tr><th align="left"> Item       <th align="left"> Description
 * <tr><td> <B>input_buf_id</B> <td> Specify the input source buffer ID in this channel
 * <tr><td> <B>scale_type</B>   <td> Specify the pyramid layer scale ratio. 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size. When scale_type is 2,
 * the downscaling ratio between layer_0 and layer_1 can be arbitrary. The size of layer_1 is specified through <B>rescale_size {width, height}</B>.
 * While for the remaining layers, the downscaling ratio are fixed to 1/2
 * <tr><td> <B>ext_mem</B>      <td> Enable the external memory for pyramid buffers. It is 0 when the pyramid is from
 * DSP's internal buffer. When it is 1, the pyramid buffer pool is allocated by the IAV driver, and pyramid buffer
 * is automatically generated by DSP into the external pyramid buffer pool
 * <tr><td> <B>frame_rate</B>   <td> Specify the pyramid frame rate, it must be less than idsp_fps (This feature is not yet supported.)
 * <tr><td> <B>manual_feed</B>  <td> Enable manual-feed mode. 0: Pyramid auto-generation mode; 1: Pyramid manual-feed mode
 * <tr><td> <B>item_num</B>     <td> Specify the number of pyramid buffers in pyramid manual-feed mode. It must be within the range
 * of [4, 12]. When set to 0, it uses 6 as a default
 * <tr><td> <B>rescale_size {width, height}</B>     <td> Specify the size of layer_1 when <B>scale_type</B> is 2
 * <tr><td> <B>max_rescale_size {width, height}</B> <td> Specify the max size of layer_1
 * <tr><td> <B>layer_map</B>    <td> Specify which layers are not enabled to reduce DRAM bandwidth. To enable all seven layers, set this to 0x7F
 * <tr><td> <B>max_layer_map</B>    <td> Specify maximum bitmaps for pyramid layers, one bit for one layer. This can only be changed before entering
 *into preview. The "layer_map" must be within "max_layer_map"
 * <tr><td> <B>crop_win {offset_x, offset_y, width, height}</B> <td> Specify the output window of each pyramid layer buffer.
 * The default value {0,0,0,0} refers to the pyramid layer's active window without cropping, rather than the window with the size 0x0.
 * The cropping window of current layer will not affect latter layers
 * </table>
 *
 * <B>Example</B><br>
 * @code
 * pyramid = {
 *     input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
 *     scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size.
 *     ext_mem = 0,
 *     frame_rate = 0,
 *     manual_feed = 0,
 *     item_num = 0,
 *     layer_map = 0x7F,	-- 0: means disable all pyramid layers
 *     --[[For each pyramid layer, the input is always full sized from the specified source buffer. As well as the full sized pyramid is
 *         generated according to input source buffer size and the scale_type. The output pyramid is cropped from the full sized pyramid.
 *         Offset 0x0 with size 0x0 means the full pyramid output without cropping.
 *     --]]
 *     layers = {
 *     {
 *         crop_win = {0, 0, 0 ,0},
 *     },
 *     {
 *         crop_win = {0, 0, 0 ,0},
 *     },
 *     {
 *         crop_win = {0, 0, 0 ,0},
 *     },
 *     {
 *         crop_win = {0, 0, 0 ,0},
 *     },
 *     {
 *         crop_win = {0, 0, 0 ,0},
 *     },
 *     {
 *         crop_win = {0, 0, 0 ,0},
 *     },
 *     {
 *         crop_win = {0, 0, 0 ,0},
 *     },
 * },
 * @endcode
 *
 * - - - -
 *
 * @section lua_canvas_cfg 4. Canvas Configuration
 * <table>
 * <caption id="canvas_cfg">Table 4-1. Canvas Configuration.</caption>
 * <tr><th align="left"> Item       <th align="left"> Description
 * <tr><td> <B>type</B>             <td> Specify the canvas type. It can be either "encode" or "prev". There is no "off" type for canvas
 * If the application must turn off the canvas, it has to reconfigure the system and remove the canvas definition. If the canvas type is previewed,
 * it can be in either YUV422 or YUV420 format with UV-interleaved data. If the canvas type is encoded, it must be in YUV420 format with UV-interleaved data
 * <tr><td> <B>size {width, height}</B> <td> Specify the canvas resolution
 * <tr><td> <B>source</B>           <td> Specify source buffers of channels to canvas. The DSP follows the source buffer declare order in order to
 * place a channel source buffer data in this field. The latter source buffer is placed in with a higher Z order and may cover the source buffer with
 * a lower Z order. The channels whose source buffer are placed into the same canvas must have the same "idsp_fps"
 * <tr><td> <B>extra_dram_buf</B>   <td> Specify extra DRAM frames for the canvas
 * <tr><td> <B>vout_id</B>          <td> Specify VOUT when canvas type is "prev". If the value is set to 1, VOUT1 (such as high-definition multimedia interface (HDMI®) or composite video with blanking and sync (CVBS)) will be
 * used to show preview canvas. If the value is set to 0, VOUT0 (such as LDC or DSI) will be used to show the preview canvas
 * <tr><td> <B>vout_YUV422</B>      <td> Specify YUV format when the canvas type is "prev". If the value is set to 1, its YUV format is YUV422.
 * Then, VOUT captures the display data from it directly.  If the value is set to 0, its YUV format is YUV420, which is
 * the same as other "encode" type canvases.  Then, VOUT will convert it to YUV422 before showing
 * <tr><td> <B>vout_back_pressure_margin</B>   <td> Specify the current VOUT input FIFO depth. Valid range is [0,3]. 0 means using the default value 2.
 * <tr><td> <B>manual_feed</B>      <td> Enable manual-feed mode.  0: Canvas auto-generation mode. 1: Canvas manual-feed mode
 * <tr><td> <B>feed_frame_num</B>   <td> Specify the number of canvas buffers in manual-feed mode. It must be within the range
 * of [4, 12].  When set to 0, it uses 6 as a default
 * <tr><td> <B>cached_items</B>     <td> Specify the canvas cache buffer number. The system will not discard canvas data immediately
 *                                       but place it in the cache buffer if cached_items > 0. This provides users with a greater time margin to query it
 * <tr><td> <B>enc_dummy_latency</B><td> Specify the latency number of the encode dummy buffer
 * <tr><td> <B>frame_rate</B>       <td> Specify the canvas frame rate; it must be less than idsp_fps
 * <tr><td> <B>zero_fps</B>         <td> Enable 0 fps canvas frame rate. When set to 0, "frame_rate = 0" represents idsp_fps.
 *                                       When set to 1, "frame_rate = 0" is real 0 fps
 * <tr><td> <B>set_min_unlocked_buf_num</B>  <td> Enable set min_unlocked_buf_num config. 1: Enable. 0: Disable
 * <tr><td> <B>min_unlocked_buf_num</B>      <td> Specify minimum number of Pyramid unlocked buffers. When users want to set min_unlocked_buf_num accordingly,
 *                                                they must enable manual_feed and set_min_unlocked_buf_num first
 * <tr><td> <B>disable_yuv_dram</B> <td> Enable DSP to allocate the canvas YUV buffer, which is used to save memory
 *                                       when users have such requirements. 0 (Default): Allocate buffer. 1: Do not allocate buffer
 * <tr><td> <B>enable_frame_tag</B> <td> Enable canvas frame tag pattern feature
 * <tr><td> <B>frame_tag_value</B>  <td> Specify canvas frame tag value. This value is valid when enable_frame_tag flag is enabled
 * <tr><td> <B>frame_tag_mask</B>   <td> Specify canvas frame tag mask. This value is valid when enable_frame_tag flag is enabled
 * <tr><td> <B>ext_mem</B>          <td> Enable the external memory for the canvas YUV data
 * <tr><td> <B>blend_stitch_type</B>         <td> Specify the blend stitch type for this canvas when multiple-channel stitching is used.
 * 0: No stitch blending. 1: Horizontal stitch blending. 2: Vertical stitch blending
 * <tr><td> <B>blend_stitch_circular_margin</B>         <td> Specify The overlap margin of the last channel and first channel. Only valid when "blend_stitch_type" isn't 0
 * <tr><td> <B>blend_warp_enable</B>         <td> Enable H warp for blending overlap region. Only valid when "blend_stitch_type" isn't 0
 * <tr><td> <B>blur_enable</B>      <td> Enable blur insertion into the canvas. This is only for canvases whose type is "encode"
 * <tr><td> <B>max_blur_area_num</B>         <td> Maximum possible blur areas to insert. Valid range is [0, 8]. 0 means using the default value 8
 * <tr><td> <B>enc_extra_padding_enable</B>  <td> Enable extra padding for streams encoding with offset. 1 : Enable. 0 : Disable
 * <tr><td> <B>low_delay_enable</B>          <td> This is a flag to enable / disable canvas low delay output with multiple vertical slices enabled. Default is 0.
 * </table>
 *
 * <B>Example</B><br>
 * @code
 * canvas = {
 *     {
 *         type = "encode",
 *         size = {1920, 1080},
 *         source = {"chan_0.main", "chan_1.main", },
 *         extra_dram_buf = 0,
 *     },
 *     {
 *         type = "prev",
 *         size = {1920, 1080},
 *         source = {"chan_0.third", "chan_1.third", },
 *         vout_id = 1,
 *         vout_YUV422 = 0,
 *         vout_back_pressure_margin = 3,
 *         extra_dram_buf = 0,
 *     },
 * }
 * @endcode
 *
 * - - - -
 *
 * @section lua_stream_cfg 5. Stream Configuration
 * <table>
 * <caption id="stream_cfg">Table 5-1. Stream Configuration.</caption>
 * <tr><th align="left"> Item       <th align="left"> Description
 * <tr><td> <B>id</B>               <td> Specify the stream ID. Ambarella recommends keeping the same value as the stream index (starting from zero)
 * <tr><td> <B>max_size</B>         <td> Specify the maximum stream resolution
 * <tr><td> <B>max_M</B>            <td> Specify the maximum group of pictures (GOP) M for the stream. For B frames, max_M > 1. For MJPEG encoding, max_M = 0
 * <tr><td> <B>fast_seek_enable</B> <td> Enable the Fast Seek frame
 * <tr><td> <B>two_ref_enable</B>   <td> Enable two forward reference frames
 * <tr><td> <B>max_svct_layers_minus_1</B>   <td> Specify maximum scalable video coding (SVC-T) layers options. 0: No SVC-T. 1: Two-layer SVC-T
 * <tr><td> <B>max_num_minus_1_ltrs</B>      <td> Specify the maximum long-term number minus 1
 * <tr><td> <B>possible_enc_src_map</B>      <td> Specify the encoding source canvas map for the encoding stream. 0 (default): all canvases. Users
 * should specify when the stream will be encoded with advanced GOP. Advanced GOP requires more memory resources to be allocated for the source
 * canvases. By default, DSP allocates memory resources for all canvases. Specifying the designated source canvases can save memory
 * <tr><td> <B>codec_enable</B>     <td> Enable the stream codec. 0: High-efficiency video coding (HEVC) / H.264 / MJPEG; 1: HEVC / MJPEG; 2: H.264 / MJPEG; 3: MJPEG only
 * <tr><td> <B>efm_enable</B>       <td> Specify if the current stream can run encode from memory (EFM)
 * <tr><td> <B>efm_buf_num</B>      <td> Specify the number of frame buffers allocated for EFM. These frame buffers are allocated by DSP and occupy extra memory
 * <tr><td> <B>efm_size</B>         <td> Specify the EFM frame buffer size
 * <tr><td> <B>efm_skip_waiting</B> <td> Enable skip waiting for DSP's response when starting / stopping EFM streams
 * <tr><td> <B>efm_extern_src_enable</B>     <td> Enable sharing EFM buffers from other streams
 * <tr><td> <B>efm_ext_mem</B>      <td> Enable external memory as the EFM stream input
 * <tr><td> <B>stream_mv_statis_enable</B>   <td> Enable stream motion vector statistics
 * <tr><td> <B>stream_pic_statis_enable</B>  <td> Enable stream frame encoding information statistics
 * <tr><td> <B>custom_sei_possible</B>       <td> Specify if the current stream can insert custom SEI
 * <tr><td> <B>custom_sei_buf_num</B>        <td> Specify the custom sei buffer number in one stream custom sei buffer pool and
 * only used when custom_sei_possible is 1.
 * <tr><td> <B>custom_sei_data_max_size</B>  <td> Specify the maximum data size (bytes) for custom sei, which is used for allocating memory in DSP and iav driver.
 * </table>
 *
 * <B>Example:</B><br>
 * @code
 * stream_0 = {
 *     id = 0,
 *     max_size = {1920, 1080},
 *     max_M = 1,
 *     fast_seek_enable = 0,
 *     two_ref_enable = 0,
 *     max_svct_layers_minus_1 = 0,
 *     max_num_minus_1_ltrs = 0,
 *     possible_enc_src_map = 0,
 *     codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
 *     efm_enable = 0,
 *     efm_buf_num = 0,
 *     efm_size = {0, 0},
 *     efm_skip_waiting = 0,
 *     efm_extern_src_enable = 0,
 *     efm_extern_src_stream = 0,
 *     stream_mv_statis_enable = 0,
 *     stream_pic_statis_enable = 0,
 *     custom_sei_possible = 1,
 *     custom_sei_buf_num = 8,
 *     custom_sei_data_max_size = 256,
 * }
 * @endcode
 *
 * - - - -
 *
 * <B>Typical Structure of Lua Configuration File:</B><br>
 * @code
 * -- vsrc configuration
 * vsrc_0 = {
 *         vsrc_id = 1,
 *         mode = "1080p",
 *         hdr_mode = "linear", -- options: "linear", "2x", "3x" or "wdr"
 *         fps = 30,
 *         bits= 0,
 * }
 * ...
 *
 * -- channel configuration
 * chan_0 = {
 *         id = 0,
 *         vsrc = vsrc_0,
 *         ...
 *         main = {
 *                 max_output = {0, 0},             -- output width
 *                 input      = {0, 0, 0, 0},       -- full VIN
 *                 output     = {0, 0, 1920, 1080},
 *         },
 *         ...
 *         pyramid = {
 *                 input_buf_id = 4,  -- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
 *                 scale_type = 0,    -- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
 *                 ...
 *                 },
 *         },
 * }
 * ...
 *
 * -- stream configuration
 * stream_0 = {
 *         id = 0,
 *         max_size = {1920, 1080},
 *         max_M = 1,
 *         fast_seek_enable = 0,
 *         two_ref_enable = 0,
 *         max_svct_layers_minus_1 = 0,
 *         max_num_minus_1_ltrs = 0,
 *         codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
 * }
 * ...
 *
 * -- system resource
 * _resource_config_ = {
 *         version = 1,
 *         log_level = 0,               -- 0: error; 1: warning; 2: info; 3: debug
 *         channels = {
 *                 chan_0,
 *         },
 *         chan_groups = {
 *                {"chan_0",},         -- group index 0
 *         },
 *         canvas = {
 *                 {
 *                         type = "encode",
 *                         size = {0, 0},        -- min size to contain source buffers
 *                         source = {"chan_0.main",},
 *                         extra_dram_buf = 0,
 *                 },
 *                 ...
 *                 {
 *                         type = "prev",
 *                         size = {0, 0},
 *                         source = {"chan_0.third", },
 *                         vout_id = 1,
 *                         extra_dram_buf = 0,
 *                 },
 *         },
 *         streams = {
 *                 stream_0,
 *                 stream_1,
 *                 stream_2,
 *         },
 * }
 *
 * return _resource_config_
 * @endcode
 *
 * - - - -
 *
 * @section lua_vout_cfg 6. VOUT Configuration
 * There are three VOUT controllers in the CV5x / CV72 SoC. The VOUT Lua is required to correctly set up the VOUT controller.
 * | ITEM                 | Description |
 * | :----------------    | :---------- |
 * | <B>status</B>               | Selection: 0: Disable, 1: on, 2: off, 3: reset;<br> disable: do not use this VOUT controller |
 * | <B>mode</B>                 | Specify VOUT format, such as "1080i" or "720p" |
 * | <B>input_yuv422</B>         | Specify if the input YUV format is YUV422 |
 * | <B>video_output_window</B>  | Specify the output window in the format {offset_x, offset_y, output_width, output_heigh} |
 * | <B>type</B>                 | Specify the valid VOUT type for each controller |
 * | <B>hdmi_output_format</B>   | Specify the data format for HDMI output. This is valid when the type is "hdmi" or "cvbs" |
 * | <B>vout_from_image</B>      | Specify the flag for VOUT from the image |
 * | <B>default_image_format</B> | Specify the default image format. This is valid when VOUT from the image is enabled |
 * | <B>video_rotate</B>         | Specify the flag for enabling rotation for VOUT |
 * | <B>video_flip_mode</B>      | Specify the flip mode for VOUT; "no": disable, "h": horizontal, "v": vertical, "hv": horizontal + vertical |
 * | <B>own_mixer</B>            | Specify if the VOUT controller has a mixer |
 * | <B>osd_output_window</B>    | Specify the onscreen display (OSD) output window of {offset_x, offset_y, output_width, output_heigh} |
 * | <B>osd_flip_mode</B>        | Specify the flip mode for OSD; "no": disable, "h": horizontal, "v": vertical, "hv": horizontal + vertical |
 * | <B>osd_rescaler</B>         | Specify the flag to enable the OSD rescaler |
 * | <B>osd_rescaler_output_window</B> | Specify the OSD rescaler window of {offset_x, offset_y, output_width, output_heigh} |
 * | <B>osd_transparent_color_enable</B> | Specify if the OSD rescaler tranparent color is enabled or not |
 * | <B>max_osd_bit_depth</B>    | Specify the max OSD bit depth: 0: auto, 8: 8bits, 16: 16bits, 32: 32bits |
 *
 * Example:
 * @code {.c}
 * vout_2 = {
 *      status = "on",                                  --selection: 0:disable, 1:on, 2:off, 3:reset
 *                                                      --disable: do not use this vout controller
 *                                                      --on: use this vout controller and enable video display
 *                                                      --off: use this vout controller and disable video display
 *                                                      --reset: reset this vout controller
 *      mode = "1080p",
 *      input_yuv422 = "yes",
 *      video_output_window = {0, 0, 1920, 1080},       --{offsetx, offsety, output_width, output_heigh}
 *
 *      type = "hdmi",                                  --selection: hdmi, mipi_csi, cvbs
 *
 *      hdmi_output_format = "rgb";                     --selection: 0:rgb, 1:yuv422, 2:yuv444
 *                                                         --only for hdmi output mode
 *      vout_from_image = "disable",
 *      default_img_format = "yuv422",                  --selection: 0:yuv422, 1:yuv420
 *
 *      video_rotate = "no",                            --selection: 0:no, 1:yes
 *      video_flip_mode = "no",                         --selection: 0:no, 1:hv, 2:h, 3:v
 *
 *      own_mixer = "yes",                              --selection: 0:no, 1:yes
 *
 *      osd_output_window = {0, 0, 0, 0},               --{offsetx, offsety, output_width, output_heigh}
 *      osd_flip_mode = "no",                           --selection: 0:no, 1:hv, 2:h, 3:v
 *      osd_rescaler = "disable",                       --selection: 0:disable, 1:enable
 *      osd_rescaler_output_window = {0, 0, 0, 0},      --{offsetx, offsety, output_width, output_heigh}
 * }
 * @endcode
 *
 * - - - -
 *
 * @section section_lua_example 7. Lua Script Examples
 *
 * @subsection example_lua1 Example 1: Single VIN with 1080p30 Input
 *
 * @par Hardware and Software Environment
 *
 * In order for this test case to function, users must perform the following:
 *  - Insert the input sensor IMX274 with a mobile industry processor interface (MIPI®) into the VIN0 slot.
 *  - Connect the EVK board to PC via a universal asynchronous receiver / transmitter (UART) and Ethernet interface.
 *  - Connect a monitor to the HDMI interface.
 *
 * @image html example_lua1.png "Figure 7-1. Single VIN Hardware Connection."
 *
 * @par Overview of the System Resources
 *
 * The following diagram is an overview of system resources for the current case. For more details,
 * users can refer to the following Lua source file, which is located in
 *
 * <em>
 * /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua or /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua
 * </em>
 *
 * @image html lua_1080p_linear.png "Figure 7-2. Lua Configuration for Single VIN with 1080p Input."
 *
 * First, initialize the EVK board to load the essential drivers and microcode, and start 3A
 * statistics if the following command was not executed previously.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * @endcode
 *
 * Set up the system resources with the Lua script.
 * @code
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * @endcode
 *
 * Then, set up three streams. Stream_0's encoding format is H.265, encoded from canvas 0.
 * Stream_1's encoding format is H.264, encoded from canvas 3. Stream_2's encoding
 * format is MJPEG, encoded from canvas 2.
 *
 * @code
 * board# test_encode -A -H 1080p -b 0 -e\
 *                    -B -h 1080p -b 3 -e\
 *                    -C -m  480p -b 2 -e
 * @endcode
 *
 */
/*!
 * @file doc_sys_faq.h
 * @brief
 * @version 1.0
 * @date 2022-08-02
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
 * @page fd_adv_multi_vin ADVANCED - Multi-VIN & Multi-Channel
 *
 * @section multi_vin_design_overview 1. Overview
 *
 * This document provides guidelines for the system and software design of multi-video input
 * (VIN) channels, as well as implementation using the Ambarella CV5x / CV7x Flexible Linux Software
 * Development Kit (SDK).<br>
 *
 * Ambarella assumes that readers of this document have previously read and worked through the
 * steps outlined in the Getting Started Guide document of the Ambarella CV5x / CV7x Flexible Linux
 * Evaluation Kit (EVK).<br>
 *
 * This chapter includes the following sections:<br>
 *
 *   - Section @ref multi_vin_design_key_updates
 *   - Section @ref multi_vin_design_uses_of_multi_vin
 *   - Section @ref multi_vin_design_third_party_serdes_chips
 *   - Section @ref multi_vin_design_reference_kit
 *
 * @subsection multi_vin_design_key_updates 1.1 Key Updates
 *
 * <table>
 * <caption id="key_updates_for_each_sdk_version">Key Updates</caption>
 * <tr><th> SDK Version <th> Date <th> Modification
 * <tr><td align="center"> 0.2
 *     <td align="center"> 20190816
 *     <td>
 *         - Revised for the CV5x Chip family
 * <tr><td align="center"> 0.2.2
 *     <td align="center"> 20211210
 *     <td>
 *          - Added Section @ref multi_vin_design_dual_sensors_with_different_modes_from_single_serdes <br>
 *          - Added Section @ref multi_vin_design_sensors_with_a_serdes_bridge <br>
 *          - Added Section @ref multi_vin_design_dual_sensors_with_different_modes_from_max9296 <br>
 * <tr><td align="center"> 0.5
 *     <td align="center"> 20220114
 *     <td>
 *          - Added Section @ref multi_vin_design_dual_channels_from_a_single_sensor_and_raw_data <br>
 *          - Added Section @ref multi_vin_design_dual_channels_from_a_single_sensor_with_dual_vsrc_ctx <br>
 *          - Added Section @ref multi_vin_design_single_sensor_with_a_dual_vsrc_ctx <br>
 *          - Updated Section @ref multi_vin_design_vsrc_to_channel <br>
 *          - Added Section @ref multi_vin_design_dual_channels_from_the_sensor_and_the_yuv_raw_data <br>
 *          - Added Section @ref multi_vin_design_dual_channels_from_imx264_with_dual_vsrc_ctx <br>
 *          - Added Section @ref multi_vin_design_multiple_yuv_input <br>
 * <tr><td align="center"> 1.0
 *     <td align="center"> 20220415
 *     <td>
 *          - Added Section @ref multi_vin_design_cv52_multi_vin_design_kit <br>
 *          - Updated Section @ref multi_vin_design_quad_sensors_with_a_long_cable_through_max9296_4_1 <br>
 * </table>
 *
 * @note
 * The SDK versions listed in the above table reflect the current SDK version (x.x) or patch
 * release (x.x.x). A patch number that is not sequential indicates that the previous patch
 * release did not apply to this document.<br>
 *
 * @subsection multi_vin_design_uses_of_multi_vin 1.2 Uses of Multi-VIN
 *
 * Most cameras come with a single VIN and sensor input equipped with a limited view and one lens,
 * which is either a fixed or zoom lens. However, new market standards require more sophisticated
 * cameras, such as those that include a wider viewfinder, multi-view stitching, and dual-view
 * capabilities (to spare the expense of dual cameras).<br>
 *
 * To perform these tasks, current camera products use either a field-programmable gate array (FGPA)
 * to stitch multiple sensor inputs into one picture, then feed them into the system on chip (SoC),
 * or come with multiple SoCs.  With multiple SoCs, the camera controls multiple sensor inputs separately,
 * and then stitches the video clips together using back-end decoding devices. However, these methods
 * fail to meet all requirements of a multi-VIN design.<br>
 *
 * To address these challenges, CV5x / CV7x support multiple independent sensors as multi-channel
 * inputs (up to eight channels can be supported), as the CV5x /CV7x families of chips come equipped
 * with more than one VIN controller. Using serializer / deserializer (SERDES) chips, such as
 * the MAX9286 and MAX9296 from MAX, can support the multi-VIN design on CV5x / CV7x. CV5x /CV7x support
 * independent automatic exposure (AE) / automatic white balance (AWB) / automatic focus (AF)
 * (3A) control processes for each VIN.  CV5x / CV7x encode different streams, using various parameters
 * from each VIN, such as the frame rate, bit rate, and resolution. This enables the camera to
 * function as if there are multiple independent cameras running within a single SoC. The following
 * table lists the number of VIN controllers and the supported sensors for each chip in the CV5x / CV7x
 * family.<br>
 *
 * <table>
 * <caption id="number_of_vin_controllers_and_supported_sensors">Number of VIN Controllers and Supported Sensors.</caption>
 * <tr><th> SoC <th> VIN Controllers <th> Supported Independent Sensors <th> Supported Sensors (via SERDES) <th> Cameras
 * <tr><td align="center"> CV5x
 *     <td align="center"> 14
 *     <td align="center"> 4
 *     <td align="center"> up to 8
 *     <td align="center"> 2 - 8
 * <tr><td align="center"> CV7x
 *     <td align="center"> 10
 *     <td align="center"> 3
 *     <td align="center"> up to 6
 *     <td align="center"> 2 - 6
 * </table>
 *
 * Ambarella CV5x / CV7x also support the multi-VIN design for synchronizing super-wide angle views and
 * 180° / 360° panoramic views.  Synchronizing sensors is simple to perform because all sensor logic
 * comes from the same SoC.<br>
 *
 * Because of its many features, the Ambarella CV5x / CV7x multi-VIN design support several new camera models,
 * such as the ATM camera, the super-wide-angle camera, and multiple cameras (with a long cable) shooting
 * different views.<br>
 *
 * @subsection multi_vin_design_third_party_serdes_chips 1.3 Third-Party SERDES Chips
 *
 * Using third-party SERDES chips, CV5x / CV7x can support additional sensors for multi-VIN designs. The following
 * describes third-party deserializers and highlights the serializers that provide a bridge between the
 * remote sensors and the deserializers.<br>
 *
 *   - The <B>MAX9296</B> deserializer receives the full high definition (FHD) video from up to two
 *     gigabit multimedia serial link (GMSL) serializers (such as MAX9295) through coaxial cables
 *     (up to 15 meters long).  Each GMSL serializer connects to a single sensor.<br>
 *   - <B>MAX9295:</B> This chip serves as a bridge between the remote sensor and MAX9296. It captures
 *     and serializes sensor data from a remote sensor before transmitting to MAX9296.<br>
 *
 * @note
 *   - In order to maintain synchronization, the sensors connected to the same SERDES must have exactly
 *     the same resolution, frames per second (fps), and clock settings.
 *
 * @subsection multi_vin_design_reference_kit 1.4 Reference Kit
 *
 * The Ambarella CV5x / CV7x multi-VIN design kit enable developers to quickly create a line of differentiated
 * multi-VIN products. This section shows the multi-VIN design kits for the chips in the CV5x / CV7x families.<br>
 *
 * @subsubsection multi_vin_design_cv5_multi_vin_design_kit 1.4.1 CV5 Multi-VIN Design Kit
 *
 * CV5 supports 4x native VIN controllers.  Through the mobile industry processor interface (MIPI®)
 * virtual channel, it can be extended to 14x VIN controllers.  CV5 can support various VIN interfaces
 * including MIPI D/C-PHY, scalable low-voltage signaling (SLVS), and SLVS with embedded clock (SLVS-EC).
 * MIPI and SLVS-EC interfaces can be up to 16 lanes.  SLVS interface can be up to eight lanes.
 * The following table lists various Ambarella VIN controller layouts.<br>
 *
 * <table>
 * <caption id="cv5_vin_controller_layout">CV5 VIN Controller Layout.</caption>
 * <tr><th> VIN Slot <th> I2C Bus ID <th> VIN Controller ID <th> Type
 * <tr><td align="center" rowspan="6"> SLVS + DPHY
 *     <td align="center" rowspan="6"> 3/4
 *     <td align="center"> 8
 *     <td align="center"> Real
 * <tr><td align="center"> 9
 *     <td align="center"> Virtual
 * <tr><td align="center"> 10
 *     <td align="center"> Virtual
 * <tr><td align="center"> 11
 *     <td align="center"> Real
 * <tr><td align="center"> 12
 *     <td align="center"> Virtual
 * <tr><td align="center"> 13
 *     <td align="center"> Virtual
 * <tr><td align="center" rowspan="4"> SLVS - EC
 *     <td align="center" rowspan="4"> 5
 *     <td align="center"> 0
 *     <td align="center"> Real
 * <tr><td align="center"> 1
 *     <td align="center"> Virtual
 * <tr><td align="center"> 2
 *     <td align="center"> Virtual
 * <tr><td align="center"> 3
 *     <td align="center"> Virtual
 * <tr><td align="center" rowspan="3"> DCPHY 0
 *     <td align="center" rowspan="3"> 5
 *     <td align="center"> 0
 *     <td align="center"> Real
 * <tr><td align="center"> 1
 *     <td align="center"> Virtual
 * <tr><td align="center"> 2
 *     <td align="center"> Virtual
 * <tr><td align="center"> DCPHY 0 (Cont'd)
 *     <td align="center">
 *     <td align="center"> 3
 *     <td align="center"> virtual
 * <tr><td align="center" rowspan="4"> DCPHY 1
 *     <td align="center" rowspan="4"> 1
 *     <td align="center"> 4
 *     <td align="center"> Real
 * <tr><td align="center"> 5
 *     <td align="center"> Virtual
 * <tr><td align="center"> 6
 *     <td align="center"> Virtual
 * <tr><td align="center"> 7
 *     <td align="center"> Virtual
 * </table>
 *
 * Currently, CV5x supports a two to four multiple-VIN design through SERDES with the SLVS + DPHY VIN slot.
 * The sensors must support a four-lane interface through either MIPI or SLVS.  The following figure shows
 * the sensor boards inserted into the SLVS + DPHY VIN slot on the CV5 Timn board.<br>
 *
 * @image html single_sensor_board_plug_in_the_cv5_timn_board.png "Single Sensor Board Plug in the CV5 Timn Board."
 *
 * @subsubsection multi_vin_design_cv52_multi_vin_design_kit 1.4.2 CV52 Multi-VIN Design Kit
 *
 * CV52 supports 4x native VIN controllers. Through the MIPI virtual channel, it can be extended to 14x VIN
 * controllers. CV52 can support various VIN interfaces including MIPI D/C-PHY and SLVS. MIPI interfaces can
 * be up to 16 lanes. SLVS interface can be up to eight lanes. The following table lists various Ambarella
 * VIN controller layouts.<br>
 *
 * <table>
 * <caption id="cv52_vin_controller_layout">CV52 VIN Controller Layout.</caption>
 * <tr><th> VIN Slot <th> I2C Bus ID <th> VIN Controller ID <th> Type
 * <tr><td align="center" rowspan="6"> SLVS + DPHY
 *     <td align="center" rowspan="6"> 3/4
 *     <td align="center"> 8
 *     <td align="center"> Real
 * <tr><td align="center"> 9
 *     <td align="center"> Virtual
 * <tr><td align="center"> 10
 *     <td align="center"> Virtual
 * <tr><td align="center"> 11
 *     <td align="center"> Real
 * <tr><td align="center"> 12
 *     <td align="center"> Virtual
 * <tr><td align="center"> 13
 *     <td align="center"> Virtual
 * <tr><td align="center" rowspan="4"> DCPHY 0
 *     <td align="center" rowspan="4"> 5
 *     <td align="center"> 0
 *     <td align="center"> Real
 * <tr><td align="center"> 1
 *     <td align="center"> Virtual
 * <tr><td align="center"> 2
 *     <td align="center"> Virtual
 * <tr><td align="center"> 3
 *     <td align="center"> Virtual
 * <tr><td align="center" rowspan="4"> DCPHY 1
 *     <td align="center" rowspan="4"> 1
 *     <td align="center"> 4
 *     <td align="center"> Real
 * <tr><td align="center"> 5
 *     <td align="center"> Virtual
 * <tr><td align="center"> 6
 *     <td align="center"> Virtual
 * <tr><td align="center"> 7
 *     <td align="center"> Virtual
 * </table>
 *
 * Currently, CV52 supports two to four multiple-VIN designs through SERDES with SLVS + DPHY VIN slot.
 * The sensors must support a four-lane interface through either MIPI or SLVS. The following figure shows
 * the sensor boards inserted into the SLVS + DPHY VIN slot on the CV52 Zircon board. Compared with CV5,
 * CV52 does not support SLVS-EC VIN interface.<br>
 *
 * @image html single_sensor_board_plug_in_the_cv52_zircon_board.png "Single Sensor Board Plug in the CV52 zircon Board."
 *
 * @subsubsection multi_vin_design_cv72_multi_vin_design_kit 1.4.3 CV72 Multi-VIN Design Kit
 *
 * CV72 supports 3x native VIN controllers. Through the MIPI virtual channel, it can be extended to 10x VIN
 * controllers. CV72 can support various VIN interfaces including MIPI D/C-PHY and SLVS. MIPI interfaces can
 * be up to 16 lanes. SLVS interface can be up to 8 lanes. The following table lists various Ambarella
 * VIN controller layouts.<br>
 *
 * <table>
 * <caption id="cv72_vin_controller_layout">CV72 VIN Controller Layout.</caption>
 * <tr><th> VIN Slot <th> I2C Bus ID <th> VIN Controller ID <th> Type
 * <tr><td align="center" rowspan="6"> SLVS + DPHY
 *     <td align="center" rowspan="6"> 0
 *     <td align="center"> 8
 *     <td align="center"> Real
 * <tr><td align="center"> 9
 *     <td align="center"> Virtual
 * <tr><td align="center"> 10
 *     <td align="center"> Virtual
 * <tr><td align="center"> 11
 *     <td align="center"> Real
 * <tr><td align="center"> 12
 *     <td align="center"> Virtual
 * <tr><td align="center"> 13
 *     <td align="center"> Virtual
 * <tr><td align="center" rowspan="4"> DCPHY 0
 *     <td align="center" rowspan="4"> 0
 *     <td align="center"> 0
 *     <td align="center"> Real
 * <tr><td align="center"> 1
 *     <td align="center"> Virtual
 * <tr><td align="center"> 2
 *     <td align="center"> Virtual
 * <tr><td align="center"> 3
 *     <td align="center"> Virtual
 * </table>
 *
 * Currently, CV72 supports two to three multiple-VIN design through SERDES with SLVS + DPHY VIN slot.
 * The sensors must support a four-lane interface through either MIPI or SLVS. The following figure shows
 * the sensor boards inserted into the SLVS + DPHY VIN slot on the CV72 Ga board. Compared with CV5,
 * CV72 does not support SLVS-EC VIN interface, and CV72 removes DCPHY 1.<br>
 *
 * @image html single_sensor_board_plug_in_the_cv72_ga_board.png "Single Sensor Board Plug in the CV72 Ga Board."
 *
 * @subsubsection multi_vin_design_max9296_board 1.4.4 MAX9296 Board
 *
 * Because the MAX9296 board is designed to support up to four remote sensors via a coaxial cable, it
 * includes two MAX9296 mounted on the board. Each MAX9296 is capable of connecting up to two remote
 * sensors through the GMSL serializer. For more information about the reference kit board design,
 * contact the Ambarella support team.<br>
 *
 * The four coaxial cable ports are mounted on the reverse side of the MAX9296 board, as shown below.<br>
 *
 * @image html max9296_board_back_view_with_four_coaxial_cable_ports.png "MAX9296 Board Back View with Four Coaxial Cable Ports."
 *
 * The following figure shows the reference kit board MAX9296 + 4x (GMSL serializer MAX9295 + imx290 sensor)
 * connected with a coaxial cable.<br>
 *
 * @image html four_sensors_with_a_coaxial_cable_max9296_4x_gmsl_serializer_imx290.png "MAX9296 Board Back View with Four Coaxial Cable Ports."
 *
 * The following figure shows the GMSL serializer MAX9295 plus a remote sensor reference kit with
 * coaxial cables. With the long cable, the GMSL serializer MAX9295 with a remote sensor can capture
 * images in different directions.<br>
 * @image html gmsl_serializer_max9295_plus_remote_sensor_with_a_coaxial_cable.png "GMSL Serializer MAX9295 Plus Remote Sensor with a Coaxial Cable."
 *
 * - - - -
 *
 * @section multi_vin_design_product_plan 2 Product Plan
 *
 * This chapter introduces the details of a potential product plan for a multi-VIN design with independent
 * sensors, using different cable options.<br>
 *
 * The chapter includes the following sections:<br>
 *
 *   - Section @ref multi_vin_design_quad_sensors_with_a_long_cable_through_max9296
 *   - Section @ref multi_vin_design_quad_independent_sensors
 *   - Section @ref multi_vin_design_dual_channels_from_a_single_sensor
 *   - Section @ref multi_vin_design_dual_sensors_with_different_modes_from_single_serdes
 *   - Section @ref multi_vin_design_dual_channels_from_a_single_sensor_and_raw_data
 *   - Section @ref multi_vin_design_dual_channels_from_a_single_sensor_with_dual_vsrc_ctx
 *   - Section @ref multi_vin_design_supported_sensors
 *   - Section @ref multi_vin_design_stream_view
 *
 * @subsection multi_vin_design_quad_sensors_with_a_long_cable_through_max9296 2.1 Quad Sensors with a Long Cable through MAX9296
 *
 * This section provides an outline for users who prefer to set up their quad sensors with long cables. In this design,
 * four sensors are mounted on four GMSL serializer chips (such as MAX9296), respectively. Every two GMSL serializers
 * connect to a single SERDES (two SERDES are required).  The two SERDES directly connect to controllers VIN8 and VIN11.<br>
 *
 * The following diagram shows the four quad sensors with a long cable design.<br>
 * @image html quad_sensors_with_long_cable_through_the_max9296_design_cv5x_cv7x.png "Quad Sensors with Long Cable through the MAX9296 Design."
 *
 * @par Implementation:
 *
 *   - The four sensors can shoot in any direction, and the application can run 3A independently for these
 *     four sensor inputs.
 *   - Every two sensors (sensor A and B or sensor C and D) that connect to the same SERDES must be identical
 *     in resolution, fps, and image signal processor (ISP) pipeline.
 *   - The maximum resolution of each sensor is up to 1080p60.
 *   - The length of the cable can be up to 15 meters.
 *   - Every two GMSL serializers that connect to the same SERDES must be the same length. This keeps the
 *     sensor phase lock loop (PLL) clock synchronized.
 *   - Each sensor possesses two streams. The main stream is 1080p, and the second stream is a smaller
 *     resolution, 480p or common intermediate format (CIF).
 *   - There is no picture-stitching inside the image digital signal processing (IDSP) channel. Each sensor
 *     input must be either an individual stream or be a part of the combined view stream.
 *
 * @par Product Plan:
 *
 *   - Electronic mirror, surround view, and four cameras in a single case.
 *
 * @subsection multi_vin_design_quad_independent_sensors 2.2 Quad Independent Sensors
 *
 * CV5x SoC includes fourteen VIN controllers, among which has four native VIN controllers. It can support quad independent sensors.
 * Refer to the figure below for a diagram of the quad independent sensors. <br>
 *
 * The four sensors can use up to a 4-lane interface (SLVS + DPHY, DCPHY 0, DCPHY 1), respectively.<br>
 *
 * The sensor boards with quad independent sensors have an I2C mux multiplexed by these four sensors. If this is a
 * configuration users want to run on the CV5 EVK board, follow the instructions through "menuconfig": <br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> platform
 *              -> vin
 *                 sensor-number-choice@virtual (drv_modules/platform/vin/sensors) (quad-sensor@virtual)
 *                 (X) quad-sensor@virtual
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-bsp
 *                 -> sensor-number-choice@virtual (meta-ambabsp/recipes-sensor)
 *                    (X) quad-sensor@virtual
 * @endcode
 *
 * @image html cv5_quad_independent_sensors.png "Quad Independent Sensors."
 *
 * @par Implementation:
 *
 *   - Independent sensors with the 4-lane MIPI (or SLVS) interface.
 *   - Independent 3A parameters for four sensor inputs.
 *   - Independent VIN resolution and frame rate.
 *   - Independent HDR mode (linear + linear, 2X HDR + 2X HDR or linear + 2X HDR).
 *   - Application independently can enable / disable VIN0, VIN4, VIN8, and VIN11 dynamically.
 *
 * @par Product Plan:
 * A wide-angle view camera that provides four different resolutions.
 *
 * @subsection multi_vin_design_dual_channels_from_a_single_sensor 2.3 Dual Channels from a Single Sensor
 *
 * This section defines the design of dual channels from a single sensor.<br>
 *
 * Both channels are captured from a single sensor with the same frame data. The DSP processes the frame data
 * for each channel independently.  For example, both channels can apply different lens distortion correction (LDC)
 * types for wide-angle or fish-eye lenses.<br>
 *
 * This is a special use case named “IDSP virtual channel”. For more information about “IDSP virtual channel”,
 * refer to Section @ref multi_vin_design_idsp_virtual_channels.
 *
 * The following diagram shows the dual channels from the single sensor design.<br>
 * @image html dual_channels_from_the_single_sensor_design_cv5x_cv7x.png "Dual Channels from the Single Sensor Design."
 *
 * @par Implementation:
 *
 *   - The maximum resolution of the sensor is up to 2592x1944 (5 MP).
 *   - The maximum throughput of the sensor is up to 2592x1944@30 in linear mode and 2592x1944@15
 *     in 2X high dynamic range (HDR) modes.
 *   - The two channels have a different IDSP processing frame rate than the VIN frame rate.
 *   - One channel can have up to four canvases for four streams, and the main stream resolution is
 *     the same as the maximum VIN resolution of 2592x1944. The second stream is 480p or CIF. Both
 *     third and fourth streams are 720p.
 *   - The second channel includes multiple canvases, similar to the first channel and the multi-streams.
 *     The main stream resolution is up to 5 MP with a lower frame rate.
 *   - There is no picture stitched inside the DSP. Each channel must be an individual stream or a part
 *     of the combined view stream, either blended view or picture-in-picture (PIP) view.
 *   - If there is one canvas designed as the blended view or PIP view, the data from the two channels
 *     must run at the same frame rate.
 *   - Different CV5x / CV7x chip part support different encode performance combinations.
 *
 * @par Product Plan:
 *
 *   - For products such as a doorbell camera, one channel can show either a rectilinear view captured
 *     from the lens center, or a panoramic view captured from the entire lens, for people detection and
 *     recognition. The other channel can show the rectilinear view captured from the lens bottom in
 *     order to perform object detection.
 *   - For particular consumer-type products, one channel can be downscaled from the original VIN resolution
 *     (> 2 MP) to a smaller resolution, such as 2 MP for stream encoding. The other channel can be down-sampled
 *     from 30 fps to 1 fps for the MJPEG snapshot with the original VIN resolution.
 *   - For select professional products, dual channels double the total number of independent source buffers
 *     from four to eight, enabling the encoding of four or more different resolution streams.
 *
 * @subsection multi_vin_design_dual_sensors_with_different_modes_from_single_serdes 2.4 Dual Sensors with Different Modes from Single SERDES
 *
 * This section defines the design of dual sensors with different modes from a single SERDES. This is achieved
 * based on the capability of the MIPI virtual channel supported by both SERDES and CV5x / CV7x.<br>
 *
 * In this design, two sensors are mounted on two GMSL serializer chips (such as MAX9296) respectively.  Each
 * GMSL serializer connects to a single SERDES (two SERDES are required) with long cables. The two SERDES
 * directly connect to controllers VIN8 and VIN9.<br>
 *
 * The following diagram shows the two sensors with a long cable design.<br>
 * @image html two_sensors_with_long_cable_through_the_max9296_design_cv5x_cv7x.png "Two Sensors with Long Cable Through the MAX9296 Design."
 *
 * @par Implementation
 *
 *   - The two sensors can shoot in any direction, and the application can run 3A independently for
 *     these two sensor inputs.
 *   - Each sensor can run different VIN modes.  For example, one in linear mode, and the other in
 *     digital overlap (DOL) 2x HDR mode.
 *   - The length of the cable can be up to 15 meters.
 *   - There is no picture stitching inside the IDSP channel. Each sensor input must be either an
 *     individual stream or a part of the combined view stream.
 *
 * @par Product Plan:
 *
 *   - Electronic mirror, surround view, and two cameras in a single case.
 *
 * @subsection multi_vin_design_dual_channels_from_a_single_sensor_and_raw_data 2.5 Dual Channels from a Single Sensor and Raw Data
 *
 * This section defines the design of dual channels from a single sensor and the raw data via direct
 * memory input.<br>
 *
 * One channel captures the frame data from a regular sensor input. The other channel captures the raw
 * data fed by the user application through memory, which acquires the frame data from a device, such
 * as the USB camera.<br>
 *
 * The following shows the diagram of dual channels from a single sensor and the raw data:<br>
 * @image html dual_channels_from_a_single_sensor_and_raw_data_cv5x_cv7x.png "Dual Channels from a Single Sensor and Raw Data."
 *
 * @par Implementation:
 *
 *   - The maximum resolution of the sensor input and raw data input is 1080p.
 *   - For sensor input, the maximum throughput is up to 1080p60 in linear mode and 1080p30 in 2X HDR mode.
 *   - For raw data input, the maximum frame rate cannot exceed the sensor input frame rate. For example,
 *     if the sensor input frame rate is 30 fps, the raw data feeding rate must be lower than 30 fps.
 *   - The format for raw data must be either the standard Bayer RGB format or the YUV422 format with UV interleaved.
 *   - Each channel can include three streams; the main and the third streams’ resolutions are both 1080p,
 *     and the second stream is smaller, such as 480p or CIF.
 *   - There is no picture stitched inside the DSP. Each channel must be an individual stream or a part of
 *     the combined view stream (either blended view or PIP view).
 *   - The application can feed raw data via “test_efm”, the standard unit test tool.
 *   - Different CV5x / CV7x chip parts support different encode performance combinations.
 *
 * @par Product Plan:
 *
 * Single sensor + USB camera, single optical sensor + thermal sensor.
 *
 * @subsection multi_vin_design_dual_channels_from_a_single_sensor_with_dual_vsrc_ctx 2.6 Dual Channels from a Single Sensor with Dual Vsrc_ctx
 *
 * This section describes the design setup of dual channels from a single sensor with the dual vsrc_ctx.
 * For more information about "vsrc_ctx", refer to Section @ref multi_vin_design_single_sensor_with_a_dual_vsrc_ctx<br>
 *
 * For the implementation of the dual vsrc_ctx, different sensor manufacturers may require different solutions.
 * Additionally, the maximum number of supported vsrc_ctx depends on the sensor models. Currently, CV5x / CV7x support
 * the following forms of dual vsrc_ctx solutions:<br>
 *
 *   - Some sensor models from Sony, such as IMX264 and IMX265, can support up to four vsrc_ctx. Users
 *     can opt to enable two or four of them. The sensor itself can automatically generate frame-interleaved
 *     frames with different vsrc_ctx. Each frame corresponding to a specific vsrc_ctx has a different
 *     pattern embedded in the first line of its data. CV5x / CV7x IDSP can dispatch them into different channels,
 *     according to their fixed patterns. The embedded frame pattern data will be cropped out by the IDSP.<br>
 *
 * @par Implementation:
 *
 *   - The maximum-supported resolution of the sensor can be up to 3840x2160 (8 MP) depending on the
 *     specific chip specifications; only linear mode is supported. This feature requires the sensor
 *     support for multiple register groups of shutter / gain settings.
 *   - In linear mode, the maximum throughput of the sensor is 3840x2160@30.
 *   - With dual vsrc_ctx, the IDSP processing frame rate of these two channels must be 1/2 of the VIN
 *     frame rate. The frames of the sensor are divided into two groups, half-by-half. One is for channel 0;
 *     the other is for channel 1.
 *   - Each channel can have up to four canvases for four streams, and the main stream resolution is
 *     the same as the maximum VIN resolution. The second stream is 480p or CIF. Both third and fourth
 *     streams are 1080p.
 *   - There is no picture stitched inside the DSP. Each channel must be an individual stream or a part
 *     of the combined view stream (either blended view or PIP view).
 *   - Various CV5x / CV7x chip parts support different encode performance combinations.
 *
 * @Product Plan:
 *
 * For some video content analysis (VCA) products, the application configures the long and short
 * exposures interleaved frame-by-frame with two groups of different 3A settings. This process
 * enables the application to achieve much larger long / short shutter ratios than the typical
 * HDR ratio (16x or 32x).<br>
 *
 * @note
 *   - This feature is highly dependent on the sensor register settings; it requires sensor support
 *     for multiple shutter / gain register groups.
 *   - Dual context from a single sensor uses one VIN interface; the application can connect the
 *     other sensor to another VIN interface.
 *   - There is no limitation for the sensor type or sensor mode for another VIN.
 *
 * @subsection multi_vin_design_supported_sensors 2.7 Supported Sensors
 *
 * This section provides information about the sensors supported for various multi-VIN designs.<br>
 *
 * The two VIN controllers are limited by the total number of VIN lanes. The dual independent sensors
 * use four lanes each; the sensor drivers must support all lanes.<br>
 *
 * <table>
 * <caption id="supported_sensors_for_multi_vin_with_native_dual_vin_design">Supported Sensors for Multi-VIN with Native Dual VIN Design. </caption>
 * <tr><th> Sensor(4-lane MIPI or SLVS I/F) <th> Resolution(MP) <th> Native Dual Sensors <th> Notes
 * <tr><td align="center"> IMX290
 *     <td align="center"> 2.0
 *     <td align="center"> Yes
 *     <td> 1: Lnear mode <br>
 *          2: DOL 2X HDR mode
 * <tr><td align="center"> IMX274
 *     <td align="center"> 8.0
 *     <td align="center"> Yes
 *     <td> 1: Lnear mode<br>
 *          2: DOL 2X HDR mode
 * <tr><td align="center"> IMX327
 *     <td align="center"> 2.0
 *     <td align="center"> Yes
 *     <td> 1: Lnear mode<br>
 *          2: DOL 2X HDR mode
 * <tr><td align="center"> IMX334
 *     <td align="center"> 8.0
 *     <td align="center"> Yes
 *     <td> 1: Lnear mode<br>
 *          2: DOL 2X HDR mode
 * <tr><td align="center"> IMX335
 *     <td align="center"> 5.0
 *     <td align="center"> Yes
 *     <td> 1: Lnear mode<br>
 *          2: DOL 2X HDR mode
 * <tr><td align="center"> IMX415
 *     <td align="center"> 8.0
 *     <td align="center"> Yes
 *     <td> 1: Lnear mode<br>
 *          2: DOL 2X HDR mode
 * <tr><td align="center"> OS05A10
 *     <td align="center"> 5.0
 *     <td align="center"> Yes
 *     <td> 1: Lnear mode<br>
 *          2: DOL 2X HDR mode
 * <tr><td align="center"> OS08A10
 *     <td align="center"> 8.0
 *     <td align="center"> Yes
 *     <td> 1: Lnear mode<br>
 *          2: DOL 2X HDR mode
 * </table>
 *
 * The multi-VIN design with MAX9296 must use the same sensors. The support list is shown below:<br>
 *
 * <table>
 * <caption id="supported_sensors_for_multi_vin_with_max9296"> Supported Sensors for Multi-VIN with MAX9296.</caption>
 * <tr><th> Sensor <th> Resolution (MP) <th> Dual Remote Sensors <th> Triple Remote Sensors <th> Quad Remote Sensors <th> Notes
 * <tr><td align="center"> IMX290
 *     <td align="center"> 2.0
 *     <td align="center"> Yes
 *     <td align="center"> Yes
 *     <td align="center"> Yes
 *     <td> 1: Linear mode<br>
 *          2: DOL 2X HDR mode
 * <tr><td align="center"> IMX390
 *     <td align="center"> 2.0
 *     <td align="center"> Yes
 *     <td align="center"> Yes
 *     <td align="center"> Yes
 *     <td> 1: Linear mode<br>
 *          2: DOL 2X HDR mode
 * </table>
 *
 * @note
 *   - The native dual VIN can support various sensor combinations as long as each individual sensor
 *     includes four lanes of MIPI interface connected to the CV5x / CV7x.
 *   - The native dual VIN can also support a long cable with the SERDES chip, which extends the
 *     distance from the sensor to the CV5x / CV7x.
 *   - B5F / B5N requires three or four pairs of SERDES cables to support a higher image resolution
 *     in each channel.
 *   - B6F / B6N can use either coaxial or Ethernet cables to support a higher image resolution in each channel.
 *
 * @subsection multi_vin_design_stream_view 2.8 Stream View
 *
 * For multi-VIN design, CV5x / CV7x support several stream views:<br>
 *
 *   - Independent stream view: Each stream is separately encoded from each sensor.
 *   - Blend stream view: One stream covers several sensor inputs’ field of view (FoV).
 *     The sensor’s input FoV can be aligned in either horizontal or vertical directions.
 *   - PIP stream view: One stream covers several sensor inputs’ FoV. One sensor input’s FoV
 *     functions as a small on-screen display (OSD) on another sensor input’s FoV.
 *
 * @subsubsection multi_vin_design_independent_stream_view 2.8.1 Independent Stream View
 *
 * The source buffers can be applied to different scale factors from the different VIN channels, as
 * shown in the following diagram. Streams can be encoded separately from these FoVs.<br>
 *
 * @image html independent_stream_view_in_multi_vin_design.png "Independent Stream View in the Multi-VIN Design."
 *
 * @par Implementation:
 *
 *   - A separate canvas for each output.  One stream cannot cross FoVs.
 *   - An independent frame rate for each output or stream.
 *
 * @subsubsection multi_vin_design_blend_stream_view 2.8.2 Blend Stream View
 *
 * The source buffer can be applied to the same scale factor from different VIN channels (as
 * shown in the following diagrams). All channels of the main buffer are combined in horizontal
 * and vertical directions.<br>
 *
 * @image html horizontal_blend_stream_view_in_multi_vin_design.png "Horizontal Blend Stream View in the Multi-VIN Design."
 * @image html vertical_blend_stream_view_in_multi_vin_design.png "Vertical Blend Stream View in the Multi-VIN Design."
 *
 * The application can encode the single stream to cover the three sensors’ input FoVs, enabling a
 * 180° panoramic view.<br>
 *
 * Stitched or panoramic view is one of the combinations of the blend view.<br>
 *
 * @note
 *   - When multiple main buffers are placed in the same canvas in the vertical blend view, the canvas
 *     option “enable_order” must be enabled.  The bottom of the main buffer always adds 16 lines of
 *     extra padding data. This option enables the next buffer to vertically cover the padding data of
 *     the current buffer. This prevents the padding data from leaking.<br>
 *
 * @par Implementation:
 *
 *   - Multiple outputs in one canvas
 *   - Identical frame rates for all VIN channels
 *
 * @par Examples
 *
 * - Horizontal Blend Stream View
 *
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8)     // For CV72
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg dual_chan_single_sensor.lua
 * board # test_encode -S 4 -H 3840x1072 --smaxsize 3840x1072 -b 4 -e
 * @endcode
 *
 * - Vertical Blend Stream View
 *
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8)     // For CV72
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg dual_chan_single_sensor.lua
 * board # test_encode -S 5 -H 1920x2144 --smaxsize 1920x2144 -b 5 -e
 * @endcode
 *
 * For lua script to configure VIN / canvas / buffer layouts / stream, please refer to @ref multi_vin_design_lua_script_4_2
 *
 * @subsubsection multi_vin_design_pip_stream_view 2.8.3 PIP Stream View
 *
 * The source buffer can be applied to different scale factors from the different VIN channels,
 * and the output from one channel can be overlapped with another.<br>
 *
 * The application can encode the single stream to cover the three sensors’ input FoVs, enabling a PIP view.<br>
 * @image html pip_stream_view_in_multi_vin_design.png "PIP Stream View in the Multi-VIN Design."
 *
 * @par Implementation:
 *
 *   - Multiple outputs in one canvas
 *   - Identical frame rates for all VIN channels
 *   - The output from one VIN channel of the sub-source buffer, which is overlapped onto another
 *     VIN channel of the same source buffer in one canvas
 *
 * @par Example
 *
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8)     // For CV72
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg dual_chan_single_sensor.lua
 * board # test_encode -S 6 -H 1920x1072 -b 6 -e
 * @endcode
 *
 * For lua script to configure VIN / canvas / buffer layouts / stream, please refer to @ref multi_vin_design_lua_script_4_2
 *
 * - - - -
 *
 * @section multi_vin_design_system_design 3 System Design
 *
 * This chapter describes the details of a multi-VIN design, including memory management, VIN channel
 * layout, canvas layout, buffer layout, stream layout, and PIP effect between channels.<br>
 *
 *   - Section @ref multi_vin_design_memory_management
 *   - Section @ref multi_vin_design_data_flow
 *   - Section @ref multi_vin_design_concept_and_configuration
 *   - Section @ref multi_vin_design_sensor_driver_installation
 *
 * @subsection multi_vin_design_memory_management 3.1 Memory Management
 *
 * Compared to the single-VIN design, DSP requires a larger dynamic random-access memory (DRAM) size for
 * the multi-VIN design. Additionally, the multi-VIN design requires more DSP messages and commands to
 * dynamically exchange the multi-channel information, such as VIN channel layout, canvas layout, stream
 * layout, and so on.  As a result, these additional commands and messages require a larger DRAM size for
 * the image audio video (IAV) driver, as well.*<br>
 *
 * The IAV creates a new partition to store multi-channel commands for this information, which is approximately
 * 6 KB per channel.  Users can configure the channel number from “menuconfig” as follows:<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> platform
 *              -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *              (4) Max VIN Channel Number // Change to 2 ~ 16 (depends on the real channel number)
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-bsp
 *                 -> recipes-video
 *                    -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                       (4)   Max VIN Channel Number
 * @endcode
 * @subsection multi_vin_design_data_flow 3.2 Data Flow
 *
 * CV5x / CV7x-supported product types of multi-VIN design are described in Section: @ref multi_vin_design_product_plan
 *
 * This section describes the entire data flow of product types, including the sensor to VIN controller,
 * the VIN controller to channel, and the channel to canvas.<br>
 *
 * @subsubsection multi_vin_design_dual_vin_controllers 3.2.1 Dual VIN Controllers
 *
 * The two real VIN controllers are limited only by the interface. The controllers can take up to
 * a 4-lane MIPI sensor at one time.<br>
 *
 * The VIN8 controller can use either the Bayer RGB format data or the YUV format data, while the
 * VIN11 controller can only take the Bayer RGB format data.<br>
 *
 * @image html dual_vin_controllers_data_flow_cv5x_cv7x.png "Dual Vin Controllers Data Flow."
 *
 * @par Data Flow:
 *
 *   - Each sensor is enumerated as a video source (VSRC) device and is connected to a separated VIN controller.
 *   - The CV5x / CV7x IDSP run two passes to process the data from the dual VIN controllers independently.
 *   - Channel 0 is from sensor A via VIN8, and channel 1 is from sensor B via VIN11.
 *
 * @subsubsection multi_vin_design_quad_sensors_long_cable_with_serdes 3.2.2 Quad Sensors (Long Cable) with SERDES
 *
 * For quad sensor cases:<br>
 *
 *   - Quad sensors are mounted on serializer chips. Every two serializers connect to one MAX9296. Two MAX9296
 *     chips are required. Then, these two MAX9296 chips connect to the CV5x / CV7x controllers (VIN8 and VIN11).
 *
 * @image html quad_sensors_through_the_max9296_data_flow_cv5x_cv7x.png "Quad Sensors Through the MAX9296 Data Flow."
 *
 * @par Data Flow:
 *
 *   - Each sensor is enumerated as a VSRC device, connected to the VIN controller 0 through a bridge chip, B5N,
 *     or connected to VIN8 and VIN11 through two MAX9296 chips respectively.
 *   - The CV5x / CV7x IDSP runs four passes to independently process the data from VIN8 and VIN11.
 *   - Channels 0 / 1 / 2 / 3 are from sensor A / B / C / D.
 *
 * @subsubsection multi_vin_design_idsp_virtual_channels 3.2.3 IDSP Virtual Channels
 *
 * For single-sensor cases, CV5x / CV7x supports IDSP virtual channels with the multi-channel design (refer
 * to the following figure).<br>
 *
 * @image html idsp_virtual_channels_data_flow_cv5x_cv7x.png "IDSP Virtual Channels Data Flow."
 *
 * @par Data Flow:
 *
 *   - Sensor A is enumerated as the VSRC 0 device and connected to VIN0.
 *   - The CV5x / CV7x IDSP run four passes to process the sensor data from VIN0 independently with different
 *     IDSP filter parameters.
 *   - Channels 0 / 1 / 2 / 3 are from sensor A with duplicated sensor data.
 *
 * @subsubsection multi_vin_design_single_sensor_with_a_dual_vsrc_ctx 3.2.4 Single Sensor with a Dual Vsrc_ctx.
 *
 * A single sensor with a dual vsrc_ctx is a special use case of the “IDSP virtual channel”. Support for
 * the dual vsrc_ctx depends on the sensor model.<br>
 *
 * Some sensors possess two separated shutter / gain register groups. These two register groups are used to
 * configure two different sets of the shutter / gain to two successive frames generated by this single sensor
 * independently. For example, with the dual vsrc-ctx, all <B>2 * N + 0</B> frames are set to shutter / gain
 * group 1, and all <B>2 * N + 1</B> frames are set to shutter / gain group 2. Here, each register group of
 * shutter / gain is called vsrc_ctx.  2x channels are set up to capture the frames from the two vsrc_ctx,
 * as shown below.<br>
 *
 * Using dual vsrc-ctx as an example, all <B>2 * N + 0</B> frames with shutter / gain group 1 are captured
 * through channel 0, and all <B>2 * N + 1</B> frames with shutter / gain group 2 are captured through
 * channel 1.  As the two register groups of shutter / gain can be configured independently without affecting
 * each other, it functions as if channel 0 and channel 1 are from two different sensors.<br>
 *
 * The following shows dual channels from the single sensor design with the dual vsrc_ctx.<br>
 *
 * @image html dual_channels_from_a_single_sensor_with_dual_vsrc_ctx_design_cv5x_cv7x.png "Dual Channels from a Single Sensor with the Dual Vsrc_ctx Design."
 *
 * @par Data Flow:
 *
 *   - Sensor A is enumerated as the VSRC 0 device, and connected to VIN0.
 *   - With the dual vsrc_ctx, the IDSP processing frame rate of these two channels is 1/2 of the VIN frame rate.
 *     The sensor frames are divided into two groups: one for channel 0 and the other for channel 1.
 *   - Among the dual vsrc_ctx, each vsrc_ctx supports its own shutter / gain. Each channel processes the sensor
 *     data independently with its own IDSP filter parameters.
 *
 * @subsubsection multi_vin_design_vsrc_to_channel 3.2.5 Vsrc to Channel
 *
 * @par Concept
 *
 *   - VIN: Each VIN controller is abstracted as a “VIN” instance. It can be connected directly to an independent
 *     sensor or multiple sensors through SERDES.
 *   - vsrc: Each sensor is abstracted as a “vsrc” instance.
 *   - vsrc_ctx: For sensors with multiple separated shutter / gain register groups that can configure different
 *     shutter / gain to multiple successive frames independently.  Each shutter / gain register group is
 *     abstracted as a “vsrc_ctx” instance.  A “vsrc” may have multiple “vsrc_ctx”.
 *
 * The following image demonstrates the data flow from the “vsrc” to the channel:<br>
 * @image html vsrc_to_channel_data_flow_cv5x_cv7x.png "Vsrc to the Channel Data Flow."
 *
 * @par Data Flow:
 *
 *   - Sensor A and sensor B both connect to VIN0 through SERDES.  Sensor A corresponds to vsrc0 and sensor
 *     B corresponds to vsrc1.
 *   - Each vsrc is captured into one channel that processes its data independently from the other channels.
 *
 * @subsubsection multi_vin_design_channel_to_canvas 3.2.6 Channel to Canvas
 *
 * The CV5x / CV7x multi-channel design enables up to five outputs per channel for data content and for pyramid output.
 * The outputs for the multi-channel case include the main / second / third / fourth / fifth source buffers and
 * the pyramid buffer. They function as follows:<br>
 *
 *   - ch0.main / ch1.main / ...
 *   - ch0.2nd / ch1.2nd / ...
 *   - ch0.3rd / ch1.3rd / ...
 *   - ch0.4th / ch1.4th / ...
 *   - ch0.5th / ch1.5th / ...
 *   - ch0.pyramid / ch1. pyramid / ...
 *
 * The figure on the following page illustrates the channel to buffer data flow, followed by a figure of the
 * channel to canvas data flow.<br>
 *
 * @image html channel_to_buffer_data_flow_cv5x_cv7x.png "Channel to Buffer Data Flow."
 * @image html channel_to_canvas_data_flow_cv5x_cv7x.png "Channel to Canvas Data Flow."
 *
 * @par Data Flow:
 *
 *   - Channel 0 generates: ch0.main, ch0.2nd, ch0.3rd, ch0.4th, ch0.5th, and pyramid
 *   - Channel 1 generates: ch1.main, ch1.2nd, ch1.3rd, ch1.4th, ch1.5th, and pyramid
 *   - Channel 2 generates: ch2.main, ch2.2nd, ch2.3rd, ch2.4th, ch2.5th, and pyramid
 *   - Channel 3 generates: ch3.main, ch3.2nd, ch3.3rd, ch3.4th, ch3.5th, and pyramid
 *
 * The following list provides examples of five canvases derived from four channels:
 *
 *   - Canvas 0: ch0.main and ch1.main
 *   - Canvas 1: ch0.2nd, ch1.2nd, ch2.2nd, and ch3.2nd
 *   - Canvas 2: ch0.3rd, ch1.3rd and ch2.3rd
 *   - Canvas 3: ch0.4th
 *   - Canvas 4: ch1.4th
 *
 * @subsection multi_vin_design_concept_and_configuration 3.3 Concept and Configuration
 *
 * For the multi-VIN design, the application must configure the various layout settings, including VIN,
 * canvas, stream, and VOUT.<br>
 *
 * To facilitate parsing the parameters, a Lua script file is introduced as the configuration file for
 * these layout settings. The Lua script is refined to organize the parameters and the multi-VIN design
 * options in a streamlined format. This Lua script format is a good reference for users to configure
 * their own implementation and file format for organizing these options.<br>
 *
 * <B>Reference code:</B> test_encode.c / test_multi_chan.c;<br>
 *                        multi-channel Lua parser library;<br>
 *                        multi_chan_vin0_1_1080p_linear.lua /<br>
 *                        multi_chan_vin0_1_4Mp_hdr.lua<br>
 *
 * @subsubsection multi_vin_design_sensor_configuration 3.3.1 Sensor Configuration
 *
 * For the two sensor designs on native dual VINs, the DSP receives the image content from the two
 * sensors, independently.<br>
 *
 * From the application, the sensor data saved in the DSP memory is as follows:<br>
 *
 *   - Frame N of VIN channel 0
 *   - Frame N of VIN channel 1
 *   - Frame N+1 of VIN channel 0
 *   - Frame N+1 of VIN channel 1
 *   - ... ... ...
 *
 * @par Implementation:
 *
 *   - Each sensor is configured as an independent "vsrc" instance in the Lua script.
 *   - Each sensor (vsrc) is connected with the independent VIN.  It can have different resolution,
 *     frame rate, and output mode.
 *   - The application can capture the sensor's raw data via the standard unit test tool "test_yuvcap".
 *
 * @par Usage:
 *
 *   - "vsrc_id" is used to specify the sensor input ID.  It is suggested to keep the same value as
 *     a sensor index, which is generated automatically during the sensor driver probes and corresponds
 *     to a real sensor.
 *   - "mode" is used to specify the sensor resolution mode.
 *   - "hdr_mode" is used to specify the high dynamic range (HDR) mode or linear mode, for example linear,
 *     2x, or 3x.
 *   - "fps" is used to specify the sensor frame rate.
 *   - "bits" is used to specify the sensor RGB bits.  0 for AUTO, 8 ~ 16 for specified bits.
 *   - "vsrc_ctx_switch" is used to specify the sensor register vsrc_ctx auto switch flag. It only works for
 *     some sensors, such as AR0230 and AR0237, which can support multiple register groups of the shutter and AGC.
 *     Not currently supported but planned for a later version CV5x / CV7x SDKs.
 *
 * @par Example:
 * @code
 *    vsrc_0 = {
 *        vsrc_id = 0,
 *        mode = "1080p",
 *        hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *        fps = 20,
 *        bits = 0,
 *        vsrc_ctx_switch = 0
 *    }
 *
 *    vsrc_1 = {
 *        vsrc_id = 1,
 *        mode = "1080p",
 *        hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *        fps = 20,
 *        bits = 0,
 *        vsrc_ctx_switch = 0
 *    }
 * @endcode
 *
 * @subsubsection multi_vin_design_channel_configuration 3.3.2 Channel Configuration
 *
 * For the multi-VIN design, the application can define different maximum source-buffer output widths for each
 * VIN channel, as well as various channel processing orders.<br>
 *
 * @par Implementation:
 *
 *   - CV5x / CV7x chips support up to eight channels.
 *   - DSP supports the flexible channel processing order. By default, it processes channels in ascending order.
 *     Each channel that the DSP processes is overlapped by the following channel.
 *   - Channel processing order supports on the fly updating to switch the content among channels.
 *   - The channel processing order is applied per-canvas.
 *   - If the application must swap PIP image content with background image content, it must change the channel
 *     processing order on the fly. The latter order channel can be overlapped with the former order channel.
 *   - The application can capture the canvas YUV / ME1 / ME0 data via the standard unit test tool "test_yuvcap".
 *   - For dual channels from a single sensor, DSP generates two copies of the 3A statistical data. Only one channel's
 *     3A data is required to control 3A because there is only a single sensor. For example, if channel 0's 3A statistic
 *     data is selected, users must set "sensor_ctrl = 1" and "img_stats_src_chan = chan_0" for channel 0. Then, set
 *     the "sensor_ctrl = 0" and "img_stats_src_chan = chan_0" for channel 1 in the Lua script.
 *   - max_main_input_width is used to configure the maximum input width for the main buffer. By default, max_main_
 *     input_width is set to 0, which is equal to the VIN raw width. However, the maximum input width must be configured
 *     if the user application requires a small main buffer input size, such as 720x480, with a large VIN, size such
 *     as 3840x2160.  The main buffer input width cannot exceed this parameter, if set, through the run-time update
 *     during the preview / encoding state.  Not currently supported but planned for a later version.
 *   - A sixth source buffer is multiplexed from the pyramid; only one can be enabled at a time.
 *
 * @par Usage:
 *
 *   - "id" specifies the channel ID. Ambarella recommends that users keep the same value as the channel index,
 *     which starts from zero.
 *   - "vsrc" specifies the source sensor (vsrc) for the channel. The content must be declared before the channel
 *     definition in the Lua script.
 *   - "raw_capture" is used to enable raw data capture from the RGB sensor. Users can get more information from
 *     the help message of the unit test app, test_yucap.
 *   - "vsrc_ctx" specifies the sensor register context of the source sensor (vsrc) for the channel. It functions
 *     with specific sensors, such as AR0230, which support multiple register groups of shutter and AGC.
 *   - "img_stats_src_chan" tells the 3A process which channel’s statistics are used for 3A control for the channel.
 *     It is used for the multi-channel stitching and IDSP virtual channel cases.
 *   - "sensor_ctrl" tells the sensor driver which channel is allowed to configure the shutter and AGC. It is only
 *     used for special "IDSP virtual channel" cases.
 *   - "max_padding_width" configures the padding value for the LDC purpose on this channel. It must function with
 *     the "lens_warp" option.
 *   - "idsp_fps" specifies the resample IDSP output frame rate.  It must be less than or equal to the VIN frame rate.
 *   - "lens_warp" enables the LDC function.
 *   - "max_main_input_width" specifies the maximum main buffer input width and can help the DSP allocate the proper
 *     resources from various cases. It must be configured when the user application requires a small main buffer
 *     input size (for example, 720x480) with a large VIN size (for example, 3840x2160). If set, it cannot be exceeded
 *     by the main buffer input width through the run-time update during the preview / encoding.
 *   - "blend_left" enables horizontal cross-channel stitching.
 *   - "blend_right" enables vertical cross-channel stitching.
 *   - "mctf_cmpr" enables motion-compensated temporal filtering (MCTF) compression.
 *   - "mctf_10bit_ref" enables the MCTF 10-bit reference.
 *   - "main_burst_tile" enables main burst tile mode.  By default, it must be set to 1.
 *   - "extra_downscale" enables a large downscale.  When the downscale ratio is greater than or equal to 6X, it must
 *     be set to 1.
 *   - "enable_group" enables channel grouping.  The channels in the same group must run the same frame rate.
 *   - "group_idx" specifies group index. For example, if channel 0’s and channel 1’s group_idx = 0, then channel 0
 *     and channel 1 are in the same group0.  Its range is 0-3 and is only valid when enable_group = 1.
 *   - "group_sync" enables channel grouping synchronization.  It is only valid when enable_group = 1.
 *   - "max_warp_input_width" specifies the maximum input width for dewarp.
 *   - "max_warp_output_width" specifies the maximum output width for dewarp.
 *   - "max_vwarp_wait_lines" specifies the waiting lines for vwarp.
 *   - "invert_mode" enables invert mode.  In this mode, all pixels of source buffers will be inverted.
 *   - "use_vsrc_ctx_pattern" specifies if the IDSP splits the VIN frame into the current channel according to its
 *     "vsrc_ctx_pattern”. This feature is only supported by certain SONY sensors, such as IMX264 and IMX265.
 *   - "vsrc_ctx_pattern" specifies the data pattern that is embedded in the first line of sensor data.
 *   - "vsrc_ctx_pattern_mask" specifies valid bits in the "vsrc_ctx_pattern”.
 *   - "vsrc_ctx_pattern_offset" specifies the data offset in the sensor data.
 *   - "pass_num" specifies the pass number generated by the IDSP for the source buffers.
 *   - "pass_0_rotation" specifies if the first pass is rotated.
 *   - "low_delay_vin_vout" enables low-delay mode between VIN and VOUT.
 *   - "packing_mode_enable" enables VIN packing mode only when the VIN RAW compression is disabled to save the
 *     DRAM bandwidth.
 *   - "low_delay_vin_vout" enables low-delay mode between VIN and VOUT.
 *   - "packing_mode_enable" enables VIN packing mode only when the VIN RAW compression is disabled to save DRAM
 *     bandwidth.
 *   - "vsrc_region_num" specifies the total region number of the source sensor. These multiple vsrc_regions must
 *     be stored in a line-interleaved format in the sensor data.
 *   - "vsrc_region_idx" specifies a region from which the current channel captures the sensor data.
 *   - "premain / main / second / third / fourth / fifth / sixth" are used to specify the buffer output of each channel.
 *
 * @par Example:
 *
 * @code {.c}
 *     chan_0 = {
 *         id = 0,
 *         vsrc = vsrc_0,
 *         raw_capture = 1,
 *         vsrc_ctx = 0,
 *         img_stats_src_chan = "chan_0",
 *         sensor_ctrl = 1,
 *         max_padding_width = 0,
 *         idsp_fps = 0,
 *         lens_warp = 0,
 *         max_main_input_width = 0, -- 0: VIN raw width
 *         blend_left = 0,
 *         blend_right = 0,
 *         mctf_cmpr = 0,
 *         mctf_10bit_ref = 0,
 *         main_burst_tile = 1,
 *         extra_downscale = 0,
 *         enable_group = 0,
 *         group_idx = 0,
 *         group_sync = 0,
 *         main = {
 *             max_output = {0, 0}, -- output width
 *             input      = {0, 0, 0, 0}, -- full VIN
 *             output     = {0, 0, 1920, 1080},
 *         },
 *
 *         second = {
 *             max_output = {0, 0}, -- output width
 *             input      = {0, 0, 0, 0}, -- full main
 *             output     = {0, 0, 720, 480},
 *         },
 *
 *         third = {
 *             ... ... ...
 *         },
 *
 *         fourth = {
 *             ... ... ...
 *         },
 *
 *         fifth = {
 *             ... ... ...
 *         },
 *
 *         pyramid = {
 *             input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
 *             scale_type = 0,		-- 0: 1/sqrt(2)	1: 1/2
 *             buf_addr = 0x0,
 *             buf_size = 0x0,
 *             layer_map = 0x3F,
 *             layers = {
 *                 {
 *                     crop_win = {0, 0, 0 ,0},
 *                 },
 *                 ... ... ...
 *             },
 *         },
 *     }
 *
 * @endcode
 *
 * @subsubsection multi_vin_design_channel_group 3.3.3 Channel Group
 *
 * The channel group concept applies in the multi-VIN design.
 *
 * The main purpose of channel group is to ensure that the order of output of all channels is the same.
 * This feature is very important for multi-vin design because the mechanism of processing video frame
 * for image digital signal processing (DSP) is FIFO.<br>
 *
 * For example, in picture in picture (PIP) stream view, the output from one channel can be overlapped on another.
 * If the output order of these channels cannot be the same, the overlap will be disordered (one minute for the output of channel A is on the top of the output of channel B, the next B is on top of A).
 * Once the channel group is enabled, this uncertainty does not exist because DSP will not process the frames until all
 * grouping channels receive new frames. When all grouping channels' new frames are received, DSP will process them orderly.<br>
 *
 * The application must use the following rules for channel group design:
 *
 * @par Implementation:
 *
 *   - All VIN sensors in a group are suggested to be the same and started at the same time. If sensors in a group are not the same,
 *     in order to keep in sync, the sensors are suggested to work in slave mode and use the same fsync signal from Amba SoC. This is to keep
 *     the sensors output the raw frames in sync. Otherwise, a longer tolerance needs to be set via `test_encode option`
 *     "--debug-chan-group-tolerance 90" (using 90 as an example, the default value is 50) to avoid frame drop due to tolerance missing.
 *
 * @par Usage:
 *
 *   - "enable_group" is used to enable the channel grouping. The channels in the same group must run the same frame rate.
 *   - "group_sync" is used to enable the channel grouping synchronization. It is only valid when enable_group = 1.
 *   - "group_idx" is used to specify the group index. For example, if chan0's and chan1's group_idx = 0,
 *     it means that chan0 and chan1 are in the same group0. Its range is 0~3, and is only valid when enable_group = 1.
 *   - "group_order_index" is used to specify the process order of channel in a group.
 *
 * @par Example:
 *
 *     @code
 *     chan_0 {
 *         ... ... ...
 *         enable_group = 1,
 *         enable_sync = 1,
 *         group_index = 0,
 *         group_order_index = 1,
 *         main = {
 *             max_output = {1920, 0},
 *             input      = {   0, 0, 1920, 1080},
 *             output     = { 960, 0,  960, 1080},
 *         },
 *
 *         second = {
 *             ... ... ...
 *         },
 *
 *         third = {
 *             max_output = {1920, 0},
 *             input      = {   0, 0,  960, 1080},
 *             output     = { 960, 0,  960, 1080},
 *         }
 *
 *         fourth = {
 *             ... ... ...
 *         },
 *
 *         fifth = {
 *             ... ... ...
 *         },
 *     }
 *
 *     chan_1 {
 *         ... ... ...
 *         enable_group = 1,
 *         enable_sync = 1,
 *         group_index = 0,
 *         group_order_index = 2,
 *         main = {
 *             max_output = {1920, 0},
 *             input      = {   0, 0, 1920, 1080},
 *             output     = { 960, 0,  960, 1080},
 *         },
 *
 *         second = {
 *             ... ... ...
 *         },
 *
 *         third = {
 *             max_output = {1920, 0},
 *             input      = {   0, 0,  960, 1080},
 *             output     = { 960, 0,  960, 1080},
 *         }
 *
 *         fourth = {
 *             ... ... ...
 *         },
 *
 *         fifth = {
 *             ... ... ...
 *         },
 *     }
 *     @endcode
 *
 * @subsubsection multi_vin_design_buffer_layout 3.3.4 Buffer Layout
 *
 * The source buffer concept applies in the multi-VIN design.<br>
 *
 * Every source buffer output window can be arranged in the canvas layout. The application must use the
 * following rules for the buffer layout design.<br>
 *
 * @par Implementation:
 *
 *   - The source buffers combined into the same canvas must be in the same type of canvas, either preview or encode.
 *   - The source buffer input size of each channel should not exceed the VIN channel resolution.
 *   - The source buffer output size and offset should not exceed the canvas resolution.
 *   - The source buffer input size in the channel layout and the output size in canvas layout can be changed on the
 *     fly to serve as the digital pan / tilt / zoom (DPTZ) effect for each channel.
 *   - The source buffer output size can be 0x0 to function as a turning off source buffer. When the output size is
 *     0x0, Ambarella recommends setting the buffer type as "off".
 *   - The source buffer output size can be different for each of the channels.
 *   - The source buffer output region can be overlapped with other source buffer output regions in the canvas layout
 *     to act as a PIP effect.
 *   - The source buffer output region can be overlapped only when they have the same buffer type and in the same canvas.
 *   - The source buffer type must be the same for all channels.
 *
 * @par Usage:
 *
 *   - "max_output {width, height}" is used to specify the maximum output width / height of each source buffer.
 *   - "input {offset_x, offset_y, width, height}" is used to specify the input window of each source buffer.
 *     The main buffer input window is cropped from the sensor (vsrc) resolution, and the other source buffer
 *     input window is cropped from the main buffer output window.
 *   - "output {offset_x, offset_y, width, height}" is used to specify the output window of each source buffer
 *     in canvas. The output offset is in the canvas coordinate.
 *
 * @par Example:
 * @code {.c}
 *     chan_0 {
 *         ... ... ...
 *         main = {
 *             max_output = {1920, 0},
 *             input      = {   0, 0, 1920, 1080},
 *             output     = { 960, 0,  960, 1080},
 *         },
 *
 *         second = {
 *             ... ... ...
 *         },
 *
 *         third = {
 *             max_output = {1920, 0},
 *             input      = {   0, 0,  960, 1080},
 *             output     = { 960, 0,  960, 1080},
 *         }
 *
 *         fourth = {
 *             ... ... ...
 *         },
 *
 *         fifth = {
 *             ... ... ...
 *         },
 *     }
 * @endcode
 *
 * @subsubsection multi_vin_design_pyramid_layout 3.3.5 Pyramid Layout
 *
 * Pyramid buffers are generated by the CV5x / CV7x DSP and are used to perform a video content analysis (VCA).
 * CV5x / CV7x support generating up to six pyramid layers.<br>
 *
 * The pyramid can choose its input source buffer from one of the Main / Second / Third / Fourth / Fifth source
 * buffers in the same channel.  The pyramid's first layer size is the same as its input buffer size. When the
 * input source buffer is one of the sub-buffers, it cannot be put into the canvas for preview or encode.
 * Consequently, if the pyramid is generated from the main buffer, the main buffer still can be put into the
 * canvas and used as an encode source.<br>
 *
 * However, it is recommended to use one of the sub-buffers for the pyramid input.  This saves DRAM bandwidth,
 * as sub-buffers can be smaller.  Typically, the fifth source buffer is the best choice for the pyramid input.<br>
 *
 * The six layers of the pyramid buffer are different sizes determined by the scale type. CV5x / CV7x support two scale
 * types:  when the scale type is 0, the width and / or height of each layer is 1 / sqrt(2) of the previous layer.
 * When the scale type is 1, the width and / or height is half the size of the previous layer.<br>
 *
 * The actual size of each layer is determined by the pyramid input buffer size and scale type. However, CV5x / CV7x also
 * support cropping from the output pyramid layer by specifying the crop window on the active window of the
 * pyramid layer.<br>
 *
 * @par Implementation:
 *
 *   - The scale type can be 0 or 1.
 *   - The buffer can come from an external buffer.  When buf_addr is valid, DSP generates the pyramid buffers
 *     from the external buffer address.  When buf_addr is 0, DSP generates the pyramid buffers in the internal
 *     memory.  If buf_addr is valid, then buf_size also is valid.
 *
 * There are two methods for allocating and maintaining the pyramid buffers: the pyramid auto-generation mode
 * and the pyramid manual-feed mode. For the auto-generation mode, DSP is responsible for the allocation and
 * maintenance of pyramid buffers. Each time, when DSP generates a group of pyramid buffers, it reports to Arm
 * automatically. For the manual-feed mode, Arm takes charge of the allocation and maintenance of the pyramid
 * buffers. Each time the user application wants a group of pyramid buffers, it feeds an empty group to DSP.
 * When DSP fills the pyramid data into the buffers, it reports them back to Arm. For more details, refer to
 * the <em>Ambarella CV5x DG Flexible Linux SDK Video Process</em> document.<br>
 *
 * @par Usage:
 *
 *   - "input_buf_id" is used to specify the input source buffer ID in this channel.
 *   - "scale_type" is used to specify the pyramid layer scale ratio.
 *   - "buf_addr" is used to specify the external buffer address in the auto-generation mode.  It is 0 when
 *     the pyramid is from DSP's internal buffer.  In the manual-feed mode, it must be 0 as its pyramid
 *     buffer pool is allocated by the image audio video (IAV) driver.
 *   - "buf_size" in the auto-generation mode is used to specify the total external buffer size to store all
 *     of the pyramid layers.  It is valid only when the "buf_addr" is specified.  The total buffer size includes
 *     up to six layers, with 4x ~ 8x for circular usage.  In the manual-feed mode, it also can be used to specify
 *     a fixed pyramid buffer pool size.  When it is specified, the IAV driver will not reallocate the pyramid
 *     buffer pool again even if the required pool size is changed.
 *   - "manual_feed" is used to enable the manual-feed mode.  0: pyramid auto-generation mode; 1: pyramid
 *     manual-feed mode.
 *   - "item_num" is used to specify the number of pyramid buffers in the pyramid manual-feed mode. It must be
 *     within the range of [4, 8].  When the setting is 0, it uses 4 as a default.
 *   - "layer_map" is used to specify which layers are not enabled to reduce the DRAM bandwidth. To enable all
 *     six layers, set this to 0x3F.
 *   - "crop_win {offset_x, offset_y, width, height}" is used to specify the output window of each pyramid layer
 *     buffer. The default value {0,0,0,0} refers to the pyramid layer's active window without cropping, rather
 *     than the window with the size 0x0.
 *
 * @par Example:
 *
 * @code {.c}
 *     pyramid = {
 *	       input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
 *         scale_type = 0,		-- 0: 1/sqrt(2)	1: 1/2
 *         buf_addr = 0,
 *         buf_size = 0,
 *         manual_feed = 0,
 *         item_num = 0,
 *         layer_map = 0x3F,	-- 0: means disable all pyramid layers
 *         --[[For each pyramid layer, the input is always full sized Main.
 *             And the full sized pyramid is generated according to Main size and the scale_type.
 *             The output pyramid is cropped from the full sized pyramid.
 *             Offset 0x0 with size 0x0 means the full pyramid output without cropping.
 *         --]]
 *
 *         layers = {
 *             {
 *                 crop_win	= {0, 0, 0 ,0},
 *             },
 *             {
 *                 crop_win	= {0, 0, 0 ,0},
 *             },
 *             {
 *                 crop_win	= {0, 0, 0 ,0},
 *             },
 *             {
 *                 crop_win	= {0, 0, 0 ,0},
 *             },
 *             {
 *                 crop_win	= {0, 0, 0 ,0},
 *             },
 *             {
 *                 crop_win	= {0, 0, 0 ,0},
 *             },
 *         },
 *		},
 * @endcode
 *
 * @subsubsection multi_vin_design_canvas_layout 3.3.6 Canvas Layout
 *
 * The multi-VIN design includes a new memory layout: canvas layout (also the concept behind the
 * encode source memory).<br>
 *
 * In the multi-VIN design, each source buffer (from the main to the fourth buffer) can output the
 * data for each channel using different resolutions.  The application can combine the field of
 * view (FoV) of each source buffer output of each channel together into one canvas so that the stream
 * encoded from this canvas can cover several FoVs from different VIN channels. Alternatively, the
 * application can crop the separate streams from encoding, using different areas of the blend view canvas.<br>
 *
 * @par Implementation:
 *
 *   - The maximum canvas number is 10.
 *   - The canvas type must be either the preview or encode.  There is no off type.
 *   - The source buffer outputs combined in the same canvas must be in the same buffer type,
 *     preview, encode, or off.
 *
 * @par Typical configuration:
 *
 *   - Different source buffer output content is aligned seamlessly in the horizontal or vertical
 *     direction, such as the Nx1 or 1xN order.
 *   - One source buffer output is overlapped on another source buffer output as the PIP effect.
 *
 * @par Usage:
 *
 *   - "type" is used to specify the canvas type.  It can be either "encode" or "prev". There is no "off"
 *     type for canvas. If the application requires to turn off the canvas, it has to reconfigure the
 *     system and remove the canvas definition.  If canvas type is previewed, it outputs the YUV422 format
 *     with UV interleaved data. If canvas type is encoded, it outputs the YUV420 format with UV interleaved data.
 *   - "size {width, height}" is used to specify the canvas resolution.
 *   - "source" is used to specify the source buffer of channels to canvas. DSP follows the source buffer
 *     declare order to put channel source buffer data in this field. The latter source buffer is put in
 *     with a higher Z order and may cover the source buffer with a lower Z order.  The channels whose source
 *     buffer are put to the same canvas must have the same "idsp_fps".
 *   - "vout_id" is used to specify VOUT. If the value is set to 1, VOUT1 (like HDMI, CVBS) will be used to
 *     show the preview canvas. If the value is set to 0, VOUT0 (like LDC, DSI) will be used to show the
 *     preview canvas.
 *   - "vout_YUV422" is used to specify the YUV format of "prev" type canvas.  If the value is set to 1, its
 *     YUV format is YUV422.  Then VOUT captures the display data from it directly to show out.  If the value
 *     is set to 0, its YUV format is YUV420, which is the same as other "encode" type canvases. The VOUT then
 *     converts it to YUV422 before showing out.
 *   - "extra_dram_buf" specifies the extra DRAM frames for the canvas.
 *   - "enable_order" enables channel order within the current canvas. It must be enabled in PIP cases.
 *   - "clear_background" enables clearing the whole canvas at the initial stage when entering the preview state.
 *     It clears the background garbage when the canvas is not fully covered by its source buffers.
 *
 * @par Example:
 *
 * @code {.c}
 *     canvas = {
 * 		{
 * 			type = "encode",
 * 			size = {1920, 1080},
 * 			source = {"chan_0.main", "chan_1.main", },
 * 			extra_dram_buf = 0,
 * 			enable_order = 1,
 * 			clear_background = 0,
 * 		},
 * 		{
 * 			type = "prev",
 * 			size = {1920, 1080},
 * 			source = {"chan_0.third", "chan_1.third", },
 * 			vout_id = 1,
 * 			vout_YUV422 = 0,
 * 			extra_dram_buf = 0,
 * 			enable_order = 1,
 * 			clear_background = 1,
 * 		},
 *     }
 * @endcode
 *
 * @subsubsection multi_vin_design_stream_configuration 3.3.7 Stream Configuration
 *
 * Single-VIN system designs enable easy configuration of the stream encode size and offset. If required,
 * the application can dynamically change the stream offset.<br>
 *
 * @par Implementation:
 *
 *   - For the multi-VIN design, use the source canvas for the encode source rather than the source buffer.
 *   - The encode source ID must be the source canvas ID, not the source buffer ID.
 *   - All encoding features of the multi-VIN stream are the same as the single VIN design.
 *
 * @par Usage:
 *
 *   - Up to 16 streams are supported.
 *   - "id" specifies the stream ID. Ambarella recommends keeping the same value as the stream index, starting from zero.
 *   - "max_size" specifies the maximum stream resolution.
 *   - "max_M" specifies the maximum GOP M for the stream. For B frame, max_M > 1.  For MJPEG encoding, max_M = 0.
 *   - "fast_seek_enable" enables the fast seek frame.
 *   - "two_ref_enable" enables two forward reference frames.
 *   - "max_svct_layers_minus_1" specifies the maximum SVC-T layers options. 0: no SVC-T; 1: 2 layers SVC-T.
 *   - "max_num_minus_1_ltrs" specifies the maximum long-term number minus 1.
 *   - "possible_enc_src_map" specifies the encoding source canvas map for the encoding stream. 0 (default): all canvases.
 *     Users must specify when the stream will be encoded with an advanced OP. Advanced GOP requires more memory resources
 *     to be allocated for the source canvases.  By default, the DSP allocates memory resources for all canvases,
 *     so specifying the designated source canvases can save memory.
 *   - "codec_enable" enables the stream CODEC.
 *
 *     0: HEVC / H264 / MJPEG
 *     1: HEVC / MJPEG
 *     2: H264 / MJPEG,
 *     3: MJPEG only
 *
 *   - "efm_enable" specifies if the current stream can run encode from memory (EFM).
 *   - "efm_buf_num" specifies the number of frame buffers allocated for the EFM. These frame buffers are allocated
 *     by the DSP and occupy extra memory.
 *   - "efm_size" specifies the EFM frame buffer resolution.
 *
 * @par Example:
 * @code {.c}
 *     stream_0 = {
 *     	   id = 0,
 *     	   max_size = {1920, 1080},
 *     	   max_M = 1,
 *     	   fast_seek_enable = 0,
 *     	   two_ref_enable = 0,
 *     	   max_svct_layers_minus_1 = 0,
 *     	   max_num_minus_1_ltrs = 0,
 *     	   possible_enc_src_map = 0,
 *     	   codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
 *     	   efm_enable = 0,
 *     	   efm_buf_num = 0,
 *     	   efm_size = {0, 0},
 *     }
 * @endcode
 *
 * @subsubsection multi_vin_design_vout_layout 3.3.8 VOUT Layout
 *
 * In the multi-VIN design, the VOUT layout is used to show a single view (PIP) of preview mode, or multiple
 * views of installation mode.<br>
 *
 * As the source buffer output size can be configured as 0x0, the application disables one of the VOUT channels,
 * or switches the channels in the background and foreground in the PIP view on the fly. This is useful for users
 * entering multi-channel product installation mode.<br>
 *
 * The third and fourth source buffers are connected to VOUT 1 / 2 / 3, making the VOUT layout rule the same
 * as the buffer layout.<br>
 *
 * @par Implementation:
 *
 *   - VOUT content comes from the source canvas, as well as the encoded streams.
 *   - VOUT supports independent view, blended view, and PIP view, along with encoded streams.
 *
 * @subsection multi_vin_design_sensor_driver_installation 3.4 Sensor Driver Installation
 *
 * The multi-VIN design can require different sensors mounted to the various VIN controllers. As each sensor
 * possesses its own sensor driver, users must install each sensor driver accordingly. For more detail, you
 * can take reference from @ref page_sys_sensor_driver_installation
 *
 * - - - -
 *
 * @section multi_vin_design_examples 4 Examples
 *
 * This chapter provides examples for configuring various layout settings in the Lua script and for running
 * the time update layout.<br>
 *
 *   - Section @ref multi_vin_design_quad_sensors_with_a_long_cable_through_max9296_4_1
 *   - Section @ref multi_vin_design_dual_channels_from_a_single_sensor_4_2
 *   - Section @ref multi_vin_design_dual_channels_from_the_sensor_and_the_yuv_raw_data
 *   - Section @ref multi_vin_design_dual_sensors_with_different_modes_from_max9296
 *   - Section @ref multi_vin_design_dual_channels_from_imx264_with_dual_vsrc_ctx
 *   - Section @ref multi_vin_design_quad_sensors_with_imx274
 *   - Section @ref multi_vin_design_multiple_yuv_input
 *   - Section @ref multi_vin_design_quad_sensors_through_bridge_chip
 *
 * @subsection multi_vin_design_quad_sensors_with_a_long_cable_through_max9296_4_1 4.1 Quad Sensors with a Long Cable through MAX9296
 *
 * <em> Example 7: For Quad Sensors, Start Ten Streams from Nine Canvas View. One is a Blend View
 *      for Encoding, and the Others are Normal Views for Encoding. </em>
 *
 * @subsubsection multi_vin_design_test_commands_4_1 4.1.1 Test Commands
 *
 * The command sequence for the test command is as follows:<br>
 * @code
 * board # init.sh --na
 * board # modprobe max9296 id=0x0303 vinc_id=0xb8
 * board # modprobe os08a10_mipi_brg fsync=1
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg quad_remote_sensors.lua
 * board # test_encode -S0 -b 0 -H 3840x2160 -e
 * board # test_encode -S1 -b 0 -m 3840x2160 --frame-factor 1/6 -e
 * board # test_encode -S2 -b 1 -H 1920x1080  -e
 * board # test_encode -S3 -b 3 -H 1920x1080  -e
 * board # test_encode -S4 -b 5 -H 1920x1080  -e
 * board # test_encode -S5 -b 7 -H 1920x1080  -e
 * board # test_encode -S6 -b 2 -H 1280x720  -e
 * board # test_encode -S7 -b 4 -H 1280x720  -e
 * board # test_encode -S8 -b 6 -H 1280x720  -e
 * board # test_encode -S9 -b 8 -H 1280x720  -e
 * @endcode
 *
 * @subsubsection multi_vin_design_lua_script_4_1 4.1.2 Lua Script
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is:
 * <a href="script/quad_remote_sensors.lua" target="_blank"><b>quad_remote_sensors.lua</b></a>.
 *
 * @subsection multi_vin_design_dual_channels_from_a_single_sensor_4_2 4.2 Dual Channels from a Single Sensor
 *
 * <em>Example 8: For Dual Channels from a Single VIN: Start Six Streams from Canvas View. </em>
 *
 * @subsubsection multi_vin_design_test_commands_4_2 4.2.1 Test Commands
 *
 * The following shows the command sequence for tests:<br>
 * @code
 * board # init.sh --na;
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8)     // For CV72
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg dual_chan_single_sensor.lua
 * board # test_encode -S 0 -H 3840x2160 -b 0 -e -S 1 -H 3840x2160 -b 1 -e -S 2 -m 3840x2160 -b 2 --frame-factor 1/6 -e -S 3 -m 3840x2160 -b 3 --frame-factor 1/6 -e
 * @endcode
 *
 * @subsubsection multi_vin_design_lua_script_4_2 4.2.2 Lua Script
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is:
 * <a href="script/dual_chan_single_sensor.lua" target="_blank"><b>dual_chan_single_sensor.lua</b></a>.
 *
 * @subsection multi_vin_design_dual_channels_from_the_sensor_and_the_yuv_raw_data 4.3 Dual Channels from the Sensor and the YUV Raw Data
 *
 * <em>Example 9: Dual Channels from the Sensor and YUV Raw Data: Start Two Streams from Two Canvas Views.
 *     Channel 0 Captures Data from Sensor; Channel 1 Captures the YUV Raw Data Fed by User Application. </em>
 *
 * @subsubsection multi_vin_design_test_commands_4_3 4.3.1 Test Commands
 *
 * The command sequence is shown below:<br>
 * @code
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 lane=2 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8 lane=2)     // For CV72
 * board # modprobe ambdd video_type=5 cap_cap_w=1920 cap_cap_h=1080 video_fps=17066667 sensor_id=0x3014
 * board # test_aaa_service -a &
 * board # test_mempart -m 2 -s 0x4000000
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_dual_chan_single_sensor.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1
 * board # test_efm -t 3 -s 1920x1080 -i cap_raw_raw_1920x1080_3840.raw -T 1
 * board # test_encode -A -h 1080p –b 0 -e -B -h 1080p -b 4 –e
 * @endcode
 *
 * @subsubsection multi_vin_design_lua_script_4_3 4.3.2 Lua Script
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is:
 * <a href="script/cv5_dual_chan_single_sensor.lua" target="_blank"><b>cv5_dual_chan_single_sensor.lua</b></a>.
 *
 * @subsection multi_vin_design_dual_sensors_with_different_modes_from_max9296 4.4 Dual Sensors with Different Modes from MAX9296
 *
 * <em>Example 10: For Dual Sensors with Different Modes from MAX9296: Start Two Streams from Canvas View. </em>
 *
 * @subsubsection multi_vin_design_test_commands_4_4 4.4.1 Test Commands
 *
 * The command sequence is shown below:<br>
 * @code
 * board # init.sh --na;
 * board # modprobe max9296 id=0x201 vc=1 dts_addr=1
 * board # modprobe os08a10_mipi_brg brg_id=0x1
 * board # modprobe imx290_mipi_brg brg_id=0x2 slave=1
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg cv5_dual_chan.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_encode -A -H 3840x2160 –b 0 -e –B –H 1080p –b 4 -e
 * @endcode
 *
 * @subsubsection multi_vin_design_lua_script_4_4 4.4.2 Lua Script
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is:
 * <a href="script/cv5_dual_chan.lua" target="_blank"><b>cv5_dual_chan.lua</b></a>.
 *
 * @subsection multi_vin_design_dual_channels_from_imx264_with_dual_vsrc_ctx 4.5 Dual Channels from IMX264 with Dual Vsrc_ctx
 *
 * <em>Example 11: Dual Channels from IMX264 with Dual Vsrc_ctx: Divide Frames into Two Channels Half-by-Half
 *     and Start Two Streams from Two-Canvas View. </em>
 *
 * @subsubsection multi_vin_design_test_commands_4_5 4.5.1 Test Commands
 *
 * The command sequence is shown below:<br>
 * @code
 * board # init.sh --na;
 * board # modprobe imx264 vinc_id=8 bus_id=3 frameset=2		// frameset must be set to 2
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_imx264_2xframe_2432x2048_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_encode -A -H 2432x2048 –b 0 -e -B -h 2432x2048 -b 2 –e
 * @endcode
 *
 * @subsubsection multi_vin_design_lua_script_4_5 4.5.2 Lua Script
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is:
 * <a href="script/cv5_imx264_2xframe_2432x2048_linear.lua" target="_blank"><b>cv5_imx264_2xframe_2432x2048_linear.lua</b></a>.
 *
 * @note
 *   - idsp_fps is set to 0. This leaves the IDSP to run its own frame down-sampling for channel 0 and channel 1.
 *     With the dual VSRC, channel 0 and channel 1 idsp_fps will be 15 when the VIN fps is set to 30.
 *   - The vsrc_ctx_pattern and the vsrc_ctx_pattern_mask are specified referring to the IMX264 sensor specification.
 *
 * @subsection multi_vin_design_quad_sensors_with_imx274 4.6 Quad Sensors with imx274
 *
 * Set up 4x imx274 sensors connected to CV5 EVK board. One sensor board includes two independent sensors connected to VIN8 and VIN11 controllers,
 * respectively. The other sensor board has two independent sensors, which connected VIN0 and VIN4 controllers, at the same time, highlight
 * DCPHY0 needs to be connected with DCPHY0 (converter board slot), and DCPHY1 needs to be connected with DCPHY1 (converter board slot).<br>
 *
 * @image html 4x_imx274_connect_to_cv5_EVK.png "4x imx274 Connect to CV5 Board."
 *
 * <em>Example 12: For Quad Sensors with imx274: Start Four Streams from Canvas View. </em>
 *
 * @subsubsection multi_vin_design_test_commands_4_6 4.6.1 Test Commands
 *
 * The command sequence is shown below:<br>
 * @code
 * board # init.sh --na;
 * board # modprobe imx274_mipi vinc_id=0x40b8;
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg cv5_four_vin_4k_encode.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_encode -S 0 -h 3840x2160 -b 0 -e
 * board # test_encode -S 1 -h 3840x2160 -b 1 -e
 * board # test_encode -S 2 -h 3840x2160 -b 2 -e
 * board # test_encode -S 3 -h 3840x2160 -b 3 -e
 * @endcode
 *
 * @subsubsection multi_vin_design_lua_script_4_6 4.6.2 Lua Script
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is as follows:
 * <a href="script/cv5_four_vin_4k_encode.lua" target="_blank"><b>cv5_four_vin_4k_encode.lua</b></a>.
 *
 * @subsection multi_vin_design_multiple_yuv_input 4.7 Multiple YUV Input
 *
 * <em>Example 13:  Multiple YUV Input: Dual YUV Input from LT6911. </em>
 *
 * @subsubsection multi_vin_design_preparation_4_7 4.7.1 Preparation
 *
 * This feature uses VINC0 and VINC8 on I2C bus 5 and 3. The ambvin section must be added to the related
 * I2C section in the DTS as shown below:<br>
 * @code {.c}
 * --- a/bsp/cv5_timn.dts
 * +++ b/bsp/cv5_timn.dts
 * @@ -145,11 +145,6 @@
 *  &i2c0 {
 *         status = "ok";
 *
 * -       ambvin0@01 {
 * -               compatible = "ambarella,ambvin";
 * -               reg = <0x01>;  // fake address, will be overwritten in runtime
 * -       };
 * -
 *         nau8810: codec@1a {
 *                                 compatible = "nuvoton,nau8810";
 *                                 #sound-dai-cells = <0>;
 * @@ -201,6 +196,10 @@
 *  #else
 *         status = "disabled";
 *  #endif
 * +       ambvin0@01 {
 * +               compatible = "ambarella,ambvin";
 * +               reg = <0x01>;   // fake address, will be overwritten in runtime
 * +       };
 *
 *         fan: amc6821@1a {
 *                 compatible = "ti,amc6821";
 * @endcode
 *
 * @subsubsection multi_vin_design_test_commands_4_7 4.7.2 Test Commands
 *
 * 1. First, set up two 1080P HDMI outputs on any board. Call them board 1 and board 2.<br>
 * @code {.c}
 * board # init.sh --imx274_mipi
 * board # test_aaa_service -a &
 * board # test_encode -i0 --hdmi 1080p
 * @endcode
 *
 * 2. Next, connect the HDMI output of board 1 to the HDMI input of LT6911. Then, connect the HDMI output of
 *    board 2 to LT6911's HDMI input, mounting the two LT6911 parts into the VIN slot of board 3.<br>
 * @code {.c}
 * board # init.sh --na
 * board # modprobe lt6911 vinc_id=0xf08
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg cv5_dual_vin_yuv.lua  --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsubsection multi_vin_design_lua_script_4_7 4.7.3 Lua Script
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is:
 * <a href="script/cv5_dual_vin_yuv.lua" target="_blank"><b>cv5_dual_vin_yuv.lua</b></a>.
 *
 * @note
 *   - The vsrc mode must be 0 when the YUV input is used.
 *
 * @subsection multi_vin_design_quad_sensors_through_bridge_chip 4.8 Quad Sensors through Bridge Chip
 *
 * Set up 4x os05a10 sensors connected to CV72 GA EVK board. CV72 supports 3x native VIN controllers, it can
 * support three independent sensors. Two independent sensors connected to VIN8 and VIN11 controllers, respectively.
 * The other two sensor connected to the same VIN0 controller through bridge chip B8N.
 * At the same time, SLVS + DPHY VIN slot needs to be connected with SLVS + DPHY (sensor board slot), and DCPHY0
 * needs to be connected with B8 MIPI OUT slot (sensor board slot).<br>
 *
 * @image html 4x_os05a10_connect_to_cv72_ga_board.png "4x os05a10 Connect to CV72 Ga Board."
 *
 * <em>Example 14: Quad Sensors through bridge chip: Start Four Streams from Canvas View. </em>
 *
 * @subsubsection multi_vin_design_preparation_4_8 4.8.1 Preparation
 *
 * Macro CONFIG_BOARD_TYPE_B8N_LOCAL_QUAD_SEN need to be defined in the DTS as shown below:<br>
 * @code {.c}
 * --- a/bsp/cv72_gage.dts
 * +++ b/bsp/cv72_gage.dts
 * @@ -21,6 +21,7 @@
 *  #endif
 *
 *  #define PCI_QUIRK_PCI_ADDR 0x02000000
 * +#define CONFIG_BOARD_TYPE_B8N_LOCAL_QUAD_SEN
 * @endcode
 *
 * @subsubsection multi_vin_design_test_commands_4_8 4.8.1 Test Commands
 *
 * The command sequence is shown below:<br>
 * @code
 * board # init.sh --na;
 * board # modprobe os05a10 vinc_id=0xb8 fsync=1 && modprobe b8 id=0x30 set_vin_first=1 && modprobe os05a10_mipi_brg fsync=1;
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg cv72_four_vin_5m_encode.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_encode -S 0 -h 2560x1920 -b 0 -e
 * board # test_encode -S 1 -h 2560x1920 -b 1 -e
 * board # test_encode -S 2 -h 2560x1920 -b 2 -e
 * board # test_encode -S 3 -h 2560x1920 -b 3 -e
 * @endcode
 *
 * @subsubsection multi_vin_design_lua_script_4_8 4.8.2 Lua Script
 *
 * Lua script to configure the VIN / canvas / buffer layouts / streams is as follows:
 * <a href="script/cv72_four_vin_5m_encode.lua" target="_blank"><b>cv72_four_vin_5m_encode.lua</b></a>.
 *
 * - - - -
 *
 * @section multi_vin_design_on_the_fly_settings 5 On the fly Settings
 *
 * This chapter provides examples of on the fly settings. The settings enable multi-channel parameters to be
 * changed independently during the preview / encoding state, such as channel orders, preview buffer DPZ, and
 * preview buffer on / off. The unit test tool (test_multi_chan) is used for the on the fly settings.<br>
 *
 * @par Implementation limitations:
 *
 *   - User applications cannot increase or decrease the number of canvases on the fly.
 *   - User applications cannot perform DPZ for main buffers on the fly.
 *   - User applications cannot change the canvas source of the source buffers on the fly.
 *
 * The chapter sections are as follows:<br>
 *
 *   - Section @ref multi_vin_design_digital_pan_tilt_zoom
 *   - Section @ref multi_vin_design_turn_the_preview_buffer_on_off
 *   - Section @ref multi_vin_design_dump_multi_channel_configurations
 *
 * @subsection multi_vin_design_digital_pan_tilt_zoom 5.1 Digital Pan / Tilt / Zoom (DPTZ)
 *
 * This user application can dynamically change the input size / offset of the preview buffers within their
 * main buffers. DPTZ can also change the output size / offset of the preview buffers within the canvases.<br>
 *
 * @note
 *   - To upscale the preview buffers on the fly, assign the maximum output width through the Lua script
 *     when preview state is entered.  This is necessary because the maximum output width cannot be changed
 *     on the fly.
 *   - The maximum zoom-in and zoom-out factors of each preview buffer is the same as the single channel cases.
 *
 * <em>Example 13: For DPTZ On the Fly: Third Buffer (800x600) of Channel 1 is Cropped (Offset 100x100 from
 *     Top Left) and Down-Scaled (from 720p to 800x600) from Main Buffer (1080p).</em>
 *
 * @code
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8)     // For CV72
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg multi_chan_vin0_1080p_vin1_4M_linear.lua --hdmi 1080p
 * board # test_multi_chan -c 1 -J --binsize 1280x720 --binoffset 100x100 --boutsize 800x600 --boutoffset 160x160
 * @endcode
 *
 * <em>Example 14: For DPTZ On the Fly: Third Buffer (1080p) of Channel 1 is Cropped (Offset 480x270 from
 *     Top Left) and Upscaled (from 960x540 to 1080p) from Main Buffer (1080p). </em>
 *
 * @code
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8)     // For CV72
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg multi_chan_vin0_1080p_vin1_4M_linear.lua --hdmi 1080p
 * board # test_multi_chan -c 1 -J --binsize 960x540 --binoffset 480x270 --boutsize 1920x1080 --boutoffset 0x0
 * @endcode
 *
 * <em>Example 15: For DPTZ On the Fly: Change Input, Output Offset, and Size of Third Buffer of Channel 1
 *     On the Fly with Direction Keys. </em>
 *
 * @code
 * board # init.sh --imx274_mipi
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg multi_chan_vin0_1080p_vin1_4M_linear.lua --hdmi 1080p
 * board # test_multi_chan -c 1 -J --binsize m		// tune input size
 * board # test_multi_chan -c 1 -J --binoffset m		// tune input offset
 * board # test_multi_chan -c 1 -J --boutsize m		// tune output size
 * board # test_multi_chan -c 1 -J --boutoffset m	// tune output offset
 * @endcode
 *
 * @subsection multi_vin_design_turn_the_preview_buffer_on_off 5.2 Turn the Preview Buffers On / Off
 *
 * To turn off the preview buffers on the fly, the input and output sizes must be set to zero.
 * The buffers can be enabled again by setting the corresponding DPTZ parameters.<br>
 *
 * <em> Example 16: Turn Off Preview Buffers On the Fly: Power Off Third Buffer of Channel 1.</em>
 * @code
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8)     // For CV72
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg multi_chan_vin0_1080p_vin1_4M_linear.lua --hdmi 1080p
 * board # test_multi_chan -c 1 -J --binsize 0x0 --boutsize 0x0
 * @endcode
 *
 * @subsection multi_vin_design_dump_multi_channel_configurations 5.3 Dump Multi-Channel Configurations
 *
 * To dump the multi-channel configurations for debugging or other purposes, use the multi-channel format
 * of the Lua script with test_multi_chan. The printed data follows the multi-channel Lua script file format.
 * Users can also copy the printed content and save it directly to the Lua script.<br>
 *
 * <em>Example 17: Dump the Multi-Channel Configuration. </em>
 * @code
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3 // For CV5 or CV52
 * (or board # modprobe imx274_mipi vinc_id=8)     // For CV72
 * board # test_aaa_service -a &
 * board # test_encode -i 0 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_multi_chan -s
 * @endcode
 *
 * - - - -
 *
 * @section multi_vin_design_faq 6 FAQ
 *
 * <B>Question 1: </B> Why does the DSP hang when multiple streams are encoded from the same canvas?<br>
 * <B>Answer: </B> Similar to the single-channel design, the DSP uses the minimum possible number of frames
 *    for the canvas in the multi-channel design to reduce DRAM size. When multiple streams are encoded
 *    from the same canvas, the DSP has a race condition for frame release. The application must specify
 *    the “--extra-buf N-1” option for the canvas if there are N streams encoded from this canvas.<br>
 *
 * <B>Question 2: </B> Does CV5x / CV7x support a multi-channel design from a single-sensor input?<br>
 * <B>Answer: </B> Yes.  This is called the "IDSP virtual channel" design case described in Section @ref
 *    multi_vin_design_idsp_virtual_channels. Although the "IDSP virtual channel" case requires more
 *    system resources than the single channel, it still requires less than the dual channels.<br>
 *    As long as the system resources are sufficient, the application can run up to four "IDSP virtual channels"
 *    from a single sensor.<br>
 *
 * <B>Question 3: </B> Why are there artifacts at the bottom of the channels?<br>
 * <B>Answer: </B> For the multi-VIN design, the DSP requires that each channel output height in the
 *    canvas is a multiple of 16. If the height is a multiple of eight, the DSP will repeat the last
 *    line eight times. As a result, the application can use the channel process order to have the
 *    latter channel output content cover the repeated lines of the former. If the latter channel
 *    content does not cover the repeated lines, users will most likely see artifacts at the bottom
 *    of the channel views.<br>
 *
 * <B>Question 4: </B>  What is the relationship between the sensors, the physical VIN controllers,
 *    and the IDSP channels?<br>
 * <B>Answer: </B> The following table provides a list of typical use cases for different combinations
 *    of sensors, physical VIN controllers, and the IDSP channels.<br>
 *
 * <table>
 * <caption id="typical_use_cases_for_different_sensors"> Typical Use Cases for Different Sensors.</caption>
 * <tr><th> Sensor <th> Physical VIN Controllers <th> IDSP Channels <th> Typical Use Cases
 * <tr><td align="center"> 1
 *     <td align="center"> 1
 *     <td align="center"> 1
 *     <td> Standard single-sensor camera
 * <tr><td align="center"> 1
 *     <td align="center"> 1
 *     <td align="center"> >1
 *     <td> IDSP virtual channel
 * <tr><td align="center"> >1
 *     <td align="center"> 1
 *     <td align="center"> >1
 *     <td> Multi-sensor camera where the number of sensors exceeds the number of physical VINs.<br>
 *          An external SERDES chip, such as B6, is needed to mux these sensors together into the line-interleaved format.<br>
 * <tr><td align="center"> >1
 *     <td align="center"> >1
 *     <td align="center"> >1
 *     <td> Standard multi-sensor cameras
 * <tr><td align="center"> >1
 *     <td align="center"> >1
 *     <td align="center">  1
 *     <td> Multiple sensors are combined into one IDSP output.<br>
 *          1: Color filter array (CFA) sensor + infrared (IR) sensor fusion.<br>
 *          2: CFA sensor + thermal sensor fusion.<br>
 *          Simple blending with an optional negative image with a Chroma overlay based on the temperature.<br>
 * </table>
 *
 * - - - -
 *
 * @section multi_vin_design_doc_license 7 License
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
 */
/*!
 * @file multi_pass.h
 * @brief
 * @version 0.1
 * @date 2024-01-08
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
 * @page fs_adv_multi_pass ADVANCED - Multi-Pass
 *
 * @section multi_pass_features 1. Multi-Pass Features
 *
 * Multi-Pass on the Ambarella CV5x, CV7x, and CV3x systems on chip (SoCs) is a multi-channel
 * design leveraging multi-region dewarp mode (mode 1).<br>
 * This chapter describes the usage of multiple passes on the Ambarella CV5x / CV7x / CV3x SoC.<br>
 *
 * The following diagram provides an overview of the multi-pass design.
 *
 * @image html multi_pass_mode1_v6.jpg "Figure 1-1. Multi-Pass."
 *
 * First pass is executed in regular mode (mode 0 or mode 5), channel 0. Second pass is executed in mode 1, channel 1.
 *
 * @note
 * - The mode-1 channel's input can be either a single-view canvas or multi-view canvas.
 * - There can be multiple mode-1 channels. The number of mode-1 channels is decided
 *    by the maximum number of channels supported and their performance.
 * - Pyramid is not supported in the mode-1 channel.
 * - The sixth buffer is not supported in the mode-1 channel.
 * - Canvases serving as mode-1 channel input cannot be used as preview or encoding input.
 *   The canvas type must be "encode".
 * - The mode-1 channel's output sub-buffers cannot be placed into its source canvas.
 * - The mode-1 channel's main buffer is composed of multiple dewarp regions from a cropped
 *    window inside of its source canvas after running the dewarping operations for each region.
 * - The default warp region split is decided by `max_warp_input_width` and
 *    `max_warp_output_width`. Image audio video (IAV) splits the cropped window within the source
 *    canvas to ensure that each region's input width is within `max_warp_input_width` and the output
 *    width is within `max_warp_output_width`. Users are allowed to change the region configurations
 *    after preview if the default configuration cannot meet users' requirements.
 * - Sub-buffers from the mode-1 channel are not directly generated by the digital pan / tilt / zoom (DPTZ) operation from
 *    the main buffer. Instead, they are containers that store multiple dewarp regions.
 *    Rescaling is performed for each region separately.
 * - Performing DPTZ on the mode-1 channel's main buffer will affect the content in all sub-buffers
 *    of the mode-1 channel. Ambarella does not recommend changing the main buffer content after preview.
 *    Instead, users can update DPTZ for sub-buffers of the mode-1 channel.
 * - There might be performance overhead for multi-channel, because the scalers from these
 *    channels share the same hardware.
 * - Ambarella recommends choosing a low-resolution canvas (no greater than 1080p) as the mode-1
 *    channel input. While this helps improve performance, it also relieves the
 *    troubles of spliting regions in the mode-1 channel.
 *
 * <br>
 *
 * ---
 *
 * @section lua_multi_pass_configuration 2. Multi-Pass Configuration
 *
 * <B>Example: Multi-Pass Lua Configuration</B>
 *
 * @code
 * chan_0 = {
 * ........
 * }
 * chan_1 = {
 *     id = 1,
 *     vcap_mode_flags = 1,              -- mode 1
 *     src_from_canvas_enable = 1,       -- enable input from canvas flag
 *     src_canvas_id = 2,                -- specify source canvas id
 *     ...
 * }
 * _resource_config_ = {
 *    version = 1,
 *     log_level = 0,
 *     channels = {
  *        chan_0,
 *         chan_1,
 *     },
 *     canvas = {
 *         {
 *             type = "encode",
 *             size = {0, 0},
 *             source = {"chan_0.main",},
 *            extra_dram_buf = 0,
 *         },
 *         {
 *             type = "encode",
 *             size = {0, 0},
 *             source = {"chan_0.second",},
 *             extra_dram_buf = 0,
 *         },
 *         {
 *             type = "encode",
 *             size = {0, 0},
 *             source = {"chan_0.third",},
 *             extra_dram_buf = 0,
 *         },
 *         {
 *             type = "encode",
 *             size = {0, 0},
 *             source = {"chan_1.main",},
 *             extra_dram_buf = 0,
 *         },
 *         ...
 *     }
 * }
 * @endcode
 *
 *
 *
 * <br>
 *
 * ---
 *
 * @section multi_pass_example 3. Multi-Pass Examples
 *
 * @subsection example_multi_pass_1 Example 1: Input from Single-View Canvas
 * The Lua script can be found at <a href="script/multi_region_dewarp_from_canvas.lua" target="_blank"><b>here</b></a>.
 * @code
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg multi_region_dewarp_from_canvas.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --chan-vcap-mode-enable 1
 * board# test_encode -A -b 3 -H qfhd -e
 * board# test_multi_chan -c 1 -K --binsize 1920x1080
 * @endcode
 *
 * @subsection example_multi_pass_2 Example 2: Input from Multi-View Canvas
 * The Lua script can be found at <a href="script/multi_region_dewarp_from_multi_view_canvas.lua" target="_blank"><b>here</b></a>.
 * @code
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg multi_region_dewarp_from_multi_view_canvas.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --chan-vcap-mode-enable 1
 * board# test_encode -A -b 3 -H qfhd -e
 * board# test_multi_chan -c 1 -K --binsize 1920x1080
 * @endcode
 *
 */
/*!
 * @file ldc.h
 * @brief
 * @version 0.1
 * @date 2022-01-10
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
 * @page fs_adv_ldc ADVANCED - Lens Distortion Correction
 *
 * @section single_vin_ldc 1. Single VIN Lens Distortion Correction (LDC)
 *
 * @subsection lens_no_transform 1.1 Lens No Transform
 *
 * @image html sv_lens_no_trans.png "Figure 1-1. Single VIN Lens No Transform."
 *
 * @subsubsection lens_no_trans_exp Example 1: Lens No Transform
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 0 --ns 1024x768 --no 800x300
 * @endcode
 *
 * @subsection lens_rectilinear 1.2 Lens Rectilinear
 *
 * @subsubsection lens_rectilinear Example 2: Lens Rectilinear
 *
 * @image html sv_lens_rectilinear.png "Figure 1-2. Single VIN Lens Rectilinear."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 1
 * @endcode
 *
 * @subsubsection lens_trapezoid_warp Example 3: Lens Trapezoid Warp
 *
 * @image html sv_lens_trapezoid_warp.png "Figure 1-3. Single VIN Lens Trapezoid Warp."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 130 -R 1300 -m 1 --zv 2/1 --zth 8/9 --zbh 2/1
 * @endcode
 *
 * @subsubsection lens_adv_py Example 4: Lens Advance Pitch / Yaw
 *
 * @image html sv_lens_adv_py.png "Figure 1-4. Single VIN Lens Advance Pitch."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 185 -R 1844 -m 1 -v
 * board# test_ldc -c 0 -F 185 -R 1844 -m 1 --top-pitch 10 --bot-pitch 0 -v
 * @endcode
 *
 * @subsubsection lens_polar_warp Example 5: Lens Polar Warp
 *
 * @image html sv_lens_polar_warp.png "Figure 1-5. Single VIN Lens Polar Warp."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 142 -R 1350 -m 1
 * @endcode
 *
 * @subsubsection lens_eyeball_pan_tilt Example 6: Lens Eyeball Rotation: Pan / Tilt
 *
 * @image html sv_lens_pan_tilt.png "Figure 1-6. Single VIN Lens Pan / Tilt."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 1 -t 30
 * board# test_ldc -c 0 -F 180 -R 1024 -m 1 -p 15
 * @endcode
 *
 * @subsubsection lens_eyeball_rotate Example 7: Lens Eyeball Rotation: Rotate
 *
 * @image html sv_lens_rotate.png "Figure 1-7. Single VIN Lens Rotate."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 185 -R 1500 -m 1 --rotate -10
 * board# test_ldc -c 0 -F 180 -R 1500 -m 1 --rotate 10
 * @endcode
 *
 * @subsubsection lens_region_of_interest Example 8: Lens ROI
 *
 * @image html sv_lens_roi.png "Figure 1-8. Single VIN Lens ROI."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 1 --roi -100x-100
 * @endcode
 *
 * @subsection lens_pannini 1.3 Lens Pannini
 *
 * @image html sv_lens_pannini.png "Figure 1-9. Single VIN Lens Pannini."
 *
 * @subsubsection lens_pannini_exp Example 9: Lens Pannini
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 10 --pannini-loc 0.5
 * @endcode
 *
 *
 * @subsection lens_pincushion 1.4 Lens Pincushion
 *
 * @image html sv_lens_pincushion.png "Figure 1-10. Single VIN Lens Pincushion."
 *
 * @subsubsection lens_pincushion_exp Example 10: Lens Pincushion
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 70 -R 1920 -m 13 --pincushion 0.09 -z 0.64
 * @endcode
 *
 *
 * @subsection lens_panorama 1.5 Lens Panorama
 *
 * @subsubsection lens_panorama_exp Example 11: Lens Panorama
 *
 * @image html sv_lens_panorama.png "Figure 1-11. Single VIN Lens Panorama."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 2 -h 160
 * @endcode
 *
 * @subsubsection lens_panorama_fan Example 12: Lens Panorama Fan Warp
 *
 * @image html sv_lens_panorama_fan.png "Figure 1-12. Single VIN Lens Panorama Fan Warp."
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 2 -h 160 --vop -35
 * @endcode
 *
 * @subsubsection lens_panorama_rotate Example 13: Lens Panorama Rotate
 * @image html sv_lens_panorama_rotate.png "Figure 1-13. Single VIN Lens Panorama Rotate."
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 2 -h 160 --rotate 20
 * @endcode
 *
 * @subsection lens_mercator 1.6 Lens Mercator
 * @image html sv_lens_mercator.png "Figure 1-14. Single VIN Lens Mercator."
 * @subsubsection lens_mercator_exp Example 14: Lens Mercator
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 4 -h 140
 * @endcode
 *
 * @subsection lens_equirectangular 1.7 Lens Equirectangular
 * @image html sv_lens_equirectangular.png "Figure 1-15. Single VIN Lens Equirectangular."
 * @subsubsection lens_equirectangular_exp Example 15: Lens Equirectangular
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1024 -m 5 -h 140
 * @endcode
 *
 * @subsection lens_squircular 1.8 Lens Squircular
 * @image html sv_lens_squircular.png "Figure 1-16. Single VIN Lens Squircular."
 * @subsubsection lens_squirecular_exp Example 16: Lens Squircular
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 848 -m 9 -h 180
 * @endcode
 *
 * @subsection lens_vertical_panorama 1.9 Lens Vertical Panorama
 *
 * @subsubsection lens_vertical_panorama_exp Example 17: Lens Vertical Panorama
 *
 * @image html sv_vertical_panorama.png "Figure 1-17. Single VIN Lens Vertical Panorama."
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -R 910 -F 180 -m 6 --ver-range 160
 * @endcode
 *
 * @subsubsection lens_transverse_mercator Example 18: Lens Transverse Mercator
 * @image html sv_lens_transverse_mercator.png "Figure 1-18. Single VIN Lens Transverse Mercator."
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 910 --ver-range 120 -m 7 -v
 * @endcode
 *
 *
 * @subsection fs_transform_twin_vector_to_idsp_format 1.10 Lens Transform 2D Vector to 1D+1D
 * @subsubsection transform_twin_vextor_exp Example 19: Lens Transform 2D Vector to 1D+1D
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * (2D vector file in pixel level)
 * board# test_ldc -c 0 -F 180 -R 910 -m 8 --twin-vec ./2D_vector_pixel_level.bin
 * (Bypass the 2D vector data invalidity check)
 * test_ldc -c 0 -F 180 -R 1280 -m 8 --twin-vec 2D-vector-file --ignore-twin-vector-invalid
 * (2D vector file in grid level)
 * board# test_ldc -c 0 -F 180 -R 910 -m 8 --twin-vec ./2D_vector_grid_level.bin --twin-vec-size 121x69 --twin-vec-spacing 16x16
 * (Covert pure coordinate binary file to 1D+1D warp table)
 * board# test_ldc -c 0 -F 180 -R 910 -m 8 --twin-coord coord-file
 * @endcode
 *
 *
 * @subsection fs_point_mapping_warp_table 1.11 Point Mapping with Warp Table
 * @subsubsection point_mapping_warp_table_exp Example 20: Point Mapping with Warp Table
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 1224 -m 1 -v
 * board# test_ldc -c 0 --pt-vin 1024x768
 * board# test_ldc -c 0 --pt-main 512x256
 * @endcode
 *
 *
 * @subsection fs_warp_input_mode 1.12 Lens Warp Input Mode
 * @subsubsection warp_input_mode_exp Example 21: Lens Warp Input Mode
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		 // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0 -F 180 -R 984 -m 1 -C 1936x952
 * >>> Input size 1600x1328, offset 1136x296
 * board# test_ldc -c 0 -F 180 -R 984 -m 1 -C 1936x952 --input-mode 1 -v
 * >>> Input size 3840x2144, offset 0x8
 * board# test_ldc -c 0 -F 180 -R 984 -m 1 -C 1936x952 --input-mode 2 -v
 * >>> Input size 1600x2144, offset 1136x8
 * @endcode
 *
 *
 * @subsection fs_pers_mat 1.13 Lens Perspective Matrix Correction
 * @subsubsection pers_mat_exp Example 22: Lens Perspective Matrix Correction
 * @image html lens_pers_mat.png "Figure 1-19. Lens Perspective Matrix Correction."
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		 // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_ldc -c 0  --pers-mat-src-pt 1769,401,3607,321,1742,1502,3612,1522 --pers-mat-dst-pt 16,16,3672,16,16,2048,3672,2048
 * [Channel 0]: 2.400629,0.059147,-4252.749512,0.091282,2.077203,-976.753723,0.000055,0.000019,1.000000
 * board# test_ldc -c 0 -F 120 -R 1920 -m 14 --pers-mat 2.400629,0.059147,-4252.749512,0.091282,2.077203,-976.753723,0.000055,0.000019,1.000000
 * @endcode
 *
 * - - - -
 *
 * @section section_smart_ldc 2. Smart LDC
 * The web-based LDC tool "Smart LDC" was reconstructed and added to the CooperHome page. All the
 * parameters of LDC are classified according to the correction modes. @ref dewarp_correction_mode "Correction Mode".
 *
 * Please visit @ref cooperhome_gdc_page and start using this new flexible tool.
 *
 *
 */
/*!
 * @file dewarp.h
 * @brief
 * @version 0.1
 * @date 2022-10-21
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
 * @page fs_adv_dewarp ADVANCED - Multi-Region Dewarp
 *
 * @section wall_mount 1. Wall Mount
 * @image html wall_mount.png "Wall Mount"
 * Please refer to @ref dewarp_correction_mode "Correction Mode" for more detailed information on how this works.
 * @subsection dewarp_wall_rectilinear Example 1: Wall Rectilinear
 * @image html dewarp_wall_rectilinear.png "Wall Rectilinear"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x924 --vid 0 -s 1920x1080 -m 1
 * @endcode
 *
 * @subsection dewarp_wall_rectilinear_eyeball Example 2: Wall Rectilinear Eyeball Rotation
 * @image html dewarp_wall_rectilinear_eyeball.png "Wall Rectilinear Eyeball Rotation"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 1 -p 20 --max-wall-rect-areas 1
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 1 -t 30 --max-wall-rect-areas 1
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 1 --rotate 10 --max-wall-rect-areas 1
 * @endcode
 *
 * @subsection dewarp_wall_rectilinear_polar Example 3: Wall Rectilinear Polar Warp
 * @image html dewarp_wall_rectilinear_polar.png "Wall Rectilinear Polar Warp"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 1 --max-wall-rect-areas 1 --polar 50x-90
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 1 --max-wall-rect-areas 1 --polar 50x90
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 1 --max-wall-rect-areas 1 --polar 30x0
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 1 --max-wall-rect-areas 1 --polar 30x180
 * @endcode
 *
 * @subsection dewarp_wall_rectilinear_adv_py Example 4: Wall Rectilinear Advance Pitch/Yaw
 * @image html dewarp_wall_rectilinear_adv_py.png "Wall Rectilinear Advance Pitch/Yaw"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x924 --vid 0 -s 1920x1080 -m 1 --left-yaw 10 --right-yaw 0 --max-wall-rect-areas 1
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 1 --max-wall-rect-areas 1 --top-pitch 10 --bot-pitch 0
 * @endcode
 *
 * @subsection dewarp_wall_pannini Example 5: Wall Pannini
 * @image html dewarp_wall_pannini.png "Wall Pannini"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 2048x1024 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x924 --vid 0 -s 1920x1080 -m 12 --pannini-loc 0.5
 * @endcode
 *
 * @subsection dewarp_wall_panorama Example 6: Wall Panorama
 * @image html dewarp_wall_panorama.png "Wall Panorama"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 2 -h 180
 * @endcode
 *
 * @subsection dewarp_wall_panorama_fan Example 7: Wall Panorama Fan Warp
 * @image html dewarp_wall_panorama_fan.png "Wall Panorama Fan Warp"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 2 --max-wall-pano-areas 1 -h 180 --vop -35
 * @endcode
 *
 * @subsection dewarp_wall_panorama_rotate Example 8: Wall Panorama Rotate
 * @image html dewarp_wall_panorama_rotate.png "Wall Panorama Rotate"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 200 -R 956 --vid 0 -s 1920x1080 -m 2 --max-wall-pano-areas 1 -h 160 --rotate 20
 * @endcode
 *
 * @subsection dewarp_wall_cylinder Example 9: Wall Cylindrical
 * @image html dewarp_wall_cylinder.png "Wall Cylindrical"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x924 --vid 0 -s 1920x1080 -m 3 -h 160
 * @endcode
 *
 * @subsection dewarp_wall_mercator Example 10: Wall Mercator
 * @image html dewarp_wall_mercator.png "Wall Mercator"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x954 --vid 0 -s 1536x1536 -m 4 -h 140
 * @endcode
 *
 * @subsection dewarp_wall_equirectangular Example 11: Wall Equirectangular
 * @image html dewarp_wall_equirectangular.png "Wall Equirectangular"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x954 --vid 0 -s 1536x1536 -m 5 -h 140
 * @endcode
 *
 * @subsection dewarp_wall_squircular Example 12: Wall Squircular
 * @image html dewarp_wall_squircular.png "Wall Squircular"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 848 -C 992x948 --vid 0 -s 1536x1536 -m 11 -h 180
 * @endcode
 *
 * @subsection dewarp_wall_transverse_mercator Example 13: Wall Transverse Mercator
 * @image html dewarp_wall_transverse_mercator.png "Wall Transverse Mercator"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x954 --vid 0 -s 1536x1536 -m 7 --ver-range 140
 * @endcode
 *
 * @subsection dewarp_wall_vertical_panorama Example 14: Wall Vertical Panorama
 * @image html dewarp_wall_vertical_panorama.png "Wall Vertical Panorama"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 960x1920 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x954 --vid 0 -s 960x1920 -m 6 --ver-range 140
 * @endcode
 *
 * @subsection dewarp_notrans_wall_rectilinear_wall_panorama Example 15: No Transform + Wall Rectilinear + Wall Panorama
 * @image html dewarp_notrans_wall_rectilinear_wall_panorama.png "No Transform + Wall Rectilinear + Wall Panorama"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 2048x2048 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x924 --vid 0 -s 1024x1024 -o 0x0 -m 0 --ns 1792x1776 --no 96x48 --vid 1 -s 1024x1024
 *  -o 1024x0 -m 1 --max-wall-rect-areas 1 --vid 2 -s 2048x1024 -o 0x1024 -m 2 -h 160
 * @endcode
 *
 * @subsection dewarp_wall_panorama_warp_copy Example 16: Wall Panorama + Warp Copy
 * @image html dewarp_wall_panorama_warp_copy.png "Wall Panorama + Warp Copy"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 2048x2048 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x924 --vid 0 -s 2048x1024 -o 0x0 -m 2 -h 160 --vid 1 -s 2048x1024 -o 0x1024 -m 10 --wc-src 0
 * @endcode
 *
 * @subsection dewarp_wall_rect_adv_mercator Example 17: Wall Rectilinear + Wall Polar Warp + Wall Advance Pitch + Wall Mercator
 * @image html dewarp_wall_rect_adv_mercator.png "Wall Rectilinear + Wall Polar Warp + Wall Advance Pitch + Wall Mercator"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 2048x2048 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1082x960 --vid 0 -s 1024x1024 -m 1 --vid 1 -s 1024x1024 -o 1024x0 -m 1 --polar 90x180
 *  --vid 2 -s 1024x1024 -o 0x1024 -m 1 --top-pitch -10 --bot-pitch 0 --vid 3 -s 1024x1024 -o 1024x1024 -m 4 -h 140 --max-wall-rect-areas 1
 *  --max-wall-mercator-areas 1 -v
 * @endcode
 *
 * @subsection dewarp_wall_panorama_eyeball Example 18: Wall Panorama + Eyeball Rotation
 * @image html dewarp_wall_panorama_eyeball.png "Wall Panorama + Eyeball Rotation"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 2048x2048 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 942 -C 1012x958 --vid 1 -s 2048x768 -o 0x640 -h 160 -m 2 --vid 0 -s 1024x640 -m 1 --vid 2
 *  -s 1024x640 -o 1024x0 -m 1 -t 10 --vid 3 -s 1024x640 -o 0x1408 -m 1 -p -10 --vid 4 -s 1024x640 -o 1024x1408 -m 1 --rotate 10 --max-wall-rect-areas 1
 * @endcode
 *
 * @subsection dewarp_no_transform_rotate Example 19: No Transform Rotate
 * @image html dewarp_no_transform_rotate.png "No Transform Rotate"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1024x1024 -b 1 -e
 * board# test_dewarp -c 1 -F 190 -R 2048 -M 0 --vid 0 -s 1024x1024 -m 13 --rotate 45 -z 0.7 --no-trans-rotate-center -128x-128
 * @endcode
 *
 *
 * @section ceiling_mount 2. Ceiling Mount
 * @image html ceiling_mount.png "Ceiling Mount"
 *
 * @subsection dewarp_ceiling_rectilinear Example 20: Ceiling Rectilinear: North, South, West, and East
 * @image html dewarp_ceiling_rectilinear.png "Ceiling Rectilinear: North, South, West, and East"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_dewarp -c 1 -M 1 -F 180 -R 924 -C 1024x1024 --vid 0 -s 768x768 -N -m 1 --vid 1 -s 768x768 -o 768x0 -S -m 1 --vid 2 -s 768x768
 * -o 0x768 -E -m 1 --vid 3 -s 768x768 -o 768x768 -W -m 1
 * @endcode
 *
 * @subsection dewarp_ceiling_panorama_360 Example 21: Ceiling Panorama Mode - 360
 * @image html dewarp_ceiling_panorama_360.png "Ceiling Panorama Mode - 360"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 4096x1024 -b 1 -e
 * board# test_dewarp -c 1 -M 1 -F 185 -R 1024 --vid 0 -s 1024x1024 -N -h 90 -m 2 --vid 1 -s 1024x1024 -o 1024x0 -E -h 90 -m 2 --vid 2 -s 1024x1024
 * -o 2048x0 -S -h 90 -m 2 --vid 3 -s 1024x1024 -o 3072x0 -W -h 90 -m 2
 * @endcode
 *
 * @subsection dewarp_ceiling_sub_region Example 22: Ceiling Sub-Region
 * @image html dewarp_ceiling_sub_region.png "Ceiling Sub-Region"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 768x768 -b 1 -e
 * board# test_dewarp -c 1 -M 1 -F 180 -R 956 -C 1024x924 --vid 0 -s 768x768 -p 120 -t -10 -m 9 --max-ceil-sub-areas 2 -N
 * board# test_dewarp -c 1 -M 1 -F 180 -R 956 -C 1024x924 --vid 0 -s 768x768 -p 120 -t -10 -m 9 --max-ceil-sub-areas 2 -W
 * @endcode
 *
 * @subsection dewarp_ceiling_double_panorama Example 23: Ceiling Double Panorama
 * @image html dewarp_ceiling_double_panorama.png "Ceiling Double Panorama"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 2048x2048 -b 1 -e
 * board# test_dewarp -c 1 -M 1 -F 185 -R 1024 --vid 0 -s 1024x1024 -N -h 90 -m 2 --vid 1 -s 1024x1024 -o 1024x0 -E -h 90 -m 2 --vid 2 -s 1024x1024
 * -o 0x1024 -h 90 -S -m 2 --vid 3 -s 1024x1024 -o 1024x1024 -h 90 -W -m 2
 * @endcode
 *
 *
 * @subsection dewarp_ceiling_1O_3R Example 24: Ceiling 1O+3R
 * @image html dewarp_ceiling_1O_3R.png "Ceiling 1O+3R"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_dewarp -c 1 -M 1 -F 185 -R 1504 --vid 0 -s 768x768 -m 0 --ns 3008x3008 --vid 1 -s 768x768 -o 768x0 -m 9 -p 20 -t 20 --vid 2 -s 768x768
 * -o 0x768 -m 9 -p 150 -t 20 --vid 3 -s 768x768 -o 768x768 -m 9 -p 90 -t 20
 * @endcode
 *
 *
 * @subsection dewarp_ceiling_4R Example 25: Ceiling 4R
 * @image html dewarp_ceiling_4R.png "Ceiling 4R"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_dewarp -c 1 -M 1 -F 185 -R 1504 --vid 0 -s 768x768 -m 9 -p -20 -t 40 --vid 1 -s 768x768 -o 768x0 -m 9 -p 20 -t 40 --vid 2 -s
 * 768x768  -o 0x768 -m 9 -p 150 -t 40 --vid 3 -s 768x768 -o 768x768 -m 9 -p 90 -t 40
 * @endcode
 *
 *
 * @section desktop_mount 3. Desktop Mount
 * @image html desktop_mount.png "Desktop Mount"
 *
 * @subsection dewarp_desktop_rectilinear Example 26: Desktop Rectilinear North, South, West and East
 * @image html dewarp_desktop_rectilinear.png "Desktop Rectilinear North, South, West and East"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 768x768 -b 1 -e
 * board# test_dewarp -c 1 -M 2 -F 180 -R 988 -C 1024x1024 --vid 0 -s 768x768 -S -m 1
 * board# test_dewarp -c 1 -M 2 -F 180 -R 988 -C 1024x1024 --vid 0 -s 768x768 -N -m 1
 * board# test_dewarp -c 1 -M 2 -F 180 -R 988 -C 1024x1024 --vid 0 -s 768x768 -E -m 1
 * board# test_dewarp -c 1 -M 2 -F 180 -R 988 -C 1024x1024 --vid 0 -s 768x768 -W -m 1
 * @endcode
 *
 * @subsection dewarp_desktop_panorama_360 Example 27: Desktop Panorama Mode - 360
 * @image html dewarp_desktop_panorama_360.png "Desktop Panorama Mode - 360"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 4096x1024 -b 1 -e
 * board# test_dewarp -c 1 -M 2 -F 185 -R 1024 --vid 0 -s 1024x1024 -N -h 90 -m 2 --vid 1 -s 1024x1024 -o 1024x0 -W -h 90 -m 2 --vid 2 -s 1024x1024
 * -o 2048x0 -S -h 90 -m 2 --vid 3 -s 1024x1024 -o 3072x0 -E -h 90 -m 2
 * @endcode
 *
 * @subsection dewarp_desktop_sub_region Example 28: Desktop Sub-Region
 * @image html dewarp_cdesktop_sub_region.png "Desktop Sub-Region"
 * @code
 * (imx412_mipi + Sunex PN DSL 216)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 2048x2048 -b 1 -e
 * board# test_dewarp -c 1 -M 2 -F 180 -R 956 -C 1024x924 --vid 0 -s 1024x1024 -p 0 -t 55 -m 9 -N --vid 1 -s 1024x1024 -o 1024x0 -m 9 -p -90 -t 55 -N
 * --vid 2 -s 1024x1024 -o 0x1024 -m 9 -p 180 -t 55 -N --vid 3 -s 1024x1024 -o 1024x1024 -m 9 -p 90 -t 55 --max-desk-sub-areas 1 -N
 * @endcode
 *
 *
 * @section ut_point_mapping 4. Point Mapping
 * Please refer to @ref point_mapping for understanding more details.
 * @subsection dewarp_pm_exp Example 29: Point Mapping
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx274_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx274_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg  /usr/share/ambarella/lua_scripts/cv5_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1920x1080 -b 1 -e
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x924 --vid 0 -s 1920x1080 -m 1 --fish-point 100x100
 * board# test_dewarp -c 1 -M 0 -F 180 -R 956 -C 1024x924 --vid 0 -s 1920x1080 -m 1 --view-point 100x100
 * @endcode
 *
 *
 * @section ut_warp_dptz 5. Warp DPTZ
 * Please refer to @ref warp_dptz for understanding more details.
 * @subsection dewarp_warp_dptz_exp Example 30: Warp DPTZ
 * @image html dewarp_warp_dptz.png "warp dptz"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_encode -B -H 1280x720 -b 2 -e
 * board# test_dewarp -c 1 -M 1 -F 185 -R 1504 --vid 0 -s 768x768 -m 9 -p -20 -t 40 --vid 1 -s 768x768 -o 768x0 -m 9 -p 20 -t 40 --vid 2 -s
 * 768x768  -o 0x768 -m 9 -p 150 -t 40 --vid 3 -s 768x768 -o 768x768 -m 9 -p 90 -t 40
 * board# test_warp -c 1 -b 2 -a 0 --din 768x768 --dout 640x360 -a 1 --din 768x768 --dout 640x360 --dout-offset 640x360 -a 2 --din 768x768 --dout 640x360 --dout-offset
 *  640x0 -a 3 --din 768x768 --dout 640x360 --dout-offset 0x360
 * @endcode
 *
 *
 * @section ut_warp_area_update 6. Warp Area Update
 * Please refer to @ref warp_area_behavior for understanding more details.
 * @subsection dewarp_warp_area_update_exp Example 31: Warp Area Update
 * @image html dewarp_warp_area_update.png "warp area update"
 * @code
 * (imx274_mipi + EVETAR F125B016IRM12)
 * board# init.sh --na
 * board# modprobe imx412_mipi vinc_id=8 bus_id=3	// For CV5 or CV52
 * (Or board# modprobe imx412_mipi vinc_id=8)		// For CV72
 * board# modprobe ambds vin_virtual_flag=1 yuv_mode=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua		// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_9M_dewarp.lua --chan-vcap-mode-enable 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)	// For CV72
 * board# test_encode -A -H 1536x1536 -b 1 -e
 * board# test_dewarp -c 1 -M 1 -F 185 -R 1504 --vid 0 -s 768x768 -m 9 -p -20 -t 40 --vid 1 -s 768x768 -o 768x0 -m 9 -p 20 -t 40 --vid 2 -s
 * 768x768  -o 0x768 -m 9 -p 150 -t 40 --vid 3 -s 768x768 -o 768x768 -m 9 -p 90 -t 40
 * board# test_dewarp -c 1 -M 1 -F 185 -R 1504 --vid 2 -s 768x768  -o 0x768 -m 9 -p -70 -t 40 --behav 1
 * @endcode
 *
 */
/*!
 * @file vsync_loss.h
 * @brief
 * @version 0.1
 * @date 2022-04-12
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
 * @page fs_adv_vl ADVANCED - Vsync Loss
 *
 * Occasionally, the sensors encounter an issue and briefly stop generating signals that we called vsync-loss.
 * There are two main situations. One is when vsync-Loss occurs but the sensor is available afterwards,
 * Ambarella needs mechanism to recover from vsync-Loss. The other is that for multi-VIN cases, if only part of sensors
 * but not all of them are disconnected, the remaining sensors can work independently, so are the encoding streams
 * and preview buffers. Later on, applications can recover the disconnected sensors and enable encoding from these
 * "recovered" sensors / channels without interrupting the previous working ones.
 *
 * @section gvl_gvl 1. Guard Vsync Loss
 * When vsync-Loss happens, DSP can detect this signal loss, report the error message to the Arm®, and enable the
 * application to reset the sensor input and recover its previous status.
 * CV5x includes "vsync loss" detection mechanism and a daemon application to detect the signal loss and
 * recover the DSP status.
 *
 * Because CV5x has more than one VIN controller, the DSP can report the vsync signal loss message for each
 * VIN controller independently so that the application can reset and recover it separately.
 *
 * The following step shows how to check the vsync loss detection from `menuconfig`, which is enabled
 * by default.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> platform
 *              -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                  [*]   Guard Vsync loss detection in IAV driver
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-bsp
 *                  -> recipes-video
 *                     -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                        [*]   Guard Vsync loss detection in IAV driver
 * @endcode
 *
 * @subsection example_vincap1 Example 1: Guard Vsync Loss for Single VIN (imx274_mipi)
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vsync-detect-disable 0         // For CV5 or CV52
 * (Or board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vsync-detect-disable 0)   // For CV72
 * board # test_encode -A -H3840x2160 -b 0 -e
 * board # test_vin_cap -a &
 * @endcode
 *
 * @subsection example_vincap2 Example 2: Guard Vsync Loss for Multi-VIN (imx586_mipi + imx274_mipi) on CV5x
 * @code
 * board # init.sh --na;modprobe imx586_mipi vinc_id=0 bus_id=5 cphy=0;modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vsync-detect-disable 0
 * board # test_encode -A -H3840x2160 -b 0 -e
 * board # test_vin_cap -a &
 * @endcode
 *
 * When the DSP detects the vsync signal loss, it reports the error code to the Arm so that the
 * @b "test_vin_cap -a &" application receives the error code, forces the "broken" sensor to power down,
 * and resumes the DSP state step-by-step.
 *
 * @note
 * - There will be frame dropping when vsync loss occurs, but it will be restored after vsync loss is recovered.
 *
 */
/*!
 * @file img_scaler.h
 * @brief
 * @version 0.1
 * @date 2022-01-10
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
 * @page fs_adv_arb_img_scaler ADVANCED - Arbitrary Image Scaler
 *
 * @section arbi_img_scaler 1. Arbitrary Image Scaler
 *
 * CV5x can export the image digital signal processor (IDSP) mixer to enable user applications to perform up- / down-scaling.
 * Using the scaler, a user-specified input buffer can be cropped and scaled up or down
 * to the chosen output size. Because the arbitrary image scaler is multiplexed with
 * the source buffer (when it is enabled), the seventh source buffer must be disabled for
 * all channels and cannot be used as a pyramid input buffer.
 *
 * @image html fs_img_scale.png "Figure 1-1. Arbitrary Image Scaler."
 *
 *
 * @par Resolution and Scalability
 *
 * - The maximum input buffer size can be up to 14336x14336.
 * - The maximum output buffer size can be up to 14336x8192.
 * - The image scaler supports up to 8x upscaling and 1/8x downscaling.
 *
 * @par Input Data Format
 *
 *  Three types of YUV formats are supported for the input / output (I/O) buffer:
 *
 * - @b YUV400
 * - @b YUV420
 * - @b YUV422
 *
 * Once designated, the format of the I/O buffer must be kept the same.
 *
 * @par Buffer Address Alignment
 *
 * The buffer pitch of the input buffer should be aligned to 64 on CV5x and aligned to 128
 * on CV72. The x-offset and width of cropping window must be aligned to 4; the y-offset
 * and height must be aligned to two. When the buffer width is aligned to 4, but not aligned to
 * 64 or 128 (such as 720), it must be padded to be aligned to 64 or 128
 * before image scaling is performed.
 *
 * The buffer pitch of the output buffer must be aligned to 64 on CV5x and aligned to 128
 * on CV72, and the buffer width must be aligned to 4. When the buffer width is
 * aligned to 4, but is not aligned to 64 or 128 (such as 360), it must be padded to be aligned
 * to 64 or 128 before image scaling is performed.
 *
 * ---
 *
 * @section section_img_scller_examples  2. Arbitrary Image Scaler Example
 *
 * @subsection example_arbi_img_scaler1 Example 1: Crop and Upscale from Canvas0 (YUV420) with Top-Left Offset 100x200 and Size 480p to 1080p
 *
 * @code
 * Remove the seventh buffer from the canvases in the Lua file `cv5_vin0_1080p_linear.lua` first.
 *
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --img-scale 1\        // For CV5 or CV52
 *            --img-scale-format 0 --img-scale-max-in 1920x1080 --img-scale-max-out 1920x1080\
 *            --img-scale-job-queue-depth 8
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --img-scale 1\   // For CV72
 *            --img-scale-format 0 --img-scale-max-in 1920x1080 --img-scale-max-out 1920x1080\
 *            --img-scale-job-queue-depth 8)
 * board# test_img_scale -b 0 --binoffset 100x200 --binsize 720x480 --boutsize 1920x1080 -f file_name
 * @endcode
 *
 */
/*!
 * @file efm.h
 * @brief
 * @version 0.1
 * @date 2020-02-10
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
 * @page fs_adv_efm ADVANCED - Encode from Memory
 *
 * @section efm_efm 1. Encode from Memory
 * This chapter describes the usage of encoding from the memory cases.
 *
 * There are two main cases for this feature based on different processing stages inside the DSP.
 *      - <b>Encode from RAW</b>:  The input for DSP is in the form of RAW data (either bayer RGB format or
 * YUV format), and it is fed into the VIN buffer.
 *      - <b>Encode from MEM</b>:  The input for the DSP is YUV (YUV420 format with UV interleaved) / ME1
 * data, and it is fed into the extended source buffer (EFM buffer).
 *

 * @section preparations 2. Preparations
 * @subsection memory 2.1 Memory
 * For the EFM case, user memory partition is needed to transfer the RAW data,
 * configure it from "menuconfig" as below. Below size is 64 MB.<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> private
 *              -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                  (0x4000000) IAV Usr Buffer Size
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *           -> meta-ambabsp
 *              -> recipes-bsp
 *                 -> recipes-video
 *                    -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                       (0x4000000) IAV Usr Buffer Size
 * @endcode
 *
 * Or use "test_mempart" to allocate user buffer runtime.
 * @code
 * board# test_mempart -m 2 -s 0x4000000
 * @endcode
 *
 * @subsection configrations 2.2 Configrations
 * For the encode from MEM case, users should configure related settings through lua script first.  Here is
 * part of /usr/share/ambarella/lua_scripts/cv5_multi_efm_1080p_linear.lua as example.
 * @code
 * ...
 * stream_0 = {
 *      id = 0,
 *      ...
 *      efm_enable = 1, -- 0: disable; 1: enable
 *      efm_buf_num = 8, -- buffer number should at range [5-10]
 *      efm_size = {720, 480},
 * }
 * ...
 * @endcode
 *
 * @note
 * 1.	For H.264, YUV and ME1 buffers are needed for the DSP.  If there is no ME1, `test_efm` will
 * generate it automatically.
 * 2.	For H.265, YUV, ME1 and ME0 buffers are needed for the DSP.  If there is no ME1 or ME0,
 * `test_efm` will generate them automatically.
 * 3.	For MJPEG , only YUV is needed for the DSP.  If only doing MJPEG encoding, especially for high-resolution,
 * it is strongly suggested to set "codec_enable = 3" for the EFM stream through lua script. This is to save
 * certain DSP hardware resource, in case running out of it.
 * 4.	Start EFM stream encoding, it needs to run `"test_efm"` in another console right after
 * `"test_encode -A -h 1080p -b 24 -e"` to feed EFM buffer with specific YUV data continuously into the DSP.
 * Different from CV2x platform, CV5x uses the ID 24 for EFM streams, because CV5x supports up to 20 canvases.
 * So the ID 16 on CV5x actually means canvas with ID 16, and 24 stands for EFM buffer.
 * 5.	EFM stream supports overlay, but doesn't support blur.
 *
 * @section efm_exp 3. EFM Examples
 * @subsection example_efm1 Example 1: Encode H.264 stream from EFM buffer: Input from main buffer
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_multi_efm_1080p_linear.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_multi_efm_1080p_linear.lua)   // For CV72
 * board# test_encode -A -h1080p -b 24 -e
 * board# test_efm -A -t 1 -b 0
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efm2 Example 2: Encode 4K H.264 stream from EFM buffer: Input from main buffer
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_multi_efm_4k_linear.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_multi_efm_4k_linear.lua)   // For CV72
 * board# test_encode -A -h3840x2160 --smaxsize 3840x2160 -b 24 -e
 * board# test_efm -A -t 1 -b 0
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efm3 Example 3: Encode 2x H.264 streams from EFM buffer: Input from main buffer and third buffer
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_multi_efm_1080p_linear.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_multi_efm_1080p_linear.lua)   // For CV72
 * board# test_encode -A -h1080p -b 24 -e -B -h720p -b 24 -e
 * board# test_efm -A -t 1 -b 0
 * board# test_efm -B -t 1 -b 2 (in another console)
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efm4 Example 4: Encode H.264 stream from EFM buffer: YUV (NV12) file
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_multi_efm_1080p_linear.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_multi_efm_1080p_linear.lua)   // For CV72
 * board# test_encode -A -h1080p -b 24 -e
 * board# test_efm -A -t 0 -y 1080p_nv12.yuv -s 1920x1080
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efm5 Example 5: Encode H.264 stream from EFM buffer with specified frame rate: YUV (NV12) file
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_multi_efm_1080p_linear.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_multi_efm_1080p_linear.lua)   // For CV72
 * board# test_encode -A -h1080p -b 24 -e
 * board# test_efm -A -t 0 -y 1080p_nv12.yuv -s 1920x1080 -r 25
 * board# test_encode -A -s
 * @endcode
 *
 *
 * @subsection example_efm7 Example 6: Encode 4K H.264 stream from EFM buffer: Input from YUV (NV12) file
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_multi_efm_4k_linear.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_multi_efm_4k_linear.lua)   // For CV72
 * board# test_encode -A -h3840x2160 --smaxsize 3840x2160 -b 24 -e
 * board# test_efm -A -t 0 -y 4k_nv12.yuv -s 3840x2160
 * board# test_encode -A -s
 * @endcode
 *
 *
 * @subsection example_efm9 Example 7: Encode H.265 stream from EFM buffer: Input from main buffer
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_multi_efm_1080p_linear.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_multi_efm_1080p_linear.lua)   // For CV72
 * board# test_encode -A -H1080p -b 24 -e
 * board# test_efm -A -t 1 -b 0
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efm10 Example 8: Encode H.265 stream from EFM buffer: Input from YUV (NV12) file
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_multi_efm_1080p_linear.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_multi_efm_1080p_linear.lua)   // For CV72
 * board# test_encode -A -H1080p -b 24 -e
 * board# test_efm -A -t 0 -y 1080p_nv12.yuv -s 1920x1080
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efm11 Example 9: Enter preview with virtual vinc_id, and Encode H.265 stream
 * from EFM buffer: Input from YUV (NV12) file
 *
 * This is for debug usage, channel 0 is for virtual vinc_id, channel 1 is for EFM.
 *
 * @code
 * board# init.sh --na;modprobe ambds mipi=0 lane=2
 * board# test_mempart -m 2 -s 0x4000000
 * board# test_encode --resource-cfg cv5_efm_1080p.lua
 * board# test_encode -A -H 1080p -b 24 -e
 * board# test_efm -A -t 0 -y 1080p_nv12.yuv -s 1920x1080
 * board# test_encode -A -s
 * @endcode
 *
 *
 */
/*!
 * @file efr.h
 * @brief
 * @version 0.1
 * @date 2021-10-26
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
 * @page fs_adv_efr ADVANCED - Encode from RAW
 *
 * @section efr_efr 1. Encode from RAW
 * There are two main cases for this feature, based on different processing stages inside the digital signal processor (DSP).
 *      - <b>Encode from RAW (EFR)</b>
 *      - @ref efm_efm "Encode from MEM"
 *
 * For EFR cases, the RAW data files are fed to video input (VIN) buffer. AE / AWB / AF (3A) flow and other image optimization
 * still function while encode from memory (EFM) cases send data directly to the source buffer for encoding.
 * <br>
 * For EFR cases, anonymous memory partitions are required to transfer the RAW data.
 * Reserve sufficient memory in the digital signal processor (DSP) private memory partition.
 *
 * If the input format is YUV, the supported format is YUV422 / YUV420, and UV
 * should be interleaved; that is, NV16 / NV12 accordingly.
 * NV16 (YUV422) is provided below:
 * @verbatim
              YYYYYYYYYYYYYYYYYYYYYYYYYYYY
              YYYYYYYYYYYYYYYYYYYYYYYYYYYY
              YYYYYYYYYYYYYYYYYYYYYYYYYYYY
              YYYYYYYYYYYYYYYYYYYYYYYYYYYY
              UVUVUVUVUVUVUVUVUVUVUVUVUVUV
              UVUVUVUVUVUVUVUVUVUVUVUVUVUV
              UVUVUVUVUVUVUVUVUVUVUVUVUVUV
              UVUVUVUVUVUVUVUVUVUVUVUVUVUV
   @endverbatim
 *
 *
 * NV12 (YUV420) is as follows:
 * @verbatim
              YYYYYYYYYYYYYYYYYYYYYYYYYYYY
              YYYYYYYYYYYYYYYYYYYYYYYYYYYY
              YYYYYYYYYYYYYYYYYYYYYYYYYYYY
              YYYYYYYYYYYYYYYYYYYYYYYYYYYY
              UVUVUVUVUVUVUVUVUVUVUVUVUVUV
              UVUVUVUVUVUVUVUVUVUVUVUVUVUV
   @endverbatim
 *
 * @note
 * To start EFR test cases, run `"test_efm"` in another console <b>immediately after</b>
 * `"test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg vout.lua --enc-raw-rgb/yuv 1"` feeds YUV data continuously into the DSP.
 *
 * - - - -
 *
 * @section efr_multi 2. EFR for Multi-VINs and Multiple Channels
 * EFR for multi-VINs can support RAW encoding from each VIN controller. EFR can support various
 * RAW formats, including RGB Bayer RAW, NV16 (YUV422), and NV12 (YUV420). In this case,
 * users must configure parameters of the ambdd driver. The parameter "vin_virtual_flag" must
 * be set to 1, and the parameter "vinc_id_map" must be set as the VINC RAW encode bitmap.
 * For example, "vinc_id_map=0xc000" indicates that virtual VIN14 and VIN15 are used; it can support RAW
 * encode from different VINCs. Of course, users want to perform RAW encode from a single real virtual
 * VINC; users can also choose not to specify the parameter above. Users can set multiple channels
 * for a single virtual VINC.
 *
 * @note
 * Currently, image audio video (IAV) supports four VINs for RAW encode and four channels for each single real virtual VINC.
 *
 * - - - -
 *
 * @section custom_virtual_vin_mode 3. Custom Virtual VIN Mode
 * To make EFR more flexible and to support different video source (VSRC) formats, users can configure the
 * virtual VIN mode via Lua script. See @ref lua_vsrc_configuration "Video Input Configuration".
 *
 * - - - -
 *
 * @section efr_exp 4. EFR Examples
 *
 * @subsection example_efr1 Example 1: Encode from RGB RAW: Input from RGB (RAW) file to VIN with custom virtual VIN mode
 *
 * @code
 * board# init.sh --na;modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_efr_rgb.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1 // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_efr_rgb.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1)  // For CV72
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv3_vin0_1080p_linear_efr_rgb.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1)  // For CV3
 * board# test_efm -t 3 -i cap_raw_raw_1920x1080_3840.raw  -s 1920x1080 -T 1 -r 30 -R 0 --vin-id 14
 * (Or board# test_efm -t 3 -i cap_raw_raw_1920x1080_3840.raw  -s 1920x1080 -T 1 -r 30 -R 0 --vin-id 24)  // For CV3
 * @endcode
 *
 * @subsection example_efr2 Example 2: Encode from 12-bit packed RGB RAW: Input from RGB (RAW) file to VIN with custom virtual VIN mode
 *
 * To support encode from 12-bit packed RAW, users must enter the preview by setting "raw_capture = 1" and "packing_mode_enable = 1".
 * For more details, refer to <a href="script/uncompressed_pack_raw_packed_4k.lua" target="_blank"><b>uncompressed_pack_raw_packed_4k.lua</b></a>.
 *
 * @code
 * board# init.sh --na;
 * board# modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg uncompressed_pack_raw_packed_4k.lua --vout-cfg vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1
 * board# test_encode -A -h 3840x2160 -e
 * board# test_efm -t 3 -i 3840x2160_5764_pck_12bits.raw -s 5764x2160 -e ce_960x2160_1444_pck_12bits.raw --ce-size 1444x2160 -T 1 --raw-format 2
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efr3 Example 3: Encode from compressed RGB RAW: Input from RGB (RAW) file to VIN with custom virtual VIN mode
 *
 * To support encode from compressed RAW, users must enter the preview by setting "raw_capture = 0".
 * For more details, refer to <a href="script/compressed_raw_4k.lua" target="_blank"><b>compressed_raw_4k.lua</b></a>.
 *
 * @code
 * board# init.sh --na;
 * board# modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg compressed_raw_4k.lua --vout-cfg vout_hdmi.lua --enc-raw-rgb 1
 * board# test_encode -A -h 3840x2160 -e
 * board# test_efm -t 3 -i 3840x2160_3244_cpr.raw -s 3244x2160 -e ce_960x2160_816_cpr.raw --ce-size 816x2160 -T 1 --raw-format 1
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efr4 Example 4: Encode from YUV NV16 RAW: YUV NV16 (RAW) to VIN
 *
 * To support encode from NV16 RAW file, users must enter the preview by setting "enc-raw-yuv = 1" and "raw-capture = 1".
 *
 * @code
 * board# init.sh --na
 * board# modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_efr_yuv.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-yuv 1 --raw-capture 1 // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_efr_yuv.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-yuv 1 --raw-capture 1)  // For CV72
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv3_vin0_1080p_linear_efr_yuv.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-yuv 1 --raw-capture 1)  // For CV3
 * board# test_efm -t 2 -s 1920x1080 -i 1080p_nv16.raw -T 1
 * board# test_encode -A -h1080p -e
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efr5 Example 5: Encode from YUV NV12 RAW: YUV NV12 (RAW) to VIN
 *
 * To support encode from NV12 RAW file, users must enter the preview by setting "enc-raw-nv12 = 1" and "raw-capture = 1".
 * 
 * @code
 * board# init.sh --na
 * board# modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_efr_yuv.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-nv12 1 --raw-capture 1 // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_efr_yuv.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-nv12 1 --raw-capture 1)  // For CV72
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv3_vin0_1080p_linear_efr_yuv.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-nv12 1 --raw-capture 1)  // For CV3
 * board# test_efm -t 4 -s 1920x1080 -i 1080p_nv12.raw -T 1
 * board# test_encode -A -h1080p -e
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efr6 Example 6: Encode from RGB RAW with multi-source: Two sources and two channels
 *
 * virtual_vsrc_num in ambds used to specify the VSRC number for the RAW encode channel.
 *
 * @code
 * board# init.sh --na; modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=2 custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_dual_chan_dual_input_raw_encode.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_dual_chan_dual_input_raw_encode.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1)  // For CV72
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv3_dual_chan_dual_input_raw_encode.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1)  // For CV3
 * board# test_efm -t 3 -i cap_raw_raw_1920x1080_3840_v1.raw -s 1920x1080 -T 1 --vin-id 14
 * board# test_efm -t 3 -i cap_raw_raw_3840x2160_7680_v2.raw -s 3840x2160 -T 1 --vin-id 15
 * (Or board# test_efm -t 3 -i cap_raw_raw_1920x1080_3840_v1.raw -s 1920x1080 -T 1 --vin-id 24)  // For CV3
 * (Or board# test_efm -t 3 -i cap_raw_raw_3840x2160_7680_v2.raw -s 3840x2160 -T 1 --vin-id 25)  // For CV3
 * board# test_encode -A -h1080p -e
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efr7 Example 7: Encode from RGB RAW with multi-source: Four sources and four channels
 *
 * The Lua script can be found in <a href="script/four_chan_four_vin_efr_4k.lua" target="_blank"><b>four_chan_four_vin_efr_4k.lua</b></a>.
 *
 * @code
 * board# init.sh --na; modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=4 custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg four_chan_four_vin_efr_4k.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 0 --enc-raw-rgb 1
 * board# test_efm -t 3 -i cap_raw_raw_3840x2160_3240_cpr_v1.raw -s 3240x2160 -e cap_raw_raw_ce_960x2160_812_cpr_v1.raw --ce-size 812x2160 --raw-format 1 -T 1 --vin-id 14
 * board# test_efm -t 3 -i cap_raw_raw_3840x2160_3240_cpr_v2.raw -s 3240x2160 -e cap_raw_raw_ce_960x2160_812_cpr_v2.raw --ce-size 812x2160 --raw-format 1 -T 1 --vin-id 15
 * board# test_efm -t 3 -i cap_raw_raw_3840x2160_3240_cpr_v3.raw -s 3240x2160 -e cap_raw_raw_ce_960x2160_812_cpr_v3.raw --ce-size 812x2160 --raw-format 1 -T 1 --vin-id 16
 * board# test_efm -t 3 -i cap_raw_raw_3840x2160_3240_cpr_v4.raw -s 3240x2160 -e cap_raw_raw_ce_960x2160_812_cpr_v4.raw --ce-size 812x2160 --raw-format 1 -T 1 --vin-id 17
 * (Or board# test_efm -t 3 -i cap_raw_raw_3840x2160_3240_cpr_v1.raw -s 3240x2160 -e cap_raw_raw_ce_960x2160_812_cpr_v1.raw --ce-size 812x2160 --raw-format 1 -T 1 --vin-id 24)  // For CV3
 * (Or board# test_efm -t 3 -i cap_raw_raw_3840x2160_3240_cpr_v2.raw -s 3240x2160 -e cap_raw_raw_ce_960x2160_812_cpr_v2.raw --ce-size 812x2160 --raw-format 1 -T 1 --vin-id 25)  // For CV3
 * (Or board# test_efm -t 3 -i cap_raw_raw_3840x2160_3240_cpr_v3.raw -s 3240x2160 -e cap_raw_raw_ce_960x2160_812_cpr_v3.raw --ce-size 812x2160 --raw-format 1 -T 1 --vin-id 26)  // For CV3
 * (Or board# test_efm -t 3 -i cap_raw_raw_3840x2160_3240_cpr_v4.raw -s 3240x2160 -e cap_raw_raw_ce_960x2160_812_cpr_v4.raw --ce-size 812x2160 --raw-format 1 -T 1 --vin-id 27)  // For CV3
 * board# test_encode -A -h3840x2160 -e
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efr8 Example 8: Encode from RGB RAW with multiple channels: One source and two channels
 * @code
 * board# init.sh --na; modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_dual_chan_single_input_raw_encode.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_dual_chan_single_input_raw_encode.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1)  // For CV72
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv3_dual_chan_single_input_raw_encode.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-rgb 1)  // For CV3
 * board# test_efm -t 3 -i cap_raw_raw_1920x1080_3840.raw -s 1920x1080 -T 1
 * board# test_encode -A -h1080p -e
 * board# test_encode -A -s
 * @endcode
 *
 * @subsection example_efr9 Example 9: One RAW encode and one physical sensor
 * The Lua script can be found in <a href="script/one_efr_one_physical_sensor.lua" target="_blank"><b>here</b></a>.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg one_efr_one_physical_sensor.lua --raw-capture 1 --enc-raw-rgb 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board# test_efm -t 3 -i cap_raw_raw_1920x1080_3840.raw -s 1920x1080 -T 1 --vin-id 14
 * @endcode
 *
 * @subsection example_efr10 Example 10: Encode from RGB RAW: Input from HDR 2X RGB (RAW) file to VIN with custom virtual VIN mode
 * Users must configure the corresponding HDR exposure parameters according to the shutter ratio of each sensor.<br>
 * Taking imx274 for example, if 1080p30/hdr2x mode is used, the first shutter ratio (rhs1) is fixed at 0x1D2, and hdr_short1_offset = rhs1 * 2 + 1 = 933.<br>
 * The Lua script can be found in <a href="script/1080p_hdr2x_efr.lua" target="_blank"><b>1080p_hdr2x_efr.lua</b></a>.
 * @code
 * board# init.sh --na;modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg 1080p_hdr2x_efr.lua.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-rgb 1
 * board# test_efm -t 3 -i cap_raw_imx274_1920x3092_1620_cpr.raw -s 1620x3092 -e cap_raw_imx274_ce_480x3092_408_cpr.raw --ce-size 408x3092 -R1 -T 1 --vin-id 14
 * (Or board# test_efm -t 3 -i cap_raw_imx274_1920x3092_1620_cpr.raw -s 1620x3092 -e cap_raw_imx274_ce_480x3092_408_cpr.raw --ce-size 408x3092 -R1 -T 1 --vin-id 24) // For CV3
 * @endcode
 *
 * @subsection example_efr11 Example 11: Encode from YUV NV12 RAW: Capture YUV(NV12) RAW from canvas then feed to EFR channel
 * In order for ARM to have control over the memory, the captured canvas must be set to manual feed or external memory mode.
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# modprobe ambds vin_virtual_flag=1 custom_format_enable=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_dual_chan_one_sensor_one_yuv_efr.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-nv12 1 // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_dual_chan_one_sensor_one_yuv_efr.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-raw-nv12 1) // For CV72
 * board# test_manual_feed -a0 -Q0 &
 * board# test_efm -t 6 -b 0 -V 14
 * @endcode
 *
 */
/*!
 * @file encode_latency.h
 * @brief
 * @version 0.1
 * @date 2020-07-07
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
 * @page fs_adv_pl_latency ADVANCED - Pipeline Latency
 *
 * @section idsp_latency 1. Image Digital Signal Processing (IDSP) Latency
 * This chapter illustrates the IDSP latency of different video input (VIN) mode cases, which are measured under the following two circumstances.
 *
 * @subsection idsp_latency_live 1.1 Latency between VIN Capture Complete and IDSP YUV Output
 * The table below records the latency between when VIN capture is completed and the IDSP YUV is output under different VIN modes.
 * It is measured with sensor input.
 * @note
 * - The latency here does not include the latency between the sensor beginning exposure and the frame being captured completed by VIN.
 * - "low_delay_vin_vout" can be supported in only encode mode 0.
 *
 * <table>
 * <caption>VIN Capture Done to IDSP YUV Output Latency (CV5s88)</caption>
 * <tr><th rowspan="2">NO.<th rowspan="2">Encode Mode<th colspan="2">VIN: 1080p60<th colspan="2">VIN: 4kp30
 * <th colspan="2">VIN: 4Kp60<tr><th>Latency<br />(ms)<th>Latency<br />(frames)<th>Latency<br />(ms)<th>Latency<br />(frames)<th>Latency<br />(ms)<th>Latency<br />(frames)
 * <tr><td>1<td>0<td>10.48<td>0.63<td>19.56<td>0.59<td>19.81<td>1.19
 * </table>
 *
 * @subsection  idsp_latency_raw 1.2 Latency Between Feeding Raw Images and IDSP YUV Output
 * The table below records the latency between feeding a raw image and the IDSP YUV output. It is measured with encode from raw (EFR).
 *
 * <table>
 * <caption>Feed Raw Data to IDSP YUV Output Latency</caption>
 * <tr><th>NO.<th>Encode Mode<th>VIN<br />(ms)<th>
 * Latency<br />(ms)<th>Latency<br />(frames)
 * <tr><td>0<td>0<td>4Kp30<td>15.6<td>0.46
 * </table>
 *
 * @subsection capture_display_latency 1.3 Latency Between VIN Capture and VOUT Display
 * To increase the latency reliability between VIN capture and VOUT display, use a high refresh-rate LCD screen as an input.
 *
 * The table below records the latency between VIN capture and VOUT display under different VIN modes.
 *
 * <table>
 * <caption> VIN Capture to VOUT Display Latency</caption>
 * <tr><th rowspan="2">NO.<th rowspan="2">Encode Mode<th colspan="2">1080p60VIN-->1080p60VOUT<br />(CV5S88)
 * <th colspan="2">4Kp60VIN-->4Kp60VOUT<br />(CV5S88)<tr><th>Latency<br />(ms)<th>Latency<br />(frames)
 * <th>Latency<br />(ms)<th>Latency<br />(frames)
 * <tr><td>1<td>0<td>62<td>3.72<td>77<td>4.62
 * </table>
 *
 * The measurement method is shown as below. It uses case "NO. 1" as an example. The PC monitor (1080p@144Hz)
 * runs a timer on the left. Its image will be captured and processed by the CV5S88 evaluation kit (EVK) and output to the
 * right monitor through the high-definition multimedia interface (HDMI®) VOUT. If using another camera to take the photo of these
 * two monitors, the latency between VIN capture and VOUT display will be the time difference of the timers
 * in these two monitors of the same photo.
 * @image html CV5_capture_display_latency.jpg "Figure 1-1. Latency Between VIN Capture and VOUT Display."
 *
 * Each test result is as shown below:
 *
 * - [Encode Mode 0], 1080P60 VIN ---> 1080p60 VOUT
 * @image html CV5_1080P60VIN_1080P60VOUT_mode0.jpg "Figure 1-2. Latency Between 1080p60VIN Capture and 1080p60VOUT Display, enc-mode = 0."
 *
 * - [Encode Mode 0] 4KP60 VIN ---> 4KP60 VOUT
 * @image html CV5_4Kp60VIN_4kP60VOUT_mode0.jpg "Figure 1-3. Latency Between 4KP60VIN Capture and 4KP60VOUT Display, enc-mode = 0."
 *
 * - - - -
 *
 * @section enc_latency 2. Encode Latency
 * This chapter describes the usage of measuring encode latency.
 *
 * Users can measure the encode latency via the following command after starting the stream. As shown in the log
 * below, monotonic_pts represents the frame presentation time stamp (PTS) before encoding and enc_done_pts represents the
 * frame PTS after encoding. The difference between enc_done_pts and monotonic_pts is the frame
 * encoding time, which is recorded as enc_pipe_time in units of ticks. As there are 90,000
 * ticks in one second, users can convert the ticks to normal time with the equation
 * Ticks / 90 = Millisecond. For example, if the enc_pipe_time is 4500, the normal time should be
 * 4500 / 90 = 50 ms.
 *
 * @note
 * The latency mentioned here is measured from the time of VIN capture completion to completion of frame encoding. It does not
 * include the latency between the sensor beginning exposure and this frame being captured completed by VIN.
 *
 * @code
 * board# test_stream -v --nofile
 * type=3, is_skipped 0, size=43110, addr=0x31826560, strm_id=0, sesn_id=1615867172, frame_num=1122, monotonic_pts=5840788, mono_diff=3011, enc_done_pts = 5845196, enc_pipe_time = 4408, reso=1920x1080, slice_header_offset = 18
 * type=3, is_skipped 0, size=3801, addr=0x31869696, strm_id=0, sesn_id=1615867172, frame_num=1123, monotonic_pts=5843799, mono_diff=3011, enc_done_pts = 5850953, enc_pipe_time = 7154, reso=1920x1080, slice_header_offset = 18
 * type=3, is_skipped 0, size=43380, addr=0x31873536, strm_id=0, sesn_id=1615867172, frame_num=1124, monotonic_pts=5846816, mono_diff=3017, enc_done_pts = 5851223, enc_pipe_time = 4407, reso=1920x1080, slice_header_offset = 18
 * type=3, is_skipped 0, size=3715, addr=0x31916928, strm_id=0, sesn_id=1615867172, frame_num=1125, monotonic_pts=5849827, mono_diff=3011, enc_done_pts = 5856929, enc_pipe_time = 7102, reso=1920x1080, slice_header_offset = 18
 * type=3, is_skipped 0, size=42154, addr=0x31920768, strm_id=0, sesn_id=1615867172, frame_num=1126, monotonic_pts=5852793, mono_diff=2966, enc_done_pts = 5857199, enc_pipe_time = 4406, reso=1920x1080, slice_header_offset = 18
 * @endcode
 *
 * @subsection latency_vin_cap_to_encoding_done 2.1 Latency Between VIN Capture Completed and Encoding Completed
 * The table below records the latency between "VIN capture done" and “Frame encode done“. It is measured with sensor input.
 *
 * <table>
 * <caption> Encoding Latency (CV5)</caption>
 * <tr><th rowspan="2">NO.<th rowspan="2">Format<th rowspan="2">Slice Num<th rowspan="2">VDSP Mode<th colspan="2">VIN: 4Kp30<br />(CV5S88)
 * <th colspan="2">VIN: 4Kp60<br />(CV5S88)<tr><th>Latency<br />(ms)<th>Latency<br />(frames)
 * <th>Latency<br />(ms)<th>Latency<br />(frames)
 * <tr><td>1<td>AVC<td>2<td>Single core<td>16.588<td>0.498<td>16.772<td>1.003
 * <tr><td>2<td>AVC<td>1<td>Dual core(temporal)<td>52.122<td>1.564<td>52.466<td>3.165
 * <tr><td>3<td>HEVC<td>2<td>Single core<td>16.561<td>0.497<td>16.783<td>1.007
 * <tr><td>4<td>HEVC<td>1<td>Dual core(temporal)<td>52.088<td>1.563<td>52.3<td>3.13
 * <tr><td>5<td>HEVC<td>1<td>Dual core(spatial)<td>15.755<td>0.473<td>15.955<td>0.957
 * </table>
 * <br>
 *
 * - - - -
 *
 * @section video_info_audit 3. Video Pipeline Info Audit
 * Ambarella integrated the image audio video (IAV) audit tool into the Linux proc file to enable real-time monitoring of video pipeline information.
 * The audit tool currently supports the following: DSP interrupt processing duration, DSP interrupt interval, IDSP latency, encode latency,
 * IDSP frame drop, encode frame drop, vout frame drop, frame sync(osd, overlay and blur), VIN-VOUT synchronization latency, IDSP and encode clock.
 *
 * Users can use the "echo" function in the shell to pass two arguments, separated by a space " ". The first parameter is the bitmap to enable auditing,
 * and the second parameter is the duration of the audit.
 * @code {.c}
 * board# echo 0x1f3 3 > /proc/ambarella/iav_audit
 * @endcode
 *
 * When the parameter is set successfully, users can use "cat" to retrieve the audit results for the
 * next few seconds (determined by the second parameter, in units /s).
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * The current audit print bitmap: 0x1f3
 * The last audit print bitmap: 0x0
 * The current audit time interval: 3s
 *
 *  bit[ 0]: enable     isr duration
 *  bit[ 1]: enable     isr interval
 *  bit[ 2]: disable    iav ioctl
 *  bit[ 3]: disable    imgproc ioctl
 *  bit[ 4]: enable     idsp delay
 *  bit[ 5]: enable     encode delay
 *  bit[ 6]: enable     VOUT-VIN delay
 *  bit[ 7]: enable     IAV IDSP frame drop audit
 *  bit[ 8]: enable     IAV encode frame drop audit
 *  bit[ 9]: disable    IAV vout underflow audit
 *  bit[10]: disable    ENC sync fail audit
 *  bit[11]: disable    EIS sync fail audit
 *  bit[12]: disable    Img scaler audit to check IDSP clock
 *  bit[13]: disable    Encode clock audit
 *  bit[14]: enable     Frame sync(ovrelay and blur) audit
 *
 * ======= Audit video info within 3s ========
 *          ...(different audit info)
 * @endcode
 *
 * @subsection isr_latency_aud 3.1 DSP ISR Latency Audit
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * === [Audit - ISR Duration Info]
 *  IRQ_NAME		status	   ISR_cnt	  ISR_FREQ (Hz)   Avg (us)	 Max (us)	Min (us)   Delta (us)
 *  vdsp			Enable	   181		  60			  0 		 4			0		   4
 *  venc			Disable    0		  0 			  0 		 0			0		   0
 *  vcap			Enable	   724		  241			  0 		 0			0		   0
 *  vin            Enable	   90		  30			  0 		 0			0		   0
 *
 *
 * === [Audit - ISR Interval Info]
 *  IRQ_NAME		status	   ISR_cnt	  Avg (us)	 Max (us)	Min (us)   Delta (us)
 *  vdsp_intvl	    Enable	   181		  16666 	 16684		16649	   35
 *  venc_intvl	    Disable    0		  0 		 0			0		   0
 *  vcap_intvl	    Enable	   724		  4182		 29786		28		   29758
 *  vin_intvl 	    Enable	   90		  33321 	 33797		32851	   946
 * @endcode
 *
 * The printout details the four main pieces of DSP interrupt audit information (<b>vdsp</b>, <b>venc</b>, <b>vcap</b>, and <b>vin</b>).
 * "ISR Duration info" shows the processing and scheduling time of each interrupt on the Arm® side,
 * and "ISR Interval Info" shows the interval time information of two adjacent interrupts for each interrupt type.
 *
 * @subsection idsp_latency_aud 3.2 IDSP Latency Audit
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * === [IDSP Latency Info] : From "raw capture done" to "IDSP YUV output"
 *  Canvas	 Src			 Avg (us)	Max (us)   Min (us)   Delta (us)
 *  0 		 chan0_main 	 10598		10632	   10574	  58
 *  1 		 chan0_2nd		 10611		10644	   10589	  55
 *  2 		 chan0_3rd		 10607		10640	   10585	  55
 *  3 		 chan0_4th		 10603		10637	   10581	  56
 * @endcode
 *
 * The printout details the average latency (<b>Avg</b>), maximum latency (<b>Max</b>),
 * minimum latency (<b>Min</b>), and the difference between the maximum and minimum
 * latency (<b>Delta</b>) over one second for each canvas.
 *
 * @subsection encode_latency_aud 3.3 Encode Latency Audit
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * === [Encode Latency Info] : From "raw capture done" to "encode done" :
 *  Stream	 Canvas 	Avg (us)   Max (us)   Min (us)	 Delta (us)
 *  0 		 0			35174	   51922	  18422 	 33500
 *  1 		 3			36824	   57011	  19900 	 37111
 *  2 		 1			37596	   57400	  20611 	 36789
 * @endcode
 *
 * Encode latency statistics are for streams that are in the encoding state.
 * Note that when obtaining encode latency statistics, ensure that the system is in the encoding
 * state; otherwise, there will be no valid statistics.
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * === [Encode Latency Info] : From "raw capture done" to "encode done" :
 *  Dsp has not started encoding!!!
 * @endcode
 *
 * @note
 * In the example, the <b>Delta</b> in <b>Encode Delay Info</b> is very large. The main reason for
 * this phenomenon is that the <b>I-frame</b> in the stream processing time is long, while the
 * <b>P-frame</b> processing time is short, so the difference between the two (<b>Delta</b>) is
 * large.
 *
 * @subsection vout_vin_latency_aud 3.4 VOUT-VIN Latency Audit
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * === [VOUT-VIN Latency Info] : From "raw capture done" to "vout display start"
 *  Vout		 Canvas 	Sync Cnt   Avg (us)   Max (us)	 Min (us)	Delta (us)
 *  2 		     2			181 	   36191	  44920 	 27249		17671
 * @endcode
 *
 * "VOUT-VIN latency info" shows the latency between VIN capture completed and VOUT display,
 * and can also help users to verify if the VIN-VOUT precise sync feature takes effect.
 * See @ref example_vin_vout_precise_sync "VIN-VOUT Precise sync".
 *
 * @subsection frame_drop_aud 3.5 IDSP and Encode Frame Drop Audit
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * === [IDSP Frame Drop Info] :
 *  Channel  Drop Count      Drop Rate (fps)     IDSP FPS     Status
 *  0        5               1.7                 30           Frame Dropped
 * @endcode
 * "IDSP Frame Drop Info" is used to audit the IDSP frame drop count; "Drop Rate (fps)" and "IDSP FPS"
 * can help users obtain the actual IDSP frame per second (fps) when there is IDSP frame drop. <b>Status</b> reflects the
 * current IDSP state. When <b>Drop Count</b> is greater than 0, it means that the current IDSP is
 * in the frame-dropped state (<b>Frame dropped</b>). Otherwise, it is in the normal (<b>OK</b>) state.
 *
 * @code {.c}
 * === [IDSP Group Channel Frame Discard Info] :
 * Group   Channel	 Discard Count	 Discard Rate (fps)  IDSP FPS	  Status
 * 0 	  0 		 0				 0.0				 30 		  OK
 * 0 	  1 		 0				 0.0				 30 		  OK
 * @endcode
 * "IDSP Group Channel Frame Discard Info" is used to audit the raw cuont being discard by IDSP proactively for
 * the cases like the raw is not within the channel grouping tolerance. If frame discard is reported in the audit info,
 * users can use “test_encode --debug-chan-group-tolerance” to adjust the chan group sync tolerance value to adapt RAW
 * capture done time drift between different sensors within one group.
 *
 * @code {.c}
 * === [Encode Frame Drop Info] :
 *  Stream	 Canvas 	Drop Count
 *  0 		 0			152
 *  1 		 3			185
 *  2 		 1			185
 * @endcode
 * "Encode Frame Drop Info" is used to audit the encode ( advanced video coding (AVC) / high-efficiency video coding (HEVC) / MJPEG ) frame drop count.
 *
 * @subsection enc_clk_aud 3.6 Encode Clock Audit
 * Encode clock audit is used to audit the actual encode clock and compare whether the clock is configured correctly.
 *
 * @code {.c}
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3	 // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)		 // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua	// For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua) // For CV72
 * board# test_encode -A -b0 -H3840x2144 -e
 * board# echo 0x2000 3 > /proc/ambarella/iav_audit
 * board# cat /proc/ambarella/iav_audit
 *
 * For cv5/cv52:
 *  === [Encode Clock Info] : gclk_core (khz) : 1140000
 *  Stream  Avg (khz)  Max (khz)  Min (khz)  Delta (khz)  Clk_Diff
 *  0       1137965    1138727    1137114    1613         1 ‰
 *
 * For cv72:
 *  === [Encode Clock Info] : gclk_vdsp (khz) : 960000
 *  Stream  Avg (khz)  Max (khz)  Min (khz)  Delta (khz)  Clk_Diff
 *  0       955570     957964     953517     4447         4 ‰
 * @endcode
 *
 * @note
 *  - In order to make audit clock accurate, it only supports run the specific use case
 *    of 4K ("3840x2144" is for height alignment) HEVC encode with "N = 1" on stream 0.
 *    The error shown by "clk_diff" is reasonable within 1%.
 *
 * @subsection vout_aud 3.7 VOUT Drop and Osd Sync Audit
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * === [VOUT Underflow and Osd Sync Info] :
 * Vout      Canvas     Vout Drop Cnt     Osd Sync Fail Cnt
 * 2         4          0                 0
 * @endcode
 * "VOUT Drop and Osd Sync Audit" is use to audit vout frame dorp and osd frame sync fail info. When the vout fps is lower than the canvas fps,
 * vout will not be able to display all frames in time, which will cause vout to drop frames and sync osd to frame fail.
 *
 * @subsection frame_sync_aud 3.8 Frame Sync (overaly and blur) Audit
 * @code {.c}
 * board# cat /proc/ambarella/iav_audit
 *
 * ==== [Audit - Frame Sync Audit to Check Overlay and Blur Sync Info] ====
 * Type	    Fail Count
 * Overlay  0
 * Blur	    0
 * @endcode
 * "Frame Sync Audit" is used to audit stream overlay and blur sync fail info. At present, ARM side can only audit the fail count
 * of all streams from DSP and can't distinguish them for each stream.
 *
 * @subsection example_iav_audit_proc Example 1: Full Report of IAV Audit Proc
 * @code {.c}
 * board# echo 0x43f3 3 > /proc/ambarella/iav_audit
 * board#
 * board# cat /proc/ambarella/iav_audit
 * The current audit print bitmap: 0x1f3
 * The last audit print bitmap: 0x0
 * The current audit time interval: 3s
 *
 *  bit[ 0]: enable     isr duration
 *  bit[ 1]: enable     isr interval
 *  bit[ 2]: disable    iav ioctl
 *  bit[ 3]: disable    imgproc ioctl
 *  bit[ 4]: enable     idsp delay
 *  bit[ 5]: enable     encode delay
 *  bit[ 6]: enable     VOUT-VIN delay
 *  bit[ 7]: enable     IAV IDSP frame drop audit
 *  bit[ 8]: enable     IAV encode frame drop audit
 *  bit[ 9]: enable     IAV vout drop and osd sync audit
 *  bit[10]: disable    ENC sync fail audit
 *  bit[11]: disable    EIS sync fail audit
 *  bit[12]: disable    Img scaler audit to check IDSP clock
 *  bit[13]: disable    Encode clock audit
 *  bit[14]: enable     Frame sync(ovrelay and blur) audit
 *
 * ======= Audit video info within 3s ========
 *
 *
 * === [Audit - ISR Duration Info]
 *  IRQ_NAME		status	   ISR_cnt	  ISR_FREQ (Hz)   Avg (us)	 Max (us)	Min (us)   Delta (us)
 *  vdsp			Enable	   181		  60			  0 		 2			0		   2
 *  venc			Enable	   273		  91			  0 		 0			0		   0
 *  vcap			Enable	   728		  242			  0 		 0			0		   0
 *  vin            Enable	   91		  30			  0 		 0			0		   0
 *
 *
 * === [Audit - ISR Interval Info]
 *  IRQ_NAME		status	   ISR_cnt	  Avg (us)	 Max (us)	Min (us)   Delta (us)
 *  vdsp_intvl	    Enable	   181		  16666 	 16684		16650	   34
 *  venc_intvl	    Enable	   273		  11143 	 39491		224 	   39267
 *  vcap_intvl	    Enable	   728		  4165		 29801		28		   29773
 *  vin_intvl 	    Enable	   91		  33327 	 33814		32851	   963
 *
 * === [IDSP Latency Info] : From "raw capture done" to "IDSP YUV output"
 *  Canvas	 Src			 Avg (us)	Max (us)   Min (us)   Delta (us)
 *  0 		 chan0_main 	 10598		10624	   10573	  51
 *  1 		 chan0_2nd		 10612		10637	   10589	  48
 *  2 		 chan0_3rd		 10608		10633	   10584	  49
 *  3 		 chan0_4th		 10604		10629	   10580	  49
 *
 *
 * === [Encode Latency Info] : From "raw capture done" to "encode done" :
 *  Stream	 Canvas 	Avg (us)   Max (us)   Min (us)	 Delta (us)
 *  0 		 0			35187	   51933	  18555 	 33378
 *  1 		 3			36899	   55466	  19911 	 35555
 *  2 		 1			29011	   45600	  12411 	 33189
 *
 *
 * === [VOUT-VIN Latency Info] : From "raw capture done" to "vout display start"
 *  Vout		 Canvas 	Sync Cnt   Avg (us)   Max (us)	 Min (us)	Delta (us)
 *  2 		     2			181 	   36191	  44920 	 27249		17671
 *
 *
 * === [IDSP Frame Drop Info] :
 *  Channel  Drop Count      Drop Rate (fps)     IDSP FPS     Status
 *  0        5               1.7                 30           Frame Dropped
 *
 *
 * === [IDSP Group Channel Frame Discard Info] :
 * Group   Channel	 Discard Count	 Discard Rate (fps)  IDSP FPS	  Status
 * There are no group channels!!!
 *
 *
 * === [Encode Frame Drop Info] :
 *  Stream	 Canvas 	Drop Count
 *  0 		 0			0
 *  1 		 3			0
 *  2 		 1			0
 *
 *
 * === [VOUT Drop and Osd Sync Info] :
 * Vout      Canvas     Vout Drop Cnt     Osd Sync Fail Cnt
 * 2         4          0                 0
 *
 *
 * ==== [Audit - Frame Sync Audit to Check Overlay and Blur Sync Info] ====
 * Type	    Fail Count
 * Overlay     0
 * Blur	    0
 * @endcode
 *
 * @subsection example_show_video_audit_info Example 2: Application for Video Pipeline Information Audit
 * Ambarella has opened the input / output control (IOCTL) interface to implement video pipeline information auditing.
 * The `show_video_audit_info` application is available for users to easily obtain the same statistics info as the IAV audit proc.
 * @code {.c}
 * board# show_video_audit_info -t 5 -i -I -d -D -f -F -v
 * @endcode
 *
 */
/*!
 * @file iav_poll.h
 * @brief
 * @version 0.1
 * @date 2022-07-01
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
 * @page fs_adv_iav_poll ADVANCED - Poll Interface
 *
 * @section iav_poll_intro 1. Introduction to Poll
 *
 * @subsection query_iav_data_intro 1.1 Poll Interface to Query IAV Data
 *
 * The image audio video(IAV) driver supports poll interface to query the IAV data. It waits for one of a series of events
 * to become ready to perform I/O. These events include the  @b IAV_DESC_FRAME, @b IAV_DESC_STATIS,
 * @b IAV_DESC_RAW, @b IAV_DESC_CANVAS, @b IAV_DESC_PYRAMID, @b IAV_DESC_Y12, @b IAV_DESC_PRE_COUNT
 * and so on. The caller should specify the events of interested before the poll. And then using
 * the poll API to wait for the events ready. This feature supports the multiple users and can poll multiple
 * events at one time.
 *
 * @subsection irq_sync_intro 1.2 Poll Interface to Sync Irq
 *
 * IAV driver supports to use standard poll mechanism to synchronize with different DSP interrupts.
 * With this feature users can synchronize their operations to the interrupt. IAV driver supports
 * vcap, vdsp, vapi, and venc interrupt sync now. IAV driver creates vcap, vdsp, and venc proc
 * file for interrupt sync. Vcap proc file is created for per channel and venc proc file is created
 * for per stream. Users can use the proc file to synchronize the certain interrupt, please check
 * unit_test/private/iav_test/dsp_v6/test_irq_sync.c
 *
 * ---
 *
 * @section section_iav_poll_example 2. Examples of Using Poll Interface
 *
 * @subsection query_iav_data_example_intro 2.1 Examples of Querying IAV Data
 *
 * @subsubsection example_iav_poll_data1 Example 2.1.1: Query Pyramid Data Using Poll
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_poll -p 0
 * @endcode
 *
 * @subsubsection example_iav_poll_data2 Example 2.1.2: Query Canvas Data Using Poll
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_poll -b 0 -b 1
 * @endcode
 *
 * @subsubsection example_iav_poll_data3 Example 2.1.3: Query Raw Data Using Poll
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_poll -r 8
 * @endcode
 *
 * @subsubsection example_iav_poll_data4 Example 2.1.4: Query Frame Using Poll
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_encode -A -h 1080p -b 0 -e
 * board# test_poll -f
 * @endcode
 *
 * @subsubsection example_iav_poll_data5 Example 2.1.5: Query Statis Data Using Poll
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_encode -A -h 1080p --mv-statis-enable 1 -b 0 -e
 * board# test_poll -S 0
 * @endcode
 *
 * @subsubsection example_iav_poll_data6 Example 2.1.6: Query Y12 Using Poll
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_poll -y 0
 * @endcode
 *
 * @subsubsection example_iav_poll_data7 Example 2.1.7: Query Data with the Multi-User Using Poll
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_dual_chan_single_sensor.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua         // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_dual_chan_single_sensor.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)   // For CV72
 * console1 :board#test_poll -r 8 -p 0 -p 1
 * console2 :board#test_poll -r 8 -p 0 -p 1
 * @endcode
 *
 * @subsection irq_sync_example_intro 2.2 Examples of Using Interrupt Synchronization
 *
 * @subsubsection example_vdsp_irq_sync Example 2.2.1: Vdsp irq sync
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_irq_sync -d
 * @endcode
 *
 * @subsubsection example_vcap_irq_sync Example 2.2.2: Vcap Irq Sync
 *
 * An example of channel 0 is provided as shown below.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_irq_sync -c -C 0
 * @endcode
 *
 * @subsubsection example_venc_irq_sync Example 2.2.3: Venc Irq Sync
 *
 * An example of stream 0 is provided as shown below.
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3     // For CV5 or CV52
 * (Or board# init.sh --na;modprobe imx274_mipi vinc_id=8)         // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0        // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-mode 0)  // For CV72
 * board# test_encode -A -b 0 -h1080p -e
 * board# test_irq_sync -e -s 0
 * @endcode
 *
 * @section section_poll_usage 3. Poll Interface Usage
 *
 * @subsection poll_iav_data_usage 3.1 Usage of Querying IAV Data
 *
 * Set the events to monitor:
 * @code {.c}
 * struct iav_poll_event_config poll_configs;
 * struct iav_querydesc_event *desc_event;
 *
 * desc_event = &poll_configs.desc_event[0];
 * desc_event->qid = IAV_DESC_PYRAMID;
 * desc_event->arg.pyramid.chan_id = 0;
 * desc_event = &poll_configs.desc_event[1];
 * desc_event->qid = IAV_DESC_CANVAS;
 * desc_event->arg.canvas.canvas_id = 0;
 * poll_configs.valid_num = 2;
 * if (ioctl(fd_iav, IAV_IOC_SET_POLL_EVENT_CFG, &poll_configs) < 0) {
 *   printf("IAV_IOC_SET_POLL_EVENT_CFG error\n");
 *   return -1;
 * }
 *
 * @endcode
 *
 * Wait for the event ready and process it:
 * @code {.c}
 * struct pollfd fds;
 * struct iav_querydesc query_desc;
 *
 * fds.fd = fd_iav;
 * fds.events = POLLIN | POLLERR;
 * if (poll(&fds, 1, -1) < 0) {
 *   printf("poll error\n");
 *   return -1;
 * } else {
 *   printf("poll success revents=%x\n", fds.revents);
 * }
 * if (fds.revents & POLLERR) {
 *   printf("poll get POLLERR\n");
 *   return -1;
 * }
 * if (fds.revents & POLLIN) {
 *   memset(&query_desc, 0, sizeof(struct iav_querydesc));
 *   query_desc.qid = IAV_DESC_POLL;
 *   if (ioctl(fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
 *     printf("IAV_IOC_QUERY_DESC error\n");
 *     return -1;
 *   }
 * }
 * switch (query_desc.qid) {
 * case IAV_DESC_PYRAMID:
 *   // Process data
 *   break;
 * case IAV_DESC_CANVAS:
 *   // Process data
 *   break;
 * case IAV_DESC_RAW:
 *   // Process data
 *   break;
 * case IAV_DESC_FRAME:
 *   // Process data
 *   break;
 * case IAV_DESC_STATIS:
 *   // Process data
 *   break;
 * case IAV_DESC_PRE_COUNT:
 *   // Process data
 *   break;
 * default:
 *   printf("unknown poll type\n");
 *   return -1;
 * }
 *
 * @endcode
 *
 * Clear the setting:
 * @code {.c}
 * if (ioctl(fd_iav, IAV_IOC_CLEAR_POLL_EVENT_CFG, NULL) < 0) {
 *   printf("IAV_IOC_CLEAR_POLL_EVENT_CFG error\n");
 *   return -1;
 * }
 *
 * @endcode
 *
 * @subsection poll_irq_sync_usage 3.2 Usage of Interrupt Synchronization
 *
 * The following is the sample code for IAV vdsp synchronization usage.
 *
 * @code {.c}
 * int fd;
 * struct pollfd fds = {0};
 * if ((fd = open("/proc/ambarella/vdsp_sync", O_RDWR, 0)) < 0) {
 *   printf("Open %s error!\n", name);
 *   return ;
 * }
 * fds.fd = fd;
 * fds.events = POLLIN | POLLERR;
 * // clear the old data
 * poll(&fds, 1, 0);
 * while (!quit_loop) {
 *   rval = poll(&fds, 1, WAIT_2S);
 *   if(rval < 0) {
 *     printf("poll error!\n");
 *     return ;
 *   } else if (rval == 0) {
 *     printf("poll timeout!\n");
 *     return ;
 *   } else {
 *     printf("poll success!\n");
 *   }
 *   if (fds.revents & POLLERR) {
 *     printf("vdsp irq sync get POLLERR\n");
 *     return ;
 *   }
 *   if (fds.revents & POLLIN) {
 *     //Doing user operations here.
 *   }
 * }
 *
 * @endcode
 *
 * The following is the sample code for IAV vcap sync usage. Vcap proc file is created for per channel.
 * The code for channel 0 is as below.
 *
 * @code {.c}
 * int fd;
 * struct pollfd fds = {0};
 * if ((fd = open("/proc/ambarella/vcap_0_sync", O_RDWR, 0)) < 0) {
 *   printf("Open %s error!\n", name);
 *   return ;
 * }
 * fds.fd = fd;
 * fds.events = POLLIN | POLLERR;
 * // clear the old data
 * poll(&fds, 1, 0);
 * while (!quit_loop) {
 *   rval = poll(&fds, 1, WAIT_2S);
 *   if(rval < 0) {
 *     printf("poll error!\n");
 *     return ;
 *   } else if (rval == 0) {
 *     printf("poll timeout!\n");
 *     return ;
 *   } else {
 *     printf("poll success!\n");
 *   }
 *   if (fds.revents & POLLERR) {
 *     printf("vdsp irq sync get POLLERR\n");
 *     return ;
 *   }
 *   if (fds.revents & POLLIN) {
 *     //Doing user operations here.
 *   }
 * }
 *
 * @endcode
 *
 * The following is the sample code for IAV venc sync usage. Venc proc file is created for per stream.
 * The code for stream 0 is as below.
 *
 * @code {.c}
 * int fd;
 * struct pollfd fds = {0};
 * if ((fd = open("/proc/ambarella/venc_0_sync", O_RDWR, 0)) < 0) {
 *   printf("Open %s error!\n", name);
 *   return ;
 * }
 * fds.fd = fd;
 * fds.events = POLLIN | POLLERR;
 * // clear the old data
 * poll(&fds, 1, 0);
 * while (!quit_loop) {
 *   rval = poll(&fds, 1, WAIT_2S);
 *   if(rval < 0) {
 *     printf("poll error!\n");
 *     return ;
 *   } else if (rval == 0) {
 *     printf("poll timeout!\n");
 *     return ;
 *   } else {
 *     printf("poll success!\n");
 *   }
 *   if (fds.revents & POLLERR) {
 *     printf("vdsp irq sync get POLLERR\n");
 *     return ;
 *   }
 *   if (fds.revents & POLLIN) {
 *     //Doing user operations here.
 *   }
 * }
 *
 * @endcode
 *
 */

/*!
 * @file customized_feature.h
 * @brief document for customized features
 * @version 0.1
 * @date 2022-10-25
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
 * @page fs_adv_customized_features ADVANCED - Customized Features
 *
 * @section capture_extra_raw 1. Capture Extra Raw Data
 * This chapter illustrates the feature of capturing extra raw data which are usually embedded in the
 * top or bottom lines of the sensor raw data. The extra raw data is typically customized as sensor
 * manufactured through mobile industry processor interface (MIPI®) embedded lines.
 *
 * @subsection extra_raw_data 1.1 Extra Raw Data
 * When the user application performs Video content analysis (VCA) or 3A (AE / AWB / AF) control,
 * the application may refer to the customized raw information, which is embedded in the top or
 * bottom lines of the sensor raw data. The customized raw data is usually in a format specified by
 * sensor manufacturer through MIPI embedded lines. CV5x supports capturing this customized raw data
 * from mobile industry processor interface (MIPI®) embedded lines, and attaching the data to
 * corresponding canvas / pyramid buffers or to 3A statistic data.
 *
 * For CV5x, there is dedicated hardware support to capture the customized raw data. Different from
 * previous platforms, CV5x is not required to to enforce uncompressed raw format to enable this feature.
 * This can save significant dynamic random access memory (DRAM) bandwidth for raw buffer transfer.
 * Users can specify compressed or packing raw data format, when extra raw data is enabled.
 *
 * @subsection extra_raw_configuration 1.2 Extra Raw Data Capture Configuration
 * Users can configure the extra raw data via the command line. Below are the parameters for extra raw
 * data capture.
 *
 * <table>
 * <caption id="table_extra_raw_data">Table 1-1. Extra Raw Data.</caption>
 * <tr><th> Item <th><div style="width:240px"><B>Parameter</B></div> <th>Description
 * <tr><td> --custom-extra-raw-vinc
 *     <td> vinc id >= 0
 *     <td> Specify the target video input (VIN) controller ID.
 * <tr><td> --custom-extra-raw-enable
 *     <td> 0: disable <br>
 *          1: enable
 *     <td> Enable / disable the function of capture extra raw data function for specified VIN controllers.
 * <tr><td> --custom-extra-raw-top
 *     <td> [0, 8]
 *     <td> Specify the top lines of sensor raw data, which will be captured as extra raw data.
 * <tr><td> --custom-extra-raw-bottom
 *     <td> [0, 8]
 *     <td> Specify the bottom lines of sensor raw data, which will be captured as extra raw data.
 * </table>
 *
 * @subsection extra_raw_example 1.3 Examples of Capturing Extra Raw Data
 * For the “Capture Extra Raw Data” feature, users are required to allocate a memory partition in the
 * continuous memory allocator (CMA) pool. By default, the “IAV_PART_EXTRA_RAW” partition size is 0.
 * Users can allocate a CMA memory partition for “Capture Extra Raw Data” via memuconfig. Users can
 * calculate the total extra raw buffer size with the following fomula.
 * @par Extra raw buffer size = pitch * (bottom lines + top lines)<br>
 * For Cooper SDK Amba build:
 * @code
 * build$ make menuconfig
 *        -> drv_modules
 *           -> platform
 *              -*- ambvideo-header (drv_modules/private/video/dsp_v6)
 *                  (0x400000) IAV Extra Raw Buffer Size
 * @endcode
 * For Cooper SDK Yocto build:
 * @code
 * build$ make menuconfig
 *        Main menu
 *          -> meta-ambabsp
 *            -> recipes-video
 *              -> ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)
 *                 (0x400000) IAV Extra Raw Buffer Size
 * @endcode
 *
 * The following example demonstrates how to enable the capture extra raw data function on CV5x platform and
 * how to attach it to a canvas buffer.
 * @code {.sh}
 * board# init.sh --na; modprobe imx586_mipi vinc_id=0 bus_id=5 pdaf=1
 * board# test_aaa_service -a&
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_8k_linear.lua \
 *        --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --custom-extra-raw-vinc 0 \
 *        --custom-extra-raw-top 2 --custom-extra-raw-bottom 0 --custom-extra-raw-enable 1
 * board# test_yuvcap -b0 -Y -f main --tcp -q
 * Canvas0 : Frame0, the first value of line0 = 0x55555500
 * Canvas0 : Frame0, the first value of line1 = 0xbeefdead
 * @endcode
 */
/*!
 * @file encode_from_yuv.h
 * @brief
 * @version 1.0
 * @date 2024-01-03
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
 * @page fs_adv_bypass_idsp_for_yuv_input ADVANCED - Bypass IDSP for YUV Input
 *
 * @section section_bypass_idsp_for_yuv_input 1. Bypass IDSP for YUV Input
 *
 * This feature is designed to support encoding directly from YUV, so that the YUV sensor
 * bypasses the image digital signal processor (IDSP).
 * The user configures the YUV sensor to output YUV data rather than RAW data. Bypassing
 * the IDSP in order to encode from YUV is supported in these cases.
 * Encoding from YUV directly conserves IDSP performance for the real video input (VIN).
 *
 * @subsection example_bypass_idsp_for_yuv_input Example 1: IDSP Bypass Configurations
 *
 * Bypassing the IDSP means that the encoder will query data from the YUV buffer,
 * requiring the channel to work in "VIN-only" mode.
 *
 * Both options `vcap_mode_flags = 0x7f` and `idsp_bypass_enable = 1` in the
 * channel configuration will set up the "VIN-only" mode pipeline for the IDSP bypass channel.
 *
 * With VIN-only mode, only one buffer can be set for the channel. Typically, it's the main buffer.
 * The configuration example below shows that video source (VSRC) 0 is used for the YUV input
 * source and is bound to channel 0.
 *
 * @code
 * vsrc_0 = {
 *     vsrc_id = 0,
 *     mode = "0",
 *     hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 *     fps = 15,
 *     bits= 0,
 * }
 * chan_0 = {
 *     id= 1,
 *     vsrc = vsrc_0,
 *     vcap_mode_flags = 0x7f,
 *     idsp_bypass_enable = 1,
 *     .......
 *     main = {
 *         max_output = {0, 0},
 *         input = {0, 0, 0, 0},
 *         output = {0, 0, 1920, 1536},
 *     },
 * }
 * _resource_config_ = {
 *     canvas = {
 *         {
 *            type = "encode",
 *            source = {"chan_0.main",},
 *         },
 *     }
 * @endcode
 *
 * Different YUV sensors may have different installation methods.
 * For IDSP bypass channel, a restriction of encoding is here it needs to specify stream's GOP length to 1.
 * The example below demonstrates using the X3J sensor as the YUV input with the following commands:
 *
 * @code {.c}
 * board# init.sh --na
 * board# modprobe max96712 id=0x1 vinc_id=0 port_mode=1 mfp4_clk=1 poc_pwr_gpio=0 sen_rst_gpio=5 fsync_gpio=8 hsync_gpio=-1 gmsl_mode=3
 * board# modprobe ambds_brg addr=0x10 mipi=1 yuv_mode=1 w=1920 h=1536 bits=8 yuv_pix_order=0 brg_id=0x1 fps=17066667 slave=1 clk=25000000
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg encode_from_yuv.lua --chan-vcap-mode-enable 1
 * board# test_encode -S0 -H 1920x1536 -b 0 -N 1 -e
 * @endcode
 *
 *
 */
/*!
 * @file lite_nn.h
 * @brief
 * @version 0.1
 * @date 2024-01-18
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
 * @page iq_lite_nn IQ - Lite - NN
 *
 * @section iq_lite_nn_history 0. Revision History
 *
 * <table>
 * <tr><th>Version  <th>Updated Date  <th>Modification
 * <tr><td>0.0.1    <td>20240124      <td>Initial Version
 * </table>
 *
 * - - - -
 *
 * @section iq_lite_nn_overview 1. Lite NN Overview
 *
 * Lite NN includes vivid high dynamic range (HDR) neural network (NN) and true motion NN.
 * - True motion uses NN to do motion detection, to get more reliable and accurate motion
 *   estimation to help motion compensated temporal filtering (MCTF) to do a better job.
 * - Vivid HDR uses NN to do tone mapping, rather than the traditional contrast enhancement (CE) block.
 *
 * - - - -
 *
 * @section iq_lite_nn_usage 2. Lite NN Usage
 *
 * This section introduces the usage of Lite NN by steps. Image flow library doesn’t support
 * to load Lite NN automatically.
 *
 * Users are required to enable Lite NN mode mannually.
 * Lite NN should be configured in <b>product_config.lua</b> which is parsed by `test_aaa_service`.
 *
 * To set up the Lite NN, follow the steps below:
 *
 * -# Configure menuconfig
 *  Select <tt>img-lite-nn-datas</tt>
 * 	- For Cooper Amba build
 * @code {.c}
 *    build $ make menuconfig
 *        packages  --->
 *        	idsp --->
 *        		[*] img-lite-nn-datas (packages/idsp/lite_nn_data/img_cv72)
 * @endcode
 *
 * 	- For Cooper Yocto build
 * @code {.c}
 *    build $ make menuconfig
 *        meta-ambalib  --->
 *        	recipes-video --->
 *        		[*] img-lite-nn (meta-ambalib/recipes-video/img-lite-nn)
 * @endcode
 *
 * -# Preparation on board side before running Lite NN
 * 	- Copy lite NN bin files to the board path, such as <b>/sdcard/mmcblk2p1/</b>
 * 	- Update <b>product_config.lua</b> to select Lite NN type and its bin file path on
 *        evk <tt>/usr/share/ambarella/idsp/product_config.lua</tt>.
 * @code {.c}
 * chan_0 = {
 * 	... ...
 * 	tm_nn_mode = 0, -- 0: disable tm nn; 1: enable tm nn
 * 	tm_nn_path = "sdcard/mmcblk2p1/vivid_hdr_nn.bin",
 * 	md_nn_mode = 1, -- 0: disable md nn; 1: enable md nn
 * 	md_nn_path = "/sdcard/mmcblk2p1/true_motion_nn.bin ",
 * }
 * @endcode
 *
 * -# Run Lite NN with sensor input
 * Take true motion NN with IMX678 on CV72_gage board as an example.
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx678_mipi vinc_id=0x8
 * board # test_aaa_service -a -p /usr/share/ambarella/idsp/product_config.lua &
 * board # cavalry_load -f /lib/firmware/cavalry.bin -r
 * board # test_encode --resource-cfg cv72_isp.lua --enc-mode 5 --raw-capture 1 --img-scale 1 --img-scale-format 2 --img-scale-max-in 1920x1080 --img-scale-max-out 1920x1080 --img-scale-job-queue-depth 8
 * board # test_encode -A -h 3840x2160 -b0 -e -B -h 1920x1080 -b1 -e
 * board # rtsp_server &
 * board # test_idsp_motion  -t0 -s1 -e1 -c0 -m 0 -d 0  -x 0 -y 0 -w 720 -h 360 &
 * @endcode
 *
 * - - - -
 *
 * @section iq_lite_nn_true_motion 3. True Motion
 *
 * This section introduces the basic idea of true motion.
 *  - Section @ref iq_lite_nn_true_motion_intro
 *  - Section @ref iq_lite_nn_true_motion_params
 *  - Section @ref iq_lite_nn_true_motion_invalid_params
 *
 * @subsection iq_lite_nn_true_motion_intro 3.1. Introduction
 *
 * True motion uses NN to do motion detection, to get more reliable and accurate motion
 * estimation to help MCTF to do a better job. A sensitivity is open to describe the
 * detection strength of different moving objects under different lighting conditions.
 *
 * @subsection iq_lite_nn_true_motion_params 3.2 ADJ Parameters
 *
 * Motion detection neural network is applied in current NN model to allow the movement
 * to be more accurately detected.
 *
 * In auto adjust (ADJ), the releated filter is 'nn_md' in 'fc_nn_pkg', it includes
 * the control of motion detection neural network. The 'nn_md' is applied in current
 * NN model to allow movement to be more accurately detected.
 *
 * <table>
 * <caption id="table_lite_nn_true_motion_params">Table 3-1. ADJ Parameters of True Motion.</caption>
 * <tr><th>Parameters             <th>Type     <th>Description
 * <tr><td>ik_nn_md_t sensitivity <td>unit 32  <td>Range:[0,128]
 * </table>
 *
 * As the sensitivity increases, it becomes easier to identify motion of small objects, and
 * the detection area of motion becomes larger. Due to the different relationship between
 * the noise and motion of each sensor under each gain, the MD_sensitivity can be set
 * different value under each gain.
 *
 * @subsection iq_lite_nn_true_motion_invalid_params 3.3 Invalid Parameters List
 *
 * These two blocks will no longer take effect and instead the motion detection results
 * will be taken from motion detection (MD) NN:
 * @par Motion_detect: fc_motion_detect
 *
 * <table>
 * <caption id="table_lite_nn_motion_detect_params"> Table 3-2. ADJ Parameters of Motion detect.</caption>
 * <tr><th>Parameters          <th>Type         <th>Description
 * <tr><td>enable              <td>uint32       <td>1 for enable; 0 for disable
 * <tr><td>lev_add_1_method    <td>uint32       <td>value: 0, 2, 7, 8, 12
 * <tr><td>lev_add_1_table[64] <td>uint32 array <td>range: [0, 255]
 * <tr><td>lev_add_2_method    <td>uint32       <td>value: 0, 2, 7, 8, 12
 * <tr><td>lev_add_2_table[64] <td>uint32 array <td>range: [0, 255]
 * <tr><td>lev_mul_1_method    <td>uint32       <td>value: 0, 2, 7, 8, 12
 * <tr><td>lev_mul_1_table[64] <td>uint32 array <td>range: [0, 255]
 * <tr><td>lev_mul_2_method    <td>uint32       <td>value: 0, 2, 7, 8, 12
 * <tr><td>lev_mul_2_table[64] <td>uint32 array <td>range: [0, 255]
 * <tr><td>local_lighting      <td>uint32       <td>range: [0,1]
 * <tr><td>motion_response     <td>uint32       <td>range: [1, 511]
 * <tr><td>noise_base          <td>uint32       <td>range: [0, 4095]
 * <tr><td>slow_mo_sensitivity <td>uint32       <td>range: [0, 19]
 * </table>
 *
 * @par Motion_detect_and_mctf: fc_motion_detect_and_mctf
 *
 * <table>
 * <caption id="table_lite_nn_mctf_params"> Table 3-3. ADJ Parameters of MCTF.</caption>
 * <tr><th>Parameters              <th>Type       <th>Description
 * <tr><td>local_lighting_radius   <td>unit32     <td>Range:[0,68]
 * </table>
 *
 * @note
 *  - The 'fc_motion_detect_pos_dep' works with md_nn_mode.
 *  - 'y/cb/cr_temporal_alpha*' and 'y/cb/cr_temporal_t*'
 *     - The valid T value greater than 1 is considered to the motion part.
 *     - The rest are consistent with MCTF usage of traditional image digital signal processing (IDSP) tuning guide.
 *
 * - - - -
 *
 * @section iq_lite_nnctrl_vivid_hdr 4. Vivid HDR
 *
 * This section introduces the basic idea of vivid HDR.
 *  - Section @ref iq_lite_nnctrl_vivid_hdr_intro
 *  - Section @ref iq_lite_nnctrl_vivid_hdr_params
 *
 * @subsection iq_lite_nnctrl_vivid_hdr_intro 4.1 Introduction
 *
 * Vivid HDR uses NN to do tone mapping, rather than the traditional CE block.
 *
 * @subsection iq_lite_nnctrl_vivid_hdr_params 4.2 ADJ Parameters
 *
 * <table>
 * <caption id="table_lite_nn_vivid_hdr"> Table 4-1. ADJ Parameters of Vivid HDR.</caption>
 * <tr><th>Parameters                        <th>Type     <th>Description
 * <tr><td>f_ce_nn_alpha_beta_gamma alpha    <td>unit32   <td>Range:[0,255]
 * <tr><td>f_ce_nn_alpha_beta_gamma beta     <td>unit32   <td>Range:[0,255]
 * <tr><td>f_ce_nn_alpha_beta_gamma gamma    <td>unit32   <td>Range:[0,255]
 * </table>
 *
 * - - - -
 *
 * @section iq_lite_nnctrl_api 5. Image NNCtrl Library API
 *
 *  - Section @ref iq_lite_nnctrl_api_intro
 *  - Section @ref iq_lite_nnctrl_api_detail
 *     - Section @ref iq_lite_nnctrl_api_detail_common
 *     - Section @ref iq_lite_nnctrl_api_detail_aisp
 *     - Section @ref iq_lite_nnctrl_api_detail_lite_nn
 *  - Section @ref iq_lite_nnctrl_api_detail_compute_method
 *  - Section @ref iq_lite_nnctrl_api_detail_example
 *     - Section @ref iq_lite_nnctrl_api_detail_example_mdnn
 *     - Section @ref iq_lite_nnctrl_api_detail_example_tmnn
 *
 * @subsection iq_lite_nnctrl_api_intro 5.1 Introduction
 *
 * The image neural network control (NNCtrl) library is an image middleware which is
 * responsible for loading image signal processor (ISP) NN networks (AISP and Lite NN)
 * and runtime selecting specified network based on 3A related results.
 *
 * @par Key features supported by the image NNCtrl APIs include the follwoing:
 * - Load ISP NN networks into dynamic random access memory (DRAM)
 * - Set / get noise reduction strength (NR strength)
 * - Set / get contrast enhancement strength (CE strength)
 * - Set / get motion detection strength (MD strength)
 * - Set / get vivid HDR control strength
 *
 * @subsection iq_lite_nnctrl_api_detail 5.2 API Details
 *
 * @subsubsection iq_lite_nnctrl_api_detail_common 5.2.1 Common APIs for AISP and Lite NN
 *
 * * AMBA_API <tt>int img_nnctrl_init(int fd_iav)</tt>
 * 	- This API initializes the library with image audio video (IAV) driver. It must be called before all other functions.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_deinit()</tt>
 * 	- This API de-initializes the library. It must be called after all other functions.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_precheck()</tt>
 * 	 This API resumes / clear data based on digital signal processor (DSP) status.
 * 	 Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_set_config(img_nn_config_info_t *config_info)</tt>
 * 	- This API sets the configuration information from user app.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>void img_nnctrl_set_loglevel(int level)</tt>
 * 	- This API sets log level. 0: error, 1: info; 2: debug: 3: print
 *
 * * AMBA_API <tt>void img_nnctrl_get_loglevel(void)</tt>
 * 	- This API gets current log level. It prints log level in console.
 *
 * * AMBA_API <tt>int img_nnctrl_get_version(img_nnctrl_version_t *ver)</tt>
 * 	- This API gets the version information of image NNCtrl library.
 * 	- Returns 0 = success, -1 = error.
 *
 * @subsubsection iq_lite_nnctrl_api_detail_aisp 5.2.2 Unique APIs for AISP
 *
 * * AMBA_API <tt>int img_nnctrl_get_aisp_default(uint32_t *nr_str, uint32_t *ce_str)</tt>
 * 	- This API gets the default NR strength and CE strength.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_set_nr_ce(uint32_t nr_str, uint32_t ce_str)</tt>
 * 	- This API sets the NR strength and CE strength. Both parameters should be valid.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_nr(uint32_t *nr_str)</tt>
 * 	- This API gets current NR strength.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_set_nr(uint32_t nr_str)</tt>
 * 	- This API sets NR strength. The CE strength uses the current value.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_ce(uint32_t *ce_str)</tt>
 * 	- This API gets current CE strength.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_set_ce(uint32_t ce_str)</tt>
 * 	- This API sets CE strength. The NR strength uses the current value.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_md(uint32_t *md_str)</tt>
 * 	- This API gets current MD strength.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_set_md(uint32_t md_str)</tt>
 * 	- This API sets MD strength. The NR strength uses the current value.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_do_execute()</tt>
 * 	- This API executes AISP configuration.
 * 	- Returns 0 = success, -1 = error.
 *
 * @subsubsection iq_lite_nnctrl_api_detail_lite_nn 5.2.3 Unique API for Lite NN
 *
 * * AMBA_API <tt>int img_nnctrl_set_nn_tm(nn_tm_t *tm, uint32_t chan_id)</tt>
 * 	- This API sets vivid HDR control parameters for specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_nn_tm(nn_tm_t *tm, uint32_t chan_id)</tt>
 * 	- This API gets vivid HDR control parameters of specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_set_nn_ce(uint32_t ce_str, uint32_t chan_id)</tt>
 * 	- This API sets CE strength for specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_nn_ce(uint32_t *ce_str, uint32_t chan_id)</tt>
 * 	- This API gets CE strength of specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_set_nn_md(uint32_t md_str, uint32_t chan_id)</tt>
 * 	- This API sets MD strength for specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_nn_md(uint32_t *md_str, uint32_t chan_id)</tt>
 * 	- This API gets MD strength of specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_set_nn_nr(uint32_t nr_str, uint32_t chan_id)</tt>
 * 	- This API sets NR strength for specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_nn_nr(uint32_t *nr_str, uint32_t chan_id)</tt>
 * 	- This API gets NR strength of specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_do_nn_execute(uint32_t chan_id)</tt>
 * 	- This API executes the NN configuration for specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_nn_md_status(uint32_t chan_id, u8 *status)</tt>
 * 	- This API queries the true motion NN status of specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_nn_tm_status(uint32_t chan_id, u8 *status)</tt>
 * 	- This API queries the vivid HDR NN status of specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * * AMBA_API <tt>int img_nnctrl_get_default_md_nn(uint32_t *nr_str, uint32_t *ce_str, uint32_t chan_id)</tt>
 * 	- This API gets the default NR strength and CE strength of specified channel index.
 * 	- Returns 0 = success, -1 = error.
 *
 * @subsection iq_lite_nnctrl_api_detail_compute_method 5.3 Computation Method of NR Strength and CE Strength
 * * NR strength: Basically, it varies with the gain result. Users can set NR strength
 *                they want to run. It is defined in `nn_container_pkg` part in ADJ file.
 * * CE strength: It is calculated based on shutter ratio result. The calculation is as follow:
 *                CE_strength = Shutter_ratio * 8
 *
 * @note
 * - When CE_strength is greater than 255, it should be clipped to 255.
 *
 * @subsection iq_lite_nnctrl_api_detail_example 5.4 Example Usage
 *
 * @subsubsection iq_lite_nnctrl_api_detail_example_mdnn 5.4.1 Example on True Motion
 *
 * @par Prepare IDSP stage
 * @code
 * # Initialize image nnctrl library
 * img_nnctrl_init(fd_iav);
 *
 * # Pre-check image nnctrl library
 * img_nnctrl_precheck();
 *
 * # Set img nn config info
 * img_nnctrl_set_config(config_info);
 *
 * # Set first NR and CE strength to IDSP before entering preview
 * # This step is related to whether DSP can work or not. Please make sure NR and CE are
 * # supported in the AISP network
 * img_nnctrl_set_nr_ce(nr_str, ce_str);
 * @endcode
 *
 * @par Runtime update after entering preview
 * @code
 * # Update NR and CE strength based on Chapter 3
 * img_nnctrl_set_nr_ce(nr_str_update, ce_str_update);
 *
 * # If users want to update only NR strength
 * # Update NR based on Chapter 3
 * img_nnctrl_set_nr(nr_str_update);
 *
 * # If users want to update only CE strength
 * # Update CE strength based on Chapter 3
 * img_nnctrl_set_ce(ce_str_update);
 * @endcode
 *
 * @subsubsection iq_lite_nnctrl_api_detail_example_tmnn 5.4.2 Example on Vivid HDR
 * This section content is still under construction.
 *
 * @par Exit preview stage
 * @code
 * # De-initialize image nnctlr library
 * img_nnctrl_deinit();
 * @endcode
 *
 * - - - -
 */
/*!
 * @file debug.h
 * @brief
 * @version 0.1
 * @date 2022-06-10
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
 * @page fs_others_debug OTHER - Debug Option
 *
 * @section other_disp_cfg 1. Others:  Display Current Configuration
 * @subsection example_other_disp_cfg1 Example 1: Chip
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode --show-chip-info
 * @endcode
 *
 * @subsection example_other_disp_cfg2 Example 2: Image Audio Video (IAV) Driver Version
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode --show-driver-info
 * @endcode
 *
 * @subsection example_other_disp_cfg3 Example 3: Dynamic Random-Access Memory (DRAM) Layout Information
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode --show-dram-layout
 * @endcode
 *
 * @subsection example_other_disp_cfg4 Example 4: Encoding Resource Configuration
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode --show-resource-info
 * @endcode
 *
 * @subsection example_other_disp_cfg5 Example 5: Channel, Canvas, and Stream Resource Configuration
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode --show-resource-cfg
 * @endcode
 *
 * @subsection example_other_disp_cfg6 Example 6: Encode Configuration
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode -A -H1080p -b0 -e
 * board# test_encode --show-encode-config
 * @endcode
 *
 * @subsection example_other_disp_cfg7 Example 7: Stream Configuration
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode -A -H1080p -b0 -e
 * board# test_encode --show-stream-info
 * @endcode
 *
 * @subsection example_other_disp_cfg8 Example 8: Canvas State
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode -A -H1080p -b0 -e
 * board# test_encode --show-canvas-state
 * @endcode
 *
 * @subsection example_other_disp_cfg9 Example 9: All Information
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode --show-all-info
 * @endcode
 *
 * @subsection example_other_disp_cfg10 Example 10: Supported Feature Set
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_encode --show-feature-set
 * @endcode
 *
 * - - - -
 *
 * @section other_disp_lat 2. Others:  Display Pipeline Latency
 * @subsection example_other_disp_lat Example 11: Pipeline Latency from Capture to Encode
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72 
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board# test_stream --nofile -v &
 * board# test_encode -A -h 1080p -e
 *
 * (message printed by test_stream)
 * stream A:       125910 frames, 30 fps,         4170898261       bytes,  7678 kbps
 * type=1, is_skipped 0, size=160199, addr=0x1209728, strm_id=0, sesn_id=486509669, frame_num=60, monotonic_pts=8684650, mono_diff=3004, enc_done_pts = 8688618, enc_pipe_time = 3968, reso=1920x1080, slice_header_offset = 98
 * type=3, is_skipped 0, size=4929, addr=0x1369984, strm_id=0, sesn_id=486509669, frame_num=61, monotonic_pts=8687651, mono_diff=3001, enc_done_pts = 8691529, enc_pipe_time = 3878, reso=1920x1080, slice_header_offset = 18
 * type=3, is_skipped 0, size=25719, addr=0x1374976, strm_id=0, sesn_id=486509669, frame_num=62, monotonic_pts=8690651, mono_diff=3000, enc_done_pts = 8691575, enc_pipe_time = 924, reso=1920x1080, slice_header_offset = 18
 * @endcode
 * @sa @ref fs_adv_pl_latency
 *
 * - - - -
 *
 * @section mmb_function 3. Others: Debug Anonymous MMB
 *
 * This function is used to debug the anonymous MMB auto-recycling feature. It can help simulate customers
 * using an anonymous MMB in multiple-thread or multiple-process cases.
 *
 * @subsection example1_mmb_function Example 16: Anonymous MMB Used in Father-and-Child Processes with the Same FD
 * @code
 * board# test_mempart -a -s 0x1000 -t 0x33
 * (message printed)
 * Anonymous MMB test mode map: 0x33.
 * anonymous mem_part[5119] has been allocated successfully.
 *         Base Address: [0xA0081000], Size [       4 KB].
 * global iav fd 3
 * start to fork child process
 * MMB[5119]: Got virtual addr 0xa0081000, size 4096
 * Main process not quit
 * MMB[5119]: Got virtual addr 0xa0081000, size 4096
 * Child process not quit
 * board#(another consle) cat /proc/ambarella/cma  //check the MMB using state
 * (message printed)
 * ANONYMOUS_MMB    pid    ref_cnt    user_name
 * buf_id: 5119
 * |-               357    2          test_mempart
 * @endcode
 *
 * @subsection example2_mmb_function Example 17: Anonymous MMB Used in Father-and-Child Processes with Different FD
 * @code
 * board# test_mempart -a -s 0x1000 -t 0x77
 * (message printed)
 * Anonymous MMB test mode map: 0x77.
 * anonymous mem_part[4351] has been allocated successfully.
 *         Base Address: [0xA0081000], Size [       4 KB].
 * global iav fd 3
 * start to fork child process
 * Main process create fd 4
 * MMB[4351]: Got virtual addr 0xa0081000, size 4096
 * Main process not quit
 * Child process create fd 4
 * MMB[4351]: Got virtual addr 0xa0081000, size 4096
 * Child process not quit
 * board#(another consle) cat /proc/ambarella/cma  //check the MMB using state
 * (message printed)
 * ANONYMOUS_MMB    pid    ref_cnt    user_name
 * buf_id: 4351
 * |-               309    0          test_mempart
 * |-               309    1          test_mempart
 * |-               310    1          test_mempart
 * @endcode
 *
 * @subsection example3_mmb_function Example 18: Anonymous MMB Used in Multiple Independent Processes
 * @code
 * board#(console A) test_mempart -a -s 0x1000 -t 0x3
 * (message printed)
 * Anonymous MMB test mode map: 0x3.
 * anonymous mem_part[5119] has been allocated successfully.
 *         Base Address: [0xA0081000], Size [       4 KB].
 * global iav fd 3
 * MMB[5119]: Got virtual addr 0xa0081000, size 4096
 * Main process not quit
 * board#(console B) test_mempart -m 5119 --test_mode 0x3
 * (message printed)
 * Anonymous MMB test mode map: 0x3.
 * global iav fd 3
 * MMB[5119]:No map size specified, map total mmb. Size 4096.
 * MMB[5119]: Got virtual addr 0xa0081000, size 4096
 * Main process not quit
 * board#(console C) cat /proc/ambarella/cma  //check the MMB using state
 * (message printed)
 * ANONYMOUS_MMB    pid    ref_cnt    user_name
 * buf_id: 5119
 * |-               348    1          test_mempart
 * |-               349    1          test_mempart
 * board#(console C) kill 348 //kill test_mempart in console A
 * board#(console C) cat /proc/ambarella/cma  //check the MMB using state
 * (message printed)
 * ANONYMOUS_MMB    pid    ref_cnt    user_name
 * buf_id: 5119
 * |-               349    1          test_mempart
 * @endcode
 *
 * - - - -
 *
 * @section perf_function 4. Others: Debug Performance
 *
 * This chapter demonstrates options related to digital signal processor (DSP) performance.
 * These options can aid the device in achieving improved performance under specific conditions.
 *
 * @subsection example1_perf_function Example 19: Enable Optimal DSP Performance Mode
 * This feature improves CV5x DSP performance as a debug option; it is used only for multiple-video
 * input (VIN) / multiple-channel scenarios, and is not applicable for single-channel cases. Extra DSP
 * resources may be required to support this option.
 *
 * @note
 * The following are three items for channel configuration that must be the same across all channels.
 * <table>
 * <caption id="table_channel_item">Table 5-1. Channel Configurations.</caption>
 * <tr><th> Item                          			<th> <B>Description</B></div>
 * <tr><td> rotate_cw                               <td> Enable 90-degree clockwise rotation.
 * <tr><td> expo_num                  				<td> Specify the digital overlap high dynamic range (DOL-HDR) exposure frame number.
 * <tr><td> vcap_mode_flags                         <td> Fixed Value: 0x00, advanced ISO mode. This is the mode for lowest latency from VIN to video output (VOUT).
 * </table>
 *
 * Use the option `--debug-perf-opt-enable`  to enable optimal DSP performance mode. The example
 * below encodes 20 streams from four channels.
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=0x40b8
 * board# test_aaa_service -a&
 * board# test_encode --debug-perf-opt-enable 1 --resource-cfg cv5_four_chan_2xhdr_20stream_dsp_opt_perf_mode.lua --enc-mode 0
 * (message printed)
 * >>> AAA prepare done.
 * init 3A done
 * loop start now
 * [Amage] launch_amage_server!!!
 * >>> Amage server start done.
 * >>> AAA start done.
 * enable preview done
 * board# test_encode -S 0 -h 2160x3840 -b 0
 * board# test_encode -S 1 -h 608x800 -b 1
 * board# test_encode -S 2 -h 2160x3840 --frame-factor 1/30 -b 0
 * board# test_encode -S 3 -h 1088x1920 -b 2
 * board# test_encode -S 4 -m 720x1280 -b 3
 * board# test_encode -S 5 -h 2160x3840 -b 4
 * board# test_encode -S 6 -h 608x800 -b 5
 * board# test_encode -S 7 -h 2160x3840 --frame-factor 1/30 -b 4
 * board# test_encode -S 8 -h 1088x1920 -b 6
 * board# test_encode -S 9 -m 720x1280 -b 7
 * board# test_encode -S 10 -h 2160x3840 -b 8
 * board# test_encode -S 11 -h 608x800 -b 9
 * board# test_encode -S 12 -h 2160x3840 --frame-factor 1/30 -b 8
 * board# test_encode -S 13 -h 1088x1920 -b 10
 * board# test_encode -S 14 -m 720x1280 -b 11
 * board# test_encode -S 15 -h 2160x3840 -b 12
 * board# test_encode -S 16 -h 608x800 -b 13
 * board# test_encode -S 17 -h 2160x3840 --frame-factor 1/30 -b 12
 * board# test_encode -S 18 -h 1088x1920 -b 14
 * board# test_encode -S 19 -m 720x1280 -b 15
 * board# test_encode --start-multi 0~19
 Start encoding for stream 0xfffff successfully
 * @endcode
 *
 * For details, refer to <a href="script/cv5_four_chan_2xhdr_20stream_dsp_opt_perf_mode.lua" target="_blank"><b>cv5_four_chan_2xhdr_20stream_dsp_opt_perf_mode.lua</b></a>.
 *
 * @subsection example1_hevc_mode Example 20: Set HEVC Encode Mode
 * This feature supports two high-efficiency video coding (HEVC) encode modes, 0: default, 1: good quality. The default is 0.
 * Use `--debug-hevc-enc-mode` option to specify the HEVC encode mode.
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --debug-hevc-enc-mode 1 --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua        // For CV5 or CV52
 * (Or board# test_encode --debug-hevc-enc-mode 1 --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -S 0 -H 1920x1080 -b 0 -e
 * 1920x1080 resolution is 1920x1080
 * Start encoding for stream 0x1 successfully
 * @endcode
 *
 * @subsection example_aaa_overlay Example 21: AAA Statistics Display on Stream
 * AAA statistics can be displayed on stream in real-time, on-screen display (OSD) of the per-frame shows AAA statistics of this frame, including shutter and gain, so the user can debug the image quality via this feature.
 * The picture below shows the AAA statistics overlay.
 *
 * @image html AAA_statis_debug_overlay.png Figure 4-1. AAA Statistics Display on Stream.
 * Here is an example of how to use it.
 * @code
 * (terminal 1)
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a -s&
 * board# test_encode --resource-cfg /usr/local/bin/scripts/cv5_vin0_4k_linear.lua  --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board# test_encode -A -b 0 -h 3840x2160 -e
 * board# rtsp_server &
 * (terminal 2)
 * board# test_textinsert --aaa-display
 * @endcode
 *
 */
/*!
 * @file others.h
 * @brief
 * @version 0.1
 * @date 2020-02-15
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
 * @page fs_others_miscellaneous OTHER - Miscellaneous
 *
 * @section rtsp_server 1. Others:  RTSP Server
 * Cooper platform works as an RTSP server By default. User can connect it to an RTSP client, and then
 * can view live streams through RTSP client.
 *
 * @note When the user specifies `"--account"` option with the account file and specifies `"--rtsp-auth-*"`
 * option to enable authentication, RTSP client will pop up a dialog for `"account/password"`.
 * The default authentication method is digest.
 *
 * @subsection example_rtsp1 Example 1: RTSP server works as no authentication method
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board # test_encode -A -H1080p -b 0 -e
 * board # rtsp_server &
 * @endcode
 *
 * @subsection example_rtsp2 Example 2: RTSP server works as basic authentication method
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board # test_encode -A -H1080p -b 0 -e
 * board # rtsp_server --rtsp-auth-basic --account /usr/local/bin/rtsp_accounts.lc&
 * @endcode
 *
 * @subsection example_rtsp3 Example 3: RTSP server works as digest authentication method
 * @code
 * board# init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board# init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                    --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)
 * board # test_encode -A -H1080p -b 0 -e
 * board # rtsp_server --rtsp-auth-digest --account /usr/local/bin/rtsp_accounts.lc&
 * @endcode
 *
 *
 */
/*!
 * @file faq.h
 * @brief
 * @version 1.0
 * @date 2022-09-19
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
 * @page fs_others_faq OTHER - FAQ
 *
 * @section faq_block_diagram_of_the_chip 1. Block Diagram of the Chip (Single VIN)
 *
 * The following figure shows the data flow of the chip (single VIN).
 * @image html data_flow_of_chip_v6.png "Data Flow of Chip"
 * Before proceeding, read the following to better understand the system.
 * - The main buffer is generated from sensor with Digital Pan/Tilt/Zoom (DPTZ) type I,
 *   and other five sub-buffers are generated from the main buffer with the DPTZ type II.
 *   As a result, updating the main buffer affects all five sub-buffers.
 * - VIN size >= main buffer size >= sub-buffer size.
 * - For information on the limitation of each buffer, please refer to @ref fs_basic_source_buffer.
 * - Stream is different from buffer.
 *   There are 6 buffers and 20 streams for CV5x / CV7x, and streams can use the same buffer as the
 *   video source or use different buffers for the video source.
 *   As a result, the ratio between buffers and streams is unequal.
 * - DPTZ is not used from the source buffer to the encoder;
 *   however, crop can be used for encoding from different areas in the same buffer.
 * - The overlay / blur is inserted between the buffer and encoder, so if all the streams come from the same buffer,
 *   they will share the same overlay / blur.
 *   Therefore, to obtain different overlay / blur, set streams to encode from different buffers.
 * - Because privacy mask (PM) is inserted in the main buffer, all streams will include PM.
 *
 * @section faq_max_encode_performance 2. Max Encode Performance
 *
 * Each Cooper platform has several part numbers with a different maximum encode performance.
 * For details, refer to the Ambarella Cooper Linux SDK Release Notes document.
 *
 * @section faq_obtain_video_data_efficiently 3. Obtain Video Data Efficiently
 *
 * Because the DSP provides H.264 / H.265 RAW data,
 * the core task is to efficiently fetch bitstream
 * and avoid data copy while connecting the user's app / middleware and the Ambarella SDK.<br>
 * The data is stored in the bitstream buffer (BSB) regardless of the amount of streams used.
 * The buffer is located at a physical continual address which is mapped to the user space in Linux.
 * As a result, the buffer uses different addresses in different processes,
 * which is convenient for data point delivery between various processes with no copy.<br>
 * To efficiently obtain video data, perform the following steps:<br>
 * To obtain the stream, refer to the test samples `(test_stream/test_bsreader)` in the SDK.
 * The following command uses the '"test_stream.c"' as an example.<br>
 * @code
 * query_mem.mid = IAV_MEM_PARTITION;
 * part_info = &query_mem.arg.partition;
 * part_info->pid = IAV_PART_BSB;
 * ioctl(fd_iav, IAV_IOC_QUERY_MEMBLOCK, &query_mem);
 * bsb_size = part_info->mem.length;
 * bsb_mem = mmap(NULL, bsb_size * 2, PROT_READ, MAP_SHARED, fd_iav, part_info->mem.addr);
 * @endcode
 * The code above shows how to obtain the base virtual address of BSB in the current process.
 * This base address will be different for various processes.
 * @code
 * query_desc.qid = IAV_DESC_FRAME;
 * ioctl(fd_iav, IAV_IOC_QUERY_DESC, &query_desc);
 * @endcode
 * Additionally, the code above can obtain the address offset between each frame;
 * this value can be transferred between different processes.
 * However, users should not call <B>IAV_IOC_QUERY_DESC</B> simultaneously during different processes
 * because the same frame cannot be repeatedly fetched.<br>
 * Moreover, users should not create processes to call <B>IAV_IOC_QUERY_DESC</B> for every stream,
 * as this is used to obtain the frames together and distribute them out to every stream.<br>
 * BSB is a ring buffer;
 * the time for data overflow is determined by the BSB size and the frame rate for each stream.
 * However, under normal circumstances, users can obtain the data for the file store
 * or net transfer directly without loosing data.
 * As a result, it is not necessary to create a new pool buffer for the data cycle save,
 * as it will not be efficient for dynamic random-access memory (DRAM) bandwidth nor the CPU.<br>
 * Use make menuconfig to change the size of the bitstream buffer.
 * For details, refer to the Doxygen CMA Driver document.
 *
 * @section faq_synchronization_between_3a_and_encode 4. Synchronization between 3A and Encode
 *
 * This section describes the work flow of synchronization between encode and the image applications.<br>
 * The following illustrates the work flow.
 * @image html illustration_of_synchronization_flow.png "Illustration of Synchronization Flow"
 * The image process includes multiple threads:  one is a Netlink thread; all others are 3A threads.
 * Netlink synchronization occurs only between the Netlink thread in the image process and the IAV driver.<br>
 * The encode process does not directly join this.
 * The figure above describes two flows of synchronization between the images and the encode applications.
 * 1. Sequence of "enter preview state":
 *    - (`test_aaa_service`) Establish Netlink connection with the IAV driver from the user space.
 *    - (`test_aaa_service`) Wait for "prepare_3a" message from the kernel space.
 *    - (`test_encode`) Call IOCTL to issue the encode commands to enter into the preview state
 *      and wait for the IOCTL calls to be complete.
 *    - (`IAV driver`) Check the parameters from "test_encode",
 *      and then send "prepare_3a" message to the image application,
 *      and wait for the acknowledgment (ACK) from the user space.
 *    - (`test_aaa_service`) Receive the "prepare_3a" message and prepare the IDSP bin for 3A configuration.
 *    - (`test_aaa_service`) Send "prepare_3a" ACK to the kernel
 *      and wait for the "start_3a" message from the kernel.
 *    - (`IAV driver`) Receive the "prepare_3a" ACK from the user space,
 *      then issue commands to the DSP and enter the preview state.
 *    - (`IAV driver`) Send "start_3a" message to the image application
 *      and wait for the ACK from the user space.
 *    - (`test_aaa_service`) Receive the "start_3a" message, create, and start 3A working threads.
 *    - (`test_aaa_service`) Send "start_3a" ACK to kernel, and wait for "stop_3a" message from the kernel space.
 *      Until then, all 3A threads are kept running to receive the 3A API as usual.
 *    - (`IAV driver`) Receive the "start_3a" ACK from the user space
 *      and return the IOCTL callings to "test_encode".
 *    - (`test_encode`) Exit from IOCTL callings.
 *    - The system now enters the preview state and the image quality is correct.
 *    - In the preview state, all 3A threads are run to receive the image API as usual.
 *      All image API callings go directly to 3A threads, but not to the Netlink thread.
 * 2. Sequence of "enter idle state":
 *    - (`test_aaa_service`) Wait for the "stop_3a" message from the kernel space.
 *    - (`test_encode`) Call IOCTL to issue the encode command to enter the IDLE state,
 *      and wait for the IOCTL callings to be complete.
 *    - (`IAV_driver`) Check the parameters from "test_encode",
 *      then send a "stop_3a" message to the image application, and wait for the ACK from the user space.
 *    - (`test_aaa_service`) Receive the "stop_3a" message and stop the 3A working threads.
 *    - (`test_aaa_service`) Send "stop_3a" ACK to kernel and wait for the "prepare_3a" message from the kernel.
 *    - (`IAV driver`) Receive the "stop_3a" ACK from the user space,
 *      and then issue commands to DSP, and enter the idle state.
 *    - (`IAV driver`) Return from IOCTL callings to "test_encode".
 *    - (`test_encode`) Exit from IOCTL callings.
 *    - Now, the system enters the idle state
 *      and the image process waits for the "prepare_3a" message in the next round.
 *
 * @section faq_magic_zoom 5. Magic Zoom
 *
 * Magic Zoom is a key component in Ambarella resolution.
 * Without interpolation amplification, Magic Zoom achieves the same effect with optical zoom;
 * the AMBA DSP connects to a large resolution sensor,
 * which is larger than the encoding specifications (see the following figure).
 * @image html magic_zoom_with_dptz_1.png "Magic Zoom with DPTZ I"
 * Example:<br>
 * In OS05A10 (5M), the main buffer is 720p.
 * 4M data converts to 720 through oversampling->stitching->downscaling.
 * The field of views (FoVs) of all pictures are complete,
 * and the screen resolution is better than from the 720p sensor.<br>
 * Next, add zoom in, and perform downscaling (2X) after the sensor is used to crop in original video
 * or directly send the original video to the main buffer for encoding.
 * Because there is no interpolation amplification, good video quality is guaranteed.<br>
 * Although this feature uses DPTZ I to perform Magic Zoom,
 * users can save a high resolution stream in local by using DTPZ II (see the following figure).
 * Users can crop 720p downscaling or 480p downscaling for encoding in the main buffer.
 * @image html magic_zoom_with_dptz_2.png "Magic Zoom with DPTZ II"
 *
 * @section faq_data_dump 6. Data Dump
 *
 * When the DSP enters the preview or encode state,
 * users can dump RAW / YUV420 / YUV422 / ME0 / ME1 data for different uses:
 * - Because RAW data comes from the sensor,
 *   the dumped RAW data can be used to check if the sensor is functioning correctly.
 * - YUV420 / YUV422 / ME1 / ME0 are used for motion detection.
 *   There is only one Y (Luma) component in the ME1/ME0 data.
 *   The ME0 data size is 1/8 the width and height of the source buffer.
 *   Additionally the ME1 data size is 1/4 the width and height of the source buffer,
 *   so the total size is 1/16 of the source buffer.
 *   Therefore, ME0 is the best data for motion detection for cases with a small DRAM bandwidth.
 *
 * @section faq_two_types_of_pts 7. Two Types of PTS
 *
 * Users can obtain two different types of presentation time stamps (PTS):
 * arm_pts and dsp_pts (code in `test_stream.c`).
 * arm_pts is used for audio and video synchronization.
 * dsp_pts is used for internal reference only, to calculate each frame interval.<br>
 * Therefore, if the file `\proc\ambarella\ambarella_hwtimer` exists
 * (indicating a hardware timer is included),
 * arm_pts will be generated by the hardware;
 * or alternatively, it will be generated by the software,
 * as function <B>get_monotonic_pts</B> calls <B>do_gettimeofday</B> to obtain system time.
 *
 * @section faq_vbr_and_cbr 8. Variable Bit Rate (VBR) and Constant Bit Rate (CBR)
 *
 * The following include descriptions for the different types of constant bit rate
 * and variable bit rate modes.
 * - IAV_CBR (CBR): One of the Smart CBR modes, where bitrate is set by "--bitrate".
 *   QP minimal value is 1 and the maximal value is 51, and frame drop is not allowed.
 *   Change QP to ensure a stable bitrate.
 * - IAV_CBR_QUALITY_KEEPING (CBR-quality): One of the Smart CBR modes, where bit rate is set by "--bitrate".
 *   QP minimal value is 1, and maximal is decided by the bit rate and resolution.
 *   Change QP value and drop frame to ensure a stable bit rate, and try to keep the video quality stable.
 * - IAV_VBR (VBR): One of the Smart CBR modes, where bit rate is set by "--vbr-bitrate".
 *   QP maximal value is 51, and the minimal is decided by "--vbr-bitrate"
 *   and resolution, and the frame drop is not allowed.
 *   Changing QP to make the bit rate stay in range is set by "--vbr-bitrate".
 * - IAV_VBR_QUALITY_KEEPING (VBR-quality): One of the Smart CBR modes,
 *   where bit rate is set by "--vbr-bitrate".
 *   QP maximal value is the same as the minimal value,
 *   all decided by the maximal value of "--vbr-bitrate" and resolution; it also allows the frame drop.
 *   Change the QP value and drop frame to ensure a stable bit rate,
 *   and try to keep the video quality stable.
 * Typically, the smart CBR is used for CBR | VBR | CBR-quality | VBR-quality.
 * Users can set the QP value, decide to set the frame drop or not, and set the rate range
 * and other values to achieve the balance between the image and bit rate when the bit rate is relatively stable.
 *
 * @section faq_dump_yuv_with_without_osd 9. Dump YUV with / without overlay
 *
 * As the final stage of YUV, overlay is inserted before the encoder.
 * The captured YUV data can be stamped with or without the overlay.<br>
 * The following illustrates the flow of video data.
 * @image html  video_data_flow.png "Video Data Flow"
 * To ensure that the overlay is inserted on the YUV frame, perform the following:
 * - Set "extra_dram_buf = 3" in a lua script's canvas configuration to make a YUV image be stored
 *   in the memory cached for more than 3 frames’ time before overlay insertion;
 * @code
 * canvas = {
 *		...
 *		{
 *			type = "encode",
 *			...
 *			extra_dram_buf = 3,
 *		},
 * 		...
 * }
 * @endcode
 * - Query the address of YUV frame and the corresponding YUV PTS, and then save the two variables.
 * - Compare H.264 PTS with YUV PTS which is saved in Step 2.
 *   If the values are equal, it means the frame has been encoded with overlay.
 *   Then, read out the YUV data from the address of YUV frame corresponding to this YUV PTS.
 *   At this time, user application can ensure that the frame read out is a complete frame with overlay.
 * - If the CPU is used to read out the YUV data (like to call <B>memcpy()</B> function),
 *   the speed can be slow as it is affected by the CPU loading introduced by other user applications.
 *   If the YUV data cannot be read out within extra_dram_buf frames’ time, it will be overwritten by the DSP.
 *   Therefore, it is strongly recommended to use GDMA copy to speed up the YUV data copying.
 *   GDMA copy is not affected by the CPU loading since it is operated by GDMA hardware.
 * For the usage above, refer to the codes:<br>
 * `unit_test\private\iav_test\dsp_v6\test_stream.c`<br>
 * `unit_test\private\iav_test\dsp_v6\test_yuvcap.c`<br>
 * `unit_test\private\iav_test\dsp_v6\test_memcpy.c`<br>
 * Note the following when determining a method for not inserting overlay on the YUV frame:
 * - Because the Arm® is not given the exact time when the overlay content will be applied on the source buffer,
 *   it cannot guarantee YUV without overlay.
 * - The option, "--encode-dummy-latency" can be used to cache frames between the image digital signal processing (IDSP)
 *   and the video digital signal processing (VDSP). (overlay is added in the VDSP side.)
 *   When the cache frames option is enabled, the application can obtain the YUV data without overlay.
 * This option increases the DSP DRAM size by "YUV frame size * dummy_latency_frames".<br>
 * For example, if "test_encode --encode-dummy-latency 1",
 * the user has one frame time (33ms) to read out the YUV data before overlay applied,
 * but DSP DRAM size also increases one frame size for all source buffers, from main to the 5th buffer.
 *
 *//*!
 * @file dsp_monitor_service.h
 * @brief
 * @version 0.2
 * @date 2022-04-07
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
 * @page fs_others_dsp_monitor_service OTHER - DSP Monitor Service
 *
 * @section section_dsp_monitor_service_features 1. DSP Monitor Service Features
 *
 * Since Cooper SDK 0.5, the digital signal processor (DSP) monitor service is added to monitor
 * the DSP working state at runtime. This service must be enabled before DSP is booted up to
 * the running state. In the Ambarella SDK, this service is enabled by default in the sensor
 * initialization script (init.sh --sensor).
 * If users don't use this initialization script, they must run the "dsp_monitor_service" service
 * before booting up DSP to the running state. Else, users must integrate the calling of
 * "libdspmonitor.so" library into their own application.
 * If users don't follow the above guidelines, they may expect DSP running at abnormal state.
 * When this happens, there may be error prints showing up in the IAV driver log, and users may
 * find significant frame drop happens from the DSP side.
 *
 * So this DSP monitor service is working actively to communicate with DSP to monitor its state.
 * Once abnormal state is detected from DSP side, IAV driver would immediately get notified.
 * IAV reports this information in the dmesg log, and users may also get notified from the DSP
 * monitor service API "dsp_mon_get_dsp_state" as well. So when this happens, users may need to
 * check whether there are abnormal configurations, such as invalid clock settings for DSP or VP.
 * Users may need to adjust back these clock settings to be within the target clock settings for
 * the specific chip part number, and recover to normal after putting DSP back to preview again.
 * The dsp monitor service can also detect DSP assertion happens or not. When this happens, users
 * may have to reboot the entire system to get DSP back to the running state again.
 *
 * For CV72, there is a limitation that cavalry must be loaded before booting DSP operations.
 * In DSP Moniter Service, it will also monitor this behavior, when booting DSP operations.
 * When users try to booting DSP before loading cavalry, there will be a warning message from DSP
 * Monitor Service, but it won't block cavalry reload operations. But when users try to reload
 * cavalry after DSP is booted, DSP will fail to enter into preview state.
 *
 * @subsection dsp_monitor_service_sample_flow 1.1 DSP Monitor Service Sample Flow
 * Below is the pseudo code for how users implement the DSP monitor service into their application.
 * @code {.c}
 * static void *monitor_service(void *context)
 * {
 *   struct dsp_mon_dsp_state dsp_state;
 *   struct pollfd pool_fd = {0};
 *   char name[64];
 *   int fd = 0, rval = 0, fd_iav = 0;
 *   snprintf(name, sizeof(name), "/proc/ambarella/vdsp_sync");
 *
 *   // Init DSP monitor service library.
 *   fd_iav = open("/dev/iav", O_RDWR, 0));
 *   dsp_mon_init_lib(fd_iav);
 *   // Set up the timing to query DSP state
 *   fd = open(name, O_RDONLY, 0);
 *   pool_fd.fd = fd;
 *   pool_fd.events = POLLIN | POLLERR;
 *   while (!quit_thread) {
 *     rval = poll(&pool_fd, 1, TIMEOUT_INFINITE);
 *     poll_times++;
 *     // POLL_THRESHOLD is suggested to be in the ange of 30 ~ 240
 *     if (poll_times % POLL_THRESHOLD) {
 *        continue;
 *     }
 *     // Call the API to get DSP state
 *     dsp_mon_get_dsp_state(&dsp_state);
 *     if (dsp_state.state != DSP_MON_STATE_OK) {
 *       // DSP is in abnormal state or assertioin
 *     } else {
 *       // DSP working normally
 *       monitor_times = 0;
 *     }
 *   }
 *   // Release the DSP monitor service library.
 *   dsp_mon_deinit_lib();
 * }
 * @endcode
 * For more details, users can find the example from the dsp_monitor_service.c, which is located in
 * sdk\ambarella\app\utility\dsp_tool\dsp_monitor_service.c.
 * For the DSP monitor service library APIs, users can find them from
 * sdk\ambarella\prebuild\library\dsp_monitor\dsp_v6\include\lib_dsp_monitor.h.
 *
 */
/*!
 * @file ucode.h
 * @brief
 * @version 0.2
 * @date 2023-12-11
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
 * @page fs_others_ucode OTHER - ucode for DSP
 *
 * @section section_ucode 1. Dedicated ucode binaries for each chip part number
 *
 * Since the Cooper Software Development Kit (SDK) version 1.5.1, there will be a dedicated
 * set of ucode binaries for each chip part number.
 *
 * This design enables Ambarella to efficiently support digital signal processor (DSP)-related
 * features for different chip part numbers.
 *
 * Note the following regarding this feature:
 *  - There is no generic ucode to support different chip part numbers, as there was before.
 *  - Users are required to load the correct version of the ucode binary files for their
 *    specific chip part number.
 *  - When incorrect ucode version is loaded, there may be unknown behaviors, so this must be
 *    avoided.
 *
 * Ambarella recommends that users compile using a configuration that matches their currently
 * used chip part number. For example, if compiling the SDK with `cv5s66_ipcam_config`, the
 * CV5S66 ucode binary files are copied into the final firmware image. Users are not required
 * to manually copy the correct version of ucode binary files into the system.
 *
 * @subsection dedicate_ucode_cv5x 1.1 CV5x
 *
 * For CV5 / CV52, each chip part number possesses a unique ucode inside the Cooper SDK. That is to
 * say, inside the SDK, there are CV5S66, CV5S88, and CV5S99 ucodes for CV5; or CV52S33, CV52S66, and
 * CV52S99 ucodes for CV52.
 *
 * The different CV5 part numbers' ucode binaries (S66, S88, and S99) are stored in the following path:<br>
 *  `SDK\ambarella\drv_modules\firmware\dsp\dsp_v6\v6\cv5\<Date_Time>\generic`.
 * The different CV52 part numbers' ucode binaries (S33, S66, and S99) are stored in the following path:<br>
 *  `SDK\ambarella\drv_modules\firmware\dsp\dsp_v6\v6\cv52\<Date_Time>\generic`.
 *
 * @note
 * - CV5S99 and CV52S99 are special part numbers only for engineering samples, which will not be
 *   released or used in final customer products.
 * - <b><Date_Time></b> is used to specify the unique ucode version number, such as "231108_082514".
 *
 * Users must use the ucode version that matches exactly with the chip part number they are using.
 * For example, if CV5S88 is used in a product, the CV5S88 ucode must be used
 * rather than CV5S66 or CV5S99. If an incorrect ucode is loaded, the resulting behaviors are listed as follows:
 *  - For CV5S88, there will be a DSP hang when trying to enter preview with CV5S99 ucode.
 *  - For CV5S66, there will be a DSP hang when trying to enter preview with CV5S99 or CV5S88 ucode.
 *  - For CV52S66, there will be a DSP hang when trying to enter preview with CV52S99 ucode.
 *  - For CV52S33, there will be a DSP hang when trying to enter preview with CV52S99 or CV52S66 ucode.
 * For other incorrect cases, the behavior is unknown, and this must be avoided.
 *
 * @subsection dedicate_ucode_cv72 1.2 CV72
 *
 * For CV72, each chip part number possesses a unique ucode inside the Cooper SDK. That is to
 * say, inside the SDK, there are CV72S33, CV72S66, CV72S66IQ, CV72S88, CV72S88IQ, and CV72S99 ucodes for CV72.
 *
 * The different CV72 part numbers' ucode binaries (S33, S66, S66IQ, S88, S88IQ, and S99)
 * are stored in the following path:<br>
 *  `SDK\ambarella\drv_modules\firmware\dsp\dsp_v6\v6\cv72\<Date_Time>\generic`.
 *
 * @note
 * - CV72S99 is a special part number only for engineering samples, which will not be
 *   released or used in final customer products.
 * - <b><Date_Time></b> is used to specify the unique ucode version number, such as "231108_082514".
 *
 * Users must use the ucode version that matches exactly with the chip part number they are using.
 * For example, if CV72S88IQ is used in a product, the CV72S88IQ ucode must be used
 * rather than CV72S33, CV72S66, CV72S66IQ, CV72S88, CV72S88IQ, or CV72S99.
 * If an incorrect ucode is loaded, the resulting behaviors are listed as follows:
 *  - For CV72S88IQ, there will be a DSP hang when trying to enter preview with CV72S99 ucode.
 *  - For CV72S88, there will be a DSP hang when trying to enter preview with CV72S99 or CV72S88IQ ucode.
 *  - For CV72S66IQ, there will be a DSP hang when trying to enter preview with CV72S99, CV72S88IQ or CV72S88 ucode.
 *  - For CV72S66, there will be a DSP hang when trying to enter preview with CV72S99, CV72S88IQ, CV72S88, CV72S66IQ ucode.
 *  - For CV72S33, there will be a DSP hang when trying to enter preview with CV72S99, CV72S88IQ, CV72S88, CV72S66IQ or CV72S66 ucode.
 *
 * For other incorrect cases, the behavior is unknown, and this must be avoided.
 */
