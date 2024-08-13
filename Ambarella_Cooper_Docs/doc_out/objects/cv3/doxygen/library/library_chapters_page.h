/*!
 * @file doc_lib_gstreamer.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2022-08-08
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
 * @page page_lib_gstreamer_doc Amba GStreamer Solution
 *
 * @section gstreamer_doc_history 0. Revision History
 * <table>
 * <caption id="table_gstreamer_doc_history"></caption>
 * <tr><th> Updated Date          <th align="left"> Modification
 * <tr><td> 20230601              <td> Initial Version
 * <tr><td rowspan="2"> 20231018  <td> 1. Updated the element informations of NNStreamer @ref amba_cvflow_in_nns
 * <tr>                           <td> 2. Fixed some issues of AAC cmdlines, add multi-input NN cases  @ref amba_test_cases
 * <tr><td> 20240116              <td> Added some use cases in Lychee OS @ref use_in_lychee
 * <tr><td rowspan="2"> 20240118  <td> 1. Updated tensor_deocder information of NNStreamer @ref amba_cvflow_in_nns
 * <tr>                           <td> 2. Added prepared works on CV52 / CV72, fixed some issues of commandlines, and added RTSP cases @ref amba_test_cases
 * </table>
 *
 * - - - -
 *
 * @section introduction 1. Introduction
 *
 * This chapter introduces the GStreamer framework and
 * provides solutions based on GStreamer to manage multi-media, machine learning, and more on Ambarella platforms.<br>
 * The following shows an overall view of the connections among GStreamer, the GStreamer Daemon (GstD),
 * and third-party plugins such as NNStreamer, Amba Gst Plugins, and more. <br>
 * Along with the core and base elements, GStreamer provides a large collection of plugins that cover more functions.
 * Amba Gst Plugins, NNStreamer, and others can be added as GStreamer plugins. <br>
 * In the GStreamer Daemon, via TCP messages, users can create a GStreamer pipeline, then play, pause, change speed, skip around,
 * and change element parameter settings all while the pipeline is active. <br>
 *
 * @image html overall_diagram_of_amba_gstreamer.png "Figure 1-6. Overall Diagram of Amba GStreamer."
 * <br>
 * This chapter includes the following sections:
 *     - Section @ref gstreamer
 *     - Section @ref gstreamer_daemon
 *     - Section @ref nnstreamer
 *     - Section @ref amba_gstreamer_plugins
 *
 * @subsection gstreamer 1.1 GStreamer
 *
 * GStreamer is an open source multi-media framework (released under the LGPL) for constructing graphs of media-handling components.
 * The applications it supports range from simple Ogg / Vorbis playback,
 * audio / video streaming to complex audio (mixing) and video (non-linear editing) processing. <br>
 *
 * The following are the GStreamer core functions that provide a framework for plugins, data flow, and media type management / negotiation.
 * GStreamer also provides application programming interfaces (APIs) to write applications using the various plugins. <br>
 *
 * GStreamer provides the following:
 *
 *    - APIs for multi-media applications<br>
 *    - Plugin architecture <br>
 *    - Pipeline architecture <br>
 *    - Mechanism for media type management / negotiation<br>
 *    - Synchronization mechanism <br>
 *    - Over 250 plugins providing more than 1,000 elements <br>
 *    - A set of tools <br>
 *
 * The GStreamer framework is designed to facilitate writing applications that manage audio, video, or any type of data flow.
 * The framework is based on plugins that provide a variety of coders / decoders (codecs) and other functionalities.
 * The plugins can be linked and arranged in a pipeline that defines the flow of the data. <br>
 * GStreamer plugins can be classified as follows: <br>
 *
 *    - <b>Protocol management </b> <br>
 *    - <b>Sources:</b> for audio and video (includes protocol plugins) <br>
 *    - <b>Formats:</b> parsers, formaters, muxers, demuxers, metadata, and subtitles <br>
 *    - <b>Codecs:</b> coders and decoders <br>
 *    - <b>Filters:</b> converters, mixers, effects, and more <br>
 *    - <b>Sinks:</b> for audio and video (includes protocol plugins) <br>
 *
 * @image html gstreamer-overview.png "Figure 1-1. GStreamer Overview."
 * <br>
 *
 * GStreamer details can be found at the following official website link: <br>
 * https://gstreamer.freedesktop.org/ <br>
 *
 * @subsubsection gstreamer_history 1.1.1 Library Revision History
 *
 * <table>
 * <caption id="table_gstreamer_history">Table 1-1. History of GStreamer Library.</caption>
 * <tr><th> Library Version  <th> License  <th> Updated Date  <th> Modification
 * <tr><td> 1.20.5           <td> LGPL     <td> 20221219      <td> Initial Version
 * </table>
 *
 * @subsubsection gstreamer_core_library 1.1.2 GStreamer Core Library
 *
 * The core library `gstreamer` provides all core GStreamer services, including initialization, plugin management, and types,
 * as well as the object hierarchy that defines elements and bins, along with some more specialized elements.
 * Characteristics of the Gstreamer core are listed below: <br>
 *
 *    - Based on the GLib 2.0 object model for object-oriented design and inheritance <br>
 *    - Graph-based structure enables arbitrary pipeline construction, such as multi-threaded pipelines <br>
 *    - Clean, simple, and stable APIs for both plugin and application developers <br>
 *    - Complete debugging system for both core and plugin / application developers <br>
 *    - Extremely lightweight data passing for very high performance / low latency <br>
 *    - Clocking to ensure global inter-stream synchronization (audio / video sync) <br>
 *    - Quality of service (QoS) to ensure best possible quality under high CPU load <br>
 *
 * Details of these characteristics can be found at the following official website link: <br>
 * https://gstreamer.freedesktop.org/documentation/gstreamer/gi-index.html?gi-language=c <br>
 *
 * @subsubsection gstreamer_community_library 1.1.3 GStreamer Community Library
 *
 * The following are some community libraries in GStreamer: <br>
 *
 *    - <b>gst-plugins-base:</b> an essential exemplary set of elements <br>
 *    - <b>gst-plugins-good:</b> a set of good-quality plugins under LGPL <br>
 *    - <b>gst-plugins-ugly:</b> a set of good-quality plugins that may pose distribution problems <br>
 *    - <b>gst-plugins-bad:</b> a set of plugins that require better quality <br>
 *    - <b>gst-libav:</b> a set of plugins that wrap libav for decoding and encoding <br>
 *    - Other packages <br>
 *
 * <b>gst-plugins-base</b> <br>
 * This is a well-groomed and well-maintained collection of GStreamer plugins and elements that
 * cover a wide range of possible elements types. The library includes examples, documentation, and regression tests.
 * These are continuously kept up-to-date with any core changes during the development series. <br>
 *
 *
 * <b>gst-plugins-good</b> <br>
 * This is a collection of plugins that have good quality code, correct functionality, and a preferred license
 * (LGPL for the plugin code, LGPL or LGPL-compatible for the supporting library).
 * This is an excellent model that can be used as a basis for user-created plugins. <br>
 *
 * <b>gst-plugins-ugly</b> <br>
 * This is a collection of plugins that have good quality and correct functionality, but may pose problems during distribution.
 * The license on either the plugins or the supporting libraries may not reach Ambarella standards.
 * These plugins may have a patent noose around their neck, a lock-up license, or another issue. <br>
 *
 * <b>gst-plugins-bad</b> <br>
 * This is a collection of plugins that are not up to par, compared to the rest of the plugins. They may be close to good quality,
 * but are missing something - be it a good code review, some documentation, a set of tests, a live maintainer,
 * or some actual wide use. Though the plugins may appear useful, Ambarella does not recommend using this library. <br>
 *
 * <b>gst-libav</b> <br>
 * This is a collection of FFmpeg plugins. The details of the supported elements list for FFmpeg
 * can be found at the following official website link: <br>
 * https://gstreamer.freedesktop.org/documentation/libav/index.html?gi-language=c#plugin-libav <br>
 *
 * More tools, APIs, elements, and plugins that supported in these GStreamer libraries can be found in the following official document: <br>
 * https://gstreamer.freedesktop.org/documentation/?gi-language=c <br>
 *
 * @subsection gstreamer_daemon 1.2 GStreamer Daemon
 *
 * @subsubsection gstd_history 1.2.1 Library Revision History
 *
 * <table>
 * <caption id="table_gstd_history">Table 1-2. History of GstD Library.</caption>
 * <tr><th> Library Version  <th> License  <th> Updated Date  <th> Modification
 * <tr><td> 0.15.0           <td> LGPL2+   <td> 20220823      <td> Initial Version
 * </table>
 *
 * @subsubsection gstd_introduction 1.2.2 Introduction
 *
 * GstD is a GStreamer framework for controlling audio and video streaming using InterProcess Communication (IPC) protocol
 * (TCP messages).
 * Users can create a GStreamer pipeline, then play, pause, change speed, skip,
 * and change element parameter settings all while the pipeline is active in the GStreamer Daemon. <br>
 *
 * The GStreamer Daemon is designed for production deployment, where the control logic runs in a separate process from the audio-video streaming server.
 * Isolating the control logic from the streaming logic solves many difficult issues,
 * from setting priorities, to avoiding audio drop out, to supporting a functioning user interface if the streaming application encounters corrupt data.
 * Creating automated audio / video tests, extending a product's features to support remote control, and enabling the control application
 * streaming daemon can be developed independently and easily. <br>
 *
 * The GStreamer Daemon design follows a model-view-controller (MVC) architecture. <br>
 *
 *    - The GStreamer daemon provides the core and IPC endpoint <br>
 *    - The custom application provides view and client logic <br>
 *
 * @image html Gstd_mvc.png "Figure 1-2. GStreamer Daemon MVC Architecture."
 * <br>
 *
 * The GStreamer Daemon project packages the core, the commandline client, and the IPC interfaces.
 * The GstD core is a standalone process that is on top of the GStreamer framework.
 * GstdClient is a simple, commandline-based application that communicates via TCP with the GStreamer Daemon. This
 * application is ideal for rapid prototyping and for shell script automation.
 * GstdClient provides users with several active pipelines with the ability to control the pipeline and receive feedback once the pipeline has been created.
 *
 * @image html Gstd_layers.png "Figure 1-3. GstD Layer Diagram."
 * <br>
 *
 * Details on this topic can be found at the following official website link: <br>
 * https://developer.ridgerun.com/wiki/index.php/GStreamer_Daemon <br>
 *
 * @subsection nnstreamer 1.3 NNStreamer
 *
 * @subsubsection nns_history 1.3.1 Library Revision History
 *
 * <table>
 * <caption id="table_nns_history">Table 1-3. History of NNStreamer Library.</caption>
 * <tr><th> Library Version  <th> License  <th> Updated Date  <th> Modification
 * <tr><td> lts_2.0.1        <td> LGPL-2.1   <td> 20180614      <td> Initial Version
 * </table>
 *
 * @subsubsection nns_introduction 1.3.2 Introduction
 *
 * NNStreamer is a set of GStreamer plugins that provide easy methods to construct media streams
 * with neural network (NN) models using the de-facto-standard media stream framework, GStreamer. <br>
 *
 *    - <b>GStreamer users:</b> uses NN models as if they are yet another media filter <br>
 *    - <b>NN developers:</b> manages media streams easily and efficiently <br>
 *
 * NN framework connectivities (for example, TensorFlow, TensorFlow-lite, Caffe, Caffe2, PyTorch, OpenVINO, ArmNN, and NEURUN) were provided by
 * NNStreamer for GStreamer streams.
 *
 *    - <b>Efficient streaming for artificial intelligence (AI) projects:</b> applies efficient and flexible stream pipelines to neural networks <br>
 *    - <b>Intelligent media filters:</b> uses an NN model as a media filter / converter <br>
 *    - <b>Composite models:</b> multiple NN models in a single stream pipeline instance <br>
 *    - <b>Multi-modal intelligence:</b> multiple sources and stream paths for NN models <br>
 *
 * @image html nnstreamer_diagram.png "Figure 1-4. NNStreamer Diagram."
 * <br>
 *
 * The following elements are supported in NNstreamer:
 *
 *    - <b>tensor_converter:</b> converts video, audio, text, and more to the tensor frame wrapping format <br>
 *    - <b>tensor_filter:</b> NN framework filters, such as TensorFlow, TensorFlow-lite, Caffe2, ArmNN, and more <br>
 *    - <b>tensor_decoder:</b> post-processing, such as direct video conversion, image classification labeling, bounding boxes, image segmentation, body posing, and more <br>
 *    - <b>tensor_sink:</b> appsink-like element <br>
 *    - <b>tensor_source:</b> appsrc-like element <br>
 *
 * More details of supported elements can be found at the following official website link: <br>
 * https://github.com/nnstreamer/nnstreamer/tree/main/Documentation <br>
 * https://github.com/nnstreamer/nnstreamer/blob/main/Documentation/component-description.md <br>
 *
 *  @subsubsection amba_cvflow_in_nns 1.3.3 Ambarella CVflow® in NNStreamer
 *
 * The Ambarella CVflow framework provides functions for running neural network models.
 * CVflow, as well as a pipeline neural network filter, can be added to NNstreamer. <br>
 *
 *    - <b>tensor_converter:</b> adds support for more video formats to convert to tensor format <br>
 *    - <b>tensor_filter:</b> adds the sub-plugin filter `amba_cvflow` to run NN models <br>
 *    - <b>tensor_decoder:</b> adds YOLOv5 / tiny YOLOv3 / YOLOP post-processing examples in `tensordec-boundingbox` <br>
 *
 * @image html diagram_of_nnstreamer_sub_plugin.png "Figure 1-5. NNStreamer Sub-Plugin Diagram."
 * <br>
 *
 * <b>tensor_converter</b> <br>
 *
 * For more efficient calculation, Amba CNNGen always treats the input as if it were NCHW format,
 * even though TensorFlow is typically in NHWC format.
 * To reduce unnecessary storage format conversions (NHWC -> NCHW), add support for RGBP / BGRP / NV12 video formats in `tensor_convert`.
 * The following is the list of supported video formats in `tensor_convert`. <br>
 *
 * <table>
 * <caption id="table_video_fmt_in_tensor_convert">Table 1-4. Supported Video Formats in tensor_convert.</caption>
 * <tr><th> GstVideoFormat  <th> Tensor Dimensions <th> Storage Format
 * <tr><td> GRAY8           <td> 0:1,1:W,2:H,3:1   <td> NHWC
 * <tr><td> RGB             <td> 0:3,1:W,2:H,3:1   <td> NHWC
 * <tr><td> BGR             <td> 0:3,1:W,2:H,3:1   <td> NHWC
 * <tr><td> RGBx            <td> 0:4,1:W,2:H,3:1   <td> NHWC
 * <tr><td> BGRx            <td> 0:4,1:W,2:H,3:1   <td> NHWC
 * <tr><td> xRGB            <td> 0:4,1:W,2:H,3:1   <td> NHWC
 * <tr><td> xBGR            <td> 0:4,1:W,2:H,3:1   <td> NHWC
 * <tr><td> RGBA            <td> 0:4,1:W,2:H,3:1   <td> NHWC
 * <tr><td> BGRA            <td> 0:4,1:W,2:H,3:1   <td> NHWC
 * <tr><td> ARGB            <td> 0:4,1:W,2:H,3:1   <td> NHWC
 * <tr><td> ABGR            <td> 0:4,1:W,2:H,3:1   <td> NHWC
 * <tr><td> RGBP            <td> 0:W,1:H,2:3,3:1   <td> NCHW
 * <tr><td> BGRP            <td> 0:W,1:H,2:3,3:1   <td> NCHW
 * <tr><td> NV12            <td> 0:W,1:H,2:2,3:1   <td> NCHW
 * </table>
 *
 * <b>tensor_filter </b> <br>
 *
 * The `amba_cvflow` framework in `tensor_filter` provides pre-processing methods to facilitate running NNs with CVflow.
 * Vproc can convert YUV to RGBP / BGRP, perform resize, crop, and scale funcions, and more. Note that for some vector operations such as
 * converting color space from interleaved to planar distribution, resizing would take the data format as (0, 0, 0, 0).
 *
 * The following was the list of supported pre-processing features in `amba_cvflow`. <br>
 *
 * <table>
 * <caption id="table_pre_process_in_amba_cvflow">Table 1-5. Supported Pre-Processing Features in amba_cvflow.</caption>
 * <tr><th> Pre-Process            <th> Supported Features                           <th> Description
 * <tr><td> Color space conversion <td> RGB -> RGBP, BGR -> RGBP, BGRP -> RGBP, NV12 -> RGBP <td> Uses Vproc APIs and some C code to implement it
 * <tr><td> Resize, crop           <td> VECTOR, RGBP, BGRP, NV12                     <td> Vproc only supports resize+crop vectors with planer+FX8 format; adds simple C implementation for interleaved / float32 data (not recommended)
 * <tr><td> Scale                  <td> FX8 / FP32 -> FX8 / FP32                           <td> Uses Vproc APIs convert data type to fixed 8-bit, floating 32-bit
 * </table>
 *
 * The following lists added properties in the sub-plugin `amba_cvflow` of `tensor_filter`.
 * Note that the values of `in_name`, `in_data_fmt`, `ROI`, `in_cs`, and `nn_cs` must be equal to
 * the NN input values, and the `out_name` value must be equal to the NN output value. <br>
 *
 * <table>
 * <caption id="table_property_in_amba_cvflow">Table 1-6. Properties in amba_cvflow.</caption>
 * <tr><th> Property  <th> Type    <th> Default                       <th> Description
 * <tr><td> in_name     <td> String  <td> NULL+...                      <td> Required; specifies NN input names
 * <tr><td> out_name    <td> String  <td> NULL+...                      <td> Required; specifies NN output names
 * <tr><td> in_data_fmt <td> String  <td> uint8:0.0.8.0 float32:1.2.0.7 <td> Specifies data formats [sign.datasize.exp_offset.exp_bits] of input tensors; if not set, decided by tensor types
 * <tr><td> roi         <td> String  <td> 0.0.0.0+...                   <td> Specifies the ROIs [xoffset.yoffset.width.height] of input tensors
 * <tr><td> in_cs       <td> String  <td> NULL+...                      <td> Specifies the color spaces of input tensorsl if not set, decided by the video format of tensors
 * <tr><td> nn_cs       <td> String  <td> rgbp+...                      <td> Specifies the color spaces of NN input feature maps
 * <tr><td> nn_out_f32  <td> Integer <td> 0                             <td> Coerces the data format of NN outputs to FP32
 * <tr><td> type        <td> String  <td> NULL                          <td> If post-processing in tensor_filter is required, specify the NN model type
 * <tr><td> label       <td> String  <td> NULL                          <td> If post-processing in tensor_filter is required, specify the label file path
 * <tr><td> f           <td> Float   <td> 0.2                           <td> If post-processing in tensor_filter is required, specify conf_threshold
 * <tr><td> nms         <td> Float   <td> 0.3                           <td> If post-processing in tensor_filter is required, specify nms_threshold
 * <tr><td> top_k       <td> Integer <td> 200                           <td> If post-processing in tensor_filter is required, specify top_k
 * <tr><td> u           <td> Integer <td> 0                             <td> If post-processing in tensor_filter is required, specify use_multi_cls
 * </table>
 *
 * The following lists the supported color spaces in `amba_cvflow`. <br>
 *
 * <table>
 * <caption id="table_cs_in_amba_cvflow">Table 1-7. Supported Color Spaces in amba_cvflow.</caption>
 * <tr><th> Amba Color Space  <th> GstVideoFormat           <th> Command Line String  <th> Description
 * <tr><td> CS_VECT           <td> GST_VIDEO_FORMAT_UNKNOWN <td> vector               <td> General vector
 * <tr><td> CS_RGB            <td> GST_VIDEO_FORMAT_RGBP    <td> rgbp                 <td> Planar RGB data
 * <tr><td> CS_BGR            <td> GST_VIDEO_FORMAT_BGRP    <td> bgrp                 <td> Planar BGR data
 * <tr><td> CS_RGB_ITL        <td> GST_VIDEO_FORMAT_RGB     <td> rgb                  <td> Element-interleaved RGB data
 * <tr><td> CS_BGR_ITL        <td> GST_VIDEO_FORMAT_BGR     <td> bgr                  <td> Element-interleaved BGR data
 * <tr><td> CS_NV12           <td> GST_VIDEO_FORMAT_NV12    <td> nv12                 <td> YUV NV12 format data
 * </table>
 *
 * The CVflow `data_format` parameter defines the signedness, element size, and precision for each vector, which is as follows: <br>
 * - <b>First argument:</b> specifies signed / unsigned; 0 is unsigned, 1 is signed<br>
 * - <b>Second argument:</b> specifies the width of the data elements (0 = 8-bit, 1 = 16-bit, and 2 = 32-bit).<br>
 * - <b>Third argument:</b> specifies the exponent offset <br>
 *  - Fixed-point, shifts the binary point to the right by `expoffset`; maximum range is [0, 15] <br>
 *  - Float-point, applies a signed binary complement offset to the exponent; maximum range is [-8, 7] <br>
 * - <b>Fourth argument:</b> specifies the value to determine the number of bits reserved in a data element for the exponent field; maximum value is 7 <br>
 *  - A value of 0 indicates fixed-point numbers
 *  - If the value is greater than 0, the number of exponent bits is (expbits + 1); 4 means FP16, 7 means FP32
 *  - Integer format is supported as a special case of fixed-point numbers where the `expoffset` and `expbits` fields are both 0
 *
 * For example: <br>
 * @code {.c}
 * ufix8_8 (0,0,8,0)  =>  [0,2^(8-0)/2^8 )=[0,1)
 * sfix8_8 (1,0,8,0)  =>  [-2^(8-1)/2^8 ,2^(8-1)/2^8 )=[-0.5,0.5)
 * sfix16_5 (1,1,5,0) =>  [-2^(16-1)/2^5 ,2^(16-1)/2^5 )=[-1024,1024)
 * @endcode
 *
 * Refer to the CNNGen document <em>Ambarella CV2x CNNGen Simple Introduction Customer</em> for more information. <br>
 *
 * @note
 * - The output is always set to FP32 / FP16. FP32 should be [1, 2, 0, 7]; FP16 (equal with FP16 defined in IEEE-754) should be [1, 1, 0 ,4].
 * - For the input, the `amba_cvflow` framework has added support for 8- / 32-bit data format. The 16-bit data format is not supported.
 *
 * <b>tensor_decoder </b> <br>
 *
 * The `bounding_boxes` is a sub-plugin of `tensor_decoder` that provides post-processing methods for some NNs such as mobilenet-ssd and
 * converts tensors to video stream (RGBA) with boxes on transparent background. <br>
 *
 * The following lists the properties in the sub-plugin `bounding_boxes`.
 * Note that the input dimension of option5 should be equal to the input resolution of NN model. <br>
 *
 * <table>
 * <caption id="table_property_in_bounding_boxes">Table 1-8. Properties in bounding_boxes.</caption>
 * <tr><th> Property    <th> Type    <th> Default  <th> Description
 * <tr><td> option1     <td> String  <td> NULL     <td> Required; specifies decoder mode
 * <tr><td> option2     <td> String  <td> NULL     <td> Required; specifies the path of label file
 * <tr><td> option3     <td> String  <td> NULL     <td> Any option1-dependent values, more details in the official document
 * <tr><td> option4     <td> String  <td> NULL     <td> Video Output Dimension (WIDTH:HEIGHT)
 * <tr><td> option5     <td> String  <td> NULL     <td> Input Dimension (WIDTH:HEIGHT), decided by the resolution of NN input
 * </table>
 *
 *
 * The following lists the supported decoder mode of bounding box.
 * Three demos `amba_yolov5`, `amba_tiny_yolov3`, and `amba_yolop` were added for postprocess with NN outputs from `amba_cvflow`. <br>
 *
 * <table>
 * <caption id="table_decoder_mode_in_bounding_boxes">Table 1-9. Supported Decoder Mode in bounding_boxes.</caption>
 * <tr><th> Decoder Mode
 * <tr><td> mobilenet-ssd
 * <tr><td> mobilenet-ssd-postprocess
 * <tr><td> ov-person-detection
 * <tr><td> ov-face-detection
 * <tr><td> mp-palm-detection
 * <tr><td> yolov5
 * <tr><td> amba_yolov5
 * <tr><td> amba_tiny_yolov3
 * <tr><td> amba_yolop
 * </table>
 *
 * In option3, add some parameter settings for postprocess with yolov5 / tiny yolov3 / yolop. <br>
 * <table>
 * <caption id="table_property_for_yolo">Table 1-10. Properties for Yolo.</caption>
 * <tr><th> Property    <th> Type    <th> Default  <th> Description
 * <tr><td> f           <td> Float   <td> 0.3      <td> Specifies conf_threshold
 * <tr><td> nms         <td> Float   <td> 0.6      <td> Specifies nms_threshold
 * <tr><td> top_k       <td> Integer <td> 100      <td> Specifies top_k
 * <tr><td> u           <td> Integer <td> 0        <td> Specifies use_multi_class
 * </table>
 *
 * To get the post-process results such as bounding boxes informations, add a new sub-plugin `bounding_boxes_ori` which was modified from `bounding_boxes` to transfer
 * NN results directly to the next without drawing on video.
 * The difference between them was the output encapsulation format. The NN results were stored in tensors without converting to the video.<br>
 *
 * @subsection amba_gstreamer_plugins 1.4 Amba GStreamer Plugins
 *
 * This is a set of GStreamer plugins that provide multi-media and machine-learning-related processing on Ambarella platforms. <br>
 *
 * @subsubsection amba_gst_plugin_history 1.4.1 Library Revision History
 *
 * <table>
 * <caption id="table_amba_gst_plugin_history">Table 1-11. History of Amba Gst Plugin Library.</caption>
 * <tr><th> Library Version <th> License     <th> Updated Date     <th> Modification
 * <tr><td> 1.2.1           <td> LGPL-2.1    <td> 20230524         <td> Initial Version
 * </table>
 *
 * @subsubsection amba_gst_plugin_element 1.4.2 List of Supported Elements
 * <table>
 * <caption id="table_element_in_amba_gst_plugin">Table 1-12. Supported Elements in Amba Gst Plugin.</caption>
 * <tr><th> Element Name      <th> Supported Since Package Version <th> Description
 * <tr><td> amba_camsrc       <td> 1.2.1                           <td> Camera source; outputs YUV frames
 * <tr><td> amba_hwvdec       <td> 1.2.1                           <td> Hardware video decoder
 * <tr><td> amba_venccap      <td> 1.2.1                           <td> Video encoder: capture
 * <tr><td> amba_vencdemux    <td> 1.2.1                           <td> Video encoder: demux
 * <tr><td> amba_venc_overlay <td> 1.2.1                           <td> Video encoder: overlay
 * <tr><td> mlinference       <td> 1.2.1                           <td> Machine learning inference
 * <tr><td> amba_heicfilesink <td> 1.2.1                           <td> High-efficiency image container (HEIC) file sink
 * <tr><td> amba_vsink        <td> 1.2.1                           <td> Video sink; do nothing
 * </table>
 *
 * @subsubsection element_amba_camsrc 1.4.3 amba_camsrc
 *
 * This element is used to capture YUV frames from the Ambarella camera source. <br>
 *
 * <b>Pad Templates </b> <br>
 *
 * @code {.c}
 * SRC template: 'src'
 *     Availability: Always
 *     Capabilities:
 *         video/x-raw
 *             format: NV12
 *             width: [ 1, 2147483647 ]
 *             height: [ 1, 2147483647 ]
 *             framerate: [ 0/1, 2147483647/1 ]
 * @endcode
 *
 *
 * <b>Properties </b> <br>
 *
 * <table>
 * <caption id="table_property_in_amba_camsrc">Table 1-13. Properties in amba_camsrc.</caption>
 * <tr><th> Property  <th> Type              <th> Default   <th> Description
 * <tr><td> buf-id      <td> Unsigned integer  <td> 0         <td> Specifies the canvas source buffer ID
 * <tr><td> gdma        <td> Unsigned integer  <td> 1         <td> Enables graphics direct memory access (GDMA) copy
 * <tr><td> dump        <td> String            <td> NULL      <td> Dumped file name
 * </table>
 *
 * @subsubsection element_amba_hwvdec 1.4.4 amba_hwvdec
 *
 * This element is used for the Ambarella hardware video decoder. <br>
 *
 * <b>Pad Templates </b> <br>
 *
 * @code {.c}
 *   SINK template: 'sink'
 *     Availability: Always
 *     Capabilities:
 *       video/x-h264
 *           stream-format: { (string)byte-stream, (string)avc, (string)avc3 }
 *               alignment: { (string)nal }
 *       video/x-h265
 *           stream-format: { (string)byte-stream, (string)hvc1, (string)hev1 }
 *               alignment: { (string)nal }
 *
 *   SRC template: 'src'
 *     Availability: Always
 *     Capabilities:
 *       video/x-raw
 *                 format: I420
 *                  width: [ 1, 2147483647 ]
 *                 height: [ 1, 2147483647 ]
 *              framerate: [ 0/1, 2147483647/1 ]
 *
 * @endcode
 *
 *
 * <b>Properties </b> <br>
 *
 * <table>
 * <caption id="table_property_in_amba_hwvdec">Table 1-14. Properties in amba_hwvdec.</caption>
 * <tr><th> Property           <th> Type              <th> Default   <th> Description
 * <tr><td> vout-number          <td> Unsigned char     <td> 1         <td> Specifies the video output (VOUT) number
 * <tr><td> decoder-number       <td> Unsigned char     <td> 1         <td> Specifies the decoder number
 * <tr><td> decoder-id           <td> Unsigned char     <td> 0         <td> Sets up the decoder ID
 * <tr><td> decoder-config-id    <td> Unsigned char     <td> 0         <td> Provides the decoder ID to be configured
 * <tr><td> vout-id              <td> Unsigned char     <td> 0         <td> Sets up VOUT ID
 * <tr><td> vout-config-id       <td> Unsigned char     <td> 0         <td> Provides the VOUT ID to be configured
 * <tr><td> enable-vout          <td> Unsigned char     <td> 1         <td> Enables VOUT for the configured decoder
 * <tr><td> enable-pb-pyramid    <td> Unsigned char     <td> 0         <td> Enables PB pyramid for the configured decoder
 * <tr><td> enable-hevc-per-tile <td> Unsigned char     <td> 0         <td> Enables high-efficiency video coding (HEVC) per tile
 * <tr><td> hevc-tile-num        <td> Unsigned char     <td> 3         <td> Sets up HEVC tile number
 * <tr><td> vout-mode            <td> String            <td> NULL      <td> Sets up VOUT mode for the configured decoder
 * <tr><td> vout-sink-type       <td> String            <td> NULL      <td> Sets up VOUT sink type for the configured decoder
 * <tr><td> vout-device          <td> String            <td> NULL      <td> Sets up VOUT device for the configured decoder
 * <tr><td> enable-vout-digital  <td> Unsigned char     <td> 0         <td> Enables VOUT digital for the configured decoder
 * <tr><td> enable-vout-hdmi     <td> Unsigned char     <td> 0         <td> Enables the VOUT high-definition multimedia interface (HDMIÂ®) for the configured decoder
 * <tr><td> enable-vout-cvbs     <td> Unsigned char     <td> 0         <td> Enables VOUT composite video with blanking and sync (CVBS) for the configured decoder
 * <tr><td> cap-max-codec-height <td> Unsigned int      <td> 480       <td> Caps the maximum codec height for the configured decoder
 * <tr><td> cap-max-codec-width  <td> Unsigned int      <td> 720       <td> Caps the maximum codec width for the configured decoder
 * <tr><td> max-gop-size         <td> Unsigned char     <td> 0         <td> Sets up the maximum group of pictures (GOP) size
 * <tr><td> cur-gop-size         <td> Unsigned char     <td> 0         <td> Sets up the current GOP size
 * <tr><td> codec-format         <td> Unsigned int      <td> 0x01      <td> Sets up the codec format for the configured decoder
 * <tr><td> frame-rate-num       <td> Unsigned int      <td> 0         <td> Frame rate number
 * <tr><td> frame-rate-den       <td> Unsigned int      <td> 0         <td> Frame rate den
 * <tr><td> add-gop-header       <td> Unsigned char     <td> 0         <td> Adds a GOP header
 * <tr><td> stream-format        <td> String            <td> "h264"    <td> the stream format
 * </table>
 *
 * @subsubsection element_amba_venccap 1.4.5 amba_venccap
 *
 * This element is used to capture streams from the Ambarella video encoder. <br>
 *
 * <b>Pad Templates </b> <br>
 *
 * @code {.c}
 *   SRC template: 'src'
 *     Availability: Always
 *     Capabilities:
 *       video/x-h264
 *           stream-format: { (string)byte-stream, (string)avc, (string)avc3 }
 *               framerate: [ 0/1, 2147483647/1 ]
 *               alignment: { (string)nal }
 *       video/x-h265
 *           stream-format: { (string)byte-stream, (string)hvc1, (string)hev1 }
 *               framerate: [ 0/1, 2147483647/1 ]nal }
 *               alignment: { (string)nal }
 * @endcode
 *
 *
 * <b>Properties </b> <br>
 *
 * <table>
 * <caption id="table_property_in_amba_venccap">Table 1-15. Properties in amba_venccap.</caption>
 * <tr><th> Property        <th> Type              <th> Default       <th> Description
 * <tr><td> enc               <td> String            <td> "stream_id:0" <td> Encoding setting
 * <tr><td> alloc_mem         <td> Unsigned int      <td> 0             <td> Allocates memory for the output buffer
 * <tr><td> sync              <td> Boolean           <td> true          <td> Synchronizes to the pipeline clock
 * </table>
 *
 * @subsubsection element_amba_vencdemux 1.4.6 amba_vencdemux
 *
 * This element is used to demux streams from the Ambarella video encoder. <br>
 *
 * <b>Pad Templates </b> <br>
 *
 * @code {.c}
 * SINK template: 'sink'
 *   Availability: Always
 *   Capabilities:
 *     ANY
 *
 * SRC template: 'stream_%u'
 *   Availability: Sometimes
 *   Capabilities:
 *     ANY
 * @endcode
 *
 * <b>Properties </b> <br>
 *
 * <table>
 * <caption id="table_property_in_amba_vencdemux">Table 1-16. Properties in amba_vencdemux.</caption>
 * <tr><th> Property            <th> Type      <th> Default   <th> Description
 * <tr><td> filename-base         <td> String    <td> NULL      <td> Locations of the file to write
 * <tr><td> heic-capture-id       <td> String    <td> "-1"      <td> Captured HEIC stream indexes
 * <tr><td> heic-capture-close-id <td> String    <td> "-1"      <td> Close-captured HEIC stream index
 * </table>
 *
 * @subsubsection element_amba_venc_overlay 1.4.7 amba_venc_overlay
 *
 * This element is used to draw a bounding box on the overlay for video stream encoding. <br>
 *
 * <b>Pad Templates </b> <br>
 *
 * @code {.c}
 * SINK template: 'sink'
 *   Availability: Always
 *   Capabilities:
 *     video/x-raw
 *             format: GST_VIDEO_FORMATS_ALL
 *             width: [ 1, 2147483647 ]
 *             height: [ 1, 2147483647 ]
 *         framerate: [ 0/1, 2147483647/1 ]
 * @endcode
 *
 *
 * <b>Properties </b> <br>
 *
 * <table>
 * <caption id="table_property_in_amba_venc_overlay">Table 1-17. Properties in amba_venc_overlay.</caption>
 * <tr><th> Property    <th> Type     <th> Default         <th> Description
 * <tr><td> stream_id     <td> Unsigned int <td> 0           <td> Provides the stream ID
 * <tr><td> roi           <td> String       <td> NULL        <td> Sets up input ROIs
 * <tr><td> color_number  <td> Unsigned int <td> 360         <td> Sets up the color number
 * <tr><td> clut_start    <td> Unsigned int <td> 0           <td> Sets up the color lookup table (CLUT) start
 * <tr><td> clut_end      <td> Unsigned int <td> 127         <td> Sets up the CLUT end
 * <tr><td> clut_ratio    <td> Unsigned int <td> 1           <td> Sets up the CLUT ratio
 * <tr><td> buf_num       <td> Unsigned int <td> 4           <td> Sets up the buffer number
 * <tr><td> alpha         <td> Unsigned int <td> 128         <td> Sets up alpha
 * <tr><td> score_lmt     <td> Float        <td> 0.7         <td> Sets up the box's score limit
 * <tr><td> cal_center_w  <td> Unsigned int <td> 10          <td> Sets up the calibration center width
 * <tr><td> cal_center_h  <td> Unsigned int <td> 10          <td> Sets up the calibration center height
 * <tr><td> font          <td> String       <td> "arial.ttf" <td> Sets up the font `*.ttf` file
 * </table>
 *
 * @subsubsection element_amba_mlinference 1.4.8 mlinference
 *
 * This element is used for machine learning inference with Ambarella CVflow. <br>
 *
 * <b>Pad Templates </b> <br>
 *
 * @code {.c}
 * SINK template: 'sink'
 *     Availability: Always
 *     Capabilities:
 *       video/x-raw
 *                   format: { (string)RGBP, (string)NV12, (string)RGB, (string)RGBP, (string)BGR, (string)BGRP }
 *     Capabilities:
 *       video/x-raw
 *                   format: { (string)RGBP, (string)NV12, (string)RGB, (string)RGBP, (string)BGR, (string)BGRP }
 *                    width: [ 1, 2147483647 ]
 *                   height: [ 1, 2147483647 ]
 *                framerate: [ 0/1, 2147483647/1 ]
 *
 * SRC template: 'src'
 *     Availability: Always
 *     Capabilities:
 *       video/x-raw
 *                   format: { (string)RGBP, (string)NV12, (string)RGB, (string)BGR, (string)BGRP }
 *                    width: [ 1, 2147483647 ]
 *                   height: [ 1, 2147483647 ]
 *                framerate: [ 0/1, 2147483647/1 ]
 * @endcode
 *
 *
 * <b>Properties </b> <br>
 *
 * <table>
 * <caption id="table_property_in_mlinference">Table 1-18. Properties in mlinference.</caption>
 * <tr><th> Property        <th> Type      <th> Default   <th> Description
 * <tr><td> in_name           <td> String    <td> NULL      <td> Required; provides NN input features' name
 * <tr><td> out_name          <td> String    <td> NULL      <td> Required; provides NN output features's name
 * <tr><td> label             <td> String    <td> NULL      <td> Provides label file name if post-processing is required
 * <tr><td> dump              <td> String    <td> NULL      <td> Sets up a dumped file name if dumping NN outputs is required
 * <tr><td> model             <td> String    <td> NULL      <td> Required; provides a model file name
 * <tr><td> type              <td> String    <td> NULL      <td> Provides a model type if required to enable post-processing
 * <tr><td> conf_threshold    <td> Float     <td> 0.2       <td> Sets up a conf threshold for post-processing
 * <tr><td> nms               <td> Float     <td> 0.5       <td> Sets up an NMS threshold for post-processing
 * <tr><td> top_k             <td> Int       <td> 100       <td> Sets up a top K for post-processing
 * <tr><td> use_multi_cls     <td> Int       <td> 0         <td> Uses multiple classes for post-processing
 * <tr><td> color_space       <td> String    <td> "rgb"     <td> Provides input feature color space of the model, if not planar RGB
 * <tr><td> roi               <td> String    <td> NULL      <td> Sets up ROI of inputs, if required
 * </table>
 *
 * @subsubsection element_amba_heicfilesink 1.4.9 amba_heicfilesink
 *
 * This element is used to dump HEIC files. <br>
 *
 * <b>Pad Templates </b> <br>
 *
 * @code {.c}
 *   SINK template: 'sink'
 *     Availability: Always
 *     Capabilities:
 *       ANY
 * @endcode
 *
 * <b>Properties </b> <br>
 *
 * <table>
 * <caption id="table_property_in_amba_heicfilesink">Table 1-19. Properties in amba_heicfilesink.</caption>
 * <tr><th> Property        <th> Type      <th> Default   <th> Description
 * <tr><td> filename-base     <td> String    <td> NULL      <td> Specifies the dumped HEIC file name
 * </table>
 *
 * @subsubsection element_amba_vsink 1.4.10 amba_vsink
 *
 * This element functions as a black hole that absorbs video data, similar to `fakesink` in GStreamer, which discards unwanted data. <br>
 *
 * <b>Pad Templates </b> <br>
 *
 * @code {.c}
 * SINK template: 'sink'
 *   Availability: Always
 *   Capabilities:
 *     video/x-raw(ANY)
 *     format: GST_VIDEO_FORMATS_ALL
 * @endcode
 *
 * - - - -
 *
 * @section gstreamer_user_guide 2. User Guide
 * This chapter provides demonstrates how to compile GStreamer-related libraries
 * on Ambarella platforms, how to run and debug GStreamer on the board,
 * and provides test cases for typical scenarios such as recording, playing, machine learning, and more. <br>
 *
 * This chapter includes the following sections:
 *     - Section @ref compilation
 *     - Section @ref command_line_tools
 *     - Section @ref debug
 *     - Section @ref amba_test_cases
 *
 * @subsection compilation 2.1 Compilation
 *
 * Confirm that all GStreamer-related options are selected under menuconfig. <br>
 *
 * @code {.c}
 * $ cd $(SDK)/ambarella
 * # recommend to compile Gstreamer with yocto-build
 * # for example on cv22
 * $ source build/env/yocto-build.env cv22_walnut
 * # There're some config files for Gstreamer test which named `*_gst_config`
 * $ make ipcam_gst_config
 * # select ambarella gstreamer plugin, nnstreamer, gstd and so in menuconfig
 * $ make menuconfig
 *   -> meta-ambalib
 *     -> recipes-ambagstreamer
 *       -> libgstamba
 *         -> Build Ambarella GStreamer Plugin
 *       -> libgstnnstreamer
 *
 *     -> recipes-video
 *       -> liblwmedia (meta-ambalib/recipes-video/liblwmedia)
 *         -> Build lw_media unit test
 * $ make -j16
 * @endcode
 *
 * @subsection command_line_tools 2.2 Command Line Tools
 *
 * GStreamer includes several commandline tools to help developers prototype their applications. <br>
 * This section includes the following sub-sections:
 *     - Section @ref gst_inspect_x
 *     - Section @ref gst_launch_x
 *     - Section @ref gstd_cmdline
 *
 * @subsubsection gst_inspect_x 2.2.1 gst-inspect-1.0
 *
 * The `gst-inspect-1.0` tool prints information on available GStreamer plugins
 * regarding a particular plugin or a particular element. <br>
 *
 * Ambarella recommends creating a checkout on the board at the first instance to verify that all user-required plugins exist. <br>
 *
 * <b>Options </b> <br>
 *
 * There are two common modes of operation. When executed without arguments, `gst-inspect-1.0` prints a list of all plugins and elements in GStreamer.
 * When executed with a <b>PLUGIN</b> or an <b>ELEMENT</b> argument, `gst-inspect-1.0` prints information about that plugin or element. <br>
 *
 *    - <b>No argument:</b> prints a list of all plugins and elements together with a summary <br>
 *    - <b>PLUGIN:</b> the plugin name <br>
 *    - <b>ELEMENT:</b> the element name <br>
 *    - <b>FILENAME:</b> specifies a file as a GStreamer plugin and prints the list of elements in this plugin <br>
 *    - <b>-h, --help:</b> prints a help synopsis and available FLAGS <br>
 *    - <b>--help-all:</b> prints all help options <br>
 *    - <b>--help-gst:</b> prints GStreamer options <br>
 *    - <b>-a, --print-all:</b> prints all plugins and elements <br>
 *    - <b>-b, --print-blacklist:</b> prints a list of blacklisted files <br>
 *    - <b>--print-plugin-auto-install-info:</b> prints a machine-parsable list of features that the specified plugin provides <br>
 *    - <b>--gst-info-mask=FLAGS:</b> sets GStreamer information flags (list with --help) <br>
 *    - <b>--gst-debug-mask=FLAGS:</b> sets GStreamer debugging flags (list with --help) <br>
 *    - <b>--gst-mask=FLAGS:</b> sets GStreamer information and debugging flags (list with --help) <br>
 *    - <b>--gst-plugin-spew:</b> sets GStreamer information flags to enable printout of errors while loading GStreamer plugins <br>
 *    - <b>--gst-plugin-path=PATH:</b> adds directories separated with `:` to the plugin search path <br>
 *
 *
 * <b>Examples </b> <br>
 *
 * Check and print element or plugin information with names in GStreamer. <br>
 * @code {.c}
 * gst-inspect-1.0 videoconvert
 * @endcode
 * <br>
 * Check and print element or plugin information with a keyword in GStreamer. <br>
 * @code {.c}
 * gst-inspect-1.0 | grep video
 * @endcode
 * <br>
 *
 * Check and print Ambarella plugin information. <br>
 * @code {.c}
 * gst-inspect-1.0 amba
 * @endcode
 * <br>
 * Check and print element information in Ambarella plugins. <br>
 * @code {.c}
 * gst-inspect-1.0 amba_camsrc
 * @endcode
 * <br>
 * Check and print NNstreamer plugin information. <br>
 * @code {.c}
 * gst-inspect-1.0 nnstreamer
 * @endcode
 * <br>
 *
 * @subsubsection gst_launch_x 2.2.2 gst-launch-1.0
 *
 * The `gst-launch-1.0` command tool is used to build and run basic GStreamer pipelines.
 *
 * @code {.c}
 * gst-launch-1.0 [OPTIONS] [PIPELINE-DESCRIPTION]
 * @endcode
 *
 * <b>Options </b> <br>
 *
 * The `gst-launch-1.0` tool accepts the following options: <br>
 *
 *    - <b>--help:</b> prints help synopsis and available FLAGS <br>
 *    - <b>-v, --verbose:</b> outputs status information and property notifications <br>
 *    - <b>-q, --quiet:</b> do not print any progress information <br>
 *    - <b>-m, --messages:</b> outputs messages posted on the pipeline's bus <br>
 *    - <b>-t, --tags:</b> outputs tags (also known as metadata) <br>
 *    - <b>-o FILE, --output=FILE:</b> saves XML representation of the pipeline to FILE and exits <br>
 *    - <b>-f, --no_fault:</b> do not install a fault handler <br>
 *    - <b>-T, --trace:</b> prints memory allocation traces; this feature must be enabled at compilation time to function <br>
 *
 * <b>Pipeline Description </b> <br>
 *
 * The `gst-launch-1.0` tool takes a pipeline described as a string to instantiate and run it.
 * <b>PIPELINE-DESCRIPTION</b> is a linked list of elements separated by exclamation marks `!`.
 *
 * @code {.c}
 * $ gst-launch-1.0 [ELEMENTTYPE] [PROPERTY=...] ! [ELEMENTTYPE] [PROPERTY=...] ...
 * @endcode
 * <br>
 * For example: <br>
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc ! videoconvert ! autovideosink
 * @endcode
 * <br>
 * A simple pipeline consists of the following parts: <br>
 *
 *    - <b>Source elements:</b> interval; only smart rate control (SRC) pads exist in the element <br>
 *    - <b>Filter / filter-like elements:</b> options; both sink pads and SRC pads exist in the element which operate on data received at input (sink) pads, and feed data at their output (source) pads <br>
 *    - <b>Sink elements:</b> interval; only sink pads exist in the element which take in data, but do not produce anything <br>
 *    - <b>!:</b> interval; link mark <br>
 *    - <b>Capabilities:</b> options; specifies what type of information can travel through the pad <br>
 *
 * <b>Elements </b> <br>
 *
 * The most important object in GStreamer for developers is the GstElement. Elements are the basic building blocks of multi-media pipelines. <br>
 * Elements can be visualized as black boxes. On one hand, users may place something into the elements which helps perform some functions.
 * On the other hand, users may receive another output from the elements.
 * Pads allow information to enter and leave an element. <br>
 *
 * Create an element of the type <b>ELEMENTTYPE</b> and set its <b>PROPERTIES</b>.
 * The tool `gst-inspect-1.0` can be used to find information regarding properties and permitted values of different elements.
 * If spaces exist in a property value, users can place them in single or double quotes. <br>
 *
 * @code {.c}
 * [ELEMENTTYPE] [PROPERTY1=VALUE1 PROPERTY2=VALUE2 ...]
 * @endcode
 *
 * For example:
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc pattern=11 ! videoconvert ! autovideosink
 * @endcode
 *
 * <b>Source Elements </b> <br>
 *
 * A source element is an element that provides data to the pipeline. It does typically not possess any sink (input) pads. <br>
 * Typical source elements include the following:
 *
 *    - <b>File readers:</b> load files <br>
 *    - <b>Network elements:</b> load and run networks, lively or not lively <br>
 *    - <b>Capture elements:</b> capture video, audio, and more <br>
 *    - <b>Generators:</b> generate signals, video, audio, and more <br>
 *
 * @image html source_element.png "Figure 2-1. Source Element."
 * <br>
 *
 * <b>Filter / Filter-Like Elements </b> <br>
 *
 * Filter / filter-like elements have both input (sink) and output (source) pads.
 * They operate on data received at input pads and feed data to their output pads. <br>
 * Typical filter / filter-like elements include the following:
 *
 *    - <b>Filters </b> <br>
 *    - <b>Convertors </b> <br>
 *    - <b>Demuxers </b> <br>
 *    - <b>Muxers </b> <br>
 *    - <b>Codecs </b> <br>
 *
 * @image html filter_element.png "Figure 2-2. Filter Element."
 * <br>
 *
 * @image html demuxer_element.png "Figure 2-3. Demuxer Element."
 * <br>
 *
 * <b>Sink Elements </b> <br>
 *
 * Sink elements consume data and typically have no source pads. <br>
 * Typical sink elements include the following:
 *
 *    - <b>Audio / video renderers </b> <br>
 *    - <b>Network sinks </b> <br>
 *    - <b>Filesinks </b> <br>
 *
 * @image html sink_element.png "Figure 2-4. Sink Element."
 * <br>
 *
 * <b>Links </b> <br>
 *
 * The simplest link is an exclamation mark `!`. <br>
 *
 * Names can be set on elements using the name property. If the name is omitted, the element that was specified directly in front of or after the link is used. <br>
 *
 * @code {.c}
 * [[ELEMENTTYPE] [name=NAME1] ! ... [NAME1.] ! ...
 * @endcode
 *
 * Users can use element names to implement complex pipelines with multiple branches. This is common for elements with multiple output / input (mux, demux, tee, and more). <br>
 *
 * The following command creates two branches from tee, each for different sinks. After one branch is finished (reaching the sink), users can create a new branch with a name followed by a dot ([NAME.]). <br>
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc ! videoconvert ! tee name=t ! queue ! autovideosink t. ! queue ! autovideosink
 * @endcode
 *
 * In the same way, multiple branches can also be merged into one. First, decode the files, encode the video to H.264 and the audio to MP3, and finally merge them to produce a TS file. <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=surround.mp4 ! decodebin name=dmux ! queue ! audioconvert ! lamemp3enc ! mux. \
 *   dmux. ! queue ! x264enc ! mpegtsmux name=mux ! queue ! filesink location=out.ts
 * @endcode
 *
 * In the example above, for elements which have only one input / output pad, there is no need to connect with pads.
 * If a pad name is provided in an element, the link is performed using that pad. If no pad names are provided, all possibilities are tried and a
 * compatible pad is used.
 * If multiple pad names are provided, both sides must have the same number of pads specified and multiple links are performed in the given order.
 * The tool `gst-inspect-1.0` can help find all pads in a specific element. <br>
 *
 * Link the element with the name <b>SRCELEMENT</b> to the element with the name <b>SINKELEMENT</b>. <br>
 * @code {.c}
 * [[SRCELEMENT].[PAD1,...]] ! [[SINKELEMENT].[PAD1,...]]
 * @endcode
 *
 * For example: <br>
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc name=a autovideosink name=b a.src ! b.sink
 * @endcode
 *
 * However, because there are no other symbols but spaces before and after element names,
 * the order between elements and link marks is not important for `gst-launch-1.0`.
 * The example is as shown below: <br>
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc name=a a.src ! b.sink autovideosink name=b
 * @endcode
 *
 * A simplified version is as shown below: <br>
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc ! autovideosink
 * @endcode
 *
 * <b>Capabilities </b> <br>
 *
 * The capabilities (caps) of a pad specify what type of information can travel through the pad.
 * In order for two elements to be linked together, they must share a common subset of capabilities.
 * However, the actual information traveling from pad to pad must have only one well-specified type through a process known as negotiation.
 * The caps filter functions as an element that only accepts the specified data type and passes the data to the next element, which can effectively solve the ambiguity issue. <br>
 *
 * The following links the element with the name <b>SRCELEMENT</b> to the element with the name <bSINKELEMENT</b>, using the capability specified in <b>CAPS</b> as a filter. <br>
 *
 * @code {.c}
 * [[SRCELEMENT].[PAD1,...]] ! CAPS ! [[SINKELEMENT].[PAD1,...]]
 * @endcode
 *
 * Users can create a capability with the provided mimetype and optionally with provided properties.
 * The mimetype can be escaped using '"' or '''. If users want to use chain caps, they can add more caps in the same format afterwards. <br>
 *
 * @code {.c}
 * MIMETYPE [, PROPERTY[, PROPERTY ...]]] [; CAPS[; CAPS ...]]
 * @endcode
 *
 * For example: <br>
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc ! 'video/x-raw, width=1920, height=1080' ! autovideosink
 * $ gst-launch-1.0 videotestsrc ! "video/x-raw, width=1920, height=1080" ! autovideosink
 * @endcode
 * <br>
 *
 * Note that the properties of <b>CAPS</b> are separated by commas; this is different from that of elements whose properties are separated by whitespace. <br>
 *
 * For types of caps properties, GStreamer provides keywords to convert: <br>
 *
 *    - <b>i or int:</b> integer values or ranges <br>
 *    - <b>f or float:</b> float values or ranges <br>
 *    - <b>4 or fourcc:</b> FOURCC values <br>
 *    - <b>b, bool, or boolean:</b> Boolean values <br>
 *    - <b>s, str, or string:</b> strings <br>
 *    - <b>fraction:</b> fractions <br>
 *    - <b>l or list:</b> lists <br>
 *
 * If no type was provided, the following order is attempted: integer, float, Boolean, then string. <br>
 *
 * <b>Examples </b> <br>
 *
 * The examples below assume that users have the correct plugins available.
 *
 * <b>Audio / Video Playback </b> <br>
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=123.mp3 ! decodebin ! audioconvert ! audioresample ! autoaudiosink
 * @endcode
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=123.mp4 ! decodebin ! autovideoconvert ! autovideosink
 * @endcode
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=123.mp4 ! qtdemux name=demux demux.video_0 ! queue ! decodebin ! videoconvert ! videoscale ! autovideosink
 * @endcode
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=123.mp4 ! qtdemux name=demux  demux.  ! queue ! decodebin  ! autovideosink  demux. ! queue  ! decodebin  ! audioconvert ! audioresample ! autoaudiosink
 * @endcode
 *
 * <b>H.264 / H.265 Decode </b> <br>
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=1.h264 ! decodebin  ! autovideosink
 * @endcode
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=1.h264 ! video/x-h264 ! h264parse ! avdec_h264 ! autovideosink
 * @endcode
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=1.h265 ! video/x-h265 ! h265parse ! avdec_h265 ! autovideosink
 * @endcode
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=1.h264 ! video/x-h264 ! h264parse ! avdec_h264 ! filesink  location=1.yuv
 * @endcode
 *
 * <b>JPEG Encode / Decode </b> <br>
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=test_mjpeg.mp4 ! qtdemux ! jpegdec ! multifilesink location=%02d.yuv
 * @endcode
 *
 * @code {.c}
 * $ gst-launch-1.0 filesrc blocksize=xxx location=xxx.yuv ! "video/x-raw,format=I420,width=1280,height=720" ! videoconvert ! jpegenc ! filesink location=yyy.jpg
 * @endcode
 *
 * For more details, refer to section @ref amba_test_cases. <br>
 *
 * @subsubsection gstd_cmdline 2.2.3 GStreamer Daemon Commandline
 *
 * This section describes how initialize and run GstD, and demonstrates how to use the GstdClient application to draft tests. <br>
 *
 * <b>Local Shell </b> <br>
 *
 * Start the GStreamer Daemon in the local system: <br>
 * For GstD Yocto community version 0.8.0: <br>
 * @code {.c}
 * $ gstd -D
 * @endcode
 *
 * For the newer GstD version 0.15.0: <br>
 * @code {.c}
 * $ gstd
 * @endcode
 *
 * This starts the process in the background. Different options can be configured for the server: <br>
 * @code {.c}
 * $ gstd --help-all
 * @endcode
 *
 * <b>Remote Shell </b> <br>
 *
 * Start the GStreamer client in an external system where the client application can run and request commands: <br>
 * @code {.c}
 * $ gst-client
 * @endcode
 *
 * Once the server is up and running, users may use the commandline application to create, play, and stop pipelines. <br>
 *
 * @code {.c}
 * # Create the pipeline
 * $ pipeline_create testpipe videotestsrc name=vts ! autovideosink
 * # Play the pipeline
 * $ pipeline_play testpipe
 * # Change a property
 * $ element_set testpipe vts pattern ball
 * # Stop the pipeline
 * $ pipeline_stop testpipe
 * # Destroy the pipeline
 * $ pipeline_delete testpipe
 * @endcode
 *
 * To list all possible commands in gst-client: <br>
 * @code {.c}
 * $ help
 * @endcode
 *
 * Alternatively, users may use the commandline application in single-command mode,
 * in which the command is provided as an argument. This mode is ideal for shell scripts. For example: <br>
 * @code {.c}
 * $ gst-client list_pipelines
 * @endcode
 *
 * More can be found at the following official website link: <br>
 * https://developer.ridgerun.com/wiki/index.php/GStreamer_Daemon <br>
 *
 * @subsection debug 2.3 Debugging
 *
 * This section provides methods to debug GStreamer. <br>
 * This section includes the following sub-sections:
 *     - Section @ref gst_launch_x_debug
 *     - Section @ref gstd_debug
 *
 * @subsubsection gst_launch_x_debug 2.3.1 Debug with gst-launch-1.0
 *
 * There is a comma-separated list of debug categories and levels to aid in developing the user's code. <br>
 * <b>--gst-debug-help </b> <br>
 * `--gst-debug-help` prints available debug categories and exits with the GStreamer commandline tool `gst-launch-1.0`. <br>
 *
 * <b>--gst-debug-level </b> <br>
 * `--gst-debug-level LEVEL` sets the default debug level (which can range from 0 (no output) to 9 (everything)). <br>
 *
 * <table>
 * <caption id="table_gst_debug_level">Table 2-1. GStreamer Debug Level.</caption>
 * <tr><th> Level  <th> Property  <th> Description
 * <tr><td> 0      <td> none      <td> No debug information
 * <tr><td> 1      <td> ERROR     <td> Logs all fatal errors that do not allow the core or elements to perform the requested action
 * <tr><td> 2      <td> WARNING   <td> Logs all warnings that are non-fatal, but user-visible problems
 * <tr><td> 3      <td> FIXME     <td> Logs all fixme messages that indicate something in the executed code path is not fully implemented or managed yet
 * <tr><td> 4      <td> INFO      <td> Logs all informational messages for events in the system that only occur once, or are important and rare enough to be logged at this level
 * <tr><td> 5      <td> DEBUG     <td> Logs all debug messages for events that occur a limited number of times during an object's lifetime
 * <tr><td> 6      <td> LOG       <td> Logs all log messages for events that occur repeatedly during an object's lifetime
 * <tr><td> 7      <td> TRACE     <td> Logs all trace messages for events that occur repeatedly during an object's lifetime, such as the ref / unref cycles
 * <tr><td> 9      <td> MEMDUMP   <td> Hex dump of buffer contents
 * </table>
 *
 * For example: <br>
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc ! fakesink --gst-debug-level 3
 * @endcode
 *
 * <b>--gst-debug </b> <br>
 *
 * `--gst-debug LIST` takes a comma-separated list of `category_name:level pairs` to set specific levels for individual categories. For example: <br>
 * @code {.c}
 * $ gst-launch-1.0 videotestsrc ! fakesink --gst-debug basesrc:4,basesink:5
 * @endcode
 *
 * <b>GST_DEBUG </b> <br>
 *
 * Users can set the `GST_DEBUG` environment variable, which has the same effect as `--gst-debug`. For example: <br>
 * @code {.c}
 * $ GST_DEBUG=basesrc:4,basesink:5 gst-launch-1.0 videotestsrc ! fakesink
 * @endcode
 *
 * @subsubsection gstd_debug 2.3.2 GstD Debug
 *
 * This section describes how to enable debugging for a given pipeline in the GStreamer Daemon. <br>
 *
 * <b>Bus </b> <br>
 *
 * A GStreamer bus forwards messages generated from the pipeline, and the GStreamer Daemon enables those messages to flow back to the client application.
 * A basic description on how to interact with GStreamer bus properties is provided below; specifically, regarding how to receive messages from the bus. <br>
 *
 * <b>Read Bus </b> <br>
 *
 * Read the pipeline bus: <br>
 * @code {.c}
 * $ bus_read <name>
 * @endcode
 *
 * <b>Read and Filter Bus </b> <br>
 *
 * GstD has the capability to read and filter (error+warning+eos) the bus of the pipeline: <br>
 * @code {.c}
 * $ bus_filter <name> <filter>
 * @endcode
 *
 * <b>Bus Timeout </b> <br>
 *
 * By setting the pipeline bus timeout, the command will block while waiting for messages: <br>
 * @code {.c}
 * $ bus_timeout <name> <time in nanoseconds>
 * @endcode
 *
 * <b>Bus Messages </b> <br>
 *
 * The following table lists supported bus messages. Users can use either a hyphen or an underscore in the bus message name. <br>
 *
 * <table>
 * <caption id="table_bus_messgae">Table 2-2. Bus Messages in GstD.</caption>
 * <tr><th> Bus Message       <th> Version  <th> Meaning
 * <tr><td> eos               <td> all      <td> After the pipeline sink element finishes processing EOS, the bus reports the event to the application
 * <tr><td> error             <td> all      <td> An element in the pipeline is in the error state
 * <tr><td> warning           <td> all      <td> An element in the pipeline encounters a recoverable error
 * <tr><td> info              <td> all      <td> An element in the pipeline produces some information
 * <tr><td> tag               <td> all      <td> An element in the pipeline decodes metadata about the stream
 * <tr><td> buffering         <td> all      <td> An element in the pipeline that is buffering adds a delay until the buffer is full
 * <tr><td> clock_lost        <td> all      <td> The pipeline clock is unusable
 * <tr><td> new_clock         <td> all      <td> A new clock was selected for the pipeline
 * <tr><td> structure_change  <td> all      <td> The buffer flow through the pipeline changed
 * <tr><td> stream_status     <td> all      <td> The pipeline started, stopped, or paused
 * <tr><td> element           <td> all      <td> Element-specific message
 * <tr><td> segment_start     <td> all      <td> New stream segment is being processed
 * <tr><td> segment_done      <td> all      <td> Segment seek requested and segment playback completed
 * <tr><td> ...               <td> ...      <td> ...
 * </table>
 *
 * Details of these messages can be found in the `gstd_msg_type_get_type` table at
 * https://github.com/RidgeRun/gstd-1.x/blob/master/gstd/gstd_msg_type.c <br>
 *
 * The examples below demonstrate how to use the bus filter and bus read. <br>
 *
 * Error bus filter: <br>
 * @code {.c}
 * # Create the pipeline that generate an error
 * $ pipeline_create p filesrc location=/tmp/test.avi ! identity error-after=2000 ! avidemux ! avdec_mpeg4 ! fpsdisplaysink
 * # Filter only a message error
 * $ bus_filter p error
 * # Play the pipeline
 * $ pipeline_play p
 * # Waiting until bus read a message error
 * $ bus_read p
 * @endcode
 *
 * Error bus filter and timeout: <br>
 * @code {.c}
 * # Create the pipeline that generate an error
 * $ pipeline_create p filesrc location=/tmp/test.avi ! identity error-after=2000 ! avidemux ! avdec_mpeg4 ! fpsdisplaysink
 * # Filter only a message error
 * $ bus_filter p error
 * # wait 100s to read message error, if not, returns
 * $ bus_timeout p 100000000000
 * # Play the pipeline
 * $ pipeline_play p
 * # Waiting until bus read a message error
 * $ bus_read p
 * @endcode
 *
 * Error+EOS bus filter: <br>
 * @code {.c}
 * # Create the pipeline that generate an eos
 * $ pipeline_create p filesrc location=/tmp/test.avi  ! avidemux ! avdec_mpeg4 ! fpsdisplaysink
 * # Filter a message error and EOS message
 * $ bus_filter p error+eos
 * # Play the pipeline
 * $ pipeline_play p
 * # Waiting until bus read a message error or eos message
 * $ bus_read p
 * @endcode
 *
 * <b>Debug Subsystem </b> <br>
 *
 * <b>Enabling the Debug Subsystem </b> <br>
 *
 * This section demonstrates how to enable the debug to a given pipeline in the GStreamer Daemon. <br>
 *
 * <b>Enable Debug </b> <br>
 *
 * @code {.c}
 * $ debug_enable true/false
 * @endcode
 *
 * <b>Debug Level </b> <br>
 *
 * Along with specifying a single level, users can also provide a list of comma-separated category:level pairs,
 * such as `v4l2src:3,GST_EVENT:5` to monitor both what is happening with the v4l2src element
 * and the GStreamer events that are occurring. <br>
 *
 * @code {.c}
 * $ debug_threshold threshold
 * @endcode
 *
 * Refer to @ref gst_launch_x_debug; for all possible debug categories, run the following: <br>
 * @code {.c}
 * $ gst-launch-1.0 --gst-debug-help
 * @endcode
 *
 * <b>Enable Debug Colors </b> <br>
 *
 * @code {.c}
 * $ debug_color true/false
 * @endcode
 *
 * The example below demonstrates how to debug a pipeline: <br>
 * @code {.c}
 * # Create a pipeline p1
 * $ pipeline_create p1 videotestsrc ! autovideosink
 * # Put it to playing
 * $ pipeline_play p1
 * # Enable debug
 * $ debug_enable true
 * # Set the debug level on 6
 * $ debug_threshold *sink*:6
 * # Enable the debug color
 * $ debug_color true
 * @endcode
 *
 * @subsection amba_test_cases 2.4 Ambarella Test Cases
 *
 * This section demonstrates typical scenarios and cases to test Ambarella GStreamer plugins
 * associated with GStreamer core / community plugins and third-party open source plugins (NNstreamer and others). <br>
 *
 * All Lua files tested below were in the path <br>
 * `\ambarella\packages\amba_gst_plugins\additional\lua_scripts\` <br>
 *
 * This section includes the following sub-sections:
 *     - Section @ref record_scenario
 *     - Section @ref playback_scenario
 *     - Section @ref machine_learning_scenario
 *     - Section @ref setup_encoding_params
 *     - Section @ref mimic_dual_vin_scenarios
 *     - Section @ref jpeg_scenarios
 *     - Section @ref rtsp_scenarios
 *     - Section @ref debug_cases
 *     - Section @ref use_in_lychee
 *     - Section @ref known_issues
 *     - Section @ref notice
 *
 * @subsubsection record_scenario 2.4.1 Record Scenarios
 *
 * Refer to the `amba_venccap` and `amba_vencdemux` elements; the following shows how to encode and record streams. <br>
 *
 * @subsubsection example_record_2_streams Example 1: Record One or Two Streams
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --hdmi 1080p --resource-cfg /home/root/dualvin.lua
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/cv28_dualvin.lua
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/cv52_vin0_1_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/cv72_vin0_1_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * <b>H.264 to MP4</b> <br>
 * Start two streams of H.264 encoding: <br>
 * @code {.c}
 * $ test_encode -A -h 1080p -b 0 -e -B -h 1080p -b 1 -e
 * @endcode
 *
 * Record one stream of video (H.264 to MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=dm dm.stream0 ! queue ! h264parse ! mp4mux ! filesink location=/tmp/h264.mp4
 * @endcode
 *
 * Record two streams of video (H.264 to MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=vencdemux vencdemux.stream0 ! queue ! h264parse ! mp4mux ! filesink location=/tmp/h264_0.mp4 \
 *   vencdemux.stream1 ! queue ! h264parse ! mp4mux ! filesink location=/tmp/h264_1.mp4
 * @endcode
 *
 * Record one stream of video / audio (H.264 + opus -> MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! queue ! opusenc ! mp4mux name=mux ! filesink location=/tmp/h264_opus.mp4 \
 *   -e amba_venccap sync=TRUE ! amba_vencdemux name=d d.stream0 ! queue ! h264parse ! mux.
 * @endcode
 *
 * Record two streams of video / audio (H.264 + opus -> MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! queue ! opusenc ! tee name=t t.src_0 ! mp4mux name=mux0 ! filesink location=/tmp/h264_opus_0.mp4 \
 *   -e amba_venccap sync=TRUE ! amba_vencdemux name=d d.stream0 ! queue ! h264parse ! mux0. \
 *   t.src_1 ! mp4mux name=mux1 ! filesink location=/tmp/h264_opus_1.mp4 d.stream1 ! queue ! h264parse ! mux1.
 * @endcode
 *
 * Record one stream of video / audio (H.264 + advanced audio coding (AAC) -> MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! audio/x-raw,rate=48000 ! audioconvert ! avenc_aac ! queue ! mp4mux name=mux ! filesink location=/tmp/h264_aac.mp4 \
 *   -e amba_venccap sync=TRUE ! amba_vencdemux name=d d.stream0 ! queue ! h264parse ! mux.
 * @endcode
 *
 * Record two streams of video / audio (H.264 + AAC -> MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! audio/x-raw,rate=48000 ! audioconvert ! avenc_aac ! queue ! tee name=t t.src_0 ! mp4mux name=mux0 ! filesink location=/tmp/h264_aac_0.mp4 \
 *   -e amba_venccap sync=TRUE ! amba_vencdemux name=d d.stream0 ! queue ! h264parse ! mux0. \
 *   t.src_1 ! mp4mux name=mux1 ! filesink location=/tmp/h264_aac_1.mp4 d.stream1 ! queue ! h264parse ! mux1.
 * @endcode
 *
 * Stop encoding: <br>
 * @code {.c}
 * $ test_encode -A -s -B -s
 * @endcode
 *
 * <b>H.265 to MP4</b> <br>
 * Start H.265 encoding: <br>
 * @code {.c}
 * $ test_encode -A -H 1080p -b 0 -e -B -H 1080p -b 1 -e
 * @endcode
 *
 * Record one stream of video (H.265 to MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=dm dm.stream0 ! queue ! h265parse ! mp4mux ! filesink location=/tmp/h265.mp4
 * @endcode
 *
 * Record one stream of video (H.265 -> MP4 + HEIC): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux heic-capture-id=0 filename-base=/tmp/amba%06d.heic name=dm dm.stream0 \
 *   ! queue ! h265parse ! mp4mux ! filesink location=/tmp/h265.mp4
 * @endcode
 *
 * Record two streams of video (H.265 to MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=vencdemux vencdemux.stream0 ! queue ! h265parse ! mp4mux ! filesink location=/tmp/h265_0.mp4 \
 *   vencdemux.stream1 ! queue ! h265parse ! mp4mux ! filesink location=/tmp/h265_1.mp4
 * @endcode
 *
 * Record one stream of video / audio (H.265 + opus -> MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! queue ! opusenc ! mp4mux name=mux ! filesink location=/tmp/h265_opus.mp4 \
 *   -e amba_venccap sync=TRUE ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! mux.
 * @endcode
 *
 * Record two streams of video / audio (H.265 + opus -> MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! queue ! opusenc ! tee name=t t.src_0 ! mp4mux name=mux0 ! filesink location=/tmp/h265_opus_0.mp4 \
 *   -e amba_venccap sync=TRUE ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! mux0. t.src_1 ! mp4mux name=mux1 ! filesink location=/tmp/h265_opus_1.mp4 \
 *   d.stream1 ! queue ! h265parse ! mux1.
 * @endcode
 *
 * Record one stream of video / audio (H.265 + AAC -> MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! audio/x-raw,rate=48000 ! audioconvert ! avenc_aac ! queue ! mp4mux name=mux ! filesink location=/tmp/h265_aac.mp4 \
 *   -e amba_venccap sync=TRUE ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! mux.
 * @endcode
 *
 * Record two streams of video / audio (H.265 + AAC -> MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! audio/x-raw,rate=48000 ! audioconvert ! avenc_aac ! queue ! tee name=t t.src_0 ! mp4mux name=mux0 ! filesink location=/tmp/h265_aac_0.mp4 \
 *   -e amba_venccap sync=TRUE ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! mux0. t.src_1 ! mp4mux name=mux1 ! filesink location=/tmp/h265_aac_1.mp4 \
 *   d.stream1 ! queue ! h265parse ! mux1.
 * @endcode
 *
 * Stop encoding: <br>
 * @code {.c}
 * $ test_encode -A -s -B -s
 * @endcode
 *
 * @subsubsection example_record_6_streams Example 2: Record Six Streams
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --hdmi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 * # Start six streams of encoding
 * $ test_encode -A -H 1080p -b 0 -e -B -h 1080p -b 1 -e -C -H 480p -b 2 -e -D -h 480p -b 3 -e -E -H 480p -b 4 -e -S 5 -h 480p -b 5 -e
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 * # Start six streams of encoding
 * $ test_encode -A -H 1080p -b 0 -e -B -h 1080p -b 1 -e -C -H 480p -b 2 -e -D -h 480p -b 3 -e -E -H 480p -b 4 -e -S 5 -h 480p -b 5 -e
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/cv52_four_vin_1080p_linear_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * # start six streams encoding
 * $ test_encode -A -H 1080p -b 0 -e -B -h 1080p -b 1 -e -C -H 1080p -b 2 -e -D -h 480p -b 3 -e -E -H 480p -b 4 -e -S 5 -h 480p -b 5 -e
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/cv72_four_vin_1080p_linear_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * # start six streams encoding
 * $ test_encode -A -H 1080p -b 0 -e -B -h 1080p -b 1 -e -C -H 1080p -b 2 -e -D -h 480p -b 3 -e -E -H 480p -b 4 -e -S 5 -h 480p -b 5 -e
 * @endcode
 *
 * Record six streams of video (H.264 / H.265):<br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=d d.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux  ! filesink location=/tmp/h265_0.mp4 \
 *   d.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_1.mp4 \
 *   d.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_2.mp4 \
 *   d.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_3.mp4 \
 *   d.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_4.mp4 \
 *   d.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_5.mp4
 * @endcode
 *
 * Record six streams of video / audio (H.264 / H.265 + opus):<br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! opusenc ! tee name=t t.src_0 ! mp4mux name=mux0 ! filesink location=/tmp/h265_opus_0.mp4 \
 *   -e amba_venccap sync=true ! amba_vencdemux heic-capture-id=0 filename-base=/tmp/amba%06d.heic name=d d.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux0. \
 *   t.src_1 ! mp4mux name=mux1 ! filesink location=/tmp/h264_opus_1.mp4 d.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux1. \
 *   t.src_2 ! mp4mux name=mux2 ! filesink location=/tmp/h265_opus_2.mp4 d.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux2. \
 *   t.src_3 ! mp4mux name=mux3 ! filesink location=/tmp/h264_opus_3.mp4 d.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux3. \
 *   t.src_4 ! mp4mux name=mux4 ! filesink location=/tmp/h265_opus_4.mp4 d.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux4. \
 *   t.src_5 ! mp4mux name=mux5 ! filesink location=/tmp/h264_opus_5.mp4 d.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux5.
 * @endcode
 *
 * Record six streams of video / audio (H.264 / H.265 + AAC): <br>
 * @code {.c}
 * $ gst-launch-1.0 -e alsasrc ! audio/x-raw,rate=48000 ! audioconvert ! avenc_aac ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! tee name=t t.src_0 ! mp4mux name=mux0 ! filesink location=/tmp/h265_aac_0.mp4 \
 *   -e amba_venccap sync=true ! amba_vencdemux heic-capture-id=0 filename-base=/tmp/amba%06d.heic name=d d.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux0. \
 *   t.src_1 ! mp4mux name=mux1 ! filesink location=/tmp/h264_aac_1.mp4 d.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux1. \
 *   t.src_2 ! mp4mux name=mux2 ! filesink location=/tmp/h265_aac_2.mp4 d.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux2. \
 *   t.src_3 ! mp4mux name=mux3 ! filesink location=/tmp/h264_aac_3.mp4 d.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux3. \
 *   t.src_4 ! mp4mux name=mux4 ! filesink location=/tmp/h265_aac_4.mp4 d.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux4. \
 *   t.src_5 ! mp4mux name=mux5 ! filesink location=/tmp/h264_aac_5.mp4 d.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux5.
 * @endcode
 *
 * Stop six streams of encoding: <br>
 * @code {.c}
 * $ test_encode -A -s -B -s -C -s -D -s -E -s -S 5 -s
 * @endcode
 *
 * @subsubsection playback_scenario 2.4.2 Playback Scenario
 *
 * This section demonstrates how to decode and play back streams. <br>
 *
 * Refer to the `amba_hwvdec` element; the following shows how to play back streams with the Ambarella hardware decoder. <br>
 * Note that the `amba_hwvdec` element supports decoding streams that are encoded from Amba venc. <br>
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_vout --hdmi 1080p
 *
 * # for cv28, `mipi_dsi` in the `amba_hwvdec` element is not supported; skip this section.
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_vout --mipi_dsi 1080p
 *
 * # Since there's some issue of DSP V6 existed in amba-gst-plugin,
 * # `amba_hwvdec` is not supported on CV52/CV72/CV3 now; skip this section.
 * @endcode
 *
 * Play back H.264 + opus (MP4): <br>
 * @code {.c}
 * # for audio
 * $ gst-launch-1.0 filesrc location=/tmp/h264_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! opusdec ! audioconvert ! autoaudiosink
 * # for video
 * $ gst-launch-1.0 filesrc location=/tmp/h264_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! h264parse ! amba_hwvdec ! amba_vsink
 * # for video + audio
 * $ gst-launch-1.0 filesrc location=/tmp/h264_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! opusdec ! audioconvert ! autoaudiosink \
 *   demuxer. ! queue ! h264parse ! amba_hwvdec ! amba_vsink async=false
 * @endcode
 *
 * Play back H.265 + opus (MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/h265_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! opusdec ! audioconvert ! autoaudiosink \
 *   demuxer. ! queue ! h265parse ! amba_hwvdec ! amba_vsink async=false
 * @endcode
 *
 * Play back H.264 + AAC (MP4): <br>
 * @code {.c}
 * # for audio
 * $ gst-launch-1.0 filesrc location=/tmp/h264_aac.mp4 ! qtdemux name=demuxer demuxer. ! queue ! avdec_aac ! audioconvert ! autoaudiosink
 * # for video
 * $ gst-launch-1.0 filesrc location=/tmp/h264_aac.mp4 ! qtdemux name=demuxer demuxer. ! queue ! h264parse ! amba_hwvdec ! amba_vsink
 * # for video + audio
 * $ gst-launch-1.0 filesrc location=/tmp/h264_aac.mp4 ! qtdemux name=demuxer demuxer. ! queue ! avdec_aac ! audioconvert ! autoaudiosink \
 *   demuxer. ! queue ! h264parse ! amba_hwvdec ! amba_vsink async=false
 * @endcode
 *
 * Play back H.265 + AAC (MP4): <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/h265_aac.mp4 ! qtdemux name=demuxer demuxer. ! queue ! avdec_aac ! audioconvert ! autoaudiosink \
 *   demuxer. ! queue ! h265parse ! amba_hwvdec ! amba_vsink async=false
 * @endcode
 *
 * Note that the digital signal processor (DSP) must return to the idle mode before decoding each time. <br>
 * @code {.c}
 * $ test_encode --idle --nopreview
 * @endcode
 *
 * @subsubsection machine_learning_scenario 2.4.3 Machine Learning Scenarios
 *
 * This section demonstrates how to run neural networks with Ambarella CVflow. <br>
 *
 * @subsubsection example_ml_in_amba_plugin Example 3: Machine Learning in the Amba Gst Plugin
 *
 * With the `mlinference` element in the Amba Gst Plugins, the following shows how to test NN models. <br>
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --hdmi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * # Please configure canvas encode dummy latency first, and enc_dummy_latency should be > 0.
 * $ test_encode --resource-cfg cv52_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * # Please configure canvas encode dummy latency first, and enc_dummy_latency should be > 0.
 * $ test_encode --resource-cfg cv72_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * $ modprobe cavalry
 * $ cavalry_load -f /lib/firmware/cavalry.bin -r
 * $ test_encode -A -H 1080p -b 0 -e -B -H 1080p -b 1 -e -C -H 480p -b 2 -e -D -H 480p -b 3 -e -E -h 480p -b 4 -e -S 5 -h 480p -b 5 -e
 * $ rtsp_server&
 *
 * # Since there's some issue of DSP V6 existed in amba-gst-plugin,
 * # `amba_venc_overlay` is not supported on CV52/CV72/CV3 now.
 * @endcode
 *
 * <b>amba_camsrc to Machine Learning </b> <br>
 *
 * Run a tested YOLOv5 model with post-processing, and then draw boxes on the overlay. <br>
 * @code {.c}
 * $ gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 \
 *   label = /tmp/nn/in/coco_class_names.txt model = /tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   type = yolov5s conf_threshold = 0.25 nms = 0.45 top_k = 100 ! queue ! amba_venc_overlay stream_id = 0 alpha = 0 \
 *   font = /tmp/arial.ttf clut_start = 22 clut_end = 70 color_number = 300 score_lmt = 0.25
 * @endcode
 *
 * Run a tested YOLOv5 model with an region of interest (ROI). <br>
 * @code {.c}
 * $ gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 \
 *   label = /tmp/nn/in/coco_class_names.txt model= /tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   type = yolov5s conf_threshold = 0.25 nms = 0.45 top_k = 100 roi=640.360.1280.720 ! queue ! amba_venc_overlay stream_id = 0 alpha = 0 \
 *   font = /tmp/arial.ttf clut_start = 22 clut_end = 70 color_number = 300 score_lmt = 0.25 roi=640.360.1280.720
 * @endcode
 *
 * Run a tested tiny YOLOv3 model with post-processing, and then draw boxes on the overlay. <br>
 * @code {.c}
 * $ gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = data out_name = layer115-conv out_name = layer125-conv \
 *   label = /tmp/nn/in/live_voc_labels.txt model = /tmp/nn/model/yolov3_fastest_xl_cavalry.bin \
 *   type = yolov3x conf_threshold = 0.8 nms = 0.3 top_k = 100 ! queue ! amba_venc_overlay stream_id = 0 alpha = 0 \
 *   font = /tmp/arial.ttf clut_start = 22 clut_end = 70 color_number = 300 score_lmt = 0.8
 * @endcode
 *
 * If not performing post-processing, remove the property `type=xxx`. <br>
 *
 * Run a tested efficientnet model without post-processing. <br>
 * @code {.c}
 * $ gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = input out_name = 672 \
 *   label = /tmp/efficientnet/coco_ids.yaml model = /tmp/efficientnet/efficientnet_cavalry.bin \
 *   conf_threshold = 0.2 nms = 0.5 top_k = 100 ! queue ! fakesink
 * @endcode
 *
 * Run a tested `tf_efficientdet_lite0` model without post-processing. <br>
 * @code {.c}
 * $ gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = image_arrays out_name = Sigmoid out_name = ArgMax out_name = stack_2 \
 *   label = /tmp/nn/in/coco_ids.yaml model = /tmp/nn/model/tf_efficientdet_lite0_cavalry.bin \
 *   conf_threshold = 0.2 nms = 0.5 top_k = 100 ! queue ! fakesink
 * @endcode
 *
 * Run a tested `movenet_lightning` model without post-processing. <br>
 * @code {.c}
 * $ gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = serving_default_input out_name = StatefulPartitionedCall \
 *   label = /tmp/movenet_lightning/coco_ids.yaml model = /tmp/movenet_lightning/tf_movenet_lightning_cavalry.bin \
 *   conf_threshold = 0.2 nms = 0.5 top_k = 100 ! queue ! fakesink
 * @endcode
 *
 * Run a tested `movenet_thunder` model without post-processing. <br>
 * @code {.c}
 * $ gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = serving_default_input out_name = StatefulPartitionedCall \
 *   label = /tmp/movenet_thunder/coco_ids.yaml model = /tmp/movenet_thunder/tf_movenet_thunder_cavalry.bin \
 *   conf_threshold = 0.2 nms = 0.5 top_k = 100 ! queue ! fakesink
 * @endcode
 *
 * Run a tested `fast_depth` model without post-processing. <br>
 * @code {.c}
 * $ gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = input.1 out_name = 424 \
 *   model = /tmp/fast_depth/onnx_fast_depth_cavalry.bin ! queue ! fakesink
 * @endcode
 *
 * <b>Software Decoding to Machine Learning </b> <br>
 *
 * Decode H.264 (MP4) to YOLOv5 with post-processing. Add `--gst-debug-level 3` to print the detected bounding box information: <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8_h264.mp4 ! qtdemux name=demuxer demuxer. ! queue ! h264parse ! avdec_h264 ! \
 *   videoconvert ! video/x-raw,format=RGBP ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 \
 *   label = /tmp/nn/in/coco_class_names.txt model = /tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   type = yolov5s conf_threshold = 0.25 nms = 0.45 top_k = 100 ! queue ! fakesink
 * @endcode
 *
 * Decode H.265 (MP4) to YOLOv5 with post-processing. Add `--gst-debug-level 3` to print the detected bounding box information: <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8_h265.mp4 ! qtdemux name=demuxer demuxer. ! queue ! h265parse ! avdec_h265 ! \
 *   videoconvert ! video/x-raw,format=RGBP ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 \
 *   label = /tmp/nn/in/coco_class_names.txt model = /tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   type = yolov5s conf_threshold = 0.25 nms = 0.45 top_k = 100 ! queue ! fakesink
 * @endcode
 *
 * Decode H.264 (ES) to YOLOv5 with post-processing. Add `--gst-debug-level 3` to print the detected bounding box information: <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! \
 *   queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 label = /tmp/nn/in/coco_class_names.txt \
 *   model = /tmp/nn/model/onnx_yolov5s_cavalry.bin conf_threshold = 0.25 nms = 0.45 top_k = 100 type = yolov5s ! queue ! fakesink
 * @endcode
 *
 * Decode H.265 (ES) to YOLOv5 with post-processing. Add `--gst-debug-level 3` to print the detected bounding box information: <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h265 ! h265parse ! avdec_h265 ! videoconvert ! video/x-raw,format=RGBP ! \
 *   queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 label = /tmp/nn/in/coco_class_names.txt \
 *   model = /tmp/nn/model/onnx_yolov5s_cavalry.bin conf_threshold = 0.25 nms = 0.45 top_k = 100 type = yolov5s ! queue ! fakesink
 * @endcode
 *
 * Decode motion JPEG to YOLOv5 with post-processing. Add `--gst-debug-level 3` to print the detected bounding box information: <br>
 * @code {.c}
 * # h264 (es) to motion jpeg
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert \
 *   ! avenc_mjpeg ! qtmux ! filesink location=/tmp/mojpeg.mp4
 * # motion jpeg to yolov5
 * $ gst-launch-1.0 filesrc location=/tmp/mojpeg.mp4 ! qtdemux ! queue ! avdec_mjpeg ! videoconvert ! video/x-raw,format=RGBP \
 *   ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 label = /tmp/nn/in/coco_class_names.txt \
 *   model = /tmp/nn/model/onnx_yolov5s_cavalry.bin type = yolov5s conf_threshold = 0.25 nms = 0.45 top_k = 100 ! fakesink
 * @endcode
 *
 * @subsubsection example_ml_in_nnstreamer Example 4: Machine Learning in NNStreamer
 *
 * With the `amba_cvflow` framework in the subplugin of the modified `tensor_filter` element, the following demonstrates how to run NN models with NNStreamer plugins. <br>
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --hdmi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv52_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv72_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * $ modprobe cavalry
 * $ cavalry_load -f /lib/firmware/cavalry.bin -r
 * $ test_encode -A -H 1080p -b 0 -e -B -H 1080p -b 1 -e -C -H 480p -b 2 -e -D -H 480p -b 3 -e -E -h 480p -b 4 -e -S 5 -h 480p -b 5 -e
 * @endcode
 *
 * <b>amba_camsrc to Machine Learning </b> <br>
 *
 * Run a tested YOLOv5 model with post-processing in `tensor_filter`. <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_camsrc buf-id=0 ! queue ! tensor_converter ! \
 *   tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997,label:/tmp/nn/in/coco_class_names.txt,f:0.25,nms:0.45,top_k:100,type:yolov5s,in_data_fmt:0.0.8.0 ! tensor_sink
 * @endcode
 *
 * Run a tested YOLOv5 model with post-processing in `tensor_decoder`. <br>
 * @code {.c}
 * # The output data format of NN model generated by CNNGEN was usually FP16(1.1.0.4) or FP32(1.2.0.7)
 * # If want to get FP32 data for postprocess, just setup `nn_out_f32:1` in tensor_filter.
 *
 * # yolov5s, postprocess in bounding_boxes, output with drawed video "RGBA".
 * $ gst-launch-1.0 -e amba_camsrc buf-id=0 ! queue ! tensor_converter ! \
 *   tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0,nn_out_f32:1 ! tensor_decoder mode=bounding_boxes option1=amba_yolov5 \
 *   option2=/tmp/nn/in/coco_class_names.txt option3=f:0.25,nms:0.45,top_k:100 option4=1280:720 option5=416:416 ! videoconvert ! fakesink
 *
 * # yolov5s, postprocess in bounding_boxes_ori, output with post-process results in 3 tensors(0: bboxes, 1: drive area mask(yolop), 2: lane line mask(yolop)).
 * $ gst-launch-1.0 -e amba_camsrc buf-id=0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0,nn_out_f32:1 ! tensor_decoder mode=bounding_boxes_ori \
 *   option1=amba_yolov5 option2=/tmp/nn/in/coco_class_names.txt option3=f:0.25,nms:0.45,top_k:100 option5=416:416 ! fakesink
 *
 * # yolop model for cv72, postprocess in bounding_boxes
 * $ gst-launch-1.0 -v -e amba_camsrc buf-id=0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/cv7x/cv72_cavalry3.0.3_onnx_yolop.bin \
 *   custom=in_name:images,out_name:1159+1515+drive_area_seg+lane_line_seg+1871,in_data_fmt:0.0.0.0,nn_out_f32:1 ! \
 *   tensor_decoder mode=bounding_boxes option1=amba_yolop option2=/tmp/nn/in/coco_class_names.txt \
 *   option3=f:0.25,nms:0.45,top_k:100 option4=1280:720 option5=640:640 ! fakesink
 *
 * # yolop model for cv72, postprocess in bounding_boxes_ori
 * $ gst-launch-1.0 -v -e amba_camsrc buf-id=0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/cv7x/cv72_cavalry3.0.3_onnx_yolop.bin \
 *   custom=in_name:images,out_name:1159+1515+drive_area_seg+lane_line_seg+1871,in_data_fmt:0.0.0.0,nn_out_f32:1 ! \
 *   tensor_decoder mode=bounding_boxes_ori option1=amba_yolop option2=/tmp/nn/in/coco_class_names.txt \
 *   option3=f:0.25,nms:0.45,top_k:100 option4=640:640 option5=640:640 ! fakesink
 * @endcode
 *
 * Run a tested YOLOv5 model without post-processing. <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_camsrc buf-id=0 ! queue ! tensor_converter ! \
 *   tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 ! tensor_sink
 * @endcode
 *
 * Run a tested YOLOv5 model with an ROI. <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_camsrc buf-id=0 ! queue ! tensor_converter ! \
 *   tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997,roi:640.360.1280.720,in_data_fmt:0.0.8.0 ! tensor_sink
 * @endcode
 *
 * <b>Software Decoding to Machine Learning </b> <br>
 *
 * Decode H.264 (MP4) to YOLOv5 without post-processing: <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8_h264.mp4 ! qtdemux name=demuxer demuxer. \
 *   ! queue ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! \
 *   tensor_converter ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 ! queue ! fakesink
 * @endcode
 *
 * Decode H.265 (MP4) to YOLOv5 without post-processing: <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8_h265.mp4 ! qtdemux name=demuxer demuxer. ! queue ! \
 *   h265parse ! avdec_h265 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! \
 *   tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 \
 *   ! queue ! fakesink
 * @endcode
 *
 * Decode H.264 (ES) to YOLOv5 without post-processing: <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP \
 *   ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 ! queue ! fakesink
 * @endcode
 *
 * Decode H.265 (ES) to YOLOv5 without post-processing: <br>
 * @code {.c}
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h265 ! h265parse ! avdec_h265 ! videoconvert ! video/x-raw,format=RGBP ! queue \
 *   ! tensor_converter ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 ! queue ! fakesink
 * @endcode
 *
 * <b>Machine Learning with Multiple Inputs </b> <br>
 *
 * Run a tested `tf_mobilenetv2` model without post-processing. <br>
 * @code {.c}
 * # $ test_nnctrl -b /tmp/multi_inputs_model/cv22_cavalry2.2.8.4_tf_mobilenetv2_nv12.bin --dummy -e
 * # Input: 0 [x] dim: (1, 2, 112, 112), pitch: 128, dram_fmt: 0, bitvector: 0, data_fmt: (0, 0, 0, 0), loop_cnt: 1, size: 28672, phys: 0x6083e000, virt: 0x7fbb36b000
 * # Input: 1 [x.1] dim: (1, 1, 224, 224), pitch: 224, dram_fmt: 0, bitvector: 0, data_fmt: (0, 0, 0, 0), loop_cnt: 1, size: 50176, phys: 0x60845000, virt: 0x7fbb372000
 * # Output: 0 [dense_1/BiasAdd] dim: (1, 1000, 1, 1), pitch: 32, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 32000, phys: 0x6087ec00, virt: 0x7fbb3abc00
 *
 * # input tensors: dims=112:112:2:1+224:224:1:1, types=uint8+uint8(0.0.0.0+0.0.0.0)
 * $ gst-launch-1.0 -v filesrc location=/tmp/src_112x112x2_u8.bin blocksize=25088 ! application/octet-stream ! \
 *   tensor_converter input-dim=112:112:2:1 input-type=uint8 ! queue ! mux.sink_0 \
 *   filesrc location=/tmp/src_224x224x1_u8.bin blocksize=50176 ! application/octet-stream ! tensor_converter input-dim=224:224:1:1 input-type=uint8 ! queue ! mux.sink_1 \
 *   tensor_mux name=mux sync_mode=nosync ! queue ! tensor_filter framework=amba_cvflow model=/tmp/multi_inputs_model/cv22_cavalry2.2.8.4_tf_mobilenetv2_nv12.bin \
 *   custom=in_name:x+x.1,out_name:dense_1/BiasAdd,in_data_fmt:0.0.0.0+0.0.0.0 ! queue ! filesink location=/tmp/nns_tf_mobilenet_v2_out.bin
 *   tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   custom=in_name:images,out_name:1037+1017+997 ! tensor_sink
 *
 * # input tensors: dims=2880:1856:2:1+2880:1856:1:1, types=uint8+uint8(0.0.0.0+0.0.0.0)
 * $ gst-launch-1.0 -v filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! \
 *   queue ! tensor_converter ! tensor_split name=split tensorseg=2880:1856:2:1,2880:1856:1:1 \
 *   split.src_0 ! queue ! mux.sink_0 split.src_1 ! queue ! mux.sink_1 tensor_mux name=mux sync_mode=nosync ! queue ! \
 *   tensor_filter framework=amba_cvflow model=/tmp/multi_inputs_model/cv22_cavalry2.2.8.4_tf_mobilenetv2_nv12.bin \
 *   custom=in_name:x+x.1,out_name:dense_1/BiasAdd,in_data_fmt:0.0.0.0+0.0.0.0 ! queue ! filesink location=/tmp/nns_tf_mobilenet_v2_out.bin
 *
 * # input tensors: dims=112:112:2:1+224:224:1:1, types=float32+uint8(1.2.0.7+0.0.0.0)
 * $ gst-launch-1.0 -v filesrc location=/tmp/src_112x112x2_f32.bin blocksize=100352 ! application/octet-stream ! \
 *   tensor_converter input-dim=112:112:2:1 input-type=float32 ! queue ! mux.sink_0 \
 *   filesrc location=/tmp/src_224x224x1_u8.bin blocksize=50176 ! application/octet-stream ! tensor_converter input-dim=224:224:1:1 input-type=uint8 ! queue ! mux.sink_1 \
 *   tensor_mux name=mux sync_mode=nosync ! queue ! tensor_filter framework=amba_cvflow model=/tmp/multi_inputs_model/cv22_cavalry2.2.8.4_tf_mobilenetv2_nv12.bin \
 *   custom=in_name:x+x.1,out_name:dense_1/BiasAdd,in_data_fmt:1.2.0.7+0.0.0.0 ! queue ! filesink location=/tmp/nns_tf_mobilenet_v2_out.bin * @endcode
 *
 * @endcode
 *
 * Run a tested `onnx_robust_video_matting` model without post-processing. <br>
 * @code {.c}
 * # $ test_nnctrl -b /tmp/multi_inputs_model/cv22_cavalry2.2.8.4_onnx_robust_video_matting.bin --dummy -e
 * # Input: 0 [r1i] dim: (1, 16, 135, 240), pitch: 960, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 2073600, phys: 0x607b9000, virt: 0x7f89790000
 * # Input: 1 [src] dim: (1, 3, 1080, 1920), pitch: 1920, dram_fmt: 0, bitvector: 0, data_fmt: (0, 0, 0, 0), loop_cnt: 1, size: 6220800, phys: 0x609b3400, virt: 0x7f8998a400
 * # Input: 2 [r4i] dim: (1, 64, 17, 30), pitch: 128, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 139264, phys: 0x60fa2000, virt: 0x7f89f79000
 * # Input: 3 [r3i] dim: (1, 40, 34, 60), pitch: 256, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 348160, phys: 0x60fc4000, virt: 0x7f89f9b000
 * # Input: 4 [r2i] dim: (1, 20, 68, 120), pitch: 480, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 652800, phys: 0x61019000, virt: 0x7f89ff0000
 * # Output: 0 [pha] dim: (1, 1, 1080, 1920), pitch: 7680, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 8294400, phys: 0x6275e800, virt: 0x7f8b735800
 * # Output: 1 [r1o] dim: (1, 16, 135, 240), pitch: 960, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 2073600, phys: 0x62f47800, virt: 0x7f8bf1e800
 * # Output: 2 [r2o] dim: (1, 20, 68, 120), pitch: 480, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 652800, phys: 0x6208ad80, virt: 0x7f8b061d80
 * # Output: 3 [r3o] dim: (1, 40, 34, 60), pitch: 256, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 348160, phys: 0x6212a380, virt: 0x7f8b101380
 * # Output: 4 [r4o] dim: (1, 64, 17, 30), pitch: 128, dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), loop_cnt: 1, size: 139264, phys: 0x62187f80, virt: 0x7f8b15ef80
 *
 * $ gst-launch-1.0 -v tensor_mux name=mux sync-mode=nosync ! tensor_filter framework=amba_cvflow model=/tmp/multi_inputs_model/cv22_cavalry2.2.8.4_onnx_robust_video_matting.bin \
 *   custom=in_name:r1i+src+r4i+r3i+r2i,out_name:pha+r1o+r2o+r3o+r4o,in_data_fmt:1.2.0.7+0.0.0.0+1.2.0.7+1.2.0.7+1.2.0.7 ! \
 *   queue ! tensor_demux name=demux demux.src_0 ! queue ! filesink location=/tmp/dst_1920x1080x1_f32.bin \
 *   demux.src_1 ! queue ! filesink location=/tmp/dst_240x135x16_f32.bin \
 *   demux.src_2 ! queue ! filesink location=/tmp/dst_120x68x20_f32.bin \
 *   demux.src_3 ! queue ! filesink location=/tmp/dst_60x34x40_f32.bin \
 *   demux.src_4 ! queue ! filesink location=/tmp/dst_30x17x64_f32.bin \
 *   filesrc location=/tmp/src_240x135x16_f32.bin blocksize=2073600 ! application/octet-stream ! tensor_converter input-dim=240:135:16:1 input-type=float32 ! queue ! mux.sink_0 \
 *   filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! queue ! mux.sink_1 \
 *   filesrc location=/tmp/src_30x17x64_f32.bin blocksize=130560 ! application/octet-stream ! tensor_converter input-dim=30:17:64:1 input-type=float32 ! queue ! mux.sink_2 \
 *   filesrc location=/tmp/src_60x34x40_f32.bin blocksize=326400 ! application/octet-stream ! tensor_converter input-dim=60:34:40:1 input-type=float32 ! queue ! mux.sink_3 \
 *   filesrc location=/tmp/src_120x68x20_f32.bin blocksize=652800 ! application/octet-stream ! tensor_converter input-dim=120:68:20:1 input-type=float32 ! queue ! mux.sink_4
 * @endcode
 *
 * <b>Machine Learning with RNN </b> <br>
 *
 * Running an RNN converted by the Amba CNNGEN tool is similar to running a typical NN. <br>
 *
 * Run a tested long short-term memory (LSTM) model without post-processing. <br>
 * @code {.c}
 * # $ test_nnctrl -b /tmp/lstm_model/warpctc_one_shot_cavalry.bin --dummy -e
 * # Total neural network num: 1
 * # Input: 0 [input] dim: (1, 3, 30, 80), pitch: 96, dram_fmt: 0, bitvector: 0, data_fmt: (0, 0, 8, 0), loop_cnt: 1, size: 8640, phys: 0x6042e000, virt: 0x7fb975d000
 * # Input: 1 [indicator] dim: (1, 1, 1, 1), pitch: 32, dram_fmt: 0, bitvector: 0, data_fmt: (0, 0, 0, 0), loop_cnt: 80, size: 2560, phys: 0x604301c0, virt: 0x7fb975f1c0
 * # Output: 0 [fc1] dim: (1, 80, 1, 11), pitch: 32, dram_fmt: 0, bitvector: 0, data_fmt: (1, 0, 1, 0), loop_cnt: 1, size: 2560, phys: 0x604592c0, virt: 0x7fb97882c0
 *
 * $ gst-launch-1.0 -v filesrc location=/tmp/lstm_model/00000-50337.bin blocksize=7200 ! application/octet-stream ! \
 *   tensor_converter input-dim=80:30:3:1 input-type=uint8 ! queue ! mux.sink_0 \
 *   filesrc location=/tmp/lstm_model/indicator.bin blocksize=1 ! application/octet-stream ! tensor_converter input- dim=1:1:1:1 input-type=uint8 ! queue ! mux.sink_1 \
 *   tensor_mux name=mux sync_mode=nosync ! queue ! tensor_filter framework=amba_cvflow model=/tmp/lstm_model/warpctc_one_shot_cavalry.bin \
 *   custom=in_name:input+indicator,out_name:fc1,in_data_fmt:0.0.8.0+0.0.0.0 ! queue ! filesink location=/tmp/nns_lstm_out.bin
 * @endcode
 *
 * @note
 * The number of input tensors in `tensor_filter` must be equal to the number of NN input feature maps.
 *
 * @subsubsection setup_encoding_params 2.4.4 Set Up Encoding Parameters
 *
 * This section demonstrates how to set up encoding parameters with the `amba_venccap` element or the `test_encode` application. <br>
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/dualvin_12_streams.lua --enc-mode 0
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_12_streams.lua --enc-mode 0
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv52_vin0_1_12_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv72_vin0_1_12_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * <b>Set parameters in the setup stage</b> <br>
 *
 * Set the encoding parameters via the `amba_venccap` element: <br>
 * @code {.c}
 * $ gst-launch-1.0 -v -e amba_venccap enc=stream_id:0,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,frame_factor:1/15,idr_interval:1,M:1,N:30,start:1,\
 *   stream_id:1,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,bitrate:1000000,N:150,start:1,\
 *   stream_id:2,stop:1,canvas-id:1,type:h265,stream-output:0.0.1280.720,bc:vbr,vbr_bitrate:10000~1000000,N:30,start:1,\
 *   stream_id:3,stop:1,canvas-id:1,type:h264,stream-output:0.0.1280.720,bitrate:800000,N:30,start:1,\
 *   stream_id:4,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,bitrate:150000,N:150,start:1,\
 *   stream_id:5,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,bitrate:10000,N:30,frame_factor:1/15,start:1 \
 *   ! amba_vencdemux name=dm dm.stream0 ! queue ! h265parse ! mp4mux ! filesink location=/tmp/h265.mp4
 * @endcode
 *
 * Set encoding parameters via the `test_encode` application first, then change the parameters using the `amba_venccap` element. <br>
 * @code {.c}
 * $ test_encode  -S 0 -b 0 -H 1080p --frame-factor 1/15 --idr 1 -M 1 -N 30 -e \
 *   -S 1 -b 0 -H 1080p --bitrate 1000000 -N 150 -e \
 *   -S 2 -b 1 -H 720p --bc vbr --vbr-bitrate 10000~1000000 -N 30 -e \
 *   -S 3 -b 1 -h 720p --bitrate 800000 -N 30 -e \
 *   -S 4 -b 2 -H 360p --bitrate 150000 -N 150 -e \
 *   -S 5 -b 2 -H 360p --bitrate 10000 -N 30 --frame-factor 1/15 -e \
 *   -S 6 -b 3 -H 2560x1440 --frame-factor 1/30 -e \
 *   -S 7 -b 3 -H 2560x1440 --bitrate 4000000 -N 300 -e \
 *   -S 8 -b 4 -H 720p --bitrate 1000000 -N 48 --frame-factor 4/5 -e \
 *   -S 9 -b 4 -h 720p --bitrate 800000 -N 40 --frame-factor 2/3 -e \
 *   -S 10 -b 5 -H 360p --bitrate 200000 -N 150 --frame-factor 1/2 -e \
 *   -S 11 -b 5 -H 360p --bitrate 10000 -N 30 --frame-factor 1/30 -e
 *
 * # Change encoding parameters via amba_venccap.
 * $ gst-launch-1.0 -v -e amba_venccap enc=stream_id:0,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,frame_factor:1/15,idr_interval:1,M:1,N:30,start:1,\
 *   stream_id:1,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,bitrate:1000000,N:150,start:1,\
 *   stream_id:2,stop:1,canvas-id:1,type:h265,stream-output:0.0.1280.720,bc:vbr,vbr_bitrate:10000~1000000,N:30,start:1,\
 *   stream_id:3,stop:1,canvas-id:1,type:h264,stream-output:0.0.1280.720,bitrate:800000,N:30,start:1,\
 *   stream_id:4,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,bitrate:150000,N:150,start:1,\
 *   stream_id:5,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,bitrate:10000,N:30,frame_factor:1/15,start:1 \
 *   ! amba_vencdemux name=dm dm.stream0 ! queue ! h265parse ! mp4mux ! filesink location=/tmp/h265.mp4
 * @endcode
 *
 * <b>Update Encoding Parameters at Runtime</b> <br>
 *
 * The following was set up in the GStreamer Daemon.
 * @code {.c}
 * # run gstd in local shell
 * $ gstd
 * # run client application in an external remote shell
 * $ gst-client
 *
 * # Request commands in gst-client below
 *
 * # Create pipeline
 * $ pipeline_create p1 amba_venccap name=venc enc=stream_id:0,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,start:1 \
 *   ! amba_vencdemux name=dm dm.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265.mp4
 * # play pipeline
 * $ pipeline_play p1
 * # change bitrate
 * $ element_set p1 venc enc stream_id:0,bitrate:1000000
 * # change absolute bitrate
 * $ element_set p1 venc enc stream_id:0,stop:1,abs-br:1,bitrate:1000000,start:1
 * # change vbr range
 * $ element_set p1 venc enc stream_id:0,vbr_bitrate:10000~1000000
 * # change bitrate control: cbr, vbr, cbr-quality, vbr-quality
 * $ element_set p1 venc enc stream_id:0,bc:cbr,bitrate:1000000
 * # force IDR
 * $ element_set p1 venc enc stream_id:0,force_idr:1
 * # stop encoding
 * $ element_set p1 venc enc stream_id:0,stop:1
 * # change resolution of canvas buffer and stream
 * $ element_set p1 venc enc stream_id:0,stop:1,chan-id:0,srcbuf-id:2,srcbuf-input:320.180.1280.720,srcbuf-output:0.0.640.480,stream-output:0.0.640.480,sar:1/1,start:1
 * # not ready: demux issue. change source buffer, frame_factor, idr_interval, M, N, codec type, stream-output and start encoding
 * $ element_set p1 venc enc stream_id:0,canvas-id:0,frame_factor:1/15,idr_interval:1,M:1,N:30,type:h265,stream-output:0.0.1280.720,start:1
 *
 * # send eos
 * $ event_eos p1
 * # stop pipeline
 * $ pipeline_stop p1
 * # destroy pipeline
 * # pipeline_delete p1
 * @endcode
 *
 * @subsubsection mimic_dual_vin_scenarios 2.4.5 Mimic Dual Video Input Scenarios
 *
 * This section mimics dual-VIN source scenarios. <br>
 *
 * @subsubsection example_mimic_dualvin_with_12s Example 5: Mimic Dual-VIN with 12 Streams
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * # for cv25, add  --check-disable-all 1
 * $ test_encode --resource-cfg /home/root/dualvin_12_streams.lua --enc-mode 0 --enc-dummy-latency 2
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_12_streams.lua --enc-mode 0 --enc-dummy-latency 2
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296  id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv52_vin0_1_12_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296  id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv72_vin0_1_12_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * $ modprobe cavalry
 * $ cavalry_load -f /lib/firmware/cavalry.bin -r
 * $ rtsp_server&
 * @endcode
 *
 * Run GstD: <br>
 * @code {.c}
 * # run gstd in local shell
 * $ gstd
 * # run client application in an external remote shell
 * $ gst-client
 * @endcode
 *
 * Run 12 streams in GstD: <br>
 * @code {.c}
 * # request commands in gst-client below
 *
 * # create pipeline
 * # For too many streams, it's needed to setup `alloc_mem=1` in amba_venccap element,
 * # `max-size-time=0 max-size-bytes=0 max-size-buffers=0` in queue.
 *
 * # a. creat a pipeline with setting encoding params in amba_venccap element.
 * $ pipeline_create p1 amba_venccap name=venc alloc_mem=1 enc=\
 *   stream_id:0,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,abs-br:1,bitrate:1000000,N:150,start:1,\
 *   stream_id:1,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,trigger_frame:1,N:1,start:1,\
 *   stream_id:2,stop:1,canvas-id:1,type:h265,stream-output:0.0.1280.720,abs-br:1,bitrate:750000,N:30,start:1,\
 *   stream_id:3,stop:1,canvas-id:1,type:h264,stream-output:0.0.1280.720,abs-br:1,bitrate:800000,N:30,start:1,\
 *   stream_id:4,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:150000,N:150,start:1,\
 *   stream_id:5,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:10000,N:60,frame_factor:1/30,start:1,\
 *   stream_id:6,stop:1,canvas-id:3,type:h265,stream-output:0.0.2560.1440,abs-br:1,bitrate:4000000,N:300,start:1,\
 *   stream_id:7,stop:1,canvas-id:3,type:h265,stream-output:0.0.2560.1440,trigger_frame:1,N:1,start:1,\
 *   stream_id:8,stop:1,canvas-id:4,type:h265,stream-output:0.0.1280.720,abs-br:1,bitrate:1000000,N:48,frame_factor:4/5,start:1,\
 *   stream_id:9,stop:1,canvas-id:4,type:h264,stream-output:0.0.1280.720,abs-br:1,bitrate:800000,N:40,frame_factor:2/3,start:1,\
 *   stream_id:10,stop:1,canvas-id:5,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:200000,N:150,frame_factor:1/2,start:1,\
 *   stream_id:11,stop:1,canvas-id:5,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:10000,N:60,frame_factor:1/60,start:1 \
 *   ! amba_vencdemux name=dm filename-base=/tmp/heic_0_%06d.heic \
 *   dm.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_0.mp4 \
 *   dm.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_2.mp4 \
 *   dm.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_0_3.mp4 \
 *   dm.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_4.mp4 \
 *   dm.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_5.mp4 \
 *   dm.stream6 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_0.mp4 \
 *   dm.stream8 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_2.mp4 \
 *   dm.stream9 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_1_3.mp4 \
 *   dm.stream10 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_4.mp4 \
 *   dm.stream11 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_5.mp4
 *
 * # b. create a pipleine, with `test_encode` app to setup encoding params.
 * $ test_encode -S 0 -b 0 -H 1080p --abs-br 1 --bitrate 1000000 -N 150 -e \
 *   -S 1 -b 0 -H 1080p --trigger-frame 1 -N 1 -e \
 *   -S 2 -b 1 -H 720p --abs-br 1 --bitrate 750000 -N 30 -e \
 *   -S 3 -b 1 -h 720p --abs-br 1 --bitrate 800000 -N 30 -e \
 *   -S 4 -b 2 -H 360p --abs-br 1 --bitrate 150000 -N 150 -e \
 *   -S 5 -b 2 -H 360p --abs-br 1 --bitrate 10000 -N 60 --frame-factor 1/30 -e \
 *   -S 6 -b 3 -H 2560x1440 --abs-br 1 --bitrate 4000000 -N 300 -e \
 *   -S 7 -b 3 -H 2560x1440 --trigger-frame 1 -N 1 -e \
 *   -S 8 -b 4 -H 720p --abs-br 1 --bitrate 1000000 -N 48 --frame-factor 4/5 -e \
 *   -S 9 -b 4 -h 720p --abs-br 1 --bitrate 800000 -N 40 --frame-factor 2/3 -e \
 *   -S 10 -b 5 -H 360p --abs-br 1 --bitrate 200000 -N 150 --frame-factor 1/2 -e \
 *   -S 11 -b 5 -H 360p --abs-br 1 --bitrate 10000 -N 60 --frame-factor 1/60 -e
 * $ pipeline_create p1 amba_venccap name=venc alloc_mem=1 ! amba_vencdemux name=dm heic-capture-id=1,7 filename-base=/tmp/heic_0_%06d.heic \
 *   dm.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_0.mp4 \
 *   dm.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_2.mp4 \
 *   dm.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_0_3.mp4 \
 *   dm.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_4.mp4 \
 *   dm.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_5.mp4 \
 *   dm.stream6 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_0.mp4 \
 *   dm.stream8 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_2.mp4 \
 *   dm.stream9 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_1_3.mp4 \
 *   dm.stream10 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_4.mp4 \
 *   dm.stream11 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_5.mp4
 *
 * # c. create a pipeline using frame factor 1/15 for trigger frame.
 * $ pipeline_create p1 amba_venccap name=venc alloc_mem=1 enc=\
 *   stream_id:0,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,abs-br:1,bitrate:1000000,N:150,start:1,\
 *   stream_id:1,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,frame_factor:1/30,N:1,start:1,\
 *   stream_id:2,stop:1,canvas-id:1,type:h265,stream-output:0.0.1280.720,abs-br:1,bitrate:750000,N:30,start:1,\
 *   stream_id:3,stop:1,canvas-id:1,type:h264,stream-output:0.0.1280.720,abs-br:1,bitrate:800000,N:30,start:1,\
 *   stream_id:4,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:150000,N:150,start:1,\
 *   stream_id:5,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:10000,N:60,frame_factor:1/30,start:1,\
 *   stream_id:6,stop:1,canvas-id:3,type:h265,stream-output:0.0.2560.1440,abs-br:1,bitrate:4000000,N:300,start:1,\
 *   stream_id:7,stop:1,canvas-id:3,type:h265,stream-output:0.0.2560.1440,frame_factor:1/30,N:1,start:1,\
 *   stream_id:8,stop:1,canvas-id:4,type:h265,stream-output:0.0.1280.720,abs-br:1,bitrate:1000000,N:48,frame_factor:4/5,start:1,\
 *   stream_id:9,stop:1,canvas-id:4,type:h264,stream-output:0.0.1280.720,abs-br:1,bitrate:800000,N:40,frame_factor:2/3,start:1,\
 *   stream_id:10,stop:1,canvas-id:5,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:200000,N:150,frame_factor:1/2,start:1,\
 *   stream_id:11,stop:1,canvas-id:5,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:10000,N:60,frame_factor:1/60,start:1 \
 *   ! amba_vencdemux name=dm \
 *   dm.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_0.mp4 \
 *   dm.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! amba_heicfilesink filename-base=/tmp/heic_0_%06d.heic \
 *   dm.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_2.mp4 \
 *   dm.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_0_3.mp4 \
 *   dm.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_4.mp4 \
 *   dm.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_5.mp4 \
 *   dm.stream6 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_0.mp4 \
 *   dm.stream7 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! amba_heicfilesink filename-base=/tmp/heic_1_%06d.heic \
 *   dm.stream8 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_2.mp4 \
 *   dm.stream9 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_1_3.mp4 \
 *   dm.stream10 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_4.mp4 \
 *   dm.stream11 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_5.mp4
 *
 * # play pipeline
 * $ pipeline_play p1
 *
 * # stop image capture streams (stream 1 and stream 7)
 * $ element_set p1 venc enc stream_id:1,stop:1
 * $ element_set p1 venc enc stream_id:7,stop:1
 * # start image capture stream (stream 1 and stream 7)
 * $ element_set p1 venc enc stream_id:1,start:1
 * $ element_set p1 venc enc stream_id:7,start:1
 *
 * # stop event trigger stream (stream 2 and stream 8)
 * $ element_set p1 venc enc stream_id:2,stop:1
 * $ element_set p1 venc enc stream_id:8,stop:1
 * # start event trigger stream (stream 2 and stream 8)
 * $ element_set p1 venc enc stream_id:2,start:1
 * $ element_set p1 venc enc stream_id:8,start:1
 *
 * # stop webRTC stream (stream 3 and stream 9)
 * $ element_set p1 venc enc stream_id:3,stop:1
 * $ element_set p1 venc enc stream_id:9,stop:1
 * # start webRTC trigger stream (stream 3 and stream 9)
 * $ element_set p1 venc enc stream_id:3,start:1
 * $ element_set p1 venc enc stream_id:9,start:1
 *
 * # stop hyperlapse stream (stream 5 and stream 11)
 * $ element_set p1 venc enc stream_id:5,stop:1
 * $ element_set p1 venc enc stream_id:11,stop:1
 * # start hyperlapse trigger stream (stream 3 and stream 9)
 * $ element_set p1 venc enc stream_id:5,start:1
 * $ element_set p1 venc enc stream_id:11,start:1
 *
 * # capture heic in stream id X
 * $ element_set p1 dm heic-capture-id 1,7
 *
 * # frame trigger image capture (stream 1 and stream 7)
 * $ element_set p1 venc enc stream_id:1,trigger_frame_num:1
 * $ element_set p1 venc enc stream_id:7,trigger_frame_num:1
 *
 * # bitrate control (stream X)
 * $ element_set p1 venc enc stream_id:X,stop:1,abs-br:1,bitrate:1000000,start:1
 *
 * # VIN fps (vin 1)
 * $ element_set p1 venc enc vsrc:1,vin_frame_rate:15
 *
 * # force IDR (stream 1 and stream 7)
 * $ element_set p1 venc enc stream_id:1,force_idr:1
 * $ element_set p1 venc enc stream_id:7,force_idr:1
 *
 * change webRCT stream resolution (stream 3 and stream 9)
 * $ element_set p1 venc enc stream_id:3,stop:1,stream-output:0.0.640.360,start:1
 * $ element_set p1 venc enc stream_id:9,stop:1,stream-output:0.0.640.360,start:1
 *
 * # send eos for pipeline
 * $ event_eos p1
 * # stop pipeline
 * $ pipeline_stop p1
 * # destory pipeline
 * $ pipeline_delete p1
 * @endcode
 *
 * Mimic running several NNs (yolov5, efficient net, tf_efficientdet_lite0): <br>
 * @code {.c}
 * # request commands in gst-client below
 *
 * $ pipeline_create p2 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 \
 *   label = /tmp/nn/in/coco_class_names.txt model = /tmp/nn/model/onnx_yolov5s_cavalry.bin type = yolov5s conf_threshold = 0.25 nms = 0.45 top_k = 100 \
 *   ! queue ! amba_venc_overlay stream_id = 0 alpha = 0 font = /tmp/arial.ttf clut_start = 22 clut_end = 70 color_number = 300 score_lmt = 0.25
 *
 * $ pipeline_create p3 amba_camsrc buf-id = 4 ! queue ! mlinference in_name = input out_name = 672  \
 *   model = /tmp/nn/model/efficientnet_cavalry.bin ! queue ! fakesink
 *
 * $ pipeline_create p4 amba_camsrc buf-id = 4 ! queue ! mlinference in_name = image_arrays out_name = Sigmoid out_name = ArgMax out_name = stack_2 \
 *   model = /tmp/nn/model/tf_efficientdet_lite0_cavalry.bin ! queue ! fakesink
 *
 * # play pipeline
 * $ pipeline_play p2
 * $ pipeline_play p3
 * $ pipeline_play p4
 *
 * # stop pipeline
 * $ pipeline_stop p2
 * $ pipeline_stop p3
 * $ pipeline_stop p4
 *
 * # delete pipeline
 * $ pipeline_delete p2
 * $ pipeline_delete p3
 * $ pipeline_delete p4
 * @endcode
 *
 * @subsubsection example_mimic_dualvin_with_8s Example 6: Mimic Dual-VIN with Eight Streams
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/dualvin_8_streams.lua --enc-mode 0
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_8_streams.lua --enc-mode 0
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296  id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv52_vin0_1_8_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296  id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv72_vin0_1_8_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * $ modprobe cavalry
 * $ cavalry_load -f /lib/firmware/cavalry.bin -r
 * $ rtsp_server&
 * @endcode
 *
 * Run GstD: <br>
 * @code {.c}
 * # run gstd in local shell
 * $ gstd
 * # run client application in an external remote shell
 * $ gst-client
 * @endcode
 *
 * Mimic an eight-stream recording scenario:
 * @code {.c}
 * # create a pipeline
 * $ pipeline_create p1 amba_venccap name=venc alloc_mem=1 enc=\
 *   stream_id:0,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,abs-br:1,bitrate:1000000,idr_interval:1,M:1,N:150,start:1,\
 *   stream_id:1,stop:1,canvas-id:1,type:h265,stream-output:0.0.1280.720,abs-br:1,bitrate:750000,N:30,start:1,\
 *   stream_id:2,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:150000,N:150,start:1,\
 *   stream_id:3,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:10000,N:60,frame_factor:1/30,start:1,\
 *   stream_id:4,stop:1,canvas-id:3,type:h265,stream-output:0.0.2560.1440,abs-br:1,bitrate:4000000,N:300,start:1,\
 *   stream_id:5,stop:1,canvas-id:4,type:h265,stream-output:0.0.1280.720,abs-br:1,bitrate:1000000,N:48,frame_factor:4/5,start:1,\
 *   stream_id:6,stop:1,canvas-id:5,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:20000,N:150,frame_factor:1/2,start:1,\
 *   stream_id:7,stop:1,canvas-id:5,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:10000,N:60,frame_factor:1/60,start:1 \
 *   ! amba_vencdemux name=dm dm.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_0.mp4 \
 *   dm.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_1.mp4 \
 *   dm.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_2.mp4 \
 *   dm.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_3.mp4 \
 *   dm.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_0.mp4 \
 *   dm.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_1.mp4 \
 *   dm.stream6 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_2.mp4 \
 *   dm.stream7 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_3.mp4
 *
 * # play pipeline
 * $ pipeline_play p1
 * # change framerate (frame factor, idr interval, M, N), bitrate, force IDR
 * $ element_set p1 venc enc stream_id:0,frame_factor:1/2,idr_interval:1,M:1,N:30
 * $ element_set p1 venc enc stream_id:0,stop:1,abs-br:1,bitrate:1000000,start:1
 * $ element_set p1 venc enc stream_id:0,force_idr:1
 *
 * # stop pipeline
 * $ event_eos p1
 * $ pipeline_stop p1
 * # delete pipeline
 * $ pipeline_delete p1
 * @endcode
 *
 * @code {.c}
 * # create a pipeline
 * $ pipeline_create p1 amba_venccap name=venc alloc_mem=1 enc=\
 *   stream_id:0,stop:1,canvas-id:0,type:h265,stream-output:0.0.1920.1080,abs-br:1,bitrate:1000000,idr_interval:1,M:1,N:150,start:1,\
 *   stream_id:1,stop:1,canvas-id:1,type:h264,stream-output:0.0.1280.720,abs-br:1,bitrate:800000,N:30,start:1,\
 *   stream_id:2,stop:1,canvas-id:2,type:h264,stream-output:0.0.640.360,abs-br:1,bitrate:400000,N:30,start:1,\
 *   stream_id:3,stop:1,canvas-id:2,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:10000,N:60,frame_factor:1/30,start:1,\
 *   stream_id:4,stop:1,canvas-id:3,type:h265,stream-output:0.0.2560.1440,abs-br:1,bitrate:4000000,N:300,start:1,\
 *   stream_id:5,stop:1,canvas-id:4,type:h264,stream-output:0.0.1280.720,abs-br:1,bitrate:800000,N:40,frame_factor:2/3,start:1,\
 *   stream_id:6,stop:1,canvas-id:5,type:h264,stream-output:0.0.640.360,abs-br:1,bitrate:400000,N:40,frame_factor:2/3,start:1,\
 *   stream_id:7,stop:1,canvas-id:5,type:h265,stream-output:0.0.640.360,abs-br:1,bitrate:10000,N:60,frame_factor:1/60,start:1 \
 *   ! amba_vencdemux name=dm dm.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_0.mp4 \
 *   dm.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_0_1.mp4 \
 *   dm.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_0_2.mp4 \
 *   dm.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_0_3.mp4 \
 *   dm.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_0.mp4 \
 *   dm.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_1_1.mp4 \
 *   dm.stream6 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux ! filesink location=/tmp/h264_1_2.mp4 \
 *   dm.stream7 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux ! filesink location=/tmp/h265_1_3.mp4
 *
 * # play pipeline
 * $ pipeline_play p1
 * # change bitrate, force IDR
 * $ element_set p1 venc enc stream_id:0,stop:1,abs-br:1,bitrate:1000000,start:1
 * $ element_set p1 venc enc stream_id:0,force_idr:1
 *
 * # stop pipeline
 * $ event_eos p1
 * $ pipeline_stop p1
 * # delete pipeline
 * $ pipeline_delete p1
 * @endcode
 *
 * Mimic running several NNs (YOLOv5, efficient net, efficientdet_lite0): <br>
 * @code {.c}
 * $ pipeline_create p2 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 \
 *   label = /tmp/nn/in/coco_class_names.txt model = /tmp/nn/model/onnx_yolov5s_cavalry.bin type = yolov5s conf_threshold = 0.25 nms = 0.45 top_k = 100 \
 *   ! queue ! amba_venc_overlay stream_id = 0 alpha = 0 font = /tmp/arial.ttf clut_start = 22 clut_end = 70 color_number = 300 score_lmt = 0.25
 *
 * $ pipeline_create p3 amba_camsrc buf-id = 4 ! queue ! mlinference in_name = input out_name = 672  \
 *   model = /tmp/nn/model/efficientnet_cavalry.bin ! queue ! fakesink
 *
 * $ pipeline_create p4 amba_camsrc buf-id = 4 ! queue ! mlinference in_name = image_arrays out_name = Sigmoid out_name = ArgMax out_name = stack_2 \
 *   model = /tmp/nn/model/tf_efficientdet_lite0_cavalry.bin ! queue ! fakesink
 *
 * # play pipeline
 * $ pipeline_play p2
 * $ pipeline_play p3
 * $ pipeline_play p4
 *
 * # stop pipeline
 * $ pipeline_stop p2
 * $ pipeline_stop p3
 * $ pipeline_stop p4
 *
 * # delete pipeline
 * $ pipeline_delete p2
 * $ pipeline_delete p3
 * $ pipeline_delete p4
 * @endcode
 *
 * @subsubsection jpeg_scenarios 2.4.6 JPEG Scenarios
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/dualvin.lua
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/cv28_dualvin.lua
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/cv52_vin0_1_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg /home/root/cv72_vin0_1_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * $ test_encode -A -h 1080p -b 0 -e -B -H 1080p -b 1 -e
 * @endcode
 *
 * YUV to JPEG: <br>
 * @code {.c}
 * # gst-launch-1.0 amba_camsrc buf-id = 0 ! jpegenc ! filesink location=/tmp/test.jpg
 * @endcode
 *
 * @subsubsection rtsp_scenarios 2.4.7 RTSP Scenarios
 *
 * GStreamer includes some RTSP / RTP /... protocols related elements.
 * This section demonstrates some cases about how to use and link these elements.
 * Currently, there are still some issues existed in `amba_venccap` when trying to work with these servers / clients.
 * Ambarella video encoding element would be improved in the future. <br>
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --hdmi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv52_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296 id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv72_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * $ modprobe cavalry
 * $ cavalry_load -f /lib/firmware/cavalry.bin -r
 * $ test_encode -A -H 1080p -b 0 -e -B -h 1080p -b 1 -e -C -H 480p -b 2 -e -D -h 480p -b 3 -e -E -H 480p -b 4 -e -S 5 -h 480p -b 5 -e
 * @endcode
 *
 * <b>RTSP</b> <br>
 * There is an example tool named `test-launch` in Gstreamer-rtsp-server plugin to
 * help create a RTSP server and test stream. The tool can be generated in the SDK path below: <br>
 * `/ambarella/out/yocto_out/cvxx/tmp/work/cortexaxx-poky-linux/gstreamer1.0-rtsp-server/x.xx.x-r0/build/examples/` <br>
 * To enable the RTSP server to send multiple streams, add a new tool named `test-launch-v2` in the unit test of amba-gst-plugin.
 * The `test-launch-v2` was modified from `test-lauch` and can be backward-compatible. <br>
 * @code {.c}
 * # VLC network URL below: rtsp://10.0.0.2:8554/test
 * # h264
 * $ ./test-launch "( amba_venccap ! amba_vencdemux name=d d.stream1 ! queue ! h264parse ! rtph264pay name=pay0 pt=96 )"
 * $ test-launch-v2 "( amba_venccap ! amba_vencdemux name=d d.stream1 ! queue ! h264parse ! rtph264pay name=pay0 pt=96 )"
 * # h265
 * $ ./test-launch "( amba_venccap ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! rtph265pay name=pay0 pt=96 )"
 * $ test-launch-v2 "( amba_venccap ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! rtph265pay name=pay0 pt=96 )"
 *
 * # 6 streams, just give a flow of creating a port with 6 mounts by test-launch-v2.
 * # Notice that `amba_venccap` cannot be called by different pipelines at the same time which would cause issues now.
 * # VLC network URL below: rtsp://10.0.0.2:8554/test0, rtsp://10.0.0.2:8554/test1, rtsp://10.0.0.2:8554/test2......
 * # "-c" was used for setup the counts of video streams or pipelines, default 1.
 * $ test-launch-v2 -c 6 "( amba_venccap stream-id= 0 ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! rtph265pay name=pay0 pt=96 )" \
 *   "( amba_venccap stream-id= 1 ! amba_vencdemux name=d d.stream1 ! queue ! h264parse ! rtph264pay name=pay0 pt=96 )" \
 *   "( amba_venccap stream-id= 2 ! amba_vencdemux name=d d.stream2 ! queue ! h265parse ! rtph265pay name=pay0 pt=96 )" \
 *   "( amba_venccap stream-id= 3 ! amba_vencdemux name=d d.stream3 ! queue ! h264parse ! rtph264pay name=pay0 pt=96 )" \
 *   "( amba_venccap stream-id= 4 ! amba_vencdemux name=d d.stream4 ! queue ! h265parse ! rtph265pay name=pay0 pt=96 )" \
 *   "( amba_venccap stream-id= 5 ! amba_vencdemux name=d d.stream5 ! queue ! h264parse ! rtph264pay name=pay0 pt=96 )"
 * @endcode
 *
 * <b>UDP</b> <br>
 * @code {.c}
 * # h265
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! rtph265pay ! queue ! udpsink host=127.0.0.1 port=8554
 * $ gst-launch-1.0 -e udpsrc port=8554 ! application/x-rtp,encoding-name=H265 ! queue ! rtph265depay ! queue ! h265parse ! qtmux ! filesink location=/tmp/h265_0.mp4
 * # h264
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=d d.stream1 ! queue ! h264parse ! rtph264pay ! queue ! udpsink host=127.0.0.1 port=8555
 * $ gst-launch-1.0 -e udpsrc port=8555 ! application/x-rtp,encoding-name=H264 ! queue ! rtph264depay ! queue ! h264parse ! qtmux ! filesink location=/tmp/h264_1.mp4
 * # 6 streams
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! rtph265pay ! queue ! udpsink host="127.0.0.1" port=8554 \
 *   d.stream1 ! queue ! h264parse ! rtph264pay ! queue ! udpsink host="127.0.0.1" port=8555 \
 *   d.stream2 ! queue ! h265parse ! rtph265pay ! queue ! udpsink host="127.0.0.1" port=8556 \
 *   d.stream3 ! queue ! h264parse ! rtph264pay ! queue ! udpsink host="127.0.0.1" port=8557 \
 *   d.stream4 ! queue ! h265parse ! rtph265pay ! queue ! udpsink host="127.0.0.1" port=8558 \
 *   d.stream5 ! queue ! h264parse ! rtph264pay ! queue ! udpsink host="127.0.0.1" port=8559
 * $ gst-launch-1.0 -e udpsrc port=8554 ! application/x-rtp,encoding-name=H265 ! queue ! rtph265depay ! queue ! h265parse ! qtmux name=mux ! filesink location=/tmp/h265_0.mp4 \
 *   -e udpsrc port=8555 ! application/x-rtp,encoding-name=H264 ! queue ! rtph264depay ! queue ! h264parse ! qtmux ! filesink location=/tmp/h264_1.mp4 \
 *   -e udpsrc port=8556 ! application/x-rtp,encoding-name=H265 ! queue ! rtph265depay ! queue ! h265parse ! qtmux ! filesink location=/tmp/h265_2.mp4 \
 *   -e udpsrc port=8557 ! application/x-rtp,encoding-name=H264 ! queue ! rtph264depay ! queue ! h264parse ! qtmux ! filesink location=/tmp/h264_3.mp4 \
 *   -e udpsrc port=8558 ! application/x-rtp,encoding-name=H265 ! queue ! rtph265depay ! queue ! h265parse ! qtmux ! filesink location=/tmp/h265_4.mp4 \
 *   -e udpsrc port=8559 ! application/x-rtp,encoding-name=H264 ! queue ! rtph264depay ! queue ! h264parse ! qtmux ! filesink location=/tmp/h264_5.mp4
 * @endcode
 *
 * <b>TCP</b> <br>
 * Report issues in `amba_venccap`: Buffer has no PTS. Just give a test flow now. <br>
 * @code {.c}
 * $ gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=d d.stream0 ! queue ! h265parse ! rtph265pay ! rtpstreampay ! queue ! tcpserversink host=127.0.0.1 port=8554
 * $ gst-launch-1.0 -e tcpclientsrc host=127.0.0.1 port=8554 do-timestamp=true ! application/x-rtp-stream,encoding-name=H265 ! queue ! rtpstreamdepay ! rtph265depay ! queue ! h265parse ! qtmux ! filesink location=/tmp/h265_0.mp4
 * @endcode
 *
 * @subsubsection debug_cases  2.4.8 Debug Cases
 *
 * <b>Validate Machine Learning </b> <br>
 *
 * The following demonstrates how to validate the outputs from NNs in file mode. <br>
 *
 * Prepare on the board: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_encode --hdmi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296  id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv52_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296  id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv72_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * $ modprobe cavalry
 * $ cavalry_load -f /lib/firmware/cavalry.bin -r
 * @endcode
 *
 * For the `ml_inference` element without post-processing, dump outputs of NN: <br>
 * @code {.c}
 * # yolov5
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue \
 *   ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 model = /tmp/nn/model/onnx_yolov5s_cavalry.bin dump=/tmp/dump.bin ! queue ! fakesink
 * # tiny yolov3
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue \
 *   ! mlinference in_name = data out_name = layer115-conv out_name = layer125-conv model = /tmp/nn/model/yolov3_fastest_xl_cavalry.bin dump=/tmp/dump.bin ! queue ! fakesink
 * # efficientnet
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue \
 *   ! mlinference in_name = input out_name = 672 model = /tmp/nn/model/efficientnet_cavalry.bin dump=/tmp/dump.bin ! queue ! fakesink
 * # tf_efficientdet_lite0
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue \
 *   ! mlinference in_name = image_arrays out_name = Sigmoid out_name = ArgMax out_name = stack_2 model = /tmp/nn/model/tf_efficientdet_lite0_cavalry.bin dump=/tmp/dump.bin ! queue ! fakesink
 * # movenet_lightning
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue \
 *   ! mlinference in_name = serving_default_input out_name = StatefulPartitionedCall model = /tmp/movenet_lightning/tf_movenet_lightning_cavalry.bin dump=/tmp/dump.bin ! queue ! fakesink
 * # movenet_thunder
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue \
 *   ! mlinference in_name = serving_default_input out_name = StatefulPartitionedCall model = /tmp/movenet_thunder/tf_movenet_thunder_cavalry.bin dump=/tmp/dump.bin ! queue ! fakesink
 * # fast_depth
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue \
 *   ! mlinference in_name = input.1 out_name = 424 model = /tmp/fast_depth/onnx_fast_depth_cavalry.bin dump=/tmp/dump.bin ! queue ! fakesink
 * @endcode
 *
 * For the `amba_cvflow` framework in `tensor_filter`, dump outputs of NN: <br>
 * @code {.c}
 * # yolov5
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow \
 *   model=/tmp/nn/model/onnx_yolov5s_cavalry.bin custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 ! queue ! filesink location=/tmp/result.bin
 * # tiny yolov3
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow \
 *   model=/tmp/nn/model/yolov3_fastest_xl_cavalry.bin custom=in_name:data,out_name:layer115-conv+layer125-conv,in_data_fmt:0.0.8.0 ! queue ! filesink location=/tmp/result.bin
 * # efficientnet
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow \
 *   model = /tmp/nn/model/efficientnet_cavalry.bin custom=in_name:input,out_name:672,in_data_fmt:0.0.0.0 ! queue ! filesink location=/tmp/result.bin
 * # tf_efficientdet_lite0
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow \
 *   model = /tmp/nn/model/tf_efficientdet_lite0_cavalry.bin custom=in_name:image_arrays,out_name:Sigmoid+ArgMax+stack_2,in_data_fmt:0.0.0.0 ! queue ! filesink location=/tmp/result.bin
 * # movenet_lightning
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow \
 *   model = /tmp/movenet_lightning/tf_movenet_lightning_cavalry.bin custom=in_name:serving_default_input,out_name:StatefulPartitionedCall,in_data_fmt:0.0.0.0 ! queue ! filesink location=/tmp/result.bin
 * # movenet_thunder
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow \
 *   model = /tmp/movenet_thunder/tf_movenet_thunder_cavalry.bin custom=in_name:serving_default_input,out_name:StatefulPartitionedCall,in_data_fmt:0.0.0.0 ! queue ! filesink location=/tmp/result.bin
 * # fast_depth
 * $ gst-launch-1.0 filesrc location=/tmp/IMX490_road_8.h264 ! h264parse ! avdec_h264 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow \
 *   model = /tmp/fast_depth/onnx_fast_depth_cavalry.bin custom=in_name:input.1,out_name:424,in_data_fmt:0.0.0.0 ! queue ! filesink location=/tmp/result.bin
 * @endcode
 *
 * Using the same inputs and the same models, compare the outputs of NNs when running each time. <br>
 *
 * <b>Validate Performance and Memory Leaks </b> <br>
 *
 * This section demonstrates how to test the performance of pipelines and validate memory leaks. <br>
 * For performance, set up `GST_DEBUG` as shown below at the beginning of `gst-launch-1.0`, and then obtain `avg frame diff` for the average time per frame in the log. <br>
 * @code {.c}
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 ...
 *
 * For example, in the log:
 * ...
 * avg frame diff 0:00:00.329551990
 * ...
 * @endcode
 *
 * For memory leaks, use the commandline below in another console to get `DIRTY` for CPU occupancy. <br>
 * @code {.c}
 * $ top -m
 * ...
 *  PID^^^VSZ^VSZRW   RSS (SHR) DIRTY (SHR) STACK COMMAND
 * ...
 * @endcode
 * Valgrind tool also can be used to make a checkout on memory leak. <br>
 * @code {.c}
 * $ make menuconfig
 *   Main menu                                                                                                                          ©¦
 *     -> meta                                                                                                                          ©¦
 *       -> recipes-devtools
 *         [*] valgrind (meta/recipes-devtools/valgrind)
 *
 * # check xxx on board
 * $ valgrind --leak-check=full xxx
 * @endcode
 * <br>
 * For VProc occupancy, use the tool `cavalry_top`. <br>
 * @code {.c}
 * $ cavalry_top
 * ...
 * PID     NID     VP%     CMD
 * ...
 * @endcode
 *
 * Check dynamic random access memory (DRAM) bandwidth statistics:<br>
 * @code {.c}
 * $ echo duration=10000 interval=1000 verbose=1 > /proc/ambarella/dram_statistics
 * $ cat /proc/ambarella/dram_statistics
 * @endcode
 *
 * Hardware encoding scenario: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * test_aaa_service -a &
 * $ test_encode --hdmi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv28
 * $ init.sh --imx274_mipi
 * test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_encode --mipi_dsi 1080p --resource-cfg /home/root/dualvin_sixstreams.lua
 *
 * # for cv52
 * $ init.sh --na; modprobe max9296  id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv52_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * # for cv72
 * $ init.sh --na; modprobe max9296  id=0x0303 vinc_id=0xb8; modprobe os08a10_mipi_brg fsync=1
 * $ test_aaa_service -a &
 * $ test_encode --resource-cfg cv72_vin0_1_6_streams.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * $ modprobe cavalry
 * $ cavalry_load -f /lib/firmware/cavalry.bin -r
 * $ test_encode -A -H 1080p -b 0 -e -B -H 1080p -b 1 -e -C -H 480p -b 2 -e -D -H 480p -b 3 -e -E -h 480p -b 4 -e -S 5 -h 480p -b 5 -e
 * $ rtsp_server&
 *
 * # amba_camsrc + mlinference (yolov5) + amba_venc_overlay
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 \
 *   label = /tmp/nn/in/coco_class_names.txt model= /tmp/nn/model/onnx_yolov5s_cavalry.bin \
 *   type = yolov5s conf_threshold = 0.25 nms = 0.45 top_k = 100 ! queue ! amba_venc_overlay stream_id = 0 alpha = 0 \
 *   font = /tmp/arial.ttf clut_start = 22 clut_end = 70 color_number = 300 score_lmt = 0.25
 *
 * # amba_camsrc + mlinference (tiny yolov3) + amba_venc_overlay
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = data out_name = layer115-conv out_name = layer125-conv \
 *   label = /tmp/nn/in/live_voc_labels.txt model = /tmp/nn/model/yolov3_fastest_xl_cavalry.bin \
 *   type = yolov3x conf_threshold = 0.8 nms = 0.3 top_k = 100 ! queue ! amba_venc_overlay stream_id = 0 alpha = 0 \
 *   font = /tmp/arial.ttf clut_start = 22 clut_end = 70 color_number = 300 score_lmt = 0.8
 *
 * # amba_camsrc + videoscale + videoconvert + mlinference (yolov5) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! videoscale ! video/x-raw,width=416,height=416,format=NV12 ! videoconvert ! video/x-raw,format=RGBP \
 *   ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 model= /tmp/nn/model/onnx_yolov5s_cavalry.bin ! queue ! fakesink
 *
 * # amba_camsrc + mlinference (yolov5) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = images out_name = 1037 out_name = 1017 out_name = 997 model= /tmp/nn/model/onnx_yolov5s_cavalry.bin ! queue ! fakesink
 *
 * # amba_camsrc + mlinference (tiny yolov3) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = data out_name = layer115-conv out_name = layer125-conv model= /tmp/nn/model/yolov3_fastest_xl_cavalry.bin ! queue ! fakesink
 *
 * # amba_camsrc + mlinference (efficientnet) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = input out_name = 672 model = /tmp/nn/model/efficientnet_cavalry.bin ! queue ! fakesink
 *
 * # amba_camsrc + mlinference (tf_efficientdet_lite0) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = image_arrays out_name = Sigmoid out_name = ArgMax out_name = stack_2 model = /tmp/nn/model/tf_efficientdet_lite0_cavalry.bin ! queue ! fakesink
 *
 * # amba_camsrc + mlinference (movenet_lightning) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = serving_default_input out_name = StatefulPartitionedCall model = /tmp/movenet_lightning/tf_movenet_lightning_cavalry.bin ! queue ! fakesink
 *
 * # amba_camsrc + mlinference (movenet_thunder) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = serving_default_input out_name = StatefulPartitionedCall model = /tmp/movenet_thunder/tf_movenet_thunder_cavalry.bin ! queue ! fakesink
 *
 * # amba_camsrc + mlinference (fast_depth) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! mlinference in_name = input.1 out_name = 424 model = /tmp/fast_depth/onnx_fast_depth_cavalry.bin ! queue ! fakesink
 *
 * # amba_camsrc + videoscale + videoconvert + tensor_converter + tensor_filter (yolov5) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! videoscale ! video/x-raw,width=416,height=416,format=NV12 ! videoconvert ! video/x-raw,format=RGBP ! queue ! tensor_converter \
 *   ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 ! queue ! fakesink
 *
 * # amba_camsrc + tensor_converter + tensor_filter (yolov5) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/onnx_yolov5s_cavalry.bin custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 ! queue ! fakesink
 *
 * # amba_camsrc + tensor_converter + tensor_filter (tiny yolov3) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model=/tmp/nn/model/yolov3_fastest_xl_cavalry.bin \
 *   custom=in_name:data,out_name:layer115-conv+layer125-conv,in_data_fmt:0.0.8.0 ! queue ! fakesink
 *
 * # amba_camsrc + tensor_converter + tensor_filter (efficientnet) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model = /tmp/nn/model/efficientnet_cavalry.bin custom=in_name:input,out_name:672,in_data_fmt:0.0.0.0 ! queue ! fakesink
 *
 * # amba_camsrc + tensor_converter + tensor_filter (tf_efficientdet_lite0) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model = /tmp/nn/model/tf_efficientdet_lite0_cavalry.bin \
 *   custom=in_name:image_arrays,out_name:Sigmoid+ArgMax+stack_2,in_data_fmt:0.0.0.0 ! queue ! fakesink
 *
 * # amba_camsrc + tensor_converter + tensor_filter (movenet_lightning) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model = /tmp/movenet_lightning/tf_movenet_lightning_cavalry.bin \
 *   custom=in_name:serving_default_input,out_name:StatefulPartitionedCall,in_data_fmt:0.0.0.0 ! queue ! fakesink
 *
 * # amba_camsrc + tensor_converter + tensor_filter (movenet_thunder) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model = /tmp/movenet_thunder/tf_movenet_thunder_cavalry.bin \
 *   custom=in_name:serving_default_input,out_name:StatefulPartitionedCall,in_data_fmt:0.0.0.0 ! queue ! fakesink
 *
 * # amba_camsrc + tensor_converter + tensor_filter (fast_depth) + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 amba_camsrc buf-id = 0 ! queue ! tensor_converter ! tensor_filter framework=amba_cvflow model = /tmp/fast_depth/onnx_fast_depth_cavalry.bin \
 *   custom=in_name:input.1,out_name:424,in_data_fmt:0.0.0.0 ! queue ! fakesink
 *
 * # amba_venccap + amba_vencdemux + h265parse/h264parse + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 -e amba_venccap ! amba_vencdemux name=d d.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! fakesink \
 *   d.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! fakesink \
 *   d.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! fakesink \
 *   d.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! fakesink \
 *   d.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! fakesink \
 *   d.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! fakesink
 *
 * # For mux related elements, do not use `top -m` to check memory. Use valgrind tool instead if enable.
 *
 * # alsasrc + opusenc + mp4mux + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 -e alsasrc ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! opusenc ! mp4mux name=mux0 ! fakesink
 *
 * # alsasrc + avenc_aac + mp4mux + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 -e alsasrc ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! avenc_aac ! mp4mux name=mux0 ! fakesink
 *
 * # amba_venccap + amba_vencdemux + h265parse + mp4mux + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 -e amba_venccap sync=true ! amba_vencdemux name=d d.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mp4mux name=mux0 ! fakesink
 *
 * # amba_venccap + amba_vencdemux + h264parse + mp4mux + fakesink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 -e amba_venccap sync=true ! amba_vencdemux name=d d.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mp4mux name=mux0 ! fakesink
 *
 * # six streams h265/h264 + opus
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 -e alsasrc ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! opusenc ! tee name=t t.src_0 ! mp4mux name=mux0 ! fakesink \
 *   -e amba_venccap sync=true ! amba_vencdemux name=d d.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux0. \
 *   t.src_1 ! mp4mux name=mux1 ! fakesink d.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux1. \
 *   t.src_2 ! mp4mux name=mux2 ! fakesink d.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux2. \
 *   t.src_3 ! mp4mux name=mux3 ! fakesink d.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux3. \
 *   t.src_4 ! mp4mux name=mux4 ! fakesink d.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux4. \
 *   t.src_5 ! mp4mux name=mux5 ! fakesink d.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux5.
 *
 * # six streams h265/h264 + aac
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 -e alsasrc ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! avenc_aac ! tee name=t t.src_0 ! mp4mux name=mux0 ! fakesink \
 *   -e amba_venccap sync=true ! amba_vencdemux name=d d.stream0 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux0. \
 *   t.src_1 ! mp4mux name=mux1 ! fakesink d.stream1 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux1. \
 *   t.src_2 ! mp4mux name=mux2 ! fakesink d.stream2 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux2. \
 *   t.src_3 ! mp4mux name=mux3 ! fakesink d.stream3 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h265parse ! mux3. \
 *   t.src_4 ! mp4mux name=mux4 ! fakesink d.stream4 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux4. \
 *   t.src_5 ! mp4mux name=mux5 ! fakesink d.stream5 ! queue max-size-time=0 max-size-bytes=0 max-size-buffers=0 ! h264parse ! mux5.
 * @endcode
 *
 * Hardware decoding scenario: <br>
 * @code {.c}
 * # for cv22/cv25
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ test_vout --hdmi 1080p
 *
 * # for cv28, not support for mipi_dsi in amba_hwvdec now, skip
 * $ init.sh --imx274_mipi
 * $ test_aaa_service -a &
 * $ modprobe lcd_r9611
 * $ test_vout --mipi_dsi 1080p
 *
 * # filesrc + qtdemux + opusdec + audioconvert + autoaudiosink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 filesrc location=h264_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! opusdec ! audioconvert ! autoaudiosink
 *
 * # filesrc + qtdemux + avdec_aac + audioconvert + autoaudiosink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 filesrc location=h264_aac.mp4 ! qtdemux name=demuxer demuxer. ! queue ! avdec_aac ! audioconvert ! autoaudiosink
 *
 * # filesrc + qtdemux + h264parse + amba_hwvdec + amba_vsink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 filesrc location=h264_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! h264parse ! amba_hwvdec ! amba_vsink
 *
 * # filesrc + qtdemux + h265parse + amba_hwvdec + amba_vsink
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 filesrc location=h265_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! h265parse ! amba_hwvdec ! amba_vsink
 *
 * # Audio(opus) + Video(h264)
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 filesrc location=h264_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! opusdec ! audioconvert ! autoaudiosink \
 *   demuxer. ! queue ! h264parse ! amba_hwvdec ! amba_vsink
 *
 * # Audio(opus) + Video(h265)
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 filesrc location=h265_opus.mp4 ! qtdemux name=demuxer demuxer. ! queue ! opusdec ! audioconvert ! autoaudiosink \
 *   demuxer. ! queue ! h265parse ! amba_hwvdec ! amba_vsink
 *
 * # Audio(aac) + Video(h264)
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 filesrc location=h264_aac.mp4 ! qtdemux name=demuxer demuxer. ! queue ! avdec_aac ! audioconvert ! autoaudiosink \
 *   demuxer. ! queue ! h264parse ! amba_hwvdec ! amba_vsink
 *
 * # Audio(aac) + Video(h265)
 * $ GST_DEBUG=basesink:6 gst-launch-1.0 filesrc location=h265_aac.mp4 ! qtdemux name=demuxer demuxer. ! queue ! avdec_aac ! audioconvert ! autoaudiosink \
 *   demuxer. ! queue ! h265parse ! amba_hwvdec ! amba_vsink
 * @endcode
 *
 * @subsubsection use_in_lychee  2.4.9 Use GStreamer in Lychee OS
 * This section demonstrates how to use GStreamer in <b> Lychee OS </b>,
 * including media file playback, live camera capture, and neural network (NN) inference. <br>
 * @note
 * Try the flows below after executing @ref lychee_os_install_lycheeos_on_cv3
 * "install and set up Lychee OS" and enable dual-VOUT correctly. <br>
 *
 * Prepare after login <b> Lychee OS </b>: <br>
 * The Lua configuration file `cv3_6vin_1080p_linear.lua` for six-cam-vin and shell script `start_prev.sh`
 * to start preview are under the path in SDK: `ambarella\app\robotics\6v_yolop_yolov5\scripts` <br>
 * Ambarella recommends placing them under the `~/` in Lychee.
 *
 * @code {.c}
 * # install amba gstremer solution related rpms
 * Lychee$ sudo dnf update --refresh
 * Lychee$ sudo dnf install gstreamer1-devel gstreamer1-plugins-base-devel alsa-lib-devel
 * Lychee$ sudo dnf install libamba-lwapputils-devel libamba_gst_plugins libamba_nnstreamer
 * # start preview
 * Lychee$ cd ~
 * Lychee$ chmod 755 start_prev.sh
 * Lychee$ ./start_prev.sh
 * @endcode
 *
 * @subsubsection example_file_playback_display Example 7: Video Decode and Display
 * Refer to the `waylandsink` and `xvimagesink` elements in gstreamer; the following shows how to decode video file and
 * native display on Lychee desktop. <br>
 *
 * Decode h.264 and display with waylandsink: <br>
 * @code {.c}
 * Lychee$ gst-launch-1.0 filesrc location=~/tmp_data/test.h264 ! h264parse ! avdec_h264 ! \
 *         videoconvert ! queue ! videoscale ! video/x-raw,width=640,height=360 ! queue ! waylandsink
 * @endcode
 *
 * Decode mp4 and display video with xvimagesink: <br>
 * @code {.c}
 * Lychee$ gst-launch-1.0 filesrc location=~/tmp_data/IMX490_road_8_h264.mp4 ! qtdemux name=demuxer demuxer. ! queue ! h264parse ! avdec_h264 ! \
 *         videoconvert ! queue ! videoscale ! video/x-raw,width=640,height=360 ! queue ! xvimagesink
 * @endcode
 *
 * Decode multiple h.264 files and display compositely: <br>
 * @code {.c}
 * Lychee$ gst-launch-1.0 compositor name=comp \
 *         sink_0::xpos=0 sink_0::ypos=0 sink_0::width=640 sink_0::height=360 \
 *         sink_1::xpos=640 sink_1::ypos=0 sink_1::width=640 sink_1::height=360 \
 *         sink_2::xpos=1280 sink_2::ypos=0 sink_2::width=640 sink_2::height=360 \
 *         sink_3::xpos=0 sink_3::ypos=360 sink_3::width=640 sink_3::height=360 \
 *         sink_4::xpos=640 sink_4::ypos=360 sink_4::width=640 sink_4::height=360 \
 *         sink_5::xpos=1280 sink_5::ypos=360 sink_5::width=640 sink_5::height=360 ! \
 *         videoconvert ! queue ! xvimagesink sync=false \
 *         filesrc location=~/tmp_data/test.h264 ! h264parse ! avdec_h264 ! comp.sink_0 \
 *         filesrc location=~/tmp_data/test.h264 ! h264parse ! avdec_h264 ! comp.sink_1 \
 *         filesrc location=~/tmp_data/test.h264 ! h264parse ! avdec_h264 ! comp.sink_2 \
 *         filesrc location=~/tmp_data/test.h264 ! h264parse ! avdec_h264 ! comp.sink_3 \
 *         filesrc location=~/tmp_data/test.h264 ! h264parse ! avdec_h264 ! comp.sink_4 \
 *         filesrc location=~/tmp_data/test.h264 ! h264parse ! avdec_h264 ! comp.sink_5
 * @endcode
 *
 * @subsubsection example_camera_capture Example 8: Capture Live Camera and Display
 * Refer to the `waylandsink` and `xvimagesink` elements in GStreamer; the following shows how to capture live camera streams
 * from `amba_camsrc` and native display on Lychee desktop. <br>
 *
 * Capture single camera and display with waylandsink: <br>
 * @code {.c}
 * Lychee$ gst-launch-1.0 -v amba_camsrc buf-id=0 ! queue ! \
 *         videoconvert ! videoscale ! video/x-raw,width=640,height=360 ! waylandsink
 * @endcode
 *
 * Capture single camera and display with xvimagesink: <br>
 * @code {.c}
 * Lychee$ gst-launch-1.0 -v amba_camsrc buf-id=0 ! queue ! \
 *         videoconvert ! videoscale ! video/x-raw,width=640,height=360 ! xvimagesink
 * @endcode
 *
 * Capture six camera streams and display compositely: <br>
 * @code {.c}
 * Lychee$ gst-launch-1.0 compositor name=comp \
 *         sink_0::xpos=0 sink_0::ypos=0 sink_0::width=640 sink_0::height=360 \
 *         sink_1::xpos=640 sink_1::ypos=0 sink_1::width=640 sink_1::height=360 \
 *         sink_2::xpos=1280 sink_2::ypos=0 sink_2::width=640 sink_2::height=360 \
 *         sink_3::xpos=0 sink_3::ypos=360 sink_3::width=640 sink_3::height=360 \
 *         sink_4::xpos=640 sink_4::ypos=360 sink_4::width=640 sink_4::height=360 \
 *         sink_5::xpos=1280 sink_5::ypos=360 sink_5::width=640 sink_5::height=360 ! \
 *         queue ! videoconvert ! queue ! xvimagesink \
 *         amba_camsrc buf-id=0 ! queue ! comp.sink_0 \
 *         amba_camsrc buf-id=1 ! queue ! comp.sink_1 \
 *         amba_camsrc buf-id=2 ! queue ! comp.sink_2 \
 *         amba_camsrc buf-id=3 ! queue ! comp.sink_3 \
 *         amba_camsrc buf-id=4 ! queue ! comp.sink_4 \
 *         amba_camsrc buf-id=5 ! queue ! comp.sink_5
 * @endcode
 *
 * @subsubsection example_fileinput_nn_inference_display Example 9: NNStreamer Inference and Result Display
 *
 * Refer to the `amba_cvflow` framework in the sub-plugin of the modified `tensor_filter` element.
 * The following demonstrates how to run NN models with the file input and compositely display
 * the original image and results on Lychee desktop. <br>
 *
 * Decode h.264 file, feed to yolov5s model for NN inference and display results in Lychee: <br>
 * @code {.c}
 * Lychee$ gst-launch-1.0 -v filesrc location=~/tmp_data/test.h264 ! h264parse ! avdec_h264 ! queue ! \
 *         videoconvert ! videoscale ! video/x-raw,width=1280,height=720,format=RGBP ! tee name=t \
 *         t. ! queue ! videoscale ! video/x-raw,width=416,height=416 ! tensor_converter ! \
 *         tensor_filter framework=amba_cvflow model=~/tmp_data/cv3_yolov5s.bin custom=in_name:images,out_name:1037+1017+997,in_data_fmt:0.0.8.0 ! \
 *         tensor_decoder mode=bounding_boxes option1=amba_yolov5 option2=~/tmp_data/coco_class_names.txt option4=1280:720 option5=416:416 ! \
 *         comp.sink_0 \
 *         t. ! queue ! comp.sink_1 \
 *         compositor name=comp sink_0::zorder=2 sink_1::zorder=1 ! videoconvert ! xvimagesink
 * @endcode
 *
 * @subsubsection known_issues  2.4.10 Known Issues
 *
 * <b>Stuck in the `amba_vencdemux` element:</b> <br>
 * When running with too many streams, `alloc_mem=1` in the `amba_venccap` element and
 * `max-size-time=0 max-size-bytes=0 max-size-buffers=0` in the `queue` element must be set up.<br>
 *
 * <b>Stuck when playbacking (hardware decoding) video and audio at the same time:</b> <br>
 * Users can set the parameter `async=false` in the sink element. <br>
 *
 * <b> Issues of overlay, hardware decoder for DSP v6 </b> <br>
 * Not ready on CV52 / CV72 /CV3 now.
 *
 * <b> RTSP / RTP issues when working with `amba_venccap` </b> <br>
 * Some test flows are provided regarding how to link with some RTSP / RTP related elements.
 * Amba Venc element needs to be improved in the future.
 * For example, it is required to enable call Ambarella video encoding element by different pipelines at the same time and
 * fix the PTS issue when working with some servers / clients.
 *
 * @subsubsection notice  2.4.11 Notice
 *
 * <b>Start the GStreamer Daemon:</b> <br>
 * @code {.c}
 * # By default, for the newer version gstd_0.15.0 in recipe-oss, simply run GstD as shown below: <br>
 * $ gstd
 *
 * # For the Yocto community version of GstD (1.0+really0.8.0) in recipe-multimeida, run GstD as shown below: <br>
 * $ gstd -D
 * @endcode
 *
 */
/*!
 * @file doc_lib_asf.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2022-05-17
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
 * @page page_lib_asf_doc Ambarella Simulation Framework Library API
 *
 * @section asf_history 0. Revision History
 *
 * <table>
 * <caption id="asf_lib_rev_history"></caption>
 * <tr><th> Library Version	<th align="left"> Updated Date	<th align="left"> Modification
 * <tr><td> 0.0.2    <td>20220517    <td> Initial Version
 * <tr><td> 0.0.2    <td>20230227    <td> Added more JSON examples
 * <tr><td> 0.0.2    <td>20230412    <td> Added troubleshooting sections. Updated compile steps
 * for common plugin version 0.2.0.
 * </table>
 *
 * - - - -
 *
 * @section asf_intro 1. ASF Introduction
 *
 * @subsection asf_intro_overview 1.1 Overview
 * The Ambarella simulation framework (ASF) provides a solution: per the developer's
 * requirements, ASF captures remote data in one time-space and simulates it locally in
 * another time-space.
 * Through the simulation, developers can get the same test environment and real data as the
 * remote side, which is more efficient and user-friendly for debugging or algorithm optimization.
 *
 * @par Advantages:
 * - ASF can be deployed easily to any Ambarella camera to record data from multiple different
 * devices (inertial measurement unit (IMU), radar, lidar, vision sensor, controller area network
 * (CAN), and more), repack on PC or Arm®, and replay on the same hardware board.
 * - Unified format: based on ASF format, customers can migrate the development of the "replay"
 * stage among different Ambarella platforms (from CV2x to CV5x, or CV3 and future chips).
 * - Database: customers can easily search, select, split, merge, and view the "recorded" data.                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          graphical user interface (GUI) tool.
 * - Time stamp accuracy: customers can align multiple devices in the same time domain and adjust
 * the data in the repack and replay stages.
 *
 * @subsection asf_intro_3r 1.2 Record, Repack, and Replay
 *
 * Within this framework, there are three main processes: record, repack, and replay.
 * @par Record
 * Capture and store data blocks continuously from the data provider. The database is also used to
 * record key data information.
 * @par Repack
 * According to the data information in the database, repack data sequences with specified rules
 * (such as presentation time stamp (PTS), device dependencies, and more).
 * @par Replay
 * Replay the repacked data on the local device.
 *
 * @image html 3r.png "Figure 1-1. Record, Repack, and Replay."
 *
 * @subsection asf_intro_structure 1.3 Data Structure
 * @image html asf_structure.png "Figure 1-2. Data Structure."
 *
 * The following tables provide details of the ASF data structure.
 * @par struct asf_block_info
 * <table>
 * <caption id="asf_block_info"></caption>
 * <tr><th align="left">Item<th align="left">Description
 * <tr><td><B>type</B><td> @ref asf_block_type
 * <tr><td><B>enable</B><td>Block enable flag
 * <tr><td><B>unit_size</B><td>Block data unit size
 * <tr><td><B>unit_num</B><td>Block data unit number
 * <tr><td><B>offset</B><td>Start offset of block data from @ref asf_header
 * <tr><td><B>crc</B><td>Cyclic redundancy check (CRC) value for block data integrity check
 * <tr><td><B>dev_id</B><td>Device ID for block
 * <tr><td><B>sys_time</B><td>Capture time based on system timer
 * <tr><td><B>mono_time</B><td>Capture time based on hardware timer
 * <tr><td><B>user_time</B><td>Reserved for user-defined timer
 * </table>
 *
 * @par struct asf_header
 * <table>
 * <caption id="asf_header"></caption>
 * <tr><th align="left">Item<th align="left">Description
 * <tr><td><B>magic_number</B><td> @ref ASF_HEADER_MAGIC
 * <tr><td><B>version</B><td> @ref asf_header_version
 * <tr><td><B>header_size</B><td>ASF cluster header size
 * <tr><td><B>data_size</B><td>Total ASF cluster data size
 * <tr><td><B>block_num</B><td>ASF cluster block number
 * <tr><td><B>crc</B><td>CRC value for ASF data integrity check
 * <tr><td><B>descriptor</B><td>ASF descriptor
 * <tr><td><B>block_info</B><td> @ref asf_block_info
 * </table>
 *
 * - - - -
 *
 * @section asf_record 2. Record
 * @image html general_record_flow.png "Figure 2-1. Record Flow."
 *
 * @subsection asf_record_type 2.1 Supported Record Data Types
 * The record process currently supports the following data types:
 * - System
 * - Sensor
 * - Gyro
 * - Bitstream
 *
 * For data type details, see section @ref asf_record_plugin.
 *
 * @subsection asf_record_plugin 2.2 Record Plugins
 * In order to more flexibly expand various data recordings, ASF uses plugins to meet this
 * requirement.
 *
 * @subsubsection asf_record_plugin_type 2.2.1 Customized Record Data Types
 * The following table details the storage types that Ambarella currently supports in the plugin method.
 * <table>
 * <caption id="supported_plugin"></caption>
 * <tr><th align="left">Module<th align="left">Plugin<th align="left">Data Type<th align="left">
 * Info Type<th align="left">Option<th align="left">Description
 * <tr><td><B>Sensor</B><td>libasf_common.so <td> @ref ASF_BLOCK_SENSOR <td>
 * @ref ASF_HW_INFO_BLOCK_SENSOR <td><B>vsrc_id</B><td>Video source (vsrc) ID
 * <tr><td rowspan="2"><B>Gryo</B><td rowspan="2">libasf_common.so <td rowspan="2"> @ref ASF_BLOCK_GYRO <td rowspan="2">
 * @ref ASF_HW_INFO_BLOCK_GYRO <td><B>id</B><td>Video input (VIN) ID
 * <tr><td><B>shift_realtime_enable</B><td>Calculate gyro initial shift before recording
 * <tr><td><B>Stream</B><td>libasf_common.so <td> @ref ASF_BLOCK_BITSTREAM <td>None<td><B>id</B>
 * <td>Stream ID
 * </table>
 *
 * @subsubsection asf_record_plugin_add_new 2.2.2 Adding New Customized Plugins
 * @par Plugin Layout
 * A plugin consists of single or multiple modules. Modules are the smallest elements of a plugin.
 * In general, a module at most contains two recording data processes. One process
 * capture data frequently and save it as a data cluster. The other process is only required to
 * capture data once and save it as an infomation cluster.
 * @image html library_layout.png "Figure 2-1. ASF Library Layout."
 *
 * @par Implement Module Functions
 * During the recording process, once a module is created, its related information will be recorded
 * in the following structure:
 * <table>
 * <caption id="asf_block_obj"></caption>
 * <tr><th align="left">Item<th align="left">Description
 * <tr><td><B>type</B><td> @ref asf_block_type
 * <tr><td><B>info_type</B><td> @ref asf_block_type
 * <tr><td><B>dev_id</B><td>Module device ID
 * <tr><td><B>uuid</B><td>Module unique universal identification (UUID)
 * <tr><td><B>name</B><td>Module name
 * <tr><td><B>serial_id</B><td>Moulde serial ID
 * <tr><td><B>description</B><td>Module description
 * <tr><td><B>mono_freq</B><td> @ref ASF_DEFAULT_MONO_PTS_FREQ
 * <tr><td><B>priv_data</B><td> Module private data pointer
 * <tr><td><B>ops</B><td> @ref asf_block_ops
 * </table>
 * The following functions in @ref asf_block_ops must be realized in each module.
 * <table>
 * <caption id="ops function"></caption>
 * <tr><th align="left">Function<th align="left">Description
 * <tr><td>int (\*data_query)(void \*args, struct asf_block\* block)<td>Data query function
 * <tr><td>int (\*info_query)(void \*args, struct asf_block\* block)<td>Infoquery function
 * <tr><td>int (\*is_finish)(void)<td>Extra exit if required; Return "0" for no extra exit
 * </table>
 *
 * @par Implement Plugin Functions
 * The following functions must be realized in each plugin:
 * <table>
 * <caption id="plugin function"></caption>
 * <tr><td>int asf_get_module_num(void)<td>Get module number in plugin
 * <tr><td>int asf_get_module_name(u32 index, char \*name)<td>Get module name in plugin through index
 * <tr><td>struct asf_block_obj\* asf_create_module(char \*name, cJSON \*cfg)<td>Create module with
 * specified module name
 * <tr><td>int asf_delete_module(struct asf_block_obj \*obj)<td>Delete module
 * <tr><td>void asf_get_plugin_version(struct asf_plugin_version \*version)<td>Get plugin version
 * information
 * </table>
 *
 * @par Add Makefile
 * Add the plugin makefile command in `ambarella/packages/asf/source/make.inc`.
 * @note
 * For more details, see the example in `ambarella/packages/asf/source/plugin_common/asf_common_plugin.c`.
 *
 * @subsection asf_record_json 2.3 Record Configuration
 * @subsubsection asf_record_json_mode 2.3.1 Record Mode and Event
 * @par Standard Mode
 * Record only once with a specified duration after an application starts.
 * @par Trigger Mode
 * Data is temporarily stored in a ring buffer after the application starts. Users can save the data to a
 * file by triggering an event.
 * @par Event
 * <B>Event</B> is introduced to distinguish the multiple recording actions in trigger mode.
 * Each recording action is an event. When a recording application is running, the application logs
 * the start and end time of the event in the database. In standard mode, as there is only one
 * recording action and only one event.
 *
 * @subsubsection asf_record_json_config 2.3.2 Configuration
 * ASF recording uses JavaScript Object Notation (JSON) format text as a configuration file.
 * @par Example: Record stream 0 in trigger mode
 * @code {.json}
 * {
 *     "plugin": [
 *         {
 *             "path": "/usr/lib/libasf_common.so",
 *             "module": [
 *                 {
 *                     "name": "stream",
 *                     "cfg": {
 *                         "id": 0
 *                     }
 *                 },
 *             ]
 *         }
 *     ],
 *     "system": {
 *         "db_path": "/tmp/test.db",
 *         "file_path": "/tmp",
 *         "file_name": "sample.bin",
 *         "file_size_limit_MB": 30,
 *         "cache_size_limit_MB": 32,
 *         "duration_second": 3,
 *         "mode": "trigger"
 *     }
 * }
 * @endcode
 *
 * @par Example: Record in standard mode for 10 seconds
 * @code {.json}
 * {
 *  ...
 *     "system": {
 *         "db_path": "/tmp/test.db",
 *         "file_path": "/tmp",
 *         "file_name": "sample.bin",
 *         "file_size_limit_MB": 30,
 *         "cache_size_limit_MB": 32,
 *         "duration_second": 10,
 *         "mode": "standard"
 *     }
 * }
 * @endcode
 *
 * The following lists general option node details in configurations:
 * <table>
 * <caption id="record options"></caption>
 * <tr><th align="left">Node<th align="left">Value Type<th align="left">Description
 * <tr><td><B>plugin</B><td>Array Node<td>Array node for all plugin binaries
 * <tr><td><B>path</B><td>String<td>Plugin binary path
 * <tr><td><B>module</B><td>Array Node<td>Array node for module enabled in plugin binary
 * <tr><td><B>name</B><td>String<td>Module name for parent module node
 * <tr><td><B>cfg</B><td>Node<td>Configuration node for parent module node;
 * content is customized by the plugin module
 * <tr><td><B>system</B><td>Node<td>Node for general configurations
 * <tr><td><B>db_path</B><td>String<td>Record database path
 * <tr><td><B>file_path</B><td>String<td>Record data binary store path
 * <tr><td><B>file_name</B><td>String<td>Record data binary name
 * <tr><td><B>file_size_limit_MB</B><td>Number<td>For large amounts of data, the recording of
 * data binaries is split into several blocks. This option determines the maximum size of a
 * single block
 * <tr><td><B>cache_size_limit_MB</B><td>Number<td>Temporary memory size in trigger mode
 * <tr><td><B>duration_second</B><td>Number<td>Record duration in standard mode
 * <tr><td><B>mode</B><td>String<td>Mode option: "trigger" or "standard"
 * </table>
 *
 * @note
 * Users can find the sample JSON record in `ambarella/packages/asf/unit_test/json_sample`.
 *
 * @subsubsection asf_record_trigger_mode 2.3.3 Record in Trigger Mode
 * Different from standard mode, the application will keep running in trigger mode until it is
 * manually stopped by the user. Events are triggered by a specific message through the socket.
 * The message should be sent in the format "cap:[pre second]:[post second]"; "pre second"
 * represents the amount of time that the user wants to capture in the cache, while "post second"
 * represents the amount of time that the user wants to capture during a livestream.
 * The valid previous time duration depends the size of the cache configured by the
 * user (<B>cache_size_limit_MB</B>). If the "pre second" duration is greater than the total cache
 * time duration, the actual previous data duration will equal the total cache time.
 * Currently, the socket IP is 127.0.0.1 and the port is 9000.
 *
 * The following table shows the difference between two modes.
 * <table>
 * <caption id="record modes"></caption>
 * <tr><th align="left">Mode<th align="left">Memory Usage<th align="left">Backtracking Support
 * <th align="left">Multiple Recordings
 * <tr><td><B>Standard</B><td>Small<td>No<td>No
 * <tr><td><B>Trigger</B><td>Depand on cache size<td>Yes<td>Yes
 * </table>
 *
 * @par Example: Record previous 10 seconds in trigger mode
 * @code {.bash}
 * board A # test_asf --record-cfg record.json
 * board B # nc 127.0.0.1 9000 //Use netcat and connect at 127.0.0.1:9000
 * board B # cap:10:0
 * @endcode
 * @par Example: Record previous 5 s and 20 s live in trigger mode
 * @code {.bash}
 * board A # test_asf --record-cfg record.json
 * board B # nc 127.0.0.1 9000 //Use netcat and connect at 127.0.0.1:9000
 * board B # cap:5:20
 * @endcode
 *
 * @subsection asf_record_compile 2.4 Compilation
 * The following compile options must be configured before building the ASF recording application.
 * - Add ASF library & test:
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * build $ make menuconfig
 * [*] Ambarella Package Configuration  --->
 *     [*]   Build Ambarella ASF library  --->
 *         [*]   Build Ambarella ASF test app  packages
 * @endcode
 *
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 * prebuild  --->
 *     oss  --->
 *         [*] prebuild-cjson (prebuild/oss/armv8-a/cjson)
 * packages  --->
 *     [*] libasf (packages/asf)
 *     [*] asf-test (packages/asf)
 * @endcode
 *
 * - For SDK Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 * meta-ambalib  --->
 *     recipes-video  --->
 *          [*] libasf (meta-ambalib/recipes-video/libasf)
 * meta-ambaapp  --->
 *     recipes-test  --->
 *          [*] asf-test (meta-ambaapp/recipes-test/asf-test)
 * @endcode
 *
 * - Add Sqlite3 library
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * build $ make menuconfig
 * [*] Ambarella File System Configuration  --->
 *     Open Source Software (OSS)  --->
 *         System Basic Libraries  --->
 *             [*] Add SQLite into root_fs
 * @endcode
 *
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 * prebuild  --->
 *     oss  --->
 *         [*] prebuild-sqlite (prebuild/oss/armv8-a/sqlite)
 * @endcode
 *
 * - For SDK Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 * meta-oe  --->
 *     recipes-dbs  --->
 *         [*] sqlite (meta-oe/recipes-dbs/sqlite)
 * @endcode
 *
 * - - - -
 *
 * @section asf_repack 3. Repack
 * Users can transform and reorganize record data using the repack application. Typically, there
 * are four stages to the repack process.
 * - Sanity check: check each block item in the data base. Verify clusters and block CRC.
 * Find the corrupted data in the binary.
 * - Statistic: update the statistics of the module and check if any data was dropped.
 * - Pre-process (optional): according to the configuration file, processed data is generated with
 * source block data.
 * - Repack: according to the configuration file, re-align the data according to the mono
 * PTS (or system time) and reorganize it in a new cluster.
 * @image html general_repack_flow.png "Figure 3-1. Repack Flow."
 *
 * @subsection asf_repack_opt 3.1 Supported Repack Operations
 * @par Decode
 * This is a supported operation in the preprocess stage. This operation transforms H.264 and
 * H.265 data into YUV data.
 * @par Stream Extract
 * Extract stream data from a block and merge it into a single binary.
 * @par Data Trim
 * This is an operation for all repack and supported action input data. This operation filters the data
 * with specfied rules. The data trim operation can be divided into two types: item selection and
 * time selection. With item selection, items can be filtered one by one. With time
 * selection, items can be filtered by their system time.
 * @image html trim_with_item.png "Figure 3-2. Trim Item."
 * @image html trim_with_time.png "Figure 3-3. Trim Time."
 * @par No Discard
 * In general, different types of source data will be aligned and repacked according to the mono PTS.
 * If one portion of data does not match the others, it will be ignored in the repack process.
 * The <B>no_discard</B> flag can be set if the user does not want this action to occur.
 * In this case, all data can be packed in the repack process.
 * @image html no_discard.png "Figure 3-4. No Discard."
 *
 * @subsection asf_repack_json 3.2 Repack Configuration
 * ASF repack also uses the JSON format text as a configuration file.
 * @par Example: Decode stream to YUV, then repack
 * @code {.json}
 * {
 *     "preprocess": {
 *         "action": [
 *             {
 *                 "name": "decode",
 *                 "cfg": {
 *                     "input": [{
 *                         "data_type": 3,
 *                         "dev_id": 0,
 *                         "slice": {
 *                             "type": "item",
 *                             "duration": 120
 *                         }
 *                     }],
 *                     "output": [{
 *                         "data_type": 2,
 *                         "dev_id": 0
 *                     }]
 *                 }
 *             }
 *         ],
 *         "cfg": {
 *             "tmp_folder": "tmp",
 *             "tmp_bin_size_limit_MB": 100
 *         }
 *     },
 *     "repack" : {
 *         "input": [{
 *             "data_type": 2,
 *             "dev_id": 0,
 *             "no_discard": 1,
 *             "slice": {
 *                "type": "time",
 *                 "start": 1,
 *                 "duration": 5
 *             }
 *         }],
 *         "cfg": {
 *             "output_name": "sample_output.bin",
 *             "output_size_limit_MB": 150,
 *             "repack_pts_delta_factor": 0.49
 *         },
 *     },
 *     "system": {
 *         "event_id": [0],
 *         "work_folder": "./sample",
 *         "db_name": "test.db",
 *         "statis_delta_factor": 0.2
 *     }
 * }
 * @endcode
 *
 * @par Example: Extract stream
 * @code {.json}
 * {
 *     "preprocess": {
 *         "action": [
 *             {
 *                 "name": "stream_extract",
 *                 "cfg": {
 *                     "input": [{
 *                         "data_type": 3,
 *                         "dev_id": 0
 *                     }],
 *                     "extract_file_name": "stream_out.h264"
 *                 }
 *             }
 *         ],
 *         "cfg": {
 *             "tmp_folder": "tmp",
 *             "tmp_bin_size_limit_MB": 100
 *         }
 *     },
 *     "system": {
 *          "event_id": [0],
 *          "work_folder": "./sample",
 *          "db_name": "test.db",
 *          "statis_delta_factor": 0.2
 *     }
 * }
 * @endcode
 *
 * @par Example: Trim stream data with time range 1 ~ 4
 * @code {.json}
 * {
 * ...
 *     "repack" : {
 *         "input": [{
 *             "data_type": 2,
 *             "dev_id": 0,
 *             "slice": {
 *                "type": "time",
 *                 "start": 1,
 *                 "duration": 3
 *             }
 *         }],
 *      ...
 *     },
 *  ...
 * }
 * @endcode
 *
 * @par Example: Trim stream data with item range 5 ~ 100
 * @code {.json}
 * {
 * ...
 *     "repack" : {
 *         "input": [{
 *             "data_type": 2,
 *             "dev_id": 0,
 *             "slice": {
 *                "type": "item",
 *                 "start": 5,
 *                 "duration": 95
 *             }
 *         }],
 *      ...
 *     },
 *  ...
 * }
 * @endcode
 *
 * @par Example: Repack data with event ID 2
 * @code {.json}
 * {
 *  ...
 *     "system": {
 *         "event_id": [2],
 *         "work_folder": "./sample",
 *         "db_name": "test.db",
 *         "statis_delta_factor": 0.2
 *     }
 * }
 * @endcode
 *
 * The following lists general option node details in the configurations.
 * <table>
 * <caption id="repack options"></caption>
 * <tr><th align="left">Node<th align="left">Value Type<th align="left">Description
 * <tr><td><B>preprocess</B><td>Node<td>Node for preprocess (optional)
 * <tr><td><B>action</B><td>Array Node<td>Array node for supported preprocess actions
 * <tr><td><B>name</B><td>String<td>Action name for parent action node
 * <tr><td><B>cfg</B><td>Node<td>Configuration node for parent node
 * <tr><td><B>input</B><td>Node<td>Input source data node for action / repack nodes
 * <tr><td><B>output</B><td>Node<td>Output data node for action node
 * <tr><td><B>data_type</B><td>Number<td>Data type @ref asf_block_type
 * <tr><td><B>dev_id</B><td>Number<td>Data module device ID
 * <tr><td><B>slice</B><td>Node<td>Node for module data selection (optional)
 * <tr><td><B>type</B><td>String<td>Data selection type: "item" or "time"
 * <tr><td><B>duration</B><td>Number<td>Data duration for data trim. The default is "0" which means full
 * time or full long. If the type is "item", it means data item count. If the type is "time", it means time
 * duration. The system will always get the valid duration even if the target duration exceeds the input
 * data duration. It is optional
 * <tr><td><B>start</B><td>Number<td>Data start offset for data trim. The default is 0. If the type is
 * "item", it means item start offset count. If the type is "time", it means time start offset. It is
 * optional
 * <tr><td><B>no_discard</B><td>Number<td>No discard flag for repack input module. Refer
 * to @ref asf_repack_opt for more details
 * <tr><td><B>extract_file_name</B><td>String<td>Extract stream output file name in action
 * <B>stream_extract</B>
 * <tr><td><B>tmp_folder</B><td>String<td>Temporary file path for parent action in preprocessing
 * <tr><td><B>tmp_bin_size_limit_MB</B><td>Number<td>For large amounts of data, the temporary data
 * binary will be split into several blocks. This option determines the single block maximum size
 * <tr><td><B>repack</B><td>Node<td>Node for repack
 * <tr><td><B>output_name</B><td>String<td>Output file name for repack
 * <tr><td><B>output_size_limit_MB</B><td>Number<td>For large amounts of data, the output data
 * binary will be split into several blocks. This option determines the single block maximum size
 * <tr><td><B>repack_pts_delta_factor</B><td>Number<td>Threshold factor for time alignment in the repack
 * process
 * <tr><td><B>system</B><td>Node<td>Node for general configurations
 * <tr><td><B>event_id</B><td>Number Array<td>Used event ID array for preprocess and repack
 * <tr><td><B>work_folder</B><td>String<td>Work folder root path for repack application
 * <tr><td><B>db_name</B><td>String<td>Database name
 * <tr><td><B>statis_delta_factor</B><td>Number<td>Threshold factor for data cluster statistic
 * </table>
 *
 * @note
 * Find the sample repack JSON in `ambarella/packages/asf/unit_test/json_sample` .
 *
 * @subsection asf_repack_compile 3.3 Compilation
 * Users can compile and run the repack application using the following commands on the host PC.
 * @code
 * build $ cd ambarella/packages/asf/pc_browser
 * build $ make
 * build $ chmod +x bin/asf_browser
 * build $ ./asf_browser
 * @endcode
 *
 * - - - -
 *
 * @section asf_replay 4. Replay
 * After recording and repacking, users are given the required time-aligned data.
 * Now, the data can be replayed on the local side.
 * @subsection asf_replay_flow 4.1 Replay Flow
 * @image html general_replay_flow.png "Figure 4-1. Replay Flow."
 *
 * @subsection asf_replay_case 4.2 Supported Replay Cases
 * Currently, there is no general replay application in ASF. Users can parse and replay the
 * required data from the repack binary. The following cases are supported for replay cases.
 * - Replay in electronic image stabilization (EIS) simulation: @ref asf_example_eis_replay
 *
 * - - - -
 *
 * @section asf_example 5. Application Examples
 * @subsection asf_exmaple_eis 5.1 EIS Simulation
 * The following compile options must be configured before running the EIS simulation.
 * - Enable EIS library:
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * build $ make menuconfig
 * [*] Ambarella Prebuild  --->
 *     [*]   Configure Ambarella eis library  --->
 *         Config EIS Library Version (Config multi-channel EIS library)  --->
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 * prebuild  --->
 *     library  --->
 *         [*] prebuild-eis (prebuild/library/eis/dsp_v5)
 * @endcode
 * - For SDK Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 * meta-ambalib  --->
 *     recipes-prebuild  --->
 *         [*] prebuild-eis (meta-ambalib/recipes-prebuild/prebuild-eis)
 * @endcode
 * - Enable EIS driver:
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * build $ make menuconfig
 * [*] Ambarella Linux Configuration  --->
 *     [*]   Ambarella Private Drivers Configuration  --->
 *         [*]   Build Ambarella private EIS modules  --->
 *             Choose EIS Driver Type (Build EIS driver multi channel)  --->
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 * drv_modules  --->
 *     platform  --->
 *         [*] ambeis-header (drv_modules/platform/eis)
 * @endcode
 * - For SDK Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 * meta-ambabsp  --->
 *     recipes-video  --->
 *         [*] ambeis-header (meta-ambabsp/recipes-video/ambeis-header)
 * @endcode
 * - Enable gyro driver:
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * build $ make menuconfig
 * [*] Ambarella Linux Configuration  --->
 *     [*]   Ambarella Private Drivers Configuration  --->
 *         [*]   Build Ambarella private gyro modules
 *             Choose Gyro Driver Type (GYRO_MULTI_CHANNEL)  --->
 *             Gyro Sensor Multi Channel (MPU9250_SPI)  --->
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 * drv_modules  --->
 *     platform  --->
 *         gyro  --->
 *             [*] kernel-module-mpu9250 (drv_modules/platform/gyro/mpu9250)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 * meta-ambabsp  --->
 *     recipes-gyro  --->
 *         [*] kernel-module-mpu9250 (meta-ambabsp/recipes-gyro/kernel-module-mpu9250)
 * @endcode
 *
 * @subsubsection asf_example_eis_record 5.1.1 EIS Simulation Record
 * This record case uses 1080p RGB sensor input. For EIS simulation, sensor RAW, gyro data, and
 * sensor-related settings are required. Because sensor RAW uses excessive storage space,
 * saving encoded bitstreams is more efficient. This data is saved in ASF data format.
 * @image html eis_record_flow.png "Figure 5-1. EIS Record Flow."
 * - Record with <a href="scripts/eis_record.json" target="_blank"><b>eis_record.json
 * </b></a> configuration:
 * @code {.bash}
 * board # (CV2x) init.sh --imx274_mipi
 * board # (CV5x) init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a &
 * board # modprobe gyro_mpu9250_mc
 * board # (CV2x) test_encode -i 1080p --hdmi 1080p
 * board # (CV5x) test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua
 *                            --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_encode -A -H 1080p -b 0 -e
 * board # test_asf --record-cfg eis_record.json
 * @endcode
 *
 * @subsubsection asf_example_eis_repack 5.1.2 EIS Simulation Repack
 * Unpack the ASF data cluster, decode the stream block, then pack the ASF cluster again with the
 * decoded YUV block.
 * - Repack with <a href="scripts/eis_repack.json" target="_blank"><b>eis_repack.json
 * </b></a> configuration:
 * @code {.bash}
 * build $ cd ambarella/packages/asf/pc_browser/bin
 * build $ ./asf_browser --repack-cfg eis_repack.json
 * @endcode
 *
 * @subsubsection asf_example_eis_replay 5.1.3 EIS Simulation Replay
 * 1080p YUV 420 block data is used as source input. According to the gyro and sensor data,
 * a related warp table is generated and applied to the channel. The final EIS result can be shown
 * through a stream or video output (VOUT).
 * @image html eis_replay_flow.png "Figure 5-2. EIS Replay Flow."
 * @code {.bash}
 * board # init.sh --yuv1080p30
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg replay_simulate_1080p.lua --enc-raw-nv12 1
 * board # test_eis_warp_replay -i 6 -F 3500 --filter-scale 512,1024,512 --filter-mode 1
 * --replay-file-prefix /sdcard/mmcblk1p1/chessboard_regression.bin
 * @endcode
 *
 * - - - -
 *
 * @section asf_qa 6. Troubleshooting
 * This chapter provides frequently asked questions (FAQs) and answers about ASF.
 * More information will be added in the future.
 *
 * @subsection asf_q1 Question 1: What record mode should the customer use?
 * @b Answer: There are two record modes in ASF. Users can check the details of these modes in
 * @ref asf_record_json.
 * In short, standard mode is a subset of trigger mode, and it can only cover simple tasks.
 * Storage input / output (I/O) performance is also required in order to be considered. In the current ASF version, data querying
 * and data writing for each task is completed in one thread. Therefore, if the write part could
 * be blocked long term, (such as when using a secure digital (SD) card), trigger mode is
 * recommended by Ambarella.
 *
 * @subsection asf_q2 Question 2: How is an "Invalid event id 1" issue on the repack stage managed?
 * @b Answer: Each record event has a unique ID ( @ref asf_record_json_mode). Double-check the
 * repack option "event_id" configured in the repack configuration file, whether or not the event exists.
 *
 * @subsection asf_q3 Question 3: In the record stage, what is "shift_realtime_enable" used for?
 * @b Answer: The "shift_realtime_enable" is an option for gyro mode ( @ref asf_record_plugin_type).
 * When this option is enabled, additional data will be captured as zero-float data at the
 * module-preparing stage.
 *
 * @subsection asf_q4 Question 4: How can users confirm that the record data has not been corrupted?
 * @b Answer: Customers can use the "asf_browser" application to check the record data binary with the option "-f".
 * This will check the data integrity. The following commands demonstrate data integrity checks.
 * @code {.bash}
 * board # asf_browser -f record.bin
 * === Sanity Check Raw Cluster Binary ===
 * Read Magic: No such file or directory
 * Read file end
 * ===Total count: 20===
 * ===Error count: 0===
 * ===Pass count: 20===
 * @endcode
 *
 * @subsection asf_q5 Question 5: How are record binaries split?
 * @b Answer: The option "file_size_limit_MB" in the repack configuration file sets the maximum size of
 * the record binary ( @ref asf_record_json_config). If the record binary size is greater than the maximum size,
 * ASF will create and save a new file.
 *
 * @subsection asf_q6 Question 6: What does the "Invalid items found:" message mean in the repack stage?
 * @b Answer: In the repack stage, an application checks the data PTSs. If the PTSs are not
 * consecutive, then this error is reported. This usually indicates that there was data loss during
 * the recording process.
 *
 * @subsection asf_q7 Question 7: Why does data loss occur in the record stage?
 * @b Answer: There are many possible reasons for this issue, including system blocking, storage I/O
 * blocking, recording moudle errors, and hardware issues.
 *
 * @subsection asf_q8 Question 8: Should the recording stream resolution and VIN resolution be the same in EIS cases?
 * @b Answer: Yes, the resolutions must be the same because stream data will be transferred to YUV data, which
 * will feed as VIN data in the replay stage. Differences in resolution will affect the EIS results.
 *
 * @subsection asf_q9 Question 9: In EIS cases, why does the "IAV_IOC_IMG_GET_STATISTICS" error print in the console?
 * @b Answer: In the replay stage, encode from RAW (EFR) is used to simulate real VIN input. This error will print when
 * there is no feed in image audio video (IAV), so it is reasonable that this error shows before and after the replay
 * application runs.
 *
 * @subsection asf_q10 Question 10: In EIS cases, what does the "Set RAW failed" error message mean in the replay stage?
 * @b Answer: This error indicates something is wrong when feeding VIN frames. This is most likely
 * caused by configuring incorrect virtual VIN I with the replay application "test_eis_warp_replay".
 * The virtual VIN ID for different evaluation kit (EVK) boards is different. For CV2x, it is likely set as the
 * last VIN ID + 1.
 *
 * @subsection asf_q11 Qustion 11: Why is replay slow in EIS cases?
 * @b Answer: The main reason is the storage I/O limitation. Customers can attempt using other storage
 * media to read replay binaries.
 *
 * @subsection asf_q12 Qustion 12: In EIS cases, why is the number of frames replayed less than the recorded ones?
 * @b Answer: Check the repack configuration file if "slice"-related options were
 * used, as they will affect the data selection range in the repack stage. Refer to @ref asf_repack_json.or
 * for "slice"-related options.
 *
 * - - - -
 *
 * @section asf_api 7. ASF Library API
 * Visit the following link for details of the application programming interface (API) functions.
 *      - @ref ASF_FUNCTION_GROUP explains API functions.
 *      - @ref ASF_DEFINE_GROUP shows related macros.
 *      - @ref ASF_ENUM_GROUP shows related enumerations.
 *      - @ref ASF_STRUCT_GROUP shows related structures.
 *
 * - - - -
 *
 * @section asf_license 8. License
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
 */

/*!
 * @defgroup ASF_FUNCTION_GROUP ASF Library API
 * @brief ASF Library API, in file asf_core.h
 */
/*!
 * @defgroup ASF_DEFINE_GROUP ASF Macro
 * @brief ASF Macro, in file asf_structure.h
 */
/*!
 * @defgroup ASF_ENUM_GROUP ASF Enumeration
 * @brief ASF Enumeration, in file asf_structure.h
 */
/*!
 * @defgroup ASF_STRUCT_GROUP ASF Structure
 * @brief ASF Structure, in file asf_structure.h and asf_core.h
 *//*!
 * @file doc_lib_cavalry_mem.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2019-08-27
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
 * @page page_lib_cavalry_mem_doc Cavalry_Mem Library API
 *
 * @section cavalry_mem_history 0. Revision History
 *  | Library Version | Updated Date     | Modification                             |
 *  | :---            | :--------------- | :--------------------------------------- |
 *  | 0.0.4           | 20190829         | Initial Version                          |
 *  | 0.0.5           | 20190417         | Support auto recycle leak cavalry memory |
 *  | 0.0.5           | 20190417         | Add API cavalry_mem_alloc_persist() to turn off auto recycle memory in some case |
 *  | 0.0.6           | 20190426         | Support dma-buf:fd for cavalry memory    |
 *  | 0.0.7           | 20190607         | Add API cavalry_mem_get_fd()             |
 *
 * - - - -
 *
 * @section cavalry_mem_introduction 1. Introduction
 * Cavalry_Mem is used for users to allocate physical continuous memory in CV region.
 * Because CVflow™ Hardware only recognizes physical memory.
 * User application should map this physical memory to user space as virtual memory,
 * then can write and read this memory.
 * It supports mapping as cached memory in user space, then boost Arm® process on it.
 * Make sure to sync (clean / invalid) cached memory when VP and Arm cross access it.
 *
 * - - - -
 *
 * @section cavalry_mem_example 2. Example Usage
 * It will show how to allocate and free memory, and get the benefit of Arm process when enabling cache.
 * Since Cavalry_Mem is based on the Cavalry driver, users should enable the Cavalry driver firstly,
 * then enable cavalry memory library.
 * Follow these commands to build the library:
 *
 * - For CV2x SDK 3.0 Amba build
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Package Configuration  --->
 *              [*]   Build Ambarella cavalry memory library
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *          packages  --->
 *              [*] libcavalrymem (packages/cavalry_mem)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *          meta-ambalib  --->
 *              recipes-cavalry  --->
 *                  [*] libcavalrymem (meta-ambalib/recipes-cavalry/libcavalrymem)
 * @endcode
 * @subsection cavalry_mem_usage 2.1 Debug Information
 * * Get the usage of the CV user memory.<br>
 * There is `/proc/ambarella/cavalry_cma` proc file can show the current used memory block.
 * The MMB ID 0000 is internal memory (6 MB) which users do not need to take care of.
 * @code {.c}
 * board # test_cavalry_mem -g
 * Usage mem: used size: 0x0, free size: 0x1fa00000
 * board # cat /proc/ambarella/cavalry_cma
 * mmb   phys[start-end]        size        kern-virt[start-end]                   ref_cnt  cache  recycle  pid
 * 0000  0x60000000-0x60400000  0x00400000  0x0000000059215c4e-0x0000000065950971
 * ----
 *
 * Free list count: 1, max contiguous free size: 0x1fc00000
 * Total Cavalry memory size: 0x20000000 (about 512MB), used size: 0x400000 (about 4MB)
 *
 * Cavalry Status: Started
 * @endcode
 *
 * @subsection cavalry_mem_alloc 2.2 Allocate Memory
 * * Allocates a specified size memory.<br>
 * The driver will return a PAGE (4 KB) aligned size of memory.
 * @code {.c}
 * board # test_cavalry_mem -s 0x100000
 * Alloc cv_mem addr: 0x60400000, size: 0x100000, cache: 0, auto_recycle: 0
 * board # cat /proc/ambarella/cavalry_cma
 * mmb   phys[start-end]        size        kern-virt[start-end]                   ref_cnt  cache  recycle  pid
 * 0000  0x60000000-0x60400000  0x00400000  0x0000000059215c4e-0x0000000065950971
 * ----
 * 0001  0x60400000-0x60500000  0x00100000  0x00000000821c3d7b-0x0000000081b84e31  0        0      0    727588(Dead)
 *
 * Free list count: 1, max contiguous free size: 0x1fb00000
 * Total Cavalry memory size: 0x20000000 (about 512MB), used size: 0x500000 (about 5MB)
 *
 * Cavalry Status: Started
 * @endcode
 *
 * @subsection cavalry_mem_free 2.3 Free Memory
 * * Frees up a specified physical address memory block.<br>
 * Physical address is used as memory block ID.
 * It frees the whole size of the memory block at once.
 * @code {.c}
 * board # test_cavalry_mem -d 0x60400000
 * Free cv_mem addr: 0x60400000
 * board # cat /proc/ambarella/cavalry_cma
 * mmb   phys[start-end]        size        kern-virt[start-end]                   ref_cnt  cache  recycle  pid
 * 0000  0x60000000-0x60400000  0x00400000  0x0000000059215c4e-0x0000000065950971
 * ----
 *
 * Free list count: 1, max contiguous free size: 0x1fc00000
 * Total Cavalry memory size: 0x20000000 (about 512MB), used size: 0x400000 (about 4MB)
 *
 * Cavalry Status: Started
 * @endcode
 *
 * @subsection cavalry_mem_sync_cache 2.4 Sync Cached Memory
 * It can improve the memory access performance in user space applications.
 * The user needs to clean or invalidate cache memory while it is enabled.
 * The following example shows that cached memory gets a better performance than non-cached memory.
 * A larger memory gets better results. The example below uses 32 MB DRAM,
 * and it shows cached access is seven times faster than non-cached access.
 * @code {.c}
 * board # test_cavalry_mem -m 0x2000000
 * [non-cache], memory size: 0x2000000
 * ARM Write : 13395 us
 * ARM Read  : 293028 us
 * board # test_cavalry_mem -m 0x2000000 -c
 * [cache], memory size: 0x2000000
 * ARM Write : 16403 us
 * ARM Read  : 26088 us
 * @endcode
 *
 * - - - -
 *
 * @section sec_cavalry_mem_api 3. Cavalry_Mem API
 * Visit the following link to see details of the API function.
 *      - @ref cavalry_mem-api-details shows API lists.
 *      - @ref cavalry_mem-helper shows related macros enumerations and structures.
 *
 * - - - -
 *
 * @section sec_cavalry_mem_lic 4. License
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
 * @example test_cavalry_mem.c
 * This is a source code file of test_cavalry_mem.
 *
 */
 /*!
 * @defgroup cavalry_mem-api Cavalry_Mem Library API
 * @brief cavalry_mem Library API, in file cavalry_mem.h
 */
/*! @defgroup cavalry_mem-api-details Cavalry_Mem Library API details
 *  @ingroup cavalry_mem-api
 *  @brief cavalry_mem API details, in file cavalry_mem.h
 */
/*! @defgroup cavalry_mem-helper Cavalry_Mem Library API helper
 *  @ingroup cavalry_mem-api
 *  @brief cavalry_mem Helper, in file cavalry_mem.h
 */
/*!
 * @file doc_lib_cavalry_opt_layers.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2020-06-30
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
 * @page page_lib_cavalry_opt_layers_doc Cavalry Opt Layers Library API
 *
 * @section cavalry_opt_layers_history 0. Revision History
 *  | Library Version |Updated Date     | Modification                 |
 *  | :---               | :--------------------------- |:----------------|
 *  | 1.0.2 |20200630         | Initial Version                |
 *  | 1.1.3 |20231103         | Added float dtcvt                |
 *
 * - - - -
 *
 * @section cavalry_opt_layers_introduction 1. Introduction
 * CVflow® can support most of layers for neural network, but some layers such as NMS, region of interest (ROI) pooling
 * and ROI align layer cannot run on CVflow.  So those layers have to run on Arm® processor.
 * Library cavalry_opt_layers can support those layers and boost some of them by NEON code,
 * like NMS, ROI pooling, ROI align and PS ROI pooling layers, and more.
 *
 * Library cavalry_opt_layers is pure Arm code, which does not depend on CVflow hardware.
 *
 * Follow these commands to build the library.
 * And select some unit test for library special function.
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Prebuild  --->
 *              [*]   Configure Ambarella cavalry opt layers library
 *
 *          [*] Ambarella Unit Test Configuration  --->
 *              [*]   Ambarella Private Linux Unit test configs  --->
 *                 [*]   Build CV unit tests  --->
 *                    [*]   Build PVANet unit tests
 *                    [*]   Build ROI Align unit tests with ARM implement
 *                    [*]   Build PS ROI Pooling unit tests with ARM implement
 *                    [*]   Build float data conversion unit tests
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *          prebuild  --->
 *              library  --->
 *                  [*] prebuild-cavalry-opt-layers (prebuild/library/cavalry_opt_layers)
 *          unit_test  --->
 *              private  --->
 *                  [*] cv-test (unit_test/private/cv_test/cavalry_v2)  --->
 *          app  --->
 *              ai_cam  --->
 *                  [*] cvflow-test (app/ai_cam/cvflow)  --->
 *                      [*]   Build PVANet unit tests
 *                      [*]   Build float data conversion unit tests
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *          meta-ambalib  --->
 *              recipes-prebuild  --->
 *                  [*] prebuild-cavalry-opt-layers (meta-ambalib/recipes-prebuild/prebuild-cavalry-opt-layers)
 *
 *          meta-ambaapp  --->
 *              recipes-test  --->
 *                  [*] cv-test (meta-ambaapp/recipes-test/cv-test)  --->
 *                  [*] cvflow-test (meta-ambaapp/recipes-test/cvflow-test)  --->
 *                      [*]   Build PVANet unit tests
 *                      [*]   Build float data conversion unit tests
 * @endcode
 * - - - -
 *
 * @section cavalry_opt_layers_example 2. Example Usage
 *
 * @subsection cavalry_opt_layers_test_pvanet 2.1 test_pvanet
 * PVANet uses a two-step structure to perform an object detection, which reduces computational
 * costs and improves the detection accuracy for most practical usages.  Most of Layers
 * can be run on CVflow harware, but some layers such as NMS, ROI pooling, and post processing
 * are implemented in libcavalry_opt_layers.  The unit test test_pvanet is an example
 * to connect them together and print the object detection result in the end.
 * The libcavalry_opt_layers can only be run on Ambarella platform, ensuring that digital signal processor (DSP) is in either of
 * idle / preview / encoding state.
 *
 * @code {.c}
 * build $ cd <SDK>/ambarella/unit_test/private/cv_test/pvanet/arch_cv22
 * build $ cavalry_gen -d rpn/vas_ouput -f pvanet_rpn_cavalry.bin
 * build $ cavalry_gen -d rcnn_compress/vas_ouput -f pvanet_rcnn_compress_cavalry.bin
 * board # test_encode --idle --nopreview
 * board # test_pvanet -c -b arch_cv22/pvanet_rpn_cavalry.bin --in data=input.bin --out rpn_cls_prob_reshape --no --out rpn_bbox_pred --no --out concat_convf_permute --no  -b arch_cv22/pvanet_rcnn_compress_cavalry.bin --in roi_pool_conv5 --no --out cls_prob --no --out bbox_pred --no
 * =================== BBox Result =====================
 * Class [7] [car] keep [1] bboxes
 *   BBOX[0]: x1 = 0.898438, y1 = 130.125000, x2 = 171.125000, y2 = 260.750000, scores = 0.952637
 * Class [12] [dog] keep [1] bboxes
 *   BBOX[0]: x1 = 178.500000, y1 = 255.000000, x2 = 255.000000, y2 = 442.000000, scores = 0.999512
 * Class [13] [horse] keep [1] bboxes
 *   BBOX[0]: x1 = 261.750000, y1 = 104.750000, x2 = 543.500000, y2 = 464.500000, scores = 0.852051
 * Class [15] [person] keep [2] bboxes
 *   BBOX[0]: x1 = 344.500000, y1 = 7.937500, x2 = 452.250000, y2 = 302.000000, scores = 0.996094
 *   BBOX[1]: x1 = 547.500000, y1 = 161.125000, x2 = 574.000000, y2 = 229.875000, scores = 0.878906
 * ================================================
 * @endcode
 *
 * @subsection cavalry_opt_layers_test_roi_align_arm 2.2 test_roi_align_arm
 * ROI align is a technique based on bilinear interpolation to smoothly crop a patch from
 * a full-image feature map based on a region proposal, and then resize the cropped patch to
 * a desired spatial size.  It was introduced in Mask R-CNN model.
 *
 ** 1. ROI align is on one feature map. The image resolution is (H, W) (480, 640), and the scale is 16.
 * The original feature map dimension is (C, H, W) [512, 30, 40], users should reshape and permute it
 * to (H, W, C) [30, 40, 512] before feeding to roi_align. RoIs number is 50.
 * The output dimension is (H, W, C) [7, 7, 512].
 * @code {.c}
 * board # test_encode --idle --nopreview
 * board # test_roi_align_arm -r rois_bbox_N50_fp32.bin -f fmap_30x40x512_s16.bin -n 50 -d 16 -F 40x30x512 -P 7x7 -o out_pooled_1_7x7x512.bin -t 2 -v
 * RoI_Align:       5972 us
 * @endcode
 *
 ** 2. ROI align is on three feature maps. The image resolution is (H, W) (608, 1088), and three scales are 8, 16, and 32.
 * Three feature maps dimensions are (C, H, W) [64, 76, 136], [64, 38, 68] and [64, 19, 34].
 * Users should reshape and permute these to (H, W, C) [76, 136, 64], [38, 68, 64] and [64, 19, 34]
 * before feeding to roi_align. RoIs number is 100. The output dimension is (H, W, C) [14, 14, 64].
 * @code {.c}
 * board # test_encode --idle --nopreview
 * board # test_roi_align_arm -r rois_bbox_N100_fp32.bin -f fmap_76x136x64_s16.bin -f fmap_38x68x64_s16.bin -f fmap_19x34x64_s16.bin -n 100 -d 8 -F 136x76x64 -P 14x14 -o out_pooled_4_14x14x512.bin -t 2 -v
 * RoI_Align:       3862 us
 * @endcode
 *
 * @subsection cavalry_opt_layers_test_psroipooling 2.3 test_psroipooling
 * The position-sensitive RoI pooling (PS-RoI Pooling) layer in Light-Head R-CNN introduces
 * spatial information during pooling. The image resolution is (H, W) (384, 512), and the scale is 16.
 * The feature map dimension is (P, C, H, W) [21, 49, 24, 32], users should reshape and permute it to
 * (C, H, W, P) [49, 24, 32, 21] before feeding to ps_roi_pooling. RoIs number is 300.
 * The output dimension is (H, W, C) [7, 7, 21].
 *
 * @code {.c}
 * board # test_encode --idle --nopreview
 * board # test_psroipooling -r rois_300_fp32.bin -f fmap_49x24x32x21_fp32.bin -n 300 -d 16 -F 32x24x49x21 -P 7x7 -o out_pooled_7x7x21.bin -t 2 -v
 * PS_RoI_Pooling:       9859 us
 * @endcode
 *
 * @subsection cavalry_opt_layers_test_float_dtcvt 2.3 test_float_dtcvt
 * This is a NEON version implementation of data format conversion when an input or output
 * is IEEE float32 data.
 *
 * @code {.c}
 * board # test_encode --idle --nopreview
 * board # test_float_dtcvt -i in.bin -o out.bin -s 1000x1000x1 -I 0,0,5,0 -O 1,2,0,7 -t
 * board # test_float_scale -i in.bin -o out.bin -s 1000x1000x1 -I 0,0,5,0 -O 1,2,0,7 -r 1.00217 -t
 * @endcode
 *
 * - - - -
 *
 * @section sec_cavalry_opt_layers_api 3. Cavalry Opt Layers API
 * Visit the following link for details on API functions.
 *      - @ref cavalry_opt_layers-api-details shows API lists.
 *      - @ref cavalry_opt_layers-helper shows related macros enumerations and structures.
 *
 * - - - -
 *
 * @section sec_cavalry_opt_layers_lic 4. License
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
 * @example test_pvanet.cpp
 * This is a source code file of test_pvanet.
 *
 */

/*!
 * @example test_roi_align_arm.cpp
 * This is a source code file of test_roi_align_arm.
 *
 */

 /*!
 * @example test_psroipooling.cpp
 * This is a source code file of test_psroipooling.
 *
 */

 /*!
 * @defgroup cavalry_opt_layers-api Cavalry Opt Layers Library API
 * @brief cavalry_opt_layers Library API, in file opt_layers.hpp
 */
/*! @defgroup cavalry_opt_layers-api-details Cavalry Opt Layers Library API details
 *  @ingroup cavalry_opt_layers-api
 *  @brief cavalry_opt_layers API details, in file opt_layers.hpp
 */
/*! @defgroup cavalry_opt_layers-helper Cavalry Opt Layers Library API helper
 *  @ingroup cavalry_opt_layers-api
 *  @brief cavalry_opt_layers Helper, in file opt_layers.hpp
 */
/*!
 * @file doc_lib_cgpp.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2019-09-24
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
 * @page page_lib_cgpp_doc CGPP Library API
 *
 * @section cgpp_history 0. Revision History
 * <table>
 * <caption id="lib_cgpp_rev_history"></caption>
 * <tr align="middle"><th> Library Version <th> Updated Date <th> Modification
 * <tr align="middle"><td> 0.0.1 <td> 20190924 <td align="left"> Initial Version
 * <tr align="middle"><td> 0.0.2 <td> 20200106 <td align="left"> Refine document structure
 * <tr align="middle"><td> 0.0.3 <td> 20220128 <td align="left"> Add feature: runtime rotate/flip
 * <tr align="middle"><td rowspan="3"> 0.0.4 <td rowspan="3s"> 20220916
 * <tr><td align="left"> Add feature: add yuv444 support, refine code
 * <tr><td align="left"> Updata Section @ref cgpp_library_test_cgpp_live_in_resize_mode and @ref cgpp_library_test_cgpp_live_in_warp_mode, remove the Dproc API int osd_server_yolov3 and replace it with the test_eazyai API.
 * </table>
 *
 * - - - -
 *
 * @section cgpp_introduction 1. Introduction
 * CGPP stands for CNNGen Pre-Processing, which is designed to support dynamic
 * configuration for network pre-processing stage, such as resize and warp
 * affine transformation. As its name indicates, this library relies on Ambarella
 * CVTool chain, especially for the parser part that does conversion from original
 * network model to Ambarella format with pre-processing nodes inserted.
 *
 * CGPP library is based on the Cavalry driver, users should enable the Cavalry driver firstly,
 * then enable CGPP library.
 * Follow these commands to build the library:
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Package Configuration  --->
 *              [*]   Build Ambarella cnngen pre-processing support library
 *
 *          [*] Ambarella Unit Test Configuration  --->
 *              [*]   Ambarella Private Linux Unit test configs  --->
 *                 [*]   Build CV unit tests  --->
 *                    [*]   Build test_cgpp unit test
 *          [*] Ambarella Application Configuration  --->
 *              [*]   Build AICAM  --->
 *                 [*]   Build AICAM CVflow  --->
 *                    [*]   Build yolov3 unit tests
 *                    [*]   Build CGPP live unit tests
 * @endcode
 *
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *          packages  --->
 *              [*]   libcnngenprep (packages/cnngen_prep)
 *          unit_test  --->
 *              private  --->
 *                  [*] cv-test (unit_test/private/cv_test/cavalry_v2)  --->
 *          app  --->
 *              ai_cam  --->
 *                  [*] cvflow-test (app/ai_cam/cvflow)  --->
 *                      [*]   Build CGPP live unit tests
 *                      [*]   Build yolov3 unit tests
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *          meta-ambalib  --->
 *              recipes-cavalry  --->
 *                  [*]   libcnngenprep (meta-ambalib/recipes-cavalry/libcnngenprep)
 *          meta-ambaapp  --->
 *              recipes-test  --->
 *                  [*] cv-test (meta-ambaapp/recipes-test/cv-test)  --->
 *                  [*] cvflow-test (meta-ambaapp/recipes-test/cvflow-test)  --->
 *                      [*]   Build yolov3 unit tests
 *                      [*]   Build CGPP live unit tests
 * @endcode
 * - - - -
 *
 * @section cgpp_library_example_usage 2. Example Usage
 *
 * @subsection cgpp_library_test_cgpp 2.1 test_cgpp Application
 * The test_cgpp is one simple application that uses CGPP library to run the network with
 * CNNGen pre-processing nodes on CVflow hardware. Customers can refer it as sample code
 * to write their own application. It supports file mode only, by feeding an input file
 * that holds YUV data in NV12 format. A set of pyramids would be generated automatically
 * according to given configuration and be used to deal with pre-processing nodes,
 * such as variable resamp, warp node.
 *
 * @subsection cgpp_library_test_cgpp_in_resize_mode 2.1.1 test_cgpp in Resize Mode
 * The test_cgpp application could be run at resize mode, which does variable resample to
 * crop out the ROI area and resize the area to the network required input resolution, and then
 * do the network inference. Take yolo v3 for example here.
 *
 * @code {.c}
 * board # cavalry_load -f /lib/firmware/cavalry.bin -r
 * board # test_cgpp -b cgpp_yolov3.bin --dump out_resize --pp 1 --yuv 1920x1080.nv12 --ires 1920x1080 --roi 200,100,960,540 --scale-type 0 --nnres 416x416
 * =======================
 * Cavalry Model Bin: [cgpp_yolov3.bin]
 * Network [0] [cgpp_yolov3.bin] total memory size: 52394368, dvi: 41076812, blob: 11164032. Bandwidth size: 83361344
 * [LIBNN WARN] Warning: Not specify net_io pointer, should get net_io by call nnctrl_get_net_io_cfg() later
 * From cgpp, set input: 0 luma phys: 0xd083ad0d, update_pitch: 1408, rotate_flip: 0x0, virt: 0x7fa9b43d0d
 * From cgpp, set input: 1 chroma phys: 0xd093720c, update_pitch: 1408, rotate_flip: 0x0, virt: 0x7fa9c4020c
 * [LIBNN INFO] Set port [luma], sub [luma], update_pitch: 1408
 * [LIBNN INFO] Set port [chroma], sub [chroma], update_pitch: 1408
 * Net_id: 0, Dags: 39 / 39, vp_ticks: 366045, vp_time: 29788 us, arm_time: 29839 us
 * @endcode
 *
 * @subsection cgpp_library_test_cgpp_in_warp_mode 2.1.2 test_cgpp in WarpAffine Mode
 * The test_cgpp application could be run at warpAffine mode, which does an affine transform
 * from a specified pyramid layer to the target that the network requires. Here uses yolo v3 to
 * illustrate the usage.
 *
 * @code {.c}
 * board # cavalry_load -f /lib/firmware/cavalry.bin -r
 * board # test_cgpp -b cgpp_yolov3.bin --dump out_warp --pp 2 --yuv 1280x720.nv12 --ires 1280x720 --scale-type 0 --nnres 416x416 --pyr-lvl 0 --tran-mat 0.325,0,0,0,0.577,0
 * =======================
 * Cavalry Model Bin: [cgpp_yolov3.bin]
 * Network [0] [cgpp_yolov3.bin] total memory size: 52815488, dvi: 41005240, blob: 11699840. Bandwidth size: 94537280
 * [LIBNN WARN] Warning: Not specify net_io pointer, should get net_io by call nnctrl_get_net_io_cfg() later
 * [LIBNN INFO] Set port [luma], sub [luma], update_pitch: 1280
 * [LIBNN INFO] Set port [chroma], sub [chroma], update_pitch: 1280
 * Net_id: 0, Dags: 38 / 38, vp_ticks: 2203430, vp_time: 179315 us, arm_time: 179489 us
 * @endcode
 *
 * @subsection cgpp_library_test_cgpp_live 2.2 test_cgpp_live Application
 * The test_cgpp_live application takes advantage of CGPP library to handle CNNGen
 * Pre-processing nodes with live stream. Customers can refer it as sample code
 * to write their own application. It querys stream data from IDSP, which means IAV
 * has to be enabled in this scenario. Follow steps below to enable the live stream.
 *
 * @b step @b 1: Modify .lua file to enable pyramid manual feed mode in live stream.
 * Some settings of pyramid are shown as follows.
 * @code {.c}
 *	pyramid = {
 *		input_buf_id = 4,       -- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
 *		scale_type = 0,         -- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
 *		buf_addr = 0x0,
 *		buf_size = 0x0,
 *		manual_feed = 1,
 *		item_num = 5,
 *		layer_map = 0x7F,
 *	},
 * @endcode
 *
 * @b step @b 2: Setup IAV and enable live stream. Use imx274 mipi camera model for example here.
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi  (Need add extra module params for cv5: vinc_id=8 bus_id=3 )
 * board # test_aaa_service -a&
 * board # rmmod ambarella_fb
 * board # modprobe ambarella_fb resolution=1920x1080 mode=clut8bpp buffernum=4
 * (cv2x command as below)
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv22_vin0_1080p_linear.lua --hdmi 1080p --ors 1920x1080
 * (or cv5 command as below, check inside vout_hdmi.lua,  selected vout osd_rescaler_output_window = {0, 0, 1920, 1080})
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * @endcode
 *
 * @subsection cgpp_library_test_cgpp_live_in_resize_mode 2.2.1 test_cgpp_live in Resize Mode
 * The test_cgpp_live application could be run at resize mode, which does variable resample to
 * crop out the ROI area in live stream and resize the area to the network input resolution, as part of
 * the network inference. Similarly, take Yolo v3 for example here.
 *
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p --stream_A 1080p --pyramid_manual_map 0x3F --pyramid_item_num 5
 * @endcode
 * - Streams live mode (draw on stream without frame sync machine `rtsp://10.0.0.2/stream1`)
 * @code {.c}
 * board # osd_server_yolov3 -p 27182 -f /usr/share/ambarella/eazyai/lua/yolov3_sp50_full.lua -r 180,80,360,320 -s 0 &
 * board # test_cgpp_live -p 27182 -b yolov3_cgpp_resize.bin --nnres 416x416 --pp 1 --roi 480,180,960,720 -n 1 -c 0
 * @endcode
 * - VOUT live mode (draw on VOUT HDMI)
 * @code {.c}
 * board # osd_server_yolov3 -p 27182 -f /usr/share/ambarella/eazyai/lua/yolov3_sp50_full.lua -r 180,80,360,320 &
 * board # test_cgpp_live -p 27182 -b yolov3_cgpp_resize.bin --nnres 416x416 --pp 1 --roi 480,180,960,720 -n 1 -c 0
 * @endcode
 *
 * @subsection cgpp_library_test_cgpp_live_in_warp_mode 2.2.2 test_cgpp_live in WarpAffine Mode
 * The test_cgpp_live application can run at the warpAffine mode, which executes warp affine
 * transform from a specified pyramid layer to a target area which the network requires
 * as a part of the network inference. Here, another example is shown using yolo v3.
 *
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p --stream_A 1080p --fb_res 1920x1080 --fifth_source_buf_res 832x832 --pyramid_input_buf_id 4 --pyramid_manual_map 0x3F  --pyramid_item_num 5
 * @endcode
 * - Streams live mode (draw on stream without frame sync machine `rtsp://10.0.0.2/stream1`)
 * @code {.c}
 * board # osd_server_yolov3 -p 27182 -f /usr/share/ambarella/eazyai/lua/yolov3_sp50_full.lua -s 0 &
 * board # test_cgpp_live -p 27182 -b yolov3_cgpp_warp.bin --nnres 416x416 --pp 2  --pyr-lvl 0 --tran-mat 0.5,0,0,0,0.5,0 -n 1 -c 0
 * @endcode
 * - VOUT live mode (draw on VOUT HDMI)
 * @code {.c}
 * board # osd_server_yolov3 -p 27182 -f /usr/share/ambarella/eazyai/lua/yolov3_sp50_full.lua &
 * board # test_cgpp_live -p 27182 -b yolov3_cgpp_warp.bin --nnres 416x416 --pp 2  --pyr-lvl 0 --tran-mat 0.5,0,0,0,0.5,0 -n 1 -c 0
 * @endcode
 *
 * @subsection cgpp_library_test_cgpp_runtime_rotate_flip 2.3 CGPP Runtime Rotate / Flip
 * The test_cgpp application has been adapted for runtime rotate / flip of CGPP Library.
 * The example just shows the runtime rotate, the runtime flip is the same. To run the
 * application with the feature, users must prepare some test images as follows.
 * Additionally, the outputs of two commonds are the same.
 *
 * @image html test_input_image.jpg "Figure 2-3. Input Image."
 *
 * @b Origin @b image output
 * @code {.c}
 * board # mkdir dump_no_rotate
 * board # test_cgpp -b cgpp_yolov3.bin -v --dump dump_no_rotate --rotate-flip 0 --pp 1 --yuv dog_small_not_rotate_1500_1000_YUV_nv12.bin --ires 1500x1000 --roi 413,208,900,790 --scale-type 1 --nnres 416x416
 * board # md5sum dump_no_rotate/conv*.bin
 * 0ec26523fe401a770b885d16063338f4  dump_no_rotate/conv59.bin
 * 9c8e6dba65461efd0fc433121d5073ce  dump_no_rotate/conv67.bin
 * 55a52e019dc0dd1a50722f0020a2150a  dump_no_rotate/conv75.bin
 * board #
 * @endcode
 *
 * @b Clock-wise @b 90 degree image, users can use the following commands
 * @code {.c}
 * board # mkdir dump_img_rotate_90
 * board # test_cgpp -b cgpp_yolov3.bin -v --dump dump_img_rotate_90 --rotate-flip 7 --pp 1 --yuv dog_small_rotate_90_1500_1000_YUV_nv12.bin --ires 1000x1500 --roi 2,413,790,900 --scale-type 1 --nnres 416x416
 * board # md5sum dump_img_rotate_90/conv*.bin
 * 0ec26523fe401a770b885d16063338f4  dump_img_rotate_90/conv59.bin
 * 9c8e6dba65461efd0fc433121d5073ce  dump_img_rotate_90/conv67.bin
 * 55a52e019dc0dd1a50722f0020a2150a  dump_img_rotate_90/conv75.bin
 * board #
 * @endcode
 *
 * To control the rotate degree, use the option rotate-flip.
 * @verbatim
      none rotate:                   0(00000)
      input need rotate 90:     1(00001)
      input need rotate 180:    6(00110)
      input need rotate 270:    7(00111)
  @endverbatim
 *
 * - - - -
 *
 * @section sec_cgpp_api 3. CGPP API
 * Visit the following link to see details of the API function.
 *      - @ref cgpp-api-details shows API lists.
 *      - @ref cgpp-helper shows related macros enumerations and structures.
 *
 * - - - -
 *
 * @section sec_cgpp_lic 4. License
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
 * @example test_cgpp.c
 * This is a source code file of test_cgpp.
 *
 */
 /*!
  * @example test_cgpp_live.c
  * This is a source code file of test_cgpp_live.
  *
  */
 /*!
 * @defgroup cgpp-api CGPP Library API
 * @brief CGPP Library API, in file cnngen_prep.h
 */
/*! @defgroup cgpp-api-details CGPP Library API details
 *  @ingroup cgpp-api
 *  @brief CGPP API details, in file cnngen_prep.h
 */
/*! @defgroup cgpp-helper CGPP Library API helper
 *  @ingroup cgpp-api
 *  @brief CGPP Helper, in file cnngen_prep.h
 */
/*!
 * @file doc_lib_data_process.h
 * @brief This is a .h file for doxygen document system.
 * @version 0.1
 * @date 2020-02-17
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
 * @page page_lib_dproc_doc Data Process Library API
 *
 * @section sec_dproc_history 0. Revision History
 * <table>
 * <caption id="lib_data_process_rev_history"></caption>
 * <tr align="middle"><th> Library Version <th> Updated Date <th> Modification
 * <tr align="middle"><td rowspan="3"> 1.0.0 <td rowspan="3"> 20200217
 * <tr><td align="left"> • Initial Version
 * <tr><td align="left"> • Updated Section @ref sec_dproc_test, remove the application of Dproc API and use test_eazyai library replacement
 * </table>
 *
 * - - - -
 *
 * @section sec_dproc_overview 1 Overview
 * The data process (DProc) Library provides some simple APIs which are used to process the output
 * generated by the VP processor as VP will not do lots of logical judgement. The section below explains
 * how to use the DProc Library for SSD, YOLOV3, TINY_YOLOV3, and will add support for more networks.
 *
 * For same networks, in most of the time, the methods to get the final result from the VP output are
 * the same, so this library encapsulates the processing code for the same network into one API. Then,
 * according to different networks, users can call the API of the corresponding network to get the final
 * result. In this way,  it can make code leaner, easier to use, and avoid errors.
 *
 * At present, this library has encapsulated the APIs for processing the detected data of SSD, YOLOV3
 * and TINY_YOLOV3. In the future, more APIs will be added as needed.
 *
 * @note
 * - This library is not thread safe.
 * - This library will not be maintained any more, refer to @ref eazyai_arm_postprocess instead.
 *
 * - - - -
 *
 * @section sec_dproc_proc 2 Dproc Library Process
 * @subsection dproc_proc_build 2.1 Build Dproc Library
 * The source code for Dproc library can be found under the path `ambarella/packages/data_process`.
 *
 * For the standard SDK, Dproc library is not compiled by default. If users need to use
 * this library in code, they need to activate "Build Ambarella Data Process library" in
 * `make menuconfig` to compile it.
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * build $ make menuconfig
 *   [*] Ambarella Package Configuration  --->
 *    [*]   Build Ambarella Data Process library
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *   packages  --->
 *      [*] libdata-process (packages/data_process)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *   meta-ambalib  --->
 *      recipes-eazyai  --->
 *          [*] libdata-process (meta-ambalib/recipes-eazyai/libdata-process)
 * @endcode
 *
 * <b>Example</b>
 *
 * To use the Dproc library in application, users need to add `select BUILD_AMBARELLA_DPROC_PACKAGE`
 * to the `AmbaConfig` of application.  For example, the Dproc library is used in `test_ssd_live.c`,
 * users can see the following code in the `AmbaConfig` of `test_ssd_live.c`.
 *
 * @code
 * config BUILD_AMBARELLA_UNIT_TESTS_CV_SSD
 *     bool "Build SSD unit tests"
 *     default n
 *     select BUILD_AMBARELLA_NNCTRL_PACKAGE
 *     select BUILD_AMBARELLA_CAVALRY_MEM_PACKAGE
 *     select BUILD_AMBARELLA_VPROC_PACKAGE
 *     select BUILD_AMBARELLA_DPROC_PACKAGE    ### Compile Dproc library ###
 *     select BUILD_AMBARELLA_SMARTFB_PACKAGE
 *     select CONFIG_AMBARELLA_FREETYPE_SUPPORT
 *     help
 *         Build Ambarella Private SSD unit tests
 * @endcode
 *
 * If the above configuration is correct, after `make sync_build_mkcfg`, users can see
 * that `Build Ambarella Data Process library` has been activated automatically in `make menuconfig`.
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * [*] Ambarella Package Configuration  --->
 *   -*-   Build Ambarella Data Process library
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *   packages  --->
 *      [*] libdata-process (packages/data_process)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *   meta-ambalib  --->
 *      recipes-eazyai  --->
 *          [*] libdata-process (meta-ambalib/recipes-eazyai/libdata-process)
 * @endcode
 *
 * @subsection dproc_proc_proc 2.2 Dproc Library Usage Process
 *
 * The usage of Dproc library mainly includes the following three steps, but for different networks,
 * the processing method of each step will be different, which will be described in detail later.
 *
 * @image html dproc_usage_process.jpg "Figure 2-1. Usage Process."
 *
 * @subsubsection dproc_proc_proc_ssd 2.2.1 Process For SSD
 *
 * 1.dproc_init() for SSD
 *
 * The dproc_init() process of SSD is as follows.
 * @image html dproc_init_for_SSD.jpg "Figure 2-2. Dproc Init For SSD."
 *
 * 2.dproc_run() for SSD
 *
 * The dproc_run() process of SSD is as follows.
 * @image html dproc_run_for_SSD.jpg "Figure 2-3. Dproc Run For SSD."
 *
 * 3.dproc_deinit() for SSD
 *
 * The dproc_deinit() process of SSD is as follows.
 * @image html dproc_deinit_for_SSD.jpg "Figure 2-4. Dproc Deinit For SSD."
 *
 *
 * @subsubsection dproc_proc_proc_yolov3 2.2.2 Process For YOLOV3(TINY_YOLOV3)
 *
 * 1.dproc_init() for YOLOV3(TINY_YOLOV3)
 *
 * The dproc_init() process of YOLOV3(TINY_YOLOV3) is as follows.
 * @image html dproc_init_for_YOLOV3.jpg "Figure 2-5. Dproc Init For YOLOV3(TINY_YOLOV3)."
 *
 * 2.dproc_run() for YOLOV3(TINY_YOLOV3)
 *
 * The dproc_run() process of YOLOV3(TINY_YOLOV3) is as follows.
 * @image html dproc_run_for_YOLOV3.jpg "Figure 2-6. Dproc Run For YOLOV3(TINY_YOLOV3)."
 *
 * 3.dproc_deinit() for YOLOV3(TINY_YOLOV3)
 *
 * The dproc_deinit() process of YOLOV3(TINY_YOLOV3) is as follows.
 * @image html dproc_deinit_for_YOLOV3.jpg "Figure 2-7. Dproc Deinit For YOLOV3(TINY_YOLOV3)."
 *
 * - - - -
 *
 * @section sec_dproc_test 3 Unit Test
 *
 * 1. Call function @ref dproc_init() to initialize the library.
 * 2. Call function @ref dproc_run() to run data processing of SSD
 * or YOLOV3(TINY_YOLOV3).
 * 3. Call function @ref dproc_deinit() to release the library session.
 * 4. Dproc API use method can refer to the code: `ambarella/packages/eazyai/apps/yolov3/` or `ambarella/packages/eazyai/apps/ssd/`.
 *
 * - - - -
 *
 * @section sec_dproc_api 4 Dproc API
 *
 * Visit the following link to see details of the API function.
 *      - @ref dproc-api explains API functions.
 *      - @ref dproc-helper shows related structures, macros and enumerations.
 *
 * - - - -
 *
 * @section sec_dproc_lic 5 License
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
 * this Software to Ambarella International LP
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
 * @defgroup dproc-lib Data Process Library API
 * @brief Related introductions of Dproc library.
 */
/*!
 * @defgroup dproc-api Data Process Library API Details
 * @ingroup dproc-lib
 * @brief Details of Dproc library API, in file lib_data_process.h.
 */
/*!
 * @defgroup dproc-helper Data Process Library API Helper
 * @ingroup dproc-lib
 * @brief Dproc library API Helper: Struct, Enumeration and Macros, in file lib_data_process.h.
 *
 */
/*!
 * @file doc_lib_depth_framewrok.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2021-01-26
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
 * @page page_lib_depth_fw_doc Depth Sensing Framework
 *
 * @section depth_history 0. Revision History
 * <table>
 * <caption id="lib_depth_framewrok_rev_history"></caption>
 * <tr><th> Updated Date          <th align="left"> Modification
 * <tr><td> 20210312              <td> Initial Version
 * <tr><td rowspan="3"> 20210521  <td> 1. Added support for dual frequency decode @ref tof_dual_frequency_decoder
 * <tr>                           <td> 2. Added support for dtof mn34906 @ref tof_input
 * <tr>                           <td> 3. Added support for choosing points manually for ToF wiggling calibraiton @ref tof_wiggle_calib
 * <tr><td rowspan="3"> 20210603  <td> 1. Added support for flying pixel removing @ref tof_flying_pixel_removing
 * <tr>                           <td> 2. Added support for converting depth image from 16 bit to three 8bit channels in JET mode @ref tof_convert_depth
 * <tr>                           <td> 3. Added support for ToF basic setting in menuconfig @ref tof_pro_menu
 * <tr><td rowspan="3"> 20210628  <td> 1. Added support for Section @ref sec_depth_disp_pc_on_ros "3. Display point cloud on ROS"
 * <tr>                           <td> 2. Added support for configuration files description @ref depth_framework_lc_explanation
 * <tr>                           <td> 3. Added support for supported sensor list @ref tof_supported_sensor_list
 * <tr><td rowspan="2"> 20210906  <td> 1. Added support for @ref tof_rgb_registration_calib
 * <tr>                           <td> 2. Added support for @ref tof_draw_osd
 * <tr><td> 20210927              <td> Update files for Section @ref sec_depth_disp_pc_on_ros "3. Display point cloud on ROS"
 * <tr><td rowspan="5"> 20211008  <td> 1. Added DSF log system @ref dsf_log_system, <br>performance profiling @ref dsf_performance_profiling, <br>and diagnosis @ref dsf_diagnosis
 * <tr>                           <td> 2. Added DSF graph viewer @ref depth_framework_graph_viewer
 * <tr>                           <td> 3. Added DSF run-time commands @ref dsf_runtime_commands, <br>and add DSF example usage @ref dsf_example_usage
 * <tr>                           <td> 4. Added DSF menuconfig description @ref depth_framework_required_menuconfig, <br>update DSF customization @ref depth_framework_customization
 * <tr>                           <td> 5. Added DSF components @ref dsf_components "2. Components for Depth Sensing Framework"
 * <tr><td> 20211102              <td> Added support for @ref tof_temperature_calib
 * <tr><td> 20211119              <td> Added point cloud display tool on windows @ref sec_display_on_windows "5. Display Point Cloud on Windows"
 * <tr><td> 20220112              <td> Added refinement for @ref tof_calibration
 * <tr><td> 20220811              <td> Added cases for dual frequency mode calibration @ref tof_calibration
 * <tr><td> 20230420              <td> Added Section of @ref sec_demo_app "6.Demo Application", include @ref demo_visiond "6.1 CV22 Vision D EVK + IMX528" and @ref demo_cv25_adi3500 "6.2 CV25_hazelnut + ADI3500 Sensor"
 * <tr><td> 20230426              <td> Refine @ref demo_cv25_adi3500 "6.2 CV25_hazelnut + ADI3500 Sensor"
 * <tr><td> 20230605              <td> Added table @ref table_demo_adi3500_performance_cv5timn "The performance on CV5_timn"
 * <tr><td> 20230619              <td> Added table @ref table_demo_adi3500_performance_cv2chestnut "The performance on CV2_chestnut", update performance of enable cache.
 * <tr><td> 20230817              <td> Added Section of @ref sec_depth_performance "7. Performance", the performance of IMX528 and IRS2877C running on chip cv25/cv5/cv72
 * <tr><td> 20230913              <td> Updated supported sensor list @ref tof_supported_sensor_list
 * <tr><td> 20230918              <td> Added depth sensing framework software stack @ref depth_framework_software_stack
 * </table>
 *
 * - - - -
 *
 * @section depth_framework 1. Depth Sensing Framework
 *     - Section @ref depth_framework_introduction
 *          - Section @ref depth_framework_architecture
 *          - Section @ref depth_framework_typical_processing_flow
 *          - Section @ref depth_framework_code_hierarchy
 *          - Section @ref depth_framework_required_menuconfig
 *     - Section @ref depth_framework_programming_guide
 *     - Section @ref depth_framework_unit_test
 *          - Section @ref dsf_runtime_commands
 *          - Section @ref dsf_example_usage
 *     - Section @ref depth_framework_customization
 *     - Section @ref depth_framework_profiling_and_debug
 *          - Section @ref dsf_log_system
 *          - Section @ref dsf_performance_profiling
 *          - Section @ref dsf_diagnosis
 *     - Section @ref depth_framework_graph_viewer
 *     - Section @ref depth_framework_lc_explanation
 *     - Section @ref depth_framework_api
 *
 * @subsection depth_framework_introduction 1.1 Depth Sensing Framework Introduction
 *
 * Ambarella depth sensing framework (DSF) is a framework for depth information processing, which is the
 * basis of three-dimensional vision technology. The framework is designed to support various types
 * of depth sensors, easy for extension and customization, lightweight and platform neutral, with
 * highly optimized runtime performance. <br>
 *
 * The framework does not bind to any specific depth technology, it can support 'time of flight (ToF)', 'stereo', and
 * 'structured light'. <br>
 *
 * @subsubsection depth_framework_architecture 1.1.1 Depth Sensing Framework Architecture
 *
 * In Ambarella depth sensing framework, the depth related processing are split into different
 * stages. Upstream stage and downstream stage are connected by pins (input pin, output pin), and
 * data are conveyed in pins. Each stage will employ a component to do the detailed processing.
 * <br>
 *
 * @image html dsf_architecture.png "Figure 1-1. Depth Sensing Framework Architecture."
 *
 * The whole processing flow is described in a readable configuration string. The processing flow
 * is a directed acyclic graph (DAG). Customers can easily modify the configurable string to set up a
 * customized processing graph, according to their applications. <br>
 *
 * During the processing, data is encapsulated in buffers. Buffers are managed by buffer pools,
 * that means stage allocates a buffer from a buffer pool, uses it to convey data, and releases
 * it to the buffer pool when the buffer is not needed. Considering there might be different data types
 * in the whole processing graph, the framework introduces a domain concept, the stages in the same
 * domain use the same type of data. Typically, there are three domains, the first one is for raw
 * data, the second one is for depth / amplitude data, and the third one is for display. <br>
 *
 * To achieve better run-time performance, the framework is able to enable "parallel computing",
 * "chip acceleration", and "memory optimization". <br>
 *
 * "Parallel computing" is automatically enabled when there are enough buffers between stages,
 * different stages are running in data driven mode, different stages' processing can run
 * simultaneously on different processors (digital signal processor (DSP), vector processor (VP), and Arm® cores). <br>
 *
 * Ambarella SDK will provide acceleration libraries for the depth processing, such as lens distortion correction (LDC), iToF
 * decoding, look-up table (LUT) based compensation, depth registration, and so on. <br>
 *
 * About "memory optimization", the framework includes a small memory management module, which will
 * try to allocate the memory buffer with physical continuous manner, so the GDMA engine can be used for
 * some data copy. If multiple stages share the same input, they will also share the buffer
 * without copy. <br>
 *
 * @subsubsection depth_framework_software_stack 1.1.2 Depth Sensing Framework Software Stack
 * The software stack diagram of the depth sensing framework is shown in @ref fig_dsf_software_stack "Figure 1-2".
 * The DSF can be running on AMBA SoC or other platforms, that rely on the dependencies of the component.
 * For example, some filters in external component need OpenCV support; draw depth and amplitude in display component need VOUT support;
 * and LDC in AMBA component depends on NNCtrl and VProc, NNCtrl and VProc need Cavalry device driver to enable the vector processor (VP);
 * amba_phase_to_depth and amba_compensation depend on CV0 library. The send to ROS in the display component can send 3D point clouds and amplitudes to the PC,
 * and these data can be displayed by amba_3dviewer or RViz.
 * @anchor fig_dsf_software_stack
 * @image html fig_dsf_software_stack.jpg "Figure 1-2. DSF Software Stack Diagram."
 * <br>
 *
 * @subsubsection depth_framework_typical_processing_flow 1.1.3 Depth Sensing Framework Typical Flow
 *
 * Typically, there are three types of depth sensors, their processing flow are similar, with slight
 * difference. Below will describe those three typical depth sensing scenarios. <br>
 *
 * <b> iToF </b> <br>
 * iToF sensor outputs four phases raw data per frame for each modulation frequency,
 * there are one or more decode stages, which convert phase into depth and amplitude (confidence),
 * spatial and temporal filter stages can be applied on raw data. LDC and compensation stages are
 * after the decode stage, then the depth / amplitude (confidence) are ready for application usage.
 * In some scenarios, "flying pixel removal" and "hole filling" are also needed. Amplitude can be
 * used for auto exposure (AE).
 * Depth information can be displayed on TV (HDMI) or remote PC (ROS).
 * On ROS, the depth information will be converted into point cloud information. <br>
 *
 * @image html typical_flow_itof.png "Figure 1-3. Typical Flow of iToF."
 *
 * <b> Structured Light </b> <br>
 * Structured light outputs a single frame, the block matching is applied on
 * captured frame and a reference frame, then it outputs disparity. Disparity will be converted
 * into depth information. Spatial and temporal filter stages can be applied on depth.  Depth
 * information can be displayed on TV (HDMI) or remote PC (ROS). On ROS, the depth information will
 * be converted into point cloud information. <br>
 *
 * @image html typical_flow_of_structured_light.png "Figure 1-4. Typical Flow of Structured Light."
 *
 * <b> SW Stereo </b> <br>
 * There are two sensors in stereo, they will output two frames, the block matching is
 * applied on those two captured frames, then it outputs disparity. Disparity will be converted
 * into depth information. Spatial and temporal filter stages can be applied on depth. Depth
 * information can be displayed on TV (HDMI) or remote PC (ROS). On ROS, the depth information will
 * be converted into point cloud information. <br>
 *
 * @image html typical_flow_of_sw_stereo.png "Figure 1-5. Typical Flow of SW Stereo."
 * <br>
 *
 * @subsubsection depth_framework_code_hierarchy 1.1.4 Depth Sensing Framework Code Hierarchy
 * The source code location is under `ambarella/packages/depth_sensing_framework`, subfolder content
 * are listed below. <br>
 *
 *    - <b> conf </b> Example of graph configuration string <br>
 *    - <b> doc </b> Simple help file <br>
 *    - <b> example_components </b> Example customized components <br>
 *    - <b> include </b> Header file for interface <br>
 *    - <b> internal_include </b> Header file for internal usage <br>
 *    - <b> ros </b> ROS setup guide and ROS display app source code <br>
 *    - <b> scripts </b> Example scripts to set up depth sensors <br>
 *    - <b> source </b> Source files of the framework <br>
 *        - <b> source/components </b> Embedded components <br>
 *        - <b> source/data_io </b> Data io <br>
 *        - <b> source/graph </b> Framework code about the processing graph <br>
 *        - <b> source/iav_al </b> IAV abstraction layer <br>
 *        - <b> source/lc_config </b> Configuration string (.lc file) parsing <br>
 *        - <b> source/platform_al </b> Platform abstraction layer <br>
 *        - <b> source/text_io </b> Text io for string parsing <br>
 *        - <b> source/utility </b> Utility functions <br>
 *    - <b> tools </b> Tools for the framework <br>
 *    - <b> unit_test </b> Unit test of the framework <br>
 *
 * - - - -
 *
 * @subsubsection depth_framework_required_menuconfig 1.1.5 Depth Sensing Framework Required Menuconfig
 *
 * First of all, select the depth sensing framework under `ambarella/packages`.
 * @code {.c}
 * -> Ambarella Package Configuration  --->
 *    [*]Build Ambarella Depth Sensing Framework  --->
 * @endcode
 *
 * Then select needed components under each category, by default, most of them are selected.
 * @code {.c}
 * -> Ambarella Package Configuration  --->
 *    [*]Build Ambarella Depth Sensing Framework  --->
 *        [*]   Build Ambarella accelerated components for DSF  --->
 *        [*]   Build c components for DSF  --->
 *        [*]   Build by extern lib components for DSF  --->
 *        [*]   Build display components for DSF  --->
 *        [*]   Build example customized components for DSF  --->
 * @endcode
 *
 * There are some other menuconfigs needed to be updated. One is that users should select correct time of fly (ToF) sensors
 * and RGB sensors.
 * @code {.c}
 * -> Ambarella Linux Configuration  --->
 *    [*]   Ambarella Private Drivers Configuration  --->
 *        [*]   Build Ambarella private Vin modules  --->
 *            [*]   Ambarella TOF Sensor Configuration  --->
 *                [*] Sony IMX316 43.2K TOF sensor(MIPI)
 *                [*] Sony IMX456 0.3M TOF sensor(MIPI)
 *                [*] Sony IMX528 0.3M TOF sensor(MIPI)
 *                [*] Panasonic MN34906 0.3M TOF sensor(MIPI)
 *                [*] Infineon IRS2877C 0.3M TOF sensor(MIPI)
 * @endcode
 *
 * Select RGB sensors for example.
 * @code {.c}
 * -> Ambarella Linux Configuration  --->
 *    [*]   Ambarella Private Drivers Configuration  --->
 *        [*]   Build Ambarella private Vin modules  --->
 *            [*]   Ambarella Sensor Configuration  --->
 *                [*] Sony IMX327 2.13M CMOS sensor(Serial LVDS)
 *                [*] Sony IMX327 2.13M CMOS sensor(MIPI)
 * @endcode
 *
 * Since some scenarios need three channels: ToF sensor, RGB sensor, and raw encode.
 * So it is better to change the maximum channel to 4.
 * @code {.c}
 * -> Ambarella Linux Configuration  --->
 *    [*]   Ambarella Private Drivers Configuration  --->
 *        [*]   Define Common Macros  --->
 *            (4)   Max VIN Channel Number
 * @endcode
 *
 * Change image data distributed method to be ROBOT type.
 * @code {.c}
 * -> Ambarella Prebuild  --->
 *    [*]   Configure to include Ambarella Image Data  --->
 *        [*]   Configure Ambarella Image Data Method  --->
 *            [*]   Select to Ambarella Image Data in distributed method.  --->
 *                [*]   Select to Ambarella Image Data ROBOT type
 * @endcode
 *
 * - - - -
 *
 * @subsection depth_framework_programming_guide 1.2 Depth Sensing Framework Programming Guide
 *
 * There are few application programming interface (APIs) of depth sensing framework listed below,
 * refer to `ambarella/packages/depth_sensing_framework/include/amba_dsf_if.h` <br>
 *
 * Setup processing graph, the graph description is readable string (graph_info)
 * @code {.c}
 * int dsf_graph_setup(dsf_graph_t *p_graph,
 *   const dsf_prerequisites_t *p_prerequisites,
 *   const char *graph_info, unsigned int info_len,
 *   dsf_component_proto_t *customized_component_list,
 *   unsigned char *p_ext_mem, unsigned int ext_mem_size);
 * @endcode
 *
 * Clean processing graph
 * @code {.c}
 * void (*clean)(struct dsf_graph_s *p_graph);
 * @endcode
 *
 * Start processing
 * @code {.c}
 * int (*start_loop)(struct dsf_graph_s *p_graph,
 *     unsigned int end_stage_index);
 * @endcode
 *
 * Stop processing
 * @code {.c}
 * int (*stop_loop)(struct dsf_graph_s *p_graph);
 * @endcode
 *
 * <br>
 * The graph needs some prerequisites
 * Setup prerequisites
 * @code {.c}
 * int dsf_prerequisites(dsf_option_t *option,
 *   dsf_prerequisites_t *p_prerequisites);
 * @endcode
 *
 * Clean prerequisites
 * @code {.c}
 * void dsf_clean_prerequisites(
 *   dsf_prerequisites_t *p_prerequisites);
 * @endcode
 *
 * <br>
 * Below are utility APIs
 * <br>
 * Get a version
 * @code {.c}
 * void dsf_get_version(dsf_version_t *version);
 * @endcode
 * <br>
 * Set a log level
 * @code {.c}
 * void dsf_set_log_level(int log_level);
 * @endcode
 * <br>
 * Set a log file name
 * @code {.c}
 * int dsf_set_log_file_name(const char *log_file_name);
 * @endcode
 * <br>
 * Set a log file name
 * @code {.c}
 * void dsf_print_errcode(int code);
 * @endcode
 * Get an error code string
 * @code {.c}
 * const char *dsf_get_errcode_string(int code);
 * @endcode
 *
 * - - - -
 *
 * @subsection depth_framework_unit_test 1.3 Depth Sensing Framework Unit Test
 *
 * Source code here: ambarella/packages/depth_sensing_framework/unit_test/test_amba_dsf.c
 * test command line
 * @code {.c}
 * ./test_amba_dsf ../conf/dsf_dummy_c.lc --loglevel 7
 * @endcode
 *
 * - - - -
 *
 * @subsubsection dsf_runtime_commands 1.3.1 Depth Sensing Framework Run-time Commands
 *
 * DSF can support run-time commands. There are three typical
 * command handlers in DSF: the unit test (test_amba_dsf), the graph, and each component.
 * Below is the current supported run-time command list:
 *
 *  | Command | Parameter Type | Description | Handler Type |
 *  | :----: | :----: | :----: | :----: |
 *  | h | none | Help | test_amba_dsf |
 *  | q | none | Quit | test_amba_dsf |
 *  | p | none | Prints the performance profiling | test_amba_dsf |
 *  | s | none | Prints run-time status of stages | test_amba_dsf |
 *  | log level | integer | Changes the log level | Graph |
 *  | print memory | integer | Enables/Disables print data statistics in memory | Graph |
 *  | print stages | none | Print stages in graph | Graph |
 *  | bypass | stage_name + integer | Bypass stage or not | Graph |
 *  | idle | stage_name + integer | Idle stage or not | Graph |
 *  | reset profiling | none | Reset profiling | Graph |
 *  | print depth | integer | Prints the depth or not | Component (phase_to_depth) |
 *  | print conf | integer | Prints the amplitude (confidence) or not | Component (phase_to_depth) |
 *  | gt depth | float | Specifies the depth's ground truth | Component (phase_to_depth) |
 *  | cap ply | none | Capture the ply file | Component (phase_to_depth) |
 *  | dump depth_amp | none | Dumps the depth and amplitude data | Component (phase_to_depth) |
 *  | iir order | integer | Specifies the IIR order | Component (temporal_filter) |
 *  | decay_a | float | Specifies the decay_a | Component (temporal_filter) |
 *  | decay_b | float | Specifies the decay_b | Component (temporal_filter) |
 *  | decay_ab | float | Specifies the decay_ab | Component (temporal_filter) |
 *  | decay_a | float | Specifies the decay_a | Component (temporal_filter) |
 *  | cap raw | none | Captures the raw | Component (itof_sensor_input) |
 *  | print temper | integer | Prints the temperature or not | Component (itof_sensor_input) |
 *  | check conf | integer | Checks the confidence or not | Component (compensation) |
 *  | conf threshold | integer | Specifies the confidence threshold | Component (compensation) |
 *  | crop depth | integer | Crops the depth or not | Component (compensation) |
 *  | enable ldc | integer | Enables the LDC or not | Component (ldc) |
 *  | dec method | integer | Specifies the decode method | Component (dual_freq_decoder) |
 *  | remove_thr | float | Specifies the flying pixel removal threshold | Component (flying_pixel_removal) |
 *  | rm invalid | integer | Specifies the removing invalid depth threshold | Component (flying_pixel_removal) |
 *  | conf th | integer | Specifies the confidence threshold | Component (flying_pixel_removal) |
 *  | c | integer | Sets the folder number for calibration data | Component (idsp_phase_ir) |
 *
 * - - - -
 *
 * @subsubsection dsf_example_usage 1.3.2 Depth Sensing Framework Example Usage
 *
 * The needed .lc files can be found under `ambarella/packages/depth_sensing_framework/conf`
 * The needed script, lua file, and compensation file can be found at `ambarella/packages/depth_sensing_framework/scripts`
 * and `ambarella/prebuild/ambarella/library/amba_tof/board`. <br>
 *
 * Below are some example usages.
 *
 * Without a real sensor, the user can run with a dummy lc file
 * @code {.c}
 * ./test_amba_dsf ../conf/dsf_dummy_c.lc --loglevel 7
 * @endcode
 * <br>
 *
 * - - - -
 *
 * With a IMX528 sensor
 * Prerequisites
 * @code {.c}
 * ./run_tof_528.sh
 * or
 * ./run_tof_528_efm.sh
 * @endcode
 * <br>
 *
 * Run with sunny optical IMX528 module
 * @code {.c}
 * test_amba_dsf dsf_imx528_amba_120m_sun.lc --loglevel 7
 * @endcode
 *
 * Run with sunny optical IMX528 module, with flying pixel removal
 * @code {.c}
 * test_amba_dsf dsf_imx528_amba_120m_sun_fpr.lc --loglevel 7
 * @endcode
 *
 * Run with sunny optical IMX528 module, with yolov5 and draw yolov5 detection result on Linux frame buffer
 * @code {.c}
 * test_amba_dsf dsf_imx528_amba_120m_sun_yolov5_fb.lc --loglevel 7
 * @endcode
 *
 * Run with sunny optical IMX528 module, with yolov5 and draw yolov5 detection result into EFM
 * @code {.c}
 * test_amba_dsf dsf_imx528_amba_120m_sun_yolov5_efm.lc --loglevel 7
 * @endcode
 * <br>
 *
 * - - - -
 *
 * Run with polight IMX528 module
 * @code {.c}
 * test_amba_dsf dsf_imx528_amba_120m_polig.lc --loglevel 7
 * @endcode
 *
 * Run with polight IMX528 module, with flying pixel removal
 * @code {.c}
 * test_amba_dsf dsf_imx528_amba_120m_polig_fpr.lc --loglevel 7
 * @endcode
 *
 * Run with IMX528 module, do not involve any post-processing for calibration
 * @code {.c}
 * test_amba_dsf dsf_imx528_amba_120m_dec_for_calib.lc --loglevel 7
 * @endcode
 * <br>
 *
 * - - - -
 *
 * With a IRS2877c sensor
 * Prerequisites
 * @code {.c}
 * ./run_tof_irs2877c.sh
 * @endcode
 * <br>
 *
 * Run with IRS2877c module, dual frequency
 * @code {.c}
 * test_amba_dsf dsf_irs2877c_amba_dual.lc --loglevel 7
 * @endcode
 *
 * Run with IRS2877c module, dual frequency, with flying pixel removal
 * @code {.c}
 * test_amba_dsf dsf_irs2877c_amba_dual_fpr.lc --loglevel 7
 * @endcode
 * <br>
 *
 * - - - -
 *
 * Get run-time performance
 *
 * @code {.c}
 * test_amba_dsf dsf_irs2877c_amba_dual_fpr.lc
 * @endcode
 * Users enter 'p' + ENTER, then may see performance information of each stages, as shown below.
 * First line, there is an "average fps", which means average fps of the graph (from this stage's observation).
 * Second line, there is a "average proc time" of this stage, and a theoretical maximum fps "maximum stage fps"
 * for this stage.
 * Third line, there is a "total frame num", which records how many frames was processed by this stage in the past.
 * @code {.c}
 * stage[itof_sensor_input, amba_itof_sensor_input] profiling: average FPS 30.318455
 *         stage average proc time 32975711 ns, 32.975712 ms, maximum stage FPS 30.325350
 *         total frame num 80, total msg num 79
 *         processing time 2638056906 ns, percentage 0.999775
 *         wait data time 0 ns, percentage 0.000000
 *         wait out buffer time 594873 ns, percentage 0.000225
 * stage[cal_depth_amp, amba_itof_decoder] profiling: average FPS 29.937582
 *         stage average proc time 25541148 ns, 25.541149 ms, maximum stage FPS 39.152508
 *         total frame num 79, total msg num 158
 *         processing time 2017750762 ns, percentage 0.766316
 *         wait data time 615058617 ns, percentage 0.233592
 *         wait out buffer time 242305 ns, percentage 0.000092
 * @endcode
 * <br>
 *
 * To get the theoretical maximum speed without VIN sensor fps limitation, users can
 * type 'idle itof_sensor_input 1' + ENTER, and type 'reset profiling' + ENTER.
 * Then users will see the maximum process speed without VIN sensor fps limitation.
 * <br>
 *
 * - - - -
 *
 * Get depth statistics (depth precision and accuracy)
 *
 * @code {.c}
 * test_amba_dsf dsf_irs2877c_amba_dual_fpr.lc
 * @endcode
 * Users enter 'gt depth 0.53' + ENTER, then may see depth statistics information, as shown below.
 * It will print AVG depth for each frame, and will print statistics for every 100 frames.
 * Users can find the depth precision and accuracy after entering the ground truth depth.
 * To disable depth statistics print, users can enter 'print depth 0' + ENTER.
 * @code {.c}
 * depth: AVG 0.533714
 * depth: AVG 0.533302
 * depth: AVG 0.533500
 * depth: AVG 0.533515
 * depth: AVG 0.533654, STD_DERV 0.000247, precision 0.000464, GT 0.530000, MAE 0.003654, RMSE 0.003662, accuracy 0.006910
 * @endcode
 * <br>
 *
 * - - - -
 *
 * Get help on run-time command
 *
 * @code {.c}
 * test_amba_dsf dsf_irs2877c_amba_dual_fpr.lc
 * @endcode
 * Users enter 'h' + ENTER, then may see help information for run-time commands, as shown below.
 * @code {.c}
 * test_amba_dsf runtime commands
 *     'q' or 'quit' + ENTER: quit
 *     's' or 'status' + ENTER: print Status
 *     'p' or 'profiling' + ENTER: print performance Profiling
 *     'log level %%d' + ENTER: set log level
 *     'print memory %%d' + ENTER: print memory 0 or 1
 *     'print stages' + ENTER: print stages
 *     'print depth %%d' + ENTER: print depth 0 or 1
 *     'print conf %%d' + ENTER: print confidence (amplitude) 0 or 1
 *     'gt depth %%f' + ENTER: enter ground truth depth, to print depth_error information
 *     'cap ply' + ENTER: capture a ply file
 *     'dump depth_amp' + ENTER: dump depth and amplitude
 *     'bypass %%s %%d' + ENTER: bypass stage, 0 means no, 1 means yes
 *     'idle %%s %%d' + ENTER: idle stage, 0 means no, 1 means yes
 *     'reset profiling' + ENTER: reset profiling
 *     'iir order %%d' + ENTER: set IIR order
 *     'decay_a %%f' + ENTER: set decay a
 *     'decay_b %%f' + ENTER: set decay b
 *     'decay_ab %%f' + ENTER: set decay ab
 *     'cap raw' + ENTER: capture raw
 *     'print temper %%d' + ENTER: print temperature or not
 *     'check conf %%d' + ENTER: check confidence or not
 *     'conf threshold %%f' + ENTER: confidence threshold
 *     'crop depth %%d' + ENTER: crop depth or not
 *     'enable ldc %%d' + ENTER: enable ldc or not
 *     'dec method %%d' + ENTER: set dec method
 *     'remove_thr %%f' + ENTER: set flying pixel removal threshold
 *     'rm invalid %%d' + ENTER: enable/disable remove invalid depth
 *     'conf th %%d' + ENTER: set confidence threshold
 *     'c %%d' + ENTER: set folder number for calibrition data
 *     'sub bg %%d' + ENTER: enable/disable substract background channel
 *     'h' or 'help' + ENTER: print Help
 *     ENTER: execute last command
 * @endcode
 * <br>
 *
 * - - - -
 *
 * Bypass a stage
 *
 * @code {.c}
 * test_amba_dsf dsf_irs2877c_amba_dual_fpr.lc
 * @endcode
 * Users enter 'bypass flying_pixel_removal 1' + ENTER, then may bypass stage (flying_pixel_removal).
 * Users can check whether there is difference between bypass and not bypass stage (flying_pixel_removal).
 * If users want to re-enable this bypassed stage, they can enter 'bypass flying_pixel_removal 0' + ENTER.
 * <br>
 *
 * - - - -
 *
 * Print stages in graph
 *
 * @code {.c}
 * test_amba_dsf dsf_irs2877c_amba_dual_fpr.lc
 * @endcode
 * Users enter 'print stages' + ENTER, then test_amba_dsf will print stage connections, as shown below.
 * For each stage, those information are printed: its domain, upstream stage, and bypass or not, and so on.
 * @code {.c}
 * print stages
 * stage [itof_sensor_input, amba_itof_sensor_input, 0], its domain [raw]:
 *         bypass 0
 * stage [cal_depth_amp, amba_itof_decoder, 1], its domain [depth_amplitude]:
 *         upstream[0]: [itof_sensor_input]
 *         bypass 0
 * stage [compensation, amba_compensation, 2], its domain [depth_amplitude]:
 *         upstream[0]: [cal_depth_amp]
 *         bypass 0
 * stage [ae, amba_ae, 3], its domain [depth_amplitude]:
 *         upstream[0]: [cal_depth_amp]
 *         bypass 0
 * stage [ldc, amba_ldc, 4], its domain [depth_amplitude]:
 *         upstream[0]: [compensation]
 *         bypass 0
 * stage [flying_pixel_removal, amba_flying_pixel_removal, 5], its domain [depth_amplitude]:
 *         upstream[0]: [ldc]
 *         bypass 0
 * stage [phase_to_depth, amba_phase_to_depth, 6], its domain [depth_amplitude]:
 *         upstream[0]: [flying_pixel_removal]
 *         bypass 0
 * stage [draw, draw_depth, 7], its domain [depth_amplitude]:
 *         upstream[0]: [phase_to_depth]
 *         bypass 0
 * stage [ros, send_to_ros, 8], its domain [depth_amplitude]:
 *         upstream[0]: [phase_to_depth]
 *         bypass 0
 * handle cmd (print stages) done
 * @endcode
 * <br>
 *
 * - - - -
 *
 * Print stage's run-time status
 *
 * @code {.c}
 * test_amba_dsf dsf_irs2877c_amba_dual_fpr.lc
 * @endcode
 * Users enter 's' + ENTER, then test_amba_dsf will print each stage's run-time status, as shown below.
 * For each stage, those information are printed: its state, number of buffers on input pin, number of
 * buffers on output pin, and number of free buffers in the buffer pool, etc.
 * @code {.c}
 * stage[itof_sensor_input, amba_itof_sensor_input] status: 4, Wait Outbuf
 * stage[itof_sensor_input, amba_itof_sensor_input] buffer status:
 *         num in output pin: 0
 *         num in buffer pool: 2
 *
 * stage[cal_depth_amp, amba_itof_decoder] status: 3, Wait Data
 * stage[cal_depth_amp, amba_itof_decoder] buffer status:
 *         num in input pin[0]: 0
 *         num in output pin: 0
 *         num in buffer pool: 2
 * @endcode
 * <br>
 *
 * - - - -
 *
 * @subsection depth_framework_customization 1.4 Depth Sensing Framework Customization
 *
 * The framework is designed to be flexible, that means the customer is able to add their own
 * component as they wish. There are two approaches to add a new component. The first one adds a
 * new component in `ambarella/packages/depth_sensing_framework/source/components`, and adds its prototype
 * into component_factory.c, the other one is a write component externally, and imports the
 * customized component list when the appication invokes dsf_graph_setup(). <br>
 *
 * In addition, the framework also supports customized "configurable string" in .lc file, for the
 * new component, this is convenient for people who do not want to touch DSF library. <br>
 *
 * There are some example customized components, under the folder example_components.
 * Take Yolov5 as an example, implement the create_func, proc_func, and destroy_func in yolov5.c.
 *
 * @code {.c}
 * dsf_component_proto_t proto_test_yolov5 = {
 *     .stage_name = "vca",
 *     .component_name = "od_yolov5",
 *
 *     .create_func = yolov5_create,
 *     .proc_func = yolov5_proc,
 *     .destroy_func = yolov5_destroy,
 * };
 * @endcode
 * <br>
 *
 * Add od_yolov5 into customized component list, in customized_component_factory.c.
 *
 * @code {.c}
 * #ifdef BUILD_DSF_COMPONENT_OD_YOLOV5
 * extern dsf_component_proto_t proto_test_yolov5;
 * #endif
 *
 * #ifdef BUILD_DSF_COMPONENT_OD_YOLOV5
 *         __add_component_proto_into_emd_list(&proto_test_yolov5);
 * #endif
 * @endcode
 * <br>
 *
 * Handle customized property in .lc file for this customized component.
 *
 * @code {.c}
 *         if (!strcmp(p_cur_pty->name, "i")) {
 *             snprintf(thiz->input_dir, sizeof(thiz->input_dir), "%s", p_cur_pty->value);
 *         } else if (!strcmp(p_cur_pty->name, "o")) {
 *             snprintf(thiz->output_dir, sizeof(thiz->output_dir), "%s", p_cur_pty->value);
 *         } else if (!strcmp(p_cur_pty->name, "model")) {
 *             snprintf(thiz->model_path, sizeof(thiz->model_path), "%s", p_cur_pty->value);
 *         } else if (!strcmp(p_cur_pty->name, "type")) {
 *             thiz->model_type = p_cur_pty->value[0];
 *         } else if (!strcmp(p_cur_pty->name, "f")) {
 *             thiz->conf_threshold = atof(p_cur_pty->value);
 *         } else if (!strcmp(p_cur_pty->name, "nms")) {
 *             thiz->nms_threshold = atof(p_cur_pty->value);
 *         } else if (!strcmp(p_cur_pty->name, "top_k")) {
 *             thiz->top_k = atoi(p_cur_pty->value);
 *         } else if (!strcmp(p_cur_pty->name, "u")) {
 *             thiz->use_multi_cls = atoi(p_cur_pty->value);
 *         }
 * @endcode
 * <br>
 *
 * Edit the .lc file to add the customized stage / component into gragh.
 *
 * @code {.c}
 *  Stage
 *   name = vca
 *   component = od_yolov5
 *   domain = rgb
 *   buffer_num = 3
 *   upstream_stage = normalization_jet
 *   bypass = 0
 *   i = ./nn/in/
 *   o = ./nn/out/
 *   model = ./nn/model/
 *   type = s
 *   f = 0.2
 *   nms = 0.3
 *   top_k = 100
 *   u = 0
 * @endcode
 * <br>
 *
 * Also add a new domain if the customized stage / component needs.
 *
 * @code {.c}
 *  Domain
 *   name = rgb
 *   buffer_num = 4
 *   alignment = 64
 *   image_num = 1
 *   Image
 *    channel_num = 3
 *    channel_interleave = 0
 *    pixel_fmt = u8
 * @endcode
 * <br>
 *
 * Finally, pass the customized components list to dsf_graph_setup(), then the
 * customized stage / component is enabled in DSF.
 *
 * @code {.c}
 *         ret = dsf_graph_setup(&graph,
 *             &prerequisites,
 *             (const char *) graph_info, info_len,
 *             setup_module_proto_customized_list(),
 *             prerequisites.mem_info.p_virt_mem_base,
 *             prerequisites.mem_info.tot_mem_size);
 * @endcode
 * <br>
 *
 * - - - -
 *
 * @subsection depth_framework_profiling_and_debug 1.5 Depth Sensing Framework Profiling and Debug
 *
 * @subsubsection dsf_log_system 1.5.1 Depth Sensing Framework Log System
 * There is a log system, users can set the log level and output log to a file or a console.
 * Users can use "--loglevel" to specify the log level, by default, the log level is ILOG_LEVEL_NOTICE (0x04).
 * For log level definition, the user can refer to internal_include/internal_log.h
 *
 *  | Log Level Name | Log Level Value |
 *  | :----: | :----: |
 *  | ILOG_LEVEL_NONE | 0x00 |
 *  | ILOG_LEVEL_FATAL  | 0x01 |
 *  | ILOG_LEVEL_ERROR  | 0x02 |
 *  | ILOG_LEVEL_WARN  | 0x03 |
 *  | ILOG_LEVEL_NOTICE  | 0x04 |
 *  | ILOG_LEVEL_INFO  | 0x05 |
 *  | ILOG_LEVEL_DEBUG  | 0x06 |
 *  | ILOG_LEVEL_VERB  | 0x07 |
 * <br>
 *
 * - - - -
 *
 * @subsubsection dsf_performance_profiling 1.5.2 Depth Sensing Framework Performance Profiling
 *
 * There is a performance profiling feature in DSF. Users can press 'p' + ENTER for test_amba_dsf, it will print
 * each stage cost time (ns) and corresponding fps. The real fps of the graph will also be printed.
 * It is expected to reach maximum fps (30) for VGA (640x480) iToF, on CV2x platform.
 * If users want to get theoretical maximum fps, regardless of the sensor fps limitation, they can idle the sensor
 * input stage, and reset profiling.
 * Here are run-time commands examples: 'idle itof_sensor_input' + ENTER; 'reset profiling' + ENRER; 'p' + ENTER.
 * Then test_amba_dsf will print the maximum fps regardless of the sensor fps limitation.
 * <br>
 *
 * - - - -
 *
 * @subsubsection dsf_diagnosis 1.5.3 Depth Sensing Framework Diagnosis
 *
 * There are three typical ways to diagnose DSF, first one is increasing the log level; the second one is using GDB;
 * the third one is checking run-time status of each stages: 's' + ENTER. The run-time status of stages include
 * the stage state, the buffer number on input pins, the buffer number on output pins and the free buffer number
 * in the buffer pool. <br>
 *
 * - - - -
 *
 * @subsection depth_framework_graph_viewer 1.6 Depth Sensing Framework Graph Viewer
 * This is python tool to view the data processing graph, it will generate a picture from a `.lc` file.
 * The tool is under `ambarella/packages/depth_sensing_framework/tools/graph_viewer`. <br>
 *
 * Prerequisites: install graphviz if it is not installed
 * @code {.c}
 * pip install graphviz
 * @endcode
 * <br>
 *
 * Usage:
 * @code {.c}
 * python ./DSF_graph_viewer.py -i xxxxx.lc -o xxxx.jpg
 * @endcode
 * Parameter '-i' is used to specify the path of input .lc file.
 * Parameter '-o' is used to specify the path of output flowchart.
 * The format of output file can be selected in ".jpg, .png or .pdf".
 * <br>
 *
 * - - - -
 *
 * @subsection depth_framework_lc_explanation 1.7 Depth Sensing Framework Configuration Files Description
 * Configuration files are in the path `ambarella/packages/depth_sensing_framework/conf`. <br>
 * <a href="scripts/dsf_imx528_amba_120m.lc" target="_blank"><b>dsf_imx528_amba_120m.lc</b></a> <br>
 * Some details of the lc files are described here:
 *  | Field | Value | Details |
 *  | :----: | :----: | :----: |
 *  | domain_num | 2  | Memory domain numbers |
 *  | dump_path  | ./ | Path of dumping |
 *  | thread_num_hint | 4 | Thread numbers for components |
 *  | name | IMX528 | Sensor name |
 *  | category | iTOF | Sensor category |
 *  | width | 640 | Resolution width |
 *  | height | 480 | Resolution height |
 *  | vin_id | 1 | Vinc ID for raw capture |
 *  | enable_confidence | 1 | Enable decoding amplitude |
 *  | fx | 513.6133634100554 | Intrinsic paramter: focal length in horizontal directrion |
 *  | fy | 513.6133634100554 | Intrinsic paramter: focal length in vertical directrion   |
 *  | cx | 342.8242453686895 | Intrinsic paramter: image center in horizontal directrion |
 *  | cy | 246.0759997902838 | Intrinsic paramter: image center in vertical directrion   |
 *  | k1 | -0.04544260539644419 | Radial distortion |
 *  | k2 | 0.3089769280456539 | Radial distortion |
 *  | k3 | -0.7618227789466491 | Radial distortion |
 *  | p1 | 0.001979789423728918 | Tangential distortion |
 *  | p2 | 0.004543491564486492 | Tangential distortion |
 *  | cw_freq_0 | 120000000 | First frequency |
 *  | cw_freq_1 | 120000000 | Second frequency used in dual freqency mode |
 *  | raw_channel_num | 4 | Channel numbers in on raw frame |
 *  | raw_sub_interleave | 1 | Raw data interleave subtraction mode |
 *  | raw_rightshift_bits | 4 | Right shift bits for raw data |
 *  | amp_cut_higher_bits | 0 | Cut higher bits of amplitude |
 *  | buffer_num | 4 | Buffer numbers |
 *  | alignment | 64 | Buffer address's alignment (bytes) |
 *  | image_num | 1 | Image number |
 *  | channel_num | 4 | Channel numbers of one frame |
 *  | channel_interleave | 0 | Channel interleave flag |
 *  | pixel_fmt | f32 | Pixel format |
 *
 * @subsection depth_framework_api 1.8 Depth Sensing Framework API
 *
 * Visit the following link to see details of the API function
 *     - @ref dsf-api-flow shows depth sensing framework work flow API
 *     - @ref dsf-api-utility shows depth sensing framework utility API
 *
 * - - - -
 *
 * @section dsf_components 2. Components for Depth Sensing Framework
 *     - Section @ref dsf_components_overview
 *     - Section @ref dsf_c_components
 *     - Section @ref dsf_amba_components
 *     - Section @ref dsf_display_components
 *     - Section @ref dsf_by_extern_lib_components
 *     - Section @ref dsf_customized_components
 *
 * @subsection dsf_components_overview 2.1 Overview of DSF Components
 * Component is a basic process unit in Amba DSF, it is used by a stage. A component can be an embedded one,
 * which is already provided by DSF, or a customized one, which is written by the customer. All components
 * use the same interface to framework for data message processing. Components are classified into several
 * categories for easy maintainence: C components, Amba components, display components,
 * by external library components and example customized components. <br>
 *
 * - - - -
 *
 * @subsection dsf_c_components 2.2 DSF C Components
 * C component is with a pure c implementation, it does not depends on any libraries and does not involve optimization.
 * Typically, c component is used for development and debug purpose. Currently, the c component list is as follows.
 *
 *  | C Components |
 *  | :----: |
 *  | c_itof_decoder |
 *  | c_dual_freq_decoder |
 *  | c_compensation |
 *  | c_spatial_median_filter |
 *  | c_spatial_gaussian_filter |
 *  | c_normalization_jet |
 *  | c_temporal_filter |
 *  | c_temporal_iir_filter |
 *  | c_flying_pixel_removal |
 * <br>
 *
 * @subsubsection c_itof_decoder 2.2.1 C iToF Decoder
 * This component decodes raw frame for iToF sensor, in single frequency's case, its output is distance (phase)
 * and amplitude (confidence).
 * The corresponding accelerated component is amba_itof_decoder.
 * <br>
 *
 * @subsubsection c_dual_freq_decoder 2.2.2 C iToF Dual Frequency Decoder
 * This component decodes raw frame for iToF sensor, in dual frequency's case, its output is distance (phase)
 * and amplitude (confidence).
 * The corresponding accelerated component is amba_dual_freq_decoder.
 * <br>
 *
 * @subsubsection c_compensation 2.2.3 C Compensation
 * This component does wiggling compensation for distance (phase).
 * The corresponding accelerated component is amba_compensation.
 * <br>
 *
 * @subsubsection c_spatial_median_filter 2.2.4 C Spatial Median Filter
 * This component operates spatial median filter.
 * The corresponding accelerated component is amba_spatial_median_filter.
 * <br>
 *
 * @subsubsection c_spatial_gaussian_filter 2.2.5 C Spatial Gaussian Filter
 * This component operates spatial gaussian filter.
 * <br>
 *
 * @subsubsection c_normalization_jet 2.2.6 C Normalization JET
 * This component operates normalization first, then converts data into pseudo-color with JET scheme.
 * <br>
 *
 * @subsubsection c_temporal_filter 2.2.7 C Temporal Filter
 * This component operates simple temporal filter.
 * <br>
 *
 * @subsubsection c_temporal_iir_filter 2.2.8 C Temporal IIR Filter
 * This component operates temporal IIR filter.
 * <br>
 *
 * @subsubsection c_flying_pixel_removal 2.2.9 C Flying Pixel Removal
 * This component operates flying pixel removal.
 * The corresponding accelerated component is amba_flying_pixel_removal.
 * <br>
 *
 * - - - -
 *
 * @subsection dsf_amba_components 2.3 DSF AMBA Components
 * AMBA component is implementation with Ambarella acceleration, it may depends on Ambarella libraries and kernel modules
 * such as sensor / VIN driver, IAV driver, NNCtrl, Cavalry, CV0 library, cvlib, lib_amba_tof, and more.
 * Typically, AMBA component has a good running performance. Currently, the AMBA component list is as follows.
 *
 *  | AMBA Components |
 *  | :----: |
 *  | amba_itof_sensor_input |
 *  | amba_dtof_sensor_input |
 *  | amba_itof_decoder |
 *  | amba_dual_freq_decoder |
 *  | amba_itof_dec_for_calib |
 *  | amba_compensation |
 *  | amba_ae_control |
 *  | amba_depth_registration |
 *  | amba_idsp_phase_ir |
 *  | amba_phase_to_depth |
 *  | amba_ldc |
 *  | amba_spatial_median_filter |
 *  | amba_flying_pixel_removal |
 * <br>
 *
 * @subsubsection amba_itof_sensor_input 2.3.1 AMBA iToF Sensor Input
 * This component reads raw frame from iToF sensor, its output is sensor raw data.
 * <br>
 *
 * @subsubsection amba_dtof_sensor_input 2.3.2 AMBA dToF Sensor Input
 * This component reads raw frame for dToF sensor, its output is distance and amplitude.
 * <br>
 *
 * @subsubsection amba_itof_decoder 2.3.3 AMBA iToF Decoder
 * This component decodes raw frame for iToF sensor, in single frequency's case, its output is distance (phase)
 * and amplitude (confidence).
 * <br>
 *
 * @subsubsection amba_dual_freq_decoder 2.3.4 AMBA iToF Dual Frequency Decoder
 * This component decodes raw frame for iToF sensor, in dual frequency's case, its output is distance (phase)
 * and amplitude (confidence).
 * <br>
 *
 * @subsubsection amba_itof_dec_for_calib 2.3.5 AMBA iToF Decoder for Calibration
 * This component decodes raw frame for iToF sensor, it is for calibration purpose, so it does not apply
 * any post-processing like global offset compensation, wiggling compensation, spatial and temporal filtering,
 * removing invalid depth and flying pixel removal.
 * <br>
 *
 * @subsubsection amba_compensation 2.3.6 AMBA Compensation
 * This component does wiggling compensation for distance (phase).
 * <br>
 *
 * @subsubsection amba_ae_control 2.3.7 AMBA AE Control
 * This component controls AE according to the current average amplitude (confidence) and AE target.
 * <br>
 *
 * @subsubsection amba_depth_registration 2.3.8 AMBA Depth Registration
 * This component is used to map the depth image to RGB sensor's coordinate.
 * align_mat option is the transform matrix.
 * <br>
 *
 * @subsubsection amba_idsp_phase_ir 2.3.9 AMBA IDSP Phase IR
 * This component is used to process phase (distance) / amplitude (confidence) by image digital signal processing (IDSP).
 * Encode from raw (EFR) is used to send 16 bits phase / amplitude to IDSP.
 * In order to obtain good quality images for lens calibration,
 * 3A parameters in `ambarella/prebuild/ambarella/ibrary/amba_tof/3a` should be loaded by Amage tool.
 * <br>
 *
 * @subsubsection amba_phase_to_depth 2.3.10 AMBA Phase to Depth
 * This component convert phase (distance) to depth, with intrinsic matrix.
 * <br>
 *
 * @subsubsection amba_ldc 2.3.11 AMBA LDC
 * This component operates LDC.
 * <br>
 *
 * @subsubsection amba_spatial_median_filter 2.3.12 AMBA Spatial Median Filter
 * This component operates spatial median filter.
 * <br>
 *
 * @subsubsection amba_flying_pixel_removal 2.3.13 AMBA Flying Pixel Removal
 * This component operates flying pixel removal.
 * <br>
 *
 * - - - -
 *
 * @subsection dsf_display_components 2.4 DSF Display Components
 * Display component is for displaying, it does not include post-processing.
 * Currently, the display component list is as follows.
 *
 *  | Display Components |
 *  | :----: |
 *  | send_to_ros |
 *  | draw_depth |
 *  | draw_osd |
 * <br>
 *
 * @subsubsection send_to_ros 2.4.1 Send to ROS
 * This component sends the depth data to ROS for display.
 * <br>
 *
 * @subsubsection draw_depth 2.4.2 Draw Depth on Linux Frame Buffer
 * This component draws the depth on Linux frame buffer.
 * <br>
 *
 * @subsubsection draw_osd 2.4.3 Draw Overlay for Video Stream Encoding
 * This component draws the depth on overlay for video stream encoding.
 * <br>
 *
 * - - - -
 *
 * @subsection dsf_by_extern_lib_components 2.5 DSF by External Library Components
 * Display component depends on external libraries like OpenCV.
 * Currently, the by external library component list is as follows.
 *
 *  | By External Library Components |
 *  | :----: |
 *  | opencv_flying_pixel_removal |
 *  | opencv_normalization_jet |
 * <br>
 *
 * @subsubsection opencv_flying_pixel_removal 2.5.1 OpenCV Flying Pixel Removal
 * This component operates flying pixel removal, with OpenCV library.
 * <br>
 *
 * @subsubsection opencv_normalization_jet 2.5.2 OpenCV Normalization JET
 * This component operates normalization first, and then converts data into pseudo-color with JET scheme.
 * This component depends on OpenCV library.
 * <br>
 *
 * - - - -
 *
 * @subsection dsf_customized_components 2.6 DSF Customized Components
 * Typically, customized component is written by customers, DSF also includes example codes for
 * some customized components. Currently, the customized component list is as follows.
 *
 *  | Customized Components |
 *  | :----: |
 *  | yolov5 |
 *  | feed_to_efm |
 *  | combine_depth_nv12_bbox |
 *  | draw_det_fb |
 * <br>
 *
 * @subsubsection yolov5 2.6.1 Yolov5
 * This component loads and executes Yolov5 on depth data.
 * <br>
 *
 * @subsubsection feed_to_efm 2.6.2 Feed to EFM
 * This component feeds the data to EFM.
 * <br>
 *
 * @subsubsection combine_depth_nv12_bbox 2.6.3 Combine Depth and BBox
 * This component combines the depth and bounding boxes.
 * <br>
 *
 * @subsubsection draw_det_fb 2.6.4 Draw detection result on Linux Frame Buffer
 * This component draws the detection result on Linux frame buffer.
 * <br>
 *
 * - - - -
 *
 * @section depth_tof 3. ToF Sensor
 *     - Section @ref tof_introduction
 *     - Section @ref tof_supported_sensor_list
 *     - Section @ref tof_calibration
 *     - Section @ref tof_process
 *     - Section @ref tof_pro_stages
 *
 * @subsection tof_introduction 3.1 ToF Introduction
 * ToF is used for extraction of three-dimensional information from scene by using modulated light
 * at specific wavelength. The phase difference between the emitted light and the light reflecting
 * off the scene is measured, per pixel, and converted to depth. By using camera intrinsic
 * parameters, each pixel can be transformed into three-dimensional coordinates. <br>
 * The cw-iToF (continues wave) method consists of illuminating the scene with a light source, which
 * amplitude is sinusoidally modulated at a certain high frequency. Once the light is emitted
 * towards the scene, it changes its phase delay in relation to the time delay interleaving the
 * emission and the detection (after the reflection).
 * This time delay (or more correctly time of flight) is related to the distance of objects within
 * the scene; thus starting from the phase delay it is possible to compute the distance of the
 * acquired scene, pixel by pixel.
 * In order to measure the phase delay it is possible to sample the back-reflected light four times
 * per period and using the Fourier Transform algorithm it is possible to compute the phase of the
 * reflected light in respect to the reference signal.
 * @image html tof_principle.png "Figure 3-1. Depth Principle."
 * Sinusoidal reflected light compared to the reference signal. The amplitude of the reflected
 * light is less than those of the emitted light because of the reflection of objects in the scene.
 * Moreover the ambient background light changes the offset of the acquired light. The algorithm
 * deals with the four samples (c0, c1, c2, and c3) of the reflected light allowing the calculation
 * of the phase delay between the two signals using the Fourier Transform equations.
 * The figure above shows the distance generated using the emitted and reflecting light.
 *
 * @subsection tof_supported_sensor_list 3.2 Supported Sensor List
 *
 * There are several sensors already supported for ToF function.
 *
 * Here is the supported sensor list for ToF:
 *  | Sensors | Resolution | Status | Modules |
 *  | :----: | :----: | :----: | :----: |
 *  | IMX316 | 240x180 | supported | Liteon |
 *  | IMX456  | 640x480 | supported | Liteon |
 *  | IMX528  | 640x480 | supported | Polight & SunnyOptical |
 *  | IRS2877c  | 640x480 | supported | Oflim |
 *  | OZT167C  | 640x480 | supported | Infineon |
 *  | ADSD3500  | 512x512 & 1024x1024 | supported | ADI |
 * - - - -
 *
 * @subsection tof_calibration 3.3 ToF Calibration
 * Users should perform the calibration as shown in the steps below: <br>
 * 1) Temperature calibration: remove sensor's temperature drift <br>
 * 2) Lens calibration: remove lens' distortion <br>
 * 3) Global calibration: common offset between the measured distance and the real distance <br>
 * 4) Wiggling calibration: nonlinear offset between the measured distance and the real distance <br>
 *
 * The flow of calibration is as shown in the steps below: <br>
 * 1) Capture the temperature calibration data and perform the temperature calibration. <br>
 * 2) Capture the lens calibration dataset, and peform the lens calibration. <br>
 * 3) Modify lc file according to the lens calibration's result (fx, fy, cx, cy, k1, k2, p1, p2, k3). <br>
 * 4) Capture the global / wiggling calibration dataset. <br>
 * 5) Perform the global calibration. <br>
 * 6) According to the global calibration results, peform the wiggling calibration. <br>
 *
 * @subsubsection tof_calib_build_step 3.3.1 ToF Build Steps
 * First, set the basic ToF information in menuconfig.
 * Configure the depth sensing framework and choose required modules.
 * @code {.c}
 * -> Ambarella Package Configuration
 *    [*]Build Ambarella Depth Sensing Framework
 * @endcode
 *
 * Configure amb_tof library.
 * @code {.c}
 * -> Ambarella Prebuild
 *    [*] Configure Ambarella amba_tof library
 * @endcode
 *
 * Configure ToF sensors.
 * @code {.c}
 * -> Ambarella Linux Configuration
 *    -> Ambarella Private Drivers Configuration
 *      -> Build Ambarella private Vin modules
 *         -> Ambarella ToF Sensor Configuration
 *           [*] Sony IMX316 43.2K ToF sensor(MIPI)
 *           [*] Sony IMX456 0.3M ToF sensor(MIPI)
 *           [*] Sony IMX528 0.3M ToF sensor(MIPI)
 *           [*] Panasonic MN34906 0.3M ToF sensor(MIPI)
 * @endcode
 *
 * Configure pre-build modules.
 * @code {.c}
 * -> Ambarella Prebuild
 *   -> CONFIG Ambarella Aicam prebuild
 *      -> [*] Configure Ambarella Optimized Aicam Algos Library
 *      -> [*] Configure Traditional Aicam Algos Library
 *      -> [*] Configure Ambarella Software CV Library
 * @endcode
 *
 * @subsubsection tof_calib_capture 3.3.2 Calibration Dataset Capturing
 * 3A and lc files are located in the path `ambarella/packages/depth_sensing_framework/data_files`. <br>
 * Calibration related configuration files are located in the path `ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/script` <br>
 * The amplitude images are gray scale images.
 * The detection of the chessboard in amplitude images could be used <br>
 * to do lens / global / wiggling calibration. <br>
 * Amage tool is used to adjust the brightness of the amplitude images. <br>
 * @image html amage_tool.png "Figure 3-2. Amage Tool."
 * The image shows the steps to apply the 3A parameters on amplitude images by raw encode. <br>
 * Step 1: Connect the tool with the board by telnet. <br>
 * Step 2: Open the 3A configuration files. <br>
 * Files are stored in `ambarella/packages/depth_sensing_framework/data_files/3a`.
 * calib_3D.bin / calib_reg.bin should be modified in ir_calibration.txt accordingly. <br>
 * Step 3: Choose the specific channel. <br>
 * Step 4: Apply the 3A parameters. <br>
 * Step 5: Choose the before_ce_wb_gain stage. <br>
 * Step 6: Change the gain value （set r_gain / g_gain / b_gain the same）to adjust the brightness, <br>
 * and click apply button. <br>
 *
 * Commands to enter the preview state and mount the share folder: <br>
 * @code {.c}
 * board # ./run_tof_xx.sh
 * board # mount -t cifs -o domain=ambarella,sec=ntlmssp,username=xx,password=xx,uid=0,
 * gid=0,file_mode=0755,dir_mode=0755 //10.0.0.5/share /mnt
 * @endcode
 *
 * Run depth framework and capture the camera calibration dataset:
 * @code {.c}
 * (A) Single frequency mode case :
 * board # test_amba_dsf dsf_imxxxx_amba_dump_calib.lc
 * (B) Dual frequency mode case :
 * board # test_amba_dsf dsf_irs2877a_amba_dump_calib_dual_lens_calib_ambadualdec.lc (if the sensor is irs2877a)
 * host  $ use Amage tool to read configurations and adjust 3A for amplitude images.
 * tof_conf_capture.sh is in ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/script/tof
 * board # ./tof_conf_capture.sh 0 30
 * @endcode
 *
 * Run depth framework and capture the temperature calibration dataset:
 * @code {.c}
 * board # mkdir calibration
 * (A) Single frequency mode case :
 * board # test_amba_dsf dsf_xxx_amba_xxx_dec_for_calib.lc
 * The data will be stored in accuracy.csv of the calibration folder.
 * Like ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/calib_data/tof/accuracy.csv.
 * (B) Dual frequency mode case :
 * board # test_amba_dsf dsf_irs2877a_amba_dump_calib_dual_laser_calib_ambadualdec.lc (if the sensor is irs2877a)
 * The distance values of the crosshair will be reported like below :
 * - frequency 0 center average value 1.146080
 * - frequency 1 center average value 1.877759
 * when put the camera to the other postion, enter "c 2", the terminal will report the other location's distance.
 * @endcode
 *
 * Run depth framework and capture the global / wiggling dataset: <br>
 * If the temperature calibration has been done, <br>
 * fill the temperature fitting parameters to the stage cal_depth_amp / itof_dec_for_calib <br>
 * to do the temperature compensation first, options are "line_slopy" and "base".
 * Global and wiggling calibration use the same dataset.
 * @image html global_wiggiling.png "Figure 3-3. Capture Global / Wiggling Dataset."
 * The image shows how to capture the global / wiggling dataset from close to the far distance. <br>
 *
 * 1) For the single frequency short range (0 - 1.25 meters) calibration, <br>
 * it is suggested to use the chessboard to perform the calibration. <br>
 * The chessboard should be rigid and flat. If the chessboard's accuracy is not good enough, <br>
 * it is suggested to use the laser method to do calibration. <br>
 * The chessboard corners could be detected automatically to get the points' ToF distance <br>
 * and caculate out the points' actual distance. Set "dump_calib = 1" in dsf_imxxxx_amba_dump_calib.lc, <br>
 * and modify the lc file's option (fx, fy, cx, cy, k1, k2, p1, p2, k3) according to the lens calibration's result. <br>
 * "dump_path" is the path to store the calibration data. <br>
 *
 * @code {.c}
 * board # test_amba_dsf dsf_imxxxx_amba_dump_calib.lc
 * @endcode
 * Run-time command "c" is used to create the folder and save the calibration data.
 * Record the distance information and YUV with a step of 10 cm from near to far. <br>
 * ToF distance information is stored in tof_distance.csv. <br>
 * tof_canvas_xx.yuv is used to detect the chessboard's coner coordinates. <br>
 *
 * 2) For the long range (greater than 1.25 meters), it is suggested to use the laser to perform the calibration. <br>
 * @image html crosshair.png "Figure 3-4. Crosshair."
 * Paste one crosshair image on the wall, and focus the principle center on the crosshair when recording distances. <br>
 * "draw_crosshair = 1" in dsf_xxx_amba_xxx_dec_for_calib_laser.lc is used to show the center crosshair on the amplitude image.
 * Record the distance information (ToF and laser measurement) <br>
 * with a step of 10 cm from near to far. <br>
 * @code {.c}
 * board # test_amba_dsf dsf_imxxxx_amba_xxxm_dec_for_calib_laser.lc
 * Key information (ToF distance) report :
 * distance(meter): AVG xx, STD_DERV xx, precision xx
 * @endcode
 * Fill the ToF distance and the measuring distance (by laser) in the nl_laser.csv, for example
 * `ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/calib_data/tof/nl_laser.csv`.
 *
 * @subsubsection tof_lens_calib 3.3.3 Lens Calibration
 * This calibration is used to remove lens' distortion, every pixel will be converted into the ideal
 * coordinate in the pin-hole model by removing the distortion.
 * Ambarella suggests using the Zhang Zhengyou calibration method for pinhole lens.
 * Lens calibration is very important, because the intrinsic and distortion parameters
 * will influence the calculation accuracy of extrinsic parameters.
 * It is better to capture more than fifty images to reduce the fitting error.
 * To avoid the chessboard to be detected with failure, ensure that every chessboard in the picture is big
 * enough.
 *
 * Use PC calibration tool to do lens calibration.
 * Tools are located in the path `ambarella/prebuild/ambarella/library/multi_sensor_calib/calib_tool`
 * Refer to the document Sensor Calibration Library API of Lens Calibration section.
 * Modify run_cali.sh, and add the option like "yuv_w=4096 -yuv_h=2160 -yuv_name=fuse_canvas3_4096x2160_NV12 -k4=1 -k5=1 -k6=1"
 * in funciton "run_lens_calib()".
 * Calibration results containing intrinsic matrix and distortion parameters will be reported as below : <br>
 * Intrinsic[1063.124773676325, 0, 973.8136518801646;0, 1063.124773676325, 541.1757522380176;0, 0, 1] <br>
 * dist_coeffs[-0.08726931759522329;0.06903056691830357;6.280400379716693e-05;-0.0006512637770184914;-0.01574894685520492;]
 *
 * Parameters meanings are:
 * Intrinsic[fx, 0, cx; 0, fy, cy; 0, 0, 1]
 * dist_coeffs[k1; k2; p1; p2; k3]
 * Refer to @ref guide_sensor_calib_lens for more details.
 *
 * @subsubsection tof_temperature_calib 3.3.4 Temperature Offset Calibration
 * There is a phase drift introduced by the temperature. It is a linear drift in distance.
 * Users can perform the temperature calibration to add the compensation for distance.
 * Tools are located in the path `ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/script/tof`.
 * Refer to the document Sensor Calibration Library API of ToF Calibration section.
 * Refer to @ref guide_sensor_calib_tof for more details.
 *
 * @subsubsection tof_global_calib 3.3.5 Global Offset Calibration
 * There is a global offset between the measured distance and the real distance.
 * Users just need chessboard or some other calibration targets to do extrinsic calibration and get ground
 * truth distance.
 * Tools are located in the path `ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool`.
 * Users perform the calibration and choose one value as a global offset value from the report.
 * Refer to the document Sensor Calibration Library API of ToF Calibration section.
 * Refer to @ref guide_sensor_calib_tof for more details.
 *
 * @subsubsection tof_wiggle_calib 3.3.6 Wiggling Calibration
 * Modulation wave shape is not perfect as the sinusoidal shape, so the phase delay will not be
 * calculated correctly, and the imperfect phase will introduce the wiggling errors for different
 * distances.
 * Refer to the document Sensor Calibration Library API of ToF Calibration section.
 * After ToF calibration, calibration data can be used for ToF process on chips.
 * Refer to @ref guide_sensor_calib_tof for more details.
 *
 * @subsubsection tof_rgb_registration_calib 3.3.7 ToF and RGB Sensors Registration Calibration
 * The proposed calibration solution provides a mechanism to calibrate RGB and Depth
 * cameras's intrinsic /extrinsic paramters. The depth image could be converted to the RGB's view with the calibration data.
 * Refer to dsf_imx528_amba_120m_register_sun.lc for how to configure the depth registration feature.
 * Refer to @ref guide_sensor_calib_tof_rgbd for more details of calibration.
 * - - - -
 *
 * @subsection tof_process 3.4 ToF Process Modules
 * @image html tof_flow.png "Figure 3-5. ToF Process Flow."
 * This image shows the process flow of Amba ToF. It shows the pipeline from raw phase data to
 * final point cloud.
 *
 * @subsection tof_pro_stages 3.5 ToF Components
 * Here is the supported components lists for ToF function :
 *  | Components |
 *  | :----: |
 *  | amba_dtof_sensor_input |
 *  | amba_itof_sensor_input |
 *  | amba_itof_decoder |
 *  | amba_ae_control |
 *  | amba_compensation |
 *  | amba_depth_register |
 *  | amba_idsp_phase_ir |
 *  | amba_ldc |
 *  | c_compensation |
 *  | c_dual_frequency_decoder |
 *  | c_file_feeder |
 *  | c_flying_pixel |
 *  | c_itof_decoder |
 *  | c_normalization_jet |
 *  | c_spatial_gaussian_filter |
 *  | c_spatial_median_filter |
 *  | c_transfer_depth |
 *  | draw_depth |
 *  | send_to_ros |
 *  | draw_osd |
 *
 * @subsubsection tof_input 3.5.1 ToF Process Input
 * This stage is to query raw / raw sequence and copy to user space. IMX528 supports four phases in
 * one raw frame.
 * MN34906 ouput depth and IR data in one raw frame without decoding.
 * c_file_feeder.c / amba_itof_sensor_input.c / amba_dtof_sensor_input.c are versions for reference.
 * dsf_mn34906_c.lc is a configuration file for reference.
 *
 * @subsubsection tof_temporal_filter 3.5.2 ToF Temporal Filter
 * The median filter is used as one example to remove noise.
 * c_spatial_gaussian_filter.c is a component for reference.
 *
 * @subsubsection tof_spatial_filter 3.5.3 ToF Spatial Filter
 * The gaussian filter is used as one example to remove noise.
 * c_spatial_gaussian_filter.c is a component for reference.
 *
 * @subsubsection tof_pro_decode 3.5.4 ToF Process Decode
 * CW-iToF 4-phase raw pictures can be decoded as two images of distance and amplitude.
 * Amplitude image is used to extract key points and control 3A.
 * @image html tof_formula.png "Figure 3-6. ToF Decode Phase / Amplitude."
 * c_itof_decoder.c/amba_itof_decoder.c in components are common / acceleration versions for
 * reference.
 *
 * @subsubsection tof_idsp_phase_ir 3.5.5 ToF Phase / Amplitude Raw Encode
 * This stage is used to process phase / amplitude by IDSP.
 * Encode from raw (EFR) is used to send 16 bits phase / amplitude to IDSP.
 * In order to have good quality images for lens calibration,
 * 3A parameters in `ambarella/prebuild/ambarella/ibrary/amba_tof/3a` should be loaded by Amage tool.
 * amba_idsp_phase_ir.c is a component for reference.
 * Option: <br>
 * "show": shows amplitude through encode from memory. <br>
 * "dump_calib": enables dump calibration data for wiggling calibration. <br>
 * "frame_mean": uses mean value from depth sequence. <br>
 * "total_num": numbers of frames to capture. <br>
 * "min_conf / max_conf": threshold of amplitude. <br>
 *
 * @subsubsection tof_ldc 3.5.6 ToF LDC
 * LDC is used to remove distortion. Distortion parameters fx,fy,cx,cy,k1,k2,k3,p1,p2
 * should be filled correctly in lc configuration files.
 * amba_ldc.c is a component for reference.
 *
 * @subsubsection tof_compensation 3.5.7 ToF Compensation
 * There are a few features for this stage: <br>
 * 1) Wiggling compensation <br>
 * "gen_com" option should be configured as the first time to generate recognizable format, fit_num
 * is the value from wiggling calibration message. <br>
 * 2) Remove outlier by checking confidence <br>
 * This is used to remove invalid noise in far distance. <br>
 * 3) Crop depth in specific range
 * amba_compensation.c is a component for reference.
 *
 * @subsubsection tof_phase_to_depth 3.5.8 ToF Phase Transformed To Depth
 * This stage is to transform phase to depth, calibration intrinsic and distortion parameters should
 * be filled.
 * "depth_mm" option is used to get depth in millimeter unit.
 * amba_phase_to_depth.c is a component for reference.
 *
 * @subsubsection tof_ae_control 3.5.9 ToF Auto Exposure Control
 * Shutter should be adjusted to avoid overexposure for specific area.
 * Overexposure will cause depth inaccuracy. Ambarella supports two kinds of methods,
 * one is using center area's average amplitude as the target to control shutter,
 * the other one is to use full amplitude image' histogram to control shutter.
 * amba_ae_control.c is a component for reference.
 *
 * @subsubsection tof_rgbd_alignment 3.5.10 ToF RGBD Alignment
 * If customers want to do alignment between RGB sensor and ToF sensor,
 * amba_depth_register.c is used to map depth image to RGB sensor's coordinate.
 * align_mat option is the transform matrix. depth_mm option should be set for phase_to_depth stage.
 * amba_depth_register.c is a component for reference.
 *
 * @subsubsection tof_draw_depth 3.5.11 ToF Draw Depth
 * This stage shows the depth through the frame buffer. Depth should do normalization to 8 bits.
 * Option "depth_mm" should be filled, if the unit is millimeter.
 * draw_depth.c is a component for reference.
 *
 * @subsubsection tof_live_show_ros 3.5.12 ToF Live Point Cloud Shown On Ros
 * This stage is used to send depth information to PC side by socket, remote_port/remote_url options
 * are used to set socket port and address. The depth information will be received in the server
 * side and transformed to cloud point.
 * send_to_ros.c is a component for reference. Refer to ros_on_ubuntu18.04.txt for details on how
 * to set up.
 *
 * @subsubsection tof_dual_frequency_decoder 3.5.13 ToF Dual Frequency Decoding
 * The real distance can not be detected correctly with one kind of frequency.
 * @image html dual_decode.png "Figure 3-7. Real Distance Calculation Formula."
 * Image shows the formula to calculate the real distance, k is a positive number, representing of cycle number.
 * If the distance is bigger than one cycle's distance, it will cause unambiguous range.
 * @image html uncertain.png "Figure 3-8. Unambiguous Range."
 * The image shows the unambiguous range phenomenon.
 * By using dual frequency decoding method, the unambiguous range problem can be resolved. <br>
 * dual_frequency_decoder.c is a component for reference.
 * dsf_imx316_c_dual_freq.lc is a configuration file for reference.
 *
 * @subsubsection tof_flying_pixel_removing 3.5.14 ToF Flying Pixel Removal
 * Even if the distance between the two targets is far, when the two targets are partially overlapped,
 * the contour of the overlapped part of the former target is not clear,
 * and the edge contour cannot be accurately determined due to multiple reflections.
 * @image html fly.png "Figure 3-9. Removing Flying Pixel Image vs Original Image."
 * Ihe image shows the effect of removing flying pixels.
 * dsf_imx528_c_compensation_20m_fly.lc is a configuration file for reference.
 *
 * @subsubsection tof_convert_depth 3.5.15 ToF Convert Depth Format
 * dsf_imx528_c_compensation_20m_jet.lc is a configuration file for reference to convert
 * depth format from 16bit to three 8bit channels in JET mode.
 *
 * @subsubsection tof_draw_osd 3.5.16 ToF Draw OSD
 * This stage is used to show the depth through overlay. Depth will be normalized to 8 bits in the stage.
 * Configure the region of interest (ROI) and alpha value to the specific stream as shown in below .lc file.
 * @code {.c}
 * stream_id = 2
 *   roi_x = 0
 *   roi_y = 0
 *   roi_w = 320
 *   roi_h = 240
 *   alpha = 255
 * stream_id = 1
 *   roi_x = 0
 *   roi_y = 0
 *   roi_w = 640
 *   roi_h = 480
 *   alpha = 128
 * @endcode
 *
 * - - - -
 *
 * @section sec_depth_disp_pc_on_ros 4. Display Point Cloud on ROS
 * This document provides the guidelines for the visual point cloud data with robot operating system (ROS) in Ubuntu and Ambarella CV25 platforms.
 * @subsection host_prepare 4.1 Host PC Preparation
 * The point cloud rendering needs to be done on a PC (host) with a separate graphics card. Do not use a virtual machine to run ROS, it is recommended to use a laptop with good rendering performance directly.
 * @subsubsection hardware_prepare 4.1.1 Hardware Preparation
 * The verified host configuration is as below table.
 * <table>
 * <caption id="lib_depth_framewrok_rev_history"></caption>
 * <tr><th> Host          <th align="left"> Dell Precision 3531
 * <tr><td> CPU              <td> Intel i7-10850H
 * <tr><td> Memory              <td> 16GB, DDR4-2666MHz SDRAM
 * <tr><td> GPU              <td> Nvidia Quadro P620  4GB GDDR5
 * <tr><td> SSD              <td> M.2 2230 512 GB, Gen 3 PCIe x4 NVMe
 * </table>
 * @subsubsection software_prepare 4.1.2 Software Preparation
 * The following table shows the software configuration for the host.
 *
 * <table>
 * <caption id="lib_depth_framewrok_rev_history"></caption>
 * <tr><th> Host          <th align="left"> Dell Precision 3531
 * <tr><td> OS              <td> Ubuntu 18.04 (Recommend, compatibility issues may occur on other versions)
 * <tr><td> GPU driver version              <td> 460.80
 * <tr><td> CUDA version              <td> 11.2
 * </table>
 *
 * Nvidia GPU Driver download：https://www.nvidia.cn/Download/index.aspx?lang=en
 * @image html nvidia_driver_download0.png
 * @image html nvidia_driver_download1.png "Figure 4-1. Step of Nvidia Driver Download."
 *
 * Type the following command on host to see if the installed version of the GPU driver matches the latest version on NVIDIA release.
 *
 * @code {.c}
 * host $ nvidia-smi
 * @endcode
 *
 * Since the older version of the GPU driver may affect the rendering of the point cloud, it is necessary to uninstall the older version of the GPU driver first:
 *
 * @code {.c}
 * host $ sudo apt-get remove --purge nvidia*
 * @endcode
 *
 * Then install the downloaded driver:
 *
 * @code {.c}
 * host $ cd to path of NVIDIA diver
 * host $ sudo sh NVIDIA-Linux-x86_64-460.84.run # install the driver, file name as yours
 * @endcode
 *
 * Finally, type the following command to confirm that the driver is installed to the latest version:
 *
 * @code {.c}
 * host $ nvidia-smi
 * @endcode
 *
 * @subsection ros_prepare 4.2 ROS Preparation
 * The robot operating system (ROS) is a set of software libraries and tools that help you build robot applications.
 * From drivers to state-of-the-art algorithms, and with powerful developer tools, ROS has what you need for your next robotics project.
 * The ROS can render point cloud data from CV25 platform real-time and adjustable.
 *
 * @subsubsection install_ros 4.2.1 Install ROS
 *
 * Install ROS:
 *
 * @code {.c}
 * host $ sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
 * host $ sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
 * host $ sudo apt update
 * host $ sudo apt install ros-melodic-desktop-full
 * @endcode
 *
 * Run ROS core:
 * @code {.c}
 * host $ source /opt/ros/melodic/setup.bash
 * host $ roscore &
 * @endcode
 *
 * Install PCL and RViz:
 *
 * @code {.c}
 * host $ sudo apt-get install ros-melodic-pcl-ros
 * host $ sudo apt-get install RViz
 * @endcode
 *
 * Compile host program:
 *
 * @code {.c}
 * host $ mkdir -p ~/catkin_ws/src
 * host $ cd ~/catkin_ws/src
 * host $ catkin_init_workspace
 * host $ cd ~/catkin_ws/
 * host $ catkin_make
 * host $ source devel/setup.bash
 * host $ cd ~/catkin_ws/src
 * host $ catkin_create_pkg amba_tof pcl_conversions pcl_ros pcl_msgs sensor_msgs
 * host $ rospack profile
 * host $ roscd amba_tof
 * @endcode
 *
 * copy amba_ros source code (ambarella/packages/depth_sensing_framework/ros/display_app) to ~/catkin_ws/src/amba_tof/
 *
 * @code {.c}
 * host $ cd ~/catkin_ws/src/amba_tof/
 * host $ vim CMakeLists.txt  (modify INCLUDE_DIR as your dir)
 * host $ cd ~/catkin_ws
 * host $ catkin_make --pkg amba_tof
 * @endcode
 *
 * @subsubsection run_ros_core 4.2.2 Run ROS Core
 * @code {.c}
 * (new terminal)
 * host $ cd ~/catkin_ws
 * host $ source devel/setup.bash
 * host $ roscore
 * @endcode
 *
 * @subsubsection run_ros_app 4.2.3 Run ROS Application
 *
 * @code {.c}
 * (new terminal)
 * host $ source devel/setup.bash
 * host $ rosrun amba_tof amba_ros_tof_socket 1555 --filterz 0.3-2
 * @endcode
 * "--filterz 0.3,2" means that points within a specified range (0.3 to 2) will be retained, select proper size according to user scenario.
 *
 * @subsubsection run_app_evk 4.2.4 Run Application in EVK
 * Take IMX528 sensor as an example, copy the file below to “board/root”, “XXX” means the specific module or frequency:
 *
 * @code {.c}
 * board $ ambarella/packages/depth_sensing_framework/conf/dsf_imx528_amba_XXX.lc
 * board $ ambarella/prebuild/ambarella/library/amba_tof/board/imx528/amba_wiggle_offset.bin
 * board $ ambarella/prebuild/ambarella/library/amba_tof/board/imx528/run_tof_528.sh
 * board $ ambarella/prebuild/ambarella/library/amba_tof/board/imx528/cv2x_vin2_640x480_linear_raw_encode_327.lua
 * @endcode
 *
 * Then run amba_tof in board.
 * @code {.c}
 * board $ sh ./run_tof_528.sh
 * board $ ./test_amba_dsf ./dsf_imx528_amba_XXX.lc
 * @endcode
 * "test_amba_dsf dsf_imx528_amba_XXX.lc" will draw the depth with HDMI and send point cloud to ROS simultaneously.
 * If encountering the error of socket connection, ensure that the IP in "dsf_imx528_amba_XXX.lc" is the same as host.
 * Then open RViz to render point cloud data.
 *
 * @subsubsection show_pt_ros 4.2.5 Show Point Cloud in ROS
 *
 * @code {.c}
 * (new terminal)
 * host $ rviz
 * @endcode
 * The topic needs to be assigned in RViz. First, the "Fixed Frame" in "Displays" must be "amtf", and add "PointCloud2" display type as shown in the figure below.
 *
 * @image html rviz_set0.png "Figure 4-2. Add Display Data."
 *
 * Then set "Topic" in "PointCloud2" is "/tof_output", although the point cloud data can display in RViz now, there are some parameters to do adjustments to find best display performance as shown in the figure below.
 *
 * @image html rviz_set1.png "Figure 4-3. Point Cloud Parameters."
 *
 * The table below lists some important parameters for point cloud to display performance and recommended values, just for your information, select proper size according to user scenario.
 *
 * <table>
 * <caption id="lib_depth_framewrok_rev_history"></caption>
 * <tr><th> Class          <th align="left"> Parameters <th align="left"> Value <th align="left"> Comment
 * <tr><td> Global options  <td> Background color <td> 48;48;48 <td> Dark colors are helpful for point cloud performance
 * <tr><td> Global options  <td> Frame rate   <td> 30 <td> The frame rate of point cloud render in RViz, final frame rate is limited by ToF
 * <tr><td> Grid           <td> Cell size     <td> 1             <td> The cell size of grid
 * <tr><td> Grid           <td> Color         <td> 32;74;135      <td> Color of grid, dark colors are helpful for point cloud
 * <tr><td> Grid           <td> Offset        <td> 0;0;-10       <td> Grid offset 10 in Z axis, prevent blocking point clouds
 * <tr><td> PointCloud2    <td> Topic         <td> /tof_output     <td> Monitor the point cloud data
 * <tr><td> PointCloud2  <td> Style           <td> Points          <td> Recommend
 * <tr><td> PointCloud2  <td> Size (pixels)     <td> 1.5            <td> Select proper size according to user scenario
 * <tr><td> PointCloud2  <td> Alpha               <td> 1            <td> The transparency of the point cloud, select proper size according to user scenario
 * <tr><td> PointCloud2  <td> Color transform    <td> AxisColor     <td> Colour according to the coordinates
 * <tr><td> PointCloud2  <td> Axis               <td> Z            <td> Colour according to the Z coordinates
 * <tr><td> PointCloud2  <td> Autocompute value    <td> False      <td> Manually set colour range in coordinates value
 * <tr><td> PointCloud2  <td> Min Value          <td> 0           <td> Select proper value according to user scenario
 * <tr><td> PointCloud2  <td> Max Value            <td> 3         <td> Select proper value according to user scenario
 * </table>
 *
 * - - - -
 *
 * @section sec_display_on_windows 5. Display Point Cloud on Windows
 * There is a tool to view point cloud on Windows: amba_3dviewer.
 * The tool location is under `ambarella/packages/depth_sensing_framework/tools/amba_3dviewer/windows`.
 * It works similarly to the ROS application and the following are examples of its use.
 *
 * @code {.c}
 * widnows $ amba_3dviewer.exe
 * @endcode
 *
 * @code {.c}
 * widnows $ amba_3dviewer.exe <port>
 * @endcode
 *
 * @code {.c}
 * widnows $ amba_3dviewer.exe <port> --loglevel 4
 * @endcode
 *
 * - - - -
 *
 * @section sec_demo_app 6. Demo Application
 * This chapter provides details on setting up the building environment and running the DSF demo.
 * There are many examples that can guide users in running demos for different EVK and sensor boards.
 *
 * @subsection demo_visiond 6.1 CV22 Vision D EVK + IMX528
 * The Vision D EVK is a reference design platform based on the Ambarella CV22 Computer Vision (CV) SoC.
 * Designed for three-dimensional sensing with a time-of-flight (ToF) sensor, Vision D is capable of generating
 * point cloud / depth images for biometric identification, as well as gray-scale images for face detection and face recognition (FDFR).
 * Additionally, the Vision D EVK serves as a reference development platform on which Ambarella users can build their own
 * products / hardware designs, using the Vision D EVK as a software development / prototype platform.
 * The final products have unique requirements, ranging from (but not limited to) the field of view (FoV) of the lens used, the
 * baseline and ToF module design (thus, the operating range), the video image / anti-spoofing algorithms based on point cloud /
 * depth information, and more. For an overview of the Vision D board and setting up the CV22 Vision D EVK hardware,
 * refer to @ref cv22_vision_d_setting_hw "Setting Up the CV22 Vision D Hardware".
 *
 * @subsubsection cv22_vision_d_build_img 6.1.1 Build Image on the Vision D EVK
 * Refer to the <em>CV2x Linux SDK Release Notes</em> document for information relating to the toolchain and other software.<br>
 * To build an image on the Vision D EVK:
 * - Extract the latest SDK patch
 * - Refer to the `readme.txt` file for the complete build process
 * For further details, such as USB boot options, USB download, or force download,
 * refer to @ref cv25m_aquaman_overview "Overview of the CV25M Aquaman Board".
 *
 * @subsubsection cv22_vision_d_compile_opts 6.1.2 Compile Options
 * There is a default configuration file in the folder `$SDK/ambarella/boards/cv22_vision_d/config`,
 * and the demo options are selected by default.
 * Users can check them in `menuconfig`.
 * @code
 * build $ source ../../build/env/aarch64-linux5.4-gcc.env
 * build $ make sync_build_mkcfg
 * build $ make cv22s88_ipcam_config
 * build $ make menuconfig
 * @endcode
 * Options for DSF:
 * @code
 * [*] Ambarella Package Configuration  --->
 *   [*]   Build Ambarella Depth Sensing Framework  --->
 *     ... ...
 *     [*]   Build example customized components for DSF  --->
 *       [*]   Build DSF component: Ambarella Od Yolov5
 *       [*]   Build DSF component: Draw detection on fb
 *       [*]   Build DSF component: Feed to efm
 *     -*-   Build DSF Ambarella TOF Library support
 *       [*]   Build Ambarella DSF Unit Test
 *       [*]   Copy files for DSF
 * @endcode
 * @note
 * For SDK versions prior to 3.0.11, users must modify "SDK_VER_LESS_THAN_030011" in the makefiles shown below:
 * @code
 * //SDK/ambarella/packages/depth_sensing_framework/unit_test/make.inc
 *   SDK_VER_LESS_THAN_030011 := y
 * //SDK/ambarella/packages/depth_sensing_framework/source/make.inc
 *   SDK_VER_LESS_THAN_030011 := y
 * @endcode
 *
 * @subsubsection cv22_vision_d_run_demo_app 6.1.3 Running Demo Applications
 * Users can check the demo sample files in the Vision D board, and assume the firmware is correct.
 * The file list is as follows:
 * @code
 * board # cd /root/data_files/sensor/demo_set_up/vision_d_pl528/20m
 * board # ls
 * calibration
 * cv2x_vin2_640x480_linear_raw_encode.lua
 * cv2x_vin2_640x480_linear_raw_encode_efm.lua
 * dsf_imx528_amba_20m_dec_for_calib_laser.lc
 * dsf_visiond_imx528_amba_20m_dec_for_calib.lc
 * dsf_visiond_imx528_amba_20m_polig_fpr.lc
 * dsf_visiond_imx528_amba_20m_polig_fpr_ros_yolo_efm.lc
 * dsf_visiond_imx528_amba_20m_polig_fpr_yolo_efm.lc
 * dsf_visiond_no_comp.lc
 * run_tof_528_20m.sh
 * run_tof_528_20m_visiond_efm.sh
 * wiggle_offset.bin
 * @endcode
 *
 * @subsubsection cv22_vision_d_display_point_cloud 6.1.4 Display Point Cloud on Windows (Amba 3D Viewer)
 * 1. Run `amba_3dviewer.exe` on the PC. Users can find this application package in the folder
 *    `$SDK/ambarella/packages/depth_sensing_framework/tools/amba_3dviewer/windows/`.
 * 2. Run the following script file on the Vision D board.
 * @code
 * board # cd /root/data_files/sensor/demo_set_up/vision_d_pl528/20m
 * board # ./run_tof_528_20m.sh
 * @endcode
 * 3. Modify the DSF configuration file.
 *    For this demo, modify the file `dsf_visiond_imx528_amba_20m_polig_fpr.lc`
 *    and change the option setting for "remote_url" to match the internet protocol (IP) used by the PC
 *    that is running the `amba_3dviewer.exe` software.
 *    Users can refer to the Doxygen documents for more details regarding the parameters in the LC files.
 * 4. Run the unit test application `test_amba_dsf`.
 * @code
 * board # test_amba_dsf dsf_visiond_imx528_amba_20m_polig_fpr.lc
 * @endcode
 * 5. View the image in Amba 3D Viewer (refer to @ref fig_cv22_vision_d_amba_3d_viewer "Figure 6-1").
 * @anchor fig_cv22_vision_d_amba_3d_viewer
 * @image html cv22_vision_d_amba_3d_viewer.jpg "Figure 6-1. Image of the Amba 3D Viewer."
 * <br>
 *
 * @subsubsection cv22_vision_d_display_depth_yolov5_vlc 6.1.5 Display Depth with Yolov5 on VLC (Streaming)
 * This sample teaches users how to demo depth via livestreaming. Users must prepare CV models and font files by themselves.
 * 1. Run the following script file on the Vision D board.
 * @code
 * board # cd /root/data_files/sensor/demo_set_up/vision_d_pl528/20m
 * board # ./run_tof_528_20m_visiond_efm.sh
 * @endcode
 * 2. Run the real-time streaming protocol (RTSP) server.
 * @code
 * board # rtsp_server &
 * @endcode
 * 3. Modify the DSF configuration file.<br>
 * For this demo, `dsf_visiond_imx528_amba_20m_polig_fpr_yolo_efm.lc` must be modified
 * to specify the yolov5 model path (i = ..., o = ..., model = ...) and font file path (font_file = ...), as shown below.
 * Users can refer to the Doxygen documents for more details regarding the parameters in lc files.
 * @code
 * Stage
 *   name = vca
 *   component = od_yolov5
 *   domain = jet
 *   buffer_num = 3
 *   upstream_stage = normalization_jet
 *   bypass = 0
 *   i = /root/yolov5/nn/in/coco_class_names.txt
 *   o = /root/yolov5/nn/out/result.txt
 *   model = /root/yolov5/nn/model/onnx_yolov5s_cavalry.bin
 *   type = s
 *   f = 0.5
 *   nms = 0.3
 *   top_k = 100
 *   u = 0
 *   tiny_enable = 0
 * Stage
 *   name = combine_bbox
 *   component = combine_depth_nv12_bbox
 *   domain = jet
 *   buffer_num = 3
 *   upstream_stage = normalization_jet
 *   upstream_stage = vca
 *   bypass = 0
 *   font_file = /root/arial.ttf
 *   enable_diagnosis = 0
 * @endcode
 * 4. Run unit test application: `test_amba_dsf`.
 * @code
 * board # test_amba_dsf dsf_visiond_imx528_amba_20m_polig_fpr_yolo_efm.lc
 * @endcode
 * 5. View the image in VLC (refer to @ref fig_cv22_vision_d_img_vlc "Figure 6-2").
 * @anchor fig_cv22_vision_d_img_vlc
 * @image html cv22_vision_d_img_vlc.jpg "Figure 6-2. Image in VLC."
 * <br>
 *
 * @subsection demo_cv25_adi3500 6.2 CV25_hazelnut + ADI3500 Sensor
 *
 * @subsubsection demo_adi3500_build 6.2.1 Build Image on CV25_hazelnut
 * Refer to the <em>CV2x Linux SDK Release Notes</em> document for information relating to the toolchain and other software.<br>
 * There is a default configuration file in the `$cv25_ipcam_depth_framework_tof_config`, and for detailed infomation, users can refer to @ref depth_framework_required_menuconfig.
 *
 * @code
 * build $ source ../../build/env/aarch64-linux5.4-gcc.env
 * build $ make sync_build_mkcfg
 * build $ make cv25_ipcam_depth_framework_tof_config
 * build $ make defconfig_public_linux
 * build $ make menuconfig
 * @endcode
 *
 * @code {.c}
 * below option need select by hand in menuconfig.
 * -> Ambarella Linux Configuration (BUILD_AMBARELLA_LINUX_KERNEL [=y]) p(MIPI)
 *     -> Ambarella Private Drivers Configuration (BUILD_AMBARELLA_PRIVATE_MODULES [=y])
 *         -> Build Ambarella private Vin modules (BUILD_AMBARELLA_VIN [=y])
 *             -> Ambarella TOF Sensor Configuration
 *                 [*] ADI ADSD3500+ADSD3100 1M TOF sensor/isp.
 *  -> Ambarella Package Configuration (BUILD_AMBARELLA_PACKAGE [=y]
 *     -> Build Ambarella Depth Sensing Framework
 *         [*] Select Copy files for DSF.
 *         -> Build vendors components for DSF (BUILD_VENDORS_COMPONENTS [=y])
 *             [*] Build DSF component: ADI depth compute engine.
 * @endcode
 *
 * Then, burn the image to cv25_hazelunt via amba_usb.
 *
 * @subsubsection demo_adi3500_prepare 6.2.2 Prepare Related Files
 * If the folder`$data_files` is not in `$board /root/`, users should copy `$ambarella/packages/depth_sensing_framework/data_files/sensor/demo_set_up/adsd3500` to `$board /root/`.
 *
 * @subsubsection demo_adi3500_run 6.2.3 Running Demo Applications
 *
 * @code
 * QMP case (InputFormat: raw8, Data Info: Depth16b+Conf8b+AB16b)
 * board $ cd /root/data_files/sensor/demo_set_up/adsd3500/qmp_raw8_Depth16b+Conf8b+AB16b
 * board $ sh ./run_adsd3500_qmp_raw8.sh
 * board $ test_amba_dsf ./dsf_adsd3500_qmp8b_draw_ros.lc
 *
 * MP case (InputFormat: raw16_bits12_shift4, Data Info: Phase12b+AB12b)
 * board $ cd /root/data_files/sensor/demo_set_up/adsd3500/mp_12t16bit_Phase12b+AB12b
 * board $ sh ./run_adsd3500_mp.sh
 * board $ test_amba_dsf ./dsf_adsd3500_mp12t16b_draw_ros.lc
 * @endcode
 * Users will see the depth image via HDMI preview; refer to @ref fig_adsd3500_hdmi_depth "Figure 6-3".
 * @anchor fig_adsd3500_hdmi_depth
 * @image html fig_adsd3500_hdmi_depth.jpg "Figure 6-3. Depth in HDMI Preview."
 * <br>
 * The point cloud data is display via amba_3dviewer; refer to @ref fig_adsd3500_3dpc "Figure 6-4".
 * Check the @ref sec_depth_disp_pc_on_ros "Display Point Cloud on ROS" for details on the robot operating system (ROS),
 * or @ref sec_display_on_windows "Display Point Cloud On Windows" for amba_3dviewer.
 * @anchor fig_adsd3500_3dpc
 * @image html fig_adsd3500_3dpc.jpg "Figure 6-4. Point Cloud Data in amba_3dviewer."
 * <br>
 *
 * @subsubsection demo_adi3500_performance 6.2.4 Performance on Boards
 *
 * The performance on CV25_hazelnut.
 * <table>
 * <caption id="table_demo_adi3500_performance_cv25hazelnut"></caption>
 * <tr><th> Sensor Resolution <th align="left"> Data Information <th align="left"> Input Format <th align="left"> Data Size (byte) <th align="left"> CPU (CV25) <th align="left"> Time (stage) <th align="left"> FPS
 * <tr><td> QMP (mode 7) <td> Depth16bit+Conf8bit+AB16bit  <td> Raw8 (VIN treats the RAW8 as RAW16) <td> 1,310,720 <td> 9.5 % <td> 8.46 ms <td> 118.16
 * <tr><td> Mp (mode 5) <td> Phase12bit+AB16bit <td> mipiRaw12_8 <td> 6,815,744 <td> 46.7 % <td> 39.39 ms <td> 25.38
 * </table>
 *
 * The performance on CV2_chestnut.
 * <table>
 * <caption id="table_demo_adi3500_performance_cv2chestnut"></caption>
 * <tr><th> Sensor Resolution <th align="left"> Data Information <th align="left"> Input Format <th align="left"> Data Size (byte) <th align="left"> CPU (CV2) <th align="left"> Time (stage) <th align="left"> FPS
 * <tr><td> QMP (mode 7) <td> Depth16bit+Conf8bit+AB16bit  <td> Raw8 (VIN treats the RAW8 as RAW16) <td> 1,310,720 <td> 45.8 % <td> 7.48 ms <td> 133.65
 * <tr><td> Mp (mode 5) <td> Phase12bit+AB16bit <td> mipiRaw12_8 <td> 6,815,744 <td> 43.9 % <td> 36.44 ms <td> 27.44
 * </table>
 *
 * The performance on CV5_timn.
 * <table>
 * <caption id="table_demo_adi3500_performance_cv5timn"></caption>
 * <tr><th> Sensor Resolution <th align="left"> Data Information <th align="left"> Input Format <th align="left"> Data Size (byte) <th align="left"> CPU (CV5) <th align="left"> Time (stage) <th align="left"> FPS
 * <tr><td> QMP (mode 7) <td> Depth16bit+Conf8bit+AB16bit  <td> Raw8 (VIN treats the RAW8 as RAW16) <td> 1,310,720 <td> 4.0 % <td> 5.10 ms <td> 196.06
 * <tr><td> Mp (mode 5) <td> Phase12bit+AB16bit <td> mipiRaw12_8 <td> 6,815,744 <td> 20.1 % <td> 23.23 ms <td> 43.04
 * </table>
 *
 * @subsubsection demo_adi3500_TOFEngine 6.2.5 Time of Flight (ToF) Depth Compute Engine NXP
 * "ToF depth compute engine" is a depth compute library which processes the raw frames captured by ADI ToF sensor module and generate confidence/depth/active-brightness and XYZ frames.
 * More details about the ADI ToF depth compute engine, contact ADI support team or consult Ambarella support team.
 *
 * - - - -
 *
 * @section sec_depth_performance 7. Performance
 * In order to compare the performance intuitively, Ambarella sets a typically DSF pipline as shown in @ref fig_typically_pipline "Figure 7-1".
 * @anchor fig_typically_pipline
 * @image html fig_typically_pipline.jpg "Figure 7-1. Typically DSF Pipline."
 *
 * The performance of some ToF sensors on our chip.<br>
 * *cpu usage<br>
 * **Downsample to enhance the frame rate of "ros" stage
 *
 * <table>
 * <caption id="table_ToFSensors_performance"></caption>
 * <tr><th colspan="3"> Sensors  <th colspan="3"> Boards
 * <tr><th> Name <th> Resolution <th> Sensor FPS <th>  CV25_hazelnut <th> CV5_timn <th> CV72_gage
 * <tr><td> IMX528 <td> 640x480 <td> 30 fps <td> 14.86 fps, 45.3%* <td> 17.64 fps, 24.2%  <td> 18.93 fps, 22.2%
 * <tr><td colspan="3" align="right"> **Downsample to 320x240 <td> 19.87 fps, 65.8% <td> 20.11 fps, 31.0% <td> 20.32 fps, 35.6%
 * <tr><td> IRS2877C <td> 640x480 <td> 15 fps <td> 15.29 fps, 41.2%  <td> 14.34 fps, 17.2% <td> 14.85 fps, 15.0%
 * </table>
 *
 * The visualization of video output (VOUT) and point cloud are as shown in @ref fig_vout_pointcloud "Figure 7-2".<br>
 * *The quality of point cloud is related to the filters in DSF pipline. The point cloud in figure 7-2 adds some spatial filters and uses different filters to get a balance between frame rate and point cloud quality.
 * @anchor fig_vout_pointcloud
 * @image html fig_vout_pointcloud.jpg "Figure 7-2. HDMI VOUT and Point Cloud Data."
 * - - - -
 *
 * @section sec_depth_api 8. ToF API
 * Visit the following link to refer to details of the application programming interface (API) functions.
 *
 * - - - -
 *
 * @section sec_depth_lic 9. License
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
 */

/*!
* @defgroup dsf-api Depth Sensing Framework API
* @brief Depth Sensing Framework API, in file amba_dsf_if.h
*/
/*! @defgroup dsf-api-flow Depth Sensing Framework work flow API
* @ingroup dsf-api
* @brief Depth Sensing Framework work flow API, in file amba_dsf_if.h
*/
/*! @defgroup dsf-api-utility Depth Sensing Framework utility API
* @ingroup dsf-api
* @brief Depth Sensing Framework utility API, in file amba_dsf_if.h
*/
/*!
 * @file doc_lib_dewarp.h
 * @author Xin Gao (xgao@ambarella.com)
 * @brief This is a .h file for Doxygen document system
 * @version 0.1
 * @date 2022-10
 *
 * @copyright Copyright (c) 2023
 *
 */

/*!
 * @page page_lib_dewarp_doc Dewarp Library API
 *
 * <b>The contents of this document are proprietary and confidential information of Ambarella International LP.</b>
 *
 * @section dewarp_support Important Declaration about Dewarp Support
 *
 * The dewarp module is an important part of the Ambarella Linux software development kit (SDK); it
 * has the ablility to warp images from video input (VIN) / the pre-main buffer to the YUV buffer in the
 * image digital signal processor (IDSP). It is different from the dewarp module in simulations or
 * any other open source library.
 * <br>From the software perspective of the dewarp library, all warp-related parameters are used
 * to compute the warp table, grid information, input window, and more. The image audio video (IAV) driver
 * and application perform validity checks in terms of alignment, boundary, and required hardware resource.
 * Afterwards, all related parameters are wrapped into one digital signal processor (DSP) command and applied to the IDSP.
 * The IDSP pipeline supports lens dewarp correction (LDC) or multi-region warp, which are closely connected to the
 * warp hardware resource. Users must understand that not all warp cases are supported during evaluation.
 * Based on the description above, Ambarella suggests following the steps below for specific warp cases.
 * For any questions, contact the Ambarella Shanghai team.
 * <br>1. Become familiar with the targeted warp correction parameters.  All valid ranges are theoretical
 * ranges; they generate different warp effects with unique resolutions, lenses, and complimentary
 * metal-oxide semiconductor (CMOS) sensors.
 * <br>2. Determine the CMOS sensor, lens type, and system specifications to estimate the required
 * hardware resources.
 * <br>3. Fine-tune the warp effect.  Ambarella can provide technical support in this stage.
 * <br>4. Establish the test set by users.  Ensure the set covers the worst cases that may occur in real
 * applications and that the test results in the same conclusions between the Ambarella evaluation
 * kit (EVK) boards and users' boards.
 * <br>5. Add the test set into the Ambarella quality assurance (QA) team's regression test to ensure
 * that any updates to the dewarp module or ucode do not impede functions required by the user.
 * <br>6. After the Ambarella-standard QA test, users should be notified of required modifications
 * about the targeted warp correction.  Users can either ask for formal hotfix or refuse to update their
 * version, giving feedback to Ambarella.  Ambarella should confirm the possibility of porting updates
 * to the specific version and notify the users.
 * <br><b>Ambarella is responsible for broken images caused by the dewarp module for the following
 * conditions:</b>
 * <br>- Artifacts occur from the cases in the test set
 * <br>- Unexpected blocks for warp-related parameters from the cases in the test set
 * <br>- Dewarp module hotfix is delivered to users without going through the test set
 * <br><b>Ambarella is NOT responsible for broken images caused by the dewarp module for the
 * following conditions:</b>
 * <br>- The CMOS sensor, lens type, and / or system specifications are changed
 * <br>- The actual use cases are out of the user-created test set
 * <br>- The unit test codes "test_ldc.c", "test_ldc.h", and "test_dewarp.c" are reference codes.  Users write
 * their own application that call the dewarp library should go through step 4 above to ensure that the test
 * sets result in the same conclusions between the Ambarella EVK boards and users' boards.
 *
 *
 *
 * @section dewarp_history 0. Revision History
 * <table>
 * <caption id="lib_dewarp_rev_history"></caption>
 * <tr><th> Library Version <th> Updated Date  <th align="left"> Modification
 * <tr><td> 2.0.0 <td> 20220919 <td> Initial Version
 * <tr><td> 2.1.0 <td> 20220927 <td> Enable point mapping (1D+1D) with rotation pipeline @ref LDC_and_dewarp, @ref point_mapping
 * <tr><td> 2.1.1 <td> 20221017 <td> Refined the warp grid computation for encode mode 1 @ref warp_vector_view
 * <tr><td> 2.1.2 <td> 20230222 <td> Align vwarp output width 64 for MCTF restriction @ref warp_align
 * <tr><td> 2.1.3 <td> 20230225 <td> Align hwarp output width with 64 according to c2y restriction under encode mode 0 @ref warp_align
 * <tr><td> 2.1.4 <td> 20230616 <td> Added ME1 v/h table for motion stream under encode mode 5 @ref ldc_me1
 * <tr><td> 2.1.5 <td> 20230621 <td> Added LDC support for encode mode 9 AISP @ref LDC_and_dewarp
 * <tr><td> 2.1.5 <td> 20230717 <td> Added the 2D vector validity rules @ref transform_twin_vector_to_idsp_format
 * <tr><td rowspan="2"> 2.1.6 <td rowspan="2"> 20220720 <td> 1. Added the check for ME1 warp table @ref ldc_me1
 * <tr>                                                 <td> 2. Refine the grid-level 2D vector conversion @ref transform_twin_vector_to_idsp_format
 * <tr><td> 3.0.0 <td> 20231011 <td> Support up to 16x channels warp @ref v6_ldc_intro
 * <tr><td rowspan="3"> 3.1.0 <td rowspan="3"> 20231017 <td> 1. LDC: Added conversion with pure float coordinate @ref transform_twin_vector_to_idsp_format
 * <tr>                                                 <td> 2. LDC: Added correction mode warp by perspective matrix(3x3) @ref perspective_matrix
 * <tr>                                                 <td> 3. Added warp input mode @ref warp_input_mode
 * <tr><td> 3.1.1 <td> 20231031 <td> Supported grid level coordinate file for conversion @ref transform_twin_vector_to_idsp_format
 * <tr><td> 3.1.2 <td> 20231114 <td> Supported vertical upscale in vertical warp for encode mode 1 (Hwarp first) pipeline @ref LDC_and_dewarp
 * <tr><td> 3.1.2 <td> 20231201 <td> Refined the description for vwarp waitlines @ref warp_hw_res @ref dewarp_qa_q9
 * <tr><td> 3.1.3 <td> 20231206 <td> Refined the input window configuration for AISP mode. @ref LDC_and_dewarp
 * <tr><td> 3.1.3 <td> 20240104 <td> Separated @ref lens_lut_example from the section @ref lens_lut
 * <tr><td> 3.1.3 <td> 20240111 <td> Changed correction table @ref dewarp_correction_mode "warp correction table"
 * <tr><td> 3.1.4 <td> 20240115 <td> Vector computation refine for Hwarp first, vertical upscale under encode mode 1. @ref LDC_and_dewarp
 * </table>
 *
 * - - - -
 *
 * @section dewarp_overview 1. Overview
 * This document provides guidelines for implementing multi-region warp and flexible perspective
 * correction (including lens distortion correction (LDC)) using the CV5x / CV7x Flexible Linux
 * Software Development Kit (SDK).  Currently, the multi-region warp feature is enabled
 * only in multi-region warp mode, and functions only for a single channel.
 *
 * This chapter contains the following sections:
 *     - Section @ref v6_fisheye_intro
 *     - Section @ref v6_ldc_intro
 *     - Section @ref LDC_and_dewarp
 *     - Section @ref warp_vector_view
 *
 * @subsection v6_fisheye_intro 1.1 CV5x / CV7x Multi-Region Warp Mode Introduction
 * "IDSP Multi-Region Warp" (encode mode 1) is one of the important image digital signal progessor (IDSP) modes
 * on CV5x / CV7x platforms, such as CV2x and S2 / S2E.  Customers can have their internet protocol camera (IPC)
 * products render multiple warp view layouts in the main buffer with one single channel.  Each warp view runs
 * through the IDSP warp hardware with a geometry warp table to obtain a variety of monitor-friendly
 * views. Typically, the cameras are mounted with a fisheye lens (large field of view (FoV)).
 * <br>Different from other platforms, such as CV2x and S2 / S2E, encode mode 1 requires configurations for dual
 * real channels for one video input (VIN) source. One channel is connected to a real VIN source under encode
 * mode 0/5 without warp operations, which is named "unwarped channel". The other channel is from one
 * dummy VIN (ambds) under encode mode 1, which is named "warped channel". The unwarped channel has
 * unwarped images for all the buffers; the YUV from the main buffer of this channel functions as a video source (VSRC) for the
 * warped channel (EFR with YUV raw). As a result, the canvas with the main buffer from the unwarped channel CANNOT be
 * encoded, and it appears as the pre-main buffer for the warped channel. This will be referred to as the fake pre-main buffer.
 * Users must be familiar with the concepts "warped channel", "unwarped channel", "fake pre-main buffer",
 * as this documents adapts them for more detailed introductions below.
 *
 *
 * @subsection v6_ldc_intro 1.2 CV5x / CV7x Lens Distortion Correction Introduction
 * LDC is supported on below encode modes:
 *  | Mode ID | Mode Name |
 *  | :------------: | :---------: |
 *  |0 | Normal ISO mode |
 *  |5 | High dynamic range (HDR) line-interleaved mode |
 *  |9 | AISP mode |
 * LDC brings one warp effect to the main buffer through the IDSP warp hardware,  so there are no multiples
 * but only one warp view exists with the same size as main buffer output.  Currently, dewarp library could
 * support up to <b>16x channels</b> warp table computation, the application can specify a channel
 * bitmap "warp_channel_map" according to active system configuration.
 * <br>For more details about the differences between LDC and multi-region warp, refer to @ref LDC_and_dewarp.
 *
 *
 * @subsection LDC_and_dewarp 1.3 LDC and Multi-Region Warp
 * The major differences between LDC and multi-region warp are as follows:
 * -# <b>Correction mode:</b> LDC only supports multi-region warp wall mount correction modes.
 * To enable multi-region warp enable ceiling / desktop mount,
 * refer to @ref ceiling_desktop_panorama_fulframe. @ref ceiling_desktop_rectilinear. @ref ceiling_desktop_sub
 * -# <b>Encode mode:</b> LDC functions in mode 0 (normal ISO mode) and mode 5 (HDR line-interleaved mode).
 * Multi-region warp functions in mode 1 (Multi\_Region\_Warp Mode).
 * -# <b>Pipeline:</b>
 * @image html v6_multi_region_warp_pipeline.png "Figure 1-1. Multi-Region Warp Pipeline."
 * <br>
 * <br>
 * @image html v6_LDC_pipeline.png "Figure 1-2. LDC Pipeline."
 * -# <b>System resource:</b> Refer to option (max_padding_width/lens_warp) and max warp
 * input / output width in @ref warp_system_config.
 * -# <b>Granularity:</b> For one view, multi-region warp can support multiple areas, while LDC only
 * has one area (group of vector). When applying wall rectilinear for main buffer 1080p, multi-region warp
 * can split one view into four areas to apply the vector.  Multi-region warp can support up to twelve areas for
 * one channel.
 * -# <b>Warp DPTZ (digital pan / tilt / zoom):</b> As there is only one area for the main buffer, warp DPTZ
 * is not available for LDC. However, users can enable DPTZ II after LDC. @ref warp_dptz
 * -# <b>Different application programming interface (API) functions and different applications:</b> @ref dewarp-api-api
 * (test_ldc.c, test_dewarp.c).
 *
 *
 * @subsection warp_vector_view 1.4 Warping Vector (Area) / Corrected View
 * The warp area is one physical rectangular area located in the main buffer of the warped channel that renders
 * the desired warp effect, which is realized by the warp engine hardware in the IDSP. This hardware enables
 * horizontal and vertical (H/V) warp for each warp area. The H/V warp stage requires a warp table at the grid level
 * to demand a pixel shift for the specific point; the warp table size and grid spacing are not
 * permitted to be set with an arbitrary value, but calculated by the library automatically according to the
 * restriction of the warp engine hardware. Below is a list of dewarp engine hardware restrictions.
 * <br><b>Warp area minimum width: 112</b>
 * <br><b>Warp area maximum width: 2048</b>
 * <br><b>Maximum warp area number: 12</b>
 * <br><b>Maximum warp table size: 128x96 (HxV) </b>
 * <br><b>Grid spacing: 8, 16, 32, 64, 128, 256, 512 </b>
 * <br><b>Warp view</b> is described in the user application scope while "warping vector (area)"
 * is described in the CV5x / CV7x image audio video (IAV) scope. It is possible for each warp view to include
 * two or four axisymmetric warp areas combined into one final warp effect; the active warp area number for
 * one warp view depends on the active @ref dewarp_correction_mode "Correction Mode". Check the sample
 * application @ref test_dewarp.c for more details.
 *
 *
 * - - - -
 *
 * @section dewarp_correction_mode 2. Correction Mode
 * This section defines correction modes for wall mount, ceiling mount, and desktop mount. In addition,
 * a schematic and explanations of parameters for each correction mode are also provided below.
 *
 * <table>
 * <caption id="correction_mode_table">Table 2-1. Overview of all correction modes</caption>
 *
 * <tr><th> Correction Mode
 *     <th style="width:128px"> LDC / Fisheye
 *     <th> Pros and Cons
 *     <th> Application
 * <tr><td align="middle"> @ref no_transform "No Transform"
       <td> LDC and Fisheye
       <td> Same as DPTZ I but costs more bandwidth loss <td> Original fisheye view in multiple regions warp
 * <tr><td align="middle"> @ref no_transform_rotate "No Transform Rotate"
 *     <td> LDC and Fisheye
 *     <td> Cannot rotate with arbitrary angles
 *     <td> N/A
 * <tr><td align="middle" rowspan="4"> @ref wall_rectilinear "Wall Rectilinear"
       <td rowspan="4"> LDC and Fisheye
       <td> 1. Flexibly control radical distortion removal <br>2. All the lines are stretched to straight                     <td> Undistortion without calibrated parameters
 * <tr><td> @ref wall_adv_polar_warp "Polar Warp"<br>3. Perspective changing by polar coordinates                             <td> Rectilinear with different perspective transform
 * <tr><td> @ref wall_eyeball_rotation "Eyeball Rotation"<br>4. Flexibly select any ROI of input image with distortion removal <td> Pan / tilt / rotate or region of interest (ROI)
 * <tr><td> @ref wall_adv_py "Advance Pitch/Yaw"<br>5. Virtually adjust perspective warp with pitch / yaw of image boundary      <td> ROI on corridor view
 *
 * <tr><td align="middle" rowspan="5"> @ref wall_panorama "Wall Panorama"
 *     <td rowspan="5"> LDC and Fisheye
 *     <td> @ref wall_cylinder_panorama "Cylinder"<br>1. Vertical lines are straight <br>2. Horizontal FoV can be specified <br>3. Aspect ratio 8:3 <td> General panoramic view
 * <tr><td> @ref wall_mercator "Mercator"<br>4. Aspect ratio 1:1 <td> Map projection
 * <tr><td> @ref wall_equirectangular "Equirectangular"<br>5.a Projection according to longitude and latitude lines<br>5.b Largest vertical FoV <br>5.c The north and south pole are avaiable <br>5.d Aspect ratio 1:1 <td> Doorbell
 * <tr><td> @ref wall_squircular "Squircular"<br>6. A shape intermediate between a square and a circle   <td> Doorbell
 * <tr><td> @ref wall_pano_fan "Fan Warp"<br>7. Adjust gravity direction in panoramic view               <td> General panoramic view
 *
 * <tr><td align="middle" rowspan="2"> @ref wall_vertical_panorama "Wall Vertical Panorama"
 *     <td rowspan="2"> LDC and Fisheye
 *     <td> @ref wall_transverse_cylinder "Transverse Cylinder"<br>1. Horizontal lines are straight <br>2. Vertical FoV can be specified <br>3. Aspect ratio 3:8 <td> General vertical panoramic view
 * <tr><td> @ref wall_transverse_mercator "Transverse Mercator"<br>4. Aspect ratio 1:1  <td> Transverse mecator
 *
 * <tr><td align="middle"> @ref wall_pincushion "Wall Pincushion"
 *     <td> LDC and Fisheye
 *     <td> Remove pincushion distortion
 *     <td> Lens warp in large optical zoom
 * <tr><td align="middle"> @ref wall_pannini "Wall Pannini"
 *     <td> LDC and Fisheye
 *     <td> Large FoV with limited distortion in horizontal direction
 *     <td> Doorbell
 *
 * <tr><td align="middle"> @ref ceiling_desktop_panorama_fulframe "Ceiling/Desktop Panorama and Fulframe"
 *     <td align="middle"> Fisheye <td> Full view of fisheye <td> 1. Surround 360 view <br>2. Double panorama
 * <tr><td align="middle"> @ref ceiling_desktop_rectilinear "Ceiling/Desktop Rectilinear"
 *     <td align="middle"> Fisheye
 *     <td> 1. Do rectilinear for North / South / East / West part<br>2. Gravity direction point to fisheye circle
 *     <td> Ceiling mount quad view surveillance
 * <tr><td align="middle"> @ref ceiling_desktop_sub "Ceiling/Desktop Sub Region"
 *     <td align="middle"> Fisheye
 *     <td> 1. Flexibly select any ROI of input image with distortion removal <br>2. Gravity direction is pointing to the fisheye circle
 *     <td> 1. Ceiling mount surveillance camera <br>2. Video conference camera
 *
 * <tr><td align="middle"> @ref transform_twin_vector_to_idsp_format "2D Vector Conversion"
 *     <td align="middle" > LDC
 *     <td>1. Multiple formats of 2D vector generation:<br>a. Pixel level 2D vector <br>b. Grid level 2D vector <br>c. Pure coodinate file <br>2. Conversion deviation is within 1 pixel unit
 *     <td> Customized warp effect
 * <tr><td align="middle"> @ref load_zzy_calib_param "Load Calibration Parameters for Undistortion"
 *     <td align="middle" > LDC
       <td> Prepare below parameters in advance for undistortion:<br>a. Radical / tangential distortion parameters <br>2. Intrinsic matrix
 *     <td> 1. Do camera undistortion precisely <br>2. Stereo camera warp for disparity map
 * <tr><td align="middle"> @ref perspective_matrix "Warp by Perspective Matrix"
 *     <td align="middle"> LDC
 *     <td> Flexibly specify perspective transformation
 *     <td> Perspective transformation
 * </table>
 *
 *
 * @subsection no_transform 2.1 No Transform
 * <b>No transform:</b> No transform image from the wide angle sensor. Usually, it is an
 * image that curves in both horizontal and vertical directions.
 * @image html no_transform_model.png "Figure 2-1. No Transform Model."
 * <b>View source:</b> The user specifies the source of the view from either the fake pre-main buffer
 * or sub-buffers of unwarped channels.
 * <br><b>Up / down scaling:</b> The scaling factor from the source in the fake pre-main buffer to the
 * output view in the main buffer is decided by the source size and the output size.
 *
 *
 * @subsection no_transform_rotate 2.2 No Transform Rotate
 * This is an advanced mode fpr no transform @ref no_transform, which enables rotation in the range
 * [-180, 180] (for LDC, the range is limited to [-45, 45]) and zoom in the range [0.25f, 4.0f].
 * @image html no_trans_rotate_model.png "Figure 2-2. No Transform Rotate Model."
 * <br><b>View size:</b> The width of the warp view should be less than or equal to the maximum area width
 * of the corresponding CV5x / CV7x platform.
 * <br><b>Warp area number:</b> Warp view can only have one warp area. Multiple areas for this correction
 * are not supported.
 * @image html no_trans_rotate.png "Figure 2-3. No Transform Rotate."
 *
 *
 * @subsection wall_rectilinear 2.3 Wall Rectilinear
 * <b>Rectilinear:</b> The dewarped image with correction in both horizontal and vertical directions.
 * In this view, the image is restored in the vertical and horizontal directions.
 * @image html rectilinear_model.png "Figure 2-4. Rectilinear Model."
 * <b>View size:</b> Assume that the radius of the fisheye circle in the fake pre-main buffer is R. The
 * following size is not mandatory, but recommended.
 * <br>Rectilinear view width / height <= 2R
 * <br><b>View center:</b> The center remains the same as the fisheye circle.  When the zoom factor
 * is 1.0x, the objects in the center of the corrected view maintain the same size as the fisheye
 * view. To see the view center in the fisheye and wall mount modes, see the images within
 * the red circles in Figure 2-5 Wall Rectilinear FoV.
 * <br><b>Gravity line:</b> The image is restored along the direction of the gravity line (yellow line in
 * Figure 2-6 Wall Rectilinear).
 * <br><b>Horizontal line:</b> The image is restored along the direction of the horizontal line
 * (Figure 2-6 Wall Rectilinear).
 * @image html wall_rectilinear_fov.png "Figure 2-5. Wall Rectilinear FoV."
 * <br><b>FoV:</b>  The FoV for the rectilinear view depends on the view size.
 * Horizontal FoV = 2 * arctan (view width / 2 / focal length)
 * Vertical FoV = 2 * arctan (view height / 2 / focal length)
 * <br>For example, the fisheye circle size is 2048 pixels at 185 degrees.  The lens's projection
 * method is f-theta.  The focal length is 2048 / (185 / 180 * Pi) = 634.3.  The horizontal / vertical
 * FoV in Figure 2-6 Wall Rectilinear view is 116 degrees.
 * In Figure 2-5 Wall Rectilinear FoV, 95 degrees is for 1536x1536 and 76 degrees is for 1024x1024.
 * @image html wall_rectilinear_zoom.jpg "Figure 2-6. Wall Rectilinear."
 * <br><b>Zooming in/out:</b>  The objects far from the center appear "stretched".  See the image within
 * the blue circles in Figure 2-5 Wall Rectilinear.  Zooming out the rectilinear view enables a wider FoV but
 * includes more "stretched" objects.
 * @image html wall_rectilinear_zoom_factor.png "Figure 2-7. Wall Rectilinear Zoom."
 * <br><b>Advanced warp: </b> Advanced warp corrections include wall rectilinear, pan / tilt / rotate,
 * region of interest (ROI)+rotate, advanced polar warp, and advanced pitch / yaw.
 *
 * @subsubsection wall_adv_polar_warp 2.3.1 Advance Polar Warp
 * Currently, only wall rectilinear correction supports advanced polar warp. Polar coordinates
 * (\f$r*\theta\f$) are used to indicate the parameters of polar warp: \f$r\f$ indicates polar strength
 * while \f$\theta\f$ indicates direction.  While polar warp offers a different perspective of
 * an object, its FoV almost always remains the same.
 * @image html polar_warp.png "Figure 2-7. Polar Warp."
 *
 * @subsubsection wall_eyeball_rotation 2.3.2 Tilt / Pan / Rotate or ROI / Rotate
 * The lens tilt / pan / rotate correction functions with different camera positions. Currently, only
 * wall rectilinear mode supports tilt / pan / rotate. Because the full range of horizontal
 * FoV, wall panorama / wall cylindrical panorama / wall mercator / wall equirectangular supports
 * pitch, not tilt.
 *	<br><b>Tilt:</b> Rotate about center vertically. Tilt degree range is [-90, +90].
 *	<br><b>Pan:</b> Rotate about center horizontally. Pan degree range is [-90, +90].
 *	<br><b>Rotate:</b> Rotate about center symmetry. Rotate degree range is limited to [-180, +180].
 * @image html lens_ptr.png "Figure 2-8. Wall Mount Lens Tilt / Pan / Rotate."
 *
 * @subsubsection wall_adv_py 2.3.3 Advanced Pitch / Yaw
 * Currently, only wall rectilinear supports advanced pitch / yaw. While pitch / yaw enables all
 * pixels or grids to rotate around the axis with the same angle, advanced pitch / yaw specifies a
 * different angle for each row or column of an image. The current version of advanced warp
 * requires pitch / yaw values at both borders of the image (top / bottom, left / right); the value of
 * internal rows or columns between them is calculated using linear interpolation.
 * @image html avdv_py.png "Figure 2-9. Wall Rectilinear: Advanced Pitch / Yaw."
 *
 *
 * @subsection wall_panorama 2.4 Wall Panorama
 * <b>Panorama:</b> The dewarped image is corrected only in the vertical direction. In this view, the image
 * is restored in the vertical direction.
 * @image html panorama_model.png "Figure 2-10. Panorama Model."
 * Currently, the dewarp library supports four types of cylindrical panoramic projection, each with
 * different features. The following images illustrate the differences between panoramic views.
 * @image html panorama_cmparison.png "Figure 2-11. Comparison of Panoramic Views."
 *
 * @subsubsection wall_cylinder_panorama 2.4.1 General Cylindrical and Panorama
 * In panoramic imaging, the cylindrical projection is most frequently used for prints of wide
 * panoramas, which occupy large ranges (>120 degrees) of longitude. While cylindrical projection
 * preserves verticals, it cannot represent data near the poles (nadir and zenith), which are
 * distorted and stretched indefinitely.
 *  | H-FoV | V-FoV |	Horizontal Curvature |Width / Height Ratio |
 *  | :-----: | :-----: | :---------: | :---: |
 *  | Interactive parameters | Proportional to H-FoV | The closer to the top or bottom of the image, the more curved it is |8:3 |
 * <br><b>View size:</b>  Assume the radius of the fisheye circle in the fake pre-main buffer is R. Although
 * the following size is not mandatory, Ambarella recommends the following:
 * <br>Panorama view width <= 2R
 * <br>Panorama view width / Panorama view height = 8 / 3
 * <br><b>View center:</b> The center remains the same as the fisheye circle. The objects in the
 * center of the corrected view maintain the same size as in the fisheye view. Observe
 * the red circles in Figure 2-12 Wall Panorama.
 * <br><b>Gravity line:</b> The image is restored in the direction of the gravity line (yellow vertical line
 * in Figure 2-12 Wall Panorama).
 * @image html wall_panorama.png "Figure 2-12. Wall Panorama."
 * <br><b>FoV:</b> The horizontal FoV (Figure 2-13 Wall Panorama: Horizontal FoV) must to be
 * specified by the user. The vertical FoV (Figure 2-14 Wall Panorama: Vertical FoV) depends on the
 * view height. The greater the view height is, the wider the vertical FoV will be.
 * @image html wall_panor_h_fov.png "Figure 2-13. Wall Panorama: Horizontal FoV"
 * @image html wall_panor_v_fov.png "Figure 2-14. Wall Panorama: Vertical FoV."
 * <br><b>Fan warp by moving the warp axis:</b> The fan degree is specified by the user.
 * The range is [-100~100]; it can perform panorama with fan warp using the moving warp axis,
 * rather than providing the same vertical FoV.
 *
 * @subsubsection wall_mercator 2.4.2 Mercator
 * The Mercator projection is a cylindrical map projection that represents lines of a constant
 * course. This projection enables a larger vertical FoV than general cylindrical or panoramic
 * projections, and a smaller vertical FoV than equirectangular, when the horizontal FoV is the same.
 *  | H-FoV | V-FoV |	Horizontal Curvature |Width / Height Ratio |
 *  | :-----: | :-----: | :---------: | :---: |
 *  | Interactive parameters | Proportional to H-FoV | The closer to the top or bottom of the image, the more curved it is |1:1 |
 * <b>View size:</b> Assume the radius of the fisheye circle in the fake pre-main buffer is R. The
 * following size is not mandatory but recommended by Ambarella.
 * <br>Mercator view height = Mercator view width <= 2R
 * <br>Mercator view width / panorama view height = 1 /1
 * <br><b>View center:</b> The center remains the same as the fisheye circle. The objects in the center of
 * the corrected view maintain the same size as they do in the fisheye view. See the red circles in
 * Figure 2-15 Wall Mercator.
 * <br><b>Gravity line:</b>  The image is restored in the direction of the gravity line (yellow vertical line in
 * Figure 2-15 Wall Mercator).
 * @image html wall_mercator.png "Figure 2-15. Wall Mercator."
 * Mercator projection is the most commonly used map projection. The central meridian projects
 * in a straight line. Other meridians project to straight lines with X constant. The Equator
 * projects to the straight line, and parallel circles project to the straight lines of the constant
 * Y. The projection is unbounded in the Y direction. The poles lie at infinity. The Mercator
 * projection distorts the size of objects as the latitude increases from the Equator to the poles.
 * Only the vertical straight lines and the horizontal line remain as straight lines in the panorama.
 * All other lines become curved.
 *
 * @subsubsection wall_equirectangular 2.4.3 Equirectangular
 * Also referred to as the "non-projection", equirectangular projection is a representation of the
 * sphere that maps longitude directly to the horizontal coordinate, and latitude to the vertical
 * coordinate. It is commonly used as the projection type of the source images for spherical
 * panorama viewers. In addition, it has the largest vertical FoV, with the south and north poles
 * of the sphere visible in the output.
 *  | H-FoV | V-FoV |	Horizontal Curvature |Width / Height Ratio |
 *  | :-----: | :-----: | :---------: | :---: |
 *  | Interactive parameters | Proportional to H-FoV | The closer to the top or bottom of the image, the more curved it is |1:1 |
 * <br><b>View size:</b> Assume the radius of the fisheye circle in the fake pre-main buffer is R. The
 * following size is not mandatory, but recommended by Ambarella.
 * <br>Equirectangular view width <= 2R
 * <br>Equirectangular view width / panorama view height = 1 / 1
 * <br><b>View center:</b> The center remains the same with the fisheye circle. The objects in the
 * center of the corrected view maintain the same size as they do in the fisheye view. See the
 * red circles in Figure 2-16 Wall Equirectangular.
 * <br><b>Gravity line:</b> The image is restored in the direction of the gravity line
 * (yellow vertical line in Figure 2-16 Wall Equirectangular).
 * @image html wall_equirectangular.png "Figure 2-16. Wall Equirectangular."
 * The equirectangular projection maps meridians to vertical straight lines of constant spacing
 * (for meridional intervals of constant spacing), and circles of latitude to horizontal straight lines
 * of constant spacing (for constant intervals of parallels). The projection is neither equal area
 * nor conformal. It is not often used in navigation or cadastral mapping. Only vertical straight
 * lines and the horizon line remain straight lines in the panorama; all other lines become curved.
 *
 * @subsubsection wall_squircular 2.4.4 Squircular
 * @image html squircular_model.png "Figure 2-17. Squircular Model."
 * In this view, the fisheye circle is mapped to a square with little FoV loss; distortion cannot
 * be removed completely. Users can also specify the horizontal FoV with the option "h" and change the
 * vertical FoV via vertical zoom.
 *  | H-FoV | V-FoV | Horizontal Curvature | Width / Height Ratio |
 *  | :-----: | :-----: | :---------: | :---: |
 *  | Interactive parameters | Proportional to H-FoV | The closer to the corner of the image, the more curved it is | 1:1 |
 * <br><b>View size:</b> Assume the radius of the fisheye circle in the fake pre-main buffer is R. The
 * following size is not mandatory, but recommended by Ambarella.
 * <br>Squircular view width <= 2R
 * <br>Squircular view width / panorama view height = 1 / 1
 * @image html wall_squircular.png "Figure 2-17. Wall Squircular."
 * A squircle is a shape intermediate between a square and a circle. There are at least two definitions
 * of "squircle" in use, the most common of which is based on the superellipse. The word "squircle" is
 * a portmanteau of the words "square" and "circle". Squircles have been applied in design and optics.
 *
 * @subsubsection wall_pano_fan 2.4.5 Fan Warp
 * @image html fan_warp.png "Figure 2-18. Wall Mount: Panorama with Fan Warp."
 * The results of fan warp in a panoramic view resemble a fan. In the panoramic view, the image
 * is restored in the vertical direction, and only the horizontal line in the middle of the image is
 * straightened. Using fan warp, the unique straight horizontal line is vertically shifted up and down.
 *
 *
 * @subsection wall_vertical_panorama 2.5 Wall Vertical Panorama
 * <b>Vertical panorama:</b> In this view, the image is restored only in the horizontal direction.
 * It is a transverse transformation of horizontal panoramic correction.
 * @image html vertical_panorama_model.png "Figure 2-19. Vertical Panorama Model."
 *
 * @subsubsection wall_transverse_mercator 2.5.1 Transverse Mercator
 *  | V-FoV | H-FoV |	Vertical Curvature |Width / Height Ratio |
 *  | :-----: | :-----: | :---------: | :---: |
 *  | Interactive parameters | Proportional to V-FoV | The closer to the left or right of the image, the more curved it is |1:1 |
 * <b>View size:</b> Assume the radius of the fisheye circle in the fake pre-main buffer is R. The
 * following size is not mandatory but recommended by Ambarella.
 * <br>Transverse mercator view height <= 2R
 * <br>Transverse mercator view width / panorama view height = 1 / 1
 * <br>When the vertical FoV becomes larger, the ratio of width / height = 3 / 8
 * <br><b>View center:</b> The center remains the same as the fisheye circle. The objects
 * in the center of the corrected view maintain the same size as in the fisheye view.
 * Observe the red circles in Figure 2-20 Wall Mount: Transverse Mercator.
 * <br><b>Gravity line:</b> The image is restored in the direction of the horizontal line
 * (yellow vertical line in Figure 2-20 Wall Mount: Transverse Mercator)
 * <br>The transverse mercator map projection is an adaptation of a map projection widely used in
 * national and international mapping systems around the world. Turning the Mercator
 * projection's cylinder so that it is tangential to the Earth along a meridian (longitude line)
 * instead of the Equator results in the Transverse Mercator projection.
 * @image html transverse_mercator.png "Figure 2-20. Wall Mount: Transverse Mercator."
 *
 * @subsubsection wall_transverse_cylinder 2.5.2 Transverse General Cylindrical
 *  | V-FoV | H-FoV |	Vertical Curvature |Width / Height Ratio |
 *  | :-----: | :-----: | :---------: | :---: |
 *  | Interactive parameters | Proportional to V-FoV | The closer to the left or right of the image, the more curved it is |3:8 |
 * <b>View size:</b> Assume the radius of the fisheye circle in the fake pre-main buffer is R. The
 * following size is not mandatory but recommended by Ambarella.
 * <br>Transverse cylinder view height <= 2R
 * <br>Transverse cylinder view width / panorama view height = 3 / 8
 * <br><b>View center:</b> The center remains the same as the fisheye circle. The objects in the
 * center of the corrected view maintain the same size as in the fisheye view. Observe
 * the red circles in Figure 2-21 Wall Mount: Vertical Panorama.
 * <br><b>Gravity line:</b>  The image is restored in the direction of the horizontal line
 * (yellow vertical line in Figure 2-21 Wall Mount: Vertical Panorama).
 * @image html trans_cylinder.png "Figure 2-21. Wall Mount: Vertical Panorama."
 * The vertical panorama is similar to the horizontal panorama, except for the projection order. The
 * vertical panorama simply corrects the horizontal line while the vertical line is curved, as in the
 * fisheye view. However, this correction is not typically used because the result is unsuitable
 * for human vision.
 *
 *
 * @subsection wall_pannini 2.6 Wall Pannini
 * Pannini projection is an approach to creating wide-angle views that avoid the stretching that
 * occurs for wide standard perspective views, such as wall rectilinear. The projection is a variant
 * on a cylindrical projection; that is, vertical structures remain straight in the projection.
 * @image html wall_pannini.png "Figure 2-22. Wall Mount: Pannini."
 *
 *
 * @subsection wall_pincushion 2.7 Wall Pincushion
 * Pincushion causes straight lines outside the image center to be bent inwards (like a pincushion).
 * Pincushion distortion, the exact opposite of barrel distortion, is a lens radical distortion.
 * With pincushion, it is easier to detect with a telephoto lens. It occurs due to image magnification
 * increasing towards the edges of the frame optical axis. It is important to know that
 * most zoom lenses that go from wide angle to standard or telephoto focal lengths typically suffer
 * from barrel distortion at the shortest focal length, which gradually transitions to pincushion
 * distortion towards the longest end.
 * @image html wall_pincushion.png "Figure 2-23. Wall Mount: Pincushion."
 *
 *
 * @subsection ceiling_desktop_panorama_fulframe 2.8 Ceiling / Desktop Panorama and Full Frame
 * <b>Panorama:</b> Dewarped image with correction in vertical directions.  In this view, users
 * should set the orientation (north / south / west / east (NSWE) and horizontal angle range in degrees.
 * <br><b>Full frame:</b> Dewarped image with correction in vertical directions; projection type is the
 * same as equirectangular. It projects half of the full FoV of lens in radial directions. In this
 * view, users should set the orientation (NSWE) and horizontal angle range in degrees. It should
 * have a larger vertical FoV than that of panoramic.
 * @image html cd_model.png "Figure 2-24. Ceiling / Desktop Panorama Model."
 * <br><b>View size:</b> Assume that the radius of the fisheye circle in the fake pre-main buffer
 * is R. The following size is not mandatory, but recommended by Ambarella.
 * <br>Panorama view width / height <= R
 * <br><b>Orientation:</b> The definition of the orientation in the fisheye circle is shown in
 * Figure 2-26 Ceiling Panorama: 360 View.
 * <br><b>Gravity line:</b> In the ceiling mount view, the gravity lines point to the
 * fisheye center. Only the gravity lines in the north are vertical to the ground. In the corrected
 * view, all lines in the direction of the gravity are restored.
 * <br><b>Top angle:</b> The top angle defines the maximum incident angle in the corrected
 * view. Ensure that the value is close to Pi/2, or the objects at the bottom of the rectilinear view
 * may appear "over-stretched".
 * <br><b>FoV:</b> The horizontal FoV is specified by users. The definition of the horizontal FoV is
 * shown in Figure 2-25 Ceiling Panorama: Horizontal FoV. The vertical FoV depends on the zoom-in
 * factor and view height.
 * @image html ceiling_panor_fov.png "Figure 2-25. Ceiling Panorama: Horizontal FoV."
 * <br><b>Zoom in in vertical:</b> The area further from the top angle may appear too "stretched".
 * User can zoom in the vertical direction to eliminate the stretched appearance.
 * <br><b>360 Panorama:</b> A 360-degree panoramic picture is composed of four 90-degree panorama
 * warp views separately in the north / south / west / east orientations. Each 90-degree warp view can
 * be divided into two warp areas. The four 90-degree panorama warp views must use the same top angle
 * and FoV to achieve seamless stitching on the edge. The order of the 90 pictures in a 360-degree
 * panorama view can be assigned according to the requirement.
 * @image html ceiling_panor_view.png "Figure 2-26. Ceiling Panorama: 360-Degree View."
 *
 *
 * @subsection ceiling_desktop_rectilinear 2.9 Ceiling / Desktop Rectilinear
 * <b>Rectilinear:</b> Dewarped image with correction in both the horizontal and vertical
 * directions. In this view, users should set the orientation (NSWE) of the part for warp correction.
 * @image html cd_rectilinear_model.png "Figure 2-27. Ceiling / Desktop Rectilinear Model."
 * <br><b>View size:</b> Suppose that the radius of the fisheye circle in the fake pre-main buffer is R.
 * The following size is not mandatory, but recommended by Ambarella.
 * <br>Rectilinear view width <= 2R
 * <br>Rectilinear view height <= R
 * @image html ceiling_orient.png "Figure 2-28. Ceiling Mount: Definition of Orientation."
 * <br><b>Orientation:</b> The definition of the orientation in the fisheye circle is shown in
 * Figure 2-28 Ceiling Mount: Definition of Orientation.
 * <br><b>Gravity line:</b> In the ceiling mount view, the gravity lines are pointing to the
 * fisheye center. Only the gravity lines in the north are vertical to the ground. In the corrected
 * view, all lines (yellow vertical line in Figure 2-29 Ceiling Rectilinear) in the direction of the gravity
 * are restored.
 * <br><b>Horizontal Line:</b> Lines in the horizontal direction (yellow horizontal line in
 * Figure 2-29 Ceiling Rectilinear) are restored.
 * @image html ceiling_rectilinear.png "Figure 2-29. Ceiling Rectilinear."
 * <br><b>Top angle:</b> The top angle defines the maximum incident angle in the corrected view.
 * Ensure that the value is close to Pi/2, or the objects on the bottom of the rectilinear view may
 * appear "over-stretched". Figure 2-30 Ceiling Mount: Definition of Top Angle shows the rectilinear view
 * with two top angles.
 * @image html top_angle_def.png "Figure 2-30. Ceiling Mount: Definition of Top Angle."
 * @image html top_angle_ex.png "Figure 2-31. Ceiling Rectilinear: Top Angle."
 * <br><b>FoV:</b> The FoV of the rectilinear view depends on its size. The larger the view size is,
 * the wider the FoV is.
 * <br><b>Zoom in:</b> The corrected view can be zoomed in around the point at the top angle.
 *
 *
 * @subsection ceiling_desktop_sub 2.10 Ceiling / Desktop Sub-Region
 * <b>Sub-region:</b> Dewarped image with correction in both the horizontal and vertical
 * directions. In this view, users can set the projected orientation (NSWE) for warp correction.
 * Orientation refers to projected orientation rather than location orientation. The orientations of west and
 * east should correspond with stream rotation. Pan / tilt angles are also set in degrees.
 * @image html cd_sub_model.png  "Figure 2-32. Ceiling / Desktop Sub-Region Model."
 * @image html ceiling_subx4.png  "Figure 2-33. Ceiling Sub-Region x4."
 * Although similar to wall mount in that there is one mapping pair of pan and tilt angles for each
 * ROI center in the fisheye view, the definitions of the pan-tilt angles are different.
 * <br><b>View size:</b> Assume the radius of the fisheye circle in the fake pre-main buffer is R. The
 * following size is not mandatory, but recommended by Ambarella.
 * <br>Sub-region width / height <= R
 * <br><b>View center:</b> The view center is specified by users. When the zoom factor is 1.0x,
 * the objects in the center of the corrected view maintain the same size as they do in the
 * fisheye view.
 * @image html ceiling_sub_roi.png "Figure 2-34. Ceiling Sub-Region: ROI Center."
 * <br><b>Note that:</b>
 * <br><b>1)</b> The incident angle of the view center must be within Pi/2, which means the distance
 * from the point to the fisheye center must be no greater than F(Pi/2). F( ) is the lens's
 * projection function.
 * <br><b>2)</b> If only one warp area is enabled in this mode, there will be distortion if both the
 * pan and tilt angles are large. The distortion can be avoided if two warp areas are used.
 * <br><b>Pan-tilt angle:</b> The pan-tilt angle is specified by users. The definition of the pan-tilt
 * system can be referred in Figure 2-35 Ceiling Sub-Region: Pan-Tilt Angle.
 * <br><b>Note that:</b>
 * <br><b>1)</b> There is distortion when both the pan and tilt angles are large if only one warp
 * area is enabled. The tolerance of the sum of pan and tilt angles is not a fixed value; it
 * depends on the zoom factor and FoV of the corrected picture.
 * <br><b>2)</b> If two warp areas are enabled, this distortion can be eliminated.
 * <br><b>FoV:</b> The FoV of the corrected view depends on the size of the view and the zoom
 * factor.
 * <br><b>Zooming in:</b> The corrected view can be zoomed in around the view center.
 * @image html ceiling_sub_pan_tilt.png "Figure 2-35. Ceiling Sub-Region: Pan-Tilt Angle."
 * @image html ceiling_sub_fov.png "Figure 2-36. Ceiling Sub-Region:  FoV (Pan Angle = 33 , Tilt Angle = -60)."
 *
 *
 * @subsection transform_twin_vector_to_idsp_format 2.11 Transform 2D Vector to 1D+1D
 * The dewarp library generates 1D+1D vectors, which can be recognized by the IDSP.
 * 1D+1D performs horizontal or vertical warp first, and then the other directions afterwards.
 * This is different from performing the horizontal and vertical warp simultaneously with a 2D
 * vector or remapped coordinate file.
 * <br>The dewarp library provides transformation function "lens_warp_from_twin_vector" and
 * "lens_warp_from_twin_coord" which could reproduce a customized warp result with the deviation
 * within one pixel. Generally, the coordinate of the source in input domain for each output point
 * should be found, for example, (Xo, Yo) is from (Xi, Yi). Note that (Xi, Yi) should be sufficiently
 * accurate at the sub-pixel level (1/16 pixel); do NOT round up, round down, or complete any
 * other operations that could cause accuracy loss. Currently, this feature can be enabled in
 * encode modes with lens warp enable; it cannot be enabled in encode mode 1.
 * ### lens_warp_from_twin_vector
 * <br>The function <b>"lens_warp_from_twin_vector"</b> requires a fixed format for the 2D
 * vector in binary.
 * -# Each 2D vector value should be a signed short (s11.4) caluclated from (input coordinate - output coordinate) * 16.
 * For example, x_part=(Xi-Xo)*16, y_part=(Yi-Yo)*16.
 * -# Separate x_part and y_part into planar formats. The x_part is located at the first half.
 * -# The 2D vector can be either pixel level or grid level. For a grid-level 2D table, the pixel
 * number between two grids (called grid spacing) is restricted to be 8 / 16 / 32 / 64 / 128, and the
 * grid number in the horizontal direction is restricted less than 128, while the grid number in the
 * vertical direction is restricted less than 96. For example, Ambarella suggests that a 2D vector
 * for 1080p should be column=121, row=69, and grid spacing is 16 for both the horizontal
 * and vertical directions. The dewarp library includes one API @ref lens_warp_get_grid_spacing to aid
 * users in obtaining the actual grid spacing value for the specific window resolution.
 * \f[
     horizontal\_grid\_spacing = \frac{1920}{16} + 1 = 121;
 * \f]
 * \f[
     vertical\_grid\_spacing = \frac{round\_up(1080, 16)}{16} + 1 = 69;
 * \f]
 *
 * <br><b> 2D Vector Validity Rules </b>
 * <br>Users must follow the rules below when generating a 2D vector. Ignoring any of the following rules
 * can lead to image artifacts and other unpredictable errors for processes that utilize the converted 1D+1D
 * warp table.
 * -# Point coordinate sign check: the pixels in the VIN domain, with the coodinate origin at the top-left of the image,
 * must not be assigned a negative value. Ambarella suggests setting the coordinate to zero as a workround. Similar rules
 * apply for coorinates originating at the top-right / bottom-left / bottom-right of the iamge.
 * -# Coordinate monotonic: use one row of output images as an example. If point A is located with a larger
 * coorindate value than point B, the source point in the VIN domain for point A must have a larger coordinate
 * value than that of point B. The same rules apply for image columns when calculating the vertical part of the 2D vector.
 * -# 2D vector size: the 2D vector is always at the pixel level or grid level. Users must obtain the resolution
 * with the output size aligned to a magic number (8 / 16 / 32 / 64 / 128 / 256). Refer to the function
 * "lens_warp_get_grid_spacing" or run the commands below:
 * @code {.c}
 * # test_ldc -c 0 --get-align 1920x1080
 * [INFO]  get_twin_vector_alignment:
 * The alignment should be 16 for width(1920) and 16 for height(1080). Afer padding, the final resolution for
 * 2D vector generating is 1920x1088.
 * @endcode
 * -# Maximum shift in pixel units: the vector value is saved in s16 (signed short, s11.4), so the maximum
 * shift is no larger than 2048 pixels.
 * -# Lens warp under encode mode 0 is limited by vertical warp waitlines. It indicates the amount of image
 * lines pre-loaded from smem, which is served for the vertical warp stage. The value can be set using "max-vwarp-wait-lines"
 * in channel configuration, only in the DSP idle state. Therefore, users must obtain the required waitlines
 * according to the 2D vector beforehand, then bring it into system smem consumption. Users can
 * obtain the source codes of computing waitlines with the 2D vector from the Ambarella Shanghai SDK team.
 * -# To avoid the repeated line artifacts in the horizontal warp stage, the "max-padding-width" from channel
 * configuration should be set as a reasonable value. Too much padding width brings IDSP performance
 * penalty. Ambarella recommends that users get help from the host tool "amba_warp_tool_x86_v1.0.0".
 *
 * <br>
 * ### lens_warp_from_twin_coord
 * <br>The function <b>"lens_warp_from_twin_coord"</b> supports loading pure float coordinate. No need
 * to generate 2D vector beforehand but the rules below must be followed when saving the coordinate value into a binary.
 * -# (Xi, Yi) is saved in fpoint_t format for each (Xo, Yo). Both (Xi, Yi) and (Xo, Yo) are at the top left
 * coordinate origin, and the negative coodinate is NOT allowed.
 * -# This function accepts both pixel level and grid level coordinate file.  Same restriction as the grid level
 * twin vector mentioned above.
 * -# The coordinate file must contain extra rows or columns according to the alignment requirements. For a
 * specific resolution, refer to the function "lens_warp_get_grid_spacing" and the example above.
 *
 *
 * @subsection load_zzy_calib_param 2.12 Loading Zhang Zhengyou Calibration Parameters
 * The dewarp library is capable of loading calibration parameters generated via the Zhang Zhengyou method.
 * - Intrinsic matrix: [fx, fy, cx, cy]
 * - Optimal intrinsic matrix: [fx, fy, cx, cy]
 * - Radical distortion parameters: [k1, k2, k3, k4, k5, k6]
 * - Tangential distortion parameters: [p1, p2]
 *
 *
 * @subsection perspective_matrix 2.13 Warp by Perspective Matrix
 * The essence of perspective transformation is to project the image from one viewing plane to
 * another. The relationship between two viewing planes can be described by a perspective
 * matrix (3x3) mathematically.
 * <br> The perspective matrix can be obtained from the coordinates of four corresponding points in
 * two images. The open source library "OpenCV" provides the API "getPerspectiveTransform(...)" to load
 * the four corresponding points and output the matrix in an array.
 * @image html perspective_matrix.png "Figure 2-37. Perspective Matrix."
 *
 *
 * @subsection point_mapping 2.14 Point Mapping
 * The point mapping feature is designed to map the point from the corrected view to the uncorrected view,
 * or perform calculation in the reverse direction.
 *
 * @subsubsection point_mapping_warp_param 2.14.1 Point Mapping with Warp Parameters
 * In this method, users must prepare all related warp parameters to the dewarp library; the process
 * is similar to generating a warp table. Note that this method is only supported in multi-region
 * warp mode (encode mode 1), and the uncorrected view here indicates the fake pre-main buffer domain.
 * Refer to the example @ref ut_point_mapping "point mapping with warp parameters" in the feature sets.
 *
 * There are four coordinate systems in the library.
 * In each of the coordinate systems, the X axis points to the right and the Y axis points to the bottom.
 * -# <b>Coordinate system of the pre-main buffer:</b>
 *    The upper left corner of the pre-main buffer is the ordinate origin, called `Pre-Main` in the
 *    following sections.
 * -# <b>Coordinate system of the fisheye circle:</b>
 *    The center of the fisheye circle is the ordinate origin. It is called `Fisheye`.
 * -# <b>Coordinate system of the main buffer:</b>
 *    The upper left corner of the main buffer is the ordinate origin. It is called `Main`.
 * -# <b>Coordinate System of the Corrected View:</b>
 *    The upper left corner of the corrected view is the ordinate origin. It is called `View`.
 *
 * @image html coordinate_systems.png "Figure 2-38. Coordinate Systems."
 *
 * @subsubsection point_mapping_warp_table 2.14.2 Point Mapping with 1D+1D Warp Table
 * In this method, users are not required to prepare the related warp parameters, but must prepare
 * the generated warp tables (horizontal and vertical), related grid information, and input / output
 * size and location. Note that this method is only supported in the encode mode that supports
 * "lens-warp", and the uncorrected view here indicates the VIN domain. Refer to the example
 * @ref fs_point_mapping_warp_table "Point Mapping with 1D+1D Warp Table".
 *
 * @image html point_mapping_1D+1D.png "Figure 2-39. Point Mapping with 1D+1D Warp Table."
 *
 * - - - -
 *
 * @section dewarp_lua_parser 3. Dewarp Lua Parser
 * | Version | Update Date | Modification |
 * | :-----: | :---------: | :--------- |
 * | 1.0.0 | 20221020 | Create dewarp Lua parser library |
 *
 * The dewarp Lua is different from the Lua scripts of entering the preview for test_encode; it is a newly defined
 * script format used to configure the unit test "test_dewarp" command.
 * <br>There are almost 12 different dewarp modes (more may be supported in the future)
 * supported in the Ambarella dewarp library (check Section @ref dewarp_correction_mode "Correction Mode").
 * Several advanced modes are derived from specific dewarp modes, such as polar mode from wall rectilinear
 * and fan warp from wall panorama. After users check the test_dewarp help information, they may find that
 * some options function for all views, some function only for specific modes, and some are shared between
 * a group of modes. The dewarp Lua script makes this configuration more clear and convenient. The following
 * is an overview of the Lua, which contains four parts:
 * - Part 1: resource information, which is effective for all channels
 * - Part 2: per-channel information, which is effective for all views
 * - Part 3: per-view information, which is effective for specific views
 * - Part 4: per-warp mode information, which is effective for the warp modes from corresponding views
 *
 * @image html dewarp_lua_overall.png "Figure 3-1. Dewarp Lua Scripts Overview."
 *
 * The following is an overview for "warp_mode_adv_param", which lists all parameters for each warp
 * mode. Users can select the required warp mode parameters for their projects and remove the others.
 *
 * @image html warp_mode_adv_param.png "Figure 3-2. warp_mode_adv_param."
 *
 * Below are reference examples. Contact the Ambarella SDK support team for assistance.
 *
 * @subsection dlp_wall_rectilinear 3.1 Dewarp Lua for Wall Rectilinear
 *
 * <a href="scripts/dewarp_lua_wall_rectilinear.lua" target="_blank"><b>dewarp_lua_wall_rectilinear.lua</b></a>
 *
 * @code {.c}
 * board # test_dewarp --dewarp-lua-file /usr/share/ambarella/lua_scripts/dewarp_lua_wall_rectilinear.lua
 * @endcode
 *
 * @image html dewarp_lua_wall_rectilinear.png "Figure 3-3. Dewarp Lua Wall Rectilinear."
 *
 * @subsection dlp_double_panorama 3.2 Dewarp Lua for Ceiling Double Panorama
 *
 * <a href="scripts/dewarp_lua_ceiling_double_panorama.lua" target="_blank"><b>dewarp_lua_ceiling_double_panorama.lua</b></a>
 *
 * @code {.c}
 * board # test_dewarp --dewarp-lua-file /usr/share/ambarella/lua_scripts/dewarp_lua_ceiling_double_panorama.lua
 * @endcode
 *
 * @image html dewarp_lua_ceiling_double_panorama.png "Figure 3-4. Dewarp Lua Ceiling Double Panorama."
 *
 *  - - - -
 *
 * @section lens_sensor 4. Lens and Sensor
 * This chapter detaily introduce the lens attributes that used in our warp library, and how to select a perfect
 * match of sensor and lens for different warp application, also bring a fast method to get the fisheye image
 * center without doing camera calibration.
 *
 *     - Section @ref lens_info
 *     - Section @ref sensor_select
 *     - Section @ref fisheye_center
 *
 * @subsection lens_info 4.1 Lens
 * @subsubsection lens_attribute 4.1.1 Attributes in Lens Datasheet
 * Lens attributes are introduced in this section to aid users in fine-tuning their
 * warp results for different warp views.
 *
 * @subsubsection lens_info_fl_inc_angle 4.1.2 Focal length and incident angle:
 * For a lens, the focal length (f) is the distance from the optical center to the focal sensor.
 * The incident angle (\f$\theta\f$) is the angle between the optical axis and the light ray. The
 * figure below shows the details.
 *
 * @image html f_incident.jpg "Figure 4-1. Focal Length and Incident Angle."
 *
 * @subsubsection lens_info_fov 4.1.3 Field of view (FoV):
 * The FoV is the angle over which objects can be seen. The FoV is the maximum
 * value of the incident angle that can be recorded in the sensor plane. There are three FoV
 * concepts described in the lens datasheet: horizontal FoV, vertical FoV, and diagonal FoV.
 *
 * @subsubsection lens_info_img_circle 4.1.4 Image circle:
 * The image circle is the primary physical characteristic of a fisheye lens. It remains the same
 * irrespective of how the lens is mounted or what type of sensor is used. This value can be found in the
 * lens datasheet.
 * \f[
     Image\_circle\_on\_sensor (pixels) = Lens\_image\_circle(mm) * \frac{1000}{sensor\_cell\_unit(um)}
 * \f]
 * Information on the cell unit of the sensor cell can be obtained from the sensor's datasheet.
 * <br>In a wide angle lens, the lens circle cannot be obtained from the sensor. Ambarella suggests performing
 * calculations to retrieve the correct image circle size in pixels.
 *
 * @subsubsection lens_info_proj_func 4.1.5 Lens projection function:
 * The distance (r) of a point from the optical center depends on the focal length (f) and the incident
 * angle (\f$\theta\f$): \f$r = F(\theta)\f$
 * <br>The direction of a light ray cannot be changed after going through a regular (non-fisheye) lens.
 * The distance (r) from the optical center to the mapping point on the sensor is \f$r = f * tan(\theta)\f$.
 * When the incident angle approaches Pi/2, the distance (r) will be infinite and it will be
 * impossible to record this information in the sensor.
 *
 * @image html non_fisheye_lens.jpg "Figure 4-2. Non-Fisheye Lens."
 *
 * In a fisheye or wide-angle lens (Figure 4-2 Non-Fisheye Lens), the direction of the light ray will be
 * changed after the light ray passes through the lens. The conversion is performed through the
 * projection function, which can be found in the lens datasheet. The following functions are
 * the most commonly used.
 *
 * @image html fisheye_lens.jpg "Figure 4-3. Fisheye Lens."
 *
 * <br><b>Equidistant</b> (also called f-theta): \f$r = f * \theta\f$
 * <br><b>Stereographic</b> (also called tailored distortion): \f$r = 2 * f * tan(\frac{\theta}{2})\f$
 * <br><b>Look-up table (LUT):</b> The mapping between the distance and incident angle is supplied in a table
 * by the lens vendor. Neither the equidistant nor the stereographic equation can be applied
 * to lens distortion. Lenses are all designed with various projection functions. This is the major projection
 * method used in fisheye dewarp.
 * <br>When capturing a wide scene with a fisheye or wide-range lens, the objects far from the
 * optical center are "squeezed". The distortion is determined by the projection function.
 * Usually, stereographic lenses preserve more details on the area of a large
 * FoV. For ceiling-mount cameras, the stereographic lens is a better choice.
 *
 * @subsubsection lens_lut 4.1.6 Lens LUT Mode
 * Amarella CV5x / CV7x supports removing the lens distortion by looking up the lens distortion table
 * provided by lens vendors, it is the relationship between the incident angles and
 * real height calculated from lens optical center, the valid range for real height is [0,
 * half of image circle radius].  This method is called "Lens LUT method" and belongs to
 * one of the lens projection function mentioned in @ref lens_info.  It does not impact the
 * typical correction modes @ref dewarp_correction_mode "Correction Mode" but only impact
 * on how the pixel is projected as a result of lens intrinsic radical distortion.
 * <br>To be recognized by dewarp library, the LUT file is demanded to be generated in the format
 * below including lens basic attributs and distortion table:
 * - Lens ID
 * - Lens FoV
 * - Lens image circle in um
 * - Lens effective focus length in um
 * - Lens LUT number
 * - Lens LUT step
 * - Lens LUT distortion table(saved lut_radius)
 *
 * <b>Lens ID:</b> Ambarella CV5x / CV7x SDK currently supports the following lenses. Each lens
 * ID is defined by a hexadecimal, as shown below.
 * - EVETAR_F117B021IRM12 = 0x00000000
 * - EVETAR_F117B12924IRM12 = 0x00000001
 * - EVETAR_F132B0108IRM12R4 = 0x00000002
 * - EVETAR_M13B02118W = 0x00000003
 *
 * <b>Lens LUT step:</b> the degrees of each step in the Lens LUT distortion table (saved lut_radius).
 *
 * <b>Lens LUT number:</b> the numbers of pairs betweeb real height and incident angle.
 *
 * <b>Lens LUT distortion table:</b> the relationship between the incident angle and the
 * LUT radius (real height / lens image circle). As the fisheye circle is symmetrical, the table
 * below shows the angle and the real height from 0 degrees to MAX_FOX / 2. The LUT step means
 * the incident angle step that is allowed to be a float type.
 *
 * To convert the real height in pixel unit, the `test_ldc` or `test_dewarp`
 * application need to take the sensor unit size and
 * effective focal length into consideration.
 * \f[
	 lut\_radius[n] = \frac{real\_height[n]}{lens\_image\_circle}
 * \f]
 *
 * @subsubsection lens_lut_example 4.1.7 Lens LUT Examples
 * <b> Example 1: How to generate Lens LUT distortion table. </b>
 * 1. Get the table below that is an original distortion table format provided by lens vendor.
 * The lens EFL is 1.08 mm, and the image circle is 3.5 mm.
 *	| Angle (degree) | Real Height (mm) |
 *	| :------------: | :---------: |
 *	|0 |0 |
 *	|1 |0.02 |
 *	|2 |0.04 |
 *	|3 |0.06 |
 *	|...|...|
 *	|100 |1.73|
 * 2. Divided the real height with image circle (3.5 mm)
 * <br> lut_radius[0]= 0
 * <br> lut_radius[1]= 0.02/3.5
 * <br> lut_radius[2]= 0.04/3.5
 * <br> lut_radius[3]= 0.06/3.5
 * <br> . . .
 * <br> lut_radius[100]= 1.73 /3.5
 * 3. Saved the lut_radius value as shown below, ensure that the radius in the table is monotonic increasing.
 * @code {.c}
 * <br>cat lut_radius.txt
 * 0
 * 0.005714
 * 0.011428
 * 0.017142
 * ...
 * 0.494285
 * @endcode
 *
 * <b> Example 2: Generate lens binary file for dewarp library with tool "lens_data_tool". </b>
 * @code {.c}
 * Generate lens binary file:
 * #lens_bin --in-lut lut_radius_file --bin lens_binary_file -i 1 -F 200 --lut-num 101 --image-circle 3500 -e 1080 --lut-step 1 -m 0
 * Parse lens binary file:
 * #lens_bin --bin lens_binary_file -m 1
 * @endcode
 * This tool is located in
 * - Cooper SDK path: `./ambarella/prebuild/library/lens`
 * - Firmware: `/usr/share/ambarella/lens/`

 * <b> Example 3: Lens LUT Mode in LDC. </b>
 * @code {.c}
 * board # init.sh --imx274_mipi
 * board # test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua 	   // For CV5 or CV52
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear_ldc.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua)  // For CV72
 * board # rtsp_server
 * board # test_encode -A -h1080p -e
 * board # test_ldc -c 0 -R 1088 -F 200 -L 2 -m 1 --lut-efl 667 --lut-bin /etc/lens/EVETAR_F132B0108IRM12R4.bin -v
 * @endcode
 * `--lut-efl` effective focal length (EFL) in pixels can be found in the lens' specifications. Take the
 * value as an example, EFL for F132B0108IRM12 is 1.08 mm, and the cell unit width of sensor imx274 is 1.62 um.
 * \f[
	 efl\_in\_pixel = 1.08 *  \frac{1000}{1.62} = 667
 * \f]
 *
 *
 * @subsection sensor_select 4.2 Sensor Selection
 *
 * @subsubsection full_fisheye_circle 4.2.1 Full Fisheye Circle
 * The complimentary metal-oxide semiconductor (CMOS) sensor includes an "optical format" which
 * can be 1/3 inch, 1/2.3 inch, and so on. Typically, the the optical format number is estimated,
 * and users should refer to the datasheet for the size of the CMOS sensor.
 * @image html Sensor_Full_Resolution_2304x1536.png "Figure 4-4. Sensor with Full Resolution 2304x1536."
 * For example, if a sensor has full resolution 2304x1536, and each pixel is 2.2x2.2 um, the
 * user can calculate the width to be 2304*2.2= 5068.8 um and the height to be
 * 1536*2.2 = 3379.2 um. Therefore, the sensor active image size is 5.068x3.379 mm. When users
 * compare the sensor's active image size to the lens image circle size, they should use this
 * method (by calculation from the cell size and pixel count), but not directly refer to the "optical
 * format" in the sensor datasheet.
 * Refer to the following figure for an example of using a fisheye lens with the same sensor.
 * Users can obtain different results using a different fisheye lens with different image circle
 * diameters.
 *
 * @image html match_of_lens_sensor.png "Figure 4-5. Different Fisheye Lens and Image Circle Diameter."
 *
 * It is important to note the following:
 * -# The number of pixels captured is directly proportional to the amount of information that the
 *	user receives. If the user is able to capture more pixels from the same sensor to record a
 *	picture, the user will receive more information. If the encoding resolution (pixel count) is
 *	the same, with more pixels captured, the picture will have improved image sharpness and
 *	higher visual resolution.
 *	<br>To perform dewarp with the same sensor, the type A situation is usually better than type B.
 * -# If the image circle has some part of the image that does not fall into the sensor image area,
 *	that part of the information will be lost in the FoV. If the user is concerned about
 *	the vertical FoV on the sensor, as in the ceiling mount dewarp use case, type C or D cannot be
 *	used.
 *	<br>If the user is not concerned about the vertical FoV and only uses it for the wall mount use
 *	case, with type C, full horizontal FoV can be obtained. Because it captures more
 *	pixels in the horizontal direction, it will result in greater image sharpness and higher visual
 *	resolution than type A or B.
 * -# Most fisheye lenses have better resolution at the center, and the center of the image is
 *	"amplified" with details. The corners do not have as much detail as the center.
 *	If the user is only concerned about the center of image, and not as concerned about the FoV,
 *	they can attempt to use type D, which uses the best resolution of
 *	the lens and all pixels of the sensor to get the best center
 *	image.
 *	<br>Wall-mount fisheye dewarp camera design:
 *	<br>Ambarella recommends using type C. If type C cannot be used, Ambarella
 *	recommends using type A.
 *	<br>Ceiling-mount (or both ceiling and wall mount) fisheye dewarp camera design:
 *	<br>Ambarella recommends using type A.
 *	<br>Note that it is harder to identify the correct lens for the 16:9 aspect ratio sensors
 *	because the sensor height is relatively small. However, because a fisheye lens with a small
 *	image circle typically has a high resolution, Ambarella recommends using a 1/3-inch sensor
 *	or larger with the aspect ratio of 4:3 or 3:2.
 *
 * @subsubsection fisheye_IQ 4.2.2 Fisheye Image Quality
 * A sensor with more pixels has better resolution and better visual resolution. Visual
 * resolution is measured using an actual lens with the sensor in proper light conditions to
 * focus on the test chart to determine how many lines it can reach, or use a test pattern with
 * line pairs to obtain the MTF value. However, note that more pixels does not always indicate a
 * better visual resolution.
 * <br>The following pictures show the difference between two different sensors using the same
 * regular lens, shooting the same target at the same lux level.
 * @image html difference_of_two_lens_sensor.png "Figure 4-6. Regular Lens with Two Different Sensors."
 * <br>Although a low-cost 5M CMOS sensor may use more pixels for the same object, it may not
 * necessarily provide greater details. The images in this section show that a high-quality 1080p
 * sensor may have the same level of details as a 5M sensor, and provide an image with a higher
 * signal-to-noise ratio (SNR) and better resolution.
 * <br>Therefore, it is important for users to choose the correct sensor. Because dewarp includes an
 * extra rescaler, it can cause further loss of resolution. While designing a fisheye dewarp
 * camera, the user must follow the suggestions provided in the CV5x/CV7x Linux SDK to select the
 * correct sensor.
 *
 * @subsubsection mount_lens 4.2.3 Mounting Lens
 * The lens should be accurately mounted so that the image circle center is the sensor's optical
 * sensor.
 * @image html correct_mounting.png "Figure 4-7. Comparison of Two Cameras' Design for Correct Mounting."
 * Camera A shows that the lens is correctly mounted with the sensor; however, Camera B,
 * shows the lens and sensors are incorrectly mounted, with some X-Y offset. Additionally,
 * because the image circle in Camera B is already beyond the sensor image area, it cannot be
 * perfectly compensated using a software solution. Adjusting the mechanical setup of the
 * lens can correct this issue.
 * @image html perfect_mounting.png "Figure 4-8. Comparison of Two Cameras' Design for a Perfect Image Circle."
 * The figure above shows that Camera C has a perfect image circle, but Camera D's image circle
 * is elliptical. This is because in Camera D, the lens optical axis is not 100% perpendicular to
 * the sensor surface. This can occur because the lens holder's screw thread is too loose or
 * the lens holder is not correctly mounted to the sensor board's printed circuit board (PCB).
 * <br>In Camera D's setup, there will be problems on the image output. The following figure shows
 * the image output from the left side and right side of Camera D:
 * @image html left_right_cameraD.png "Figure 4-9. Image Output Left Side and Right Side of Camera D."
 * The figures in this section show that mounting the lens incorrectly can produce an incomplete
 * or elliptical image circle, causing inconsistent focusing of the images.
 *
 *
 * @subsection fisheye_center 4.3 Fisheye Center
 * Before dewarping, the fisheye circle center must be identified in the fake pre-main buffer of the
 * unwarped channel (multi-region dewarp) or VIN (LDC). Ambarella suggests performing Zhang
 * Zhengyou calibration using a chessboard, from which the result is sufficiently accurate.  Another
 * convenient, but less accurate, the method is the tool `fish_center_calibration.sh`. This tool is
 * provided to find the circle center in the image. The related files:
 * `./ambarella/unit_test/private/package_test/arch_v6/scripts/fishey_center`
 * <br>The steps of the script are as follows:
 * 1.	Reboot the board.
 * 2.	Initialize VIN and force IAV to enter preview mode with the selected sensor, resolution,
 *    and commands.
 * 3.	Ensure that the lens is focused correctly. The preview from the high-definition multimedia
 *    interface (HDMI®) cable will help the camera to adjust the focus.
 * 4.	Cover the lens with a white half-transparent cap. The goal is to ensure that the
 *    fisheye circle is bright enough and the rest is dark. The edge of the circle must be clear.
 * 5.	The script will run @b cali_fisheye_center to find the center axis. If there are no error
 *    messages, the result is reliable. Users can perform one more test (which is supported
 *    in the script) and verify that the result is reliable. Users can choose one of the results.
 *    The radius is for reference only, it cannot be used as a circle radius for dewarping.
 * 6.	If the results are very different, ensure the following:
 *    The light is bright enough inside the circle.
 *    The edge is clear and sharp.
 *    There is no leakage of light on the edge.
 * @image html fish_center_calibration.png "Figure 4-10. Results of fish_center_calibration.sh."
 *
 * - - - -
 *
 * @section warp_system_config 5. System Configuration
 *
 * This chater introduces warp related configuration in system level including hardware resource,
 * warp alignment, buffer layout, the ME1 warp table for different encode modes; Some features such as
 * warp DPTZ and warp input mode.
 *
 *     - Section @ref warp_dual_chan
 *     - Section @ref warp_hw_res
 *     - Section @ref warp_align
 *     - Section @ref pm_on_warp
 *     - Section @ref post_buffer_layout
 *     - Section @ref warp_dptz
 *     - Section @ref warp_input_mode
 *     - Section @ref ldc_me1
 *
 * @subsection warp_dual_chan 5.1 Dual Channel for Multi-Region Warp
 * ###Pros and Cons
 * Below is a comparison of multi-region warp between CV2x, CV5x, and CV72x.
 * <br><b>Pros</b>:
 * <br>1. Although dual channels are implemented for encode mode 1, the IDSP performance is
 * almost the same.
 * <br>2. The unwarp channel can be flexibly configured as encode mode 0/5.
 * <br>3. There is no pass concept in CV5x / CV7x mode 1.
 * <br><b>Cons</b>:
 * <br>Users must confgure the partner relationship using the system option "raw_src_chan".
 * ###EFR with YUV for warped channel:
 * The main buffer of the unwarped channel is connected to the warped channel by one dummy sensor,
 * which is performed by AMBDS.  Regardless of the main buffer resolution from the unwarped channel,
 * AMBDS handles the VSRC configuration.
 * ###Fake pre-main:
 * On the CV5x / CV7x platforms, the main buffer from the unwarped channel functions as the video source
 * of the warped channel, called the fake pre-main buffer. Ambarella does not suggest performing LDC for
 * the unwarped channel, as it could break the camera geometry relationship.
 * - Input window
 * Once the sensor and the lens are selected, the fisheye circle's diameter calculated in the unit
 * of pixels is known and fixed. Before sending the fisheye circle into the warping stage, Ambarella
 * recommends configuring the pre-main input window width and height:
 * <br>Pre-main input window = lens image circle on sensor (pixels)
 * <br>Vertical upscaling is not supported by the pre-main input window or the pre-main buffer in
 * multi-region warping mode, as upscaling causes dark padding be added around the
 * circle view in order to meet the input window height restriction.
 * - Buffer size:
 * As mentioned in previous sections, the
 * recommended view size for each mode is related to the fisheye circle's radius in the
 * pre-main buffer. The fisheye circle's radius is estimated by the view size. For example,
 * if 800x600 is picked up for sub-region dewarping, the preferred pre-main buffer size is no
 * less than 1600x1600.
 *
 *
 * @subsection warp_hw_res 5.2 Warp Hardware Resource
 * ### Maximum Warp Input / Output Width:
 * In addition to the maximum size of the source buffers and streams, the maximum width for
 * warping areas must be configured in the system resource setting.
 * <br>The maximum width does not refer to the width of the corrected view. Rather, it sets
 * the limit for the warping area. For example, a 2048x768 wall panorama view contains two
 * warping areas. The maximum width for the input warping area is 2048 and output is
 * 2048 / 2 = 1024.
 * <br>There is no equation to calculate the maximum value of the input warping area. Use the
 * fake pre-main buffer width as the maximum input warping width. If the system resource is
 * insufficient, try reducing this value gradually so that it does not break the dewarping effect.
 * ### max_padding_width / lens_warp:
 * The valid range is 0 to 256, the same for LDC. When entering multi-region warp
 * encode mode, set the option "lens-warp" to 0 in the Lua configuration.
 * ### max_vwarp_blk_height:
 * When processing one warp macroblock (16x16) in the vertical warp stage, warp engine hardware
 * fetches image lines configured by <b>max_vwarp_blk_height</b>. Usually, this is related to
 * active warp cases. Users can specify it in the Lua using the item "max_vwarp_blk_height = 28"; the
 * valid range is [0, 64]. It affects both warp cases in LDC and multi-region warp. The default
 * value is 28 for LDC cases and 64 for multi-region warp cases.
 * ### max_vwarp_wait_lines:
 * Under encode mode 0, the vertical warp stage of lens warp requires enough <b>wait lines</b> to
 * avoid the artifacts generated. The vertical warp no longer requires <b>max_vwarp_blk_height</b>.
 * Confirm the <b>max_vwarp_wait_lines</b> via the LDC application, which reports the wait lines
 * required by the active warp case, and then configure it to back to the Lua file for the system
 * and re-enter the preview again.
 * <br> It is not wise to configure a large wait lines for the system which probably leads to DSP
 * assertion of internal resource shortage before entering preview. The internale resource is shared
 * by all the system modules like encoding streams, canvas size and so on. So it is better to set
 * the minimum waitlines demanded to satisfy all the warp cases.  Here a mathematic formula is
 * provided to help users understand the relationship between wait lines and different incident angles(theta)
 * \f$[
     focal_length = \frac{EFL(mm)}{pixel_cell_unit_size(mm)}
     wait lines (pixels) = focal_length * tan(\theta) - focal_length * \theta
 * \f$]
 *
 * @subsection warp_align 5.3 Warp Alignment
 * <table>
 * <caption id="warp_alignment_table">Table 5-1. Warp Alignment</caption>
 * <tr><th> Encode mode <th> Pipeline <th> Input/Output <th> Offset <th align="left"> Width & Height
 * <tr><td rowspan="4"> Mode 0/5, LDC <td rowspan="4"> Horizontal warp first <td rowspan="2"> Input <td> x-4 <td> width-16
 * <tr>                                                                                               <td> y-2 <td> height-8
 * <tr>                                                                        <td rowspan="2"> Output <td> N/A <td> width-16
 * <tr>                                                                                                <td> N/A <td> height-8
 * <tr><td rowspan="8"> Mode 1, Multi-Region Warp <td rowspan="4"> Horizontal warp first <td rowspan="2"> Input <td> x-16 <td> width-16
 * <tr>                                                                                                         <td> y-8 <td> height-8
 * <tr>                                                                                  <td rowspan="2"> Output <td> x-8 <td> width-32
 * <tr>                                                                                                          <td> y-8 <td> height-16
 * <tr>                                           <td rowspan="4"> Vertical warp first <td rowspan="2"> Input <td> x-16 <td> width-16
 * <tr>                                                                                                       <td> y-8 <td> height-16
 * <tr>                                                                                <td rowspan="2"> Output <td> x-16 <td> width-32
 * <tr>                                                                                                        <td> y-16 <td> height-8
 * </table>
 *
 *
 * @subsection pm_on_warp 5.4 Privacy Mask (PM) on Warp View
 * ### Privacy Mask with LDC:
 * Privacy masks can be added after LDC is enabled, even in the rotation pipeline.
 * Once a new warp effect is applied in a specific channel, the PM added in the previous warp effect will be
 * placed in the wrong location with new warp table compensation. Users must disable the PM and
 * add it again.  In order for the PM to function correctly with LDC, the warp table should be applied first.
 * <br>Users should refer to option "use-warp-table" in @ref test_privacymask.c, which controls two
 * types of PM after LDC:
 * @image html PM_w_LDC.png "Figure 5-1. No Jaggy with Distortion versus Rectangle PM with Jaggy."
 * ###Circle PM on Fisheye:
 * In order to cover up light leakage from the lens and create a sharp edge for the fisheye circle,
 * users can apply a complement PM for circles; see the examples below. This type
 * of PM is added in the pre-main buffer domain.
 * @image html pm_fisheye.png "Figure 5-2. Circle PM on Fisheye."
 *
 *
 * @subsection post_buffer_layout 5.5 Main Buffer Layout Design
 * ### Main Buffer Size:
 * The corrected views are placed in the main buffer space. The user is expected to specify
 * the size of the main buffer according to the layout of the views.
 * @image html main_buffer.png "Figure 5-3. Main Buffer."
 * Main Buffer Layout:
 * Ambarella recommends that users specify the position of the views in a compact manner in order to
 * optimize dynamic random access memory (DRAM) for the main buffer. For example, assume
 * that two views are to be placed in the main buffer. One view is a 1920x720 wall panorama and
 * the other is 800x600. The total main buffer size for Layout A is 2720x720 and Layout B is 1920x1320.
 * Between the two layouts, Layout A is a better choice from the DRAM usage perspective.
 * @image html layout_1920x720_VGA.png "Figure 5-4. Layouts of 1920x720+VGA on Main Buffer."
 * ### Wall Mount: Rectilinear
 * @image html layout_rectilinear.png "Figure 5-5. Rectilinear Layout."
 * <br><b>Example 1</b> Wall Mount: Fisheye view (no transformation) + Rectilinear + 180 Panorama
 * Refer to the example No Transform + Wall Rectilinear + Wall Panorama in the document dewarp unit test.
 * @image html no_trans_sub_panor.png "Figure 5-6. Wall Mount:  Fisheye View (No Transform) + Sub-Region + 180 Panorama."
 * <br><b>Example 2</b> Wall Mount: Fisheye view (no transformation) + polar warp + advance yaw + Mercator
 * Refer to the example Wall Rectilinear + Wall Polar Warp + Wall Advance Pitch + Wall Mercator in the document dewarp unit test.
 * @image html fisheye_polar_adv_yaw_mercator.png "Figure 5-7. Wall Mount:  Fisheye View, Polar Warp, Advance Yaw, Mercator."
 * <br><b>Example 3</b> Wall Mount: 180 Panorama + Eyeball Rotation x4
 * Refer to the example Wall Panorma + Eyeball Rotation in the document dewarp unit test.
 * @image html panor_eyeball.png "Figure 5-8. Wall Mount: 180 Panorama + Eyeball Rotation."
 * <br><b>Example 4</b> Ceiling Mount: Sub-region x4
 * Refer to the example Ceiling Rectilinear North and South, West and East in the document dewarp unit test.
 * @image html ceiling_sub_regionx4.png "Figure 5-9. Ceiling Mount: Sub-Region x4."
 * <br><b>Example 5</b> Ceiling Mount: Double 180 Panorama
 * Refer to the example Ceiling Double Panorama in the document dewarp unit test.
 * @image html ceiling_double_panor.png "Figure 5-10. Ceiling Mount: Double 180 Panorama."
 * <br><b>Example 6</b> Ceiling Mount: 360 Panorama
 * Refer to the example Ceiling Panorama Mode - 360 in document dewarp unit test.
 * @image html 360_Panorama.png "Figure 5-11. Ceiling Mount: 360 Panorama."
 *
 *
 * @subsection warp_dptz 5.6 Warp DPTZ
 * When configuring a preview buffer as a warp buffer, the content is scaled from post-main by
 * default. DPTZ II is not supported in multi-region warping mode,
 * which indicates that the input window does not function in this mode.
 * @image html default_layout_prev.png "Figure 5-12. Default Area Layout on Warped Preview Buffer."
 * The IAV driver assigns the default area layout for the preview buffer each time the warping
 * control parameters are reset. The following section introduces the concept of "warp DPTZ",
 * which allows the user to disable the default behavior and set the customized layout on the
 * sub-buffers. Refer to example in feature sets @ref ut_warp_dptz "Example 33: Warp DPTZ".
 * @image html warp_dptz_prev.png "Figure 5-13. Warp DPTZ on Sub-Buffer."
 * <br>Note that this type of digital PTZ (warping DPTZ) is not DPTZ (II). The DPTZ in this section
 * functions in the warping views dimension only, as shown in figure 5-14 Warp DPTZ on Sub-Buffer (a).
 * One warping DPTZ cannot cross two warping views at a time. If the application requires the area
 * across two views, it must use two warping DPTZ views, as shown in (b). If the application
 * must exchange the location of some warp views, refer to (c). If the application
 * requires area across two views, and must perform an upscale for one view and a downscale for another view,
 * refer to (d).
 * <br><b>Keep Warp DPTZ:</b>
 * <br>When changing the warp effect on the specified areas, the IAV driver attempts to re-draw warp
 * DPTZ on the preview buffer by default. If users are required to use the customized warp DPTZ
 * parameters to keep the customized warp layout, they should turn on the "keeping warp DPTZ"
 * flag for the relative sub-buffer when calling the warp control API.
 *
 *
 * @subsection warp_input_mode 5.7 Warp Input Mode
 * To meet different requirements from system resource perspective, the application could specify
 * the input mode type @ref WARP_INPUT_MODE, below table shows the pros and cons.
  * <table>
 * <caption id="warp_input_mode_table">Table 5-2. Warp input mode</caption>
 * <tr><th> Input mode Type
 *     <th> Notes
 *     <th> Pipeline
 *     <th> Pros and Cons
 * <tr><td align="middle"> WIM_MIN_BOUNDING_RECT
 *     <td> Minimum bounding rectangle (default)
 *     <td> N/A
 *     <td> Pros: DRAM bandwidth and raw padding wise <br>Cons: Cost more vertical warp block height or wait lines for H+V pipeline
 * <tr><td align="middle"> WIM_ORIGINAL_INPUT
 *     <td> Original full VIN size or premain buffer size
 *     <td> H+V
 *     <td> Pros: Wise for vertical warp block height or wait lines <br>Cons: Cost more DRAM bandwidth and raw padding
 * <tr><td align="middle"> WIM_MIN_WIDTH_MAX_HEIGHT
 *     <td> Minimum bounding rectangle width and original input height
 *     <td> H+V
 *     <td> Pros: Wise for raw padding and vertical warp block height or wait lines <br>Cons: DRAM bandwidth is larger than WIM_MIN_BOUNDING_RECT
 * </table>
 *
 *
 * @subsection ldc_me1 5.8 ME1 H/V for Lens Warp
 * The motion estimation block, which is used to ensure the image quality of the stream when motion occurs in the
 * FoV, is designed for lens warp pipeline under encode mode 5/9 only. It takes the quad size for both
 * width and height of main buffer size and derives from the normal horizontal or vertical table with different grid
 * spacing and counts.
 * | Encode mode |Notes |
 * | :---------: | :---------: |
 * |High dynamic range (HDR) line-interleaved mode | ME1 size vertical warp table|
 * |AISP mode | Both ME1 size horizontal and vertical warp table|
 *
 *
 * - - - -
 *
 * @section dewarp_development 6. Dewarp Development
 *
 * This chapter introduce the workflow of unit test application (test_ldc and test_dewarp) and the basic data
 * structure for warp library initialization, and targets to help users get familiar with the methods of utilizing
 * warp library and develop their owne application.  It contains the following sections:
 *
 * - Section @ref dewarp_intro_init_param
 * - Section @ref dewarp_ldc_dev
 * - Section @ref multi_region_warp
 *
 * @subsection dewarp_intro_init_param 6.1 Introduction to "dewarp_init_param"
 * @code {.c}
 * typedef struct {
 *	version_t version;
 *	memblock_t heap;
 *	memblock_t stack;
 *	channel_info_t channel_info[MAX_CHANNEL_NUM];
 *	u32 debug_check_disable : 1;
 *	u32 debug_reserved : 31;
 * } dewarp_init_t;
 * @endcode
 * @code {.c}
 * typedef struct {
 *	u32 enable : 1;
 *	u32 channel_id : 4;
 *	u32 vcap_mode : 4;
 *	u32 reserved : 23;
 *	input_limit_t max_input;
 *	rect_t post_buffer_size;
 *	lens_info_t lens_info;
 *	fisheye_area_t fisheye_area;
 *	warp_limit_t warp_limit;
} channel_info_t;
 * @endcode
 *
 * Check the definition of dewarp_init_t and channel_info_t. For lens warp under
 * AISP (encode mode 9), users are required to configure DSP_AISP_MODE for "vcap_mode".
 * Other items in channel_info are almost the same as those for other encode modes;
 * refer to the steps and sample codes in @ref test_ldc.c or @ref test_dewarp.c.
 *
 *
 * @subsection dewarp_ldc_dev 6.2 LDC Development
 * Refer to @ref test_ldc.c to learn how to develop user applications.
 * - Malloc memory for the warp table according to the channel number -- map_warp().
 * - Configure general dewarp,  @ref fov "Lens FoV", max radius,
 * @ref lens_projection_mode "lens projection", @ref fishey_center "center coordinate",
 * verbose option, and save the vector flag.
 * - Configure @ref dewarp_correction_mode "warp correction" and advanced warp parameters.
 * - Initialize the dewarp library.
 *   1. Set the log level for the dewarp library.
 *   2. Check lens @ref lens_projection_mode "projection type" in the LUT.
 *   3. Obtain the VIN and main buffer sizes.
 *   4. Malloc the heap memory used by the library. Assign "dewarp_init_param.heap.addr".
 *   5. Set the default value for parameters used by multi-region warp.
 * - Create a warp table @ref warp_vector_view  "create_lens_warp_vector(channel_id)" ->
 * Check warp table information -> Update to IAV driver via "IAV_IOC_CFG_WARP_CTRL"
 * and "IAV_IOC_CFG_WARP_CTRL".
 * - Deinitialize the dewarp library.
 *   1. Free the heap memory malloced for library computation.
 *   2. Free the array used for the LUT.
 *   3. Free the memory used for twin vector conversion to 1D+1D mode.
 *
 * @subsection multi_region_warp 6.3 Multi-Region Warp Development
 * Refer to @ref test_dewarp.c to learn how to develop user applications.
 * - Malloc the memory for the warp table according to the channel number.
 * - Configure general dewarp, mount method, @ref fov "Lens FoV", max radius,
 * @ref lens_projection_mode "projection type", @ref fishey_center "center coordinate",
 * verbose option, and save the vector flag.
 * - Configure warp parameters for each view, update view map, and view ID,
 * @ref post_buffer_layout "view size and view offset",
 * @ref dewarp_correction_mode "warp correction", advance warp parameters, max area number,
 * and area behavior (change, update or clear).
 * - Initialize the dewarp library.
 *   1. Set the log level for the dewarp library.
 *   2. Check the lens @ref lens_projection_mode "projection type" in the LUT.
 *   3. Sum up the total area number for vector memory deployment.
 *   4. Count area numbers for each view for area update behavior.
 *   5. Obtain @ref pre-main "pre-main" and post-main buffer size.
 *   6. Malloc the heap memory used by the library. Assign "dewarp_init_param.heap.addr".
 * - Create a warp table "create_fisheye_warp_vector()" for each warp view -> Count the area numbers for each view for area
 * update behavior -> Check the warp table information -> Update to IAV driver via "IAV_IOC_CFG_WARP_CTRL" and
 * "IAV_IOC_CFG_WARP_CTRL".
 * - Deinitialize the dewarp library.
 *   1. Free the heap memory malloced for library computation.
 *   2. Free the array used for the LUT.
 *   3. Free the memory used for twin vector conversion to 1D+1D mode.
 *
 *
 * - - - -
 *
 *@section dewarp_qa 7. Dewarp Trouble Shooting
 * This chapter provides frequently asked questions (FAQs) and answers that are specific to multi-region dewarp
 * and LDC. More information will be added in the future.
 *
 * @subsection dewarp_qa_q1 Question 1: What is the difference between LDC and multi-region dewarp?
 * @b Answer:  @ref LDC_and_dewarp.
 *
 * @subsection dewarp_qa_q2 Question 2: Why there are artifacts in the warp results when performing rotation in large angles?
 * @b Answer:  It should be clear that the Ambarella IDSP warp engine is implemented differently from the
 * pure memory operation of 2D warp. There is a limitation on the warp engine to fetch pixels from lines far
 * away. <br>To minimize artifacts, Ambarella suggests configuring the proper warp region resolution
 * and other parameters that affect the hardware resource demanded by the warp table.
 *
 * @subsection dewarp_qa_q3 Question 3: How can users get a panning effect from ceiling-mount 360 panorama?
 * @b Answer:  @ref ut_warp_enc_sync_proc "Warp Encode Sync Process"
 *
 * @subsection dewarp_qa_q4 Question 4: What are easy ways to configure parameters for different warp views using test_dewarp?
 * @b Answer:  @ref dewarp_lua_parser "Dewarp Lua Parser"
 *
 * @subsection dewarp_qa_q5 Question 5: Are there examples for each correction mode?
 * @b Answer:  @ref fs_adv_ldc "Lens Distortion Correction" and @ref fs_adv_dewarp "Multi-Region Warp"
 *
 * @subsection dewarp_qa_q6 Question 6: How do users sharpen a fisheye edge?
 * @b Answer:  As a result of deviation from installation, light may leak at the edge of the fisheye circle.
 * Users are encouraged to try a circle privacy mask, which can be set at the pixel level to block any useless
 * pixels. @ref PM_fisheye
 *
 * @subsection dewarp_qa_q7 Question 7: Does multi-region warp mode function with multiple VIN sources?
 * @b Answer:  No. Contact the Ambarella Shanghai SDK team with any requests.
 *
 * @subsection dewarp_qa_q8 Question 8: How can the warp view aspect ratio be maintained?
 * @b Answer:  The aspect ratio may be inappropriate for some views in the post-main buffer, which is caused by warp
 * correction; users can tune the option "sar" from test_encode for a more satisfying aspect ratio when
 * starting to encode.
 * @code {.c}
 * board # test_encode -A -h 2048x2048 --sar 1/1 -e
 * @endcode
 *
 * @subsection dewarp_qa_q9 Question 9: How to get the vertical warp waitlines under encode mode 0?
 * @b Answer:  @ref warp_hw_res
 *
 * - - - -
 *
 * @section dewarp_api_sec 8. Dewarp API
 * Visit the following link to see details of the API function.
 *      - @ref dewarp-api-api explains API functions.
 *      - @ref dewarp-helper shows related structures, macros, and enumerations.
 *      - The return error number has been added for dewarp library APIs.
 *  | ERROR NUMBER | DESCRIPTION |
 *  | :------------: | :---------: |
 *  |@ref DEWARP_SUCCESS | Return success |
 *  |@ref DEWARP_EINVALID | Invalid arguement |
 *  |@ref DEWARP_EPERM | Operation not permitted |
 *  |@ref DEWARP_EFAULT | Bad address |
 *
 * - - - -
 *
 * @section dewarp_license 9. License
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
 * @defgroup dewarp-api Dewarp Library API
 * @brief dewarp Library API, in file amba_lib_dewarp.h
 */
/*!
 * @defgroup dewarp-api-api Dewarp Library API Details
 * @ingroup dewarp-api
 * @brief dewarp Library API, in file amba_lib_dewarp.h
 */
/*!
 * @defgroup dewarp-helper Dewarp Library API Helper
 * @ingroup dewarp-api
 * @brief dewarp Library Api Helper: Struct, Enumeration and Macros, in file amba_lib_dewarp.h
 *
 */

/*!
 * @example test_ldc.c
 * This is a source code file of test_ldc.c.
 *
 * @example test_dewarp.c
 * This is a source code file of test_dewarp.c.
 */

/*!
 * @file doc_lib_eazyai.h
 * @brief This is a .h file for doxygen document system.
 * @version 1.0
 * @date 2022-09-26
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
 * @page page_lib_eazyai_doc EazyAI Library API
 *
 *
 * @section eazyai_history 0 Revision History
 * <table>
 * <caption id="lib_eazyai_rev_history"></caption>
 * <tr align="middle"><th> Library Version <th> Updated Date <th> Modification
 * <tr align="middle"><td> 0.1.1 <td> 20200827 <td align="left"> Initial Version
 * <tr align="middle"><td> 0.1.2 <td> 20210528 <td align="left"> Added ea_queue for multi-thread support
 * <tr align="middle"><td> 0.1.3 <td> 20210922 <td align="left"> Added ea_display_stream_areas and ea_warp_*
 * <tr align="middle"><td> 0.1.4 <td> 20211203 <td align="left"> Modified ea_net, ea_tensor, let stream area buffer align to 128
 * <tr align="middle"><td> 0.1.5 <td> 20211228 <td align="left"> Added canvas manual feed, and ext memory support
 * <tr align="middle"><td> 0.1.6 <td> 20220516 <td align="left"> Added automatically generation for image color table on stream overlay
 * <tr align="middle"><td> 0.1.7 <td> 20220722 <td align="left"> Added drawing DSP blur and overlay on the same stream
 * <tr align="middle"><td rowspan="5"> 0.2.0 <td rowspan="5"> 20220824
 * <tr><td align="left"> Refined all the document to support x86 simulator and Unit Test
 * <tr><td align="left"> Added support for x86 simulator in @ref eazyai_simulator
 * <tr><td align="left"> Added support for EazyAI Arm postprocess in @ref eazyai_arm_postprocess
 * <tr><td align="left"> Added EazyaAI unit test in @ref eazyai_unit_test_cvflow and @ref eazyai_unit_test_simulator
 * <tr align="middle"><td rowspan="5"> 0.5.0 <td rowspan="5"> 20221230
 * <tr><td align="left"> Separate EazyAI library to Core, Utils, Communication, and Simulator, and declare Core library to MP level, @ref eazyai_introduction
 * <tr><td align="left"> Added EazyAI OSD modules in Core library which for OSD display in VOUT and Stream, @ref eazyai_cvflow_core_osd
 * <tr><td align="left"> Added some new APIs in @ref eazyai_introduction_api_new
 * <tr><td align="left"> Added compatibility violation declaration in @ref eazyai_introduction_api_break
 * <tr align="middle"><td rowspan="13"> 0.5.1 <td rowspan="13"> 20230518
 * <tr><td align="left"> Added support for CV72 and Declare module licenses in @ref eazyai_introduction
 * <tr><td align="left"> Used OpenCV 4.5.1 for Utils library in @ref eazyai_cvflow_utils
 * <tr><td align="left"> Added API Core test in @ref eazyai_core_api_test
 * <tr><td align="left"> Added some new APIs in @ref eazyai_introduction_api_new
 * <tr><td align="left"> Added compatibility violation declaration in @ref eazyai_introduction_api_break
 * <tr><td align="left"> Refined command lines for @ref eazyai_unit_test_cvflow_usage
 * <tr><td align="left"> Refined command lines for @ref eazyai_arm_postprocess
 * <tr><td align="left"> Added support for Soft-NMS in @ref eazyai_cvflow_sub_utils.
 * <tr><td align="left"> Delete the option `class_num` of `test_eazyai` in @ref eazyai_unit_test_cvflow_usage
 * <tr><td align="left"> Used default OpenCV version in system for PC Simulator in @ref eazyai_simulator_build_compile
 * <tr><td align="left"> Updated `test_eazyai` usage in @ref eazyai_unit_test_cvflow_usage
 * <tr><td align="left"> Added EazyAI display unit test in @ref eazyai_display_unit_test_cvflow
 * <tr align="middle"><td rowspan="3"> 0.5.2 <td rowspan="3"> 20230728
 * <tr><td align="left"> Updated simulator in @ref eazyai_simulator_build_compile
 * <tr><td align="left"> Updated simulator unit test in @ref eazyai_unit_test_simulator_usage
 * <tr align="middle"><td rowspan="3"> 0.5.4 <td rowspan="3"> 20230928
 * <tr><td align="left"> Updated `test_eazyai` usage in @ref eazyai_unit_test_cvflow_usage
 * <tr><td align="left"> Updated @ref eazyai_introduction_api_break
 * <tr align="middle"><td rowspan="2"> 0.5.6 <td rowspan="2"> 20231130
 * <tr><td align="left"> Added broken flag in `ea_img_resource_data_t` and update @ref eazyai_introduction_api_new
 * <tr align="middle"><td rowspan="14"> 0.6.0 <td rowspan="14"> 20231228
 * <tr><td align="left"> Updated overview image in @ref eazyai_introduction_overview
 * <tr><td align="left"> Added section @ref eazyai_introduction_cvflow_traditional_accl
 * <tr><td align="left"> Updated section @ref eazyai_introduction_unit_test
 * <tr><td align="left"> Updated section @ref eazyai_introduction_folder_structure
 * <tr><td align="left"> Updated section @ref eazyai_introduction_api_new
 * <tr><td align="left"> Updated section @ref eazyai_introduction_api_break
 * <tr><td align="left"> Added EazyAI utility of ORB extractor in @ref eazyai_cvflow_sub_orb_extractor
 * <tr><td align="left"> Added EazyAI utility of topic in @ref eazyai_cvflow_sub_topic
 * <tr><td align="left"> Added EazyAI communication of socket in @ref eazyai_cvflow_comm_socket
 * <tr><td align="left"> Added EazyAI acceleration library in @ref eazyai_cvflow_accl
 * <tr><td align="left"> Updated the unit test in @ref eazyai_unit_test
 * <tr><td align="left"> Added EazyAI ORB extractor unit test in @ref eazyai_orb_extractor_unit_test
 * <tr><td align="left"> Added EazyAI topic unit test in @ref eazyai_topic_unit_test
 * </table>
 *
 * - - - -
 *
 * @section eazyai_introduction 1 Introduction
 * EazyAI is an easy framework for network debugging and deployment, simulations, file mode tests, and live demos.
 *
 * Since version 0.5.0, EazyAI has been extended to the following different libraries.
 *
 * <table>
 * <caption id="eazyai_modules_introduction"></caption>
 * <tr align="middle"><th> EazyAI Module Name <th> Library SO Name <th> Library Version <th> Ambarella License <th> Features
 * <tr align="middle"><td rowspan="7"> Core <td rowspan="7"> libeazyai.so <td rowspan="7"> v0.6.0 <td rowspan="7"> **MP** Level License
 * <td align="left"> @ref eazyai_cvflow_core_env functions initialize the necessary device environment
 * <tr><td align="left"> @ref eazyai_cvflow_core_tensor functions provide interfaces for the tensor, which carries data in the data flow of a CV program
 * <tr><td align="left"> @ref eazyai_cvflow_core_img_resource functions load image type data from RAW binary, JPEG / PNG, DSP Canvas Buffer, Pyramid Buffer, and so on
 * <tr><td align="left"> @ref eazyai_cvflow_core_preprocess functions provide functions to perform image conversion, such as format conversion, resize, crop, and so on
 * <tr><td align="left"> @ref eazyai_cvflow_core_net functions provide functions to forward a network on the CVflow
 * <tr><td align="left"> @ref eazyai_cvflow_core_osd functions provide functions to configure the OSD (VOUT-Display / Stream-Display) buffer
 * <tr><td align="left"> @ref eazyai_cvflow_core_log macros, enumerations and structures provides macros to control the output of log messages of each individual source code file
 * <tr align="middle"><td rowspan="2"> Utils <td rowspan="2"> libeazyai_utils.so <td rowspan="2"> v0.6.0 <td rowspan="2"> **Reference** Level License
 * <td align="left"> @ref eazyai_cvflow_utils_display functions provide functions to draw detection results on the display media
 * <tr><td align="left"> @ref eazyai_cvflow_sub_utils functions provide utilities such as NMS calculation and frames per second (fps) statistics
 * <tr align="middle"><td rowspan="1"> Communication <td rowspan="1"> libeazyai_comm.so <td rowspan="1"> v0.6.0 <td rowspan="1"> **Reference** Level License
 * <td align="left"> @ref eazyai_cvflow_comm functions provide functions to transfer data in multi-threads.
 * <tr align="middle"><td rowspan="1"> Acceleration <td rowspan="1"> libeazyai_accl.so <td rowspan="1"> v0.6.0 <td rowspan="1"> **Reference** Level License
 * <td align="left"> @ref eazyai_cvflow_accl provides hardware acceleration for traditional algorithms like ORB extractor through CVflow primitives and so on.
 * <tr align="middle"><td rowspan="1"> PC Simulator <td rowspan="1"> libeazyai.so <td rowspan="1"> v0.6.0 <td rowspan="1"> **Reference** Level License
 * <td align="left"> @ref eazyai_simulator has similar APIs with above chip modules to allow users to run simulation inference in PC build server.
 * <tr align="middle"><td rowspan="1"> NN PostProcess <td rowspan="1"> libeazyai_arm_postprocess.so <td rowspan="1"> v0.2.0 <td rowspan="1"> **Reference** Level License
 * <td align="left"> @ref eazyai_arm_postprocess functions assembles public network post processing realization on Arm, such as SSD, YOLOV5, and so on.
 * </table>
 *
 * Currently, EazyAI has supported below chips.
 * - <b>CV2x</b> which includes CV2, CV22, CV25, and CV28.
 * - <b>CV5x</b> which includes CV5 and CV52.
 * - <b>CV7x</b> which includes CV72.
 * - <b>CV3x</b> which includes CV3.
 *
 * @subsection eazyai_introduction_overview 1.1 Overview
 *
 * The following is the detailed structure and introduction for EazyAI.
 *
 * @image html eazyai_library_framework.jpg "Figure 1-1. EazyAI Library Framework."
 *
 * - **EazyAI Deployment Library**, which provides the same application programming interfaces (APIs) to support real CVflow chip deployment.
 *   + **Core**, which includes the **MP level** APIs for image resource query, image preprocess, NN inference, and the low level OSD visualize.
 *   + **Communication**, which includes the **Reference level** APIs for queue support of multi threads, data transfer among processes and devices.
 *   + **Utils**, which includes the **Reference level** APIs for some high level smart OSD display APIs which will call the low level OSD visualize in **Core** library,
 *     and some basic tools, such as fps statistics, 8 bit color table generation of images, basic NMS, OpenCV related (Call OpenCV library), and so on.
 *   + **Traditional Acceleration**, which includes the **Reference level** APIs for CVflow hardware acceleration for traditional algorithms
 *     like ORB extractor through CVflow primitives, and so on.
 *   + **NN Postprocess**, which includes **Reference level** public network postprocess codes such as SSD, Yolov5, and more,
 *     enabling users to easily add customized post-processing code into the library,
 *     and some custom draw functions which will call the **NN Deployment** libraries on Chips, or **NN Simulator** library on PC.
 *   + **Simulator**, which includes the **Reference level** APIs for PC accuracy debug with Ades and Acinference in CNNGen toolchain,
 *     actually it includes the whole same APIs in **NN Deployment**.  That means users can use the same APIs for both debugging on the x86 platform and network deployment on chips.
 * - **Unit Test**, which provides a unified demo to run on different networks on Chips or PC, core api test, display test, ORB test, and so on.
 * - **Applications**, which is not showed in figure and includes lots of complex live demo examples with EazyAI APIs, such as multi-networks, and so on.  It only can work on chips.
 *
 * @note
 * The x86 simulator can support only file mode.
 * The EazyAI library can be found in the following two packages:
 * + `ambarella/packages/eazyai` in the Linux software development kit (SDK) package.
 * + `cnngen_sample_package/library/eazyai` in the CVflow CNNGen Sample Package.
 *
 * @note
 * The EazyAI library version may differ between the two packages.
 *
 * @subsection eazyai_introduction_cvflow 1.2 NN CVflow Inference
 *
 * EazyAI CVflow Deployment Libraries provides easy-to-use APIs for running neural networks (NNs) or specific traditional algorithms on Ambarella computer vision (CV) platforms.
 * The library encapsulates low-level modules in the SDK package including the image audio video (IAV) driver, Cavalry_Mem, VPROC, and NNCtrl.
 * Then, it arranges high-level functions with general conceptions in the CV ground, such as image query, preprocess, forward, and visualize.
 * @image html eazyai_overview_cvflow.jpg "Figure 1-2. EazyAI CVflow Overview. (contents in [...] are dependent upon OpenCV.)"
 *
 * @note
 * + Only **Core** library is **MP level** which will not include image decode, postprocess, and smart display in **Utils**, **Comm**, and **ARM Postprocess** libraries.
 * + New module `ea_osd` is more flexible than 'ea_display', but 'ea_display' is easy to use, and **Core** library only includes `ea_osd` support.
 *
 * @subsection eazyai_introduction_simulator 1.3 NN Simulator Inference
 *
 * The EazyAI Simulator library share the same structures and APIs with EazyAI Deployment Libraries.
 * The EazyAI Simulator encapsulates Ambarella directed acyclic graph (DAG) emulator system (ADES) APIs and Acinference APIs to perform forward inference simulations on the x86 Linux platform.
 * - While using the **ADES** API, the simulation inference will possess bit-perfect results with real CVflow chip output.  However, the simulation may be slow.
 * - While using the **Acinference** API, the simulation inference will perform quickly; however, and its result will not be bit perfect with the real CVflow chip, but very close to the CVflow output.
 *
 * @image html eazyai_overview_simulator.jpg "Figure 1-3. EazyAI Simulator Overview."
 *
 * @subsection eazyai_introduction_arm_postprocess 1.4 NN Postprocess
 *
 * The EazyAI NN Postprocess library provides public model postprocess implementations, which mostly works on CPU
 * as there are lots of logical selection.  Users also can easily add customized postprocess to this
 * library by implementing four functions, then register these functions to the EazyAI Arm Postprocess library.
 * For more details, refer to @ref eazyai_arm_postprocess_customize_postprocess.
 *
 * @subsection eazyai_introduction_cvflow_traditional_accl 1.5 Traditional Algorithms Acceleration
 *
 * The EazyAI Traditional Acceleration Algorithms library provides different traditional algorithms APIs which can works on CVflow.
 *
 * @subsection eazyai_introduction_unit_test 1.6 Unit Test
 *
 * EazyAI's main unit test is `test_eazyai`, also there are also some other unit tests,
 * such as display, core test, orb, topic, and so on, please refer to @ref eazyai_unit_test for detail.
 *
 * `test_eazyai` includes the three parts below for NN inference:
 * - Input query and preprocess, which use the EazyAI Core API to query frames from digital signal processor (DSP) buffers or get frames from file input (RAW, JPEG, PNG).
 *   Then, the API converts the frames to the correct network format required by CVflow, DSP, or Arm.
 * - Inference with @ref eazyai_introduction_cvflow and @ref eazyai_introduction_simulator.
 * - Postprocess with @ref eazyai_introduction_arm_postprocess, which implements the non-maximum suppression (NMS) code on Arm to get the final network result, then shows the final result on the video output (VOUT), stream, images, or print information.
 *
 * `test_eazyai` is also a convenient unit test for users to perform x86 simulations, performance tests with file mode, and final live deployments on CVflow chips.
 * This unit test can support most of a single network, and includes three different modes below:
 * - **Dummy mode**, which feeds fixed input data to the network and gets the inference time without postprocess.  Dummy mode only supports CVflow.
 * - **File mode**, which gets input data from RAW binary files, JPEG files, or PNG files and performs preprocess with Arm or CVflow,
 *   then performs inference with or without postprocess.  With postprocess, this mode shows the result on images and can support both CVflow and the simulator.
 * - **Live mode**, which queries frames from the DSP canvas or pyramid buffer, and performs CVflow preprocess and CVflow inference, then shows the result on VOUT or DSP stream.
 *
 * @image html test_eazyai_overview.jpg "Figure 1-6. test_eazyai Overview."
 *
 *
 * @subsection eazyai_introduction_apps 1.7 Application
 * EazyAI applications include some complex demos, such as multiple network, doorbell, and more.
 *
 * @subsection eazyai_introduction_folder_structure 1.8 Folder Structure
 * @code {.c}
 * EazyAI
 *   |------apps 		//source folder of EazyAI Applications
 *   |------unit_test
 *   |      |------accl
 *   |      |      |------test_ea_orb_extractor		// source of EazyAI ORB Test to run ORB Extractor
 *   |      |------comm
 *   |      |      |------test_ea_topic				// source of EazyAI Data Share Test between multiply processes and devices
 *   |      |------api_test
 *   |      |      |------test_api_eazyai_core		// source of EazyAI API Core Test
 *   |      |------test_eazyai_display				// source of EazyAI Display Unit Test to draw OSD on stream and VOUT
 *   |      |------test_eazyai					// source of EazyAI Unit Test
 *   |      |------nn_arm_task						// source folder of EazyAI Arm Postprocess
 *   |      |------eazyai_video						// source of eazyai_video which is used to enable DSP in different platforms
 *   |      |------cnngui							// configuration file of CNNGUI tool
 *   |------src
 *   |      |------core				// source folder of EazyAI Core
 *   |      |------simulator		// source folder of EazyAI Simulator
 *   |      |------utils			// source folder of EazyAI Utility
 *   |      |------comm				// source folder of EazyAI Communication module
 *   |      |------accl				// source folder of EazyAI Acceleration module
 * @endcode
 *
 * @subsection eazyai_introduction_api_new 1.9 API Updates
 * <table>
 * <caption id="lib_eazyai_api_rev_history"></caption>
 * <tr align="middle"><th> Library Version <th> Library Name <th> Module Name <th> API / Structure Name
 *
 * <tr align="middle"><td rowspan="25"> 0.5.0
 * <td rowspan="23"> libeazyai.so <td rowspan="8"> @ref eazyai_cvflow_core_env
 * <tr><td align="left"> int ea_env_enabled_features()
 * <tr><td align="left"> ea_env_arch_t ea_env_arch()
 * <tr><td align="left"> ea_env_properties_t* ea_env_properties()
 * <tr><td align="left"> int ea_env_set_overlay_buffer_offset(unsigned long offset)
 * <tr><td align="left"> unsigned long ea_env_dsp_blur_arbitrary_buffer_size()
 * <tr><td align="left"> int ea_env_set_dsp_blur_arbitrary_buffer_offset(unsigned long offset)
 * <tr><td align="left"> int ea_env_set_callbacks(const ea_env_callbacks_t *callbacks)
 * <tr align="middle"><td rowspan="2"> @ref eazyai_cvflow_core_preprocess
 * <tr><td align="left"> int ea_rotate_flip(ea_tensor_t *src, ea_tensor_t *dst, unsigned int flip_bitmap, ea_tensor_color_mode_t color_mode, ea_device_t device)
 * <tr align="middle"><td rowspan="11"> @ref eazyai_cvflow_core_tensor
 * <tr><td align="left"> `enum ea_data_type_e`
 * <tr><td align="left"> ea_tensor_new_from_vect_desc(ea_memory_t mem_type, const vect_desc_t *desc, void *virt)
 * <tr><td align="left"> ea_tensor_new_from_other_buffer(ea_memory_t mem_type, int iav_buf_pid, ea_data_type_t dtype, const size_t *shape, size_t pitch, void *virt, unsigned long phys)
 * <tr><td align="left"> int ea_tensor_vect_desc(const ea_tensor_t *tensor, vect_desc_t *desc)
 * <tr><td align="left"> ea_tensor_data_for_read(ea_tensor_t *tensor, ea_device_t device)
 * <tr><td align="left"> ea_tensor_data_for_write(ea_tensor_t *tensor, ea_device_t device)
 * <tr><td align="left"> unsigned long ea_tensor_phys_for_read(ea_tensor_t *tensor, ea_device_t device)
 * <tr><td align="left"> unsigned long ea_tensor_phys_for_write(ea_tensor_t *tensor, ea_device_t device)
 * <tr><td align="left"> ea_tensor_new_from_image(const char *path)
 * <tr><td align="left"> int ea_tensor_to_image(ea_tensor_t *tensor, ea_tensor_color_mode_t color_mode, const char *path)
 * <tr align="middle"><td rowspan="2"> @ref eazyai_cvflow_core_osd
 * <tr><td align="left"> Add support for this module first time
 * <tr align="middle"><td rowspan="2"> libeazyai_utils.so <td rowspan="2"> @ref eazyai_cvflow_sub_utils
 * <tr><td align="left"> int ea_utils_env_callbacks_register()
 *
 * <tr align="middle"><td rowspan="13"> 0.5.1
 * <td rowspan="11"> libeazyai.so <td rowspan="2"> @ref eazyai_cvflow_core_tensor
 * <tr><td align="left"> ea_tensor_t* ea_tensor_new_from_other_roi()
 * <tr align="middle"><td rowspan="2"> @ref eazyai_cvflow_core_img_resource
 * <tr><td align="left"> Add support for custom data format of RAW binary input and NV12 input
 * <tr align="middle"><td rowspan="2"> @ref eazyai_cvflow_core_preprocess
 * <tr><td align="left"> Add support for small ROI crop from size>4096 RGB/BGR/GRAYSCALE images.
 * <tr align="middle"><td rowspan="2"> @ref eazyai_cvflow_core_net
 * <tr><td align="left"> Add support for updating (0,0,8,0) input for (0,0,0,0) tensor automatically with 256 scaling only
 * <tr align="middle"><td rowspan="3"> @ref eazyai_cvflow_core_osd
 * <tr><td align="left"> Add support for dynamic ROI of areas
 * <tr><td align="left"> Add support for circular buffer size configuration.
 * <tr align="middle"><td rowspan="2"> libeazyai_utils.so <td rowspan="2"> @ref eazyai_cvflow_sub_utils
 * <tr><td align="left"> int ea_soft_nms()
 *
 * <tr align="middle"><td rowspan="2"> 0.5.6
 * <td rowspan="2"> libeazyai.so <td rowspan="2"> @ref eazyai_cvflow_core_img_resource
 * <tr><td align="left"> Add support for frame broken flag
 *
 * <tr align="middle"><td rowspan="15"> 0.6.0
 * <td rowspan="8"> libeazyai.so <td rowspan="3"> @ref eazyai_cvflow_core_tensor
 * <tr><td align="left"> Updated ea_tensor_new_from_other_roi() to support multi channels when full FOV is in ROI.
 * <tr><td align="left"> Updated ea_tensor_new_from_other_buffer() to let it get virt or phys with `cavalry_mem_phys_to_virt()` and `cavalry_mem_virt_to_phys()` API.
 * <tr align="middle"><td rowspan="3"> @ref eazyai_cvflow_core_net
 * <tr><td align="left"> Added ea_net_config_output_ext() to support network like video_matting on CV72.
 * <tr><td align="left"> Added `nvp_affinity` in `ea_net_params_t` to support NVP affinity configuration on CV3 and CV7x.
 * <tr align="middle"><td rowspan="2"> @ref eazyai_cvflow_core_env
 * <tr><td align="left"> Added ea_env_set_vproc_tid_attr() to wrap VPROC's API to support thread priority, and NVP&GVP affinity configuration for `ea_preprocess` module which uses VPROC API.
 * <tr align="middle"> <td rowspan="2"> libeazyai_accl.so <td rowspan="2"> @ref eazyai_cvflow_accl
 * <tr><td align="left"> Added acceleration library with FAST corner detection `ea_fast`, ORB angle orientation calculation `ea_angle`, and BRIEF descriptor calculation `ea_brief`.
 * <tr align="middle"> <td rowspan="2"> libeazyai_comm.so <td rowspan="2"> @ref eazyai_cvflow_comm_socket
 * <tr><td align="left"> Added `ea_socket` module in communication library.
 * <tr align="middle"> <td rowspan="3"> libeazyai_utils.so <td rowspan="3"> @ref eazyai_cvflow_utils
 * <tr><td align="left"> Added `ea_topic` module in utils library.
 * <tr><td align="left"> Added `ea_orb_extractor` module in utils library.
 * </table>
 *
 * @note
 * **Deployment** libraries and **Simulator** library share the same API, also share the same API updates.
 *
 * @subsection eazyai_introduction_api_break 2.0 API Compatibility Violation
 *
 * Since version **0.5.0**, EazyAI is separated to three libraries, and **Core** library is declared for MP level.  Then there will be API compatibility violation as follows.
 *
 * **Core v0.5.0** Library
 * + `EA_ENV_ENABLE_OSD_JPEG` is removed, users need to call `ea_utils_env_callbacks_register()` for JPEG file mode in the application.
 * + `ea_net_show_nn_bin_version()` adds ea_net as a new input parameter.
 *
 * **Utils v0.5.0** Library
 * + `EA_DISPLAY_STREAM_DSP_BLUR` is removed, use `EA_DISPLAY_STREAM` instead.
 * + `EA_DISPLAY_STREAM_AREAS` is removed, use `EA_DISPLAY_STREAM` or use `ea_osd()` to implement directly.
 * + Rotation is removed this time which will not rotate overlay content adapted to stream rotation.
 * + Some parameters are being changed for `ea_display_obj_params_t` in `ea_display.h`.
 *   - Deprecated Parameters
 *     1. `int transparent_color`, which does nothing with this parameter.
 *     2. `const char *char_set`, which is fixed with defined Macro in library.
 *   - New Parameters
 *     1. `int draw_with_opencv`, which select OpenCV to draw shapes. Default is 0.
 * + Some APIs are renamed in `eazyai_utils.h`.
 *     1. Rename `ea_display_efm_frame_t` to `ea_osd_refresh_efm_params_t` with same structure.
 *     2. `ea_color_table_image_t *ea_color_table_image_create(const char *path, int width, int height, int start_index, int color_num)`
 *     3. `void ea_color_table_image_free(ea_color_table_image_t *color_table_image)`
 *     4. `uint8_t *ea_color_table_image_rgb_color_table(ea_color_table_image_t *color_table_image)`
 *     5. `uint8_t *ea_color_table_image_pixel_data(ea_color_table_image_t *color_table_image)`
 *     6. `int ea_color_table_image_width(ea_color_table_image_t *color_table_image)`
 *     7. `int ea_color_table_image_height(ea_color_table_image_t *color_table_image)`
 *
 * **Core v0.5.1** Library
 * + Move @ref eazyai_cvflow_core_log APIs to Core library.
 * + `ea_net_type_t` is removed as not used.
 * + Rename `ea_osd_area_location_t` to `ea_osd_roi_t`.
 * + Add ROI parameters in `ea_osd_area_current_buffer()`.
 * + Refine return value to int for `ea_net_config_input()` and `ea_net_config_output()`.
 * **Utils** Library
 * + `EA_DISPLAY_STREAM_DSP_BLUR` is removed, use `EA_DISPLAY_STREAM` instead.
 *
 * **Core v0.5.4** Library
 * + Remove vproc_image_deformation() for Cavalry V3 in @ref ea_cvt_color_resize APIs.
 *
 * @note
 * **Deployment** libraries and **Simulator** library share the same API, also share the same API compatibility violation.
 *
 * - - - -
 *
 * @section eazyai_cvflow 2 EazyAI Deployment
 * @subsection eazyai_cvflow_build 2.1 Build
 * @subsubsection eazyai_cvflow_build_include 2.1.1 Include
 * For each source file that uses the API in the EazyAI library, the following include file is required.
 * @code
 * #include <eazyai.h>
 * @endcode
 * @subsubsection eazyai_cvflow_build_makefile 2.1.2 Makefile
 * There are several link targets on the EazyAI library: `libeazyai.so`, `libeazyai_comm.so`, `libeazyai_accl.so`, and `libeazyai_utils.so`.
 *
 * The `libeazyai.so` is the library for core functions mainly including **IAV**, **NNCTRL**, **VPROC**.
 *
 * The `libeazyai_comm.so` is the library for thread, process and device communication.
 *
 * The `libeazyai_accl.so` is the library for accelerating traditional algorithms.
 *
 * The `libeazyai_utils.so` is the library for utilities, including drawing various shapes on a given buffer, etc.
 * It has dependency of the OpenCV library and of the `libeazyai.so`.  For example,
 * the `ea_display` module in the `libeazyai_utils.so` calls the `ea_osd` module in the
 * the `libeazyai.so` to update the overlay buffer or frame buffer.
 *
 * For the applications that do not use `acceleration`, `ea_utils` or `ea_display` functions,
 * the following content is used in the SDK makefile.
 * @code
 * LOCAL_CFLAGS 	+= -I$(AMB_TOPDIR)/packages/eazyai/inc
 * LOCAL_LIBS   	:=  libeazyai.so
 * LOCAL_LDFLAGS	+= -Wl,-rpath-link=$(FAKEROOT_DIR)/usr/lib
 * @endcode
 *
 * For the applications that use `acceleration` functions,
 * the following content is used in the SDK makefile.
 * @code
 * LOCAL_CFLAGS 	+= -I$(AMB_TOPDIR)/packages/eazyai/inc
 * LOCAL_LIBS   	:=  libeazyai.so libeazyai_accl.so
 * LOCAL_LDFLAGS	+= -Wl,-rpath-link=$(FAKEROOT_DIR)/usr/lib
 * @endcode
 *
 * For the applications that use `acceleration`, `ea_utils` or `ea_display` functions,
 * the following content can be used in the SDK makefile.
 * @code
 * LOCAL_CFLAGS 	+= -I$(AMB_TOPDIR)/packages/eazyai/inc
 * LOCAL_LIBS   	:=  libeazyai.so
 * LOCAL_LDFLAGS	+= -Wl,-rpath-link=$(FAKEROOT_DIR)/usr/lib
 * ifeq ($(BUILD_AMBARELLA_EAZYAI_UTILS_PACKAGE), y)
 * LOCAL_LIBS		+= libeazyai_accl.so libeazyai_utils.so
 * LOCAL_LDFLAGS	+=  -Wl,-rpath-link=$(PREBUILD_OSS_DIR)/freetype/usr/lib
 * 	-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/opencv/usr/lib \
 * 	-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libjpeg-turbo/usr/lib \
 * 	-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/libpng/usr/lib \
 * 	-Wl,-rpath-link=$(PREBUILD_OSS_DIR)/zlib/usr/lib
 * endif
 * @endcode
 *
 * @subsubsection eazyai_cvflow_build_configuration 2.1.3 Configuration
 * To use the EazyAI library in the SDK, there are two ways to select the library in configuration.
 * 1. Manually select EazyAI in `make menuconfig`.
 * The OpenCV support will be selected if `BUILD_AMBARELLA_EAZYAI_UTILS_PACKAGE` is selected.
 *
 *  - For CV2x SDK 3.0 Amba build:
 *  @code
 *  build $ make menuconfig
 *     [*] Ambarella Package Configuration --->
 *         [*] Build Ambarella EAZYAI library --->
 *             [*] Build eazyai core library
 *             [*] Build eazyai utilities library
 *             [*] Build eazyai communication library
 *             [*] Build eazyai acceleration library
 *  @endcode
 *  - For Cooper Amba build:
 *  @code {.c}
 *  build $ make menuconfig
 *     packages  --->
 *         eazyai  --->
 *              [*] libeazyai (packages/eazyai/lib_amba_mk)
 *              [*] libeazyai-comm (packages/eazyai/lib_amba_mk)
 *              [*] libeazyai-accl (packages/eazyai/lib_amba_mk)
 *              [*] libeazyai-utils (packages/eazyai/lib_amba_mk)
 *  @endcode
 *  - For Cooper Yocto build:
 *  @code {.c}
 *  build $ make menuconfig
 *     meta-ambalib  --->
 *         recipes-eazyai  --->
 *              [*] libeazyai (meta-ambalib/recipes-eazyai/libeazyai)
 *  @endcode
 * 2. Select in AmbaConfig file.
 * @code
 * select BUILD_AMBARELLA_EAZYAI_PACKAGE
 * select BUILD_AMBARELLA_EAZYAI_CORE_PACKAGE
 * select BUILD_AMBARELLA_EAZYAI_UTILS_PACKAGE
 * select BUILD_AMBARELLA_EAZYAI_COMM_PACKAGE
 * select BUILD_AMBARELLA_EAZYAI_ACCL_PACKAGE
 * @endcode
 *
 * - - - -
 *
 * @subsection eazyai_cvflow_core 2.2 Core Library
 * @subsubsection eazyai_cvflow_core_env 2.2.1 Core Library - ea_env
 * @ref eazyai-env-details initialize the necessary environment to use the CV features.
 * ::ea_env_open() should be called before the other APIs in EazyAI are called.
 * ::ea_env_close() should be called after the other APIs in EazyAI are called.
 * @code {.c}
 * int features;
 * features = EA_ENV_ENABLE_IAV
 *     | EA_ENV_ENABLE_CAVALRY
 *     | EA_ENV_ENABLE_VPROC
 *     | EA_ENV_ENABLE_NNCTRL
 *     | EA_ENV_ENABLE_OSD_STREAM; // EA_ENV_ENABLE_OSD_STREAM is for displaying on stream.
 *                                 // It can be replaced with EA_ENV_ENABLE_OSD_VOUT.
 * rval = ea_env_open(features);
 * // ...
 * ea_env_close();
 * @endcode
 *
 * @note
 * + `EA_ENV_ENABLE_OSD_JPEG` is deleted in `ea_env()` as it is related with OpenCV in **Core** library since version 0.5.0,
 * but users can enable it with calling ea_utils_env_callbacks_register() in **Utils** library which will enable OpenCV together.
 * + Only when ea_utils_env_callbacks_register() is called, users can use `EA_JPEG_FOLDER` in Preprocessing modules.
 *
 * @subsubsection eazyai_cvflow_core_tensor 2.2.2 Core Library - ea_tensor
 * @ref eazyai-tensor-details provide interfaces for the tensor, which carries data in the data flow of a CV program.
 * The tensor is a four-dimensional array with a shape in NxCxHxW order.
 * When a tensor holds data shared between the CPU, vector processor (VP - CVflow), and DSP, it is necessary for the CVflow and DSP to know the physical address of the data.
 * When creating a tensor, the memory is not allocated from a heap,
 * but allocated by the interface provided by the Cavalry_Mem library or by the IAV driver.
 * - ::EA_MEM_CAVALRY
 *
 *     This is the type of memory allocated with the Cavalry_Mem library for common use.
 * The tensor created by ::ea_tensor_new() or ::ea_tensor_new_from_file() uses this type of memory.
 * - ::EA_MEM_IAV_ANON
 *
 *     This is the type of memory allocated with the IAV driver in the IAV anonymous partition
 * for special use with the IAV image scaler function.
 * The tensor created by ::ea_tensor_new_from_iav_anon_mem() uses this type of memory.
 * The created tensor will be used as the parameter of ::ea_crop_resize() when @a device = ::EA_DSP.
 * - ::EA_MEM_IAV_DSP
 *
 *     This is the type of memory allocated with the IAV driver in the IAV DSP partition.
 * The interface to create a tensor with this type of memory is not opened,
 * but the tensor output by ::ea_img_resource_hold_data() uses this type of memory
 * when @a ea_img_resource_t is of type ::EA_CANVAS or ::EA_PYRAMID.
 *
 * - ::EA_MEM_HEAP
 *   This is the type of memory allocated with malloc for common use.
 *   The tensor created by ::ea_tensor_new() or ::ea_tensor_new_from_file() uses this type of memory.
 *
 * @subsubsection eazyai_cvflow_core_img_resource 2.2.3 Core Library - ea_img_resource
 * @ref eazyai-img-resource-details load image data in a format of ::ea_tensor_color_mode_e from cameras (::EA_CANVAS and ::EA_PYRAMID),
 * RAW binary files (::EA_RAW_FILE or ::EA_RAW_FILE_FOLDER), or JPEG files (::EA_JPEG_FOLDER).
 * A new group of image data is loaded by every call of ::ea_img_resource_hold_data().
 * ::ea_img_resource_drop_data() should be called the same number of times as ::ea_img_resource_hold_data() to release the internal buffers.
 * Usually, the image data from the camera (IAV driver) has the format of ::EA_TENSOR_COLOR_MODE_YUV_NV12;
 * the image data from a JPEG file has the format of ::EA_TENSOR_COLOR_MODE_BGR.
 * If the YUV NV12 data is from the camera (IAV driver), the Y data and the UV data are stored discontiguously in the memory.
 * Two tensors will be used to hold the image data.
 * The Y data is stored in a tensor returned by ::ea_img_resource_hold_data() and
 * the UV data is stored in the tensor returned by ::ea_tensor_related().
 * 1. ::EA_CANVAS
 *
 *     This type of image resource is created by a canvas ID. It outputs image data generated by the IAV driver in the canvas buffer.
 * A frame of YUV data in the canvas buffer is updated once at a time by ::ea_img_resource_hold_data().
 * The image data is stored in ::ea_img_resource_data_s::tensor_group.
 * There may be more than one YUV buffer in each frame,
 * so the array of the tensor pointer is used and the number is returned by ::ea_img_resource_data_s::tensor_num.
 * ea_img_resource_data_s::tensor_group[0] represents the YUV image in the canvas buffer.
 * ea_img_resource_data_s::tensor_group[1] represents the image data in the ME0 buffer.
 * If the canvas is configured as prev type, it may be NULL.
 * ea_img_resource_data_s::tensor_group[2] represents the image data in the ME1 buffer.
 * If the canvas is configured as prev type, it may be NULL.
 * @code {.c}
 * ea_img_resource_t *img_resource;
 * int canvas_id = 0;
 * // ...
 * img_resource = ea_img_resource_new(EA_CANVAS, (void *)(unsigned long)canvas_id);
 * // ...
 * ea_img_resource_free(img_resource);
 * @endcode
 * @code {.c}
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_img_resource_drop_data(img_resource, &data);
 * @endcode
 *
 * 2. ::EA_PYRAMID
 *
 *     This type of image resource is created by a channel ID.  It outputs image data generated by the IAV driver into the pyramid buffer.
 * The frames of YUV data in the channel pyramid buffer are updated once a time by ::ea_img_resource_hold_data().
 * The image data is stored in ::ea_img_resource_data_s::tensor_group.
 * There are six layers in pyramid buffer, and each layer has a YUV buffer, meaning that there are six YUV buffers in each frame of the image data.
 * The array of the tensor pointer is used and the fixed number 6 is returned by ::ea_img_resource_data_s::tensor_num.
 * ea_img_resource_data_s::tensor_group[N] represents the YUV image on the Nth layer. It will be NULL if the layer is disabled.
 * @code {.c}
 * ea_img_resource_t *img_resource;
 * int channel_id = 0;
 * // ...
 * img_resource = ea_img_resource_new(EA_PYRAMID, (void *)(unsigned long)channel_id);
 * // ...
 * ea_img_resource_free(img_resource);
 * @endcode
 * @code {.c}
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_img_resource_drop_data(img_resource, &data);
 * @endcode
 *
 * 3. ::EA_RAW_FILE
 *
 *     This type of image resource is created by a file path for reading one RAW binary file
 * with a name in the format [N]x[C]x[H]x[W]_*.bin; for example, `1x3x480x640_dog.bin`.
 * @code {.c}
 * ea_img_resource_t *img_resource;
 * char *file_path = "/sdcard/mtcnn/in/1x3x480x640_face01.bin";
 * img_resource = ea_img_resource_new(EA_RAW_FILE, file_path);
 * // ...
 * ea_img_resource_free(img_resource);
 * @endcode
 * @code {.c}
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_img_resource_drop_data(img_resource, &data);
 * @endcode
 *
 * 4. ::EA_RAW_FILE_FOLDER
 *
 *     This type of image resource is created by a folder path for reading each RAW binary file
 * under the folder with a name in the format [N]x[C]x[H]x[W]_*.bin; for example, `1x3x480x640_dog.bin`.
 * The data in every file will be returned by each call of ::ea_img_resource_hold_data().
 * The reading order is decided by the Linux API @e readdir().
 * @code {.c}
 * ea_img_resource_t *img_resource;
 * char *folder_path = "/sdcard/mtcnn/in/";
 * img_resource = ea_img_resource_new(EA_RAW_FILE_FOLDER, folder_path);
 * // ...
 * ea_img_resource_free(img_resource);
 * @endcode
 * @code {.c}
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_img_resource_drop_data(img_resource, &data);
 * @endcode
 *
 * 5. ::EA_JPEG_FOLDER
 *
 *     This type of image resource is created by a folder path for reading each *.jpg file under the folder.
 * The data in every file will be returned by each call of ::ea_img_resource_hold_data().
 * The reading order is decided by the Linux API @e readdir().
 * @code {.c}
 * ea_img_resource_t *img_resource;
 * char *folder_path = "/sdcard/mtcnn/in/";
 * img_resource = ea_img_resource_new(EA_JPEG_FOLDER, folder_path);
 * // ...
 * ea_img_resource_free(img_resource);
 * @endcode
 * @code {.c}
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_img_resource_drop_data(img_resource, &data);
 * @endcode
 *
 * @subsubsection eazyai_cvflow_core_preprocess 2.2.4 Core Library - ea_preprocess
 * @ref eazyai-preprocess-details provide functions to perform image color conversion, resize, and crop.
 * The process can be performed by VP - CVflow, DSP, or CPU devices.
 * There are limitations on each kind of device. Refer to @ref eazyai-preprocess-details for the limitations.
 * 1. Color convert
 *
 *     Resize will be performed if the source size and the destination size are different.
 *     - YUV NV12 to RGB or BGR
 * @code {.c}
 * ea_img_resource_data_t data;
 * size_t shape[] = {1, 3, 300, 300};
 * ea_tensor_t *rgb_tensor = ea_tensor_new(EA_U8, shape, 0);
 * ea_tensor_t *bgr_tensor = ea_tensor_new(EA_U8, shape, 0);
 * // ...
 * ea_cvt_color_resize(data.tensor_group[0], rbg_tensor, EA_COLOR_YUV2RGB_NV12, EA_VP);
 * ea_cvt_color_resize(data.tensor_group[0], bgr_tensor, EA_COLOR_YUV2BGR_NV12, EA_VP);
 * // ...
 * ea_tensor_free(rgb_tensor);
 * ea_tensor_free(bgr_tensor);
 * @endcode
 *     - RBG to BGR or BGR to RGB
 * @code {.c}
 * ea_cvt_color_resize(rbg_tensor, bgr_tensor, EA_COLOR_RGB2BGR, EA_VP);
 * ea_cvt_color_resize(bgr_tensor, rbg_tensor, EA_COLOR_BGR2RGB, EA_VP);
 * @endcode
 *     - Transpose to / from OpenCV Mat format
 *
 *         A color image in an OpenCV Mat is stored in HxWx3 format.  If padding is used, the format will be Hx(W*3+padding).
 * @code {.c}
 * size_t shape[] = {1, 1, 300, 300 * 3};
 * ea_tensor_t *mat_tensor = ea_tensor_new(EA_U8, shape, 0);
 * // ...
 * ea_cvt_color_resize(bgr_tensor, mat_tensor, EA_COLOR_TRANSPOSE, EA_VP);
 * ea_tensor_sync_cache(mat_tensor, EA_VP, EA_CPU);
 * cv::Mat bgr(300, 300, CV_8UC3, ea_tensor_data(mat_tensor, EA_CPU), ea_tensor_pitch(mat_tensor));
 * // ...
 * ea_tensor_free(bgr_tensor);
 * @endcode
 * @code {.c}
 * size_t shape_1[] = {1, 1, 300, 300 * 3};
 * ea_tensor_t *mat_tensor = ea_tensor_new(EA_U8, shape, 0);
 * cv::Mat bgr(300, 300, CV_8UC3, ea_tensor_data(mat_tensor), ea_tensor_pitch(mat_tensor));
 * // ...
 * size_t shape_2[] = {1, 3, 300, 300};
 * ea_tensor_t *bgr_tensor = ea_tensor_new(EA_U8, shape, 0);
 * // ...
 * ea_tensor_sync_cache(mat_tensor, EA_CPU, EA_VP);
 * ea_cvt_color_resize(mat_tensor, bgr_tensor, EA_COLOR_TRANSPOSE, EA_VP);
 * // ...
 * ea_tensor_free(mat_tensor);
 * ea_tensor_free(bgr_tensor);
 * @endcode
 * 2. Crop
 *
 *     Resize will be performed if the source size and the destination size are different.
 *     - Crop YUV NV12 from the IAV driver
 *
 *         When @a device = ::EA_DSP is used, only cropping YUV data from the IAV driver is supported.
 * The destination tensor is created by ::ea_tensor_new_from_iav_anon_mem().  Otherwise, ::EA_VP can be used.
 * @code {.c}
 * size_t shape[] = {1, 1, 224, 224};
 * ea_tensor_t *scale_tensor = ea_tensor_new_from_iav_anon_mem(shape);
 * ea_crop_resize(&data.tensor_group[0], 1, &scale_tensor, 1, NULL, EA_TENSOR_COLOR_MODE_YUV_NV12, EA_DSP);
 * @endcode
 *     - Batch crop
 *
 *         The batch is decided by @a dst and @a dst_num in ::ea_crop_resize(),
 * which is the accumulation of N in the shape of each @a dst tensor.
 * @code {.c}
 * ea_tensor_t *src_tensor;
 * int batch_num;
 * // ...
 * ea_roi_t *roi_group;
 * roi_group = (ea_roi_t *)malloc(sizeof(ea_roi_t) * batch_num);
 * memset(roi_group, 0, sizeof(ea_roi_t) * batch_num);
 *
 * for (i = 0; i < batch_num; i++) {
 *     roi_group[i].x = detections[i].x_start;
 *     roi_group[i].y = detections[i].y_start;
 *     roi_group[i].w = detections[i].x_end - detections[i].x_start;
 *     roi_group[i].h = detections[i].y_end - detections[i].y_start;
 * }
 *
 * size_t shape[4] = {1, 3, 112, 96};
 * shape[0] = batch_num;
 * ea_tensor_t *resize_dst = ea_tensor_new(EA_U8, shape, 0);
 * ea_crop_resize(&src_tensor, 1, &resize_dst, 1, roi_group, EA_VP);
 * // ...
 * free(roi_group);
 * ea_tensor_free(resize_dst);
 * @endcode
 *
 * @subsubsection eazyai_cvflow_core_net 2.2.5 Core Library - ea_net
 * @ref eazyai-net-details provide functions to forward a network on the CVflow.
 * The network model and pretrained weights are packaged in the cavalry binary format.
 * It can be load from a file or from a dynamic random-access memory (DRAM) buffer.
 * The tensors, which hold the network input / output buffers, can be fetched by ::ea_net_input()/::ea_net_output().
 * The input tensors can be used to accept the input data, for example, as the @a dst in ::ea_cvt_color_resize().
 * The output tensors can be used to read the inference result.  Before reading the inference result,
 * the CPU cache should be invalidated by ::ea_tensor_sync_cache().
 * 1. Load the model from the file.
 * @code {.c}
 * char *model_path = "/sdcard/network_cavalry.bin"
 * ea_net_t *net = ea_net_new(NULL);
 * ea_net_config_input(net, "input");
 * ea_net_config_output(net, "output");
 * ea_net_load(net, EA_NET_LOAD_FILE, (void *)model_path, 1);
 * input_tensor = ea_net_input(net, "input");
 * output_tensor = ea_net_output(net, "output");
 * @endcode
 * 2. Load the model from DRAM.
 * @code {.c}
 * uint8_t *model_buffer = (uint8_t *)malloc(MODEL_SIZE);
 * // ...
 * ea_net_t *net = ea_net_new(NULL);
 * ea_net_config_input(net, "input");
 * ea_net_config_output(net, "output");
 * ea_net_load(net, EA_NET_LOAD_DRAM, (void *)model_buffer, 1);
 * input_tensor = ea_net_input(net, "input");
 * output_tensor = ea_net_output(net, "output");
 * @endcode
 * 3. Forward.
 * @code
 * ea_cvt_color_resize(img_tensors[0], input_tensor, EA_COLOR_YUV2RGB_NV12, EA_VP);
 * // no need to sync cache, because data is updated by VP and will be read by VP too.
 * ea_net_forward(net, 1);
 * @endcode
 * 4. Read the inference result.
 * @code
 * ea_tensor_sync_cache(output_tensor, EA_VP, EA_CPU);
 * bbox_addr = (float *)ea_tensor_data(output_tensor);
 * @endcode
 *
 * @subsubsection eazyai_cvflow_core_osd 2.2.6 Core Library - ea_osd
 * @ref eazyai-osd-details provide functions to configure the OSD (VOUT-Display / Stream-Display) buffer.
 * 1. Setup OSD
 *     - For VOUT, users can use different frame_buffer_id to decide
 * the device to show this OSD, including HDMI, CVBS, LCD, etc.
 * @code {.c}
 * ea_osd_t *osd = ea_osd_new(EA_OSD_VOUT, frame_buffer_id, NULL);
 * @endcode
 *     - For stream, it's different from the VOUT.  It has a `stream_params`
 * to describe the stream configuration, including the required overlay area numbers,
 * the location of each overlay area, the required blur area numbers, etc.
 * @code {.c}
 * ea_osd_t *osd = ea_osd_new(EA_OSD_STREAM, stream_id, stream_params);
 * @endcode
 * 2. Set CLUT (Color Look Up Table)
 *
 *     - Users can use the below APIs to set the CLUT for each area:
 * @code {.c}
 * ea_osd_area_set_color_table_rgba(osd, local_area_id, rgb_color_table, color_num)
 * ea_osd_area_set_color_table_yuva(osd, local_area_id, yuva_color_table, color_num)
 * ea_osd_area_set_default_16_color_table(osd, local_area_id)
 * @endcode
 * 3. Draw
 *     - Get area buffer to write.
 * Before drawing shapes on the OSD,
 * users need to get the area buffer.  The area buffer is mapped
 * from the overlay buffer(for the stream case) or is mapped from
 * the framebuffer(for the VOUT case).  Users can add various OSD shapes
 * by modifying this buffer.  The `local_area_id` of an area need
 * to be managed by users.  If the local_area_id is smaller than
 * the `overlay_area_number` specified in the calling of `ea_osd_new`,
 * then the returned area buffer is an overlay area buffer.
 * The arbitrary blur will be supported in the future release.
 * The number of the arbitrary blur areas should be currently **zero**.
 * @code {.c}
 * const ea_osd_area_buffer_t *area_buf =  ea_osd_area_current_buffer(osd, local_area_id);
 * @endcode
 *     - Draw DSP blur bounding box. It's not necessary to get
 * area buffer to draw blur bounding box.
 * The low level software layer takes care of the blur box drawing.
 * @code {.c}
 * ea_osd_set_dsp_blur_box(osd, local_area_id, blur_box_location)
 * @endcode
 * 4. Refresh
 *     - For VOUT, the `params` can be `NULL`.  For stream, if the
 * `dsp_pts` is given in the params, this function trys to use
 * overlay frame-sync machanism to apply overlay to the
 * corresponding frame number. Otherwise, the overlay is added
 * to the current arbitrary frame.
 * @code {.c}
 * ea_osd_refresh(osd, params)
 * @endcode
 *
 * 5. Some information about the overlay mechanism
 *
 *     Ambarella CV series chips superimpose graphics and/or text information on video streams by overlay hardware.
 * Only CLUT8 mode is supported, each look-up table is an array of 256 entries.
 * The entry is defined for four individual channels: Y, U, V, and alpha (transparency).
 * Alpha 0 is transparent and 255 is non-transparent.
 *
 *    1. Why do users need cycle buffers?
 *
 *       In reality, there is a delay for DSP apply the overlay to the frame, and the real-time delay in DSP is difficult to determine.  Also it is difficult to describe it, the follow section used a picture (Figure 2-1) to describe how the cycle buffers are used when drawing the overlay.
 *       - From the time line in below image, the time when DSP acquires each frame of data and starts encoding with overlay is called F1, F2, ..., and Fn.
 *       - The application starts to apply a new drawing on the overlay buffer block during [Fn, Fn+1] in the left time line, then this buffer content cannot be modified.
 *       - As the delay, DSP will start to handle the new drawing after (<b>4 + encode_dummy_latency</b>) frames in the right time line, which will finish at time T. Then this overlay buffer block can be released for other task.
 *       - Therefore, the number of cycle buffers used by the application is <b>the maximum number of plots</b> in the time span [Fn, T].
 *       - The yellow part is the number of frames that encode_dummy_elatency causes the DSP to delay for frame accurate overlay.
 *       @image html eazyai_overlay_mechanism_in_dsp.png "Figure 2-1. Overlay Mechanism in DSP."
 *
 *    2. How do users choose the correct circular buffer number?
 *
 *       - There are two cases for the application of overlay, which are ordinary overlay insertion and
 * frame accurate overlay insertion.
 *       - In the case of the ordinary overlay insertion, the overlay will be added to the current arbitrary frame.
 *       - In the case of the frame accurate overlay insertion, there is a frame_id(dsp_pts) along with the overlay frame, so that the overlay could be applied to corresponding correct frame.
 *       - The frame accurate overlay insertion is able to give better overlay effect.  For example, the detection bounding boxes, the human skeletons or the blur privacy effect can be added correspondingly with the correct target object.
 *       - Here are just some tips about the overlay circle buffer number. The library will handle this number,
 * and users don't need to take care about it.
 *       - In ordinary overlay insertion case:
 *         @code
 *         buffer_number = |-- 4~6  (overlay_update_frequency >= VIN_frequency/4)
 *                         |
 *                         |-- 2    (overlay_update_frequency < VIN_frequency/4)
 *         @endcode
 *       - In frame accurate overlay insertion case (dummy here is the encoding dummy latency number):
 *         @code
 *         buffer_number = |-- dummy + 4~6  (overlay_update_frequency >= VIN_frequency/4)
 *                         |
 *                         |-- dummy + 2    (overlay_update_frequency < VIN_frequency/4)
 *         @endcode
 *       - When there are less buffer number for frame accurate overlay insertion (but the buffer number is still enough for ordinary insertion), the overlay can still be applied, **but it will not be applied to the accurate frame**.
 *
 * @subsubsection eazyai_cvflow_core_log 2.2.7 Core Library - ea_log
 * @ref eazyai-log-helper provides macros to control the output of log messages of each individual source code file.
 * 1. ::EA_LOG_DECLARE_LOCAL
 *
 *     This macro is used to declare the log level variable in each source code file.
 * @code
 * EA_LOG_DECLARE_LOCAL(EA_LOG_LEVEL_NOTICE);
 * @endcode
 * 2. ::EA_LOG_GET_LOCAL
 *
 *     This macro is used to get the current log level in a source code file scope.
 * @code
 * log_level = EA_LOG_GET_LOCAL();
 * @endcode
 * 3. ::EA_LOG_SET_LOCAL
 *
 *     This macro is used to change the log level in a source code file scope.
 * @code
 * EA_LOG_SET_LOCAL(params->log_level);
 * @endcode
 * 4. ::EA_LOG_GET_GLOBAL
 *
 *     This macro is used to get the current log level in the global scope.
 * @code
 * log_level = EA_LOG_GET_GLOBAL();
 * @endcode
 * 5. ::EA_LOG_SET_GLOBAL
 *
 *     This macro is used to change the log level in the global scope.  By default, it is ::EA_LOG_LEVEL_INVALID.
 * After it is set with a valid value, all logs with lower criticality will not be output.
 * @code
 * EA_LOG_SET_GLOBAL(params->log_level);
 * @endcode
 * 6. ::EA_LOG_VERBOSE, ::EA_LOG_DEBUG, ::EA_LOG_NOTICE, ::EA_LOG_ERROR
 *
 *     These macros are used to output the log message when criticality is allowed by the log level.
 * @code
 * EA_LOG_NOTICE("retinaface_deinit\n");
 * @endcode
 * 7. ::EA_LOG_ASSERT
 *
 *     This macro can be used to check a statement.  If the statement is false, the trace of line, function, and file will be printed.
 * @code
 * EA_LOG_ASSERT(is_true());
 * @endcode
 *
 * - - - -
 *
 * @subsection eazyai_cvflow_utils 2.3 Utils Library
 *
 * @subsubsection eazyai_cvflow_utils_display 2.3.1 Utils Library - ea_display
 * @ref eazyai-display-details provide functions to draw detection results on the display media
 * in the form of bounding boxes, textboxes, and grey images.
 * Along with the parameters in the ea_display_set_*() functions, the other parameters of drawing content can be set
 * by changing the common parameters returned by ::ea_display_obj_params().
 * The overlay buffer size taken by each feature in ::ea_display_feature_e is around <b>(1024 + resolution * (enc-dummy-latency + 5))</b>.
 * 1. Draw on VOUT.
 * @code {.c}
 * ea_display_t *display = ea_display_new(EA_DISPLAY_VOUT, EA_DISPLAY_ANALOG_VOUT, EA_DISPLAY_BBOX_TEXTBOX, NULL);
 * @endcode
 * 2. Draw on the stream.
 *     - With automatically allocated overlay buffer:
 * @code
 * ea_display_t *display = ea_display_new(EA_DISPLAY_STREAM, stream_id, EA_DISPLAY_BBOX_TEXTBOX | EA_DISPLAY_GRAY_SCALE, NULL);
 * @endcode
 *     - With specified overlay buffer offset when overlay buffer is used in multiple applications:
 * @code
 * ea_display_t *display = ea_display_new(EA_DISPLAY_STREAM, stream_id, EA_DISPLAY_BBOX_TEXTBOX | EA_DISPLAY_GRAY_SCALE, (void *)0x1000000);
 * @endcode
 *     - With standalone server application:
 *         - Server application:
 * @code
 * ea_display_t *display = ea_display_new(EA_DISPLAY_STREAM_SERVER, stream_id, EA_DISPLAY_BBOX_TEXTBOX | EA_DISPLAY_GRAY_SCALE, (void *)0x1000000);
 * while (1) {
 *     ea_display_refresh(display, NULL);
 * }
 * @endcode
 *         - Client application:
 * @code
 * ea_display_t *display = ea_display_new(EA_DISPLAY_STREAM_CLIENT, stream_id, EA_DISPLAY_BBOX_TEXTBOX | EA_DISPLAY_GRAY_SCALE, "127.0.0.1");
 * @endcode
 *     - With DSP blur:
 * @code
 * ea_display_t *display = ea_display_new(EA_DISPLAY_STREAM, stream_id, EA_DISPLAY_BBOX_TEXTBOX | EA_DISPLAY_GRAY_SCALE, NULL);
 * ea_display_obj_params(display)->blur_strength = USER_BLUR_STRENGTH_LEVEL;
 * @endcode
 * 3. Draw on the JPEG image.
 * @code
 * ea_img_resource_t *img_resource = ea_img_resource_new(EA_JPEG_FOLDER, (void *)"/sdcard/in/");
 * // ...
 * ea_display_t *display = ea_display_new(EA_DISPLAY_JPEG, EA_TENSOR_COLOR_MODE_BGR, EA_DISPLAY_BBOX_TEXTBOX, (void *)"/sdcard/out/");
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_display_refresh(display, (void *)data.tensor_group[0]);
 * @endcode
 *
 * @subsubsection eazyai_cvflow_sub_utils 2.3.2 Utils Library - ea_utils
 * @ref eazyai-utils-details provide utilities such as NMS calculation and frames per second (fps) statistics, along with some macros to shorten code.
 * 1. Macros used in <em> do {} while (0); </em>:
 *     - ::RVAL_OK
 *
 *         This macro can be used to check the return value of a function if a negative returned value indicates failure.
 * If a negative value is returned, it will break <em> do {} while (0); </em>, and print the error trace of line, function, and file.
 * @code
 * int rval = 0; // checked by RVAL_OK()
 *
 * do {
 *     RVAL_OK(function_return_int());
 *     // ...
 * } while (0);
 *
 * return rval;
 * @endcode
 *     - ::RVAL_ASSERT
 *
 *         This macro can be used to check a statement.
 * If the statement is false, it will break <em> do {} while (0); </em>, and print the error trace of line, function, and file.
 * @code
 * int rval = 0; // checked by RVAL_OK()
 *
 * do {
 *     RVAL_ASSERT(is_true());
 *     // ...
 * } while (0);
 *
 * return rval;
 * @endcode
 *     - ::RVAL_BREAK
 *         This macro is used to further check a returned negative value after a loop inside <em> do {} while (0); </em> is broken.
 * If the return value is negative, it will perform a further break.
 * @code
 * int rval = 0; // checked by RVAL_OK()
 *
 * do {
 *     for (int i = 0; i < N; i++) {
 *         RVAL_OK(function_return_int());
 *         // ...
 *     }
 *     RVAL_BREAK();
 *     // ...
 * } while (0);
 *
 * return rval;
 * @endcode
 *
 * 2. Macros used to measure execution time:
 *     - ::EA_MEASURE_TIME_DECLARE
 *
 *         This macro is used to declare a static value to record time.
 *  It can be placed in a source code file outside of functions to be seen by all functions, or inside a function with limited visibility.
 * @code
 * EA_MEASURE_TIME_DECLARE();
 * static int cv_env_init(live_ctx_t *live_ctx, live_params_t *params)
 * {
 * // ...
 * }
 * @endcode
 * @code
 * int function()
 * {
 *     EA_MEASURE_TIME_DECLARE();
 * }
 * @endcode
 *     - ::EA_MEASURE_TIME_START
 *
 *         This macro is placed at the start point of a time measure.
 *     - ::EA_MEASURE_TIME_END
 *
 *         This macro is placed at the end point of a time measure. The time message will be printed.
 * @code
 * EA_MEASURE_TIME_DECLARE();
 * // ...
 * static int live_run_loop(live_ctx_t *live_ctx, live_params_t *params)
 * {
 *     int rval = 0;
 *     // ...
 *     do {
 *         // ...
 *         EA_MEASURE_TIME_START();
 *         RVAL_OK(retinaface_vp_forward(&live_ctx->retinaface));
 *         // ...
 *         EA_MEASURE_TIME_END("process time: ");
 *         // ...
 *     } while (0);
 *
 *     return rval;
 * }
 * @endcode
 *
 * 3. Statistic fps of loops:
 *
 *     ::ea_calc_fps() can be used to statistic fps of running loops by setting how many loops should be used to get the statistic.
 * During the statistic, ::ea_calc_fps() returns a negative value.  When a statistic is finished,
 * a valid fps value will be returned and a new statistic will start.
 * @code
 * static int live_run_loop(live_ctx_t *live_ctx, live_params_t *params)
 * {
 *     int rval = 0;
 *     ea_calc_fps_ctx_t calc_fps_ctx;
 *     float fps;
 *
 *     memset(&calc_fps_ctx, 0, sizeof(ea_calc_fps_ctx_t));
 *     calc_fps_ctx.count_period = 100;
 *     // ...
 *     do {
 *         // ...
 *         fps = ea_calc_fps(&calc_fps_ctx);
 *         if (fps > 0) {
 *             EA_LOG_NOTICE("fps %.1f\n", fps);
 *         }
 *     } while (0);
 *
 *     return rval;
 * }
 * @endcode
 *
 * 4. NMS:
 *
 *     ::ea_nms() can be used to perform NMS calculation on the data in the format of [[x1, y1, x2, y2, score], ...].
 * If there is data related to each item in [[x1, y1, x2, y2, score], ...],
 * for example, the landmarks output of a face detection network,
 * ::ea_nms() can be used to manage them together.
 * The outputs will be sorted in the score order.
 * @code
 * ea_nms(x1y1x2y2score, NULL, 0, valid_count, nms_threshold, use_iou_min, top_k,
 *     nms_x1y1x2y2score, NULL, &nms_valid_count);
 * @endcode
 * @code
 * ea_nms(bbox_and_score, landmarks, sizeof(float) * 10, valid_det_num, nms_threshold, use_iou_min, top_k,
 *     nms_bbox_and_score, nms_landmarks, &nms_valid_det_num);
 * @endcode
 *
 * 5. Soft-NMS:
 *
 *     ::ea_soft_nms(), it is named Soft-NMS.  For detail, please refer to https://arxiv.org/pdf/1704.04503.pdf.
 * non-maximum suppression is an integral part of the object detection pipeline.
 * First, it sorts all detection boxes on the basis of their scores.  The detection box M with the maximum score is selected
 * and all other detection boxes with a significant overlap (using a pre-defined threshold) with M are suppressed, such as above `ea_nms()`.
 * This process is recursively applied on the remaining boxes.  As per the design of the algorithm,
 * if an object lies within the predefined overlap threshold, it leads to a miss. To this end,
 * then Soft-NMS, an algorithm which decays the detection scores of all other objects as a continuous function of their overlap with M.
 * Hence, no object is eliminated in this process.
 * The outputs will be sorted in the score order.
 * @code
 * ea_soft_nms(float *x1y1x2y2score, void *aux, size_t aux_element_size, int num,
 *     float iou_threshold, int use_iou_min, int top_k,
 *     ea_soft_nms_method_t method, float discard_threshold, float sigma,
 *     float *out_x1y1x2y2score, void *out_aux, int *out_num);
 * @endcode
 *
 * @subsubsection eazyai_cvflow_sub_orb_extractor 2.3.3 Utils Library - ea_orb_extractor
 * @ref eazyai-orb-extractor-details provide functions to integrate the ORB extractor steps of FAST corner detection, ORB angle orientation calculation, and ORB BRIEF descriptor calculation. Each step has the choice to run with pure CPU, or run with CVflow acceleration.
 *
 * @subsubsection eazyai_cvflow_sub_topic 2.3.3 Utils Library - ea_topic
 * @ref eazyai-topic-details provide functions to transfer dedicated types of data among processes and devices. Currently, it supports buffer, buffer array, tensor, and tensor array.
 *
 * - - - -
 *
 * @subsection eazyai_cvflow_comm 2.4 Communication Library
 *
 * @subsubsection eazyai_cvflow_comm_queue 2.4.1 Comm Library - ea_queue
 * @ref eazyai-queue-details provide functions to transfer data in multi threads.
 * The queue owner allocates blocks of memory, and registers each memory block to ea_queue.
 * Each time the data sender needs a block of memory to carry data, it requests an idle block from ea_queue.
 * After the data receiver consumes the data, it releases the block of memory to ea_queue.
 * This block of memory is called a carrier in the API. After the queue is destroyed, the queue owner frees these blocks of memory.
 * @image html eazyai_queue_carrier_states.jpg "Figure 2-2. EazyAI Queue Carrier States."
 * 1. Add carriers.
 * @code {.c}
 * im_output_t output_group[IM_OUTPUT_QUEUE_SIZE];
 * ea_queue_t *im_output_queue = ea_queue_new();
 * for (i = 0; i < IM_OUTPUT_QUEUE_SIZE; i++) {
 *     ea_queue_add_carrier(im_output_queue, &output_group[i])
 * }
 * @endcode
 * 2. Enqueue:
 * @code {.c}
 * im_output_t *im_output = NULL;
 * im_output_t *force_out_output = NULL;
 * im_output = (im_output_t *)ea_queue_request_carrier(im_output_queue);
 * // or
 * im_output = (im_output_t *)ea_queue_request_carrier_force(im_output_queue, (void **)&force_out_output);
 * // or
 * im_output = (im_output_t *)ea_queue_request_carrier_nowait(im_output_queue);
 * // or
 * im_output = (im_output_t *)ea_queue_request_carrier_timeout(im_output_queue, 10 * 1000);
 * // put data into im_output
 * ...
 * ea_queue_en(im_output_queue, im_output);
 * @endcode
 * 3. Peek:
 * @code
 * if (ea_queue_peek(im_output_queue)) { ... }         // peek carrier in the queue
 * if (ea_queue_peek_carrier(im_output_queue)) { ... } // peek idle carrier which is not in the queue
 * @endcode
 * 4. Dequeue and release:
 * @code
 * im_output_t *im_output = NULL;
 * im_output = (im_output_t *)ea_queue_de(im_output_queue);
 * //or
 * im_output = (im_output_t *)ea_queue_de_nowait(im_output_queue);
 * // or
 * im_output = (im_output_t *)ea_queue_de_timeout(im_output_queue, 10 * 1000);
 * // use data in im_output
 * ...
 * ea_queue_release_carrier(im_output_queue, im_output)
 * @endcode
 * 5. Free:
 * @code
 * ea_queue_free(im_output_queue);
 * @endcode
 *
 * @subsubsection eazyai_cvflow_comm_socket 2.4.2 Comm Library - ea_socket
 * @ref eazyai-socket-details provide functions to transfer data in multi processes and multi devices.
 * The TCP protocol is used inside to build direct connections between a server and multi clients. The server/client role is decided automatically inside by if the server IP is provided and which side starts first. A frame of data can be divided into blocks of data and be sent through multi calls of `ea_socket_send` The N+1 calls of `ea_socket_send` on one side will have corresponding 1 call of `ea_socket_read` and N calls of `ea_socket_read_by_fd` on the other side.
 *
 * - - - -
 *
 * @subsection eazyai_cvflow_accl 2.5 Acceleration Library
 *
 * @subsubsection eazyai_cvflow_accl_fast 2.5.1 ACCL Library - ea_fast
 * @ref eazyai-fast-details provides functions to do FAST corner detection with CVflow acceleration. Please refer to the section **ORB extractor** under the chapter **Acceleration Demos** of the CNNGen sample package Doxygen for how to generate the Cavalry binary file for `ea_fast`.
 *
 * @subsubsection eazyai_cvflow_accl_angle 2.5.2 ACCL Library - ea_angle
 * @ref eazyai-angle-details provides functions to do ORB angle orientation calculation with CVflow acceleration. Please refer to the section **ORB extractor** under the chapter **Acceleration Demos** of the CNNGen sample package Doxygen for how to generate the Cavalry binary file for `ea_angle`.
 *
 * @subsubsection eazyai_cvflow_accl_brief 2.5.3 ACCL Library - ea_brief
 * @ref eazyai-brief-details provides functions to do ORB BRIEF descriptor calculation with CVflow acceleration. Please refer to the section **ORB extractor** under the chapter **Acceleration Demos** of the CNNGen sample package Doxygen for how to generate the Cavalry binary files for `ea_brief`.
 *
 * - - - -
 *
 * @section eazyai_simulator 3 EazyAI Simulator
 * @subsection eazyai_simulator_build 3.1 Build
 * @subsubsection eazyai_simulator_build_include 3.1.1 Include
 * For each source file that uses the API in the EazyAI library, the following include file is required:
 * @code
 * #include <eazyai.h>
 * @endcode
 * @subsubsection eazyai_simulator_build_compile 3.1.2 Compile
 * The EazyAI simulator uses CMake to compile the source code.  As this library uses the ADES and AC_INF libraries,
 * users must source the CNNGen toolchain before compiling this library.  The EazyAI simulator library is avaliable for
 * adv (standard) CNNGen toolchain, but is not available for basic CNNGen toolchain.
 *
 * Before compiling the library, users must install the json-c library into the folder `<project_folder>/eazyai/3rd_party`.
 * The json-c library is available under MIT license; it aids in analyzing the `network_name.json` file.
 * The readme in this folder guides the installation.  The installation steps below are the same as those in the readme:
 * @code
 * build $ cd <project_folder>/eazyai/3rd_party
 * build $ git clone https://github.com/json-c/json-c.git
 * build $ cd json-c
 * build $ git reset --hard f2fc1ca00a9f35aa67c987f45a4f86ae5ad22e57
 * build $ cd -
 * build $ mkdir build
 * build $ cd build
 * build $ cmake ../json-c -DCMAKE_INSTALL_PREFIX=../install
 * build $ make
 * build $ make install
 * build $ cd -
 * @endcode
 * @note
 * The compile target should be located at `<project_folder>/eazyai/3rd_party/install/lib/libjson-c.so`.
 * If users must use another path, they can use the cmake parameter`-DJSON_C_INC` and `-DJSON_C_LIB` to modify it.
 *
 * Compile steps for EazyAI simulator library:
 * @code
 * build $ source <user_CNNGen_Toolchain_env_file>
 * build $ cd <user_path>/cvflow_cnngen_samples/library/eazyai)
 * build $ mkdir build
 * build $ cd build; cmake ..; make; cd -
 * @endcode
 *
 * (Optional) OpenCV is enabled by default.  The users can use the macro `DISABLE_OPENCV` to compile a no-OpenCV version library.
 * @code
 * build $ cmake -DDISABLE_OPENCV=Y ..; make
 * @endcode
 *
 * (Optional) If there are multiple versions of OpenCV installed, users can
 * use the CMake macro `USE_OPENCV_VERSION` during the CMake stage to specify the OpenCV version to be used.
 * For example,
 * @code
 * build $ cmake -DUSE_OPENCV_VERSION=4.2.0 ..; make
 * @endcode
 * @note
 * Users can specify the version of OpenCV with CMake macro <b>USE_OPENCV_VERSION</b> as required if needed, such as `cmake -DUSE_OPENCV_VERSION=3.4.3 ..`.
 * However, high version OpenCV is always suggested. Some examples are only supported by high OpenCV version, such as
 * `/cvflow_cnngen_samples/library/eazyai/unit_test/nn_arm_task/qrcode`, which requests <b>OpenCV >= 3.4.3</b>.
 * And please ensure that the EazyAI library and applications use the same OpenCV version.
 *
 * In Linux SDK, it used OpenCV 4.5 for CVflow application, but it is not supported in Ubuntu 2004
 * if users want to match between CVflow and Simulator, users could install OpenCV 4.5 with PPA resource as follows.
 * @code
 * $ sudo add-apt-repository ppa:komfamedia/backports
 * $ sudo apt-get update
 * $ sudo apt-get install libopencv-dev
 * @endcode

 * (Optional) The AC_INF is able to use a central processing unit (CPU) to do the forward inference (default setting).
 * It also supports using a graphics processing unit (GPU) to perform forward inference.
 * To enable this feature, users must install CUDA on the build machine.  It is necessary to
 * use the macro CUDA_VERSION to specify the CUDA version during the compiling of this EazyAI library.
 * @code
 * build $ cmake -DCUDA_VERSION=<version> ..; make
 * @endcode
 * @note
 * - If users call the GPU on a no-GPU machine via AC_INF API, the AC_INF instance cannot be created successfully.
 * - For more details on how to run GPU using AC_INF, refer to @ref eazyai_simulator_components_net.
 * - Since CNNGen toolchain 2.5.5.0 and 3.5.5.0, Ades will also benefit from GPU, and it is an alpha version, users can try it if needed.
 * - Please refer to @ref sub_sec_cnngen_acinf and @ref sub_sec_cnngen_ades for the supported CUDA versions.
 *
 * (Optional) Users can use the following command to remove ADES related support from the source code.
 * This could be useful for the basic toolchian, which doesn't support ADES feature.
 * @code
 * build $ cmake -DDISABLE_ADES=Y ..; make
 * @endcode
 *
 * For how to compile the `test_eazyai` application, refer to @ref eazyai_unit_test_simulator.
 *
 * - - - -
 *
 * @subsection eazyai_simulator_components 3.2 Components
 * @subsubsection eazyai_simulator_components_env 3.2.1 ea_env
 * @ref eazyai-env-details initialize the necessary environment to use the CV features.
 * ::ea_env_open() should be called before the other APIs in EazyAI are called.
 * ::ea_env_close() should be called after the other APIs in EazyAI are called.
 * @code {.c}
 * int features;
 * rval = ea_env_open(features);
 * ea_utils_env_callbacks_register();
 * // ...
 * ea_env_close();
 * @endcode
 *
 * @note
 * - The JPEG file mode needs OpenCV library to show network result.
 * - ::EA_ENV_ENABLE_IAV, ::EA_ENV_ENABLE_CAVALRY, ::EA_ENV_ENABLE_VPROC, ::EA_ENV_ENABLE_NNCTRL,
 *	 ::EA_ENV_ENABLE_OSD_VOUT, ::EA_ENV_ENABLE_OSD_STREAM are not supported on the simulator platform.
 *
 * @note
 * + `EA_ENV_ENABLE_OSD_JPEG` is deleted in `ea_env()` since version 0.5.0, but users can enable it with calling ea_utils_env_callbacks_register().
 * + Only when ea_utils_env_callbacks_register() is called, users can use `EA_JPEG_FOLDER` in Preprocessing modules.
 *
 * @subsubsection eazyai_simulator_components_tensor 3.2.2 ea_tensor
 * @ref eazyai-tensor-details provide interfaces for the tensor, which carries data in the data flow of a CV program.
 * The tensor is a four-dimensional array with a shape in NxCxHxW order.
 * This is not the same with EazyAI CVflow library; when creating a tensor,
 * the memory is allocated from the heap.  Users are not required to know the
 * memory physical address or sync cache.
 * - ::EA_MEM_HEAP
 *   This is the type of memory allocated with malloc for common use.
 *   The tensor created by ::ea_tensor_new() or ::ea_tensor_new_from_file() uses this type of memory.
 *
 * @note
 * ::EA_MEM_CAVALRY, ::EA_MEM_IAV_DSP, ::EA_MEM_IAV_ANON are not supported on the simulator platform.
 *
 * @subsubsection eazyai_simulator_components_img_resource 3.2.3 ea_img_resource
 * @ref eazyai-img-resource-details load image data in the format ::ea_tensor_color_mode_e from
 * RAW binary files (::EA_RAW_FILE or ::EA_RAW_FILE_FOLDER) or JPEG files (::EA_JPEG_FOLDER).
 * A new group of image data is loaded by each call of ::ea_img_resource_hold_data().
 * ::ea_img_resource_drop_data() should be called the same number of times as ::ea_img_resource_hold_data() is called to release the internal buffers.
 * Usually, the image data from a JPEG file has the format of ::EA_TENSOR_COLOR_MODE_BGR.
 * If the YUV NV12 data is loaded from a binary file, the Y data and the UV data are stored discontiguously in the memory;
 * two tensors will be used to hold the image data.
 * The Y data is stored in a tensor returned by ::ea_img_resource_hold_data() and
 * the UV data is stored in the tensor returned by ::ea_tensor_related().
 *
 * 1. ::EA_RAW_FILE
 *
 *     This type of image resource is created by a file path for reading one RAW binary file
 * with a name in the format [N]x[C]x[H]x[W]_*.bin; for example, `1x3x480x640_dog.bin`.
 * @code {.c}
 * ea_img_resource_t *img_resource;
 * char *file_path = "/sdcard/mtcnn/in/1x3x480x640_face01.bin";
 * img_resource = ea_img_resource_new(EA_RAW_FILE, file_path);
 * // ...
 * ea_img_resource_free(img_resource);
 * @endcode
 * @code {.c}
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_img_resource_drop_data(img_resource, &data);
 * @endcode
 *
 * 2. ::EA_RAW_FILE_FOLDER
 *
 *     This type of image resource is created by a folder path for reading each RAW binary file
 * under the folder with a name in the format [N]x[C]x[H]x[W]_*.bin; for example, `1x3x480x640_dog.bin`.
 * The data in every file will be returned by each call of ::ea_img_resource_hold_data().
 * The reading order is decided by the Linux API @e readdir().
 * @code {.c}
 * ea_img_resource_t *img_resource;
 * char *folder_path = "/sdcard/mtcnn/in/";
 * img_resource = ea_img_resource_new(EA_RAW_FILE_FOLDER, folder_path);
 * // ...
 * ea_img_resource_free(img_resource);
 * @endcode
 * @code {.c}
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_img_resource_drop_data(img_resource, &data);
 * @endcode
 *
 * 3. ::EA_JPEG_FOLDER
 *
 *     This type of image resource is created by a folder path for reading each *.jpg file under the folder.
 * The data in every file will be returned by each call of ::ea_img_resource_hold_data().
 * The reading order is decided by the Linux API @e readdir().
 * @code {.c}
 * ea_img_resource_t *img_resource;
 * char *folder_path = "/sdcard/mtcnn/in/";
 * img_resource = ea_img_resource_new(EA_JPEG_FOLDER, folder_path);
 * // ...
 * ea_img_resource_free(img_resource);
 * @endcode
 * @code {.c}
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_img_resource_drop_data(img_resource, &data);
 * @endcode
 *
 * @note
 * ::EA_CANVAS, ::EA_CANVAS_GROUP, ::EA_PYRAMID are not supported on the simulator platform.
 *
 * @subsubsection eazyai_simulator_components_preprocess 3.2.4 ea_preprocess
 * @ref eazyai-preprocess-details provide functions to perform image color convert, resize, and crop.
 * The process is performed by the CPU device with the help of OpenvCV.  If the user requires the inference
 * result to be the same between the simulator platform and the CVflow platform, the OpenCV library version must be the same.
 * Users can check the version of this library in the Linux SDK package under `<user_path>/ambarella/prebuild/oss/arm<version>/opencv/usr/lib`.
 * There are limitations on each type of device.  Refer to @ref eazyai-preprocess-details for the limitations.
 * @note
 * On the simulator platform, ::EA_CPU is supported for preprocessing. ::EA_VP and ::EA_DSP are not supported.
 *
 * 1. Color convert:
 *
 *     Resize will be performed if the source size and the destination size are different.
 *     - YUV NV12 to RGB or BGR
 * @code {.c}
 * ea_img_resource_data_t data;
 * size_t shape[] = {1, 3, 300, 300};
 * ea_tensor_t *rgb_tensor = ea_tensor_new(EA_U8, shape, 0);
 * ea_tensor_t *bgr_tensor = ea_tensor_new(EA_U8, shape, 0);
 * // ...
 * ea_cvt_color_resize(data.tensor_group[0], rbg_tensor, EA_COLOR_YUV2RGB_NV12, EA_CPU);
 * ea_cvt_color_resize(data.tensor_group[0], bgr_tensor, EA_COLOR_YUV2BGR_NV12, EA_CPU);
 * // ...
 * ea_tensor_free(rgb_tensor);
 * ea_tensor_free(bgr_tensor);
 * @endcode *     - RBG to BGR or BGR to RGB.
 * @code {.c}
 * ea_cvt_color_resize(rbg_tensor, bgr_tensor, EA_COLOR_RGB2BGR, EA_CPU);
 * ea_cvt_color_resize(bgr_tensor, rbg_tensor, EA_COLOR_BGR2RGB, EA_CPU);
 * @endcode
 *
 * 2. Crop:
 *
 *     Resize will be performed if the source size and the destination size are different.
 *
 * @code {.c}
 * size_t shape[] = {1, 1, 224, 224};
 * ea_roi_t roi = {100, 100, 200, 200};
 * ea_tensor_t *scale_tensor = ea_tensor_new_from_file(EA_U8, shape, RAW_file_path);
 * ea_crop_resize(&data.tensor_group[0], 1, &scale_tensor, 1, &roi, EA_TENSOR_COLOR_MODE_RGB, EA_CPU);
 * @endcode
 * @note
 * ::ea_crop_resize does not support ::EA_COLOR_TRANSPOSE.
 *
 * If only resize is required, use NULL as ::ea_roi_t:
 * @code {.c}
 * size_t shape[] = {1, 1, 224, 224};
 * ea_tensor_t *scale_tensor = ea_tensor_new_from_file(EA_U8, shape, RAW_file_path);
 * ea_crop_resize(&data.tensor_group[0], 1, &scale_tensor, 1, NULL, EA_TENSOR_COLOR_MODE_RGB, EA_CPU);
 * @endcode
 * @note
 * - ::ea_crop_resize does not support batch mode on the simlator platform.
 * - ::ea_crop_resize does not support ::EA_TENSOR_COLOR_MODE_YUV_NV12.
 *
 * @subsubsection eazyai_simulator_components_net 3.2.5 ea_net
 * @ref eazyai-net-details provide functions to perform network forward inference on the simulator platform
 *using the ADES or AC_INF API.
 * - For the AC_INF API, the network model and converted weights are stored in
 * the parser output folder.  The `network_name.json` is regarded as the structure file of the networks.
 * This file defines the relations between each node and
 * the data format, dimension, and so on for each node.
 * The weights binary files and the other parameters of the network are also stored in the
 * parser output folder.  The path of these binary files are defined in `network_name.json`.
 * Users must keep the parser output folder in its original hierarchy.
 * - For the ADES API, users will require the output of ades_autogen.py.  The `network_name_ades.cmd` file path must be filled to
 * the `ades_cmd_file` parameter of ::ea_net_t.  Users must keep the ADES output folder in its original hierarchy because the weights
 * and other network parameters are stored in the ADES output folder.
 * The path of these binary files are defined in `network_name_ades.cmd`.
 * The `network_name.json` is also required because it provides the input / output (I/O) port information of this network.
 *
 * The tensors that hold the network I/O buffers can be fetched by ::ea_net_input()/::ea_net_output().
 * The input tensors can be used to accept the input data, for example, as the @a dst in ::ea_cvt_color_resize().
 * The output tensors can be used to read the inference result.
 * 1. Load the model and call AC_INF API.
 * @code {.c}
 * char *model_path = "/path/network_name.json"
 * ea_net_params_t net_param;
 * net_param.acinf_gpu_id = -1; (Specify the GPU id to use, -1 is CPU)
 * ea_net_t *net = ea_net_new(&net_param);
 * ea_net_config_input(net, "input");
 * ea_net_config_output(net, "output");
 * ea_net_load(net, EA_NET_LOAD_FILE, (void *)model_path, 1);
 * input_tensor = ea_net_input(net, "input");
 * output_tensor = ea_net_output(net, "output");
 * @endcode
 * @note
 * If users call the GPU on a no-GPU machine via AC_INF API, the AC_INF instance cannot be created successfully.
 * If only the CPU is required to perform the forward inference, set acinf_gpu_id as -1.  For more information on how to compile the EazyAI library
 * with CUDA support, refer to @ref eazyai_simulator_build_compile.
 *
 * 2. Load the model and call the ADES API.
 * @code {.c}
 * char *model_path = "/path_to/network_name.json"
 * ea_net_params_t net_param;
 * net_param.ades_cmd_file = "/path_to/network_name_ades.cmd";
 * ea_net_t *net = ea_net_new(&net_param);
 * ea_net_config_input(net, "input");
 * ea_net_config_output(net, "output");
 * ea_net_load(net, EA_NET_LOAD_FILE, (void *)model_path, 1);
 * input_tensor = ea_net_input(net, "input");
 * output_tensor = ea_net_output(net, "output");
 * @endcode
 * 3. Forward.
 * @code
 * ea_cvt_color_resize(img_tensors[0], input_tensor, EA_COLOR_BGR2RGB, EA_CPU); (optional)
 * ea_net_forward(net, 1);
 * @endcode
 * 4. Read inference result.
 * @code
 * bbox_addr = (float *)ea_tensor_data(output_tensor);
 * @endcode
 * @subsubsection eazyai_simulator_components_display 3.2.6 ea_display
 * @ref eazyai-display-details provide functions to draw detection results on the JPEG image
 * in the form of bounding boxes, textboxes, segmentations, and grey images.
 * Along with the parameters in the ea_display_set_*() functions, the other parameters of drawing content can be set
 * by changing the common parameters returned by ::ea_display_obj_params().
 * @code
 * ea_img_resource_t *img_resource = ea_img_resource_new(EA_JPEG_FOLDER, (void *)"/sdcard/in/");
 * // ...
 * ea_display_t *display = ea_display_new(EA_DISPLAY_JPEG, EA_TENSOR_COLOR_MODE_BGR, EA_DISPLAY_BBOX_TEXTBOX, (void *)"/sdcard/out/");
 * ea_img_resource_data_t data;
 * // ...
 * ea_img_resource_hold_data(img_resource, &data);
 * // ...
 * ea_display_refresh(display, (void *)data.tensor_group[0]);
 * @endcode
 * @note
 * ::EA_DISPLAY_STREAM, ::EA_DISPLAY_STREAM_SERVER, ::EA_DISPLAY_STREAM_CLIENT, and ::EA_DISPLAY_VOUT
 * are not supported on simulator platform.  ::EA_DISPLAY_JPEG feature depends on OpenCV.
 *
 * @subsubsection eazyai_simulator_components_log 3.2.7 ea_log
 * @ref eazyai-log-helper provide macros to control the output of log messages of each individual source code file.
 * 1. ::EA_LOG_DECLARE_LOCAL
 *
 *     This macro is used to declare the log level variable in each source code file.
 * @code
 * EA_LOG_DECLARE_LOCAL(EA_LOG_LEVEL_NOTICE);
 * @endcode
 * 2. ::EA_LOG_GET_LOCAL
 *
 *     This macro is used to get the current log level in a source code file scope.
 * @code
 * log_level = EA_LOG_GET_LOCAL();
 * @endcode
 * 3. ::EA_LOG_SET_LOCAL
 *
 *     This macro is used to change the log level in a source code file scope.
 * @code
 * EA_LOG_SET_LOCAL(params->log_level);
 * @endcode
 * 4. ::EA_LOG_GET_GLOBAL
 *
 *     This macro is used to get the current log level in the global scope.
 * @code
 * log_level = EA_LOG_GET_GLOBAL();
 * @endcode
 * 5. ::EA_LOG_SET_GLOBAL
 *
 *     This macro is used to change the log level in the global scope.  By default, it is ::EA_LOG_LEVEL_INVALID.
 * After it is set with a valid value, all logs with lower criticality will not output.
 * @code
 * EA_LOG_SET_GLOBAL(params->log_level);
 * @endcode
 * 6. ::EA_LOG_VERBOSE, ::EA_LOG_DEBUG, ::EA_LOG_NOTICE, ::EA_LOG_ERROR
 *
 *     These macros are used to output the log message when the criticality is allowed by the log level.
 * @code
 * EA_LOG_NOTICE("retinaface_deinit\n");
 * @endcode
 * 7. ::EA_LOG_ASSERT
 *
 *     This macro can be used to check a statement.  If the statement is false, the trace of line, function, and file will be printed.
 * @code
 * EA_LOG_ASSERT(is_true());
 * @endcode
 *
 * @subsubsection eazyai_simulator_simulator_components_utils 3.2.8 ea_utils
 * @ref eazyai-utils-details provide utilities such as NMS calculation and fps statistic, as well as some macros to shorten code.
 * 1. Macros used in <em> do {} while (0); </em>:
 *     - ::RVAL_OK
 *
 *         This macro can be used to check the return value of a function if a negative returned value indicates failure.
 * If a negative value is returned, it will break <em> do {} while (0); </em>, and print the error trace of line, function, and file.
 * @code
 * int rval = 0; // checked by RVAL_OK()
 *
 * do {
 *     RVAL_OK(function_return_int());
 *     // ...
 * } while (0);
 *
 * return rval;
 * @endcode
 *     - ::RVAL_ASSERT
 *
 *         This macro can be used to check a statement.
 * If the statement is false, it will break <em> do {} while (0); </em>, and print the error trace of line, function, and file.
 * @code
 * int rval = 0; // checked by RVAL_OK()
 *
 * do {
 *     RVAL_ASSERT(is_true());
 *     // ...
 * } while (0);
 *
 * return rval;
 * @endcode
 *     - ::RVAL_BREAK
 *         This macro is used to make further check of a returned negative value after a loop inside <em> do {} while (0); </em> is broken.
 * If the return value is negative, it will perform a further break.
 * @code
 * int rval = 0; // checked by RVAL_OK()
 *
 * do {
 *     for (int i = 0; i < N; i++) {
 *         RVAL_OK(function_return_int());
 *         // ...
 *     }
 *     RVAL_BREAK();
 *     // ...
 * } while (0);
 *
 * return rval;
 * @endcode
 * 2. Macros used to measure execution time:
 *     - ::EA_MEASURE_TIME_DECLARE
 *
 *         This macro is used to declare a static value to record time.
 *  It can be placed in a source code file outside of functions to be seen by all functions, or inside a function for limited visibility.
 * @code
 * EA_MEASURE_TIME_DECLARE();
 * static int cv_env_init(live_ctx_t *live_ctx, live_params_t *params)
 * {
 * // ...
 * }
 * @endcode
 * @code
 * int function()
 * {
 *     EA_MEASURE_TIME_DECLARE();
 * }
 * @endcode
 *     - ::EA_MEASURE_TIME_START
 *
 *         This macro is placed at the start point of a time measure.
 *     - ::EA_MEASURE_TIME_END
 *
 *         This macro is placed at the end point of a time measure.  The time message will be printed.
 * @code
 * EA_MEASURE_TIME_DECLARE();
 * // ...
 * static int live_run_loop(live_ctx_t *live_ctx, live_params_t *params)
 * {
 *     int rval = 0;
 *     // ...
 *     do {
 *         // ...
 *         EA_MEASURE_TIME_START();
 *         RVAL_OK(retinaface_vp_forward(&live_ctx->retinaface));
 *         // ...
 *         EA_MEASURE_TIME_END("process time: ");
 *         // ...
 *     } while (0);
 *
 *     return rval;
 * }
 * @endcode
 * 3. Statistic fps of loops:
 *
 *     ::ea_calc_fps() can be used to get statistic fps of running loops by setting how many loops should be used to get the statistic.
 * During the statistic, ::ea_calc_fps() returns a negative value.  When a statistic is finished,
 * a valid fps value will be returned and a new statistic will start.
 * @code
 * static int live_run_loop(live_ctx_t *live_ctx, live_params_t *params)
 * {
 *     int rval = 0;
 *     ea_calc_fps_ctx_t calc_fps_ctx;
 *     float fps;
 *
 *     memset(&calc_fps_ctx, 0, sizeof(ea_calc_fps_ctx_t));
 *     calc_fps_ctx.count_period = 100;
 *     // ...
 *     do {
 *         // ...
 *         fps = ea_calc_fps(&calc_fps_ctx);
 *         if (fps > 0) {
 *             EA_LOG_NOTICE("fps %.1f\n", fps);
 *         }
 *     } while (0);
 *
 *     return rval;
 * }
 * @endcode
 * 4. NMS
 *
 *     ::ea_nms() can be used to perform NMS calculation on the data in the format of [[x1, y1, x2, y2, score], ...].
 * If there is data related to each item in [[x1, y1, x2, y2, score], ...],
 * for example, the landmarks output of a face detection network,
 * ::ea_nms() can be used to manage them together.
 * The outputs will be sorted in the score order.
 * @code
 * ea_nms(x1y1x2y2score, NULL, 0, valid_count, nms_threshold, use_iou_min, top_k,
 *     nms_x1y1x2y2score, NULL, &nms_valid_count);
 * @endcode
 * @code
 * ea_nms(bbox_and_score, landmarks, sizeof(float) * 10, valid_det_num, nms_threshold, use_iou_min, top_k,
 *     nms_bbox_and_score, nms_landmarks, &nms_valid_det_num);
 * @endcode
 *
 * - - - -
 *
 * @section eazyai_arm_postprocess 4 EazyAI Arm Postprocess
 *
 * The EazyAI Arm Postprocess library assembles public network postprocessing realization on Arm,
 * such as SSD, YOLOV5, and so on.
 *
 * @subsection eazyai_arm_postprocess_build 4.1 Build
 * The EazyAI Arm Postprocess library is based on the EazyAI Library.  Users should first enable the EazyAI library and then enable
 * the EazyAI Arm Postprocess library.  Follow the commands below to build the library:
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build $ make menuconfig
 *          [*] Ambarella Package Configuration  --->
 *              [*] Build Ambarella EAZYAI library  --->
 *                  [*] Build Ambarella custom postprocess libray
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 *     packages  --->
 *         eazyai  --->
 *              [*] libeazyai-arm-postprocess (packages/eazyai/unit_test)  --->
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 *     meta-ambalib  --->
 *         recipes-eazyai  --->
 *              [*] libeazyai-arm-postprocess (meta-ambalib/recipes-eazyai/libeazyai)  --->
 * @endcode
 * @subsection eazyai_arm_postprocess_customize_postprocess 4.2 How to Add Customized Postprocess
 * @subsubsection eazyai_arm_postprocess_customize_postprocess_implement 4.2.1 Implement
 *
 * Users can add the customized postprocess of a network into the EazyAI Arm Postprocess library by implementing the four functions in the following table, such as SSD in
 * `eazyai/unit_test/nn_arm_task/ssd`.
 *
 * <table>
 * <caption id="ops function">Table 4-1. EazyAI_Postprocess_Functions.</caption>
 * <tr><th align="left">Function<th align="left">Description
 * <tr><td>int (\*nn_arm_init)(nn_arm_context_t \*ctx, const char \*lua_file)<td>Initialization function of post-processing
 * <tr><td>void (\*nn_arm_deinit)(nn_arm_context_t \*ctx)<td>Recovery function of post-processing
 * <tr><td>int (\*nn_arm_post_process)(nn_arm_context_t \*ctx, vp_output_t \*output, nn_label_t \*labels, int label_count)<td>Process function of post-processing
 * <tr><td>int (\*nn_arm_show_result)(nn_arm_context_t \*ctx, const ea_tensor_t \*tensor)<td>Show result function of post-processing
 * </table>
 *
 * Register them to the EazyAI Arm Postprocess library by searching by name.
 *
 * @subsubsection eazyai_arm_postprocesss_custmoize_postprocess_include 4.2.2 Include
 *
 * Add customized postprocess header files into `eazyai/unit_test/nn_arm_task/nn_arm_list.h`, such as SSD below.
 *
 * @code {.c}
 * #ifdef BUILD_AMBARELLA_CONFIG_NN_ARM_TASK_SSD
 * #include "ssd.h"
 * #endif
 * @endcode
 *
 * @subsubsection eazyai_arm_postprocess_customize_postprocess_register 4.2.3 Register Postprocess
 *
 * Register postprocess functions at @ref eazyai_arm_postprocess_customize_postprocess_implement to EazyAI Arm Postprocess library in
 * `eazyai/unit_test/nn_arm_task/nn_arm.c`, such as SSD below.
 *
 * @code {.c}
 * #ifdef BUILD_AMBARELLA_CONFIG_NN_ARM_TASK_SSD
 * REGISTER_NN_ARM_TASK("ssd", ssd_arm_init, ssd_arm_deinit, ssd_arm_post_process, ssd_arm_show_result),
 * #endif
 * @endcode
 *
 * @subsubsection eazyai_arm_postprocess_custmoize_postprocess_configure 4.2.4 Configure
 *
 * Add build configuration macros in `eazyai/unit_test/AmbaConfig` of the SDK, such as SSD below.
 *
 * @code {.c}
 * config BUILD_AMBARELLA_CONFIG_NN_ARM_TASK_SSD
 * 	bool "Build Ambarella custom postprocess library with ssd"
 * 	default y
 * 		help
 * 			Build Ambarella custom postprocess library with ssd
 * @endcode
 *
 * @subsubsection eazyai_arm_postprocess_customize_postprocess_makefile 4.2.5 Makefile
 *
 * Add source files into `eazyai/unit_test/nn_arm_task` of the SDK, such as SSD below.
 *
 * @code {.c}
 * ifeq ($(BUILD_AMBARELLA_CONFIG_NN_ARM_TASK_SSD), y)
 * LOCAL_SRCS	+= $(LOCAL_PATH)/ssd/ssd.c
 * LOCAL_CFLAGS	+= -I$(LOCAL_PATH)/ssd
 * endif
 * @endcode
 *
 * - - - -
 *
 * @section eazyai_unit_test 5 EazyAI Unit Test
 *
 * @subsection eazyai_unit_test_cvflow 5.1 CVflow Inference Test
 *
 * @subsubsection eazyai_unit_test_cvflow_build 5.1.1 Build
 *
 * Follow the commands below to build the unit test `test_eazyai`:
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build $ make menuconfig
 *          [*] Ambarella Package Configuration  --->
 *              [*] Build Ambarella EAZYAI library  --->
 *                  [*] Build EazyAI unit tests
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 *     packages  --->
 *         eazyai  --->
 *              [*] eazyai-unit-test (packages/eazyai/unit_test)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 *     meta-ambaapp  --->
 *         recipes-test  --->
 *              [*] eazyai-test@virtual (meta-ambaapp/recipes-test/eazyai-test)  --->
 * @endcode
 *
 * @subsubsection eazyai_unit_test_cvflow_usage 5.1.2 Unit Test Usage
 *
 * The available options of `test_eazyai` are listed as follows:
 * @verbatim
	-m --mode                    Run mode: (0 = live), (1 = file), (2 = dummy). Default is live mode.
	-c --canvas_id               Canvas Id. Default is 1.
	-p --pyramid_id              Pyramid Id.
	-r --rgb                     Set color type to rgb_planar, default is bgr_planar. Only for live mode. It will be deprecated, suggest use option --nn_in_cf.
	--roi                        Roi of image, default is full image, order of roi parameters: x,y,h,w. Only for live mode.
	--yuv                        Enable yuv input from iav. Default is disable. It will be deprecated, suggest use option --nn_in_cf.
	--nn_in_cf                   Set color format of model, 0=bgr_planar, 1=rgb_planar, 2=grayscale, 3=yuv_nv12. Default is 0. Only for live mode.
	--isrc                       Multi input, e.g. -isrc "i:data=image|t:jpeg|c:rgb|r:0,0,0,0|d:cpu". Only for file mode.
	--model_path                 Path of cavalry binary file.
	--dis_auto_odfc              Disable output float32 data from float16 data on non-float32 CVflow ARCH. Default is enable.
	--nvp_id                     Specify the NVP ID. Only valid for CV3.
	--ades_cmd_file              Enable Ades with the Ades command file path, default will enable Acinference without this file.
	--acinf_gpu_id               Acinference gpu id. Default is -1(CPU). Only for Acinference.
	-n --nn_arm_name             NN Arm task name.
	--queue_size                 Queue size, test_eazyai is refined to use single thread, please use test_eazyai_queue for this option.
	--lua_file                   Lua file name.
	--thread_num                 Thread number, test_eazyai is refined to use single thread, please use test_eazyai_queue for this option.
	--extra_input                Extra input for network.
	--label_path                 Path of class names file.
	--hold_img                   Enable or disable to hold image data for postprocess. Default is disable. Only for live mode.
	-d --draw_mode               Draw mode, 0=draw bbox, 1=draw img.
	-s --stream_id               Stream ID to draw. Default is -1, means app doesn't use stream to draw.
	--fsync_off                  Enable or disable frame sync, default is enable.
	--stream_offset              Overlay buffer offset for multi-stream display.
	--vout_id                    VOUT Id for display. Default is 1, means to use HDMI/CVBS.
	--to_txt                     Save detection results to txt file. Only for file mode.
	--output_dir                 Path to contain output file.
	--support                    Show support list.
	-v --log_level               Log level 0=None, 1=Error, 2=Notice, 3=Debug, 4=Verbose.
	-t --iter                    Iteration of running inference or postprocess, loop forever (0xffffffff) if set 0. Default is 1.
	--interval                   Interval loop count, should be less than or equal iteration count. Default is 1.
	--cavalry_load               Specify the percentage of cavalry loading for dummy mode, ex. 0.5.

	test_eazyai live pipeline:
	==========================================================================================================================================
	Mode                   Input               ==>Preprocess          ==>Inference           ==>Postprocess         ==>Show_Results
	==========================================================================================================================================
    live                  |-c --canvas_id        |-r --rgb              |   --model_path       |-n --nn_arm_name      |-d --draw_mode
                          |-p --pyramid_id       |   --roi              |   --dis_auto_odfc    |   --queue_size       |-s --stream_id
                          |                      |   --yuv              |   --nvp_id           |   --lua_file         |   --fsync_off
                          |                      |   --nn_in_cf         |                      |   --thread_num       |   --stream_offset
                          |                      |                      |                      |   --extra_input      |   --vout_id
                          |                      |                      |                      |   --label_path       |
                          |                      |                      |                      |   --hold_img         |
                          |                      |                      |                      |                      |
	==========================================================================================================================================

	test_eazyai live usage:
	test_eazyai -m 0 -s 0 -d 0 -r -n yolov3 --model_path onnx_yolov3_cavalry.bin --lua_file yolov3.lua --label_path label_coco_80.txt --fsync_off

	test_eazyai file pipeline:
	==========================================================================================================================================
	Mode                   Input               ==>Preprocess          ==>Inference           ==>Postprocess         ==>Show_Results
	==========================================================================================================================================
    file                  |   --isrc                                    |   --model_path       |-n --nn_arm_name      |-d --draw_mode
                          |                                             |   --dis_auto_odfc    |   --queue_size       |   --to_txt
                          |                                             |   --nvp_id           |   --lua_file         |   --output_dir
                          |                                             |   --ades_cmd_file    |   --thread_num       |
                          |                                             |   --acinf_gpu_id     |   --extra_input      |
                          |                                             |                      |   --label_path       |
                          |                                             |                      |                      |
                          |                                             |                      |                      |
	==========================================================================================================================================

	test_eazyai file usage:
	test_eazyai -m 1 -d 0 -n yolov3 --model_path onnx_yolov3_cavalry.bin --lua_file yolov3.lua --isrc i:input.1=in|t:jpg|c:rgb --label_path label_coco_80.txt --output_dir out/

	test_eazyai file usage with Ades on PC:
	test_eazyai -m 1 -d 0 -n yolov3 --model_path <usr_path>/out_onnx_yolov3_parser/onnx_yolov3.json --lua_file yolov3.lua --isrc i:input.1=<usr_path>/dra_img|t:jpg|c:rgb --label_path <usr_path>/label_coco_80.txt --output_dir <usr_path>/yolov3/out --ades_cmd_file <usr_path>/ades_onnx_yolov3/onnx_yolov3_ades.cmd

	test_eazyai file usage with Acinference on PC:
	test_eazyai -m 1 -d 0 -n yolov3 --model_path <usr_path>/out_onnx_yolov3_parser/onnx_yolov3.json --lua_file yolov3.lua --isrc i:data=<usr_path>/dra_img|t:jpg|c:rgb --label_path <usr_path>/label_coco_80.txt --output_dir <usr_path>/yolov3/out

	test_eazyai dummy usage:
	test_eazyai -m 2 --model_path onnx_yolov3_cavalry.bin

	support 16 arm postprocess tasks:
			to_file
			bisenet
			centernet
			deeplabv3
			fgfd
			fairmot
			hfnet
			lffd
			mobilenetv2_nv12
			opennet
			retinaface
			ssd
			yolox
			yolov3
			yolov8
			yolov5
   @endverbatim
 *
 * The value of `--isrc` can be set as shown in the table below :
 *
 * <table>
 * <caption id="isrc_key_value">Table 5-1. Isrc Parameters for test_eazyai.</caption>
 * <tr align="middle"><th> Key <th> Value <th> Option <th align="left"> Description
 * <tr align="middle"><td> i <td> name=folder      <td> <B>No</B>  <td align="left"> Feed network with files in a folder; name is the input name of a network.
 * <tr align="middle"><td> t <td> jpeg/raw/jpg/png <td> <B>No</B>  <td align="left"> Type of file; file postfix shold be ".jpeg", ".bin",".jpg" or ".bin".  Supports capital letters, such as JPEG.
 * <tr align="middle"><td> c <td> rgb/bgr          <td> <B>Yes</B> <td align="left"> Color of image which is fed into network; the default value is bgr.
 * <tr align="middle"><td> r <td> 0,0,0,0          <td> <B>Yes</B> <td align="left"> The region of interest (ROI) of an image which is fed into the network; the value is in order of x,y,h,w.  The default is 0,0,0,0, which feeds full image.
 * <tr align="middle"><td> d <td> cpu/vp           <td> <B>Yes</B> <td align="left"> Use CPU or CVflow device to perform pre-processing; the default value is CPU.
 * </table>
 *
 * @subsubsection eazyai_unit_test_cvflow__example 5.1.3 Examples
 *
 * Example to get the **support list**:
 *
 * @code {.c}
 * build $ test_eazyai --support
 * @endcode

 * Four **CVflow** examples are as follows.
 *
 * 1. File mode:
 * @code {.c}
 * board # rmmod cavalry && modprobe cavalry && cavalry_load -f /lib/firmware/cavalry.bin -r
 * board # test_eazyai -m 1 -d 1 -n hfnet --model_path /sdcard/hfnet/model/tf_hfnet_cavalry.bin --lua_file /usr/share/
 *
 *
 * /eazyai/lua/hfnet.lua --isrc "i:gray_image=/sdcard/hfnet/in|t:jpeg|d:vp" --output_dir /sdcard/hfnet/out/
 * @endcode
 * 2. Dummy mode for performance test:
 * @code {.c}
 * board # rmmod cavalry && modprobe cavalry && cavalry_load -f /lib/firmware/cavalry.bin -r
 * board # test_eazyai -m 2 --model_path /sdcard/hfnet/model/tf_hfnet_cavalry.bin
 * @endcode
 * 3. Live mode (draw on stream <em>rtsp://10.0.0.2/stream1</em>):
 * @code {.c}
 * board # eazyai_video.sh --stream_A 1080p --enc_dummy_latency 4 --reallocate_mem overlay,0x01200000
 * board # test_eazyai -m 0 -s 0 -c 1 -d 1 --model_path /sdcard/hfnet/model/tf_hfnet_cavalry.bin -n hfnet --lua_file /usr/share/ambarella/eazyai/lua/hfnet.lua
 * @endcode
 * 4. Live mode (draw on VOUT):
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p
 * board # test_eazyai -m 0 -d 1 -c 1 --model_path /sdcard/hfnet/model/tf_hfnet_cavalry.bin -n hfnet --lua_file /usr/share/ambarella/eazyai/lua/hfnet.lua
 * @endcode
 *
 *
 * - - - -
 *
 * @subsection eazyai_unit_test_simulator 5.2 Simulator Inference Test
 *
 * @subsubsection eazyai_unit_test_simulator_build 5.2.1 Build
 *
 * The EazyAI unit test simulator shares the same header files source files with
 * @ref eazyai_unit_test_cvflow_build, also it shared the same unit test `test_eazyai`:
 *
 * Before compiling the executable target, users must install the **EazyAI** simulator library into the folder
 * `<project_folder>/eazyai/build`.  If users must use another path,
 * they can use the cmake parameter `-DEA_INC` and `-DEA_LIB` to modify it.
 * For how to compile the **EazyAI** simulator library,
 * refer to @ref eazyai_simulator_build_compile.
 *
 * Follow the steps below to setup the Lua library, the Eigen library, and the executable application.
 *
 * The Lua library is available under MIT license; it aids in analyzing the `network_name.lua` file for postprocessing.
 * The readme in this folder guides the installation.  The installation steps below are the same as those in the readme:
 * @code
 * build $ cd <project_folder>/eazyai/unit_test/3rd_party
 * build $ wget https://www.lua.org/ftp/lua-5.4.4.tar.gz
 * build $ tar -xzf lua-5.4.4.tar.gz
 * build $ cd lua-5.4.4
 * build $ make MYCFLAGS="-fPIC"
 * build $ cd -
 * @endcode
 * @note
 * The compile target should be located at `<project_folder>/eazyai/unit_test/3rd_party/lua-5.4.4/src/liblua.a`.
 * If users must use another path, they can use the cmake parameter `-DLUA_INC` to modify it.
 *
 * Below are the steps to install the Eigen library into the folder `<project_folder>/eazyai/unit_test/3rd_party`.
 * This library aids in algebra function.  Only its header files are required during the compilation.
 * @code
 * build $ cd <project_folder>/eazyai/unit_test/3rd_party
 * build $ wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.zip
 * build $ unzip eigen-3.4.0.zip
 * build $ cd -
 * @endcode
 * @note
 * - The demo fairmot (source file path `eazyai/unit_test/nn_arm_task/fairmot/`) requires this Eigen library.
 *   If users do not require it, they must modify `eazyai/unit_test/CMakeLists.txt`
 *   and `eazyai/unit_test/nn_arm_task/nn_arm_list.h` to remove the related source code.
 * - The download target should be located at `<project_folder>/eazyai/unit_test/3rd_party/eigen-3.4.0/Eigen`.
 * - If users must use another path, they can use the cmake parameter `-DEIGEN_INC` to modify it.
 * - For more information about this Eigen library, refer to https://eigen.tuxfamily.org/dox/GettingStarted.html
 *
 * Below are the steps to install the `test_eazyai` application.
 * The EazyAI unit test simulator uses CMake to compile the source code.
 * The compile steps are as follows:
 * @code
 * build $ source <user_CNNGen_Toolchain_env_file>
 * build $ cd <user_path>/cvflow_cnngen_samples/eazyai/unit_test
 * build $ mkdir build
 * build $ cd build; cmake ..; make; cd -
 * @endcode
 * The executable file is located at `<project_folder>/eazyai/unit_test/build/test_eazyai`.
 * @note
 * `nn_arm_task/qrcode` requests `OpenCV >= 3.4.3`.  By default, this target is not compiled.  To compile this target,
 * users must install an `OpenCV >= 3.4.3`.  If there are multiple versions of OpenCV installed, users can
 * use the CMake macro `USE_OPENCV_VERSION` during the CMake stage to specify which OpenCV version to be used.
 * For example, `cmake -DUSE_OPENCV_VERSION=3.4.3 ..`.
 * Ensure that the libeazyai uses the same OpenCV version as this unit test.  For more information on how to compile the library libeazyai,
 * refer to @ref eazyai_simulator_build_compile.
 *
 * @subsubsection eazyai_unit_test_simulator_usage 5.2.2 Usage
 * The usage of the EazyAI simulator unit test is similar to the @ref eazyai_unit_test_cvflow_usage.
 * The EazyAI simulator unit test supports using AC_INF API or ADES API to forward the network.
 * For the difference between AC_INF API and ADES API, refer to @ref eazyai_introduction_simulator.
 * Users must pay attention to the following options:
 * - `--models`: This option should be followed by the path of the `network_name.json` file.
 *   The `network_name.json` must remain in the parser output of this network in AC_INF mode.
 *   For more information, refer to @ref eazyai_simulator_components_net.
 * - `--ades_cmd_file`: This option should be followed by the path of the `network_name_ades.cmd` file.
 *   Along with `network_name.json`, the `network_name_ades.cmd` should remain in the ADES output folder.
 *   If this option is provided via command-line interface (CLI), the forward inference is performed by the ADES API;
 *   otherwise, it is performed by the AC_INF API.
 *   And this file is generated by the tool `ades_autogen.py`.
 *   For more information, refer to @ref eazyai_simulator_components_net.
 * - `--acinf_gpu_id`: The AC_INF supports using GPU to perform forward inference.  To enable this feature, users must
 *   set up CUDA on the build machine as well as the GPU version EazyAI library.
 *   If users call the GPU on a no-GPU machine via AC_INF API, the AC_INF instance cannot be created successfully.
 *   For more information on how to compile the EazyAI lib with GPU support, refer to @ref eazyai_simulator_build_compile.
 *   For more information on how to run GPU using AC_INF, refer to @ref eazyai_simulator_components_net.
 *
 * For more information, refer to @ref eazyai_unit_test_cvflow_usage.
 *
 * @subsubsection eazyai_unit_test_simulator_example 5.2.3 Examples
 *
 * Example for how to get the **support list**:
 *
 * @code {.c}
 * build $ ./build/test_eazyai --support
 * @endcode
 *
 * Some **ADES** examples, as shown below, which only support file mode:
 *
 * @code {.c}
 * build $ ./build/test_eazyai -m 1 -d 0 --model_path /<cnngen_sample_sdk>/out/onnx/demo_networks/onnx_yolov5s/out_onnx_yolov5s_parser/onnx_yolov5s.json \
 *          --label_path /<cnngen_sample_sdk>/library/eazyai/unit_test/resource/label_coco_80.txt -n yolov5 \
 *          --lua_file /<cnngen_sample_sdk>/library/eazyai/unit_test/resource/lua/yolov5s.lua --output_dir output --isrc "i:images=dra_img|t:jpeg|c:rgb" \
 *          --ades_cmd_file /<cnngen_sample_sdk>/out/onnx/demo_networks/onnx_yolov5s/ades_onnx_yolov5s/onnx_yolov5s_ades.cmd
 * @endcode
 *
 * Some **Acinference** examples, as shown below, which only support file mode:
 *
 * @code {.c}
 * build $ ./build/test_eazyai -m 1 -d 0 --model_path /<cnngen_sample_sdk>/out/onnx/demo_networks/onnx_yolov5s/out_onnx_yolov5s_parser/onnx_yolov5s.json \
 *          --label_path /<cnngen_sample_sdk>/library/eazyai/unit_test/resource/label_coco_80.txt -n yolov5 \
 *          --lua_file /<cnngen_sample_sdk>/library/eazyai/unit_test/resource/lua/yolov5s.lua --output_dir output --isrc "i:images=dra_img|t:jpeg|c:rgb"
 * @endcode
 *
 * - - - -
 *
 * @subsection eazyai_core_api_test 5.3 Core API Test
 *
 * Core API test `test_api_eazyai_core ` is designed for Core library test to make sure every API works well in different chips, also it is the reference code for
 * how to use these APIs by users.  Please refer to `eazyai/unit_test/api_test/readme.txt` with below main source codes.
 *     - `case_ea_env.cpp` for @ref eazyai_cvflow_core_env
 *     - `case_ea_tensor.cpp` for @ref eazyai_cvflow_core_tensor
 *     - `case_ea_img_resource.cpp` for @ref eazyai_cvflow_core_img_resource
 *     - `case_ea_preprocess.cpp` for @ref eazyai_cvflow_core_preprocess
 *     - `case_ea_net.cpp` for @ref eazyai_cvflow_core_net
 *     - `case_ea_osd.cpp` for @ref eazyai_cvflow_core_osd
 *     - No for @ref eazyai_cvflow_core_log as this is too simple
 *
 *
 * - - - -
 *
 * @subsection eazyai_display_unit_test_cvflow 5.4 Display Test
 *
 * @subsubsection eazyai_display_unit_test_cvflow_build 5.4.1 Build
 * `test_eazyai_display` is an Display unit test of EazyAI which is only for chip side, it can be built
 * with the same steps in @ref eazyai_unit_test_cvflow_build.
 *
 * @subsubsection eazyai_display_unit_test_cvflow_usage 5.4.2 Usage
 * `test_eazyai_display` is an user interaction drawing tool with a two-level menu as follows:
 *
 * @code {.c}
 * Main Menu:
 *     v - Display On Vout
 *     s - Display On Stream
 *     q - Quit
 *
 * Sub Menu:
 *     1 - Draw bbox (stream blur)
 *     2 - Draw textbox
 *     3 - Draw line
 *     4 - Draw circle
 *     5 - Display refresh
 *     q - Back to Main Menu
 * @endcode
 *
 * @note
 * Stream Blur is only supported in feature **Draw bbox** in **Stream Mode**.
 *
 * @subsubsection eazyai_display_unit_test_cvflow_examples 5.4.3 Examples
 * Part of the prompts have been omitted from the examples for brevity.  For details, please refer to
 * the prompts from `test_eazyai_display`.
 *
 * - Example to draw bbox on VOUT:
 * @code {.c}
 * board # eazyai_video.sh --hdmi 1080p --fb_res 1920x1080
 * board # test_eazyai_display
 *
 * ** Main Menu Choice **
 * ==> Input your choice: v
 *
 * ** OBJ Window Attribution **
 * [Notice] OBJ window size is [1920.0]x[1080.0].
 *
 * ** Sub Menu Choice **
 * ==> Input your choice: 1
 *
 * ** Input Function Attribution **
 * ==> Input start x: 100
 * ==> Input start y: 100
 * ==> Input width: 200
 * ==> Input height: 200
 * ==> Input border thickness: 10
 * ==> Input bbox color(if solid bbox, will also be bg color): 2
 * ==> Input bbox background transparency: 255
 * ==> Input title position: 2
 * ==> Input font size: 20
 * ==> Input text color: 2
 * ==> Input text background color: 3
 * ==> Input text background transparency: 255
 * ==> Input text string: Ambarella
 *
 * ** To Refresh Display **
 *
 * ** Sub Menu Choice **
 * ==> Input your choice: 5
 *
 * ** Display Refreshed **
 * @endcode
 *
 * - Example to draw bbox on stream:
 * @code {.c}
 * board # eazyai_video.sh --stream_A 1080p
 * board # test_eazyai_display
 *
 * ** Main Menu Choice **
 * ==> Input your choice: s
 *
 * ** OBJ Window Attribution **
 * [Notice] OBJ window size is [1920.0]x[1080.0].
 *
 * ** Sub Menu Choice **
 * ==> Input your choice: 1
 *
 * ** Input Function Attribution **
 * ==> Input start x: 100
 * ==> Input start y: 100
 * ==> Input width: 200
 * ==> Input height: 200
 * ==> Input blur strength: -1
 * ==> Input border thickness: 10
 * ==> Input bbox color(if solid bbox, will also be bg color): 2
 * ==> Input bbox background transparency: 255
 * ==> Input title position: 2
 * ==> Input font size: 20
 * ==> Input text color: 2
 * ==> Input text background color: 3
 * ==> Input text background transparency: 255
 * ==> Input text string: Ambarella
 *
 * ** To Refresh Display **
 *
 * ** Sub Menu Choice **
 * ==> Input your choice: 5
 *
 * ** Display Refreshed **
 * @endcode
 *
 * - Example to draw blur on stream:
 * @code {.c}
 * board # eazyai_video.sh --stream_A 1080p --blur --enc_dummy_latency 3 --reallocate_mem blur,0x01000000:overlay,0x01000000
 * board # test_eazyai_display
 *
 * ** Main Menu Choice **
 * ==> Input your choice: s
 *
 * ** OBJ Window Attribution **
 * [Notice] OBJ window size is [1920.0]x[1080.0].
 *
 * ** Sub Menu Choice **
 * ==> Input your choice: 1
 *
 * ** Input Function Attribution **
 * ==> Input start x: 100
 * ==> Input start y: 100
 * ==> Input width: 200
 * ==> Input height: 200
 * ==> Input blur strength: 2
 *
 * ** To Refresh Display **
 *
 * ** Sub Menu Choice **
 * ==> Input your choice: 5
 *
 * ** Display Refreshed **
 * @endcode
 *
 * - Draw other objects
 *
 *     Users can draw other objects according to the prompts of `test_eazyai_display`.
 *
 *
 * - - - -
 *
 * @subsection eazyai_orb_extractor_unit_test 5.5 ORB Extractor Test
 *
 * `test_ea_orb_extractor` allows users to run ORB extrator on CVflow.
 *
 * Please refer to @ref sec_acceleration_orb in Chapter @ref fs_cnngen_acceleration_demos.
 *   + Generate Cavalry Binary Files
 *   + Run Unit Test
 *
 * - - - -
 *
 * @subsection eazyai_topic_unit_test 5.6 Topic Test
 *
 * `test_ea_topic` allows users to share message or content between multiple processes or devices, such as the network output, images, and so on.
 *
 * Please follow below steps to run unit test.
 *
 * - Prepare PNG image files in a SD card for EVK test
 *
 *     For example, place files on the SD card with the following structure.
 *     @code
 *     /sdcard/topic
 *     |--in
 *     |       image_1.png
 *     |       image_2.png
 *     |       image_3.png
 *     |       ...
 *     |
 *     |--out_buffer
 *     |--out_buffer_array
 *     |__out_tensor
 *     |__out_tensor_array
 *     @endcode
 *
 *     - Run buffer mode.
 *
 *         In terminal A
 *         @code
 *         board # test_ea_topic -m 0 -i /sdcard/topic/in --server_ip 127.0.0.1 --port 62023
 *         @endcode
 *
 *         In terminal B
 *         @code
 *         board # test_ea_topic -m 0 -o /sdcard/topic/out_buffer --server_ip 127.0.0.1 --port 62023
 *         @endcode
 *
 *         The folder `/sdcard/topic/out_buffer` should get the same image files as in `/sdcard/topic/in`.
 *
 *     - Run buffer array mode.
 *
 *         In terminal A
 *         @code
 *         board # test_ea_topic -m 1 -i /sdcard/topic/in --server_ip 127.0.0.1 --port 62023
 *         @endcode
 *
 *         In terminal B
 *         @code
 *         board # test_ea_topic -m 1 -o /sdcard/topic/out_buffer_array --server_ip 127.0.0.1 --port 62023
 *         @endcode
 *
 *         The folder `/sdcard/topic/out_buffer_array` should get the same image files as in `/sdcard/topic/in`.
 *
 *     - Run tensor mode.
 *
 *         In terminal A
 *         @code
 *         board # test_ea_topic -m 2 -i /sdcard/topic/in --server_ip 127.0.0.1 --port 62023
 *         @endcode
 *
 *         In terminal B
 *         @code
 *         board # test_ea_topic -m 2 -o /sdcard/topic/out_tensor --server_ip 127.0.0.1 --port 62023
 *         @endcode
 *
 *         The folder `/sdcard/topic/out_tensor` should get the same image files as in `/sdcard/topic/in`.
 *
 *     - Run tensor array mode.
 *
 *         In terminal A
 *         @code
 *         board # test_ea_topic -m 3 -i /sdcard/topic/in --server_ip 127.0.0.1 --port 62023
 *         @endcode
 *
 *         In terminal B
 *         @code
 *         board # test_ea_topic -m 3 -o /sdcard/topic/out_tensor_array --server_ip 127.0.0.1 --port 62023
 *         @endcode
 *
 *         The folder `/sdcard/topic/out_tensor_array` should get the same image files as in `/sdcard/topic/in`.
 *
 * - - - -
 *
 * @section eazyai_api 6 EazyAI API
 * Visit the following links to see details of @ref eazyai-api "EazyAI API".
 *     - @ref eazyai-api-details
 *     - @ref eazyai-api-helper
 *     - @ref eazyai_arm_postprocess-api-details
 *     - @ref eazyai_arm_postprocess-helper
 *
 * - - - -
 *
 * @section eazyai_license 7 License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
 *
 * This file and its contents ( "Software" ) are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights.  This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors.  You may not use, reproduce,
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
 * @defgroup eazyai-api EazyAI library API
 * @brief EazyAI library API.
 */

/*!
 * @defgroup eazyai-api-details EazyAI library functions
 * @ingroup eazyai-api
 * @brief Definition of functions in EazyAI library.
 */
/*!
 * @defgroup eazyai-api-helper EazyAI library macros, enumerations and structures
 * @ingroup eazyai-api
 * @brief Definition of macros, enumerations and structures in EazyAI library.
 */

// ea_log
/*!
 * @defgroup eazyai-log-details ea_log functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_log functions.
 */
/*!
 * @defgroup eazyai-log-helper ea_log macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_log macros, enumerations and structures.
 */

// ea_env
/*!
 * @defgroup eazyai-env-details ea_env functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_env functions.
 */
/*!
 * @defgroup eazyai-env-helper ea_env macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_env macros, enumerations and structures.
 */

// ea_tensor
/*!
 * @defgroup eazyai-tensor-details ea_tensor functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_tensor functions.
 */
/*!
 * @defgroup eazyai-tensor-helper ea_tensor macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_tensor macros, enumerations and structures.
 */

// ea_img_resource
/*!
 * @defgroup eazyai-img-resource-details ea_img_resource functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_img_resource functions.
 */
/*!
 * @defgroup eazyai-img-resource-helper ea_img_resource macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_img_resource macros, enumerations and structures.
 */

// ea_preprocess
/*!
 * @defgroup eazyai-preprocess-details ea_preprocess functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_preprocess functions.
 */
/*!
 * @defgroup eazyai-preprocess-helper ea_preprocess macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_preprocess macros, enumerations and structures.
 */

// ea_net
/*!
 * @defgroup eazyai-net-details ea_net functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_net functions.
 */
/*!
 * @defgroup eazyai-net-helper ea_net macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_net macros, enumerations and structures.
 */

// ea_osd
/*!
 * @defgroup eazyai-osd-details ea_osd functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_osd functions.
 */
/*!
 * @defgroup eazyai-osd-helper osd macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_osd macros, enumerations and structures.
 */

// ea_display
/*!
 * @defgroup eazyai-display-details ea_display functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_display functions.
 */
/*!
 * @defgroup eazyai-display-helper ea_display macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_display macros, enumerations and structures.
 */

// ea_utils
/*!
 * @defgroup eazyai-utils-details ea_utils functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_utils functions.
 */
/*!
 * @defgroup eazyai-utils-helper ea_utils macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_utils macros, enumerations and structures.
 */

// ea_topic
/*!
 * @defgroup eazyai-topic-details ea_topic functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_topic functions.
 */
/*!
 * @defgroup eazyai-topic-helper ea_topic macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_topic macros, enumerations and structures.
 */

// ea_orb_extractor
/*!
 * @defgroup eazyai-orb-extractor-details ea_orb_extractor functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_orb_extractor functions.
 */
/*!
 * @defgroup eazyai-orb-extractor-helper ea_orb-extractor macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_orb-extractor macros, enumerations and structures.
 */

// ea_queue
/*!
 * @defgroup eazyai-queue-details ea_queue functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_queue functions.
 */
/*!
 * @defgroup eazyai-queue-helper ea_queue macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_queue macros, enumerations and structures.
 */

// ea_socket
/*!
 * @defgroup eazyai-socket-details ea_socket functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_socket functions.
 */
/*!
 * @defgroup eazyai-socket-helper ea_socket macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_socket macros, enumerations and structures.
 */

// ea_fast
/*!
 * @defgroup eazyai-fast-details ea_fast functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_fast functions.
 */
/*!
 * @defgroup eazyai-fast-helper ea_fast macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_fast macros, enumerations and structures.
 */

// ea_angle
/*!
 * @defgroup eazyai-angle-details ea_angle functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_angle functions.
 */
/*!
 * @defgroup eazyai-angle-helper ea_angle macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_angle macros, enumerations and structures.
 */

// ea_brief
/*!
 * @defgroup eazyai-brief-details ea_brief functions
 * @ingroup eazyai-api-details
 * @brief Definition of ea_brief functions.
 */
/*!
 * @defgroup eazyai-brief-helper ea_brief macros, enumerations and structures
 * @ingroup eazyai-api-helper
 * @brief Definition of ea_brief macros, enumerations and structures.
 */

/*!
 * @defgroup eazyai_arm_postprocess-api-details EazyAI Arm Postprocess library functions
 * @ingroup eazyai-api
 * @brief EazyAI Arm Postprocess API details, in file nn_arm.h
 */

/*!
 * @defgroup eazyai_arm_postprocess-helper EazyAI Arm Postporcess structures
 * @ingroup eazyai-api
 * @brief Definition of EazyAI Arm Postprocess library structures.
 */

/*!
 * @example test_eazyai.c
 * This is a source code file of test_eazyai.
 *
 */

/*!
 * @example test_eazyai_display.c
 * This is a source code file of test_eazyai_display.
 *
 */

/*!
 * @example test_ea_topic.cpp
 * This is a source code file of test_ea_topic.
 *
 */

/*!
 * @example test_ea_orb_extractor.cpp
 * This is a source code file of test_ea_orb_extractor.
 *
 */

/*!
 * @example test_api_eazyai_core.cpp
 * This is a source code file of test_api_eazyai_core.
 *
 */
 /*!
 * @example case_ea_env.cpp
 * This is a source code file of test_api_eazyai_core.
 *
 */
/*!
 * @example case_ea_img_resource.cpp
 * This is a source code file of test_api_eazyai_core.
 *
 */
/*!
 * @example case_ea_net.cpp
 * This is a source code file of test_api_eazyai_core.
 *
 */
/*!
 * @example case_ea_osd.cpp
 * This is a source code file of test_api_eazyai_core.
 *
 */
/*!
 * @example case_ea_preprocess.cpp
 * This is a source code file of test_api_eazyai_core.
 *
 */
/*!
 * @example case_ea_tensor.cpp
 * This is a source code file of test_api_eazyai_core.
 *
 */
/*!
 * @example nn_cvflow.c
 * This is a source code file of test_eazyai.
 *
 */
/*!
 * @example dummy_input.c
 * This is a source code file of test_eazyai.
 *
 */
/*!
 * @example file_input.c
 * This is a source code file of test_eazyai.
 *
 */
/*!
 * @example iav_input.c
 * This is a source code file of test_eazyai.
 *
 */
/*!
 * @example nn_input.c
 * This is a source code file of test_eazyai.
 *
 */
/*!
 * @example post_thread.c
 * This is a source code file of test_eazyai.
 *
 */
/*!
 * @file doc_lib_eis.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2022-07-18
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
 * @page page_lib_eis_doc EIS Library API
 *
 * @section eis_history 0. Revision History
 *
 * <table>
 * <caption id="lib_eis_rev_history"></caption>
 * <tr><th> Library Version <th> Updated Date <th align="left"> Modification
 * <tr><td> 2.0.0 <td>  20220718 <td> Initial Version
 * <tr><td> 2.0.0 <td>  20220808 <td> Support ICM42670 from Invensense @ref eis_imu
 * <tr><td> 3.0.0 <td>  20220823 <td> Reserve enough space for EIS external structure
 * <tr><td rowspan="3"> 4.0.0 <td rowspan="3"> 20221123 <td> 1. Remove EFR logic from test_eis_warp.c
 * <tr>                                                 <td> 2. Refine the initialization API
 * <tr>                                                 <td> 3. Add user context support
 * <tr><td> 4.0.1 <td>  20230206 <td> Round up vertical warp out width 64 for MCTF restriction
 * <tr><td rowspan="2"> 4.1.0 <td rowspan="2"> 20230421 <td> 1. Added support to real time update filter scale for stationary mode @ref eis_rt_change
 * <tr>                                                 <td> 2. Added @ref eis_qa_q12
 * <tr><td> 4.1.1 <td>  20230427 <td> Align horizontal warp output width with 64 for c2y restriction under encode mode 0
 * <tr><td> 4.2.0 <td>  20230626 <td> The data structure amba_eis_stat_t upgrade to have mono_pts
 * <tr><td rowspan="2"> 4.2.0 <td rowspan="2"> 20230717 <td> 1. Added section @ref eis_pm
 * <tr>                                                 <td> 2. Unified the EIS module in this chapter for CV5 / CV52 / CV72 @ref eis_intro
 * <tr><td> 4.2.1 <td>  20231110 <td> Refined stationary mode rt scale configuration @ref eis_filter_mode
 * <tr><td> 4.3.0 <td>  20231123 <td> Added option for configuring EIS warp table density @ref eis_warp_vector
 * <tr><td> 4.3.0 <td>  20231201 <td> Refined the description for EIS window @ref eis_res_eis
 * <tr><td rowspan="3"> 4.3.0 <td rowspan="3"> 20231212 <td> 1. Added eis_v6_framework for section @ref eis_overview "1. Overview"
 * <tr>                                                 <td> 2. Added @ref eis_qa_q14
 * <tr>                                                 <td> 3. Moved Section @ref gyro_dev_tree to chapter 3
 * <tr><td> 4.3.1 <td>  20231214 <td> Fix the issue for updating EFL in real time. @ref eis_rt_change
 * <tr><td rowspan="3"> 4.4.0 <td rowspan="3"> 20231222 <td> 1. Enable EIS on rotation pipeline @ref eis_enc
 * <tr>                                                 <td> 2. Enable the customized filter @ref eis_filter_mode
 * <tr>                                                 <td> 3. Add one example @ref eis_ex_4
 * <tr><td> 4.4.0 <td>  20240122 <td> Adjusted chapter @ref eis_design and added description in @ref eis_sensor
 * </table>
 *
 * - - - -
 *
 * @section eis_overview 1. Overview
 * Electronic image stabilization (EIS) is a process where image stability is
 * controlled through electronic processing procedures. Another motion sensor, "IMU",  is
 * mounted to detect camera vibration in the pitch / yaw / roll directions. EIS responds
 * by moving the image cropping offset and applying warp operations so that the
 * output content can remain in a position that is as close as possible to the original position.
 *
 * @subsection eis_intro 1.1. EIS Introduction
 * In this chapter, the EIS module introduced is in the software development kits (SDKs)
 * for the <b>CV5, CV52, and CV72</b> systems on chip (SoCs).
 * <br>From the system perspective, the EIS module is implemented differently from previous
 * chips, such as CV2x and S5L. In order to receive one channel output's stablized result, another
 * auxiliary channel is configured to malloc external memory and generate the 3A
 * (auto white balance (AWB) / auto exposure (AE) / auto focus (AF)) statistics as
 * soon as possible in order for AE control to function without delay. The channels are called
 * the <b>EIS source channel</b> and the <b>EIS effective channel</b>.
 *
 * @image html eis_v6_framework.png "Figure 1-1. EIS Framework."
 * The figure above shows the CV5x EIS framework. The connection between both channels
 * (the EIS source channel and the EIS effective channel) are reflected by "raw_src_chan"
 * in channel configuration. For the EIS source channel, the EIS framework prepares necessary data for
 * further computation inside the EIS library and frame synchronization inside of the IAV driver.
 * - Image raw data: there is one external memory attached with the EIS source channel
 * for caching full size raw image and 1/12 size CE (contrast enhance) image. The memory size
 * depends on the "raw_feed_frame_num" from channel configuration, which indicates the capacity
 * of the external memory in frame units while "raw_cached_items" sets the active cached frame
 * number. Ambarella does NOT suggest setting "raw_cached_items" equal to the raw_feed_frame_num value.
 * - 3A statistics: generated without delay and cached in the IAV driver, which is already
 * sychronized with image raw. To ensure that the 3A statistics are synchronized with image raw
 * when taking the raw cache number into consideration, set "eis-delay-count" the same
 * as (raw_cached_items - 1) for the <b>EIS effective channel</b>.
 * - Warp table: the EIS application fetches gyro raw data and real-time CMOS timing information
 * and forwards them to the EIS library to compute the warp table. The warp table has been synchronized
 * with image raw before it is generated. The EIS library could obtain the gyro data and CMOS timing
 * information for the latest frame in external memory, but always keeps the whole frame
 * gyro / CMOS information in external memory. Meanwhile, the warp table being computed
 * is not for the latest frame but the oldest frame; this mechanism makes it possible to enable the EIS
 * algorithm to forsee future frame gyro data in order to help refine the warp table for the oldest frames.
 *
 * All information (image raw, 3A, and warp table) is combined into one batch of encode from raw (EFR) commands and sent to the
 * EIS effective channel to obtain the stablized result. There are some hard restrictions for both channels
 * if they are configured to perform EIS, such the same packing mode flag and the raw capture flag.
 * Refer to @ref eis_des_example for an intuitive understanding.
 *
 *
 * @subsection eis_spec 1.2. EIS Specification
 * <table>
 * <caption id="eis_spec_table">Table 1-1. EIS Specification.</caption>
 * <tr><th> Related Sector <th> Item <th align="left"> Specification Detail
 * <tr><td> Gyro <td> Data sample rate <td> Up to 2000 Hz
 * <tr><td rowspan="4"> Algorithm <td> X/Y/Z axis correction frequency <td> Up to 10 Hz
 * <tr>                           <td> X/Y axis correction coverage in percentage <td> Up to sensor coverage
 * <tr>                           <td rowspan="2"> Z axis correction coverage in degrees <br>(Highly depends on the EFL and margin from sensor) <td> 1. The larger margin with same EFL, the larger degree can correct.
 * <tr>                                                                                                                                         <td> 2. The larger EFL with same margin, the smaller degree can correct.
 * <tr><td> Lens <td> Effective focal length (EFL) correction coverage in um <td> 2000 um <= EFL <=15000 um
 * <tr><td rowspan="3"> VIN  <td> Resolution <td> 720p30 to 4KP60
 * <tr>                      <td rowspan="2"> VIN mode  <td> Supports rolling shutter sensor in <br>1. Linear mode<br>2. Fake linear mode<br>3. DCG HDR<br>4. Clear HDR (Sony sensor)
 * <tr>                                                <td> Supports global shutter sensor in linear mode
 * <tr><td rowspan="3"> IDSP <td> EIS delay count <td> [3, 30]
 * <tr>                      <td> Encode mode supported <td> 0, 5
 * <tr>                      <td> Supports multi-channel EIS <td> Both library and driver
 * <tr><td rowspan="2"> Advanced features <td> Lens geometric distortion correction <td> Rectilinear
 * <tr>                                 <td> Rolling shutter compensation <td> Caused by rolling shaking @ref eis_rolling_shaking
 * <tr><td> CPU <td> Occupation <td> TBD
 * </table>
 *
 * - - - -
 *
 * @section eis_implementation 2. Implementation
 * <br>This chapter provides important information on EIS.
 *     - Section @ref eis_rolling_shaking
 *     - Section @ref eis_pry_def
 *     - Section @ref eis_va_map
 *     - Section @ref eis_enc
 *     - Section @ref eis_warp_vector
 *     - Section @ref eis_build
 *     - Section @ref eis_pm
 *
 * @subsection eis_rolling_shaking 2.1 Rolling Shaking
 * Ambarella EIS supports rolling shaking in the pitch / yaw / rotate directions (refer to @ref eis_pry_def),
 * which is type of an irregular rolling shaking around the three axises of the camera coordinate
 * system. The gyro sensor is used to detect angular velocity but not linear velocity, <b>so if
 * the shaking direction is parallel to the horizontal axis (pitch axis) or vertical axis (yaw axis)
 * of the camera coordinate system (refer to the figure in Section 2.2 Definition of Pitch / Roll / Yaw),
 * Ambarella will not support it.</b>
 * @image html eis_shaking_type.png "Figure 2-1. Shaking Type."
 *
 * @subsection eis_pry_def 2.2 Definition of Pitch / Roll / Yaw
 * Before starting, ensure that there is a three-axis gyro sensor mounted on the main board.
 * Currently, the SDK supports Invensense MPU6000 / MPU6500 / MPU9250 sensors. For any questions
 * about gyro implementation, contact the Ambarella support team.
 * @image html eis_pry_def.png "Figure 2-2. Pitch / Roll / Yaw Definition."
 *
 * The rotation and axis follow the right-hand screw rule. As the CMOS sensor uses a
 * rolling shutter, an X-direction move on the sensor plane causes the sensor output image
 * to skew. If the skew is not corrected, the vertical lines will not be vertical.
 * If the camera moves up and down, the image will be stretched in the vertical direction.
 *
 * The gyro-based EIS algorithm can compensate for the stretch effect from the rolling shutter.
 *
 * Currently, the EIS module supports @b Pitch, @b Roll, and @b Yaw corrections all together. Further
 * updates and improvements will be added in the future.
 *
 * @subsection eis_va_map 2.3 Virtual Axis Mapping
 * By default, Ambarella's EIS algorithm assumes that the gyro axis is mounted as shown below.
 * @image html eis_gyro_axis.png "Figure 2-3. Default Gyro Axis EIS."
 *
 * However, if the gyro axis is not mounted as shown in the diagram above, gyro virtual mapping can be
 * set according to different mounting positions.
 * @image html eis_mount_pos.png "Figure 2-4. Custom Gyro Mounting Position."
 * In this case:
 * <br>X_mapped = +Y_Gyro
 * <br>Y_mapped = -X_Gyro
 * <br>Z_mapped = +Z_Gyro
 * <br>Users are expected to provide the details of the mapping information in the device trees (DTS) in the folder
 * `./ambarealla/board/cv22_walnut/bsp/cv22_walnut.dts`. For any other platform, there is always a
 * DTS file under `./bsp/`, which has the same name as the board.
 * <br>(Axis direction definition - 0:-X, 1:+X, 2:-Y, 3:+Y, 4:-Z, 5:+Z)
 * @code {.c}
 * gyro@0 {
 * .....
 * x_axis = <1>;
 * y_axis = <3>;
 * z_axis = <5>;
 * .....
 *};
 * @endcode
 *
 * @subsection eis_enc 2.4 Encode Mode
 * As described in @ref eis_intro, there are two channels (EIS effective channel and
 * EIS source channel) that serve in the current implementation. The EIS source channel is restricted to be
 * image pipeline only mode (mode 8) only, while the EIS effective channel can be configured to both high dynamic
 * range (HDR) line-interleaved mode (mode 5) and normal ISO mode (mode 0).  The EIS effective channel
 * can set channel rotate clockwise and horizontal/vertical flip at the same time, which could work together
 * with EIS.
 * <br><b>Mode 0 example:</b>
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_encode --show-vsrc-info
 *             [Vsrc information]:
 *              VIN Controller[8]:
 *                   vsrc[0]: imx274 (sensor_id: 0x3014, status: active, agc_db_step: 0x180000)
 * board # modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=1 custom_format_enable=1
 * board # modprobe eis_mc
 * board # modprobe gyro_icm20648_mc
 * board # test_aaa_service -a &
 * board # test_encode --enc-mode 0 --resource-cfg /usr/share/ambarella/lua_scripts/cv5_4k_linear_eis.lua --raw-capture 1 --enc-raw-rgb 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_efm -t 5 -i 0 -V 14
 * board # test_eis_warp --ch 1 -c 1000 -F 7200 -e 1920x1080
 * @endcode
 * @note
 * The <b>"sensor_id, agc_db_step, video_bits"</b> must read out from the master sensor channel.
 *
 * <b>Mode 5 example:</b>
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_encode --show-vsrc-info
 *             [Vsrc information]:
 *              VIN Controller[8]:
 *                   vsrc[0]: imx274 (sensor_id: 0x3014, status: active, agc_db_step: 0x180000)
 * board # modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=1 custom_format_enable=1
 * board # modprobe eis_mc
 * board # modprobe gyro_icm20648_mc
 * board # test_aaa_service -a &
 * board # test_encode --chan-vcap-mode-enable 1 --resource-cfg /usr/share/ambarella/lua_scripts/cv5_4k_linear_eis_mode5.lua --raw-capture 1 --enc-raw-rgb 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_efm -t 5 -i 0 -V 14
 * board # test_eis_warp --ch 1 -c 1000 -F 7200 -e 1920x1080
 * @endcode
 * @note
 * The <b>"sensor_id", "agc_db_step", and "video_bits"</b> must read out from the master sensor channel.
 *
 *
 * @subsection eis_warp_vector 2.5 Warp Vector
 * EIS correction is based on the warp engine, which is hardware that uses the warp vector to perform
 * real-time dewarp operations. The warp pipeline requires one horizontal vector and one vertical vector.
 * These horizontal and vertical warp vectors are calculated by the Ambarella EIS library.
 * <br>There are some limitations for the warp vector. In the horizontal or vertical warp stage, the
 * digital signal processor (DSP) divides the input of the vector map into grids and relocates the vertices of each grid based
 * on the vector. The DSP performs interpolation for the pixels that are not vertices of the grids.
 * <br><b>Maximum density</b>
 *   - The default maximum density of the horizontal and vertical map is 128 (H) by 96 (V).  Users can also
 * set them by an option "warp-table-density" of `test_eis_warp.c`. Smaller dimension requires larger grid spacing
 * but lower CPU loading for warp table computation.
 *
 * <br><b>Grid</b>
 *   - The grid size can be different in the horizontal and vertical map.
 *   - The grid width and height for the horizontal vector map must be 8 / 16 / 32 / 64 / 128 / 256 / 512.
 *   - The grid width for the vertical vector map must be 8 / 16 / 32 / 64 / 128 / 256 / 512.
 *   - The grid height for the vertical vector map must be 8 / 16 / 32 / 64 / 128 / 256 / 512.
 * <br><b>The vector map height can be greater than the main buffer height.</b>
 * <br>The redundant rows will be discarded. The advantage is that the user can see when warping
 * is performed on the main buffer, which does not have an appropriate grid division.
 * <br>For example, 1080 is not a multiple of 16 / 32 / 64 / 128. It is possible to set the main buffer
 * to 1920x1080 and the vector map to 1920x1088. The eight lines at the bottom of the grid will not be included
 * in the main buffer after warping.
 *
 * <br><b>Vector</b>
 * <br>The vector is in the format signed 12.4.
 * <br>For the horizontal map, negative vectors point to the right and positive vectors point to the left.
 * <br>For the vertical map, negative vectors point downwards and positive vectors point upwards.
 * @image html eis_vertical_vector.png "Figure 2-5. EIS Vertical Vector."
 * @image html eis_horizontal_vector.png "Figure 2-6. EIS Horizontal Vector."
 *
 * @subsection eis_build 2.6 Building
 * Use the following steps to build the EIS as well as the gyro drivers. Proceed with the unit
 * test @a test_eis_warp.
 *
 * @subsubsection eis_build_board 2.6.1 Board
 * Turn <b>SW1 (1-4)</b> off on the CV5 Timn or CV52 Crco evaluation kit (EVK) board. Enable the serial peripheral interface (SPI) with the steps below
 * in order for gyro INT and SPI 1 to function. @ref cv5_timn_imu_switch
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 * [*] bootmenu@virtual (boot)  --->
 *      [*]   boot (boot)  --->
 *           Bootloader  --->
 *              Ambarella Firmware Configuration  --->
 *                 SPI1 and GPIO(69-71) Selection (SPI1)  --->
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *  meta-ambabsp --->
 *     recipes-bsp --->
 *        boot (meta-ambabsp/recipes-bsp/boot)  --->
 *           Bootloader  --->
 *              Ambarella Firmware Configuration  --->
 *                 SPI1 and GPIO(69-71) Selection (SPI1)  --->
 * @endcode
 * For the switch and jumper information on the CV72 GA EVK board, refer to @ref cv72_ga_imu_switch.
 *
 * @subsubsection eis_build_drv 2.6.2 Driver
 * EIS functions with the image audio video (IAV) driver, as well as EIS and gyro. Currently, InvenSense's gyro
 * sensor ICM20648 is welded on the CV5x EVK and ICM42670 is welded on the CV72 GAGE EVK.
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *    drv_modules  --->
 *       platform  --->
 *          [*] kernel-module-eis-mc (drv_modules/platform/eis)
 *          [*] ambeis-header (drv_modules/platform/eis)
 *              gyro  --->
 *                [*] kernel-module-icm20648 (drv_modules/platform/gyro/icm20648)
 *                [*] kernel-module-icm42670 (drv_modules/platform/gyro/icm42670)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *  meta-ambabsp --->
 *     recipes-gyro --->
 *        [*] kernel-module-icm20648 (drv_modules/platform/gyro/icm20648)
 *        [*] kernel-module-icm42670 (drv_modules/platform/gyro/icm42670)
 * @endcode
 *
 * @subsubsection eis_build_test 2.6.3 Unit test
 * Enable "Configure Ambarella EIS library" while compiling EIS.
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *     prebuild  --->
 *        library  --->
 *           [*] prebuild-eis (prebuild/library/eis/dsp_v6)
 *           [*]   eis-test (prebuild/library/eis/dsp_v6)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *   meta-ambalib  --->
 *      recipes-prebuild  --->
 *         [*] prebuild-eis (meta-ambalib/recipes-prebuild/prebuild-eis)
 *   meta-ambaapp  --->
 *      recipes-test  --->
 *         [*] eis-test (meta-ambaapp/recipes-test/eis-test)
 * @endcode
 *
 *@subsubsection eis_build_iav_mem 2.6.4 IAV Memory --- IK Buffer Size
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0x1000000) IAV IMG IK CFG Buffer Size
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *   meta-ambabsp  --->
 *      recipes-video  --->
 *         -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)  --->
 *             (0x1000000) IAV IMG IK CFG Buffer Size
 * @endcode
 *
 *
 * @subsection eis_pm 2.7 EIS with Privacy Mask
 * For the CV72 platform, the new parameter "is_post_warp_pm" in channel configuration
 * is designed to enable or disable privacy masks at the post-warp stage for EIS effect channels. This
 * means that privacy mask operations can be performed immediately after the EIS warp table takes effect. Note that this
 * feature is only available for CV72, and is not supported CV5, CV52, or any other platform.
 *
 * - - - -
 *
 * @section eis_design 3. Design
 * This chapter provides information on EIS design. <b>If users require any help
 * with EIS case design or evaluation on the CV5 / CV52 / CV72 platform, contact the Ambarella
 * SDK support team.</b>
 * EIS is a real-time task, which requires a high priority to run. When the user enables EIS,
 * the priority of the process must be maximized.
 *     - Section @ref gyro_dev_tree
 *     - Section @ref eis_imu
 *     - Section @ref eis_sensor
 *     - Section @ref eis_window
 *     - Section @ref eis_filter_mode
 *     - Section @ref eis_des_lens
 *     - Section @ref eis_rt_change
 *     - Section @ref eis_des_example
 *
 *
 * @subsection gyro_dev_tree 3.1 Device Tree Configuration
 *
 * <br>The figure below shows what type of multi-VIN cases that the current EIS module supports.
 * Note that one IMU device can only serve one VIN source at most.
 * @image html multi_chan_eis_typical_cases.png "Figure 3-1. Typical Cases."
 * Clarify the relationship between the gyro device and the <b>channel map</b>. Then, fill it in the
 * DTS, together with the <b>VIN source ID</b> and the <b>VIN controller ID</b>.
 * Refer to the example below. The EIS driver possesses all registered information and manages data
 * flow to ensure the pass of the corresponding group of gyro raw data to the application for warp
 * table computation.
 * @code {.c}
 * gyro@0 {
 * compatible = "ambarella,gyro";
 * reg = <0>;
 * spi-max-frequency = <20000000>;
 * spi-cpha;
 * spi-cpol;
 * x_axis = <1>;
 * y_axis = <3>;
 * z_axis = <5>;
 * vinc_id = <0>;
 * vsrc_id = <0>;
 * bus_id = <1>;
 * cs_id = <0>;
 * channel_map = <1>;
 * irq-gpio = <&gpio 31 0>;
 * };
 * @endcode
 *
 *
 * @subsection eis_imu 3.2 IMU Selection
 * Currently, the SDK supports the following IMU sensors.
 * <table>
 * <caption id="gyro_list">Table 3-1. Supported IMU Part Number.</caption>
 * <tr><th> IMU Part Number    <th> Vendor <th align="left"> Last Modified
 * <tr><td> MPU9250            <td> InvenSense  <td> 20161122
 * <tr><td> MPU6000            <td> InvenSense  <td> 20161122
 * <tr><td> MPU6500            <td> InvenSense  <td> 20161122
 * <tr><td> ICM20600           <td> InvenSense  <td> 20201130
 * <tr><td> ICM20648           <td> InvenSense  <td> 20210701
 * <tr><td> ICM40608           <td> InvenSense  <td> 20210726
 * <tr><td> ICM42605           <td> InvenSense  <td> 20210427
 * <tr><td> ICM42670           <td> InvenSense  <td> 20221027
 * <tr><td> ICG20660           <td> InvenSense  <td> 20161122
 * <tr><td> BMI270             <td> Bosch       <td> 20210422
 * <tr><td> BMI160             <td> Bosch       <td> 20210429
 * <tr><td> LSMD6SR            <td> STMicroelectronics  <td> 20220520
 * </table>
 *
 * The supported IMU sensor list is supposed to be kept updating, Ambarella SDK team removes the ones
 * out of stock and adds newly lauched IMU selectively.  Feel free to contact Ambarella and share the sensor
 * list for further cooperation.
 *
 * @subsection eis_sensor 3.3 CMOS Sensor
 * Ambarella Cooper SDK now supports most of the CMOS sensor with EIS. Typically, Ambarella SDK team
 * collects customer feedbacks and requests from the market, and then make own decision of plan and schedule to
 * support the new CMOS sensors gradually. To confirm whether a specific sensor is capable of working for
 * EIS, either an RGB sensor or a thermal sensor, the following information needs to be accurately addressed:
 * - Video blank time
 * - Line time
 * - Pixel unit size
 * - Rolling shutter or global shutter
 * - Whether there is latency costed by DSP inside sensor before generate the frame to SoC
 * - Thermal sensor (time constant); sampling of the temperature

 * <b>HDR Mode</b>
 * <br> Currently, the EIS algorithm does NOT function with DOL-HDR mode, <b>but it does function with DCG-HDR
 * mode (such as ov2775 DCG-HDR mode)</b>. In theory, DOL-HDR sets different exposure configurations for long
 * and short frames before blending. DCG-HDR sets the same exposure configuration but different AE gains for
 * two frames. Different exposure times may cause some trailing smears when EIS is functioning for quick vibration.
 * Users must develop their own EIS algorithm for DOL-HDR input.
 * <br>Supported HDR modes are listed as below, and the option "hdr-mode" of test_eis_warp_sc / test_eis_warp_mc
 * is designed for the selection.
 * - Rolling shutter sensor in linear mode
 * - Rolling shutter sensor in (2x HDR) faking linear mode
 * - Global shutter sensor in linear mode
 *
 * <b>Shutter time</b>
 * <br>Ambarella recommends setting a maximum shutter time of less than 1/60 s (refer to @a test_aaa_service). However,
 * this is a suggestion and is not required for a good EIS correction effect. Different conditions may
 * be set with different values to obtain better correction results.
 *
 * @subsection eis_window 3.4 Window
 * @subsubsection eis_res_vin 3.4.1 VIN Window
 * Ambarella Cooper SDK now has most of the CMOS sensor with EIS support. Typically, Ambarella SDK team
 * collect customer feedbacks and requests from the market, and then make own decision of plan and schedule to
 * support the new CMOS sensors gradually. No hard restriction to VIN window size from EIS requirements.
 * <table>
 * <caption id="gyro_list">Table 3-2. Typical Resolution.</caption>
 * <tr><th> CMOS Sensor    <th> Resolution
 * <tr><td> OS05A10        <td> 2592x1944
 * <tr><td> OS08A10        <td> 3840x2160
 * <tr><td> IMX335         <td> 2592x1944
 * <tr><td> IMX274         <td> 3840x2160
 * <tr><td> IMX334         <td> 3840x2160
 * <tr><td> IMX678         <td> 3840x2160
 * <tr><td> IMX178         <td> 3072x2048
 * </table>
 *
 * @subsubsection eis_res_eis 3.4.2 EIS Window
 * The EIS window is the actual output of the EIS correction algorithm. It can be set with the option
 * <b>"eis-output"</b> (see @ref eis_ex_4 in @ref eis_des_example). In the default setting, the EIS window
 * size is equal to the main buffer size.
 * @image html eis_eis_window.png "Figure 3-2. VIN Margin for EIS without Option @a 'eis-output'."
 * In order for EIS to function well, users must ensure there is sufficient margin between the EIS
 * window and the VIN window. For example, if VIN window size is 2304x1536 and the EIS window size is
 * 1920x1080, the vertical margin = (1536-1080) / 2 /1080 = 21%. There is no mandatory requirement for
 * the margin, but the larger margin is, the larger vibration angle can be corrected. It is possible
 * to roughly convert the margin size to the angle value in radian:
 * \f[
     focal_length = \frac{EFL(mm)}{pixel_cell_unit_size(mm)}
     angle (radian) = \frac{V_margin(pixel)}{focal_length}
 * \f]
 *
 * <br>This EIS window size can be smaller than the main buffer size. Therefore, there is no limitation
 * that the main buffer size should be smaller than the VIN size. The EIS warp table is capable of taking
 * the upscale into the computation.
 *    - Pitch correction requires a vertical margin only
 *    - Yaw correction requires a horizontal margin only
 *    - Roll correction requires both horizontal and vertical margins
 * @image html eis_vin_margin.png "Figure 3-3. VIN Margin for EIS with Option @a 'eis-output'."
 * <b>ROI Center Control</b>
 * <br>By default, the EIS output window is located in the center position of the VIN domain. This means that
 * the V-margin at the top and bottom are the same, and the H-margin at the left and right are the same.
 * Using the center point of the EIS output window as a parameter specified in the VIN domain, users can
 * manually change the left / right and top / bottom margins. See the figure below.
 * @image html eis_roi_center.png "Figure 3-4. EIS Region of Interest Center Control."
 *
 *
 * @subsection eis_filter_mode 3.5 EIS Filter Mode
 * From the perspective of image stabilization applications, EIS is now a basic feature for camera
 * products, such as body-worn cameras and internet protocol cameras (IPCs)). Meanwhile, Ambarella
 * EIS made some changes according to the classified market demands.  A new developed option "filter-mode"
 * is added to ensure EIS correction can output the best result under different situations.
 *  | Filter Mode   | Application |
 *  | :-----------: | :---------: |
 *  | Action mode  | Body-worn camera |
 *  | Stationary mode  | IPC |
 *  | Customized Mode  | Customized filter design, bypass Amba EIS filter.|
 * Below are detailed introductions for the above filter modes.
 *      - Action mode: covers body-worn cameras with large amplitudes and small vibration frequencies.
 * The final stabilized video is not required to remain stationary, but must have a smooth effect for all types
 * of motion (walking, running, and skating).
 *      - Stationary mode: covers most IPC products, which are mounted to a fixed location without
 * any movement. Generally, stationary mode functions for vibrations that are smaller in amplitude
 * but have larger vibration frequency.
 *      - Customized filter mode.  Customers designed their own filter and bypassed the EIS library internal filters,
 * please set filter mode as EIS_FILTER_MODE_CUSTOMIZED in @a test_eis_warp_sc/test_eis_warp_mc.
 *
 * @subsection eis_des_lens 3.6 Lens
 * Currently, the EIS library only supports prime lenses. Even if a distorted lens is in use, the jelly effect in
 * both the vertical and horizontal directions will be removed.<br>For zoom lenses, users are required to know the exact
 * EFL and configure EFL to the library in real time.<br>For TELE lens which EFL is <b>larger than 15 mm</b>, Ambarella
 * does not recommend enabling EIS, as the requirement for the margin or field of view (FoV) loss is much larger than
 * what users may expect.
 *
 * <b>EIS with Lens Distortion Correction (LDC)</b>
 * <br>When implementing EIS with a distorted lens, Ambarella supports enabling the feature "EIS + LDC", which simultaneously
 * performs EIS and removes distortion. In terms of LDC, users can also convert the distortion
 * table to a lens data file in binary format for more-accurate distortion correction. The tool "lens_data_tool"
 * is used to convert the lens distortion table into an EIS library readable configuration binary. It is located
 * in the SDK folder `./ambarella/prebuild/ambarella/library/lens`.
 *
 *
 * @subsection eis_rt_change 3.7 Real Time Update
 * EIS functions for different vibration conditions, and there are no intelligent processes to
 * change key parameters for the stablization algorithm. However, the EIS library is designed with
 * an interface that enables EIS applications to change their EIS parameters in real time.
 * <br>Refer to the definition of the structure "eis_rt_info_t", which is designed for real-time communication
 * between the library and the application. The EIS application registers one callback function,
 * <b>get_eis_stat_rt</b>, which recieves gyro raw data from the EIS driver and incorporates the changed
 * EIS parameters wrapped in "eis_rt_update_t" into the algorithm. The
 * parameters "shutter_in_ms", "shutter_short_in_ms", and "sync_hw_pts" are read directly from the
 * IAV driver. Users can change <b>efl_in_um</b> for zoom lenses, <b>filter_scale</b> for
 * different vibration frequencies, <b>ldc_enable</b> to remove distortion,
 * <b>res_fov_vin</b> to hange FoV function when EIS is off, <b>VIN frame rate</b> in high
 * precision, and other parameters from the structure "debug_param_rt".
 * @code {.c}
 * typedef struct {
 * 	u8 channel_id;
 *	u8 update_efl_flag : 1;
 *	u8 update_fps_flag : 1;
 *	u8 reserved1 : 6;
 *	u8 reserved0[2];
 *	u32 sync_hw_pts;
 *	float shutter_in_ms;
 *	u32 efl_in_um;
 *	u32 fps_hp;
 *	float vb_in_ms;
 *	void *filter_param;
 *	u32 reserved2[6];
 * } eis_rt_info_t;
 * @endcode
 *
 *
 * @subsection eis_des_example 3.8 Example
 * When EIS is enabled, pitch / yaw / roll correction can be performed simultaneously.
 * @note
 * The parameters below must be set properly.
 * <br>EIS source channel:
 * <br>@b "raw_feed_frame_num" The capacity of the caching frame in external memory
 * <br>@b "raw_cached_items" Active cached frame number
 * <br>@b "chan_input_src" Set to 1 to save IDSP performance
 * <br>EIS effective channel:
 * <br>@b "lens-warp" Set to 1
 * <br>@b "max_padding_width" Specify the maximum padding width for stitched cases
 * <br>@b "raw_feed_frame_num" Set to the same as that in the EIS source channel
 * <br>@b "eis_delay_count" Set >= 3; only required in the EIS effective channel
 *
 * @subsubsection eis_ex_1 3.8.1 IMX274 + EVK + Enable "--eis-output"
 * If users require both a larger stream resolution and a larger correction range, the parameter
 * "--eis-output" can be used to set the EIS output size with a 16-pixel aligned width and an 8-pixel aligned
 * height; the resolution must be smaller than the main buffer size. The EIS algorithm can
 * upscale the correction content from the "--eis-output" size to the main buffer, which may result in
 * resolution loss due to upscaling.
 * <br>Example 4: Enable "--eis-output" Option
 * @code {.c}
 * board # init.sh --na
 * cv5x   # modprobe imx274_mipi vinc_id=8 bus_id=3
 * cv7x   # modprobe imx274_mipi vinc_id=8
 * board # test_encode --show-vsrc-info
 *             [Vsrc information]:
 *              VIN Controller[8]:
 *                   vsrc[0]: imx274 (sensor_id: 0x3014, status: active, agc_db_step: 0x180000)
 * board # modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=1 custom_format_enable=1
 * board # modprobe eis_mc
 * cv5x   # modprobe gyro_icm20648_mc
 * cv7x   # modprobe gyro_icm42670_mc
 * board # test_aaa_service -a &
 * board # test_encode --enc-mode 0 --resource-cfg /usr/share/ambarella/lua_scripts/cv5_4k_linear_eis.lua --raw-capture 1 --enc-raw-rgb 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_efm -t 5 -i 0 -V 14
 * board # test_eis_warp --ch 1 -c 1000 -F 7200 -e 1920x1080
 *      --> enable (1), disable (0):
 *      --> Type 2 to enable EIS correction for channel 1
 * @endcode
 * @note
 * The <b>"sensor_id", "agc_db_step", and "video_bits"</b> must read out from the master sensor channel.
 *
 * @subsubsection eis_ex_2 3.8.2 IMX274 + EVK + Dual VIN EIS
 * <br>Example 5: Multi-VIN EIS
 * Currently, the CV5 / CV52 / CV72 EVKs cannot verify this feature, as there is only one IMU mounted,
 * which cannot serve multiple video sources. Another video source demands an IMU hardware
 * registered in the device tree. The IMU and video source must match one-to-one.
 * @code {.c}
 * board # init.sh --na
 * board # modprobe imx274_mipi vinc_id=0xf08
 * board # test_encode --show-vsrc-info
 * [Vsrc information]:
 * VIN Controller[0]:
 *       vsrc[1]: imx274 (sensor_id: 0x3014, status: active, agc_db_step: 0x180000)
 * VIN Controller[8]:
 *       vsrc[0]: imx274 (sensor_id: 0x3014, status: active, agc_db_step: 0x180000)
 *
 * board # modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=2 custom_format_enable=1
 * board # modprobe eis_mc
 * cv5x   # modprobe gyro_icm20648_mc chan_map_active=0x5
 * cv7x   # modprobe gyro_icm42670_mc chan_map_active=0x5
 * board # test_aaa_service -a &
 * board # test_encode --enc-mode 0 --resource-cfg /usr/share/ambarella/lua_scripts/cv5_dual_vin_eis.lua --raw-capture 1 --enc-raw-rgb 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_efm -t 5 -i 0 -V 14
 * board # test_efm -t 5 -i 1 -V 15
 * board # test_eis_warp -c 1000 --ch 1 -F 7200 -e 1920x1080 --ch 3 -F 3400 -e 1920x1080
 *      --> enable (1), disable (0):
 *      --> Type 2 to enable EIS correction for channel 1
 * @endcode
 * @note
 *  - The <b>"sensor_id, agc_db_step, video_bits"</b> must read out from the master sensor channel.
 *
 * @subsubsection eis_ex_3 3.8.3 IMX274 + EVK + Enable EIS and LDC
 * If users design a case with a distorted lens, and require a result combining LDC and EIS, enable the
 * flag "ldc".
 * <br>Example 6: Enable EIS + LDC
 * @code {.c}
 * board # init.sh --na
 * cv5x   # modprobe imx274_mipi vinc_id=8 bus_id=3
 * cv7x   # modprobe imx274_mipi vinc_id=8
 * board # test_encode --show-vsrc-info
 *             [Vsrc information]:
 *              VIN Controller[8]:
 *                   vsrc[0]: imx274 (sensor_id: 0x3014, status: active, agc_db_step: 0x180000)
 * board # modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=1 custom_format_enable=1
 * board # modprobe eis_mc
 * cv5x   # modprobe gyro_icm20648_mc
 * cv7x   # modprobe gyro_icm42670_mc
 * board # test_aaa_service -a &
 * board # test_encode --enc-mode 5 --resource-cfg /usr/share/ambarella/lua_scripts/cv5_4k_linear_eis.lua --raw-capture 1 --enc-raw-rgb 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_efm -t 5 -i 0 -V 14
 * board # test_eis_warp --ch 1 -c 1000 -F 7200 -e 1920x1080 --gdc 1
 *      --> enable (1), disable (0):
 *      --> Type 2 to enable EIS correction for channel 1
 * @endcode
 * @note
 * The <b>"sensor_id", "agc_db_step", and "video_bits"</b> must read out from the master sensor channel.
 *
 *
 * @subsubsection eis_ex_4 3.8.4 IMX274 + EIS + Rotation
 * <br>Example 7: Enable EIS + Rotation
 * @code {.c}
 * board # init.sh --na
 * cv5x   # modprobe imx274_mipi vinc_id=8 bus_id=3
 * cv7x   # modprobe imx274_mipi vinc_id=8
 * board # test_encode --show-vsrc-info
 *             [Vsrc information]:
 *              VIN Controller[8]:
 *                   vsrc[0]: imx274 (sensor_id: 0x3014, status: active, agc_db_step: 0x180000)
 * board # modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=1 custom_format_enable=1
 * board # modprobe eis_mc
 * cv5x   # modprobe gyro_icm20648_mc
 * cv7x   # modprobe gyro_icm42670_mc
 * board # test_aaa_service -a &
 * board # test_encode --enc-mode 5 --resource-cfg /usr/share/ambarella/lua_scripts/cv5_4k_linear_eis_rotate.lua --raw-capture 1 --enc-raw-rgb 1 --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_efm -t 5 -i 0 -V 14
 * board # test_eis_warp --ch 1 -c 1000 -F 7200 -e 1920x1080
 *      --> enable (1), disable (0):
 *      --> Type 2 to enable EIS correction for channel 1
 * @endcode
 *
 * - - - -
 *
 * @section eis_development 4. EIS Development
 * Refer to @ref test_eis_warp.c to learn how to develop user applications.
 *  - Confirm the EIS effective channel and the EIS source channel at the system level
 *  - Configure warp parameters for EIS: lens focal length in um; @ref eis_res_eis "eis output window";
 * @ref eis_des_lens "enable rectilinear"; restore to the VIN FoV when EIS is disabled
 *  - Set the log level for the EIS library.
 *  - Initialize the EIS library with filter setup, callback function, gyro, and CMOS sensor configuration
 * for the EIS effective channel
 *  - Compute the initial location of gyro raw data
 *  - If users are required to update parameters from "eis_rt_info_t" in real time, refer to the function "get_eis_stat_rt"
 *  - Enable or disable EIS by calling "eis_open()" or "eis_close()"
 *  - Ensure that the EIS process is alive at all times
 *
 * - - - -
 *
 * @section eis_tuning 5. Tuning
 * In the EIS fine-tuning stage, users must pay attention to items below and check them one by one.
 *  - Section @ref gyro_tuning
 *  - Section @ref lens_tuning
 *  - Section @ref timing_tuning
 *  - Section @ref margin_tuning
 *  - Section @ref filter_mode_tuning
 *  - Section @ref filter_scale_tuning
 *  - Section @ref debug_method
 *
 * @subsection gyro_tuning 5.1 Gyro
 *     - <b>The location must be as close as possible to the CMOS image sensor.</b>
 *     - <b>Virtual axis mapping:</b> @ref eis_va_map
 *     - <b>Keep the camera stationary for 1~2 seconds to remove white noise data.</b>
 *     - <b>A larger ODR requires longer calculation time.</b>
 *
 * @subsection lens_tuning 5.2 Lens
 *     - <b>EFL range [2000um, 15000um]</b> @ref eis_spec
 * @code
 * board# test_eis_warp --ch 1 -c 1000 -F 2000
 * @endcode
 *     - <b>Real-time update EFL for zoom lens:</b>
 *        Performed through the function "get_eis_stat_rt" (amba_eis_stat_t* eis_stat, void *rt_info), (similar to the shutter time update).
 *     - <b>Fisheye lens</b>
 *        <br>Users must specify the full FoV to better remove the jelly effect.
 * @code
 * board# test_eis_warp --ch 1 -c 1000 -F 2000 --fov 180
 * @endcode
 *        Users must specify the lookup table (LUT) table for more-accurate care of the distortion information.
 * @code
 * board# test_eis_warp --ch 1 -c 1000 -F 2000 --fov 180 --lut-bin lens_file
 * @endcode
 *     - <b>Enable rectilinear:</b>
 * @code
 * board# test_eis_warp --ch 1 -c 1000 -F 3000 --ldc 1
 * @endcode
 *     - <b>Set the optical center:</b>
 * @code
 * board# test_eis_warp --ch 1 -c 1000 -F 3000 --optical-center axb
 * @endcode
 *
 * @subsection timing_tuning 5.3 Timing
 *     - <b>Shutter:</b> @ref eis_des_shutter
 *     - <b>EIS delay count:</b> @ref eis_delay_count
 *
 * @subsection margin_tuning 5.4 Margin
 *     - <b>EIS output window:</b>  @ref eis_res_eis
 * @code
 * board# test_eis_warp --ch 1 -c 1000 -F 3000 -e 1280x720
 * @endcode
 *     - <b>Region of interest (ROI) center:</b> @ref eis_res_eis
 * @code
 * board# test_eis_warp --ch 1 -c 1000 -F 3000 -e 1280x720 --roi-center 1024x864
 * @endcode
 *
 * @subsection filter_mode_tuning 5.5 Filter Mode
 *     - <b>Action mode and stationary mode.</b>  @ref eis_filter_mode
 * @code
 * board# test_eis_warp --ch 1 -c 1000 -F 3000 --filter-mode 1
 * @endcode
 *
 * @subsection filter_scale_tuning 5.6 Filter Scale
 *     - <b>Frequency</b>
 *     - <b>EFL</b>
 *     - <b>Artifacts, abnormal shift</b>
 *     - <b>Avoid significant change in a real-time update</b>
 *
 * @subsection debug_method 5.7 Debug Method
 *     - <b>Dump the dmesg log to check if a EIS sync failure occurred.</b>
 *        <br>Ex: [123.456] #iav_error# Fail to update eis sync cmd!
 *     - <b>See the library log via option "-d 2".</b>
 * @code
 * board# test_eis_warp --ch 1 -c 3000 -F 8000 -e 1280x720 -d 2
 * @endcode
 *     - <b>Dump gyro raw data via option "-s".</b>
 * @code
 * board# test_eis_warp --ch 1 -c 3000 -F 8000 -e 1280x720 -s /tmp/gyro_raw
 * @endcode
 *
 *
 * - - - -
 *
 * @section eis_qa 6. FAQ
 * This chapter provides frequently asked questions (FAQs) and answers that are specific to EIS tuning. More
 * information will be added in the future.
 *
 * @subsection eis_qa_q1 Question 1. How can users ensure that the gyro is functioning as per the design?
 * @b Answer:   Ensure that the EIS library obtains the correct group of pitch / yaw / roll angular
 *              velocities. The three gyro axes should be vertically or horizontally aligned with
 *              the optical axis in the lens and the sensor plane. Further, virtual axis
 *              mapping (@ref eis_va_map) should be configured in the DTS file. More
 *              checking points mentioned will be added in future.
 *
 * @subsection eis_qa_q2 Question 2. Why is the EIS effect not as good as the EVK reference design solution?
 * @b Answer:   The EIS result may be affected by many factors, including the lens focal length,
 *              gyro data output frequency, gyro data filter design, and more. Different platforms may
 *              encounter slightly different EIS results. Below are some key points:
 *                   - Refer to the specific lens datasheet as the lens focal length
 *                     parameter is very important.
 *                   - The EIS algorithm functions with frequencies
 *                     larger than 500Hz for 30fps and 1000HZ for 60fps. Ensure that the gyro raw data
 *                     number of one frame is larger than 16.
 *                   - The gyro sensor should be mounted as close as possible to the image sensor.
 *                   - One gyro interrupt PIN must be used to export gyro data periodically in the circular buffer.
 *                   - The gyro interrupt is configured as @b falling-trigger or @b rising-trigger in the driver.
 *                   - Shutter time must be tuned correctly, as mentioned in @ref eis_des_shutter
 *
 * @subsection eis_qa_q3 Question 3. Does EIS function with the LDC feature?
 * @b Answer:   Yes, Ambarella supports performing image stablization simultaneously with removing the distortion
 *              from the lens. Users can refer to example @ref eis_ex_2.
 *
 * @subsection eis_qa_q4 Question 4. Does EIS function with the HDR feature?
 * @b Answer:   Currently, the EIS algorithm does NOT function with DOL-HDR mode, <b>but it does function with DCG-HDR
 *              mode (such as ov2775 DCG-HDR mode)</b>. In theory, DOL-HDR sets different exposure configurations
 *              for long and short frames before blending. DCG-HDR sets the same exposure configuration
 *              but different AE gains for two frames. Different exposure times may cause some trailing smears
 *              when EIS is functioning for quick vibration. Users must develop their own EIS algorithm
 *              for DOL-HDR input.
 *
 * @subsection eis_qa_q5 Question 5. Does EIS function with the fisheye dewarp feature?
 * @b Answer:   No. EIS is only supported in encode modes 0 and 5 (refer to @ref eis_enc), while fisheye dewarp
 *              is only supported in encode mode 1. From the IDSP perspective, different pipelines and
 *              different DSP commands are implemented in different encode modes.
 *
 * @subsection eis_qa_q6 Question 6. Which gyro sensor is supported? If there is a new gyro sensor not included in the list, can it be supported ?
 * @b Answer:  The IMU sensor supported by Ambarella SDK is mainly from InvenSense; users can refer to
 *             @ref eis_imu. If users require support for another IMU sensor, they can contact the Ambarella SDK team.
 *
 * @subsection eis_qa_q7 Question 7. How do users define the size of the margin between the VIN window and the EIS output window?
 * @b Answer:  In order for EIS to function well, users must ensure that the VIN size has a sufficient margin between
 *             the EIS output window and the VIN window. The larger the amount of margin is left, the larger the range EIS can correct.
 *             The size of the margin depends on the active cases and therefore, the margin will differ. For products such as
 *             body-worn cameras that have large shaking amplitude, EIS requires 40% to 60%. For IPC products with
 *             small shaking amplitude, 30% to 40% is sufficient.
 *
 * @subsection eis_qa_q8 Question 8. What is the process to re-configure the EIS library when the VIN resolution or frame rate changes?
 * @b Answer:  Follow the steps below for EIS to run as expected when there are changes to the VIN resolution or fps.
 *             -# <b>Disable</b> the EIS function.
 *             -# Prepare new values for the corresponding parameters, then call <b>eis_setup(...)</b> to configure the
 *                parameters for the EIS library.
 *             -# <b>Re-enable</b> the EIS function.
 *
 * @subsection eis_qa_q9 Question 9. When EIS is enabled, why does DPTZ type I fail?
 * @b Answer:  DPTZ I performs crop / scale functions from VIN to the main buffer. Those parameters are not effective
 *                  because the EIS library computation outputs related warp tables. The dummy window
 *                  determines the active area from VIN, which is exactly the DPTZ I parameter.
 *
 *
 * @subsection eis_qa_q10 Question 10. Does Ambarella support IMU sensors that are not in included in the standard SDK?
 * @b Answer:  Ambarella recommends using the IMU sensors that are already supported in the SDK, as new IMU sensors
 *             would require extra support for drivers and verification. Further, new IMU sensor may entail extra support costs.
 *
 * @subsection eis_qa_q11 Question 11. Does EIS require calibration?
 * @b Answer:  EIS does not currently require calibration.
 *
 *
 * @subsection eis_qa_q12 Question 12. What are the steps to configure the main buffer size of the EIS source channel and the EIS effective channel?
 * @b Answer:  To obtain lower bandwidths and better performance for the EIS source channel with no impact on the real-time
 *             3A statistics, the main buffer width of the EIS source channel must be as a
 *             quarter of the VIN width (1/4). Users must configure the option `chan_input_src = 1` and
 *             set the main buffer size of the EIS effective channel to be the same as the VIN size.
 *             In the Lua file for the resource-cfg of test_encode, leave the input window as 0 for
 *             both channels, which permits the IAV driver to take the default operation.
 *
 * @subsection eis_qa_q13 Question 13. How do you know the maximum correction angles with specific EIS output window size?
 * @b Answer:  Please refer to the section @ref eis_res_eis.
 *
 *
 * @subsection eis_qa_q14 Question 14. Why does EIS cache a certain number of frames in external memory?
 * @b Answer:  The EIS algorithm can fetch gyro samples in the future frames starting from the current frame, which
 *             allows the algorithm to adjust warp table and input window location in advance to make it smoothly pass
 *             the large amplitude vibration.
 *
 * - - - -
 *
 * @section sec_eis_api 7. EIS Application Programming Interface
 * Visit the following link to get details of the application programming interface (API) functions.
 *      - @ref eis-api-api explains API functions.
 *      - @ref eis-helper shows related macros and enumerations.
 *      - @ref eis-struct shows related structures.
 *
 * - - - -
 *
 * @section sec_eis_lic 8. License
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
 * this Software to Ambarella International LP
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
 * @defgroup eis-api EIS Library API
 * @brief EIS Library API, in file lib_eis.h
 */
/*!
 * @defgroup eis-api-api EIS Library API Details
 * @ingroup eis-api
 * @brief EIS Library API, in file lib_eis.h
 */
/*!
 * @defgroup eis-helper EIS Library API Helper
 * @ingroup eis-api
 * @brief EIS Library Api Helper: Enumeration and Macros, in file lib_eis.h
 *
 */
/*!
 * @defgroup eis-struct EIS Library Struct Helper
 * @ingroup eis-api
 * @brief EIS Library Api Struct: Struct, in file lib_eis.h
 *
 */


/*!
 * @example test_eis_warp.c
 * This is a source code file of test_eis_warp.
 *
 */
/*!
 * @file doc_lib_image_flow.h
 * @brief This is a .h file for doxygen document system
 * @version 0.0.1
 * @date 2024-01-24
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
 * @page page_lib_img_flow_doc Image Flow Library API
 *
 * @section img_flow_history 0. Revision History
 * <table>
 * <caption id="img_flow_rev_history"></caption>
 * <tr><th>Version<th> Updated Date<th align="left"> Modification
 * <tr><td>0.0.1<td>20240124<td> Initial Version
 * </table>
 *
 * - - - -
 *
 * @section img_flow_introduction 1. Introduction
 * The img_flow library is a AE / AWB / ADJ (3A) middleware that is responsible for connecting
 * image signal processor (ISP) library and 3A related upper level applications (apps).
 * To address the increasingly strong demand for the requests below, Ambarella brings
 * up this new method to run AAA flow:
 *  - No need to port the 3A flow source code from the sample code
 *  - No need to refactor users' own 3A flow after the 3A algorithm is upgraded
 *  - To support multiple video input (multi-VIN) cases better for different VIN types
 *  - Assemble all functions and testing / tuning tools into one test application
 *
 * In the diagram as shown below, the Level 3 is the middle layer that sits between
 * the kernel layer and the application layer. The img_flow library and ISP library are at the same level.
 * The ISP libraries include img_algo and img_dsp, which provide low / high level interfaces
 * to img_flow library.
 * @image html ambarella_system_diagram_1202x491.png "Figure 1-1. System Diagram."
 *
 * To make it easier to use the img_flow library, Ambarella provides
 * an application named <em>test_aaa_service</em> that calls the library to run 3A flow.
 * Together with the application <em>test_aaa_service</em>, the image library can do these things listed below:
 * - Contain basic 3A flow
 * - Start / stop the 3A flow with Netlink
 * - Load image quality (IQ) parameters adaptively for multi-VIN case
 * - Start / stop Amage server
 * - Control 3A with interactive menu by calling image flow APIs
 * - Load calibration data, including automatic white balance (AWB) / lens shading / BPC / CA
 * - Load product_config lua for a particular product
 * - Support smooth IQ transition from Ambarella real-time operating system (AMRTOS) fastboot to Linux 3A
 * - Support infrared (IR) process
 * - Support slow shutter process
 * - Embody automatic exposure（AE）timing tool
 * - Embody sample code of calling 3A application programming interfaces (APIs) 
 *
 * From now on, users can use ISP library conveniently and easily to maintain or upgrade
 * their own code. There is no need to port the AAA flow source code from the
 * sample code.
 *
 * What users are required to do is to call two APIs: @ref create_img_flow()
 * and @ref destroy_img_flow() that listed in the `img_flow_api.h` file.
 *
 * At the same time, img_flow library is released by the source code as a whole module,
 * which is built as <em>libimg_aaa_flow_v6.so</em> for applications.
 *
 * @note
 *  - Image flow Library can only be used by one app at the same time. That means only one app
 *    can control 3A at the same time.
 *
 * - - - -
 *
 * @section img_flow_usage 2. Image Flow Usage
 * The usage of img_flow library and <em>test_aaa_service</em> application program is provided as shown below:
 *      - Section @ref img_flow_lib_usage_enable
 *      - Section @ref img_flow_lib_usage_run_app
 *      - Section @ref img_flow_lib_usage_advanced_func
 *      - Section @ref img_flow_lib_usage_lua_file
 *      - Section @ref img_flow_lib_usage_add_new_app_type
 *      	- Section @ref img_flow_lib_usage_add_type
 *      	- Section @ref img_flow_lib_usage_add_sensor
 *
 * @subsection img_flow_lib_usage_enable 2.1 How to Enable Image Flow Library
 * There are two steps to enable the img_flow library: configuring menuconfig and
 * running sample application.
 *
 * <b>Step 1: Configure menuconfig</b>
 *
 * 1. Enable the Img_aaa_flow library
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *     packages  --->
 *         idsp  --->
 *             [*] libimgflow (packages/idsp/img_flow)
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build $ make menuconfig
 *     meta-ambalib --->
 *         recipes-video --->
 *             [*] libimgflow (meta-ambalib/recipes-video/libimgflow)
 * @endcode
 *
 * 2. Select IPC / DVR / DMS / ADAS / BWC / ITS / OMC / STEREO type needed
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *	  meta-ambalib  --->
 *      [*] sensor-datas@virtual (meta-ambalib/recipes-sensor) --->
 *            [*]   ipc-sensor-datas@virtual (meta-ambalib/recipes-sensor/IPC) --->
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    packages --->
 *       idsp --->
 *          [*] sensor-datas@virtual (packages/idsp/data/img_cv5x)  --->
 *               [*]   ipc-sensor-datas@virtual (packages/idsp/data/img_cv5x/IPC)  --->
 * @endcode
 *
 * <b>Step 2: Run the sample test application</b>
 *
 * In order to demonstrate the usage of the img_flow library, a sample application
 * that can be executed directly is provided. The <em>test_aaa_service</em> is the sample
 * test application that can be executed by running the commands below:
 * @code {.c}
 * board # init.sh --na; modprobe <sensor_name> vinc_id=8 bus_id=3
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua
 *                     --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --app-img-profile 4
 * @endcode
 *
 * Note:
 * The option <tt>app-img-profile</tt> specifies the application type with an enumerated value
 * <table>
 * <caption id="the app-img-profile enumeration"></caption>
 * <tr><th>Option Value<th> Abbreviation<th align="left"> Details
 * <tr><td>0<td>IPC<td> Internet protocol camera
 * <tr><td>1<td>BWC<td> Body wearing camera
 * <tr><td>2<td>ITS<td> Intelligent transportation system
 * <tr><td>3<td>DVR<td> Digital video recorder
 * <tr><td>4<td>DMS<td> Driver monitoring system
 * <tr><td>5<td>ADAS<td> Advanced driver assistance system
 * <tr><td>6<td>OMC<td> Occupant monitoring camera
 * <tr><td>8<td>STEREO<td> Stereoscopic vision
 * <tr><td>10<td>ROBOT<td> Robot vision
 * </table>
 *
 * @subsection img_flow_lib_usage_run_app 2.2 How to Run test_aaa_service Application
 * The application <em>test_aaa_service</em> is an upper layer application for img_flow library.
 * In order to use img_flow library more efficiently and conveniently, the
 * <em>test_aaa_service</em> provides the sample code for calling the associated APIs.
 * The application executes different actions depending on the input parameters.
 *
 * The available options of <em>test_aaa_service</em> are listed as follows:
 * @verbatim
   -a Auto configuration
   -c Calibration mode
   -d Debug IK for internal
   -i Interactive mode
   -p Load product configuration
   -s String display on screen
   @endverbatim
 *
 * <table>
 * <caption id="<em>test_aaa_service</em> options"></caption>
 * <tr><th>test_aaa_service options<th> Comment
 * <tr><td>test_aaa_service -a<td> Run 3A flow with default configuration parameters
 * <tr><td>test_aaa_service -c<td> Calibration mode. The functions supported in
 * this mode are as follows:
 * * Calculate 3A timing
 * * Calculate vignette calibration
 * * Calculate AWB calibration
 * * Calculate bad pixel calibration
 * * Calculate CA calibration
 * <tr><td>test_aaa_service -d<td> Debug mode for internal use.
 * <tr><td>test_aaa_service -i<td> Interactive mode. The operations supported in
 * this mode are as follows:
 * * Global settings
 * * Exposure control settings
 * * White balance settings
 * * Image adjustment settings
 *
 * Detailed options information has been provided, and users can follow the prompts for relevant actions.
 * <tr><td>test_aaa_service -p<td> Load product configuration from specified lua file, such as:
 *
 * <tt>test_aaa_service -p /usr/share/ambarella/idsp/product_config.lua</tt>
 * <tr><td>test_aaa_service -s<td> Display some 3A parameters on the image stream
 * </table>
 *
 * @subsection img_flow_lib_usage_advanced_func 2.3 How to Use Image Flow Library Better
 * There is a configuration lua file for 3A in the image flow library. The lua file
 * is named as <em>aaa_iq_config.lua</em>, which is at the path
 * <tt>/usr/share/ambarella/idsp/</tt> on the EVK board.
 *
 * - For CV3, the file <em>aaa_iq_config.lua</em> is at the path: <tt>ambarella/packages/idsp/img_flow/img_cv3/</tt>.
 * - For CV5, the file <em>aaa_iq_config.lua</em> is at the path: <tt>ambarella/packages/idsp/img_flow/img_cv5x/</tt>.
 * - For CV72, the file <em>aaa_iq_config.lua</em> is at the path: <tt>ambarella/packages/idsp/img_flow/img_cv72/</tt>.
 *
 *The main configuration options supported in <em>aaa_ia_config.lua</em> are as below:
 * <table>
 * <caption id="aaa_iq_config.lua options"></caption>
 * <tr><th>aaa_iq_config.lua options<th> Comment
 * <tr><td>use_amba_default_aaa_config<td> 0: use 3A configuration in this lua;
 *
 * 1: bypass this lua and use default 3A configuration.
 * <tr><td>preload_enable<td> 0: disable preload and save;
 *
 * 1: enable preload and save
 * <tr><td>load_adj_data_mode<td> 0: load default binary;
 *
 * 1: load customer aeb binary: <tt>adj_param_binary_file_name = "/usr/share/ambarella/idsp/adj_param.bin"</tt>
 * <tr><td>load_aeb_data_mode<td> 0: load default binary;
 *
 * 1: load customer aeb binary: <tt>aeb_param_binary_file_name = "/usr/share/ambarella/idsp/aeb_param.bin"</tt>
 * <tr><td>load_sbp_calibration_load_mode<td> -1: do not load;
 *
 * 0: load default binary;
 *
 * 1: load customer binary: <tt>sbp_calibration_binary_file_name = "/usr/share/ambarella/idsp/cali/bad_pixel.bin"</tt>
 * <tr><td>load_vignette_calibration_load_mode<td> -1: do not load;
 *
 * 0: load default binary;
 *
 * 1: load customer binary: <tt>vignette_calibration_binary_file_name = "/usr/share/ambarella/idsp/cali/lens_shading.bin"</tt>
 * </table>
 *
 * The source code for img_flow library and application <em>test_aaa_service</em> may be modified during
 * using or debugging. Just recompiling and replacing the related binaries would be fine for test
 * and no need to reload the whole firmware:
 * - The latest application <em>test_aaa_service</em> shall be replaced at <tt>/usr/local/bin/</tt>
 * if the test_aaa_service is modified;
 * - The latest library <em>libimg_aaa_flow_v6.so</em> shall be replaced at <tt>/usr/lib/</tt>
 * if source code for img_aaa_flow
 * or img_algo is modified;
 * - The latest bin files of <em>AEB / ADJ /CC</em> shall be replaced at <tt>/usr/share/ambarella/idsp/<app_name>/</tt>
 * if AEB / ADJ / CC files are modified.
 *
 *
 * @subsection img_flow_lib_usage_lua_file 2.4 How to Make Lua Files for Multi-channel Cases
 * Users will need a corresponding lua configuration for multi-channel cases. In this case,
 * two (or three) single-channel lua files can be assembled into one to make it work.
 *
 * Take OV2775-OV2778-OV9284 three-channel case as an example:
 *
 * <b>Step 1: Clarify the correspondence between channels and sensors</b>
 * In this case:
 * @verbatim
   channel_0: ov2775 --> DVR
   channel_1: ov2778 --> OMS
   channel_2: ov9284 --> DMS
   @endverbatim
 *
 * <b>Step 2: Get the configuration file for each sensor in a single channel case</b>
 *
 * - For CV3, the file <em>aaa_iq_config.lua</em> is at the path: <tt>ambarella/packages/idsp/img_flow/img_cv3/config/</tt>.
 * - For CV5, the file <em>aaa_iq_config.lua</em> is at the path: <tt>ambarella/packages/idsp/img_flow/img_cv5x/config/</tt>.
 * - For CV72, the file <em>aaa_iq_config.lua</em> is at the path: <tt>ambarella/packages/idsp/img_flow/img_cv72/config/</tt>.
 *
 * The active channel would be 'channel_0' by default for single-channel cases, thus the
 * configuration parameters are in section 'channel_0'.
 * - Single-channel <em>aaa_iq_config.lua</em> for OV2775
 * @code {.c}
 * global = {
 * 	 version = 0xffff, --the version of config file(hex format)
 * 	 mod = 0x202009011, --the modified date(hex format)
 * 	 amage_server_enable = 1, --1:enable Amage server; 0:disable Amage server
 * 	 preload_enable = 0, --0:disable preload and save; 1:enable preload and save
 * }
 * channel_0 ={
 * 	 // configuration parameters for OV2775
 * 	 ...
 * }
 * @endcode
 *
 * - Single-channel <em>aaa_iq_config.lua</em> for OV2778
 * @code {.c}
 * global = {
 * 	 version = 0xffff, --the version of config file(hex format)
 * 	 mod = 0x202009011, --the modified date(hex format)
 * 	 amage_server_enable = 1, --1:enable Amage server; 0:disable Amage server
 * 	 preload_enable = 0, --0:disable preload and save; 1:enable preload and save
 * }
 * channel_0 ={
 * 	 // configuration parameters for OV2778
 * 	 ...
 * }
 * @endcode
 *
 * - Single-channel <em>aaa_iq_config.lua</em> for OV9284
 * @code {.c}
 * global = {
 * 	 version = 0xffff, --the version of config file(hex format)
 * 	 mod = 0x202009011, --the modified date(hex format)
 * 	 amage_server_enable = 1, --1:enable Amage server; 0:disable Amage server
 * 	 preload_enable = 0, --0:disable preload and save; 1:enable preload and save
 * }
 * channel_0 ={
 * 	 // configuration parameters for OV9284
 * 	 ...
 * }
 * @endcode
 *
 *
 * <b>Step 3: Integrate single channel configuration parameters into multi-channel configuration files</b>
 *
 * According to the corresponding relationship and the configuration file above, fill the
 * configuration parameters of each single-channel into the multi-channel <em>aaa_iq_config.lua</em> file.
 *
 * Final multi_channel <em>aaa_iq_config.lua</em> for OV2775-OV2778-OV9284 case
 * @code {.c}
 * global = {
 * 	 version = 0xffff, --the version of config file(hex format)
 * 	 mod = 0x202009011, --the modified date(hex format)
 *	 amage_server_enable = 1, --1:enable Amage server; 0:disable Amage server
 *	 preload_enable = 0, --0:disable preload and save; 1:enable preload and save
 * }
 * channel_0 ={
 * 	 // configuration parameters for OV2775
 * 	 ...
 * }
 * channel_1 ={
 * 	 // configuration parameters for OV2778
 * 	 ...
 * }
 * channel_2 ={
 * 	 // configuration parameters for OV9284
 * 	 ...
 * }
 * @endcode
 *
 * @subsection img_flow_lib_usage_add_new_app_type 2.5 How to Add a New Sensor or an Application Type
 * @subsubsection img_flow_lib_usage_add_type 2.5.1 How to Add a New Application Type
 * The applicable types include IPC, BWC, ITS, DVR, DMS, ADAS, OMC, STEREO, and ROBOT.
 * Users may need to add a new application type.
 *
 *
 * Here is an example of adding DMS type on CV72:
 *
 * <b>Step 1: Add a new recipe folder for this application type</b>
 *
 * Add the configuration below into the file <em>amba.vdeps</em> at the path <tt>ambarella/metadata/meta-ambalib/recipes-sensor/</tt>:
 * @code {.c}
 * #VDEPS(menuconfig) dms-sensor-datas(/DMS): libimgalgo||prebuild-libimgalgo
 *
 * @endcode
 * Create a new type folder:
 * @code {.c}
 * build # cd ambarella/metadata/meta-ambalib/recipes-sensor/
 * build # mkdir DMS
 * @endcode
 *
 * <b>Step 2: Add a new data folder for this application type</b>
 *
 * Add the configuration below into the file <em>amba.vdeps</em> at the path <tt>ambarella/packages/idsp/data/img_<chip_name>/</tt>:
 * In this case, it is <tt>ambarella/packages/idsp/data/img_cv72/</tt>
 * @code {.c}
 * #VDEPS(menuconfig) dms-sensor-datas(/DMS): &&ambaimg-header
 *
 * @endcode
 * There are sensor data folders in the application type folder:
 * @code {.c}
 * build # ls ambarella/packages/idsp/data/img_cv72/DMS -l
 * drwxr-xr-x 4 cn-sw ar0135
 * drwxr-xr-x 4 cn-sw ar0144
 * @endcode
 * There shall be a makefile <em>amba.mk</em> of this sensor for
 * the IQ binaries to be built, and several subfolders to put the source files and binaries.
 * Set ar0135 as an example:
 * @code {.c}
 * build # ls ambarella/packages/idsp/data/img_cv72/DMS/ar0135 -l
 * total 23
 * drwxr-xr-x 2 cn-sw  adj_params     //to put AEB/ADJ files
 * drwxr-xr-x 2 cn-sw  calib_param    //to put calibration configuration files
 * drwxr-xr-x 2 cn-sw  lens_params    //to put PIRIS configuration files
 * -rw-r--r-- 1 cn-sw  amba.mk        //makefile for dms-ar0135
 * drwxr-xr-x 2 cn-sw  cc_bins        //to put CC binaries
 * -rw-r--r-- 1 cn-sw  LICENSE-AMBARELLA-2-Clause  //license of ambarella
 * @endcode
 *
 * @subsubsection img_flow_lib_usage_add_sensor 2.5.2 How to Add a New Sensor
 * Many sensors have been supported by default, yet users may add new sensors by themselves.
 *
 * Take AR0144 for DMS on CV72 as an example:
 *
 * <b>Step 1: Get sensor ID from sensor_list</b>
 *
 * The sensor_id can be found in structure <tt>sensor_list</tt> of header file <em>iav_vin_common.h</em>
 * at the path <tt>ambarella/drv_modules/private/video/dsp_v6/include/uapi/</tt>:
 * @code {.c}
 * enum sensor_list {
 *	...
 *	SENSOR_AR0144				= 0x0000000C,
 *	...
 * }
 * @endcode
 *
 * <b>Step 2: Map the sensor ID to sensor name</b>
 *
 * Map the sensor_id to sensor name for img_flow library in the source file <tt>ambarella/packages/idsp/img_flow/img_<chip_name>/src/img_flow_sensor_list.c</tt>.
 * In this case, it is <tt>ambarella/packages/idsp/img_flow/img_cv72/src/img_flow_sensor_list.c</tt>.
 * @code {.c}
 * const sensor_t amba_3a_supported_sensors[] = {
 * 	...
 * 	{SENSOR_AR0144, "ar0144"},//dms
 * 	...
 * }
 * @endcode
 *
 * <b>Step 3: Prepare the predefined parameter files</b>
 * - AEB file:
 * The AEB filename format is: `<sensor_name>_aeb_param_<app_type>.c`.
 * In this case:
 * @verbatim
	ar0144_aeb_param_dms.c
   @endverbatim
 * - Auto adjust (ADJ) file:
 * The ADJ filename format is:
 * `<sensor_name>_<vin_type>_<flow_type>_<isp_pipeline>_adj_param_<app_type>.c`.
 * In this case:
 * @verbatim
	ar0144_mono_linear_liso_adj_param.c
   @endverbatim
 *
 * - CC files:
 * The CC binaries name format is: `<sensor_name>_<vin_type>_01/02/03/04_3D_<app_type>.bin`.
 * In this case:
 * @verbatim
    ar0144_mono_01_3D_dms.bin
    ar0144_mono_02_3D_dms.bin
    ar0144_mono_03_3D_dms.bin
    ar0144_mono_04_3D_dms.bin
   @endverbatim
 *
 * <b>Step 4: Create the foler for new sensor and move parameter files to the specified folder</b>
 *
 * 1. Create a new foler named ar0144 at the path <tt>ambarella/packages/idsp/data/img_<chip_name>/<app_type>/</tt>.
 *	In this case,it is <tt>ambarella/packages/idsp/data/img_cv72/DMS/</tt>.
 *
 * 2. Copy <tt>amba.mk</tt> and <tt>LICENSE-AMBARELLA-2-Clause</tt> from <tt>ambarella/packages/idsp/data/img_<chip_name>/GENERIC/def_iq_data/</tt> to this new folder.
 *
 * In this case, it is <tt>ambarella/packages/idsp/data/img_cv72/GENERIC/def_iq_data/</tt>.
 * 3. Create subfolders for IQ parameters.
 *
 * @code {.c}
 * build # ls ambarella/packages/idsp/data/img_cv72/DMS/ar0144/ -l
 * drwxr-xr-x 2 cn-sw adj_params
 * -rw-r--r-- 1 cn-sw amba.mk
 * drwxr-xr-x 2 cn-sw cc_bins
 * -rw-r--r-- 1 cn-sw LICENSE-AMBARELLA-2-Clause
 * @endcode
 *
 * - AEB / ADJ files shall be at the path <tt>ambarella/packages/idsp/data/img_<chip_name>/<app_type>/<sensor>/adj_params</tt>.
 *
 * In this case, it is <tt>ambarella/packages/idsp/data/img_cv72/DMS/ar0144/adj_params</tt>
 * @code {.c}
 * build # ls ambarella/packages/idsp/data/img_cv72/DMS/ar0144/adj_params -l
 * -rw-r--r-- 1 cn-sw   9234 ar0144_mono_aeb_param_dms.c
 * -rw-r--r-- 1 cn-sw 193121 ar0144_mono_linear_liso_adj_param_dms.c
 * @endcode
 *
 * - CC binaries shall be at the path <tt>ambarella/packages/idsp/data/img_<chip_name>/<app_type>/<sensor>/cc_bins</tt>.
 *
 * In this case, it is <tt>ambarella/packages/idsp/data/img_cv72/DMS/ar0144/cc_bins/</tt>
 * @code {.c}
 * build # ls ambarella/packages/idsp/data/img_cv72/DMS/ar0144/cc_bins -l
 * -rw-r--r-- 1 cn-sw 17536  ar0144_mono_01_3D_dms.bin
 * -rw-r--r-- 1 cn-sw 17536  ar0144_mono_02_3D_dms.bin
 * -rw-r--r-- 1 cn-sw 17536  ar0144_mono_03_3D_dms.bin
 * -rw-r--r-- 1 cn-sw 17536  ar0144_mono_04_3D_dms.bin
 * @endcode
 *
 * <b>Step 5: Modify makefile to support new sensors</b>
 *
 * Modify the <tt>amba.mk</tt> in the path <tt>ambarella/packages/idsp/data/img_<chip_name>/<app_type>/<sensor>/</tt>
 * In this case, it is <tt>ambarella/packages/idsp/data/img_cv72/DMS/ar0144/</tt>
 *
 * Check the code below in the <tt>amba.mk</tt> for information consistency. Here, the information contains app_type, sensor, and path.
 * In this case, the app_type is DMS, the sensor is ar0144.
 * @verbatim
   #DEPS(amba.mk) dms-ar0144-datas(jobserver): &&??generic-header \
	&&??ambvideo-header &&??ambaimg-header &kernel-module-ar0144-mipi \
	&kernel-module-ar0144-mipi-brg &kernel-module-ar0144-parallel \
	&kernel-module-ar0144-parallel-brg

   PARAMS_TYPE = dms
   PACKAGE_NAME = $(PARAMS_TYPE)-ar0144-datas
   PACKAGE_DEPS = generic-header ambvideo-header ambaimg-header

   SRC_PATH = adj_params
   IDSP_PARAM_PATH = /ambarella/idsp/$(PARAMS_TYPE)
   INSTALL_DATAS_adj_params = $(ALL_BINS) $(IDSP_PARAM_PATH)/adj_params
   INSTALL_DATAS_cc_bins = cc_bins/*.bin $(IDSP_PARAM_PATH)/cc_bins
 * @endverbatim
 *
 * <b>Step 6: Add recipes for preloading files</b>
 *
 * Create the folder <tt><app_type>-<sensor>-datas</tt> at the path <tt>ambarella/metadata/meta-ambalib/recipes-sensor/<app_type></tt>.
 *
 * In this case, it is <tt>ambarella/metadata/meta-ambalib/recipes-sensor/DMS/dms-ar0144-datas</tt>.
 *
 * 1. Copy an existing recipe folder such as <tt>ipc-imx274-datas</tt> then rename it and sub-files.
 *
 * 2. Modify the code as below in “dms-ar0144-datas_1.0.0.bb”:
 * @verbatim
   EXTRADEPS = "&kernel-module-ar0144-mipi &kernel-module-ar0144-mipi-brg &kernel-module-ar0144-parallel &kernel-module-ar0144-parallel-brg"
   @endverbatim
 * The libraries such as &kernel-module-XXXX are saved in <tt>metadata/meta-ambabsp/recipes-sensor</tt>.
 *
 * 3. Modify the code as below in “dms-ar0144-datas_1.0.0.bbappend”:
 * @verbatim
   EXTERNALSRC = "${ENV_TOP_DIR}/packages/idsp/data/img_${AMBA_IMG_ARCH}/DMS/ar0144"
   EXTERNALSRC_BUILD = "${ENV_TOP_DIR}/packages/idsp/data/img_${AMBA_IMG_ARCH}/DMS/ar0144"
   @endverbatim
 *
 *
 * <b>Step 7: Check the sensor option in menuconfig and rebuild</b>
 * - For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *     drv_modules  --->
 *         platform  --->
 *              vin  --->
 *                 sensors  --->
 *                   [*] kernel-module-ar0144-mipi (drv_modules/platform/vin/sensors/onsemi_ar0144_mipi)
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build $ make menuconfig
 *     meta-ambabsp  --->
 *         recipes-sensor  --->
 *              [*] kernel-module-ar0144-mipi (meta-ambabsp/recipes-sensor/kernel-module-ar0144-mipi)
 * @endcode
 *
 * - - - -
 *
 * @section img_flow_api 3. Image Flow API
 * Visit the following link to find details of the image flow API functions
 *      - @ref img_flow-api-details shows image flow API lists.
 *      - @ref img_flow-api_struct shows image flow structures.
 *      - @ref img_flow-api_helper shows related macros enumerations and macros.
 *
 * - - - -
 *
 * @section img_flow_lic 4. License
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
 * @example test_aaa_service.c
 * This is a source code file of test_aaa_service.c.
 *
 * @example product_parse_lua.c
 * This is a source code file of product_parse_lua.c.
 */
 /*!
 * @defgroup img_flow-api Image Flow Library API
 * @brief Image Flow Library APIs, in file img_flow_api.h
 */
 /*!
 * @defgroup img_flow-api-details Image Flow Library API details
 *  @ingroup img_flow-api
 * @brief Image Flow Library APIs, in file img_flow_api.h
 */
 /*!
 * @defgroup img_flow-api_struct Image Flow Library API structure
 *  @ingroup img_flow-api
 * @brief Image Flow Library structures, in file img_flow_api.h
 */
 /*!
 * @defgroup img_flow-api_helper Image Flow Library API helper
 * @ingroup img_flow-api
 * @brief Image Flow Library Helper, in file img_flow_api.h and img_struct_arch.h
 */

/*!
 * @file doc_lib_image.h
 * @brief This is a .h file for doxygen document system
 * @version 0.0.1
 * @date 2022-06-21
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
 * @page page_lib_img_doc Image Library API
 *
 * @section img_lib_history 0. Revision History
 * <table>
 * <caption id="img_lib_rev_history"></caption>
 * <tr><th>Library Version<th> Updated Date<th align="left"> Modification
 * <tr><td>0.0.1<td>20220621<td> Initial Version
 * <tr><td>0.0.2<td>20230919<td> Added Section 3
 * </table>
 *
 * - - - -
 *
 * @section img_lib_introduction 1. Introduction
 * The image processing digital signal processor (DSP) group of application programming interface (APIs) enables users to configure various
 * image tuning parameters. In CV5x environment, the image processing is
 * performed in three domains below:
 *  * Color filter array (CFA) domain before demosaicing
 *  * Red, green, blue (RGB) domain before converting to YUV
 *  * YUV domain before entering the image encoder
 *
 * The key features supported by the image processing APIs include the following:
 *  * Auto-exposure, auto-focus, auto-white-balance (AAA) statistics
 *  * Lens and sensor correction
 *  * Color processing
 *  * Noise removal
 *  * Sharpening
 *
 * - - - -
 *
 * @section img_lib_pipeline 2. Image Pipeline
 * The CV5x image pipeline is provided as shown in the following diagram. Each function
 * block has a corresponding API to configure the desired quality settings.
 *
 * @image html cv5_pipeline_1527x614.png "Figure 2-1. Image Pipeline."
 *
 * - - - -
 * @section aaa_statistics 3. AAA Statistics Information
 * The CV5x and CV72 image tile number are variable in different cases. 
 * 
 * However, CV72 can upscale tiles into the maximum size of column / row, and CV5x cannot.
 * 
 * The main setting and considerations are listed below:
 *
 * @subsection aaa_statistics_tile_num 3.1 AAA Statistics Tile Number
 * - <b>CFA</b> :
 *   - <b>AE</b> :
 *     - 12x8  (Width <= 4096, Height <= 2160);
 *     - 24x8  (Width >  4096, Height <= 2160);
 *     - 12x16 (Width <= 4096, Height >  2160);
 *     - 24x16 (Width >  4096, Height >  2160).
 *   - <b>AWB</b> :
 *     - 32x32 (Width <= 4096, Height <= 2160);
 *     - 64x32 (Width >  4096, Height <= 2160);
 *     - 32x64 (Width <= 4096, Height >  2160);
 *     - 64x64 (Width >  4096, Height >  2160).
 *   - <b>AF</b> :
 *     - 12x8  (Width <= 4096, Height <= 2160);
 *     - 24x8  (Width >  4096, Height <= 2160);
 *     - 12x16 (Width <= 4096, Height >  2160);
 *     - 24x16 (Width >  4096, Height >  2160).
 * - <b>RGB</b> :
 *   - <b>AE</b> : 24x16.
 *   - <b>AF</b> : 32x16.
 *
 * @subsection considerations_of_aaa 3.2 Considerations
 * - Due to using the hardware format, some parameters of tile such as <em><b>"width/height"</b></em> 
 *   and <em><b>"column/row"</b></em> need the operation <b>"+1"</b>. 
 * 
 * For example, tile number of RGB-AE should be read out <b>"23x15"</b> directly, 
 * so applying <b>"+1"</b> to get the actual number <b>"24x16"</b> before use.
 * 
 * The parameters in below structure include these key words <em><b>"width, height, col, row"</b></em>
 * using the hardware format.
 *          - @a aaa_tile_info_t
 *           - @a awb_tile_info_t 	awb
 *           - @a cfa_ae_tile_info_t 	cfa_ae
 *           - @a af_tile_info_t 	cfa_af
 *           - @a rgb_ae_tile_info_t 	pg_ae
 *           - @a af_tile_info_t 	pg_af
 * 
 * 
 * 
 * - - - -
 * @section img_lib_api 4. Image Library API
 * Visit the following link to find details of the API functions.
 *      - @ref img_lib-high-level-api-details shows high level API lists.
 *      - @ref img_lib-adv-api-details shows advanced API lists.
 *      - @ref img_lib-helper shows related macros enumerations and structures.
 *
 * - - - -
 *
 * @section img_lib_lic 5. License
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
 * @example test_aaa_service.c
 * This is a source code file of test_aaa_service.c.
 *
 * @example aaa_comm_func.c
 * This is a source code file of aaa_comm_func.c.
 *
 * @example customer_loop.c
 * This is a source code file of customer_loop.c.
 */
 /*!
 * @defgroup img_lib-api Image Library API
 * @brief Image Library APIs, in file img_api_arch.h and file img_customer_interface_arch.h
 */
 /*!
 * @defgroup img_lib-high-level-api-details High level Image Library API details
 *  @ingroup img_lib-api
 * @brief High level Image Library APIs, in file img_api_arch.h
 */
/*!
 * @defgroup img_lib-adv-api-details Advanced Image Library API details
 * @ingroup img_lib-api
 * @brief Advanced Image Library APIs, in file img_customer_interface_arch.h
 */
/*!
 * @defgroup img_lib-adj-adv-api-details Advanced ADJ Image Library API Details
 * @ingroup img_lib-adv-api-details
 * @brief Advanced ADJ Image Library APIs, in file img_customer_interface_arch.h
 *
 * There are two sets of memory spaces for each filter: One filter is marked as "in_use",
 * the other is "idle".
 *
 * If it is necessary to modify an individual filter or
 * several filters at once, follow the steps below:
 * 1. Synchronize the "in_use" and "idle" filters to ensure that two sets of filters are identical
 * to function @ref img_adj_sync_containers()
 * 2. Modify the "idle" filter setting with function @ref img_adj_update_idle_container()
 * 3. Flip two sets of filters, and enable the "idle" filter with function @ref img_adj_flip_containers()
 */
/*!
 * @defgroup img_lib-helper Image Library API helper
 * @ingroup img_lib-api
 * @brief Image Library Helper, in file img_struct_arch.h and ambas_imgproc_arch.h
 */


/*!
 * @file doc_lib_nnctrl.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2019-08-29
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
 * @page page_lib_nnctrl_doc NNCtrl Library API
 *
 *
 * @section nnctrl_history 0. Revision History
 *  | Library Version |Updated Date     | Modification                 |
 *  | :---               | :--------------------------- |:----------------|
 *  | 0.2.8 |20190829         | Initial Version                |
 *  | 0.2.9 |20190910         | Support issued split number times ioctl to driver for each network |
 *  | 0.2.9 |20200325         | Support update_pitch on network port |
 *  | 0.3.0 |20200527         | Support dma-buf:fd API for network |
 *  | 0.3.0 |20200803         | Support encrypted network  |
 *  | 0.3.0 |20200803         | Add API nnctrl_get_net_bin_version() |
 *  | 0.3.0 |20200807         | Add API nnctrl_resume_net_ext()  |
 *  | 0.3.0 |20200818         | Remove data struct dvi_desc, pitch_byte_offset and pitch_bsize in io_dim  |
 *  | 0.3.0 |20200901         | Add API nnctrl_run_one_dag_of_net()  |
 *  | 1.0.0 |20200910         | Support LSTM network by loop descriptor, Upgrade cavalry_gen version to 2.2.8.1  |
 *  | 1.0.0 |20201030         | Support mprotect dvi and cmd memory of Network binary |
 *  | 1.0.0 |20201106         | Support check chip version in Network binary. Upgrade cavalry_gen to version: 2.2.8.2 |
 *  | 1.1.0 |20210921         | Support Bi-directional LSTM. Upgrade cavalry_gen to version: 2.2.8.3 |
 *  | 1.2.2 |20230423         | Support DDI (const port) for CV2x. Upgrade cavalry_gen to version: 2.2.8.4 |
 *  | 3.1.0 |20230710         | Support CV72, using cavalry_gen version 3.0.2 |
 *  | 1.2.2 |20231103         | CV2x: Support separate intermediate IO memory |
 *
 * - - - -
 *
 * @section nnctrl_introduction 1. Introduction
 * Neural network control (NNCtrl) is used for users to control the neural network.
 *
 * - - - -
 *
 * @section nnctrl_library_example_usage 2. Example Usage
 * NNCtrl library is based on the Cavalry driver, users should enable the Cavalry driver first,
 * then enable NNCtrl library.
 * Follow these commands to build the library:
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Package Configuration  --->
 *              [*]   Build Ambarella neural network control library
 *
 *          [*] Ambarella Unit Test Configuration	--->
 *              [*]	 Ambarella Private Linux Unit test configs	--->
 *                 [*]   Build CV unit tests
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *          packages  --->
 *              [*]   libnnctrl (packages/nnctrl)
 *
 *          unit_test  --->
 *              private  --->
 *                  [*] cv-test (unit_test/private/cv_test/cavalry_v2)  --->
 *                  [*] cv-stereo-test (unit_test/private/cv_test/cavalry_v2)
 *                  [*] cv-fex-test (unit_test/private/cv_test/cavalry_v2)
 *                  [*] cv-fma-test (unit_test/private/cv_test/cavalry_v2)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *          meta-ambalib  --->
 *              recipes-cavalry  --->
 *                  [*]   libnnctrl (meta-ambalib/recipes-cavalry/libnnctrl)
 *
 *          meta-ambaapp  --->
 *              recipes-test  --->
 *                  [*] cv-fex-test (meta-ambaapp/recipes-test/cv-test)
 *                  [*] cv-fma-test (meta-ambaapp/recipes-test/cv-test)
 *                  [*] cv-stereo-test (meta-ambaapp/recipes-test/cv-test)
 *                  [*] cv-test (meta-ambaapp/recipes-test/cv-test)  --->
 * @endcode
 * @subsection nnctrl_library_cavalry_gen 2.1 cavalry_gen
 * The cavalry_gen provides a method for condensing many output files contained
 * within CNNGen and saving them into one file. The following steps demonstrate an example:
 * @code {.c}
 * build # cavalry_gen -d vas_output/ -f NET_cavalry.bin
 * Using cavalry_gen version latest
 * Save to file NET_cavalry.bin with file size 34376004.
 * @endcode
 *
 * @subsection nnctrl_library_cavalry_gen_api_version 2.1.1 cavalry_gen_api_version
 * Note that Cavalry gen version should match Cavalry parser version
 * shown in test_nnctrl.  Otherwise it will report an error in libnnctrl.
 * For example, all versions are 2.2.8.2 as below.
 * @code {.c}
 * build (or board) # cavalry_gen --version
 * version 2.2.8.2 ( HASH 77c9eb9 )
 * board # test_nnctrl -b NET_cavalry.bin --bin-version
 * [NET_cavalry.bin] Net Binary Cavalry Gen Version: 2.2.8.2
 * board # test_nnctrl --version
 * Cavalry Parser Version: 2.2.8.2
 * @endcode
 *
 * @subsection nnctrl_library_cavalry_gen_chip_version 2.1.2 cavalry_gen_chip_version
 * In order to avoid to run the wrong version network binary on board,
 * the cavalry_gen 2.2.8.2 includes chip arch information in network binary by the corresponding CNNGen tools.
 * @code {.c}
 * board # test_nnctrl -b NET_cavalry.bin --bin-version
 * [NET_cavalry.bin] Net Binary Cavalry Gen Version: 2.2.8.2
 * VDG Chip Arch: cv22
 * @endcode
 *
 * Libnnctrl will report an error if using the wrong chip network binary.
 * The following example is tested on CV22 board, but network binary is built for CV2.
 * @code {.c}
 * board # test_nnctrl -b NET_Cavalry_cv2.bin --bin-version
 * [NET_Cavalry_cv2.bin] Net Binary Cavalry Gen Version: 2.2.8.2
 * VDG Chip Arch: cv2
 * board # source /etc/ambarella.conf
 * board # echo $AMBARELLA_ARCH
 * cv22
 * board # test_nnctrl -b NET_Cavalry_cv2.bin --in input -e
 * [LIBNN  ERR] Compiled ARCH is: 1 - cv22, but VDG ARCH in NET.bin is: 2 - cv2
 * [LIBNN  ERR] Please update NET.bin with CNNGen cv22 Env
 * [LIBNN  ERR] Check VDG ARCH error in NET.bin
 * @endcode
 *
 * Previous cavalry_gen 2.2.8.2 does not have chip arch information inside,
 * so NNCtrl will bypass the chip check.
 * @code {.c}
 * board # test_nnctrl -b NET_Cavalry.bin --bin-version
 * [NET_Cavalry.bin] Net Binary Cavalry Gen Version: 2.2.8.1
 * VDG Chip Arch: Bypass
 * @endcode
 *
 * @subsection nnctrl_library_test_nnctrl 2.2 test_nnctrl Application
 * The test_nnctrl is one simple application that uses NNCtrl library to run the network on CVflow™
 * hardware. Customers can reference it as a sample code to write their own application.
 * It supports file mode only, by feeding input file to network and will generate output file after the
 * network finishes.
 *
 * @subsection nnctrl_library_test_nnctrl_show_io_info 2.2.1 test_nnctrl Show IO Information
 * It shows network's input and output information, such as dimension, data_format, size and more.
 * For example, the network insightface is shown as below.
 * @code {.c}
 * board # test_nnctrl -b insightface_cavalry_fix8.bin  --show-io
 * =======================
 * Net id: 0, name: insightface_cavalry_fix8.bin IO:
 * Input: 0 [data] dim: (1, 3, 112, 112), pitch: 128 (2000, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 0, 7, 0), size: 43008
 * Output: 0 [fc1_scale] dim: (1, 1, 1, 512), pitch: 1024 (588, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 1, 0, 4), size: 1024
 * @endcode
 *
 * @subsection nnctrl_library_test_nnctrl_reuse_mem 2.2.2 test_nnctrl Reuse Port Memory
 * It mainly reuses the network's intermediate port memory. The library considers all port as blob, so blob
 * memory size is decreased if enabling reuse_mem flag.
 * The test_nnctrl will enable this reuse_mem by default, and can disable it by adding "--off-reuse" option.
 * For example, blob size is decreased from 1557536 to 759808 after enabling reuse_mem
 * in network insightface.
 *
 * @b Enable reuse_mem:
 * @code {.c}
 * board # test_nnctrl -b insightface_cavalry_fix8.bin --in data=13.bin --out fc1_scale=output.bin
 * Network [0] [insightface_cavalry_fix8.bin] total memory size: 35041056, dvi: 34280968, blob: 759808. Bandwidth size: 37552712
 * @endcode
 * @b Disable reuse_mem:
 * @code {.c}
 * board # test_nnctrl -b insightface_cavalry_fix8.bin --in data=13.bin --out fc1_scale=output.bin --off-reuse
 * Network [0] [insightface_cavalry_fix8.bin] total memory size: 35838784, dvi: 34280968, blob: 1557536. Bandwidth size: 37552712
 * @endcode
 *
 * @subsection nnctrl_library_test_nnctrl_dump_net 2.2.3 test_nnctrl Dump Net
 * It dumps all DVI and port memory in the network. All DVI files should be identical in "parser" folder
 * when running cavalry_gen.  Port files can be used to debug accuracy issues by analyzing layer's output.
 * The test_nnctrl will close reuse_mem when dumping net, and generate "dvi_dump" and "blob_dump"
 * folder by using "--dump" option.
 * For example, all DVI files in test_nnctrl and cavalry_gen should be identical when using network insightface.
 * @code {.c}
 * board # test_nnctrl -b insightface_cavalry_fix8.bin --in data --out fc1_scale --dump /tmp
 * Network [0] [insightface_cavalry_fix8.bin] total memory size: 35838784, dvi: 34280968, blob: 1557536. Bandwidth size: 37552712
 * Dump blob dir: /tmp/blob_dump
 * Dump dvi dir: /tmp/dvi_dump
 * board # md5sum /tmp/dvi_dump/insightface_*.dvi
 * b6f04aa7153b8da0f44cc84b09b036c5  /tmp/dvi_dump/insightface_prim_split_0.dvi
 * ...
 * ff857d4558ecf44d2c973ca8b8eb1b15  /tmp/dvi_dump/insightface_prim_split_20.dvi
 * build # cavalry_gen -d vas_output/ -f insightface_cavalry_fix8.bin -v
 * build # md5sum parse/insightface_*.dvi
 * b6f04aa7153b8da0f44cc84b09b036c5  parse/insightface_prim_split_0.dvi
 * ...
 * ff857d4558ecf44d2c973ca8b8eb1b15  parse/insightface_prim_split_20.dvi
 * @endcode
 *
 * @subsection nnctrl_library_test_nnctrl_no_mem 2.2.3 test_nnctrl io no_mem
 * Normally, libnnctrl will assign the memory for all ports and DVIs.  The library still supports to use the memory
 * specified by the application.  Users can add "--no" option after port option.
 * For example, blob size reported by libnnctrl is decreased from 759808 to 716800 byte,
 * the reduction is equal to "data" port size 43008 byte.
 *
 * @b Disable no_mem
 * @code {.c}
 * board # test_nnctrl -b insightface_cavalry_fix8.bin --in data --out fc1_scale
 * Input: 0 [data] dim: (1, 3, 112, 112), pitch: 128 (2000, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 0, 7, 0), size: 43008, phys: 0x626b1720, virt: 0x7fbe30e720
 * Output: 0 [fc1_scale] dim: (1, 1, 1, 512), pitch: 1024 (588, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 1, 0, 4), size: 1024, phys: 0x6274d9a0, virt: 0x7fbe3aa9a0
 * Network [0] [insightface_cavalry_fix8.bin] total memory size: 35041056, dvi: 34280968, blob: 759808. Bandwidth size: 37552712
 * @endcode
 * @b Enable no_mem on input
 * @code {.c}
 * board # test_nnctrl -b insightface_cavalry_fix8.bin --in data --no --out fc1_scale
 * Do not allocate net [0] input [0] memory in libnnctrl.
 * Input_ext phys: 0x62770000, dram_size: 43008, size: 43008, virt: 0x7fa254f000
 * Input: 0 [data] dim: (1, 3, 112, 112), pitch: 128 (2000, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 0, 7, 0), size: 43008, phys: 0x62770000, virt: 0x7fa254f000
 * Output: 0 [fc1_scale] dim: (1, 1, 1, 512), pitch: 1024 (588, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 1, 0, 4), size: 1024, phys: 0x627431a0, virt: 0x7fa469d1a0
 * Network [0] [insightface_cavalry_fix8.bin] total memory size: 34998048, dvi: 34280968, blob: 716800. Bandwidth size: 37552712
 * @endcode
 *
 * @subsection nnctrl_library_test_nnctrl_multi_io 2.2.4 test_nnctrl multi-io
 * The test_nnctrl supports multiple inputs and outputs by using multiple "--in" or "--out" options.
 * For example, Yolov3 has three outputs as below.
 * @code {.c}
 * board # test_nnctrl -b yolo_v3_cavalry_fix8_full.bin --in data --out conv59 --out conv67 --out conv75
 * Input: 0 [data] dim: (1, 3, 416, 416), pitch: 416 (752, 16), dram_fmt: 0, bitvector: 0, data_fmt: (0, 0, 8, 0), size: 519168, phys: 0x63ed28e0, virt: 0x7fa313d8e0
 * Output: 0 [conv59] dim: (1, 255, 13, 13), pitch: 64 (916, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), size: 212160, phys: 0x63fa80a0, virt: 0x7fa32130a0
 * Output: 1 [conv67] dim: (1, 255, 26, 26), pitch: 128 (1332, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), size: 848640, phys: 0x6432d4e0, virt: 0x7fa35984e0
 * Output: 2 [conv75] dim: (1, 255, 52, 52), pitch: 224 (588, 16), dram_fmt: 0, bitvector: 0, data_fmt: (1, 2, 0, 7), size: 2970240, phys: 0x643fc7e0, virt: 0x7fa36677e0
 * @endcode
 *
 * @subsection nnctrl_library_test_nnctrl_multi_net 2.2.5 test_nnctrl Multi-net
 * The test_nnctrl supports multiple networks by using multiple "--b" options.
 * For example, the application runs Yolov3 full and sp50 sequentially.
 * @code {.c}
 * board # test_nnctrl -b yolo_v3_cavalry_fix8_full.bin --in data --out conv59 --out conv67 --out conv75
 *  -b yolo_v3_cavalry_fix8_sp50.bin --in data --out conv59 - -out conv67 --out conv75
 * Total neural network num: 2
 * Network [0] [yolo_v3_cavalry_fix8_full.bin] total memory size: 67967584, dvi: 59582100, blob: 8384896. Bandwidth size: 103555796
 * Network [1] [yolo_v3_cavalry_fix8_sp50.bin] total memory size: 48796352, dvi: 40836988, blob: 7958912. Bandwidth size: 73300860
 * @endcode
 *
 * @subsection nnctrl_library_test_nnctrl_io_rotate_flip 2.2.6 test_nnctrl IO Rotate Flip
 * The test_nnctrl supports rotate and flip DRAM feature. There are 5 bitmap for 5 operations.
 * Bitmap order (High -> Low): 4: pflip; 3: dflip; 2: vflip; 1: hflip; 0: rotate.
 * For example, if input data is feeding by clock-wise 270 degree, it will generate identical ouput when
 * feeding input by rotating 90 degree clockwise. For example, the following network insightface shows that
 * "output.bin" and "output_rotate.bin" are the same.
 *
 * @b Original Input
 * @code {.c}
 * board # test_nnctrl -b insightface_cavalry_fix8.bin --in data=13.bin --out fc1_scale=output.bin
 * board # md5sum output.bin
 * b1e2b7c305cf9f8150e1fe95682d2f62  output.bin
 * @endcode
 * @b Clock-wise 270 degree Input
 * @code {.c}
 * There is one tool "binroate.py" in "tools/rotate" folder of CNNGen samples package.
 * Rotate original file with 270 degree clockwise before feeding to the network.
 * build # binrotate.py -i 13.bin -width 112 -height 112 -chan 3 -r 270 -o 13_270.bin
 * board # test_nnctrl -b insightface_cavalry_fix8.bin --in data=13_270.bin --rotate-flip 0x1 --out fc1_scale=output_rotate.bin
 * board # md5sum output_rotate.bin
 * b1e2b7c305cf9f8150e1fe95682d2f62  output_rotate.bin
 * @endcode
 *
 * @subsection nnctrl_library_test_nnctrl_dram_bandwith 2.3 Vector Processor (VP) DRAM Bandwidth
 * The test_nnctrl supports calculation of the current VP dynamic random access memory (DRAM) bandwidth. The VP DRAM bandwidth
 * will be decreased if digital signal processor (DSP) or Arm® accesses the DRAM in background. The test_nnctrl checks
 * approximately if the VP-obtained DRAM bandwidth is sufficient for the network.
 *
 * Both DSP and Arm are idle
 * @code {.c}
 * board # test_nnctrl -w
 * VP BW: 10099 MB/s = 67109028 B / 6645.68 us
 * ==== Check Bandwidth ====
 * Total VP Margin BW: 9594 MB/s = 10099 MB x (100 - 5)%
 * @endcode
 *
 * Arm is busy, and check if DRAM bandwidth is sufficient for the network insightface as below.
 * @code {.c}
 * board # memtester-arm 100 &  (Type command in another console, used to simulate busy ARM process)
 * board # test_nnctrl -w -b insightface_cavalry_fix8.bin --in data --out fc1_scale
 * VP BW: 6205 MB/s = 67109028 B / 10815.43 us
 * Network [0] [insightface_cavalry_fix8.bin] total memory size: 35041056, dvi: 34280968, blob: 759808. Bandwidth size: 37552712
 * ==== Check Bandwidth ====
 * Total VP Margin BW: 5894 MB/s = 6205 MB x (100 - 5)%
 * Net [0] BW : 1496 MB/s = 37552712 B / 25096 us
 * Check BW Result: pass
 * @endcode
 *
 * - - - -
 *
 * @section sec_nnctrl_api 3. NNCtrl API
 * Visit the following link to find details of the API function.
 *      - @ref nnctrl-api-details shows API lists.
 *      - @ref nnctrl-helper shows related macros enumerations and structures.
 *
 * - - - -
 *
 * @section sec_nnctrl_lic 4. License
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
 * @example test_nnctrl.c
 * This is a source code file of test_nnctrl.
 *
 */

 /*!
 * @example test_nnctrl_mfd.c
 * This is a source code file of test_nnctrl_mfd.
 *
 */

 /*!
 * @defgroup nnctrl-api NNCtrl Library API
 * @brief nnctrl Library API, in file nnctrl.h
 */
/*! @defgroup nnctrl-api-details NNCtrl Library API details
 *  @ingroup nnctrl-api
 *  @brief nnctrl API details, in file nnctrl.h
 */
/*! @defgroup nnctrl-helper NNCtrl Library API helper
 *  @ingroup nnctrl-api
 *  @brief nnctrl Helper, in file nnctrl.h
 */
/*!
 * @file doc_lib_sensor_calib.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2021-06-03
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
 * @page page_lib_sensor_calib_doc Sensor Calibration Library API
 *
 * <table>
 * <caption id="Sensor calibration library"></caption>
 * <tr><th> Library Version      <th align="left">Updated Date   <th align="left"> Modification
 * <tr><td> 0.0.1                <td>   20210604                 <td>Initial Version
 * <tr><td> 0.0.2                <td>   20210608                 <td>Added support for saving calibraiton target struct for changing distance calibration
 * <tr><td> 0.0.3                <td>   20210623                 <td>Refined calibration board detecting and add doing calibration with initial values
 * <tr><td> 0.0.4                <td>   20210628                 <td>Added support for creating map for H cylindrical and transverse cylindrical projection
 * <tr><td> 0.0.5                <td>   20210706                 <td>Added support for saving corner id of april tags
 * <tr><td> 0.0.6                <td>   20210713                 <td>Added support for creating grid level map
 * <tr><td> 0.0.7                <td>   20210722                 <td>Added support for using disparity to create configrations for specific distance stitching
 * <tr><td> 0.0.8                <td>   20210809                 <td>Added support for keeping output resolution as the configuration files in base folder
 * <tr><td> 0.0.9                <td>   20210810                 <td>Added support for keeping specific output resolution for multi-channel stitching
 * <tr><td> 0.1.0                <td>   20210811                 <td>Added support for keeping specific output resolution for Thermal and RGB calibration
 * <tr><td> 0.1.1                <td>   20210904                 <td>Added support for accerleration of Mono and RGB automatic calibration
 * <tr><td> 0.1.2                <td>   20210904                 <td>Added some check for RGB and Thermal calibration
 * <tr><td> 0.1.2                <td>   20210904                 <td>Moved Lens / ToF calibration to Sensor Calibration User Guide
 * <tr><td> 0.1.2                <td>   20210921                 <td>Refined the stitching pose calibration
 * <tr><td> 0.1.3                <td>   20210921                 <td>Added support for creating stereo map
 * <tr><td> 0.1.4                <td>   20211012                 <td>Added support for keeping output
 * <tr><td> 0.1.5                <td>   20211021                 <td>Removed crop delta function
 * <tr><td> 0.1.6                <td>   20211022                 <td>1. Added different zoom factor 2. Added padding width
 * <tr><td> 0.1.7                <td>   20211110                 <td>Fixed issues of RGB and Mono calibration
 * <tr><td> 0.1.8                <td>   20211114                 <td>Fixed issues of specifying the output resolution
 * <tr><td> 0.1.9                <td>   20211117                 <td>Fixed issues of creating full calibration warp table
 * <tr><td> 0.1.10               <td>   20211206                 <td>Fixed issues of VFoV loss
 * <tr><td> 0.1.11               <td>   20211209                 <td>Fixed issues of saving debug image
 * <tr><td> 0.1.11               <td>   20211220                 <td>Added options descriptions
 * <tr><td> 0.1.12               <td>   20211220                 <td>Removed unnecessary cutting of the last channel
 * <tr><td> 0.1.13               <td>   20220118                 <td>Added detection threshold to get more keypoints
 * <tr><td> 0.1.13               <td>   20220119                 <td>Updated Section @ref sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> 0.1.14               <td>   20220126                 <td>Updated Section @ref sensor_calib_mono_rgb "Mono and RGB Sensors Calibration"
 * <tr><td> 0.1.15               <td>   20220126                 <td>Updated Section @ref sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> 0.1.16               <td>   20220224                 <td>Updated Section @ref sensor_calib_mono_rgb "Mono and RGB Sensors Calibration"
 * <tr><td> 0.1.17               <td>   20220303                 <td>Updated Section @ref sensor_calib_mono_rgb "Mono and RGB Sensors Calibration"
 * <tr><td> 0.1.18               <td>   20220311                 <td>Moved use_apriltag to reserved0
 * <tr><td> 0.1.19               <td>   20220314                 <td>Added log level
 * <tr><td> 0.1.20               <td>   20220418                 <td>Added multiple threads for creating 2d map
 * <tr><td> 0.1.21               <td>   20220525                 <td>Fixed issues of core dump in adjust camera
 * <tr><td> 0.1.22               <td>   20220616                 <td>Added support for channel rotate @ref sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> 0.1.23               <td>   20220630                 <td>Changed offset to 64 align @ref sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> 0.1.24               <td>   20220729                 <td>Added outlier remove for clusters @ref sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> 0.1.25               <td>   20220803                 <td>Added check for the stitching view bigger than 360 degree @ref sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> 0.2.0                <td>   20220809                 <td>Added support for grid keypoints @ref sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> 0.2.1                <td>   20220810                 <td>Fixed issues when detecting the neighbouring points @ref sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> 0.2.2                <td>   20220906                 <td>Fixed issues in debug image
 * <tr><td> 0.2.3                <td>   20220915                 <td>Removed H matrix refinement stage
 * <tr><td> 0.2.4                <td>   20221024                 <td>Added support for April tag ID 3
 * <tr><td> 0.2.5                <td>   20221025                 <td>Added support for cw_rotate / hflip / vflip
 * <tr><td> 1.0.0                <td>   20221130                 <td>Added support for dual fisheye stitching
 * <tr><td> 1.0.1                <td>   20230317                 <td>Added WINDOWS_COMPILE macro to prevent imwrite compatibility problem
 * <tr><td> 1.0.2                <td>   20230327                 <td>Fix warnings caused by snprintf
 * <tr><td> 1.0.3                <td>   20230428                 <td>Added support for tilt angle stitching
 * <tr><td> 1.0.4                <td>   20230530                 <td>Added support for adjusting dewarp table on the fly by using optical flow
 * <tr><td> 1.0.5                <td>   20230531                 <td>Remove thread to fix core dump problem
 * <tr><td> 1.0.6                <td>   20230728                 <td>Added calib_scale to increase speed
 * <tr><td> 1.1.0                <td>   20230728                 <td>Added support for dense dynamic stitching V3
 * <tr><td> 1.1.1                <td>   20230927                 <td>Added support for keypoints to get global shifts
 * <tr><td> 1.1.2                <td>   20230927                 <td>Fixed artifact in the padding area
 * <tr><td> 1.2.0                <td>   20231020                 <td>Added support for vhhv mode stitching case
 * <tr><td> 1.3.0                <td>   20231020                 <td>Added support for using middle line's dis to do compensation
 * <tr><td> 1.3.1                <td>   20231114                 <td>Added template match to resolve chessboard matching
 * <tr><td> 1.4.0                <td>   20231114                 <td>Added FoV configrations for calibration with rotation stitching
 * <tr><td> 1.4.1                <td>   20231226                 <td>Added scale ratio for rotation stitching
 * <tr><td> 1.5.0                <td>   20240116                 <td>Added max_overlap / ignore_pause options
 * </table>
 *
 * @section sensor_calib_introduction Introduction
 * This chapter introduces basic information on different sensor calibrations.
 *     - Section @ref sensor_calib_cfg
 *     - Section @ref sensor_calib_stitch
 *     - Section @ref sensor_calib_thermal_rgb
 *     - Section @ref sensor_calib_mono_rgb
 *     - Section @ref sensor_calib_tool_usage
 *     - Section @ref sensor_calib_api
 *     - Section @ref sensor_calib_lic
 *
 * - - - -
 *
 * @section sensor_calib_cfg 1. Calibration Configration File Descriptions
 * The `.ini` example files are in the path `ambarella\packages\sensor_calib_ini_parser\arch_v5\configure`.
 * Some descriptions of the options in sensor calibration (.ini file) are as follows: <br>
 *  | Title | Field | Value | Details |
 *  | :----: | :----: | :----: | :----: |
 *  | General | sensor_mode | 1  | Calibration mode. 0: Projection. 1: Calibration. 2: Create undistorted map |
 *  |  | channel_num | 4  | Channel numbers |
 *  |  | overlap_num | 4  | Overlap numbers |
 *  |  | is_vertical | 1  | Vertical stitching flag |
 *  |  | no_yuv | 1  | No YUV for calibration |
 *  |  | prefix | ../example/2_hor/  | Path prefix |
 *  |  | output_width | 2592  | Output width |
 *  |  | output_height | 1944  | Output height |
 *  |  | disable_hv_align | 1  | Disable horizontal and vertical alignment |
 *  |  | cw-rotate | 0 | Channel rotate in the clockwise direction |
 *  |  | hflip | 0 | Channel h-flip in the horizontal direction |
 *  |  | vflip | 0 | Channel v-flip in the vertical direction |
 *  |  | width_ratio | 1 | Width ratio for ecurectangle projection |
 *  |  | create_base  | 0 | Create base configuation |
 *  |  | sensor_debug_mode  | -1 | Specify debug mode. 2: Print difference information. 9: Print detailed information. 10: Save simulation canvas image |
 *  |  | ignore_pause  | 0 | Stop the terminal task |
 *  |  | max_overlap  | 0 | Max overlap width / height |
 *  | Overlap | tag_info | 11 0.023978 0.024031  | April tag information |
 *  | Channel | width | 2592  | Input width |
 *  |  | height | 1944  | Input height |
 *  |  | use_h_flag | 0  | Use H matrix |
 *  |  | no_dist_flag | 1944  | No distortion |
 *  |  | scale_ratio | 1.0,1.0  | Scale ratio |
 *  |  | filename_yuv | 0_canvas0_2592x1944_NV12.yuv  | YUV name |
 *  |  | focal | 1080 | Focal length of fisheye |
 *  |  | cx | width / 2 | X center of fisheye |
 *  |  | cy | height / 2 | Y center of fisheye |
 *  |  | tilt_angle  | 0 | Specify tilt angle |
 *  |  | coor_point  | 0 | Specify coordinates |
 *  |  | H_mat  | 0 | Specify H matrix |
 *  |  | top_left_point  | 0 | Specify top left points |
 *  |  | bot_right_point  | 0 | Specify right bottom points |
 *  |  | adjust | 0,0  | Adjust offset for stitching result |
 *  |  | chan_cw_rotate | 0  | Clockwise rotate |
 *  | Pattern | sensor_pattern_type | 0  | 0: Circle. 1: Chessboard |
 *  |  | share_id | 1  | Share ID |
 *  |  | multi_board | 1  | Multiple board calibration flags |
 *  |  | sensor_pattern_distance | 1.5  | Pattern distance to the optical center |
 *  |  | square_size | 1.5  | Chessboard pattern square size |
 *  |  | board_size | 8,12  | Chessboard pattern size |
 *  | Calib  | different_zoom | 1  | Different zoom factors |
 *  |  | expand_flag | 1  | Expand field of view (FoV) flag |
 *  |  | sensor_dist_mode | 1  | Sensor distance mode. 0: Disparity. 1: Rotation |
 *  |  | keep_cfg_from_base | 1  | Keep configration as the base |
 *  |  | sensor_distance | 1  | Stitching distance |
 *  |  | baseline | 0.05  | Baseline between two lens |
 *  |  | sensor_fuse_method | 2  | 0: Homography. 1: Rotation. 2: Homography and rotation |
 *  |  | expand_same_focal | 1  | Keep the focal length the same in the horizontal / vertical direction |
 *  |  | cali_type | 1  | Sensor distance mode. 0: Fuse. 1: Thermal. 2: STITCH. 3: Matrix. 4: Extrinsic. |
 *  |  | cali_keypoints_method | 1  | Sensor distance mode. 0: Akaze. 1: Orb. 2:Sift. 3:Static. 4:Harris. |
 *  |  | calib_scale | 1  | Scale ratio to increase calibration speed |
 *  |  | fisheye_radius | 544 | Radius of fisheye |
 *  |  | fisheye_overlap_delta | 0 | Overlap width of fisheye |
 *  |  | fisheye_stitch_start | 0 | Fisheye stitching start offset |
 *  |  | fisheye_stitch_end | 0 | Fisheye stitching end offset |
 *  |  | fx_ratio | 1 | X focal length ratio |
 *  |  | fy_ratio | 1 | Y focal length ratio |
 *  |  | use_grid_keypoints | 1  | Use keypoints in the grid level to improve matching robustness |
 *  |  | auto_match_method  | 0 | Specify match method. 0: Apriltag. 1: Optical flow. 2: Flann |
 *  |  | use_four_points | 1  | Use four points to calculate the homography matrix |
 *  |  | backend_name | "backend" | Specify folder name for backend files |
 *  | Thresh | detect_thresh | 0.001  | Key point detection threshold for (AKAZE / SIFT). Decreasing (such as by 0.0005) the value will get more points |
 *  |  | extract_match_ratio | 1  | Image scale ratio for key point extraction and matching; the defalut is 1 |
 *  |  | knn_thresh | 0.6  | Key point matching threshold for the KNN method, the defalut is 0.6. Increasing (such as by 0.75) the value will get more pairs |
 *  |  | ransac_thresh | 1  | Threshold for calculating homography matrix. Decreasing (such as by 0.5 pixel) the value will improve the calibration accuracy |
 *  |  | x_offset_ratio | 0.1  | Threshold of key points horizontal coordinates ratio difference in point-matching stage |
 *  |  | y_offset_ratio | 0.1  | Threshold of key points vertical coordinates ratio difference in point-matching stage |
 *  |  | octaves | 4  | Group numbers of the image pyramid |
 *  |  | sublevels | 4  | Level numbers in one group of the image pyramid |
 *  |  | use_apriltag | 0  | Use the April tag to calculate the homography matrix |
 *  |  | min_area | 50  | Threshold for detecting small radius circle on the calibration pattern |
 *  |  | line_ratio | 0.3  | Threshold of removing the wrong connection in the incline direction |
 *
 * @note <br>
 *  - In the `xx_save_target_xx.ini` file, sensor_distance should be fixed to 100.
 *  - In the `xx_pose_calibration_distance_xx.ini` file, sensor_distance should be no smaller than the pattern distance.
 *
 * - - - -
 *
 * @section sensor_calib_stitch 2. Stitching Pose Calibration
 * Users should perform stitching pose calibration to obtain the configuration (offset / width / height) for each channel.
 * Ambarella platforms support pose calibration on both the host side and the chip side. <br>
 * Host side: more friendly for users to achieve mass production. <br>
 * Chip side: suitable for environment-independent applications.
 * Users can refer to @ref stitching_pose_flow to learn how to perform pose calibration at both the PC Windows side and the chip side.
 *
 * @subsection sensor_calib_chip 2.1 Stitching Pose Calibration Flow
 * The process of pose calibration relies on the intrinsic parameters generated in the process of lens calibration,
 * which is assumed to be performed on the host side. For more details, refer to @ref guide_sensor_calib_lens "2. Lens Calibration". <br>
 * Because the intrinsic parameters of same lens are similar, users can perform stitching pose calibration on the chip side
 * with the same intrinsic parameters to save the time it costs during the process of lens calibration. <br>
 *
 * Stitching pose calibration could be performed on the chip side with a few images. <br>
 * If users choose to perform pose calibration on the chip side, refer to @ref sensor_calib_prepare_board to configure
 * board configurations and build the firmware. <br>
 * To increase convenience for users to configure the values of each parameter, Ambarella introduces the `.ini` file.
 * Compared with the form of the command line, the `.ini` file is much more friendly. <br>
 * With the exception of the four lens pose calibrations based on circle board cases shown in @ref stitching_pose_flow, Ambarella lists
 * two lenses for circle boards and three lenses for chess board pose calibration.
 *
 * Case 1: Perform pose calibration for circle boards for two-lens lens distortion correction (LDC) alignment
 * @code {.c}
 * host (Windows) $ copy "intrinsic_x" generated in the stage of "lens calibration" to the path "front_end/" directly. (intrinsic_x: x = 0, 1, 2, 3)
 * host (Windows) $ test_sensor_calib --msc-ini-file sensor_calib_ini_pose_calibration_save_target_2x_hor.ini
 * host (Windows) $ Edit "sensor_calib_ini_pose_calibration_distance_2x_hor.ini" and modify "sensor_distance=x" accordingly. (x means the distance user specified, and the unit is meter.)
 * host (Windows) $ test_sensor_calib --msc-ini-file sensor_calib_ini_pose_calibration_distance_2x_hor.ini
 * host (Windows) $ There will be source buffer configurations showed in the command window, and then users can config "cvxx_dual_chan_xm_stitch_xM_linear.lua" file accordingly.
 * @endcode
 *
 * Case 2: Perform pose calibration for chess boards for three-lens LDC alignment
 * @code {.c}
 * host (Windows) $ copy "intrinsic_x" generated in the stage of "lens calibration" to the path "front_end/" directly. (intrinsic_x: x = 0, 1, 2, 3)
 * host (Windows) $ test_sensor_calib --msc-ini-file sensor_calib_ini_pose_calibration_save_target_3x_hor_chess.ini
 * host (Windows) $ cp back_end/ base/ -rf
 * host (Windows) $ Edit "sensor_calib_ini_pose_calibration_distance_3x_hor_chess.ini" and modify "sensor_distance=x" accordingly. (x means the distance user specified, and the unit is meter.)
 * host (Windows) $ test_sensor_calib --msc-ini-file sensor_calib_ini_pose_calibration_distance_3x_hor_chess.ini
 * host (Windows) $ There will be source buffer configurations shown in the command window, and then users can configure "cvxx_tripple_chan_xm_stitch_xM_linear.lua" file accordingly.
 * @endcode
 *
 * Users can refer to sections below for more details about the complete flow of the stitching calibration (inlcuding lens and pose calibration). <br>
 * - @ref guide_sensor_calib_lens "Lens Calibration"  <br>
 * - @ref guide_sensor_calib_stitch "Multi-Sensor Stitching Pose Calibration"  <br>
 *
 * @subsection sensor_calib_chip 2.2 Creating Warp Tables
 * Multi-VIN stitching is based on the warp engine, which is hardware that uses the warp vector to perform real-time dewarping. <br>
 * The warp pipeline requires a 1D horizontal vector and a 1D vertical vector. <br>
 * There are some limitations for the warp vector.
 * In the horizontal or vertical warp stage, the digital signal processor (DSP) divides the input of the vector map into grids and relocates
 * the vertices of each grid based on the vector. <br>
 * The DSP performs an interpolation for the pixels that are not vertices of the grids. <br>
 * <b> Maximum Dimensions </b> <br>
 * The grid size can be different in the horizontal and vertical map. <br>
 * The grid width and height for the horizontal vector map must be 8 / 16 / 32 / 64 / 128 / 256 / 512. <br>
 * The grid width for the vertical vector map must be 8 / 16 / 32 / 64 / 128 / 256 / 512. <br>
 * The grid height for the vertical vector map must be 8 / 16 / 32 / 64 / 128 / 256 / 512. <br>
 * The vector map height can be greater than the main buffer height. <br>
 * <b> Vector </b> <br>
 * The vector is in the format of signed 11.4. <br>
 * For the horizontal map, negative vectors point to the right and positive vectors point to the left. <br>
 * @image html horizontal_vector.jpg "Figure 2-1. Horizontal Vector."
 * @image html vertical_vector.jpg "Figure 2-2. Vertical Vector."
 * Users can create 2D warp tables by using pose calibration parameters, and then convert them to 1D + 1D warp tables using the test_stitch application. <br>
 * Different grid spacings will bring quality loss, especially in the horizontal direction. Users can choose the proper grid spacing for good image
 * quality and calculation times. <br>
 * There are a few types of 2D warp tables: <br>
 * - Full pixel-level 2D warp tables. After convertion, the caculated 1D horizontal vector is the most accurate. <br>
 * - For grid-level warp tables, calculate the grid spacing automatically. The calculation time is the shortest. <br>
 * - For grid-level warp tables, customize the grid spacing. The default grid spacing is four; users can specify the grid spacing for proper image quality and calculation time. <br>
 *
 * Case 1: Create a full pixel-level 2D warp table, and apply LDC
 * @code {.c}
 * test_sensor_calib --mode 2 --channel-num 4 -f ./ --grid-map 0
 * test_stitch  --mode 2 -f . --no-overlap --fuse 15 --vertical
 * @endcode
 *
 * Case 2: Create a grid-level 2D warp table (calculate the grid spacing automatically), and apply LDC
 * @code {.c}
 * test_sensor_calib --mode 2 --channel-num 4 -f ./ --grid-map 1
 * test_stitch  --mode 2 -f . --no-overlap --fuse 15 --vertical --use-map 2
 * @endcode
 *
 * Case 3: Create a grid-level 2D warp table (customize the grid spacing), and apply LDC
 * @code {.c}
 * test_sensor_calib --mode 2 --channel-num 4 -f ./ --grid-map 2 --grid-wh 4 --grid-h 4
 * test_stitch  --mode 2 -f . --no-overlap --fuse 15 --vertical --use-map 3 --grid-w 4 --grid-h 4
 * @endcode
 *
 * - - - -
 *
 * @section sensor_calib_thermal_rgb 3. Thermal and RGB Sensors Calibration
 * @image html thermal_points_calib.jpg "Figure 3-1. Thermal Points Choosing Procedure."
 * Because the thermal image's resolution is low, in order to obtain an accurate key point, <br>
 * Ambarella suggests resizing the thermal image to the RGB image size. <br>
 * After the thermal key points are selected, the key points should be resized to a coordinate in the original image. <br>
 * Ambarella recommends selecting more than four pairs of points from both sensor FoVs to perform calibration. <br>
 * First, upscale the thermal image and choose good-quality points, then downscale to the video input (VIN) domain. <br>
 * In one example of the calibration flow, assuming that the thermal sensor resolution is 256x192, and RGB sensor is 2336x1752. Specify scale_ratio (2.5, 2.5) <br>
 * in the `.ini [Channel]` part for channel 1, if the output fusion resolution is 640x480. <br>
 * All points should come from the VIN domain, and the dewarp parameters should only be applied for RGB channels. <br>
 * Specify output_width / output_height in the `.ini [General]` part to fix RGB channel's resolution. <br>
 *
 * 1. Perform thermal and RGB sensor (remove distortion) alignment calibration. <br>
 * It is assumed that users have performed lens calibration; refer to @ref guide_sensor_calib_lens for more details. <br>
 * @code {.c}
 * board # cp front_end /root -rf
 * Set no_dist_flag=0 for RGB channel in the sensor_calib_ini_rgb_thermal.ini
 * board # test_sensor_calib --msc-ini-file sensor_calib_ini_rgb_thermal.ini
 * @endcode
 *
 * 2. Perform thermal and RGB sensor (no distortion) alignment calibration.
 * @code {.c}
 * board # test_sensor_calib --msc-ini-file sensor_calib_ini_rgb_thermal.ini
 * @endcode
 *
 * After calibration, the application reports the messages as shown below. Users can use it to crop the RGB channel's fusion source buffer.
 * @code {.c}
 * Channel [0] Configuration:
 * Canvas: output: size [2304x1712]
 * RGB and thermal calibration result: input offset 216, 282, w / h 1680, 1260
 * @endcode
 * [2304x1712] is the RGB channel's main buffer size. <br>
 *
 * Users can change the Lua option "srcbuf_to_fusion" to specify which source buffer from
 * the RGB channel to fuse with the thermal channel main buffer. <br>
 * Note that the thermal channel main buffer only performs upscaling / downscaling during thermal RGB fusion. <br>
 * After entering the preview with the applied calibration result through the Lua configuration,
 * apply LDC parameters for the RGB channel concurrently. <br>
 * If users want to obtain a fused image with a resolution of 640x480, "scale-reso" option should be modified accordingly. Apply the calibration result
 * above to the RGB channel. <br>
 * In the following Lua configuration, RGB channel-1 in the fifth buffer is chosen for the RGB fusion
 * source buffer through specifying "srcbuf_to_fusion = 4".
 *
 * @code {.c}
 * chan_1 = {
 * 	id = 1,
 * ....
 * 	srcbuf_to_fusion = 4,
 * 	fifth = {
 * 		max_output = {2304, 1712},
 * 		input	   = {0, 0, 0, 0},
 * 		output     = {0, 0, 2304, 1712},
 * 	},
 * ....
 * 	fifth = {
 * 		max_output = {1088, 976},
 * 		input	   = {216, 282, 1680, 1260},
 * 		output     = {0, 0, 640, 480},
 * 	},
 * ....
 * }
 * @endcode
 *
 * input_offset: 216 x 282 from RGB VIN domain.
 * input_width * input_hegith: 1680 * 1260:
 * After configuration, users can run the command to apply the calibration results.
 * @code {.c}
 * board # mv back_end/cali_warp_0 back_end/cali_warp_1 (change dewarp parameters for RGB)
 * board # test_stitch --mode 2 -f ./ --no-overlap --fuse-channel 2 -c 0
 * @endcode
 *
 * - - - -
 *
 * @section sensor_calib_mono_rgb 4. Mono and RGB Sensor Calibration
 * @image html mono_rgb.jpg "Figure 4-1. Mono and RGB Sensor Calibration."
 * For mono and RGB sensor fusion applications, users must align the field of view (FoV) of the mono
 * image with the FoV of the RGB image before combining them.
 * The tool can support automatic alignment calibration for the application.
 * Refer to @ref sensor_calib_prepare_board for setting in menuconfig. <br>
 * The flow of the mono and RGB sensor calibration is as follows: <br>
 * 1. Capture RGB and mono channels' dataset. <br>
 * 2. Perform lens calibration if the lens' distortion is large. <br>
 * Refer to @ref guide_sensor_calib_lens for more details. <br>
 * 3. There are a few methods for the users to perform the calibration. <br>
 * a) Perform the calibration by detecting keypoints automatically. <br>
 * As the keypoint extraction algorithm runs very slowly on Arm®, <br>
 * the user can adjust the "extract_match_ratio" and "thread-num" options to perform the acceleration. <br>
 * As keypoint detection and matching quality is related to image quality, <br>
 * users can change some options to obtain enough matching pairs in different testing environments. <br>
 * Adjust the "cali_keypoints_method" option to choose the point detection algorithm; the
 * tool supports the Akaze / Orb / Sift detection methods. <br>
 * Adjust the "detect_thresh" option to get more keypoints in each image. <br>
 * Adjust "octaves" / "sublevels" to control the image pyramid levels for the AKAZE algorithm. <br>
 * Adjust the "knn_thresh" option for more matching keypoints numbers. <br>
 * Adjust the "ransac_thresh" option to remove outliers and improve the calibration accuracy. <br>
 * Adjust "x_offset_ratio" and "y_offset_ratio" options to remove outliers in the horizontal / vertical directions. <br>
 * The default value is 0.1. If the coordinate difference is larger than width * x_offset_ratio / height * y_offset_ratio,
 * the outliers will be removed. <br>
 *
 * @image html mono_rgb_four_points.jpg "Figure 4-2. Use Four Points to Calculate the Homography Matrix."
 * The image demonstrates using four pairs of points from keypoint extraction to calculate the homography matrix. <br>
 * Set "use_four_points" to 1 in order to choose the feature. <br>
 * When taking snapshots of the calibration pattern, ensure that at least one pair of matching
 * points are placed in each area, as shown below: <br>
 * (< center_x, < center_y), (> center_x, < center_y), (< center_x, > center_y), (> center_x, > center_y). <br>
 * Otherwise, the tool will receive a failure.
 * Refer to @ref sensor_calib_cfg for more details. <br>
 *
 * b) Perform the calibration using April tags.
 * If users want to find four pairs of points to calculate the homography matrix without automatic keypoint detection,
 * they can use four April tags to reach such a target. <br>
 * @image html april_tag_in_four_corner.jpg "Figure 4-3. April Tag Distribution."
 * The image shows four April tags that are placed in the corners of the pattern. <br>
 * The April tags can be found from https://github.com/AprilRobotics/apriltag-imgs, and tag16h5 is shown in the image.
 * Users can add the four April tags to their own calibration pattern board. <br>
 * When taking snapshots of the pattern, ensure that at least one pair of matching points are placed in each area as follows: <br>
 * (< center_x, < center_y), (> center_x, < center_y), (< center_x, > center_y), (> center_x, > center_y). <br>
 * Otherwise, the tool will receive a failure.
 * The option "use_april_tag" is to be used for this method.
 *
 * Perform mono and RGB sensor calibration with the following commands. <br>
 * @code {.c}
 * 1. Calibration:
 * Set no_dist_flag = 0 if the distortion has been calibrated.
 * Case 1: use April tag to perform the calibration.
 * board # test_sensor_calib --msc-ini-file sensor_calib_ini_rgb_mono_apri.ini
 *
 * Case 2: use the Orb feature extraction method to perform the calibration.
 * board # test_sensor_calib --msc-ini-file sensor_calib_ini_rgb_mono.ini
 *
 * 2. Apply calibration results.
 * a) If "no_dist_flag=1" is used:
 * board # mv back_end/cali_warp_0 back_end/cali_warp_1
 * board # test_stitch --mode 2 -f . --no-overlap --fuse 2 -c 0
 *
 * b) If "no_dist_flag=0" is used:
 * board # test_sensor_calib --mode 2 --channel-num 2 -f ./
 * board # test_stitch  --mode 2 -f . --no-overlap --fuse 3
 *
 * @endcode
 *
 * 4. If users have performed the calibration by themselves and want to apply the homography matrix to the specific channel, use the 
 * following command:
 * @code {.c}
 * board # test_sensor_calib --mode 1 -i 0 --no-distort --H_matrix 0.9977401365552157,-0.000099578
 * 23263696219,2.775830523841213,-0.0001202783377077572,0.9971905736384313,1.376427136930342,-
 * 0.0000001840078883173892,-0.000000157500677787866,1 --cali-type 0 -w 2688 -h 1520 -f .
 * configure the lua as the tool reports, and run :
 * board # mv back_end/cali_warp_0 back_end/cali_warp_1
 * board # test_stitch --mode 2 -f . --no-overlap --fuse 2  -c 0
 * @endcode
 *
 * - - - -
 *
 * @section sensor_calib_tool_usage 5. Tool Usage
 *     - Section @ref sensor_calib_tool_usage_function
 *     - Section @ref calib_2dwarp_gen_tool_usage
 *
 * @subsection sensor_calib_tool_usage_function 5.1 Feature Usage
 * The tool supports other basic features for customers to use.
 *
 * @b Example 1: Apply an H matrix on a specific channel
 * @code {.c}
 * board # test_sensor_calib --mode 1 -i 0 --no-distort
 *       --H_matrix 0.998323,-0.000051,4.251321,-0.000663,0.997634,-1.634829,-0.000000,-0.000001,1.000001
 *       --cali-type 0 -w 2560 -h 1440 -f .
 * board # test_stitch --mode 2 -f /root --no-overlap --verbose --fuse-channel 1  -c 0
 * @endcode
 *
 * @b Example 2: RGBD alignment matrix / reprojection matrix calibration
 * @code {.c}
 * board # test_sensor_calib --mode 1 --yuv-file 0.yuv_canvas0_640x480_IYUV.yuv,2.yuv_canvas2_1920x1080_IYUV.yuv
 * -f /root --pattern 1 --chessboard-size 5,3 -i 0 -w 640 -h 480 -i 1 -w 1920 -h 1080 --cali-type 3
 * board # test_sensor_calib --mode 0  -i 1 --map-point 282,129 -f . (map point from one image to the other)
 * @endcode
 *
 * @b Example 3: Mono sensor extrinsic calibration
 * @code {.c}
 * board # test_sensor_calib --mode 1  --yuv-file 0.yuv_canvas0_3840x2160_IYUV.yuv -i 0 -w 3840 -h 2160 --cali-type 4
 * --pattern 1 --chessboard-size 5,3 --mode 1 -f /root -s 0.058
 * @endcode
 *
 * @subsection calib_2dwarp_gen_tool_usage 5.2 Generate 2D Warp Table via Calib-Param
 * When performing lens distortion correction (LDC) or other image remapping operations, the Ambarella
 * digital signal processor (DSP) requires a unique format warp table. Users must implement a user application to convert
 * sensor calibration parameters to an Ambarella warp table. Ambarella provides a sample application, calib_2d_warp_gen.cpp,
 * which reads a calibration parameter file and generates the corresponding 2D-warp table bin file. Users can
 * refer to it to implement their own application. Developers must focus on two funtions: gen_remap_stereo_param
 * and transfer_to_s12_4_vector. Using the example tool, the command is as follows.
 *
 * @note
 * Do not perform any round_up / round_down / truncating to the parameters of the calibration results when generating
 * 2D warp table from calibration results on the PC side. Otherwise, it will cause negative side effects to the final dewarped image.
 *
 * @b Example 1: Build calib_2d_warp_gen
 *
 * - For software development kit (SDK) 3.0 Amba build:
 * @code {.c}
 * build $ make menuconfig
 * build $ [*] Ambarella Prebuild  --->
 * build $ 	[*]   Configure Ambarella sensor calibration library  --->
 * build $ 		[*]   Configure Generate 2D-Calib Warp Table
 * build $ make
 * @endcode
 * - For Cooper Amba build
 * @code {.c}
 * build # make menuconfig
 *   prebuild --->
 *       library  --->
 *           [*] prebuild-sensorcalib (prebuild/library/multi_sensor_calib/dsp_v6)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *      meta-ambalib  --->
 *          recipes-prebuild  --->
 *              [*] prebuild-sensorcalib (meta-ambalib/recipes-prebuild/prebuild-sensorcalib)
 * @endcode
 * @b Example 2: Run calib_2d_warp_gen
 * @code {.c}
 * board # calib_2d_warp_gen -f sensor_calib_ini_stereo.ini -o ./ --res_l 1920x1080 --res_r 1920x1080
 * board # 	//res_l or res_r represents the sensor resolution.
 * @endcode
 *
 * - - - -
 *
 * @section sensor_calib_api 6. Sensor Calibration API
 * Visit the following link for details of the application programming interface (API) functions.
 *      - @ref lib-sensor-helper shows related macros and enumerations.
 *      - @ref lib-sensor-api shows related APIs.
 *
 * - - - -
 *
 * @section sensor_calib_lic 7. License
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
 */

/*!
 * @example test_sensor_calib.c
 * This is a source code file of test_sensor_calib.
 *
 */
 /*!
 * @defgroup sensor-api Sensor Calibration Library API
 * @brief Sensor Calibration Library API, in file lib_sensor_calib.h
 */

/*! @defgroup lib-sensor-api Sensor Calibration Library API Detail
 *  @ingroup sensor-api
 *  @brief Sensor Calibration Library detail, in file lib_sensor_calib.h
 */

/*! @defgroup lib-sensor-helper Sensor Calibration Library API Helper
 *  @ingroup sensor-api
 *  @brief Sensor Calibration Library Helper, in file lib_sensor_calib.h
 */

/*!
 * @file doc_lib_smartfb.h
 * @brief This is a .h file for doxygen document system.
 * @version 0.1
 * @date 2020-02-11
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
 * This file includes sample code and is only for internal testing and evaluation.  If you
 * distribute this sample code (whether in source, object, or binary code form), it will be
 * without any warranty or indemnity protection from Ambarella International LP or its affiliates.
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
 * @page page_lib_smartfb_doc SmartFB Library API
 *
 * @section SmartFB_history 0. Revision History
 *
 * <table>
 * <caption id="lib_smartfb_rev_history"></caption>
 * <tr><th align="left"> Library Version  <th> Updated Date  <th align="left"> Modification
 * <tr><td rowspan="2"> 0.0.4             <td> 20191111      <td> Initial Version
 * <tr>                                   <td> 20220621      <td> Add the introduction about @ref SmartFB_clut
 * </table>
 *
 *
 * - - - -
 *
 * @section SmartFB_overview 1. Overview
 * The smart frame buffer (SmartFB) library is a tool to overlap images on top of the original image
 * by using Linux's FrameBuffer device.  This document explains how to use the SmartFB library for
 * IP cameras and other related devices.
 *
 * SmartFB library fully follows the Linux standard framebuffer interface, users can get more information
 * by understanding the FrameBuffer interface of Liunx.  However, it should be noted in the SmartFB library
 * that when the data is written to framebuffer, it is not directly displayed on video output (VOUT), but the data in
 * framebuffer is resized by the digital signal processor (DSP), and then the resized image is overlapped on VOUT.
 *
 * - - - -
 *
 * @section SmartFB_proc 2. SmartFB Library Process
 * @subsection SmartFB_proc_dep 2.1	Dependency Library
 * The source code for SmartFB can be found in the path `ambarella/packages/smartfb`.
 *
 * To use this library, ensure "Build Ambarella SMARTFB library" is selected in menuconfig.
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * build $ make menuconfig
 *   [*] Ambarella Package Configuration  --->
 *    [*]   Build Ambarella SMARTFB library
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *   packages  --->
 *      smartfb  --->
 *          [*] libsmartfb (packages/smartfb/lib_amba_mk)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *   meta-ambalib  --->
 *      recipes-eazyai  --->
 *          [*] libsmartfb (meta-ambalib/recipes-eazyai/libsmartfb)
 * @endcode
 * After the option to compile SmartFB library is selected correctly, other related dependent
 * options will also be selected automatically.  Users can refer to the following settings.
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code
 * build $ make menuconfig
 *   [*] Ambarella Package Configuration  --->
 *    [*]   Build Ambarella SMARTFB library
 *    -*-   Build Ambarella textinsert library
 *   [*] Ambarella File System Configuration  --->
 *    Third Party Software / Libraries  --->
 *     System Basic Libraries  --->
 * 	    -*- Add freetype2 into root_fs  --->
 *         -*- Add free fonts to file system
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *   packages  --->
 *      [*] libtextinsert (packages/textinsert)  --->
 *      smartfb  --->
 *          [*] libsmartfb (packages/smartfb/lib_amba_mk)
 *   prebuild  --->
 *      oss  --->
 *          [*] prebuild-freetype (prebuild/oss/armv8-a/freetype)
 *          noarch  --->
 *              [*] prebuild-fonts (prebuild/oss/noarch/font)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *   meta-ambalib  --->
 *      recipes-eazyai  --->
 *          [*] libsmartfb (meta-ambalib/recipes-eazyai/libsmartfb)
 *      recipes-video  --->
 *          [*] libtextinsert (meta-ambalib/recipes-video/libtextinsert)  --->
 *   meta-thirdparty  --->
 *      recipes-prebuild  --->
 *          [*] prebuild-fonts (meta-thirdparty/recipes-prebuild/prebuild-fonts)
 * @endcode
 * @subsection SmartFB_color_mode 2.2 Color Mode
 *
 * The information in the SmartFB library typically consists of color values for every pixel to be shown
 * on the display.  Color values are commonly stored in 8-bit palettized, 16-bit high color，and 32-bit
 * true color formats, but there are many different color modes.  For the color mode, users can refer to
 * the following code, or get more detailed information from
 * `ambarella/kernel/linux-4.14/drivers/video/fbdev/ambarella/ambarella_fb.c`.
 *
 * @code
 * static struct ambfb_format ambfb_formats[] = {
 *     { "clut8bpp", 8, {0, 0}, {0, 0}, {0, 0}, {0, 0}, DRM_FORMAT_C8 },
 *     { "rgb565", 16, {11, 5}, {5, 6}, {0, 5}, {0, 0}, DRM_FORMAT_RGB565 },
 *     { "vyu565", 16, {11, 5}, {5, 6}, {0, 5}, {0, 0}, fourcc_code('v', 'y', '1', '6') },
 *     { "bgr565", 16, {0, 5}, {5, 6}, {11, 5}, {0, 0}, DRM_FORMAT_BGR565 },
 *     { "uyv565", 16, {0, 5}, {5, 6}, {11, 5}, {0, 0}, fourcc_code('u', 'y', '1', '6') },
 *     { "ayuv4444", 16, {0, 4}, {8, 4}, {4, 4}, {12, 4}, fourcc_code('a', 'y', 'u', 'v') },
 *     { "rgba4444", 16, {12, 4}, {8, 4}, {4, 4}, {0, 4}, DRM_FORMAT_RGBA4444 },
 *     { "bgra4444", 16, {4, 4}, {8, 4}, {12, 4}, {0, 4}, DRM_FORMAT_BGRA4444 },
 *     { "abgr4444", 16, {0, 4}, {4, 4}, {8, 4}, {12, 4}, DRM_FORMAT_ABGR4444 },
 *     { "argb4444", 16, {8, 4}, {4, 4}, {0, 4}, {12, 4}, DRM_FORMAT_ARGB4444 },
 *     { "ayuv1555", 16, {0, 5}, {10, 5}, {5, 5}, {15, 1}, fourcc_code('a', 'y', '1', '5') },
 *     { "rgba5551", 16, {11, 5}, {6, 5}, {1, 5}, {0, 1}, DRM_FORMAT_RGBA5551 },
 *     { "bgra5551", 16, {1, 5}, {6, 5}, {11, 5}, {0, 1}, DRM_FORMAT_BGRA5551 },
 *     { "abgr1555", 16, {0, 5}, {5, 5}, {10, 5}, {15, 1}, DRM_FORMAT_ABGR1555 },
 *     { "argb1555", 16, {10, 5}, {5, 5}, {0, 5}, {15, 1}, DRM_FORMAT_ARGB1555 },
 *     { "ayuv8888", 32, {0, 8}, {16, 8}, {8, 8}, {24, 8}, DRM_FORMAT_AYUV },
 *     { "rgba8888", 32, {24, 8}, {16, 8}, {8, 8}, {0, 8}, DRM_FORMAT_RGBA8888 },
 *     { "bgra8888", 32, {8, 8}, {16, 8}, {24, 8}, {0, 8}, DRM_FORMAT_BGRA8888 },
 *     { "abgr8888", 32, {0, 8}, {8, 8}, {16, 8}, {24, 8}, DRM_FORMAT_ABGR8888 },
 *     { "argb8888", 32, {16, 8}, {8, 8}, {0, 8}, {24, 8}, DRM_FORMAT_ARGB8888 },
 * };
 * @endcode
 *
 * It should be noted that the larger the bits of color is, the greater the expense of memory will be.
 * Commonly used color modes are clut8bpp, rgb565, and argb8888, but currently SmartFB library
 * only supports clut8bpp and argb8888. Users can set the color mode as required using the
 * following command.
 *
 * 1.Set the color mode to clut8bpp.
 * @code
 * board# rmmod ambarella_fb; modprobe ambarella_fb mode=clut8bpp
 * @endcode
 *
 * 2.Set the color mode to rgb565 (SmartFB library does not support this mode).
 * @code
 * board# rmmod ambarella_fb; modprobe ambarella_fb mode=rgb565
 * @endcode
 *
 * 3.Set the color mode to argb8888.
 * @code
 * board# rmmod ambarella_fb; modprobe ambarella_fb mode=argb8888
 * @endcode
 *
 * If the user sets the color mode to clut8bpp, the color value is stored in 8-bit and only 256 colors
 * can be represented.  The problem with such small color depths is that a full range of colors cannot
 * be produced.  The solution to this problem was indexed color which adds a lookup table to the
 * library.  Each color stored in memory acts as a color index.  The lookup table serves as a palette
 * with a limited number of different colors, and it is called <b>Color Look Up Table (CLUT)</b>.
 *
 * If the user sets the color mode to ARGB8888 (A is alpha, R is red, G is green, and B is blue), then
 * A(alpha) uses 8bit, R(red) uses 8bit, G(green) uses 8bit, and B(blue) uses 8bit, so one pixel occupies
 * 32-bit(four bytes), it will represent a full range of colors.
 *
 *
 * @note
 * For the SmartFB library, the final image is overlapped on VOUT after resized by DSP. Due to the limitation
 * of DSP, the maximum resolution that can be set is different for different color mode.  The larger the
 * bpp is, the smaller the maximum resolution gets.  If the resolution exceeds the maximum resolution, the user
 * may see an open error.  It should be noted that the resolution is "WxH", "W" is width and "H" is height.
 *
 * - When the color mode is set to clut8bpp(8bpp), the maximum width in resolution is 1920.
 * - When the color mode is set to rgb565(16bpp), the maximum width in resolution is 960.
 * - When the color mode is set to argb8888(32bpp), the maximum width in resolution is 480.
 * - The above limitations are based on the default VOUT Profile.
 * For the detailed information of different VOUT Profiles, refer to @ref vout_special_cfg.
 *
 *
 * @subsection SmartFB_clut 2.3 CLUT
 *
 * In the SmartFB library, there is a default <b>CLUT (clut8bpp)</b>,
 * and 23 colors and 8 transparencies are predefined as follows.
 *
 * @code
 * static fb_color_t default_color_clut[SMARTFB_COLOR_NUM] = {
 *     [SMARTFB_COLOR_RED] = {.r = 255, .g = 0, .b = 0},
 *     [SMARTFB_COLOR_LIME] = {.r = 0, .g = 255, .b = 0},
 *     [SMARTFB_COLOR_BLUE] = {.r = 0, .g = 0, .b = 255},
 *     [SMARTFB_COLOR_MAGENTA] = {.r = 255, .g = 0, .b = 255},
 *     [SMARTFB_COLOR_SPRING_GREEN] = {.r = 0, .g = 255, .b = 127},
 *     [SMARTFB_COLOR_MEDIUM_SLATE_BLUE] = {.r = 127, .g = 127, .b = 255},
 *     [SMARTFB_COLOR_YELLOW] = {.r = 255, .g = 255, .b = 0},
 *     [SMARTFB_COLOR_DARK_ORANGE] = {.r = 255, .g = 127, .b = 0},
 *     [SMARTFB_COLOR_CYAN] = {.r = 0, .g = 255, .b = 255},
 *     [SMARTFB_COLOR_GREEN] = {.r = 0, .g = 127, .b = 0},
 *     [SMARTFB_COLOR_BLUE_VIOLET] = {.r = 127, .g = 0, .b = 255},
 *     [SMARTFB_COLOR_VIOLET] = {.r = 255, .g = 127, .b = 255},
 *     [SMARTFB_COLOR_DEEP_PINK] = {.r = 255, .g = 0, .b = 127},
 *     [SMARTFB_COLOR_NAVY] = {.r = 0, .g = 0, .b = 127},
 *     [SMARTFB_COLOR_MAROON] = {.r = 127, .g = 0, .b = 0},
 *     [SMARTFB_COLOR_PURPLE] = {.r = 127, .g = 0, .b = 127},
 *     [SMARTFB_COLOR_SALMON] = {.r = 255, .g = 127, .b = 127},
 *     [SMARTFB_COLOR_OLIVE] = {.r = 127, .g = 127, .b = 0},
 *     [SMARTFB_COLOR_MOCCASIN] = {.r = 255, .g = 255, .b = 180},
 *     [SMARTFB_COLOR_TEAL] = {.r = 0, .g = 127, .b = 127},
 *     [SMARTFB_COLOR_GRAY] = {.r = 127, .g = 127, .b = 127},
 *     [SMARTFB_COLOR_WHITE] = {.r = 255, .g = 255, .b = 255},
 *     [SMARTFB_COLOR_BLACK] = {.r = 0, .g = 0, .b = 0},
 * };
 *
 * static u32 default_alpha_clut[SMARTFB_ALPHA_NUM] =
 *     { 0, 32, 64, 96, 128, 160, 192, 255 };
 *
 * @endcode
 *
 *
 * Here are some introductions of the default CLUT, refer to @ref smartfb_color_init() for details.
 *
 * 1. The first 184 indexes of this default CLUT are composed of 23 colors and 8 transparencies.
 * Each color and 8 transparencies form 8 indexes, which are mainly used in the interface of drawing line, box, etc.
 *
 * 2. The 184 ~ 247 index (64 indexes) of this default CLUT include 64 opaque grayscales,
 * which are mainly used for the interface of drawing mosaics.
 *
 * 3. The remaining 8 indexes of this default CLUT are set to transparent full black (values are 0),
 * which are generally not used.
 *
 *
 *@subsection SmartFB_cycle_buffer 2.4 Cycle-buffer Mechanism
 *
 *@image html SmartFB_Double_buffer.jpg "Figure 2-1. Double Buffer."
 *
 * Most framebuffer uses double buffering mechanism, of course, it may be 3, 4 or
 * more circular buffers.  If the framebuffer uses a double buffering mechanism,
 * the visual resolution of framebuffer is 640×400, the virtual resolution
 * of framebuffer is 640×800.  In the framebuffer model in the Linux kernel, there
 * is a variable called "yoffset", which represents the specific vertical coordinate,
 * and it's default value is 0.  When yoffset is 0, the content in the vertical coordinate
 * from 0 to 399 will be displayed.  If yoffset changes, such as 400 in this example, the
 * rest of the content will be displayed (its ordinate is 400-799).
 *
 * When the system displays the first frame(the content of the ordinate is 0-399),
 * the system can prepare the data of the second frame(the content of the ordinate
 * is 400-799) in the background, so when the first frame is displayed, most of
 * the time, the data for the second frame is also ready and can be displayed
 * directly.  Similarly, when the system displays the second frame, the system can
 * prepare the data of the next frame.  Cycle in this way, the image can be displayed
 * smoothly and the display efficiency can be greatly improved.
 *
 * The user can set the number of buffers through the following command.
 *
 * @code
 *  board# rmmod ambarella_fb; modprobe ambarella_fb  buffernum=2 /* Set the number of buffers to 2 */
 * Or
 *  board# rmmod ambarella_fb; modprobe ambarella_fb  buffernum=4 /* Set the number of buffers to 4 */
 * @endcode
 *
 * @subsection SmartFB_structure 2.5 FrameBuffer Common Structure
 *
 * FrameBuffer has the following commonly used structures: "fb_var_screeninfo",
 * "fb_fix_screeninfo", "fb_cmap", "ioctl".  These structures are declared in
 * `ambarella/kernel/linux-4.14/include/uapi/linux/fb.h`.
 *
 * 1.<b>fb_var_screeninfo</b>
 *
 * This structure is used to record user-modifiable display attribute parameters,
 * including screen resolution, the number of bits per pixel, and so on.
 *
 * There are some frequently used information in this structure, such as:
 * offset (xoffset, yoffset), visible rows and columns of pixels (xres, yres), the
 * number of bits per pixel (bits_per_pixel), virtual resolution (xres_virtual, Yres_virtual).
 *
 * Ambarella can obtain these data through the ioctl() function, such as:
 * `ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo)`.  We can also re-assign and then set it into the
 * system through ioctl(), such as: `ioctl(fbfd, FBIOPUT_VSCREENINFO, &finfo)`.
 *
 * @image html SmartFB_fb_var_screeninfo.jpg "fb_var_screeninfo"
 *
 * @code
 * struct fb_var_screeninfo {
 *    __u32 xres;         /* visible resolution       */
 *    __u32 yres;
 *    __u32 xres_virtual;     /* virtual resolution       */
 *    __u32 yres_virtual;
 *    __u32 xoffset;          /* offset from virtual to visible */
 *    __u32 yoffset;          /* resolution           */
 *
 *    __u32 bits_per_pixel;       /* guess what           */
 *    __u32 grayscale;        /* 0 = color, 1 = grayscale,    */
 *                    /* >1 = FOURCC          */
 *    struct fb_bitfield red;     /* bitfield in fb mem if true color, */
 *    struct fb_bitfield green;   /* else only length is significant */
 *    struct fb_bitfield blue;
 *    struct fb_bitfield transp;  /* transparency         */
 *
 *    __u32 nonstd;           /* != 0 Non standard pixel format */
 *
 *    __u32 activate;         /* see FB_ACTIVATE_*        */
 *
 *    __u32 height;           /* height of picture in mm    */
 *    __u32 width;            /* width of picture in mm     */
 *
 *    __u32 accel_flags;      /* (OBSOLETE) see fb_info.flags */
 *
 *    /* Timing: All values in pixclocks, except pixclock (of course) */
 *    __u32 pixclock;         /* pixel clock in ps (pico seconds) */
 *    __u32 left_margin;      /* time from sync to picture    */
 *    __u32 right_margin;     /* time from picture to sync    */
 *    __u32 upper_margin;     /* time from sync to picture    */
 *    __u32 lower_margin;
 *    __u32 hsync_len;        /* length of horizontal sync    */
 *    __u32 vsync_len;        /* length of vertical sync  */
 *    __u32 sync;         /* see FB_SYNC_*        */
 *    __u32 vmode;            /* see FB_VMODE_*       */
 *    __u32 rotate;           /* angle we rotate counter clockwise */
 *    __u32 colorspace;       /* colorspace for FOURCC-based modes */
 *    __u32 reserved[4];      /* Reserved for future compatibility */
 * };
 * @endcode
 *
 * 2.<b>fb_fix_screeninfo</b>
 *
 * This structure is mainly described with some fixed parameters.
 * These parameters are set during driver initialization and cannot be modified by the user.
 * For example: memory space size, memory start address, the number of bytes occupied by each line and so on.
 *
 * @code
 * struct fb_fix_screeninfo {
 *     char id[16];            /* identification string eg "TT Builtin" */
 *     unsigned long smem_start;   /* Start of frame buffer mem */
 *                     /* (physical address) */
 *     __u32 smem_len;         /* Length of frame buffer mem */
 *     __u32 type;         /* see FB_TYPE_*        */
 *     __u32 type_aux;         /* Interleave for interleaved Planes */
 *     __u32 visual;           /* see FB_VISUAL_*      */
 *     __u16 xpanstep;         /* zero if no hardware panning  */
 *     __u16 ypanstep;         /* zero if no hardware panning  */
 *     __u16 ywrapstep;        /* zero if no hardware ywrap    */
 *     __u32 line_length;      /* length of a line in bytes    */
 *     unsigned long mmio_start;   /* Start of Memory Mapped I/O   */
 *                     /* (physical address) */
 *     __u32 mmio_len;         /* Length of Memory Mapped I/O  */
 *     __u32 accel;            /* Indicate to driver which */
 *                     /*  specific chip/card we have  */
 *     __u16 capabilities;     /* see FB_CAP_*         */
 *     __u16 reserved[2];      /* Reserved for future compatibility */
 * };
 * @endcode
 *
 * 3.<b>fb_cmap</b>
 *
 * This structure is mainly used to describe color mapping information.
 * The color mapping information can be set or get through the ioctl()
 *  operation corresponding to FBIOGETCMAP and FBIOPUTCMAP.
 *
 * @code
 * struct fb_cmap {
 *     __u32 start;            /* First entry  */
 *     __u32 len;          /* Number of entries */
 *     __u16 *red;         /* Red values   */
 *     __u16 *green;
 *     __u16 *blue;
 *     __u16 *transp;          /* transparency, can be NULL */
 * };
 * @endcode
 *
 * 4.<b>parameters_of_ioctl()</b>
 *
 * The commonly used request parameters in ioctl().
 *
 * @code
 * - FBIOGET_VSCREENINFO /* indicates that the user obtains the variable parameters of the screen; */
 * - FBIOPUT_VSCREENINFO /* indicates that the user sets variable screen parameters; */
 * - FBIOGET_FSCREENINFO /* indicates that the user obtains fixed parameters of the screen; */
 * - FBIOBLANK   /* clears the screen */
 * - FBIOPUTCMAP /* sets the color table of the screen */
 * - FBIOGETCMAP /* get color table */
 * @endcode
 *
 *
 * @subsection SmartFB_proc_usage 2.6 FrameBuffer Usage Process
 *
 * The main uses of SmartFB library are as follows.
 *
 * User can also refer to `ambarella/unit_test/private/package_test/arch_v5/test_smartfb.c`.
 *
 * @image html SmartFB_usage_process.jpg "Usage Process"
 *
 * - - - -
 *
 * @section sec_SmartFB_test 3. Unit Test
 *
 * Locate the SmartFB library unit test file in the path below:
 * `ambarella/unit_test/private/package_test/arch_v5/test_smartfb.c`.
 *
 * @subsection SmartFB_test_lp 3.1 Main Loop
 *
 * 1. Call function @ref smartfb_init() to initialize the library.
 * 2. Call function @ref smartfb_get_fb_mode_name() to set the framebuffer mode
 * for the library.
 * 3. Call function input_xxx_attr() to set the necessary parameters for the library.
 * 4. Call function @ref smartfb_display() to show image and switch the current cycle
 * buffer to the next.
 * 5. Call function @ref smartfb_deinit() to release the library session.
 *
 * @subsection SmartFB_test_examp 3.2 Examples
 * Before executing the following unit test, please execute the following command to initialize framebuffer.
 * @code
 * board # rmmod ambarella_fb; modprobe ambarella_fb resolution=1920x1080 mode=clut8bpp buffernum=2
 * @endcode
 *
 * @subsubsection SmartFB_test_examp_solid_box  3.2.1 Draw Solid Box
 *
 * To draw solid box.
 *
 * @code
 * board # test_smartfb
 * board # Your choice: b
 * board # Your choice: 1
 * board # Input OBJ offset x: 100
 * board # Input OBJ offset y: 100
 * board # Input OBJ color: (Useless when special option is selected)
 * board # 0
 * board # Input OBJ bg_color:
 * board # 2
 * board # Input OBJ bg_alpha:
 * board # 7
 * board # Input Box width: 100
 * board # Input Box height: 100
 * board # Your choice: 7
 * @endcode
 *
 * @subsubsection SmartFB_test_examp_mosaic  3.2.2 Draw Mosaic
 *
 * To draw mosaic.
 *
 * @code
 * board # test_smartfb
 * board # Your choice: b
 * board # Your choice: 9
 * board # Input the buffer_id(recommended value is 1) of fetched data: 1
 * board # Input Mosaic fb_offset x: 100
 * board # Input Mosaic fb_offset y: 100
 * board # Input Mosaic fb_width: 100
 * board # Input Mosaic fb_height: 100
 * board # Input Mosaic fb_grid_width: 10
 * board # Input Mosaic fb_grid_height: 10
 * board # Your choice: 7
 * @endcode
 *
 * @subsubsection SmartFB_test_examp_other_objects  3.2.3 Draw Other Objects
 *
 * Users can draw other objects according to the prompts of test_smartfb.
 *
 * - - - -
 *
 * @section sec_SmartFB_api 4. SmartFB API
 *
 * Visit the following link to find details of the API function.
 *      - @ref SmartFB-api explains API functions.
 *      - @ref SmartFB-helper shows related structures, macros, and enumerations.
 *
 * - - - -
 *
 * @section sec_SmartFB_lic 5. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
 *
 * This file and its contents ( "Software" ) are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights.  This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors.  You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Ambarella International LP.
 *
 * This file includes sample code and is only for internal testing and evaluation.  If you
 * distribute this sample code (whether in source, object, or binary code form), it will be
 * without any warranty or indemnity protection from Ambarella International LP or its affiliates.
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
 * @defgroup SmartFB-lib SmartFB Library API
 * @brief Related introductions of SmartFB Library.
 */
/*!
 * @defgroup SmartFB-api SmartFB Library API Details
 * @ingroup SmartFB-lib
 * @brief Details of SmartFB Library API, in file lib_smartfb.h.
 */
/*!
 * @defgroup SmartFB-helper SmartFB Library API Helper
 * @ingroup SmartFB-lib
 * @brief SmartFB Library API Helper: Struct, Enumeration and Macros, in file lib_smartfb.h.
 *
 */

/*!
 * @example test_smartfb.c
 * This is a source code file for testing smartfb.
 *
 */
/*!
 * @file doc_lib_smartrc_v3.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2022-06-30
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
 * @page page_lib_src_v3 SmartRC V3 Library API
 *
 * @section srcv3_history 0. Revision History
 * <table>
 * <caption id="smartrcv3_lib_rev_history"></caption>
 * <tr><th> Library Version	<th align="left"> Updated Date	<th align="left"> Modification
 * <tr><td rowspan="2"> 3.0.0 <td>20200617    <td> 1. Initial Version
 * <tr>                       <td>20200917    <td> 2. <b>[doxygen]</b> Added Section @ref srcv3_lp "5. Lua Parser"
 * <tr><td> 3.0.9             <td>20210506    <td> <b>[SDK]</b> Added support for CV bounding box overlay feature
 * <tr><td> 3.0.10            <td>20210728    <td> <b>[SDK]</b> Added support for force control and update examples
 * <tr><td> 3.0.11            <td>20210811    <td> <b>[SDK]</b> Update buffer ID limitation from 4 to 12
 * <tr><td rowspan="2"> 3.0.12<td>20211009    <td> 1. <b>[SDK]</b> Fix lua parser bug and add IAV version check
 * <tr>                       <td>20211213    <td> 2. <b>[SDK]</b> Adjust the prebuild folder from "\prebuild\ambarella\library\smartrc3\lib" to "\prebuild\ambarella\library\smartrc3\lib\arch_v5"
 * <tr><td> 3.0.14            <td>20220708    <td> <b>[SDK]</b> Extend max encode resolution to 6720x4096 for CV2x
 * <tr><td> 3.0.16            <td>20220708    <td> <b>[SDK]</b> Extend max encode resolution to 7680x4320 for CV5x
 * <tr><td rowspan="7"> 3.0.18<td>20230317    <td> 1. <b>[SDK]</b> Add support to disable low light profile
 * <tr>                       <td>20230317    <td> 2. <b>[SDK]</b> Add support to choose if apply ROI params for B frame
 * <tr>                       <td>20230317    <td> 3. <b>[SDK]</b> Add support to config threshold for motion and noise in lua script
 * <tr>                       <td>20230317    <td> 4. <b>[SDK]</b> Add option to disable frame sync for applying cv outpus bbox, set dsp_pts = 0 in non frame sync case
 * <tr>                       <td>20230317    <td> 5. <b>[SDK]</b> Add option to choose motion value is from preanalysis or cv outpus bbox when cv is enabled
 * <tr>                       <td>20230317    <td> 6. <b>[SDK]</b> Fix issue smartrc cv buf is full when the stream has no valid frame but still in encoding state
 * <tr>                       <td>20230317    <td> 7. <b>[SDK]</b> Fix the issue of SmartRC reset after 256th frame, due to u8 overflow in SmartRC V3 lib
 * <tr><td rowspan="4"> 3.0.19<td>20230410    <td> 1. <b>[SDK]</b> Add new API to update log-level on the fly.
 * <tr>                       <td>20230410    <td> 2. <b>[SDK]</b> Keep the SmartRC thread running instead exiting when dealing with MJPEG stream
 * <tr>                       <td>20230410    <td> 3. <b>[SDK]</b> Reset profile to BIG_MOTION when stream is restarted
 * <tr>                       <td>20230410    <td> 4. <b>[SDK]</b> Fix stop thread block issue
 * <tr><td rowspan="3"> 3.0.20<td>20230330    <td> 1. <b>[SDK]</b> Update overlay width algin to 64 for CV5x
 * <tr>                       <td>20230330    <td> 2. <b>[SDK]</b> Query pre-frame replace sw_pts with dsp_pst
 * <tr>                       <td>20230330    <td> 3. <b>[SDK]</b> Add force IDR support for CV5x
 * <tr><td> 3.0.24            <td>20230425    <td> 1. <b>[SDK]</b> Add API to query / reset profile information
 * <tr><td> 3.1.0             <td>20230506    <td> 1. <b>[SDK]</b> Add support DSP downscale me0 to save CPU loading
 * <tr><td rowspan="2"> 3.2.0 <td>20230704    <td> 1. <b>[SDK]</b> Add support frame drop for static profile
 * <tr>                       <td>20230704    <td> 2. <b>[SDK]</b> Add user_class setting check for AVC
 * </table>
 *
 * - - - -
 *
 * @section srcv3_overview 1. Overview
 * The smart rate control (SRC) library is a tool that controls bit rate according to the
 * specific scene and focus on the regions of interest (ROIs) to maintain video quality in these
 * areas. SmartRC is designed for internet protocol (IP) cameras and other related devices. This document explains
 * how to use the SRC library.
 *
 * There is no standard SmartRC definition for either H.264 (advanced video coding (AVC)) or H.265
 * (high-efficiency video coding (HEVC)). It was designed to effectively increase the number of bits saved for
 * various types of video and maintain improved quality in two methods:
 *
 * - Frame-level control method: saves bits by changing the frame encoding parameters to lower
 * the target bit rate for some specific scenes
 *
 * - Macroblock (MB)-level control method: saves the bits in macro encoding unit (MB or coding
 * tree block (CTB)) aspects by setting the quantization parameter (QP) matrix tables to the macro encoding units
 *
 * There are many encoding tools used for these two types of control. <br><b>All parameters rely on practical
 * video resolution, frames per second (fps), and the complexity of specific scenes. For the software development
 * kit (SDK), the SRC library supports both @b H.264 (AVC) and @b H.265 (HEVC).</b>
 *
 * As H.264 and H.265 are general video coder / decoder (codec) standards, it is difficult to optimize the specific
 * scenes and ROIs. Rather than looking for a solution to optimize H.264 or H.265
 * for a generic scene, the SRC library seeks to improve the @b given scene. The figure below displays
 * the typical rate of optimization.
 * @image html src_codec.jpg "Figure 1-1. H.264 / H.265 Mature Video Codec Standard."
 *
 * Most security IP cameras function with situations A or B, and some are optimized to function with
 * situation C. The LBR library has further improvement for situations D and E. In detail, it means that
 * the SRC library not only inherits LBR's advantages, but also has its own characteristics. The SRC
 * library conserves bits for static areas in a selected frame. Then, these saved bits are used
 * for other areas of motion.
 *
 * - - - -
 *
 * @section srcv3_build 2. Building
 *
 * Smartrc_v3 library, header files, unit test, configuration lua file path is as below.
 * @code {.c}
 * For CV2x SDK 3.0
 *     1. LIB_PATH = ambarella/prebuild/ambarella/library/smartrc3/lib/arch_v5
 *     2. LIB_HEADER_PATH = ambarella/prebuild/ambarella/library/smartrc3/include
 *     3. UNIT_TEST_PATH = ambarella/unit_test/private/package_test/arch_v5/
 *     4. LUA_PATH = ambarella/unit_test/private/package_test/arch_v5/scripts
 *
 * For Cooper SDK (including CV2x SDK4.0)
 *   For CV2x SDK4.0
 *       1. LIB_PATH = ambarella/prebuild/library/smartrc3/lib/arch_v5
 *       2. LIB_HEADER_PATH = ambarella/prebuild/library/smartrc3/arch_v5/include
 *       3. UNIT_TEST_PATH = ambarella/prebuild/library/smartrc3/dsp_v6/unit_test
 *       4. LUA_PATH = ambarella/prebuild/library/smartrc3/dsp_v5/unit_test
 *   For CV5x Cooper SDK
 *       1. LIB_PATH = ambarella/prebuild/library/smartrc3/lib/arch_v6
 *       2. LIB_HEADER_PATH = ambarella/prebuild/library/smartrc3/arch_v6/include
 *       3. UNIT_TEST_PATH = ambarella/prebuild/library/smartrc3/dsp_v6/unit_test
 *       4. LUA_PATH = ambarella/prebuild/library/smartrc3/dsp_v6/unit_test
 * @endcode
 *
 * This library can be found in the path `LIB_PATH`.
 *
 * To use this library, choose the following options in menuconfig to compile the SRC into an application.
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build # make menuconfig
 *   [*] Ambarella Prebuild  --->
 *         [*]   Configure Ambarella smart rate pre-analysis library
 *         [*]   Configure Ambarella smartrc library V3
 * @endcode
 *
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *   prebuild  --->
 *       library  --->
 *           [*] prebuild-smartrc3 (prebuild/library/smartrc3/dsp_v6)
 *           [*]   smartrc3-test (prebuild/library/smartrc3/dsp_v6)
 * @endcode
 *
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *      meta-ambalib -->
 *          recipes-prebuild -->
 *              [*] prebuild-libpreanalysis (meta-ambalib/recipes-prebuild/prebuild-libpreanalysis)
 *              [*] prebuild-smartrc3 (meta-ambalib/recipes-prebuild/prebuild-smartrc3)
 *      meta-ambaapp -->
 *          recipes-test -->
 *              [*] smartrc3-test (meta-ambaapp/recipes-test/smartrc3-test)
 * @endcode
 * - - - -
 *
 * @section srcv3_design 3. Design
 * The SRC library defines several profiles according to the different levels of motion and noise;
 * each profile has one set of encoding parameters including frame and MB-level parameters.
 * Different from the normal codec standards, the library will set frame encoding parameters
 * actively to decrease the bit rate, such as bit rate and group of pictures (GOP) length and more.
 * Based on the MB-level parameters, the library attempts to improve or maintain the video quality for the ROI.
 * @image html src_main_flow.jpg "Figure 3-1. Workflow of the SmartRC Library."
 *
 * @subsection srcv3_preanalysis 3.1 Preanalysis
 * The SRC library performs precise motion detection with the input of 1/16-downscaled luma data. The
 * outputs contain three types of maps: a motion map, an uncovered area (UA) map, and a static area map. The
 * motion map records all of the moved pixels, and then compares this to the reference frames. The
 * UA map records all pixels that cannot be located in the reference frames.
 * The static area map records all background pixels and compares them to the reference frames.
 * These maps will be referred to when performing frame-level and MB-level control.
 *
 * @subsection srcv3_fctl 3.2 Frame-Level Control
 * The maps are used to determine the current profile for the specific scene. The SRC library counts the
 * motion map and caculates its percentage in one frame. It marks this frame as a static frame / small
 * motion frame / mid-motion frame / big motion frame. The SRC library also counts these different motion
 * type frames in one GOP, and decides to switch to different profiles by comparing these counts with the
 * pre-defined or user-defined thresholds.
 *
 * When switching to a new profile, the frame-level parameter settings for this profile will be updated to
 * the digital signal processor (DSP). The structure of the frame encoding parameters is @ref smartrc_frame_params_table_t.
 * Frame-level controls affect the bit rate directly, and all frame-level parameters are in the file
 * `LUA_PATH/smartrc_example.lua`.
 *
 * The advantage of frame-level control is that the library can switch profiles and decrease the
 * bit rate for static scenes. Using encoding tools, such as P-frame skip, frame-level control can maintain
 * good quality at a low bit rate for static scenes.
 * @image html src_static_compare.jpg "Figure 3-2. H.264 100-Kbps Static Scene SRC On / Off."
 *
 * @subsection srcv3_roictl 3.3 ROI-Level Control
 * Along with the frame encoding parameters, each profile has a set of MB-level encoding parameters
 * @ref smartrc_roi_params_table_t. These parameters are filled into QP matrix tables
 * according to the maps. As the unit of the matrix table is @ref iav_h264_qproi_data or @ref
 * iav_h265_qproi_data, and the resolution of the table is 1/16x1/16 (AVC) or 1/32x1/32 (HEVC)
 * from the streams, the pixels in the maps can be mapped to the QP matrix table. This means that the
 * MB-level parameters can be applied to specific areas, such as motion areas, in the QP
 * matrix table.
 *
 * The advantage of MB-level control is that the library can improve image quality for specific areas
 * and skip the encoding of static pixels. The image below demonstrates the improvement on the moving
 * hands.
 * @image html src_motion_compare.jpg "Figure 3-3. H.265 200-Kbps Motion Scene SRC On / Off."
 *
 * Note that there are some limitations for the matrix number for HEVC, and complex
 * GOP structures will require more matrixes (as different frame types must use different matrixes
 * for HEVC). The table shows the relationship between the GOP structures and number of matrixes.
 *
 * @image html src_roi_matrixes.jpg "Figure 3-4. ROI-Level Control."
 * The matrix number for each stream can be specified in the Lua script.
 * @code
 * streams_mem = {
 *	{
 *		qpm_possible = 1,
 *		qpm_max_matrix_num = 2,  // matrix number is 2
 *		qpm_buf_max_num = 7,
 *		max_stream = {1920, 1080},
 *  },
 * @endcode
 *
 * @subsection srcv3_cvctl 3.4 Computer Vision (CV) Control
 * The SRC library supports improving video quality according to CV outputs. Once CV control
 * is enabled, the server inside the library will be set up. The CV applications can then access
 * the server and send the CV outputs to the SRC library. The SRC library performs frame-level and
 * MB-level control with these outputs. The client application programming interfaces (APIs) can be found in
 * `LIB_HEADER_PATH/lib_smartrc_client.h`, and the example code can be found in `UNIT_TEST_PATH/test_smartrc_ssd_live.c`.
 * @image html src_cv_compare.jpg "Figure 3-5. H.265 300-Kbps CV On / Off Person Detection."
 *
 * - - - -
 *
 * @section srcv3_padj 4. Parameter Adjustment
 *
 * The file `LUA_PATH/smartrc_example.lua` includes all encoding parameters for SRC. These parameters are not
 * fixed, as they depend on a variety of factors including the complexity of the scene, GOP structures, resolutions,
 * and frames per second (fps). The parameters must be tuned for different cases. For example, a 100-Kbps bit rate
 * may be suitable for a simple static scene, but if the scene is much more complex, the bit rate may be required to
 * be inreased. For details of these frame-level and ROI-level parameters, refer to @ref fs_basic_codec "BASIC - H.264 / H.265 Codec".
 *
 * @subsection srcv3_frame_level_params 4.1 Frame-Level Parameters
 *
 * For frame-level parameters, decrease the average bit rate via the following steps:
 *
 * -# The target bit rate can be reduced and the GOP length can be increased.
 *
 * -# If the average bit rate exceeds or cannot reach the target bit rate in a specific profile,
 *    the QP limitation can be tuned. Increasing the minimum value of the limitations can
 *    decrease the size of the corresponding frames, and the frames' size will be increased
 *    when the maximum value of the limitations is decreased.
 *
 * -# For static scenes, setting either frame_skip or frame_drop helps to use lower bit rates to obtain
 *    similar image quality. Note that only one parameter can be configured for static scenes; both
 *    parameters cannot be configured for non-static scenes.
 *
 * -# Note that the bit rate is supposed to be increased when the motion level is increased.
 *    GOP length is also supposed to be decreased when the motion level is increased.
 *
 * @subsection srcv3_roi_level_params 4.2 ROI-Level Parameters
 *
 * There are two types of MB-level parameters:
 *
 * - QP offset, which can be used to lower the QP value on MB / CTB  if the QP offset is negative
 *
 * - Category (HEVC) and user_class (AVC), which can be used to affect the codec strategy
 *   (such as intra, inter, or skip) for each MB / CTB
 *
 *    When the user class is set to 1 for AVC, the MB will be encoded as skip type as often as is
 *    possible. Additionally, the MB will be encoded as intra or inter type as often as is possible when the
 *    user class is set to 2. Ambarella recommends using "user_class = 1" only for static maps.
 *    For details of user_class, refer to @ref example_codec_roi_enc2 "Set User Class Type for MB".
 *
 *    For HEVC, the category can directly influence the codec type. If it is set to 1, the CTB motion
 *    vector (MV) will be processed as 0 (force zero motion vector (ZMV)). If it is set to 2,
 *    the CTB will be encoded as intra type. If it is set to 3, the QP offset will always take effect.
 *    If it is set to 4, the CTB will be encoded as skip type. For absolute static areas, the CTB
 *    category could be set to 4. For details on these category, refer to @ref example_codec_roi_enc1
 *    "Set Category Lookup Table".
 *
 * Note that applying negative QP offsets to large areas will cause the bit rate to increase. As
 * smaller QP values for MB / CTB result in a greater size cost on the MB / CTB, Ambarella does not suggest applying
 * negative numbers with large absolute values.
 *
 * - - - -
 *
 * @section srcv3_lp 5. Lua Parser
 * SRC Lua scripts are different from the Lua scripts used to enter the preview via test_encode. SRC Lua scripts are
 * defined to configure the encoding parameters for the SRC library. All frame-level and MB-level
 * parameters for each profile can be configured in the scripts. With the Lua parser, the scripts are
 * parsed and the parameters are updated to the SRC library. The SRC Lua scripts can help users 
 * to more easily understand SRC control. The Lua scripts are saved in `LUA_PATH`, and there is a default Lua script
 * for the SRC library, named `smartrc_example.lua`.
 *
 * @subsection srcv3_lp_fw 5.1 Lua Description
 * There are several profiles which can be configured in the script.
 *
 * @code
 * _src_enc_cfg_ = {
 *      version = 1,
 *      log_level = 0,
 *      profiles = {
 *      profile_0,
 *      profile_1,
 *      profile_2,
 *      profile_3,
 *      profile_4,
 *  },

 *  thresholds = { -- threshold_0 is for motion threshold, threshold_1 is for noise threshold
 *      threshold_0,
 *      threshold_1,
 *  },
 * },
 * @endcode
 *
 * The structure information of each profile can be configured, as shown below:
 *
 * @code
 * profile_0 = {
 *     profile_type = "static_profile",
 *     frame_ctrl = {
 *         force_idr = 1,
 *         gop = {
 *             ....
 *         },
 *
 *         qp_params = {
 *             ....
 *         },
 *
 *         zmv_params = {
 *             ....
 *         },
 *
 *         skip_params = {
 *             ....
 *         },
 *
 *         drop_params = {
 *             ....
 *         },
 *     },
 *
 *     roi_ctrl = {
 *         matrix_0 = {
 *             used_by = "single_ref_P",
 *             maps = {
 *                 map_0 = {
 *                     type = "static_map",
 *                     ....
 *                 },
 *                 map_1 = {
 *                     type = "motion_map",
 *                     ....
 *                 },
 *                 map_2 = {
 *                     type = "uc_map",
 *                     ....
 *                 },
 *             },
 *             bbox_class = {
 *                 class_0 = {
 *                     id = 0,
 *                     ....
 *                 }
 *             },
 *         }
 *     },
 * },
 * @endcode
 *
 * Profile information can be divided into the following parts:
 * - Specify the profile type @ref smartrc_profile_type_e: There are several types of profiles
 * for different scenes. The SRC library uses the parameters of different profiles according to
 * the motions in the scenes
 *
 * - Specify motion and scene thresholds @ref smartrc_level_thres_t and @ref smartrc_scene_thres_t:
 * The threshold @ref smartrc_level_thres_t is used to determine the current frame level (static frame, small motion
 * frame, mid-motion frame, big motion frame, or noise frame). The threshold @ref smartrc_scene_thres_t is used to
 * determine the current scene level (static scene, small motion scene, mid-motion scene, big motion
 * scene, or noise scene). Based on the accumulated scene level, SmartRC determines when to switch to a different
 * profile
 *
 * - Parameters for frame-level control @ref smartrc_frame_params_table_t: These parameters
 * are used to tune video global quality. All of these parameters are coupled, so the bit rate
 * may not achieve the target when tuning it alone. For more information about tuning
 * frame-level parameters, refer to @ref srcv3_padj
 *
 * - Parameters for MB-level control @ref smartrc_roi_params_table_t: These parameters are
 * used to tune ROI quality in the frames. For adjustment of these
 * parameters, refer to @ref srcv3_padj
 *
 * - Specify the matrix type: As mentioned in @ref srcv3_roictl, there are up to three matrixes, and
 * each matrix can be specified for use by a specific type of frame. For matrixes used
 * by the DSP, the frame types can be divided into four types: I frames, single-reference P frames, two-reference
 * P frames, and B frames. However, users are not required to perform any improvements at the MB-level for I frames,
 * as they are used to specify the matrix for @b single_ref_P, @b two_ref_P, and @b ref_B
 *
 * - Specify ROI parameters @smartrc_roi_params_t for different maps @ref smartrc_map_type_e:
 * Different maps are used to record different types of pixels (such as static maps recording static
 * pixels). The ROI parameters for static maps are applied to the static pixels when the
 * frames are encoded
 *
 * - Specify ROI parameters @smartrc_roi_params_t for different types of objects detected by the
 * CV algorithm: There are up to four classes of ROI parameters for CV which can be set. 
 * Note that the classes have no clear definition of the object category, meaning that the ROI
 * parameters of class 0 can be used for any object. Users are required to specify the ROI parameters
 * through the @b roi_idx in @ref cv_bbox_info_t when sending the CV outputs to the SRC library
 *
 * - - - -
 *
 * @section srcv3_ut 6. Unit Test
 * Locate the SmartRC library unit test file in the path
 * `UNIT_TEST_PATH/test_smartrc_v3.c`. The example demonstrating how to use
 * the SmartRC client library to send the outputs to the SRC library can be found in
 * `UNIT_TEST_PATH/test_smartrc_ssd_live.c`.
 *
 * @subsection srcv3_ut_src 6.1 Smart Rate Control Application
 * -# Call the function @ref smartrc_init_lib() to initialize the library.
 * -# Call the function @ref smartrc_set_params_table() to update the table of encoding parameters
 * to the library.
 * -# Call the function @ref smartrc_set_force_control_map() to enable frame-level force control,
 * if required.
 * -# Call the functions @ref smartrc_set_mask_info() and @ref smartrc_set_file_info() to set the debug
 * settings.
 * -# Call the function @ref smartrc_enable_control() to enable / disable frame-level or MB-level control.
 * -# Call the function @ref smartrc_enable_dynamic_gop() to enable / disable dynamic GOP when frame-level
 * control is enabled.
 * -# Call the functions @ref smartrc_start_process() and smartrc_stop_process() to start / stop the
 * SmartRC process on the fly.
 * -# Call the function @ref smartrc_server_init() to set up the socket server after `smartrc_init_lib()`
 * is called, and to perform bit-rate control on CV outputs if required.
 * -# Call the function @ref smartrc_deinit_lib() to close the library.
 * -# Call the function @ref smartrc_server_deinit() to close the server.
 *
 * @subsection srcv3_ut_cv 6.2 Computer Vision Application
 * -# Load the library `LIB_PATH/lib_smartrc_client.so`
 * in the CV application.
 * -# Call the function @ref smartrc_client_init() to set up the client for the SRC server. Note that
 * the server should be set up before the client setup request is received.
 * -# Call the function @ref smartrc_client_query_vcap_frame() to query YUV information to perform an analysis.
 * -# Call the function @ref smartrc_client_update_bbox() to send bounding boxes to the SRC library.
 * -# Call the function @ref smartrc_client_deinit() to close the client.
 *
 * @subsection srcv3_ut_lp 6.3 Lua Application
 * -# Call the function @ref smartrc_parse_lua_cfg() to parse the Lua scripts.
 * -# Call the function @ref smartrc_create_lua_cfg() to create the Lua scripts.
 *
 * - - - -
 *
 * @section srcv3_exp 7. Examples
 * @subsection srcv3_exp_prev 7.1 Enter Preview
 * Users are required to specify the extra buffer number for the stream-dummy-lantency feature.
 * Modify the default configuration Lua as shown below:
 * @code
 * ...
 * canvas = {
 * 			{
 * 				type = "encode",
 * 				size = {0, 0}, -- min size to contain source buffers
 * 				source = {"chan_0.main",},
 * 				extra_dram_buf = 3,
 * 			},
 * ...
 * @endcode
 *
 * @code
 * board # init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_encode -A -h 1080p -b 0 --stream-dummy-latency 3 -e
 * @endcode
 * Note that the @b extra_dram_buf of the corresponding canvas in the Lua and @b `stream-dummy-latency`
 * in the command line should be set.<br>
 *
 * @subsection srcv3_exp_frame 7.2 Frame-Level Control
 * To enable frame-level control:
 * @code
 * board # test_smartrc_v3 -A --frame-control 1 -l 1
 * @endcode
 * To disable dynamic GOP change when performing frame-level control:
 * @code
 * board # test_smartrc_v3 -A --frame-control 1 --dyn-gop 0 -l 1
 * @endcode
 * To enable frame-level force control:
 * If users specify frame-level control parameters without force control, the parameters will
 * be stored in the configuration table of the current profile. The parameters take effect when
 * the system changes back to the current motion at the next instance.
 * If users specify the frame-level control parameters with force control, the parameters will
 * take effect immediately.
 * @code
 * board # test_smartrc_v3 -A -l 1 --force-control 0x1F
 * @endcode
 *
 * @subsection srcv3_exp_roi 7.3 ROI-level Control
 * To disable roi-level control:
 * @code
 * board # test_smartrc_v3 -A --roi-control 0 -l 1
 * @endcode
 *
 * @subsection srcv3_exp_roi_for_B 7.4 Apply ROI Matrix for B Frames
 * By default, when there is a B frame in the GOP, the SRC library will skip to applying an ROI matrix to B frames in order to
 * conserve CPU loading. Applying ROI matrixes for B frames with the option @b enable-roi-for-B-frame is also supported.
 * @code
 * board # test_smartrc_v3 -A --roi-control 1 -l 3 --enable-roi-for-B-frame 1
 * @endcode
 *
 * @subsection srcv3_exp_drwspt 7.5 Draw Spots
 * To draw white spots on static areas in stream A:
 * @code
 * board # test_smartrc_v3 -A -k -m 0 -c 255 -l 1
 * @endcode
 * To draw white spots on motion areas in stream A:
 * @code
 * board # test_smartrc_v3 -A -k -m 1 -c 255 -l 1
 * @endcode
 * To draw black spots on uncovered areas in stream A:
 * @code
 * board # test_smartrc_v3 -A -k -m 2 -c 0 -l 1
 * @endcode
 * To draw black spots on bounding boxes in stream A, refer to the example @ref srcv3_exp_cv.
 * @code
 * board # test_smartrc_v3 -A -r 8 --cv-enable 1 --cv-src 1 -l 1 -m 3
 * @endcode
 *
 * @subsection srcv3_exp_dm 7.6 Dump Maps
 * Dump the static map for stream A, and save it in the `/tmp` folder:
 * @code
 * board # test_smartrc_v3 -A -f /tmp/ -d 0 -l 1
 * @endcode
 * Dump the motion map for stream A, and save it in the `/tmp` folder:
 * @code
 * board # test_smartrc_v3 -A -f /tmp/ -d 1 -l 1
 * @endcode
 * Dump the uncovered map for stream A, and save it in the `/tmp` folder:
 * @code
 * board # test_smartrc_v3 -A -f /tmp/ -d 2 -l 1
 * @endcode
 *
 * @subsection srcv3_exp_at 7.7 Auto Tests
 * Run the auto socket test, and draw black spots on the fake CV areas:
 * @code
 * board # test_smartrc_v3 -A -r 8 --cv-enable 1 -t 0 -m 3 -c 0 -l 1
 * @endcode
 * Run the auto start / stop process test:
 * @code
 * board # test_smartrc_v3 -A -t 1 -l 1
 * @endcode
 * Run the auto random frame control test:
 * @code
 * board # test_smartrc_v3 -A -t 2 -l 1
 * @endcode
 *
 * @subsection srcv3_exp_lp 7.8 Lua Script
 * Specify the Lua scripts for the SRC library.
 * @code
 * board # test_smartrc_v3 -A -r 7 --lua /usr/local/bin/script/src_example.lua
 * @endcode
 * Create Lua scripts with the parameters inside the library.
 * @code
 * board # test_smartrc_v3 -A -r 7 --lua /usr/local/bin/script/src_example.lua --lua-dump /tmp/src_dump.lua
 * @endcode
 *
 * @subsection srcv3_exp_disable_low_light 7.9 Disable Low-Light Profiles
 * There are a total of five profiles in the SmartRC Lua script; users can choose to disable low-light profiles.
 * @code
 * board # test_smartrc_v3 -A -r 15 --frame-control 1 --roi-control 1 --disable-low-light-profile 1
 * @endcode
 *
 * @subsection srcv3_exp_thres 7.10 Threshold of Motion and Noise in the Lua Script
 * Ambarella supports configuring thresholds for motion / noise level and scenes in the Lua script.
 * @code
 * threshold_0 = {
 *     is_valid = 1,  -- 0 : use default threshold inside lib, 1 : use below threshold for lib
 *     threshold_type = "motion_thres",  -- motion threshold
 *     level = {
 *         none = 1,
 *         low = 301,
 *         mid = 30001,
 *         high = 100001,
 *     },
 *     scene = {
 *         none = 51,
 *         low = 31,
 *         mid = 21,
 *         high = 4,
 *     },
 * }
 * threshold_1 = {
 *     is_valid = 1,  -- 0 : use default threshold inside lib, 1 : use below threshold for lib
 *     threshold_type = "noise_thres",  -- noise threshold
 *     level = {
 *         none = 1,
 *         low = 19,
 *         mid = 21,
 *         high = 25,
 *    },
 *
 *    scene = {
 *        none = 121,
 *        low = 61,
 *        mid = 11,
 *        high = 1,
 *    },
 * }
 * @endcode
 *
 * @code
 * board # test_smartrc_v3 -A -r 7 --lua /usr/local/bin/script/src_example.lua
 * @endcode
 *
 * @subsection srcv3_exp_apply_cv_output_with_non_frame_sync 7.11 Apply CV Output with Non-Frame Sync Mode
 * By default, when CV is enabled, the SmartRC library performs frame synchronization with CV output; this means that CV
 * applications can correct a YUV frame's `dsp_pts`. Non-frame sync is also supported without setting `dsp_pts`.
 *
 * @code
 * board # test_smartrc_v3 -A -r 15 --frame-control 1 --roi-control 1 --cv-enable 1 --cv-src 0 -t 0 --disable-frame-sync-for-cv 1
 * @endcode
 *
 * @subsection srcv3_exp_cv 7.12 Cooperate with CV
 * Run the CV application to perform object detection and send the bounding boxes of humans to the SRC library for
 * SRC control. Mark the human region(s) on the stream and on the high-definition multimedia interface (HDMI®) video.
 * @code
 * board # init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a &
 * board # rmmod ambarella_fb;modprobe ambarella_fb resolution=720x480 mode=clut8bpp buffernum=4
 * board # modprobe cavalry;cavalry_load -f /lib/firmware/cavalry.bin -r
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear_qp.lua --enc-mode 5 --resource-mem-cfg-enable 1
 *         --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua -A -h1080p -b0 --stream-dummy-latency 2 --gop 0 --frame-factor 1/1 -e (for cv5x cooper SDK)
 * board # test_encode --resource-cfg /usr/local/bin/scripts/cv2_vin0_4k_linear_qp.lua --enc-mode 5 --resource-mem-cfg-enable 1
 *         --hdmi 1080p -A -h1080p -b0 --stream-dummy-latency 2 --gop 0 --frame-factor 1/1 -e (for cv2x SDK 3.0)
 * board # test_smartrc_v3 -A -r 8 --cv-enable 1 --cv-src 1 -l 1 -m 3
 * board # test_yolo_live_smartrc -b /root/onnx_yolov3_cavalry.bin  -l /root/label_coco_80.txt --in input.1 --out 290 --out 352 --out 414
 *         -a /root/live_yolov3_anchors.txt  -t 1 -c 80 -s 0 -n 0.7 --width 300 --height 300 (another console)
 * @endcode
 * Note that the canvas settings should be configured in the Lua script for specific CV examples.
 * The @b `enc-dummy-latency` should also be set, as it is used by the SRC library to
 * synchronize CV outputs with preanalysis outputs.
 *
 * The option @b `-c` of the CV application is used to specify the class ID in order to perform SRC control. The
 * meaning of the class ID is as described below:
 *  | CLASS NAME | CLASS ID |
 *  | :-------------: | :-----: |
 *  | BACKGROUND | 0 |
 *  | AEROPLANE | 1 |
 *  | BICYCLE | 2 |
 *  | BIRD | 3 |
 *  | BOAT | 4 |
 *  | BOTTLE | 5 |
 *  | BUS | 6 |
 *  | CAR | 7 |
 *  | CAT | 8 |
 *  | CHAIR | 9 |
 *  | COW | 10 |
 *  | TABLE | 11 |
 *  | DOG | 12 |
 *  | HORSE | 13 |
 *  | MOTORBIKE | 14 |
 *  | PERSON | 15 |
 *  | PLANT | 16 |
 *  | SHEEP | 17 |
 *  | SOFA | 18 |
 *  | TRAIN | 19 |
 *  | TV | 20 |
 *
 * @subsection srcv3_exp_cvo 7.13 Draw CV Boxes
 * If users run cases with CV, they can draw CV box overlays on the stream with the options @b `cv-overlay-enable`
 * and @b `cv-overlay-color`.
 * @code
 * board # init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a &
 * board # rmmod ambarella_fb;modprobe ambarella_fb resolution=720x480 mode=clut8bpp buffernum=4
 * board # modprobe cavalry;cavalry_load -f /lib/firmware/cavalry.bin -r
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear_qp.lua --enc-mode 5 --resource-mem-cfg-enable 1
 *       --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua -A -h1080p -b0 --stream-dummy-latency 2 --gop 0 --frame-factor 1/1 -e (for cv5x cooper SDK)
 * board # test_encode --resource-cfg /usr/local/bin/scripts/cv2_vin0_4k_linear_qp.lua --enc-mode 5 --resource-mem-cfg-enable 1
 *         --hdmi 1080p -A -h1080p -b0 --stream-dummy-latency 2 --gop 0 --frame-factor 1/1 -e (for cv2x SDK 3.0)
 * board # test_smartrc_v3 -A -r 8 --cv-enable 1 --cv-src 1 -l 1 --cv-overlay-enable 1 --cv-overlay-color 1
 * board # test_yolo_live_smartrc -b /root/onnx_yolov3_cavalry.bin  -l /root/label_coco_80.txt --in input.1 --out 290 --out 352 --out 414
 *         -a /root/live_yolov3_anchors.txt  -t 1 -c 80 -s 41 -n 0.7 --width 300 --height 300 (another console)
 * @endcode
 * @image html src_cv_overlay.png "Figure 7-1. SmartRC CV Overlay."
 * - - - -
 *
 * @subsection srcv3_exp_motion 7.14 Choose Motion from CV Bbox or PA Library
 * If users run cases with CV, by default, the motion detection is from the CV Bbox. The option @b `disable-motion-from-cv` can be used
 * to choose motion detection from the PA library.
 * @code
 * board # init.sh --imx290_mipi
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear_qp.lua --enc-mode 5 --resource-mem-cfg-enable 1
 *       --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua -A -h1080p -b0 --stream-dummy-latency 2 --gop 0 --frame-factor 1/1 -e (for cv5x cooper SDK)
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv25_vin0_1080p_linear_mem_cfg.lua --hdmi 720p --resource-mem-cfg-enable 1
 *         --enc-dummy-latency 2 --ors 1280x720 -A -h 1920x1080 -b 0 --stream-dummy-latency 2  --gop 6 --frame-factor 1/1 -e (for CV2x SDK3.0)
 * board # test_smartrc_v3 -A -r 15 --frame-control 1 --roi-control 1 --cv-enable 1 --cv-src 0 -t 0 -l 3 --disable-motion-from-cv 1
 * @endcode
 * - - - -
 *
 * @section srcv3_tuning 8. Tuning Guide
 * Ambarella recommends tuning the `frame_level` parameters first, and then tuning the `roi_level` parameters.
 *
 * @subsection srcv3_frame_level_tuning 8.1 Tuning Frame-Level Parameters
 *
 * There are too many frame-level parameters that can be tuned. Ambarella suggests tuning the GOP length, bit rate,
 * QP limitations, and one-by-one QP reduction first. Then, tune the other parameters for final video
 * quality and bit rate. All frame-level parameters can be found in the default Lua script (smartrc_example.lua).
 *
 * @subsubsection srcv3_gop_tuning 8.1.1 GOP Length
 * Determine the GOP length for different profiles.
 *
 * @note
 * - The higher the profile, the smaller the GOP.
 *
 * The following is an example. Users can determine the GOP for their real use cases.
 * @code
 * Static profile: 180
 * Small motion profile: 120
 * Middle motion profile: 60
 * Big motion profile:30
 * Low light profile: 30
 * @endcode
 *
 * @subsubsection srcv3_bitrate_tuning 8.1.2 Bit Rate
 * Determine the bit rate for different profiles.
 *
 * @note
 * - The higher the profile, the larger the bit rate.
 *
 * Get the acceptable target bit rate via `test_encode` at this stage (do not use `test_smartrc_v3`).
 *
 * Find the lowest-possible bit rate which results in acceptable video quality. For example, set the target bit rate to 1 Mbps
 * for the specified 1080p30 stream of the real case scene at the beginning, and then increase the bit rate if
 * the video quality is not acceptable (or decrease it if it is acceptable).
 *
 * @code
 * board # test_encode -A -h 1080p -bitrate 800000 -N 60
 * board # test_encode -A -h 1080p -bitrate 700000 -N 60
 * board # test_encode -A -h 1080p -bitrate 600000 -N 60
 * @endcode
 *
 * When obtaining a reasonable bit rate for the real case scene, find the bit rate for big-motion scenes first.
 * Once the big-motion bit rate is a reasonable value, users can set 80% of the big-motion bit rate for mid-motion profiles, and 80% of
 * the mid-motion bit rate for small-motion profiles, and 80% of the small-motion bit rate for static scenes. 80% is a suggested value;
 * users can determine the correct coefficient according to their real scenes.
 *
 * @subsubsection srcv3_qp_limitation_tuning 8.1.3 QP Limitation
 * Determine the QP limitation for different frames for different profiles.
 *
 * @note
 * - For I frames, users can set lower values for both the minimum / maximum of `i_qp_limit`, compared to P frames.
 * This results in improved quality for I frames. Better I-frame quality allows for better video quality.
 * - Users can set proportionally larger values for both the minimum /
 * maximum of `qp_limit` for larger profiles, as they already have a greater bit rate.
 * - Ambarella suggests setting a relatively wide range for `qp_limit` (do not set a narrow range).
 *
 * When obtaining a reasonable bit rate, the bit rate may lose control and exceed or fail to reach the target.
 * This occurs due to unsuitable QP parameters, particularly QP limitations. Before
 * analyzing these cases, it is important to note the following:
 *
 * - The rate controller inside the DSP pre-allocates bits for each frame according to the target bit rate,
 * GOP length, encoding fps, and the allocation for the former GOP. The bits for different types of frames
 * are allocated with different weights, which are determined by the QP reduction parameters (such as
 * `i_qp_reduce` and `p_qp_reduce`).
 *
 * - Once the bits are pre-allocated, the rate controller inside the DSP obtains a reference QP called "slice
 * QP". After adding the QP offset of ROI matrixes on the slice QP, the rate controller can obtain the QP for
 * each MB / CTU.
 *
 * - However, it is not the final value, as the rate controller compares it with the QP limitations
 * (which are specified by the user’s options). If the value is beyond the boundaries of the limitation, the controller
 * uses the boundary values as the final QP for each MB / CTU. Otherwise, the QP is considered as
 * valid, and it is used as the final QP for the MB / CTU.
 *
 * - Further, note that the controller allows the QP to exceed the boundaries
 * within a certain range if the parameter `adapt-qp` is set.
 *
 * - The bits spent for each MB / CTU depends on the QP value and the codec type. The smaller the QP,
 * the more bits are spent on each MB / CTU.
 *
 * The issue of the real bit rate being unable to reach the target value occurs because the target bit rate is
 * too high, and the QP of each MB / CTU calculated according to the bit rate pre-allocation is smaller than
 * the minimum value of the QP limitations, so the controller takes the boundary value instead of the
 * QP value that was calculated. In this case, the real bit rate is limited by the QP limitations. To solve this issue,
 * Ambarella recommends decreasing the minimum value of the QP limitations.
 *
 * @code
 * board # test_encode -A -h 1080p --bitrate 800000 -N 60 --qp-limit-i 20~51
 * board # test_encode -A -h 1080p --bitrate 800000 -N 60 --qp-limit-i 13~51
 * @endcode
 *
 * @subsubsection srcv3_qp_reduce_tuning 8.1.4 QP Reduction
 * Determine QP reduction for different frames of different profiles.
 *
 * @note
 * - In cases when the bit rate is very sensitive, and the user requires a relatively low bit rate, the user can increase
 * `i_qp_reduce`. This operation allocates more bits on the I frame, which results in improved video quality.
 * - In cases when the final bit rate exceeds the target value, one possibility is that the target bit rate is too
 * low, which leads to the decreased quality for the current frame. When next frame is encoded, the difference between
 * reference frame is large, causing most of the MB / CTU to be encoded as intra or inter even in static scenes. 
 * Many more bits than expected are used in this case. To resolve this issue, increase the I frame QP reduction value. The encoder
 * allocates more bits for the I frame and decreases the maximum value of I frame QP limitations, which results in an improved I frame,
 * which is used as a reference. If this method does not resolve the issue, increase the target bit rate.
 *
 * @code
 * board # test_encode -A -h 1080p --bitrate 800000 -N 60 --qp-limit-i 20~51 --i-qp-reduce 4
 * board # test_encode -A -h 1080p --bitrate 800000 -N 60 --qp-limit-i 13~51 --i-qp-reduce 6
 * @endcode
 * 
 * @subsubsection srcv3_skip_frame_drop_frame_tuning 8.1.5 Skip_frame and Drop_frame
 * Determine `skip_frame` and `drop_frame` only for static profiles.
 *
 * For static profiles, users can enable `skip_frame` or `drop_frame` to save bit rates. Only one is
 * supported for static profiles.
 *
 * @subsubsection srcv3_chroma_qp_offset_tuning 8.1.6 Chroma_qp_offset
 * Determine the chroma QP offset for different profiles.
 *
 * When there is no bit rate margin, but there is a video color artifact, users can set a reasonable chroma
 * QP offset for the real scene.
 *
 * @subsubsection srcv3_zmv_threshold_qp_offset_tuning 8.1.7 Zmv_threshold_qp_offset
 * Determine `zmv_threshold_qp_offset` for ZMV MBs.
 *
 * @note
 * - `zmv_threshold_qp_offset` is only supported for CV2x and H.264.
 * - This should be combined with the ROI-level parameter `zmv_threshold`, which is used for rate control inside the DSP to figure out
 * small noise on a stationary background. If there is a small amount of noise on a stationary background, the MB is encoded as skip;
 * otherwise, the rate control will add `zmv_threshold_qp_offset` for these MBs.
 *
 * @subsection srcv3_roi_level_tuning 8.2 Tuning ROI-Level Parameters
 *
 * Due to the large number of ROI-level parameters, only some can be tuned at one time. There are different ROI
 * maps (static maps, motions map, and UA maps) for different profiles; users can set different ROI-level parameters for these
 * different MBs / CTUs based on the maps. All frame-level parameters can be found in the default Lua script.
 *
 * @subsubsection srcv3_qp_adjust_tuning 8.2.1 QP Adjust (QP Offset)
 *
 * Determine the QP adjustment (QP offset) for different profiles. Users can get improve quality for the specific ROI area by
 * setting a reasonable QP adjustment value.
 *
 * @note
 * - The QP adjustment values for uncovered-area ROIs should be larger negative values than those of motion ROIs, and the QP adjustment
 * values for motion ROIs should be more negative than those of static ROIs (for example, -8 for the uncovered-area ROI, -5 for the
 * motion ROI, and 0 for the static ROI).
 *
 * - The larger the profile, the less negative the QP adjustment is (for example: -8 for big-motion profiles, -6 for uncovered-area
 * ROIs, -4 for motion ROIs, 0 for static ROIs, -4 for mid-motion profiles, -8 for uncovered-area ROIs, -6 for motion ROIs, and
 * -2 for static ROI).
 *
 * @subsubsection srcv3_user_class_tuning 8.2.2 User Class
 * Determine `user_class` for different ROI. This is used for H.264 encoding.
 *
 * @note
 * - For static ROIs, set `user_class = 1` to be encoded as skip type for this MB in order to conserve static MB bit rates.
 * - For motion and uncovered-area ROIs, `set user_class = 2` to be encoded as intra / cinter type for this MB.
 * - Users can set `user_class = 0` for static / motion / uncovered-area ROIs, which enales the DSP to choose the encoding
 * type for these MBs / CTUs.
 *
 * @subsubsection srcv3_category_tuning 8.2.3 Category
 * Determine the category for different ROIs. This is used for H.265 encoding.
 *
 * @note
 * - Set reasonable categories in the range [0, 4] for different ROIs.
 * - For static ROIs, set `category = 4` to be force encoded as skip type. This can save static MB bit rates;
 * Ambarella recommends that this is used in static profiles only.
 * - For uncovered-area ROIs, set `category = 3` to be force encoded as UC.
 * - For motion ROIs, set `category = 2` to be force encoded as intra type.
 * - Users can set `category = 0` for all ROIs, which enables the DSP to choose the encoding type for these MBs / CTUs.
 *
 * @subsubsection srcv3_zmv_threshold_tuning 8.2.4 ZMV Threshold
 * Determine the ZMV threshold for different ROIs.
 *
 * @note
 * - ZMV threshold is only supported on CV2x and for H.264 encoding.
 *
 * Ambarella recommends setting `zmv_threshold = 8 (or 16)` for static ROIs. This is used for rate control inside the DSP
 * to mitigate small amounts of noise on a stationary background. If it is a small amout of noise, it will be encoded as skip
 * type; otherwise, `zmv_threshold_qp_offset` will be applied on the MB.
 *
 * Ambarella does not recommend setting `zmv_threshold` for other ROIs.
 *
 * @subsection srcv3_fine_tuning 8.3 Fine-Tuning by EFR
 * After reasonable frame-level parameters have been set, users can use `test_smartrc_v3` to tune ROI-level parameters 
 * to improve video quality and bit rate. Follow the steps below.
 *
 * -# Capture high bit-rate (such as 20 MB) video clips under real use case scenes. Users can also capture
 * YUV sequences. Ensure that the video clips include different motions under real use case scenes.
 *
 * -# Decode the video clips to YUV sequences (NV12 format) with ffmpeg. This step is not required when
 * YUV sequences are captured.
 * @code
 * ffmpeg -i input.mp4 -an -pix_fmt nv12 -s 2592x1944 -filter:v "select='between(n\, 0\, 660)'" output_nv12.yuv
 * @endcode
 *
 * -# Perform a raw encode with the NV12 YUV sequences, and then use it to begin encoding.
 *
 * -# Run `test_smartrc_v3` with reasonable frame-level parameters, and tune the ROI-level parameters as needed.
 *
 * -# Begin capturing this stream, which enables SmartRC. Check the stream's quality and bit rate.
 *
 * -# Update the ROI-level parameters if the video quality or bit rate is not acceptable, then perform steps 4 and 5.
 *
 * - - - -
 *
 * @section srcv3_faq 9. FAQ
 * This chapter lists possible questions and answers related to the SmartRC library, helping
 * readers to understand SmartRC.
 *
 * @b Question: Does the SmartRC library have different encoding standards for H.264 / AVC
 * and H.265 / HEVC?
 *
 * @b Answer:  No, because the SmartRC library is an optimization of the H.264 / AVC and
 * H.265 / HEVC encoder that is used in rate control to improve efficiency, especially for security IP cameras
 * with a static background.
 *
 * @b Question: What's the unit for threshold specified in smartrc lua script, and what is it used for?
 *
 * @b Answer:
 * -# For threshold_0's level none / low / mid / high, it is frame-level threshold, its unit is a percentage with multipy 1000000,
 * such as low = 300, mid = 30000, it means 300 / 1000000 = 0.03%, 30000 / 1000000 = 3%. When motion value is in range [0, low),
 * this frame is a static frame; when it is in range [low, mid), it is a low-motion frame; when it is in range [mid high), it is
 * a mid-motion frame; and when it is larger than high, it is a high-motion frame.
 *
 * -# For threshold_0's scene none / low / mid / high, it is scene-level threshold, its unit is also percentage, it means how many
 * different motion-type frame in one GOP. It is used for switching from low motion profile to high motion profile, in this situation,
 * smartrc will switch profile immediately but not wait one GOP time. It is used to switch to different motion profiles.
 *
 * -# For threshold_1's level none / low / mid / high, it is frame-level threshold, only low and high is valid, and its unit is sensor
 * agc db value. When sensor agc db value is in range [0, low), it is a none-noise frame; when it is in range [low, hight), it is a
 * low-nosie frame; when its value is larger than high, it is a high-noise frame.
 *
 * -# For threshold_1's scene none / low / mid / high, it is scene-level threshold, only low and high is valid, its unit is noise frame
 * counts, means how many different noise-type frame. It is used to switch to low light profile.
 *
 * @b Question: How and when does SmartRC library switch to a new profile?
 *
 * @b Answer: Bacially, for each frame, SmartRC libarary calculates its motion value, and determines frame's motion level by comparing
 * motion value with frame level threshold (determined inside lib or user specified by threshold_0's level none / low / mid / high value and
 * threshold_1's level none / low / mid / high value).
 * Meanwhile, SmartRC libarary counts different frame types (static frames / motion frames) in one GOP and determine scene motion level in this
 * GOP based on the motion threshold (determined inside lib or user specified by threshold_0's scene none / low / mid / high value and threshold_1's
 * scene none / low / mid / high value). If the scene motion level changed, then SmartRC switches to a new profile, different GOP length and
 * different stream framerate may take different time for the switch.
 * When switching to low motion profile, SmartRC libarary will switch proflie step by step : high motion --> mid motion --> low motion --> static.
 * When switching to high motion profile, SmartRC libarary will switch proflie immediately but doesn't wait one GOP.
 *
 * @b Question: When does SmartRC libarary apply frame level parameters?
 *
 * @b Answer: Smartrc libarary will apply new frame level encoding parameters to DSP when switching to a new profile, including GOP structure, qp
 * parameters (including bitrate, qp_reduce, qp_limit, adapt_qp), ...
 *
 * @b Question: When does SmartRC libarary apply ROI level parameters?
 *
 * @b Answer: Smartrc libarary will apply new ROI level encoding parameters to DSP for every frame runtime no matter if switching to a new
 * profile or not.
 *
 * - - - -
 *
 * @section srcv3_api 10. SmartRC APIs
 * Visit the following links for details of the API functions.
 *      - @ref srcv3-api explains API functions.
 *      - @ref srcv3-helper shows related structures, macros, and enumerations.
 *
 * - - - -
 *
 * @section srcv3_lic 11. License
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
 */

/*!
 * @defgroup srcv3-api SmartRC Library API
 * @brief SmartRC Library API
 */
/*!
 * @defgroup srcv3-general-api SmartRC Library General API Details
 * @ingroup srcv3-api
 * @brief SmartRC Library General API, in file lib_smartrc.h
 */
/*!
 * @defgroup srcv3-server-api SmartRC Library Server API Details
 * @ingroup srcv3-api
 * @brief SmartRC Library Server API, in file lib_smartrc_server_api.h
 */
/*!
 * @defgroup srcv3-client-api SmartRC Library Client API Details
 * @ingroup srcv3-api
 * @brief SmartRC Library Client API, in file lib_smartrc_client_api.h
 */
/*!
 * @defgroup srcv3-lp-api SmartRC Library Lua Parser API Details
 * @ingroup srcv3-api
 * @brief SmartRC Library Lua Parser API, in file lib_smartrc_lp.h
 */

/*!
 * @defgroup srcv3-helper SmartRC Library helper
 * @brief SmartRC Library helper
 */
/*!
 * @defgroup srcv3-general-helper SmartRC Library General Helper
 * @ingroup srcv3-helper
 * @brief SmartRC Library General Helper, in file lib_smartrc_common.h
 *
 */
/*!
 * @defgroup srcv3-client-helper SmartRC Library Client Helper
 * @ingroup srcv3-helper
 * @brief SmartRC Library Client Helper, in file lib_smartrc_client_structure.h
 */

/*!
 * @example test_smartrc_v3.c
 * @example test_smartrc_ssd_live.c
 * These two files are the source code of apps.
 *
 */
/*!
 * @file doc_lib_stitch.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2019-02-21
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
 * @page page_lib_stitch_doc Stitch Library API
 *
 * @section stitch_history 0. Revision History
 *
 * <table>
 * <caption id="Stitch library"></caption>
 * <tr><th> Library Version   <th align="left">Updated Date<th align="left">Chip<th align="left"> Modification
 * <tr><td> 0.3.4             <td>20190524        <td>CV2x               <td>Initial Version
 * <tr><td> 1.0.0             <td>20200109        <td>CV2x               <td>Added backward mapping and raw encode for stitching
 * <tr><td> 1.2.0             <td>20200213        <td>CV2x               <td>Added calibration on chip
 * <tr><td> 2.0.0             <td>20200426        <td>CV2x               <td>Added dual fisheye lens for 360 degree panorama view stitching
 * <tr><td> 2.0.6             <td>20210115        <td>CV2x               <td>Added 6x4M performance @ref stitch_features
 * <tr><td> 2.0.6             <td>20210223        <td>CV2x               <td>Added support for skipping sub source buffer blend pass @ref stitch_skip_blend
 * <tr><td> 2.1.0             <td>20210427        <td>CV2x               <td>Added support for vertical stitching with rotate input @ref stitch_pro_rotate
 * <tr><td> 2.1.1             <td>20210629        <td>CV2x               <td>Refined homography cylindrical projection formula
 * <tr><td> 2.1.2             <td>20210629        <td>CV2x               <td>Fixed the issue of projection formula
 * <tr><td> 2.1.3             <td>20210713        <td>CV2x               <td>Added support for using grid level map to perform LDC
 * <tr><td> 2.1.4             <td>20210722        <td>CV2x               <td>Added support for disparity difference to create configrations for specific distance stitching
 * <tr><td> 2.2.0             <td>20210807        <td>CV2x               <td>Added support for keeping specific output resolution
 * <tr><td> 2.2.0             <td>20210904        <td>CV2x               <td>Added reference link of lens / pose calibration
 * <tr><td> 2.2.0             <td>20210921        <td>CV2x               <td>1. Fixed issue in stitch_set_seam_line 2. Changed radius for keeping seam
 * <tr><td> 2.3.1             <td>20220105        <td>CV2x               <td>Added support for increasing stitching max height from 2160 to 3840
 * <tr><td> 2.3.2             <td>20220117        <td>CV2x               <td>Added support for doing dewarp in pixel level
 * <tr><td> 2.3.2             <td>20220119        <td>CV2x               <td>Updated Section @ref stitch_calib "2.4 Calibration Process"
 * <tr><td> 2.3.2             <td>20220308        <td>CV2x               <td>Updated Section @ref stitch_insert_pm "2.5.8 Stitch Privacy Mask"
 * <tr><td> 2.3.2             <td>20220328        <td>CV2x               <td>Updated Section @ref stitch_simulation "2.5.11 Stitch Simulation"
 * <tr><td> 2.3.2             <td>20220510        <td>CV2x               <td>Updated Section @ref sec_stitch_faq "4 Stitch FAQ"
 * <tr><td> 2.3.3             <td>20220510        <td>CV2x               <td>Added support for specifying grid number of warp table
 * <tr><td> 2.3.4             <td>20220616        <td>CV5x               <td>Updated Section @ref stitch_channel_rotate "2.5.6 Stitch with Rotated channels"
 * <tr><td> 2.3.5             <td>20220803        <td>CV2x               <td>Updated Section @ref sec_stitch_faq "4 Stitch FAQ"
 * <tr><td> 2.3.5             <td>20220803        <td>CV5x               <td>Updated Section @ref stitch_eight_channels_stitching "2.5.7 Stitch with 6x / 8x Channels"
 * <tr><td> 2.3.6             <td>20220907        <td>CV5x               <td>Updated Section @ref stitch_pro_parameters 2.5.1 Stitching Configration File Descriptions
 * <tr><td> 2.3.6             <td>20220908        <td>CV2x               <td>Added support for alpha-blending for 6th source buffer
 * <tr><td> 2.3.7             <td>20220922        <td>CV2x               <td>Changed grid spacing order to grid spacing width / height pixel value.
 * <tr><td> 2.3.8             <td>20221025        <td>CV2x               <td>Updated Section @ref stitch_pro_rotate "2.5.5 Stitch with with Rotated Channels"
 * <tr><td> 2.3.8             <td>20221101        <td>CV5x               <td>Updated Section @ref stitch_calib_lsc "2.4.1 LSC Calibration"
 * <tr><td> 3.0.0             <td>20221101        <td>CV2x               <td>Updated Section @ref stitch_pro_dual "2.5.11 Stitch Dual Fisheyes for 360 Degree Panoramic"
 * <tr><td> 3.0.0             <td>20221215        <td>CV2x               <td>Updated Section @ref stitch_simulation "2.5.14 Stitch with Customers' Warp Table and Alpha Table"
 * <tr><td> 3.0.1             <td>20230110        <td>CV2x               <td>Updated Section @ref stitch_backwarp_map "2.5.12 Stitch Backward / Forward Mapping"
 * <tr><td> 3.0.2             <td>20230327        <td>CV2x               <td>Fix some warnings
 * <tr><td> 3.0.3             <td>20230404        <td>CV5x               <td>Updated Section @ref stitch_pro_tilt "2.5.17 Stitch in horizontal direction with angles below the horizon"
 * <tr><td> 3.0.4             <td>20230528        <td>CV5x               <td>Updated Section @ref stitch_update_warp_table "2.5.15 Stitch with updating warp table on the fly"
 * <tr><td> 3.0.4             <td>20230528        <td>CV5x               <td>Updated Section @ref stitch_simulate_with_pose_results "2.5.16 Stitch Simulation with Pose Calibration Results"
 * <tr><td> 3.0.4             <td>20230528        <td>CV5x               <td>Updated Section @ref sec_stitch_faq_q7 "Question 7: How to make calibration data compatible with new version SDK?"
 * <tr><td> 3.0.5             <td>20230727        <td>CV5x               <td>Updated Section @ref stitch_pro_dual "2.5.11 Stitch Dual Fisheyes for 360 Degree Panoramic"
 * <tr><td> 3.0.6             <td>20230802        <td>CV5x               <td>Updated Section @ref sec_stitch_faq_q7 "Question 7: How to make calibration data compatible with new version SDK?"
 * <tr><td> 3.0.7             <td>20230802        <td>CV5x               <td>Added compatibility for old warp table of vertical case
 * <tr><td> 3.0.8             <td>20230811        <td>CV5x               <td>Fix artifact in the boundary
 * <tr><td> 4.0.0             <td>20231020        <td>CV5x               <td>Added Section @ref stitch_pro_tilt_vhvh
 * <tr><td> 4.0.1             <td>20231221        <td>CV5x               <td>Fix issues in the calculation of horizontal vector
 * <tr><td> 4.1.0             <td>20231226        <td>CV5x               <td>Added VH dewarp pipeline
 * </table>
 *
 * - - - -
 *
 * @section stitch_introduction 1. Introduction
 *
 * The CV2x and CV5x series of chips support multi-channel stitching.
 * This chapter introduces basic information on image stitching.
 *     - Section @ref stitch_features
 *     - Section @ref stitch_concept
 *     - Section @ref stitch_solutions
 *     - Section @ref stitch_blending_solution
 *
 * @subsection stitch_features 1.1 Ambarella Stitching Features
 * Some basic stitching features are listed below.
 *  | Stitching Mode             | Channels | Projection Mode                   | Performance                    |
 *  | :-------                   | :------- | :------------                     | :------------                  |
 *  | Horizontal stitching       | 2x/3x/4x | Cylindrical / perspective         | 4ch x 5MP20 HEVC               |
 *  | Vertical stitching         | 2x/../6x | Transverse Mercator / cylindrical | 4ch x 5MP20 / 6ch x 4MP14 HEVC |
 *  | Dual-channel 360 stitching | 2x       | Equirectangular                   | --                             |
 *
 * Tool versions for the software development kit (SDK) are listed below. <br>
 *  | SDK Version  (CV5x)   | Lens Tool Version                                              |  Pose Tool Version  |
 *  | :-------              | :-------                                                       | :------------       |
 *  | 2.0                   | cv5x_cv2x_lens_calibration_tool_for_windows_v2.0.8_20230207.tar | cv5x_cv2x_pose_calibration_tool_for_windows_v0.2.5_20221024.tar |
 *  | 2.5                   | cv5x_cv2x_lens_calibration_tool_for_windows_v2.0.8_20230207.tar | cv5x_2x_pose_calibration_tool_for_windows_v1.0.0_20230220.tar   |
 *  | Cooper 1.0            | cv5x_cv2x_lens_calibration_tool_for_windows_v2.0.9_20230530.tar | cv5x_cv2x_pose_calibration_tool_for_windows_v1.0.6_20230628.tar |
 *  | Cooper 1.5            | cv5x_cv2x_lens_calibration_tool_for_windows_v2.0.9_20230530.tar |cv5x_2x_pose_calibration_tool_for_windows_v1.3.0_20231023.tar |
 *  | Cooper 1.6            | cv5x_cv2x_lens_calibration_tool_for_windows_v2.0.9_20230530.tar |cv5x_2x_pose_calibration_tool_for_windows_v1.5.0_20240116.tar |
 *
 * @subsection stitch_concept 1.2 Image Stitching
 * Image stitching is an important research direction for computer vision (CV) and image processing.
 * It is a complex process that involves computer graphics, graph theory, software development, and more. <br>
 * The image stitching technology combines images captured by different
 * cameras; this technology can enlarge the field of view (FoV) and raise the
 * image resolution. The image stitching process includes the two following stages: <br>
 * - Image calibration <br>
 * - Image stitching <br>
 * In addition, a natural intergradation effect can be obtained using the related
 * blending algorithms to synchronize the luminance,
 * color, exposure window of different cameras, and so on.
 *
 * @subsection stitch_solutions 1.3 Stitching without Alpha Blending
 * @image html image_stitch.jpg "Figure 1-1. Image Stitching."
 * Fixed-line stitching is a simple method to join images together.
 * In this example, the image to the left of the fixed line comes from the left side, and the image to the right of the fixed line comes from the right side.
 * This solution facilitates the blending process, and ensures the quality is stable
 * without any large fluctuations.
 * A disadvantage of this solution is that the image boundary is noticeable.
 *
 * @subsection stitch_blending_solution 1.4 Stitching with Alpha Blending
 * As users perform fixed-line stitching, the channel junction traces are
 * relatively shallow. However, as @ref stitching_pose_result shows,
 * the traces are still there. If users want to make the channel junction almost
 * invisible in a particular situation, Ambarella recommends that
 * users consider alpha blending, which may result in sacrificing
 * around 15% ~ 20% of image digital signal processor (IDSP) performance and dynamic random-access memory (DRAM) bandwidth.
 *
 * @subsubsection stitch_solutions_linear 1.4.1 Linear-Blending Stitching
 * @image html linear_blending.jpg "Figure 1-2. Linear Line-Blending Stitching Example Image."
 * Linear blending uses an alpha table to adjust the transparency of the overlap area.
 * This enables the area to gradually transfer from one image to the other.
 * The overlap width is about 15% of the original image width.
 * If the images are aligned sufficiently, the blending width can be reduced, resulting
 * in a better blending result for a moving object.
 * On the other hand, if the images are misaligned, this width must be increased.
 * The advantage of this solution is that the image border is not visible and the
 * stitching result is stable.
 * The disadvantage of linear stitching is that when there is a large difference in
 * the distance between objects, at least one of the objects will be blurred.
 *
 * @subsubsection stitch_solutions_dyna 1.4.2 Dynamic Seam Line Blending Stitching
 * The dynamic seam line solution uses the best seam line searching algorithm.
 * Based on the current input images, this algorithm outputs the minimum visual
 * effect difference seam line's position of the overlap zone.
 * The advantage of this solution is that it can bypass the areas and make the
 * merged image appear soft and natural.
 * The disadvantage is that video fluctuation can appear in the overlap zone.
 * The seam line is recalculated for each frame, so it is possible that the best
 * seam line for each frame will not be the same.
 * Moreover, the complexity of the algorithm must be limited, given that the
 * update period is about 30 ms per frame.
 *
 * @subsection stitch_solutions_blend 1.5 Stitching Result Comparison
 * <b>Original images:</b>
 * @image html left_right.jpg "Figure 1-3. Original Left and Right Images."
 *
 * <b>Fixed line stitching:</b>
 * @image html fix_stitching.jpg "Figure 1-4. Fixed Line Stitching."
 *
 * <b>Linear blending stitching:</b>
 * @image html linear_stitching.jpg "Figure 1-5. Linear Stitching."
 *
 * <b>Dynamic seam line blending stitching:</b>
 * @image html dyna_stitching.jpg "Figure 1-6. Dynamic Seam Line Stitching."
 *
 * - - - -
 *
 * @section stitch_design 2. Design
 * This chapter provides information on the design of the stitching system.
 *     - Section @ref stitch_cap
 *     - Section @ref stitch_soft
 *     - Section @ref stitch_sys
 *     - Section @ref stitch_calib
 *     - Section @ref stitch_pro
 *
 * @subsection stitch_cap 2.1 Capture Device Structure
 * @image html expand.jpg "Figure 2-1. Expanding Structure for Capture Device."
 * In order to enlarge the total FoV, an expanding structure is used for the image
 * capture device:
 * Because the capture device is composed of at least two cameras, similar to human
 * eyesight, there are some parallaxes between the images captured by these cameras.
 * If an object is too close to the camera, it is not possible to stitch the two
 * images together without distortion.
 * Therefore, a minimum distance between the cameras and the object is required
 * (example: 6 meters).
 * @image html close.jpg "Figure 2-2. Blending Result for Close Object."
 * Users should note that objects closer to the eye appear larger. As a result,
 * if the same horizontal offset is applied to different object distances, at least
 * one of the objects will be positioned incorrectly.
 * Therefore, if two object distances overlap, at least one of them will not be
 * perfect. For a related demonstration, refer to the appendix.
 *
 * @subsection stitch_soft 2.2 Software Structure
 * The software structure contains three parts: the application, the driver, and the library.
 *
 * Application
 *
 * * User interface: obtains the input parameters from the command-line interface to set
 *   up the action of the application and the parameters for calibration and stitching.
 * * Image capture: obtains the YUV of the current scene.  Then, it sends an input / output (I/O) control message to the driver.
 *   The driver sends back the address of the image in DRAM.
 * * Apply calibration: sends the left (or top) YUV address and the right (or bottom)
 *   YUV address to the library for calibration.
 *   Then, it sends the calibration parameters to the library and receives the
 *   shifting value from the library.
 * * Apply stitching: sends the left (or top) YUV address and the right (or bottom)
 *   YUV address to the library for stitching.
 *   Then, it sends the stitching parameters to the library and retrieves the
 *   updated data from the alpha table.
 *
 * Driver
 *
 * The driver is used to communicate with the digital signal processor (DSP). It acts as the bridge for the
 * application and the DSP.
 * The alpha table data is copied to a specific dynamic random access memory (DRAM) in the Linux kernel.
 * Once this table is updated, it must wait for the DSP to consume it.
 * The YUV data address for stitching analysis is retrieved by the interruption
 * and fed back to the application.
 *
 * Library
 *
 * @image html soft.jpg "Figure 2-3. Software Structure."
 * * Calibration: the library receives the left (or top) image and the right (or bottom image) from the application.
 *   Afterwards, it receives the calibration parameters from the application and
 *   calculates the shifting value for the image pair.
 *   Then, it sends the shifting value back to the application.
 * * Stitching: the library receives the left (or top) image and the right (or bottom) image from the application.
 *   Then, it gets the stitching parameters from the application. Finally, it
 *   calculates the seam line for this image pair to create the alpha table.
 *
 * @subsection stitch_sys 2.3  System Flow
 * There are two steps in this process:
 * - Calibration
 * - Stitching
 *
 * The steps are independent from one another.
 * In the calibration step, the input images come from the camera. This means
 * that the calibration will be based on the current scene.
 * Image pre-processing includes automatic exposure (AE) and automatic white balance (AWB) adjustment, noise elimination, and more.
 * The calibration model provides the image scale, rotation, and shift factors.
 * In the stitching step, the input images come from the cameras.
 * Then, it pre-processes the image using the calibration parameters obtained from the calibration process.
 * Afterwards, it finds the best seam line for the current images and creates an alpha table.
 *
 * @subsection stitch_calib 2.4 Calibration Process
 * The calibration process consists of three stages: lens shading calibration (LSC), lens calibration, and pose calibration. <br>
 * LSC should be performed on the host PC. The user can use amba_calibration_v2.6.exe to perform the calibration;
 * Contact the Ambarella support team for these tools.  <br>
 * Lens calibration should be performed on the host PC because it is a long process.  <br>
 * Pose calibration can be performed either on the host PC or on the chip.  <br>
 *
 * @subsubsection stitch_calib_lsc 2.4.1 Lens Shading Calibration (on Host Windows Side)
 * @image html shading.jpg "Figure 2-4. Lens Shading."
 * The term shading describes the light fall-off or color variation from the sensor center to the corners that do not originate from the captured scene.
 * Users must perform LSC to remove the lens shading. <br>
 * Ambarella suggests setting the color temperature to 5000K for the lamp box.
 * The command should follow the rule amba_calibration_vX.X.exe MODE SOURCE PATH PREFIX WIDTH HEIGHT BLC PATTERN CENTERX CENTERY  <br>
 *
 * MODE: 2 <br>
 * SOURCE: 0 <br>
 * PATH: the path of the RAW data <br>
 * PREFIX: the prefix of the RAW data <br>
 * WIDTH: width of the RAW data <br>
 * HEIGHT: height of the RAW data <br>
 * BLC: black level of the RAW data <br>
 * @image html blc.jpg "Figure 2-5. Black Level Correction Value."
 * PATTERN: Bayer RAW pattern <br>
 * @image html bayer_pattern.jpg "Figure 2-6. Bayer Pattern Value."
 * CENTERX: center in the horizontal direction. If it is set to 0, the tool will caculate it automatically <br>
 * CENTERY: center in the vertical direction. If it is set to 0, the tool will caculate it automatically <br>
 *
 * @code {.c}
 * The folder "lsc_bin" should be created in the path E:\resolved_problem\stitching\3A\0\ first.
 * amba_calibration_vx.x.exe 2 0 E:\resolved_problem\stitching\3A\0\ cap_raw_raw_3840x4320_0 3840 2160 1024 1 0 0
 * the log is shown below ：
 * vig_result->model_center_R = [942, 561]
 * vig_result->model_center_Gr = [942, 561]
 * vig_result->model_center_Gb = [942, 561]
 * vig_result->model_center_B = [942, 561]
 * separate_raw.size.width = 1920
 * separate_raw.size.height = 1080
 * cal LSC calibration Done!
 * -------------end------------
 * @endcode
 *
 * The calibration data is stored in the folder "lsc_bin". <br>
 * Rename the bin in "lsc_bin" to a name such as "vin0_3840x2160_cali_lens_shading.bin"; 0 is the video source (VSRC) name. <br>
 * Copy the "vin0_3840x2160_cali_lens_shading.bin" to the path `/usr/share/ambarella/idsp/calibration/` in the board,
 * and modify the Lua file /usr/share/ambarella/idsp/aaa_iq_config.lua. <br>
 * @image html lsc_loadding.jpg "Figure 2-7. Loading LSC Bin Configuration."
 * When users run "test_aaa_service -a", the calibration data will be loaded automatically.
 *
 * @subsubsection stitch_calib_lens 2.4.2 Lens Calibration (on Host Windows Side)
 * Refer to @ref guide_sensor_calib_lens "2. Lens Calibration" for more details. <br>
 * Lens calibration is used to estimate the intrinsic parameters and distortion parameters. <br>
 * Intrinsic parameters: focal length / principal point <br>
 * Distortion parameters: radial distortion and tangential distortion <br>
 * Ambarella suggests using the following lens model: <br>
 * Horizontal mode: EVETAR N125b03518w <br>
 * Vertical mode: EVETAR M127B02820WM12 <br>
 *
 * @subsubsection stitch_calib_chip 2.4.3 Stitch Pose Calibration (on Chip)
 * Refer to @ref sensor_calib_stitch "1. Stitching Pose Calibration" for more details. <br>
 * - There are four April tags in one pattern; it is assumed that each tag has its own corner ID
 * (the angle of the April tag is different and the corner ID is from 0~3).
 * As the pose calibration algorithm must use the same corner ID, the user
 * should first query the common corner ID.
 * "--debug 7" is the option to list all corner IDs. <br>
 * - Storing many frames of YUV on the flash is a waste of memory; extracting the
 * pattern information (include circle image position / object position) will be
 * helpful. "--debug 6" is used to save target information.
 * "--no-yuv" is specified to use previous stored target information. <br>
 * - Users can specify stitching distance to create certain configuration information.
 * "--sensor-dist" is used to specify the stitching distance. <br>
 * Performing pose calibration on the chip is suitable for environment-independent applications.
 * As pose calibration must be performed for all equipment, using the calibraiton
 * tool on board is much more efficient. <br>
 * Users can refer to @ref page_lib_sensor_calib_doc "Sensor Calibration Library API"
 * for more pose calibration details.
 *
 * @subsubsection stitch_calib_example 2.4.4 Stitch Calibration Example
 * The following is an example to perform the calibration for four-channel vertical stitching.
 * - Refer to @ref lens_calib_flow "2.2 Lens Calibration Flow" to learn the
 *    dataset capture method and the lens calibration process. <br>
 * - Refer to @ref stitching_pose_flow "5.3 Stitching Pose Calibration Flow" to
 *    learn the pose calibration process. <br>
 * - Refer to @ref stitching_cmd_list "5.4 Multi-Channel Stitching Example" to
 *    learn the run stitching case commands. <br>
 *
 * @subsection stitch_pro 2.5 Stitching Process
 * After the calibration process, the stitch library reports the calibration parameters to the application.
 * Users must confirm if the result represents the optimal offset for each channel.
 *
 * @subsubsection  stitch_pro_parameters 2.5.1 Stitching Configration File Descriptions
 * Some descriptions of the options are provided in test_stitch utility: <br>
 *  | Field | Value | Details |
 *  | :----: | :----: | :----: |
 *  | A / B / C / D / E | 1  | Specify the overlap ID |
 *  | i | 1  | Channel ID |
 *  | width | 1920  | Width |
 *  | height | 1080  | Height |
 *  | mode | 3  | 0: map out to VIN; 1: merge data; 2: perform dewarp; 3: blending; 4: mapping point from VIN |
 *  | map-point | 960,540  | Specify the point in the output image and map the point in the VIN domain |
 *  | seam-method | 0  | Seam-line type. 0: dynamic plan method, 1: graphcut method |
 *  | seam-write | x  | Save the seam line position in the overlap area |
 *  | seam-read | x  | Read the seam line position; create and apply the alpha table |
 *  | top | 0~shift_hor,0~3840  | Indicate the position and number of top rows in order to prevent performance of seam-line searching |
 *  | bottom | 0~shift_hor,0~3840  | Indicate the position and number of down rows in order to prevent performance of seam-line searching; default is 0,0 |
 *  | blend-r | 4  | Blending radius; alpha changing steps are 255 / (2 * radius + 1) near the seam line position. The values vary from 255 to 0 |
 *  | vertical | x  | Perform blending for vertical-direction stitching |
 *  | clear | x  | Clear the dewarp effect on the main buffer |
 *  | warp-file | "file name"  | Save the horizontal and vertical warp vector for debugging |
 *  | verbose | x  | Show the detailed input / output (offset / width / height / grid spacing / grid number information) |
 *  | adjust | 20,2  |  Adjust the offset of specified channels in pixels |
 *  | no-overlap | x  | Specify the no overlap flag, used in the dewarp stage|
 *  | fuse-channel | 1  | Specify fuse channel for dewarp; 1: 1, 2: 2, 3: 1 and 2, 7: 1 and 2 and 3 |
 *  | use-map | x  | Specify use of the map method. 0: no map; 1: pixel-level map; 2: calculate grid spacing automatically; 3: use a specific grid-spacing map. When this option is not specified, the default is to use the pixel-level map method |
 *  | grid-w | 1,2,4,8,16,...,128 | Specify the specific grid spacing width to create a 2D warp table |
 *  | grid-h | 1,2,4,8,16,...,128 | Specify the specific grid spacing height to create a 2D warp table |
 *  | cw-rotate | 0/1 | Rotate channel in the clockwise direction |
 *  | hflip | 0/1 | Flip channel in the horizontal direction |
 *  | vflip | 0/1 | Flip channel in the vertical direction |
 *  | dual-fisheye-ldc | 0,1,2 | 0: stitching without LDC. 1: stitching with calibration. 2: stitching with parameter adjustment |
 *  | update-overlap-content | 0 | Perform dynamic stitching with updating overlap's content. 0: no; 1: sparse; 2: dense; 3: dense acc |
 *  | skip-version-check | 0 |	Skip sensor calibration data version |
 *  | diff-thresh        | 20 |	Specify difference threshold |
 *  | diff-step-ratio    | 2 |	Specify difference step ratio |
 *  | no-calib           | 0 |	Specify to do stitching without calibration |
 *  | max-fov            | 0 |	Specify maximum FoV of lens |
 *  | fish-radius        | 0 | 	Specify fisheye radius |
 *  | in-center          | 0 |	Specify input center |
 *  | shift              | 0 |	Specify output shift |
 *  | extend-output      | 0 | 	Specify equirectangular output |
 *  | skip-version-check  | 0 |	Skip version check operation |
 *  | smooth-width        | 0 |	Specify smooth width for dynamic stitching |
 *  | clear-blend-warp    | 0 | Specify to clear blend warp |
 *  | max-disparity       | 0 |	Specify maximum disparity to filter invalid data |
 *  | stable-frame        | 0 |	Specify stable frames for dyanmic stitching |
 *  | motion-thresh       | 0 |	Specify motion thresh for dyanmic stitching |
 *  | speed-mode          | 0 | Specify dynamic stitcing mode. 0: fastest; 1: fast; 2: slow |
 *  | stop-shift          | 0 | Specify to stop using globle shift |
 *
 * @subsubsection stitch_pro_pre 2.5.2 Run Multi-channel Stitching Cases
 * For multi-channel stitching cases, users must modify the Lua script
 * accordingly. The overlapped areas in the canvas must be configured properly.
 * The following procedure describes the steps required for stitching:
 *
 * Preview -> dewarp (rough tuning) -> offset change (refined tuning) -> blending
 *
 * <b>1. Configure the Lua script </b> <br>
 * There are some options that should be configured for stitching use cases.
 * In the channel configuration, "blend_left_or_top" and "blend_right_or_bot" are configured to show which channel part will perform blending. <br>
 * There are two parts for each channel. <br>
 * For horizontal stitching: left or right <br>
 * For vertical stitching: top or bottom <br>
 * The first channel should be set as blend_left_or_top = 0, blend_right_or_bot = 1.<br>
 * The last channel should be set as blend_left_or_top = 1, blend_right_or_bot = 0.<br>
 * The middle channels should be set as blend_left_or_top = 1, blend_right_or_bot = 1. <br>
 * For CV5x, in the canvas configuration: <br>
 * "blend_copy_num_minus_1" is used to report each channel's blending YUV address. <br>
 * "blend_stitch_type" is used to specify blend stitch mode; the default is 0. 0: none; 1: horizontal; 2: vertical. <br>
 * @code {.c}
 * canvas = {
 * 		{
 * 			type = "encode",
 * 			size = {4416, 1424},
 * 			source = {"chan_0.main", "chan_1.main"},
 * 			extra_dram_buf = 0,
 * 			blend_stitch_type = 1,
 * 			blend_copy_num_minus_1 = 1,
 * 		},
 * 	}
 * @endcode
 *
 * <b>2. Dewarp</b> <br>
 * This step is used to remove lens distortion and reproject the image to the stitching view.
 * As the Amareblla dewarp engine only supports 1D + 1D dewarp maps, the stitching library
 * transfers 2D maps to 1D + 1D maps.
 * @code {.c}
 * Creating grid level 2D maps
 * Board# test_sensor_calib --mode 2 --channel-num 4 -f ./
 *
 * Transfer to 1D + 1D maps and perform dewarp.
 * Board# test_stitch --mode 2 -f . --no-overlap --fuse-channel 15 --vertical (no overlap part)
 * Board# test_stitch --mode 2 -f . --vertical (overlap)
 * @endcode
 *
 * <b>3. Refined tuning</b> <br>
 * This tool offers post adjustment for the horizontal and vertical offsets.
 * @code {.c}
 * "-i" : Channel ID
 * "--adjust x,y" : (is used to adjust the offset of specified channel with the
 * unit of pixel, x > 0: up, x < 0 : down; y > 0: right, y < 0: left)
 * Board # test_sensor_calib --mode 2 --channel-num 4 -f ./ -i 0 --adjust 3,-2
 * Board # test_stitch --mode 2 -f . --no-overlap --fuse-channel 15 --vertical (no overlap part)
 * Board # test_stitch --mode 2 -f . --vertical (overlap)
 * @endcode
 *
 * <b>4. Blending</b> <br>
 * 1) The blend radius can be set using the "r" option; the default is "16". <br>
 * 2) If the user wants to try the on the fly seam line, the algorithm uses motion to control the seam;
 * "motion-r/motion-decide/motion-width/motion-height" options are used to control the motion. <br>
 * 3) There are two types of dynamic seam methods: DP and GC.
 * "seam-global / seam-shake / seam-bounce-w / seam-bounce-h" is used for the DP method in order to control the seam. <br>
 * 4) If on the fly straight line is required rather than a seam line, "top / bottom" options can be used.
 * "top" should be set as "x,0" and "bottom" should be set as "x,height",
 * where x is the horizontal coordinate in the overlap area and the height is the overlap height.
 *
 * @subsubsection stitch_pro_hor 2.5.3 Stitch in Horizontal Direction
 * @image html horizon_stitch.jpg "Figure 2-8. Horizontal Stitching."
 * The command is as shown below:
 * CV2x: <br>
 * @code {.c}
 * board # init.sh --na;modprobe b5_imx290 id=0x7 lane=3
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg ./cvxx_triple_4512x704_hor.lua  --enc-mode 5 --debug-stitch 1 -A --smaxsize 4512x704 --blend-stitch-type 1
 * board # test_stitch --mode 2 -f /root
 * board # test_stitch --mode 3 --overlap 0 --motion-w 70 -f /root
 * @endcode
 *
 * CV5x: <br>
 * @code {.c}
 * board # modprobe ambrg
 * board # modprobe max9296 id=0x0303 vinc_id=0xb8
 * board # modprobe os08a10_mipi_brg fsync=1
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg ./cv5x_4_vin_4_chan_4k_encode_from_main_horizonal_stitch_in_row.lua
 * board # test_stitch --mode 2 -f /root
 * board # test_stitch --mode 3 --overlap 0 --motion-w 70 -f /root
 * @endcode
 *
 * @subsubsection stitch_pro_ver 2.5.4 Stitch in Vertical Direction on CV2x
 * @image html vertical_stitch.jpg "Figure 2-9. Vertical Stitching."
 * This is designed for the CV2x series of chips to perform stitching in the vertical direction. <br>
 * The flow of vertical stitching is shown in the image above; rotate the canvas
 * to improve the view.
 * The command to run the stitch is as shown below:
 * @code {.c}
 * board # init.sh --na && modprobe imx335_mipi vinc_id=0xf1320 slave=1
 * board # test_aaa_service -a&
 * board # test_encode -i 0 --hdmi 480p --resource-cfg cvxx_quad_chan_5280x1856_ver_linear.lua --enc-mode 5 --blend-stitch-type 2
 * board # test_encode -A -H 1856x5280 -b 0 --rotate 1 -e -B -H 1856x5280 -b 1 --rotate 1 -e
 * board # test_sensor_calib --mode 2 --channel-num 4 -f ./
 * board # rtsp_server &
 * board # test_stitch --mode 2 -f . --no-overlap --fuse-channel 15 --vertical (no overlap part)
 * @endcode
 * <b>Linear line alpha blending</b>
 * @code {.c}
 * board # test_stitch --mode 3 --overlap 0 --top 120,0 --bottom 120,1856 -r 100 -B --top 160,0 --bottom 160,1856 -r 100 -C --top 112,1856 --bottom 112,1856 -r 100 --vertical
 * @endcode
 * <b>Seam line alpha blending</b>
 * @code {.c}
 * board # test_stitch --mode 3 --overlap 0  --motion-width 10 --motion-height 10 --vertical
 * @endcode
 *
 * @subsubsection stitch_pro_rotate 2.5.5 Stitch with Rotate Input on CV2x
 * @image html stitching_with_rotate_input_cv2x.jpg "Figure 2-10. Stitching with Rotate Input."
 * This is designed for the CV2x series of chips to perform stitching in the vertical direction. <br>
 * In the example, the start of the frame is in the bottom left.
 * A goal of this feature is to decrease the shutter time lag as much as possible between the two
 * channels around the stitching line.
 * Ambarella recommends installing sensors 1 and 3 with 180-degree rotation, so the stitching
 * line between channel0 and channel1 are exposed
 * at the first row, the stitching line between channel1 and channel2 are exposed at the last row,
 * and the stitching line between channel2 and channel3 are exposed at the first row.
 * The four sensors that run uniform auto exposure (AE) strategies for the same shutter / automatic gain control (AGC) configuration.
 * The shutter time lag and the AGC of the first row (or the last row) from different sensors
 * should be very close to each other, so the luma should also be very close.
 * Configure the specific mirror type of the VSRC in the Lua script to orient images in the same direction.
 *
 * The command to run the stitch is as shown below:
 * @code {.c}
 * (Do pose calibration on Host)
 * host # save_target_info_4x_ver.bat
 * host # specify_distance_4x_ver.bat
 * board # init.sh --na; modprobe ambdd video_type=2 cap_cap_w=2688 cap_cap_h=3040 video_phase=3 video_yuv_mode=3 video_fps=17066667
 * board # test_aaa_service -a&
 * board(cv2x) # test_encode --resource-cfg cvxx_vin2_2688x1520_z116_m.lua --raw-capture 1 --enc-raw-yuv 1
 * --enc-mode 5 --blend-stitch-type 1
 * board # test_efm -t 2 -i out16_m.yuv  -s 2688x3040 -T 1
 * board # test_encode -A -h 5184x1456 -e
 * board # rtsp_server&
 * board # test_sensor_calib --mode 2 --channel-num 2 -f ./
 * board # test_stitch --mode 2 -f /root --raw-encode-chan 2
 * @endcode
 *
 * @subsubsection stitch_channel_rotate 2.5.6 Stitch with Rotated Channels on CV5x
 * This is designed for the CV5 series of chips to perform stitching in the vertical direction. <br>
 * @image html stitching_with_rotate_input_cv5x.jpg "Figure 2-11. Stitching with Rotated Channels." <br>
 * The image shows the design flow for Ambarella's reference demo. <br>
 * @image html stitch_rotate_hardware.jpg "Figure 2-12. Stitching with Rotated Channels demo hardware." <br>
 * The image shows the hardware design for Ambarella's reference board. <br>
 * Customers should configure it according to their hardware. <br>
 * In the stitching stage, the VSRC should be configured with the specific "mirror" type.  <br>
 * The channels should be configured with the options "cw_rotate", "hflip", and "vflip" in the Lua. <br>
 * The example script is located in the path `ambarella\prebuild\library\multi_sensor_calib\dsp_v6\host_calib_tool\script\stitch\cv5x\ipc`. <br>
 * The command to run the stitch is as shown below: <br>
 * @code {.c}
 * board # init.sh --na
 * board # modprobe max9296 id=0x0303 vinc_id=0xb8
 * board # modprobe os08a10_mipi_brg fsync=1
 * board # test_aaa_service -a &
 * (Capture images)
 * board # test_encode --resource-cfg ./cv5x_4_vin_4_chan_1080p_encode_from_main_vertical_rotate.lua (1080p)
 * board # test_encode --resource-cfg ./cv5x_4_4k_capture.lua (4k)
 * board # test_encode -A -H 1080p -e -B -H 1080p -b 1 -e
 * (Do pose calibration on Host)
 * host # save_target_info_4x_ver_rotate.bat
 * host # specify_distance_4x_ver_rotate.bat ("cw_rotate" "hflip" "vflip" should be set as 1 in the ini file)
 * (Do stitching)
 * board # test_encode --resource-cfg ./cv5x_4_vin_4_chan_1080p_encode_from_main_horizonal_stitch_rotate_hvf.lua (1080p)
 * board # test_encode --resource-cfg ./cv5x_4_4k_stitch_hvf.lua (4k)
 * board # test_encode -A -H 1080p -e
 * board # test_sensor_calib --mode 2 --channel-num 4 -f ./
 * board # test_stitch --mode 2 -f /root -i 0 --rotate-cw --hflip --vflip -i 1 --rotate-cw --hflip --vflip -i 2 --rotate-cw --hflip --vflip -i 3 --rotate-cw --hflip --vflip --vertical
 * board # test_stitch --mode 3 --overlap 0 --top 30,0 --bottom 30,2880 --overlap 1 --top 30,0 --bottom 30,2880 --overlap 2 --top 30,0 --bottom 30,2880
 * board # rtsp_server
 * @endcode
 *
 * @subsubsection stitch_eight_channels_stitching 2.5.7 Stitch with Six / Eight Channels on CV5x
 * This is designed for CV5 series of chips to perform stitching with six / eight channels. <br>
 * @image html 8channel_stitching.jpg "Figure 2-13. Stitching with Eight Channels." <br>
 * Eight-channel stitching is used as an example. <br>
 * The image shows the canvas layout for Ambarella's reference board, including the calibration stage layout and stitching stage layout. <br>
 * Because there is a limitation of the coder / decoder (codec) stream width, the stitched buffers should be placed in two layers. <br>
 * After performing pose calibration, the message shown below appears: <br>
 * @code {.c}
 * (Do pose calibration on Host)
 * host # save_target_info_8x_hor.bat
 * host # specify_distance_8x_hor.bat
 *
 * Channel [0] Configuration :
 * Buffer : output size [2176x960], zoom [1.378815, 1.378815]
 * Canvas : Input : offset [0x0], size [2176x960], Output : offset [0x0], size [2176x960]
 * Channel [1] Configuration :
 * Buffer : output size [2176x960], zoom [1.378815, 1.378815]
 * Canvas : Input : offset [0x0], size [2176x960], Output : offset [1280x0], size [2176x960]
 * Channel [2] Configuration :
 * Buffer : output size [2112x960], zoom [1.378815, 1.378815]
 * Canvas : Input : offset [0x0], size [2112x960], Output : offset [2560x0], size [2112x960]
 * Channel [3] Configuration :
 * Buffer : output size [2176x960], zoom [1.378815, 1.378815]
 * Canvas : Input : offset [0x0], size [2176x960], Output : offset [3904x0], size [2176x960]
 * Channel [4] Configuration :
 * Buffer : output size [2176x960], zoom [1.378815, 1.378815]
 * Canvas : Input : offset [0x0], size [2176x960], Output : offset [5120x0], size [2176x960]
 * Channel [5] Configuration :
 * Buffer : output size [2304x960], zoom [1.378815, 1.378815]
 * Canvas : Input : offset [0x0], size [2304x960], Output : offset [6336x0], size [2304x960]
 * Channel [6] Configuration :
 * Buffer : output size [2112x960], zoom [1.378815, 1.378815]
 * Canvas : Input : offset [0x0], size [2112x960], Output : offset [7680x0], size [2112x960]
 * Channel [7] Configuration :
 * Buffer : output size [2112x960], zoom [1.378815, 1.378815]
 * Canvas : Input : offset [0x0], size [2112x960], Output : offset [8896x0], size [2048x960]
 * @endcode
 *
 * When configuring the Lua, users must note the width change of channel3,
 * Channel 3 width = channel_3_out_w - ((channel_3_out_x + channel_3_out_w) - (channel_7_out_x + channel_7_out_w - channel_4_out_x))
 * Channel 3 width = 2176 - ((3904 + 2176) - (8896 + 2048) - 5120).
 * @code {.c}
 * chan_3 = {
 *		blend_left_or_top = 1,
 * 		blend_right_or_bot = 0,
 * 		main = {
 * 			max_output = {2176, 960}, -- output width
 * 			input      = {0, 0, 0, 0}, -- full main
 * 			output     = {3904, 0, 1920, 960},
 * 		},
 * }
 *
 * chan_4 = {
 * 		blend_left_or_top = 0,
 * 		blend_right_or_bot = 1,
 * 		main = {
 * 			max_output = {2176, 960}, -- output width
 * 			input      = {0, 0, 0, 0}, -- full main
 * 			output     = {0, 960, 2176, 960},
 * 		},
 * }
 * @endcode
 * The example script is located in the path `ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/script/stitch`. <br>
 * The command to run the stitch is as shown below: <br>
 * @code {.c}
 * (Do stitching)
 * board # init.sh --na;modprobe max9296 id=0x03030303 vinc_id=0x40b8
 * board # modprobe os08a10_mipi_brg fsync=1
 * board # test_aaa_service -a &
 * board(cv5x) # test_encode --resource-cfg ./cv5x_8_vin_8_chan_1080p_encode_from_main_horizonal_stitch.lua
 * board # test_encode -A -H 5824x1920 -e
 * board # test_sensor_calib --mode 2 --channel-num 8 -f ./
 * board # test_stitch --mode 2 -f .
 * board # test_stitch --mode 3 --overlap-id 0 --top 100,0 --bot 100,960 --overlap-id 1 --top 100,0 --bot 100,960
		--overlap 2 --top 100,0 --bot 100,960 --overlap 3 --top 100,0  --bot 100,960 --overlap-id 4 --top 100,0 --bot 100,960
		--overlap-id 5 --top 10,0 --bot 10,960 --overlap-id 6 --top 100,960 --bot 100,960
 * board # rtsp_server
 * @endcode
 *
 * @subsubsection stitch_pro_dptz 2.5.8 Stitch Digital Pan / Tilt / Zoom on CV2x
 * @image html stitch_dptz.jpg "Figure 2-14. Stitching DPTZ."
 * This is designed for the CV2x series chips. <br>
 * If the digital pan / tilt / zoom (DPTZ) is applied in one channel, users are required to only configure one channel.
 * If the DPTZ is applied across more than one channel, users must configuration those channels accordingly.
 * The features have been implemented in the test_multi_chan application.
 * Another example of DPTZ within the stitched panorama view is shown in the image above.
 * The bottom part is scaled from the stitched panorama view, and the top part is cropped and
 * scaled from the stitched panorama view.
 * The top part enables users to change the crop offset dynamically or on the fly.
 * The command is as shown below:
 * @code {.c}
 * board # init.sh --na;modprobe b5_imx290 id=0x7 lane=3
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg ./triple_chan_blend_4512x704_dptz.lua  --enc-mode 5 --debug-stitch 1 -A --smaxsize 4512x704 --blend-stitch-type 1
 * board # test_encode -A -h 4512x704 -b 1 -e
 * board # rtsp_server&
 * board # test_sensor_calib --mode 2 --channel-num 3 -f ./
 * board # test_stitch --mode 2 -f /root
 * board # test_stitch --mode 3 --overlap 0 --motion-w 70 -f /root
 * board # test_multi_chan -L --cinoff 0x0 --cinsize 1920x700 --coutoffset 0x1328 --coutsize 1920x700
 * board # test_stitch --mode 3 --overlap 0 --motion-w 10 --dptz-auto
 * @endcode
 *
 * @subsubsection stitch_skip_blend 2.5.9 Stitch Skip Source Buffer Blend
 * This is a flag to skip sub source buffer blend passes in stitching. The main buffer
 * always has a blend pass; it cannot be skipped. It is only available when stitching is enabled.
 * "srcbuf_to_skip_blend" is the configuration option in the Lua script.
 * For example, the second source buffer is to set bit[1], the third source buffer is to set bit[2], and so on.
 *
 * @subsubsection stitch_insert_pm 2.5.10 Stitch Privacy Mask
 * The privacy mask (PM) is inserted in the VIN / main buffer domain. <br>
 * It can be added when LDC (lens-warp) is enabled. <br>
 * The application calculates the coordinates in the VIN domain according to the warp table. <br>
 * Users should refer to the Privacy Mask utility library (API: pm_fill_rect) to insert rectangular PMs:
 * @image html rect_pm_w_jaggy.jpg "Figure 2-15. Rectangle PM with Jaggy."
 * The image shows the rectangle performs normally in the LDC channel.
 * @image html stitch_pm.jpg "Figure 2-16. PM Layout."
 * If the PM is inserted in one channel, users are required to configure only one channel.
 * If the PM is inserted across multiple channels, users configure those channels accordingly.
 *
 * @subsubsection stitch_insert_blur 2.5.11 Stitch Blur on CV5x / CV72
 * Blur is inserted in the canvas domain. It is allowed to insert one blur region across channel
 * boundary onto the overlapped area. <br>
 * With the assumption that the left (or top) image and the right (or bottom) image have similar
 * content in the overlapped area, DSP only takes one side's content as source image to calculate
 * blur effect for the overlapped region. <br>
 * If the content in the overlapped region differs a lot, the blur result will mismatch with one
 * side's content.
 *
 * @image html stitch_blur_mismatch.jpg "Figure 2-17. Blur mismatch when overlap content differs."
 *
 * @subsubsection stitch_pro_dual 2.5.12 Stitch Dual Fisheyes for 360-Degree Panorama
 * @image html dual_fisheye_panorama.jpg "Figure 2-18. Stitching 360-Degree Panorama."
 * The flow of dual fisheye for 360-degree panorama stitching is shown in the image above.
 * The output is a 360 x 180 degree panorama stitched view.
 *
 * (1) Create panorama view with calibration. <br>
 * Lens calibration <br>
 * Ambarella suggests using the MEI fisheye calibration model to perform lens calibration.
 * The command to run the lens calibration is as shown below:
 * @code {.c}
 * host # run_calib_chess_mei_yuv.bat
 * @endcode
 *
 * Pose calibration <br>
 * The following is an example to perform pose calibration for 2x 360-degree back-to-back fisheye stitching. <br>
 * Refer to @ref guide_sensor_calib_dual_fish "10. Dual-Fisheye Back-to-Back Pose Calibration" to learn the pose calibration process.
 *
 * LDC / Dewarp <br>
 * 1) Perform blending <br>
 * @image html fisheye_ldc.jpg "Figure 2-19. Fisheye LDC."
 * Blending is only supported for mode 5, and between adjacent channels, users must use virtual channels for VINC0 to perform LDC. <br>
 * @code {.c}
 * board # init.sh --na
 * board # modprobe ambdd video_type=2 video_yuv_mode=3 video_fps=17066667 cap_cap_w=1600 cap_cap_h=2592
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg cv2x_360_stitch_1600_1200_warp_3_chan_ldc_fisheye.lua --enc-raw-yuv 1 --blend-stitch-type 1 --enc-mode 5
 * board # test_sensor_calib --mode 2 --channel-num 2 -f ./
 * board # test_stitch --mode 2 -f ./ --dual-fisheye-ldc 1
 * @endcode
 *
 * 2) No blending <br>
 * Mode 1 (dewarp) is used for this feature. There is no overlap region (blending) for two cameras at this stage. <br>
 * The command to run stitching is as shown below : <br>
 * @code {.c}
 * board # init.sh --na
 * board # modprobe b5_imx274 bus_addr=0x20000
 * board # test_aaa_service -a&
 * board # test_encode --resource cv2x_360_stitch_1920_1080_warp_b5_imx274.lua --enc-mode 1
 * board # test_stitch --mode 2 -f /root --no-overlap
 * @endcode
 *
 * (2) Create panorama view without calibration (CV5x). <br>
 * Equirectangular projection is a representation of the sphere that maps longitude directly to the horizontal coordinate, and latitude to the vertical coordinate.  <br>
 * It is commonly used as the projection type of the source images for spherical panorama viewers. <br>
 * The users can adjust the equirectangular projection paramters on the fly to stitch the images. <br>
 * The overlap area is specified by the user and they can do parameters adjustment to stitch the images.
 * @code {.c}
 * board # init.sh --na; modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=2 custom_format_enable=1
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg cv5x_dual_channel_encode_from_main_horizonal_stitch_without_calib.lua  --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua --raw-capture 1 --enc-raw-nv12 1
 * board # test_efm -t 4 -i right.yuv  -s 1600x1296 -T 1 --vin-id 15 (right.yuv format is nv12)
 * board # test_efm -t 4 -i left.yuv  -s 1600x1296 -T 1 --vin-id 14 (left.yuv format is nv12)
 * board # test_encode -A -H 2944x1296 -e
 * board # test_stitch --mode 2 --no-overlap --no-calib --dual-fisheye-ldc 2 --max-fov 200 --fish-radius 600 -i 0 --in-center 800,648
 * --extend-output 1536,1296  --shift 768,0 -i 1 --in-center 800,648 --extend-output 1536,1296  --shift 0,0  --fuse 7 -i 2 --in-center 800,648
 * --extend-output 1536,1296 --shift 0,0
 * board # test_stitch --mode 3 --overlap-id 0 --motion-width 10
 * @endcode
 *
 * Options description : <br>
 * max-fov : FoV for lantitude-longitude frame.
 * fish-radius : radius of fisheye, fixed by the parameter adjustment effect.
 * in-center : coordinate in the input image, adjust the coordinates to shift the image. <br>
 * extend-output : resolution for latitude and longitude extend. <br>
 * fuse: dewarp channel id. 7 is for 3 channels. <br>
 * shift: shift the output image. <br>
 *
 * @subsubsection stitch_backwarp_map 2.5.13 Stitch-Backward / Forward Mapping
 * Stitch-backward mapping is used to map after LDC points to the VIN input domain.
 * Stitch-forward mapping is used to map the points from the VIN input domain to the LDC domain.
 * The command is as shown below:
 * CV2x： <br>
 * @code {.c}
 * board # init.sh --na; modprobe b5_imx290 id=0x7 lane=3
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg cvxx_triple_4512x704_hor.lua --enc-mode 5 --debug-stitch 1 --blend-stitch-type 1
 * @endcode
 * Run mapping : <br>
 * @code {.c}
 * board # test_stitch --mode 2 -f /root
 * Stitch Backward Mapping:
 * board # test_stitch --mode 0 -i 0 --map-point 441,210 -f /root -w 2560 -h 1440
 *
 * Stitch Forward Mapping:
 * board # test_stitch --mode 4 -i 0 --map-point 441,210 -f /root -w 2560 -h 1440
 *
 * (441, 210 is the point of specific channel, w / h is used to specify the VIN resolution.
 * If the option "fuse_method" is set to 2 in the pose calibration, changing width / height
 * will not influence the result, becuase width / height will not be used in the formula.
 * If the option "fuse_method" is set to 0 in the pose calibration, changing width / height
 * will influence the result, becuase width / height will be used in the formula.)
 * @endcode
 *
 * @subsubsection stitch_simulation_efm 2.5.14 Stitch Simulation with EFM
 * If LDC functions are applied to perform simulations,
 * customers must run encode from RAW (EFR) processes.
 * However, EFR only functions for single-VIN cases and takes RAW format.
 * Customers must combine two RAW frames of data vertically into a single frame (n x 1080p -> 1920 x (n x 1080).
 * @code {.c}
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 * 					(0x8200000)-> IAV Usr Buffer Size
 * @endcode
 * The command is as shown below:
 * @code {.c}
 * 1. Prepare RAW data, and merge the data in the vertical direction. The input name of each RAW should be in the format chan_x.raw.
 * board # test_stitch --merge-num 2 --mode 1 -i 0 -w 2688 -h 1520 -i 1 -w 2688 -h 1520 --raw
 * 2. Configure the Lua; each channel's input offset should be changed accordingly.
 * vsrc_0 = {
 * 	vsrc_id = 0,
 * 	mode = "0",
 * 	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
 * 	fps = 30,
 * 	bits= 0,
 * }
 *
 * ....
 * chan_0 = {
 *	id = 0,
 *	vsrc = vsrc_0,
 *	main = {
 *		max_output = {0, 0}, -- output width
 *		input      = {0, 0, 2048, 1536},
 *		output     = {0, 0, 2048, 1536},
 *	},
 * }
 *
 * ....
 * chan_1 = {
 *	id = 1,
 *	vsrc = vsrc_0,
 *	main = {
 *		max_output = {0, 0}, -- output width
 *		input      = {0, 1536, 2048, 1536},
 *		output     = {0, 0, 1920, 1536},
 *	},
 * }
 * .....
 *
 * 3. Perform RAW encode + stitching
 * board # init.sh --na
 * board # modprobe ambdd video_type=2 video_yuv_mode=3 video_fps=17066667 cap_cap_w=2048  cap_cap_h=3072
 * board # test_aaa_service -a &
 * board(cv2x) # test_encode --resource-cfg cvxx.lua  --hdmi 720p --raw-capture 1 --enc-raw-rgb 1
 * board # test_mempart -m 2 -s 0x8200000
 * board # test_efm -t 3 -i out.raw  -s 2048x3072 -T 1
 * board # test_sensor_calib --mode 2 --channel-num 2 -f ./
 * board # test_stitch --mode 2 -f .
 * @endcode
 *
 * @subsubsection stitch_user_warp_alpha 2.5.15 Stitch with Users' Warp Table and Alpha Table
 *
 * 1. If users want to use their own algorithms to perform calibrations and then apply them to the DSP, <br>
 * they must transform the OpenCV 2D warp table to a "1D + 1D" warp table. <br>
 * For 2D warp table details, refer to the Doxygen document (Dewarp Library API, 2.11 Transform 2D Vector to 1D+1D). <br>
 * @code {.c}
 * board# test_ldc -c 0 -F 180 -R 910 -m 8 --twin-vec ./2D_vector.bin
 * @endcode
 *
 * 2. If customers want to create their own alpha table and apply blending data, <br>
 * `test_stitch.c` is the reference application for this purpose. <br>
 * 1) The function `do_vproc_ioctl()` is used to configure and perform blending. <br>
 * IAV_IOC_CFG_VIDEO_PROC is used to configure blend; the overlap information should be configured there. <br>
 * IAV_IOC_APPLY_VIDEO_PROC is used to apply blend. <br>
 * 2) The formula is final_YUV = (chan_0 * alpha + chan_1 * (255 - alpha)) / 255. <br>
 * 3) The alpha table format is shown as below: <br>
 * Channel 0, data is from 255 - 0 <br>
 * @image html channel_0_alpha_table.jpg "Figure 2-20. Channel 0 Alpha Table Format."
 * Channel 1, data is from 0 - 255 <br>
 * @image html channel_1_alpha_table.jpg "Figure 2-21. Channel 1 Alpha Table Format."
 *
 *
 * @subsubsection stitch_update_warp_table 2.5.16 Stitch with Updating Warp Table on the Fly
 * For video conference use cases, the distance between the users and the camera is very close and a large parallax issue will occur.
 * This feature is designed to change the right channel's warp table and improve image alignment in the object's location.
 * @code {.c}
 * board# init.sh --na
 * board# modprobe max9296 id=0x0303 vinc_id=0xb8
 * board# modprobe os08a10_mipi_brg fsync=1
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg cvx_4k_stitch_4k_4hor_channel.lua
 * board# test_stitch --mode 2 -f /root
 * board# test_stitch --mode 3 --overlap-id 0 -r 4 --top 160,0 --bot 160,1024  --update-overlap-content 2
 * -f /root --overlap-id 1 -r 4 --top 160,0 --bot 160,1024 --overlap-id 2 -r 4 --top 160,0 --bot 160,1024
 * --smooth-width 64 --skip-frame 2 --diff-thresh 2 --max-disparity 100 --stable-frame 2 --speed-mode 1
 * @endcode
 *
 * @subsubsection stitch_simulate_with_pose_results 2.5.17 Stitch Simulation with Pose Calibration Results
 * The function `simulation_canvas_image_xx_xx.bat` demonstrates how to obtain the PC simulation results <br>
 * when users want to check the pose calibration results on the PC side, as well as the calibration quality.
 * @code {.c}
 * host# save_target_info_2x_hor.bat
 * host# specify_distance_2x_hor.bat
 * host# simulation_canvas_image_2x_hor.bat
 * @endcode
 * The simulation results are stored in the path `example\2_hor\back_end`.
 *
 * @subsubsection stitch_pro_tilt 2.5.18 Stitch in Horizontal Direction with Angles below the Horizon
 * @image html stitch_tilt.jpg "Figure 2-22. Sensor Mounting with Angles below the Horizon." <br>
 * The design of sensor mounting with angles below the horizon is shown in the image above. <br>
 * The four pinhole sensors should be placed with the same tilt angle. 25 degree is a commonly used value. <br>
 * Equirectangular projection across the horizon is used for this kind of product. <br>
 *
 * Steps to perform stitching are as follows: <br>
 * 1. Lens calibration <br>
 * Ambarella suggests using the pinhole calibration model to perform the lens calibration.
 * The command to run the lens calibration is shown below:
 * @code {.c}
 * host # run_calib_chess_yuv.bat
 * @endcode
 *
 * 2. Pose calibration <br>
 * The following is an example to perform pose calibration for 3x stitching with angles below the horizon. <br>
 * Ambarella suggests performing pose calibration with a chessboard. The option "no_dist_flag" should be set to 1, <br>
 * and "tilt_angle" should be set accordingly in the `.ini` configuration file. <br>
 * @code {.c}
 * host # save_target_info_3x_hor_chess_tilt.bat
 * host # specify_distance_3x_hor_chess_tilt.bat
 * @endcode
 *
 * 3. LDC and blending <br>
 * @code {.c}
 * board # init.sh --na
 * board # modprobe ambrg
 * board # modprobe max9296 id=0x0303 vinc_id=0xb8
 * board # modprobe os08a10_mipi_brg fsync=1
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg cv5x_3_vin_3_chan_4k_encode_from_main_horizonal_stitch.lua --enc-mode 5
 * board # test_sensor_calib --mode 2 --channel-num 3 -f ./
 * board # test_stitch --mode 2 -f ./
 * board # test_stitch --mode 3 --overlap-id 0 --motion-w 21
 * @endcode
 *
 * @subsubsection stitch_pro_tilt_vhvh 2.5.19 Stitch in Vertical-Horizontal-Vertical-Horizontal Direction with Angles below the Horizon
 * The vertical-horizontal-vertical-horizontal direction stitching is designed to combine 4 vertical-horizontal-vertical-horizontal direction channels into a 360-degree panorama view. <br>
 * @image html vhvh_tilt_stitching_input_output.jpg "Figure 2-23. Input / Output in Vertical-Horizontal-Vertical-Horizontal Direction with Angles below the Horizon." <br>
 * The input and output of vertical-horizontal-vertical-horizontal stitching is shown in the image above. <br>
 * @image html vhvh_tilt_stitching_design.jpg "Figure 2-24. Sensor Mounting in Vertical-Horizontal-Vertical-Horizontal Direction with Angles below the Horizon." <br>
 * The lens layout design of sensor mounting in vertical-horizontal-vertical-horizontal direction with angles below the horizon is shown in the image above. <br>
 * For the 4 channels’ sensor inputs, the ISP process order will be channel0->channel2->channel1->channel3. <br>
 * This is to ensure that the invalid area can be covered properly with the channels in higher Z-order. <br>
 * Step 1: for channel0, dewarp and rotate the output directly to main buffer canvas. <br>
 * Step 2: for channel2, dewarp and crop the output first (crop window is as below example), then rotate the output to main buffer canvas. <br>
 * Step 3: for channel1, dewarp and crop the output (crop window is as below example) to main buffer canvas. <br>
 * Step 4: for channel3, dewarp and crop the output (crop window is as below example) to main buffer canvas. <br>
 *
 * Steps to perform stitching are as follows: <br>
 * 1. Pose calibration <br>
 * @image html vhvh_tilt_stitching_config_ini.jpg "Figure 2-25. Vertical-Horizontal-Vertical-Horizontal Stitching Pose Calibration File Configurations." <br>
 * The following is an example to perform pose calibration for vertical-horizontal-vertical-horizontal stitching with angles below the horizon. <br>
 * The options `output_width/output_height/intrinsic/distortion/extrinsic/offset/resolution/top_fov/bot_fov` should be set accordingly in the `.ini` configuration file. <br>
 * The options descriptions are listed below : <br>
 * "output_width / output_height" is the width and height of the panorama view . <br>
 * "intrinsic" should be filled with lens calibration intrinsic parameters. <br>
 * "distortion" should be filled with lens calibration distortion parameters. <br>
 * "extrinsic" should be filled with pose calibration extrinsic parameters. <br>
 * "offset" should be filled with offset of the specific channel in the canvas (panaroma view). <br>
 * "resolution" should be filled with width / height of the specific channel in the canvas (panaroma view). <br>
 * "top_fov" is the FoV at the top of the panorama view. <br>
 * "bot_fov" is the FoV at the bottom of the panorama view. <br>
 * The methods to calculate some options are listed below : <br>
 * It is assumed "input_width" is 2304, "hfov" is 115, "top_fov" is 15, "bottom_fov" is -85.
 * @code {.c}
 * output_width = 360 * (input_width / hfov)
 * output_height = (top_fov - bottom_fov) * (input_width / hfov))
 * host # save_target_rotation_4m_85.bat
 * host # create_map.bat
 * @endcode
 *
 * 2. Multiple fisheye dewarp <br>
 * @code {.c}
 * board # init.sh --na; modprobe ambds vin_virtual_flag=1 virtual_vsrc_num=8 custom_format_enable=1 yuv_mode=1
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg motorola_stitching_efr_warp_al_new_bot_852_7212.lua   --enc-raw-nv12 1 --raw-capture 1 --chan-vcap-mode-enable 1
 * board # sleep 0.5
 * board # test_efm -t 4 -s 2592x1944 -i ./office-sensorImg0.yuv  -T 1 --vin-id 14 & test_efm -t 4 -s 2592x1944
 * -i ./office-sensorImg1.yuv  -T 1 --vin-id 15 & test_efm -t 4 -s 2592x1944 -i ./office-sensorImg2.yuv
 * -T 1 --vin-id 16 & test_efm -t 4 -s 2592x1944 -i ./office-sensorImg3.yuv  -T 1 --vin-id 17&
 * board # test_encode -A -h 7168x1888 -b 4 -e
 * board # rtsp_server &
 * board # test_stitch --mode 2 -f /tmp/ --no-overlap --fuse 32 --skip-version --extra-height 16
 * board # test_stitch --mode 2 -f /tmp/ --no-overlap --fuse 64 --skip-version   --extra-height 16
 * board # test_stitch --mode 2 -f /tmp/ --no-overlap --fuse 16 -i4 -a 0 --rotate -H -V -a 1 -H -V
 * -a 2 --expand-len 192 -a 3 --rotate -H -V --skip-version --extra-height 16
 * board # test_stitch --mode 2 -f /tmp/ --no-overlap --fuse 128 -i7 -a 0 --rotate -H -V -a 1 --rotate -H -V --skip-version --extra-height 16
 * @endcode
 *
 * - - - -
 *
 * @section sec_stitch_api 3. Stitch Application Programming Interface
 * Visit the following link for details of the application programming interface (API) functions.
 *      - @ref lib-stitch-helper shows related macros and enumerations
 *      - @ref lib-stitch-api shows related APIs
 *
 * - - - -
 *
 * @section sec_stitch_faq 4. Stitch FAQ
 * @subsection sec_stitch_faq_q1 Question 1: How can green artifacts in the overlap area be avoided?
 * @b Answer: To ensure image quality in the overlap area, users must configure the Lua: <br>
 * enable_group = 1 <br>
 * If this issue still occurs, check the dmesg: <br>
 * dmesg -w | grep “raw data dropped” <br>
 * @image html green_artifact.jpg "Figure 4-1. Green Artifact."
 *
 * @subsection sec_stitch_faq_q2 Question 2: When there are visible straight lines in sub-buffer stitching, but normal in main-buffer stitching, how can the lines be mitigated?
 * @b Answer: To ensure image quality in the overlap area for sub-buffers, users must ensure that the
 * zoom factor (width and height) is be the same for each buffer.
 * It is necessary to use round_up to calculate the offset.
 * @image html visible_straight_line.jpg "Figure 4-2. Visible Straight Line for Sub Buffers Stitching."
 * @code {.c}
 * Chan0
 * main buffer
 *	input	= {0, 0, 2592, 1944},
 *	output	= {0, 0, 2624, 1632}
 * sixth buffer
 *	input	= {0, 0, 2624, 1632},
 *	output	= {0, 0, 672, 416},
 *
 * Chan1
 * main buffer
 *	input	= {0, 0, 2592, 1944},
 *	output	= {2432, 0, 2432, 1632},
 * sixth buffer
 *	input	= {0, 0, 2376, 1632},
 *	output	= {624, 0, 608, 416},
 *
 * it is assumed ratio_x = 672 / 2624, ratio_y = 416 / 1632
 * offset_x 624 = round_up(2432 * ratio_x, 4)
 * input_width 2376 = round_up(608 / ratio_x, 4)
 * @endcode
 *
 * @subsection sec_stitch_faq_q3 Question 3: How can artifacts in the horizontal and vertical directions after applying LDC be avoided?
 * @b Answer: Users may encounter the banding problem as seen in @image html padding_artifact.jpg "Figure 4-3. Padding-width Artifact."
 * To ensure image quality, users must increase the value of the option "max_padding_width" in the Lua: <br>
 * Users may encounter the artifact on the top lines of the channel as seen in @image html max_vwarp_wait_lines.jpg "Figure 4-4. Vwarp Lines Artifact."
 * To ensure image quality, users must increase the value of the option "max_vwarp_wait_lines" in the Lua. There is no such problem in mode 5.
 *
 * @subsection sec_stitch_faq_q4 Question 4: How is the warp table size reduced?
 * @b Answer: The pose calibration configuration files are stored in the folder "back_end" and stored as "cali_warp_x". Users must create the 2D warp table using <br>
 * the application test_sensor_calib first. The full resolution 2D table will be downsampled with specific grid spacing in the horizontal and vertical directions. <br>
 * and stored as "undistort_x". Then users must create the 1D + 1D warp table by application "test_stitch". <br>
 * Users can increase values of the options “grid-w” and “grid-h” to reduce the size of "undistort_x".
 *
 * @subsection sec_stitch_faq_q5 Question 5: How to capture images to avoid pose calibration fail?
 * @b Answer: @image html pose_error.jpg "Figure 5-1. Detection Error."
 * Users may encounter the image detection failure problem in the pose calibration.
 * The april tag ID is different for each tag. For pose calibration, the "share_id" in the .ini file is used to find the corresponding circle points of the specific channel image. <br>
 * To successfully detect the same ID tag and points, Ambarella suggests leaving at least three columns near the specified share ID inside the image, as shown in the green box. <br>
 * The first column should not exceed the image boundary.
 *
 * @subsection sec_stitch_faq_q6 Question 6: How is the shared ID chosen?
 * When running the bat of the calibration script, users can see the log below from the terminal. <br>
 * Users can then choose the ID that is common to the shared ID, and fill it in in the `.ini` file.
 * @code {.c}
 * read image 0
 * Left tag id 11, sid 1
 * Left tag id 11, sid 0
 * vector 27.553820, 34.688438
 * read image 1
 * Left tag id 11, sid 2
 * Left tag id 11, sid 3
 * Left tag id 11, sid 0
 * Left tag id 11, sid 1
 * @endcode
 * share id is 0 / 1.
 *
 * @subsection sec_stitch_faq_q7 Question 7: How is calibration data made compatible with the new SDK version?
 * (1) Use "skip-version-check" in test_stitch to ignore the calibration file version difference, dynamic stitching is not supported for this method. <br>
 * @code {.c}
 * board # test_stitch --mode 2 -f ./ --skip-version-check
 * @endcode
 *
 * (2) Redo calibration to create the new configuration file with old keypoints. <br>
 * When cameras have performed pose calibration in the old SDK version, and users want to upgrade to the latest-version calibration tool in the SDK, <br>
 * they are required to set the option "no_yuv" to 1 in the configuration file `sensor_calib_ini_pose_calibration_save_target_xx_xx.ini`, <br>
 * then run `save_target_info_xx_xx.bat` and `specify_distance_xx_xx.bat` again to create new configurations.
 *
 * - - - -
 *
 * @section sec_stitch_lic 5. License
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
 */
/*!
 * @example test_stitch.c
 * This is a source code file of test_stitch.
 *
 */
 /*!
 * @defgroup stitch-api STITCH Library API
 * @brief stitch Library API, in file lib_stitch.h
 */

/*! @defgroup lib-stitch-api STITCH Library API Detail
 *  @ingroup stitch-api
 *  @brief stitch detail, in file lib_stitch.h
 */

/*! @defgroup lib-stitch-helper STITCH Library API Helper
 *  @ingroup stitch-api
 *  @brief stitch Helper, in file lib_stitch.h
 */
/*!
 * @file doc_lib_vproc.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2020-06-30
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
 * @page page_lib_vproc_doc VPROC Library API
 *
 * @section vproc_history 0. Revision History
 *  | Library Version |Updated Date     | Modification                 |
 *  | :---               | :--------------------------- |:----------------|
 *  | 0.0.1 |20200630         | Initial Version                |
 *  | 0.1.4 |20210125         | Support 1)alpha blending; 2)rgb2yuv; 3)transpose; 4)abs calculation; 5)cclb; 6)bayer2bgr |
 *  | 0.1.5 |20210422         | Support flatten |
 *  | 0.1.6 |20210616         | Support bitwise logical operation |
 *  | 0.1.8 |20210718         | Support dsi fusion scale0 with shifted |
 *  | 0.1.9 |20210928         | Upgrade vproc.bin with cavalry_gen version 2.2.8.3 |
 *  | 0.1.9 |20220221         | 1. Add VProc performance information of CV22<br>2. Split APIs into two groups that use physical address and use memory file descriptor |
 *  | 0.1.9 |20220823         | 1. Support vproc FBM, @ref vproc_library_test_vproc_fbm. <br> 2. Support Point Cloud Rendering,@ref vproc_library_test_vproc_render3d.   |
 *  | 0.1.9 |20221101         | Update the descriptions about FBM and dfilter   |
 *  | 0.2.0 |20221216         | Add log level support |
 *  | 0.2.0 |20230214         | Add rotate with mvproc.bin for CV28 and CV25 |
 *  | 0.2.0 |20230224         | Support dsfilter, update the descriptions about FBM   |
 *  | 0.2.0 |20230308         | Support pre-process of FBM, add the descriptions about FBM process pipeline  |
 *  | 0.2.0 |20230315         | Refine VProc page   |
 *  | 3.0.0 |20230615         | Enable Harris for CV72   |
 *  | 3.0.0 |20230625         | Enable Render3d for CV72   |
 *  | 3.0.0 |20230710         | Support CV72, using cavalry_gen version 3.0.2   |
 *  | 3.0.0 |20230724         | Expand the maximal input resolution of cvfilter from 1080p to 4096x4096 for CV2x / CV72  |
 *  | 3.0.0 |20230725         | Add performance improvement guidance for CV72 resize   |
 *  | 3.0.0 |20230831         | Enable FBM and related pre-process and post-process filters for CV72  |
 *  | 3.0.0 |20230926         | Update FBM performance for CV72  |
 *
 * - - - -
 *
 * @section vproc_introduction 1. Introduction
 * VProc stands for CVflow™ vector processor (VP), which manages operations and mathmatical calculations whose performance can
 * be boosted utilizing Ambarella CVflow chips. Here, the majority of the heavy calculations are carried out on the CVflow vector processor.
 *
 * The VProc library is based on the Cavalry driver. Users should first enable the Cavalry
 * driver, and then enable the VProc library.
 * Follow the commands below to build the library:
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Package Configuration  --->
 *              [*]   Build Ambarella vp process library
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *          packages  --->
 *              [*] libvproc (packages/vproc)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *          meta-ambalib  --->
 *              recipes-cavalry  --->
 *                 [*] libvproc (meta-ambalib/recipes-cavalry/libvproc)
 * @endcode
 *
 * To verify pre-defined algorithms in the VProc library, such as the algorithm cvfilter,
 * follow the commands below to build the unit tests:
 *
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Unit Test Configuration  --->
 *              [*]   Ambarella Private Linux Unit test configs  --->
 *                 [*]   Build CV unit tests  --->
 *                    [*]   Build vproc algorithm unit test
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *          unit_test  --->
 *              private  --->
 *                  [*] cv-test (unit_test/private/cv_test/cavalry_v2)  --->
 *                      [*]   Build VP Profile unit tests
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *          meta-ambaapp  --->
 *              recipes-test  --->
 *                  [*] cv-test (meta-ambaapp/recipes-test/cv-test)  --->
 *                      [*]   Build vproc algorithm unit tests
 * @endcode
 * - - - -
 *
 * @section vproc_library_example_usage 2. Example Usage
 *
 * @subsection vproc_library_test_vproc 2.1 VProc Unit Test Application
 * Dozens of unit test applications are provided for VProc library
 * verificaiton. DMABuf is supported for each feature, with a postfix "mfd"
 * in its corresponding unit test. Users can reference them as the sample code when
 * writing applications. Enable the Cavalry driver before running a
 * VProc unit test with the command below.
 *
 * @note
 *   The following live demos may not function on CV5x. Refer to the CV5x Feature Sets document for more details if using a CV5x platform.
 * @code {.c}
 * board # cavalry_load -f /lib/firmware/cavalry.bin -r
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_yuv2rgb 2.1.1 test_vproc_yuv2rgb
 * The test_vproc_yuv2rgb uses the VProc library to convert YUV images to RGB images.
 * By default, the test converts YUV (NV12) images to RGB images. The available options
 * of test_vproc_yuv2rgb are as follows:
 * @verbatim
     -b --bin          Path to bin binary
     -i --input        Path to YUV input binary
     -o --output       Path to output binary
     -s --resolution   Image resolution [WxH]
     -p --pitch        Image pitch
     -R --ROI          ROI of input image, [x_offset],[y_offset],[width],[height]
     -y --yuv_format   YUV format, 10: NV12. Default is NV12 format
     -r --rgb_format   RGB format, 0: RGB; 1: BGR. Default is RGB
     -m --feed_mem     Feed VProc binary by memory instead of filename; default is disabled
     -t --time         Measure runtime
   @endverbatim
 *
 * One example is provided using the command below:
 * @code {.c}
 * board # test_vproc_yuv2rgb -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/yuv1080p.bin -o /tmp/rgb1080p.bin -s 1920x1080
 * @endcode
 *
 * @subsubsection vproc_library_test_resize 2.1.2 test_vproc_resize
 * The test_vproc_resize application can resize gray, UV-interleaved, RGB,
 * and YUV images to specified-resolution images with the same color space. Users
 * are free to choose the resize strategy, which could be either multiple steps
 * or a single step in order to approach the targeted ratio. The available test_vproc_resize
 * options are listed below:
 * @verbatim
     -b --bin              Path to bin binary
     -i --input            Path to input binary
     -o --output           Path to output binary
     -s --in_resolution    Input image resolution [WxHxD]
     -p --in_pitch         Input image pitch
     -R --ROI              Input image ROI, [x_offset],[y_offset],[width],[height]
     -S --out_resolution   Output image resolution [WxHxD]
     -P --out_pitch        Output image pitch
     -c --cspace           Image color space. 0: VECT; 1: RGB; 2: BGR; 10: NV12; 11: Y; 12: ITL; default is 0 (VECT)
     -m --method           Resize method. 0: mul-step; 1: sin-step; default is 0
     -t --time             Measure runtime
   @endverbatim
 *
 * Below is an example of resizing an RGB image with an region of interest (ROI), where only the ROI would be
 * taken into account.
 * @code {.c}
 * board # test_vproc_resize -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/rgb1080p.bin -o /tmp/rgb720p.bin -s 1920x1080x3 -S 1280x720x3 -c 1 -R 100,100,640,480
 * @endcode
 *
 * Resizing on CV72 and CV3 provides a certain degree of parallelism on the channel dimension. Performance improvement can be achieved
 * if data with the same input / output resolution and ROI settings can be combined in the channel dimension and executed together.
 * For instance, it takes almost the same time to resize RGB image as grayscale image (when channel-promotion is not applicable).
 *
 * On CV72 and CV3, channel-promotion optimization is also introduced to accelerate resizing performance.
 * It is however only applicable to planar input data, and in cases where:
 *  * The height dimension is being down-sampled ( output height <= input height )
 *  * The scale factor in the height dimension can be represented by 13 fractional bits ( (input height << 13) % output height) == 0 )
 *  * The input height and output height have a common divisor within [2, 43]
 *
 * Ambarella recommends that users design use cases in such a manner that they can profit from channel-promotion optimization, as the improvement in performance is substantial.
 * For example, resizing RGB 1920x1080 to 1280x720 requires 700 us when channel-promotion is enabled by default. When this optimization is disabled, it requires 3600 us.
 *
 * The channel-promotion feature is enabled by default. The VProc library provides an option to disable this optimization if there is a decrease in performance.
 * @note
 *   Multi-step resize is not yet supported on CV72.
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_submean 2.1.3 test_vproc_submean
 * The test_vproc_submean application subtracts a mean value from the input data
 * by channel or by pixel. Input data, mean data, and output data should be
 * represented as either fixed 8-bit values or fixed 16-bit values. The
 * available options of test_vproc_submean are as follows:
 * @verbatim
     -b --bin               Path to bin binary
     -i --input             Path to data input binary
     -m --mean              Path to mean input binary
     -o --output            Path to output binary
     -s --in_resolution     Input data resolution [WxHxD]
     -p --in_pitch          Input data pitch
     -S --mean_resolution   Mean data resolution WxHxD
     -P --mean_pitch        Mean data pitch
     -I --in_df             Input data format [sign] [datasize] [exp_offset] [exp_bits]. 0,0,0,0 stands for uint8. Default is 0,0,0,0. FP16 is 1,1,0,4
     -M --mean_df           Mean data format [sign] [datasize] [exp_offset] [exp_bits]. 0,0,0,0 stands for uint8. Default is 0,0,0,0. FP16 is 1,1,0,4
     -O --out_df            Output data format [sign] [datasize] [exp_offset] [exp_bits]. 0,0,0,0 stands for uint8. Default is 1,0,0,0. FP16 is 1,1,0,4
     -t --time              Measure runtime
   @endverbatim
 *
 * Follow the example to perform channel-wise mean subtraction.
 * @code {.c}
 * board # test_vproc_submean -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/rgb720p.bin -o /tmp/norm.bin -m /tmp/mean.bin -s 1280x720x3 -S 1x1x3 -I 0,0,0,0 -M 0,0,0,0 -O 1,0,0,0
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_scale 2.1.4 test_vproc_scale
 * The test_vproc_submean scales the input data by multiplying it with
 * a scale factor, which can be used to normalize the image data to a defined
 * range. Input data and output data should be represented as fixed 8-bit or
 * 16-bit values. The available test_vproc_scale options are as follows:
 * @verbatim
     -b --bin             Path to bin binary
     -i --input           Path to data input binary
     -o --output          Path to output binary
     -s --in_resolution   Input data resolution [WxHxD]
     -p --in_pitch        Input data pitch
     -I --in_df           Input data format [sign] [datasize] [exp_offset]. 0,0,0,0 stands for uint8. Default is 0,0,0,0
     -r --scale           Scale factor
     -O --out_df          Output data format [sign] [datasize] [exp_offset]. 0,0,0,0 stands for uint8. Default is 0,0,0,0
     -t --time            Measure runtime
   @endverbatim
 *
 * Use the command below to scale fixed 8-bit input data with a provided scale
 * factor. Both input and output data must be set by the user.
 * @code {.c}
 * board # test_vproc_scale -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/rgb720p.bin -o /tmp/out.bin -s 1280x720x3 -I 0,0,0,0 -r 0.00390625 -O 0,0,8,0
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_dtcvt 2.1.5 test_vproc_dtcvt
 * The test_vproc_submean applicaiton converts data among the FX8 / FX16 / FP16 / FP32
 * formats. Note that output data can overflow if the Q in the data format is not
 * correctly set. The available test_vproc_dtcvt options are as follows:
 * @verbatim
     -b --bin             Path to bin binary
     -i --input           Path to data input binary
     -o --output          Path to output binary
     -s --in_resolution   Input data resolution [WxHxD]
     -p --in_pitch        Input data pitch
     -P --out_pitch       Output data pitch
     -I --in_df           Input data format [sign] [datasize] [exp_offset] [exp_bits]. 0,0,0,0 stands for uint8. Default is 0,0,0,0. FP16 is 1,1,0,4
     -O --out_df          Output data format [sign] [datasize] [exp_offset] [exp_bits]. 0,0,0,0 stands for uint8. Default is 0,0,0,0. FP16 is 1,1,0,4
     -t --time            Measure runtime
   @endverbatim
 *
 * The test_vproc_dtcvt application is able to convert fixed 8-bit data to fixed
 * 16-bit data by setting the corresponding data format with the command below.
 * @code {.c}
 * board # test_vproc_dtcvt -b /tmp/vproc.bin -i /tmp/rgb720p.bin -o /tmp/out.bin -s 1280x720x3 -I 0,0,0,0 -O 0,1,0,0
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_rotate 2.1.6 test_vproc_rotate
 * The test_vproc_rotate applicaiton rotates / flips a fixed 8-bit image by
 * providing a rotate-flip bit map. The available test_vproc_rotate options
 * are as follows:
 * @verbatim
     -b --bin              Path to bin binary
     -i --input            Path to input binary
     -o --output           Path to output binary
     -s --in_resolution    Input image resolution WxHXD
     -p --in_pitch         Input image pitch
     -S --out_resolution   Output image resolution WxHXD
     -P --out_pitch        Output image pitch
     -c --color_space      Image color space. 0: VECT; 1: RGB; 2: BGR; 10: NV12; 11: Y; 12: ITL; Default is 0 (VECT)
     -f --rotate_flip      Set input port rotate-flip bit map. Specify bitmap order (High -> Low):
                            3: dflip; 2: vflip; 1: hflip; 0: rotate. For example: vflip+rotate: 0x05 (00101)
     -t --time             Measure run time
   @endverbatim
 *
 * Follow the example below to rotate an image 90 degrees:
 * @code {.c}
 * board # test_vproc_rotate -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/head1080p.bin -o /tmp/head_rot.bin -s 1920x1080x3 -S 1080x1920x3 -f 0x1
 * @endcode
 *
 * Rotate an image 180 degrees by simultaneously flipping an image horizontally and vertically:
 * @code {.c}
 * board # test_vproc_rotate -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/head1080p.bin -o /tmp/head_rot.bin -s 1920x1080x3 -S 1920x1080x3 -f 0x6
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_preproc 2.1.7 test_vproc_preproc
 * The test_vproc_rotate application performs pre-processing operations in a
 * chain, either starting image deformation (such as YUV2RGB and resize) or
 * data processing (such as mean substraction and scaling). The
 * available test_vproc_preproc options are as follows:
 * @verbatim
     -b --bin      Path to bin binary
     -m --mode     Modes to run image_deformation or data_polish. Default is 0
                     0: Image deformation; manages YUV2RGB, resize, cropping, and more
                     1: Data polish; manages submean, scaling, data type conversion, and more
        --in       Path to data input binary
        --out      Path to output binary
        --avg      Path to mean input binary
        --ires     Input data resolution [WxHxD]. Default is 1280x720x3
        --ipch     Input data pitch
        --ares     Mean data resolution [WxHxD]
        --apch     Mean data pitch
        --ores     Output data resolution [WxHxD]. Default is 1280x720x3
        --opch     Output data pitch
        --ics      Input color space. Default is 0
                     0: General vector; 1: RGB; 2: BGR; 3: NV12; 4: Y
        --ocs      Output color space. Default is 0
                     0: General vector; 1: RGB; 2: BGR; 3: NV12; 4: Y
     -R --roi      ROI of input image, [x_offset],[y_offset],[width],[height]
     -r --scale    Scale factor
     -I --in_df    Input data format [sign],[datasize],[exp_offset],[exp_bits]. 0,0,0,0 stands for uint8. FP16 is 1,1,0,4. Default is 0,0,0,0
     -O --out_df   Mean data format [sign],[datasize],[exp_offset],[exp_bits]. 0,0,0,0 stands for uint8. FP16 is 1,1,0,4. Default is 0,0,0,0
     -A --avg_df   Output data format [sign],[datasize],[exp_offset],[exp_bits]. 0,0,0,0 stands for uint8. FP16 is 1,1,0,4. Default is 0,0,0,0
     -t --time     Print runtime
     -h --help     Print help information
   @endverbatim
 *
 * Follow the test_vproc_preproc example below to use the YUV image as an input and
 * perform YUV2RGB, cropping, and resize operations in order to generate an
 * RGB image as a defined ROI.
 * @code {.c}
 * board # test_vproc_preproc -b /usr/share/ambarella/vproc/vproc.bin --in /tmp/yuv1080.bin --ires 1920x1080x3 --ics 3 --out /tmp/out.bin --ores 1280x720x3 --ocs 1 -R 0,200,1280,720 -m 0
 * @endcode
 *
 * Use test_vproc_preproc to manage mean substration,
 * scaling, and data type conversion in one call, as shown in the example below.
 * @code {.c}
 * board # test_vproc_preproc -b /usr/share/ambarella/vproc/vproc.bin --in /tmp/cvt720_fx8.bin --ires 1280x720x3 -ics 0 -I 0,0,0,0 --avg /tmp/cvt720_fx16.bin --ares 1280x720x3 -A 0,1,1,0 --out /tmp/out.bin --ores 1280x720x3 -O 0,0,2,0 --ocs 0 -r 0.5 -m 1
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_harris 2.1.8 test_vproc_harris
 * The test_vproc_harris application performs two-image matching using detected
 * Harris points with BRIEF descriptors. The available
 * test_vproc_harris options are as follows:
 * @verbatim
     -b   File path to vproc.bin
     -l   File path to left image file
     -r   File path to right image file
     -o   Output folder path
     -s   Resize the input image, image in [WxH] format; supports 1920x1080,1280x720 and 720x640
     -t   Harris response threshold
     -n   Maximum number of the Harris points
   @endverbatim
 *
 * Follow the example below to use test_vproc_harris to perform two-image
 * resizing to 1080p. Then, perform Harris point detection and
 * Harris point matching.
 * @code {.c}
 * board # test_vproc_harris -b /usr/share/ambarella/vproc/vproc.bin -l left.jpg -r right.jpg -o /tmp -s 1920x1080 -t 0.01 -n 1000
 * @endcode
 * @image html harris_match.jpg "Figure 2-1. Harris Point Matching."
 *
 *
 * @subsubsection vproc_library_test_vproc_harris_live 2.1.9 test_vproc_harris_live
 * This is a live demo that performs Harris point detection and screen
 * illustration. It only supports two input resolutions: 1920x1080 and 720x640.
 * The available test_vproc_harris_live options are as follows:
 * @verbatim
     -t   Harris point response threshold
     -n   Maximum number of Harris points
     -w   Set non-maximum suppression (NMS) window size
   @endverbatim
 *
 * Follow the example below to perform Harris point detection and to draw boxes
 * for each Harris point on the screen.
 * @code {.c}
 * board # test_vproc_harris_live -t 0.01 -n 2000 -w 28
 * @endcode
 * @image html harris_live_result.gif "Figure 2-2. Live Harris Detection."
 *
 *
 * @subsubsection vproc_library_test_vproc_perspective 2.1.10 test_vproc_perspective
 * The test_vproc_perspective application performs perspective warp using a given
 * perspective projection matrix. The input resolution should be one of the following:
 * 1/3x1280x800,1/3x1280x720, and 1/3x720x640. The available test_vproc_perspective
 * options are as follows:
 * @verbatim
     -b     File path to vproc.bin
     -i     File path to the input image file
     -m     The perspective projection matrix whose size must be 3x3
     -o     Output folder path
     -s     Resize the input images. The format is in [CxWxH], which supports [1/3]x1280x800,[1/3]x1280x720 and [1/3]x720x640
   @endverbatim
 *
 * The example below utilizes test_vproc_perspective to warp an image to a bird's-eye view.
 * @code {.c}
 * board # test_vproc_perspective -b /usr/share/ambarella/vproc/vproc.bin -i test.jpg -m [-0.46688,-1.89871,922.0,-0.06845,-3.18593,1304.6,-0.000059,-0.00311,1] -o /tmp -s 1x1280x800
 * @endcode
 * @image html perspective_result.jpg "Figure 2-3. Perspective Result."
 *
 * @note
 *   CV72 is not supported yet.
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_perspective_live 2.1.11 test_vproc_perspective_live
 * The test_vproc_perspective_live application performs a perspective live demo.
 * The available test_vproc_perspective_live options are as follows:
 * @verbatim
     -m   Perspective projection matrix whose size must be 3x3
     -s   Resizes input images in [1xWxH] format
   @endverbatim
 *
 * Use the command below to run the live perspective demo.
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi  (Need add extra module params for cv5: vinc_id=8 bus_id=3 )
 * board # test_aaa_service -a&
 * (cv2x command as below)
 * board # test_encode -i0 --hdmi 1080p --ors 1920x1080 --enc-dummy-latency 2
 * (or cv5 command as below, check inside vout_hdmi.lua,  selected vout osd_rescaler_output_window = {0, 0, 1920, 1080})
 * board # test_encode -i0 cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --enc-dummy-latency 2
 * board # rmmod ambarella_fb
 * board # modprobe ambarella_fb resolution=1920x1080 mode=clut8bpp buffernum=5
 * board # test_vproc_perspective_live -m [-0.46688,-1.89871,922.0,-0.06845,-3.18593,1304.6,-0.000059,-0.00311,1] -s 1x1280x800
 * @endcode
 *
 * @note
 *   CV72 is not supported yet.
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_cdist 2.1.12 test_vproc_cdist
 * The test_vproc_cdist application performs cosine distance calculations. The
 * available test_vproc_cdist options are as follows:
 * @verbatim
     -b   File path to vproc.bin
     -l   Input binary file path of data vector A
     -r   Input binary file path of data vector B
     -L   Data format of input file A
     -R   Data format of input file B
     -s   Vector input dimension [CxWxH]
   @endverbatim
 *
 * The example below uses test_vproc_cdist to calculate the cosine distance
 * between vector A and vector B.
 * @code {.c}
 * board # test_vproc_cdist -b /usr/share/ambarella/vproc/vproc.bin -l vect_A.bin -r vect_B.bin -L ufix8_8 -R ufix8_8 -s 3x256x128
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_imhist 2.1.13 test_vproc_imhist
 * The test_vproc_imhist application performs histogram analysis for a grayscale
 * input image. The available test_vproc_imhist options are as follows:
 * @verbatim
     -b   File path to vproc.bin
     -i   The grayscale input image
     -n   Category: number of histograms
     -o   Output folder path
     -s   Resize input images in [WxH] format
   @endverbatim
 *
 * The example below uses test_vproc_imhist to perform histogram calculations for a grayscale image.
 * @code {.c}
 * board # test_vproc_imhist -b /usr/share/ambarella/vproc/vproc.bin -i gray.jpg -n 256 -o /tmp -s 1920x1080
 * @endcode
 * @image html imhist_result.jpg "Figure 2-4. Image Histogram Result."
 *
 * @subsubsection vproc_library_test_vproc_imcvt 2.1.14 test_vproc_imcvt
 * The test_vproc_imcvt application converts images to different formats,
 * which are plane-interleaved and element-interleaved in the OpenCV format.
 * The available test_vproc_imhist options are as follows:
 * @verbatim
     -b --bin             Path to bin binary
     -i --input           Path to input binary
     -o --output          Path to output binary
     -s --in_resolution   Input image resolution [WxH]
     -p --in_pitch        Input image pitch
     -P --out_pitch       Output image pitch
     -c --cvt_code        Image conversion code. 0: amb2ocv; 1: ocv2amb; default is 0 (amb2ocv)
     -t --time            Measure runtime
   @endverbatim
 *
 * Follow the example below to convert an RGB image in Ambarella format to the OpenCV format
 * using test_vproc_imcvt.
 * @code {.c}
 * board # test_vproc_imcvt -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/head1080p_amb.bin -o /tmp/head1080p_ocv.bin -s 1920x1080x3 -c 0
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_cvfilter 2.1.15 test_vproc_cvfilter
 * The test_vproc_cvfilter application filters an input
 * grayscale or color image with the provided filter kernel. The available test_vproc_cvfilter
 * options are as follows:
 * @verbatim
     -b    File path to vproc.bin
     -i    Input grayscale / color image
     -o    Output folder path
     -s    Resize input images in [CxWxH] format
     -f    Filtering kernel size
     -k    Filtering kernel data. (Note: The same kernel applies to multiple input channels)
   @endverbatim
 *
 * The example below applies an average filter on the input image. The average window size is 11x11 and the elements value is 1/(11*11) = 0.00826.
 * @code {.c}
 * board # test_vproc_cvfilter -b /usr/share/ambarella/vproc/vproc.bin -i img.JPEG -o /tmp -s 3x1920x1080 -f 11x11 -k [0.00826]
 * @endcode
 * @image html cvfilter_result.jpg "Figure 2-5. Average CVfilter Result."
 *
 * @subsubsection vproc_library_test_vproc_morph 2.1.16 test_vproc_morph
 * The test_vproc_morph application applies dilation or erosion to a binarized / Luma
 * image. The application supports dilate / erode / open / close, and can be used to delete the noisy
 * points or fill the in-block hole. The available test_vproc_morph options
 * are as follows:
 * @verbatim
     -b    File path to vproc.bin
     -i    Input binarized image
     -m    0: binary dilate; 1: binary erode; 2: Luma dilate; 3: Luma erode
     -o    Output folder path
     -s    Resize input images in [WxH] format
     -t    Binarization threshold (set -1 in Luma morph)
     -f    Morph kernel size
     -k    Morph kernel data
     -r    Anner of border replication. 0: same data replicated; 1: zero data replicated
   @endverbatim
 *
 * The example provided below applies a morphological transformation.
 * @code {.c}
 * board # test_vproc_morph -b /usr/share/ambarella/vproc/vproc.bin -i pic1.jpg -m 0 -o /tmp -s 1920x1080 -t 127 -f 11x11 -r 0
 * board # test_vproc_morph -b /usr/share/ambarella/vproc/vproc.bin -i pic1.jpg -m 1 -o /tmp -s 1920x1080 -t 127 -f 11x11 -r 1
 * board # test_vproc_morph -b /usr/share/ambarella/vproc/vproc.bin -i pic1.jpg -m 2 -o /tmp -s 1280x720 -t -1 -f 5x5 -k [0,0,1,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,0,0,1,0,0]  -r 0
 * board # test_vproc_morph -b /usr/share/ambarella/vproc/vproc.bin -i pic1.jpg -m 3 -o /tmp -s 1280x720 -t -1 -f 5x5 -k [0,0,1,0,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,0,0,1,0,0]  -r 1
 * @endcode
 * @image html bin_morph_result.jpg "Figure 2-6. Binary Morph (Orginal / Dilate / Erode) Result."
 * @image html luma_morph_result.jpg "Figure 2-7. Luma Morph (Orginal / Dilate / Erode) Result."
 *
 * @subsubsection vproc_library_test_vproc_optlk 2.1.17 test_vproc_optlk
 * The test_vproc_optlk application performs LK calculations on two continuous
 * images. The available test_vproc_optlk options are as follows:
 * @verbatim
     -b   File path to vproc.bin
     -l   First input image
     -r   Second input image
     -o   Output folder path
     -s   Resize input images in [WxH] format
     -t   Threshold to the LK response (for details, see the application programming interface (API) vproc_optlk() )
     -z   With / without K coefficient. LK response value = det(M)-k*(trace(M))^2
     -w   LK window size
     -k   Windows kernel data; default is 1
     -d   Stride to draw the optical flow for pixels
   @endverbatim
 *
 * Run the command below to perform LK calculations using test_vproc_optlk.
 * @code {.c}
 * board # test_vproc_optlk -b /usr/share/ambarella/vproc/vproc.bin -l img0.jpg -r img1.jpg -o /tmp -s 160x90 -t 0.01 -w 11x11
 * @endcode
 * @image html optflow_flow.jpg "Figure 2-8. LK Optical Flow Result."
 *
 * @note
 *   CV72 is not supported yet.
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_optlk_flow_live 2.1.18 test_vproc_optlk_flow_live
 * The test_vproc_optlk_flow_live application shows a live demo of the optical
 * flow on Harris points. The available test_vproc_optlk_flow_live options
 * are as follows:
 * @verbatim
     -b   File path to vproc.bin
     -s   Resizes input in [WxH] format
     -d   Harris points reponse threshold
     -n   Harris points NMS window size
     -k   Scale-down factor of the input size; runs the optical flow on the scaled input
     -f   Run loop per frame
     -t   Threshold to the LK response (for details, see the API vproc_optlk() ).
     -w   LK window size
     -m   0: shows the optical flow on Harris points, 1: shows only the Harris points, 2: shows the full optical flow
     -o   Threshold to show the minimal optical flow displacement dx / dy
     -z   Scales the optical flow displacement dx / dy for display
   @endverbatim
 *
 * Execute the command below to run the optical flow live demo.
 * @code {.c}
 * board # rmmod ambarella_fb
 * board # modprobe ambarella_fb resolution=1920x1080 mode=clut8bpp buffernum=4
 * board # init.sh --na
 * board # modprobe lt6911  (Need add extra module params for cv5: vinc_id=8 bus_id=3 )
 * board # sleep 5
 * board # test_aaa_service -a&
 * (cv2x command as below)
 * board # test_encode --resource-cfg cv22_vin0_1080p_linear.lua --hdmi 1080p --ors 1920x1080
 * (or cv5 command as below, check inside vout_hdmi.lua,  selected vout osd_rescaler_output_window = {0, 0, 1920, 1080})
 * board # test_encode --resource-cfg cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_vproc_optlk_flow_live -b /usr/share/ambarella/vproc/vproc.bin -s 1920x1080 -d 0.01 -n 20 -k 10.0 -f 1 -t 0.001 -w 11x11 -m 0 -o 2 -z 4
 * @endcode
 * @image html optlk_flow_live.gif "Figure 2-9. Live LK Optical Flow on Harris Points."
 *
 * @note
 *   CV72 is not supported yet.
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_optlk_tracking_live 2.1.19 test_vproc_optlk_tracking_live
 * The test_vproc_optlk_tracking_live application is a live demo of LK tracking
 * based on Harris points. The available test_vproc_optlk_tracking_live options
 * are as follows:
 * @verbatim
     -b   File path to vproc.bin
     -s   Resize input in [WxH] format
     -t   Threshold to the LK response (for details, see the API vproc_optlk() )
     -w   LK window size
     -k   LK window weights
     -p   Pyramid level for LK tracking
     -f   Run loop per frame
     -l   Tracking records per frame
     -d   Harris points reponse threshold
     -n   Harris points NMS window size
     -o   Minimum tracking points (otherwise, add new Harris points for tracking)
   @endverbatim
 *
 * Run the command below to enable the optical tracking live demo.
 * @code {.c}
 * board # rmmod ambarella_fb
 * board # modprobe ambarella_fb resolution=1920x1080 mode=clut8bpp buffernum=4
 * board # init.sh --na
 * board # modprobe lt6911  (Need add extra module params for cv5: vinc_id=8 bus_id=3 )
 * board # sleep 5
 * board # test_aaa_service -a&
 * (cv2x command as below)
 * board # test_encode --resource-cfg cv22_vin0_1080p_linear.lua --hdmi 1080p --ors 1920x1080
 * (or cv5 command as below, check inside vout_hdmi.lua,  selected vout osd_rescaler_output_window = {0, 0, 1920, 1080})
 * board # test_encode --resource-cfg cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # test_vproc_optlk_tracking_live -b /usr/share/ambarella/vproc/vproc.bin -s 1280x720 -t 0.01 -w 11x11 -k [1.0] -p 4 -f 2 -l 2 -d 0.04 -n 64 -o 20
 * @endcode
 * @image html optlk_tracking_live.gif "Figure 2-10. Pyramid LK on Harris Points Tracking."
 *
 * @note
 *   CV72 is not supported yet.
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_edge_det 2.1.20 test_vproc_edge_det
 * The test_vproc_edge_det application performs edge detection. The available
 * test_vproc_edge_det options are as follows:
 * @verbatim
     -b   File path to vproc.bin
     -i   Input image file path
     -s   Resize input in [WxH] format
     -f   Kernel size of the edge filter
     -k   Kernel data of the edge filter
     -t   Edge line binarization threshold
     -p   Smooth filter kernel size; run the smooth filter before edge detection
     -o   Output path
   @endverbatim
 *
 * Use the example below to detect edge using test_vproc_edge_det.
 * @code {.c}
 * board # test_vproc_edge_det -b /usr/share/ambarella/vproc/vproc.bin -i img.JPEG -s 1280x720 -f 3x3 -k [1,2,1,0,0,0,-1,-2,-1] -t 20 -p 5x5 -o /tmp
 * @endcode
 * @image html edgedet_result.jpg "Figure 2-11. Sobel Edge Detection Result."
 *
 * @subsubsection vproc_library_test_vproc_memcpy 2.1.21 test_vproc_memcpy
 * The test_vproc_memcpy application performs a memory copy for a continuous
 * region. The available test_vproc_memcpy options are as follows:
 * @verbatim
     -i --input    Path to input binary
     -o --output   Path to output binary
     -l --loop     Loop count, always -1
     -t --time     Measure run time
     -c --cache    Enable cache
   @endverbatim
 *
 * The example below illustrates using test_vproc_memcpy to copy data.
 * @code {.c}
 * board # test_vproc_memcpy -i /tmp/1920x1080.y -o /tmp/out.bin -c -t
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_memset 2.1.22 test_vproc_memset
 * The test_vproc_memset application sets a continuous region of memory with a
 * provided value (0~255). The available test_vproc_memset options are
 * as follows:
 * @verbatim
     -b --bin      Path to bin binary
     -o --output   Path to output binary
     -s --size     Buffer size
     -a --val      Initial value (0~255)
     -t --time     Measure runtime
   @endverbatim
 *
 * The example below illustrates using test_vproc_memset to set memory.
 * @code {.c}
 * board # test_vproc_memset -o /tmp/out.bin -s 2073600 -a 0 -t
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_statistics 2.1.23 test_vproc_statistics
 * The test_vproc_statistics application gets input vector statistics such as mean,
 * standard deviation, minimum, and maximum. The available test_vproc_memset options
 * are as follows:
 * @verbatim
     -b --bin            Path to bin binary
     -i --input          Path to input binary
     -o --output         Path to output binary
     -s --in_resolution  Input image resolution [WxHxD]
     -p --in_pitch       Input data pitch
     -I --in_df          Input data format [sign] [datasize] [exp_offset] [exp_bits]. Default is uint8 (0,0,0,0)
     -O --out_df         Output data format [sign] [datasize] [exp_offset] [exp_bits]. Default is FP32 (1,2,0,7)
        --min            Enable minimum calculation if set to 1
        --max            Enable maximum calculation if set to 1
        --avg            Enable mean calculation if set to 1
        --std            Enable standard deviation calculation if set to 1
     -t --time           Measure runtime
   @endverbatim
 *
 * Use the example below to calculate the input vector statistics.
 * @code {.c}
 * board # test_vproc_statistics -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/1920x1080.y -o /tmp/out.bin -s 1920x1080x1 -I 0,0,0,0 -O 1,2,0,7 --min 1 --max 1 --avg 1 --std 1 -t
 * @endcode
 *
 * @note
 *   CV72 is not supported yet.
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_warp 2.1.24 test_vproc_warp
 * The test_vproc_warp application performs a variety of image
 * transformations based on warp operations. The available test_vproc_warp options
 * are as follows:
 * @verbatim
     -b --bin     Path to bin binary
     -i --in      Path to input binary
     -o --out     Path to output binary
     -w --warp    Path to warp table binary
     -m --mode    Warp mode. 0: generic warp; 1: warp affine; 2: warp perspective. Default is 0
        --ires    Input data resolution [WxHxD]
        --ipch    Input data pitch
        --ores    Output data resolution [WxHxD]
        --opch    Output data pitch
        --wres    Warp table resolution [WxH]
        --wpch    Warp table pitch
        --amat    2x3 warp affine transformation matrix
        --pmat    3x3 warp perspective transformation matrix
        --inv     Matrix is the inverse transformation matrix. 0: non-inverse; 1: inverse. Default is 0
     -s --dsize   Input / output (I/O) data size. 0 for 8-bit; 1 for 16-bit. Default is 0
     -t --time    Measure run time
   @endverbatim
 *
 * The test_vproc_warp can perform any transformation as long as the warp field is
 * correctly provided.
 * @code {.c}
 * board # test_vproc_warp -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/y720.bin -o /tmp/out.bin -w /tmp/wt.bin --ires 1280x720x1 --ores 1280x720x1 --wres 641x361 -m 0 -s 0 -t
 * @endcode
 *
 * Warp affine transformation is also supported by the test_vproc_warp
 * application. The user must provide the affine transformation matrix.
 * @code {.c}
 * board # test_vproc_warp -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/y720.bin -o /tmp/out.bin --ires 1280x720x1 --ores 640x360x1 --amat 0.5,0,0,0,0.5,0 --inv 1 -m 1 -s 0 -t
 * @endcode
 *
 * Warp perspective transformation is achievable using the test_vproc_warp
 * application if the perspective transformation matrix is provided.
 * @code {.c}
 * board # test_vproc_warp -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/y720.bin -o /tmp/out.bin --ires 1280x720x1 --ores 1280x720x1 --pmat -0.46688,-1.89871,922.0,-0.06845,-3.18593,1304.6,-0.000059,-0.00311,1 --inv 1 -m 2 -s 0 -t
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_epnr 2.1.25 test_vproc_epnr
 * The test_vproc_epnr application performs edge-preserved noise reduction (EPNR). The available
 * test_vproc_epnr options are as follows:
 * @verbatim
     -b    File path to vproc.bin
     -i    Input path of Y / YUV data
     -s    Input size in format [WxH]
     -d    Alpha value; range in [0, 14]. Set to 0 to keep as original input
     -o    Output path
   @endverbatim
 *
 * Follow the example below to perform EPNR using test_vproc_epnr.
 * @code {.c}
 * board # test_vproc_epnr -b /usr/share/ambarella/vproc/vproc.bin -s 384x288 -i in.NV12 -d 10 -o /tmp
 * @endcode
 * @image html epnr_thermal.png "Figure 2-12. Edge-Preserved Noise Reduction Result from Thermal Map Test."
 * @image html epnr_yuv.png "Figure 2-13. Edge-Preserved Noise Reduction Result from YUV Image Test."
 *
 * @subsubsection vproc_library_test_vproc_epnr_live 2.1.26 test_vproc_epnr_live
 * The test_vproc_epnr_live application performs the EPNR live demo. The available
 * test_vproc_epnr_live options are as follows:
 * @verbatim
     -b    File path to vproc.bin
     -k    Low pass filter kernel size
     -B    Canvas buffer ID
     -d    Alpha value; range is [0, 14]. Set to 0 to keep as original input
     -m    Run mode
   @endverbatim
 *
 * Run the command below to enable the EPNR demo.
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi  (Need add extra module params for cv5: vinc_id=8 bus_id=3 )
 * board # test_aaa_service -a&
 * board # rmmod ambarella_fb
 * board # modprobe ambarella_fb resolution=1920x1080 mode=clut8bpp buffernum=5
 * (cv2x command as below)
 * board # test_encode --resource-cfg cv22_vin0_1080p_linear.lua  --hdmi 1080p --ors 1920x1080 --vout-from-image 1
 * (or cv5 command as below, check inside vout_hdmi.lua,  selected vout osd_rescaler_output_window = {0, 0, 1920, 1080}, vout_from_image = "enable")
 * board # test_encode --resource-cfg cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 * board # cavalry_load -f /lib/firmware/cavalry.bin
 * board # test_vproc_epnr_live -b /usr/share/ambarella/vproc/vproc.bin -d 10 -k 3 -B 2 -m 3
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_bayer2bgr 2.1.27 test_vproc_bayer2bgr
 * The test_vproc_bayer2bgr application performs data format conversion from Bayer pattern to BGR / RGB.
 * The available test_vproc_bayer2bgr options are as follows:
 * @verbatim
     -b    File path to vproc.bin
     -i    Bayer pattern input file path
     -s    Input size in [WxH] format
     -c    0: RGB sequence; 1: BGR sequence
     -o    Output path
   @endverbatim
 *
 * Follow the example below to convert Bayer data to RGB data using test_vproc_bayer2bgr.
 * @code {.c}
 * board # test_vproc_bayer2bgr -b /usr/share/ambarella/vproc/vproc.bin -i bayer_in_1080p.bin  -s 1920x1080 -c 0 -o /tmp
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_cclb 2.1.28 test_vproc_cclb
 * Run the test_vproc_cclb application to label the connected component.
 * The available test_vproc_cclb options are as follows:
 * @verbatim
     -b    File path to vproc.bin
     -i    Path to input image
     -s    Input resize resolution in [WxH] format
     -t    Black / white threshold; for example, -t 128
     -w    Method of connection. 0: 4-way,1: 8-way
     -c    Minimum component size
     -h    Minmum hole size
     -o    Path to output folder; for example, -o / tmp
     -l    Scale factor for label
   @endverbatim
 *
 * Follow the example below to label the connected component using test_vproc_cclb.
 * @code {.c}
 * board # test_vproc_cclb -b /usr/share/ambarella/vproc/vproc.bin -i Ambarella.png  -s 128x128 -t 128 -w 1 -c 10 -h 4 -o /tmp/ -l 40
 * @endcode
 *
 * @note
 *   CV72 is not supported yet.
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_alpha_blend 2.1.29 test_vproc_alpha_blend
 * Run the test_vproc_alpha_blend application to blend two images using an alpha
 * matrix. The available test_vproc_alpha_blend options are as follows:
 * @verbatim
     -b --bin                 Path to bin binary
        --inA                 Path to input image A binary
        --inB                 Path to input image B binary
        --alpha               Path to input alpha matrix binary
        --out                 Path to output binary
        --in_resolution       Input images resolution [WxHxD]
        --in_pitch            Input images pitch
        --alpha_resolution    Input alpha matrix resolution [WxH]
        --alpha_pitch         Alpha matrix pitch
        --out_pitch           Output image pitch
        --cs                  Color space of input / output images. Default is 0
                                0: General vector; 1: RGB; 2: BGR; 3: NV12; 4: Y
     -t --time                Measure runtime
   @endverbatim
 *
 * The example below uses test_vproc_alpha_blend to merge two images.
 * @code {.c}
 * board # test_vproc_alpha_blend -b /usr/share/ambarella/vproc/vproc.bin --inA head_1080p.bin --inB rgb_1080p.bin --alpha mask0_5.bin --out out.bin --in_resolution 1920x1080x3 --alpha_resolution 1920x1080 --cs 0 -t
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_abs 2.1.30 test_vproc_abs
 * Run the test_vproc_abs application to calculate the absolute values of a matrix.
 * The available test_vproc_abs options are as follows:
 * @verbatim
     -b --bin       Path to bin binary
     -i --input     Path to input binary
     -o --output    Path to output binary
     -s --ires      Input image resolution [WxHxD]
     -p --ipch      Input data pitch
     -I --idf       Input data format [sign] [datasize] [exp_offset] [exp_bits]. Default is int8 (1,0,7,0)
     -O --odf       Output data format [sign] [datasize] [exp_offset] [exp_bits]. Default is int8 (1,0,7,0)
     -t --time      Measure runtime
   @endverbatim
 *
 * Follow the example below to obtain the absolute value matrix from a matrix using test_vproc_abs.
 * @code {.c}
 * board # test_vproc_abs -b /usr/share/ambarella/vproc/vproc.bin -i data.bin -o out.bin -s 1280x720x1 -I 1,1,0,4 -O 1,1,0,4 -t
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_rgb2yuv 2.1.31 test_vproc_rgb2yuv
 * Run the test_vproc_rgb2yuv application to convert an image from RGB format to YUV
 * format.
 * The available test_vproc_rgb2yuv options are as follows:
 * @verbatim
     -b --bin            Path to bin binary
     -i --input          Path to RGB input binary
     -o --output         Path to YUV output binary
     -s --resolution     Image resolution [WxH]
     -p --pitch          Image pitch
     -R --ROI            ROI of input image, [x_offset],[y_offset],[width],[height]
     -r --rgb_format     RGB format, 0: RGB; 1: BGR. Default is RGB
     -y --yuv_format     YUV format, 10: NV12. Default is NV12 format
     -t --time           Measure runtime
   @endverbatim
 *
 * Follow the example below to use test_vproc_rgb2yuv to convert an image from RGB to
 * NV12.
 * @code {.c}
 * board # test_vproc_rgb2yuv -b /usr/share/ambarella/vproc/vproc.bin -i rgb_1080p.bin -o out.bin -s 1920x1080 -t
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_transpose 2.1.32 test_vproc_transpose
 * Run the test_vproc_transpose application to transpose a vector.
 * The available test_vproc_transpose options are as follows:
 * @verbatim
     -b --bin        Path to bin binary
     -i --input      Path to input binary
     -o --output     Path to output binary
     -s --idim       Input vector dimension [DxHxW]
     -p --ipch       Input vector pitch
     -P --opch       Output vector pitch
     -T --tspose     Transpose operation. 0: CHW2HWC; 1: HWC2CHW. Default is 0
     -d --dsize      Data size of the I/O vector. 0 is 8-bit, 1 is 16-bit
     -t --time       Measure runtime
   @endverbatim
 *
 * The example below uses test_vproc_transpose to tranpose a vector from
 * CxHxW to HxWxC.
 * @code {.c}
 * board # test_vproc_transpose -i bgr_320x180.bin -o /tmp/out.bin -s 3x180x320 -T 0 -d 0 -t 0
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_render3d 2.1.33 test_vproc_render3d_live
 * Run the test_vproc_render3d_live application to directly render a point cloud via video output (VOUT)
 * high-definition multimedia interface (HDMI®) without PC tool support.
 * @verbatim
     The point cloud rendering function consists of two sub-functions:
         - Transfer and rotate the point cloud in the world Axis
         - Render the point cloud to the canvas
     Both results from the sub-functions can be dumped by the library function, and only the rendering result is used in this unit test.
     The whole processing sequence in the unit test is as follows:
      1. Input the depth map
      2. Convert to point cloud in world Axis; the data format of the point in the world Axis should be int16
      3. Center shift the point cloud
      4. Rotate the point cloud
      5. Transfer shift the point cloud
      6. Project for 3D rendering
      7. Draw on VOUT
     The library performs the functions from step 3 to step 6.
     The formula from step 3 to step 5 is as follows: P_out=R_rot * (P_in + T_center) + T_trans, P_in/out=(Px,Py,Pz)
     R_rot = Rot_yaw * Rot_roll * Rot_pitch
   @endverbatim
 * @image html render3d_world_axis.png "Figure 2-14. Render 3D World Axis."
 * The available test_vproc_render3d_live options are as follows:
 * @verbatim
     -b   Path to vproc.bin
     -i   Input depth map; for example, -i depth.bin
     -s   Input size of depth map
     -S   Projection resolution
     -f   Focal length of input depth
     -F   Focal length of projection
     -r   Rotation degree (Pitch#Roll#Yaw); for example, 90#30#180
     -c   Center shift [X#Y#Z]; for example, 0#0#-50 indicates rotation around the origin point at (0,0,50)
     -t   Transfer shift [X#Y#Z]; for example, -t 0#0#500 indicates the object shift at (0,0,500) for rendering
     -d   Rendering stride. High stride means low rendering density
     -q   Rendering depth range; for example, -q 100#500 indicates that a depth from 100 to 500 has rendering
     -m   Run live frequence; for example, -m 0 [0:static mode, 1: live mode]
     -Q   Scale of depth data; for example, -Q 0.0625. Some depth data has a high accuracy level; for example, with 1/16 pixel accuracy
   @endverbatim
 *
 * The two examples below run point cloud rendering using test_vproc_render3d_live.
 * @code {.c}
 * board # test_vproc_render3d_live -b /usr/share/ambarella/vproc/vproc.bin -i dm_face_int16.bin -s 400x640 -S 1920x1080 -f 822.4  -F 622.4 -r 0#0#0 -c 0#0#-800 -t 0#0#800 -d 3 -q 500#1000 -m 1 -Q 1.0
 * @endcode
 * @image html render3d_live.gif "Figure 2-15. Live Rendering of a Point Cloud."
 * @image html render3d_static.png "Figure 2-16. Static Rendering of a Point Cloud."
 *
 * @subsubsection vproc_library_test_vproc_bitwise 2.1.34 test_vproc_bitwise
 * Run the test_vproc_bitwise application to perform bitwise logical operations.
 * The available test_vproc_bitwise options are as follows:
 * @verbatim
     -b --bin              Path to bin binary
        --in0              Path to input0 binary
        --in1              Path to input1 binary
        --out              Path to output binary
     -s --in_resolution    Input image resolution [WxHxC]
     -p --in_pitch         Input image pitch
     -P --out_pitch        Output image pitch
     -o --opt_code         Bitwise operation code
                   0: v0&v1; 1: v0&~v1; 2: ~v0&v1; 3: ~(v0|v1); 4: v0|v1; 5: v0|~v1;6: ~v0|v1; 7: ~(v0&v1); 8: v0^v1; 9: ^(v0^v1). Default is 0 (v0&v1)
     -t --time             Measure runtime
   @endverbatim
 *
 * Follow the example below using test_vproc_bitwise to perform "or" bitwise logical operations.
 * @code {.c}
 * board # test_vproc_bitwise --in0 1.bin --in1 2.bin --out 1or2.bin -s 32x32x3 -p 32 -P 32 -o 4
 * @endcode
 *
 * @subsubsection vproc_library_test_vproc_fbm 2.1.35 test_vproc_fbm
 * Run the test_vproc_fbm application to generate the disparity using fast BM (FBM). The available test_vproc_fbm options are as follows.
 * @verbatim
     -b --bin                Path to vproc.bin; for example, -b /usr/share/ambarella/vproc/vproc.bin
     -l --src input          Path to source input image; for example, -l left.jpg
     -r --ref input          Path to reference input image; for example, -r right.jpg
     -o --output             Path to output folder; for example, -o /tmp
     -s --resolution         Resize input to WxH; for example, -s 720x640, maximum resolution is 1280x720
     -A --roi                ROI configuration [x#y#w#h]; for example, -A 320#180#640#480, not supported in CV7x version
     -w --SAD-winsize        SAD window size; for example, -w 15, range in [11,27]
     -g --SAD-thresh         SAD threshold, suggestion from 4000 to 50000; for example, -g 10000
     -n --disparity-num      Disparity number,CV2x: range in [27, 135], must be times of 9. CV7x: range in [33, 143], must be times of 11. For example, -n 66,
     -t --min-disparity      Minimum disparity value; for example, -t -32
     -q --fb-value           Focal length multiply baseline; for example, -q 1000
     -u --unique-ratio       Unique ratio, range [0,100]; for example, -u 3
     -f --pre-post-filter    With post / pre-filter; for example, -f 1, [0x01:pre-filter:xsobel, 0x02:pre-filter:xnorm, 0x04:post-process: dfilter & dsfilter ]
     -d --max-speckle-diff   Maximum disparity / depth speckle difference; for example, -d 15
     -a --max-speckle-size   Maximum disparity / depth speckle size; for example, -a 7, range in [2,11]
     -k --texture-threshold  Texture threshold range in [0,100]; for example, -k 5
     -e --dsfilter-alpha     dsfilter alpha; for example, -e 0.1  [diparity / depth smooth filter with edge preserved], suggest range in [0.1, 10]
   @endverbatim
 * The FBM dumped disparity value is a fixed-point value in 16 signed bits, with 4 lower bits for fraction accuracy.
 * @code {.c}
 * real_disparity = dump_disparity / 16.0, real_disparity is float value.
 * @endcode
 * Below is an example to run test_vproc_fbm.
 * @code {.c}
 * board # test_vproc_fbm -b /usr/share/ambarella/vproc/vproc.bin -l l2.png -r r2.png -o /tmp -w 17 -g 40000 -n 63 -t 0  -q 3200 -u 3  -s 1280x720 -d 15  -a 7 -f 4 -k 5 -e 2
 * @endcode
 * @image html fbm_src.png "Figure 2-17. FBM Inputs."
 * @image html fbm_disp.png "Figure 2-18. FBM Output Disparity."
 * &diams; <b>FBM schematic:</b><br>
 * The following image shows the FBM schematic, which enables users to set the minimum-disparity for all the values even for a negative value, <br>
 * which is convenient for mono-stereo solutions. The maximum disparity number is 135. <br>
 * The following chart on the right demonstrates the way to define the min-disparity and disparity number.
 * @image html fbm_schematic.png "Figure 2-19. FBM Schematic."
 * &diams; <b>FBM pipeline with pre-process and post-process: </b><br>
 * FBM must function with pre-process and post-process functions in order to obtain improved disparity / depth results. <br>
 * Different solutions, hardware conditions, and use scenarios may require different pre-process / post-process conditions. <br>
 * Currently, the xsobel and xnorm filters are designed for pre-processing. Dfilter and dsfilter are designed for post-processing. <br>
 * Not all cases require pre-process and post-process; requirements depend on if the quality of disparity maps / depth maps meet expectations. <br>
 * @image html fbm_pipeline.png "Figure 2-20. FBM Process Pipeline."
 * &diams; <b>pre-process: (xsobel filter and xnorm filter)</b><br>
 * Both the xsobel filter and xnorm filter are used to extract details from a RAW input image. Xsobel focuses on gradient details while xnorm focuses on grayscale details.<br>
 * Both can be used in stereo, active stereo, and mono structured-light stereo conditions. The filters can also run simultaneously with high efficiency and excellent results. <br>
 * The following case shows the disparity result from a mono structured-light stereo. Using the xnorm filter provides better results than when the filter is not in use.
 * @image html fbm_prefilter_result.png "Figure 2-21. Using Xnorm Filter in Mono Structured-Light Stereo."
 * &diams; <b>dfilter: (Noise filter of disparity / depth map)</b><br>
 * The following image demonstrates the <b>disparity / depth noise filter (dfilter)</b>process, which suppresses disparity / depth noise speckles.
 * When the disparity / depth noise speckles are detected, the speckles are stuffed by a filtered value.
 * <br>
 * <br>
 * @image html dfilter.png "Figure 2-22. Dfilter Process."
 *
 *  The dfilter configurations are as follows:
 * @verbatim
     max_speckle_size:  Maximum noise speckle size to be suppressed; range is [2,11]
     filtered_val:      When noise speckles are detected, fill the filtered value into these speckles
     max_diff:          The gradient threshold of disparity / depth map. A gradient under max_diff indicates a continual area; a gradient over max_diff indicates an area edge
   @endverbatim
 * @image html dfilter_result.png "Figure 2-23. Dfilter Result."
 * &diams; <b>dsfilter: (Edge-preserved smooth filter of disparity / depth map)</b><br>
 * The dsfilter configurations are as follows :
 * @verbatim
     alpha:        Smooth filter intensity; suggested range is from 0.1 to 10
     filtered_val: Filtered value in disparity / depth map will be skipped by dsfilter
     keep_edge:    Disparity / depth map gradient threshold. A gradient under keep_edge indicates a continual area; a gradient over keep_edge indicates an area edge
     rad:          Filter radius, valid in rad = 2
   @endverbatim
 * @image html dsfilter_result.png "Figure 2-24. Dsfilter Result."
 *
 *
 * @subsubsection vproc_library_test_vproc_fbm_live 2.1.36 test_vproc_fbm_live
 * Run the test_vproc_fbm_live application to generate the disparity map using FBM in a live demo. The available test_vproc_fbm_live options are as follows:
 * @verbatim
     -b --bin                 Path to vproc.bin; for example, -b /usr/share/ambarella/vproc/vproc.bin
     -i  --input              Input canvas buffer ID; for example, -i 2
     -o --overlay-stream      Output stream ID; for example, -o 1
     -s --resolution          Resize input to WxH; for example, -s 720x640
     -A --roi                 ROI configuration [x#y#w#h]; for example, -A 320#180#640#480, not supported in CV7x version
     -w --SAD-winsize         SAD window size; for example, -w 15
     -g --SAD-thresh          SAD threshold; the suggested value is from 4000 to 50000. For example, -g 10000
     -n --disparity-num       Disparity number,CV2x: range in [27, 135], must be times of 9. CV7x: range in [33, 143],must be times of 11.  For example, -n 66,
     -t --min-disparity       Minimum disparity value; for example, -t -32
     -u --unique-ratio        Unique ratio, range is [0,100]. For example, -u 10
     -f --pre-post-filter     With post / pre-filter; for example, -f 1, [0x01:pre-filter, 0x02:post-filter, 0x03:both filter ]
     -d --max-speckle-diff    Maximum disparity speckle difference; for example, -d 15
     -a --max-speckle-size    Maximum disparity speckle size; for example, -a 7, range in [2,11]
     -k --texture-threshold   Texture threshold range is [0,100]; for example, -k 5
     -j --render-color-scale  Render color scale; for example, -j 1
   @endverbatim
 *
 * Follow the example below to run test_vproc_fbm_live.
 * @code {.c}
 * board # test_vproc_fbm_live -b /usr/share/ambarella/vproc/vproc.bin -i 2 -o 0  -w 15 -g 50000 -n 81  -t 0 -A 0#0#0#0  -u 10  -s 960x640 -d 16  -a 5 -f 2 -k 5 -j 1
 * @endcode
 * @image html fbm_live_disp.png "Figure 2-25. FBM Live Demo."
 *
 *
 * @subsubsection vproc_library_test_vproc_fbm_render_live 2.1.37 test_vproc_fbm_render_live
 * Run the test_vproc_fbm_render_live application to render the point cloud for the FBM result in the live demo. The available test_vproc_fbm_render_live options are as follows:
 * @verbatim
     -b --bin                 Path to vproc.bin; for example, -b /usr/share/ambarella/vproc/vproc.bin
     -i --input               Input canvas buffer ID; for example, -i 2
     -o --overlay-stream      Output stream ID; for example, -o 1
     -s --resolution          Resize input to [WxH]; for example, -s 720x640
     -A --roi                 ROI configuration [x#y#w#h]; for example, -A 320#180#640#480, not supported in CV7x version
     -w --SAD-winsize         SAD window size; for example, -w 15
     -g --SAD-thresh          SAD threshold, suggested range is from 4000 to 50000. For example, -g 10000
     -n --disparity-num       Disparity number,CV2x: range in [27, 135], must be times of 9. CV7x: range in [33, 143], must be times of 11.  For example, -n 66,
     -t --min-disparity       Minimum disparity value; for example; -t -32
     -u --unique-ratio        Unique ratio, range [0,100]; for example, -u 10
     -f --pre-post-filter     With post / pre-filter; for example, -f 1, [0x01: pre-filter, 0x02: post-filter, 0x03: both filters]
     -d --max-speckle-diff    Maximum disparity speckle difference; for example, -d 15
     -a --max-speckle-size    Maximum disparity speckle size; for example, -a 7, range is [2,11]
     -F --lens-focal-length   Lens focal length. -F 820
     -B --baseline            Baseline (unit mm); for example, -B 40
     -Q --pc-depth-range      Point cloud rendering depth range; for example, -Q 100#500
     -k --texture-threshold   Texture threshold range [0,100]; for example, -k 20
     -r --render-stride       Render stride; for example, -r 3
     -R --rotation            Rotations (Pitch#Roll#Yaw); for example, -R 10#10#10
     -C --center-shift        Center shift [X#Y#Z]; for example, -C 0#0#-250
     -T --trans-shift         Transfer shift [X#Y#Z]; for example, -T 0#0#250
   @endverbatim
 *
 * Follow the example below to run test_vproc_fbm_render_live.
 * @code {.c}
 * board # test_vproc_fbm_render_live -b /usr/share/ambarella/vproc/vproc.bin -i 2 -o 0  -w 15 -g 50000 -n 81  -t 0 -A 0#0#0#0  -u 10  -s 960x640 -d 16  -a 5 -f 2 -k 5 -Q  0#32000 -F 820 -B 40 -r 4 -C 0#-100#-1000 -R  0#0#10 -T -400#0#500
 * @endcode
 * @image html fbm_live_render.png "Figure 2-26. FBM Live Demo."
 *
 *
 * @subsubsection vproc_library_test_vproc_flatten 2.1.38 test_vproc_flatten
 * The test_vproc_flatten uses the VProc library to flatten the shape of input.
 * The available options of test_vproc_flatten are as follows:
 * @verbatim
     -b --bin          Path to bin binary
     -i --input        Path to input binary
     -o --output       Path to output binary
     -s --ires         Input image resolution WxHxD
     -p --ipch         Input data pitch
     -I --in_df        Input data format [sign] [datasize] [exp_offset] [exp_bits]. Default is uint8(0,0,0,0)
     -O --out_df       Output data format [sign] [datasize] [exp_offset] [exp_bits]. Default is uint8(0,0,0,0)
     -c --cspace       Color space of image. 0: VECT; 1: RGB; 2: BGR; 11: Y; 12: ITL. Default is 0(VECT)
     -t --time         Measure runtime
   @endverbatim
 *
 * One example is provided using the command below:
 * @code {.c}
 * board # test_vproc_flatten -b /usr/share/ambarella/vproc/vproc.bin -i /tmp/in.bin -o /tmp/out.bin -s 1920x1080x3 -c 0 -t
 * @endcode
 *
 *
 * - - - -
 *
 * @section sec_vproc 3. VProc Performance
 * The table below shows the VProc performance on CV chips.
 * |     VProc Fun    | CV2 | CV22 (DRAM: 1800 MHz, VP: 1008 MHz) | CV25 | CV28 | CV5 | CV72 |
 * |------------------|-----|------|------|------|------|------|
 * |yuv2rgb           | |4.3 ms (3840x2160)<br>1.1 ms (1920x1080)<br>0.5 ms (1280x720)| | | | |
 * |resize            | |2.8 ms (RGB, 3840x2160 -> 1920x1080)<br>0.9 ms (RGB, 1920x1080 -> 1280x720)<br>2.1 ms (NV12, 3840x2160 -> 1920x1080)<br>0.84 (NV12, 1920x1080 -> 1280x720)| | | | |
 * |submean           | |1.3 ms (RGB, 1920x1080)<br>0.76 ms (RGB, 1280x720)| | | | |
 * |scale             | |1.6 ms (RGB; 1920x1080)<br>0.78 ms (RGB; 1280x720)| | | | |
 * |dtcvt             | |2 ms (RGB, 1920x1080)<br>0.9 ms (RGB, 1290x720)| | | | |
 * |rotate            | |5.9 ms (RGB, 1920x1080, r90)<br>1.5 ms (RGB, 1920x1080, r180)<br>5.6 ms (RGB, 1920x1080, r270)<br>2.3 (RGB, 1280x720, r90)<br>0.66 ms (RGB, 1280x720, r180)<br>2.3 ms (RGB, 1280x720, r270)| | | | |
 * |harris            | |8 ms (can reach 5.2 ms after 8-bit optimization, 1920x1080)| | | |4ms |
 * |wrap              | |11.97 ms (generic warp, 1920x1080, warp mat size: 640x360)<br>8.69 ms (generic warp, 1280x720, warp mat size: 640x360)<br>1.48 ms (warp affine, 1920x1080 -> 960x720)<br>0.55 ms (warp affine, 1280x720 -> 640x320)<br>19.16 ms (warp perspective, 1920x1080)<br>8.66 ms (warp perspective, 1280x720)| | | | |
 * |perspective       | |13.1 ms (1280x800)| | | | |
 * |cdist             | |89 ms (RGB, 1920x1080)<br>40 ms (RGB, 1280x720)| | | | |
 * |imhist            | |2.2 ms (RGB, 1920x1080)<br>1 ms (RGB, 1280x720)| | | | |
 * |imcvt             | |4.1 ms (1920x1080, ocv -> ambaRGB)<br>1.8 ms (1280x720, ocv -> ambaRGB)| | | | |
 * |merge_uv          | |0.61 ms (image res: 1920x1080)<br>0.31 ms (image res: 1280x720)| | | | |
 * |split_uv          | |0.32 ms (image res: 1920x1080)<br>0.2 ms (image res: 1280x720)| | | | |
 * |cvfilter          | |2.8 ms (1080p, filter size=3x3)<br>4 ms (1080p, filter size=11x11)| | | | |
 * |morph             | |3.3 ms (dilate, RGB, 1920x1080)<br>1.6 ms (dilate, RGB, 1280x720)| | | | |
 * |optlk             | |9 ms (720p)<br>4.9 ms (720x640)<br>0.3 ms (120x80)| | | | |
 * |memcpy            | |1.6 ms (RGB, 1080p)<br>0.76 ms (RGB, 720p)| | | | |
 * |memset            | |0.61 ms (RGB, 1080p)<br>0.3 ms (RGB, 720p)| | | | |
 * |statistics        | |6.2 ms (RGB, 1080p)<br>2.84 ms (RGB, 720p)| | | | |
 * |epnr              | |15 ms (1080p)<br>2.5 ms (640x480)<br>1 ms (384x288)| | | | |
 * |bayer2bgr         | |14.1 ms (1920x1080)<br>6.6 ms (1280x720)| | | | |
 * |cclb              | |0.21 ms (128x128)<br>0.22 ms (256x256)<br>0.4 ms (512x512)| | | | |
 * |alpha_blend       | |2.3 ms (RGB, 1920x1080)<br>1.05 ms (RGB, 1280x720)| | | | |
 * |abs               | |1.28 ms (RGB, 1920x1080)<br>0.67 ms (RGB, 1280x720)| | | | |
 * |transpose         | |13.59 ms (RGB, 960x720, chw2hwc)<br>17.43 ms (RGB, 960x720, hwc2chw)| | | | |
 * |bitwise           | |1.78 ms (RGB, 1920x1080, a & b)<br>0.83 ms (RGB, 1280x720, a & b)| | | | |
 * |flatten           | |1.37 ms (RGB, 1920x1080)<br>0.67 ms (RGB, 1280x720)| | | | |
 * |render3D          | |5 ms (400x600, drawing stride is 2)<br>10 ms (400x600, drawing stride is 1)| | | | |
 * |FBM          	  | |30 ms (640x480, disparity number is 63) <br>90 ms (1280x720, disparity number is 63)| | |22 ms <br>70 ms |16 ms (disparity number is 66)<br>46 ms (disparity number is 66)|
 *
 * - - - -
 *
 * @section sec_vproc_api 4. VProc API
 * Visit the following link for details on API functions.
 *      - @ref vproc-api-details shows API lists.
 *      - @ref vproc-api-details-mfd shows memory file descriptor (MFD) lists for API use.
 *      - @ref vproc-helper shows related macros, enumerations, and structures.
 *
 * - - - -
 *
 * @section sec_vproc_lic 5. License
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
 * @example test_vproc_yuv2rgb.c
 * This is a source code file of test_vproc_yuv2rgb.
 *
 */
 /*!
  * @example test_vproc_resize.c
  * This is a source code file of test_vproc_resize.
  *
  */
 /*!
 * @example test_vproc_submean.c
 * This is a source code file of test_vproc_submean.
 *
 */
 /*!
 * @example test_vproc_scale.c
 * This is a source code file of test_vproc_scale.
 *
 */
 /*!
 * @example test_vproc_dtcvt.c
 * This is a source code file of test_vproc_dtcvt.
 *
 */
 /*!
 * @example test_vproc_rotate.c
 * This is a source code file of test_vproc_rotate.
 *
 */
 /*!
 * @example test_vproc_preproc.c
 * This is a source code file of test_vproc_preproc.
 *
 */
 /*!
 * @example test_vproc_harris.cpp
 * This is a source code file of test_vproc_harris.
 *
 */
 /*!
 * @example test_vproc_harris_live.cpp
 * This is a source code file of test_vproc_harris_live.
 *
 */
 /*!
 * @example test_vproc_perspective.cpp
 * This is a source code file of test_vproc_perspective.
 *
 */
 /*!
 * @example test_vproc_perspective_live.cpp
 * This is a source code file of test_vproc_perspective_live.
 *
 */
 /*!
 * @example test_vproc_cdist.cpp
 * This is a source code file of test_vproc_cdist.
 *
 */
 /*!
 * @example test_vproc_imhist.cpp
 * This is a source code file of test_vproc_imhist.
 *
 */
 /*!
 * @example test_vproc_imcvt.c
 * This is a source code file of test_vproc_imcvt.
 *
 */
 /*!
 * @example test_vproc_cvfilter.cpp
 * This is a source code file of test_vproc_cvfilter.
 *
 */
 /*!
 * @example test_vproc_morph.cpp
 * This is a source code file of test_vproc_morph.
 *
 */
 /*!
 * @example test_vproc_optlk.cpp
 * This is a source code file of test_vproc_optlk.
 *
 */
 /*!
 * @example test_vproc_optlk_flow_live.cpp
 * This is a source code file of test_vproc_optlk_flow_live.
 *
 */
 /*!
 * @example test_vproc_optlk_tracking_live.cpp
 * This is a source code file of test_vproc_optlk_tracking_live.
 *
 */
 /*!
 * @example test_vproc_edge_det.cpp
 * This is a source code file of test_vproc_edge_det.
 *
 */
 /*!
 * @example test_vproc_memcpy.c
 * This is a source code file of test_vproc_memcpy.
 *
 */
 /*!
 * @example test_vproc_memset.c
 * This is a source code file of test_vproc_memset.
 *
 */
 /*!
 * @example test_vproc_statistics.c
 * This is a source code file of test_vproc_statistics.
 *
 */
 /*!
 * @example test_vproc_warp.c
 * This is a source code file of test_vproc_warp.
 *
 */
 /*!
  * @example test_vproc_yuv2rgb.c
  * This is a source code file of test_vproc_yuv2rgb.
  *
  */
/*!
 * @example test_vproc_resize_mfd.c
 * This is a source code file of test_vproc_resize_mfd.
 *
 */
/*!
 * @example test_vproc_submean_mfd.c
 * This is a source code file of test_vproc_submean_mfd.
 *
 */
/*!
 * @example test_vproc_scale_mfd.c
 * This is a source code file of test_vproc_scale_mfd.
 *
 */
/*!
 * @example test_vproc_dtcvt_mfd.c
 * This is a source code file of test_vproc_dtcvt_mfd.
 *
 */
/*!
 * @example test_vproc_rotate_mfd.c
 * This is a source code file of test_vproc_rotate_mfd.
 *
 */
/*!
 * @example test_vproc_preproc_mfd.c
 * This is a source code file of test_vproc_preproc_mfd.
 *
 */
/*!
 * @example test_vproc_harris_mfd.cpp
 * This is a source code file of test_vproc_harris_mfd.
 *
 */
/*!
 * @example test_vproc_harris_live_mfd.cpp
 * This is a source code file of test_vproc_harris_live_mfd.
 *
 */
/*!
 * @example test_vproc_perspective_mfd.cpp
 * This is a source code file of test_vproc_perspective_mfd.
 *
 */
/*!
 * @example test_vproc_perspective_live_mfd.cpp
 * This is a source code file of test_vproc_perspective_live_mfd.
 *
 */
/*!
 * @example test_vproc_cdist_mfd.cpp
 * This is a source code file of test_vproc_cdist_mfd.
 *
 */
/*!
 * @example test_vproc_imhist_mfd.cpp
 * This is a source code file of test_vproc_imhist_mfd.
 *
 */
/*!
 * @example test_vproc_imcvt_mfd.c
 * This is a source code file of test_vproc_imcvt_mfd.
 *
 */
/*!
 * @example test_vproc_cvfilter_mfd.cpp
 * This is a source code file of test_vproc_cvfilter_mfd.
 *
 */
/*!
 * @example test_vproc_morph_mfd.cpp
 * This is a source code file of test_vproc_morph_mfd.
 *
 */
/*!
 * @example test_vproc_optlk_mfd.cpp
 * This is a source code file of test_vproc_optlk_mfd.
 *
 */
/*!
 * @example test_vproc_optlk_flow_live_mfd.cpp
 * This is a source code file of test_vproc_optlk_flow_live_mfd.
 *
 */
/*!
 * @example test_vproc_optlk_tracking_live_mfd.cpp
 * This is a source code file of test_vproc_optlk_tracking_live_mfd.
 *
 */
/*!
 * @example test_vproc_edge_det_mfd.cpp
 * This is a source code file of test_vproc_edge_det_mfd.
 *
 */
/*!
 * @example test_vproc_memcpy_mfd.c
 * This is a source code file of test_vproc_memcpy_mfd.
 *
 */
/*!
 * @example test_vproc_memset_mfd.c
 * This is a source code file of test_vproc_memset_mfd.
 *
 */
/*!
 * @example test_vproc_statistics_mfd.c
 * This is a source code file of test_vproc_statistics_mfd.
 *
 */
/*!
 * @example test_vproc_warp_mfd.c
 * This is a source code file of test_vproc_warp_mfd.
 *
 */
/*!
 * @example test_vproc_epnr.cpp
 * This is a source code file of test_vproc_epnr.
 *
 */
/*!
 * @example test_vproc_epnr_live.cpp
 * This is a source code file of test_vproc_epnr_live.
 *
 */
 /*!
  * @example test_vproc_alpha_blend.c
  * This is a source code file of test_vproc_alpha_blend.
  *
  */
 /*!
  * @example test_vproc_alpha_blend_mfd.c
  * This is a source code file of test_vproc_alpha_blend_mfd.
  *
  */
 /*!
  * @example test_vproc_abs.c
  * This is a source code file of test_vproc_abs.
  *
  */
 /*!
  * @example test_vproc_abs_mfd.c
  * This is a source code file of test_vproc_abs_mfd.
  *
  */
 /*!
  * @example test_vproc_rgb2yuv.c
  * This is a source code file of test_vproc_rgb2yuv.
  *
  */
 /*!
  * @example test_vproc_rgb2yuv_mfd.c
  * This is a source code file of test_vproc_rgb2yuv_mfd.
  *
  */
 /*!
  * @example test_vproc_transpose.c
  * This is a source code file of test_vproc_transpose.
  *
  */
 /*!
  * @example test_vproc_transpose_mfd.c
  * This is a source code file of test_vproc_transpose_mfd.
  *
  */
 /*!
  * @example test_vproc_bayer2bgr.cpp
  * This is a source code file of test_vproc_bayer2bgr.
  *
  */
 /*!
  * @example test_vproc_bayer2bgr_mfd.cpp
  * This is a source code file of test_vproc_bayer2bgr_mfd.
  *
  */
 /*!
  * @example test_vproc_cclb.cpp
  * This is a source code file of test_vproc_cclb.
  *
  */
 /*!
  * @example test_vproc_cclb_mfd.cpp
  * This is a source code file of test_vproc_cclb_mfd.
  *
  */
/*!
/*!
  * @example test_vproc_render3d_live.cpp
  * This is a source code file of test_vproc_render3d_live.
  *
  */
 /*!
  * @example test_vproc_bitwise.cpp
  * This is a source code file of test_vproc_bitwise.
  *
  */
 /*!
  * @example test_vproc_bitwise_mfd.cpp
  * This is a source code file of test_vproc_bitwise_mfd.
  *
  */
/*!
  * @example test_vproc_flatten.c
  * This is a source code file of test_vproc_flatten.
  *
  */
/*!
 * @defgroup vproc-api VProc Library API
 * @brief VProc Library API, in file vproc.h
 */
/*! @defgroup vproc-api-details VProc Library API details
 *  @ingroup vproc-api
 *  @brief VProc API details, in file vproc.h
 */
/*! @defgroup vproc-api-details-mfd VProc Library MFD API details
 *  @ingroup vproc-api
 *  @brief VProc MFD API details, in file vproc.h. This function is
 *         the same as the function which name without MFD. MFD means
 *         the memory physical address will be replaced by the memory file descriptor.
 */
/*! @defgroup vproc-helper VProc Library API helper
 *  @ingroup vproc-api
 *  @brief VProc Helper, in file vproc.h
 */
/*!
 * @file doc_lib_vfunc.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2020-06-30
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
 * @page page_lib_vfunc_doc VFUNC Library API
 *
 * @section vfunc_history 0. Revision History
 *  | Library Version |Updated Date     | Modification                 |
 *  | :---               | :--------------------------- |:----------------|
 *  | 0.0.1 |20230503         | Initial Version, Support 1) FEX, FMA, (Feature Points Extraction and Matching); 2) FFPYDLK  (Fast Feature points Pyramid LK Tracking)     |
 *
 * - - - -
 *
 * @section vfunc_introduction 1. Introduction
 * VFunc is a library of visual algorithms based on VProc and algorithmic logic. The performance is
 * boosted by utilizing Ambarella CVflow® chips and Arm® thread. <br>Currently, the VFunc supports CV2, CV22, CV25, CV5, and CV52 CVflow chips.
 * <br>
 * @image html vfunc_arch.png "Figure 3-1. Hierarchy of Libraries."
 * <br>
 * The VFunc functions are provided to the user as a prebuild library.
 * Follow the below commands to enable the library:
 * - For CV2x SDK 3.0 Amba build
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Prebuild  --->
 *              [*]   Configure Ambarella Vfunc library
 * @endcode
 * To verify the functions of the VFunc library, follow the commands below to build the unit tests.
 * The VFunc library is enabled when the unit tests are configured.
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Unit Test Configuration  --->
 *              [*]   Ambarella Private Linux Unit test configs  --->
 *                 [*]   Build CV unit tests  --->
 *                    [*]   Build vfunc algorithm unit test
 * @endcode
 * - For Cooper Amba build
 * @code {.c}
 * build # make menuconfig
 *    unit_test --->
 *        private --->
 *            cv-test (unit_test/private/cv_test/cavalry_v2) --->
 *                [*]   Build vproc algorithm unit tests
 * @endcode
 * - For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambaapp --->
 *        recipes-test --->
 *            cv-test (meta-ambaapp/recipes-test/cv-test) --->
 *                [*]   Build vproc algorithm unit tests
 * @endcode
 *
 * - - - -
 *
 * @section vfunc_library_example_usage 2. Example Usage
 *
 * @subsection vfunc_library_test_vfunc 2.1 VFunc Unit Test Application
 * Dozens of unit test applications are provided for VFunc library
 * verificaiton. Users can reference them as the sample code when
 * writing applications. Enable the Cavalry driver before running a
 * VFunc unit test with the command below.
 *
 * @code {.c}
 * board # modprobe cavalry
 * board # cavalry_load -f /lib/firmware/cavalry.bin -r
 * @endcode
 *
 * @subsubsection vfunc_library_test_vfunc_fma 2.1.1 test_vfunc_fma
 * This function consists of two sub-modules: feature extraction (FEX) and feature matching (FMA).
 * The sub-modules cowork together for the whole function.<br>
 * The following chart shows the process of FEX and FMA:
 * <br>
 * @image html Process_of_FEX_and_FMA.jpg "Figure 3-2. FEX and FMA Process."
 * <br>
 * FMA is based on hamming distance calculation; the size of the feature description is 256 binary bits, which is equal to 32 bytes.
 * The FEX outputs the feature point positions and descriptions. For each point in image #0, FMA outputs the corresponding point index in image #1 with the nearest distance.
 * The maximum feature points from FEX is 1024. FMA supports a maximum of 1024 matching pairs, which means 1024 points to 1024 points.
 * The table below shows the invariance features of FEX.
 * |     Invariance    | Status |
 * |------------------|-----|
 * |Rotation / angle invariance  | Supported|
 * |Luma invariance  | Supported|
 * |Scale invariance  | Slightly supported when the image scales in the range from ~80% to ~120%.|
 * |Deformation invariance  | Slightly supported|
 * |Blurred invariance  | Unsupported|
 *
 * test_vfunc_fma uses FEX to extract the feature points from two images,
 * and then FMA performs feature point matching.
 * The available options of test_vfunc_fma are as follows:
 * @verbatim
	-l --left_input			Path to the left input image. For example, -l left.jpg
	-r --right_input			Path to the right input image. For example, -r right.jpg
	-O --output				Path to output folder
	-s --resolution			Input resize resolution WxH.(Note: different width / height scale ratios will deform the rotated image; this will affect the matching result)
	-t --harris-threshold		Harris response threshold. For example, -t 0.001
	-n --max-harris_num		Maximum Harris point number. Maximum number of feature points is 1024
	-w --harris-nms-size		Set non-maximum suppression (NMS) window size; range is [7,64]
	-d --fma-dist-thresh		Matching distance threshold. Range is [0,256]; suggested range is [20,40]
	-o --angle-invariance		0: Angle variance. 1: Angle invariance
   @endverbatim
 *
 * One example is provided using the command below:
 * @code {.c}
 * board # test_vfunc_fma -l left.jpg -r right.jpg	-s 1280x720 -t 0.001 -n 1024 -w 25 -d 30 -o 1 -O /tmp
 * @endcode
 * The following picture shows the test result of FEX and FMA
 * @image html vfunc_fma_result.jpg "Figure 3-3. FEX and FMA Results."
 * <br>
 * @subsubsection vfunc_library_test_vfunc_fma_live 2.1.2 test_vfunc_fma_live
 * The test_vfunc_fma_live application matches feature points and displays the matching result via livestream.
 * It fetches the first frame as the reference frame, then extracts the reference feature points from the frame.
 * By continually extracting the new feature points from the new frames, this test matches the new points to the reference points.
 * The available test_vfunc_fma_live options are listed below:
 * @verbatim
	-s --resolution		 	Input resize resolution WxH
	-t --harris-threshold		Harris response threshold. For example, -t 0.001
	-n --max-harris-num		Maximum Harris point number. Maximum number of feature points is 1024
	-w --harris-nms-size		Set NMS window size, range is [7,64]
	-d --fma-dist-thresh		Matching distance threshold. Range is [0,256]; suggested range is [20,40]
	-m --run-mode				Run mode. 0: Continue mode. 1: Run-stop mode
	-o --angle-invariance		0: Angle variance. 1: Angle invariance
	-O --overlay-stream		Output stream ID. For example,  -O 0
   @endverbatim
 *
 * Below is an example to run FEX and FMA in live mode.
 * @code {.c}
 * board # test_vfunc_fma_live -s 1280x720 -t 0.001 -n 1024 -w 25 -d 30 -o 1 -m 0
 * @endcode
 * The following image shows a stereo slam demo, which primarily uses FEX, FMA from VFunc, and FBM from VProc.<br>
 * @image html fma_in_slam.gif "Figure 3-4. Using FMA in Stereo Slam."
 * <br>
 * @subsubsection vfunc_library_test_vfunc_ffpydlk_tracking 2.1.3 test_vfunc_ffpydlk_tracking
 * The test_vfunc_ffpydlk_tracking application tracks the feature points from image0 to image1,
 * and the tracking trajectory will be drawn to a result file.
 * The available options of test_vfunc_ffpydlk_tracking are as follows:
 * @verbatim
	-s --resolution		 			Input resize resolution WxH. For example, -s 720x640
	-l --left-input		 			Path to left input image. For example, -l left.jpg
	-r --right-input		 			Path to right input image. For example, -r right.jpg
	-t --opt-response-threshold 		Threshold of LK response. For example, -t 0.01
	-w --lk-win-size					LK window size. For example, set -w 11 for window size 11x11
	-p --opt-pyramid-number			Pyramid level number; pyramid number = level_num + 1. For example, -p 3
	-c --opt-pyramid-scale-factor		Pyramid down-scale factor; range is [0.5,0.9]. For example, -c 0.6
	-A --new-points-roi		 		Detection region of interest (ROI) of new Harris points (X#Y#W#H). For example, -A 320#180#320#320
	-d --harris-response-threshold 	Harris response threshold. For example, -d 0.01
	-n --harris-nms-size				Set NMS window size, range is [7,64]
   @endverbatim
 *
 * Follow the example to perform pyramid LK tracking in file mode.
 * @code {.c}
 * board # test_vfunc_ffpydlk_tracking -l 10.png  -r 11.png -s 1280x720 -t 0.005 -w 11 -p 4  -d 0.001 -n 13  -c 0.6 -A 0#0#1280#720
 * @endcode
 *
 * The following image shows the test result of ffpydlk.
 * @image html ffpydlk_in.jpg "Figure 3-5. The ffpydlk Input (the Right Image Shifts Right / Down from the Left Image)."
 * <br>
 * @image html ffpydlk_out.png "Figure 3-6. The ffpydlk Output."
 * <br>
 * @subsubsection vfunc_library_test_vfunc_ffpydlk_tracking_live 2.1.4 test_vfunc_ffpydlk_tracking_live
 * The test_vfunc_ffpydlk_tracking_live performs pyramid LK tracking in live mode;
 * the tracking trajectory will be drawn to the canvas in output stream.
 * The available test_vfunc_ffpydlk_tracking_live options are as follows:
 * @verbatim
	-s --resolution		 		Input resize resolution WxH. For example, -s 720x640
	-O --overlay-stream		 	output stream ID; for example, -O 0
	-t --opt-response-threshold 	LK response threshold. For example, -t 0.01
	-w --lk-win-size				LK window size. For example, set -w 11 for window size 11x11
	-p --opt-pyramid-number		Pyramid level number; pyramid number = level_num + 1. For example, -p 3
	-c --opt-pyramid-scale-factor	Pyramid down-scale factor; range is [0.5,0.9]. For example, -c 0.6
	-f --opt-run-per-frames		Run tracking per N frames; for example, -f 2
	-A --new-points-roi		 	Detection ROI of new Harris points (X#Y#W#H). For example, -A 320#180#320#320
	-d --harris-response-threshold Harris response threshold. For example, -d 0.01
	-n --harris-nms-size		 	Set NMS window size, range is [7,64]
	-o --tracking-min-num			Minimum tracking points; -o 20
   @endverbatim
 *
 * Use the command below to run test_vfunc_ffpydlk_tracking_live.
 * @code {.c}
 * board # test_vfunc_ffpydlk_tracking_live -s 1280x720 -t 0.0001 -w 11 -p 3  -f 1 -d 0.01 -n 48 -o 80 -c 0.6 -A 850#100#240#520 -O 0
 * @endcode
 * <br>
 * @image html ffpydlk_live.jpg "Figure 3-7. The ffpydlk Live Demo."
 * <br>
 *
 *
 * - - - -
 *
 * @section sec_vfunc 3. VFunc Performance
 * The table below shows the VFunc performance on CV2x and CV5x chips.
 * |     VFunc     |CV2 | CV22 | CV5 |
 * |------------------|-----|------|------|
 * |FEX (extract 200 points in 720p image <br>with / without rotation invariance)|~9 ms / ~7 ms|~10 ms / ~8 ms|~6 ms / ~5 ms|
 * |FMA (300-point pair matching)|~6 ms|~6 ms|~6 ms|
 * |FFPYDLK (track 200 points in 720p) |~7 ms|~7.5 ms|~5.5 ms|
 *
 * - - - -
 *
 * @section sec_vfunc_api 4. VFunc API
 * Visit the following link for details on application programming interface (API) functions.
 *      - @ref vfunc-api-details shows API lists.
 *      - @ref vfunc-helper shows related macros, enumerations, and structures.
 *
 * - - - -
 *
 * @section sec_vfunc_lic 5. License
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
 * @example test_vfunc_fma.cpp
 * This is a source code file of test_vfunc_fma.
 *
 */
 /*!
  * @example test_vfunc_fma_live.cpp
  * This is a source code file of test_vfunc_fma_live.
  *
  */
 /*!
 * @example test_vfunc_ffpydlk_tracking.cpp
 * This is a source code file of test_vfunc_ffpydlk_tracking.
 *
 */
 /*!
 * @example test_vfunc_ffpydlk_tracking_live.cpp
 * This is a source code file of test_vfunc_ffpydlk_tracking_live.
 *
 */
/*!
 * @defgroup vfunc-api VFunc Library API
 * @brief VFunc Library API, in file vfunc.h
 */
/*! @defgroup vfunc-api-details VFunc Library API details
 *  @ingroup vfunc-api
 *  @brief VFunc API details, in file vfunc.h
 */
/*! @defgroup vfunc-helper VFunc Library API helper
 *  @ingroup vfunc-api
 *  @brief VFunc Helper, in file vfunc.h
 */
/*!
 * @file doc_lib_vss.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2023-07-17
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
 * @page page_lib_vss_doc Video Sharing Service Library API
 *
 * @section vss_history 0. Revision History
 *
 * <table>
 * <caption id="vss_lib_rev_history"></caption>
 * <tr><th> Library Version	<th align="left"> Updated Date	<th align="left"> Modification
 * <tr><td> 0.0.1    <td>20230717    <td> Initial Version
 * </table>
 *
 * - - - -
 *
 * @section vss_intro 1. Video Sharing Service Introduction
 *
 * The video sharing service (VSS) is a library for user applications to publish and
 * subscribe to video frames and bitstreams with low latency. VSS is based on the
 * data distribution service (DDS). Based on the VSS library, the publisher service
 * application acquires video data, publishes it via DDS, and manages the
 * lifetime of the published data. User applications
 * can subscribe to video data and verify if it is expired
 * at any stage of data processing.
 * @image html vss_introduction.png "Figure 1-1. VSS Introduction."
 *
 * @par Advantages:
 * - VSS provides a method for data sharing without memory copy, of which the target
 * is to effectively save dynamic random-access memory (DRAM) bandwidth.
 * - Multiple user applications can subscribe to the same topic sharing the same video frame data.
 * - VSS offers the flexibility to change different DDS libraries, such as Cyclone DDS and FastDDS.
 *
 * @par Notes:
 * - VSS only supports manual feed mode (`manual_feed = 1` in the Lua script) for pyramid.
 *   For canvas, VSS does not support manual feed mode.
 * - The value of `zero_copy` in the Lua script should be set to 1. The
 *   function `zero_copy = 0` is implemented in the next stage.
 * - The option "--list-topics, -l" in the test application `test_vss_subscriber`
 *   is not currently supported; it will be supported after enabling the topic
 *   discovery feature in the upcoming Cyclone DDS library.
 * - Currently, only Cyclone DDS is available in the Ambarella software development kit (SDK).
 *   Ambarella will support more types of DDS in the future.
 * - The file save function in the test application `test_vss_subscriber` is an
 *   auxiliary function. Currently, only saving one YUV frame into file can be
 *   guarenteed (option: -c 1). When multiple YUV frames are captured, some succeeding
 *   frames may be lost due to the delay caused by saving the current frame to the file.
 * - The publish and subscribe functions for streams will be available at a later time.
 *
 * - - - -
 *
 * @section vss_lib_api 2. Video Sharing Service Library Application Programming Interface (API)
 * Refer to the following link for API function details.
 *      - @ref video-sharing-service-video-frame explains VSS API functions.
 *      - @ref video-sharing-service-utility explains VSS Utility API functions.
 *      - @ref video-sharing-service-struct-group shows VSS related structures.
 *      - @ref vss-config-parser explains VSS Configuration Parser API functions.
 *      - @ref vss-config-struct-group shows VSS Configuration Parser related structures.
 *
 * - - - -
 *
 * @section vss_usage 3. VSS Usage
 * When using the VSS library, the digital signal processor (DSP) must be in the
 * preview or encoding state, otherwise VSS will report errors.<br>
 * To enable VSS function and verify it, follow the steps below:
 * 1. Enable the VSS feature.
 * @code {.c}
 * build $ make menuconfig
 *         [*] Ambarella Package Configuration  --->
 *           [*]   Build Ambarella video_sharing_service
 * @endcode
 *   - If the multi-channel function is used, such as in the following CV72 example,
 *     the "Max VIN Channel Number" must be set in menuconfig.
 * @code {.c}
 * build $ make menuconfig
 *         [*] Ambarella Linux Configuration  --->
 *           [*]   Ambarella Private Drivers Configuration  --->
 *             [*]   Define Common Macros  --->
 *               (4)   Max VIN Channel Number
 * @endcode
 *
 * 2. Enter into the preview.<br>
 * The examples of the test commands are listed below.<br>
 *  - For CV22, the Lua script for the system resource settings can be found from
 *    <a href="scripts/cv22_vin0_1080p_linear.lua" target="_blank"><b>cv22_vin0_1080p_linear.lua</b></a>.
 *  @code
 *  board# init.sh --imx274_mipi
 *  board# test_aaa_service -a&
 *  board# test_encode --resource-cfg cv22_vin0_1080p_linear.lua --hdmi 1080p
 *  ...
 *  @endcode
 *
 *  - For CV5, the Lua script for system resource settings can be found from
 *    <a href="scripts/cv22_vin0_1080p_linear.lua" target="_blank"><b>cv5_vin0_1080p_linear.lua</b></a>.
 *  @code
 *  board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3
 *  board# test_aaa_service -a&
 *  board# test_encode --resource-cfg cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *  ...
 *  @endcode
 *
 *  - For CV72, the Lua script for system resource settings can be found from
 *    <a href="scripts/cv72_three_chan_single_sensor_1080p.lua" target="_blank"><b>cv72_three_chan_single_sensor_1080p.lua</b></a>.
 *  @code
 *  board# init.sh --na;modprobe imx274_mipi vinc_id=8
 *  board# test_aaa_service -a&
 *  board# test_encode --resource-cfg cv72_three_chan_single_sensor_1080p.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi_720p.lua
 *  ...
 *  @endcode
 *
 * 3. Change the VSS Lua script according to the canvas and pyramid settings in
 *   step 2.<br>
 *  - The VSS Lua script example for CV22 and CV5 can be found
 *    <a href="scripts/vss_cfg.lua" target="_blank"><b>here</b></a>.
 *  - The VSS Lua script example for CV72 can be found
 *    <a href="scripts/cv72_vss_cfg.lua" target="_blank"><b>here</b></a>.
 *
 * 4. Start the publisher daemon in one console.
 *  @code {.c}
 *  board # video_sharing_service_publisher
 *  ===============================
 *      l -- load configure from the specified file path
 *      a -- start all vss publisher(s)
 *      x -- stop all vss publisher(s)
 *      s -- start current vss publisher
 *      e -- stop current vss publisher
 *      d -- delete a vss publisher
 *      c -- set current vss publisher
 *      t -- list all vss publisher(s)
 *      p -- print current vss publisher info
 *      g -- change the log level
 *      q -- Quit
 *  ===============================
 *  @endcode
 *  Suggested steps:<br>
 *   - a. Load the VSS configuration; use "l" to load the Lua script first. If
 *        nothing is input, it will use the default script
 *        (`/usr/share/ambarella/vss/lua/vss_cfg.lua`).
 *   - b. Show all loaded topic names. Use "t" to show all topic names to be published.
 *        The initial publish states should be "stopped".
 *   - c. Start the publisher. Use option "a" to start all publishers, or
 *        "c -> s" to start one publisher.
 *   - d. Show all topic names again. Use "t" to show all publish topic names,
 *        and the publish states should be "running".
 *   @code
 *   ======vss_publisher_info=======
 *   ID: 1 state: running  topic_name: yuv_canvas_0_chan_map_1_yuv420_1920x1080p30
 *   ID: 2 state: running  topic_name: yuv_multi_canvas_1_chan_map_1_yuv420_720x480p30_canvas_2_chan_map_1_yuv420_1920x1080p30
 *   ID: 3 state: running  topic_name: yuv_chan0_srcbuf_4_scale_0_layer0_1280x720_layer1_908x510_layer2_640x360_layer3_456x256_layer4_320x180_layer5_228x128p3
 *   ...
 *   @endcode
 *
 * 5. Start the subscriber application `test_vss_subscriber` in another console
 *    to subscribe to a topic which is in a running state listed in step 4 and sub-step d.
 *  @code
 *  board # test_vss_subscriber -t yuv_canvas_0_chan_map_1_yuv420_1920x1080p30
 *  seq: 10077, 1920x1080, format: YUV420, lifetime: 100, pts: 32834436, zero_copy: 1, y_addr: 0x7f73bde780, uv_addr: 0x7f73def380, latency: 1.31
 *  seq: 10078, 1920x1080, format: YUV420, lifetime: 100, pts: 32837436, zero_copy: 1, y_addr: 0x7f73efd380, uv_addr: 0x7f7410df80, latency: 0.28
 *  seq: 10079, 1920x1080, format: YUV420, lifetime: 100, pts: 32840436, zero_copy: 1, y_addr: 0x7f7421bf80, uv_addr: 0x7f7442cb80, latency: 0.27
 *  seq: 10080, 1920x1080, format: YUV420, lifetime: 100, pts: 32843436, zero_copy: 1, y_addr: 0x7f738bfb80, uv_addr: 0x7f73ad0780, latency: 0.16
 *  seq: 10081, 1920x1080, format: YUV420, lifetime: 100, pts: 32846435, zero_copy: 1, y_addr: 0x7f73bde780, uv_addr: 0x7f73def380, latency: 0.16
 *  seq: 10082, 1920x1080, format: YUV420, lifetime: 100, pts: 32849436, zero_copy: 1, y_addr: 0x7f73efd380, uv_addr: 0x7f7410df80, latency: 0.20
 *  ...
 *  @endcode
 *
 * - - - -
 *
 * @section dds_brief 4. Data Distribution Service Introduction
 * The "data distribution service for real-time systems" is an open
 * standard from the Object Management Group (OMG). This standard is the
 * specification of API of a publish-subscribe communication middleware
 * for distributed systems. Distributed applications using DDS can publish or
 * subscribe to "topics" of information and use a rich set of quality-of-service
 * parameters to set up different aspects of communication, such as reliability,
 * persistence, redundancy, lifespan, transport settings, resources, and more.
 *
 * @image html dds_introduction.png "Figure 3-1. DSS Introduction."
 *
 * - - - -
 *
 * @section pm_license 5. License
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
 *
 * @defgroup video-sharing-service-video-frame Video Sharing Service Library API
 * @brief Video Sharing Service Library API, in video_sharing_service_if.h
 *
 * @defgroup video-sharing-service-utility Video Sharing Service Library Utility API
 * @brief Video Sharing Service Library Utility API, in video_sharing_service_if.h
 *
 * @defgroup video-sharing-service-struct-group Video Sharing Service Structure
 * @brief Video Sharing Service Structure, in file vss_types.h
 *
 * @defgroup vss-config-parser Video Sharing Service Configuration Parser API
 * @brief Video Sharing Service Configuration Parser API, in file vss_cfg_parser.h
 *
 * @defgroup vss-config-struct-group Video Sharing Service Configuration Parser Structure
 * @brief Video Sharing Service Configuration Parser Structure, in file vss_cfg_parser.h
 *
 */
/*!
 * @file doc_lib_pm.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2022-12-06
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
 * @page page_lib_pm_doc PrivacyMask Library API
 *
 * @section privacymask_history 0. Revision History
 *
 * <table>
 * <caption id="privacymask_lib_rev_history"></caption>
 * <tr><th> Library Version	<th align="left"> Updated Date	<th align="left"> Modification
 * <tr><td> 0.0.2    <td>20221230    <td> Initial Version
 * </table>
 *
 * - - - -
 *
 * @section privacymask_intro 1. Introduction
 *
 * The privacy mask (PM) library provides a group of flexible and friendly application programming interfaces(APIs) for
 * users to easily integrate the PM feature into their application. It supports filling or clearing triangular, rectangular,
 * quadrangular, circular privacy masks. It also provides some low-level APIs for users to implment
 * privacy masks in other shapes.
 * @note
 * The PM library can only support single-color PMs, and the library can only be used by single-user applications.
 *
 * - - - -
 *
 * @section pm_lib_process 2. Privacy Mask Usage Guide
 * - For CV2x, the source code of the PM library can be found under the path:
 * `ambarella/packages/iav_utils/arch_v5/privacymask`.</br>
 * - For CV5x, the source code of the PM library can be found under the path:
 * `ambarella/packages/iav_utils/arch_v6/privacymask`.</br>
 * Usage of the PM library includes the following steps:
 *
 * @image html privacymask_usage_process.jpg "Figure 2-1. Usage Process."
 *
 * (1) pm_get_sys_info() implementation flow
 *
 * The pm_get_sys_info() implementation flow is as follows.
 * @image html pm_get_sys_info.jpg "Figure 2-2. PM Get System Information Flow."
 *
 * (2) pm_lib_init() implementation flow
 *
 * The pm_lib_init() implementation flow is as follows.
 * @image html pm_lib_init.jpg "Figure 2-3. PM Library Initialization Flow."
 *
 * The following tables list the details of key structures.
 * @par Table 2-1. Struct pm_usr_cfg.
 * <table>
 * <caption id="pm_usr_cfg"></caption>
 * <tr><th align="left">Item<th align="left">Description
 * <tr><td><B>use_warp_table_chan_map</B><td>Warp enable per channel's map
 * <tr><td><B>loop_step</B><td>Per pixel PM loop step
 * </table>
 *
 * @par Table 2-2. Struct pm_sys_info.
 * <table>
 * <caption id="pm_sys_info"></caption>
 * <tr><th align="left">Item<th align="left">Description
 * <tr><td><B>channel_num</B><td>Channel number in case of system
 * <tr><td><B>enc_mode</B><td>Current digital signal processor (DSP) encoding mode
 * <tr><td><B>mask_info[IAV_MAX_CHANNEL_NUM]</B><td>Mask information per channel
 * <tr><td><B>pm_domain_size[IAV_MAX_CHANNEL_NUM]</B><td>PM domain size per channel
 * <tr><td><B>main_domain_size[IAV_MAX_CHANNEL_NUM]</B><td>Main domain size per channel
 * </table>
 *
 * @par  Table 2-3.Struct pm_chan_info.
 * <table>
 * <caption id="pm_chan_info"></caption>
 * <tr><th align="left">Item<th align="left">Description
 * <tr><td><B>pm_virt_addr</B><td>Mask buffer virtual address per channel
 * <tr><td><B>pm_mem_size</B><td>Mask buffer size per channel
 * <tr><td><B>vin_info</B><td>Video input (VIN) configuration
 * <tr><td><B>main_input_win</B><td>Main buffer window configuration
 * <tr><td><B>width_scaler</B><td>VIN width scaler ratio for per channel
 * <tr><td><B>height_scaler</B><td>VIN height scaler ratio for per channel
 * <tr><td><B>input_width_scaler</B><td>Main buffer input window width scaler ratio for per channel
 * <tr><td><B>input_height_scaler</B><td>Main buffer input window height scaler ratio for per channel
 * <tr><td><B>rotate_flip</B><td>Horizontal flip, vertical flip, and rotate flag
 * </table>
 *
 * (3) pm_get_cfg() implementation flow
 *
 * - pm_get_cfg() obtains the PM configuration, virtual address, and size of the PM buffer.
 *
 * (4) PM fill shape implementation flow
 *
 * The PM library can support filling or clearing triangular, rectangular, quadrangular, and circular PMs.
 * It can also support filling frame border artifact based on mask YUV when using LDC case.
 * The following table details functions in pm fill shape:
 * @par  Table 2-4. PM Fill Function.
 * <table>
 * <caption id="fill function"></caption>
 * <tr><th align="left">Function<th align="left">Description
 * <tr><td>int pm_fill_rect(u8 chan_id, struct iav_rect \*pm_rect, u8 pm_remove);<td>Fill rectangle mask
 * <tr><td>int pm_fill_circle(u8 chan_id, struct iav_circle \*circle, u8 pm_remove);<td>Fill circle mask
 * <tr><td>int pm_fill_polygon(u8 chan_id, struct iav_polygon \*polygon, u8 pm_remove);<td>Fill polygon mask
 * <tr><td>int pm_fill_frame_border_by_mask(u8 chan_id, u8 *luma_data);<td>Fill frame border based on mask frame
 * </table>
 *
 * The parameters are explained as follows:
 * @code
 * chan_id -> mask channel
 * pm_remove -> 0: fill, 1: clear
 *
 * struct iav_rect {
 *	u32 x; //!< Offset X
 *	u32 y; //!< Offset Y
 *	u32 width; //!< Width
 *	u32 height; //!< Height
 * };
 *
 * struct iav_circle {
 *	u16 center_x; //!< Circle Center Offset X
 *	u16 center_y; //!< Circle Center Offset Y
 *	u16 radius; //!< Circle Radius
 *	u16 reserved;
 * };
 *
 * struct iav_polygon {
 *	u8 vertice_num; //!< Number of vertices
 *	u8 reserved[3];
 *	struct iav_point vertex[4]; //!< Vertex coordinates
 * };
 * @endcode
 *
 * (5) pm_insert(), pm_apply(), and pm_clear() implementation flow
 * - pm_insert(): Update the current channel's PM configuration to the image audio video(IAV) driver.
 * Before calling pm_insert(), users can call pm_get_cfg() to get current PM configuration. PM color
 * can be set through configuring Y, U, and V. Note that each time, only one color can be used for
 * all inserted PMs. The PM color is set to black by default.<br>
 * - pm_apply_cfg(): Apply all channel's PM configuration into the DSP.<br>
 * - pm_clear(): Clear all inserted PMs.
 *
 * (6) PM domain convert APIs
 * @par  Table 2-5. PM Convert APIs.
 * <table>
 * <caption id="convet function"></caption>
 * <tr><th align="left">Function<th align="left">Description
 * <tr><td>void pm_rect_to_pm_domain(u8 chan_id, struct iav_rect \*pm_rect);<td>Converts PM rectangular coordinate from main domain to pm domain
 * <tr><td>void pm_point_to_pm_domain(u8 chan_id, struct iav_point \*point);<td>Converts PM point coordinate from main domain to pm domain
 * <tr><td>struct iav_point pm_warp_map_to_point(u8 chan_id, struct iav_point point_in);<td>Converts PM point coordinate from main domain to warp domain
 * </table>
 *
 * For more details about the main domain and PM domain, users can can refer to @ref section_pm "1. Privacy Mask".
 *
 * - - - -
 *
 * @section pm_example 3. Privacy Mask Examples
 *
 * For PM examples, refer to @ref section_sc_pm_examples "2. Single-Color Privacy Mask Examples".
 *
 * - - - -
 *
 * @section pm_lib_api 4. Privacy Mask Library API
 * Refer to the following link for API function details.
 *      - @ref PM_FUNCTION_GROUP explains API functions.
 *      - @ref PM_STRUCT_GROUP shows related structures.
 *
 * - - - -
 *
 * @section pm_license 5. License
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
 */

 /*!
 * @defgroup PM_FUNCTION_GROUP Privacy Mask Library API
 * @brief Privacy Mask Library API, in file lib_pm.h
 */
/*!
 * @defgroup PM_STRUCT_GROUP Privacy Mask Structure
 * @brief Privacy Mask Structure, in file lib_pm.h.
 *//*!
 * @file doc_lib_vsrc_guard.h
 * @brief This is a .h file for doxygen document system
 * @version 0.1
 * @date 2023-07-17
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
 * @page page_lib_vg_doc Vsrc Guard Library API
 *
 * @section vg_history 0. Revision History
 *
 * <table>
 * <caption id="vg_lib_rev_history"></caption>
 * <tr><th> Library Version	<th align="left"> Updated Date	<th align="left"> Modification
 * <tr><td> 0.0.1    <td>20240112    <td> Initial Version
 * </table>
 *
 * @section vg_lib 1. VSRC Guard Library
 *
 * @subsection vg_intro 1.1 VSRC Guard Library Introduction
 *
 * The video source (VSRC) guard (VG) library provides user applications with the ability
 * to subscribe to sensor status. The VG library is based on the data
 * distribution service (DDS). Based on the VSRC guard library, the publisher service
 * application acquires video data, publishes it via DDS, and manages the lifetime of
 * the published data. User applications can subscribe to video data and verify if it is
 * expired at any stage of data processing, and then restore the sensor to its normal state.<br>
 * Refer to @ref dds_brief "Data Distribution Service Introduction" for more information about DDS.
 *
 * @image html vg_lib.png "Figure 1-1. VG library Introduction."
 *
 * @subsection vg_lib_api 1.2 VSRC Guard Library Application Programming Interface (API)
 *
 * Refer to the following links for API function details:
 *      - @ref VSRC_GUARD_FUNCTION_GROUP explains VG API functions
 *      - @ref VSRC_GUARD_STRUCT_GROUP shows structures related to the VG library
 *
 * Internal description of each API:
 * @par lib_vg_init
 * @image html vg_init.png "Figure 1-2. lib_vg_init Introduction."
 *
 * @par lib_vg_deinit
 * @image html vg_deinit.png "Figure 1-3. lib_vg_deinit Introduction."
 *
 * @par lib_vg_start
 * @image html vg_start.png "Figure 1-4. lib_vg_start Introduction."
 *
 * @par lib_vg_stop
 * @image html vg_stop.png "Figure 1-5. lib_vg_stop Introduction."
 *
 * @subsection vg_lib_usage 1.3 VSRC Guard Library Usage
 * If users are required to use this library in code, they must activate "Build Ambarella
 * IAV utils VSRC GUARD library" in `make menuconfig` to compile it.
 *
 * - For CV2x / CV5x / CV72 Amba build:
 * @code
 * build $ make menuconfig
 *   [*] Ambarella Package Configuration  --->
 *    [*]   Build Ambarella IAV utils VSRC GUARD library
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *   packages  --->
 *		iav_utils  --->
 *       [*] libiav-vsrc-guard (packages/iav_utils/dsp_v5/lib_vsrc_guard)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *   meta-ambalib  --->
 *      recipes-video  --->
 *          [*] libiav-vsrc-guard (meta-ambalib/recipes-video/libiav-vsrc-guard)
 * @endcode
 *
 * - - - -
 *
 * @section vg_service 2. VSRC Guard Service
 *
 * @subsection vg_service_intro 2.1 VSRC Guard Service Introduction
 *
 * The application `vsrc_guard_service` is an upper-layer application for the VG library.
 * In order to use the VG library more efficiently, `vsrc_guard_service`
 * provides the sample code for calling the associated APIs. The application can revert
 * the state of the sensor based on the information subscribed by VG library.
 *
 * The following are the main functional interfaces of the application and its workflow.
 *
 * @image html vg_service_api.png "Figure 2-1. VG Service API."
 *
 * @image html vg_service_flow.png "Figure 2-2. VG Service Workflow."
 *
 * @subsection vg_service_usage 2.2 VSRC Guard Service Usage
 *
 * The `vsrc_guard_service` depends on VG library and must be configured before continuing when users
 * enable `libiav-vsrc-guard` according to @ref vg_lib_usage "VSRC Guard Library Usage".
 * The `vsrc_guard_service` runs in the background when the system is booted up.
 *
 * - For CV2x / CV5x / CV72 Amba build:
 * @code
 * build $ make menuconfig
 *   [*] Ambarella Package Configuration  --->
 *   [*]   Build Ambarella IAV utils VSRC GUARD library
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 *   packages  --->
 *		iav_utils  --->
 *       [*] libiav-vsrc-guard (packages/iav_utils/dsp_v5/lib_vsrc_guard)
 *       [*] vsrc-guard-service (packages/iav_utils/dsp_v6/service_vsrc_guard)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build # make menuconfig
 *   meta-ambalib  --->
 *      recipes-video  --->
 *          [*] libiav-vsrc-guard (meta-ambalib/recipes-video/libiav-vsrc-guard)
 *          [*] vsrc-guard-service (meta-ambalib/recipes-video/vsrc-guard-service)
 * @endcode
 *
 * @subsection vg_service_effect 2.3 VSRC Guard Service Application Notes
 *
 * Due to the variety of sensors and serializers / deserializers (SERDES) and different connection scenarios between the sensor and SERDES,
 * the VSRC guard service functions with the supportability scope below:
 *
 * <table>
 * <caption id="vg_service_support_scope">Table 5-1. Vsrc Guard Service Support Scope.</caption>
 * <tr><th> Case <th> Subscribe to Topics with Abnormal Sensor Status <th> Sensor / SERDES Recovery
 * <tr><td align="center"> Multiple sensors without SERDES
 *     <td> Supported
 *     <td> Supported
 * <tr><td align="center"> Multiple sensors and SERDES (sensor and SERDES in one->one connection)
 *     <td> Supported
 *     <td> Supported
 * <tr><td align="center"> Multiple sensors and SERDES (sensor and SERDES in multiple->one connection)
 *     <td> Supported
 *     <td> Not supported
 * </table>
 *
 * @subsection vg_service_case 2.4 Example Cases
 *
 * @par One Sensor with One SERDES
 * For CV2, the Lua script for the system resource settings can be found at
 * <a href="scripts/cv2_vin0_1920x1200_linear.lua" target="_blank"><b>cv2_vin0_1920x1200_linear.lua</b></a>.
 * @code {.c}
 * board# init.sh --na
 * board# modprobe max9296 id=0x01 vinc_id=0x0 gmsl_mode=3 mfp4_clk=1 sen_rst_gpio=0
 * board# modprobe ox03c10_mipi_brg
 * board# test_aaa_service -a &
 * board# vsrc_guard_service &
 * board# test_encode --resource-cfg cv2_vin0_1920x1200_linear.lua --hdmi 1080p --vsync-detect-disable 0
 * @endcode
 *
 * For CV5x / CV72:
 * @code {.c}
 * board# init.sh --na
 * board# modprobe max9296 id=0x01
 * board# modprobe imx390_mipi_brg
 * board# vsrc_guard_service &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vsync-detect-disable 0    // For CV5
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vsync-detect-disable 0)    // For CV72
 * @endcode
 *
 * @par Multiple Sensors with Multiple SERDES (One-One Map)
 * For CV2:
 * @code {.c}
 * board# init.sh --na
 * board# modprobe max9296 id=0x0101 vinc_id=0x20
 * board# test_aaa_service -a &
 * board# modprobe os08a10_mipi_brg fsync=1
 * board# vsrc_guard_service &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv2_vin0_1_1080p_linear --hdmi 1080p --vsync-detect-disable 0
 * @endcode
 *
 * For CV5x / CV72:
 * @code {.c}
 * board# init.sh --na
 * board# modprobe max9296 id=0x0101
 * board# modprobe imx390_mipi_brg fsync=1
 * board# vsrc_guard_service &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vsync-detect-disable 0    // For CV5
 * (Or board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv72_vin0_1_4k_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua --vsync-detect-disable 0)    // For CV72
 * @endcode
 *
 * Users can simulate the sensor-broken situation by entering the command `test_vin_cap -p `vin-id``
 * to verify this function. The `vsrc_guard_service` started at the command line outputs the following
 * printout when the sensor is restored successfully:
 * @code {.c}
 * Start to restore vsrc[0] vin_mode 0x28 and hdr_mode 0.
 * Start to restore vin frame rate 17066667.
 * Power off vsrc[0].
 * Succeed to restore vsrc[0] vin_mode 0x28 and hdr_mode 0.
 * Succeed to restore vin frame rate 17066667.
 * @endcode
 *
 * @note
 * In order for `vsrc_guard_service` to function properly, `vsync-detect-disable` must be set to 0.<br>
 * The `vsrc_guard_service` runs in the background by default, and the cases above demonstrate how to manually start the process.
 *
 * - - - -
 *
 * @section vg_license 3. License
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
 *
 * @defgroup VSRC_GUARD_FUNCTION_GROUP Vsrc Guard Library API
 * @brief Vsrc Guard Library API, in lib_vsrc_guard.h
 *
 * @defgroup VSRC_GUARD_STRUCT_GROUP Vsrc Guard Library Structure
 * @brief Vsrc Guard Library Structure, in lib_vsrc_guard.h
 *
 */
