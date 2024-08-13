--[[
@file vss_cfg.lua

History:
  2023/05/04 - [Long Li] created file
 
Copyright (c) 2024 Ambarella International LP.

This file and its contents ( "Software" ) are protected by intellectual
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

cyclone_dds = {
        domain = 0,
        dds_protocol = "cyclone",
        preferred_version=100,   -- 1.0.0
        qos = {
                policy = 0,  -- 0: default, 1: reliability, 2: best effort
        },
}

_vss_config_ = {
	canvas_publish = {
		canvas = {
			{
				enable = 1,
				id = 0,
				zero_copy = 1,
			},
			{
				enable = 1,
				id = 1,
				zero_copy = 1,
			},
			{
				enable = 1,
				id = 2,
				zero_copy = 1,
			},
			{
				enable = 1,
				id = 5,
				zero_copy = 1,
			},
			{
				enable = 1,
				id = 6,
				zero_copy = 1,
			},
		},
		dds = cyclone_dds,
	},

	canvas_grp_publish = {
		canvas_grp = {
			enable = 1,
			id = {3,4},
			zero_copy = 1,
		},
		dds = cyclone_dds,
	},

	pyramid_publish = {
		pyramid = {
			{
				enable = 1,
				chan_id = 0,
				trigger_fps = 30,
				zero_copy = 1,
				layers = {0,1,2,3,4,5},
			},
			{
				enable = 1,
				chan_id = 1,
				trigger_fps = 30,
				zero_copy = 1,
				layers = {0,1,3},
			},
			{
				enable = 1,
				chan_id = 2,
				trigger_fps = 30,
				zero_copy = 1,
				layers = {0,1,2,3,4,5},
			},
		},
		dds = cyclone_dds,
	},
}

return _vss_config_
