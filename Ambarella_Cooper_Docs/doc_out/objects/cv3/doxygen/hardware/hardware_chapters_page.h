/*!
 * @file doc_hw_modules.h
 * @brief
 * @version 1.0
 * @date 2022-08-19
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
 * @page hw_modules HW - Modules
 *
 * @section hw_video_input 1. Video Input
 * The following sections list the video input (VIN) features and characteristics of the Cooper family.
 *
 * @subsection hw_video_input_cv5 1.1 CV5 / CV52
 *
 * Four independent VINs, which can expand to fourteen VIN instances through the mobile industry processor interface (MIPI®) virtual channel (VC):
 *   - fourteen VIN instances
 *   - Four independent VINs: VIN0 / 4 / 8 / 11
 *   - Ten MIPI VC-only VINs, VIN1 / 2 / 3, VIN5 / 6 / 7, VIN9 / 10, and VIN12 / 13
 *
 * For the four independent VINs:
 *   - VIN0 connects to SLVS-EC (12 lanes) and MIPI DC-PHY1 (four lanes)
 *   - VIN4 connects to MIPI DC-PHY2 (four lanes)
 *   - VIN8 connects to MIPI D-PHY1 (eight lanes) and SLVS1 (eight lanes)
 *   - VIN11 connects to MIPI D-PHY2 (four lanes) and SLVS2 (four lanes)
 *
 * Possible combinations:
 *   - SLVS-EC + MIPI DC-PHY + 1*8 lane or 2*4 lane MIPI D-PHY
 *   - 2 * MIPI DC-PHY + 1*8 lane or 2*4 lane MIPI D-PHY
 *   - 2 * MIPI DC-PHY + 1*8 lane or 2 *4 lane SLVS
 *   - 2 * MIPI DC-PHY + 1*4 lane MIPI D-PHY + 1*4 lane SLVS
 *
 * For the other VINs:
 *   - VIN1 /VIN2 / VIN3 are used as a VC with VIN0
 *   - VIN5 / VIN6 / VIN7 are used as a VC with VIN4
 *   - VIN9 / VIN10 are used as a VC with VIN8
 *   - VIN12 / VIN13 are used as a VC with VIN11
 *
 * @subsection hw_video_input_cv72 1.2 CV72
 *
 * Three independent VINs, which can expand to ten VIN instances through the MIPI VC:
 *   - Ten VIN instances
 *   - Three independent VINs: VIN 0 / 8 / 11
 *   - Seven MIPI VC-only VINs: VIN 1 / 2 / 3, VIN 9 / 10, and VIN 12 / 13
 *
 * For the three independent VINs:
 *   - VIN0 connects to MIPI C-PHY (three lanes) or MIPI D-PHY1 (four lanes)
 *   - VIN8 connects to MIPI D-PHY2 (eight lanes) and SLVS1 (eight lanes)
 *   - VIN11 connects to MIPI D-PHY2 (four lanes) and SLVS2 (four lanes)
 *
 * Possible combinations:
 *   - 1 * MIPI DC-PHY + 1 * 8 lane or 2*4 lane MIPI D-PHY
 *   - 1 * MIPI DC-PHY + 1 * 8 lane or 2 *4 lane SLVS
 *   - 1 * MIPI DC-PHY + 1 * 4 lane MIPI D-PHY + 1*4 lane SLVS
 *
 * For the other VINs:
 *   - VIN1 / VIN2 / VIN3 are used as a VC with VIN0
 *   - VIN9 / VIN10 are used as a VC with VIN8
 *   - VIN12 / VIN13 are used as a VC with VIN11
 *
 * @subsection hw_video_input_cv3_hd 1.3 CV3 Hight Definition (HD)
 *
 * Twelve independent VINs, which can expand to fourty-eight VIN instances through the MIPI VC:
 *   - Fourty-eight VIN instances
 *   - Twelve independent VINs: VIN 0 / 4 / 8 / 12 / 16 / 20 / 24 / 28 / 32 / 36 / 40 / 44
 *   - Thirty-six MIPI VC-only VINs: VIN 1 / 2 / 3, VIN 5 / 6 / 7, VIN 9 / 10 / 11, VIN 13 / 14 / 15, VIN 17 / 18 / 19, VIN 21 / 22 / 23,
 * VIN 25 / 26 / 27, VIN 29 / 30 / 31, VIN 33 / 34 / 35, VIN 37 / 38 / 39, VIN 41 / 42 / 43, and VIN 45 / 46 / 47
 *
 * For the twelve independent VINs, they support MIPI D-PHY®, and each supports up to three MIPI VC-only VINs.
 *
 * For the other VINs:
 *   - VIN1 / VIN2 / VIN3 are used as a VC with VIN0
 *   - VIN5 / VIN6 / VIN7 are used as a VC with VIN4
 *   - VIN9 / VIN10 / VIN11 are used as a VC with VIN8
 *   - VIN13 / VIN14 / VIN15 are used as a VC with VIN12
 *   - VIN17 / VIN18 / VIN19 are used as a VC with VIN16
 *   - VIN21 / VIN22 / VIN23 are used as a VC with VIN20
 *   - VIN25 / VIN26 / VIN27 are used as a VC with VIN24
 *   - VIN29 / VIN30 / VIN31 are used as a VC with VIN28
 *   - VIN33 / VIN34 / VIN35 are used as a VC with VIN32
 *   - VIN37 / VIN38 / VIN39 are used as a VC with VIN36
 *   - VIN41 / VIN42 / VIN43 are used as a VC with VIN40
 *   - VIN45 / VIN46 / VIN47 are used as a VC with VIN44
 *
 * - - - -
 *
 * @section hw_video_output 2. Video Output
 *
 * Video output (VOUT) includes the following features:
 *  - Three VOUT interfaces
 *  - High definition multimedia interface (HDMI®) v2.0 output, including an on-chip PHY with consumer electronic control (CEC) support
 *  - HDMI output channel, up to 8KP30
 *  - 2x MIPI DSI® / CSI-2® output
 *  - Video digital-to-analog converter (DAC) for 480i / 576i composite PAL / NTSC output
 *  - Full-screen frame buffer on the analog / digital VOUT
 *
 * - - - -
 *
 * @section hw_idsp_pipeline 3 IDSP Pipeline
 * The image digital signal processing (IDSP) pipeline includes the following features:
 *  - Adjustable 3A: auto exposure (AE), auto white balance (AWB), and auto focus (AF) control
 *  - 3D noise reduction with motion-compensated temporal filtering (MCTF)
 *  - Slow shutter function for low-light
 *  - IQ adjustment, including color saturation / sharpness / brightness
 *  - Local exposure adjustment, contrast enhancement, tone mapping, and tone-curve adjustment
 *  - RGB and YUV statistics, histogram, and AF focus value generation
 *  - Customized support for 3A (AE / AWB / AF) algorithms
 *  - RAW picture capture for the sensor calibration
 *  - White balance (WB) / bad pixel / lens shading calibration
 *  - Flexible application programming interfaces (APIs) and image tuning tools
 *  - 360° fisheye lens dewarp and lens optical / geometric distortion correction
 *  - Lens geometric distortion correction (dewarping)
 *  - Vignette compensation
 *  - Chromatic aberration correction
 *  - Image signal processor (ISP) VC support
 *
 * - - - -
 *
 * @section hw_video_codec 4. Video Codec
 * The following sections list the video coder / decoder (codec) features and characteristics of the Cooper family.
 *
 * @subsection hw_video_codec_cv5 4.1 CV5
 *
 *  - Simultaneous H.264 (advanced video coding (AVC)), H.265 (high-efficiency video coding (HEVC)), and MJPEG codec
 *  - Full frame rate codec up to 4Kp160 with multiple sub-streams
 *  - Encoding up to twenty streams
 *  - Codec resolution that ranges from common intermediate format (CIF) to 32M pixels per frame
 *  - Up to six resolutions at the full field of view (FoV)
 *  - Flexibility to start / stop streams independently
 *  - Ability to add a graphic or text (overlay) on the streams
 *  - Digital pan / tilt / zoom (DPTZ)
 *  - Privacy mask with PTZ
 *  - Flip and 90° clockwise rotation without the sensor support (corridor view / portrait mode)
 *  - Video analysis for YUV / motion estimation buffer
 *  - Encoding duration that can run for H.264 (AVC), H.265 (HEVC), and MJPEG
 *  - H.265 (HEVC)
 *     - Main profile (level 6.2)
 *     - Constant bit rate (CBR) / variable bit rate (VBR) / constant quantization parameter (CQP) rate control with maximum bit rate control
 *     - Up to 160 Mbps bitrate for single stream
 *     - I, IP, and IBP modes
 *     - Up to two forward reference frames
 *     - Up to four layers of scalable video coding (SVC-T)
 *     - On the fly changes to the bit rate, the frame rate, group of pictures (GOP) length, instantaneous decoder refresh (IDR) interval, and the QP region of interest (ROI)
 *     - CU-level adaptive quantization
 *     - IDR insertion on request
 *     - Dynamic region of interest (ROI) encoding with an unrestricted numbers of areas
 *     - Advanced GOP structures with fast seek and bi-directional prediction (B-frames)
 *  - H.264 (AVC)
 *     - Main / high profile (level 6.2)
 *     - Context-adaptive binary arithmetic coding (CABAC) entropy coding supported by the digital signal processor (DSP) hardware module
 *     - CBR / VBR / CQP rate control with maximum bit-rate control
 *     - Up to 160 Mbps bitrate for single stream
 *     - I, IP, and IBP modes
 *     - Up to two forward reference frames
 *     - Up to four layers of SVC-T
 *     - High profile with B-frames and hierarchical GOP
 *     - On the fly changes to bit rate, frame rate, GOP length, IDR interval, and QP ROI
 *     - MB-level adaptive quantization
 *     - IDR insertion on request
 *     - Dynamic ROI encoding with an unrestricted numbers of areas
 *     - Advanced GOP structures with fast seek and bi-directional prediction (B-frames)
 *  - MJPEG
 *     - Independent quality control
 *
 * @subsection hw_video_codec_cv52 4.2 CV52
 *
 *  - Simultaneous H.264 (AVC), H.265 (HEVC), and MJPEG codec
 *  - Full frame rate codec up to 4KP90 with multiple sub-streams
 *  - Encoding up to twenty streams
 *  - Codec resolution ranging from CIF to 32M pixels per frame
 *  - Up to six resolutions at full FoV
 *  - Flexibility to start / stop streams independently
 *  - Ability to add a graphic or text (overlay) on the streams
 *  - DPTZ
 *  - Privacy mask with PTZ
 *  - Flip and 90° clockwise rotation without the sensor support (corridor view / portrait mode)
 *  - Video analysis for the YUV / motion estimation buffer
 *  - Encoding duration that can run for H.264 (AVC), H.265 (HEVC), and MJPEG
 *  - H.265 (HEVC)
 *     - Main profile (level 6.2)
 *     - CBR / VBR / CQP rate control with maximum bit rate control
 *     - Up to 160 Mbps bitrate for single stream
 *     - I, IP, and IBP modes
 *     - Up to two forward reference frames
 *     - Up to four layers of SVC-T
 *     - On the fly changes to bit rate, frame rate, GOP length, IDR interval, and QP ROI
 *     - CU-level adaptive quantization
 *     - IDR insertion on request
 *     - Dynamic ROI encoding with an unrestricted numbers of areas
 *     - Advanced GOP structures with fast seek and bi-directional prediction (B-frames)
 *  - H.264 (AVC)
 *     - Main / high profile (level 6.2)
 *     - CABAC entropy coding supported by the DSP hardware module
 *     - CBR / VBR / CQP rate control with maximum bit-rate control
 *     - Up to 160 Mbps bitrate for single stream
 *     - I, IP, and IBP modes
 *     - Up to two forward reference frames
 *     - Up to four layers of SVC-T
 *     - High profile with B-frames and hierarchical GOP
 *     - On the fly changes to bit rate, frame rate, GOP length, IDR interval, and QP ROI
 *     - MB-level adaptive quantization
 *     - IDR insertion on request
 *     - Dynamic ROI encoding with an unrestricted numbers of areas
 *     - Advanced GOP structures with Fast Seek and bi-directional prediction (B-frames)
 *  - MJPEG
 *     - Independent quality control
 *
 * @subsection hw_video_codec_cv72 4.3 CV72
 *
 *  - Simultaneous H.264 (AVC), H.265 (HEVC), and MJPEG codec
 *  - Full frame rate codec up to 4KP90 with multiple sub-streams
 *  - Encoding up to twenty streams
 *  - Codec resolution ranging from CIF to 32M pixels per frame
 *  - Up to six resolutions at full FoV
 *  - Flexibility to start / stop streams independently
 *  - Ability to add a graphic or text (overlay) on the streams
 *  - DPTZ
 *  - Privacy mask with PTZ
 *  - Flip and 90° clockwise rotation without the sensor support (corridor view / portrait mode)
 *  - Video analysis for the YUV / motion estimation buffer
 *  - Encoding duration that can run for H.264 (AVC), H.265 (HEVC), and MJPEG
 *  - H.265 (HEVC)
 *     - Main profile (Level 6.2)
 *     - CBR / VBR / CQP rate control with maximum bit rate control
 *     - Up to 160 Mbps bitrate for single stream
 *     - I, IP, and IBP modes
 *     - Up to two forward reference frames
 *     - Up to four layers of SVC-T
 *     - On the fly changes to bit rate, frame rate, GOP length, IDR interval, and QP ROI
 *     - CU-level adaptive quantization
 *     - IDR insertion on request
 *     - Dynamic ROI encoding with an unrestricted numbers of areas
 *     - Advanced GOP structures with fast seek and bi-directional prediction (B-frames)
 *  - H.264 (AVC)
 *     - Main / high profile (Level 6.2)
 *     - CABAC entropy coding supported by the DSP hardware module
 *     - CBR / VBR / CQP rate control with maximum bit-rate control
 *     - Up to 160 Mbps bitrate for single stream
 *     - I, IP, and IBP modes
 *     - Up to two forward reference frames
 *     - Up to four layers of SVC-T
 *     - High profile with B-frames and hierarchical GOP
 *     - On the fly changes to bit rate, frame rate, GOP length, IDR interval, and QP ROI
 *     - MB-level adaptive quantization
 *     - IDR insertion on request
 *     - Dynamic ROI encoding with an unrestricted numbers of areas
 *     - Advanced GOP structures with fast seek and bi-directional prediction (B-frames)
 *  - MJPEG
 *     - Independent quality control
 *
 * @subsection hw_video_codec_cv3_hd 4.4 CV3 HD
 *
 *  - Simultaneous H.264 (AVC), H.265 (HEVC), and MJPEG codec
 *  - Full frame rate codec up to 4KP180 with multiple sub-streams
 *  - Encoding up to twenty streams
 *  - Codec resolution ranging from CIF to 32M pixels per frame
 *  - Up to eight resolutions at full FoV
 *  - Flexibility to start / stop streams independently
 *  - Ability to add a graphic or text (overlay) on the streams
 *  - DPTZ
 *  - Privacy mask with PTZ
 *  - Flip and 90° clockwise rotation without the sensor support (corridor view / portrait mode)
 *  - Video analysis for the YUV / motion estimation buffer
 *  - Encoding duration that can run for H.264 (AVC), H.265 (HEVC), and MJPEG
 *  - H.265 (HEVC)
 *     - Main profile (Level 6.2)
 *     - CBR / VBR / CQP rate control with maximum bit rate control
 *     - Up to 160 Mbps bitrate for single stream
 *     - I, IP, and IBP modes
 *     - Up to two forward reference frames
 *     - Up to four layers of SVC-T
 *     - On the fly changes to bit rate, frame rate, GOP length, IDR interval, and QP ROI
 *     - CU-level adaptive quantization
 *     - IDR insertion on request
 *     - Dynamic ROI encoding with an unrestricted numbers of areas
 *     - Advanced GOP structures with fast seek and bi-directional prediction (B-frames)
 *  - H.264 (AVC)
 *     - Main / high profile (Level 6.2)
 *     - CABAC entropy coding supported by the DSP hardware module
 *     - CBR / VBR / CQP rate control with maximum bit-rate control
 *     - Up to 160 Mbps bitrate for single stream
 *     - I, IP, and IBP modes
 *     - Up to two forward reference frames
 *     - Up to four layers of SVC-T
 *     - High profile with B-frames and hierarchical GOP
 *     - On the fly changes to bit rate, frame rate, GOP length, IDR interval, and QP ROI
 *     - MB-level adaptive quantization
 *     - IDR insertion on request
 *     - Dynamic ROI encoding with an unrestricted numbers of areas
 *     - Advanced GOP structures with fast seek and bi-directional prediction (B-frames)
 *  - MJPEG
 *     - Independent quality control
 *
 * - - - -
 *
 * @section hw_audio 5. Audio
 * Audio includes the following features:
 *  - Audio connection to the system host
 *  - Support for encoding / decoding
 *     - G.711 / G.726 / ADPCM encode / decode
 *     - Advanced audio coding (AAC) encode and decode
 *     - AC3 encode and decode
 *     - MP3 decode
 *
 * - - - -
 *
 * @section hw_system 6. System
 *
 * The following sections list the system on chip (SoC) system features of the Cooper family.
 *
 * @subsection hw_system_cv5 6.1 CV5
 *
 *  - Dual-core Arm Cortex-A76 processor
 *  - 32-GB (256-Gb) maximum dynamic random access memory (DRAM) capacity for LPDDR5
 *  - 16-GB (128-Gb) maximum DRAM capacity for LPDDR4
 *  - Up to 2.8-GHz DRAM clock rate for LPDDR5
 *  - Up to 1.8-GHz DRAM clock rate for LPDDR4
 *  - 64-KB data / 64-KB instruction L1 cache
 *  - 256-KB L2 cache
 *  - 1-MB L3 cache
 *  - 64-bit data bus
 *  - NEON SIMD engine (per core)
 *  - Floating point unit (FPU)
 *  - Vector floating point version 4 (VFPv4) with hardware floating-point processing
 *  - Up to 1.6-GHz Arm Cortex-A76 with NEON and FPU
 *  - DC power 12-V supply or power over Ethernet (PoE)
 *  - Time synchronization with real-time clock (RTC) or network time protocol (NTP)
 *  - RTC
 *  - Watchdog timer (WDT)
 *  - Built-in power controller (PWC) for power-up or power-down sequencing
 *  - Multiple boot options (NAND flash, SPI NOR, USB, and eMMC card)
 *  - Embedded Linux OS
 *
 * - - - -
 *
 * @subsection hw_system_cv52 6.2 CV52
 *
 *  - Dual-core Arm Cortex-A76 processor
 *  - 16-GB (128-Gb) maximum DRAM capacity for LPDDR5
 *  - 8-GB (64-Gb) maximum DRAM capacity for LPDDR4
 *  - Up to 2.6-GHz DRAM clock rate for LPDDR5
 *  - Up to 1.8-GHz DRAM clock rate for LPDDR4
 *  - 64-KB data / 64-KB instruction L1 cache
 *  - 256-KB L2 cache
 *  - 1-MB L3 cache
 *  - 32-bit data bus
 *  - NEON SIMD engine (per core)
 *  - FPU
 *  - Vector floating point version 4 (VFPv4) with hardware floating-point processing
 *  - Up to 1.6-GHz Arm Cortex-A76 with NEON and FPU
 *  - DC power 12-V supply or PoE
 *  - Time synchronization with RTC or NTP
 *  - RTC
 *  - WDT
 *  - Built-in PWC for power-up or power-down sequencing
 *  - Multiple boot options (NAND flash, SPI NOR, USB, and eMMC card)
 *  - Embedded Linux OS
 *
 * - - - -
 *
 * @subsection hw_system_cv72 6.3 CV72
 *
 *  - Dual-core Arm Cortex-A76 processor
 *  - Single-core Arm Cortex-M3
 *  - 16-GB (128-Gb) maximum DRAM capacity for LPDDR5
 *  - 8-GB (64-Gb) maximum DRAM capacity for LPDDR4
 *  - Up to 3.2-GHz DRAM clock rate for LPDDR5
 *  - Up to 2.1-GHz DRAM clock rate for LPDDR4
 *  - 64-KB data / 64-KB instruction L1 cache
 *  - 256-KB L2 cache
 *  - 1-MB L3 cache
 *  - 32-bit data bus
 *  - NEON SIMD engine (per core)
 *  - FPU
 *  - Neural vector processor (NVP) with hardware floating-point processing
 *  - Up to 1.6-GHz Arm Cortex-A76 with NEON and FPU
 *  - DC power 12-V supply or PoE
 *  - Time synchronization with RTC or NTP
 *  - RTC
 *  - WDT
 *  - Built-in PWC for power-up or power-down sequencing
 *  - Multiple boot options (NAND flash, SPI NOR, USB, and eMMC card)
 *  - Embedded Linux OS
 *
 * - - - -
 *
 * @subsection hw_system_cv3_hd 6.4 CV3 HD
 *
 *  - Sixteen-core Arm Cortex-A78AE processors, with 4 clusters
 *  - Single-core Arm Cortex-M3
 *  - 128-GB (1024-Gb) maximum DRAM capacity for LPDDR5
 *  - Up to 2.8-GHz DRAM clock rate for LPDDR5
 *  - 64-KB data / 64-KB instruction L1 cache
 *  - 256-KB L2 cache
 *  - 2-MB L3 cache
 *  - 256-bit data bus
 *  - NEON SIMD engine (per core)
 *  - FPU
 *  - NVP with hardware floating-point processing
 *  - General vector processor (GVP) with hardware floating-point processing
 *  - Up to 1.6-GHz Arm Cortex-A78AE with NEON and FPU
 *  - DC power 12-V supply or PoE
 *  - Time synchronization with RTC or NTP
 *  - RTC
 *  - WDT
 *  - Built-in PWC for power-up or power-down sequencing
 *  - Multiple boot options (NAND flash, SPI NOR, USB, and eMMC card)
 *  - Embedded Linux OS
 *
 * - - - -
 *
 * @section hw_interfaces 7. Interfaces
 * The following sections list the interface features and characteristics of the Cooper family.
 *
 * @subsection hw_interfaces_cv5 7.1 CV5 / CV52 / CV72
 *  - Ethernet controller
 *     - Two ENET ports with 10- / 100- / 1000-Mbps data transfer rates with an IEEE 802.3-compliant RGMII interface
 *     - IEEE 802.3 compliant with full and half-duplex (IEEE 802.3x flow control) and jumbo frames
 *     - IEEE 802.1Q VLAN tag detection
 *     - Audio video bridging (AVB) endpoint implementation for IEEE 1588 / 802.1AS with a hardware timestamp
 *     - Checksum off-load for received internet protocol (IP) and transmission control protocol (TCP) / user datagram protocol (UDP) packets
 *     - FIFO (4 KB / 4 KB) and DRAM support
 *     - Dedicated pins for the RGMII and RMII interfaces
 *  - Two USB interfaces
 *     - One USB 3.2 Gen 2 interface configurable to perform in host or device mode.  Backward compatible with USB 2.0 / 1.1
 *     - One USB 2.0 high-speed, device-only interface that supports USB power-on boot mode
 *  - NAND flash controller
 *     - Up to 128 Gbit device, 2 KB, and 4 KB page sizes
 *     - 4- and 8-bit single-level cell (SLC) with error correction code (ECC) hardware and read-confirm support
 *     - BCH error correction and increased spare area availability
 *  - Three SD controllers (SD0, SDIO0, SDIO1)
 *     - SD0:
 *         - SDIO v3.0, SD, SDHC, SDXC, MMC, and eMMC operations with boot support and UHS-I speed support
 *         - 1-bit, 4-bit, and 8-bit SD modes
 *     - SDIO0:
 *         - SDIO v3.0, SD, SDHC, SDXC, MMC, and eMMC operations with UHS-I speed support
 *         - 1-bit and 4-bit SD modes
 *     - SDIO1:
 *         - SDIO v3.0, SD, SDHC, SDXC, MMC, and eMMC operations with boot support and UHS-I speed support
 *         - 1-bit and 4-bit SD modes
 *         - Optional 8-bit SDK mode if the SD0 is in a 1-bit or 4-bit SDK mode
 *     - 32 GB maximum capacity for the SDHC SD card
 *     - 2 TB maximum capacity for the SDXC SD card
 *     - CRC7 for command, and CRC16 for data integrity
 *  - SSI / SPI interface
 *     - Six serial synchronous interface (SSI) / serial peripheral interface (SPI) masters
 *     - Dedicated SSI / SPI slave port to connect to an external system master
 *  - Universal asynchronous receiver / transmitter (UART) (X5)
 *     - Four AHB-bus UART interfaces, one APB-bus UART interface
 *     - DMA and hardware flow control support in the four AHB interfaces
 *     - Maximum baud rate of 115200
 *  - Pulse-width modulator (PWM) (X12)
 *     - Three sets of PWM controllers; each controller supports up to four PWMs
 *
 * - - - -
 *
  * @subsection hw_interfaces_cv3_hd 7.2 CV3 HD
 *  - Ethernet controller
 *     - Four ENET ports with 10- / 100- / 1000-Mbps data transfer rates with an IEEE 802.3-compliant RGMII interface
 *     - IEEE 802.3 compliant with full and half-duplex (IEEE 802.3x flow control) and jumbo frames
 *     - IEEE 802.1Q VLAN tag detection
 *     - Audio video bridging (AVB) endpoint implementation for IEEE 1588 / 802.1AS with a hardware timestamp
 *     - Checksum off-load for IP and TCP / UDP packets
 *     - FIFO (16KB for TX and 8KB for RX) and DRAM support
 *     - Dedicated pins for the RGMII and RMII interfaces
 *  - Two USB interfaces
 *     - One USB 3.2 Gen 2 interface configurable to perform in host or device mode.  Backward compatible with USB 2.0 / 1.1
 *     - One USB 2.0 high-speed, device-only interface that supports USB power-on boot mode
 *  - NAND flash controller
 *     - Up to 128 Gbit device, 2 KB, and 4 KB page sizes
 *     - 4- and 8-bit SLC with ECC hardware and read-confirm support
 *     - BCH error correction and increased spare area availability
 *  - Three SD controllers (SD0, SDIO0, SDIO1)
 *     - SD0:
 *         - SDIO v3.0, SD, SDHC, SDXC, MMC, and eMMC operations with boot support and UHS-I speed support
 *         - 1-bit, 4-bit, and 8-bit SD modes
 *     - SDIO0:
 *         - SDIO v3.0, SD, SDHC, SDXC, MMC, and eMMC operations with UHS-I speed support
 *         - 1-bit and 4-bit SD modes
 *     - SDIO1:
 *         - SDIO v3.0, SD, SDHC, SDXC, MMC, and eMMC operations with boot support and UHS-I speed support
 *         - 1-bit and 4-bit SD modes
 *     - 32 GB maximum capacity for the SDHC SD card
 *     - 1 TB maximum capacity for the SDXC SD card
 *     - CRC7 for command, and CRC16 for data integrity
 *  - SSI / SPI interface
 *     - Six SSI / SPI masters
 *     - Dedicated SSI / SPI slave port muxed with other GPIOs to connect to an external system master
 *  - UART (X5)
 *     - Four AHB-bus UART interfaces, one APB-bus UART interface
 *     - DMA and hardware flow control support in the four AHB interfaces
 *  - PWM (X12)
 *     - Three sets of PWM controllers; each controller supports up to four PWMs
 *
 * - - - -
 *
 */
/*!
 * @file doc_hw_cv5_timn.h
 * @brief
 * @version 1.0
 * @date 2022-08-05
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
 * @page page_cv5_timn Board - CV5 Titanium
 *
 * This chapter provides details on setting up the hardware for the evaluation kit (EVK) and is
 * divided into the following sections:<br>
 *
 *   - Section @ref cv5_timn_evk_package
 *   - Section @ref cv5_timn_overview
 *   - Section @ref cv5_timn_setting_up
 *   - Section @ref cv5_timn_system_io_hardware_control
 *   - Section @ref cv5_timn_doc_license
 * - - - -
 *
 * @section cv5_timn_evk_package 1 EVK Package
 *
 * The Ambarella Cooper Linux EVK contains the following hardware and accessories. If any of the
 * following components are missing from the EVK package, contact the Ambarella support team.<br>
 *
 * <table>
 * <tr><td align="center"> <b> EVK Board: </b>
 *     <td> The board that comes furnished with the Ambarella CV5 system on chip (SoC)
 * <tr><td align="center"> <b> Sensor board: </b>
 *     <td> The sensor board that is connected to the EVK board as the video input (VIN)
 * <tr><td align="center"> <b> Cables: </b>
 *     <td> Serial cable and USB cable
 * <tr><td align="center"> <b> EVK firmware: </b>
 *     <td> The firmware in the folder Binary/ that is upgraded to the EVK board
 * <tr><td align="center"> <b> Install program: </b>
 *     <td> The tools in the folder Tools/ that are used for evaluation, including <br>
 *          AmbaUSB, PortServer, USBServer, and the VLC player
 * <tr><td align="center"> <b> Getting started guide: </b>
 *     <td> The document providing information on how to use the EVK
 * </table>
 *
 * The pre-loaded demonstration application is provided through the following:<br>
 *
 * <table>
 * <tr><td align="center" width="165px"> <b> Unit test program: </b>
 *     <td> The unit test applications used to evaluate features using commands from<br>
 *          the command line interface
 * </table>
 * - - - -
 *
 * @section cv5_timn_overview 2 Overview of the EVK Board
 *
 * The figure below provides an overview of the major components and input / output (I/O)
 * connectors of the CV5 EVK board.<br>
 *
 * @image html cv5_timn_evk_board.png "Figure 2-1. CV5 Timn EVK Board."
 *
 * The major components and I/O connectors identified in the figure above are as follows:<br>
 *
 * 1. Universal asynchronous receiver / transmitter (UART1) DB9 with flow control
 * 2. USB to serial debug UART + firmware download port
 * 3. Internal power on / off
 * 4. Reset
 * 5. External power on / off
 * 6. Microcontroller unit (MCU) reset
 * 7. Audio line-out
 * 8. Analog microphone (MIC)
 * 9. Digital MIC
 * 10. Joint test action group (JTAG)
 * 11. Dual in-line package (DIP) switches
 * 12. VIN port1
 * 13. VIN port2
 * 14. VIN port3
 * 15. VIN port3
 * 16. Mobile industry processor interface® (MIPI) digital serial interface (DSI) video output (VOUT)
 * 17. USB 3.0 host
 * 18. USB Type-C
 * 19. Micro USB3 . 0 device
 * 20. Composite video broadcast signal (CVBS) VOUT
 * 21. Infrared (IR)-receiver
 * 22. Peripheral component interconnect express (PCIe) X4 port
 * 23. Ethernet
 * 24. Ethernet
 * 25. 12-V DC power
 * 26. High definition multimedia interface (HDMI) VOUT
 * - - - -
 *
 * @section cv5_timn_setting_up 3 Setting up the EVK Board
 *
 * Use the following steps to set up the EVK hardware for the first time.<br>
 *
 *   - Using a grounding strap or another verified device to protect the board from static
 *     charges and connect the communication cables to the board before connecting any equipment
 *     to the power supply.<br>
 *
 *   - Ensure that the parallel sensors used on the CV5 boards are compatible with the adapter,
 *     then carefully insert the sensor board to the slot of the primary VIN, which is component
 *     1 on the EVK board (see the following figure). Ensure that the sensor board is secure
 *     before proceeding.<br>
 *
 * @image html cv5_timn_sensor_board_inserted.png "Figure 3-1. Sensor Board Inserted into the CV5 Timn Board."
 *
 *   - Use an Ethernet cable to connect the Ethernet port on the EVK board to the network
 *     port on the host PC.<br>
 *
 *   - For high-definition (HD) preview, connect a video display with an HDMI input to the
 *     HDMI connector on the EVK board.<br>
 *
 * @image html cv5_timn_connected_hdmi_ethernet_usb_cable.png "Figure 3-2. CV5 Timn Board with the HDMI / Ethernet / USB Cable Connected."
 *
 *   - For the UART console window, the Timn EVK board is equipped with a USB serial bridge.
 *     Connect the EVK board to the host PC using a USB Mini A cable.<br>
 *
 *   - To ensure protection from electro-static discharge (ESD), first connect the power cable
 *     to the EVK power jack on the board, and then connect the cable to the power supply.<br>
 * - - - -
 *
 * @section cv5_timn_system_io_hardware_control 4 CV5 EVK System I/O and Hardware Control
 *
 * @subsection cv5_timn_connectors 4.1 Connectors
 *
 * The following figures show all main I/O connectors on the top and bottom sides (respectively)
 * of the CV5 EVK base board Rev3.0.<br>
 *
 * @image html cv5_timn_major_io_connectors_on_the_top_side.png "Figure 4-1. Major I/O Connectors on the Top Side of the CV5 EVK Base Board."
 * @image html cv5_timn_major_io_connectors_on_the_bottom_side.png "Figure 4-2. Major I/O Connectors on the Bottom Side of the CV5 EVK Base Board."
 *
 * Refer to the table below for a list of the main I/O connectors shown in the figures above.<br>
 *
 * <table>
 * <caption id="main_board_connectors">Table 4-1. Main Board Connectors.</caption>
 * <tr><th> Item <th> Designator <th> Functions <th> Notes
 * <tr><td align="center"> 1
 *     <td align="center"> J63
 *     <td> UART1
 *     <td> DB9 connector with hardware flow control
 * <tr><td align="center"> 2
 *     <td align="center"> SW19
 *     <td> Key button
 *     <td> Key button for general purpose input / output (GPIO) debug
 * <tr><td align="center"> 3
 *     <td align="center"> J105
 *     <td> Power measurement
 *     <td> 15x2, 1.25-mm connector for power measurement
 * <tr><td align="center"> 4
 *     <td align="center"> J106
 *     <td> Power measurement
 *     <td> 10x2, 1.25-mm connector for power measurement
 * <tr><td align="center"> 5
 *     <td align="center"> SW1~SW5
 *     <td> PINMUX switch
 *     <td> 2-SPST / 4-SPST switches for PINMUX selection
 * <tr><td align="center"> 6
 *     <td align="center"> J46
 *     <td> HDMI transmit (TX)
 *     <td> Vertical HDMI receptacle
 * <tr><td align="center"> 7
 *     <td align="center"> J55
 *     <td> Audio HP out
 *     <td> 3.5-mm audio jack
 * <tr><td align="center"> 8
 *     <td align="center"> J47
 *     <td> Composite video broadcasting signal (CVBS) output
 *     <td> Mono RCA jack
 * <tr><td align="center"> 9
 *     <td align="center"> U91
 *     <td> IR input
 *     <td> IR receiver
 * <tr><td align="center"> 10
 *     <td align="center"> J76
 *     <td> Controller area network (CAN) bus
 *     <td> 2x2, 2.54-mm connector for the CAN bus
 * <tr><td align="center"> 11
 *     <td align="center"> J37/J36
 *     <td> PCIe x4
 *     <td> Standard PCIe x4 card edge connectors
 * <tr><td align="center"> 12
 *     <td align="center"> J69
 *     <td> JTAG connector
 *     <td> 10x2, 2.54-mm connector for the JTAG
 * <tr><td align="center"> 13
 *     <td align="center"> J50
 *     <td> Ethernet
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * <tr><td align="center"> 14
 *     <td align="center"> SW6~SW9
 *     <td> Power-on configuration (POC) switch
 *     <td> 2-SPST / 4-SPST / 8-SPST switches for POC setting
 * <tr><td align="center"> 15
 *     <td align="center"> BAT2
 *     <td> Real-time clock (RTC) battery holder
 *     <td> 2032 battery holder for the RTC
 * <tr><td align="center"> 16
 *     <td align="center"> J72
 *     <td> MCU serial wire debug (SWD) connector
 *     <td> 5x2, 2.54-mm connector for the MCU debug tool
 * <tr><td align="center"> 17
 *     <td align="center"> J75
 *     <td> MCU reset button
 *     <td> Button to reset the MCU
 * <tr><td align="center"> 18
 *     <td align="center"> SW13
 *     <td> Reset button
 *     <td> Button to make the system warm boot
 * <tr><td align="center"> 19
 *     <td align="center"> SW20
 *     <td> MCU power-on button
 *     <td> Button to indicate to the MCU to power on the system
 * <tr><td align="center"> 20
 *     <td align="center"> SW23
 *     <td> Power ON / OFF switch button
 *     <td> Button to make the system switch between the power on and power<br>
 *          off states when the external power sequencer is used
 * <tr><td align="center"> 21
 *     <td align="center"> J78
 *     <td> Power jack
 *     <td> 12-V system power adapter input, 2.5 mm
 * <tr><td align="center"> 22
 *     <td align="center"> J51
 *     <td> Ethernet1
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * <tr><td align="center"> 23
 *     <td align="center"> SW14~SW18
 *     <td> ADC1 key buttons
 *     <td> Key buttons in ADC1 to simulate menu / direction buttons
 * <tr><td align="center"> 24
 *     <td align="center"> J25
 *     <td> USB 2.0 device / serial debug port
 *     <td> Micro-B USB receptacle
 * <tr><td align="center"> 25
 *     <td align="center"> J29
 *     <td> USB 3.1 device
 *     <td> Micro-B USB 3.0 receptacle
 * <tr><td align="center"> 26
 *     <td align="center"> J31
 *     <td> USB 3.1 host
 *     <td> Type-A USB 3.0 receptacle
 * <tr><td align="center"> 27
 *     <td align="center"> J32
 *     <td> USB 3.1 hub host
 *     <td> Type-C USB 3.0 receptacle
 * <tr><td align="center"> 28
 *     <td align="center"> J33 / J34 / J35
 *     <td> USB 3.1 hub host
 *     <td> Type-A USB 3.0 receptacle
 * <tr><td align="center"> 29
 *     <td align="center"> J1 / J2
 *     <td> Core board connector
 *     <td> 120- / 180-pin high-speed ground plane sockets
 * <tr><td align="center"> 30
 *     <td align="center"> J48 / J49
 *     <td> VOUT MIPI DSI A / B
 *     <td> 40-pin, 0.5-mm FPC connector for VOUT MIPI DSI
 * <tr><td align="center"> 31
 *     <td align="center"> J43 / J44
 *     <td> VIN DCPHY
 *     <td> 41-pin, 0.5-mm connector for VIN DCPHY
 * <tr><td align="center"> 32
 *     <td align="center"> J42
 *     <td> VIN SLVS-EC
 *     <td> 51-pin, 0.5-mm connector for VIN SLVS-EC
 * <tr><td align="center"> 33
 *     <td align="center"> J39
 *     <td> VIN SLVS+DPHY
 *     <td> 164-pin PCIe connector for VIN SLVS+DPHY
 * <tr><td align="center"> 34
 *     <td align="center"> J38
 *     <td> SSD hard drive
 *     <td> Non-volatile memory express (NVMe) M2 connector
 * <tr><td align="center"> 35
 *     <td align="center"> J13
 *     <td> SDIO0
 *     <td> SD socket for SDIO0 I/F
 * <tr><td align="center"> 36
 *     <td align="center"> J19
 *     <td> SDIO1
 *     <td> Micro-SD socket for SDIO1 I/F
 * <tr><td align="center"> 37
 *     <td align="center"> BAT1
 *     <td> Lithium battery
 *     <td> 1.5-V lithium battery for RTC
 * <tr><td align="center"> 38
 *     <td align="center"> SW1
 *     <td> IMU
 *     <td> IMU in data ready interrupt mode
 * </table>
 *
 * @subsection cv5_timn_system_io_configurations 4.2 System I/O Configurations
 *
 * The CV5 EVK base board supplies abundant I/O interfaces for a variety of applications.
 * Ensure that the system I/O interfaces are properly configured with the on-board hardware
 * jumpers and switches.<br>
 *
 * The figure below provides the locations of the jumpers and switches listed in this chapter.<br>
 *
 * @image html cv5_timn_major_jumpers_for_system_io_on_the_top_side.png "Figure 4-3. Major Jumpers for the System I/O Configurations on the Top Side of the CV5 EVK Base Board."
 * @image html cv5_timn_major_jumpers_for_system_io_on_the_bottom_side.png "Figure 4-4. Major Jumpers for the System I/O Configurations on the Bottom Side of the CV5 EVK Base Board."
 * @image html cv5_timn_major_jumpers_for_system_io_top_side_core_board.png "Figure 4-5. Major Jumpers for the System I/O Configurations on the Top Side of the CV5 EVK Core Board."
 *
 * @subsubsection cv5_timn_system_io_uart1 4.2.1 UART1
 *
 * UART1 is available in J63, which is the DB9 connector for the EIA / TIA 232 serial interface.
 * UART1 supports hardware flow control and direct memory access (DMA).<br>
 *
 *   - Assemble the jumpers on J60 / J62 / J66 / J67
 *
 * @image html cv5_timn_jumpers_and_switches_for_uart1.png "Figure 4-6. Jumpers and Switches for UART1."
 *
 * @subsubsection cv5_timn_system_io_gpio_debug 4.2.2 General Purpose Input / Output (GPIO) Debug
 *
 * SW19 is a key button for software GPIO debugging. SW19 is connected to GPIO138, which includes
 * a default pull-high in hardware. The software can configure GPIO138 to verify the general
 * input / output function.  Pressing SW19 will assert low to GPIO138.<br>
 *
 *   - SW2.pin3 = ON: Connect GPIO138 to SW19
 *
 * @image html cv5_timn_jumpers_and_switches_for_gpio_debug.png "Figure 4-7. Jumpers and Switches for GPIO Debug (GPIO138)."
 *
 * @subsubsection cv5_timn_system_io_power_measurement 4.2.3 Power Measurement
 *
 * J105 and J106 are designed for power measurement. J105 and J106 have 30 / 20 pins and
 * 1.25-mm pitch connectors with a customized PIN-out. Contact the Ambarella support team
 * for more details.<br>
 *
 * @subsubsection cv5_timn_system_io_hdmi_tx 4.2.4 HDMI Transmit
 *
 * J46 is a standard vertical 19-pin HDMI receptacle for HDMI TX. Assemble the jumper on J45 to
 * enable 5-V power on J46.<br>
 *
 * @subsubsection cv5_timn_system_io_audio_hp_out 4.2.5 Audio Headphone out
 *
 * The on-board audio coder / decoder (codec) is AU8810. The audio HP out is available in J55,
 * which is a 3.5-mm audio jack.<br>
 *
 * The CV5 CLK_AU signal can be chosen to output to AU8810 or the external audio codec through SW12.<br>
 *
 *   - Assemble the jumpers on J52 and J54
 *   - SW12 = OFF: Connect to AU8810
 *   - SW12 = ON: Connect to the external audio codec
 *
 * @image html cv5_timn_jumpers_and_switches_for_audio_hp_out.png "Figure 4-8. Jumpers and Switches for Audio HP-Out."
 *
 * @subsubsection cv5_timn_system_io_cvbs_output 4.2.6 CVBS Output
 *
 * J47 is a mono RCA jack for the CVBS output.<br>
 *
 * @subsubsection cv5_timn_system_io_ir_receiver 4.2.7 Infrared (IR) Receiver
 *
 * U91 is an IR receiver module for the infrared remote control systems with a 38-kHz carrier
 * frequency.<br>
 *
 * @subsubsection cv5_timn_system_io_pinmux_sw1_to_sw5 4.2.8 PINMUX Switch – SW1~SW5
 *
 * SW1, SW2, and SW4 are 4-SPST switches, while SW3 and SW5 are 2-SPST switches used for the
 * PINMUX selection.<br>
 *
 * The table below shows a summary of the PINMUX switches. Refer to each sector for details.<br>
 *
 * <table>
 * <caption id="cv5_evk_mux_configurations">Table 4-2. CV5 EVK Mux Configurations.</caption>
 * <tr><th> Switch <th> Pin <th> Status <th> Function <th> Description
 * <tr><td align="center" rowspan="26"> SW1
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO65 as VSDELAY_HSYNC_OUT_0
 *     <td> HSYNC0 to VIN / DCPHY1 connector
 * <tr><td> GPIO66 as VSDELAY_HSYNC_OUT_1
 *     <td> HSYNC1 to SLVC-EC / DCPHY0 connector
 * <tr><td> GPIO67 as EXT_HSYNC_SRC_INPUT
 *     <td> HSYNC source input
 * <tr><td> GPIO68 as EXT_VSYNC_SRC_INPUT
 *     <td> VSYNC source input
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO65 as GPIO65
 *     <td> GPIO
 * <tr><td> GPIO66 as GPIO66
 *     <td> GPIO
 * <tr><td> GPIO67 as DMIC_CLK
 *     <td> DMIC clock
 * <tr><td> GPIO68 as DMIC_DAT
 *     <td> DMIC data
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO69 as SSI1_SCLK
 *     <td> SS1 clock
 * <tr><td> GPIO70 as SSI1_TXD
 *     <td> SSI1 TX Data
 * <tr><td> GPIO71 as SSI1_RXD
 *     <td> SSI1 RX Data
 * <tr><td> GPIO72 as SSI1_EN0
 *     <td> SSI1 to Gyro
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO69 as GPIO69
 *     <td> GPIO69 to VIN
 * <tr><td> GPIO70 as GPIO70
 *     <td> GPIO70 to VIN
 * <tr><td> GPIO71 as GPIO71
 *     <td> GPIO71 to VIN
 * <tr><td> GPIO72 as GPIO72
 *     <td> GPIO72 to VIN
  * <tr><td align="center" rowspan="6"> Pin3
 *     <td align="center" rowspan="3"> OFF
 *     <td> GPIO73 as SSI1_EN1
 *     <td> SSI1 to MIPI_DSI_A connector
 * <tr><td> GPIO74 as SSI1_EN2
 *     <td> SSI1 to MIPI_DSI_B connector
 * <tr><td> GPIO75 as SSI1_EN3
 *     <td> SSI1 to debug connector
 * <tr><td align="center" rowspan="3"> ON
 *     <td> GPIO73 as GPIO73
 *     <td> GPIO73 to VIN
 * <tr><td> GPIO74 as GPIO74
 *     <td> GPIO74 to VIN
 * <tr><td> GPIO75 as GPIO75
 *     <td> GPIO75 to VIN
 * <tr><td align="center" rowspan="4"> Pin4
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO76 as GPIO76
 *     <td> GPIO76 to VIN
 * <tr><td> GPIO77 as GPIO77
 *     <td> GPIO77 to VIN
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO76 as IDCSCLK
 *     <td> IDCS clock
 * <tr><td> GPIO77 as IDCSDATA
 *     <td> IDCS data
 * <tr><td align="center" rowspan="28"> SW2
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO92 as SDIO0_D[0]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO93 as SDIO0_D[1]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO94 as SDIO0_D[2]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO95 as SDIO0_D[3]
 *     <td> SDIO0 for SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO92 as VSDELAY_VSYNC_OUT_0
 *     <td> VSYNC0 to VIN
 * <tr><td> GPIO93 as VSDELAY_VSYNC_OUT_1
 *     <td> VSYNC1 to SLVS-EC
 * <tr><td> GPIO94 as VSDELAY_VSYNC_OUT_2
 *     <td> VSYNC2 to DCPHY0
 * <tr><td> GPIO95 as VSDELAY_VSYNC_OUT_3
 *     <td> VSYNC3 to DCPHY1
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO96 as SDIO0_CLK
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO97 as SDIO0_CMD
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO98 as SDIO0_CD
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO99 as SDIO0_WP
 *     <td> SDIO0 for SD socket
  * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO96 as IDC1CLK
 *     <td> IDC1 to DCPHY1 / MIPI_DSI_A connector
 * <tr><td> GPIO97 as IDC1DATA
 *     <td> IDC1 to DCPHY1 / MIPI_DSI_A connector
 * <tr><td> GPIO98 as GPIO98
 *     <td> GPIO
 * <tr><td> GPIO99 as GPIO99
 *     <td> GPIO
 * <tr><td align="center" rowspan="4"> Pin3
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO100 as GPIO100
 *     <td> SDIO0 PWRON for SD socket
 * <tr><td> GPIO138 as SDIO0_HS_SEL
 *     <td> SDIO0_HS_SEL
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO100 as GPIO100
 *     <td> Reset to DCPHY1 connector
 * <tr><td> GPIO138 as GPIO138
 *     <td> GPIO
 * <tr><td align="center" rowspan="8"> Pin4
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO101 as SDIO1_D[0]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO102 as SDIO1_D[1]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO103 as SDIO1_D[2]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO104 as SDIO1_D[3]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO101 as SSI3_RXD
 *     <td> SSI3 RX data
 * <tr><td> GPIO102 as SSI3_TXD
 *     <td> SSI3 TX data
 * <tr><td> GPIO103 as SSI3_SCLK
 *     <td> SSI3 clock
 * <tr><td> GPIO104 as SSI3_EN0
 *     <td> SSI3 to DCPHY1 / SLVS-EC connector
 * <tr><td align="center" rowspan="12"> SW3
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO105 as SDIO1_CLK
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO106 as SDIO1_CMD
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO107 as SDIO1_CD
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO108 as SDIO1_WP
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO105 as GPIO105
 *     <td> GPIO105 to DCPHY0 / SLVS-EC
 * <tr><td> GPIO106 as GPIO106
 *     <td> GPIO106 to DCPHY0
 * <tr><td> GPIO107 as IDC5CLK
 *     <td> IDC5 to DCPHY1 / SLVS-EC connector
 * <tr><td> GPIO108 as IDC5DATA
 *     <td> IDC5 to DCPHY1 / SLVS-EC connector
 * <tr><td align="center" rowspan="4"> Pin2
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO109 as GPIO109
 *     <td> SDIO1 PWRON for the Micro-SD socket
 * <tr><td> GPIO132 as SDIO1_HS_SEL
 *     <td> SDIO1_HS_SEL
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO109 as GPIO109
 *     <td> GPIO109 as reset to DCPHY0 / SLVS-EC connector
 * <tr><td> GPIO132 as GPIO132
 *     <td> GPIO132 as FLASH debug
 * <tr><td align="center" rowspan="26"> SW4
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO133 as I2S1_CLK or UART2_AHB_RX
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO134 as I2S1_SI_0 or UART2_AHB_TX
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO135 as I2S1_SO_0 or UART2_AHB_CTS_N
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO136 as I2S1_WS or UART2_AHB_RTS_N
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO133 as SSI4_SCLK
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO134 as SSI4_TXD
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO135 as SSI4_RXD
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO136 as SSI4_EN0
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td align="center" rowspan="2"> Pin2
 *     <td align="center"> OFF
 *     <td> GPIO0 as IR_IN
 *     <td> IR receiver (Input)
 * <tr><td align="center"> ON
 *     <td> GPIO0 as WDT_EXT_RST_L
 *     <td> WDTn
 * <tr><td align="center" rowspan="8"> Pin3
 *     <td aling="center" rowspan="4"> OFF
 *     <td> GPIO119 as GPIO119
 *     <td> GPIO
 * <tr><td> GPIO120 as GPIO120
 *     <td> GPIO
 * <tr><td> GPIO121 as GPIO121
 *     <td> GPIO
 * <tr><td> GPIO122 as GPIO122
 *     <td> GPIO
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO119 as USB32C_OVERCURRENT
 *     <td> USB32_Over_Current
 * <tr><td> GPIO120 as USB32C_DRIVE_VBUS
 *     <td> USB32_PWRON
 * <tr><td> GPIO121 as PWM10
 *     <td> PWM10
 * <tr><td> GPIO122 as PWM11
 *     <td> PWM11
 * <tr><td align="center" rowspan="8"> Pin4
 *     <td aling="center" rowspan="4"> OFF
 *     <td> GPIO123 as GPIO123
 *     <td> GPIO123 to MIPI_DSI_A
 * <tr><td> GPIO124 as GPIO124
 *     <td> GPIO124 to MIPI_DSI_A
 * <tr><td> GPIO125 as GPIO125
 *     <td> GPIO125 to MIPI_DSI_A
 * <tr><td> GPIO126 as GPIO126
 *     <td> GPIO126 to MIPI_DSI_A
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO123 as UART1_AHB_RX
 *     <td> UART1
 * <tr><td> GPIO124 as UART1_AHB_TX
 *     <td> UART1
 * <tr><td> GPIO125 as UART1_AHB_CTS_N
 *     <td> UART1
 * <tr><td> GPIO126 as UART1_AHB_RTS_N
 *     <td> UART1
 * <tr><td align="center" rowspan="16"> SW5
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO127 as GPIO127
 *     <td> GPIO127 to MIPI_DSI_B
 * <tr><td> GPIO128 as GPIO128
 *     <td> GPIO128 to MIPI_DSI_B
 * <tr><td> GPIO129 as GPIO129
 *     <td> GPIO129 to MIPI_DSI_B
 * <tr><td> GPIO130 as GPIO130
 *     <td> GPIO130 to MIPI_DSI_B
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO127 as CAN0_RX
 *     <td> CAN0
 * <tr><td> GPIO128 as CAN0_TX
 *     <td> CAN0
 * <tr><td> GPIO129 as CAN1_RX
 *     <td> CAN1
 * <tr><td> GPIO130 as CAN1_TX
 *     <td> CAN1
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO106 as IDC4CLK
 *     <td> IDC4 for VIN / external RTC
 * <tr><td> GPIO107 as IDC4DATA
 *     <td> IDC4 for VIN / external RTC
 * <tr><td> GPIO108 as IDC3CLK
 *     <td> IDC3 for VIN / EXGPIO
 * <tr><td> GPIO109 as IDC3DATA
 *     <td> IDC3 for VIN / EXGPIO
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO106 as SSI2_SCLK
 *     <td> SSI2 in debug header
 * <tr><td> GPIO107 as SSI2_TXD
 *     <td> SSI2 in debug header
 * <tr><td> GPIO108 as SSI2_RXD
 *     <td> SSI2 in debug header
 * <tr><td> GPIO109 as SSI2_EN0
 *     <td> SSI2 in debug header
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_sw1_to_sw5.png "Figure 4-9. Jumpers and Switches for SW1~SW5."
 *
 * @subsubsection cv5_timn_system_poc_switch_sw6_sw9 4.2.9 POC Switch ― SW6~SW9
 *
 * The table below shows the CV5 power on configuration (POC) setup in SW6~SW9. Contact the
 * Ambarella support team for the POC user guide.<br>
 *
 * <table>
 * <caption id="cv5_evk_poc_setup">Table 4-3. CV5 EVK POC Setup.</caption>
 * <tr><th> Designator <th> Pins <th> Notes
 * <tr><td align="center" rowspan="8"> SW6
 *     <td align="center"> pin A1
 *     <td> POC[21]=BOOT_OPTION[8]
 * <tr><td align="center"> pin A2
 *     <td> POC[1]=CLK_FRE[0]
 * <tr><td align="center"> pin A3
 *     <td> POC[2]=CLK_FRE[1]
 * <tr><td align="center"> pin A4
 *     <td> POC[3]=CLK_FRE[2]
 * <tr><td align="center"> pin A5
 *     <td> POC[8]=BOOT_BYPASS
 * <tr><td align="center"> pin A6
 *     <td> POC[30]=RESERVED
 * <tr><td align="center"> pin A7
 *     <td> POC[31]=SYSCONFIG_SRC
 * <tr><td align="center"> pin A8
 *     <td> POC[13]=BOOT_OPTION[0]
 * <tr><td align="center" rowspan="8"> SW7
 *     <td align="center"> pin A1
 *     <td> POC[16]=BOOT_OPTION[3]
 * <tr><td align="center"> pin A2
 *     <td> POC[17]=BOOT_OPTION[4]
 * <tr><td align="center"> pin A3
 *     <td> POC[18]=BOOT_OPTION[5]
 * <tr><td align="center"> pin A4
 *     <td> POC[19]=BOOT_OPTION[6]
 * <tr><td align="center"> pin A5
 *     <td> POC[20]=BOOT_OPTION[7]
 * <tr><td align="center"> pin A6
 *     <td> POC[4]=BOOT_MODE[0]
 * <tr><td align="center"> pin A7
 *     <td> POC[5]=BOOT_MODE[1]
 * <tr><td align="center"> pin A8
 *     <td> POC[6]=SECURE_BOOT
 * <tr><td align="center" rowspan="2"> SW8
 *     <td align="center"> pin A1
 *     <td> POC[14]=BOOT_OPTION[1]
 * <tr><td align="center"> pin A2
 *     <td> POC[15]=BOOT_OPTION[2]
 * <tr><td align="center"> SW9
 *     <td align="center"> pin A1
 *     <td> POC[10]=FORCE_USB_BOOT
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_poc.png "Figure 4-10. Jumpers and Switches for POC."
 *
 * @subsubsection cv5_timn_poc_table 4.2.10 CV5 POC Table
 *
 * <table>
 * <caption id="cv5_timn_evk_poc_table">Table 4-3. CV5 POC Table.</caption>
 * <tr><th> POC bit <th> PIN Name <th colspan="5"> Description <th> EVK Default
 * <tr><td> POC[3:1]
 *     <td> ENET_TXD[3:1]
 *     <td colspan = "5"> IDSP/CORE/DDR Clock config <br>
 *          VDSP/IDSP/VISION/CORTEX/NAND(contact for below frequency setting) <br>
 *          000:  912 / 1104 / 1104 / 1584 / 528 Mhz <br>
 *          001: 1200 / 1200 / 1392 / 1800 / 528 Mhz <br>
 *          010:  504 /  600 /  600 /  816 / 264 Mhz <br>
 *          011:  960 / 1056 / 1056 / 1536 / 528 Mhz <br>
 *          100: 1056 / 1152 / 1152 / 1632 / 528 Mhz <br>
 *          101: 1008 / 1056 / 1056 / 1584 / 528 Mhz <br>
 *          110:  504 /  600 /  600 /  816 / 360 Mhz <br>
 *          111:  432 /  432 /  432 /  432 / 264 Mhz
 *     <td> 111
 * <tr><td> POC[5:4]
 *     <td> ENET1_TXD[1:0]
 *     <td  colspan = "5"> Boot Mode [1:0] <br>
 *          00: SPINOR <br>
 *          01: NAND (include SPI NAND) <br>
 *          10: eMMC <br>
 *          11: PCIe
 *     <td> 01
 * <tr><td> POC[6]
 *     <td> ENET1_TXD[2]
 *     <td  colspan = "5"> Secure boot: <br>
 *          0: Clear boot <br>
 *          1: Secure boot
 *     <td> 0
 * <tr><td> POC[8]
 *     <td> CLK_AU[8]
 *     <td  colspan = "5"> Boot Bypass: <br>
 *          0: disable <br>
 *          1: enable
 *     <td> 0
 * <tr><td> POC[10]
 *     <td> ENET_PTP_PPS
 *     <td  colspan = "5"> Force USB boot: <br>
 *          0: disable <br>
 *          1: enable
 *     <td> 0
 * <tr><td rowspan = "2"> [21:13]
 *     <td>
 *     <td colspan = "5"> Boot Options[8:0]
 *     <td>
 * <tr><td>
 *     <td> <b> Boot Option </b>
 *     <td> <b> SPI-NOR </b>
 *     <td> <b> NAND </b>
 *     <td> <b> eMMC </b>
 *     <td> <b> PCIe </b>
 *     <td>
 * <tr><td> POC[21]
 *     <td> ENET_GTX_CLK
 *     <td> boot_option[8]
 *     <td>
 *     <td>
 *     <td> <b> eMMC boot controller sel </b> <br>
 *          1: Legancy SD
 *     <td>
 *     <td>
 * <tr><td> POC[20]
 *     <td> SHSYNC
 *     <td> boot_option[7]
 *     <td>
 *     <td> <b> 8K BST code size Select </b> <br>
 *          0: 4K BST code size <br>
 *          1: 8K BST code size
 *     <td> <b> eMMC bst 8k </b> <br>
 *          0: 4K BST code size <br>
 *          1: 8K BST code size
 *     <td>
 *     <td> 1
 * <tr><td> POC[19]
 *     <td> SVSYNC
 *     <td> boot_option[6]
 *     <td>
 *     <td>
 *     <td> <b> tRSCA sel boot </b> <br>
 *          0: For tRSCA=75 SD clock cycles <br>
 *          1: For tRSCA=10000 SD clock cycles
 *     <td>
 *     <td>
 * <tr><td> POC[18]
 *     <td> PWM0
 *     <td> boot_option[5]
 *     <td>
 *     <td> <b> SCK Mode </b> <br>
 *          0: Mode 0 (CPOL = 0. CPHA = 0) <br>
 *          1: Mode 3 (CPOL = 1. CPHA = 1) <br>
 *     <td> <b> tRSCA </b> <br>
 *          Set this value to 1 to delay the timing of boot initialization
 *     <td>
 *     <td> 0
 * <tr><td> POC[17]
 *     <td> ENET1_PTP_PPS
 *     <td> boot_option[4]
 *     <td>
 *     <td> <b> 4K/2K Page Select </b> <br>
 *          0: 4K-page <br>
 *          1: 2K-page
 *     <td> <b> eMMC reset for SW Boot </b> <br>
 *          When eMMC boot = 1, mmc_boot_sel = 1 and emmc_reset_default_on = 1.
 *          Legacy SD controller will drive sdio1_reset signal through pad sd_reset.
 *     <td> Ref24
 *     <td> 1
 * <tr><td> POC[16]
 *     <td> I2S_SO_0
 *     <td> boot_option[3]
 *     <td> <b> SPI Mode Selection </b> <br>
 *          0: SPI mode 0 <br>
 *          1: SPI mode 1
 *     <td> <b> Skip ECC check for Blank </b> <br>
 *          0: Do not skip ECC check for blank pages <br>
 *          1: Skip ECC check for blank pages
 *     <td> <b> eMMC boot sd pull </b> <br>
 *          When 0: No pull on sd_cmd and sd_d[7:0] <br>
 *          When 1: Interal pull high on sd_cmd and sd_d[7:0]
 *     <td> DDR5
 *     <td> 1
 * <tr><td> POC[15]
 *     <td> UART_APB_TX
 *     <td> boot_option[2]
 *     <td> <b> Boot Mode[2] </b> <br>
 *          Take reference to table: @ref cv5_boot_mode_table
 *     <td> <b> NAND ECC BCH Enable </b> <br>
 *          Enable ECC BCH function or not
 *     <td> <b> 4-bit Bus Width </b> <br>
 *          Use 4 SD data pins for boot
 *     <td> Gen
 *     <td> 0
 * <tr><td> POC[14]
 *     <td> UART1_AHB_TX
 *     <td> boot_option[1]
 *     <td> <b> Boot Mode[1] </b> <br>
 *          Take reference to table: @ref cv5_boot_mode_table
 *     <td> <b> NAND Spare Cell 2x </b> <br>
 *          0: Support 1X NAND spare area <br>
 *             When NAND page size if 0: Spare area = 128 B <br>
 *             When NAND page size if 1: Spare area =  64 B <br>
 *          1: Support 2X NAND spare area <br>
 *             When NAND page size if 0: Spare area = 256 B <br>
 *             When NAND page size if 1: Spare area = 128 B
 *     <td> <b> 8-bit Bus Width </b> <br>
 *          Use 8 SD data pins for boot
 *     <td rowspan="2"> sub-mode[1:0]
 *     <td> 1
 * <tr><td> POC[13]
 *     <td> UART0_AHB_TX
 *     <td> boot_option[0]
 *     <td> <b> Boot Mode[0] </b> <br>
 *          Take reference to table: @ref cv5_boot_mode_table
 *     <td> <b> Flash Fast Boot </b> <br>
 *          0: Normal NAND flash component read cycle time <br>
 *          1: Shorter NAND flash component read cycle time
 *     <td> <b> hs boot </b> <br>
 *          0: Default-Speed Mode (12.5 MB/sec interface speed related for sd4_boot or 25 MB/sec interface speed for sd8_boot) <br>
 *          1: High-Speed Mode (25 MB/sec interface speed for sd4_boot, 50 MB/sec interface speed for sd8_boot)
 *     <td> 0
 * <tr bgcolor="#00FFFF"><td> POC[30]
 *     <td> I2S_WS
 *     <td  colspan = "5"> Reserved (Set to 0)
 *     <td>
 * <tr><td> POC[31]
 *     <td> PWM1
 *     <td  colspan = "5"> Source of sys config data: <br>
 *          0: config data is set by pins <br>
 *          1: config data is read from on-chip efuse rom
 *     <td> 1
 * </table>
 *
 * <table>
 * <caption id="cv5_boot_mode_table">Table 4-4. Boot Modes of SPI NOR.</caption>
 * <tr><th> Boot Option <th colspan="6"> Description <th> POC Pin
 * <tr><td rowspan="7"> Boot mode
 *     <td colspan="6"> Initial boot mode
 *     <td rowspan="7"> 15:13
 * <tr><td> <b> Boot Mode </b>
 *     <td> <b> Target Device </b>
 *     <td> <b> Interface </b>
 *     <td> <b> Address #Bytes </b>
 *     <td> <b> Read Command </b>
 *     <td> <b> Reset Command </b>
 * <tr><td> 0
 *     <td> Generic Device
 *     <td> Extended SPI (a)
 *     <td> 3
 *     <td> 0x03
 *     <td> 0x66-0x99 (b)
 * <tr><td> 1
 *     <td> Generic Device
 *     <td> Extended SPI
 *     <td> 3
 *     <td> 0x03
 *     <td> 0xFF-0xF0 (c)
 * <tr><td> 2
 *     <td> Micron
 *     <td> Octave-IO, A/D DDR (d), Dummy Length 16
 *     <td> 4
 *     <td> 0x8B
 *     <td> 0x66-0x99
 * <tr><td> 3-7
 *     <td> (Reserved)
 *     <td>
 *     <td>
 *     <td>
 *     <td>
 * <tr><td colspan="6"> <b> Note </b> <br>
 *     (a) SPI transmission bit order for all modes is MSB first. <br>
 *     (b) MICRON / MXIC / GigaDevice. Reset enable (0x66) followed by reset command (0x99). <br>
 *     (c) Spansion. Mode bit reset (MBR; 0xFF) followed by reset command (0xF0) <br>
 *     (d) A/D DDR -- Double samples per clock on address / data stage.
 * </table>

 *
 * @subsubsection cv5_timn_can_bus 4.2.11 Controller Area Network (CAN) Bus
 *
 * J76 is a 2x2, 2.54-mm connector for the CAN bus. J77 is a jumper that enables the CAN
 * transceiver. In normal mode, assemble the jumper on J77.<br>
 *
 *   - SW21 = OFF: Select CAN0
 *   - SW21 = ON: Select CAN1
 *
 * @image html cv5_timn_jumpers_and_switches_for_can.png "Figure 4-11. Jumpers and Switches for CAN."
 *
 * @subsubsection cv5_timn_pcie_x4 4.2.12 PCIe x4
 *
 * J36 and J37 are two standard, 64-pin PCIe x4 card edge connectors.
 *
 * The PCIe reference clock is generated from the PCIe clock generator PI6CG18401, which can be
 * configured through SW22.<br>
 *
 *   - SW22.pin1 = OFF: Disable the SS function
 *   - SW22.pin1 = ON: Enable the SS function at -0.5% spread
 *   - SW22.pin2 = OFF: Power on the PCIe clock generator
 *   - SW22.pin2 = ON: Power down the PCIe clock generator
 *
 * @image html cv5_timn_jumpers_and_switches_for_pcie_4.png "Figure 4-12. Jumpers and Switches for PCIe x 4."
 *
 * @subsubsection cv5_timn_jtag_connector 4.2.13 Joint Test Action Group (JTAG) Connector
 *
 * J60 is a 10x2, 2.54-mm connector for JTAG debugging.<br>
 *
 * @subsubsection cv5_timn_rtc_battery_holder 4.2.14 Real-time Clock (RTC) Battery Holder
 *
 * BAT2 is a 2032 battery holder for the CV5 RTC block. By default, the battery is not assembled.
 * Ensure correct battery polarity during assembly.<br>
 *
 * @subsubsection cv5_timn_mcu_swd_connector 4.2.15 MCU Serial Wire Debug (SWD) Connector
 *
 * J72 is a 5x2, 2.54-mm connector for the MCU debug tool. It supports a 2-pin serial wire debug
 * function only.<br>
 *
 * @subsubsection cv5_timn_mcu_reset_button 4.2.16 MCU Reset Button
 *
 * J75 is the MCU reset button, which triggers an active-low signal to assert a hardware reset
 * to the MCU.<br>
 *
 * @subsubsection cv5_timn_reset_button 4.2.17 Reset Button
 *
 * SW13 functions as the system reset button, which triggers an active-low signal to assert a
 * system reset to CV5 power-on reset (POR) pin.<br>
 *
 * @subsubsection cv5_timn_mcu_power_on_button 4.2.18 MCU Power-on Button
 *
 * SW20 functions as a power-on button, which triggers an active-low signal to indicate a power-on
 * action to the MCU. Ensure that the software has enabled this function in the MCU.<br>
 *
 * @subsubsection cv5_timn_power_on_off_switch_button 4.2.19 Power ON / OFF Switch Button
 *
 * SW23 functions as a system power ON / OFF switch button. Pressing SW23 will power on the
 * system if the system is in the OFF state, or power off the system if the system is in the
 * ON state. Do not assemble a jumper on J79.  If there is a jumper on J79, it will bypass SW23.<br>
 *
 * @subsubsection cv5_timn_power_jack 4.2.20 Power Jack
 *
 * J78 is a standard 2.5-mm power jack for an external 12-V power adapter. Plugging the power
 * adapter through J78 supplies the power for the CV5 EVK base board.<br>
 *
 * @subsubsection cv5_timn_ethernet0 4.2.21 Ethernet0
 *
 * The CV5 EVK base board supports 1.8-V I/O between the MAC and the PHY only.<br>
 * CV5 requires a 125-MHz reference clock if GMAC functions. The 125-MHz clock can be chosen
 * from external oscillator or from GPHY. Use switch SW30 to choose which is used.<br>
 *
 *   - SW30 = OFF: Select 125-MHz clock from external oscillator
 *   - SW30 = ON: Select 125-MHz clock from GPHY
 *
 * @image html cv5_timn_jumpers_and_switches_for_ethernet_125mhz_clock.png "Figure 4-13. Jumpers and Switches for Ethernet 125-MHz Clock."
 *
 * Both GPHYs RTL8211 can supply the 125-MHz reference clock to the MAC. They can be chosen
 * through switch SW10 pin 1.<br>
 *
 *   - SW10.pin1 = OFF: Select 125-MHz clock from GPHY RTL8211
 *   - SW10.pin1 = ON: Select 125-MHz clock from GPHY1 RTL8211
 *
 * J50 is a 10 / 100 / 1000 Base-T Ethernet single-port RJ45 connector with LEDs (link / act).
 * The CV5 ENET0 media access control (MAC) supports the RGMII / RMII interfaces and the
 * management data clock (MDC) / management data input / output (MDIO) management interface to
 * the external Ethernet PHY.<br>
 *
 * Both Giga PHY RTL8211 and Mega PHY RTL8201 are assembled on the board. RTL8211 is connected
 * to the CV5 through RGMII I/F, and RTL8201 is connected to the CV5 through RMII I/F. Only one
 * can be used at a time. Use switch SW10 pin2 to choose which is used.<br>
 *
 *   - SW10.pin2 = OFF: Enable GPHY RTL8211
 *   - SW10.pin2 = ON: Enable MPHY RTL8201
 *
 * @image html cv5_timn_jumpers_and_switches_for_ethernet.png "Figure 4-14. Jumpers and Switches for Ethernet."
 *
 * @subsubsection cv5_timn_ethernet1 4.2.22 Ethernet1
 *
 * J51 is a 10 / 100 / 1000 Base-T Ethernet single port RJ45 connector with LEDs (link / act).
 * The CV5 ENET1 MAC supports the RGMII / RMII interfaces and the MDC / MDIO management interface
 * to the external Ethernet PHY.<br>
 *
 * Both Giga PHY RTL8211 and Mega PHY RTL8201 are assembled on the board. RTL8211 is connected to
 * CV5 through RGMII I/F, and RTL8201 is connected to CV5 through RMII I/F. Only one can be used
 * at a time. Use switch SW11 to choose which is used.<br>
 *
 *   - SW11 = OFF: Enable GPHY RTL8211
 *   - SW11 = ON: Enable MPHY RTL8201
 *
 * @image html cv5_timn_jumpers_and_switches_for_ethernet1.png "Figure 4-15. Jumpers and Switches for Ethernet 1."
 *
 * @subsubsection cv5_timn_adc1_key_buttons 4.2.23 ADC1 Key Buttons
 *
 * SW14~SW18 are key buttons to simulate menu / direction buttons. Ensure that the software has
 * this function enabled in ADC1.<br>
 *
 * @subsubsection cv5_timn_usb_2_0_device_serial_debug_port 4.2.24 USB2.0 Device / Serial Debug Port
 *
 * J25 is a Micro-B USB receptacle. USB0 I/F functions only in device mode. Plug the USB cable
 * from the USB host to J25. The AmbaUSB tool functions in this mode and serves as a serial
 * debug port, because a USB-to-UART chip is used to perform the interface conversion.<br>
 *
 * @subsubsection cv5_timn_usb_3_1_device 4.2.25 USB3.1 Device
 * * J29 is a Micro-B USB3.1 receptacle. When USB1 I/F is in device mode, plug the USB host to J29.<br>
 *
 *   - Jumper on J28 must be assembled
 *
 * @subsubsection cv5_timn_usb_3_1_host 4.2.26 USB3.1 Host
 *
 * J31 is a Type-A USB3.1 receptacle. When USB1 I/F is in host mode, plug the USB device to J31.<br>
 *
 *   - Jumper on J28 must not be assembled
 *   - Jumper on J30 must be assembled
 *
 * @subsubsection cv5_timn_usb_3_1_hub_host 4.2.27 USB3.1 Hub Host
 *
 * J32 is a Type-C USB3.1 receptacle, and J33~J35 are Type-A USB3.1 receptacles from the on-board
 * USB3.1 hub. When USB1 I/F is in host mode and is connected through the USB 3.1 hub, J32~J36 will
 * be available.<br>
 *
 *   - Jumper on J28 must not be assembled
 *   - Jumper on J30 must not be assembled
 *
 * @subsubsection cv5_timn_core_board_sockets 4.2.28 Core Board Sockets
 *
 * J1 and J2 are two high-speed sockets with ground planes. J1 has 120 pins and J2 has 180 pins.
 * They are used to connect the CV5 series core boards.<br>
 *
 * @subsubsection cv5_timn_vout_mipi_dsi 4.2.29 VOUT MIPI DSI
 *
 * J48 and J49 are two 20x2, 0.5-mm FFC / FPC connectors for MIPI DSI A and B output. They are
 * customized PIN-out connectors. Check the reference design for more details.<br>
 *
 * @subsubsection cv5_timn_vin_dcphy 4.2.30 VIN DCPHY
 *
 * J43 and J44 are two 41-pin, 0.5-mm pitch, 3.8-mm height connectors for the VIN DCPHY I/Fs.
 * They are customized PIN-out connectors. Check the reference design for more details.<br>
 *
 * @subsubsection cv5_timn_vin_slvs_ec 4.2.31 VIN SLVS-EC
 *
 * J42 is a 51-pin, 0.5-mm pitch, 3.8-mm height connector for the VIN SLVS-EC I/F. J42 is a
 * customized PIN-out connector. Check the reference design for more details.<br>
 *
 * @subsubsection cv5_timn_vin_slvs_dphy 4.2.32 VIN SLVS+DPHY
 *
 * J39 is a standard 164-pin PCIe connector for the VIN SLVS+DPHY. J39 is a customized PIN-out
 * connector. Check the reference design for more details.<br>
 *
 * @subsubsection cv5_timn_nvme_m_2_connector 4.2.33 Nonvolatile Memory Express (NVMe) M.2 Connector
 *
 * J38 is a standard NVMe M.2 connector for the PCIe-based SSD hard drive.<br>
 *
 * @subsubsection cv5_timn_sdio0 4.2.34 SDIO0
 *
 * SDIO0 is available in J13, which is an SD socket on the bottom side.<br>
 *
 *   - SW2.pin1 / 2 / 3 = LOW: SDIO0 is connected to the J13 socket shown in the figure below:
 *
 * @image html cv5_timn_jumpers_and_switches_for_sdio0.png "Figure 4-16. Jumpers and Switches for SDIO0."
 *
 * J14 and J15 are used to control the J13 VDD (3.3 V).<br>
 *
 *   - Short J15 by default: Enable software control on the VDD
 *   - Short J14: Make the VDD always-on
 *
 * @image html cv5_timn_jumpers_and_switches_for_sdio0_j14_j15.png "Figure 4-17. Jumpers and Switches for J14 and J15."
 *
 * When an SD memory card is used in J13:<br>
 *
 *   - Jumper on J16 must be assembled
 *   - Jumper on J18 must not be assembled
 *
 * When an SD I/O card is used in J13:<br>
 *
 *   - Jumper on J16 must not be assembled
 *   - Jumper on J18 must be assembled to select SDIO0 I/O voltage
 *     - J18.pin1-2: SDIO0_VDDO = 1.8 V
 *     - J18.pin2-3: SDIO0_VDDO = 3.3 V
 *
 * @image html cv5_timn_jumpers_and_switches_for_sdio0_j16_j18.png "Figure 4-18. Jumpers and Switches for SDIO0."
 *
 * @subsubsection cv5_timn_sdio1 4.2.35 SDIO1
 *
 * SDIO1 is available in J19, which is a micro-SD socket on the bottom side.<br>
 *
 *   - SW2.pin4 = LOW and SW3.pin1/2 = LOW: SDIO1 is connected to the J19 socket
 *
 * @image html cv5_timn_jumpers_and_switches_for_sdio1_sw2_sw3.png "Figure 4-19. Jumpers and Switches for SDIO1."
 *
 * J20 and J21 are used to control the J16 VDD (3.3 V).
 *
 *   - Jumpers on J21 must be assembled by default to enable software control on the VDD.
 *   - Jumpers on J20 can be assembled to make the VDD always on.
 *
 * @image html cv5_timn_jumpers_and_switches_for_sdio1_j20_j21.png "Figure 4-20. Jumpers and Switches for J20 and J21."
 *
 * When the SD memory card is used in J19:
 *
 *   - Jumper on J22 must be assembled
 *   - Jumper on J24 must not be assembled
 *
 * When an SD I/O card is used in J19:
 *
 *   - Jumper on J22 must not be assembled
 *   - Jumper on J24 must be assembled to select SDIO0 I/O voltage
 *     - J24.pin1-2: SDIO1_VDDO = 1.8 V
 *     - J24.pin2-3: SDIO1_VDDO = 3.3 V
 *
 * @image html cv5_timn_jumpers_and_switches_for_sdio1_j22_j24.png "Figure 4-21. Jumpers and Switches for SDIO1."
 *
 * @subsubsection cv5_timn_lithium_battery 4.2.36 Lithium Battery
 *
 * BAT1 is a 1.5-V lithium battery for the CV5 real-time clock (RTC) block. By default, the battery
 * is not assembled. Ensure correct battery polarity during assembly.<br>
 *
 * @subsubsection cv5_timn_spi_nand_nor_flash_switch 4.2.37 SPI NAND / NOR Flash Switch
 *
 * SW1 in the core board is used to select different boot sources between SPI NAND flash and
 * SPI NOR flash. This table provides the selection by SW1.
 *
 * <table>
 * <caption id="cv5_spi_nand_nor_flash_sel">Table 4-5. CV5 SPI NAND / NOR Flash Selection.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="165px"> Boot Source
 * <tr><td align="center" rowspan="2"> SW1
 *     <td align="center"> ON
 *     <td align="center"> SPI NOR
 * <tr><td align="center"> OFF
 *     <td align="center"> SPI NAND (Default)
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_spi_nand_nor_flash_sel.png "Figure 4-22. Jumpers and Switches for SPI NAND / NOR Flash Selection."
 *
 * @subsubsection cv5_timn_power_jumpers 4.2.38 Power Jumpers
 *
 * J4 in the core board is used to adjust the VDD. The table below provides the VDD
 * configuration via J4:<br>
 *
 * <table>
 * <caption id="cv5_vdd_configuration">Table 4-6. CV5 VDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Jumpers <th width="165px"> VDD Value (V)
 * <tr><td align="center" rowspan="4"> J4
 *     <td align="center"> 1-3
 *     <td align="center"> 0V7
 * <tr><td align="center"> 3-5
 *     <td align="center"> 0V75 (Default)
 * <tr><td align="center"> 4-6
 *     <td align="center"> 0V8
 * <tr><td align="center"> 2-4
 *     <td align="center"> 0V85
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_cv5_vdd_in_core_board.png "Figure 4-23. Jumpers and Switches for CV5 VDD in the Core Board."
 *
 * @note
 *   - Do not adjust the VDD voltage when the board is powered on so as to avoid permanently
 *     damaging the CV5 chipset.<br>
 *
 * SW27 is used to adjust the VDDA. The table below provides the VDDA configuration by SW27:<br>
 *
 * <table>
 * <caption id="cv5_vdda_configuration">Table 4-7. CV5 VDDA Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="165px"> VDDA Value (V)
 * <tr><td align="center" rowspan="2"> SW27
 *     <td align="center"> ON
 *     <td align="center"> 0V8 (Default)
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V825
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_cv5_vdda.png "Figure 4-24. Jumpers and Switches for CV5 VDDA."
 *
 * SW28 is used to select the PCIE_AVDD. The table below provides the PCIE_AVDD configuration
 * by SW28.<br>
 *
 * <table>
 * <caption id="cv5_pcie_avdd_configuration">Table 4-8. CV5 PCIE_AVDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> PCIE_AVDD Value (V)
 * <tr><td align="center" rowspan="2"> SW28
 *     <td align="center"> ON
 *     <td align="center"> 0V8
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V85 (Default)
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_pcie_avdd.png "Figure 4-25. Jumpers and Switches for PCIE_AVDD."
 *
 * SW29 is used to select the DCPHY_AVDD. This table provides the DCPHY_AVDD configuration
 * by SW29.<br>
 *
 * <table>
 * <caption id="cv5_dcphy_avdd_configuration">Table 4-9. CV5 DCPHY_AVDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> DCPHY_AVDD Value (V)
 * <tr><td align="center" rowspan="2"> SW29
 *     <td align="center"> ON
 *     <td align="center"> 0V8
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V85 (Default)
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_cv5_cdphy_avdd.png "Figure 4-26. Jumpers and Switches for CV5 CDPHY_AVDD."
 *
 * J112 and J113 are used to select the power enablement of PWR_CVSYS_5V and PWR_CVSYS_3V3.
 * This table provides the PWR_CVSYS_5V and PWR_CVSYS_3V3 configuration by J112 and J113.<br>
 *
 * <table>
 * <caption id="cv5_power_5v_33v_configuration">Table 4-10. CV5 PWR_CVSYS_5V and PWR_CVSYS_3V3 Power Enable Source Configuation.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="165px"> Jumpers <th width="200px"> Power Enable Source
 * <tr><td align="center" rowspan="2"> J112
 *     <td align="center" rowspan="2"> PWR_CVSYS_5V
 *     <td align="center"> 1-2
 *     <td align="center"> 12 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> PWR_PSEQ1 (Default)
 * <tr><td align="center" rowspan="2"> J113
 *     <td align="center" rowspan="2"> PWR_CVSYS_3V3
 *     <td align="center"> 1-2
 *     <td align="center"> 12 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> PWR_PSEQ1 (Default)
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_cv5_pwr_cvsys_5v_33v.png "Figure 4-27. Jumpers and Switches for CV5 PWR_CVSYS_5V and PWR_CVSYS_3V3 Power Enable Source."
 *
 * J7 and J8 are used to select the embedded multi-media controller (eMMC) VCC and eMMC
 * VCCQ (CV5 SD_VDDO). This table provides the PWR_CVSYS_5V and PWR_CVSYS_3V3 configuration by
 * J7 and J8.<br>
 *
 * <table>
 * <caption id="emmc_vcc_vccq_configuration">Table 4-11. eMMC VCC and eMMC VCCQ (CV5 SD_VDDO) Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Power Rail <th width="165px"> Jumpers <th width="200px"> Power Rail Value (V)
 * <tr><td align="center" rowspan="2"> J7
 *     <td align="center" rowspan="2"> EMMC VCC
 *     <td align="center"> 1-2
 *     <td align="center"> 1.8 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> 3.3 V (Default)
 * <tr><td align="center" rowspan="2"> J8
 *     <td align="center" rowspan="2"> EMMC VCCQ<br>
 *                                     (CV5_SD_VDDO)
 *     <td align="center"> 1-2
 *     <td align="center"> 1.8 (Default)
 * <tr><td align="center"> 2-3
 *     <td align="center"> 3.3 V
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_peripheral_1v8_3v3_5v_12v.png "Figure 4-28. Jumpers and Switches for Peripheral 1V8 / 3V3 / 5V / 12V Power Enable Source."
 *
 * J102 and J103 are used to select the power enablement of peripheral 1V8 / 3V3 / 5V / 12V.
 * The table below provides the power enable configuration of peripheral power rails by J102
 * and J103.<br>
 *
 * <table>
 * <caption id="power_enable_peripheral_configuration">Table 4-12. Power Enable of peripheral 1V8 / 3V3 / 5V / 12V Configuation.</caption>
 * <tr><th width="165px"> Designator <th width="530px"> Power Enable of peripheral 1V8 / 3V3 / 5V / 12V
 * <tr><td align="center"> J102
 *     <td align="center"> SYS_RSTn (Default)
 * <tr><td align="center"> J103
 *     <td align="center"> CV_3V3
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_emmc_vcc_and_vccq.png "Figure 4-29. Jumpers and Switches for eMMC VCC and eMMC VCCQ."
 *
 * @subsubsection cv5_timn_external_wdt 4.2.39 External Watch Dog Timer (WDT)
 *
 * The WDT is implemented in the RESET chip. J123 is used to enable the WDT.
 * The following table provides the selection by J123.<br>
 *
 * <table>
 * <caption id="cv5_spi_nand_nor_flash_sel">Table 4-13. CV5 SPI NAND / NOR Flash Selection.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="165px"> Boot Source
 * <tr><td align="center" rowspan="2"> J123
 *     <td align="center"> 1-2
 *     <td align="center"> Enable WDT
 * <tr><td align="center"> 2-3
 *     <td align="center"> Disable WDT (Default)
 * </table>
 *
 * @image html cv5_timn_jumpers_and_switches_for_external_wdt_sel.png "Figure 4-30. Jumpers and Switches for External WDT Selection."
 *
 * @subsubsection cv5_timn_imu_switch 4.2.40 IMU Switch
 * <table>
 * <caption id="cv5_imu_switch">Table 4-14. CV5 IMU Switch.</caption>
 * <tr><th width="165px"> Designator-Pins <th width="85px"> Status <th width="400px"> Notes
 * <tr><td align="center" rowspan="2"> SW1-Pin2
 *     <td align="center"> OFF
 *     <td> SSI1 to Gyro; SSI1 RX Data and TX Data; SS1 clock
 * <tr><td align="center"> ON
 *     <td> GPIO69-72 to VIN
 * </table>
 *
 * - - - -
 *
 * @section cv5_timn_doc_license 5 License
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
 * @file doc_hw_cv52_co.h
 * @brief
 * @version 1.0
 * @date 2022-08-25
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
 * @page page_cv52_cocr Board - CV52 Co / Cr
 *
 * This chapter provides details on setting up the hardware for the evaluation kit (EVK) and is
 * divided into the following sections:<br>
 *
 *   - Section @ref cv52_co_evk_package
 *   - Section @ref cv52_co_overview
 *   - Section @ref cv52_co_setting_up
 *   - Section @ref cv52_co_lpddr4x_system_io_hardware_control
 *   - Section @ref cv52_cr_lpddr5_system_io_hardware_control
 *   - Section @ref cv52_co_doc_license
 *
 * - - - -
 *
 * @section cv52_co_evk_package 1 EVK Package
 *
 * The Ambarella Cooper Linux EVK contains the following hardware and accessories. If any of the
 * following components are missing from the EVK package, contact the Ambarella support team.<br>
 *
 * <table>
 * <tr><td align="center"> <b> EVK Board: </b>
 *     <td> The board that comes furnished with the Ambarella CV52 System on chip (SoC)
 * <tr><td align="center"> <b> Sensor Board: </b>
 *     <td> The sensor board that is connected to the EVK board as the video input (VIN)
 * <tr><td align="center"> <b> Cables: </b>
 *     <td> Serial cable and USB cable
 * <tr><td align="center"> <b> EVK firmware: </b>
 *     <td> The firmware in the folder Binary/ that is upgraded to the EVK board
 * <tr><td align="center"> <b> Install program: </b>
 *     <td> The tools in the folder Tools/ that are used for evaluation, including <br>
 *          AmbaUSB, PortServer, USBServer, and the VLC player
 * <tr><td align="center"> <b> Getting started guide: </b>
 *     <td> The document provides information on how to use the EVK
 * </table>
 *
 * The pre-loaded demonstration application is provided through the following:<br>
 *
 * <table>
 * <tr><td align="center" width="165px"> <b> Unit test program: </b>
 *     <td> The unit test applications used to evaluate features using commands from<br>
 *          the command line interface
 * </table>
 * - - - -
 *
 * @section cv52_co_overview 2 Overview of the EVK Board
 *
 * The figure below provides an overview of the major components and I/O connectors of the
 * CV52 EVK board.<br>
 *
 * @image html cv52_co_evek_board.png "Figure 2-1. CV52 Co Board."
 *
 * The major components and I/O connectors identified in the figure above are as follows:<br>
 *
 * <b>1.</b> USB to serial debug UART + firmware download port<br>
 * <b>2.</b> Internal power on / off<br>
 * <b>3.</b> Reset<br>
 * <b>4.</b> External power on / off<br>
 * <b>5.</b> MCU reset<br>
 * <b>6.</b> Audio line-out<br>
 * <b>7.</b> Audio HP out<br>
 * <b>8.</b> Audio speaker out<br>
 * <b>9.</b> JTAG<br>
 * <b>10.</b> Dual in-line package (DIP) switches<br>
 * <b>11.</b> Video input (VIN) port1<br>
 * <b>12.</b> VIN port2<br>
 * <b>13.</b> VIN port3<br>
 * <b>14.</b> VIN port3<br>
 * <b>15.</b> Mobile industry processor interface (MIPI) DSI VOUT<br>
 * <b>16.</b> USB 3.0 host<br>
 * <b>17.</b> USB Type-C<br>
 * <b>18.</b> Micro USB3.0 device<br>
 * <b>19.</b> CVBS VOUT<br>
 * <b>20.</b> IR-receiver<br>
 * <b>21.</b> PCIe x4 port<br>
 * <b>22.</b> Ethernet<br>
 * <b>23.</b> Ethernet<br>
 * <b>24.</b> 12-V DC power<br>
 * <b>25.</b> HDMI VOUT<br>
 * - - - -
 *
 * @section cv52_co_setting_up 3 Setting Up the EVK Board
 *
 * Use the following steps to set up the EVK hardware for the first time:<br>
 *
 *   - Using a grounding strap or another verified device to protect the board from static
 *     charges, connect the communication cables to the board before connecting any equipment
 *     to the power supply.<br>
 *
 *   - Ensure that the parallel sensors used on the CV52 boards are compatible with the adapter,
 *     and then carefully insert the sensor board to the slot of the primary VIN, which is
 *     component 1 on the EVK board (see the following figure). Ensure that the sensor board is
 *     secure before proceeding.<br>
 *
 * @image html cv52_co_evk_board_with_hdmi_ethernet_usb_cable_connected.png "Figure 3-1. Sensor Board Inserted into the CV52 Co Board."
 *
 *   - Use an Ethernet cable to join the Ethernet port on the EVK board to the network port on
 *     the host PC.<br>
 *
 *   - For high-definition (HD) preview, connect a video display with a high-definition multimedia interface (HDMI)
 *     input to the HDMI connector on the EVK board.<br>
 *
 * @image html cv52_co_evk_board_with_hdmi_ethernet_usb_cable_connected.png "Figure 3-2. CV52 Co Board with the HDMI / Ethernet / USB Cable Connected."
 *
 *   - For the universal asynchronous receiver / transmitter (UART) console window, the Co/Cr EVK
 *     board is equipped with a USB serial bridge.
 *   - Connect the EVK board to the host PC using a USB Mini A cable.
 *   - To ensure protection from elestrostatice discharge (ESD), connect the power cable to the
 *     EVK power jack on the board first, and then connect the cable to the power supply.
 * - - - -
 *
 * @section cv52_co_lpddr4x_system_io_hardware_control 4 System I/O and Hardware Control of CV52 EVK Co (LPDDR4x) Rev1.1
 *
 * @subsection cv52_co_lpddr4x_connectors  4.1 Connectors
 *
 * The figures below show all main I/O connectors on the top and bottom sides (respectively) of
 * the CV52 EVK Co (LPDDR4x) board.<br>
 *
 * @image html cv52_co_lpddr4x_major_io_connectors_on_top_side.png "Figure 4-1. Major I/O Connectors on the Top Side of the CV52 EVK Co (LPDDR4x) Board."
 *
 * @image html cv52_co_lpddr4x_major_io_connectors_on_bottom_side.png "Figure 4-2. Major I/O Connectors on the Bottom Side of the CV52 EVK Co (LPDDR4x) Board."
 *
 * Refer to the table below for a list of the main I/O connectors shown in the figures above.<br>
 *
 * <table>
 * <caption id="main_board_connectors">Table 4-1. Main board connectors.</caption>
 * <tr><th> Item <th> Designator <th> Functions <th> Notes
 * <tr><td align="cemter"> 1
 *     <td align="center"> SW19
 *     <td> Key button
 *     <td> Key button for the GPIO debug
 * <tr><td align="cemter"> 2
 *     <td align="center"> J106
 *     <td> Power measurement
 *     <td> 10x2,1.25-mm connector for power measurement
 * <tr><td align="cemter"> 3
 *     <td align="center"> J105
 *     <td> Power measurement
 *     <td> 15x2,1.25-mm connector for power measurement
 * <tr><td align="cemter"> 4
 *     <td align="center"> J50
 *     <td> Ethernet
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * <tr><td align="cemter"> 5
 *     <td align="center"> J47
 *     <td> Composite video broadcast signal (CVBS) output
 *     <td> Mono RCA jack
 * <tr><td align="cemter"> 6
 *     <td align="center"> U91
 *     <td> Infrared (IR) input
 *     <td> IR receiver
 * <tr><td align="cemter"> 7
 *     <td align="center"> J76
 *     <td> Controller area network (CAN) bus
 *     <td> 2x2, 2.54-mm connector for the CAN bus
 * <tr><td align="cemter"> 8
 *     <td align="center"> J37/J36
 *     <td> Peripheral component interconnected express (PCIe) x4
 *     <td> Standard PCIe x4 card edge connectors
 * <tr><td align="cemter"> 9
 *     <td align="center"> J69
 *     <td> Joint test action group (JTAG) connector
 *     <td> 10x2, 2.54-mm connector for JTAG
 * <tr><td align="cemter"> 10
 *     <td align="center"> SW6~SW9
 *     <td> Power on configuration (POC) switch
 *     <td> 2-SPST / 4-SPST / 8-SPST switches for POC setting
 * <tr><td align="cemter"> 11
 *     <td align="center"> BAT2
 *     <td> Real-time (RTC) battery holder
 *     <td> 2032 battery holder for the RTC
 * <tr><td align="cemter"> 12
 *     <td align="center"> J51
 *     <td> Ethernet1
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * <tr><td align="cemter"> 13
 *     <td align="center"> J72
 *     <td> MCU serial wire debug (SWD) connector
 *     <td> 5x2, 2.54-mm connector for the MCU debug tool
 * <tr><td align="cemter"> 14
 *     <td align="center"> J75
 *     <td> MCU reset button
 *     <td> Button to reset the MCU
 * <tr><td align="cemter"> 15
 *     <td align="center"> SW13
 *     <td> Reset button
 *     <td> Button to initiate system warm boot
 * <tr><td align="cemter"> 16
 *     <td align="center"> SW20
 *     <td> MCU power-on button
 *     <td> Button to indicate to the MCU to power-on the system
 * <tr><td align="cemter"> 17
 *     <td align="center"> SW23
 *     <td> Power on / OFF switch button
 *     <td> Button to make the system switch between the power-on and<br>
 *          power-off states when the external power sequencer is used
 * <tr><td align="cemter"> 18
 *     <td align="center"> J78
 *     <td> Power jack
 *     <td> 12-V system power adapter input, 2.5-mm
 * <tr><td align="cemter"> 19
 *     <td align="center"> J42
 *     <td> Audio line-in
 *     <td> 3.5-mm audio jack
 * <tr><td align="cemter"> 20
 *     <td align="center"> J59
 *     <td> Audio headphone (HP) out
 *     <td> 3.5-mm audio jack
 * <tr><td align="cemter"> 21
 *     <td align="center"> J55
 *     <td> Audio speaker out
 *     <td> 3.5-mm audio jack
 * <tr><td align="cemter"> 22
 *     <td align="center"> SW14~SW18
 *     <td> ADC1 key buttons
 *     <td> Key buttons in ADC1 to simulate menu / direction buttons
 * <tr><td align="cemter"> 23
 *     <td align="center"> J25
 *     <td> USB 2.0 device / serial debug port
 *     <td> Micro-B USB receptacle
 * <tr><td align="cemter"> 24
 *     <td align="center"> J29
 *     <td> USB 3.1 device
 *     <td> Micro-B USB 3.0 receptacle
 * <tr><td align="cemter"> 25
 *     <td align="center"> J31
 *     <td> USB 3.1 host
 *     <td> Type-A USB 3.0 receptacle
 * <tr><td align="cemter"> 26
 *     <td align="center"> J32
 *     <td> USB 3.1 hub host
 *     <td> Type-C USB 3.0 receptacle
 * <tr><td align="cemter"> 27
 *     <td align="center"> J33 / J34 / J35
 *     <td> USB 3.1 hub host
 *     <td> Type-A USB 3.0 receptacle
 * <tr><td align="cemter"> 28
 *     <td align="center"> J48 / J49
 *     <td> VOUT MIPI DSI A / B
 *     <td> 40-pin, 0.5-mm FPC connector for VOUT MIPI DSI
 * <tr><td align="cemter"> 29
 *     <td align="center"> J46
 *     <td> HDMI TX
 *     <td> Vertical HDMI receptacle
 * <tr><td align="cemter"> 30
 *     <td align="center"> SW1~SW5
 *     <td> PINMUX switch
 *     <td> 2-SPST / 4-SPST switches for PINMUX selection
 * <tr><td align="cemter"> 31
 *     <td align="center"> J43 / J44
 *     <td> VIN DCPHY
 *     <td> 41-pin, 0.5-mm connector for VIN DCPHY
 * <tr><td align="cemter"> 32
 *     <td align="center"> J39
 *     <td> VIN SLVS+DPHY
 *     <td> 164-pin PICe connector for VIN SLVS + DPHY
 * <tr><td align="cemter"> 33
 *     <td align="center"> J38
 *     <td> SSD hard drive
 *     <td> NVMe M2 connector
 * <tr><td align="cemter"> 34
 *     <td align="center"> J13
 *     <td> SDIO0
 *     <td> SD socket for SDIO0 I/F
 * <tr><td align="cemter"> 35
 *     <td align="center"> J19
 *     <td> SDIO1
 *     <td> Micro-SD socket for SDIO1 I/F
 * <tr><td align="cemter"> 36
 *     <td align="center"> BAT1
 *     <td> Lithium battery
 *     <td> 1.5-V lithium battery for RTC
 * </table>
 *
 * @subsection cv52_co_lpddr4x_system_io_configurations 4.2 System I/O Configurations
 *
 * The CV52 EVK board supplies abundant I/O interfaces for a variety of applications. Ensure
 * that the system I/O interfaces are properly configured with the on-board hardware jumpers
 * and switches.<br>
 *
 * The figure below provides the locations of the jumpers and switches listed in this chapter.<br>
 *
 * @image html cv52_co_lpddr4x_major_jumpers_system_io_config_on_top_side.png "Figure 4-3. Major Jumpers for the System I/O Configurations on the Top Side of the Cv52 EVK Co (LPDDR4x) Board."
 *
 * @subsubsection cv52_co_lpddr4x_gpio_debug 4.2.1 GPIO Debug
 *
 * SW19 is a key button for software GPIO debugging. SW19 is connected to GPIO138, which includes
 * a default pull-high hardware. The software can configure GPIO138 to verify the general
 * input / output function. Pressing SW19 will assert low to GPIO138.
 *
 *   - SW2.pin3 = ON: Connect GPIO138 to SW19
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_gpio138_debug.png "Figure 4-4. Jumpers and Switches for GPIO Debug (GPIO138)."
 *
 * @subsubsection cv52_co_lpddr4x_power_measurement 4.2.2 Power Measurement
 *
 * J105 and J106 are designed for power measurement. J105 and J106 have 30 / 20 pins and 1.25-mm
 * pitch connectors with a customized PIN-out. Contact the Ambarella support team for more details.<br>
 *
 * @subsubsection cv52_co_lpddr4x_ethernet 4.2.3 Ethernet
 *
 * The CV52 EVK board supports 1.8-V I/O between the media access control (MAC) and the PHY.<br>
 *
 * CV52 requires a 125-MHz reference clock if GMAC functions. The 125-MHz clock can be chosen
 * from the external oscillator or from GPHY. They can be chosen through switch SW30.<br>
 *
 *   - SW30 = OFF: Select 125-MHz clock from external oscillator
 *   - SW30 = ON: Select 125-MHz clock from GPHY
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_eth0_125mhz_clock.png "Figure 4-5. Jumpers and Switches for Ethernet 125-MHz Clock."
 *
 * Both GPHYs RTL8211 can supply the 125-MHz reference clock to the MAC. Use switch SW10 pin 1
 * to choose which is used.<br>
 *
 *   - SW10.pin1 = OFF: Select 125-MHz clock from GPHY RTL8211
 *   - SW10.pin1 = ON: Select 125-MHz clock from GPHY1 RTL8211
 *
 * J50 is a 10 / 100 / 1000 Base-T Ethernet single-port RJ45 connector with LEDs (link / act).
 * The CV52 ENET0 MAC supports the RGMII / RMII interfaces and the MDC / MDIO management interface
 * to the external Ethernet PHY.<br>
 *
 * Both Giga PHY RTL8211 and Mega PHY RTL8201 are assembled on the board. RTL8211 is connected
 * to CV52 through RGMII I/F, and RTL8201 is connected to CV52 through RMII I/F. Only one can
 * be used at a time. Use switch SW10 pin2 to choose which is used.<br>
 *
 *   - SW10.pin2 = OFF: Enable GPHY RTL8211
 *   - SW10.pin2 = ON: Enable MPHY RTL8201
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_eth0.png "Figure 4-6. Jumpers and Switches for Ethernet."
 *
 * @subsubsection cv52_co_lpddr4x_cvbs_output 4.2.4 CVBS Output
 *
 * J47 is a mono RCA jack for the CVBS output.<br>
 *
 * @subsubsection cv52_co_lpddr4x_ir_receiver 4.2.5 IR Receiver
 *
 * U91 is an IR receiver module for the infrared remote control systems with a 38-KHz
 * carrier frequency.<br>
 *
 * @subsubsection cv52_co_lpddr4x_can_bus 4.2.6 CAN Bus
 *
 * J76 is a 2x2, 2.54-mm connector for the CAN bus. J77 is a jumper that enables the CAN
 * transceiver. In normal mode, assemble the jumper on J77.<br>
 *
 *   - SW21 = OFF: Select CAN0
 *   - SW21 = ON: Select CAN1
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_can_bus.png "Figure 4-7. Jumpers and Switches for CAN."
 *
 * @subsubsection cv52_co_lpddr4x_pcie_x4 4.2.7 PCIe x4
 *
 * J36 and J37 are two standard, 64-pin PCIe x4 card edge connectors. The PCIe reference clock
 * is generated from the PCIe clock generator ― PI6CG18401, which can be configured through SW22.<br>
 *
 *   - SW22.pin1 = OFF: Disable the SS function
 *   - SW22.pin1 = ON: Enable the SS function at -0.5% spread
 *   - SW22.pin2 = OFF: Power on the PCIe clock generator
 *   - SW22.pin2 = ON: Power down the PCIe clock generator
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_pcie_x4.png "Figure 4-8. Jumpers and Switches for PCIe x4."
 *
 * @subsubsection cv52_co_lpddr4x_jtag_connector 4.2.8 JTAG Connector
 *
 * J60 is a 10x2, 2.54-mm connector for the JTAG debugging.<br>
 *
 * @subsubsection cv52_co_lpddr4x_poc_switch_sw6_sw9 4.2.9 POC Switch - SW6~SW9
 *
 * The table below shows the CV52 POC setup in SW6~SW9. Contact the Ambarella support team for
 * the POC user guide.<br>
 *
 * <table>
 * <caption id="cv52_evk_poc_setup">Table 4-2. CV52 EVK POC Setup.</caption>
 * <tr><th width="120px"> Designator <th width="85px"> Pins <th width="240px"> Notes
 * <tr><td align="center" rowspan="8"> SW6
 *     <td align="center"> pin A1
 *     <td> POC[21]=BOOT_OPTION[8]
 * <tr><td align="center"> pin A2
 *     <td> POC[1]=CLK_FRE[0]
 * <tr><td align="center"> pin A3
 *     <td> POC[2]=CLK_FRE[1]
 * <tr><td align="center"> pin A4
 *     <td> POC[3]=CLK_FRE[2]
 * <tr><td align="center"> pin A5
 *     <td> POC[8]=BOOT_BYPASS
 * <tr><td align="center"> pin A6
 *     <td> POC[30]=RESERVED
 * <tr><td align="center"> pin A7
 *     <td> POC[31]=SYSCONFIG_SRC
 * <tr><td align="center"> pin A8
 *     <td> POC[13]=BOOT_OPTION[0]
 * <tr><td align="center" rowspan="8"> SW7
 *     <td align="center"> pin A1
 *     <td> POC[16]=BOOT_OPTION[3]
 * <tr><td align="center"> pin A2
 *     <td> POC[17]=BOOT_OPTION[4]
 * <tr><td align="center"> pin A3
 *     <td> POC[18]=BOOT_OPTION[5]
 * <tr><td align="center"> pin A4
 *     <td> POC[19]=BOOT_OPTION[6]
 * <tr><td align="center"> pin A5
 *     <td> POC[20]=BOOT_OPTION[7]
 * <tr><td align="center"> pin A6
 *     <td> POC[4]=BOOT_MODE[0]
 * <tr><td align="center"> pin A7
 *     <td> POC[5]=BOOT_MODE[1]
 * <tr><td align="center"> pin A8
 *     <td> POC[6]=SECURE_BOOT
 * <tr><td align="center" rowspan="2"> SW8
 *     <td align="center"> pin A1
 *     <td> POC[14]=BOOT_OPTION[1]
 * <tr><td align="center"> pin A2
 *     <td> POC[15]=BOOT_OPTION[2]
 * <tr><td align="center"> SW9
 *     <td align="center"> pin A1
 *     <td> POC[10]=FORCE_USB_BOOT
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_poc_sw6_sw9.png "Figure 4-9. Jumpers and Switches for POC."
 *
 * @subsubsection cv52_co_lpddr4x_rtc_battery_holder 4.2.10 RTC Battery Holder
 *
 * BAT2 is a 2032 battery holder for the CV52 RTC block. By default, the battery is not assembled.
 * Ensure correct battery polarity during assembly.<br>
 *
 * @subsubsection cv52_co_lpddr4x_ethernet_1 4.2.11 Ethernet 1
 *
 * J51 is a 10 / 100 / 1000 Base-T Ethernet single port RJ45 connector with LEDs (link / act).
 * The CV52 ENET1 MAC supports the RGMII / RMII interfaces and the MDC / MDIO management
 * interface to the external Ethernet PHY.<br>
 *
 * Both Giga PHY RTL8211 and Mega PHY RTL8201 are assembled on the board. RTL8211 is connected
 * to the CV52 through RGMII I/F, and RTL8201 is connected to the CV52 through RMII I/F. Only
 * one can be used at a time.  Use switch SW11 to choose which is used.<br>
 *
 *   - SW11 = OFF: Enable GPHY RTL8211
 *   - SW11 = ON: Enable MPHY RTL8201
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_ethernet_1.png "Figure 4-10. Jumpers and Switches for Ethernet 1."
 *
 * @subsubsection cv52_co_lpddr4x_mcu_swd_connector 4.2.12 MCU SWD Connector
 *
 * J72 is a 5x2, 2.54-mm connector for the MCU debug tool. It supports only a 2-pin SWD function.<br>
 *
 * @subsubsection cv52_co_lpddr4x_mcu_reset_button 4.2.13 MCU Reset Button
 *
 * J75 is the MCU reset button, which triggers an active-low signal to assert a hardware reset
 * to the MCU.<br>
 *
 * @subsubsection cv52_co_lpddr4x_reset_button 4.2.14 Reset Button
 *
 * SW13 functions as the system reset button, which triggers an active-low signal to assert a
 * system reset to CV52 POR pin.<br>
 *
 * @subsubsection cv52_co_lpddr4x_mcu_power_on_button 4.2.15 MCU Power-on Button
 *
 * SW20 functions as a power-on button, which triggers an active-low signal to indicate a
 * power-on action to the MCU.  Ensure that the software has enabled this function in the MCU.<br>
 *
 * @subsubsection cv52_co_lpddr4x_power_on_off_switch_button 4.2.16 Power ON / OFF Switch Button
 *
 * SW23 functions as a system power ON / OFF switch button. Pressing SW23 powers on the system
 * if the system is in the OFF state, or power off the system if the system is in the ON state.
 * Do not assemble a jumper on J79.  If there is a jumper on J79, it will bypass SW23.<br>
 *
 * @subsubsection cv52_co_lpddr4x_power_jack 4.2.17 Power Jack
 *
 * J78 is a standard 2.5-mm power jack for an external 12-V power adapter. Plugging the power
 * adapter through J78 supplies the power for the CV52 EVK board.<br>
 *
 * @subsubsection cv52_co_lpddr4x_audio_line_in 4.2.18 Audio Line-in
 *
 * The on-board audio codec / decoder (CODEC) is NAU88C22.<br>
 * The CV52 CLK_AU signal could be chosen to output to NAU88C22 or to the external audio codec
 * through SW12.<br>
 *
 *   - Assemble the jumpers on J52 and J54
 *   - SW12 = OFF: Connect to NAU88C22
 *   - SW12 = ON: Connect to the external audio codec
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_clk_au_to_audio_codec.png "Figure 4-11. Jumpers and Switches for CLK_AU to Audio Codec."
 *
 * The audio line-in is available in J42, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv52_co_lpddr4x_audio_hp_out 4.2.19 Audio HP out
 *
 * The audio HP out is available in J59, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv52_co_lpddr4x_audio_speaker_out 4.2.20 Audio Speaker Out
 *
 * The audio speaker out is available in J55, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv52_co_lpddr4x_adc1_key_button 4.2.21 ADC1 Key Buttons
 *
 * SW14~SW18 are key buttons to simulate menu / direction buttons. Ensure that the software has
 * this function enabled in ADC1.<br>
 *
 * @subsubsection cv52_co_lpddr4x_usb_20_device_serial_debug_port 4.2.22 USB2.0 Device / Serial Debug Port
 *
 * J25 is a Micro-B USB receptacle. USB0 I/F functions in device mode only. Plug the USB cable
 * from the USB host to J25. The AmbaUSB tool functions in this mode. It also serves as a serial
 * debug port because a USB-to-UART chip is used to perform the interface conversion.<br>
 *
 * @subsubsection cv52_co_lpddr4x_usb_31_device 4.2.23 USB3.1 Device
 *
 * J29 is a Micro-B USB3.1 receptacle. When USB1 I/F is in device mode, plug the USB host to J29.<br>
 *
 *   - Jumper on J28 must be assembled
 *
 * @subsubsection cv52_co_lpddr4x_usb_31_host 4.2.24 USB3.1 Host
 *
 * J31 is a Type-A USB 3.1 receptacle.  When USB1 I/F is in host mode, plug the USB device to J31.<br>
 *
 *   - Jumper on J28 must not be assembled
 *   - Jumper on J30 must be assembled
 *
 * @subsubsection cv52_co_lpddr4x_usb_31_hub_host 4.2.25 USB 3.1 Hub Host
 *
 * J32 is a Type-C USB 3.1 receptacle, and J33~J35 are Type-A USB 3.1 receptacles from the on-board
 * USB3.1 hub. When USB1 I/F functions in host mode and is connected through the USB3.1 hub,
 * J32~J36 will be available.<br>
 *
 *   - Jumper on J28 must not be assembled
 *   - Jumper on J30 must not be assembled
 *
 * @subsubsection cv52_co_lpddr4x_vout_mipi_dsi 4.2.26 VOUT MIPI DSI
 *
 * J48 and J49 are two 20x2, 0.5-mm FFC / FPC connectors for the MIPI DSI A and B output. They
 * are customized pin-out connectors. Check the reference design for more details.<br>
 *
 * @subsubsection cv52_co_lpddr4x_hdmi_tx 4.2.27 HDMI TX
 *
 * J46 is a standard vertical 19-pin HDMI receptacle for HDMI transmit (TX). Assemble the jumper on J45
 * to enable 5-V power on J46.
 *
 * @subsubsection cv52_co_lpddr4x_pinmux_switch_sw1_sw5 4.2.28 PINMUX Switch – SW1~SW5
 *
 * SW1, SW2, and SW4 are 4-single pole single throw (SPST) switches, while SW3 and SW5 are 2-SPST
 * switches used for PINMUX selection.<br>
 *
 * The table below shows a summary of the PINMUX switches. Refer to each sector for details.<br>
 *
 * <table>
 * <caption id="cv52_evk_mux_configurations">Table 4-3. CV52 EVK Mux Configurations.</caption>
 * <tr><th> Switch <th> Pin <th> Status <th> Function <th> Description
 * <tr><td align="center" rowspan="26"> SW1
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO65 as VSDELAY_HSYNC_OUT_0
 *     <td> HSYNC0 to VIN / DCPHY1 connector
 * <tr><td> GPIO66 as VSDELAY_HSYNC_OUT_1
 *     <td> HSYNC1 to SLVC-EC / DCPHY0 connector
 * <tr><td> GPIO67 as EXT_HSYNC_SRC_INPUT
 *     <td> HSYNC source input
 * <tr><td> GPIO68 as EXT_VSYNC_SRC_INPUT
 *     <td> VSYNC source input
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO65 as GPIO65
 *     <td> GPIO
 * <tr><td> GPIO66 as GPIO66
 *     <td> GPIO
 * <tr><td> GPIO67 as DMIC_CLK
 *     <td> DMIC clock
 * <tr><td> GPIO68 as DMIC_DAT
 *     <td> DMIC data
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO69 as SSI1_SCLK
 *     <td> SS1 clock
 * <tr><td> GPIO70 as SSI1_TXD
 *     <td> SSI1 TX Data
 * <tr><td> GPIO71 as SSI1_RXD
 *     <td> SSI1 RX Data
 * <tr><td> GPIO72 as SSI1_EN0
 *     <td> SSI1 to Gyro
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO69 as GPIO69
 *     <td> GPIO69 to VIN
 * <tr><td> GPIO70 as GPIO70
 *     <td> GPIO70 to VIN
 * <tr><td> GPIO71 as GPIO71
 *     <td> GPIO71 to VIN
 * <tr><td> GPIO72 as GPIO72
 *     <td> GPIO72 to VIN
  * <tr><td align="center" rowspan="6"> Pin3
 *     <td align="center" rowspan="3"> OFF
 *     <td> GPIO73 as SSI1_EN1
 *     <td> SSI1 to MIPI_DSI_A connector
 * <tr><td> GPIO74 as SSI1_EN2
 *     <td> SSI1 to MIPI_DSI_B connector
 * <tr><td> GPIO75 as SSI1_EN3
 *     <td> SSI1 to debug connector
 * <tr><td align="center" rowspan="3"> ON
 *     <td> GPIO73 as GPIO73
 *     <td> GPIO73 to VIN
 * <tr><td> GPIO74 as GPIO74
 *     <td> GPIO74 to VIN
 * <tr><td> GPIO75 as GPIO75
 *     <td> GPIO75 to VIN
 * <tr><td align="center" rowspan="4"> Pin4
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO76 as GPIO76
 *     <td> GPIO76 to VIN
 * <tr><td> GPIO77 as GPIO77
 *     <td> GPIO77 to VIN
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO76 as IDCSCLK
 *     <td> IDCS clock
 * <tr><td> GPIO77 as IDCSDATA
 *     <td> IDCS data
 * <tr><td align="center" rowspan="28"> SW2
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO92 as SDIO0_D[0]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO93 as SDIO0_D[1]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO94 as SDIO0_D[2]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO95 as SDIO0_D[3]
 *     <td> SDIO0 for SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO92 as VSDELAY_VSYNC_OUT_0
 *     <td> VSYNC0 to VIN
 * <tr><td> GPIO93 as VSDELAY_VSYNC_OUT_1
 *     <td> VSYNC1 to SLVS-EC
 * <tr><td> GPIO94 as VSDELAY_VSYNC_OUT_2
 *     <td> VSYNC2 to DCPHY0
 * <tr><td> GPIO95 as VSDELAY_VSYNC_OUT_3
 *     <td> VSYNC3 to DCPHY1
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO96 as SDIO0_CLK
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO97 as SDIO0_CMD
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO98 as SDIO0_CD
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO99 as SDIO0_WP
 *     <td> SDIO0 for SD socket
  * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO96 as IDC1CLK
 *     <td> IDC1 to DCPHY1 / MIPI_DSI_A connector
 * <tr><td> GPIO97 as IDC1DATA
 *     <td> IDC1 to DCPHY1 / MIPI_DSI_A connector
 * <tr><td> GPIO98 as GPIO98
 *     <td> GPIO
 * <tr><td> GPIO99 as GPIO99
 *     <td> GPIO
 * <tr><td align="center" rowspan="4"> Pin3
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO100 as GPIO100
 *     <td> SDIO0 PWRON for SD socket
 * <tr><td> GPIO138 as SDIO0_HS_SEL
 *     <td> SDIO0_HS_SEL
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO100 as GPIO100
 *     <td> Reset to DCPHY1 connector
 * <tr><td> GPIO138 as GPIO138
 *     <td> GPIO
 * <tr><td align="center" rowspan="8"> Pin4
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO101 as SDIO1_D[0]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO102 as SDIO1_D[1]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO103 as SDIO1_D[2]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO104 as SDIO1_D[3]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO101 as SSI3_RXD
 *     <td> SSI3 RX data
 * <tr><td> GPIO102 as SSI3_TXD
 *     <td> SSI3 TX data
 * <tr><td> GPIO103 as SSI3_SCLK
 *     <td> SSI3 clock
 * <tr><td> GPIO104 as SSI3_EN0
 *     <td> SSI3 to DCPHY1 / SLVS-EC connector
 * <tr><td align="center" rowspan="12"> SW3
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO105 as SDIO1_CLK
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO106 as SDIO1_CMD
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO107 as SDIO1_CD
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO108 as SDIO1_WP
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO105 as GPIO105
 *     <td> GPIO105 to DCPHY0 / SLVS-EC
 * <tr><td> GPIO106 as GPIO106
 *     <td> GPIO106 to DCPHY0
 * <tr><td> GPIO107 as IDC5CLK
 *     <td> IDC5 to DCPHY1 / SLVS-EC connector
 * <tr><td> GPIO108 as IDC5DATA
 *     <td> IDC5 to DCPHY1 / SLVS-EC connector
 * <tr><td align="center" rowspan="4"> Pin2
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO109 as GPIO109
 *     <td> SDIO1 PWRON for the Micro-SD socket
 * <tr><td> GPIO132 as SDIO1_HS_SEL
 *     <td> SDIO1_HS_SEL
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO109 as GPIO109
 *     <td> GPIO109 as reset to DCPHY0 / SLVS-EC connector
 * <tr><td> GPIO132 as GPIO132
 *     <td> GPIO132 as FLASH debug
 * <tr><td align="center" rowspan="26"> SW4
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO133 as I2S1_CLK or UART2_AHB_RX
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO134 as I2S1_SI_0 or UART2_AHB_TX
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO135 as I2S1_SO_0 or UART2_AHB_CTS_N
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO136 as I2S1_WS or UART2_AHB_RTS_N
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO133 as SSI4_SCLK
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO134 as SSI4_TXD
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO135 as SSI4_RXD
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO136 as SSI4_EN0
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td align="center" rowspan="2"> Pin2
 *     <td align="center"> OFF
 *     <td> GPIO0 as IR_IN
 *     <td> IR receiver (Input)
 * <tr><td align="center"> ON
 *     <td> GPIO0 as WDT_EXT_RST_L
 *     <td> WDTn
 * <tr><td align="center" rowspan="8"> Pin3
 *     <td aling="center" rowspan="4"> OFF
 *     <td> GPIO119 as GPIO119
 *     <td> GPIO
 * <tr><td> GPIO120 as GPIO120
 *     <td> GPIO
 * <tr><td> GPIO121 as GPIO121
 *     <td> GPIO
 * <tr><td> GPIO122 as GPIO122
 *     <td> GPIO
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO119 as USB32C_OVERCURRENT
 *     <td> USB32_Over_Current
 * <tr><td> GPIO120 as USB32C_DRIVE_VBUS
 *     <td> USB32_PWRON
 * <tr><td> GPIO121 as PWM10
 *     <td> PWM10
 * <tr><td> GPIO122 as PWM11
 *     <td> PWM11
 * <tr><td align="center" rowspan="8"> Pin4
 *     <td aling="center" rowspan="4"> OFF
 *     <td> GPIO123 as GPIO123
 *     <td> GPIO123 to MIPI_DSI_A
 * <tr><td> GPIO124 as GPIO124
 *     <td> GPIO124 to MIPI_DSI_A
 * <tr><td> GPIO125 as GPIO125
 *     <td> GPIO125 to MIPI_DSI_A
 * <tr><td> GPIO126 as GPIO126
 *     <td> GPIO126 to MIPI_DSI_A
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO123 as UART1_AHB_RX
 *     <td> UART1
 * <tr><td> GPIO124 as UART1_AHB_TX
 *     <td> UART1
 * <tr><td> GPIO125 as UART1_AHB_CTS_N
 *     <td> UART1
 * <tr><td> GPIO126 as UART1_AHB_RTS_N
 *     <td> UART1
 * <tr><td align="center" rowspan="16"> SW5
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO127 as GPIO127
 *     <td> GPIO127 to MIPI_DSI_B
 * <tr><td> GPIO128 as GPIO128
 *     <td> GPIO128 to MIPI_DSI_B
 * <tr><td> GPIO129 as GPIO129
 *     <td> GPIO129 to MIPI_DSI_B
 * <tr><td> GPIO130 as GPIO130
 *     <td> GPIO130 to MIPI_DSI_B
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO127 as CAN0_RX
 *     <td> CAN0
 * <tr><td> GPIO128 as CAN0_TX
 *     <td> CAN0
 * <tr><td> GPIO129 as CAN1_RX
 *     <td> CAN1
 * <tr><td> GPIO130 as CAN1_TX
 *     <td> CAN1
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO106 as IDC4CLK
 *     <td> IDC4 for VIN / external RTC
 * <tr><td> GPIO107 as IDC4DATA
 *     <td> IDC4 for VIN / external RTC
 * <tr><td> GPIO108 as IDC3CLK
 *     <td> IDC3 for VIN / EXGPIO
 * <tr><td> GPIO109 as IDC3DATA
 *     <td> IDC3 for VIN / EXGPIO
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO106 as SSI2_SCLK
 *     <td> SSI2 in debug header
 * <tr><td> GPIO107 as SSI2_TXD
 *     <td> SSI2 in debug header
 * <tr><td> GPIO108 as SSI2_RXD
 *     <td> SSI2 in debug header
 * <tr><td> GPIO109 as SSI2_EN0
 *     <td> SSI2 in debug header
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_sw1_sw5.png "Figure 4-12. Jumpers and Switches for SW1~SW5."
 *
 * @subsubsection cv52_co_lpddr4x_poc_table 4.2.29 CV52 POC Table
 *
 * <table>
 * <caption id="cv52_co_evk_poc_table">Table 4-4. CV52 POC Table.</caption>
 * <tr><th> POC bit <th> PIN Name <th colspan="5"> Description <th> EVK Default
 * <tr><td> POC[3:1]
 *     <td> ENET_TXD[3:1]
 *     <td colspan = "5"> IDSP/CORE/DDR Clock config <br>
 *          VDSP/IDSP/VISION/CORTEX/NAND(contact for below frequency setting) <br>
 *          000:  912 / 1104 / 1104 / 1584 / 528 Mhz <br>
 *          001: 1200 / 1200 / 1392 / 1800 / 528 Mhz <br>
 *          010:  504 /  600 /  600 /  816 / 264 Mhz <br>
 *          011:  960 / 1056 / 1056 / 1536 / 528 Mhz <br>
 *          100: 1056 / 1152 / 1152 / 1632 / 528 Mhz <br>
 *          101: 1008 / 1056 / 1056 / 1584 / 528 Mhz <br>
 *          110:  504 /  600 /  600 /  816 / 360 Mhz <br>
 *          111:  432 /  432 /  432 /  432 / 264 Mhz
 *     <td> 111
 * <tr><td> POC[5:4]
 *     <td> ENET1_TXD[1:0]
 *     <td  colspan = "5"> Boot Mode [1:0] <br>
 *          00: SPINOR <br>
 *          01: NAND (include SPI NAND) <br>
 *          10: eMMC <br>
 *          11: PCIe
 *     <td> 01
 * <tr><td> POC[6]
 *     <td> ENET1_TXD[2]
 *     <td  colspan = "5"> Secure boot: <br>
 *          0: Clear boot <br>
 *          1: Secure boot
 *     <td> 0
 * <tr><td> POC[8]
 *     <td> CLK_AU[8]
 *     <td  colspan = "5"> Boot Bypass: <br>
 *          0: disable <br>
 *          1: enable
 *     <td> 0
 * <tr><td> POC[10]
 *     <td> ENET_PTP_PPS
 *     <td  colspan = "5"> Force USB boot: <br>
 *          0: disable <br>
 *          1: enable
 *     <td> 0
 * <tr><td rowspan = "2"> [21:13]
 *     <td>
 *     <td colspan = "5"> Boot Options[8:0]
 *     <td>
 * <tr><td>
 *     <td> <b> Boot Option </b>
 *     <td> <b> SPI-NOR </b>
 *     <td> <b> NAND </b>
 *     <td> <b> eMMC </b>
 *     <td> <b> PCIe </b>
 *     <td>
 * <tr><td> POC[21]
 *     <td> ENET_GTX_CLK
 *     <td> boot_option[8]
 *     <td>
 *     <td>
 *     <td> <b> eMMC boot controller sel </b> <br>
 *          1: Legancy SD
 *     <td>
 *     <td>
 * <tr><td> POC[20]
 *     <td> SHSYNC
 *     <td> boot_option[7]
 *     <td>
 *     <td> <b> 8K BST code size Select </b> <br>
 *          0: 4K BST code size <br>
 *          1: 8K BST code size
 *     <td> <b> eMMC bst 8k </b> <br>
 *          0: 4K BST code size <br>
 *          1: 8K BST code size
 *     <td>
 *     <td> 1
 * <tr><td> POC[19]
 *     <td> SVSYNC
 *     <td> boot_option[6]
 *     <td>
 *     <td>
 *     <td> <b> tRSCA sel boot </b> <br>
 *          0: For tRSCA=75 SD clock cycles <br>
 *          1: For tRSCA=10000 SD clock cycles
 *     <td>
 *     <td>
 * <tr><td> POC[18]
 *     <td> PWM0
 *     <td> boot_option[5]
 *     <td>
 *     <td> <b> SCK Mode </b> <br>
 *          0: Mode 0 (CPOL = 0. CPHA = 0) <br>
 *          1: Mode 3 (CPOL = 1. CPHA = 1) <br>
 *     <td> <b> tRSCA </b> <br>
 *          Set this value to 1 to delay the timing of boot initialization
 *     <td>
 *     <td> 0
 * <tr><td> POC[17]
 *     <td> ENET1_PTP_PPS
 *     <td> boot_option[4]
 *     <td>
 *     <td> <b> 4K/2K Page Select </b> <br>
 *          0: 4K-page <br>
 *          1: 2K-page
 *     <td> <b> eMMC reset for SW Boot </b> <br>
 *          When eMMC boot = 1, mmc_boot_sel = 1 and emmc_reset_default_on = 1.
 *          Legacy SD controller will drive sdio1_reset signal through pad sd_reset.
 *     <td> Ref24
 *     <td> 1
 * <tr><td> POC[16]
 *     <td> I2S_SO_0
 *     <td> boot_option[3]
 *     <td> <b> SPI Mode Selection </b> <br>
 *          0: SPI mode 0 <br>
 *          1: SPI mode 1
 *     <td> <b> Skip ECC check for Blank </b> <br>
 *          0: Do not skip ECC check for blank pages <br>
 *          1: Skip ECC check for blank pages
 *     <td> <b> eMMC boot sd pull </b> <br>
 *          When 0: No pull on sd_cmd and sd_d[7:0] <br>
 *          When 1: Interal pull high on sd_cmd and sd_d[7:0]
 *     <td> DDR5
 *     <td> 1
 * <tr><td> POC[15]
 *     <td> UART_APB_TX
 *     <td> boot_option[2]
 *     <td> <b> Boot Mode[2] </b> <br>
 *          Take reference to table: @ref cv52_boot_mode_table
 *     <td> <b> NAND ECC BCH Enable </b> <br>
 *          Enable ECC BCH function or not
 *     <td> <b> 4-bit Bus Width </b> <br>
 *          Use 4 SD data pins for boot
 *     <td> Gen
 *     <td> 0
 * <tr><td> POC[14]
 *     <td> UART1_AHB_TX
 *     <td> boot_option[1]
 *     <td> <b> Boot Mode[1] </b> <br>
 *          Take reference to table: @ref cv52_boot_mode_table
 *     <td> <b> NAND Spare Cell 2x </b> <br>
 *          0: Support 1X NAND spare area <br>
 *             When NAND page size if 0: Spare area = 128 B <br>
 *             When NAND page size if 1: Spare area =  64 B <br>
 *          1: Support 2X NAND spare area <br>
 *             When NAND page size if 0: Spare area = 256 B <br>
 *             When NAND page size if 1: Spare area = 128 B
 *     <td> <b> 8-bit Bus Width </b> <br>
 *          Use 8 SD data pins for boot
 *     <td rowspan="2"> sub-mode[1:0]
 *     <td> 1
 * <tr><td> POC[13]
 *     <td> UART0_AHB_TX
 *     <td> boot_option[0]
 *     <td> <b> Boot Mode[0] </b> <br>
 *          Take reference to table: @ref cv52_boot_mode_table
 *     <td> <b> Flash Fast Boot </b> <br>
 *          0: Normal NAND flash component read cycle time <br>
 *          1: Shorter NAND flash component read cycle time
 *     <td> <b> hs boot </b> <br>
 *          0: Default-Speed Mode (12.5 MB/sec interface speed related for sd4_boot or 25 MB/sec interface speed for sd8_boot) <br>
 *          1: High-Speed Mode (25 MB/sec interface speed for sd4_boot, 50 MB/sec interface speed for sd8_boot)
 *     <td> 0
 * <tr bgcolor="#00FFFF"><td> POC[30]
 *     <td> I2S_WS
 *     <td  colspan = "5"> Reserved (Set to 0)
 *     <td>
 * <tr><td> POC[31]
 *     <td> PWM1
 *     <td  colspan = "5"> Source of sys config data: <br>
 *          0: config data is set by pins <br>
 *          1: config data is read from on-chip efuse rom
 *     <td> 1
 * </table>
 *
 * <table>
 * <caption id="cv52_boot_mode_table"> Boot Modes of SPI NOR </caption>
 * <tr><th> Boot Option <th colspan="6"> Description <th> POC Pin
 * <tr><td rowspan="7"> Boot mode
 *     <td colspan="6"> Initial boot mode
 *     <td rowspan="7"> 15:13
 * <tr><td> <b> Boot Mode </b>
 *     <td> <b> Target Device </b>
 *     <td> <b> Interface </b>
 *     <td> <b> Address #Bytes </b>
 *     <td> <b> Read Command </b>
 *     <td> <b> Reset Command </b>
 * <tr><td> 0
 *     <td> Generic Device
 *     <td> Extended SPI (a)
 *     <td> 3
 *     <td> 0x03
 *     <td> 0x66-0x99 (b)
 * <tr><td> 1
 *     <td> Generic Device
 *     <td> Extended SPI
 *     <td> 3
 *     <td> 0x03
 *     <td> 0xFF-0xF0 (c)
 * <tr><td> 2
 *     <td> Micron
 *     <td> Octave-IO, A/D DDR (d), Dummy Length 16
 *     <td> 4
 *     <td> 0x8B
 *     <td> 0x66-0x99
 * <tr><td> 3-7
 *     <td> (Reserved)
 *     <td>
 *     <td>
 *     <td>
 *     <td>
 * <tr><td colspan="6"> <b> Note </b> <br>
 *     (a) SPI transmission bit order for all modes is MSB first. <br>
 *     (b) MICRON / MXIC / GigaDevice. Reset enable (0x66) followed by reset command (0x99). <br>
 *     (c) Spansion. Mode bit reset (MBR; 0xFF) followed by reset command (0xF0) <br>
 *     (d) A/D DDR -- Double samples per clock on address / data stage.
 * </table>
 *
 * @subsubsection cv52_co_lpddr4x_vin_dcphy 4.2.30 VIN DCPHY
 *
 * J43 and J44 are two 41-pin, 0.5-mm pitch, 3.8-mm height connectors for the VIN DCPHY I/Fs.
 * They are customized pin-out connectors. Check the reference design for details.<br>
 *
 * @subsubsection cv52_co_lpddr4x_vin_slvs_dcphy 4.2.31 VIN SLVS+DPHY
 *
 * J39 is a standard 164-pin, PCIe connector for the VIN SLVS+DPHY. J39 is a customized pin-out
 * connector. Check the reference design for details.<br>
 *
 * @subsubsection cv52_co_lpddr4x_nvme_m2_connector 4.2.32 NVMe M.2 Connector
 *
 * J38 is a standard NVMe M.2 connector for the PCIe-based SSD hard drive.<br>
 *
 * @subsubsection cv52_co_lpddr4x_sdio0 4.2.33 SDIO0
 *
 * SDIO0 is available in J13, which is an SD socket on the bottom side.
 *
 *   - SW2.pin1 / 2 / 3 = LOW: SDIO0 is connected to the J13 socket shown in the figure below
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_sdio0_sw2.png "Figure 4-13. Jumpers and Switches for SDIO0."
 *
 * J14 is used to control the J13 VDD (3.3 V).<br>
 *
 *   - J14 pin2-3 ON: Enable software control on the VDD
 *   - J14 pin1-2 ON: Make the VDD always-on
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_sdio0_j14.png "Figure 4-14. Jumpers and Switches for J14."
 *
 * When an SD memory card is used in J13:<br>
 *
 *   - Jumper on J16 must be assembled
 *   - Jumper on J18 must not be assembled
 *
 * When an SD I/O card is used in J13:<br>
 *
 *   - Jumper on J16 must not be assembled
 *   - Jumper on J18 must be assembled to select SDIO0 I/O voltage
 *     - J18.pin1-2: SDIO0_VDDO = 1.8 V
 *     - J18.pin2-3: SDIO0_VDDO = 3.3 V
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_sdio0_j16_j18.png "Figure 4-15. Jumpers and Switches for SDIO."
 *
 * @subsubsection cv52_co_lpddr4x_sdio1 4.2.34 SDIO1
 *
 * SDIO1 is available in J19, which is a micro-SD socket on the bottom side.<br>
 *
 *   - SW2.pin4 = LOW and SW3.pin1/2 = LOW: SDIO1 is connected to the J19 socket
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_sdio1_sw23.png "Figure 4-16. Jumpers and Switches for SDIO1."
 *
 * J20 is used to control the J19 VDD (3.3 V).<br>
 *
 *   - J20 pin2-3 ON: Enable software control on the VDD
 *   - J20 pin1-2 ON: Make the VDD always-on
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_sdio1_j20.png "Figure 4-17. Jumpers and Switches for J20."
 *
 * When an SD memory card is used in J19:<br>
 *
 *   - Jumper on J22 must be assembled
 *   - Jumper on J24 must not be assembled
 *
 * When an SD I/O card is used in J19:
 *
 *   - Jumper on J22 must not be assembled
 *   - Jumper on J24 must be assembled to select SDIO0 I/O voltage
 *     - J24.pin1-2: SDIO1_VDDO = 1.8 V
 *     - J24.pin2-3: SDIO1_VDDO = 3.3 V
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_sdio1_j22_j24.png "Figure 4-18. Jumpers and Switches for J22 and J24."
 *
 * @subsubsection cv52_co_lpddr4x_emmc 4.2.35 eMMC
 *
 * The on-board embedded multi-media controller (eMMC) is connected to the CV52 SD interface as a boot source.<br>
 * J7 is used to select eMMC VCC and J8 is used to select eMMC VCCQ.<br>
 * This table provides the eMMC VCC and eMMC VCCQ configuration by J7 and J8.<br>
 *
 * <table>
 * <caption id="emmc_vcc_vccq_config">Table 4-5. eMMC VCC and eMMC VCCQ (CV52 SD_VDDO) Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Power Rail <th width="165px"> Jumpers <th width="200px"> Power Rail Value (V)
 * <tr><td align="center" rowspan="2"> J7
 *     <td align="center" rowspan="2"> eMMC VCC
 *     <td align="center"> 1-2
 *     <td align="center"> 1.8 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> 3.3 V (Default)
 * <tr><td align="center" rowspan="2"> J8
 *     <td align="center" rowspan="2"> eMMC VCCQ <br>
 *                                     (CV52 SD_VDDO)
 *     <td align="center"> 1-2
 *     <td align="center"> 1.8 V (Default)
 * <tr><td align="center"> 2-3
 *     <td align="center"> 3.3 V
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_emmc_vcc_vccq.png "Figure 4-19. Jumpers and Switches for eMMC VCC and eMMC VCCQ."
 *
 * @subsubsection cv52_co_lpddr4x_lithium_battery 4.2.36 Lithium Battery
 *
 * BAT1 is a 1.5-V lithium battery for the CV52 RTC block. By default, the battery is not assembled.
 * Ensure correct battery polarity during assembly.<br>
 *
 * @subsubsection cv52_co_lpddr4x_power_jumpers 4.2.37 Power Jumpers
 *
 * J97 is used to adjust the VDD. The following table provides the VDD configuration via J97.<br>
 *
 * <table>
 * <caption id="cv52_vdd_configuration">Table 4-6. CV52 VDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Jumpers <th width="200px"> VDD Value (V)
 * <tr><td align="center" rowspan="4"> J97
 *     <td align="center"> 1-3
 *     <td align="center"> 0V7
 * <tr><td align="center"> 3-5
 *     <td align="center"> 0V75 (Default)
 * <tr><td align="center"> 4-6
 *     <td align="center"> 0V8
 * <tr><td align="center"> 2-4
 *     <td align="center"> 0V85
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_cv52_vdd.png "Figure 4-20. Jumpers and Switches for CV52 VDD."
 *
 * @note
 *   - Do not adjust the VDD voltage when the board is powered on so as to avoid permanently
 *     damaging the CV52 chipset.
 *
 * SW27 is used to adjust the VDDA. This table provides the VDDA configuration by SW27.<br>
 *
 * <table>
 * <caption id="cv52_vdda_configuration">Table 4-7. CV52 VDDA Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> VDDA Value (V)
 * <tr><td align="center" rowspan="2"> SW27
 *     <td align="center"> ON
 *     <td align="center"> 0V8 (Default)
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V825
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_cv52_vdda.png "Figure 4-21. Jumpers and Switches for CV52 VDDA."
 *
 * SW28 is used to select PCIE_AVDD. This table provides the PCIE_AVDD configuration by SW28.<br>
 *
 * <table>
 * <caption id="cv52_pcie_avdd_configuration">Table 4-8. CV52 PCIE_AVDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> PCIE_AVDD Value(V)
 * <tr><td align="center" rowspan="2"> SW28
 *     <td align="center"> ON
 *     <td align="center"> 0V8
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V85 (Deafult)
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_pcie_avdd.png "Figure 4-22. Jumpers and Switches for PCIE_AVDD."
 *
 * SW29 is used to select DCPHY_AVDD. This table provides the DCPHY_AVDD configuration by SW29.<br>
 *
 * <table>
 * <caption id="cv52_dcphy_avdd_configuration">Table 4-9. CV52 DCPHY_AVDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> PCIE_AVDD Value(V)
 * <tr><td align="center" rowspan="2"> SW29
 *     <td align="center"> ON
 *     <td align="center"> 0V8
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V85 (Deafult)
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_dcphy_avdd.png "Figure 4-23. Jumpers and Switches for DCPHY_AVDD."
 *
 * J112 and J113 are used to select the power enablement of PWR_CVSYS_5V and PWR_CVSYS_3V3. This
 * table provides the PWR_CVSYS_5V and PWR_CVSYS_3V3 configuration by J112 and J113.<br>
 *
 * <table>
 * <caption id="cv52_power_5v_33v_configuration">Table 4-10. CV52 PWR_CVSYS_5V and PWR_CVSYS_3V3 Power Enable Source Configuation.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Power Rail <th width="165px"> Jumpers <th width="200px"> Power Enable Source
 * <tr><td align="center" rowspan="2"> J112
 *     <td align="center" rowspan="2"> PWR_CVSYS_5V
 *     <td align="center"> 1-2
 *     <td align="center"> 12 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> PWR_PSEQ1 (Default)
 * <tr><td align="center" rowspan="2"> J113
 *     <td align="center" rowspan="2"> PWR_CVSYS_3V3
 *     <td align="center"> 1-2
 *     <td align="center"> 12 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> PWR_PSEQ1 (Default)
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_cv52_power_enable_source.png "Figure 4-24. Jumpers and Switches for CV52 PWR_CVSYS_5V and PWR_CVSYS_3V3 Power Enable Source."
 *
 * J102 and J103 are used to select the power enablement of peripheral 1V8 / 3V3 /5V / 12V. The
 * following table provides the power enable configuration of peripheral power rails by J102 and J103.<br>
 *
 * <table>
 * <caption id="power_enable_of_peripheral_config">Table 4-11. Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="365px"> Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V
 * <tr><td align="center"> J102
 *     <td align="center"> SYS_RSTn (Default)
 * <tr><td align="center"> J103
 *     <td align="center"> CV_3V3
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_power_enable_of_peripheral.png "Figure 4-25. Jumpers and Switches for Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V."
 *
 * @subsubsection cv52_co_lpddr4x_nand_nor_flash_switch 4.2.38 SPI NAND / NOR flash switch
 *
 * SW31 is used to select different boot sources between SPI NAND flash and SPI NOR flash.
 * This table provides the selection by SW31.<br>
 *
 * <table>
 * <caption id="cv52_spi_nand_nor_flash_selection">Table 4-12. CV52 SPI NAND / NOR Flash Selection.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> Boot Source(V)
 * <tr><td align="center" rowspan="2"> SW31
 *     <td align="center"> ON
 *     <td align="center"> SPI NOR
 * <tr><td align="center"> OFF
 *     <td align="center"> SPI NAND (Default)
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_spi_nand_nor_flash_select.png "Figure 4-26. Jumpers and Switches for SPI NAND / NOR Flash Selection."
 *
 * @subsubsection cv52_co_lpddr4x_external_wdt 4.2.39 External WDT
 *
 * The watch dog timer (WDT) is implemented in the RESET chip. J123 is used to enable the WDT. This table provides
 * the selection by J123.<br>
 *
 * <table>
 * <caption id="cv52_external_wdt_selection">Table 4-13. CV52 External WDT Selection.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> Boot Source(V)
 * <tr><td align="center" rowspan="2"> J123
 *     <td align="center"> 1-2
 *     <td align="center"> Enable WDT
 * <tr><td align="center"> 2-3
 *     <td align="center"> Disable WDT (Default)
 * </table>
 *
 * @image html cv52_co_lpddr4x_jumpers_and_switches_for_external_wdt_select.png "Figure 4-27. Jumpers and Switches for External WDT Selection."*
 *
 * @note
 *   - When the external WDT is enabled, ensure that the corresponding software has been configured
 *     correctly. Otherwise, the system remains in the endless reboot cycle.<br>
 *
 * - - - -
 *
 * @section cv52_cr_lpddr5_system_io_hardware_control 5 System I/O and Hardware Control of CV52 EVK Cr (LPDDR5) Rev 1.0
 *
 * @subsection cv52_cr_lpddr5_connectors 5.1 Connectors
 *
 * The figures below show all main I/O connectors on the top and bottom sides (respectively) of
 * the CV52 EVK Cr (LPDDR5) board Rev1.0. <br>
 *
 * @image html cv52_cr_lpddr5_major_io_connectors_on_top_side.png "Figure 5-1. Major I/O Connectors on the Top Side of the CV52 EVK Cr (LPDDR5) Board."
 * @image html cv52_cr_lpddr5_major_io_connectors_on_bottom_side.png "Figure 5-2. Major I/O Connectors on the Bottom Side of the CV52 EVK Cr (LPDDR5) Board."
 *
 * Refer to the table below for a list of the main I/O connectors shown in the figures above.<br>
 *
 * <table>
 * <caption id="main_board_connectors_cr_lpddr5">Table 5-1. Main board connectors.</caption>
 * <tr><th> Item <th> Designator <th> Functions <th> Notes
 * <tr><td align="cemter"> 1
 *     <td align="center"> SW19
 *     <td> Key button
 *     <td> Key button for the GPIO debug
 * <tr><td align="cemter"> 2
 *     <td align="center"> J106
 *     <td> Power measurement
 *     <td> 10x2,1.25-mm connector for power measurement
 * <tr><td align="cemter"> 3
 *     <td align="center"> J105
 *     <td> Power measurement
 *     <td> 15x2,1.25-mm connector for power measurement
 * <tr><td align="cemter"> 4
 *     <td align="center"> J50
 *     <td> Ethernet
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * <tr><td align="cemter"> 5
 *     <td align="center"> J47
 *     <td> CVBS output
 *     <td> Mono RCA jack
 * <tr><td align="cemter"> 6
 *     <td align="center"> U91
 *     <td> IR input
 *     <td> IR receiver
 * <tr><td align="cemter"> 7
 *     <td align="center"> J76
 *     <td> CAN bus
 *     <td> 2x2, 2.54-mm connector for the CAN bus
 * <tr><td align="cemter"> 8
 *     <td align="center"> J37/J36
 *     <td> PCIe x4
 *     <td> Standard PCIe x4 card edge connectors
 * <tr><td align="cemter"> 9
 *     <td align="center"> J69
 *     <td> JTAG connector
 *     <td> 10x2, 2.54-mm connector for JTAG
 * <tr><td align="cemter"> 10
 *     <td align="center"> SW6~SW9
 *     <td> POC switch
 *     <td> 2-SPST / 4-SPST / 8-SPST switches for POC setting
 * <tr><td align="cemter"> 11
 *     <td align="center"> BAT2
 *     <td> RTC battery holder
 *     <td> 2032 battery holder for the RTC
 * <tr><td align="cemter"> 12
 *     <td align="center"> J51
 *     <td> Ethernet1
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * <tr><td align="cemter"> 13
 *     <td align="center"> J72
 *     <td> MCU SWD connector
 *     <td> 5x2, 2.54-mm connector for the MCU debug tool
 * <tr><td align="cemter"> 14
 *     <td align="center"> J75
 *     <td> MCU reset button
 *     <td> Button to reset the MCU
 * <tr><td align="cemter"> 15
 *     <td align="center"> SW13
 *     <td> Reset button
 *     <td> Button to initiate system warm boot
 * <tr><td align="cemter"> 16
 *     <td align="center"> SW20
 *     <td> MCU power-on button
 *     <td> Button to indicate to the MCU to power-on the system
 * <tr><td align="cemter"> 17
 *     <td align="center"> SW23
 *     <td> Power on / OFF switch button
 *     <td> Button to make the system switch between the power-on and<br>
 *          power-off states when the external power sequencer is used
 * <tr><td align="cemter"> 18
 *     <td align="center"> J78
 *     <td> Power jack
 *     <td> 12-V system power adapter input, 2.5-mm
 * <tr><td align="cemter"> 19
 *     <td align="center"> J42
 *     <td> Audio line-in
 *     <td> 3.5-mm audio jack
 * <tr><td align="cemter"> 20
 *     <td align="center"> J59
 *     <td> Audio HP out
 *     <td> 3.5-mm audio jack
 * <tr><td align="cemter"> 21
 *     <td align="center"> J55
 *     <td> Audio speaker out
 *     <td> 3.5-mm audio jack
 * <tr><td align="cemter"> 22
 *     <td align="center"> SW14~SW18
 *     <td> ADC1 key buttons
 *     <td> Key buttons in ADC1 to simulate menu / direction buttons
 * <tr><td align="cemter"> 23
 *     <td align="center"> J25
 *     <td> USB 2.0 device / serial debug port
 *     <td> Micro-B USB receptacle
 * <tr><td align="cemter"> 24
 *     <td align="center"> J29
 *     <td> USB 3.1 device
 *     <td> Micro-B USB 3.0 receptacle
 * <tr><td align="cemter"> 25
 *     <td align="center"> J31
 *     <td> USB 3.1 host
 *     <td> Type-A USB 3.0 receptacle
 * <tr><td align="cemter"> 26
 *     <td align="center"> J32
 *     <td> USB 3.1 hub host
 *     <td> Type-C USB 3.0 receptacle
 * <tr><td align="cemter"> 27
 *     <td align="center"> J33 / J34 / J35
 *     <td> USB 3.1 hub host
 *     <td> Type-A USB 3.0 receptacle
 * <tr><td align="cemter"> 28
 *     <td align="center"> J48 / J49
 *     <td> VOUT MIPI DSI A / B
 *     <td> 40-pin, 0.5-mm FPC connector for VOUT MIPI DSI
 * <tr><td align="cemter"> 29
 *     <td align="center"> J46
 *     <td> HDMI TX
 *     <td> Vertical HDMI receptacle
 * <tr><td align="cemter"> 30
 *     <td align="center"> SW1~SW5
 *     <td> PINMUX switch
 *     <td> 2-SPST / 4-SPST switches for PINMUX selection
 * <tr><td align="cemter"> 31
 *     <td align="center"> J43 / J44
 *     <td> VIN DCPHY
 *     <td> 41-pin, 0.5-mm connector for VIN DCPHY
 * <tr><td align="cemter"> 32
 *     <td align="center"> J39
 *     <td> VIN SLVS+DPHY
 *     <td> 164-pin PICe connector for VIN SLVS + DPHY
 * <tr><td align="cemter"> 33
 *     <td align="center"> J38
 *     <td> SSD hard drive
 *     <td> NVMe M2 connector
 * <tr><td align="cemter"> 34
 *     <td align="center"> J13
 *     <td> SDIO0
 *     <td> SD socket for SDIO0 I/F
 * <tr><td align="cemter"> 35
 *     <td align="center"> J19
 *     <td> SDIO1
 *     <td> Micro-SD socket for SDIO1 I/F
 * <tr><td align="cemter"> 36
 *     <td align="center"> BAT1
 *     <td> Lithium battery
 *     <td> 1.5-V lithium battery for RTC
 * </table>
 *
 * @subsection cv52_cr_lpddr5_system_io_configurations 5.2 System I/O Configurations
 *
 * The CV52 EVK board supplies abundant I/O interfaces for a variety of applications. Ensure that
 * the system I/O interfaces are properly configured with the on-board hardware jumpers and switches.<br>
 *
 * The figure below provides the locations of the jumpers and switches listed in this chapter.<br>
 *
 * @image html cv52_cr_lpddr5_major_jumpers_for_system_io_config_on_top_side.png "Figure 5-3. Major Jumpers for the System I/O Configurations on the Top Side of the CV52 EVK Cr (LPDDR5) Board."
 *
 * @subsubsection cv52_cr_lpddr5_gpio_debug 5.2.1 GPIO Debug
 *
 * SW19 is a key button for software GPIO debugging. SW19 is connected to GPIO138, which includes
 * a default pull-high in hardware. The software can configure GPIO138 to verify the general
 * input / output function. Pressing SW19 will assert low to GPIO138.
 *
 *   - SW2.pin3 = ON: Connect GPIO138 to SW19
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_gpio138_debug.png "Figure 5-4. Jumpers and Switches for the GPIO Debug (GPIO138)."
 *
 * @subsubsection cv52_cr_lpddr5_power_measurement 5.2.2 Power Measurement
 *
 * J105 and J106 are designed for power measurement. J105 and J106 have 30 / 20 pins and 1.25-mm
 * pitch connectors with a customized PIN-out. Contact the Ambarella support team for more details.<br>
 *
 * @subsubsection cv52_cr_lpddr5_ethernet 5.2.3 Ethernet
 *
 * The CV52 EVK board supports 1.8-V I/O between the MAC and the PHY.<br>
 *
 * CV52 requires a 125-MHz reference clock if GMAC functions. The 125-MHz clock can be chosen
 * from external oscillator or from GPHY. They can be chosen through switch SW30.<br>
 *
 *   - SW30 = OFF: Select 125-MHz clock from external oscillator
 *   - SW30 = ON: Select 125-MHz clock from GPHY
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_eth0_125mhz_clock.png "Figure 5-5. Jumpers and Switches for Ethernet 125-MHz Clock."
 *
 * Both GPHYs RTL8211 can supply the 125-MHz reference clock to the MAC. Use switch SW10 pin 1
 * to choose which is used.<br>
 *
 *   - SW10.pin1 = OFF: Select 125-MHz clock from GPHY RTL8211
 *   - SW10.pin1 = ON: Select 125-MHz clock from GPHY1 RTL8211
 *
 * J50 is a 10 / 100 / 1000 Base-T Ethernet single-port RJ45 connector with LEDs (link / act).
 * The CV52 ENET0 MAC supports the RGMII / RMII interfaces and the MDC / MDIO management interface
 * to the external Ethernet PHY.<br>
 *
 * Both Giga PHY RTL8211 and Mega PHY RTL8201 are assembled on the board. RTL8211 is connected
 * to CV52 through RGMII I/F, and RTL8201 is connected to CV52 through RMII I/F. Only one can
 * be used at a time. Use switch SW10 pin2 to choose which is used.<br>
 *
 *   - SW10.pin2 = OFF: Enable GPHY RTL8211
 *   - SW10.pin2 = ON: Enable MPHY RTL8201
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_eth0.png "Figure 5-6. Jumpers and Switches for Ethernet."
 *
 * @subsubsection cv52_cr_lpddr5_cvbs_output 5.2.4 CVBS Output
 *
 * J47 is a mono RCA jack for the CVBS output.<br>
 *
 * @subsubsection cv52_cr_lpddr5_ir_receiver 5.2.5 IR Receiver
 *
 * U91 is an IR receiver module for the infrared remote control systems with a 38-KHz
 * carrier frequency.<br>
 *
 * @subsubsection cv52_cr_lpddr5_can_bus 5.2.6 CAN Bus
 *
 * J76 is a 2x2, 2.54-mm connector for the CAN bus. J77 is a jumper that enables the CAN
 * transceiver. In normal mode, assemble the jumper on J77.<br>
 *
 *   - SW21 = OFF: Select CAN0
 *   - SW21 = ON: Select CAN1
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_can_bus.png "Figure 5-7. Jumpers and Switches for CAN."
 *
 * @subsubsection cv52_cr_lpddr5_pcie_x4 5.2.7 PCIe x4
 *
 * J36 and J37 are two standard, 64-pin PCIe x4 card edge connectors. The PCIe reference clock
 * is generated from the PCIe clock generator ― PI6CG18401, which can be configured through SW22.<br>
 *
 *   - SW22.pin1 = OFF: Disable the SS function
 *   - SW22.pin1 = ON: Enable the SS function at -0.5% spread
 *   - SW22.pin2 = OFF: Power on the PCIe clock generator
 *   - SW22.pin2 = ON: Power down the PCIe clock generator
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_pcie_x4.png "Figure 5-8. Jumpers and Switches for PCIe x4."
 *
 * @subsubsection cv52_cr_lpddr5_jtag_connector 5.2.8 JTAG Connector
 *
 * J60 is a 10x2, 2.54-mm connector for the JTAG debugging.<br>
 *
 * @subsubsection cv52_cr_lpddr5_poc_switch_sw6_sw9 5.2.9 POC Switch - SW6~SW9
 *
 * The table below shows the CV52 POC setup in SW6~SW9. Contact the Ambarella support team for
 * the POC user guide.<br>
 *
 * <table>
 * <caption id="cv52_evk_poc_setup">Table 5-2. CV52 EVK POC Setup.</caption>
 * <tr><th width="120px"> Designator <th width="85px"> Pins <th width="240px"> Notes
 * <tr><td align="center" rowspan="8"> SW6
 *     <td align="center"> pin A1
 *     <td> POC[21]=BOOT_OPTION[8]
 * <tr><td align="center"> pin A2
 *     <td> POC[1]=CLK_FRE[0]
 * <tr><td align="center"> pin A3
 *     <td> POC[2]=CLK_FRE[1]
 * <tr><td align="center"> pin A4
 *     <td> POC[3]=CLK_FRE[2]
 * <tr><td align="center"> pin A5
 *     <td> POC[8]=BOOT_BYPASS
 * <tr><td align="center"> pin A6
 *     <td> POC[30]=RESERVED
 * <tr><td align="center"> pin A7
 *     <td> POC[31]=SYSCONFIG_SRC
 * <tr><td align="center"> pin A8
 *     <td> POC[13]=BOOT_OPTION[0]
 * <tr><td align="center" rowspan="8"> SW7
 *     <td align="center"> pin A1
 *     <td> POC[16]=BOOT_OPTION[3]
 * <tr><td align="center"> pin A2
 *     <td> POC[17]=BOOT_OPTION[4]
 * <tr><td align="center"> pin A3
 *     <td> POC[18]=BOOT_OPTION[5]
 * <tr><td align="center"> pin A4
 *     <td> POC[19]=BOOT_OPTION[6]
 * <tr><td align="center"> pin A5
 *     <td> POC[20]=BOOT_OPTION[7]
 * <tr><td align="center"> pin A6
 *     <td> POC[4]=BOOT_MODE[0]
 * <tr><td align="center"> pin A7
 *     <td> POC[5]=BOOT_MODE[1]
 * <tr><td align="center"> pin A8
 *     <td> POC[6]=SECURE_BOOT
 * <tr><td align="center" rowspan="2"> SW8
 *     <td align="center"> pin A1
 *     <td> POC[14]=BOOT_OPTION[1]
 * <tr><td align="center"> pin A2
 *     <td> POC[15]=BOOT_OPTION[2]
 * <tr><td align="center"> SW9
 *     <td align="center"> pin A1
 *     <td> POC[10]=FORCE_USB_BOOT
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_poc_sw6_sw9.png "Figure 5-9. Jumpers and Switches for POC."
 *
 * @subsubsection cv52_cr_lpddr5_rtc_battery_holder 5.2.10 RTC Battery Holder
 *
 * BAT2 is a 2032 battery holder for the CV52 RTC block. By default, the battery is not assembled.
 * Ensure correct battery polarity during assembly.<br>
 *
 * @subsubsection cv52_cr_lpddr5_ethernet_1 5.2.11 Ethernet 1
 *
 * J51 is a 10 / 100 / 1000 Base-T Ethernet single port RJ45 connector with LEDs (link / act).
 * The CV52 ENET1 MAC supports the RGMII / RMII interfaces and the MDC / MDIO management
 * interface to the external Ethernet PHY.<br>
 *
 * Both Giga PHY RTL8211 and Mega PHY RTL8201 are assembled on the board. RTL8211 is connected
 * to the CV52 through RGMII I/F, and RTL8201 is connected to the CV52 through RMII I/F. Only
 * one can be used at a time.  Use switch SW11 to choose which is used.<br>
 *
 *   - SW11 = OFF: Enable GPHY RTL8211
 *   - SW11 = ON: Enable MPHY RTL8201
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_ethernet_1.png "Figure 5-10. Jumpers and Switches for Ethernet 1."
 *
 * @subsubsection cv52_cr_lpddr5_mcu_swd_connector 5.2.12 MCU SWD Connector
 *
 * J72 is a 5x2, 2.54-mm connector for the MCU debug tool. It supports only a 2-pin SWD function.<br>
 *
 * @subsubsection cv52_cr_lpddr5_mcu_reset_button 5.2.13 MCU Reset Button
 *
 * J75 is the MCU reset button, which triggers an active-low signal to assert a hardware reset
 * to the MCU.<br>
 *
 * @subsubsection cv52_cr_lpddr5_reset_button 5.2.14 Reset Button
 *
 * SW13 functions as the system reset button, which triggers an active-low signal to assert a
 * system reset to CV52 POR pin.<br>
 *
 * @subsubsection cv52_cr_lpddr5_mcu_power_on_button 5.2.15 MCU Power-on Button
 *
 * SW20 functions as a power-on button, which triggers an active-low signal to indicate a
 * power-on action to the MCU.  Ensure that the software has enabled this function in the MCU.<br>
 *
 * @subsubsection cv52_cr_lpddr5_power_on_off_switch_button 5.2.16 Power ON / OFF Switch Button
 *
 * SW23 functions as a system power ON / OFF switch button. Pressing SW23 powers on the system
 * if the system is in the OFF state, or power off the system if the system is in the ON state.
 * Do not assemble a jumper on J79.  If there is a jumper on J79, it will bypass SW23.<br>
 *
 * @subsubsection cv52_cr_lpddr5_power_jack 5.2.17 Power Jack
 *
 * J78 is a standard 2.5-mm power jack for an external 12-V power adapter. Plugging the power
 * adapter through J78 supplies the power for the CV52 EVK board.<br>
 *
 * @subsubsection cv52_cr_lpddr5_audio_line_in 5.2.18 Audio Line-in
 *
 * The on-board audio codec is NAU88C22.<br>
 * The CV52 CLK_AU signal could be chosen to output to NAU88C22 or to the external audio codec
 * through SW12.<br>
 *
 *   - Assemble the jumpers on J52 and J54
 *   - SW12 = OFF: Connect to NAU88C22
 *   - SW12 = ON: Connect to the external audio codec
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_clk_au_to_audio_codec.png "Figure 5-11. Jumpers and Switches for CLK_AU to Audio Codec."
 *
 * The audio line-in is available in J42, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv52_cr_lpddr5_audio_hp_out 5.2.19 Audio HP out
 *
 * The audio HP out is available in J59, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv52_cr_lpddr5_audio_speaker_out 5.2.20 Audio Speaker Out
 *
 * The audio speaker out is available in J55, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv52_cr_lpddr5_adc1_key_button 5.2.21 ADC1 Key Buttons
 *
 * SW14~SW18 are key buttons to simulate menu / direction buttons. Ensure that the software has
 * this function enabled in ADC1.<br>
 *
 * @subsubsection cv52_cr_lpddr5_usb_20_device_serial_debug_port 5.2.22 USB2.0 Device / Serial Debug Port
 *
 * J25 is a Micro-B USB receptacle. USB0 I/F functions in device mode only. Plug the USB cable
 * from the USB host to J25. The AmbaUSB tool functions in this mode. It also serves as a serial
 * debug port because a USB-to-UART chip is used to perform the interface conversion.<br>
 *
 * @subsubsection cv52_cr_lpddr5_usb_31_device 5.2.23 USB 3.1 Device
 *
 * J29 is a Micro-B USB 3.1 receptacle. When USB1 I/F is in device mode, plug the USB host to J29.<br>
 *
 *   - Jumper on J28 must be assembled
 *
 * @subsubsection cv52_cr_lpddr5_usb_31_host 5.2.24 USB3.1 Host
 *
 * J31 is a Type-A USB3.1 receptacle.  When USB1 I/F is in host mode, plug the USB device to J31.<br>
 *
 *   - Jumper on J28 must not be assembled
 *   - Jumper on J30 must be assembled
 *
 * @subsubsection cv52_cr_lpddr5_usb_31_hub_host 5.2.25 USB3.1 Hub Host
 *
 * J32 is a Type-C USB3.1 receptacle, and J33~J35 are Type-A USB3.1 receptacles from the on-board
 * USB3.1 hub. When USB1 I/F functions in host mode and is connected through the USB3.1 hub,
 * J32~J36 will be available.<br>
 *
 *   - Jumper on J28 must not be assembled
 *   - Jumper on J30 must not be assembled
 *
 * @subsubsection cv52_cr_lpddr5_vout_mipi_dsi 5.2.26 VOUT MIPI DSI
 *
 * J48 and J49 are two 20x2, 0.5-mm FFC / FPC connectors for the MIPI DSI A and B output. They
 * are customized pin-out connectors. Check the reference design for more details.<br>
 *
 * @subsubsection cv52_cr_lpddr5_hdmi_tx 5.2.27 HDMI TX
 *
 * J46 is a standard vertical 19-pin HDMI receptacle for HDMI TX. Assemble the jumper on J45
 * to enable 5-V power on J46.
 *
 * @subsubsection cv52_cr_lpddr5_pinmux_switch_sw1_sw5 5.2.28 PINMUX Switch – SW1~SW5
 *
 * SW1, SW2, and SW4 are 4-SPST switches, while SW3 and SW5 are 2-SPST switches used for
 * PINMUX selection.<br>
 *
 * The table below shows a summary of the PINMUX switches. Refer to each sector for details.<br>
 *
 * <table>
 * <caption id="cv52_evk_mux_configurations">Table 5-3. CV52 EVK Mux Configurations.</caption>
 * <tr><th> Switch <th> Pin <th> Status <th> Function <th> Description
 * <tr><td align="center" rowspan="26"> SW1
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO65 as VSDELAY_HSYNC_OUT_0
 *     <td> HSYNC0 to VIN / DCPHY1 connector
 * <tr><td> GPIO66 as VSDELAY_HSYNC_OUT_1
 *     <td> HSYNC1 to SLVC-EC / DCPHY0 connector
 * <tr><td> GPIO67 as EXT_HSYNC_SRC_INPUT
 *     <td> HSYNC source input
 * <tr><td> GPIO68 as EXT_VSYNC_SRC_INPUT
 *     <td> VSYNC source input
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO65 as GPIO65
 *     <td> GPIO
 * <tr><td> GPIO66 as GPIO66
 *     <td> GPIO
 * <tr><td> GPIO67 as DMIC_CLK
 *     <td> DMIC clock
 * <tr><td> GPIO68 as DMIC_DAT
 *     <td> DMIC data
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO69 as SSI1_SCLK
 *     <td> SS1 clock
 * <tr><td> GPIO70 as SSI1_TXD
 *     <td> SSI1 TX Data
 * <tr><td> GPIO71 as SSI1_RXD
 *     <td> SSI1 RX Data
 * <tr><td> GPIO72 as SSI1_EN0
 *     <td> SSI1 to Gyro
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO69 as GPIO69
 *     <td> GPIO69 to VIN
 * <tr><td> GPIO70 as GPIO70
 *     <td> GPIO70 to VIN
 * <tr><td> GPIO71 as GPIO71
 *     <td> GPIO71 to VIN
 * <tr><td> GPIO72 as GPIO72
 *     <td> GPIO72 to VIN
  * <tr><td align="center" rowspan="6"> Pin3
 *     <td align="center" rowspan="3"> OFF
 *     <td> GPIO73 as SSI1_EN1
 *     <td> SSI1 to MIPI_DSI_A connector
 * <tr><td> GPIO74 as SSI1_EN2
 *     <td> SSI1 to MIPI_DSI_B connector
 * <tr><td> GPIO75 as SSI1_EN3
 *     <td> SSI1 to debug connector
 * <tr><td align="center" rowspan="3"> ON
 *     <td> GPIO73 as GPIO73
 *     <td> GPIO73 to VIN
 * <tr><td> GPIO74 as GPIO74
 *     <td> GPIO74 to VIN
 * <tr><td> GPIO75 as GPIO75
 *     <td> GPIO75 to VIN
 * <tr><td align="center" rowspan="4"> Pin4
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO76 as GPIO76
 *     <td> GPIO76 to VIN
 * <tr><td> GPIO77 as GPIO77
 *     <td> GPIO77 to VIN
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO76 as IDCSCLK
 *     <td> IDCS clock
 * <tr><td> GPIO77 as IDCSDATA
 *     <td> IDCS data
 * <tr><td align="center" rowspan="28"> SW2
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO92 as SDIO0_D[0]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO93 as SDIO0_D[1]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO94 as SDIO0_D[2]
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO95 as SDIO0_D[3]
 *     <td> SDIO0 for SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO92 as VSDELAY_VSYNC_OUT_0
 *     <td> VSYNC0 to VIN
 * <tr><td> GPIO93 as VSDELAY_VSYNC_OUT_1
 *     <td> VSYNC1 to SLVS-EC
 * <tr><td> GPIO94 as VSDELAY_VSYNC_OUT_2
 *     <td> VSYNC2 to DCPHY0
 * <tr><td> GPIO95 as VSDELAY_VSYNC_OUT_3
 *     <td> VSYNC3 to DCPHY1
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO96 as SDIO0_CLK
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO97 as SDIO0_CMD
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO98 as SDIO0_CD
 *     <td> SDIO0 for SD socket
 * <tr><td> GPIO99 as SDIO0_WP
 *     <td> SDIO0 for SD socket
  * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO96 as IDC1CLK
 *     <td> IDC1 to DCPHY1 / MIPI_DSI_A connector
 * <tr><td> GPIO97 as IDC1DATA
 *     <td> IDC1 to DCPHY1 / MIPI_DSI_A connector
 * <tr><td> GPIO98 as GPIO98
 *     <td> GPIO
 * <tr><td> GPIO99 as GPIO99
 *     <td> GPIO
 * <tr><td align="center" rowspan="4"> Pin3
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO100 as GPIO100
 *     <td> SDIO0 PWRON for SD socket
 * <tr><td> GPIO138 as SDIO0_HS_SEL
 *     <td> SDIO0_HS_SEL
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO100 as GPIO100
 *     <td> Reset to DCPHY1 connector
 * <tr><td> GPIO138 as GPIO138
 *     <td> GPIO
 * <tr><td align="center" rowspan="8"> Pin4
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO101 as SDIO1_D[0]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO102 as SDIO1_D[1]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO103 as SDIO1_D[2]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO104 as SDIO1_D[3]
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO101 as SSI3_RXD
 *     <td> SSI3 RX data
 * <tr><td> GPIO102 as SSI3_TXD
 *     <td> SSI3 TX data
 * <tr><td> GPIO103 as SSI3_SCLK
 *     <td> SSI3 clock
 * <tr><td> GPIO104 as SSI3_EN0
 *     <td> SSI3 to DCPHY1 / SLVS-EC connector
 * <tr><td align="center" rowspan="12"> SW3
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO105 as SDIO1_CLK
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO106 as SDIO1_CMD
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO107 as SDIO1_CD
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td> GPIO108 as SDIO1_WP
 *     <td> SDIO1 for Micro-SD socket
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO105 as GPIO105
 *     <td> GPIO105 to DCPHY0 / SLVS-EC
 * <tr><td> GPIO106 as GPIO106
 *     <td> GPIO106 to DCPHY0
 * <tr><td> GPIO107 as IDC5CLK
 *     <td> IDC5 to DCPHY1 / SLVS-EC connector
 * <tr><td> GPIO108 as IDC5DATA
 *     <td> IDC5 to DCPHY1 / SLVS-EC connector
 * <tr><td align="center" rowspan="4"> Pin2
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO109 as GPIO109
 *     <td> SDIO1 PWRON for the Micro-SD socket
 * <tr><td> GPIO132 as SDIO1_HS_SEL
 *     <td> SDIO1_HS_SEL
 * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO109 as GPIO109
 *     <td> GPIO109 as reset to DCPHY0 / SLVS-EC connector
 * <tr><td> GPIO132 as GPIO132
 *     <td> GPIO132 as FLASH debug
 * <tr><td align="center" rowspan="26"> SW4
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO133 as I2S1_CLK or UART2_AHB_RX
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO134 as I2S1_SI_0 or UART2_AHB_TX
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO135 as I2S1_SO_0 or UART2_AHB_CTS_N
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td> GPIO136 as I2S1_WS or UART2_AHB_RTS_N
 *     <td> I2S1 or UART2 to external audio codec debug connector
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO133 as SSI4_SCLK
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO134 as SSI4_TXD
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO135 as SSI4_RXD
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td> GPIO136 as SSI4_EN0
 *     <td> SSI4 to DCPHY1 connector
 * <tr><td align="center" rowspan="2"> Pin2
 *     <td align="center"> OFF
 *     <td> GPIO0 as IR_IN
 *     <td> IR receiver (Input)
 * <tr><td align="center"> ON
 *     <td> GPIO0 as WDT_EXT_RST_L
 *     <td> WDTn
 * <tr><td align="center" rowspan="8"> Pin3
 *     <td aling="center" rowspan="4"> OFF
 *     <td> GPIO119 as GPIO119
 *     <td> GPIO
 * <tr><td> GPIO120 as GPIO120
 *     <td> GPIO
 * <tr><td> GPIO121 as GPIO121
 *     <td> GPIO
 * <tr><td> GPIO122 as GPIO122
 *     <td> GPIO
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO119 as USB32C_OVERCURRENT
 *     <td> USB32_Over_Current
 * <tr><td> GPIO120 as USB32C_DRIVE_VBUS
 *     <td> USB32_PWRON
 * <tr><td> GPIO121 as PWM10
 *     <td> PWM10
 * <tr><td> GPIO122 as PWM11
 *     <td> PWM11
 * <tr><td align="center" rowspan="8"> Pin4
 *     <td aling="center" rowspan="4"> OFF
 *     <td> GPIO123 as GPIO123
 *     <td> GPIO123 to MIPI_DSI_A
 * <tr><td> GPIO124 as GPIO124
 *     <td> GPIO124 to MIPI_DSI_A
 * <tr><td> GPIO125 as GPIO125
 *     <td> GPIO125 to MIPI_DSI_A
 * <tr><td> GPIO126 as GPIO126
 *     <td> GPIO126 to MIPI_DSI_A
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO123 as UART1_AHB_RX
 *     <td> UART1
 * <tr><td> GPIO124 as UART1_AHB_TX
 *     <td> UART1
 * <tr><td> GPIO125 as UART1_AHB_CTS_N
 *     <td> UART1
 * <tr><td> GPIO126 as UART1_AHB_RTS_N
 *     <td> UART1
 * <tr><td align="center" rowspan="16"> SW5
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO127 as GPIO127
 *     <td> GPIO127 to MIPI_DSI_B
 * <tr><td> GPIO128 as GPIO128
 *     <td> GPIO128 to MIPI_DSI_B
 * <tr><td> GPIO129 as GPIO129
 *     <td> GPIO129 to MIPI_DSI_B
 * <tr><td> GPIO130 as GPIO130
 *     <td> GPIO130 to MIPI_DSI_B
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO127 as CAN0_RX
 *     <td> CAN0
 * <tr><td> GPIO128 as CAN0_TX
 *     <td> CAN0
 * <tr><td> GPIO129 as CAN1_RX
 *     <td> CAN1
 * <tr><td> GPIO130 as CAN1_TX
 *     <td> CAN1
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO106 as IDC4CLK
 *     <td> IDC4 for VIN / external RTC
 * <tr><td> GPIO107 as IDC4DATA
 *     <td> IDC4 for VIN / external RTC
 * <tr><td> GPIO108 as IDC3CLK
 *     <td> IDC3 for VIN / EXGPIO
 * <tr><td> GPIO109 as IDC3DATA
 *     <td> IDC3 for VIN / EXGPIO
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO106 as SSI2_SCLK
 *     <td> SSI2 in debug header
 * <tr><td> GPIO107 as SSI2_TXD
 *     <td> SSI2 in debug header
 * <tr><td> GPIO108 as SSI2_RXD
 *     <td> SSI2 in debug header
 * <tr><td> GPIO109 as SSI2_EN0
 *     <td> SSI2 in debug header
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_sw1_sw5.png "Figure 5-12. Jumpers and Switches for SW1~SW5."
 *
 * @subsubsection cv52_cr_lpddr5_vin_dcphy 5.2.29 VIN DCPHY
 *
 * J43 and J44 are two 41-pin, 0.5-mm pitch, 3.8-mm height connectors for the VIN DCPHY I/Fs.
 * They are customized pin-out connectors. Check the reference design for details.<br>
 *
 * @subsubsection cv52_cr_lpddr5_vin_slvs_dcphy 5.2.30 VIN SLVS+DPHY
 *
 * J39 is a standard 164-pin, PCIe connector for the VIN SLVS+DPHY. J39 is a customized pin-out
 * connector. Check the reference design for details.<br>
 *
 * @subsubsection cv52_cr_lpddr5_nvme_m2_connector 5.2.31 NVMe M.2 Connector
 *
 * J38 is a standard NVMe M.2 connector for the PCIe-based SSD hard drive.<br>
 *
 * @subsubsection cv52_cr_lpddr5_sdio0 5.2.32 SDIO0
 *
 * SDIO0 is available in J13, which is an SD socket on the bottom side.
 *
 *   - SW2.pin1 / 2 / 3 = LOW: SDIO0 is connected to the J13 socket shown in the figure below
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_sdio0_sw2.png "Figure 5-13. Jumpers and Switches for SDIO0."
 *
 * J14 is used to control the J13 VDD (3.3 V).<br>
 *
 *   - J14 pin2-3 ON: Enable software control on the VDD
 *   - J14 pin1-2 ON: Make the VDD always-on
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_sdio0_j14.png "Figure 5-14. Jumpers and Switches for J14."
 *
 * When an SD memory card is used in J13:<br>
 *
 *   - Jumper on J16 must be assembled
 *   - Jumper on J18 must not be assembled
 *
 * When an SD I/O card is used in J13:<br>
 *
 *   - Jumper on J16 must not be assembled
 *   - Jumper on J18 must be assembled to select SDIO0 I/O voltage
 *     - J18.pin1-2: SDIO0_VDDO = 1.8 V
 *     - J18.pin2-3: SDIO0_VDDO = 3.3 V
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_sdio0_j16_j18.png "Figure 5-15. Jumpers and Switches for SDIO."
 *
 * @subsubsection cv52_cr_lpddr5_sdio1 5.2.33 SDIO1
 *
 * SDIO1 is available in J19, which is a micro-SD socket on the bottom side.<br>
 *
 *   - SW2.pin4 = LOW and SW3.pin1/2 = LOW: SDIO1 is connected to the J19 socket
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_sdio1_sw23.png "Figure 5-16. Jumpers and Switches for SDIO1."
 *
 * J20 is used to control the J19 VDD (3.3 V).<br>
 *
 *   - J20 pin2-3 ON: Enable software control on the VDD
 *   - J20 pin1-2 ON: Make the VDD always-on
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_sdio1_j20.png "Figure 5-17. Jumpers and Switches for J20."
 *
 * When an SD memory card is used in J19:<br>
 *
 *   - Jumper on J22 must be assembled
 *   - Jumper on J24 must not be assembled
 *
 * When an SD I/O card is used in J19:
 *
 *   - Jumper on J22 must not be assembled
 *   - Jumper on J24 must be assembled to select SDIO0 I/O voltage
 *     - J24.pin1-2: SDIO1_VDDO = 1.8 V
 *     - J24.pin2-3: SDIO1_VDDO = 3.3 V
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_sdio1_j22_j24.png "Figure 5-18. Jumpers and Switches for J22 and J24."
 *
 * @subsubsection cv52_cr_lpddr5_emmc 5.2.34 eMMC
 *
 * The on-board eMMC is connected to the CV52 SD interface as a boot source.<br>
 * J7 is used to select eMMC VCC and J8 is used to select eMMC VCCQ.<br>
 * This table provides the eMMC VCC and eMMC VCCQ configuration by J7 and J8.<br>
 *
 * <table>
 * <caption id="emmc_vcc_vccq_config">Table 5-4. eMMC VCC and eMMC VCCQ (CV52 SD_VDDO) Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Power Rail <th width="165px"> Jumpers <th width="200px"> Power Rail Value (V)
 * <tr><td align="center" rowspan="2"> J7
 *     <td align="center" rowspan="2"> eMMC VCC
 *     <td align="center"> 1-2
 *     <td align="center"> 1.8 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> 3.3 V (Default)
 * <tr><td align="center" rowspan="2"> J8
 *     <td align="center" rowspan="2"> eMMC VCCQ <br>
 *                                     (CV52 SD_VDDO)
 *     <td align="center"> 1-2
 *     <td align="center"> 1.8 V (Default)
 * <tr><td align="center"> 2-3
 *     <td align="center"> 3.3 V
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_emmc_vcc_vccq.png "Figure 5-19. Jumpers and Switches for eMMC VCC and eMMC VCCQ."
 *
 * @subsubsection cv52_cr_lpddr5_lithium_battery 5.2.35 Lithium Battery
 *
 * BAT1 is a 1.5-V lithium battery for the CV52 RTC block. By default, the battery is not assembled.
 * Ensure correct battery polarity during assembly.<br>
 *
 * @subsubsection cv52_cr_lpddr5_power_jumpers 5.2.36 Power Jumpers
 *
 * J97 is used to adjust the VDD. The following table provides the VDD configuration via J97.<br>
 *
 * <table>
 * <caption id="cv52_vdd_configuration">Table 5-5. CV52 VDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Jumpers <th width="200px"> VDD Value (V)
 * <tr><td align="center" rowspan="4"> J97
 *     <td align="center"> 1-3
 *     <td align="center"> 0V7
 * <tr><td align="center"> 3-5
 *     <td align="center"> 0V75 (Default)
 * <tr><td align="center"> 4-6
 *     <td align="center"> 0V8
 * <tr><td align="center"> 2-4
 *     <td align="center"> 0V85
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_cv52_vdd.png "Figure 5-20. Jumpers and Switches for CV52 VDD."
 *
 * @note
 *   - Do not adjust the VDD voltage when the board is powered on so as to avoid permanently
 *     damaging the CV52 chipset.
 *
 * SW27 is used to adjust the VDDA. This table provides the VDDA configuration by SW27.<br>
 *
 * <table>
 * <caption id="cv52_vdda_configuration">Table 5-6. CV52 VDDA Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> VDDA Value (V)
 * <tr><td align="center" rowspan="2"> SW27
 *     <td align="center"> ON
 *     <td align="center"> 0V8 (Default)
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V825
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_cv52_vdda.png "Figure 5-21. Jumpers and Switches for CV52 VDDA."
 *
 * SW28 is used to select PCIE_AVDD. This table provides the PCIE_AVDD configuration by SW28.<br>
 *
 * <table>
 * <caption id="cv52_pcie_avdd_configuration">Table 5-7. CV52 PCIE_AVDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> PCIE_AVDD Value(V)
 * <tr><td align="center" rowspan="2"> SW28
 *     <td align="center"> ON
 *     <td align="center"> 0V8
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V85 (Deafult)
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_pcie_avdd.png "Figure 5-22. Jumpers and Switches for PCIE_AVDD."
 *
 * SW29 is used to select DCPHY_AVDD. This table provides the DCPHY_AVDD configuration by SW29.<br>
 *
 * <table>
 * <caption id="cv52_dcphy_avdd_configuration">Table 5-8. CV52 DCPHY_AVDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> PCIE_AVDD Value(V)
 * <tr><td align="center" rowspan="2"> SW29
 *     <td align="center"> ON
 *     <td align="center"> 0V8
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V85 (Deafult)
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_dcphy_avdd.png "Figure 5-23. Jumpers and Switches for DCPHY_AVDD."
 *
 * J112 and J113 are used to select the power enablement of PWR_CVSYS_5V and PWR_CVSYS_3V3. This
 * table provides the PWR_CVSYS_5V and PWR_CVSYS_3V3 configuration by J112 and J113.<br>
 *
 * <table>
 * <caption id="cv52_power_5v_33v_configuration">Table 5-9. CV52 PWR_CVSYS_5V and PWR_CVSYS_3V3 Power Enable Source Configuation.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Power Rail <th width="165px"> Jumpers <th width="200px"> Power Enable Source
 * <tr><td align="center" rowspan="2"> J112
 *     <td align="center" rowspan="2"> PWR_CVSYS_5V
 *     <td align="center"> 1-2
 *     <td align="center"> 12 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> PWR_PSEQ1 (Default)
 * <tr><td align="center" rowspan="2"> J113
 *     <td align="center" rowspan="2"> PWR_CVSYS_3V3
 *     <td align="center"> 1-2
 *     <td align="center"> 12 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> PWR_PSEQ1 (Default)
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_cv52_power_enable_source.png "Figure 5-24. Jumpers and Switches for CV52 PWR_CVSYS_5V and PWR_CVSYS_3V3 Power Enable Source."
 *
 * J102 and J103 are used to select the power enablement of peripheral 1V8 / 3V3 / 5V / 12V. The
 * following table provides the power enable configuration of peripheral power rails by J102 and J103.<br>
 *
 * <table>
 * <caption id="power_enable_of_peripheral_config">Table 5-10. Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="365px"> Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V
 * <tr><td align="center"> J102
 *     <td align="center"> SYS_RSTn (Default)
 * <tr><td align="center"> J103
 *     <td align="center"> CV_3V3
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_power_enable_of_peripheral.png "Figure 5-25. Jumpers and Switches for Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V."
 *
 * @subsubsection cv52_cr_lpddr5_nand_nor_flash_switch 5.2.37 SPI NAND / NOR Flash Switch
 *
 * SW31 is used to select different boot sources between SPI NAND flash and SPI NOR flash.
 * This table provides the selection by SW31.<br>0
 *
 * <table>
 * <caption id="cv52_spi_nand_nor_flash_selection">Table 5-11. CV52 SPI NAND / NOR Flash Selection.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> Boot Source(V)
 * <tr><td align="center" rowspan="2"> SW31
 *     <td align="center"> ON
 *     <td align="center"> SPI NOR
 * <tr><td align="center"> OFF
 *     <td align="center"> SPI NAND (Default)
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_spi_nand_nor_flash_select.png "Figure 5-26. Jumpers and Switches for SPI NAND / NOR Flash Selection."
 *
 * @subsubsection cv52_cr_lpddr5_external_wdt 5.2.38 External WDT
 *
 * The WDT is implemented in the RESET chip. J123 is used to enable the WDT. This table provides
 * the selection by J123.<br>
 *
 * <table>
 * <caption id="cv52_external_wdt_selection">Table 5-12. CV52 External WDT Selection.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> Boot Source(V)
 * <tr><td align="center" rowspan="2"> J123
 *     <td align="center"> 1-2
 *     <td align="center"> Enable WDT
 * <tr><td align="center"> 2-3
 *     <td align="center"> Disable WDT (Default)
 * </table>
 *
 * @image html cv52_cr_lpddr5_jumpers_and_switches_for_external_wdt_select.png "Figure 5-27. Jumpers and Switches for External WDT Selection."*
 *
 * @note
 *   - When the external WDT is enabled, ensure that the corresponding software has been configured
 *     correctly. Otherwise, the system remains in the endless reboot cycle.<br>
 *
 * - - - -
 *
 * @section cv52_co_doc_license 6 License
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
 * @file doc_hw_cv72_gage.h
 * @brief
 * @version 1.0
 * @date 2023-02-07
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
 * @page page_cv72_gage Board - CV72 Ga / Ge
 *
 * This chapter provides details on setting up the hardware for the evaluation kit (EVK) and is
 * divided into the following sections:<br>
 *
 *   - Section @ref cv72_ga_evk_package
 *   - Section @ref cv72_ga_overview
 *   - Section @ref cv72_ga_setting_up
 *   - Section @ref cv72_ga_system_io_hardware_control
 *   - Section @ref cv72_ga_design_notes
 *   - Section @ref cv72_ga_doc_license
 *
 * - - - -
 *
 * @section cv72_ga_evk_package 1 EVK Package
 *
 * The Ambarella Cooper Linux EVK contains the following hardware and accessories. If any of the
 * following components are missing from the EVK package, contact the Ambarella support team.<br>
 *
 * <table>
 * <tr><td align="center"> <b> EVK board </b>
 *     <td> The board that comes furnished with the Ambarella CV72 system on chip (SoC)
 * <tr><td align="center"> <b> Sensor board </b>
 *     <td> The sensor board that is connected to the EVK board as the video input (VIN)
 * <tr><td align="center"> <b> Cables </b>
 *     <td> Serial cable and USB cable
 * <tr><td align="center"> <b> EVK firmware  </b>
 *     <td> The firmware in the folder Binary/ that is upgraded to the EVK board
 * <tr><td align="center"> <b> Install program  </b>
 *     <td> The tools in the folder Tools/ that are used for evaluation, including <br>
 *          AmbaUSB, PortServer, USBServer, and the VideoLAN Client (VLC) player
 * <tr><td align="center"> <b> Getting started guide  </b>
 *     <td> The document providing information on how to use the EVK
 * </table>
 *
 * The pre-loaded demonstration application is provided through the following:<br>
 *
 * <table>
 * <tr><td align="center" width="165px"> <b> Unit test program </b>
 *     <td> The unit test applications used to evaluate features using commands from<br>
 *          the command line interface
 * </table>
 *
 * @note
 *  - For CV72, the hardware setup for Ge EVK board is the same as as Ga EVK board.
 *
 * - - - -
 *
 * @section cv72_ga_overview 2 Overview of the EVK Board
 *
 * The figure below provides an overview of the major components and input / output (I/O)
 * connectors of the CV72 Ga EVK board.<br>
 *
 * @image html cv72_ga_evk_lpddr5_board.png "Figure 2-1. CV72 EVK Ga (LPDDR5) Board."
 *
 * The major components and I/O connectors identified in the figure above are as follows:<br>
 *
 * <b>1.</b> USB to serial debug universal asynchronous receiver / transmitter (UART) and firmware download port<br>
 * <b>2.</b> Internal power on / off<br>
 * <b>3.</b> Reset<br>
 * <b>4.</b> External power on / off<br>
 * <b>5.</b> Microcontroller unit (MCU) reset<br>
 * <b>6.</b> Audio line-out<br>
 * <b>7.</b> Audio headphone (HP) out<br>
 * <b>8.</b> Audio speaker out<br>
 * <b>9.</b> Joint test action group (JTAG)<br>
 * <b>10.</b> Dual in-line package (DIP) switches<br>
 * <b>11.</b> VIN port1<br>
 * <b>12.</b> VIN port2<br>
 * <b>13.</b> Mobile industry processor interface (MIPI) DSI® video output (VOUT)<br>
 * <b>14.</b> USB 3.2 host<br>
 * <b>15.</b> USB Type-C<br>
 * <b>16.</b> Micro USB 3.2 device<br>
 * <b>17.</b> Composite video broadcast signal (CVBS) VOUT<br>
 * <b>18.</b> Infrared (IR) receiver<br>
 * <b>19.</b> Peripheral component interconnect express (PCIe) x1 port<br>
 * <b>20.</b> Ethernet<br>
 * <b>21.</b> 12-V DC power<br>
 * <b>22.</b> High definition multimedia interface (HDMI®) VOUT<br>
 * - - - -
 *
 * @section cv72_ga_setting_up 3 Setting Up the EVK Board
 *
 * Use the following steps to set up the EVK hardware for the first time.<br>
 *
 *   - Using a grounding strap or another verified device to protect the board from static
 *     charges. Connect the communication cables to the board before connecting any equipment
 *     to the power supply.<br>
 *
 *   - Ensure that the parallel sensors used on the CV72 Ga boards are compatible with the adapter. Then,
 *     carefully insert the sensor board to the slot of the primary VIN, which is component
 *     1 on the EVK board (see the following figure). Ensure that the sensor board is secure
 *     before proceeding.<br>
 *
 * @image html cv72_ga_sensor_board_inserted.png "Figure 3-1. Sensor Board Inserted into the CV72 Ga Board."
 *
 *   - Use an Ethernet cable to connect the Ethernet port on the EVK board to the network
 *     port on the host PC.<br>
 *
 *   - For high-definition (HD) preview, connect a video display with an HDMI input to the
 *     HDMI connector on the EVK board.<br>
 *
 * @image html cv72_ga_connected_hdmi_ethernet_usb_cable.png "Figure 3-2. CV72 Ga Board with the HDMI / Ethernet / USB Cable Connected."
 *
 *   - For the UART console window, the CV72 Ga EVK board is equipped with a USB serial bridge.
 *     Connect the EVK board to the host PC using a USB Mini A cable.<br>
 *
 *   - To ensure protection from electro-static discharge (ESD), first connect the power cable
 *     to the EVK power jack on the board, and then connect the cable to the power supply.<br>
 * - - - -
 *
 * @section cv72_ga_system_io_hardware_control 4 CV72 Ga EVK (LPDDR5) System I/O and Hardware Control
 *
 * @subsection cv72_ga_connectors 4.1 Connectors
 *
 * The following figures show all main I/O connectors on the top side
 * of the CV72 Ga EVK base board Rev1.0.<br>
 *
 * @image html cv72_ga_major_io_connectors_on_the_top_side.png "Figure 4-1. Major I/O Connectors on the Top Side of the CV72 Ga EVK Base Board."
 *
 * Refer to the table below for a list of the main I/O connectors shown in the figures above.<br>
 *
 * <table>
 * <caption id="main_board_connectors">Table 4-1. Main Board Connectors.</caption>
 * <tr><th> Item <th> Designator <th> Functions <th> Notes
 * <tr><td align="center"> 1
 *     <td align="center"> J76
 *     <td> Controller area network (CAN) bus
 *     <td> 2x2, 2.54-mm connector for the CAN bus
 * <tr><td align="center"> 2
 *     <td align="center"> J105
 *     <td> Power measurement
 *     <td> 15x2, 1.25-mm connector for power measurement
 * <tr><td align="center"> 3
 *     <td align="center"> J106
 *     <td> Power measurement
 *     <td> 10x2, 1.25-mm connector for power measurement
 * <tr><td align="center"> 4
 *     <td align="center"> J127
 *     <td> PCIe x1
 *     <td> Standard PCIe x1 card edge connector
 * <tr><td align="center"> 5
 *     <td align="center"> J50
 *     <td> Ethernet
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * <tr><td align="center"> 6
 *     <td align="center"> J51
 *     <td> Ethernet1
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * <tr><td align="center"> 7
 *     <td align="center"> J69
 *     <td> JTAG connector
 *     <td> 10x2, 2.54-mm connector for JTAG
 * <tr><td align="center"> 8
 *     <td align="center"> J19
 *     <td> Secure digital input / output (SDIO)
 *     <td> Micro-secure digital (SD) socket for SDIO1 I/F
 * <tr><td align="center"> 9
 *     <td align="center"> J11
 *     <td> SD
 *     <td> SD multi-media card (MMC) socket for SD I/F
 * <tr><td align="center"> 10
 *     <td align="center"> BAT2
 *     <td> Real-time clock (RTC) battery holder
 *     <td> 2032 battery holder for the RTC
 * <tr><td align="center"> 11
 *     <td align="center"> J13
 *     <td> SDIO0
 *     <td> SD socket for SDIO0 I/F
 * <tr><td align="center"> 12
 *     <td align="center"> J72
 *     <td> Microcontroller unit (MCU) SWD connector
 *     <td> 5x2, 2.54-mm connector for the MCU debug tool
 * <tr><td align="center"> 13
 *     <td align="center"> J75
 *     <td> MCU reset button
 *     <td> Button to reset the MCU
 * <tr><td align="center"> 14
 *     <td align="center"> SW13
 *     <td> Reset button
 *     <td> Button to initiate system
 * <tr><td align="center"> 15
 *     <td align="center"> SW20
 *     <td> MCU power-on button
 *     <td> Button to indicate the MCU to power-on the system
 * <tr><td align="center"> 16
 *     <td align="center"> SW23
 *     <td> Power ON / OFF switch
 *     <td> Button to make the system switch between the power-on and<br>
 *          power-off states when the external power sequencer is used
 * <tr><td align="center"> 17
 *     <td align="center"> J78
 *     <td> Power jack
 *     <td> 12-V system power adapter input, 2.5 mm
 * <tr><td align="center"> 18
 *     <td align="center"> J42
 *     <td> Audio line-in
 *     <td> 3.5-mm audio jack
 * <tr><td align="center"> 19
 *     <td align="center"> J59
 *     <td> Audio HP out
 *     <td> 3.5-mm audio jack
 * <tr><td align="center"> 20
 *     <td align="center"> J55
 *     <td> Audio speaker out
 *     <td> 3.5-mm audio jack
 * <tr><td align="center"> 21
 *     <td align="center"> SW14~SW18
 *     <td> Analog-to-digital (ADC) key buttons
 *     <td> Key buttons in ADC1 to simulate menu / direction buttons
 * <tr><td align="center"> 22
 *     <td align="center"> SW19
 *     <td> Key button
 *     <td> Key button for the general purpose input / output (GPIO) debug
 * <tr><td align="center"> 23
 *     <td align="center"> U91
 *     <td> IR input
 *     <td> IR receiver
 * <tr><td align="center"> 24
 *     <td align="center"> J47
 *     <td> CVBS output
 *     <td> Mono RCA jack
 * <tr><td align="center"> 25
 *     <td align="center"> J25
 *     <td> USB 2.0 device / serial debug port
 *     <td> Micro-B USB receptacle
 * <tr><td align="center"> 26
 *     <td align="center"> J29
 *     <td> USB 3.2 device
 *     <td> Micro-B USB 3.0 receptacle
 * <tr><td align="center"> 27
 *     <td align="center"> J31
 *     <td> USB 3.2 host
 *     <td> Type-A USB 3.0 receptacle
 * <tr><td align="center"> 28
 *     <td align="center"> J32
 *     <td> USB 3.2 hub host
 *     <td> Type-C USB 3.0 receptacle
 * <tr><td align="center"> 29
 *     <td align="center"> J33 / J34 / J35
 *     <td> USB 3.2 hub host
 *     <td> Type-A USB 3.0 receptacle
 * <tr><td align="center"> 30
 *     <td align="center"> J39
 *     <td> VIN SLVS+DPHY
 *     <td> 164-pin PCIe connector for VIN SLVS+DPHY
 * <tr><td align="center"> 31
 *     <td align="center"> J43
 *     <td> VIN DCPHY
 *     <td> 41-pin, 0.5-mm connector for VIN DCPHY
 * <tr><td align="center"> 32
 *     <td align="center"> SW6~SW9
 *     <td> Power on configuration (POC) switch
 *     <td> 2-SPST / 4-SPST / 8-SPST switches for POC setting
 * <tr><td align="center"> 33
 *     <td align="center"> J48 / J49
 *     <td> VOUT MIPI DSI A / B
 *     <td> 40-pin, 0.5-mm FPC connector for VOUT MIPI DSI
 * <tr><td align="center"> 34
 *     <td align="center"> SW1~SW4
 *     <td> PINMUX switch
 *     <td> 4-SPST switches for PINMUX selection
 * <tr><td align="center"> 35
 *     <td align="center"> J46
 *     <td> HDMI transmit (TX)
 *     <td> Vertical HDMI receptacle
 * <tr><td align="center"> 36
 *     <td align="center">SW1,SW4,SW36
 *     <td> IMU
 *     <td> IMU in data ready interrupt mode
 * </table>
 *
 * @subsection cv72_ga_system_io_configurations 4.2 System I/O Configurations
 *
 * The CV72 Ga EVK board supplies abundant I/O interfaces for a variety of applications.
 * Ensure that the system I/O interfaces are properly configured with the on-board hardware
 * jumpers and switches.<br>
 *
 * The figure below provides the locations of the jumpers and switches listed in this chapter.<br>
 *
 * @image html cv72_ga_major_jumpers_for_system_io_on_the_top_side.png "Figure 4-2. Major Jumpers for the System I/O Configurations on the Top Side of the CV72 Ga EVK Ga (LPDDR5) Board."
 *
 * @subsubsection cv72_ga_system_io_can_bus 4.2.1 CAN Bus
 *
 * J76 is a 2x2, 2.54-mm connector for the CAN bus. J77 is a jumper that enables the CAN
 * transceiver. In normal mode, assemble the jumper on J77.<br>
 *
 *   - SW21 = OFF: Select CAN0 (default)
 *   - SW21 = ON: Select CAN1
 *
 * @image html cv72_ga_jumpers_and_switches_for_can_bus.png "Figure 4-3. Jumpers and Switches for CAN."
 *
 * @subsubsection cv72_ga_system_io_power_measurement 4.2.2 Power Measurement
 *
 * J105 and J106 are designed for power measurement. J105 and J106 have 30 / 20 pins and
 * 1.25-mm pitch connectors with a customized PIN-out. Contact the Ambarella support team
 * for more details.<br>
 *
 * @subsubsection cv72_ga_system_io_pcie_x1 4.2.3 PCIe x1
 *
 * J127 is a standard 64-pin PCIe x1 card edge connector.<br>
 *
 * The PCIe reference clock is generated from the PCIe clock generator PI6CG18401, which can be
 * configured through SW22.<br>
 *
 *   - SW22.pin1 = OFF: Disable the SuperSpeed (SS) function (default)
 *   - SW22.pin1 = ON: Enable the SS function at -0.5% spread
 *   - SW22.pin2 = OFF: Power on the PCIe clock generator (default)
 *   - SW22.pin2 = ON: Power down the PCIe clock generator
 *
 * @image html cv72_ga_jumpers_and_switches_for_pcie_x1.png "Figure 4-4. Jumpers and Switches for PCIe x1."
 *
 * @subsubsection cv72_ga_system_io_ethernet 4.2.4 Ethernet
 *
 * The CV72 Ga EVK board supports 1.8-V I/O between the media access control (MAC) and the PHY.<br>
 *
 * CV72 requires a 125-MHz reference clock if GMAC functions. The 125-MHz clock can be chosen
 * from the external oscillator or from GPHY. They can be chosen through switch SW30.<br>
 *
 *   - SW30 = OFF: Select 125-MHz clock from external oscillator (default)
 *   - SW30 = ON: Select 125-MHz clock from GPHY
 *
 * @image html cv72_ga_jumpers_and_switches_for_eth0_125mhz_clock.png "Figure 4-5. Jumpers and Switches for Ethernet 125-MHz Clock."
 *
 * Both GPHYs RTL8211 can supply the 125-MHz reference clock to the MAC. Use switch SW10 pin 1
 * to choose which is used.<br>
 *
 *   - SW10.pin1 = OFF: Select 125-MHz clock from GPHY RTL8211 (default)
 *   - SW10.pin1 = ON: Select 125-MHz clock from GPHY1 RTL8211
 *
 * J50 is a 10 / 100 / 1000 Base-T Ethernet single-port RJ45 connector with LEDs (link / act).
 * The CV72 ENET0 MAC supports the RGMII / RMII interfaces and the MDC / MDIO management interface
 * to the external Ethernet PHY.<br>
 *
 * Both Giga PHY RTL8211 and Mega PHY RTL8201 are assembled on the board. RTL8211 is connected
 * to CV72 through RGMII I/F, and RTL8201 is connected to CV72 through RMII I/F. Only one can
 * be used at a time. Use switch SW10 pin2 to choose which is used.<br>
 *
 *   - SW10.pin2 = OFF: Enable GPHY RTL8211 (default)
 *   - SW10.pin2 = ON: Enable MPHY RTL8201
 *
 * @image html cv72_ga_jumpers_and_switches_for_eth0.png "Figure 4-6. Jumpers and Switches for Ethernet."
 *
 * @subsubsection cv72_ga_system_io_ethernet_1 4.2.5 Ethernet 1
 *
 * J51 is a 10 / 100 / 1000 Base-T Ethernet single port RJ45 connector with LEDs (link / act).
 * The CV72 ENET1 MAC supports the RGMII / RMII interfaces and the MDC / MDIO management
 * interface to the external Ethernet PHY.<br>
 *
 * Both Giga PHY RTL8211 and Mega PHY RTL8201 are assembled on the board. RTL8211 is connected
 * to the CV72 through RGMII I/F, and RTL8201 is connected to the CV72 through RMII I/F. Only
 * one can be used at a time.  Use switch SW11 to choose which is used.<br>
 *
 *   - SW11 = OFF: Enable GPHY1 RTL8211 (default)
 *   - SW11 = ON: Enable MPHY1 RTL8201
 *
 * @image html cv72_ga_jumpers_and_switches_for_ethernet_1.png "Figure 4-7. Jumpers and Switches for Ethernet 1."
 *
 * @subsubsection cv72_ga_system_io_jtag_connector 4.2.6 JTAG Connector
 *
 * J60 is a 10x2, 2.54-mm connector for the JTAG debugging.<br>
 *
 * @subsubsection cv72_ga_system_io_sdio1 4.2.7 SDIO1
 *
 * SDIO1 is available in J19, which is a micro-SD socket on the top side.<br>
 * J20 is used to control the J19 VDD (3.3 V).<br>
 *
 *   - J20 pin2-3 ON: Enable software control on the VDD (default)
 *   - J20 pin1-2 ON: Make the VDD always-on
 *
 * @image html cv72_ga_jumpers_and_switches_for_sdio1_j20.png "Figure 4-8. Jumpers and Switches for J20."
 *
 * When an SD memory card is used in J19:<br>
 *
 *   - Jumper on J22 must be assembled
 *   - Jumper on J24 must not be assembled
 *
 * When an SD I/O card is used in J19:<br>
 *
 *   - Jumper on J22 must not be assembled
 *   - Jumper on J24 must be assembled to select SDIO0 I/O voltage
 *     - J24.pin1-2: SDIO1_VDDO = 1.8 V
 *     - J24.pin2-3: SDIO1_VDDO = 3.3 V
 *
 * @image html cv72_ga_jumpers_and_switches_for_sdio1_j22_j24.png "Figure 4-9. Jumpers and Switches for J22 and J24."
 *
 * @subsubsection cv72_ga_system_io_sd 4.2.8 SD
 *
 * SD could be switched to the on-board embedded multi-media controller (eMMC) as a boot source or the MMC socket J11
 * to SD memory card and I/O card by SW31.<br>
 *
 *   - SW31 = OFF: SD bus is connected to the MMC socket J11 (default)
 *   - SW31 = ON: SD bus is connected to the on-board embedded multi-media controller / card (eMMC)
 *
 * @image html cv72_ga_jumpers_and_switches_for_sd.png "Figure 4-10. Jumpers and Switches for SD."
 *
 * When J11 is selected:<br>
 * J123 is used to control the J11 VDD (3.3 V).<br>
 *   - J123 pin2-3 ON: Enable software control on the VDD (default)
 *   - J123 pin1-2 ON: Make the VDD always on
 *
 * @image html cv72_ga_jumpers_and_switches_for_j123.png "Figure 4-11. Jumpers and Switches for J123."
 *
 * When an SD memory card is used in J11:<br>
 *
 *   - Jumper on J126 must not be assembled
 *   - Jumper on J8 must not be assembled
 *
 * When an SD I/O card is used in J11:<br>
 *
 *   - Jumper on J126 must not be assembled
 *   - Jumper on J8 must be assembled to select SDIO0 I/O voltage
 *
 *     - J8.pin1-2: SD_VDDO = 1.8 V
 *     - J8.pin2-3: SD_VDDO = 3.3 V
 *
 * @image html cv72_ga_jumpers_and_switches_for_sd_j126_j8.png "Figure 4-12. Jumpers and Switches for J126 and J8."
 *
 * When eMMC is selected:<br>
 * J7 is used to select eMMC VCC and J8 is used to select eMMC VCCQ.<br>
 *
 * This table provides the eMMC VCC and eMMC VCCQ configuration by J7 / J8.<br>
 *
 * <table>
 * <caption id="cv72_ga_eMMc_VCC_and_eMMc_VCCQ_configuration">Table 4-2. CV72 eMMC VCC and eMMC VCCQ (CV72 SD_VDDO) Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Power Rail <th width="165px"> Jumpers <th width="200px"> Power Rail Value (V)
 * <tr><td align="center" rowspan="2"> J7
 *     <td align="center" rowspan="2"> eMMC VCC
 *     <td align="center"> 1-2
 *     <td align="center"> 1.8 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> 3.3 V (Default)
 * <tr><td align="center" rowspan="2"> J8
 *     <td align="center" rowspan="2"> eMMC VCCQ<br>
 *     (CV72 SD_VDD0)
 *     <td align="center"> 1-2
 *     <td align="center"> 1.8 V (Default)
 * <tr><td align="center"> 2-3
 *     <td align="center"> 3.3 V
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_emmc_vcc_vccq.png "Figure 4-13. Jumpers and Switches for eMMC VCC and eMMC VCCQ."
 *
 * @subsubsection cv72_ga_system_io_rtc_battery_holder 4.2.9 RTC Battery Holder
 *
 * BAT2 is a 2032 battery holder for the CV72 RTC block. By default, the battery is not assembled.
 * Ensure correct battery polarity during assembly.<br>
 *
 * @subsubsection cv72_ga_system_io_sdio0 4.2.10 SDIO0
 *
 * SDIO0 is available in J13 on the side, which is an SD socket.<br>
 *
 * J14 is used to control the J13 VDD (3.3 V).<br>
 *
 *   - J14 pin2-3 ON: Enable software control on the VDD (default)
 *   - J14 pin1-2 ON: Make the VDD always on
 *
 * @image html cv72_ga_jumpers_and_switches_for_sdio0_j14.png "Figure 4-14. Jumpers and Switches for J14."
 *
 * When an SD memory card is used in J13:<br>
 *
 *   - Jumper on J16 must be assembled
 *   - Jumper on J18 must not be assembled
 *
 * When an SD I/O card is used in J13:<br>
 *
 *   - Jumper on J16 must not be assembled
 *   - Jumper on J18 must be assembled to select SDIO0 I/O voltage
 *     - J18.pin1-2: SDIO0_VDDO = 1.8 V
 *     - J18.pin2-3: SDIO0_VDDO = 3.3 V
 *
 * @image html cv72_ga_jumpers_and_switches_for_sdio0_j16_j18.png "Figure 4-15. Jumpers and Switches for J16 and J18."
 *
 * @subsubsection cv72_ga_system_io_mcu_swd_connector 4.2.11 MCU SWD Connector
 *
 * J72 is a 5x2, 2.54-mm connector for the MCU debug tool. It supports only a 2-pin serial wire debug (SWD) function.<br>
 *
 * @subsubsection cv72_ga_system_io_mcu_reset_button 4.2.12 MCU Reset Button
 *
 * J75 is the MCU reset button, which triggers an active-low signal to assert a hardware reset
 * to the MCU.<br>
 *
 * @subsubsection cv72_ga_system_io_reset_button 4.2.13 Reset Button
 *
 * SW13 functions as the system reset button, which triggers an active-low signal to assert a
 * system reset to CV72 power-on reset (PoR) pin.<br>
 *
 * @subsubsection cv72_ga_system_io_mcu_power_on_button 4.2.14 MCU Power-on Button
 *
 * SW20 functions as a power-on button, which triggers an active-low signal to indicate a
 * power-on action to the MCU.  Ensure that the software has enabled this function in the MCU.<br>
 *
 * @subsubsection cv72_ga_system_io_power_on_off_switch_button 4.2.15 Power ON / OFF Switch Button
 *
 * SW23 functions as a system power ON / OFF switch button. Pressing SW23 powers on the system
 * if the system is in the OFF state, or powers off the system if the system is in the ON state.
 * Do not assemble a jumper on J79.  If there is a jumper on J79, it will bypass SW23.<br>
 *
 * @subsubsection cv72_ga_system_io_power_jack 4.2.16 Power Jack
 *
 * J78 is a standard 2.5-mm power jack for an external 12-V power adapter. Plugging the power
 * adapter through J78 supplies the power for the CV72 Ga EVK board.<br>
 *
 * @subsubsection cv72_ga_system_io_audio_line_in 4.2.17 Audio Line-in
 *
 * The on-board audio coder / decoder (codec) is NAU88C22.<br>
 * The CV72 CLK_AU signal could be chosen to output to NAU88C22 or to the external audio codec
 * through SW12.<br>
 *
 *   - Assemble the jumpers on J52 and J54
 *   - SW12 = OFF: Connect to NAU88C22 (default)
 *   - SW12 = ON: Connect to the external audio codec
 *
 * @image html cv72_ga_jumpers_and_switches_for_clk_au_to_audio_codec.png "Figure 4-16. Jumpers and Switches for CLK_AU to Audio Codec."
 *
 * The audio line-in is available in J42, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv72_ga_system_io_audio_hp_out 4.2.18 Audio HP out
 *
 * The audio HP out is available in J59, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv72_ga_system_io_audio_speaker_out 4.2.19 Audio Speaker Out
 *
 * The audio speaker out is available in J55, which is a 3.5-mm audio jack.<br>
 *
 * @subsubsection cv72_ga_system_io_adc1_key_button 4.2.20 ADC1 Key Buttons
 *
 * SW14~SW18 are key buttons to simulate menu / direction buttons. Ensure that the software has
 * this function enabled in ADC1.<br>
 *
 * @subsubsection cv72_ga_system_io_gpio_debug 4.2.21 GPIO Debug
 *
 * SW19 is a key button for software general purpose input / output (GPIO) debugging. SW19 is connected to GPIO44, which includes
 * a default pull-high hardware. The software can configure GPIO44 to verify the general
 * input / output function. Pressing SW19 will assert low to GPIO44.<br>
 *
 *   - SW4.pin3 = OFF: Connect GPIO44 to SW19
 *
 * @image html cv72_ga_jumpers_and_switches_for_gpio44_debug.png "Figure 4-17. Jumpers and Switches for GPIO Debug (GPIO44)."
 *
 * @subsubsection cv72_ga_system_io_ir_receiver 4.2.22 IR Receiver
 *
 * U91 is an IR receiver module for the infrared remote control systems with a 38-kHz
 * carrier frequency.<br>
 *
 * @subsubsection cv72_ga_system_io_cvbs_output 4.2.23 CVBS Output
 *
 * J47 is a mono RCA jack for CVBS output.<br>
 *
 * @subsubsection cv72_ga_system_io_usb_20_device_serial_debug_port 4.2.24 USB 2.0 Device / Serial Debug Port
 *
 * J25 is a micro-B USB receptacle. USB0 I/F functions in device mode only. Plug the USB cable
 * from the USB host to J25. The AmbaUSB tool functions in this mode. J25 also serves as a serial
 * debug port because a USB-to-UART chip is used to perform the interface conversion.<br>
 *
 * @subsubsection cv72_ga_system_io_usb_32_device 4.2.25 USB 3.2 Device
 *
 * J29 is a micro-B USB 3.2 receptacle.  When USB1 I/F is in device mode, plug the USB host to J29.<br>
 * It can be chosen through SW32=ON.<br>
 *
 *   - SW32 = OFF: USB 3.2 is in host mode (default)
 *   - SW32 = ON: USB 3.2 is in device mode to J29
 *
 * @image html cv72_ga_jumpers_and_switches_for_sw32.png "Figure 4-18. Jumpers and Switches for SW32."
 *
 * @subsubsection cv72_ga_system_io_usb_32_host 4.2.26 USB 3.2 host
 *
 * J31 is a type-A USB 3.2 receptacle.  When USB1 I/F is in host mode, plug the USB device to J31.<br>
 * It can be chosen through SW32=OFF and SW35=ON.<br>
 *
 *   - SW35 = OFF: USB 3.2 is in host mode through USB hub (default)
 *   - SW35 = ON: USB 3.2 is in host mode to J31
 *
 * @image html cv72_ga_jumpers_and_switches_for_sw35.png "Figure 4-19. Jumpers and Switches for SW35."
 *
 * @subsubsection cv72_ga_system_io_usb_32_hub_host 4.2.27 USB 3.2 Hub Host
 *
 * J32 is a type-C USB 3.2 receptacle, and J33~J35 are type-A USB 3.2 receptacles from the on-board USB 3.2 hub.
 * When USB1 I/F functions in host mode and is connected through the USB 3.2 hub, J32~J36 will be available.<br>
 * They can be chosen through SW32=OFF and SW35=OFF.<br>
 *
 * @subsubsection cv72_ga_system_io_vin_slvs_dcphy 4.2.28 VIN SLVS+DPHY
 *
 * J39 is a standard 164-pin, PCIe connector for the VIN SLVS+DPHY. J39 is a customized pin-out
 * connector. Check the reference design for details.<br>
 *
 * @subsubsection cv72_ga_system_io_vin_dcphy 4.2.29 VIN DCPHY
 *
 * J43 is a 41-pin, 0.5-mm pitch, 3.8-mm height connector for the VIN DCPHY I/Fs. It is a customized
 * pin-out connector.  Check the reference design for more details.<br>
 *
 * @subsubsection cv72_ga_system_io_poc_switch_sw6_sw9 4.2.30 POC Switch - SW6~SW9
 *
 * The table below shows the CV72 POC setup in SW6~SW9. Contact the Ambarella support team for
 * the POC user guide.<br>
 *
 * <table>
 * <caption id="cv72_ga_evk_poc_setup">Table 4-3. CV72 Ga EVK POC Setup.</caption>
 * <tr><th width="120px"> Designator <th width="85px"> Pins <th width="240px"> Notes
 * <tr><td align="center" rowspan="8"> SW6
 *     <td align="center"> pin A1
 *     <td> POC[21]=HSM BOOT
 * <tr><td align="center"> pin A2
 *     <td> POC[1]=CLK_FRE[0]
 * <tr><td align="center"> pin A3
 *     <td> POC[2]=CLK_FRE[1]
 * <tr><td align="center"> pin A4
 *     <td> POC[3]=CLK_FRE[2]
 * <tr><td align="center"> pin A5
 *     <td> POC[4]=BOOT_MODE[0]
 * <tr><td align="center"> pin A6
 *     <td> POC[5]=BOOT_MODE[1]
 * <tr><td align="center"> pin A7
 *     <td> POC[6]=SECURE BOOT
 * <tr><td align="center"> pin A8
 *     <td> POC[13]=BOOT_OPTION[0]
 * <tr><td align="center" rowspan="8"> SW7
 *     <td align="center"> pin A1
 *     <td> POC[16]=BOOT_OPTION[3]
 * <tr><td align="center"> pin A2
 *     <td> POC[17]=BOOT_OPTION[4]
 * <tr><td align="center"> pin A3
 *     <td> POC[18]=BOOT_OPTION[5]
 * <tr><td align="center"> pin A4
 *     <td> POC[19]=BOOT_OPTION[6]
 * <tr><td align="center"> pin A5
 *     <td> POC[20]=BOOT_OPTION[7]
 * <tr><td align="center"> pin A6
 *     <td> POC[8]=BOOT_BYPASS
 * <tr><td align="center"> pin A7
 *     <td> POC[31]=SYSCONFIG_SRC
 * <tr><td align="center"> pin A8
 *     <td> RESERVED
 * <tr><td align="center" rowspan="2"> SW8
 *     <td align="center"> pin A1
 *     <td> POC[14]=BOOT_OPTION[1]
 * <tr><td align="center"> pin A2
 *     <td> POC[15]=BOOT_OPTION[2]
 * <tr><td align="center"> SW9
 *     <td align="center"> pin A1
 *     <td> POC[10]=FORCE_USB_BOOT
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_poc_sw6_sw9.png "Figure 4-20. Jumpers and Switches for POC."
 *
 * @subsubsection cv72_ga_system_io_vout_mipi_dsi 4.2.31 VOUT MIPI DSI
 *
 * J48 and J49 are two 20x2, 0.5-mm FFC / FPC connectors for MIPI DSI A and B output. They
 * are customized pin-out connectors. Check the reference design for more details.<br>
 *
 * @subsubsection cv72_ga_system_io_pinmux_switch_sw1_sw4 4.2.32 PINMUX Switch – SW1~SW4
 *
 * SW1~SW4 are 4-SPST switches used for PINMUX selection.<br>
 *
 * The table below shows a summary of the PINMUX switches. Refer to each sector for details.<br>
 *
 * <table>
 * <caption id="cv72_ga evk_mux_configurations">Table 4-4. CV72 Ga EVK PINMUX Configurations.</caption>
 * <tr><th> Switch <th> Pin <th> Status <th> Function <th> Description
 * <tr><td align="center" rowspan="32"> SW1
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO2 as GPIO2
 *     <td> GPIO2 to external audio codec connector
 * <tr><td> GPIO3 as GPIO3
 *     <td> GPIO3 to external audio codec connector
 * <tr><td> GPIO4 as IDC1_CLK
 *     <td> IDC1 to external audio ccodec / VOUT DSI_A / HCSL clock
 * <tr><td> GPIO5 as IDC1_DATA
 *     <td> IDC1 to external audio codec / VOUT DSI_A / HCSL clock
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO2 as SSI0_CLK
 *     <td> SSI0_CLK
 * <tr><td> GPIO3 as SSI0_MOSI
 *     <td> SSI0_MOSI
 * <tr><td> GPIO4 as SSI0_MISO
 *     <td> SSI0_MISO
 * <tr><td> GPIO5 as SSI0_MISO
 *     <td> SSI0_EN0 to VIN DCPHY
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO6 as SSI0_EN1
 *     <td> SSI0_EN1 to debug connector
 * <tr><td> GPIO45 as SSI0_EN4
 *     <td> SSI0_EN4 to VOUT DSI_A
 * <tr><td> GPIO46 as SSI0_EN5
 *     <td> SSI0_EN5 to VOUT DSI_B
 * <tr><td> GPIO47 as PWM2
 *     <td> PWM2 to VIN DCPHY
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO6 as PWM7
 *     <td> PWM7 to IRIS connector
 * <tr><td> GPIO45 as GPIO45
 *     <td> GPIO45 to Flash connector
 * <tr><td> GPIO46 as GPIO46
 *     <td> GPIO46 to Flash connector
 * <tr><td> GPIO47 as GPIO47
 *     <td> GPIO47 to Flash connector
  * <tr><td align="center" rowspan="8"> Pin3
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO7 as SSI1_CLK
 *     <td> SSI1_CLK
 * <tr><td> GPIO8 as SSI1_MOSI
 *     <td> SSI1_MOSI
 * <tr><td> GPIO9 as SSI1_MISO
 *     <td> SSI1_MISO
 * <tr><td> GPIO10 as SSI1_EN0
 *     <td> SSI1_EN0 to VIN SLVS+DPHY
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO7 as GPIO7
 *     <td> GPIO7 to VOUT DSI_A
 * <tr><td> GPIO8 as GPIO8
 *     <td> GPIO8 to VOUT DSI_A
 * <tr><td> GPIO9 as GPIO9
 *     <td> GPIO9 to VOUT DSI_B
 * <tr><td> GPIO10 as GPIO10
 *     <td> GPIO10 to VOUT DSI_B
 * <tr><td align="center" rowspan="8"> Pin4
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO11 as SSI2_CLK
 *     <td> SSI2_CLK
 * <tr><td> GPIO12 as SSI2_MOSI
 *     <td> SSI2_MOSI
 * <tr><td> GPIO13 as SSI2_MISO
 *     <td> SSI2_MISO
 * <tr><td> GPIO14 as SSI2_EN0
 *     <td> SSI2_EN0 to Gyro sensor
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO11 as GPIO11
 *     <td> GPIO11 to VIN SLVS+DPHY
 * <tr><td> GPIO12 as GPIO12
 *     <td> GPIO12 to VIN SLVS+DPHY
 * <tr><td> GPIO13 as GPIO13
 *     <td> GPIO13 to VIN SLVS+DPHY
 * <tr><td> GPIO14 as GPIO14
 *     <td> GPIO14 to VIN SLVS+DPHY
 * <tr><td align="center" rowspan="28"> SW2
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO15 as GPIO15
 *     <td> GPIO15 to / from MCU
 * <tr><td> GPIO16 as GPIO16
 *     <td> GPIO16 to / from MCU
 * <tr><td> GPIO17 as GPIO17
 *     <td> GPIO17 to / from MCU
 * <tr><td> GPIO18 as GPIO18
 *     <td> GPIO18 to / from MCU
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO15 as SSIS_CLK or TCC
 *     <td> SSIS_CLK or TCC
 * <tr><td> GPIO16 as SSIS_TXD or TCC
 *     <td> SSIS_TXD or TCC
 * <tr><td> GPIO17 as SSIS_RXD or TCC
 *     <td> SSIS_RXD or TCC
 * <tr><td> GPIO18 as SSIS_EN or TCC
 *     <td> SSIS_EN or TCC to debug connector
 * <tr><td align="center" rowspan="4"> Pin2
 *     <td align="center" rowspan="2"> OFF
 *     <td> GPIO19 as IDC0_CLK or I3C_CLK
 *     <td> IDC0 or I3C to VIN SLVS+DPHY / DCPHY / Gyro sensor
 * <tr><td> GPIO20 as IDC0_DATA or I3C_DATA
 *     <td> IDC0 or I3C to VIN SLVS+DPHY / DCPHY / Gyro sensor
  * <tr><td align="center" rowspan="2"> ON
 *     <td> GPIO19 as IDCS_CLK
 *     <td> IDCS_CLK to debug connector
 * <tr><td> GPIO20 as IDCS_DATA
 *     <td> IDCS_DATA to debug connector
 * <tr><td align="center" rowspan="8"> Pin3
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO21 as VSYNC0
 *     <td> VSYNC0 to VIN SLVS+DPHY
 * <tr><td> GPIO22 as VSYNC1
 *     <td> VSYNC1 to VIN DCPHY
 * <tr><td> GPIO25 as HSYNC0
 *     <td> HSYNC0 to VIN SLVS+DPHY
 * <tr><td> GPIO26 as HSYNC1
 *     <td> HSYNC1 to VIN DCPHY
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO21 as GPIO21
 *     <td> GPIO21 to UART0 debug connector
 * <tr><td> GPIO22 as GPIO22
 *     <td> GPIO22 to UART0 debug connector
 * <tr><td> GPIO25 as GPIO25
 *     <td> GPIO25 to UART1 debug connector
 * <tr><td> GPIO26 as GPIO26
 *     <td> GPIO26 to UART1 debug connector
 * <tr><td align="center" rowspan="8"> Pin4
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO23 as GPIO23
 *     <td> GPIO23 to USB0_ID
 * <tr><td> GPIO24 as GPIO24
 *     <td> GPIO24 to USB1_ID
 * <tr><td> GPIO115 as GPIO115
 *     <td> GPIO115 from ENET PHY_INTn
 * <tr><td> GPIO116 as GPIO116
 *     <td> GPIO116 from ENET1 PHY_INTn
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO23 as VSYNC2
 *     <td> VSYNC2 to Gyro sensor
 * <tr><td> GPIO24 as VSYNC3
 *     <td> VSYNC3 to test point
 * <tr><td> GPIO115 as IDC0_CLK
 *     <td> backup IDC0_CLK to debug connector
 * <tr><td> GPIO116 as IDC0_DATA
 *     <td> backup IDC0_CLK to debug connector
 * <tr><td align="center" rowspan="20"> SW3
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO27 as PWM9
 *     <td> PWM9 to VOUT DSI_A/B
 * <tr><td> GPIO28 as PWM10
 *     <td> PWM10 to VOUT DSI_A/B
 * <tr><td> GPIO29 as PWM11
 *     <td> PWM11 to VIN SLVS+DPHY
 * <tr><td> GPIO30 as SSI1_EN1
 *     <td> SSI1_EN1 or VIN SLVS+DPHY
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO27 as EXT_VSYNC_IN
 *     <td> EXT_HSYNC_IN to test point
 * <tr><td> GPIO28 as EXT_HSYNC_IN
 *     <td> EXT_HSYNC_IN to test point
 * <tr><td> GPIO29 as VIN_STRIG0
 *     <td> VIN_STRIG0 to test point
 * <tr><td> GPIO30 as VIN_STRIG1
 *     <td> VIN_STRIG1 to test point
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO33 as GPIO33
 *     <td> GPIO33 to VIN SLVS+DPHY
 * <tr><td> GPIO34 as GPIO34
 *     <td> GPIO34 to VIN SLVS+DPHY
 * <tr><td> GPIO35 as GPIO35
 *     <td> GPIO35 to VIN SLVS+DPHY
 * <tr><td> GPIO36 as GPIO36
 *     <td> GPIO36 to VIN SLVS+DPHY
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO33 as UART0_RX
 *     <td> UART0_RX to UART0 debug connector
 * <tr><td> GPIO34 as UART0_TX
 *     <td> UART0_TX to UART0 debug connector
 * <tr><td> GPIO35 as UART0_CTSn
 *     <td> UART0_CTSn to UART0 debug connector
 * <tr><td> GPIO36 as UART0_RTSn
 *     <td> UART0_RTSn to UART0 debug connector
 * <tr><td align="center" rowspan="2"> Pin3
 *     <td align="center"> OFF
 *     <td> GPIO0 as IR_IN
 *     <td> IR_IN to IR receiver
 * <tr><td align="center"> ON
 *     <td> GPIO0 as WDT_EXT_RST
 *     <td> WDT_EXT_RST to RESET IC as manual reset
 * <tr><td align="center" rowspan="2"> Pin4
 *     <td align="center"> OFF
 *     <td> GPIO1 as GPIO1
 *     <td> GPIO1 to EXGPIO INTn
 * <tr><td align="center"> ON
 *     <td> GPIO1 as TM11_CLK
 *     <td> TM11_CLK to test point
 * <tr><td align="center" rowspan="24"> SW4
 *     <td align="center" rowspan="8"> Pin1
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO37 as GPIO37
 *     <td> GPIO37 to VIN DCPHY
 * <tr><td> GPIO38 as GPIO38
 *     <td> GPIO38 to VIN DCPHY
 * <tr><td> GPIO39 as GPIO39
 *     <td> GPIO39 to VIN DCPHY
 * <tr><td> GPIO40 as GPIO40
 *     <td> GPIO40 to VIN DCPHY
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO37 as UART1_RX
 *     <td> UART1_RX to UART1 debug connector
 * <tr><td> GPIO38 as UART1_TX
 *     <td> UART1_TX to UART1 debug connector
 * <tr><td> GPIO39 as UART1_CTSn
 *     <td> UART1_CTSn to UART1 debug connector
 * <tr><td> GPIO40 as UART1_RTSn
 *     <td> UART1_RTSn to UART1 debug connector
 * <tr><td align="center" rowspan="8"> Pin2
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO41 as IDC3_CLK
 *     <td> IDC3 to GPIO EXPANDER / RTC / VOUT DSI_B / VIN SLVS+DPHY / Audio Codec
 * <tr><td> GPIO42 as IDC3_DATA
 *     <td> IDC3 to GPIO EXPANDER / RTC / VOUT DSI_B / VIN SLVS+DPHY / Audio Codec
 * <tr><td> GPIO43 as GPIO43
 *     <td> GPIO43 to PCIex1 Slot
 * <tr><td> GPIO44 as GPIO44
 *     <td> GPIO44 to debug button
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO41 as CAN0_RX
 *     <td> CAN0_RX
 * <tr><td> GPIO42 as CAN0_TX
 *     <td> CAN0_TX
 * <tr><td> GPIO43 as CAN1_RX
 *     <td> CAN1_RX
 * <tr><td> GPIO44 as CAN1_TX
 *     <td> CAN1_TX
 * <tr><td align="center" rowspan="8"> Pin3
 *     <td align="center" rowspan="4"> OFF
 *     <td> GPIO48 as DMIC_CLK
 *     <td> DMIC_CLK
 * <tr><td> GPIO49 as DMIC_DAT
 *     <td> DMIC_DAT
 * <tr><td> GPIO50 as GPIO50
 *     <td> GPIO50 to VIN DCPHY
 * <tr><td> GPIO51 as GPIO51
 *     <td> GPIO51 to Gyro INTn
 * <tr><td align="center" rowspan="4"> ON
 *     <td> GPIO48 as I2S_CLK
 *     <td> I2S to external audio codec connector
 * <tr><td> GPIO49 as I2S_SI
 *     <td> I2S to external audio codec connector
 * <tr><td> GPIO50 as I2S_SO
 *     <td> I2S to external audio codec connector
 * <tr><td> GPIO51 as I2S_WS
 *     <td> I2S to external audio codec connector
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_sw1_sw4.png "Figure 4-21. Jumpers and Switches for SW1~SW4."
 *
 * @subsubsection cv72_ga_system_io_poc_table 4.2.33 CV72 POC Table
 *
 * <table>
 * <caption id="cv72_ga_evk_poc_table">Table 4-5 CV72 POC Table.</caption>
 * <tr><th> POC bit <th> PIN Name <th colspan="5"> Description <th> EVK Default
 * <tr><td> POC[3:1]
 *     <td> ENET_TXD[3:1]
 *     <td colspan = "5"> IDSP/CORE/DDR Clock config <br>
 *          VDSP/CORE/IDSP/VISION/CORTEX/NAND(contact for below frequency setting) <br>
 *          000: 1104 /  912 / 1296 /  792 / 1440 / 528 Mhz <br>
 *          001: 1200 / 1080 / 1392 /  840 / 1584 / 528 Mhz <br>
 *          010:  684 /  684 /  828 /  912 / 1344 / 396 Mhz <br>
 *          011: 1080 /  888 / 1296 /  768 / 1416 / 504 Mhz <br>
 *          100:  888 /  864 / 1080 /  744 / 1416 / 480 Mhz <br>
 *          101:  768 /  624 /  912 /  528 / 1008 / 384 Mhz <br>
 *          110: 1080 /  912 / 1296 /  756 / 1440 / 528 Mhz <br>
 *          111:  432 /  432 /  432 /  432 /  432 / 264 Mhz
 *     <td> 111
 * <tr><td> POC[5:4]
 *     <td> ENET1_TXD[1:0]
 *     <td  colspan = "5"> Boot Mode [1:0] <br>
 *          00: SPINOR <br>
 *          01: SPINAND <br>
 *          10: eMMC <br>
 *          11: PCIe
 *     <td> 01
 * <tr><td> POC[6]
 *     <td> ENET1_TXD[2]
 *     <td  colspan = "5"> Secure boot: <br>
 *          0: Clear boot <br>
 *          1: Secure boot
 *     <td> 0
 * <tr><td> POC[8]
 *     <td> CLK_AU[8]
 *     <td  colspan = "5"> Boot Bypass: <br>
 *          0: disable <br>
 *          1: enable
 *     <td> 0
 * <tr><td> POC[10]
 *     <td> ENET_PTP_PPS
 *     <td  colspan = "5"> Force USB boot: <br>
 *          0: disable <br>
 *          1: enable
 *     <td> 0
 * <tr><td rowspan = "2"> [20:13]
 *     <td>
 *     <td colspan = "5"> Boot Options[7:0]
 *     <td>
 * <tr><td>
 *     <td> <b> Boot Option </b>
 *     <td> <b> SPI-NOR </b>
 *     <td> <b> NAND </b>
 *     <td> <b> eMMC </b>
 *     <td> <b> PCIe </b>
 *     <td>
 * <tr><td> POC[20]
 *     <td> SHSYNC
 *     <td> boot_option[7]
 *     <td>
 *     <td> <b> 32 BST code size Select </b> <br>
 *          0: Determined by boot_option[6] <br>
 *          1: 32K BST code size
 *     <td> <b> eMMC bst 32 </b> <br>
 *          POC[20, 17] <br>
 *          01:  8K BST code size <br>
 *          10: 32K BST code size <br>
 *          Otherwise: 4K BST code size
 *     <td>
 *     <td> 1
 * <tr><td> POC[19]
 *     <td> SVSYNC
 *     <td> boot_option[6]
 *     <td>
 *     <td> <b> 8K BST code size Select </b> <br>
 *          0: 4K BST code size <br>
 *          1: 8K BST code size
 *     <td> <b> tRSCA sel boot </b> <br>
 *          0: For tRSCA=75 SD clock cycles <br>
 *          1: For tRSCA=10000 SD clock cycles
 *     <td>
 *     <td>
 * <tr><td> POC[18]
 *     <td> PWM0
 *     <td> boot_option[5]
 *     <td>
 *     <td> <b> SCK Mode </b> <br>
 *          0: Mode 0 (CPOL = 0. CPHA = 0) <br>
 *          1: Mode 3 (CPOL = 1. CPHA = 1) <br>
 *     <td> <b> tRSC enable boot </b> <br>
 *          Set this value to 1 to delay the timing of boot initialization
 *     <td>
 *     <td> 0
 * <tr><td> POC[17]
 *     <td> ENET1_PTP_PPS
 *     <td> boot_option[4]
 *     <td>
 *     <td> <b> 4K/2K Page Select </b> <br>
 *          0: 4K-page <br>
 *          1: 2K-page
 *     <td> <b> eMMC bst 8K </b> <br>
 *          POC[20, 17] <br>
 *          01:  8K BST code size <br>
 *          10: 32K BST code size <br>
 *          Otherwise: 4K BST code size
 *     <td> Ref24
 *     <td> 1
 * <tr><td> POC[16]
 *     <td> I2S_SO_0
 *     <td> boot_option[3]
 *     <td> <b> SPI Mode Selection </b> <br>
 *          0: SPI mode 0 <br>
 *          1: SPI mode 1
 *     <td> <b> Skip ECC check for Blank </b> <br>
 *          0: Do not skip ECC check for blank pages <br>
 *          1: Skip ECC check for blank pages
 *     <td> <b> eMMC boot sd pull </b> <br>
 *          When 0: No pull on sd_cmd and sd_d[7:0] <br>
 *          When 1: Interal pull high on sd_cmd and sd_d[7:0]
 *     <td> DDR5
 *     <td> 1
 * <tr><td> POC[15]
 *     <td> UART_APB_TX
 *     <td> boot_option[2]
 *     <td> <b> Boot Mode[2] </b> <br>
 *          Take reference to table: @ref cv72_boot_mode_table
 *     <td> <b> NAND ECC BCH Enable </b> <br>
 *          Enable ECC BCH function or not
 *     <td> <b> 4-bit Bus Width </b> <br>
 *          Use 4 SD data pins for boot
 *     <td> Gen
 *     <td> 0
 * <tr><td> POC[14]
 *     <td> UART1_AHB_TX
 *     <td> boot_option[1]
 *     <td> <b> Boot Mode[1] </b> <br>
 *          Take reference to table: @ref cv72_boot_mode_table
 *     <td> <b> NAND Spare Cell 2x </b> <br>
 *          0: Support 1X NAND spare area <br>
 *             When NAND page size if 0: Spare area = 128 B <br>
 *             When NAND page size if 1: Spare area =  64 B <br>
 *          1: Support 2X NAND spare area <br>
 *             When NAND page size if 0: Spare area = 256 B <br>
 *             When NAND page size if 1: Spare area = 128 B
 *     <td> <b> 8-bit Bus Width </b> <br>
 *          Use 8 SD data pins for boot
 *     <td rowspan="2"> sub-mode[1:0]
 *     <td> 1
 * <tr><td> POC[13]
 *     <td> UART0_AHB_TX
 *     <td> boot_option[0]
 *     <td> <b> Boot Mode[0] </b> <br>
 *          Take reference to table: @ref cv72_boot_mode_table
 *     <td> <b> Flash Fast Boot </b> <br>
 *          0: Normal NAND flash component read cycle time <br>
 *          1: Shorter NAND flash component read cycle time
 *     <td> <b> hs boot </b> <br>
 *          0: Default-Speed Mode (12.5 MB/sec interface speed related for sd4_boot or 25 MB/sec interface speed for sd8_boot) <br>
 *          1: High-Speed Mode (25 MB/sec interface speed for sd4_boot, 50 MB/sec interface speed for sd8_boot)
 *     <td> 0
 * <tr><td> POC[31]
 *     <td> PWM1
 *     <td  colspan = "5"> Source of sys config data: <br>
 *          0: config data is set by pins <br>
 *          1: config data is read from on-chip efuse rom
 *     <td> 1
 * </table>
 *
 * <table>
 * <caption id="cv72_boot_mode_table"> Boot Modes of SPI NOR </caption>
 * <tr><th> Boot Option <th colspan="6"> Description <th> POC Pin
 * <tr><td rowspan="7"> Boot mode
 *     <td colspan="6"> Initial boot mode
 *     <td rowspan="7"> 15:13
 * <tr><td> <b> Boot Mode </b>
 *     <td> <b> Target Device </b>
 *     <td> <b> Interface </b>
 *     <td> <b> Address #Bytes </b>
 *     <td> <b> Read Command </b>
 *     <td> <b> Reset Command </b>
 * <tr><td> 0
 *     <td> Generic Device
 *     <td> Extended SPI (a)
 *     <td> 3
 *     <td> 0x03
 *     <td> 0x66-0x99 (b)
 * <tr><td> 1
 *     <td> Generic Device
 *     <td> Extended SPI
 *     <td> 3
 *     <td> 0x03
 *     <td> 0xFF-0xF0 (c)
 * <tr><td> 2
 *     <td> Micron
 *     <td> Octave-IO, A/D DDR (d), Dummy Length 16
 *     <td> 4
 *     <td> 0x8B
 *     <td> 0x66-0x99
 * <tr><td> 3-7
 *     <td> (Reserved)
 *     <td>
 *     <td>
 *     <td>
 *     <td>
 * <tr><td colspan="6"> <b> Note </b> <br>
 *     (a) SPI transmission bit order for all modes is MSB first. <br>
 *     (b) MICRON / MXIC / GigaDevice. Reset enable (0x66) followed by reset command (0x99). <br>
 *     (c) Spansion. Mode bit reset (MBR; 0xFF) followed by reset command (0xF0) <br>
 *     (d) A/D DDR -- Double samples per clock on address / data stage.
 * </table>

 *
 * @subsubsection cv72_ga_system_io_hdmi_tx 4.2.34 HDMI TX
 *
 * J46 is a standard vertical 19-pin HDMI receptacle for HDMI TX.  Make SW34 ON to enable 5-V power on J46.<br>
 *
 * @image html cv72_ga_jumpers_and_switches_for_sw34.png "Figure 4-22. Jumpers and Switches for SW34."
 *
 * @subsubsection cv72_ga_system_io_power_jumpers 4.2.35 Power Jumpers
 *
 * J97 is used to adjust the VDD. The following table provides the VDD configuration via J97.<br>
 *
 * <table>
 * <caption id="cv72_ga_vdd_configuration">Table 4-6. CV72 VDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Jumpers <th width="200px"> VDD Value (V)
 * <tr><td align="center" rowspan="4"> J97
 *     <td align="center"> 1-3
 *     <td align="center"> 0V7
 * <tr><td align="center"> 3-5
 *     <td align="center"> 0V75 (Default)
 * <tr><td align="center"> 4-6
 *     <td align="center"> 0V8
 * <tr><td align="center"> 2-4
 *     <td align="center"> 0V85
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_vdd.png "Figure 4-23. Jumpers and Switches for VDD."
 *
 * @note
 *   - Do not adjust the VDD voltage when the board is powered on so as to avoid permanently
 *     damaging the CV72 chipset.
 *
 * SW38 is used to adjust the VDD_DDR. This table provides the VDD_DDR configuration by SW38.<br>
 *
 * <table>
 * <caption id="cv72_ga_vdd_ddr_configuration">Table 4-7. CV72 VDD_DDR Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> VDDA Value (V)
 * <tr><td align="center" rowspan="2"> SW38
 *     <td align="center"> ON
 *     <td align="center"> 0V75 (Default)
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V8
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_vdd_ddr.png "Figure 4-24. Jumpers and Switches for VDD_DDR."
 *
 * @note
 *   - Check the VDD_DDR connection on board first. There is an option for VDD_DDR to combine with VDD power rail.
 *
 * SW27 is used to adjust the VDDA.  This table provides the VDDA configuration by SW27.<br>
 *
 * <table>
 * <caption id="cv72_ga_vdda_configuration">Table 4-8. CV72 VDDA Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> VDDA Value(V)
 * <tr><td align="center" rowspan="2"> SW27
 *     <td align="center"> ON
 *     <td align="center"> 0V8 (Default)
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V825
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_vdda.png "Figure 4-25. Jumpers and Switches for VDDA."
 *
 * SW28 is used to select the PCIE_AVDD.  This table provides the PCIE_AVDD configuration by SW28.<br>
 *
 * <table>
 * <caption id="cv72_ga_pcie_avdd_configuration">Table 4-9. CV72 PCIE_AVDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> PCIE_AVDD Value(V)
 * <tr><td align="center" rowspan="2"> SW28
 *     <td align="center"> ON
 *     <td align="center"> 0V8
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V85 (Deafult)
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_pcie_avdd.png "Figure 4-26. Jumpers and Switches for PCIE_AVDD."
 *
 * @note
 *   - Check the PCIE_AVDD connection on board first. There is an option for PCIE_AVDD to combine with VDDA power rail.
 *
 * SW29 is used to select the DCPHY_AVDD. This table provides the DCPHY_AVDD configuration by SW29.<br>
 *
 * <table>
 * <caption id="cv72_ga_dcphy_avdd_configuration">Table 4-10. CV72 DCPHY_AVDD Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Status <th width="200px"> DCPHY_AVDD Value(V)
 * <tr><td align="center" rowspan="2"> SW29
 *     <td align="center"> ON
 *     <td align="center"> 0V8
 * <tr><td align="center"> OFF
 *     <td align="center"> 0V85 (Deafult)
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_dcphy_avdd.png "Figure 4-27. Jumpers and Switches for DCPHY_AVDD."
 *
 * @note
 *   - Check the DCPHY_AVDD connection on the board first. There is an option for DCPHY_AVDD to combine with VDDA power rail.
 *
 * J112 and J113 are used to select the power enablement of PWR_CVSYS_5V and PWR_CVSYS_3V3.  This table provides
 * the PWR_CVSYS_5V and PWR_CVSYS_3V3 configuration by J112 / J113.<br>
 *
 * <table>
 * <caption id="cv72_ga_power_5v_33v_configuration">Table 4-11. CV72 PWR_CVSYS_5V and PWR_CVSYS_3V3 Power Enable Source Configuation.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Power Rail <th width="165px"> Jumpers <th width="200px"> Power Enable Source
 * <tr><td align="center" rowspan="2"> J112
 *     <td align="center" rowspan="2"> PWR_CVSYS_5V
 *     <td align="center"> 1-2
 *     <td align="center"> 12 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> PWR_PSEQ1 (Default)
 * <tr><td align="center" rowspan="2"> J113
 *     <td align="center" rowspan="2"> PWR_CVSYS_3V3
 *     <td align="center"> 1-2
 *     <td align="center"> 12 V
 * <tr><td align="center"> 2-3
 *     <td align="center"> PWR_PSEQ1 (Default)
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_power_enable_source.png "Figure 4-28. Jumpers and Switches for CV72 PWR_CVSYS_5V and PWR_CVSYS_3V3 Power Enable Source."
 *
 * J130 is used to select the power enablement of peripheral 1V8 / 3V3 /5V / 12V.  The following table provides
 * the power enable configuration of peripheral power rails by J102 / J103.<br>
 *
 * <table>
 * <caption id="cv72_ga_power_enable_of_peripheral_config">Table 4-12. Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V Configuration.</caption>
 * <tr><th width="165px"> Designator <th width="165px"> Jumpers <th width="200px"> Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V
 * <tr><td align="center" rowspan="2"> j130
 *     <td align="center"> 1-2
 *     <td align="center"> CV_3V3
 * <tr><td align="center"> 2-3
 *     <td align="center"> SYS_RSTn (Default)
 * </table>
 *
 * @image html cv72_ga_jumpers_and_switches_for_power_enable_of_peripheral.png "Figure 4-29. Jumpers and Switches for Power Enable of Peripheral 1V8 / 3V3 / 5V / 12V."
 *
 * @subsubsection cv72_ga_imu_switch 4.2.35 IMU Switch
 * To enable device IMU, set sw1-4 OFF; to enable IMU data ready interrupt report to CV72,
 * set sw1-4 OFF, SW36 OFF.
 * <table>
 * <caption id="cv72_ga_imu_switch">Table 4-13. CV72 IMU Switch.</caption>
 * <tr><th width="165px"> Designator-Pins <th width="85px"> Status <th width="320px"> Notes
 * <tr><td align="center" rowspan="2"> SW1-Pin4
 *     <td align="center"> OFF
 *     <td> SSI2_EN0 to Gyro sensor
 * <tr><td align="center"> ON
 *     <td> GPIO14 to VIN SLVS+DPHY
 * <tr><td align="center" rowspan="2"> SW4-Pin3
 *     <td align="center"> OFF
 *     <td> GPIO51 to Gyro INTn
 * <tr><td align="center"> ON
 *     <td> I2S to external audio codec connector
 * <tr><td align="center" rowspan="2"> SW36
 *     <td align="center"> OFF
 *     <td> PWR_GYRO_1V8
 * <tr><td align="center"> ON
 *     <td> GYRO_SPI_I3C_SELECT
 * </table>
 *
 * - - - -
 *
 * @section cv72_ga_design_notes 5 Design Notes
 * CV72 Ga (LP5) EVK board dual VIN slots share the same I2C bus. It cannot support two identical sensors with
 * two VIN slots run different sensor mode (like 4Kp60 and 1080p30).<br>
 *
 * There are two ways to try:
 *  - Ask HW team to rework the CV72 Ga board, rework VIN8's slot to use I2C3 instead.
 *  - Use different sensors like Sensor-A (IMX274) + sensor-B (IMX678) for different sensor modes.
 *
 * - - - -
 *
 * @section cv72_ga_doc_license 6 License
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
 * @file doc_hw_cv72_xiezhi.h
 * @brief
 * @version 1.0
 * @date 2023-08-16
 *
 * @copyright Copyright (c) 2024 Ambarella International LP.
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and / or foreign
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
 * @page page_cv72_xiezhi Board - CV72 Xiezhi
 *
 * This chapter provides details on setting up the hardware for the evaluation kit (EVK) and is
 * divided into the following sections:<br>
 *
 *   - Section @ref cv72_xiezhi_evk_package
 *   - Section @ref cv72_xiezhi_overview
 *   - Section @ref cv72_xiezhi_setting_up
 *   - Section @ref cv72_xiezhi_system_io_hardware_control
 *   - Section @ref cv72_xiezhi_design_notes
 *   - Section @ref cv72_xiezhi_doc_license
 *
 * - - - -
 *
 * @section cv72_xiezhi_evk_package 1. Evaluation Kit Package
 *
 * The Ambarella Cooper Linux EVK contains the following hardware and accessories. If any of the
 * following components are missing from the EVK package, contact the Ambarella support team.<br>
 *
 * <table>
 * <tr><td align="center"> <b> EVK board </b>
 *     <td> The board that comes furnished with the Ambarella CV72 system on chip (SoC)
 * <tr><td align="center"> <b> Cables </b>
 *     <td> Serial cables and USB cables
 * <tr><td align="center"> <b> EVK firmware  </b>
 *     <td> The firmware in the folder `Binary/` that is upgraded to the EVK board
 * <tr><td align="center"> <b> Install program </b>
 *     <td> The tools in the folder `Tools/` that are used for evaluation, including <br>
 *          AmbaUSB, PortServer, USBServer, and the VideoLAN Client (VLC) player
 * <tr><td align="center"> <b> Getting started guide  </b>
 *     <td> The document provides information on how to use the EVK board
 * </table>
 *
 * - - - -
 *
 * @section cv72_xiezhi_overview 2. Overview of the EVK Board
 *
 * The figure below provides an overview of the major components and input / output (I/O)
 * connectors of the CV72 Xiezhi EVK board.<br>
 *
 * @image html cv72_xiezhi_evk_board.png "Figure 2-1. CV72 Xiezhi EVK Board."
 *
 * - - - -
 *
 * @section cv72_xiezhi_setting_up 3. Setting Up the EVK Board
 *
 * Follow the steps below to set up the EVK hardware.<br>
 *
 *   -# Use a grounding strap or another verified device to protect the board from static
 *     charges. Connect the communication cables to the board before connecting any equipment
 *     to the power supply.<br>
 *
 *   -# Ensure that the sensors used on the CV72 Xiezhi board are compatible with MAX96712. Then,
 *     connect one sensor to the VIN0 port A via Mini-FAKRA cable.<br>
 *
 *   -# Use an Ethernet cable to connect the Ethernet port on the EVK board to the network
 *     port on the host PC.<br>
 *
 *   -# For high-definition (HD) preview, connect a video display with a high-definition multimedia interface (HDMI®) input to the
 *     HDMI connector on the EVK board.<br>
 *
 *   -# For the universal asynchronous receiver / transmitter (UART) console window, the CV72 Xiezhi EVK board is equipped with a USB serial bridge.
 *     Connect the EVK board to the host PC using a USB Mini A cable.<br>
 *
 *   -# To ensure protection from electro-static discharge (ESD), first connect the power cable
 *     to the EVK power jack on the board, and then connect the cable to the power supply.<br>
 *
 * @image html cv72_xiezhi_connected_hdmi_ethernet_usb_cable.png "Figure 3-1. CV72 Xiezhi Board with the HDMI / Ethernet / USB Cable Connected."
 *
 * - - - -
 *
 * @section cv72_xiezhi_system_io_hardware_control 4. System I/O and Hardware Control
 *
 * @subsection cv72_xiezhi_connectors 4.1 Connectors
 *
 * The following figures show all main I/O connectors on both sides
 * of the CV72 Xiezhi EVK board.<br>
 *
 * @image html cv72_xiezhi_major_io_connectors_on_the_top_side.png "Figure 4-1. Major I/O Connectors on the Top Side of the CV72 Xiezhi EVK Board."
 *
 * @image html cv72_xiezhi_major_io_connectors_on_the_bot_side.png "Figure 4-2. Major I/O Connectors on the Bottom Side of the CV72 Xiezhi EVK Board."
 *
 * Refer to the table below for a list of the main I/O connectors shown in the figures above.<br>
 *
 * <table>
 * <caption id="main_board_connectors"> Table 4-1. Main Board Connectors. </caption>
 * <tr><th> Item <th> Designator <th> Functions <th> Notes
 * <tr><td align="center"> 1
 *     <td align="center"> J128
 *     <td> Power
 *     <td> 12-V system power adapter input, 2.5 mm
 * <tr><td align="center"> 2
 *     <td align="center"> J25
 *     <td> USB serial
 *     <td> Debug UART and download for Cortex®-A76 and Cortex®-M3
 * <tr><td align="center"> 3
 *     <td align="center"> J137
 *     <td> Ethernet
 *     <td> 10 / 100 / 1000 Base-T Ethernet, single port with LEDs (link / act)
 * <tr><td align="center"> 4
 *     <td align="center"> J21
 *     <td> Automative Ethernet
 *     <td> 10 / 100 / 1000 Base-T Ethernet, single port
 * <tr><td align="center"> 5
 *     <td align="center"> J23
 *     <td> Controller area network (CAN)
 *     <td> 2 x 2, UTP
 * <tr><td align="center"> 6
 *     <td align="center"> J6
 *     <td> USB 3.2 hub host
 *     <td> Type-C
 * <tr><td align="center"> 7
 *     <td align="center"> J135
 *     <td> HDMI
 *     <td> HDMI receptacle
 * <tr><td align="center"> 8
 *     <td align="center"> J136
 *     <td> GPS
 *     <td> 5 mm SMA
 * <tr><td align="center"> 9
 *     <td align="center"> J127
 *     <td> Peripheral component interconnect express (PCIe)
 *     <td> ADT-Link
 * <tr><td align="center"> 10
 *     <td align="center"> J13 / J19
 *     <td> Secure digital (SD) slot
 *     <td> SD multi-media card (MMC) socket for SD I/F
 * <tr><td align="center"> 11
 *     <td align="center"> J8 / J9
 *     <td> Video input (VIN)
 *     <td> 2 x 4, Mini-FAKRA quad ports
 * <tr><td align="center"> 12
 *     <td align="center"> J10
 *     <td> VIN
 *     <td> Mini-FAKRA dual ports
 * <tr><td align="center"> 13
 *     <td align="center"> J17 / J18
 *     <td> MIPI DSI® video output (VOUT)
 *     <td> HSD connector
 * <tr><td align="center"> 14
 *     <td align="center"> J16
 *     <td> MIPI CSI VOUT
 *     <td> FAKRA connector
 * <tr><td align="center"> 15
 *     <td align="center"> J31
 *     <td> Microcontroller unit (MCU) USB serial
 *     <td> Debug UART and download for MCU
 * <tr><td align="center"> 16
 *     <td align="center"> J65
 *     <td> MCU CAN
 *     <td> 6 x 2, UTP
 * <tr><td align="center"> 17
 *     <td align="center"> J50
 *     <td> MCU Ethernet
 *     <td> 10 / 100 / 1000 Base-T Ethernet single port with LEDs (link / act)
 * </table>
 *
 * @subsection cv72_xiezhi_system_io_configurations 4.2 System I/O Configurations
 *
 * The CV72 Xiezhi EVK board supplies abundant I/O interfaces for a variety of applications.
 * Ensure that the system I/O interfaces are properly configured with the on-board hardware
 * switches.<br>
 *
 * The figure below provides the locations of the switches listed in this chapter.<br>
 *
 * @image html cv72_xiezhi_major_switches_for_system_io_on_the_top_side.png "Figure 4-2. Major Switches for the System I/O Configurations on the Top Side of the CV72 Xiezhi EVK Board."
 *
 * @subsubsection cv72_xiezhi_system_io_poc 4.2.1 Power on Configuration
 *
 * The table below shows the CV72 power-on configuration (POC) setup in SW3~SW7. Contact the Ambarella support team for the POC user guide.<br>
 *
 * <table>
 * <caption id="cv72_xiezhi_evk_poc_setup"> Table 4-1. CV72 Xiezhi POC Setup. </caption>
 * <tr><th> Designator <th> Pins <th> Notes
 * <tr><td align="center" rowspan="4"> SW3
 *     <td align="center"> A1
 *     <td> POC[4]=Boot Mode[0]
 * <tr><td align="center"> A2
 *     <td> POC[5]=Boot Mode[1]
 * <tr><td align="center"> A3
 *     <td> POC[6]=Secure boot
 * <tr><td align="center"> A4
 *     <td> POC[17]=boot_option[4]
 * <tr><td align="center" rowspan="2"> SW4
 *     <td align="center"> A1
 *     <td> POC[10]=Force USB boot
 * <tr><td align="center"> A2
 *     <td> POC[21]=HSM boot
 * <tr><td align="center" rowspan="2"> SW5
 *     <td align="center"> A1
 *     <td> POC[13]=boot_option[0]
 * <tr><td align="center"> A2
 *     <td> POC[15]=boot_option[2]
 * <tr><td align="center" rowspan="4"> SW6
 *     <td align="center"> A1
 *     <td> POC[16]=boot_option[3]
 * <tr><td align="center"> A2
 *     <td> POC[18]=boot_option[4]
 * <tr><td align="center"> A3
 *     <td> POC[19]=boot_option[5]
 * <tr><td align="center"> A4
 *     <td> POC[20]=boot_option[6]
 * <tr><td align="center" rowspan="1"> SW7
 *     <td align="center"> A1
 *     <td> POC[14]=boot_option[1]
 * </table>
 *
 * @subsubsection cv72_xiezhi_system_io_mcu_boot_mode 4.2.2 MCU Boot Mode
 *
 * <table>
 * <caption id="cv72_xiezhi_mcu_boot_mode"> Table 4-2. MCU Boot Mode. </caption>
 * <tr><th> Designator <th> Pins <th> Notes
 * <tr><td align="center" rowspan="1"> SW7
 *     <td align="center"> A1
 *     <td> Boot from pins HWCFG[4:5] or flash BMI
 * </table>
 *
 * - - - -
 *
 * @section cv72_xiezhi_design_notes 5. Design Notes
 * Because MAX96712 port A and MIPI DSI_A VOUT share the same MAX96717 input, the
 * hardware connection must to be changed in order to receive either one.<br>
 *
 * - - - -
 *
 * @section cv72_xiezhi_doc_license 6. License
 * Copyright (c) @ambalicyear Ambarella International LP.
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and / or foreign
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
 * @file doc_hw_cv3_dk_mini.h
 * @brief
 * @version 1.0
 * @date 2023-08-16
 *
 * @copyright Copyright (c) 2024 Ambarella International LP.
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and / or foreign
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
 * @page page_cv3_dk_mini Board - CV3 Dk_mini
 *
 * This chapter provides details on setting up the hardware for the CV3 Dk_mini evaluation kit (EVK) and is
 * divided into the following sections:<br>
 *
 *   - Section @ref cv3_dk_mini_evk_package
 *   - Section @ref cv3_dk_mini_overview
 *   - Section @ref cv3_dk_mini_setting_up
 *   - section @ref cv3_dk_mini_system_io_hardware_control
 *   - section @ref cv3_dk_mini_vin_map
 *   - Section @ref cv3_dk_mini_typical_case
 *   - Section @ref cv3_dk_mini_doc_license
 *
 * - - - -
 *
 * @section cv3_dk_mini_evk_package 1. Evaluation Kit Package
 *
 * The Ambarella Cooper Linux EVK contains the following hardware and accessories. If any of the
 * following components are missing from the EVK package, contact the Ambarella support team.<br>
 *
 * <table>
 * <tr><td align="center"> <b> EVK board </b>
 *     <td> The board that comes furnished with the Ambarella CV3 system on chip (SoC)
 * <tr><td align="center"> <b> Cables </b>
 *     <td> Serial cables and USB cables
 * <tr><td align="center"> <b> EVK firmware  </b>
 *     <td> The firmware in the folder `firmware/` that is upgraded to the EVK board
 * <tr><td align="center"> <b> Install program </b>
 *     <td> The tools in the folder `Tools/` that are used for evaluation, including <br>
 *          AmbaUSB, PortServer, USBServer, and the VideoLAN Client (VLC) player
 * <tr><td align="center"> <b> Getting Started Guide  </b>
 *     <td> Provides information on how to use the EVK board
 * </table>
 *
 * - The hardware specification
 * @image html cv3_dk_mini_specification.png "Figure 1-1. CV3 Dk_mini EVK Board Specification."
 *
 * - - - -
 *
 * @section cv3_dk_mini_overview 2. Overview of the EVK Board
 *
 * The figure below provides an overview of hardware architecture of the CV3 Dk_mini EVK board.<br>
 *
 * @image html cv3_dk_mini_hardware_architecture.png "Figure 2-1. CV3 Dk_mini EVK Board Architecture."
 *
 * The figures below provide an overview of the major components and input / output (I/O) connectors of the CV3 Dk_mini EVK board.<br>
 *
 * @image html cv3_dk_mini_side_overview.png "Figure 2-2. The Side View of CV3 Dk_mini EVK Board."
 *
 * @image html cv3_dk_mini_bot_overview.png "Figure 2-3. The Bottom View of CV3 Dk_mini EVK Board."
 *
 * - - - -
 *
 * @section cv3_hd_data_flow_overview 3. Overview of the Data Flow
 *
 * The figure below provides an overview of data flow of the CV3 high-definition (HD) platform.<br>
 *
 * @image html cv3_hd_data_flow_overview.svg "Figure 3-1. CV3 Data Flow Overview." width=1600 height=880
 *
 * - - - - 
 *
 * @section cv3_dk_mini_setting_up 4. Setting Up the EVK Board
 *
 * Follow the steps below to set up the EVK hardware.<br>
 *
 *   -# Use a grounding strap or another verified device to protect the board from static
 *     charges. Connect the communication cables to the board before connecting any equipment
 *     to the power supply.<br>
 *
 *   -# Ensure that the sensors used on the CV3 Dk_mini board are compatible with the MAX96712 sensor. Then,
 *     connect one sensor to the video input (VIN0) port A on CH1 via a Mini-FAKRA cable.<br>
 *
 *   -# Use an Ethernet cable to connect the Ethernet port (ETH0) on the EVK board to the network
 *     port on the host PC.<br>
 *
 *   -# For HD preview, connect to the video display with a high-definition multimedia interface (HDMI®) input to the
 *     HDMI connector on the EVK board.<br>
 *
 *   -# For the universal asynchronous receiver / transmitter (UART) console window, the CV3 Dk_mini EVK board is equipped with a USB serial bridge.
 *     Connect the EVK board (USB console) to the host PC using a USB type-C cable.<br>
 *
 *   -# AmbaUSB is used to download firmware for the CV3 EVK.<br>
 *
 *   -# The microcontroller unit (MCU) USB helps control power. Users can use this console to power the board on / off, as well as to switch to force USB download mode.<br>
 *      @code
 *      board # p  //power off
 *      board # p  //power on
 *      board # u  //enter force usb mode
 *      @endcode
 *
 *   -# To ensure protection from electro-static discharge (ESD), connect the power cable
 *     to the EVK power jack on the board, and then connect the cable to the power supply.<br>
 *
 * @image html cv3_dk_mini_6V_setup.png "Figure 4-1. CV3 Dk_mini Board with Six Connected Sensors."
 *
 * - - - -
 *
 * @section cv3_dk_mini_system_io_hardware_control 5. System I/O and Hardware control
 * The following figures show all main I/O connectors and switches on both sides of the CV3 Dk_mini board.<br>
 *
 * @image html cv3_dk_mini_major_io_connectors_on_top.png "Figure 5-1. Major I/O Connectors on the Top Side of the CV3 Dk_mini Board."
 *
 * @image html cv3_dk_mini_major_io_connectors_on_bot.png "Figure 5-2. Major I/O Connectors on the Bottom Side of the CV3 Dk_mini Board."
 *
 * @subsection cv3_dk_mini_connectors 5.1 Connectors
 *
 * Refer to the table below for a list of the main I/O connectors shown in the figures above.<br>
 *
 * <table>
 * <caption id="main_board_connectors"> Table 5-1. Main Board Connectors. </caption>
 * <tr><th> Item <th> Designator <th> Functions <th> Notes
 * <tr><td align="center"> 1
 *     <td align="center"> J1/J2
 *     <td> SOM connector
 *     <td> Connnect to CV3 Dev, refer to Figure 2-1.
 * <tr><td align="center"> 2
 *     <td align="center"> J3
 *     <td> Remote power control
 *     <td> reserved for Raspberry Pi 4 model B to remote control
 * <tr><td align="center"> 3
 *     <td align="center"> J4
 *     <td> Secure digital (SD) slot
 *     <td> SD multi-media card (MMC) socket for SD I/F
 * <tr><td align="center"> 4
 *     <td align="center"> J5/J6
 *     <td> Controller area network (CAN) bus
 *     <td> 1x2Pin 2.00 mm connector for the CAN bus
 * <tr><td align="center"> 5
 *     <td align="center"> J18
 *     <td> SWD
 *     <td> MOLEX 1x5Pin 2.54 mm connector for the MCU debug tool
 * <tr><td align="center"> 6
 *     <td align="center"> J19 / J44/ J45
 *     <td> Peripheral component interconnect express (PCIe) x 3
 *     <td> Standard PCIe card edge connector
 * <tr><td align="center"> 7
 *     <td align="center"> J43
 *     <td> SDIO0
 *     <td> Misco-SD socket for SDIO0 I/F
 * <tr><td align="center"> 8
 *     <td align="center"> J46
 *     <td> EXRST
 *     <td> 1x2Pin 2.00 mm, socket for external reset button
 * <tr><td align="center"> 9
 *     <td align="center"> J47
 *     <td> LED
 *     <td> prepared for LED
 * <tr><td align="center"> 10
 *     <td align="center"> CON1
 *     <td> MIPI DSI® video output (VOUT) 0/1
 *     <td> 80Pin 0.5mm HRS connnector
 * <tr><td align="center"> 11
 *     <td align="center"> CON2
 *     <td> HDMI
 *     <td> HDMI receptacle
 * <tr><td align="center"> 12
 *     <td align="center"> CON6
 *     <td> USB 3.1 hub host
 *     <td> Type-C
 * <tr><td align="center"> 13
 *     <td align="center"> CON7
 *     <td> Console USB
 *     <td> Type-C, CV3 debug
 * <tr><td align="center"> 14
 *     <td align="center"> CON9
 *     <td> Power
 *     <td> 2x3Pin 4.2 mm, 12-V system power adapter input
 * <tr><td align="center"> 15
 *     <td align="center"> CON10
 *     <td> AMBA USB
 *     <td> Mini-B type, CV3 firmware download port
 * <tr><td align="center"> 16
 *     <td align="center"> CON11
 *     <td> VIN Connector
 *     <td> Prepared for CV3 Dk_mini VINMIPI Board
 * <tr><td align="center"> 17
 *     <td align="center"> CON12
 *     <td> Ethernet connector
 *     <td> Prepared for Ethernet board
 * <tr><td align="center"> 18
 *     <td align="center"> CON13
 *     <td> Microcontroller unit (MCU) USB serial
 *     <td> Mini-B type, debug for MCU
 * <tr><td align="center"> 19
 *     <td align="center"> CON14
 *     <td> Joint test action group (JTAG)
 *     <td> 1x10Pin 0.5 mm FPC connector
 * </table>
 *
 * @subsection cv3_dk_mini_switches 5.2 Switches
 *
 * The table below shows the CV3 Dk_mini Switches. Contact the Ambarella support team for the POC user guide.<br>
 *
 * <table>
 * <caption id="Designator"> Table 5-2. CV3 Dk_mini Switches Setup. </caption>
 * <tr><th> Designator <th> Pins <th> Notes
 * <tr><td align="center" rowspan="2"> SW1
 *     <td align="center"> A1
 *     <td> ON/OFF: Power up/down CV3
 * <tr><td align="center"> A2
 *     <td> ON/OFF: Force USB boot is enabled/disabled
 * <tr><td align="center" rowspan="2"> SW2
 *     <td align="center"> A1
 *     <td> Prepared for CV3 reference clock selection, not used.
 * <tr><td align="center"> A2
 *     <td> Prepared for testing SoC power
 * <tr><td align="center" rowspan="2"> SW9
 *     <td align="center"> A1
 *     <td> ON: auto power on/off MCU, OFF: Normal (Default)
 * <tr><td align="center"> A2
 *     <td> ON: Suspend to RAM, OFF: Normal (Default)
 * </table>
 *
 * @subsection cv3_dk_mini_hardware_connection 5.3 Hardware Connection
 *
 * - Front View
 * @image html cv3_dk_mini_hardware_connect_front_view.png "Figure 5-3. Front View of Hardware Connection."
 *
 * -  Back View
 * @image html cv3_dk_mini_hardware_connect_back_view.png "Figure 5-4. Back View of Hardware Connection."
 *
 * -  Bottom View
 * @image html cv3_dk_mini_bottom_view.png "Figure 5-5. Bottom View of Hardware Connection."
 *
 * - VIN Connector
 * @image html cv3_dk_mini_vin_connector.png "Figure 5-6. VIN Connection."
 *
 * - VIN Cable Connection
 * @image html cv3_dk_mini_cable_connnection.png "Figure 5-7. Cable Connection."
 *
 * @subsection cv3_dk_mini_power_operation 5.4 Power Operation
 *
 * CV3 Dk_mini support two kinds of power on flow.
 * - Case A: Plug / Unplug power supply.
 *     -# Let switch always be "ON" side.
 * @image html cv3_dk_mini_switch_on.png "Figure 5-8. Case A: Switch on"
 *
 *     -# Power on by giving power to CV3 Dk_mini.
 * @image html cv3_dk_mini_give_power.png "Figure 5-9. Case A: Give Power"
 *
 *     -# Power off by unplugging power cable from CV3 Dk_mini.
 * @image html cv3_dk_mini_unplug_power.png "Figure 5-10. Case A: Unplug Power"
 *
 * - Case B: Remote power control by MCU sub-section in the remote development section.
 *     -# Ensure that system plug power cable and change switch to "ON" side
 *     -# Users are required to connect to [MCU USB UART] (CV3 Dk_mini) (Troubleshooting with console setup)
 *     -# Ensure that system plug power cable and change switch to "ON" side
 * @image html cv3_dk_mini_mcu_connection.png "Figure 5-11. Case B: Remote Power Control."
 *
 * - - - -
 *
 * @section cv3_dk_mini_vin_map 6. VIN Map
 * Equipped with 6x MAX96712, CV3 Dk_mini supports six channels (CH1 ~ CH6); currently, sensors are only supported on CH1 ~ CH3.<br>
 *
 * @image html cv3_dk_mini_vin_map.png "Figure 6-1. CV3 Dk_mini Board VIN Map."
 *
 * More details are shown in following table.
 *
 * <table>
 * <caption id="vin_map"> Table 6-1. VIN Map. </caption>
 * <tr><th> Channel <th> VIN <th> Vsync <th> Hsync <th> I2C addr <th> Reset <th> I2C <th> Notes
 * <tr><td align="center"> CH1
 *     <td align="center"> 0, 1, 2, 3
 *     <td> IDSPV0_IOPAD_VIN1_MASTER_VSYNC/GPIO_212
 *     <td> IDSPV0_IOPAD_VIN1_MASTER_HSYNC/GPIO_211
 *     <td align="center"> 0x52
 *     <td align="center"> GPIO_156
 *     <td align="center"> IDC0
 *     <td> --
 * <tr><td align="center"> CH2
 *     <td align="center"> 12, 13, 14, 15
 *     <td> VSYNC0_OUT_0/PWM7/GPIO_21
 *     <td> HSYNC0_OUT_0/GPIO_25
 *     <td align="center"> 0x52
 *     <td align="center"> GPIO_53
 *     <td align="center"> IDC1
 *     <td> --
 * <tr><td align="center"> CH3
 *     <td align="center"> 16, 17, 18, 19
 *     <td> VSYNC0_OUT_1/PWM8/GPIO_22
 *     <td> HSYNC0_OUT_1/GPIO_26
 *     <td align="center"> 0xD6
 *     <td align="center"> GPIO_54
 *     <td align="center"> IDC1
 *     <td> --
 * <tr><td align="center"> CH4
 *     <td align="center"> 24, 25, 26, 27
 *     <td> SVSYNC/GPIO_158
 *     <td> SHSYNC/GPIO_157
 *     <td align="center"> 0x52
 *     <td align="center"> GPIO_55
 *     <td align="center"> IDC3
 *     <td> Temporarily not supported
 * <tr><td align="center"> CH5
 *     <td align="center"> 36, 37, 38, 39
 *     <td> VSYNC1_VOUT_0/GPIO_27
 *     <td> HSYNC1_OUT_0/GPIO_31
 *     <td align="center"> 0x52
 *     <td align="center"> GPIO_56
 *     <td align="center"> IDC4
 *     <td> Temporarily not supported
 * <tr><td align="center"> CH6
 *     <td align="center"> 40, 41, 42, 43
 *     <td> VSYNC1_OUT_1/PWM8/GPIO_28
 *     <td> HSYNC1_OUT_1/GPIO_32
 *     <td align="center"> 0xD6
 *     <td align="center"> GPIO_57
 *     <td align="center"> IDC4
 *     <td> Temporarily not supported
 * </table>
 *
 * - - - -
 *
 * @section cv3_dk_mini_typical_case 7. Typical Cases
 *
 * @subsection typical_case_6v 7.1 6-V Case
 *
 * The sensor connection: <br>
 * CH1 port A~B -- IMX390_mipi_brg <br>
 * CH2 port A~B, CH3 port A~B -- OS08A10_mipi_brg
 *
 * Currently, CV3 only supports `app-img-profile 5 (ADAS) / 8 (STEREO) / 10 (ROBOT)`. Customers need
 * to specify it through command option `--app-img-profile` or lua script configuration
 * (command option has higher priority than lua script configuration).
 *
 * @code
 * board # init.sh --na
 * board # modprobe max96712 id=0x020102010201 dts_addr=1 use_max20087=0 vc=1
 * board # modprobe imx390_mipi_brg brg_id=0x03
 * board # modprobe os08a10_mipi_brg brg_id=0x3C
 * board # test_encode --resource-cfg /usr/local/bin/script/cv3_six_vin_2x1080p_4x4k_linear.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua  --raw-capture 1 --app-img-profile 8
 * board # test_encode -A -h 1080p -b 0 -e
 * @endcode
 *
 * @subsection typical_case_11v 7.2 11-V Case
 *
 * The sensor connection: <br>
 * CH1 port A -- ox08b40_mipi_brg <br>
 * CH1 port B~C, CH2 port A~D, CH3 port A~D -- ox03c10_mipi_brg
 *
 * The Lua script can be found at <a href="attachment/11v_x8b_10x3c.lua" target="_blank"><b>11v_x8b_10x3c.lua</b></a>. <br>
 * The vinbrg modification in the device tree can be found at <a href="attachment/CV3_Dk_mini_11v_x8b_10x3c_vinbrg_reference.txt" target="_blank"><b>CV3_Dk_mini_11v_x8b_10x3c_vinbrg_reference.txt</b></a>.
 *
 * @code
 * board # init.sh --na
 * board # modprobe max96712 id=0x0f0f040201 dts_addr=1 poc_rst_time=150 use_max20087=0
 * board # modprobe ox08b40_mipi_brg brg_id=0x1 fsync=1 fsync_block=1
 * board # modprobe ox03c10_mipi_brg brg_id=0x1e fsync=1
 * board # test_aaa_service -a &
 * board # test_encode --resource-cfg 11v_x8b_10x3c.lua --vout-cfg /usr/local/bin/scripts/vout_hdmi.lua --raw-capture 1 --app-img-profile 5
 * @endcode
 *
 * - - - -
 *
 * @section cv3_dk_mini_doc_license 8. License
 * Copyright (c) @ambalicyear Ambarella International LP.
 *
 * This file and its contents ("Software") are protected by intellectual
 * property rights including, without limitation, U.S. and / or foreign
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
