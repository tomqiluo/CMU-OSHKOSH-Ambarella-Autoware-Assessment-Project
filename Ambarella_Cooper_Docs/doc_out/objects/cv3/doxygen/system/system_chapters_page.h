/*!
 * @file doc_sys_migration_guide_cv2x.h
 * @brief
 * @version 1.0
 * @date 2023-4-23
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
 * @page page_sys_mg_cv2x Migration Guide From CV2x
 *
 * @section sys_mg_cv2x_history 0. Revision History
 * <table>
 * <caption id="sys_migration_guide_rev_history"></caption>
 * <tr><th> Updated Date         <th align="left"> Modification
 * <tr><td> 20220812             <td> Initial Version
 * <tr><td> 20221010             <td> Added Section @ref sys_mg_sw_api_diff_img_scale
 * <tr><td rowspan="2"> 20221027 <td> 1. Updated Section @ref sys_mg_ioctl_interface "IOCTL Interface"
 * <tr>                          <td> 2. Updated Section @ref sys_mg_tools "Tools"
 * <tr><td rowspan="2"> 20230725 <td> 1. Updated Section @ref sys_mg_sw_api_diff
 * <tr>                          <td> 2. Updated Section @ref sys_mg_ioctl_interface_g_sys_res
 * <tr><td rowspan="2"> 20231025 <td> 1. Updated Section @ref sys_mg_tools_linux
 * <tr>                          <td> 2. Updated Section @ref sys_mg_ioctl_interface_g_sys_res
 * <tr><td> 20240109             <td> Added Section @ref sys_mg_sw_api_diff_multi_pass
 * <tr><td rowspan="3"> 20240122 <td> 1. Added Section @ref sys_mg_sw_api_diff_custom_sei
 * <tr>                          <td> 2. Added Section @ref sys_mg_sw_api_diff_raw_fps
 * <tr>                          <td> 3. Updated Section @ref sys_mg_ioctl_interface "IOCTL Interface"
 * </table>
 *
 * @section sys_mg_overview 1. Overview
 *
 * This document provides users with instructions for migrating single- and multiple-video
 * input (VIN) channel designs from the CV2x to the Cooper chip family. The Cooper family of chips
 * includes the CV5, CV52, CV72, and CV3 chips.
 *
 * - - - -
 *
 * @section sys_mg_hw 2. Hardware
 *
 * @subsection sys_mg_hw_main_diff 2.1 Main Differences
 * The following table lists the main differences between the CV2S88, CV5S66, and CV72S66 chips.
 * <table>
 * <caption>Table 2-1. Differences Between CV2S88, CV5S66, and CV72S66.</caption>
 * <tr><th colspan="2">Hardware Type                    <th>CV2S88             <th>CV5S66                                     <th>CV72S66
 * <tr><th rowspan="8">Basic      <th>Process(nm)       <td>10                 <td>5                                          <td>5
 * <tr>                           <th>CPU               <td>Quad-Cortex® A53 (1.0 GHz, 64 bits)
 *                                                      <td>Dual-Cortex A76 (1.6 GHz, 64 bits)
 *                                                      <td>Dual-Cortex A76 (1.6 GHz, 64 bits) + Cortex-M3 (576 MHz)
 * <tr>                           <th>VIN               <td>Native six (can future extend by B5 / B6 / B8)
 *                                                      <td>Four independent VINs; total of 14 VINs (can extend via serializer / deserializer (SERDES))
 *                                                      <td>Three independent VINs; total of ten VINs (can extend via SERDES)
 * <tr>                           <th>CVflow® processor  <td>One                <td>One                                        <td>One
 * <tr>                           <th>USB interface     <td>2.0 (up to 480 Mbps)<td>3.2 Gen 2 (up to 10 Gbps)                   <td>3.2 Gen 2 (up to 10 Gbps)
 * <tr>                           <th>DRAM interface    <td>LPDDR4             <td>LPDDR5 / LPDDR4                              <td>LPDDR5 / LPDDR4
 * <tr>                           <th>Max DRAM size     <td>4 GB               <td>32 GB for LPDDR5 / 16 GB for LPDDR4        <td>16 GB for LPDDR5(x) / 8 GB for LPDDR4
 * <tr>                           <th>PCIe              <td>N/A                <td>Four-lane PCIe                             <td>One-lane PCIe Gen 3
 * <tr><th rowspan="5">Clock(MHz) <th>Cortex            <td>Quad-Core@1008     <td>Dual-Core@1608                             <td>1608
 * <tr>                           <th>DRAM              <td>1596 (64-bit LPDDR4)<td>2640 (64-bit LPDDR5)                       <td>3192 (32-bit LPDDR5)
 * <tr>                           <th>IDSP              <td>864                <td>696                                        <td>1272
 * <tr>                           <th>Core              <td>960                <td>720                                        <td>624
 * <tr>                           <th>Vision (VP)       <td>912                <td>1104                                       <td>624
 * <tr><th>Voltage (V)            <th>Core              <td>0.80               <td>0.75                                       <td>0.75
 * <tr><th rowspan="2">Performance<th>HEVC encode       <td>4 x 5MP30 HEVC (linear VIN)
 *                                                      <td>4 x (5MP30 + 720P30 + 5MP15)
 *                                                      <td>4 x (5MP30 + 720p30 + 5MP2)
 * <tr>                           <th>CV                <td>Various convolutional neural network (CNN) algorithms
 *                                                      <td>Various CNN algorithms
 *                                                      <td>Various CNN algorithms
 * </table>
 *
 * @subsection sys_mg_hw_dsp_diff 2.2 Digital Signal Processor Differences
 * The major digital signal processor (DSP)-related differences between CV2x, CV5x, CV72, and CV3 are as follows:
 *   - CV2x and CV72 offer one core for both image digital signal processing (IDSP) and video
 *     digital signal processing (VDSP). Alternatively, CV5x and CV3 have dual cores
 *     for both IDSP and VDSP.
 *   - CV2x provides six pyramid layers. Alternatively, CV5x, CV72 and CV3 provide seven pyramid layers.
 *
 * @subsection sys_mg_hw_timn_board 2.3 CV5 Timn Board
 * This sections provides details on the CV5 Timn board.
 *
 * @subsubsection sys_mg_hw_timn_board_cfg 2.3.1 Board Configuration
 * The figure below provides an overview of the major components and input / output (I/O) connectors of the
 * CV5 evaluation kit (EVK) board, followed by a table of component descriptions.
 * @image html cv5_timn_board.png "Figure 2-1. CV5 Timn Board."
 * The major components and I/O connectors identified in the figure above are as follows.
 * <table>
 * <caption>Table 2-2. Input / Output Connectors Identifier.</caption>
 * <tr><th>Identifier <th>Description
 * <tr><td>1          <td>Universal asynchronous receiver / transmitter (UART)1 DB9 with flow control
 * <tr><td>2          <td>USB to serial debug UART + firmware download port
 * <tr><td>3          <td>Internal power on / off
 * <tr><td>4          <td>Reset
 * <tr><td>5          <td>External power on / off
 * <tr><td>6          <td>Microcontroller unit (MCU) reset
 * <tr><td>7          <td>Audio line-out
 * <tr><td>8          <td>Analog microphone (MIC)
 * <tr><td>9          <td>Digital MIC
 * <tr><td>10         <td>Joint test action group (JTAG)
 * <tr><td>11         <td>Dual in-line package (DIP) switches
 * <tr><td>12         <td>Video input (VIN) port1
 * <tr><td>13         <td>VIN port2
 * <tr><td>14         <td>VIN port3
 * <tr><td>15         <td>VIN port3
 * <tr><td>16         <td>Mobile industry processor interface (MIPI®) DSI video output (VOUT)
 * <tr><td>17         <td>USB 3.0 host
 * <tr><td>18         <td>USB Type-C
 * <tr><td>19         <td>Micro USB 3.0 device
 * <tr><td>20         <td>Composite video with blanking and sync (CVBS) VOUT
 * <tr><td>21         <td>Infrared (IR) receiver
 * <tr><td>22         <td>Periperal component interconnect express (PICe) x4 port
 * <tr><td>23         <td>Ethernet
 * <tr><td>24         <td>Ethernet
 * <tr><td>25         <td>12-V DC power
 * <tr><td>26         <td>High-definition multimedia interface (HDMI®) VOUT
 * </table>
 *
 * @subsection sys_mg_hw_ga_board 2.4 CV72 Ga Board
 * This section provides details on the CV72 Ga board.
 *
 * @subsubsection sys_mg_hw_timn_board_cfg 2.4.1 Board Configuration
 * The figure below provides an overview of the major components and I/O connectors of the
 * CV72 EVK board, followed by a table of component descriptions.
 * @image html cv72_ga_board.png "Figure 2-2. CV72 Ga Board."
 * The major components and I/O connectors identified in the figure above are as follows.
 * <table>
 * <caption>Table 2-3. Input / Output Connectors Identifier.</caption>
 * <tr><th>Identifier <th>Description
 * <tr><td>1          <td>USB to serial debug UART and firmware download port
 * <tr><td>2          <td>Internal power on / off
 * <tr><td>3          <td>Reset
 * <tr><td>4          <td>External power on / off
 * <tr><td>5          <td>MCU reset
 * <tr><td>6          <td>Audio line-out
 * <tr><td>7          <td>Audio headphone (HP) out
 * <tr><td>8          <td>Audio speaker out
 * <tr><td>9          <td>JTAG
 * <tr><td>10         <td>DIP switches
 * <tr><td>11         <td>VIN port1
 * <tr><td>12         <td>VIN port2
 * <tr><td>13         <td>MIPI DSI VOUT
 * <tr><td>14         <td>USB 3.2 host
 * <tr><td>15         <td>USB Type-C
 * <tr><td>16         <td>Micro USB 3.2 device
 * <tr><td>17         <td>CVBS VOUT
 * <tr><td>18         <td>IR receiver
 * <tr><td>19         <td>PCIe x1 port
 * <tr><td>20         <td>Ethernet
 * <tr><td>21         <td>12-V DC power
 * <tr><td>22         <td>HDMI VOUT
 * </table>
 *
 * - - - -
 *
 * @section sys_mg_sw 3. Software
 *
 * This chapter describes the software migration process from CV2x to the Cooper Linux software development kit (SDK).
 *
 * @subsection sys_mg_sw_api_diff 3.1 Application Programming Interface Differences
 *
 * @subsubsection sys_mg_sw_api_diff_sysres 3.1.1 System Resources
 * CV2x uses the @b iav_system_resource structure to describe system resources,
 * including the channel, canvas, and stream. The Cooper Linux SDK splits the @b iav_system_resource structure to
 * create smaller structures. By removing the channel, canvas, and stream from the
 * @b iav_system_resource structure and adding a new input / output control (IOCTL)
 * @b IAV_IOC_SET_CHAN_CONFIG, @b IAV_IOC_SET_CANVAS_CONFIG, and @b IAV_IOC_SET_STREAM_RESOURCE,
 * the Cooper Linux SDK optimizes this process and enables a streamlined configuration. For detailed usage of
 * these new IOCTLs, refer to "Set System Resources Limitations" in the Doxygen image audio / video (IAV) driver application programming interface (API) partition.
 *
 * @subsubsection sys_mg_sw_api_diff_canvas_num 3.1.2 Canvas Number
 * The Cooper chip family supports a maximum canvas number of 20, while CV2x supports a maximum of 12. On CV2x, canvas
 * ID 16 is reserved for the encode from memory (EFM) stream; this has been changed to 24 in the Cooper Linux SDK.
 * Canvas ID 16 indicates the 16th canvas in the Cooper Linux SDK, rather than the ID for the EFM stream.
 * Because the canvas number has been upgraded from 12 to 20, there is potential for size changes to
 * the canvas-related structures, or to the canvas bitmaps. More canvas numbers enable more dynamic
 * random-access memory (DRAM) bandwidth, so the overall DRAM bandwidth may be increased. Users may
 * expect the overall frame rate to be affected if the DRAM bandwidth is the bottleneck.
 *
 * @subsubsection sys_mg_sw_api_diff_stream_num 3.1.3 Stream Number
 * The Cooper chip family supports a maximum stream number of 20, while CV2x supports a maximum of 16.
 * Note that the total encode performance remains unchanged for the Cooper chips, so the individual stream
 * performance may require adjustments to support additional stream numbers.
 * Due to the stream number increasing from 12 to 20, there is potential for size changes
 * to the stream-related structures or the stream bitmaps.
 *
 * @subsubsection sys_mg_sw_api_diff_blur_insertion 3.1.4 Blur Insertion
 * For Cooper chips, dedicated hardware performs blur insertion, and the blur effect is improved to appear
 * more natural. The blur interface is slightly different from CV2x.
 * The information below provides further details on the blur-related interface changes for the Cooper Linux SDK and
 * provides a comparison to CV2x.
 *   - Blur color is no longer required in the Cooper Linux SDK. Blur operations are performed with the color from
 *     the original YUV data in order to provide a more natural appearance.
 *     The blur color can also be enabled for CV5x and later chips, to achieve backward compatible behavior. 
 *   - Compared to the per-8x8 block for CV2x, the per-pixel-level blur granuarity is finer for Cooper chips.
 *     Because per-pixel-level blur granularity uses one bit per pixel in the blur memory, Cooper chips require
 *     a larger DRAM size and greater bandwidth than CV2x.
 *     A bit value of 0 indicates that blur is enabled, while a bit value of 1 indicates that blur is disabled for Cooper chips
 *     (these values are different for CV2x).
 *   - Cooper chips insert blur for each encode frame. There is not an "insert always" flag in the
 *     blur configuration.
 *   - The maximum-supported blur strength level is 4 on Cooper chips and 3 on CV2x.
 *   - Cooper chips supports two types of blur effect: mosaic-like blur and ground-glass-like blur.
 *
 * @subsubsection sys_mg_sw_api_diff_eis 3.1.5 Electronic Image Stabilization
 * Implementation of the electronic image stabilization (EIS) feature in the Cooper chip family differs from that of CV2x.
 * EIS is implemented with two channels in the Cooper Linux SDK, while the CV2x SDK uses a single channel. Using two channels
 * for the EIS feature ensures that there is no extra latency in frames for 3A (auto exposure (AE) / auto white balance (AWB) / auto focus (AF)) statistics.
 * For more details, refer to the EIS Library document in Doxygen, as well as the unit test @b test_eis.
 *
 * @subsubsection sys_mg_sw_api_diff_img_scale 3.1.6 Arbitrary Image Scaler
 * For Cooper chips, users can specify the image offset in the scaler output buffer. For CV2x, the image is always
 * at the top-left corner of the output buffer.
 *
 * @subsubsection sys_mg_sw_api_diff_multi_pass 3.1.7 Multi-Pass
 * The multi-pass feature is redesigned for CV5x and later computer vision (CV) chips (but not applicable to earlier CV2x chips).
 * It is a multi-channel design leveraging multi-region dewarp mode (mode 1) to expand the
 * number of source buffers. Each channel still has only one pass.<br>
 * This feature is supported since Cooper SDK 1.6. For more details, refer to @ref fs_adv_multi_pass.
 *
 * @subsubsection sys_mg_sw_api_diff_custom_sei 3.1.8 Custom SEI
 * The custom SEI feature is redesigned inside DSP / IAV for CV5x and later computer vision (CV) chips.
 * Therefore, the API flow and interfaces are also refined. This feature is supported since Cooper SDK 1.6.
 *
 * The previous CV2x API flow is listed as follows:
 *   1. Enable custom SEI, and configure custom SEI related buffers when set up system resource before preview.
 *      The related parameters are custom_sei / custom_sei_buf_size / custom_sei_buf_num for iav_system_resource.
 *   2. Map the custom SEI memory with IAV_PART_DSP.
 *      For the previous CV2x platform, the custom SEI memory is inside the DSP partition (IAV_PART_DSP) memory.
 *   3. Request custom SEI buffer to write the SEI content.
 *      The API is IAV_IOC_CUSTOM_SEI_REQUEST_BUF.
 *   4. Fill the custom SEI buffer, and set request to IAV.
 *      The API is IAV_IOC_SET_STREAM_CONFIG with IAV_STMCFG_CUSTOM_SEI.
 *
 * The new API flow is listed as follows:
 *   1. Enable custom SEI, and configure custom SEI related buffers when set up stream resource before preview.
 *      The related parameters are custom_sei_possible / custom_sei_data_max_size / custom_sei_buf_num for iav_stream_resource.
 *      These parameters are stream based, so each stream can enable and configure them separately.
 *      The parameter "custom_sei_data_max_size" stands for the maximum custom SEI data size for this stream.
 *   2. Map the custom SEI memory with IAV_PART_CUSTOM_SEI.
 *      For the new implementation, the custom SEI has its dedicated memory partition.
 *   3. Request custom SEI buffer to write the SEI content.
 *      The API is IAV_IOC_GET_STREAM_CONFIG with IAV_STMCFG_CUSTOM_SEI.
 *   4. Fill the custom SEI buffer, and set request to IAV.
 *      The API is IAV_IOC_SET_STREAM_CONFIG with IAV_STMCFG_CUSTOM_SEI.
 *
 * For more details, refer to @ref subsection_custom_sei.
 *
 * @subsubsection sys_mg_sw_api_diff_raw_fps 3.1.9 RAW fps
 * For CV5x and later chips, RAW fps is introduced between VIN fps and IDSP fps, which can potentially save significant
 * DRAM bandwidth for RAW data output, if user needs a lower IDSP processing rate.
 * For CV2x, RAW fps must be the same as VIN fps, which is also sensor fps.
 *
 * The RAW fps is specified with parameter "raw_fps" or "raw_fps_hp" in iav_chan_cfg.
 * For more details, refer to @ref fs_basic_fps.
 *
 *
 * @subsection sys_mg_sw_mem_access 3.2 Memory Access
 * The CV2x platform supports up to 4 GB of DRAM. The DSP and vector processor (VP) hardware can access up
 * to a 32-bit memory address. Therefore, all modules including CPU, DSP, and VP can access the entire 4-GB
 * DRAM without issue.<br>
 * The CV5x platform supports up to 16 GB of DRAM. The DSP and VP hardware can access up to a 32-bit memory
 * address. However, there is a limitation that the DSP and VP hardware can only access up to 4 GB of DRAM.
 * The solution is to separate the memory access ranges for both DSP and VP, enabling VP to access a range
 * from 0 GB to 4 GB, and the DSP to access a range within 4 GB to 8 GB. All memory, including DSP and VP
 * memory, can be accessed by the Arm CPU. The shared memory between DSP and VP is within a 4 GB range with
 * the end address of 4 GB. For more details, refer to Section 2.1.2, "8 GB (or > 8 GB) Memory Layout" in
 * the DRAM Optimization document.
 *
 * DSP memory space is divided into two partitions: the first is DSP private memory, which can be accessed by
 * only DSP and Arm; the other is the DSP shared memory, which can be accessed by DSP, Arm, and VP. If the
 * DRAM size is 8 GB or greater, the DSP private memory starts from the physical memory (4 GB), and the shared
 * memory ends with physical memory (4 GB).
 * Due to the new memory layout introduced on the CV5x platform, there are some special notes:
 *   - The DSP memory address and physical memory address may require translation from one to another. When
 *     the DRAM size is 8 GB or greater, the DSP private memory is mapped from the physical address (4 GB) to
 *     the DSP address (0x0).
 *   - If the DSP output buffer must be accessed by VP hardware, this buffer must be from the DSP shared memory
 *     rather than DSP private memory, which is within the 4-GB limit. For example, the canvas or pyramid
 *     buffer can enable the external memory or manual feed, which will be assigned in the DSP shared memory.
 *     Otherwise, the buffer is located in the DSP private memory, which cannot be directly accessed by the
 *     VP hardware. The typical DSP shared memory partitions may include canvas, pyramid, VOUT onscreen
 *     display (OSD), and overlay. These may be required to be directly accessed by the VP without a memory
 *     copy.
 *   - The graphics direct memory access (GDMA) hardware can only access 32-bit DRAM address; the accessing
 *     memory range is configured to be the same as the DSP in order to accelerate the copy speed for DSP-related
 *     memory.
 *
 *
 * @subsubsection sys_mg_sw_mem_access_cv 3.2.1 Accessing Canvas Data from CV Applications
 * For CV-related use cases, CV applications may require queried canvas data from the IAV
 * driver and send it to the VP for further detection. To avoid extra memory copies, Ambarella suggests that
 * users enable manual feed or external memory for this canvas. This way, the canvas will be from the DSP
 * shared memory and can be directly accessed by the VP without extra copies from the DSP private memory to the
 * VP-accessible memory.
 *
 * If the canvas is enabled with manual feed or external memory, the queried canvas is from the canvas pool
 * (@b IAV_PART_CANVAS_POOL) in the DSP shared memory, and the YUV data is reported with the base address of
 * the canvas pool. Otherwise, the queried canvas is from the DSP partition (@b IAV_PART_DSP), and the YUV data
 * is reported with the base address of the DSP partition.
 *
 * To simplify the process for CV applications to query canvas data, Ambarella suggests that customers use the
 * API @b IAV_IOC_QUERY_INFO with @b IAV_INFO_CANVAS to obtain the base
 * address for the buffer pool of the reported canvas data and the total memory size for this buffer pool.
 * @code {.c}
 * struct iav_canvas_info {
 *      u32 canvas_id : 8;	// Canvas ID
 *      u32 reserved0 : 24;
 *      enum iav_canvas_type type;
 *      enum iav_canvas_state state
 *      u32 reserved1;
 *      unsigned long mem_phys_addr;	// Canvas memory partition base physical address
 *      unsigned long mem_size;		// Canvas memory partition size
 * };
 * @endcode
 *
 * The example usage for this API to obtain buffer pool information is as follows:
 * @code {.c}
 * struct iav_queryinfo query_info;
 * struct iav_canvas_info *canvas_info = NULL;
 * memset(&query_info, 0, sizeof(query_info));
 * query_info.qid = IAV_INFO_CANVAS;
 * canvas_info = &query_info.arg.canvas;
 * canvas_info->canvas_id = p_iav->buffer_id;
 * if (ioctl(fd_iav, IAV_IOC_QUERY_INFO, &query_info) < 0) {
 *      perror("IAV_IOC_QUERY_INFO");
 *      return -1;
 * }
 * // This is the buffer pool size
 * mem_size = canvas_info->mem_size;
 * // This is the virtual memory base
 * virt_base = (uint8_t *)mmap(NULL, mem_size, PROT_READ, MAP_SHARED, p_iav->fd_iav, canvas_info->mem_phys_addr);
 * // This is the physical memory base
 * phy_base = canvas_info->mem_phys_addr;
 * @endcode
 *
 * The example usage to access the YUV data is as follows:
 * @code {.c}
 * struct iav_querydesc query_desc = {0};
 * ------------------------------------------------------
 * query_desc.qid = IAV_DESC_CANVAS;
 * ------------------------------------------------------
 * if (ioctl(fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
 *      perror("IAV_IOC_QUERY_DESC");
 *      return -1;
 * }
 * // This is the canvas luma physical address
 * phy_luma_addr = (phy_base + data_cap->y_addr_offset);
 * // This is the canvas luma virtual address
 * virt_luma_addr = (virt_base + data_cap->y_addr_offset);
 * // This is the canvas chroma physical address
 * phy_chroma_addr = (phy_base + data_cap->uv_addr_offset);
 * // This is the canvas chroma virtual address
 * virt_chroma_addr = (virt_base + data_cap->uv_addr_offset;
 * @endcode
 *
 * - - - -
 *
 * @section sys_mg_ioctl_interface 4. Input / Output Control Interface
 *
 * This chapter describes software migration and provides IOCTL differences between the CV2x SDK and the Cooper Linux SDK.
 * The IOCTLs are as follows:
 * - @ref sys_mg_ioctl_interface_query_info "4.1 IAV_IOC_QUERY_INFO"
 * - @ref sys_mg_ioctl_interface_set_dsp_log "4.2 IAV_IOC_SET_DSP_LOG"
 * - @ref sys_mg_ioctl_interface_drv_dsp_info "4.3 IAV_IOC_DRV_DSP_INFO"
 * - @ref sys_mg_ioctl_interface_s_sys_res "4.4 IAV_IOC_SET_SYSTEM_RESOURCE"
 * - @ref sys_mg_ioctl_interface_g_sys_res "4.5 IAV_IOC_GET_SYSTEM_RESOURCE"
 * - @ref sys_mg_ioctl_interface_s_chan_cfg "4.6 IAV_IOC_SET_CHAN_CONFIG"
 * - @ref sys_mg_ioctl_interface_g_chan_cfg "4.7 IAV_IOC_GET_CHAN_CONFIG"
 * - @ref sys_mg_ioctl_interface_s_canvas_cfg "4.8 IAV_IOC_SET_CANVAS_CONFIG"
 * - @ref sys_mg_ioctl_interface_g_canvas_cfg "4.9 IAV_IOC_GET_CANVAS_CONFIG"
 * - @ref sys_mg_ioctl_interface_s_stream_res "4.10 IAV_IOC_SET_STREAM_RESOURCE"
 * - @ref sys_mg_ioctl_interface_g_stream_res "4.11 IAV_IOC_GET_STREAM_RESOURCE"
 * - @ref sys_mg_ioctl_interface_query_encmode "4.12 IAV_IOC_QUERY_ENC_MODE_CAP"
 * - @ref sys_mg_ioctl_interface_enter_idle "4.13 IAV_IOC_ENTER_IDLE"
 * - @ref sys_mg_ioctl_interface_s_mem_layout_res "4.14 IAV_IOC_SET_MEM_LAYOUT_RESOURCE"
 * - @ref sys_mg_ioctl_interface_g_mem_layout_res "4.15 IAV_IOC_GET_MEM_LAYOUT_RESOURCE"
 * - @ref sys_mg_ioctl_interface_query_mem_layout "4.16 IAV_IOC_QUERY_MEM_LAYOUT_INFO"
 * - @ref sys_mg_ioctl_interface_query_desc "4.17 IAV_IOC_QUERY_DESC"
 * - @ref sys_mg_ioctl_interface_cfg_video_proc "4.18 IAV_IOC_CFG_VIDEO_PROC"
 * - @ref sys_mg_ioctl_interface_g_video_proc "4.19 IAV_IOC_GET_VIDEO_PROC"
 * - @ref sys_mg_ioctl_interface_s_raw_enc_cfg "4.20 IAV_IOC_SET_RAW_ENC_CFG"
 * - @ref sys_mg_ioctl_interface_s_raw_encode "4.21 IAV_IOC_SET_RAW_ENCODE"
 * - @ref sys_mg_ioctl_interface_g_raw_encode "4.22 IAV_IOC_GET_RAW_ENCODE"
 * - @ref sys_mg_ioctl_interface_s_stream_cfg "4.23 IAV_IOC_SET_STREAM_CONFIG"
 * - @ref sys_mg_ioctl_interface_g_stream_cfg "4.24 IAV_IOC_GET_ STREAM_CONFIG"
 * - @ref sys_mg_ioctl_interface_s_blur_insert "4.25 IAV_IOC_SET_BLUR_INSERT"
 * - @ref sys_mg_ioctl_interface_g_blur_insert "4.26 IAV_IOC_GET_ BLUR_INSERT"
 * - @ref sys_mg_ioctl_interface_fram_sync_proc "4.27 IAV_IOC_APPLY_FRAME_SYNC_PROC"
 * - @ref sys_mg_ioctl_interface_query_memblock "4.28 IAV_IOC_QUERY_MEMBLOCK"
 * - @ref sys_mg_ioctl_interface_efm_hsk_frm "4.29 IAV_IOC_EFM_HANDSHAKE_FRAME"
 * - @ref sys_mg_ioctl_interface_efm_set_ext_pool "4.30 IAV_IOC_EFM_SET_EXT_POOL"
 * - @ref sys_mg_ioctl_interface_depre_or_unsupport_ioc "4.31 Depreciated or Unsupported IOCTLs"
 *
 * @subsection sys_mg_ioctl_interface_query_info 4.1 IAV_IOC_QUERY_INFO
 * In the Cooper Linux SDK, selected parameters are diminished in the IOCTL @b IAV_IOC_QUERY_INFO.
 * The removed information ID is as follows:
 *   - IAV_INFO_MULTI_COLOR_MASK
 *
 * @subsection sys_mg_ioctl_interface_set_dsp_log 4.2 IAV_IOC_SET_DSP_LOG
 * The Cooper Linux SDK adds new parameters in the structure `iav_dsplog_setup`, as shown below.
 * @code {.c}
 * struct iav_dsplog_setup {
 *      .......
 *      u32	module;	//  DSP modules map.
 *      u32	level;	//  DSP log level.
 *                   // Log level:
 *                   // 0 :  Silent
 *                   // 1 :  MINIMAL
 *                   // 2 :  NORMAL
 *                   // 3 :  VERBOSE
 *                   // 4 :  DEBUG
 *      u32	mask;
 *      .......
 * };
 * @endcode
 *
 * @subsection sys_mg_ioctl_interface_drv_dsp_info 4.3 IAV_IOC_DRV_DSP_INFO
 * The Cooper Linux SDK removes selected parameters in the structure @b iav_driver_dsp_info.
 * In this structure, `dspout` and `dspin` are removed.
 *
 * @subsection sys_mg_ioctl_interface_s_sys_res 4.4 IAV_IOC_SET_SYSTEM_RESOURCE
 * The following lists the changes in the structure parameter `iav_system_resource`
 * for the IOCTL @b IAV_IOC_SET_SYSTEM_RESOURCE.<br>
 * The Cooper Linux SDK modifies parameters in the structure @b iav_img_scale_cfg, as follows:
 * <table>
 * <caption>Table 4-1. iav_img_scale_cfg Structure Definition.</caption>
 * <tr><th>Parameter             <th>Change            <th>Notes
 * <tr><td>"src_buf_id"          <td>Removed           <td>
 * <tr><td>"max_input_width"     <td>Removed           <td>Replaced with `max_input`
 * <tr><td>"max_output_width"    <td>Removed           <td>Replaced with `max_output`
 * <tr><td>"max_input"           <td>Added             <td>Specifies the maximum input
 * <tr><td>"max_output"          <td>Added             <td>Specifies the maximum output
 * <tr><td>"format"              <td>Added             <td>Specifies the image scale data format of the input and output image
 * <tr><td>"output"              <td>Updated           <td>Replaced with the `iav_rect` structure from the `iav_window` structure to support image scaling to a dedicated offset instead of always 0x0
 * </table>
 *
 * The Cooper Linux SDK modifies parameters in the structure `iav_system_resource`, as follows:
 * <table>
 * <caption>Table 4-2. iav_system_resource Structure Definition.</caption>
 * <tr><th>Parameter                       <th>Change  <th>Notes
 * <tr><td>"raw_pitch_in_bytes"            <td>Removed <td>
 * <tr><td>"total_memory_size"             <td>Removed <td>
 * <tr><td>"iso_type"                      <td>Removed <td>
 * <tr><td>"is_stitched"                   <td>Removed <td>
 * <tr><td>"vout_only"                     <td>Removed <td>
 * <tr><td>"insert_blur_enable"            <td>Removed <td>
 * <tr><td>"enable_vin_precise_sync"       <td>Removed <td>
 * <tr><td>"back_pressure_margin"          <td>Removed <td>
 * <tr><td>"insert_mc_mask_enable"         <td>Removed <td>
 * <tr><td>"emirror_vout_sync_enable"      <td>Removed <td>
 * <tr><td>"custom_sei"                    <td>Removed <td>
 * <tr><td>"blend_stitch_type"             <td>Removed <td>
 * <tr><td>"prev_bottom_repeat_disabled"   <td>Removed <td>
 * <tr><td>"dynamic_slice"                 <td>Removed <td>
 * <tr><td>"blur_vout_mixer"               <td>Removed <td>
 * <tr><td>"enc_raw_fast_enable"           <td>Removed <td>
 * <tr><td>"enabled_canvas_frame_tag"      <td>Removed <td>
 * <tr><td>"raw_size"                      <td>Removed <td>
 * <tr><td>"custom_sei_buf_size"           <td>Removed <td>
 * <tr><td>"custom_sei_buf_num"            <td>Removed <td>
 * <tr><td>"enc_dummy_latency"             <td>Removed <td>
 * <tr><td>"dsp_api_thread_freq"           <td>Removed <td>
 * <tr><td>"eis_delay_count"               <td>Removed <td>
 * <tr><td>"low_delay_state_switch_enable" <td>Removed <td>
 * <tr><td>"debug_stitched"                <td>Removed <td>
 * <tr><td>"debug_skip_efm_mb"             <td>Removed <td>
 * <tr><td>"debug_vp_dram_priority"        <td>Removed <td>
 * <tr><td>"debug_hevc_hi_dram_ef_mode"    <td>Removed <td>
 * <tr><td>"debug_reset_seq_num_in_idle"   <td>Removed <td>
 * <tr><td>"stream"                        <td>Removed <td>The stream resource configuration is moved to the new IOCTL @b IAV_IOC_SET_STREAM_RESOURCE
 * <tr><td>"chan_cfg"                      <td>Removed <td>The channel resource configuration is moved to the new IOCTL @b IAV_IOC_SET_CHAN_CONFIG
 * <tr><td>"canvas_cfg"                    <td>Removed <td>The canvas resource configuration is moved to the new IOCTL @b IAV_IOC_SET_CANVAS_CONFIG
 * <tr><td>"chan_map"                      <td>Added   <td>Specifies the channel map
 * <tr><td>"canvas_map"                    <td>Added   <td>Specifies the canvas map
 * <tr><td>"stream_map"                    <td>Added   <td>Specifies the stream map
 * <tr><td>"avc_pjpeg_size_MB_per_tile"    <td>Added   <td>Specifies the DRAM size of the advanced video coding (AVC) JPEG encoding buffer
 * <tr><td>"debug_max_chroma_radius"       <td>Added   <td>Specifies the maximum chroma radius
 * <tr><td>"debug_ce_off"                  <td>Added   <td>Disables chroma enhancement (CE)
 * <tr><td>"debug_perf_opt_enable"         <td>Added   <td>Enables / disables DSP performance optimal mode
 * <tr><td>"debug_low_delay_enable"        <td>Added   <td>Enables / disables low delay mode for mode 0
 * <tr><td>"debug_preblend_only_for_aisp"  <td>Added   <td>Enables preblend pass only for AISP (mode 9)
 * <tr><td>"vout_back_pressure_margin"     <td>Added   <td>Specifies the IDSP VOUT back pressure margin
 * <tr><td>"mjpeg_pjpeg_size_MB_per_tile"  <td>Added   <td>Specify the DRAM size of the MJPEG / PJPEG encoding buffer
 * <tr><td>"vin_frame_broken_dummy_repeat" <td>Added   <td>Enables / disables last good frame repeat when a broken frame is detected
 * <tr><td>"debug_chan_group_tolerance"    <td>Added   <td>Specify the group sync tolerance value to adapt the end-of-frame (EOF) drift between sensors within a group
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_g_sys_res 4.5 IAV_IOC_GET_SYSTEM_RESOURCE
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_SET_SYSTEM_RESOURCE.
 *
 * @subsection sys_mg_ioctl_interface_s_chan_cfg 4.6 IAV_IOC_SET_CHAN_CONFIG
 * CV2x uses IOCTL @b IAV_IOC_SET_SYSTEM_RESOURCE to configure the channel resource.
 * The Cooper Linux SDK adds a new IOCTL @b IAV_IOC_SET_CHAN_CONFIG to configure the channel resource;
 * it uses the same structure, `iav_chan_cfg`.
 * The structure parameter changes for the Cooper Linux SDK are listed below:
 * <table>
 * <caption>Table 4-3. iav_chan_cfg Structure Definition.</caption>
 * <tr><th>Parameter                    <th>Change  <th>Notes
 * <tr><td>"input"                      <td>Removed <td>
 * <tr><td>"mctf_10bit_ref"             <td>Removed <td>
 * <tr><td>"main_burst_tile"            <td>Removed <td>
 * <tr><td>"vin_overflow_protection"    <td>Removed <td>
 * <tr><td>"low_delay_vin_vout"         <td>Removed <td>
 * <tr><td>"is_still_fusion_proc"       <td>Removed <td>
 * <tr><td>"mc_mask_buf_ds"             <td>Removed <td>
 * <tr><td>"raw_vflip"                  <td>Removed <td>
 * <tr><td>"enable_tml_raw_packing"     <td>Removed <td>
 * <tr><td>"enable_tml_proc"            <td>Removed <td>
 * <tr><td>"is_mo_fusion_img_cfg_chan"  <td>Removed <td>
 * <tr><td>"raw_dsp_priv_dram"          <td>Removed <td>
 * <tr><td>"srcbuf_to_fusion"           <td>Removed <td>
 * <tr><td>"hdec_raw_format"            <td>Removed <td>
 * <tr><td>"orig_idsp_fps_hp"           <td>Removed <td>
 * <tr><td>"debug_stitch_tile_num"      <td>Removed <td>
 * <tr><td>"enable_group"               <td>Renamed <td>New name: "group_enable"
 * <tr><td>"chan_id"                    <td>Added   <td>Specifies channel ID
 * <tr><td>"c2y_burst_tile"             <td>Removed <td>Enables / disables c2y burst tile mode
 * <tr><td>"y12_enable"                 <td>Added   <td>Enables / disables c2y y12 output
 * <tr><td>"y12_cached_items"           <td>Added   <td>Queries with blocking call
 * <tr><td>"slice_cfg_enable"           <td>Added   <td>Enables / disables slice-related configurations
 * <tr><td>"slice_num"                  <td>Added   <td>Specifies the channel's slice number, automatically calculated by IAV
 * <tr><td>"slice_width"                <td>Added   <td>Specifies the channel's slice width
 * <tr><td>"slice_num"                  <td>Added   <td>Specifies the channel's slice number
 * <tr><td>"raw_padding_width"          <td>Added   <td>Specifies the channel's padding width for RAW data when IDSP stitching is used
 * <tr><td>"warp_padding_width"         <td>Added   <td>Specifies the channel's padding width for YUV data at warp stage when IDSP stitching is used
 * <tr><td>"high_perf_enable"           <td>Added   <td>Enables IDSP high performance mode (obsolete)
 * <tr><td>"ext_mem"                    <td>Added   <td>Enables / disables external memory for raw
 * <tr><td>"chan_input_src"             <td>Added   <td>Sets the input source for the channel
 * <tr><td>"idsp_core_cfg_enable"       <td>Added   <td>Enables / disables customized IDSP core mode
 * <tr><td>"idsp_core_mode"             <td>Added   <td>Specifies IDSP core mode
 * <tr><td>"raw_src_chan"               <td>Added   <td>Specifies the EIS or dewarp channel's input source channel
 * <tr><td>"eis_delay_count"            <td>Added   <td>Updated from 3 bits to 7 bits to support greater EIS delay count values
 * <tr><td>"reuse_src_chan_iso_cfg"     <td>Added   <td>Enables duplicated 3A configurations from master channel
 * <tr><td>"pre_dec_enable"             <td>Added   <td>Enables decoding first to generate YUV before going through IDSP pipeline
 * <tr><td>"pre_dec_type"               <td>Added   <td>Specifies the decoder type when `pre_dec_enable` = 1
 * <tr><td>"img_stats_enable_group"     <td>Added   <td>Enables grouping for 3A control
 * <tr><td>"img_stats_group_idx"        <td>Added   <td>Specifies the group index of 3A statistic data
 * <tr><td>"vin_roi_idx"                <td>Added   <td>Specifies the VIN region of interest (ROI) index, when VIN ROI is enabled
 * <tr><td>"ca_warp_enable"             <td>Added   <td>Enables / disables the client application (CA) warp function
 * <tr><td>"raw_slice_num"              <td>Added   <td>Specifies the capture slice number for RAW data
 * <tr><td>"raw_slice_cached_items"     <td>Added   <td>Specifies the RAW slice cached items to query RAW with blocking call
 * <tr><td>"raw_width"                  <td>Added   <td>Read-only option to report the RAW width for the current channel
 * <tr><td>"raw_height"                 <td>Added   <td>Read-only option to report the RAW height for the current channel
 * <tr><td>"isp_nn_enable"              <td>Added   <td>Enables / disables ISP NN, such as True Motion
 * <tr><td>"motion_output_enable"       <td>Added   <td>Enables / disables motion buffer output from IDSP channel
 * <tr><td>"motion_cached_items"        <td>Added   <td>Specifies the motion buffer cached items for user to query
 * <tr><td>"src_from_canvas_enable"     <td>Added   <td>Enables / disables channel input from the specified canvas, for multi-pass feature
 * <tr><td>"src_canvas_id"              <td>Added   <td>Specifies the source canvas ID, for multi-pass feature
 * <tr><td>"raw_fps"                    <td>Added   <td>Specifies the RAW fps between VIN fps and IDSP fps
 * <tr><td>"raw_fps_hp"                 <td>Added   <td>Specifies the high precision RAW fps between VIN fps and IDSP fps
 * <tr><td>"ver_slice_num"              <td>Added   <td>Specifies the IDSP vertical slice number
 * <tr><td>"raw_padding_height"         <td>Added   <td>Specifies the RAW DATA padding height, for multiple IDSP vertical slices feature
 * <tr><td>"idsp_bypass_enable"         <td>Added   <td>Enables / disables IDSP bypass to enable DSP to encode from YUV input directly
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_g_chan_cfg 4.7 IAV_IOC_GET_CHAN_CONFIG
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_SET_CHAN_CONFIG.
 *
 * @subsection sys_mg_ioctl_interface_s_canvas_cfg 4.8 IAV_IOC_SET_CANVAS_CONFIG
 * CV2x uses the IOCTL @b IAV_IOC_SET_SYSTEM_RESOURCE to configure canvas resources.
 * The Cooper Linux SDK adds a new IOCTL @b IAV_IOC_SET_CANVAS_CONFIG to configure the canvas resources;
 * it uses the same structure, `iav_canvas_cfg`.
 * The structure parameter changes for the Cooper Linux SDK are listed below:
 * <table>
 * <caption>Table 4-4. iav_canvas_cfg Structure Definition.</caption>
 * <tr><th>Parameter                      <th>Change  <th>Notes
 * <tr><td>"dsp_priv_dram"                <td>Removed <td>
 * <tr><td>"order"                        <td>Removed <td>
 * <tr><td>"is_broken"                    <td>Removed <td>
 * <tr><td>"canvas_id"                    <td>Added   <td>Specifies the canvas ID
 * <tr><td>"ext_mem"                      <td>Added   <td>Specifies the external memory for the canvas
 * <tr><td>"blend_stitch_type"            <td>Added   <td>Specifies the blend type for multi-channel stitching
 * <tr><td>"clear_background"             <td>Added   <td>Enables / disables clearing the canvas data in the background color before preview
 * <tr><td>"buf_offset_enable"            <td>Added   <td>Enables / disables source buffer offset in a single-view canvas
 * <tr><td>"blur_enable"                  <td>Added   <td>Enables / disables blur operations from the specific canvas
 * <tr><td>"max_blur_area_num"            <td>Added   <td>Specifies the maximum number of blur areas
 * <tr><td>"blend_copy_num_minus_1"       <td>Added   <td>Specifies the copy sides, minus 1, of the blending area
 * <tr><td>"blend_warp_enable"            <td>Added   <td>Enables / disables H-warp for blending overlap region
 * <tr><td>"blend_stitch_circular_margin" <td>Added   <td>Specifies the overlap margin of the last blend channel and first blend channel
 * <tr><td>"enc_extra_padding_enable"     <td>Added   <td>Disables / enables extra padding for stream encoding
 * <tr><td>"hevc_width_align_enable"      <td>Added   <td>Disables / enables canvas width alignment to improve HEVC encoding efficiency
 * <tr><td>"low_delay_enable"             <td>Added   <td>Disables / enables low delay output with multiple IDSP veritical slices
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_g_canvas_cfg 4.9 IAV_IOC_GET_CANVAS_CONFIG
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_SET_CANVAS_CONFIG.
 *
 * @subsection sys_mg_ioctl_interface_s_stream_res 4.10 IAV_IOC_SET_STREAM_RESOURCE
 * CV2x uses the IOCTL @b IAV_IOC_SET_SYSTEM_RESOURCE to configure the stream resource.
 * The Cooper Linux SDK adds a new IOCTL, @b IAV_IOC_SET_STREAM_RESOURCE, to configure the stream resource;
 * it uses the same structure, @b iav_stream_resource.  The structure parameter
 * change for the Cooper Linux SDK is as follows:
 *   - Add the parameter `stream_id`.  This is used to specify the stream ID.
 *   - Add the parameter `efm_ext_mem`. This is used to enable the user-managed external EFM frame buffer.
 *   - Add the parameter `hevc_width_align_enable`. This is used to enable the HEVC width alignment for encoding efficiency.
 *   - Add the parameter `custom_sei_possible`. This is used to enable the customized SEI insertion into the stream.
 *   - Add the parameter `custom_sei_buf_num`. This is used to specify the customized SEI buffer number for the stream.
 *   - Add the parameter `custom_sei_data_max_size`. This is used to specify the customized SEI buffer max size for the stream.
 *
 * @subsection sys_mg_ioctl_interface_g_stream_res 4.11 IAV_IOC_GET_STREAM_RESOURCE
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_SET_STREAM_RESOURCE.
 *
 * @subsection sys_mg_ioctl_interface_query_encmode 4.12 IAV_IOC_QUERY_ENC_MODE_CAP
 * The following lists the changes in the structure parameter `iav_enc_mode_cap`
 * for the IOCTL @b IAV_IOC_QUERY_ENC_MODE_CAP:
 * <table>
 * <caption>Table 4-5. iav_enc_mode_cap Structure Definition.</caption>
 * <tr><th>Parameter            <th>Change  <th>Notes
 * <tr><td>"vout_swap_possible" <td>Removed <td>
 * <tr><td>"mc_mask_possible"   <td>Removed <td>
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_enter_idle 4.13 IAV_IOC_ENTER_IDLE
 * The following lists the changes in the structure parameter `iav_dsp_boot_params`
 * for the IOCTL @b IAV_IOC_ENTER_IDLE.
 * <table>
 * <caption>Table 4-6. iav_dsp_boot_params Structure Definition.</caption>
 * <tr><th>Parameter                        <th>Change  <th>Notes
 * <tr><td>"vout_profile"                   <td>Removed <td>
 * <tr><td>"osd_profile"                    <td>Removed <td>
 * <tr><td>"vout_profile_flag"              <td>Removed <td>
 * <tr><td>"vout_osd_profile_flag"          <td>Removed <td>
 * <tr><td>"dsp_private_dram_flag"          <td>Removed <td>
 * <tr><td>"dsp_max_fb_num_flag"            <td>Removed <td>
 * <tr><td>"vout_underflow_prevention_flag" <td>Removed <td>
 * <tr><td>"support_vout_rotate_flag"       <td>Removed <td>
 * <tr><td>"vout_back_pressure_margin_flag" <td>Removed <td>
 * <tr><td>"dsp_max_fb_num"                 <td>Removed <td>
 * <tr><td>"vout_underflow_prevention"      <td>Removed <td>
 * <tr><td>"vout0_support_rotate"           <td>Removed <td>
 * <tr><td>"vout1_support_rotate"           <td>Removed <td>
 * <tr><td>"vout0_back_pressure_margin"     <td>Removed <td>
 * <tr><td>"vout1_back_pressure_margin"     <td>Removed <td>
 * <tr><td>"bsh_no_reset"                   <td>Removed <td>
 * <tr><td>"bsh_no_reset_flag"              <td>Removed <td>
 * <tr><td>"vout_status_msg_flag"           <td>Removed <td>
 * <tr><td>"vout_status_msg"                <td>Removed <td>
 * <tr><td>"dsp_private_dram_addr"          <td>Removed <td>
 * <tr><td>"dsp_private_dram_size"          <td>Removed <td>
 * <tr><td>"vout_osd_rescale_flag"          <td>Added   <td>Configures `vout_osd_rescale_disable`
 * <tr><td>"vout_osd_rescale_disable"       <td>Added   <td>Disables VOUT OSD rescale
 * <tr><td>"vout_possible_map_flag"         <td>Added   <td>Configures `vout_possible_map`
 * <tr><td>"vout_possible_map"              <td>Added   <td>Possible VOUT map when booting DSP
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_s_mem_layout_res 4.14 IAV_IOC_SET_MEM_LAYOUT_RESOURCE
 * The following lists the changes in the structure parameter `iav_mem_cfg_chan`
 * for the IOCTL @b IAV_IOC_SET_MEM_LAYOUT_RESOURCE.
 * <table>
 * <caption>Table 4-7. iav_mem_cfg_chan Structure Definition.</caption>
 * <tr><th>Parameter              <th>Change  <th>Notes
 * <tr><td>"mc_mask_possible"     <td>Removed <td>
 * <tr><td>"mc_mask_buf_max_num"  <td>Removed <td>
 * <tr><td>"mc_mask_buf_ds"       <td>Removed <td>
 * <tr><td>"tfc_possible"         <td>Removed <td>
 * <tr><td>"tfc_buf_max_num"      <td>Removed <td>
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_g_mem_layout_res 4.15 IAV_IOC_GET_MEM_LAYOUT_RESOURCE
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_SET_MEM_LAYOUT_RESOURCE.
 *
 * @subsection sys_mg_ioctl_interface_query_mem_layout 4.16 IAV_IOC_QUERY_MEM_LAYOUT_INFO
 * The following lists the changes in the structure parameter `iav_mem_layout_info`
 * for the IOCTL @b IAV_IOC_QUERY_MEM_LAYOUT_INFO.
 * <table>
 * <caption>Table 4-8. iav_mem_layout_info Structure Definition.</caption>
 * <tr><th>Parameter         <th>Change  <th>Notes
 * <tr><td>"mc_mask_layout"  <td>Removed <td>
 * <tr><td>"tfc_layout"      <td>Removed <td>
 * <tr><td>"raw_pool_layout" <td>Added   <td>Queries each VIN's memory layout in raw pool
 * </table>
 *
 * The definition of the structure @b iav_mem_layout_raw_pool is shown below:
 * @code {.c}
 * struct iav_mem_layout_raw_pool {
 *      unsigned long phys_base;	// Physical memory base address.
 *      u32 total_user_size;		// Total memory size for user configuration.
 *      u32 total_size;				// Total memory size.
 *      struct iav_mem_layout buf_layout[IAV_MAX_REAL_VIN_NUM];	// Buffer layout info.
 * };
 * @endcode
 *
 * @subsection sys_mg_ioctl_interface_query_desc 4.17 IAV_IOC_QUERY_DESC
 * The following lists the changes in the structure parameter `iav_querydesc` for the IOCTL @b IAV_IOC_QUERY_DESC.
 * <table>
 * <caption>Table 4-9. iav_querydesc Structure Definition.</caption>
 * <tr><th>Parameter      <th>Change  <th>Notes
 * <tr><td>"tml"          <td>Removed <td>
 * <tr><td>"dis"          <td>Removed <td>
 * <tr><td>"y12"          <td>Added   <td>Queries a single Y12 image
 * <tr><td>"raw"          <td>Updated <td>Added parameter `delay_frames` for EIS delay frames to query raw data from this channel
 * <tr><td>"blend"        <td>Updated <td>Added parameter `canvas_id` to query canvas-based blending options
 * <tr><td>"statis"       <td>Updated <td>Added parameter `data2_addr_offset_valid` and `data2_addr_offset` to support the frame's second status for the second core, when dual-core spatial encode mode is used.
 * <tr><td>"custom_aisp"  <td>Added   <td>Queries custom AISP buffer information
 * <tr><td>"raw_slice"    <td>Updated <td>Queries RAW slice buffer information
 * <tr><td>"motion"       <td>Added   <td>Queries a motion data from the IDSP channel
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_cfg_video_proc 4.18 IAV_IOC_CFG_VIDEO_PROC
 * The following lists the changes in the structure parameter `iav_video_proc`
 * for the IOCTL @b IAV_IOC_CFG_VIDEO_PROC.
 * <table>
 * <caption>Table 4-10. iav_video_proc Structure Definition.</caption>
 * <tr><th>Parameter       <th>Change  <th>Notes
 * <tr><td>"canvas_order"  <td>Removed <td>
 * <tr><td>"canvas_dptz"   <td>Removed <td>
 * <tr><td>"blend_warp"    <td>Added   <td>
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_g_video_proc 4.19 IAV_IOC_GET_VIDEO_PROC
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_CFG_VIDEO_PROC.
 *
 * @subsection sys_mg_ioctl_interface_s_raw_enc_cfg 4.20 IAV_IOC_SET_RAW_ENC_CFG
 * CV2x uses the IOCTL @b IAV_IOC_SET_RAW_ENCODE to configure and perform raw encode.
 * The IOCTL @b IAV_IOC_SET_RAW_ENC_CFG is added in the Cooper Linux SDK to configure the raw encode first.
 * Then, it uses @b IAV_IOC_SET_RAW_ENCODE to perform raw encode and adds
 * the structure @b iav_raw_enc_cfg. New parameters in
 * the structure @b iav_raw_enc_cfg are shown below:
 * @code {.c}
 * struct iav_raw_enc_cfg {
 *      u8 vinc_id;				// VIN Control ID
 *      u8 total_buf_num;		// Data total buf num
 *      u8 reserved[2];
 *      u32 raw_pitch : 16;		// RAW data pitch
 *      u32 raw_hdec_pitch : 16; // HDEC data pitch
 *      u32 raw_width : 16;		// RAW data width
 *      u32 raw_hdec_width : 16; // HDEC data width
 *      u32 raw_height : 16;		// RAW data height
 *      u32 raw_hdec_height : 16; // HDEC data height
 *      unsigned long raw_buf_addr;	// RAW data DRAM addr
 *      unsigned long raw_hdec_buf_addr; // HDEC data DRAM addr
 * };
 * @endcode
 *
 * @subsection sys_mg_ioctl_interface_s_raw_encode 4.21 IAV_IOC_SET_RAW_ENCODE
 * The following lists the changes in the structure parameter `iav_raw_enc_setup`
 * for the IOCTL @b IAV_IOC_SET_RAW_ENCODE.
 * The memory configuration parameters are moved to the IOCTL @b IAV_IOC_SET_RAW_ENC_CFG.
 * <table>
 * <caption>Table 4-11. iav_raw_enc_setup Structure Definition.</caption>
 * <tr><th>Parameter                <th>Change  <th>Notes
 * <tr><td>"raw_frame_size"         <td>Removed <td>
 * <tr><td>"raw_hdec_size"          <td>Removed <td>
 * <tr><td>"preblend_size"          <td>Removed <td>
 * <tr><td>"pitch"                  <td>Removed <td>
 * <tr><td>"raw_hdec_dpitch"        <td>Removed <td>
 * <tr><td>"preblend_dpitch"        <td>Removed <td>
 * <tr><td>"raw_frame_num"          <td>Removed <td>
 * <tr><td>"use_ext_buf"            <td>Removed <td>
 * <tr><td>"raw_format"             <td>Removed <td>
 * <tr><td>"hdec_raw_format"        <td>Removed <td>
 * <tr><td>"raw_daddr_offset"       <td>Removed <td>
 * <tr><td>"raw_hdec_daddr_offset"  <td>Removed <td>
 * <tr><td>"preblend_daddr_offset"  <td>Removed <td>
 * <tr><td>"ext_buf_addr"           <td>Removed <td>
 * <tr><td>"raw_daddr_buf_idx"      <td>Added   <td>Specifies the RAW data buffer index
 * <tr><td>"raw_hdec_daddr_buf_idx" <td>Added   <td>Specifies the HDEC data buffer index
 * <tr><td>"mono_pts"               <td>Added   <td>Synchronizes with IDSP configurations for the EIS feature
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_g_raw_encode 4.22 IAV_IOC_GET_RAW_ENCODE
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_SET_RAW_ENCODE.
 *
 * @subsection sys_mg_ioctl_interface_s_stream_cfg 4.23 IAV_IOC_SET_STREAM_CONFIG
 * The following lists the changes in the structure parameter `iav_stream_cfg`
 * for the IOCTL @b IAV_IOC_SET_STREAM_CONFIG.
 * <table>
 * <caption>Table 4-12. iav_stream_cfg Structure Definition.</caption>
 * <tr><th>Parameter   <th>Change   <th>Notes
 * <tr><td>"format"    <td>Updated  <td>The parameter `enc_src_map` in the structure `iav_stream_format`
 *                                      is extended from 16 bits to 32 bits due to the support of
 *                                      up to 20 streams
 * <tr><td>"custom_sei" <td>Added   <td>The new structure to specify the customized SEI configuration
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_g_stream_cfg 4.24 IAV_IOC_GET_ STREAM_CONFIG
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_SET_STREAM_CONFIG.
 *
 * @subsection sys_mg_ioctl_interface_s_blur_insert 4.25 IAV_IOC_SET_BLUR_INSERT
 * The following lists the changes in the structure parameter `iav_blur_insert` for
 * the IOCTL @b IAV_IOC_SET_BLUR_INSERT.
 * <table>
 * <caption>Table 4-13. iav_blur_insert Structure Definition.</caption>
 * <tr><th>Parameter         <th>Change  <th>Notes
 * <tr><td>"insert_always"   <td>Removed <td>The blur will always insert into the stream input canvas; there no option to turn it off
 * <tr><td>"area"            <td>Updated <td>The `iav_blur_area` structure update information is listed in the following table
 * </table>
 * The table below lists the structure parameter @b iav_blur_area inside structure @b iav_blur_insert.
 * <table>
 * <caption>Table 4-14. iav_blur_area Structure Definition.</caption>
 * <tr><th>Parameter       <th>Change  <th>Notes
 * <tr><td>"color_enable"  <td>Added   <td>Specifies whether the blur color is enabled or not for this blur area
 * <tr><td>"is_blocky"     <td>Added   <td>Specifies the blur effect.  0: Blur without blocky effect. 1: Blur with blocky effect
 * <tr><td>"coeff"         <td>Added   <td>Specifies the blur coefficients, range 0 ~ 3 when `is_blocky` is 0 and range 0 ~ 2 when `is_blocky` is 1.
 *                                         0: Weakest blur coefficients
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_g_blur_insert 4.26 IAV_IOC_GET_BLUR_INSERT
 * Refer to the structure parameter change from the IOCTL @b IAV_IOC_SET_BLUR_INSERT.
 *
 * @subsection sys_mg_ioctl_interface_fram_sync_proc 4.27 IAV_IOC_APPLY_FRAME_SYNC_PROC
 * The following lists the changes in the structure parameter `iav_apply_frame_sync` for the IOCTL @b IAV_IOC_APPLY_FRAME_SYNC_PROC.
 * <table>
 * <caption>Table 4-15. iav_apply_frame_sync Structure Definition.</caption>
 * <tr><th>Parameter                 <th>Change    <th>Notes
 * <tr><td>"stream_updated_map"      <td>Updated   <td>The parameter `stream_updated_map` is extended from 16 bits to 28 bits, due to the
 *                                                     support of up to 20 streams
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_query_memblock 4.28 IAV_IOC_QUERY_MEMBLOCK
 * Query IAV_MEM_IMG_FIFO is removed from enum @b iav_mem_id. Users can now only query partition or canvas memory block information.
 * The following lists the changes in the enumeration parameter `iav_mem_part_id` for the IOCTL @b IAV_IOC_QUERY_MEMBLOCK.
 * <table>
 * <caption>Table 4-16. iav_mem_part_id Enumeration Definition.</caption>
 * <tr><th>Parameter                   <th>Change    <th>Notes
 * <tr><td>"IAV_PART_IMG_STATIS"       <td>Removed   <td>
 * <tr><td>"IAV_PART_DIS_CTB_STATIS"   <td>Removed   <td>
 * <tr><td>"IAV_PART_H26X_SCALELIST"   <td>Renamed   <td>HEVC and AVC scalelist partition
 * <tr><td>"IAV_PART_DEC_BSB"          <td>Added     <td>Decoder BSB buffer partition
 * <tr><td>"IAV_PART_DSP_CV"           <td>Added     <td>Partition ID for DSP and CV internal share
 * <tr><td>"IAV_PART_VOUT0_FB"         <td>Added     <td>VOUT0 frame buffer partition
 * <tr><td>"IAV_PART_VOUT1_FB"         <td>Added     <td>VOUT1 frame buffer partition
 * <tr><td>"IAV_PART_VOUT2_FB"         <td>Added     <td>VOUT2 frame buffer partition
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_efm_hsk_frm 4.29 IAV_IOC_EFM_HANDSHAKE_FRAME
 * The following lists the changes in the structure parameter `iav_efm_handshake_frame` for the IOCTL @b IAV_IOC_EFM_HANDSHAKE_FRAME.
 * <table>
 * <caption>Table 4-17. iav_efm_handshake_frame Structure Definition.</caption>
 * <tr><th>Parameter            <th>Change    <th>Notes
 * <tr><td>"yuv_ext_offset"     <td>Added     <td>EFM YUV offset inside of YUV partition; should only be used when @ref efm_ext_mem = 1
 * <tr><td>"me_ext_offset"      <td>Added     <td>EFM ME offset inside of ME partition; should only be used when @ref efm_ext_mem = 1
 * </table>
 *
 * @subsection sys_mg_ioctl_interface_efm_set_ext_pool 4.30 IAV_IOC_EFM_SET_EXT_POOL
 * The structure `iav_efm_ext_pool` and IOCTL @b IAV_IOC_EFM_SET_EXT_POOL are added to set EFM external memory infomation to IAV.
 * The `iav_efm_ext_pool` structure definition is shown below:
 * @code {.c}
 * struct iav_efm_ext_pool {
 *      u32 stream_id;		// EFM stream id
 *      u32 yuv_buf_pid;	// EFM YUV buffer partition id
 *      u32 me_buf_pid;		// EFM ME buffer partition id. No need when stream is MJPEG.
 *      u32 yuv_pitch;		// YUV buffer pitch.
 *      u32 me1_pitch;		// me1 buffer pitch.
 *      u32 me0_pitch;		// me0 buffer pitch.
 *      struct iav_window me1_size;	// me1 image size.
 *      struct iav_window me0_size;	// me0 image size.
 * };
 * @endcode
 *
 * @subsection sys_mg_ioctl_interface_depre_or_unsupport_ioc 4.31 Deprecated or Unsupported IOCTLs
 * <table>
 * <caption>Table 4-18. Deprecated or Unsupported IOCTLs.</caption>
 * <tr><th>IOCTL                                       <th>Notes
 * <tr><td>IAV_IOC_SET_DSP_VP_CFG                      <td>Removed
 * <tr><td>IAV_IOC_GET_DSP_VP_CFG                      <td>Removed
 * <tr><td>IAV_IOC_DSP_AUTH                            <td>Removed
 * <tr><td>IAV_IOC_GET_SYSTEM_CONFIG                   <td>Removed, because there is no single system configuration.
 *                                                         The system configuration is now separated into smaller configurations,
 *                                                         such as channel configuration, canvas configuration, and stream configuration
 * <tr><td>IAV_IOC_SET_FASTOSD_INSERT                  <td>Removed
 * <tr><td>IAV_IOC_GET_FASTOSD_INSERT                  <td>Removed
 * <tr><td>IAV_IOC_CUSTOM_SEI_REQUEST_BUF              <td>Removed
 * <tr><td>IAV_IOC_CTRL_DSP_DUMP_CMD                   <td>Removed
 * <tr><td>IAV_IOC_QUERY_DSP_DUMP_CMD                  <td>Removed
 * <tr><td>IAV_IOC_SET_TML_CONFIG                      <td>Not implemented
 * <tr><td>IAV_IOC_GET_TML_CONFIG                      <td>Not implemented
 * <tr><td>IAV_IOC_RELEASE_FRAMEDESC                   <td>Not implemented
 * <tr><td>IAV_IOC_FLUSH_FRAMEDESC                     <td>Not implemented
 * </table>
 *
 * - - - -
 *
 * @section sys_mg_unit_test 5. Unit Test
 * This chapter describes the unit test tool differences between CV2x and the Cooper chip family.
 *
 * @subsection sys_mg_unit_test_encode 5.1 test_encode
 * The CV2x and Cooper chip families both utilize the unit test `test_encode` to support single- and multi-VIN cases.
 * This test can support both Lua scripts and command lines for single-VIN cases.
 *
 * For multi-VIN cases, only Lua scripts are supported.
 *
 * The Cooper family of chips adds another option, `--vout-cfg`, which enables
 * users to configure VOUT from the Lua script.
 *
 * - - - -
 *
 * @section sys_mg_tools 6. Tools
 * This chapter describes how to upgrade the firmware and use the tools for Linux and the CVflow® processor.
 *
 * @subsection sys_mg_tools_fw_upgrade 6.1 Firmware Upgrade
 * The CV5x firmware download process differs from the CV2x firmware download process. CV2x uses the AmbaUSB tool
 * to upgrade the firmware, while CV5x can use either the AmbaUSB tool or the Android fastboot tool.
 * Refer to @ref page_getting_start_guide for more details.<br>
 * CV72 is similar to CV2x in terms of firmware upgrade, as both use the AmbaUSB tool to download the firmware.
 *
 * @subsection sys_mg_tools_linux 6.2 Toolchain for Linux
 * Use the toolchain below to compile the Linux source code.
 * @code {.c}
 * build $ source ../../build/env/amba-build.env
 * ============================================================
 * Host System: ubuntu 18.04.6 LTS (Bionic Beaver)
 * ============================================================
 * KERNEL_VER       : 5.15
 * KERNEL_PV        : 136
 * KERNEL_SRC       : /cooper_dev/ambarella/kernel/linux-5.15
 * KERNEL_OUT       : /cooper_dev/ambarella/out/amba_out/cv72_gage/objects/kernel/linux-5.15
 * AMBA_BOARD       : cv72_gage
 * AMBA_SOC_SERIES  : cv7x
 * AMBA_SOC         : cv72
 * AMBA_CPU_ARCH    : armv8-a
 * AMBA_DSP_ARCH    : v6
 * AMBA_IMG_ARCH    : cv72
 * AMBA_CAVALRY_ARCH: cavalry_v3
 * ENV_MIRROR_URL   : http://yocto.ambarella.com/mirror/cooper_1.5
 * ============================================================
 * ============================================================
 * TOOLCHAIN    PATH: /usr/local/cortex-a76-2023.04-gcc12.2-linux5.15
 * TOOLCHAIN    NANE: aarch64-linux-gnu-gcc
 * TOOLCHAIN VERSION: 12.2.1
 * ============================================================
 * ============================================================
 * ENV_BUILD_MODE   : external
 * ENV_BUILD_ARCH   : arm64
 * ENV_BUILD_TOOL   : /usr/local/cortex-a76-2023.04-gcc12.2-linux5.15/bin/aarch64-linux-gnu-
 * ENV_BUILD_JOBS   : -j8
 * ENV_TOP_DIR      : /cooper_dev/ambarella
 * ENV_MAKE_DIR     : /cooper_dev/ambarella/build/core
 * ENV_TOOL_DIR     : /cooper_dev/ambarella/build/bin
 * ENV_DOWN_DIR     : /cooper_dev/ambarella/out/mirror-cache/downloads
 * ENV_CACHE_DIR    : /cooper_dev/ambarella/out/mirror-cache/build-cache
 * ENV_TOP_OUT      : /cooper_dev/ambarella/out/amba_out/cv72_gage
 * ENV_OUT_ROOT     : /cooper_dev/ambarella/out/amba_out/cv72_gage/objects
 * ENV_INS_ROOT     : /cooper_dev/ambarella/out/amba_out/cv72_gage/sysroot
 * ENV_DEP_ROOT     : /cooper_dev/ambarella/out/amba_out/cv72_gage/sysroot
 * ENV_IMG_ROOT     : /cooper_dev/ambarella/out/amba_out/cv72_gage/images
 * ENV_CFG_ROOT     : /cooper_dev/ambarella/out/amba_out/cv72_gage/config
 * ENV_OUT_HOST     : /cooper_dev/ambarella/out/amba_out/cv72_gage/objects-native
 * ENV_INS_HOST     : /cooper_dev/ambarella/out/amba_out/cv72_gage/sysroot-native
 * ENV_DEP_HOST     : /cooper_dev/ambarella/out/amba_out/cv72_gage/sysroot-native
 * ENV_FSANITIZE_OPTION : 0 // 0:close, 1:address, 2:thread, 3:leak, 4:undefined
 * ============================================================

 * @endcode
 *
 * @subsection sys_mg_tools_cvflow_processor 6.3 Toolchain for the CVflow Processor
 * Use the toolchain below to compile the CV source code.
 * @code {.c}
 * build $ source /usr/local/amba-cv-tools-2.4.0.0.1020.ubuntu-18.04/env/cv5.env
 * Using cavalry_gen version latest
 * =================================================
 * AmbaCnnUtils Version: cv2.2.4.0.0.1020.ubu1804
 *     CnnUtils Version: cv2.2.4.0.0.1020.ubu1804
 *      Cavalry Version: version 2.2.8.2 ( HASH a38a866 )
 *          Vas Version: cv5.2.4.0.0.1020.ubu1804
 * =================================================
 * @endcode
 *
 * - - - -
 *
 * @section sys_mg_faq 7. Frequently Asked Questions (FAQ)
 * @b Question:  Is it difficult to migrate CV2x products to the Cooper chip family?
 *
 * @b Answer:  Migrating from the CV2x platform to the Cooper chip family is simple. The Cooper SDK IOCTL is
 * backwards-compatible with the CV2x IOCTL, so users who have already designed a CV2x-based single-VIN /
 * channel platform should find it easy to migrate upper-level applications from CV2x to the Cooper Linux SDK.
 * Users who have designed CV2x multi-channel products must implement minor changes to the processing
 * flow, as well as to some data structures in the Lua script, in order to access multi-channel features.
 *
 * - - - -
 *
 * @section sys_mg_license 8. License
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
 */

/*!
 * @file doc_sys_migration_guide_legacy.h
 * @brief
 * @version 1.0
 * @date 2023-4-27
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
 * @page page_sys_mg_legacy Migration Guide from CV5x Legacy SDK
 *
 * @section sys_mg_lgc_history 0. Revision History
 * <table>
 * <caption id="sys_migration_guide_rev_history"></caption>
 * <tr><th> Updated Date         <th align="left"> Modification
 * <tr><td> 20230427             <td> Initial Version
 * <tr><td rowspan="2"> 20230725 <td> 1. Updated Section @ref sys_mg_lgc_sw_api_diff
 * <tr>                          <td> 2. Updated Section @ref sys_mg_lgc_ioctl_interface_s_chan_cfg
 * <tr><td> 20230803             <td> Updated Section @ref sys_mg_lgc_sw_api_diff_multi_vin
 * <tr><td> 20231025             <td> Added Section @ref sys_mg_lgc_highlights "2. Highlights for DSP APIs"
 * <tr><td> 20240122             <td> Updated Section @ref sys_mg_lgc_highlights "2. Highlights for DSP APIs"
 * </table>
 *
 * @section sys_mg_lgc_overview 1. Overview
 *
 * This document provides users with instructions for migrating single- and multiple-video
 * input (VIN) channel designs from the CV5x legacy software development kit (SDK) to the Cooper Linux SDK.
 *
 * - - - -
 *
 * @section sys_mg_lgc_highlights 2. Highlights for DSP APIs
 *
 * This chapter describes the highlights for this SDK version, compared with the previous SDK version.
 *
 * @subsection sys_mg_lgc_highlights_1_6 2.1 Highlights for DSP APIs in SDK 1.6
 *
 * - The custom SEI API is added to insert customized SEI for AVC / HEVC / MJPEG streams, and the
 *   working flow is refined inside DSP / IAV, and the API is not fully compatible with CV2x.
 * - The ISP NN interface are added to support lite NN based motion detection in encode mode 5.
 *   The lite NN based motion detection feature is also called "True Motion".
 * - The multiple pass API is added to support up to 2 passes.  This feature is redesigned
 *   with 2 channels instead of 2 passes in the same channel.  With the new design, it is possible
 *   to generate multiple source buffers from a multi-view canvas.
 * - IDSP vertical slice related interfaces are added for IDSP veritical slicing feature.
 *   This can possibly improve the IDSP pipeline latency.
 * - RAW fps can be specified in the channel cfg. It is the fps after VIN stage, and before IDSP stage.
 *   So this fps may possibly be different from sensor fps, and IDSP fps.
 * - The blur color API is added to specify the blur color, if needed.
 * - The stream overlay API is updated to support Y blend only, or UV blend only. Default is to blend
 *   both Y and UV.
 * - The motion data API is added to support the motion data query.
 * - The encoded frame num is supported into iav_framedesc and iav_slicedesc, to report stream based
 *   frame number.
 * - The new IAV memory IAV_PART_IMG_NN is added to support for image NN buffer, which can be used for
 *   NN based image processing.
 * - The option "hevc_width_align_enable" is added in iav_stream_resource and iav_canvas_cfg to
 *   enable padding to improve HEVC encoding efficiency.
 * - The option "enc_extra_padding_enable" is added to support extra paddding for stream encoding,
 *   to eliminate the potential encoding boundary artifacts due to alignment.
 * - The overlay / blur audit is added to audit frame sync failure count.
 * - The IDSP audit is updated to support grouping frame drop count.
 *
 * @subsection sys_mg_lgc_highlights_1_5 2.2 Highlights for DSP APIs in SDK 1.5
 *
 * - IDSP channel num is increased from 8 to 16.
 * - The MJPEG encoding width is limited to be 16 aligned, and height to be 8 aligned.
 *   In preview SDK versions, both width and height are incorrectly limited to 4 aligned.
 *   The valid values are 0 ~ 2, with value 0 weakest blur effect and 2 strongest blur effect.
 * - The parameter vout_possible_map must be specified, if other than VOUT 1 may be supported.
 * - VIN ROI related interfaces are added into VIN APIs.
 * - The RAW width and height information is added into iav_chan_cfg structure, which stands for the
 *   actual output RAW size information.
 * - RAW slice related interfaces are added for RAW vertical slicing feature.
 * - Blur coefficients parameters is added to achieve different blur effects.
 * - The skip strengh is by default set to 2 for AVC / HEVC for better encoding efficiency.
 * - The AVC scalelist strength is added for better encoding efficiency. 
 * - The blending DPTZ APIs are added to support blending DPTZ runtime update for the canvas. 
 * - The IDSP encode sync API is added to support synchronization for IDSP and encoder.
 * - The image scalar audit API is added for IDSP clock audit.
 * - The encoder audit API is added for encoder clock audit.
 * - The IQ ADJ parameters has been refined with structure changes, so it is not fully compatible
 *   with previous SDK versions.
 *
 * - - - -
 *
 * @section sys_mg_lgc_sw 3. Software
 *
 * This chapter describes the migration of the software from the CV5x legacy SDK to the Cooper Linux SDK.
 *
 * @subsection sys_mg_lgc_sw_api_diff 3.1 Application Programming Interface (API) Differences
 *
 * @subsubsection sys_mg_lgc_sw_api_diff_blur_insertion 3.1.1 Blur Insertion
 * - The blur effect in the Cooper Linux SDK is improved to achive better consistency across
 *   preview buffers and create more visual effects. The maximum-supported blur strength level is
 *   extended to four, while there are only three strength levels in the legacy SDK. When mosaic-like
 *   blur is enabled, each mosaic block's size will be fixed to 8x8, 16x16, 32x32, or 64x64 pixels
 *   in the respective strength level. This presents more flexibilities for users to choose
 *   from different resolutions of preview buffers.
 * - Pyramid is still required to be enabled for blur, but pyramid layer selection is managed
 *   entirely in the SDK. It is no longer required for users to enable the pyramid layer used by blur.
 * - Channel groups are not required for blur in the Cooper Linux SDK.
 * - The new blur coefficients are supported in the Cooper Linux SDK to achieve different blur effects.
 *   The valid values are 0 ~ 2, with value 0 weakest blur effect and 2 strongest blur effect.
 * - The maximum blur number for a single stream is increased from 8 in CV5x Legacy SDK to 16 in Cooper Linux SDK.
 * - There is less dynamic random-access memory (DRAM) footprint when the blur is enabled in the Cooper Linux SDK,
 *   compared to the CV5x legacy SDK.
 *
 * @subsubsection sys_mg_lgc_sw_api_diff_multi_vin 3.1.2 Multi-VIN Stitching
 * - In the legacy SDK, each canvas's stitching is performed independently.
 *   In the Cooper Linux SDK, the stitching effect is decided by the layout of the main buffers. Stitching
 *   on sub-buffers is scaled from the main buffer and copied to sub-buffers.
 * - To skip blend stitching for a certain sub-buffer, users should set "blend_stitch_type = 0" in
 *   the structure iav_canvas_cfg in the legacy SDK; and should set "srcbuf_to_skip_blend" in the structure iav_chan_cfg
 *   in the Cooper Linux SDK.
 * - In the Cooper Linux SDK, a preview buffer is sacrificed for stitching: the fifth buffer
 *   on CV5x, and the second buffer on other chips. In other words, the fifth buffer or the second buffer cannot be placed
 *   into any canvas or used as pyramid input when stitching is enabled.
 * - In the Cooper Linux SDK, the sixth buffer cannot enable the stitch; this restriction doesn't exist in
 *   the legacy SDK.
 *
 * @subsubsection sys_mg_lgc_sw_api_diff_img_scale 3.1.3 Arbitrary Image Scaler
 * - In the legacy SDK, the arbitrary image scaler only supports NV12 and NV16 formats, and the
 *   format is decided when entering into the preview. Ambarella does not support scaling different image formats
 *   after preview.
 * - In the Cooper Linux SDK, the arbitrary image scaler supports NV12, NV16, and MONO formats.
 *   Users can send scaler jobs with mixed YUV formats after preview.
 * - In the legacy SDK, the offset and size of the image scaler all must be aligned to four.
 *   While the width and x-offset must be aligned to four in the Cooper Linux SDK, the height and y-offset
 *   must be aligned only to 2.
 *
 * @subsubsection sys_mg_lgc_sw_api_diff_seventh_buf 3.1.4 Seventh Preview Buffer
 * - The seventh preview buffer is not supported in the Cooper Linux SDK.
 *
 * @subsubsection sys_mg_lgc_sw_api_diff_eis 3.1.5 Electronic Image Stabilization
 * - In the legacy SDK, electronic image stabilization (EIS) uses the two-channel approach, and the
 *   EIS source channel can run in mode 0 or mode 5.
 * - In the Cooper Linux SDK, although EIS still uses the two-channel approach, the EIS source channel
 *   should run in mode 8. This saves system resources, as the first EIS channel is only used
 *   to generate 3A (auto exposure (AE) / auto white balance (AWB) / auto focus (AF)) statistics data.
 *
 * @subsubsection sys_mg_lgc_sw_api_diff_overlay 3.1.6 Overlay
 * - The total overlay number of all streams cannot exceed 64 in the Cooper Linux SDK.
 *
 * @subsubsection sys_mg_lgc_sw_api_diff_vout 3.1.7 VOUT
 * - With Cooper Linux SDK, the VOUT possible map parameter vout_possible_map must be specified when booting DSP,
 *   if there is potential requirement to use VOUT 0, 2, or multiple VOUT devices. If there is only potential
 *   VOUT 1 is needed, then there is no need to configure this.
 *
 * - - - -
 *
 * @section sys_mg_lgc_ioctl_interface 4. Input / Output Control (IOCTL) Interface
 *
 * The legacy SDK and the Cooper Linux SDK share the same API files, so they include identical IOCTLs
 * and structures. Only some structure members may not be required in the Cooper Linux SDK,
 * or they may be used for a different purpose.
 *
 * This chapter describes software migration and provides IOCTL differences between the
 * legacy SDK and the Cooper Linux SDK.
 * The IOCTLs are as follows:
 * - @ref sys_mg_lgc_ioctl_interface_s_chan_cfg "3.1 IAV_IOC_SET_CHAN_CONFIG"
 * - @ref sys_mg_lgc_ioctl_interface_g_chan_cfg "3.2 IAV_IOC_GET_CHAN_CONFIG"
 * - @ref sys_mg_lgc_ioctl_interface_s_system_resource "3.3 IAV_IOC_SET_SYSTEM_RESOURCE"
 * - @ref sys_mg_lgc_ioctl_interface_g_system_resource "3.4 IAV_IOC_GET_SYSTEM_RESOURCE"
 *
 * @subsection sys_mg_lgc_ioctl_interface_s_chan_cfg 4.1 IAV_IOC_SET_CHAN_CONFIG
 * The structure parameter changes are listed below:
 * <table>
 * <caption>Table 3-1. iav_chan_cfg Structure Definition.</caption>
 * <tr><th>Parameter                 <th>Used in legacy  <th>Used in Cooper
 * <tr><td>"vsrc_ctx_pattern"        <td>✓               <td>Not implemented
 * <tr><td>"vsrc_ctx_pattern_mask"   <td>✓               <td>Not implemented
 * <tr><td>"slice_cfg_enable"        <td>✓               <td>-
 * <tr><td>"slice_num"               <td>✓               <td>-
 * <tr><td>"warp_padding_width"      <td>✓               <td>✓<br>For rotation pipeline only
 * <tr><td>"slice_width"             <td>✓               <td>-
 * <tr><td>"c2y_slice_num"           <td>✓               <td>-
 * <tr><td>"high_perf_enable"        <td>-                <td>-
 * <tr><td>"srcbuf_to_skip_blend"    <td>-                <td>✓
 * </table>
 *
 * @subsection sys_mg_lgc_ioctl_interface_g_chan_cfg 4.2 IAV_IOC_GET_CHAN_CONFIG
 * Refer to the structure parameter change from IOCTL @b IAV_IOC_SET_CHAN_CONFIG.
 *
 * @subsection sys_mg_lgc_ioctl_interface_s_system_resource 4.3 IAV_IOC_SET_SYSTEM_RESOURCE
 * Because the image format of arbitrary image scaler is not required to be specified at preview,
 * the "format" member in the structure iav_img_scale_cfg will not be used in the Cooper Linux SDK.
 * The following lists the changes in the structure parameter iav_img_scale_cfg
 * for the IOCTL @b IAV_IOC_SET_SYSTEM_RESOURCE.
 * <table>
 * <caption>Table 3-2. iav_img_scale_cfg Structure Definition.</caption>
 * <tr><th>Parameter     <th>Used in legacy  <th>Used in Cooper
 * <tr><td>"format"      <td>✓               <td>-
 * </table>
 *
 * @subsection sys_mg_lgc_ioctl_interface_g_system_resource 4.4 IAV_IOC_GET_SYSTEM_RESOURCE
 * Refer to the structure parameter change from IOCTL @b IAV_IOC_SET_SYSTEM_RESOURCE.
 *
 * - - - -
 *
 * @section sys_mg_lgc_tools 5. Tools
 * CV5x legacy SDK and the Cooper Linux SDK use the same toolchain.
 *
 * - - - -
 *
 * @section sys_mg_lgc_faq 6. Frequently Asked Questions (FAQ)
 * @b Question:  Is it difficult to migrate from the legacy SDK to the Cooper Linux SDK?
 *
 * @b Answer:  Migrating from the CV5x legacy SDK to the Cooper Linux SDK is simple, as they share
 * the same API header files. Only a few changes are required for migration.
 *
 * - - - -
 *
 * @section sys_mg_lgc_license 7. License
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
 */
/*!
 * @file doc_sys_amboot.h
 * @brief
 * @version 1.0
 * @date 2020-11-17
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
 * @page page_sysdoc_amboot_doc BASE - AMBoot
 *
 * @section amboot_doc_history 0. Revision History
 *  | Library Version  | Updated Date   | Modification         |
 *  | :---             | :------------- |:-------------------- |
 *  | 1.0.0            | 20201117       | Initial draft        |
 *
 *
 * - - - -
 * @section amboot_doc_intro 1. AMBoot Documents Introduction
 *
 * There's a folder in SDK that contains AMBoot documents, which can help users to better
 * understand related topic. They are located in `SDK/ambarella/amboot/doc`.
 *     -# <a href="txt/amrtos.txt" target="_blank"><b>amrtos.txt</b></a>
 *     -# <a href="txt/boot_command.txt" target="_blank"><b>boot_command.txt</b></a>
 *     -# <a href="txt/bstiniparser.txt" target="_blank"><b>bstiniparser.txt</b></a>
 *     -# <a href="txt/dram_shmoo.txt" target="_blank"><b>dram_shmoo.txt</b></a>
 *     -# <a href="txt/env.txt" target="_blank"><b>env.txt</b></a>
 *     -# <a href="txt/flexible_firmware.txt" target="_blank"><b>flexible_firmware.txt</b></a>
 *     -# <a href="txt/lfat.txt" target="_blank"><b>lfat.txt</b></a>
 *     -# <a href="txt/mem_layout.txt" target="_blank"><b>mem_layout.txt</b></a>
 *     -# <a href="txt/multi_bstini.txt" target="_blank"><b>multi_bstini.txt</b></a>
 *     -# <a href="txt/ptb_backup.txt" target="_blank"><b>ptb_backup.txt</b></a>
 *     -# <a href="txt/recovery.txt" target="_blank"><b>recovery.txt</b></a>
 *     -# <a href="txt/sdmmc.txt" target="_blank"><b>sdmmc.txt</b></a>
 *     -# <a href="txt/secure_boot.txt" target="_blank"><b>secure_boot.txt</b></a>
 *     -# <a href="txt/stack_boot.txt" target="_blank"><b>stack_boot.txt</b></a>
 *
 *
 * @subsection amboot_mem 1.1 BST & Memory Documents
 * Below are some documents regarding different aspects of BST and system memory.
 *
 * <a href="txt/bstiniparser.txt" target="_blank"><b>Bstiniparser.txt</b></a> introduces parameters
 * needed in BST, dram parameters are important part of this document. If dram shmoo tool is needed,
 * it is highly recommended to read this document before.
 *
 * <a href="txt/dram_shmoo.txt" target="_blank"><b>Dram_shmoo.txt</b></a> introduces the usage of the
 * tools to tune dram parameters in order to get a better and more stable dram performance. There are 2
 * tools acting for different roles: <b>dram_preliminary_shmoo</b> would give a parameters combination when
 * system loading is relative low. <b>dram_advanced_shmoo</b> is trying to found a better parameters combination
 * when system is in heavy loading status.
 *
 * For some cases, one BST needs to support several sets of boot parameters so that a single BST can run on
 * several different boards.<br>
 * <a href="txt/multi_bstini.txt" target="_blank"><b>Multi_bstini.txt</b></a> introduces how to configure
 * single BST with multiple ini files.
 *
 *
 * @subsection amboot_amrtos 1.2 Amrtos Documents
 * AMRTOS is a lite OS in Amboot. It supports mutiple threads, mutiple cores, spin lock, mutex,
 * semaphore and event mechanism.<br>
 * <a href="txt/amrtos.txt" target="_blank"><b>Amrtos.txt</b></a> describes some details about AMRTOS. It is
 * helpful for developer to program some software on it.
 *
 *
 * @subsection amboot_secure 1.3 Security Documents
 * The Secure Boot is to authenticate the image of each booting stage, include BST, BL2, BL31, BL32(Optee)
 * and BL33(Amboot).
 *
 * The system with security feature is ususally divided into secure world and non-secure world.
 * The Secure Device is protected from access by non-secure world.
 * That is, once a device is configured as a secure device, kernel and application, which are in non-secure world,
 * cannot directly access the registers belong to this secure device.
 *
 * <a href="txt/secure_boot.txt" target="_blank"><b>Secure_boot.txt</b></a> introduces secure boot and secure devices.
 *
 * <a href="txt/mem_layout.txt" target="_blank"><b>Mem_layout.txt</b></a> introduces memory layout with different
 * arm_tf componets combinations:<br>
 *    Amboot <br>
 *    BL2 + BL31 + BL33(Amboot) <br>
 *    BL2 + BL31 + BL33(Amboot) + Image Signature <br>
 *    BL2 + BL31 + BL33(Amboot) + Image Signature + DTB Signature <br>
 *    BL2 + BL31 + BL32 + BL33(Amboot) + Image Signature + DTB Signature <br>
 *
 * For more details regarding security, uses can refer to <em>Ambarella Flexible Linux SDK Security</em> Documents.
 *
 * @subsection amboot_fs 1.4 Storage & File System Documents
 * EVK boards usually set nand flash as default storage for binaries, but our system support eMMC as boot media.
 * Spinor flash together with eMMC is also supported, which is callled stack mode.<br>
 * <a href="txt/sdmmc.txt" target="_blank"><b>Sdmmc.txt</b></a> introduces eMMC, SD card and SDIO controller.<br>
 * <a href="txt/stack_boot.txt" target="_blank"><b>Stack_boot.txt</b></a>
 * introduces how to use this kind of storage solution.
 *
 * Besides those partitions which save the system image,like BST, BLD, LNX, etc, there are some partitions acting
 * different roles which can be chosen according to usage.<br>
 *     - BAK partition is used for system recovery.
 *     - PTB partition is used to save PTB and second/backup PTB.
 *     - ENV partition is used to store environment variables used by Amboot. ENV partition need to work with flexible
 * firmware layout.
 *
 * <a href="txt/recovery.txt" target="_blank"><b>Recovery.txt</b></a> introduces the recovery flow of SDK and usage of BAK
 * partition.<br>
 * <a href="txt/ptb_backup.txt" target="_blank"><b>Ptb_backup.txt</b></a> introdcues the ptb backup mechanism in PTB partition.<br>
 * <a href="txt/env.txt" target="_blank"><b>Env.txt</b></a> introduces environment partition which is uesd to store environment
 * variables used by Amboot.<br>
 *
 * Traditional firmware layout consists of fixed partition combinations. It is not allowed to change or add partition.
 * Flexible firmware is introduced to bring more flexibility into firmware layouts.<br>
 * <a href="txt/flexible_firmware.txt" target="_blank"><b>Flexible_firmware.txt</b></a> introduces this solution.<br>
 *
 * LFAT means lightweight FAT file system. It is used as a read-only file system in Ambarella practice.<br>
 * <a href="txt/lfat.txt" target="_blank"><b>Lfat.txt</b></a> introduces usage of Lightweight FAT file system.
 *
 *
 * - - - -
 * @section amboot_doc_license 2. License
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
 */

/*!
 * @file doc_sys_kernel.h
 * @brief
 * @version 1.0
 * @date 2020-11-23
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
 * @page page_sysdoc_kernel_doc BASE - Kernel
 *
 * @note Ambarella's kernel documentation has been integrated into the kernel's Sphinx documentation system. Please check it out [here](xxx/arm/ambarella/index.html)
 *
 * Here is a brief summary:
 *
 * - - - -
 *
 * @subsection kernel_doc_adc 1.1 Adc
 * An analog-to-digital converter (abbreviated ADC) is a device that uses sampling to
 * convert a continuous quantity to a discrete time representation in digital form. Ambarella Socs
 * have on-chip ADCs. Ambarella ADC supports "on-shot" mode and "continuous" mode. The sampling rate
 * is determined by gclk_adc, the number of used channels and clock cycles for one sampling.
 * The formula of ADC is D = V * (2^12 - 1) / R, here D is digital value, V is input voltage,
 * R is the range, i.e., 1.8v or 3.3v.<br>
 *
 *
 * @subsection kernel_doc_ir 1.2 Ir
 * Ambarella Soc has an internal Infrared RC (Remote Control) module, which owns a dedicated PIN
 * for it. This IR module consists of a 16-bit counter, driven at a rate of gclk_ir which is
 * derived from OSC. Once the IR module is enabled, the counter will start to count.
 *
 * @subsection kernel_doc_mem 1.3 Memory_hotplug
 *
 * @subsection kernel_doc_nist 1.4 Nisttest
 * NIST Statistical Test Suite is used to verify if a bit stream is random enough. There are 15
 * tests in NIST SP-800-22 test suite.<br>
 * RNG stands for Random Number Generator, and the output is used for ‘encryption key’ generation.
 * The linux driver provides /dev/hwrng character device through hw_random framework.To check if
 * RNG output is random enough, this page provides the information about how to verify the randomness.
 * It contains randomness verification, number generation and test result on different platform.
 *
 * @subsection kernel_doc_ptp 1.5 Ptp
 * PTP stands for precise time protocol. IEEE 1588 PTP is supported on CV2x and later chips. `linuxptp`
 * is a recommended tool to test and configure the ptp on linux.<br>
 *
 * @subsection kernel_doc_sr 1.6 Self-refresh
 * Linux kernel support up to 4 system sleep states generically:
 * | mode    | explain                                       |
 * | ------- | --------------------------------------------- |
 * | freeze  | Suspend-To-Idle / ACPI S0                     |
 * | standby | Standby / Power-On Suspend / ACPI S1          |
 * | mem     | Suspend-To-RAM / Self-Refresh / STR / ACPI S3 |
 * | disk    | Suspend-To-Disk / STD / ACPI S4               |
 *
 * Mem, i.e., Self-Refresh means system powers off all the hardwares except for DRAM and PWC, which
 * would save the power and also bring up the system quickly when waken up.
 * Internal or external power control is essential in self-refresh. Arm_tf is also needed for this
 * feature.
 *
 * @subsection kernel_doc_dts Ambarella.txt
 * Device Tree is essentially a data structure in byte code format which contains information that is
 * helpful to the kernel when booting up. The boot loader copies that chunk of data into a known address
 * in the RAM before jumping to the kernel's entry point.<br>
 * <a href="txt/ambarella.txt" target="_blank"><b>Ambarella.txt</b></a> introduces how to configure
 * Ambarella Platforms Device-Tree.
 *
 * @note
 * <ul>
 * <li> When secure boot is enabled, many registers including peripherals like GPIO will ONLY be
 * accessible in secure world by default. Refer to "Section - Secure Monitor node" for how to configure
 * the device node of secure monitor to make GPIO accessible in non-secure world. Users need to take
 * care of this especially when trying to operate on GPIOs at BLD stage.
 * </ul>
 *
 * - - - -
 *
 * @section kernel_doc_license 2. License
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
 */
/*!
 * @file doc_sys_rootfs.h
 * @brief
 * @version 1.0
 * @date 2024-01-16
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
 * @page page_sysdoc_rootfs_doc BASE - Rootfs
 *
 * @section rootfs_doc_history 0. Revision History
 *  | Version  | Updated Date   | Modification         |
 *  | :---     | :------------- |:-------------------- |
 *  | 1.0.0    | 20240116       | Initial Version        |
 *
 *
 * - - - -
 * @section si_rootfs_doc_intro 1. Rootfs Introduction
 *
 * The Ambarella software development kit (SDK) can support various root file systems (rootfs) types. The following table lists
 * the rootfs types supported by different SDK builds. The user can
 * choose the right one according to the actual needs.
 * <table>
 * <caption id="si_rootfs_table">Table 1-1. Supported Rootfs Types.</caption>
 * <tr>
 * <th rowspan="2" align="center">Rootfs Type</th>
 * <th colspan="2" align="center">Cooper SDK</th>
 * <th colspan="1" align="center">CV2x SDK 3.0</th>
 * <th rowspan="2" align="center">Description</th>
 * </tr>
 * <tr>
 * <th align="center">Amba Build</th>
 * <th align="center">Yocto Build</th>
 * <th align="center">Amba Build</th>
 * </tr>
 * <tr>
 * <th align="center">UBIFS</th>
 * <td align="center">✔</td><td align="center">✔</td><td align="center">✔</td>
 * <td>Unsorted block image file system (UBIFS)</td>
 * </tr>
 * <tr>
 * <th align="center">SQUASHFS</th>
 * <td align="center">✔</td><td align="center">✔</td><td align="center">✔</td>
 * <td>A compressed read-only file system</td>
 * </tr>
 * <tr>
 * <th align="center">JFFS2</th>
 * <td align="center">✔</td><td align="center">✔</td><td align="center">✔</td>
 * <td>Journaling flash file system version 2</td>
 * </tr>
 * <tr>
 * <th align="center">YAFFS</th>
 * <td align="center">✘</td><td align="center">✘</td><td align="center">✔</td>
 * <td>Yet another flash file system</td>
 * </tr>
 * <tr>
 * <th align="center">EXT2</th>
 * <td align="center">✘</td><td align="center">✔</td><td align="center">✔</td>
 * <td>Second extended file system</td>
 * </tr>
 * <tr>
 * <th align="center">EXT3</th>
 * <td align="center">✘</td><td align="center">✔</td><td align="center">✔</td>
 * <td>Third extended file system</td>
 * </tr>
 * <tr>
 * <th align="center">EXT4</th>
 * <td align="center">✔</td><td align="center">✔</td><td align="center">✔</td>
 * <td>Fourth extended file system</td>
 * </tr>
 * <tr>
 * <th align="center">RAMDISK</th>
 * <td align="center">✔</td><td align="center">✘</td><td align="center">✔</td>
 * <td>RAM file system generated based on EXT2</td>
 * </tr>
 * <tr>
 * <th align="center">CPIO</th>
 * <td align="center">✘</td><td align="center">✘</td><td align="center">✔</td>
 * <td>RAM file system generated by CPIO utility</td>
 * </tr>
 * <tr>
 * <td colspan="5" align="center">✔: Supported       ✘: Not supported yet</td>
 * </tr>
 * </table>
 *
 *
 * - - - -
 *
 * @section si_rootfs_build 2. Rootfs Guidance
 * This chapter contains the following sections. If other rootfs types are used,
 * the procedures are similar.
 * - Section @ref si_ubifs_guide
 * - Section @ref si_ramdisk_guide
 *
 * @subsection si_ubifs_guide 2.1 UBIFS Guidance
 * UBIFS is a filesystem that works on top of unsorted block images (UBI) volumes which make it have the
 * following features relative to other flash filesystems:
 * - UBI / UBIFS scales to large flash sizes better than JFFS2
 * - Good fault tolerance, via a number of features
 * - Built-in on-the-fly compression
 * - Good runtime performance<br>
 *
 * For legacy firmware layout, the user can enable the UBIFS by performing the
 * following steps (Take CV22_walnut as an example):
 * 1. Allocate the "rootfs" partition size.
 *   @code {.c}
 *   build$ vim ambarella/boards/cv22_walnut/bsp/bsp.h
 *   ...
 *   #define AMBOOT_LNX_SIZE     (192  * 1024 * 1024)
 *   ...
 *   @endcode
 *
 * 2. Modify the `bootargs` in device trees (DTS) file for mounting the UBIFS.
 *   @code
 *   build$ vim ambarella/boards/cv22_walnut/bsp/cv22_walnut.dts
 *   bootargs = "console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs";
 *   @endcode
 *   The user can also set the bootargs in menuconfig which will replace the one
 *   set in DTS file.
 *   - For CV2x SDK 3.0 Amba Build:
 *   @code {.c}
 *   build$ make cv22_ipcam_config
 *   build$ make menuconfig
 *   Ambarella Bootloader Configuration  --->
 *     AMBoot Options  --->
 *       Common Boot Options  --->
 *         (console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline
 *   @endcode
 *   - For Cooper SDK Amba Build:
 *   @code {.c}
 *   build$ make ipcam_config
 *   build$ make menuconfig
 *   boot  --->
 *     [*] amboot (boot/ambamk)  --->
 *       Ambarella Bootloader Configuration  --->
 *         AMBoot Options  --->
 *           Common Boot Options  --->
 *             (console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline
 *   @endcode
 *   - For Cooper SDK Yocto Build:
 *   @code {.c}
 *   build$ make ipcam_config
 *   build$ make menuconfig
 *   meta-ambabsp  --->
 *     recipes-bsp  --->
 *       [*] amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *         Ambarella Bootloader Configuration  --->
 *           AMBoot Options  --->
 *             Common Boot Options  --->
 *               (console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline
 *   @endcode
 *
 * 3. Select the UBIFS in menuconfig.
 *   - For CV2x SDK 3.0 Amba Build:
 *   @code {.c}
 *   build$ make menuconfig
 *   Ambarella Bootloader Configuration  --->
 *      Firmware Options  --->
 *        Linux Partition  --->
 *          ($(AMB_BOARD_OUT)/rootfs/ubifs) Linux FS image
 *          ($(AMB_TOPDIR)/amboot/vif/ubifs.info) Linux FS Version File
 *   [*] Ambarella File System Configuration  --->
 *     Linux Root File System (UBIFS)  --->
 *       (X) UBIFS
 *   @endcode
 *   - For Cooper SDK Amba Build:
 *   @code {.c}
 *   build$ make menuconfig
 *     boot  --->
 *       [ ] ambfw (boot/ambamk)  ----
 *       [*] amboot (boot/ambamk)  --->
 *         Ambarella Bootloader Configuration  --->
 *           Firmware Options  --->
 *             Firmware Layout Style (Legacy Firmware Layout)  --->
 *               (X) Legacy Firmware Layout
 *             Linux Partition  --->
 *               ($(ENV_IMG_ROOT)/rootfs.bin) Linux FS image
 *               ($(AMBOOT_TOPDIR)/vif/ubifs.info) Linux FS Version File
 *     rootfs  --->
 *       [*]   rootfs (rootfs/system)  --->
 *         Linux Root File System (UBIFS)  --->
 *           (X) UBIFS
 *   @endcode
 *   - For Cooper SDK Yocto Build:
 *   @code {.c}
 *   build$ make menuconfig
 *   meta-ambabsp  --->
 *     recipes-bsp  --->
 *       [ ] ambfw (meta-ambabsp/recipes-bsp/boot)  ---
 *       [*] amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *         Ambarella Bootloader Configuration  --->
 *           Firmware Options  --->
 *             Firmware Layout Style (Legacy Firmware Layout)  --->
 *               (X) Legacy Firmware Layout
 *             ROMFS Partition  --->
 *               ($(ENV_IMG_ROOT)/rootfs.bin)  Romfs image
 *               ($(AMBOOT_TOPDIR)/vif/ubifs.info) ROMFS Version File
 *       [*] amrootfs (meta-ambabsp/recipes-bsp/amrootfs)  --->
 *         Linux Root File System (UBIFS)  --->
 *           (X) UBIFS
 *   @endcode
 *
 * 4. Add UBIFS and memory technology device (MTD) block device support in the kernel.<br>
 *   @code {.c}
 *   build$ make menuconfig_public_linux  // for CV2x SDK 3.0 Amba build
 *   or
 *   build$ make linux_menuconfig         // for Cooper SDK
 *   Device Drivers  --->
 *     <*> Memory Technology Device (MTD) support  --->
 *       <*>   Enable UBI - Unsorted block images  --->
 *         (4096) UBI wear-leveling threshold
 *         (20)  Maximum expected bad eraseblock count per 1024 eraseblocks
 *   File systems  --->
 *     [*] Miscellaneous filesystems  --->
 *       <*>   UBIFS file system support
 *       [*]     Advanced compression options
 *       [*]       LZO compression support
 *       [*]       ZLIB compression support
 *       [*]       ZSTD compression support
 *       [*]     UBIFS XATTR support
 *       [*]       UBIFS Security Labels
 *   @endcode
 *
 * 5. Build the firmware.
 *   - For CV2x SDK 3.0:
 *   @code {.c}
 *   build $ make -j8
 *   @endcode
 *   The generated firmware: `ambarella/out/<board_name>/images/bst_bld_kernel_lnx_release.elf`
 *   - For Cooper SDK:
 *   @code {.c}
 *   build $ make
 *   @endcode
 *   The generated firmware: `ambarella/out/<amba|yocto>_out/<board_name>/firmware/bst_bld_kernel_lnx_release.elf`
 *
 * @subsection si_ramdisk_guide 2.2 RAMDisk Guidance
 * RAMDisk file system is a virtual storage location created out of the system
 * memory. All read and write requests to RAMdisk file system are processed in
 * memory, resulting in a huge improvement in overall performance with
 * ultra-fast speed and ultra-low latency.<br>
 *
 * For flexible firmware layout, the user can enable the RAMDisk by performing the
 * following steps (using CV72_gage as an example):
 * 1. Allocate the "ramdisk" partition size.
 * @code {.c}
 * #define AMBOOT_PARTITION_LAYOUT \
 *         MEDIA_DEV \
 *         "128k(bst),1024k(bld),896k(dtb),896k(env),128k(cfg)," \
 *         "32m@0x1300000(kernel),192m(ramdisk),-(raw)"
 * @endcode
 *
 * 2. Select the RAMDisk file system and configure it.
 * @code {.c}
 * build $ make menuconfig
 *   rootfs --->
 *     rootfs (rootfs/system) --->
 *       Linux Root File System (Ramdisk) --->
 *         (X) Ramdisk
 *       [*]   Compress RAM disk              // Compress the RAM disk to save size
 *       (204800) Ambarella RootFS Size (KB)  // 204800 (200M) relates to RAMDisk size if not compressed
 *       (3500) Ambarella RootFS inodes number
 * @endcode
 *
 * 3. Modify the `bootargs` and configure the initial ramdisk start address.<br>
 *   - Use menuconfig to set the initrd start address.
 *   @code {.c}
 *   build $ make menuconfig
 *     boot  --->
 *       [*] amboot (boot/ambamk)  --->
 *         Ambarella Bootloader Configuration  --->
 *           Memory Options  --->
 *             (0x10000000) Initrd start address
 *   @endcode
 *   - Modify the bootargs in `ambarella/boards/<board_name>/bsp/<board_name>.dts`
 *   @code {.c}
 *   bootargs = "console=ttyS0 initrd=0x10000000,200M root=/dev/ram rw rootfs=ramfs earlycon pci=nomsi";
 *   @endcode
 *   @note
 *     The "Kernel start address" and the "Initrd start address" must be set
 *     properly in case the kernel image overlaps with the rootfs image, which
 *     could cause the kernel to fail to boot.
 *
 * 4. Add RAMDisk to the firmware.
 *   - Create a `ambarella/boards/<board_name>/bsp/profile.ramdisk` for firmware layout.
 *   @code {.c}
 *   IMAGE_FWPROG    := $(BIN_DIR)/fwp.bin
 *
 *   IMAGE_0_NAME    := bst
 *   IMAGE_0_FILE    := $(BIN_DIR)/bst.bin
 *   IMAGE_0_ADDR    := -1
 *   IMAGE_0_FLAG    := force raw
 *
 *   IMAGE_1_NAME    := bld
 *   IMAGE_1_FILE    := $(BIN_DIR)/bld.bin
 *   IMAGE_1_ADDR    := -1
 *   IMAGE_1_FLAG    := force raw
 *
 *   IMAGE_2_NAME    := env
 *   IMAGE_2_FILE    := $(BIN_DIR)/env.bin
 *   IMAGE_2_ADDR    := -1
 *   IMAGE_2_FLAG    := force
 *
 *   IMAGE_3_NAME    := dtb
 *   IMAGE_3_FILE    := $(BIN_DIR)/dtb.bin
 *   IMAGE_3_ADDR    := -1
 *   IMAGE_3_FLAG    := force
 *
 *   IMAGE_4_NAME    := kernel
 *   IMAGE_4_FILE    := $(BIN_DIR)/kernel.bin
 *   IMAGE_4_ADDR    := $(KERNEL_RAM_START)
 *   IMAGE_4_FLAG    := verify compressed
 *
 *   IMAGE_5_NAME    := ramdisk
 *   IMAGE_5_FILE    := $(BIN_DIR)/rootfs.bin
 *   IMAGE_5_ADDR    := $(CONFIG_INITRD_PHYS)
 *   IMAGE_5_FLAG    := verify
 *   @endcode
 *   @note
 *     The "IMAGE_5_FLAG" for `ramdisk` must not be set to "raw". Because before
 *     the ramdisk image is loaded into the dynamic random access memory (DRAM), the bootloader will first
 *     check the ramdisk image's header which is excluded in the raw image.
 *
 *   - Create a DTS file `ambarella/boards/<board_name>/bsp/<board_name>.env` for firmware layout.
 *   @code {.c}
 *   /dts-v1/;
 *
 *   #include "config.h"
 *
 *   / {
 *       compatible = "ambarella,environment";
 *       #address-cells = <1>;
 *       #size-cells = <1>;
 *
 *   #if defined(AMBOOT_DEV_AUTO_BOOT)
 *       auto_boot;
 *   #endif
 *       serial_num = AMBOOT_DEFAULT_SN;
 *
 *       bootcmd = "";
 *
 *       bootargs = "";
 *
 *       kernel_meta {
 *           partition = "kernel";
 *           binary_id = <0>;
 *       };
 *
 *       dtb_meta {
 *           partition = "dtb";
 *           binary_id = <0>;
 *       };
 *
 *       ramdisk_meta {
 *           partition = "ramdisk";
 *           binary_id = <0>;
 *       };
 *
 *       netdev_eth0 {
 *           mac = "00:00:00:00:00:00";
 *           mask = "0.0.0.0";
 *           gw = "0.0.0.0";
 *           ip = "0.0.0.0";
 *       };
 *
 *       tftpd {
 *           server,ip = "0.0.0.0";
 *           kernel,file = "";
 *           kernel,addr = <0x00000000>;
 *           ramdisk,file = "";
 *           ramdisk,addr = <0x00000000>;
 *       };
 *   };
 *   @endcode
 *   - Enable the profile in menuconfig.
 *   @code {.c}
 *   build $ make menuconfig
 *   boot  --->
 *     [*] ambfw (boot/ambamk)  --->
 *       AMBFW Configuration  --->
 *         [*] Build AMBFW
 *         (profile.ramdisk) Firmware Profile
 *     [*] amboot (boot/ambamk)  --->
 *       Ambarella Bootloader Configuration  --->
 *         Firmware Options  --->
 *           Firmware Layout Style (Flexible Firmware Layout)  --->
 *             (X) Flexible Firmware Layout
 *   @endcode
 *
 * 5. Enable RAMDisk and RAM block device support in the kernel.
 * @code {.c}
 * build $ make linux_menuconfig
 *     General set up --->
 *       [*] Initial RAM filesystem and RAM disk (initramfs/initrd) support
 *     File system --->
 *       <*> Second extended fs support
 *     Device Drivers --->
 *       [*] Block devices --->
 *          <*> RAM block device support
 *          (204800) Default RAM disk size (kbytes)  // 204800 (200M) relates to RAMDisk size
 * @endcode
 * @note
 *   During the ramdisk booting stage, if there are some errors related to
 *   the "incomplete write (xxx != xxx)", the user can enlarge the ramdisk size
 *   by adding "ramdisk_size=0x8000000" to bootargs or enlarging the RAM disk
 *   size in kernel, and then have a try.
 *
 * 6. Build and burn the firmware.
 * @code {.c}
 * build $ make
 * @endcode
 * The generated firmware: `ambarella/out/amba_out/<board_name>/firmware/bst_bld_env_dtb_kernel_ramdisk.elf`
 *
 *
 * - - - -
 * @section si_rootfs_doc_license 3. License
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
 */

/*!
 * @file doc_sysdoc_cm3.h
 * @brief
 * @version 1.0
 * @date 2023-11-15
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
 * @page page_sysdoc_cm3_doc BASE - CM3
 *
 * @section cm3_history 0. Revision History
 *
 * <table>
 * <caption id="cm3_history_table"></caption>
 * <tr><th> Updated Date         <th> Modification
 * <tr><td> 20231115             <td> Initial Version
 * <tr><td> 20231226             <td> Updated Section @ref cm3_driver_rpmsg_board_config
 * </table>
 *
 * - - - -
 * @section cm3_overview 1. Overview
 *
 * The Cortex-M3 (CM3) processor is specifically developed for high-performance and
 * low-cost platforms. This document provides an introduction on CM3 implementation.
 *
 * - - - -
 * @section cm3_freertos 2. FreeRTOS
 *
 * CM3 runs on `FreeRTOS 202210 LTS`.
 * Users can download it from `https://github.com/FreeRTOS/FreeRTOS-LTS/tree/202210-LTS`.
 *
 * - - - -
 * @section cm3_configuration 3. Configuration
 *
 * CM3 codes are located in `SDK/ambarella/boot/cm3` and `SDK/ambarella/boards/${board_name}/bsp/bsp_cm3.c`.
 *
 * @code {.c}
 * build $ tree -L 1 ambarella/boot/cm3
 * ambarella/boot/cm3
 * ├── AmbaConfig
 * ├── cv3ad685
 * ├── cv72
 * ├── doc
 * ├── FreeRTOS
 * ├── include
 * ├── license
 * ├── Makefile
 * ├── rpmsg-lite-master
 * └── source
 * @endcode
 *
 * @subsection cm3_toolchain 3.1 Toolchain
 *
 * The toolchain `gcc-arm-none-eabi-10.3-2021.10` is used to build CM3.
 * Users can download it from `https://developer.arm.com/downloads/-/gnu-rm`.
 *
 * @code {.c}
 * build $ sudo tar -C /usr/local -xjvf gcc-arm-none-eabi-10.3-2021.10-x86_64-linux.tar.bz2
 * @endcode
 *
 * @subsection cm3_board_config 3.2 Board Configuration
 *
 * @code {.c}
 * build $ make menuconfig
 *     boot  --->
 *         [*] cm3 (boot/ambamk)  --->
 *             Cortex-M3 Configuration  --->
 *                 [*] BOOT Cortex-M3
 *                 (1) Cortex-M3 Log Console
 * @endcode
 *
 * The CM3 firmware is included in AMBoot.
 *
 * - - - -
 * @section cm3_driver 4. Driver
 *
 * @subsection cm3_driver_rpmsg 4.1 Remote Processor Messaging Framework
 *
 * There are several remote processor messaging (RPMsg) frameworks available.
 * Currently, only RPMsg-Lite is ported.
 * Users can download it from `https://github.com/nxp-mcuxpresso/rpmsg-lite`.
 *
 * The remote processor (RPROC) framework manages the resources required by the RPMsg framework.
 *
 * @subsubsection cm3_driver_rpmsg_board_config 4.1.1 Board Configuration
 *
 * -# Boot option
 *
 *     If `Boot with TrustZone` is selected, secure boot should be enabled and power-on configuration (POC) pin 6 should be pulled up.
 *
 *     @code {.c}
 *     build $ make menuconfig
 *         boot  --->
 *             [*] amboot (boot/ambamk)  --->
 *                 Ambarella Bootloader Configuration  --->
 *                     AMBoot Options  --->
 *                         [*] Boot with TrustZone  --->
 *                             [*]   Secure Boot with Signature
 *                             [*]   Secure DTB with Signature (SOC Firmware Config)
 *     @endcode
 *
 * -# Shared memory
 *
 *     @code {.c}
 *     build $ make menuconfig
 *         boot  --->
 *             [*] cm3 (boot/ambamk)  --->
 *                 Drivers  --->
 *                     [*] RPMsg Driver  --->
 *                         (0x60000000) Cortex-M3 Shared Memory Address
 *                         (0xC0000000) Cortex-M3 Shared Memory Remap Address
 *                         (0x100000) Cortex-M3 Shared Memory Remap Size
 *     @endcode
 *
 * @subsubsection cm3_driver_rpmsg_kernel_config 4.1.2 Kernel Configuration
 *
 * @code {.c}
 * build $ make linux_menuconfig
 *     Device Drivers  --->
 *         Remoteproc drivers  --->
 *             [*] Support for Remote Processor subsystem
 *             <M>   Ambarella remoteproc support
 *         Rpmsg drivers  --->
 *             <M> RPMSG device interface
 *             -*- RPMSG name service announcement
 *             <*> Virtio RPMSG bus driver
 * @endcode
 *
 * @subsubsection cm3_driver_rpmsg_device_tree 4.1.3 Device Tree
 *
 * @code {.c}
 * #define VDEV0_VRING0_ADDRESS        (CONFIG_CORTEX_M3_REMAP_ADDRESS)
 * #define VDEV0_VRING0_SIZE           (0x8000)
 * #define VDEV0_VRING1_ADDRESS        (VDEV0_VRING0_ADDRESS + VDEV0_VRING0_SIZE)
 * #define VDEV0_VRING1_SIZE           (0x8000)
 * #define VDEV0_BUFFER_ADDRESS        (VDEV0_VRING1_ADDRESS + VDEV0_VRING1_SIZE)
 * #define VDEV0_BUFFER_SIZE           (0x10000)
 * #define VDEV0_RSC_TABLE_SIZE        (0x1000)
 * #define VDEV0_RSC_TABLE_ADDRESS     (CONFIG_CORTEX_M3_REMAP_ADDRESS + \
 *                                      CONFIG_CORTEX_M3_REMAP_SIZE - VDEV0_RSC_TABLE_SIZE)
 *
 * reserved-memory {
 *     vdev0vring0: vdev0vring0 {
 *         compatible = "shared-dma-pool";
 *         reg = <(VDEV0_VRING0_ADDRESS >> 32) (VDEV0_VRING0_ADDRESS & 0xffffffff)
 *                (VDEV0_VRING0_SIZE >> 32) (VDEV0_VRING0_SIZE & 0xffffffff)>;
 *         no-map;
 *     };
 *
 *     vdev0vring1: vdev0vring1 {
 *         compatible = "shared-dma-pool";
 *         reg = <(VDEV0_VRING1_ADDRESS >> 32) (VDEV0_VRING1_ADDRESS & 0xffffffff)
 *                (VDEV0_VRING1_SIZE >> 32) (VDEV0_VRING1_SIZE & 0xffffffff)>;
 *         no-map;
 *     };
 *
 *     vdev0buffer: vdev0buffer {
 *         compatible = "shared-dma-pool";
 *         reg = <(VDEV0_BUFFER_ADDRESS >> 32) (VDEV0_BUFFER_ADDRESS & 0xffffffff)
 *                (VDEV0_BUFFER_SIZE >> 32) (VDEV0_BUFFER_SIZE & 0xffffffff)>;
 *         no-map;
 *     };
 *
 *     rsc_table: rsc-table {
 *         reg = <(VDEV0_RSC_TABLE_ADDRESS >> 32) (VDEV0_RSC_TABLE_ADDRESS & 0xffffffff)
 *                (VDEV0_RSC_TABLE_SIZE >> 32) (VDEV0_RSC_TABLE_SIZE & 0xffffffff)>;
 *         no-map;
 *     };
 * };
 * @endcode
 *
 * @code {.c}
 * cv72-cm3 {
 *     compatible = "ambarella,cv72-cm3";
 *     interrupts = <0 23 0x1>, <0 24 0x1>;
 *     interrupt-names = "vq0", "vq1";
 *     clocks = <&gclk_axi>;
 *     amb,scr-regmap = <&ca76_scratchpad_syscon>;
 *     amb,axi-regmap = <&s_axi_private
 *                       (CONFIG_CORTEX_M3_SHMEM_ADDRESS)
 *                       (CONFIG_CORTEX_M3_REMAP_ADDRESS >> 32)
 *                       (CONFIG_CORTEX_M3_REMAP_ADDRESS & 0xffffffff)
 *                       (CONFIG_CORTEX_M3_REMAP_SIZE)>;
 *     amb,nscr-regmap = <&n_scratchpad_syscon 0x2000>;
 *     memory-region = <&vdev0buffer>, <&vdev0vring0>, <&vdev0vring1>, <&rsc_table>;
 *     amb,auto-boot = <1>;
 *     status = "okay";
 *};
 * @endcode
 *
 * @subsubsection cm3_driver_rpmsg_unit_test 4.1.4 Unit Test
 *
 * The unit test code is located in `SDK/ambarella/unit_test/linux/misc/test_cm3_rpmsg.c`.
 *
 * @code {.c}
 * ca76 # modprobe ambarella_remoteproc
 * ca76 # test_cm3_rpmsg create /dev/rpmsg_ctrl0 rpmsg-client-sample 1024 1
 * create endpoints
 * endpoint created
 * ca76 # test_cm3_rpmsg test /dev/rpmsg0 -l 1000 -d 20 -s 492
 * test mode using endpoints
 * devpath=/dev/rpmsg0, loop=1000,send_dly=20, payload_sz=492
 * Results:
 * roundtrip: 8 bytes, costs 178 us
 * send only: 1000 messages payload size 492, costs 76562 us
 * receive only: 1000 messages payload size 492, costs 140996 us
 * @endcode
 *
 * @subsection cm3_driver_spi 4.2 Serial Peripheral Interface
 *
 * CM3 implements a slave serial peripheral interface (SPI) device to
 * communicate with a master SPI device, such as microcontroller unit (MCU).
 *
 * @subsubsection cm3_driver_spi_device_tree 4.2.1 Device Tree
 *
 * @code {.c}
 * &slavespi {
 *     status = "disabled";
 * };
 * @endcode
 *
 * @subsubsection cm3_driver_spi_unit_test 4.2.2 Unit Test
 *
 * CM3 waits for data from the MCU.
 *
 * @code {.c}
 * cm3=> spi -l 128 sspi
 * fill data [128] cheksum: 0x1f41
 * @endcode
 *
 * The MCU sends 128-bit data to CM3.
 *
 * @code {.c}
 * Shell> spi 0
 * @endcode
 *
 * - - - -
 * @section cm3_license 5. License
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
 */
/*!
 * @file doc_sys_multi_cluster.h
 * @brief
 * @version 1.0
 * @date 2023-12-5
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
 * @page page_sysdoc_multi_cluster BASE - Multi-Clusters
 *
 * @section multi_cluster_doc_history 0. Revision History
 *  | SDK Version      | Updated Date   | Modification         |
 *  | :----------      | :------------- |:-------------------- |
 *  | Cooper SDK 1.6.0 | 20231225       | Initial Version      |
 *
 * - - - -
 *
 * @section multi_cluster_intro 1. Multi-Clusters Introduction
 *
 * @subsection Multi-multi_cluster_s1 1.1 Introduction
 * This chapter describes the multiple clusters on Ambarella platforms. Currently,
 * only CV3-DEV-H and CV3AD685 chips can support multiple clusters.
 *
 *  | Platform   | Cluster                 |
 *  | :-------   | :--------               |
 *  | CV3-DEV-H  |  4 clusters x quad-A78  |
 *  | CV3AD685   |  3 clusters x quad-A78  |
 *
 * Each cluster is assigned to an independent Linux kernel.
 *
 * Clusters are able to communicate with each other by a <b>virtual ethernet</b>
 * (@ref multi_cluster_blazenet_driver "Blazenet").
 * - Each cluster has its own DRAM address space and IO resource.
 * - Cluster 0 is the primary cluster, others are secondary clusters.
 * - The primary cluster creates a network file system (NFS) service
 *   (@ref multi_cluster_nfs_rootfs) for secondary clusters.
 *
 *
 * - - - -
 *
 * @section multi_cluster_design 2. Design
 *
 * Taking `cv3_dk_mini` board as an example to show the design concept of multiple
 * clusters.
 *
 * <table>
 * <caption>Table 2-1. CV3 DK_mini IO Resource.</caption>
 * <tr><th>Resource                                             <th>Description
 * <tr><td>Dynamic random access memory (DRAM)                  <td>32 GiB
 * <tr><td>Universal asynchronous receiver / transmitter (UART) <td>4 x USB to serial debug UART
 * <tr><td>Ethernet port                                        <td>4 x port
 * </table>
 *
 * @subsection multi_cluster_design_mem_layout 2.1 Memory Layout
 *
 * The figure below describes the memory layout of multiple clusters.
 *
 * @image html cv3_dk_mini_multi_cluster_mem_layout.png  "Figure 2-1. CV3 Dk_mini Memory Layout."
 *
 * Each secondary cluster has 4-GiB work memory. The work memory size of
 * <b>primary cluster</b> is <b>20462 MiB</b>, it can be computed as below:
 *
 * - 20 GiB is equal to 20480 MiB.
 * - KERNEL_RAM_START in `.config` is 0x1200000 (18 MiB).
 * - The size of work memory assigned to primary cluster is 20480 - 18 = 20462 MiB.
 *
 * <b>Primary cluster</b>'s work memory is declared in bootargs(`cv3_dk_mini.dts`)
 * @code
 *      bootargs = "console=ttyS0 mem=20462M init=/linuxrc earlycon pci=nomsi ...
 * @endcode
 *
 * @subsection multi_cluster_design_io_res 2.2 IO Resource
 *
 * <table>
 * <caption>Table 2-2. CV3 Dk_mini IO Assignment.</caption>
 * <tr><th>cluster   <th>tty                    <th> ethernet    <th>blazenet
 * <tr><td>0         <td>/dev/ttyS0 (APB_UART)  <td> eth0	 <td>blazenet@01/02/03
 * <tr><td>1         <td>/dev/ttyS1 (AHB_UART0) <td> eth1        <td>blazenet@01
 * <tr><td>2         <td>/dev/ttyS2 (AHB_UART1) <td> eth2        <td>blazenet@02
 * <tr><td>3         <td>/dev/ttyS3 (AHB_UART2) <td> eth3        <td>blazenet@03
 * </table>
 *
 * In order to simplify the system design, all physical Ethernet ports are assigned to the
 * primary cluster by default. In customer own use case, they can also assign physical
 * Ethernet to secondary cluster for different purpose.
 *
 * @subsection multi_cluster_design_boot_flow 2.3 Boot Flow
 *
 * The following figure describes the boot flow of multiple clusters.
 *
 * @image html cv3_dk_mini_multi_cluster_boot_flow.png "Figure 2-2. Multiple Clusters Boot Flow."
 *
 * - - - -
 *
 * @section multi_cluster_blazenet_driver 3. Blazenet
 *
 * Blazenet is a virtual Ethernet driver which is based on remote processor messaging (rpmsg)
 * device. Blazenet on primary cluster is in `rpmsg master` mode, on secondary cluster is in
 * `rpmsg slave` mode.
 *
 * However, Linux kernel does not support `rpmsg slave` mode, Ambarella implements an extra
 * driver to support this mode.
 *
 * Enable <b>blazenet</b> during configuration:
 * @code
 * $ make linux_menuconfig_single
 *   -> Device Drivers
 *       -> Rpmsg Drivers
 *           -> Ambarella RPMSG
 *               <*> Blazenet driver
 *               -*- Ambarella RPMSG driver
 *               -*- RPMSG name service announcement for slave
 *               -*- Virtio RPMSG bus driver for slave
 * @endcode
 *
 * <table>
 * <caption>Table 3-1. Blazenet IP Assignment in Each Cluster.</caption>
 * <tr><th>             <th> cluster-0   <th> cluster-1   <th> cluster-2   <th> cluster-3
 * <tr><th>blazenet@01  <td> 192.168.1.1 <td> 192.168.1.2 <td> X           <td> X
 * <tr><th>blazenet@02  <td> 192.168.2.1 <td> X           <td> 192.168.2.2 <td> X
 * <tr><th>blazenet@03  <td> 192.168.3.1 <td> X           <td> X           <td> 192.168.3.2
 * </table>
 *
 * Currently, Blazenet IP assignment is hardcode in script `rootfs/skeleton/initramfs_sysroot/usr/bin/create_cluster_nfs.sh`.
 *
 * From secondary clusters' point of view, blazenet is to communicate with primary
 * cluster only. Secondary clusters are unable to directly communicate with each other.
 * Enable the <b>ip_forward</b> feature in the primary cluster so that secondary clusters can talk with each other.
 * @code
 * echo 1 > /proc/sys/net/ipv4/ip_forward
 * @endcode
 *
 * The figure below describes the network routing via primary cluster.
 *
 * @image html cv3_dk_mini_multi_cluster_blazenet.png  "Figure 3-1. Blazenet Network on CV3 Dk_mini."
 *
 * - - - -
 *
 * @section multi_cluster_nfs_rootfs 4. NFS Rootfs
 *
 * Since seconary clusters are not assigned to any storge devices, customers use <b>NFS rootfs</b>
 * as secondary clusters' rootfs.
 *
 * The <b>NFS service</b> is created by primary cluster, the NFS shared
 * folder is `/nfs`.
 *
 * The following script is responsible for creating
 * <b>NFS service</b>, `rootfs/skeleton/initramfs_sysroot/usr/bin/create_cluster_nfs.sh`.
 *
 * The rootfs of primary and seconary clusters are stored on an extra SD card. There are two
 * partitions on SD card, `/dev/mmcblk0p1` and `/dev/mmcblk0p2`.
 *  - The `/dev/mmcblk0p1` is primary's rootfs.
 *  - The `/dev/mmcblk0p2` is seconary's rootfs, and it's mounted to `/nfs` by
 *    primary cluster, which means all seconary clusters share a same rootfs.
 *
 *
 * Actually, users can specify the rootfs by Linux bootargs
 * `cluster_nfsroot` (cluster_nfsroot=[primary device][, seconary device]),
 * @code
 * bootargs = "... cluster_nfsroot=mmcblk0p1,mmcblk0p2";
 * @endcode
 *
 * - - - -
 *
 * @section multi_cluster_boot 5. Boot Multiple Clusters for CV3 Dk_mini
 *
 * @subsection multi_cluster_boot_build 5.1 Build
 *
 * Use the following commands to build the firmware for CV3 Dk_mini:
 * @code
 * build $ cd ambarella/boards/cv3_dk_mini
 * build $ source ../../build/env/amba-build.env
 * build $ make ipcam_clusters_config
 * build $ make -j 8
 * @endcode
 *
 * @subsection multi_cluster_boot_burn_fw 5.2 Burn the Firmware
 *
 * Burn the firmware `bst_bld_env_dtb_kernel.bin` or `bst_bld_env_dtb_kernel.elf` using <b>AmbaUSB-v6.x</b> version.
 * @code
 * build $ ls ../../out/amba_out/cv3_dk_mini/firmware/
 * bld.bin  bld.fw   bst_bld_env_dtb_kernel.bin  bst_bld_env_dtb_kernel.fw  bst.fw   dtb.elf  env.bin  env.fw      kernel.elf
 * bld.elf  bst.bin  bst_bld_env_dtb_kernel.elf  bst.elf                    dtb.bin  dtb.fw   env.elf  kernel.bin  kernel.fw
 * @endcode
 *
 * Open other 3 USBs to the serial devices at the PC side, after the system is booting up, the following will display.
 *
 * @image html cv3_dk_mini_multi_cluster_console.png  "Figure 5-1. CV3 Dk_mini console."
 *
 * The primary cluster successfully enters Linux shell and seconary clusters are blocked waitting for NFS rootfs.
 *
 * @subsection multi_cluster_boot_make_rootfs 5.3 Make Rootfs
 *
 * -# Ethernet is up, connect with host PC at `ETH0`.
 * -# Insert a micro SD card into the slot `MICRO SD`
 *
 * @image html cv3_dk_mini_multi_cluster_device_snapshot.png "Figure 5-2. CV3 Dk_mini Device."
 *
 * Follow the steps below to make the rootfs:
 *
 * 1. Ping the host PC in the console of primary cluster, ensure that the physical Ethernet can work properly.
 *  	@code
 *  	board # ping 10.0.0.120
 *  	64 bytes from 10.0.0.120: seq=0 ttl=64 time=0.666 ms
 *  	64 bytes from 10.0.0.120: seq=1 ttl=64 time=0.233 ms
 *  	--- 10.0.0.120 ping statistics ---
 *  	2 packets transmitted, 2 packets received, 0% packet loss
 *  	round-trip min/avg/max = 0.233/0.449/0.666 ms
 *  	@endcode
 *
 * 2. Transfer <b>rootfs.ext4</b> to the boards using FTP protocol.
 * 	If the host PC is Linux, go to `out/amba_out/cv3_dk_mini/images`, and use tool <b>ftp</b> to transfer files.
 * 	@code
 * 	build $ ls
 * 	ambust_ambausb_lpddr5_none_release.bin   bld.bin  cluster1_dtb.bin  cluster3_dtb.bin  dtb.bin  fwp.bin  initramfs.cpio.gz  rootfs.bin
 * 	ambust_fastboot_lpddr5_none_release.bin  bst.bin  cluster2_dtb.bin  clusters_env.bin  env.bin  Image    kernel.bin         rootfs.ext4
 * 	build $ ftp 10.0.0.2
 * 	build $ Connected to 10.0.0.2.
 * 	build $ 220 Operation successful
 * 	build $ Name (10.0.0.2:build-machine): root
 * 	build $ 331 Specify password
 * 	build $ Password:			# 'press enter key'
 * 	build $ 230 Operation successful
 * 	build $ Remote system type is UNIX.
 * 	build $ Using binary mode to transfer files.
 * 	build $ ftp> put rootfs.ext4
 * 	build $ local: rootfs.ext4 remote: rootfs.ext4
 * 	build $ 200 Operation successful
 * 	build $ 150 Ok to send data
 * 	build $ 226 Operation successful
 * 	build $ 252385280 bytes sent in 4.69 secs (51.2918 MB/s)
 * 	@endcode
 *
 * 	If the host PC is Windows, use FTP app <b>Filezilla</b> to transfer files.
 * 	@image html cv3_dk_mini_multi_cluster_filezilla.png "Figure 5-3. Filezilla."
 *
 * 	After `rootfs.ext4` is successfully transferred to the board, users can find it under `/`,
 * 	@code
 * 	board # ls /rootfs.ext4
 * 	rootfs.ext4
 * 	@endcode
 *
 * 3. Create SD partitions.
 * 	Two partitions are required to be created on SD card, each partition size should be larger than 1 GiB.
 * 	@code
 * 	board # fdisk /dev/mmcblk0
 *      @endcode
 * 	The number of cylinders for this disk is set to 489728.
 * 	There is nothing wrong with that, but it is larger than 1024,
 * 	and in certain setups it can cause the following issues:
 * 	1) Software that runs at boot time (for example, old versions of LILO)
 * 	2) Booting and partitioning software from other OSs
 * 	   (for example, DOS FDISK, OS/2 FDISK)
 * 	@code
 * 	Command (m for help): p
 * 	Disk /dev/mmcblk0: 15 GB, 16047407104 bytes, 31342592 sectors
 * 	489728 cylinders, 4 heads, 16 sectors / track
 * 	Units: sectors of 1 * 512 = 512 bytes
 *
 * 	Device       Boot StartCHS    EndCHS        StartLBA     EndLBA    Sectors  Size Id Type
 * 	/dev/mmcblk0p1    0,1,1       1023,3,16           16    2097167    2097152 1024M 83 Linux
 * 	/dev/mmcblk0p2    1023,3,16   1023,3,16      2097168    4194319    2097152 1024M 83 Linux
 *
 * 	Command (m for help): d
 * 	Partition number (1-4): 1
 *
 * 	Command (m for help): d
 * 	Selected partition 2
 *
 * 	Command (m for help): d
 * 	No partition is defined yet!
 *
 * 	Command (m for help): p
 * 	Disk /dev/mmcblk0: 15 GB, 16047407104 bytes, 31342592 sectors
 * 	489728 cylinders, 4 heads, 16 sectors / track
 * 	Units: sectors of 1 * 512 = 512 bytes
 *
 * 	Device       Boot StartCHS    EndCHS        StartLBA     EndLBA    Sectors  Size Id Type
 *
 * 	Command (m for help): n
 * 	Partition type
 * 	   p   primary partition (1-4)
 * 	   e   extended
 * 	p
 * 	Partition number (1-4): 1
 * 	First sector (16-31342591, default 16):
 * 	Using default value 16
 * 	Last sector or +size{,K,M,G,T} (16-31342591, default 31342591): +2G
 *
 * 	Command (m for help): n
 * 	Partition type
 * 	   p   primary partition (1-4)
 * 	   e   extended
 * 	p
 * 	Partition number (1-4): 2
 * 	First sector (4194320-31342591, default 4194320):
 * 	Using default value 4194320
 * 	Last sector or +size{,K,M,G,T} (4194320-31342591, default 31342591): +2G
 *
 * 	Command (m for help): w
 * 	The partition table has been altered.
 * 	Calling ioctl() to re-read partition table
 * 	@endcode
 *
 * 4. Program **rootfs.ext4** into SD partition.
 * 	@code
 * 	board # dd if=/tmp/rootfs.ext4 of=/dev/mmcblk0p1
 * 	board # dd if=/tmp/rootfs.ext4 of=/dev/mmcblk0p2
 * 	@endcode
 *
 * Now, all clusters rootfs are ready, reboot the board.
 *
 * **NOTE**
 *
 * - Add files to slave clusters' rootfs, please go to cluster0's directory `/nfs`.
 * - Setup network with specified IP or MAC address, please refer to following script,
 *   and add them in `/nfs/etc/network/cluster-if.sh`,
 *   @code
 *   #!/bin/sh
 *   let addr=$1+100
 *
 *   MAC=8A:97:4F:39:0$1:AA
 *   IP=10.0.0.$addr
 *
 *   ifconfig eth0 hw ether $MAC
 *   ifconfig eth0 $IP
 *   @endcode
 * - - - -
 *
 * @section multi_cluster_cavalry 6. Cavalry in Multi-Cluster
 *
 * The Cavalry support on a multi-cluster system can provide users with the same user experience
 * as in a single-cluster environment.
 * Users can submit Cavalry jobs on any cluster, utilizing libraries such as NNCtrl, Cavalry_Mem,
 * and tools like cavalry_top provided by Cavalry.
 *
 * @subsection multi_cluster_cvr_mem_setup 6.1 Memory Setup
 * In multi-cluster setup, each Cavalry driver instance on a cluster has its own separate private memory,
 * and this can be configured through menuconfig.
 *
 * @par For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 *    -*- board (boards)  --->
 *          Memory  --->
 *             (128) CV Private Memory size in MB for cluster 0
 *             (128) CV Private Memory size in MB for cluster 1
 *             (128) CV Private Memory size in MB for cluster 2
 *             (128) CV Private Memory size in MB for cluster 3
 * @endcode
 *
 * @subsection multi_cluster_cvr_limitations 6.2 Limitations
 * Currently, there are certain limitations to the use of multi-cluster Cavalry driver :
 *   - When starting the vector processor (VP), the primary CPU cluster (cluster-0) must
 *     start VP before the secondary clusters (cluster-1/2/3).
 *   - When stopping the VP, the primary cluster (cluster-0) can only stop VP after all
 *     secondary clusters (cluster-1/2/3) have already stopped VP.
 *
 * - - - -
 *
 * @section multi_cluster_license 7. License
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
 */

/*!
 * @file doc_sys_lychee_os.h
 * @brief
 * @version 1.0
 * @date 2023-12-22
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
 * @page page_sysdoc_lychee_os BASE - Lychee OS
 *
 * @section multi_cluster_doc_history 0. Revision History
 * <table>
 * <caption id="lycheeos-history">Lychee OS History.</caption>
 * <tr><th>System Version<th> Updated Date<th align="left"> Modification
 * <tr><td>202312a<td>20231226
 *     <td> Initial Version
 * </table>
 *
 * @section lychee_os_intro 1. Lychee OS Introduction
 * @subsection lychee_os_what_is_lycheeos 1.1 What is LycheeOS
 * Lychee operating system (OS) is built on the Fedora desktop system and it is a specialized Linux
 * distribution tailored for Ambarella system on chip (SoC), featuring Cortex® A76 / A78 architecture
 * and optimized for high performance.
 * Built upon the foundation of Fedora, Lychee OS leverages Fedora's extensive
 * software repository, utilizing it as the primary open-source software (OSS) source.
 * The distribution employs customized compile options specifically designed for
 * the Cortex A76 / A78AE architecture of Ambarella SoC.
 * Lychee OS is compatible with CV5, CV72, and CV3, with the added advantage of
 * graphics processing unit (GPU) acceleration for the graphical user interface (GUI) on CV3.
 *
 * @image html am_lychee_os_logo.svg "Figure 1-1 LycheeOS Logo." width=400px
 *
 * 
 * @subsection lychee_os_deploy_and_develop_in_one_box 1.2 Deploy and Develop in One Box
 * Lychee OS incorporates a comprehensive set of development tools,
 * encompassing GCC, Clang, LLVM, RUST, Golang, BCC, Perl, Python, Lua, and Java.
 * As a natively compiled system, it is proficient in generating full-feature
 * OSS while being optimized for both feature richness and code size reduction.
 * The distribution uses Red Hat Packet Manager (RPM) package management, ensuring explicit package
 * dependency checks for enhanced reliability.
 *
 * What's more, Lychee OS supports a variety of popular open source middleware
 * of multimedia, autonomous-driving and robotics, such as GStreamer, Apollo CyberRT, and ROS2.
 *
 * Users can easily install, utilize and develop these open source modules with Lychee OS.
 *
 * @image html am_lychee_os_show_ros2.jpg "Figure 1-2. Render Point Cloud with Rviz2 in LycheeOS Desktop." width=800px
 *
 * @image html am_lychee_os_show_gst.jpg "Figure 1-3. NN Inference with GStreamer in LycheeOS Desktop." width=800px
 * 
 *
 * @subsection lychee_os_native_compile_amba_private_drivers_and_app 1.3 Native Compile Ambarella private Drivers and Application
 * @par Quicker
 * Reduce compile time, improve work efficiency, connect the user's keyboard and mouse,
 * compile drivers and applications on Ambarella CV3 / CV72 with Lychee.
 *
 * @par Easier
 * Get just what you need and compile exactly what you need, just design a
 * brick, but not build a full house from scratch.
 *
 * @par More Standard
 * Drivers and applications can work with different hardware (HW) configurations and it is no need to recompile for
 * HW changes. Similar to a standard PC or smartphone application, compile it and drop, it will
 * work!
 *
 * @image html  am_lychee_os_desktop.png "Figure 1-4. LycheeOS Desktop." width=800px
 *
 * - - - -
 *
 * @section lychee_os_install_lycheeos_on_cv3 2. Install Lychee OS on CV3
 * @subsection lychee_os_burn_uboot 2.1 Flash Uboot
 *
 * @par Preparation
 * -# Connect "USB Console", "AmbaUSB" and "microcontroller unit (MCU)" port with USB cable to the PC.<br>
 *
 * -# Install AmbaUSB application with the version at least 5.0.7 to the PC.<br>
 *
 * -# Prepare an secure digital (SD) card with at least 64G. It is recommended to use a 128G SD
 *    card, but the maximum size cannot exceed 256G.
 *
 * -# Select the required version of Uboot. At present, there are mainly three kinds
 *  of Uboot:
 *  - 2808-MHz clock / 32-GB memory<br>
 *  - 3192-MHz clock / 32-GB memory<br>
 *  - 3192-MHz clock / 64-GB memory<br>
 *
 * -# Select the requred version of Lychee OS.
 *
 * @note
 * Please contact the Ambarella support team to obtain the Uboot and Lychee OS.
 *
 * @par Flash Uboot Steps:
 * -# Click "USB Console" and "MCU" serial consoles.<br>
 * There are two important and different consoles:<br>
 * <B>MCU Console</B>: input sequence to control the CV3 Dk_mini
 *                     (power on /power off / change to USB download mode)<br>
 * <B>USB Console</B>: print and display the log<br>
 *
 * -# Click the <B>MCU Console</B> and then enter the <B>'p'</B> command to power
 * on the CV3 Dk_mini.
 * @code
 * ### MCU Console
 * > p
 * @endcode
 * -# Open the <B>MCU Console</B> and then enter the <B>'u'</B> command to
 *    change the status of MCU to download.
 * @code
 * ### MCU Console
 * > u
 * @endcode
 *
 * -# Download Uboot
 *  - Open the <b>AmbaUSB</b> application.
 *  - Select <b>CV3</b> in the chip selection box.
 *  - Click <b>Find</b> button to find prepared Uboot file, such as 'uboot-cooper-sdk-2808MHz.elf'.
 *  - Click <b>Download</b> button.
 *
 * -# Wait for the download to complete, and view the flash information in the console
 *    to determine if the flashing was successful.
 *
 * -# After flashing Uboot, enter 'p' in "MCU Console" to power off the device.
 *
 * @subsection lychee_os_install_lychee_to_sd_card 2.2 Install Lychee OS to an SD Card
 * There are two methods for installing Lychee OS. One method is to automatically run
 * an installation sricpt to automatically install Lychee OS and the other is to manually
 * install it.
 * Ambarella recommends the automatic installation method as it is convenient and fast.
 * If users require more advanced configurations, such as customizing the SD storage space,
 * it is recommended to use the manual installation method.
 *
 * @note
 * Both methods only support desktop Linux systems.
 *
 * <br>
 * @par Perpare the Tools Required for Installation
 * -# <B>gparted:</B> This is disk partitioning tool, and it is used to partition the
 *                     SD card
 * -# <B>lsblk:</B> This is a Linux tool used to list information about block
 *                  devices in the system
 * -# <B>losetup:</B> This is a Linux tool for setting up and controlling
 *                    loopback devices
 * -# <B>rsync:</B> This is a fast and flexible tool for synchronizing files
 *                  and directories <br>
 *
 * If these tools are not installed, execute the corresponding installation
 * command below according to the user's Linux system.
 * @code{.c}
 * ### Example for Fedora
 * build$ sudo dnf update
 * build$ sudo dnf install
 * build$ sudo dnf install util-linux gparted rsync
 *
 * ### Example for Ubuntu
 * build$ sudo apt-get update
 * build$ sudo apt-get install util-linux gparted rsync
 * @endcode
 *
 * <br>
 * @par Automatical Installation (Recommended)
 *
 * Insert the SD card into the desktop Linux PC and then run
 * `Install_Lychee_Raw_Disk_Image_v4.4.1.sh` on desktop Linux PC.<br>
 * @code{c}
 * sudo ./Install_Lychee_Raw_Disk_Image_v4.4.1.sh --image=xxx.raw.xz --media=/dev/sdx
 * @endcode
 * If the installation is successful, the following print information will display:
 * @code{c}
 * =====================================================
 * Successfully umount sd* and loop*
 * =====================================================
 * @endcode
 *
 * <br>
 * @par Manual Installation
 * -# Insert the SD card users' prepared into your desktop Linux PC
 *
 * -# Make partitions to this SD card
 *  - Run `sudo gparted` command to open the application <br>
 *  - Delete the original paritions of this SD card <br>
 *  - Create a new "GPT" partition table <br>
 *  - Create the 1st partition (boot partition), change the size to 1 GB (1024 MB),
 *    file system type "ext4" (MUST), change the partition label to `lychee.boot` (MUST) <br>
 *  - Create the 2nd partition (root partition), change the size to 60 GB (61440 MB),
 *    file system type "btrfs" (MUST), Change the partition label to `lychee.root` (MUST) <br>
 *  - Create the 3rd partition (home partition), change the size to 50 GB (51200 MB),
 *    file system type "btrfs" (MUST), change the partition label to `lychee.home` (MUST) <br>
 *
 * -# Confirm that the partitions `lychee.root` and `lychee.boot` already exist
 *  @code{.c}
 *  build$ lsblk -f
 *  build$ NAME     FSTYPE   FSVER LABEL     UUID       FSAVAIL FSUSE% MOUNTPOINTS
 *  build$ sda
 *  build$  ├─sda1      ext4     1.0   lychee.boot aae28d63-3d1d-4208-8c79-378400980373
 *  build$  └─sda2      btrfs          lychee.root 26985f95-4078-4a5b-8eda-d112b1d1a0b6
 *  build$ ...
 *  @endcode
 *
 * -# Mount the `boot` and `root` partitions on the SD card
 *  @code{.c}
 *  build$ sudo mkdir /run/media/lychee.boot
 *  build$ sudo mkdir /run/media/lychee.root
 *  build$ sudo mount /dev/sda1 /run/media/lychee.boot
 *  build$ sudo mount /dev/sda2 /run/media/lychee.root
 *  @endcode
 *
 * -# Make the loopback device of Lychee OS with `losetup` tool
 *  @code{.c}
 *  ### Select the lychee OS raw file under the current file
 *  build$ sudo losetup -P --show --find ./lychee_cv3_cooper_20230719.raw
 *
 *  ### Check if the following devices are in the /dev directory.
 *  ### if they are, then it is sucessful.
 *  build$ ls /dev/dev/loop0p*
 *  build$ /dev/loop0p1     //this is boot
 *  build$ /dev/loop0p2     //this is root
 *  @endcode
 *
 * -# Copy boot data to boot partition in the SD card
 * @code{.c}
 * build$ sudo mount -t auto /dev/loop0p1 /mnt
 * build$ pushd /mnt
 * build$ sudo rsync -Hav . /run/media/lychee.boot/
 * build$ popd
 * build$ sudo umount /mnt
 * @endcode
 *
 * -# Copy root data to root partition in the SD card
 * @code{.c}
 * build$ sudo mount -t auto /dev/loop0p2 /mnt
 * build$ pushd /mnt
 * build$ sudo rsync -Hav . /run/media/lychee.root/
 * build$ popd
 * build$ sudo umount /mnt
 *
 * ### Add the following line into fstab
 * build$ sudo vim /run/media/lychee.root/etc/fstab
 * LABEL=lychee.home /home btrfs defaults 0 0
 * ### save and quit
 * @endcode
 *
 * -# Uninstall loopback devices
 * @code{.c}
 * build$ sudo losetup -D
 * @endcode
 *
 * -# Umount `lychee.root` and `lychee.boot`
 * @code{.c}
 *  build$ sudo umount  /run/media/lychee.boot
 *  build$ sudo umount  /run/media/lychee.root
 *  build$ sudo rm /run/media/lychee.boot -rf
 *  build$ sudo rm /run/media/lychee.root -rf
 * @endcode
 *
 * @subsection lychee_os_install_lychee_the_first_boot_lychee_os 2.3 The First Boot Lychee OS
 * -# Insert the SD card into the `CV3 Dk_mini`
 * -# Connect CV3 board to a monitor with full HD resolution (1920x1080),
 *    using high definition multimedia interface (HDMI®) cable
 * -# Connect eth0 with an Ethernet cable to a router with internet
 *    access (IMPORTANT)
 * -# Connect the keyboard and mouse to CV3 USB port (MUST for the first time boot to
 *    do the initial setup)
 * -# Input 'p' in "MCU Console" to power on the device, then wait for the
 *    "initial setup GUI" to show up in the monitor
 * -# Set up <b>Time Zone</b> in the GUI program
 * -# Set up <b>Host Name</b>
 * -# Set up <b>Root User</b>, in the GUI program, choose <b>Enable root</b>
 * -# Set up <b>User Account</b>, in the GUI program, in <b>advanced</b> section,
 *    add the user to <b>wheel,root,disk,dialout,video,sys,admin</b> group
 * -# Press <b>Finish</b> in the GUI program
 *
 * @note
 * After pressing the <b>Finish</b> button, wait approximately 5 minutes as the
 * system is running `selinux-autorelabel.service`.
 *
 * <br>
 * @par User Group Explaination
 * <table>
 * <caption id="lycheeos-history">Table 2-1. User Group Explaination.</caption>
 * <tr><th>Group<th> Explaination<th align="left">
 * <tr><td> <B>wheel</B>
 *     <td> Users in wheel group will be granted to run commands that
 *          are only allowed for root
 * <tr><td> <B>root</B>
 *     <td> Users in root group will be granted to access files in root group
 * <tr><td> <B>disk</B>
 *     <td> Users in disk group will be granted to access device node in disk
 *          group, for example `/dev/sdX /dev/mmcblkXXX`, and more.
 * <tr><td> <B>dialout</B>
 *     <td>  Users in dialout group will be granted to access the serial device,
 *           for example `/dev/ttySX`, `/dev/ttyUSBX`
 * <tr><td> <B>video</B>
 *     <td>  Users in video group will be granted to access the video device,
 *           for example `/dev/dri/cardX`, `/dev/fbX`, and `/dev/video/XXX`
 * <tr><td> <B>sys</B>
 *     <td> Users in sys group will be granted to access `/sys` file system
 * <tr><td> <B>admin</B>
 *     <td>  Users in admin group will be granted to access system
 *           administrator's tools
 * </table>
 *
 * - - - -
 *
 * @section lychee_os_the_first_login_settings 3. Login Settings
 *
 * @par 1. Set Up MAC Address
 * - Set proper "MAC" address for users' network device
 *   @code{.c}
 *   Lychee$ nm-connection-editor
 *   @endcode
 * - Select the network card that needs to be connected to the internet,
 *   and click the <b>Settings</b> button in the lower left corner.
 * - Select <B>random</B> in the cloned MAC address column in the Ethernet page.
 * - Save and quit.
 *
 * <br>
 * @par 2. Config System Time
 * - Configure to maintain the RTC in universal time, and synchronize the RTC from the system clock.
 *   @code{.c}
 *   Lychee$ sudo timedatectl  set-local-rtc 0
 *   @endcode
 *
 * <br>
 * @par 3. Update the System
 * - Run the command to upgrade the user's system to the latest. And in the future,
 *   if Lychee OS has a newer release, users do not require to go through this process
 *   again to re-install, just need to install Lychee OS repo file and run the command.
 *   @code{.c}
 *   lychee$ sudo dnf update --refresh
 *   @endcode
 *   @note
 *   - Users should consider this Lychee OS as a complete desktop Linux,
 *     and use normal user account to login and work.<br>
 *   - Uboot only supports boot partition with ext4 file system type,
 *     this is probably enhanced in the newer Uboot version.<br>
 *   - The default system language is English, which can be changed after
 *     logging into Linux desktop.
 *
 * <br>
 * @par 4. (Optional) Enable Dual-VOUT
 * - Check if the default DTB supports dual-VOUT: <br>
 *   @code{.c}
 *   Lychee$ vim /boot/extlinux/extlinux.conf
 *   @endcode
 *   The content may be as shown below, note the default label for boot:
 *
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
 *   If the default DTB name (`ambarella-cv3-gpu-dual-vout.dtb` in line 7 above for example)
 *   includes <b>dual-VOUT</b>, it means dual-VOUT is supported.
 *
 *   Or users should change default DTB to one that supports dual-VOUT:
 *
 *   @code{.c}
 *   Lychee$  cd /boot/dtb-5.15.141-300.lch2023.aarch64/ambarella/  # step 1, the path after /boot is defined in line 7 above
 *   Lychee$  ls *dual-vout*.dtb                                    # step 2, check usable dtb
 *   Lychee$  ambarella-cv3-gpu-4K-llava-dual-vout.dtb  ambarella-cv3-gpu-dual-vout.dtb
 *   Lychee$  sudo vim /boot/extlinux/extlinux.conf                 # step 3
 *   @endcode
 *
 * - Or modify dtb to support feature (Advanced):
 *   @code{.c}
 *   Lychee$ sudo dtc -I dtb -O dts ambarella-cv3-gpu.dtb -o ambarella-cv3-gpu-dump.dts               # Decompile dtb to dts
 *   Lychee$ sudo vim ambarella-cv3-gpu-dump.dts                                                      # modify dts
 *   Lychee$ sudo dtc -I dts -O dtb ambarella-cv3-gpu-dump.dts -o ambarella-cv3-gpu-<customized>.dtb  # Compile modified dts to dtb
 *   @endcode
 *
 *   Change the content in `/boot/extlinux/extlinux.conf` (in <b>line 7</b> above for example),
 *   replace the DTB name with one in step 2 shown (such as `ambarella-cv3-gpu-4K-llava-dual-vout.dtb`).
 *
 * - Change lua configuration for HDMI VOUT:
 *   @code{.c}
 *   Lychee$  cd /etc/ambarella/cv3/vout/
 *   Lychee$  sudo ln -sf vout_hdmi_dual.lua vout_hdmi.lua
 *   @endcode
 *
 * - Reboot Lychee and dual-VOUT can be used now.
 *
 * - - - -
 *
 * @section lychee_os_the_local_sdk_repo_setup_guide 4. Setup Local SDK Repo
 *
 * @par Configure Local Repository
 * - Get sdk-release-cv3 local repository. (Contact the Ambarella support team)
 * - Place the ` sdk-release-cv3-local-repo-20231115.tar.xz` in the `/var` dectory
 * - Extract files to the '/var' folder
 * @code{.c}
 * Lychee$ cd /var/ && sudo tar -xvf sdk-release-cv3-local-repo-20231115.tar.xz
 * @endcode
 *
 * @par Create Local SDK `.repo` File
 * -# Create a `yum .repo` file, so that users can use 'dnf' command to manage
 *   software packages in Lychee OS
 *  @code{.c}
 *  Lychee$ sudo vim /etc/yum.repos.d/sdk-release-local.repo
 *  @endcode
 * -# Paste the content below to the `.repo` file for 'dnf' to track and configure the
 *    local SDK repo
 *  @code{.c}
 *   [sdk-release-local]
 *    name=SDK Release - $basearch - CV3
 *    baseurl=file:///var/sdk-release-local-repo/aarch64/
 *    enabled=1
 *    type=rpm
 *    metadata_expire=1h
 *    skip_if_unavailable=True
 *
 *   [sdk-release-local-source]
 *    name=SDK Release - $basearch - CV3 - Sources
 *    baseurl=file:///var/sdk-release-local-repo/src/
 *    enabled=1
 *    type=rpm
 *    metadata_expire=1h
 *    skip_if_unavailable=True
 *  @endcode
 *
 * @par Install SDK Packages to the System
 *
 * Local SDK release repo contains packages:
 * @code{.c}
 *   ambarella-cooper-cv3-kmod (private-driver)
 *   ambarella-cooper-cv3-cavalry-kmod
 *   libamba-cooper-imglib-cv3 (3A)
 *   libamba-vproc-cv3
 *   libamba-data-transfer
 *   ambarella-utility-cv3
 *   libamba-eazyai-cv3
 *   libamba-lwmedia (rtsp)
 *   libamba-eazydds
 *   libamba-dsp-monitor-cv3
 *   libamba-tof-cv3
 *   libamba-textinsert
 * @endcode
 *
 * @par Install Local SDK release run-time, develop, debug meta package, contains the packages mentioned above.
 * @code{.c}
 * Lychee$ sudo dnf install ambarella-cv3-cooper-sdk-run-time ambarella-cv3-cooper-sdk-devel \
 *          ambarella-cv3-cooper-sdk-debug --refresh --repo sdk-release-local
 * @endcode
 *
 * @par If users want to download the source RPM, for example (EazyAI), use the following command.
 * @code{.c}
 *  Lychee$ sudo dnf download --source libamba-eazyai-cv3 --repo sdk-release-local
 * @endcode
 *
 * @par To Upgrade SDK Release Packages
 * @code{.c}
 *  Lychee$ sudo dnf update --refresh --repo sdk-release-local
 * @endcode
 *
 * - - - -
 *
 * @section lychee_os_dnf_command_reference 5. Command Reference : dnf / rpm
 * The commonly used commands for package management in Lychee include:
 * @code{.c}
 * ### Update all installed packages
 * Lychee$ sudo dnf update
 *
 * ### Install the package
 * Lychee$  Lychee $ sudo dnf install <name>
 *
 * ### Update the package
 * Lychee$ sudo dnf update <name>  
 *
 * ### Downgrade the package
 * Lychee$ Lychee $ sudo dnf downgrade <name>
 *
 * ### Search what provides "test_encode" in designated repository
 * Lychee$ sudo dnf repoquery --whatprovide "*test_encode*" --repo lychee-updates-tests
 *
 * ### Clean dnf repo cache
 * Lychee$ sudo dnf clean all
 *
 * ### Show packages installed in your system
 * Lychee$ rpm -qa
 *
 * ### show package info
 * Lychee$ rpm -qi <name>
 *
 * ### show what in the package
 *  Lychee$ rpm -qlp <name>   
 *
 * ### Install the package to your system
 * Lychee $ rpm -ivh <name> 
 *
 * ### What does this file belong to
 * Lychee $ rpm -qf </path/to/file> 
 * @endcode
 *
 * @par Package "ambarella-cv3-cooper-sdk" contains components:
 * - private-driver, cavalry, imglib (3A), vproc, tof, eazydds, data-transfer,
 *   lwmedia, xorg-ambafbdev, dsp-monitor, cvlib, utility of Ambarella
 *   Cooper SDK.
 * - Install all of them using the following command:
 *  @code{.c}
 *  Lychee $ sudo dnf install ambarella-cv3-cooper-sdk --refresh --repo lychee-updates-tests
 *  @endcode
 *
 * For more information about [DNF Fedora official document introduction]
 * (https://docs.fedoraproject.org/en-US/fedora/latest/system-administrators-guide/package-management/DNF/)
 *
 * - - - -
 *
 * @section lychee_os_license 6. License
 *
 * Lychee OS licensed under the MIT license <http://opensource.org/licenses/MIT>.
 *
 * Ambarella SDK software packages license is as follow:
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
 */
/*!
 * @file doc_sysdoc_boot_upgrade.h
 * @date 2022-03-30
 * @author Jing Leng
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
 * @page si_boot_upgrade DESIGN - Boot & Upgrade
 *
 *@section boot_upgrade_doc_history 0. Revision History
 *  | Version  | Updated Date   | Modification         |
 *  | :---     | :------------- |:-------------------- |
 *  | 1.0.0    | 20240115       | Initial Version      |
 *
 * - - - -
 * @section si_partition 1. Partition
 *
 * The Ambarella boot loader (AMBoot) uses a prior knowledge of the storge medium
 * to allocate the different partitions for different usages in the compilation.
 * These partitions are logical groups on the storge devices and they have the
 * continuous physical blocks. This chapter explains two styles of firmware
 * layouts supported by AMBoot.
 * - Section @ref si_flexible_firmware_layout
 * - Section @ref si_legacy_firmware_layout
 *
 * @subsection si_flexible_firmware_layout 1.1 Flexible Firmware Layout
 * For CV72, CV3 and the new evaluation kit (EVK) boards in future, the
 * flexible firmware layout is used. The flexible firmware layout has much merits:<br>
 * - Supports up to 128 partitions, and easy to support more
 * - Supports to determine each partition's name by user
 * - Supports the partition size larger than 4 GB
 * - Supports multi images per partition
 * - Supports multi kernel images and multi dtb binaries
 * - Supports to generate images that burners can use directly, that is, no need
 *      binsplit<br>
 *
 * To use the flexible firmware layout, the user must pay attention to the following
 * three parts to do the configurations.
 *
 * - @par Partition Layout
 *   The pre-located partition definition file is `ambarella/boards/<board_name>/bsp/bsp.h`.
 *   The rules for the firmware layout format is as follows:
 *   @code {.c}
 *   partitions format: <devdef>[;<devdef>]
 *   <devdef> format:   dev=<dev>:<partdef>[,<partdef>]
 *   <partdef> format:  <size>[@<offset>](part-name)
 *   @endcode
 *   @note
 *     - The `dev` in <devdef> must be "nand", "snor" or "emmc".
 *     - The `part-name` in <partdef> can be arbitrary, but must be unique.
 *
 *   Below is a firmware layout example for a NAND flash.
 *   @code {.c}
 *   build$ vim ambarella/boards/<board_name>/bsp/bsp.h
 *   #define AMBOOT_PARTITION_LAYOUT \
 *               "dev=nand:" \
 *               "128k(bst),1024k(bld),896k(dtb),896k(env),128k(cfg)," \
 *               "32m@0x600000(kernel),176m(rootfs),-(raw)"
 *   @endcode
 *   The bootstrap (BST), bootloader (BLD), device tree blob (DTB), environment (ENV),
 *   kernel, and root file system (rootfs) are the default
 *   partition names using in AMBoot to generate the firmware image. If the
 *   user wants to modify the partition names, the firmware profile for generating
 *   the firmware and the ENV file for choosing booting partition must be modified
 *   together.
 *   @note
 *     For more information, the user can refer to
 *     `ambarella/boot/amboot/doc/flexible_firmware.txt`.
 *
 * - @par Firmware Profile
 *   The firmware profile is used for generating the firmware. The default
 *   profile is located under directory `ambarella/boot/ambfw/profile`.
 *   The user can create a new one under `ambarella/boards/<board_name>/bsp` and
 *   select it in menuconfig.
 *   @code {.c}
 *   build$ vim bsp/profile.new
 *   IMAGE_FWPROG    := $(BIN_DIR)/fwp.bin
 *
 *   IMAGE_0_NAME    := bst
 *   IMAGE_0_FILE    := $(BIN_DIR)/bst.bin
 *   IMAGE_0_ADDR    := -1
 *   IMAGE_0_FLAG    := force raw
 *
 *   IMAGE_1_NAME    := bld
 *   IMAGE_1_FILE    := $(BIN_DIR)/bld.bin
 *   IMAGE_1_ADDR    := -1
 *   IMAGE_1_FLAG    := force raw
 *
 *   IMAGE_2_NAME    := env
 *   IMAGE_2_FILE    := $(BIN_DIR)/env.bin
 *   IMAGE_2_ADDR    := -1
 *   IMAGE_2_FLAG    := force
 *
 *   IMAGE_3_NAME    := dtb
 *   IMAGE_3_FILE    := $(BIN_DIR)/dtb.bin
 *   IMAGE_3_ADDR    := -1
 *   IMAGE_3_FLAG    := force
 *
 *   IMAGE_4_NAME    := kernel
 *   IMAGE_4_FILE    := $(BIN_DIR)/kernel.bin
 *   IMAGE_4_ADDR    := $(KERNEL_RAM_START)
 *   IMAGE_4_FLAG    := verify compressed
 *
 *   IMAGE_5_NAME    := rootfs
 *   IMAGE_5_FILE    := $(BIN_DIR)/rootfs.bin
 *   IMAGE_5_ADDR    := -1
 *   IMAGE_5_FLAG    := raw
 *   @endcode
 *   @code {.c}
 *   build$ make menuconfig
 *   boot  --->
 *   [*] ambfw (boot/ambamk)  --->
 *     AMBFW Configuration  --->
 *       [*] Build AMBFW
 *         (profile.new) Firmware Profile
 *   [*] amboot (boot/ambamk)  --->
 *     Ambarella Bootloader Configuration  --->
 *       Firmware Options  --->
 *           Firmware Layout Style (Flexible Firmware Layout)  --->
 *             (X) Flexible Firmware Layout
 *   @endcode
 *
 * - @par ENV File
 *   The ENV file is used to describe the environment variables recognized by AMBoot.
 *   The environment variables include the variables specifying which partition
 *   image is used for booting. The default ENV file is located at the
 *   `ambarella/boot/amboot/src/bld/default.env`. The user can create a new one
 *   with the customized settings named as `<board_name>.env` or
 *   `<BSP_BOARD_VER>.env` under `ambarella/boards/<board_name>/bsp` to replace
 *   it. The `<BSP_BOARD_VER>.env` has a higher priority than `<board_name>.env`.
 *   @code {.c}
 *   build$ vim ambarella/boards/<board_name>/bsp/<board_name>.env
 *   /dts-v1/;
 *
 *   #include "config.h"
 *
 *   / {
 *       compatible = "ambarella,environment";
 *       #address-cells = <1>;
 *       #size-cells = <1>;
 *
 *   #if defined(AMBOOT_DEV_AUTO_BOOT)
 *       auto_boot;
 *   #endif
 *       serial_num = AMBOOT_DEFAULT_SN;
 *
 *       bootcmd = "";
 *
 *       bootargs = "";
 *
 *       kernel_meta {
 *           partition = "kernel";
 *           binary_id = <0>;
 *       };
 *
 *       dtb_meta {
 *           partition = "dtb";
 *           binary_id = <0>;
 *       };
 *       rootfs_meta {
 *           partition = "rootfs";
 *           binary_id = <0>;
 *       };
 *
 *       netdev_eth0 {
 *           mac = "00:00:00:00:00:00";
 *           mask = "0.0.0.0";
 *           gw = "0.0.0.0";
 *           ip = "0.0.0.0";
 *       };
 *
 *       tftpd {
 *           server,ip = "0.0.0.0";
 *           kernel,file = "";
 *           kernel,addr = <0x00000000>;
 *           ramdisk,file = "";
 *           ramdisk,addr = <0x00000000>;
 *       };
 *   };
 *   @endcode
 *   @note
 *     - For more information, the user can refer to
 *       <a href="txt/env.txt" target="_blank"><b>env.txt</b></a>
 *     - When programmed to the EVK board, the ENV image allocates two copies
 *       in ENV partition on the storage medium. If any one of the
 *       ENV image is corrupted, the other one will be used to automatically recover the corrupted
 *       one.
 *
 * @subsection si_legacy_firmware_layout 1.2 Legacy Firmware Layout
 * For CV2x and CV5x, the legacy firmware layout is used. The legacy firmware
 * layout is easy to use and has been used and verified by many customers over the
 * years. Only the following partitions are supported: BST, BLD, PTB,
 * ATF, PBA, PRI, SEC, BAK, RMD, ROM, DSP, LNX, SWP, ADD, ADC, CFG, and RAW. It has
 * some limitations. For example, it is not allowed to add other more
 * partitions, each partition's name is also unchangeable and so on.<br>
 * The file path for partition definition is `ambarella/boards/<board_name>/bsp/bsp.h`.
 * @code {.c}
 * build$ vim ambarella/boards/<board_name>/bsp/bsp.h
 * #define AMBOOT_BST_SIZE     (AMBOOT_BST_FIXED_SIZE)
 * #define AMBOOT_BLD_SIZE     (AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PTB_SIZE     (AMBOOT_MIN_PART_SIZE * 7)
 * #define AMBOOT_ATF_SIZE     (AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PBA_SIZE     (16 * 1024 * 1024)
 * #define AMBOOT_PRI_SIZE     (16 * 1024 * 1024)
 * #define AMBOOT_SEC_SIZE     (0  * 1024 * 1024)
 * #define AMBOOT_BAK_SIZE     (0  * 1024 * 1024)
 * #define AMBOOT_RMD_SIZE     (0  * 1024 * 1024)
 * #define AMBOOT_ROM_SIZE     (0  * 1024 * 1024)
 * #define AMBOOT_DSP_SIZE     (0  * 1024 * 1024)
 * #define AMBOOT_LNX_SIZE     (144 * 1024 * 1024)
 * #define AMBOOT_SWP_SIZE     (0  * 1024 * 1024)
 * #define AMBOOT_ADD_SIZE     (12  * 1024 * 1024)
 * #define AMBOOT_ADC_SIZE     (0  * 1024 * 1024)
 * @endcode
 *
 * The BST, BLD, partition table (PTB), Arm® trusted
 * firmware (ATF), primary (PRI), and Linux (LNX) are used by default. Those
 * partitions whose size is set to 0 are recognized as unused. All optional and
 * reserved partitions can be utilized for user storage. For example, Android
 * data (ADD) pre-boot authentication (PBA), SEC, backup (BAK), RAMDisk (RMD),
 * or read-only memory (ROM) can be used as user partitions.
 *
 * @note
 *   - The legacy firmware layout only supports a fixed number of partitions.
 *   - Each partition's name is unchangeable.
 *   - One partition only supports one image.
 *
 * The following conventions are used in the partition names.
 * <table>
 * <caption id="firmware_partition_table">Table 1-1. List of Fixed Partition Names.</caption>
 * <tr><th align="center">Partition</th><th align="center">Choice</th><th align="center">Description</th></tr>
 * <tr><td>BST</td><td>Mandatory</td><td>AMBoot bootstrap code for hardware initialization</td></tr>
 * <tr><td>BLD</td><td>Mandatory</td><td>AMBoot bootloader</td></tr>
 * <tr><td>PTB</td><td>Mandatory</td><td>Device tree binary (DTB) and partition table, save the command line and boot flags.</td></tr>
 * <tr><td>ATF</td><td>Mandatory</td><td>Arm® trusted firmware (ATF), which can be used as bl2 to verify bl3x.bin in secure boot</td></tr>
 * <tr><td>PBA</td><td>Optional</td><td>Persistent basic input / output system (BIOS) application for safe recovery<br>
 * For AB upgrade, the system stores kernel B image; for PBA upgrade, it stores kernel+ramfs.<br>
 * If PRI or RMD / ROM is corrupted, AMBoot can boot from the PBA partition and execute the recovery processes.</td></tr>
 * <tr><td>PRI</td><td>Mandatory</td><td>Primary code image, which refers to the Linux kernel image<br>
 * For AB and PBA upgrades, the system stores the kernel A image.</td></tr>
 * <tr><td>SEC</td><td>Optional</td><td>Secondary code image, which can be used to store the private customer data</td></tr>
 * <tr><td>BAK</td><td>Optional</td><td>Backup code image, which can be uesed to backup images of all other specifized partitons</td></tr>
 * <tr><td>RMD</td><td>Optional</td><td>RAMDisk rootfs. If RAMDisk is selected, AMBoot loads the RAMDisk image at the boot stage.</td></tr>
 * <tr><td>ROM</td><td>Optional</td><td>For AB upgrades, ROM stores kernel B rootfs. It is not used for PBA upgrades</td></tr>
 * <tr><td>DSP</td><td>Reserved</td><td>Backup digital signal processor (DSP) microcode</td></tr>
 * <tr><td>LNX</td><td>Mandatory</td><td>Stores kernel A rootfs for AB and PBA upgrades</td></tr>
 * <tr><td>SWP</td><td>Reserved</td><td>(Reserved)</td></tr>
 * <tr><td>ADD</td><td>Reserved</td><td>Android data partition, or used for Oryx configuration</td></tr>
 * <tr><td>ADC</td><td>Reserved</td><td>Android cache partition, or used for Oryx upgrade firmware</td></tr>
 * <tr><td>RAW</td><td>Optional</td><td>Remaining space in current storage media<br>
 * If there is remaining space in the storage media, especially in the case of electronic multi-media cards (eMMCs),
 * Ambarella suggests that users enable this partition in order to make use of all available space.</td></tr>
 * </table>
 *
 * - - - -
 *
 * @section si_boot 2. Boot
 * This chapter explains the boot flow based on the CV2x SDK 3.0. The boot flow
 * for the Cooper software development kit (SDK) is similar. This chapter contains the following sections:
 * - Section @ref si_normal_boot
 * - Section @ref si_secure_boot
 *
 * @subsection si_normal_boot 2.1 Normal Boot
 *
 * @subsubsection si_normal_boot_flow 2.1.1 Normal Boot Flow
 *
 * @image html normal_boot_flow.jpg "Figure 2-1. Normal Boot Flow."
 *
 * - BST: 4K bootstrap binary for CVxx written by assembly.
 *   + BST starts from `ambarella\amboot\src\bst\<chip_name>\start.S`.
 * - BLD: The boot loader is the main part of AMBoot.
 *   + It initializes hardware devices and maps memory space, then jumps to the
 *     kernel partition.
 *   + BLD starts from `ambarella\amboot\src\bld\main.c`.
 * - PTB: In the normal boot process, the boot flag and command line are from
 *   the PTB.
 *
 * @subsection si_secure_boot 2.2 Secure Boot
 *
 * @subsubsection si_secure_boot_flow 2.2.1 Secure Boot Flow
 *
 * @image html secure_boot_flow.jpg "Figure 2-2. Secure Boot Flow."
 *
 * - BST: `bstemmc.S`, `bstemmc.S`, `bstspinor.S`
 *   + Load `bl2.bin` into dynamic random access memory (DRAM) and verify `bl2.bin`.
 *   + If the authentication is successful, jump to bl2 address x22 (bl2_main).
 *   + If the authentication fails, halt the CPU to die (loop at the current
 *     instruction address).
 * - BL2: `external\tee\arm-trusted-firmware\bl2`
 *   + Load `bl3x.bin` (BL31, BL32, BL33) into DRAM and verify `bl3x.bin`.
 *   + If the authentication is successful or if the verification step is
 *     skipped, jump to bl31 DRAM first address (next_load_info).
 *   + If the authentication fails, the `bl31.bin` will be erased from the
 *     memory and enter into the CPU loop.
 * - BL31: `tee\arm-trusted-firmware\bl31`
 *   + Initialize and start the open portable trusted execution environment
 *     (OP-TEE) operating system (OS) (BL32).
 *   + Obtain the address of the kernel image in read-only memory (ROM).
 *   + Jump to BL33 (BLD).
 * - BL32: optee_os
 *   + Data encryption can be performed in the un-secure world (Linux) or in
 *     the secure world (OP-TEE).
 *   + The trusted application (TA) functions can be run in the secure world (OP-TEE).
 * - BL33: `bld.bin`
 *   + Load kernel image and verify `kernel_release.bin`.
 *   + If the authentication is successful, jump to the kernel (the jump
 *     partition depends on bootflags in bl33).
 *   + If the authentication fails, halt the CPU to die (loop at the current
 *     instruction address).
 *
 * @subsubsection si_secure_boot_key_mgr 2.2.2 Key Management
 *
 * 1. Local approach:
 *
 *   @image html secure_boot_local_key.jpg "Figure 2-3. Local Key Approach."
 *
 *   The private keys are stored in the local area.
 *   - Root of trust (RoT) public key: `ambarella\amboot\build\keys\rot_public.bin`
 *   - RoT private key: `ambarella\amboot\build\keys\rot_private.pem`
 *   - Kernel private key: `ambarella\amboot\build\keys\auth_kernel_private.txt`
 *   - TA private key: `external\tee\optee_os\keys\default_ta.pem`

 * 2. Remote procedure call (RPC) ToolKit approach:
 *
 *   @image html secure_boot_rpc_key.jpg "Figure 2-4. RPC Key Approach."
 *
 *   The private keys are stored in the remote server.
 *   - Remote RoT public key: `ambarella\packages\security\build\tz_dev_server\rot_public.bin`
 *   - RoT private key: `ambarella\packages\security\build\tz_dev_server\rot_private.pem`
 *   - Kernel private key: `ambarella\packages\security\build\tz_dev_server\kernel_private.pem`
 *   - TA private key: `ambarella\packages\security\build\tz_dev_server\default_ta.pem`
 *
 *   RPC usage:
 *       1. Select in menuconfig and specify the different local port for the
 *          different account.
 *           @code {.c}
 *           build $ make menuconfig
 *             Ambarella Package Configuration ->
 *               [*] Build Utilities ->
 *                 [*] Build Ambarella Security Package ->
 *                   [*] Build Security Package for AMBOOT ->
 *                     [*] Using RPC(Remote Procedure Call) Toolkit to sign binary ->
 *                        (9088) Local port
 *           @endcode
 *       2. Set up the development server and daemon before compilation.
 *           @code {.c}
 *           host $ cd ambarella/packages/security/build/tz_dev_server/
 *           host $ ./tz_dev_server ./db 9002
 *           host $ cd ambarella/packages/security/build/tz_dev_daemon/
 *           host $ ./tz_dev_daemon 10.4.8.67 9002 9088
 *           @endcode
 *       3. For more details, refer to
 *          `ambarella\packages\security\build\trustzone_secure_boot_toolkit_help.txt`.
 *
 * @subsubsection si_secure_boot_en_otp 2.2.3 Enable OTP
 *
 * 1. Enable one-time programmable (OTP) with a power-on configuration (POC) pin.<br>
 *   - If POC[6] pulls up, secure boot can be enabled temporarily.
 *   - If POC[6] pulls low, secure boot will be disabled.
 *
 * 2. Enable OTP permanently.<br>
 *    If the eFUSE bit is used, the secure boot will be permanently enabled. If
 *    the secure boot is permanently enabled, POC[6] cannot enable / disable
 *    the secure boot. Because this process is irrevocable. The user uses it with
 *    cautions while performing this operation. Typically, this step is performed
 *    in manufacturing.
 *    @code {.c}
 *    board # modprobe optee
 *    board # tee-supplicant &
 *    board # test_program_otp --enablesecurebootpermanently
 *    @endcode
 *
 * - - - -
 *
 * @section si_upgrade 3. Upgrade
 * Since Cooper SDK supports two styles of firmware layouts, the upgrade will be
 * described based on these styles.<br>
 * This chapter contains the following sections:
 * - Section @ref si_fw_and_image
 * - Section @ref si_tftp_upgrade
 * - Section @ref si_sd_upgrade
 * - Section @ref si_image_upgrade
 *
 * @subsection si_fw_and_image 3.1 Firmware and Image
 * After SDK compilation, various binaries are generated according to the
 * different configurations. Ambarella uses the following conventions for
 * different binaries according its usages:
 *   - <B>Binary</B>: It is generated directly by compilation and it is executable
 *     code, data, filesystem or others.
 *   - <B>Image</B>: It may have a header and contains one or several binaries.
 *     It can be burned into storage media.
 *   - <B>Firmware</B>: It consists of self-burning header and several images
 *     and binaries. It can be used by AmbaUSB programming, trivial file transfer protocol (TFTP) upgrade and secure card (SD)
 *     upgrade.<br>
 *
 * According to the Ambarella SDK version and its build methods, the user gets
 * the firmwares, images and binaries from different paths:
 * @par For Flexible Firmware Layout:
 * <table>
 * <caption id="si_flex_fw_table">Table 3-1. List of Firmwares, Images, and Binaries’ Path for Flexible.</caption>
 * <tr>
 * <th rowspan="2" align="center">Type</th>
 * <th colspan="2" align="center">Cooper SDK</th>
 * </tr>
 * <tr>
 * <th align="center">Amba Build</th>
 * <th align="center">Yocto Build</th>
 * </tr>
 * <tr>
 * <th align="center">Firmware Path</th>
 * <td>`out/amba_out/<board_name>/firmware`</td>
 * <td>`out/yocto_out/<board_name>/firmware`</td>
 * </tr>
 * <tr>
 * <th align="center">Image Path</th>
 * <td>`out/amba_out/<board_name>/objects/boot/ambfw`</td>
 * <td>`out/yocto_out/<board_name>/tmp/work/cortexaXX-poky-linux/ambfw/1.0-r0/ambfw-1.0`</td>
 * </tr>
 * <tr>
 * <th align="center">Binary Path</th>
 * <td>`out/amba_out/<board_name>/images`</td>
 * <td>`out/yocto_out/<board_name>/images`</td>
 * </tr>
 * </table>
 *
 * <table>
 * <caption id="si_flex_fw_table">Table 3-2. List of Firmwares, Images, and Binaries. </caption>
 * <tr>
 * <th rowspan="3" align="center">Image Type</th>
 * <th colspan="6" align="center">Cooper SDK</th>
 * <th rowspan="3" align="center">Description</th>
 * </tr>
 * <tr>
 * <th colspan="3" align="center">Amba Build</th>
 * <th colspan="3" align="center">Yocto Build</th>
 * </tr>
 * <tr>
 * <th align="center">Firmware</th>
 * <th align="center">Image</th>
 * <th align="center">Binary</th>
 * <th align="center">Firmware</th>
 * <th align="center">Image</th>
 * <th align="center">Binary</th>
 * </tr>
 * <tr>
 * <th align="center">BST</th>
 * <td>`bst.elf`</td><td>`bst.img`</td><td>`bst.bin`</td>
 * <td>`bst.elf`</td><td>`bst.img`</td><td>`bst.bin`</td>
 * <td>BST partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">BLD</th>
 * <td>`bld.elf`</td><td>`bld.img`</td><td>`bld.bin`</td>
 * <td>`bld.elf`</td><td>`bld.img`</td><td>`bld.bin`</td>
 * <td>BLD partition binary for normal boot</td>
 * </tr>
 * <tr>
 * <th align="center">BL2</th>
 * <td>`bl2.elf`</td><td>`bl2.img`</td><td>`bl2.bin`</td>
 * <td>`bl2.elf`</td><td>`bl2.img`</td><td>`bl2.bin`</td>
 * <td>BL2 partition binary for secure boot</td>
 * </tr>
 * <tr>
 * <th align="center">FIP</th>
 * <td>`fip.elf`</td><td>`fip.img`</td><td>`fip.bin`</td>
 * <td>`fip.elf`</td><td>`fip.img`</td><td>`fip.bin`</td>
 * <td>FIP partition binary for secure boot</td>
 * </tr>
 * <tr>
 * <th align="center">ENV</th>
 * <td>`env.elf`</td><td>`env.img`</td><td>`env.bin`</td>
 * <td>`env.elf`</td><td>`env.img`</td><td>`env.bin`</td>
 * <td>ENV partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">DTB</th>
 * <td>`dtb.elf`</td><td>`dtb.img`</td><td>`dtb.bin`</td>
 * <td>`dtb.elf`</td><td>`dtb.img`</td><td>`dtb.bin`</td>
 * <td>ENV partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">KERNEL</th>
 * <td>`kernel.elf`</td><td>`kernel.img`</td><td>`kernel.bin`</td>
 * <td>`kernel.elf`</td><td>`kernel.img`</td><td>`kernel.bin`</td>
 * <td>Kernel partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">PBA</th>
 * <td>`pba.elf`</td><td>`pba.img`</td><td>`pba.bin`</td>
 * <td></td><td></td><td></td>
 * <td>PBA partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">ROOTFS</th>
 * <td>`rootfs.elf`</td><td>`rootfs.img`</td><td>`rootfs.bin`</td>
 * <td>`rootfs.elf`</td><td>`rootfs.img`</td><td>`rootfs.bin`</td>
 * <td>Rootfs partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">ALL</th>
 * <td>`bst_bld_env_dtb_kernel_rootfs.elf` or `bst_bl2_fip_env_dtb_kernel_rootfs.elf (Secure Boot)`</td><td></td><td></td>
 * <td>`bst_bld_env_dtb_kernel_rootfs.elf` or `bst_bl2_fip_env_dtb_kernel_rootfs.elf (Secure Boot)`</td><td></td><td></td>
 * <td>Firmware for all partitions (Normal Boot)</td>
 * </tr>
 * <tr>
 * <th align="center">ALL</th>
 * <td>`bst_bl2_fip_env_dtb_kernel_rootfs.elf`</td><td></td><td></td>
 * <td>`bst_bl2_fip_env_dtb_kernel_rootfs.elf`</td><td></td><td></td>
 * <td>Firmware for all partitions (Secure Boot)</td>
 * </tr>
 * </table>
 *
 * @note
 *   - The final generated firmware contains images and binaries used by the
 *     following partitions respectively:
 *     + Images: ENV, DTB, KERNEL, PBA
 *     + Binaries: BST, BLD, ROOTFS, BL2, FIP
 *   - These images and binaries are also used by the
 *     @ref si_image_upgrade "Image Upgrade"
 *
 * @par For Legacy Firmware Layout:
 * <table>
 * <caption id="si_legacy_fw_path_table">Table 3-3. List of Firmwares, Images, and Binaries’ Path.</caption>
 * <tr>
 * <th rowspan="2" align="center">Type</th>
 * <th colspan="2" align="center">Cooper SDK</th>
 * <th align="center">CV2x SDK 3.0</th>
 * </tr>
 * <tr>
 * <th align="center">Amba Build</th>
 * <th align="center">Yocto Build</th>
 * <th align="center">Amba Build</th>
 * </tr>
 * <tr>
 * <th align="center">Firmware Path</th>
 * <td>`out/amba_out/<board_name>/firmware`</td>
 * <td>`out/yocto_out/<board_name>/firmware`</td>
 * <td>`out/<board_name>/images`</td>
 * </tr>
 * <tr>
 * <th align="center">Image/Binary Path</th>
 * <td>`out/amba_out/<board_name>/images`</td>
 * <td>`out/yocto_out/<board_name>/images`</td>
 * <td>BST, BLD, ATF, DTB: `out/<board_name>/amboot`<br />KERNEL, PBA: `out/<board_name>/kernel`<br />ROOTFS: `out/<board_name>/rootfs`</td>
 * </tr>
 * </table>
 *
 * <table>
 * <caption id="si_legacy_fw_table">Table 3-4. List of Firmwares, Images, and Binaries.</caption>
 * <tr>
 * <th rowspan="3" align="center">Image Type</th>
 * <th colspan="4" align="center">Cooper SDK</th>
 * <th colspan="2" align="center">CV2x SDK 3.0</th>
 * <th rowspan="3" align="center">Description</th>
 * </tr>
 * <tr>
 * <th colspan="2" align="center">Amba Build</th>
 * <th colspan="2" align="center">Yocto Build</th>
 * <th colspan="2" align="center">Amba Build</th>
 * </tr>
 * <tr>
 * <th align="center">Firmware</th>
 * <th align="center">Image / Binary</th>
 * <th align="center">Firmware</th>
 * <th align="center">Image / Binary</th>
 * <th align="center">Firmware</th>
 * <th align="center">Image / Binary</th>
 * </tr>
 * <tr>
 * <th align="center">BST</th>
 * <td>`bst_release.elf`</td><td>`bst.bin`</td>
 * <td>`bst_release.elf`</td><td>`bst.bin`</td>
 * <td>`bst_release.elf`</td><td>`bst_release.bin`</td>
 * <td>BST partition image</td>
 * <tr>
 * <th align="center">BLD</th>
 * <td>`bld_release.elf`</td><td>`bld.bin`</td>
 * <td>`bld_release.elf`</td><td>`bld.bin`</td>
 * <td>`bld_release.elf`</td><td>`bld_release.bin`</td>
 * <td>BLD partition binary for normal boot</td>
 * </tr>
 * <tr>
 * <th align="center">ATF</th>
 * <td>`atf_release.elf`</td><td>`atf.bin`</td>
 * <td>`atf_release.elf`</td><td>`atf.bin`</td>
 * <td>`atf_release.elf`</td><td>`atf_release.bin`</td>
 * <td>ATF partition binary for secure boot</td>
 * </tr>
 * <tr>
 * <th align="center">FIP</th>
 * <td>`fip_release.elf`</td><td>`fip.bin`</td>
 * <td>`fip_release.elf`</td><td>`fip.bin`</td>
 * <td>`fip_release.elf`</td><td>`fip_release.bin`</td>
 * <td>BLD partition binary for secure boot</td>
 * </tr>
 * <tr>
 * <th align="center">DTB</th>
 * <td></td><td>`dtb.bin`</td>
 * <td></td><td>`dtb.bin`</td>
 * <td></td><td>`<board_name>.dtb`</td>
 * <td>DTS binary stored in PTB partition</td>
 * </tr>
 * <tr>
 * <th align="center">KERNEL</th>
 * <td>`kernel_release.elf`</td><td>`kernel.bin` or `Image.SIGNED (secure boot)`</td>
 * <td>`kernel_release.elf`</td><td>`kernel.bin` or `Image.SIGNED (secure boot)`</td>
 * <td>`kernel_release.elf`</td><td>`Image` or `Image.SIGNED (secure boot)`</td>
 * <td>PRI partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">PBA</th>
 * <td>`pba_release.elf`</td><td>`pba.bin` or `Image.SIGNED (secure boot)`</td>
 * <td></td><td></td>
 * <td>`pba_release.elf`</td><td>`pba_zImage` or `pba_zImage.SIGNED (secure boot)`</td>
 * <td>PBA partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">ROOTFS</th>
 * <td>`lnx_release.elf`</td><td>`rootfs.bin`</td>
 * <td>`lnx_release.elf`</td><td>`rootfs.bin`</td>
 * <td>`lnx_release.elf`</td><td>`ubifs` (Take UBIFS as an example)</td>
 * <td>LNX partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">ALL</th>
 * <td>`bst_bld_kernel_lnx_release.elf` or `bst_bld_atf_kernel_lnx_release.elf (Secure Boot)`</td><td></td>
 * <td>`bst_bld_kernel_lnx_release.elf` or `bst_bld_atf_kernel_lnx_release.elf (Secure Boot)`</td><td></td>
 * <td>`bst_bld_kernel_lnx_release.elf` or `bst_bld_atf_kernel_lnx_release.elf (Secure Boot)`</td><td></td>
 * <td>Firmware for all partitions</td>
 * </tr>
 * </table>
 * @note
 *   - For legacy firmware layout, there is no difference between images and
 *     binaries. They are all raw binaries.
 *   - These images / binaries are also used by @ref si_image_upgrade "Image Upgrade".
 *
 * @subsection si_tftp_upgrade 3.2 TFTP Upgrade
 *
 * The default configuration for the platform is to boot from flash with the file
 * system on the EVK board's NAND flash.<br>
 * In some cases, only Ethernet access is available. This section describes upgrading
 * the NAND flash file system by using the trivial file transfer protocol (TFTP) server.
 *
 * @subsubsection si_tftp_upgrade_methods 3.2.1 TFTP Upgrade Methods
 *
 * There are two different methods to perform the upgrade: upgrade_partition and
 * AMBoot shell.<br>
 * The <B>upgrade_partition</B> tool helps users manage the Ambarella boot
 * configuration in rootfs and enables them to set up the Ambarella bootloader
 * options easily without inputting much command lines to the <B>AMBoot</B> shell.
 *
 * <table>
 * <caption id="tftp_commands_table">Table 3-5. List of TFTP Upgrade Commands.</caption>
 * <tr>
 * <th align="center">TFTP Upgrade for Flexible Firmware Layout<br> in the Linux System</th>
 * <th align="center">TFTP Upgrade for Legacy Firmware Layout<br> in the Linux System</th>
 * <th align="center">TFTP Upgrade<br> in the AMBoot Shell</th>
 * <th align="center">Description</th>
 * </tr>
 * <tr>
 * <td>`upgrade_partition -e /dev/mtd3 --auto_boot 0`</td>
 * <td>`upgrade_partition --auto_boot 0`</td>
 * <td>`setenv auto_boot 0`</td>
 * <td>1 (Load Linux kernel from NAND flash) or 0</td>
 * </tr>
 * <tr>
 * <td>`upgrade_partition -e /dev/mtd3 -E -i 0 --mac 20:11:09:19:10:39`</td>
 * <td>`upgrade_partition --ethmac 20:11:09:19:10:39`</td>
 * <td>`setenv eth 0 mac 20:11:09:19:10:39`</td>
 * <td>Eth0 MAC address</td>
 * </tr>
 * <tr>
 * <td>`upgrade_partition -e /dev/mtd3 -E -i 0 --ip 10.0.0.2`</td>
 * <td>`upgrade_partition --lan_ip 10.0.0.2`</td>
 * <td>`setenv eth 0 ip 10.0.0.2`</td>
 * <td>Eth0 IP address</td>
 * </tr>
 * <tr>
 * <td>`upgrade_partition -e /dev/mtd3 -E -i 0 --mask 255.255.255.0`</td>
 * <td>`upgrade_partition --lan_mask 255.255.255.0`</td>
 * <td>`setenv eth 0 mask 255.255.255.0`</td>
 * <td>Eth0 netmask</td>
 * </tr>
 * <tr>
 * <td>`upgrade_partition -e /dev/mtd3 -E -i 0 --gw 10.0.0.1`</td>
 * <td>`upgrade_partition --lan_gw 10.0.0.1`</td>
 * <td>`setenv eth 0 gw 10.0.0.1`</td>
 * <td></td>Eth0 default gateway
 * </tr>
 * <tr>
 * <td>`upgrade_partition -e /dev/mtd3 --tftpd_ip 10.0.0.1`</td>
 * <td>`upgrade_partition --tftpd 10.0.0.1`</td>
 * <td>`setenv tftpd 10.0.0.1`</td>
 * <td>TFTP server IP address</td>
 * </tr>
 * <tr>
 * <td>`reboot`</td>
 * <td>`reboot`</td>
 * <td></td>
 * <td>Reboot to enter into Amboot.</td>
 * </tr>
 * <tr>
 * <td>`tftp program firmware.bin 0x4000000 1`</td>
 * <td>`tftp program firmware.bin 0x4000000 1`</td>
 * <td>`tftp program firmware.bin 0x4000000 1`</td>
 * <td>Use tftp to download the firmware and program it.</td>
 * </tr>
 * </table>
 *
 * @note
 *   Assume that the `/dev/mtd3` in the first column is the ENV partition.
 *
 * @subsubsection si_tftp_upgrade_example 3.2.2 Example: TFTP Upgrade
 *
 * 1. Prepare the TFTP upgrade.
 *   - The user must confirm that the Ethernet cable is connected and the TFTP
 *     server is running on the host PC.
 *   - If the user uses the `upgrade_partition` tool, the following option must
 *     be selected.
 *     @par For CV2x SDK 3.0 Amba build:
 *     @code {.c}
 *     build $ make menuconfig
 *       Ambarella Application Configuration ->
 *         Build Utilities ->
 *           [*] Build Ambarella upgrade partition
 *     @endcode
 *     @par For Cooper Amba Build:
 *     @code {.c}
 *     build $ make menuconfig
 *       app --->
 *         utility --->
 *           upgrade_partition --->
 *             [*] upgrade-partition (app/utility/upgrade_partition/app)
 *     @endcode
 *     @par For Cooper Yocto Build:
 *     @code {.c}
 *     build $ make menuconfig
 *       meta-ambaapp --->
 *         recipes-upgrade-partition --->
 *           [*] upgrade-partition (meta-ambaapp/recipes-upgrade-partition/upgrade-partition)
 *     @endcode
 *   - The `AMBoot` must enable the Ethernet to download the firmware. The
 *     following option must be selected.
 *     @par For CV2x SDK 3.0 Amba build:
 *     @code {.c}
 *     build $ make menuconfig
 *       Ambarella Bootloader Configuration  --->
 *         Hardware Options  --->
 *           [*] Support Micrel Ethernet Phy
 *     @endcode
 *
 *     @par For Cooper Amba Build:
 *     @code {.c}
 *     build $ make menuconfig
 *       [*] boot (boot) --->
 *         Bootloader --->
 *           Ambarella Bootloader Configuration  --->
 *             Hardware Options  --->
 *               [*] Support Micrel Ethernet Phy
 *     @endcode
 *     @par For Cooper Yocto Build:
 *     @code {.c}
 *     build $ make menuconfig
 *       meta-ambabsp --->
 *         recipes-bsp --->
 *           [*] boot (meta-ambabsp/recipes-bsp/boot) --->
 *             Bootloader --->
 *               Ambarella Bootloader Configuration  --->
 *                 Hardware Options  --->
 *                   [*] Support Micrel Ethernet Phy
 *     @endcode
 *   - The generated firmware path can be found in the following path:
 *     + For CV2x SDK 3.0: `ambarella/out/<board_name>/images/xxx_release.bin`
 *     + For Cooper SDK Amba Build: `ambarella/out/amba_out/<board_name>/firmware/xxx_release.bin`
 *     + For Cooper SDK Yocto Build: `ambarella/out/yocto_out/<board_name>/firmware/xxx_release.bin`
 *
 *   - The user must place the firmware in the TFTP server's directory.
 *   - The user might need to rename the default firmware name. The firmware
 *     name size must not exceed the TFTP server's limitation (32 characters).
 *
 * 2. Configure the TFTP parameters.
 *   - For upgrade_partition:
 *     + For flexible firmware layout:
 *       @code {.c}
 *       board # upgrade_partition -e /dev/mtd3 -E -i 0 --mac 20:11:09:19:10:39
 *       board # upgrade_partition -e /dev/mtd3 -E -i 0 --ip 10.0.0.2
 *       board # upgrade_partition -e /dev/mtd3 -E -i 0 --mask 255.255.255.0
 *       board # upgrade_partition -e /dev/mtd3 -E -i 0 --gw 10.0.0.1
 *       board # upgrade_partition -e /dev/mtd3 --auto_boot 0
 *       board # upgrade_partition -e /dev/mtd3 --tftpd_ip 10.0.0.1
 *       @endcode
 *     + For legacy firmware layout:
 *       @code {.c}
 *       board # upgrade_partition --ethmac 20:11:09:19:10:39
 *       board # upgrade_partition --lan_ip 10.0.0.2
 *       board # upgrade_partition --lan_mask 255.255.255.0
 *       board # upgrade_partition --lan_gw 10.0.0.1
 *       board # upgrade_partition --auto_boot 0
 *       board # upgrade_partition --tftpd 10.0.0.1
 *       @endcode
 *   - For AMBoot shell:
 *     @code {.c}
 *     amboot> setenv auto_boot 0
 *     amboot> setenv eth 0 mac 20:11:09:19:10:39
 *     amboot> setenv eth 0 ip 10.0.0.2
 *     amboot> setenv eth 0 mask 255.255.255.0
 *     amboot> setenv eth 0 gw 10.0.0.1
 *     amboot> setenv tftpd 10.0.0.1
 *     @endcode
 *
 * 3. Display the current settings.
 *   - For AMBoot shell:
 *     @code {.c}
 *     amboot> show netboot
 *     eth0_mac: 20:11:09:19:10:39
 *     eth0_ip: 10.0.0.2
 *     eth0_mask: 255.255.255.0
 *     eth0_gw: 10.0.0.1
 *     eth1_mac: 0.0.0.0
 *     eth1_ip: 0.0.0.0
 *     eth1_mask: 0.0.0.0
 *     eth1_gw: 0.0.0.0
 *     tftpd: 10.0.0.1
 *     pri_addr: 0x00000000
 *     pri_file:
 *     rmd_addr: 0x00000000
 *     rmd_file:
 *     @endcode
 *
 * 4. Enter AMBoot, download and program the firmware.
 *   - Type the following command to start the upgrade:
 *     @code {.c}
 *     amboot> tftp program firmware.bin 0x4000000 1
 *     @endcode
 *   - The downloading progress is shown below.
 *     @image html tftp_boot_enter_netboot_mode.png "Figure 3-1. Enter Netboot Mode."
 *   - When the firmware download is complete, the message "Success" is
 *     displayed on the serial console.
 *     @note
 *       - The EVK board boots if the firmware is configured to automatically boot
 *         after the download is complete.
 *       - If the firmware is not configured to automatically boot, press the
 *         <b>RESET</b> button on the EVK board to load the firmware.
 *
 * @subsection si_sd_upgrade 3.3 SD Upgrade
 *
 * This section describes the usage of the SD upgrade.
 *
 * @subsubsection si_sd_upgrade_images 3.3.1 Images for SD Upgrade
 *
 * If the default build configuration (`make cvx_ipcam_config`) is used,
 * only one BLD, BST, kernel, and rootfs will be generated.
 * After the compilation is complete, there will be six files in `ambarella\out\cvx_board\images`.
 *
 * <table>
 * <caption id="sd_upgrade_images">Table 3-6. Firmwares for SD Upgrade.</caption>
 * <tr>
 * <th align="center">Image Name</th>
 * <th align="center">Description</th>
 * </tr>
 * <tr><td>`bst_release.bin`</td><td>BST partition binary</td></tr>
 * <tr><td>`bld_release.bin`</td><td>BLD partition binary</td></tr>
 * <tr><td>`bst_bld_release.bin`</td><td>BST and BLD partition binary</td></tr>
 * <tr><td>`kernel_release.bin`</td><td>PRI partition binary (kernel image)</td></tr>
 * <tr><td>`lnx_release.bin`</td><td>LNX partition binary (root file system)</td></tr>
 * <tr><td>`bst_bld_kernel_lnx_release.bin`</td><td>All the binary files including PTB partition binary</td></tr>
 * </table>
 *
 * @subsubsection si_sd_upgrade_example 3.3.2 Example: SD Upgrading the Partitions
 *
 * In the serial console window, press and hold the <B>ENTER</B> key on the keyboard,
 * and then press the <B>RESET</B> button on the EVK board. The EVK board will
 * switch to the AMBoot shell.
 *
 * Then, users can type the following commands to upgrade different partitions.
 * The binary name is shown in the @ref si_sd_upgrade_images "3.2.1 Images for SD Upgrade".
 * @code {.c}
 * amboot> sd init 0 hs
 * amboot> fs init
 * amboot> fs ls
 * amboot> fs read <binary name> <MEMFWPROG_RAM_START> 1
 * @endcode
 *
 * @subsection si_image_upgrade 3.4 Image Upgrade
 * In some cases, the user might want to change some partition images stored in
 * the development board rather than replacing the entire firmware. This section
 * will introduce the upgrade methods and procedures to fullfill this goal.
 *
 * @subsubsection si_image_upgrade_modes 3.4.1 Image Upgrade Modes
 *
 * In Ambarella SDK design, two image upgrade modes are recommended: <B>AB Upgrade</B>
 * and <B>PBA Upgrade</B>.
 *
 * @par AB Upgrade:
 *   - Advantages:
 *     + During AB upgrade, the system functions can still run normally.
 *     + If the AB upgrade fails, the system which performing the upgrade
 *       operation can still run normally.
 *     + Rolling back to the previous system version at any time is possible.
 *     + If the current file system has been damaged, rolling back to another
 *       file system to restore it is possible.
 *   - Disadvantages:
 *     + Compared to PBA upgrade, an additional rootfs partition must be
 *       allocated to enable the AB upgrade function.
 *     + The system version control must be performed to prevent a system
 *       version rollback.
 *   - AB upgrade flow for flexbile firmware layout:
 *     @image html ab_upgrade_flow_flexible.jpg "Figure 3-2. AB Upgrade Flow for Flexbile Firmware Layout."
 *   - AB upgrade flow for legacy firmware layout:
 *     @image html ab_upgrade_flow_legacy.jpg "Figure 3-3. AB Upgrade Flow for Legacy Firmware Layout."
 *
 * @par PBA Upgrade:
 *   - Advantages:
 *     + ROM only requires one additional partition for PBA (PBA is a small
 *       system used to perform online upgrades only); additional rootfs are not required.
 *     + The ROM size for PBA partition is just a little bigger than size of the kernel image.
 *     + Users are not required to pay extra attention to the system version.
 *     + If the PBA upgrade is interrupted unexpectedly, the user can still
 *       enter the PBA system to do the upgrade again.
 *   - Disadvantages:
 *     + If the PBA upgrade failed, the only way to restore the system is to
 *       upgrade again in PBA system.
 *     + The system cannot roll back to the previous system version.
 *   - PBA upgrade flow for flexbile firmware layout:
 *     @image html pba_upgrade_flow_flexible.jpg "Figure 3-4. PBA Upgrade Flow for Flexbile Firmware Layout."
 *   - PBA upgrade flow for legacy firmware layout:
 *     @image html pba_upgrade_flow_legacy.jpg "Figure 3-5. PBA Upgrade Flow for Legacy Firmware Layout."
 *
 * @note
 *   1. No matter what upgrade method is used, there is only one copy for BST,
 *      BLD and ATF / BL2 (secure boot) partition. They are shared by the kernel
 *      and the rootfs that have two copies.
 *   2. If any of them except BST fails to boot after upgrade, the user can
 *      restore them through the `BAK` partition which can save backups for
 *      these partitions.
 *   3. In rare cases, new upgrade kernel may be not compatible with the old BLD
 *      image in the board, the user must upgrade the BLD (BST and ATF / BL2 may
 *      be also needed) together with the kernel in such cases.
 *   4. For BST, if it fails to boot, the only way to rescue it is to let the
 *      system enter force USB boot mode and download the firmware through
 *      the AmbaUSB tool. So users are suggested not to upgrade this
 *      partition unless necessary.
 *   5. The `upgrade_partition` tool used for upgrading the images are not
 *      compatible for flexible and legacy firmware layout.
 *   6. PBA upgrade is not supported by the Yocto Build.
 *   7. For flexible firmware layout:
 *     - No matter what upgrade method is used, there is only one copy for BST,
 *       BLD, BL2 (secure boot) and ENV partition. They are shared by the kernel
 *       and the rootfs that have two copies.
 *     - There are two DTB partitions that store different boot arguments for
 *       switching to the rootfs to be used.
 *     - ENV partition has two copies in one partition by default in case of the
 *       data corruption, the user must take care of this when modifying it in
 *       the apps.
 *     - ENV partition is used to switch the DTB, kernel and rootfs partitions
 *       to be used.
 *   8. For legacy firmware layout:
 *     - No matter what upgrade method is used, there is only one copy for BST,
 *       BLD, ATF (secure boot) and PTB partition. They are shared by the kernel
 *       and the rootfs that have two copies.
 *     - The DTB is also stored in the PTB partition and PTB partition has two
 *       copies in one partition by default in case of the data corruption. The
 *       user must take care of this when modifying it in the apps.
 *
 *@subsubsection si_images_for_upgrading 3.4.2 Images for Upgrading
 * From the following tables, the user can get a quick overview on
 * where to get the images used by the upgrade.
 * @par For Flexible Firmware Layout:
 * <table>
 * <caption id="si_flex_fw_table">Table 3-7. Images for Image Upgrade. </caption>
 * <tr>
 * <th rowspan="2" align="center">Image Type</th>
 * <th colspan="2" align="center">Cooper SDK</th>
 * <th rowspan="2" align="center">Description</th>
 * </tr>
 * <tr>
 * <th align="center">Amba Build</th>
 * <th align="center">Yocto Build</th>
 * </tr>
 * <tr>
 * <th align="center">BST</th>
 * <td>`out/amba_out/<board_name>/images/bst.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/bst.bin`</td>
 * <td>BST partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">BLD</th>
 * <td>`out/amba_out/<board_name>/images/bld.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/bld.bin`</td>
 * <td>BLD partition binary for normal boot</td>
 * </tr>
 * <tr>
 * <th align="center">BL2</th>
 * <td>`out/amba_out/<board_name>/images/bl2.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/bl2.bin`</td>
 * <td>BL2 partition binary for secure boot</td>
 * </tr>
 * <tr>
 * <th align="center">FIP</th>
 * <td>`out/amba_out/<board_name>/images/fip.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/fip.bin`</td>
 * <td>FIP partition binary for secure boot</td>
 * </tr>
 * <tr>
 * <th align="center">ENV</th>
 * <td>`out/amba_out/<board_name>/objects/boot/ambfw/env.img`</td>
 * <td>`out/yocto_out/<board_name>/tmp/work/cortexaXX-poky-linux/ambfw/1.0-r0/ambfw-1.0/env.img`</td>
 * <td>ENV partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">DTB</th>
 * <td>`out/amba_out/<board_name>/objects/boot/ambfw/dtb.img`</td>
 * <td>`out/yocto_out/<board_name>/tmp/work/cortexaXX-poky-linux/ambfw/1.0-r0/ambfw-1.0/dtb.img`</td>
 * <td>ENV partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">KERNEL</th>
 * <td>`out/amba_out/<board_name>/objects/boot/ambfw/kernel.img`</td>
 * <td>`out/yocto_out/<board_name>/tmp/work/cortexaXX-poky-linux/ambfw/1.0-r0/ambfw-1.0/kernel.img`</td>
 * <td>Kernel partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">PBA</th>
 * <td>`out/amba_out/<board_name>/objects/boot/ambfw/pba.img`</td>
 * <td></td>
 * <td>PBA partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">ROOTFS</th>
 * <td>`out/amba_out/<board_name>/images/rootfs.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/rootfs.bin`</td>
 * <td>Rootfs partition binary</td>
 * </tr>
 * </table>
 *
 * @par For Legacy Firmware Layout:
 * <table>
 * <caption id="si_legacy_fw_table">Table 3-8. Images for Image Upgrade.</caption>
 * <tr>
 * <th rowspan="2" align="center">Image Type</th>
 * <th colspan="2" align="center">Cooper SDK</th>
 * <th colspan="1" align="center">CV2x SDK 3.0</th>
 * <th rowspan="2" align="center">Description</th>
 * </tr>
 * <tr>
 * <th align="center">Amba Build</th>
 * <th align="center">Yocto Build</th>
 * <th align="center">Amba Build</th>
 * </tr>
 * <tr>
 * <th align="center">BST</th>
 * <td>`out/amba_out/<board_name>/images/bst.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/bst.bin`</td>
 * <td>`out/<board_name>/amboot/bst_release.bin`</td>
 * <td>BST partition image</td>
 * <tr>
 * <th align="center">BLD</th>
 * <td>`out/amba_out/<board_name>/images/bld.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/bld.bin`</td>
 * <td>`out/<board_name>/amboot/bld_release.bin`</td>
 * <td>BLD partition binary for normal boot</td>
 * </tr>
 * <tr>
 * <th align="center">ATF</th>
 * <td>`out/amba_out/<board_name>/images/atf.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/atf.bin`</td>
 * <td>`out/<board_name>/amboot/atf_release.bin`</td>
 * <td>ATF partition binary for secure boot</td>
 * </tr>
 * <tr>
 * <th align="center">FIP</th>
 * <td>`out/amba_out/<board_name>/images/fip.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/fip.bin`</td>
 * <td>`out/<board_name>/amboot/fip_release.bin`</td>
 * <td>BLD partition binary for secure boot</td>
 * </tr>
 * <tr>
 * <th align="center">DTB</th>
 * <td>`out/amba_out/<board_name>/images/dtb.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/dtb.bin`</td>
 * <td>`out/<board_name>/amboot/<board_name>.dtb`</td>
 * <td>DTS binary stored in PTB partition</td>
 * </tr>
 * <tr>
 * <th align="center">KERNEL</th>
 * <td>`out/amba_out/<board_name>/images/kernel.bin` or `Image.SIGNED (secure boot)`</td>
 * <td>`out/yocto_out/<board_name>/images/kernel.bin` or `Image.SIGNED (secure boot)`</td>
 * <td>`out/<board_name>/kernel/Image` or `Image.SIGNED (secure boot)`</td>
 * <td>PRI partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">PBA</th>
 * <td>`out/amba_out/<board_name>/images/pba.bin` or `Image.SIGNED (secure boot)`</td>
 * <td></td>
 * <td>`out/<board_name>/kernel/pba_zImage` or `pba_zImage.SIGNED (secure boot)`</td>
 * <td>PBA partition binary</td>
 * </tr>
 * <tr>
 * <th align="center">ROOTFS</th>
 * <td>`out/amba_out/<board_name>/images/rootfs.bin`</td>
 * <td>`out/yocto_out/<board_name>/images/rootfs.bin`</td>
 * <td>`out/<board_name>/rootfs/ubifs` (Take UBIFS as an example)</td>
 * <td>LNX partition binary</td>
 * </tr>
 * </table>
 * @note
 *   For secure boot, the DTB binary together with `bld.bin` is packed into the
 *   `fip.bin`, the DTB binary stored in DTB or PTB partition takes no effect
 *   unless `CONFIG_RELOAD_UNTRUSTED_DTB` is selected in menuconfig.
 *
 *@subsubsection si_image_upgrade_tool 3.4.3 The Upgrade Tool
 * To perform the upgrade operation, the Ambarella SDK provides a tool named
 * `upgrade_partition` for the user. The user can use this tool in both upgrade
 * modes. <br>
 * The user can select this tool in menuconfig:
 * - For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build $ make menuconfig
 *   Ambarella Application Configuration ->
 *     Build Utilities ->
 *       [*] Build Ambarella upgrade partition
 * @endcode
 * - For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 *   app --->
 *     utility --->
 *       upgrade_partition --->
 *         [*] upgrade-partition (app/utility/upgrade_partition/app)
 * @endcode
 * - For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 *   meta-ambaapp --->
 *     recipes-upgrade-partition --->
 *       [*] upgrade-partition (meta-ambaapp/recipes-upgrade-partition/upgrade-partition)
 * @endcode
 * The user can type the `upgrade_partition` in console to get the usages or
 * refer to the upgrade examples @ref si_ab_flex_upgrade and @ref si_ab_legacy_upgrade
 * @code
 * board# upgrade_partition
 * Usage:upgrade_partition [OPTION] MTD_DEVICE INPUTFILE
 * Writes to the specified MTD device.
 * ......
 * @endcode
 *
 * <B>Here are some examples for upgrade_partition.</b><br>
 * - For flexible firmware layout:
 *   + Upgrade boot arguments.
 *     @code
 *     // Assume NAND is used. "mtd3" is the ENV partition.
 *     board# upgrade_partition -e /dev/mtd3 -C "console=ttyS0 ubi.mtd=rootfs root=ubi0:rootfs rw rootfstype=ubifs earlycon pci=nomsi"
 *     @endcode
 *     @note
 *       - For flexible firmware layout, the user must update the `bootargs` with
 *         cautions:
 *         + The `upgrade_partition` tool can change the "bootargs" stored in
 *           ENV partition, it can't change the "bootargs" stored in DTB partition.
 *         + If the "bootargs" in ENV partition is not NULL, this "bootargs" will
 *           replace the one in memory loaded from DTB during the amboot stage.
 *         + If the "bootargs" in ENV partition is NULL, AMboot will use the
 *           "bootargs" stored in DTB partition.
 *       - If the user really wants to change the "bootargs" stored in DTB
 *         partition, the only way is to change it in amboot.
 *         @code
 *         amboot# fdt cmdline console=ttyS0 ubi.mtd=rootfs root=ubi0:rootfs rw rootfstype=ubifs earlycon pci=nomsi
 *         @endcode
 *       - The user can also change the "bootargs" stored in ENV partition through
 *         the AMBoot shell.
 *         @code
 *         amboot# setenv cmdline console=ttyS0 ubi.mtd=rootfs root=ubi0:rootfs rw rootfstype=ubifs earlycon pci=nomsi
 *         @endcode
 *       - If the "bootargs" stored in DTB partition is back to use, the user must
 *         clear the "bootargs" stored in ENV partition.
 *         @code
 *         board# upgrade_partition -e /dev/mtd3 -C ""
 *         // or in AMBoot shell
 *         amboot# setenv cmdline
 *         @endcode
 *
 *   + Upgrade `dtb2` partition and switch to it.
 *     @code
 *     // Assume NAND is used. "mtd3" and "mtd5" are ENV and dtb2 partition.
 *     board# flash_erase /dev/mtd5 0 0
 *     board# upgrade_partition -p /dev/mtd5 /sdcard/upgrade/dtb.img
 *     board# upgrade_partition -e /dev/mtd3 -n -P dtb2
 *     @endcode
 *   + Upgrade `kernel2` partition and switch to it.
 *     @code
 *     // Assume EMMC is used. "mmcblk0p4" and "mmcblk0p5" are ENV and kernel2 partition.
 *     board# upgrade_partition -p /dev/mmcblk0p5 /sdcard/upgrade/kernel.img
 *     board# upgrade_partition -e /dev/mmcblk0p4 -k -P kernel2
 *     @endcode
 *
 * - For legacy firmware layout:
 *   + Upgrade DTB and update boot arguments in DTB.
 *     @code
 *     // Assume NAND is used.
 *     board# upgrade_partition -d /sdcard/upgrade/<board_name>.dtb
 *     board# upgrade_partition -C "console=ttyS0 ubi.mtd=rootfs root=ubi0:rootfs rw rootfstype=ubifs earlycon pci=nomsi"
 *     @endcode
 *   + Upgrade `pba` partition (kernel) and switch to it.
 *     @code
 *     // Assume NAND is used. "mtd4" is the pba partition.
 *     board# flash_erase /dev/mtd4 0 0
 *     board# upgrade_partition -p -Q /dev/mtd4 /sdcard/upgrade/Image
 *     board# upgrade_partition -S 2
 *     @endcode
 *
 * @note
 *   It is better to switch to a second rootfs / system to update the first
 *   rootfs / system, or it may cause a system crash.
 *
 * @subsubsection si_image_upgrade_signature 3.4.4 Digital Signature (Optional)
 * For the sake of safety, the digital signature check can be added into the
 * image updating flow to ensure that only the correct and untampered firmware
 * can be flashed to the board. The Ambrella SDK provides a digital signature
 * tool and related APIs to do this. The security package is located at:<br>
 * For CV2x SDK 3.0: `ambarella/packages/security`<br>
 * For Cooper SDK: `ambarella/security`
 *
 * - @par Digital Signature Tool
 *   This tool can generate key pairs, sign the firmwares, and verify signatures
 *   in the host Linux PC. The user can build this using the following command:
 *   @code
 *   build$ cd security/
 *   build$ make
 *   build$ cd key_tools/pkey_tool_native/
 *   build$ make
 *   @endcode
 *   The tool `key_tool_ed25519` will be generated under `key_tools/pkey_tool_native/`.
 *   @code
 *   // Generate the private and public keys, e.g. pri_ed25519.bin and pub_ed25519.bin
 *   build$ ./key_tool_ed25519 --genkey ed25519
 *   // Generate the signature using the private key
 *   build$ ./key_tool_ed25519 --sign xxx_image.bin pri_ed25519.bin xxx_image.bin.signature
 *   // Verify the signature using the public key
 *   build$ ./key_tool_ed25519 --verify xxx_image.bin pub_ed25519.bin xxx_image.bin.signature
 *   verify pass
 *   @endcode
 *   The user can write the public key into the security OTP for succeeding
 *   signature verifications during firmware upgrading stage. The user must keep
 *   the generated private key in safe in order to sign the firmwares to be used
 *   in the subsequent upgrade operation. The used private and public keys must
 *   be a pair, which are generated together.
 *
 * - @par Key Verification
 *   The key verification APIs reside at `security/lw_cryptography/include/curve25519.h`.
 *   The user can read the public key from the OTP and call these APIs to verify the
 *   firmware signature in the upgrade application. The user can refer to the
 *   examples under `security/lw_cryptography/unit_test` on how to use these APIs.
 *
 * - @par The Digital Signature Check Flow:
 *   @image html image_upgrading_digital_signature_check.png "Figure 3-4. Digital Signature Check for Image Updating."
 *
 * @subsubsection si_ab_flex_upgrade 3.4.5 AB Upgrade Example for Flexible Firmware Layout
 * For flexible firmware layout, two DTB partitions are used to do the switch
 * between the system A and the system B.<br>
 * Take CV72_gage as an example, perform the following steps to setup AB upgrade
 * for flexible firmware layout:
 * 1. Allocate the "dtb2", "kernel2" and "rootfs2" partition size.
 * @code
 * vim ambarella/boards/cv72_gage/bsp/bsp.h
 * #define AMBOOT_PARTITION_LAYOUT \
 *               MEDIA_DEV \
 *               "128k(bst),1024k(bld),1024k(dtb),896k(dtb2),896k(env),128k(cfg)," \
 *               "16m@0x600000(kernel),16m(kernel2),108m(rootfs),108m(rootfs2),-(raw)"
 * @endcode
 * @note
 *   - The generated root file system (rootfs) size may be larger than the partition size, the user
 *     can remove some unwanted configurations in menuconfig.
 *   - Ensure that the total size (6M(kernel offset) + 16M * 2 + 108M * 2 = 254M) is
 *     smaller than the NAND flash total size.
 *   - The space (6M) before the kernel is big enough for the bst, bld, dtb,
 *     dtb2, env and cfg in this example.
 *   - The partition allocation above is not suitable for embedded multi-media controller (eMMC). When eMMC is used,
 *     the user must allocate the partition according to the actual need,
 *     especially for the rootfs size.
 *
 * 2. Create a `.dts` file and change the `bootargs` for the system B.
 * @code
 * build$ cp -rf ambarella/boards/cv72_gage/bsp/cv72_gage.dts ambarella/boards/cv72_gage/bsp/cv72_gage_ab_upgrade.dts
 * // change the command line for system B
 * build$ vim ambarella/boards/cv72_gage/bsp/cv72_gage_ab_upgrade.dts
 * bootargs = "console=ttyS0 ubi.mtd=rootfs2 root=ubi0:rootfs rw rootfstype=ubifs earlycon pci=nomsi";
 * @endcode
 * @note
 *   When eMMC is used, the bootargs for system A and system B appear as follows if
 *   the partition layout in step 1 is used. For "root=/dev/mmcblk0pX", the `X`
 *   is the sequence number of the partitions counting from 1(bst).
 *   @code
 *   // For system A
 *   bootargs = "console=ttyS0 noinitrd root=/dev/mmcblk0p9 rw rootfstype=ext4 rootwait pci=nomsi pcie_aspm=off";
 *   // For system B
 *   bootargs = "console=ttyS0 noinitrd root=/dev/mmcblk0p10 rw rootfstype=ext4 rootwait pci=nomsi pcie_aspm=off";
 *   @endcode
 *
 *
 * 3. Create a Makefile to build the `dtb2.bin` using the DTS file in step 2.
 * @code
 * build$ vim ambarella/boards/cv72_gage/bsp/upgrade_dtb2.mk
 * CC  := $(ENV_BUILD_TOOL)gcc
 * DTC := dtc
 *
 * DTC_OPTIONS := -I dts -H epapr -q
 * DTC_OPTIONS += -i $(KERNEL_SRC)/arch/arm64/boot/dts/ambarella
 *
 * DTC_CFLAGS  := -E -nostdinc -D__DTS__ -U linux -x assembler-with-cpp
 * DTC_CFLAGS  += -I . -I $(KERNEL_SRC)/include -I$(ENV_CFG_ROOT)
 * DTC_CFLAGS  += -I$(KERNEL_SRC)/arch/arm64/boot/dts/ambarella
 *
 * ifeq ($(CONFIG_BACKUP_CPIO), y)
 * DTS_FILE := $(BSP_DIR)/cv72_gage_pba_upgrade.dts
 * else
 * DTS_FILE := $(BSP_DIR)/cv72_gage_ab_upgrade.dts
 * endif
 *
 * dtb2.bin: $(DTS_FILE)
 * 	@$(CC) $(DTC_CFLAGS) $< | $(DTC) $(DTC_OPTIONS) -S 0x10000 -O dtb -o $@
 *
 * .FORCE:
 *
 * @endcode
 *
 * 4. Create a profile for the firmware to be generated.
 * @code
 * build$ vim bsp/profile.ab_upgrade
 * IMAGE_FWPROG    := $(BIN_DIR)/fwp.bin
 *
 * IMAGE_0_NAME    := bst
 * IMAGE_0_FILE    := $(BIN_DIR)/bst.bin
 * IMAGE_0_ADDR    := -1
 * IMAGE_0_FLAG    := force raw
 *
 * IMAGE_1_NAME    := bld
 * IMAGE_1_FILE    := $(BIN_DIR)/bld.bin
 * IMAGE_1_ADDR    := -1
 * IMAGE_1_FLAG    := force raw
 *
 * IMAGE_2_NAME    := env
 * IMAGE_2_FILE    := $(BIN_DIR)/env.bin
 * IMAGE_2_ADDR    := -1
 * IMAGE_2_FLAG    := force
 *
 * IMAGE_3_NAME    := dtb
 * IMAGE_3_FILE    := $(BIN_DIR)/dtb.bin
 * IMAGE_3_ADDR    := -1
 * IMAGE_3_FLAG    := force
 *
 * IMAGE_4_NAME    := dtb2
 * IMAGE_4_FILE    := dtb2.bin
 * IMAGE_4_ADDR    := -1
 * IMAGE_4_FLAG    := force
 *
 * IMAGE_5_NAME    := kernel
 * IMAGE_5_FILE    := $(BIN_DIR)/kernel.bin
 * IMAGE_5_ADDR    := $(KERNEL_RAM_START)
 * IMAGE_5_FLAG    := verify compressed
 *
 * IMAGE_6_NAME    := kernel2
 * IMAGE_6_FILE    := $(BIN_DIR)/kernel.bin
 * IMAGE_6_ADDR    := $(KERNEL_RAM_START)
 * IMAGE_6_FLAG    := verify compressed
 *
 * IMAGE_7_NAME    := rootfs
 * IMAGE_7_FILE    := $(BIN_DIR)/rootfs.bin
 * IMAGE_7_ADDR    := -1
 * IMAGE_7_FLAG    := raw
 *
 * IMAGE_8_NAME    := rootfs2
 * IMAGE_8_FILE    := $(BIN_DIR)/rootfs.bin
 * IMAGE_8_ADDR    := -1
 * IMAGE_8_FLAG    := raw
 *
 * include $(BSP_DIR)/upgrade_dtb2.mk
 *
 * @endcode
 * @note
 *   It is better to keep the flags the same for doubled partitions in the
 *   profile above.
 *
 * 5. Create a new `.env` file for partition if needed, or use the default one
 * located at `boot/amboot/src/bld/default.env`.<br>
 * This file can determine which dtb, kernel, and rootfs partions are used for
 * booting up the EVK board.
 * @code
 * build$ vim ambarella/boards/cv72_gage/bsp/cv72_gage.env
 * /dts-v1/;
 *
 * #include "config.h"
 *
 * / {
 *     compatible = "ambarella,environment";
 *     #address-cells = <1>;
 *     #size-cells = <1>;
 *
 * #if defined(AMBOOT_DEV_AUTO_BOOT)
 *     auto_boot;
 * #endif
 *     serial_num = AMBOOT_DEFAULT_SN;
 *
 *     bootcmd = "";
 *
 *     bootargs = "";
 *
 *     kernel_meta {
 *         partition = "kernel";
 *         binary_id = <0>;
 *     };
 *
 *     dtb_meta {
 *         partition = "dtb";
 *         binary_id = <0>;
 *     };
 *
 *     rootfs_meta {
 *         partition = "rootfs";
 *         binary_id = <0>;
 *     };
 *
 *     netdev_eth0 {
 *         mac = "00:00:00:00:00:00";
 *         mask = "0.0.0.0";
 *         gw = "0.0.0.0";
 *         ip = "0.0.0.0";
 *     };
 *
 *     tftpd {
 *         server,ip = "0.0.0.0";
 *         kernel,file = "";
 *         kernel,addr = <0x00000000>;
 *         ramdisk,file = "";
 *         ramdisk,addr = <0x00000000>;
 *     };
 * };
 * @endcode
 *
 * 6. Configure the AB system in menuconfig.
 * @par For Cooper Amba Build:
 * @code
 * build$ make ipcam_lp5_config
 * build$ make menuconfig
 * boot  --->
 *   [*] ambfw (boot/ambamk)  --->
 *     AMBFW Configuration  --->
 *       [*] Build AMBFW
 *       (profile.ab_upgrade) Firmware Profile
 *   [*] amboot (boot/ambamk)  --->
 *     Ambarella Bootloader Configuration  --->
 *       Firmware Options  --->
 *         Firmware Layout Style (Flexible Firmware Layout)  --->
 *           (X) Flexible Firmware Layout
 *       // If secure boot is used, "Reload DTB" should be selected.
 *       AMBoot Options  --->
 *         [*] Boot with TrustZone  --->
 *           [*]   Secure DTB with Signature (SOC Firmware Config)
 *             [*]     Reload DTB in PTB partiton
 * app  --->
 *   utility  --->
 *     upgrade_partition  --->
 *       [*] upgrade-partition (app/utility/upgrade_partition/app)
 *       -*- libfdt (app/utility/upgrade_partition/libfdt)
 * rootfs  --->
 *   [ ] backup-cpio (rootfs/backup-cpio)  ----  // unselect
 * // For NAND flash, add the mtd utils
 * prebuild  --->
 *   oss  --->
 *     [*] prebuild-mtd-utils (prebuild/oss/armv8-a/mtd-utils)
 * @endcode
 *
 * @par For Cooper Yocto Build:
 * @code
 * build$ make ipcam_lp5_config
 * build$ make menuconfig
 * meta-ambabsp  --->
 *   recipes-bsp  --->
 *     [*] ambfw (meta-ambabsp/recipes-bsp/boot)  --->
 *       AMBFW Configuration  --->
 *         [*] Build AMBFW
 *         (profile.ab_upgrade) Firmware Profile
 *     [*] amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *       Ambarella Bootloader Configuration  --->
 *         Firmware Options  --->
 *           Firmware Layout Style (Flexible Firmware Layout)  --->
 *             (X) Flexible Firmware Layout
 *         // If secure boot is used, "Reload DTB" should be selected.
 *         AMBoot Options  --->
 *           [*] Boot with TrustZone  --->
 *             [*]   Secure DTB with Signature (SOC Firmware Config)
 *               [*]     Reload DTB in PTB partiton
 * meta-ambaapp  --->
 *   recipes-upgrade-partition  --->
 *     [*] upgrade-partition (meta-ambaapp/recipes-upgrade-partition/upgrade-partition)
 * meta-ambalib  --->
 *   recipes-upgrade-partition  --->
 *     [*] libfdt (meta-ambalib/recipes-upgrade-partition/libfdt)
 * // For NAND flash, add the mtd utils
 * meta  --->
 *   recipes-devtools  --->
 *     [*] mtd-utils (meta/recipes-devtools/mtd)
 * @endcode
 *
 * 7. Build the firmware and program it to the EVK board.
 * @code
 * build$ make
 * @endcode
 * The generated firmware: `ambarella/out/amba_out/cv72_gage/bst_bld_env_dtb_dtb2_kernel_kernel2_rootfs_rootfs2.elf`<br>
 * @code
 * ------ Report ------
 * bst:    success
 * bld:    success
 * env:    success
 * dtb:    success
 * dtb2:   success
 * kernel: success
 * kernel2:    success
 * rootfs: success
 * rootfs2:    success
 * @endcode
 *
 * 8. Prepare the images for AB upgrade used by the `upgrade_partition` tool.<br>
 * For the images to be used, the user can refer to @ref si_images_for_upgrading
 * and copy them to a SD card, such as under a `upgrade` folder.
 *
 * 9. Get the allocated partitions.
 *   - For NAND:
 *     @code
 *     board# cat /proc/mtd
 *     dev:    size   erasesize  name
 *     mtd0: 00020000 00020000 "bst"
 *     mtd1: 00100000 00020000 "bld"
 *     mtd2: 00100000 00020000 "dtb"
 *     mtd3: 000e0000 00020000 "dtb2"
 *     mtd4: 000e0000 00020000 "env"
 *     mtd5: 00020000 00020000 "cfg"
 *     mtd6: 01000000 00020000 "kernel"
 *     mtd7: 01000000 00020000 "kernel2"
 *     mtd8: 06c00000 00020000 "rootfs"
 *     mtd9: 06c00000 00020000 "rootfs2"
 *     mtd10: 00180000 00020000 "raw"
 *     @endcode
 *   - For eMMC:<br>
 *     Here is not an eMMC partition allocation example for AB upgrade, just for
 *     showing the eMMC partitions.
 *     @code
 *     board# cat /proc/partitions
 *     major minor  #blocks  name
 *
 *        1        0      65536 ram0
 *       31        0     262144 mtdblock0
 *      179        0   31080448 mmcblk0
 *      179        1        128 mmcblk0p1
 *      179        2       1024 mmcblk0p2
 *      179        3        896 mmcblk0p3
 *      179        4        896 mmcblk0p4
 *      179        5      65536 mmcblk0p5
 *      179        6     524288 mmcblk0p6
 *      179        7   30471168 mmcblk0p7
 *     @endcode
 *     The partition name can be obtained from device-tree information.
 *     @code
 *     board# cat /proc/device-tree/sdmmc0@fff2000000/partitions/partition@1/label
 *     @endcode
 *
 * 10. Insert the SD card and upgrade the system B partitions's image.<br>
 * Assume the SD card will be auto-mounted to `/sdcard/mmcblk1p1/`.
 * @code
 * For NAND:
 * // upgrade bld
 * board# flash_erase /dev/mtd1 0 0
 * board# upgrade_partition -p /dev/mtd1 /sdcard/mmcblk1p1/upgrade/bld.bin
 * // upgrade dtb2
 * board# flash_erase /dev/mtd3 0 0
 * board# upgrade_partition -p /dev/mtd3 /sdcard/mmcblk1p1/upgrade/dtb.img
 * // upgrade kernel2
 * board# flash_erase /dev/mtd7 0 0
 * board# upgrade_partition -p /dev/mtd7 /sdcard/mmcblk1p1/upgrade/kernel.img
 * // upgrade rootfs2
 * board# flash_erase /dev/mtd9 0 0
 * board# upgrade_partition -p /dev/mtd9 /sdcard/mmcblk1p1/upgrade/rootfs.bin
 *
 * For eMMC:
 * // upgrade kernel2
 * board# upgrade_partition -p /dev/mmcblk0p8 /sdcard/mmcblk1p1/upgrade/kernel.img
 * // upgrade rootfs2
 * board# upgrade_partition -p /dev/mmcblk0p10 /sdcard/mmcblk1p1/upgrade/rootfs.bin
 *
 * board# sync
 * @endcode
 * @note
 *   - If eMMC is used, the user can clean the data first and then upgrade the
 *     partition image.
 *     @code
 *     board# dd if=/dev/zero of=/dev/mmcblk0pX
 *     @endcode
 *   - If eMMC boot partition is used as BST partition, the user must get the
 *     written permission first and then upgrade it.
 *     @code
 *     board# echo 0 > /sys/block/mmcblk0boot0/force_ro
 *     board# upgrade_partition -p /dev/mmcblk0boot0 /sdcard/upgrade/bst.bin
 *     @endcode
 *
 * 11. Switch to system B.
 * @code
 * // "/dev/mtd4" is the ENV partition.
 * board# upgrade_partition -e /dev/mtd4 -r -P rootfs2
 * board# upgrade_partition -e /dev/mtd4 -k -P kernel2
 * board# upgrade_partition -e /dev/mtd4 -n -P dtb2
 *
 * // If EMMC is used, "/dev/mmcblk0p5" is the ENV partition.
 * board# upgrade_partition -e /dev/mmcblk0p5 -r -P rootfs2
 * board# upgrade_partition -e /dev/mmcblk0p5 -k -P kernel2
 * board# upgrade_partition -e /dev/mmcblk0p5 -n -P dtb2
 *
 * board# sync && reboot
 * @endcode
 * @note
 *   For debugging purpose, the user can switch to system B in AMBoot.
 *   @code
 *   amboot# setenv bootmeta rootfs rootfs2
 *   amboot# setenv bootmeta kernel kernel2
 *   amboot# setenv bootmeta dtb dtb2
 *   amboot# reboot
 *   @endcode
 *
 * @subsubsection si_pba_flex_upgrade 3.4.6 PBA Upgrade Example for Flexible Firmware Layout
 * PBA upgrade is only supported by the Amba build. For flexible firmware layout,
 * two DTB partitions are used to do the switch between the main system and the
 * PBA system.<br>
 * Take CV72_gage as an example, perform the following steps to setup PBA
 * upgrade for flexible firmware layout:
 * 1. Allocate the "pba" and "dtb2" partition size.
 * @code
 * build$ vim ambarella/boards/cv72_gage/bsp/bsp.h
 * #define AMBOOT_PARTITION_LAYOUT \
 *               MEDIA_DEV \
 *               "128k(bst),1024k(bld),1024k(dtb),896k(dtb2),896k(env),128k(cfg)," \
 *               "32m@0x600000(kernel),176m(rootfs),20m(pba),-(raw)"
 * @endcode
 * @note
 *   - Ensure that the total size (6M(kernel offset) + 32M + 176M + 32M = 246M) is
 *     smaller than the NAND flash total size.
 *   - The space (6M) before the kernel is big enough for the bst, bld, dtb,
 *     dtb2, env and cfg in this example.
 *   - The partition allocation above is not suitable for eMMC. When eMMC is used,
 *     the user must allocate the partition according to the actual need,
 *     especially for the rootfs size.
 *
 * 2. Create a `.dts` file and change the `bootargs` for the PBA system.
 * @code
 * build$ cp -rf ambarella/boards/cv72_gage/bsp/cv72_gage.dts ambarella/boards/cv72_gage/bsp/cv72_gage_pba_upgrade.dts
 * // change the command line for PBA system
 * build$ vim ambarella/boards/cv72_gage/bsp/cv72_gage_pba_upgrade.dts
 * bootargs = "console=ttyS0 rootfs=ramfs root=/dev/ram rw rdinit=/linuxrc earlycon pci=nomsi";
 * @endcode
 * @note
 *   When eMMC is used, the boot arguments for the main system and PBA system appear as follows
 *   if the partition layout in step 1 is used. For "root=/dev/mmcblk0pX",
 *   the `X` is the sequence number of the partitions counting from 1(bst).
 *   @code
 *   // For main system
 *   bootargs = "console=ttyS0 noinitrd root=/dev/mmcblk0p8 rw rootfstype=ext4 rootwait pci=nomsi pcie_aspm=off";
 *   // For PBA system
 *   bootargs = "console=ttyS0 rootfs=ramfs root=/dev/ram rw rdinit=/linuxrc earlycon pci=nomsi pcie_aspm=off";
 *   @endcode
 *
 * 3. Create a Makefile to build the `dtb2.bin` using the DTS file in step 2.
 * @code
 * build$ vim ambarella/boards/cv72_gage/bsp/upgrade_dtb2.mk
 * CC  := $(ENV_BUILD_TOOL)gcc
 * DTC := dtc
 *
 * DTC_OPTIONS := -I dts -H epapr -q
 * DTC_OPTIONS += -i $(KERNEL_SRC)/arch/arm64/boot/dts/ambarella
 *
 * DTC_CFLAGS  := -E -nostdinc -D__DTS__ -U linux -x assembler-with-cpp
 * DTC_CFLAGS  += -I . -I $(KERNEL_SRC)/include -I$(ENV_CFG_ROOT)
 * DTC_CFLAGS  += -I$(KERNEL_SRC)/arch/arm64/boot/dts/ambarella
 *
 * ifeq ($(CONFIG_BACKUP_CPIO), y)
 * DTS_FILE := $(BSP_DIR)/cv72_gage_pba_upgrade.dts
 * else
 * DTS_FILE := $(BSP_DIR)/cv72_gage_ab_upgrade.dts
 * endif
 *
 * dtb2.bin: $(DTS_FILE)
 * 	@$(CC) $(DTC_CFLAGS) $< | $(DTC) $(DTC_OPTIONS) -S 0x10000 -O dtb -o $@
 *
 * .FORCE:
 *
 * @endcode
 * @note
 *   The leading indentation before @ must be generated by "tab" key.
 *
 * 4. Create a profile for the firmware to be generated.
 * @code
 * build$ vim bsp/profile.pba_upgrade
 * IMAGE_FWPROG    := $(BIN_DIR)/fwp.bin
 *
 * IMAGE_0_NAME    := bst
 * IMAGE_0_FILE    := $(BIN_DIR)/bst.bin
 * IMAGE_0_ADDR    := -1
 * IMAGE_0_FLAG    := force raw
 *
 * IMAGE_1_NAME    := bld
 * IMAGE_1_FILE    := $(BIN_DIR)/bld.bin
 * IMAGE_1_ADDR    := -1
 * IMAGE_1_FLAG    := force raw
 *
 * IMAGE_2_NAME    := env
 * IMAGE_2_FILE    := $(BIN_DIR)/env.bin
 * IMAGE_2_ADDR    := -1
 * IMAGE_2_FLAG    := force
 *
 * IMAGE_3_NAME    := dtb
 * IMAGE_3_FILE    := $(BIN_DIR)/dtb.bin
 * IMAGE_3_ADDR    := -1
 * IMAGE_3_FLAG    := force
 *
 * IMAGE_4_NAME    := dtb2
 * IMAGE_4_FILE    := dtb2.bin
 * IMAGE_4_ADDR    := -1
 * IMAGE_4_FLAG    := force
 *
 * IMAGE_5_NAME    := kernel
 * IMAGE_5_FILE    := $(BIN_DIR)/kernel.bin
 * IMAGE_5_ADDR    := $(KERNEL_RAM_START)
 * IMAGE_5_FLAG    := verify compressed
 *
 * IMAGE_6_NAME    := pba
 * IMAGE_6_FILE    := $(BIN_DIR)/pba.bin
 * IMAGE_6_ADDR    := $(KERNEL_RAM_START)
 * IMAGE_6_FLAG    := verify
 *
 * IMAGE_7_NAME    := rootfs
 * IMAGE_7_FILE    := $(BIN_DIR)/rootfs.bin
 * IMAGE_7_ADDR    := -1
 * IMAGE_7_FLAG    := raw
 *
 * include $(BSP_DIR)/upgrade_dtb2.mk
 *
 * @endcode
 *
 * 5. Create a new `.env` file for partition if needed, or use the default one
 * located at `boot/amboot/src/bld/default.env`.<br>
 * This file can determine which DTB, kernel and rootfs partions are used for
 * booting up the EVK board.
 * @code
 * build$ vim ambarella/boards/cv72_gage/bsp/cv72_gage.env
 * /dts-v1/;
 *
 * #include "config.h"
 *
 * / {
 *     compatible = "ambarella,environment";
 *     #address-cells = <1>;
 *     #size-cells = <1>;
 *
 * #if defined(AMBOOT_DEV_AUTO_BOOT)
 *     auto_boot;
 * #endif
 *     serial_num = AMBOOT_DEFAULT_SN;
 *
 *     bootcmd = "";
 *
 *     bootargs = "";
 *
 *     kernel_meta {
 *         partition = "kernel";
 *         binary_id = <0>;
 *     };
 *
 *     dtb_meta {
 *         partition = "dtb";
 *         binary_id = <0>;
 *     };
 *
 *     rootfs_meta {
 *         partition = "rootfs";
 *         binary_id = <0>;
 *     };
 *
 *     netdev_eth0 {
 *         mac = "00:00:00:00:00:00";
 *         mask = "0.0.0.0";
 *         gw = "0.0.0.0";
 *         ip = "0.0.0.0";
 *     };
 *
 *     tftpd {
 *         server,ip = "0.0.0.0";
 *         kernel,file = "";
 *         kernel,addr = <0x00000000>;
 *         ramdisk,file = "";
 *         ramdisk,addr = <0x00000000>;
 *     };
 * };
 * @endcode
 *
 * 6. Enable PBA function in menuconfig.
 * @code
 * build$ make ipcam_lp5_config
 * build$ make menuconfig
 * boot  --->
 *   [*] ambfw (boot/ambamk)  --->
 *     AMBFW Configuration  --->
 *       [*] Build AMBFW
 *       (profile.pba_upgrade) Firmware Profile
 *   [*] amboot (boot/ambamk)  --->
 *     Ambarella Bootloader Configuration  --->
 *       Firmware Options  --->
 *         Firmware Layout Style (Flexible Firmware Layout)  --->
 *           (X) Flexible Firmware Layout
 * // If secure is used, "Reload DTB" should be selected.
 *       AMBoot Options  --->
 *         [*] Boot with TrustZone  --->
 *           [*]   Secure DTB with Signature (SOC Firmware Config)
 *             [*]     Reload DTB in PTB partiton
 * app  --->
 *   utility  --->
 *     upgrade_partition  --->
 *       [*] upgrade-partition (app/utility/upgrade_partition/app)
 *       -*- libfdt (app/utility/upgrade_partition/libfdt)
 * rootfs  --->
 *   [*] backup-cpio (rootfs/backup-cpio)  --->
 *     [*]   pba system support sdcard
 * // For NAND flash, add the mtd utils
 * prebuild  --->
 *   oss  --->
 *     [*] prebuild-mtd-utils (prebuild/oss/armv8-a/mtd-utils)
 * @endcode
 *
 * 7. Build the firmware and program it to the EVK board.
 * @code
 * build$ make
 * @endcode
 * The generated firmware: `ambarella/out/amba_out/cv72_gage/bst_bld_env_dtb_dtb2_kernel_pba_rootfs.elf`<br>
 * @code
 * ------ Report ------
 * bst:    success
 * bld:    success
 * env:    success
 * dtb:    success
 * dtb2:   success
 * kernel: success
 * pba:    success
 * rootfs: success
 * @endcode
 *
 * 8. Prepare the images for PBA upgrade used by the `upgrade_partition` tool.<br>
 * For the images to be used, the user can refer to @ref si_images_for_upgrading
 * and copy them to a SD card, such as under a `upgrade` folder.
 *
 * 9. Enter PBA.
 * @code
 * // "/dev/mtd4" is the ENV partition.
 * board# upgrade_partition -e /dev/mtd4 -k -P pba
 * board# upgrade_partition -e /dev/mtd4 -n -P dtb2
 *
 * // If EMMC is used.
 * board# upgrade_partition -e /dev/mmcblk0p4 -k -P pba
 * board# upgrade_partition -e /dev/mmcblk0p4 -n -P dtb2
 *
 * board# sync && reboot
 * @endcode
 * @note
 *   For debugging purpose, the user can switch to PBA system in AMBoot.
 *   @code
 *   amboot# setenv bootmeta kernel pba
 *   amboot# setenv bootmeta dtb dtb2
 *   amboot# reboot
 *   @endcode
 *
 * 10. Get the allocated partitions.
 *   - For NAND:
 *     @code
 *     board# cat /proc/mtd
 *     dev:    size   erasesize  name
 *     mtd0: 00020000 00020000 "bst"
 *     mtd1: 00100000 00020000 "bld"
 *     mtd2: 00100000 00020000 "dtb"
 *     mtd3: 000e0000 00020000 "dtb2"
 *     mtd4: 000e0000 00020000 "env"
 *     mtd5: 00020000 00020000 "cfg"
 *     mtd6: 02000000 00020000 "kernel"
 *     mtd7: 0ac00000 00020000 "rootfs"
 *     mtd8: 01400000 00020000 "pba"
 *     mtd9: 00c80000 00020000 "raw"
 *     @endcode
 *   - For eMMC:<br>
 *     Here is not a partition allocation example for PBA upgrade, just for
 *     showing the eMMC partitions.
 *     @code
 *     board# cat /proc/partitions
 *     major minor  #blocks  name
 *
 *        1        0      65536 ram0
 *       31        0     262144 mtdblock0
 *      179        0   31080448 mmcblk0
 *      179        1        128 mmcblk0p1
 *      179        2       1024 mmcblk0p2
 *      179        3        896 mmcblk0p3
 *      179        4        896 mmcblk0p4
 *      179        5      65536 mmcblk0p5
 *      179        6     524288 mmcblk0p6
 *      179        7   30471168 mmcblk0p7
 *     @endcode
 *     The partition name can be obtained from device-tree information.
 *     @code
 *     board# cat /proc/device-tree/sdmmc0@fff2000000/partitions/partition@1/label
 *     @endcode
 *
 * 11. Insert the SD card and upgrade the main system partitions' image.
 * @code
 * board# mkdir /sdcard
 * board# mount -t vfat /dev/mmcblk1p1 /sdcard
 * For NAND:
 * // upgrade bld
 * board# flash_erase /dev/mtd1 0 0
 * board# upgrade_partition -p /dev/mtd1 /sdcard/upgrade/bld.bin
 * // upgrade dtb
 * board# flash_erase /dev/mtd2 0 0
 * board# upgrade_partition -p /dev/mtd2 /sdcard/upgrade/dtb.img
 * // upgrade kernel
 * board# flash_erase /dev/mtd6 0 0
 * board# upgrade_partition -p /dev/mtd6 /sdcard/upgrade/kernel.img
 * // upgrade rootfs
 * board# flash_erase /dev/mtd7 0 0
 * board# upgrade_partition -p /dev/mtd7 /sdcard/upgrade/rootfs.bin
 * board# sync
 * For EMMC:
 * // upgrade kernel
 * board# upgrade_partition -p /dev/mmcblk0p7 /sdcard/upgrade/kernel.img
 * // upgrade rootfs
 * board# upgrade_partition -p /dev/mmcblk0p8 /sdcard/upgrade/rootfs.bin
 * board# sync
 * @endcode
 * @note
 *   If eMMC boot partition is used as BST partition, the user must get the
 *   written permission first and then upgrade it.
 *   @code
 *   board# echo 0 > /sys/block/mmcblk0boot0/force_ro
 *   board# upgrade_partition -p /dev/mmcblk0boot0 /sdcard/upgrade/bst.bin
 *   @endcode
 *
 * 12. Switch back to the main system.
 * @code
 * // "/dev/mtd4" is the ENV partition.
 * board# upgrade_partition -e /dev/mtd4 -k -P kernel
 * board# upgrade_partition -e /dev/mtd4 -n -P dtb
 *
 * // If EMMC is used, "/dev/mmcblk0p5" is the ENV partition.
 * board# upgrade_partition -e /dev/mmcblk0p5 -k -P kernel
 * board# upgrade_partition -e /dev/mmcblk0p5 -n -P dtb
 *
 * board# sync && reboot
 * @endcode
 * @note
 *   For debugging purpose, the user can switch to PBA system in AMBoot.
 *   @code
 *   amboot# setenv bootmeta kernel pba
 *   amboot# setenv bootmeta dtb dtb2
 *   amboot# reboot
 *   @endcode
 *
 * @subsubsection si_ab_legacy_upgrade 3.4.7 AB Upgrade Example for Legacy Firmware Layout
 * For legacy firmware layout, a boot flag is used to do the switch between
 * the system A and the system B.<br>
 * Take CV22_gage as an example, perform the following steps to setup AB upgrade
 * for legacy firmware layout:
 * 1. Allocate the "kernel2"(pba) and "rootfs2"(rom) partition size.
 * @code {.c}
 * #define AMBOOT_BST_SIZE     (AMBOOT_BST_FIXED_SIZE)
 * #define AMBOOT_BLD_SIZE     (AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PTB_SIZE     (AMBOOT_MIN_PART_SIZE * 7)
 * #define AMBOOT_ATF_SIZE     (AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PBA_SIZE     (16  * 1024 * 1024)
 * #define AMBOOT_PRI_SIZE     (16  * 1024 * 1024)
 * #define AMBOOT_ROM_SIZE     (108  * 1024 * 1024)
 * #define AMBOOT_LNX_SIZE     (108  * 1024 * 1024)
 * ...
 * @endcode
 * @note
 *   The partition allocation above is not suitable for eMMC. When eMMC is used,
 *   the user must allocate the partition according to the actual need,
 *   especially for the rootfs size.
 *
 * 2. Modify the `bootargs` for booting up the system A.
 * @code
 * build$ vim ambarella/boards/cv22_walnut/bsp/cv22_walnut.dts
 * bootargs = "console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs";
 * @endcode
 * @note
 *   - Although the boot arguments (bootargs) can be set in the menuconfig, it is sugguested to
 *     keep the same as the one set in DTS file. Because the bootargs set in
 *     menuconfig will not be compiled into the DTB image. It takes effect only
 *     in the programming stage.
 *   - When eMMC is used, the bootargs for the main system and PBA system appear as follows
 *     if the partition layout in step 1 is used. For "root=/dev/mmcblk0pX",
 *     the `X` is the sequence number of the partitions counting from 1(bst).
 *     @code
 *     // For system A
 *     bootargs = "console=ttyS0 noinitrd root=/dev/mmcblk0p8 rw rootfstype=ext4 rootwait";
 *     // For system B
 *     bootargs = "console=ttyS0 noinitrd root=/dev/mmcblk0p7 rw rootfstype=ext4 rootwait";
 *     @endcode
 *
 * 3. Modify the `ambarella/boards/<board_name>/bsp/bsp.c`.<br>
 *   The bootloader must obtain the boot flag (boot_opt) to determine which
 *   bootargs to be used and from which partition to load the kernel: PRI or PBA.
 *   @code {.c}
 *   int amboot_bsp_entry(void)
 *   {
 *     char *cmdline = CONFIG_AMBOOT_SWAP_CMDLINE;
 *     u32 boot_opt = 0;
 *     int retval = 0;
 *
 *     retval = env_get_boot_opt(&boot_opt);
 *     if (retval < 0)
 *       return retval;
 *     if (boot_opt > 0) {
 *       printf("Find BIOS boot flag\n");
 *       if (cmdline) {
 *         retval = env_set_cmdline(cmdline);
 *           if (retval < 0)
 *             return retval;
 *       }
 *       retval = 2;
 *     }
 *     return retval;
 *   }
 *   @endcode
 *
 * 4. Configure the AB system in menuconfig.
 * @par For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build$ make cv22_ipcam_config
 * build$ make menuconfig
 * Ambarella Bootloader Configuration  --->
 *   AMBoot Options  --->
 *     Common Boot Options  --->
 *       (console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline  //If rootfs type is UBIFS.
 *       (console=ttyS0 ubi.mtd=rom root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline for swap upgrade
 *      Firmware Options  --->
 *        Persistent BIOS App Partition  --->
 *          ($(AMB_BOARD_OUT)/kernel/Image) PBA
 *          ($(AMB_TOPDIR)/amboot/vif/kernel.info) PBA Version File
 *        ROMFS Partition  --->
 *          ($(AMB_BOARD_OUT)/rootfs/ubifs) Romfs image
 *          ($(AMB_TOPDIR)/amboot/vif/ubifs.info) ROMFS Version File
 * [*] Ambarella File System Configuration  --->
 *   Linux Root File System (UBIFS)  --->
 *     (X) UBIFS
 *   Open Source Software (OSS)  --->
 *     Filesystem Tools  --->
 *       [*] Add mtd utils into root_fs
 * [*] Ambarella Application Configuration  --->
 *   [*]   Build Utilities  --->
 *     [*]   Build Ambarella upgrade partition
 *       Upgrade partition tool (Build for Kernel 4.X and 5.X)  --->
 *         (X) Build for Kernel 4.X and 5.X
 * @endcode
 *
 * @par For Cooper Amba build:
 * @code {.c}
 * build$ make ipcam_config
 * build$ make menuconfig
 * boot  --->
 *   [ ] ambfw (boot/ambamk)  ----
 *   [*] amboot (boot/ambamk)  --->
 *     Ambarella Bootloader Configuration  --->
 *       Firmware Options  --->
 *         Firmware Layout Style (Legacy Firmware Layout)  --->
 *           (X) Legacy Firmware Layout
 *       Persistent BIOS App Partition  --->
 *         ($(ENV_IMG_ROOT)/kernel.bin)  PBA
 *         ($(AMBOOT_TOPDIR)/vif/kernel.info)  PBA Version File
 *       ROMFS Partition  --->
 *         ($(ENV_IMG_ROOT)/rootfs.bin) Romfs image
 *         ($(AMBOOT_TOPDIR)/vif/ubifs.info) ROMFS Version File
 *       AMBoot Options  --->
 *         Common Boot Options  --->
 *           (console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline  //If rootfs type is UBIFS.
 *           (console=ttyS0 ubi.mtd=rom root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline for swap upgrade
 * rootfs  --->
 *   [ ] backup-cpio (rootfs/backup-cpio)  ----
 *   [*]   rootfs (rootfs/system)  --->
 *     Linux Root File System (UBIFS)  --->
 *       (X) UBIFS
 * app  --->
 *   utility  --->
 *     upgrade_partition  --->
 *       [*] upgrade-partition (app/utility/upgrade_partition/app)
 *       -*- libfdt (app/utility/upgrade_partition/libfdt)
 * // For NAND flash, add the mtd utils
 * prebuild  --->
 *   oss  --->
 *     [*] prebuild-mtd-utils (prebuild/oss/armv8-a/mtd-utils)
 * @endcode
 *
 * @par For Cooper Yocto build:
 * @code {.c}
 * build$ make ipcam_config
 * build$ make menuconfig
 * meta-ambabsp  --->
 *   recipes-bsp  --->
 *     [ ] ambfw (meta-ambabsp/recipes-bsp/boot)  ---
 *     [*] amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *       Ambarella Bootloader Configuration  --->
 *         Firmware Options  --->
 *           Firmware Layout Style (Legacy Firmware Layout)  --->
 *             (X) Legacy Firmware Layout
 *           Persistent BIOS App Partition  --->
 *             ($(ENV_IMG_ROOT)/kernel.bin)  PBA
 *             ($(AMBOOT_TOPDIR)/vif/kernel.info)  PBA Version File
 *           ROMFS Partition  --->
 *             ($(ENV_IMG_ROOT)/rootfs.bin)  Romfs image
 *             ($(AMBOOT_TOPDIR)/vif/ubifs.info) ROMFS Version File
 *         AMBoot Options  --->
 *           Common Boot Options  --->
 *             (console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline  //If rootfs type is UBIFS.
 *             (console=ttyS0 ubi.mtd=rom root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline for swap upgrade
 *     [*] amrootfs (meta-ambabsp/recipes-bsp/amrootfs)  --->
 *       Linux Root File System (UBIFS)  --->
 *         (X) UBIFS
 * meta-ambaapp  --->
 *   recipes-upgrade-partition  --->
 *     [*] upgrade-partition (meta-ambaapp/recipes-upgrade-partition/upgrade-partition)
 * meta-ambalib  --->
 *   recipes-upgrade-partition  --->
 *     [*] libfdt (meta-ambalib/recipes-upgrade-partition/libfdt)
 * // For NAND flash, add the mtd utils
 * meta  --->
 *   recipes-devtools  --->
 *     [*] mtd-utils (meta/recipes-devtools/mtd)
 * @endcode
 * @note
 *   - The generated rootfs size may be larger than the partition size allocated
 *     in step 1, the user can remove some unwanted configurations in menuconfig
 *     to reduce the size.
 *
 * 5. Build the firmware and program it to the EVK board.
 * @par For SDK 3.0 Amba Build:
 * @code {.c}
 * build$ make -j8
 * @endcode
 * The generated firmware path: `ambarella/out/cv22_walnut/images/bst_bld_pba_kernel_romfs_lnx_release.elf`.
 * @par For Cooper SDK:
 * @code {.c}
 * build$ make
 * @endcode
 * The generated firmware path: `ambarella/out/<amba|yocto>_out/cv22_walnut/images/bst_bld_pba_kernel_romfs_lnx_release.elf`.<br>
 * The firmware program log:
 * @code {.c}
 * ------ Report ------
 * bst:    success
 * bld:    success
 * pba:    success
 * pri:    success
 * rom:    success
 * lnx:    success
 * @endcode
 * @note
 *    Usually, when programming the firmware into the flash in AMBoot through
 *    the AmbaUSB tool, the available dynamic random access memory (DRAM) size
 *    must be large enough to store the whole firmware. Because before the
 *    firmware is programmed into the flash, it will be loaded into the DRAM
 *    first. If the user's hardware DRAM resources are strained, there are two
 *    ways for the user to handle this situation:
 *    - Program these partitions respectively through the AmbaUSB tool.
 *    - Build a normal firmware and program the extra partitions respectively via
 *      the `upgrade_partition` tool, the same as the image upgrade operations.
 *
 * 7. Prepare the images for AB upgrade used by the `upgrade_partition` tool.<br>
 *   For the images to be used, the user can refer to @ref si_images_for_upgrading
 *   and copy them to a SD card, such as under a `upgrade` folder.
 *
 * 8. Verify the partition after booting up the board.<br>
 *   - Verify the partitions.
 *     For NAND:
 *     @code {.c}
 *     board # cat /proc/mtd
 *     dev:    size   erasesize  name
 *     mtd0: 00020000 00020000 "bst"
 *     mtd1: 00100000 00020000 "bld"
 *     mtd2: 000e0000 00020000 "ptb"
 *     mtd3: 00100000 00020000 "atf"
 *     mtd4: 01000000 00020000 "pba"
 *     mtd5: 01000000 00020000 "pri"
 *     mtd6: 06000000 00020000 "rom"
 *     mtd7: 06000000 00020000 "lnx"
 *     mtd8: 00c00000 00020000 "add"
 *     mtd9: 01080000 00020000 "raw"
 *
 *     board # cat /proc/cmdline
 *     console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc
 *     @endcode
 *
 *     For eMMC:<br>
 *     Here is not a partition allocation example for AB upgrade, just for showing
 *     the eMMC partitions.
 *     @code
 *     board# cat /proc/partitions
 *     major minor  #blocks  name
 *
 *        1        0      65536 ram0
 *       31        0     262144 mtdblock0
 *      179        0   31080448 mmcblk0
 *      179        1        128 mmcblk0p1
 *      179        2       1024 mmcblk0p2
 *      179        3        896 mmcblk0p3
 *      179        4        896 mmcblk0p4
 *      179        5      65536 mmcblk0p5
 *      179        6     524288 mmcblk0p6
 *      179        7   30471168 mmcblk0p7
 *
 *     board # cat /proc/cmdline
 *     console=ttyS0 noinitrd root=/dev/mmcblk0p6 rw rootfstype=ext4 rootwait
 *     @endcode
 *     The partition name can be got from device-tree info.
 *     @code
 *     board# cat /proc/device-tree/sdmmc0@fff2000000/partitions/partition@1/label
 *     @endcode
 *
 *   - Switch to the system B.
 *     @code {.c}
 *     board # upgrade_partition -S 2
 *     board # reboot
 *     @endcode
 *
 *   - Switch back to the system A.
 *     @code {.c}
 *     board # upgrade_partition -S 0
 *     board # reboot
 *     @endcode
 *
 * 9. Insert the SD card and upgrade the system B partitions' image.<br>
 * Assume the SD card will be auto-mounted to `/sdcard/mmcblk1p1/`.
 * @code
 * For NAND:
 * // upgrade bst
 * board# flash_erase /dev/mtd0 0 0
 * board# upgrade_partition -p /dev/mtd0 /sdcard/mmcblk1p1/upgrade/bst.bin
 * // upgrade bld
 * board# flash_erase /dev/mtd1 0 0
 * board# upgrade_partition -p -G /dev/mtd1 /sdcard/mmcblk1p1/upgrade/bld.bin
 * // upgrade dtb
 * board# upgrade_partition -d /sdcard/mmcblk1p1/upgrade/dtb.bin
 * // upgrade kernel2(pba)
 * board# flash_erase /dev/mtd4 0 0
 * board# upgrade_partition -p -Q /dev/mtd4 /sdcard/mmcblk1p1/upgrade/pba.bin
 * // upgrade rootfs2(rom)
 * board# flash_erase /dev/mtd6 0 0
 * board# upgrade_partition -p -R /dev/mtd6 /sdcard/mmcblk1p1/upgrade/rootfs.bin
 *
 * For EMMC:
 * // upgrade kernel2(pba)
 * board# upgrade_partition -p /dev/mmcblk0p5 /sdcard/mmcblk1p1/upgrade/kernel.bin
 * // upgrade rootfs2(rom)
 * board# upgrade_partition -p /dev/mmcblk0p7 /sdcard/mmcblk1p1/upgrade/rootfs.bin
 *
 * board# sync
 * @endcode
 * @note
 *   - If eMMC is used, the user can clean the data first and then upgrade the
 *     partition image.
 *     @code
 *     board# umount /dev/mmcblk0pX
 *     board# dd if=/dev/zero of=/dev/mmcblk0pX
 *     @endcode
 *   - If eMMC boot partition is used as BST partition, the user must get the
 *     written permission first and then upgrade it.
 *     @code
 *     board# echo 0 > /sys/block/mmcblk0boot0/force_ro
 *     board# upgrade_partition -p /dev/mmcblk0boot0 /sdcard/mmcblk1p1/upgrade/bst.bin
 *     @endcode
 *
 * 10. Switch to the system B.
 *     @code {.c}
 *     board# upgrade_partition -S 2
 *     board# sync && reboot
 *     @endcode
 *
 * @subsubsection si_pba_legacy_upgrade 3.4.8 PBA Upgrade Example for Legacy Firmware Layout
 * For legacy firmware layout, a boot flag is used to do the switch between
 * the main system and the PBA system.<br>
 * Take CV22_gage as an example, perform the following steps to setup PBA upgrade
 * for legacy firmware layout:
 * 1. Alloc the `PBA` partition size.
 * @code {.c}
 * #define AMBOOT_BST_SIZE     (AMBOOT_BST_FIXED_SIZE)
 * #define AMBOOT_BLD_SIZE     (AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PTB_SIZE     (AMBOOT_MIN_PART_SIZE * 7)
 * #define AMBOOT_ATF_SIZE     (AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PBA_SIZE     (20  * 1024 * 1024)
 * #define AMBOOT_PRI_SIZE     (16  * 1024 * 1024)
 * #define AMBOOT_ROM_SIZE     (0  * 1024 * 1024)
 * #define AMBOOT_LNX_SIZE     (208  * 1024 * 1024)
 * ...
 * @endcode
 * @note
 *   The partition allocation above is not suitable for eMMC. When eMMC is used,
 *   the user must allocate the partition according to the actual need,
 *   especially for the rootfs size.
 *
 * 2. Modify the `bootargs` for booting up the main system.
 * @code
 * build$ vim ambarella/boards/cv22_walnut/bsp/cv22_walnut.dts
 * bootargs = "console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs";
 * @endcode
 * @note
 *   - Although the bootargs can be set in the menuconfig, it is sugguested to
 *     keep the same as the one set in DTS file. Because the bootargs set in
 *     menuconfig will not be compiled into the DTB image. It takes effect only
 *     in the programming stage. For "root=/dev/mmcblk0pX", the `X` is the
 *     sequence number of the partitions counting from 1(bst).
 *   - When eMMC is used, the bootargs for the main system appear as follows if the
 *     partition layout in step 1 is used.
 *     @code
 *     // For main system
 *     bootargs = "console=ttyS0 noinitrd root=/dev/mmcblk0p7 rw rootfstype=ext4 rootwait";
 *     @endcode
 *
 * 3. Modify the `ambarella/boards/<board_name>/bsp/bsp.c`.<br>
 *   The bootloader must obtain the boot flag (boot_opt) to determine which
 *   bootargs to be used and from which partition to load the kernel: PRI or PBA.
 *   @code {.c}
 *   int amboot_bsp_entry(void)
 *   {
 *     char *cmdline = CONFIG_AMBOOT_SWAP_CMDLINE;
 *     u32 boot_opt = 0;
 *     int retval = 0;
 *
 *     retval = env_get_boot_opt(&boot_opt);
 *     if (retval < 0)
 *       return retval;
 *     if (boot_opt > 0) {
 *       printf("Find BIOS boot flag\n");
 *       if (cmdline) {
 *         retval = env_set_cmdline(cmdline);
 *           if (retval < 0)
 *             return retval;
 *       }
 *       retval = 2;
 *     }
 *     return retval;
 *   }
 *   @endcode
 *
 * 4. Configure the PBA system in menuconfig.
 * @par For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build$ make cv22_ipcam_config
 * build$ make menuconfig
 * Ambarella Bootloader Configuration  --->
 *   AMBoot Options  --->
 *     Common Boot Options  --->
 *       (console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline  //If rootfs type is UBIFS.
 *       (console=ttyS0 rootfs=ramfs root=/dev/ram rw rdinit=/linuxrc) Booting cmdline for swap upgrade
 *      Firmware Options  --->
 *        Persistent BIOS App Partition  --->
 *          ($(AMB_BOARD_OUT)/kernel/pba_zImage) PBA
 *          ($(AMB_TOPDIR)/amboot/vif/pba.info) PBA Version File
 * [*] Ambarella File System Configuration  --->
 *   Linux Root File System (UBIFS)  --->
 *     (X) UBIFS
 *   Open Source Software (OSS)  --->
 *     Filesystem Tools  --->
 *       [*] Add mtd utils into root_fs
 * [*] Ambarella Application Configuration  --->
 *   [*]   Build Utilities  --->
 *     [*]   Build Ambarella upgrade partition
 *       Upgrade partition tool (Build for Kernel 4.X and 5.X)  --->
 *         (X) Build for Kernel 4.X and 5.X
 * @endcode
 *
 * @par For Cooper Amba build:
 * @code {.c}
 * build$ make ipcam_config
 * build$ make menuconfig
 * boot  --->
 *   [ ] ambfw (boot/ambamk)  ----
 *   [*] amboot (boot/ambamk)  --->
 *     Ambarella Bootloader Configuration  --->
 *       Firmware Options  --->
 *         Firmware Layout Style (Legacy Firmware Layout)  --->
 *           (X) Legacy Firmware Layout
 *       Persistent BIOS App Partition  --->
 *         ($(ENV_IMG_ROOT)/pba.bin)  PBA
 *         ($(AMBOOT_TOPDIR)/vif/pba.info)  PBA Version File
 *       AMBoot Options  --->
 *         Common Boot Options  --->
 *           (console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs) Booting cmdline  //If rootfs type is UBIFS.
 *           (console=ttyS0 rootfs=ramfs root=/dev/ram rw rdinit=/linuxrc) Booting cmdline for swap upgrade
 * rootfs  --->
 *   [ ] backup-cpio (rootfs/backup-cpio)  ----
 *   [*]   rootfs (rootfs/system)  --->
 *     Linux Root File System (UBIFS)  --->
 *       (X) UBIFS
 * app  --->
 *   utility  --->
 *     upgrade_partition  --->
 *       [*] upgrade-partition (app/utility/upgrade_partition/app)
 *       -*- libfdt (app/utility/upgrade_partition/libfdt)
 * // For NAND flash, add the mtd utils
 * prebuild  --->
 *   oss  --->
 *     [*] prebuild-mtd-utils (prebuild/oss/armv8-a/mtd-utils)
 * @endcode
 * @note
 *   - To save the storage size, the user can remove some unwanted kernel and
 *     rootfs configurations in menuconfig to reduce the firmware size.
 *
 * 5. Build the firmware and program it to the EVK board.
 * @par For SDK 3.0 Amba Build:
 * @code {.c}
 * build$ make -j8
 * @endcode
 * The generated firmware path: `ambarella/out/cv22_walnut/images/bst_bld_pba_kernel_lnx_release.elf`.
 * @par For Cooper SDK:
 * @code {.c}
 * build$ make
 * @endcode
 * The generated firmware path: `ambarella/out/<amba|yocto>_out/cv22_walnut/firmware/bst_bld_pba_kernel_lnx_release.elf`.<br>
 * The firmware program log:
 * @code {.c}
 * ------ Report ------
 * bst:    success
 * bld:    success
 * pba:    success
 * pri:    success
 * lnx:    success
 * @endcode
 *
 * 7. Prepare the images for PBA upgrade used by the `upgrade_partition` tool.<br>
 *   For the images to be used, the user can refer to @ref si_images_for_upgrading
 *   and copy them to a SD card, such as under a `upgrade` folder.
 *
 * 8. Verify the partition after booting up the board.<br>
 *   - Verify the partitions.
 *     For NAND:
 *     @code {.c}
 *     board # cat /proc/mtd
 *     dev:    size   erasesize  name
 *     mtd0: 00020000 00020000 "bst"
 *     mtd1: 00100000 00020000 "bld"
 *     mtd2: 000e0000 00020000 "ptb"
 *     mtd3: 00100000 00020000 "atf"
 *     mtd4: 01400000 00020000 "pba"
 *     mtd5: 01000000 00020000 "pri"
 *     mtd6: 0D000000 00020000 "lnx"
 *     mtd7: 00880000 00020000 "raw"
 *
 *     board # cat /proc/cmdline
 *     console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc
 *     @endcode
 *
 *     For eMMC:<br>
 *     Here is not a partition allocation example for PBA upgrade, just for showing
 *     the eMMC partitions.
 *     @code
 *     board# cat /proc/partitions
 *     major minor  #blocks  name
 *
 *        1        0      65536 ram0
 *       31        0     262144 mtdblock0
 *      179        0   31080448 mmcblk0
 *      179        1        128 mmcblk0p1
 *      179        2       1024 mmcblk0p2
 *      179        3        896 mmcblk0p3
 *      179        4        896 mmcblk0p4
 *      179        5      65536 mmcblk0p5
 *      179        6     524288 mmcblk0p6
 *      179        7   30471168 mmcblk0p7
 *
 *     board # cat /proc/cmdline
 *     console=ttyS0 noinitrd root=/dev/mmcblk0p6 rw rootfstype=ext4 rootwait
 *     @endcode
 *     The partition name can be obtained from device-tree information.
 *     @code
 *     board# cat /proc/device-tree/sdmmc0@fff2000000/partitions/partition@1/label
 *     @endcode
 *
 *   - Switch to the PBA system.
 *     @code {.c}
 *     board # upgrade_partition -S 2
 *     board # reboot
 *     @endcode
 *
 *   - Switch back to the main system.
 *     @code {.c}
 *     board # upgrade_partition -S 0
 *     board # reboot
 *     @endcode
 *
 * 9. Insert the SD card and upgrade the main system partitions' image.<br>
 * The SD card might not be auto-mounted. The user can use the following command
 * to mount the SD card.
 * @code
 * mknod /dev/mmcblk1p1 b 179 1  // If mmcblk device is not created automatically
 * mkdir -p /sdcard
 * mount -t vfat /dev/mmcblk1p1 /sdcard  // Assume SD card filesystem is vfat.
 * @endcode
 * Then, perform the upgrade opertations.
 * @code
 * For NAND:
 * // upgrade bst
 * board# flash_erase /dev/mtd0 0 0
 * board# upgrade_partition -p /dev/mtd0 /sdcard/upgrade/bst.bin
 * // upgrade bld
 * board# flash_erase /dev/mtd1 0 0
 * board# upgrade_partition -p -G /dev/mtd1 /sdcard/upgrade/bld.bin
 * // upgrade dtb
 * board# upgrade_partition -d /sdcard/upgrade/dtb.bin
 * // upgrade kernel
 * board# flash_erase /dev/mtd5 0 0
 * board# upgrade_partition -p -K /dev/mtd5 /sdcard/upgrade/kernel.bin
 * // upgrade rootfs
 * board# flash_erase /dev/mtd6 0 0
 * board# upgrade_partition -p -R /dev/mtd6 /sdcard/upgrade/rootfs.bin
 *
 * For EMMC:
 * // upgrade kernel
 * board# upgrade_partition -p /dev/mmcblk0p6 /sdcard/upgrade/kernel.bin
 * // upgrade rootfs
 * board# upgrade_partition -p /dev/mmcblk0p7 /sdcard/upgrade/rootfs.bin
 *
 * board# sync
 * @endcode
 * @note
 *   - If eMMC is used, the user can clean the data first and then upgrade the
 *     partition image.
 *     @code
 *     board# umount /dev/mmcblk0pX
 *     board# dd if=/dev/zero of=/dev/mmcblk0pX
 *     @endcode
 *   - If eMMC boot partition is used as BST partition, the user must get the
 *     written permission first and then upgrade it.
 *     @code
 *     board# echo 0 > /sys/block/mmcblk0boot0/force_ro
 *     board# upgrade_partition -p /dev/mmcblk0boot0 /sdcard/upgrade/bst.bin
 *     @endcode
 *
 * 10. Switch to the main system.
 *     @code {.c}
 *     board# upgrade_partition -S 0
 *     board# sync && reboot
 *     @endcode
 *
 * - - - -
 *
 * @section si_partition_auto_recovery 4. Partition Auto Recovery
 *
 * Sometimes, the system on chip (SoC) cannot start normally after the system is upgraded;
 * The reasons for this may include an issue with the upgraded firmware itself or bad blocks appearing in the firmware storage medium, among others.
 * To handle this abnormal situation, the software development kit (SDK) provides an automatic recovery solution.
 * This chapter contains the following sections:
 * - Section @ref si_partition_auto_recovery_introduction
 * - Section @ref si_build_recovery_image_example
 * - Section @ref si_partition_auto_recovery_test
 * - Section @ref si_mcu_communication_protocol_introduction
 *
 * @subsection si_partition_auto_recovery_introduction 4.1 Partition Auto-Recovery Introduction
 *
 * This section introduces the partition auto-recovery mechanism.
 * The recovery mechanism requires the assistance of the microcontroller unit (MCU), because after the system fails to start,
 * the SoC may not be able to pull up the recovery pin to enter recovery mode by itself.
 * After the MCU pulls up the designated recovery pin,
 * the SoC will enter into recovery mode and execute the bootloader stored in the BAK partition to perform the recovery operation.
 *
 * @image html partition_auto_recovery_flow.png "Figure 4-1. Partition Auto-Recovery Flow."
 *
 * After the system boots up successfully in one partition, the SoC will send this partition boot success report to the MCU
 * through the universal asynchronous receiver / transmitter (UART), and the MCU will record the partition state.
 * If the MCU does not receive a boot success report within the timeout when the system boots in a certain partition, the MCU restarts the SoC.
 * After restarting N times, if the corresponding boot success report is still not received, the MCU will pull up the recovery pin of the SoC,
 * and then restart the SoC to let the SoC enter recovery mode. After entering recovery mode,
 * the SoC will query the failed partitions from the MCU, and then perform the recovery operation for the corresponding partitions.
 * After the partitions are restored successfully, the SoC notifies the MCU that the recovery was successful.
 * Then, the MCU pulls low the recovery pin and restarts the SoC.
 *
 * @subsubsection si_build_recovery_image_example 4.2 Example: Build the Recovery Image
 * The following example describes how to enable the partition auto-recovery function.
 *
 * 1. Enable the recovery function and select the UART interface to communicate between the SoC and the MCU. UART1 is used as an example here.<br>
 *   After enabling the recovery function, the BST, BLD, and ATF images will be packed into the BAK image.<br>
 *   @par For CV2x SDK 3.0 Amba build
 *   @code {.c}
 *   build $ make menuconfig
 *           Ambarella Bootloader Configuration  --->
 *             AMBoot Options  --->
 *               [*] Build Recovery Firmware Images  --->
 *                   Recovery Interface (Uart)  --->
 *                   (1)   Recovery Uart Port
 *                   [ ] Build Compressed Recovery Firmware Images
 *   @endcode
 *   @par For Cooper Amba build:
 *   @code {.c}
 *   build $ make menuconfig
 *           [*] boot (boot) --->
 *             Bootloader --->
 *               Ambarella Bootloader Configuration  --->
 *                 AMBoot Options  --->
 *                   [*] Build Recovery Firmware Images  --->
 *                     Recovery Interface (Uart)  --->
 *                       (1)   Recovery Uart Port
 *                       [ ] Build Compressed Recovery Firmware Images
 *   @endcode
 *   @par For Cooper Yocto build:
 *   @code {.c}
 *   build $ make menuconfig
 *           meta-ambabsp --->
 *             recipes-bsp --->
 *               [*] boot (meta-ambabsp/recipes-bsp/boot) --->
 *                 Bootloader --->
 *                   Ambarella Bootloader Configuration  --->
 *                     AMBoot Options  --->
 *                       [*] Build Recovery Firmware Images  --->
 *                         Recovery Interface (Uart)  --->
 *                           (1)   Recovery Uart Port
 *                           [ ] Build Compressed Recovery Firmware Images
 *   @endcode
 *
 *   @note
 *     - The `[ ] Build Compressed Recovery Firmware Images` can be selected to save the size of the BAK partition.
 *     - The baudrate used by UART is set to 115200 by default in the BLD.
 *     - A simple communication protocol is used between the SoC and the MCU @ref si_mcu_communication_protocol_introduction "4.4 Communication Protocol Introduction".
 *     - Though BST is packed into the BAK image, if BST is corrupted in current
 *       running system, the recovery mechanism will not run. Because the
 *       recovery mechanism is based on a working BST.
 *
 * 2. Add the kernel image to the BAK image.<br>
 *   @par For CV2x SDK 3.0 Amba build:
 *   @code {.c}
 *   build $ make menuconfig
 *           Ambarella Bootloader Configuration  --->
 *             Firmware Options  --->
 *               Primary Partition  --->
 *                 [*] Build Kernel to Recovery Image
 *   @endcode
 *   @par For Cooper SDK Amba build:
 *   @code {.c}
 *   build $ make menuconfig
 *           [*] boot (boot) --->
 *             Bootloader --->
 *               Ambarella Bootloader Configuration  --->
 *                 Firmware Options  --->
 *                   Primary Partition  --->
 *                     [*] Build Kernel to Recovery Image
 *   @endcode
 *   @par For Cooper SDK Yocto build:
 *   @code {.c}
 *   build $ make menuconfig
 *           meta-ambabsp --->
 *             recipes-bsp --->
 *               [*] boot (meta-ambabsp/recipes-bsp/boot) --->
 *                 Bootloader --->
 *                   Ambarella Bootloader Configuration  --->
 *                     Firmware Options  --->
 *                       Primary Partition  --->
 *                         [*] Build Kernel to Recovery Image
 *   @endcode
 *
 * 3.	Add the fs image to the BAK image.<br>
 *   @par For CV2x SDK 3.0 Amba build:
 *   @code {.c}
 *   build $ make menuconfig
 *           Ambarella Bootloader Configuration  --->
 *             Firmware Options  --->
 *               Linux Partition  --->
 *                 [*] Build Linux FS to Recovery Image
 *   @endcode
 *   @par For Cooper SDK Amba build:
 *   @code {.c}
 *   build $ make menuconfig
 *           [*] boot (boot) --->
 *             Bootloader --->
 *               Ambarella Bootloader Configuration  --->
 *                 Firmware Options  --->
 *                   Linux Partition  --->
 *                     [*] Build Linux FS to Recovery Image
 *   @endcode
 *   @par For Cooper SDK Yocto build:
 *   @code {.c}
 *   build $ make menuconfig
 *           meta-ambabsp --->
 *             recipes-bsp --->
 *               [*] boot (meta-ambabsp/recipes-bsp/boot) --->
 *                 Bootloader --->
 *                   Ambarella Bootloader Configuration  --->
 *                     Firmware Options  --->
 *                       Linux Partition  --->
 *                         [*] Build Linux FS to Recovery Image
 *   @endcode
 *
 * 4.	Allocate the BAK partition in `ambarella/boards/<board_name>/bsp/bsp.h`.<br>
 *   The BAK partition must be large enough to accommodate the sum of the images selected above.
 *   @code {.c}
 *   #define AMBOOT_BAK_SIZE     (250  * 1024 * 1024)
 *   @endcode
 *
 * 5.	Configure the recovery pin in `ambarella/boards/<board_name>/bsp/xxx.ini`.<br>
 *   The general purpose input / output (GPIO) 106 is used as an example here.
 *   @code {.c}
 *   <?xml version="1.0" encoding="utf-8"?>
 *     ......
 *     <PARAM_RECOVERY_GPIO value="106"/>
 *   </BSTConfig>
 *   @endcode
 *
 * 6.	Configure the UART1 mentioned above, which can be used to report the Linux boot state in the file system..
 *   @code {.c}
 *   n_ahb@e0000000 {
 *     ........
 *     uart1: uart@e00XX000 {
 *       status = "ok";
 *     };
 *     ........
 *   };
 *
 *   @endcode
 *
 * 7.	Build and burn the firmware `ambarella/out/cvx_board/images/bst_bld_atf_pba_kernel_backup_lnx_release.elf` on CV2x SDK 3.0
 *    or `ambarella/[amba|yocto]_out/cvx_board/firmware/bst_bld_atf_pba_kernel_backup_lnx_release.elf` on Cooper SDK to the board.
 *   @code {.c}
 *   build $ make -j8
 *   @endcode
 *
 * @subsubsection si_partition_auto_recovery_test 4.3 Example: Partition Auto-Recovery Test
 * This example is tested on an eMMC boot device.
 *
 * 1. Verify the partition after booting up the board.<br>
 *   If the boot media is an eMMC device, use the following command to check the specified partition
 *   instead of `cat /proc/mtd`, which is used for the memory technology device (MTD), such as NAND.
 *   @code {.c}
 *   # cat /proc/device-tree/n_ahb@e0000000/sdmmc0@e0004000/partitions/partition@7/label
 *   bak
 *   @endcode
 *
 * 2. Upgrade the BLD using a corrupted image, or erase the BLD.
 *   @code {.c}
 *   board # upgrade_partition -p -G /dev/mmcblk0p2 /tmp/bld_release.bin (or /tmp/fip.bin in the secure boot.)
 *   @endcode
 *   or
 *   @code {.c}
 *   amboot> erase bld
 *   @endcode
 *
 * 3. Inform the MCU to restart the SoC through UART1 in the file system or power cycle the whole device.
 *
 * 4. Wait for the auto recovery operation; the logs from the SoC are as shown below.
 *   @image html partition_auto_recovery_log.png "Figure 4-2. Partition Auto Recovery Log."
 *
 * 5. After recovery, the SoC will be restarted by the MCU and then boot normally.
 *
 * @subsubsection si_mcu_communication_protocol_introduction 4.4 MCU Communication Protocol Introduction
 * This communication protocol is used between the SoC and the MCU. Its fields are defined as follows.<br>
 *
 * @image html mcu_communication_protocol.png "Figure 4-3. Communication Protocol."
 *
 * @note
 * The protocol implementation can be found under `ambarella/amboot/src/bld/recovery`.
 */

/*!
 * @file doc_sys_design_hw_timer_pts.h
 * @brief
 * @version 1.0
 * @date 2021-10-21
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
 * @page page_sys_hw_pts_doc DESIGN - Timer & PTS
 *
 * @section hw_pts_history 0. Revision History
 *  | Updated Date     | Modification                                               |
 *  | :--------------- |:------------------------------------------------ ----------|
 *  | 20211021         | Initial draft                                              |
 *  | 20220613         | Update the document to explain in more details             |
 *  | 20230726         | Updated Section 2, added details for sync timer and source |
 *  | 20230828         | Updated Section 2.3 for sync timer usage                   |
 *
 * - - - -
 *
 * @section hw_pts_overview 1. Overview
 *
 * In order to synchronize video and audio data for the CV5x platform, a global
 * timer is required to generate video and audio timestamp.
 * The requirements for this global timer are listed as follows:
 *  1. The global timer should be able to generate a 64-bit timestamp instead of
 *     a 32-bit timestamp. A 32-bit timestamp can be wrapped around in a short time.
 *     For instance, if the timer jiffies are 1000000, the generated timestamp
 *     will be wrapped around after 4295 seconds. However, if the width is 64 bits,
 *     the generated timestamp will last long enough to avoid wrap around.
 *  2. This global timer should be independent enough and cannot be affected by
 *     any other sources. Only this can ensure that the generated timestamp
 *     is precise enough and then can be used for synchronization between audio and video.
 *
 * Previously, Ambarella adopted the system timer as a reference clock source.
 * Since the system timer ticks can be accessed directly by calling the related
 * API, video and audio applications can directly access it to get the timestamp
 * for any timer.  However, this method has the following drawbacks:
 *  1. The system clock may be synchronized with the NTP time. Thus, the timestamp
 *     around the synchronization point can be drifted forward or back.
 *     But this cannot ensure that the timestamp is monotonic increasing, which
 *     is quite important for the PTS use case.
 *  2. The system clock cannot be accessed by digital signal processor (DSP). So,
 *     the video PTS generation has to be delayed inside the VIN ISR. This will
 *     cause frame time-stamping delay depending on the time difference between
 *     DSP capturing a frame and Arm® receiving VIN ISR.
 *
 * The solution used in CV5x SDK is listed as follows:
 *  1. For CV5x, there is a 32-bit global timer (12.288 MHz) which can be accessed
 *     both from DSP and Arm side. Both audio and video can use this global timer
 *     to generate their timestamps as PTS.
 *  2. One of the CV5x interval timers (TIMER 4 is used here) is used to check the
 *     global timer overflow cases periodically.
 *  3. Arm generates 64-bit timer ticks based on the 32-bit global timer by incorporating
 *     overflow counters, and outputs timestamps with configured output frequencies.
 *
 * The global timer is independent, and not influenced by outer resources. So,
 * there are no timer tick drift cases. The timestamp generated by the global timer
 * is easy to be configured to be 64 bits to make sure no wraparound happens.
 *
 * - - - -
 *
 * @section hw_pts_hw 2. Hardware Timer
 * @subsection hw_pts_hw_implementation 2.1 Implementation
 * In CV5x, the global timer is used to be implemented as a hardware timer.
 * This is a 32-bit timer, not enough for 64-bit PTS usage. The frequency for this
 * global timer is 12.288 MHz. So, the 64 bits counter is maintained with this 32-bit
 * tick in the hardware timer driver. The driver is located in
 * @c "ambarella\drv_modules\private\video\dsp_v6\hw_timer"
 *
 * In this hardware timer driver, proc file @c "/proc/ambarella/ambarella_hwtimer"
 * is created. All the applications can read the value from this proc file to get
 * the current timestamp in 64 bits. Normally, Audio PTS is generated in this way.
 * Video PTS is generated inside IAV. Hardware timer driver also provides interface
 * to kernel modules (IAV) so that IAV can get the current timestamp for video directly.
 *
 * Hardware timer driver supports changing the output frequency dynamically by writing a
 * new output frequency counter into the process file /proc/ambarella/ambarella_hwtimer_outfreq.
 * For example, users can change the output frequency to 1 MHz with the commands
 * @c "echo 1000000 > /proc/ambarella/ambarella_hwtimer_outfreq".
 *
 * It is recommended to keep the default 90 KHz output frequency. However, if a new
 * output frequency is required, the IAV driver should be re-initialized again,
 * so that the IAV driver is aware of the updated output frequency.
 *
 * The hardware timer driver maintains a global 64-bit counter.
 * The TIMER4 used by the hardware timer driver is used to watch the overflow counters
 * periodically.  So the 64-bit counter is listed as follows:<br>
 * <b>Timestamp_input = (Overflow_counter << 32) + Global_timer_tick</b><br>
 * The output 64 bits timestamp is then generated from the input timestamp.
 * The formula is as follows:<br>
 * <b>Timestamp_output = (Timestamp_input * OUT_FREQ + INP_FREQ / 2) / INP_FREQ</b><br>
 * @b OUT_FREQ and @b INP_FREQ are output frequency and input frequency respectively.
 * The input frequency is fixed with 12288000.
 *
 * @subsection hw_pts_timer_sync 2.2 Sychronized with System Timer
 * For some use cases, hardware timer needs to be in sync with the global system timer.
 * This is because some modules may need to use the system timer as the clock source.
 * So when the events from these modules need to be synchronized with the video or audio
 * presentation time stamp (PTS), users can configure the hardware timer to be in sync
 * with system timer. Then the PTS from them would be in the same clock domain, and can
 * be considered from the same clock source.
 *
 * Firstly, the hardware timer must be in the same frequency as the system timer. It would
 * be configured with 1 MHz, which means value 1 tick indicating 1/1000000 second. Secondly,
 * the initial timer value should be initialized as the current system timer tick, to make
 * sure that hardware timer and system timer start at the same time.  Lastly, it is also
 * needed to adjust the hardware timer values in a fixed frequency, according to the system
 * timer ticks. The synchronization frequency is currently set once per second, to make sure
 * the hardware timer is not drifted too much.
 *
 * For the system timer source, Linux supports various sorts for different purposes.
 * Currently, hardware timer can choose from the system timer sources below:
 * (1) <b>CLOCK_MONOTONIC</b>:
 *     The system timer increases monotonically, but may be adjusted by adjtime and network
 *     time protocol (NTP). This matches user space API clock_gettime(<b>CLOCK_MONOTONIC</b>, xxx).
 * (2) <b>CLOCK_MONOTONIC_RAW</b>:
 *     The system timer increases monotonically. It won'd be affected by adjtime or NTP.
 *     This is used as the default system clock source, when adjusting hardware timer.
 *     This matches user space API clock_gettime(<b>CLOCK_MONOTONIC_RAW</b>, xxx).
 * (3) <b>CLOCK_REALTIME</b>:
 *     The realtime system clock, may be ajdusted by adjtime and NTP.
 *     This matches user space API clock_gettime(<b>CLOCK_REALTIME</b>, xxx).
 * (4) <b>CLOCK_BOOTTIME</b>:
 *     It is similar as CLOCK_MONOTONIC. The difference is that CLOCK_BOOTTIME still counts
 *     time when system is suspended, while CLOCK_MONOTONIC doesn't.
 *     This matches user space API clock_gettime(<b>CLOCK_BOOTTIME</b>, xxx).
 *
 * When the hardware timer is configured to synchronize with the system timer, the 64-bit
 * video PTS can be directly used to compare with other system event timestamps captured from
 * user space clock APIs mentioned above. For more details of the example about how to use
 * hardware timer tick and user space clock API, please refer to the unit test `test_hwtimer`,
 * which is located at ambarella\unit_test\private\iav_test\dsp_v6.
 *
 * @subsection hw_pts_hw_usage 2.3 Usage
 * Hardware timer module is located in ambarella\kernel\private\drivers. To enable
 * this module to compile, enable @c "Build Ambarella private hw_timer module" in
 * @c menuconfig as shown below:
 * @code {.c}
 * build $ make menuconfig
 *     [*] Ambarella Linux Configuration --->
 *       [*] Ambarella Private Drivers Configuration --->
 *         [*] Build Ambarella private hw_timer module
 * @endcode
 * When hardware timer module is compiled, users can find two process files:
 * @c "/proc/ambarella/ambarella_hwtimer" and @c "/proc/ambarella/ambarella_hwtimer_outfreq".
 * Users can open @c "/proc/ambarella/ambarella_hwtimer" and read the current 64-bit
 * timestamp. @c "/proc/ambarella/ambarella_hwtimer_outfreq" stores the current
 * hardware timer output frequency. Users can write values to it through
 * @c "echo value > /proc/ambarella/ambarella_hwtimer_outfreq".
 *
 * Example to configure the hardware timer output frequency to be 90 KHz.
 * @code {.c}
 *    #echo 90000 > /proc/ambarella/ambarella_hwtimer_outfreq
 * @endcode
 *
 * Example to write the initial 64-bit timestamps, when the system is booted.
 * @code {.c}
 *    #echo 0 > /proc/ambarella/ambarella_hwtimer
 * @endcode
 *
 * Example to read the current 64-bit timestamps.
 * @code {.c}
 *    #cat /proc/ambarella/ambarella_hwtimer
 * @endcode
 *
 * There is a parameter "sync_timer" for hardware timer module, which is used as the flag to enable
 * synchronization with system timer.
 * Users can add below line into /etc/modprobe.d/ambarella.conf to enable the synchronization.
 * @code {.c}
 *    options hw_timer sync_timer=1
 * @endcode
 * Example to check whether sync_timer is enabled, after system boots up.
 * @code {.c}
 *    #cat /proc/ambarella/ambarella_hwtimer_sync_timer
 * @endcode
 *
 * There is another parameter "timer_src" for hardware timer module, which is used as the option to select
 * the timer source for system timer synchronization. This option must be used, when "sync_timer" is enabled.
 * The values for the sync sources are as follows:
 *     0 -> CLOCK_MONOTONIC_RAW; 1 -> CLOCK_MONOTONIC; 2 -> CLOCK_REALTIME; 3 -> CLOCK_BOOTTIME.
 * Users can add the line below into /etc/modprobe.d/ambarella.conf to configure sync source to be
 * SYNC_CLOCK_MONOTONIC.
 * @code {.c}
 *    options hw_timer sync_timer=1 timer_src=1
 * @endcode
 * Example to check the current system timer sync source, after system boot up.
 * @code {.c}
 *    #cat /proc/ambarella/ambarella_hwtimer_sync_src
 * @endcode
 *
 * The parameter "sync_interval" is added for hardware timer module to configure the synchronization
 * interval in milliseconds (ms). The default value is 1000, meaning to synchronize hardware timer
 * and system timer every second.
 * Users can add the line below into /etc/modprobe.d/ambarella.conf to configure sync source to be
 * SYNC_CLOCK_MONOTONIC with synchronization interval 100 ms.
 * @code {.c}
 *    options hw_timer sync_timer=1 timer_src=1 sync_interval=100
 * @endcode
 *
 * - - - -
 *
 * @section hw_pts_clock_source 3. Clock Sources
 * There are possible three clock sources, which are used as PTS sources.
 *
 * The first one is the I2S clock (audio clock) source from the global timer,
 * with 12.288 MHz frequency. It is normally for the PTS information reported from
 * DSP, because DSP can only access this timer. The global timer is started once
 * DSP is booted, and the ticks and the frequency can't be configured.
 *
 * The second one is the clock source from hardware timer. This clock is commonly
 * used by user applications to synchronize different events, such as video frame
 * PTS, audio sample PTS, and potentially others. The frequency is by default 90
 * KHz, and it is configurable for other values, such as 1 MHz.
 *
 * The third one is from DSP software, and it is used to generate software PTS.
 * The software PTS is increased from 0, and with fixed PTS interval. The frequency
 * for this is 90 KHz. So if the frame rate is 30, the software PTS will be in the
 * sequence of 0/3000/6000/9000/... The PTS will be reset to 0 for each time DSP
 * is switched into preview state.
 *
 * - - - -
 *
 * @section hw_pts_audio 4. Audio PTS
 * @subsection hw_pts_audio_implementation 4.1 Implementation
 * Audio PTS is generated in user space applications. It can be generated directly
 * by reading the proc file @c "/proc/ambaella/ambarella_hwtimer".
 *
 * Once an audio packet needs an audio PTS, the only thing the application needs
 * to do is to read the procs file. It is requested to stamp the audio PTS, when the
 * audio sample is captured from the audio capture device. If the audio PTS is stamped
 * after some processing, then there will be potential sychronization issues, such as
 * audio / video synchronization issue.
 *
 * - - - -
 *
 * @section hw_pts_video 5. Video PTS
 * @subsection hw_pts_video_implementation 5.1 Implementation
 * Video PTS generation is more complicated when compared to Audio PTS.
 *
 * The video time-stamping operation is implemented inside DSP. This is the exact
 * accurate timing generating timestamp that is generated when a full frame is captured.
 * The presentation time stamp (PTS) has the same meaning as the capture time stamp.
 * If the time-stamping operation is done on the Arm side, the time-stamping moment
 * is delayed and inaccurate.
 *
 * The PTS sent by DSP is generated from the global timer, with I2S clock 12.288 MHz.
 * The hardware time driver will translate this PTS to the hardware timer PTS.
 *
 * When DSP finishes encoding a frame of a stream, it will generate an encode interrupt
 * to IAV. There will be several frames delay when one frame is encoded after this
 * frame is captured. This is called encode pipeline delay here. Before issuing
 * the encode interrupt, DSP will put the frame information to the frame information
 * buffer shared between the DSP and IAV. IAV will get the DSP PTS (generated
 * by the global timer) from the frame information buffer, and generate the hardware
 * PTS based on the DSP PTS. Since the DSP PTS is just a few frames before the current
 * global timer tick, the hardware PTS will be generated based on this information
 * to avoid confusion for overflow cases.
 *
 * @subsection pts_in_each_idsp_vdsp_domain 5.2 PTS for Output Data in Each Stage
 * @image html hw_timer_pts_in_each_idsp_domain.png "PTS in Each IDSP/VDSP Domain"
 * The image above shows the PTS for each output data in IDSP/VDSP stage.
 *
 * The timing to stamp the PTS value is when the video frame is captured by DSP.
 * In this way, the PTS for the frame data at different stages can be sychronized.
 * Users can use the PTS value to know whether the frame information from different stages
 * are from the same captured frame, and they can also know the capture time difference
 * for the 2 frame data in different stages.
 *
 * @subsection PTS_clock_source 5.3 PTS Clock Sources
 * As @ref hw_pts_overview "Overview" and @ref hw_PTS_hw "Hardware Timer" described,
 * the clock source of hardware PTS is audio clock, and the frequency of which is 12.288 MHz.
 * However, the typical application domain frequency is 90 KHz, so Ambarella introduces
 * software PTS, which is 90 KHz based.
 *
 * @subsection different_PTS_categories 5.4 Different PTS Categories
 * The table below shows the basic information of hardware PTS, software PTS, and monotonic PTS.
 * these three types of PTS are all attached by IDSP/VDSP or Arm.<br>
 * In theory, the PTS value will be increased frame by frame, and the difference of PTS per frame is
 * "The frequency of clock base / fps".
 * <table>
 * <caption>Clock Souce of Different PTS</caption>
 * <tr><th>PTS variable<th>Bits<th>Clock Source<th>Calculation Method
 * <tr><td>hw_pts<td>32<td>Global Timer<td>Global Timer Ticks used by DSP, in 12.288 MHz
 * <tr><td>sw_pts<td>32<td>Software<td>Start from 0, adding fixed delta in 90 KHz for each frame.
 * <tr><td>mono_pts/arm_pts<td>64<td>Hardware Timer<td>Sychnorized with hardware timer, default 90 KHz
 * </table>
 *
 * In this section, Ambarella enumerates the PTS categories in each stages and lists tables below.<br>
 * (1) RAW & IDSP<br>
 * <table>
 * <caption>RAW & IDSP Stage PTS Varibles</caption>
 * <tr><th>PTS variable<th>Bits<th>Clock Source<th>Description
 * <tr><td>hw_pts<td>32<td>Global Timer<td>Raw/3A global timer PTS stamped by DSP
 * <tr><td>sw_pts<td>32<td>Software<td>Raw/3A software PTS stamped by DSP
 * <tr><td>mono_pts<td>64<td>Hardware Timer<td>Raw/3A monotonic PTS stamped by hardware timer
 * </table>
 * (2) Canvas/Pyramid, YUV/me0/me1<br>
 * For "dsp_pts", users can specify the clock source of it according the flag "is_dsp_hw_pts" in user space.
 * <table>
 * <caption>YUV Stage PTS Varibles</caption>
 * <tr><th>PTS variable<th>Bits<th>Clock Source<th>Description
 * <tr><td>hw_pts<td>32<td>Global Timer Clock<td>Raw/3A global timer PTS stamped by DSP
 * <tr><td>sw_pts<td>32<td>Software<td>Raw/3A software PTS stamped by DSP
 * <tr><td>mono_pts<td>64<td>Hardware Timer<td>Raw/3A monotonic PTS stamped by hardware timer
 * <tr><td>dsp_pts<td>32<td>Global Timer or Software<<td>DSP sw_pts or hw_pts, decided by "is_dsp_hw_pts"
 * </table>
 * (3) VDSP<br>
 * <table>
 * <caption>VDSP Stage PTS Varibles</caption>
 * <tr><th>PTS variable<th>Bits<th>Clock Source<th>Description
 * <tr><td>arm_pts<td>64<td>Hardware Timer<td>Raw capture done monotonic PTS stamped by Arm
 * <tr><td>enc_done_pts<td>64<td>Hardware Timer<td>Frame bitstream output monotonic PTS stamped by Arm
 * <tr><td>dsp_pts<td>64<td>Global Timer & Software<td>Low 32 bit with sw_pts, high 32 bit with hw_pts
 * </table>
 *
 * @subsection PTS_for_different_sychronization_scenarios 5.5 PTS for Different Sychronization Scenarios
 * Users can take different PTS for different stages and use them for different purposes, such as:<br>
 * (1) @ref codec_fsync "Frame Sync" and @ref codec_ssync "Stream Sync"<br>
 *  For these user cases, both hardware PTS and software PTS can be used for synchronization.<br>
 * (2) Audio video sync<br>
 *  Audio's PTS is obtained from hardware timer, which is the same clock base as video monotonic PTS.
 *  Hence, users can do audio and video synchronization combine either hardware PTS or monotonic PTS.
 *
 * If user application would like to do synchronizations between Arm and DSP, then users may
 * need to choose from hardware PTS (hw_pts) or software PTS (sw_pts). For example, synchronize warp related
 * operations to the specified frame, or synchronize encoder related operations to the specified frames.
 *
 * If user application needs to synchronize different sources at Arm side, then users may need to use
 * the 64 bit monotonic Arm PTS (arm_pts or mono_pts). For example, synchronization between audio and
 * video data, or synchronization between video and other sources (gyro data, ...)
 *
 * - - - -
 *
 * @section hw_pts_use_scenario 6. Use Scenarios for PTS
 * @subsection hw_pts_av_sync 6.1 Audio and Video Synchronization
 * For audio, user applicaion should get the hardware time ticks, as soon as the audio samples is
 * captured from audio capture device.
 * For video, when user application calls IOCTL to query frame data, users will get the actual PTS
 * from arm_pts in the struct iav_framedesc. This PTS is also stamped when the video RAW frame is
 * captured by DSP.
 * As long as the timing for both audio PTS and video PTS happens when the data is captured done,
 * these audio samples and video frames can be automatically sychronized using the capture PTS.
 *
 * @subsection hw_pts_frame_sync 6.2 Frame Synchronization Mechanism
 * The typical working flow for frame synchronization mechanism is described below.
 *  1. User application queries the canvas frame data, through IOCTL IAV_IOC_QUERY_DESC with IDSP
 *     IAV_DESC_CANVAS.
 *     In the struct iav_yuv_cap, there is dsp_pts used to synchronize with DSP.
 *  2. User application does some analysis based on the canvas YUV data, and calculates some
 *     encode parameters for this dedicated frame.
 *  3. User issues these encode parameter to IAV/DSP, through IOCTL IAV_IOC_APPLY_FRAME_SYNC_PROC.
 *     In the struct iav_apply_frame_sync, there is also dsp_pts field, which needs to match the
 *     dsp_pts in the canvas YUV data. When this is matched, the encode parameters will be applied
 *     to this dedicated frame, when it goes into encoder.
 * For this frame synchronization feature, the dsp_pts is actually software PTS (sw_pts described above),
 * so the parameter is_dsp_hw_pts in struct iav_canvasdesc must be disabled in this case, when querying
 * canvas YUV data. This PTS is from DSP, and also applied to DSP when performing frame synchronization.
 *
 * - - - -
 *
 * @section hw_pts_encode 7. Stream Encode Done PTS
 * @subsection hw_pts_encode_info 7.1 Information
 * The stream encode done time-stamping operation is implemented inside IAV driver. This
 * is the timing when IAV driver gets the VDSP interrupt, and has collected the full
 * frame data from VDSP. IAV driver will call hardware timer driver to get current ticker
 * immediately when the full frame data are collected.
 *
 * @code {.c}
 * struct iav_framedesc {
 *      u32 id;
 *      u32 time_ms;
 *      ............
 *      u64 enc_done_ts;
 *      ............
 * };
 * @endcode
 *
 * @subsection hw_pts_encode_usage 7.2 Usage
 *
 * The encode done PTS describes the timing when Arm receives the endoded frame data.
 * By comparing this PTS with the RAW capture done PTS (mono_pts or arm_pts), users can
 * understand the pipeline latency between RAW capture done and encode done, which includes
 * the time of IDSP processing time as well as VDSP encoding time.
 *
 * The encode done PTS is NOT suggested to be used as the actual PTS, which may be used
 * to sychronize with other events, such as audio. The reasons are listed as follows:
 *  1. The time stamp timing must be deterministic. The encode done timing is not
 *     deterministic, because it may be affected by the IDSP procession latency as well as
 *     the encode latency.
 *  2. The time stamp timing must be stable. When stamping at Arm side, it may be affected
 *     by the DSP interrupt timing as well as the system loading. The timing may be
 *     fluctuated from time to time. And it may also be affected by different number of
 *     encode streams, because there is only one set of VDSP hardware to encode all the
 *     streams, and the frames from these streams must be encoded sequentially.
 *  3. The frame encoding order may be different from frame capture order. When B frames
 *     are enabled, the PTS will not be in ascending order. So it is not applicable to use
 *     encode done timing as the PTS.
 *
 * - - - -
 *
 * @section hw_pts_license 8. License
 * Copyright (c) @ambalicyear Ambarella International LP
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
 *
 */
/*!
 * @file doc_sys_design_fastboot.h
 * @brief This file introduces fast boot design
 * @version 0.1
 * @date 2023-11-23
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

/*! @page page_sys_fastboot DESIGN - Fast Boot
 *
 * @section fastboot_history 0. Revision History
 * <table>
 * <caption id="fastboot_rev_history"></caption>
 * <tr><th> SDK Version        <th> Updated Date          <th> Modification
 * <tr><td> cooper 1.5         <td> 20231122              <td> Added Page Design - Fast Boot
 * </table>
 *
 * @note
 * The SDK versions listed in the table reflect the current SDK version (x.x) or patch release (x.x.x).<br>
 * A patch number that is not sequential indicates that the previous patch release did not apply to this document.
 *
 * - - - -
 *
 * @section sys_fb_intro 1. Introduction
 * This document describes the fastboot method used to quickly start the system.
 * The following list compares the advantages and disadvantages to these methods.
 * - Cold boot:<br>
 * Fast cold boot is a fastboot option that requires the least amount of modification
 * to the existing system among all two fastboot methods.
 * It retains the normal boot-up mechanism, and accelerates the boot-up process by
 * optimizing boot scripts, utilizing clean boot, and speeding up peripheral
 * loading.
 * - Dynamic random-access memory (DRAM) self-refresh:<br>
 * DRAM self-refresh is a fastboot option that relies on DRAM running in the
 * background. It saves the system context to DRAM on shutdown and
 * restores the system from DRAM on bootup. <br>
 * However, the DRAM self-refresh method requires an external
 * microcontroller unit (MCU) to manage system on chip (SoC) power and DRAM. Further, its standby
 * power additionally includes the DRAM power consumption.
 *
 * The following tables provide the key specifications of each fastboot option:
 * <table>
 * <caption id="cleanboot_table">Table 1-1. Comparison of Fastboot Methods.</caption>
 * <tr><th align="center">                                  <th align="center" width="300px"> Cold Boot                           <th align="center" width="300px"> DRAM Self-refrsh
 * <tr><th> Resume Timestamp                                <td align="center">Load kernel image: 171 mSec<br>
 *                                                                             Jump to kernel: 305 mSec<br>
 *                                                                             Enter Linux: 663 mSec<br>
 *                                                                             Probe digital signal processor (DSP): 697 mSec<br>
 *                                                                             Cavalry done: 736 mSec<br>
 *                                                                             Load firmware: 770 mSec<br>
 *                                                                             Probe video input (VIN) done: 821 mSec<br>
 * <td align="center"> Resume from idle: 64 mSec
 * <tr><th> First frame capture                                  <td align="center"> 1050 mSec                                                  <td align="center"> 442 mSec
 * <tr><th> Enter encode                                         <td align="center"> 1322 mSec                                                  <td align="center"> 624 mSec
 * <tr><th> Note                                                 <td align="center"> With eMMC boot; SD read speed: 73333 KB/s                  <td align="center"> An external MCU for power management is required
 * </table>
 * @note
 * Limited driver modules are probed for optimization, as shown below.
 *     @code {.c}
 *     Module                  Size  Used by
 *     os08a10                32768  0
 *     iav                   995328  5 os08a10
 *     cavalry               126976  2
 *     amba_otp               40960  0
 *     dsp                   114688  3 iav
 *     imgproc               307200  1 iav
 *     ambcma                 61440  3 imgproc,dsp,iav
 *     ambnl                 176128  3 imgproc,dsp,iav
 *     hwtimer                20480  3 imgproc,ambnl,iav
 *     @endcode
 *
 * - - - -
 *
 * @section sys_fb_cold_boot 2. Cold Boot
 * @subsection clean_boot_outline 2.1 Outline
 *
 * This guide demonstrates how to cold start the system to record videos
 * as soon as possible by (1) optimizing the system startup script and (2) clipping the system.
 * The system startup time refers to the time from cold startup to the acquisition of the first frame.<br>
 * - @ref clean_boot_script "Section 2.2" describes how to prepare the system startup script to
 * load drivers in parallel, which is the most important step and can reduce time by about two seconds<br>
 * - @ref clean_boot_system "Section 2.3" describes how to slim the system in order to achieve
 * a faster start-up speed, which can reduce the time by hundreds of milliseconds<br>
 * - @ref clean_boot_others "Section 2.4" introduces other hardware-related optimization methods<br>
 * - @ref clean_boot_test "Section 2.5" describes how to measure the boot-up time<br>
 * - @ref clean_boot_example "Section 2.6" shows an example of running cold boot optimization<br>
 *
 * @subsection clean_boot_script 2.2 System Startup Script Optimization Method
 *
 * @subsubsection script_optimization_parallel 2.2.1 Load Necessary Module Drivers in Parallel
 *     @code {.c}
 *     S10syscfg   	S13load-private-driver
 *     S11init 		rcS
 *     S12udev
 *     @endcode
 *
 * After the system restarts, `rcS` will be executed. `rcS` executes the Sxx script to load the module drivers,
 * such as audio, secure digital (SD), USB, udev, network, and more. The system waits until all drivers are loaded.
 * In order for the camera to function normally, only image audio video (IAV), audio, SD, and udev, among other drivers, are required.
 * Therefore, the system must load these drivers when starting.
 * In order to further accelerate the loading process, the parallel loading method
 * (running in the background) can be adopted.
 * First, modify `rootfs/system-init/busybox-sysvinit/sysroot/etc/init.d/rcS` to execute only one optimization script, as follows:
 *     @code {.c}
 *     #!/bin/sh
 *     /etc/init.d/S01optinit
 *     exit
 *     @endcode
 *
 * Then, write `S01optinit` to load the necessary drivers in parallel. Refer to the following:
 *     @code {.c}
 *     #!/bin/sh
 *     export PATH=/bin:/sbin:/usr/sbin:/usr/bin:/usr/local/bin
 *     __calc_time() {
 *     timer8_val=`devmem 0xffe4004074`
 *         let timer8_val=-$timer8_val+0xffffffff
 *         let t_ms=$timer8_val/156000
 *         echo "$1: $t_ms"
 *     }
 *
 *     __probe_vin_os08a10() {
 * 	       modprobe os08a10 vinc_id=8
 * 	       __calc_time "Probe VIN Done"
 *     }
 *
 *     __probe_cavalry() {
 * 	       modprobe amba_otp &
 * 	       modprobe cavalry
 * 	       cavalry_load -r
 * 	       __calc_time "Cavalry Done"
 *     }
 *
 *     __calc_time "/etc/init.d/rcS"
 *
 *     __load_ucode_fw() {
 * 	       load_ucode -f /lib/firmware > /dev/null
 * 	       __calc_time "Load Firmware"
 *     }
 *
 *     __probe_dsp_drv() {
 * 	       modprobe ambnl
 * 	       modprobe ambcma ama_enable=1
 * 	       modprobe imgproc
 * 	       modprobe dsp ## ucode_preload=1
 *
 *
 * 	       __calc_time "Probe DSP"
 *     }
 *
 *     __probe_iav_vin() {
 *  	   modprobe iav
 * 	       echo 0x0 > /proc/ambarella/dsp_print &
 *         echo 0x0 > /proc/ambarella/iav_cmd_print &
 *
 * 	       __probe_vin_os08a10
 *     }
 *     # __probe_vin run in background
 *
 *     ######################################

 *     __probe_dsp_drv
 *
 *     __probe_iav_vin &
 *     __probe_cavalry &
 *     __load_ucode_fw

 *     dsp_monitor_service &
 *
 *     __calc_time "Done"
 *
 *     @endcode
 *
 * @subsubsection script_optimization_compile 2.2.2 Compile Optimized Scripts in the SDK
 * For the optimizations described in @ref script_optimization_parallel "Section 2.1" to take effect at the compilation stage,
 * add the above files to `rootfs/system-init/busybox-sysvinit/sysroot/etc/init.d` in the software development kit (SDK).<br>
 *
 * Then, check the `CONFIG_BUSYBOX_SYSVINIT` option in menuconfig, as follows:<br>
 * @code {.c}
 * build $ make menuconfig
 *         rootfs --->
 *           system-init@virtual (rootfs/system-init) (busybox-sysvinit) --->
 * @endcode<br>
 *
 * After the system boots up, the optimized startup scripts will be under the directory `/etc/init.d`.<br>
 *
 * @subsection clean_boot_system 2.3 System Tailoring
 *
 * @subsubsection file_system_size 2.3.1 Reduce File System Size
 * To reduce the size of the root file system (rootfs) image, users can reduce the size of the rootfs partition by removing
 * unwanted packages, pre-builds, third-party software / libraries, unit test applications, and so on.<br>
 * Note that the cutdown should be based on the customer's real use case.<br>
 * After simplification, check the compiled image size in the out directory `ls -h images/rootfs.ubifs`,
 * then modify the rootfs partition size.<br>
 * The `AMBOOT_PARTITION_LAYOUT` partition size is defined in the board support package (BSP) / bsp.h:
 * @code {.c}
 * #define AMBOOT_PARTITION_LAYOUT	\
 *              MEDIA_DEV \
 *              "128k(bst),128k(bl2),2048k(fip),896k(dtb),896k(env),128k(cfg)," \
 *              "32m@0x1300000(kernel),192m(rootfs),-(raw)"
 * @endcode
 *
 * @subsubsection kernel_size 2.3.2 Reduce Linux Kernel Size
 * The purpose of streamlining the kernel is to manage modules that are not required
 * in the boot phase. Users can choose not to directly build them into the kernel, but into separated
 * module drivers (change from 'Y' to 'M'). Then, load them dynamically after system boots up.
 * This can reduce the time required to load the kernels. Users can change other file system support to another type
 * other than rootfs (such as network file systems) to dynamically load.
 * It is also possible to pursue a faster startup without compiling other drivers that are not required.
 * Users can refer to `ipcam_cleanboot_kernel_emmc_lp4/5_config`.
 *
 * @subsubsection squashfs_select 2.3.3 Select SquashFS as Rootfs
 * Using SquashFS as the rootfs will further reduce the system boot time, as compared to the Unsorted Block Image File System (UBIFS).
 * In some cases, when using NAND, SquashFS can reduce the time by around 500 ms.
 *
 * @subsubsection console_log 2.3.4 Reduce System Startup Serial Port Printing
 * Add the parameter "quiet" to the command line; for example:<br>
 * `console=ttyS0 noinitrd root=/dev/mmcblk0p6 rw rootfstype=ext4 rw rootfstype=ext4 rootwait pci=nomsi pcie_aspm=off quiet`.<br>
 * This will greatly reduce the time required to print information through the serial port
 * when the system starts.<br>
 * Users can add it in `CONFIG_AMBOOT_BD_CMDLINE` in menuconfig, as follows:
 *
 * Or, modify it in `bsp/xxx.dts`, as follows:
 * @code {.c}
 *	chosen {
 * #if defined(CONFIG_BOOT_MEDIA_SPINOR)
 *     bootargs = "console=ttyS0 root=/dev/mtdblock5 rw rootfstype=jffs2";
 * #else
 *     bootargs = "console=ttyS0 noinitrd root=/dev/mmcblk0p6 rw rootfstype=ext4 rw rootfstype=ext4 rootwait pci=nomsi pcie_aspm=off quiet";
 * #endif
 * 	};
 * ........
 * @endcode
 *
 * @subsection clean_boot_others 2.4 Other Optimization Measures
 *
 * @subsubsection others_reduce_delay 2.4.1 Reduce Delay of Peripheral Driver Loading
 * Some peripheral drivers have software delays (calling `sleep()` or `delay()`) when loading.
 * For example, the SD card driver can be delayed by hundreds of milliseconds upon power-up,
 * which can be appropriately reduced according to actual requirements and after assessing risks.
 *
 * @subsubsection others_increase_i2c_clock 2.4.2 Increase I2C Clock Frequency
 * To increase the speed of I2C communication for some peripherals, such as the sensor,
 * users can also modify the I2C clock frequency (modify `ambarella-xxx.dtsi`).
 * Currently, the CV72 platform can support up to a 1-MHz clock.
 *
 * @subsubsection others_nand_timing 2.4.3 Adjust NAND Timing
 * Adjust NAND timing by modifying `bsp/xxx.ini`.
 *
 * @subsubsection others_emmc_boot 2.4.4 Adjust eMMC Power-On Configuration as HS200 8-bit Mode
 * Adjust the embedded multi-media controller (eMMC) power-on configuration (POC) as HS200 8-bit mode to boot up.
 * Select HS 8-bit mode for the bootloader (BLD) in menuconfig.
 * @par For Cooper SDK Amba Build:
 * @code {.c}
 * build $ make menuconfig
 *         boot --->
 *             Ambarella Bootloader Configuration --->
 *                 Hardware Options --->
 *                     [*] Support SD Driver --->
 *                         EMMC Bus Mode (HS200) --->
 *                         EMMC Bus Width (8) --->
 * @endcode
 * @par For Cooper SDK Yocto Build:
 * @code {.c}
 * build $ make menuconfig
 *         meta-ambabsp --->
 *           recipes-bsp --->
 *             amboot (meta-ambabsp/recipes-bsp/boot) --->
 *               Ambarella Bootloader Configuration --->
 *                   Hardware Options --->
 *                     [*] Support SD Driver --->
 *                       EMMC Bus Mode (HS200)
 *                       EMMC Bus Width (8)
 * @endcode
 *
 *
 * @subsection clean_boot_test 2.5 Testing Process
 * Ambarella recommends measuring the time difference between the general purpose input / output (GPIO) pin level flip
 * through the oscilloscope.
 * When the first `dsp_encode_irq` arrives, a high level is generated through a test pin,
 * and the time difference between it and the reset high level is measured; that is, it measures
 * the accurate time from system start-up to plot.
 *
 * @subsection clean_boot_example 2.6 Example
 * @code {.c}
 * build $ make ipcam_cleanboot_kernel_emmc_lp4/5_config
 * @endcode
 * On the CV72 evaluation kit (EVK), the boot-up time from system power-up to the first `dsp_encode_irq`
 * has been measured to be about 1.3 seconds (`cortex_clock`: 1608 MHz, `core_clock`: 624 MHz, sensor: OS08A10).
 *
 * - - - -
 *
 * @section sys_fb_dram_refresh 3. DRAM Self-Refresh
 * When the DRAM self-refresh feature is enabled, the system operates in low-power mode.
 * During suspension, all hardware (except DRAM) is powered off. This feature is
 * supported in CV72. DRAM self-refresh functions with both the normal boot
 * flow and the secure boot / Arm® TrustZone® flow.
 *
 * @subsection sys_pm_dram_flow 3.1 Self-Refresh Workflow
 * @subsubsection sys_pm_dram_resume_flow 3.1.1 Self-Refresh Resume Workflow
 * Starting from the bootstrapper (BST), normal self-refresh and secure self-refresh share many of
 * the same resume-flow components.
 * @image html normal_boot_self_refresh_flow.png "Figure 3-1. Normal Boot DRAM Self-Refresh Resume Workflow for the SoC."
 * For a detailed overview of the secure boot flow, refer to the <em>Ambarella DG Flexible Linux
 * SDK Security Overview</em> document.
 * @image html secure_boot_dram_selrefresh_flow.png "Figure 3-2. Secure Boot DRAM Self-Refresh Resume Workflow for the SoC."
 * The following figure shows the MCU workflow on DRAM self-refresh resume:
 * @image html self_refresh_resume_mcu_workflow.png "Figure 3-3. DRAM Self-Refresh Resume Workflow for the MCU."
 *
 * @subsubsection sys_pm_dram_suspend_flow 3.1.2 Self-Refresh Suspend Workflow
 * The following figure shows the SoC workflow on DRAM self-refresh suspend:
 * @image html self_refresh_suspend_soc_workflow.png "Figure 3-4. DRAM Self-Refresh Suspend Workflow for the SoC."
 * The following figure shows the MCU workflow on DRAM self-refresh suspend:
 * @image html self_refresh_suspend_mcu_workflow.png "Figure 3-5. DRAM Self-Refresh Suspend Workflow for the MCU."
 *
 * @subsection sys_pm_hw_config 3.2 Hardware Configuration
 * @subsubsection sys_pm_hw_powctl 3.2.1 Power Control
 * Self-refresh must function with power control (PWC). PWC can be used in two ways:
 *      - Internal PWC (not all SoCs include an internal PWC)
 *      - External PWC (an external MCU must be used when the SoC does not have an internal PWC)
 *
 * If the board design uses an external MCU for the power sequence control, the SoC must communicate
 * with the MCU through a GPIO.
 *
 * The protocol is as follows:
 *      - The SoC generates a rising signal to notify the MCU that the SoC will enter into self-refresh.
 *      - The MCU then notifies the SoC of the state after being powered on:
 *        - If from a cold boot, MCU keeps the GPIO high
 *        - If resumed from self-refresh, MCU keeps the GPIO low
 *
 * Different board designs may use different GPIOs. Both the BST and kernel must know which GPIO
 * is used in order to communicate with the external MCU.
 *      - For BST, the GPIO is defined in the .ini file by `PARAM_SOC_NOTIFY_MCU_GPIO`. For more
 *        details, users can refer to @ref sys_pm_hw_ini "Section 3.2.2 INI File" below
 *
 * @subsubsection sys_pm_hw_ini 3.2.2 INI File
 * In the .ini file, there are two fields related to self-refresh: the `PARAM_SOC_NOTIFY_MCU_GPIO` value and
 * the `PARAM_MCU_NOTIFY_SOC_GPIO` value. For different boards, the GPIO setup will be different:
 *
 * -# For the @b CV72 Gage board:
 * @code {.c}
 * <PARAM_SOC_NOTIFY_MCU_GPIO value="16"/>
 * <PARAM_MCU_NOTIFY_SOC_GPIO value="15"/>
 * @endcode
 *
 * @subsection sys_pm_preimg 3.3 Prepare the Image
 * The DRAM self-refresh function is supported on the CV72 board.
 * To enable this function, users must have the corresponding MCU code and the CV72 firmware binary.
 * Before compiling, ensure that the peripheral component interconnect (PCI) and Cadence USB are disabled.
 * @code {.c}
 * build $ make linux_menuconfig
 *         Device Drivers --->
 *             [ ] PCI support ---
 *             [*] USB support --->
 *                 < > Cadence USB Support
 * @endcode
 *
 * Use the following commands to compile the firmware that supports normal DRAM self-refresh:
 * @code {.c}
 * build $ make ipcam_lp4/5_srs_config
 * build $ make
 * @endcode
 *
 * @subsection sys_pm_run_dram 3.4 Running DRAM Self-Refresh
 * @subsubsection sys_pm_run_dram_prehw 3.4.1 Preparing the Hardware
 * Users should ensure that the external MCU is flashed with code that supports the DRAM self-refresh
 * functionality.
 * Meanwhile, the power selection jumper should be shorted in order to enable power management from the MCU.<br>
 * For the @b CV72 Gage board, connect the @b J80 pins.
 *
 * @subsubsection sys_pm_run_dram_entersr 3.4.2 Enter Into Self-Refresh
 * Power on the system using the [PS-ON] button, and then enter the following commands:
 * @code {.c}
 * board # init.sh --na
 * board # modpeobe os08a10 vinc_id=8
 * board # test_aaa_service -a &
 * board # test_encode --idle --nopreview
 * board # echo mem > /sys/power/state
 * @endcode
 *
 * @note
 * DRAM self-refresh does not support resume-from-preview mode; use `test_encode`
 * to enter preview after resuming from idle mode.
 *
 * The sequence of commands listed above is used to perform the suspend operation, in which all
 * device modules will save the current scenario information (with the exception of the information
 * inside the DRAM). This information includes hardware configurations, states, and other scenario-
 * specific information.
 *
 * @subsubsection sys_pm_run_dram_resume 3.4.3 Resume from Self-Refresh
 * The resume operation is executed by pressing the <b>MCU PWRON</b> button on the EVK board. This operation
 * restores the hardware registers and states, in addition to recovering the state of the camera.
 *
 * - - - -
 *
 * @section fastboot_license 4. License
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
 * @file doc_sensor_calibration_user_guide.h
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
 * @page page_sensor_calib_user_guide_doc DESIGN - Multiple Sensors Calibration
 *
 * @section guide_sensor_calib_history 0. Revision History
 *
 * <table>
 * <caption id="Sensor calibration user guide"></caption>
 * <tr><th> Tool Name   <th> Tool Version   <th align="left">Updated Date<th align="left">Tool Platform<th align="left"> Modification
 * <tr><td> Lens_calib  <td>  0.0.1            <td>       20210902               <td>armv8-a / x86             <td>Initial Version
 * <tr><td> Lens_calib  <td>  0.1.2            <td>       20210921               <td>armv8-a                   <td>Refine lens calibration flow
 * <tr><td> Lens_calib  <td>  2.0.1            <td>       20210924               <td>x86                       <td>Added Section @ref guide_sensor_calib_structure_light "Structured-light Parameters Pose Calibration"
 * <tr><td> Lens_calib  <td>  2.0.2            <td>       20211102               <td>x86                       <td>Add support for @ref sensor_calibtof_temp_calib "Temperature Calibration"
 * <tr><td> Lens_calib  <td>  2.0.2            <td>       20211124               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_lens "Lens Calibration"
 * <tr><td> Lens_calib  <td>  2.0.2            <td>       20211207               <td>armv8-a / x86             <td>Updated Section @ref lens_calib_flow "Lens Calibration Flow"
 * <tr><td> Lens_calib  <td>  2.0.3            <td>       20211210               <td>armv8-a / x86             <td>Updated Section @ref lens_calib_flow "Lens Calibration Flow"
 * <tr><td> Lens_calib  <td>  2.0.3            <td>       20211210               <td>armv8-a / x86             <td>Updated Section @ref stitching_pose_tool "Multi-Sensor Stitching Pose Calibration Tool"
 * <tr><td> Lens_calib  <td>  2.0.3            <td>       20211216               <td>armv8-a / x86             <td>Updated Section @ref sensor_calib_introduction "Introduction"
 * <tr><td> Lens_calib  <td>  2.0.4            <td>       20211216               <td>armv8-a / x86             <td>Updated Section @ref lens_calib_flow "Lens Calibration Flow"
 * <tr><td> Lens_calib  <td>  2.0.4            <td>       20211216               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_preparation "Calibration Preparation Work"
 * <tr><td> Lens_calib  <td>  2.0.4            <td>       20220119               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_lens "Lens Calibration"
 * <tr><td> Lens_calib  <td>  2.0.4            <td>       20220119               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_stitch "Stitching Pose Calibration"
 * <tr><td> Lens_calib  <td>  2.0.4            <td>       20220124               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_faq "Sensor Calibration FAQ"
 * <tr><td> Lens_calib  <td>  2.0.4            <td>       20220126               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_faq "Sensor Calibration FAQ"
 * <tr><td> Lens_calib  <td>  2.0.5            <td>       20220127               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_lens "Lens Calibration"
 * <tr><td> Lens_calib  <td>  2.0.5            <td>       20220211               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_lens "Lens Calibration"
 * <tr><td> Lens_calib  <td>  2.0.5            <td>       20220217               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_lens "Lens Calibration"
 * <tr><td> Pose_calib  <td>  1.0.0            <td>       20221130               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_dual_fish "Dual-fisheye back to back Pose Calibration"
 * <tr><td> Lens_calib  <td>  2.0.6            <td>       20221201               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_lens "Lens Calibration"
 * <tr><td> Lens_calib  <td>  2.0.7            <td>       20230206               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_lens "Lens Calibration"
 * <tr><td> Lens_calib  <td>  2.0.8            <td>       20230208               <td>armv8-a / x86             <td>Updated Section @ref guide_sensor_calib_lens "Lens Calibration"
 * </table>
 *
 * - - - -
 *
 * @section guide_sensor_calib_introduction 1. Introduction
 *
 * This chapter introduces the basic information on different sensor calibrations.
 *     - Section @ref guide_sensor_calib_preparation
 *     - Section @ref guide_sensor_calib_lens
 *     - Section @ref guide_sensor_calib_tof
 *     - Section @ref guide_sensor_calib_tof_rgbd
 *     - Section @ref guide_sensor_calib_stitch
 *     - Section @ref guide_sensor_calib_thermal_rgb
 *     - Section @ref guide_sensor_calib_mono_rgb
 *     - Section @ref guide_sensor_calib_structure_light
 *     - Section @ref guide_sensor_calib_faq
 *     - Section @ref guide_sensor_calib_lic
 *
 * - - - -
 *
 * @section guide_sensor_calib_preparation 2. Calibration Preparation Work
 * @subsection sensor_calib_prepare 2.1 Preparing Work
 *     - @ref sensor_calib_prepare_host
 *     - @ref sensor_calib_prepare_board
 *     - @ref sensor_calib_prepare_pat
 *
 * @subsubsection sensor_calib_prepare_host 2.1.1 Host Calibration Tool
 *
 * Host calibration tool supports the following features : <br>
 * - @ref guide_sensor_calib_lens
 * - @ref guide_sensor_calib_tof
 * - @ref guide_sensor_calib_tof_rgbd
 * - @ref guide_sensor_calib_structure_light
 *
 * The host calibration tool is used to manage time-consuming problems. <br>
 * Ambarella supports performing both lens and pose calibration on the PC Linux side and on the Windows side. <br>
 * Ambarella recommends performing lens / pose calibration on the PC Windows side to save environment installation time.
 * <b>(1) PC Windows side lens calibration tool:</b> <br>
 * Windows environment: Win10, x64 <br>
 * Lens calibration tools: cv2x_cv5x_lens_calibration_tool_for_windows_vx.x.x_x.tar.bz2 <br>
 * Pose calibration tools: cv2x_cv5x_pose_calibration_tool_for_windows_vx.x.x_x.tar.bz2 <br>
 * If users want to perform calibration on the PC Windows side, they must ask the Ambarella support team for the required tools.
 *
 * <b>(2) PC Linux side lens calibration tool:</b> <br>
 * The lens calibration tool is in the path below: <br>
 * ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool <br>
 * Some descriptions of the key libraries of the calibration are as follows : <br>
 *  | Name | Version | Calibration type |
 *  | :----: | :----: | :----: |
 *  | OpenCV | 3.2.0  | ALL |
 *  | Apriltag | 2018-11-29  | Lens / multi-sensor pose / structured-light pose calibration |
 *  | Ceres solver | 1.14.0  | Binocular|
 *  | Python | 2.7  | ToF |
 *  | Matplotlib | --  | ToF |
 *
 * 1. Install the dependency libraries.
 * @code {.c}
 * build $ sudo ./host_tool_install.sh
 * @endcode
 *
 * 2. The calibration is based on the OpenCV 3.2.0 version. Ensure that the correct
 * version for OpenCV is installed on the host Ubuntu building machine.
 * Use the following reference to install the OpenCV package.
 * First, download the opencv3.2.0.tar.gz source code package from the website: https://opencv.org/opencv-3-2.html.
 * @code {.c}
 * build $ tar -xzvf opencv-3.2.0.tar.gz
 * build $ cd opencv-3.2.0/
 * build $ sudo mkdir -p build
 * build $ cd build/
 * build $ cmake ../
 * build $ sudo sudo make
 * build $ sudo make install
 * @endcode
 *
 * 3. Users should also install the apriltag library to use the circle target, and the version should be apriltag-2018-11-29.
 * Save the library in the path  multi_sensor_calib/host_calib_tool/third_party . Compress it and run, as follows:
 * @code {.c}
 * build $ sudo make all
 * build $ sudo make install
 * @endcode
 *
 * 4. If users want to perform binocular calibration, Ceres Solver is required for installation.
 * Ceres Solver is used for optimization; download it from
 * https://github.com/ceres-solver/ceres-solver. Ambarella uses version 1.14.0.
 * Some dependencies can be refered to host_tool_install.sh. Compress it and run:
 * @code {.c}
 * build $ sudo cmake ../ceres-solver-1.14.0
 * build $ sudo make
 * build $ sudo make install
 * @endcode
 *
 * 5. If users want to perform time of flight (ToF) calibration, users must install the library:
 * @code {.c}
 * build $ sudo pip install matplotlib
 * @endcode
 *
 * @subsubsection sensor_calib_prepare_board 2.1.2 Board Calibration Tool
 * Libsensor_calib.so is the tool, which supports the following features: : <br>
 *  - @ref guide_sensor_calib_stitch
 *  - @ref guide_sensor_calib_thermal_rgb
 *  - @ref guide_sensor_calib_mono_rgb
 *
 * The calibration tool should be configured in menuconfig.
 * Follow the instructions as shown below
 * @par For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * Configure libsensor_calib.so.
 * build # make menuconfig
 * [*] Ambarella Prebuild  --->
 * 	[*] Configure Ambarella sensor calibration library
 *
 * Configure test_stitch and libstitch.so.
 * build # make menuconfig
 * [*] Ambarella Prebuild  --->
 * 	[*] Configure Ambarella stitch library
 *
 * Configure test_sensor_calib and libmsc_ini.so.
 * build # make menuconfig
 * [*]  Ambarella Package Configuration  --->
 * 	 -*-   Build Ambarella sensor calibration ini parser library
 *
 * Users must specify the maximum channel number accordingly.
 * build # make menuconfig
 *     drv_modules  --->
 *          private  --->
 *           -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *               (4)   Max VIN Channel Number
 *
 * @endcode
 *
 * @par For Cooper Amba build:
 * @code {.c}
 * Configure test_sensor_calib and libsensor_calib.so
 * build # make menuconfig
 *     prebuild --->
 *       library --->
 *         [*] prebuild-sensorcalib (prebuild/library/multi_sensor_calib/dsp_v5)
 *         [*] sensorcalib-test (prebuild/library/multi_sensor_calib/dsp_v5)
 *
 * Configure test_stitch and libstitch.so
 * build # make menuconfig
 *     prebuild --->
 *       library --->
 *         [*] prebuild-stitch (prebuild/library/stitch_algo/dsp_v5)
 *         [*] stitch-test (prebuild/library/stitch_algo/dsp_v5)
 *
 * Configure libmsc_ini.so
 * build # make menuconfig
 *     package --->
 *       [*] libmsc (packages/sensor_calib_ini_parser/armv8-a)
 *
 * Users must specify the maximum channel number accordingly.
 * build # make menuconfig
 *     drv_modules --->
 *       private --->
 *         -*- ambavideo-header (drv_modules/private/video/dsp_v5) --->
 *           (4) Max VIN Channel Number
 *
 * @endcode
 *
 * The board calibration tool is in the path <br>
 * ambarella/prebuild/ambarella/library/multi_sensor_calib/lib/armv8-a/ <br>
 * The source code of application "test_sensor_calib" is in the path <br>
 * ambarella/unit_test/private/package_test/arch_v5/test_sensor_calib.cpp <br>
 *
 * @subsubsection sensor_calib_prepare_pat 2.1.3 Pattern Preparing Work
 * Users require different patterns for different calibrations. <br>
 * Some descriptions of the key points detection method of the calibration are as follows <br>
 *  | Calibration Type | Tool (Pattern) |
 *  | :----: | :----: |
 *  | Lens | Circle board / chessboard  |
 *  | ToF | Laser board / chessboard  |
 *  | RGBD | chessboard  |
 *  | Stitch pose | Circle board / chessboard  |
 *  | Thermal-RGB | Choose the points manually  |
 *  | Mono-RGB | Akaze algorithm to detect the keypoints automatically |
 *  | Structured-light | Circle board  |
 *
 * @image html circle_pattern.jpg "Figure 2-1. Circle Pattern."
 * @image html chess_pattern.jpg "Figure 2-2. Chess Pattern."
 * In order to maintain accuracy, Ambarella recommends following the rules below. <br>
 * - Paste the pattern flat on the board <br>
 * - Use sufficient amounts of light <br>
 *
 * The circle pattern image shows each calibration board contains four April tags and many circles. <br>
 * <b>Key notes for the circle board:</b>
 * - The diameter of each circle in the picture is between 15 and 20 pixels (20 is ideal, 10-20 is also sufficient). A larger size can cause loss in accuracy.
 * - Ambarella recommends using at least one April tag in each image.
 * - When the pattern board is sufficiently rigid and flat, users should use a ruler to measure the horizontal length (width) between the horizontal triangle strip-line symbols and <br>
 * the vertical length (height) between the vertical triangle strip-line symbols. <br>
 * Based on this data, users can obtain an average distance between the adjacent circles for the horizontal and vertical directions in order to increase accuracy.
 * The example below is in meters. <br>
 * Horizontal spacing = width / 46 <br>
 * Vertical spacing = height / 32 <br>
 * <b>Lens calibration:</b> Fill the spacing command information "-tag_info_list" for the application "lens_calib.exe" in run_xx_circle_xx.bat. <br>
 * <b>Pose calibration:</b> Fill the spacing command information "-tag_info" for the application "test_sensor_calib.exe" in sensor_calib_ini_pose_calibration_save_target_xx.ini
 * or command line directly. <br>
 * - - - -
 *
 * @section guide_sensor_calib_lens 3. Lens Calibration
 * This chapter describes the following concepts:
 *     - @ref lens_calib_principle
 *     - @ref lens_calib_tool
 *     - @ref lens_calib_flow
 *     - @ref lens_calib_result
 *
 * @subsection lens_calib_principle 3.1 Lens Calibration Principle
 * Users should perform lens calibration to remove distortions because there are radial and tangential distortions for each lens.
 * @image html distortion.jpg "Figure 3-1. Distortion for Lens."
 * The image above shows that the table will be twisted because of lens distortion.
 * This chapter provides information on how to perform lens calibration.
 *
 * @subsection lens_calib_tool 3.2 Lens Calibration Tool
 * Ambarella supports performing lens calibration on both the PC Linux side and on the Windows side.
 * Users can obtain lens calibration applications for the Windows side in the path below:. <br>
 * Environment: Win10, x64
 * Tool: cv2x_cv5x_lens_calibration_tool_for_windows_vx.x.x_x.tar.bz2
 *
 * @subsection lens_calib_flow 3.3 Lens Calibration Flow
 * <b>Multi-channel stitching lens calibration strategy:</b>
 * Ambarella recommends performing full calibration for the specific lens (with <b>60+</b> images) and <br>
 * perform fast calibration for the other channel (as in case 7 mentioned above, the results of full calibration are used as initial parameters to estimate other lenses).
 *
 * @image html lens_calib.jpg "Figure 3-2. Calibration for Pinhole Lens."
 * <b>1) Capture image sets</b><br>
 * The image above shows some pattern's positions when users perform the calibration.
 * Ambarella suggests using the Zhang Zhengyou calibration method for pinhole and fisheye lens.
 * It is recommended to use omnidirectional calibration method when the FoV is greater than 180 degrees.
 * The calibration process requires users to capture more than <b> 60 </b> pictures as shown in the image. <br>
 * Key points for lens calibration:
 * - The diameter of each circle in the picture is between 15 and 20 pixels (20 is ideal, 10-20 is also sufficient). A larger diameter will cause loss in accuracy.
 * - Ambarella recommends using at least one April tag for each image.
 * - Cover images in different parts of the FoV.
 * - If users must quickly perform calibration, Ambarella recommends covering many targets in the image.
 * - The tool supports both chessboard and circle patterns to perform calibration.
 * - Ambarella recommends capturing images at three different distances, such as 1.5 / 2 / 2.5 meters.
 * - Move the board in different angles (pitch / roll / yaw); however, the angles should not be too large. Refer to the image above.
 * - The tool supports performing lens calibration with multiple patterns in one image.
 *
 * For CV2x, the user should copy get_frame.sh and calib_3x_chan.lua/calib_4x_chan.lua to the "/root" directory of the board. <br>
 * For CV5x, the user should copy yuv_capture.sh and cv5x_4vin_capture_yuv.lua to the "/root" directory of the board. <br>
 * yuv_capture.sh is used to capture YUV data for each channel. <br>
 * The scripts creates in ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/script/stitch/cvxx/capture. <br>
 * CV2x: <br>
 * @code {.c}
 * board # cd /root
 * board # init.sh --na && modprobe imx335_mipi vinc_id=0xf1320 slave=1 (the user should modify the command accordingly)
 * board # test_aaa_service -a&
 * board # test_encode -i 0 --enc-mode 0 --debug-stitched 1 --vsync-detect-disable 0 --resource-cfg calib_4x_chan.lua --raw-capture 1
 * board # test_encode -A -h 1920x1080 -b 0 --rotate 1 -e -B -h 1920x1080 -b 1 --rotate 1 -e -C -h 1920x1080 -b 2 --rotate 1 -e -D -h 1920x1080 -b 3 --rotate 1 -e (the user should modify the command accordingly)
 * board # ./get_frame.sh 3 0 15
 * The first option "3" is the number of channels.
 * The second option: 0: capture YUV and JPEG
 *                    1: capture JPEG (Suggested, should enter the encoding state first)
 *                    2: capture YUV
 * The third option "3" is the number of JPEG / YUV data to be captured.
 * @endcode
 *
 * CV5x: <br>
 * @code {.c}
 * board # cd /root
 * board # modprobe ambrg
 * board # modprobe max9296 id=0x0303 vinc_id=0xb8
 * board # modprobe os08a10_mipi_brg fsync=1
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg cv5x_4vin_capture_yuv.lua --raw-capture 1
 * board # ./yuv_capture.sh 0 0 30
 * The first option "0" is the number of channels.
 * The second option "0" is the start index.
 * The third option "30" is the end endex.
 * @endcode
 *
 * This script will create sub-folders under the "/tmp" folder with the name "calib_data".
 * After the picture capture process is complete, copy the calib_data folders to
 * the building machine in the "host_calib_tool/" folder.
 * Commands are as follows:
 *
 * <b>2) Perform the full lens calibration at the PC Windows side</b> <br>
 * Some descriptions of the parameters can be found in ".bat".
 *  | Options | Tool (Pattern) |
 *  | :----: | :----: |
 *  | opt | Specify the focal length of the lens (mm x 10) |
 *  | cel_size | Specify the cell size of the sensor |
 *  | debug | Bit 0: show outlier information. Bit 1: show undistorted image. Bit 2: show tag information. Bit 3: show grid image. Bit 4:: show circle / object information. |
 *  | chess_w / chess_h | Specify the chessboard width / height |
 *  | start / end | Specify the start / end index for lens calibration |
 *  | pic_format | Specify the pictures format |
 *  | input_folder | Specify the folder of the "jpeg / png" format images |
 *  | tag_info_list | Set the April tag information |
 *  | dst | Set the maximum distance in circle detection |
 *  | yuv_w / yuv_h | Set the YUV width / height |
 *  | read_calib | Specify performance of fast lens calibration |
 *  | fix_distort | Specify use of full lens calibration's distortion parameters |
 *  | expand_fov | 0: normal intrinsic parameters, 1: horizontal optimization parameters, 2: vertical optimization parameters, 3: horizontal optimization. |
 *  | k1 / k2 / k3 / k4 / k5 / k6 / k7 | Set the distortion parameter "k" to 0. Ambarella suggests setting k4 / k5 / k6 when the lens is a low-distortion pinhole lens |
 *  | save_undistort_map | Specify saving the undistorted x/y map. |
 *  | slope_ratio | Set the maximum slope difference with the basis when removing the wrong connection |
 *  | start_ratio | Set the vector maximum ratio when detecting the origin. |
 *  | line_ratio | Set the threshold of removing the wrong connection in the incline direction |
 *  | min_area | Set the threshold for detecting small radius circle on the calibration pattern |
 *  | lens_mode | Set the lens calibration mode. 0: fisheye KB mode, 1: fisheye MEI mode, 2: fisheye OCAM mode, 3: PINHOLE |
 *  | map_align | Specify the alignment for the undistorted x/y map to be saved |
 *
 * @code {.c}
 * host (Windows) $ Decompress cv2x_cv5x_lens_calibration_tool_for_windows_vx.x.x_x.tar.bz2
 * Case 1: do full lens calibration for lens 1 with chessboard pattern in YUV or JPG format.
 * host (Windows) $ run_calib_chess_jpg.bat (Suggested)
 * host (Windows) $ run_calib_chess_yuv.bat
 * Case 2: do full lens calibration for lens 1 with circle pattern in YUV format.
 * host (Windows) $ run_calib_circle_yuv.bat
 * Case 3: do full lens calibration for lens 1 with multiple circle patterns in JPEG format.
 * host (Windows) $ run_calib_mutli_board.bat
 * It is suggested to set expand_fov as 1 for horizontal stitching, and expand_fov as 2 for vertical stitching when
 * option "debug" is set to show undistort images.
 * Case 4: do full lens calibration for fisheye lens in JPEG format.
 * host (Windows) $ run_calib_chess_jpg_fisheye.bat
 * @endcode
 * The intrinsic parameters for specified lens will be stored in the relative path lens_calib1/out/front_end/intrinsic_0
 *
 * <b>3) Perform the fast lens calibration at the PC Windows side (using a four-channel stitching as an example)</b> <br>
 * Fast calibration uses the full calibration's intrinsic as initial parameters to estimate the other lens.
 * The tool supports performing fast calibration with only a few images (3 - 4).
 * Ambarella recommends placing the calibration board in the left / middle / right of the image. <br>
 *
 * @image html multi_board.jpg "Figure 3-3. Fast Calibration with Multiple Calibration Boards."
 * The tool supports performing fast calibration with many patterns in one image. <br>
 * - Use different April tag IDs for each calibration board. <br>
 * - Keep the boards in different angles (pitch / yaw / roll). The angles should not be too large; refer to the image above. <br>
 *
 * @code {.c}
 * host (Windows) $ Decompress cv2x_cv5x_lens_calibration_tool_for_windows_vx.x.x_x.tar.bz2
 * Case 1: do fast lens calibration for lens 1 with 3 images (single calibration board).
 * host (Windows) $ Copy "calib_example\circle\lens1\out\front_end" to "calib_example\circle\lensx\out\front_end".(lensx: x = 0, 1, 2, 3)
 * host (Windows) $ cd "calib_example\circle\lensx\out\front_end" (lensx: x = 0, 1, 2, 3)
 * host (Windows) $ Create folder "initial"
 * host (Windows) $ Copy "intrinsic_0" generated in the stage of full lens calibration to the folder "initial".
 * host (Windows) $ Edit "run_fast_calib_circle_yuv.bat" and modify -folder="../calib_example/circle/lens1" to -folder="../calib_example/circle/lensx". (lensx: x = 0, 1, 2, 3)
 * host (Windows) $ Edit "run_fast_calib_circle_yuv.bat" and modify -yuv_name="1_canvas1_wxh_NV12" to -yuv_name="x_canvasx_wxh_NV12". (canvasx: x = 0, 1, 2, 3)
 * host (Windows) $ Double click "\script\run_fast_calib_circle_yuv.bat"
 * host (Windows) $ Rename "calib_example\circle\lensx\out\front_end\intrinsic_0" as "intrinsic_x". (lensx: x = 0, 1, 2, 3), (intrinsic_x: x = 0, 1, 2, 3)
 * Case 2: do fast lens calibration for lens with 1 image only.  (four calibration boards included).
 * host (Windows) $ Double click "\script\run_fast_calib_circle_multi_board_yuv.bat"
 * @endcode
 *
 * Note that if users want to apply lens calibration parameters after fast calibration,
 * they must generate pose calibration parameters again for all channels based on new lens
 * calibration parameters. Then, place all channels' results to the "front_end" folder.
 * Copy the "front_end" folder to the board, and apply the parameters then:
 * @code {.c}
 * It is assumed that the parameters will be applied on channels 0, 1, 2, and 3.
 * board # test_sensor_calib --mode 2 --channel-num 4 -f ./
 * board # test_stitch --mode 2 -f . --no-overlap --fuse-channel 0xf (no overlap part)
 * board # test_stitch --mode 2 -f . (overlap)
 * @endcode
 *
 * @subsection lens_calib_result 3.4 Lens Calibration Result
 * @image html before_after_ldc.jpg "Figure 3-4. Before and After Lens Distortion Calibration."
 * The image shows the contrast result after applying the calibration intrinsic and distortion paramters. <br>
 * The curved line becomes a straight line.
 *
 * - - - -
 *
 * @section guide_sensor_calib_tof 4. ToF Calibration
 * This chapter describes the following conceptions:
 *     - @ref tof_principle
 *     - @ref tof_tool
 *     - @ref tof_flow
 *     - @ref tof_result
 *
 * @subsection tof_principle 4.1 ToF Calibration Principle
 * Users should perform the calibration as shown in the steps below: <br>
 * <b>1) Lens calibration</b> <br>
 * This calibration is used to remove the lens' distortion; each pixel will be converted into
 * the ideal coordinate in the pin-hole model. <br>
 * Refer to @ref guide_sensor_calib_lens "2. Lens Calibration" for more details of removing the distortion. <br>
 * <b>2) Temperature calibration</b> <br>
 * There is a phase drift introduced by the temperature. It is a linear drift in distance.
 * Temperature calibration is used to remove such problem by doing curve-fitting. <br>
 * <b>3) Global calibration</b> <br>
 * There is a global offset between the measured distance and the real distance. <br>
 * Users just need the chessboard or some other calibration targets to do extrinsic
 * calibration and get ground truth distance. <br>
 * <b>4) Wiggling calibration</b> <br>
 * The phase delay can not be calculated correctly because the modulation wave shape
 * is not as perfect as the sinusoidal shape. <br>
 * The imperfect phase will introduce the wiggling errors for different distances.
 * Wiggling calibration is used to remove such problem. <br>
 *
 * @subsection tof_tool 4.2 ToF Calibration Tool
 * Path: ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/bin/x86_64 <br>
 * Path: ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/script/tof <br>
 * Tool: create_xml / lens_cali / tof_cali / do_temp_calib.py <br>
 *
 * @subsection tof_flow 4.3 ToF Calibration Flow
 * It is assumed that the lens calibration has been completed perfectly before this stage;
 * the section introduces the flow of ToF calibration.
 *     - @ref sensor_calibtof_temp_calib
 *     - @ref sensor_calibtof_global_calib
 *     - @ref sensor_calibtof_wiggle_calib
 *
 * @subsubsection sensor_calibtof_temp_calib 4.3.1 Temperature Calibration
 * Temperature calibration performs curve-fitting to find good coefficients used in compensation. <br>
 * It is assumed that the calibration data has been stored in accuracy.csv. <br>
 * Modify x = range(37, 48) in do_temp_calib.py for the specific temperature range from the accuracy.csv file.
 * The users can also ignore the bad statics by setting the range.
 * @code {.c}
 * host # python3 do_temp_calib.py
 * @endcode
 * @image html temp_offset.jpg "Figure 4-1. Temperature Calibration Fitting."
 * The first temperature value 37 of x = range(37, 48) is used as the base,
 * and the image shows the fitting result by using the mean distance difference of the base. <br>
 * The tool reports the result: <br>
 * temp_mean0_base:  37  <br>
 * temp_mean0_distance:  0.12938596591621487  <br>
 * line_slopy:  0.00034453650504337203  <br>
 * base: -0.012889773367656475  <br>
 * "temp_mean0_base" is the temperature compensation base of the calibration. <br>
 * "line_slopy" and "base" are the curve-fitting coefficients used for compensation. <br>
 * Fill the parameters "line_slopy" and "base" to amba_itof_decoder or amba_itof_dec_for_calib stage in the .lc file to
 * perform the temperature compensation. <br>
 *
 * @subsubsection sensor_calibtof_global_calib 4.3.2 Global Calibration
 * There is a global offset between the measured distance and the real distance. <br>
 * <b>1) For the short range (0 - 1.5 meters)</b> <br>
 * Ambarella suggests using a chessboard or some other calibration tools to perform extrinsic calibration
 * and get ground truth distance. Users should perform lens calibration first, then fill with
 * intrinsic and distortion parameters to the commands below.
 * The tools are in the path ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool.
 * Users can perform the calibration and choose one value as the global offset value from the report.
 * There are some scripts (run_xxx_xxxMHZ.sh) in the folder "script/tof" for reference;
 * the user can run it by changing some parameters. <br>
 * Some descriptions of the options in the script: <br>
 * "bw" chessboard center numbers in the horizontal direction <br>
 * "bh" chessboard center numbers in the vertical direction <br>
 * "board-square" the side length of a square (unit is meter) <br>
 * "m" ToF frequency in Hz
 * "global-offset" global-offset value, should be 0 for the global calibration. <br>
 * The command in the script is as shown below:
 * There are many reference calibration command scripts in the path multi_sensor_calib/host_calib_tool/script/tof. <br>
 *
 * @code {.c}
 * host # ../../bin/x86_64/tof_cali --mode 2 --show-fit --count 50 -f ../../calib_data/wiggle_20m/ --fx 380.7416486811555
 * --fy 380.7416486811555 --cx 321.0045588907875 --cy 243.8313078372227 --k1 -0.1839007852803311 --k2 0.3616930968794873
 * --p1 0.0002937727395641034 --p2 0.0007998748191078006 --k3 -0.2225507425779707 --show-chess --index 1 --board-start 51
 * --board-end 70 --bw 7 --bh 4 --board-square 0.1933 --control-cnt 20 --use-csv --use-white -m 120000000
 * @endcode
 *
 * The tool supports choosing points manually when the image quality is not well detected.
 * The selection interface appears when the automatic points fail to extract.
 * @image html manual.jpg "Figure 4-2. Find Points."
 * The image shows how to choose the chessboard cross center manually;
 * follow the straight line's direction.
 *
 * <b>2) For the long range (greater than 1.5 meters)</b> <br>
 * Because it is difficult to find too-large calibration parameters, Ambarella recommends that users use a laser to perform the calibration.
 *
 * @code {.c}
 * host # ../../bin/x86_64/tof_cali --mode 3 --show-fit --count 50 -f ../../calib_data/tof/
 * --control-cnt 5 -m 120000000 --global 0.48
 * @endcode
 *
 * @image html global_offset.jpg "Figure 4-3. Global Offset."
 * The image shows how to choose the global offset manually.
 * Choose one value from the fitting image, such as (phase 0.2, offset -0.55),
 * where -0.55 is the global compensation value.
 * Option "global_offset" in the compensation stage of lc file should be filled with 0.55.
 *
 * @subsubsection sensor_calibtof_wiggle_calib 4.3.3 Wiggling Calibration
 * Modulation wave shape is not as perfect as the sinusoidal shape, so the phase delay will not be
 * calculated correctly, and the imperfect phase will introduce the wiggling errors for different
 * distances. It will bring wiggling errors.
 * Taking multiple images can bring more points and improve the accuracy of fitting results.
 * Capture data in small steps from the start to the end position so that it can cover full 360 degree in
 * phase, then perform the wiggling calibration with PC tools with lens calibration results.
 * Enter the folder "script/tof", fill with the global offset value as shown in the command below, and run the command again.
 * @code {.c}
 * host # ../../bin/x86_64/tof_cali --mode 2 --show-fit --count 50 -f ../../calib_data/wiggle_20m/ --fx 380.7416486811555
 * --fy 380.7416486811555 --cx 321.0045588907875 --cy 243.8313078372227 --k1 -0.1839007852803311 --k2 0.3616930968794873
 * --p1 0.0002937727395641034 --p2 0.0007998748191078006 --k3 -0.2225507425779707 --show-chess --index 1 --board-start 51
 * --board-end 70 --bw 7 --bh 4 --board-square 0.1933 --control-cnt 20 --use-csv --use-white -m 120000000 --global -0.311332
 * @endcode
 * The tool will report the following:
 * start base 0.000000, end base 1.008698, end off 0.996727 number 64, step base 0.01601108. <br>
 * Option "fit_num" in the compensation stage of lc file should be filled with 64.
 *
 * @image html wiggle_offset.jpg "Figure 4-4. Wiggling Offset."
 * After the calibration, the data will vibrate around y = 0 axis,
 * and a lookup table (LUT) for specific distance spacing to express distance compensation for different positions will be created.
 * After ToF calibration, calibration data can be used for the ToF process on the chip.
 *
 * @subsection tof_result 4.4 ToF Calibration Result
 * The calibration result is listed in the above section.
 *
 * - - - -
 *
 * @section guide_sensor_calib_tof_rgbd 5. RGBD Registration Calibration
 * This chapter describes the following conceptions:
 *     - @ref rgbd_principle
 *     - @ref rgbd_tool
 *     - @ref rgbd_flow
 *     - @ref rgbd_result
 *
 * @subsection rgbd_principle 5.1 RGBD Registration Calibration Principle
 * Depth-sensing cameras have made it possible to use 3D point clouds
 * in many fields of reasearch and industry. <br>
 * The 2D RGB cameras are used by many algorithms to perform detection and classification. <br>
 * The proposed solution provides a mechanism to calibrate RGB and depth <br>
 * cameras's intrinsic /extrinsic paramters and create an aligned matrix. <br>
 * With applying the aligned matrix, the dpeth image could be converted to the RGB's view in real time.
 *
 * @subsection rgbd_tool 5.2 RGBD Registration Calibration Tool
 * Path ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/bin/x86_64 <br>
 * Tool binocular_cali
 *
 * @subsection rgbd_flow 5.3 RGBD Registration Flow
 * @image html rgbd_calib.jpg "Figure 5-1. RGBD Calibration Image."
 * The image shows the calibration RGB and ToF amplitude images. <br>
 * The flow of calibration is performed in the steps below: <br>
 * 1) Use the Amage tool to read configurations and adjust 3A for amplitude image. <br>
 * 2) Capture the RGB / ToF (amplitude) calibration dataset. <br>
 * Key points for RGBD calibration <br>
 * The calibration process requires users to capture more than <b> 60 </b> pictures as shown in the image. <br>
 * Keep images covered different parts of FoV. <br>
 * Ambarella recommends using a chessboard to perform calibration. <br>
 * Ambarella recommends capturing images at three different distances, <br>
 * such as 1.5 / 1.8 / 2 meters (capture many images at a fixed distance (1.5 meters) and capture three images at a far distance (1.8 / 2 meters)). <br>
 * Keep the board in different angles (pitch / yaw / roll). <br>
 * Ensure that the chessboard is complete in the two channels' images. <br>
 * 3) Perform the RGBD registration calibration. <br>
 * Calibration algorithm is performed as described below: <br>
 * 1) Perform lens calibration for each lens <br>
 * The intrinsic / distortion parameters "intrinsic_x.bin" will be stored in the debug/front_end folder. <br>
 * 2) Perform binocular calibration to get the alignment matrix between RGB and ToF sensors. <br>
 * Lens calibration results will be used as the initial values for binocular calibration; they could be fixed via the
 * "--fix-distort" option. <br>
 * The alignment matrix parameters "align_mat.bin" will be stored in the debug/front_end folder. <br>
 *
 * @code {.c}
 * host # ../../bin/x86_64/binocular_cali -i 0 --width 640 --height 480
 * -i 1 --width 1920 --height 1080  --pattern-mode 0 --chess-sqs 0.03
 * -d 5 --fix-distort --get-align --chess-w 11 --chess-h 8 -s 0 -n 52
 * --l-file l_640x480_nv12_0000000000.yuv_canvas0_640x480_NV12.yuv
 * --r-file l_1920x1080_nv12_0000000000.yuv_canvas2_1920x1080_NV12.yuv
 * @endcode
 * Options descriptions <br>
 * - "--fix-distort" is used to fix the distortion parameters from the lens calibration stage in binocular calibration. <br>
 * - "--get-align" is used to calculate the alignment matrix parameters. <br>
 * - "-d" is used to set numbers of distortion paramters. <br>
 * - "chess-w" is used to set the width of the chessboard. <br>
 * - "chess-h" is used to set the height of the chessboard. <br>
 *
 * @subsection rgbd_result 5.4 RGBD Registration Result
 * @image html rgbd_registration.jpg "Figure 5-2. RGBD Registration."
 * As shown in the image, the depth image is aligned to the RGB sensor and pasted on the RGB's view with overlay.
 *
 * - - - -
 *
 * @section guide_sensor_calib_stitch 6. Multi-sensor Stitching Pose Calibration
 * This chapter describes the following concepts, using a four-channel stitching case as an example.
 *     - @ref stitching_pose_principle
 *     - @ref stitching_pose_tool
 *     - @ref stitching_pose_flow
 *     - @ref stitching_cmd_list
 *     - @ref stitching_pose_result
 *
 * @subsection stitching_pose_principle 6.1 Multi-sensor Stitching Pose Calibration Principle
 * Homograpy matrix is used to express the transformation between two image planes. <br>
 * The calibration is used to get the homograpy matrix and project each channel to the middle image channel. <br>
 * It is assumed that users did lens calibration before this calibration stage. <br>
 * After the pose calibration, users can get the message of configuration (offset / width / height) for each channel. <br>
 *
 * @subsection stitching_pose_tool 6.2 Multi-sensor Stitching Pose Calibration Tool
 * For pose calibration, Ambarella supports performing pose calibration both on PC Windows side and board side.
 * Users can get pose calibration application for Windows side in the path below. <br>
 * Environment: Win10, x64
 * Tool: cv2x_cv5x_pose_calibration_tool_for_windows_vx.x.x_x.tar.bz2
 *
 * Board side path ambarella/prebuild/ambarella/library/multi_sensor_calib/lib/armv8-a <br>
 * Tool libsensor_calib.so <br>
 * Application <br>
 * ambarella/packages/sensor_calib_ini_parser/arch_v5/unit_test/test_sensor_calib.c <br>
 *
 * @subsection stitching_pose_flow 6.3 Stitching Pose Calibration Flow
 * <b>1) Capture image sets</b>
 * @image html pose_calib_layout.jpg "Figure 6-1. Camera Set and Calibration Board Layout."
 * The figure above shows the relative position of camera set and calibration board when users perform the pose calibration. <br>
 * Key points of capturing image sets for pose calibration are listed below:<br>
 * 1: Fix three calibration boards’ distance (from the middle line of each group of two adjacent lens) to the same 1.5 meters. <br>
 * 2: Make sure each calibration board can be perpendicular to the middle line as far as possible. <br>
 * 3: Totally capture four images (the schematics images are shown below) for four lenses respectively. <br>
 * 4: As figures <b>"Camera Set and Calibration Board Layout"</b> and <b>"Four-lens Schematic Images"</b> shown, the overlapping part view of
 * two adjacent channels' must have circles of the calibration board.
 * @image html pose_calib_schematic_image.jpg "Figure 6-2. Four-lens Schematic Images."
 *
 * <b>2) Perform the pose calibration</b> <br>
 * As users refer to @ref lens_calib_flow to get "intrinsic_x"(x = 0, 1, 2, 3) in the stage of lens calibration.
 * Users can do pose calibration with the process below both at PC Windows side and board edge side.
 * Users can perform pose calibration with the process below both at PC Windows side and board edge side.
 * Compared with performing pose calibration at the board-edge side, performing pose calibration on the PC Windows-side is faster and more convenient.
 * However, users may be required to change the specific distance dynamically. For such a situation, it is preferred to select board-edge side pose calibration.
 * Here, Ambarella lists the commands at both the Windows side and the board-edge side.
 * Users can choose either to perform pose calibration.
 *
 * <b>PC Windows side:</b>
 * @code {.c}
 * host (Windows) $ copy "intrinsic_x" generated in the stage of "lens calibration" to the path "front_end/" directly. (intrinsic_x: x = 0, 1, 2, 3)
 * host (Windows) $ test_sensor_calib --msc-ini-file ..\config\sensor_calib_ini_pose_calibration_save_target_4x_ver.ini (or simply double click "save_target_info_4x_ver.bat")
 * host (Windows) $ Edit "sensor_calib_ini_pose_calibration_distance_4x_ver.ini" and modify "sensor_distance=x" accordingly. (x means the distance user specified, unit is meter.)
 * host (Windows) $ test_sensor_calib --msc-ini-file ..\config\sensor_calib_ini_pose_calibration_distance_4x_ver.ini (or simply double click "specify_distance_4x_ver.bat")
 * host (Windows) $ There will be source buffer configurations in the command window shown in the figure below.
 * Users can then configure the "cvx_quad_chan_xm_stitch_xM_linear.lua" file accordingly; the simplified reference lua configurations is shown below.
 * vsrc_0 = {
 * 	  ..............
 * 	  mode = "2592x1944",
 * 	  ..............
 * }
 * vsrc_1 = {
 * 	  ..............
 * 	  mode = "2592x1944",
 * 	  ..............
 * }
 * vsrc_2 = {
 * 	  ..............
 * 	  mode = "2592x1944",
 * 	  ..............
 * }
 * vsrc_3 = {
 * 	  ..............
 * 	  mode = "2592x1944",
 * 	  ..............
 * }
 * chan_0 = {
 * 	  ..............
 *    -- ================ src buf cfg  ================
 * 	  main = {
 * 	  	  max_output = {2592, 0},  -- output width
 * 	  	  input = {0, 0, 2592, 1944},  -- full VIN
 * 	  	  output = {0, 0, 1984, 1696},
 * 	  },
 * 	  ..............
 * }
 * chan_1 = {
 * 	  ..............
 *    -- ================ src buf cfg  ================
 * 	  main = {
 * 	  	  max_output = {2592, 0},  -- output width
 * 	  	  input = {0, 0, 2592, 1944},  -- full VIN
 * 	  	  output = {0, 1536, 1984, 1696},
 * 	  },
 * 	  ..............
 * }
 * chan_2 = {
 * 	  ..............
 *    -- ================ src buf cfg  ================
 * 	  main = {
 * 	  	  max_output = {2592, 0},  -- output width
 * 	  	  input = {0, 0, 2592, 1944},  -- full VIN
 * 	  	  output = {0, 2944, 1984, 1696},
 * 	  },
 * 	  ..............
 * }
 * chan_3 = {
 * 	  ..............
 * 	  ..............
 *    -- ================ src buf cfg  ================
 * 	  main = {
 * 	  	  max_output = {2592, 0},  -- output width
 * 	  	  input = {0, 0, 2592, 1944},  -- full VIN
 * 	  	  output = {0, 4480, 1984, 1472},
 * 	  },
 * 	  ..............
 * }
 * stream_0 = {
 * 	..............
 * 	id = 0,
 * 	max_size = {5952, 1984},
 * 	..............
 * }
 * _resource_config_ = {
 * 	  channels = {
 * 	  	chan_0,
 * 	  	chan_1,
 * 	  	chan_2,
 * 	  	chan_3,
 * 	  },
 * 	  canvas = {
 * 	 	{
 * 			type = "encode",
 * 			size = {1984, 5952},
 * 			source = {"chan_0.main","chan_1.main","chan_2.main","chan_3.main",},
 * 	  	},
 * 	  },
 * 	  streams = {
 * 		stream_0,
 * 	  },
 * }
 * return _resource_config_
 * @endcode
 * @image html source_buffer_configurations.jpg "Figure 6-3. Source Buffer Configurations."
 *
 * <b>The board edge side (The method for configuring the source buffer is the same as that for PC Windows side):</b>
 * @code {.c}
 * Board # copy "intrinsic_x" generated in the stage of "lens calibration" to the path "front_end/" directly. (intrinsic_x: x = 0, 1, 2, 3)
 * Board # test_sensor_calib --msc-ini-file ../config/sensor_calib_ini_pose_calibration_save_target_4x_ver.ini
 * Board # Edit "sensor_calib_ini_pose_calibration_distance_4x_ver.ini" and modify "sensor_distance=x" accordingly. (x means the distance user specified, unit is meter.)
 * Board # test_sensor_calib --msc-ini-file ../config/sensor_calib_ini_pose_calibration_distance_4x_ver.ini
 * Board # There will be source buffer configurations showed in the command window, and then users can config "cvx_quad_chan_xm_stitch_xM_linear.lua" file accordingly.
 * @endcode
 *
 * @subsection stitching_cmd_list 6.4 Multi-Channel Stitching Example
 *
 * @subsubsection stitching_pose_result 6.4.1 Four-channel Stitching Example
 * The commands below demonstrate how to set up a four-channel stitching case.
 * CV2x: <br>
 * @code {.c}
 * host (Windows) $ copy folder "back_end/" and "cvx_quad_chan_xm_stitch_xM_linear.lua" file generated in the stage of @ref stitching_pose_flow to the path "/root" of board.
 * Board # init.sh --na && modprobe imx335_mipi vinc_id=0xf1320 slave=1
 * Board # test_aaa_service -a&
 * Board # test_encode -i 0 --enc-mode 0 --debug-stitched 1 --vsync-detect-disable 0 --resource-cfg cvx_quad_chan_xm_stitch_xM_linear.lua --raw-capture 1
 * Board # test_encode -A -H 1984x5952 -b 1 --rotate 1 -e
 * Board # test_sensor_calib --mode 2 --channel-num 4 -f ./
 * Board # test_stitch --mode 2 -f . --no-overlap --fuse-channel 15 --vertical (no overlap part)
 * Board # test_stitch --mode 2 -f . --vertical (overlap)
 * @endcode
 *
 * The image below shows the contrast result for 4 channels stitching case after applying the pose calibration paramters. <br>
 * @image html before_after_stitching.jpg "Figure 6-4. Before vs After Pose Calibration."
 * For more principles of stitching sensor calibration and stitching LDC alignment, please refer to links below.
 * @ref page_lib_sensor_calib_doc "Sensor Calibration Library API"
 * @ref page_lib_stitch_doc "Stitch Library API"
 *
 * - - - -
 *
 * @section guide_sensor_calib_thermal_rgb 7. Thermal-RGB Fusion FoV-Alignment Calibration
 * This chapter describes the following conceptions:
 *     - @ref thermal_rgb_principle
 *     - @ref thermal_rgb_tool
 *     - @ref thermal_rgb_flow
 *     - @ref thermal_rgb_result
 *
 * @subsection thermal_rgb_principle 7.1 Thermal-RGB Fusion FoV-Alignment Calibration Principle
 * @image html thermal_rgb_fov_align_calib.jpg "Figure 7-1. Thermal RGB Align Calibration."
 * For the majority of use cases, users will have to align the FoV of the thermal
 * image with the RGB image before combining them. <br>
 * For example, suppose the thermal sensor resolution is 256x192, and the RGB sensor resolution is 2336x1752. <br>
 * To align the FoVs between thermal and RGB, users will need to get the coordinates of several specified <br>
 * key points for the same target in both sensor's FoVs. <br>
 *
 * @subsection thermal_rgb_tool 7.2 Thermal-RGB Fusion FoV-Alignment Calibration Tool
 * Path: ambarella/prebuild/ambarella/library/multi_sensor_calib/lib/armv8-a <br>
 * Tool: libsensor_calib.so <br>
 * Application: <br>
 * ambarella/packages/sensor_calib_ini_parser/arch_v5/unit_test/test_sensor_calib.c
 *
 * @subsection thermal_rgb_flow 7.3 Thermal-RGB Fusion FoV-Alignment Calibration Flow
 *
 * Refer to @ref sensor_calib_thermal_rgb "Thermal and RGB Sensors Calibration" for more details.
 *
 * @subsection thermal_rgb_result 7.4 Thermal-RGB Fusion FoV-Alignment Calibration Result
 * @image html thermal_rgb_result.jpg "Figure 7-2. Thermal and RGB Alignment."
 * The image shows the result between before and after applying the thermal and RGB calibration paramters. <br>
 *
 * - - - -
 *
 * @section guide_sensor_calib_mono_rgb 8. Mono-RGB Fusion FoV-Alignment Calibration
 * This chapter describes the following conceptions:
 *     - @ref mono_rgb_principle
 *     - @ref mono_rgb_tool
 *     - @ref mono_rgb_flow
 *     - @ref mono_rgb_result
 *
 * @subsection mono_rgb_principle 8.1 Mono-RGB Fusion FoV-Alignment Calibration Principle
 * @image html mono_rgb_cali.jpg "Figure 8-1. Mono RGB Alignment Calibration."
 * For the mono and RGB sensors fusion application, users will have to align the FoV of the mono
 * image with the FoV of the RGB image before combining them. <br>
 * The proposed solution provides a mechanism for thermal and RGB images
 * alignment automated and much more efficient. <br>
 * With the advances in technology, mono and RGB alignment
 * can be built to leverage automatic extraction method to
 * reach subpixel pixel level alignment effect. <br>
 *
 * @subsection mono_rgb_tool 8.2 Mono-RGB Fusion FoV-Alignment Calibration Tool
 * Path: ambarella/prebuild/ambarella/library/multi_sensor_calib/lib/armv8-a <br>
 * Tool: libsensor_calib.so <br>
 * Application: <br>
 * ambarella/unit_test/private/package_test/arch_v5/test_sensor_calib.cpp <br>
 *
 * @subsection mono_rgb_flow 8.3 Mono-RGB Fusion FoV-Alignment Calibration Flow
 * 1) If the user wants to use keypoints automatic detection algorithm to do calibration,
 * Just do mono and RGB sensors calibration with following commands.
 * @code {.c}
 * Set no_dist_flag=0 if the distortion has been calibrated.
 * board # test_sensor_calib --msc-ini-file sensor_calib_ini_rgb_mono.ini
 * If "no_dist_flag=1" is used :
 * board # test_stitch --mode 2 -f . --no-overlap --fuse 1
 * If "no_dist_flag=0" is used :
 * board # test_sensor_calib --mode 2 --channel-num 2 -f ./
 * board # test_stitch --mode 2 -f . --no-overlap --fuse 3
 * @endcode
 *
 * 2) If the users have done the calibration by themselves, and want to apply homography matrix to the specific channel.
 * @code {.c}
 * board # test_sensor_calib --mode 1 -i 0 --no-distort --H_matrix 0.9977401365552157,-0.000099578
 * 23263696219,2.775830523841213,-0.0001202783377077572,0.9971905736384313,1.376427136930342,-
 * 0.0000001840078883173892,-0.000000157500677787866,1 --cali-type 0 -w 2688 -h 1520 -f .
 * Configure the lua as the tool reports, and run :
 * board # test_stitch --mode 2 -f . --no-overlap --fuse 1
 * @endcode
 *
 * Refer to @ref sensor_calib_mono_rgb for more details.
 *
 * @subsection mono_rgb_result 8.4 Mono-RGB Fusion FoV-Alignment Calibration Result
 * @image html mono_rgb_match.jpg "Figure 8-2. Mono and RGB Alignment Matching."
 * The image shows the keypoints matching the result with mono and RGB sensors calibration. <br>
 *
 * - - - -
 *
 * @section guide_sensor_calib_structure_light 9. Structured-light Parameters Pose Calibration
 * This chapter describes the following conceptions:
 *     - @ref sl_pose_principle
 *     - @ref sl_pose_tool
 *     - @ref sl_pose_flow
 *     - @ref sl_pose_result
 *
 * @subsection sl_pose_principle 9.1 Structured-light Pose Parameters Calibration Principle
 * It is easy to cause an accuracy loss if users use the ruler to measure the baseline
 * between the projector and the RGB sensor. <br>
 * The proposed solution provides a mechanism to calculate the structured light's pose parameters
 * with high accuracy.
 * With the advances in technology, the pose calibration parameters accuracy can reach 0.01 mm.
 * @image html sl_formula.jpg "Figure 9-1. Structured-light Pose Calibration."
 * With the proposed solution, the formula to calculate the depth can be expressed as shown in the image above. <br>
 * "e" is the disparity <br>
 * "d0" is the depth to the specific pattern. <br>
 * "fx" is the focal length from lens calibration. <br>
 * "Tx", "Ty" and "Tz" are the 3D coordinates based on the camera optical center. <br>
 * "u2" is the x coordinate in 2D image. <br>
 *
 * @subsection sl_pose_tool 9.2 Structured-light Pose Parameters Calibration Tool
 * Path: ambarella/prebuild/ambarella/library/multi_sensor_calib/host_calib_tool/bin/x86_64 <br>
 * Tool: sl_cali <br>
 *
 * @subsection sl_pose_flow 9.3 Structured-light Pose Parameters Calibration Flow
 * It is assumed that the lens calibration has been done perfectly before this
 * stage, and the images are captured without distortion.
 * Users can refer to @ref guide_sensor_calib_lens "Lens Calibration" for more details of lens calibration.
 * @image html sl_base.jpg "Figure 9-2. Structured Light in the First Position."
 * Put the structured-light camera in the first position with a certain distance (like 45 cm) to the pattern, <br>
 * and capture two YUVs as shown in the image. One image has no speckle, and the other one has. <br>
 * Convert them to the format of BMP. The name of one image is base_img.bmp,
 * and name of the other image is random_img.bmp. <br>
 *
 * @image html sl_location.jpg "Figure 9-3. Structured Light in the Second Position."
 * Put the structured-light camera in the second position with a certain distance (like 55 cm) to the pattern, <br>
 * and capture two YUVs as shown in the image. One image has no speckle, and the other one has. <br>
 * Convert them to the format of BMP. The name of one image is base_img1.bmp,
 * and name of the other image is random_img1.bmp. <br>
 *
 * Run the command as shown below: <br>
 * Tag-info is used to specify the pattern information, refer to @ref sensor_calib_prepare_pat for more details. <br>
 * Share-id is used to specify the common April tag corner ID (there are four
 * April tags in one image, and each tag has its own ID). <br>
 * Ensure that at lease one same April tag is visible in the four images. <br>
 * @code {.c}
 * bin/x86_64/sl_cali -f calib_data/rgbir/50 --pattern 1 --tag-info 14,0.024,0.024 --share-id 2 -r
 * @endcode
 *
 * @subsection sl_pose_result 9.4 Structured-light Pose Parameters Calibration Result
 * The result is shown below :
 * @code {.c}
 * fitting plan file calib_data/rgbir/50/base_img.bmp
 * fitting plan file calib_data/rgbir/50/random_img.bmp
 * random points file calib_data/rgbir/50/base_img1.bmp
 * random points file calib_data/rgbir/50/random_img1.bmp
 * cnt 71, avg epilines error 0.131668
 * cnt 65, avg epilines error 0.101085
 * Final inlier 46
 * T [0.040939398;
 *  0.00016056612]
 * @endcode
 *
 * "T" is the pose calibration result, it contains Tx and Tz. Users can apply it
 * to the formula expressed in @ref sl_pose_principle.
 *
 * - - - -
 *
 * @section guide_sensor_calib_dual_fish 10. Dual-fisheye back to back Pose Calibration
 * This chapter describes the following conceptions:
 *     - @ref ds_pose_principle
 *     - @ref ds_pose_tool
 *     - @ref ds_pose_flow
 *     - @ref ds_pose_result
 *
 * @subsection ds_pose_principle 10.1 Dual-fisheye Pose Calibration Principle
 * Homograpy matrix is used to express the transformation between two image planes. <br>
 * The calibration is used to get the homograpy matrix and project each channel to the first image channel. <br>
 * After the pose calibration, users could get the message of configuration (offset / width / height) for each channel. <br>
 * @image html dual_fisheye_panorama.jpg "Figure 10-1. Dual-fisheye Pose Calibration."
 * The ouput is a 360 x 180 degree panorama stitched view.
 *
 * @subsection ds_pose_tool 10.2 Dual-fisheye Pose Calibration Tool
 * For pose calibration, Ambarella supports to do pose calibration both on PC Windows side and board side. <br>
 * Users can get pose calibration application for Windows side from the below path. <br>
 * Environment: Win10, x64 Tool: cv2x_cv5x_pose_calibration_tool_for_windows_vx.x.x_x.tar.bz2 <br>
 * Board side path: ambarella/prebuild/ambarella/library/multi_sensor_calib/lib/armv8-a <br>
 * Tool: libsensor_calib.so <br>
 * Application: <br>
 * ambarella/packages/sensor_calib_ini_parser/arch_v5/unit_test/test_sensor_calib.c <br>
 *
 * @subsection ds_pose_flow 10.3 Dual-fisheye Pose Calibration Flow
 * 1) If the users want to do the pose calibration with chessboard calibration board: <br>
 * The command to run the lens calibration is shown below: <br>
 * @code {.c}
 * host $ save_target_info_2x_dual_fisheye_1920_1920_auto_chessboard_mei.bat
 * @endcode
 *
 * 2) If the users want to to do the pose calibration without doing lens calibration : <br>
 * The users need to find the fisheye circle radius and image center manually. <br>
 * @image html fishe_radius_center.jpg "Figure 10-2. Fisheye Radius and Center."
 * 1> Find the circle center and radius like the picture show. <br>
 * Left point coordinate : (380, 528) <br>
 * Right point coordinate : (1489, 528) <br>
 * Radius = (1489 - 380) / 2 = 554 <br>
 * Center = (380 + (1489 - 380) / 2, 528) = (934, 528) <br>
 *
 * 2> Run below command to create the undistorted images. <br>
 * @code {.c}
 * host $ save_target_info_2x_dual_fisheye_1600_1296_manully_no_lens_calibration.bat <br>
 * @endcode
 * The undistorted images will be stored in the same folder of the bat files, named "un_image_x.png". <br>
 *
 * @image html fisheye_undistorted_segment.jpg "Figure 10-3. Fisheye Stitching Offset and Corresponding Points."
 * 3> Choose the x coordinate offset_0 / offset_1 from the image "un_image_0.png". <br>
 * 4> Choose more than 4 pairs of corresponding points from the two undistorted images. <br>
 * 5> Fill them into the ini file as shown below. <br>
 * @code {.c}
 * [Chan_x]
 *    top_left_point=570,539:579,776
 *    bot_right_point=1778,439:1830,815
 *    focal=1080
 *    cx=826
 *    cy=624
 *    no_dist_flag=1
 *
 * [Calib]
 *    fisheye_radius=602
 *    fisheye_stitch_start=652
 *    fisheye_stitch_end=1891
 * @endcode
 *
 * 6> Run below command to get the canvas configuration information. <br>
 * @code {.c}
 * host $ save_target_info_2x_dual_fisheye_1600_1296_manully_no_lens_calibration.bat
 * @endcode

 * 3) If users want to to do the pose calibration with choosing the points manually: <br>
 * 1> Run below command to create the undistorted images. <br>
 * @code {.c}
 * host $ save_target_info_2x_dual_fisheye_1920_1080_manully_mei.bat
 * @endcode
 * The undistorted images will be stored in the same folder of the bat files, named "un_image_x.png" <br>
 * 2> Choose more than 4 pairs of corresponding points in the two undistorted images like above image shown. <br>
 * 3> Run below command to create the calibration information. <br>
 * @code {.c}
 * host $ save_target_info_2x_dual_fisheye_1920_1080_manully_mei.bat
 * @endcode
 *
 * @subsection ds_pose_result 10.4 Dual-fisheye Pose Calibration Result
 * The result is shown below:
 * @code {.c}
 * Channel [0] Configuration :
 * Buffer : output size [2400x1296], zoom [1.000000, 1.000000]
 * Canvas : Input : offset [0x0], size [0x0], Output : offset [0x0], size [704x1200]
 * Canvas : Input : offset [0x0], size [0x0], Output : offset [1792x0], size [512x1200]
 * Channel [1] Configuration :
 * Buffer : output size [2752x1304], zoom [1.000000, 1.000000]
 * Canvas : Input : offset [0x0], size [0x0], Output : offset [640x0], size [1216x1200]
 * Canvas : Input : offset [0x0], size [0x0], Output : offset [0x0], size [0x0]
 * @endcode
 * Users need to configure the lua script according to the report.
 *
 * - - - -
 *
 * @section guide_sensor_calib_faq 11. Sensor Calibration FAQ
 *
 * @subsection guide_sensor_calib_faq_q1 Question 1 How to ensure the lens calibration quality?
 * @b Answer: To assure the lens calibration works well. Users need to ensure the following : <br>
 *    1) Tool supports circle and chessboard patterns. It is more accurate to use circle pattern,
 *       keep each circle's diameter about 20 pixels. <br>
 *    2) At least one Apriltag in the image. <br>
 *    3) It is better to take snapshots in different distances from close to far, with different
 *       angles (pitch / yaw / roll, cover full FoV). <br>
 *    4) Choose the rigid and flat board as a calibration board, and make sure RMS is less than 0.4.
 *       It is hard to achieve 0.4, if the calibration target's quality is not good enough. <br>
 *    5) Measure average distance between two circle centers (measuring distance between two tags
 *       in the horizontal and vertical direction, divided by circle numbers, then getting an average value)
 *       and fill in run_cali.sh. <br>
 *    6) Set <b> "debug" </b> option as @ref lens_calib_flow to check the lens calibration quality.
 *
 * @subsection guide_sensor_calib_faq_q2 Question 2 What is the minimum number of images required for the fast lens calibration?
 * @b Answer: Users need to capture at least 3 images to perform the fast lens calibration. It is suggested <br>
 * to put the pattern in left, middle, right part of the image, refer to the dataset in the cv2x_cv5x_lens_calibration_tool_for_windows_vx.x.x_x.tar.bz2.
 *
 * @subsection guide_sensor_calib_faq_q3 Question 3 Can Lens calibration work well with multiple patterns in one image?
 * @b Answer: Yes. The lens calibration supports multiple circle patterns in one image. <br>
 * Users can set <b> "debug" </b> option's bit 2 as 1 to check the tag information.
 *
 * @subsection guide_sensor_calib_faq_q4 Question 4 How to ensure the stitching pose calibration quality?
 * @b Answer: To make sure stitch pose calibration works well. Users need to ensure the following : <br>
 *  1) At least one pair of common April tag in the images. <br>
 *  2) The lens calibration result is good.
 *
 * @subsection guide_sensor_calib_faq_q5 Question 5 What's the mass production strategy for multi-VIN stitching?
 * @b Answer: <br>
 * 1) If the customer wants to do the pose calibration with a fixed pattern (without specifying specific distance). <br>
 * It is better to do lens calibration once, as distortion parameters are similar for the same type lens. <br>
 * Pose calibration must be done for every equipment, using the calibration tool on board is faster. <br>
 * 2) If the customer wants to do the pose calibration with a fixed pattern (specifying certain distance). <br>
 * As the image center is different for each channel, it is recommended to use more than <b> 60 </b> images to do
 * the full lens calibration once to get initial parameters. Additionally, the lens calibration for each lens with two or three images
 * is performed to estimate the image center.
 *
 * @subsection guide_sensor_calib_faq_q6 Question 6 How to ensure the thermal-RGB fusion FoV-alignment calibration quality?
 * @b Answer: <br>
 * If the user is not satisfied with the alignment quality of choosing 4 pairs of key points manually, the tools support more pairs of <br>
 * key points to do calibration, the more the better. It is suggested to choose the points that are uniform and do not cluster together to improve the accuracy.
 *
 * @subsection guide_sensor_calib_faq_q7 Question 7 How to avoid image size mismatching between different channels for multi-VIN stitching?
 * @b Answer: <br>
 * @image html different_stitching_size.jpg "Figure 11-1. Image Size Mismatching between Different Channel."
 * The image shows the pattern size is mismatching between two channels, the root cause is that the calibration intrinsic data's focal length <br>
 * is not similar (lens calibration is not performed well). For example, if one channel's focal lenght is 1750, <br>
 * and the other channel's focal length is 1810, the difference will be (1800 - 1750) / 1750 = 0.03. <br>
 * So it is necessary to keep the output of the lens calibration's intrinsic parameters are similar when doing the lens calibration.
 *
 * - - - -
 *
 * @section guide_sensor_calib_lic 12. License
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
 * @file doc_sys_design_docker.h
 * @brief This file introduces the construction of the Docker environment
 * and the implementation of software development kit (SDK) functions under Docker.
 * @version 0.1
 * @date 2022-11-04
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

/*! @page page_sys_docker DESIGN - Docker Usage Guide
 *
 * @section docker_history 0. Revision History
 * <table>
 * <caption id="docker_rev_history"></caption>
 * <tr><th> Updated Date   <th> Modification
 * <tr><td> 20221104       <td> Initial Version
 * <tr><td> 20221129       <td> Updated Section @ref docker_ov "1. Overview"
 * <tr><td> 20221201       <td> Added Section @ref docker_ssh_server "11. Support SSH server"
 * <tr><td> 20230308       <td> Added Sections @ref docker_build_cv72 "3. Build the Firmware for CV72 EVK"
 *                              @ref docker_build_cv3 "4. Build the Firmware for CV3x EVK"
 * <tr><td> 20230407       <td> Added Section @ref docker_qa "12. Docker Q&A"
 * <tr><td> 20240110       <td> Updated Section @ref docker_ov "1. Overview"
 * </table>
 *
 * - - - -
 *
 * @section docker_ov 1. Overview
 * Ambarella provides Docker support for CV5x platforms. This document provides a guide for building
 * a Docker environment and demonstrates how to run software development kit (SDK) functions under Docker.
 *
 * @subsection docker_about 1.1 About Docker
 * Docker is an open platform for developing, shipping, and running applications.
 * Docker enables users to separate applications from infrastructure so they can quickly deliver software.
 * With Docker, users can manage the infrastructure in the same way that they manage applications.
 * By taking advantage of Docker methodologies for shipping, testing, and accelerated code deployment,
 * users can significantly reduce the delay between writing code and running it in production.
 *
 * Docker provides the functions for packing and running applications in a friendly isolated environment,
 * which is called a container. Containers are lightweight and can
 * run directly on the host's kernel without other additional management programs.
 * At the same time, the isolation and security features of the environment enable multiple
 * containers to run on a given host. Containers are independent of one other and multiple
 * containers will not interfere with each other.
 *
 * To download the latest Docker container and daemon applications running on Arm® V8 platforms, users can
 * access the link https://download.docker.com/linux/static/stable/aarch64/.
 *
 * @note
 *  - The Docker binaries downloaded from the Docker link above all belong to `Docker Engine`,
 *    scope, which is licensed under the <b>Apache version 2.0 License</b>.
 *    Here is the reference `https://docs.docker.com/engine/`.
 *  - For the differences between `Docker Engine` and `Docker Desktop`,
 *    refer to `https://www.docker.com/products/docker-desktop/alternatives/`.
 *
 *
 * - - - -
 *
 * @section docker_build_cv5 2. Build the Firmware for the CV5x Evaluation Kit (EVK)
 * 1. Build the firmware for the CV5 Timn EVK with the configuration file below.
 * @code
 * build $ make cv5_ipcam_emmc_docker_config
 * build $ make defconfig_public_linux
 * build $ make -j 8
 * @endcode
 *
 * 2. Build the firmware for the CV52 Crco EVK with the configuration file below.
 * DDR type: LPDDR4
 * @code
 * build $ make cv52_ipcam_emmc_lp4_docker_config
 * @endcode
 * DDR type: LPDDR5
 * @code
 * build $ make cv52_ipcam_emmc_lp5_docker_config
 * @endcode
 * @code
 * build $ make defconfig_public_linux
 * build $ make -j 8
 * @endcode
 *
 * 3. Build the firmware for the CV52n Zr EVK with the configuration file below.
 * @code
 * build $ make cv52_ipcam_emmc_docker_config
 * build $ make defconfig_public_linux
 * build $ make -j 8
 * @endcode
 *
 * - - - -
 *
 * @section docker_build_cv72 3. Build the Firmware for the CV72 EVK
 * 1. Build the firmware for the CV72 Ga EVK with the configuration file below.
 * @code
 * build $ make cv72_ipcam_docker_config
 * build $ make defconfig_public_linux
 * build $ make -j 8
 * @endcode
 *
 * - - - -
 *
 * @section docker_build_cv3 4. Build the Firmware for the CV3x EVK
 * 1. Build the firmware for the CV3bub EVK with the configuration file below.
 * @code
 * build $ make cv3bub_ipcam_cavalry_docker_config
 * build $ make defconfig_public_linux
 * build $ make -j 8
 * @endcode
 *
 * 2. Build the firmware for the CV3 Dk-mini EVK with the configuration file below.
 * @code
 * build $ make cv3_dk_mini_ipcam_cavalry_docker_config
 * build $ make defconfig_public_linux
 * build $ make -j 8
 * @endcode
 *
 * - - - -
 *
 * @section docker_network_set 5. Network Setup
 * To build a Docker environment, users must ensure access to the internet.
 * Then, they can set up the network according to the operation in @ref si_wifi "WiFi" and @ref si_ethernet "Ethernet".
 *
 * Test the network with the command below.
 * The following information indicates that the connection to the internet is normal.
 * @code
 * board # ping www.google.com
 * PING www.google.com (180.101.49.12): 56 data bytes
 * 64 bytes from 180.101.49.12: seq=0 ttl=49 time=9.787 ms
 * 64 bytes from 180.101.49.12: seq=1 ttl=49 time=18.995 ms
 *
 * @endcode
 *
 * - - - -
 *
 * @section docker_configure 6. Configure Docker Image
 * Before running Docker, users must configure the following:
 * 1. Prepare a secure digital (SD) card and format it to EXT4.<br>
 * Copy the Docker daemon and client applications (CAs) from the master branch to the SD card.
 * Users cannot build it into the firmware due to the size limit of the electronic logic gate NAND.
 * Refer to @ref si_sd_card "SD Card" for SD card contents.
 *
 * 2. Add domestic mirror sources.<br>
 * Create `daemon.json` and enter the following information:
 * @code
 * board # cat /etc/docker/daemon.json
 * {
 * "data-root":"/sdcard/mmcblk0p1/docker_data_root",
 * "registry-mirrors":["https://hub-mirror.c.163.com","http://f1361db2.m.daocloud.io"]
 * }
 * @endcode
 * @note
 * The following configuration options are used:<br>
 * - `data-root`: The root path used by Docker runtime, default: `/var/lib/Docker`<br>
 * - `registry-mirrors`: Sets the mirror acceleration, address: "https://hub-mirror.c.163.com""http://f1361db2.m.daocloud.io"
 * These are for domestic use in China, and users can choose acceleration mirror addresses that
 * are suitable for the network environment.
 *
 * 3. Change the system time.<br>
 * Confirm that the system time is accurate; if not, set it to the correct time.
 * @code
 * board # date -s 2022-12-1
 * @endcode
 *
 * - - - -
 *
 * @section docker_run_daemons 7. Run Docker Daemons
 * @code
 * board # export PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/bin/X11:/usr/local/bin:/usr/local/sbin:/sdcard/mmcblk0p1/bin
 * board # containerd &
 * board # dockerd &
 * @endcode
 *
 * - - - -
 *
 * @section docker_load_ubuntu 8. Load Ubuntu
 * Because @ref docker_network_set "Set Network" implements the connection to the internet,
 * users can pull Ubuntu images from the Docker community.
 * @code
 * board # docker pull arm64v8/ubuntu
 * @endcode
 * @note
 * The `docker pull arm64v8/ubuntu` command indicates that the pulled image version is the latest,
 * such as `docker pull arm64v8/ubuntu:18.04`. Users can add the corresponding version after the image name.
 *
 * - - - -
 *
 * @section docker_run_ubuntu 9. Run Ubuntu
 * 1. Create and start a new containter.
 * @code
 * board # docker run -itd --name u1201 --privileged=true -p 9554:554 -p 8049:2049 arm64v8/ubuntu
 * @endcode
 * @note
 * The following configuration options are used:<br>
 * The `--privileged=true` sets the root privilege<br>
 * The `-p` opens the port, which maps the port of the Docker container to the host port<br>
 * The `-name` sets the container name
 *
 * 2. Enter into the container.
 * @code
 * board # docker exec -it u1201 /bin/bash
 * root@90ad03cbb159:/#
 * @endcode
 *
 * - - - -
 *
 * @section docker_implement_sdk 10. Implement SDK
 * Users can implement the SDK functions in Docker through the following operations.
 * 1. Copy SDK-related files to Docker.
 * @code
 * board # docker cp /usr/local/bin u1201:/usr/local/
 * board # docker cp /usr/lib/   u1201:/usr/
 * board # docker cp /usr/local/bin/   u1201:/usr/local/
 * root@90ad03cbb159:/# mkdir -p /lib/modules/5.15.76	// Need to enter the container to create the relevant directory.
 * board # docker cp /lib/modules/5.15.76   u1201:/lib/modules
 * board # docker cp /lib/firmware/   u1201:/lib/
 * board # docker cp /etc/ambarella.conf  u1201:/etc/
 * board # docker cp /sbin/modprobe   u1201:/sbin
 * board # docker cp /usr/bin/kmod   u1201:/usr/bin/
 * @endcode
 * @note
 * `mkdir -p /lib/modules/5.15.76`<br>
 * The name of the folder to be created must be consistent with the folder name under `/lib/modules/` outside Docker.
 *
 * 2. Start the basic image audio video (IAV) functions in the Docker container.
 *  1) Operation outside Docker:
 *  @code
 *  board # init.sh --na
 *  board # modprobe imx274_mipi vinc_id=8 bus_id=3
 *  board # test_aaa_service -a&
 *  @endcode
 *  2) Operation in Docker:
 *  @code
 *  board # docker exec -it u1201 /bin/bash
 *  root@90ad03cbb159:/# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *  @endcode
 *
 * 3. Start the Cavalry functions in the Docker container.<br>
 * For Cavalry content, refer to @ref page_drv_cavalry_doc "Cavalry Driver API".<br>
 * Users can package their own algorithms through Docker technology and run them on the CV5x board.<br>
 * The benefits are as follows:<br>
 * 1) Continuous deployment and testing:<br>
 * The Docker container eliminates the difference between online and offline environments
 * and ensures the consistency and standardization of the environment in the application life cycle.
 * Developers use an image to build a standard development environment,
 * and then migrate through an image that encapsulates the complete environment and application.
 * This truly realizes the concept "build once, run everywhere".
 * This enables test and operations personnel to directly deploy software images for testing and publishing,
 * greatly simplifying the process of continuous integration, testing, and publishing.<br>
 * 2) Cross-platform support:<br>
 * Because Docker technology decouples the application from the underlying environment,
 * users can seamlessly run their applications on any chip platform.<br>
 * 3) High resource utilization:<br>
 * The container does not have the extra overhead of the manager,
 * but shares the operating system with the bottom layer.
 * The user's application can access and process the bottom layer data with low load and make full use of system resources.<br>
 *
 * The location of algorithms in Docker in the computer vision (CV) software framework is shown below.
 * @image html docker_algorithms.png "Figure 10-1. Algorithms in Docker."
 *
 * - - - -
 *
 * @section docker_ssh_server 11. Support Secure Shell (SSH) Server
 * 1. Ensure that the board's network is smooth.
 *
 * 2. Set the port to bind to the host when creating the container.
 * @code
 * board # docker run -itd --name u1201 --privileged=true -p 9022:22 arm64v8/ubuntu
 * @endcode
 * @note
 * The option `-p` opens a port, which maps the port of the Docker container (22) to the host port (9022).<br>
 *
 * 3. Software source update (input in Docker).
 * @code
 * root@90ad03cbb159:~# apt-get update
 * root@90ad03cbb159:~# apt-get upgrade
 * @endcode
 *
 * 4. Install vim (input in Docker).
 * @code
 * root@90ad03cbb159:~# apt-get install -y vim
 * @endcode
 *
 * 5. Set up the SSH server（input in Docker).<br>
 *  1)Install openssh-server.
 *  @code
 *  root@90ad03cbb159:~# apt-get install -y openssh-server
 *  @endcode
 *  2)Open service.
 *  @code
 *  root@90ad03cbb159:~# /etc/init.d/ssh start
 *  @endcode
 *  3)Verify that it starts normally.
 *  @code
 *  root@90ad03cbb159:~# ps -e | grep ssh
 *  @endcode
 *  4)Edit sshd_config.
 *  @code
 *  root@90ad03cbb159:~# vi /etc/ssh/sshd_config
 *  @endcode
 *  Remove the comment `#` before `PermitRootLogin prohibit-password` and change it to `PermitRootLogin yes`.<br>
 *  5)Restart service.
 *  @code
 *  root@90ad03cbb159:~# /etc/init.d/ssh restart
 *  @endcode
 *  6)Set the SSH password.
 *  @code
 *  root@90ad03cbb159:~# passwd root
 *  @endcode
 *
 * 6. SSH access Docker<br>
 * Use secureCRT or other tools to connect to 10.0.0.2:9022 to verify that SSH function is normal.
 * The user name is root, and the password is set previously.
 *
 * - - - -
 *
 * @section docker_ROS2 12. Support ROS2
 * The robot operating system (ROS) is an open source project for building robot applications.<br>
 *
 * 1. Get the ROS2 image for arm64v8.
 * @code
 * board # docker pull arm64v8/ros
 * @endcode
 * @note
 * The `docker pull arm64v8/ros` command indicates that the pulled image version is the latest.
 * Users can add the specified version after the image name, such as `docker pull arm64v8/ros:humble`.
 *
 * 2. Check the ROS image.
 * @code
 * board # docker image ls
 * REPOSITORY    TAG       IMAGE ID       CREATED         SIZE
 * arm64v8/ros   latest    71fb575afde7   4 weeks ago     714MB
 * @endcode
 *
 * 3. Create a new containter for the `arm64v8/ros` image.
 * @code
 * board # docker run -it --net=host --name ros2_humble --privileged=true --restart=always arm64v8/ros
 * @endcode
 *   - `--net=host` indicates that the host network mode is used for the container. The container’s network stack
 *     is not isolated from the Docker host (the container shares the host’s networking namespace),
 *     and the container is not allocated its own IP address.
 *   - `--restart=always` indicates that the container will always start on daemon startup,
 *      regardless of the current state of the container.
 *
 * 4. Check the ROS container.
 * @code
 * board # docker ps -a
 * CONTAINER ID   IMAGE         COMMAND                  CREATED         STATUS                       PORTS     NAMES
 * 0ae11e3d8e06   arm64v8/ros   "/ros_entrypoint.sh …"   2 days ago      Exited 6 hours ago                     ros2_humble
 * @endcode
 * If the container is in `Exited` status, the user can use the following command to start it.
 * @code
 * board # docker start ros2_humble
 * board # docker ps -a
 * CONTAINER ID   IMAGE         COMMAND                  CREATED         STATUS                       PORTS     NAMES
 * 0ae11e3d8e06   arm64v8/ros   "/ros_entrypoint.sh …"   2 days ago      Up 15 seconds                          ros2_humble
 * @endcode
 *
 * 5. Enter into the container.
 * @code
 * board # docker exec -it ros2_humble /bin/bash
 * root@Ambarella:/#
 * @endcode
 *
 * 6. Run the demo test application to publish information.
 * @code
 * root@Ambarella:/# source /opt/ros/humble/setup.bash
 * root@Ambarella:/# apt-get update && apt-get install -y ros-${ROS_DISTRO}-demo-nodes-cpp
 * root@Ambarella:/# ros2 run demo_nodes_cpp talker
 * @endcode
 * The user can run the demo test application to subscribe the information
 * on another device or on a PC with the ROS2 image installed.
 * @code
 * root@Ambarella:/# source /opt/ros/humble/setup.bash
 * root@Ambarella:/# ros2 run demo_nodes_cpp listener
 * @endcode
 *
 * 7. Visit the following links for useful documentation on ROS.<br>
 * How to use an `arm64v8:ros` image: https://hub.docker.com/r/arm64v8/ros<br>
 * ROS official documentation: https://docs.ros.org/en/humble/Tutorials.html
 *
 * @note
 * In the Linux operating environment, each released version of ROS2 corresponds to
 * an Ubuntu version, which is difficult to use on other versions.
 * For example, ROS2 Humble must run on ubuntu22.04, while ROS2 Foxy must run on ubuntu20.04.
 *
 * - - - -
 *
 * @section docker_qa 13. Docker Q & A
 * 1. Why did Docker fail to start?<br>
 * Users may encounter different errors when running Docker, which is caused by the different configurations supported by the board.<br>
 * The following are the solutions for commonly-reported errors.<br>
 *  1) How can the error below be resolved when running `dockerd &`?
 *  @code
 *  failed to start daemon: failed to dial "/run/containerd/containerd.sock":
 *  unknown service containerd.services.namespaces.v1.Namespaces: not implemented
 *  @endcode
 *
 *  Method of resolution:
 *  @code
 *  board # rm /run/containerd/containerd.sock
 *  board # dockerd &
 *  @endcode
 *
 *  2) How can the error below be resolved when running `dockerd &`?<br>
 *  @code
 *  WARN Your kernel does not support cgroup memory limit
 *  WARN Unable to find cpu cgroup in mounts
 *  WARN Unable to find blkio cgroup in mounts
 *  WARN Unable to find cpuset cgroup in mounts
 *  WARN Unable to find pids cgroup in mounts
 *  INFO stopping healthcheck following graceful shutdown  module=libcontainerd
 *  INFO stopping event stream following graceful shutdown  error="context canceled" module=libcontainerd namespace=plugins.moby
 *  failed to start daemon: Devices cgroup isn't mounted
 *  @endcode
 *
 *  Method of resolution:<br>
 *  Execute `manual_mount.sh` in the `/bin directory`.<br>
 *  - Execute <a href="script/manual_mount.sh" target="_blank"><b>manual_mount.sh</b></a> in /bin directory.<br>
 *  @code
 *  board # cd /sdcard/mmcblk0p1/bin/
 *  board # chmod +x manual_mount.sh
 *  board # ./manual_mount.sh
 *  board # dockerd &
 *  @endcode
 *
 *  3) How can the error below be resolved  when running `dockerd &`?<br>
 *  @code
 *  WARN Failed to find iptables: exec: "iptables": executable file not found in $PATH
 *  INFO stopping event stream following graceful shutdown  error="<nil>" module=libcontainerd namespace=moby
 *  INFO stopping event stream following graceful shutdown  error="context canceled" module=libcontainerd namespace=plugins.moby
 *  INFO stopping healthcheck following graceful shutdown  module=libcontainerd
 *  failed to start daemon: Error initializing network controller: error obtaining controller instance: failed to create NAT chain DOCKER: Iptables not found
 *  @endcode
 *
 *  Methods of resolution:<br>
 *   - Modify options in `/etc/docker/daemon.json`.<br>
 *   @code
 *    - "registry-mirrors":["https://hub-mirror.c.163.com","http://f1361db2.m.daocloud.io"]
 *    + "registry-mirrors":["https://hub-mirror.c.163.com","http://f1361db2.m.daocloud.io"],
 *    + "iptables":false
 *    }
 *   @endcode
 *   - Add `CONFIG_AMBARELLA_IPTABLES_SUPPORT` to the board configuration.
 *
 *  4) How can the error below be resolved when running `docker pull arm64v8/ubuntu`?<br>
 *  @code
 *  Using default tag: latest
 *  WARN[2021-11-14T09:45:55.936641160Z] Error getting v2 registry: Get "https://registry-1.docker.io/v2/":
 *  dial tcp: lookup registry-1.docker.io on [::1]:53: dial udp [::1]:53: socket: address family not supported by protocol<br>
 *  INFO[2021-11-14T09:45:55.936735420Z] Attempting next endpoint for pull after error: Get "https://registry-1.docker.io/v2/":
 *  dial tcp: lookup registry-1.docker.io on [::1]:53: dial udp [::1]:53: socket: address family not supported by protocol<br>
 *  ERRO[2021-11-14T09:45:55.942925120Z] Handler for POST /v1.43/images/create returned error: Get "https://registry-1.docker.io/v2/":
 *  dial tcp: lookup registry-1.docker.io on [::1]:53: dial udp [::1]:53: socket: address family not supported by protocol<br>
 *  Error response from daemon: Get "https://registry-1.docker.io/v2/": dial tcp: lookup registry-1.docker.io on [::1]:53:
 *  dial udp [::1]:53: socket: address family not supported by protocol
 *  @endcode
 *
 *  Methods of resolution:<br>
 *   - Configure nameserver in `/etc/resolv.conf`.<br>
 *   @code
 *   nameserver 8.8.8.8
 *   nameserver 8.8.4.4
 *   @endcode
 *
 *  5) How can the error below be resolved when running `docker run -itd --name xxx --privileged=true -p 9554:554 -p 8049:2049 arm64v8/ubuntu`?<br>
 *  @code
 *  ERRO[2023-11-20T19:46:54.338243660Z] Handler for POST /v1.43/containers/9d3d8cd663f0df80f2ba2f0dcf0e0160152eb48d6bceafb619cc11fcd09788ec/start
 *  returned error: failed to create task for container: failed to start shim: mkdir /var/lib/containerd/io.containerd.runtime.v2.task/moby: no space left on device: unknown<br>
 *  docker: Error response from daemon: failed to create task for container: failed to start shim:
 *  mkdir /var/lib/containerd/io.containerd.runtime.v2.task/moby: no space left on device: unknown.
 *  @endcode
 *  This error is usually caused by the Docker daemon being unable to create a task for the container.
 *
 *  Methods of resolution:<br>
 *   - Check if the system resources are sufficient: RAM, storage space, CPU, and more.<br>
 *   - Users can stop the Docker service, delete the Docker data root directory and re-enable it.
 *
 *  6) How can the error below be resolved when running `docker pull arm64v8/ubuntu`?<br>
 *  @code
 *  Using default tag: latest
 *  WARN[2023-11-30T00:00:22.437193920Z] Error getting v2 registry: Get "https://hub-mirror.c.163.com/v2/": x509: certificate signed by unknown authority<br>
 *  INFO[2023-11-30T00:00:22.437284980Z] Attempting next endpoint for pull after error: Get "https://hub-mirror.c.163.com/v2/": x509: certificate signed by unknown authority<br>
 *  WARN[2023-11-30T00:00:23.240061920Z] Error getting v2 registry: Get "http://f1361db2.m.daocloud.io/v2/": dial tcp: lookup f1361db2.m.daocloud.io on 208.67.222.222:53: no such host <br>
 *  INFO[2023-11-30T00:00:23.240131980Z] Attempting next endpoint for pull after error: Get "http://f1361db2.m.daocloud.io/v2/": dial tcp: lookup f1361db2.m.daocloud.io on 208.67.222.222:53: no such host <br>
 *  WARN[2023-11-30T00:00:23.676285300Z] Error getting v2 registry: Get "https://registry-1.docker.io/v2/": x509: certificate signed by unknown authority <br>
 *  INFO[2023-11-30T00:00:23.676359100Z] Attempting next endpoint for pull after error: Get "https://registry-1.docker.io/v2/": x509: certificate signed by unknown authority<br>
 *  ERRO[2023-11-30T00:00:23.706194600Z] Handler for POST /v1.41/images/create returned error: Get "https://registry-1.docker.io/v2/": x509: certificate signed by unknown authority<br>
 *  Error response from daemon: Get "https://registry-1.docker.io/v2/": x509: certificate signed by unknown authority<br>
 *  @endcode
 *
 *  The system defaults to not having a CA certificates root certificate, which makes it unable to recognize digital certificates carried by external HTTPS.
 *
 *  Methods of resolution:<br>
 *   If the user is only in the testing phase, the option to disable TLS verify can be configured in /etc/docker/daemon.json.
 *   @code
 *    - "registry-mirrors":["https://hub-mirror.c.163.com","http://f1361db2.m.daocloud.io"]
 *    + "registry-mirrors":["https://hub-mirror.c.163.com","http://f1361db2.m.daocloud.io"],
 *    + "tlsverify": false
 *    }
 *   @endcode
 *   Ambarella recommends the user downloads a digital certificate on the host side for security assurance.
 *
 * 2. How do users view the kernel options required for Docker?<br>
 * This can be detected with the following linked script:<br>
 * `https://github.com/moby/moby/blob/master/contrib/check-config.sh`
 *
 * 3. What are the suggested FS formats when using an SD card?<br>
 * Docker supports different file systems for different storage drivers.
 * The following are the main types of storage drivers supported by Docker:
 * @par overlay2
 * This is the recommended storage driver for the current release; it offers excellent performance without additional dependencies and configurations.<br>
 * Replace the overlay storage driver after version 18.09. It supports XFS (in case of ftype = 1) and EXT4 file systems.<br>
 * @par AUFS
 * The storage driver used in the early days of Docker is recommended before Docker version 18.06 and Ubuntu version 14.04.
 * It supports XFS and EXT4 file systems.<br>
 * @par devicemapper
 * This is the recommended storage driver for earlier versions of Community Enterprise Operating System (CentOS) and Red Hat Enterprise Linux (RHEL) systems,
 * as they do not support overlay2 and require direct-lvm support.<br>
 * @par BTRFS
 * Use only for BTRFS file systems.
 * @par ZFS
 * Use only for ZFS file systems.
 * @par VFS
 * This does not depend on the file system, but the performance is sub-optimal. Thus, it is mainly used for testing.<br>
 *
 * Users can select the corresponding file system format according to the driver system used.<br>
 * The Docker official recommendation is to choose the overlay2 storage driver.
 *
 * - - - -
 *
 * @section docker_license 14. License
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
 * @file doc_sys_design_porting_ubuntu.h
 * @brief This file introduces porting ubuntu system design
 * @version 0.1
 * @date 2023-02-27
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

/*! @page page_sys_porting_ubuntu_doc DESIGN - Porting Ubuntu System
 *
 * @section porting_ubuntu_system_history 0. Revision History
 * <table>
 * <caption id="porting_ubuntu_system_rev_history"></caption>
 * <tr><th> Updated Date          <th> Modification
 * <tr><td> 20230227              <td> Initial Version
 * </table>
 *
 * - - - -
 *
 * @section porting_ubuntu_system_ov 1. Overview
 *
 * This document introduces transplanting Ubuntu system to Ambarella system on chip (SoC) platform
 * without running the graphic user interface (GUI). At the same time, unit tests, the digital signal
 * process (DSP) driver, and the vector process (VP) driver located in the software develop kit (SDK) are
 * also transplanted into the Ubuntu system to implement encoding in the DSP and running convolutional neural network (CNN) algorithms.<br>
 *
 * - - - -
 *
 * @section porting_ubuntu_system_bg 2. Background Introduction
 *
 * When users develop software on Ambarella SoC platform, third-party tools and libraries are often required.
 * Users must cross-compile and transplant them on the device each time. If the Ubuntu system can run directly
 * on the device, softwares can be installed via application, thus improving the efficiency of
 * developing software.<br>
 *
 * - - - -
 *
 * @section porting_ubuntu_system_preparation 3. Preparation of Ubuntu's Root File System (Rootfs)
 *
 * @subsection porting_ubuntu_system_download_core_sys 3.1 Download and Extract Ubuntu Core System
 *
 * The Ubuntu core system can be downloaded from the official Ubuntu website: http://cdimage.ubuntu.com/ubuntu-base/releases/<br>
 *
 * In this document, version 16.04 is used as an example:<br>
 *
 * @image html porting_ubuntu_version.png "Figure 3-1. Ubuntu Version."
 *
 * Download the `ubuntu-base-16.04.6-base-arm64.tar.gz` file and extract it to the working directory:<br>
 *
 * @image html porting_ubuntu_base_code.png "Figure 3-2. Ubuntu Base Code."
 *
 * Extract the download package to working directory:<br>
 *
 * @code {.c}
 * Host $ tar -xvf ubuntu-base-16.04.6-base-arm64.tar.gz -C $work_dir (Your working directory)
 * @endcode
 *
 * @subsection porting_ubuntu_system_download_qemu 3.2 Download QEMU Simulator and Run Arm Ubuntu Core System
 *
 * Install the QEMU simulator on the host PC:
 *
 * @code {.c}
 * Host $ sudo apt-get install qemu-user-static
 * @endcode
 *
 * QEMU is a powerful simulator that will be used to run the Ubuntu system that is to be ported to the PC.
 * Copy "qemu-arm-static" to the Ubuntu core directory `usr/bin`.
 *
 * @code {.c}
 * Host $ sudo cp /usr/bin/qemu-arm-static $work_dir/usr/bin
 * @endcode
 *
 * Copy the host `resolv.conf` to the Ubuntu core directory `etc`. This step enables Ubuntu core system domain name service (DNS) to work normally.
 *
 * @code {.c}
 * Host $ sudo cp -b /etc/resolv.conf $work_dir/etc/resolv.conf
 * @endcode
 *
 * Mount `proc`, `sys`, and `dev/pts` file systems, then and use "chroot" to enter into the Ubuntu core system.
 *
 * @code {.c}
 * Host $ sudo ch-mount.sh -m $work_dir
 * @endcode
 *
 * Contents of `ch-mount.sh` are listed below:
 *
 * @code {.c}
 * #!/bin/bash
 *
 * function mnt()
 * {
 *   echo "MOUNTING"
 *
 *   sudo mount -t proc /proc ${2}proc
 *   sudo mount -t sysfs /sys ${2}sys
 *   sudo mount -o bind /dev  ${2}dev
 *   sudo mount -o bind /dev/pts ${2}/dev/pts
 *   sudo chroot ${2}
 * }
 *
 * function umnt()
 * {
 *   echo "UNMOUNTING"
 *
 *   sudo umount ${2}proc
 *   sudo umount ${2}sys
 *   sudo umount ${2}dev/pts
 *   sudo umount ${2}dev
 * }
 *
 * if [ "$1" == "-m" ] && [ -n "$2" ]; then
 *   mnt $1 $2
 * elif [ "$1" == "-u" ] && [ -n "$2" ]; then
 *   umnt $1 $2
 * else
 *   echo ""
 *   echo "Either 1'st, 2'nd or both parameters were missing"
 *   echo ""
 *   echo "1'st parameter can be one of these: -m(mount) OR -u(umount)"
 *   echo "2'nd parameter is the full path of the rootfs directory (with trailing '/')"
 *   echo ""
 *   echo "For example: ch-mount -m /media/sdcard/"
 *   echo ""
 *   echo 1st parameter : ${1}
 *   echo 2nd parameter : ${2}
 * fi
 *
 * @endcode
 *
 * After mounting the file system, users can execute Ubuntu's operation in the simulator.
 *
 * @subsection porting_ubuntu_system_configure_ubuntu_core 3.3 Configure Ubuntu Core System
 *
 * 1. Set password for root:
 *
 * @code {.c}
 * ubuntu # passwd root
 * @endcode
 *
 * 2. Add a new user:
 *
 * @code {.c}
 * ubuntu # adduser ambarella
 * @endcode
 *
 * 3. Modify the download repositories of the Ubuntu core system. In China, users can choose University
 *    of Science and Technology, Tsinghua University, Alibaba, and Huawei. <br>
 *
 * 4. After the repositories have been configured, users can install the common softwares:<br>
 *
 * @code {.c}
 * ubuntu # sudo apt-get update --allow-insecure-repositories
 * ubuntu # sudo apt-get install ssh net-tools ethtool vim kmod ... # any interested software
 * @endcode
 *
 *
 * 5. Serial configuration:
 *
 * As ttyS0 is the console serial port on Ambarella platform, the link getty@ttyS0.service
 * must be added to connect getty@.service:<br>
 *
 * @code {.c}
 * ubuntu # ln -s /lib/systemd/system/getty@.service /etc/systemd/system/getty.target.wants/getty@ttyS0.service
 * @endcode
 *
 * 6. Network configuration:
 *
 * The gigabit netword card on Ambarella platform is eth0. Users must create the "eth0" file under `/etc/network/interfaces.d`
 * and configure network-related parameters:<br>
 *
 * @code {.c}
 * ubuntu # touch /etc/network/interfaces.d/eth0
 * ubuntu # vim /etc/network/interfaces.d/eth0
 * @endcode
 *
 * If a static network is configured, the following parameters must be provided:<br>
 *
 * @code {.c}
 * auto eth0
 * iface eth0 inet static
 * address 192.168.137.2
 * netmask 255.255.255.0
 * gateway 192.168.137.1
 * @endcode
 *
 * If a dynamic network is configured, the following contents must be provided:
 * @code {.c}
 * auto eth0
 * iface eth0 inet dhcp
 * @endcode
 *
 * 7. As Ubuntu base rootfs doesn't contain kernel modules (.ko), they are required to be copied
 *    to Ubuntu core system from standard SDK
 *
 * 8. Copy the standard SDK's unit test binaries, lua, 3a binary, and DSP / VP firmware binaries
 *    to Ubuntu core system.<br>
 *
 * 9. Add Ambarella-related drivers that can be loaded automatically when the system boots up:<br>
 *
 * @code {.c}
 * ubuntu # touch /etc/modules-load.d/ambarella
 * ubuntu # vim /etc/modules-load.d/ambarella
 * @endcode
 *
 * Input the driver list that must be loaded, for example:
 *
 * @code {.c}
 * iav
 * dsplog
 * ambad
 * ambdve
 * ambhdmi
 * ambarella_eth
 * ehci-ambarella
 * snd-soc-ak4951-amb
 * snd-soc-ambdummy
 * snd-soc-simple-card
 * @endcode
 *
 * 10. Exit from the Ubuntu core chroot system:
 *
 * @code {.c}
 * ubuntu # exit
 * @endcode
 *
 * 11. Uninstall the rootfs:
 *
 * @code {.c}
 * Host $ sudo ch-mount.sh -u $work_dir
 * @endcode
 *
 * 12. Package the rootfs:
 *
 * @code {.c}
 * Host $ tar zcvf rootfs.tar $work_dir
 * @endcode
 *
 * - - - -
 *
 * @section porting_ubuntu_system_burn_system 4. Burn Root File System into the Device
 *
 * There are two scenarios to burn the rootfs into the evaluation kit (EVK) board:<br>
 *
 * - The EVK board possesses an embedded multi-media controller / card (eMMC). The rootfs can be downloaded directly to the eMMC.
 * - The EVK board just has a NAND and secure digital (SD) slot
 *
 * @subsection porting_ubuntu_system_burn_system_emmc 4.1 Burn the Root File System to eMMC
 *
 * -# Select the boot media for the eMMC on the EVK. Burn the normal firmware (bst_bld_kernel_lnx_release.elf) to the EVK board.
 *
 * -# When the normal firmware has completed burning to the EVK board, boot up the board and format `/dev/mmcblk0p8`.
 *
 *   @code {.c}
 *   board # mkfs.ext4 /dev/mmcblk0p8 -N 2000000
 *   @endcode
 *
 *   @note
 *     The parameter "-N" indicates the number of inodes. Users must configure this parameter according to the actual situation. If the inode
 *     amount is too small, the file cannot be written sequentially, even if there is sufficient disk space.
 *
 * -# Mount the Ubuntu file system partition.
 *
 *   @code {.c}
 *   board # mkdir /temp
 *   board # mount -t ext4 /dev/mmcblk0p8 /temp/
 *   @endcode
 *
 * -# Extract the Ubuntu file system (.tar.gz) to the partition mounted in step 3:
 *   @code {.c}
 *   board # mount -t cifs //192.168.137.1/pcshare /mnt -o username=xxx,password=xxx,vers=3.0
 *   board # tar zxvf /mnt/rootfs.tar.gz -C /temp/
 *   @endcode
 *
 *   @note
 *     The "mount" command enables users to access the rootfs.tar.gz package. Users can use other methods, such as "sdcard" or file transfer protocol (FTP).
 *
 * -# Modify the Ubuntu file system permissions.
 *   @code
 *   board # chown -R root:root /temp
 *   @endcode
 *
 * -# Unmount the Ubuntu file system partition.
 *   @code
 *   board # umount /temp
 *   @endcode
 *
 * -# Reboot the system and enter into AMBoot to modify the booting command (cmdline).
 *
 *   @code
 *   amboot> fdt cmdline console=ttyS0 noinitrd root=/dev/mmcblk0p8 rw rootfstype=ext4 rootwait
 *   amboot> boot
 *   @endcode
 *
 * -# Reboot the system to enter into the Ubuntu system. Log in with the username and password when the rootfs is created.
 *
 * @subsection porting_ubuntu_system_burn_system_sd 4.2 Burn Root File System onto SD Card
 *
 * As the rootfs must be burned onto SD card, Ambarella SD driver must be compiled into the kernel (CV2 is used as an example):
 *
 * -# Modify the kernel configuration and generate the firmware (the CV2_Chestnut EVK is used as an example)
 *   @par For CV2x SDK 3.0 Amba Build:
 *   @code {.c}
 *   Build $ make cv2_ipcam_config
 *   Build $ make defconfig_public_linux
 *   Build $ make menuconfig_public_linux
 *           Device Driver --->
 *             <*> MMC/SD/SDIO card support --->
 * 	              <*> MMC block device driver
 * 	              <*> Ambarella Media Processor SD/MMC Host Controller driver
 *
 *           File System --->
 *             <*> The Extended 4 (ext4) file system
 * 	           [*] JBD2 (ext4) debugging support
 *
 *   Build $ make menuconfig
 *           Ambarella File System Configuration --->
 *             [*] Open Source Software (OSS) --->
 *               [*] Filesystem Tools --->
 *                  [*] Add e2fsprogs app
 *
 *   Build $ make -j32
 *
 *   @endcode
 *   @par For Cooper Amba and Yocto Build:
 *   @code {.c}
 *   Build $ make ipcam_config
 *   Build $ make linux_menuconfig
 *           Device Driver --->
 *             <*> MMC/SD/SDIO card support --->
 * 	              <*> MMC block device driver
 * 	              <*> Ambarella Media Processor SD/MMC Host Controller driver
 *
 *           File System --->
 *             <*> The Extended 4 (ext4) file system
 * 	           [*] JBD2 (ext4) debugging support
 *   @endcode
 *
 *   @par For Amba Build:
 *   @code {.c}
 *   Build $ make menuconfig
 *           Ambarella File System Configuration --->
 *             [*] Open Source Software (OSS) --->
 *               [*] Filesystem Tools --->
 *                  [*] Add e2fsprogs app
 *
 *   Build $ make -j32
 *   @endcode
 *
 *   @par For Yocto Build:
 *   @code {.c}
 *   Build $ make menuconfig
 *   Build $ meta --->
 *   Build $   recipes-devtools --->
 *   Build $     [*] e2fsprogs (meta/recipes-devtools/e2fsprogs)
 *
 *   Build $ make
 *   @endcode
 *
 * -# Burn the firmware to the board using the AmbaUSB tool.
 *
 * -# Insert and format the SD card.
 *   @code
 *   board # mkfs.ext4 /dev/mmcblk1p1 -N 2000000
 *   @endcode
 *
 *   @note
 *     The parameter "-N" indicates the number of inodes. Users must configure this parameter according to the actual situation. If the inode
 *     amount is too small, the file cannot be written sequentially, even if there is sufficient disk space.
 *
 * -# Mount the SD card partition.
 *   @code
 *   board # mkdir /temp
 *   board # mount -t ext4 /dev/mmcblk1p1 /temp/
 *   @endcode
 *
 * -# Extract the Ubuntu file system (.tar.gz) to the partition mounted in step 3:
 *   @code {.c}
 *   board # mount -t cifs //192.168.137.1/pcshare /mnt -o username=xxx,password=xxx,vers=3.0
 *   board # tar zxvf /mnt/rootfs.tar.gz -C /temp/
 *   @endcode
 *
 *   @note
 *     The "mount" command enables users to access the `rootfs.tar.gz` package. Users can use other methods, such as "sdcard" or FTP.
 *
 * -# Modify the Ubuntu file system permission.
 *
 *   @code
 *   board # chown -R root:root /temp
 *   @endcode
 *
 * -# Unmount the Ubuntu file system partition.
 *   @code
 *   board # umount /temp
 *   @endcode
 *
 * -# Reboot the system and enter into AMBoot to modify the booting command (cmdline).
 *
 *   @code
 *   amboot> fdt cmdline console=ttyS0 noinitrd root=/dev/mmcblk1p1 rw rootfstype=ext4 rootwait
 *   amboot> boot
 *   @endcode
 *
 * -# Reboot the system to enter into the Ubuntu system. Log in with the username and password when the rootfs is created.
 *
 *   Figure 4-1 is captured from the board's serial when the CV2 EVK board enters into the Ubuntu shell:
 *
 *   @image html porting_ubuntu_login.png "Figure 4-1. Ubuntu login."
 *
 * - - - -
 *
 * @section porting_ubuntu_system_faq 5. Frequently Asked Questions (FAQ)
 *
 * This section focuses on some issues during the migration process, and the corresponding solutions.<br>
 *
 * <b>Question 1:</b> How can the "kmod" error be fixed when the system boots up?<br>
 * <b>Answer:</b> Connect to the network and install the "kmod" software using "sudo apt-get install kmod".
 *
 * <b>Question 2:</b> How is "sudo" added by a common user?<br>
 * <b>Answer:</b>
 *
 * 1. Log in with the root account.
 *
 * 2. Add writing permission to `/etc/sudoers`.
 *    @code
 *    board # chmod u+w /etc/sudoers
 *    @endcode
 *
 * 3. For example, add sudo permission to "ambarella":
 *    @code
 *    # User privilege specification
 *    root ALL=(ALL) ALL
 *    ambarella ALL=(ALL) ALL
 *    @endcode
 *
 * 4. Remove the writing permission from `/etc/sudoers`.
 *    @code
 *    board # chmod u-w /etc/sudoers
 *    @endcode
 *
 * 5. Grant "setuid" privileges to the sudo program.
 *    @code {.c}
 *    board # chmod 4755 /usr/bin/sudo
 *    @endcode
 *
 * <b>Question 3:</b> What is the solution for when the command user cannot restart the system?<br>
 * <b>Answer:</b> Install dbus-user-session software using "sudo apt-get install dbus-user-session", then execute "sudo reboot".
 *
 * <b>Question 4:</b> What are the steps to update the Ubuntu 16.04 libc version from 2.23 to 2.29?<br>
 * <b>Answer:</b>
 *
 * 1. Use the following commands to compile and install glic 2.29:
 *    @code {.c}
 *    board # wget http://ftp.gnu.org/pub/gnu/glibc/glibc-2.29.tar.gz
 *    board # tar -zxvf glibc-2.29.tar.gz
 *    board # cd glibc-2.29
 *    board # mkdir build && cd build
 *    board # apt-get install make gcc gawk bison -you
 *    board # ../configure --prefix=/usr/
 *    board # make -j8
 *    board # make install DESTDIR={xxx}
 *    @endcode
 *
 * 2. Replace all `.so` files located in `/lib/aarch64-linux-gnu/` with the same file of xxx/lib64.<br>
 *
 * 3. Replace the soft link file /lib/ld-linux-aarch64.so.1 ---> aarch64-linux-gnu/ld-2.23.so with /lib/ld-linux-aarch64.so.1 ---> aarch64-linux-gnu/ld-2.29.so.
 *
 * <b>Question 5:</b> Where can the corresponding .so file for a new library be found?<br>
 * <b>Answer:</b> Execute the "ldconfig" command to find the `.so` file.
 *
 * <b>Question 6:</b> The system cannot be entered when libc is updated. How do users solve this issue?<br>
 * <b>Answer:</b>
 *
 * 1. Reboot the system and enter into the AMBoot shell to modify the command line:
 *    @code
 *    amboot> fdt cmdline console=ttyS0 noinitrd root=/dev/mmcblk0p7 rw rootfstype=ext4
 *    amboot> boot
 *    @endcode
 *
 * 2. Use "mount -t ext4 /dev/mmcblk0p8 /temp" to mount Ubuntu file system.
 *
 * 3. Enter into the Ubuntu system and modify the libc soft link:
 *    @code
 *    board # cd /temp/lib/
 *    board # rm -rf ld-linux-aarch64.so.1
 *    board # ln -s aarch64-linux-gnu/ld-2.29.so ld-linux-aarch64.so.1
 *    board # cd aarch64-linux-gnu
 *    board # rm -rf ld-linux-aarch64.so.1
 *    board # ln -s ld-2.29.so ld-linux-aarch64.so.1
 *    @endcode
 *
 * 4. Uninstall the Ubuntu file system:
 *    @code {.c}
 *    board # cd /
 *    board # umount /temp
 *    @endcode
 *
 * 5. Reboot the system and enter into the AMBoot shell to modify the command line:
 *    @code
 *    amboot> fdt cmdline console=ttyS0 noinitrd root=/dev/mmcblk0p8 rw rootfstype=ext4
 *    amboot> boot
 *    @endcode
 *
 * 6. To prevent subsequent updates to glibc, use the following commands to disable glibc updates:
 *    @code {.c}
 *    board # echo libc hold | dpkg --set-selections
 *    board # echo libc-bin hold | dpkg --set-selections
 *    @endcode
 *
 * - - - -
 *
 * @section porting_ubuntu_system_license 6. License
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
/*! @file doc_sys_opt_dram.h
 * @brief This file defines the doxygen structure of DRAM Optimization.
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

//intro
/*! @page page_sys_dram_opt_doc DESIGN - Memory Layout & Optimization
 *
 * @section dram_opt_history 0. Revision History
 *
 * <table>
 * <caption id="sys_dram_opt_history"></caption>
 * <tr><th> SDK Version              <th> Updated Date         <th> Modification
 * <tr><td> CV5x SDK 0.5             <td> 20211021             <td> Initial Version
 * <tr><td rowspan="6"> CV5x SDK 0.5 <td rowspan="6"> 20220114 <td> Added Section @ref sec_dram_mem_intr.
 * <tr>                                                        <td> Updated Section @ref sec_dram_linux.
 * <tr>                                                        <td> Updated Section @ref sec_dram_iav.
 * <tr>                                                        <td> Updated Section @ref sub_sec_user.
 * <tr>                                                        <td> Updated Section @ref sub_sec_comp.
 * <tr>                                                        <td> Added Section @ref sec_dram_cv52.
 * <tr><td rowspan="6"> CV5x SDK 1.5 <td rowspan="6"> 20220721 <td> Updated Section @ref sec_dram_iav.
 * <tr>                                                        <td> Added Section @ref sub_sec_can.
 * <tr>                                                        <td> Added Section @ref sub_sec_blur.
 * <tr>                                                        <td> Added Section @ref sub_sec_arblur.
 * <tr>                                                        <td> Updated Section @ref sec_dram_cv5.
 * <tr>                                                        <td> Updated Section @ref sec_dram_cv52.
 * <tr><td> CV5x SDK 2.0             <td> 20220801             <td> Migrate this DRAM Optimization document from Word form into Doxygen form.
 * <tr><td> Cooper SDK 1.5           <td> 20230928             <td> Update Section @ref dram_opt_example.
 * <tr><td> Cooper SDK 1.6           <td> 20240110             <td> Update Section @ref dram_opt_example.
 * </table>
 *
 * - - - -
 *
 * @section dram_opt_introduction 1. Introduction
 * The DRAM system consists of four partitions: Linux, image audio video (IAV), image digital signal
 * processing (DSP), and computer vision (CV).  The Linux partition operates the Linux system;
 * the IAV partition is shared by the IAV driver and DSP; the DSP partition is used by DSP; and
 * the CV partition is used by the vector processor (VP).
 *
 * The base addresses and total sizes of the IAV, DSP, and CV-related partitions can be configured
 * using "menuconfig" and the "iav_config.h" file.  If desired, users can change the system to ensure
 * that it fits customized designs, provided that any changes meet the DSP and VP minimum requirements
 * for DRAM size.
 *
 * The continuous memory allocator (CMA) is supported by the Linux kernel and enables the allocation
 * of large physically continuous memory blocks at runtime.  The CMA also allocates and maintains
 * the IAV, DSP, and CV partitions on CV2x.  The IAV and DSP partitions share the same CMA memory
 * pool, while CV has its own.  When Linux boots up, the free memory left in the memory pools
 * is reused by the Linux system.
 *
 * The base addresses and sizes of the CMA memory pools for the IAV, DSP, and CV partitionsare specified
 * in the compile configuration using the default configuration (build $ make cv2x_ipcam_config)
 * for the CV series of chips.
 *
 * @subsection sec_dram_mem_intr 1.1 Memory Layout Introduction
 *
 * The Ambarella CV5x platform supports DRAM sizes of 4 GB, 8 GB, 16 GB, and greater. The chip series
 * targets 8KP30+ encoding, therefore requiring a large DRAM size and bandwidth, as well as high-resolution
 * image signal processing (ISP) and encoding processing.
 *
 * Ambarella divides system memory into the following three categories through the CMA:
 *   - DSP private memory partition
 *      - "DSP + Arm®" access only, CV cannot read or write the memory in this partition.
 *   - CV private memory partition
 *      - "Arm + CV" access only, DSP cannot read or write the memory in this partition.
 *   - DSP and CV shared memory partition
 *      - The memory in this partition can be accessed by "DSP + CV + Arm", Which means
 * DSP, CV, and Arm have accessed to the memory in this partition.
 *
 * For the CV5x platform, Arm has been upgraded to access DRAM with a 40-bit address bitwidth, which
 * exceeds the minimum required to access the entire DRAM. However, the DRAM access address bitwidth
 * of DSP and CV remains 32 bits; as a result, both can access only 4 GB memory space. To address
 * this, different memory layouts will be made for the 4 GB and 8 GB (or > 8 GB) DRAM accordingly.
 *
 * @subsubsection sub_sec_4g_layout 1.1.1 4 GB Memory Layout
 *
 * The total 4GB DRAM size can be accessed by <b>"Arm + CV + DSP"</b>. The figure below shows
 * the system memory layout for 4 GB DRAM size, which is applied to <b>"CV52 Zr"</b> platform.
 *
 * @image html cv5_sys_dram_opt_total_4g.png "4 GB DRAM System Memory Layout."
 *
 * For 4 GB DRAM size on the "CV52 Zr" platform:
 *   - DSP private memory pool size = 2816 MB
 *   - DSP shared memory size = 16 MB
 *   - CV private memory pool size = 512 MB
 *   - CV shared memory size = 0 MB
 *   - Linux memory size = 4096 - 2816 - 512 - 16 = 0x2F400000 = 756 MB
 *
 * @code {.c}
 * 	Memory  --->
 *      (2816) DSP Private Memory size in MB
 *      (16) DSP Shared Memory size in MB
 *      (512) CV Private Memory size in MB
 *      (0) CV Shared Memory size in MB
 * @endcode
 *
 * @subsubsection sub_sec_8g_layout 1.1.2 8 GB (or > 8 GB) Memory Layout
 *
 * Because the DRAM access address bitwidth of both DSP and CV is 32 bits, they are unable
 * to directly access the memory beyond the 4G boundary. To provide them with their own 4
 * GB memory space, the CV5x platform utilizes the address translation table (ATT) mapping
 * for the "DSP Memory Space" (both "DSP Private Pool" and "DSP & VP Shared Pool"), while CV,
 * "CV Private Pool", and "DSP & VP Shared Pool" continue using the default DRAM memory space,
 * as they are both within 4 GB.
 *
 * The process of ATT mapping for "DSP Memory Space" is separated into the following two steps:
 *
 * 1.When performing ATT mapping, "DSP Private Pool" is mapped from 0, which means that its
 * offset in the ATT memory space will be the same with the lower u32 of its DRAM physical
 * address. For example, if the DRAM physical address is 0x1, 0010, 0000, the offset in
 * the ATT memory space will be 0x0010, 0000.
 *
 * 2.Map "DSP & VP Shared Pool" to the end of the 4 GB ATT memory space. Its offset
 * in the ATT memory space will be the same as its DRAM physical address. For example,
 * if the DRAM physical address is 0xFF10, 0000, then its offset in the ATT memory space
 * will also be 0xFF10, 0000.
 *
 * Consequently, the memory layout of the 8G DRAM size is designed as shown in the following diagram.
 *
 * @image html cv5_sys_dram_opt_total_8g.png "8 GB DRAM System Memory Layout."
 *
 * The following table shows the DRAM access limitation for Arm, CV, and DSP.
 * @par 8 GB DRAM Access Limitation for Arm, CV, and DSP
 * <table>
 * <caption id="dram_table_8g_limit"></caption>
 * <tr><th> Element      <th>DRAM Access Limitation
 * <tr><td> Arm          <td> 0~8 GB
 * <tr><td> CV           <td> 0~4 GB
 * <tr><td> DSP          <td> DSP memory space
 * </table>
 *
 * For 8 GB DRAM size on the "CV52 Zr" platform:
 *   - DSP private memory pool size = 2816 MB
 *   - DSP shared memory size = 16 MB
 *   - CV private memory pool size = 512 MB
 *   - CV shared memory size = 0 MB
 *   - Linux memory size = 8192 - 2816 – 512 - 16 = 0x12F400000 = 4852 MB
 *
 * @code {.c}
 * 	Memory  --->
 *      (2816) DSP Private Memory size in MB
 *      (16) DSP Shared Memory size in MB
 *      (512) CV Private Memory size in MB
 *      (0) CV Shared Memory size in MB
 * @endcode
 *
 * - - - -
 *
 * @section dram_opt 2. DRAM Optimization
 *
 * This chapter describes each partition in detail while providing guidelines on
 * how user applications can optimize DRAM usage for their corresponding system.
 * The DRAM utilization can be changed manually for user applications with different
 * requirements. This chapter includes the following sections:
 *
 * <ul>
 * <li> @ref sec_dram_linux
 * <li> @ref sec_dram_iav
 * <li> @ref sec_dram_dsp
 * <li> @ref sec_dram_cv
 * <li> @ref sec_dram_res
 * </ul>
 *
 * When the system boots up, customers can dump the start addresses and sizes of
 * the IAV / DSP / CV sub-partitions using the following commands.
 *
 * Dump the IAV / DSP sub-partitions:
 * @code {.c}
 * board # cat /proc/ambarella/cma
 * @endcode
 *
 * Dump the CV sub-partitions:
 * @code {.c}
 * board # cat /proc/ambarella/cavalry_cma
 * @endcode
 *
 * When the system is in preview or encoding state, customers can check the DSP DRAM
 * usage information using the following commands:
 * @code {.c}
 * board # cat /proc/ambarella/iav_mem
 * @encode
 *
 * @subsection sec_dram_linux 2.1 Linux Partition
 *
 * As shown in picture @ref sub_sec_4g_layout "4 GB DRAM System Memory Layout"
 * and @ref sub_sec_8g_layout "8 GB DRAM System Memory Layout",
 * users must ensure that there is sufficient DRAM for the Linux
 * system by setting the start addresses of the CMA memory pools for the IAV, DSP, and CV
 * partitions. The following configured options are for the CV5x board. The size must be a
 * multiple of 4 MB, as required by the CMA.
 * @code {.c}
 * build $ make menuconfig
 * 	 -*- board (boards)  --->
 *     Memory  --->
 *      (2816) DSP Private Memory size in MB
 *      (16) DSP Shared Memory size in MB
 *      (512) CV Private Memory size in MB
 *      (0) CV Shared Memory size in MB
 * @endcode
 *
 * @subsection sec_dram_iav 2.2 IAV Partition
 *
 * The following figure illustrates the IAV sub-partition.
 *
 * @image html cv5_sys_dram_opt_iav_partion.png "Detailed IAV Sub-Partitions."
 *
 * The following table shows the details of the IAV sub-partitions. All DRAM
 * sizes will be aligned to page sizes (4 KB) in the actual DRAM map.
 *
 * @par IAV Partition Usage Instructions
 * <table>
 * <caption id="dram_iav_partition_usage"></caption>
 * <tr><th> Name    <th>Instruction and Usage    <th> Resiz-able   <th> Default Size  <th> Necessity
 * <tr><td> BSB     <td> Bitstream buffer stores the encoding data (such as H.265, H.264, and MJPEG).<br>
 * The size depends on the total stream bitrate and bitstream data cache time
 * <td> Yes         <td> 32 MB                        <td> Compulsory
 * <tr><td> USR     <td> User data buffer is used to encode from the raw data (both YUV and RGB).<br>
 * Its size depends on raw data size and number.
 * <td> Yes         <td> 0 MB                         <td> Optional
 * <tr><td> MV      <td> Motion vector buffer.
 * <td> Yes         <td> 0 MB                         <td> Optional
 * <tr><td> OVERLAY <td> Overlay buffer is used for on screen display (OSD).<br>
 * Its size depends on the overlay area size and number.
 * <td> Yes         <td> 16 MB                        <td> Optional
 * <tr><td> QPMATRIX QPMATRIX_RAW <td>QP ROI matrix buffer.<br> QP matrix raw buffer.
 * <td> Yes         <td> 10 MB                        <td> Optional
 * <tr><td> WARP    <td> The warp buffer is used for multi-region dewarp and LDC.
 * <td> Yes         <td> 1 MB x N(N: channel number)  <td> Optional
 * <tr><td> QUANT   <td> JPEG quant matrix table is used to improve the MJPEG quality.
 * <td> No          <td> 8 KB                         <td> Compulsory
 * <tr><td> IMG     <td> Image buffer used for 3A.
 * <td> Yes         <td> (5 x N + 1) MB(N: channel number) <td> Compulsory
 * <tr><td> MASK    <td> Single-color / multi-color privacy mask buffer.<br>
 * The size depends on the maximum supported VIN resolution.<br>
 * Single-color: (maximum VIN resolution / 8) x N.<br>
 * Multi-color: maximum VIN resolution x N(N: channel number)
 * <td> Yes         <td> Single-color: 40 MB x N.<br> Multi-color: 0 MB(N: channel number)
 * <td> Optional
 * <tr><td> PYRAMID_POOL     <td> Pyramid buffer pool for the pyramid manual-feed mode.<br>
 * The size depends on the pyramid buffer size and number.
 * <td> Yes                  <td> 0 MB                  <td> Optional
 * <tr><td> CANVAS_POOL      <td> Canvas buffer pool for the canvas manual-feed mode.<br>
 * The size depends on the canvas buffer size and number.
 * <td> Yes                  <td> 0 MB                  <td> Optional
 * <tr><td> BLEND_ALPHA      <td> Alpha blend buffer for the cross-channel stitching.<br>
 * The size depends on the stitching area size and number.
 * <td> Yes                  <td> 0 MB                  <td> Optional
 * <tr><td> BLUR             <td> Blur buffer for the stream privacy protection.<br>
 * The size depends on the maximum blur area size.
 * <td> Yes                  <td> 0 MB                  <td> Optional
 * <tr><td> ARB_BLUR         <td> Arbitrary blur buffer for the stream privacy protection.<br>
 * The size depends on the maximum blur area size and maximum stream number.
 * <td> Yes                  <td> 0 MB                  <td> Optional
 * </table>
 *
 * The following stages specify the size of the IAV sub-partitions for different use cases:<br>
 *    - Compilation stage (for reserved memory management or CMA)<br>
 *        - The compilation stage configures the partition size through "menuconfig", and
 *          then compiles it into the firmware.
 *    - Driver installation stage (only for CMA)<br>
 *        - The driver installation stage sets the driver module parameters to load
 *          different options for the partition size.
 *    - Run-time stage (only for CMA)<br>
 *        - The run-time stage configures and resizes the partition size through
 *          IAV IOCTL on-the-fly while the system runs.
 *
 * The following guidelines provide details to optimize the DRAM size of IAV sub-partitions.
 * @par Details of IAV sub-partitions
 * <table>
 * <caption id="dram_iav_part_usage"></caption>
 * <tr><th> Sub partition           <th> Usage
 * <tr><td> <b>BSB</b>              <td> Adjusts the size of the bitstream buffer according to the total stream bitrate and
 *                                       bitstream data cache time. For more details, refer to Section @ref sub_sec_bsb.
 * <tr><td> <b>Overlay</b>          <td> Adjusts the size of the overlay buffer according to the total overlay area size and
 *                                       number. For more details, refer to Section @ref sub_sec_over.
 * <tr><td> <b>QPM</b>              <td> Adjusts the single QP matrix memory size according to the maximum stream resolution
 *                                       and number. The default value is 128 KB for a 4K resolution. The QPM size can be reduced
 *                                       by more than half for resolutions smaller than 4 MP. For more details, refer to Section @ref sub_sec_qp.
 * <tr><td> <b>WARP</b>             <td> If LDC or dewarp functions are not required, set the warp buffer  size to zero. For
 *                                       more details, refer to Section @ref sub_sec_warp.
 * <tr><td> <b>PM</b>               <td> Adjusts the single-color / multi-color privacy mask matrix memoryaccording to the
 *                                       maximum VIN resolution. The default value is 10 MB set for 4K, but it can be reduced
 *                                       when the VIN resolution is smaller in size. For more details, refer to Section @ref sub_sec_mask.
 * <tr><td> <b>IMG</b>              <td> Adjusts the IMG buffer size according to the requirements of the 3A application. Different
 *                                       encode modes, EIS delay settings, and back pressure margin settings may need a different
 *                                       IMG buffer size.  For more details, refer to Section @ref sub_sec_img.
 * </table>
 *
 * @subsubsection sub_sec_bsb 2.2.1 Bitstream Buffer
 *
 * CV5x supports up to 16 streams. The BSB is used to store the bitstream data generated by all
 * streams encoded by the DSP, which functions as a ring buffer. If the BSB size is too small, the
 * time remaining for Arm to read out the bitstream data will be insufficient, and the data may be
 * overwritten. By default, the BSB size is 10 MB. If there are four streams with a total 20 Mbps
 * (8M + 4M + 4M + 4M) bit rate, then the buffer can cache the bitstream data for 10 (MB) x 8 /
 * 20 (Mbps) = 4s. Typically, 4s of cache time is adequate for Arm to read out the bitstream data.
 *
 * Users should adjust the BSB buffer size according to the number and bitrate of the streams in use.
 *
 *    BSB size = SUM (stream_bitrate x cache_time)<br>
 *    (This example uses cache_time as >= 4s.)
 *
 * The  BSB size can be configured in three stages:
 *  - Compile stage: Sets the BSB buffer size through "menuconfig", then compiles it into the image.
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0x0A00000) DSP Bit Stream Buffer Size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *               (0x0A00000) DSP Bit Stream Buffer Size
 * @endcode
 *  - Driver installation stage: Configures the BSB buffer size through the driver module parameter.
 * @code {.c}
 * board # modprobe ambcma bsb_buf_size=0x0A00000
 * @endcode
 *  - Run-time stage: Dynamically resizes the BSB buffer through IAV IOCTL
 *    (<b>IAV_IOC_ALLOC_MEM_PART</b> and <b>IAV_IOC_FREE_MEM_PART</b>) when the system is running.
 *
 * @subsubsection sub_sec_user 2.2.2 User Data Buffer
 *
 * The user data buffer (USR) is used for cases of encoding from raw data and encoding from memory (EFM).
 *
 * For the case of encoding from raw data, the memory partition size depends on the resolution
 * and raw type (RGB / YUV422). For example, in the case of a 1080p RGB raw encode, the buffer
 * size is (1920 x 2 + 1920 / 2) x 1080 x 5 (5 cycle buffers) = ~25 MB. In the case of a 1080p
 * YUV raw encode, the buffer size is (1920 x 2 + 1920) x 1080 x 5 (5 cycle buffers) = ~30 MB.
 *
 * In EFM cases, the USR partition size depends on the resolution and number of EFM buffers. For
 * example, if the EFM buffer resolution is 1080p and the buffer number is 6, then the USR partition
 * size is (1920 x 1.5) x 1088 x 6 = ~18 MB.
 *
 * The USR size is configured in three stages:
 *  - Compile stage: Sets the internal BSB buffer size through "menuconfig", then compiles it into the image.
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0x4000000) IAV Usr Buffer Size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *              (0x4000000) IAV Usr Buffer Size
 * @endcode
 *  - The driver installation stage, which configures the USR size through the driver module parameter.
 * @code {.c}
 * board # modprobe ambcma usr_buf_size=0x4000000
 * @endcode
 *  - Run-time stage: Dynamically resizes the internal BSB buffer through IAV IOCTL
 *    (<b>IAV_IOC_ALLOC_MEM_PART</b> and <b>IAV_IOC_FREE_MEM_PART</b>) when the system is running.
 *
 * @note
 * If the system does not require encoding from raw data or encoding from memory , the USR size must
 * be set to zero through "menuconfig" or via the driver module parameter, to reduce the DRAM size.
 *
 * @subsubsection sub_sec_mv 2.2.3 Motion Vector Buffer
 *
 * CV5x supports dumping the motion vector (MV) for up to five streams. The MV dump
 * is available only for AVC streams.
 *
 * The basic unit for the MV is a macroblock with 16x16 pixels (MB). Each MV unit occupies 4 bytes,
 * including the motion information in the x and y directions. If the maximum stream size is 3840x2160,
 * the single MV buffer frame size will be (3840 x 2160) / (16 x16) x 4 ~= 128 KB. Usually, a ring
 * buffer with several MV buffer frames is required to cache between the DSP and Arm. This ensures
 * that there is enough time for Arm to read out the MV data before being overwritten by the DSP.
 * If eight frames are used, the total MV buffer size for each stream will be 128 KB x 8 = 1 MB.
 *
 * The MV buffer size of a single stream is configured through "menuconfig":
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0x0100000) IAV Motion Vector Buffer Size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *              (0x0100000) IAV Motion Vector Buffer Size
 * @endcode
 *
 * The maximum stream number that needs MV dump is configured through "menuconfig":
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (2) IAV Max Stream Num with MV statistics
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *              (2) IAV Max Stream Num with MV statistics
 * @endcode
 *
 * The total DRAM size needed for the MV buffer should be the maximum stream number multiplied by the
 * MV buffer size.  With the above settings, it will be 1 MB x 2 = 2 MB.
 *
 * The total MV buffer size can also be specified at the driver installation stage, which configures
 * the total MV buffer size through the driver module parameters.
 * @code {.c}
 * board # modprobe ambcma mv_buf_size=0x200000
 * @endcode
 *
 * @note
 * If the system does not use the MV feature, users can set the MV buffer size to zero through
 * "menuconfig" ,or the driver module parameter to reduce the DRAM size.
 *
 * @subsubsection sub_sec_over 2.2.4 Overlay
 *
 * The CV2x supports 16 independent color look-up tables (CLUT).
 * Each CLUT requires 1 KB of memory.  Only CLUT8 is supported.
 *
 * With CLUT8, each look-up table is an array of 256 entries. The entry is
 * defined for four individual color channels:  Y, U, V, and alpha (transparency).
 * Alpha 0 is the transparent value, 255 is non-transparent.
 *
 * The default configuration for overlay is 8 MB for CV2x chips.
 * Users can change the overlay size to meet their application requirements.
 *
 * The overlay buffer size can be specified in three stages:
 *  - The compile stage configures the overlay buffer size through "menuconfig", and then compiles it to the image.
 * @code {.c}
 * @par For Cooper Amba build
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0x0800000) IAV Overlay Buffer Size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *              (0x0800000) IAV Overlay Buffer Size
 * @endcode
 *  - The driver installation stage configures the overlay buffer size through the driver module parameter.
 * @code {.c}
 * board # modprobe ambcma overlay_buf_size=0x800000
 * @endcode
 *  - The run-time stage configures / resizes the overlay buffer through IAV IOCTL
 *    (<b>IAV_IOC_ALLOC_MEM_PART</b> and <b>IAV_IOC_FREE_MEM_PART</b>) simultaneously while the system is running.
 *
 * @note
 * If the system does not use the stream overlay feature, users can set the overlay buffer size
 * to zero through menuconfig or the driver module parameter in order to reduce the DRAM size.
 *
 * @subsubsection sub_sec_qp 2.2.5 QP Matrix
 *
 * The two configurations below are provided to ensure the effectiveness of the QP matrix buffer.
 *
 * The first configuration is <b>IAV_ROI_NUM_FOR_IPB_FRAMES</b>, which is used to configure
 * the QP matrix number for each stream.  The valid matrix numbers for H26X streams range
 * from one to three inclusive.
 *
 * The default QP matrix value is one, which means there only is one QP matrix.
 * It is shared by the I / P frames. B frame is not enabled.
 *
 * When the QP matrix number is two, there are three different application cases:
 * (1) I / P frames share the same QP matrix. The B frame uses the other QP matrix;
 * (2) I / P frames use different QP matrixes. The B frame is not enabled.
 * (3) I / P frames share the same QP matrix. The P2 frame uses the other QP matrix.
 *
 * When the QP matrix number is three, there are three different application cases:
 * (1) I / P / B frames use different QP matrixes separately;
 * (2) I / P / P2 frames use different QP matrixes separately. The B frame is not enabled.
 * (3) I / P frames share the same QP matrix.  The B / P2 frames use the other two QP matrixes separately.
 *
 * The QPMATRIX number is configured through "menuconfig".
 * @par For Cooper Amba build
 * @code {.C}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           [2] IAV ROI Matrix numbers for I/P/B/P2 frames
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *              [2] IAV ROI Matrix numbers for I/P/B/P2 frames
 * @endcode
 *
 * The second configuration is <b>IAV_MEM_QPM_SIZE</b>. This is used to establish the single QP matrix size.
 * By default, the size is 128 KB to support 4K encoding. This can be used either as an AVC or HEVC QP matrix.
 *
 * To support 4K AVC encoding, the required QP matrix size is (4096 x 2048) / (16 x16) x 4
 * = 128 KB where 16 x 16 is the MB size, and 4 indicates 4 bytes QP matrix item size per MB.
 *
 * To support the 4K HEVC encoding, the required QP matrix size is (4096 x 2048) / (32 x 32)
 * x 12 = 96 KB where 32 x 32 is the CTU size, and 12 indicates 12 bytes QP matrix item size
 * per CTU. In this configuration, 128 KB is enough to support both AVC and HEVC 4K encoding.
 *
 * Based on the above formula, users can customize the QP matrix size according to
 * the encoding type and the maximum stream size that is required.
 *
 * The QPMATRIX size is configured through "menuconfig".
 * @par For Cooper Amba build
 * @code {.C}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *          [0x0020000] IAV QP MATRIX Buffer Size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *              [0x0020000] IAV QP MATRIX Buffer Size
 * @endcode
 *
 * In order to support the frame or the stream synchronization mechanism, there is one active
 * buffer for the user configuration and four internally-used buffers for each stream.
 * Suppose that there are 13 streams, each stream’s QP matrix number is one and size is 128 KB.
 * Thus, the total size is 128 KB x 1 x (1 + 4) x 13 = 8320 KB. If the QP matrix number is three
 * (the maximum value), the total size will be 128 KB x 3 x (1 + 4) x 13 = 24960 KB.
 *
 * The total QP matrix buffer size can also be specified at the driver installation stage, which
 * configures the total QP matrix buffer size through the driver module parameters.
 * @code {.C}
 * board # modprobe ambcma qpm_buf_size=0x1800000
 * @endcode
 *
 * @note
 * If the system does not use the QPMATRIX feature, the QP matrix size can be set to zero through
 * menuconfig or through the driver module parameter in order to reduce DRAM utilization.
 *
 * @subsubsection sub_sec_warp 2.2.6 Warp
 *
 * The warp buffer is reserved to store all warp vectors for fisheye lens or lens distortion
 * correction (LDC). The buffer size is approximately 126 KB per channel; changing this size
 * is unnecessary.  Warp can be configured through "menuconfig".
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           [*] Open warp memory for dewarp
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *              [*] Open warp memory for dewarp
 * @endcode
 *
 * @note
 * If the system does not support or use the fisheye correction and LDC, the user can disable
 * it through "menuconfig" to reduce DRAM utilization.
 *
 * @subsubsection sub_sec_img 2.2.7 Image
 *
 * This buffer is reserved for 3A to store all image signal processor (ISP) configuration parameters.
 * IMG consists of two sub-partitions: (1) The image kernel (IK) buffer, which stores IK
 * configuration parameters. (2) The static bad pixel (SBP) buffer for SBP correction.
 * By default, the SBP buffer is not allocated. Only the IK buffer is allocated, and its buffer
 * size depends on the channel number.  IMG size = 5 x channel_number + 1(MB). For example,
 * if the channel number is two, the IMG size required is 5 x 2 + 1 = 11 MB. Therefore,
 * when one channel is added, an extra 5 MB will be added accordingly. The number of
 * channels is configured by <b>CONFIG_AMBARELLA_MAX_CHANNEL_NUM</b> in "menuconfig", as shown below:
 *
 * @par For Cooper Amba build
 * @code {.c}
 * build $ make menuconfig
 *     drv_modules  --->
 *          private  --->
 *           -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *               (4)   Max VIN Channel Number
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *     meta-ambabsp --->
 *         recipes-video --->
 *           -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *                 (4)   Max VIN Channel Number
 * @endcode
 *
 * In a real use case, users may be required to specify their own IK buffer and SBP buffer sizes.
 * These sizes can be specified in the following two stages. Once specified, they will be
 * merged into the IMG buffer.
 *  - The compile stage configures the IK buffer and SBP buffer sizes through "menuconfig",
 *    then compiles it into the image.
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0xC00000) IAV IMG IK CFG Buffer Size
 *           (0x400000) IAV IMG SBP Buffer Size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *             (0xC00000) IAV IMG IK CFG Buffer Size
 *             (0x400000) IAV IMG SBP Buffer Size
 * @endcode
 *  - The driver installation stage configures the IK buffer and SBP buffer sizes through the driver module parameters.
 * @code {.c}
 * board # modprobe ambcma ik_buf_size=0xC00000 sbp_buf_size=0x400000
 * @endcode
 *
 * @subsubsection sub_sec_quant 2.2.8 QUANT
 *
 * The QUANT buffer size is 4 KB. Usually, there is no need to change this buffer size.
 *
 * @subsubsection sub_sec_mask 2.2.9 Mask
 *
 * The privacy mask (PM) can protect sensitive regions from being leaked by covering them with
 * arbitrarily-shaped areas. Once the PM areas are inserted, they will appear in both the VOUT
 * preview and the encoded streams.
 *
 * Details for privacy mask include the following:
 *  - Privacy mask takes effect on the VIN domain.
 *  - Single-color privacy mask only supports one kind of color at a time. Its granularity can be pixel
 *    level. The corresponding memory partition name is <b>IAV_PART_MASK</b>.
 *
 * For the single-color PM, the default supported maximum resolution is 12 MP (4096 x 3072).
 * Therfore, the maximum size of a single PM buffer is (4096 >> 3) x 3072 = 1.5 MB. There are
 * four internally-used cache buffers, as well as an extra buffer for user application to fill
 * PM data. As a result, the total PM size required for one channel is 1.5 MB x (1 + 4) = 7.5 MB.
 * For multi-channel, the size will be 7.5 MB x N.  N can be found using the
 * <b>CONFIG_AMBARELLA_MAX_CHANNEL_NUM</b>. Users can refer to Section @ref sub_sec_img for more details.
 *
 * The size of the single-color PM buffer can be specified in the driver installation stage,
 * which configures the MASK buffer size through the driver module parameter.
 * @code {.c}
 * board # modprobe ambcma multi_color_mask_buf_size=0x780000
 * @endcode
 *
 * @note
 * If the system does not use the MASK feature, then the MASK buffer size can be set to zero
 * through the driver module parameter, in order to reduce the DRAM size.
 *
 * @subsubsection sub_sec_py 2.2.10 PYRAMID_POOL
 *
 * This buffer is allocated and maintained by the IAV driver only in the pyramid manual-feed mode.
 * Its size depends on the number and size of the pyramid buffer. Because the buffer size can be
 * calculated automatically in the IAV driver, users do not need to change it in the user application.
 *
 * @note
 * If the system does not use the feature of the pyramid manual-feed, users can disable the
 * pyramid manual-feed mode (when entering preview), in order to save the DRAM size.
 *
 * @subsubsection sub_sec_can 2.2.11 CANVAS_POOL
 *
 * This buffer is allocated and maintained by the IAV driver only in the canvas manual-feed mode.
 * Its size depends on the number and size of the canvas buffer. Because the buffer size can
 * be calculated automatically in the IAV driver, users do not need to change it in the user application.
 *
 * @note
 * If the system does not use the canvas manual-feed feature, users can disable the canvas
 * manual-feed mode when entering the preview state to reduce DRAM utilization.
 *
 * @subsubsection sub_sec_raw 2.2.12 RAW_POOL
 *
 * This buffer is allocated and maintained by the IAV driver only in the raw manual-feed mode.
 * Its size depends on the number and size of the raw buffer. Because the buffer size can be
 * automatically calculated in the IAV driver, there is no need for users to change it in the
 * user application.
 *
 * @note
 * If the system does not use the raw manual-feed feature, users can disable the raw
 * manual-feed mode when entering the preview state to reduce DRAM utilization.
 *
 * @subsubsection sub_sec_blend 2.2.13 BLEND_ALPHA
 *
 * This buffer is allocated and maintained by the IAV driver for the alpha blending feature.
 * It is dedicated for multi-channel stitching application cases. Its size depends on the number
 * of the stitched channels and the size of overlapped areas. Because the buffer size can
 * be automatically calculated in the IAV driver, there is no need for users to change it
 * in the user application.
 *
 * @note
 * If the alpha blending feature is not enabled, this buffer will not be allocated.
 *
 * @subsubsection sub_sec_blur 2.2.14 Blur
 *
 * Blur is mainly used for video stream privacy protection. Users can insert multiple blur
 * areas into a video stream to protect the privacy areas. Once blur areas are inserted,
 * the covered areas in the video stream will be severely blurred.
 *
 * The default configuration for blur is 0 MB for CV2x chips (blur is disabled, by default).
 * Users can change the blur size to meet their application requirements.
 *
 * The blur size consists of two parts:  <b>BLUR_CONTENT_SIZE</b> and <b>BLUR_RSV_SIZE</b>. The
 * <b>BLUR_RSV_SIZE</b> is used to store the blur color table and blur commands. Its size is
 * fixed at 50k. The <b>BLUR_CONTENT_SIZE</b> is based on the largest blur area size.
 * The largest blur area size can be described as width x height.
 * <b>BLUR_CONTENT_SIZE</b> = ROUND_UP ((width / 8), 64) x (height / 8).
 *
 * The size of the blur buffer can be specified in three stages:
 *  - Compile stage: Configures the multi-color buffer size through "menuconfig", then compiles it into the image.
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0x0100000) IAV Blur Buffer Size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *                 (0x0100000) IAV Blur Buffer Size
 * @endcode
 *  - Driver installation stage: Configures the blur buffer size through the driver module parameter.
 * @code {.c}
 * board # modprobe ambcma blur_buf_size=0x100000
 * @endcode
 *  - Run-time stage: Configures / resizes the blur buffer through IAV IOCTL (<b>IAV_IOC_ALLOC_MEM_PART</b>
 *    and <b>IAV_IOC_FREE_MEM_PART</b>) simultaneously while the system is running.
 *
 * @note
 * If the system does not use the stream blur feature, users can disable it through "menuconfig" or
 * the driver module parameter, in order to reduce the DRAM size.
 *
 * @subsubsection sub_sec_arblur 2.2.15 Arbitrary Blur
 *
 * Arbitrary blur is used mainly for video stream privacy protection. Users can insert multiple
 * blur areas into a video stream to protect the privacy areas. Once blur areas are inserted,
 * the covered areas in the video stream will be blurred severely. Compared with blur, arbitrary
 * blur offers users more flexibility. Arbitrary blur also allows users to customize their blur
 * area shapes through changing specified blur area memory.
 *
 * The default configuration for arbitrary blur is 0 MB for CV2x chips, which means arbitrary blur
 * is disabled by default. Users can change the arbitrary blur size to meet their application requirements.
 *
 * The single largest arbitrary blur area size can be described as:
 *   - Single_arbitrary_blur_size_x = ROUND_UP ((width / 8), 64) * (height / 8) *
 *     ring_buffer_num (x = 0, 1, 2...)
 *   - stream_y _arbitrary_blur_size = ∑ Single_arbitrary_blur_size_x (x = 0, 1, 2...)
 *   - total_arbitrary_blur_size = ∑ stream_y _arbitrary_blur_size (y = 0, 1, 2...)
 *   - "x" is the serial number of arbitrary blue area and "y" is the serial number of stream.
 *   - Single_arbitrary_blur_size_x: The arbitrary blur size for the single area which
 *     the serial number is x.
 *   - stream_y _arbitrary_blur_size: The arbitrary blur size for the single stream which
 *     the serial number is y.
 *   - total_arbitrary_blur_size: The totally needed arbitrary blur size.
 *
 * The size of the blur buffer can be specified in three stages:
 *  - Compile stage: Configures the multi-color buffer size through "menuconfig", then compiles it into the image.
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0x0100000) IAV Blur Buffer Size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *                 (0x0100000) IAV Blur Buffer Size
 * @endcode
 *  - Driver installation stage: Configures the blur buffer size through the driver module parameter.
 * @code {.c}
 * board # modprobe ambcma abr_blur_buf_size=0x100000
 * @endcode
 *  - Run-time stage: Configures / resizes the blur buffer through IAV IOCTL (<b>IAV_IOC_ALLOC_MEM_PART</b>
 *    and <b>IAV_IOC_FREE_MEM_PART</b>) simultaneously, while the system is running.
 *
 * @note
 * If the system does not use the stream blur feature with arbitrary shape, users can disable
 * it through "menuconfig" or the driver module parameter, in order to reduce the DRAM size.
 *
 * @subsection sec_dram_dsp 2.3 Digital Signal Processor Partition
 *
 * Digital signal processor (DSP) partition includes the DSP Buffer, DEF_CMD, UCODE, DSP_LOG,
 * DSP_RSV, and more, as shown in the following figure.
 *
 * @image html cv5_sys_dram_opt_dsp_alloc.png "Detailed DSP Partition Allocation."
 *
 * @subsubsection sub_sec_comp 2.3.1 Composition
 *
 * The DSP partition is composed of the DSP buffer and other fixed-size sub-partitions, including
 * the DEF_CMD (16 KB), ucode firmware (10 MB), the DSP log buffer (512 KB), the DSP reserved buffer
 * (~500 KB), and more. The DSP buffer can be resized, depending on the VIN resolution, channel number,
 * encode mode, stream number, stream resolution, and other required values. On the CV5x EVK board,
 * the size of the DSP buffer has been set to 2816 MB to accommodate most use cases.
 *
 *     <b>DSP partition = DSP buffer + 12 MB (DEF_CMD + UCODE + DSP_LOG + DSP_RSV …)</b>
 *
 * After entering the preview / encoding state, users can input command "dmesg | grep MB" to check the actual
 * DSP buffer size used by DSP. This is also the minimum DSP buffer size to run the current case.
 * See the following result:<br>
 *     <b>handle_dsp_cfg_msg(131): DSP DRAM Used: 393 MB</b><br>
 *     (Limited size is defined as the total DSP buffer size.)
 *
 * With the minimum required DSP buffer size (393 MB) reported by DSP, users can accommodate the current DSP
 * buffer size (2816 MB) to meet the minimum requirements of their use cases.
 *
 * The minimum required DSP buffer size depends on various DSP configurations such as encode mode, VIN
 * resolution and HDR / linear mode, EIS delay count, VIN back pressure margin, canvas size and number,
 * and maximum stream size and number. For each canvas, the buffer pool is maintained by the DSP. The
 * buffer number of the buffer pool depends on the canvas extra buffer and the encode dummy latency.
 * By default, with no extra buffer or encode dummy latency, each canvas buffer pool has a minimum of
 * 4 canvas buffer items, costing 4x the canvas size memory. As each canvas and stream costs considerable
 * DRAM space, disabling unnecessary canvases and streams is highly recommended to reduce DRAM utilization.
 *
 * The following table shows the extra DRAM consumption for different options.
 * @par Details of the DSP Buffer Size-Related Options
 * <table>
 * <caption id="dram_detail_dsp_option"></caption>
 * <tr><th> Option                      <th> DRAM Size
 * <tr><td> Canvas extra buffer         <td> Canvas size
 * <tr><td> Encode dummy latency        <td> Canvas size
 * <tr><td> EIS delay count             <td> VIN frame size
 * </table>
 *
 * The size of the DSP buffer can be specified in two stages:
 *  - Compile stage: Sets the extra raw buffer size through "menuconfig", then compiles it into the image.
 * @par For Cooper Amba build
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *           (0xB0000000) DSP buffer size
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-ambabsp --->
 *      recipes-video --->
 *          -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header) --->
 *                (0xB0000000) DSP buffer size
 * @endcode
 *  - Driver installation stage: Configures the DSP buffer size through the driver module parameter.
 * @code {.c}
 * board # modprobe ambcma dsp_buf_size=0xB0000000
 * @endcode
 *
 * @subsubsection sub_sec_exampl_23 2.3.2 Examples
 *
 * The following examples show the total DSP DRAM usage for typical use cases.
 * @subsubsection dram_example_1 Example 1 IMX274_mipi / Mode 5 / 4Kp H.265 + 1080p H.265 + 4Kp MJPEG.
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg cv5_vin0_4k_linear.lua
 * board # test_encode -A -H 3840x2160 -b 0 -e -B -H 1920x1080 -b 2 -e -C -m 3840x2160 –b 3 -e
 * DRAM:  512 MB
 * @endcode
 *
 * @subsection sec_dram_cv 2.4 CV Partition
 *
 * The sub-partitions of CV partition can be divided into two categories:  CMD, MSG, LOG, and ucode, which are
 * reserved for internal use; and, the remaining USR sub-partitions, which are allocated and maintained by user
 * applications. The sizes of the USR sub-partitions depend on the type of neural network (NN) deployed by the user applications.
 *
 * @image html cv5_sys_dram_opt_cv_alloc.png "Detailed CV Partition Allocation."
 *
 * @subsubsection sub_sec_exampl_24 2.4.1 Examples
 *
 * The following examples show the total CV DRAM usage for various neural networks.
 * @subsubsection dram_example_2 Example 2 MTCNN on the Timn (CV5) Board.
 * @code {.c}
 * board # modprobe cavalry; cavalry_load -f /lib/firmware/cavalry.bin –r
 * board # test_nnctrl -w -t 5000 &
 * Iteration number [5000]
 * board # cat /proc/ambarella/cavalry_cma
 * mmb   phys[start-end]        size        kern-virt[start-end]                   ref_cnt  cache  recycle  pid    src_type
 * 0000  0x30000000-0x30400000  0x00400000  0x00000000731e466f-0x000000006e9f230f
 * ----
 * 0001  0x30400000-0x34401000  0x04001000  0x000000005b9b7810-0x000000005b0f8884  1        0      1    284(Alive)  User
 * @endcode
 *
 * @note
 *  - "<b>0000</b>" is the self-used memory, which is about <b>4 MB</b>.
 *  - "<b>0001</b>" is used by "test_nnctrl -w -t 5000 &", which is about <b>64 MB</b>.<br>
 * For details, please refer to @a LIBRARY @a - @a Cavalry_Mem @a Library @a API in Doxygen.
 *
 * @subsection sec_dram_res 2.5 Resource Memory Layout Configuration
 *
 * For mask, multi-color mask, warp, and QP matrix (QPM) partitions, the memory layout can
 * be configured according to actual use cases for different customers. The memory size of these
 * partitions can be customized gradually, according to the memory-related parameters.
 *
 * The memory must be configured at the boot stage, before the DSP enters the preview state.
 *
 * The example below shows how to configure the resource memory layout in the Lua file:
 * @code {.c}
 * resource_mem_cfg = {
 *     max_chan_num = 2,
 *     max_stream_num = 3,
 *     channels_mem = {
 *         {
 *             mask_possible = 1,
 *             warp_possible = 0,
 *             mask_buf_max_num = 5,
 *             warp_buf_max_num = 0,
 *             warp_area_max_num = 0,
 *             max_vin = {3840, 2160},
 *         },
 *         {
 *             mask_possible = 1,
 *             warp_possible = 0,
 *             mask_buf_max_num = 5,
 *             warp_buf_max_num = 0,
 *             warp_area_max_num = 0,
 *             max_vin = {1920, 1080},
 *         },
 *     },
 *     streams_mem = {
 *         {
 *             qpm_possible = 1,
 *             qpm_max_matrix_num = 2,
 *             qpm_buf_max_num = 7,
 *             max_stream = {3840, 2160},
 *         },
 *         {
 *             qpm_possible = 1,
 *             qpm_max_matrix_num = 3,
 *             qpm_buf_max_num = 6,
 *             max_stream = {1920, 1080},
 *         },
 *         {
 *             qpm_possible = 1,
 *             qpm_max_matrix_num = 1,
 *             qpm_buf_max_num = 5,
 *             max_stream = {1280, 720},
 *         },
 *     },
 * }
 * @endcode
 *
 * @par Usage
 * <table>
 * <caption id="dram_para_usage"></caption>
 * <tr><th> Sub partition              <th> Usage
 * <tr><td> max_chan_num               <td> specify the maximum channel number for the PM and WARP memory layout configuration.
 * <tr><td> max_stream_num             <td> specify the maximum stream number for the QPM memory layout configuration.
 * <tr><td> warp_possible              <td> specify whether the warp memory needs to be allocated in each channel.
 * <tr><td> mask_possible              <td> specify whether the privacy mask (PM) memory needs to be allocated in each channel.
 * <tr><td> mask_buf_max_num           <td> specify the maximum allocation of PM buffers in each channel. 1 is used for
 *                                          user application configuration, and the others are used to toggle between IAV and DSP.
 * <tr><td> warp_buf_max_num           <td> specify the maximum allocated warp buffer number in each channel. 1 is used for
 *                                          user application configuration, and the others are used to toggle between IAV and DSP.
 * <tr><td> warp_area_max_num          <td> specify the maximum allocated warp area number in each channel. For LDC / EIS use cases, the maximum
 *                                          number should be one. For the dewarp use cases, the maximum number of configurations is up to twelve.
 * <tr><td> max_vin {width, height}    <td> specify the maximum possible VIN input width and height for PM / WARP memory allocation.
 * <tr><td> qpm_possible               <td> specify whether QPM (QP matrix) memory is needed to allocate in each encode stream.
 * <tr><td> qpm_buf_max_num            <td> specify the maximum allocated QPM buffer number in each encode stream. One is used for user
 *                                          application configuration, and the others are used to toggle between IAV and DSP.
 * <tr><td> qpm_max_matrix_num         <td> specify the maximum allocated QPM matrix number in each encode stream. The maximum number
 *                                          can be up to three.  When the number is one, it may mean I / P shares the same QP matrix.
 *                                          When the number is two, it may mean different QP matrixes for I / P frames, or I / P frames
 *                                          share one matrix and B frames use the other one. When the number is three, it may mean
 *                                          different QP matrixes for I / P / B frames.
 * <tr><td> max_stream {width, height} <td> specify the maximum possible stream width and height for QP matrix memory allocation.
 * </table>
 *
 * @subsubsection sub_sec_exampl_25 2.5.1 Examples
 *
 * This section provides common examples of configuring memory layout resource through
 * Lua, including warp, single-color PM, multi-color PM, and QPM.
 *  - Unit test commands to configure memory layout resource.
 * @subsubsection  dram_example_3 Example 3 Enables the Memory Layout Resource Configuration.
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3 lane=2
 * board # test_tuning -a&
 * board # test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_4k_linear_mem_cfg.lua –resource-mem-cfg-enable 1
 * @endcode
 *  - Typical Lua examples to configure warp, single-color PM, multi-color PM, or QPM memory layout resource.
 *
 * The following example shows a warp memory layout resource, including three warp buffers (one for user
 * app, two for IAV / DSP usage).  Each warp buffer supports up to two warp areas.
 * @subsubsection  dram_example_4 Example 4 Set Warp Memory Layout through Lua.
 * @code {.c}
 *  resource_mem_cfg = {
 *      max_chan_num = 1,
 *      max_stream_num = 1,
 *      channels_mem = {
 *         {
 *              warp_possible = 1,
 *              warp_buf_max_num = 3,
 *              warp_area_max_num = 2,
 *              mask_possible = 0,
 *              mask_buf_max_num = 0,
 *              max_vin = {3840, 2160},
 *         },
 *      },
 *      streams_mem = {
 *         {
 *              qpm_possible = 0,
 *              qpm_max_matrix_num = 0,
 *              qpm_buf_max_num = 0,
 *              max_stream = {3840, 2160},
 *         },
 *      },
 *  },
 * @endcode
 *
 * The following example shows single-color PM resource memory layout, including three single-color
 * PM buffers (one for user app, two for IAV / DSP usage).  The maximum VIN size is {3840, 2160}.
 * @subsubsection dram_example_5 Example 5 Set Single-Color Privacy Mask Memory Layout through Lua.
 * @code {.c}
 *  resource_mem_cfg = {
 *      max_chan_num = 1,
 *      max_stream_num = 1,
 *      channels_mem = {
 *          {
 *              warp_possible = 0,
 *              warp_buf_max_num = 0,
 *              warp_area_max_num = 0,
 *              mask_possible = 1,
 *              mask_buf_max_num = 3,
 *              max_vin = {3840, 2160},
 *          },
 *      },
 *      streams_mem = {
 *          {
 *              qpm_possible = 0,
 *              qpm_max_matrix_num = 0,
 *              qpm_buf_max_num = 0,
 *              max_stream = {3840, 2160},
 *          },
 *      },
 *  },
 * @endcode
 *
 * The following example shows QPM resource memory layout, including three QP matrix buffers (one for
 * user app, two for IAV / DSP usage) for each stream.  Each buffer has three QP matrixes for I / P /
 * B frames, respectively.
 * @subsubsection dram_example_6 Example 6 Set QP Matrix Memory Layout through Lua.
 * @code {.c}
 * resource_mem_cfg = {
 *      max_chan_num = 1,
 *      max_stream_num = 1,
 *      channels_mem = {
 *          {
 *              warp_possible = 0,
 *              warp_buf_max_num = 0,
 *              warp_area_max_num = 0,
 *              mask_possible = 0,
 *              mask_buf_max_num = 0,
 *              max_vin = {3840, 2160},
 *          },
 *      },
 *      streams_mem = {
 *          {
 *              qpm_possible = 1,
 *              qpm_buf_max_num = 3,
 *              qpm_max_matrix_num = 3,
 *              max_stream = {3840, 2160},
 *          },
 *      },
 * },
 * @endcode
 *
 * The following example shows the typical user case of disabling warp, single-color PM,
 * multi-color PM, and QPM memory layout through Lua.
 * @subsubsection dram_example_7 Example 7 Reset Memory Layout through Lua.
 * @code {.c}
 *	resource_mem_cfg = {
 *      max_chan_num = 1,
 *      max_stream_num = 1,
 *      channels_mem = {
 *          {
 *              warp_possible = 0,
 *              warp_buf_max_num = 0,
 *              warp_area_max_num = 0,
 *              mask_possible = 0,
 *              mask_buf_max_num = 0,
 *              max_vin = {3840, 2160},
 *          },
 *      },
 *      streams_mem = {
 *          {
 *              qpm_possible = 0,
 *              qpm_max_matrix_num = 0,
 *              qpm_buf_max_num = 0,
 *              max_stream = {3840, 2160},
 *          },
 *      },
 * },
 * @endcode
 *
 * - - - -
 *
 * @section dram_opt_example 3. Examples of Memory Allocation
 * This chapter includes the following sections:
 *
 * <ul>
 * <li> @ref sec_dram_s5mp
 * <li> @ref sec_dram_s4k
 * <li> @ref sec_dram_s8k
 * <li> @ref sec_dram_q5mp
 * <li> @ref sec_dram_q4k
 * </ul>
 *
 * @subsection sec_dram_s5mp 3.1 Single 5MP VIN
 *
 * @subsubsection dram_example_8 Example 8 Single VIN 5MP with Stream Overlay and Single-Color PM.
 * This case has a single 5MP30 linear VIN input and 5MP30 AVC + 1080p30 AVC+ 5MP1 MJPEG streams
 * on encode mode 5. The largest overlay area is full screen (2592 x 1944) and the single-color
 * privacy mask covers the full VIN (2592 x 1944).
 *
 * Both CV5 and CV72 are used single core for IDSP and encoder. If CV5 uses dual core for
 * IDSP and encoder, CV5 may take more DRAM size than CV72.
 *
 * The Lua script can be found <a href="script/single_5mp_vin.lua" target="_blank"><b>here</b></a>.
 *
 * @par Single 5MP VIN Case Memory Allocation for IAV and DSP
 *
 * <table>
 * <caption id="single_5mp_case_allocation"></caption>
 * <tr><th> Major                          <th> Sub1       <th> Sub2              <th> CV5           <th> CV72
 * <tr><td rowspan="14"> <b>IAV / DSP</b>  <td>            <td> <b>Total Size</b> <td> <b>418 MB</b> <td> <b>418 MB</b>
 * <tr>                                    <td> <b>DSP</b> <td> <b>DSP_BUFFER</b> <td> <b>268 MB</b> <td> <b>287 MB</b>
 * <tr>                                    <td> DSP        <td> DSP_DEF_CMD       <td> 16 KB         <td> 32 KB
 * <tr>                                    <td> DSP        <td> DSP_LOG           <td> 4 MB          <td> 4 MB
 * <tr>                                    <td> IAV        <td> Quant             <td> 12 KB         <td> 12 KB
 * <tr>                                    <td> DSP        <td> DSP Reserved      <td> 1204 KB       <td> 2148 KB
 * <tr>                                    <td> DSP        <td> DSP_UCODE         <td> 11 MB         <td> 11 MB
 * <tr>                                    <td> IAV        <td> IMG               <td> 65 MB          <td> 65 MB
 * <tr>                                    <td> IAV        <td> BSH               <td> 16 KB         <td> 16 KB
 * <tr>                                    <td> IAV        <td> IAV Reserved      <td> 3160 KB       <td> 5 MB
 * <tr>                                    <td> IAV        <td> BSB               <td> 32 MB         <td> 10 MB
 * <tr>                                    <td> IAV        <td> Overlay           <td> 11 MB         <td> 11 MB
 * <tr>                                    <td> IAV        <td> QP matrix         <td> 13 MB         <td> 13 MB
 * <tr>                                    <td> IAV        <td> Privacy Mask      <td> 10 MB         <td> 8 MB
 * </table>
 *
 * @subsection sec_dram_s4k 3.2 Single 4K VIN
 *
 * @subsubsection dram_example_9 Example 9 Single VIN 4K with Stream Overlay and Single-color PM.
 * This case uses a single 4Kp30 linear VIN input and 4Kp30 AVC + 1080p30 AVC + 4Kp1 MJPEG streams on encode
 * mode 5. The largest overlay area is full screen (3840 x 2160) and the single-color privacy mask
 * covers the full VIN (3840 x 2160).
 *
 * Both CV5 and CV72 are used single core for IDSP and encoder. If CV5 uses dual core for
 * IDSP and encoder, CV5 may take more DRAM size than CV72.
 *
 * The Lua script can be found <a href="script/single_4k_vin.lua" target="_blank"><b>here</b></a>.
 *
 * The following table lists the case for IAV / DSP DRAM layout:
 * @par Single 4K VIN Case Memory Allocation for IAV and DSP
 * <table>
 * <caption id="single_4k_case_allocation"></caption>
 * <tr><th> Major                          <th> Sub1       <th> Sub2              <th> CV5           <th> CV72
 * <tr><td rowspan="15"> <b>IAV / DSP</b>  <td>            <td> <b>Total Size</b> <td> <b>521 MB</b> <td> <b>508 MB</b>
 * <tr>                                    <td> <b>DSP</b> <td> <b>DSP_BUFFER</b> <td> <b>353 MB</b> <td> <b>367 MB</b>
 * <tr>                                    <td> DSP        <td> DSP_DEF_CMD       <td> 16 KB         <td> 32 KB
 * <tr>                                    <td> DSP        <td> DSP_LOG           <td> 4 MB          <td> 4 MB
 * <tr>                                    <td> IAV        <td> Quant             <td> 12 KB         <td> 12 KB
 * <tr>                                    <td> DSP        <td> DSP Reserved      <td> 1204 KB       <td> 2148 KB
 * <tr>                                    <td> DSP        <td> DSP_UCODE         <td> 11 MB         <td> 11 MB
 * <tr>                                    <td> IAV        <td> IMG               <td> 65 MB         <td> 65 MB
 * <tr>                                    <td> IAV        <td> BSH               <td> 16 KB         <td> 16 KB
 * <tr>                                    <td> IAV        <td> IAV Reserved      <td> 3160 KB       <td> 5 MB
 * <tr>                                    <td> DSP        <td> DSP_FIFO          <td> 60 KB         <td> 76 KB
 * <tr>                                    <td> IAV        <td> BSB               <td> 32 MB         <td> 10 MB
 * <tr>                                    <td> IAV        <td> Overlay           <td> 17 MB         <td> 17 MB
 * <tr>                                    <td> IAV        <td> QP matrix         <td> 13 MB         <td> 13 MB
 * <tr>                                    <td> IAV        <td> Privacy Mask      <td> 21 MB         <td> 12 MB
 * </table>
 *
 * @subsection sec_dram_s8k 3.3 Single 8K VIN
 *
 * @subsubsection dram_example_10 Example 10 Single VIN 8K with Stream Overlay and a Single-color PM.
 * This case uses a single 8KP30 linear VIN and 8KP30 AVC stream on encode
 * mode 0. The largest overlay area is full screen (7680 x 4320) and the single-color privacy mask
 * covers the full VIN (7680 x 4320).
 * Due to the HW limitation, CV72 can only support 8KP AVC and 8KP MJPEG encode at low frame rate,
 * it <b>cannot</b> support 8KP HEVC encode.
 *
 * Both CV5 and CV72 are used single core for IDSP and encoder. If CV5 uses dual core for
 * IDSP and encoder, CV5 may take more DRAM size than CV72.
 *
 * The Lua script can be found <a href="script/single_8k_vin.lua" target="_blank"><b>here</b></a>.
 *
 * The following table lists the case for IAV / DSP DRAM layout:
 *
 * @par Single 8K VIN Case Memory Allocation for the IAV and DSP.
 * <table>
 * <caption id="single_8k_case_allocation"></caption>
 * <tr><th> Major                         <th> Sub1       <th> Sub2              <th> CV5            <th> CV72
 * <tr><td rowspan="14"> <b>IAV / DSP</b> <td>            <td> <b>Total Size</b> <td> <b>956 MB</b> <td> <b>924 MB</b>
 * <tr>                                   <td> <b>DSP</b> <td> <b>DSP_BUFFER</b> <td> <b>715 MB</b> <td> <b>732 MB</b>
 * <tr>                                   <td> DSP        <td> DSP_DEF_CMD       <td> 16 KB          <td> 32 KB
 * <tr>                                   <td> DSP        <td> DSP_LOG           <td> 4 MB           <td> 4 MB
 * <tr>                                   <td> IAV        <td> Quant             <td> 12 KB          <td> 12 KB
 * <tr>                                   <td> DSP        <td> DSP Reserved      <td> 1204 KB        <td> 2148 KB
 * <tr>                                   <td> DSP        <td> DSP_UCODE         <td> 11 MB          <td> 11 MB
 * <tr>                                   <td> IAV        <td> IMG               <td> 65 MB          <td> 65 MB
 * <tr>                                   <td> IAV        <td> BSH               <td> 16 KB          <td> 16 KB
 * <tr>                                   <td> IAV        <td> IAV Reserved      <td> 3160 KB        <td> 5 MB
 * <tr>                                   <td> IAV        <td> BSB               <td> 32 MB          <td> 10 MB
 * <tr>                                   <td> IAV        <td> Overlay           <td> 32 MB          <td> 32 MB
 * <tr>                                   <td> IAV        <td> QP matrix         <td> 13 MB          <td> 13 MB
 * <tr>                                   <td> IAV        <td> Privacy Mask      <td> 79 MB          <td> 48 MB
 * </table>
 *
 *
 * @subsection sec_dram_q5mp 3.4 Quad 5 MP VIN
 *
 * @subsubsection dram_example_11 Example 11 Quad VIN 5MP with Stream Overlay and a Single-color PM.
 * This case has dual 5MP30 linear VIN and dual 5MP30 AVC streams on encode mode 5. If four
 * streams need overlay and single-color PM, the largest overlay area must be full screen
 * (2592 x 1944) and the single-color privacy mask covers the full VIN (2592 x 1944).
 *
 * Both CV5 and CV72 are used single core for IDSP and encoder. If CV5 uses dual core for
 * IDSP and encoder, CV5 may take more DRAM size than CV72.
 *
 * The Lua script can be found <a href="script/quad_5m_vin.lua" target="_blank"><b>here</b></a>.
 *
 * The following details show the memory allocation of the IAV / DSP sub-partitions.
 * Note that the memory sizes listed in the following table are 4 KB-aligned.
 *
 * <b>IMG</b> calculation: <br>
 *    8 x 4 + 1 = 21 MB
 *
 * <b>QPMATRIX</b> calculation: <br>
 *   (128 x 20) x (1 + 4) = 10 MB
 *
 * <b>Overlay</b> calculation:<br>
 *    ROUND_UP(2592, 64) x 1944 x 2 + ROUND_UP(1920, 64) x 1080 = 19 MB
 *
 * <b>Mask</b> calculation:<br>
 *    ROUND_UP ((2592 / 8), 64) x 1944 x (1 + 4) x 4 = 10 MB.
 *
 * The following table lists the IAV / DSP DRAM layout:
 * @par Quad 5MP VIN Case Memory Allocation for the IAV and DSP.
 * <table>
 * <caption id="quad_5mp_case_allocation"></caption>
 * <tr><th> Major                         <th> Sub1       <th> Sub2              <th> CV5           <th> CV72
 * <tr><td rowspan="14"> <b>IAV / DSP</b> <td>            <td> <b>Total Size</b> <td> <b>734 MB</b> <td> <b>744 MB</b>
 * <tr>                                   <td> <b>DSP</b> <td> <b>DSP_BUFFER</b> <td> <b>576 MB</b> <td> <b>599 MB</b>
 * <tr>                                   <td> DSP        <td> DSP_DEF_CMD       <td> 16 KB         <td> 32 KB
 * <tr>                                   <td> DSP        <td> DSP_LOG           <td> 4 MB          <td> 4 MB
 * <tr>                                   <td> IAV        <td> Quant             <td> 12 KB         <td> 12 KB
 * <tr>                                   <td> DSP        <td> DSP Reserved      <td> 1204 KB       <td> 2148 KB
 * <tr>                                   <td> DSP        <td> DSP_UCODE         <td> 11 MB         <td> 11 MB
 * <tr>                                   <td> IAV        <td> IMG               <td> 65 MB         <td> 65 MB
 * <tr>                                   <td> IAV        <td> BSH               <td> 16 KB         <td> 16 KB
 * <tr>                                   <td> IAV        <td> IAV Reserved      <td> 3160 KB       <td> 5 MB
 * <tr>                                   <td> IAV        <td> BSB               <td> 32 MB         <td> 10 MB
 * <tr>                                   <td> IAV        <td> Overlay           <td> 19 MB         <td> 20 MB
 * <tr>                                   <td> IAV        <td> QP matrix         <td> 13 MB         <td> 13 MB
 * <tr>                                   <td> IAV        <td> Privacy Mask      <td> 10 MB         <td> 15 MB
 * </table>
 *
 *
 * @subsection sec_dram_q4k 3.5 Quad 4K VIN
 *
 * @subsubsection dram_example_12 Example 12 Quad VIN 4K with Stream Overlay and Single-color PM.
 * This case uses the quad 4KP30 linear VIN and quad groups "4KP30 HEVC"
 * streams on encode mode 5. If 12x streams must use the overlay and a single-color PM, the
 * largest overlay area must be full screen (3840 x 2160) and the single-color privacy mask
 * must cover the full VIN (3840 x 2160).
 * Due to the HW limitation, CV72 can only support quad 4K HEVC encode at lower frame
 * rate but not 30fps.
 *
 * Both CV5 and CV72 are used single core for IDSP and encoder. If CV5 uses dual core for
 * IDSP and encoder, CV5 may take more DRAM size than CV72.
 *
 * The Lua script can be found <a href="script/quad_4k_vin.lua" target="_blank"><b>here</b></a>.
 *
 * The following table lists the IAV / DSP DRAM layout:
 * @par Quad 4K VIN Case Memory Allocation for the IAV and DSP
 * <table>
 * <caption id="quad_4k_case_allocation"></caption>
 * <tr><th> Major                         <th> Sub1       <th> Sub2              <th> CV5            <th> CV72
 * <tr><td rowspan="14"> <b>IAV / DSP</b> <td>            <td> <b>Total Size</b> <td> <b>1015 MB</b> <td> <b>1035 MB</b>
 * <tr>                                   <td> <b>DSP</b> <td> <b>DSP_BUFFER</b> <td> <b>833 MB</b>  <td> <b>845 MB</b>
 * <tr>                                   <td> DSP        <td> DSP_DEF_CMD       <td> 16 KB          <td> 32 KB
 * <tr>                                   <td> DSP        <td> DSP_LOG           <td> 4 MB           <td> 4 MB
 * <tr>                                   <td> IAV        <td> Quant             <td> 12 KB          <td> 12 KB
 * <tr>                                   <td> DSP        <td> DSP Reserved      <td> 1024 KB        <td> 2148 KB
 * <tr>                                   <td> DSP        <td> DSP_UCODE         <td> 11 MB          <td> 11 MB
 * <tr>                                   <td> IAV        <td> IMG               <td> 65 MB          <td> 65 MB
 * <tr>                                   <td> IAV        <td> BSH               <td> 16 KB          <td> 16 KB
 * <tr>                                   <td> IAV        <td> IAV Reserved      <td> 3160 KB        <td> 5 MB
 * <tr>                                   <td> IAV        <td> BSB               <td> 32 MB          <td> 10 MB
 * <tr>                                   <td> IAV        <td> Overlay           <td> 31 MB          <td> 32 MB
 * <tr>                                   <td> IAV        <td> QP matrix         <td> 13 MB          <td> 13 MB
 * <tr>                                   <td> IAV        <td> Privacy Mask      <td> 21 MB          <td> 48 MB
 * </table>
 *
 * - - - -
 *
 * @section dram_opt_bandwidth 4. Bandwidth
 *
 * As bandwidth is an important data parameter, it is important to note bandwidth limitations.
 * The following sections list the bandwidth limitations for the CV chip line.
 *
 * <ul>
 * <li> @ref sec_dram_cv5
 * <li> @ref sec_dram_cv52
 * <li> @ref sec_dram_band_opt
 * </ul>
 *
 * @subsection sec_dram_cv5 4.1 CV5 Bandwidth Limitation
 *
 * @par List of the Ambarella CV5 Bandwidth Limitations with LPDDR5
 * <table>
 * <caption id="dram_table_cv5_ddr5_bandwidth_limit"></caption>
 * <tr><th> Chip ID         <th> CV5S66         <th> CV5S88
 * <tr><td> DDR frequency   <td> 2640 MHz       <td> 2808 MHz
 * <tr><td> Bitwidth        <td> 64 bits        <td> 64 bits
 * <tr><td> DDR efficiency  <td> 40%            <td> 40%
 * <tr><td> Bandwidth       <td> 16113 MB/s     <td> 17138 MB/s
 * </table>
 *
 * @par List of the Ambarella CV5 Bandwidth Limitations with LPDDR4x
 * <table>
 * <caption id="dram_table_cv5_ddr4_bandwidth_limit"></caption>
 * <tr><th> Chip ID         <th> CV5S66         <th> CV5S88
 * <tr><td> DDR frequency   <td> 1800 MHz       <td> 1800 MHz
 * <tr><td> Bitwidth        <td> 64 bits        <td> 64 bits
 * <tr><td> DDR efficiency  <td> 40%            <td> 40%
 * <tr><td> Bandwidth       <td> 10986 MB/s     <td> 10986 MB/s
 * </table>
 *
 * Refer to the computational formula provided below.
 *
 * <b>Bandwidth</b> = <b>DDR Frequency x Bitwidth</b> / 8 x 2 x <b>DDR Efficiency</b> / 100 / 1.024 / 1.024
 *
 * Using the CV2 Chestnut board as an example, the following shows the total DSP DRAM
 * bandwidth for some of the typical use cases.
 *
 * @subsubsection dram_example_13 Example 13 IMX274_mipi / Mode 5 / 4Kp H.265 + 1080p H.265 + 4Kp MJPEG (CV5_Timn).
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg cv5_vin0_4k_linear.lua
 * board # test_encode -A -H 3840x2160 -b 0 -e -B -H 1920x1080 -b 2 -e -C -m 3840x2160 -b 3 -e
 * board # modprobe ambdram_statis
 * board # echo duration=5000 interval=2500 verbose=1 > /proc/ambarella/dram_statistics
 * board # cat /proc/ambarella/dram_statistics
 * [DRAM Info]
 *   LPDDR5 with 64-bits @ 2808MHz, Burst Size: 64, theory BW: 42846 MB/s
 * [Average BW]
 *   Module                Bandwidth(In MB/s)              Percent
 *   -----------
 *   Cortex                         7.572                   0.017
 *   DSP                         4547.825                  10.614
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                         4555.374                  10.631
 * @endcode
 *
 * @subsection sec_dram_cv52 4.2 CV52 Bandwidth Limitation
 *
 * @par  List of the Ambarella CV52 Bandwidth Limitations with LPDDR5.
 * <table>
 * <caption id="dram_table_cv5_ddr5_bandwidth_limit"></caption>
 * <tr><th> Chip ID         <th> CV52S66        <th> CV52S33
 * <tr><td> DDR frequency   <td> 2640 MHz       <td> 2640 MHz
 * <tr><td> Bitwidth        <td> 32 bits        <td> 32 bits
 * <tr><td> DDR efficiency  <td> 40%            <td> 40%
 * <tr><td> Bandwidth       <td> 8056 MB/s     <td> 8056 MB/s
 * </table>
 *
 * @par List of the Ambarella CV52 Bandwidth Limitations with LPDDR4x
 * <table>
 * <caption id="dram_table_cv5_ddr4_bandwidth_limit"></caption>
 * <tr><th> Chip ID         <th> CV52S66        <th> CV52S33
 * <tr><td> DDR frequency   <td> 1800 MHz       <td> 1800 MHz
 * <tr><td> Bitwidth        <td> 32 bits        <td> 32 bits
 * <tr><td> DDR efficiency  <td> 40%            <td> 40%
 * <tr><td> Bandwidth       <td> 5492 MB/s      <td> 5492 MB/s
 * </table>
 *
 * Refer to the computational formula provided below.
 *
 * <b>Bandwidth</b> = <b>DDR Frequency x Bitwidth</b> / 8 x 2 x <b>DDR Efficiency</b> / 100 / 1.024 / 1.024
 *
 * Using the CV52 Zr board as an example, the following shows the total DSP DRAM bandwidth for typical use cases.
 *
 * @subsubsection dram_example_14 Example 14 IMX274_mipi / Mode 5 / 4Kp H.265 + 1080p H.265 + 4Kp MJPEG (CV52_zr).
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a&
 * board # test_encode --resource-cfg cv5_vin0_4k_linear.lua
 * board # test_encode -A -H 3840x2160 -b 0 -e -B -H 1920x1080 -b 2 -e -C -m 3840x2160 -b 3 -e
 * board # modprobe ambdram_statis
 * board # echo duration=5000 interval=2500 verbose=1 > /proc/ambarella/dram_statistics
 * board # cat /proc/ambarella/dram_statistics
 * [DRAM Info]
 *   LPDDR5 with 64-bits @ 2640MHz, Burst Size: 64, theory BW: 20141  MB/s
 * [Average BW]
 *   Module                Bandwidth(In MB/s)              Percent
 *   -----------
 *   Cortex                        12.982                   0.064
 *   DSP                         4475.721                  22.221
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                         4488.680                  22.285
 * @endcode
 *
 * @subsection sec_dram_band_opt 4.3 Bandwidth Optimization
 *
 * The following guidelines provide users with details to optimize the DRAM bandwidth:
 *   - <b>Canvas</b>: Larger canvas size costs more DRAM bandwidth. Users should choose the
 *     suitable canvas size and disable unused canvases to save the DRAM bandwidth.
 *   - <b>Pyramid</b>: The pyramid buffer usually is used by the CV algorithm. It supports up
 *     to 6x layers with various resolutions, and each layer can be independently enabled or
 *     disabled. Users can disable the unnecessary layers to save the DRAM bandwidth. In
 *     addition, using the pyramid manual-feed mode is recommended whenever the user application
 *     can control the feeding frame rate of the pyramid. If the processing frame rate of CV
 *     algorithm is lower than the VIN frame rate, the user application can lower this rate
 *     to reduce the DRAM bandwidth.
 *   - <b>MCTF compression</b>: This option can be enabled through setting "mctf_cmpr" to 1 in the
 *     "chan_x" section of the Lua script.  It is enabled by default to reduce the DRAM bandwidth.
 *   - <b>Raw compression</b>: This option can be enabled through setting the "raw-capture" to 0
 *     in the "chan_x" section of the Lua script.  By default, raw compression is enabled to
 *     reduce the DRAM bandwidth.  Users can disable it to dump the sensor raw data for debugging purposes.
 *   - <b>Raw pack mode</b>: This option can be enabled through setting "packing_mode_enable" to
 *     1 in the "chan_x" section of the Lua script.  Users can enable this option to generate the
 *     packed raw image, which uses a lower DRAM bandwidth than the uncompressed raw image. Note
 *     that the raw pack mode and raw compression cannot be enabled simultaneously.
 *
 * - - - -
 *
 * @section dram_opt_license 5. License
 *
 * Copyright (C) @ambalicyear Ambarella International LP
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and/or foreign
 * copyrights. This Software is also the confidential and proprietary
 * information of Ambarella International LP and its licensors. You may not use, reproduce,
 * disclose, distribute, modify, or otherwise prepare derivative works of this
 * Software or any portion thereof except pursuant to a signed license agreement
 * or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
 * In the absence of such an agreement, you agree to promptly notify and return
 * this Software to Ambarella International LP。
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
 * @file doc_sys_power_management.h
 * @brief
 * @version 1.0
 * @date 2022-8-8
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
 * @page page_sys_pm OPTIMIZATION - Power Management
 *
 * @section sys_pm_history 0. Revision History
 *
 * <table>
 * <caption id="sys_opt_power_rev_history"></caption>
 * <tr><th> Updated Date          <th align="left"> Modification
 * <tr><td> 20220809              <td> Initial Version
 * <tr><td> 20220812              <td> Updated @ref page_sys_pm for detailed information
 * <tr><td> 20220921              <td> Added Section @ref sys_pm_adc
 * <tr><td> 20230209              <td> Added Section @ref sys_pm_ccidsp
 * <tr><td rowspan="4"> 20230831  <td> 1. Added Section @ref sys_pm_pcie
 * <tr>                           <td> 2. Added Section @ref sys_pm_hevc
 * <tr>                           <td> 3. Added Section @ref sys_pm_vout_video
 * <tr>                           <td> 4. Updated Section @ref sys_pm_vout
 * </table>
 *
 * - - - -
 *
 * @section sys_pm_overview 1. Overview
 *
 * This document provides guidelines for power management with the Ambarella CV5x Flexible
 * Linux Software Development Kit (SDK).
 *
 * - - - -
 *
 * @section sys_pm_power_optimization 2. Power Optimization
 *
 * @subsection sys_pm_po_core_numbers 2.1 Core Numbers
 * @subsubsection sys_pm_po_core_linux 2.1.1 Linux Boot Arguments Modification
 * If the system load is minimal, the number of CPU cores can be set to two or less.
 * This modification alters the Linux boot arguments (bootargs); a reboot is required to take effect.
 *
 * -# If Arm® trusted firmware (ATF) is enabled, then CONFIG_RELOAD_UNTRUSTED_DTB is also required
 * in order for AMBoot modifications to take effect.
 * @code {.c}
 * build$ make menuconfig
 *         Main menu
 *          -> boot
 *            -> amboot (boot/ambamk) (CONFIG_AMBOOT [=y])
 *              -> Ambarella Firmware Configuration
 *                -> AMBoot Options
 *                  -> Boot with TrustZone (CONFIG_AARCH64_TRUSTZONE [=y])
 *                    -> Secure DTB with Signature (SOC Firmware Config) (CONFIG_TRUSTZONE_DTB_SIGNED [=y])
 *                      -> Reload DTB in PTB partiton
 * @endcode
 *
 * -# Enter into AMBoot and modify the bootargs.
 * @code {.c}
 * amboot>  fdt cmdline
 *
 * /chosen
 * linux,stdout-path = /apb@20e4000000/uart@e4000000
 * bootargs = console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc
 * pci=nomsi,pcie_bus_perf pcie_pme=nomsi
 * ambarella,hibernate-lzo-enable
 * amboot>  fdt cmdline console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs
 * init=/linuxrc pci=nomsi,pcie_bus_perf pcie_pme=nomsi maxcpus=1 //change to 1 CPU Cores
 * amboot> booti //boot to linux
 * @endcode
 * -# Boot into Linux and check the log below:
 * @code {.c}
 * [    0.336985] rcu: Hierarchical SRCU implementation.
 * [    0.342039] smp: Bringing up secondary CPUs ...
 * [    0.346583] smp: Brought up 1 node, 1 CPU
 * [    0.270393] SMP: Total of 1 processors activated. //total 1 CPU cores are up.
 * @endcode
 *
 * @note
 *   - CV5x chips do not support CPU core hotplug.
 *   - The CV72 chip does not support CPU core hotplug.
 *
 * @subsection sys_pm_ccidsp 2.2 CPU, Core, and IDSP Clock Runtime Update
 * This feature enables users to update the CPU, core, and image digital signal processor (IDSP)
 * clocks on the fly. This benefits users as it enables them to select the appropriate CPU, core,
 * and IDSP clocks to conserve system power.
 *
 * @note
 *   - In order to change the CPU and core clocks, ATF must be involved. For
 *     more details about ATF, refer to Section @ref sys_pm_atf.
 *   - If users request runtime updates of the CPU and core clocks, Amabrella recommends
 *     reserving the ATF partition at the NAND partition layout design.
 *   - When changing the core and IDSP clocks for the digital signal processor (DSP), the DSP must
 *     first be placed in the idle state.
 *
 * @subsubsection sys_pm_ccidsp_bF 2.2.1 Build the Firmware
 * Suppose that users want to switch over among the following CPU, core, and IDSP clock combinations.
 * <table>
 * <caption>Table 2-1. CPU, Core, and IDSP Clock Combinations.</caption>
 * <tr><th>CPU (MHz)<th>Core (MHz)<th> IDSP (MHz)
 * <tr><td>1608<td>1140<td>960
 * <tr><td>1392<td>960<td>720
 * <tr><td>600<td>336<td>360
 * </table>
 * Follow the steps below to build the firmware.
 *
 * -# Change the CV5x device trees (DTS) to add the desired CPU and core clock combinations.
 *    The following provides an example using the CV5 system on chip (SoC):<br/>
 *    @code {.c}
 * build $ vi ambarella/kernel/linux-5.15/arch/arm64/boot/dts/ambarella/ambarella-cv5.dtsi
 *
 *
 *		 * MASK
 *		 * + --- + ----- + ----- +
 *		 * | bit |   1   |   0   |
 *		 * + --- + ----- + ----- +
 *		 * | clk |  CORE | CORTEX|
 *		 * + --- + ----- + ----- +
 *
 *		cpufreq-mask = <1>;
 *		amb,timer-freq-adjust-off;
 *		clocks = <&gclk_cortex &gclk_core>;
 *		clock-names = "cortex_clk", "core_clk";
 *		clocks-frequency-cortex-core =
 *			<1608000  1140000>,
 *			<1392000  960000>,
 *			<600000   336000>;
 *         };
 *    @endcode
 * -# Select the following kernel configuration to enable CPU frequency scaling.
 *    @code {.c}
 * build $ make sync_build_mkcfg
 * build $ make cv5_ipcam_atf_config
 * build $ make defconfig_public_linux
 * build $ make menuconfig_public_linux
 *   CPU Power Manager --->
 *    CPU Frequency scaling --->
 *     Default CPUFreq governor (userspace) --->
 *     ( ) performance
 *     (X) userspace
 *     ( ) ondemand
 *     ( ) conservative
 *    @endcode
 *    Usage guidelines of the four options above are as follows:
 *       - @b Performance: the guaranteed performance
 *       - @b Userspace: users can update on the fly
 *       - @b Ondemand: users can update on the fly, according to the present requirements
 *       - @b Conservative: users can update on the fly in a conservative manner
 *
 * @subsubsection sys_pm_change_clock 2.2.2 Change CPU, Core, and IDSP Clock
 *
 * Note that Ambarella recommends updating the clock in the Telnet client console rather than
 * in the serial port.<br/>
 * -# Open Telnet and perform the following operations.
 * -# Update frequency on the fly through the following commands:
 *
 * @code {.c}
 * // Disabling kernel prints is required for extremely low frequency
 * board # echo 1 1 1 1 > /proc/sys/kernel/printk
 * board # cd /sys/devices/system/cpu/cpu1/cpufreq
 * board # cat scaling_available_frequencies	// Check the available clock options
 * 1608000 1392000 600000
 * board # echo 1392000 > scaling_setspeed		// Change CPU and Core clocks
 * board # echo gclk_idsp 720000000 > /proc/ambarella/clock		// Change IDSP clock
 * board # cat /proc/ambarella/clock		// check whether clocks are set properly
 * Clock Information:
 *
 *         gclk_cortex:    1392000000 Hz
 *         gclk_core:      1140000000 Hz
 *         gclk_idsp:      720000000  Hz
 *
 * @endcode
 *
 * Several options that can be set are in the folder `/sys/devices/system/cpu/cpu0/cpufreq`, and are listed as follows:<br/>
 *   - @b scaling_available_frequencies: the supported frequencies to be updated
 *   - @b scaling_governor: the current governor (performance / userspace / ondemand / conservative)
 *   - @b scaling_cur_freq: the current frequency, in kHz; 24000 is 24 MHz
 *   - @b scaling_setspeed: the frequency to be updated
 *
 * @note
 *      - CPU, IDSP, and core clocks are independent from one another. Users can attempt any
 *        combination. For CPU clocks and core clocks, only frequencies listed in the DTSi
 *        are permitted to be set. Ensure that those values are multiples of 24 MHz.
 *      - The maximum CPU, IDSP, and core clocks CANNOT be greater than the specification of the
 *        corresponding CV5x system on chip (SoC).
 *      - If the clock is updated to a low value, such as 24000, the serial port may not function.
 *        However, the Telnet port may still function.
 *      - The CPU clock must be greater than 96 MHz due to the physical design limitation.
 *      - The core clock must be greater than 24 MHz. If a high-definition multimedia interface
 *        (HDMI®) is enabled with a resolution greater than 480p, a minimum value of 96 MHz for the
 *        core clock is suggested.
 *
 * @subsubsection sys_pm_measure_clock 2.2.3 Measure Clock Runtime-Switch Time
 *
 * The clock runtime-switch time includes the clock switching time and the re-running DSP
 * time. The spent time varies according to different DSP use cases. Users
 * can measure the clock runtime-switch time using the following method.<br/>
 * Place the clock switching and unit test commands (to re-run the DSP) into a single script.
 * Then, use the tool "time" to measure the time spent executing this script. The "time" tool
 * outputs the spent time with the results displayed as three parts:
 *
 * @b Real: total spent time <br/>
 * @b User: user space spent time <br/>
 * @b Sys: kernel space spent time <br/>
 *
 * For example, the script `clock_switch.sh` includes changing the IDSP
 * clock commands and re-entering preview commands, as shown below:
 * @code {.c}
 * #!/bin/sh
 * # put dsp to idle state before changing idsp clock
 * test_encode --idle --nopreview
 * # change idsp clock
 * echo gclk_idsp 720000000 > /proc/ambarella/clock
 * sleep 1
 * # re-enter preview state
 * test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua
 *
 * @endcode
 * The user can measure the time on the board, as shown below.
 * @code {.c}
 * board # time ./clock_switch.sh
 * ...
 * enable preview done
 * real    0m 1.83s
 * user    0m 0.06s
 * sys     0m 0.26s
 *
 * @endcode
 *
 * @subsection sys_pm_vector_processor 2.3 Vector Processor Clock Runtime Update
 * The vector processor (VP) clock frequency can only be switched to a different frequency when the VP is not in use.
 * Use `cavalry_load` to change the VP clock.
 * @code {.c}
 * board # cat /proc/ambarella/clock        //check all the system clock
 * Clock Information:
 * ...
 *         gclk_vision:    1104000000Hz
 * board # cavalry_load --vp-clk 1/2        //set vp clock to 542 MHz
 * Configure VP Clock Percentage: 552/1104
 * board # cat /proc/ambarella/clock        //check the clock again
 * Clock Information:
 * ...
 *         gclk_vision:    552000000 Hz
 * board #
 * @endcode
 * @note
 *   - Because the VP clock setting in the .ini file is the runtime upper limit, the runtime VP
 *     clock change cannot exceed the value in the .ini file.
 *   - The VP clock must be an exact multiple of 24 MHz and cannot be set to 0. Users must
 *     calculate the fraction when updating the VP clock. Additionally, users must always check
 *     the clock frequency after setting it.
 *
 * @subsection sys_pm_vin 2.4 Video Input
 * Contact the Ambarella SDK support team for connecting the video input (VIN) pins to the ground (GND).
 *
 * @subsection sys_pm_mipi_interface 2.5 Mobile Industry Processor Interface
 * If no mobile industry processor interface (MIPI®) sensor is used, the MIPI CSI-2 power can be lowered via the following commands:
 * @code {.c}
 * board # devmem 0x20ED2000E8 32 0x0d2b5c03
 * board # devmem 0x20ed200124 32 0x0d2b5c03
 * board # devmem 0x20ed200160 32 0x0d2b5c03
 * board # devmem 0x20ed20019c 32 0x0d2b5c03
 * board # devmem 0x20ed2001d8 32 0x0d2b5c03
 * board # devmem 0x20ed200214 32 0x0d2b5c03
 * board # devmem 0x20ed200250 32 0x0d2b5c03
 * board # devmem 0x20ed20028c 32 0x0d2b5c03
 * board # devmem 0x20ed2002c8 32 0x0d2b5c03
 * board # devmem 0x20ed200304 32 0x0d2b5c03
 * board # devmem 0x20ed200340 32 0x0d2b5c03
 * board # devmem 0x20ed20037c 32 0x0d2b5c03
 * board # devmem 0x20ed2000ec 32 0x024179a8
 * board # devmem 0x20ed200128 32 0x024179a8
 * board # devmem 0x20ed200164 32 0x024179a8
 * board # devmem 0x20ed2001a0 32 0x024179a8
 * board # devmem 0x20ed2001dc 32 0x024179a8
 * board # devmem 0x20ed200218 32 0x024179a8
 * board # devmem 0x20ed200254 32 0x024179a8
 * board # devmem 0x20ed200290 32 0x024179a8
 * board # devmem 0x20ed2002cc 32 0x024179a8
 * board # devmem 0x20ed200308 32 0x024179a8
 * board # devmem 0x20ed200344 32 0x024179a8
 * board # devmem 0x20ed200380 32 0x024179a8
 *
 * @endcode
 *
 * @subsection sys_pm_gpio 2.6 General Purpose Input / Output
 * To conserve power, all floating inputs / outputs (I/Os) can be set to the general purpose input / output (GPIO)
 * and enabled with an internal pull-low. Refer to the <em>Peripherals</em> Doxygen webpages
 * for additional details regarding GPIO configuration. Then, use the following commands:
 * @code {.c}
 * board # devmem 0x20e002f068 32 0xffffffff
 * board # devmem 0x20e002f06c 32 0xffffffff
 * board # devmem 0x20e002f070 32 0xffffffff
 * board # devmem 0x20e002f074 32 0xffffffff
 * board # devmem 0x20e002f078 32 0xffffffff
 * board # devmem 0x20ed080314 32 0x0
 * board # devmem 0x20ed080318 32 0x0
 * board # devmem 0x20ed08031c 32 0x0
 * board # devmem 0x20ed080320 32 0x0
 * board # devmem 0x20ed080324 32 0x0
 * board # devmem 0x20ed080328 32 0x0
 * board # devmem 0x20ed08032c 32 0x0
 * board # devmem 0x20ed080330 32 0x0
 * board # devmem 0x20ed08043c 32 0x0
 * board # devmem 0x20ed080440 32 0x0
 * board # devmem 0x20ed080444 32 0x0
 * @endcode
 * Or, use `poweroff_pdev.sh` in the path `ambaralla/app/utility/amba_scripts`:
 * @code {.c}
 * board # poweroff_pdev.sh --gpio
 * @endcode
 *
 * @subsection sys_pm_vout 2.7 Video Output
 * If video output (VOUT) is not required, contact the Ambarella SDK support team to disable it. VOUT B
 * can be disabled using the following command:
 * @code {.c}
 * board # devmem 0x20e0008a04 32 0x00    // disable vout a clock
 * board # devmem 0x20e0008a08 32 0x00    // disable vout b clock
 * board # devmem 0x20e0008a1c 32 0x00    // disable vout c clock
 * @endcode
 * Alternatively, use `poweroff_pdev.sh`:
 * @code {.c}
 * board # poweroff_pdev.sh --vout
 * @endcode
 *
 * @subsubsection sys_pm_vout_cvbs 2.7.1 Composite Video Broadcast Signal
 * If CVBS is not required, disable it using the following commands:
 * @code {.c}
 * board # devmem 0x20ed080688 32 0x40000000   //  Disable CVBS
 * @endcode
 * Alternatively, use `poweroff_pdev.sh`:
 * @code {.c}
 * board # poweroff_pdev.sh --cvbs
 * @endcode
 *
 * @subsubsection sys_pm_vout_hdmi 2.7.2 HDMI
 * If HDMI is not required, disable it using the following commands:
 * @code {.c}
 * board # devmem 0x20ed080008 32 0x0c   //  Power down HDMI
 * board # devmem 0x20ed0801a8 32 0x14073021   //  Power down the HDMI PLL
 * board # devmem 0x20ed0801a8 32 0x14073020
 * @endcode
 * Alternatively, use poweroff_pdev.sh:
 * @code {.c}
 * board # poweroff_pdev.sh --hdmi
 * @endcode
 *
 * @subsubsection sys_pm_vout_mipidsi 2.7.3 MIPI DSI
 * If MIPI DSI® is not required, disable it using the following commands:
 * @code {.c}
 * board # devmem 0x20ed200028 32 0x000300ff   //  Power down the mipi dsi
 * board # devmem 0x20ed200020 32 0x00000006
 * @endcode
 *
 * @subsubsection sys_pm_vout_video 2.7.4 Video (LCD)
 * If LCD is not required, disable it using the following command:
 * @code {.c}
 * board # devmem 0x20ed0800c0 32 0x01078021
 * board # devmem 0x20ed0800c0 32 0x01078020
 * @endcode
 *
 * @subsection sys_pm_cv 2.8 Computer Vision
 * If computer vision (CV) is not required, disable it to save power. Contact the Ambarella SDK support
 * team for further assistance.
 * @code {.c}
 * board # devmem 0x20ed0806e4 32 0x2f130020   //  Disable clock for CV
 * @endcode
 * Alternatively, use poweroff_pdev.sh:
 * @code {.c}
 * board # poweroff_pdev.sh --cv
 * @endcode
 *
 * @subsection sys_pm_sdio 2.9 Secure Digital Input / Output
 * If secure digital input / output (SDIO) is not required, disable it using the following commands:
 * @code {.c}
 * board # devmem 0x20ed0804ac 32 0x16012021   //  Power down sdio clk
 * board # devmem 0x20ed0804ac 32 0x16012020
 * @endcode
 * Alternatively, use poweroff_pdev.sh:
 * @code {.c}
 * board # poweroff_pdev.sh --sd
 * @endcode
 *
 * @subsection sys_pm_audio 2.10 Audio
 * If audio is not required, disable it using the following commands:
 * @code {.c}
 * board # devmem 0x20e0024110	32 0x01   //  Power down audio clk
 * @endcode
 * Alternatively, use poweroff_pdev.sh:
 * @code {.c}
 * board # poweroff_pdev.sh --audio
 * @endcode
 *
 * @subsection sys_pm_adc 2.11 Analog-to-Digital Converter
 * If the analog-to-digital converter (ADC) is not required, disable it using the following command:
 * @code {.c}
 * board # devmem 0x20ed080198 32 0x00000002   //  Power down adc
 * @endcode
 * Or use poweroff_pdev.sh:
 * @code {.c}
 * board # poweroff_pdev.sh --adc
 * @endcode
 *
 * @subsection sys_pm_pcie 2.12 Peripheral Component Interconnect Express
 * If peripheral component interconnect express (PCIe) is not required, set the disable flag into the related DTS node:
 * @code {.c}
 * &pciec_rc {
 *     status = "disabled";
 * };
 * @endcode
 *
 * @subsection sys_pm_hevc 2.13 High Efficiency Video Coding (HEVC)
 * If the system only encodes in H.264 format, then the H.265 state registers can be disabled using
 * the following command.
 * @code {.c}
 * board # devmem 0x20ed08008c 32 0xffff7f7f   //  Disable DSP HEVC STATE REG
 * @endcode
 * Or, use poweroff_pdev.sh:
 * @code {.c}
 * board # poweroff_pdev.sh --hevc
 * @endcode
 *
 * - - - -
 *
 * @section sys_pm_atf 3. Arm Trusted Firmware
 * Use the following steps to verify if ATF is properly configured.
 *
 * -# Check the options from "menuconfig":
 * @par For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 *   [*] boot (boot) --->
 *     Bootloader --->
 *       Ambarella Firmware Configuration --->
 *         Memory Options --->
 * 	         (0x01000000) AMBoot bootloader starting address
 * 	         (0x04000000) Firmware programmer starting address
 *         AMBoot Options --->
 *           [*] Boot with TrustZone --->
 *   -*- board (boards) --->
 *     Memory --->
 *       (0x01280000) Kernel start address
 * @endcode
 * @par For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 *   meta-ambabsp --->
 *     recipes-bsp --->
 *       [*] boot (meta-ambabsp/recipes-bsp/boot) --->
 *         Ambarella Firmware Configuration --->
 *           Memory Options --->
 * 	           (0x01000000) AMBoot bootloader starting address
 * 	           (0x04000000) Firmware programmer starting address
 *           AMBoot Options --->
 *             [*] Boot with TrustZone --->
 *       -*- board (meta-ambabsp/recipes-bsp/board) --->
 *         Memory --->
 *           (0x01280000) Kernel start address
 * @endcode
 * -# Check if the ATF partition size is configured properly in `bsp.h`.
 * @code {.c}
 * #define AMBOOT_BLD_SIZE 	(AMBOOT_MIN_PART_SIZE * 8)
 * #define AMBOOT_PTB_SIZE 	(AMBOOT_MIN_PART_SIZE * 7)
 * #define AMBOOT_ATF_SIZE 	(AMBOOT_MIN_PART_SIZE * 8)
 * @endcode
 *
 * - - - -
 *
 * @section sys_pm_license 4. License
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
 * @file doc_sys_tool_cooperhome.h
 * @brief This file introduces the instructions on how to build/install
 * the Cooperhome and how to get started with Cooperhome.
 * @version 0.1.0
 * @date 2023-08-24
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

/*! @page page_sys_cooperhome TOOL - CooperHome
 *
 * @section cooperhome_history 0. Revision History
 * <table>
 * <caption id="cooperhome_rev_history"></caption>
 * <tr><th> Version                   <th> Updated Date             <th> Modification
 * <tr><td> 0.1.0 - Alpha             <td> 20230824                 <td> Initial Version
 * <tr><td rowspan="2"> 0.1.0 - Beta  <td rowspan="2"> 20230928     <td> 1. Added Section @ref cooperhome_iq_page.
 * <tr>                                                             <td> 2. Added Section @ref cooperhome_about_page.
 * <tr><td> 0.1.0                     <td> 20231023                 <td> Added Section @ref cooperhome_gdc_page.
 * <tr><td rowspan="2"> 0.2.0 - Alpha <td rowspan="2"> 20231220     <td> 1. Added Section @ref cooperhome_startup_page.
 * <tr>                                                             <td> 2. Added Section @ref cooperhome_vcap_page.
 * <tr><td> 0.2.1 - Alpha             <td> 20240112                 <td> Updated Section @ref cooperhome_performance_cvflowprofile.
 * <tr><td rowspan="2"> 0.2.2         <td rowspan="2"> 20240124     <td> 1. Added Section @ref cooperhome_lychee_installation.
 * <tr>                                                             <td> 2. Added Section @ref cooperhome_run_lychee.
 * </table>
 *
 * - - - -
 *
 * @section cooperhome_ov 1. Overview
 *
 * CooperHome is a light-weight web application designed for the Ambarella Cooper software development
 * kit (SDK) that runs on Ambarella's CV2x, CV5x, CV7x, and CV3x systems on chip (SoCs) to bring
 * webpage access to the SoCs. Thus, users can visually and graphically check
 * and configure Ambarella SoCs on any client device (such as PCs, cellphones, tablets,
 * and more) through the web browser.
 *
 * With the CooperHome features, users are able to see a summary of system
 * information, monitor device status, profile use case performance, configure
 * tasks on CPU / digital signal processor (DSP) / CVflow® cores, capture output data, and more.
 *
 * CooperHome is targeted to help new users to get started with the Ambarella SoC
 * and become familiar with the Ambarella system.
 *
 * CooperHome also aims to help experienced users accelerate their evaluation
 * and development speeds with the Ambarella Cooper SDK.
 * - CooperHome application source code is located  `/COOPER_SDK_PATH/ambarella/app/utility/cooper_home/`.
 * - CooperHome external plugins are placed under `/COOPER_SDK_PATH/ambarella/prebuild/oss/noarch/cooper-home/`.
 *
 * @note
 * - CooperHome is published and released as full source code in the Cooper SDK and is
 *   developed under the Ambarella Three-clause Proprietary License.
 * - CooperHome only can be used as sample code for user reference. Customers
 *   <b>CANNOT</b> directly copy and use this piece of source code for their final products.
 *
 * @image html cooperhome_main.png "Figure 1-1. CooperHome Main Page."
 *
 * - - - -
 *
 * @section cooperhome_build 2. Build Method and Installation
 *
 * As CooperHome needs Python module which is not supported by Amba-build
 * firmware, there are two ways for users to build or install CooperHome
 * application into the final image.
 * - Use Yocto build to generate CooperHome into the firmware.
 * - Use the prepared installation package and install it into the firmware.
 *
 * @subsection cooperhome_yocto_build 2.1 Build CooperHome with Yocto-build Firmware
 * Follow the below instructions to enable CooperHome in the Yocto-build firmware.
 * @code
 * build $ source build/env/yocto-build.env
 * build $ make ipcam_config
 * build $ make menuconfig
 *             -> meta-ambaapp
 *                 -> recipes-tool --->
 *                     [*] cooper-home (meta-ambaapp/recipes-tool/cooper-home)
 * build $ make
 * @endcode
 *
 * @subsection cooperhome_build_installation_pack 2.2 Build CooperHome Installation Package
 * Follow the below instructions to create the CooperHome installation package.
 * The installation package is generated under the output folder
 * "cooper-home-install-pack package".
 * For example, `./out/yocto_out/cv22_walnut/tmp/work/cortexa53-crypto-poky-linux/cooper-home-install-pack/1.0-r0/build/cooper_home_installer.tar`.
 *
 * @code
 * build $ source build/env/yocto-build.env
 * build $ make ipcam_config
 * build $ make cooper-home-install-pack
 * @endcode
 *
 * @subsection cooperhome_installation 2.3 Install CooperHome on Existing Amba-Build or Yocto-Build Firmware
 *
 * Follow the below instructions to install the CooperHome application on any
 * existing Amba-build / Yocto-build firmware.
 *
 * If user installs the CooperHome into system default path, ensure that root
 * storage has more than <b>25 MB</b> free space before installation.
 * Use `df` to check the size of free space.
 *
 * It is recommended to install CooperHome on SD card or network driver because
 * the application will not be erased by device reboot and / or frimware
 * re-program. Also, it does not rely on the storage size of rootfs.
 *
 * It extracts and installs the CooperHome executable files and runtime
 * environment to the target device.
 * @code
 * ## Copy the cooper_home_installer.tar file into "/tmp" path or SD card
 * board # tar xfp cooper_home_installer.tar
 * board # cd cooper_home_installer
 * @endcode
 *
 * -# Install CooperHome to root (`/usr/bin, /usr/lib and /usr/share/ambarella`):
 * @code
 * board # ./cooper_home_install.sh -n
 * @endcode
 *
 * -# Install CooperHome to external storage (for example, SD card or network drive):
 * @code
 * board # ./cooper_home_install.sh -p /sdcard/mmcblk0p1/cooperhome
 * @endcode
 *
 * -# Install CooperHome to `tmp` folder:
 * @code
 * board # ./cooper_home_install.sh -p /tmp/cooperhome
 * @endcode
 *
 * @subsection cooperhome_lychee_installation 2.4 Install CooperHome on Lychee
 * Follow the below instructions to install the CooperHome application on Lychee.
 *
 * @code
 * lychee $ sudo dnf install cooper-home.noarch
 * @endcode
 *
 * Follow the below instructions to update the CooperHome application to the latest version.
 *
 * @code
 * lychee $ sudo dnf update cooper-home.noarch
 * @endcode
 *
 * - - - -
 *
 * @section cooperhome_run 3. Run CooperHome
 *
 * @subsection cooperhome_run_amba_yocto 3.1 Run CooperHome on Amba-build or Yocto-build Firmware
 * Follow the below instructions to run CooperHome server on the board, and view
 * CooperHome pages on web browser.
 *
 * 1. Run the CooperHome application on the board.
 * @code
 * board # cooper_home_launch.sh
 * @endcode
 *
 * 2. Open the CooperHome webpage in a PC browser with the EVK board IP
 *    address (such as 10.0.0.2) and port-5000 `http://10.0.0.2:5000/`
 *
 * @subsection cooperhome_run_lychee 3.2 Run CooperHome on Lychee
 * Follow the below instructions to run CooperHome application on Lychee.
 *
 * 1. Open the Start Menu.
 * 2. Search for Cooper Home application.
 * 3. Click Cooper Home and Run.
 *
 * @image html cooperhome_run_lychee.png "Figure 3-1. Run CooperHome on Lychee."
 *
 * - - - -
 *
 * @section cooperhome_pages 4. CooperHome Webpages
 *
 * @image html cooperhome_logo.png "Figure 4-1. CooperHome Main Logo." width=178 height=200
 *
 * @subsection cooperhome_dashboard_page 4.1 Dashboard
 * The CooperHome dashboard page provides users with overview information and the status of both
 * the Ambarella SoC and the EVK.
 *
 * @image html cooperhome_main.png "Figure 4-2. CooperHome Dashboard Page."
 *
 * @subsubsection cooperhome_dashboard_devinfo 4.1.1 Device Information
 * The device information section provides an overview of the Ambarella device.
 * It consists of five tabs: device, processor, memory, firmware, and clocks.
 *
 * @image html cooperhome_main_dev.png "Figure 4-3. CooperHome Dashboard Page - Device Info (Device)." width=1000
 *
 * @image html cooperhome_main_processor.png "Figure 4-4. CooperHome Dashboard Page - Device Info (Processor)." width=1000
 *
 * @image html cooperhome_main_memory.png "Figure 4-5. CooperHome Dashboard Page - Device Info (Memory)." width=1000
 *
 * @image html cooperhome_main_firmware.png "Figure 4-6. CooperHome Dashboard Page - Device Info (Firmware)." width=1000
 *
 * @image html cooperhome_main_clock.png "Figure 4-7. CooperHome Dashboard Page - Device Info (Clocks)." width=1000
 *
 * @subsubsection cooperhome_dashboard_cpustat 4.1.2 CPU Loading
 * The CPU loading section shows the CPU loading percentage value for the past second;
 * this value refreshes each second.
 *
 * @image html cooperhome_main_cpu.png "Figure 4-8. CooperHome Dashboard Page - CPU Loading."
 *
 * @subsubsection cooperhome_dashboard_cvflowstat 4.1.3 CVflow Loading
 * The CVflow loading section shows the CVflow loading percentage value for the past second;
 * this value refreshes each second.
 *
 * @image html cooperhome_main_cvflow.png "Figure 4-9. CooperHome Dashboard Page - CVflow Loading."
 *
 * @subsubsection cooperhome_dashboard_vininfo 4.1.4 Video Input Information
 * The video input (VIN) information section shows a list of initialized sensor modules on
 * the Ambarella device.
 *
 * @image html cooperhome_main_vin.png "Figure 4-10. CooperHome Dashboard Page - VIN Info."
 *
 * @subsubsection cooperhome_dashboard_streaminfo 4.1.5 Stream Information
 * The stream information section shows a list of enabled streams on the
 * Ambarella device.
 *
 * @image html cooperhome_main_vin.png "Figure 4-11. CooperHome Dashboard Page - Stream Info."
 *
 * @subsection cooperhome_startup_page 4.2 Startup
 * The CooperHome startup page provides users with one-click operations to start tasks on CPU, DSP,
 * and CVflow.
 *
 * @image html cooperhome_startup.png "Figure 4-12. CooperHome Startup Page."
 *
 * @subsubsection cooperhome_startup_cpu 4.2.1 CPU
 * The CPU section allows users to enable dummy loading on CPU cores (`load50`), start DRAM memory
 * test (`memtester-arm`) and start memory copy speed test (`test_memcpy`). These operations add
 * load to CPU cores and/or DRAM read / write.
 *
 * @image html cooperhome_startup_cpu.png "Figure 4-13. CooperHome Startup Page - CPU."
 *
 * @subsection cooperhome_performance_page 4.3 Performance
 * The CooperHome performance page provides users with performance profile features on the
 * Ambarella SoC with the following six aspects.
 *
 * @image html cooperhome_performance.png "Figure 4-14. CooperHome Peformance Page."
 *
 * @subsubsection cooperhome_performance_drambw 4.3.1 DRAM Bandwidth
 * The dynamic random-access memory (DRAM) bandwidth section includes a DRAM bandwidth diagram of the Ambarella device
 * over the past hundreds of milliseconds. The samples are captured on the edge of
 * each millisecond. After clicking the "Run" button, the application
 * starts to capture the latest data and the diagram is refreshed. <br>
 * Other functions in this section are as follows:
 * - "Run" button: start profiling the DRAM bandwidth diagram<br>
 * - "Save data" button: save DRAM bandwidth raw data<br>
 * - "Save image" button: save the PNG image of the current DRAM bandwidth graph<br>
 * - "Graph type" dropdown menu: select the graph type (line graph or
 * stacked area graph)<br>
 * - "Samples" dropdown menu: select the duration of the sample capture time
 *
 * @image html cooperhome_performance_drambw.png "Figure 4-15. CooperHome Peformance Page - DRAM Bandwidth." width=1000
 *
 * @subsubsection cooperhome_performance_itrp 4.3.2 Interrupts
 * The interrupts section shows the increment values of interrupts in the Ambarella
 * system during the selected period. The average, minimum, and maximum columns are accumulated values, starting
 * from when the "Run" button is clicked, and they are reset when the "Stop" button is clicked.<br>
 * - "Run" button: start profiling system interrupts<br>
 * - "Interval" dropdown menu: select the time of the increment values' duration
 *
 * @image html cooperhome_performance_interrupt.png "Figure 4-16. CooperHome Peformance Page - System Interrupts." width=1000
 *
 * @subsubsection cooperhome_performance_latency 4.3.3 Video Pipeline Analysis
 * The video pipeline analysis section profiles the canvas, stream, and video output (VOUT) latencies
 * for the running video pipeline. This section also shows the frame drop status in the
 * top-right corner of the image digital signal processing (IDSP) and encoder blocks.<br>
 * - "Run" button: start profiling the video pipeline<br>
 * - "Interval" dropdown menu: select the time of the latency values' duration
 *
 * @image html cooperhome_performance_latency.png "Figure 4-17. CooperHome Peformance Page - Video Pipeline Analysis." width=1000
 *
 * @subsubsection cooperhome_performance_cpuprofile 4.3.4 CPU Profile
 * The CPU profile section evaluates the CPU core on the Ambarella SoC. The "Processes"
 * tab shows the history diagram of CPU loading and memory use for each process.
 * The "Resources" tab shows the overall CPU loading, memory use, and network
 * throughput.<br>
 * - "Run" button: start to profile the CPU core
 *
 * @image html cooperhome_performance_cpu_proc.png "Figure 4-18. CooperHome Peformance Page - CPU Profile (Processes)." width=1000
 *
 * @image html cooperhome_performance_cpu_resource.png "Figure 4-19. CooperHome Peformance Page - CPU Profile (Resources)." width=1000
 *
 * @subsubsection cooperhome_performance_dspprofile 4.3.5 DSP Profile
 * The DSP profile section evaluates the DSP core on the Ambarella SoC. The "Memory"
 * tab shows memory useage of the DSP continuous memory allocator (CMA) partition(s).<br>
 * - "Run" button: start to profile the DSP core
 *
 * @image html cooperhome_performance_dsp_mem.png "Figure 4-20. CooperHome Peformance Page - DSP Profile (Memory)." width=1000
 *
 * @subsubsection cooperhome_performance_cvflowprofile 4.3.6 CVflow Profile
 * The CVflow profile section evaluates the CVflow core on the Ambarella SoC.
 *  - "Run" button: start to profile the CVflow core
 *
 *  - The "Memory" tab shows memory useage of the CVflow CMA partition.
 * @image html cooperhome_performance_cvflow_mem.png "Figure 4-21. CooperHome Peformance Page - CVflow Profile (Memory)." width=1000
 *
 *  - The "Processes" tab shows the CVflow loading of CVflow processes.
 * @image html cooperhome_performance_cvflow_proc.png "Figure 4-22. CooperHome Peformance Page - CVflow Profile (Processes)." width=1000
 *
 *  - For CV3x, the "Resources" tab shows the loading of multiple CVflow cores (NVP + GVP).
 * @image html cooperhome_performance_cvflow_resource.png "Figure 4-23. CooperHome Peformance Page - CVflow Profile (Resources) for CV3 only." width=1000
 *
 *  - The "Perfstat" tab shows the performance statistics of CVflow cores.
 * @image html cooperhome_performance_cvflow_perfstat.png "Figure 4-24. CooperHome Peformance Page - CVflow Profile (Perfstat)." width=1000
 *
 *
 * @subsection cooperhome_iq_page 4.4 Image Quality
 * The CooperHome image quality page provides users with image controls to Ambarella
 * image process.
 *
 * @image html cooperhome_iq.png "Figure 4-25. CooperHome Image Quality Page."
 *
 * @subsubsection cooperhome_iq_info 4.4.1 Image Processs Information
 * The image process information section provides the image process library version
 * number, parameter file version number, and more.
 *
 * @subsubsection cooperhome_iq_config 4.4.2 Image Process Configuration
 * Image process configuration section provides the image control to individual channels.
 * There are three type of controls (auto exposure, auto white balance and image
 * adjustment) for the user.
 * When entering the image quality page, the image process running at background will
 * be killed, and the `/tmp/aaa_iq_config.lua` will be loaded if file exists. Otherwise,
 * the default `/usr/share/ambarella/idsp/aaa_iq_config.lua` will be loaded.
 * When leaving the image quality page, the original image process will be resumed.
 *
 * - "Save" button: Save current settings to `/tmp/aaa_iq_config.lua`
 *
 * @subsection cooperhome_gdc_page 4.5 Geometric Distortion Correction
 * The CooperHome geometric distortion correction (GDC) page provides users with controls to Ambarella
 * dewarp features through `test_ldc`@ref fs_adv_ldc. Before tuning the geometric distortion, the DSP
 * must be in preview state, and lens_warp of channel configuration must be enabled.
 * After GDC tuning is complete, it will generate the configuration / warp table parameters located
 * in `/tmp/ldc/`. These files can be used by "test_warp" to load a well-tuned combination.
 *
 * @image html cooperhome_gdc.png "Figure 4-26. CooperHome Geometric Distortion Correction Page."
 *
 * @subsubsection cooperhome_gdc_gen 4.5.1 General Configuration
 * The general configuration section sets the channel ID to be tuned and the related lens parameters.
 *
 * @subsubsection cooperhome_gdc_cm 4.5.2 Correction Mode Configuration
 * The correction mode configuration section provides users with controls to follow correction modes.
 * - No Transform Rotation @ref no_transform_rotate
 * - Rectilinear @ref wall_rectilinear
 * - Horizontal Panorama @ref wall_panorama
 * - Cylinder @ref wall_cylinder_panorama
 * - Mercator @ref wall_mercator
 * - Equirectangular @ref wall_equirectangular
 * - Squircular @ref wall_squircular
 * - Vertical Panorama @ref wall_vertical_panorama
 * - Pannini @ref wall_pannini
 * - Pincushion @ref wall_pincushion
 *
 * @subsection cooperhome_vcap_page 4.6 Video Capture
 * The CooperHome video capture page provides the capabilities to capture video outputs.
 *
 * @image html cooperhome_vcap.png "Figure 4-27. CooperHome Video Capture Page."
 *
 * @subsubsection cooperhome_vcap_livestream 4.6.1 Live stream
 * The Livestream section streams the video in realtime given the selections of frame rate and source buffer.
 *
 * @image html cooperhome_vcap_livestream.png "Figure 4-28. CooperHome Video Capture Page - Livestream."
 *
 * @subsection cooperhome_about_page 4.7 About
 * The CooperHome about page provides the descriptions and history updates of the application.
 *
 * @image html cooperhome_about.png "Figure 4-29. CooperHome About Page."
 *
 * - - - -
 *
 * @section cooperhome_prerequisite 5. CooperHome Prerequisite
 * CooperHome server checks the running environment at startup. It requires the following
 * environment to enable the full features of CooperHome. Otherwise, only subset of
 * CooperHome features will be shown.
 *
 * @subsection cooperhome_prerequisite_cl 5.1 Command Line
 * - dmesg
 * - top
 * - df
 * - ifconfig
 * - lscpu
 * - mpstat
 *
 * @subsection cooperhome_prerequisite_ev 5.2 Environment Variable
 * - AMBARELLA_ARCH
 * - SYS_BOARD_BSP
 * - SYS_BOARD_VERSION
 *
 * @subsection cooperhome_prerequisite_drv 5.3 Driver
 * - iav
 * - cavalry
 * - ambdram_statis
 *
 * @subsection cooperhome_prerequisite_ut 5.4 Unit Test
 * - test_encode
 * - test_aaa_service
 * - cavalry_top
 * - cavalry_log
 * - ddrc_v2
 * - dsp
 * - [CV2x] test_dsp_pipeline_latency
 * - test_ldc
 * - jpg_http_stream
 * - load50
 * - test_memcpy
 * - memtester-arm
 * - dsplog_cap
 * - cavalry_profile
 *
 * @subsection cooperhome_prerequisite_sysfs 5.5 System File
 * - [CV5x/CV7x] /proc/ambarella/iav_audit
 * - /proc/ambarella/cma
 * - /proc/ambarella/cavalry_cma
 * - /proc/ambarella/iav_mem
 * - /proc/ambarella/clock
 * - /proc/iomem
 * - /proc/meminfo
 * - /proc/mtd
 * - /proc/version
 * - /proc/mounts
 * - /proc/dev/net
 * - /proc/partitions
 *
 * - - - -
 *
 * @section cooperhome_license 6. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
 *
 * This file and its contents ("Software") are protected by intellectual
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
 *
 * - - - -
 */
/*!
 * @file doc_sys_debug_dram_statistics.h
 * @brief
 * @version 0.1
 * @date 2020-09-23
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
 * @page page_sys_dram_stat DEBUG - DRAM Bandwidth Statistics
 *
 * @section section_dram_bandwidth_statistics_features 1. DRAM Bandwidth Statistics Features
 *
 * When the system is running, user usually pay a lot of attention to the CPUs
 * status, in fact, the dynamic random access memory (DRAM) loading status is also important to users. when
 * the bandwidth resources are tight, users need to adjust the loading of the
 * running case according to the system running status in time. However, the
 * real system is very complicated that there are many DRAM clients interacting
 * with memory at the same time. It is difficult to monitor the behavior of each
 * client at the upper level. For this request, DRAM bandwidth statistics tool
 * is very useful to help users monitor the real-time status of the system and
 * allocate system resources.
 * The DRAM bandwidth statistics tool can obtain some inherent properties of
 * DRAM such as type, bit width, clock and so on. It can also perform statistics on
 * the behavior of all memory clients at a certain time, and calculate their
 * bandwidth and the percentage of maximum throughput. The bandwidth result can
 * help users obtain the real interaction situation of each DRAM clients intuitively,
 * and the percentage result can tell users the proportion of each client's total
 * system resources and the system margin.
 *
 * @subsection dram_bandwidth_statistics_preparations 1.1 Preparations
 * To enable DRAM bandwidth tool environment needs below steps:
 *
 * @note
 * To use DRAM bandwidth tool, Arm® Trust Zone® must be enabled, but secure boot and
 * secure operating system (OS) must be disabled.
 *
 * - For Cooper Amba build:
 *   Enable ATF module to start DRAM statistics, these options below are only for CV5/CV52,
 *   not for CV72 config.
 *
 * @code {.c}
 * build $ make menuconfig
 *   [*] boot --->
 *     [*] amboot (boot/ambamk)  --->
 *       Ambarella Firmware Configuration --->
 *         Memory Options --->
 *                (0x01800000) AMBoot starting address
 *                (0x00008000) AMBoot bootloader stack size
 *                (0x00080000) AMBoot bootloader heap size
 *                (0x00000000) Device Tree start address
 *                (0x00A00000) Initrd start address
 *                (0x04000000) Firmware programmer starting address
 *         AMBoot Options --->
 *           [*] Boot with TrustZone --->
 *                      [ ]   Secure Boot with Signature
 *                      [*]   Secure DTB with Signature (SOC Firmware Config)
 *                      [ ]     Reload DTB in PTB partiton
 *                      [ ]   Boot with trusted OS(OPTEE)
 *      tee  --->
 *         [*] arm-tf (boot/tee/ambamk)
 *   -*- board (boards) --->
 *     Memory --->
 *       (0x02000000) Kernel start address
 * @endcode
 * Load DRAM statistic module into kernel
 * @code {.c}
 * build $ make menuconfig
 *   drv_modules --->
 *       platform --->
 *           [*] kernel-module-ambdram-statis (drv_modules/platform/dram_statis)
 * @endcode
 *
 * - For Cooper Yocto build:
 *   Enable ATF module to start DRAM statistics, these options below are only for CV5/CV52,
 *   not for CV72 config.
 *
 * @code {.c}
 * build $ make menuconfig
 *   meta-ambabsp --->
 *     recipes-bsp --->
 *       [*] boot (meta-ambabsp/recipes-bsp/boot) --->
 *         Ambarella Firmware Configuration --->
 *           Memory Options --->
 * 	           (0x01000000) AMBoot bootloader starting address
 * 	           (0x04000000) Firmware programmer starting address
 *           AMBoot Options --->
 *             [*] Boot with TrustZone --->
 *                      [ ]   Secure Boot with Signature
 *                      [*]   Secure DTB with Signature (SOC Firmware Config)
 *                      [ ]     Reload DTB in PTB partiton
 *                      [ ]   Boot with trusted OS(OPTEE)
 *      tee  --->
 *         [*] arm-tf (boot/tee/ambamk)
 *       -*- board (meta-ambabsp/recipes-bsp/board) --->
 *         Memory --->
 *           (0x02000000) Kernel start address
 * @endcode
 * Load DRAM statistic module into kernel
 * @code {.c}
 * build $ make menuconfig
 *   meta-ambabsp --->
 *     recipes-dbgtool --->
 *       [*] kernel-module-ambdram-statis (meta-ambabsp/recipes-dbgtool/kernel-module-ambdram-statis)
 * @endcode
 *
 * @subsection dram_bandwidth_statistics_configuration 1.2 Configuration
 * The DRAM bandwidth statistics tools have three parameters: duration time, interval time,
 * and verbose switch.<br>
 * Users need to specify a duration time so that the DRAM tool will last for such a
 * long time to do statistics. And the tool calculates the result of every interval if
 * the interval time is set more than 0. Users can get statistical details if verbose switch
 * is on.
 *
 * Users can configure them using the command below:
 * @code
 * board # modprobe ambdram_statis
 * board # echo duration=M interval=N verbose=0/1 > /proc/ambarella/dram_statistics
 * @endcode
 *
 * 1. The unit of "M" is "ms", the default value is 1000 ms.
 * 2. The unit of "N" is "ms", the default value is 0 ms.
 * 3. Verbose can only be set to 0 or 1, it is used to configure whether to output statistical
 * details.
 * 4. If M is not divisible by N, M will be set a multiple of N automatically.
 *
 *
 * @subsection dram_bandwidth_statistics_result 1.3 Statistics Result
 * If users run the DRAM bandwidth statistics tool, a result can be got as below after the
 * duration time delay.<br>
 * The result contains 7 sections: [Usage], [DRAM Info], [Average BW],
 * [Minimal BW among each interval], [Maximal Total BW among each interval], [Interval BW],
 * and [Statistics Info].
 *
 * @code
 * [Usage]
 *   echo duration=M interval=N verbose=0/1 > /proc/ambarella/dram_statistics
 *     M: statistical time in ms, now M=100
 *     N: statistics in every N ms, 0ms means no interval, now N=10
 *
 * [DRAM Info]
 *   LPDDR5 with 64-bits @ 2808MHz, Burst Size: 64, theory BW: 42846 MB/s
 *
 * [Average BW]
 *   Module                Bandwidth(In MB/s)              Percent
 *   -----------
 *   Cortex                         0.933                   0.002
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.008                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.942                   0.002
 *
 * [Minimal BW among each interval]
 *   Module                Bandwidth(In MB/s)              Percent
 *   -----------
 *   [Cortex]                       0.375                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.375                   0.000
 *   -----------
 *   Cortex                         4.591                   0.010
 *   [DSP]                          0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            4.591                   0.010
 *   -----------
 *   Cortex                         4.591                   0.010
 *   DSP                            0.000                   0.000
 *   [VP]                           0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            4.591                   0.010
 *   -----------
 *   Cortex                         4.591                   0.010
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   [GDMA]                         0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            4.591                   0.010
 *   -----------
 *   Cortex                         4.591                   0.010
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   [ENET]                         0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            4.591                   0.010
 *   -----------
 *   Cortex                         4.591                   0.010
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   [Other]                        0.000                   0.000
 *   All                            4.591                   0.010
 *   -----------
 *
 * [Maximal Total BW among each interval]
 *   Module                Bandwidth(In MB/s)              Percent
 *   -----------
 *   Cortex                         4.591                   0.010
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            4.591                   0.010
 *
 * [Interval BW]
 *   Module                Bandwidth(In MB/s)              Percent
 *   -----------
 *   Cortex                         4.591                   0.010
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            4.591                   0.010
 *   -----------
 *   Cortex                         0.387                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.387                   0.000
 *   -----------
 *   Cortex                         0.396                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.396                   0.000
 *   -----------
 *   Cortex                         0.375                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.375                   0.000
 *   -----------
 *   Cortex                         0.371                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.371                   0.000
 *   -----------
 *   Cortex                         0.375                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.375                   0.000
 *   -----------
 *   Cortex                         0.371                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.371                   0.000
 *   -----------
 *   Cortex                         0.375                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.375                   0.000
 *   -----------
 *   Cortex                         0.371                   0.000
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.000                   0.000
 *   Other                          0.000                   0.000
 *   All                            0.371                   0.000
 *   -----------
 *   Cortex                         1.601                   0.003
 *   DSP                            0.000                   0.000
 *   VP                             0.000                   0.000
 *   GDMA                           0.000                   0.000
 *   ENET                           0.084                   0.000
 *   Other                          0.000                   0.000
 *   All                            1.685                   0.003
 *   -----------
 *
 *
 * [Statistics Info]
 *   ID     ClientName        Request           Burst       MaskBurst
 *    0           AXI0           1086            1074              57
 *    1           AXI1            363             363               0
 *    2        L2CACHE              0               0               0
 *    3           USB3              0               0               0
 *    4           PCIE              0               0               0
 *    5          ENET0              0               0               0
 *    6          ENET1              6              12               1
 *    7           FDMA              0               0               0
 *    8         SDAXI0              0               0               0
 *    9         SDAXI1              0               0               0
 *   10         SDAHB0              0               0               0
 *   11       USB(DEV)              0               0               0
 *   12       ARM_DMA0              0               0               0
 *   13       ARM_DMA1              0               0               0
 *   14          CANC0              0               0               0
 *   15           GDMA              0               0               0
 *   16         ORCME0              0               0               0
 *   17         ORCME1              0               0               0
 *   18       ORCCODE0              0               0               0
 *   19       ORCCODE1              0               0               0
 *   20          ORCVP              0               0               0
 *   21        SMEM_WR              0               0               0
 *   22        SMEM_RD              0               0               0
 *   23          VMEM0              0               0               0
 *   24           DBSE              0               0               0
 *
 *   BANK  Bank0   Bank1   Bank2   Bank3   Bank4   Bank5   Bank6   Bank7
 *   Open  39      21      17      24      22      21      20      16
 *
 *   RW Toggle: 316
 *
 *
 *  [perf info]
 *  page miss counter = 2098
 *  bg conflict counter = 15743
 *  die switch counter = 0
 *  dtte         stall = 0
 *  wready       stall = 23654
 *  cready       stall = 148172
 *
 *
 * @endcode
 *
 * Whether the result section is shown depending on the parameter value, the dependencies
 * are as follows：
 * <table>
 * <caption id="dram statistics result section"></caption>
 * <tr> <td> <th> verbose = 0 <th> verbose = 1
 * <tr> <th> interval = 0 <td> 	[Usage]<br>
 *								[DRAM Info]<br>
 *								[Average BW]<br>
 *						 <td>	[Usage]<br>
 *								[DRAM Info]<br>
 *								[Average BW]<br>
 *								[Statistics Info]<br>
 * <tr> <th> interval >0 <td> 	[Usage]<br>
 *								[DRAM Info]<br>
 *								[Average BW]<br>
 * 								[Minimal BW among each interval]<br>
 *								[Maximal Total BW among each interval]<br>
 *						 <td>	[Usage]<br>
 *								[DRAM Info]<br>
 *								[Average BW]<br>
 * 								[Minimal BW among each interval]<br>
 *								[Maximal Total BW among each interval]<br>
 *								[Interval BW]<br>
 *								[Statistics Info]<br>
 * </table>
 *
 *
 * @subsubsection dram_bandwidth_statistics_result_usage 1.3.1 Usage
 *  @image html dram_statistics_usage_archv6.jpg "Figure 1-1. DRAM Statistics Usage."
 * Usage section is belong to basic part, it is mainly to inform the configuration of the
 * parameters and how to use this feature.
 *
 * @subsubsection dram_bandwidth_statistics_result_dram_info 1.3.2 DRAM Info
 *  @image html dram_statistics_dram_info_archv6.jpg Dram Statistics Dram Info
 * DRAM Info section belongs to the basic part, it is mainly to inform the DRAM basic information
 * such as "DRAM type"，"DRAM bits" and so on in the format as below:
 * @code
 * board# "DRAM type" with "DRAM Bits"-bits @ "DRAM Clock" MHz, Burst Size: "Burst Size", theory BW: "DRAM Theory Total Bandwidth" MB/s
 * @endcode
 * such as
 * @code
 * board#  LPDDR5 with 64-bits @ 2808MHz, Burst Size: 64, theory BW: 42846 MB/s
 * @endcode
 * 1. "DRAM type" is the type property of dram including "LPDDR5", "LPDDR4" and "DDR4".
 * 2. "DRAM Bits" is the bit width property of dram including "64" and "32".
 * 3. "DRAM Clock" is the clock property of dram such as "2808 MHz","1800 Mhz" and so on.
 * 4. "Burst Size" is the burst size of dram, it depends on "DRAM type".
 * 5. "DRAM Theory Total Bandwidth" is the maximum tranfer count in theory with these DRAM
 * parameters.
 * It can be calculated as below:
 * @code
 * DRAM Theory Total Bandwidth = DRAM Clock (Hz) * DRAM Bits (byte) * 2
 * @endcode
 *
 * @subsubsection dram_bandwidth_statistics_result_average_bw 1.3.3 Average BW
 *  @image html dram_statistics_average_bw_archv6.jpg "Figure 1-2. DRAM Statistics Average Bandwidth."
 * Average BW section belongs to the basic part, it informs the average bandwidth status for
 * different modules during the measurement period.
 * 1. "Cortex" module is for Arm loading status.
 * 2. "DSP" module is for image digital signal processing (IDSP) and video digital signal processor (VDSP), including ORCME, ORCCODE, SMEM.
 * 3. "VP" module is for computer vision (CV) engine loading status, including ORCVP, ORCL2CACHE, VMEM0 and
 * so on.
 * 4. "GDMA" module is for graphics direct memory access (GDMA) loading status.
 * 5. "Other" module include all the other client such as SDXC, USB, CAN and so on.
 * 6. "Bandwidth (In MB/s)" is calculated according to the total statistical transfer data
 * volume and the duration of statistics.
 *
 * @subsubsection dram_bandwidth_statistics_result_minimal 1.3.4 Minimal BW among Each Interval
 *  @image html dram_statistics_minimal_interval_archv6.jpg "Figure 1-3. DRAM Statistics Minimal Bandwidth."
 * Minimal BW among each interval section is only shown when the interval parameter > 0, it
 * records the bandwidth of different modules in which time period is the minimal in the
 * whole measurement cycle, and shows the bandwidth results of all modules of corresponding
 * time period.
 *
 * @subsubsection dram_bandwidth_statistics_result_maximal 1.3.5 Maximal BW among Each Interval
 *  @image html dram_statistics_maximal_interval_archv6.jpg "Figure 1-4. DRAM Statistics Maximal Bandwidth."
 * Maximal Total BW among each interval section is only shown when the interval parameter > 0, and
 * it shows the maximal bandwidth value of total bandwidth.
 *
 * @note
 * The presentation modes of maximal BW is different from minimal BW.
 *
 * @subsubsection dram_bandwidth_statistics_result_interval 1.3.6 Interval BW
 *  @image html dram_statistics_interval_bw_archv6.jpg "Figure 1-5. DRAM Statistics Interval Bandwidth."
 * Interval bandwidth shows the bandwidth statistics result of every interval in all the duration
 * period.
 *
 * @subsubsection dram_bandwidth_statistics_result_statistics 1.3.7 Statistics Info
 *  @image html dram_statistics_statistics_archv6.jpg "Figure 1-6. DRAM Statistics Info."
 *
 * Statistics Info shows the total statistical transfer data volume and the duration of statistics.
 * It shows the request number, burst number, maskburst number of different client and the
 * bank status.
 *
 * -----------
 *
 * @section section_dram_bandwitdh_statistics_examples 2. DRAM Bandwidth Statistics Example
 *
 * @subsection example_dram_bandwitdh_statistics_example1 Example 1: 1080p encode case
 *
 * First, initialize the EVK board to load the essential drivers and microcode,
 * and start 3A statistic if the following command was not executed previously.
 * Then, put the image audio video (IAV) driver into "preview" state and wait it to enter the stable
 * state for a while .
 *
 * @code
 * board# init.sh --na;modprobe imx274_mipi vinc_id=8 bus_id=3
 * board# test_aaa_service -a &
 * board# test_encode --resource-cfg /usr/share/ambarella/lua_scripts/cv5_vin0_1080p_linear.lua --vout-cfg /usr/share/ambarella/lua_scripts/vout_hdmi.lua #(in console 2)
 * board# test_encode -A -h 1080p -b 0 -e
 * @endcode
 *
 * Next, start DRAM bandwidth statistics tool.
 * @code
 * board# modprobe ambdram_statis
 * board# echo duration=5000 interval=1000 verbose=1 > /proc/ambarella/dram_statistics
 * board# cat /proc/ambarella/dram_statistics
 * @endcode
 *
 * Last, a DRAM bandwidth statistics result is got.
 *
 * @subsection example_dram_bandwitdh_statistics_example2 Example 2: memcpy 1M buffer
 * @code
 * board# modprobe ambdram_statis
 * board# echo duration=5000 interval=1000 verbose=1 > /proc/ambarella/dram_statistics
 * board# cat /proc/ambarella/dram_statistics & test_memcpy -s 0x100000 -c 0 -t 1
 * @endcode
 */
 /*!
 * @file doc_sys_debug_tool.h
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
 * @page sys_debug_tool DEBUG - Tools
 *
 * @section debug_tool_history 0. Revision History
 *
 * <table>
 * <caption id="debug_tool_history">Revision History</caption>
 * <tr><th> SDK Version        <th> Updated Date           <th> Modification
 * <tr><td> 1.5.0              <td> 20220920               <td> Migrated the Debug Tools and Linux Programming Guide from Word into Doxygen
 * <tr><td> 1.5.1              <td> 20231225               <td> Updated Directory Structure
 * </table>
 *
 * - - - -
 *
 * @section sys_debug_tool_sdk 1. Software Development Kit (SDK) Debug Tools
 *
 * This chapter describes how to perform the following:
 * <ul>
 * <li> Section @ref sub_sys_debug_tool_sdk_gen
 * <li> Section @ref sub_sys_debug_tool_sdk_ker
 * <li> Section @ref sub_sys_debug_tool_sdk_cap
 * <li> Section @ref sub_sys_debug_tool_sdk_scr
 * <li> Section @ref sub_sys_debug_tool_sdk_mes
 * <li> Section @ref sub_sys_debug_tool_sdk_gdb
 * <li> Section @ref sub_sys_debug_tool_sdk_mem
 * <li> Section @ref sub_sys_debug_tool_sdk_cav
 * <li> Section @ref sub_sys_debug_tool_sdk_str
 * <li> Section @ref sub_sys_debug_tool_sdk_top
 * <li> Section @ref sub_sys_debug_tool_sdk_cor
 * <li> Section @ref sub_sys_debug_tool_sdk_perf
 * </ul>
 *
 * @subsection sub_sys_debug_tool_sdk_gen 1.1 General Debug Method
 *
 * To modify the Linux kernel driver source code, insert the new kernel driver
 * module directly without burning the entire binary to NAND flash.
 *
 * 1. Compile the Linux driver module under `ambarella/boards/<board_type>`.
 *  @code {.c}
 *  build $ make linux
 *  build $ chmod 755 ../../out/cv5x_<chip_name>/fakeroot
 *  build $ chmod 755 ../../out/cv5x_<chip_name>/fakeroot/lib
 *  @endcode
 *
 * 2. Boot the platform and insert the new module.<br>
 *    If the user is able to access the building directory from the platform,
 *    the following commands will insert the new kernels (do not use init.sh).
 *    (Refer to Section @ref sub_code_build_pc_cifs for more details on managing
 *    network sharing between the building machine, the virtual machine,
 *    and the platform.)
 *  @code {.c}
 *  board # mount -o remount,rw /
 *  board # mount -t cifs //10.0.0.3/vm_share /mnt -o user=<vm_username>,password=<vm_passpharse>
 *  board # cd /mnt/ambarella/out/board_<chip_name>/fakeroot/lib/modules/4.9.0+/extra
 *  @endcode
 *
 *  @note
 *  The command above uses kernel version 4.9.0+. If the user writes or
 *  modifies a program, they should run the program on the platform via network
 *  sharing. The commands below assume that the test_encode has been modified
 *  and recompiled:
 *
 *  @code {.c}
 *  board # mount -o remount,rw /
 *  board # mount -t cifs //10.0.0.3/linux_share /mnt -o user=<linux_username>,password=<linux_passpharse>
 *  @endcode
 *
 *  @note
 *  In the code above, <linux_username> and <linux_passphrase> represent the user ID and password.
 *
 *  @code {.c}
 *  board # cd /mnt/ambarella/unit_test/private/iav_test/arch_v5
 *  board # test_encode
 *  @endcode
 *
 * 3. To change the microcode (also referred to as the ucode) binaries without upgrading
 * the entire firmware, substitute the new binaries for the old microcode binaries
 * <b>orccode.bin, default_binary.bin</b>, and <b>orcme.bin</b> under `/lib/firmware` on the platform.
 *
 *   If the new microcodes are on the SD card, use the following commands:
 *  @code {.c}
 *  board # cp /tmp/mmcblk0p1/orccode.bin  /lib/firmware
 *  board # cp /tmp/mmcblk0p1/default_binary.bin  /lib/firmware
 *  board # cp /tmp/mmcblk0p1/orcme.bin  /lib/firmware
 *  board # reboot
 *  board # init.sh
 *  @endcode
 *
 * 4. If SDK bugs are found during the development, try the following troubleshooting steps:
 *  - Reproduce the bug using the unit test programs on the evaluation kit (EVK) board. Report it using
 *    the steps above.
 *  - If the bug cannot be reproduced by a unit test program, capture the kernel and digital signal processor (DSP)
 *    log and report the bug with the log files. For more details, refer to Section @ref sub_sys_debug_tool_sdk_ker.
 *
 * @subsection sub_sys_debug_tool_sdk_ker 1.2 Kernel Log
 *
 * By default, the kernel log is appended to `/var/log/message` and its size is 200 KB.
 *
 * To change the log file path and size:
 * @code {.c}
 * board # syslogd –O <filename> -s <filesize in KB>
 * board # klogd
 * @endcode
 *
 * For example, save the kernel log to `/tmp/kernel_log.txt`.
 *
 * The size is 1000 KB, as shown below:
 * @code {.c}
 * board # syslogd –O /tmp/kernel_log.txt -s 1000
 * board # klogd
 * board # test_encode --hdmi 720p --resource-cfg /usr/share/ambarella/lua_scripts/CV5x_vin0_1080p_linear.lua
 * @endcode
 *
 * Type the "logread" command to see the kernel logs.
 *
 * @subsection sub_sys_debug_tool_sdk_cap 1.3 Capture the DSP Log and Parse
 *
 * The tool "dsplog_cap", in the binary format, enables users to analyze and
 * debug the DSP. For a more legible option, "dsplog_cap"
 * can also be used to parse the log to text format.
 *
 * For example, to debug a `DSP start encoding failure`, start the
 * dsplog_cap before encoding.
 *
 * Type "dsplog_cap" to see help texts and the usage guide.
 *
 * Perform the following to capture entire DSP logs, limited logs,
 * or parse the DSP log binary file into text.
 *   - To capture DSP logs to a file on an SD card, use the following command:
 *     @code {.c}
 *     board # dsplog_cap -m all -l 3 -r 0 -o /sdcard/log1.bin
 *     @endcode
 *     Alternatively, press <b>'Ctrl + c'</b> to end the DSP log
 *     capture process. If there is no SD card in the camera, but there is
 *     a network shared file system, replace the file directory name above
 *     for the '-o' option.
 *
 *   - To capture limited logs to the SD card, where each log file is
 *     about 100 MB, use the following command:
 *     @code {.c}
 *     board # dsplog_cap -m all -l 3 -r 0 -o /sdcard/log1.bin -p 10000000
 *     @endcode
 *
 *   - To parse the DSP log binary into text, use the following commands.
 *     By default, the tool uses `/lib/firmware` as the ucode firmware directory.
 *
 *     The '-d' option can also be used to specify another ucode directory.
 *     @code {.c}
 *     board # dsplog_cap –i /sdcard/log1.bin -f `/sdcard/log1_parse.txt` -d /mnt/firmware
 *     @endcode
 *     Upon completion, the user can see that the `/sdcard/log1_parse.txt` is the
 *     parsed text version of the DSP log.
 *
 * @note
 * Users can zip the log file and send it to the Ambarella support team for analysis.
 *
 * @subsection sub_sys_debug_tool_sdk_scr 1.4 Debug with the Script
 *
 * If the DSP crashes, the script enables users to capture additional
 * logs such as image audio video (IAV) messages, video input (VIN) registers, and DSP logs.
 * The script can also auto-stop the capture log after detecting the interrupt:
 * "vin0_idsp_last_pixel" or video digital signal processor ("VDSP") hang.
 *
 * To debug with script:
 *
 *  1. Run the test case<br>
 *  2. Run dsp_debug.sh
 *    @code {.c}
 *    board # dsp_debug.sh
 *    @endcode
 *
 * The DSP log bin file is saved in `/tmp`; by default, other files
 * are saved in `/home/ambarella`.
 *
 * Additionally, users can modify the path by referring to the following
 * source code: `$SDK/ambarella/app/utility/amba_scripts/dsp_debug.sh`.
 *
 * @subsection sub_sys_debug_tool_sdk_mes 1.5 Kernel Message Module
 *
 * To avoid the private IAV driver debugging process and other kernel
 * modules, users can enable the kernel message module to redirect all
 * Ambarella private drivers' print messages from the default file
 * `/proc/kmsg` to `/proc/amkmsg`. This provides a convenient method
 * for customers who are required to develop kernel modules.
 *
 * The message is disabled by default. To enable the message, follow
 * the steps as shown below.
 *
 * From menuconfig, use the following commands:
 * @code {.c}
 * build # make menuconfig
 *     [*] Ambarella Linux Configuration --->
 *       [*] Ambarella Private Linux Configuration --->
 *         [*] Build Ambarella private drv msg module
 * @endcode
 *
 * @subsection sub_sys_debug_tool_sdk_gdb 1.6 Gnu DeBugger (GDB) Debug
 *
 * @subsubsection dsub_sys_debug_tool_sdk_board 1.6.1 Debug on the Board
 *
 * 1. Build the firmware.
 *  - To prepare the debug binary, use the following commands.
 *    @par For Cooper Amba build:
 *    @code {.c}
 *    build $ source build/env/amba-build.env
 *    build $ make ipcam_config
 *    build $ make menuconfig
 *      oss --->
 *        [*] gmp (oss/gmp)
 *        [*] isl (oss/isl)
 *        [*] mpc (oss/mpc)
 *        [*] mpfr (oss/mpfr)
 *        [*] gdb (oss/gdb)
 *    @endcode
 *    @par For Cooper Yocto build:
 *    @code {.c}
 *    build $ source build/env/yocto-build.env
 *    build $ make ipcam_config
 *    build $ make menuconfig
 *      meta --->
 *        recipes-devtools --->
 *          [*] gdb (meta/recipes-devtools/gdb)
 *    @endcode
 *
 * 2. Compile the GNU program debugger (GDB) program.
 *  - To compile the customized code on the building machine, use the following commands:
 *    @code {.c}
 *    build $ /usr/local/cortex-a76-2022.03-gcc11.2-linux5.15/bin/aarch64-linux-gnu-gcc gdb-sample.c -o gdb-sample -g
 *    @endcode
 *  - Confirm that the program is compiled for the correct target, using the following commands:
 *    @code {.c}
 *    build $ /usr/local/cortex-a76-2022.03-gcc11.2-linux5.15/bin/aarch64-linux-gnu-readelf -h hello | grep -i "class\|machine"
 *    @endcode
 *
 *  @note
 *  - The debug tool mentioned in step one and the the application with
 *    debug information mentioned in step two are both necessary steps.
 *    Neither can be omitted.
 *  - The step two is a simple and fast way to add the debug infomation.
 *    Another way to add the debug infomation is to build
 *    all the applications with the debug infomation. This results in
 *    a large size of the compiled firmware. So it is not recommended
 *    when the device has a small storage space.
 *    @code {.c}
 *    build $ make menuconfig
 *    [*] Ambarella Application Configuration  --->
 *      [*]   Build Ambarella Application with debug info
 *      //unselect the following configuration to avoid comipling errors
 *      [ ]   Build Ambarella SDK with FORTIFY_SOURCE=2
 *    @endcode
 *
 * 3. Start the GDB on board.
 *  - First, use TFTP, USB, or another method to copy the gdb-sample and `gdb-sample.c` to the board.
 *  - Then, use the following commands to debug the application:
 *    @code {.c}
 *    board # gdb gdb-sample
 *    GNU gdb (GDB-****.**.**) *.*.*.********-git
 *    Copyright (C) **** Free Software Foundation, Inc.
 *    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
 *    This is free software: you are free to change and redistribute it.
 *    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
 *    and "show warranty" for details.
 *    This GDB was configured as "aarch64-linux-gnu".
 *    Type "show configuration" for configuration details.
 *    For bug reporting instructions, please see:
 *    ……
 *    Find the GDB manual and other documentation resources online at:
 *    <http://www.gnu.org/software/gdb/documentation/>.
 *    For help, type "help".
 *    Type "apropos word" to search for commands related to "word"...
 *    Reading symbols from gdb-sample...done.
 *    (gdb)
 *    @endcode
 *
 *    @par Some useful parameters for GDB:
 *    <table>
 *    <caption id="gdb_command_parameters">Table 1-1. Useful Parameters for GDB.</caption>
 *    <tr><th> Comamnds                                  <th> Function
 *    <tr><td> gdb --args gdb-sample [arg0 arg1 ...]     <td> Call the application with arguments
 *    <tr><td> gdb --directory=SOURCE_CODE_DIR           <td> Search for source files in SOURCE_CODE_DIR
 *    </table>
 *
 *    @par Some useful parameters for GDB debugging
 *    <table>
 *    <caption id="gdb_debugging_parameters">Table 1-2. GDB Debugging Parameters.</caption>
 *    <tr><th> Comamnds                                  <th> Function
 *    <tr><td> b[reak] main                              <td> Places a breakpoint at the beginning of the program
 *    <tr><td> b[reak] N                                 <td> Places a breakpoint at line N
 *    <tr><td> b[reak] fn                                <td> Places a breakpoint at the beginning of function "fn"
 *    <tr><td> info break                                <td> Lists breakpoints
 *    <tr><td> d[elete] N                                <td> Deletes breakpoint number N
 *    <tr><td> r[un] [arglist]                           <td> Runs the program with the arglist if have until a breakpoint or error is encountered
 *    <tr><td> c[ontinue]                                <td> Continues running the program until the next breakpoint or error
 *    <tr><td> s[tep] [N]                                <td> Runs the next [N] line(s) of the program
 *    <tr><td> n[ext]                                    <td> Similar to s, but it does not step into functions
 *    <tr><td> bt, backtrace, where                      <td> Prints backtrace of all stack frames, or innermost COUNT frames
 *    <tr><td> l[ist] [N|function]                       <td> Lists specified functions or lines
 *    <tr><td> p[rint] var[=X]                           <td> Prints the current value of the variable "var" or set 'var' to 'X'
 *    <tr><td> q[uit], exit                              <td> Quits GDB
 *    </table>
 *
 * @subsubsection dsub_sys_debug_tool_sdk_host 1.6.2 Debug on the Host
 *
 * 1. Build the firmware.
 *  - To prepare the debug binary, use the following commands:
 *    @code {.c}
 *    build $ make sync_build_mkcfg
 *    build $ make cv5x_xxx_config (xxx = board name or specifications)
 *    build $ make menuconfig
 *    Ambarella File System Configuration
 *        -->Debug Tools
 *            --> [*] Add gdbserver into root_fs
 *    build $ make -j8
 *    @endcode
 *
 * 2. Compile the GDB program.
 *  - To compile the customized code on the building machine, use the following commands:
 *    @code {.c}
 *    build $ /usr/local/cortex-a76-2022.03-gcc11.2-linux5.15/bin/aarch64-linux-gnu-gcc gdb-sample.c -o gdb-sample -g
 *    @endcode
 *  - Confirm that the program is compiled for the correct target by using the following commands:
 *    @code {.c}
 *    build $ /usr/local/cortex-a76-2022.03-gcc11.2-linux5.15/bin/aarch64-linux-gnu-readelf -h hello | grep -i "class\|machine"
 *    @endcode
 *
 * 3. Start the GDB server on board.
 *  - First, use TFTP, USB, or another method to copy the gdb-sample to the board, and then use the following commands:
 *    @code {.c}
 *    board # gdbserver localhost:2345 gdb-sample
 *    @endcode
 *
 *    @note
 *    `gdbserver localhost:2345 gdb-sample [arg0 arg1 ...]` can be used when the application requires arguments.
 *
 *  - Start the GDB client on the host.
 *    @code {.c}
 *    board #/usr/local/cortex-a76-2022.03-gcc11.2-linux5.15/bin/aarch64-linux-gnu-gdb gdb-sample
 *    GNU gdb (GDB-****.**.**) *.*.*.********-git
 *    Copyright (C) **** Free Software Foundation, Inc.
 *    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
 *    This is free software: you are free to change and redistribute it.
 *    There is NO WARRANTY, to the extent permitted by law. Type "show copying"
 *    and "show warranty" for details.
 *    This GDB was configured as "aarch64-linux-gnu".
 *    Type "show configuration" for configuration details.
 *    For bug reporting instructions, please see:
 *    <http://www.gnu.org/software/gdb/bugs/>.
 *    Find the GDB manual and other documentation resources online at:
 *    <http://www.gnu.org/software/gdb/documentation/>.
 *    For help, type "help".
 *    Type "apropos word" to search for commands related to "word"...
 *    Reading symbols from gdb-sample...done.
 *    (gdb) target remote 10.0.0.2:2345
 *    @endcode
 *
 *    @note
 *    `c[ontinue]` must be used when the user starts to run the application insteading of `r[un]`.
 *
 * @subsection sub_sys_debug_tool_sdk_mem 1.7 Memory Debug
 *
 * 1. Build the application using the following options in menuconfig:
 *
 * - For Cooper SDK Amba build:
 *   @code {.c}
 *   build $ source build/env/amba-build.env
 *           ...
 *           ENV_FSANITIZE_OPTION : 0 // 0:close, 1:address, 2:thread, 3:leak, 4:undefined
 *   build $ export ENV_FSANITIZE_OPTION=1 // or 2 / 3 / 4
 *   build $ make xxx (xxx = the target application)
 *   @endcode
 *
 * - For Cooper SDK Yocto build:
 *   @code {.c}
 *   build $ cat metadata/meta-ambabsp/classes/ambadebug.bbclass | grep 'ENV_FSANITIZE_OPTION ?='
 *   ENV_FSANITIZE_OPTION ?= "0"
 *   # Change the value of ENV_FSANITIZE_OPTION to 1 or 2 / 3 / 4
 *   build $ grep -rn ambadebug metadata/
 *   metadata/meta-ambaapp/recipes-usb-gadget/test-ffs/test-ffs-host.bb:19:inherit ambadebug
 *   # The recipe of application should inherit ambadebug class
 *   build $ make xxx (xxx = the target application)
 *   @endcode
 *
 *   @note
 *   - For more information about sanitizer options, users can refer to the GCC manual book
 *     (https://gcc.gnu.org/onlinedocs/gcc-12.3.0/gcc/Instrumentation-Options.html).
 *
 * 2. Copy the application, the library libasan* and libubsan* in
 *  folder `LINARO-TOOLCHAIN/arm-linux-gnueabihf/libc/lib` to `/lib` on the board.
 *
 * 3. Run the application on the board; the debug messages will print.
 *  The following uses test_yuvcap as an example:
 *  @code {.c}
 *  board # test_yuvcap -b 0 -Y -f 1.yuv -F 0 -r 1
 *  =================================================================
 *  ==322==ERROR: AddressSanitizer: global-buffer-overflow on address 0x00000040d6f4 at pc 0x007f8eb76a58 bp 0x007fda2d2e90 sp 0x007fda2d2f08
 *  WRITE of size 12288000 at 0x00000040d6f4 thread T0
 *      #0 0x7f8eb76a57 in __interceptor_memset /development/abe-toolchain-build/abe.build/ambarella/../../tarballs/gcc-11.2-2018.08/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:709
 *      #1 0x405b5f in capture_yuv /cygdrive/z/shfan/projects/s5l_master/ambarella/unit_test/private/iav_test/arch_v5/test_yuvcap.c:709
 *      #2 0x40c8ef in main /cygdrive/z/shfan/projects/s5l_master/ambarella/unit_test/private/iav_test/arch_v5/test_yuvcap.c:1650
 *      #3 0x7f8e9a0ce3 in __libc_start_main ../csu/libc-start.c:308
 *      #4 0x40207b  (/usr/local/bin/test_yuvcap+0x40207b)
 *
 *  0x00000040d6f4 is located 44 bytes to the left of global variable '*.LC1' defined in '/cygdrive/z/shfan/projects/s5l_master/ambarella/unit_test/private/iav_test/arch_v5/test_yuvcap.c' (0x40d720) of size 11
 *    '*.LC1' is ascii string 'media/test'
 *  0x00000040d6f4 is located 0 bytes to the right of global variable '*.LC0' defined in '/cygdrive/z/shfan/projects/s5l_master/ambarella/unit_test/private/iav_test/arch_v5/test_yuvcap.c' (0x40d6e0) of size 20
 *    '*.LC0' is ascii string '/mnt/media/test.yuv'
 *  SUMMARY: AddressSanitizer: global-buffer-overflow /development/abe-toolchain-build/abe.build/ambarella/../../tarballs/gcc-11.2-2021.09/libsanitizer/sanitizer_common/sanitizer_common_interceptors.inc:709 in __interceptor_memset
 *  Shadow bytes around the buggy address:
 *    0x001000081a80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 *    0x001000081a90: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 *    0x001000081aa0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 *    0x001000081ab0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 *    0x001000081ac0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
 *  =>0x001000081ad0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00[04]f9
 *    0x001000081ae0: f9 f9 f9 f9 00 03 f9 f9 f9 f9 f9 f9 00 01 f9 f9
 *    0x001000081af0: f9 f9 f9 f9 00 00 00 00 00 00 00 06 f9 f9 f9 f9
 *    0x001000081b00: 00 05 f9 f9 f9 f9 f9 f9 00 00 00 00 00 00 02 f9
 *    0x001000081b10: f9 f9 f9 f9 00 00 06 f9 f9 f9 f9 f9 00 00 00 00
 *    0x001000081b20: 00 00 00 00 00 00 07 f9 f9 f9 f9 f9 00 00 00 05
 *  Shadow byte legend (one shadow byte represents 8 application bytes):
 *    Addressable:           00
 *    Partially addressable: 01 02 03 04 05 06 07
 *    Heap left redzone:       fa
 *    Freed heap region:       fd
 *    Stack left redzone:      f1
 *    Stack mid redzone:       f2
 *    Stack right redzone:     f3
 *    Stack after return:      f5
 *    Stack use after scope:   f8
 *    Global redzone:          f9
 *    Global init order:       f6
 *    Poisoned by user:        f7
 *    Container overflow:      fc
 *    Array cookie:            ac
 *    Intra object redzone:    bb
 *    ASan internal:           fe
 *    Left alloca redzone:     ca
 *    Right alloca redzone:    cb
 *  ==322==ABORTING
 *  @endcode
 *
 * @subsection sub_sys_debug_tool_sdk_cav 1.8 Capture the Cavalry Log
 *
 * <b>cavalry_log</b> enables users to debug system errors by providing the liveshow
 * log when ucode is running. Because the system generates many
 * messages, Ambarella recommends using <b>Telnet</b> for this command.
 * @image html debug_tool_cavalry_log.png "Figure 1-1. Capture Vector Processor Ucode Log."
 *
 * @subsection sub_sys_debug_tool_sdk_str 1.9 Stream Diff
 *
 * Stream Diff can assist users in debugging dynamic random-access memory (DRAM). <b>Stream Diff</b> encodes
 * two streams with identical encoding parameters; the streams must be
 * aligned in each bit.
 *
 * The following provides an example of <b>Stream Diff</b>:
 * @code {.c}
 *  board # init.sh --imx274_mipi
 *  board # test_image -i0 &
 *  board # test_encode -i0 –cvbs 480i -X --bsize 1080p --bmax 1080p --extra-buf 1 -A -H 1080p -b 0 --bitrate 4000000 -B -H 1080p --bitrate 4000000 -b 0 --smax 1080p
 *  board # test_encode -A -e -B -e
 *  board # test_stream --dram-en 1 --dram-mode 0 --no
 * @endcode
 *
 * If the following messages appear, the DRAM is unstable.
 * @code {.c}
 * Frame[1]: comapre stream A and stream B, bits info is different!
 * Frame[2]: comapre stream A and stream B, bits info is different!
 * Frame[3]: comapre stream A and stream B, bits info is different!
 * Frame[4]: comapre stream A and stream B, bits info is different!
 * Frame[5]: comapre stream A and stream B, bits info is different!
 * Frame[6]: comapre stream A and stream B, bits info is different!
 * Frame[7]: comapre stream A and stream B, bits info is different!
 * @endcode
 *
 * @subsection sub_sys_debug_tool_sdk_top 1.10 Cavalry Top
 *
 * Users can run "cavalry_top" to check the efficiency of the vector processor (VP) chip.
 * This is the same as the command "top" in Linux, as shown below.
 * @code {.c}
 * board # modprobe cavalry;cavalry_load -f /lib/firmware/cavalry.bin
 * board # cavalry_top -u 100 -c 1000
 * PID	VP%	CMD
 * VP IDLE 100.000%
 * @endcode
 *
 * @subsection sub_sys_debug_tool_sdk_cor 1.11 Cavalry Core Dump
 *
 * If the VP hangs, users can utilize this tool to dump all
 * necessary information into a single binary. Then, the binary can
 * be "replayed" on the Ambarella side to determine if the problem
 * is due to either hardware instability or a directed acyclic graph (DAG).
 * @code {.c}
 * board # cavalry_core_dump -d /tmp/dump.bin (Save into core dump)
 * @endcode
 *
 * Send the `dump.bin` to Ambarella to enable Ambarella to reproduce
 * the problem without using the actual network model files and applications.
 * (Note that this method is only applicable for the VP hang issue.)
 *
 * @subsection sub_sys_debug_tool_sdk_perf 1.12 Performance Debugging
 *
 * Perf is a built-in performance analysis tool for Linux. Perf can be used to analyze performance
 * of the following issues: specific applications (per thread), the kernel, applications and the
 * kernel simultaneously. To support perf, the user must follow the steps below:
 * 1. Set up the building environment.
 *  @code {.c}
 *  build $ export TARGET=aarch64-linux-gnu
 *  build $ export INSTALLDIR=/usr/local/cortex-a76-2022.08-gcc12.1-linux5.15
 *  build $ export PATH=$INSTALLDIR/bin:$PATH
 *  build $ export TARGETMACH=${TARGET}
 *  build $ export CROSS=${TARGET}-
 *  build $ export CC=${CROSS}gcc
 *  build $ export LD=${CROSS}ld
 *  build $ export AS=${CROSS}as
 *  build $ export C_INCLUDE_PATH=$(YOUR_SDK_PATH)/ambarella/prebuild/oss/armv8-a/libpng/include/
 *  build $ export LD_LIBRARY_PATH=$(YOUR_SDK_PATH)/ambarella/prebuild/oss/armv8-a/libpng/usr/lib/
 *  @endcode
 * 2. Enable kernel support for various performance events provided by the software and hardware.
 *  @code {.c}
 *  build $ make menuconfig_public_linux
 *	  General setup
 *		  Kernel Performance Events And Counters  --->
 *			  [*] Kernel performance events and counters
 *  @endcode
 * 3. Download and build the libraries that perf depends on (copy <a href="script/Makefile" target="_blank"><b>Makefile</b></a> to ~/perf_tool/),
 *  The Makefile includes all dependent libraries such as audit, binutils, bzip2, elfutils, xz, slang, libunwind, zlib, dl, and building steps.
 *  @code {.c}
 *  build $ mkdir ~/perf_tool/
 *  build $ make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- clean && make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- EXTRA_CFLAGS="-fPIC"
 *  @endcode
 * 4. Build the perf tool.
 *  @code {.c}
 *  build $ mkdir $(HOME_PATH)/build_out
 *  build $ make ARCH=arm64 WERROR=0 CROSS_COMPILE=aarch64-linux-gnu- LDFLAGS="-L$(HOME_PATH)/perf_tool/deps-arm64/lib" EXTRA_CFLAGS="-lbz2 -fPIC -I$(HOME_PATH)/perf_tool/deps-arm64/include" -C $(YOUR_SDK_PATH)/ambarella/kernel/linux-5.15/tools/perf  O=$(HOME_PATH)/build_out V=1
 *  @endcode
 * 5. Install perf to the EVK.
 *  @code {.c}
 *  board # cp deps-arm64/lib/libbz2.so.1.0.6 /usr/lib/
 *  board # cp deps-arm64/lib/libunwind-aarch64.so.8 /usr/lib/
 *  board # cp deps-arm64/lib/libunwind.so.8 /usr/lib/
 *  board # cp deps-arm64/lib/libslang.so.2 /usr/lib/
 *  board # cp perf /usr/local/bin
 *  board # chmod +x /usr/local/bin/perf
 *  @endcode
 * 6. Run perf to record the kernel events and copy the output to the PC.
 *  @code {.c}
 *  board # perf record -F 999 -a -g -- sleep 10
 *  board # perf script > perf.data.processed
 *  @endcode
 * 7. Generate scalable vector graphics (SVG).
 *  @code {.c}
 *  build $ cat perf.data.processed | stackcollapse-perf.pl > perf.data.processed.folded
 *  build $ flamegraph.pl --cp perf.data.processed.folded > perf.svg
 *  @endcode
 *  @image html script/perf.svg Figure 1-2. Perf.svg
 *
 *  @note
 *  `Flamegraph.pl` and `stackcollapse-perf.pl` are located in <a href="https://github.com/brendangregg/FlameGraph" target="_blank"><b>FlameGraph-master.zip</b></a>.
 *  Unzip `FlameGraph-master.zip` and add the path to the environment.
 *
 * - - - -
 *
 * @section sys_debug_tool_license 2. License
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
 * @file doc_sys_faq.h
 * @brief
 * @version 1.0
 * @date 2022-04-17
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
 * @page page_sys_faq_doc DEBUG - FAQ
 *
 * @section faq_choosing_the_appropriate_chip 1. Choosing the Appropriate Chip
 *
 * Choosing an appropriate chip depends on the following:
 * encoding specifications, encode mode, double data rate (DDR) bandwidth, and DDR size.
 * This section lists the specifications required for each to enable users
 * to choose the appropriate chip(s) for their applications.
 * - Encoding specifications<br>
 *   Please check the specification from release note document.
 * - Encode mode<br>
 *   It is important to ensure that
 *   the feature wanted is supported in current encode mode.<br>
 *   For details, refer to @ref fs_adv_enc_mode.
 * - DDR bandwidth<br>
 *   DDR bandwidth is an important resource that users care a lot about.
 *   Dynamic random access memory (DRAM) bandwidth statistics tool could be useful when profiling bandwidth usage.
 *   Please check @ref fs_others_dram_statistics for the usage of the tool.
 * - DDR size<br>
 *   DDR memory is divided into three partitions: Linux, image audio video (IAV), and digital signal processor (DSP).
 *   The Linux partition is used to run the operating system and the user program;
 *   the IAV partition is used for the interaction between the DSP and IAV;
 *   and the DSP partition is reserved for the DSP's internal usage.<br>
 *   Currently, users can perform their own optimization.
 *   For details, refer to the Ambarella CV5x DG Flexible Linux SDK DRAM Optimization document.<br>
 *   For the DSP partition, users can decide the size according to the specification.
 *   After they decide the size, users should check the minimum DSP memory with the user case;
 *   for example, use test commands.<br>
 *   Additionally, users can modify the IAV partition using the "make menuconfig" command
 *   with the requirement.<br>
 *   The following commands can be used to check the DSP RAM cost when the case is running:
 *   @code
 *   # dmesg | grep handle_dsp_cfg_msg
 *   [ 2762.614016] handle_dsp_cfg_msg(130): DSP DRAM Used: 392 MB
 *   @endcode
 *
 * @section faq_system_change 2. System Change
 *
 * Ambarella performs several tests to determine the chip clocks for various part numbers.
 * Therefore, to ensure stable encoding, Ambarella does not include APIs to change the clocks
 * and recommends users not attempt to change them.
 * Instead, Ambarella recommends users to choose a real part number
 * with "Board-> Board Revision" in "make menuconfig" to
 * ensure that the system clock is configured correctly.
 *
 * @section faq_how_to_obtain_audio_data 3. How to Obtain Audio Data
 *
 * In the user space, there are two interfaces for obtaining the PCM audio data: ALSA or PulseAudio.
 * Although pulse audio provides a strong and rich interface, it requires more DRAM bandwidth and CPU.<br>
 * For ALSA, refer to the ALSA sample code for audio applications:<br>
 * `ambarella\unit_test\linux\audio\test_audio.cpp` or<br>
 * `ambarella\app\cloud\media_mw\src\audio_platform\linux_alsa\audio_alsa.cpp`.<br>
 * For pulse audio, users can refer to the following:<br>
 * `ambarella\app\cloud\media_mw\src\audio_platform\pulse_audio\pulse_audio.cpp` or<br>
 * `ambarella\oryx_v2\base\audio\device\am_audio_device_pulse.cpp`.
 *
 * @section faq_full_duplex_communication_for_audio 4. Full Duplex Communication For Audio
 *
 * The I2S interface supports two-way voice data transmission;
 * its core task is to achieve echo cancellation.
 * Hardware and software methods can be used for echo cancellation:
 * - For hardware, users’ audio code should support echo cancellation, such as AK7755.
 *   Alternatively, users can add DSP for echo cancellation between audio CODEC and the master control chip,
 *   such as AK4951 + AK7719.
 * - For software, users can try AEC of pulse audio in the SDK, which must run Oryx.
 *
 * @section faq_flash_usage 5 Flash Usage
 *
 * @subsection faq_flash_type 5.1 Type Confirm
 *
 * Before selecting a flash, first check if the flash is supported by the Ambarella SDK:
 * @code
 * make menuconfig
 *   -*-Ambarella Boot Configuration --->
 *        Amboot Configuration --->
 *	        Hardware Options  --->
 *            [*] Support NAND Driver  --->
 *               Nand Flash Type (P2K_E128K)  --->
 * @endcode
 * Once the support is confirmed, choose the correct type and compile.
 *
 * @subsection faq_flash_ecc 5.2 ECC Confirm
 *
 * Because incorrect ECC bits may lead to serious problems,
 * users must first confirm and check the ECC so that ECC configuration errors do not occur in the mass production.<br>
 * The CV5x chip includes a hardware ECC function and supports 1/6/8 bit ECC.
 * In the hardware design, first confirm that the ECC bits exist in the flash specification,
 * and then configure the corresponding hardware POC for EVK as shown below.
 * @code
 * POC (15, 16) (VD0_OUT15, I2S0_SO):
 * ECC level: [15 16], 1-bit = 00
 * ECC level: [15 16], 6-bit = 01
 * ECC level: [15 16], 8-bit = 11
 * @endcode
 * @note
 * If users want to support the 8-bit mode, then the flash page NAND size should be (2K+128).
 * For more information,
 * refer to the section on the ECC level in @ref si_nand.
 *
 * @subsection faq_flash_format_level 5.3 File System Format and ECC Level
 *
 * For different page sizes, the number of ECC bytes generated by different ECC levels and its layout
 * is in out of band (OOB).
 * For the code, refer to the structure nand_ecclayout in
 * `ambarella\kernel\linux-5.4\drivers\mtd\nand\ambarella_nand.c`.<br>
 * If the unsorted block image file system (UBIFS) are used, OOB stores only bad block markers and ECC data.
 * In this case, as long as OOB has sufficient size to store ECC which is defined by flash specification,
 * then flash can use UBIFS.
 * If YAFFS2 are used,
 * OOB includes file systems with information relating to YAFFS2,
 * which are required for various storage purposes.
 * Therefore, the OOB size must be large enough to store both ECC and YAFFS tags.<br>
 * The following lists the requirements:<br>
 * @code
 * Chunks: 1KB 30 Bytes
 * Chunks: 2kB 42 Bytes
 * @endcode
 * @note
 * If the OOB size is insufficient, it cannot support YAFFS2.<br>
 * If JFFS2 is used, then JFFS2 uses OOB to store specific information and must ensure that these locations,
 * the hardware ECC, and the other data locations do not conflict with each other.<br>
 * For flash with built-in ECC, use UBIFS, as the OOB cannot be read from or written to.
 *
 * @subsection faq_flash_notice 5.4 Notice for Flash Programmer
 *
 * A flash programmer is typically required in mass production.
 * Because generating the ECC using the burner can be difficult,
 * users can generate it using the master instead.<br>
 * The following steps describe this procedure:<br>
 * - Select a part of the flash that includes no bad blocks and solder it to the board.
 * Erase all, and then use AmbaUSB to burn the firmware of mass production.
 * When finished, do not reboot. Also, avoid writing operations in flash while running.<br>
 * Weld off the flash, wash, place it in the flash programmer, and then read the content several times,
 * saving to the bin file and ensure there are no inconsistencies.<br>
 * Use the flash programmer to burn the bin file in Step 2 to flash.
 * Ensure the burn is to the partition and not the entire piece.
 * Mark the bad blocks using the burner.<br>
 * Patch the flash, and ensure that the system is fully activated for the first boot.
 *
 * @section faq_gpio_configuration 6 GPIO Configuration
 *
 * @subsection faq_gpio_default 6.1 System Startup with Default Configuration
 *
 * Activated in AMBoot, the default value is written in the `boards\$BOARD\bsp\bsp.h`.
 * For example, for cv5_timn: `boards\cv5_timn\bsp\bsp.h`.
 * @code
 * DEFAULT_GPIOX_AFSEL
 * DEFAULT_GPIOX_DIR
 * DEFAULT_GPIOX_MASK
 * DEFAULT_GPIOX_DATA,
 * @endcode
 * For further details, refer to the following:
 *    - GPIO: AMBARELLA CV5 HW PRM
 *    - GPIO: AMBARELLA CV52 HW PRM
 *
 * For GPIO, the following two registers can be enabled:
 * @code
 * DEFAULT_GPIO0_CTRL_ENA
 * DEFAULT_GPIO0_CTRL_DIR
 * @endcode
 * If one GPIO includes multiple functions, then the user must set its IOMUX register;
 * the corresponding feature selection list can be found in the Ambarella CV5x Hardware PRM
 * document. If the register is not correctly set, the default value will not be used.
 *
 * @subsection faq_gpio_control 6.2 GPIO Control in User Space
 *
 * The following commands can be used for debug purposes:
 * @code
 * # amba_debug -g 59 -d 0x0
 * # amba_debug -g 59 -d 0x1
 * @endcode
 * For further details, refer to @ref si_debugfs.
 * For customer use:
 * @code
 * # echo 59 > /sys/class/gpio/export
 * # echo out > /sys/class/gpio/gpio59/direction
 * # echo 1 > /sys/class/gpio/gpio59/value
 * # echo 0 > /sys/class/gpio/gpio59/value
 * # echo in > /sys/class/gpio/gpio59/direction
 * # cat /sys/class/gpio/gpio59/value
 * # echo 59 > /sys/class/gpio/unexport
 * @endcode
 *
 * @section faq_adc_usage 7. ADC Usage
 * For information about ADC usage, refer to `ambarella\kernel\linux-5.15\Documentation\arm\ambarella\adc.txt`.
 *
 * @section faq_lcd_in_cv5x 8. LCD in CV5x
 *
 * The following shows example steps for adding an LCD named "mylcd0" with a resolution of 320x240:
 * - Refer to the digital or td043 driver in `Ambarella\kernel\private\drivers\vout\amblcd\`.
 *   Check the LCD datasheet to confirm the resolution, pixel clock, timing signals,
 *   interface types rgb565 / rgb888, and other information, then create the driver following the datasheet.<br>
 *   Use "`test_encode ¨Ci 0 --lcd 320x240`" to configure and test the LCD.
 *
 * @section faq_chip_id_check 9. Chip ID Check
 *
 * UUID is not provided for chips. However, users can check the CPU type (chip ID) as follows:
 * @code
 * AM_IOCTL(fd_iav, IAV_IOC_GET_CHIP_ID, &chip_id);
 * @endcode
 * @note
 * Call this check after the DSP enters the preview or encode mode.
 *
 * @section faq_protection_against_overcurrent_in_the_usb_host 10. Protection Against Overcurrent in the USB Host
 *
 * If the USB host does not have an overcurrent,
 * users must disable the flow detection in the source code to avoid issues
 * and ensure that the USB device can be identified.<br>
 * Modify `boards/cv5x_board/bsp/cv5x_board.dts`.
 * The following command is an example that uses the CV5 Timn EVK board:
 * @code
 * Boards/cv5_timn/bsp/cv5_timn.dts
 *     rct@ed080000 {
 *         usbphy: usbphy@ed080050 {
 *             // high will trigger the ocp interrupt
 *                amb,ocp-polarity = <0>;
 *             // disable below 2 lines if disable over-current
 *             //   pinctrl-names = "default";
 *             //   pinctrl-0 = <&usb_host0_pins_a>;
 *                md-gpios = <&gpio 34 0x0>;
 *                hub-gpios = <&pca9539 10 0x0>;
 *         };
 *     };
 * @endcode
 * Check to verify that the open firmware is enabled:
 * @par For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 *   [*] boot (boot) --->
 *     Bootloader --->
 *       Ambarella Firmware Configuration --->
 *         AMBoot Options  --->
 *           Open Firmware and Device Tree  --->
 *             [*] Support Open Firmware
 * @endcode
 * @par For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 *   meta-ambabsp --->
 *     recipes-bsp --->
 *       [*] boot (meta-ambabsp/recipes-bsp/boot) --->
 *         Bootloader --->
 *           Ambarella Firmware Configuration --->
 *             AMBoot Options  --->
 *               Open Firmware and Device Tree  --->
 *                 [*] Support Open Firmware
 * @endcode
 *
 * @section faq_watchdog 11. Watchdog
 *
 * If users want to use the CV5x internal watchdog,
 * they should refer to the example of the watchdog in the kernel in
 * `ambarella\kernel\linux-5.15\Documentation\watchdog\`.
 *
 * @section faq_spinor_flash 12. SPI NOR Flash
 *
 * First, users must add new flash-related attributes in the array "amb_ids",
 * and include the ID flash, sector size, sector number, page size, clock, and more.<br>
 * Next, in the function <B>amb_spi_nor_shutdown()</B>,
 * users must add the reset command for the new flash to avoid system problems after reboot.<br>
 * The following example is for mx25l25645g.
 * For this flash, the ID is 0x1940c8; there are 512 sectors, each sector is 64K,
 * and the page size is 256 bytes.
 * See the following "amb_ids" after adding mx25l25645g:
 * @code
 * Const struct ambid_t amb_ids[] static = {
 * ... ...
 * {"32M", INFO (0x1920c2, 0, 64 * 1024, 512, 256, 50000000, 0,)},
 * {"mx25l25645g", INFO (0x1940c8, 0, 64 * 1024, 512, 256, 50000000, 0,)},
 * {"w25q128", INFO (0xef4018, 0, 64 * 1024, 256, 256, 50000000, 0,)},
 * ......
 * }
 * @endcode
 * SPI flash includes a definition of "addressing space".
 * Address space of 3 bytes can access the 16M flash.
 * If users must access more than 16M storage space, then they should use the 4-byte addressing mode.<br>
 * For mx25l25645g 32M, if the system wants to access any data within the flash,
 * the 4-byte addressing mode is required.
 * In functions <B>amb_spi_nor_probe()</B>,
 * the system sends 4 byte instructions to the flash, so mx25l25645g is in a state of 4 byte.
 * If the system reboots at this time, AMBoot will access the flash with 3 bytes,
 * causing data read anomalies and leading to startup issues.
 * The solution to this problem is to send reset to mx25l25645g in function "amb_spi_nor_shutdown()".
 *
 * @section faq_sensor_driver_init 13. Sensor Driver Initialization
 *
 * The following lists information about the sensor driver initialization:
 * - Users must add parameters when using "insmod" or "modprobe" in order to load the driver directly.
 * - Parameters such as the bayer_pattern, bus_addr, and lane, are related to the hardware design.
 * - bayer_pattern is related to the sample timing of the pixel clock.
 * - bus_addr is related to the I2C address and interface of the sensor.
 * - Lane specifies the data transmission number between the sensor and main control.
 *   For example, set number of lanes to 2 when using OV4689 in the CV5 platform.
 *
 * @section faq_supporting_chinese_ssid 14. Supporting Chinese SSID
 *
 * The following lists the steps required to support Chinese SSID:
 * - Create a corresponding file for the Chinese fonts.
 *   Run the following command before generating the firmware
 *   in the fakeroot directory of the user's compiler environment.
 *   For example, on the CV5_Timn board, it is `ambarella/out/cv5_timn/fakeroot`.
 *   @code
 *   make -p $(FAKEROOT_DIR)/usr/lib/localelocaledef --prefix=$(FAKEROOT_DIR) --no-archive -c
 *        --little-endian -i zh_CN -f UTF-8 zh_CN.UTF-8
 *   @endcode
 *   Compile and burn the new firmware.
 *   Set Lang variables when the system is on, using the following command.
 *   @code
 *   export LANG=zh_CN.utf8 LANG=zh_CN.utf8
 *   @endcode
 *
 * @section faq_firmware_upgrade 15. Firmware Upgrade
 *
 * For kernel upgrade and rootfs upgrade, users can refer to @ref si_online_upgrading.<br>
 * If `boards/$BOARD/bsp/$BOARD.dts` file is changed,
 * then users must update the DTB file using the following command.
 * @code
 * upgrade_partition -d $BOARD.dts.dtb
 * @endcode
 * `$BOARD.dts.dtb` file is under the `out/$BOARD/amboot`.
 *
 * @section faq_mptool 16. MPtool
 *
 * As a testing tool, MPtool consists of two parts: the server on the product side and the client on the PC end.
 * There are two methods for connecting:  WiFi and USB virtual network card.
 * Ambarella recommends using a USB to ensure a more stable connection.<br>
 * Enable the server in "`make menuconfig`".
 * There is no relationship between the server implementation and Oryx middleware;
 * it is implemented by calling the interface in unit test and IAV.
 *
 * @section faq_how_to_patch 17. How to Patch
 *
 * Patch is used to improve the SDK package. Typically, package + patch is used.
 * The package + patch1 + patch2 is not supported.<br>
 * After installing a new patch, users must re-integrate changes in bsp\dts, customized applications,
 * and IQ related files when the board is brought-up.
 * Additionally, users must accurately backup
 * and manage IQ files to avoid negatively impacting the IQ performance after patch installation.
 *
 * @section faq_configuration_file 18. Configuration File
 *
 * @subsection faq_configuration_dts 18.1 DTS
 *
 * The following includes general information about device trees (DTS) files:
 *   - If users must modify the public portion of a chip, modify the file
 *     `arch\arm64\boot\dts\ambarella\ambarella-$SoC.dtsi`.
 *     For the CV5S66 chip, for example, modify the file
 *     `arch\arm64\boot\dts\ambarella\ambarella-cv5.dtsi`.
 *   - For external devices, users must modify the device tree file
 *     `ambarella\boards\$BOARD\bsp\$BOARD.dts`.
 *     For example, for CV5_Timn, modify `ambarella\boards\cv5_timn\bsp\cv5_timn.dts`
 *     and `ambarella\boards\cv5_timn\bsp\cv5_timn_private.dtsi`.
 *   - If users want to check how many device nodes exist when the system is running,
 *     they must first enable the device tree in the public Linux menuconfig.
 *     Then, check them in `proc\device-tree`.
 *     DTS works after the Linux kernel runs. The BST and AMBoot modes work before the kernel.
 *     Therefore, when there are changes in the hardware,
 *     users must check `ambarella/boards/$BOARD/bsp/bsp.h`.
 *     This file defines the initial state of each pin,
 *     the initial function of each pin, and each flash partition’s size.
 *     Incorrect bsp.h will cause the system to hang.
 * For detailed DTS information, refer to
 * `kernel\linux-5.15\documentation\devicetree\bindings\arm\ambarella.txt`.
 *
 * @subsection faq_configuration_ddr 18.2 DDR
 *
 * If users change the type of the DDR SDRAM or perform a shmoo test,
 * then they must check or change `ambarella/boards/$BOARD/$BOARD_$CPU.ini`.<br>
 * For example, for CV5S66, users must change
 * `ambarella/boards/cv5_timn/bsp/cv5_timn_66_micron_lpddr5.ini`.<br>
 * After running a shmoo test and receiving the correct DDR parameters,
 * users can then modify the file `ambarella/boards/$BOARD/bsp/$BOARD_$CPU.ini`.<br>
 * For example, for cv5_timn, modify: `ambarella/boards/cv5_timn/bsp/cv5_timn_66_micron_lpddr5.ini`.
 *
 * @subsection faq_configuration_menuconfig 18.3 Menuconfig
 *
 * The default configuration file for "make menuconfig", is
 * `ambarella/boards/$BOARD/config/$BOARD_config`.<br>
 * To change the configuration in CV5 Timn, modify:
 * `ambarella/boards/cv5_timn/bsp/cv5_ipcam_config`.<br>
 * While using make menuconfig_public_linux, the default kernel configuration file is typically
 * `ambarella/boards/$BOARD/config/kernel/$BOARD_kernel_config`.<br>
 * Alternatively, for example, use `/linux-5.15/arch/arm64/configs/ambarella_cv5_defconfig`.
 *
 * @subsection faq_configuration_cvflow_issues 18.4 CVflow® Issues
 *
 * For issues concerning CVflow, refer to the document `Ambarella CV5x DG Flexible Linux SDK CVflow FAQ`.
 *
 * @section faq_emmc_usage 19. eMMC Usage
 *
 * To use embedded multi-media controller (eMMC) on the EVK, a hardware rework may be required.
 * Refer to @ref si_sd_upgrading.
 * Additionally, @ref notitle provides information on software configuration and flash upgrading.
 *
 * @section faq_cma_for_iav_cv_memory_partitions 20. CMA for IAV / CV Memory Partitions
 *
 * For instructions on how to use the contiguous memory allocator (CMA) for IAV / CV memory partitions,
 * refer to the document Ambarella `CV5x DG Flexible Linux SDK CMA Driver`.
 * Users are recommended to specify the size of the IAV / CV CMA partitions
 * according to their requirements with less margin and leave more system memory for the Linux partition.<br>
 * Although the unused memory resource left in the CMA partition can be reused by the Linux system,
 * it is easy to trigger the out of memory (OOM) killer when the Linux system starts to allocate
 * from the CMA partition and this is a limitation of the CMA.  For details on this limitation,
 * refer to `Ambarella CV5x DG Flexible Linux SDK CMA Driver`.
 *
 */
