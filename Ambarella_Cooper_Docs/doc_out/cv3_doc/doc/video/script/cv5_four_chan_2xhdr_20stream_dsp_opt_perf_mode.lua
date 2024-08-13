vsrc_0 = {
	vsrc_id = 0,
	mode = "3840x2160",
	hdr_mode = "2x", -- options: "linear", "2x" or "3x"
	fps = 30,
	bits= 0,
}

vsrc_1 = {
	vsrc_id = 1,
	mode = "3840x2160",
	hdr_mode = "2x", -- options: "linear", "2x" or "3x"
	fps = 30,
	bits= 0,
}

vsrc_2 = {
	vsrc_id = 2,
	mode = "3840x2160",
	hdr_mode = "2x", -- options: "linear", "2x" or "3x"
	fps = 30,
	bits= 0,
}

vsrc_3 = {
	vsrc_id = 3,
	mode = "3840x2160",
	hdr_mode = "2x", -- options: "linear", "2x" or "3x"
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
	idsp_core_cfg_enable = 1,
	idsp_core_mode = 0,
	rotate_cw = 1,
	hflip = 1,
	vflip = 1,
	high_perf_enable = 0,
	main = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 2160, 3840},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 608, 800},
	},
	third = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 1088, 1920},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 1280},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 1280},
	},

	pyramid = {
		input_buf_id = 0,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x00,
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
	idsp_core_cfg_enable = 1,
	idsp_core_mode = 1,
	high_perf_enable = 0,
	rotate_cw = 1,
	hflip = 1,
	vflip = 1,
	main = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 2160, 3840},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 608, 800},
	},
	third = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 1088, 1920},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 1280},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 1280},
	},
	pyramid = {
		input_buf_id = 0,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x00,
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
	idsp_core_cfg_enable = 1,
	idsp_core_mode = 0,
	high_perf_enable = 0,
	rotate_cw = 1,
	hflip = 1,
	vflip = 1,
	main = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 2160, 3840},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 608, 800},
	},
	third = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 1088, 1920},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 1280},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 1280},
	},
	pyramid = {
		input_buf_id = 0,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x00,
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
	idsp_core_cfg_enable = 1,
	idsp_core_mode = 1,
	high_perf_enable = 0,
	rotate_cw = 1,
	hflip = 1,
	vflip = 1,
	main = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 2160, 3840},
	},
	second = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 608, 800},
	},
	third = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 1088, 1920},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 1280},
	},
	fifth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 720, 1280},
	},
	pyramid = {
		input_buf_id = 0,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 0,
		item_num = 0,
		layer_map = 0x00,
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
	max_size = {2160, 3840,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_1 = {
	id = 1,
	max_size = {608, 800,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_2 = {
	id = 2,
	max_size = {2160, 3840,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_3 = {
	id = 3,
	max_size = {1088, 1920,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_4 = {
	id = 4,
	max_size = {720, 1280,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_5 = {
	id = 5,
	max_size = {2160, 3840,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_6 = {
	id = 6,
	max_size = {608, 800,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_7 = {
	id = 7,
	max_size = {2160, 3840,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_8 = {
	id = 8,
	max_size = {1088, 1920,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_9 = {
	id = 9,
	max_size = {720, 1280,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_10 = {
	id = 10,
	max_size = {2160, 3840,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_11 = {
	id = 11,
	max_size = {608, 800,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_12 = {
	id = 12,
	max_size = {2160, 3840,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_13 = {
	id = 13,
	max_size = {1088, 1920,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_14 = {
	id = 14,
	max_size = {720, 1280,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_15 = {
	id = 15,
	max_size = {2160, 3840,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_16 = {
	id = 16,
	max_size = {608, 800,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_17 = {
	id = 17,
	max_size = {2160, 3840,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_18 = {
	id = 18,
	max_size = {1088, 1920,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
}

stream_19 = {
	id = 19,
	max_size = {720, 1280,},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 2, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	enc_core_cfg_enable = 1,
	enc_core_mode = 2,
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
			size = {0, 0},
			source = {"chan_0.main",},
			extra_dram_buf = 2,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_0.second", },
			extra_dram_buf = 1,
			frame_rate = 10,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_0.third", },
			extra_dram_buf = 1,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_0.fourth",},
			extra_dram_buf = 1,
			frame_rate = 1,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_1.main",},
			extra_dram_buf = 2,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_1.second", },
			extra_dram_buf = 1,
			frame_rate = 10,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_1.third", },
			extra_dram_buf = 1,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_1.fourth",},
			extra_dram_buf = 1,
			frame_rate = 1,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_2.main",},
			extra_dram_buf = 2,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_2.second", },
			extra_dram_buf = 1,
			frame_rate = 10,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_2.third", },
			extra_dram_buf = 1,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_2.fourth",},
			extra_dram_buf = 1,
			frame_rate = 1,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_3.main",},
			extra_dram_buf = 2,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_3.second", },
			extra_dram_buf = 1,
			frame_rate = 10,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_3.third", },
			extra_dram_buf = 1,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_3.fourth",},
			extra_dram_buf = 1,
			frame_rate = 1,
		},

	},
	streams = {
		stream_0,
		stream_1,
		stream_2,
		stream_3,
		stream_4,
		stream_5,
		stream_6,
		stream_7,
		stream_8,
		stream_9,
		stream_10,
		stream_11,
		stream_12,
		stream_13,
		stream_14,
		stream_15,
		stream_16,
		stream_17,
		stream_18,
		stream_19,
	},
}

return _resource_config_

