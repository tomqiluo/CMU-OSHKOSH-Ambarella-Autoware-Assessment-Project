/*!
 * @file doc_apps_acc_ctrl_page.h
 * @brief
 * @version 1.0
 * @date 2022-07-29
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
 * @page acc_ctrl_page Access Control Camera
 *
 * @section acc_ctrl_history 0. Revision History
 * <table>
 * <caption id="acc_ctrl_history_table"></caption>
 * <tr><th> Updated Date              <th align="left"> Modification
 * <tr><td> 20220815                  <td> Initial Version
 * </table>
 *
 * - - - -
 *
 * @section acc_ctrl_ov 1. Overview
 * This document introduces Ambarella access control applications and provides
 * details of the reference design for the Ambarella CV2x system on chip (SoC).
 * <br>
 *
 * Users are encouraged to proceed sequentially through this guide (beginning
 * with hardware setup for their particular chip), and become familiar
 * with the system requirements, software, and features included in the software
 * development kit (SDK).
 *
 * Using the package contents and this document, customers can set up a demo to
 * test a working procedure for their product. Because customer product
 * requirements may vary, this document provides basic framework and sample
 * codes as references for users to design their customized products.
 *
 * The access control evaluation kit (EVK) is a reference design platform based
 * on the Ambarella CV2x computer vision (CV) SoC. Designed for
 * three-dimensional sensing with the structured-light module, it is capable of
 * generating disparity images, depth images, and point cloud data for biometric
 * identification.
 *
 * Additionally, the access control EVK serves as a reference development
 * platform on which Ambarella customers can build their own product / hardware
 * designs and use as a software development / prototype platform. The final
 * products possess unique requirements, ranging from (but not limited to) the
 * field of view (FoV) of the lens used, the baseline and structured-light
 * module design (thus, the operating range), the liveness / anti-spoofing
 * algorithms based on depth information, and more.
 *
 * @note
 * This kit is not intended to provide the following:
 * - A turnkey solution
 * - Demo applications for production purposes
 * - Security camera / product application-level software or capabilities
 * - Liveness algorithms, and more for production purposes
 *
 * <table>
 * <caption id="acc_ctrl_feature_table">Features of Access Control Demo</caption>
 * <tr><th> Feature                     <th align="center" width="150px"> Demo Only  <th align="center" width="150px"> SDK Support
 * <tr><td> Generate RGB image          <td align="center"> YES                      <td align="center"> YES
 * <tr><td> Generate IR image           <td align="center"> YES                      <td align="center"> YES
 * <tr><td> Generate depth image        <td align="center"> YES                      <td align="center"> NO
 * <tr><td> Generate point cloud data   <td align="center"> YES                      <td align="center"> NO
 * <tr><td> Face detection / face recognition (FDFR) <td align="center"> YES                      <td align="center"> NO
 * <tr><td> Liveness detection          <td align="center"> YES                      <td align="center"> NO
 * <tr><td> Detection range (cm)        <td align="center"> YES                      <td align="center"> /
 * </table>
 *
 * @subsection acc_ctrl_evk_pkg 1.1 EVK Package
 * The CV series of the Flexible Linux Evaluation Kit includes the following
 * hardware and accessories. If any of the following components are missing
 * from the EVK package, contact the Ambarella support team for assistance.
 * | SDK Components      | Descriptions |
 * | ------------------- | ------------ |
 * | EVK boards          | The board armed with an Ambarella CV2x system on chip and a structured-light projector module |
 * | Cables              | Micro USB cable |
 * | EVK Firmware        | The firmware in the folder `binary/` that is upgraded to the EVK board |
 * | Install Program     | Tools in the folder `Tools/` used for evaluation, including for the AmbaUSB and the VLC player |
 * | Unit test programs  | The unit test applications that enable users to evaluate features using commands from the command line interface |
 *
 * @subsection acc_ctrl_pc_req 1.2 PC Requirement
 * A PC connected to the internet is required for downloading the SDK and / or
 * upgrading the firmware. For further details on upgrading the firmware,
 * refer to the @ref quick_start_guide.
 *
 * The PC must be equipped with the following:
 * | Items            | Requirements |
 * | ---------------- | ------------ |
 * | CPU              | Intel® i7 or higher grade |
 * | Memory           | 8 GB system memory or more |
 * | Hard disk        | 120 GB or more |
 * | Video card       | 3D hardware accelerator card required―100% DirectX 9.0c compatible. NVIDIA® GeForce GT520 or above to ensure the full frame rate of the HD playback |
 * | Monitor          | 24-inch LCD or larger with a digital visual interface (DVI) input. The Dell UltraSharp 2709W (VA panel) is preferred. |
 * | Ethernet card    | 1000 Mbps (adaptive) |
 * | Operating system | Windows 7/8 64-bit or Ubuntu 18.04 LTS 64-bit |
 * | Virtual machine  | Oracle VirtualBox 5.0.32 or later |
 *
 * @subsection acc_ctrl_accuracy 1.3 Detection Range and Accuracy
 * The detection range and accuracy of the structured-light module depends on
 * the baseline, focal length, sensor pixel size, infra-red (IR) filter
 * performance, structured-light strength, and pattern density, as well as the
 * IR illumination interference.
 *
 * For reference, @ref cv25m_janus_page "CV25M Janus EVK" uses a
 * <b>4-cm baseline</b> that ensures a 0.3-1.5 m depth generation range and a
 * liveness detection range indoors.
 *
 * @ref cv22_vision_lus_page "CV22 Vision+ EVK" uses a <b>5-cm baseline</b>
 * that allows for a 0.3-5 m depth generation range and a 0.3-1.5 m liveness
 * detection range indoors.
 *
 * When outdoors, sunlight exposure and restrictions from the structured-light
 * strength and shutter time result in a narrow detection range of 0.3-1.0 m or
 * greater. Additionally, depth information may be limited or non-existent if
 * intense sunlight shines directly on the subject's face. Using increased
 * structured-light strength can optimize performance, but because results
 * can be limited by the environment, users must first define the scope of their
 * product.
 *
 * The following images are examples of both valid and invalid depth image
 * information in the outdoor test environment.
 *
 * @image html acc_ctrl_valid_depth.png "Figure 1-1. Valid Depth Image Information (Outdoor: 5000 LUX)."
 * <br>
 * @image html acc_ctrl_invalid_depth.png "Figure 1-2. Invalid Depth Image Information (Outdoor: Sunlight on Face)."
 * <br>
 *
 * @subsection acc_ctrl_depth_gen 1.4 Depth Generation
 * The Ambarella SDK includes two depth generation algorithms. The first is
 * Blade Runner, and the other is Fast Block Match. Blade Runner is a CPU
 * intensive algorithm and its calculation relies only on CPU. Fast Block Match
 * is a Vector processor (VP) intensive algorithm, and most of its calculation
 * relies on VP.
 *
 * The following table provides the performance of the depth map calculations,
 * CPU usages, and VP usages at various resolutions. The value set in each cell
 * presents the time cost for the depth map calculation, the CPU usage
 * percentage, and VP usage percentage.
 *
 * @note
 * - EVK is facing a blank wall during the tests.
 * - CV25M Janus uses the CV25S55M clock, and CV22 Vision+ uses the CV22S66
 *   clock.
 * - CV25M Janus uses the 270p and 1080p reference YUV, while CV22 Vision+
 *   uses the 480x376 and 1280x1000 reference YUV.
 * - CPU usage is measured in one-second intervals; it refers to average CPU
 *   usage within each second.
 * - In typical use cases, a depth map is generated for the facial area only,
 *   which is much smaller than the entire frame size. Consequently, the depth
 *   map calculation time is reduced dramatically.
 *
 * <table>
 * <caption id="acc_ctrl_blade_runner">Blade Runner Depth Map Generation Time and Average CPU Usage.</caption>
 * <tr><th width="200px">  <th align="center" width="200px"> 480x270          <th align="center" width="200px"> 1280x720         <th align="center" width="200px"> 480x376         <th align="center" width="200px"> 1280x1000
 * <tr><th> CV25M Janus    <td align="center"> 122 ms<br> 20%(CPU)<br> 0%(VP) <td align="center"> 678 ms<br> 65%(CPU)<br> 0%(VP) <td align="center"> \                             <td align="center"> \
 * <tr><th> CV22 Vision+   <td align="center"> \                              <td align="center"> \                              <td align="center"> 119 ms<br> 14%(CPU)<br> 0%(VP) <td align="center"> 820 ms<br> 60%(CPU)<br> 0%(VP)
 * </table>
 *
 * <table>
 * <caption id="acc_ctrl_fbm">Fast Block Match Depth Map Generation Time and Average CPU Usage.</caption>
 * <tr><th width="200px">  <th align="center" width="200px"> 480x270     <th align="center" width="200px"> 1280x720      <th align="center" width="200px"> 480x376  <th align="center" width="200px"> 1280x1000
 * <tr><th> CV25M Janus    <td align="center"> \                         <td align="center"> 239 ms<br> 1%(CPU) 83%(VP)   <td align="center"> \                      <td align="center"> \
 * <tr><th> CV22 Vision+   <td align="center"> \                         <td align="center"> 120 ms<br> 1%(CPU) 81.5%(VP) <td align="center"> \                      <td align="center"> \
 * </table>
 *
 * The low-resolution reference YUV must not be used in production, as it will
 * yield a lower-quality depth map. The system must instead use the
 * high-resolution image with the region of interest (ROI) for the depth map
 * creation area.
 *
 * @subsection acc_ctrl_liveness_det 1.5 Liveness Detection
 * The table for liveness detection accuracy provides the performance of the
 * liveness detection library. TP, TN, FP, and FN seen below stand for true
 * positives, true negatives, false positives, and false negatives.
 *
 * <table>
 * <caption>Livenes Detection Accuracy - Version 1.0.0</caption>
 * <tr><th width="200px">  <th align="center" width="300px"> Formula     <th align="center" width="300px"> Result
 * <tr><th> Recall         <td align="center"> TP/(TP+FN)                <td align="center"> 0.9444
 * <tr><th> Precision      <td align="center"> TP/(TP+FP)                <td align="center"> 0.9639
 * <tr><th> Accuracy       <td align="center"> (TP+TN)/(TP+TN+FN+FP)     <td align="center"> 0.9695
 * </table>
 *
 * - - - -
 *
 * @section acc_ctrl_demo 2. Demo Application
 * This chapter provides details on setting up the building environment and
 * running the access control EVK demos.
 *
 * @subsection acc_ctrl_bulid_image 2.1 Build Image for Access Control EVK
 * If the user does not possess an SDK, skip this section and proceed directly
 * to Section @ref acc_ctrl_initialize.
 *
 * Refer to the <em>CV2x Linux SDK Release Notes</em> document for information
 * relating to the Toolchain and other software.
 *
 * To build an image for the access control EVK:
 * - Extract the latest access control SDK patch.
 * - Refer to the readme.txt file for the complete build process.
 *
 * For further details, refer to @ref ov_code_build.
 *
 * @subsection acc_ctrl_initialize 2.2 Initialize the System and Video Pipeline
 * This section details the process for generating the demo scripts for the
 * access control EVK boards.
 * -# Check the module ID on the access control EVK’s sensor module or acrylic
 *    mounting support (Note that this is not the ID found on the main board).
 *    Each sensor module has a unique ID, such as H1912060001 or H210615A001.
 * -# Verify that the configuration file, warp table, and reference data are
 *    ready; the default path is `/usr/share/ambarella/calib_mono`.<br>
 *    The `board_config` file defines all user configuration settings for
 *    the access control demos. The `warp_<resolution>.bin` is the warp table,
 *    and the `ref_<resolution>.yuv` files are the structured-light reference
 *    data.
 *    @note
 *    Users must back up the `calib_mono` folder before flashing a new firmware
 *    to the access control board. If there are any problems, contact the
 *    Ambarella support team for assistance.

 *    The `board_config` file can be generated and initialized by the
 *    `gen_board_config.sh` script. By changing the `CHANNEL_AMOUNT` and
 *    `FRAME_RATIO`, users can enable / disable the IR LED channel and adjust the
 *    frequency of the frames with the structured-light pattern. More details on
 *    the parameters in the `board_config` can be found in the Section
 *    @ref acc_ctrl_board_config.
 *    @code {.c}
 *    board # gen_board_config.sh /usr/share/ambarella/calib_mono <module ID>
 *    @endcode
 *
 * -# Run `quick_ipc_for_access_control.sh` to initialize the stream. The demo
 *    applications will generate under /tmp/run_ipc_folder.<br>
 * <b>Janus:</b><br>
 * &emsp;quick_ipc_for_access_control.sh \--rgb_sub_buf_out_res 1280x720<br>
 * <b>Vision+:</b><br>
 * &emsp;quick_ipc_for_access_control.sh \--rgb_sub_buf_out_res 1280x1000<br>
 * @code {.c}
 * board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720
 * ===================================================================================
 * Summary:
 *
 *         Current board name is: [cv25m_janus]
 *         Current sensor name is: [ar0237]
 *
 *         Reallocate overlay memory to: [0x1000000]
 *
 *         Channel num: [3]
 *         Enable best_performance: [No]
 *
 *         Canvas information:
 *                 canvas_id: [0], from SL  main   buffer, resolution: [1920x1080]
 *                 canvas_id: [1], from RGB main   buffer, resolution: [1920x1080]
 *                 canvas_id: [2], from IR  main   buffer, resolution: [1920x1080]
 *                 canvas_id: [3], from SL  second buffer, resolution: [480x272]
 *                 canvas_id: [4], from RGB third  buffer, resolution: [1280x720]
 *
 *         There are [stream_A], [stream_B], and [stream_C]:
 *                 stream_A for [SL ], from canvas_id: [0], resolution: [1920x1080]
 *                 stream_B for [RGB], from canvas_id: [1], resolution: [1920x1080]
 *                 stream_C for [IR ], from canvas_id: [2], resolution: [1920x1080]
 *
 *         In the current case:
 *                 [shell script    : /tmp/run_ipc_folder/run_ipc.sh]
 *                 [lua             : /tmp/run_ipc_folder/run_ipc.lua]
 *
 *         Run demo v1 script:
 *                 [Liveness script     : /tmp/run_ipc_folder/blade_runner_run_liveness_demo.sh]
 *                 [Depth capture script: /tmp/run_ipc_folder/blade_runner_run_depth_capture.sh]
 *                 [Face capture script : /tmp/run_ipc_folder/blade_runner_run_face_capture.sh]
 *
 *         Run demo v2 script:
 *                 [Script         : /tmp/run_ipc_folder/sl_liveness_run_liveness_demo_v2.sh]
 *
 * Warning: Please use the AC-DC power, USB power supply may not be enough to power the board !
 * ===================================================================================
 * @endcode
 *
 * -# Using the VLC, open `rtsp://10.0.0.2/stream2` to get the RGB livestream.
 *
 * Ensure that the local PC and access control board are in the same network
 * segment.
 *
 * Stream 1 is used for the IR channel with the structured-light pattern,
 * stream 2 is used for the RGB channel, and stream 3 is used for the IR
 * channel with the IR LED.
 *
 * @note
 * If the structured-light pattern is not stable on stream 3, the power supply
 * may be not suitable and / or sufficient.
 *
 * @subsection acc_ctrl_run_demo 2.3 Run Demo Applications
 * Users can run the demo applications after the board_config file is generated
 * via the instructions provided in Section @ref acc_ctrl_initialize.
 *
 * @note
 * Each demo requires the stream to be initialized in advance. Ensure
 * that `quick_ipc_for_access_control.sh` runs once after the reboot.
 *
 * Demo shells also accept an option to select the reference YUV being used in
 * the demo. A higher-resolution reference YUV provides a depth map with higher
 * accuracy and resolution; However, it also increases the calculation time.
 * `low_res` represents a low-resolution reference YUV, such as 480x270 and
 * 480x376, and `high_res` represents a high-resolution 1080p reference YUV.
 * By default, a 1080p reference YUV is selected in all demo applications.
 * For example, `sl_run_liveness_demo_v2.sh low_res` enables the use of a
 * low-resolution reference YUV in the liveness demo.
 *
 * A low-resolution reference cannot be used in production because it results
 * in a low-resolution depth map.
 *
 * This chapter includes two demo applications:
 * - `blade_runner_run_depth_capture.sh`
 * - `sl_liveness_run_liveness_demo_v2.sh`
 *
 * @subsubsection acc_ctrl_depth_cap_demo 2.3.1 Capture the Disparity, Depth, and Point Cloud Data
 * Because the FoV of the access control sensors exceed the FoV of the
 * structured-light projector, the valid FoV only covers approximately
 * two-thirds of the full sensor FoV. Users can only obtain 1280x720 and
 * 1280x1000 disparity or depth images from Janus and Vision+ respectively,
 * if the 1080P YUV data is used as a reference frame. Users can obtain the
 * focal length baseline and the center_x / center_y directly from the
 * `calib_mono/warp_<resolution>.json` file.
 *
 * In this example, the disparity is drawn on stream 2.
 * @code {.c}
 * board # /tmp/run_ipc_folder/blade_runner_run_depth_capture.sh
 * Input buffer type = 0
 * Input buffer id = 0
 * Display on stream, id = 0
 * ref data resolution = 1920 x 1080,pitch = 1920
 * ...
 * ...
 * Frame id = 0
 * Frame id = 1
 * ...
 * @endcode
 *
 * @image html acc_ctrl_depth_cap_demo.png "Figure 2-1. Capturing the Disparity, Depth, and Point Cloud Data."
 * <br>
 * The following three files are generated:
 * - `disparity_xxxxx_1frame_int16.4_xxxxx_2560.bin`<br>
 * The file includes the disparity data: each pixel has 16 bits; the resolution
 * is 1280x720 (Janus) or 1280x1000 (Vision+); the pitch=2560; fix point /
 * signed / 16 bit / 4 fractional bits; and the data_format=(1, 1, 4, 0).<br>
 * Users may look up the disparity map file via the `Vooya` application on
 * Linux. Please set the format as follows: color space = single channel, data
 * container = single integer, and bit depth = 12 bit.
 *
 * - `depth_xxxxx_1frame_fp32_xxxxxx_5120.bin`<br>
 * The file includes the depth data: each pixel has a 32-bit floating point
 * representing the distance to the lens center plane. The resolution is
 * 1280x720 (Janus) or 1280x1000 (Vision+), the pitch=5120, and the
 * data_format=(1, 2, 0, 7).<br>
 * Users may look up the disparity map file via the `Vooya` application on
 * Linux. Set the format as follows: color space = single channel, data
 * container = single float (32bit).
 *
 * - `point_cloud_xxxxx_frame1_165327_points.pcd`<br>
 * The file includes the pcd format-total of 165327 points; users can open the
 * three-dimensional point clouds using the `pcl_viewer` on Ubuntu.
 *
 *@note
 * The data format shown in the parentheses above (such as 1, 1, 4, 0) are the
 * vectors that represent the corresponding output data format, and the meaning
 * is as follows:
 * - 1st argument: 0 is unsigned, 1 is signed
 * - 2nd argument: 0 refers to 8-bit, 1 is 16-bit, 2 is 32-bit
 * - 3rd argument: the exponent offset
 * - 4th argument: the number of bits reserved for the exponent field. 0
 *   indicates a fixed point number
 *
 * @subsubsection acc_ctrl_liveness_demo 2.3.2 Run the FDFR Liveness Test Demo
 * -# Run the quick_ipc_for_access_control.sh script:
 *     - With static structured light mode (the following command is optional
 *       if it has run in Section @ref acc_ctrl_initialize).
 *       @code {c}
 *       board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720
 *       @endcode
 *     - With dynamic structured light mode.
 *       @code {c}
 *       board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720 --enable_dynamic_mode
 *       @endcode
 * -# Run the Demo:
 *     - Run the demo to calculate the depth-of-face areas in the 1080p
 *       structured-light image.
 *       @code {c}
 *       board # /tmp/run_ipc_folder/sl_run_liveness_demo_v2.sh high_res
 *       @endcode
 *     - Run the demo to calculate the depth of the full image in the
 *       480x272(Janus) or the 480x376(Vision+) structured-light image.
 *       @code {c}
 *       board # /tmp/run_ipc_folder/sl_run_liveness_demo_v2.sh low_res
 *       @endcode
 * -# Register a new face in the database:
 *     - On the keyboard, press `f` to initiate the program.
 *     - Select option `2` and enter a name.
 *       @code {c}
 *       f
 *       Anything to do on the face database?
 *       1. Show database information.
 *       2. Record a new face.
 *       2
 *       Start recording 9 views of a person's face.
 *       Input name no more than 31 ('q' to exit):
 *       Ambaman
 *       @endcode
 *     - Position the face in one of the nine orientations, and type `r` to
 *       repeat another eight times.
 *       @image html acc_ctrl_face_record.png "Figure 2-2. Face Positions While Recording a Face Database."
 *       @code {c}
 *       Type 'r' to record view 1 in 9 of Ambaman
 *       r
 *       …
 *       Type 'r' to record view 9 in 9 of Ambaman
 *       r
 *       face database saved in /usr/local/bin/data/blade_runner_bin/database.bin.
 *       @endcode
 * -# View the results on the livestream.
 *    The following three types of information will be shown in the results.
 *     - Bounding boxes with different colors:
 *         - Green: Live person
 *         - Red: Not a live person
 *         - Yellow: Invalid distance; no depth information
 *     - Person’s name:
 *         - Name of the person registered in the database
 *     - Distance:
 *       @code {c}
 *       [Notice]: det: 2
 *       [Notice]: ++++++++ Ambaman 0.897497, liveness 1, distance 0.422252m
 *       [Notice]: ++++++++ Ambaman 0.704975, liveness 0, distance 0.333818m
 *       @endcode
 *    <br>
 *    @image html acc_ctrl_face_depth.png "Figure 2-3. Liveness Detection by Calculating the Depth-of-Face Areas."
 *    <br>
 *    @image html acc_ctrl_full_depth.png "Figure 2-4. Liveness Detection by Calculating the Depth on the Full Structured-Light Image."
 *    <br>
 *
 * - - - -
 *
 * @section acc_ctrl_soft_design 3. Software Design
 * The access control EVK module can control the structured-light projector and
 * the IR LED by generating an IR image with a structured-light pattern and an
 * IR image with the IR LED light. The module can also simultaneously retrieve
 * the RGB image. The IR image, with the structured-light pattern, can generate
 * the depth image while the IR image, without the structured-light pattern,
 * can provide face detection or recognition in “night” mode; alternatively, the
 * RGB image can be used for face detection and recognition in “day” mode.
 * Further, users can add an additional 940-nm IR-LED or a white LED for
 * illumination adjustments.
 *
 * @subsection acc_ctrl_sl_control 3.1 Structured-Light Control
 * The data flow is configured by the image audio video (IAV) / sensor driver
 * and the image digital signal processor (IDSP). The driver turns on the
 * structured-light pattern when the sensor begins the exposure process. The
 * typical use case does not require full frame rate IR data with the
 * structured-light pattern, as the default sequence of structured-light pattern
 * is 000001000001000001…. This turns on the structured light once every six
 * frames.
 *
 * @image html acc_ctrl_sensor_sl.png "Figure 3-1. Sensor Exposure and Structured Light."
 *
 * IDSP splits the input data into two IR channels and one RGB channel. The
 * video input (VIN) frames per second (fps) is equal to the sum of the fps for
 * each of the three channels.
 *
 * @image html acc_ctrl_sensor_sl_control.png "Figure 3-2. Structured Light and the RGB-IR Sensor Control."
 *
 * @subsection acc_ctrl_data_flow 3.2 RGB and IR Data Flow for Streaming
 * This section illustrates the data flow of the input IR and RGB channels.
 *
 * First, the data moves to the main buffer of each channel, and then the valid
 * structured-light data is cropped from channel 0.main. Depending on the
 * hardware, the valid IR size and offset will vary. For example, Janus has an
 * offset of (320,160) and a cropped size of (1280x720); Vision+ has an
 * offset of (640, 0) and a cropped size of (2560, 2000). Check the setting
 * files used by `test_encode`.
 *
 * @image html acc_ctrl_janus_data_flow.png "Figure 3-3. Janus Data Flow of Three Channels."
 * <br>
 * @image html acc_ctrl_vision_plus_data_flow.png "Figure 3-4. Vision+ Data Flow of Three Channels."
 * <br>
 *
 * @subsection acc_ctrl_adv_feature 3.3 Advanced Features
 * This section explains the advanced features of the access control product.
 * @subsubsection acc_ctrl_dyn_trigger 3.3.1 Dynamic Trigger of Structured Light
 * Dynamic trigger mode is used to fully control the structured light by
 * customer application. It includes controlling the light point of SL
 * (Structured Light), adjusting the light duration of SL.
 *
 * Dynamic trigger mode is enabled when the system enters the preview stage.
 * This can be performed by setting the frame ratio of the SL channel to 0. The
 * `FRAME_RATIO` value is defined in the board configuration file, and passed to
 * the `test_encode` command via the `custom-chan-frame-ratio` option.
 *
 * After dynamic trigger mode is enabled, the user gets the fully control to the
 * SL. The SL control can be accessed by `IAV_IOC_CUSTOM_CMDS ioctl`.
 * -# `flash_led_custom_trigger_once` enables SL on the next single frame.
 * -# `flash_led_min_time_in_ms` sets the minimum SL light duration in
 *    miliseconds.
 * -# `flash_led_line_offset` defines the SL light point in the line index. The
 *    range is [0, max line number].
 * -# `flash_time_in_ms` configures the SL light duration in miliseconds.
 * -# `ir_led_time_in_ms` configures the IR LED light duration in miliseconds.
 * -# `flash_led_update_flag_bitmap` defines which parameters are updated in the
 *    IAV driver.
 *
 * @code {c}
 * struct iav_custom_cfg custom_cfg;
 * struct iav_custom_vin_led_ctrl *vin_led_ctrl = &custom_cfg.arg.vin_led_ctrl;
 * memset(&custom_cfg, 0, sizeof(custom_cfg));
 * vin_led_ctrl->flash_led_custom_trigger_once = 1;
 * vin_led_ctrl->flash_led_min_time_in_ms = 5;
 * vin_led_ctrl->flash_led_line_offset = 180;
 * vin_led_ctrl->flash_time_in_ms = 10;
 * vin_led_ctrl->ir_led_time_in_ms = 10;
 * vin_led_ctrl->flash_led_update_flag_bitmap =
 *     IAV_CUSTOM_LED_FLASH_LINE_OFFSET_UPDATE_FLAG |
 *     IAV_CUSTOM_LED_FLASH_TRIGGER_ONCE_UPDATE_FLAG |
 *     IAV_CUSTOM_LED_FLASH_MIN_TIME_UPDATE_FLAG |
 *     IAV_CUSTOM_LED_FLASH_TIME_UPDATE_FLAG |
 *     IAV_CUSTOM_LED_IR_FLOOD_FLASH_TIME_UPDATE_FLAG;
 * custom_cfg.cmd_code = IAV_CUSTOMCMD_CFG_VIN_LED_RT_CTRL;
 * ioctl(fd_iav, IAV_IOC_CUSTOM_CMDS, &custom_cfg);
 * @endcode
 *
 * @subsubsection acc_ctrl_ai_metering 3.3.2 AI Metering Mode
 * AI metering mode allows the user to control the exposure based on a region
 * of interest (ROI) input. The ROI input can be calculated using a different CV
 * algorithm, such as face detection, person detection, and so on. By enabling
 * this mode, the interested areas will always be well exposed and will not be
 * interfered by background.
 *
 * The Ambarella SDK provides an example of the AI Metering feature. The code
 * below demonstrates the steps to run the AI metering feature on Janus. To run
 * on Vision+, adjust rgb_sub_buf_out_res value to 1280x1000.
 *
 * -# Initialize the system with AI Metering enabled:
 *   @code {c}
 *   board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720 --enable_dynamic_mode --enable_ai_metering
 *   @endcode
 * -# Run liveness demo application:
 *   @code {c}
 *   board # /tmp/run_ipc_folder/sl_run_liveness_demo_v2.sh
 *   @endcode
 *
 * @subsubsection acc_ctrl_depth_option 3.3.3 Depth Generation Method Selection
 * The Ambarella SDK includes two depth generation methods: Blade Runner and
 * Fast Block Match. Blade Runner runs on CPU only, while Fast Block Match
 * mainly runs on VP. Due to their properties, they are proficient in
 * VP-intensive and CPU-intensive systems.
 *
 * Demo applications using Blade Runner:
 * -# test_blade_runner
 * -# test_sl_liveness_v2
 *
 * Demo applications using Fast Block Match:
 * -# test_sl_liveness_v2
 *
 * The Blade Runner algorithm is selected for all applications by default. In
 * order to select the depth generation method in the `test_sl_liveness_v2`
 * application, the `depth_algo_type` option will be used. A value of 0 refers
 * to the Blade Runner method, and a value of 1 refers to Fast Block Match
 * method. Further, the `fbm_config` option must be specified. Refer to
 * Section @ref acc_ctrl_test_sl_liveness for more details on these options.
 *
 * The following configuration requires to be selected for FBM feature.
 * @code
 * [*] Ambarella Application Configuration  --->
 *     [*]   Build Access Control Apps  --->
 *         [*]   Build Structured Light Liveness V2 FBM Apps
 * @endcode
 *
 * The demos for using the Fast Block Match method on `test_sl_liveness_v2` can
 * run with the commands below.
 *
 * For Janus:
 *     @code {c}
 *     board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720
 *     board # /tmp/run_ipc_folder/sl_run_liveness_demo_v2.sh fbm_enable
 *     @endcode
 * For Vision+:
 *     @code {c}
 *     board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720 --rgb_sub_buf_in_param 640,320,2560,1440
 *     board # /tmp/run_ipc_folder/sl_run_liveness_demo_v2.sh fbm_enable
 *     @endcode
 *
 * @subsection acc_ctrl_algo_data_flow 3.4 IR / RGB Data Flow for the Algorithm Library
 * The digital signal processor (DSP) splits the IR / RGB data from one RGB-IR
 * sensor.
 *
 * The Ambarella IR process library can generate the depth and point cloud
 * images from the IR structured-light pattern, which includes two main
 * functions: (1) generating a disparity image, depth image, and point cloud
 * data and (2) performing the liveness test. Users may refer to the documents
 * in the SDK for additional details.
 * @code {c}
 * build $ make sdk_doc
 * make sdk_doc
 * other_feature.h is formed.
 * advanced_feature.h is formed.
 * basic_feature.h is formed.
 * [Succeeded] Generating document of feature_sets!
 * [Succeeded] Generating document of bpi_app!
 * amba_doc.h is generated.
 * amba.doxygen is formed.
 * [Succeeded] Generating document of amba!
 * All documents are generated...
 * @endcode
 *
 * Refer to @ref page_lib_blade_runner_doc for more details.
 *
 * The demo `FDFR + liveness test` flow is shown below. The IR process library
 * checks the depth information with the FD result for the liveness checking.
 * <br>
 * @image html acc_ctrl_algo_data_flow.png "Figure 3-5. IR / RGB Data Flow for the Algorithm Library."
 *
 * @subsection acc_ctrl_board_config 3.5 Customize the Board Configuration File
 * The `board_config` file is generated by the gen_board_config.sh shell, and
 * specifies the system and hardware configuration data for each access control
 * board. Each time the hardware calibration data is updated, the `board_config`
 * file must be regenerated.
 *
 * By default, the most commonly-used system configuration is selected in the
 * `board_config` file. It uses a three-channel system for structured light,
 * RGB, and IR LED, respectively. Additionally, the frame ratio for each channel
 * is 5:20:5. The user is permitted to change the parameters within the
 * `board_config` in order to customize the system. For example,
 * `CHANNEL_AMOUNT` can be set to 2 for disabling the third IR LED channel. For
 * more details, refer to the comments within the `board_config` file.
 *
 * @code {sh}
 * CV2x # gen_board_config.sh /usr/share/ambarella/calib_mono H210615A001
 * BOARD_CONFIG_VERSION=1.0.0
 * MODULE_ID=1912060033 # Sensor module ID
 *
 * # File Name and Path Configurations
 * CALIB_MONO_PATH=/usr/share/ambarella/calib_mono
 * CONFIG_FILE_PATH=/usr/share/ambarella/calib_mono/board_config
 * CALIB_DATA_SHA256SUM_FILE=/usr/share/ambarella/calib_mono/calib_data_sha256.txt
 * AAA_LUA_PATH=/usr/share/ambarella/idsp/product_id_authen_dn_switch_limit_shutter.lua
 * DYNAMIC_MODE_AAA_LUA_PATH=/usr/share/ambarella/idsp/product_id_authen_dn_switch.lua
 *
 * # User Configurations - Structured Light Control Settings
 * CHANNEL_AMOUNT=3 # Configure the number of channels being used in the range of [2, 3].
 *               # 2-channel mode includes RGB channel and Structured light channel.
 *               # 3-channel mode additionaly enables IR LED channel.
 * # [NOTE] Changes to FRAME_RATIO requires to update channels' idsp_fps in IAV script luas accordingly.
 * if [ $CHANNEL_AMOUNT -eq 3 ]; then
 * FRAME_RATIO=1:4:1 # Frame ratio for each channel. Chan 2 frame ratio : Chan 1 frame ratio : Chan 0 frame ratio
 * elif [ $CHANNEL_AMOUNT -eq 2 ]; then
 * FRAME_RATIO=4:1 # Frame ratio for each channel. Chan 1 frame ratio : Chan 0 frame ratio
 * else
 * echo -e "Unsupported Channel Number!"
 * fi
 * STRUCTURED_LIGHT_FLASH_TIME=10 # Structured light flash time in miliseconds
 * FLASH_START_OFFSET=0 # Adjust structured light flash start offset in lines for dynamic trigger mode. Range: [-(vin height), (vin height)];
 * FLASH_START_MULTIPLIER=1 # Adjust structured light flash start line's multiplier.
 *
 * # User Configurations - System and Physical Parameters
 * BASELINE=0.04 # The distance between structured light and sensor in meter
 * SL_MAIN_BUF_OUT_WIDTH=1920 # The width of main buffer output in structured light channel
 * SL_MAIN_BUF_OUT_HEIGHT=1080 # The height of main buffer output in structured light channel
 * SL_SUB_BUF_OUT_WIDTH=480 # The width of sub buffer output in structured light channel
 * SL_SUB_BUF_OUT_HEIGHT=272 # The height of sub buffer output in structured light channel
 * RGB_MAIN_BUF_OUT_WIDTH=1920 # The width of main buffer output in rgb channel
 * RGB_MAIN_BUF_OUT_HEIGHT=1080 # The height of main buffer output in rgb channel
 * RGB_SUB_BUF_OUT_WIDTH=1280 # The width of sub buffer output in rgb channel
 * RGB_SUB_BUF_OUT_HEIGHT=720 # The height of sub buffer output in rgb channel
 * IR_MAIN_BUF_OUT_WIDTH=1920 # The width of main buffer output in ir channel
 * IR_MAIN_BUF_OUT_HEIGHT=1080 # The height of main buffer output in ir channel
 * CROP_ROI_BASE_WIDTH=1920 # The width of crop source
 * CROP_ROI_BASE_HEIGHT=1080 # The height of crop source
 * CROP_ROI_MIN_OFFSET_X=320 # The minimum x offset of valid structured light pattern area
 * CROP_ROI_MIN_OFFSET_Y=160 # The minimum y offset of valid structured light pattern area
 * CROP_ROI_MAX_WIDTH=1280 # The maximum width of valid structured light pattern area
 * CROP_ROI_MAX_HEIGHT=720 # The maximum height of valid structured light pattern area
 *
 * # User Configurations - Blade Runner Parameter Settings
 * CV_MODEL_DIR=/usr/local/bin/data/blade_runner_bin/
 * DISP_SMOOTH_LOW_RES=8 # Disparity smooth value for using high resolution ref
 * DISP_RANGE_LOW_RES=4 # Disparity range value for using high resolution ref
 * DISP_SMOOTH_HIGH_RES=13 # Disparity smooth value for using low resolution ref
 * DISP_RANGE_HIGH_RES=6 # Disparity range value for using low resolution ref
 *
 * # Module Settings (Automatically Generated)
 * REF_YUV_DIST=1.475 # The distance from the YUV being captured to sensor
 * ROTATE_MODE=1 # Rotate operation depends on orientation of structured light and sensor
 *
 * # Module settings for using low resolustion reference YUV (Automatically Generated)
 * REF_YUV_PATH=/usr/share/ambarella/calib_mono/ref_b2_H1912060033_canvas2_480x272_NV12_1.475.yuv # Reference YUV file path
 * REF_YUV_WIDTH=480 # The width of selected reference yuv
 * REF_YUV_HEIGHT=272 # The height of selected reference yuv
 * REF_YUV_PITCH=480 # The pitch of selected reference yuv
 * FOCAL_LENGTH=306.75 # Focal length in pixels
 * CENTER_X_COORD=239.25 # Coordinates of center X in pixels
 * CENTER_Y_COORD=134.25 # Coordinates of cneter Y in pixels
 * REF_YUV_OFFSET=0 # Reference YUV transition offset
 * DISP_SMOOTH=8 # Disparity smooth value for selected ref
 * DISP_RANGE=4 # Disparity range value for selected ref
 * CROP_OFFSET_X=0 # X offset of crop area within reference yuv
 * CROP_OFFSET_Y=0 # Y offset of crop area within reference yuv
 * DEPTH_FACE_ONLY="" # depth map for face only in liveness demo
 * @endcode
 *
 * @subsection acc_ctrl_quick_ipc_janus 3.6 Demo Preparation ― Quick IPC on CV25M Janus
 * After the `board_config` is generated, `quick_ipc_for_access_control.sh` can
 * be used to set up the IAV environment, including channels, canvases, and
 * streams. It includes the commands `test_aaa_service` and `test_encode`.
 *
 * @subsubsection acc_ctrl_quick_ipc_janus_options 3.6.1 Options
 * <table>
 * <caption>quick_ipc_for_access_control.sh for Janus Usages.</caption>
 * <tr><th> Short Options <th> Long Options <th> Usages
 * <tr><td colspan="3"> Vin
 * <tr><td>     <td> --vin_mode                <td> Specifies the high dynamic range (HDR) mode, such as "linear" and "2x". The default is "linear".
 * <tr><td>     <td> --vsrc_fps                <td> Specifies the sensor frame rate; the default is 30.
 * <tr><td>     <td> --enable_dynamic_mode     <td> Enables the dynamic mode; the default is disabled. No parameters are required.
 * <tr><td colspan="3"> 3A
 * <tr><td>     <td> --enable_ai_metering      <td> Enables AI metering mode; the default is disabled. No parameters are required. It allows AE / AWB / AF (3A) to focus on face exposure.
 * <tr><td colspan="3"> Source Buffer
 * <tr><td>     <td> --sl_main_buf_out_res     <td> Specifies the output resolution of the main buffer of the SL channel. The default is "1920x1080".
 * <tr><td>     <td> --sl_sub_buf_in_param     <td> Specifies the input crop parameters for the sub-buffer (second buffer) of the SL channel, which is cropped from the main buffer by the digital signal processor (DSP). The format of parameters is "offset_x, offset_y, width, and height". For example: "--sl_sub_buf_in_param 320,160,1280,720".
 * <tr><td>     <td> --sl_sub_buf_out_res      <td> Specifies the output resolution for the sub-buffer (second buffer) of the SL channel, which must be smaller than the resolution that is defined in "sl_sub_buf_in_param" as DSP only supports the downscale. For example: "--sl_sub_buf_out_res 480x272".
 * <tr><td>     <td> --rgb_main_buf_out_res    <td> Specifies the output resolution of the main buffer of the RGB channel. Normally, this buffer is for encoding to show the algorithm result. The default is "1920x1080".
 * <tr><td>     <td> --rgb_sub_buf_in_param    <td> Specifies the input crop parameters for the sub-buffer (third buffer) of the RGB channel, which is cropped from the main buffer by the DSP. The format of parameters is "offset_x, offset_y, width, and height". For example: "--rgb_sub_buf_in_param 320,160,1280,720". The default is "320, 160, 1280, and 720".
 * <tr><td>     <td> --rgb_sub_buf_out_res     <td> Specifies the output resolution for the sub-buffer (third buffer) of the RGB channel, which must be smaller than the resolution that is defined in "rgb_sub_buf_in_param" as DSP only supports the downscale. Normally, this buffer is for the face detection. The default is "1280x720".
 * <tr><td>     <td> --ir_main_buf_out_res     <td> Specifies the output resolution of the main buffer of the IR channel. The default is "1920x1080".
 * <tr><td colspan="3"> System
 * <tr><td>     <td> --realloc_mem             <td> Reallocates the memory part size. It only supports "overlay" and "blur". Only one type can be reallocated at a time. For example: "--realloc_mem overlay,0x04009000" or "--realloc_mem blur, 0x04009000".
 * <tr><td>     <td> --best_performance        <td> Disables unnecessary streams and the canvas buffer. No parameters are required.
 * <tr><td>     <td> --customized_lua          <td> Uses a customized Lua. For example: "--customized_lua /root/customized.lua".
 * <tr><td colspan="3"> Debug
 * <tr><td> -h  <td> --help                    <td> Prints help information. No parameters are required.
 * <tr><td>     <td> --disable_summary_info    <td> Does not print summary information. No parameters are required.
 * <tr><td>     <td> --save_path               <td> Saves the generated files to specify the directory. The default is "/tmp/run_ipc_folder".
 * </table>
 *
 * @subsubsection acc_ctrl_quick_ipc_janus_config 3.6.2 Configurations
 * Default with three channels
 * @code {c}
 * board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720
 * @endcode
 * <b>Canvas Information</b>
 * - Canvas 0, from the SL channel main buffer, the resolution is: [1920x1080]
 * - Canvas 1, from the RGB channel main buffer, the resolution is: [1920x1080]
 * - Canvas 2, from the IR channel main buffer, the resolution is: [1920x1080]
 * - Canvas 3, from the SL channel second buffer, the resolution is: [480x272]
 * - Canvas 4, from the RGB channel third buffer, the resolution is: [1280x720]
 *
 * <b>Stream Information</b>
 * - Stream A for SL, from canvas 0, the resolution is: [1920x1080]
 *   (the same as canvas)
 * - Stream B for RGB, from canvas 1, the resolution is: [1920x1080]
 *   (the same as canvas)
 * - Stream C for IR, from canvas 2, the resolution is: [1920x1080]
 *   (the same as canvas)
 * - Stream D is reserved in the generated Lua file. It is not enabled
 *   by default.
 * <br>
 *
 * Best performance with three channels
 * @code {c}
 * quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720 --best_performance
 * @endcode
 * <b>Canvas Information</b>
 * - Canvas 0, from the SL channel main buffer, the resolution is: [1920x1080]
 * - Canvas 1, from the RGB channel main buffer, the resolution is: [1920x1080]
 * - Canvas 2, from the IR channel main buffer, the resolution is: [1920x1080]
 * - Canvas 3, from the RGB channel third buffer, the resolution is : [1280x720]
 *
 * <b>Stream Information</b>
 * - Stream A for RGB, from canvas 1, the resolution is: [1920x1080]
 *   (the same as canvas)
 * <br>
 *
 * Two channels
 * @code {c}
 * board # vi /usr/share/ambarella/calib_mono/board_config
 * CHANNEL_AMOUNT=2
 * board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720
 * @endcode
 * <b>Canvas Information</b>
 * - Canvas 0, from the SL channel main buffer , the resolution is: [1920x1080]
 * - Canvas 1, from the RGB channel main buffer, the resolution is: [1920x1080]
 * - Canvas 2, from the SL channel second buffer, the resolution is: [480x272]
 * - Canvas 3, from the RGB third channel buffer, the resolution is: [1280x720]
 *
 * <b>Stream Information</b>
 * - Stream A for SL, from canvas 0, the resolution is: [1920x1080]
 *   (the same as canvas)
 * - Stream B for RGB, from canvas 1, the resolution is: [1920x1080]
 *   (the same as canvas)
 *
 * @subsection acc_ctrl_quick_ipc_vision_plus 3.7 Demo Preparation ― Quick IPC on CV22 Vision+
 * After the `board_config` is generated, `quick_ipc_for_access_control.sh` can
 * be used to set up the IAV environment, including channels, canvases, and
 * streams. It includes the commands `test_aaa_service` and `test_encode`.
 *
 * @subsubsection acc_ctrl_quick_ipc_vision_plus_options 3.7.1 Options
 * <table>
 * <caption>quick_ipc_for_access_control.sh for Vision+ Usages.</caption>
 * <tr><th> Short Options <th> Long Options <th> Usages
 * <tr><td colspan="3"> Vin
 * <tr><td>     <td> --vin_mode                <td> Specifies the HDR mode, such as "linear" or "2x". The default is "linear".
 * <tr><td>     <td> --enable_dynamic_mode     <td> Enables dynamic mode. The default is disabled. No parameters are required.
 * <tr><td colspan="3"> 3A
 * <tr><td>     <td> --enable_ai_metering      <td> Enables AI metering mode; the default is disabled. No parameters are required. It allows 3A to focus on face exposure.
 * <tr><td colspan="3"> Source Buffer
 * <tr><td>     <td> --sl_main_buf_out_res     <td> Specifies the output resolution of the main buffer of the SL channel. The default is "3840x2160".
 * <tr><td>     <td> --sl_sub_buf_in_param     <td> Specifies the input crop parameters for the sub-buffer (second buffer) of the SL channel, which is cropped from the main buffer by the DSP. The format of parameters is "offset_x,offset_y,width,hight". For example: "--sl_sub_buf_in_param 320,160,1280, and 720".
 * <tr><td>     <td> --sl_sub_buf_out_res      <td> Specifies the output resolution for the sub-buffer (second buffer) of the SL channel, which must be smaller than the resolution that is defined in "sl_sub_buf_in_param" as the DSP only supports the downscale. For example: "--sl_sub_buf_out_res 480x272".
 * <tr><td>     <td> --rgb_main_buf_out_res    <td> Specifies the output resolution of the main buffer of the RGB channel. Normally, this buffer is for encoding to show the algorithm result. The default is "3840x2160".
 * <tr><td>     <td> --rgb_sub_buf_in_param    <td> Specifies the input crop parameters for the sub-buffer (third buffer) of the RGB channel, which is cropped from the main buffer by the DSP. The format of parameters is "offset_x,offset_y,width,hight". For example: "--rgb_sub_buf_in_param 640,0,2560,2000". The default is "640, 0, 2560, and 2000".
 * <tr><td>     <td> --rgb_sub_buf_out_res     <td> Specifies the output resolution for the sub-buffer (third buffer) of the RGB channel, which must be smaller than the resolution that is defined in "rgb_sub_buf_in_param" as the DSP only supports the downscale. Normally, this buffer is for face detection. The default is "1280x1000".
 * <tr><td>     <td> --ir_main_buf_out_res     <td> Specifies the output resolution of the main buffer of the IR channel. The default is "3840x2160".
 * <tr><td colspan="3"> System
 * <tr><td>     <td> --realloc_mem             <td> Reallocates the memory part size. It only supports "overlay" and "blur". Only one type can be reallocated at a time. For example: "--realloc_mem overlay,0x04009000" or "--realloc_mem blur, 0x04009000".
 * <tr><td>     <td> --best_performance        <td> Disables unnecessary streams and the canvas buffer. No parameters are required.
 * <tr><td>     <td> --customized_lua          <td> Uses a customized Lua. For example: "--customized_lua /root/customized.lua".
 * <tr><td colspan="3"> Debug
 * <tr><td>     <td> --help                    <td> Prints help information. No parameters are required.
 * <tr><td>     <td> --disable_summary_info    <td> Does not print summary information. No parameters are required.
 * <tr><td>     <td> --save_path               <td> Saves the generated files to specify the directory. The default is "/tmp/run_ipc_folder".
 * </table>
 *
 * @subsubsection acc_ctrl_quick_ipc_vision_plus_config 3.7.2 Configurations
 * Default with three channels
 * @code {c}
 * quick_ipc_for_access_control.sh --rgb_sub_buf_out_res
 * @endcode
 * <b>Canvas Information</b>
 * - Canvas 0, from the SL channel third buffer, the resolution is [1920x1080]
 * - For the stream encoded from canvas 0, the resolution is 1080p when the main
 *   buffer is 1080p. If the main buffer is less than 1080p, the resolution will
 *   be set to be the same as the main buffer.
 * - Canvas 1, from the RGB channel second buffer, the resolution is:
 *   [1920x1080]
 * - For the stream encoded from canvas 1, the resolution is 1080p when the main
 *   buffer is 4K. If the main buffer is in (480p, 4K), the resolution will be
 *   set to 480p. If the main buffer is less than 480p, the resolution will be
 *   set to be the same as the main buffer.
 * - Canvas 2, from the IR channel second buffer, the resolution is [1920x1080]
 * - For the stream encoded from canvas 2, the resolution is 1080p when the main
 *   buffer is 4K. If the main buffer is in (480p, 4K), the resolution will be
 *   set to 480p. If the main buffer is less than 480p, the resolution will be
 *   set to be the same as the main buffer.
 * - Canvas 3, from the SL channel second buffer, the resolution is [480x376]
 * - Canvas 4, from the RGB channel third buffer, the resolution is [1280x1000]
 * - Canvas 5, from the SL channel main buffer, the resolution is [3840x2160],
 *   disable_yuv_dram=1 in Lua
 * - Canvas 6, from the RGB channel main buffer, the resolution is [3840x2160]
 * - Canvas 7, from the IR channel main buffer, the resolution is [3840x2160],
 *   disable_yuv_dram=1 in Lua
 *
 * <b>Stream Information</b>
 * - Stream A for SL, from canvas 0, the resolution is [1920x1080] (the same
 *   as canvas)
 * - Stream B for RGB, from canvas 1, the resolution is [1920x1080] (the same
 *   as canvas)
 * - Stream C for IR, from canvas 2, the resolution is [1920x1080] (the same
 *   as canvas)
 * - Stream D is reserved in the generated Lua file. It is not enabled by
 *   default.
 *   <br>
 *
 * Best performance with three channels
 * @code {c}
 * quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x1000 --best_performance
 * @endcode
 * <b>Canvas Information</b>
 * - Canvas 0, from the SL channel third buffer, the resolution is [1920x1080]
 * - Canvas 1, from the RGB channel second buffer, the resolution is [1920x1080]
 * - Canvas 2, from the IR channel second buffer, the resolution is [1920x1080]
 * - For the stream encoded from canvas 0, 1, and 2, the resolution is 1080p
 *   when the main buffer is 4K. If the main buffer is in (480p, 4K), the
 *   resolution will be set to 480p. If the main buffer is less than 480p, the
 *   resolution will be set to be the same as the main buffer.
 * - Canvas 3, from the RGB third buffer, the resolution is [1280x1000]
 * - Canvas 4, from the SL channel main buffer , the resolution is [3840x2160],
 *   disable_yuv_dram=1 in Lua
 * - Canvas 5, from the RGB channel main buffer , the resolution is
 *   [3840x2160], disable_yuv_dram=1 in Lua
 * - Canvas 6, from the IR channel main buffer , the resolution is [3840x2160],
 *   disable_yuv_dram=1 in Lua
 *
 * <b>Stream Information</b>
 * - Stream A for RGB, from canvas 1, the resolution is [1920x1080] (the same as
 * canvas)
 * <br>
 *
 * Two channels
 * @code {c}
 * board # vi /usr/share/ambarella/calib_mono/board_config
 * CHANNEL_AMOUNT=2
 * board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x1000
 * @endcode
 * <b>Canvas Information</b>
 * - Canvas 0, from the SL channel third buffer, the resolution is [1920x1080]
 * - For the stream encoded from canvas 0, the resolution is 1080p when the main
 *   buffer is 1080p. If the main buffer is less than 1080p, the resolution will
 *   be set to be the same as the main buffer.
 * - Canvas 1, from the RGB channel second buffer, the resolution is
 *   [1920x1080]
 * - For the stream encoded from canvas 1, the resolution is 1080p when the main
 *   buffer is 4K. If the main buffer is in (480p, 4K), the resolution will be
 *   set to 480p. If the main buffer is less than 480p, the resolution will be
 *   set to be the same as the main buffer.
 * - Canvas 2, from the SL channel second buffer, the resolution is [480x376]
 * - Canvas 3, from the RGB channel third buffer, the resolution is [1280x1000]
 * - Canvas 4, from the SL channel main buffer, the resolution is [3840x2160]
 *   disable_yuv_dram=1 in Lua
 * - Canvas 5, from the RGB channel main buffer, the resolution is [3840x2160]
 *
 * <b>Stream Information</b>
 * - Stream A for SL, from canvas 0, the resolution is [1920x1080] (the same
 *   as canvas)
 * - Stream B for RGB, from canvas 1, the resolution is [1920x1080] (the same
 *   as canvas)
 *
 * @subsection acc_ctrl_sl_liveness_demo 3.8 Software Design of test_sl_liveness_v2
 * This section provides details on the framework of `test_sl_liveness_v2`
 * and how user customizations can be applied onto `test_sl_liveness_v2`.
 * @subsubsection acc_ctrl_sl_liveness_data_flow 3.8.1 Data Flow of the test_sl_liveness_v2 Demo
 * The demonstration has im, fd, fr, ld, vl, and main threads.
 * - im: Image thread to query the colored YUV images and the structured-light images.
 * - fd: Face detection thread to run the face detection algorithm.
 * - fr: Face recognition thread to run the face recognition algorithm.
 * - ld: Liveness detection thread to run the liveness detection with the Blade Runner and / or Fast Block Match algorithm.
 * - vl: Visualize thread to draw the result on the stream.
 * - main: The thread to initialize and use data to connect the other threads.
 *
 * @image html acc_ctrl_sl_liveness_data_flow.png "Figure 3-6. test_sl_liveness_v2 Multi-Thread Data Flow."
 *
 * The data flow includes image data, face detection results, face recognition
 * results, and liveness detection results; it begins with the image data,
 * proceeding through each thread to generate more data along the way.
 *
 * There are two types of image data queried by the im thread from the IAV
 * driver: the colored YUV images and the structured-light images.
 * - Colored YUV images
 *
 * The colored YUV images are sampled when the structured light is off, and are
 * used for face detection and face recognition in the fd and fr threads.
 * - Structured-light images
 *
 * The structured-light images are sampled when the structured light is on, and
 * are used for liveness detection with the Blade Runner and / or Fast Block
 * Match algorithm.
 *
 * The image data follows the data flow path, so all threads can use the image
 * data. After being generated by the im thread, the image data will return to
 * the im thread and be released by the thread.
 *
 * If the structured light is turned on dynamically, the face detection result
 * returns to the im thread to control the query of the structured-light images.
 * If any faces are detected, the im thread will turn on the light to query the
 * structured-light images. If there is no face detected, the im thread will
 * stop the querying process.
 *
 * These threads can enable several frames of images in parallel, and handle
 * the same frame of an image in order.
 * - Depending on the size of each queue and the performance of each algorithm,
 *   several frames may remain in the data flow.
 * - The im thread will discard the old image data in the queue if the algorithm
 *   cannot manage it in a timely manner.
 * - If the queue size is large, the number of frames to manage per second will
 *   be greater, so the delay from the generation of the image to the final
 *   detection result will be longer. Therefore, to reduce the delay in the
 *   demo, the queue size is limited and the new feeding of the fd thread will
 *   wait for the fr and id threads to complete their functions.
 *
 * @subsubsection acc_ctrl_sl_livenss_customize 3.8.2 Customize the Demo
 * The source code of the demo is placed under
 * `ambarella/app/access_control/sl_liveness_v2` in the SDK. The following
 * examples demostrate how to customize the demo by changing the source code.
 * -# Replace the face detection module.
 *     - Change the multi-task cascaded convolutional neural network
 *       (MTCNN)-related part in the fd_thread.h and the fd_thread.c.<br>
 *       fd_thread.h
 *       @code {c}
 *       typedef struct fd_thread_s {
 *           mtcnn_t mtcnn;
 *       @endcode
 *       fd_thread.c
 *       @code {c}
 *       #include <mtcnn.h>
 *       static int fd_net_init(fd_thread_t *thread)
 *       static void fd_net_deinit(fd_thread_t *thread)
 *       static ea_tensor_t *fd_net_input(fd_thread_t *thread)
 *       static int fd_net_update_input(fd_thread_t *thread, ea_tensor_t *input)
 *       static int fd_net_forward(fd_thread_t *thread)
 *       static int fd_net_post_process(fd_thread_t *thread, fd_result_t *result)
 *       @endcode
 *     - Change the image pre-processing in the test_sl_liveness.c.
 *       @code {c}
 *       static int feed_fd(ctx_t *ctx)
 *       {
 *           RVAL_OK(ea_cvt_color_resize(fd_canvas_tensor, fd_input->image, EA_COLOR_YUV2RGB_NV12, EA_VP));
 *       @endcode
 *     - Add / remove parameters in `params.h` and 'params.c'.
 *       @code {c}
 *       typedef struct params_s {
 *           int fd_canvas_id;
 *           roi_t fd_roi_in_canvas;
 *           float fd_area_thresh;
 *           int max_face_num;
 *       @endcode
 * -# Replace the face recognition module.
 *     - Change the `Mobilefacenets` related part in the `fr_thread.h` and the
 *       `fr_thread.c`.<br>
 *       fr_thread.h
 *       @code {c}
 *       typedef struct fr_thread_s {
 *           mobilefacenets_t mobilefacenets;
 *       @endcode
 *       fr_thread.c
 *       @code {c}
 *       #include <mobilefacenets.h>
 *       #define FR_MODEL_BINARY_NAME          "mobilefacenets_cavalry.bin"
 *       #define FR_MAX_FEATURE_VECTOR_NUM    MOBILEFACENETS_MAX_OUT_NUM
 *       #define FR_FEATURE_VECTOR_SIZE        MOBILEFACENETS_FEATURE_VECTOR_SIZE
 *
 *       static int fr_net_init(fr_thread_t *thread)
 *       static void fr_net_deinit(fr_thread_t *thread)
 *       static ea_tensor_t *fr_net_input(fr_thread_t *thread)
 *       static int fr_net_forward(fr_thread_t *thread, int batch_num)
 *       static int fr_net_post_process(fr_thread_t *thread, fr_features_t *features)
 *
 *       TFloat fixed_dim[5 * 2] = {
 *           30.2946, 51.6963,
 *           65.5318, 51.6963,
 *           48.0252, 71.7366,
 *           33.5493, 92.3655,
 *           62.7299, 92.3655};
 *       @endcode
 *     - Change the vector size in fr/mfn_face_db.h if the new size is
 *       different.
 *       @code {c}
 *       #define D_MFN_FACE_EV_LEN 128
 *       @endcode
 *     - Change the image pre-processing in the test_sl_liveness.c.
 *       @code {c}
 *       static int feed_fr_sl(ctx_t *ctx)
 *       {
 *           RVAL_OK(ea_cvt_color_resize(fr_canvas_tensor, fr_input->image, EA_COLOR_YUV2BGR_NV12, EA_VP));
 *       @endcode
 * -# Replace the liveness detection module.
 *     - Add a new file, including depth generation and liveness detection, to
 *       the folder of `ambarella/app/access_control/sl_liveness_v2/liveness_detection`.
 *       For example: `blade_runner_algo.c`
 *     - Implement the algorithm interface, such as `blade_runner_algo.c`
 *       @code {c}
 *       static int ld_new_depth_algo_init(const ld_thread_params_t *params)
 *       static int ld_new_depth_algo_deinit(void)
 *       static int ld_new_depth_algo_calc_full_depth(ld_thread_t *thread)
 *       static int ld_new_depth_algo_calc_face_depth(ld_thread_t *thread)
 *       int register_new_depth_algo_ops(ld_algo_op_t *algo_ops)
 *       @endcode
 *     - Register new liveness detection operations in ld_thread.c
 *       @code {c}
 *       static int register_ld_ops(ld_algo_op_t *algo_ops, int algo_type)
 *       @endcode
 *     - Add / remove parameters in `params.h` and `params.c`.
 *       @code {c}
 *       typedef struct params_s {
 *           int ld_canvas_id;
 *           roi_t ld_roi_in_canvas;
 *           float baseline;
 *           float ref_dist;
 *           char ref_yuv_path[MAX_PATH_STRLEN + 1];
 *           int ref_width;
 *           int ref_height;
 *           int ref_pitch;
 *           int depth_algo_type;
 *           int calc_full_depth;
 *           int blade_runner_config[7];
 *           int fbm_config[10];
 *           float liveness_config[7];
 *       }
 *       @endcode
 *
 * - - - -
 *
 * @section acc_ctrl_unit_test 4. Unit Test Usage
 * The Ambarella IR process library includes three unit tests:
 * - test_blade_runner
 * - test_sl_liveness_v2
 *
 * The `test_blade_runner` generates the disparity, depth, and point cloud, and
 * performs the liveness test based on the specified ROI. Users can refer to
 * this demo to understand this library.
 *
 * The `test_sl_liveness_v2` runs the face detection algorithm MTCNN and the
 * face recognition algorithm MobileFaceNet, along with the liveness test.
 *
 * @subsection acc_ctrl_unit_test_cfg 4.1 Configuring the Parameters
 * Before running the unit test demo, users must configure the following
 * device-related parameters by converting them to meters:
 * - The real focal length (m) / sensor pixel size (m)
 * - Baseline (m)
 * - Center offset (x / y) (pixels)
 * - Reference frame distance (m)
 *
 * This library uses the following focal length: real_focal_length (m) /
 * sensor_pixel_size (m). Information generated by Ambarella’s calibration
 * tools is located in the following file:
 * `/usr/share/ambarella/calib_mono/fov1.json`.
 *
 * Users can determine the reference frame distance from the file name. For
 * example, if the reference YUV data name is
 * `ref_b0_0_canvas0_1920x1080_0.8.yuv`, the reference frame distance is
 * “0.8 m”.
 *
 * If there is not a distance number in the filename, users can interpret the ID
 * between H1912060001 ~ H1912060010 as “1.1 m” and “ID >= H1912060011” as
 * “0.8 m”.
 * @note
 * Users can capture a new frame by following the steps for camera
 * calibration in the Section @ref acc_ctrl_ref_cap "6. Reference Capture".
 *
 * The script file `/usr/local/bin/gen_board_config.sh` integrates these
 * calculations. This script file provides an easy method to initialize
 * parameters during the evaluation stage. Output parameters are generated when
 * the `/usr/share/ambarella/calib_mono/board_config` file is created.
 *
 * The following example demonstrates how to obtain parameters from a Janus
 * calibration. (The Vision+ EVK follows the same process):
 * @code {c}
 * board # cat /usr/share/ambarella/calib_mono/fov1.json
 * {"version":1,"generated-by":"CTB 4.6.29382","time":"2019-Dec-09 18:41:43",
 * "name":"fov1","id":"1","params":{"model":"pinhole","ku":817,"kv":817,
 * "u0":959.5,"v0":517.89999999999998,"w":1920,"h":1080},"position":[0,0,0,0,-0,0],
 * "relative-to": "-","src-params":{"model":"kannala-brandt","ku":950.7136530619706,
 * "kv":950.7136530619706,"u0":940.94117891765529,"v0":523.62050365128425,
 * "w":1920,"h":1080,"lens-model":"brown-conrady","dc":[1.28873114001354741e-04,-5.74621130511462626e-04],
 * "kd":[8.01211810077433889e-02,7.31375685226345364e-03,3.32111311321012974e-03]},
 * "src-params-uncertainty":{"model":"kannala-brandt","ku":0.096290835325604646,
 * "kv":0.096290835325604646,"u0":0.07855489443337979,"v0":0.061336162934196442,
 * "w":0,"h":0,"lens-model":"brown-conrady"},
 * "src-orientation":[0.00000000000000000e+00,0.00000000000000000e+00,0.00000000000000000e+00],
 * "src-position":[0.00000000000000000e+00,0.00000000000000000e+00,0.00000000000000000e+00],
 * "fov":[-1.11100949331228782e+00,-8.02715335971528554e-01,1.17702690362275231e+00,8.28458032121773269e-01],
 * "vsync":0.00000000000000000e+00,"fitting":7.48930349946022034e-02,"fitting_max":4.19740349054336548e-01}#
 * @endcode
 *
 * For the pinhole model result in the example above, ku / kv is the
 * focal_length, which is equal to the real_focal_length(m) /
 * sensor_pixel_size(m); u0 is the center_x; and v0 is the center_y, which is
 * the lens center coordinate on the image.
 *
 * The following shows the resulting example parameters for the 1080P YUV data:
 * - focal_length = 817
 * - baseline = 0.04
 * - center_x = 959.5
 * - center_y = 517.899
 *
 * The following lists the formula for converting the parameters (for a new
 * resolution):
 * - scale_ratio = data_width_dst / data_width_src
 * - focal_length_dst = focal_length_src * scale_ratio
 * - baseline_dst = baseline_src
 * - center_x_dst = (center_x_src - src_offset_x) * scale_ratio
 * - center_y_dst = (center_y_src - src_offset_y) * scale_ratio
 *
 * @subsection acc_ctrl_test_encode 4.2 Unit_test: test_encode (New Parameters)
 * Users can change the structured-light frame rate accordingly, depending on
 * the algorithm speed. New options are added in test_encode. Users can refer
 * to `test_encode` and review the contents of `quick_ipc_for_access_control.sh`
 * and `/usr/share/ambarella/calib_mono/board_config`.
 *
 * The new parameters for the access control platform in test_encode:
 * <table>
 * <tr><th align="center"> Parameters                 <th align="center"> Features
 * <tr><td> custom-vinc-id                            <td> Specifies the VIN controller ID, which is 0 by default.
 * <tr><td> custom-flash-enable [0|1]                 <td> Specifies if this function is enabled.
 * <tr><td> custom-led-gpio                           <td> Specifies the output general purpose input / output (GPIO) to control the structured light.
 * <tr><td> custom-flash-time                         <td> Specifies the structured-light turn time for one frame. Set it to 5 for 5 ms. The current limit is 1 ms to 7 ms.
@note
If the access control platform is turned on for too long, it will overheat, which can damage the structured-light projector.
 * <tr><td> custom-structured_light_chan [0~2]        <td> Specifies the channel ID, which contains the structured-light pattern frames.
 * <tr><td> Custom-ir-led-chan [0~2]                  <td> Specifies the channel ID, which contains the IR LED pattern frames.
 * <tr><td> custom-chan-frame-ratio [0~10:0~10:0~10]  <td> Specifies the frame ratio on each channel in the format of channel 2’s ratio, channel 1’s ratio, and channel 0’s ratio. If channel 2 is not used, the value can be left as 0. If one of the non-structured-light channels shares the same frames as the other non-structured-light channel, its value can be left as 0.
@note
Update the idsp_fps for each channel in the IAV Lua script accordingly after changing this ratio value.
 * <tr><td> custom-ir-led-gpio                        <td> Specifies the custom configuration for IR LED GPIO.
 * <tr><td> custom-ir-led-mode [0|1|2]                <td> Specifies the custom configuration for the IR LED work mode:<br> 0: off, 1: always on, 2: light-on interleave with structured light.
 * <tr><td> custom-ir-led-time                        <td> Specifies the IR LED enabled duration in ms on the non-structured-light frame.
 * <tr><td> custom-flash-latency-plus1                <td> Specifies the flash latency after EOF irq. 0: auto, others: (x-1) ms.
 * <tr><td> custom-flash-led-trigger-once             <td> Manually triggers the custom configuration of the LED once, when the custom frame pattern = 0.
 * <tr><td> custom-flash-led-line-offset              <td> Specifies the custom configuration of the LED flash line offset based on VIN height.
 * <tr><td> custom-update-flash-time [1~10]           <td> Updates the custom configuration of the LED flash in ms.
 * <tr><td> custom-flash-min-time                     <td> Specifies the custom configuration of the LED flash minimum time.
 * </table>
 * @note
 * Some physical parameters, such as `custom-led-gpio`, `custom-ir-led-gpio`,
 * `custom-flash-time`, and `custom-ir-led-time`, have been defined in the device
 * tree (DTS) files by default, however, these parameters can still be
 * updated with the test_encode option on the fly.
 *
 * @subsection acc_ctrl_test_aaa_service 4.3 Unit_test: test_aaa_service (New Parameters)
 * <table>
 * <caption>New Parameters of test_tuning for Access Control LED Control.</caption>
 * <tr><th align="center"  width="150px"> Short Options   <th align="center"  width="200px"> Long Options    <th align="center"> Usages
 * <tr><td> -p              <td> --product_cfg   <td> Specifies the product Lua path; the default Lua path is `/usr/share/ambarella/idsp/product_id_authen.lua`. The product Lua specifies the virtual type for each channel.
 * <tr><td> -m              <td> --ai_metering   <td> Enables the AI metering mode
 * </table>
 *
 * @subsection acc_ctrl_test_blade_runner 4.4 Unit_test: test_blade_runner
 * The `test_blade_runner` includes the depth generation-associated functions.
 *
 * @subsubsection acc_ctrl_tbr_intro 4.4.1 Introduction to test_blade_runner
 * <table>
 * <caption>test_blade_runner Usages.</caption>
 * <tr><th align="center" width="150px"> Short Options   <th align="center" width="200px"> Long Options    <th align="center"> Usages
 * <tr><td> -t    <td> --source-type          <td> Sets the live input data source type = canvas_buffer / pyramid_buffer,0=canvas_buffer, 1=pyramid_buffer.
 * <tr><td> -i    <td> --source-id            <td> Sets the live input data canvas / pyramid ID, canvas_buffer 0: Main / 1:Second / 2:Thrid / 3:Fourth / 4:Fifth; pyramid layer 0 / 1 / 2 / 3 / 4 / 5.
 * <tr><td> -s    <td> --stream-id            <td> Displays on the encode stream. Sets the stream ID, [0:1:2...]
 * <tr><td> -r    <td> --ref-yuv              <td> References the YUV file path.
 * <tr><td>       <td> --ref-info             <td> References the YUV file width, height, and pitch.
 * <tr><td> -o    <td> --ref-offset           <td> References the YUV file offset; value ~ [-1920, 1920].
 * <tr><td> -m    <td> --smooth               <td> Blade Runner disparity smoothness. The value must be > = 1.
 * <tr><td> -g    <td> --range                <td> Blade Runner disparity data range. The value must be > = 1.
 * <tr><td> -n    <td> --min                  <td> Blade Runner min disparity.
 * <tr><td>       <td> --data-roi             <td> ROI of the live YUV data. The format = x, y, w, h.
 * <tr><td> -f    <td> --focal-length         <td> Sets the focal length, focal_length = focal_length_real / sensor_pixel_size, and then crops / resizes the image from the 1080p input, focal_length = focal_length * resize_dst_w / crop_w.
 * <tr><td> -b    <td> --baseline             <td> Sets the baseline. The units are in meters.
 * <tr><td> -d    <td> --ref-dist             <td> Sets the ref_distance. The units are in meters.
 * <tr><td> -x    <td> --cx                   <td> Sets the reference data center_x. It crops and resizes the image from the 1080p input, center_x = (center_x - crop_start_x) * resize_dst_w / crop_w.
 * <tr><td> -y    <td> --cy                   <td> Sets the reference data center_y. It crops and resizes the image from the 1080p input, center_y = (center_y - crop_start_y) * resize_dst_h / crop_h.
 * <tr><td> -e    <td> --rotate               <td> Sets the rotate to 0, 1, 2. 0:no_rotate / 1:rotate_90_clockwise / 2:rotate_270_clockwise.
 * <tr><td> -M    <td> --mode                 <td> Sets the mode, which can be 0 / 1 / 2 / 3. The default is 0. When facing the camera module, the coordinate (0,0) is the lens. If the structured-light projector is at the x-negative position: mode = 0/2 and rotate = 0. If the structured-light projector is located at the y-positive position: mode = 0/2 and rotate = 1. If the structured-light projector is at the x-positive position: mode = 1/3 and rotate = 0. If the structured-light projector is at the y-negative position: mode = 1/3 and rotate = 1. Compared to mode 0 / 1, mode 2 / 3 has better depth quality but introduces more noise for invalid pixels.
 * <tr><td>       <td> --flash-start-offset   <td> Structured-light flash starts the offset in lines for the dynamic mode. The range is: [-(VIN height), (VIN height)].
 * <tr><td>       <td> --flash-start-ratio    <td> Structured-light flash starts the multiplier ratio for the dynamic mode. This value is equal to (VIN height) / (the height of structured-light main buffer).
 * <tr><td>       <td> --save-data-path       <td> Saves the data path.
 * <tr><td>       <td> --save-dsi-num         <td> Saves the disparity uint8 frame number.
 * <tr><td>       <td> --save-dsi16-num       <td> Saves the disparity int16 frame number.
 * <tr><td>       <td> --save-depth-num       <td> Saves the depth frame number.
 * <tr><td>       <td> --save-pcd-num         <td> Saves the point cloud frame number.
 * <tr><td>       <td> --live-roi             <td> Sets the liveness test ROI, which must be smaller than the disparity size.
 * <tr><td>       <td> --min-max-dist         <td> Sets the liveness test face distance range.
 * <tr><td>       <td> --min-max-height       <td> Sets the liveness test face height range.
 * <tr><td>       <td> --min-max-dsi-ratio    <td> Sets the liveness test face ratio range.
 * <tr><td>       <td> --face-th              <td> Sets the liveness test face threshold.
 * <tr><td>       <td> --depth-display        <td> Draws the depth map on the overlay. 0=disable, 1=enable. The default is enabled.
 * <tr><td> -v    <td> --verbose              <td> Shows the verbose information.
 * </table>
 *
 * @note
 * - -t and -i specify the YUV source buffer; in the default Lua configuration file, it must be canvas buffer 0 for 1920x1080.
 * - -s specifies the stream ID. The result of disparity data will draw on that stream; the output disparity size must be less than the stream size.
 * - -r sets the path of the reference YUV file; the typical file is the 1080P YUV data path. "--ref-info" describes the resolution of the YUV file. For the 1920x1080 resolution, the description is"--ref-info 1920,1080,1920". The resolution is the same as the input buffer specified by -t and -i.
 * - -o specifies the offset of the input YUV data: 0 is for general cases. It can change the min-max range of the structured-light module based on the current reference frame. For example, if the current detection range is 0.2 m~1.0 m, set this value to a larger number, as 5 can adjust the detection range to 0.3 m~1.5 m.
 * - -m sets the smoothness of the disparity data. “-m” must be greater than 1, and vary according to different YUV resolutions—a large resolution must have a larger value. Smaller values result in a greater sharpness disparity map.
 * - -g sets the maximum 16-bit disparity, which must be greater than 1. The maximum output disparity value equals the value multiplied by 16.
 * - -n sets the minimum 16-bit disparity value. The typical value is zero.
 * - -e sets the rotation for input data, of input data, and for reference data. It could be 0, 1, or 2, with 0 for no rotate, 1 for rotate 90-degrees clockwise, 2 for rotate 270-degrees clockwise (90 counterclockwise).
 * - -M sets the algorithm mode. It is reserved and set to 0.
 * - --data-roi sets the ROI based on the YUV data; with parameter x_offset, y_offset, width, and height, the offset can set the start position on the reference YUV data. The width and height are the output disparity data resolution.
 * - -f -b -d -x -y sets the focal length, baseline, reference frame distance, center_x, and center_y. For parameters, refer to Section @ref acc_ctrl_unit_test_cfg.
 * - --save-data-path specifies the path to the output data.
 * - --save-dsi-num specifies the number of saved 8-bit disparity frames. The format is uint8, for any range of -g specified value, and its normalized range will always be 0-255. The resolution is the resolution of the disparity data.
 * - --save-dsi16-num specifies the number of saved frames. The data format is 16-bit fixed-point data with the sign bit=1 and the expoffset bits = 4. Users can read the data by int16, then divide by 2^4=16; the maximum value can be specified by the -g option. After dividing by 16, if a -1 is returned, then the pixel is invalid and the resolution is the disparity data resolution.
 * - --save-depth-num specifies the number of saved depth frames. The output data format is a 32-bit floating point, and the unit is one meter for each pixel. Users can read the data by the float pointer in C code, and the resolution is the disparity data resolution.
 * - --save-pcd-num specifies the number of saved point cloud frames. The output is in the pcd file format, with a header and a binary, including x, y, and z coordinates in 32-bit floating point. The binary output data size without the header = total_valid_pixel * 3 * sizeof (float); users can install pcl_viewer in Linux, which reads and automatically shows the pcd file in a three-dimensional point cloud.
 * - --live-roi specifies a region of interest for the liveness test. If the disparity data includes the full FoV of the image, the ROI can be a small region of the disparity data. If the disparity data is already the ROI of the human face, it can be close but not equal to the disparity data. The ROI for the liveness test must always be smaller than the disparity resolution to account for the black border of the disparity data.  The border width is equal to the value in the -m parameter. If users want to calculate the disparity data for the face ROI based on the 1080P reference YUV, the command of --data-roi can be used to define the ROI region.  After the ROI is assigned, the disparity calculation will be applied on the specified area only, which dramatically decreases the calculation time compared to generating the depth for the entire image.  However, the output of the blade_runner depth image will always have a blank border at the edge of the image.  In order to avoid these blank borders, expand the --data-roi first to calculate a larger image.  After the depth image is generated, the blank borders then can be cropped from the output data.  The border size is equal to the value specified by the -m option.  Ambarella suggests expanding the ROI’s border (x - border_width, y - border_width, w + 2*border_width,h+2*border_width) by several pixels (equal to the value of -m) to calculate the disparity or depth, and then run the liveness test with a smaller resolution on the output disparity (without the black border).
 * - --min-max-dist is used for the liveness test and sets the min / max distance for the liveness test. The face distance out of range returns -1 if the distance of the face is out of range.
 * - --min-max-height is used for the liveness test and sets the min / max of the real face height. The typical range setting is 0.15 m-0.3 m.
 * - --min-max-dsi-ratio is used for the liveness test and sets the min / max disparity ratio of the liveness ROI. If the valid pixels / total pixels are not within the specified range, an “out of range” message is returned.
 * - --face-th is used for the liveness test and sets the threshold. A value of 0.999 is typical.
 *
 * @subsubsection acc_ctrl_tbr_demo 4.4.2 Capture the Disparity, Depth, and Point Cloud Data
 * Because the FoV of the access control sensors exceeds the FoV of
 * the structured-light projector, the valid FoV only covers approximately
 * two-thirds of the full sensor FoV. Users can only obtain 1280x720 and
 * 1280x1000 disparity or depth image from Janus and Vision+, respectively,
 * if the 1080P YUV data is used as the reference frame. Users can obtain the
 * focal length baseline and center_x / center_y directly from the
 * `calib_mono/fov1.json` file.
 *
 * The following examples show the sample commands for running
 * `test_blade_runner`. Some hardware parameters are not universal to other
 * boards. See the printouts of
 * `/usr/local/bin/blade_runner_run_depth_capture.sh` for parameters dedicated
 * to a personal board.
 *
 * For CV25M Janus:
 * @code {c}
 * board # test_blade_runner -t 0 -i 0 -s 0 -r /usr/share/ambarella/calib_mono/ref_b0_0_canvas0_1920x1080_0.8.yuv --ref-info 1920,1080,1920 -o 0 -m 11 -g 4 -n 0 -f 817 -b 0.04 -d 0.8 -x 959.5 -y 517.899 --data-roi 360,180,1280,720 -e 1 --save-dsi16-num 1 --save-depth-num 1 --save-pcd-num 1
 * @endcode
 * For CV22 Vision+:
 * @code {c}
 * board # test_blade_runner -t 0 -i 0 -s 0 –r /usr/share/ambarella/calib_mono/ref_b0_H210615A001_canvas0_1920x1080_NV12_0.816.yuv --ref-info 1920,1080,1920 -o 21 -m 13 -g 4 -n 0 -M 2 -f 764 -b 0.05 -d 0.816 -x 958 -y 522 --data-roi 320,0,1280,1000 -e 1 --save-dsi16-num 1 --save-depth-num 1 --save-pcd-num 1
 * @endcode
 *
 * @image html acc_ctrl_test_blade_runner.png Figure 4-1. Capturing the Disparity, Depth, and Point Cloud Data.
 * <br>
 * The following three files are generated:
 * - `disparity_xxxxx_1frame_int16.4_xxxxx_2560.bin`<br>
 *    Includes the disparity data: Each pixel has 16 bits; the resolution is
 *    1280x720 (Janus) or 1280x1000 (Vision+), the pitch=2560, fix point /
 *    signed / 16 bit / 4 fractional bits, and the data_format=(1, 1, 4, 0).
 *    <br>
 *    Users may look up the disparity map file via the `Vooya` application in
 *    Linux. Set the format as follows: color space = single channel; data
 *    container = single integer; and bit depth = 12 bit.
 * - `depth_xxxxx_1frame_fp32_xxxxxx_5120.bin`<br>
 *    Includes the depth data: Each pixel has a 32-bit floating point
 *    representing the distance to the lens center plane. The resolution is
 *    1280x720 (Janus) or 1280x1000 (Vision+); pitch=5120; and the
 *    data_format=(1, 2, 0, 7).
 *    Users may look up the disparity map file via the `Vooya` application on
 *    Linux. Set the format as follows: color space = single channel, data
 *    container = single float (32bit).
 * - `point_cloud_xxxxx_frame1_165327_points.pcd`<br>
 *    Includes the point cloud data (PCD) format: A total of 165327 points.
 *    Users can open the three-dimensional point clouds using pcl_viewer on
 *    Ubuntu.
 *
 * @note
 * The data format shown in the parentheses above (such as 1, 1, 4, 0) is the
 * vector to represent the corresponding output data format, and the meaning is
 * as shown below.
 * - 1st argument: 0 is unsigned, 1 is signed.
 * - 2nd argument: 0 refers to 8 bits, 1 is 16 bits, 2 is 32 bits.
 * - 3rd argument: The exponent offset.
 * - 4th argument: Number of bits reserved for the exponent field. 0 indicates a fixed point number.
 *
 * @subsection acc_ctrl_test_sl_liveness 4.5 Unit_test: test_sl_liveness_v2
 * The `test_sl_liveness_v2` includes the face detection, face recognition, and
 * liveness tests. Each algorithm is defined in an individual thread, which
 * provides the modular design to the software. Moreover, some data queues are
 * designed to connect these threads to a program flow.
 *
 * @subsubsection acc_ctrl_tsll_v2_intro 4.5.1 Introduction of test_sl_liveness_v2
 * <table>
 * <caption>test_sl_liveness_v2 Usages.</caption>
 * <tr><th align="center"  width="150px"> Short Options  <th align="center"  width="200px"> Long Options  <th align="center"> Usages
 * <tr><td> -m   <td> --run_mode          <td> Run mode. 0=live, 1=dump, 2=replay.
 * <tr><td> -i   <td> --input_dir         <td> Path to the folder containing the model binaries (pnet*.bin, rnet.bin, onet.bin, mfacenet.bin), database binary (database.bin), etc.
 * <tr><td> -o   <td> --output_dir        <td> Path to the folder that will save the generated files
 * <tr><td> -n   <td> --max_loop          <td> Loop count to run. -1 means the endless loop.
 * <tr><td> -l   <td> --log_level         <td> Log level 0=None, 1=Error, 2=Notice, 3=Debug, 4=Verbose.
 * <tr><td> -t   <td> --measure_time      <td> Measure time flags in order of im, fd, fr, sl, vl, and main threads. For example, 1,0,0,0,0,0.
 * <tr><td> -b   <td> --fd_canvas         <td> RGB canvas parameters in order of id,roi_x,roi_y,roi_w,roi_h. The parameters roi_* are ROI in the canvas.
 * <tr><td> -p   <td> --ld_canvas         <td> IR structured-light canvas parameters in order of id,roi_x,roi_y,roi_w,roi_h. The parameters roi_* are ROI in the canvas.
 * <tr><td> -s   <td> --stream            <td> Stream parameters in order of id,roi_x,roi_y,roi_w,roi_h. The parameters roi_* are ROI in the stream.
 * <tr><td> -e   <td> --max_face_num      <td> Maximum face number to detect with the area priority.
 * <tr><td> -g   <td> --fr_thres          <td> FR threshold.
 * <tr><td>      <td> --fd_area_thresh    <td> FD area threshold to multiply 96x112.
 * <tr><td>      <td> --sl_temperature    <td> Sets the maximum temperature of structured light in Celsius (0~70). If the current temperature exceeds the maximum value, structured light will not be lit up in dynamic mode.
 * <tr><td>      <td> --sl_wait_ms        <td> The time, in milliseconds, to wait after the structured light is enabled and until the IR pattern buffer is placed into the IDSP pipeline.
 * <tr><td>      <td> --ref_yuv_path      <td> The reference YUV file path for the Blade Runner.
 * <tr><td>      <td> --ref_w_h_pitch     <td> The shape of the reference YUV file in the order of width, height, and pitch.
 * <tr><td>      <td> --ref_dist          <td> The distance of reference YUV captured.
 * <tr><td>      <td> --baseline          <td> The baseline of sensor module.
 * <tr><td>      <td> --depth_algo_type   <td> Select the depth algo, 0=blade_runner, 1=fbm. Default is 0.
 * <tr><td>      <td> --calc_full_depth   <td> The flag to calculate the depth of the full image for liveness detection.
 * <tr><td>      <td> --blade_runner_config <td> The parameters for blade runner depth configuration in the order of rotate, mode, disp_range, disp_smooth,disp_min_value, ref_offset, verbose.
 * <tr><td>      <td> --fbm_config        <td> The parameters for Fast Block Match configuration in the order of maxspecklesize,maxspecklediff, sad_win_size, sad_thresh, uniqueratio, texture_threshold, disparity_num, min_disparity, detect_near_depth, detect_far_depth.
 * <tr><td>      <td> --liveness_config   <td> The parameters for blade runner liveness configuration in the order of min_face_dsi_ratio, max_face_dsi_ratio,min_face_3d_height, max_face_3d_height, min_face_distance, max_face_distance, face_threshold.
 * <tr><td>      <td> --font_scale        <td> The font scale to draw the text with the OpenCV API.
 * <tr><td>      <td> --depth_display     <td> Draw the depth map on the overlay, 0=disable, 1=enable. The default is enabled.
 * <tr><td>      <td> --door_control      <td> Run /usr/local/bin/open_the_door.sh to open the door. Not yet implemented.
 * <tr><td>      <td> --video_record      <td> Run /usr/local/bin/record_video.sh to record the video. Not yet implemented.
 * <tr><td>      <td> --access_led        <td> The access LED configuration in order of GPIO ID, delay times in ms before the no-access to LED is on, and the timeout to close in ms. Not yet implemented.
 * <tr><td>      <td> --no_access_led     <td> The "no access" LED configuration in order of GPIO ID, delay times in ms before access to LED is on, and the timeout to close in ms. Not yet implemented.
 * <tr><td>      <td> --access_sensitive  <td> The access sensitive of status-holding threshold counted in frames to filter access events in order of active / inactive. Not yet implemented.
 * <tr><td>      <td> --ai_metering       <td> Enables AI metering method and send face ROI to 3A application. 0=disable, 1=enable. The default is disabled.
 * <tr><td>      <td> --ini_config        <td> Path to the ini configuration file.
 * <tr><td>      <td> --lens_config       <td> The parameters for lens configuration in the order of focal_length, center_x, center_y.
 * </table>
 *
 * @subsubsection acc_ctrl_tsll_v2_demo 4.5.2 Run the Face Detection, Face Recognition, and Liveness Test Demo
 * The following examples show sample commands for running the
 * `test_sl_liveness_v2`. Some hardware parameters are not universal to other
 * boards. See the script `/tmp/run_ipc_folder/sl_run_liveness_demo_v2.sh`
 * generated by `quick_ipc_for_access_control.sh` for parameters dedicated to
 * the personal board.
 *
 * For CV25M Janus:
 * @code {c}
 * board # test_sl_liveness_v2 --ini_config /usr/share/ambarella/sl_liveness/liveness_v2_config.ini \
 *     -b 4,0,0,1280,720 \
 *     -p 0,320,160,1280,720 \
 *     -s 1,320,160,1280,720 \
 *     --ref_yuv_path /usr/share/ambarella/calib_mono/ref_b0_H1912060058_canvas0_1920x1080_NV12_1.524.yuv --ref_w_h_pitch 1920,1080,1920 \
 *     --ref_dist 0.8 --baseline 0.04 --calc_full_depth 0 \
 *     --lens_config 766,957,540 \
 *     --blade_runner_config 1,0,6,13,0,23,0
 * @endcode
 *
 * For CV22 Vision+:
 * @code {c}
 * board # test_sl_liveness_v2 --ini_config /usr/share/ambarella/sl_liveness/liveness_v2_config.ini \
 *     -b 4,0,0,1280,1000 \
 *     -p 0,320,0,1280,1000 \
 *     -s 1,320,0,1280,1000 \
 *     --ref_yuv_path /usr/share/ambarella/calib_mono/ref_b0_H210802A036_canvas0_1920x1080_NV12_0.798.yuv --ref_w_h_pitch 1920,1080,1920 \
 *     --ref_dist 0.8 --baseline 0.04 --calc_full_depth 0 \
 *     --lens_config 766,957,540 \
 *     --blade_runner_config 1,0,6,13,0,23,0
 * @endcode
 *
 * @subsection acc_ctrl_test_calib_deviation 4.6 Unit_test: test_calibrate_deviation
 * The `test_calibration_deviation` evaluates the dewarp result
 * (`calib_mono/fov1.bin`). It analyzes a YUV file that contains a chess board
 * object. The algorithm inside calculates whether or not the lines of the
 * chess board are straight enough.
 *
 * @subsubsection acc_ctrl_tcd_intro 4.6.1 Introduction to test_calibrate_deviation
 * <table>
 * <caption>test_calibrate_deviation Usages.</caption>
 * <tr><th align="center"  width="150px"> Short Options  <th align="center"  width="200px"> Long Options  <th align="center"> Usages
 * <tr><td> -f    <td> --yuv-path            <td> Specifies the YUV file's path.
 * <tr><td> -r    <td> --yuv-info            <td> Specifies the YUV file's width and height. The default is 1920x1080.
 * <tr><td> -c    <td> --chess-board-info    <td> Specifies the chess board's columns and rows. The default is 8x6.
 * <tr><td> -t    <td> --point-dist-thres    <td> Specifies the threshold of distance between the chess board corner point and the regression line in pixels. The default is 1.0.
 * </table>
 *
 * @subsubsection acc_ctrl_tcd_demo 4.6.2 Run the Calibration Deviation to Check the Demo
 * The following shows the command for the calibration deviation to check the
 * demo. The chess board information must be specified depending on the chess
 * board dimension captured in the YUV file.
 * @code {c}
 * board # test_calibrate_deviation -f /tmp/chessboard.yuv -r 1920x1080 -c 8x6 -t 1
 * @endcode
 *
 * @subsection acc_ctrl_test_sl 4.7 Unit_test: test_structured_light
 * The `test_structured_light` evaluates the quality and orientation of the
 * structured-light projector. It scans the structured-light pattern image and
 * calculates the coverage of the structured-light pattern in the provided ROI.
 *
 * @subsubsection acc_ctrl_tsl_intro 4.7.1 Introduction to test_structured_light
 * <table>
 * <caption>test_structured_light Usages.</caption>
 * <tr><th align="center" width="150px"> Short Options  <th align="center" width="200px"> Long Options  <th align="center"> Usages
 * <tr><td> -f    <td> --yuv-path               <td> Specifies the YUV file's path.
 * <tr><td> -r    <td> --yuv-info               <td> Specifies the YUV file's width and height. The default is 1920x1080.
 * <tr><td> -d    <td> --data-roi               <td> Specifies the ROI area. The default is 0,0,1920,1080.
 * <tr><td> -w    <td> --weber-contrast-thres   <td> Specifies the Weber contrast threshold of the individual subareas (4x4 or 16x16 pixels). The default is 0.5.
 * <tr><td> -s    <td> --sl-coverage-thres      <td> Specifies the structured-light coverage threshold of the ROI area. The default is 0.99.
 * </table>
 *
 * @subsubsection acc_ctrl_tsl_demo 4.7.2 Run the Structured Light Test to Check the Demo
 * The following shows the command for the structured light test to check the demo.
 * The test takes a YUV file as an input and evaluates the coverage of the
 * structured-light pattern in a defined ROI area.
 * @code {c}
 * board # test_structured_light -f /tmp/reference.yuv -r 1920x1080 -d 320,160,1280,720 -w 0.5 -s 0.9
 * @endcode
 *
 * @subsection acc_ctrl_test_ref_yuv 4.8 Unit_test: test_reference_yuv
 * The `test_reference_yuv` is a tool that evaluates the quality of the reference
 * YUV file taken in the calibration process. It receives a YUV input with a
 * structured-light pattern and checks whether the pattern has sufficient
 * contrast between the structured-light dots and the background.
 *
 * @subsubsection acc_ctrl_try_intro 4.8.1 Introduction to test_reference_yuv
 * <table>
 * <caption>test_reference_yuv Usages.</caption>
 * <tr><th align="center" width="150px"> Short Options  <th align="center" width="200px"> Long Options  <th align="center"> Usages
 * <tr><td> -f    <td> --yuv-path             <td> Specifies the YUV file's path.
 * <tr><td> -r    <td> --yuv-info             <td> Specifies the YUV file's width and height. The default is 1920x1080.
 * <tr><td> -a    <td> --intensity-range      <td> Specifies the average intensity range. The default is 0,255.
 * <tr><td> -c    <td> --contrast-theshold    <td> Specifies the contrast threshold. The default is 0.
 * </table>
 *
 * @subsubsection acc_ctrl_try_demo 4.8.2 Run the Reference YUV to Check the Demo
 * The following shows the command for the reference YUV to check the demo. It
 * calculates the intensity and contrast of the reference YUV file, and then
 * evaluates the quality of the captured reference YUV.
 * @code {c}
 * board # test_reference_yuv -f /tmp/reference.yuv -a 30,100 -c 500
 * @endcode
 *
 * - - - -
 *
 * @section acc_ctrl_len_calib 5. Lens Calibration
 * @subsection acc_ctrl_mon_calib_tool 5.1 Mono Calibration Tool Version
 * The table below shows the release history of the mono calibration tool.
 * If the current calibration tool is not available, contact the Ambarella
 * support team for the latest version.
 *
 * <table>
 * <caption>Mono Calibration Tool Version Table.</caption>
 * <tr><th align="center"> Mono Calibration Tool Version <th align="center"> Updated Date <th align="center"> Modification
 * <tr><td> cv2x_sdk_2.5_mono_v231_20200713   <td> 20200713   <td> Initial release of mono calibration
 * </table>
 *
 * @subsection acc_ctrl_calib_pkg_install 5.2 PC Environment Setup
 * This section provides information for installing the AmbaCalib tool to
 * calculate the warp table.
 * -# Prepare the PC with Ubuntu version 18.04 installed.
 * -# Download the latest mono calibration package.
 * -# Run the commands below to install the AmbaCalib tool.
 *    @code {c}
 *    build # sudo dpkg -i ambacalib-<VERSION>.deb
 *    build # sudo apt install -f
 *    @endcode
 *
 * @note
 * - AmbaCalib enables the lens distortion parameters to be calculated and generated into the warp table in order to remove the distortion.
 * - By default, NV12 YUV images with the resolution of 1920x1080 are selected. To specify another resolution, use the following parameter: -r 1920 1080.
 * - Use the option `-i <NAME> <imagelist>` to specify the first master image list and the slave image list, respectively.
 * - Use wildcard `%0xd` in the image list to select all images.
 * - Use the option `-o Calibfolder` to override the output folder.
 *
 * @subsection acc_ctrl_calib_board 5.3 Calibration Board Preparation
 * Ambarella recommends that users print directly on a flat and rigid particle board
 * or a medium-density fireboard to manufacture the calibration target. Because
 * manufacturing tolerance can affect the dot spacing, a direct measurement of
 * the actual board width and height must be performed. To perform this
 * measurement, users must measure the space between the reference markers on
 * the border of the grid, both in the vertical and horizontal directions. The
 * illustration below shows an enlarged view of the top part of the circle
 * target, with the reference marker positions highlighted.
 *
 * After measuring the width and height, as demonstrated in the figure, the
 * numbers (divided by horizontal / vertical grids) must be entered into the
 * calibration initiation file. For example, if the width / height is 110.3 cm
 * / 76.4 cm, the spacing is HSPACE = 110.3cm / 46, VSPACE = 76.4cm / 32 in
 * .ini files (such as `calibtool_mono_pinhole.ini`).
 *
 * [SECTION 3]<br>
 * &emsp; HSPACE = 0.023978<br>
 * &emsp; VSPACE = 0.023875<br>
 * [END]
 *
 * @note
 * The calibration target images and calibtool_mono_pinhole files can be found
 * in the calibrate_targets folder and profiles folder respectively within the
 * calibration tool package. The section number in the
 * `calibtool_mono_pinhole.ini` file must match the calibrated target’s index.
 *
 * @image html acc_ctrl_calib_board.png Figure 5-1. Calibration Board.
 *
 * @subsection acc_ctrl_gen_warp_table 5.4 Warp Table Generation
 * This section provides instructions for capturing the RGB YUVs and calculating
 * the warp table.
 * -# Generate the board_config for the calibration, followed by the device’s
 *    module number:
 *    @code {c}
 *    board # gen_board_config.sh /usr/share/ambarella/calib_mono H1912060001
 *    @endcode
 * -# Run `quick_ipc_for_access_control.sh` followed by the board’s module ID
 *    to initialize the access control EVK board. Use VLC to open
 *    `rtsp://10.0.0.2/stream2` during the YUV capturing stage.
 *    @code {c}
 *    board # quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720
 *    @endcode
 * -# Insert an SD card and create a new folder with the name of the module ID.
 *    From this folder, run `calib_capture.sh H1912060001 0 16` to capture 17
 *    YUV files. The data will be stored in the `mono_yuv` folder under the
 *    current path. Ensure that at least one rectangular tag appears in the
 *    FoV, and that the YUV images cover all regions of the full FoV.
 *    @image html acc_ctrl_calib_capture.png "Figure 5-2. Capture the YUV File from the RGB Channel for Lens Calibration."
 * -# Copy the `mono_yuv` folder to the PC and run AmbaCalib. Ensure that
 *    `calibtool_mono_pinhole.ini` and `calibtool_mono_pinhole.cas` are placed
 *    under the mono_yuv folder. These two files can be found in the profile
 *    folder in the calibration tool package. Then, run the command (seen in
 *    the box on the following page) on the PC.
 *    The sensor name below (`warp_<resolution>`) must be renamed to end with
 *    the correct resolution; for example, `warp_1080p` for the Janus board,
 *    and `warp_2160p` for the Vision+ board. Additionally, the resolution
 *    below must match the YUV input; for example, 1920x1080 for the Janus
 *    board, and 3840x2160 for the Vision+ board.
 *    @code {c}
 *    host $ mkdir -p calib_mono && /opt/amba/bin/calibtool calibtool_mono_pinhole.ini \
 *        -iwarp_<resolution> %d/mono_1920x1080_nv12_0000000000.yuv_canvas1_1920x1080_NV12.yuv \
 *        -x warp_<resolution> -t calib -o calib_mono/
 *    @endcode
 *    @note
 *    After the warp table is successfully generated, the fitting error
 *    parameters are printed out on the terminal. Ensure that the values are
 *    less than 0.2 sqm to achieve a favorable dewarp result. If the values
 *    exceed 0.2 sqm, the user must recapture the YUV files.
 * -# Add the `readme.txt` in the `calib_mono` folder to track the calibration
 *    data.
 *    @code {c}
 *    host $ cat calib_mono/readme.txt
 *    This warp table is used for access control EVK module H1912060001
 *    @endcode
 * -# Generate SHA256 for the warp table files.
 *    @code {c}
 *    host $ sha256sum -b calib_mono/warp_* >> calib_mono/calib_data_sha256.txt
 *    @endcode
 * -# Copy the `calib_mono` folder to the access control board
 *    `/usr/share/ambarella` folder, and ensure that the `warp_<resolution>.bin`
 *    and `warp_<resolution>.json` files are located in
 *    `/usr/share/ambarella/calib_mono/`.
 * -# Reboot the system and run
 *   `quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720`. Use VLC
 *    to open `rtsp://10.0.0.2/stream2`.
 * -# Place the camera so that it is facing the chessboard image, as shown
 *    below, and then capture the YUV image.
 *    @code {c}
 *    board # test_yuvcap –b 1 –Y –F 2 –f /tmp/calib_dev –r 1
 *    @endcode
 *    @image html acc_ctrl_calib_deviation_image.png "Figure 5-3. Capture the YUV File from the RGB Channel for the Calibrate Deviation Check."
 * -# Evaluate the calibration deviation with `test_calibrate_deviation`. If
 *    the output deviation exceeds the threshold defined in the program option,
 *    a warning message will appear.
 *    @code {c}
 *    board # test_calibrate_deviation –f /tmp/calib_dev* -c 8x6 -t 3
 *        YUV file is /tmp/x_canvas1_1920x1080_NV12.yuv
 *        Point distance threshold is set to 3.000000
 *        Notice: calibrate deviation is acceptable. [max corner point deviation: 1.381636 pixels]
 *    @endcode
 *    @note
 *    If a different chessboard image is used, change the grid dimension option `-c`.
 *
 * - - - -
 *
 * @section acc_ctrl_ref_cap 6. Reference Capture
 * -# Run `quick_ipc_for_access_control.sh --rgb_sub_buf_out_res 1280x720` and
 *    then `ref_capture_init.sh`. After the reboot, the image will be tuned to
 *    best fit the current ambient light conditions, and the warp table in
 *    `calib_mono/warp_<resolution>.bin` will be enabled to remove the lens
 *    distortion.
 *
 *    To ensure that the YUV frame is captured with a structured-light pattern,
 *    open `rtsp://10.0.0.2/stream1` for the IR stream and
 *    `rtsp://10.0.0.2/stream2` for the RGB stream. Verify that the IR pattern
 *    is from stream 1. `ref_capture_init.sh` evaluates the current light
 *    environment and adjusts the structured-light flash time, shutter, and
 *    gain in order to find the best reference YUV under the current ambient
 *    light conditions. If the program cannot obtain the qualified reference YUV
 *    under the current light conditions, an error message will appear.
 *    @anchor acc_ctrl_ref_yuv_img
 *    @image html acc_ctrl_ref_yuv.png "Figure 6-1. Reference Data Quality."
 *
 *    Follow the instructions to change the ambient light. Further, ensure that
 *    there is no obstruction between the lens and the wall. For example, in
 *    @ref acc_ctrl_ref_yuv_img "Figure 6-1", (A) and (B) show quality images; however, (C)
 *    is unacceptable because the pattern is unclear.
 *
 *    Ensure that the setting is facing a white wall, the distance from the
 *    lens center to the wall is 0.8 meters, and that the sensor plane is parallel
 *    to the wall. Users must be able to see a cross on the center of stream 2.
 *    Draw a cross on the wall at the same height, and then place the sensor at
 *    0.8 m (the same height with the cross and vertical to the wall). Finally,
 *    adjust the orientation to ensure that the cross in stream 2 is aligned
 *    with the cross on the wall.
 *
 * -# Run the following command to capture the reference YUV file. The
 *    structured-light pattern coverage is checked. If its coverage is less
 *    than 85% of the cropped area, then the structured-light coverage may be
 *    insufficient or the orientation is incorrect. If either of these occur,
 *    the reference YUV file will not be captured.
 *    @code {c}
 *    board # ref_capture.sh /usr/share/ambarella/calib_mono H1912060001 0.8
 *    @endcode
 *    The first parameter is the path to the calib_mono folder, which is
 *    generated at the lens calibration stage (@ref acc_ctrl_gen_warp_table);
 *    the second parameter is the module ID; and the third parameter is the
 *    distance from the lens’ center to the wall. Ambarella recommends that
 *    users utilize a laser rangefinder to measure the distance for the third
 *    parameter.
 *
 *    Two YUV files will be captured and saved into the
 *    `/usr/share/ambarella/calib_mono folder`. One is 480x272(Janus) /
 *    480x376(Vision+) and the other is 1920x1080. Users can find the
 *    distance and module name in the YUV file name.
 *
 * -# After the capture is completed, back up the
 *    `/usr/share/ambarella/calib_mono` folder for each setting. To create a
 *    configuration file for the access control boards, run
 *    `gen_board_config.sh`.
 *    @code {c}
 *    board # gen_board_config.sh /usr/share/ambarella/calib_mono H1912060001
 *    @endcode
 *    The first parameter is the path to the `/usr/share/ambarella/calib_mono`
 *    folder, and the second parameter is the access control board’s module ID.
 *    After running the command, the user configuration settings
 *    will be created in `/usr/share/ambarella/calib_mono/board_config`.
 *
 * -# To verify the calibration and dewarp result, run
 *    `blade_runner_run_liveness_demo.sh`. Then open `rtsp://10.0.0.2/stream2`
 *    to check the depth map against the livestream.
 *
 * -# Back up the calibration data and reference data, then copy
 *    `calib_mono` to `/usr/share/ambarella/` by FTP after the firmware
 *    downloads.
 *
 * - - - -
 *
 * @section acc_ctrl_faq 7. FAQ
 * @subsection acc_ctrl_faq_q1 Question 1: How can frame rates of a structured light (SL) channel be increased?
 * <b>Answer:</b>
 * This can be achieved by changing VIN fps and the frame ratio on the SL
 * channel.
 *
 * VIN fps can be increased by the option of `vsrc_fps` in the
 * `quick_ipc_for_access_control.sh`. It increases the total number of frames
 * coming from the VIN sensor.
 *
 * Frame ratio can be configured by the parameter of `FRAME_RATIO` in
 * `/usr/share/ambarella/calib_mono/board_config` file. This parameter defines
 * how VIN frames are dispatched onto each channels.
 *
 * @subsection acc_ctrl_faq_q2 Question 2: What is dynamic mode? How is SL dynamic mode enabled?
 * <b>Answer:</b>
 * By default, the access control system starts from static mode. In this mode,
 * the structured light is always enabled on predefined SL frames. The time
 * sequence of frames outputting from each channel is static. The time when the
 * SL projector is triggered is also static.
 *
 * The option of `enable_dynamic_mode` for `quick_ipc_for_access_control.sh`
 * allows the access control system to start in dynamic mode. At this time,
 * there is no longer output on the SL channel,unless the SL-trigger-once event
 * is enabled at the user application. This is useful when users would like to
 * enable SL only when an event is occurring, such as a person-detect event or
 * a motion-detect event.
 *
 * @subsection acc_ctrl_faq_q3 Question 3: What are users required to take care of in the mechanical design?
 * <b>Answer:</b>
 * The vertical-cavity surface-emitting laser (VCSEL) projector can be easily
 * overheat when it is enabled for extended periods of time. This requires heat
 * dissipation design, such as a heat sink for the projector. The placement
 * between VCSEL and the ensor should be steady and fixed. The displacement of
 * the baseline will affect the depth generation result.
 *
 * @subsection acc_ctrl_faq_q4 Question 4: How is the on-board SDIO WiFi set up?
 * <b>Answer:</b>
 * The WiFi setup can be divided into two steps:
 * -# Probe the WiFi driver.
 *    @code {c}
 *    board # modprobe bcmdhd
 *    @endcode
 * -# Connect to the access point.
 *    @code {c}
 *    board # wifi_setup.sh sta nl80211 <ssid> <password>
 *    @endcode
 * @note
 * The WiFi firmware is no longer included in the SDK starting from the
 * revision 3.0.9. The `external_wifi_utility` patch must be applied in order
 * to use the on-board SDIO WiFi.
 *
 * - - - -
 *
 * @section acc_ctrl_license 8. License
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
 */

/*!
 * @file doc_apps_beetle_page.h
 * @brief
 * @version 1.0
 * @date 2024-01-12
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
 * @page beetle_page Beetle Demo
 *
 * @section beetle_history 0. Revision History
 * <table>
 * <caption id="beetle_history_table"></caption>
 * <tr><th> Updated Date              <th align="left"> Modification
 * <tr><td> 20240112                  <td> Initial Version
 * </table>
 *
 *
 * - - - -
 *
 * @section beetle_ov 1. Overview
 *
 * This document introduces the Ambarella Beetle Demo (multi-view recording-playback NNInference application)
 * and provides details of the reference design for the Ambarella CV3 DK-Mini system on chip (SoC).
 * As shown in Figure 1-1 below, Beetle Demo simultaneously displays six live camera views and bounding boxes (BBox) that
 * result from neural network (NN) inference.
 *
 * This document serves to demonstrate the easy application of the Beetle effect in the CV3x SoC to
 * aid users in designing their products.
 *
 * @image html beetle_hdmi_display.JPG "Figure 1-1. Beetle HDMI Display."
 * <br>
 *
 *
 * - - - -
 *
 * @section beetle_demo 2. Demonstration Application
 *
 * The Ambarella CV3x software development kit (SDK) has developed many basic and advanced
 * features for customer use. In addition, popular computer vision (CV) and image processing
 * algorithms are implemented to reduce user development costs.<br>
 * Beetle is a combination of features and CV algorithms in the Ambarella CV3x SDK.
 * The primary features used are the Lychee operating system (OS), GStreamer, ROS2, and CyberRT.
 * LycheeOS is a specialized Linux distribution tailored for Ambarella SoCs. Refer to
 * @ref page_sysdoc_lychee_os "LycheeOS". <br>
 * @note
 *  - This demo depends on lychee. However, GSTreamer architecture, ROS2 and CyberRT do not depend on lychee.
 *
 * The robotics / autonomous-driving middleware in the Beetle demo are ROS2 and CyberRT (Apollo 8.0).
 * The multi-media middleware in the Beetle demo uses GStreamer; the second stage attempts using Oryx.
 * The feature list of the Beetle demo includes encoding, streaming, decoding, recording,
 * NN inference, drawing detection, and segmentation results on the display device.
 * The application pipeline is provided in @ref beetle_soft_design "Software Design".
 *
 * Follow the steps below to build the environment and run the Beetle demo.
 *
 * @subsection build_install_lychee 2.1 Install and Set Up Lychee
 * Ensure that Lychee is correctly installed and set up;
 * follow the instructions from LycheeOS's WiKi page, @ref page_sysdoc_lychee_os "LycheeOS", to install.
 * The user name for testing this demo should be `amba`; perform the steps below in Lychee.
 *
 * @subsection build_install_dependecy 2.2 Install Required Dependencies
 * The demo depends on `amba_gst_plugins`, `nnstreamer`, and `amba_gst_helper`, as well as other open source libraries
 * that can be easily installed in Lychee. For detailed information, refer to the related pages.
 *
 * @code {.c}
 * ```bash
 * sudo dnf update --refresh
 * sudo dnf install libuuid-devel protobuf-devel glog-devel opencv-devel apollo-fast* apollo-cyber*
 * sudo dnf install gstreamer1-devel gstreamer1-plugins-base-devel alsa-lib-devel
 * sudo dnf install libamba-lwapputils-devel libamba_gst_helper-devel
 * @endcode
 *
 * @subsection build_compile_demo 2.3 Compile the Beetle Demo
 *
 * Download the source code of the Beetle demo and copy it to CV3.
 * The folder is located at `/AMBA_SDK_PATH/ambarella/app/robotics/6v_yolop_yolov5`.
 *
 * The middleware of publishing and subscribing is ROS2 / Apollo, please select one to install.
 * ROS2 as default, alse can support Apollo to replace ROS2 as alternative.
 *
 * @subsubsection build_demo_ros2 2.3.1 ROS2
 *
 * @code {.c}
 * ```bash
 * cd robotics/6v_yolop_yolov5/ros2/gstreamer/ros2_gst_6v_demo
 * source /opt/ros2/iron-20231205/setup.bash
 * pip install lark # only for first time
 *
 * # build
 * colcon build
 * source ./install/setup.bash
 * ```
 * @endcode
 *
 * @subsubsection build_demo_applo 2.3.2 Apollo
 *
 * @code {.c}
 * ```bash
 * cd /your_code_path_xxx/robotics/6v_yolop_yolov5/cyber_rt
 * make
 * sudo make install INSTALL_DIR=/opt/apollo
 * ```
 * @endcode
 *
 * @subsection build_demo_presets 2.4 Beetle Demo Presets
 * @subsubsection preset_dual_vout 2.4.1 Set Up Dual-Video Output
 * -# Check if the default device tree blob (DTB) supports dual-video-output (dual-VOUT): <br>
 *   @code{.c}
 *   Lychee$ vim /boot/extlinux/extlinux.conf
 *   @endcode
 *
 *  The content appears as follows. Note the default boot label: <br>
 *   @code{.c}
 *   1  default Ambarella-cv3-5.15.141-300-dual-vout
 *   2
 *   3  timeout 50
 *   4
 *   5  label Ambarella-cv3-5.15.141-300-dual-vout
 *   6  kernel //vmlinuz-5.15.141-300.lch2023.aarch64
 *   7  fdt //dtb-5.15.141-300.lch2023.aarch64/ambarella/ambarella-cv3-gpu-dual-vout.dtb
 *   8  append earlycon console=ttyS0 arm64.nopauth root=/dev/mmcblk0p2 rootwait rw rootfstype=btrfs init=/sbin/init pci=nomsi,pcie_bus_perf pcie_pme=nomsi fw_devlink=permissive rhgb
 *   ......
 *   @endcode
 *
 *   If the default DTB name (for example, `ambarella-cv3-gpu-dual-vout.dtb` in line 7 above)
 *   includes <b>dual-VOUT</b>, it denotes that dual-VOUT is supported. <br>
 *   Users can change the default DTB to one that supports the dual-VOUT feature:</br>
 *   @code{.c}
 *   Lychee$  cd /boot/dtb-5.15.141-300.lch2023.aarch64/ambarella/  # step 1, the path after /boot is defined in line 7 above
 *   Lychee$  ls *dual-vout*.dtb                                    # step 2, check usable dtb
 *   Lychee$  ambarella-cv3-gpu-4K-llava-dual-vout.dtb  ambarella-cv3-gpu-dual-vout.dtb
 *   Lychee$  sudo vim /boot/extlinux/extlinux.conf                 # step 3
 *   @endcode
 *
 *   Change the content in `/boot/extlinux/extlinux.conf` (in line 7 above, for example),
 *   and replace the DTB name with the one shown in step 2
 *   replace the DTB name with one in step 2 shows (`ambarella-cv3-gpu-4K-llava-dual-vout.dtb`) <br>
 *
 * -# Change Lua configuration for HDMI VOUT: <br>
 *   @code{.c}
 *   Lychee$  cd /etc/ambarella/cv3/vout/
 *   Lychee$  sudo ln -sf vout_hdmi_dual.lua vout_hdmi.lua
 *   @endcode
 *
 * -# Reboot Lychee; dual-VOUT is now ready for use.
 *
 * @subsubsection preset_prepare_files 2.4.2 Prepare Required Test Files
 *
 * The required files include models, labels, and test videos for file input.
 * Ambarella recommends placing the files in the following location:
 *
 * @code {.c}
 * /home/amba/tmp_data/
 * --coco_class_names.txt
 * --cv3_yolop.bin
 * --cv3_yolov5s.bin
 * --IMX490_road_8_h264.mp4
 * @endcode
 *
 * @subsection run_demo 2.5 Run Beetle Demo
 *
 * @subsubsection run_demo_ros2 2.5.1 Run Demo with ROS2
 *
 * Note that the line below is required for each new console that users open.
 * @code {.c}
 * ```bash
 * source /opt/ros2/iron-20231205/setup.bash
 * ```
 * @endcode
 *
 * Multi-camera input case:
 * @code {.c}
 * ```bash
 * cd robotics/6v_yolop_yolov5/ros2/gstreamer/ros2_gst_6v_demo
 * source /opt/ros2/iron-20231205/setup.bash
 * source ./install/setup.bash
 *
 * #run renderer
 * ros2 run ros2_gst_6v_demo  renderer --ros-args --params-file ./cfg_renderer.yaml
 *
 * #run inference and publish for each topic
 * [new console]
 * cd robotics/6v_yolop_yolov5/ros2/gstreamer/ros2_gst_6v_demo
 * source /opt/ros2/iron-20231205/setup.bash
 * source ./install/setup.bash
 * ros2 run ros2_gst_6v_demo ros2_cam_inference --ros-args --params-file ./cfg_cam_instance_pub.yaml
 *
 * ```
 * @endcode
 *
 * Multi-file input case:
 * @code {.c}
 * ```bash
 * cd robotics/6v_yolop_yolov5/ros2/gstreamer/ros2_gst_6v_demo
 * source /opt/ros2/iron-20231205/setup.bash
 * source ./install/setup.bash
 *
 * #run renderer
 * ros2 run ros2_gst_6v_demo renderer --ros-args --params-file ./cfg_renderer.yaml
 *
 * #run inference and publish for each topic
 * [new console]
 * cd robotics/6v_yolop_yolov5/ros2/gstreamer/ros2_gst_6v_demo
 * source /opt/ros2/iron-20231205/setup.bash
 * source ./install/setup.bash
 *
 * ros2 run ros2_gst_6v_demo ros2_demux_inference  --ros-args --params-file ./cfg_file_instance_pub.yaml
 * ```
 * @endcode
 *
 * @subsubsection run_demo_appllo 2.5.2 Run Demo with Apollo
 *
 * @code {.c}
 * ```bash
 * cd /opt/apollo/
 * source scripts/set_test_env.sh
 * #test multi-cam input
 * mainboard -d 6v_yolop_yolov5/dag/multi_cam_writer.dag -d 6v_yolop_yolov5/dag/osd_render.dag
 * #test multi-file input
 * mainboard -d 6v_yolop_yolov5/dag/multi_file_writer.dag -d 6v_yolop_yolov5/dag/osd_render.dag
 * ```
 * @endcode
 *
 *
 * - - - -
 * @section beetle_hw_design 3. Hardware Design
 * In this application, there are six cameras (using the OS08A10 sensor as an example) placed around the car:
 * `cam_0` at the front-left(cv3 port CH1.A), `cam_1` at the front-center(cv3 port CH1.B),
 * `cam_2` at the front-right(cv3 port CH2.A), `cam_3` at the rear-left(cv3 port CH2.B),
 * `cam_4` at the rear-center(cv3 port CH3.A), and `cam_5` at the rear-right(cv3 port CH3.B).
 * The cameras are connected to CV3 via serializers / deserializers (SERDES).
 * A high-definition multi-media interface (HDMI®) monitor is required for the Lychee interface.
 * In the output stage, the CV3x board outputs the video stream to another HDMI monitor.
 * Refer to the figure below for the hardware design.
 * @image html beetle_hw_design.JPG "Figure 3-1. Beetle Hardware Design."
 * <br>
 *
 * Figure 3-2 shows the camera and scenario:
 * @image html beetle_hw_senario.JPG "Figure 3-2. Beetle Senario."
 *
 *
 * - - - -
 * @section beetle_soft_design 4. Software Design
 *
 * The following is a schematic diagram of the Beetle pipeline for this application.
 * @image html beetle_sw_design.JPG "Figure 4-1. Beetle Pipeline."
 *
 * In the camera live mode, the video inputs (VINs) capture video previews from the six cameras,
 * concatenated on a canvas by the image digital signal processor (IDSP) and displayed via HDMI.
 * GStreamer captures YUV data from the cameras and feeds it to the NNInference-return bounding box.
 * The data of each YUV is segmented, then that data is published to the renderer by
 * Apollo or ROS2.  Finally, the renderer draws the bounding box and segmentation overlap on the video preview.
 * In file input mode, the media file is decoded and displayed by GStreamer, and NNInference obtains YUV and RGBP data
 * from files rather than cameras. The camera video can also be
 * recorded to a local file by GStreamer's `vencap`.
 *
 * The Beetle software stack diagram is as shown in
 * @image html beetle_sw_stack_diagram.JPG "Figure 4-2. Beetle Software Stack Diagram."
 *
 * The Beetle demo depends on `gst-helper`, ROS2, CyberRT, and more. The `gst-helper` is for multi-media processing, and
 * ROS2 / CyberRT are for data publishing and subscribing. VIN and VOUT are drivers
 * on LycheeOS; all components run on CV3.
 *
 *
 * - - - -
 * @section beetle_performance 5. Performance
 *
 * The following are performance values of the Beetle demo. <br>
 * <b>*</b> The file mode is not yet ready.
 *
 * <table>
 * <caption id="beetle_performance_table"></caption>
 * <tr><th> Mode <th align="left"> Modification <th align="left"> Class  <th align="left"> Data
 * <tr><td rowspan="14"> Camera Live <td rowspan="7"> Apollo <td> FPS                   <td> 30
 * <tr>                                                      <td> CPU usage  (CV3)      <td> 54.7 %
 * <tr>                                                      <td> NVP usage             <td> 21.38 % (6 NVP)
 * <tr>                                                      <td> GVP usage             <td> 7.1 % (2 GVP)
 * <tr>                                                      <td> Cortex DRAM Bandwidth <td> 6052 MB/s (3.52 %)
 * <tr>                                                      <td> DSP DRAM Bandwidth    <td> 3565 MB/s (2.08 %)
 * <tr>                                                      <td> VP DRAM Bandwidth     <td> 3845 MB/s (2.24 %)
 * <tr>                              <td  rowspan="7"> ROS2  <td> FPS                   <td> 30
 * <tr>                                                      <td> CPU usage  (CV3)      <td>  55.9 %
 * <tr>                                                      <td> NVP usage             <td> 21.42 % (6 NVP)
 * <tr>                                                      <td> GVP usage             <td> 7.2 % (2 GVP)
 * <tr>                                                      <td> Cortex DRAM Bandwidth <td> 6119 MB/s (3.57 %)
 * <tr>                                                      <td> DSP DRAM Bandwidth    <td> 3869 MB/s (2.26 %)
 * <tr>                                                      <td> VP DRAM Bandwidth     <td> 3564 MB/s (2.08 %)
 * </table>
 *
 *
 * - - - -
 * @section beetle_license 6. License
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
 */
/*!
 * @file doc_apps_aibox_page.h
 * @brief
 * @version 1.0
 * @date 2024-01-17
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
 * @page aibox_page AIbox Demo
 *
 * @section aibox_history 0. Revision History
 * <table>
 * <caption id="aibox_history_table"></caption>
 * <tr><th> Updated Date              <th align="left"> Modification
 * <tr><td> 20240112                  <td> Initial Version
 * </table>
 *
 * - - - -
 *
 * @section aibox_ov 1. Overview
 * AIBox provides demos related to multi-media and machine learning processing,
 * as well as demos illustrating the real-time streaming protocol, using the Ambarella platform.
 * AIBox is located in the software development kit (SDK) under `ambarella/app/aibox`.<br>
 * The following applications are included in AIBox:
 * - <b> multidec_vca: </b>
 *  used for multiple streams with RTSP + Demuxer + VideoDecoder (FFMpeg) + VideoFrameHook + DownScale + MachineLearning
 * <br>
 * - <b> multidec_vca_sub: </b>
 * subscribes the detected neural network (NN) results via CycloneDDS
 *
 * - - - -
 *
 * @section aibox_demo 2. Demo Application
 *
 * The Ambarella CV3x SDK includes many basic and advanced features,
 * including popular computer vision (CV) and image processing algorithms
 * that are implemented in order to reduce customer development costs.
 * <br>
 * AIBox is a combination of features and CV algorithms provided in the CV3x SDK.
 * Primary features include `lw_media`, used for multi-media processing; `cycloneDDS`, used for data distribution;
 * `cavalry_mem`, `NNCtrl`, and `VProc`, used for machine learning inference.
 * For detailed information, refer to @ref aibox_soft_design "Software Design".
 * <br>
 * Follow the steps below to build the environment and run the AIbox demo.
 *
 * @subsection build_hardware_prepare 2.1 Hardware Preparation
 * The following components are required.
 * - An CV3 system on chip (SoC)
 * - A secure digital (SD) card <br>
 * The following are required for RTSP mode: <br>
 * - Four RGB sensors (the following uses an `imx415_mipi` sensor as an example)
 * - Four other boards, called `rtsp-boards`. Use CV2x, CV5x, or CV7x; they must run the RTSP server
 * - A nine-port switch, or two switches. Ensure that the Ethernet port is >=9 (1 for PC, 4 for CV3, 4 for `rtsp-boards`)
 *
 * @subsection build_firmware_prepare 2.2 Firmware Preparation
 * @subsubsection build_firmware_cv3 2.2.1 Compile CV3 Firmware
 *
 * @code {.c}
 * cd $(SDK_PATH)/ambarella/boards/cv3_dk_mini
 * source build/env/amba-build.env cv3_dk_mini
 * make ipcam_clusters_config
 * @endcode
 *
 * Select the following configurations:
 * @code {.c}
 * Main menu
 * -> app
 *   -> aibox
 *     -> [*] multidec-vca (app/aibox/multi_dec_vca)
 * -> board (boards) (CONFIG_BOARD [=y]
 *   -> Memory (256) DSP Shared Memory size in MB
 *     (256) CV Shared Memory size in MB
 *     (512) CV Private Memory size in MB for cluster 0
 *     (512) CV Private Memory size in MB for cluster 1
 *     (512) CV Private Memory size in MB for cluster 2
 *     (512) CV Private Memory size in MB for cluster 3
 * -> boot
 *   -> amboot (boot/ambamk) (CONFIG_AMBOOT [=y])
 *     -> Ambarella Bootloader Configuration
 *       ->Board Revision (CV3_DK_MINI (128Gbit micron LPDDR5 @ 2808MHz))
 * -> prebuild
 *   -> internal_oss [*] prebuild-ffmpeg (prebuild/internal_oss/armv8-a/ffmpeg)
 * -> packages
 *   -> lw_media
 *     -*- liblwmedia (packages/lw_media/source)
 *       ---> select all
 * @endcode
 *
 * Then `make`
 *
 * @subsubsection build_firmware_rtsp 2.2.2 Compile RTSP-Boards Firmware
 * Select a sensor driver on `ipcam_config` for the corresponding board firmware.
 *
 * @subsubsection burn_firmware 2.2.3 Burn Firmware
 * <b> a) </b> Prepare a TransFlash (TF) card to store the root file system (rootfs) in EXT4 format. <br>
 * The default setting for CV72 is `mkfs.ext4`;
 * Ambarella recommends using this evaluation kit (EVK) for this step.
 * Refer to the sample code below to format the TF card to EXT4.
 *
 * @code {.c}
 * # fdisk -l  // Note: TF card device name will be effected by the hardware Slot. # mkfs.ext4 /dev/mmcblk1
 * # mkfs.ext4 /dev/mmcblk1
 * # umount /sdcard/mmcblk1  //Due to after format tf card, it will mount by default. This steps is necessary.
 * # fdisk /dev/mmcblk
 * ---> p // print current status
 *
 * //Created a new partition 1 of type 'Linux' and of size 5 GiB.
 * ---> n // create new partition
 *   ---> p // select (default p) <br>
 *          Partition number (1-4, default 1): type-in 1 <br>
 *          First sector (2048-121534463, default 2048): type-in "enter" button //use default setting <br>
 *          Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-121534463, default 121534463): type-in +5G <br>
 *
 * ---> n // create new partition 2
 *   ---> p // Select (default p)
 *          Partition number (2-4, default 2): type-in  "enter" button
 *          First sector (10487808-62333951, default 10487808): type-in "enter" button //use default setting
 *          Last sector, +/-sectors or +/-size{K,M,G,T,P} (10487808-62333951, default 62333951): type-in  "enter" button //use default setting
 *
 * ---> w
 *   The partition table has been altered.
 *   ailed to add partition 1 to system: Invalid argument
 *   Failed to add partition 2 to system: Invalid argument
 *   The kernel still uses the old partitions. The new table will be used at the next reboot. Syncing disks.
 *
 * # reboot // This step must execute. the above setting will be effect after reboot.
 *
 * # fdisk -l //check partition
 *       Device  Boot  Start  End Sectors Size Id Type
 *       /dev/mmcblk1p1 2048 10487807 10485760 5G 83 Linux
 *       /dev/mmcblk1p2 10487808 31291391 20803584 9.9G 83 Linux
 * @endcode
 *
 * <b> b) </b> Create Rootfs <br>
 * `Rootfs.ex4` location: `/sdk_path/out/amba_out/cv3_dk_mini/images/rootfs.ext4`. Copy `rootfs.ext4` to EVK, the path is under: `/tmp`
 * @code {.c}
 * # dd if=/tmp/new/rootfs.ext4 of=/dev/mmcblk0p1 && sync && dd if=/tmp/new/rootfs.ext4 of=/dev/mmcblk0p2
 * @endcode
 *
 * <b> c) </b> Burn the firmware via AmbaUSB <br>
 * The firmware path is: `/sdk_path/ambarella/out/amba_out/cv3_dk_mini/firmware/bst_bld_env_dtb_kernel.elf` <br>
 * Insert the SD card into CV3 and reboot; CV3 can then use multiple clusters.<br>
 * The IP for cluster0 is 10.0.0.2, 10.0.0.3 for cluster1, 10.0.0.4 for cluster2, and 10.0.0.5 for cluster3. <br>
 *
 * @subsubsection set_ip_rtsp 2.2.4 Set Up IP Address on RTSP Board
 *
 * Use the method below to set the IP address for the four `rtsp-boards` to:
 * 10.0.0.6, 10.0.0.7, 10.0.0.8, 10.0.0.9.
 * @code {.c}
 * vi /etc/network/interfaces
 * change "address 10.0.0.2" to "address 10.0.0.6"
 * reboot
 * @endcode
 *
 * @subsection run_demo 2.3 Run Demo
 * The following prepared files must be copied to the EVK board: <br>
 * - Configured files for multi pipelines, such as
 *  `/ambarella/app/aibox/conf/ffmpeg_decoder_16c_rtsp_yolov5s.lc`; copy the files to `/tmp/` on the board
 * - Tested NN models for machine learning, such as `yolov5s` model; copy the files to `/tmp/` on the board
 * - Media files for file mode, such as `h264 es`; copy the files to `/tmp/` on the board
 *
 * For RTSP scenarios, connect CV3 and the four `rtsp-boards` (with RGB sensors) via an nine-port switch.
 * Ensure that the hardware components can communicate with one another.
 *
 * <b> Debug and set up the log level of the pipeline using either of the following methods: </b> <br>
 * There are two methods to set up the loglevel of pipeline.
 * - Add `--loglevel x`: `multidec_vca /tmp/ffmpeg_decoder_9c_rtsp.lc <b> --loglevel </b> 7`
 * - Modify `log_level = x` in the .lc file
 *
 * @subsubsection test_rtsp 2.3.1 Test RTSP
 * The following case demonstrates testing and validation for RTSP + Demuxer +
 * VideoDecoder (FFMpeg) + VideoFrameHook, with nine streams on each cluster.
 * 1. Run `rtsp_server` on `rtsp-boards`.
 * @code {.c}
 *  // run below cmds on each rtsp-boards, the sensor is example of imx415_mipi
 * init.sh --na; modprobe imx415_mipi vinc_id=8
 * test_aaa_service -a &
 * test_encode --resource-cfg /usr/share/ambarella/lua_scripts/ cv72_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/ vout_hdmi_720p.lua
 * rtsp_server &
 * test_encode -A -h1080p -e --bitrate 2000000
 * @endcode
 *
 * 2. Simultaneously run AIBox on each CV3 cluster.
 * @code {.c}
 * // cluster 0: (10.0.0.2)
 * multidec_vca /tmp/ffmpeg_decoder_9c_rtsp.lc //set all ve_input_file = rtsp://10.0.0.6/stream1
 * (new console) multidec_vca_sub --stream_num 9
 *
 * // cluster 1: (10.0.0.3)
 * multidec_vca /tmp/ffmpeg_decoder_9c_rtsp.lc //set all ve_input_file = rtsp://10.0.0.7/stream1
 * (new console) multidec_vca_sub --stream_num 9
 *
 * // cluster 2: (10.0.0.4)
 * multidec_vca /tmp/ffmpeg_decoder_9c_rtsp.lc //set all ve_input_file = rtsp://10.0.0.8/stream1
 * (new console) multidec_vca_sub --stream_num 9
 *
 * // cluster 3: (10.0.0.5)
 * multidec_vca /tmp/ffmpeg_decoder_9c_rtsp.lc //set all ve_input_file = rtsp://10.0.0.9/stream1
 * (new console) multidec_vca_sub --stream_num 9
 * @endcode
 *
 * @subsubsection test_filesrc 2.3.2 Test Filesrc
 * The following case tests and validates Filesrc + Demuxer +
 * VideoDecoder(FFMpeg) + VideoFrameHook, with 16 streams on each cluster.
 * @code {.c}
 * // if input es, setup "demuxer_es = 1" in lc; if input mp4, setup "demuxer_mp4 = 1" in lc.
 * // running on cluster 0(10.0.0.2)/1(10.0.0.3)/2(10.0.0.4)/3(10.0.0.5) at the same time
 * multidec_vca /tmp/ffmpeg_decoder_16c_filesrc_dec.lc // ensure ve_input_file = /tmp/your_media_file
 * (new console) multidec_vca_sub --stream_num 16
 * @endcode
 *
 * @subsubsection test_rtsp_ds_ml 2.3.2 Test RTSP with Downscale and Machine Learning
 * The following case demonstrates testing and validation for RTSP + Demuxer + VideoDecoder (FFMpeg) +
 * VideoFrameHook + DownScale + MachineLearning, with eight streams on cluster0.
 *
 * @code {.c}
 * // on cluster 0: (10.0.0.2)
 * multidec_vca /tmp/ffmpeg_decoder_8c_rtsp_yolov5s.lc //set all ve_input_file = rtsp://10.0.0.6/stream1
 * (new console) multidec_vca_sub --stream_num 8
 * @endcode
 *
 * @subsubsection test_filesrc_ds_ml 2.3.2 Test Filesrc with Downscale and Machine Learning
 * The following case demonstrates testing and validation for Filesrc + Demuxer +
 * VideoDecoder (FFMpeg) + VideoFrameHook + DownScale + MachineLearning, with 16 streams on cluster0.
 * @code {.c}
 * // if input es, setup "demuxer_es = 1" in lc; if input mp4, setup "demuxer_mp4 = 1" in lc.
 * // on cluster 0: (10.0.0.2)
 * multidec_vca /tmp/ffmpeg_decoder_16c_filesrc_yolov5s.lc // ensure ve_input_file = /tmp/your_media_file
 * (new console) multidec_vca_sub --stream_num 16
 * @endcode
 *
 *
 * <b> * Note the following known issues: </b> <br>
 * - Setup for image audio video (IAV) and Cavalry is not currently supported on cluster 1/2/3
 * - Set up `enable_scale_conversion = 0` and `enable_nn_inference = 0` in the .lc files before running on cluster 1/2/3
 * - Do not attempt to run an NN on cluster 1/2/3
 *
 *
 * - - - -
 * @section aibox_hw_design 3. Hardware Design
 * In the RTSP mode application, there is one `rtsp-board` with an RGB camera.
 * This `rtsp-board` sens out video data via Ethernet from the RGB camera to CV3.
 * Ambarella recommends using one board per stream to prevent lags in data flow.
 * <br>
 *
 * In filesrc mode, the local media file is decoded and fed into `lw_media`,
 * rather than captured from the camera in RTSP mode.
 * <br>
 *
 * In the output stage, the CV3x board outputs the video stream to
 * a high definition multi-media interface (HDMI®) monitor.
 * <br>
 *
 * <b> * </b> The display module is not yet prepared.
 *
 * Refer to Figure 3-1 below for the hardware design.
 * @image html aibox_hw_design.JPG "Figure 3-1. AIbox Hardware Design."
 * <br>
 *
 *
 * - - - -
 * @section aibox_soft_design 4. Software Design
 * Figure 4-1 below is a schematic diagram of the AIBox pipeline for this application.
 * @image html aibox_sw_design.JPG "Figure 4-1. AIbox Pipeline."
 *
 * In RTSP mode, the video inputs (VINs) compare video previews from RGB cameras,
 * which are concatenated on a canvas by the image digital signal processor (IDSP)
 * and displayed on the HDMI video output (VOUT). The `lw_media` captures YUV data
 * from the RTSP stream and feeds it to the machine learning inference (mlinference)
 * return bounding box for each YUV. The data is then published to the renderer via CyberRT.
 * Finally, the renderer draws the bounding box, overlapping the video preview.
 * In filesrc mode, the media file is decoded and fed into `lw_media`,
 * and mlinference obtains the YUV data from files rather than the RTSP stream.
 *
 * Figure 4-2 below demonstrates the software stack of the AIBox demo.
 * @image html aibox_sw_stack_diagram.JPG "Figure 4-2. AIbox Software Stack Diagram."
 *
 * The four main AIBox modules are the multi-media processing, mlinference,
 * data distribution, and renderer modules. Multi-media processing is dependent upon `lw_media`,
 * invoking FFMpeg to achieve this feature. Mlinference, which returns bounding boxes
 * from the YUV data, depends on `cavalry_mem`, neural network control (NNCtrl),
 * and the VProc library. The data distribution module depends on CycloneDDS,
 * which publishes the bounding box to the renderer. Finally,
 * the renderer module draws the bounding box overlapping the VOUT.
 * <br>
 * <b> * </b> The renderer module is not yet prepared.
 *
 * - - - -
 * @section aibox_performance 5. Performance
 *
 *
 * - - - -
 * @section aibox_license 6. License
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
 */

/*!
 * @file doc_apps_mvvc_page.h
 * @brief
 * @version 1.0
 * @date 2022-12-20
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
 * @page mvvc_page Multi-View Video Conference
 *
 * @section mvvc_history 0. Revision History
 * <table>
 * <caption id="mvvc_history_table"></caption>
 * <tr><th> Updated Date              <th align="left"> Modification
 * <tr><td> 20221220                  <td> Initial Version
 * </table>
 *
 * - - - -
 *
 * @section mvvc_ov 1. Overview
 *
 * This document introduces the Ambarella multi-view video conference (MVVC) demo application
 * and provides details of the reference design for the Ambarella CV5x system on chip (SoC). As shown
 * in Figure 1-2 below, MVVC displays stitched scenes of all participants in the same video screen at the same time.
 *
 * This document serves to demonstrate the easy application of the MVVC effect in the CV5x SoC in order to aid
 * customers in designing their own product.
 *
 * @image html mvvc_meeting_room.jpg "Figure 1-1. MVVC Meeting Room."
 * <br>
 * @image html mvvc_effect_v6.png "Figure 1-2. MVVC Effect."
 * <br>
 *
 * - - - -
 *
 * @section mvvc_demo 2. Demo Application
 * The Ambarella CV5x software development kit (SDK) has developed many basic and advanced features for customer use.
 * In addition, popular computer vision (CV) and image process algorithms are implemented to reduce customer development costs.
 * MVVC is a combination of features and CV algorithms in the Ambarella CV5x SDK. The primary features used are encoding from memory (EFM),
 * image scaling, and video stitching. The demo also uses a byte tracking algorithm for human detection and tracking.
 * The application pipeline is provided in later chapters.
 * Follow the steps below to build the environment and run the MVVC demo.
 *
 * -# Build the demo application:
 * @code {.c}
 * [*] Ambarella Application Configuration  --->
 *     [*] Build Video Conference  --->
 *         [*] Build Multi Combine ROI View from Stitch Canvas Application
 * @endcode
 *
 * -# Build the ByteTrack EazyAI application:
 * @code {.c}
 * [*] Ambarella Package Configuration  --->
 *     [*] Build Ambarella EAZYAI library  --->
 *         [*] Build EazyAI applications  --->
 *             [*] Build ByteTrack EazyAI apps
 * @endcode
 *
 * -# Run the demo application command line:
 * @code {.c}
 * ----------------------------------1: start a stream for efm------------------------------------------
 * board # init.sh --na;modprobe max9296 id=0x0303 vinc_id=0xb8;modprobe os08a10_mipi_brg fsync=1
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_four_chan_four_sensor_8064x1024_main_3840x2160_third_1920x256_fourth.lua \
  *        --img-scale 1 --img-scale-format 0 --img-scale-max-in 8276x2176 --img-scale-max-out 3840x2176 --img-scale-job-queue-depth 12
 * board # test_encode -A -H qfhd -b 24 -e
 * board # test_encode -A --bitrate 800000
 * ----------------------------------2: sensor calibration----------------------------------------------
 * board # test_stitch --mode 2 -f ./ &
 * board # test_stitch --mode 3 --overlap-id 0 --top 200,0  --bot 200,1024 --overlap-id 1 --top 200,0  --bot 200,1024 \
 *         --overlap 2 --top 200,0  --bot 200,1024 --overlap 3 --top 200,0  --bot 200,1024
 * ----------------------------------3: combine ROIs--------------------------------------------------
 * board # test_stitch_multi_roi_combine -A -s 0 -b 1 -H 480 -W 8064 --non-block 1 -l 15 --resort 1 -F 376 -m 344 -e 150 \
 *         --moving-steps-x 16 --moving-steps-y 4 --moving-steps-w 4 -M 8 --input-width-thr 0.03 --objid-change-thr 310 &
 * ----------------------------------4: start CV detection----------------------------------------------
 * board # rmmod cavalry && modprobe cavalry && cavalry_load -f /lib/firmware/cavalry.bin -r
 * board # test_bytetrack -p cavalry_bytetrack-fx16.bin -b 1 -d 1 -s 1 -e 1 -u 1 --disable_display 1
 * @endcode
 * - - - -
 * @section mvvc_hw_design 3. Hardware Design
 * In this application, there is one panoramic camera consisting of four cameras covering a 360° view of the meeting room.
 * In the output stage, the CV5x board can output the video stream to the monitor via a high definition multimedia interface (HDMI®)
 * cable or transfer H26x / MJPEG streams via Ethernet.
 * Refer to the following figure for the hardware design:
 * @image html mvvc_hw_design_v6.png "Figure 3-1. MVVC Hardware Design."
 * - - - -
 * @section mvvc_soft_design 4. Software Design
 * The following is a schematic diagram of the MVVC pipeline for this application.
 * @image html mvvc_sw_design_v6.png "Figure 4-1. MVVC Pipeline."
 * The four cameras are deserialized as four video inputs (VINs); each connects to one image digital signal processing (IDSP) channel.
 * Each VIN-IDSP channel records part of the view of the meeting room.
 * In the canvas, it is necessary to stitch the YUV image from all four channels together to get one panoramic view again.
 * Refer to @ref page_lib_stitch_doc "Ambarella Stitching Features" on how to perform image stitching.
 *
 * There are three canvases in this application:
 * -# <b>Canvas 0</b> consists of four main buffers. Its resolution should be as large as possible within system limitations.
 * -# <b>Canvas 1</b> is formed from four third buffers. As shown in Figure 4-1, the panoramic view is on the top of the canvas while the bottom half
 * is a blank area reserved for the image scaler's output. This canvas also functions as an EFM input, so its resolution should
 * be the same as the EFM stream's, which is 4K in this demo.
 * -# <b>Canvas 2</b> is comprised of four fourth buffers. This canvas is used as an input for the CV detection algorithm. Its resolution
 * is decided on the CV algorithm's requirement.
 *
 * After starting the application, the CV algorithm queries each YUV image from canvas 2 and runs detection. Then, CV outputs
 * detection results to the MVVC application containing the position of each person. The MVVC application will then extract people
 * from canvas 0 using @ref fs_adv_arb_img_scaler "image scaler" and output the scaled image to canvas 1's blank area to compose
 * the YUV containing one panoramic view, plus serveral region of interests (ROIs). After extracting
 * all people detected, the MVVC application sends canvas 1's YUV image to EFM and video output (VOUT). Then, users can see this frame on
 * a monitor or via VideoLAN Client (VLC).
 *
 * If the user does not want the panoramic view on the top of the stream, canvas 1 can be removed. In this case, the user application must
 * allocate a dynamic random-access memory (DRAM) partition for the image scaler output and EFM input.
 * The effect without panoramic view is shown as below in Figure 4-2.
 * @image html mvvc_effect_without_panorama_v6.png "Figure 4-2. MVVC Effect Without Panoramic View."
 * - - - -
 * @section mvvc_advanced_features 5. Advanced Features
 * @subsection mvvc_strategy_of_me_img 5.1 Generate ME Image
 * If the EFM stream format is H26x, the MVVC application will also generate the ME image. There are two
 * strategies to generate ME1 and ME0 images:
 * -# Scale down from the YUV image using the image scaler
 * -# Compose each ROI to the ME buffer; similar to what is performed for the YUV image
 *
 * Strategy 1 uses more DRAM bandwith when the panoramic view exists because it must process not only the ROIs but also the panoramic
 * view on the stream top. <br>
 * Strategy 2 is not affected by the panoramic view, but it sends more DSP commands than strategy 1. Thus, the digital signal processor (DSP)
 * will spend more time on command and message exchanges with Arm®, which results in lower frames per second (fps) and longer latency. <br>
 * The following table provides the DRAM bandwidth utilization of these two strategies.
 * <table>
 * <caption id="bram_bw_of_mvvc_app">Table 5-1. DRAM Bandwidth Utilization of the MVVC Application.</caption>
 * <tr><th>                     <th align="center"> Strategy 1                                                     <th align="center"> Strategy 2
 * <tr><th> DSP DRAM Bandwidth  <td align="center"> 6578.497 MB/s <br>(15.353% of LPDDR5@2.8GHz)       <td align="center"> 6323.493 MB/s <br>(14.758% of LPDDR5@2.8GHz)
 * </table>
 * Ambarella recommends using strategy 1 when DRAM loading is not heavy in order to get higher fps and lower latency.
 * - - - -
 * @section mvvc_license 6. License
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
 */
/*!
 * @file doc_apps_mvbc_page.h
 * @brief
 * @version 1.0
 * @date 2023-6-20
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
* @page multi_vin_bind_page Multi-VIN Binding Single Channel
*
* @section mvbc_history 0. Revision History
* <table>
* <caption id="mvbc_history_table"></caption>
* <tr><th> Updated Date 			 <th align="left"> Modification
* <tr><td> 20230620 				 <td> Initial Version
* </table>
*
* - - - -
*
* @section mvbc_ov 1. Overview
*
* This document introduces the Ambarella  multi-VIN bind to single channel (MVBC) demo and provides details
* of the reference design for the Ambarella CV5x system on chip (SoC).
*
* This document demonstrates a simple method to use MVBC in the CV5x SoC in order to aid
* users in designing their products.
*
* Channels are the software concept of the image digital signal processor (IDSP) pipeline.
* For each channel, CV5x / CV7x chips process the input frames captured from an RGB sensor or YUV
* device, and generate different YUV buffers for further processing. Therefore, the image audio video
* (IAV) driver allocates a large amount of memory to each channel to ensure the normal operation
* of the entire pipeline. The memory required by each channel is closely related to the resolution
* of the sensor.
* If the resolution of the sensor corresponding to the channel is high, the number of channels
* supported by the system will be smaller. When users must support multiple large
* resolution sensors, the overhead of the system becomes stretched.
*
* CV5x / CV7x chips can support multiple sensors time-sharing the same channel. Users can
* dynamically change the video input (VIN) source functioning on a channel when IAV has entered the preview or
* encode state. Therefore, it can support multiple large-resolution sensors to function together
* with limited system overhead, without having to enter the idle state or reset both the IAV and the
* digital signal processor (DSP).
*
* - - - -
*
* @section mvbc_demo 2. Demo Application
*
* The field `possible_vsrc_list` has been added into the channel configuration of the Lua file.
*
* @code {.c}
* chan_0 = {
*     ...
*     possible_vsrc_list = {vsrc_0, vsrc_1, vsrc_2, },
*     ...
* }
* @endcode
*
* The purpose of this field is to bind several sensors of the same format to the current channel.
* These sensors can be dynamically switched after the IAV enters the preview state or even after
* encoding has begun.
*
* -# Ambarella currently provides a demo to switch VIN sources in the "test_aaa_service -i" interactive mode.
*
* @code {.c}
* ----------------------------------1: When preview is done, you can following menu----------------------------------
* board# test_aaa_service -i
* g -- global settings
* e -- exposure control settings
* w -- white balance settings
* a -- image adjustment settings
* n -- nn isp settings
* d -- dynamic change channel vsrc mapping
* q -- quit
* ================================================
* Channel [0]: > d
* ----------------------------------2: Type “d”, then you can get----------------------------------------------------
* ======= dynamic change channel vsrc mapping menu ======
* s -- show current vsrc id   (shows current vsrc id for default channel id(0))
* c -- change vsrc id         (switches vsrc id to the input value.)
* q -- Return to upper level
* ================================================
* A > c
* ----------------------------------3: switch vsrc for current channel.------------------------------------------------
* ==========================
* Input new vsrc id: 1
*
* New vsrc id is 0. Start changing vsrc...
* ========= Start dynamic chaning vsrc for chan[0] =========
*         1. stop AAA flow!
*         2. switch to vsrc_id[1] for chan[0]
* Successfully switch vsrc_id from [0] to [1] for chan[0]
*
*         3. Update vsrc2chan map in AAA
*         4. Re-start AAA flow!
* Dynamic change vsrc is done!
* Successfully change vsrc!
* @endcode
*
* -# Run the demo application command line:
*
* @code {.c}
* board-1 # init.sh --na;
* board-1 # modprobe imx274_mipi vinc_id=0x40b8;
* board-2 # test_aaa_service -i
* board-1 # test_encode --resource-cfg three_vin_bind_chan0_one_vin_bind_chan1.lua  --vout-cfg vout_hdmi.lua
* board-1 # test_encode -A -Hqfhd -b0 -e
* board-1 # test_encode -B -Hqfhd -b4 -e
* board-1 # rtsp_server
* board-2 # test_aaa_service -i > d > c
* @endcode
*
* Refer to <a href="script/three_vin_bind_chan0_one_vin_bind_chan1.lua" target="_blank"><b>three_vin_bind_chan0_one_vin_bind_chan1.lua</b></a>.
*
* - - - -
*
* @section mvbc_hw_design 3. Software Design
* The following is a schematic diagram of the mixed-case MVBC
* pipeline for this application.
* @image html mvbc_pipeline.jpg "Figure 3-1. MVBC Pipeline."
*
* As an initial version, there are still some limitations:
* - Ambarella currently only supports <b>multiple independent VINC</b> bindings to the same channel,
*   and the case of multiple sensors mounted to one VINC is not yet supported.
* - Several sensors bound to the same channel must be the same model sensor and have exactly the same
*   configuration parameters (such as Bayer, high dynamic range (HDR) mode, frame rate,
*   resolution, and RGB bits).
* - Some features (such as vsync loss detection) are not yet supported for this application.
* - The demo application is only used as a reference design. Only channel0 can switch the video source (VSRC) on
*   the fly. Users are required to write their own application for other cases.
*
* - - - -
*
* @section mvbc_license 4. License
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
*/

