--[[
History:
  2020-3-10 - [Xin Gao] created file

Copyright (c) 2024 Ambarella International LP

This file and its contents ("Software") are protected by intellectual
property rights including, without limitation, U.S. and/or foreign
copyrights. This Software is also the confidential and proprietary
information of Ambarella International LP and its licensors. You may not use, reproduce,
disclose, distribute, modify, or otherwise prepare derivative works of this
Software or any portion thereof except pursuant to a signed license agreement
or nondisclosure agreement with Ambarella International LP or its authorized affiliates.
In the absence of such an agreement, you agree to promptly notify and return
this Software to Ambarella International LP

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

chan_0 = {
	id = 0,
	mount = 1, -- 0: wall mount; 1: ceiling mount; 2: desktop mount
	lens_projection_mode = 0, -- 0: equidistant; 1: stereographic; 2: look up table
	lens_fov = 190, -- in degree, lens diagonal fov
	max_radius = 1504, -- (0, pre_main width / 2]
	center_coord = {0, 0}, -- center of premain buffer
	behav = 0, -- 0: change all; 1: update specific view.
	tangential_distortion = {0.0, 0.0},
	clear = 0,
	view_num = 4,

	view_0 = {
		view_id = 0,
		area_num = 1,
		output = {0, 0, 1504, 1504},
		warp_mode = 2,	-- 0: no transform; 1: rectilinear; 2: panorama; 3: cylinder;
						-- 4: mercator; 5: equirectangular; 6: vertical panorama;
						-- 7: transverse mercator; 8: fulframe; 9: ceiling/desktop subg region;
						-- 10: warp copy; 11: squiricular
		zoom = {1.0, 1.0},
		fast_compute = 0,
		h_disable = 0,
		v_disable = 0,
		-- union
		warp_mode_adv_param = {
			ceiling_desktop_panor = { -- fulframe; ceiling and desktop panorama
				orientation = 'N', -- NESW
				edge_angle = 90,
				pan = 0,
				fov = 90,
			},
		},
	},
	view_1 = {
		view_id = 1,
		area_num = 1,
		output = {1504, 0, 1504, 1504},
		warp_mode = 2,	-- 0: no transform; 1: rectilinear; 2: panorama; 3: cylinder;
						-- 4: mercator; 5: equirectangular; 6: vertical panorama;
						-- 7: transverse mercator; 8: fulframe; 9: ceiling/desktop subg region;
						-- 10: warp copy; 11: squiricular
		zoom = {1.0, 1.0},
		fast_compute = 0,
		h_disable = 0,
		v_disable = 0,
		-- union
		warp_mode_adv_param = {
			ceiling_desktop_panor = { -- fulframe; ceiling and desktop panorama
				orientation = 'E', -- NESW
				edge_angle = 90,
				pan = 0,
				fov = 90,
			},
		},
	},
	view_2 = {
		view_id = 2,
		area_num = 1,
		output = {0, 1504, 1504, 1504},
		warp_mode = 2,	-- 0: no transform; 1: rectilinear; 2: panorama; 3: cylinder;
						-- 4: mercator; 5: equirectangular; 6: vertical panorama;
						-- 7: transverse mercator; 8: fulframe; 9: ceiling/desktop subg region;
						-- 10: warp copy; 11: squiricular
		zoom = {1.0, 1.0},
		fast_compute = 0,
		h_disable = 0,
		v_disable = 0,
		-- union
		warp_mode_adv_param = {
			ceiling_desktop_panor = { -- fulframe; ceiling and desktop panorama
				orientation = 'S', -- NESW
				edge_angle = 90,
				pan = 0,
				fov = 90,
			},
		},
	},
	view_3 = {
		view_id = 3,
		area_num = 1,
		output = {1504, 1504, 1504, 1504},
		warp_mode = 2,	-- 0: no transform; 1: rectilinear; 2: panorama; 3: cylinder;
						-- 4: mercator; 5: equirectangular; 6: vertical panorama;
						-- 7: transverse mercator; 8: fulframe; 9: ceiling/desktop subg region;
						-- 10: warp copy; 11: squiricular
		zoom = {1.0, 1.0},
		fast_compute = 0,
		h_disable = 0,
		v_disable = 0,
		-- union
		warp_mode_adv_param = {
			ceiling_desktop_panor = { -- fulframe; ceiling and desktop panorama
				orientation = 'W', -- NESW
				edge_angle = 90,
				pan = 0,
				fov = 90,
			},
		},
	},
}

_dewarp_config_ = {
	version = 1,
	log_level = 1, -- 0: error; 1: info; 2: debug
	heap_size = 0,
	check_disable = 0,
	verbose = 0,
	sync_enc_enable = 0,
	sync_enc_stream_id = -1,
	sync_enc_offset = {0, 0},
	channels = {
		chan_0,
	},
}

return _dewarp_config_
