/*! @file doc_drv_cavalry.h
 * @brief This file defines the doxygen structure of cavalry ioctl api.
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
/*! @page page_drv_cavalry_doc Cavalry V3 (CV72) Driver API
 *
 * @section cavalry_history 0. Revision History
 *
 * <table>
 * <caption id="drv_cavalry_rev_history"></caption>
 * <tr><th> Updated Date          <th align="left"> Modification
 * <tr><td> 20230424              <td> Initial Version for CV72
 * </table>
 *
 * - - - -
 *
 * @section cavalry_intro 1. Introduction
 *
 *
 * The Cavalry device driver for the CV7x vector processor (VP) includes a set of Linux device
 * drivers that encapsulate the lower-level complexities of the CV7x's VP functionalities.
 * The drivers conform to the standard Linux driver model, exposing a series of APIs that
 * can be invoked by IOCTL() system calls.
 * These APIs are used by applications to configure and control the CV7x's VP in detail.
 * Prototypes for the APIs and structures can be found in cavalry_ioctl.h in each SDK package.
 * However, if there are any conflicts between the header files and this document, refer to the source code.
 *
 * - - - -
 *
 * @section cavalry_usage 2. Cavalry Usage
 *
 * Follow these commands to build the Cavalry driver and Cavalry related unit test:
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Linux Configuration  --->
 *              [*]   Build Ambarella nerual network control library  --->
 *                 [*]   Build Ambarella Cavalry Driver
 *
 *          [*] Ambarella Unit Test Configuration	--->
 *              [*]	 Ambarella Private Linux Unit test configs	--->
 *                 [*]   Build CV unit tests
 * @endcode
 *
 * @subsection cavalry_usage_load_ucode 2.1 cavalry_load
 * Before running directed acyclic graph (DAGs) on the Cavalry driver, the VP microcode must be properly loaded.
 * To facilitate this task, cavalry_load should be called after the system boots up.
 * The CV7x VP microcode file name is cavalry.bin.  The following example assumes
 * that the VP ucode files are located under the directory `/lib/firmware`.
 * The full path of the VP microcode is an argument of the cavalry_load program.
 * After loading, the ucode version message will display on the standard output.
 * @code {.c}
 * board # modprobe cavalry
 * board # ls -l /dev/cavalry
 * crw-rw-rw-    1 root     root      249,   0 Aug 19 23:28 /dev/cavalry
 * board # cavalry_load -f /lib/firmware/cavalry.bin
 * Cavalry Ucode Version = CV72-Ver.126-20230419-ef006a44-hl_fw.00000001
 * @endcode
 *
 * @subsection cavalry_usage_clock 2.2 cavalry_clock
 *
 * * After system boots up, VP clock is set as the max value according to chip specifications.
 * The following command will use insightface network as reference.
 * @code {.c}
 * board # cat /proc/ambarella/clock | grep gclk_nvp
 *       gclk_nvp:    1008000000 Hz
 * board # test_nnctrl -b insightface_cavalry.bin --in data -e
 * Net_id: 0, Dags: 21 / 21, vp_ticks: 301073, vp_time: 24501 us, arm_time: 24585 us
 * @endcode
 *
 * * Users can lower the VP clock to save power when the VP performance is sufficient.
 * cavalry_load enables user to slower down VP clock by providing percentage of maximum value.
 * For Example, slower down VP clock to 50% of maximum value.
 * @code {.c}
 * board # cavalry_load --vp-clk 1/2
 *   Configure VP Clock Percentage: 504/1008
 * board # cat /proc/ambarella/clock | grep gclk_nvp
 *       gclk_nvp:    504000000 Hz
 * board # test_nnctrl -b insightface_cavalry.bin --in data -e
 * Net_id: 0, Dags: 21 / 21, vp_ticks: 589749, vp_time: 47993 us, arm_time: 48089 us
 * @endcode
 *
 * * Recover VP clock to the maximum value.
 * @code {.c}
 * board # cavalry_load --vp-clk 1/1
 * Configure VP Clock Percentage: 1008/1008
 * board # cat /proc/ambarella/clock | grep gclk_nvp
 *       gclk_nvp:    1008000000 Hz
 * @endcode
 *
 * * Stop Cavalry and VP clock will stop all VP resource.
 * @code {.c}
 * board # cavalry_load --stop-vp
 * Configure VP Clock Percentage: 1008/1008
 * board # cat /proc/ambarella/clock | grep gclk_nvp
 *       gclk_nvp:    0 Hz
 * @endcode
 *
 * @subsection cavalry_usage_ucode_log 2.3 cavalry_log
 * If an error occurs, use cavalry_log to debug.  It supports a live show log when the ucode is running.
 * Because it generates many messages, it is recommended to run on Telnet console for this command.
 * @code {.c}
 * board # cavalry_log -u /lib/firmware/cavalry.bin -l -d 4
 * Cavalry Ucode Version = CV72-Ver.126-20230419-ef006a44-hl_fw.00000001
 * [T 4 C 0 t 0   :1] Cavalry ucode is started.
 * [T 4 C 0 t 0   :2] ARM CMD Q Addr 0x00000000|58200000, size 0x8000.
 * [T 4 C 0 t 0   :3] ARM MSG Q Addr 0x00000000|58208000, size 0x8000.
 * [T 4 C 0 t 0   :4] IDSP CMD Q Addr 0x00000000|58210000, size 0x8000.
 * [T 4 C 0 t 0   :5] IDSP MSG Q Addr 0x00000000|58218000, size 0x8000.
 * [T 4 C 0 t 0   :6] LOG Q Addr 0x00000000|58220000, size 0x20000, Log Level 2.
 * [T 4 C 0 t 0   :7] PROFILE Q Addr 0x00000000|58240000, size 0x20000.
 * [T 4 C 0 t 0   :8] STATS INFO Addr 0x00000000|58260000, size 0x20.
 * [T 4 C 0 t 0   :9] Receive INT from ARM.
 * [T 5 C 0 t 1   :10] Processing SET_LOG_LEVEL_CMD.
 * [T 5 C 0 t 1   :11] Changed log level from [2] to [4].
 * @endcode
 *
 * @subsection cavalry_usage_top 2.4 cavalry_top
 * Users can use the Cavalry top tool to check the VP usage statistics.  It is like tool top in Linux
 * to summary system resource information as well as a list of processes and CPU usage.
 * @code {.c}
 * board # cavalry_top
 * -------------
 * PID    NID    NVP0
 * 527    0     097.1   test_nnctrl -b insightface_cavalry.bin --in data --out fc1_scale -e -t 1000
 * -------------
 * 0: NVP0  IDLE 002.7%
 * @endcode
 *
 * - - - -
 *
 * @section cavalry_debug 3. Cavalry Debug
 * The software development kit (SDK) supplies several tools to address problems when the error occurs.
 *
 * @subsection cavalry_debug_core_dump 3.1 cavalry_core_dump
 * cavalry_core_dump is used to dump cavalry related context into one binary when encountering VP hang,
 * and users can reproduce the VP hang issue by this dumped binary.
 * @code {.c}
 * 1. Kernel dmesg will report the following message when encountering VP hang. After that, users can use
 * tool to dump binary.
 *
 * kthread_vp_core_dump_monitor(64): VP Seems Hang
 * board # cavalry_core_dump -d /tmp/cavalry_core_dump.bin
 * VP hang detected.
 * VP Core dump saved.
 *
 * 2. Users have to reload cavalry driver after VP hang.
 * board # rmmod cavalry; modprobe cavalry; cavalry_load -f /lib/firmware/cavalry.bin
 *
 * 3. Reproduce VP hang by dumped bianry.
 * board # cavalry_core_dump -r /tmp/cavalry_core_dump.bin
 * kthread_vp_core_dump_monitor(64): VP Seems Hang
 * @endcode
 *
 * @subsection cavalry_debug_vpstatus 3.2 vpstatus
 * vpstatus is used to dump VP register releated context into an binary when encountering a VP hang.
 * Follow these commands to build the vpstatus tool.
 * @code {.c}
 * build # make menuconfig
 *          [*] Ambarella Unit Test Configuration	--->
 *              [*]	 Ambarella Private Linux Unit test configs	--->
 *                 [*]   Build CV unit tests	--->
 *                    [*]   Build VPUtils unit tests
 * @endcode
 *
 * Same as cavalry_core_dump, users can dump one binary when encountering a VP hang.
 *
 * @note
 * Only execute vpstatus dump binary once, the second command is invalid after dumped already.
 *
 * @code {.c}
 * board # vpstatus -d /tmp/vpstatus_dump.bin
 * cycles = 0xffffffff
 * VP hang detected!
 * @endcode
 *
 * @subsection cavalry_debug_monitor 3.3 cavalry_monitor
 * cavalry_monitor tool can receive error event that Cavalry driver reported,
 * and use cavalry_core_dump and vpstatus tools to dump the corresponding binary automatically.
 * So it is easy for user to dump the information without to execute cavalry_core_dump and vpstatus by manually.
 *
 * Users can send these two binaries (such as "cavalry_core_dump.bin" and "vpstatus_dump.bin" in the following command)
 * to the Ambarella support team for assistance.
 * @code {.c}
 * board # cavalry_monitor -c /tmp/cavalry_core_dump.bin -v /tmp/vpstatus_dump.bin
 * No INFO MSG
 * No ERR MSG
 * Polled ERR
 * [2020-08-20 22:31:59 185.158] Receive ERR: VP_Hang, at func: kthread_vp_core_dump_monitor:(127)
 * VP hang detected.
 * VP Core dump saved.
 * cycles = 0xffffffff
 * VP hang detected!
 * @endcode
 *
 * - - - -
 *
 * @section sec_cavalry_api 4. Cavalry API
 *
 * Visit the following link to see details of the API functions
 *     - @ref cavalry-ioctl-api shows API lists
 *     - @ref cavalry-ioctl-helper shows related macros enumerations and structures
 *
 * - - - -
 *
 * @section cavalry_license 5. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

/*!
* @example cavalry_load.c
* This is a source code file of cavalry_load.
*/

/*!
* @example cavalry_log.c
* This is a source code file of cavalry_load.
*/

/*!
* @example cavalry_top.c
* This is a source code file of cavalry_top.
*/

/*!
* @example vpstatus.c
* This is a source code file of vpstatus.
*/

/*!
* @example cavalry_core_dump.c
* This is a source code file of cavalry_core_dump.
*/

/*!
* @example cavalry_monitor.c
* This is a source code file of cavalry_monitor.
*/


/*!
* @defgroup cavalry-api Cavalry IOCTL API
* @brief Cavalry IOCTL API, in file cavalry_ioctl.h
*/
/*! @defgroup cavalry-ioctl-api Cavalry IOCTL API details
* @ingroup cavalry-api
* @brief Cavalry IOCTL API, in file cavalry_ioctl.h
*/
/*! @defgroup cavalry-ioctl-helper Cavalry IOCTL Helper
* @ingroup cavalry-api
* @brief Cavalry IOCTL API Structs, Enumerations and Macros, in file cavalry_ioctl.h
*/

/*! @file doc_drv_cma.h
 * @brief This file defines the doxygen structure of cma driver.
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
/*! @page page_drv_cma_doc CMA Driver API
 *
 * @section cma_driver_history 0. Revision History
 *
 * <table>
 * <caption id="drv_cma_rev_history"></caption>
 * <tr><th> SDK Version       <th> Updated Date         <th> Modification
 * <tr><td> 0.2               <td> 20211021             <td> Initial Version
 * <tr><td rowspan="7"> 0.5   <td rowspan="7"> 20220114 <td> Added Section @ref cma_layout_intr "1. Memory Layout Introduction".
 * <tr>                                                 <td> Updated Section @ref sec_specify_cma_partion.
 * <tr>                                                 <td> Added Section @ref sub_sec_enable.
 * <tr>                                                 <td> Added Section @ref sec_driver_private_share.
 * <tr>                                                 <td> Updated Section @ref sec_dump_mmb_info.
 * <tr>                                                 <td> Updated Section @ref sub_sec_mod_conf.
 * <tr>                                                 <td> Updated Chapter @ref sub_sec_conf_mod_para.
 * <tr><td> 1.0               <td> 20220718             <td> Migrated this CMA driver document from WORD form into Doxygen form.
 * </table>
 *
 * - - - -
 *
 * @section cma_layout_intr 1. Memory Layout Introduction
 * The Ambarella Cooper platforms support 4-GB, 8-GB, 16-GB, and larger dynamic
 * random-access memory (DRAM) sizes. The chip series targets 8Kp30+ or 4x4K processing,
 * requiring large DRAM bandwidth as well as high resolution Image signal processor (ISP)
 * and encoding processing.
 *
 * According to real-case usage requirements, Ambarella divides the system memory
 * into the following three categories through the continuous memory allocator (CMA).
 *   - DSP private memory partition
 *      - <b>"DSP + Arm®"</b> access only: computer vision (CV) cannot read or write the memory
 * in this partition.
 *   - CV private memory partition
 *      - <b>"Arm + CV"</b> access only: DSP cannot read or write the memory in this partition.
 *   - DSP and CV shared memory partition
 *      - The memory in this partition can be accessed by <b>"DSP + CV + Arm"</b>, which means
 * DSP, CV, and Arm can access the memory in this partition. Currently, the DSP and CV shared
 * memory partition is not yet supported for use.
 *
 * For the Cooper platforms, Arm has been upgraded in order to access DRAM with a 40-bit
 * address bitwidth, which exceeds the minimum to access the entire DRAM. However, for CV5x,
 * the DRAM access address bitwidth DSP and CV remains 32 bits; as a result, of the both can only
 * access 4-GB of memory space. To address this, different memory layouts will be made for 4-GB
 * and 8-GB DRAM accordingly. For CV72, CV can access the entire DRAM, while DSP still can only
 * access 32-bit DRAM. Currently, the memory layout for CV72 shares the same as CV5x. However,
 * it is possible to put CV private memory partition in any address inside the whole DRAM.
 *
 * @subsection cma_4g_layout 1.1 4-GB Memory Layout
 *
 * The total 4-GB DRAM size can be accessed by <b>"Arm + CV + DSP"</b>. The figure below shows
 * the system memory layout for 4-GB DRAM size, which is applied to the <b>"CV52 Zr"</b> platform.
 *
 * @image html 4g_layout.jpg "Figure 1-1. 4-GB DRAM System Memory Layout."
 *
 * - - - -
 *
 * @subsection cma_8g_layout 1.2 8-GB Memory Layout
 *
 * Because the DRAM access address bitwidth of both DSP and CV are 32 bits, they
 * are unable to directly access the memory beyond the 4G boundary. To enable
 * them to have their own 4 GB memory space, the CV5x / CV7x platform utilizes the address
 * translation table (ATT) mapping for "DSP Memory Space" (both "DSP Private Pool"
 * and "DSP & VP Shared Pool"), while CV, "CV Private Pool", and "DSP & VP Shared Pool"
 * continue using the default DRAM memory space (as they are both within 4 GB).
 *
 * The ATT process for "DSP Memory Space" is separated into the following two steps.
 *     1. While performing ATT mapping, "DSP Private Pool" is mapped from 0, which means its
 * offset in the ATT memory space will be the same with the lower u32 of its DRAM physical
 * address. For example, if the DRAM physical address is 0x1, 0010, 0000, then the offset
 * in the ATT memory space will be 0x0010, 0000.
 *     2. Map "DSP & VP Shared Pool" to the end of the 4-GB ATT memory space, which means that
 * its offset in the ATT memory space will be the same as its DRAM physical address.
 * For example, if the DRAM physical address is 0xFF10, 0000, then its offset in the
 * ATT memory space will also be 0xFF10, 0000.
 *
 * Consequently, the memory layout of the 8-GB DRAM size is designed as shown below.
 *
 * @image html 8g_layout.jpg "Figure 1-2. 8-GB DRAM System Memory Layout."
 *
 * The table below shows the DRAM access limitation for Arm, CV, and DSP respectively.
 *
 * @par 8-GB DRAM Access Limitation for Arm, CV, and DSP
 * <table>
 * <caption id="cma_table_8g_limit"></caption>
 * <tr><th> Element      <th> DRAM Access Limitation
 * <tr><td> Arm          <td> 0~8 GB
 * <tr><td> CV           <td> 0~4 GB
 * <tr><td> DSP          <td> DSP memory space
 * </table>
 *
 * - - - -
 *
 * @section cma_memory 2. Memory Management of IAV / DSP Partitions
 * This chapter provides an introduction of memory management for the IAV / DSP partitions:
 * CMA memory management.
 *
 * According to the @a Flexible @a Linux @a SDK @a Design @a Guide
 * @a - @a DRAM @a Optimization document,  the DRAM system consists of four partitions:
 * Linux, image audio video (IAV), DSP, and CV partitions.  The CMA Linux kernel feature
 * supports allocating large, physically contiguous memory blocks at runtime. This feature
 * is used for the allocation of the IAV, DSP, and CV partitions, enabling the partition
 * sizes to be resized during runtime.  Once the CMA method is applied, the DRAM can be
 * separated into two partitions, the Linux and CMA partitions (see below), from which the
 * IAV, DSP, and CV partitions are allocated. This method is called CMA memory management.
 *
 * @image html CMA_memory_management.jpg "Figure 2-1. CMA Memory Management."
 *
 * @subsection reserved_memory_management 2.1 Reserved Memory Management
 * Using the CMA memory management method, IAV / DSP / CV partitions can
 * be allocated / freed from the CMA partition during runtime. Ambarella
 * recommends that users closely specify the size of the CMA partition
 * according to their requirements, and allocate more of the available
 * memory resources to the Linux partition.
 *
 * @note
 * Although the Linux system can reuse the remaining memory in the CMA partition,
 * be aware that it can potentially trigger the out of memory (OOM)-killer,
 * which is the result of a CMA limitation. For more information on the CMA limitations,
 * refer to Chapter @ref cma_faq "5. FAQ".
 *
 * Choose CMA memory management through menuconfig, as follows.
 * @par For CV2x SDK 3.0 Amba build
 * @code {.c}
 * build $ make menuconfig
 * 	Memory  --->
 * 		IAV/DSP Memory (Linux CMA)  --->
 * 		[ ] CV memory from Reserved memory
 * @endcode
 * @par For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 * 	 -*- board (boards)  --->
 *     Memory  --->
 * 		 IAV/DSP Memory (Linux CMA)  --->
 * 		 [ ] CV memory from Reserved memory
 * @endcode
 * @par For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 * 	 meta-ambabsp --->
 *     recipes-bsp --->
 *       -*- board (meta-ambabsp/recipes-bsp/board)  --->
 *           Memory  --->
 * 		        IAV/DSP Memory (Linux CMA)  --->
 * 		        [ ] CV memory from Reserved memory
 * @endcode
 *
 * The CMA partition consists of two separate CMA memory pools: one
 * for the IAV and DSP partitions; the other for the CV partition only.
 * The start address of each CMA memory pool is configured through menuconfig.
 *
 * @note
 *   - As a Linux system requirement of the CMA, the start address and size must be
 *     <b>4 MB aligned</b>.
 *
 * For example, on the CV5 Timn board, users can issue the following commands
 * to set the size of the CMA memory pool for the IAV and DSP partitions to 2816
 * MB and to set the size of CMA memory pool for the CV partition to 512 MB:
 * @par For CV2x SDK 3.0 Amba build
 * @code {.c}
 * build $ make menuconfig
 * 	 Memory  --->
 * 		 (2816) DSP Private Memory size in MB
 * 		 (16) DSP Shared Memory size in MB
 * 		 (512) CV Private Memory size in MB
 * @endcode
 * @par For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 * 	 -*- board (boards)  --->
 *     Memory  --->
 * 		       (2816) DSP Private Memory size in MB
 * 		       (16) DSP Shared Memory size in MB
 * 		       (512) CV Private Memory size in MB
 * @par For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 * 	 meta-ambabsp --->
 *     recipes-bsp --->
 *       -*- board (meta-ambabsp/recipes-bsp/board)  --->
 *           Memory  --->
 * 		       (2816) DSP Private Memory size in MB
 * 		       (16) DSP Shared Memory size in MB
 * 		       (512) CV Private Memory size in MB
 * @endcode
 *
 * Within the CMA memory pool for the IAV and DSP partitions, users can subdivide
 * the DSP partition through menuconfig as shown below. The remainder of the partition
 * is for IAV. For this configuration, the size of the DSP partition is 2560 MB and
 * the size of the IAV partition is 256 MB.
 * @par For CV2x SDK 3.0 Amba build
 * @code {.c}
 * build $ make menuconfig
 *  [*] Ambarella Linux Configuration ->
 *        [*]   Ambarella Private Drivers Configuration  --->
 *          [*]   Build Ambarella private IAV module  --->
 *                  IAV memory options  --->
 *            		  (0xA0000000) DSP buffer size
 * @endcode
 * @par For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *            		  (0xA0000000) DSP buffer size
 * @endcode
 * @par For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 * 	 meta-ambabsp --->
 *     recipes-video  --->
 *       -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)  --->
 *            		  (0xA0000000) DSP buffer size
 * @endcode
 *
 * The configuration options are the same for CV5x and CV7x.
 *
 * - - - -
 *
 * @section cma_driver 3. CMA Driver
 *
 * This chapter describes the operations and functions of the CMA driver in Cooper platform.
 *
 * This chapter includes the following sections:
 *
 * <ul>
 * <li> Section @ref sec_ambarella_cma_driver
 * <li> Section @ref sec_specify_cma_partion
 * <li> Section @ref sec_memory_mangement_block
 * <li> Section @ref sec_pre_allocate_mmbs
 * <li> Section @ref sec_driver_module_parameters
 * <li> Section @ref sec_dump_mmb_info
 * <li> Section @ref sec_private_mem_allocator
 * </ul>
 *
 * @subsection sec_ambarella_cma_driver 3.1 Ambarella CMA Driver
 *
 * In order to effectively manage the entire CMA partition while also serving various
 * types of module drivers (such as IAV, DSP, and imgproc), the kernel CMA’s application
 * programming interfaces (APIs) are wrapped into Ambarella’s CMA driver, then exported
 * to a group of APIs for the module drivers.
 *
 * These APIs cover general functions, such as memory block allocation / free,
 * memory block information queries, memory block mapping, and more.
 *
 * @image html CMA_diagram.jpg "Figure 3-1. Diagram of Ambarella CMA Driver and Other Module Drivers."
 *
 * @note
 * Currently, only the CMA memory pool for IAV / DSP partitions is managed by the
 * Ambarella CMA driver. While the CMA memory pool is used for CV partitions,
 * it is managed by the Ambarella Cavalry driver. For more details, refer to the
 * @a Flexible @a Linux @a SDK @a Design @a Guide @a Cavalry @a Driver document.
 *
 * - - - -
 *
 * @subsection sec_specify_cma_partion 3.2 Specifying CMA Partitions through Device Trees
 *
 * As Section @ref cma_layout_intr "1. Memory Layout Introduction" described,
 * Ambarella divides the system memory into "DSP Private Memory Pool", "CV
 * Private Memory Pool", and "DSP & CV Shared Memory Pool" through CMA.
 *
 * Users can configure the size for the CMA pools listed above through menuconfig.
 * @par For Cooper Amba build:
 * @code {.c}
 * build # make menuconfig
 * 	 -*- board (boards)  --->
 *     Memory  --->
 *      (2816) DSP Private Memory size in MB
 *      (16) DSP Shared Memory size in MB
 *      (512) CV Private Memory size in MB
 *      (0) CV Shared Memory size in MB
 * @endcode
 * @par For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 * 	 meta-ambabsp --->
 *     recipes-bsp --->
 *       -*- board (meta-ambabsp/recipes-bsp/board)  --->
 *           Memory  --->
 *              (2816) DSP Private Memory size in MB
 *              (16) DSP Shared Memory size in MB
 *              (512) CV Private Memory size in MB
 *              (0) CV Shared Memory size in MB
 * After menuconfig is done, it will finally be applied to the device tree (DTS) automatically,
 * which decides the size of the CMA pools. So users do not have to modify the DTS manually.
 * For user's reference, the CMA pool related parts in the DTS are listed below, which uses the
 * CV5 Timn board as an example,
 *
 * @par CMA Memory Partition Related DTS Nodes
 * <table>
 * <caption id="cma_table_dts_node"></caption>
 * <tr><th> DTS Nodes      <th> Description
 * <tr><td> iav_reserved: iav@0          <td> "Arm + DSP" access only memory partition
 * <tr><td> iav_shared: iav@1            <td> "DSP + CV + Arm" shared memory partition
 * <tr><td> cavalry_reserved: cavalry@0  <td> "Arm + CV" access only memory partition
 * <tr><td> cavalry_shared: cavalry@1    <td> "DSP + CV + Arm" shared memory partition
 * </table>
 *
 * @code {.c}
 * a/bsp/CV5_timn_private.dtsi
 * #include <arch_v6/plat_memory.h>
 *
 * / {
 * 	reserved-memory {
 * 		#address-cells = <2>;
 * 		#size-cells = <2>;
 * 		ranges;
 *
 * 		linux,cma {
 * 			compatible = "shared-dma-pool";
 * 			reusable;
 * 			size = <0 0x04000000>;
 * 			linux,cma-default;
 * 		};
 *
 * 		iav_reserved: iav@0 {
 * 			compatible = "shared-dma-pool";
 * 			no-map;
 * 			reg = <(IDSP_RAM_START >> 32) (IDSP_RAM_START&0xFFFFFFFF) 0x0 IDSP_PRIVATE_SIZE>;
 * 		};
 *
 * 		iav_shared: iav@1 {
 * 			compatible = "shared-dma-pool";
 * 			no-map;
 * #if (IDSP_SHARED_SIZE > 0)
 * 			reg = <(IDSP_SHARED_START >> 32) (IDSP_SHARED_START&0xFFFFFFFF) 0x0 IDSP_SHARED_SIZE>;
 * #endif
 * 		};
 *
 * 		cavalry_reserved: cavalry@0 {
 * 			compatible = "shared-dma-pool";
 * 			no-map;
 * 			reg = <(CV_RAM_START >> 32) (CV_RAM_START&0xFFFFFFFF) 0x0 CV_PRIVATE_SIZE>;
 * 		};
 *
 * 		cavalry_shared: cavalry@1 {
 * 			compatible = "shared-dma-pool";
 * 			no-map;
 * #if (CV_SHARED_SIZE > 0)
 * 			reg = <(CV_SHARED_START >> 32) (CV_SHARED_START&0xFFFFFFFF) 0x0 CV_SHARED_SIZE>;
 * #endif
 * 		};
 * 	};
 *
 * 	iav {
 * 		// node for hwtimer controller
 * 		hwtimer {
 * 			compatible = "ambarella,hwtimer";
 * 			interrupts = <0 25 0x1>;
 * 			interrupt-names = "hwtimer";
 * 		};
 *
 * 		ambcma {
 * 			compatible = "ambarella,cma";
 * 			memory-region = <&iav_reserved>;
 * 			shared-region = <&iav_shared>;
 * 			dsp_buf_size = <0x20000000>;
 * 		};
 * 	};
 *
 * 	sub_scheduler: sub_scheduler0 {
 * 		compatible = "ambarella,sub-scheduler";
 * 		interrupts = <0 169 0x4>, <0 170 0x4>, <0 171 0x4>, <0 172 0x4>, <0 173 0x4>;
 * 		memory-region = <&cavalry_reserved>;
 * 		shared-region = <&cavalry_shared>;
 * 	};
 *
 * #if (DRAM_SIZE > (4 * SIZE_GB))
 * 	att-regmap {
 * 		compatible = "ambarella,att-regmap";
 * 		amb,att-debug;
 * 		dram-size = <(DRAM_SIZE >> 32) (DRAM_SIZE&0xFFFFFFFF)>;
 * 		client-bitmap = <0x006F8000>;
 * 		// <virt-addr phys-addr size>
 * 		segment-regmap =
 * #if (CV_SHARED_START < (4 * SIZE_GB))
 * 			<0 CV_SHARED_START 0 CV_SHARED_START 0 (CV_SHARED_SIZE + IDSP_SHARED_SIZE)>,
 * #endif
 * 			<0 0 (IDSP_RAM_START >> 32) (IDSP_RAM_START&0xFFFFFFFF) 0 IDSP_PRIVATE_SIZE>;
 * 	};
 * #endif
 * };
 * @endcode
 *
 * - - - -
 *
 * @subsection sec_memory_mangement_block 3.3 Memory Management Block
 *
 * Each IAV / DSP sub-partition in the CMA driver, such as the bitstream buffer (BSB) partition,
 * user buffer partition, overlay buffer partition, and others are abstracted into a memory
 * management block (MMB). Additionally, each IAV / DSP sub-partition corresponds to only one
 * MMB. All MMBs are created and maintained in the CMA driver. Other module drivers perform MMB
 * allocation / free, memory mapping, and MMB information queries through the APIs exported by
 * Ambarella’s CMA driver.
 *
 * @subsubsection sub_sec_anon 3.3.1 Anonymous MMB
 *
 * In addition to the specified IAV / DSP sub-partitions, users
 * may require their own continuous memory partitions.
 *
 * To meet these requirements, the CMA driver utilizes an anonymous MMB.
 * After an anonymous MMB is allocated, the CMA driver assigns it a random memory
 * partition ID instead of a fixed memory partition ID (such as IAV_PART_BSB
 * for the BSB).
 *
 * Additionally, user applications can perform data analysis on the anonymous MMBs.
 * In order to shorten the analysis time, the Arm data cache can be enabled for the anonymous
 * MMBs when they are mapped to the user memory space.
 *
 * @subsubsection sub_sec_custom 3.3.2 User-Customized MMB
 *
 * For certain use cases, users may be required to create a continuous memory partition
 * with a customized and fixed partition ID. The CMA driver enables a user-customized MMB.
 * When using customized MMBs, applications or other module drivers can specify the custom
 * partition IDs when allocating these MMBs. Currently, the selected range of user-customized
 * partition IDs ranges from 192 to 254 (inclusive).
 *
 * @note
 * User applications can also enable the Arm data cache for customized
 * MMBs that are mapped from the user memory space.
 *
 * @subsubsection sub_sec_enable 3.3.3 Enabling and Synchronizing the Cache for MMBs
 *
 * Cache is a high-speed buffer between the CPU and DRAM to address the condition of data
 * read / write speed mismatch in the system. Ambarella CMA framework supports enabling the
 * cache for specified MMBs. For more details on cached MMBs, refer to @ref specify_cache_mmbs.
 *
 * In a multi-core system, the following two factors may cause the cache inconsistency
 * issue that leads the CPU or input / output (I/O) devices to read the wrong data.
 *   - As the CPU writes data to the cache, the contents change. However, as DRAM is not written
 * immediately, the DRAM data is not changed.
 *   - The I/O processor or I/O device writes data to the main memory. The
 * contents of DRAM are modified, but the contents of cache are not.
 *
 * To solve the condition of incorrect data reading caused by a cache inconsistency,
 * Ambarella provides two APIs, as seen below.
 *   - <b>ambarella_cma_clean_cache</b>: checks the dirty bit of the memory cache line. If the dirty
 * bit is 1, write the contents of the cache line back to the next-level storage and set the dirty bit to 0.
 *   - <b>ambarella_cma_invalidate_cache</b>: checks the valid bit of the memory cache line.
 * If the valid bit is 1, set it to 0 to discard the cached contents
 *
 * The combination of <b>"clean cache"</b> and <b>"invalidate cache"</b> operations above is called the
 * <b>"flush cache"</b> process. Users can decide which operation should be executed according
 * to the direction of data access.  The detailed usages are listed below:
 *   - If the CPU writes data to DRAM first, and then DMA or other devices access DRAM,
 *     users must execute <b>clean cache</b> first to ensure that the DMA or other devices
 *     access DRAM accurately.
 *   - If the CPU reads DRAM first, DMA or other devices are not required to execute <b>clean cache</b>
 *     before accessing it. Once DMA or other devices re-write the DRAM, users must
 *     execute <b>invalidate cache</b>. This enables the CPU to read the data from DRAM directly,
 *     rather than the data in the cache.
 *   - If both CPU and DMA access a block of DRAM concurrently, Ambarella recommends that users execute a
 *     <b>"flush cache"</b> before reading / writing such a block of DRAM to avoid cache inconsistency issues.
 *
 * - - - -
 *
 * @subsection sec_pre_allocate_mmbs 3.4 Pre-Allocated MMBs
 *
 * The sizes of most IAV / DSP sub-partitions do not require modification after they are specified
 * through the compiled configuration or module parameters of the Ambarella CMA driver.
 * Users should merge them into a large contiguous area, referred to as the
 * pre-allocated MMB, as this will be the first sub-partition allocated at the
 * beginning of the partition.
 *
 * Only the IAV / DSP sub-partitions whose sizes will be modified during
 * runtime are allocated in the left CMA partition, resulting in less memory
 * fragmentation. The first table provided below illustrates the list
 * of IAV / DSP sub-partitions that can be placed into the pre-allocated MMB.
 *
 * Because the size of the IAV / DSP sub-partitions placed into the pre-allocated MMB cannot
 * be changed on the fly, particular sub-partitions (such as the DSP FIFO buffer and the
 * blend alpha buffer) cannot be placed into the pre-allocated MMB. This is because their
 * sizes will be dynamically changed in the IAV / DSP driver. The second table in this section
 * provides the list of IAV / DSP sub-partitions that cannot be added into the pre-allocated MMB.
 * The following figure illustrates the pre-allocated and resizable MMBs.
 *
 * @image html pre_allocated_MMBS.jpg "Figure 3-2. Diagram of Pre-Allocated MMB and Resizable MMBs."
 *
 * @par Diagram of Pre-Allocated MMB and Resizable MMBs
 * <table>
 * <caption id="sub_partitions_supported_mmbs"></caption>
 * <tr><th> IAV / DSP Sub-partition   <th>State
 * <tr><td> IAV_PART_DSP              <td> <B>Compulsory</B>
 * <tr><td> IAV_PART_DSP_DEF_CMD      <td> <B>Compulsory</B>
 * <tr><td> IAV_PART_DSP_LOG          <td> <B>Compulsory</B>
 * <tr><td> IAV_PART_IMG              <td> <B>Compulsory</B>
 * <tr><td> IAV_PART_BSH              <td> <B>Compulsory</B>
 * <tr><td> IAV_PART_DSP_UCODE        <td> <B>Compulsory</B>
 * <tr><td> IAV_PART_DSP_RSV          <td> <B>Compulsory</B>
 * <tr><td> IAV_PART_IAV_RSV          <td> <B>Compulsory</B>
 * <tr><td> IAV_PART_BSB              <td> Selective
 * <tr><td> IAV_PART_USR              <td> Selective
 * <tr><td> IAV_PART_MV               <td> Selective
 * <tr><td> IAV_PART_OVERLAY          <td> Selective
 * <tr><td> IAV_PART_QPMATRIX         <td> Selective
 * <tr><td> IAV_PART_QPMATRIX_RAW     <td> Selective
 * <tr><td> IAV_PART_WARP             <td> Selective
 * <tr><td> IAV_PART_QUANT            <td> Selective
 * <tr><td> IAV_PART_MASK             <td> Selective
 * <tr><td> IAV_PART_FB_DATA          <td> Selective
 * <tr><td> IAV_PART_FB_AUDIO         <td> Selective
 * <tr><td> IAV_PART_INTRA_PB         <td> Selective
 * <tr><td> IAV_PART_STAT             <td> Selective
 * <tr><td> IAV_PART_PREALLOC         <td> Selective
 * <tr><td> IAV_PART_PREALLOC2        <td> Selective
 * <tr><td> IAV_PART_QPMATRIX_RAW     <td> Selective
 * <tr><td> IAV_PART_CANVAS_POOL      <td> Selective
 * <tr><td> IAV_PART_BLUR             <td> Selective
 * <tr><td> IAV_PART_HEVC_SCALELIST   <td> Selective
 * <tr><td> IAV_PART_MULTI_COLOR_MASK <td> Selective
 * <tr><td> IAV_PART_INT_BSB          <td> Selective
 * <tr><td> IAV_PART_ARB_BLUR         <td> Selective
 * <tr><td> IAV_PART_EXTRA_RAW        <td> Selective
 * <tr><td> IAV_PART_TFC              <td> Selective
 * </table>
 *
 * @par IAV / DSP Sub-Partitions that Cannot be Supported in Pre-Allocated MMBs
 * <table>
 * <caption id="cannot_supported_pre-allocated_mmbs"></caption>
 * <tr><th> IAV / DSP Sub-partition <th>State
 * <tr><td> AV_PART_BLEND_ALPHA     <td> Not Permitted
 * <tr><td> IAV_PART_DSP_FIFO       <td> Not Permitted
 * <tr><td> IAV_PART_PYRAMID_POOL   <td> Not Permitted
 * <tr><td> IAV_PART_CANVAS_POOL    <td> Not Permitted
 * <tr><td> IAV_PART_DSP_FIFO       <td> Not Permitted
 * <tr><td> IAV_PART_VOUT0_FB       <td> Not Permitted
 * <tr><td> IAV_PART_VOUT1_FB       <td> Not Permitted
 * <tr><td> IAV_PART_VOUT2_FB       <td> Not Permitted
 * </table>
 *
 * - - - -
 *
 * @subsection sec_driver_private_share 3.5 IAV / DSP Private and Shared MMBs
 *
 * As chapter @ref cma_layout_intr "1. Memory Layout Introduction" described,
 * Ambarella divides the system memory into "DSP private memory pool", "CV private
 * memory pool", and "DSP & CV shared memory pool" through the CMA.
 *
 * The combination of "DSP private memory pool" and "DSP & CV shared memory pool"
 * is called "DSP memory space". Table @ref sub_partitions_supported_mmbs
 * "IAV / DSP Sub-partitions private MMBs" lists the IAV / DSP private MMBs which
 * can only be accessed by "Arm + DSP", while the Table @ref sub_partitions_share_mmbs
 * "IAV / DSP Sub-partitions shared MMBs" lists the IAV / DSP shared
 * MMBs which can be access by "Arm + DSP + CV".
 *
 * @image html CMA_constituent_pool.jpg "Figure 3-3. The Constituent Pool of DSP Memory Space."
 *
 * @par IAV / DSP Sub-partitions Private MMBs
 * <table>
 * <caption id="sub_partitions_supported_mmbs"></caption>
 * <tr><th> IAV / DSP Sub-partition    <th>Attribute
 * <tr><td> IAV_PART_DSP               <td> Private
 * <tr><td> IAV_PART_DSP_DEF_CMD       <td> Private
 * <tr><td> IAV_PART_DSP_LOG           <td> Private
 * <tr><td> IAV_PART_IMG               <td> Private
 * <tr><td> IAV_PART_BSH               <td> Private
 * <tr><td> IAV_PART_DSP_UCODE         <td> Private
 * <tr><td> IAV_PART_DSP_RSV           <td> Private
 * <tr><td> IAV_PART_IAV_RSV           <td> Private
 * <tr><td> IAV_PART_BSB               <td> Private
 * <tr><td> IAV_PART_USR               <td> Private
 * <tr><td> IAV_PART_MV                <td> Private
 * <tr><td> IAV_PART_OVERLAY           <td> Private
 * <tr><td> IAV_PART_QPMATRIX          <td> Private
 * <tr><td> IAV_PART_QPMATRIX_RAW      <td> Private
 * <tr><td> IAV_PART_WARP              <td> Private
 * <tr><td> IAV_PART_QUANT             <td> Private
 * <tr><td> IAV_PART_MASK              <td> Private
 * <tr><td> IAV_PART_FB_DATA           <td> Private
 * <tr><td> IAV_PART_FB_AUDIO          <td> Private
 * <tr><td> IAV_PART_INTRA_PB          <td> Private
 * <tr><td> IAV_PART_STAT              <td> Private
 * <tr><td> IAV_PART_PREALLOC          <td> Private
 * <tr><td> IAV_PART_PREALLOC2         <td> Private
 * <tr><td> IAV_PART_QPMATRIX_RAW      <td> Private
 * <tr><td> IAV_PART_CANVAS_POOL       <td> Private
 * <tr><td> IAV_PART_BLUR              <td> Private
 * <tr><td> IAV_PART_HEVC_SCALELIST    <td> Private
 * <tr><td> IAV_PART_MULTI_COLOR_MASK  <td> Private
 * <tr><td> IAV_PART_INT_BSB           <td> Private
 * <tr><td> IAV_PART_ARB_BLUR          <td> Private
 * <tr><td> IAV_PART_EXTRA_RAW         <td> Private
 * <tr><td> IAV_PART_TFC               <td> Private
 * <tr><td> IAV_PART_AISP              <td> Private
 * <tr><td> IAV_PART_DEC_BSB           <td> Private
 * </table>
 *
 * @par  IAV / DSP Sub-partitions Shared MMBs
 * <table>
 * <caption id="sub_partitions_share_mmbs"></caption>
 * <tr><th> IAV / DSP Sub-partition <th>Attribute
 * <tr><td> IAV_PART_PYRAMID_POOL   <td> Shared
 * <tr><td> IAV_PART_CANVAS_POOL    <td> Shared
 * <tr><td> IAV_PART_RAW_POOL       <td> Shared
 * <tr><td> IAV_PART_VOUT0_FB       <td> Shared
 * <tr><td> IAV_PART_VOUT1_FB       <td> Shared
 * <tr><td> IAV_PART_VOUT2_FB       <td> Shared
 * <tr><td> IAV_PART_DSP_CV         <td> Shared
 * </table>
 *
 * - - - -
 *
 * @subsection sec_driver_module_parameters 3.6 Driver Module Parameters
 *
 * Ambarella’s CMA driver exports various driver module parameters to specify the sizes of
 * the IAV / DSP sub-partitions, and places the fixed sub-partitions into
 * the pre-allocated MMBs. The table below provides detailed descriptions of
 * the module parameters in the Ambarella CMA driver.
 *
 * @note
 * The CMA driver divides the memory into several partitions and maintains
 * several banks to better manage them. Each bank maintains 32 memory partitions,
 * <b>BANK0</b> for partition 0 ~ 31, <b>BANK1</b> for partition 32~63, and so on.
 * Drivers maintain several module parameters for each bank.
 *
 * <b>BANK0</b>: prealloc_buf_map, cached_buf_map <br>
 * <b>BANK1</b>: prealloc_buf_map1, cached_buf_map1
 *
 * @par Illustration of Module Parameters of the Ambarella CMA Driver
 * <table>
 * <caption id="illustration_of_module_parameters"></caption>
 * <tr><th> Parameters                <th> Description
 * <tr><td> buf_size_from_dts         <td> Specifies if the DSP
 * partition size from the device tree can be retrieved
 * <tr><td> dsp_buf_size              <td> Specifies the size of
 * the DSP partition (IAV_PART_DSP)
 * <tr><td> int_bsb_buf_size          <td> Specifies the size of
 * the internal bitstream partition (IAV_PART_INT_BSB)
 * <tr><td> bsb_buf_size              <td> Specifies the size of
 * the bitstream partition (IAV_PART_BSB)
 * <tr><td> usr_buf_size              <td> Specifies the size of
 * the user data partition (IAV_PART_USR)
 * <tr><td> mv_stat_size_per_stream   <td> Specifies the motion vector (MV) stats
 * buffer size for each stream. Determines the size of motion vector
 * partition (IAV_PART_MV) with another module parameter "mv_stream_num"
 * <tr><td> mv_stream_num             <td> Specifies the maximum MV stream number
 * Determines the size of the motion vector partition (IAV_PART_MV) with
 * another module parameter "mv_stat_size_per_stream". Meanwhile,
 * it decides the maximum stream number for the MV statistics
 * <tr><td> overlay_buf_size          <td> Specifies the size of
 * the overlay partition (IAV_PART_OVERLAY)
 * <tr><td> blur_buf_size             <td> Specifies the size of
 * the blur partition (IAV_PART_BLUR)
 * <tr><td> qpm_buf_size              <td> Specifies the size of
 * the quantization parameter (QP) region of interest (ROI) matrix
 * partition (IAV_PART_QPMATRIX) or the QPMATRIX_RAW partition
 * (IAV_PART_QPMATRIX_RAW). IAV_PART_QPMATRIX and IAV_PART_QPMATRIX_RAW
 * share the same memory partition
 * <tr><td> hevc_scalelist_buf_size   <td> Specifies the size of
 * the HEVC scale list partition (IAV_PART_HEVC_SCALELIST)
 * <tr><td> warp_buf_size             <td> Specifies the size of
 * the warp partition (IAV_PART_WARP)
 * <tr><td> quant_buf_size            <td> Specifies the size of
 * the JPEG quant matrix table (IAV_PART_QUANT)
 * <tr><td> pm_buf_size               <td> Specifies the size of
 * the MASK partition (IAV_PART_MASK)
 * <tr><td> pb_buf_size               <td> Specifies the size of
 * the intra playback partition (IAV_PART_INTRA_PB)
 * <tr><td> stat_buf_size             <td> Specifies the size of
 * the picture statistics partition (IAV_PART_STAT)
 * <tr><td> sbp_buf_size              <td> Specifies the size of
 * static bad pixel correction buffer, which is merged into (IAV_PART_IMG)
 * <tr><td> ik_buf_size               <td> Specifies the size of
 * IK configuration buffer, which is merged into (IAV_PART_IMG)
 * <tr><td> max_vin_width             <td> Specifies the maximum supported
 * video input (VIN) width, and should be aligned to 32. Determine the size of the
 * single color privacy mask partition (IAV_PART_MASK) with another variable
 * "max_vin_height". Meanwhile, it decides the maximum width of pyramid, warp, raw,
 * encode from memory (EFM), and image scale
 * <tr><td> max_vin_height            <td> Specifies the maximum-supported VIN
 * height, and should be aligned to 16. Determine the size of the single
 * color privacy mask partition (IAV_PART_MASK) with another module parameter
 * "max_vin_width". Meanwhile, it decides the maximum height of pyramid, warp,
 * raw, EFM, and image scale
 * <tr><td> mc_mask_buf_pitch         <td> Specifies the multi-color mask buffer
 * pitch, and should be aligned to 64. Determine the size of multi-color privacy
 * mask partition (IAV_PART_MULTI_COLOR_MASK) and memory layout with another
 * module parameter "mc_mask_buf_height"
 * <tr><td> mc_mask_buf_height        <td> Specifies the multi-color mask buffer
 * height. Determine the size of multi-color privacy mask partition
 * (IAV_PART_MULTI_COLOR_MASK) and memory layout with another module
 * parameter "mc_mask_buf_pitch"
 * <tr><td> extra_raw_buf_size        <td> Specifies the size of the extra raw
 * partition IAV_PART_EXTRA_RAW
 * <tr><td> tfc_buf_size              <td> Specifies the size of the thermal fusion CLUT partition IAV_PART_TFC
 * <tr><td> prealloc_buf_map          <td> Specifies the bit map (BANK0) of the IAV / DSP sub-partitions
 * that are allocated from the pre-allocated MMB.
 * For bit definition, refer to table @ref illustration_bank0 "IAV / DSP Sub-partitions bank0"
 * <tr><td> prealloc_buf_map1         <td> Specifies the bit map (BANK1) of the IAV / DSP
 * sub-partitions that are allocated from the pre-allocated MMB. For bit definition,
 * refer to table @ref illustration_bank0 "IAV / DSP Sub-partitions bank0"
 * <tr><td> cached_buf_map            <td> Specifies the bit map (BANK0) of IAV / DSP sub-partitions
 * that are mapped with cache enabled from user applications.
 * For bit definition, refer to table @ref illustration_bank0 "IAV / DSP Sub-partitions bank0"
 * <tr><td> cached_buf_map1           <td> Specifies the bit map (BANK1) of IAV / DSP sub-partitions
 * that are mapped with cache enabled from user applications.
 * For bit definition, refer to table @ref illustration_bank0 "IAV / DSP Sub-partitions bank0"
 * <tr><td> ama_enable                <td> Enables private memory allocator AMA to manage
 * IAV / DSP related CMA memory. By default, AMA is disabled
 * <tr><td> ama_alignment             <td> Specifies the maximum alignment of the start address of
 * the memory partitions allocated by AMA.  It is only valid when <b> ama_enable = 1 </b>.
 * For example, when it is 8, it means if the allocated memory partition size >= 1 MB,
 * the allocated memory partition start address will be aligned to 1MB (4KB * 1 << 8).
 * When the allocated memory partition size is < 1MB, the allocated memory partition start
 * address will be aligned to 2^round_up(log2(size)). The valid range for this parameter
 * is [4, 12].  The default is 8
 * <tr><td> ama_crc_enable            <td> Enables cyclic redundancy check (CRC) check for AMA internal bitmap.
 * It is only valid when <b>ama_enable = 1</b>. By default, it is disabled
 * </table>
 *
 * - - - -
 *
 * @subsection sec_dump_mmb_info 3.7 Dump MMB Information
 *
 * After the Linux system boots, users can dump the MMB information, including the physical
 * start address, size, kernel space virtual address, user mode reference count through the
 * memory map, the corresponding IAV / DSP sub-partition, and other MMB parameters.
 *
 * Users can also dump the user application information that allocates or memory maps
 * anonymous MMBs, including user application process ID and name, user mode reference
 * count through the memory map, and other select forms of user application information.
 *
 * In the following CV5 Timn board example for dumping the MMB information, the information is
 * shown in the ascending order of the physical address. The MMB4 and MMB6, which have the symbol
 * "|-" before their MMB IDs, are located in the pre-allocated MMBs. The total size of all MMBs
 * is provided at the end of the dumped information. In this example, private MMBs used about
 * 2575 MB, shared MMBs used about 4 MB, and the  total used MMB are 2579 MB.
 *
 * @subsubsection cmd_example_1 Example 1. Dumping the MMB information of a CV5 Timn board.
 * @code {.c}
 * # cat /proc/ambarella/cma
 * CV5x Ambarella CMA Driver : 2.0.0 (Last updated: 20221020)
 *
 *  DSP PRIVATE MEM REGION:
 * mmb   phys[start-end]          size        virt[start-end]                        attr    buf_id      ref_cnt  dma_buf  usage
 * 0     0x100000000-0x100404000  0x00404000  0xffffffc040000000-0xffffffc040404000  0x0003  21          0        0        IAV_PART_PREALLOC
 * |-4   0x100000000-0x100004000  0x00004000  0xffffffc040000000-0xffffffc040004000  0x0003  15          0        0        IAV_PART_DSP_DEF_CMD
 * |-6   0x100004000-0x100404000  0x00400000  0xffffffc040004000-0xffffffc040404000  0x0001  17          0        0        IAV_PART_DSP_LOG
 * 11    0x100404000-0x100406000  0x00002000  0xffffffc040404000-0xffffffc040406000  0x0000  7           0        0        IAV_PART_QUANT
 * 1     0x100500000-0x1025A6000  0x020A6000  0xffffffc040500000-0xffffffc0425a6000  0x0003  22          0        0        IAV_PART_PREALLOC2
 * |-2   0x100500000-0x1005BD000  0x000BD000  0xffffffc040500000-0xffffffc0405bd000  0x0003  19          0        0        IAV_PART_DSP_RSV
 * |-5   0x1005BD000-0x100FBD000  0x00A00000  0xffffffc0405bd000-0xffffffc040fbd000  0x0001  16          0        0        IAV_PART_DSP_UCODE
 * |-12  0x100FBD000-0x1024BD000  0x01500000  0xffffffc040fbd000-0xffffffc0424bd000  0x0001  8           0        0        IAV_PART_IMG
 * |-14  0x1024BD000-0x1024C1000  0x00004000  0xffffffc0424bd000-0xffffffc0424c1000  0x0003  14          0        0        IAV_PART_BSH
 * |-15  0x1024C1000-0x1025A6000  0x000E5000  0xffffffc0424c1000-0xffffffc0425a6000  0x0003  20          0        0        IAV_PART_IAV_RSV
 * 3     0x102600000-0x192600000  0x90000000  0xffffffc042600000-0xffffffc0d2600000  0x0005  0           0        0        IAV_PART_DSP
 * 7     0x192600000-0x194600000  0x02000000  0xffffffc0d2600000-0xffffffc0d4600000  0x0008  1           0        0        IAV_PART_BSB
 * 8     0x194600000-0x195614000  0x01014000  0xffffffc0d4600000-0xffffffc0d5614000  0x0008  4           0        0        IAV_PART_OVERLAY
 * 9     0x195700000-0x196100000  0x00A00000  0xffffffc0d5700000-0xffffffc0d6100000  0x0008  5           0        0        IAV_PART_QPMATRIX
 * 10    0x196100000-0x1970C0000  0x00FC0000  0xffffffc0d6100000-0xffffffc0d70c0000  0x0008  6           0        0        IAV_PART_WARP
 * 13    0x197100000-0x1A1100000  0x0A000000  0xffffffc0d7100000-0xffffffc0e1100000  0x0008  9           0        0        IAV_PART_MASK
 *
 * Total mmb size: 0xa0e80000, about 2575MB, total 2816MB
 *
 *  DSP SHARED MEM REGION:
 * mmb   phys[start-end]          size        virt[start-end]                        attr    buf_id      ref_cnt  dma_buf  usage
 * 0     0x0FF000000-0x0FF152000  0x00152000  0xffffffc012000000-0xffffffc012152000  0x0044  35          0        0        IAV_PART_VOUT0_FB
 * 1     0x0FF200000-0x0FF352000  0x00152000  0xffffffc012200000-0xffffffc012352000  0x0044  36          0        0        IAV_PART_VOUT1_FB
 * 2     0x0FF400000-0x0FF552000  0x00152000  0xffffffc012400000-0xffffffc012552000  0x0044  37          0        0        IAV_PART_VOUT2_FB
 *
 * Total mmb size: 0x3f6000, about 4MB, total 16MB
 *
 * @endcode
 *
 * @par MMB Information
 * <table>
 * <caption id="illustration_of_mm_info"></caption>
 * <tr><th> Parameters         <th> Description
 * <tr><td> mmb               <td>MMB ID for internal reference
 * <tr><td> phys[start-end]   <td>Physical address illustrated from beginning to end
 * <tr><td> size              <td>MMB size
 * <tr><td> virt[start-end]   <td>Kernel space virtual address illustrated from beginning to end
 * <tr><td> attr              <td>MMB attributes, for bit definition, refer to table
 * @ref illustration_mmb_attribute "MMB attributes"
 * <tr><td> buf_id            <td>IAV / DSP / sub-partition ID and ANONYMOUS_MMB ID, refer to table
 * @ref illustration_bank0 "IAV / DSP Sub-partitions bank0,"
 * @ref illustration_bank1 "IAV / DSP Sub-partitions bank1."
 * <tr><td> ref_cnt           <td>Reference count by user applications through mmap
 * <tr><td> usage             <td>Corresponding sub-partition name
 * <tr><td> pid               <td>The process ID of user application which allocates or maps anonymous MMB
 * <tr><td> user_name         <td>The user name of user application which allocates or maps anonymous MMB
 * </table>
 *
 * @par IAV / DSP Sub-partitions bank0
 * <table>
 * <caption id="illustration_bank0"></caption>
 * <tr><th> Enumeration                      <th> Description
 * <tr><td> IAV_PART_DSP = 0                 <td> DSP partition
 * <tr><td> IAV_PART_BSB = 1                 <td> Bitstream partition
 * <tr><td> IAV_PART_USR = 2                 <td> User data partition
 * <tr><td> IAV_PART_MV = 3                  <td> Motion vector partition
 * <tr><td> IAV_PART_OVERLAY = 4             <td> Overlay partition
 * <tr><td> IAV_PART_QPMATRIX = 5            <td> QP ROI matrix partition
 * <tr><td> IAV_PART_WARP = 6                <td> Warp partition
 * <tr><td> IAV_PART_QUANT = 7               <td> JPEG quant matrix table partition
 * <tr><td> IAV_PART_IMG = 8                 <td> IDSP image partition
 * <tr><td> IAV_PART_MASK = 9                <td> MASK partition
 * <tr><td> IAV_PART_FB_DATA = 10            <td> Fastboot data partition
 * <tr><td> IAV_PART_FB_AUDIO = 11           <td> Fastboot audio partition
 * <tr><td> IAV_PART_INTRA_PB = 12           <td> Intra playback partition
 * <tr><td> IAV_PART_STAT = 13               <td> Picture statistics partition
 * <tr><td> IAV_PART_BSH = 14                <td> Bitstream header buffer for internal use
 * <tr><td> IAV_PART_DSP_DEF_CMD = 15        <td> DSP default command buffer for internal use
 * <tr><td> IAV_PART_DSP_UCODE = 16          <td> Ucode partition
 * <tr><td> IAV_PART_DSP_LOG = 17            <td> DSP log buffer for internal use
 * <tr><td> IAV_PART_DSP_FIFO = 18           <td> DSP FIFO buffer for internal use
 * <tr><td> IAV_PART_DSP_RSV = 19            <td> DSP driver reserved partition for internal use
 * <tr><td> IAV_PART_IAV_RSV = 20            <td> IAV driver reserved partition for internal use
 * <tr><td> IAV_PART_PREALLOC = 21           <td> Pre-allocated CMA partition for internal use
 * <tr><td> IAV_PART_PREALLOC2 = 22          <td> Pre-allocated CMA partition2 for internal use
 * <tr><td> IAV_PART_PYRAMID_POOL = 23       <td> Pyramid buffer pool for pyramid manual-feed mode
 * <tr><td> IAV_PART_QPMATRIX_RAW = 24       <td> QPMATRIX_RAW buffer
 * <tr><td> IAV_PART_CANVAS_POOL = 25        <td> Canvas buffer pool for manual-feed mode
 * <tr><td> IAV_PART_INT_BSB = 26            <td> Internal use bitstream partition
 * <tr><td> IAV_PART_EXTRA_RAW = 27          <td> Extra raw partition
 * <tr><td> IAV_PART_RAW_POOL = 28           <td> Raw buffer pool for the raw manual-feed mode
 * <tr><td> IAV_PART_HEVC_SCALELIST = 29     <td> HEVC scale list partition
 * <tr><td> IAV_PART_BLUR = 30               <td> Blur partition
 * <tr><td> IAV_PART_ARB_BLUR = 31           <td> Customized blur partition
 * </table>
 *
 * @par IAV / DSP Sub-partitions bank1
 * <table>
 * <caption id="illustration_bank1"></caption>
 * <tr><th> Enumeration                    <th> Description
 * <tr><td> IAV_PART_BLEND_ALPHA = 32      <td> Blend Alpha partition
 * <tr><td> IAV_PART_MULTI_COLOR_MASK = 33 <td> Multi-color mask partition
 * <tr><td> IAV_PART_TFC = 34              <td> TML fusion color lookup table (CLUT) partition
 * <tr><td> IAV_PART_VOUT0_FB = 35         <td> VOUT frame buffer partition
 * <tr><td> IAV_PART_VOUT1_FB = 36         <td> VOUT frame buffer partition
 * <tr><td> IAV_PART_VOUT2_FB = 37         <td> VOUT frame buffer partition
 * <tr><td> IAV_PART_AISP = 38             <td> Ambarella AISP partition
 * <tr><td> IAV_PART_DEC_BSB = 39          <td> Decoder BSB buffer partition
 * <tr><td> IAV_PART_DSP_CV = 40           <td> DSP CV shared buffer partition
 * </table>
 *
 * @par Illustration of MMB Attributes
 * <table>
 * <caption id="illustration_mmb_attribute"></caption>
 * <tr><th> Enumeration      <th> Description
 * <tr><td> Bit0             <td>1: Cannot be freed once allocated <br>
 * 0: Can be freed
 * <tr><td> Bit1             <td>1: Cannot be mapped and accessed from user applications <br>
 * 0: Can be mapped and accessed from user applications
 * <tr><td> Bit2             <td>1: Cannot be put to IAV_PART_PREALLOC <br>
 * 0: Can be put to IAV_PART_PREALLOC
 * <tr><td> Bit3             <td>1: Cache enabled when mapped from user mode <br>
 * 0: Cache disabled when mapped from user mode
 * </table>
 *
 * - - - -
 *
 * @subsection sec_private_mem_allocator 3.8 Private Memory Allocator AMA
 *
 * When using the CMA memory management method, the CMA driver is based on
 * the Linux CMA to allocate physically contiguous memory for the IAV / DSP partitions.
 * However, the Linux CMA includes an out of memory (OOM), which can be triggered when
 * the Linux system tries to "borrow" memory from the free memory of the CMA pool.
 * For the detailed root cause of OOM, refer to Chapter @ref cma_faq "5.FAQ". When OOM
 * is triggered, it typcially becomes a serious problem as OOM might kill key user
 * applications that have been run by the user.
 *
 * In order to deal with OOM problems, the CMA driver introduces AMA, which is its
 * own private memory allocator. Once the AMA is enabled, it is responsible for
 * allocating and freeing the IAV / DSP memory partitions instead of using the Linux CMA.
 * Additionally, it prevents the above OOM issue by not allowing the Linux system to
 * "borrow" memory from its free / unused memory. AMA achieves this by requesting all
 * available memory from the IAV / DSP CMA pool at the driver initializing stage and
 * managing this memory pool by itself.
 *
 * @subsubsection sub_sec_ama 3.8.1 Enable AMA
 * The CMA driver provides several module parameters for users to configure AMA.
 *
 * Module parameter <b>ama_enable</b> is used to enable / disable AMA. It is
 * disabled by default, meaning that Linux CMA will be used to allocate or free
 * IAV / DSP memory partitions. When it is enabled, AMA will replace Linux CMA
 * to allocate or free these memory partitions.
 *
 * Module parameter <b>ama_alignment</b>
 * is used to specify the maximum alignment of the start address of memory partitions
 * allocated by AMA. It is only valid when <b>ama_enable = 1</b>. For example, when
 * it is equal to eight, it means if the allocated memory partition size is ±1MB,
 * the allocated memory partition start address will be aligned to 1MB (4KB * (1 << 8)).
 * When the allocated memory partition size < 1MB, the allocated memory partition start
 * address will be aligned to 2^round_up(log2(size)). The valid range of this parameter is
 * [4, 12]; the default is 8.
 *
 * @subsubsection cmd_example_2 Example 2. Enabling AMA through the module parameter "ama_enable" of Ambarella CMA driver.
 *
 * @code {.c}
 * board # modprobe ambcma ama_enable=1 ama_alignment=8
 * @endcode
 *
 * - - - -
 *
 * @section cma_example 4. Examples
 *
 * This chapter includes the following sections:
 * <ul>
 * <li> Section @ref specify_sub_partion_size
 * <li> Section @ref specify_pre_allocate_mmbs
 * <li> Section @ref specify_cache_mmbs
 * <li> Section @ref mange_memory_partition
 * </ul>
 *
 * @subsection specify_sub_partion_size 4.1 Specifying the IAV / DSP Sub-partition Size
 *
 * The following lists three stages for specifying the size of each
 * IAV / DSP sub-partition for different use cases:
 *   - Compile stage
 *      - Configures the partition size through menuconfig then compiles it into the image
 *   - Driver installation stage
 *      - Configures the driver module parameters to load different options for the partition size
 *   - Run-time stage
 *      - Configures and resizes partition size through IAV IOCTL on-the-fly when the system is running
 *
 * @subsubsection sub_sec_compile 4.1.1 Compile Configuration
 * For the reserved memory management method, the default size of some IAV / DSP
 * sub-partitions can be configured at the compile stage through make menuconfig.
 * For more details, refer to the @a Flexible @a Linux @a SDK @a Design
 * @a Guide @a - @a DRAM @a Optimization document.
 *
 * Using the user data buffer (IAV_PART_USR) as an example, users can specify
 * its default size through make menuconfig as follows.
 * @par For Cooper Amba build:
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *            (0x04000000) IAV Usr Buffer Size
 * @endcode
 * @par For Cooper Yocto build:
 * @code {.c}
 * build$ make menuconfig
 * 	 meta-ambabsp --->
 *     recipes-video  --->
 *       -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)  --->
 *            (0x04000000) IAV Usr Buffer Size
 * @endcode
 *
 * In addition, users can specify the default size of the DSP buffer (IAV_PART_DSP)
 * through make menuconfig, but only for the CMA memory management method (see below).
 * @par For Cooper Amba build:
 * @code {.c}
 * build$ make menuconfig
 *    drv_modules  --->
 *       private  --->
 *          -*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *            (0x90000000) DSP buffer size
 * @endcode
 * @par For Cooper Yocto build:
 * @code {.c}
 * build$ make menuconfig
 * 	 meta-ambabsp --->
 *     recipes-video  --->
 *       -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)  --->
 *            (0x90000000) DSP buffer size
 * @endcode
 *
 * @subsubsection sub_sec_mod_conf 4.1.2 Module Parameters Configuration
 * The size of the IAV / DSP sub-partitions can also be configured through
 * the driver module parameters of the Ambarella CMA driver.
 *
 * This method provides more flexibility in specifying the DRAM size for different
 * partitions without re-compiling the entire image, thereby allowing users to verify different cases.
 *
 * The following is an example showing how to specify the sizes of the DSP
 * buffer, the bitstream buffer, and the user data buffer through the module parameters.
 *
 * @subsubsection cmd_example_3 Example 3. Specifying the size of the IAV / DSP sub-partitions through the module parameters of Ambarella CMA driver.
 * @code {.c}
 * board # modprobe ambcma dsp_buf_size= 0x90000000 bsb_buf_size=0x0A00000 usr_buf_size=0x4000000
 * @endcode
 *
 * @subsubsection sub_sec_ioctl 4.1.3 IOCTL Configuration
 * Some of the IAV / DSP sub-partitions (such as the bitstream buffer, user data buffer,
 * overlay buffer, and other sub-partitions) will need to be resized at runtime. In
 * order to meet these requirements, the IAV driver exports two input output control (IOTCL) APIs:
 * <b>IAV_IOC_ALLOC_MEM_PART</b> and <b>IAV_IOC_FREE_MEM_PART</b> to the user applications.
 *   - <b>IAV_IOC_ALLOC_MEM_PART</b> allocates the IAV / DSP sub-partitions.
 *   - <b>IAV_IOC_FREE_MEM_PART</b> frees the IAV / DSP sub-partitions.
 *
 * Refer to the unit test, test_mempart, for more detailed instructions.
 *
 * <b>Implementation:</b>
 *   - Before resizing an existing IAV / DSP sub-partition, users must first free
 * the sub-partition, and unmap it from all user applications. Also, confirm that
 * no potential applications can access it.
 *   - The IAV / DSP sub-partitions that have been put in the pre-allocated MMB cannot be resized.
 *
 * @par Illustration of the Resizable IAV / DSP Sub-partitions
 * <table>
 * <caption id="cam_table_illuatrate_partitions"></caption>
 * <tr><th>Resizable IAV / DSP Sub-partition    <th>State
 * <tr><td> IAV_PART_BSB            <td> Idle
 * <tr><td> IAV_PART_USR            <td> Any
 * <tr><td> IAV_PART_MV             <td> Idle
 * <tr><td> IAV_PART_OVERLAY        <td> Idle/Preview
 * <tr><td> IAV_PART_QPMATRIX       <td> Idle/Preview
 * <tr><td> IAV_PART_QPMATRIX _raw  <td> Idle/Preview
 * <tr><td> IAV_PART_WARP           <td> Idle
 * <tr><td> IAV_PART_QUANT          <td> Idle/Preview
 * <tr><td> IAV_PART_MASK           <td> Idle
 * <tr><td> IAV_PART_INTRA_PB       <td> Idle
 * <tr><td> IAV_PART_EXTRA_RAW      <td> Idle
 * <tr><td> IAV_PART_STAT           <td> Idle
 * </table>
 *
 * The following example shows how to resize a bitstream buffer with the unit test test_mempart.
 * @subsubsection cmd_example_4 Example 4. Resizing the bitstream buffer (IAV_PART_BSB) through test_mempart.
 *
 * @code {.c}
 * board # test_mempart -m 1				// show current size
 * [BSB 1] Base Address: [0x31600000], Size [   10240 KB]
 *
 * board # test_mempart -m 1 –f				// free current partition
 * board # test_mempart -m 1
 * [BSB 1] Base Address: [0x00000000], Size [       0 KB]
 *
 * board # test_mempart -m 1 –s 0x1000000	// reallocate
 * [BSB 1] has been allocated successfully.
 *           Base Address: [0x33C00000], Size [   16384 KB]
 * @endcode
 *
 * - - - -
 *
 * @subsection specify_pre_allocate_mmbs 4.2 Specifying the Pre-allocated MMBs
 *
 * This section describes two methods to configure the IAV / DSP sub-partitions as pre-allocated MMBs.
 *
 * @subsubsection sub_sec_compile_configuration 4.2.1 Compile Configuration
 * The default bitmap of the IAV / DSP sub-partitions that will be placed into pre-allocated MMBs,
 * along with the sub-bitmap of these partitions,
 * can be configured through "make menuconfig".
 *
 * For detailed bit definitions of each partition, refer to table @ref illustration_bank0
 * "IAV / DSP Sub-partitions bank0."
 * @code {.c}
 * build$ make menuconfig
 *   [*] Ambarella Linux Configuration ->
 *     [*] Ambarella Private Drivers Configuration ->
 *       (0x378101) The default map of buffers from prealloc MMB
 * @endcode
 *
 * @subsubsection sub_sec_conf_mod 4.2.2 Configuring the Module Parameters
 * The bitmap of the IAV / DSP sub-partitions that will be placed into the pre-allocated
 * MMBs can be configured through the module parameter "prealloc_buf_map" in the Ambarella
 * CMA driver.
 *
 * The following example demonstrates how to specify the bitmap of the IAV / DSP
 * sub-partitions through the module parameters "prealloc_buf_map" and "nofree_prealloc_buf_map".
 *
 * @subsubsection cmd_example_5 Example 5. Specifying the bitmap of the IAV / DSP sub-partitions through the module parameters "prealloc_buf_map" and "nofree_prealloc_buf_map" of the Ambarella CMA driver.
 *
 * @code {.c}
 * board # modprobe ambcma prealloc_buf_map=0x378101 nofree_prealloc_buf_map=0x328100
 * @endcode
 *
 * @subsection specify_cache_mmbs 4.3 Specifying Cached MMBs
 * This section describes how to enable the Arm data cache for IAV / DSP sub-partitions
 * mapped from the user mode. The following table lists the IAV / DSP sub-partitions
 * for which the Arm data cache can be enabled.
 *
 * @par Illustration of the IAV / DSP Sub-partitions that can Enable the Data Cache
 * <table>
 * <caption id="cam_table_partitions_can_enable_cache"></caption>
 * <tr><th> IAV / DSP Sub-partitions for Caching    <th>State
 * <tr><td> IAV_PART_BSB              <td> Selective
 * <tr><td> IAV_PART_DSP              <td> Selective
 * <tr><td> IAV_PART_USR              <td> Selective
 * <tr><td> IAV_PART_MV               <td> Selective
 * <tr><td> IAV_PART_OVERLAY          <td> Selective
 * <tr><td> IAV_PART_QPMATRIX         <td> Selective
 * <tr><td> IAV_PART_QPMATRIX_RAW     <td> Selective
 * <tr><td> IAV_PART_WARP             <td> Selective
 * <tr><td> IAV_PART_MASK             <td> Selective
 * <tr><td> IAV_PART_BLEND_ALPHA      <td> Selective
 * <tr><td> IAV_PART_EXTRA_RAW        <td> Selective
 * <tr><td> IAV_PART_ARB_BLUR         <td> Selective
 * <tr><td> IAV_PART_STAT             <td> Selective
 * <tr><td> IAV_PART_PYRAMID_POOL     <td> Selective
 * <tr><td> IAV_PART_CANVAS_POOL      <td> Selective
 * <tr><td> IAV_PART_INT_BSB          <td> Selective
 * <tr><td> IAV_PART_RAW_POOL         <td> Selective
 * <tr><td> IAV_PART_HEVC_SCALELIST   <td> Selective
 * <tr><td> IAV_PART_BLUR             <td> Selective
 * <tr><td> IAV_PART_MULTI_COLOR_MASK <td> Selective
 * <tr><td> IAV_PART_TFC              <td> Selective
 * </table>
 *
 *  @subsubsection sub_sec_conf_mod_para 4.3.1 Configuring Module Parameters
 * The bitmap of the IAV / DSP sub-partitions that can utilize the Arm data cache
 * is configured through the module parameter "cached_buf_map" in the Ambarella CMA driver.
 *
 * The following example shows how to specify the bitmap of the IAV / DSP
 * sub-partitions through the module parameter "cached_buf_map".
 *
 * @subsubsection cmd_Example_6  Example 6. Specifying the bitmap of the IAV / DSP sub-partitions through the module parameters "cached_buf_map" of the Ambarella CMA driver.
 *
 * @code {.c}
 * board # modprobe ambcma cached_buf_map=0x7e
 * @endcode
 *
 * - - - -
 *
 * @subsection mange_memory_partition 4.4 Allocating/Freeing Anonymous Memory Partitions
 * Anonymous memory partitions can only be allocated or freed during the run-time stage.
 * The IAV driver exports the IOCTL API <b>IAV_IOC_ALLOC_ANON_MEM_PART</b> to user applications
 * in order to allocate anonymous memory partitions.  Alternatively, the
 * API <b>IAV_IOC_ALLOC_MEM_PART</b> is exported to allocate the IAV / DSP sub-partitions.
 * To free anonymous memory partitions, applications can use the API <b>IAV_IOC_FREE_MEM_PART</b>.
 *
 * @note
 * <b>IAV_IOC_ALLOC_ANON_MEM_PART</b> should only be used for allocating anonymous memory
 * partitions. For detailed usage, refer to the unit test: test_mempart.
 *
 * @subsubsection cmd_example_7 Example 7. Allocating or freeing the anonymous memory partition through test_mempart.
 *
 * @code {.c}
 * board # test_mempart -a -s 0x1000000 -c
 * anonymous mem_part[4517] has been allocated successfully.
 * 	Base Address: [0x43700000], Size [   16384 KB].
 * // 4517 is the memory partition ID of allocated memory partition
 * // -c: enable ARM data cache for anonymous MMB
 *
 * board # test_mempart -m 4517 -f			// free this partition
 * @endcode
 *
 * - - - -
 *
 * @section cma_faq 5. FAQ
 *
 * <b>Question 1</b>: If the system fails to allocate the physically contiguous
 * memory through <b>IAV_IOC_ALLOC_ANON_MEM_PART</b> due to an insufficient CMA
 * pool size, what should the user do?
 *
 * <b>Example: IAV_IOC_ALLOC_ANON_MEM_PART</b>: bad address
 * @code {.c}
 * [  462.309301] #iav_error# cma_alloc(226): dma_alloc_writecombine error[0x00FD2000], no memory
 * [  462.309310] #iav_error# iav_ioc_s_alloc_anon_mem_part (1400): fail to allocated anonymous part.
 * @endcode
 *
 * <b>Cause</b>: On the CV5x / CV7x platforms, the physically contiguous memory is allocated from the CMA
 * pool through <b>IAV_IOC_ALLOC_ANON_MEM_PART</b>. When the CMA pool cannot meet the demand
 * for allocating a large number of contiguous memory blocks, the CMA pool size must be enlarged.
 *
 * <b>Solution:</b> Enlarge the size of the CMA pool for the IAV and DSP partitions through menuconfig.
 * @par For Cooper Amba build:
 * @code {.c}
 * build $ make menuconfig
 * 	 -*- board (boards)  --->
 *     Memory  --->
 * 		(2816) DSP Private Memory size in MB
 * @endcode
 * @par For Cooper Yocto build:
 * @code {.c}
 * build $ make menuconfig
 * 	 meta-ambabsp --->
 *     recipes-bsp --->
 *       -*- board (meta-ambabsp/recipes-bsp/board)  --->
 *           Memory  --->
 *              (2816) DSP Private Memory size in MB
 * @endcode
 *
 * Check the kernel log during system boot up to verify that the modification is functioning correctly. The following message example is from CV5x.
 * @code {.c}
 * [    0.000000] Booting Linux on physical CPU 0x0000000000 [0x414fd0b1]
 * [    0.000000] Linux version 5.15.93 (mwen@shbuild3) (aarch64-linux-gnu-gcc (GCC) 12.1.1 20220803 [ revision 3df2f035871e913b94a35d4b5c12d37828f313f7], GNU ld (Binutils-2.38-20220721) 2.38.20220708) #3 SMP PREEMPT Wed Sep 22 10:30:59 CST 2021
 * [    0.000000] Machine model: Ambarella CV5 TIMN Board
 * [    0.000000] Reserved memory: created CMA memory pool at 0x000000002c000000, size 64 MiB
 * [    0.000000] OF: reserved mem: initialized node linux,cma, compatible id shared-dma-pool
 * [    0.000000] Reserved memory: created CMA memory pool at 0x0000000030000000, size 512 MiB
 * [    0.000000] OF: reserved mem: initialized node cavalry@0, compatible id shared-dma-pool
 * [    0.000000] Reserved memory: created DMA memory pool at 0x0000000100000000, size 2816 MiB
 * [    0.000000] OF: reserved mem: initialized node iav@0, compatible id shared-dma-pool
 * @endcode
 *
 * <b>Question 2</b>: The CMA partition includes unused memory. However, when the Linux
 * system attempts to reuse this memory, an OOM-killer results. Why does this happen?
 *
 * <b>Cause</b>: Although the Linux system can reuse the free memory in the CMA partition
 * to obtain a higher DRAM-use ratio, there are conditions. For example, CMA memory used
 * by the Linux system must be (migratable) when the Linux kernel attempts to allocate
 * physically contiguous memory blocks (but the remaining size is not sufficient).
 *
 * The following lists information about the Linux system’s use of the free memory in the CMA pool:
 *   - Not all Linux system memory is migratable. User-space allocated memory and file system cache
 * memory are migratable, while Linux-kernel allocated memory and page table memory are not.
 *   - Migrated memory is returned to the Linux partition. However, when the Linux system attempts
 * to allocate memory from the CMA partition, its memory has now been depleted, and finding
 * additional memory to save the migrated data may not be possible.
 *
 * Based on its design, the Linux "Buddy System" (system memory allocator) prefers to allocate
 * system memory directly from the Linux partition instead of the CMA partition. Once all
 * memory from the Linux partition is allocated, the Linux system "borrows"from the CMA
 * partition. However, when there is a request to allocate the system memory that cannot be
 * migrated or swapped from the CMA partition, the system must allocate from the Linux
 * partition—which no longer has the necessary remaining memory. As a result, an
 * OOM-killer is triggered to reclaim more system memory.
 *
 * <b>Solution</b>: Although an ideal solution does not currently exist, a
 * possible solution is as follows:
 *
 * Specify the size of the CMA partition according to real user requirements, and
 * allocate a portion of the available memory resources to the Linux partition.
 *
 * - - - -
 *
 * @section cma_license 6. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * - - - -
 *
 *
 */
/*! @file doc_drv_iav.h
 * @brief This file defines the doxygen structure of iav ioctl api.
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
/*! @page page_drv_iav_doc IAV Driver API
 *
 * @section iav_history 0. Revision History
 *
 * <table>
 * <caption id="drv_iav_rev_history"></caption>
 * <tr><th> Updated Date          <th align="left"> Modification
 * <tr><td> 20210924              <td> Initial draft
 * <tr><td> 20220415              <td> Update for SDK 1.0
 * <tr><td> 20230308              <td> Update for Cooper SDK 0.5
 * <tr><td> 20230821              <td> Update for Cooper SDK 1.0
 * </table>
 *
 * - - - -
 *
 * @section iav_intro 1. Introduction
 *
 * The Ambarella Cooper family systems on chip (SoCs) are ideal for multi-video input (VIN) camera
 * applications. The platforms are driven by a Linux 64-bit operating system (OS) that runs
 * on Arm® Dual-Cortex®-A76 cores of the Cv5x / CV7x processors.
 * The Linux kernel is based on a standard 5.15.0+ GNU release with Ambarella modifications
 * offered as a kernel patch. Device drivers are needed to make the device work properly
 * and provide a user-friendly interface for applications.
 *
 * The Cooper platform device driver is called the @a Image Audio Video (IAV) @a Device @a Driver.
 * It includes a set of Linux device drivers that encapsulate the lower-level complexities of
 * the Cooper platform digital signal processor (DSP) core functionalities. The drivers conform to
 * the standard Linux driver model, exposing a series of application programming interfaces
 * (APIs) that can be invoked using @b ioctl() system calls. These APIs are used by applications
 * to configure and control the Cooper platform SoC in details, including the control of image, audio,
 * and video. (Audio control is new in this version.)
 *
 * Prototypes for the APIs and structures can be found in iav_ioctl.h. The image audio video (IAV)
 * driver provides mechanisms to control some of the lower level hardware devices, such as the VIN
 * module (sensor), video output (VOUT) module, and DSP cores.
 *
 * In addition to providing user interfaces, the IAV driver also allows for coordination of the
 * system to read the input image stream, process it, and encode it to an H.264, H.265 and/or
 * Motion-JPEG bit stream. The figure below shows the work flow of the data process.
 * @image html iav_hardware_flow.png "Figure 1-1. Illustration of Hardware Work Flow."
 *
 * - - - -
 *
 * @section iav_key_feature 2. Key Features of the APIs
 *
 * The IAV driver provides several groups of APIs that enable the application-level software to
 * control the entire data processing flow. The APIs allow to control the following functionality:
 *   - VIN control unit
 *   - Video output (VOUT) control unit
 *   - Image processing
 *   - H.265 / H.264 / motion-JPEG encode
 *   - RAW image / YUV image / ME1 image / ME0 image capture
 *
 * The key features of the API package are as follows:
 *   - Supports video output with various resolutions and frame rates.
 *   - Supports frame buffer display on the VOUT preview.
 *   - Supports various image processing pipeline with different feature sets.
 *   - Supports VOUT preview with / without encoding.
 *   - Supports encoding to H.265 only, H.264 only, MJPEG only, and H.265/H.264 plus MJPEG multi-streaming,
 * and other types of multi-streaming (up to 20 streams with different encoding sources).
 *   - Supports digital pan / tilt / zoom (DPTZ) of the encoded video bit stream and video output.
 *
 * - - - -
 *
 * @section iav_state_model 3. IAV Driver State Model
 * @subsection iav_driver_state_machine 3.1 IAV Driver State Machine
 * The IAV driver includes a state machine to protect the application from exercising the lower-level
 * hardware in an unsupported manner.
 * @image html iav_state_model_v6.png "Figure 3-1. Driver State Model."
 *
 * The following is a description of IAV state.
 * <table>
 * <caption id="table_iav_state"></caption>
 * <tr><th>State    <th>Description
 * <tr><td><B>@anchor anchor_state_init Init</B>
 * <td>The IAV driver is loaded to kernel with empty configuration. And the DSP is not booted yet.
 * <tr><td><B>@anchor anchor_state_idle Idle</B>
 * <td>In this state, the hardware is idle and the user can issue commands to set up the
 *    VIN, VOUT, IDSP, and encoder modules, and reconfigure the system source buffers, or change to
 *    special settings that require the system to go idle in advance and so on.
 * <tr><td><B>@anchor anchor_state_preview Preview</B>
 * <td>The hardware processes incoming image data from the VIN module. Video output (VOUT) preview
 *    can be enabled/disabled and the VOUT resolution can be also changed.
 * <tr><td><B>@anchor anchor_state_encoding Encoding</B>
 * <td>The hardware encodes video data in this state.
 * <tr><td><B>@anchor anchor_state_decoding Decoding</B>
 * <td>The hardware decodes video data in this state.
 * <tr><td><B>@anchor anchor_state_duplex Duplex</B>
 * <td>The hardware is in preview / encoding and decoding state at the same time.
 * </table>
* @subsection iav_driver_boot_param 3.2 IAV driver boot param
 * The IAV Driver initializes dsp module with @a iav_dsp_boot_params at the first time entering Preview state.
 * And the boot parameters can't be modified after initialization.
 *
 * The following is a description of dsp boot parameters.
 * <table>
 * <caption id="table_dsp_boot_params"></caption>
 * <tr><th>param    <th>Description
 * <tr><td><B>@anchor anchor_boot_param_debug_chip_id debug_chip_id</B>
 * <td>This section include "debug_chip_id_flag" and "debug_chip_id".<br>
 *    If "debug_chip_id_flag" is set true, Dsp will use "debug_chip_id" instead of the real chip id.
 *    It's used to do different chip simulation in the one same chip.
 * <tr><td><B>@anchor anchor_boot_param_vout_osd_rescale_disable vout_osd_rescale_disable</B>
 * <td>This section include "vout_osd_rescale_flag" and "vout_osd_rescale_disable".<br>
 *    If "vout_osd_rescale_flag" is set true, Dsp will determine whether OSD rescale ise enabled or
 *    disabled based on the value of "vout_osd_rescale_disable" for vout0 / vout 1.
 * <tr><td><B>@anchor anchor_boot_param_vout_possible_map vout_possible_map</B>
 * <td>This section include "vout_possible_map_flag" and "vout_possible_map".<br>
 *    If "vout_possible_map_flag" is set true, Dsp will decide whether it is possile to support vout 0
 *    or vout 1 based on the value of "vout_possible_map".
 *    It's used to allocate vout related resources inside Dsp.
 * </table>
 * <br>
 *
 * ---
 *
 * @section iav_interrupts 4. IAV Interrrupts
 *
 * There are 3 interrupts generated as a group for each VIN controller.
 *   - @b vin_idsp - This interrupt is generated by DSP. It is signaled to Arm, when DSP finishes 1 frame capture.
 *     - CV5 / CV52 has 14 VIN controllers (vin0 ~ vin13); it has 14 groups of VIN related interrupts.
 *     - CV72 has 10 VIN controllers (vin0 ~ vin3, vin8 ~ vin13); it has 10 groups of VIN-related interrupts.
 *     - Users can check this interrupt for VIN 0 using the command below:
 *       @code
 *       board # cat /proc/interrupts | grep vin0_idsp
 *       @endcode
 *   - @b vin_idsp_sof - This interrupt is generated by VIN hardware. It is signaled to Arm,
 * when VIN hardware receives the SOF (Start Of Frame) signal from the sensor.
 *     - Users can check this interrupt for VIN 0 using:
 *       @code
 *       board # cat /proc/interrupts | grep vin0_idsp_sof
 *       @endcode
 *   - @b vin_idsp_last_pixel - This interrupt is generated by VIN hardware. It is signaled to Arm,
 * when VIN hardware receives the EOF (End Of Frame) signal from the sensor.
 *     - Users can check this interrupt for VIN 0 using:
 *       @code
 *       board # cat /proc/interrupts | grep vin0_idsp_last_pixel
 *       @endcode
 *
 * There are 7 interrupts generated for DSP.
 *   - @b vdsp - This interrupt is a generic interrupt used for general cmd/msg exchange
 * between Arm and DSP.
 *     - It is a periodical interrupt with a default frequency of <b> 60 Hz </b>.
 *     - It is used by Arm to issue generic / encode DSP commands.
 *     - DSP will report generic system related information from messages.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep vdsp
 *       @endcode
 *     - IAV create the vdsp proc file for vdsp interrupt. User operations can sync to this interrupt
 *       use the proc file. example: @ref poll_irq_sync_usage_drv
 *   - @b vcap - This interrupt is signaled to Arm, when DSP finishes processing one image digital
 * signal processing (IDSP) stage of a single slice for one frame in IDSP stage.
 *     - There are two IDSP stages, one is Raw to YUV stage, and the other one is YUV processing stage.
 *     - All the channels share the same vcap interrupt handler.
 *     - It is not a periodical interrupt. The frequency is the sum of IDSP stage number multiplied by
 * frame slice number. For example, two channels like channel 0 IDSP out is 10fps with 4 slices, while
 * channel 1 DSP output is 30fps with 2 slices, then the total @b vcap interrupt number is @b 100
 * (10 x 4 + 30 x 2) per second.
 *     - DSP will report canvas YUV data, when DSP finishes processing one frame's last stage of the last slice.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep vcap
 *       @endcode
 *     - IAV create the vcap proc file for vcap interrupt. User operations can sync to this interrupt
 *       use the proc file. example: @ref poll_irq_sync_usage_drv
 *   - @b venc - This interrupt is generated by VDSP encoder. It is signaled to Arm, when DSP
 * finishes encoding 1 frame or 1 slice of bit stream data.
 *     - It is shared by all the encoded streams.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep venc
 *       @endcode
 *     - IAV create the venc proc file for venc interrupt. User operations can sync to this interrupt
 *       use the proc file. example: @ref poll_irq_sync_usage_drv
 *   - @b async - This interrupt is an asynchronization interrupt between Arm and DSP. It is a new
 * mechnism for Arm and DSP to exchang cmd / msg instantly.
 *     - It is used by Arm to issue IDSP / VIN / VDSP related commands.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep async
 *       @endcode
 *   - @b vin - This interrupt is signaled to Arm from DSP to report VIN relates messages,
 * such as RAW data status msg.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep vin
 *       @endcode
 *   - @b vpostp - This interrupt is signaled to Arm, when DSP finishes processing one custom scalar job,
 * which is in YUV processing stage.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep vpostp
 *       @endcode
 *   - @b vcodec - This interrupt is signaled to Arm from DSP to report codec relates messages.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep vcodec
 *       @endcode
 *
 * There are 3 interrupts generated for each VOUT controller.
 *   - @b voutc0 - This interrupt is signaled to Arm, when DSP finishes sending 1 frame to VOUT A.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep voutc0
 *       @endcode
 *   - @b voutc1 - This interrupt is signaled to Arm, when DSP finishes sending 1 frame to VOUT B.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep voutc1
 *       @endcode
 *   - @b voutc2 - This interrupt is signaled to Arm, when DSP finishes sending 1 frame to VOUT C.
 *     - Users can check this interrupt via:
 *       @code
 *       board # cat /proc/interrupts | grep voutc2
 *       @endcode
 *
 * - - - -
 *
 * @section iav_encode_flow 5. Encoding Data Flow
 *
 * <ul>
 * <li> @ref sec_encode_concepts
 * <li> @ref sec_encode_relation
 * <li> @ref sec_encode_states
 * <li> @ref sec_encode_stream
 * </ul>
 *
 * @subsection sec_encode_concepts 5.1 Concepts
 *
 * ### Encode Mode
 * Currently, Cooper platforms support the following encoding modes:
 *   - (Mode 0) Advanced ISO mode
 *   - (Mode 1) Multi-region dewarp mode
 *   - (Mode 5) HDR line interleaved mode
 *   - (Mode 8) Image pipeline only mode (Only for EIS source channel)
 *
 * Each mode works for a typical case or specific product type. Among these modes, there are
 * many differences in image quality, encode performance, and the system resource configuration. Refer to
 * @ref fs_adv_enc_mode to learn more details about the configuration and limitation of the encode mode.
 *
 * ### Channel
 * The channel (demonstrated in the figure below) enables the system to support multiple sensors on
 * one Cooper SoC. A channel is an independent unit that captures and processes raw data from
 * an arbitrary sensor connected to Cooper SoC. Each channel has a separate 3A control process,
 * which can include multiple source buffers (up to six for single-pass IDSP scalers).
 * Since Cooper SoCs supports multiple VIN controllers natively, they can support multiple
 * independent (four-lane) sensors into separate VIN controllers as multi-channel inputs.
 *
 * For VIN controller, each one supports either one sensor or multiple sensors by bridge SERDES.
 * Different VIN controllers can connect with different setting of sensors (different resolutions,
 * sensor mode and sensor frame rate).
 *
 * Each channel supports only one sensor. Different channels can connect from either different sensor,
 * or from the same sensor as "IDSP virtual channels". Users can find more multi-channel information
 * from the document @ref fd_adv_multi_vin "ADVANCED - Multi-VIN & Multi-Channel".
 *
 * @image html iav_channel.jpg "Figure 5-1. Channel."
 *
 * ### Source Buffer
 * Each channel has up to five source buffers: the main, the second, the third, the fourth, and
 * the fifth. These five buffers are filled with YUV data from sensor / decoder / other output
 * devices in real time. They have the same content with their channel's source VIN device. If
 * the channel's pyramid buffers are disabled, it can be used to generate sixth source buffer.
 *
 * See @ref fs_basic_source_buffer "Source Buffer".
 *
 * ### Canvas Buffer
 * The canvas buffers are referred to as encode source buffers. They are also the containers of
 * all channels' source buffers. In the multi-channel design, every channel's source buffer (from
 * the main to the 6th buffer) can output the data with different resolutions independently. The
 * application can put the final outputs of source buffers together into one canvas so that the
 * stream encoded from this canvas can cover several field of views (FoVs) from different VIN
 * channels. Alternatively, the application can encode several streams cropped from different
 * areas of one canvas separately.
 * Currently, CV5x / CV7x can support up to 20 canvases.
 *
 * In <b>Case A</b>, a stream is encoded with the same size and FoV as its source canvas.
 *
 * In <b>Case B</b>, a stream is encoded with a cut-out area and smaller FoV than its source canvas.
 *
 * The above cases are two possible ways for a stream encoded from a source canvas. Since the source
 * canvas contains the source buffers that have already been cropped and scaled from its channel's
 * VIN, the streams can neither be in higher resolution than their source canvases, nor can they be
 * scaled down from the source canvases. For example, if VIN is 1080p and the size of source canvas
 * is 720p (has only one source buffer which is downscaled and has the same FoV with VIN), all
 * streams encoded from this source canvas can only be up to 720p. If one stream is smaller than
 * 720p in size, it must be cut out from the source canvas which sacrifices its FoV. As to one
 * channel with single sensor, each canvas has only one source buffer.
 * @image html iav_source_canvas.jpg "Figure 5-2. Source Canvas."
 *
 * See @ref fs_basic_canvas "Canvas".
 *
 * ### Encode Stream
 * The encode stream is a stream during the state of encoding or preparing for encoding. It can be
 * in H.265, H.264 or MJPEG format, with various resolution, GOP configuration, frame rate, and
 * other properties.
 *
 * Currently, CV5x / CV7x can support up to <b>20 encode streams</b>.
 *
 * In the Cooper Linux SDK design, streams are independent of each other. The application can
 * start / stop encoding one stream independently without affecting other running streams.
 *
 * Additionally, each encoding stream format (H.265, H.264 or MJPEG) reconfiguration does not affect
 * other encode streams, as long as the total resource is within the system limit.
 *
 *
 * @subsection sec_encode_relation 5.2 Relationships and Data Flow
 *
 * ### A. Source Canvas and Encode Stream Relationship
 * The maximum number of streams supported by one source canvas is the same as the maximum number
 * of streams that can be encoded at the same time. (e.g., if a system can support 8 streams, all
 * streams can be encoded from the same source canvas.)
 * @image html iav_canvas_relation.jpg "Figure 5-3. Source Canvas and Encoded Stream Relationship."
 *
 * <b>Currently, each channel can support up to five source buffers. The size of the sub-source
 * buffer must be no larger than the size of the main source buffer.</b>
 *
 * The size of the main source buffer can be up to 8K (7680x4320) for CV5x, and up to 4K (3840x2160)
 * for CV72.
 *
 * All source buffers have a default resolution in IAV driver and can be reconfigured. However,
 * since the encode stream depends on the source canvas which contains the final output of source
 * buffers, the source buffer can be only configured when there is no active encode stream running
 * on its source canvas.
 *
 * Similarly, reconfiguring the main source buffer will also affect the other sub source buffer
 * within same channel. Thus, it is necessary to go to the idle state before reconfiguring the main
 * source buffer. In other words, in current Cooper IAV implementation, if the application
 * must reconfigure the main source buffer format, it must first enter into the idle state.
 *
 * The upper figure shows one example of the relationship between the source canvases and encoded
 * streams. There are no restrictions on which source canvases can be used to encode a stream. The
 * source canvas can be configured so that all streams are encoded from one canvas, or each stream
 * is encoded from an independent source canvas.
 *
 * ### B.	Multiple Source Buffer Relationship
 * @image html iav_source_relation.jpg "Multiple Source Buffers Relation."
 *
 * Within a channel, the second, third, fourth, fifth and sixth source buffers are re-scaled
 * (scaled up or scaled down) from the main buffer. They can do digital PTZ (DPTZ type II) on the fly.
 * Also, the main buffer can do digital PTZ (DPTZ type I) on the fly.
 *
 * DPTZ type I will affect all its sub buffers within a channel, since the main buffer is their
 * source. However, it will not affect the sub buffers of other channels. Because of the source
 * buffer relationship, in order to have several streams with different resolutions, which are all
 * scaled down with full FoV, it is necessary that each stream has an independent source canvas
 * which contains only one scaled source buffer. This also affects overlay blending.
 *
 * ### C. Synonyms/Exchangeable Terms
 * <table>
 * <caption id="source_buffer"></caption>
 * <tr><th> IAV/DSP Driver Domain     <th> Unit Test Application Domain       <th> Comments
 * <tr><td> Capture buffer / Source buffer / Cap source <td>Source buffer
 *     <td> Buffers comprises canvas that is encoding/preview source.
 * <tr><td rowspan="2"> Main source / capture Buffer <td rowspan="2"> Main source buffer
 *     <td> Always exists, same or smaller than VIN.
 * <tr><td> Buffer size up to 8192x8192 for CV5x, up to 4096x4096 for CV7x.
 * <tr><td rowspan="2">Preview C buffer <td rowspan="2">Second source buffer
 *     <td> Encode source buffer, can be turn off. It is usually configured to be 480p or less.
 * <tr><td> Buffer size up to 3840x4096 for CV5x and CV7x.
 * <tr><td rowspan="2"> Preview B buffer
 *     <td rowspan="2"> Third source buffer
 *     <td> Can be configured as a source buffer for encode, or for VOUT B, or to turn off. It is usually configured to be 1080p or less.
 * <tr><td> Buffer size up to 7680x8192 for CV5x, up to 3840x4096 for CV7x.
 * <tr><td rowspan="2">Preview A buffer
 *     <td rowspan="2">Fourth source buffer
 *     <td> Can be configured as a source buffer for encode, or for VOUT A, or to turn off. It is usually configured to be 720p or less.
 * <tr><td> Buffer size up to 7680x8192 for CV5x, up to 3840x4096 for CV7x.
 * <tr><td rowspan="2">Preview D buffer
 *     <td rowspan="2">Fifth source buffer
 *     <td> Can be configured as a source buffer for encode, or for VOUT B, or to turn off. It is usually configured to be 1080p or less.
 * <tr><td> Buffer size up to 7680x8192 for CV5x, up to 3840x4096 for CV7x.
 * <tr><td rowspan="2">(Only available in second pass)
 *     <td rowspan="2">Sixth source buffer
 *     <td> Encode source buffer, can be turn off, up to 7680x8192 for CV5x, and up to 3840x4096 for CV7x.
 * <tr><td> Only available for CV2x, not for S6LM.
 * </table>
 *
 * @note
 * - Those buffer size follow: <b>VIN >= Main Buffer >= Sub Prev Buffer</b>.
 * - Regarding CV2 8K user case, please contact the Ambarella support team.
 *
 *
 * @subsection sec_encode_states 5.3 Encoding States
 *
 * There are several different states that correspond to different concepts in encoding.
 * IAV encoding state:  At least one of the streams is in encoding.
 * Stream encoding state:  The encoding state is independent for each stream.
 * \n IAV encoding = "stream 1 in encoding" OR \n
 * \t "stream 2 in encoding" OR \n
 * \t "stream 3 in encoding" OR ... \n
 * The source buffer has two states, @a IDLE or @a BUSY.
 * If there is at least one stream encoding on the current buffer, then it is in @a BUSY state;
 * otherwise, it is in @a IDLE state.
 *
 * @subsection sec_encode_stream 5.4 Stream States
 * 1. @e <b>Unknown:</b> The stream is un-initialized or un-configured.
 * 2. <em><b>Ready for encoding:</b></em> The stream is configured and ready for encoding, but has not started yet.
 * 3. @e <b>Starting:</b> The stream start command is issued to DSP, while DSP does not generate the first encode frame yet.
 * 4. @e <b>Encoding:</b> The stream has already started to encode.
 * 5. @e <b>Stopping:</b> The stream stop command is issued to DSP, while DSP does not generate the "stream end" NULL frame yet.
 *
 * - - - -
 *
 * @section iav_decode 6. Decoding Data Flow
 *
 * When preparing decoding data in decode mode, Arm and DSP share the same ring-buffer, known as bitstream
 * buffer. IAV allocates and maintains this bitstream buffer for user application. User application
 * accesses it via mmap (@ref IAV_PART_DEC_BSB). When preparing data into the bitstream buffer, user
 * application should do as follows:
 *
 * a) Wait for the bitstream buffer to have enough free space which is released by DSP. This is to prevent data
 * from being overwritten. The space can be checked via @ref IAV_IOC_WAIT_DECODE_BSB.
 *
 * b) The fed data should be continuous in memory and there should be no gap between the current and
 * the next data chunk. Also, user application should take care of the ring buffer wrapper around
 * case. The data chunk sent to the DSP begins with the start_pointer (include this byte) and ends
 * with the end_pointer (not include this byte).
 *
 * - - - -
 *
 * @section iav_sysfs_info 7. IAV Sysfs Info
 *
 * IAV driver supports to report IAV related state info via sysfs in CV2x / S6LM SDK. There are
 * 3 sysfs files named @b iav_info, @b iav_state, and @b iav_error. Their location is under
 * "/sys/devices/platform/iav/monitor/". Because the data format which sysfs files provided is binary,
 * so user application should not use "cat" cmd to read these files. The data structures used in these
 * sysfs files are defined as below. This module is mainly used for function safety, which means the
 * application could use epoll to monitor these files. When some error happens, the application would
 * receive the error report and get the error information. So it can help the application to do error
 * handling and increase system stability at the same time.
 *
 * @subsection iav_sysfs_file 7.1 IAV sysfs files
 *
 * - @b iav_info - This file provides current IAV information. The application can read them out at anytime.
 * The data structure used by iav_info file is defined as below.
 *   @sa iav_sysfs_info_msg
 * - @b iav_state - This file can be monitored by epoll in the user space. When the IAV state is changed,
 *   epoll would return and application can read the state changing information from it. The data structure
 *   used by iav_state file is defined as below.
 *   @sa iav_sysfs_state_msg
 * - @b iav_error - This file can also be monitored by epoll like iav_state file. When error happens in IAV,
 *   epoll would return and application can read the error information from it. The data structure used by
 *   iav_error file is defined as below.
 *   @sa amba_sysfs_error_msg
 *
 * example: @ref usage_sysfs
 *
 * - - - -
 *
 * @section iav_proc_info 8. IAV Procfs Info
 *
 * IAV driver uses procfs to expose some IAV related debug information in Cooper SDK.
 *
 * @subsection iav_state_info 8.1 IAV State Info
 *
 * User can use proc file to show the current IAV status. The debug option proc file is
 * <b>"/proc/ambarella/iav_state"</b>.
 *
 * Here is the example shown the IAV state print, when IAV is in encoding state.
 * @code {.c}
 * # cat /proc/ambarella/iav_state
 * AMBARELLA_CHIP=CV5
 * dsp_op_mode: 2
 * dsp_encode_state: 1
 * dsp_encode_mode: 5
 * DSP DRAM: used 318 MB, total 2304 MB
 * DSP_CV DRAM: used 0 MB, total 1 MB
 * @endcode
 *
 * Below describes the information for each line:
 *   - AMBARELLA_CHIP:   This shows the current chip name for the Cooper family.
 *   - dsp_op_mode:      This shows the current DSP operation mode, 0: Init; 1: Idle; 2: Encode; 3: Decode
 *   - dsp_encode_state: This shows the current DSP state for encode pipeline, 0: Idle; 1: Running
 *   - dsp_encode_mode:  This shows the IDSP pipeline, also named encoding mode. See @ref sec_encode_concepts.
 *   - DSP DRAM:         This shows the used and total DSP DRAM size.
 *   - DSP_CV DSP DRAM:  This shows the used and total DRAM size shared by DSP and CV, for encode mode 9.
 *
 * @subsection iav_memory_info 8.2 IAV Memory Info
 *
 * User can use proc file to check the current IAV/DSP memory usage. The debug option proc file is
 * <b>"/proc/ambarella/iav_mem"</b>.
 *
 * Here is the example shown the IAV/DSP memory usage, when IAV is in encoding state.
 * @code {.c}
 * # cat /proc/ambarella/iav_mem
 * DSP Dram:
 * DSP DRAM Used: 318 MB, Limited: 2304 MB.
 * Shared DSP CV DRAM Used: 0 MB, Limited: 1 MB.
 * Dram Bandwidth:
 * Chip ID [0]: DSP memory bandwidth limit [23565 MB/s].
 * @endcode
 *
 * Below describes the information for each line:
 *   - The current DSP DRAM size used by DSP is 318 MB, and the total DSP memory size is 2304 MB.
 *   - The current DSP CV shared DRAM size is 0 MB, and the total memory size is 1 MB.
 *   - The current used DRAM memory bandwidth limit is 23565 MB/s.
 *
 * @subsection iav_feature_debug 8.3 IAV Feature Debug
 *
 * If users encounter some problems with some features such as EFM or manual feed, there is a debug option which
 * can be switched on to output more kernel messages related to those features. The debug option proc file is
 * <b>"/proc/ambarella/iav_feature_print"</b>.
 *
 * The configuration below is required to enable this feature.
 * @code {.c}
 * build $ make menuconfig
 *		[*] drv_modules  --->
 *			[*]   private  --->
 *				-*- ambvideo-header (drv_modules/private/video/dsp_v6)  --->
 *					[*]   Enable iav feature debug
 * @endcode
 *
 * The default IAV feature print setting is provided as shown below.
 * @code {.c}
 * # cat /proc/ambarella/iav_feature_print
 * The current feature print bitmap: 0xffffff80
 * The last feature print bitmap: 0xffffffff
 * EFM:                    bit[0]: disable
 * RAW Encode:             bit[1]: disable
 * RAW Manual Feed:        bit[2]: disable
 * Pyramid Manual Feed:    bit[3]: disable
 * Canvas Manual Feed:     bit[4]: disable
 * IMG Scaler:             bit[5]: disable
 * VOUT Msg:               bit[6]: disable
 * @endcode
 *
 * Users can set the corresponding bit(s) to enable EFM and canvas manual feed printing.
 * @code {.c}
 * # echo 0xffffff91 > /proc/ambarella/iav_feature_print
 * # cat /proc/ambarella/iav_feature_print
 * The current feature print bitmap: 0xffffff91
 * The last feature print bitmap: 0xffffff80
 * EFM:                    bit[0]: enable
 * RAW Encode:             bit[1]: disable
 * RAW Manual Feed:        bit[2]: disable
 * Pyramid Manual Feed:    bit[3]: disable
 * Canvas Manual Feed:     bit[4]: enable
 * IMG Scaler:             bit[5]: disable
 * VOUT Msg:               bit[6]: disable
 * @endcode
 *
 * @subsection iav_ioctl_arg_print_function 8.4 IAV IOCTL Arguments Print
 * This function is used to print the arguments of IAV IOCTL APIs at runtime.
 * Through it, users can check whether the input parameters of each IAV IOCTL API are prepared correctly by user app or not.
 * The total number of IAV IOCTL APIs is nearly 130. They are classified into 16 categories for the arguments print.
 * Each category uses one bit to enable/disable printing their arguments.
 *
 * Example 1: IAV IOCTL Categories and Corresponding Bitmap.
 * @code {.c}
 * board# cat /proc/ambarella/iav_ioc_arg_print
 * The current IOCTL category bitmap: 0x0
 * The last IOCTL category bitmap: 0x0
 * System:                 bit[0]: disable
 * VIN:                    bit[1]: disable
 * VOUT:                   bit[2]: disable
 * Pyramid:                bit[3]: disable
 * EFM:                    bit[4]: disable
 * EFR:                    bit[5]: disable
 * Memory Management:      bit[6]: disable
 * Stream:                 bit[7]: disable
 * Overlay Blur:           bit[8]: disable
 * Vcap:                   bit[9]: disable
 * Warp:                   bit[10]: disable
 * VProc:                  bit[11]: disable
 * VIN IDSP:               bit[12]: disable
 * Debug:                  bit[13]: disable
 * Decoder:                bit[14]: disable
 * Image Scaler:           bit[15]: disable
 * @endcode
 *
 * Example 2: Turn on IAV IOCTL Arg print and Check Dmesg Log.
 * @code {.c}
 * board# echo 0x00000001 > /proc/ambarella/iav_ioc_arg_print
 * board# cat /proc/ambarella/iav_ioc_arg_print
 * The current IOCTL category bitmap: 0x1
 * The last IOCTL category bitmap: 0x0
 * System:                 bit[0]: enable
 * .
 * .
 * .
 * <--Run an app which uses IAV IOCTLs to output the dmesg log. Like: test_encode-->
 * .
 * board# dmesg
 * <--Below is the iav ioctl arg print log. Example: IOCTL---IAV_IOC_GET_PYRAMID_CFG-->
 * [ 6747.968267] IOCTL BEGIN: IAV_IOC_GET_PYRAMID_CFG
 * [ 6747.968270] struct iav_pyramid_cfg
 * [ 6747.968273]     chan_id = 0
 * [ 6747.968278]     enable = 0
 * [ 6747.968280]     input_buf_id = 4
 * [ 6747.968283]     layers_map = 0x0
 * [ 6747.968285]     manual_feed = 0
 * [ 6747.968288]     set_min_unlocked_buf_num = 0
 * [ 6747.968290]     item_num = 4
 * [ 6747.968293]     scale_type = 0
 * [ 6747.968298]     buf_addr = 0
 * [ 6747.968300]     buf_size = 0
 * [ 6747.968302]     frame_rate = 0
 * [ 6747.968304]     min_unlocked_buf_num = 0
 * [ 6747.968307]     max_layers_map = 0x0
 * [ 6747.968309]     enable_frame_tag = 0
 * [ 6747.968312]     cached_items = 1
 * [ 6747.968317]     rescale_size.width = 0
 * [ 6747.968319]     rescale_size.height = 0
 * [ 6747.968322]     max_rescale_size.width = 0
 * [ 6747.968324]     max_rescale_size.height = 0
 * [ 6747.968327]     frame_tag.value = 0
 * [ 6747.968329]     frame_tag.mask = 0x0
 * [ 6747.968334]     frame_rate_hp = 0x0
 * [ 6747.968336] IOCTL END: IAV_IOC_GET_PYRAMID_CFG
 * @endcode
 * <BR>
 *
 * - - - -
 *
 * @section dsp_proc_info 9. DSP Procfs Info
 *
 * @subsection iav_optional_dsp_cmd_print 9.1 Optional DSP command printing
 *
 * In Cooper SDK, a switch to enable and disable some commands printing dynamically is implemented.
 * To switch off certain kind of command for better debug is supported. The switch is implemented
 * by reading and writing <b>"/proc/ambarella/dsp_print"</b>.
 *
 * Show the default DSP printing setting:
 * @code {.c}
 * # cat /proc/ambarella/dsp_print
 * The current dsp print bitmap: 0xbfffff3f
 * The last dsp print bitmap: 0xffffffff
 * DSP_CMD_PRINT_GEN:      bit[0]: enable
 * DSP_CMD_PRINT_VPROC:    bit[1]: enable
 * DSP_CMD_PRINT_VIN:      bit[2]: enable
 * DSP_CMD_PRINT_VOUT:     bit[3]: enable
 * DSP_CMD_PRINT_VENC:     bit[4]: enable
 * DSP_CMD_PRINT_VDEC:     bit[5]: enable
 * DSP_CMD_PRINT_IMG:      bit[6]: disable
 * DSP_CMD_PRINT_VDEC_MORE bit[7]: disable
 * UNUSED: bit[8]: enable
 * UNUSED: bit[9]: enable
 * UNUSED: bit[10]: enable
 * ...
 * UNUSED: bit[28]: enable
 * UNUSED: bit[29]: enable
 * DSP_CMD_PRINT_RAW:      bit[30]: disable
 * DSP_CMD_PRINT_MORE:     bit[31]: enable
 * @endcode
 *
 * Reset the default DSP printing setting to enable IMG 3A related printing:
 * @code {.c}
 * # echo 0xbffff836 > /proc/ambarella/dsp_print
 * # cat /proc/ambarella/dsp_print
 * The current dsp print bitmap: 0xbfffff7f
 * The last dsp print bitmap: 0xbfffff3f
 * DSP_CMD_PRINT_GEN:      bit[0]: enable
 * DSP_CMD_PRINT_VPROC:    bit[1]: enable
 * DSP_CMD_PRINT_VIN:      bit[2]: enable
 * DSP_CMD_PRINT_VOUT:     bit[3]: enable
 * DSP_CMD_PRINT_VENC:     bit[4]: enable
 * DSP_CMD_PRINT_VDEC:     bit[5]: enable
 * DSP_CMD_PRINT_IMG:      bit[6]: enable
 * DSP_CMD_PRINT_VDEC_MORE bit[7]: disable
 * UNUSED: bit[8]: enable
 * UNUSED: bit[9]: enable
 * UNUSED: bit[10]: enable
 * ...
 * UNUSED: bit[28]: enable
 * UNUSED: bit[29]: enable

 * @endcode
 *
 *
 * <BR>
 *
 * @subsection iav_dsp_state_proc_file 9.2 DSP state
 * Users need to pay attention to two states of DSP when the system is running:
 * 1. Assertion state. When some behaviors unsupported by DSP occur, DSP will enter assertion state and
 * stop running, and Linux will lose communication with DSP.
 * Users must reboot to recover it.
 * 2. Abnormal state.  When DSP detects abnormal clock information or lose it for a long time,
 * it will enter abnormal state.
 * Users can re-enter PREVIEW with right clock information to recover it.
 *
 * Users can get DSP state by reading <b>"/proc/ambarella/dsp_state"</b> as below. This file is read-only.
 *
 * Show the default DSP state:
 * @code {.c}
 * # cat /proc/ambarella/dsp_state
 * The current dsp state bitmap:	0x0
 * [bit0] DSP_STATE_ASSERT  :	not assert
 * [bit1] DSP_STATE_ABNORMAL:	normal
 * @endcode
 *
 * If something unexpected happened, users will get messages as below:
 * @code {.c}
 * # cat /proc/ambarella/dsp_state
 * The current dsp state bitmap:	0x1
 * [bit0] DSP_STATE_ASSERT  :	assert!
 * [bit1] DSP_STATE_ABNORMAL:	normal
 * @endcode
 * or
 * @code {.c}
 * # cat /proc/ambarella/dsp_state
 * The current dsp state bitmap:	0x2
 * [bit0] DSP_STATE_ASSERT  :	not assert
 * [bit1] DSP_STATE_ABNORMAL:	abnormal!
 * @endcode
 *
 * <BR>
 * - - - -
 *
 *
 * @section iav_poll 10. Poll interface
 *
 *
 * @subsection drv_query_iav_data 10.1 Poll interface to query IAV data
 *
 * IAV driver supports poll interface to query the iav data. It waits for one of a set of events to
 * become ready to perform I/O. These events include the  @b IAV_DESC_FRAME, @b IAV_DESC_STATIS,
 * @b IAV_DESC_RAW, @b IAV_DESC_CANVAS, @b IAV_DESC_PYRAMID, @b IAV_DESC_SLICE, @b IAV_DESC_PRE_COUNT
 * and so on. The caller should specify the events of interested before the poll. And then using the
 * poll API wait the events ready. This feature supports the multiple users and can poll multiple
 * events at one time.
 *
 * example: @ref poll_iav_data_usage_drv
 *
 * @subsection drv_irq_sync 10.2 Poll interface to sync irq
 *
 * IAV driver supports to use standard poll mechanism to synchronize with different DSP interrupts.
 * With this feature users can synchronize their operations to the interrupt. IAV driver supports
 * the vcap, vdsp, and venc interrupt sync now. IAV driver creates vcap, vdsp, and venc proc file
 * for interrupt sync. Vcap proc file is created for per channel and venc proc file is created for
 * per stream. Users can use the proc file to synchronize the certain interrupt, please check
 * unit_test/private/iav_test/arch_v5/test_irq_sync.c
 *
 * example: @ref poll_irq_sync_usage_drv
 *
 * - - - -
 *
 * @section iav_example 11. Example Usage of APIs
 *
 * In order to encode a stream, the general work flow of IAV driver is as follows.
 *
 * <ol>
 *   <li> @ref usage_open                 "Open the Device"
 *   <li> @ref usage_mem                  "Map Bitstream Memory"
 *   <li> @ref usage_vin                  "Init VIN Controller"
 *   <li> @ref usage_vout_config          "Init VOUT Controller"
 *   <li> @ref usage_go_to_idle           "Go to Idle from Init"
 *   <li> @ref usage_dsp_configuration    "Configure DSP Resource"
 *   <li> @ref usage_enter_preview        "Enter Preview State"
 *   <li> @ref usage_stream_configuration "Configure Stream Parameters"
 *   <li> @ref usage_start_encode         "Start Encode"
 *   <li> @ref usage_bsb                  "Query Bitstream Data"
 *   <li> @ref usage_stop_encode          "Stop Encode"
 * </ol>
 *
 * Some other features examples are listed below:
 * <ul>
 *   <li> @ref usage_sysfs                "Sysfs Usage"
 *   <li> @ref usage_poll_interface_drv   "Poll Interface"
 *   <li> @ref usage_return_value         "IOCTL Return Values"
 * </ul>
 *
 * The following code fragment is an example which shows the flow of the user application.<br>
 *
 * @code {.c}
 * int main()
 * {
 *   int fd_iav = open("/dev/iav", O_RDWR, 0);  // open iav device
 *   ...
 *   map_bsb();
 *   init_vin(fd_iav, 0);
 *   vout_init(fd_iav);
 *
 *   goto_idle();                      // go to "idle state", system resources are configurable only in idle state
 *
 *   set_system_resource();            // set the system resources limit
 *   set_dptz_buffer();                // configure the dptz for source buffer
 *   set_pyramid();                    // set the pyramid if needed.
 *
 *   enable_preview();
 *
 *   set_encode_format(stream_0);      // set encode format of stream 0
 *   start_encode(0x01);               // start encode for stream 0
 *
 *   ...
 *   // do something for a period
 *   ...
 *
 *   stop_encode();
 *   goto_idle();
 *   ...
 *
 *   return 0;
 * }
 * @endcode
 *
 * In the main function, it shows the general sequence of encoding control. For more details, please
 * check the source code of @ref test_encode.c.
 *
 * The following is a detailed description of the related functions.
 *
 *
 * @subsection usage_open 11.1 Open the Device
 *
 * The main device node of the IAV driver is @c /dev/iav. The user program needs to call @c open() to open
 * the device and get its file handler. Other APIs are called by @c ioctl() system calls, which need
 * the file handler, command code, and the corresponding parameters.
 *
 * @code {.c}
 * int fd_iav;
 *
 * if ((fd_iav = open("/dev/iav", O_RDWR, 0)) < 0) {
 *     //open fails
 *     return -1;
 * }
 * ...
 * close(fd_iav);
 * @endcode
 *
 *
 * @subsection usage_mem 11.2 Memory Management
 *
 * When the encoding is initiated, the DSP will generate a bit stream to an internal buffer, which
 * is allocated by the driver. For any user space program to access the buffer efficiently, the buffer
 * needs to be mapped to the user space, then the program can have the direct access to it.
 *
 * The <b>Bit Stream Buffer (BSB)</b> information can be queried by calling the ioctl #IAV_IOC_QUERY_MEMBLOCK
 * with the Partition ID #IAV_PART_BSB. The BSB physical address and length are returned in the information
 * data structure.
 *
 * The user space program can get the virtual address via mmap system call. Since BSB is a ring buffer,
 * when the frame's start address plus frame size exceed the BSB length, DSP will wrap around the data
 * and write from the beginning of BSB again. So, usually <b>double mmap (double the BSB buffer size)</b>
 * will be used to avoid special handling for the warp around issue.
 *
 * @code {.c}
 * struct iav_querymem query_mem;
 * struct iav_mem_part_info *part_info;
 *
 * memset(&query_mem, 0, sizeof(query_mem));
 * query_mem.mid = IAV_MEM_PARTITION;
 * part_info = &query_mem.arg.partition;
 * part_info->pid = IAV_PART_BSB;
 * if (ioctl(fd_iav, IAV_IOC_QUERY_MEMBLOCK, &query_mem) < 0) {
 * 	perror("IAV_IOC_QUERY_MEMBLOCK");
 * 	return -1;
 * }
 *
 * bsb_size = part_info->mem.length;
 * bsb_mem = mmap(NULL, bsb_size * 2, PROT_READ, MAP_SHARED, fd_iav,
 * 	        part_info->mem.addr);
 * if (bsb_mem == MAP_FAILED) {
 * 	perror("mmap IAV_PART_BSB failed\n");
 * 	return -1;
 * }
 * @endcode
 *
 * When encoding is started, the user space program can call another ioctl command #IAV_IOC_QUERY_DESC
 * with the ID #IAV_DESC_FRAME, to fetch the encoded frames from the bit stream buffer.
 *
 *
 * @subsection usage_vin 11.3 Configure VIN
 *
 * The following code checks the total VIN source and sets the specified VIN as the active source.
 *
 * @code {.c}
 * int init_vin(int vsrc_id, int hdr_mode)
 * {
 *   struct vindev_mode src_mode = {0};
 *   struct vindev_fps vsrc_fps = {0};
 *   struct vindev_video_info video_info;
 *
 *   vsrc_mode.vsrc_id = 0;                            // choose vsrc 0
 *   vsrc_mode.video_mode = AMBA_VIDEO_MODE_1920_1080; // sensor resolution: 1920x1080
 *   vsrc_mode.hdr_mode = 0;                           // liner input mode
 *   vsrc_mode.bits = 12;                              // set the pixel depth to 12
 *   ...
 *   ioctl(fd_iav, IAV_IOC_VIN_SET_MODE, &vsrc_mode);
 *
 *   // set sensor input frame rate to 30
 *   vsrc_fps.vsrc_id = 0;
 *   vsrc_fps.fps = 30;
 *   ...
 *   ioctl(fd_iav, IAV_IOC_VIN_SET_FPS, &vsrc_fps);
 *
 *   // do something, such as set the aaa parameters for rgb sensor
 *   ...
 *
 *   // also, user can get current video info by ioc
 *   memset(&video_info, 0, sizoef(struct vindev_video_info));
 *   video_info.vsrc_id = 0;
 *   video_info.info.mode = AMBA_VIDEO_MODE_CURRENT;
 *   ioctl(fd_iav, IAV_IOC_VIN_GET_VIDEOINFO, &video_info);
 *
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsection usage_vout_config 11.4 Configure VOUT
 *
 * CV5x / CV7x supports HDMI (digital) VOUT, the composite (analog) VOUT, and MIPI DSI / CSI VOUT.
 *
 * HDMI VOUT can support up to 8K resolution. More details can be found in the unit test sample codes.
 *
 * The following is an example on how to use ioctl @ref IAV_IOC_VOUT_SET_MODE to configure the VOUT
 * parameters.
 *
 * @code {.c}
 * int vout_init(int fd)
 * {
 *   struct voutdev_format format;
 *
 *   format.id = 2;                             // use vout2 controller
 *   format.type = VOUT_TYPE_HDMI;              // use HDMI output
 *   format.mode = AMBA_VIDEO_MODE_1920_1080;   // resolution 1920x1080
 *   format.fps = 60 * 1000;                    // fps is 60
 *   ...
 *
 *   ioctl(fd, IAV_IOC_VOUT_SET_MODE, &format);
 *
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsection usage_go_to_idle 11.5 Go To Idle State
 * Set the IAV to @ref anchor_state_idle "Idle State".
 * @code {.c}
 * int goto_idle(int vin_off)
 * {
 *   struct iav_idle_params idle_params = {0};
 *   u32 state;
 *
 *  // set the vout profile
 *      AM_IOCTL(fd_iav, IAV_IOC_GET_IAV_STATE, &state);
 *      if (dsp_boot_param.vout_profile_flag && state != IAV_STATE_INIT) {
 *              printf("Error! vout profile should be set when first entering preview.\n");
 *              return -1;
 *      }
 *
 *   // maybe power off the vin controller is needed
 *   idle_params.poweroff_vin = vin_off;
 *   // call ioctl to enter preview
 *   ioctl(fd_iav, IAV_IOC_ENTER_IDLE, &idle_params);
 *
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsection usage_dsp_configuration 11.6 Configure DSP Resources
 *
 * Users can set the parameters of multi-channel configuration during @ref anchor_state_idle "Idle State".
 * Include <B>System Resources</B>, @ref ut_source_buffer and @ref ut_pryamid ...
 *
 *
 * @subsubsection ioc_configure_resource 11.6.1 Set System Resources Limitations
 *
 * The system resources contain the following aspects:
 * <ul>
 * <li> Global Parameters
 * <li> Channel Configuration
 * <li> Canvas Configuration
 * <li> Stream Configuration
 * </ul>
 * Following is an example about how to configure DSP system resources.
 * @code {.c}
 * int set_system_resource(void)
 * {
 *   struct iav_system_resource resource;          // for system resource ioc
 *   struct iav_chan_cfg chan_cfgs[IAV_MAX_CHANNEL_NUM];
 *   struct iav_canvas_cfg canvas_cfgs[IAV_MAX_CANVAS_BUF_NUM];
 *   struct iav_stream_resource stream_resources[IAV_STREAM_MAX_NUM_ALL];
 *   struct mcl_multi_chan_cfg resource_cfg;
 *
 *   // Here you can get your buffer configuration from a Lua file, or directly hard code in
 *   // a C resource file. For example, here we get configuration from Lua script.
 *   get_multi_chan_cfg("example.lua", &resource_cfg);
 *
 *   // set up some global parameters
 *   resource.encode_mode = 5;                     // use enc-mode 5
 *   resource.raw_capture_enable = 0;              // enable capture date from sensor
 *   ...
 *   // rise a ioc to set up system resource
 *   ioctl(fd_iav, IAV_IOC_SET_SYSTEM_RESOURCE, &resource);
 *
 *   // set up channel resource
 *   resource->chan_num = resource_cfg.chan_num;
 *   resource->chan_map = (1 << resource_cfg.chan_num) - 1;
 *   for (i = 0; i < resource->chan_num; i++) {
 *      channel = chan_cfgs[i];
 *      channel->vsrc_id = resource_cfg.channels[i].vsrc.vsrc_id;
 *      channel->pass_num = resource_cfg.channels[i].scale_pass_num;
 *      chan_cfg->raw_capture = resource_cfg.channels[i].raw_capture;
 *      ...
 *      for (j = 0; j < resource_cfg.channels[i].pass_num; j++) {
 *         //set up the pass resource
 *         ...
 *      }
 *      // rise a ioc to set up channel resource
 *      ioctl(fd_iav, IAV_IOC_SET_CHAN_CONFIG, &chan_cfgs[i]);
 *   }
 *
 *   // set up canvas resource
 *   resource->canvas_num = resource_cfg.canvas_num;
 *   resource->canvas_map = (1 << resource_cfg.canvas_map) - 1;
 *	 for (i = 0; i < resource_cfg.canvas_num; i++) {
 *		 canvas = &canvas_cfgs[i];
 *		 canvas->max.width = resource_cfg.canvas[i].width;
 *		 canvas->max.height = resource_cfg.canvas[i].height;
 *		 canvas->type = resource_cfg.canvas[i].type;
 *		 ...
 *       // rise a ioc to set up canvas resource
 *       ioctl(fd_iav, IAV_IOC_SET_CANVAS_CONFIG, &canvas_cfgs[i]);
 *	  }
 *
 *   // set up stream resource
 *	 for (i = 0; i < resource_cfg.stream_num; ++i) {
 *		 stream = &stream_resources[i];
 *	     stream->max_size.width = resource_cfg.streams[i].max_size.width;
 *	     stream->max_size.height = resource_cfg.streams[i].max_size.height;
 *	     stream->max_M = resource_cfg.streams[i].max_M;
 *       ...
 *       // rise a ioc to set up stream resource
 *       ioctl(fd_iav, IAV_IOC_SET_STREAM_RESOURCE, &stream_resources[i]);
 *   }
 *
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsubsection ioc_configure_dptz 11.6.2 Configure DPTZ for Source Buffer
 *
 * Digital Pan/Tilt/Zoom for @ref main_buffer_dptz "Main Buffer" and @ref sub_buffer_dptz "Sub-Buffer".
 * @code {.c}
 * int set_dptz_buffer()
 * {
 *   struct iav_video_proc vproc;                             // for source buffer ioc
 *   struct iav_dptz *dptz = &vproc.arg.dptz;
 *   struct iav_buf_cfg *buf_cfg = &vproc.arg.dptz.buf_cfg;
 *   struct mcl_multi_chan_cfg resource_cfg;

 *   // set up source buffer each channel
 *   vproc.cid = IAV_VIDEO_PROC_DPTZ;
 *   for (i = 0; i < resource_cfg.chan_num; i++) {
 *      //configure buffer for each pass
 * 	     for (j = 0; j < resource_cfg.channels[i].scale_pass_num; j++) {
 * 		    for (k = IAV_SRCBUF_FIRST; k < IAV_SRCBUF_LAST; k++) {
 *             buffer = &resource_cfg.channels[i].source_buffer[j][k];
 *             dptz->channel_id = i;
 *             dptz->pass_id = j;
 *             dptz->buf_id = k;
 *             buf_cfg->input = buffer->input;
 *             buf_cfg->output = buffer->output;
 *             buf_cfg->canvas_id = buffer->canvas_id;
 *             ioctl(fd_iav, IAV_IOC_CFG_VIDEO_PROC, &vproc);
 *         }
 *      }
 *   }
 *
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsubsection ioc_configure_pyramid 11.6.3 Configure Pyramid
 *
 * @ref ut_pryamid "Pyramid" is available on Amba CV family chips. The pyramid can be configured if
 * it is needed in application.
 * @code {.c}
 * int set_pyramid()
 * {
 *   struct iav_pyramid_cfg pyramid_cfg;                     // for pyramid ioc
 *   struct mcl_multi_chan_cfg resource_cfg;
 *
 *   for (i = 0; i < resource_cfg.chan_num; i++) {
 *      // configure pyramid for each channel
 *      pyramid = &resource_cfg.channels[i].pyramid;
 *      pyramid_cfg.enable = (pyramid->layers_map != 0);     // enable pyramid
 *      pyramid_cfg.input_buf_id = pyramid->input_buf_id;    // set the input buffer
 *      pyramid_cfg.layers_map = pyramid->layers_map;        // set the layers_map mask
 *      pyramid_cfg.scale_type = pyramid->scale_type;        // set dawn-sample rate
 *      pyramid_cfg.manual_feed = pyramid->manual_feed;      // if enable manual feed
 *      ...
 *
 *      ioctl(fd_iav, IAV_IOC_SET_PYRAMID_CFG, &pyramid_cfg);
 *   }
 *
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsection usage_enter_preview 11.7 Enter Preview State
 * The following is a sample code fragment to put the IAV to @ref anchor_state_preview "Preview State".
 * @code {.c}
 * int enable_preview(void)
 * {
 *   ioctl(fd_iav, IAV_IOC_ENABLE_PREVIEW, 0);
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsection usage_stream_configuration 11.8 Configure Stream
 * The following is a sample code fragment to set the stream parameters, such as encoding format,
 * resolution, source canvas...
 * @code {.c}
 * int set_encode_format(int id)
 * {
 *   struct iav_stream_cfg stream_cfg;
 *   struct iav_stream_format *format = &stream_cfg.arg.format;
 *
 *   stream_cfg.id = id;
 *   stream_cfg.cid = IAV_STMCFG_FORMAT;
 *   ioctl(fd_iav, IAV_IOC_GET_STREAM_CONFIG, &stream_cfg);
 *
 *   format->type = IAV_STREAM_TYPE_H264;   // encode as h264 format
 *   format->enc_win.width = 1920;          // set resolution as 1920x1080
 *   format->enc_win.height = 1080;
 *   format->enc_src_id = 0;                // set the source canvas
 *   ...
 *
 *   ioctl(fd_iav, IAV_IOC_SET_STREAM_CONFIG, &stream_cfg);
 *
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsection usage_start_encode 11.9 Start Encoding
 * Once the stream has been configured properly, users should call ioctl @ref IAV_IOC_START_ENCODE to start
 * encoding the specified stream. The parameters is a bitmap for the specified stream(s).
 * @code {.c}
 * int start_encode(u32 stream_mask)
 * {
 *   ioctl(fd_iav, IAV_IOC_START_ENCODE, stream_mask);
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsection usage_stop_encode 11.10 Stop Encoding
 * Also, users can stop the streams as needed. The mask bit of specified stream can be cleared, and
 * issued through ioctl @ref IAV_IOC_STOP_ENCODE.
 * @code {.c}
 * int stop_encode(u32 stream_mask)
 * {
 *   // stop the encoding stream
 *   ioctl(fd_iav, IAV_IOC_STOP_ENCODE, stream_mask);
 *   return 0;
 * }
 * @endcode
 *
 *
 * @subsection usage_bsb 11.11 Query Bit Stream Information
 *
 * The following code fragment shows the minimal steps required to query encoded bit stream information.
 *
 * 1. The system needs to be in the encoding state, that is to say at least one stream is encoding
 * with the specified stream type (H.264 / H.265 / MJPEG).
 *
 * 2. As described in @ref usage_mem, the BSB buffer should be <b>double mapped</b> for the application
 * to read out the bit stream information.
 *
 * 3. #IAV_IOC_QUERY_DESC starts to read out the bit stream information.
 *
 * For more details, please check the source code of "test_stream.c".
 *
 * @code {.c}
 * u32 bsb_size = 0;
 * u8 *bsb_mem = NULL;
 * struct iav_querymem query_mem;
 * struct iav_mem_part_info *part_info;
 *
 * struct iav_querydesc query_desc;
 * struct iav_framedesc *frame_desc = NULL;
 *
 * // Map BSB buffer for querying bit stream descriptor
 * memset(&query_mem, 0, sizeof(query_mem));
 * query_mem.mid = IAV_MEM_PARTITION;
 * part_info = &query_mem.arg.partition;
 * part_info->pid = IAV_PART_BSB;
 * if (ioctl(fd_iav, IAV_IOC_QUERY_MEMBLOCK, &query_mem) < 0) {
 * 	perror("IAV_IOC_QUERY_MEMBLOCK");
 * 	return -1;
 * }
 *
 * bsb_size = part_info->mem.length;
 * bsb_mem = mmap(NULL, bsb_size * 2, PROT_READ, MAP_SHARED, fd_iav,
 * 		part_info->mem.addr);
 * if (bsb_mem == MAP_FAILED) {
 * 	perror("mmap IAV_PART_BSB failed\n");
 * 	return -1;
 * }
 *
 * // Query frame descriptor from IAV
 * memset(&query_desc, 0, sizeof(query_desc));
 * frame_desc = &query_desc.arg.frame;
 * query_desc.qid = IAV_DESC_FRAME;
 * frame_desc->id = -1;
 * if (ioctl(fd_iav, IAV_IOC_QUERY_DESC, &query_desc) < 0) {
 * 	// fail
 * 	return -1;
 * }
 * @endcode
 *
 *
 * @subsection usage_sysfs 11.12 Sysfs Usage
 *
 * The following code shows how to use sysfs file.
 * @code {.c}
 * #define SYSFS_IAV_INFO "/sys/devices/platform/iav/monitor/iav_info"
 * #define SYSFS_IAV_STATE "/sys/devices/platform/iav/monitor/iav_state"
 * #define SYSFS_IAV_ERROR "/sys/devices/platform/iav/monitor/iav_error"
 *
 * void test_sysfs()
 * {
 *  int read_num = 0;
 *  int epoll_fd = -1;
 *  int iav_info_fd = -1;
 *  int iav_error_fd = -1;
 *  int iav_state_fd = -1;
 *  char buf[4096] = {0};
 *  struct iav_sysfs_info_msg *info_msg = NULL;
 *  struct iav_sysfs_state_msg *state_msg = NULL;
 *  struct amba_sysfs_error_msg *error_msg = NULL;
 *  epoll_event add_event;
 *  epoll_event event_list[2];
 *  do {
 *    if ((iav_info_fd = ::open(SYSFS_IAV_INFO, O_RDONLY)) < 0) {
 *      perror("Failed to open iav_info file.");
 *      break;
 *    }
 *    if ((iav_state_fd = ::open(SYSFS_IAV_STATE, O_RDONLY)) < 0) {
 *      perror("Failed to open iav_state file.");
 *      break;
 *    }
 *    if ((iav_error_fd = ::open(SYSFS_IAV_ERROR, O_RDONLY)) < 0) {
 *      perror("Failed to open iav_error file.");
 *      break;
 *    }
 *    if (!(epoll_fd = ::epoll_create1(EPOLL_CLOEXEC))) {
 *      perror("Failed to create epoll!");
 *      break;
 *    }
 *    //Read iav info msg from iav_info file
 *    read_num = ::read(iav_info_fd, buf, sizeof(buf));
 *    if (read_num >= sizeof(struct iav_sysfs_info_msg)) {
 *       info_msg = (struct iav_sysfs_info_msg*)buf;
 *       printf("iav info msg pts is %llu\n", info_msg->pts);
 *    } else {
 *      printf("Read iav_info file data size error.\n");
 *    }
 *    //We need to read all the data out before using select to monitor the fd.
 *    read_num = ::read(iav_state_fd, buf, sizeof(buf));
 *    ::lseek(iav_state_fd, 0, SEEK_SET);
 *    read_num = ::read(iav_error_fd, buf, sizeof(buf));
 *    ::lseek(iav_error_fd, 0, SEEK_SET);
 *    add_event.events = EPOLLPRI;//Should not use EPOLLIN
 *    add_event.data.fd = iav_state_fd;
 *    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, iav_state_fd, &add_event) < 0) {
 *      perror("epoll ctl error.");
 *      break;
 *    }
 *    add_event.data.fd = iav_error_fd;
 *    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, iav_error_fd, &add_event) < 0) {
 *      perror("epoll ctl error.");
 *      break;
 *    }
 *    while(1) {
 *       int ready = epoll_wait(epollfd, event_list, 2, -1);
 *      if (ready < 0) {
 *        perror("epoll error");
 *        break;
 *      }
 *      for (int i = 0; i < ready; ++ i) {
 *        if (event_list[i].events & EPOLLPRI) {
 *          if (event_list[i].data.fd == iav_state_fd) {
 *            printf("Iav state Change happened.\n");
 *            //Read iav state msg from iav_state file
 *            memset(buf, 0, sizeof(buf));
 *            read_num = ::read(iav_state_fd, buf, sizeof(buf));
 *            ::lseek(iav_state_fd, 0, SEEK_SET);
 *            if (read_num >= sizeof(struct iav_sysfs_state_msg)) {
 *              state_msg = (struct iav_sysfs_state_msg*)buf;
 *              printf("iav state msg pts is %llu\n", state_msg->pts);
 *            } else {
 *              printf("Read iav_state file data size error.\n");
 *            }
 *          }
 *          if (event_list[i].data.fd == iav_error_fd) {
 *            printf("Iav error happened.\n");
 *            //Read iav error msg from iav_error file
 *            memset(buf, 0, sizeof(buf));
 *            read_num = ::read(iav_error_fd, buf, sizeof(buf));
 *            ::lseek(iav_error_fd, 0, SEEK_SET);
 *            if (read_num >= sizeof(struct amba_sysfs_error_msg)) {
 *              state_msg = (struct amba_sysfs_error_msg*)buf;
 *              printf("iav error msg pts is %llu\n", state_msg->pts);
 *            } else {
 *              printf("Read iav_error file data size error.\n");
 *            }
 *          }
 *        }
 *      }
 *    }
 *  } while (false);
 *  if (iav_info_fd >= 0) {
 *    ::close(iav_info_fd);
 *  }
 *  if (iav_state_fd >= 0) {
 *    ::close(iav_state_fd);
 *  }
 *  if (iav_error_fd >= 0) {
 *    ::close(iav_error_fd);
 *  }
 *  if (epoll_fd >= 0) {
 *    ::close(epoll_fd);
 *  }
 * }
 * @endcode
 *
 *
 * @subsection usage_poll_interface_drv 11.13 Poll Interface Usage.
 *
 * @subsubsection poll_iav_data_usage_drv 11.13.1 Usage of Querying IAV Data
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
 * Wait for the events ready and process it:
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
 * case IAV_DESC_SLICE:
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
 * @subsubsection poll_irq_sync_usage_drv 11.13.2 Usage of Interrupt Synchronization
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
 * @subsection usage_return_value 11.14 Return Value of APIs
 *
 * All return values of IOCTL APIs are defined in /ambarella/kernel/linux/include/uapi/asm-generic/errno-base.h.
 * | Error number   | Description             |
 * | :------------- | :----------             |
 * | EPERM          | Operation not permitted |
 * | EIO            | I/O error               |
 * | EAGAIN         | Try again               |
 * | ENOMEM         | Out of memory           |
 * | EACCES         | Permission denied       |
 * | EFAULT         | Bad address             |
 * | EBUSY          | Device or resource busy |
 * | EINVAL         | Invalid argument        |
 *
 * - - - -
 *
 * @section sec_iav_api 12. IAV API
 *
 * In @ref iav-api, Ambarella has put APIs in groups as below:
 *
 *
 * @subsection sec_iav_api_vin 12.1 IAV IOCTL API: VIN
 *
 * Each source represents one real video input device. In a working system,
 * there should be at least one input source. The application can query the
 * total source number, the active source ID, and set the active source ID.
 * @b IAV_IOC_VIN_* operations will be applied on the active source, so the
 * application must take care to select an active source ID before sending
 * any @b IAV_IOC_VIN_* IO control commands.
 *
 * @ref iav-ioctl-vin-api will show more details about the API details.
 *
 *
 * @subsection sec_iav_api_vout 12.2 IAV IOCTL API: VOUT
 *
 * @ref iav-ioctl-vout-api will show more details about vout related ioctl, located in file
 * iav_vin_ioctl.h
 *
 *
 * @subsection sec_iav_api_ucode 12.3 IAV IOCTL API: Load Ucode
 *
 * @ref iav-ioctl-ucode-api will show more details about ucode loading related ioctl, located in
 * file iav_ucode_ioctl.h
 *
 *
 * @subsection sec_iav_api_drv 12.4 IAV IOCTL API: DSP & Driver Control
 *
 * @ref iav-ioc-enc-use-drv will show more details about DSP & Driver related ioctl, located in
 * file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_enc 12.5 IAV IOCTL API: Encode Pyramid Control
 *
 * @ref iav-ioc-enc-use-pyra will show more details about Encode Pyramid related ioctl, located in
 * file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_sys 12.6 IAV IOCTL API: System Control
 *
 * @ref iav-ioc-enc-use-sys will show more details about System Control related ioctl, located in
 * file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_efm 12.7 IAV IOCTL API: EFM
 *
 * @ref iav-ioc-enc-use-efm will show more details about EFM related ioctl, located in file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_efr 12.8 IAV IOCTL API: EFR
 *
 * @ref iav-ioc-enc-use-efr will show more details about EFR related ioctl, located in file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_mem 12.9 IAV IOCTL API: Memory Management Control
 *
 * The most efficient way to share data with IAV, user space application and DSP, is to use the share
 * memory between Arm and DSP, then memory mapping from Arm kernel space to Arm user space.
 *
 * The shared buffers include DSP memory partition, bit stream buffer partition, user buffer partition,
 * overlay buffer partition, QP ROI matrix buffer partition, warp buffer partition, JPEG quant matrix
 * table buffer partition, image buffer partition, privacy mask buffer partition, and bad pixel
 * correction buffer partition as shown below. All partition sizes are configurable in the "iav_config.h"
 * file.
 * @image html iav_memory_layout.jpg "IAV Related Memory Layout."
 *
 * These partitions are pre-allocated and already pre-mapped at kernel space. User space applications
 * query the physical address / length of each partition from IAV and map it into the user space
 * address themselves.
 *
 * The base address and total size of IAV related partitions can be configured through menuconfig,
 * allowing customers to make changes for the customized design; however, the dynamic random access
 * memory (DRAM) size must meet DSP minimum requirement.
 *
 * By default, all partitions are mapped as "non-cached" memory in the IAV driver. If customers want
 * to change any partition map type from "non-cached" to "cached" to get a faster read or write speed
 * from cache benefits, it is suggested to contact the SDK support team for assistance.
 *
 * User partition is used to store large data and export to the application to call GDMA to speed
 * up the memory access operations.
 *
 * go to @ref iav-ioc-enc-use-mem to see more details about the APIs.
 *
 *
 * @subsection sec_iav_api_stm 12.10 IAV IOCTL API: Stream Control
 *
 * @ref iav-ioc-enc-use-stm will show more details about Stream Control related ioctl, located in
 * file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_ovl 12.11 IAV IOCTL API: Overlay Control
 *
 * @ref iav-ioc-enc-use-ovl will show more details about Overlay Control related ioctl, located in
 * file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_vcap 12.12 IAV IOCTL API: Vcap Control
 *
 * @ref iav-ioc-enc-use-vcap will show more details about Vcap Control related ioctl, located in
 * file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_vproc 12.13 IAV IOCTL API: VProc Control
 *
 * @ref iav-ioc-enc-use-vproc will show more details about VProc Control related ioctl, located in
 * file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_vind 12.14 IAV IOCTL API: VIN & IDSP Control
 *
 * @ref iav-ioc-enc-use-vin will show more details about VIN & IDSP Control related ioctl, located
 * in file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_dbg 12.15 IAV IOCTL API: Debug IOCTL
 *
 * @ref iav-ioc-enc-use-dbg will show more details about Debug ioctl, located in file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_dec 12.16 IAV IOCTL API: Decoder Control
 *
 * @ref iav-ioctl-dec-api will show more details about decode ioctl, located in file iav_ioctl.h
 *
 *
 * @subsection sec_iav_api_img_scale 12.17 IAV IOCTL API: Arbitrary Image Scaler Control
 *
 * @ref iav-ioc-enc-img-scale will show more details about arbitrary image scale ioctl, located in file iav_ioctl.h
 * - - - -
 *
 * @section iav_license 13. License
 *
 * Copyright (c) @ambalicyear Ambarella International LP
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

//module
/*! @defgroup iav-api IAV IOCTL API
 * @brief IAV IOCTL API
 */
/*! @defgroup iav-helper IAV API Helper
 * @ingroup iav-api
 * @brief IAV IOCTL API Structs, Enumerations and Macros
 */


//basetypes.h
/*! @defgroup iav-basetype IAV Base Type
 * @ingroup iav-helper
 * @brief IAV API Base Type, in file basetypes.h
 */
//basetypes.h


//iav_common.h
/*! @defgroup iav-common IAV Common
 * @ingroup iav-helper
 * @brief IAV Common Structs, Enumerations and Macros, in file iav_common.h
 */

/*! @defgroup iav-common-struct IAV Common Structs
 * @ingroup iav-common
 * @brief IAV Common Structs, Enumerations and Macros
 */

/*! @defgroup iav-common-helper IAV Common Enumerations and Macros
 * @ingroup iav-common
 * @brief IAV Common Enumerations and Macros
 */
//iav_common.h


//iav_vout_ioctl.h
/*! @defgroup iav-ioctl-vout IAV VOUT IOCTL Helper
 * @ingroup iav-helper
 * @brief IAV VOUT IOCTL API Helper, in file iav_vout_ioctl.h
 */

/*! @defgroup iav-ioctl-vout-api IAV IOCTL API: Vout
 * @ingroup iav-api
 * @brief IAV IOCTL API: Video Output Configuration, in file iav_vout_ioctl.h and iav_vout_common.h
 */

/*! @defgroup iav-ioctl-vout-struct IAV IOCTL VOUT Structs
 * @ingroup iav-ioctl-vout
 * @brief IAV IOCTL Video Output API: Structs used in API
 */

/*! @defgroup iav-ioctl-vout-helper IAV IOCTL VOUT Macros and Enumerations
 * @ingroup iav-ioctl-vout
 * @brief IAV IOCTL Video Output API: Macros and Enumerations
 */
//iav_vout_ioctl.h


//iav_vin_ioctl.h
/*! @defgroup iav-ioctl-vin IAV VIN IOCTL Helper
 * @ingroup iav-helper
 * @brief IAV VIN IOCTL API Helper, in file iav_vin_ioctl.h
 */

/*! @defgroup iav-ioctl-vin-api IAV IOCTL API: Vin
 * @ingroup iav-api
 * @brief IAV IOCTL API: Video Input Configuration, in file iav_vin_ioctl.h and iav_vin_common.h
 * @details Each source represents one real video input device. In a working system,
 * there should be at least one input source. The application can query the
 * total source number, the active source ID, and set the active source ID.
 * @b IAV_IOC_VIN_* operations will be applied on the active source, so the
 * application must take care to select an active source ID before sending
 * any @b IAV_IOC_VIN_* IO control commands.
 */

/*! @defgroup iav-ioctl-vin-struct IAV IOCTL VIN Struct
 * @ingroup iav-ioctl-vin
 * @brief IAV IOCTL Video Input API: Structs used in API
 */

/*! @defgroup iav-ioctl-vin-helper IAV IOCTL VIN Macros and Enumerations
 * @ingroup iav-ioctl-vin
 * @brief IAV IOCTL Video Input API: Macros and Enumerations
 */
//iav_vin_ioctl.h


//iav_ucode_ioctl.h
/*! @defgroup iav-ioctl-ucode IAV UCODE IOCTL Helper
 * @ingroup iav-helper
 * @brief IAV IOCTL API Helper: Load Ucode, in file iav_ucode_ioctl.h
 */

/*! @defgroup iav-ioctl-ucode-api IAV IOCTL API: Load Ucode
 * @ingroup iav-api
 * @brief IAV IOCTL API: Load Ucode, in file iav_ucode_ioctl.h
 */

/*! @defgroup iav-ioctl-ucode-struct IAV IOCTL Ucode Struct
 * @ingroup iav-ioctl-ucode
 * @brief IAV IOCTL Load Ucode API: Structs used in API
 */

/*! @defgroup iav-ioctl-ucode-helper IAV IOCTL Ucode Macros and Enumerations
 * @ingroup iav-ioctl-ucode
 * @brief IAV IOCTL Load Ucode API: Macros and Enumerations
 */
//iav_ucode_ioctl.h


//iav_ioctl.h
/*! @defgroup iav-ioctl-general IAV IOCTL Encoder Helper
 * @ingroup iav-helper
 * @brief IAV IOCTL Encoder API Helper, in file iav_ioctl.h
 */

/*! @defgroup iav-ioctl-general-struct IAV IOCTL Encoder Struct
 * @ingroup iav-ioctl-general
 * @brief IAV IOCTL Encoder Struct used in API
 */

/*! @defgroup iav-ioctl-general-helper IAV IOCTL Encoder Macros and Enumerations
 * @ingroup iav-ioctl-general
 * @brief IAV IOCTL Encoder API: Macros and Enumerations
 */

/*! @defgroup iav-ioctl-dec IAV IOCTL Decoder Helper
 * @ingroup iav-helper
 * @brief IAV IOCTL Decoder API Helper, in file iav_ioctl.h
 */

/*! @defgroup iav-ioctl-dec-api IAV IOCTL API: Decoder
 * @ingroup iav-api
 * @brief IAV IOCTL API: Decoder, in file iav_ioctl.h
 */

/*! @defgroup iav-ioctl-dec-struct IAV IOCTL Decoder Struct
 * @ingroup iav-ioctl-dec
 * @brief IAV IOCTL Decoder Struct used in API
 */

/*! @defgroup iav-ioctl-dec-helper IAV IOCTL Decoder Macros and Enumerations
 * @ingroup iav-ioctl-dec
 * @brief IAV IOCTL Decoder API: Macros and Enumerations
 */

/*!
 * @defgroup iav-ioc-enc-use-drv IAV IOCTL API: DSP & driver Control
 * @ingroup iav-api
 * @brief IAV ioctl API: DSP & driver ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-pyra IAV IOCTL API: Encode Pyramid Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: Encode Pyramid ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-canvas IAV IOCTL API: Encode Canvas Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: Encode Canvas ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-sys IAV IOCTL API: System Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: System ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-efm IAV IOCTL API: EFM Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: Encode from memory ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-efr IAV IOCTL API: EFR Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: Encode from raw ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-mem IAV IOCTL API: Memory Management Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: Memory Management ioctl, in file iav_ioctl.h
 * @details The most efficient way to share data with IAV, user space application and DSP, is to use the share
 * memory between Arm and DSP, then memory mapping from Arm kernel space to Arm user space.
 *
 * The shared buffers include DSP memory partition, bit stream buffer partition, user buffer partition, overlay
 * buffer partition, QP ROI matrix buffer partition, warp buffer partition, JPEG quant matrix table buffer
 * partition, image buffer partition, privacy mask buffer partition, and bad pixel correction buffer partition
 * as shown below. All partition sizes are configurable in the "iav_config.h" file.
 * @image html iav_memory_layout.jpg "IAV Related Memory Layout."
 *
 * These partitions are pre-allocated and already pre-mapped at kernel space. User space applications query the
 * physical address / length of each partition from IAV and map it into the user space address themselves.
 *
 * The base address and total size of IAV related partitions can be configured through menuconfig, allowing
 * customers to make changes for the customized design; however, DRAM size must meet DSP minimum requirement.
 *
 * By default, all partitions are mapped as "non-cached" memory in the IAV driver. If customers want to change any
 * partition map type from "non-cached" to "cached" to get a faster read or write speed from cache benefits, it is
 * suggested to contact the SDK support team for assistance.
 *
 * User partition is used to store large data and export to the application to call GDMA to speed up the
 * memory access operations.
 */

/*!
 * @defgroup iav-ioc-enc-use-stm IAV IOCTL API: Stream Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: Stream ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-ovl IAV IOCTL API: Overlay/Blur Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: Overlay/Blur ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-vcap IAV IOCTL API: Vcap Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: VCAP ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-warp IAV IOCTL API: Warp Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: WARP control ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-vproc IAV IOCTL API: Vproc Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: VPROC control ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-vin IAV IOCTL API: Vin & IDSP Control
 * @ingroup iav-api
 * @brief IAV IOCTL API: VIN & IDSP ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-dbg IAV IOCTL API: Debug IOCTL
 * @ingroup iav-api
 * @brief IAV IOCTL API: test for debug ioctl, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-use-usr IAV IOCTL API: Customized IAV IOCTL
 * @ingroup iav-api
 * @brief IAV IOCTL API: Customized IAV IOCTL, in file iav_ioctl.h
 */

/*!
 * @defgroup iav-ioc-enc-img-scale IAV IOCTL API: Arbitrary Image Scaler
 * @ingroup iav-api
 * @brief IAV IOCTL API: Arbitrary Image Scaler, in file iav_ioctl.h
 */
//iav_ioctl.h

//amba_sysfs_iav.h
/*!
 * @defgroup iav-sysfs-monitor IAV Sysfs Helper
 * @ingroup iav-helper
 * @brief IAV Sysfs Helper: IAV Sysfs debug info, in file amba_sysfs_iav.h
 */

/*!
 * @defgroup iav-sysfs-monitor-general-helper
 * @ingroup iav-sysfs-monitor
 * @brief IAV Sysfs Helper: IAV Sysfs debug info, in file amba_sysfs_iav.h
 */
/*!
 * @defgroup iav-sysfs-monitor-general-struct
 * @ingroup iav-sysfs-monitor
 * @brief IAV Sysfs Helper: IAV Sysfs debug info, in file amba_sysfs_iav.h
 */

/*!
 * @defgroup sysfs-monitor-general-struct
 * @ingroup iav-sysfs-monitor
 * @brief IAV Sysfs Helper: IAV Sysfs debug info, in file amba_sysfs_iav.h
 */
//amba_sysfs_iav.h


/*! @example test_decode.c
 * This is an example of how to decode a video clip.
 */

/*! @example test_efm.c
 * This is an example of how to encode from memory and encode from raw input.
 */

/*! @example test_privacymask.c
 * This is an example of how to apply privacy mask to the entire source buffer.
 */

/*! @example test_overlay.c
 * This is an example of how to apply overlay to a stream.
 */

/*! @example test_encode.c
 * @This is a example file to show how to configure video resource, start/stop encode.
 */

/*! @example test_mempart.c
 * @This is a example file to show how to configure memory.
 */

/*! @example test_decode.c
 * This is an example of how to decode a video clip.
 */

/*! @example test_dptz.c
 * This is an example of how to configure dptz of a stream.
 */

/*! @example test_stream.c
 * This is an example of how to configure a stream.
 */

/*! @example test_img_scale.c
 * This is an example of how to do arbitrary image scale.
 */

/*! @example test_blur.c
 * This is an example of how to insert blur areas to streams for privacy protection.
 */


/*!
 * @page page_drv_sensor Sensor Parameters & Tuning Table
 *
 * @section sensor_history 0. Revision History
 *  | Version | Updated Date  | Modification            |
 *  | :---    | :------------ |:--------------------    |
 *  | 1.0.0   | 20200706      | Initial Version         |
 *  | 1.0.1   | 20200731      | Add serdes parameters   |
 *  | 1.0.2   | 20210315      | Add sensor tuning table |
 *  | 1.0.3   | 20210414      | Add last update time for sensor tuning table |
 *  | 1.0.4   | 20210514      | Add last update time for sensor driver |
 *  | 1.0.5   | 20230302      | Add optical format and max resolution for sensor parameters table |
 *
 * - - - -
 * @section sensor_parm 1. Sensor Module Parameters
 * Sensor drivers have some parameters that is mandatory or optional. For different system,
 * those parameters can be different. Improper setting may cause the sensor(s) not working.
 * For more examples on how to use those parameters,
 * refer to @ref fd_adv_multi_vin "ADVANCED - Multi-VIN & Multi-Channel"
 *
 * | Parameter | Description |
 * | :----- | :------ |
 * | a_num | stay frames at group 0, A frame |
 * | addr | device address |
 * | aeq | turn AEQ on/off |
 * | auto_cg | hcg/lcg switch mode selection, 0:lcg mode, 1:auto lcg/hcg mode |
 * | auto_det | detect input format automatically |
 * | b_num | stay frames at group 1, B frame |
 * | bayer_pattern | set bayer pattern: 0:RG, 1:BG, 2:GR, 3:GB, 255:default |
 * | binning | 0: none binning 1: 2x2 binning |
 * | bits | customized mode input bit width |
 * | brg_id | indicate which bridge is bind to |
 * | bus_addr | bus and cs: bit16~bit31: bus, bit0~bit15: cs |
 * | bus_id | device bus id |
 * | calb_en | use default calibration data |
 * | clk | sensor's master clock |
 * | color | 0: monochrome(LLR), 1: color(LQR) |
 * | compression | 0: no compression, 1:compression |
 * | cphy | Use CPHY, 0:DPHY, 1:CPHY |
 * | cphy_rate | cphy data rate, 0:1188Msps/trio, 1:1624Msps/trio, 2:2376Msps/trio |
 * | cs_id | spi cs |
 * | custom_format_enable | Flag to enable custom video format |
 * | data_rate | indicate D-PHY data rate |
 * | data_reverse | use reverse data pin mapping |
 * | dcg_2x_mode | 2x hdr mode selection, 0:2x staggered HDR mode, 1:2x dcg HDR mode |
 * | dcg_3x_mode | 3x hdr mode selection, 0:3-exp new staggered HDR mode, 1:3x dcg+vs HDR mode, 2:3-exp vc staggered HDR mode |
 * | debug_mode | 0: disbale, 1: HCG frame, 2: LCG frame, 3: LOFIC frame, 4: VS frame |
 * | def_ser_addr | default serializer address |
 * | delay | set delayed vsync time, unit is ns |
 * | double_pixel | use double pixel mode |
 * | drive_mode | drive mode: 0: without flash, 1: with flash |
 * | dts_addr | load SERDES i2c address from dts |
 * | dual_freq | use dual band/freq modulation |
 * | dual_gain | Use dual gain mode 0:normal mode 1:dual gain mode |
 * | dual_gain_mode | 2x hdr mode selection, 0:vs mode, 1:dual gain mode, 2:combined+vs mode |
 * | dual_port | use dual port mode(csi0 & csi1) |
 * | dvdd_mode | DVDD Power supply: 0:external LDO, 1:sensor internal LDO |
 * | dynamic_offset | HDR offset changed dynamically or not |
 * | err_flag | use error flag mode for shutter out of range |
 * | exp_gain | exp_gain: 0: 0dB, 1: 6dB; 2: 12dB; 3: 18dB; 4: 24dB; 5: 30dB |
 * | expo_ratio | frameset ratio, smaller than 32 |
 * | fb_test | indicate to do fast boot test or not |
 * | fhd_mode | use 1080p or 720p AHD |
 * | fpga | use FPGA or not |
 * | fps | customized mode input frame rate |
 * | frameset | 1: default use one set, 2: 2 frames one-set |
 * | freq_20m | use 20MHz frequency mode |
 * | freq_mode | 0: 120MHz 1: 20MHz 2:20/120MHz dual freq |
 * | fsync | use internal fsync function |
 * | fsync_gpio | indicate serializer gpio to output fsync |
 * | fsync_int | internal fsync mode 0:off 1:on |
 * | gain_ratio | gain_ratio: 1: 6dB; 2: 12dB; 3: 18dB; 4: 24dB; 5: 30dB |
 * | global_ae | use global ae for all channels |
 * | gmsl_mode | indicate GMSL mode |
 * | gmsl_spi_clk | set GMSL SER spi speed |
 * | gmsl_spi_mode | use max96712/9295 spi |
 * | gp_ctrl | built-in hdr 3a selection, 0:use single-frame ctrl, 1:use group ctrl |
 * | gpi_o | enable GPI->GPO forwarding |
 * | gyro_test | gyro test |
 * | h | customized mode input height |
 * | hispi_style | sync code style: 0:HiSPi Streaming-S, other:HiSPi Packetized-SP |
 * | hsync_gpio | indicate serializer gpio to output hsync |
 * | id | channel ID 0x1/0x2/0x4/0x8, bit map |
 * | id_ext | extra channel ID 0x01~0x0F for brg8 or more, bit map |
 * | inck_mode | INCK frequency, 0: 74.25M, 1: 37.125M |
 * | interlace | line interleaving mode |
 * | io_1p8 | i2c voltage level seletion(only for ds90ub953/935) |
 * | ir_gpio | indicate which gpio controls ir led |
 * | ir_mode | Use IR mode, 0:RGB mode, 1:RGB-IR mode |
 * | lane | serdes lane number: from 1~3 |
 * | lane_mux | set lane mux to remap logic with physical lane sequencer |
 * | lccen_gpio | indicate gpio to control lccen |
 * | ld_type | Laser Drive IC 0: CXA4026 1: OCP8681 |
 * | led_on | 0: strobe pin off 1: strobe pin on |
 * | low_rate | 0: 60fps(max) 1: 30fps(max) |
 * | main_fw | main fw file name |
 * | max9295d | use max9295d dual csi-2 serializer |
 * | mclk_mode | MCLK frequency, 0: 12M, 1: 24M |
 * | mfp4_clk | use MFP4 to output clock, default is MFP2 |
 * | mipi | Set interface type 0:LVCMOS 1:MIPI |
 * | mode | FPD-Linke input mode 0: CSI mode 1: RAW 12 LF 2: RAW 12 HF 3: RAW10 0xFF: From MODE pin |
 * | n4_id | n4 port id |
 * | ntsc_mode | use NTSC or PAL mode |
 * | ob_capture | Capture OB line or not, 0:disable, 1:enable |
 * | pdaf | Use PDAF or not, 0:disable PDAF, 1:enable PDAF |
 * | poc_pwr_gpio | indicate gpio for poc power |
 * | poc_rst_time | poc reset time(ms) to reset serializer with max20087 |
 * | port_mode | CSI port 0: port A 1: port B 2: port A+port B |
 * | rate | serdes rate: from 0~3 |
 * | ratio | compression ratio |
 * | reset_all | reset all for mode switch |
 * | reverse | reverse channel sequence |
 * | samebus_num | indicate max9296 numbers using same i2c bus |
 * | sehdr_mode | hdr mode selection, 0:MEHDR mode, 1: SEHDR mode |
 * | sen_pwr_gpio | indicate gpio for sensor power |
 * | sen_rst_gpio | indicate serializer gpio for sensor reset |
 * | sensor_id | sensor_id(used for RGB sensor) |
 * | set_vin_first | set vin first for some phys which require phy ready before streaming |
 * | sl_gpio | indicate which gpio controls struct light |
 * | slave | 0: master mode 1: slave mode |
 * | spi | Use SPI interface 0:I2C 1:SPI |
 * | start_x | customized mode start offset for x |
 * | start_y | customized mode start offset for y |
 * | stp_mode | Use Shielded twisted pair(STP) mode |
 * | strobe_mode | 0: off 1: long 2: short 3: env 255: auto |
 * | sub_fw | sub fw file name |
 * | super_gain | internal hdr mode selection, false:3-exp mode, true:super expor T1 + T2 mode |
 * | sync_duplicate | sync code sytle: duplicate on each lane |
 * | sync_phase | DVP H/V sync phase |
 * | test | use FPGA test pattern or not |
 * | test_mode | test pattern enable, 1: Deserializer 2: Serializer |
 * | tof_mode | tof output mode 0:A&B 1:A-B |
 * | trigger_gpio | trigger gpio selection |
 * | tvi | input standard 0: AHD 1: TVI |
 * | use_max20087 | use max20087 to control POC power or not |
 * | v300 | use max96712 v300 board |
 * | vc | use virtual channel |
 * | vc_id | virtual channel map |
 * | version | indicate module version |
 * | vin_format | vin_format: 0:rgb; 1:yuv |
 * | vin_virtual_flag | Vin Virtual Flag |
 * | vinc_id | indicate which vin controller is bind to |
 * | virtual_vsrc_num | Virtual vsrc Num |
 * | vout_lane | vout lane number: 4~8 |
 * | vs_dly_lines | indicate delayed vsync lines |
 * | vs_ilpwm | 0: vsync from vsync/fsin 1: vsync from ilpwm |
 * | w | customized mode input width |
 * | xtrig | 0: not use external trigger, 1: use fast trigger, 2: use sequential trigger |
 * | xvs_out | 0: HiZ mode 1: XVS output |
 * | yuv_mode | customized mode input format, RGB mode:0, YUV mode:1 |
 * | yuv_pix_order | 0: Y0_CB_Y1_CR, 1: CR_Y0_CB_Y1, 2: CB_Y0_CR_Y1, 3: Y0_CR_Y1_CB |


 * - - - -
 * @section sensor_parm_table 2. Sensor Module Parameters Table
 * @subsection cmos_parm_table 2.1 CMOS Sensor Parameters Table
 * Below table shows CMOS sensors and their parameters.
 *
 * | Sensor | Optical Format | Max Resolution | Parameters | Last Mod Time |
 * | :----- | :------- | :--- | :--- | :--- |
 * | altera_fpga | / | / | vin_format | 2023.12.01 |
 * | ambds | / | / | vinc_id, vc_id, virtual_vsrc_num, vin_virtual_flag, yuv_mode, spi, bus_addr, lane, yuv_pix_order, slave, sync_duplicate, mipi, data_rate, custom_format_enable, vs_dly_lines, w, h, start_x, start_y, fps, bits, sensor_id | 2024.01.16 |
 * | b5_ar0230 | 1/2.7-Inch | 1928x1088 | bus_addr, id, interlace, global_ae, ratio, lane, reverse | 2023.12.01 |
 * | b5_ar0237 | 1/2.7-Inch | 1928x1088 | bus_addr, id, interlace, global_ae, ratio, lane, reverse | 2024.01.16 |
 * | b5_imx274 | 1/2.5-Inch | 3864x2202 | bus_addr, id, interlace, global_ae, ratio, lane, reverse | 2023.12.01 |
 * | b5_imx290 | 1/2.5-Inch | 3864x2202 | bus_addr, id, interlace, global_ae, ratio, lane, vout_lane, reverse | 2023.12.01 |
 * | brillnics_brv0200_mipi | 1/2.7-Inch | 1920x1080 | bus_addr | 2024.01.16 |
 * | brillnics_brv0500_mipi | 1/2.5-Inch | 2592x1944 | bus_addr, sehdr_mode | 2024.01.16 |
 * | cista_c2390_mipi | 1/2.7-Inch | 1920x1080 | bus_addr | 2024.01.16 |
 * | cista_c2390_parallel | 1/2.7-Inch | 1920x1080 | bus_addr, bayer_pattern | 2024.01.16 |
 * | galaxycore_gc13a2 | 1/3.08-Inch | 4208x3120 | bus_id, addr, vinc_id | 2024.01.16 |
 * | galaxycore_gc2093 | 1/3-Inch | 1920x1080 | bus_id, addr, vinc_id, fsync | 2024.01.16 |
 * | galaxycore_gc2145 | 1/5.0-Inch | / | bus_id, addr, vinc_id | 2024.01.16 |
 * | galaxycore_gc2385 | 1/5-Inch | 1600x1200 | bus_id, addr, vinc_id | 2024.01.16 |
 * | galaxycore_gc4663 | 1/3-Inch | 2560x1440 | bus_id, addr, vinc_id | 2024.01.16 |
 * | galaxycore_gc8034 | 1/4.0-Inch | / | bus_id, addr, vinc_id | 2024.01.16 |
 * | himax_hm2140 | 1/4-Inch | 1920x1080 | bus_addr, dvdd_mode | 2024.01.16 |
 * | himax_hm5532 | 1/2.6-Inch | 2720x2080 | bus_addr, ir_mode | 2024.01.16 |
 * | micron_ar0130 | 1/3.2-Inch | / | bus_addr, bayer_pattern | 2024.01.16 |
 * | micron_ar0141 | 1/4-Inch | 1280x800 | bus_addr | 2024.01.16 |
 * | micron_ar0230 | 1/2.7-Inch | 1928x1088 | bus_id, addr, vinc_id | 2024.01.16 |
 * | micron_ar0230_parallel | 1/2.7-Inch | 1928x1088 | bus_addr, bayer_pattern | 2024.01.16 |
 * | micron_ar0331 | 1/3-Inch | 2048x1536 | bus_addr | 2024.01.16 |
 * | micron_mt9t002 | 1/3.2-Inch | / | bus_addr | 2024.01.16 |
 * | micron_mt9t002_mipi | 1/3.2-Inch | / | bus_addr | 2024.01.16 |
 * | micron_mt9t002_parallel | 1/3.2-Inch | / | bus_addr, bayer_pattern | 2024.01.16 |
 * | omnivision_og01a1b | 1/5-Inch | 1280x1024 | bus_id, addr, vinc_id, xtrig | 2024.01.16 |
 * | omnivision_os02a1q | 1/2.7-Inch | 2688x1944 | bus_id, addr, vinc_id, lane | 2024.01.16 |
 * | omnivision_os02c10 | 1/2.8-Inch | 1920x1080 | bus_id, addr, vinc_id, fsync, dcg_2x_mode, dcg_3x_mode, vc, lane, dynamic_offset | 2024.01.16 |
 * | omnivision_os02f10 | 1/4-Inch | 1920x1080 | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_os02h10 | 1/2.8-Inch | 1920x1080 | bus_id, addr, vinc_id, vc, lane, dynamic_offset, fsync, led_on | 2024.01.16 |
 * | omnivision_os02k10 | 1/2.8-Inch | 1920x1080 | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_os04a10 | 1/1.79-Inch | 2688x1520 | bus_id, addr, vinc_id, dcg_2x_mode, dcg_3x_mode, fsync | 2024.01.16 |
 * | omnivision_os04c10_mipi | 1/3-Inch | 2688x1520 | bus_id, addr, vinc_id, lane | 2024.01.16 |
 * | omnivision_os04e10_mipi | 1/3.11-Inch | 2048x2048 | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_os05a10 | 1/2.7-Inch | 2688x1944 | bus_id, addr, vinc_id, fsync, mclk_mode, dynamic_offset | 2024.01.16 |
 * | omnivision_os05b10 | 1/2.78-Inch | 2592x1944 | bus_id, addr, vinc_id, vc | 2024.01.16 |
 * | omnivision_os08a10 | 1/2-Inch | 3840x2160 | bus_id, addr, vinc_id, lane | 2024.01.16 |
 * | omnivision_os08b10 | 1/1.25-Inch | 3840x2160 | bus_id, addr, vinc_id, dynamic_offset | 2024.01.16 |
 * | omnivision_ov02k10 | 1/2.8-Inch | 1920x1080 | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_ov10823 | 1/2.6-Inch | 4320x2432 | bus_addr | 2024.01.16 |
 * | omnivision_ov2311_mipi | 1/2.9-Inch | 1600x1300 | bus_id, addr, vinc_id, led_on, ir_mode, fsync, frameset | 2024.01.16 |
 * | omnivision_ov2710_parallel | 1/3-Inch | / | bus_addr, bayer_pattern | 2024.01.16 |
 * | omnivision_ov2718_mipi | 1/3-Inch | 1936x1096 | bus_id, addr, vinc_id, auto_cg, dual_gain, gp_ctrl, lane | 2024.01.16 |
 * | omnivision_ov2732_mipi | 1/4-Inch | 1920x1080 | bus_id, addr, vinc_id, fsync | 2024.01.16 |
 * | omnivision_ov2732_parallel | 1/4-Inch | 1920x1080 | bus_addr, bayer_pattern | 2024.01.16 |
 * | omnivision_ov2735_mipi | 1/2.7-Inch | 1920x1080 | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_ov2735_parallel | 1/2.7-Inch | 1920x1080 | bus_addr, bayer_pattern | 2024.01.16 |
 * | omnivision_ov2736_mipi | 1/4-Inch | 1920x1080 | bus_id, addr, vinc_id, frameset, a_num, b_num, led_on | 2024.01.16 |
 * | omnivision_ov2770_mipi | 1/3-Inch | 1936x1096 | bus_id, addr, vinc_id, dual_gain_mode | 2024.01.16 |
 * | omnivision_ov2775_mipi | 1/3-Inch | 1936x1096 | bus_id, addr, vinc_id, lane | 2024.01.16 |
 * | omnivision_ov2778_mipi | 1/2.9-Inch | 1936x1096 | bus_id, addr, vinc_id, fsync | 2024.01.16 |
 * | omnivision_ov4689_mipi | 1/3-Inch | 2688x1520 | bus_id, addr, lane, vinc_id, ir_mode | 2024.01.16 |
 * | omnivision_ov5653 | 1/3.2-Inch | / | bus_addr, bayer_pattern | 2024.01.16 |
 * | omnivision_ov5658_mipi | 1/3.2-Inch | / | bus_addr | 2024.01.16 |
 * | omnivision_ov7251_mipi | 1/7.5-Inch | 640x480 | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_ov8856_mipi | 1/4.0-Inch | / | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_ov9281 | 1/4-Inch | 1296x816 | bus_id, addr, vinc_id, led_on, fsync | 2024.01.16 |
 * | omnivision_ov9710 | 1/4-Inch | 1280x800 | bus_addr, bayer_pattern | 2024.01.16 |
 * | omnivision_ov9718_mipi | 1/4-Inch | 1280x800 | bus_addr | 2024.01.16 |
 * | omnivision_ov9732_mipi | 1/4-Inch | 1288x728 | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_ov9732_parallel | 1/4-Inch | 1288x728 | bus_addr, bayer_pattern | 2024.01.16 |
 * | omnivision_ov9750_mipi | 1/3-Inch | 1280x960 | bus_addr, ir_mode | 2024.01.16 |
 * | omnivision_ov9750_parallel | 1/3-Inch | 1280x960 | bus_addr, bayer_pattern, ir_mode | 2024.01.16 |
 * | omnivision_ov9755_mipi | 1/3-Inch | 1280x720 | bus_addr | 2024.01.16 |
 * | omnivision_ovm7690_parallel | 1/13-Inch | 640x480 | bus_addr, bayer_pattern | 2024.01.16 |
 * | omnivision_ox01a10_mipi | 1/2.56-Inch | 1280x1080 | bus_id, addr, vinc_id | 2024.01.16 |
 * | omnivision_ox03c10_mipi | 1/2.6-Inch | 1920x1280 | bus_id, addr, vinc_id, debug_mode, fsync | 2024.01.16 |
 * | omnivision_ox05b1s_mipi | 1/2.53-Inch | 2592x1944 | bus_id, addr, vinc_id, led_on, frameset | 2024.01.16 |
 * | omnivision_ox08b40_mipi | 1/2.6-Inch | 3840x2160 | bus_id, addr, vinc_id, debug_mode, fsync, mclk_mode | 2024.01.16 |
 * | omnivision_ox08d10_mipi | 1/1.73-Inch | 3840x2160 | bus_id, addr, vinc_id, debug_mode, fsync | 2024.01.16 |
 * | onsemi_ar0132_parallel | 1/3.2-Inch | / | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0138_mipi | 1/2.6-Inch | 1280x960 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0143_parallel | 1/4-Inch | 1280x960 | bus_addr | 2024.01.16 |
 * | onsemi_ar0144_mipi | 1/4-Inch | 1280x800 | bus_id, addr, vinc_id, led_on, slave | 2024.01.16 |
 * | onsemi_ar0144_parallel | 1/4-Inch | 1280x800 | bus_id, addr, vinc_id, led_on | 2024.01.16 |
 * | onsemi_ar0147_mipi | 1/4-Inch | 1344x968 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0220_mipi | 1/1.8-Inch | 1828x948 | bus_id, addr, slave, trigger_gpio, vinc_id | 2024.01.16 |
 * | onsemi_ar0221_mipi | 1/1.7-Inch | 1936x1096 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0231_mipi | 1/2.7-Inch | 1928x1208 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0231_parallel | 1/2.7-Inch | 1928x1208 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0233_mipi | 1/2.5-Inch | 2048x1280 | bus_id, addr, vinc_id, super_gain, slave, trigger_gpio | 2024.01.16 |
 * | onsemi_ar0234_mipi | 1/2.6-Inch | 1920x1200 | bus_id, addr, vinc_id, led_on, xtrig, color | 2024.01.16 |
 * | onsemi_ar0237 | 1/2.7-Inch | 1928x1088 | bus_id, addr, ir_mode, vinc_id, lane | 2024.01.16 |
 * | onsemi_ar0237_parallel | 1/2.7-Inch | 1928x1088 | bus_addr, bayer_pattern | 2024.01.16 |
 * | onsemi_ar0239 | 1/3-Inch | 1928x1188 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0239_mipi | 1/3-Inch | 1928x1188 | bus_id, addr, vinc_id, ir_mode | 2024.01.16 |
 * | onsemi_ar0323_mipi | 1/2-Inch | 2880x1080 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0431_mipi | 1/3.2-Inch | 2316x1746 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0432_mipi | 1/3.2-Inch | 2316x1746 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0521 | 1/2.5-Inch | 2592x1944 | bus_addr, hispi_style | 2024.01.16 |
 * | onsemi_ar0521_mipi | 1/2.5-Inch | 2592x1944 | bus_id, addr, vinc_id, dynamic_offset | 2024.01.16 |
 * | onsemi_ar0822_mipi | 1/2-Inch | 3848x2168 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar0830_mipi | 1/2.9-Inch | 3840x2160 | bus_id, addr, vinc_id | 2024.01.16 |
 * | onsemi_ar2020_mipi | 1/1.8-Inch | 5120x3840 | bus_id, addr, vinc_id, ir_mode | 2024.01.16 |
 * | onsemi_xgs12000_mipi | 1/1-Inch | 4096x3072 | bus_id, addr, vinc_id | 2024.01.16 |
 * | panasonic_mn34041pl | 1/3-Inch | / | bus_addr | 2023.12.01 |
 * | panasonic_mn34210pl | 1/3-Inch | 1296x1032 | bus_addr | 2024.01.16 |
 * | panasonic_mn34220pl | 1/3-Inch | 1944x1213 | bus_addr | 2024.01.16 |
 * | panasonic_mn34227pl | 1/3-Inch | 1944x1092 | bus_addr | 2024.01.16 |
 * | panasonic_mn34420pl | 1/2.86-Inch | 1944x1212 | bus_id, addr, vinc_id | 2024.01.16 |
 * | panasonic_mn34422pl | 1/2.86-Inch | 1944x1212 | bus_addr, slave | 2024.01.16 |
 * | panasonic_mn34424pl | 1/2.86-Inch | 1944x1212 | bus_addr, slave | 2024.01.16 |
 * | primesensor_ps5250 | 1/2.7-Inch | 1536x1536 | bus_addr | 2024.01.16 |
 * | primesensor_ps5270 | 1/2.7-Inch | 1536x1536 | bus_addr | 2024.01.16 |
 * | smartsens_sc130gs_mipi | 1/2.7-Inch | 1288x1032 | bus_id, addr, vinc_id | 2024.01.16 |
 * | smartsens_sc200ai_mipi | 1/2.8-Inch | 1920x1080 | bus_id, addr, vinc_id, vc | 2024.01.16 |
 * | smartsens_sc2135_parallel | 1/2.7-Inch | 1920x1080 | bus_addr, bayer_pattern | 2024.01.16 |
 * | smartsens_sc2235_parallel | 1/2.7-Inch | 1920x1080 | bus_addr, bayer_pattern | 2024.01.16 |
 * | smartsens_sc230ai_mipi | 1/2.8-Inch | 1920x1080 | bus_id, addr, vinc_id | 2024.01.16 |
 * | smartsens_sc2310_mipi | 1/2.7-Inch | 1920x1080 | bus_addr | 2024.01.16 |
 * | smartsens_sc2315_mipi | 1/2.9-Inch | 1920x1080 | bus_addr | 2024.01.16 |
 * | smartsens_sc2332_mipi | 1/3-Inch | 1920x1080 | bus_id, addr, lane, vinc_id | 2024.01.16 |
 * | smartsens_sc301iot_mipi | 1/2.8-Inch | 2052x1540 | bus_id, addr, vinc_id, fb_test | 2024.01.16 |
 * | smartsens_sc410gs | 1/1.3-Inch | 1752x2336 | bus_id, addr, vinc_id | 2024.01.16 |
 * | smartsens_sc4210_mipi | 1/3-Inch | 2560x1440 | bus_id, addr, vinc_id, slave | 2024.01.16 |
 * | smartsens_sc500ai_mipi | 1/2.7-Inch | 2880x1620 | bus_id, addr, vinc_id | 2024.01.16 |
 * | smartsens_sc5238_mipi | 1/2.7-Inch | 2592x1952 | bus_id, addr, vinc_id | 2024.01.16 |
 * | smartsens_sc5300_mipi | 1/2.7-Inch | 2592x1952 | bus_addr | 2024.01.16 |
 * | smartsens_sc530ai_mipi | 1/2.7-Inch | 2880x1620 | bus_id, addr, vinc_id | 2024.01.16 |
 * | smartsens_sc533at_mipi | 1/2.5-Inch | 2592x1944 | bus_id, addr, vinc_id, led_on | 2024.01.16 |
 * | smartsens_sc630ai_mipi | 1/2.5-Inch | 2564x2564 | bus_id, addr, vinc_id, ir_mode | 2024.01.16 |
 * | smartsens_sc8235_mipi | 1/2.7-Inch | 3840x2160 | bus_id, addr, vinc_id, frameset | 2024.01.16 |
 * | smartsens_sc850sl_mipi | 1/1.8-Inch | 3856x2176 | bus_id, addr, vinc_id | 2024.01.16 |
 * | soi_jx_f22_mipi | 1/2.7-Inch | 1932x1088 | bus_addr | 2024.01.16 |
 * | soi_jx_f23_mipi | 1/2.9-Inch | 1932x1088 | bus_addr | 2024.01.16 |
 * | soi_jx_f32_mipi | 1/2.9-Inch | 1932x1088 | bus_id, addr, vinc_id | 2024.01.16 |
 * | soi_jx_f35_mipi | 1/2.7-Inch | 1932x1088 | bus_id, addr, vinc_id | 2024.01.16 |
 * | soi_jx_f53_mipi | 1/2.8-Inch | 1932x1088 | bus_id, addr, vinc_id | 2024.01.16 |
 * | soi_jx_k02_mipi | 1/2.7-Inch | 2704x1528 | bus_addr | 2024.01.16 |
 * | soi_jx_k308_mipi | 1/2.5-Inch | 3840x2160 | bus_id, addr, vinc_id | 2024.01.16 |
 * | soi_jx_k351_mipi | 1/3.2-Inch | 2008x2008 | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_imx104 | 1/3-Inch | 1280x1024 | bus_addr | 2023.12.01 |
 * | sony_imx117 | 1/2.3-Inch | 4168x3062 | bus_addr, lane | 2023.12.01 |
 * | sony_imx122 | 1/2.8-Inch | 1920x1080 | bus_addr, bayer_pattern | 2023.12.01 |
 * | sony_imx123 | 1/2.8-Inch | 2065x1565 | bus_id, addr, vinc_id, dual_gain | 2024.01.16 |
 * | sony_imx123_mipi | 1/2.8-Inch | 2065x1565 | bus_id, addr, vinc_id, slave, dual_gain | 2024.01.16 |
 * | sony_imx124 | 1/2.8-Inch | 2065x1565 | bus_addr | 2024.01.16 |
 * | sony_imx136 | 1/2.8-Inch | 1920x1200 | bus_addr | 2023.12.01 |
 * | sony_imx136_parallel | 1/2.8-Inch | 1920x1200 | bus_addr, bayer_pattern | 2023.12.01 |
 * | sony_imx172 | 1/2.5-Inch | 4096x2160 | bus_addr, lane, vinc_id | 2023.12.01 |
 * | sony_imx174 | 1/1.2-Inch | 1936x1216 | bus_addr | 2023.12.01 |
 * | sony_imx178 | 1/1.8-Inch | 3096x2080 | bus_addr, lane | 2024.01.16 |
 * | sony_imx183 | / | 5544x3694 | bus_addr, lane, vinc_id | 2023.12.01 |
 * | sony_imx185 | 1/1.9-Inch | 1920x1200 | bus_addr | 2024.01.16 |
 * | sony_imx185_mipi | 1/1.9-Inch | 1920x1200 | bus_addr | 2024.01.16 |
 * | sony_imx185_plvds | 1/1.9-Inch | 1920x1200 | bus_addr | 2024.01.16 |
 * | sony_imx224 | 1/3-Inch | 1280x960 | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_imx224_mipi | 1/3-Inch | 1280x960 | bus_id, addr, vinc_id, lane | 2024.01.16 |
 * | sony_imx226 | 1/1.7-Inch | 4168x3062 | bus_addr, lane | 2023.12.01 |
 * | sony_imx250 | 2/3-Inch | 2464x2056 | bus_addr, color, xtrig, lane | 2024.01.16 |
 * | sony_imx264 | 2/3-Inch | 2448x2048 | bus_id, addr, vinc_id, xtrig, frameset, mclk_mode, slave, lane_mux | 2024.01.16 |
 * | sony_imx265 | 1/1.8-Inch | 2064x1544 | bus_id, cs_id, vinc_id, xtrig, slave, frameset | 2023.12.01 |
 * | sony_imx274 | 1/2.5-Inch | 3864x2202 | bus_addr, lane | 2023.12.01 |
 * | sony_imx274_mipi | 1/2.5-Inch | 3864x2202 | bus_id, addr, vinc_id, vs_dly_lines | 2024.01.16 |
 * | sony_imx277 | 1/2.3-Inch | 4152x3062 | bus_addr, compression | 2023.12.01 |
 * | sony_imx290 | 1/2.8-Inch | 1945x1097 | bus_addr | 2024.01.16 |
 * | sony_imx290_mipi | 1/2.8-Inch | 1945x1097 | bus_id, addr, lane, vinc_id | 2024.01.16 |
 * | sony_imx291 | 1/2.8-Inch | 1945x1097 | bus_addr | 2024.01.16 |
 * | sony_imx291_mipi | 1/2.8-Inch | 1945x1097 | bus_addr | 2024.01.16 |
 * | sony_imx296_mipi | 1/2.9-Inch | 1440x1080 | bus_id, addr, vinc_id, color, xtrig, slave, frameset | 2024.01.16 |
 * | sony_imx299_mipi | 4/3-Inch | 3792x2824 | bus_addr, dual_gain | 2024.01.16 |
 * | sony_imx305 | / | 4096x2160 | bus_id, addr, vinc_id, slave, frameset | 2024.01.16 |
 * | sony_imx307 | 1/2.8-Inch | 1945x1097 | bus_addr, slave | 2024.01.16 |
 * | sony_imx307_mipi | 1/2.8-Inch | 1945x1097 | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_imx322 | 1/2.9-Inch | 1936x1097 | bus_addr | 2024.01.16 |
 * | sony_imx326 | 1/2.9-Inch | 3096x2196 | bus_addr, lane | 2023.12.01 |
 * | sony_imx326_mipi | 1/2.9-Inch | 3096x2196 | bus_addr | 2024.01.16 |
 * | sony_imx327 | 1/2.8-Inch | 1945x1097 | bus_id, addr, vinc_id, xvs_out, slave | 2024.01.16 |
 * | sony_imx327_mipi | 1/2.8-Inch | 1945x1097 | bus_id, addr, ir_mode, vinc_id, xvs_out | 2024.01.16 |
 * | sony_imx334_mipi | 1/1.8-Inch | 3864x2180 | bus_id, addr, vinc_id, lane, vc, slave, inck_mode | 2024.01.16 |
 * | sony_imx335_mipi | 1/2.8-Inch | 2592x1944 | bus_id, addr, vinc_id, slave, xvs_out, inck_mode, dynamic_offset | 2024.01.16 |
 * | sony_imx347_mipi | 1/2.8-Inch | 2688x1520 | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_imx377_mipi | 1/2.3-Inch | 4152x3062 | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_imx385 | 1/2-Inch | 1945x1097 | bus_id, addr, vinc_id, lane, dynamic_offset | 2024.01.16 |
 * | sony_imx385_mipi | 1/2-Inch | 1945x1097 | bus_id, addr, vinc_id, dynamic_offset | 2024.01.16 |
 * | sony_imx390_mipi | 1/2.7-Inch | 2017x1217 | bus_id, addr, vinc_id, calb_en | 2024.01.16 |
 * | sony_imx408_mipi | 1/3.61-Inch | 1944x1104 | bus_addr, lane | 2024.01.16 |
 * | sony_imx412_mipi | 1/2.3-Inch | 4056x3040 | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_imx415_mipi | 1/2.8-Inch | 3840x2160 | bus_id, addr, vinc_id, vc, slave, inck_mode | 2024.01.16 |
 * | sony_imx422 | 1/1.7-Inch | 1632x1248 | bus_id, addr, vinc_id, xtrig | 2024.01.16 |
 * | sony_imx455 | 1/2.5-Inch | 9568x6380 | bus_addr, fpga, test | 2023.12.01 |
 * | sony_imx462_mipi | 1/2.8-Inch | 1945x1097 | bus_id, addr, slave, vinc_id, dynamic_offset | 2024.01.16 |
 * | sony_imx464_mipi | 1/1.8-Inch | 2688x1520 | bus_id, addr, vinc_id, vc | 2024.01.16 |
 * | sony_imx485_mipi | 1/1.2-Inch | 3840x2160 | bus_id, addr, vinc_id, slave | 2024.01.16 |
 * | sony_imx492 | 1/1.4-Inch | 8432x5680 | bus_addr | 2023.12.01 |
 * | sony_imx515_mipi | 1/2.8-Inch | 3840x2160 | bus_id, addr, vinc_id, vc | 2024.01.16 |
 * | sony_imx542 | 1/1-Inch | 5328x3040 | bus_id, addr, vinc_id, xtrig, slave | 2024.01.16 |
 * | sony_imx566_mipi | 2/3-Inch | 2856x2848 | bus_id, addr, vinc_id, xtrig, slave, frameset | 2024.01.16 |
 * | sony_imx568_mipi | 1/1.8-Inch | 2432x2048 | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_imx571 | 1/1.8-Inch | 6244x4186 | bus_addr, fpga, test | 2023.12.20 |
 * | sony_imx577_mipi | 1/2.3-Inch | 4072x3176 | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_imx585_mipi | 1/1.2-Inch | 3840x2160 | bus_id, addr, vinc_id, slave, exp_gain | 2024.01.16 |
 * | sony_imx586_mipi | 1/2.0-Inch | 8000x6000 | bus_id, addr, vinc_id, cphy, cphy_rate, pdaf | 2024.01.16 |
 * | sony_imx623_mipi | 1/2.42-Inch | 1936x1552 | bus_id, addr, vinc_id, drive_mode | 2024.01.16 |
 * | sony_imx662_mipi | 1/2.8-Inch | 1920x1080 | bus_id, addr, vinc_id, slave, vc, exp_gain, dynamic_offset | 2024.01.16 |
 * | sony_imx664_mipi | 1/1.8-Inch | 2704x1560 | bus_id, addr, vinc_id, gain_ratio, dynamic_offset | 2024.01.16 |
 * | sony_imx675_mipi | 1/2.8-Inch | 2608x1964 | bus_id, addr, vinc_id, slave, dynamic_offset, lane, gain_ratio, inck_mode, vc | 2024.01.16 |
 * | sony_imx676_mipi | 1/1.6-Inch | 3552x3552 | bus_id, addr, vinc_id, slave, lane, inck_mode, gain_ratio | 2024.01.16 |
 * | sony_imx678_mipi | 1/1.8-Inch | 3864x2180 | bus_id, addr, vinc_id, dynamic_offset, vc, exp_gain, slave, lane, inck_mode, ob_capture, vs_dly_lines | 2024.01.16 |
 * | sony_imx715_mipi | 1/2.8-Inch | 3840x2160 | bus_id, addr, vinc_id, vc, slave | 2024.01.16 |
 * | sony_imx989_mipi | 1/0.98-Inch | 8192x6144 | bus_id, addr, vinc_id, cphy, pdaf | 2024.01.16 |
 * | st_vg5761_mipi | 1/2.5-Inch | 1944x1204 | bus_id, addr, vinc_id, strobe_mode, fsync, low_rate | 2024.01.16 |
 * | superpix_sp2309_mipi | 1/2.7-Inch | 1920x1080 | bus_id, addr, vinc_id | 2024.01.16 |


 * - - - -
 * @subsection tof_parm_table 2.2 TOF Sensor Parameters Table
 * Below table shows TOF sensors and their parameters.
 *
 * | Sensor | Parameters | Last Mod Time |
 * | :----- | :------ | :---- |
 * | adi_adsd3500 | bus_id, addr, vinc_id | 2024.01.16 |
 * | gp_tof75027_mipi_brg | addr, brg_id | 2023.12.01 |
 * | infineon_irs2877a_brg | addr, brg_id, version | 2023.12.01 |
 * | infineon_irs2877c | bus_id, addr, vinc_id, version | 2024.01.16 |
 * | infineon_irs2877c_brg | addr, brg_id, version | 2023.12.01 |
 * | panasonic_mn34906bl | bus_id, addr, vinc_id | 2024.01.16 |
 * | sony_cxd5639_imx570_mipi | bus_id, addr, vinc_id, main_fw, sub_fw | 2024.01.16 |
 * | sony_imx316_mipi | bus_id, addr, vinc_id, dual_freq, err_flag, tof_mode | 2024.01.16 |
 * | sony_imx456_mipi | bus_id, addr, vinc_id, freq_20m, err_flag, tof_mode | 2024.01.16 |
 * | sony_imx528_mipi | bus_id, addr, vinc_id, freq_mode, binning, slave, ld_type | 2024.01.16 |


 * - - - -
 * @section brg_sensor_parm_table 3. Bridge Sensor Parameters Table
 * Below tables show serdes / bridge sensors and their parameters.
 *
 * | Serdes | Parameters | Last Mod Time |
 * | :----- | :------ | :---- |
 * | ambrg | reset_all | 2024.01.22 |
 * | b5 | id, interlace, ratio, lane, vout_lane, reverse, vinc_id | 2023.12.01 |
 * | b6 | id, interlace, ratio, rate, vinc_id | 2023.12.01 |
 * | b8 | id, interlace, ratio, rate, vinc_id, ir_gpio, sl_gpio, set_vin_first | 2023.12.01 |
 * | maxim_9286 | id, interlace, vinc_id, lccen_gpio, sen_rst_gpio, data_rate, fsync, dts_addr, data_reverse | 2023.12.01 |
 * | maxim_9288 | id, interlace, vinc_id, dts_addr, lccen_gpio, gpi_o | 2023.12.01 |
 * | maxim_9296 | id, interlace, vinc_id, gmsl_mode, lccen_gpio, sen_pwr_gpio, sen_rst_gpio, hsync_gpio, fsync_gpio, dts_addr, mfp4_clk, gyro_test, samebus_num, vc, port_mode, use_max20087, double_pixel, def_ser_addr | 2024.01.12 |
 * | maxim_96712 | id, id_ext, interlace, vinc_id, gmsl_mode, poc_pwr_gpio, sen_pwr_gpio, sen_rst_gpio, hsync_gpio, fsync_gpio, dts_addr, vc, port_mode, mfp4_clk, test_mode, max9295d, double_pixel, gmsl_spi_mode, gmsl_spi_clk, poc_rst_time, use_max20087, v300, def_ser_addr | 2024.01.12 |
 * | maxim_96716 | id, vinc_id, gmsl_mode, sen_pwr_gpio, sen_rst_gpio, hsync_gpio, fsync_gpio, dts_addr, mfp4_clk, port_mode, double_pixel, def_ser_addr | 2024.01.18 |
 * | nextchip_n4 | id, n4_id, vinc_id, dts_addr, fhd_mode, ntsc_mode | 2023.12.01 |
 * | techpoint_tp2855 | id, vinc_id, dts_addr, tvi | 2024.01.22 |
 * | ti_ds90ub954 | id, vinc_id, mode, stp_mode, test_mode, dts_addr, aeq, sen_rst_gpio, fsync_gpio, fsync_int, io_1p8 | 2023.12.01 |
 * | ti_ds90ub964 | id, vinc_id, mode, stp_mode, test_mode, dts_addr, aeq, sen_rst_gpio, fsync_gpio, fsync_int, io_1p8, dual_port | 2023.12.01 |

 * Below table shows parameters of sensors over serdes.
 * | Sensor | Optical Format | Max Resolution | Parameters | Last Mod Time |
 * | :----- | :------- | :--- | :--- | :--- |
 * | ambds_brg | / | / | addr, brg_id, sync_phase, yuv_pix_order, slave, mipi, lane, w, h, start_x, start_y, fps, bits, yuv_mode, clk, sensor_id, auto_det | 2024.01.22 |
 * | micron_ar0230_brg | 1/2.7-Inch | 1928x1088 | addr, brg_id | 2023.12.01 |
 * | omnivision_os02h10_mipi_brg | 1/2.8-Inch | 1920x1080 | addr, brg_id, fsync | 2023.12.01 |
 * | omnivision_os05a10_mipi_brg | 1/2.7-Inch | 2688x1944 | addr, brg_id, fsync | 2023.12.01 |
 * | omnivision_os08a10_mipi_brg | 1/2-Inch | 3840x2160 | addr, brg_id, fsync | 2023.12.01 |
 * | omnivision_ov10640_brg | 1/4-Inch | 1288x1088 | addr, brg_id, fsync | 2023.12.01 |
 * | omnivision_ov2311_mipi_brg | 1/2.9-Inch | 1600x1300 | addr, brg_id, ir_mode, led_on, fsync, frameset | 2023.12.01 |
 * | omnivision_ov2718_mipi_brg | 1/3-Inch | 1936x1096 | addr, brg_id, lane | 2023.12.01 |
 * | omnivision_ov2718_parallel_brg | 1/3-Inch | 1936x1096 | addr, brg_id | 2023.12.01 |
 * | omnivision_ov2775_mipi_brg | 1/3-Inch | 1936x1096 | addr, brg_id, lane | 2023.12.01 |
 * | omnivision_ov2778_mipi_brg | 1/2.9-Inch | 1936x1096 | addr, brg_id, fsync, delay | 2023.12.01 |
 * | omnivision_ov2778_parallel_brg | 1/2.9-Inch | 1936x1096 | addr, brg_id | 2023.12.01 |
 * | omnivision_ov9281_brg | 1/4-Inch | 1296x816 | addr, brg_id | 2024.01.11 |
 * | omnivision_ov9284_brg | 1/4-Inch | 1296x816 | addr, brg_id, led_on, vs_ilpwm | 2023.12.01 |
 * | omnivision_ov9284_mipi_brg | 1/4-Inch | 1296x816 | addr, brg_id, led_on, fsync, frameset | 2023.12.01 |
 * | omnivision_ov9706_parallel_brg | 1/3.8-Inch | 1392x976 | addr, brg_id, fsync | 2023.12.01 |
 * | omnivision_ox03c10_mipi_brg | 1/2.6-Inch | 1920x1280 | addr, brg_id, debug_mode, fsync, mclk_mode | 2023.12.05 |
 * | omnivision_ox03f10_mipi_brg | 1/2.44-Inch | 1920x1536 | addr, brg_id, debug_mode, fsync, mclk_mode | 2023.12.05 |
 * | omnivision_ox05b1s_mipi_brg | 1/2.53-Inch | 2592x1944 | addr, brg_id, led_on, frameset | 2023.12.01 |
 * | omnivision_ox08b40_mipi_brg | 1/2.6-Inch | 3840x2160 | addr, brg_id, debug_mode, fsync, mclk_mode | 2023.12.05 |
 * | omnivision_ox08c4c_mipi_brg | 1/1.73-Inch | 3840x2160 | addr, brg_id, debug_mode, fsync, mclk_mode | 2023.12.01 |
 * | onsemi_ar0132_parallel_brg | 1/3.2-Inch | / | addr, brg_id | 2023.12.01 |
 * | onsemi_ar0135_parallel_brg | 1/3-Inch | 1280x960 | addr, brg_id, led_on | 2023.12.01 |
 * | onsemi_ar0144_mipi_brg | 1/4-Inch | 1280x800 | addr, brg_id, led_on, slave | 2023.12.01 |
 * | onsemi_ar0144_parallel_brg | 1/4-Inch | 1280x800 | addr, brg_id, led_on, slave | 2023.12.01 |
 * | onsemi_ar0147_mipi_brg | 1/4-Inch | 1344x968 | addr, brg_id | 2023.12.01 |
 * | onsemi_ar0147_parallel_brg | 1/4-Inch | 1344x968 | addr, brg_id | 2023.12.01 |
 * | onsemi_ar0220_mipi_brg | 1/1.8-Inch | 1828x948 | addr, brg_id, slave, trigger_gpio | 2023.12.01 |
 * | onsemi_ar0231_mipi_brg | 1/2.7-Inch | 1928x1208 | addr, brg_id, slave, trigger_gpio | 2023.12.01 |
 * | onsemi_ar0231_parallel_brg | 1/2.7-Inch | 1928x1208 | addr, brg_id, slave, trigger_gpio | 2023.12.01 |
 * | onsemi_ar0233_mipi_brg | 1/2.5-Inch | 2048x1280 | addr, super_gain, brg_id, slave, trigger_gpio | 2023.12.01 |
 * | onsemi_ar0234_mipi_brg | 1/2.6-Inch | 1920x1200 | addr, brg_id, slave, trigger_gpio | 2023.12.01 |
 * | onsemi_ar0237_brg | 1/2.7-Inch | 1928x1088 | addr, ir_mode, brg_id | 2023.12.01 |
 * | onsemi_ar0239_mipi_brg | 1/3-Inch | 1928x1188 | addr, ir_mode, brg_id, slave | 2023.12.01 |
 * | onsemi_ar0323_mipi_brg | 1/2-Inch | 2880x1080 | addr, brg_id | 2023.12.01 |
 * | onsemi_ar0341_mipi_brg | 1/3.6-Inch | 1928x1544 | addr, brg_id | 2024.01.18 |
 * | onsemi_ar0820_mipi_brg | 1/2-Inch | 3848x2168 | addr, brg_id | 2023.12.01 |
 * | onsemi_ar0822_mipi_brg | 1/2-Inch | 3848x2168 | addr, brg_id | 2023.12.01 |
 * | samsung_s5k1h1_mipi_brg | 1/1.7-Inch | 3856x2168 | addr, brg_id | 2024.01.12 |
 * | smartsens_sc533at_mipi_brg | 1/1.72-Inch | 3840x2160 | addr, brg_id, led_on | 2024.01.12 |
 * | sony_imx274_mipi_brg | 1/2.5-Inch | 3864x2202 | addr, brg_id | 2023.12.01 |
 * | sony_imx290_brg | 1/2.8-Inch | 1945x1097 | addr, brg_id | 2023.12.01 |
 * | sony_imx290_mipi_brg | 1/2.8-Inch | 1945x1097 | addr, brg_id, slave | 2023.12.01 |
 * | sony_imx296_mipi_brg | 1/2.9-Inch | 1440x1080 | addr, brg_id, color, xtrig, slave | 2023.12.01 |
 * | sony_imx307_mipi_brg | 1/2.8-Inch | 1945x1097 | addr, brg_id | 2023.12.01 |
 * | sony_imx327_mipi_brg | 1/2.8-Inch | 1945x1097 | addr, brg_id, ir_mode, xvs_out | 2023.12.01 |
 * | sony_imx335_mipi_brg | 1/2.8-Inch | 2592x1944 | addr, brg_id, slave, xvs_out, inck_mode | 2023.12.01 |
 * | sony_imx390_mipi_brg | 1/2.7-Inch | 2017x1217 | addr, brg_id, fsync, calb_en | 2023.12.01 |
 * | sony_imx415_mipi_brg | 1/2.8-Inch | 3840x2160 | addr, brg_id, slave | 2023.12.01 |
 * | sony_imx424_mipi_brg | 1/1.7-Inch | 3840x1920 | addr, brg_id, fsync | 2023.12.01 |
 * | sony_imx462_mipi_brg | 1/2.8-Inch | 1945x1097 | addr, brg_id, slave | 2023.12.01 |
 * | sony_imx490_mipi_brg | 1/1.55-Inch | 2880x1860 | addr, brg_id, fsync | 2023.12.01 |
 * | sony_imx623_mipi_brg | 1/2.42-Inch | 1936x1552 | addr, brg_id, drive_mode | 2023.12.01 |
 * | sony_imx662_mipi_brg | 1/2.8-Inch | 1920x1080 | addr, brg_id, slave | 2023.12.01 |
 * | sony_imx675_mipi_brg | 1/2.8-Inch | 2608x1964 | brg_id, addr, slave, lane | 2023.12.01 |
 * | sony_imx728_mipi_brg | 1/1.72-Inch | 3840x2160 | addr, brg_id | 2023.12.01 |
 * | st_vb1940_mipi_brg | 1/2.5-Inch | 2560x1984 | addr, brg_id | 2023.12.01 |
 * | st_vg1762_mipi_brg | 1/2.5-Inch | 1944x1204 | addr, brg_id, strobe_mode, fsync, low_rate, frameset, expo_ratio, mclk_mode | 2023.12.01 |
 * | st_vg5761_mipi_brg | 1/2.5-Inch | 1944x1204 | addr, brg_id, strobe_mode, fsync, low_rate | 2023.12.01 |

 * - - - -

 * @section CV5x_sensor_tuning_table 4. CV5x Sensor Tuning Table
 * Below tables shows tuned sensor of different usages.
 *     - Parameters @b liso in ISP Mode means the tuning data is applied when system is set in encode mode 0/1.
 *     - Parameters @b aliso in ISP Mode means the tuning data is applied when system is set in encode mode 3/5.
 *     - Parameters @b fusion in ISP Mode means the tuning data is applied when system is set in encode mode 2/4.
 *
 * @subsection img_cv5x_table_ipc 4.1 Sensor tuning table for IPC
 * | Sensor Name | Bayer Pattern | HDR Mode | ISP Mode | Last Mod Time |
 * | :---: | :----: | :----: | :----: | :----: |
 * | ar2020 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | ar2020 | rgb | buildin-wdr | aliso | 2024.01.08  |
 * | ar2020 | rgb | linear | aliso | 2024.01.08  |
 * | ar2020 | rgb | linear | liso | 2024.01.08  |
 * | bypass | / | 2xhdr | aliso | 2024.01.08  |
 * | bypass | / | 2xhdr | liso | 2024.01.08  |
 * | bypass | / | linear | aliso | 2024.01.08  |
 * | bypass | / | linear | liso | 2024.01.08  |
 * | imx274 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx274 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx274 | rgb | 2xhdr | nn | 2024.01.08  |
 * | imx274 | rgb | linear | aliso | 2024.01.08  |
 * | imx274 | rgb | linear | liso | 2024.01.08  |
 * | imx274 | rgb | linear | nn | 2024.01.08  |
 * | imx334 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx334 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx334 | rgb | linear | aliso | 2024.01.08  |
 * | imx334 | rgb | linear | liso | 2024.01.08  |
 * | imx335 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx335 | rgb | linear | aliso | 2024.01.08  |
 * | imx335 | rgb | linear | liso | 2024.01.08  |
 * | imx415 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx415 | rgb | linear | aliso | 2024.01.08  |
 * | imx455 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx455 | rgb | linear | aliso | 2024.01.08  |
 * | imx455 | rgb | linear | liso | 2024.01.08  |
 * | imx462 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx462 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx462 | rgb | linear | aliso | 2024.01.08  |
 * | imx462 | rgb | linear | liso | 2024.01.08  |
 * | imx492 | rgb | linear | liso | 2024.01.08  |
 * | imx515 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx515 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx515 | rgb | linear | liso | 2024.01.08  |
 * | imx586 | rgb | linear | aliso | 2024.01.08  |
 * | imx586 | rgb | linear | liso | 2024.01.08  |
 * | imx662 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx662 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx662 | rgb | 2xhdr | nn | 2024.01.08  |
 * | imx662 | rgb | linear | aliso | 2024.01.08  |
 * | imx662 | rgb | linear | liso | 2024.01.08  |
 * | imx662 | rgb | linear | nn | 2024.01.08  |
 * | imx664 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx664 | rgb | 2xhdr | nn | 2024.01.08  |
 * | imx664 | rgb | 3xhdr | aliso | 2024.01.08  |
 * | imx664 | rgb | linear | aliso | 2024.01.08  |
 * | imx664 | rgb | linear | nn | 2024.01.08  |
 * | imx675 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx675 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx675 | rgb | linear | aliso | 2024.01.08  |
 * | imx675 | rgb | linear | liso | 2024.01.08  |
 * | imx678 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx678 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx678 | rgb | 2xhdr | nn | 2024.01.08  |
 * | imx678 | rgb | 3xhdr | aliso | 2024.01.08  |
 * | imx678 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx678 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx678 | rgb | linear | aliso | 2024.01.08  |
 * | imx678 | rgb | linear | liso | 2024.01.08  |
 * | imx678 | rgb | linear | nn | 2024.01.08  |
 * | imx715 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | imx715 | rgb | 2xhdr | liso | 2024.01.08  |
 * | imx715 | rgb | 3xhdr | aliso | 2024.01.08  |
 * | imx715 | rgb | 3xhdr | liso | 2024.01.08  |
 * | imx715 | rgb | linear | aliso | 2024.01.08  |
 * | imx715 | rgb | linear | liso | 2024.01.08  |
 * | os05b10 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | os05b10 | rgb | 2xhdr | liso | 2024.01.08  |
 * | os05b10 | rgb | linear | aliso | 2024.01.08  |
 * | os05b10 | rgb | linear | liso | 2024.01.08  |
 * | os08a10 | rgb | 2xhdr | aliso | 2024.01.08  |
 * | os08a10 | rgb | 2xhdr | liso | 2024.01.08  |
 * | os08a10 | rgb | linear | aliso | 2024.01.08  |
 * | os08a10 | rgb | linear | liso | 2024.01.08  |
 * | yuv_input | / | / | aliso | 2024.01.08  |
 * | yuv_input | / | / | liso | 2024.01.08  |
 * - - - -

 * @section CV72_sensor_tuning_table 5. CV72 Sensor Tuning Table
 * Below tables shows tuned sensor of different usages.
 *     - Parameters @b liso in ISP Mode means the tuning data is applied when system is set in encode mode 0/1.
 *     - Parameters @b aliso in ISP Mode means the tuning data is applied when system is set in encode mode 3/5.
 *     - Parameters @b fusion in ISP Mode means the tuning data is applied when system is set in encode mode 2/4.
 *
 * @subsection img_cv72_table_dvr 5.1 Sensor tuning table for DVR
 * | Sensor Name | Bayer Pattern | HDR Mode | ISP Mode | Last Mod Time |
 * | :---: | :----: | :----: | :----: | :----: |
 * | ov2735 | rgb | linear | liso | 2023.11.24  |
 * | ov2775 | rgb | buildin-wdr | liso | 2023.11.24  |
 * | ov9732 | rgb | linear | liso | 2023.11.24  |
 * - - - -
 *
 * @subsection img_cv72_table_emirror 5.2 Sensor tuning table for EMIRROR
 * | Sensor Name | Bayer Pattern | HDR Mode | ISP Mode | Last Mod Time |
 * | :---: | :----: | :----: | :----: | :----: |
 * | imx623 | rgb | buildin-wdr | liso | 2023.11.24  |
 * - - - -
 *
 * @subsection img_cv72_table_ipc 5.3 Sensor tuning table for IPC
 * | Sensor Name | Bayer Pattern | HDR Mode | ISP Mode | Last Mod Time |
 * | :---: | :----: | :----: | :----: | :----: |
 * | ar2020 | rgb | 2xhdr | aliso | 2023.11.17  |
 * | ar2020 | rgb | buildin-wdr | aliso | 2023.11.20  |
 * | ar2020 | rgb | linear | aliso | 2023.11.20  |
 * | ar2020 | rgb | linear | liso | 2023.11.17  |
 * | imx274 | rgb | 2xhdr | aliso | 2023.09.26  |
 * | imx274 | rgb | 2xhdr | liso | 2023.11.24  |
 * | imx274 | rgb | linear | aliso | 2023.09.26  |
 * | imx274 | rgb | linear | liso | 2023.11.24  |
 * | imx290 | rgb | 2xhdr | aliso | 2024.01.09  |
 * | imx290 | rgb | 2xhdr | liso | 2024.01.09  |
 * | imx290 | rgb | linear | aliso | 2024.01.09  |
 * | imx290 | rgb | linear | liso | 2024.01.09  |
 * | imx334 | rgb | 2xhdr | aliso | 2023.09.26  |
 * | imx334 | rgb | linear | aliso | 2023.09.26  |
 * | imx585 | rgb | 2xhdr | aliso | 2023.12.19  |
 * | imx585 | rgb | 2xhdr | liso | 2023.12.19  |
 * | imx585 | rgb | 2xhdr | nn | 2023.12.27  |
 * | imx585 | rgb | 2xhdr | aliso | 2023.12.19  |
 * | imx585 | rgb | 2xhdr | liso | 2023.12.19  |
 * | imx585 | rgb | linear | aliso | 2023.12.19  |
 * | imx585 | rgb | linear | liso | 2023.12.19  |
 * | imx585 | rgb | linear | nn | 2024.01.08  |
 * | imx664 | rgb | 2xhdr | aliso | 2023.12.21  |
 * | imx664 | rgb | 2xhdr | liso | 2023.12.21  |
 * | imx664 | rgb | 2xhdr | nn | 2023.12.21  |
 * | imx664 | rgb | linear | aliso | 2023.12.21  |
 * | imx664 | rgb | linear | liso | 2023.12.21  |
 * | imx664 | rgb | linear | nn | 2023.12.21  |
 * | imx676 | rgb | 2xhdr | aliso | 2023.09.26  |
 * | imx676 | rgb | 2xhdr | liso | 2023.11.24  |
 * | imx676 | rgb | linear | aliso | 2023.09.26  |
 * | imx676 | rgb | linear | liso | 2023.11.24  |
 * | imx678 | rgb | 2xhdr | aliso | 2023.09.26  |
 * | imx678 | rgb | aliso | litenn | 2023.12.21  |
 * | imx678 | rgb | 2xhdr | liso | 2023.11.24  |
 * | imx678 | rgb | liso | litenn | 2023.12.27  |
 * | imx678 | rgb | 2xhdr | nn | 2023.12.27  |
 * | imx678 | rgb | 2xhdr | aliso | 2023.09.26  |
 * | imx678 | rgb | 2xhdr | liso | 2023.11.24  |
 * | imx678 | rgb | linear | aliso | 2023.09.26  |
 * | imx678 | rgb | linear | liso | 2023.11.24  |
 * | imx678 | rgb | linear | nn | 2023.12.27  |
 * | os05a10 | rgb | 2xhdr | aliso | 2023.09.26  |
 * | os05a10 | rgb | 2xhdr | liso | 2023.11.24  |
 * | os05a10 | rgb | linear | aliso | 2023.09.26  |
 * | os05a10 | rgb | linear | liso | 2023.11.24  |
 * | os08a10 | rgb | 2xhdr | aliso | 2023.09.26  |
 * | os08a10 | rgb | 2xhdr | liso | 2023.11.24  |
 * | os08a10 | rgb | linear | aliso | 2023.09.26  |
 * | os08a10 | rgb | linear | liso | 2023.11.24  |
 * | yuv_input | / | / | aliso | 2024.01.03  |
 * | yuv_input | / | / | liso | 2023.09.26  |
 * - - - -
 *
 * @subsection img_cv72_table_stereo 5.4 Sensor tuning table for STEREO
 * | Sensor Name | Bayer Pattern | HDR Mode | ISP Mode | Last Mod Time |
 * | :---: | :----: | :----: | :----: | :----: |
 * | imx390 | rgb | buildin-wdr | liso | 2023.11.24  |
 * - - - -

 * @section CV3_sensor_tuning_table 6. CV3 Sensor Tuning Table
 * Below tables shows tuned sensor of different usages.
 *     - Parameters @b liso in ISP Mode means the tuning data is applied when system is set in encode mode 0/1.
 *     - Parameters @b aliso in ISP Mode means the tuning data is applied when system is set in encode mode 3/5.
 *     - Parameters @b fusion in ISP Mode means the tuning data is applied when system is set in encode mode 2/4.
 *
 * @subsection img_cv3_table_robot 6.1 Sensor tuning table for ROBOT
 * | Sensor Name | Bayer Pattern | HDR Mode | ISP Mode | Last Mod Time |
 * | :---: | :----: | :----: | :----: | :----: |
 * | os08a10 | rgb | linear | liso | 2023.12.08  |
 * - - - -
 *
 * @subsection img_cv3_table_stereo 6.2 Sensor tuning table for STEREO
 * | Sensor Name | Bayer Pattern | HDR Mode | ISP Mode | Last Mod Time |
 * | :---: | :----: | :----: | :----: | :----: |
 * | imx390 | rgb | buildin-wdr | liso | 2023.12.08  |
 * | yuv_input | / | / | liso | 2023.12.08  |
 * - - - -

 * @section sensor_lic 7. License
 * Copyright (c) 2024 Ambarella International LP.
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
 * @file doc_sys_sensor_driver_installation.h
 * @brief
 * @version 1.0
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
 * @page page_sys_sensor_driver_installation Sensor & SERDES Driver Installation
 *
 * @section Sensor_driver_installation_history 0. Revision History
 *  | Library Version  | Updated Date     | Modification         |
 *  | :---             | :--------------- |:-------------------- |
 *  | 1.0.0 | 20220110 | Initial Version    |
 *  | 1.0.1 | 20220119 | Added sensor driver installation related chapters |
 *  | 1.0.2 | 20220328 | Added Section @ref CV52_Multi_VIN_Design |
 *  | 1.0.3 | 20220726 | Correct Sensor & SERDES driver installation error description |
 *  | 1.0.4 | 20230130 | Added Section @ref ambds_usage |
 *
 * - - - -
 *
 * @section sensor_driver_module_parameters 1. Sensor Driver Module Parameters
 * Sensor driver module parameters table: @ref sensor_parm_table "2. Sensor Module Parameters Table".
 *
 * - - - -
 *
 * @section serdes_driver_module_parameters 2. SERDES Driver Module Parameters
 * Bridge sensor parameters table: @ref brg_sensor_parm_table "3. Bridge Sensor Parameters Table".
 *
 * - - - -
 *
 * @section driver_installation_guide 3. Driver Installation Guide
 * @subsection ambds_usage 3.1 Dummy Sensor Driver Usage
 * In some special cases, a dummy sensor is needed to configure the video input (VIN),
 * and thus enable the whole digital signal processor (DSP) pipeline.<br>
 * @image html dummy_sensor_driver_data_flow_overview.jpg "Figure 3-1. Sensor Data Playback Flow for Dummy Sensor Driver."
 * The user can choose either of the two available dummy sensor drivers in SDK
 * according to whether the serializer / deserializer (SERDES) is used:
 * - <B>Dummy Sensor Driver</B><br>
 *   This driver can support both YUV or RAW input which does not need real
 *   configurations. It provides 1080p, 720p, and 4K resolutions by default.
 *   If the other resolution is used, the user can load this dummy driver with the
 *   video format parameters to specify the resolution.<br>
 *   There are two main use cases for this driver:<br>
 *   - Virtual VIN mode used by the encode from RAW (EFR).<br>
 *     The dummy sensor driver is `ambds` and the VIN PHY will not be
 *     initialized in this mode. For more usages, the user can refer to
 *     @ref efr_exp "EFR Examples".
 *   - Input RAW data through MIPI® interface to VIN PHY.<br>
 *     To receive the RAW data through the MIPI / LVCOMS interface, the VIN PHY
 *     must be initialized in the dummy sensor driver `ambds`. The following
 *     examples show how the dummy driver is used for such a use case:<br>
 *     <B>Example 1:</B> Below is an example on how the sensor raw data flow
 *     is handled by the dummy sensor drivers. For the dummy sensor driver part,
 *     if the input data is "IMX274 MIPI format (1280x960 10bits at 54fps)", the
 *     user can use the following commands to load the dummy driver:
 *     @code
 *     board# init.sh --na; modprobe ambds mipi=1 vinc_id=8 yuv_mode=0 yuv_pix_order=0 lane=4 w=1208 h=960 bits=10 fps=9481481 sensor_id=0x3014
 *     board# test_aaa_service -a&
 *     board# test_encode --resource-cfg vin0_1280x960_10bits_linear.lua --vout-cfg vout_hdmi.lua
 *     @endcode
 *     @image html dummy_sensor_driver_usage_example.jpg "Figure 3-2. Dummy Sensor Driver Usage Example."
 *
 *     <B>Example 2:</B> Below is a brief example on a 4-lane MIPI YUV input
 *     dummy sensor.
 *     @code
 *     board# modprobe ambds yuv_mode=1 mipi=1 lane=4 vinc_id=0
 *     @endcode
 *
 *     <B>Example 3:</B> @ref expample_vout_mipi_raw8 "VOUT Example 28" is an
 *     example of how to enable the VIN of the board-2 via the ambds driver. In
 *     this example, the "sensor" is a 4-lane MIPI YUV input module.<br>
 *
 *     @note
 *     - VIN mode must be set to 0 (auto mode) in the lua script when the dummy
 *       driver is loaded with parameters `w` and `h` both specified.
 *     - The `w` and `h` are the width and height of the customized mode input.
 *     - The `lane` is the MIPI lane number.
 *     - The `sensor_id` is the sensor unique identifier. The unique identifier for IMX274 is 0x3014.
 *     - The `yuv_mode` is the VIN input data format, the `yuv_mode=0` indicates that it is a RGB data input.
 *     - For non-YUV input, the `yuv_pix_order` must be set to 0.
 *     - The module parameter `fps` is calculated by ( 512000000 / actual fps ).
 *       For 54 fps, it’s 512000000 / 54 = 9481481.
 *     - If multiple resolutions for dummy sensor driver are required, the user can
 *       modify the dummy sensor driver and add these resolutions into the video
 *       format table accordingly in `ambds_table.c`
 *     - Other driver parameters can be found in @ref sensor_parm_table "Sensor Module Parameters Table"
 *
 * - <B>Dummy Sensor Driver for Bridge</B><br>
 *   This driver is used with SERDES case together. The interface can be MIPI or
 *   LVCMOS for serializer to receive. It can support both YUV or RAW input
 *   which does not need real configurations.<br>
 *   For example, if ds90ub954 bridge is used and the input data is
 *   "IMX274 MIPI format (1280x960 10bits at 54fps)", the user can also refer to
 *   the <B>Example 1</B> above for the dummy sensor driver for bridge part and
 *   use the following commands to load this dummy driver:
 *   @code
 *   board# modprobe ds90ub954 id=0x1 vinc_id=8 mode=0
 *   board# modprobe ambds_brg mipi=1 yuv_mode=0 yuv_pix_order=0 lane=4 w=1280 h=960 bits=10 fps=9481481 sensor_id=0x3014
 *   board# test_aaa_service -a&
 *   board# test_encode --resource-cfg vin0_1280x960_10bits_linear.lua --vout-cfg vout_hdmi.lua
 *   @endcode
 *   @note
 *   - Some parameters' descriptions can be found in the section's note above.
 *   - Other driver parameters can be found in @ref brg_sensor_parm_table "Bridge Sensor Parameters Table"
 *
 * @subsection Multiple_Sensors_with_Different_Sensor_Types 3.2 Multiple Sensors with Different Sensor Types
 *
 * In this case, multiple sensor drivers are installed for the VIN controllers so that each sensor gets its own sensor
 * driver. While installing each sensor driver, users must specify the VIN controller ID and I2C bus ID using the
 * sensor driver module parameters "vinc_id" and "bus_id".<br>
 * Using imx274_mipi and imx290_mipi as examples, assume imx274_mipi is mounted on VIN8 and imx290_mipi on VIN0.
 * Specify "vinc_id=8" and "bus_id=3" while installing the imx274_mipi sensor driver. Alternatively, "vinc_id=0" and
 * "bus_id=5" are specified when the imx290_mipi sensor driver is installed.<br>
 *
 * For CV72, there is no need to specify bus_id. This is because all VIN controllers share I2C bus ID 0. Since
 * I2C bus ID 0 is the default value, so there is no need to speicfy this when performing sensor probe.
 *
 * @code
 * board_cv5x# modprobe imx274_mipi vinc_id=8 bus_id=3
 * board_cv5x# modprobe imx290_mipi vinc_id=0 bus_id=5
 * board_cv72# modprobe imx274_mipi vinc_id=8
 * @endcode
 *
 * @note
 * - The "bus_id=3" is the I2C bus ID specified for VIN controller 8 in the device tree. The "bus_id=5" is the I2C bus ID specified
 *   for VIN controller 0 in the device tree.
 * - For CV5 Timn EVK, VIN controller 8 and I2C bus 3 are bound together, VIN controller 0 and I2C bus 5 are bound together.
 *
 * @subsection Multiple_Sensors_with_the_same_sensor_type 3.3 Multiple Sensors with the Same Sensor Type
 *
 * In this case, one sensor driver is installed for multiple sensors connected to one or more VIN controllers. Using imx274_mipi
 * as an example, assume that there are quad imx274_mipi mounted on VIN8, VIN11, VIN0 and VIN4 for CV5x. Specify "vinc_id=0x40b8"
 * when installing the sensor driver. In "vinc_id=0x40b8", "8", "b" "0" and "4" are VIN controller ID. "bus_id" does not require to be
 * specified, as the sensor driver can query it from the device tree.<br>
 *
 * @code
 * board_cv5x# modprobe imx274_mipi vinc_id=0x40b8
 * @endcode
 *
 * @note
 * - In the first case, the same sensor driver cannot be installed twice.
 *
 * @subsection Sensors_with_SERDES_Bridge 3.4 Sensors with SERDES Bridge
 *
 * In this case, sensor drivers are installed for multiple sensors connected through one or more SERDES. To get this,
 * users need to install Ambarella bridge driver, SERDES driver and sensor drivers (SERDES version) sequentially.
 * When installing each SERDES driver, users must specify the bitmap of bridge ports where sensors are connected.
 * VIN controller ID module paramater can be specified optionally as it can be specified in the device tree. When
 * installing the sensor driver (SERDES version), users need to specify the bridge ID that it connects. The SERDES
 * and sensor driver module parameters are listed below.<br>
 *
 * <B>SERDES driver module parameters:</B><br>
 * - "id": the bitmap of sensor ports in the bridges of SERDES. Each 8-bit represents a SERDES bridge node "vinbrg(xxxx)"
 *   in DTS, and one bit is a SERDES port.
 * - "vinc_id": VIN controller ID to which SERDES connects. SERDES driver will query it from the device tree (DTS) first,
 *   if not, users must specify it as a module parameter. "dts_addr": if it is set to 1, SERDES driver will query SERDES
 *   configurations from "bus-addr" in DTS. The bit definition of "bus-addr"is as below. If it is not set, SERDES driver
 *   will use default values pre-defined in its driver. For I2C bus ID, SERDES driver always queries it from bit[19:16] of
 *   "bus-addr"despite that "dts_addr"is set or not.<br>
 *
 *  | Bit Field    | Description   |
 *  | :---         | :--------------  |
 *  | bit[7:0]     | Deserializer address         |
 *  | bit[15:8]    | Serializer address         |
 *  | bit[19:16]   | I2C bus ID                |
 *  | bit[31:20]   | Reserved for SERDES internal usage         |
 *
 * - "brg_id": bitmap of bridge on SERDES. It represents which bridge are the sensors connected. Each bit corresponds
 *    to a bridge. For example, "brg_id=0x1/0x2/0x4" means bridge 0/1/2, "brg_id=0x3" means bridge 0 and bridge 1.
 * - "slave" or "fsync": "slave/fsync=0" means the sensor runs at master mode. "slave=1" means the sensor runs at slave mode.
 *   "fsync=1"means the sensor runs at fsync mode.<br>
 *
 * The following diagram shows the topology among sensors, SERDES, and VINCs.
 * @image html Sensors_Serdes_VINC_Topology.jpg "Figure 3-1. Sensors-Serdes-VINC_Topology."
 * <B>Reference examples:</B><br>
 * @subsubsection example_serdes_connect1 Example 1.  Single ar0233_mipi_brg connects to MAX9296.
 * In this example, single ar0233_mipi_brg connects to MAX9296 bridge1's port0 for the board.
 *
 * @code
 * board# modprobe ambrg
 * board# modprobe max9296 id=0x100 vinc_id=0xb
 * board# modprobe ar0233_mipi_brg
 * @endcode
 *
 * Max9296 SERDES driver will find bridge node "vinbrg1" according to the module parameter: "id=0x100"(only port0 of bridge1
 * is specified) from "iav" node. "vinc_id=0xb" means it corresponds to VIN controller 11.<br>
 *
 * @subsubsection example_serdes_connect2 Example 2 Dual ar0231_mipi_brg connects to ds90ub954.
 * In this example, dual ar0231_mipi_brg connects to TIDS90UB954 bridge0's port0 and port1.
 *
 * @code
 * board# modprobe ambrg
 * board# modprobe ds90ub954 id=0x3 vinc_id=8
 * board# modprobe ar0231_mipi_brg slave=1
 * @endcode
 *
 * Ds90ub954 SERDES driver will find the bridge node "vinbrg0" according to the module parameter: "id=0x3"(port0 and port1 of
 * bridge0 are specified) from "iav" node. "vinc_id=8" means it corresponds to VIN controller 8.<br>
 *
 * @subsubsection example_serdes_connect3 Example 3 Dual ar0231_mipi_brg connects to dual ds90ub954.
 * In this example, one ar0231_mipi_brg connects to one TIDS90UB954 bridge0's port0, another ar0231_mipi_brg connects to another
 * TIDS90UB954 bridge1's port0 for the board.
 *
 * @code
 * board# modprobe ambrg
 * board# modprobe ds90ub954 id=0x101 vinc_id=0xb8
 * board# modprobe ar0231_mipi_brg
 * @endcode
 *
 * Ds90ub954 SERDES driver will find bridge nodes "vinbrg0" and "vinbrg1" according to the module parameter: "id=0x101" from "iav" node.
 * "vinc_id=0xb8" means it corresponds to VIN controller 8 and 11 respectively.<br>
 *
 * @subsubsection example_serdes_connect4 Example 4 Single ar0231_mipi_brg and ar0239_mipi_brg connect to dual ds90ub954.
 * In this example, one ar0231_mipi_brg connects to TIDS90UB954 bridge0's port0. The other ar0239_mipi_brg connects to another TIDS90UB954
 * bridge1's port0 for the board.
 *
 * @code
 * board# modprobe ambrg
 * board# modprobe ds90ub954 id=0x101 vinc_id=0xb8
 * board# modprobe ar0231_mipi_brg brg_id=0x1 // connect to bridge0 of ds90ub954
 * board# modprobe ar0239_mipi_brg brg_id=0x2 // connect to bridge1 of ds90ub954
 * @endcode
 *
 * Ds90ub954 SERDES driver will find bridge nodes "vinbrg0" and "vinbrg1" according to the module parameter: "id=0x101" from "iav" node.
 * "vinc_id=0xb8" means it corresponds to VIN controller 8 and 11 respectively.<br>
 *
 * @subsubsection example_serdes_connect5 Example 5 Single ar0231_mipi_brg and ar0239_mipi_brg connect to dual ds90ub954; ar0144_brg connects to max9288.
 * In this example, one ar0231_mipi_brg connects to TIDS90UB954 bridge0's port0. The other ar0239_mipi_brg connects to another TIDS90UB954
 * bridge1's port0. Another ar0144_brg connects to MAX9288 bridge2's port0.
 *
 * @code
 * board# modprobe ambrg
 * board# modprobe ds90ub954 id=0x101 vinc_id=0xb8
 * board# modprobe max9288 id=0x10000 vinc_id=0
 * board# modprobe ar0231_mipi_brg brg_id=0x1 // connect to bridge0 of ds90ub954
 * board# modprobe ar0239_mipi_brg brg_id=0x2 // connect to bridge1 of ds90ub954
 * board# modprobe ar0144_brg brg_id=0x4 // connect to bridge2 of max9288
 * @endcode
 *
 * Ds90ub954 SERDES driver will find bridge nodes "vinbrg0" and "vinbrg1" according to module parameter: "id=0x101" from "iav" node. "vinc_id=0xb8" means  * it corresponds to VIN controller 8 and 11 respectively.
 * Max9288 SERDES driver will find bridge node "vinbrg2" according to the module parameter: "id=0x10000" from "iav" node. "vinc_id=0" means it corresponds * to VIN controller 0.<br>
 *
 * @subsubsection example_serdes_connect6 Example 6 Quad os08a10_mipi_brg connects to dual MAX9296.
 * In this example, two MAX9296 SERDES are connected to VIN controller 8 and controller 11. Each SERDES has two ar0231_mipi_brg connected
 * to its port0 and port1.
 *
 * @code
 * board# modprobe ambrg
 * board# modprobe max9296 id=0x0303 vinc_id=0xb8
 * board# modprobe os08a10_mipi_brg fsync=1
 * @endcode
 *
 * Max9296 SERDES driver will find bridge nodes "vinbrg0" and "vinbrg1" according to the module parameter: "id=0x0303" from "iav" node.
 * As "vinc_id" is not specified in bridge nodes, users must specify "vinc_id=0xb8" through the module parameter.<br>
 * <B>DTS example configuration</B><br>
 *
 * @code
 * iav {
 *    ……
 *    Vinbrg0 {
 *       compatible = "ambarella,vinbrg";
 *       ……
 *       bus-addr = <0x30000>;
 *    };
 *    Vinbrg1 {
 *       compatible = "ambarella,vinbrg";
 *       ……
 *       bus-addr = <0x30001>;
 *     };
 *     ……
 * };
 * @endcode
 *
 * @subsubsection example_serdes_connect7 Example 7 Set up dual sensors with different modes from MAX9296.
 * This example shows how to set up dual sensor with different modes from MAX9296.
 *
 * @code
 * board# modprobe max9296 id=0x201 vc=1 dts_addr=1
 * board# modprobe os08a10_mipi_brg brg_id=0x1
 * board# modprobe imx290_mipi_brg brg_id=0x2 slave=1
 * @endcode
 *
 * @subsection Vsrc_id_recordering 3.5 Vsrc_id Reordering
 *
 * During the sensor driver installation, each sensor is enumerated as a VIN source (VSRC) device, and a unique vsrc_id is allocated for
 * each VSRC device. Each sensor has a different vsrc_id.<br>
 * Vsrc_id starts at zero and keeps incrementally increasing after each newly enumerated VSRC device is added. Therefore, the vsrc_id value
 * specified for each sensor depends on the installation order of the sensor driver.<br>
 * In the example provided in @ref Multiple_Sensors_with_Different_Sensor_Types "1. Multiple Sensors with Different Sensor Types", as the
 * imx274_mipi sensor driver is installed before imx290_mipi, "vsrc_id=0" will be specified for imx274_mipi, "vsrc_id=1" for imx290_mipi.<br>
 *
 * @code
 * board_cv5x# modprobe imx274_mipi vinc_id=8 bus_id=3	// vsrc_id = 0
 * board_cv5x# modprobe imx290_mipi vinc_id=0 bus_id=5	// vsrc_id = 1
 * @endcode
 *
 * If the sensor driver imx290_mipi is installed before imx274_mipi, "vsrc_id=0" will be specified for imx290_mipi, "vsrc_id=1" for imx274_mipi.
 *
 * @code
 * board_cv5x# modprobe imx290_mipi vinc_id=0 bus_id=5	// vsrc_id = 0
 * board_cv5x# modprobe imx274_mipi vinc_id=8 bus_id=3	// vsrc_id = 1
 * @endcode
 *
 * Some use cases require the order of the sensor's vsrc_id to stay the same despite the installation order of their sensor drivers.
 * In order to meet these requirements, the image audio video (IAV) driver supports the vsrc_id feature of reordering through the module parameter: "vsrc_id_reorder".
 * When it is enabled, vsrc_id specifies that each sensor will follow the same order with the VIN controllers that they are mounted on.  By default,
 * this will disable vsrc_id reordering.<br>
 * In the example above, when vsrc_id reordering is enabled, no matter the order of the sensor driver installation of imx274_mipi and imx290_mipi is,
 * "vsrc_id=0" will always be specified for imx274_mipi, "vsrc_id=1" for imx290_mipi, and so on.<br>
 *
 * @code
 * board_cv5x# modprobe iav vsrc_id_reorder=1
 * board_cv5x# modprobe imx274_mipi vinc_id=8 bus_id=3	// vsrc_id = 1
 * board_cv5x# modprobe imx290_mipi vinc_id=0 bus_id=5	// vsrc_id = 0
 * @endcode
 *
 * @subsection keep_broken_vsrc_id 3.6 Keep Broken Vsrc_id
 *
 * Sensor driver installation will probe the corresponding physical sensor proactively through the I2C or SPI bus. By default, if the sensor is
 * disconnected or broken and cannot be probed successfully, then the sensor drivers will not be installed.<br>
 * Some use cases with multiple sensors may require the sensor driver to be installed normally, even when the sensor is disconnected or broken.
 * For most cases, users should keep the vsrc_id of the other sensors unchanged.<br>
 * In order to meet these requirements, the IAV driver supports the feature of keeping broken vsrc_id with the module parameter: "keep_broken_vsrc".
 * When it is enabled, the sensor driver will always be installed no matter what the sensor status is. If the sensor cannot be probed, it will be
 * marked as broken. By default, this is disabled.<br>
 *
 * @code
 * board# modprobe iav keep_broken_vsrc=1
 * @endcode
 *
 * @subsection Specify_Target_Vsrc_num 3.7 Specify Target Vsrc_num
 *
 * The IAV driver supports specifying the target Vsrc number feature with the module parameter: "target_vsrc_num".  When it is specified, the user
 * application can only operate the sensor control after all of the sensor drivers are installed. This ensures that the sensor driver installation
 * is finished before any sensor control operations. By default, the target Vsrc number is 0, which means that the IAV driver will not check, even
 * if all of the sensor drivers are installed.<br>
 *
 * @code
 * board# modprobe iav target_vsrc_num=2
 * @endcode
 *
 * - - - -
 *
 * @section cv5x_multi_vin_support 4. Cooper EVK with Multi-VIN support
 * @subsection CV5_Multi_VIN_Design 4.1 CV5 Multi-VIN Design
 *
 * CV5x supports 4x native VIN controllers. Through MIPI virtual channel, it can be extended to 14x VIN controllers. It can
 * support various VIN interfaces including MIPI D/C-PHY, SLVS-EC, and SLVS. MIPI and SLVS-EC interfaces can be up to 16
 * lanes. SLVS interface can be up to 8 lanes.
 *
 * <table>
 * <tr>
 * <th><div style="width:120px"></div>VIN Slot Mode</div></th><th><div style="width:120px"></div>I2C Bus ID</th>
 * <th><div style="width:120px"></div>VIN Controller ID</div></th><th><div style="width:120px"></div>Type</th>
 * </tr>
 * <tr><td rowspan="7">SLVS + DPHY
 * <tr>			<td align="center">3/4</td><td align="center">8</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">9</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">10</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">11</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">12</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">13</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * <tr><td rowspan="5">SLVS-EC
 * <tr>			<td align="center">5</td><td align="center">0</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">1</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">2</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">3</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * <tr><td rowspan="5">DCPHY 0
 * <tr>			<td align="center">5</td><td align="center">0</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">1</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">2</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">3</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * <tr><td rowspan="5">DCPHY 1
 * <tr>			<td align="center">1</td><td align="center">4</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">5</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">6</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">7</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * </table>
 *
 * Currently, CV5 supports a 2~4 multiple-VIN design through SERDES with SLVS + DPHY VIN slot. The sensors must support a
 * 4-lane interface through either MIPI or SLVS. The following figure shows the sensor boards inserted into the SLVS + DPHY
 * VIN slot on the CV5 Timn board.
 *
 * @image html single_sensor_plug_into_CV5_Timn_Board.jpg "Figure 4-1. Single Sensor Boards Plug in CV5 Timn Board."
 *
 * - - - -
 *
 * @subsection CV52_Multi_VIN_Design 4.2 CV52 Multi-VIN Design
 * CV52 supports 4x native VIN controllers. Through MIPI virtual channel, it can be extended to 14x VIN controllers. CV52
 * can support various VIN interfaces including MIPI D/C-PHY and SLVS. MIPI interfaces can be up to 16 lanes. SLVS interface
 * can be up to 8 lanes.
 *
 * <table>
 * <tr>
 * <th><div style="width:120px"></div>VIN Slot Mode</div></th><th><div style="width:120px"></div>I2C Bus ID</th>
 * <th><div style="width:120px"></div>VIN Controller ID</div></th><th><div style="width:120px"></div>Type</th>
 * </tr>
 * <tr><td rowspan="7">SLVS + DPHY
 * <tr>			<td align="center">3/4</td><td align="center">8</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">9</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">10</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">11</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">12</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">13</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * <tr><td rowspan="5">DCPHY 0
 * <tr>			<td align="center">5</td><td align="center">0</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">1</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">2</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">3</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * <tr><td rowspan="5">DCPHY 1
 * <tr>			<td align="center">1</td><td align="center">4</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">5</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">6</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">7</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * </table>
 *
 * Currently, CV52 supports a 2~4 multiple-VIN design through SERDES with SLVS + DPHY VIN slot. The sensors must support a 4-lane interface
 * through either MIPI or SLVS. The following figure shows the sensor boards inserted into the SLVS + DPHY VIN slot on the CV52 Zircon board.
 * Compared with CV5, CV52 does not support SLVS-EC VIN interface.
 *
 * @image html single_sensor_plug_into_CV52_Zircon_Board.jpg "Figure 4-2. Single Sensor Boards Plug in CV52 Zircon Board."
 *
 * - - - -
 *
 * @subsection CV72_Multi_VIN_Design 4.3 CV72 Multi-VIN Design
 * CV72 supports 3x native VIN controllers. Through MIPI virtual channel, it can be extended to 10x VIN controllers. CV72
 * can support various VIN interfaces including MIPI D/C-PHY and SLVS. MIPI interfaces can be up to 16 lanes. SLVS interface
 * can be up to 8 lanes.
 *
 * <table>
 * <tr>
 * <th><div style="width:120px"></div>VIN Slot Mode</div></th><th><div style="width:120px"></div>I2C Bus ID</th>
 * <th><div style="width:120px"></div>VIN Controller ID</div></th><th><div style="width:120px"></div>Type</th>
 * </tr>
 * <tr><td rowspan="7">SLVS + DPHY
 * <tr>			<td align="center">0</td><td align="center">8</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">9</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">10</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">11</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">12</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">13</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * <tr><td rowspan="5">DCPHY 0
 * <tr>			<td align="center">0</td><td align="center">0</td><td align="center">Real</td></tr>
 * <tr>			<td align="center"></td><td align="center">1</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">2</td><td align="center">Virtual</td></tr>
 * <tr>			<td align="center"></td><td align="center">3</td><td align="center">Virtual</td></tr>
 * </td></tr>
 * </table>
 *
 * Currently, CV72 supports a 2~3 multiple-VIN design through SERDES with SLVS + DPHY VIN slot. The sensors must support a 4-lane interface
 * through either MIPI or SLVS. The following figure shows the sensor boards inserted into the SLVS + DPHY VIN slot on the CV72 Ga board.
 * Compared with CV5, CV72 does not support SLVS-EC VIN interface, and CV72 removes DCPHY 1.
 *
 * @image html single_sensor_plug_into_CV72_Ga_Board.jpg "Figure 4-3. Single Sensor Boards Plug in CV72 Ga Board."
 *
 * - - - -
 *
 */
