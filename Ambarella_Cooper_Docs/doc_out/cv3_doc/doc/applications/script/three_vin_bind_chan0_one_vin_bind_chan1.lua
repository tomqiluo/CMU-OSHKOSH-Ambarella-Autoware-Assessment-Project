--[[
History:
  2023-3-9 - [Bingliang Liu] created file

Copyright (c) 2024 Ambarella International LP.

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
	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
	fps = 30,
	bits= 0,
}

vsrc_1 = {
	vsrc_id = 1,
	mode = "3840x2160",
	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
	fps = 30,
	bits= 0,
}

vsrc_2 = {
	vsrc_id = 2,
	mode = "3840x2160",
	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
	fps = 30,
	bits= 0,
}

vsrc_3 = {
	vsrc_id = 3,
	mode = "3840x2160",
	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
	fps = 30,
	bits= 0,
}


chan_0 = {
	id = 0,
	vsrc = vsrc_0,
	vsrc_ctx = 0,
	possible_vsrc_list = {vsrc_0,vsrc_1,vsrc_2,},
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
		max_output = {3840, 0},
		input      = {0, 0, 3840, 2160},
		output     = {0, 0, 3840, 2160},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 480},
	},
	third = {
		max_output = {3840, 0},
		input      = {0, 0, 3840, 2160},
		output     = {0, 0, 1920, 1080},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 1280, 720},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 1280, 720},
	},
	pyramid = {
		input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x7f,
		layers = {
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
		},
	},
}


chan_1 = {
	id = 1,
	vsrc = vsrc_3,
	vsrc_ctx = 0,
	img_stats_src_chan = "chan_1",
	sensor_ctrl = 1,
	max_padding_width = 0,
	idsp_fps = 30,
	raw_capture = 1,
    raw_manual_feed = 1,
    raw_feed_frame_num = 4,
	lens_warp = 0,
	max_main_input_width = 0, -- 0: VIN raw width
	mctf_cmpr = 1,
	c2y_burst_tile = 1,
	extra_downscale = 0,
	main = {
		max_output = {3840, 0},
		input      = {0, 0, 3840, 2160},
		output     = {0, 0, 3840, 2160},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 480},
	},
	third = {
		max_output = {3840, 0},
		input      = {0, 0, 3840, 2160},
		output     = {0, 0, 1920, 1080},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 1280, 720},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 1280, 720},
	},
	pyramid = {
		input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x7f,
		layers = {
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
			{
				crop_win = {0, 0, 0 ,0},
			},
		},
	},
}

stream_0 = {
	id = 0,
	max_size = {3840, 2160},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
}


stream_1 = {
	id = 1,
	max_size = {3840, 2160},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
}

stream_2 = {
	id = 2,
	max_size = {3840, 2160},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
}

stream_3 = {
	id = 3,
	max_size = {3840, 2160},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
}

stream_4 = {
	id = 4,
	max_size = {1920, 1080},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
}

stream_5 = {
	id = 5,
	max_size = {720, 480},
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
	},
	canvas = {
		{
			type = "encode",
			size = {3840, 2160},
			--[[you can change the channel orders by setting the item orer.
			Like "source = {"chan_0.main", "chan_1.main",}" or "source = {"chan_1.main", "chan_0.main",}"
			for different channel order
			--]]
			source = {"chan_0.main",},
			extra_dram_buf = 0,
		},
		{
			type = "encode",
			size = {720, 480},
			source = {"chan_0.second", },
			extra_dram_buf = 0,
		},
		{
			type = "prev",
			size = {1920, 1080},
			source = {"chan_0.third",},
			vout_id = 2,
			vout_YUV422 = 0,
			extra_dram_buf = 0,
		},
		{
			type = "encode",
			size = {1280, 720},
			source = {"chan_0.fourth", },
			extra_dram_buf = 0,
		},
		{
			type = "encode",
			size = {3840, 2160},
			source = {"chan_1.main",},
			extra_dram_buf = 0,
		},
		{
			type = "encode",
			size = {720, 480},
			--[[you can change the channel orders by setting the item orer.
			Like "source = {"chan_0.main", "chan_1.main",}" or "source = {"chan_1.main", "chan_0.main",}"
			for different channel order
			--]]
			source = {"chan_1.second", },
			extra_dram_buf = 0,
		},
		{
			type = "encode",
			size = {1920, 1080},
			source = {"chan_1.third", },
			extra_dram_buf = 0,
		},
	},
	streams = {
		stream_0,
		stream_1,
		stream_2,
		stream_3,
		stream_4,
		stream_5,
	},
}

return _resource_config_
