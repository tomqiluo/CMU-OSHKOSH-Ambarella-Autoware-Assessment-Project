/*!
 * @file doc_video_main.h
 * @brief This is a dummy header file for doxygen
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
 * @defgroup te_parm Test_encode Parameters
 * @brief test_encode parameters
 */

/*!
 * @defgroup tefm_parm Test_efm Parameters
 * @brief test_efm parameters
 */

/*!
 * @defgroup tdptz_parm Test_dptz Parameters
 * @brief test_dptz parameters
 */

/*!
 * @defgroup tyuvcap_parm Test_yuvcap Parameters
 * @brief test_yuvcap parameters.
 *
 * This program captures the YUV / ME1 buffer in YUV420 format for the encode buffer, and saves it as IYUV, YV12, or NV12.
 * <br>  IYUV format (U and V are planar buffers) is as follows:
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                UUUUUUUUUUUUUU
 * <br>                UUUUUUUUUUUUUU
 * <br>                VVVVVVVVVVVVVV
 * <br>                VVVVVVVVVVVVVV
 * <br>  YV12 format (U and V are planar buffers) is as follows:
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                VVVVVVVVVVVVVV
 * <br>                VVVVVVVVVVVVVV
 * <br>                UUUUUUUUUUUUUU
 * <br>                UUUUUUUUUUUUUU
 * <br>  NV12 format (U and V are interleaved buffers) is as follows:
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                UVUVUVUVUVUVUV
 * <br>                UVUVUVUVUVUVUV
 * <br>                UVUVUVUVUVUVUV
 * <br>                UVUVUVUVUVUVUV
 *
 * This program captures the YUV buffer in YUV422 format for the preview buffer, and saves it as YU16 or YV16.
 * <br>   YU16 format (U and V are planar buffers) is shown below:
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                UUUUUUUUUUUUUUUUUUUUUUUUUUUU
 * <br>                UUUUUUUUUUUUUUUUUUUUUUUUUUUU
 * <br>                VVVVVVVVVVVVVVVVVVVVVVVVVVVV
 * <br>                VVVVVVVVVVVVVVVVVVVVVVVVVVVV
 * <br>  YV16 format (U and V are planar buffers) is shown below:
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                VVVVVVVVVVVVVVVVVVVVVVVVVVVV
 * <br>                VVVVVVVVVVVVVVVVVVVVVVVVVVVV
 * <br>                UUUUUUUUUUUUUUUUUUUUUUUUUUUU
 * <br>                UUUUUUUUUUUUUUUUUUUUUUUUUUUU
 * <br>  NV16 format (U and V are interleaved buffers) is shown below:
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                YYYYYYYYYYYYYYYYYYYYYYYYYYYY
 * <br>                UVUVUVUVUVUVUVUVUVUVUVUVUVUV
 * <br>                UVUVUVUVUVUVUVUVUVUVUVUVUVUV
 * <br>                UVUVUVUVUVUVUVUVUVUVUVUVUVUV
 * <br>                UVUVUVUVUVUVUVUVUVUVUVUVUVUV
 *
 * To get one single preview frame of IYUV format:
 * @code
 * > test_yuvcap -b 1 -Y -f 1.yuv -F 0 -r 1 --tcp
 * @endcode
 *
 * To get 30 frames of YUV data as a .yuv file of YV12 format:
 * @code
 * > test_yuvcap -b 1 -Y -f 1.yuv -F 1 -r 30 --tcp
 * @endcode
 *
 * To get continuous frames of YUV data as a .yuv file of YV12 format with a delay of one frame-capture YUV:
 * @code
 * > test_yuvcap -b 1 -Y -f 1.yuv -F 1 -r 0 --tcp -d
 * @endcode
 *
 * To get PBG data from the main buffer, enter the following:
 * @code
 * > test_yuvcap -p -Y -f pbg.yuv --tcp
 * @endcode
 *
 * To get 30 frames of me1 data as a .yuv file:
 * @code
 * > test_yuvcap -b 0 -m -b 1 -m -f 2.me1 -r 30 --tcp
 * @endcode
 *
 * To get continuous frames of me1 data as a .yuv file:
 * @code
 * > test_yuvcap -b 0 -m -b 1 -m -f 2.me1 -r 0 --tcp
 * @endcode
 *
 * To get raw data from RGB sensor input mounted on vinc0:
 * @code
 * > test_yuvcap -i 0 -R -f cap_raw --tcp
 * @endcode
 *
 * To get 30 frames of yuv data as .yuv file of NV16 format:
 * @code
 * > test_yuvcap -b 2 -Y -f 1.yuv -F 5 -r 30 --tcp
 * @endcode
 *
 * To get five frames of YUV data from four pyramids in channel0 as a .yuv file of NV12 format:
 * @code
 * > test_yuvcap -c 0 -P 0~3 -f cap_pyramid -r 5 --tcp
 * @endcode
 */

/*!
 * @defgroup tstream_parm Test_stream Parameters
 * @brief test_stream parameters
 */

/*!
 * @defgroup tvincap_parm Test_vin_cap Parameters
 * @brief test_vin_cap parameters
 */

/*!
 * @defgroup tfsync_parm Test_frame_sync Parameters
 * @brief test_frame_sync parameters
 */

/*!
 * @defgroup tfb_parm Test_fb Parameters
 * @brief test_fb parameters
 *
 * 1. The precondition is provided below:
 * <br>The frame buffer unit test tool is selected to compile.
 * <br>Users can select the unit test tool from menuconfig:
 * @code
 * build$ make menuconfig
 *   -> Ambarella Unit Test Configuration
 *     -> Ambarella Public Linux Unit test configs
 *       -> Build Ambarella Public Linux Misc unit tests
 * @endcode
 *
 * 2. Install the frame buffer module manually when the default values cannot satisfy the requirement.
 *
 * There are two frame buffers: fb0 and fb1. The fb0 buffer is a bind to digital video output (VOUT) and fb1 is a bind to
 * composite video with blanking and sync (CVBS) / high-definition multimedia interface (HDMI®). The `Ambarella_fb` module
 * is automatically installed; the default value for video
 * size is @b 480p and the color format is <b>16 bits per pixel</b>. Users should reinstall the module if the
 * default values do not meet the application requirements:
 * @code
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3  // For CV5 or CV52
 * (Or board # init.sh --na; modprobe imx274_mipi vinc_id=8)      // For CV72
 * board # rmmod ambarella_fb
 * board # modprobe ambarella_fb resolution=1280x720 mode=clut8bpp
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua\       // For CV5 or CV52
 *                     --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                     --os 1280x720 --oo 0,0 --vs 1280x720 --vo 0,0
 * (Or board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua\  // For CV72
 *                     --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua\
 *                     --os 1280x720 --oo 0,0 --vs 1280x720 --vo 0,0)
 * board # test_fb -c 255,0,0,128 -w 1280 -h 720 -b 1
 * @endcode
 */

/*!
 * @defgroup tldc_parm Test_ldc Parameters
 * @brief test_ldc parameters
 */

/*!
 * @defgroup tmc_parm Test_multi_chan Parameters
 * @brief test_multi_chan parameters
 */

/*!
 * @defgroup tdec_parm Test_decode Parameters
 * @brief test_decode parameters
 */

/*!
 * @defgroup tcs_parm Test_custom_sei Parameters
 * @brief test_custom_sei parameters
 */

/*!
 * @defgroup ties_parm Test_idsp_enc_sync Parameters
 * @brief test_idsp_enc_sync parameters
 */

/*!
 * @defgroup tpmf_parm Test_pyramid_mf Parameters
 * @brief test_pyramid_mf parameters
 */

/*!
 * @defgroup tmf_parm Test_manual_feed Parameters
 * @brief test_manual_feed parameters
 */

/*!
 * @defgroup test_poll_parm Test_poll Parameters
 * @brief test_poll parameters
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
 * <tr><td> 20211015              <td> First release for Feature Sets document
 * <tr><td> 20211221              <td> Added Section @ref section_source_buffer_example "Source buffer Examples"
 * <tr><td> 20211222              <td> Added webpage @ref fs_basic_hdr
 * <tr><td> 20220110              <td> Added webpage @ref fs_adv_arb_img_scaler
 * <tr><td> 20220111              <td> Added Section @ref section_vout_examples "Video Output Examples"
 * <tr><td> 20220113              <td> Added Section @ref section_raw_example "Raw Examples"
 * <tr><td> 20220119              <td> Added Section @ref example_pyramid_external_mem "Canvas External Memory" and @ref example_pyramid_external_mem "Pyramid External Memory"
 * <tr><td> 20220126              <td> Updated Section @ref section_canvas_example "Canvas Examples" and @ref efr_exp "EFR Examples"
 * <tr><td> 20220221              <td> Added Section @ref subsection_encoder_dual_cores "Encoder Dual Cores"
 * <tr><td> 20220301              <td> Added Section @ref data_dump_mv "MV Dump"
 * <tr><td> 20220315              <td> Updated Section @ref efr_exp "EFR Examples"
 * <tr><td> 20220328              <td> Updated Section @ref section_multiple_sltile_enc "Multiple Tile Encoding"
 * <tr><td> 20220331              <td> Updated Section @ref efr_exp "EFR Examples"
 * <tr><td> 20220406              <td> Added webpage @ref fs_basic_gop
 * <tr><td> 20220418              <td> Added webpage @ref fs_adv_enc_mode
 * <tr><td rowspan="11"> 20220420 <td> 1. Added Section @ref section_buffer_capability "Buffer Capability"
 * <tr>                           <td> 2. Added Section @ref section_img_scller_examples "Arbitrary Image Scaler Example"
 * <tr>                           <td> 3. Updated webpage @ref fs_adv_lua
 * <tr>                           <td> 4. Updated webpage @ref fs_basic_codec
 * <tr>                           <td> 5. Updated Section @ref section_raw_features "Raw Features"
 * <tr>                           <td> 6. Added Section @ref example_stream_monochrome "Monochrome Stream"
 * <tr>                           <td> 7. Updated Section @ref vin_vout_precise_sync "VIN-VOUT Precise Synchronization"
 * <tr>                           <td> 8. Added Section @ref vout_mixer "Video Output Mixer"
 * <tr>                           <td> 9. Added Section @ref vout_rotate "Video Output: VOUT Rotate"
 * <tr>                           <td> 10. Added Section @ref vout_flip "Video Output: VOUT Flip"
 * <tr>                           <td> 11. Updated Section @ref section_vout_examples "Video Output Examples"
 * <tr><td> 20220424              <td> Added webpage @ref fs_basic_channel
 * <tr><td rowspan="2"> 20220509  <td> 1. Added Section @ref codec_pskip "Force P-skip"
 * <tr>                           <td> 2. Added Section @ref codec_skip_mode "Skip Frame Strategy and Mode"
 * <tr><td> 20220513              <td> Added Section @ref example_codec_decode_by_ffmpeg "Decode by FFmpeg"
 * <tr><td> 20220610              <td> Added webpage @ref fs_others_debug
 * <tr><td> 20220616              <td> Updated Section @ref codec_fdrop "Force Frame Drop" and @ref codec_roi_enc "ROI Encoding Tools"
 * <tr><td> 20220627              <td> Added example @ref example_vin_VGA480_FPS "VIN 480 fps"
 * <tr><td rowspan="3"> 20220706  <td> 1. Added webpage @ref fs_adv_iav_poll
 * <tr>                           <td> 2. Updated Section @ref enc_latency "Encode Latency"
 * <tr>                           <td> 3. Updated Section @ref section_buffer_capability "Buffer Capability"
 * <tr><td rowspan="2"> 20220711  <td> 1. Updated Section @ref efm_efm "1. Encode from Memory"
 * <tr>                           <td> 2. Added Section @ref example_codec_long_start_code "Set HEVC Long Start Code"
 * <tr><td> 20220713              <td> Added webpage @ref fs_basic_blur
 * <tr><td rowspan="3"> 20220719  <td> 1. Updated webpage @ref fs_adv_efm
 * <tr>                           <td> 2. Updated Section @ref section_stream_example "Stream Examples"
 * <tr>                           <td> 3. Added Section @ref other_disp_cfg "Others:  Display Current Configuration"
 * <tr><td> 20220805              <td> Added Section @ref hevc_scalelist "HEVC Scalelist"
 * <tr><td> 20220829              <td> Move page @ref page_sys_dram_stat into "System" project
 * <tr><td rowspan="2"> 20221012  <td> 1. Added Section @ref channel_reuse_src_chan "IDSP Virtual Channel Frame-Synchronized"
 * <tr>                           <td> 2. Added Section @ref data_dump_qp_hist "QP Histogram Dump for AVC and HEVC"
 * <tr><td> 20221021              <td> Added Section @ref fps_suggest "3. Framerate Examples"
 * <tr><td rowspan="2"> 20221024  <td> 1. Added webpage @ref fs_adv_dewarp
 * <tr>                           <td> 2. Added webpage @ref fs_basic_playback
 * <tr><td rowspan="2"> 20221025  <td> 1. Added webpage @ref fs_adv_customized_features
 * <tr>                           <td> 2. Added Section @ref data_dump_raw_dio "Data Dumping: Capture Raw Data via Direct IO"
 * <tr><td rowspan="2"> 20221116  <td> 1. Added Section @ref vout_no_reset "1.8 Video Output: No VOUT Reset during Mode Switch",
and added Example @ref example_vout_no_reset "Example 8: VOUT No Reset for Mode Switch"
 * <tr>                           <td> 2. Added product plan @ref multi_vin_design_quad_independent_sensors "Quad Independent Sensors", example @ref multi_vin_design_quad_sensors_with_imx274 "Quad Sensors with imx274"
 * <tr><td rowspan="3"> 20221213  <td> 1. Added section @ref section_smart_ldc "Smart LDC"
 * <tr>                           <td> 2. Added Example @ref example_codec_fsync13 "Add Overlay Insertion" and @ref example_codec_fsync14 "Add Blur Insertion"
 * <tr>                           <td> 3. Added section @ref pb_lua_vin_config "2.2 Lua File Configuration for Virtual VIN mode"
 * <tr><td> 20230110              <td> Added Section @ref custom_virtual_vin_mode "3. Custom virtual VIN mode"
 * <tr><td> 20230309              <td> Added some examples @ref section_sc_pm_examples "2. Privacy Mask Examples"
 * <tr><td> 20230419              <td> Update the document to include CV72 platform
 * <tr><td> 20230602              <td> Added Section @ref video_info_audit  "3. Video Pipeline Info Audit"
 * <tr><td> 20230616              <td> Added CV3 EFR and EFM examples @ref efr_exp "4. EFR Examples" and @ref example_efm11
 * <tr><td> 20230620              <td> Update EFR examples @ref example_efr6
 * <tr><td> 20230628              <td> Update EFR examples @ref example_efr7 and @ref example_efr11
 * <tr><td> 20230713              <td> Added Section @ref cam_seamless_switch and added example @ref example_broken_vin
 * <tr><td> 20230817              <td> Update Section @ref section_encode_mode "1. Encode Mode"
 * <tr><td> 20230830              <td> Added Section @ref enc_clk_aud
 * <tr><td rowspan="2"> 20230914  <td> 1. Updated Section @ref example_vout_no_reset "VOUT No Reset for Mode Switch"
 * <tr>                           <td> 2. Added Example @ref example_pm9 "Fill Warp Frame Border Artifact"
 * <tr><td rowspan="7"> 20231026  <td> 1. Added Section @ref codec_qp_offset "19. Chroma QP Offset"
 * <tr>                           <td> 2. Updated Section @ref frame_drop_aud "3.5 IDSP and Encode Frame Drop Audit"
 * <tr>                           <td> 3. Added Section @ref vin_repeat_frame "1.9 VIN Repeat Frame"
 * <tr>                           <td> 4. Added Section @ref section_pjpeg_tile_size "1.14 Encode PJPEG tile dram size"
 * <tr>                           <td> 5. Updated Section @ref H26X_scalelist "16. H26x Scalelist"
 * <tr>                           <td> 6. Updated Section @ref codec_skip_mode "9. Skip Frame Strategy and Mode"
 * <tr>                           <td> 7. Updated Section "Smart LDC".
 * <tr><td> 20231030              <td> Added Section @ref mode_vin_only "1.5 Mode 127: VIN Only Mode"
 * <tr><td> 20231108              <td> Added commands of mode 1 for CV72. @ref fs_adv_dewarp
 * <tr><td> 20231211              <td> Added webpage @ref fs_others_ucode
 * <tr><td> 20231225              <td> Update @ref section_fps_features "1. Frame Rate"
 * <tr><td rowspan="5"> 20231229  <td> 1. Updated Section @ref example_blur_on_stream for color blur
 * <tr>                           <td> 2. Updated Section @ref video_info_audit  "3. Video Pipeline Info Audit"
 * <tr>                           <td> 3. Added Section @ref dual_vin_slice "1.12 Dual VIN Slicing"
 * <tr>                           <td> 4. Added Section @ref vout_osd_sync "1.8 Video Output: VOUT OSD Frame Sync"
 * <tr>                           <td> 5. Added Section @ref subsection_custom_sei "1.16 Insert User-Customized Data into Bitstream"
 * <tr><td rowspan="5"> 20240105  <td> 1. Added page @ref fs_basic_duplex and @ref example_pb_npb3
 * <tr>                           <td> 2. Added Section @ref example_stream_abs_fps and @ref example_canvas_zero_fps
 * <tr>                           <td> 3. Added Section @ref example_aaa_overlay
 * <tr>                           <td> 4. Added RAW fps examples @ref example_raw_fps and @ref example_raw_fps_scale_roi_vin
 * <tr>                           <td> 5. Added codec CU BIAS options example @ref example_codec_cu_size_control1, @ref example_codec_cu_size_control2 and @ref example_codec_cu_size_control3
 * <tr><td rowspan="9"> 20240109  <td> 1. Added Section @ref example_video_output_via_dsi
 * <tr>                           <td> 2. Added Section @ref example_video_output_via_csi
 * <tr>                           <td> 3. Added Section @ref example_dual_vout
 * <tr>                           <td> 4. Added Section @ref example_vout_switch_multi_chan
 * <tr>                           <td> 5. Added Section @ref example_vout_underflow_prevention
 * <tr>                           <td> 6. Added page @ref fs_adv_multi_pass
 * <tr>                           <td> 7. Added Section @ref sys_mg_sw_api_diff_multi_pass
 * <tr>                           <td> 8. Added webpage @ref fs_adv_bypass_idsp_for_yuv_input
 * <tr>                           <td> 9. Added examples @ref fs_warp_input_mode, @ref fs_pers_mat
 * <tr><td rowspan="4"> 20240125  <td> 1. Added page @ref iq_lite_nn
 * <tr>                           <td> 2. Added Section @ref data_dump_idsp_motion "5. Dump and Display IDSP Motion Data with Encode Mode 5/9"
 * <tr>                           <td> 3. Added VIN fps example @ref exampe_update_vin_fps
 * <tr>                           <td> 4. Added Section @ref codec_qframe "20. Q Frame Mechanism"
 * </table>
 *
 *
 * ---
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
