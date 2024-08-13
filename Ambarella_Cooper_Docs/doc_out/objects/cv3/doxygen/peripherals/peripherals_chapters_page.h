/*!
 * @file audio.h
 * @date 2021-09-15
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
 * @page si_audio Audio
 *
 * @section audio_arch 1. Audio Architecture
 *
 * @subsection audio_codec_block_diagram 1.1 Audio Codec Block Diagram
 *
 * CV series SoC supports the external codec.
 * The figure below shows the audio subsystem architecture for CV2 and CV22.
 * @image html audio_codec_simple.png "Figure 1-1. Audio Codec Block Diagram for CV2 and CV22"
 *
 * The figure below shows the audio subsystem architecture for CV25, CV5, CV52, CV72 and CV3.
 * @image html audio_codec_complex.png "Figure 1-2. Audio Codec Block Diagram for CV25 / CV5x / CV72 / CV3"
 *
 * @subsection si_alsa_architecture 1.2 Advanced Linux Sound Architecture (ALSA)
 *
 * The CV series SoC audio function is implemented through the ALSA architecture.
 * Visit http://www.alsa-project.org
 * for information about ALSA.
 * @image html audio_alsa_architecture.png "Figure 1-3. ALSA Architecture"
 *
 * The figure above describes the general software architecture for the audio.
 * The ALSA driver has been implemented by Ambarella, while the ALSA core and ALSA library are provided
 * by the ALSA open source project.
 * This enables flexibility for developers to implement applications following the pipeline.
 * @note
 * Currently, the Ambarella ALSA driver exclusively supports 16-bit PCM raw data.
 * However, it can encode or decode operations in customized applications to support AAC
 * or different audio encoding formats.
 * `test_audio` provides an example on how to use the ALSA driver.
 *
 * @subsection aplay_arecord 1.3 aplay / arecord
 *
 * `"arecord / aplay"` are ALSA utility tools for controlling the sound card,
 * it belongs to GNU general public license version 2 (GPLv2).
 *
 * 1. arecord / aplay: Description
 *   - arecord is a command-line soundfile recorder for the ALSA soundcard driver.
 *     It supports several file formats.
 *   - aplay is similar to arecord, but it plays instead of recording.
 *     For the supported soundfile formats, the sampling rate, bit depth,
 *     and other details can be automatically determined from the soundfile header.
 *
 * 2. arecord / aplay: Usage
 *   - Prepare the hardware.
 *     Read the hardware design schematics to verify that the audio jumpers have been configured correctly
 *     on the platform.
 *   - Compile ALSA-Lib and ALSA-Utils, and then load the audio ALSA driver.
 *     For details on how to compile ALSA, refer to @ref install_alsa_dri_ver.
 *
 *     The audio ALSA driver will be loaded automatically by a script when the platform has been booted.
 *     The script is named `S13load-private-driver`,
 *     and it is located in `ambarella/boards/cvx_board/rootfs/default/etc/init.d/S13load-private-driver`.
 *     It can be modified per user requirements.
 *     After the platform boots up,
 *     type `"lsmod | grep snd_soc"` to check whether `snd_soc_ak4951_amb` exists.
 *     If it does not exist, use:
 *     @code {.c}
 *     board # modprobe snd_soc_ak4951_amb
 *     @endcode
 *
 * 3. Set the codec controller.
 *   - Use the alsamixer to set the codec controller.
 *   - Type `alsamixer` and then `"S"` to select the sound card.
 *     @image html audio_sound_card_selection.png "Figure 1-4. Sound Card Selection"
 *   - Press <B>Left</B> or <B>Right</B> Key to select the Item
 *     and <B>Up</B> or <B>Down</B> Key to select the value.
 *     @image html audio_select_the_value_of_card_selection.png "Figure 1-5. Select the Value of Card Selection"
 *   - Press <B>"ESC"</B> to save and exit.
 *   - Run `arecord / aplay`
 *     @code {.c}
 *     board # arecord -f dat -t wav test.wav
 *     board # aplay -f dat test.wav
 *     @endcode
 *
 * - - - -
 *
 * @section audio_alsa 2. ALSA Library
 *
 *
 * This section introduces how to use and configure ALSA in Linux,
 * and explains ALSA basic concepts such as development methods for the audio application.
 * The ALSA provides audio functionality to the Linux operating system.
 * ALSA has the following significant features:
 * - Modularized sound drivers.
 * - SMP and thread-safe design.
 * - User space library (alsa-lib) to simplify application programming
 *   and provide a higher level functionality.
 * - Support for the older open sound system (OSS) API, providing binary compatibility for most OSS programs.
 * ALSA comes with a kernel API and a library API.
 * Application programmers should use the library API rather than the kernel API.
 * The library offers 100% of the functionality of the kernel API,
 * but adds major improvements in usability, improving the application code.
 *
 * @subsection install_alsa_dri_ver 2.1 Install ALSA Driver
 *
 * 1. Install ALSA driver: Install alsa-utils
 *     All <B>alsa-utils</B> require the <B>ncurse library</B>.
 *     Configuring without the <B>ncurse library</B> will cause the system failure.
 *   - To cross-compile the ncurse library:
 *     @code {.c}
 *     build $ CC=arm-linux-gcc ./configure --build=i686-linux --host=arm-linux --prefix=/tmp/ncurse;
 *     make;
 *     make install
 *     @endcode
 *     <B>ncurse library</B> can be found in `/tmp/ncurse`.
 *   - Download <B>alsa-utils-1.0.26.tar.bz2</B> from the site www.alsa-project.org.
 *   - Compile and install alsa-utils (see below):
 *     @code {.c}
 *     build $ CC=arm-linux-gcc; LDFLAGS+="-L/tmp/ncurse/lib -lpthread -lm -lc";
 *     CFLAGS+="-I/tmp/ncurse/include -I/tmp/ncurse/include/ncurses";
 *     ./configure --build=i686-linux --host=arm-linux --prefix=/tmp/alsa/utils
 *     --with-alsa-prefix=/tmp/alsa-lib/lib --with-alsa-inc-prefix=/tmp/alsa-lib/include;
 *     make; make install
 *     @endcode
 *     The <B>alsa-utils</B> is in `/tmp/alsa/utils`.
 *     @note
 *     The alsa-utils will be built as a dynamic library by default.
 *     To build the alsa-utils as static binaries,
 *     remove the dynamic library (`/tmp/alsa-lib/lib/libasound.so*`).<br>
 *
 * 2. Install the ALSA Driver: Test the Hardware and the ALSA Driver
 *   - Boot the platform with the Linux kernel support.
 *   - Make the node for PCM capture and playback.
 *     @code {.c}
 *     board # mkdir -p /dev/snd
 *     board # mknod /dev/snd/controlC0 c 116 0
 *     board # mknod /dev/snd/pcmC0D0c c 116 24
 *     board # mknod /dev/snd/pcmC0D0p c 116 16
 *     @endcode
 *   - Copy `*.conf` files needed by alsa-utils to `/usr/share/alsa` on the platform.<br>
 *     The `*.conf` files are created and installed after installing `alsa-lib`
 *     and placed in the directory indicated by `--with-configdir` option.<br>
 *     <B>alsa-utils</B> just need 3 `*.conf` files, which are `alsa.conf,
 *     cards/aliases.conf and pcm/default.conf.`
 *   - <B>aplay</B> and <B>arecord</B> are provided in alsa-utils.
 *     <B>Arecord</B> is a link to <B>aplay</B> and used to capture sound.<br>
 *     For capture:
 *     @code {.c}
 *     board # arecord -fdat test.wav
 *     board # arecord -vv -r 8000 -c 2 -f mu_law -t au test.au
 *     board # arecord -vv -r 8000 0c -f a_law -t raw test.raw
 *     @endcode
 *     For playback: (A-law needs to specify the format).
 *     @code {.c}
 *     board # aplay –vv test.au
 *     @endcode
 *
 * @subsection develop_alsa_applications 2.2 Develop ALSA Applications
 *
 * This section introduces basic concepts and guidelines for developing the audio application using ALSA
 * and does not provide a complete reference manual for the <B>alsa-lib</B> API.<br>
 * Most of the contents mentioned in this section can also be found in www.alsa-project.org.
 *
 * <B>Reference Documents:</B>
 * - ALSA-lib API document: http://www.alsa-project.org/alsa-doc/alsa-lib
 * - A tutorial on using the ALSA Audio API: http://equalarea.com/paul/alsa-audio.html
 * - ALSA 0.9.0 HOW TO: http://www.suse.de/~mana/alsa090_howto.html<br>
 *   <B>Reference Code:</B> `play.c, latency.c, pcm.c, pcm_min.c`
 *
 * <B>Basic Concepts</B>
 * - <B>Capture:</B> Receiving data from the outside world (which is different from <B>arecord</B>,
 *   as it implies data storage). It is not part of the ALSA APIs.
 * - <B>Playback:</B> Delivering data to the outside world, presumably, though unnecessarily, it can be heard.
 * - <B>Duplex:</B> Duplex shows a situation when the capture
 *   and playback can occur simultaneously on the same interface.
 * - <B>PCM:</B> Pulse code modulation (PCM) describes a method
 *   that represents an analog signal in a digital form.
 *   It is used by all computer audio interfaces, and in the ALSA API as a shorthand for "audio".
 * - <B>Channel:</B> 1 for mono, 2 for stereo.
 * - <B>Sample:</B> A single value refers to the amplitude of the audio signal
 *   at a single point in time on a single channel.
 * - <B>Frame:</B> When working with the digital audio, users often discuss the data
 *   that represents all channels at a single point in time.
 *   This is a collection of samples, one per channel, and is generally called a frame.
 *   In other words, a frame = sample * channel.
 * - <B>Sample format:</B> This indicates the sample format used to transfer data to or from the interface.
 *   It may or may not correspond with a format directly supported by the hardware.
 * - <B>Rate:</B> For fully digital interfaces, the rate indicates the speed of the clock
 *   that is used to move digital audio data to or from the outside world.
 * - <B>Interleaved:</B> A data layout arrangement, samples of each channel is played at the same time
 *   so that they can follow each other sequentially.
 *   See the following section: non-interleaved.
 * - <B>Non-interleaved:</B> A data layout where the samples for a single channel follow each other sequentially;
 *   samples for another channel are either in another buffer or another part of this buffer.
 *   In contrast with the interleaved concept, it responds with a format supported by the hardware.
 * - <B>Chunk size:</B> The number of frames used when transferring data to / from the device hardware buffer.
 * - <B>Chunk byte:</B> Chunk byte = chunk size * channel.
 * - <B>Period:</B> The number of frames processed every time.
 * - <B>Buffer size:</B> The size of buffer used to store the sound data per period.
 *
 * @par ALSA Architecture
 * Application developers should focus more on the application logic
 * and less on the implementation of the ALSA core and ALSA driver.
 * Furthermore, developers must use the API functions in the ALSA-lib
 * to achieve native ALSA support for applications.
 *
 * The <B>ALSA-lib</B> documentation tutorial is a valuable developer reference to the available functions.<br>
 * A typical audio application uses the following routine:
 * @code {.c}
 * open_the_device();
 * set_the_parameters_of_the_device();
 * while (!done) {
 * 	receive_audio_data_from_the_device();
 * 	deliver_audio_data_to_the_device();
 * 	}
 * close the device
 * @endcode
 * 1. Open the device<br>
 *   The currently designed interfaces are listed below:
 *   - Information interface (`/proc/asound`)
 *   - Control interface (`/dev/snd/controlC0`)
 *   - PCM capture interface (`/dev/snd/pcmC0D0c`)
 *   - PCM playback interface (`/dev/snd/pcmC0D0p`)
 *
 *   ALSA does not directly operate with the interfaces listed above;
 *   the most important ALSA interfaces to the PCM devices are the default, plughw: 0, 0 and HW: 0, 0 interface.<br>
 *   Only HW: 0, 0 will interact with the `/dev/snd/controlC0, /dev/snd/pcmC0D0c,`
 *   and `/dev/snd/pcmC0D0p`, because HW: 0, 0 is the lowest layer interface.
 *   However, plughw: 0, 0 and default only interacts with HW: 0, 0.<br>
 *   If the plughw or default interface is used, the sound hardware is not important.
 *   If the sound device does not support the sample rate you specify, your data will be automatically converted.
 *   This also applies to the sample format, the access type, and the number of channels.<br>
 *   For the hardware interface, users must check if their hardware supports the desired configuration.
 *   If the desired configuration is not supported, then the application using the hardware will fail,
 *   but the applications using plughw or default will still be successful because of its convertible capability.
 *
 *   @note
 *   The default interface fits the requirement of most applications
 *   In addition, ALSA provides many PCM plugins, e.g., `plugin: copy, plugin: rate, plugin: file` and etc.
 *   Please see `alsa-lib` API document for details.
 *   Users can use the function named <B>snd_pcm_open()</B> to open the PCM device.
 *   @code {.c}
 *   snd_pcm_t * capture;
 *   snd_pcm_t * playback;
 *   snd_pcm_open(&capture,"default",SND_PCM_STREAM_CAPTURE, 0);
 *   snd_pcm_open(&playback,"default",SND_PCM_STREAM_PLAYBACK, 0);
 *   @endcode
 *   Because using one PCM handle for both playback and capture is not possible,
 *   users must configure two handles for full-duplex--the sound device can be opened in the capture mode
 *   and the playback mode simultaneously (they are independent).
 *
 * 2. Set Parameters<br>
 *   Users must correctly set the parameters before writing / reading PCM data to / from the sound device.<br>
 *   Parameters are as follows:
 *   - Access type
 *   - Sample format
 *   - Sample rate
 *   - Number of channels
 *   - Number of periods
 *   - Period size
 *
 *   Allocate the hardware parameter structure:
 *   @code {.c}
 *   snd_pcm_hw_params_t *hwparams_c;
 *   snd_pcm_hw_params_alloca(&hwparams_c);
 *   snd_pcm_hw_params_t *hwparams_p;
 *   snd_pcm_hw_params_alloca(&hwparams_p);
 *   @endcode
 *   Initialize the hardware parameter structure with the full configuration space of the soundcard:
 *   @code {.c}
 *   snd_pcm_hw_params_any(capture, hwparams_c);
 *   snd_pcm_hw_params_any(playback, hwparams_p);
 *   @endcode
 *   Restrict the configuration space to a certain configuration with a set of functions named as follows:
 *   @code {.c}
 *   snd_pcm_hw_params_set_<parameter>(capture, hwparams_c, …);
 *   snd_pcm_hw_params_set_<parameter>(playback, hwparams_p, …);
 *   @endcode
 *   If the hardware interface is used, calls to these functions may fail
 *   if the sound device does not support the parameters you specify.<br>
 *   Apply the configuration to the PCM device pointed to by capture or playback.
 *   This will also prepare the PCM device.
 *   @code {.c}
 *   snd_pcm_hw_params(capture, hwparams_c);
 *   snd_pcm_hw_params(playback, hwparams_p);
 *   @endcode
 * 3. Read / Write Sound Data
 *   For the interleaved access type:
 *   @code {.c}
 *   snd_pcm_readi(capture, data_c, num_frames_c);
 *   snd_pcm_writei(playback, data_p, num_frames_p);
 *   @endcode
 *   For the non-interleaved access type,
 *   @code {.c}
 *   snd_pcm_readn(capture, data_c, num_frames_c);
 *   snd_pcm_writen(playback, data_p, num_frames_p);
 *   @endcode
 *   Xrun (underrun / overrun):<br>
 *   After the audio interface begins, it continues running until it is instructed to stop.
 *   It will continue to generate data for the computer to use and / or send data
 *   from the computer to the outside world.
 *   The reasons listed below explain why the user’s program might not keep up with it.<br>
 *   For playback, this can lead to a situation where the interface requires new data from the computer;
 *   however, because no new data exists, the interface uses old data left in the hardware buffer.
 *   This is called an "underrun".<br>
 *   For capture, the interface may have data to deliver to the computer, but nowhere to store it,
 *   so it has to overwrite part of the hardware buffer that contains data the computer has not received.
 *   This is called an "overrun".<br>
 *   For simplicity, ALSA uses the term "xrun" to refer to either of these conditions (underrun or overrun).<br>
 *   If xrun occurs, the following function should be called:
 *   @code {.c}
 *   snd_pcm_prepare(capture);
 *   snd_pcm_prepare(playback);
 *   @endcode
 *
 * - - - -
 *
 * @section audio_aac_enc 3. AAC Encode Library
 *
 * snd_pcm_prepare(capture); snd_pcm_prepare(playback);
 *
 * @subsection data_structure 3.1 Data Structure
 *
 * This section includes `aac_audio_enc.h`. Do not change the parameter order.
 *
 * - <B>Structure name</B>: `au_aacenc_config_s`
 * <table>
 * <caption id="table_vsrc_lua"></caption>
 * <tr><th> <div style="width:240px"><B>Parameter</B></div>
 * <th> <div style="width:240px"><B>Description</B></div>
 * <tr><td> u32 sample_freq
 *     <td> Specifies the sampling rate
 * <tr><td> u32 coreSampleRate
 *     <td> Specifies the sampling rate for AAC+
 * <tr><td> s32 Src_numCh
 *     <td> Specifies the input channel number
 * <tr><td> s32 Out_numCh
 *     <td> Specifies the output channel number
 * <tr><td> u32 bitRate
 *     <td> Specifies the bitrate of encoding bitstream
 * <tr><td> u8 ena_adjbr
 *     <td> Specifies the adjusting bitrate mode
 * <tr><td> u32 adj_bitRate
 *     <td> Specifies the adjusting bitrate when encoding
 * <tr><td> u32 quantizerQuality
 *     <td> Specifies the quantizer quality
 * <tr><td> u32 tns
 *     <td> Specifies the TNS function on/off
 * <tr><td> s8 ffType
 *     <td> Specifies the file format (ADTS, ADIF, LOAS, RAW)
 * <tr><td> s32 enc_mode
 *     <td> Specifies the encode mode (AAC, AAC+, AAC++)
 * <tr><td> u32 frameCounter
 *     <td> Specifies the encode frame counter
 * <tr><td> u32 ErrorStatus
 *     <td> Specifies the error status of encode
 * <tr><td> u32 nBitsInRawDataBlock
 *     <td> Specifies the all bit number of encoding a frame
 * <tr><td> u8* enc_wptr
 *     <td> Specifies the write pointer of output bit stream
 * <tr><td> s32* enc_rptr
 *     <td> Specifies the read pointer of input source data
 * <tr><td> u32* codec_lib_mem_adr
 *     <td> Specifies the address of library working memory
 * <tr><td> audio_lib_info_t lib_info
 *     <td> Specifies the SVN revision of audio library
 * <tr><td> u32 calibre_proc_on
 *     <td> Specifies the calibration process on/off
 * <tr><td> u32 calibre_proc_mode
 *     <td> Specifies the calibration process mode
 * <tr><td> u32 calibre_apply
 *     <td> Specifies the calibration apply on/off
 * <tr><td> s8* calibre_curve_addr
 *     <td> Specifies the address of calibration curve
 * </table>
 * <br>
 *
 * - Parameter values - sample_freq
 *   Supported options:
 *   @code {.c}
 *   #define AUDIO_FS_48000 48000
 *   #define AUDIO_FS_44100 44100
 *   #define AUDIO_FS_32000 32000
 *   #define AUDIO_FS_24000 24000
 *   #define AUDIO_FS_22050 22050
 *   #define AUDIO_FS_16000 16000
 *   #define AUDIO_FS_12000 12000
 *   #define AUDIO_FS_11025 11025
 *   #define AUDIO_FS_8000 8000
 *   @endcode
 *
 *   Limitation:
 *   @code {.c}
 *   if (enc_mode == AACPLAIN)
 *   // support all sample_freq (48000, 44100, 32000, 24000, 22050,
 *   // 16000, 12000, 11025, 8000) else if (enc_mode == AACPLUS || enc_mode == AACPLUS_PS)
 *   // only support sample_freq (32000, 44100, 48000)
 *   @endcode
 *
 *   Example:<br>
 *   If the input audio signal source is 48 KHz, the parameter is set as follows.
 *   @code {.c}
 *   sample_freq = define AUDIO_FS_48000;
 *   @endcode
 *
 * - Parameter values - coreSampleRate<br>
 *   Supported options:<br>
 *   Obsolete, this parameter is automatically set by `sample_freq` and `enc_mode`.
 *
 * - Parameter values - Src_numCh<br>
 *   Supported options:
 *   @code {.c}
 *   #define AUDIO_MONO 1
 *   #define AUDIO_STEREO 2
 *   @endcode
 *   Example:
 *   If the input audio source is stereo, the parameter is set as follows.
 *   @code {.c}
 *   Src_numCh = AUDIO_STEREO;
 *   @endcode
 *
 * - Parameter values - Out_numCh<br>
 *   Supported options:<br>
 *   Obsolete, this parameter is auto-set by `Src_numCh` and `enc_mode`.
 *
 * - Parameter values - BitRate<br>
 *   Supported options:
 *   @code {.c}
 *   if (enc_mode == AACPLAIN ) {
 *   if (sample_freq == 32000 || sample_freq == 44100 || sample_freq == 48000) {
 *   min.bitRate = numChannels * 16000;
 *   max.bitRate = numChannels * 160000;
 *   } else if (sample_freq == 16000 || sample_freq == 22050 || sample_freq == 24000)
 *   {
 *   min.bitRate = numChannels * 16000;
 *   max.bitRate = numChannels * 80000;
 *   } else if (sample_freq == 11025 || sample_freq == 12000) {
 *   min.bitRate = numChannels * 8000;
 *   max.bitRate = numChannels * 40000;
 *   } else if (sample_freq == 8000 ) {
 *   min.bitRate = numChannels * 8000;
 *   max.bitRate = numChannels * 12000;
 *   }
 *   } else if (enc_mode == AACPLUS) {
 *   min.bitRate = numChannels * 14000;
 *   max.bitRate = numChannels * 64000;
 *   } else if (enc_mode == AACPLUS_PS) {
 *   min.bitRate = 16000;
 *   max.bitRate = 64000;
 *   }
 *   @endcode
 *
 * - Parameter values - ena_adjbr<br>
 *   Support options:<br>
 *   Obsolete.
 *
 * - Parameter values - adj_bitRate<br>
 *   Supported options:<br>
 *   The same as bitRate.<br>
 *   This parameter is changeable after calling aacenc_setup function.<br>
 *   Example:<br>
 *   Set the initial bit rate (bitRate). Change the AAC bitrate (adj_bitRate).<br>
 *   Set `adj_bitRate = bitRate` in aacenc_setup function to avoid `NULL` value.
 *
 * - Parameter values - QuantizerQuality<br>
 *   Supported options:<br>
 *   The parameter is related the quantizer quality, 0 (low), 1 (high), 2 (highest).<br>
 *   Example:<br>
 *   The highest value brings in the best encoding quality but the computation is the most complex.
 *   Recommend `quantizerQuanlity = 1`.
 *
 * - Parameter values - Tns<br>
 *   Supported options:<br>
 *   The parameter switches TNS on or off, 0 (Off), 1 (On).<br>
 *   Example:
 *   @code {.c}
 *   tns = 1;
 *   @endcode
 *
 * - Parameter values - FfType<br>
 *   Supported options:
 *   @code {.c}
 *   char AAC_BS_TYPE[4] = { 'r', 'a', 't', 'l' };
 *   r: RAW
 *   a: ADIF
 *   t: ADTS
 *   l: LOAS
 *   @endcode
 *   Example:<br>
 *   To obtain the raw AAC bit stream (without any MPEG defined header information),
 *   @code {.c}
 *   ffType = 'r';
 *   @endcode
 *   For normal recording, generate the AAC bitstream with the ADTS header.
 *   @code {.c}
 *   ffType = 't';
 *   @endcode
 *
 * - Parameter values - enc_mode<br>
 *   Supported options:
 *   @code {.c}
 *   typedef enum {
 *   AACPLAIN,         // aac encoding low complexity
 *   AACPLUS,          // aacPlus encoding
 *   AACPLUS_SPEECH,   // Not supported
 *   AACPLUS_PS,       // aacPlus encoding with parametric stereo
 *   AACPLUS_SPEECH_PS // Not supported
 *   } AAC_MODE;
 *   @endcode
 *   Limitation:<br>
 *   Currently, only `AACPLAIN, AACPLUS` and `AACPLUS_PS` are supported.<br>
 *   Example:<br>
 *   Encode the input audio source to the plain AAC.
 *   @code {.c}
 *   enc_mode = AACPLAIN;
 *   @endcode
 *
 * - Parameter values - FrameCounter<br>
 *   Obsolete.
 *
 * - Parameter values - ErrorStatus<br>
 *   Supported options:<br>
 *   The upper layer must check the ErrorStatus when it calls the AAC encode APIs.
 *   @code {.c}
 *   typedef enum {
 *   ENCODE_OK,                      // No error
 *   ENCODE_INVALID_POINTER,         // Pointer invalid
 *   ENCODE_FAILED,                  // Encoding failed
 *   ENCODE_UNSUPPORTED_SAMPLE_RATE, // Given sample rate not supported
 *   ENCODE_UNSUPPORTED_CH_CFG,      // Given channel not supported
 *   ENCODE_UNSUPPORTED_BIT_RATE,    // Given bitrate not supported
 *   ENCODE_UNSUPPORTED_MODE         // Given mode not supported
 *   } AACPLUS_ERROR;
 *   @endcode
 *
 * - Parameter values - NBitsInRawDataBlock<br>
 *   Supported options:<br>
 *   This parameter records all the bit numbers that go into encoding a frame.
 *
 * - Parameter values - enc_wptr<br>
 *   Supported options:<br>
 *   This parameter is the write pointer of the encoding bitstream.
 *   A memory address must be assigned to this parameter.
 *
 * - Parameter values - enc_rptr<br>
 *   Supported options:<br>
 *   This parameter is the read pointer of the input source data.
 *   The address of the input source address must be assigned to this parameter.
 *   The source PCM format is 16 bits resolution.
 *   If the input audio source is stereo, the PCM data is interleaved.
 *   @code {.c}
 *   Stereo: L(16bit) R(16bit) L(16bit) R(16bit) ...
 *   Mono: L(16bit) L(16bit) L(16bit) L(16bit) ...
 *   @endcode
 *
 * - Parameter values - codec_lib_mem_adr<br>
 *   Supported options:<br>
 *   This parameter is the address of the library’s working memory.
 *   A memory address must be assigned to this parameter. The memory is at least 106K bytes.
 *
 * - Parameter values - lib_info
 *   @code {.c}
 *   calibre_proc_on
 *   calibre_proc_mode
 *   calibre_apply
 *   calibre_curve_addr Obsolete.
 *   Set calibre_proc_on = 0 and calibre_apply = 0.
 *   @endcode
 *
 * @subsection apis 3.2 APIs
 *
 * For parameters, refer to @ref audio_codec_block_diagram.
 *
 * - aacenc_setup<br>
 *   Description:<br>
 *   Initialize the AAC library. Assign the AAC data control structures to the internal operation variables.
 *   Confirm that the configurations are correct.<br>
 *   Syntax:
 *   @code {.c}
 *   void aacenc_setup(au_aacenc_config_t *pau_aacenc_config)
 *   @endcode
 *
 * - aacenc_open<br>
 *   Description:<br>
 *   Allocate the memory required for the AAC encode library.
 *   This function must be called before starting the AAC encoding.<br>
 *   Syntax:
 *   @code {.c}
 *   void aacenc_encode(au_aacenc_config_t *pau_aacenc_config)
 *   @endcode
 *
 * - aacenc_encode<br>
 *   Description:<br>
 *   Performs AAC encoding. One frame audio bit stream will be generated.
 *   This function must be called after the aac_setup and aac_open.<br>
 *   Syntax:
 *   @code {.c}
 *   void aacenc_encode(au_aacenc_config_t *pau_aacenc_config)
 *   @endcode
 *
 * @subsection sample_code 3.3 Sample Code
 *
 * Sample app: `test_aacenc.c`<br>
 * The following is an AAC encode operation example.
 * @code {.c}
 * // pseudo code
 * au_aacenc_config_t au_aacenc_config;
 * s32     inputBuffer[1024*2]
 * u8      outputBuffer[(6144/8)*2+100];
 * u8      enc_work_buf[106000];
 *
 * {
	 * // Set AAC encode control parameters
	 * au_aacenc_config.sample_freq = 48000;
	 * au_aacenc_config.Src_numCh = 2;
	 * au_aacenc_config.bitRate = 128000;
	 * au_aacenc_config.quantizerQuality = 1;
	 * au_aacenc_config.tns = 1;
	 * au_aacenc_config.ffType = 't';
	 * au_aacenc_config.enc_mode = AACPLAIN;
	 *
	 * au_aacenc_config.codec_lib_mem_adr = (u32*)enc_work_buf;
	 * au_aacenc_config.calibre_proc_on = 0;
	 * au_aacenc_config.calibre_apply = 0;
	 * aacenc_setup(&au_aacenc_config);
	 * aacenc_open(&au_aacenc_config);
	 *
	 * while (1) {
		 * // step 1: read source pcm data to inputBuffer
		 * // step 2: assign enc_rptr and enc_wptr
		 * au_aacenc_config.enc_rptr = inputBuffer;
		 * au_aacenc_config.enc_wptr = outputBuffer;
		 *
		 * // step 3: AAC encode one frame
		 * aacenc_encode(&au_aacenc_config);
		 *
		 * encoded_byte = (au_aacenc_config->nBitsInRawDataBlock + 7) >> 3;
		 * // step 4: write output the encode bitstream byte
	* }
 * }
 * @endcode
 *
 * - - - -
 *
 * @section audio_aac_dec 4. AAC Decode Library
 *
 * This section describes the data structure and APIs of the AAC decode library.
 *
 * @subsection decode_data_structure 4.1 Data Structure
 *
 * - Structure name：`au_aacdec_config_s`
 * <table>
 * <caption id="table_vsrc_lua"></caption>
 * <tr><th> <div style="width:240px"><B>Parameter</B></div>
 * <th> <div style="width:240px"><B>Description</B></div>
 * <tr><td> u32 sample_freq
 *     <td> Specifies the sample frequency
 * <tr><td> s8 syncState
 *     <td> Specifies the sync status
 * <tr><td> s8 channelMode
 *     <td> Specifies the channel mode
 * <tr><td> s32 bsFormat
 *     <td> Specifies the bitstream format (adif,adts,loas)
 * <tr><td> s32 streamType
 *     <td> Specifies the stream type
 * <tr><td> s32 objtype
 *     <td> Specifies the audio object type
 * <tr><td> s32 profile
 *     <td> Specifies the bitstream profile
 * <tr><td> s32 useHqSbr
 *     <td> Specifies the high quality SBR
 * <tr><td> s32 dec_mode
 *     <td> Specifies the decode mode (AAC, AAC+, AAC++)
 * <tr><td> s32 frameSize
 *     <td> Specifies the frame size
 * <tr><td> s32 Src_numCh
 *     <td> Specifies the input channel number
 * <tr><td> s32 Out_numCh
 *     <td> Specifies the output channel number
 * <tr><td> s32 averageBitrate
 *     <td> Specifies the average bit rate
 * <tr><td> s32 numberOfRawDataBlocks
 *     <td> Specifies the number of raw data blocks in frames
 * <tr><td> s32 bBitstreamDownMix
 *     <td> Specifies the stereo to mono down mix flag
 * <tr><td> s32 externalBitrate
 *     <td> Specifies the external bitrate for loading the input buffer
 * <tr><td> s32 externalSamplingRate
 *     <td> Specifies the external sampling rate for raw decoding
 * <tr><td> s32 ErrorStatus
 *     <td> Specifies the error status of decode process
 * <tr><td> s32 fs_out
 *     <td> Specifies the sample frequency of bitstream
 * <tr><td> s32 fs_out
 *     <td> Specifies the sample frequency of bitstream
 * <tr><td> s32 fs_core
 *     <td> Specifies the core sample frequency for AAC+ bitstream
 * <tr><td> s32 frameCounter
 *     <td> Specifies the frame counter of decode
 * <tr><td> s32 errorcounter
 *     <td> Specifies the error counter of decode
 * <tr><td> s32 errorcounter
 *     <td> Specifies the error counter of decode
 * <tr><td> s8 bDownSample
 *     <td> Specifies the down sampled SBR flag
 * <tr><td> u32 consumed_byte
 *     <td> Specifies the consumed byte of decoding one frame
 * <tr><td> u32 interbufsize
 *     <td> Specifies the internal buffer size
 * <tr><td> u32 interbufsize
 *     <td> Specifies the internal buffer size
 * <tr><td> s32* dec_wptr
 *     <td> Specifies the write pointer of output data
 * <tr><td> u8* dec_rptr
 *     <td> Specifies the read pointer of input bitstream
 * <tr><td> u8 has_dec_out
 *     <td> Specifies the decode output flag
 * <tr><td> u32* codec_lib_mem_adr
 *     <td> Specifies the address of library working memory
 * <tr><td> u8* codec_lib_backup_adr
 *     <td> Specifies the address of library backup memory
 * <tr><td> u16 codec_lib_backup_size
 *     <td> Specifies the size of library backup memory
 * <tr><td> u8 need_more
 *     <td> Specifies the need for more flags
 * <tr><td> audio_lib_info_t lib_info
 *     <td> Specifies the svn revision information of audio library
 * </table>
 * <br>
 *
 * - Parameter value - sample_freq<br>
 *   Obsolete.
 *
 * - Parameter value - syncState<br>
 *   Supported options:
 *   @code {.c}
 *   typedef enum {
 *   syncState_SyncWordSearch = 0, // start sync search
 *   syncState_SyncWordFound, // sync found, search of super frame forbidden
 *   syncState_SuperFrameSearch, // sync found, search of super frame allowed
 *   syncState_SuperFrameFound, // sync found, super frame found
 *   syncState_SyncFinished // sync search finished
 *   } AAC_DEC_SYNC_STATUS;
 *   @endcode
 *
 * - Parameter value - channelMode<br>
 *   Supported options:
 *   @code {.c}
 *   typedef enum {
 *   Mono=0x0,
 *   Stereo,
 *   DualMono,
 *   ParametricStereo,
 *   unkown_channel_mode = 0xf
 *   } AAC_DEC_Channel_Mode
 *   @endcode
 *
 * - Parameter value - bsFormat<br>
 *   Supported options:
 *   @code {.c}
 *   enum aac_bsformat {
 *   RAW_BSFORMAT = 0x0,
 *   ADIF_BSFORMAT,
 *   ADTS_BSFORMAT,
 *   LOAS_BSFORMAT, };
 *   @endcode
 *   Example: To decode a AAC bitstream with ADTS header,
 *   @code {.c}
 *   bsFormat = ADTS_BSFORMAT.
 *   @endcode
 *
 * - Parameter value - streamType<br>
 *   Supported options:
 *   @code {.c}
 *   typedef enum {
 *   MPEG4_BSFORMAT=0x0,
 *   MPEG2_BSFORMAT
 *   } AAC_DEC_MPEG_FMT;
 *   @endcode
 *
 * - Parameter value - objtype<br>
 *   Supported options: Reports the audio object type for LOAS bitstream.<br>
 *
 * - Parameter value - profile<br>
 *   Supported options: Reports the AAC profile of decoding bitstream.
 *
 * - Parameter value - useHqSbr<br>
 *   Supported options: Set by the AAC decode library.
 *   This parameter is set to "1" with decoding one channel AAC+ bitstream
 *   and "0" with decoding two channel AAC+ bitstream in the library.<br>
 *   1 (high quality sbr on), 0 (low power on).
 *
 * - Parameter value - dec_mode<br>
 *   Supported options:
 *   @code {.c}
 *   typedef enum {
 *   AACPLAIN, // aac encoding low complexity
 *   AACPLUS, // aacPlus encoding
 *   AACPLUS_SPEECH, // Not support
 *   AACPLUS_PS, // aacPlus encoding with parametric stereo
 *   AACPLUS_SPEECH_PS // Not support
 *   } AAC_MODE;
 *   @endcode
 *
 * - Parameter value - frameSize<br>
 *   Supported options:
 *   @code {.c}
 *   1024 (AACPLAIN)
 *   2048 (AACPLUS or AACPLUS_PS)
 *   @endcode
 *
 * - Parameter value - Src_numCh<br>
 *   Supported options:
 *   @code {.c}
 *   1 (MONO)
 *   2(STEREO)
 *   @endcode
 *
 * - Parameter value - Out_numCh<br>
 *   Supported options: Obsolete.
 *   @code {.c}
 *   1 (MONO), 2(STEREO)
 *   @endcode
 *
 * - Parameter value - averageBitrate<br>
 *   Supported options: Set by users with the input buffer size.
 *
 * - Parameter value - numberOfRawDataBlocks<br>
 *   Supported options: Reports the number of RAW data blocks in frames.
 *
 * - Parameter value - BitstreamDownMix<br>
 *   Supported options: Sets by the AAC decoder library with "0".
 *   @code {.c}
 *   1 (Stereo to mono downmix on), 0 (Stereo to mono downmix off)
 *   @endcode
 *
 * - Parameter value - externalBitrate<br>
 *   Obsolete.
 *
 * - Parameter value - externalSamplingRate<br>
 *   Supported options:
 *   @code {.c}
 *   #define AUDIO_FS_48000 48000
 *   #define AUDIO_FS_44100 44100
 *   #define AUDIO_FS_32000 32000
 *   #define AUDIO_FS_24000 24000
 *   #define AUDIO_FS_22050 22050
 *   #define AUDIO_FS_16000 16000
 *   #define AUDIO_FS_12000 12000
 *   #define AUDIO_FS_11025 11025
 *   #define AUDIO_FS_8000 8000
 *   @endcode
 *   Limitation: This parameter must be set if the decoding bitstream is RAW.
 *
 * - Parameter value - ErrorStatus<br>
 *   Supported options:
 *   @code {.c}
 *   typedef enum {
 *   AAC_DEC_OK = 0x0,
 *   AAC_DEC_ADTS_SYNC_ERROR = 0x1000,
 *   AAC_DEC_LOAS_SYNC_ERROR,
 *   AAC_DEC_ADTS_SYNCWORD_ERROR,
 *   AAC_DEC_LOAS_SYNCWORD_ERROR,
 *   AAC_DEC_ADIF_SYNCWORD_ERROR,
 *   AAC_DEC_UNSUPPORTED_FORMAT,
 *   AAC_DEC_DECODE_FRAME_ERROR,
 *   AAC_DEC_CRC_CHECK_ERROR,
 *   AAC_DEC_INVALID_CODE_BOOK,
 *   AAC_DEC_UNSUPPORTED_WINOW_SHAPE,
 *   AAC_DEC_PREDICTION_NOT_SUPPORTED_IN_LC_AAC,
 *   AAC_DEC_UNIMPLEMENTED_CCE,
 *   AAC_DEC_UNIMPLEMENTED_GAIN_CONTROL_DATA,
 *   AAC_DEC_UNIMPLEMENTED_EP_SPECIFIC_CONFIG_PARSE,
 *   AAC_DEC_UNIMPLEMENTED_CELP_SPECIFIC_CONFIG_PARSE,
 *   AAC_DEC_UNIMPLEMENTED_HVXC_SPECIFIC_CONFIG_PARSE,
 *   AAC_DEC_OVERWRITE_BITS_IN_INPUT_BUFFER,
 *   AAC_DEC_CANNOT_REACH_BUFFER_FULLNESS,
 *   AAC_DEC_TNS_RANGE_ERROR,
 *   AAC_DEC_NEED_MORE_DATA,
 *   AAC_DEC_INSUFFICIENT_BACKUP_MEMORY
 *   } AAC_DEC_Status;
 *   @endcode
 *
 * - Parameter value - fs_out<br>
 *   Supported options: This is the same as the externalSamplingRate supported option.
 *
 * - Parameter value - fs_core<br>
 *   Supported options:
 *   @code {.c}
 *   #define AUDIO_FS_24000 24000
 *   #define AUDIO_FS_22050 22050
 *   #define AUDIO_FS_16000 16000
 *   #define AUDIO_FS_12000 12000
 *   #define AUDIO_FS_11025 11025
 *   #define AUDIO_FS_8000 8000
 *   @endcode
 *
 * - Parameter value - frameCounter<br>
 *   Supported options: Reports the frame counter.
 *
 * - Parameter value - errorcounter<br>
 *   Supported options: Reports the error counter.
 *
 * - Parameter value - DownSample<br>
 *   Supported options: Set by the AAC decode library with "0".
 *   @code {.c}
 *   0(downsampled sbr off), 1(downsampled sbr on)
 *   @endcode
 *
 * - Parameter value - consumed_byte<br>
 *   Supported options: Reports the consumed byte when calling decoding APIs.
 *
 * - Parameter value - interbufsize<br>
 *   Supported options: Set by users with the internal buffer size.
 *
 * - Parameter value - dec_wptr<br>
 *   Supported options: This parameter is the write pointer of decoding bitstream.
 *   A memory address must be assigned to this parameter.
 *   The decoding output PCM format is 32 bits resolution.
 *   @code {.c}
 *   Stereo: L(32bit) R(32bit) L(32bit) R(32bit) ...
 *   Mono: L(32bit) L(32bit) L(32bit) L(32bit) ...
 *   @endcode
 *
 * - Parameter value - dec_rptr<br>
 *   Supported options: This parameter is the read pointer of decoding bitstream.
 *   A memory address must be assigned to this parameter.
 *
 * - Parameter value - has_dec_out<br>
 *   Supported options: The AAC decode library will set has_dec_out=1 when AAC decoding is successful.
 *
 * - Parameter value - codec_lib_mem_adr<br>
 *   Supported options: This parameter is the address of the library’s working memory.
 *   A memory address must be assigned to this parameter.
 *   The memory is at least 106K bytes.
 *
 * - Parameter value - codec_lib_backup_adr<br>
 *   Supported options: This parameter is the address of the library’s backup memory.
 *   A memory address must be assigned to this parameter. The memory is at least 252K bytes.
 *
 * - Parameter value - codec_lib_backup_size<br>
 *   Supported options: This is necessary if two bitstreams are being decoded simultaneously.
 *   The backup size is at least 252K bytes.
 *
 * - Parameter value - need_more<br>
 *   Supported options: The AAC decode library will report the need for more flags
 *   if the decoding buffer is not enough.
 *
 * - Parameter value - lib_info<br>
 *   Obsolete.
 *
 * @subsection decode_apis 4.2 APIs
 *
 * - aacdec_setup<br>
 *   Description:<br>
 *   Initialize the AAC library. Assign the AAC decode data structures to the internal operation variables.
 *   Confirm that the configurations are correct.
 *   This function must be called as the first one.
 *   Syntax:
 *   @code {.c}
 *   void aacdec_setup(au_aacdec_config_t *pau_aacdec_config)
 *   @endcode
 *   Parameters:
 *   Please refer to Section @ref decode_data_structure 4.1 Data Structure.
 *
 * - aacdec_open<br>
 *   Description:<br>
 *   Allocate the memory required for the AAC decode library.
 *   This function must be called before starting the AAC decoding.
 *   Syntax:
 *   @code {.c}
 *   void aacdec_open(au_aacdec_config_t *pau_aacdec_config)
 *   @endcode
 *   Parameters:
 *   Please refer to Section @ref decode_data_structure 4.1 Data Structure.
 *
 * - aacdec_set_bitstream_rp<br>
 *   Description:<br>
 *   Initialize the internal bit stream buffer.
 *   This function must be called after <B>aacdec_setup</B> and <B>aacdec_open</B>.
 *   Syntax:
 *   @code {.c}
 *   void aacdec_set_bitstream_rp(au_aacdec_config_t *pau_aacdec_config)
 *   @endcode
 *   Parameters:
 *   Please refer to Section @ref decode_data_structure 4.1 Data Structure.
 *
 * - aacenc_decode<br>
 *   Description:<br>
 *   Perform AAC encoding and one frame audio sample will be generated.
 *   This function must be called after the <B>aacdec_setup, aacdec_open</B>
 *   and <B>aacdec_set_bitstream_rp</B> functions.
 *   Syntax:
 *   @code {.c}
 *   void aacdec_decode(au_aacdec_config_t *pau_aacdec_config)
 *   @endcode
 *   Parameters:
 *   Please refer to Section @ref decode_data_structure 4.1 Data Structure.
 *
 * @subsection decode_sample_code 4.3 Sample Code
 *
 * Sample app: `test_aacdec.c`<br>
 * The following is an example of the AAC decode operation.
 * @code {.c}
 * // pseudo code
 * au_aacdec_config_t au_aacdec_config;
 * u8 input_Buffer[16384];
 * u32 dec_work_buf[106000];
 * u8 dec_backup_buf[252];
 * {
 * // Set AAC decode control parameters
 * au_aacdec_config.externalSamplingRate = 48000;
 * au_aacdec_config.bsFormat = ADTS_BSFORMAT;
 * au_aacdec_config.Out_numCh = 2;
 * au_aacdec_config.externalBitrate = 0;
 * au_aacdec_config.frameCounter = 0;
 * au_aacdec_config.errorcounter = 0;
 * au_aacdec_config.interbufsize = 0;
 * au_aacdec_config.codec_lib_mem_adr = dec_work_buf;
 * au_aacdec_config.codec_lib_backup_adr = dec_backup_buf;
 * au_aacdec_config.codec_lib_backup_size = 0;
 * au_aacdec_config.dec_rptr = input_Buffer;
 *
 * aacdec_setup(&au_aacdec_config);
 * aacdec_open(&au_aacdec_config);
 *
 * aacdec_set_bitstream_rp(&au_aacdec_config);
 * do {
	 * // step 1: read bitstream to input Buffer
	 *
	 * // step 2: initialize the internal bit stream buffer
	 * aacdec_set_bitstream_rp(&au_aacdec_config);
	 *
	 * // step 3: AAC decode one frame
	 * aacdec_decode(&au_aacdec_config);
	 * if (au_aacdec_config.ErrorStatus)
		 * break;
	 * // step 4 : write audio channels sample to pcm file
	 * if (au_aacdec_config.frameCounter>0) {
		 * fwrite(&buff[0], sizeof(s16),
				 * * au_aacdec_config.frameSize * au_aacdec_config.Src_numCh,
				 * pOutputFile);
		 * }
	 * } while (!au_aacdec_config.ErrorStatus);
 * }
 * @endcode
 * - - - -
 *
 * @section audio_mic_sup 5. CV5x EVK with Analog and Digital MIC Support
 *
 * This section describes how to enable nau8810(analog MIC) and DMIC(digital MIC) on CV5x EVK board.
 *
 * @subsection cv52_zr_and_cv5_Timn 5.1 CV52_Zr/CV5_Timn
 *
 * On CV5x EVK board, the nau8810 and DMIC cannot be enabled at the same time. By default, nau8810 is enabled.
 * If users want to enable DMIC, they can refer to the following steps.
 * @note
 * CV52_Zr board and CV5_Timn board are similar in this section.
 *
 * - Activate the option under menuconfig_public_linux<br>
 *   Users need to enable "Ambarella DMIC" in "menuconfig_public_linux" to compile it.
 *   @code {.c}
 *   build $ make menuconfig_public_linux
 *
 *   Device Drivers  --->
 *     <M> Sound card support  --->
 *       <M>   Advanced Linux Sound Architecture  --->
 *         <M>   ALSA for SoC audio support  --->
 *           <M>   Select Codec for Ambarella Platform  --->
 *             <M>   Ambarella DMIC
 *   @endcode
 *
 * - Make some modifications on SDK 1.0<br>
 *   <B>CV52_Zr board</B>: Modify `ambarella/boards/cv52_zr/bsp/cv52_zr.dts`<br>
 *   <B>CV5_Timn board</B>: Modify `ambarella/boards/cv5_timn/bsp/cv5_timn.dts`<br>
 *   Both modifications are the same, and CV52_Zr board is taken as an example below.
 *   @code {.c}
 *   @@ -52,17 +52,9 @@
 *   };
 *
 *   sound {
 *   -               compatible = "ambarella,audio-board";
 *   -               simple-audio-card,name = "nau8810 @ AMBEVK";
 *   +               compatible = "simple-audio-card";
 *   +               simple-audio-card,name = "Direct @ AMBEVK";
 *                   simple-audio-card,mclk-fs = <256>;
 *   -               simple-audio-card,widgets =
 *   -               "Speaker", "Speaker",
 *   -               "Microphone", "Mic Internal";
 *   -               simple-audio-card,routing =
 *   -               "MICP", "Mic Internal",
 *   -               "MICN", "Mic Internal",
 *   -               "Speaker", "SPKOUTP",
 *   -               "Speaker", "SPKOUTN";
 *
 *                   simple-audio-card,dai-link@0 {
 *                     format = "i2s";
 *
 *   @@ -72,7 +64,7 @@
 *                           };
 *
 *                           codec {
 *   -                               sound-dai = <&nau8810>;
 *   +                               sound-dai = <&dmic>;
 *                           };
 *                   };
 *
 *   @@ -98,7 +90,7 @@
 *
 *   #if defined(CONFIG_CV52_ZR_SELECT_IDC1_VSYNC)
 *                           pinctrl-names = "default";
 *   -                       pinctrl-0 = <&vsync_dly_pins>;
 *   +                       //pinctrl-0 = <&vsync_dly_pins>;
 *   #endif
 *                           clocks = <&gclk_so2>;
 *                   };
 *   @@ -340,6 +332,7 @@
 *   #endif
 *   };
 *   &i2s0 {
 *   +       pinctrl-0 = <&dmic0_pins_c>;
 *           status = "ok";
 *   };
 *   @endcode
 *
 * - HSYNC_DMIC_SEL pull high
 *   Set switch <B>1</B> to <B>ON</B> at DIP SW1.
 *   @image html DIP_SW1_diagram.jpg "Figure 5-1. Diagram of DIP_SW1"
 *//*!
 * @file file_system.h
 * @date 2021-09-15
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
 * @page si_fs File System
 *
 * @section fs_ubi 1. UBIFS (Recommended)
 *
 * Unsorted block image (UBI) file system (UBIFS) is a successor to JFFS2.
 * UBIFS functions with a UBI device,
 * which itself is on top of a memory technology device (MTD). This means that with UBIFS,
 * MTD is not used directly.<br>
 * There are two major advantages to using UBIFS rather than JFFS2:
 *   - UBIFS supports write caching and tolerates unclean reboots
 *   - UBIFS tends to perform better with fast input / output (I/O) and fast mount, when compared to JFFS2 for large NAND flash devices<br>
 *
 * For more information about UBIFS, refer to the following links:<br>
 *    <b>http://www.linux-mtd.infradead.org/doc/ubifs.html </b><br>
 *    <b>http://www.linux-mtd.infradead.org/faq/ubifs.html </b><br>
 * For more information about UBI, refer to the links below:<br>
 *    <b>http://www.linux-mtd.infradead.org/doc/ubi.html </b><br>
 *    <b>http://www.linux-mtd.infradead.org/faq/ubi.html </b><br>
 *
 * @subsection ubi_rootfs 1.1 Use UBIFS as Rootfs
 *
 * Ambarella recommends using UBIFS as the default root file system (rootfs) in the software development kit (SDK).<br>
 *
 * @par Execute the following command for CV2x SDK 3.0 Amba Build:
 *   @code {.c}
 *   build $ make menuconfig
 *   @endcode
 *
 * - Ambarella Firmware Configuration > AMBoot (boot loader) >
 *   Common Boot Options > () Booting cmdline<br>
 *   (`console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc</em>`)
 *   can be an input for this configuration.
 *   It will be brought into effect as an alternative to the boot arguments (bootargs) defined in device trees (DTS).
 *   If this configuration is left blank, the bootargs in DTS will function.
 *
 * - By default, boot arguments are defined in the DTS file:<br>
 *   `ambarella/boards/cvx_board/bsp/cvx_board.dts.`
 *   bootargs = "console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc"
 *
 * - Ambarella Firmware Configuration > AMBoot (boot loader) > Linux Partition >
 *   @code {.c}
 *   ($(AMB_BOARD_OUT)/ubifs) Linux FS image
 *   ($(AMBABUILD_TOPDIR)/amboot/vif/ubifs.info) Linux FS Version File
 *   @endcode
 *
 * - Ambarella File System Configuration > Linux Root File System > (X) UBIFS<br>
 *   Execute the following command:
 *   @code {.c}
 *   build $ make menuconfig_public_linux
 *   Device Drivers >
 *   	Memory Technology Device (MTD) support >
 *   		<*> Enable UBI - Unsorted block images
 *   File Systems >
 *   	[*] Miscellaneous filesystems >
 *   		<*> UBIFS file system support
 *   @endcode
 *   Execute the following command:
 *   @code {.c}
 *   build $ make
 *   @endcode
 *
 * @par Execute the following command for Cooper SDK Amba build:
 *
 *   @code {.c}
 *   build $ make menuconfig
 *   @endcode
 *
 * - boot (boot) > Bootloader > Ambarella Firmware Configuration > AMBoot Options >
 *   Common Boot Options > () Booting cmdline<br>
 *   (`console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc</em>`)
 *   can be input to this configuration.
 *   It will be brought into effect, rather than the bootargs defined in DTS.
 *   If this configuration is left blank, the bootargs in DTS will function.
 *
 * - By default, boot arguments are defined in the DTS file:<br>
 *   `ambarella/boards/cvx_board/bsp/cvx_board.dts.`
 *   bootargs = "console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc"
 *
 * - boot (boot) > Bootloader > Ambarella Firmware Configuration > Firmware Options > Linux Partition >
 *   @code {.c}
 *   ($(ENV_IMG_ROOT)/rootfs.ubi) Linux FS image
 *   ($(AMBOOT_TOPDIR)/vif/ubifs.info) Linux FS Version File
 *   @endcode
 *
 *   @code {.c}
 *   build $make menuconfig
 *   @endcode
 * - rootfs > rootfs (rootfs/system) > Linux Root File System (UBIFS) >
 *   Execute the following command:
 *   @code {.c}
 *   build $ make linux_menuconfig
 *   Device Drivers >
 *   	Memory Technology Device (MTD) support >
 *   		<*> Enable UBI - Unsorted block images
 *   File Systems >
 *   	[*] Miscellaneous filesystems >
 *   		<*> UBIFS file system support
 *   @endcode
 *   Execute the following command:
 *   @code {.c}
 *   build $ make
 *   @endcode
 *
 * @par Execute the following command for Cooper SDK Yocto build:
 *
 *   @code {.c}
 *   build $ make menuconfig
 *   @endcode
 *
 * - meta-ambabsp > recipes-bsp > boot (meta-ambabsp/recipes-bsp/boot) > Bootloader > Ambarella Firmware Configuration >
 *   AMBoot (boot loader) > Common Boot Options > () Booting cmdline<br>
 *   (`console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc</em>`)
 *   can be input to this configuration.
 *   It will be brought into effect, rather than the bootargs defined in DTS.
 *   If this configuration is left blank, the bootargs in DTS will function.
 *
 * - By default, boot arguments are defined in the DTS file:<br>
 *   `ambarella/boards/cvx_board/bsp/cvx_board.dts.`
 *   bootargs = "console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs init=/linuxrc"
 *
 * - meta-ambabsp > recipes-bsp > boot (meta-ambabsp/recipes-bsp/boot) > Bootloader > Ambarella Firmware Configuration >
 *   Firmware Options > Linux Partition >
 *   @code {.c}
 *   ($(ENV_IMG_ROOT)/rootfs.ubi) Linux FS image
 *   ($(AMBOOT_TOPDIR)/vif/ubifs.info) Linux FS Version File
 *   @endcode
 *
 *   @code {.c}
 *   build $make menuconfig
 *   @endcode
 * - meta-ambabsp > recipes-bsp > [*] amrootfs (meta-ambabsp/recipes-bsp)/amrootfs >
 *   Linux Root File System (UBIFS) >
 *   Execute the following command.
 *   @code {.c}
 *   build $ make linux_menuconfig
 *   Device Drivers >
 *   	Memory Technology Device (MTD) support >
 *   		<*> Enable UBI - Unsorted block images
 *   File Systems >
 *   	[*] Miscellaneous filesystems >
 *   		<*> UBIFS file system support
 *   @endcode
 *   Execute the following command:
 *   @code {.c}
 *   build $ make
 *   @endcode
 *
 * @subsection ubi_test 1.2 Test UBIFS
 *
 * <B>UBI utils</B> is compiled from the mtd-utils project (http://elinux.org/CompilingMTDUtils).
 *
 * 1. Execute the following command.
 * @code {.c}
 * build $ make menuconfig
 * Ambarella File System Configuration >
 * 	Third Party Software / Libraries >
 *		Filesystem Tools >
 *			[*] Add ubi tools into root_fs
 * Ambarella Unit Test Configuration >
 * 	Ambarella Public Linux Unit test configs >
 *		[*] Build Ambarella Public Linux Flash FS unit tests
 * @endcode
 *
 * @code {.c}
 * build $ make menuconfig
 * Ambarella File System Configuration >
 *	Third Party Software / Libraries >
 *		Filesystem Tools >
 *			[*] Add ubi tools into root_fs
 * Ambarella Unit Test Configuration >
 *	Ambarella Public Linux Unit test configs >
 *		[*] Build Ambarella Public Linux Flash FS unit tests
 * @endcode
 * @note
 * The following steps must be performed on a partition that does not include critical system information.
 * To determine the current partition on the board, use `cat /proc/mtd`.
 * The size of this partition must be larger than 20 MB.
 *
 * 2. If this is the first time using the UBIFS partition (such as MTD6), the following procedure is required:
 * @code {.c}
 * board # flash_eraseall /dev/mtd6
 * board # ubiattach /dev/ubi_ctrl -m 6
 * board # ubimkvol /dev/ubi1 -s 20000000 -N usr_a
 * @endcode
 * (usr_a and usr_b are volume names)
 * @code {.c}
 * boadr # mkdir /tmp/ubi_v
 * board # mount -t ubifs ubi1_0 /tmp/ubi_v
 * @endcode
 * Copy a file to the UBIFS directory.
 * @code {.c}
 * board # umount /tmp/ubi_v
 * board # reboot
 * @endcode
 *
 * 3. After the board reboots:
 * @code {.c}
 * board # ubiattach /dev/ubi_ctrl -m 6
 * board # ubinfo -a
 * board # mkdir /tmp/ubi_v
 * board # mount -t ubifs ubi1_0 /tmp/ubi_v
 * board # ls /tmp/ubi_v -la
 * @endcode
 *
 * 4. Test UBIFS.
 * @code {.c}
 * board # touch /tmp/ubi_v/ubi_tmp_file
 * board # test_ffs /tmp/ubi_v/ubi_tmp_file
 * # test_ffs
 * default to read file /tmp/ubi_v/ubi_tmp_file
 * start time      [946686070s:126607us]
 * end time        [946686070s:129973us]
 * spend [3366us] to read 0 MB data
 * flash fs read speed is 0.000000 MB/s
 * start time      [946686070s:139273us]
 * end time        [946686072s:159527us]
 * spend [2020254us] to write 16 MB data
 * flash fs write speed is 7.919796 MB/s
 * @endcode
 *
 * @note
 * Because the file is buffered in memory after the test,
 * reboot before any additional round of testing.
 *
 * - - - -
 *
 * @section fs_jffs 2. JFFS2
 *
 * Journalling flash file system version 2 (JFFS2) is a log-structured file system
 * for use with flash memory devices.
 * Rather than using a type of translation layer on flash devices to emulate a normal hard drive,
 * it places the file system directly on the flash chips.<br>
 * The latest JFFS2 code can be found at http://www.jffs.net/.
 *
 * @subsection use_jffs2_as_rootfs 2.1 Use JFFS2 as Rootfs
 *
 * 1. Execute the following command.
 * @code {.c}
 * build $ make menuconfig
 * @endcode
 *
 *   - Ambarella Firmware Configuration > AMBoot (boot loader) > Common Boot Options > () Boot cmdline
 * @code {.c}
 * (console=ttyS0 root=/dev/mtdblock7 rw rootfstype=jffs2 init=/linuxrc) can be input into this config,
 * and will be brought into effect, rather than the bootargs defined in DTS.
 * If this config is left blank, the bootargs in DTS will become effective.
 * root=/dev/mtdblock7 depends on the system.
 * To find out the current Linux partition on the board, use cat /proc/mtd.
 * @endcode
 *
 *   - Ambarella Firmware Configuration > AMBoot (boot loader) > Linux Partition >
 * @code {.c}
 * ($(AMB_BOARD_OUT)/rootfs/jffs2) Linux FS image
 * ($(AMBABUILD_TOPDIR)/amboot/vif/jffs2.info) Linux FS Version File
 * @endcode
 *
 *   - Ambarella File System Configuration > Linux Root File System > (X) JFFS2
 *
 * 2. Execute the following command.
 * @code {.c}
 * build $ make defconfig_public_linux
 * build $ make menuconfig_public_linux
 * File systems >
 *    [*] Miscellaneous filesystems >
 *       <*> Journalling Flash File System v2
 *           (JFFS2) support
 * @endcode
 *
 * 3. Execute the following command.
 * @code {.c}
 * build $ make
 * @endcode
 *
 * @subsection test_jffs2 2.2 Test JFFS2
 *
 * 1. If this is the first time that the JFFS2 partition (such as MTD6) is used,
 * the following procedure is required.
 * @code {.c}
 * board # flash_eraseall /dev/mtd6
 * board # mkdir /mnt/ffs/
 * board # mount -t jffs2 /dev/mtdblock6 /mnt/ffs/
 * @endcode
 *
 *   Copy the file to the JFFS2 directory.
 * @code {.c}
 * board # umount /mnt/ffs/
 * board # reboot
 * @endcode
 *
 * 2. After the board reboots:
 * @code {.c}
 * board # mkdir /mnt/ffs/
 * board # mount -t jffs2 /dev/mtdblock6 /mnt/ffs/
 * board # ls /mnt/ffs/ -la
 * @endcode
 *
 * 3. Test JFFS2.
 * @code {.c}
 * board # touch /mnt/ffs/jffs2
 * board # test_ffs /mnt/ffs/jffs2
 * start time [946684933s:925416us]
 * end time [946684933s:927988us]
 * spend [2572us] to read 0 MB data
 * flash fs read speed is 0.000000 MB/s
 * start time [946684933s:937284us]
 * end time [946684937s:554533us]
 * spend [3617249us] to write 16 MB data
 * flash fs write speed is 4.423251 MB/s
 * @endcode
 *
 * @note
 * The file is buffered in memory after the test; reboot before another round of testing is performed.
 *
 * - - - -
 *
 * @section fs_ext4 3. Ext4
 *
 * Ext4 is the latest generation of the Ext3 file system.
 * Unlike the upgrade from Ext2 to the Ext3 file system,
 * the on-disk format of Ext4 is not forward-compatible with Ext3,
 * as it is based on extent maps and supports 48-bit physical block numbers.
 * Ext4 supports delayed allocation, persistent pre-allocation, high-resolution time stamps,
 * and a number of other features that improve the performance and speed of FSCK time.<br>
 * For more information, refer to the web page http://ext4.wiki.kernel.org.
 *
 * @subsection use_ext4_as_rootfs 3.1 Use Ext4 as Rootfs
 *
 * Ambarella recommends using the Ext4 file system with embedded multi-media card / controller (eMMC) flash.
 *
 * 1. Execute the following command.
 *   @code {.c}
 *   build $ make menuconfig
 *   @endcode
 *   - Ambarella Firmware Configuration > AMBoot (boot loader) > Boot Media (Boot From eMMC)
 *   - Ambarella Firmware Configuration > AMBoot (boot loader) > Common Boot Options >
 *     (console=ttyS0 noinitrd root=/dev/mmcblk0p7 rw rootfstype=ext4 init=/linuxrc) Booting cmdline
 *   - Ambarella Firmware Configuration > AMBoot (boot loader) > Linux Partition >
 *     @code {.c}
 *     ($(AMB_BOARD_OUT)/ext4) Linux FS image
 *     ($(AMBABUILD_TOPDIR)/amboot/vif/extx.info) Linux FS Version File
 *     @endcode
 *   - Ambarella File System Configuration > Linux Root File System > (X) EXT4
 *
 * 2. Execute the following command.
 *   @code {.c}
 *   build $ make menuconfig_public_linux
 *   File systems >
 *       <*> The Extended 4
 *           (ext4) filesystem
 *   @endcode
 *
 * 3. Execute the following command.
 *   @code {.c}
 *   build $ make
 *   @endcode
 *
 * - - - -
 *
 * @section fs_exfat 4. ExFAT
 *
 * ExFAT is an extension of the traditional FAT file system
 * and is optimized for flash memory, such as USB flash drives and SD cards.
 * Compared to FAT, ExFAT has better scalability to large disk sizes and
 * more efficient write operation.
 * ExFAT contains features such as boundary alignment for file system structures
 * and OEM parameters that makes ExFAT flash-friendly.<br>
 * For more information, refer to the web page https://en.wikipedia.org/wiki/ExFAT.
 *
 * @subsection use_exfat_for_flash_cards 4.1 Enable ExFAT
 *
 * Ambarella recommends using the ExFAT file system with USB flash drives and SD cards.
 *
 * 1. Execute the following command.
 *   @code {.c}
 *   build $ make menuconfig
 *   @endcode
 *   @code {.c}
 *   Ambarella File System Configuration >
 *   	Open Source Software (OSS) >
 *   	  Filesystem Tools >
 *          [*] Add fuse-exfat support
 *          [*]   Add exfat-utils support
 *   @endcode
 * 2. Execute the following command.
 *   @code {.c}
 *   build $ make
 *   @endcode
 */
/*!
 * @file nand.h
 * @date 2021-09-15
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
 * @page si_nand NAND
 *
 * The computer vision (CV) series system on chip (SoC) can be configured to enable NAND- or NOR-flash controller logic.
 * When the power-on-configuration uses NAND, the system boots from the NAND devices.
 *
 * @section ecc_level 1. ECC Level
 *
 * The SoC can support 6-bit or 8-bit error correcting code (ECC) levels.
 * The ECC level depends on the power-on configuration (POC) (15,16) (VD0_OUT15, I2S0_SO).
 * ECC level depends on POC (15, 16).
 * @code {.c}
 * 6-bit ECC level: [15, 16] = 01
 * 8-bit ECC level: [15, 16] = 11
 * @endcode
 *
 * The SoC supports both 6-bit and 8-bit ECC in the kernel.
 * When using ECC 8-bit mode, the NAND flash should have a (2K + 128) byte page size.<br>
 * Note that it must `"erase all"` before downloading the firmware to avoid an ECC error
 * when changing the ECC level.<br>
 * The software settings are as follows.
 * @par For CV2x SDK 3.0 Amba Build:
 * @code {.c}
 * build $ make menuconfig
 *   Ambarella Firmware Configuration --->
 *     Hardware Options --->
 *       [*] Support NAND Driver
 *           NAND Flash Type (P2K E128K) --->
 * @endcode
 *
 * @par For Cooper Amba Build:
 * @code {.c}
 * build $ make menuconfig
 *   [*] boot (boot) --->
 *     Bootloader --->
 *       Ambarella Firmware Configuration  --->
 *         Hardware Options --->
 *           [*] Support NAND Driver
 *             NAND Flash Type (P2K E128K) --->
 * @endcode
 *
 * @par For Cooper Yocto Build:
 * @code {.c}
 * build $ make menuconfig
 *   meta-ambabsp --->
 *     recipes-bsp --->
 *       [*] boot (meta-ambabsp/recipes-bsp/boot) --->
 *         Bootloader --->
 *           Ambarella Firmware Configuration  --->
 *             Hardware Options --->
 *               [*] Support NAND Driver
 *                 NAND Flash Type (P2K E128K) --->
 * @endcode
 *
 * The system supports 6-bit / 8-bit software ECC; users can select the option
 * on the Linux kernel configuration.
 * In addition, the 6-bit / 8-bit software is controlled by the POC.<br>
 * When using software ECC in the kernel, users must make the following changes in the DTS file.<br>
 * To enable the "amb, soft-ecc" feature:
 * @code {.c}
 * "kernel/linux-5.x/arch/arm64/boot/dts/Ambarella/ambarella-cvx.dtsi"
 * - // amb, soft-ecc = <6>;
 * + amb, soft-ecc = <8>;
 * @endcode
 * After the system boots up, users can check BCH 8-bit mode with the command `"dmesg | grep ecc"`.
 *
 * ---
 *
 * @section boot_flow 2. Boot Flow
 *
 * @subsection nand_boot_flow 2.1 NAND Boot Flow: Boot Sequence
 *
 * @image html nand_hardware_reset_sequences.png "Figure 2-1. Hardware Reset Sequences."
 * The boot sequence from hardware reset is as follows:
 * 1. The hardware fetches the first 4 KB (the first page in the first block) of NAND
 *   to the 4 KB buffer of flash I/O FIFO and executes the 4-KB codes.<br>
 * 2. The 4 KB bootstrap (BST) initializes the double data rate (DDR) controller and the dynamic random-access memory (DRAM) device.<br>
 * 3. The bootstrap relocates itself in DRAM and enables FIFO for the NAND transaction.<br>
 * 4. The bootstrap runs in DRAM and loads the bootloader (BLD) to DRAM.
 *   After the BLD is loaded completely, it jumps to the BLD codes.<br>
 * 5. The BLD initializes the memory management unit and page tables.<br>
 * 6. The BLD loads the Linux kernel image from the NAND primary partition (PRI).<br>
 * 7. (Optional) The BLD loads the root file system image from the Linux partition.<br>
 * 8. The BLD jumps to the Linux kernel codes in the memory and completes the bootup process.
 *   The address of the Linux kernel code is 0x00208000 for most cases.
 *
 * @subsection nand_boot_flow_llf 2.2 NAND Boot Flow: Load Linux Kernel and File System
 *
 * AMBoot does not support the decompress functionality; all decompression is completed through the kernel.
 * In the default configuration, the Linux kernel image is uncompressed and the file system is compressed.
 * The Linux kernel performs the decompression.<br>
 * If both the Linux kernel and the file system are compressed,
 * copy the compressed images to the working DRAM space.h
 * The kernel compresses both (zImage).<br>
 * The following figure illustrates the process;
 * the BLD loads additional program images from the NAND partition.
 *
 * @image html nand_load_linux_kernel_and_file_system.png "Figure 2-2. Load Linux Kernel and File System."
 *
 * The following describes the sequence of the NAND boot flow:
 *  1. The BLD reads out the partition table (PTB) from the PTB partition.<br>
 *  2. The BLD determines the following:
 *   - Linux kernel image size
 *   - Linux kernel image load address
 *   - Ramdisk file system image size (optional)
 *   - Ramdisk file system load address (optional)<br>
 *  3. The BLD loads the Linux kernel image to DRAM.<br>
 *  4. The BLD loads the Ramdisk file system to DRAM (optional).
 */
/*!
 * @file emmc.h
 * @date 2021-09-15
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
 * @page si_emmc EMMC
 *
 * @section hardware_setting 1. Hardware Setting
 *
 * The Cooper system on chip (SoC) can be configured to enable the eMMC controller.
 * When the power-on configuration uses eMMC, the system boots from the eMMC devices.
 * Because the EVK board default configuration uses NAND flash as a storage / boot media,
 * a hardware rework is required to support the eMMC devices, and an SDIO interface is used.
 * If the eMMC is the boot up device, a proper POC setup is also required.<br>
 * Refer to <em>Ambarella DG Flexible Linux SDK NAND NOR Flash EMMC Selection Qualification</em>
 * for verified eMMC information.
 *
 * @subsection poc_setting 1.1 POC Setting
 *
 * `POC[5:4](BOOT MODE)` are used to set the booting media, POC[4:5]=0b01 means to boot up from eMMC.<br>
 * `POC[21, 20:14](BOOT OPTION[8:1])` are used to configure detailed options.<br>
 * Set them according to the hardware design and eMMC specifications.
 * Bus width must be chosen between 4 bits and 8 bits.
 *
 * <table>
 * <caption id="table_vsrc_lua"></caption>
 * <tr><th> <div><B>POC</B></div>
 * <th> <div><B>POC Function</B></div>
 * <th> <div><B>POC Value 1</B></div>
 * <th> <div><B>POC Value 0</B></div>
 * <th> <div><B>Recommended Settings</B></div>
 * <tr><td> BOOT OPTION[8]
 *     <td> MMC controller choose
 *     <td> use legacy MMC controller
 *     <td> use Synposys MMC controller
 *     <td> 1
 * <tr><td> BOOT OPTION[6]
 *     <td> tRSCA sel boot delay
 *     <td> tRSCA=10000 SD clock cycles
 *     <td> tRSCA=75 SD clock cycles
 *     <td> 0 by default Depends on the eMMC
 * <tr><td> BOOT OPTION[5]
 *     <td> tRSCA enable boot delay
 *     <td> Enable the tRSCA delay during the boot initialization
 *     <td> Disable the tRSCA delay during the boot initialization
 *     <td> 1
 * <tr><td> BOOT OPTION[4]
 *     <td> eMMC enable reset
 *     <td> Controller will drive sd_reset pin
 *     <td> Controller will not drive sd_reset pin
 *     <td> 1
 * <tr><td> BOOT OPTION[3]
 *     <td> eMMC boot sd pull
 *     <td> Internal pull-high on sd_cmd and sd_d[7:0]
 *     <td> No pull on sd_cmd and sd_d[7:0]
 *     <td> 1
 * <tr><td> BOOT OPTION[2]
 *     <td> 4-bit bus width
 *     <td> Use 4-bit data pins for booting
 *     <td> x
 *     <td> Depends on the design
 * <tr><td> BOOT OPTION[1]
 *     <td> 8-bit bus width
 *     <td> Use 8-bit data pins for booting
 *     <td> x
 *     <td> Depends on the design
 * </table>
 * <br>
 *
 * @image html emmc_example_of_trsca_timing_specification.png "Figure 1-1. Example of tRSCA Timing Specification."
 *
 * CV5 Timn EVK<br>
 *  - SW7[7] – ON, SW7[6] - OFF
 *  - SW6[1] - ON
 *
 * @note
 * For Option B, the Max Clock of SD0 needs to be lowered to <b>50MHz</b> (current is 100MHz).
 *
 * The following shows pins, bits, and clock reates for eMMC boot options.
 * @par Pins, Bits, and Clock Rates for eMMC Boot Options
 * <table>
 * <caption id="table_emmc_boot"></caption>
 * <tr><th> <div>Option A</div>  <th>      <th colspan="4"> <div>For eMMC Boot</div>
 * <tr><td> <b>Pins</b>  <td> <b>Bits</b>  <td> <b>POC17/<b>  <td> <b>POC21</b>  <td> <b>eMMC Boot</b>  <td> <b>Max Clock(MHz)</b>
 * <tr><td> SD0          <td> 8            <td> 1             <td> 1             <td> o                 <td> 200
 * <tr><td> SDIO0        <td> 4            <td> 1             <td> 1             <td> x                 <td> 200
 * <tr><td> SDIO1        <td> 4            <td> 1             <td> 1             <td> x                 <td> 50
 * <tr><th> <div>Option B</div>  <th>      <th colspan="4"> <div>For eMMC Boot</div>
 * <tr><td> <b>Pins</b>  <td> <b>Bits</b>  <td> <b>POC17/<b>  <td> <b>POC21</b>  <td> <b>eMMC Boot</b>  <td> <b>Max Clock(MHz)</b>
 * <tr><td> SD0          <td> 8            <td> 1             <td> 1             <td> o                 <td> 50
 * <tr><td> SDIO0        <td> 4            <td> 1             <td> 1             <td> x                 <td> 200
 * <tr><td> SDIO1        <td> 4            <td> 1             <td> 1             <td> x                 <td> 200
 * </table>
 *
 * @note
 *  -  Option A is eMMC boot and SD0 8-bit with maximum clock rate 200 MHz, but SDIO1 maximum clock reta supports 50 MHz only.<br>
 *  -  Option B is eMMC boot and SD0 8-bit maximum clock rate 50 MHz, and the SDIO1 maximum clock reta can be up to 200 MHz.
 *
 * Contact the Ambarella support team for further questions.
 *
 * ---
 *
 * @section configuration_and_compile 2. Configuration and Compile
 *
 * The default eMMC configuration is as follows:
 * @code {.c}
 * build $ make cv5x_ipcam_emmc_config
 * @endcode
 *
 * in `SDK/ambarella/board/cv5x_board`.
 * @code {.c}
 * build $ make sync_build_mkcfg
 * build $ make cv5x_ipcam_emmc_config
 * build $ make -j8
 * @endcode
 *
 * Ambarella highly recommends that the eMMC boot functions with Ext4 file system, which is the default configuration.
 * For more information about the Ext4 file system, refer to @ref fs_ext4 <br>
 * When using eMMC boot, don't enable 'fdisk'. Because it is not supported by eMMC boot. If users download a firmware
 * into the board with 'fdisk' enabled accidentally, they need to erase the whole eMMC before downloading a new firmware.
 * Else, the board can't boot up normally. <br>
 * After building the binary, select the board configuration with "eMMC", and then download the binary to EVK boards.
 *
 * @note
 * 1. Forcing USB boot is required to successfully flash the binary
 * if the boot media is switched from NAND to eMMC (or vice versa). <br>
 * 2. When downloading a firmware whose size is larger than 1 GB, users must increase the timeout period in case of hitting timeout issue.
 * They should modify "TransTimeOutMS = 5000" in AmbaUSB.conf file, which locates in "ambausb/share/ambausb-x.x.x" of AmbaUSB installation folder.
 * "TransTimeOutMS = 5000" means that the timeout is 5 s.  They can enlarge it to "TransTimeOutMS = 10000"(10 s) or even larger depending on the firmware size. <br>
 * 3. The maximum firmware size that can be downloaded by AmbaUSB must be less than CV5x set's DRAM size.
 * 4. SD slot 2 cannot enable ultra high speed when EMMC boot is enabled.
 *
 */
/*!
 * @file debugfs.h
 * @date 2021-09-15
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
 * @page si_debugfs Debugfs
 *
 * Debugfs is an easy-to-use RAM-based file system specially designed for debugging purposes.
 * The CONFIG_DEBUG_FS option is set to "yes" by default.
 * It is mounted at `/sys/kernel/debug` on the EVK board.
 * If it is not mounted, Debugfs could mount with a command given below:
 * @code {.c}
 * board # mount -t debugfs debugfs /debug
 * @endcode
 *
 *
 * @section gpio_debug 1. GPIO Debug
 *
 * General purpose input/output (GPIO) status can be obtained by a command from the Debugfs as follows:
 * @code {.c}
 * board # cat /sys/kernel/debug/gpio
 * GPIOs 0-127, platform/gpio.0, ambarella-gpio:
 * GPIO[0]: [0 - 31]
 * GPIO_BASE: 0xE8009000
 * GPIO_AFSEL: 0xFFDF0F1E
 * GPIO_DIR: 0x000000A1
 * GPIO_MASK: 0x00000080:0x0020F0E1
 * GPIO_DATA: 0x00200081
 * IOMUX_REG0_0: 0xF0D0001E
 * IOMUX_REG0_1: 0x01DF0F00
 * IOMUX_REG0_2: 0x0E000000
 * gpio-0 [GPIO] (sd ext power ) out hi
 * gpio-1 [HW ] (alt1)
 * gpio-2 [HW ] (alt1)
 * gpio-3 [HW ] (alt1)
 * gpio-4 [HW ] (alt1)
 * gpio-5 [GPIO] ( ) out lo
 * @endcode
 *
 * If the GPIO is not occupied by the other driver, it can be read and written to `amba_debug/ambad.ko`.
 *  1. Set the GPIO as input (use GPIO 5 for example):
 *    @code {.c}
 *    board # amba_debug -g 5
 *    board # grep gpio-5 /sys/kernel/debug/gpio
 *    gpio-5 [GPIO] ( ) in high
 *    @endcode
 *
 *  2. Set the GPIO as output high (use GPIO 5):
 *    @code {.c}
 *    board # amba_debug -g 5 -d 0x1
 *    board # grep gpio-5 /sys/kernel/debug/gpio
 *    gpio-5 [GPIO] ( ) out high
 *    @endcode
 *
 *  3. Set the GPIO as output low (use GPIO 5):
 *    @code {.c}
 *    board # amba_debug -g 5 -d 0x0
 *    board # grep gpio-5 /sys/kernel/debug/gpio
 *    gpio-5 [GPIO] ( ) out low
 *    @endcode
 */
/*!
 * @file usb.h
 * @date 2021-09-15
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
 * @page si_usb USB
 *
 * The CV5x USB 3.2 Gen-2 port supports both device and host modes. The USB 2.0 port only supports device mode.
 *
 * Device mode can be used to perform flash direct downloading, mass storage, virtual Ethernet device,
 * and serial downloading.
 * Host mode can be used to connect with USB storage, USB WiFi, and the USB mouse / keyboard.
 *
 *
 * @section usb_device 1. USB Device
 *
 * 1. Set the USB to function on "device" mode.
 *   @code {.c}
 *   board # usb_role_switch.sh device
 *   [   33.795578] cdns-usb3 2020008000.cdns3: Rev: 00000204/00001c7d, eps: 00ff00ff, buff: 04000010/03000020
 *   @endcode
 *
 * 2. Confirm that the USB is functioning on "device" mode.
 *   @code {.c}
 *   board # cat cat /sys/class/usb_role/2020008000.cdns3-role-switch/role
 *   device
 *   @endcode
 *
 * @subsection ud_usb_mass_storage 1.1 USB Device: USB Mass Storage
 *
 * The CV5x platform can use the free partition for a mass storage.<br>
 * - USB mass storage: USB storage requirements
 *   - The CV5x platform
 *   - The USB storage driver (g_mass_storage.ko)
 *     @code {.c}
 *     build $ make menuconfig_public_linux
 *       Device Drivers -->
 *         [*] USB supports -->
 *             <M> USB Mass Storage Support
 *     @endcode
 *   - Unused partition or space
 *
 * - USB mass storage: testing the USB storage
 *   1. Confirm that the USB is functioning on "device" mode and the module ambarella_udc is loaded into the system.
 *     @code {.c}
 *     board # usb_role_switch.sh device
 *     @endcode
 *   2. The first time the USB is used as a mass storage device,
 *     confirm that the unused partition of the board will be used for storage.
 *     If it is not formatted to the correct file system, skip to Section @ref fs_ubi
 *     to set up unsorted block image file system (UBIFS) on the partition and mount it to /mass_storage.
 *     If UBIFS is not directly supported by the PC, Vfat is required.
 *     Users can create a Vfat file system with the commands below.<br>
 *     In the following commands, the storage size is 36 MB (storage size should be at least 32 MB).
 *     @code {.c}
 *     board # dd if=/dev/zero of=/mass_storage/usb bs=1024 count=36864
 *     board # mkfs.vfat /mass_storage/usb
 *     @endcode
 *   3. Load the USB storage module.
 *     @code {.c}
 *     board # modprobe g_mass_storage file=/mass_storage/usb stall=0 removable=1
 *     @endcode
 *   4. Use the storage partition from the Windows PC or the CV5x platform (one user at a time).
 *     To use the storage from the PC, unmount it on the CV5x platform. To use storage on the CV5x platform,
 *     go to the PC and eject the device.<br>
 *     To use the storage partition on the CV2x platform, use the following code:
 *     @code {.c}
 *     board # mkdir -p /tmp/usbdisk
 *     board # mount -t vfat /mass_storage/usb /tmp/usbdisk
 *     @endcode
 *     To use the storage partition from Windows, connect the CV5x board to the PC via USB.
 *     The Windows PC will recognize the CV5x board as a mass storage device.
 *     @code {.c}
 *     board # umount /tmp/usbdisk
 *     (USB mass storage is located in /dev/mtdblock6).
 *     @endcode
 *
 * @subsection ud_usb_ethernet_device 1.2 USB Device: USB Ethernet Device
 *
 * The CV5x platform USB can serve as a virtual Ethernet device.<br>
 * - USB Ethernet device: USB Ethernet device requirements<br>
 *   The following components are required to test the USB Ethernet device with the Windows operating system (OS) host.
 *   - Windows OS PC<br>
 *     The USB driver (linux.inf)<br>
 *     ambarella/kernel/linux/Documentation/usb/linux.inf<br>
 *     The USB application (PortServer / ps.exe)
 *   - CV5x platform
 *   - Linux USB Ethernet / RNDIS gadget driver (g_ether.ko)
 *     @code {.c}
 *     build $ make menuconfig_public_linux
 *       Device Drivers -->
 *         [*] USB supports -->
 *           <*> USB Gadget Support -->
 *             [*] Ethernet Control Model (CDC ECM)
 *     @endcode
 *   - The USB application (test_bsreader, test_stream)
 *
 * - USB Ethernet device: test USB Ethernet device<br>
 *   Transfer the video streams via USB as an Ethernet device using the following steps:
 *   1. Verify that the USB cable is connected between the windows PC and the CV5x board.
 *   2. Confirm that the USB is functioning in "device" mode and that
 *     the module ambarella_udc is loaded into the system.
 *     @code {.c}
 *     board # usb_role_switch.sh device
 *     ambarella_udc 40960 0
 *     @endcode
 *   3. Log in to the CV5x board and load the module g_ether.
 *     @code {.c}
 *     board # modprobe g_ether
 *     [ 19.140000] g_ether gadget: using random self ethernet address
 *     [ 19.140000] g_ether gadget: using random host ethernet address
 *     [ 19.170000] usb0: MAC 52:d7:87:0c:65:82
 *     [ 19.170000] usb0: HOST MAC de:2b:af:57:03:96
 *     [ 19.210000] g_ether gadget: Ethernet Gadget, version: Memorial Day 2008
 *     [ 19.230000] g_ether gadget: g_ether ready
 *     @endcode
 *   4. The PC will discover the device Linux USB Ethernet / RNDIS Gadget.
 *     Install the driver (ambarella/kernel/linux/Documentation/usb/linux.inf) for the device.
 *     After installation, the PC will add a device to network adapters. Refer to the figure below.
 *     @image html usb_is_recognized_as_a_network_adapter_in_the_pc.png "Figure 1-1. USB is Recognized as a Network Adapter in the PC."
 *   5. Set up the IP address (for example, 10.0.1.1) for the Linux USB ethernet / RNDIS Gadget on the PC.
 *     Refer to the figure below.<br>
 *     @image html usb_ip_address_of_linux_usb_ethernet_rndis_gadget_on_the_pc.png "Figure 1-2. IP Address of Linux USB Ethernet / RNDIS Gadget on the PC."
 *   6. Configure the USB0 IP address (for example, 10.0.1.10) on the CV5x board.
 *     @code {.c}
 *     board # ifconfig usb0 10.0.1.10 netmask 255.255.255.0
 *     borad # ping 10.0.1.1 (test connection between the board and PC)
 *     @endcode
 *   7. Use USB as an Ethernet device. For example, run mediaserver via USB0 Ethernet.
 *     @code {.c}
 *     board # /etc/init.d/S99IPCamControlServer stop
 *     board # /etc/init.d/S98avahi-daemon stop
 *     @endcode
 *     The example above is for the CV5x EVK board
 *     because the Avahi daemon will enable eth0 automatically if it finds eth0 down.
 *     @code {.c}
 *     board # ifconfig eth0 down
 *     board # rtspserver
 *     @endcode
 *     Receive the streams VLC with the USB0 IP (for example, 10.0.1.10).
 *
 * @subsection ud_usb_serial 1.4 USB Device: USB Serial
 *
 * The CV5x USB port can be used as a serial gadget to be a virtual serial port for the PC.<br>
 * - USB serial requirements<br>
 *   The following components are required to test USB serial with a Window OS host.<br>
 *   - Windows OS PC<br>
 *     The USB driver (linux-cdc-acm.inf)<br>
 *     ambarella/kernel/linux/Documentation/usb/linux-cdc-acm.inf
 *
 *   - CV5x platform<br>
 *     Linux USB Ethernet / RNDIS gadget driver (g_serial.ko)
 *     @code {.c}
 *     build $ make menuconfig
 *       Ambarella File System Configuration ->
 *          Serial Port Configuration ->
 *            [*] USB serial tty support
 *
 *     build $ make menuconfig_public_linux
 *       Device Drivers ->
 *         [*] USB support ->
 *           <*> USB Gadget Support ->
 *             [*] Serial support
 *     @endcode
 *
 * - Test the USB serial<br>
 *   1. Confirm that the USB is functioning in "device" mode
 *     and module ambarella_udc is loaded into the system.
 *     @code {.c}
 *     board # usb_role_switch.sh device
 *     ambarella_udc 40960 0
 *     @endcode
 *     If the firmware is built with the configuration shown above,
 *     the USB gadget serial driver will be loaded automatically when the board boots.
 *     Skip this step and proceed to the next step.<br>
 *     If the USB gadget serial driver is not loaded automatically, it must be installed manually.
 *     Users should ensure that they have <B>"g_serial.ko"</B> in
 *     `/lib/modules/5.10.61/kernel/drivers/usb/gadget/legacy`.
 *     @code {.c}
 *     board # modprobe g_serial
 *     [ 85.660148] g_serial gadget: Gadget Serial v2.4
 *     [ 85.664661] g_serial gadget: g_serial ready
 *     @endcode
 *   2. After the gadget driver has been established, users should then see a `/dev/ttyGS0` node:
 *     @code {.c}
 *     board # ls -l /dev/ttyGS0 | cat
 *     crw--w---- 1 root root 250, 0 Jan 1 08:00 /dev/ttyGS0
 *     @endcode
 *   3. Set up an `/etc/inittab` entry to run "getty". The `/dev/ttyGS0` line should be as follows:
 *     @code {.c}
 *     ttyGS0::respawn:/sbin/getty -L ttyGS0 115200 vt100
 *     @endcode
 *   4. Install the Windows host abstract control model (ACM) driver.<br>
 *     To use the Windows ACM driver, users must have the `linux-cdc-acm.inf` file
 *     (`ambarella/kernel/linux/Documentation/usb/`) which supports all recent versions of Windows.<br>
 *     When the gadget serial driver is loaded and the USB device is connected to the Windows host with a USB cable,
 *     Windows will recognize the gadget serial device and ask for a driver.
 *     The driver can be found in the folder that contains the `linux-cdc-acm.inf` file.<br>
 *     <B>Windows XP</B><br>
 *     When the gadget serial device is first plugged in, the <b>Found New Hardware Wizard</b> starts up.
 *     Select <b>Install from a list or specific location (Advanced)</b>. Then, on the next screen,
 *     select <b>Include this location in the search</b>
 *     and enter the path or browse to the folder containing the `linux-cdc-acm.inf` file.
 *     Windows will display a warning that the gadget serial driver has not passed the Windows Logo testing,
 *     but users should select <b>Continue anyway</b> to finish the driver installation.<br>
 *     <B>Windows 7</B><br>
 *     When the gadget serial device is first plugged in,
 *     go to <b>Control Panel > System > Hardware > Device Manager</b> and expand Other Devices.
 *     Right click on <b>Gadget Serial</b> entry and select <b>Update Driver Software</b>.
 *     Click <b>Browse my computer for driver software</b>
 *     and enter the path or browse to the folder containing the `linux-cdc-acm.inf` file.
 *     Select <b>Install the driver anyway</b> and finish the installation.<br>
 *     In <b>Control Panel > System > Hardware > Device Manager</b> expand the Ports (COM and LPT) entry.
 *     Users should see "Gadget Serial" listed as the driver for one of the COM ports
 *     (shown in the figure below).<br>
 *     To uninstall the Windows XP driver for "Gadget Serial",
 *     right click on the <b>Gadget Serial</b> entry in the <b>Device Manager</b> and select <b>Uninstall</b>.
 *     @image html usb_gadget_serial_port.png "Figure 1-3. Gadget Serial Port."
 *   5. Test with PuTTy.<br>
 *     The PuTTy console and PC settings must match the specifications below:
 *     @code {.c}
 *     Serial line: COM10 (Check the port number in "Control Panel > System > Hardware
 *     > Device > Ports (COM & LPT) > ELMO GMAS")
 *     Speed: 115200
 *     Date bits: 8
 *     Stop bits: 1
 *     Parity: None
 *     Flow control: None
 *     @endcode
 *     Verify that <B>AmbaUSB</B> is not in use while using USB as the serial port.
 *     If there is no print on the USB serial console, unplug the USB cable and plug in again.
 *     Before rebooting the board, disconnect the USB serial console.<br>
 *     Users can test the "Gadget Serial" function as follows:<br>
 *     First, in the debug console (always COMM1), type the information below:
 *     @code {.c}
 *     board # echo ambarella cv chip > /dev/ttyGS0
 *     @endcode
 *     @image html usb_gadget_serial_port_output_information.png "Figure 1-4. Gadget Serial Port Output Information."
 *
 * @subsection ud_troubleshooting 1.5 Troubleshooting
 *
 * <B>Question 1:</B> Is it possible for users to burn the code to flash when it is completely empty?<br>
 * <B>Answer:</B> Yes, it is possible to use the USB to perform those operations.
 *
 * <B>Question 2:</B> The CV5x board is not responding, and the AMBoot shell cannot be accessed.
 * How can the binary be burned to the board?<br>
 * <B>Answer:</B> Set the dual in-line package (DIP) switches to USB boot mode and upgrade the firmware directly.
 *
 * <B>Question 3:</B> The system fails when the user tries to download the firmware using the USB.
 * Why does the USB performance appear to be unstable?<br>
 * <B>Answer:</B> Ensure that the USB cable is good quality.
 * Data transfer may be unreliable if the poor-quality USB cables are used.
 * The cable in the photo below is an example of a suitable USB 2.0 cable.
 * @image html usb_2.0_cable.png "Figure 1-5. USB 2.0 Cable."
 *
 * <B>Question 4:</B> Does the Cooper Software Development Kit (SDK) provide a USB driver on the platform?
 * Is the USB device compatible with (insert device name here)?<br>
 * <B>Answer:</B> Yes. The USB driver for Linux can be found in the SDK Linux patch.
 * The USB driver implementation is open to customers and used "AS IS".
 * The data transfer speed and reliability are good.
 * However, the USB driver is not designed as "video class" and the protocol is simple.
 * Developers can choose to use the driver for applications if it is required.
 *
 * <B>Question 5:</B> What does Ambarella recommend for burning firmware to flash in production?<br>
 * <B>Answer:</B> Use a USB. Ambarella suggests reserving four pins on the printed circuit board (PCB) for USB connections.
 * Upgrading firmware using the USB has the following advantages:
 *  - USB can burn codes to an empty NAND flash in production.
 *  - USB can download firmware to the board if the wrong codes have been burnt
 *    or if the system is unable to boot up.
 *
 * <B>Question 6:</B> While using the USB as an Ethernet device,
 * the connection between the PC and the board is running normally. The ping is being received from each side.
 * However, the rtsp_server shows the message "rtsp://0.0.0.0/stream1" which does not match the IP of USB0.
 * Why are the streams not being viewed using this address?<br>
 * <B>Answer:</B> This is because the rtsp_server requires the default route to stream the video.
 * Check the default route.
 * @code {.c}
 * board # route
 * Kernel IP routing table
 * Destination Gateway    Genmask       Flags Metric Ref Use Iface
 * 10.0.1.0    *          255.255.255.0 U     0      0   0 usb0
 * 127.0.0.0   *          255.0.0.0     U     0      0   0 lo
 * default     10.0.1.1   0.0.0.0       UG    0      0   0 usb0
 * @endcode
 *
 * - - - -
 *
 * @section usb_host 2. USB Host
 *
 * The usage of the CV5x USB host mode is shown below.
 *  1. Set the USB to function in "host" mode.
 *    @code {.c}
 *    board # usb_role_switch.sh host
 *    Current usb role is device
 *    Try to set usb to host
 *    [  220.925708] usbcore: deregistering device driver usb
 *    [  220.930835] usbcore: deregistering interface driver usbfs
 *    [  220.936401] usbcore: deregistering interface driver hub
 *    [  220.975505] usbcore: registered new interface driver usbfs
 *    [  220.981045] usbcore: registered new interface driver hub
 *    [  220.986482] usbcore: registered new device driver usb
 *    [  221.014036] xhci-hcd xhci-hcd.1.auto: xHCI Host Controller
 *    [  221.019566] xhci-hcd xhci-hcd.1.auto: new USB bus registered, assigned bus number 1
 *    [  221.027628] xhci-hcd xhci-hcd.1.auto: hcc params 0x08007f0d hci version 0x110 quirks 0x0000002000018010
 *    [  221.037081] xhci-hcd xhci-hcd.1.auto: irq 97, io mem 0x2020008000
 *    [  221.043457] usb usb1: New USB device found, idVendor=1d6b, idProduct=0002, bcdDevice= 5.15
 *    [  221.051760] usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
 *    [  221.059006] usb usb1: Product: xHCI Host Controller
 *    [  221.063896] usb usb1: Manufacturer: Linux 5.15.55 xhci-hcd
 *    [  221.069396] usb usb1: SerialNumber: xhci-hcd.1.auto
 *    [  221.074448] hub 1-0:1.0: USB hub found
 *    [  221.078222] hub 1-0:1.0: 1 port detected
 *    [  221.082243] xhci-hcd xhci-hcd.1.auto: xHCI Host Controller
 *    [  221.087749] xhci-hcd xhci-hcd.1.auto: new USB bus registered, assigned bus number 2
 *    [  221.095435] xhci-hcd xhci-hcd.1.auto: Host supports USB 3.1 Enhanced SuperSpeed
 *    [  221.102797] usb usb2: We don't know the algorithms for LPM for this host, disabling LPM.
 *    [  221.110942] usb usb2: New USB device found, idVendor=1d6b, idProduct=0003, bcdDevice= 5.15
 *    [  221.119235] usb usb2: New USB device strings: Mfr=3, Product=2, SerialNumber=1
 *    [  221.126480] usb usb2: Product: xHCI Host Controller
 *    [  221.131370] usb usb2: Manufacturer: Linux 5.15.55 xhci-hcd
 *    [  221.136870] usb usb2: SerialNumber: xhci-hcd.1.auto
 *    [  221.141866] hub 2-0:1.0: USB hub found
 *    [  221.145633] hub 2-0:1.0: 1 port detected
 *    [  221.319641] usb 1-1: new high-speed USB device number 2 using xhci-hcd
 *    [  221.452158] usb 1-1: New USB device found, idVendor=0424, idProduct=2814, bcdDevice= 6.25
 *    [  221.460365] usb 1-1: New USB device strings: Mfr=1, Product=2, SerialNumber=0
 *    [  221.467523] usb 1-1: Product: USB2814 Smart Hub
 *    [  221.472065] usb 1-1: Manufacturer: Microchip
 *    [  221.476670] hub 1-1:1.0: USB hub found
 *    [  221.480618] hub 1-1:1.0: 7 ports detected
 *    [  221.769641] usb 1-1.7: new high-speed USB device number 3 using xhci-hcd
 *    [  221.864399] usb 1-1.7: New USB device found, idVendor=0424, idProduct=2840, bcdDevice= 2.04
 *    [  221.872781] usb 1-1.7: New USB device strings: Mfr=1, Product=2, SerialNumber=0
 *    [  221.880113] usb 1-1.7: Product: Hub Feature Controller
 *    [  221.885265] usb 1-1.7: Manufacturer: Microchip
 *    @endcode
 *  2. Confirm that the USB is functioning in "host" mode.
 *    @code {.c}
 *    board # cat /sys/class/usb_role/2020008000.cdns3-role-switch/role
 *    host
 *    @endcode
 *
 * @subsection uh_support_usb_mass_storage_device 2.1 USB Host: Support USB Mass Storage Device
 *
 * - Support USB storage device: requirement<br>
 *   CV5x platform
 *   @code {.c}
 *   build $ make menuconfig_public_linux
 *     Device Drivers ->
 *       [*] USB support ->
 *         <M> Support for Host-side USB
 *         <M> USB Mass Storage support
 *
 *   File systems ->
 *     DOS/FAT/NT Filesystems ->
 *       <*> VFAT (Windows-95) fs support
 *       <*> NTFS file system support
 *       [*] NTFS write support
 *   @endcode
 *
 * - Support USB storage device: test steps<br>
 *   1. Confirm that the USB is working in the "host" mode.
 *     @code {.c}
 *     board # usb_role_switch.sh host
 *     @endcode
 *   2. Plug in the USB storage device. The kernel will add "sd_mod",
 *     "scsi_mod", and "usb_storage" modules automatically. Afterwards, it will detect the USB storage.
 *     @code {.c}
 *     [  169.086517] usb 1-1.2: new high-speed USB device number 4 using xhci-hcd
 *     [  169.183451] usb 1-1.2: New USB device found, idVendor=05e3, idProduct=0747, bcdDevice= 8.19
 *     [  169.191831] usb 1-1.2: New USB device strings: Mfr=3, Product=4, SerialNumber=5
 *     [  169.199163] usb 1-1.2: Product: USB Storage
 *     [  169.203356] usb 1-1.2: Manufacturer: Generic
 *     [  169.207636] usb 1-1.2: SerialNumber: 000000000819
 *     [  169.227520] SCSI subsystem initialized
 *     [  169.236982] usb-storage 1-1.2:1.0: USB Mass Storage device detected
 *     [  169.243862] scsi host0: usb-storage 1-1.2:1.0
 *     [  169.248638] usbcore: registered new interface driver usb-storage
 *     [  170.278124] scsi 0:0:0:0: Direct-Access     Generic  STORAGE DEVICE   0819 PQ: 0 ANSI: 6
 *     [  170.697718] sd 0:0:0:0: [sda] 62333952 512-byte logical blocks: (31.9 GB/29.7 GiB)
 *     [  170.705937] sd 0:0:0:0: [sda] Write Protect is off
 *     [  170.711167] sd 0:0:0:0: [sda] Write cache: disabled, read cache: enabled, doesn't support DPO or FUA
 *     [  170.729780]  sda: sda1
 *     [  170.733539] sd 0:0:0:0: [sda] Attached SCSI removable disk
 *     @endcode
 *   3. Find the device name of the USB storage device.
 *     @code {.c}
 *     board # fdisk -l
 *     Disk /dev/sda: 8011 MB, 8011120640 bytes
 *     255 heads, 63 sectors/track, 973 cylinders, total 15646720 sectors
 *     Units = sectors of 1 * 512 = 512 bytes
 *     Sector size (logical/physical): 512 bytes / 512 bytes
 *     I/O size (minimum/optimal): 512 bytes / 512 bytes
 *     Disk identifier: 0xcad4ebea
 *
 *     Device Boot Start End Blocks Id System
 *     /dev/sda4 * 63 15646656 7823297 b W95 FAT32
 *     @endcode
 *   4. Mount the USB storage device.
 *     @code {.c}
 *     board # mkdir -p /tmp/usbstorage
 *     board # mount -t /dev/sda1 /tmp/usbstorage
 *     @endcode
 *
 * @subsection uh_mouse_keyboard 2.2 USB Host: Mouse / Keyboard
 *
 * - Support for USB mouse / keyboard device: requirements<br>
 *   CV5x platform
 *   @code {.c}
 *   build $ make menuconfig_public_linux
 *     Device Drivers -->
 *       HID support -->
 *      {M} HID bus support
 *      <M> Generic HID driver
 *   	        USB HID support --->
 *                     <M> USB HID transport layer
 *   @endcode
 *
 * - Support USB mouse / keyboard device: sample<br>
 *   1. Confirm that the USB is functioning in "host" mode (possible parameter: <B>host device</B>).
 *     @code {.c}
 *     board # usb_role_switch.sh host
 *     @endcode
 *   2. Plug in the USB mouse device. The kernel will recognize the device as follows:
 *     @code {.c}
 *     [  386.942517] usb 1-1.2: new low-speed USB device number 5 using xhci-hcd
 *     [  387.041511] usb 1-1.2: New USB device found, idVendor=0461, idProduct=4d51, bcdDevice= 7.17
 *     [  387.049894] usb 1-1.2: New USB device strings: Mfr=0, Product=2, SerialNumber=0
 *     [  387.057317] usb 1-1.2: Product: DELL Laser Mouse
 *     [  387.078319] usbcore: registered new interface driver usbhid
 *     [  387.083928] usbhid: USB HID core driver
 *     [  387.089981] input: DELL Laser Mouse as /devices/platform/2020000000.cdns3/2020008000.cdns3/xhci-hcd.1.auto/usb1/1-1/1-1.2/1-1.2:1.0/0003:0461:4D51.0001/input/input0
 *     [  387.104852] hid-generic 0003:0461:4D51.0001: input: USB HID v1.11 Mouse [DELL Laser Mouse] on usb-xhci-hcd.1.auto-1.2/input0
 *     @endcode
 *   3. Confirm the event interface of the USB mouse.
 *     @code {.c}
 *     board # cat /proc/bus/input/devices
 *     I: Bus=0003 Vendor=0461 Product=4d51 Version=0111
 *     N: Name="DELL Laser Mouse"
 *     P: Phys=usb-xhci-hcd.1.auto-1.2/input0
 *     S: Sysfs=/devices/platform/2020000000.cdns3/2020008000.cdns3/xhci-hcd.1.auto/usb1/1-1/1-1.2/1-1.2:1.0/0003:0461:4D51.0001/input/input0
 *     U: Uniq=
 *     H: Handlers=mouse0 event0
 *     B: PROP=0
 *     B: EV=17
 *     B: KEY=1f0000 0 0 0 0
 *     B: REL=903
 *     B: MSC=10
 *     @endcode
 *   4. Get the mouse event.
 *     @code {.c}
 *     board # cat /dev/input/event0
 *     @endcode
 *     Or,
 *     @code {.c}
 *     board # cat /dev/input/mouse0
 *     @endcode
 *   5. Plug in the USB keyboard device.
 *     The kernel will recognize the device and send the message as shown below:
 *     @code {.c}
 *     [  639.614517] usb 1-1.2: new full-speed USB device number 6 using xhci-hcd
 *     [  639.709699] usb 1-1.2: New USB device found, idVendor=0483, idProduct=4025, bcdDevice= 0.00
 *     [  639.718082] usb 1-1.2: New USB device strings: Mfr=1, Product=2, SerialNumber=3
 *     [  639.725499] usb 1-1.2: Product: 69M-RGB
 *     [  639.729354] usb 1-1.2: Manufacturer: CATEX TECH.
 *     [  639.733987] usb 1-1.2: SerialNumber: CA2017091
 *     [  639.740994] input: CATEX TECH. 69M-RGB as /devices/platform/2020000000.cdns3/2020008000.cdns3/xhci-hcd.1.auto/usb1/1-1/1-1.2/1-1.2:1.0/0003:0483:4025.0002/input/input1
 *     [  639.807640] hid-generic 0003:0483:4025.0002: input: USB HID v1.10 Keyboard [CATEX TECH. 69M-RGB] on usb-xhci-hcd.1.auto-1.2/input0
 *     [  639.820653] hid-generic 0003:0483:4025.0003: device has no listeners, quitting
 *     [  639.829588] input: CATEX TECH. 69M-RGB Consumer Control as /devices/platform/2020000000.cdns3/2020008000.cdns3/xhci-hcd.1.auto/usb1/1-1/1-1.2/1-1.2:1.2/0003:0483:4025.0004/input/input2
 *     [  639.897730] input: CATEX TECH. 69M-RGB System Control as /devices/platform/2020000000.cdns3/2020008000.cdns3/xhci-hcd.1.auto/usb1/1-1/1-1.2/1-1.2:1.2/0003:0483:4025.0004/input/input3
 *     [  639.914229] input: CATEX TECH. 69M-RGB Keyboard as /devices/platform/2020000000.cdns3/2020008000.cdns3/xhci-hcd.1.auto/usb1/1-1/1-1.2/1-1.2:1.2/0003:0483:4025.0004/input/input4
 *     [  639.930201] input: CATEX TECH. 69M-RGB Mouse as /devices/platform/2020000000.cdns3/2020008000.cdns3/xhci-hcd.1.auto/usb1/1-1/1-1.2/1-1.2:1.2/0003:0483:4025.0004/input/input5
 *     [  639.945887] hid-generic 0003:0483:4025.0004: input: USB HID v1.10 Keyboard [CATEX TECH. 69M-RGB] on usb-xhci-hcd.1.auto-1.2/input2
 *     @endcode
 *
 * @subsection uh_support_usb_serial_device 2.3 USB Host: Support USB Serial Device
 *
 * - Support USB serial device: requirements<br>
 *   CV5x platform<br>
 *   The system and binary build:
 *   @code {.c}
 *   build $ make menuconfig_public_linux
 *     Device Drivers  --->
 *      [*] USB support  --->
 *         <M>   Support for Host-side USB
 *         <M>   xHCI HCD (USB 3.0) support
 *         [*]     xHCI support for debug capability
 *         -M-     Generic xHCI driver for a platform device
 *         <M>   USB Serial Converter support  --->
 *         [*]   USB Generic Serial Driver
 *   @endcode
 *
 * - Support USB serial device: test steps<br>
 *   1. Confirm that the USB is functioning in "host" mode (possible parameter: <B>host device</B>).
 *     @code {.c}
 *     board # usb_role_switch.sh host
 *     @endcode
 *   2. Plug in the USB serial device. The kernel will add "usbserial" modules automatically
 *     and detect the USB serial device.
 *     @code {.c}
 *     board # [ 1165.438518] usb 1-1.2: new full-speed USB device number 7 using xhci-hcd
 *     [ 1165.533156] usb 1-1.2: New USB device found, idVendor=067b, idProduct=2303, bcdDevice= 4.00
 *     [ 1165.541538] usb 1-1.2: New USB device strings: Mfr=1, Product=2, SerialNumber=0
 *     [ 1165.548871] usb 1-1.2: Product: USB-Serial Controller D
 *     [ 1165.554111] usb 1-1.2: Manufacturer: Prolific Technology Inc.
 *     ...  ...  ...
 *     @endcode
 *   3. Check the USB serial device.
 *     @code {.c}
 *     board # lsusb
 *      Bus 001 Device 002: ID 067b:2303
 *      Bus 001 Device 001: ID 1d6b:0001
 *      Bus 002 Device 001: ID 1d6b:0002
 *     board # cat /dev/ttyUSB0
 *     @endcode
 *
 * @subsection uh_support_usb_eye_diagram_testing 2.4 USB Host: HS Electrical Test (Eye Diagram)
 *
 * - Why do users require the eye diagram test?
 *   The USB eye diagram is the result of accumulating and displaying bits of the serial signal
 *   collected by the afterglow method. The shape of the superimposed image resembles an
 *   eye, so it is called the eye diagram test. According to the information of the eye diagram,
 *   the inter-symbol crosstalk and noise can be observed, reflecting the overall
 *   characteristics of the digital signal, so as to estimate the advantages and
 *   disadvantages of the system. Therefore, the eye diagram test is the core of signal integrity
 *   analysis of high-speed interconnection systems.
 *
 * - How do users test the eye diagram in the Ambarella evaluation kit (EVK)?
 *   1. List of testing equipment
 *      - Select any two EVK test boards with USB devices (one for USB host and one for USB device)
 *      - USB OTG cable
 *      - Micro USB cable
 *      - E2666B USB 2.0 hi-speed device test fixture kit (Agilent / Keysight test fixture)
 *      - Compatible oscilloscopes
 *
 *   2. Configure the USB device EVK firmware. Then, burn them to the host EVK to be tested.
 *      @code {.c}
 *      build $ make defconfig_public_linux
 *      build $ make menuconfig_public_linux
 *             Device Drivers --->
 *                 [*] USB support --->
 *                     USB EHSET Test Fixture driver
 *      @endcode
 *
 *   3. Set up the environemnt.
 *   @image html usb_eye_environment.png "Figure 2-1. Ambarella USB Eye Diagram Environment Setting."
 *
 *   4. Follow the steps below for the test procedure.
 *
 *      1. Host: as the USB host, connect the micro-USB port to the test jig.
 *          @code {.c}
 *          board # echo host > /proc/ambarella/usbphy0
 *          board # modprobe usbcore
 *          board # modprobe ehci-hcd
 *          board # modprobe ehci_ambarella
 *          board # modprobe ehset
 *          @endcode
 *      2. Device: as USB device, connect the micro-USB port plug to the same test fixture (as a USB device-like dongle)
 *          @code {.c}
 *          board # echo device > /proc/ambarella/usbphy0
 *          board # dd if=/dev/zero of=/tmp/fsg bs=1M count=10
 *          board # modprobe g_mass_storage file=/tmp/fsg stall=0 removable=1 idVendor=0x1a0a idProduct=0x0104
 *          @endcode
 *      @note
 *          - Ensure that the EVK_host (as USB host) starts to output the USB test pattern.
 *             Check point: The host has identified the device.
 *          @image html usb_eye_host_result.png "Figure 2-2 Ambarella USB Eye Diagram Test Result."
 *          - Switch the jig to test mode on the kit board.
 *          - After the negotiation between the host / device is complete and the test
 *             mode is sent, the user can unplug the EVK_host (as a USB device).
 *          - The system must be rebooted and commands must be repeated if the user wants to start a new test product identifier (PID).
 *          - This test is only for the direct USB port on the Ambarella chip, not the USB
 *             HUB ports. For HUB ports test, ask the USB HUB vendor for help.
 *          - Do not connect other USB devices during the eye diagram test to avoid interference.
 *
 *   5. Conclusion
 *   @image html usb_eye_diagram.png "Figure 2-3. Ambarella USB Eye Diagram."
 *
 * @subsection uh_support_usb_uvc_camera_device 2.5 USB Host: Support USB UVC Camera Device
 * - Support USB UVC camera device: requirements<br>
 *   For the CV5 platform:<br>
 *   @code {.c}
 *   build $ make menuconfig_public_linux
 *      Device Drivers --->
 *       [*] USB support --->
 *              <M> Support for Host-side USB
 *              <M> OHCI HCD support
 *                [*] Ambarella OHCI support
 *       <M> Multimedia support --->
 *          Media device types  --->
 *              [*] Cameras and video grabbers
 *          Media drivers  --->
 *              [*] Media USB Adapters --->
 *                      <M> USB Video Class (UVC)
 *                        [*] UVC input events device support
 *   @endcode
 *
 * - Support USB UVC device: test steps<br>
 *   1. Ensure that USB (3.0) is functioning in "host" mode (possible parameter: <B>host device</B>).
 *     @code {.c}
 *     board # usb_role_switch.sh host
 *     @endcode
 *     @code {.c}
 *     [   31.021908] usbcore: deregistering device driver usb
 *     [   31.027183] usbcore: deregistering interface driver usbfs
 *     [   31.032945] usbcore: deregistering interface driver hub
 *     [   31.073446] usbcore: registered new interface driver usbfs
 *     [   31.079324] usbcore: registered new interface driver hub
 *     [   31.084686] usbcore: registered new device driver usb
 *     # [   31.109275] xhci-hcd xhci-hcd.1.auto: xHCI Host Controller
 *     [   31.114803] xhci-hcd xhci-hcd.1.auto: new USB bus registered, assigned bus number 1
 *     [   31.122870] xhci-hcd xhci-hcd.1.auto: hcc params 0x08007f0d hci version 0x110 quirks 0x0000002000018010
 *     [   31.132335] xhci-hcd xhci-hcd.1.auto: irq 94, io mem 0x2020008000
 *     [   31.138743] xhci-hcd xhci-hcd.1.auto: xHCI Host Controller
 *     [   31.144277] xhci-hcd xhci-hcd.1.auto: new USB bus registered, assigned bus number 2
 *     [   31.151965] xhci-hcd xhci-hcd.1.auto: Host supports USB 3.1 Enhanced SuperSpeed
 *     [   31.159338] usb usb1: New USB device found, idVendor=1d6b, idProduct=0002, bcdDevice= 5.15
 *     [   31.167633] usb usb1: New USB device strings: Mfr=3, Product=2, SerialNumber=1
 *     [   31.174894] usb usb1: Product: xHCI Host Controller
 *     [   31.179785] usb usb1: Manufacturer: Linux 5.15.93 xhci-hcd
 *     [   31.185285] usb usb1: SerialNumber: xhci-hcd.1.auto
 *     [   31.190634] hub 1-0:1.0: USB hub found
 *     [   31.194413] hub 1-0:1.0: 1 port detected
 *     [   31.198705] usb usb2: We don't know the algorithms for LPM for this host, disabling LPM.
 *     [   31.206857] usb usb2: New USB device found, idVendor=1d6b, idProduct=0003, bcdDevice= 5.15
 *     [   31.215154] usb usb2: New USB device strings: Mfr=3, Product=2, SerialNumber=1
 *     [   31.222429] usb usb2: Product: xHCI Host Controller
 *     [   31.227321] usb usb2: Manufacturer: Linux 5.15.93 xhci-hcd
 *     [   31.232843] usb usb2: SerialNumber: xhci-hcd.1.auto
 *     [   31.238123] hub 2-0:1.0: USB hub found
 *     [   31.241917] hub 2-0:1.0: 1 port detected
 *     @endcode
 *   2. Use modprobe uvcvideo.
 *     @code {.c}
 *     board # modprobe uvcvideo
 *     @endcode
 *   3. Plug in the USB UVC device. The kernel identifies the USB UVC camera
 *     and registers the V4L2 video device automatically.
 *     @code {.c}
 *     # [  115.568858] usb 2-1: new SuperSpeed Plus Gen 2x1 USB device number 2 using xhci-hcd
 *     [  115.588258] usb 2-1: New USB device found, idVendor=1d6b, idProduct=0104, bcdDevice= 5.15
 *     [  115.596466] usb 2-1: New USB device strings: Mfr=1, Product=2, SerialNumber=3
 *     [  115.603624] usb 2-1: Product: USB V/A Streaming
 *     [  115.608170] usb 2-1: Manufacturer: Ambarella
 *     [  115.612452] usb 2-1: SerialNumber: 123456789AB
 *     [  115.640430] mc: Linux media interface: v0.10
 *     [  115.657828] videodev: Linux video capture interface: v2.00
 *     [  115.677051] uvcvideo 2-1:1.1: Unknown video format 59455247-0000-0010-8000-00aa00389b71
 *     [  115.685098] usb 2-1: Found UVC 1.00 device USB V/A Streaming (1d6b:0104)
 *     [  115.704845] usbcore: registered new interface driver uvcvideo
 *     @endcode
 *   4. Check the USB UVC device.
 *     @code {.c}
 *     board # lsusb
 *     Bus 002 Device 002: ID 1d6b:0104
 *     Bus 001 Device 001: ID 1d6b:0002
 *     Bus 002 Device 001: ID 1d6b:0003
 *     board # ls /dev/video*
 *     /dev/video0
 *     @endcode
 *   5. Capture a YUV picture based on V4L2.
 *
 *     The v4l-utils are a series of packages for managing media devices that aid in obtaining YUV frames from a UVC camera.\n
 *     First, use the v4l2-ctl command to set camera parameters, such as frame size and frame rate. For example,
 *     the command below will set up a camera with a resolution of 1920x1080 and a frame rate of 30 frames per second (fps).
 *     @code {.c}
 *     board # v4l2-ctl --device=/dev/video0 --set-fmt-video=width=1920, height=1080, pixelformat=YUYV --set-parm=30
 *     @endcode
 *     Then, use the v4l2-ctl command to enable streaming and output a frame to a file. For example,
 *     the following command will capture a YUV image and save it to a file named yuv_image.yuv.
 *     @code {.c}
 *     board # v4l2-ctl --stream-mmap --stream-count=1 --stream-to=yuv_image.yuv --device=/dev/video0
 *     @endcode
 *
 * - - - -
 *
 * @section usb_speed 3. USB Speed
 *
 * The table below is the test result of USB 3.2 speed of mass storage:
 * <table>
 * <tr>
 * <th><div style="width:120px">USB Mode</div></th><th><div style="width:120px"></div>Read / Write</th>
 * <th><div style="width:120px">Speed</div></th>
 * </tr>
 * <tr><td rowspan="3">USB Host
 * <tr>		        	<td>Read</td><td>696.4 MB/s</td></tr>
 * <tr>				<td>Write</td><td>544.1 MB/s</td></tr>
 * </td></tr>
 * <tr><td rowspan="3">USB Device
 * <tr>		        	<td>Read</td><td>560 MB/s</td></tr>
 * <tr>				<td>Write</td><td>560 MB/s</td></tr>
 * </td></tr>
 * </table>
 * <br>
 *
 * @note
 * The USB port on PC greatly affects the read and write speed of the USB device.
 *
 * For example, with the same device, the read / write speed of the USB 3.0 port
 * maybe 150 MB/s ~ 200 MB/s slower than that of the USB 3.1 port on host PC.<br>
 * @image html usb_speed_device_usb3.1_port.png "Figure 3-1. Ambarella USB Speed with USB 3.1 Port."
 * @image html usb_speed_device_usb3.0_port.png "Figure 3-2. Ambarella USB Speed with USB 3.0 Port."
 *
 * The reference test steps are as follows:<br>
 * 1. Assemble the jumper on J28.<br>
 * 2. Input the following test commands:<br>
 *    @code {.c}
 *    board # rmmod Ambarella_udc
 *    board # dd if=/dev/zero of=/tmp/fsg bs=1M count=500
 *    board # mkfs.vfat /tmp/fsg
 *    board # modprobe g_mass_storage file=/tmp/fsg stall=0 removable=1
 *    @endcode
 *
 * - - - -
 *
 * @section amba_uvc_camera 4. Ambarella UVC Camera
 *
 * The Ambarella UVC camera is a camera with a USB interface
 * that meets the standards set for the USB video class (UVC).
 *
 * @subsection uvc_cam_specifications 4.1 Specifications
 *
 * <table>
 * <caption id="uvac_spec_table"></caption>
 * <tr><th> Parameters          <th align="left"> Specification
 * <tr>
 * <td> UVC features
 * <td>
 * - UVC 1.0 / UVC 1.1 / UVC 1.5<br>
 * - Bulk and isochronous (ISOC) mode (Ambarella suggests using bulk mode for higher throughput) <br>
 * - Multiple endpoints (EPs) with multiple streams<br>
 *   - Up to 2 UVCs for USB 2.0<br>
 *   - Up to 7 UVCs for USB 3.2-Gen2<br>
 * - Streams with different resolution in the same format<br>
 * - Camera terminal (CT) control<br>
 * - Processing unit (PU) control<br>
 * - USB 3.2-Gen2 transmission<br>
 * - Bit rate up to 2 Gbps
 * <tr>
 * <td> UVC stream
 * <td>
 * - Up to H.265 8K @ 30 fps (Default 1080p@30fps)<br>
 * - Up to H.264 8K @ 30 fps (Default 1080p@30fps)<br>
 * - Up to MJPEG 8K @ 30 fps (Default 1080p@30fps)<br>
 * - Up to NV12 4K @ 30 fps (Default 720p@30fps)<br>
 * - Up to YUYV 1080p @ 30 fps (Default 480p@30fps)<br>
 * - JPEG, NV12 and YUYV image
 * <tr>
 * <td> UAC features
 * <td>
 * - UAC 1.0 (microphone)<br>
 * - UAC 2.0 (microphone)<br>
 * - 48 Kbps sample rate and stereo microphone input<br>
 * - Volume and mute control
 * <tr>
 * <td> Compatibility
 * <td>
 * - Microsoft Windows (7 and above)<br>
 * - Linux (Ubuntu 16.04 and above)
 * </table>
 *
 * @note
 * - USB3 has <B>15</B> physical EPs in total: 1x EP0, 7x IN EPs, and 7x OUT EPs. Only 7x IN EPs can be
 *   used for UVC / USB audio class (UAC) purposes. Each UVC uses either 1 or 2 IN EPs. Each UAC uses 1 IN EP.
 *     - If only UVC, up to 7x UVCs can be supported in parallel if using single IN EP.
 *     - If UVC + UAC, up to 6x UVC + 1x UAC can be supported in parallel if using single IN EP for UVC.
 *     - For UAC, if enabling audio volume control, one additional IN EP will be occupied. Therefore,
 *        5x UVC + 1x (UAC + UAC volume control) can be supported with a total of IN EPs = 7 if using a single IN EP for UVC.
 * - The maximum UVC throughput is about 4.278 Gbps (NV12 4K @ 43fps: `3840 * 2160 * 12 * 43 / 1000000000`) without loading.
 *
 * @subsection uvc_cam_build_firmware 4.2 Build Firmware Support UVC
 *
 * @par For Old SDK Amba Build:
 * @code {.c}
 * build $ source ../../build/env/cortex-a76-linux5.15-gcc.env
 * build $ make sync_build_mkcfg
 * build $ make cv5_ipcam_config
 * build $ make menuconfig
 * 	[*] Ambarella Linux Configuration  --->
 * 		[*]   Apply Linux Patch  --->
 * 			[*]   Apply Ambarella UVAC Patch
 * 		[*]   Ambarella Private Drivers Configuration  ---> // If running 8K@30
 * 			[*]   Build Ambarella private IAV module  --->
 * 				(7680)   Max VIN width in pixel
 * 				(4320)   Max VIN height
 * 	[*] Ambarella Unit Test Configuration  --->
 * 		[*]   Ambarella Private Linux Unit test configs  --->
 * 			[*]   Build uvc stream tool
 * @endcode
 *
 * @par For Cooper SDK Amba Build:
 * @code {.c}
 * build $ source build/env/amba-build.env
 * build $ make ipcam_config
 * build $ make menuconfig
 *   kernel --->
 *     linux-patch-uvac-choice@virtual (kernel/linux-patch) (linux-patch-uvac) --->
 *   drv_modules --->
 *     private --->
 *       -*- ambavideo-header (drv_modules/private/dsp_v5) ---> // If running 8K@30
 *        (7680) Max VIN width in pixel
 *        (4320) Max VIN height
 *   packages --->
 *     usb_gadget --->
 *       [*] usb-gadget-configfs (packages/usb_gadget/configfs)
 *       [*] libuvc (packages/usb_gadget/libuvc)
 *         [*] uvc-stream (packages/usb_gadget/unit_test/dsp_v5)
 * @endcode
 *
 * @par For Cooper SDK Yocto Build:
 * @code {.c}
 * build $ source build/env/yocto-build.env
 * build $ make ipcam_config
 * build $ make menuconfig
 *   meta-ambabsp --->
 *     recipes-kernel --->
 *       linux-patch-uvac-choice@virtual (meta-ambabsp/recipes-kernel/linux-patch) (linux-patch-uvac) --->
 *     recipes-video --->
 *       -*- ambavideo-header (meta-ambabsp/recipes-video/ambvideo-header) ---> // If running 8K@30
 *         (7680) Max VIN width in pixel
 *         (4320) Max VIN height
 *   meta-ambalib --->
 *     recipes-video --->
 *       [*] libuvc (meta-ambalib/recipes-video/libuvc)
 *   meta-ambaapp --->
 *     recipes-usb-gadget --->
 *       [*] usb-gadget-configfs (meta-ambaapp/recipes-usb-gadget/usb-gadget-configfs)
 *       [*] uvc-stream (meta-ambaapp/recipes-usb-gadget/uvc-stream)
 * @endcode
 *
 * @par For Linux kernel 5.15:
 * @code {.c}
 * build $ make defconfig_public_linux  // Cooper SDK doesn't need do it
 * build $ make menuconfig_public_linux // Cooper SDK is "make linux_menuconfig"
 * 	Device Drivers  --->
 * 		<M> Multimedia support  --->
 * 			Media device types  --->
 * 				[*] Cameras and video grabbers
 * 		[*] USB support  --->
 * 			<M>   Cadence USB3 support on Ambarella platforms
 * 				[*]     Cadence CDNSP device controller  // USB 3.2-Gen2 UDC
 * 				[*]     Cadence CDNSP host controller
 * 			<*>   USB Gadget Support  --->
 * 				<M>   USB Gadget functions configurable through configfs
 * 				[*]     Audio Class 1.0  // UAC 1.0
 * 				[*]     Audio Class 2.0  // UAC 2.0
 * 				[*]     USB Webcam function
 * @endcode
 *
 * - If users do not want to change "Max VIN" using "make menuconfig",
 *   they can also add <B>"options ambcma max_vin_width=7680 max_vin_height=4320"</B> in
 *   "/etc/modprobe.d/ambarella.conf", and then restart the board.
 *
 * @subsection uvc_cam_stream_ambarella_uvc 4.3 Stream Ambarella UVC
 *
 * The following is the recommended topology between canvases and encode streams in the image audio video (IAV) layer,
 * which is required to match the UVC stream application.
 * Users can refer to the `Lua script v6_generic_1080px2.lua` and the UVC stream configuration file `uvc.conf`.
 * @image html usb_cv5x_uvc_pipeline.png "Figure 4-1. Ambarella UVC Pipeline."
 * UVC stream application is a unit test which is responsible for fetching the video frame from the IAV layer,
 * and then feeding it to Linux V4L2. The source is located under
 * `ambarella/unit_test/private/uvc_stream`.
 * Before streaming the UVC, set up IAV canvas and encoding (1080p).
 * @code {.c}
 * board # init.sh --na; modprobe imx274_mipi vinc_id=8 bus_id=3 lane=2
 * board # test_aaa_service -a &
 * // For Old SDK:
 * board # test_encode --resource-cfg /vendor/config/v6_generic_1080px2.lua --vout-cfg /vendor/config/vout_hdmi_480p.lua
 * // For Cooper SDK:
 * board # test_encode --resource-cfg /usr/share/uvc-stream/uvc_1080p.lua --vout-cfg /usr/share/uvc-stream/vout_hdmi_480p.lua
 * board # test_encode -A -m 1080p -b 1 -B -h 1080p -b 2 -C -H 1080p -b 0
 * board # test_encode -A -e -B -e -C -e
 * @endcode
 * Before streaming the UVC, set up IAV canvas and encoding (High-efficiency video coding (HEVC) 8K).
 * @code {.c}
 * board # init.sh --na; modprobe imx586_mipi vinc_id=8 bus_id=3
 * board # test_aaa_service -a &
 * // For Old SDK:
 * board # test_encode --resource-cfg /vendor/config/v6_generic_8k.lua
 * // For Cooper SDK:
 * board # test_encode --resource-cfg /usr/share/uvc-stream/uvc_8kp.lua
 * board # test_encode -A -m 1080p -b 1 -B -h 1080p -b 2 -C -H 7680x4320 -b 0
 * board # test_encode -A -e -B -e -C -e
 * board # start-uvac-configfs -a -b
 * @endcode
 * @note
 * - Ambarella recommends using a sensor with direct 8K resolution.
 * - Configure the `/vendor/config/uvc.conf` according to the actual stream.
 *   @code {.c}
 *   stream: m 1920 1080 333333 8 0
 *   stream: h 1920 1080 333333 8 1
 *   stream: H 7680 4320 333333 8 2
 *   stream: u 1920 1080 333333 12 3
 *   @endcode
 *
 * Start streaming UVC 1.0 and UAC 1.0.
 *   @code {.c}
 *   build $ start-uvac-configfs -a -b
 *   @endcode
 * Or, start streaming UVC 1.1 and UAC 1.0.
 *   @code {.c}
 *   build $ start-uvac-configfs -a -b -u 0x0110
 *   @endcode
 * Or, start streaming UVC 1.5 and UAC 1.0.
 *   @code {.c}
 *   build $ start-uvac-configfs -a -b -u 0x0150
 *   @endcode
 * Or, start streaming UVC 1.0 and UAC 2.0.
 *   @code {.c}
 *   build $ start-uvac-configfs -a -b -s
 *   @endcode
 * Or, start streaming the multiple-UVCs and UAC 1.0 by USB 2.0.
 *   @code {.c}
 *   build $ start-uvac-configfs -a -b -X -Y       // two UVCs
 *   @endcode
 *   Note: USB 2.0 UDC only has six physical endpoints (1 EP0 + 5 IN EPs).
 *   USB 3.2-Gen2 UDC only has 15 physical endpoints (1 EP0 + 7 IN EPs + 7 OUT EPs).
 *   Each UVC will use two IN EPs, and each UAC will use 2 IN EPs with volume control enabled.
 *   If users enable the volume control while using two UVCs in USB 2.0 or three UVCs in
 *   USB 3.2-Gen2, the number of used IN EPs will exceed the number of physical IN EPs
 *   and the device will have no audio. Users must disable volume control in these situations.<br>
 * Or, start streaming UVC 1.0 and UAC 1.0 by USB 3.2-Gen2 ISOC mode.
 *   @code {.c}
 *   build $ start-uvac-configfs -a -t
 *   @endcode
 * Or, start streaming UVC 1.0 and UAC 1.0 by USB 3.2-Gen2 bulk mode.
 *   @code {.c}
 *   build $ start-uvac-configfs -a -t -b
 *   @endcode
 *   Bulk mode can achieve higher transmission speed than ISOC mode.
 * Or, start streaming the multiple-UVCs and UAC 1.0 by USB 3.2-Gen2 bulk mode.
 *   @code {.c}
 *   build $ start-uvac-configfs -a -t -b -X -Y -Z // three UVCs
 *   build $ start-uvac-configfs -a -t -b -N 6     // seven UVCs without UAC
 *   @endcode
 * Stop streaming UVC and UAC.
 *   @code {.c}
 *   build $ start-uvac-configfs -q
 *   @endcode
 *
 * Users can use the command <B>start-uvac-configfs -h</B> for help with the options.
 *
 * Connect the PC with the USB cable.
 * @image html usb_cv5x_connect_the_pc.png "Figure 4-2. Connect the PC."
 * Check the <B>Device Manager</B>.
 * @image html usb_device_manager.png "Figure 4-3. Device Manager."
 * Use Potplayer to stream the Ambarella UVC.
 * - Menu->Preferences (F5)->Device->Webcam
 *   @image html usb_potplayer.png "Figure 4-4. Potplayer."
 * Select the video and audio device, and then open the devices to view the preview.
 * - Menu->Open->Open Webcam / Other Device
 *   @image html usb_preview.png "Figure 4-5. Preview."
 * For more details, refer to `ambarella/unit_test/private/uvc_stream/doc/Ambarella_UVAC_GETTING_STARTED.md`
 *
 * @subsection ud_usb_uvc_latency 4.4 Ambarella UVC Latency
 *
 * <table>
 * <caption id="uvac_spec_table"></caption>
 * <tr>
 * <th align="center"> codec Type
 * <th align="center"> Streaming
 * <th align="center"> Encode Latency<br> from DSP (ms)
 * <th align="center"> Encode Latency<br> from Potplayer (ms)
 * </tr>
 * <tr><td rowspan="4">MJPEG
 * <tr>     <td>1080p60</td><td>11.35</td><td>100</td></tr>
 * <tr>     <td>4kp60</td><td>23.82</td><td>240</td></tr>
 * <tr>     <td>8kp30</td><td>77.61</td><td>590</td></tr>
 * </td></tr>
 * <tr><td rowspan="4">AVC (Temporal Mode)
 * <tr>     <td>1080p60</td><td>12.64/28.75</td><td>160</td></tr>
 * <tr>     <td>4kp60</td><td>26.44/41.82</td><td>200</td></tr>
 * <tr>     <td>8kp30</td><td>102.02/124.11</td><td>390</td></tr>
 * </td></tr>
 * <tr><td rowspan="4">HEVC (Temporal Mode)
 * <tr>     <td>1080p60</td><td>12.91/29.53</td><td>120</td></tr>
 * <tr>     <td>4kp60</td><td>26.10/42.26</td><td>130</td></tr>
 * <tr>     <td>8kp30</td><td>98.83/130.96</td><td>380</td></tr>
 * </td></tr>
 * <tr><td rowspan="4">HEVC (Spatial Mode)
 * <tr>     <td>1080p60</td><td>12.64</td><td>90</td></tr>
 * <tr>     <td>4kp60</td><td>24.35</td><td>100</td></tr>
 * <tr>     <td>8kp30</td><td>87.26</td><td>360</td></tr>
 * </td></tr>
 * <tr><td rowspan="3">NV12
 * <tr>     <td>800x600@30</td><td>/</td><td>260</td></tr>
 * <tr>     <td>720p30</td><td>/</td><td>430</td></tr>
 * </td></tr>
 * </table>
 *
 * @note
 *   - This latency is measured between sensor frame exposure and UVC streaming out, it contains three parts,
 *   the pipeline latency, the transfer latency, and the decoding latency. The first two lantencies are related
 *   to the performance of Ambarella system on chip (SoC), and the decoding latency is highly dependent on the decoding performance
 *   of the connected PC / laptop.
 *   - The way to measure pipeline latency (from sensor capture done to image digital signal processing (IDSP) encode done) can be found on Page @ref fs_adv_pl_latency.
 *   - The way to measure transfer latency (from encode done to UVC frame capture done by PC host) is as follows.
 *
 * - Modify the source code
 *   @code {.c}
 *   diff --git a/unit_test/dsp_v6/iav_query.c b/unit_test/dsp_v6/iav_query.c
 *   index cbb2665..744dc8f 100644
 *   --- a/unit_test/dsp_v6/iav_query.c
 *   +++ b/unit_test/dsp_v6/iav_query.c
 *   @@ -135,6 +135,7 @@ int iav_query_bitstream(uint32_t stream_id, void *buffer, uint32_t size)
 *   #define USB_CHUNK_SIZE (2048)
 *       struct iav_framedesc *frame_desc = NULL;
 *       struct iav_querydesc query_desc;
 *   +   struct timespec tp;
 *
 *       do {
 *           memset(&query_desc, 0, sizeof(query_desc));
 *   @@ -174,6 +175,9 @@ int iav_query_bitstream(uint32_t stream_id, void *buffer, uint32_t size)
 *           frame_desc->size = (frame_desc->size + USB_CHUNK_SIZE - 1) & ~(USB_CHUNK_SIZE - 1);
 *       }
 *       memcpy(buffer, bsb_virt_addr + frame_desc->data_addr_offset, frame_desc->size);
 *   +   memset(&tp, 0, sizeof(struct timespec));
 *   +   clock_gettime(CLOCK_REALTIME, &tp);
 *   +   memcpy(buffer, &tp, sizeof(struct timespec));
 *       return frame_desc->size;
 *   }
 *
 *   diff --git a/uvc_host/test_uvc_host.c b/uvc_host/test_uvc_host.c
 *   index 6148931..2334792 100644
 *   --- a/uvc_host/test_uvc_host.c
 *   +++ b/uvc_host/test_uvc_host.c
 *   @@ -41,6 +41,7 @@ static user_options_t G_usr_opt = {
 *      .filename = {0},
 *      .stream = V4L2_PIX_FMT_MJPEG,
 *      .cap_num = -1,
 *    + .lat_num = 0,
 *      .width = UVC_DEFAULT_WIDTH,
 *      .height = UVC_DEFAULT_HEIGHT,
 *    };
 *   @@ -57,6 +58,41 @@ static uvc_cap_context_t G_uvc_cap_ctx = {
 *      .not_exit = 1,
 *    };
 *
 *   +static int measure_time(const struct v4l2_buffer *buffer, unsigned char **buf_addr)
 *   +{
 *   +  struct timespec tp1, tp2;
 *   +  void *pbuf = buf_addr[buffer->index];
 *   +  long int lat;
 *   +  static int filfram = 90, latnum = 0;
 *   +  static long int max_lat = 0, min_lat = 1000000, avg_lat = 0;
 *   +
 *   +  memset(&tp1, 0, sizeof(struct timespec));
 *   +  memset(&tp2, 0, sizeof(struct timespec));
 *   +  memcpy(&tp1, pbuf, sizeof(struct timespec));
 *   +  clock_gettime(CLOCK_REALTIME, &tp2);
 *   +  lat = (tp2.tv_sec - tp1.tv_sec) * 1000000 + (tp2.tv_nsec - tp1.tv_nsec) / 1000;
 *   +
 *   +  if (latnum != G_usr_opt.lat_num)
 *   +  {
 *   +      if (filfram)
 *   +          filfram--;
 *   +      else
 *   +      {
 *   +	        printf("clock_id = CLOCK_REALTIME, latency = %ld\n", lat);
 *   +          max_lat = (max_lat > lat) ? max_lat : lat;
 *   +          min_lat = (min_lat < lat) ? min_lat : lat;
 *   +	        avg_lat += lat;
 *   +	        latnum++;
 *   +	        if (latnum == G_usr_opt.lat_num) {
 *   +	            avg_lat = avg_lat / latnum;
 *   +	            printf("Latency(us):\nmax = %ld, min = %ld, avg = %ld\n", max_lat, min_lat, avg_lat);
 *   +          }
 *   +	    }
 *   +  }
 *   +  return 0;
 *   +}
 *   +
 *    static int save_frame(const struct v4l2_buffer *buffer, unsigned char **buf_addr, FILE *file)
 *    {
 *      void *pbuf = buf_addr[buffer->index];
 *   @@ -106,6 +142,8 @@ static int uvc_frame_capture(int fd, FILE *file, uvc_cap_context_t *ctxs)
 *      if (file) {
 *          save_frame(&buffer, buf_addr, file);
 *      }
 *
 *   +  measure_time(&buffer, buf_addr);
 *
 *      ret = ioctl(fd, VIDIOC_QBUF, &buffer);
 *      if (ret < 0) {
 *   @@ -285,6 +323,8 @@ static void usage(const char *myself)
 *    {
 *      printf("Usage: %s [options]\n", myself);
 *      printf("Available options are:\n");
 *   +  printf(" \033[34m-t --latency [frame]\033[0m			Specify the frame numbers to caculate latency, " \
 *   +      "default: function closed\n");
 *      printf(" \033[34m-d --device [devicename]\033[0m		Specify the video device name, default: /dev/video0\n");
 *      printf(" \033[34m-f --file [filename]\033[0m			Specify the file to save video frame and " \
 *          "Open the dump function, default: the dump function is closed\n");
 *   @@ -304,6 +344,9 @@ static int init_param(int argc, char **argv, user_options_t *usr_opt)
 *
 *      while ((ch = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
 *          switch (ch) {
 *   +      case 't':
 *   +          usr_opt->lat_num = atoi(optarg);
 *   +          break;
 *          case 'd':
 *              snprintf(usr_opt->dev_path, sizeof(usr_opt->dev_path), "%s", optarg);
 *              break;
 *
 *   diff --git a/uvc_host/test_uvc_host.h b/uvc_host/test_uvc_host.h
 *   index 27eb98b..f7acb98 100644
 *   --- a/uvc_host/test_uvc_host.h
 *   +++ b/uvc_host/test_uvc_host.h
 *   @@ -45,6 +45,7 @@
 *    #include <string.h>
 *    #include <getopt.h>
 *    #include <poll.h>
 *   +#include <time.h>
 *    #include <signal.h>
 *    #include <sys/mman.h>
 *    #include <sys/ioctl.h>
 *   @@ -63,6 +64,7 @@ typedef struct user_options_s {
 *      char filename[MAX_STR_LEN];
 *      unsigned int stream;
 *      unsigned int cap_num;
 *   +  unsigned int lat_num;
 *      unsigned int width;
 *      unsigned int height;
 *    } user_options_t;
 *   @@ -73,9 +75,10 @@ typedef struct uvc_cap_context_s {
 *      unsigned int reserved : 31;
 *    } uvc_cap_context_t;
 *
 *   -static const char *short_options = "d:f:hn:r:s:";
 *   +static const char *short_options = "t:d:f:hn:r:s:";
 *
 *    static struct option long_options[] = {
 *   +  {"latency", HAS_ARG, 0, 't'},
 *      {"device", HAS_ARG, 0, 'd'},
 *      {"file", HAS_ARG, 0, 'f'},
 *      {"help", NO_ARG, 0, 'h'},
 *   @endcode
 *
 * - Build the firmware
 *   1. Enable UVC function. @ref uvc_cam_build_firmware
 *   2. Enable PTP function. @ref ptp_on_ambarella_platform
 *   3. Enable UVC_HOST application.
 *      @code {.c}
 *      // For amba build:
 *      make menuconfig
 *          packages  --->
 *              usb_gadget  --->
 *                  [*]test-uvc-host-native
 *      // For yocto build:
 *      make menuconfig
 *          meta-ambaapp  --->
 *              recipes-usb-gadget  --->
 *                  [*] test-uvc-host
 *      @endcode
 * - Test the latency
 *   1. Copy the `test-uvc-host-native` to the Ubuntu PC (this tool is not related to the SDK version).
 *   2. Load firmware to the board.
 *   3. Start PTP.
 *      @code {.c}
 *      // pc command:
 *      phc2sys -s CLOCK_REALTIME -c eth0 -w -m -r -r -O 0 &
 *      ptp4l -i eth0 -m -H &
 *      // board command:
 *      phc2sys -s eth0 -c CLOCK_REALTIME -w -m -r -O 0 &
 *      ptp4l -i eth0 -m -s -H &
 *      @endcode
 *   4. Start UVC on board.
 *   5. Start capturing UVC frame on Ubuntu PC.
 *      @code {.c}
 *      // example: test the uvc latency of 300 frames
 *      ./test-uvc-host -d /dev/video0 -t 300
 *      @endcode
 *
 * @subsection ud_usb_device_uvc_gadget 4.5 Test uvc-gadget
 *
 * The uvc-gadget (https://git.ideasonboard.org/uvc-gadget.git) UVC test program, officially
 * recommended by Linux, only supports MJPEG and YUV streams with `ISOC mode`.
 *
 * Ambarella adds BULK mode support for uvc_gadget with the following patch:
 *
 *   @code {.c}
 *   From 0dacb67fc4d39743fe0ee7f2871bbdea6b5b33bc Mon Sep 17 00:00:00 2001
 *   From: jleng <jleng@ambarella.com>
 *   Date: Fri, 3 Feb 2023 15:40:18 +0800
 *   Subject: [PATCH] Add bulk transport support
 *
 *   ---
 *    include/uvcgadget/configfs.h |  1 +
 *    lib/uvc.c                    |  4 +++-
 *    src/main.c                   | 10 +++++++++-
 *    3 files changed, 13 insertions(+), 2 deletions(-)
 *
 *   diff --git a/include/uvcgadget/configfs.h b/include/uvcgadget/configfs.h
 *   index e5a7efa..054051e 100644
 *   --- a/include/uvcgadget/configfs.h
 *   +++ b/include/uvcgadget/configfs.h
 *   @@ -100,6 +100,7 @@ struct uvc_function_config {
 *
 *    	struct uvc_function_config_control control;
 *    	struct uvc_function_config_streaming streaming;
 *   +	unsigned int max_payload_size;
 *    };
 *
 *    struct uvc_function_config *configfs_parse_uvc_function(const char *function);
 *   diff --git a/lib/uvc.c b/lib/uvc.c
 *   index 747cd65..f130332 100644
 *   --- a/lib/uvc.c
 *   +++ b/lib/uvc.c
 *   @@ -173,7 +173,9 @@ uvc_fill_streaming_control(struct uvc_device *dev,
 *    		break;
 *    	}
 *
 *   -	ctrl->dwMaxPayloadTransferSize = dev->fc->streaming.ep.wMaxPacketSize;
 *   +	ctrl->dwMaxPayloadTransferSize = dev->fc->max_payload_size ? \
 *   +					 dev->fc->max_payload_size : \
 *   +					 dev->fc->streaming.ep.wMaxPacketSize;
 *    	ctrl->bmFramingInfo = 3;
 *    	ctrl->bPreferedVersion = 1;
 *    	ctrl->bMaxVersion = 1;
 *   diff --git a/src/main.c b/src/main.c
 *   index cec622a..faa9e88 100644
 *   --- a/src/main.c
 *   +++ b/src/main.c
 *   @@ -9,6 +9,7 @@
 *
 *    #include <signal.h>
 *    #include <stdio.h>
 *   +#include <stdlib.h>
 *    #include <unistd.h>
 *
 *    #include "config.h"
 *   @@ -25,6 +26,7 @@ static void usage(const char *argv0)
 *    {
 *    	fprintf(stderr, "Usage: %s [options] <uvc device>\n", argv0);
 *    	fprintf(stderr, "Available options are\n");
 *   +	fprintf(stderr, " -p max_payload_size	Set dwMaxPayloadTransferSize\n");
 *    #ifdef HAVE_LIBCAMERA
 *    	fprintf(stderr, " -c <index|id> libcamera camera name\n");
 *    #endif
 *   @@ -76,11 +78,16 @@ int main(int argc, char *argv[])
 *    	struct uvc_stream *stream = NULL;
 *    	struct video_source *src = NULL;
 *    	struct events events;
 *   +	unsigned int max_payload_size = 0;
 *    	int ret = 0;
 *    	int opt;
 *
 *   -	while ((opt = getopt(argc, argv, "c:d:i:s:k:h")) != -1) {
 *   +	while ((opt = getopt(argc, argv, "p:c:d:i:s:k:h")) != -1) {
 *    		switch (opt) {
 *   +		case 'p':
 *   +			max_payload_size = atoi(optarg);
 *   +			break;
 *   +
 *    #ifdef HAVE_LIBCAMERA
 *    		case 'c':
 *    			camera = optarg;
 *   @@ -117,6 +124,7 @@ int main(int argc, char *argv[])
 *    		printf("Failed to identify function configuration\n");
 *    		return 1;
 *    	}
 *   +	fc->max_payload_size = max_payload_size;
 *
 *    	if (cap_device != NULL && img_path != NULL) {
 *    		printf("Both capture device and still image specified\n");
 *   --
 *   2.17.1
 *   @endcode
 *
 * @note
 *   - If using BULK mode, set max_payload_size with `-p` option.
 *
 * - The configuration steps are as follows:
 *   @code {.c}
 *   build $ make menuconfig
 *     Ambarella File System Configuration ->
 *        Open Source Software (OSS) ->
 *          Multimedia Software ->
 *            [*] Add uvc-gadget into root_fs
 *   build $ make –j8
 *   @endcode
 *
 * - The test steps are as follows:
 *   @code {.c}
 *   board # echo "image: m 1280 720 10000000 8 /vendor/data/test_720p.jpg" > uvc-gadget.conf
 *   board # start-uvac-configfs -b -c uvc-gadget.conf
 *   board # uvc-gadget -p $(( 128 * 1024 )) -i /vendor/data/test_720p.jpg uvc.usb0
 *   @endcode
 *
 * @subsection ud_usb_ffs_device 4.6 USB FunctionFS Device (Cooper SDK)
 *
 * The configuration steps are as follows:
 *
 * 1. Enable the device driver.
 *   @code {.c}
 *   build $ make linux_menuconfig
 *     Device Drivers -->
 *       [*] USB supports -->
 *         [M] USB Gadget Support -->
 *           [M] USB Gadget functions configurable through configfs
 *             [*] Function filesystem (FunctionFS)
 *   @endcode
 *
 * 2. Enable the device package.
 *
 *   @par For Cooper SDK Amba Build:
 *   @code {.c}
 *   build $ make menuconfig
 *     oss -->
 *       [*] libaio (oss/libaio)
 *     packages -->
 *       usb_gadget -->
 *         [*] usb-gadget-configfs (packages/usb_gadget/configfs)
 *         ffs_test  -->
 *           [*] test-ffs-device (packages/usb_gadget/ffs_test/device)
 *   build $ make test-ffs-device
 *   @endcode
 *
 *   @par For Cooper SDK Yocto Build:
 *   @code {.c}
 *   build $ make menuconfig
 *     meta-ambapp -->
 *       recipes-usb-gadget -->
 *         [*] usb-gadget-configfs (meta-ambaapp/recipes-usb-gadget/usb-gadget-configfs)
 *         [*] test-ffs-device (meta-ambaapp/recipes-usb-gadget/test-ffs)
 *   build $ make test-ffs-device
 *   @endcode

 * 3. Enable the host package.
 *
 *   @par Build PC Host Tool With Amba Build:
 *   @code {.c}
 *   build $ sudo apt install libusb-1.0-dev
 *   build $ make menuconfig
 *     packages -->
 *       usb_gadget -->
 *         ffs_test  -->
 *           [*] test-ffs-host-native (packages/usb_gadget/ffs_test/host)
 *   build $ make test-ffs-host-native
 *   @endcode
 *
 *   @par Enable Board Host Tool With Amba Build:
 *   @code {.c}
 *   build $ sudo apt install libusb-1.0-dev
 *   build $ make menuconfig
 *     prebuild -->
 *       oss -->
 *         [*] prebuild-libusbx (prebuild/oss/armv8-a/libusbx)
 *     packages -->
 *       usb_gadget -->
 *         ffs_test  -->
 *           [*] test-ffs-host (packages/usb_gadget/ffs_test/host)
 *   build $ make test-ffs-host
 *   @endcode
 *
 *   @par Enable Board Host Tool With Yocto Build:
 *   @code {.c}
 *   build $ make menuconfig
 *     meta-ambapp -->
 *       recipes-usb-gadget -->
 *         [*] test-ffs-host (meta-ambaapp/recipes-usb-gadget/test-ffs)
 *   build $ make test-ffs-host
 *   @endcode
 *
 * 4. Test FunctionFS (single device).
 *
 *   Device:
 *   @code {.c}
 *   board # start-uvac-configfs -F 8192
 *   @endcode
 *   Host:
 *   @code {.c}
 *   host $ sudo time ./test_ffs_host -b 8192 -i 0 -t 1000
 *   @endcode
 *
 * 5. Test FunctionFS (composite device).
 *
 *   Device:
 *   @code {.c}
 *   board # start-uvac-configfs -F 65536 -a
 *   @endcode
 *   Host:
 *   @code {.c}
 *   host $ sudo time ./test_ffs_host -b 65536 -i 4 -t 1000
 *   @endcode
 *
 * @note
 *  - Users can run `./test_ffs_host -h` to get help.
 *  - Due to CV5x UDC hardware limitation, the max chunk size can only be <b>up to 64 KB</b>.
 *
 */

 /*!
 * @file sd_card.h
 * @date 2021-09-15
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
 * @page si_sd_card SD Card
 *
 * The CV5x / CV7x evaluation kit (EVK) board has two secure digital (SD) interfaces:
 * one slot is used for the SD card and the other is used for the micro SD card.
 * The two SD slots are independent; they have their own SD controllers.
 * The maximum frequency of the SD controller is 150 MHz.
 *
 *
 * @section uvc_cam_sd_slot 1. SD Slot
 *
 * The following figure shows the bottom of the CV5x EVK (Timn) board.
 * @image html sd_slots_arch_v6.png "Figure 1-1. SD Slots."
 *
 * - - - -
 *
 * @section uvc_cam_sd_card_type 2. SD Card Type
 *
 * Secure digital is a non-volatile memory card format developed by the SD Card Association
 * for use in portable devices. See https://www.sdcard.org/home/ for further details.
 * Users can also refer to http://en.wikipedia.org/wiki/SD_card for SD card standards.
 * @image html sd_sdhc_sdxc_mmc_cards_from_different_vendors.png "Figure 2-1. SD / SDHC / SDXC / MMC Cards from Different Vendors."
 * @image html sd_pins_on_an_sd_card.png "Figure 2-2. Pins on an SD Card."
 * If the application requires storing data continuously,
 * Ambarella recommends using high speed / high quality SD cards.
 * High speed / high quality SD cards write data in less time and require less CPU for input / output (I/O).<br>
 * The following sections provide information about SD card formats, speeds, and design notes.
 * Ambarella does not recommend normal-speed SD cards, low-speed SD cards, low-speed multi-media controller (MMC) cards,
 * or small-capacity SD cards for typical internet protocol camera (IPCAM) system designs or car DV designs.
 * As an alternative, Ambarella recommends using SDHC class 4 (or above) for continuous data writing applications.<br>
 * If applications require long-time, continuous data writing, Ambarella recommends using SDHC class 4 or above
 * for typical IP camera or car DV products.<br>
 * Although various SD cards might be usable for use with CV5x,
 * only the SD cards in the following list are verified on the CV5x EVK board.
 * <table>
 * <tr>
 * <th><div style="width:120px">Brand</div></th><th><div style="width:120px"></div>Class</th>
 * <th><div style="width:120px">Capacity</div></th><th><div style="width:120px"></div>Type</th>
 * </tr>
 * <tr><td rowspan="6">Kingston
 * <tr>		        	<td>Normal</td><td>2 GB</td><td>MicroSD card</td></tr>
 * <tr>				<td>Class 4</td><td>4 GB</td><td>MicroSD card</td></tr>
 * <tr>		        	<td></td><td>2 GB</td><td>SD card</td></tr>
 * <tr>		        	<td></td><td>4 GB</td><td>SD card</td></tr>
 * <tr>		        	<td>Class 4</td><td>4 GB</td><td>SDHC card</td></tr>
 * </td></tr>
 * <tr><td rowspan="3">Kingmax
 * <tr>		        	<td>Normal</td><td>2 GB</td><td>MicroSD card</td></tr>
 * <tr>				<td>Class 6</td><td>4 GB</td><td>Micro-SDHC card</td></tr>
 * </td></tr>
 * <tr><td rowspan="6">SanDisk
 * <tr>		        	<td>Class 2</td><td>4 GB</td><td>MicroSD card</td></tr>
 * <tr>				<td>Class 4</td><td>4 GB</td><td>MicroSD card</td></tr>
 * <tr>		        	<td>Normal</td><td>512 MB</td><td>SD card</td></tr>
 * <tr>		        	<td>Class 2</td><td>4 GB</td><td>SDHC card</td></tr>
 * <tr>		        	<td>Class 4</td><td>4 GB</td><td>SDHC card</td></tr>
 * </td></tr>
 * <tr><td rowspan="3">Toshiba
 * <tr>				<td>Class 4</td><td>4 GB</td><td>MicroSD card</td></tr>
 * <tr>		        	<td>Class 10</td><td>16 GB</td><td>SDHC card</td></tr>
 * </td></tr>
 * <tr><td rowspan="3">Apacer
 * <tr>		        	<td></td><td>2 GB</td><td>MicroSD card</td></tr>
 * <tr>				<td>Class 4</td><td>4 GB</td><td>MicroSD card</td></tr>
 * </td></tr>
 * <tr><td rowspan="3">PNY
 * <tr>		        	<td></td><td>2 GB</td><td>MicroSD card</td></tr>
 * <tr>				<td>Class 4</td><td>4 GB</td><td>MicroSD card</td></tr>
 * </td></tr>
 * <tr><td>PQI</td><td></td><td>2 GB</td><td>MicroSD card</td></tr>
 * <tr><td>Esuninfo</td><td></td><td>2 GB</td><td>MicroSD card</td></tr>
 * <tr><td>Verbatim</td><td></td><td>2 GB</td><td>MicroSD card</td></tr>
 * <tr><td>SONY</td><td>Class 4</td><td>32 GB</td><td>MicroSD card</td></tr>
 * <tr><td>Lenovo</td><td></td><td>1 GB</td><td>SD card</td></tr>
 * <tr><td>Adata</td><td></td><td>256 MB</td><td>SD card</td></tr>
 * <tr><td rowspan="3">Transcend
 * <tr>		        	<td>Class 10</td><td>8 GB</td><td>SDHC card</td></tr>
 * <tr>				<td>Class 10</td><td>32 GB</td><td>SDHC card</td></tr>
 * </td></tr>
 * </table>
 * <br>
 *
 * ---
 *
 * @section hardware_software_preparation 3. Hardware and Software Preparation
 *
 * @subsection cv5_evk 3.1 CV5 EVK
 *
 * For CV5, CONFIG_CV5_TIMN_SELECT_SD1 should be enabled for SDIO0, and CONFIG_CV5_TIMN_SELECT_SD2 should be enabled for SDIO1.<br>
 * For CV52, CONFIG_CV52_CRCO_SELECT_SD1 should be enabled for SDIO0, and CONFIG_CV52_CRCO_SELECT_SD2 should be enabled for SDIO1.<br>
 * For CV5 and CV52, SW2-1, SW2-2, and SW2-3 should be set to "off"; remove J18 and connect J16 when using SDIO0.
 * SW2-4, SW3-1, and SW3-2 should be set to "off"; remove J24 and connect J22 when using SDIO1.
 *
 * - - - -
 *
 * @section mount_format 4. Mount and Format
 *
 * @subsection mount_an_sd_card 4.1 Mount an SD Card
 *
 * The CV5x board recognizes the SD card after the card is inserted into the SD card slot,
 * and it is automatically mounted to `/mnt/sdcard`.
 * Enter mount on the CV5x board to see the mounting information.
 * @code {.c}
 * board # mount
 * /dev/mmcblk0p1 on /sdcard type vfat
 * (rw,relatime,fmask=0000,dmask=0000,allow_utime=0022,codepage=cp437,iocharset=iso8859-1,
 * shortname=mixed,errors=remount-ro)
 * @endcode
 * @note
 * NTFS file system is not supported by default.
 * To get NTFS-formatted SD cards recognized by the board, enable the kernel menuconfig in bellow:
 * @code {.c}
 * File systems
 *     DOS/FAT/NT Filesystems
 *         <*> NTFS file system support
 *             [*]   NTFS write support
 * @endcode
 *
 * @subsection unmount_an_sd_card 4.2 Unmount an SD Card
 *
 * Before removing the SD card, close all files, then unmount the SD card (see below).
 * @code {.c}
 * board # cd /
 * board # umount /dev/mmcblk0p1
 * @endcode
 * If the message "Device or resource busy" appears,
 * check if all files on the SD card are closed
 * and `/mnt/sdcard` is not being accessed (type "cd /" to go to the root directory).
 * 1. Format the SD card.
 *   Although the SD card may arrive pre-formatted,
 *   Ambarella recommends formatting the card manually to avoid potential errors and to maximize performance.<br>
 *   The SD card can be formatted to FAT32, NTFS, ext3, and other file systems.
 *   For SD cards equal to or less than 32 GB, FAT32 is recommended.
 *   For SD cards larger than 32 GB, NTFS is preferred, as Windows limits FAT32 partitions to 32 GB.<br>
 *   Windows 7 also supports exFAT, but exFAT is not formally supported by the Linux kernel.
 *   Ext3 is supported on Linux to support large SDHC (or SDXC) cards, but Windows does not recognize ext3.<br>
 *   There are three main options to format the SD cards to the required format.
 *   To successfully format an SD card,
 *   the write protection lock on the side of the card must be in the "unlock" position.
 *   SD mini and micro SD cards must be used with an adapter or specialized USB card reader
 *   when a computer is formatting them.
 * 2. Use a format utility.<br>
 *   Most computer systems include generic formatting utilities for nearly every format of writable media.
 *   For example, in the Windows operating system (OS), users can access the format option
 *   by right-clicking an "SD card" driver in the "My Computer" folder.
 *   Use the default setting to format the SD card.<br>
 *   The SD Association SD Formatter is the recommended option for the Windows OS platform.
 *   The SD Formatter is recommended because generic-format utilities are not designed
 *   to format SD cards to their official SD memory format requirements that are required to run at optimum performance on devices.
 *   The SD formatter that the SD Association offers is free
 *   and is offered at SDcard.org: https://www.sdcard.org/downloads/formatter_3/.
 * 3. The tool "mkdosfs" is included in the CV5x Flexible Linux SDK.<br>
 *   The tool can format an SD card to the FAT32 format, and is used to create a DOS file system under Linux.
 *   @code {.c}
 *   board # umount /dev/mmcblk0p1 (Unmount the SD card first)
 *   board # mkdosfs -v -n LOCAL /dev/mmcblk0p1
 *   board # mount /dev/mmcblk0p1 /tmp/mmcblk0p1
 *   @endcode
 *   If users intend to use a SD card as common data storage,
 *   they must format the card in their product (under Linux) using mkdosfs in order to ensure optimal performance.
 *   An SD card that is formatted by a different tool on Windows can potentially result in lower performance.<br>
 * 4. Check the file system integrity.<br>
 *   The tool "dosfsck" is used to check and repair the MS-DOS file system.
 *   The source code of dosfs is available at http://ftp.uni-erlangen.de/pub/Linux/LOCAL/dosfstools/.
 *   @code {.c}
 *   board # dsfsck /dev/mmcblk0p1
 *   @endcode
 *   If the file system of the SD card is correct, the output message is as follows:
 *   @code {.c}
 *   dosfsck 2.11, 12 Mar 2005, FAT32, LFN
 *   /dev/mmcblk0p1: 1 files, 1/965792 clusters
 *   @endcode
 *   @note
 *   If the SD card is removed before unmounting,
 *   users must check the integrity of the file system again before using the card.
 *   Removing the SD card before unmounting can cause inconsistent data storage
 *   and reduce the integrity of the file system.
 *   To avoid this potential issue, good product design should include unmounting the SD card before removing.
 *   Alternatively,
 *   it should call a poweroff command to enable the system to close all open files and flush data to sync,
 *   and then unmount.
 * 5. Partition the SD card.<br>
 *   Occasionally, users must partition the SD card.
 *   For example, if a user must format a 64-GB SDXC card to the FAT32 file system, note the following:
 *   because Windows limits FAT32 to 32 GB, multiple partitions are required.
 *   However, only the first partition can be seen on Windows while Linux can display all partitions.<br>
 *   <B>Gparted</B> is a software utility that scans storage devices,
 *   examining the data in order to detect partitions which may exist
 *   but are absent from the disk's partition tables.
 *   For more details, go to http://gparted.sourceforge.net/.
 *   @note
 *   If users must access all partitions in Windows, Ambarella does not recommend using the Linux tool to form the partition.
 *   As an alternative, users can attempt to port exFAT to Linux or use NTFS on the SD card to support large partitions
 *   that can be recognized on Windows.
 *
 * <br>
 *
 * - - - -
 *
 * @section write_performance 5. Write Performance
 *
 * In most applications, the SD card is used as local storage in which data is written.
 * However, data write performance and I/O CPU usage is important;
 * if the I/O CPU usage is too high, it can lead to write errors or other issues.<br>
 * Good write performance is achieved
 * if the CPU load in the I/O operation is less than 20% (on average) in the top command
 * when performing a continuous write to the SD card.
 * If the write performance does not meet this average, it should be checked;
 * reasons for less than optimal performance could include a slow SD card,
 * too many concurrent read / write operations on the SD card, insufficient I/O memory buffer,
 * or bad hardware design.
 * 1. Check write performance.<br>
 *   Check the SD card write performance using the command <B>dd</B>.
 *   The usage of dd can be found in the Linux user manual.
 *   @code {.c}
 *   board # time dd if=/dev/zero of=/sdcard/write_tmp bs=1M count=128
 *   128+0 records in
 *   128+0 records out
 *   134217728 bytes (128.0MB) copied, 14.356227 seconds, 8.9MB/s
 *   real 0m 14.36s
 *   user 0m 0.00s
 *   sys 0m 0.75s
 *   @endcode
 *   The results are shown above: the average writing speed is 128 MB / 14.36 s = 8.9 MB/s
 * 2. Improve write performance:<br>
 *   Users can optimize the writing method to improve the write performance of the FAT32 SD card.
 *   If each "write" syscall is in multiples of 16-KB sizes, the SD card can obtain a better write performance.
 *   For a larger SD card, 32 KB or 64 KB is preferred.
 *   A quick solution is to write in multiples of 64 KB to obtain optimal performance on all SD cards.
 *   If writing data of a random size, the FAT32 file system may include fragments.
 *   The fragments will be lower than the writing speed, and the I/O operation may require more CPU resources,
 *   affecting the overall write performance.<br>
 *   The prototype of the write function is as follows:
 *   @code {.c}
 *   ssize_t write(int fd, const void *buf, size_t count)
 *   @endcode
 *   For the FAT32 file system, Ambarella suggests that the "count" is aligned to 64 KB in the code,
 *   meaning that if there is not enough data, it is preferred to place it into a queue
 *   and add data to increase the size to 64 KB.
 *
 * - - - -
 *
 * @section boot_from_rootfs_in_sd_card 6. Boot from Rootfs in the SD Card
 *
 * The size of rootfs can be very large, and flash may not have sufficient space to store it.
 * In this case, users can use SD card to store rootfs.<br>
 * The following steps use the SD card as rootfs: the kernel is stored in the flash, and
 * rootfs is stored in the SD card.
 *
 * 1. Change rootfs to the SD card.
 *   @code {.c}
 *   ambarella$ git diff
 *   diff --git a/rootfs/skeleton/initramfs_sysroot/init b/rootfs/skeleton/initramfs_sysroot/init
 *   index 59e351b..563b58a 100755
 *   --- a/rootfs/skeleton/initramfs_sysroot/init
 *   +++ b/rootfs/skeleton/initramfs_sysroot/init
 *   @@ -9,6 +9,9 @@ SYSTEM_DEV=`echo ${CMDLINE##*root=}|awk '{print $1}'`
 *    SYSTEM_FSTYPE=`echo ${CMDLINE##*rootfstype=}|awk '{print $1}'`
 *    SYSTEM_MOUNT=/system
 *
 *   +SYSTEM_DEV=/dev/mmcblk0
 *   +SYSTEM_FSTYPE=ext4
 *   +
 *    __clean_boot() {
 *           exec /linuxrc
 *    }
 *   @endcode
 *
 * 2. Enable initramfs and build it (Amba build).
 *   @code {.c}
 *   build $ source build/env/amba-build.env
 *   build $ make ipcam_config
 *   build $ make menuconfig
 *       rootfs  --->
 *           [*] initramfs (rootfs/initramfs)  --->
 *   build $ make initramfs
 *   @endcode
 *
 * 3. Generate rootfs, whose type is `tar`.
 *   @code {.c}
 *    ambarella/metadata$ git diff
 *    diff --git a/meta-ambabsp/conf/machine/include/rootfs-type.inc b/meta-ambabsp/conf/machine/include/rootfs-type.inc
 *    index f079b40..f54d7be 100644
 *    --- a/meta-ambabsp/conf/machine/include/rootfs-type.inc
 *    +++ b/meta-ambabsp/conf/machine/include/rootfs-type.inc
 *    @@ -144,5 +144,5 @@ python() {
 *                 comptype = '-zst'
 *             fstype = fstype + comptype
 *
 *    -    d.setVar('IMAGE_FSTYPES', fstype)
 *    +    d.setVar('IMAGE_FSTYPES', '%s tar' % (fstype))
 *     }
 *   @endcode
 *
 * 4. Set the initramfs file path (Yocto build).
 *   @code {.c}
 *   build $ source build/env/yocto-build.env
 *   build $ make ipcam_config
 *   build $ make linux_menuconfig
 *       search CONFIG_INITRAMFS_SOURCE
 *       (/home/jleng/data/cooper_sdk/ambarella/out/amba_out/cv3_dk_mini/firmware/initramfs.cpio.gz) Initramfs source file(s)
 *   @endcode
 *
 * 5. Change the ext4 and MMC drivers to "built-in" instead of "module".
 *   @code {.c}
 *   build $ make linux_menuconfig
 *       search CONFIG_EXT4_FS
 *           <*> The Extended 4 (ext4) filesystem
 *           [*] Use ext4 for ext2 file systems
 *           [*] Ext4 POSIX Access Control Lists
 *           [*] Ext4 Security Labels
 *           [ ] Ext4 debugging support
 *           [ ] JBD2 (ext4) debugging support
 *       search CONFIG_MMC
 *           <*> MMC/SD/SDIO card support  --->
 *               < > HW reset support for eMMC
 *               < > Simple HW reset support for MMC
 *               <*> MMC block device driver
 *               (32) Number of minors per block device
 *               < > SDIO UART/GPS class support
 *               < > MMC host test driver
 *                   *** MMC/SD/SDIO Host Controller Drivers ***
 *               [ ] MMC host drivers debugging
 *               <*> Ambarella Media Processor SD/MMC Host Controller driver
 *               < > ARM AMBA Multimedia Card Interface support
 *               <*> Secure Digital Host Controller Interface support
 *               < >     SDHCI support on PCI bus
 *               <*>     SDHCI platform and OF driver helper
 *               < >         SDHCI OF support for the Arasan SDHCI controllers
 *               < >         SDHCI OF support for the ASPEED SDHCI controller
 *               < >         SDHCI OF support for the Atmel SDMMC controller
 *               < >         SDHCI OF support for the Synopsys DWC MSHC
 *               <*>         SDHCI support for Ambarella DWC MSHC
 *               < >         SDHCI support for the Cadence SD/SDIO/eMMC controller
 *   @endcode
 *
 * 6. Build ipcam-image and burn the image to the board.
 *   @code {.c}
 *   build $ make
 *   @endcode
 *
 * 7. Build ros rootfs.
 *   @code {.c}
 *   build $ make ipcam-image_clean
 *   build $ make ros-image
 *   @endcode
 *
 * 8. Untar rootfs.tar to the SD card.
 *   @code {.c}
 *   build $ sudo umount /dev/mmcblk0
 *   build $ sudo mkfs.ext4 /dev/mmcblk0
 *   build $ sudo mkdir -p /mnt/sd
 *   build $ sudo mount -t ext4 /dev/mmcblk0 /mnt/sd
 *   build $ sudo tar -xvpf images/ros-image-galactic-cv3x-20230721091753.rootfs.tar -C /mnt/sd
 *   @endcode
 *
 * 9. Insert the SD card to board and reboot it. The kernel is from the flash and rootfs is from the SD card.
 *
 * @note
 *   - `/dev/mmcblk0` is the SD card device; the actual value depends on the user's system.
 *   - The rootfs of Amba build is different from Yocto build; it is `ambarella/out/amba_out/<board>/fakeroot`
 *
 * - - - -
 *
 * @section troubleshooting 7. Troubleshooting
 *
 * <B>Question 1:</B> Why is the system boot speed too slow when using the customer’s board?
 * It seems to be related to the SD card interrupt.<br>
 * <B>Answer:</B>
 *  1. Check the hardware design. If there is only one SD interface that is being used, and no secure digital input / output (SDIO) interface,
 *    check the SD configuration file.
 *  2. To verify if the slow boot issue is caused by the SD card, do not insert ambarella_sd.ko.
 *    Remove the following line from `/etc/init.d/S11init`:
 *    @code {.c}
 *    if [ -r /lib/modules/$kernel_ver/kernel/drivers/mmc/host/ambarella_sd.ko
 *	    modprobe ambarella_sd
 *    fi
 *    @endcode
 *    If the issue is solved, the slow boot was a result of SD detection.
 *    If the issue is not solved, proceed to the next troubleshooting step.
 *  3. Check if fixed_cd is floating.<br>
 *    Ambarella recommends pulling down fixed_cd if SDIO WiFi is not used permanently.<br>
 *    If SDIO WiFi is reserved for future use and fixed_cd is floating,
 *    disable SDIO WiFi detection on the software side.<br>
 *    Modify `/etc/init.d/S11init` as follows:
 *    @code {.c}
 *    if [ -r /lib/modules/$kernel_ver/kernel/drivers/mmc/host/ambarella_sd.ko
	 *    echo 0 > cat /debug/mmc0/ambhost/fixed_cd
	 *    modprobe ambarella_sd
 *    fi
 *    @endcode
 *
 * <B>Question 2:</B> Why do I/O errors occur after the message:
 * "ambarella_sd_request cmd25 timeout 2@100, retries" when recording to the SD card?<br>
 * <B>Answer:</B> cmd25 is WRITE_MULTIPLE_BLOCK.
 * As the SD device is busy, no acknowledgement is passed after the defined time is out.<br>
 * Try the following solutions to solve this issue:
 * 1. Use 12 MHz as the SD clock frequency.<br>
 *   The SD clock quality is not good enough for some boards, which may lead SD cards to being unrecognized.
 *   Lowering the SD clock frequency fixes this issue.
 * 2. Check the current SD clock frequency.
 *   @code {.c}
 *   board # grep sd /proc/ambarella/clock
 *   @endcode
 * 3. Modify ambarella/boards/<broad>/bsp/<broad>.dts to use 12 MHz as the SD clock frequency.
 *   @code {.c}
 *   max-frequency = <12000000>;
 *   @endcode
 *
 * <B>Question 3:</B> Why do "out of memory" or "cannot allocate memory" errors appear
 * when data is recorded to the SD card over a long period of time?<br>
 * <B>Answer:</B> Large amounts of memory are used to record streams to the SD card or perform intensive SD written tests.
 * Therefore, the free memory may be insufficient for other applications.
 * The errors mentioned above are caused when users attempt to use a large amount of memory.<br>
 * To avoid this issue, perform the following steps:
 * 1. Dynamically allocate memory to create memory fragments,
 *   making further memory allocation difficult or impossible.
 *   Users should try allocating the memory consisting of large blocks to the applications, and manage the memory internally.
 * 2. The kernel reserves a dedicated amount of memory for itself to process jobs.
 *   Release part of the memory to the user space.<br>
 *   Check the memory size (20000 KB) reserved for the kernel.
 *   @code {.c}
 *   board # cat /proc/sys/vm/min_free_kbytes
 *   @endcode
 *   Check the free memory size.
 *   @code {.c}
 *   board # top -d 1
 *   @endcode
 *   Memory: 32488K used, 183572K free, 0K shared, 0K buffer, 13148K cached<br>
 *   Edit /proc/sys/vm/min_free_kbytes. Note that the change will be forgotten after rebooting.
 *   @code {.c}
 *   board # echo 1024 > /proc/sys/vm/min_free_kbytes
 *   @endcode
 */
/*!
 * @file wifi.h
 * @date 2021-09-15
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
 * @page si_wifi WiFi
 *
 * The computer vision (CV) series system on chip (SoC) platform supports WiFi with USB and secure
 * digital input / output (SDIO) interfaces.
 * For USB WiFi, contact the Ambarella support team for further information.
 * Depending on the WiFi driver and firmware (FW) copyright and support, the standard software
 * development kit (SDK) may not include WiFi drivers or WiFi firmware.
 * Users can contact the Ambarella support team with any questions.
 *
 * @note
 *   - This chapter introduces SDIO WiFi connected to the SoC.
 *   - Battery-powered IP (BPI) evaluation kit (EVK) boards use an internet of things (IoT) WiFi
 *     microcontroller unit (MCU); ingore this chapter and refer to the document
 *     <em>Ambarella BPI Suite: Getting Started Guide</em> for details.
 *
 * @section wifi_with_sdio_interface 1. WiFi Modules with SDIO Interface
 *
 * The board supports many SDIO WiFi products, listed as follows:
 * <table>
 * <caption id="sdio_wifi_support_list">Table 1-1. SDIO WiFi Support List.</caption>
 * <tr><th align="center" width="200px"> WiFi Vendor   <th align="center" width="200px"> Chip Name
 * <tr><td rowspan="19"> Broadcom                      <td> BCM43362(AP6181)
 * <tr>                                                <td> BCM43341(AP6441) <br>
 * <tr>                                                <td> BCM43340(AP6234) <br>
 * <tr>                                                <td> BCM43438(AP6212) <br>
 * <tr>                                                <td> BCM43438(AP6452) <br>
 * <tr>                                                <td> BCM43438A1(AP6212A) <br>
 * <tr>                                                <td> BCM43436(AP6236) <br>
 * <tr>                                                <td> BCM43455(AP6255) <br>
 * <tr>                                                <td> BCM43456(AP6256) <br>
 * <tr>                                                <td> BCM43456(AP6745) <br>
 * <tr>                                                <td> BCM43751(AP6271S) <br>
 * <tr>                                                <td> BCM43752(AP6275S) <br>
 * <tr>                                                <td> BCM43241(AP62X2) <br>
 * <tr>                                                <td> BCM4356(AP6356S) <br>
 * <tr>                                                <td> BCM4359(AP6359SA) <br>
 * <tr>                                                <td> BCM4359(AP6398S) <br>
 * <tr>                                                <td> BCM43012(AP6201) <br>
 * <tr>                                                <td> BCM430132(AP6203) <br>
 * <tr>                                                <td> BCM43143 <br>
 * <tr><td rowspan="12"> Infineon                      <td> CYW4343W
 * <tr>                                                <td> CYW43438 <br>
 * <tr>                                                <td> CYW43439 <br>
 * <tr>                                                <td> CYW43012 <br>
 * <tr>                                                <td> CYW43455 <br>
 * <tr>                                                <td> CYW4373 <br>
 * <tr>                                                <td> CYW4356 <br>
 * <tr>                                                <td> CYW54590 <br>
 * <tr>                                                <td> CYW54591 <br>
 * <tr>                                                <td> CYW55571 <br>
 * <tr>                                                <td> CYW55572 <br>
 * <tr>                                                <td> CYW55573 <br>
 * </table>
 *
 * Some modules from WiFi vendors are as follows:
 *   @image html wifi_broadcom_bcm43340_ap6234_sdio_wifi_uartbt.png "Figure 1-1. Broadcom BCM43340 (AP6234) SDIO WiFi + UART BT."
 *   @image html wifi_broadcom_bcm43362_ap6181_sdio_wifi.png "Figure 1-2. Broadcom BCM43362 (AP 6181) SDIO WiFi."
 *   @image html wifi_broadcom_bcm43438_ap6212_sdio_wifi_uartbt.png "Figure 1-3. Broadcom BCM43438 (AP6212) SDIO WiFi + UART BT."
 *   @image html wifi_broadcom_bcm43752_sdio_wifi.png "Figure 1-4. Broadcom BCM43752 (AP6275S) SDIO WiFi."
 *   @image html wifi_infineon_cyw4373_sdio_wifi.png "Figure 1-5. Infineon CYW4373 SDIO WiFi."
 *   @image html wifi_infineon_cyw54591_sdio_wifi.png "Figure 1-6. Infineon CYW54591 SDIO WiFi."

 *   @note
 *   If customers require more information about these modules, contact WiFi vendor for assistance.
 *
 * - - - -
 *
 * @section wifi_compile  2. Compile SDK Firmware with WiFi Driver
 * 1. Modify the coresponding SDIO for WiFi in the device trees (DTS) file. Using sdmmc0 on cv22_walnut as an example.
 *   @code {.c}
 *	  sdmmc0: sdmmc0@e0004000 {
 *		  pwr-gpios = <&gpio 109 0x1>;
 *		  v18-gpios = <&gpio 156 0x1>;
 *		  max-frequency = <100000000>;
 *		  bus-width = <4>;
 *	  };
 *   @endcode
 *   @note
 *   - If WiFi is not stable or is difficult to detect during the debugging stage, users can decrease max-frequency to debug.
 *   - If users want to change the host voltage manually, they can comment out the following line.
 *   Then, they can set GPIO156 to 1 for 1.8 V or to 0 for 3.3 V.
 *
 * 2. Driver and firmware menu
 *   @par For CV2x SDK 3.0 Amba build:
 *   @code {.c}
 *   build $ make menuconfig
 *    [*] Ambarella Linux Configuration	--->
 *      [*]   Ambarella External Linux Configuration  --->
 *        [*] External WiFi-Bluetooth Configuration
 *          [*] Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *          [ ]   Add PM State in proc file
 *          [ ]   Support WiFi ARP offload
 *          [ ]   Support WiFi txglom
 *          [*]   Out-of-Band Interrupt
 *          (4)   The GPIO of Platform to control WiFi WL_HOST_WAKE
 *          (102) The GPIO of Platform to control WiFi WL_REG_ON
 *                Broadcom WiFi driver Version (Kernel 4.14, 5.4; Driver 101.10.361.21 (r892223-20220709-05))  --->
 *                Broadcom WiFi Firmware and nvram Version (BCM43752(AP6275S))  --->
 *          [ ] Infineon WiFi SDIO Drivers
 *   @endcode
 *   @note
 *   - Some menus will be shown after the WiFi module brand is selected.
 *   - Select the corresponding driver version and firmware. If the option required by the user is not available, contact Ambarella or the WiFi vendor.
 *   - 102 is the host CPU general purpose input / output (GPIO), which connects to WL_REG_ON on the WiFi device.
 *   - The host CPU GPIO is 4, which connects to WL_HOST_WAKE on the WiFi device and enables it when using the out of band (OOB) interrupt.
 *   (Ambarella strongly recommends that users use OOB). It can be changed according to the hardware.
 *
 *  Select the option in menu to copy pre-built WiFi firmware and nvram data into the firmware.
 *   @code {.c}
 *    [*] Ambarella Prebuild  --->
 *      [*]   Add Broadcom Wifi firmware and nvram data into root_fs
 *      [ ]   Add Cypress Wifi firmware and nvram data into root_fs
 *
 *   @endcode
 *
 *   @par For Cooper Amba build:
 *   @code {.c}
 *   build $ make menuconfig
 *    drv_modules  --->
 *      external  --->
 *        wireless  --->
 *          [*] kernel-module-external-bcmdhd (drv_modules/external/wireless/broadcom)  --->
 *            [*] Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *            [ ]   Add PM State in proc file
 *            [ ]   Support WiFi ARP offload
 *            [ ]   Support WiFi txglom
 *            [*]   Out-of-Band Interrupt
 *            (4)   The GPIO of Platform to control WiFi WL_HOST_WAKE
 *            (102) The GPIO of Platform to control WiFi WL_REG_ON
 *                Broadcom WiFi driver Version (Kernel 4.14, 5.4; Driver 101.10.361.21 (r892223-20220709-05))  --->
 *                Broadcom WiFi Firmware and nvram Version (BCM43752(AP6275S))  --->
 *          [ ] kernel-module-external-cyfmac (drv_modules/external/wireless/infineon)  --->
 *   @endcode
 *
 *  If it is infineon WiFi module, use the following command.
 *    @code {.c}
 *          [ ] kernel-module-external-bcmdhd (drv_modules/external/wireless/broadcom)  --->
 *          [*] kernel-module-external-cyfmac (drv_modules/external/wireless/infineon)  --->
 *            [*]   Infineon WiFi SDIO Drivers
 *                Infineon WiFi driver Version (FMAC DRIVER for Kernel 5.4, 5.15(v5.15.58-backports-20230901))  --->
 *                Infineon WiFi FMAC Firmware (FMAC: CYW55571)  --->
 *   @endcode
 *
 *   @par For Cooper Yocto build:
 *   @code {.c}
 *   build $ make menuconfig
 *    meta-external  --->
 *      recipes-wireless  --->
 *        [*] firmware-broadcom-wifi (meta-external/recipes-wireless/firmware-broadcom-wifi)
 *        [*] kernel-module-external-bcmdhd (meta-external/recipes-wireless/kernel-module-bcmdhd)  --->
 *        [*] Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *            [ ]   Add PM State in proc file
 *            [ ]   Support WiFi ARP offload
 *            [ ]   Support WiFi txglom
 *            [*]   Out-of-Band Interrupt
 *            (4)   The GPIO of Platform to control WiFi WL_HOST_WAKE
 *            (102) The GPIO of Platform to control WiFi WL_REG_ON
 *                Broadcom WiFi driver Version (Kernel 4.14, 5.4; Driver 101.10.361.21 (r892223-20220709-05))  --->
 *                Broadcom WiFi Firmware and nvram Version (BCM43752(AP6275S))  --->
 *   @endcode
 *
 *   @note
 *   - It does not support infineon WiFi fmac driver for Yocto build.
 *
 * 3. Below is the WiFi tools menu:
 *   @par For CV2x SDK 3.0 Amba build:
 *   @code {.c}
 *    [*] Ambarella File System Configuration  --->
 *      Open Source Software (OSS)  --->
 *        Network/BlueTooth Packages >
 *          Wireless >
 *            [ ] Add wireless tools into root_fs
 *            [ ] Add wireless regulatory db into root_fs
 *            -*- Add wpa_supplicant tool into root_fs
 *            [*]   Add wpa_supplicant tool stock version into root_fs  --->
 *            [ ] Add gpsd and its client tool into root_fs
 *            -*- Add iw wireless tool into root_fs
 *            -*- Add dnsmasq into root_fs
 *            [ ] Add hostapd into root_fs
 *          Network Utilities  --->
 *            Network Management Service (No Network Management Service)  --->
 *   @endcode
 *   @note
 *   - Ambarella recommends to unselect NetworkManager in Menuconfig.
 *     The NetworkManager may affect the WiFi tune during the WiFi bring-up stage.
 *
 *   @par For Cooper Amba build:
 *   @code {.c}
 *    prebuild  --->
 *      oss  --->
 *        [*] prebuild-dnsmasq (prebuild/oss/armv8-a/dnsmasq)
 *        [*] prebuild-iw (prebuild/oss/armv8-a/iw)
 *        [*] prebuild-wpa_supplicant (prebuild/oss/armv8-a/wpa_supplicant)
 *   @endcode
 *
 *   @par For Cooper Yocto build:
 *   @code {.c}
 *    meta  --->
 *      recipes-connectivity  --->
 *        [*] iw (meta/recipes-connectivity/iw
 *        [*] wpa-supplicant (meta/recipes-connectivity/wpa-supplicant)
 *    meta-networking  --->
 *      recipes-support  --->
 *        [*] dnsmasq (meta-networking/recipes-support/dnsmasq)
 *   @endcode
 *
 * 4. Network throughout test application menu:
 *   @par For CV2x SDK 3.0 Amba build:
 *   @code {.c}
 *    [*] Ambarella File System Configuration  --->
 *      Open Source Software (OSS)  --->
 *        Benchmark Tools  --->
 *          [*] Add iperf support
 *          [*] Add iperf3 support
 *   @endcode
 *
 *   @par For Cooper Amba build:
 *   @code {.c}
 *    prebuild  --->
 *      oss  --->
 *        [*] prebuild-iperf (prebuild/oss/armv8-a/iperf)
 *        [*] prebuild-iperf3 (prebuild/oss/armv8-a/iperf3)
 *   @endcode
 *
 *   @par For Cooper Yocto build:
 *   @code {.c}
 *    meta-oe  --->
 *      recipes-benchmark  --->
 *        [*] iperf3 (meta-oe/recipes-benchmark/iperf3)
 *   @endcode
 *
 * 5. Build the SDK.
 *   @code {.c}
 *   build $ make
 *   @endcode
 * or
 *   @code {.c}
 *   build $ make -j8
 *   @endcode
 *
 * - - - -
 *
 * @section WiFi_test  3. WiFi Test on the EVK Board
 * 1. Boot up the system.
 *
 * 2. Plug in the WiFi EVB card. If users comment out "v18-gpios = <&gpio 156 0x1>;"
 *    line in DTS file, they should set the SDIO host voltage first before plugging in the WiFi EVB card.
 *   @code {.c} board# modprobe ambad    //driver for amba_debug @endcode
 *   @code {.c} board# amba_debug -g 156 -d 1    //set host to 1.8V @endcode
 *   @code {.c} board# amba_debug -g 156 -d 0    //set host to 3.3V @endcode
 *
 * 3. When plugging in the WiFi card, the WiFi driver is automatically loaded.
 *   - DHD driver: bcmdhd.ko for BroadCom; cywdhd.ko for Infineon.
 *   - FMAC driver of Infineon: cfg80211.ko, compat.ko, brcmfmac.ko, brcmutil.ko
 *
 * 4. Type the following command to enable the wlan0 interface.
 *   @code {.c} board# ifconfig wlan0 up @endcode
 *
 * 5. Connect to AP when using station mode.
 *   @code {.c} board# wifi_setup.sh sta nl80211 WiFi-SSID  WiFi-password @endcode
 *
 * 6. Set up the AP when using AP mode.
 *   @code {.c} board# wifi_setup.sh ap nl80211 SSID Password wpawpa2 Channel @endcode
 *
 * 7. WiFi throughput test:
 *   The Ambarella EVK is used as the iperf client, and the PC is used as the iperf server.
 *   @code {.c}
 *    AMBA EVK IP address: 10.0.0.111
 *    PC IP address: 10.0.0.10
 *   @endcode
 *
 *    1) TCP transmit (TX):
 *   @code {.c} board# iperf -c 10.0.0.10 -i1 -w 1M -t999999 @endcode
 *
 *    2) TCP receive (RX):
 *   @code {.c} board# iperf -i1 -s @endcode
 *
 *    3) UDP TX:
 *   @code {.c} board# iperf -c 10.0.0.10 -i1 -u -b 200M -t999999 @endcode
 *
 *    4) UDP RX:
 *   @code {.c} board# iperf -i1 -u -s @endcode
 *
 * @note
 *  - If the eth0 IP address and the wlan0 IP address are in the same network segment,
 *    the user should disable the eth0 interface using the following command.
 *    Otherwise, if the Ambarella EVK cannot ping through the network, the command is as follows:
 *      @code {.c} board# ifconfig eth0 down @endcode
 *
 */
/*!
 * @file bluetooth.h
 * @date 2021-09-15
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
 * @page si_bluetooth Bluetooth
 *
 * The CV series system on chip (SoC) platform supports Bluetooth by the Universal asynchronous receiver / transmitter (UART) interface.
 *
 * @section bluetooth_with_uart_interface_device 1. Bluetooth with UART Interface Device
 *
 * The CV series SoC platform can support UART BT products. This section details the following:
 * - Broadcom BCM43340 UART BT + 1x1 abgn dual band SDIO WiFi,
 *   refer to @ref wifi_with_sdio_interface
 * - Broadcom BCM43438 UART BT + 1x1 bgn SDIO WiFi,
 *   refer to @ref wifi_with_sdio_interface
 *
 * Build the UART BT driver.
 * @code {.c}
 * build $ make menuconfig_public_linux
 * Device Drivers >
 *   Character devices >
 *     <*> Serial device bus //this config needs be chosen first as to see HCILL protocol config
 *  Networking support >
 *    Bluetooth subsystem support >
 *      Bluetooth device drivers >
 *        <M> HCI UART driver
 *        -*- UART (H4) protocol support
 *        [*] BCSP protocol support
 *        [*] HCILL protocol support
 * @endcode
 *
 * @subsection bluetooth_bcm43340 1.1 BCM43340
 *
 * Select the BT firmware.
 * @par For CV2x SDK 3.0 Amba build
 * @code {.c}
 * build $ make menuconfig
 *   Ambarella Linux Configuration >
 * Ambarella External Linux Configuration >
 *   [*] External WiFi-Bluetooth Configuration
 *     [*] Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *         Broadcom WiFi driver Version (Kernel 3.8, 3.10; Driver 1.88.45.4 (r420671))
 *         Broadcom WiFi Firmware and nvram Version (BCM43340(AP6234))
 * Ambarella File System Configuration >
 *   Network/BlueTooth Packages >
 *     Wireless >
 *       [*] Add Broadcom Wifi firmware and nvram data into root_fs
 * @endcode
 * @par For Cooper Amba build
 * @code {.c}
 * build # make menuconfig
 *    drv_modules --->
 *        external --->
 *           wireless  --->
 *             [*]  kernel-external-module-bcmdhd (drv_modules/external/wireless/broadcom)
 *               [*] Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *               Broadcom WiFi driver Version (Kernel 4.14, 5.4, 5.15; Driver 101.10.361.21 (r892223-20220709-05))  --->
 *               Broadcom WiFi Firmware and nvram Version (BCM43340(AP6234))  --->
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-external --->
 *        recipes-wireless --->
 *           [*] kernel-external-module-bcmdhd (meta-external/recipes-wireless/kernel-module-bcmdhd) --->
 *               [*] Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *               Broadcom WiFi driver Version (Kernel 4.14, 5.4, 5.15; Driver 101.10.361.21 (r892223-20220709-05))  --->
 *               Broadcom WiFi Firmware and nvram Version (BCM43340(AP6234))  --->
 * @endcode
 *
 * @subsection bluetooth_bcm43438 1.2 BCM43438
 *
 * Select the BT firmware.
 * @par For SKD 3.0 Amba build
 * @code {.c}
 * build $ make menuconfig
 *   Ambarella Linux Configuration >
 *     Ambarella External Linux Configuration >
 *       Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *       Broadcom WiFi driver Version (Kernel 3.8, 3.10; Driver 1.88.45.4 (r420671))
 *       Broadcom WiFi Firmware and nvram Version (BCM43438(AP6212))
 *   Ambarella File System Configuration >
 *     Third Party Software / Libraries >
 *       Network/BlueTooth Packages >
 *         Wireless >
 *           [*] Add Broadcom Wifi firmware and nvram data into root_fs
 * @endcode
 * @par For Cooper Amba build
 * @code {.c}
 * build # make menuconfig
 *    drv_modules --->
 *        external --->
 *           wireless  --->
 *             [*]  kernel-external-module-bcmdhd (drv_modules/external/wireless/broadcom)
 *               [*] Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *               Broadcom WiFi driver Version (Kernel 4.14, 5.4, 5.15; Driver 101.10.361.21 (r892223-20220709-05))  --->
 *               Broadcom WiFi Firmware and nvram Version (BCM43438(AP6212))  --->
 * @endcode
 * @par For Cooper Yocto build
 * @code {.c}
 * build # make menuconfig
 *    meta-external --->
 *        recipes-wireless --->
 *           [*] kernel-external-module-bcmdhd (meta-external/recipes-wireless/kernel-module-bcmdhd) --->
 *               [*] Broadcom WiFi SDIO BCM43362/BCM43340/BCM43341/BCM43438
 *               Broadcom WiFi driver Version (Kernel 4.14, 5.4, 5.15; Driver 101.10.361.21 (r892223-20220709-05))  --->
 *               Broadcom WiFi Firmware and nvram Version (BCM43438(AP6212))  --->
 * @endcode
 *
 * - - - -
 *
 * @section bluez_stack 2. Bluez Stack
 *
 * Select the Bluez stack.
 * @code {.c}
 * build $ make menuconfig
 *   Ambarella File System Configuration >
 *     Third Party Software / Libraries >
 *       Network/BlueTooth Packages >
 *         Wireless >
 *           [*] Broadcom firwmare and nvram data
 *           [*] Add Broadcom wireless tools into root_fs
 *
 *  Ambarella File System Configuration >
 *    Third Party Software / Libraries >
 *      Network/BlueTooth Packages->
 *        BlueTooth >
 *          Choose BlueTooth Version (Bluetooth version 5.xx)
 *          [*] Add bluez tools
 *
 *  Ambarella File System Configuration >
 *    Third Party Software / Libraries >
 *      Audio Packages >
 *        PulseAudio
 *          [*] Add PulseAudio utilities into root_fs
 * @endcode
 *
 * @subsection setup_bt_a2dp_profile 2.1 Setup BT A2DP profile
 *
 * 1. Reset `BT_RST_N`<br>
 *   On a reference board, BT_RTS_N connects to GPIO 101, it can be changed according to the hardware.
 *   Otherwise, it can also be reset manually on the BT EVK.
 *   @code {.c}
 *   board # amba_debug -g 101 -d 0x00
 *   board # amba_debug -g 101 -d 0x01
 *   @endcode
 * 2. Load the BT firmware.<br>
 *   BCM43340:
 *   @code {.c}
 *   board # brcm_patchram --tosleep=200000 --no2bytes --enable_hci --baudrate 1500000
 *   --patchram /lib/firmware/broadcom/ap6234/bcm43341b0.hcd /dev/ttyS1 &
 *   @endcode
 *   BCM43438:
 *   @code {.c}
 *   board # brcm_patchram_plus_fake_open /dev/ttyS1
 *   board # brcm_patchram --tosleep=200000 --no2bytes --enable_hci --baudrate 1500000
 *   --patchram /lib/firmware/broadcom/ap6212/BCM4343A0.hcd /dev/ttyS1 &
 *   @endcode
 *   After `brcm_patchrm` is run, the following message will be printed on the console.
 *   @code {.c}
 *   [19826.397450] Bluetooth: Core ver 2.16
 *   [19826.404306] NET: Registered protocol family 31
 *   [19826.411665] Bluetooth: HCI device and connection manager initialized
 *   [19826.418262] Bluetooth: HCI socket layer initialized
 *   [19826.423135] Bluetooth: L2CAP socket layer initialized
 *   [19826.428394] Bluetooth: SCO socket layer initialized
 *   [19826.439956] Bluetooth: HCI UART driver ver 2.2
 *   [19826.444393] Bluetooth: HCI H4 protocol initialized
 *   [19826.449429] Bluetooth: HCI BCSP protocol initialized
 *   [19826.454376] Bluetooth: HCILL protocol initialized Done setting line discipline
 *   @endcode
 * 3. Obtain the bluetooth interface information and make the device discoverable.
 *   @code {.c}
 *   board # hciconfig hci0 up
 *   hci0: Type: BR/EDR Bus: UART
 *         BD Address: 00:22:58:00:C4:42 ACL MTU: 1021:7 SCO MTU: 120:6
 *         UP RUNNING
 *         RX bytes:435 acl:0 sco:0 events:11 errors:0
 *         TX bytes:82 acl:0 sco:0 commands:11 errors:0
 *   00:22:58:00:C4:42 is the Bluetooth device MAC address.
 *   board # hciconfig hci0 piscan
 *   @endcode
 * 4. Scan the bluetooth devices.
 *   @code {.c}
 *   board # hcitool -i hci0 scan
 *   Scanning ...
 *   	00:11:67:00:21:C0 Easy-to-use
 *   	00:1A:7D:11:86:8D n/a
 *   @endcode
 * 5. Establish a connection between the bluetooth board card and bluetooth headset.
 *   @code {.c}
 *   board # bt-device -c <BT Headset Mac>
 *   Connecting to: 00:11:67:00:21:C0
 *   Agent registered
 *   Agent released Done
 *   board # bt-audio -c <BT Headset Mac>
 *   Connecting to an audio service
 *   Audio service is connected.
 *   @endcode
 * 6. Configure PulseAudio of the bluetooth headset.
 *   @code {.c}
 *   board # vi /etc/asound.conf
 *   # device for bluetooth
 *   pcm.bluetooth{
	 *   type bluetooth
	 *   device 00:11:67:00:21:C0
 *   }
 *   @endcode
 *   @note
 *   00:11:67:00:21:C0 is sample BT MAC, change it according to the BT.
 * 7. Play the audio file through the bluetooth headset.
 *   @code {.c}
 *   board # aplay -D bluetooth <sample.wav>
 *   @endcode
 */
/*!
 * @file spi.h
 * @date 2023-03-22
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
 * @page si_spi SPI
 *
 * @section doc_perihperals_spi_introduciton 1 Serial Peripheral Interface Introduction
 *
 * The serial peripheral interface (SPI) is a synchronous, full-duplex serial communication interface
 * used for short-distance communication. SPI uses a master–slave architecture and uses separate clock and data lines,
 * along with a chip select line to choose the device that users wish to talk to.
 *
 * @subsection doc_perihperals_spi_interface 1.1 SPI Interface
 * The SPI bus specifies four logic signals:
 * - SCLK: Serial clock (output from master)
 * - MOSI: Master out, slave in (data output from master)
 * - MISO: Master in, slave out (data output from slave)
 * - CS: Chip / slave select (output from master to indicate that data is being sent)
 * @image html spi_interface_connections.png "Figure 1-1. Connecting Map between SPI Interfaces."
 *
 * @subsection doc_perihperals_spi_mode 1.2 SPI Mode
 * The SPI bus has four modes (0, 1, 2, 3) that correspond to four possible clocking configurations
 * of the clock polarity (CPOL) and the clock phase (CPHA).
 * - <b>Mode 0</b>
 *   - CPOL=0: The clock is idle when low
 *   - CPHA=0: Data is sampled on the leading edge (rising edge) of the clock pulse and
 *     shifted out on the trailing edge (falling edge) of the clock pulse
 * - <b>Mode 1</b>: CPOL=0, CPHA=1
 *   - CPOL=0: The clock is idle when low
 *   - CPHA=1: Data is sampled on the trailing edge (falling edge) of the clock pulse and
 *     shifted out on the leading edge (rising edge) of the next cycle clock pulse
 * - <b>Mode 2</b>: CPOL=1, CPHA=0
 *   - CPOL=1: The clock is idle when high
 *   - CPHA=0: Data is sampled on the leading edge (falling edge) of the clock pulse and
 *     shifted out on the trailing edge (rising edge) of the clock pulse
 * - <b>Mode 3</b>: CPOL=1, CPHA=1
 *   - CPOL=1: The clock is idle when high
 *   - CPHA=1: Data is sampled on the trailing edge (rising edge) of the clock pulse and
 *     shifted out on the leading edge (falling edge) of the next cycle clock pulse
 * @image html spi_mode_introduction.png "Figure 1-2. SPI Mode Introduction."
 *
 *
 * @section doc_perihperals_amba_spi 2 Ambarella SPI
 * CV2x chips provide four SPI masters, provding up to fourteen devices in total,
 * and one decicated slave. While, CV5x chips provide six SPI masters, providing up to
 * sixteen devices in total, and one decicated slave. The SPI interface provides
 * interrupt capability, various transfer modes, and serial master operations.
 * They both provide Motorola interface capability.<br>
 * This chapter describes the setup process of the SPI master and slave on Ambarella systems on chip (SoCs).
 * An Ambarella SoC and one microcontroller unit (MCU) are used for this demo case. The user can also
 * use two Ambarella SoCs to perform such a test by directly connecting their SPI interfaces.
 *
 * @subsection doc_perihperals_spi_master_setup 2.1 SPI Master
 *
 * The baud rate of the SPI master can reach up to 20 MHz. The SPI master can be used
 * to transfer data in full-duplex or half-full duplex mode. Ambarella recommends that
 * users use the SPI mode 3 to transfer data between SPI devices, because SPI mode 3 is
 * fully tested by Ambarella.<br>
 *
 * To set up the SPI master, follow the steps below:<br>
 * 1. Modify `ambarella/boards/<board_name>/bsp/<board_name>.dts` to enable the SPI master.<br>
 *   Use cv25_bigeye for example:
 *   @code {.c}
 *   spi3: spi@e0014000 {
 *     status = "ok";
 *     cs-gpios = <&gpio 16 0>;
 *
 *     spidev@0 {
 *       compatible = "ambarella,spidev";
 *       reg = <0>;
 *       spi-max-frequency = <20000000>;
 *       spi-cpha;
 *       spi-cpol;
 *     };
 *   };
 *   @endcode
 *
 * 2. Add Ambarella SPI driver support in the kernel.
 *
 *   @par For CV2x SDK 3.0 Amba Build:
 *   @code {.c}
 *   build $ make menuconfig_public_linux
 *     Device Drivers  --->
 *       [*] SPI support  --->
 *         <M>   Ambarella SPI Controller
 *         <M>   Ambarella SPI Slave Controller
 *   @endcode
 *
 *   @par For Cooper Amba and Yocto Build:
 *   @code {.c}
 *   build $ make linux_menuconfig
 *     Device Drivers  --->
 *       [*] SPI support  --->
 *         <M>   Ambarella SPI Controller
 *         <M>   Ambarella SPI Slave Controller
 *   @endcode
 *
 * 3. Add the SPI test application into the root file system (Rootfs).
 *   @par For CV2x SDK 3.0 Amba Build:
 *   @code {.c}
 *   build $ make menuconfig
 *     [*] Ambarella Unit Test Configuration  --->
 *       [*]   Ambarella Public Linux Unit test configs  --->
 *         [*]   Build Ambarella Public Linux Misc unit tests
 *   @endcode
 *
 *   @par For Cooper Amba Build:
 *   @code {.c}
 *   build $ make menuconfig
 *     unit_test --->
 *       linux --->
 *         [*] mistools (unit_test/linux/misc)
 *   @endcode
 *
 *   @par For Cooper Yocto Build:
 *   @code {.c}
 *   build $ make menuconfig
 *     meta-ambaapp --->
 *       recipes-linuxtest --->
 *         [*] mistools (meta-ambaapp/recipes-linuxtest/misctools)
 *   @endcode
 *
 * 4. Perform the SPI master test.
 *
 *   - Run the SPI slave test application first on the MCU side.
 *     @code {.c}
 *     MCU # spi_slave_transfer_data 64
 *     fill data [64] cheksum: 0x7a1
 *     frame length: 64
 *     Data received, loop: 1
 *     0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0a
 *     0x0b 0x0c 0x0d 0x0e 0x0f 0x10 0x11 0x12 0x13 0x14
 *     0x15 0x16 0x17 0x18 0x19 0x1a 0x1b 0x1c 0x1d 0x1e
 *     0x1f 0x20 0x21 0x22 0x23 0x24 0x25 0x26 0x27 0x28
 *     0x29 0x2a 0x2b 0x2c 0x2d 0x2e 0x2f 0x30 0x31 0x32
 *     0x33 0x34 0x35 0x36 0x37 0x38 0x39 0x3a 0x3b 0x3c
 *     0x3d 0x3e 0xa1 0x07
 *     @endcode
 *
 *   - Then, load the SPI master driver and run the SPI master test application
 *     on the Ambarella SoC side.
 *     @code {.c}
 *     board # modprobe spi-ambarella
 *     board # test_spi -m 3 -s 12000000 -l64 -c 1 -b 8 -g 106 /dev/spidev3.0
 *     fill data [64] cheksum: 0x7a1
 *     0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08
 *     0x09 0x0a 0x0b 0x0c 0x0d 0x0e 0x0f 0x10
 *     0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18
 *     0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f 0x20
 *     0x21 0x22 0x23 0x24 0x25 0x26 0x27 0x28
 *     0x29 0x2a 0x2b 0x2c 0x2d 0x2e 0x2f 0x30
 *     0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38
 *     0x39 0x3a 0x3b 0x3c 0x3d 0x3e 0xa1 0x07
 *     check point: [0]
 *     @endcode
 *
 *   @note
 *     When using the option `-g`, the SPI master test application can run first
 *     because it can wait for the SPI slave device to be ready to transfer data.
 *
 * @subsection doc_perihperals_spi_slave_setup 2.2 SPI Slave
 *
 * According to the SPI slave Linux driver designed by Ambarella,
 * there are two main points of which users must be aware when using the SPI slave.
 *
 * - One extra general purpose input / output (GPIO) is introduced to inform the SPI master that the
 *   SPI slave is ready and the transfer can be performed,
 *   according to the design of the SPI slave Linux driver.
 * - The maximum clock frequency supported by the SPI slave is 8 MHz.
 *   The user cannot set the clock higher than 8 MHz.<br>
 *
 * The actual transmission speed primarily depends on the size of the SPI transfer buffer and
 * the length of the data being transmitted. The longer the data being transmitted is, within certain limits, the better.<br>
 *
 * To set up the SPI slave, follow the steps below:<br>
 * 1. Modify `ambarella/boards/<board_name>/bsp/<board_name>.dts` to enable the SPI slave.<br>
 *   Take cv25_bigeye for example:
 *   @code {.c}
 *   spi_slave@e0010000 {
 *     status = "ok";
 *     notify-gpio = <&gpio 106 0x1>;
 *     amb,dma-buf-size = <2048>;
 *   };
 *   spi3: spi@e0014000 {
 *     status = "disabled";
 *   };
 *   @endcode
 *
 *   @note
 *     The `spi3` above should be disabled, because `spi3` and `spi slave`
 *     share the same interfaces according to the cv25_bigeye schematic diagram.
 *
 * 2. Add Ambarella SPI slave driver support in the kernel.
 *   @code {.c}
 *   For CV2x SDK 3.0 Amba Build:
 *   build $ make menuconfig_public_linux
 *     Device Drivers  --->
 *       [*] SPI support  --->
 *         <M>   Ambarella SPI Slave Controller
 *   @endcode
 *   @code {.c}
 *   For Cooper Amba Build:
 *   build $ make linux_menuconfig
 *     Device Drivers  --->
 *       [*] SPI support  --->
 *         <M>   Ambarella SPI Slave Controller
 *   @endcode
 *   @code {.c}
 *   For Cooper Yocto Build:
 *   build $ make linux_menuconfig
 *     Device Drivers  --->
 *       [*] SPI support  --->
 *         <M>   Ambarella SPI Slave Controller
 *   @endcode
 *
 * 3. Add the SPI test application into Rootfs.<br>
 *   The SPI slave shares the same test application with the SPI master.
 *   @code {.c}
 *   For CV2x SDK 3.0 Amba Build:
 *   build $ make menuconfig
 *     [*] Ambarella Unit Test Configuration  --->
 *       [*]   Ambarella Public Linux Unit test configs  --->
 *         [*]   Build Ambarella Public Linux Misc unit tests
 *   @endcode
 *   @code {.c}
 *   For Cooper Amba Build:
 *   build $ make menuconfig
 *     unit_test --->
 *       linux --->
 *         [*] mistools (unit_test/linux/misc)
 *   @endcode
 *   @code {.c}
 *   For Cooper Yocto Build:
 *   build $ make menuconfig
 *     meta-ambaapp --->
 *       recipes-linuxtest --->
 *         [*] mistools (meta-ambaapp/recipes-linuxtest/misctools)
 *   @endcode
 *
 *
 * 4. Perform the SPI slave test.
 *   - Configure the SPI master to be triggered by the `notify-gpio` rising edge on the MCU side.<br>
 *     MCU setup is not described in detail in this document.<br>
 *     By detecting the `notify-gpio` rising edge, the MCU SPI master
 *     will start the transfer automatically whenever the SPI slave is ready.
 *   @code {.c}
 *   MCU # spi_transfer_len 64
 *   fill data [64] cheksum: 0x7a1
 *
 *   received len: 64
 *   01 02 03 04 05 06 07 08 09 0a
 *   0b 0c 0d 0e 0f 10 11 12 13 14
 *   15 16 17 18 19 1a 1b 1c 1d 1e
 *   1f 20 21 22 23 24 25 26 27 28
 *   29 2a 2b 2c 2d 2e 2f 30 31 32
 *   33 34 35 36 37 38 39 3a 3b 3c
 *   3d 3e a1 07
 *   @endcode
 *
 *   - Load the SPI slave driver and run the SPI slave test application on the Ambarella SoC side.
 *   @code {.c}
 *   board # modprobe spi-slave-ambarella
 *   [   49.913929] ambarella-spi-slave e0010000.spi_slave: probed
 *   board # test_spi -m 3 -l 64 -c 1 -s 8000000 -b 8 /dev/slavespi
 *   fill data [64] cheksum: 0x7a1
 *   0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08
 *   0x09 0x0a 0x0b 0x0c 0x0d 0x0e 0x0f 0x10
 *   0x11 0x12 0x13 0x14 0x15 0x16 0x17 0x18
 *   0x19 0x1a 0x1b 0x1c 0x1d 0x1e 0x1f 0x20
 *   0x21 0x22 0x23 0x24 0x25 0x26 0x27 0x28
 *   0x29 0x2a 0x2b 0x2c 0x2d 0x2e 0x2f 0x30
 *   0x31 0x32 0x33 0x34 0x35 0x36 0x37 0x38
 *   0x39 0x3a 0x3b 0x3c 0x3d 0x3e 0xa1 0x07
 *   check point: [0]
 *   @endcode
 *
 *   @note
 *     The example above is a demo case. Users can run the SPI slave test application first,
 *     and then run the SPI master test application according to their demands.
 *
 */
/*!
 * @file i2c.h
 * @date 2022-06-20
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
 * @page si_i2c I2C
 *
 * This section describes how to support the Inter-Integrated Circuit (I2C) bus slave mode.
 *
 * <B>I2C interface errata</B><br>
 * Ambarella has observed a glitch with I2C (IDC) signals due to fast transition and long
 * printed circuit board (PCB) traces, especially for single-load use cases. The glitch typically occurs when the signal
 * transitions from low to high. A glitch on the serial clock (SCK) can be problematic, as it may appear as an incorrect
 * clock. <br>
 * As a workaround, Ambarella suggests adding a RC filter on the SCL / serial data (SDA) signal. An option is to add
 * a 100-ohm series resistor and a 100pF capacitor (single I2C device on the bus). Depending on the load,
 * use a smaller capacitance value, especially if there are multiple devices on the same bus. This issue
 * exists for both I2C master and slave configurations. <br>
 * @image html errata_I2C_Interface_connecting.png "I2C Interface Connection"
 *
 *
 * <B>Enable I2C slave mode steps</B><br>
 * 1. Configure the device trees (DTS) node.
 * For example, find kernel/linux-5.4/arch/arm64/boot/dts/ambarella/ambarella-cv2.dtsi, and modify the I2CS node.
 * @code {.c}
 * i2cs: i2cs@e4007000 {
 *        compatible = "ambarella,i2cs";
 *        #address-cells = <1>;
 *        #size-cells = <0>;
 *        reg = <0xe4007000 0x1000>;
 *        interrupts = <0 19 0x4>;
 *        clocks = <&gclk_apb>;
 *        pinctrl-names = "default";
 *        pinctrl-0 = <&i2cs0_pins>;
 *        status = "ok";
 *        slave-24c02@62{
 *             compatible = "slave-24c02";
 *             reg = <0x40000062>;
 *        };
 * };
 * @endcode
 * 2. Select the I2C slave controller before building the firmware. Enable I2C slave mode in the
 * Linux kernel along with the module that simulates the EEPROM.
 * @par For CV2x SDK 3.0 Amba build:
 * @code {.c}
 * build $ make menuconfig_public_linux
 *       Device Drivers >
 *         [*] I2C support >
 *             I2C Hardware Bus support >
 *               <*> Ambarella Media Soc I2C bus support
 *               <M> Ambarella Media Soc I2C Slave
 *         [*] I2C slave support >
 *               <M>  I2C eeprom slave driver
 * (Enter spacebar to select this item and then exit by saving.)
 * @endcode
 *
 * @par For Cooper Amba build:
 * @code {.c}
 * build $ make linux_menuconfig
 *       Device Drivers >
 *         [*] I2C support >
 *             I2C Hardware Bus support >
 *               <*> Ambarella Media Soc I2C bus support
 *               <M> Ambarella Media Soc I2C Slave
 *         [*] I2C slave support >
 *               <M>  I2C eeprom slave driver
 * (Enter spacebar to select this item and then exit by saving.)
 * @endcode
 *
 * @par For Cooper Yocto build:
 * @code {.c}
 * build $ make linux_menuconfig
 *       Device Drivers >
 *         [*] I2C support >
 *             I2C Hardware Bus support >
 *               <*> Ambarella Media Soc I2C bus support
 *               <M> Ambarella Media Soc I2C Slave
 *         [*] I2C slave support >
 *               <M>  I2C eeprom slave driver
 * (Enter spacebar to select this item and then exit by saving.)
 * @endcode
 * 3. Boot up the board.
 * @code {.c}
 * board # modprobe i2c-slave-eeprom
 * @endcode
 */

/*!
 * @file pci_express.h
 * @date 2021-09-15
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
 * @page pci_express PCI Express
 *
 * Ambarella systems on chip (SoCs) CV5 and CV72 include one Gen3x4 dual-mode controller, and CV3 includes
 * three Gen3x4 dual-mode controllers. CV3 includes one Gen5x4 dual-mode controller and two Gen5x1 dual-mode controllers.
 *
 * Devices such as Ethernet cards and non-volatile memory express (NVMe) disks can be connected to
 * the system via peripheral component interconnect express (PCIe) ports.
 * ![NVMe example](pci_express_nvme_ssd_port.png)
 * The CV5 Timn evaluation kit (EVK) has a dedicated NVMe solid-state drive (SSD) slot for SSD disks.
 * Other general PCIe devices can be connected to the system using the general PCIe ports on the top side of the EVK board.
 * All of Ambarella's PCIe controllers can function as either a root complex (RC) or an endpoint (EP),
 * but only one mode can be active at a time, and cannot be switched during runtime.
 * For more details on the endpoint function (EPF), refer to the `Documentation/arm/ambarella/`
 * directory within the Linux kernel source tree.
 *
 * # Regular Endpoint Devices
 *
 * ## nvme_ssd NVMe SSD
 *
 * Some drivers for PCIe Ethernet are already in the kernel. The two drivers below are selected by default.
 *
 *     build $ make cv5_ipcam_config
 *     build $ make menuconfig
 *             Ambarella Boot Configuration  --->
 *               Amboot Configuration  --->
 *                 Hardware Options  --->
 *                   [*] Support PCIE Driver  --->
 *                     PCIE Mode (RC)
 *     build $ make defconfig_public_linux
 *     build $ make menuconfig_public_linux
 *             Device Drivers  --->
 *               NVMe support  --->
 *                 <M> NVM Express block device
 *
 * If NVMe SSD is not automatically loaded, users can enable it using the command below.
 *
 *     board # modprobe nvme
 * The following is the performance of NVMe SSD on the CV5 EVK:
 * - Read: 3432.9 MB/s
 * - Write: 2754.5 MB/s
 *
 * - - - -
 *
 * ### Throughput Result
 *
 * Test command:
 * - fio -direct=1 -iodepth=128 -rw=write -ioengine=libaio -bs=128k -numjobs=1 -time_based=1 -runtime=10 -group_reporting -filename=/dev/nvme0n1 -name=test
 * - fio -direct=1 -iodepth=128 -rw=write -ioengine=libaio -bs=128k -numjobs=1 -time_based=1 -runtime=10 -group_reporting -filename=/dev/nvme0n1 -name=test
 *
 * |  Read Throughput  | Write Throughput  |  DDR Frequency  | Lane Number  |   NVMe Model   | SoC / Board   |
 * | ------------------| ----------------  | ---------- | --------- | -------------- | -------------- |
 * | 3261 MB/s         | 2418 MB/s         | 3.192 G    |    4      | Samsung 980    | CV5            |
 * | 3467 MB/s         | 2416 MB/s         | 3.192 G    |    4      | Samsung 970    | CV5            |
 * | 844 MB/s          | 793 MB/s          | 3.192 G    |    1      | Samsung 970    | CV72 (Gage)    |
 * | 845 MB/s          | 807 MB/s          | 3.192 G    |    1      | Samsung 970    | CV72 (Xiezhi)  |
 *
 * ## GPU AMD ATI GPU
 *
 * At present, CV72 is the only platform capable of supporting PCIe graphics processing units (GPUs) due to its
 * extensive advanced extensible interface (AXI) memory space for PCIe. This feature is crucial for most GPUs, as they
 * typically require at least 256 MB of 64-bit prefetchable memory space.
 *
 * Ambarella has tested AMD RV620 PRO [Radeon HD 3470] on CV72:
 *
 *     Graphics:
 *     Device-1: AMD RV620 PRO [Radeon HD 3470] driver: radeon v: kernel
 *      Display: x11 server: X.org v: 1.20.14 with: Xwayland v: 22.1.9 driver: X: loaded: radeon
 *       unloaded: fbdev,modesetting dri: swrast gpu: radeon tty: 237x61 resolution: 1920x1080-60Hz
 *     Application programming interface (API): OpenGL v: 4.5 Mesa 23.0.3 renderer: llvmpipe (LLVM 15.0.7 128 bits)
 *
 * As shown above, the Radeon driver is employed in this case. However, if users possess other ATI
 * cards that are compatible with amdgpu, Ambarella recommends using them instead. The amdgpu driver
 * offers more advanced memory management features, such as GTT support.
 *
 * ### Troubleshooting
 *
 * #### The video random-access memory (VRAM) is too large:
 *
 * The GPU may require a large amount of VRAM space, which is beyond the amount of Ambarella SoC PCIe AXI space that is supported:
 *
 * ```
 *     [   14.993326] pcieport 0000:00:00.0: BAR 15: no space for [mem size 0x300000000 64bit pref]
 *     [   15.005583] pcieport 0000:00:00.0: BAR 15: failed to assign [mem size 0x300000000 64bit pref]
 *     [   15.015590] amdgpu 0000:01:00.0: BAR 0: no space for [mem size 0x200000000 64bit pref]
 *     [   15.024950] amdgpu 0000:01:00.0: BAR 0: failed to assign [mem size 0x200000000 64bit pref]
 *     [   15.033368] amdgpu 0000:01:00.0: BAR 2: no space for [mem size 0x00200000 64bit pref]
 *     [   15.041335] amdgpu 0000:01:00.0: BAR 2: failed to assign [mem size 0x00200000 64bit pref]
 *     [   15.097912] [drm] Not enough PCI address space for a large BAR.
 *     [   15.097933] amdgpu 0000:01:00.0: BAR 0: assigned [mem 0xfe20000000-0xfe2fffffff 64bit pref]
 *     [   15.112403] amdgpu 0000:01:00.0: BAR 2: assigned [mem 0xfe18000000-0xfe181fffff 64bit pref]
 *     [   15.140949] [drm] Detected VRAM RAM=8192M, BAR=256M
 * ```
 *
 * For this case, users should limit VRAM by adding "vis_vramlimit=512 vramlimit=512 gartsize=128 gttsize=512" to the kernel commandline;
 * however, this is not sufficient because it only limits VRAM usage and would still require 8192 M. Therefore, users should disable bar resize:
 * ```
 *     modified   drivers/gpu/drm/amd/amdgpu/gmc_v8_0.c
 *     @@ -572,11 +572,11 @@ static int gmc_v8_0_mc_init(struct amdgpu_device *adev)
 *              adev->gmc.mc_vram_size = tmp * 1024ULL * 1024ULL;
 *              adev->gmc.real_vram_size = adev->gmc.mc_vram_size;
 *
 *     -        if (!(adev->flags & AMD_IS_APU)) {
 *     -                r = amdgpu_device_resize_fb_bar(adev);
 *     -                if (r)
 *     -                        return r;
 *     -        }
 *     +        //if (!(adev->flags & AMD_IS_APU)) {
 *     +        //     r = amdgpu_device_resize_fb_bar(adev);
 *     +        //     if (r)
 *     +        //             return r;
 *     +        //}
 * ```
 *
 * Note that if the amdgpu driver used is not gmc_v8_0.c, users should remove the bar resize function in the correct gmc_vN_M.c.
 *
 * #### Ring Test Failed
 *
 * If users encounter error messages such as `*ERROR* ring gfx test failed (-110)` or `*ERROR* radeon: ring 0 test failed`, there is an
 * issue with reading or writing to the ring buffer (also known as the GPU's command buffer). The specific cause of these errors can vary
 * depending on the platform and other factors, such as support for ExtTag by the upstream switch.
 * For the Ambarella platform, this issue arises due to a limitation with the Cadence Gen3 PCIe controller. This controller does not permit variations
 * from its maximum `pcie_master_AXI_ARSIZE` value of four, unless `pcie_master_AXI_ARLEN` is zero in a request.
 * This means that, if users must read or write (memory-mapped input / output (MMIO)) to the endpoint's bar, they are required to use writel / readl operations.
 * The use of `memcpy / memcpy_to / fromio / readq / writeq` operations is not allowed under these circumstances.
 *
 * At present, the `radeon / amdgpu` driver uses the `memcpy_toio / memcpy_fromio` functions for the ring buffer. To address this issue, these functions
 * should be replaced with the 32-bit version of `memcpy`. Users can easily implement this change by applying the modifications found in
 * [Coreforge's PR] (https://github.com/Coreforge/linux/pull/1/commits), which introduces the 32-bit `memcpy`. Alternatively, users can utilize
 * the `memcpy_fromio_ambarella` function that the Ambarella kernel provides.
 *
 * It is important to note that this limitation does not only impact kernel space drivers; updates to memcpy in the userspace are also necessary.
 * The `GLIBC`'s `memcpy` for `aarch64` is implemented in assembly and uses single instruction / multiple data (SIMD) `stp/ldp` operations where possible. A solution could be to implement
 * a version of memcpy that copies four-byte chunks at one time, similar to how `memcpy_fromio_ambarella` functions. An example of how to perform this operation
 * can be found in this Stack Overflow post: https://stackoverflow.com/a/11876613/6949852.
 * ```
 * void memcpy(void* dest, void* src, int size)
 * {
 *     uint8_t *pdest = (uint8_t*) dest;
 *     uint8_t *psrc = (uint8_t*) src;
 *
 *     int loops = (size / sizeof(uint32_t));
 *     for(int index = 0; index < loops; ++index)
 *     {
 *         *((uint32_t*)pdest) = *((uint32_t*)psrc);
 *         pdest += sizeof(uint32_t);
 *         psrc += sizeof(uint32_t);
 *     }
 *
 *     loops = (size % sizeof(uint32_t));
 *     for (int index = 0; index < loops; ++index)
 *     {
 *         *pdest = *psrc;
 *         ++pdest;
 *         ++psrc;
 *     }
 * }
 * ```
 *
 * To compile the shared library, use the following flags: `-fPIC -g -fno-inline -fno-builtin-inline -fno-inline-functions -fno-builtin -shared`.
 * Users can test this library by using the `LD_PRELOAD="./libmemcpy.so"` command, followed by the user application. Alternatively, users can make the library
 * globally available by adding its full path to the `/etc/ld.so.preload` file.
 *
 * As pointed above, it is the Ambarella controller's limition, but only the GPU driver requires this change because drivers, such as NVMe, have performed similar
 * changes in https://github.com/torvalds/linux/commit/a310acd7a7ea53533886c11bb7edd11ffd61a036. The commit changes how
 * NVMe storage devices are managed by the kernel, specifically in relation to how 64-bit `read / write` operations are managed.
 * The commit modifies the kernel's NVMe driver to use "split" `read / write` operations for certain storage controllers that may require ordered split
 * transfers, even on 64-bit machines. This includes, for example, the NVMe controller found in certain models of Apple™'s MacBook™. The commit changes
 * several instances in the code where `readq` and `writeq` functions were used, to instead use `lo_hi_readq` and `lo_hi_writeq` respectively. These changes
 * should ensure ordered split transfers on 64-bit platforms, which helps avoid potential issues with the aforementioned controllers.
 *
 * Users are not required to modify the NVMe driver. If desired, users can attempt to undo the changes made by the commit using the following method:
 * ```
 * modified   drivers/nvme/host/pci.c
 * @@ -1755,8 +1755,8 @@ static int nvme_pci_configure_admin_queue(struct nvme_dev *dev)
 *          aqa |= aqa << 16;
 *
 *          writel(aqa, dev->bar + NVME_REG_AQA);
 * -        lo_hi_writeq(nvmeq->sq_dma_addr, dev->bar + NVME_REG_ASQ);
 * -        lo_hi_writeq(nvmeq->cq_dma_addr, dev->bar + NVME_REG_ACQ);
 * +        writeq(nvmeq->sq_dma_addr, dev->bar + NVME_REG_ASQ);
 * +        writeq(nvmeq->cq_dma_addr, dev->bar + NVME_REG_ACQ);
 *
 *          result = nvme_enable_ctrl(&dev->ctrl);
 *          if (result)
 * @@ -2501,7 +2501,7 @@ static int nvme_pci_enable(struct nvme_dev *dev)
 *          if (result < 0)
 *                  return result;
 *
 * -        dev->ctrl.cap = lo_hi_readq(dev->bar + NVME_REG_CAP);
 * +        dev->ctrl.cap = readq(dev->bar + NVME_REG_CAP);
 *
 *          dev->q_depth = min_t(u32, NVME_CAP_MQES(dev->ctrl.cap) + 1,
 *                                  io_queue_depth);
 * @@ -2868,7 +2868,7 @@ static int nvme_pci_reg_write32(struct nvme_ctrl *ctrl, u32 off, u32 val)
 *
 *  static int nvme_pci_reg_read64(struct nvme_ctrl *ctrl, u32 off, u64 *val)
 *  {
 * -        *val = lo_hi_readq(to_nvme_dev(ctrl)->bar + off);
 * +        *val = readq(to_nvme_dev(ctrl)->bar + off);
 *          return 0;
 *  }
 * ```
 *
 * Users will then notice that the NVMe controller ceases to function properly:
 * ```
 * nvme nvme0: pci function 0000:05:00.0
 * nvme 0000:05:00.0: enabling device (0000 -> 0002)
 * sdhci: Secure Digital Host Controller Interface driver
 * sdhci: Copyright(c) Pierre Ossman
 * irq 48: nobody cared (try booting with the "irqpoll" option)
 * CPU: 0 PID: 197 Comm: kworker/u4:2 Tainted: G           O      5.15.108-rt61 #2
 * Hardware name: Ambarella CV5 TIMN Board (DT)
 * Workqueue: events_unbound async_run_entry_fn
 * Call trace:
 * ...
 * nvme nvme0: I/O 16 QID 0 timeout, disable controller
 * nvme nvme0: Device shutdown incomplete; abort shutdown
 * nvme nvme0: Identify Controller failed (-4)
 * nvme nvme0: Removing after probe failure status: -5
 * ```
 *
 * Users can also utilize the Ambarella `pci-amba-test` to validate the presence of this issue:
 * ```
 * modified   drivers/misc/pci_endpoint_amba_test.c
 * @@ -154,18 +154,18 @@ pci_endpoint_amba_test_writel(struct pci_endpoint_amba_test *test, u32 offset,
 *  	writel(value, test->base + offset);
 *  }
 *
 * -static inline u32
 * -pci_endpoint_amba_test_bar_readl(struct pci_endpoint_amba_test *test, int bar,
 * +static inline u64
 * +pci_endpoint_amba_test_bar_readq(struct pci_endpoint_amba_test *test, int bar,
 *  				 int offset)
 *  {
 * -	return readl(test->bar[bar] + offset);
 * +	return readq(test->bar[bar] + offset);
 *  }
 *
 *  static inline void
 * -pci_endpoint_amba_test_bar_writel(struct pci_endpoint_amba_test *test, int bar,
 * -				  u32 offset, u32 value)
 * +pci_endpoint_amba_test_bar_writeq(struct pci_endpoint_amba_test *test, int bar,
 * +				  u32 offset, u64 value)
 *  {
 * -	writel(value, test->bar[bar] + offset);
 * +	writeq(value, test->bar[bar] + offset);
 *  }
 *
 *  static irqreturn_t pci_endpoint_amba_test_irqhandler(int irq, void *dev_id)
 * @@ -288,7 +288,7 @@ static bool pci_endpoint_amba_test_bar(struct pci_endpoint_amba_test *test,
 *  				       enum pci_barno barno)
 *  {
 *  	int j;
 * -	u32 val;
 * +	u64 val;
 *  	int size;
 *  	struct pci_dev *pdev = test->pdev;
 *
 * @@ -301,11 +301,11 @@ static bool pci_endpoint_amba_test_bar(struct pci_endpoint_amba_test *test,
 *  		size = 0x4;
 *
 *  	for (j = 0; j < size; j += 4)
 * -		pci_endpoint_amba_test_bar_writel(test, barno, j, 0xA0A0A0A0);
 * +		pci_endpoint_amba_test_bar_writeq(test, barno, j, 0xA0A0A0A0A0A0A0A0);
 *
 *  	for (j = 0; j < size; j += 4) {
 * -		val = pci_endpoint_amba_test_bar_readl(test, barno, j);
 * -		if (val != 0xA0A0A0A0)
 * +		val = pci_endpoint_amba_test_bar_readq(test, barno, j);
 * +		if (val != 0xA0A0A0A0A0A0A0A0)
 *  			return false;
 *  	}
 *  ```
 *  When running `amba-pcitest -b 0`, users can see the following:
 *  ```
 *  # amba-pcitest -b 0
 *  BAR0            NOT OKAY
 *  ```
 * This also implies that attempts to access the 64-bit bar will be unsuccessful.
 *
 * ## PCIe Ethernet:
 *
 * Some drivers for PCIe Ethernet are already in the kernel. The two drivers below are selected by default.
 *
 * ```
 *     build $ make cv5_ipcam_config
 *     build $ make defconfig_public_linux
 *     build $ make menuconfig_public_linux
 *            Device Drivers  --->
 *              [*] Network device support  --->
 *                [*]   Ethernet driver support  --->
 *                   [*]   aQuantia devices
 *                   <M>     aQuantia AQtion(tm) Support
 *                   [*]   Intel devices
 *                   <M>     Intel(R) 10GbE PCI Express adapters support
 * ```
 *
 * After building the binary and flashing it to the EVK board, the command below can be used to enable the hardware.
 * - Intel® PCIe Ethernet card
 *
 *     board # modprobe ixgbe InterruptThrottleRate=1 IntMode=0
 *
 * - Marvel PCIe Ethernet card
 *     board # modprobe atlantic aq_itr=1
 *
 * The table below provides PCIe Ethernet performance data:
 * <table>
 * <tr><th> <div style="width:240px"><B>Connection</B></div>
 * <th> <div style="width:240px"><B>Throughput (Gbits/s)</B></div>
 * <tr><td> PC <-> CV5 Timn
 *     <td> 9.38
 * <tr><td> CV5 Timn <-> CV5 Timn
 *     <td> 3.71
 * </table>
 * <br>
 *
 * # RC mode:
 *
 * Users can refer to [Wikipedia] (https://www.wikiwand.com/en/Root_complex) for details.
 *
 * ## Troubleshooting:
 *
 * ### RC often gets hung when read / write endpoints' BAR / CFG
 *
 * If users are testing a new board with a PCIe controller acting as either an RC or EP, and you
 * encountered the issue mentioned in the title, ensure that the signal lengths of the PCIe
 * connector's P and N are the same. If they are different, prioritize fixing this issue by
 * replacing the connector with one which has the same length.
 *
 * ### Downstream EP devices cannot be recongized or are not functioning:
 *
 * -   If using a CV5 / CV52 EVK, verify that the PCIe switch is attached to the board.
 *
 *  ![switch](switch.jpg)
 *
 * -   If the PCIe switch does not exist, enable
 *     CONFIG\_AMBOOT\_PCIE\_MODE\_RC\_QUIRK(CONFIG\_AMBOOT\_PCIE0/1/2\_MODE\_RC\_QUIRK
 *     for CV3) under the Ambarella software development kit (SDK).
 * -   If the steps above do not resolve the issue, check the PCIe status register.
 *     PCIe status reg:
 *     -   CV5: devmem 0x20e0024198
 *     -   CV3:
 *         -   PCIe0: devmem 0xffe00241ac
 *         -   PCIe1: devmem 0xffe00241b0
 *         -   PCIe2: devmem 0xffe00241b4
 *     -   CV72: devmem 0xffe003e1ac
 *
 * If all values are 0, verify that the PCIe controller driver has been probed.
 * In SDK 2.0, the CV52 PCIe has not been checked because its compatible is "cdns,cdns-pcie-host",
 * but the driver uses "ambarella,cdns-pcie-host". As a result, the driver is not probed and the
 * register receives all 0 values. Update the compatible to "ambarella,cnds-pcie-host" and try again.
 *
 * Get bit \[3:2\]. If the value is not 0b11 (linkup completed), it indicates that the controller
 * linkup has not succeeded. It is possible that some SoC pins are broken.
 * Some CV5 boards have this issue; if so, request a new CV5 board.
 *
 * If the status register is functional, verify that the PCIe slot powers on. For example, the CV5 EVK uses a PCA953x
 * GPIO 6 for slot power control. If the user's GPIO setting is incorrect, and the slot does not have power,
 * the endpoint cannot be recongized.
 *
 * # EP mode:
 *
 * Ambarella's PCIe controller can function as a regular endpoint.
 *
 * ### As an EP, rework is required.
 *
 * #### CV3 and CV5:
 *
 * For the CV3 bring-up board (BUB): pull up U38.47 to SYS\_VCC1V8 with 10 K. Pull up U38.46 to
 * SYS\_VCC1V8 with 10 K. Pull up U38.44 to SYS\_VCC1V8 with 10 K.
 *
 * For the CV5 BUB:
 *
 * 1. Pull up U60.pin37 (PCIE\_PERST\_N) to SYS\_VCC1V8 with 10 K.
 * 2. The CV5 BUB default is as follows: (R59,R61 is fitted and R62,R63 is removed). (XXX:
 *     this step should only be required if the PC is the root complex).
 *
 *    Remove R86, R88, R87, and R90, then wire two lines as shown in the pictures below to the user's external clock from the PCIe connector:
 *    ![cv5 ep.png](cv5_ep_01.png)
 *    ![cv5 ep.png](cv5_ep_02.png)
 *
 * ### CV72 EP Mode:
 *
 * If users set up the EP (CV72) after the RC boots up (which is the recommended method), they can ignore this section. 
 * The rest of this section is only for situations where the EP is configured before RC bootup.
 *
 * Unlike CV3 / CV5, the CV72 EVK does not include level shift. Perst is asserted when the RC links up and some registers,
 * such as the EP trans IB register, are cleared.
 *
 * To fix this issue, Perst must be disabled. This can be performed,
 * for example, by removing R1125 from the CV72 EVK. Note that with this rework,
 * if CV72 functions as an RC, the endpoints may malfunction due to missing fundmental resets. For example, NVMe will receive a timeout when reading / writing.
 *
 * Users should only disable Perst (remove R1125 or add a diode) when CV72 functions as an EP and configures its EPF before RC bootup.
 *
 * ## Rework may be required if a PC is used as the RC.
 *
 * If the user wants to use a PC as the RC and the Ambarella chip's PCIe controller as the EP, the EP must use the RC's clock source.
 * To find the root cause, users can refer to [here](xxx/arm/ambarella/pci/verify-soc-interconnect-via-pci.html).
 *
 * ### CV3:
 *
 * CV3 integrates three PCIe controllers: PCIe0, PCIe1, and PCIe2. To configure the connections for the BUB's PCIe2, follow the steps below:
 * 1. Disconnect resistors R411, R413, R414, and R415.
 * 2. Connect the A13 and A14 pins on the PCIe2 connector (PCIe Port-2) to CV3:
 *  * Connect A13 to the PCIEP2_CK_REFREFCLK_P clock.
 *  * Connect A14 to the PCIEP2_CK_REFREFCLK_N clock.
 * Refer to the images below for more information.
 * ![cv3 pcie2 external refclk](cv3_pcie2_external_refclk0.png)
 * ![cv3 pcie2 external refclk](cv3_pcie2_external_refclk.png)
 *
 * For PCIe0, follow the steps below to modify the connections:
 * 1. Disconnect resistors R401, R402, R403, and R405.
 * 2. Connect the A13 and A14 pins on the PCIe0 connector (PCIe Port-0) to CV3:
 *  * Connect A13 to the PCIEP0_REFCLK_P (R401) clock.
 *  * Connect A14 to the PCIEP0_REFCLK_N (R402) clock.
 *
 * For PCIe1, follow the steps below to modify the connections:
 * 1. Disconnect R406, R407, R408, and R409.
 * 2. Connect the A13 and A14 pins on the PCIe1 connector (PCIe Port-1) to CV3:
 *  * Connect A13 to the PCIEP1_REFCLK_P (R406) clock.
 *  * Connect A14 to the PCIEP1_REFCLK_N (R407) clock.
 *
 * @note
 * When connecting the reference clock, ensure that it is connected to the
 * end of the original resistor that is furthest from the clock chip:
 * <img src="this_side.jpg" title="this_side.jpg" width="500" />
 *
 * ### CV72:
 *
 * CV72 EVK (Ga):
 * ![cv72 ep connector clock](cv72_ep_connector_clock.png)
 * ![cv72 ep connector clock](cv72_ep_connector_clock2.png)
 *
 * ### CV5:
 *
 * CV5 performs similar rework to CV3 / CV72.
 *
 * # Use I2C to read / write the clock generator on the board.
 *
 * @note
 * The clock generator is located on the board rather than on the chip.
 *
 * -   All Shanghai EVKs can use I2C to read / write the clock generator / PCIe switch, for example, to
 *     disable the clock.
 * -   Taiwan CV72 and CV5 BUBs have no such support.
 *
 * The Taiwan CV3 BUB supports I2C clock generator read / write.
 *
 * # Disable unused lanes:
 *
 * Users may have a variety of reasons for preferring to use a single lane, even if the SoC provides four PCIe lanes.
 * For instance, in certain cases, users may only require single-lane throughput for specific applications,
 * such as serial adanced technology attachment (SATA) controllers.
 *
 * ## AMBoot:
 *
 * ```
 *     From 612aa5a822429c0160210b5741e0d39d0e3b30f0 Mon Sep 17 00:00:00 2001
 *     From: Li Chen <lchen@ambarella.com>
 *     Date: Wed, 9 Mar 2022 17:23:26 +0800
 *     Subject: [PATCH] limit PCIe controller's lane to single
 *
 *     Signed-off-by: Li Chen <lchen@ambarella.com>
 *     Change-Id: I93cef1542f444b700352be0c9ac7631b7d6160ca
 *     ---
 *      src/bld/main.c | 20 ++++++++++++++++++++
 *      1 file changed, 20 insertions(+)
 *
 *     diff --git a/src/bld/main.c b/src/bld/main.c
 *     index 4251c899..920ce073 100644
 *     --- a/src/bld/main.c
 *     +++ b/src/bld/main.c
 *     @@ -57,6 +57,24 @@ static const char *AMBOOT_LOGO =						\
 *
 *     +#include <ambhw/pcie.h>
 *     +#include <ambhw/idc.h>
 *     +void limit_pcie_lane_to_single()
 *     +{
 *     +	u32 tmp = 0;
 *     +	pca9539_set_gpio(IDC3, EXGPIO6_PCIESLOT_PWERON, 0);
 *     +	pca9539_set_gpio(IDC3, EXGPIO5_PCIECLK_EN, 0);
 *     +
 *     +	tmp = readl(PCIEC_CTRL1_REG) & (~(1 << 19)) & (~(1 << 20));
 *     +	writel(PCIEC_CTRL1_REG, tmp);
 *     +
 *     +	pca9539_set_gpio(IDC3, EXGPIO6_PCIESLOT_PWERON, 1);
 *     +	pca9539_set_gpio(IDC3, EXGPIO5_PCIECLK_EN, 1);
 *     +
 *     +	tmp = readl(PCIEC_STATUS_REG);
 *     +	printf("pcie link width: 0x%x%x", tmp & (1 << 5), tmp & (1 << 4));
 *     +}
 *     +
 *      int main(void)
 *      {
 *      	u32 recovery_mode = (amboot_recovery_boot[0] == BAKFW_MAGIC);
 *     @@ -78,6 +96,8 @@ int main(void)
 *
 *      	watchdog_init();
 *
 *     +	limit_pcie_lane_to_single();
 *     +
 *      #if defined(AMBOOT_DEV_USBDL_MODE)
 *      	usb_boot();
 *
 *     --
 *     2.35.1
 * ```
 *
 *
 * ## Linux kernel:
 *
 * ```
 *     --- a/drivers/phy/cadence/phy-cadence-torrent.c
 *     +++ b/drivers/phy/cadence/phy-cadence-torrent.c
 *     @@ -222,6 +222,7 @@
 *
 *      /* PHY PCS common registers */
 *      #define PHY_PIPE_CMN_CTRL1		0x0000U
 *     +#define PHY_PIPE_LANE_DSBL		0x0005U
 *      #define PHY_PLL_CFG			0x000EU
 *      #define PHY_PIPE_USB3_GEN2_PRE_CFG0	0x0020U
 *      #define PHY_PIPE_USB3_GEN2_POST_CFG0	0x0022U
 *     @@ -1939,6 +1940,10 @@ static int cdns_torrent_phy_init(struct phy *phy)
 *      	 */
 *      	regmap = cdns_phy->regmap_phy_pcs_lane_cdb[inst->mlane];
 *      	regmap_write(regmap, 0x0013U, 0x1111);
 *     +
 *     +    regmap = cdns_phy->regmap_phy_pcs_common_cdb;
 *     +	regmap_write(regmap, 0x0005U, 0xFE);// only enable lane 0
 *     +    //regmap_write(regmap, 0x0005U, 0xFC);// enable lane 0 and 1
 *      #endif
 *
 *     index 59060c2101fe7..a532ce93a28dd
 *     --- a/drivers/reset/reset-amba-cdns-phy.c
 *     +++ b/drivers/reset/reset-amba-cdns-phy.c
 *     @@ -39,6 +39,8 @@
 *      #define PCIEC_APB_CORE_RATIO_4			(4 << 9)
 *      #define PCIEC_APB_CORE_RATIO_MASK		GENMASK(13, 9)
 *      #define PCIEC_MISC_RESET			GENMASK(7, 0)
 *     +#define PCIEC_GEN_RESET			GENMASK(18, 17)
 *     +#define PCIEC_LANE_RESET			GENMASK(20, 19)
 *
 *      enum {
 *      	PMA_CTRL_REG = 0,
 *     @@ -97,6 +99,8 @@ static int amba_phyrst_pcie_deassert(struct reset_controller_dev *rcdev, unsigne
 *      	case CDSN_PHY_LINK_RESET:
 *      		break;
 *      	case CDSN_PHY_RESET:
 *     +        regmap_clear_bits(phyrst->regmap, phyrst->offset[C_CTRL_REG], PCIEC_GEN_RESET);
 *     +        regmap_clear_bits(phyrst->regmap, phyrst->offset[C_CTRL_REG], PCIEC_LANE_RESET);
 *      		regmap_clear_bits(phyrst->regmap, phyrst->offset[P_CTRL_REG], PCIEP_PHY_RESET(phy_id));
 *      		regmap_clear_bits(phyrst->regmap, phyrst->offset[C_CTRL_REG], PCIEC_MISC_RESET);
 *      		regmap_set_bits(phyrst->regmap, phyrst->offset[C_CTRL_REG], PCIEC_LINK_TRAIN_EN);
 * ```
 *
 *
 * Users can check the PCIe status register to see if the lanes are limited to a single lane, using CV5 for an example:
 *     devmem 0x20e0024198
 * - if BIT(5:4) is 0b00 -> x1
 * - if BIT(5:4) is 0b01 -> x2
 * - if BIT(5:4) is 0b10 -> x4
 *
 * # Utilizing Alternate General Purpose Input / Output (GPIO) for Power Provision
 *
 * **Depending on the specific board design**, it may be necessary to supply power to the slot during the PCIe
 * controller boot-on process. This can be verified within AMBoot, for instance, if users are utilizing GPIO 68 to manage the
 * power for the slot.
 * ```
 * amboot> gpio hw 68 0 # operate exclusively as a GPIO, instead of repurposing it for alternative functions
 * amboot> gpio set 68 # pull up
 * ```
 */
/*!
 * @file ethernet.h
 * @date 2021-09-15
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
 * @page si_ethernet Ethernet
 *
 * CV5x / CV7x include two Gigabit (Gbit) Ethernet ports, which can support 1000 / 100 / 10 Mbps with
 * full- / half-duplex mode. The Ethernet port can automatically negotiate with the
 * router / switch / hub to set on the appropriate mode or manually set any mode.
 *
 *
 * @section show_ethernet_device_information 1. Show Ethernet Device Information
 *
 * Display the standard information for devices with the <B>ethtool</B>.
 * @code {.c}
 * build $ make menuconfig
 *   Ambarella File System Configuration >
 *     Open Source Software (OSS) >
 *       Network/BlueTooth Packages >
 *         Network Utilities >
 *           [*] Add ethtool support.
 * @endcode
 * @code {.c}
 * board # ethtool eth0
 * Settings for eth0:
 *   Supported ports: [ TP MII ]
 *   Supported link modes: 10baseT/Half 10baseT/Full
 *                         100baseT/Half 100baseT/Full
 *                         1000baseT/Half 1000baseT/Full
 *   Supported pause frame use: Symmetric Receive-only
 *   Supports auto-negotiation: Yes
 *   Advertised link modes: 10baseT/Half 10baseT/Full
 *                          100baseT/Half 100baseT/Full
 *                          1000baseT/Half 1000baseT/Full
 *   Advertised pause frame use: No
 *   Advertised auto-negotiation: Yes
 *   Speed: 1000Mb/s
 *   Duplex: Full
 *   Port: MII
 *   PHYAD: 0
 *   Transceiver: internal
 *   Auto-negotiation: on
 *   Current message level: 0x00000001 (1)
 *                          drv
 *   Link detected: yes
 * @endcode
 *
 * - - - -
 *
 * @section modify_ip_address 2. Modify IP Address
 *
 * For CV5x / CV7x, the IP address of eth0 is set to 10.0.0.2 (default). The IP address can be modified to another
 * IP address. The IP address of the second Ethernet port, which is not defined by default,
 * can also be configured in the same file.
 * @code {.c}
 * board # vi /etc/network/interfaces
 * # Configure Loopback
 * auto lo
 * iface lo inet loopback
 *
 * auto eth0
 * iface eth0 inet static
 * address 10.0.0.2 (for example, 10.0.0.19)
 * netmask 255.255.255.0
 * gateway 10.0.0.1
 *
 * # below is an example for eth1 in the same domain
 * auto eth1
 * iface eth1 inet static
 * address 10.0.0.10
 * netmask 255.255.255.0
 * gateway 10.0.0.1
 * @endcode
 *
 * - - - -
 *
 * @section jumbo_frames 3. Jumbo Frames
 *
 * <B>Set up the PC</B><br>
 * First, users must enable "jumbo frame" on a PC.
 * The following text explains how to enable jumbo frames on Windows 10.
 * @image html ethernet_enable_jumbo_frame_on_pc.png "Figure 3-1. Enable Jumbo Frame on a PC."
 * Ubuntu users should use the following command:
 * @code {.c}
 * board # ifconfig eth0 mtu 7000
 * @endcode
 * The Ethernet throughput can be tested using iperf3.<br>
 * In this case, PC acts as a server:
 * @code {.c}
 * PC $ iperf3.exe –s –i 1
 * @endcode
 * @note
 * Not all the Ethernet cards on a PC are compatible with jumbo frames.
 * Users should take care to ensure that their Ethernet cards have the desired performance.
 *
 * <B>Setting up the EVK board</B><br>
 * CV5x supports long frames, which are called jumbo frames.
 * This is advantageous for the Gbit Ethernet because it can function more efficiently with long frames.
 * This feature is enabled by default. The limit for maximum transmission unit (MTU) is 8 KB;
 * use "ifconfig" to change the size of the MTU.
 * 1. Select the iperf3 tool.
 *   @code {.c}
 *   build $ make menuconfig
 *     Ambarella File System Configuration >
 *       Third Party Software / Libraries >
 *         Benchmark Tools >
 *           [*] Add iperf3 support
 *   @endcode
 * 2. Change the size of the MTU.
 *   @code {.c}
 *   board # ifconfig eth0 mtu 6000
 *   board # ifconfig
 *   eth0 Link encap:Ethernet HWaddr 1E:17:5E:FA:7B:4D
 *        inet addr:10.0.0.2 Bcast:10.255.255.255 Mask:255.0.0.0
 *        UP BROADCAST RUNNING MULTICAST MTU:6000 Metric:1
 *        RX packets:186 errors:0 dropped:1 overruns:0 frame:0
 *        TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
 *        collisions:0 txqueuelen:1000
 *        RX bytes:15426 (15.0 KiB) TX bytes:0 (0.0 B)
 *        Interrupt:33
 *   @endcode
 * 3. Use the `iperf` or `iperf3` tool. The evaluation kit (EVK) board sends the data, then the PC receives it.
 *   @code {.c}
 *   board # iperf3 –c 10.0.0.1 -i 1 –M 6000 -t 1000
 *   PC; iperf3.exe –s –i 1
 *   @endcode
 * 4. Use the `iperf` or `iperf3` tool. The PC sends the data, then the EVK board receives it.
 *   @code {.c}
 *   PC: iperf3.exe –c 10.0.0.2 -i 1 –M 6000 -t 1000
 *   board # iperf3 –s –i 1
 *   @endcode
 *
 * - - - -
 *
 * @section test_the_ethernet_throughput 4. Test the Ethernet Throughput
 *
 * Preparation:
 * - One 1000 / 100 / 10 Mbps switch
 * - One PC with Ethernet
 * - CV5x platform
 * Build `iperf` into the CV5x platform.
 * @code {.c}
 * build $ make menuconfig
 *   Ambarella File System Configuration >
 *     Third Party Software / Libraries >
 *       Benchmark Tools >
 *         [*] Add iperf support.
 * @endcode
 *
 * @subsection test_et_100 4.1 Test the Ethernet Throughput with the Speed 100 Mbps
 *
 * Connect the PC and the CV5x Ethernet ports to 100 Mbps and switch with an Ethernet cable.
 * When CV5x is set on 100-Mbps full-duplex mode, the PC should also be set on 100-Mbps full-duplex mode.
 * This is similar to half-duplex mode.
 * - <B>Full-Duplex Mode</B>
 *   1. Set the PC Ethernet to 100-Mbps full-duplex mode.
 *     @code {.c}
 *     host $ sudo ethtool -s <device> speed 100 duplex full
 *     @endcode
 *   2. Set the CV5x Ethernet to 100-Mbps full-duplex mode.
 *     @code {.c}
 *     board # ethtool -s <device> autoneg off speed 100 duplex full
 *     @endcode
 *   3. Use "iperf" to test the transmission control protocol (TCP) / user datagram protocol (UDP) throughput performance.
 *
 * - <B>Half-Duplex Mode</B>
 *
 *   1. Set the PC Ethernet to 100-Mbps half-duplex mode.
 *     @code {.c}
 *     host $ sudo ethtool -s <device> speed 100 duplex half
 *     @endcode
 *   2. Set the CV5x Ethernet to speed 100-Mbps half-duplex mode.
 *     @code {.c}
 *     board # ethtool -s <device> autoneg off speed 100 duplex half
 *     @endcode
 *   3. Use "iperf" to test the TCP / UDP throughput performance.
 *
 * @subsection test_et_10 4.2 Test Ethernet Throughput with 10-Mbps Speed
 *
 * Connect the PC and the CV5x Ethernet port to 1000 / 100 / 10 Mbps and switch with an Ethernet cable.
 * When CV5x is set to 10-Mbps full-duplex mode, the PC should be set to 100 Mbps full-duplex mode correspondingly.
 * This is similar to the half-duplex mode.
 * - <B>Full-Duplex Mode</B>
 *   1. Set the PC Ethernet to the 100 Mbps-speed with full-duplex mode.
 *   @code {.c}
 *   host $ sudo ethtool -s <device> speed 100 duplex full
 *   @endcode
 *   2. Set the CV5x Ethernet to 10-Mbps speed with full-duplex mode.
 *   @code {.c}
 *   board # ethtool -s <device> autoneg off speed 10 duplex full
 *   @endcode
 *   3. Use `"iperf"` to test TCP / UDP throughput performance.
 *
 * - <B>Half-Duplex Mode</B>
 *   1. Set the PC Ethernet to 100-Mbps speed with half-duplex mode.
 *   @code {.c}
 *   host $ sudo ethtool -s <device> speed 100 duplex half
 *   @endcode
 *   2. Set the CV5x Ethernet to 10-Mbps speed with half-duplex mode.
 *   @code {.c}
 *   board # ethtool -s <device> autoneg off speed 10 duplex half
 *   @endcode
 *   Use `"iperf"` to test the TCP / UDP throughput performance.
 *
 * - - - -
 *
 * @section reference_ethernet_throughput_test_result 5. Reference Ethernet Throughput Test Result
 *
 * The following table provides the reference Ethernet throughput test results.
 * <table>
 * <tr>
 * <th><div style="width:120px">Protocol</div></th><th><div style="width:120px">Speed</div></th>
 * <th><div style="width:120px">Duplex</div></th><th><div style="width:240px">TCP Result</div></th>
 * </tr>
 * <tr><td rowspan="7">
 * <tr>			<td rowspan="3">100Mbps	  <tr><td>full</td><td>77 Mbps</td></tr>
 * <tr>						      <td>Half</td><td>77.1 Mbps</td></tr></td></tr>
 * <tr>			<td rowspan="2">1000Mbps      <tr><td>Full</td><td>835 Mbps</td></tr>
 * </tr></td>
 * </table>
 * <br>
 *
 * <table>
 * <tr>
 * <th><div style="width:120px">Protocol</div></th><th><div style="width:120px">Speed</div></th>
 * <th><div style="width:120px">Duplex</div></th><th><div style="width:240px">UDP Result(Mbps,Packat Loss)</div></th>
 * </tr>
 * <tr><td rowspan="7">UDP
 * <tr>			<td rowspan="3">100Mbps	<tr><td>full</td><td>94.41(0%)</td></tr>
 * <tr>						    <td>Half</td><td>94(0%)</td></tr></td></tr>
 * <tr>			<td rowspan="2">1000Mbps	<tr><td>Full</td><td>852(0.02%)</td></tr>
 * </tr></td>
 * </table>
 * <br>
 *
 * - - - -
 *
 * @section configure_VLAN_function 6. Configure VLAN Function
 *
 * Virtual local area networks (VLANs) are logical groupings of devices in the same broadcast domain. VLANs are
 * usually configured on switches by placing some interfaces into one broadcast domain and some
 * interfaces into another. Each VLAN acts as a subgroup of switch ports in an Ethernet LAN.
 * VLANs can spread across multiple switches, with each VLAN being treated as its own subnet or
 * broadcast domain. This means that frames broadcasted onto the network will be switched only
 * between the ports within the same VLAN.<br>
 * The following provides steps to show VLAN connection between two EVK boards:
 *
 * One EVK board:
 * @code {.c}
 * board# vconfig add eth0 20
 * board# vconfig add eth0 15
 * board# ifconfig eth0.20 192.168.20.144 up
 * board# ifconfig eth0.15 192.168.1.144 up
 * board# ifdown –f eth0
 * board# ifconfig eth0 192.168.254.144 up
 * @endcode
 *
 * Another EVK board:
 * @code {.c}
 * board# vconfig add eth0 20
 * board# vconfig add eth0 15
 * board# ifconfig eth0.20 192.168.20.140 up
 * board# ifconfig eth0.15 192.168.1.140 up
 * board# ifdown –f eth0
 * board# ifconfig eth0 192.168.254.140 up
 * @endcode
 *
 * There should be no communication between VLAN20 and VLAN15, but the test results show that
 * there is communication in different VLANs, which is unexpected.
 * @image html test_result_for_vlan_connect_between_two_EVK_boards.png "Figure 6-1. VLAN Connect Between Two EVK Boards Test Result."
 *
 * In order to prevent different VLAN ports from communicating with each other, reverse path
 * filtering is a mechanism adopted by the Linux kernel, as well as most networking devices
 * to verify if a receiving packet source address is routable.<br>
 * Enable the reverse path in the Linux kernel:
 * @code {.c}
 * board# echo 1 > /proc/sys/net/ipv4/conf/all/rp_filter
 * @endcode
 *
 * - - - -
 *
 * @section dual_eth_work 7. Two Ethernet Ports Function Together
 * The two Ethernet ports can function simultanously, either in the same domain or different domains.
 * An example for the two ports in the same domain is below.
 *
 * @note
 *   - For the case of two ports in the same domain, Ambarella recommends adding a switch / hub / router
 *     into the network so that the packet can be forwarded correctly.
 *   - If two ports are in the same domain, the system chooses an interface with smaller matric
 *     values for network traffic automatically.
 *
 * @code {.c}
 * Set address:
 * PC:           Eth0 10.0.0.5  Eth1 10.0.0.20
 * EVK:          eth0 10.0.0.2  eth1 10.0.0.10
 * And connect PC Eth0 to board eth0, PC Eth1 to board eth1
 *
 * board# ifconfig
 * eth0      Link encap:Ethernet  HWaddr 76:34:96:C8:83:48
 *           inet addr:10.0.0.2  Bcast:10.0.0.255  Mask:255.255.255.0
 *           UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
 *           RX packets:13 errors:0 dropped:0 overruns:0 frame:0
 *           TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
 *           collisions:0 txqueuelen:1000
 *           RX bytes:1230 (1.2 KiB)  TX bytes:0 (0.0 B)
 *           Interrupt:32
 *
 * eth1      Link encap:Ethernet  HWaddr 6E:E0:D7:79:73:A0
 *           inet addr:10.0.0.10  Bcast:10.0.0.255  Mask:255.255.255.0
 *           UP BROADCAST MULTICAST  MTU:1500  Metric:1
 *           RX packets:0 errors:0 dropped:0 overruns:0 frame:0
 *           TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
 *           collisions:0 txqueuelen:1000
 *           RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
 *           Interrupt:33
 *
 * lo        Link encap:Local Loopback
 *           inet addr:127.0.0.1  Mask:255.0.0.0
 *           UP LOOPBACK RUNNING  MTU:65536  Metric:1
 *           RX packets:0 errors:0 dropped:0 overruns:0 frame:0
 *           TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
 *           collisions:0 txqueuelen:1000
 *           RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
 *
 * board# route -n
 * Kernel IP routing table
 * Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
 * 0.0.0.0         10.0.0.1        0.0.0.0         UG    100    0        0 eth0
 * 10.0.0.0        0.0.0.0         255.255.255.0   U     0      0        0 eth1
 * 10.0.0.0        0.0.0.0         255.255.255.0   U     100    0        0 eth0
 * @endcode
 *
 * Below is an example of two ports in different domains.
 * @code {.c}
 * Set address:
 * PC:           Eth0 10.0.0.5  Eth1 110.0.0.5
 * EVK:          eth0 10.0.0.2  eth1 110.0.0.2
 * And connect PC Eth0 to board eth0, PC Eth1 to board eth1.
 * board# ifconfig
 * eth0      Link encap:Ethernet  HWaddr 76:34:96:C8:83:48
 *           inet addr:10.0.0.2  Bcast:10.0.0.255  Mask:255.255.255.0
 *           UP BROADCAST RUNNING MULTICAST  MTU:1500  Metric:1
 *           RX packets:13 errors:0 dropped:0 overruns:0 frame:0
 *           TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
 *           collisions:0 txqueuelen:1000
 *           RX bytes:1230 (1.2 KiB)  TX bytes:0 (0.0 B)
 *           Interrupt:32
 *
 * eth1      Link encap:Ethernet  HWaddr 6E:E0:D7:79:73:A0
 *           inet addr:110.0.0.2  Bcast:110.0.0.255  Mask:255.255.255.0
 *           UP BROADCAST MULTICAST  MTU:1500  Metric:1
 *           RX packets:0 errors:0 dropped:0 overruns:0 frame:0
 *           TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
 *           collisions:0 txqueuelen:1000
 *           RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
 *           Interrupt:33
 *
 * lo        Link encap:Local Loopback
 *           inet addr:127.0.0.1  Mask:255.0.0.0
 *           UP LOOPBACK RUNNING  MTU:65536  Metric:1
 *           RX packets:0 errors:0 dropped:0 overruns:0 frame:0
 *           TX packets:0 errors:0 dropped:0 overruns:0 carrier:0
 *           collisions:0 txqueuelen:1000
 *           RX bytes:0 (0.0 B)  TX bytes:0 (0.0 B)
 *
 * board# route -n
 * Kernel IP routing table
 * Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
 * 0.0.0.0         10.0.0.1        0.0.0.0         UG    100    0        0 eth0
 * 10.0.0.0        0.0.0.0         255.255.255.0   U     100    0        0 eth0
 * 110.0.0.0       0.0.0.0         255.255.255.0   U     0      0        0 eth1
 * @endcode
 *
 */
/*!
 * @file ptp.h
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
 * @page si_ptp PTP
 *
 * @section ptp_introduction 1 PTP Introduction
 *
 * Precision time protocol (PTP) is defined in IEEE 1588 as pecision clock synchronization for
 * networked measurements and control systems, and was developed to synchronize the clocks in
 * packet-based networks that include distributed device clocks of varying precision and stability.<br>
 *
 * PTP can transmit over user datagram protocol (UDP), media access control (MAC) protocol, or
 * multi-protocol label switching (MPLS).<br>
 *
 * To distribute time, PTP devices are made up primarily of two main roles.
 *   - Master: the entity distributing time to slaves. A master can also be a grand master (GM)
 *     that receives its time from a primary reference source, typically a GPS satellite signal.
 *   - Slave: the remove device that synchronizes to the master.
 *
 * @par Benefits of PTP:
 *
 * - Standardized protocol, IEEE1588v2
 * - Sub-microsecond accuracy and precision
 * - Low cost and easy setup in existing Ethernet networks
 * - Limited bandwidth required for PTP data packets
 * - Capability to autonomously decide GM clocks using a best master clock algorithm (BMCA)
 * - Synchronization of the clocks in local area accounts for path delays
 * - Hardware timestamps, which improve the accuracy of time synchronization
 * - On-board clock included with hardware PTP, which can be synchronized by or synchronized to other
 *   clock sources (such as GPS and NTP), enabling increasing clock accuracy
 *
 * - - - -
 *
 * @section ptp_on_ambarella_platform 2 PTP Examples on the Ambarella Platform
 *
 * There are two applications for PTP on the Ambarella platform: <b>ptp4l</b> and <b>phc2sys</b>.<br>
 *
 *   - <b>ptp4l</b>: Implements PTP and ordinary clocks. Through hardware timestamps, this application synchronizes
 *            PTP hardware clocks from physical MAC to remote master clocks.
 *   - <b>phc2sys</b>: Based on hardware timestamp, this application synchronizes clocks from the system to PTP hardware.
 *
 * @subsection ptp_on_ambarella_platform_preparation 2.1 Preparation
 *
 * 1. Prepare two Ambarella evaluation kit (EVK) boards: One is used as master clock and the other as a slave.
 * 2. Use a network cable to connect the boards and configure different IP addresses (default is 10.0.0.2).
 *
 * @par For CV2x SDK 3.0 Amba Build:
 * @code {.c}
 * build $ make menuconfig
 *           [*] Ambarella File System Configuration --->
 *             [*] Enable eth0
 *               (10.0.0.3) IP Address
 * @endcode
 *
 * @par For Cooper Amba Build:
 * @code {.c}
 * build $ make menuconfig
 *           rootfs --->
 *             network --->
 *               network-init (rootfs/network/network-init) --->
 *                 [*] Enable eth0 --->
 *                   (10.0.0.3) IP Address
 * @endcode
 *
 * @par For Cooper Yocto Build:
 * @code {.c}
 * build $ make menuconfig
 *           meta-ambabsp --->
 *             recipes-bsp --->
 *               network-init (meta-ambabsp/recipes-bsp/network-init) --->
 *                 [*] Enable eth0 --->
 *                   (10.0.0.3) IP Address
 * @endcode
 *
 * @subsection ptp_on_ambarella_platform_build 2.2 Build the PTP Driver and the Linux PTP Tool (linuxptp)
 *
 * @par For CV2x SDK 3.0 Amba Build:
 * @code {.c}
 *   build $ make menuconfig_public_linux
 *             Device Drivers --->
 *               PTP clock support --->
 *                 <*> PTP clock support
 *
 *   build $ make menuconfig
 *             [*] Ambarella File System Configuration --->
 *               Open Source Software (OSS) --->
 *                 Network/BlueTooth Packages --->
 *                   Network Utilities --->
 *                     [*] Add linuxptp into root_fs
 *
 * @endcode
 *
 * @par For Cooper Amba Build:
 * @code {.c}
 *   build $ make linux_menuconfig
 *             Device Drivers --->
 *               PTP clock support --->
 *                 <*> PTP clock support
 *
 *   build $ make menuconfig
 *             prebuild --->
 *               Open Source Software (OSS) --->
 *                 oss --->
 *                   [*] prebuild-linuxptp (prebuild/oss/armv8-a/linuxptp)
 * @endcode
 *
 * @par For Cooper Yocto Build:
 * @code {.c}
 *   build $ make linux_menuconfig
 *             Device Drivers --->
 *               PTP clock support --->
 *                 <*> PTP clock support
 *
 *   build $ make menuconfig
 *             meta-os --->
 *               recipes-connectivity --->
 *                 [*] linuxptp (meta-oe/recipes-connectivity/linuxptp)
 * @endcode
 *
 * @subsection ptp_on_ambarella_platform_test 2.3 Testing on the EVK Board
 *
 * When the building operation completes, burn the firmware to the respective EVK board.<br>
 *
 * When the system boots up, run the following commands on the EVK board with master clock to synchronize the clock
 * to Ethernet. The slave device will be synchronized via PTP.<br>
 *
 * @code {.c}
 * board # phc2sys -s CLOCK_REALTIME -c eth0 -w -m -r -r -O 0 &
 * board # ptp4l -i eth0 -m -H &
 * @endcode
 *
 * Run the following commands on the slave device to synchronize the system clock using PTP.<br>
 *
 * @code {.c}
 * board # phc2sys -s eth0 -c CLOCK_REALTIME -w -m -r -O 0 &
 * board # ptp4l -i eth0 -m -s -H &
 * @endcode
 *
 * While system time is modified on the master device, slaves will be synchronized slowly.
 *
 * @code {.c}
 * board # date
 * board # hwclock --set --date='12/17/2020 9:32'
 * board # hwclock --hctosys
 * board # date
 * @endcode
 *
 * @note
 *   Because the default adjusting step is 24 ms, the change step should be minimal. Users can increase
 *   or decrease by 100 seconds based on the current time.
 */
/*!
 * @file miscellaneous.h
 * @date 2021-09-15
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
 * @page si_miscellaneous Miscellaneous
 *
 * This chapter provides details on the measuring video latency, installing the TFTP server,
 * and the encryption engine.
 *
 *
 * @section installing_the_tftp_server 1. Installing the TFTP Server
 *
 * The following sub-sections provide instructions to install the TFTP server on the PC host.
 *
 * @subsection tftpd_for_windows 1.1 TFTPD for Windows
 *
 * Install and run <B>TFTPD</B> (http://tftpd32.jounin.net/).<br>
 * <B>TFTPD32</B> for Windows 32-bit (shown below).<br>
 * <B>TFTPD64</B> for Windows 64-bit<br>
 * @image html miscellaneous_tftfpd_server_on_windows.png "TFTFPD Server on Windows"
 * Set the current directory to the folder where the firmware is
 * and set the server interface to the one connected to the board.
 *
 * @subsection tftpd_hpa_for_ubuntu 1.2 TFTPD HPA for Ubuntu
 *
 * Install <B>TFTPD-HPA.</B>
 * @code {.c}
 * host $ sudo apt-get install tftpd-hpa
 * @endcode
 * Create a directory for <B>TFTPD-HPA</B> and put the firmware in it.
 * @code {.c}
 * host $ sudo mkdir /tftpboot
 * host $ sudo chmod 777 tftpboot
 * host $ sudo chown nobody tftpboot
 * @endcode
 * Configure <B>TFTPD-HPA</B>.
 * @code {.c}
 * host $ sudo vim /etc/default/tftpd-hpa
 * TFTP_USERNAME="nobody"
 * TFTP_DIRECTORY="/tftpboot"
 * @endcode
 * Start <B>TFTPD-HPA</B>.
 * @code {.c}
 * host $ sudo /etc/init.d/tftpd-hpa start
 * @endcode
 *
 * @section use_watchdog 2. Using Watchdog
 *
 * The following sub-section provides instructions to use watchdog to avoid system hang.
 *
 * Before using watchdog, users must enable it via menuconfig.
 * @code
 * host$ make menuconfig
 * [*] Ambarella File System Configuration  --->
 *     Open Source Software (OSS)  --->
 *         System Utils  --->
 *             [*] Add watch dog support
 * @endcode
 *
 * Users can use following commands to let watchdog trigger system reboot when kernel panic happens.
 * @code
 * /sbin/watchdog -t 2 -T 3 /dev/watchdog
 * echo 3 > /proc/sys/kernel/panic
 * echo 1 > /proc/sys/kernel/panic_on_oops
 * echo 1 > /proc/sys/kernel/panic_on_warn
 * echo 1 > /proc/sys/kernel/panic_on_rcu_stall
 * @endcode
 */
/*!
 * @file jtag.h
 * @date 2022-07-21
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
 * @page si_jtag JTAG
 *
 * Joint test action group (JTAG) is used for testing interconnects and functionality on integrated circuit (ICs).
 * In this document, users are provided with setup details and also, provided with details on how to run JTAG.
 *
 *
 * @section set_up_jtag_code_viser_with_cvd64 1. Setup the JTAG Code Viser with CVD64
 *
 * @subsection setup_with_cvd64 1.1 Setup
 *
 * This chapter provides instructions to set up the JTAG Code Viser with CVD64 on Arm® Cortex® - A53 platforms
 * (including S5 / S5L / CV2 / CV22 / CV25 / CV25M / S6LM) and Arm® Cortex® - A76 platforms (including CV5).
 * The following instruction describes the use of Code Viser and CVD64 on CV5 as an example.
 * The same procedures apply to the other Arm® Cortex® - A53 and Arm® Cortex® - A76 platforms.
 * 1. Connect the Code Viser to the EVK board and PC.<br>
 * The Code Viser connects to the PC host with a USB cable to run Windows.
 * It connects to the EVK board JTAG slot via the JTAG cable.
 * @image html connect_code_viser_2_evk_board.png "Connect the Code Viser to the EVK Board"
 * 2. Install CVD64.<br>
 * CVD64 version 1.42 is recommended (Figure "Chameleon Version").
 * After the CVD is installed successfully, Visual C++ 2005 Redistributable for running CVD64 is automatically installed.
 * Let the system complete the installation.
 * If possible, restart the computer after the system finishes installing CVD64.
 * @image html cvd64_version.png "CVD64 Version 1.42"
 * 3. Install the USB driver for Code Viser.<br>
 * After CVD64 is installed, users need to install the USB driver for Code Viser manually.
 * The driver file is in JnDTech\CVI\CVD64\Drv.
 * Then, connect Code Viser to the PC and check if the driver is installed successfully as shown in Figure "CodeViser Driver".
 * @image html codeviser_driver_location.png "CodeViser Driver Location"
 * @image html codeviser_driver.png "CodeViser Driver"
 *
 * @subsection run_jtag_code_viser_with_cvd64 1.2 Run
 *
 *
 * @subsubsection a53_platforms 1.2.1 Cortex® - A53 Platforms
 *
 * 1. Start CVD64 and click <B>"Program > Open Script Files..."</B>.
 * Then, choose the script Ambarella_ARM_A53_CVD64.csf.  The contents of the script file is as shown below.
 * @code
 * ;CVD64  Friday, November 13, 2015  10:55:55
 * ;OPTION SET START
 *
 * CPUTYPE CORTEXA53
 * OPTION.JTAGCLOCK      10.000000Mhz
 *
 * ;JTAG Setting
 * MULtiCore.DEBUGACCESSPORT 0.
 * MULtiCore.IRPOST      0.
 * MULtiCore.DRPost      0.
 * MULtiCore.IRPRE       0.
 * MULtiCore.DRPre       0.
 * MULtiCore.DAPIRPOST   0.
 * MULtiCore.DAPDRPOST   0.
 * MULtiCore.DAPIRPRE    0.
 * MULtiCore.DAPDRPRE    0.
 * MULtiCore.COUNT       4.
 * MULtiCore.COREBASE    0x80010000 0x80110000 0x80210000 0x80310000
 * MULtiCore.CTIBASE     0x80020000 0x80120000 0x80220000 0x80320000
 * MULtiCore.ETMBASE     0x80040000 0x80140000 0x80240000 0x80340000
 *
 * SYStem.OPTION EnReset       OFF
 * SYStem.OPTION TRST          OFF
 * SYStem.OPTION ResBreak      OFF
 * SYStem.OPTION PCZero        OFF
 * SYStem.OPTION RegisterInit  OFF
 * SYStem.OPTION BigEndian     OFF
 *
 * VectorCatch.RESET           OFF
 * VectorCatch.PABORT          OFF
 * VectorCatch.DABORT          OFF
 * VectorCatch.UNDEF           OFF
 *
 * connectAttach
 * wait 100.ms
 *
 * break
 * register.view
 * @endcode
 * @image html load_a53_script_file.png "Load Cortex® A53 Script File"
 * 2. Click the <B>"GO"</B> button in the script window to run the script and start debugging.
 * 3. When it runs successfully, the system on the EVK board will halt.
 * Click <B>"GO"</B> to resume the system.
 * @image html load_a53_debug_recover.png "Cortex® A53 Debug and Recover"
 *
 * @subsubsection a76_platforms 1.2.2 Cortex® - A76 Platforms
 *
 * 1. Start CVD64 and click <B>"Program > Open Script Files..."</B>.
 * Then, choose the script Ambarella_ARM_A76_CVD64.csf.  The contents of the script file is as shown below.
 * @code
 * ; For Ambarella CV5 JTAG configuration
 *
 *
 * ; Ambarella configuration, DONOT delete
 * ; Amba:LogLevel 3
 * ; Amba:MemMap 0xEC000000 0x01000000 IO
 * ; Amba:Aarch  64
 *
 * CPUTYPE CORTEXA76
 * OPTION.JTAGCLOCK      30.000000Mhz
 * OPTION.InterruptRESet
 * OPTION.InterruptDisable ASMSTEP
 * OPTION.InterruptDisable CSTEP
 *
 * ;JTAG Setting
 * MULtiCore.DEBUGACCESSPORT 0.
 * MULtiCore.IRPOST      0.
 * MULtiCore.DRPost      0.
 * MULtiCore.IRPRE       0.
 * MULtiCore.DRPre       0.
 * MULtiCore.DAPIRPOST   0.
 * MULtiCore.DAPDRPOST   0.
 * MULtiCore.DAPIRPRE    0.
 * MULtiCore.DAPDRPRE    0.
 * MULtiCore.COUNT       2.
 * MULtiCore.COREBASE    0x80010000 0x80110000
 * MULtiCore.CTIBASE     0x80020000 0x80120000
 * MULtiCore.ETMBASE     0x80040000 0x80140000
 *
 * SYStem.OPTION EnReset       OFF
 * SYStem.OPTION TRST          OFF
 * SYStem.OPTION ResBreak      OFF
 * SYStem.OPTION PCZero        OFF
 * SYStem.OPTION RegisterInit  OFF
 * SYStem.OPTION BigEndian     OFF
 *
 * VectorCatch.RESET           OFF
 * VectorCatch.PABORT          OFF
 * VectorCatch.DABORT          OFF
 * VectorCatch.UNDEF           OFF
 *
 * # MapBusWidth32 0x00000000++0xFFFFFFFF
 *
 * connectAttach
 * wait 100.ms
 *
 * break
 * register.view
 *
 * ENDEXE
 * @endcode
 * @image html load_a76_script_file.png "Load Cortex® A76 Script File"
 * 2. Click the <B>"GO"</B> button in the script window to run the script and start debugging.
 * 3. When it runs successfully, the system on the EVK board will halt.
 * Click <B>"GO"</B> to resume the system.
 * @image html load_a76_debug_recover.png "Cortex® A76 Debug and Recover"
 */
/*!
 * @file temperature.h
 * @date 2022-12-16
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
 * @page si_temperature Temperature
 *
 * This section describes how to obtain CV5x junction temperature.
 *
 * 1. Update the analog-to-digital(ADC) node in the CV5 dtsi, to enable the ADC and temperature to voltage(T2V).
 *   @code {.c}
 *   adc@e4003000 {
 *   	compatible = "ambarella,adc";
 *   	#io-channel-cells = <1>;
 *   	reg = <0xe4003000 0x1000>;
 *   	interrupts = <0 42 0x4>;
 *   	clock-frequency = <3000000>;
 *   	clocks = <&gclk_adc>;
 *   	amb,rct-regmap = <&rct_syscon 0x198 0x1a0 0x770>;
 *   	amb,channel-num = <4>;
 *   	amb,scaler-1v8 = <0x01>;
 *   	amb,t2v-channel = <3>;
 *   	status = "okay";
 *   	};
 *   @endcode
 *
 * 2. Get the temperature in the system.
 *   @code {.c}
 *   # modprobe ambarella_adc
 *   # cat /sys/bus/iio/devices/iio\:device0/in_temp3_input
 *   # cat /sys/bus/iio/devices/iio\:device0/in_temp3_raw
 *   @endcode
 *
 */

