vout_0 = {
	status = "disable",				--selection: 0:disable, 1:on, 2:off, 3:reset
							--disable: do not use this vout controller
							--on: use this vout controller and enable video display
							--off: use this vout controller and disable video display
							--reset: reset this vout controller
	mode = "1200x1920p",
	input_yuv422 = "yes",				----selection: yes, no
	video_output_window = {0, 0, 1200, 1920},	--{offsetx, offsety, output_width, output_heigh}

	type = "mipi_dsi",      			--selection: digital, mipi_dsi, fpd_link

	vout_from_image = "disable",
	start_vout_immediately = "disable",
	default_img_format = "yuv422",			--selection: yuv422, yuv420

	video_rotate = "no",    			--selection: 0:no, 1:yes
	video_flip_mode = "no", 			--selection: 0:no, 1:hv, 2:h, 3:v

	own_mixer = "yes",      			--selection: 0:no, 1:yes

	osd_output_window = {0, 0, 0, 0},       	--{offsetx, offsety, output_width, output_heigh}
	osd_flip_mode = "no",   			--selection: 0:no, 1:hv, 2:h, 3:v
	osd_rescaler = "disable", 			--selection: 0:disable, 1:enable
	osd_rescaler_output_window = {0, 0, 0, 0},	--{offsetx, offsety, output_width, output_heigh}
	osd_transparent_color_enable = "enable",	--selection: 0:disable, 1:enable
	max_osd_bit_depth = 0,				--selection: 0: auto, 8: 8bits, 16: 16bits, 32: 32bits
}

vout_1 = {
	status = "disable",  				--selection: 0:disable, 1:on, 2:off, 3:reset
                                    			--disable: do not use this vout controller
                                    			--on: use this vout controller and enable video display
                                    			--off: use this vout controller and disable video display
                                    			--reset: reset this vout controller
	mode = "1200x1920p",
	input_yuv422 = "yes",           		----selection: yes, no
	video_output_window = {0, 0, 1200, 1920},	--{offsetx, offsety, output_width, output_heigh}

	type = "mipi_dsi",      			--selection: digital, mipi_dsi, fpd_link

	vout_from_image = "disable",
	start_vout_immediately = "disable",
	default_img_format = "yuv422",  		--selection: yuv422, yuv420

	video_rotate = "no",    			--selection: 0:no, 1:yes
	video_flip_mode = "no", 			--selection: 0:no, 1:hv, 2:h, 3:v

	own_mixer = "yes",      			--selection: 0:no, 1:yes

	osd_output_window = {0, 0, 0, 0},       	--{offsetx, offsety, output_width, output_heigh}
	osd_flip_mode = "no",   			--selection: 0:no, 1:hv, 2:h, 3:v
	osd_rescaler = "disable", 			--selection: 0:disable, 1:enable
	osd_rescaler_output_window = {0, 0, 0, 0},	--{offsetx, offsety, output_width, output_heigh}
	osd_transparent_color_enable = "enable",	--selection: 0:disable, 1:enable
	max_osd_bit_depth = 0,				--selection: 0: auto, 8: 8bits, 16: 16bits, 32: 32bits
}

vout_2 = {
	status = "on",  				--selection: 0:disable, 1:on, 2:off, 3:reset
							--disable: do not use this vout controller
							--on: use this vout controller and enable video display
							--off: use this vout controller and disable video display
							--reset: reset this vout controller
	mode = "1080p",
	input_yuv422 = "yes",
	video_output_window = {0, 0, 1920, 1080}, 	--{offsetx, offsety, output_width, output_heigh}

	type = "hdmi",          			--selection: hdmi, mipi_csi, cvbs

	hdmi_output_format = "rgb";     		--selection: 0:rgb, 1:yuv422, 2:yuv444
	                                		--only for hdmi output mode
	vout_from_image = "disable",
	start_vout_immediately = "disable",
	default_img_format = "yuv422",  		--selection: 0:yuv422, 1:yuv420

	video_rotate = "no",    			--selection: 0:no, 1:yes
	video_flip_mode = "no", 			--selection: 0:no, 1:hv, 2:h, 3:v

	own_mixer = "yes",      			--selection: 0:no, 1:yes

	osd_output_window = {0, 0, 1920, 1080},       	--{offsetx, offsety, output_width, output_heigh}
	osd_flip_mode = "no",   			--selection: 0:no, 1:hv, 2:h, 3:v
	osd_rescaler = "enable", 			--selection: 0:disable, 1:enable
	osd_rescaler_output_window = {0, 0, 1920, 1080},	--{offsetx, offsety, output_width, output_heigh}
	osd_transparent_color_enable = "enable",	--selection: 0:disable, 1:enable
	max_osd_bit_depth = 32,				--selection: 0: auto, 8: 8bits, 16: 16bits, 32: 32bits
}



_vout_config_ = {
	version = 1,
	vouts = {
		vout_0,
		vout_1,
		vout_2,
	},
}

return _vout_config_

