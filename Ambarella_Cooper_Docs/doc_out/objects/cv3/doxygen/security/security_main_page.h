/*!
 * @file doc_security_main.h
 * @brief This file defines the doxygen structure of security chapter
 * @version 1.0
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


/*! @mainpage notitle
 * <h1>Ambarella Security Document</h1>
 * - - - -
 * <h2>Revision History</h2>
 *
 *
 * <table>
 * <caption id="security_rev_history"></caption>
 * <tr><th> Updated Date                <th align="left"> Modification
 * <tr><td> 20220721                    <td> Initial Release
 * </table>
 *
 * - - - -

 * The outline of @ref security_overview is listed as follows:
 * - Section @ref sec_solution 
 * - Section @ref sec_sw_hierarchy 
 * - Section @ref partitions 
 *
 *
 * --- 
 *
 * The outline of @ref sys_integrity_protection is listed as follows:
 * - Section @ref sec_boot 
 * - Section @ref sec_ota 
 * - Section @ref dm_verity 
 *
 *
 * --- 
 *
 * The outline of @ref system_reinforcement is listed as follows:
 * - Section @ref SEBLD 
 * - Section @ref selinux 
 * - Section @ref tee_and_trustzone 
 * - Section @ref anti_rollback 
 * - Section @ref disable_hw_debug_port 
 * - Section @ref disable_no_secure_protocol 
 * - Section @ref buffer_overflow_attack_resistance 
 * - Section @ref dram_scrambling 
 * - Section @ref cve_fix_strategy 
 *
 *
 * --- 
 *
 * The outline of @ref data_storage_protection is listed as follows:
 * - Section @ref data_part_enc 
 * - Section @ref data_enc_protection 
 * - Section @ref secure_storage 
 *
 *
 * --- 
 *
 * The outline of @ref data_transfer_protection is listed as follows:
 * - Section @ref ssl_and_tls 
 * - Section @ref tls_solution_in_amba 
 * - Section @ref secure_connection_in_cvflow 
 *
 *
 * --- 
 *
 * The outline of @ref system_integrity_protection is listed as follows:
 * - Section @ref ulp 
 * - Section @ref ulp_user_guide 
 * - Section @ref neural_network_model_protection 
 * - Section @ref neural_network_model_protections_user_guide 
 * - Section @ref ulp_nmp_key_tool 
 *
 *
 * --- 
 *
 * The outline of @ref user_privacy_protection is listed as follows:
 *
 *
 * --- 
 *
 * The outline of @ref secure_hardware is listed as follows:
 * - Section @ref otp_history 
 * - Section @ref otp 
 * - Section @ref uuid 
 * - Section @ref mono_counter 
 * - Section @ref TRNG 
 * - Section @ref disable_jtag_usb_boot 
 *
 *
 * --- 
 *
 * The outline of @ref key_management is listed as follows:
 * - Section @ref key_management_history 
 * - Section @ref pub_key_on_dev 
 * - Section @ref pri_key_in_local 
 * - Section @ref pri_key_rpc 
 * - Section @ref revoke_rot_key 
 * - Section @ref key_management_user_guide 
 *
 *
 * --- 
 *
 * The outline of @ref crypto_performance is listed as follows:
 * - Section @ref crpypto_performance_history 
 *
 *
 * --- 
 *
 * The outline of @ref design_guide is listed as follows:
 * - Section @ref design_guide_history 
 * - Section @ref for_dev_board 
 * - Section @ref hw_schematic_diag 
 * - Section @ref mass_production_process 
 *
 *
 * --- 
 *
 * The outline of @ref security_validation_guide is listed as follows:
 * - Section @ref validation_guide_history 
 * - Section @ref test_secure_boot 
 * - Section @ref test_optee 
 * - Section @ref test_ota 
 * - Section @ref test_sebld 
 * - Section @ref test_dm_crypt 
 * - Section @ref test_data_encryption 
 * - Section @ref test_secure_storage 
 * - Section @ref test_ulp 
 * - Section @ref test_nmp 
 * - Section @ref test_otp 
 * - Section @ref test_rng 
 * - Section @ref test_key_tools 
 * - Section @ref test_crypto_performance 
 *
 *
 * --- 
 *
 * The outline of @ref migration_guide is listed as follows:
 * - Section @ref migration_guide_history 
 * - Section @ref migration_guide_introduction 
 * - Section @ref key_alg 
 * - Section @ref pub_key 
 * - Section @ref poc6 
 * - Section @ref sec_usb_boot 
 * - Section @ref key_program 
 *
 *
 * --- 
 *

 *
 * <h2>License</h2>
 *
 *
 * Copyright (c) 2024 Ambarella International LP.
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

 *
 */
