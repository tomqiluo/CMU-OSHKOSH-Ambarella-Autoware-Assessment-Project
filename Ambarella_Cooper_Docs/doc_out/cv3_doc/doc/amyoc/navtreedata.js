/*
 @licstart  The following is the entire license notice for the JavaScript code in this file.

 The MIT License (MIT)

 Copyright (C) 1997-2020 by Dimitri van Heesch

 Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 and associated documentation files (the "Software"), to deal in the Software without restriction,
 including without limitation the rights to use, copy, modify, merge, publish, distribute,
 sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all copies or
 substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 @licend  The above is the entire license notice for the JavaScript code in this file
*/
var NAVTREE =
[
  [ "Build System", "index.html", [
    [ "Introduction", "da/dab/doc_amyoc_introduction.html", [
      [ "1 Main Features", "da/dab/doc_amyoc_introduction.html#doc_amyoc_guide_feature", null ],
      [ "2 Architecture", "da/dab/doc_amyoc_introduction.html#doc_amyoc_guide_arch", null ],
      [ "3 Differences Between Two Methods", "da/dab/doc_amyoc_introduction.html#doc_amyoc_guide_diff", null ],
      [ "4 Directory Structure", "da/dab/doc_amyoc_introduction.html#doc_amyoc_guide_system_structure_compilation", null ]
    ] ],
    [ "Target Build Guidance", "d2/dea/doc_amyoc_target.html", [
      [ "1 Firmware Image", "d2/dea/doc_amyoc_target.html#doc_amyoc_guide_build_normal_image", [
        [ "1.1 CV2x Image Build", "d2/dea/doc_amyoc_target.html#doc_guide_build_image_cv2x", null ],
        [ "1.2 CV5x Image Build", "d2/dea/doc_amyoc_target.html#doc_guide_build_image_cv5x", null ],
        [ "1.3 CV3 Image Build", "d2/dea/doc_amyoc_target.html#doc_guide_build_image_cv3", null ],
        [ "1.4 CV72 Image Build", "d2/dea/doc_amyoc_target.html#doc_guide_build_image_cv72", null ]
      ] ],
      [ "2 General Make Commands", "d2/dea/doc_amyoc_target.html#doc_amyoc_guide_parameter_config", null ],
      [ "3 Populate SDK Commands", "d2/dea/doc_amyoc_target.html#doc_amyoc_guide_populate_sdk", null ],
      [ "4 Other Make Commands", "d2/dea/doc_amyoc_target.html#doc_amyoc_guide_other_commands", null ]
    ] ],
    [ "ROS2 Image by Yocto Build", "dd/d7c/doc_amyoc_ros2.html", null ],
    [ "Environment Parameters", "d1/d20/doc_amyoc_genv.html", [
      [ "1 Export Env Parameters for Amba Build", "d1/d20/doc_amyoc_genv.html#doc_amyoc_guide_environment_variable_amba_build", null ],
      [ "2 Export Env Parameters for Yocto Build", "d1/d20/doc_amyoc_genv.html#doc_amyoc_guide_environment_variable_yocto_build", null ],
      [ "3 Description of Env Parameters", "d1/d20/doc_amyoc_genv.html#doc_amyoc_guide_environment_variable_description", null ]
    ] ],
    [ "Makefile Templates", "d7/d05/doc_amyoc_makefile.html", [
      [ "1 Environment Template: inc.env.mk", "d7/d05/doc_amyoc_makefile.html#doc_amyoc_guide_environment_template", null ],
      [ "2 Installation Template: inc.ins.mk", "d7/d05/doc_amyoc_makefile.html#doc_amyoc_guide_installation_template", null ],
      [ "3 Application Template: inc.app.mk", "d7/d05/doc_amyoc_makefile.html#doc_amyoc_guide_application_template", null ],
      [ "4 Driver Template: inc.mod.mk", "d7/d05/doc_amyoc_makefile.html#doc_amyoc_guide_driver_template", null ],
      [ "5 Configuration Template: inc.conf.mk", "d7/d05/doc_amyoc_makefile.html#doc_amyoc_guide_configuration_template", null ]
    ] ],
    [ "Generate Dependency Chain", "d7/df0/doc_amyoc_dep.html", [
      [ "1 Amba Build Command Option", "d7/df0/doc_amyoc_dep.html#doc_amyoc_guide_command_usage_of_amba_build", null ],
      [ "2 Yocto Build Command Option", "d7/df0/doc_amyoc_dep.html#doc_amyoc_guide_command_usage_of_yocto_build", null ],
      [ "3 Amba Build Regular Dependency", "d7/df0/doc_amyoc_dep.html#doc_amyoc_guide_real_dependency_amba", null ],
      [ "4 Yocto Build Regular Dependency", "d7/df0/doc_amyoc_dep.html#doc_amyoc_guide_real_dependency_yocto", null ],
      [ "5 Virtual Dependency", "d7/df0/doc_amyoc_dep.html#doc_amyoc_guide_virtual_dependency", null ],
      [ "6 Special Dependency", "d7/df0/doc_amyoc_dep.html#doc_amyoc_guide_special_dependencies", [
        [ "6.1 Virtual Package", "d7/df0/doc_amyoc_dep.html#sub_amyoc_guide_spec_dep_virt_pkg", null ],
        [ "6.2 Keyword", "d7/df0/doc_amyoc_dep.html#sub_amyoc_guide_spec_dep_keyword", null ],
        [ "6.3 Special Character", "d7/df0/doc_amyoc_dep.html#sub_amyoc_guide_spec_dep_spec_charactor", null ],
        [ "6.4 Environment Variable", "d7/df0/doc_amyoc_dep.html#sub_amyoc_guide_spec_dep_env_var", null ],
        [ "6.5 Yocto Special Dependencies", "d7/df0/doc_amyoc_dep.html#sub_amyoc_guide_spec_dep_yocto", null ]
      ] ],
      [ "7 Amba Build Dependency Graph", "d7/df0/doc_amyoc_dep.html#doc_amyoc_guide_amba_dep_graph", [
        [ "7.1 DSP Unit Test", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_amba_dsp", null ],
        [ "7.2 CV Unit Test", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_amba_cv", null ],
        [ "7.3 EazyAI", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_amba_eazyai", null ],
        [ "7.4 3A", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_amba_3a", null ],
        [ "7.5 Amba Private Kernel Drivers", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_amba_kernel", null ],
        [ "7.6 GStreamer", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_amba_gstreamer", null ],
        [ "7.7 Prebuild SW Packages", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_amba_prebuild", null ]
      ] ],
      [ "8 Yocto Build Dependency Graph", "d7/df0/doc_amyoc_dep.html#doc_amyoc_guide_yocto_dep_graph", [
        [ "8.1 DSP Unit Test", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_yocto_dsp", null ],
        [ "8.2 CV Unit Test", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_yocto_cv", null ],
        [ "8.3 EazyAI", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_yocto_eazyai", null ],
        [ "8.4 3A", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_yocto_3a", null ],
        [ "8.5 Amba Private Kernel Drivers", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_yocto_amba", null ],
        [ "8.6 Prebuild SW Packages", "d7/df0/doc_amyoc_dep.html#sub_amyoc_graph_yocto_prebuild", null ]
      ] ]
    ] ],
    [ "OSS Source Code Build by Amba Build", "d1/d51/doc_amyoc_oss.html", [
      [ "1 Download Packages: fetch_package.sh", "d1/d51/doc_amyoc_oss.html#doc_amyoc_guide_download_packages", null ],
      [ "2 Patch Package: exec_patch.sh", "d1/d51/doc_amyoc_oss.html#doc_amyoc_guide_patch_package", null ]
    ] ],
    [ "Yocto Recipe", "de/d89/doc_yocto_recipes.html", [
      [ "1. Class Files", "de/d89/doc_yocto_recipes.html#doc_yocto_rec_sec_class", null ],
      [ "2. Recipe Files", "de/d89/doc_yocto_recipes.html#doc_yocto_rec_sec_recipes", [
        [ "2.1 Add Package Dependencies", "de/d89/doc_yocto_recipes.html#sub_yocto_rec_pa", null ],
        [ "2.2 Add Inherited Classes", "de/d89/doc_yocto_recipes.html#sub_yocto_rec_in", null ],
        [ "2.3 Installation and Packaging", "de/d89/doc_yocto_recipes.html#sub_yocto_rec_and", null ]
      ] ],
      [ "3. Recipe Append Files", "de/d89/doc_yocto_recipes.html#doc_yocto_rec_sec_append", null ],
      [ "4. Patch Hotfix", "de/d89/doc_yocto_recipes.html#doc_yocto_rec_sec_patch", [
        [ "4.1 Typical Method of Yocto Patching", "de/d89/doc_yocto_recipes.html#sub_amyoc_hot_off", null ],
        [ "Method", "de/d89/doc_yocto_recipes.html#autotoc_md0", null ],
        [ "Advantages", "de/d89/doc_yocto_recipes.html#autotoc_md1", null ],
        [ "Disadvantages", "de/d89/doc_yocto_recipes.html#autotoc_md2", null ],
        [ "4.2 Customized Patching Method", "de/d89/doc_yocto_recipes.html#sub_amyoc_hot_cus", null ],
        [ "Method", "de/d89/doc_yocto_recipes.html#autotoc_md3", null ],
        [ "Advantages", "de/d89/doc_yocto_recipes.html#autotoc_md4", null ],
        [ "Disadvantages", "de/d89/doc_yocto_recipes.html#autotoc_md5", null ],
        [ "Example", "de/d89/doc_yocto_recipes.html#autotoc_md6", null ]
      ] ],
      [ "5. Examples of Recipe Files", "de/d89/doc_yocto_recipes.html#doc_yocto_rec_sec_example", [
        [ "Example 1. Build library", "de/d89/doc_yocto_recipes.html#append_rec_exa_1", null ],
        [ "Example 2. Build application", "de/d89/doc_yocto_recipes.html#append_rec_exa_2", null ],
        [ "Example 3. Install prebuild libraries", "de/d89/doc_yocto_recipes.html#append_rec_exa_3", null ],
        [ "Example 4. Compile cJSON by adding the wrapper for cmake", "de/d89/doc_yocto_recipes.html#append_rec_exa_4", null ],
        [ "Example 5. Build kernel modules", "de/d89/doc_yocto_recipes.html#append_rec_exa_5", null ]
      ] ],
      [ "6. Yocto Meta Layers", "de/d89/doc_yocto_recipes.html#yocto_meta_layers", [
        [ "6.1 Ambarella Meta Layers", "de/d89/doc_yocto_recipes.html#ambarella_meta_layers", null ],
        [ "6.2 OSS Meta Layers", "de/d89/doc_yocto_recipes.html#oss_meta_layers", null ]
      ] ],
      [ "7. Commerial Third-Party Libraries", "de/d89/doc_yocto_recipes.html#doc_yocto_rec_sec_commerial_3rd_party", null ],
      [ "8. Single Package with Multiple Sub-Packages", "de/d89/doc_yocto_recipes.html#doc_yocto_rec_sec_single_multi_sub", [
        [ "8.1 Introduction", "de/d89/doc_yocto_recipes.html#doc_yocto_sub_single_introduction", null ],
        [ "8.2 Add Sub-Packages to Source Package Installation", "de/d89/doc_yocto_recipes.html#doc_yocto_sub_single_guide", null ]
      ] ],
      [ "9. The Difference of Big OSS Modules", "de/d89/doc_yocto_recipes.html#doc_yocto_rec_difference_3rd_party", null ]
    ] ],
    [ "Yocto FAQ", "d9/de1/doc_yocto_faq.html", [
      [ "Question 1: What are the Yocto official documents to learn?", "d9/de1/doc_yocto_faq.html#yocto_faq1", null ],
      [ "Question 2: Which is better: Yocto or Buildroot?", "d9/de1/doc_yocto_faq.html#yocto_faq2", null ],
      [ "Question 3: Can customers download and use Poky from the Yocto community?", "d9/de1/doc_yocto_faq.html#yocto_faq3", null ],
      [ "Question 4: Can customers download and use the Linux kernel from the community?", "d9/de1/doc_yocto_faq.html#yocto_faq4", null ],
      [ "Question 5: How does the Cooper SDK Yocto build manage the OSS supported by Yocto Poky?", "d9/de1/doc_yocto_faq.html#yocto_faq5", null ],
      [ "Question 6: What is the main difference between Yocto compilation and regular compilation?", "d9/de1/doc_yocto_faq.html#yocto_faq6", null ],
      [ "Question 7: How does Yocto export environment variables?", "d9/de1/doc_yocto_faq.html#yocto_faq7", null ],
      [ "Question 8: What are the common Yocto commands?", "d9/de1/doc_yocto_faq.html#yocto_faq8", null ],
      [ "Question 9: Which configuration files should users pay attention to in Yocto build?", "d9/de1/doc_yocto_faq.html#yocto_faq9", null ],
      [ "Question 10: How are variables used in Yocto?", "d9/de1/doc_yocto_faq.html#yocto_faq10", null ],
      [ "Question 11: How can shared files be included in Yocto?", "d9/de1/doc_yocto_faq.html#yocto_faq11", null ],
      [ "Question 12: How does Yocto build function under network file system (NFS)?", "d9/de1/doc_yocto_faq.html#yocto_faq12", null ],
      [ "Question 13: Where is the Yocto directory structure defined?", "d9/de1/doc_yocto_faq.html#yocto_faq13", null ],
      [ "Question 14: What do downloads and sstate-cache have?", "d9/de1/doc_yocto_faq.html#yocto_faq14", null ],
      [ "Question 15: How can users establish local mirror servers to speed up the build?", "d9/de1/doc_yocto_faq.html#yocto_faq15", null ],
      [ "Question 16: What are the Yocto rules for getting source code and not recompiling?", "d9/de1/doc_yocto_faq.html#yocto_faq16", null ],
      [ "Question 17: How are official open source package compilation errors managed?", "d9/de1/doc_yocto_faq.html#yocto_faq17", null ],
      [ "Question 18: Why does the recipe file name of an external Linux module start with kernel-module-?", "d9/de1/doc_yocto_faq.html#yocto_faq18", null ],
      [ "Question 19: How can the compiler be prevented from creating symlinks", "d9/de1/doc_yocto_faq.html#yocto_faq19", null ],
      [ "Question 20: How is the error message \"ERROR: Please use a umask which allows a+rx and u+rwx\" resolved and managed?", "d9/de1/doc_yocto_faq.html#yocto_faq20", null ],
      [ "Question 21: How is the quality assurance (QA) issue [ldflags] resolved?", "d9/de1/doc_yocto_faq.html#yocto_faq21", null ],
      [ "Question 22: How is the QA issue [dev-so] resolved?", "d9/de1/doc_yocto_faq.html#yocto_faq22", null ],
      [ "Question 23: How is the QA issue [file-rdeps] resolved?", "d9/de1/doc_yocto_faq.html#yocto_faq23", null ],
      [ "Question 24: How is the QA issue [already-stripped] resolved?", "d9/de1/doc_yocto_faq.html#yocto_faq24", null ],
      [ "Question 25: How is the error message \"Error: Unable to find a match: <packagename>\" managed?", "d9/de1/doc_yocto_faq.html#yocto_faq25", null ],
      [ "Question 26: How are errors such as \"Error: Transaction test error\" managed?", "d9/de1/doc_yocto_faq.html#yocto_faq26", null ],
      [ "Question 27: How can the recipe be prepared so that the package can be recompiled at each time?", "d9/de1/doc_yocto_faq.html#yocto_faq27", null ],
      [ "Question 28: How are new user-customized tasks created?", "d9/de1/doc_yocto_faq.html#yocto_faq28", null ],
      [ "Question 29: How are local Yocto builds accelerated?", "d9/de1/doc_yocto_faq.html#yocto_faq29", null ],
      [ "Question 30: How is the fetcher issue \"Fetcher failure for URL: 'https://yoctoproject.org/connectivity.html'.\" resolved?", "d9/de1/doc_yocto_faq.html#yocto_faq30", null ],
      [ "Question 31: How is the error message \"meson: error: unrecognized arguments: --pkg-config-path\" in Ubuntu resolved?", "d9/de1/doc_yocto_faq.html#yocto_faq31", null ],
      [ "Question 32: How is the error message \"Transaction test error: file /usr/lib/systemd conflicts between attempted installs\" resolved?", "d9/de1/doc_yocto_faq.html#yocto_faq32", null ],
      [ "Question 33: How to prepare Yocto mirror and sstate-cache?", "d9/de1/doc_yocto_faq.html#yocto_faq33", null ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"d0/d1d/amyoc__main__page_8h.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';