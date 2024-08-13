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
  [ "Video", "index.html", [
    [ "BASIC - Video Input", "d2/d61/fs_basic_vin.html", [
      [ "1. Video Input Features", "d2/d61/fs_basic_vin.html#section_vsrc_features", [
        [ "1.1 Resolution", "d2/d61/fs_basic_vin.html#vsrc_resolution", null ],
        [ "1.2 Frame Rate", "d2/d61/fs_basic_vin.html#vsrc_frame_rate", null ],
        [ "1.3 Mirror / Flip", "d2/d61/fs_basic_vin.html#vsrc_mirror_filp", null ],
        [ "1.4 High Dynamic Range Mode", "d2/d61/fs_basic_vin.html#vsrc_hdr", null ],
        [ "1.5 YUV Input", "d2/d61/fs_basic_vin.html#vsrc_yuv", null ],
        [ "1.6 Multi-VIN", "d2/d61/fs_basic_vin.html#vsrc_multi_vin", null ],
        [ "1.7 VIN-VOUT Precise Synchronization", "d2/d61/fs_basic_vin.html#vin_vout_precise_sync", null ],
        [ "1.8 Camera Seamless Switch (CSS)", "d2/d61/fs_basic_vin.html#cam_seamless_switch", null ],
        [ "1.9 VIN repeat frame", "d2/d61/fs_basic_vin.html#vin_repeat_frame", null ],
        [ "1.10 Scale VIN", "d2/d61/fs_basic_vin.html#scale_VIN", null ],
        [ "1.11 ROI VIN", "d2/d61/fs_basic_vin.html#Roi_VIN", null ],
        [ "1.12 Dual VIN Slicing", "d2/d61/fs_basic_vin.html#dual_vin_slice", null ]
      ] ],
      [ "2. Video Input Configuration", "d2/d61/fs_basic_vin.html#lua_vsrc_configuration", null ],
      [ "3. Video Input Examples", "d2/d61/fs_basic_vin.html#section_vsrc_example", [
        [ "Example 1: Resolution Control", "d2/d61/fs_basic_vin.html#example_vsrc_resolution", null ],
        [ "Example 2: Frame Rate Control", "d2/d61/fs_basic_vin.html#example_vsrc_frame_rate", null ],
        [ "Example 3: Mirror / Filp", "d2/d61/fs_basic_vin.html#example_vsrc_mirror_filp", null ],
        [ "Example 4: YUV Input using LT6911", "d2/d61/fs_basic_vin.html#example_vsrc_yuv", null ],
        [ "Example 5: VIN-VOUT Precise Sync", "d2/d61/fs_basic_vin.html#example_vin_vout_precise_sync", null ],
        [ "Example 6: VIN 480 fps", "d2/d61/fs_basic_vin.html#example_vin_VGA480_FPS", null ],
        [ "Example 7: Single 8K VIN Case", "d2/d61/fs_basic_vin.html#example_vin_8k", null ],
        [ "Example 8: Encode from RGB RAW: Input from RGB (RAW) File to VIN with Custom Virtual VIN Mode", "d2/d61/fs_basic_vin.html#example_virtual_vin", null ],
        [ "Example 9: Enter Preview with Broken VIN", "d2/d61/fs_basic_vin.html#example_broken_vin", null ],
        [ "Example 10: VIN repeat frame", "d2/d61/fs_basic_vin.html#example_vin_repeat_frm", null ],
        [ "Example 11: Scale VIN", "d2/d61/fs_basic_vin.html#example_scale_VIN", null ],
        [ "Example 12: Roi VIN", "d2/d61/fs_basic_vin.html#example_Roi_VIN", null ],
        [ "Example 13: Scale VIN with roi VIN", "d2/d61/fs_basic_vin.html#example_scale_vin_with_roi_vin", null ]
      ] ]
    ] ],
    [ "BASIC - Video Ouput", "db/d36/fs_basic_vout.html", [
      [ "1. Video Output Features", "db/d36/fs_basic_vout.html#section_vout_features", [
        [ "1.1 Video Output Mixer", "db/d36/fs_basic_vout.html#vout_mixer", null ],
        [ "1.2 Video Output: Default Image", "db/d36/fs_basic_vout.html#vout_default_image", null ],
        [ "1.3 Video Output: VOUT Rotate", "db/d36/fs_basic_vout.html#vout_rotate", null ],
        [ "1.4 Video Output: VOUT Flip", "db/d36/fs_basic_vout.html#vout_flip", null ],
        [ "1.5 Video Output: No VOUT for Preview", "db/d36/fs_basic_vout.html#no_vout_for_preview", null ],
        [ "1.6 Video Output: HDMI VOUT Format", "db/d36/fs_basic_vout.html#hdmi_vout_format", null ],
        [ "1.7 Video Output: VOUT No Reset During Mode Switch", "db/d36/fs_basic_vout.html#vout_no_reset", null ],
        [ "1.8 Video Output: VOUT OSD Frame Sync", "db/d36/fs_basic_vout.html#vout_osd_sync", null ]
      ] ],
      [ "2. Video Output Devices", "db/d36/fs_basic_vout.html#section_vout_devices", [
        [ "2.1 Video Output with Multi-Interface", "db/d36/fs_basic_vout.html#vout_multi_interface", null ],
        [ "2.2 Video Output: Supported VOUT Interfaces", "db/d36/fs_basic_vout.html#vout_support_list", null ]
      ] ],
      [ "3. Video Output Examples", "db/d36/fs_basic_vout.html#section_vout_examples", [
        [ "Example 1: Video Output via HDMI", "db/d36/fs_basic_vout.html#example_hdmi_output", null ],
        [ "Example 2: Video Output via CVBS", "db/d36/fs_basic_vout.html#example_cvbs_output", null ],
        [ "Example 3: HDMI Output Size Change on the Fly", "db/d36/fs_basic_vout.html#example_vout_size", null ],
        [ "Example 4: VOUT Default Image", "db/d36/fs_basic_vout.html#example_vout_default_image", null ],
        [ "Example 5: VOUT Rotate", "db/d36/fs_basic_vout.html#example_vout_rotate", null ],
        [ "Example 6: VOUT Flip", "db/d36/fs_basic_vout.html#example_vout_flip", null ],
        [ "Example 7: HDMI VOUT Format", "db/d36/fs_basic_vout.html#example_hdmi_vout_format", null ],
        [ "Example 8: VOUT No Reset for Mode Switch", "db/d36/fs_basic_vout.html#example_vout_no_reset", null ],
        [ "Example 9: VOUT OSD Sync", "db/d36/fs_basic_vout.html#example_vout_osd_sync", null ],
        [ "Example 10: Video Output via DSI", "db/d36/fs_basic_vout.html#example_video_output_via_dsi", null ],
        [ "Example 11: Video Output via CSI", "db/d36/fs_basic_vout.html#example_video_output_via_csi", null ],
        [ "Example 12: Dual Vout", "db/d36/fs_basic_vout.html#example_dual_vout", null ],
        [ "Example 13: VOUT Switch Multi-Channel on the Fly", "db/d36/fs_basic_vout.html#example_vout_switch_multi_chan", null ],
        [ "Example 14: VOUT Underflow Prevention", "db/d36/fs_basic_vout.html#example_vout_underflow_prevention", null ]
      ] ]
    ] ],
    [ "BASIC - Raw", "d8/dca/fs_basic_raw.html", [
      [ "1. Raw Features", "d8/dca/fs_basic_raw.html#section_raw_features", [
        [ "1.1 Raw Size", "d8/dca/fs_basic_raw.html#VIN_raw_size", null ],
        [ "1.2 Raw Buffer Manual Feed", "d8/dca/fs_basic_raw.html#raw_buffer_manunal_feed", null ],
        [ "1.3 Raw slice", "d8/dca/fs_basic_raw.html#raw_slice_capture", null ]
      ] ],
      [ "2. Raw Configuration", "d8/dca/fs_basic_raw.html#lua_raw_configuration", null ],
      [ "3. Raw Examples", "d8/dca/fs_basic_raw.html#section_raw_example", null ]
    ] ],
    [ "BASIC - Channel", "da/de9/fs_basic_channel.html", [
      [ "1. Channel and IDSP Pipeline", "da/de9/fs_basic_channel.html#channel_features", [
        [ "1.1 Channel IDSP Rotation / Flip", "da/de9/fs_basic_channel.html#channel_rotation", null ],
        [ "1.2 IDSP Dual Cores", "da/de9/fs_basic_channel.html#channel_idso_dual_cores", null ],
        [ "1.3 MCTF Compression", "da/de9/fs_basic_channel.html#channel_mctf_compression", null ],
        [ "1.4 IDSP Virtual Channel Frame-Synchronized", "da/de9/fs_basic_channel.html#channel_reuse_src_chan", null ]
      ] ],
      [ "2. Channel Examples", "da/de9/fs_basic_channel.html#section_channel_example", [
        [ "Example 1: Channel Rotation", "da/de9/fs_basic_channel.html#example_channel_rotate", null ],
        [ "Example 2: Channel IDSP Flip", "da/de9/fs_basic_channel.html#example_channel_flip", null ],
        [ "Example 3: IDSP Dual Cores for CV5x", "da/de9/fs_basic_channel.html#example_channel_idsp_cores", null ],
        [ "Example 4: Virtual Channel Duplicated 3A Configuration of Master Channel.", "da/de9/fs_basic_channel.html#example_channel_vir_dup", null ]
      ] ]
    ] ],
    [ "BASIC - Source Buffer", "d0/ded/fs_basic_source_buffer.html", [
      [ "1. Source Buffer Features", "d0/ded/fs_basic_source_buffer.html#source_buffer_features", [
        [ "1.1 Main Buffer: Digital Pan / Tilt / Zoom (DPTZ)", "d0/ded/fs_basic_source_buffer.html#main_buffer_dptz", null ],
        [ "1.2 Sub-Buffer: Digital Pan / Tilt / Zoom", "d0/ded/fs_basic_source_buffer.html#sub_buffer_dptz", null ],
        [ "1.3 Buffer Type", "d0/ded/fs_basic_source_buffer.html#section_buffer_type", null ],
        [ "1.4 Buffer Capability", "d0/ded/fs_basic_source_buffer.html#section_buffer_capability", [
          [ "1.4.1 Main Source Buffer", "d0/ded/fs_basic_source_buffer.html#main_source_buffer", null ],
          [ "1.4.2 Second Source Buffer", "d0/ded/fs_basic_source_buffer.html#second_source_buffer", null ],
          [ "1.4.3 Third Source Buffer", "d0/ded/fs_basic_source_buffer.html#third_source_buffer", null ],
          [ "1.4.4 Fourth Source Buffer", "d0/ded/fs_basic_source_buffer.html#fourth_source_buffer", null ],
          [ "1.4.5 Fifth Source Buffer", "d0/ded/fs_basic_source_buffer.html#fifth_source_buffer", null ],
          [ "1.4.6 Sixth Source Buffer", "d0/ded/fs_basic_source_buffer.html#sixth_source_buffer", null ]
        ] ],
        [ "1.5 Maximum Buffer Resolution", "d0/ded/fs_basic_source_buffer.html#section_buffer_resolution", [
          [ "1.5.1 Buffer Resolution in 4K Case", "d0/ded/fs_basic_source_buffer.html#buffer_resolution_4k", null ]
        ] ]
      ] ],
      [ "2. Source Buffer Configuration", "d0/ded/fs_basic_source_buffer.html#lua_source_buffer_configuration", null ],
      [ "3. Source Buffer Examples", "d0/ded/fs_basic_source_buffer.html#section_source_buffer_example", [
        [ "Example 1: Preview from Third Buffer with HDMI 480i", "d0/ded/fs_basic_source_buffer.html#example_source_buffer_preview", null ],
        [ "Example 2: Encode from Main Buffer with Resolution 1080p", "d0/ded/fs_basic_source_buffer.html#example_main_encode", null ],
        [ "Example 3: Digital Pan / Tilt / Zoom", "d0/ded/fs_basic_source_buffer.html#example_dptz", null ],
        [ "Example 4: Configure Buffer Type and Resolution", "d0/ded/fs_basic_source_buffer.html#example_buffer_type_resolution", null ],
        [ "Example 5: Source Buffer Aspect Ratio", "d0/ded/fs_basic_source_buffer.html#example_aspect_ratio", null ]
      ] ]
    ] ],
    [ "BASIC - Pyramid", "db/de4/fs_basic_pyramid.html", [
      [ "1. Pyramid Features", "db/de4/fs_basic_pyramid.html#section_pyramid_features", [
        [ "1.1 Pyramid Input Buffer", "db/de4/fs_basic_pyramid.html#pyramid_input_buffer", null ],
        [ "1.2 Pyramid Downsampling Rate", "db/de4/fs_basic_pyramid.html#pyramid_downsampling", null ],
        [ "1.3 Crop from Pyramid", "db/de4/fs_basic_pyramid.html#pyramid_crop", null ],
        [ "1.4 Pyramid Feed Mode", "db/de4/fs_basic_pyramid.html#pyramid_feed_mode", null ],
        [ "1.5 Arbitrary Pyramid Size", "db/de4/fs_basic_pyramid.html#pyramid_arbitrary_scale", null ]
      ] ],
      [ "2. Pyramid Configuration", "db/de4/fs_basic_pyramid.html#lua_pyramid_configuration", null ],
      [ "3. Pyramid Examples", "db/de4/fs_basic_pyramid.html#section_pryamid_example", [
        [ "Example 1: Pyramid Data Capture", "db/de4/fs_basic_pyramid.html#example_pyramid_data_capture", null ],
        [ "Example 2: Pyramid Manual Feed", "db/de4/fs_basic_pyramid.html#example_pyramid_manual_feed", null ],
        [ "Example 3: Pyramid Arbitrary Scale", "db/de4/fs_basic_pyramid.html#example_pyramid_arbitrary_scale", null ],
        [ "Example 4: Change Pyramid Rescale Size and Layer Map Dynamically.", "db/de4/fs_basic_pyramid.html#example_change_pyramid_configurations", null ],
        [ "Example 5: Pyramid External Memory", "db/de4/fs_basic_pyramid.html#example_pyramid_external_mem", null ]
      ] ]
    ] ],
    [ "BASIC - Canvas", "d6/d71/fs_basic_canvas.html", [
      [ "1. Canvas Features", "d6/d71/fs_basic_canvas.html#canvas_manual_feed", [
        [ "1.1 Flexible Canvas Layout", "d6/d71/fs_basic_canvas.html#canvas_layout", null ],
        [ "1.2 Canvas Feed Mode", "d6/d71/fs_basic_canvas.html#canvas_feed_mode", null ]
      ] ],
      [ "2. Canvas Configuration", "d6/d71/fs_basic_canvas.html#canvas_configuration", null ],
      [ "3. Canvas Examples", "d6/d71/fs_basic_canvas.html#section_canvas_example", [
        [ "Example 1: Manual Feed Main Canvas", "d6/d71/fs_basic_canvas.html#example_manual_feed_main_buffer", null ],
        [ "Example 2: Manual Feed Second Canvas", "d6/d71/fs_basic_canvas.html#example_manual_feed_second_buffer", null ],
        [ "Example 3: Update Canvas Framerate at Runtime", "d6/d71/fs_basic_canvas.html#example_runtime_update_canvas_fps", null ],
        [ "Example 4: Canvas External Memory", "d6/d71/fs_basic_canvas.html#example_canvas_external_mem", null ],
        [ "Example 5: Canvas Extra Padding Enable", "d6/d71/fs_basic_canvas.html#example_canvas_extra_padding", null ],
        [ "Example 6: Canvas YUV Disable", "d6/d71/fs_basic_canvas.html#example_canvas_yuv_disable", null ]
      ] ]
    ] ],
    [ "BASIC - Stream", "d5/d7d/fs_basic_stream.html", [
      [ "1. Stream Features", "d5/d7d/fs_basic_stream.html#section_stream_features", [
        [ "1.1 Stream Input – from Single Canvas", "d5/d7d/fs_basic_stream.html#section_stream_input", null ],
        [ "1.2 Stream Input – From Multi-Canvas", "d5/d7d/fs_basic_stream.html#section_stream_multi_input", null ],
        [ "1.3 Frame Rate", "d5/d7d/fs_basic_stream.html#section_frame_rate", null ],
        [ "1.4 Bit Rate", "d5/d7d/fs_basic_stream.html#section_bit_rate", null ],
        [ "1.5 Maximum GOP M", "d5/d7d/fs_basic_stream.html#section_maximum_gop_m", null ],
        [ "1.6 GOP N", "d5/d7d/fs_basic_stream.html#section_gop_n", null ],
        [ "1.7 Encode Duration", "d5/d7d/fs_basic_stream.html#section_encode_duration", null ],
        [ "1.8 Encode Frame Drop", "d5/d7d/fs_basic_stream.html#section_encode_frame_drop", null ],
        [ "1.9 Encode Frame Trigger", "d5/d7d/fs_basic_stream.html#section_encode_frame_trigger", null ],
        [ "1.10 Canvas and Stream Sync", "d5/d7d/fs_basic_stream.html#section_canvas_stream_sync", [
          [ "1.10.1 Encode Dummy Latency", "d5/d7d/fs_basic_stream.html#subsection_encode_dummy_latency", null ],
          [ "1.10.2 Stream Dummy Latency", "d5/d7d/fs_basic_stream.html#subsection_stream_dummy_latency", null ],
          [ "1.10.3 Comparison for Encode/Stream Dummy Latency", "d5/d7d/fs_basic_stream.html#subsection_latency_comparison", null ],
          [ "1.10.4 IDSP Encoder Sync", "d5/d7d/fs_basic_stream.html#subsection_idsp_encode_sync", null ]
        ] ],
        [ "1.11 Monochrome", "d5/d7d/fs_basic_stream.html#section_monochrome", null ],
        [ "1.12 Strict Constant Bit Rate", "d5/d7d/fs_basic_stream.html#section_strict_cbr", null ],
        [ "1.13 Multiple Tile Encoding", "d5/d7d/fs_basic_stream.html#section_multiple_sltile_enc", null ],
        [ "1.14 Encoder Dual Cores", "d5/d7d/fs_basic_stream.html#subsection_encoder_dual_cores", null ],
        [ "1.15 Encode PJPEG Tile DRAM Size", "d5/d7d/fs_basic_stream.html#section_pjpeg_tile_size", null ],
        [ "1.16 Insert User-Customized Data into Bitstream", "d5/d7d/fs_basic_stream.html#subsection_custom_sei", null ]
      ] ],
      [ "2. Stream Configuration", "d5/d7d/fs_basic_stream.html#section_stream_configuration", null ],
      [ "3. Stream Examples", "d5/d7d/fs_basic_stream.html#section_stream_example", [
        [ "Example 1: Get Bitstream", "d5/d7d/fs_basic_stream.html#example_get_bit_stream", null ],
        [ "Example 2: Encoding Control", "d5/d7d/fs_basic_stream.html#example_encoding_control", null ],
        [ "Example 3: Encode from Specified Single Canvas", "d5/d7d/fs_basic_stream.html#example_choose_source_canvas", null ],
        [ "Example 4: Setting up Maximum Resolution", "d5/d7d/fs_basic_stream.html#example_stream_resolution", null ],
        [ "Example 5: Cropping from Source Canvas", "d5/d7d/fs_basic_stream.html#example_crop_from_canvas", null ],
        [ "Example 6: Set Encoding Frame Rate", "d5/d7d/fs_basic_stream.html#example_stream_frame_rate", null ],
        [ "Example 7: Set Encoding Duration", "d5/d7d/fs_basic_stream.html#example_encode_duration", null ],
        [ "Example 8: Monochrome Stream", "d5/d7d/fs_basic_stream.html#example_stream_monochrome", null ],
        [ "Example 9: Frame Drop", "d5/d7d/fs_basic_stream.html#example_frame_drop", null ],
        [ "Example 10: Frame Trigger", "d5/d7d/fs_basic_stream.html#example_frame_trigger", null ],
        [ "Example 11: Strict Constant Bit Rate", "d5/d7d/fs_basic_stream.html#example_strict_cbr", null ],
        [ "Example 12: Configure Stream Session ID", "d5/d7d/fs_basic_stream.html#example_stream_session_id", null ],
        [ "Example 13: Display System Information", "d5/d7d/fs_basic_stream.html#example_show_stream_info", null ],
        [ "Example 14: Encoded Frame Order", "d5/d7d/fs_basic_stream.html#example_show_encoded_order", null ],
        [ "Example 15: HEVC Width Padding", "d5/d7d/fs_basic_stream.html#example_hevc_width_padding", null ]
      ] ]
    ] ],
    [ "BASIC - H.264 / H.265 Codec", "d5/d14/fs_basic_codec.html", [
      [ "1. BitRate", "d5/d14/fs_basic_codec.html#codec_br", [
        [ "Example 1: Change Bitrate On the Fly", "d5/d14/fs_basic_codec.html#example_codec_br1", null ],
        [ "Example 2: Set Target Bitrate Per Stream", "d5/d14/fs_basic_codec.html#example_codec_br2", null ],
        [ "Example 3: Display the Target Bitrate", "d5/d14/fs_basic_codec.html#example_codec_br3", null ],
        [ "Example 4: Bitrate changed according to encoding frame factor", "d5/d14/fs_basic_codec.html#example_codec_br4", null ],
        [ "Example 5: Keep bitrate not affected by encoding frame factor", "d5/d14/fs_basic_codec.html#example_codec_br5", null ]
      ] ],
      [ "2. Group of Picture (GOP) Length", "d5/d14/fs_basic_codec.html#codec_gop", [
        [ "Example 6: Force IDR at Shorter GOP", "d5/d14/fs_basic_codec.html#example_codec_gop1", null ],
        [ "Example 7: Force IDR at Longer GOP", "d5/d14/fs_basic_codec.html#example_codec_gop2", null ],
        [ "Example 8: Display Current GOP Length", "d5/d14/fs_basic_codec.html#example_codec_gop3", null ],
        [ "Example 9: Update at Next GOP", "d5/d14/fs_basic_codec.html#example_codec_gop4", null ]
      ] ],
      [ "3. Instantaneous Decoder Refresh (IDR) Frequency", "d5/d14/fs_basic_codec.html#codec_idr", [
        [ "Example 10: Set IDR Interval", "d5/d14/fs_basic_codec.html#example_codec_idr1", null ],
        [ "Example 11: Set IDR Interval Per Stream", "d5/d14/fs_basic_codec.html#example_codec_idr2", null ],
        [ "Example 12: Change IDR Interval On the Fly", "d5/d14/fs_basic_codec.html#example_codec_idr3", null ],
        [ "Example 13: Display Current IDR Frequency", "d5/d14/fs_basic_codec.html#example_codec_idr4", null ]
      ] ],
      [ "4. Force IDR", "d5/d14/fs_basic_codec.html#codec_fidr", [
        [ "Example 14: Generate IDR Frames for H.264 Streams.", "d5/d14/fs_basic_codec.html#example_codec_fidr", null ]
      ] ],
      [ "5. QP Limitation", "d5/d14/fs_basic_codec.html#codec_qp_limit", [
        [ "Example 15: Set QP Range for I Frame.", "d5/d14/fs_basic_codec.html#example_codec_qp_limit", null ]
      ] ],
      [ "6. Adapt QP", "d5/d14/fs_basic_codec.html#codec_qp_adapt", [
        [ "Example 16: Set Adapt QP", "d5/d14/fs_basic_codec.html#example_codec_qp_adapt", null ]
      ] ],
      [ "7. Force P-skip", "d5/d14/fs_basic_codec.html#codec_pskip", [
        [ "Example 17: Add Force P-skip Frame", "d5/d14/fs_basic_codec.html#example_codec_pskip1", null ],
        [ "Example 18: Force P-skip with Normal Mode", "d5/d14/fs_basic_codec.html#example_codec_pskip2", null ],
        [ "Example 19: Force P-skip with Inverted Mode", "d5/d14/fs_basic_codec.html#example_codec_pskip3", null ]
      ] ],
      [ "8. Force Frame Drop", "d5/d14/fs_basic_codec.html#codec_fdrop", [
        [ "Example 20: Force Frame Drop", "d5/d14/fs_basic_codec.html#example_codec_fdrop1", null ],
        [ "Example 21: Force Frame Drop Repeatedly", "d5/d14/fs_basic_codec.html#example_codec_fdrop2", null ]
      ] ],
      [ "9. Skip Frame Strategy and Mode", "d5/d14/fs_basic_codec.html#codec_skip_mode", [
        [ "Example 22: Frames Dropped according to Picture Size", "d5/d14/fs_basic_codec.html#example_codec_smode1", null ],
        [ "Example 23: Frames Skipped according to Picture Size", "d5/d14/fs_basic_codec.html#example_codec_smode2", null ],
        [ "Example 24: Frames Dropped according to CPB Size", "d5/d14/fs_basic_codec.html#example_codec_smode3", null ],
        [ "Example 25: Frames Skipped according to CPB Size", "d5/d14/fs_basic_codec.html#example_codec_smode4", null ],
        [ "Example 26: Frames Dropped according to Target Bitrate", "d5/d14/fs_basic_codec.html#example_codec_smode5", null ],
        [ "Example 27: Frames Skipped according to Target Bitrate", "d5/d14/fs_basic_codec.html#example_codec_smode6", null ],
        [ "Example 28: Set Maximum Skipped Frames Number", "d5/d14/fs_basic_codec.html#example_codec_smode7", null ]
      ] ],
      [ "10. Maximum I Size Limit", "d5/d14/fs_basic_codec.html#codec_ilimit", [
        [ "Example 29: Set the Maximum I Size", "d5/d14/fs_basic_codec.html#example_codec_ilimit", null ]
      ] ],
      [ "11. MV Dump for AVC", "d5/d14/fs_basic_codec.html#codec_mvdump", [
        [ "Example 30: Display Frame of MV Dump", "d5/d14/fs_basic_codec.html#example_codec_mvdump1", null ],
        [ "Example 31: Capture Continuous MV Data", "d5/d14/fs_basic_codec.html#example_codec_mvdump2", null ]
      ] ],
      [ "12. The aqp Type for HEVC", "d5/d14/fs_basic_codec.html#codec_aqp", [
        [ "Example 32: Frame Size Decided by QP Limitation", "d5/d14/fs_basic_codec.html#example_codec_aqp1", null ],
        [ "Example 33: Frame Size Decided by QP of MB", "d5/d14/fs_basic_codec.html#example_codec_aqp2", null ]
      ] ],
      [ "13. Stream Structure au Type", "d5/d14/fs_basic_codec.html#codec_au", [
        [ "Example 34: Specify AUD Before SPS / PPS with SEI Syntax", "d5/d14/fs_basic_codec.html#example_codec_au1", null ],
        [ "Example 35: Set Au-type", "d5/d14/fs_basic_codec.html#example_codec_au2", null ]
      ] ],
      [ "14. ROI Encoding Tools", "d5/d14/fs_basic_codec.html#codec_roi_enc", [
        [ "Example 36: Set Category Lookup Table", "d5/d14/fs_basic_codec.html#example_codec_roi_enc1", null ],
        [ "Example 37: Set User Class Type for MB", "d5/d14/fs_basic_codec.html#example_codec_roi_enc2", null ],
        [ "Example 38: Set QP Offset for H.264", "d5/d14/fs_basic_codec.html#example_codec_roi_enc3", null ],
        [ "Example 39: Set Category Type for CTB", "d5/d14/fs_basic_codec.html#example_codec_roi_enc4", null ]
      ] ],
      [ "15. Frame Sync", "d5/d14/fs_basic_codec.html#codec_fsync", [
        [ "Example 40: Set Encode Dummy Latency for Main Canvas", "d5/d14/fs_basic_codec.html#example_codec_fsync1", null ],
        [ "Example 41: Set Encode Dummy Latency for Specific Canvases", "d5/d14/fs_basic_codec.html#example_codec_fsync2", null ],
        [ "Example 42: Force Insert IDR Frame", "d5/d14/fs_basic_codec.html#example_codec_fsync3", null ],
        [ "Example 43: Set QP Adjust Value", "d5/d14/fs_basic_codec.html#example_codec_fsync4", null ],
        [ "Example 44: Update QP Limitation for P Frame", "d5/d14/fs_basic_codec.html#example_codec_fsync5", null ],
        [ "Example 45: Update QP Limitation for I Frame", "d5/d14/fs_basic_codec.html#example_codec_fsync6", null ],
        [ "Example 46: Force Drop Frames", "d5/d14/fs_basic_codec.html#example_codec_fsync7", null ],
        [ "Example 47: Set Adaptive QP", "d5/d14/fs_basic_codec.html#example_codec_fsync8", null ],
        [ "Example 48: Add Overlay Insertion", "d5/d14/fs_basic_codec.html#example_codec_fsync9", null ],
        [ "Example 49: Add Blur Insertion", "d5/d14/fs_basic_codec.html#example_codec_fsync10", null ],
        [ "Example 50: Setting HEVC Long Start Code", "d5/d14/fs_basic_codec.html#example_codec_long_start_code", null ]
      ] ],
      [ "16. H26x Scalelist", "d5/d14/fs_basic_codec.html#H26X_scalelist", [
        [ "Example 51: Config Scalelist Strength for AVC", "d5/d14/fs_basic_codec.html#example_avc_scalelist_strength", null ],
        [ "Example 52: Custom Scalelist Matrix for AVC", "d5/d14/fs_basic_codec.html#example_avc_scalelist_setting", null ],
        [ "Example 53: Custom Scalelist Matrix for HEVC", "d5/d14/fs_basic_codec.html#example_hevc_scalelist_setting", null ],
        [ "Example 54: Direct Use Scalelist Bin File for AVC", "d5/d14/fs_basic_codec.html#example_avc_scalelist_bin_setting", null ]
      ] ],
      [ "17. Video Full Range", "d5/d14/fs_basic_codec.html#codec_full_range", [
        [ "Example 55: Decode by FFmpeg", "d5/d14/fs_basic_codec.html#example_codec_decode_by_ffmpeg", null ]
      ] ],
      [ "18. Chroma QP Offset", "d5/d14/fs_basic_codec.html#codec_qp_offset", [
        [ "Example 55: Set Chroma QP Offset", "d5/d14/fs_basic_codec.html#example_codec_chroma_qp_offset", null ]
      ] ],
      [ "19. Support CU Size Control for HEVC", "d5/d14/fs_basic_codec.html#codec_cu_size_control", [
        [ "Example 56: Disable CU8 and CU16 Blocks", "d5/d14/fs_basic_codec.html#example_codec_cu_size_control1", null ],
        [ "Example 57: Set Bias Level for CU8 Block", "d5/d14/fs_basic_codec.html#example_codec_cu_size_control2", null ],
        [ "Example 58: Set Bias Level for CU16 Block", "d5/d14/fs_basic_codec.html#example_codec_cu_size_control3", null ]
      ] ],
      [ "20. Q Frame Mechanism", "d5/d14/fs_basic_codec.html#codec_qframe", [
        [ "Example 59: Set Q Frame Number for AVC", "d5/d14/fs_basic_codec.html#example_codec_qframe1", null ],
        [ "Example 60: Set Q Frame Number for HEVC", "d5/d14/fs_basic_codec.html#example_codec_qframe2", null ]
      ] ]
    ] ],
    [ "BASIC - GOP", "db/d91/fs_basic_gop.html", [
      [ "1. Simple GOP", "db/d91/fs_basic_gop.html#gop_simple", [
        [ "1.1 Simple GOP without B frame", "db/d91/fs_basic_gop.html#gop_simple_without_B", [
          [ "Example 1: Simple GOP without B Frame", "db/d91/fs_basic_gop.html#example_gop_simple1", null ]
        ] ],
        [ "1.2 Simple GOP With B Frame", "db/d91/fs_basic_gop.html#gop_simple_with_B", [
          [ "Example 2: Simple GOP with B frame", "db/d91/fs_basic_gop.html#example_gop_simple2", null ]
        ] ]
      ] ],
      [ "2. Fast Seek GOP", "db/d91/fs_basic_gop.html#gop_fast_seek", [
        [ "2.1 Fast Seek GOP", "db/d91/fs_basic_gop.html#gop_simple_fast_seek", [
          [ "Example 3: Fast seek GOP", "db/d91/fs_basic_gop.html#example_gop_fast_seek", null ],
          [ "Example 4: Special fast seek :\"non-ref-P\" (fast-seek-interval = 1)", "db/d91/fs_basic_gop.html#example_gop_simple3", null ]
        ] ]
      ] ],
      [ "3. Two References GOP", "db/d91/fs_basic_gop.html#gop_2ref", [
        [ "3.1 Two Reference GOP with Short Term Ref and Long Term Ref", "db/d91/fs_basic_gop.html#gop_2ref_st_lt", [
          [ "Example 5: Two reference GOP with short term ref and long term ref", "db/d91/fs_basic_gop.html#example_gop_2ref_st_lt", null ]
        ] ],
        [ "3.2 Two Short Term References", "db/d91/fs_basic_gop.html#gop_2ref_short_term", [
          [ "Example 6: Two short term reference GOP", "db/d91/fs_basic_gop.html#example_gop_2ref_short_term", null ]
        ] ]
      ] ],
      [ "4. Two References with Fast Seek GOP", "db/d91/fs_basic_gop.html#gop_2ref_fastseek", [
        [ "4.1 Two references with Fast Seek without B Frame", "db/d91/fs_basic_gop.html#gop_2ref_fastseek_without_B", [
          [ "Example 7: Two references with fast seek GOP without B", "db/d91/fs_basic_gop.html#example_gop_2ref2", null ]
        ] ],
        [ "4.3 Two references with Fast Seek with B", "db/d91/fs_basic_gop.html#gop_2ref_fastseek_with_B", [
          [ "Example 8: Two references with fast seek GOP with B", "db/d91/fs_basic_gop.html#example_gop_2ref_fastseek_with_B", null ]
        ] ]
      ] ],
      [ "5. SVC-T", "db/d91/fs_basic_gop.html#gop_svct", [
        [ "5.1 Hierarchical P GOP", "db/d91/fs_basic_gop.html#gop_svct_hp", [
          [ "Example 9: SVC-T 2 GOP", "db/d91/fs_basic_gop.html#example_gop_svct2", null ],
          [ "Example 10: SVC-T 3 GOP", "db/d91/fs_basic_gop.html#example_gop_svct3", null ]
        ] ],
        [ "5.2 Fast Seek in SVC-T 2/3 Layers", "db/d91/fs_basic_gop.html#gop_svct_fastseek", [
          [ "Example 11: 2 layers SVC-T of HEVC with fast seek interval 6", "db/d91/fs_basic_gop.html#example_gop_svct4", null ],
          [ "Example 12: 3 layers SVC-T of AVC with fast seek interval 4", "db/d91/fs_basic_gop.html#example_gop_svct5", null ]
        ] ]
      ] ]
    ] ],
    [ "BASIC - On-the-Fly Settings", "d0/d89/fs_basic_on_the_fly.html", [
      [ "1. On the fly settings", "d0/d89/fs_basic_on_the_fly.html#on_the_fly", null ]
    ] ],
    [ "BASIC - Privacy Mask", "da/de1/fs_basic_pm.html", [
      [ "1. Privacy Mask", "da/de1/fs_basic_pm.html#section_pm", null ],
      [ "2. Privacy Mask Examples", "da/de1/fs_basic_pm.html#section_sc_pm_examples", [
        [ "Example 1: Add Two Privacy Masks", "da/de1/fs_basic_pm.html#example_pm1", null ],
        [ "Example 2: Remove One Small Mask Area from Privacy Mask Region", "da/de1/fs_basic_pm.html#example_pm2", null ],
        [ "Example 3: Insert Circular Inner Privacy Mask", "da/de1/fs_basic_pm.html#example_pm3", null ],
        [ "Example 4: Insert Circular Outer Privacy Mask", "da/de1/fs_basic_pm.html#example_pm4", null ],
        [ "Example 5: Insert Triangle Privacy Mask", "da/de1/fs_basic_pm.html#example_pm5", null ],
        [ "Example 6: Insert Quadrilateral Privacy Mask", "da/de1/fs_basic_pm.html#example_pm6", null ],
        [ "Example 7: Insert canvas domain PM to support cross-channel stitching case", "da/de1/fs_basic_pm.html#example_pm7", null ],
        [ "Example 8: Clear All Privacy Masks", "da/de1/fs_basic_pm.html#example_pm8", null ],
        [ "Example 9: Fill Warp Frame Border Artifact", "da/de1/fs_basic_pm.html#example_pm9", null ]
      ] ]
    ] ],
    [ "BASIC - Blur on Streams", "dd/d39/fs_basic_blur.html", [
      [ "1. Blur on Streams", "dd/d39/fs_basic_blur.html#section_blur", [
        [ "1.1 Blur Lua Configuration", "dd/d39/fs_basic_blur.html#blur_lua_cfg", null ]
      ] ],
      [ "2. Stream Blur Examples", "dd/d39/fs_basic_blur.html#section_blur_example", [
        [ "Example 1: Rectangle Blur on Stream A", "dd/d39/fs_basic_blur.html#example_blur_on_stream", null ],
        [ "Example 2: Run Arbitrary Blur Demo", "dd/d39/fs_basic_blur.html#example_arbitrary_blur_on_stream", null ],
        [ "Example 3: Apply Different Blur Coefficients on Stream", "dd/d39/fs_basic_blur.html#example_blur_coeff_on_stream", null ],
        [ "Example 4: Frame Accurate Blur Insertion", "dd/d39/fs_basic_blur.html#example_blur_frame_sync", null ]
      ] ]
    ] ],
    [ "BASIC - Overlay on Streams", "da/d36/fs_basic_overlay.html", [
      [ "1. Overlay Features", "da/d36/fs_basic_overlay.html#section_overlay_feature", null ],
      [ "2. Overlay Examples", "da/d36/fs_basic_overlay.html#section_overlay_example", [
        [ "Example 1: Rectangle Overlay", "da/d36/fs_basic_overlay.html#example_overlay_rect", null ],
        [ "Example 2: Update the Overlay Every Frame", "da/d36/fs_basic_overlay.html#example_overlay_always", null ]
      ] ]
    ] ],
    [ "BASIC - Playback", "d4/d15/fs_basic_playback.html", [
      [ "1. Normal Playback", "d4/d15/fs_basic_playback.html#pb_npb", [
        [ "Example 1: Playback H.264 / H.265 stream and show the HDMI VOUT", "d4/d15/fs_basic_playback.html#example_pb_npb1", null ],
        [ "Example 2: Multi-channel Playback and Show the HDMI® VOUT", "d4/d15/fs_basic_playback.html#example_pb_npb2", null ],
        [ "Example 3: Playback Virtual Channels and Show the HDMI VOUT", "d4/d15/fs_basic_playback.html#example_pb_npb3", null ]
      ] ],
      [ "2. Lua File Configuration for Decoder", "d4/d15/fs_basic_playback.html#pb_lua_config", [
        [ "2.1 Decoder Configuration", "d4/d15/fs_basic_playback.html#pb_lua_dec_config", null ],
        [ "2.2 Lua File Configuration for Virtual VIN Mode", "d4/d15/fs_basic_playback.html#pb_lua_vin_config", null ],
        [ "2.3 Lua File Configuration for Multi-channel Decoding", "d4/d15/fs_basic_playback.html#pb_lua_ut_config", null ],
        [ "2.4 Lua File Configuration for Decode Virtual Channel", "d4/d15/fs_basic_playback.html#pb_lua_vc_config", null ]
      ] ],
      [ "3. Software Decoding Performance", "d4/d15/fs_basic_playback.html#pb_perf", null ]
    ] ],
    [ "BASIC - Duplex", "d6/d35/fs_basic_duplex.html", [
      [ "1. Duplex", "d6/d35/fs_basic_duplex.html#duplex_sec1", null ]
    ] ],
    [ "BASIC - Data Dumping", "d1/d3e/fs_basic_data_dump.html", [
      [ "1. Data Dumping", "d1/d3e/fs_basic_data_dump.html#data_dump", [
        [ "Example 1: Getting 1080p Raw Data for Calibration (CFA Input Only)", "d1/d3e/fs_basic_data_dump.html#example_data_dump1", null ],
        [ "Example 2: Capture 1080p YUV from Canvas 0 with a Blocking Call", "d1/d3e/fs_basic_data_dump.html#example_data_dump2", null ],
        [ "Example 3: Capture 480p YUV from Canvas 1 with a Non-blocking Call", "d1/d3e/fs_basic_data_dump.html#example_data_dump3", null ],
        [ "Example 4: Capture 480p ME Data from Canvas 0 in 30 Frames with a Blocking Call", "d1/d3e/fs_basic_data_dump.html#example_data_dump4", null ],
        [ "Example 5: Capture 480p ME Data from Canvas 1 in 30 Frames with a Blocking Call", "d1/d3e/fs_basic_data_dump.html#example_data_dump5", null ],
        [ "Example 6: Capture Raw slice Data", "d1/d3e/fs_basic_data_dump.html#example_data_dump6", null ]
      ] ],
      [ "2. Data Dumping: Capture Raw Data via Direct IO", "d1/d3e/fs_basic_data_dump.html#data_dump_raw_dio", [
        [ "Example 6: Capture 8K Raw Data from CV5x via Direct IO", "d1/d3e/fs_basic_data_dump.html#example_data_8K_raw_dump_via_direct_io", null ]
      ] ],
      [ "3. Data Dumping:  MV Dump", "d1/d3e/fs_basic_data_dump.html#data_dump_mv", [
        [ "Example 7: Capture 720p MV Data with Blocking Way", "d1/d3e/fs_basic_data_dump.html#example_mv_dump1", null ],
        [ "Example 8: Capture 720p Continuous MV Data with Blocking Way", "d1/d3e/fs_basic_data_dump.html#example_mv_dump2", null ]
      ] ],
      [ "4. QP Histogram Dump for AVC and HEVC", "d1/d3e/fs_basic_data_dump.html#data_dump_qp_hist", [
        [ "Example 9: Display QP Histogram Dump of 1 Frame for AVC", "d1/d3e/fs_basic_data_dump.html#example_avc_qp_hist_dump", null ],
        [ "Example 10: Display QP Histogram Dump of 1 Frame for CV5x HEVC with Dual Core Spatial Mode", "d1/d3e/fs_basic_data_dump.html#example_hevc_qp_hist_dump", null ]
      ] ],
      [ "5. Dump and Display IDSP Motion Data with Encode Mode 5/9", "d1/d3e/fs_basic_data_dump.html#data_dump_idsp_motion", null ]
    ] ],
    [ "BASIC - Frame Rate", "dc/d95/fs_basic_fps.html", [
      [ "1. Frame Rate", "dc/d95/fs_basic_fps.html#section_fps_features", null ],
      [ "2. High Precision Frame Rate", "dc/d95/fs_basic_fps.html#hp_fps", [
        [ "2.1 Introduction", "dc/d95/fs_basic_fps.html#hp_fps_intro", null ],
        [ "2.2 Enable High Precison Frame Rate", "dc/d95/fs_basic_fps.html#hp_fps_enable", null ],
        [ "2.3 Using High Precison Frame Rate", "dc/d95/fs_basic_fps.html#hp_fps_apply", null ]
      ] ],
      [ "3. Frame Rate Examples", "dc/d95/fs_basic_fps.html#framerate_example", [
        [ "Example 1: fps suggestion", "dc/d95/fs_basic_fps.html#example_fps1", null ],
        [ "Example 2: High Precision fps", "dc/d95/fs_basic_fps.html#example_high_precision_fps", null ],
        [ "Example 3: Canvas Zero fps", "dc/d95/fs_basic_fps.html#example_canvas_zero_fps", null ],
        [ "Example 4: Stream Absolute fps", "dc/d95/fs_basic_fps.html#example_stream_abs_fps", null ],
        [ "Example 5: RAW fps", "dc/d95/fs_basic_fps.html#example_raw_fps", null ],
        [ "Example 6: Set different RAW fps for scale VIN and ROI VIN", "dc/d95/fs_basic_fps.html#example_raw_fps_scale_roi_vin", null ],
        [ "Example 7: Update VIN fps on the fly", "dc/d95/fs_basic_fps.html#exampe_update_vin_fps", null ]
      ] ]
    ] ],
    [ "BASIC - HDR", "db/deb/fs_basic_hdr.html", [
      [ "1. Line-Interleaved High Dynamic Range", "db/deb/fs_basic_hdr.html#line_intlv_hdr", [
        [ "Example 1. imx274_mipi 1080p30 2X HDR VIN mode.", "db/deb/fs_basic_hdr.html#example_line_intlv_hdr1", null ],
        [ "Example 2. imx274_mipi 5MP30 2X HDR VIN mode.", "db/deb/fs_basic_hdr.html#example_line_intlv_hdr2", null ],
        [ "Example 3. imx290_mipi 3X HDR + 1080p30 VIN mode.", "db/deb/fs_basic_hdr.html#example_line_intlv_hdr4", null ],
        [ "Example 4. imx678_mipi 2X HDR (DCG) + 3840x2160 VIN mode.", "db/deb/fs_basic_hdr.html#example_dcg_hdr2", null ]
      ] ]
    ] ],
    [ "ADVANCED - Encode Mode", "df/d92/fs_adv_enc_mode.html", [
      [ "1. Encode Mode", "df/d92/fs_adv_enc_mode.html#section_encode_mode", [
        [ "1.1 Comparison", "df/d92/fs_adv_enc_mode.html#mode_comparision", null ],
        [ "1.2 Mode 0: Normal ISO Mode", "df/d92/fs_adv_enc_mode.html#mode_normal_iso", null ],
        [ "1.3 Mode 1: Multi-Region Warp", "df/d92/fs_adv_enc_mode.html#mode_multi_region_warp", null ],
        [ "1.4 Mode 5: Advanced HDR", "df/d92/fs_adv_enc_mode.html#mode_advanced_hdr", null ],
        [ "1.5 Mode 127: VIN Only Mode", "df/d92/fs_adv_enc_mode.html#mode_vin_only", null ]
      ] ],
      [ "2. Encode Mode Examples", "df/d92/fs_adv_enc_mode.html#section_enc_mode_examples", [
        [ "Example 1: Normal ISO mode example", "df/d92/fs_adv_enc_mode.html#example_iso", null ],
        [ "Example 2: Advanced HDR mode example", "df/d92/fs_adv_enc_mode.html#example_hdr", null ]
      ] ]
    ] ],
    [ "ADVANCED - Configure with Lua Script", "d8/dab/fs_adv_lua.html", [
      [ "1. Introduction to Lua Configuration", "d8/dab/fs_adv_lua.html#lua_lua", null ],
      [ "2. VSRC Configuration", "d8/dab/fs_adv_lua.html#lua_vsrc_cfg", [
        [ "2.1 VSRC Common Configuration", "d8/dab/fs_adv_lua.html#lua_vsrc_cfg_common", null ],
        [ "2.2 Custom Virtual VIN Mode Configuration", "d8/dab/fs_adv_lua.html#lua_src_virtual_cfg", null ]
      ] ],
      [ "3. Channel Configuration", "d8/dab/fs_adv_lua.html#lua_chan_cfg", [
        [ "3.1 Buffer Configuration", "d8/dab/fs_adv_lua.html#lua_buf_cfg", null ],
        [ "3.2 Pyramid Configuration", "d8/dab/fs_adv_lua.html#lua_pyramid_cfg", null ]
      ] ],
      [ "4. Canvas Configuration", "d8/dab/fs_adv_lua.html#lua_canvas_cfg", null ],
      [ "5. Stream Configuration", "d8/dab/fs_adv_lua.html#lua_stream_cfg", null ],
      [ "6. VOUT Configuration", "d8/dab/fs_adv_lua.html#lua_vout_cfg", null ],
      [ "7. Lua Script Examples", "d8/dab/fs_adv_lua.html#section_lua_example", [
        [ "Example 1: Single VIN with 1080p30 Input", "d8/dab/fs_adv_lua.html#example_lua1", null ]
      ] ]
    ] ],
    [ "ADVANCED - Multi-VIN & Multi-Channel", "d3/dc4/fd_adv_multi_vin.html", [
      [ "1. Overview", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_overview", [
        [ "1.1 Key Updates", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_key_updates", null ],
        [ "1.2 Uses of Multi-VIN", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_uses_of_multi_vin", null ],
        [ "1.3 Third-Party SERDES Chips", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_third_party_serdes_chips", null ],
        [ "1.4 Reference Kit", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_reference_kit", [
          [ "1.4.1 CV5 Multi-VIN Design Kit", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_cv5_multi_vin_design_kit", null ],
          [ "1.4.2 CV52 Multi-VIN Design Kit", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_cv52_multi_vin_design_kit", null ],
          [ "1.4.3 CV72 Multi-VIN Design Kit", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_cv72_multi_vin_design_kit", null ],
          [ "1.4.4 MAX9296 Board", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_max9296_board", null ]
        ] ]
      ] ],
      [ "2 Product Plan", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_product_plan", [
        [ "2.1 Quad Sensors with a Long Cable through MAX9296", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_quad_sensors_with_a_long_cable_through_max9296", null ],
        [ "2.2 Quad Independent Sensors", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_quad_independent_sensors", null ],
        [ "2.3 Dual Channels from a Single Sensor", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_channels_from_a_single_sensor", null ],
        [ "2.4 Dual Sensors with Different Modes from Single SERDES", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_sensors_with_different_modes_from_single_serdes", null ],
        [ "2.5 Dual Channels from a Single Sensor and Raw Data", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_channels_from_a_single_sensor_and_raw_data", null ],
        [ "2.6 Dual Channels from a Single Sensor with Dual Vsrc_ctx", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_channels_from_a_single_sensor_with_dual_vsrc_ctx", null ],
        [ "2.7 Supported Sensors", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_supported_sensors", null ],
        [ "2.8 Stream View", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_stream_view", [
          [ "2.8.1 Independent Stream View", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_independent_stream_view", null ],
          [ "2.8.2 Blend Stream View", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_blend_stream_view", null ],
          [ "2.8.3 PIP Stream View", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_pip_stream_view", null ]
        ] ]
      ] ],
      [ "3 System Design", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_system_design", [
        [ "3.1 Memory Management", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_memory_management", null ],
        [ "3.2 Data Flow", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_data_flow", [
          [ "3.2.1 Dual VIN Controllers", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_vin_controllers", null ],
          [ "3.2.2 Quad Sensors (Long Cable) with SERDES", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_quad_sensors_long_cable_with_serdes", null ],
          [ "3.2.3 IDSP Virtual Channels", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_idsp_virtual_channels", null ],
          [ "3.2.4 Single Sensor with a Dual Vsrc_ctx.", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_single_sensor_with_a_dual_vsrc_ctx", null ],
          [ "3.2.5 Vsrc to Channel", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_vsrc_to_channel", null ],
          [ "3.2.6 Channel to Canvas", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_channel_to_canvas", null ]
        ] ],
        [ "3.3 Concept and Configuration", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_concept_and_configuration", [
          [ "3.3.1 Sensor Configuration", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_sensor_configuration", null ],
          [ "3.3.2 Channel Configuration", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_channel_configuration", null ],
          [ "3.3.3 Channel Group", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_channel_group", null ],
          [ "3.3.4 Buffer Layout", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_buffer_layout", null ],
          [ "3.3.5 Pyramid Layout", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_pyramid_layout", null ],
          [ "3.3.6 Canvas Layout", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_canvas_layout", null ],
          [ "3.3.7 Stream Configuration", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_stream_configuration", null ],
          [ "3.3.8 VOUT Layout", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_vout_layout", null ]
        ] ],
        [ "3.4 Sensor Driver Installation", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_sensor_driver_installation", null ]
      ] ],
      [ "4 Examples", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_examples", [
        [ "4.1 Quad Sensors with a Long Cable through MAX9296", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_quad_sensors_with_a_long_cable_through_max9296_4_1", [
          [ "4.1.1 Test Commands", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_test_commands_4_1", null ],
          [ "4.1.2 Lua Script", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_lua_script_4_1", null ]
        ] ],
        [ "4.2 Dual Channels from a Single Sensor", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_channels_from_a_single_sensor_4_2", [
          [ "4.2.1 Test Commands", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_test_commands_4_2", null ],
          [ "4.2.2 Lua Script", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_lua_script_4_2", null ]
        ] ],
        [ "4.3 Dual Channels from the Sensor and the YUV Raw Data", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_channels_from_the_sensor_and_the_yuv_raw_data", [
          [ "4.3.1 Test Commands", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_test_commands_4_3", null ],
          [ "4.3.2 Lua Script", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_lua_script_4_3", null ]
        ] ],
        [ "4.4 Dual Sensors with Different Modes from MAX9296", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_sensors_with_different_modes_from_max9296", [
          [ "4.4.1 Test Commands", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_test_commands_4_4", null ],
          [ "4.4.2 Lua Script", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_lua_script_4_4", null ]
        ] ],
        [ "4.5 Dual Channels from IMX264 with Dual Vsrc_ctx", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dual_channels_from_imx264_with_dual_vsrc_ctx", [
          [ "4.5.1 Test Commands", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_test_commands_4_5", null ],
          [ "4.5.2 Lua Script", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_lua_script_4_5", null ]
        ] ],
        [ "4.6 Quad Sensors with imx274", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_quad_sensors_with_imx274", [
          [ "4.6.1 Test Commands", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_test_commands_4_6", null ],
          [ "4.6.2 Lua Script", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_lua_script_4_6", null ]
        ] ],
        [ "4.7 Multiple YUV Input", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_multiple_yuv_input", [
          [ "4.7.1 Preparation", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_preparation_4_7", null ],
          [ "4.7.2 Test Commands", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_test_commands_4_7", null ],
          [ "4.7.3 Lua Script", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_lua_script_4_7", null ]
        ] ],
        [ "4.8 Quad Sensors through Bridge Chip", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_quad_sensors_through_bridge_chip", [
          [ "4.8.1 Preparation", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_preparation_4_8", null ],
          [ "4.8.1 Test Commands", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_test_commands_4_8", null ],
          [ "4.8.2 Lua Script", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_lua_script_4_8", null ]
        ] ]
      ] ],
      [ "5 On the fly Settings", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_on_the_fly_settings", [
        [ "5.1 Digital Pan / Tilt / Zoom (DPTZ)", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_digital_pan_tilt_zoom", null ],
        [ "5.2 Turn the Preview Buffers On / Off", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_turn_the_preview_buffer_on_off", null ],
        [ "5.3 Dump Multi-Channel Configurations", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_dump_multi_channel_configurations", null ]
      ] ],
      [ "6 FAQ", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_faq", null ],
      [ "7 License", "d3/dc4/fd_adv_multi_vin.html#multi_vin_design_doc_license", null ]
    ] ],
    [ "ADVANCED - Multi-Pass", "d3/ddf/fs_adv_multi_pass.html", [
      [ "1. Multi-Pass Features", "d3/ddf/fs_adv_multi_pass.html#multi_pass_features", null ],
      [ "2. Multi-Pass Configuration", "d3/ddf/fs_adv_multi_pass.html#lua_multi_pass_configuration", null ],
      [ "3. Multi-Pass Examples", "d3/ddf/fs_adv_multi_pass.html#multi_pass_example", [
        [ "Example 1: Input from Single-View Canvas", "d3/ddf/fs_adv_multi_pass.html#example_multi_pass_1", null ],
        [ "Example 2: Input from Multi-View Canvas", "d3/ddf/fs_adv_multi_pass.html#example_multi_pass_2", null ]
      ] ]
    ] ],
    [ "ADVANCED - Lens Distortion Correction", "de/d79/fs_adv_ldc.html", [
      [ "1. Single VIN Lens Distortion Correction (LDC)", "de/d79/fs_adv_ldc.html#single_vin_ldc", [
        [ "1.1 Lens No Transform", "de/d79/fs_adv_ldc.html#lens_no_transform", [
          [ "Example 1: Lens No Transform", "de/d79/fs_adv_ldc.html#lens_no_trans_exp", null ],
          [ "1.2 Lens Rectilinear", "de/d79/fs_adv_ldc.html#lens_rectilinear", null ],
          [ "Example 3: Lens Trapezoid Warp", "de/d79/fs_adv_ldc.html#lens_trapezoid_warp", null ],
          [ "Example 4: Lens Advance Pitch / Yaw", "de/d79/fs_adv_ldc.html#lens_adv_py", null ],
          [ "Example 5: Lens Polar Warp", "de/d79/fs_adv_ldc.html#lens_polar_warp", null ],
          [ "Example 6: Lens Eyeball Rotation: Pan / Tilt", "de/d79/fs_adv_ldc.html#lens_eyeball_pan_tilt", null ],
          [ "Example 7: Lens Eyeball Rotation: Rotate", "de/d79/fs_adv_ldc.html#lens_eyeball_rotate", null ],
          [ "Example 8: Lens ROI", "de/d79/fs_adv_ldc.html#lens_region_of_interest", null ]
        ] ],
        [ "1.3 Lens Pannini", "de/d79/fs_adv_ldc.html#lens_pannini", [
          [ "Example 9: Lens Pannini", "de/d79/fs_adv_ldc.html#lens_pannini_exp", null ]
        ] ],
        [ "1.4 Lens Pincushion", "de/d79/fs_adv_ldc.html#lens_pincushion", [
          [ "Example 10: Lens Pincushion", "de/d79/fs_adv_ldc.html#lens_pincushion_exp", null ]
        ] ],
        [ "1.5 Lens Panorama", "de/d79/fs_adv_ldc.html#lens_panorama", [
          [ "Example 11: Lens Panorama", "de/d79/fs_adv_ldc.html#lens_panorama_exp", null ],
          [ "Example 12: Lens Panorama Fan Warp", "de/d79/fs_adv_ldc.html#lens_panorama_fan", null ],
          [ "Example 13: Lens Panorama Rotate", "de/d79/fs_adv_ldc.html#lens_panorama_rotate", null ]
        ] ],
        [ "1.6 Lens Mercator", "de/d79/fs_adv_ldc.html#lens_mercator", [
          [ "Example 14: Lens Mercator", "de/d79/fs_adv_ldc.html#lens_mercator_exp", null ]
        ] ],
        [ "1.7 Lens Equirectangular", "de/d79/fs_adv_ldc.html#lens_equirectangular", [
          [ "Example 15: Lens Equirectangular", "de/d79/fs_adv_ldc.html#lens_equirectangular_exp", null ]
        ] ],
        [ "1.8 Lens Squircular", "de/d79/fs_adv_ldc.html#lens_squircular", [
          [ "Example 16: Lens Squircular", "de/d79/fs_adv_ldc.html#lens_squirecular_exp", null ]
        ] ],
        [ "1.9 Lens Vertical Panorama", "de/d79/fs_adv_ldc.html#lens_vertical_panorama", [
          [ "Example 17: Lens Vertical Panorama", "de/d79/fs_adv_ldc.html#lens_vertical_panorama_exp", null ],
          [ "Example 18: Lens Transverse Mercator", "de/d79/fs_adv_ldc.html#lens_transverse_mercator", null ]
        ] ],
        [ "1.10 Lens Transform 2D Vector to 1D+1D", "de/d79/fs_adv_ldc.html#fs_transform_twin_vector_to_idsp_format", [
          [ "Example 19: Lens Transform 2D Vector to 1D+1D", "de/d79/fs_adv_ldc.html#transform_twin_vextor_exp", null ]
        ] ],
        [ "1.11 Point Mapping with Warp Table", "de/d79/fs_adv_ldc.html#fs_point_mapping_warp_table", [
          [ "Example 20: Point Mapping with Warp Table", "de/d79/fs_adv_ldc.html#point_mapping_warp_table_exp", null ]
        ] ],
        [ "1.12 Lens Warp Input Mode", "de/d79/fs_adv_ldc.html#fs_warp_input_mode", [
          [ "Example 21: Lens Warp Input Mode", "de/d79/fs_adv_ldc.html#warp_input_mode_exp", null ]
        ] ],
        [ "1.13 Lens Perspective Matrix Correction", "de/d79/fs_adv_ldc.html#fs_pers_mat", [
          [ "Example 22: Lens Perspective Matrix Correction", "de/d79/fs_adv_ldc.html#pers_mat_exp", null ]
        ] ]
      ] ],
      [ "2. Smart LDC", "de/d79/fs_adv_ldc.html#section_smart_ldc", null ]
    ] ],
    [ "ADVANCED - Multi-Region Dewarp", "d5/d18/fs_adv_dewarp.html", [
      [ "1. Wall Mount", "d5/d18/fs_adv_dewarp.html#wall_mount", [
        [ "Example 1: Wall Rectilinear", "d5/d18/fs_adv_dewarp.html#dewarp_wall_rectilinear", null ],
        [ "Example 2: Wall Rectilinear Eyeball Rotation", "d5/d18/fs_adv_dewarp.html#dewarp_wall_rectilinear_eyeball", null ],
        [ "Example 3: Wall Rectilinear Polar Warp", "d5/d18/fs_adv_dewarp.html#dewarp_wall_rectilinear_polar", null ],
        [ "Example 4: Wall Rectilinear Advance Pitch/Yaw", "d5/d18/fs_adv_dewarp.html#dewarp_wall_rectilinear_adv_py", null ],
        [ "Example 5: Wall Pannini", "d5/d18/fs_adv_dewarp.html#dewarp_wall_pannini", null ],
        [ "Example 6: Wall Panorama", "d5/d18/fs_adv_dewarp.html#dewarp_wall_panorama", null ],
        [ "Example 7: Wall Panorama Fan Warp", "d5/d18/fs_adv_dewarp.html#dewarp_wall_panorama_fan", null ],
        [ "Example 8: Wall Panorama Rotate", "d5/d18/fs_adv_dewarp.html#dewarp_wall_panorama_rotate", null ],
        [ "Example 9: Wall Cylindrical", "d5/d18/fs_adv_dewarp.html#dewarp_wall_cylinder", null ],
        [ "Example 10: Wall Mercator", "d5/d18/fs_adv_dewarp.html#dewarp_wall_mercator", null ],
        [ "Example 11: Wall Equirectangular", "d5/d18/fs_adv_dewarp.html#dewarp_wall_equirectangular", null ],
        [ "Example 12: Wall Squircular", "d5/d18/fs_adv_dewarp.html#dewarp_wall_squircular", null ],
        [ "Example 13: Wall Transverse Mercator", "d5/d18/fs_adv_dewarp.html#dewarp_wall_transverse_mercator", null ],
        [ "Example 14: Wall Vertical Panorama", "d5/d18/fs_adv_dewarp.html#dewarp_wall_vertical_panorama", null ],
        [ "Example 15: No Transform + Wall Rectilinear + Wall Panorama", "d5/d18/fs_adv_dewarp.html#dewarp_notrans_wall_rectilinear_wall_panorama", null ],
        [ "Example 16: Wall Panorama + Warp Copy", "d5/d18/fs_adv_dewarp.html#dewarp_wall_panorama_warp_copy", null ],
        [ "Example 17: Wall Rectilinear + Wall Polar Warp + Wall Advance Pitch + Wall Mercator", "d5/d18/fs_adv_dewarp.html#dewarp_wall_rect_adv_mercator", null ],
        [ "Example 18: Wall Panorama + Eyeball Rotation", "d5/d18/fs_adv_dewarp.html#dewarp_wall_panorama_eyeball", null ],
        [ "Example 19: No Transform Rotate", "d5/d18/fs_adv_dewarp.html#dewarp_no_transform_rotate", null ]
      ] ],
      [ "2. Ceiling Mount", "d5/d18/fs_adv_dewarp.html#ceiling_mount", [
        [ "Example 20: Ceiling Rectilinear: North, South, West, and East", "d5/d18/fs_adv_dewarp.html#dewarp_ceiling_rectilinear", null ],
        [ "Example 21: Ceiling Panorama Mode - 360", "d5/d18/fs_adv_dewarp.html#dewarp_ceiling_panorama_360", null ],
        [ "Example 22: Ceiling Sub-Region", "d5/d18/fs_adv_dewarp.html#dewarp_ceiling_sub_region", null ],
        [ "Example 23: Ceiling Double Panorama", "d5/d18/fs_adv_dewarp.html#dewarp_ceiling_double_panorama", null ],
        [ "Example 24: Ceiling 1O+3R", "d5/d18/fs_adv_dewarp.html#dewarp_ceiling_1O_3R", null ],
        [ "Example 25: Ceiling 4R", "d5/d18/fs_adv_dewarp.html#dewarp_ceiling_4R", null ]
      ] ],
      [ "3. Desktop Mount", "d5/d18/fs_adv_dewarp.html#desktop_mount", [
        [ "Example 26: Desktop Rectilinear North, South, West and East", "d5/d18/fs_adv_dewarp.html#dewarp_desktop_rectilinear", null ],
        [ "Example 27: Desktop Panorama Mode - 360", "d5/d18/fs_adv_dewarp.html#dewarp_desktop_panorama_360", null ],
        [ "Example 28: Desktop Sub-Region", "d5/d18/fs_adv_dewarp.html#dewarp_desktop_sub_region", null ]
      ] ],
      [ "4. Point Mapping", "d5/d18/fs_adv_dewarp.html#ut_point_mapping", [
        [ "Example 29: Point Mapping", "d5/d18/fs_adv_dewarp.html#dewarp_pm_exp", null ]
      ] ],
      [ "5. Warp DPTZ", "d5/d18/fs_adv_dewarp.html#ut_warp_dptz", [
        [ "Example 30: Warp DPTZ", "d5/d18/fs_adv_dewarp.html#dewarp_warp_dptz_exp", null ]
      ] ],
      [ "6. Warp Area Update", "d5/d18/fs_adv_dewarp.html#ut_warp_area_update", [
        [ "Example 31: Warp Area Update", "d5/d18/fs_adv_dewarp.html#dewarp_warp_area_update_exp", null ]
      ] ]
    ] ],
    [ "ADVANCED - Vsync Loss", "d0/d09/fs_adv_vl.html", [
      [ "1. Guard Vsync Loss", "d0/d09/fs_adv_vl.html#gvl_gvl", [
        [ "Example 1: Guard Vsync Loss for Single VIN (imx274_mipi)", "d0/d09/fs_adv_vl.html#example_vincap1", null ],
        [ "Example 2: Guard Vsync Loss for Multi-VIN (imx586_mipi + imx274_mipi) on CV5x", "d0/d09/fs_adv_vl.html#example_vincap2", null ]
      ] ]
    ] ],
    [ "ADVANCED - Arbitrary Image Scaler", "d8/d93/fs_adv_arb_img_scaler.html", [
      [ "1. Arbitrary Image Scaler", "d8/d93/fs_adv_arb_img_scaler.html#arbi_img_scaler", null ],
      [ "2. Arbitrary Image Scaler Example", "d8/d93/fs_adv_arb_img_scaler.html#section_img_scller_examples", [
        [ "Example 1: Crop and Upscale from Canvas0 (YUV420) with Top-Left Offset 100x200 and Size 480p to 1080p", "d8/d93/fs_adv_arb_img_scaler.html#example_arbi_img_scaler1", null ]
      ] ]
    ] ],
    [ "ADVANCED - Encode from Memory", "d9/dc7/fs_adv_efm.html", [
      [ "1. Encode from Memory", "d9/dc7/fs_adv_efm.html#efm_efm", null ],
      [ "2. Preparations", "d9/dc7/fs_adv_efm.html#preparations", [
        [ "2.1 Memory", "d9/dc7/fs_adv_efm.html#memory", null ],
        [ "2.2 Configrations", "d9/dc7/fs_adv_efm.html#configrations", null ]
      ] ],
      [ "3. EFM Examples", "d9/dc7/fs_adv_efm.html#efm_exp", [
        [ "Example 1: Encode H.264 stream from EFM buffer: Input from main buffer", "d9/dc7/fs_adv_efm.html#example_efm1", null ],
        [ "Example 2: Encode 4K H.264 stream from EFM buffer: Input from main buffer", "d9/dc7/fs_adv_efm.html#example_efm2", null ],
        [ "Example 3: Encode 2x H.264 streams from EFM buffer: Input from main buffer and third buffer", "d9/dc7/fs_adv_efm.html#example_efm3", null ],
        [ "Example 4: Encode H.264 stream from EFM buffer: YUV (NV12) file", "d9/dc7/fs_adv_efm.html#example_efm4", null ],
        [ "Example 5: Encode H.264 stream from EFM buffer with specified frame rate: YUV (NV12) file", "d9/dc7/fs_adv_efm.html#example_efm5", null ],
        [ "Example 6: Encode 4K H.264 stream from EFM buffer: Input from YUV (NV12) file", "d9/dc7/fs_adv_efm.html#example_efm7", null ],
        [ "Example 7: Encode H.265 stream from EFM buffer: Input from main buffer", "d9/dc7/fs_adv_efm.html#example_efm9", null ],
        [ "Example 8: Encode H.265 stream from EFM buffer: Input from YUV (NV12) file", "d9/dc7/fs_adv_efm.html#example_efm10", null ],
        [ "Example 9: Enter preview with virtual vinc_id, and Encode H.265 stream", "d9/dc7/fs_adv_efm.html#example_efm11", null ]
      ] ]
    ] ],
    [ "ADVANCED - Encode from RAW", "d3/dff/fs_adv_efr.html", [
      [ "1. Encode from RAW", "d3/dff/fs_adv_efr.html#efr_efr", null ],
      [ "2. EFR for Multi-VINs and Multiple Channels", "d3/dff/fs_adv_efr.html#efr_multi", null ],
      [ "3. Custom Virtual VIN Mode", "d3/dff/fs_adv_efr.html#custom_virtual_vin_mode", null ],
      [ "4. EFR Examples", "d3/dff/fs_adv_efr.html#efr_exp", [
        [ "Example 1: Encode from RGB RAW: Input from RGB (RAW) file to VIN with custom virtual VIN mode", "d3/dff/fs_adv_efr.html#example_efr1", null ],
        [ "Example 2: Encode from 12-bit packed RGB RAW: Input from RGB (RAW) file to VIN with custom virtual VIN mode", "d3/dff/fs_adv_efr.html#example_efr2", null ],
        [ "Example 3: Encode from compressed RGB RAW: Input from RGB (RAW) file to VIN with custom virtual VIN mode", "d3/dff/fs_adv_efr.html#example_efr3", null ],
        [ "Example 4: Encode from YUV NV16 RAW: YUV NV16 (RAW) to VIN", "d3/dff/fs_adv_efr.html#example_efr4", null ],
        [ "Example 5: Encode from YUV NV12 RAW: YUV NV12 (RAW) to VIN", "d3/dff/fs_adv_efr.html#example_efr5", null ],
        [ "Example 6: Encode from RGB RAW with multi-source: Two sources and two channels", "d3/dff/fs_adv_efr.html#example_efr6", null ],
        [ "Example 7: Encode from RGB RAW with multi-source: Four sources and four channels", "d3/dff/fs_adv_efr.html#example_efr7", null ],
        [ "Example 8: Encode from RGB RAW with multiple channels: One source and two channels", "d3/dff/fs_adv_efr.html#example_efr8", null ],
        [ "Example 9: One RAW encode and one physical sensor", "d3/dff/fs_adv_efr.html#example_efr9", null ],
        [ "Example 10: Encode from RGB RAW: Input from HDR 2X RGB (RAW) file to VIN with custom virtual VIN mode", "d3/dff/fs_adv_efr.html#example_efr10", null ],
        [ "Example 11: Encode from YUV NV12 RAW: Capture YUV(NV12) RAW from canvas then feed to EFR channel", "d3/dff/fs_adv_efr.html#example_efr11", null ]
      ] ]
    ] ],
    [ "ADVANCED - Pipeline Latency", "dc/d27/fs_adv_pl_latency.html", [
      [ "1. Image Digital Signal Processing (IDSP) Latency", "dc/d27/fs_adv_pl_latency.html#idsp_latency", [
        [ "1.1 Latency between VIN Capture Complete and IDSP YUV Output", "dc/d27/fs_adv_pl_latency.html#idsp_latency_live", null ],
        [ "1.2 Latency Between Feeding Raw Images and IDSP YUV Output", "dc/d27/fs_adv_pl_latency.html#idsp_latency_raw", null ],
        [ "1.3 Latency Between VIN Capture and VOUT Display", "dc/d27/fs_adv_pl_latency.html#capture_display_latency", null ]
      ] ],
      [ "2. Encode Latency", "dc/d27/fs_adv_pl_latency.html#enc_latency", [
        [ "2.1 Latency Between VIN Capture Completed and Encoding Completed", "dc/d27/fs_adv_pl_latency.html#latency_vin_cap_to_encoding_done", null ]
      ] ],
      [ "3. Video Pipeline Info Audit", "dc/d27/fs_adv_pl_latency.html#video_info_audit", [
        [ "3.1 DSP ISR Latency Audit", "dc/d27/fs_adv_pl_latency.html#isr_latency_aud", null ],
        [ "3.2 IDSP Latency Audit", "dc/d27/fs_adv_pl_latency.html#idsp_latency_aud", null ],
        [ "3.3 Encode Latency Audit", "dc/d27/fs_adv_pl_latency.html#encode_latency_aud", null ],
        [ "3.4 VOUT-VIN Latency Audit", "dc/d27/fs_adv_pl_latency.html#vout_vin_latency_aud", null ],
        [ "3.5 IDSP and Encode Frame Drop Audit", "dc/d27/fs_adv_pl_latency.html#frame_drop_aud", null ],
        [ "3.6 Encode Clock Audit", "dc/d27/fs_adv_pl_latency.html#enc_clk_aud", null ],
        [ "3.7 VOUT Drop and Osd Sync Audit", "dc/d27/fs_adv_pl_latency.html#vout_aud", null ],
        [ "3.8 Frame Sync (overaly and blur) Audit", "dc/d27/fs_adv_pl_latency.html#frame_sync_aud", null ],
        [ "Example 1: Full Report of IAV Audit Proc", "dc/d27/fs_adv_pl_latency.html#example_iav_audit_proc", null ],
        [ "Example 2: Application for Video Pipeline Information Audit", "dc/d27/fs_adv_pl_latency.html#example_show_video_audit_info", null ]
      ] ]
    ] ],
    [ "ADVANCED - Poll Interface", "d1/d67/fs_adv_iav_poll.html", [
      [ "1. Introduction to Poll", "d1/d67/fs_adv_iav_poll.html#iav_poll_intro", [
        [ "1.1 Poll Interface to Query IAV Data", "d1/d67/fs_adv_iav_poll.html#query_iav_data_intro", null ],
        [ "1.2 Poll Interface to Sync Irq", "d1/d67/fs_adv_iav_poll.html#irq_sync_intro", null ]
      ] ],
      [ "2. Examples of Using Poll Interface", "d1/d67/fs_adv_iav_poll.html#section_iav_poll_example", [
        [ "2.1 Examples of Querying IAV Data", "d1/d67/fs_adv_iav_poll.html#query_iav_data_example_intro", [
          [ "Example 2.1.1: Query Pyramid Data Using Poll", "d1/d67/fs_adv_iav_poll.html#example_iav_poll_data1", null ],
          [ "Example 2.1.2: Query Canvas Data Using Poll", "d1/d67/fs_adv_iav_poll.html#example_iav_poll_data2", null ],
          [ "Example 2.1.3: Query Raw Data Using Poll", "d1/d67/fs_adv_iav_poll.html#example_iav_poll_data3", null ],
          [ "Example 2.1.4: Query Frame Using Poll", "d1/d67/fs_adv_iav_poll.html#example_iav_poll_data4", null ],
          [ "Example 2.1.5: Query Statis Data Using Poll", "d1/d67/fs_adv_iav_poll.html#example_iav_poll_data5", null ],
          [ "Example 2.1.6: Query Y12 Using Poll", "d1/d67/fs_adv_iav_poll.html#example_iav_poll_data6", null ],
          [ "Example 2.1.7: Query Data with the Multi-User Using Poll", "d1/d67/fs_adv_iav_poll.html#example_iav_poll_data7", null ]
        ] ],
        [ "2.2 Examples of Using Interrupt Synchronization", "d1/d67/fs_adv_iav_poll.html#irq_sync_example_intro", [
          [ "Example 2.2.1: Vdsp irq sync", "d1/d67/fs_adv_iav_poll.html#example_vdsp_irq_sync", null ],
          [ "Example 2.2.2: Vcap Irq Sync", "d1/d67/fs_adv_iav_poll.html#example_vcap_irq_sync", null ],
          [ "Example 2.2.3: Venc Irq Sync", "d1/d67/fs_adv_iav_poll.html#example_venc_irq_sync", null ]
        ] ]
      ] ],
      [ "3. Poll Interface Usage", "d1/d67/fs_adv_iav_poll.html#section_poll_usage", [
        [ "3.1 Usage of Querying IAV Data", "d1/d67/fs_adv_iav_poll.html#poll_iav_data_usage", null ],
        [ "3.2 Usage of Interrupt Synchronization", "d1/d67/fs_adv_iav_poll.html#poll_irq_sync_usage", null ]
      ] ]
    ] ],
    [ "ADVANCED - Customized Features", "de/da3/fs_adv_customized_features.html", [
      [ "1. Capture Extra Raw Data", "de/da3/fs_adv_customized_features.html#capture_extra_raw", [
        [ "1.1 Extra Raw Data", "de/da3/fs_adv_customized_features.html#extra_raw_data", null ],
        [ "1.2 Extra Raw Data Capture Configuration", "de/da3/fs_adv_customized_features.html#extra_raw_configuration", null ],
        [ "1.3 Examples of Capturing Extra Raw Data", "de/da3/fs_adv_customized_features.html#extra_raw_example", null ]
      ] ]
    ] ],
    [ "ADVANCED - Bypass IDSP for YUV Input", "d3/d54/fs_adv_bypass_idsp_for_yuv_input.html", [
      [ "1. Bypass IDSP for YUV Input", "d3/d54/fs_adv_bypass_idsp_for_yuv_input.html#section_bypass_idsp_for_yuv_input", [
        [ "Example 1: IDSP Bypass Configurations", "d3/d54/fs_adv_bypass_idsp_for_yuv_input.html#example_bypass_idsp_for_yuv_input", null ]
      ] ]
    ] ],
    [ "IQ - Lite - NN", "d9/daa/iq_lite_nn.html", [
      [ "0. Revision History", "d9/daa/iq_lite_nn.html#iq_lite_nn_history", null ],
      [ "1. Lite NN Overview", "d9/daa/iq_lite_nn.html#iq_lite_nn_overview", null ],
      [ "2. Lite NN Usage", "d9/daa/iq_lite_nn.html#iq_lite_nn_usage", null ],
      [ "3. True Motion", "d9/daa/iq_lite_nn.html#iq_lite_nn_true_motion", [
        [ "3.1. Introduction", "d9/daa/iq_lite_nn.html#iq_lite_nn_true_motion_intro", null ],
        [ "3.2 ADJ Parameters", "d9/daa/iq_lite_nn.html#iq_lite_nn_true_motion_params", null ],
        [ "3.3 Invalid Parameters List", "d9/daa/iq_lite_nn.html#iq_lite_nn_true_motion_invalid_params", null ]
      ] ],
      [ "4. Vivid HDR", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_vivid_hdr", [
        [ "4.1 Introduction", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_vivid_hdr_intro", null ],
        [ "4.2 ADJ Parameters", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_vivid_hdr_params", null ]
      ] ],
      [ "5. Image NNCtrl Library API", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api", [
        [ "5.1 Introduction", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_intro", null ],
        [ "5.2 API Details", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_detail", [
          [ "5.2.1 Common APIs for AISP and Lite NN", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_detail_common", null ],
          [ "5.2.2 Unique APIs for AISP", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_detail_aisp", null ],
          [ "5.2.3 Unique API for Lite NN", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_detail_lite_nn", null ]
        ] ],
        [ "5.3 Computation Method of NR Strength and CE Strength", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_detail_compute_method", null ],
        [ "5.4 Example Usage", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_detail_example", [
          [ "5.4.1 Example on True Motion", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_detail_example_mdnn", null ],
          [ "5.4.2 Example on Vivid HDR", "d9/daa/iq_lite_nn.html#iq_lite_nnctrl_api_detail_example_tmnn", null ]
        ] ]
      ] ]
    ] ],
    [ "OTHER - Debug Option", "dd/d0d/fs_others_debug.html", [
      [ "1. Others:  Display Current Configuration", "dd/d0d/fs_others_debug.html#other_disp_cfg", [
        [ "Example 1: Chip", "dd/d0d/fs_others_debug.html#example_other_disp_cfg1", null ],
        [ "Example 2: Image Audio Video (IAV) Driver Version", "dd/d0d/fs_others_debug.html#example_other_disp_cfg2", null ],
        [ "Example 3: Dynamic Random-Access Memory (DRAM) Layout Information", "dd/d0d/fs_others_debug.html#example_other_disp_cfg3", null ],
        [ "Example 4: Encoding Resource Configuration", "dd/d0d/fs_others_debug.html#example_other_disp_cfg4", null ],
        [ "Example 5: Channel, Canvas, and Stream Resource Configuration", "dd/d0d/fs_others_debug.html#example_other_disp_cfg5", null ],
        [ "Example 6: Encode Configuration", "dd/d0d/fs_others_debug.html#example_other_disp_cfg6", null ],
        [ "Example 7: Stream Configuration", "dd/d0d/fs_others_debug.html#example_other_disp_cfg7", null ],
        [ "Example 8: Canvas State", "dd/d0d/fs_others_debug.html#example_other_disp_cfg8", null ],
        [ "Example 9: All Information", "dd/d0d/fs_others_debug.html#example_other_disp_cfg9", null ],
        [ "Example 10: Supported Feature Set", "dd/d0d/fs_others_debug.html#example_other_disp_cfg10", null ]
      ] ],
      [ "2. Others:  Display Pipeline Latency", "dd/d0d/fs_others_debug.html#other_disp_lat", [
        [ "Example 11: Pipeline Latency from Capture to Encode", "dd/d0d/fs_others_debug.html#example_other_disp_lat", null ]
      ] ],
      [ "3. Others: Debug Anonymous MMB", "dd/d0d/fs_others_debug.html#mmb_function", [
        [ "Example 16: Anonymous MMB Used in Father-and-Child Processes with the Same FD", "dd/d0d/fs_others_debug.html#example1_mmb_function", null ],
        [ "Example 17: Anonymous MMB Used in Father-and-Child Processes with Different FD", "dd/d0d/fs_others_debug.html#example2_mmb_function", null ],
        [ "Example 18: Anonymous MMB Used in Multiple Independent Processes", "dd/d0d/fs_others_debug.html#example3_mmb_function", null ]
      ] ],
      [ "4. Others: Debug Performance", "dd/d0d/fs_others_debug.html#perf_function", [
        [ "Example 19: Enable Optimal DSP Performance Mode", "dd/d0d/fs_others_debug.html#example1_perf_function", null ],
        [ "Example 20: Set HEVC Encode Mode", "dd/d0d/fs_others_debug.html#example1_hevc_mode", null ],
        [ "Example 21: AAA Statistics Display on Stream", "dd/d0d/fs_others_debug.html#example_aaa_overlay", null ]
      ] ]
    ] ],
    [ "OTHER - Miscellaneous", "d0/da8/fs_others_miscellaneous.html", [
      [ "1. Others:  RTSP Server", "d0/da8/fs_others_miscellaneous.html#rtsp_server", [
        [ "Example 1: RTSP server works as no authentication method", "d0/da8/fs_others_miscellaneous.html#example_rtsp1", null ],
        [ "Example 2: RTSP server works as basic authentication method", "d0/da8/fs_others_miscellaneous.html#example_rtsp2", null ],
        [ "Example 3: RTSP server works as digest authentication method", "d0/da8/fs_others_miscellaneous.html#example_rtsp3", null ]
      ] ]
    ] ],
    [ "OTHER - FAQ", "d5/d6e/fs_others_faq.html", [
      [ "1. Block Diagram of the Chip (Single VIN)", "d5/d6e/fs_others_faq.html#faq_block_diagram_of_the_chip", null ],
      [ "2. Max Encode Performance", "d5/d6e/fs_others_faq.html#faq_max_encode_performance", null ],
      [ "3. Obtain Video Data Efficiently", "d5/d6e/fs_others_faq.html#faq_obtain_video_data_efficiently", null ],
      [ "4. Synchronization between 3A and Encode", "d5/d6e/fs_others_faq.html#faq_synchronization_between_3a_and_encode", null ],
      [ "5. Magic Zoom", "d5/d6e/fs_others_faq.html#faq_magic_zoom", null ],
      [ "6. Data Dump", "d5/d6e/fs_others_faq.html#faq_data_dump", null ],
      [ "7. Two Types of PTS", "d5/d6e/fs_others_faq.html#faq_two_types_of_pts", null ],
      [ "8. Variable Bit Rate (VBR) and Constant Bit Rate (CBR)", "d5/d6e/fs_others_faq.html#faq_vbr_and_cbr", null ],
      [ "9. Dump YUV with / without overlay", "d5/d6e/fs_others_faq.html#faq_dump_yuv_with_without_osd", null ]
    ] ],
    [ "OTHER - DSP Monitor Service", "d7/df4/fs_others_dsp_monitor_service.html", [
      [ "1. DSP Monitor Service Features", "d7/df4/fs_others_dsp_monitor_service.html#section_dsp_monitor_service_features", [
        [ "1.1 DSP Monitor Service Sample Flow", "d7/df4/fs_others_dsp_monitor_service.html#dsp_monitor_service_sample_flow", null ]
      ] ]
    ] ],
    [ "OTHER - ucode for DSP", "d2/d51/fs_others_ucode.html", [
      [ "1. Dedicated ucode binaries for each chip part number", "d2/d51/fs_others_ucode.html#section_ucode", [
        [ "1.1 CV5x", "d2/d51/fs_others_ucode.html#dedicate_ucode_cv5x", null ],
        [ "1.2 CV72", "d2/d51/fs_others_ucode.html#dedicate_ucode_cv72", null ]
      ] ]
    ] ],
    [ "Modules", "modules.html", "modules" ],
    [ "Data Structures", "annotated.html", [
      [ "Data Structures", "annotated.html", "annotated_dup" ],
      [ "Data Fields", "functions.html", [
        [ "All", "functions.html", "functions_dup" ],
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
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"annotated.html",
"d1/df0/structencode__format__s.html#aab3eff270bf9ab4a121d69283b2276b2",
"d4/daa/vin__init_8c.html#a5f7e1ffb5a81753bc3d14e52a8826c4b",
"d5/d7d/structsect__config__slim__header__t.html#a1bac3eaf5ec72ae83059cda38a312592",
"d7/dac/structsource__buffer__cfg__s.html#a73990a5019c30cadc4a7b32b93864124",
"d8/d6e/structsystem__resource__setup__s.html#ad7a55d4448970358cb11075cb0c8071f",
"d9/d9a/test__stream_8h.html#ab5fefa6fc4abffdc4b912255ea537aaeaab63096b334741d46f4182ae110c927b",
"da/d30/stream__cfg_8c.html#afafb33646b186699e6d1581e6d8a17b7",
"dc/d79/group__tmc__parm.html#gac42c7158acb0e9ad5fd958434d91fb43",
"dd/ddb/test__frame__sync_8h.html#ab5fefa6fc4abffdc4b912255ea537aaea52009ddb03d83b84397bb847d9863876",
"de/de8/group__te__parm.html#ga06167b03542ae37fe675bbf550d6c4e1",
"de/de8/group__te__parm.html#gafbc28bae4f75fd1ca0efec1d3b840063"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';