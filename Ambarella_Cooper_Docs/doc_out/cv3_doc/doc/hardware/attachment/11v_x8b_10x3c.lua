--[[
History:
  2023-02-20 - [Ian Ding] created file

Copyright (c) 2024 Ambarella International LP

This file and its contents ("Software") are protected by intellectual
property rights including, without limitation, U.S. and/or foreign
copyrights. This Software is also the confidential and proprietary
information of Ambarella International LP and its licensors. You may not use, reproduce,
disclose, distribute, modify, or otherwise prepare derivative works of this
Software or any portion thereof except pursuant to a signed license agreement
or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
In the absence of such an agreement, you agree to promptly notify and return
this Software to Ambarella International LP.

This file includes sample code and is only for internal testing and evaluation.  If you
distribute this sample code (whether in source, object, or binary code form), it will be
without any warranty or indemnity protection from Ambarella International LP or its affiliates.

THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF NON-INFRINGEMENT,
MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL AMBARELLA INTERNATIONAL LP OR ITS AFFILIATES BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; COMPUTER FAILURE OR MALFUNCTION; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

--]]

vsrc_0 = {
        vsrc_id = 0,
        mode = "3840x2160",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_1 = {
        vsrc_id = 1,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_2 = {
        vsrc_id = 2,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_3 = {
        vsrc_id = 3,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_4 = {
        vsrc_id = 4,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_5 = {
        vsrc_id = 5,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}
vsrc_6 = {
        vsrc_id = 6,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_7 = {
        vsrc_id = 7,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_8 = {
        vsrc_id = 8,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_9 = {
        vsrc_id = 9,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

vsrc_10 = {
        vsrc_id = 10,
        mode = "1920x1200",
        hdr_mode = "wdr", -- options: "linear", "2x" or "3x"
        fps = 30,
        bits= 0,
}

chan_0 = {
        id = 0,
        vsrc = vsrc_0,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_0",
        sensor_ctrl = 1,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {480, 0, 960, 536},
        },
}

chan_1 = {
        id = 1,
        vsrc = vsrc_1,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_1",
        sensor_ctrl = 1,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {480, 544, 960, 536},
        },

}

chan_2 = {
        id = 2,
        vsrc = vsrc_2,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_2",
        sensor_ctrl = 1,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 480, 216},
        },

}

chan_3 = {
        id = 3,
        vsrc = vsrc_3,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_3",
        sensor_ctrl = 1,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 216, 480, 216},
        },

}

chan_4 = {
        id = 4,
        vsrc = vsrc_4,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_4",
        sensor_ctrl = 1,
        app_img_profile = 5,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 432, 480, 216},
        },
}

chan_5 = {
        id = 5,
        vsrc = vsrc_5,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_5",
        sensor_ctrl = 1,
        app_img_profile = 5,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 648, 480, 216},
        },
}

chan_6 = {
        id = 6,
        vsrc = vsrc_6,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_6",
        sensor_ctrl = 1,
        app_img_profile = 5,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 864, 480, 216},
        },
}

chan_7 = {
        id = 7,
        vsrc = vsrc_7,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_7",
        sensor_ctrl = 1,
        app_img_profile = 5,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {1440, 0, 480, 216},
        },
}

chan_8 = {
        id = 8,
        vsrc = vsrc_8,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_8",
        sensor_ctrl = 1,
        app_img_profile = 5,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {1440, 216, 480, 216},
        },
}

chan_9 = {
        id = 9,
        vsrc = vsrc_9,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_9",
        sensor_ctrl = 1,
        app_img_profile = 5,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {1440, 432, 480, 216},
        },
}

chan_10 = {
        id = 10,
        vsrc = vsrc_10,
        vsrc_ctx = 0,
        img_stats_src_chan = "chan_10",
        sensor_ctrl = 1,
        app_img_profile = 5,
        max_padding_width = 0,
        idsp_fps = 30,
        lens_warp = 0,
        max_main_input_width = 0, -- 0: VIN raw width
        mctf_cmpr = 1,
        c2y_burst_tile = 1,
        extra_downscale = 0,
        main = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {0, 0, 1920, 1080},
        },
        third = {
                max_output = {0, 0},
                input      = {0, 0, 0, 0},
                output     = {1440, 648, 480, 216},
        },
}

stream_0 = {
        id = 0,
        max_size = {1920, 1080},
        max_M = 1,
        fast_seek_enable = 0,
        two_ref_enable = 0,
        max_svct_layers_minus_1 = 0,
        max_num_minus_1_ltrs = 0,
        codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
}

_resource_config_ = {
        version = 1,
        log_level = 0, -- 0: error; 1: warning; 2: info; 3: debug
        channels = {
                chan_0,
                chan_1,
                chan_2,
                chan_3,
                chan_4,
                chan_5,
                chan_6,
                chan_7,
                chan_8,
                chan_9,
                chan_10,
        },
        canvas = {
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_0.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_1.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_2.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_3.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_4.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_5.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_6.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_7.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_8.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_9.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "encode",
                        size = {0, 0},
                        source = {"chan_10.main",},
                        extra_dram_buf = 0,
                },
                {
                        type = "prev",
                        size = {1920, 1080},
                        source = {"chan_0.third", "chan_1.third","chan_2.third","chan_3.third", "chan_4.third", "chan_5.third","chan_6.third","chan_7.third", "chan_8.third","chan_9.third","chan_10.third"},
                        vout_id = 2,
                        vout_YUV422 = 0,
                        extra_dram_buf = 0,
                        ext_mem = 1,
                        clear_background = 1,
                        feed_frame_num = 6,
                },
        },
        streams = {
                stream_0,
        },
}

return _resource_config_
