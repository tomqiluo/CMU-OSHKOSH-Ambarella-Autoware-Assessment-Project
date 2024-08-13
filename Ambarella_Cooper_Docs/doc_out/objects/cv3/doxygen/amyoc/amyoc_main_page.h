/*!
 * @file doc_amyoc_main.h
 * @brief This file defines the doxygen structure of amyoc project
 * @version 1.0
 * @date 2023-12-21
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


/*! @mainpage notitle
 * <h1>Ambarella Build System Document</h1>
 * - - - -
 * <h2>Revision History</h2>
 *
 * <table>
 * <caption id="amyoc_guide_rev_history"></caption>
 * <tr><th> Updated Date            <th align="left"> Modification
 * <tr><td> 2022-11-28              <td> Initial Version
 * <tr><td> 2022-12-19              <td> Updated Directory Structure
 * <tr><td> 2022-12-21              <td> Updated "out" Directory Structure
 * <tr><td> 2023-01-12              <td> Updated Section @ref doc_amyoc_guide_environment_template "1 Environment Template: inc.env.mk"
 * <tr><td> 2023-01-17              <td> Updated Section @ref doc_amyoc_guide_build_normal_image "1 Build the Normal Image"
 * <tr><td> 2023-01-31              <td> Updated Section @ref yocto_faq15 "Question 15"
 * <tr><td rowspan="3"> 2023-01-31  <td> 1. Updated Section @ref yocto_faq15 "Question 15"
 * <tr>                             <td> 2. Added Section @ref doc_yocto_rec_sec_commerial_3rd_party "7. Commerial Third-Party Libraries"
 * <tr>                             <td> 3. Updated Section @ref doc_amyoc_guide_build_normal_image "1 Firmware Image"
 * <tr><td> 2023-02-09              <td> Updated Section @ref doc_amyoc_guide_parameter_config "2 General Make Commands"
 * <tr><td rowspan="2"> 2023-02-16  <td> 1. Updated Page @ref doc_amyoc_oss "OSS Source Code Build by Amba Build"
 * <tr>                             <td> 2. Added Section @ref yocto_faq2 "Question 2"
 * <tr><td> 2023-06-27              <td> Added Section @ref yocto_faq30 "Question 30"
 * <tr><td> 2023-06-30              <td> Updated Section @ref doc_amyoc_guide_environment_variable_description "3 Description of Environment Variables"
 * <tr><td> 2023-07-04              <td> Updated Section @ref doc_amyoc_guide_application_template "3 Application Template: inc.app.mk"
 * <tr><td> 2023-08-03              <td> Updated Page @ref doc_amyoc_makefile "Makefile Templates"
 * <tr><td> 2023-08-16              <td> Updated Section @ref doc_amyoc_guide_environment_template "1 Environment Template: inc.env.mk"
 * <tr><td> 2023-09-04              <td> Added Section @ref doc_yocto_rec_difference_3rd_party "9. The Difference of Big OSS Modules"
 * <tr><td> 2023-10-16              <td> Updated Page @ref doc_amyoc_genv "Environment Parameters"
 * <tr><td> 2023-12-12              <td> Added Page @ref doc_amyoc_ros2 "ROS2 Image by Yocto Build"
 * <tr><td> 2023-12-26              <td> Updated Directory Structure
 * </table>
 *
 * - - - -

 * <h2>Cooper Build System Introduction</h2>
 * This document provides cooper build system introduction.
 *
 * The outline of @ref doc_amyoc_introduction is listed as follows:
 * - Section @ref doc_amyoc_guide_feature 
 * - Section @ref doc_amyoc_guide_arch 
 * - Section @ref doc_amyoc_guide_diff 
 * - Section @ref doc_amyoc_guide_system_structure_compilation 
 *
 * - - - -
 * <h2>Target Build Guidance</h2>
 * This document provides usage guide about how to build image and make commands.
 *
 * The outline of @ref doc_amyoc_target is listed as follows:
 * - Section @ref doc_amyoc_guide_build_normal_image 
 * - Section @ref doc_amyoc_guide_parameter_config 
 * - Section @ref doc_amyoc_guide_populate_sdk 
 * - Section @ref doc_amyoc_guide_other_commands 
 *
 * - - - -
 * <h2>Doxygen ROS2 Image by Yocto Build</h2>
 * This document provides usage guide about how to build ROS2 image.
 *
 *
 *
 * - - - -
 * <h2>Environment Parameters</h2>
 * This document introduces the environment parameters of Cooper Build System.
 *
 * The outline of @ref doc_amyoc_genv is listed as follows:
 * - Section @ref doc_amyoc_guide_environment_variable_amba_build 
 * - Section @ref doc_amyoc_guide_environment_variable_yocto_build 
 * - Section @ref doc_amyoc_guide_environment_variable_description 
 *
 * - - - -
 * <h2>Makefile Templates</h2>
 * This document provides usage guide about cooper build system makefile templates.
 *
 * The outline of @ref doc_amyoc_makefile is listed as follows:
 * - Section @ref doc_amyoc_guide_environment_template 
 * - Section @ref doc_amyoc_guide_installation_template 
 * - Section @ref doc_amyoc_guide_application_template 
 * - Section @ref doc_amyoc_guide_driver_template 
 * - Section @ref doc_amyoc_guide_configuration_template 
 *
 * - - - -
 * <h2>Generate Dependency Chain</h2>
 * This document introduces how to generate dependency chain for each software package.
 *
 * The outline of @ref doc_amyoc_dep is listed as follows:
 * - Section @ref doc_amyoc_guide_command_usage_of_amba_build 
 * - Section @ref doc_amyoc_guide_command_usage_of_yocto_build 
 * - Section @ref doc_amyoc_guide_real_dependency_amba 
 * - Section @ref doc_amyoc_guide_real_dependency_yocto 
 * - Section @ref doc_amyoc_guide_virtual_dependency 
 * - Section @ref doc_amyoc_guide_special_dependencies 
 * - Section @ref doc_amyoc_guide_amba_dep_graph 
 * - Section @ref doc_amyoc_guide_yocto_dep_graph 
 *
 * - - - -
 * <h2>OSS Source Code Build by Amba Build</h2>
 * This document provides usage guide about how to build OSS source code by using Amba-Build.
 *
 * The outline of @ref doc_amyoc_oss is listed as follows:
 * - Section @ref doc_amyoc_guide_download_packages 
 * - Section @ref doc_amyoc_guide_patch_package 
 *
 * - - - -
 * <h2>Yocto Recipe</h2>
 * This document provides yocto recipe usage and introduction.
 *
 * The outline of @ref doc_yocto_recipes is listed as follows:
 * - Section @ref doc_yocto_rec_sec_class 
 * - Section @ref doc_yocto_rec_sec_recipes 
 * - Section @ref doc_yocto_rec_sec_append 
 * - Section @ref doc_yocto_rec_sec_patch 
 * - Section @ref doc_yocto_rec_sec_example 
 * - Section @ref yocto_meta_layers 
 * - Section @ref doc_yocto_rec_sec_commerial_3rd_party 
 * - Section @ref doc_yocto_rec_sec_single_multi_sub 
 * - Section @ref doc_yocto_rec_difference_3rd_party 
 *
 * - - - -
 * <h2>Yocto Frequently Asked Questions</h2>
 * This document provides Yocto Frequently Asked Questions of Doxygen documents.
 *
 * The outline of @ref doc_yocto_faq is listed as follows:
 * - Section @ref yocto_faq1 
 * - Section @ref yocto_faq2 
 * - Section @ref yocto_faq3 
 * - Section @ref yocto_faq4 
 * - Section @ref yocto_faq5 
 * - Section @ref yocto_faq6 
 * - Section @ref yocto_faq7 
 * - Section @ref yocto_faq8 
 * - Section @ref yocto_faq9 
 * - Section @ref yocto_faq10 
 * - Section @ref yocto_faq11 
 * - Section @ref yocto_faq12 
 * - Section @ref yocto_faq13 
 * - Section @ref yocto_faq14 
 * - Section @ref yocto_faq15 
 * - Section @ref yocto_faq16 
 * - Section @ref yocto_faq17 
 * - Section @ref yocto_faq18 
 * - Section @ref yocto_faq19 
 * - Section @ref yocto_faq20 
 * - Section @ref yocto_faq21 
 * - Section @ref yocto_faq22 
 * - Section @ref yocto_faq23 
 * - Section @ref yocto_faq24 
 * - Section @ref yocto_faq25 
 * - Section @ref yocto_faq26 
 * - Section @ref yocto_faq27 
 * - Section @ref yocto_faq28 
 * - Section @ref yocto_faq29 
 * - Section @ref yocto_faq30 
 * - Section @ref yocto_faq31 
 * - Section @ref yocto_faq32 
 * - Section @ref yocto_faq33 
 *
 * - - - -

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
