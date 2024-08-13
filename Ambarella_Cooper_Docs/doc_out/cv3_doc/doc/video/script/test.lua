vsrc_0 = {
	vsrc_id = 0,
	mode = "1952x1112",
	hdr_mode = "linear", -- options: "linear", "2x" or "3x"
	fps = 60,
	bits= 12,
	vsrc_ctx_switch = 0,
}

chan_0 = {
	id = 0,
	vsrc = vsrc_0,
	img_stats_src_chan = "chan_0",
	sensor_ctrl = 1,
	max_padding_width = 0,
	idsp_fps = 0,
	lens_warp = 0,
	max_main_input_width = 0, -- 0: VIN raw width
	blend_left = 0,
	blend_right = 0,
	mctf_cmpr = 1,
	mctf_10bit_ref = 0,
	main_burst_tile = 1,
	extra_downscale = 0,
	raw_capture = 1,
	main = {
		max_output = {0, 0}, -- output width
		input	   = {16, 16, 1920, 1080},
		output     = {0, 0, 1920, 1080},
	},
	second = {
		max_output = {0, 0}, -- output width
		input	   = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 720, 480},
	},
	third = {
		max_output = {1920, 0},
		input      = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 1920, 1080},
	},
	fourth = {
		max_output = {0, 0},
		input      = {0, 0, 0, 0},
		output     = {0, 0, 0, 0},
	},
	fifth = {
		max_output = {0, 0}, -- output width
		input	   = {0, 0, 0, 0}, -- full main
		output     = {0, 0, 1280, 720},
	},
	pyramid = {
		input_buf_id = 4,	-- 0: Main, 1: Second, 2: Third, 3: Fourth, 4: Fifth
		scale_type = 0,		-- 0: 1/sqrt(2); 1: 1/2; 2: Arbitrary size
		buf_addr = 0x0,
		buf_size = 0x0,
		manual_feed = 1,
		item_num = 0,
		layer_map = 0x3F,
		enable_frame_tag = 1 ,
		frame_tag_value = 0x410,
		frame_tag_mask = 0xc30,
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
	max_size = {1920, 1080},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	possible_enc_src_map = 0x0;
}

stream_1 = {
	id = 1,
	max_size = {720, 480},
	max_M = 1,
	fast_seek_enable = 0,
	two_ref_enable = 0,
	max_svct_layers_minus_1 = 0,
	max_num_minus_1_ltrs = 0,
	codec_enable = 0, -- 0: H264/H265/MJPEG; 1: H265/MJPEG; 2: H264/MJPEG; 3: MJPEG
	possible_enc_src_map = 0x0;
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
			size = {0, 0}, -- min size to contain source buffers
			source = {"chan_0.main",},
			extra_dram_buf = 1,
			enable_order = 0,
		},
		{
			type = "encode",
			size = {0, 0},
			source = {"chan_0.second",},
			extra_dram_buf = 0,
		},
		{
			type = "prev",
			size = {0, 0},
			source = {"chan_0.third",},
			vout_id = 1,
			extra_dram_buf = 0,
			enable_order = 0,
		},
	},
	streams = {
		stream_0,
		stream_1,
	},
}

return _resource_config_