/*!
 * @file amba_doc.h
 * @brief This file defines the whole structure of ambarella sdk usage document.
 * @version 0.1
 * @date 2021-10-21
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
 * @mainpage notitle
 * <h1>AMBA Flexible Linux SDK Document</h1>
 * - - - -
 * <h2>Overview</h2>
 * The Ambarella Cooper family systems on chip (SoCs) are driven by a Linux 64-bit operating system
 * (OS) that runs on an Arm® Dual-Cortex® A76 processor. With digital signal processor (DSP)
 * firmware, drivers and middlewares, as well as vector processor (VP) firmware, drivers, and
 * libraries, the Ambarella Flexible Linux Software Development Kit (SDK) offers a powerful software
 * platform for internet protocol cameras (IPCams) and automotive application software.
 *
 * - - - -

 * <h2>DRIVER - Cavalry Driver Document Overview</h2>
 *
 * These web pages provides the application programming interface (APIs) for allocate memory, run DAGs, FEX and FMA on Cavalry. <br>
 * The outline of @ref page_drv_cavalry_doc is listed as follows:
 * - Section @ref cavalry_history 
 * - Section @ref cavalry_intro 
 * - Section @ref cavalry_usage 
 * - Section @ref cavalry_debug 
 * - Section @ref sec_cavalry_api 
 * - Section @ref cavalry_license 
 *
 * Detailed API information could be found in the section @ref cavalry-api.
 *
 * Structure and other macro information can be found in the section @ref cavalry-helper.
 * - - - -
 * <h2>DRIVER - CMA Driver Document Overview</h2>
 *
 * These web pages provide an introduction on how the contiguous
 * memory allocator (CMA) is applied to CV5x as a memory management
 * method for image audio video (IAV) / image digital signal processing
 * (DSP) partitions. Additionally, it provides detailed guidelines for
 * managing the IAV / DSP partitions using this method through the Ambarella
 * CV5x Flexible Linux SDK.<br>
 * The outline of @ref page_drv_cma_doc is listed as follows:
 * - Section @ref cma_driver_history 
 * - Section @ref cma_layout_intr 
 * - Section @ref cma_memory 
 * - Section @ref cma_driver 
 * - Section @ref cma_example 
 * - Section @ref cma_faq 
 * - Section @ref cma_license 
 *
 *
 * - - - -
 * <h2>DRIVER - IAV Driver Document Overview</h2>
 *
 * These web pages provides the APIs for the video input control unit and video output control unit,
 * image processing, H.265 / H.264 / Motion-JPEG compressor / decompressor (codec), and audio codec.  It includes control for
 * encoding parameters, single and multi-stream encoding, basic H.264 decoding functions, overlay
 * on streams, privacy mask insertion, digital pan / tilt / zoom, and lens distortion correction
 * functions.<br>
 * The outline of @ref page_drv_iav_doc is listed as follows:
 * - Section @ref iav_history 
 * - Section @ref iav_intro 
 * - Section @ref iav_key_feature 
 * - Section @ref iav_state_model 
 * - Section @ref iav_interrupts 
 * - Section @ref iav_encode_flow 
 * - Section @ref iav_decode 
 * - Section @ref iav_sysfs_info 
 * - Section @ref iav_proc_info 
 * - Section @ref dsp_proc_info 
 * - Section @ref iav_poll 
 * - Section @ref iav_example 
 * - Section @ref sec_iav_api 
 * - Section @ref iav_license 
 *
 * Detailed API information could be found in the section @ref iav-api.
 *
 * Structure and other macro information can be found in the section @ref iav-helper.
 * - - - -
 * <h2>DRIVER - Sensor Module Parameters</h2>
 *
 * This document provides introductions of sensor module parameters.<br>
 * The outline of @ref page_drv_sensor is listed as follows:
 * - Section @ref sensor_history 
 * - Section @ref sensor_parm 
 * - Section @ref sensor_parm_table 
 * - Section @ref brg_sensor_parm_table 
 * - Section @ref CV5x_sensor_tuning_table 
 * - Section @ref CV72_sensor_tuning_table 
 * - Section @ref CV3_sensor_tuning_table 
 * - Section @ref sensor_lic 
 *
 * - - - -
 * <h2>DRIVER - Sensor and SERDES Driver Installation</h2>
 *
 * This document provides introductions of sensor and serializers / deserializers (SERDES) driver installation.<br>
 * The outline of @ref page_sys_sensor_driver_installation is listed as follows:
 * - Section @ref Sensor_driver_installation_history 
 * - Section @ref sensor_driver_module_parameters 
 * - Section @ref serdes_driver_module_parameters 
 * - Section @ref driver_installation_guide 
 * - Section @ref cv5x_multi_vin_support 
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
