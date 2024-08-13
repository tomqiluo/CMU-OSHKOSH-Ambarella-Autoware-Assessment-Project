--[[
History:
  2018-3-9 - [Zhaoyang Chen] created file

Copyright (c) 2018 Ambarella International LP

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
	fps = 20,
	bits= 0,
	mirror=3,
	pattern=2,
}

vsrc_1 = {
	vsrc_id = 1,
	mode = "3840x2160",
	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
	fps = 20,
	bits= 0,
	mirror = 0,
}

vsrc_2 = {
	vsrc_id = 2,
	mode = "3840x2160",
	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
	fps = 20,
	bits= 0,
	mirror=3,
	pattern=0,
}

vsrc_3 = {
	vsrc_id = 3,
	mode = "3840x2160",
	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
	fps = 20,
	bits= 0,
	mirror=0,
}

chan_0 = {
	id = 0,
	vsrc = vsrc_0,
	vsrc_ctx = 0,
	img_stats_src_chan = "chan_0",
	sensor_ctrl = 1,
	max_padding_width = 512,
	max_vwarp_wait_lines = 0,
	idsp_fps = 0,
	lens_warp = 1,
	max_main_input_width_width = 0, -- 0: VIN raw width
	high_perf_enable = 1,
	mctf_cmpr = 0,
	y12_enable =0,
	c2y_burst_tile = 1,
	extra_downscale = 0,
	enable_group = 1,
	group_idx = 0,
	group_order_idx = 0,
	rotate_cw = 1,
	hflip = 1,
	vflip = 1,
	high_perf_enable = 0,
--[[
	slice_cfg_enable = 0,
	slice_num = 2,
	warp_paddind_width = 64,
	raw_padding_width = 64,
--]]
	main = {
		max_output = {1920, 2880}, -- output width
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 1920, 2880},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	third = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 0, 0},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 0, 0},
	},
	pyramid = {
		input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x0,
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
		},
	},
}

chan_1 = {
	id = 1,
	vsrc = vsrc_1,
	vsrc_ctx = 0,
	img_stats_src_chan = "chan_0",
	sensor_ctrl = 1,
	max_padding_width = 512,
	max_vwarp_wait_lines = 0,
	idsp_fps = 0,
	lens_warp = 1,
	max_main_input_width = 0, -- 0: VIN raw width
	mctf_cmpr = 0,
	high_perf_enable = 0,
	y12_enable =0,
	c2y_burst_tile = 1,
	extra_downscale = 0,
	enable_group = 1,
	group_idx = 0,
	group_order_idx = 1,
	rotate_cw = 1,
	hflip = 1,
        vflip = 1,
--[[
	slice_cfg_enable = 0,
	slice_num = 2,
	warp_paddind_width = 64,
	raw_padding_width = 64,
--]]
	main = {
		max_output = {1984, 2880}, -- output width
		input      = {0, 0, 0, 0}, -- full main
		output     = {1728, 0, 1984, 2880},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	third = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 0, 0},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 0, 0},
	},
	pyramid = {
		input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x0,
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
		},
	},
}

chan_2 = {
	id = 2,
	vsrc = vsrc_2,
	vsrc_ctx = 0,
	img_stats_src_chan = "chan_0",
	sensor_ctrl = 1,
	max_padding_width = 512,
	max_vwarp_wait_lines = 0,
	idsp_fps = 0,
	lens_warp = 1,
	max_main_input_width = 0, -- 0: VIN raw width
	mctf_cmpr = 0,
	high_perf_enable = 0,
	y12_enable =0,
	c2y_burst_tile = 1,
	extra_downscale = 0,
	enable_group = 1,
	group_idx = 0,
	group_order_idx = 2,
	rotate_cw = 1,
	hflip = 1,
	vflip = 1,
--[[
	slice_cfg_enable = 0,
	slice_num = 2,
	warp_paddind_width = 64,
	raw_padding_width = 64,
--]]
	main = {
		max_output = {1920, 2880}, -- output width
		input      = {0, 0, 0, 0}, -- full main
		output     = {3520, 0, 1920, 2880},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	third = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 0, 0},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 0, 0},
	},
	pyramid = {
		input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x0,
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
		},
	},
}

chan_3 = {
	id = 3,
	vsrc = vsrc_3,
	vsrc_ctx = 0,
	img_stats_src_chan = "chan_0",
	sensor_ctrl = 1,
	max_padding_width = 512,
	max_vwarp_wait_lines = 0,
	idsp_fps = 0,
	lens_warp = 1,
	max_main_input_width = 0, -- 0: VIN raw width
	mctf_cmpr = 0,
	high_perf_enable = 0,
	y12_enable =0,
	c2y_burst_tile = 1,
	extra_downscale = 0,
	enable_group = 1,
	group_idx = 0,
	group_order_idx = 3,
	rotate_cw = 1,
	hflip = 1,
	vflip = 1,
--[[
	slice_cfg_enable = 0,
	slice_num = 2,
	warp_paddind_width = 64,
	raw_padding_width = 64,
--]]
	main = {
		max_output = {1792, 2880}, -- output width
		input      = {0, 0, 0, 0}, -- full main
		output     = {5376, 0, 1792, 2880},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	third = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 0, 0},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 0, 0},
	},
	pyramid = {
		input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x0,
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
		},
	},
}

stream_0 = {
	id = 0,
	max_size = {7168, 2880},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 1,
	max_num_minus_1_ltrs = 0,
	codec_enable = 1, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
}

_resource_config_ = {
	version = 1,
	log_level = 0, -- 0: error; 1: warning; 2: info; 3: debug
	channels = {
		chan_0,
		chan_1,
		chan_2,
		chan_3,
	},
	canvas = {
		{
			type = "encode",
			size = {7168, 2880},
			source = {"chan_0.main", "chan_1.main", "chan_2.main", "chan_3.main",},
			--vout_id = 2,
			blend_stitch_type = 1,
			extra_dram_buf = 0,
		},
	},
	streams = {
		stream_0,
	},
}

return _resource_config_
