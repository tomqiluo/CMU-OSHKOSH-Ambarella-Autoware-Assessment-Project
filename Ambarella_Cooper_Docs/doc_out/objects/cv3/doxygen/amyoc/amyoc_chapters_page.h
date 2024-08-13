/*!
 * @file doc_amyoc_int.h
 * @brief document for doxygen amyoc introduction
 * @version 1.o
 * @date 2023-12-26
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

/*!
 * @page doc_amyoc_introduction Introduction
 *
 * The build system is developed by Ambarella to support both Amba build and Yocto build.
 *
 * @section doc_amyoc_guide_feature 1 Main Features
 *
 * - Supports both Amba build and Yocto build with unified Makefile on Linux host.
 *   - Also supports wrapping the existing `Makefile / CMake / Autotools / Meson` into Makefile for the open source packages
 * - Supports both cross-compilation and native-compilation; supports automatic analysis of header files as compilation dependencies
 * - Provides template for compiling static libraries, shared libraries, and executables (inc.app.mk)
 *   - Supports mixed compilation of C (`*.c`) C++ (`*.cc` `*.cp` `*.cxx` `*.cpp` `*.CPP` `*.c++` `*.C`) and assembly (`*.S` `*.s` `*.asm`)
 * - Provides template for compiling external kernel modules (inc.mod.mk)
 *   - Supports mixed compilation of C (`*.c`) and assembly (`*.S`)
 * - Provides template for configuring parameters using Kconfig (`inc.conf.mk` / `kconfig.bbclass`)
 * - Provides script to automatically generate compilation chain (Kconfig / `auto.mk`) (`gen_build_chain.py`)
 *   - Supports checking the compilation time (time_statistics) of each package
 * - Provides script for configuring Yocto build (Kconfig / `ipcam-image.inc` / `prepare-patch.inc`) automatically (`gen_build_chain.py`)
 * - Supports real package rule (`amba.mk`) and virtual package rule (`amba.vdeps`); virtual package rule can be used to control a set of real package rules
 *   - Supports automatically generating normal structure (config), hierarchy (menuconfig), selection structure (choice)...
 *   - Supports automatically generating strong dependencies (depends on), weak dependencies (if... endif), strong selections (select), weak selections (imply)...
 *   - Supports prebuild strategy to speed up repeated compilation without building again from source code
 * - Enhances patching methods; users can choose whether or not to apply the patch (`exec_patch.sh` / `externalpatch.bbclass`)
 * - Supports generating the dependency graph (`gen_depends_image.sh`)
 * - Supports downloading packages from internet or mirror server for Amba build (`fetch_package.sh`)
 *   - Supports http / git / svn methods
 *   - Supports URL attributes: md5 for tar / zip, branch / rev / tag for git, rev for svn
 * - Supports build cache for Amba build; it can fetch the cached files from local path or mirror server directly without re-compilation (`inc.cache.mk process_cache.sh`)
 * - Supports generating cross-compiler toolchain for Amba build (`toolchain/Makefile process_machine.sh`)
 *
 * - - - -
 *
 * @section doc_amyoc_guide_arch 2 Architecture
 *
 * - Amba build composition:
 *   - The application and driver are Makefile + DEPS-statement
 *   - The packages are assembled through the dependencies defined by DEPS-statement (package name-level dependencies)
 * - Yocto build composition:
 *   - The application and driver are Makefile + Recipe
 *   - The packages are assembled through the dependencies defined by the Recipe (package name-level dependencies)
 * - DEPS-statement / Recipe are required only to define dependencies. Compilation is performed entirely by the Makefile
 *   Users can enter the package path and click `make` to compile it
 * - Implementation style:
 *   - Makefile / Recipe can be freely implemented by developers according to the Make / Yocto rules
 *   - Makefile only requires the three targets `all`, `clean`, and `install` to be defined, and provide templates to simplify the preparation for the Makefile.
 *   - Makefile can also be used to wrap the existing `Makefile / CMake / Autotools / Meson` implementations of the packages
 *   - DEPS-statement follows the assembly method of the `gen_build_chain.py` convention
 * - Separate from Amba build, the source code, compiled scripts, and configuration are all independent:
 *   - `gen_build_chain.py` analyses DEPS-statement and generates the compilation chain file automatically; all packages are compiled one by one
 *   - Kconfig must be placed in the same directory as the DEPS-statement file; users are not required to specify the parent-child inclusion relationship manually
 *     Instead, it is automatically analyzed and assembled by the script
 *   - Each package is supported to manage its own Kconfig
 * - `Convenience` of Yocto build:
 *   - Users can modify the configuration through `make menuconfig` (select or unselect packages, modify configuration, and more)
 *   - Build system wraps bitbake commands as make. It makes the build flow similar to Amba build for better user experience
 *
 * - - - -
 *
 * @section doc_amyoc_guide_diff 3 Differences Between Two Methods
 *
 * <table>
 * <caption id="yocto_difff_two_methods">Table 3-1. Differences Between Two Methods.</caption>
 * <tr><th> Topic                         <th> Amba-build                                        <th> Yocto-build
 * <tr><td> Build assembly rules          <td> Amba build is assembled by DEPS-statement
 *                                        <td> Yocto build is assembled the Recipe `DEPENDS / EXTRADEPS`
 * <tr><td> Package the root file system  <td> Amba build uses shell commands to package the root file system (rootfs) manually
 *                                        <td> Yocto build uses the bbclass to package rootfs automatically
 * <tr><td> Open oss package              <td> Amba build uses a prebuilt-oss compiled by Ambarella
 *                                        <td> Yocto build may download open source packages and compile them by
 *                                             itself (such as by using the busybox systemd)
 * <tr><td> Top-level output directory    <td> The top-level output directory of all packages in Amba build is fixed and the
 *                                             compilation, output, installation, and other directories are fixed
 *                                        <td> Each package in Yocto Build has its own top-level output directory and the
 *                                             compilation, output, installation, and other directories are located in this
 *                                             top-level output directory
 * <tr><td> Dependencies                  <td> Amba build searches for dependencies in a fixed directory
 *                                        <td> The Poky system is responsible for copying dependencies to the working directory
 *                                             of the current package. `ENV_INS_ROOT` and `ENV_DEP_ROOT` are not the same directory
 * <tr><td> Environment variables         <td> Amba build can export environment variables using the shell
 *                                        <td> The compilation environment of each package of Yocto build is independent from Host shell.
 *                                             Environment variables must be exported by recipe, which cannot be exported by host shell
 * <tr><td> Compilation tool              <td> Amba build uses the host-installed compilation tool
 *                                        <td> Yocto build has its own compilation tool chain; Yocto build may be required to specify
 *                                             the host depends (DEPENDS += "< package_name > -native")
 * </table>
 *
 * - - - -
 *
 * @section doc_amyoc_guide_system_structure_compilation 4 Directory Structure
 *
 * @par SDK directory structure (for Amba build)
 *
 * @image html amba-build-structure.png "Figure 4-1. SDK Directory Structure (for Amba Build)."
 *
 * @par SDK directory structure (for Yocto build)
 *
 * @image html yocto-build-structure.png "Figure 4-2. SDK Directory Structure (for Yocto Build)."
 *
 * @par Compilation project directory
 *
 * @code {.c}
 * ambarella/build
 * ├── core                         // Template of Makefile
 * │   ├── inc.env.mk               // Export template of compiling tool chain
 * │   ├── inc.ins.mk               // Template for installation
 * │   ├── inc.app.mk               // Template for compiling application
 * │   ├── inc.mod.mk               // Template for compiling external kernel module
 * │   ├── inc.cache.mk             // Template for compilation cache of Amba Build
 * │   └── inc.conf.mk              // Template of Kconfig
 * │
 * ├── bin
 * │   ├── common
 * │   │   ├── regex_deps.svg       // Picture of displaying DEPS-statement of Amba Build
 * │   │   ├── regex_incdeps.svg    // Picture of displaying INCDEPS-statement of Amba Build
 * │   │   ├── regex_vdeps.svg      // Picture of displaying VDEPS-statement
 * │   │   ├── gen_build_chain.py   // Script for generating compile chain
 * │   │   └── update_mks.py        // Tool for updating template of Makefile
 * │   ├── amba
 * │   │   ├── inc-amba-build.mk    // Top Makefile for Amba Build
 * │   │   ├── gen_depends_image.sh // Tool for generating the dependency graph
 * │   │   ├── exec_patch.sh        // Tool for patching or unpatching
 * │   │   ├── fetch_package.sh     // Tool for fetching package from internet or mirror server
 * │   │   ├── process_cache.sh     // Tool for supporting compilation cache
 * │   │   ├── process_machine.sh   // Tool for getting various machine-related informations
 * │   │   └── meson_cross.sh       // Tool for generating default config of meson cross-compilation
 * │   └── yocto
 * │       ├── inc-yocto-build.mk   // Top Makefile of Yocto Build
 * │       ├── gen_depends_image.sh // Tool for generating the dependency graph
 * │       └── run_user_task.sh     // Script to run tasks defined by user
 * │
 * ├── env
 * │   ├── amba-build.env           // Top environment script of Amba Build
 * │   ├── amba-build.mk            // Makefile to set environment when user compiles system in ambarella/boards/$board_name with Amba Build
 * │   ├── yocto-build.env          // Top environment script of Yocto Build
 * │   ├── yocto-ros2-build.env     // Top environment script of ROS2 Yocto Build
 * │   ├── common
 * │   │   ├── inc-get-boardinfo.sh // Script to get environment variables related to board
 * │   │   ├── inc-get-boardname.env// Script to get board name
 * │   │   ├── inc-amba-board.env   // Script to set environment variables related to board
 * │   │   └── inc-unset-env.env    // Script to clean environment exported by system
 * │   ├── amba
 * │   │   ├── inc-amba-build.env   // Script to set environment variables, such as directory, in Amba Build
 * │   │   ├── inc-check-host.sh    // Script to check environment of host and set thead count for compiling in Amba Build
 * │   │   └── inc-get-toolchain.sh // Script to get cross-compile toolchain in Amba Build
 * │   └── yocto
 * │       ├── inc-yocto-build.env  // Script to set environment variables, such as directory, in Yocto Build
 * │       ├── inc-prepare-ros.sh   // Script to set ROS2 metas
 * │       ├── inc-layer-ctrl.env   // Script to add and delete meta in Yocto Build
 * │       ├── inc-apply-patch.sh   // Script to add patch for Poky in Yocto Build
 * │       └── patch
 * │           ├── 0001-Disable-nfs-check-for-TMPDIR-file-system.patch // Yocto Build does not support compiling under NFS file system by default. This patch disables NFS check
 * │           └── 0001-Support-loading-kernel-config-in-the-external-path.patch // Yocto Build can support to load kernel config from external path
 * │
 * ├── kconfig                      // Kconfig, transplant from linux-5.18, and add the support of specifying path of "config/", ".config" and "config.h"
 * │
 * └── poky                         // Official Project of Yocto
 *
 * @endcode
 *
 * @par Amba build compiling output directory
 *
 * @code {.c}
 * ambarella/out/mirror-cache
 * ├── downloads                    // Folder for storing downloaded source codes
 * └── build-cache                  // Folder for storing compilation caches
 *
 * ambarella/out/amba_out/cv22_walnut // Top directory of compiling output for Amba Build
 * ├── config
 * │   ├── autoconfig
 * │   ├── .config                  // Compiling configuration file for system
 * │   ├── config.h                 // Header file of compiling configuration for system
 * │   ├── Kconfig                  // Kconfig generated by gen_build_chain.py automatically
 * │   ├── auto.mk                  // Makefile generated by gen_build_chain.py automatically
 * │   ├── DEPS                     // All package's dependencies parsed by gen_build_chain.py
 * │   ├── Target                   // All package's name and source path parsed by gen_build_chain.py
 * │   ├── depends                  // Folder for storing dependency images
 * │   └── time_statistics          // Statistic file of compiling time for each package
 * │
 * ├── objects                      // Top directory for cross-compilation output $(ENV_OUT_ROOT)
 * │   └── boards
 * │
 * ├── sysroot                      // Top directory for cross-compilation installation and dependency $(ENV_INS_ROOT), $(ENV_DEP_ROOT)
 * │   └── usr
 * │       ├── include
 * │       │   ├── ammem
 * │       │   │   └── memory.h
 * │       │   └── board            // Installation directory of each package's header file is $(ENV_INS_ROOT)/usr/include/$package_name
 * │       │       ├── board_config // System compiling configuration, copied from .config
 * │       │       ├── board_config.h // header file for system compiling configuration, copied from config.h
 * │       │       └── bsp.h
 * │       └── share
 * │           └── bsp
 * ├── objects-native               // Top directory for native-compilation output $(ENV_OUT_HOST)
 * │
 * ├── sysroot-native               // Top directory for native-compilation installation and dependency $(ENV_INS_HOST), $(ENV_DEP_HOST)
 * │
 * ├── fakeroot                     // contents from rootfs
 * │
 * └── images                       // output directory for all images
 *
 * @endcode
 *
 * @par Yocto build compiling output directory
 *
 * @code {.c}
 * ambarella/out/mirror-cache
 * ├── downloads                    // Folder for storing downloaded source codes
 * └── sstate-cache                 // Folder for storing compilation caches

 * ambarella/out/yocto_out/cv22_walnut // Top directory of compiling output for Amba Build
 * ├── conf
 * │   ├── local.conf               // Local configuration for Yocto Build, environment variable can be defined here
 * │   └── bblayers.conf            // Layer configuration for Yocto Build
 * │
 * ├── config
 * │   ├── autoconfig
 * │   ├── .config                  // Compile configuration file of system
 * │   ├── config.h                 // Header file for system compile configuration
 * │   ├── Kconfig                  // Kconfig generated by gen_build_chain.py automatically
 * │   ├── Target                   // All package's name and source path parsed by gen_build_chain.py
 * │   ├── prepare-patch.inc        // Package list of patch/unpatch and they are generated by gen_build_chain.py
 * │   ├── ipcam-image.inc          // Installation list of rootfs package and they are generated by gen_build_chain.py
 * │   └── depends                  // Folder for storing dependency images
 * │
 * ├── tmp
 * │ └── work
 * │     ├── cortexa53-crypto-poky-linux // Work directory of compiling for application and others
 * │     │   └── board              // Package name
 * │     │       └── 1.0-r0         // Version
 * │     │           ├── build      // Output directory of compiling $(OUT_PATH)
 * │     │           ├── image      // Top directory for installation $(ENV_INS_ROOT)
 * │     │           ├── recipe-sysroot // Top directory for dependency $(ENV_DEP_ROOT)
 * │     │           ├── recipe-sysroot-native // Top directory for corresponding tools of host
 * │     │           └── temp       // Storage directory for log file
 * │     │
 * │     ├── cv2x-poky-linux        // Compiling work directory for external core modules and rootfs
 * │     │   ├── kernel-module-ambvideo // Driver package name
 * │     │   └── ipcam-image        // Rootfs package name
 * │     │       └── 1.0-r0         // Version
 * │     │           └── rootfs     // Rootfs, similar to fakeroot of Amba Build
 * │     └── x86_64-linux           // Compiling work directory of host's tools
 * │
 * └── images                       // Output directory for all images
 *
 * @endcode
 *
 * @par Yocto build directory of compiling scripts
 *
 * @code {.c}
 *
 * ambarella/metadata
 * ├── meta-ambabsp                 // Kernel, image, driver, core tools and libraries
 * │   │
 * │   ├── classes                  // Directory of class layers
 * │   │   ├── ambaenv.bbclass      // Ambarella environment class, environment variables are exported here
 * │   │   ├── kconfig.bbclass      // Kconfig class of build system
 * │   │   ├── externalpatch.bbclass// External patch class, decides whether patches need to be applied or redo
 * │   │   ├── extrasrc.bbclass     // Class to append source files or directories to make task verification
 * │   │   └── weakdep.bbclass      // Weak output class for build system extension
 * │   │
 * │   ├── conf                     // Configuration directory for layers
 * │   │   ├── layout.conf          // Configuration file for layers, define how to search recipes
 * │   │   └── machine              // Configuration directory for machine
 * │   │       ├── cv2x.conf        // Configuration file for machine
 * │   │       └── include
 * │   │           ├── ambarella-common.inc // Common sub-configurations for machine
 * │   │           └── rootfs-type.inc // Configure rootfs type dynamically
 * │   │
 * │   ├── ...
 * │   ├── recipes-bsp              // Package directory of bsp's core
 * │   │   ├── boot
 * │   │   │   ├── boot.bb
 * │   │   │   └── boot.bbappend
 * │   │   └── ...
 * │   │
 * │   ├── recipes-core             // Package's directory of core
 * │   │   ├── images
 * │   │   │   └── ipcam-image.bb   // Image package to generate rootfs
 * │   │   └── prepare-patch
 * │   │       └── prepare-patch.bb // Prepare patch / unpatch
 * │   │
 * │   ├── recipes-devtools         // Package directory of host tools
 * │   │   └── kconfig-native
 * │   │       ├── kconfig-native.bb// Script of kconfig to compile build system
 * │   │       └── kconfig-native.bbappend // Specify source path and directory of compiling
 * │   │
 * │   ├── recipes-kernel
 * │   │   ├── linux-patch          // Linux decides to apply patch or not by checking config
 * │   │   └── linux
 * │   │       ├── linux-ambarella
 * │   │       │   ├── 001-linux-version-tweak.patch // kernel patch
 * │   │       │   ├── feature.scc  // kernel patch configuration
 * │   │       │   └── smp.cfg      // slice of kernel configuration
 * │   │       ├── linux-ambarella.bb // script to compile kernel
 * │   │       └── linux-ambarella.bbappend // set kernel's parameters, such as version, configuration file, and so on
 * │   │
 * │   ├── recipes-oss
 * │   │   ├── base-files
 * │   │   │   └── base-files_%.bbappend // Modification to system configuration file of rootfs
 * │   │   ├── busybox
 * │   │   │   └── busybox_%.bbappend // Modification to configuration of busybox
 * │   │   └── systemd
 * │   │       └── systemd_%.bbappend // Modification to configuration of systemd
 * │   │
 * │   ├── recipes-sensor
 * │   │   ├── kernel-module-os08a10
 * │   │   │   ├── kernel-module-os08a10.bb
 * │   │   │   └── kernel-module-os08a10.bbappend
 * │   │   └── ...
 * │   │
 * │   └── recipes-video
 * │       ├── kernel-module-ambvideo
 * │       │   ├── kernel-module-ambvideo.bb
 * │       │   └── kernel-module-ambvideo.bbappend
 * │       └── ...
 * │
 * ├── meta-ambalib                 // General library
 * ├── meta-ambaapp                 // Application and unit tests
 * └── meta-thirdparty              // Third-party open source libraries and tools
 *     ├── recipes-prebuild         // Ambarella prebuild OSS packages
 *     └── recipes-oss              // Public OSS packages
 * @endcode
 *
 * - - - -
 *
 */
/*!
 * @file doc_amyoc_target.h
 * @brief document for doxygen amyoc target build guidance
 * @version 1.o
 * @date 2023-12-26
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

/*!
 * @page doc_amyoc_target Target Build Guidance
 *
 * @section doc_amyoc_guide_build_normal_image 1 Firmware Image
 *
 * @subsection doc_guide_build_image_cv2x 1.1 CV2x Image Build
 * The following steps are using CV22 Walnut EVK as an example, users can replace cv22_walnut with other CV2x boardname,
 * such as cv25m_pinenut, cv2_chestnut.
 *
 * @par Build the cross-toolchain (optional)
 *
 * @code {.c}
 * ambarella$ sudo apt install texinfo gawk
 * ambarella$ source build/env/amba-build.env cv22_walnut
 * ambarella$ make -C build/toolchain
 * ambarella$ export ENV_BUILD_TOOL=`pwd`/out/toolchain/cortex-a53-toolchain-gcc12.2.0-linux5.15/bin/aarch64-linux-gnu-
 * @endcode
 *
 * @par Amba build at the top folder (using CV22 Walnut EVK as an example)
 *
 * @code {.c}
 * ambarella$ source build/env/amba-build.env cv22_walnut
 * ambarella$ make ipcam_config
 * ambarella$ make
 * @endcode
 *
 * @par Amba build at the board folder (`ambarella/boards/cv22_walnut`)
 *
 * @code {.c}
 * ambarella/boards/cv22_walnut$ make ipcam_config
 * ambarella/boards/cv22_walnut$ make
 * @endcode
 *
 * @par Yocto build (using CV22 Walnut EVK as an example)
 *
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env cv22_walnut
 * ambarella/out/yocto_out/cv22_walnut$ make ipcam_config
 * ambarella/out/yocto_out/cv22_walnut$ make
 * @endcode
 *
 * @note
 *   - Environment configuration files for both Amba and Yocto build can be loaded in any SDK
 *     subdirectory: source `xxx/build/env/xxxx-build.env`.
 *   - Users can load environment configuration files, then select the board by index
 *   - The `ipcam_config` will be loaded by default if the configuration file is not specified and
 *     `.config` file does not exist in the compiling stage.
 *
 * @subsection doc_guide_build_image_cv5x 1.2 CV5x Image Build
 * The following steps are using CV5 Timn EVK as an example, users can replace cv5_timn with other CV5x boardname,
 * such as cv52_crco.
 *
 * @par Build the cross-toolchain (optional)
 *
 * @code {.c}
 * ambarella$ sudo apt install texinfo gawk
 * ambarella$ source build/env/amba-build.env cv5_timn
 * ambarella$ make -C build/toolchain
 * ambarella$ export ENV_BUILD_TOOL=`pwd`/out/toolchain/cortex-a53-toolchain-gcc12.2.0-linux5.15/bin/aarch64-linux-gnu-
 * @endcode
 *
 * @par Amba build at the top folder (using CV5 Timn EVK as an example)
 *
 * @code {.c}
 * ambarella$ source build/env/amba-build.env cv5_timn
 * ambarella$ make ipcam_config
 * ambarella$ make
 * @endcode
 *
 * @par Amba build at the board folder (`ambarella/boards/cv5_timn`)
 *
 * @code {.c}
 * ambarella/boards/cv5_timn$ make ipcam_config
 * ambarella/boards/cv5_timn$ make
 * @endcode
 *
 * @par Yocto build (using CV5 Timn EVK as an example)
 *
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env cv5_timn
 * ambarella/out/yocto_out/cv5_timn$ make ipcam_config
 * ambarella/out/yocto_out/cv5_timn$ make
 * @endcode
 *
 * @subsection doc_guide_build_image_cv3 1.3 CV3 Image Build
 * The following steps are using CV3 Dk_mini EVK as an example, users can replace cv3_dk_mini with other CV3 boardname,
 * such as cv3ad685bub, cv2hpcie.
 *
 * @par Build the cross-toolchain (optional)
 *
 * @code {.c}
 * ambarella$ sudo apt install texinfo gawk
 * ambarella$ source build/env/amba-build.env cv3_dk_mini
 * ambarella$ make -C build/toolchain
 * ambarella$ export ENV_BUILD_TOOL=`pwd`/out/toolchain/cortex-a53-toolchain-gcc12.2.0-linux5.15/bin/aarch64-linux-gnu-
 * @endcode
 *
 * @par Amba build at the top folder (using CV3 Dk_mini EVK as an example)
 *
 * @code {.c}
 * ambarella$ source build/env/amba-build.env cv3_dk_mini
 * ambarella$ make ipcam_config
 * ambarella$ make
 * @endcode
 *
 * @par Amba build at the board folder (`ambarella/boards/cv3_dk_mini`)
 *
 * @code {.c}
 * ambarella/boards/cv3_dk_mini$ make ipcam_config
 * ambarella/boards/cv3_dk_mini$ make
 * @endcode
 *
 * @par Yocto build (using CV3 Dk_Mini EVK as an example)
 *
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env cv3_dk_mini
 * ambarella/out/yocto_out/cv3_dk_mini$ make ipcam_config
 * ambarella/out/yocto_out/cv3_dk_mini$ make
 * @endcode
 *
 * @subsection doc_guide_build_image_cv72 1.4 CV72 Image Build
 * The following steps are using CV72 Xiezhi EVK as an example, users can replace cv72_xiezhi with other CV72 boardname,
 * such as cv72_gage.
 *
 * @par Build the cross-toolchain (optional)
 *
 * @code {.c}
 * ambarella$ sudo apt install texinfo gawk
 * ambarella$ source build/env/amba-build.env cv72_xiezhi
 * ambarella$ make -C build/toolchain
 * ambarella$ export ENV_BUILD_TOOL=`pwd`/out/toolchain/cortex-a53-toolchain-gcc12.2.0-linux5.15/bin/aarch64-linux-gnu-
 * @endcode
 *
 * @par Amba build at the top folder (using CV72 Xiezhi EVK as an example)
 *
 * @code {.c}
 * ambarella$ source build/env/amba-build.env cv72_xiezhi
 * ambarella$ make auto_nand_config
 * ambarella$ make
 * @endcode
 *
 * @par Amba build at the board folder (`ambarella/boards/cv72_xiezhi`)
 *
 * @code {.c}
 * ambarella/boards/cv72_xiezhi$ make auto_nand_config
 * ambarella/boards/cv72_xiezhi$ make
 * @endcode
 *
 * @par Yocto build (using CV72 Xiezhi EVK as an example)
 *
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env cv72_xiezhi
 * ambarella/out/yocto_out/cv72_xiezhi$ make auto_nand_config
 * ambarella/out/yocto_out/cv72_xiezhi$ make
 * @endcode
 *
 * - - - -
 *
 * @section doc_amyoc_guide_parameter_config 2 General Make Commands
 *
 * @par Commands to configure parameters
 *
 * <table>
 * <caption id="yocto_command_parameters">Table 2-1. Commands to Configure Parameters.</caption>
 * <tr><th> Comamnds                                  <th> Function
 * <tr><td> make menuconfig                           <td> Perform menuconfig for software packages (including AMBoot)
 * <tr><td> make xxx_config                           <td> Load specific software package config file
 * <tr><td> make xxx_saveconfig                       <td> Save current `.config` to config file xxx_config
 * <tr><td> make linux_menuconfig                     <td> Perform menuconfig for Linux kernel
 * <tr><td> make linux_defconfig                      <td> Apply default configuration for Linux kernel
 * </table>
 *
 * @par Directory structure of configuration files
 *
 * @code {.c}
 * ambarella/boards/cv22_walnut
 * ├── Makefile
 * ├── amba.kconf
 * ├── bsp
 * └── config
 *     ├── amba
 *     │   ├── ipcam_config         // Compilation configuration of Amba Build
 *     │   └── amboot
 *     │       └── amboot_config    // Amboot configuration of Amba Build
 *     ├── yocto
 *     │   ├── ipcam_config         // Compilation configuration of Yocto Build
 *     │   └── amboot
 *     │       └── amboot_config    // Amboot configuration of Yocto Build
 *     └── kernel
 *         └── xxx_kernel_config    // Compilation configuration of kernel
 * @endcode
 *
 * Example: configure <b>Max VIN Channel Number</b>
 *
 * @par For Cooper Amba build:
 * @code {.c}
 * build$ make menuconfig
 *   drv_modules  --->
 *     private  --->
 *       -*- ambvideo-header (drv_modules/private/video/dsp_v5)  --->
 *         (4)   Max VIN Channel Number
 * @endcode
 *
 * @par For Cooper Yocto build:
 * @code {.c}
 * build$ make menuconfig
 *   meta-ambabsp  --->
 *     recipes-video  --->
 *       -*- ambvideo-header (meta-ambabsp/recipes-video/ambvideo-header)  --->
 *         (4)   Max VIN Channel Number
 * @endcode
 *
 * - - - -
 *
 * @section doc_amyoc_guide_populate_sdk 3 Populate SDK Commands
 * Building the SDK installer for a standard SDK and populating the SDK image are the features
 * supported by Yocto Poky. Users can refer to below note for more information about populating SDK.
 *
 * Users must use Yocto Build to enable this function. Amba Build does not support this function.
 *
 * The sample commands for each chip family are as follows.
 *
 * @par Populate SDK for CV2x (using CV22 Walnut EVK as an example)
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env cv22_walnut
 * ambarella/out/yocto_out/cv22_walnut$ make ipcam_config
 * ambarella/out/yocto_out/cv22_walnut$ bitbake ipcam-image -c populate_sdk
 * @endcode
 *
 * @par Populate SDK for CV5x (using CV5 Timn EVK as an example)
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env cv5_timn
 * ambarella/out/yocto_out/cv5_timn$ make ipcam_config
 * ambarella/out/yocto_out/cv5_timn$ bitbake ipcam-image -c populate_sdk
 * @endcode
 *
 * @par Populate SDK for CV3 (using CV3 Dk_mini EVK as an example)
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env cv3_dk_mini
 * ambarella/out/yocto_out/cv3_dk_mini$ make ipcam_config
 * ambarella/out/yocto_out/cv3_dk_mini$ bitbake ipcam-image -c populate_sdk
 * @endcode
 *
 * @par Populate SDK for CV72 (using CV72 Xiezhi EVK as an example)
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env cv72_xiezhi
 * ambarella/out/yocto_out/cv72_xiezhi$ make auto_nand_config
 * ambarella/out/yocto_out/cv72_xiezhi$ bitbake ipcam-image -c populate_sdk
 * @endcode
 *
 * @note
 * - Building the SDK installer for extensible SDK (`bitbake ipcam-image -c populate_sdk_ext`) is
 *   not supported here, as the recipes in Cooper SDK are using "EXTERNALSRC", which is not
 *   currently supported in sdk_ext by Yocto Poky.
 * - For more information about populating SDK, users can refer to `https://docs.yoctoproject.org/4.0.11/singleindex.html#sdk-generation`.
 *
 * - - - -
 *
 * @section doc_amyoc_guide_other_commands 4 Other Make Commands
 *
 * <table>
 * <caption id="yocto_other_command">Table 4-1. Other Make Commands.</caption>
 * <tr><th> Comamnds                          <th> Function
 * <tr><td> make deps                         <td> Generate the compilation chain. This operation must be performed
 *                                                 when a new package is added or an old package is deleted
 * <tr><td> make clean (Yocto Build)          <td> Clean rootfs
 * <tr><td> make clean (Amba Build)           <td> Clean the compiling output, but maintain the system's compilation configuration
 * <tr><td> make distclean                    <td> Clean both the compling output and the system's compilation configuation
 * <tr><td> make \$(package)_clean            <td> Execute clean operations for the specified package
 * <tr><td> make \$(package)-deps             <td> Generate the dependency graph for the specified package
 * <tr><td> make all-deps                     <td> Generate the dependency graph for all software packages
 * <tr><td> make sdk_doc                      <td> Generate Doxgen documents and output them into `ambarella/out/doc_out/cv2x`
 * <tr><td> make makes                        <td> Update the Makefile template
 * <tr><td> make time_statistics (Amba Build) <td> Generate the statistics file for the compiling time of all packages
 * <tr><td> make \$(package)                  <td> Compile the given package. The dependency packages will be compiled automatically
 * <tr><td> make \$(package)_single (Amba Build)
 *                                            <td> Compile the given package and do not compile dependency packages
 * <tr><td> make \$(package)_\$(target) (Amba Build)
 *                                            <td> Compile the given target in the specified package;
 *                                                 dependent packages will be compiled automatically
 * <tr><td> make \$(package)_\$(target)_single (Amba build)
 *                                            <td> Compile the given target in the specified package and do not compile dependent packages
 * <tr><td> bitbake \$(package) -c \$(task) (Yocto Build)
 *                                            <td> Compile the single task in the specified package
 * <tr><td> make \$(package) c=\$(target) f=\$(makefile) (Yocto build)
 *                                            <td> Compile the single target in the specified package; the recipe should include `include ${THISDIR}/usertask.inc`
 * </table>
 *
 * @note
 *   - When a target of the package is specified in Amba build, it must be declared in <b>Other_Target_Names</b> of the DEPS-statement.
 *   - Targets of a single type exist with dependent packages.
 *   - Commands for building package targets in Yocto build cannot cover all cases. For more details, take reference from the Yocto official document.
 *
 * - - - -
 *
 */
/*!
 * @file doc_amyoc_ros2.h
 * @brief document for doxygen amyoc ros2
 * @version 1.o
 * @date 2023-12-26
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

/*!
 * @page doc_amyoc_ros2 ROS2 Image by Yocto Build
 *
 * ROS2 image is supported by the Yocto build only. Because the size of the ROS2
 * image is very big, the eMMC are usually used to store it.
 *
 * @par Example 1: Build ROS2 Image for CV22 Walnut EVK
 *
 * @code {.c}
 * ambarella$ source build/env/yocto-ros2-build.env cv22_walnut
 * ambarella/out/yocto_out/cv22_walnut$ make ipcam_emmc_config
 * ambarella/out/yocto_out/cv22_walnut$ make ros-image
 * @endcode
 *
 * @par Example 2: Build ROS2 Image for CV3 Dk_mini EVK
 *
 * CV3 Dk_mini board's storage media is a SPI NOR flash. Due to its size limitation,
 * the user must prepare a TF card for it to store the ROS2 Image's Rootfs.<br>
 * To set up the ROS2 Image, perform the following steps:
 *
 * 1. Modify the CV3 Dk_mini's device trees (DTS) file.
 * @code {.c}
 * ambarella$ vim ambarella/boards/cv3_dk_mini/bsp/cv3_dk_mini.dts
 * ...
 * //bootargs = "console=ttyS0 root=/dev/mtdblock5 rw rootfstype=jffs2 earlycon pci=nomsi";
 * bootargs = "console=ttyS0 noinitrd root=/dev/mmcblk0p1 rw rootfstype=ext4 rootwait";
 * ...
 * @endcode
 *
 * 2. Create a profile for the firmware to be programed to the SPI NOR flash.
 * @code {.c}
 * ambarella$ vim ambarella/boards/cv3_dk_mini/bsp/profile.ros2
 * IMAGE_FWPROG    := $(BIN_DIR)/fwp.bin
 *
 * IMAGE_0_NAME    := bst
 * IMAGE_0_FILE    := $(BIN_DIR)/bst.bin
 * IMAGE_0_ADDR    := -1
 * IMAGE_0_FLAG    := force raw
 *
 * IMAGE_1_NAME    := bld
 * IMAGE_1_FILE    := $(BIN_DIR)/bld.bin
 * IMAGE_1_ADDR    := -1
 * IMAGE_1_FLAG    := force raw
 *
 * IMAGE_2_NAME    := env
 * IMAGE_2_FILE    := $(BIN_DIR)/env.bin
 * IMAGE_2_ADDR    := -1
 * IMAGE_2_FLAG    := force
 *
 * IMAGE_3_NAME    := dtb
 * IMAGE_3_FILE    := $(BIN_DIR)/dtb.bin
 * IMAGE_3_ADDR    := -1
 * IMAGE_3_FLAG    := force
 *
 * IMAGE_4_NAME    := kernel
 * IMAGE_4_FILE    := $(BIN_DIR)/kernel.bin
 * IMAGE_4_ADDR    := $(KERNEL_RAM_START)
 * IMAGE_4_FLAG    := verify compressed
 * @endcode
 *
 * 3. Select the profile above .
 * @code {.c}
 * ambarella$ make ipcam_config
 * ambarella$ make menuconfig
 * meta-ambabsp  --->
 *   recipes-bsp  --->
 *     [*] ambfw (meta-ambabsp/recipes-bsp/boot)  --->
 *       AMBFW Configuration  --->
 *         [*] Build AMBFW
 *         (profile.ros2) Firmware Profile
 * @endcode
 *
 * 4. Set the CV3 Dk_mini's Rootfs type to 'EXT4'.
 * @code {.c}
 * ambarella$ make menuconfig
 * meta-ambabsp  --->
 *   recipes-bsp  --->
 *     [*] amrootfs (meta-ambabsp/recipes-bsp/amrootfs)  --->
 *       Linux Root File System (EXT4)  --->
 *
 * make linux_menuconfig   //Enable EXT4 support in kernel
 *   Device Drivers  --->
 *     <*> MMC/SD/SDIO card support  --->   //<*> to build into kernel, not <M>
 *       <*>   MMC block device driver
 *       <*>   Ambarella Media Processor SD/MMC Host Controller driver
 *       <*>   Secure Digital Host Controller Interface support
 *       <*>     SDHCI platform and OF driver helper
 *       <*>       SDHCI support for Ambarella DWC MSHC
 *   File systems  --->
 *     <*> The Extended 4 (ext4) filesystem   //<*> to build into kernel, not <M>
 *     [*]   Use ext4 for ext2 file systems
 *     [*]   Ext4 POSIX Access Control Lists
 *     [*]   Ext4 Security Labels
 * @endcode
 *
 * 5. Build the ROS2 image.
 * @code {.c}
 * ambarella$ make ros-image
 * @endcode
 * The generated firmware path: `ambarella/out/yocto_out/cv3_dk_mini/firmware/bst_bld_env_dtb_kernel.elf`<br>
 * The generated Rootfs path: `ambarella/out/yocto_out/cv3_dk_mini/images/ros-image-galactic-cv3x-XXXXXX.rootfs.ext4`
 *
 * 6. Prepared a TF card to format it to `EXT4`.
 * @code {.c}
 * board# fdisk -l   // Note: Use a CV72 board as an example to formate the TF card.
 * board# umount /sdcard/mmcblk1p1   // The device name will be effected by the hardware slot. Here is in slot 1.
 * board# mkfs.ext4 /dev/mmcblk1
 * @endcode
 *
 * 7. Create partitions on the TF card.
 * @code {.c}
 * board# fdisk /dev/mmcblk1
 * Welcome to fdisk (util-linux 2.35.1).
 * Changes will remain in memory only, until you decide to write them.
 * Be careful before using the write command.
 *
 * The device contains 'ext4' signature and it will be removed by a write command. See fdisk(8) man page and --wipe option for more details.
 *
 * Device does not contain a recognized partition table.
 * Created a new DOS disklabel with disk identifier 0x55843850.
 *
 * Command (m for help): p
 * Disk /dev/mmcblk1: 59.7 GiB, 64088965120 bytes, 125173760 sectors
 * Units: sectors of 1 * 512 = 512 bytes
 * Sector size (logical/physical): 512 bytes / 512 bytes
 * I/O size (minimum/optimal): 512 bytes / 512 bytes
 * Disklabel type: dos
 * Disk identifier: 0x55843850

 * Command (m for help): n
 * Partition type
 *    p   primary (0 primary, 0 extended, 4 free)
 *    e   extended (container for logical partitions)
 * Select (default p): p
 * Partition number (1-4, default 1): 1
 * First sector (2048-125173759, default 2048):
 * Last sector, +/-sectors or +/-size{K,M,G,T,P} (2048-125173759, default 125173759): +5G
 *
 * Created a new partition 1 of type 'Linux' and of size 5 GiB.
 *
 * Command (m for help): n
 * Partition type
 *    p   primary (1 primary, 0 extended, 3 free)
 *    e   extended (container for logical partitions)
 * Select (default p): p
 * Partition number (2-4, default 2):
 * First sector (10487808-125173759, default 10487808):
 * Last sector, +/-sectors or +/-size{K,M,G,T,P} (10487808-125173759, default 125173759):
 *
 * Created a new partition 2 of type 'Linux' and of size 54.7 GiB.
 *
 * Command (m for help): w
 * The partition table has been altered.
 * Calling ioctl() to re-read partition table.
 * [ 4587.885399]  mmcblk1: p1 p2
 * Syncing disks.
 * @endcode
 *
 * 8. Reboot the board used to format the TF card to ensure that the settings above take effect.
 * @code {.c}
 * board# reboot
 * board# fdisk -l
 * ......
 * Disk /dev/mmcblk1: 59.7 GiB, 64088965120 bytes, 125173760 sectors
 * Units: sectors of 1 * 512 = 512 bytes
 * Sector size (logical/physical): 512 bytes / 512 bytes
 * I/O size (minimum/optimal): 512 bytes / 512 bytes
 * Disklabel type: dos
 * Disk identifier: 0x55843850

 * Device         Boot    Start       End   Sectors  Size Id Type
 * /dev/mmcblk1p1          2048  10487807  10485760    5G 83 Linux
 * /dev/mmcblk1p2      10487808 125173759 114685952 54.7G 83 Linux
 * @endcode
 *
 * 9. Store the ROS2 image's Rootfs to the TF card.<br>
 * Put `ambarella/out/yocto_out/cv3_dk_mini/images/ros-image-galactic-cv3x-XXXXXX.rootfs.ext4`
 * under CV72 board's `/tmp/` folder.
 * @code {.c}
 * board# dd if=/tmp/ros-image-galactic-cv3x-XXXXXX.rootfs.ext4 of=/dev/mmcblk1p1
 * @endcode
 *
 * 10. Insert the TF card into cv3_dk_mini board.
 *
 * 11. Flash the generated firmware in step 5 to CV3 DK MINI board using the AmbaUSB program tool.
 * @code {.c}
 * ------ Report ------
 * bst:    success
 * bld:    success
 * env:    success
 * dtb:    success
 * kernel: success
 * @endcode
 *
 * 12. Reboot and the Rootfs in TF card will be recognized in device `/dev/mmcblk0p1`.
 * @code {.c}
 * [    1.181415] Waiting for root device /dev/mmcblk0p1...
 * [    1.254990] mmc0: new ultra high speed SDR104 SDXC card at address 59b4
 * [    1.261784] mmcblk0: mmc0:59b4 JC1S5 59.7 GiB
 * [    1.267337]  mmcblk0: p1 p2
 * [    1.281551] EXT4-fs (mmcblk0p1): mounted filesystem with ordered data mode. Opts: (null). Quota mode: disabled.
 * [    1.291695] VFS: Mounted root (ext4 filesystem) on device 179:1
 * @endcode
 *
 * @par Check ROS2
 *
 * @code {.c}
 * board # ping 10.0.0.1
 * board # source /usr/bin/ros_setup.sh
 * board # ros2 pkg list
 * action_msgs
 * actionlib_msgs
 * ament_index_cpp
 * ament_index_python
 * builtin_interfaces
 * ...
 * @endcode
 *
 * - - - -
 *
 */
/*!
 * @file doc_amyoc_env.h
 * @brief document for doxygen amyoc environment parameters
 * @version 1.o
 * @date 2023-12-26
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

/*!
 * @page doc_amyoc_genv Environment Parameters
 *
 * @section doc_amyoc_guide_environment_variable_amba_build 1 Export Env Parameters for Amba Build
 *
 * - Export environment parameters directly to the shell environment and Makefile. Take CV22 Walnut EVK for example:
 *
 * @code {.c}
 * ambarella$ source build/env/amba-build.env
 *  1: cv22_vision_plus
 *  2: cv22_walnut
 *  3: cv25_hazelnut
 *  4: cv25m_janus
 *  5: cv25m_pinenut
 *  6: cv28m_cashewnut
 *  7: cv2_chestnut
 *  8: cv2_dk
 *  9: cv3_dk_mini
 * 10: cv52_crco
 * 11: cv5_timn
 * 12: cv72_gage
 * 13: cv72_xiezhi
 * 14: s6lm_pineapple
 *
 * Please input the board number (1 ~ 14): 2
 * Host System: ubuntu 20.04.6 LTS (Focal Fossa)
 * ============================================================
 * KERNEL_VER       : 5.15
 * KERNEL_PV        : 120
 * KERNEL_SRC       : USER_AMYOC_SDK_FOLDER/ambarella/kernel/linux-5.15
 * KERNEL_OUT       : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/objects/kernel/linux-5.15
 * AMBA_BOARD       : cv22_walnut
 * AMBA_SOC_SERIES  : cv2x
 * AMBA_SOC         : cv22
 * AMBA_CPU_ARCH    : armv8-a
 * AMBA_DSP_ARCH    : v5
 * AMBA_IMG_ARCH    : cv2x
 * AMBA_CAVALRY_ARCH: cavalry_v2
 * ENV_MIRROR_URL   : http://yocto.ambarella.com/mirror/cooper_1.5
 * ============================================================
 * ============================================================
 * TOOLCHAIN    PATH: USER_TOOLCHAIN_FOLDER/cortex-a53-2022.08-gcc12.1-linux5.15
 * TOOLCHAIN    NANE: aarch64-linux-gnu-gcc
 * TOOLCHAIN VERSION: 12.1.1
 * ============================================================
 * ============================================================
 * ENV_BUILD_MODE   : external
 * ENV_BUILD_ARCH   : arm64
 * ENV_BUILD_TOOL   : USER_TOOLCHAIN_FOLDER/cortex-a53-2022.08-gcc12.1-linux5.15/bin/aarch64-linux-gnu-
 * ENV_BUILD_JOBS   : -j20
 * ENV_TOP_DIR      : USER_AMYOC_SDK_FOLDER/ambarella
 * ENV_MAKE_DIR     : USER_AMYOC_SDK_FOLDER/ambarella/build/core
 * ENV_TOOL_DIR     : USER_AMYOC_SDK_FOLDER/ambarella/build/bin
 * ENV_DOWN_DIR     : USER_AMYOC_SDK_FOLDER/ambarella/out/mirror-cache/downloads
 * ENV_CACHE_DIR    : USER_AMYOC_SDK_FOLDER/ambarella/out/mirror-cache/build-cache
 * ENV_TOP_OUT      : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut
 * ENV_OUT_ROOT     : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/objects
 * ENV_INS_ROOT     : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/sysroot
 * ENV_DEP_ROOT     : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/sysroot
 * ENV_IMG_ROOT     : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/images
 * ENV_CFG_ROOT     : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/config
 * ENV_OUT_HOST     : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/objects-native
 * ENV_INS_HOST     : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/sysroot-native
 * ENV_DEP_HOST     : USER_AMYOC_SDK_FOLDER/ambarella/out/amba_out/cv22_walnut/sysroot-native
 * ENV_FSANITIZE_OPTION : 0 // 0:close, 1:address, 2:thread, 3:leak, 4:undefined
 * ============================================================
 * @endcode
 *
 * - - - -
 *
 * @section doc_amyoc_guide_environment_variable_yocto_build 2 Export Env Parameters for Yocto Build
 *
 * - Export some environment parameters directly to the shell environment and Makefile. Take CV22 Walnut EVK for example:
 *
 * @code {.c}
 * ambarella$ source build/env/yocto-build.env
 *  1: cv22_vision_plus
 *  2: cv22_walnut
 *  3: cv25_hazelnut
 *  4: cv25m_janus
 *  5: cv25m_pinenut
 *  6: cv28m_cashewnut
 *  7: cv2_chestnut
 *  8: cv2_dk
 *  9: cv3_dk_mini
 * 10: cv52_crco
 * 11: cv5_timn
 * 12: cv72_gage
 * 13: cv72_xiezhi
 * 14: s6lm_pineapple
 *
 * Please input the board number (1 ~ 14): 2
 * ============================================================
 * ENV_TOP_DIR      : USER_AMYOC_SDK_FOLDER/ambarella
 * ENV_BUILD_MODE   : yocto
 * ENV_MAKE_DIR     : USER_AMYOC_SDK_FOLDER/ambarella/build/core
 * ENV_TOOL_DIR     : USER_AMYOC_SDK_FOLDER/ambarella/build/bin
 * ============================================================
 * ============================================================
 * KERNEL_VER       : 5.15
 * KERNEL_PV        : 120
 * AMBA_BOARD       : cv22_walnut
 * AMBA_SOC_SERIES  : cv2x
 * AMBA_SOC         : cv22
 * AMBA_CPU_ARCH    : armv8-a
 * AMBA_DSP_ARCH    : v5
 * AMBA_IMG_ARCH    : cv2x
 * AMBA_CAVALRY_ARCH: cavalry_v2
 * ENV_MIRROR_URL   : http://yocto.ambarella.com/mirror/cooper_1.5
 * ============================================================
 * @endcode
 *
 * - Self-defined variables in `local.conf`
 *
 * @code {.c}
 * ambarella$ cat out/yocto_out/cv22_walnut/conf/local.conf
 * ...
 * #### Ambarella Configuration Start ####
 *
 * # All Ambarella configurations are automatically generated from `yocto-build.env`; DO NOT EDIT.
 *
 * # Setting the machine in the "meta-xxx/conf/machine/"
 * MACHINE = "cv2x"
 *
 * # Setting the maximum number of threads BitBake simultaneously executes
 * BB_NUMBER_THREADS = "20"
 *
 * # Setting the save path of image
 * DEPLOY_DIR_IMAGE = "${TOPDIR}/images"
 *
 * # Setting the save path of downloads and sstate-cache
 * DL_DIR = "${TOPDIR}/../downloads"
 * SSTATE_DIR = "${TOPDIR}/../sstate-cache_cv2x"
 *
 * # Setting the mirror of downloads and sstate-cache
 * #BB_HASHSERVE = "http://yocto.ambarella.com:port"
 * SSTATE_MIRRORS = "file://.* http://yocto.ambarella.com/mirror/cooper_1.5/sstate-cache_cv2x/PATH;downloadfilename=PATH"
 * SOURCE_MIRROR_URL = "http://yocto.ambarella.com/mirror/cooper_1.5/downloads"
 * INHERIT += "own-mirrors"
 *
 * # Do not create symlinks oe-workdir/oe-logs in the src dir
 * EXTERNALSRC_SYMLINKS = ""
 *
 * # To avoid "ERROR: ... do_package_qa: QA Issue: File ... in package ... doesn't have GNU_HASH (didn't pass LDFLAGS?) [ldflags]"
 * # LINKER_HASH_STYLE = "sysv"
 *
 * # ffmpeg was skipped: because it has a restricted license 'commercial'. Which is not listed in LICENSE_FLAGS_ACCEPTED
 * LICENSE_FLAGS_ACCEPTED = "commercial"
 *
 * # Add host tool: crc32 mkpasswd
 * # Install crc32: sudo apt install libarchive-zip-perl
 * # Install mkpasswd: sudo apt install whois
 * HOSTTOOLS += "crc32 mkpasswd"
 *
 * # Setting the customized envionment variables of AMBA
 * ENV_TOP_DIR = "USER_AMYOC_SDK_FOLDER/ambarella"
 * ENV_BUILD_MODE = "yocto"
 * KERNEL_VER = "5.15"
 * AMBA_BOARD = "cv22_walnut"
 * AMBA_SOC_SERIES = "cv2x"
 * AMBA_SOC = "cv22"
 * AMBA_CPU_ARCH = "armv8-a"
 * AMBA_DSP_ARCH = "v5"
 * AMBA_IMG_ARCH = "cv2x"
 * AMBA_CAVALRY_ARCH = "cavalry_v2"
 *
 * #### Ambarella Configuration Finish ####
 * @endcode
 *
 * - Self-defined variables exported in `ambaenv.bbclass`
 *
 * @code {.c}
 * ambarella$ cat metadata/meta-ambabsp/classes/ambaenv.bbclass
 *
 * export ENV_TOP_DIR
 * export ENV_MAKE_DIR = "${ENV_TOP_DIR}/build/core"
 * export CONF_PATH = "${STAGING_BINDIR_NATIVE}"
 * export OUT_PATH = "${WORKDIR}/build"
 * export ENV_INS_ROOT = "${WORKDIR}/image"
 * export ENV_DEP_ROOT = "${WORKDIR}/recipe-sysroot"
 * export ENV_CFG_ROOT = "${TOPDIR}/config"
 * export ENV_INS_HOST = "${WORKDIR}/image/${WORKDIR}/recipe-sysroot-native"
 * export ENV_DEP_HOST = "${WORKDIR}/recipe-sysroot-native"
 * export ENV_BUILD_MODE
 *
 * export AMBA_BOARD
 * export AMBA_SOC_SERIES
 * export AMBA_SOC
 * export AMBA_CPU_ARCH
 * export AMBA_DSP_ARCH
 * export AMBA_IMG_ARCH
 * export AMBA_CAVALRY_ARCH
 * ...
 * @endcode
 *
 * @note
 *   In Yocto build, as environment variables of the host shell cannot be used directly by the BitBake task,
 *   self-defined environment variables should be exported by the configuration file.
 *
 * - - - -
 *
 * @section doc_amyoc_guide_environment_variable_description 3 Description of Env Parameters
 *
 * Environment variables of build system:
 * <table>
 * <caption id="yocto_env_var_build">Table 3-1. Environment Variables of Build System.</caption>
 * <tr><th> Variables         <th> Used in Method            <th> Description
 * <tr><td> ENV_BUILD_MODE    <td> Amba-build | Yocto-build  <td> Sets compiling mode; `external` is for Amba build, `yocto` is for Yocto build
 * <tr><td> ENV_BUILD_ARCH    <td> Amba-build                <td> Specifies ARCH of cross compiling for Linux module
 * <tr><td> ENV_BUILD_TOOL    <td> Amba-build                <td> Specifies the cross compiler prefix
 * <tr><td> ENV_BUILD_JOBS    <td> Amba-build                <td> Specifes how many CPU cores will be used to compile
 * <tr><td> ENV_TOP_DIR       <td> Amba-build | Yocto-build  <td> Root directory
 * <tr><td> ENV_MAKE_DIR      <td> Amba-build | Yocto-build  <td> Build templates directory
 * <tr><td> ENV_TOOL_DIR      <td> Amba-build | Yocto-build  <td> Build scripts directory
 * <tr><td> ENV_DOWN_DIR      <td> Amba-build                <td> Download directory of Amba build
 * <tr><td> ENV_CACHE_DIR     <td> Amba-build                <td> Cache directory of Amba build
 * <tr><td> ENV_MIRROR_URL    <td> Amba-build | Yocto-build  <td> The mirror server URL
 * <tr><td> ENV_TOP_OUT       <td> Amba-build                <td> Output root directory, including compile output, installation files, images, and more
 * <tr><td> ENV_OUT_ROOT      <td> Amba-build                <td> Compiling output directory when source code and compiled output are separated for cross-compilation
 * <tr><td> ENV_INS_ROOT      <td> Amba-build                <td> Root directory of installation files for cross-compilation
 * <tr><td> ENV_DEP_ROOT      <td> Amba-build                <td> Root directory of libraries and header files for searching for cross-compilation
 * <tr><td> ENV_IMG_ROOT      <td> Amba-build                <td> Output directory of images
 * <tr><td> ENV_CFG_ROOT      <td> Amba-build                <td> Output directory for global control of compiling system
 * <tr><td> ENV_OUT_HOST      <td> Amba-build                <td> Compiling output directory when source code and compiled output are separated for native-compilation
 * <tr><td> ENV_INS_HOST      <td> Amba-build                <td> Root directory of installation files for native-compilation
 * <tr><td> ENV_DEP_HOST      <td> Amba-build                <td> Root directory of libraries and header files for searching for native-compilation
 * </table>
 *
 * @note
 *  - Configure in this directory should not be used directly and the correct way is installing the global configuration
 *    to board_config and `board_config.h` by the board package.
 *  - Modification of Yocto's global configuration will not trigger the recompilation of packages that are dependent on global configuration.
 *    These packages that are dependent on the board package will be recompiled because the build system has set the recompiling operations
 *    forcibly when the global configuration is changed.
 *
 * Ambarella board environment variables:
 * <table>
 * <caption id="yocto_env_var_board">Table 3-2. Environment Variables of the Ambarella Board.</caption>
 * <tr><th> Variables         <th> Function
 * <tr><td> AMBA_BOARD        <td> Board name
 * <tr><td> AMBA_SOC_SERIES   <td> System on chip (Soc) series
 * <tr><td> AMBA_SOC          <td> System on chip (Soc) name
 * <tr><td> AMBA_CPU_ARCH     <td> CPU version
 * <tr><td> AMBA_DSP_ARCH     <td> Digital signal processor (DSP) version
 * <tr><td> AMBA_IMG_ARCH     <td> 3A image version
 * <tr><td> AMBA_CAVALRY_ARCH <td> Cavalry version
 * <tr><td> KERNEL_VER        <td> Kernel major and minor versions
 * <tr><td> KERNEL_PV         <td> Kernel patch version
 * <tr><td> KERNEL_SRC        <td> Kernel source patd
 * <tr><td> KERNEL_OUT        <td> Kernel output directory
 * </table>
 *
 * Yocto cache:
 * <table>
 * <caption id="yocto_env_yocto_cache">Table 3-3. Environment Variables of Yocto Cache.</caption>
 * <tr><th> Variables         <th> Function
 * <tr><td> SSTATE_DIR        <td> Cache of final output for Yocto build
 * <tr><td> DL_DIR            <td> Storage path of third-party packages that are downloaded by Yocto build
 * <tr><td> SSTATE_MIRRORS    <td> Cache network images for final output
 * <tr><td> SOURCE_MIRROR_URL <td> Third-party network images that are download by Yocto build
 * <tr><td> BUILD_CPUS        <td> Specify the number of CPUs for compilation
 * </table>
 *
 * @note
 * - For Yocto build, if customers want to modify their SSTATE_MIRRORS and SOURCE_MIRROR_URL,
 *   they should change `amba_mirror_url` in the `ambarella/build/env/common/inc-get-boardinfo.sh`,
 *   not modifying `local.conf` directly.</br>
 * - Users can specify the number of CPU for compilation by executing "export BUILD_CPUS=16".
 *   This is valid for both Yocto build and Amba build.
 *
 * - - - -
 *
 */
/*!
 * @file doc_amyoc_makefile.h
 * @brief document for doxygen amyoc makefile templates
 * @version 1.o
 * @date 2023-12-26
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

/*!
 * @page doc_amyoc_makefile Makefile Templates
 *
 * Each package must copy templates from the common directory `ambarella/build/core`
 * to their directory because the package can include internal templates, not just the common ones.
 *
 * @section doc_amyoc_guide_environment_template 1 Environment Template: inc.env.mk
 *
 * @par Description
 *
 *   - In Amba build, the function of this template is setting the compiling output directory <b>\$(OUT_PATH)</b> and
 *     exporting the cross compiling environment: ARCH CROSS_COMPILE, CC, CXX ...
 *   - In Yocto build, the output directory and cross compiling environment are set and exported by recipe.
 *
 * - Functions:
 *   - <b>$(call safe_copy,srcs and dst)</b>: do safe copy
 *   - <b>$(call link_hdrs)</b>: derive searching path in CFLAGS for header files
 *   - <b>$(call link_libs)</b>: derive searching path in LDFLAGS for linked libraries
 *   - <b>$(call prepare_sysroot)</b>: prepare dependency sysroot in the OUT_PATH directory
 *
 * - Variables:
 *   - <b>PACKAGE_NAME</b>: package name, it should be equal to package name in the DEPS-statement
 *     - PACKAGE_NAME does not need add suffix of "-native" in native-compilation
 *   - <b>PACKAGE_ID</b>: read-only unique package ID, the default value is equal to the value of PACKAGE_NAME
 *     - PACKAGE_ID adds suffix of "-native" in native-compilation
 *   - <b>INSTALL_HDR</b>: installing sub-directory under the include folder of header files, the default value is equal to the value of PACKAGE_NAME
 *   - <b>PACKAGE_DEPS</b>: depends of the package, it will be removed in the future
 *   - <b>SEARCH_HDRS</b>: searching sub-directories under the include folder, the default value is equal to the value of PACKAGE_DEPS
 *   - <b>OUT_PREFIX</b>: compiling output directory when source code and compiled output are separated
 *   - <b>INS_PREFIX</b>: root directory of installation files
 *   - <b>DEP_PREFIX</b>: root directory of libraries and header files for searching
 *   - <b>PATH_PREFIX</b>: root directory of host tools for searching
 *   - <b>OUT_PATH</b>: compilation output path
 *   - <b>EXPORT_HOST_ENV</b>: if the package has dependency on native-built packages, set it to y
 *   - <b>BUILD_FOR_HOST</b>: if the package is native-compiled, set it to y
 *   - <b>EXPORT_PC_ENV</b>: if the package uses pkg-config, set it to y
 *   - <b>PREPARE_SYSROOT</b>: if the package uses dependency sysroot under the OUT_PATH directory, set it to y
 *   - <b>LOGOUTPUT</b>: the default value is `1>/dev/null`, if it is set to space, it will print more infomation when using `inc.app.mk` or `inc.cache.mk`
 *
 * @par Example: cmake of wrapping cJSON
 * @code {.c}
 * PACKAGE_NAME = cjson
 * LOCAL_PATH= $(shell pwd)
 *
 * include $(ENV_MAKE_DIR)/inc.env.mk
 * MACHINE_SCRIPT = $(ENV_TOOL_DIR)/amba/process_machine.sh
 *
 * .PHONY: all clean install
 *
 * all:
 *   @mkdir -p $(OUT_PATH)
 *   @cd $(OUT_PATH) && \
 *    cmake $(LOCAL_PATH) -DENABLE_CJSON_UTILS=On -DENABLE_CJSON_TEST=Off $(shell $(MACHINE_SCRIPT) cmake_cross) -DCMAKE_INSTALL_PREFIX=$(ENV_INS_ROOT)/usr && \
 *    make
 *   @echo "Build $(PACKAGE_NAME) Done."
 *
 * clean:
 *   @rm -rf $(OUT_PATH)
 *   @echo "clean $(PACKAGE_NAME) Done."
 *
 * install:
 *   @cd $(OUT_PATH) && make install
 *   @rm -rf $(ENV_INS_ROOT)/usr/lib/pkgconfig $(ENV_INS_ROOT)/usr/lib/cmake
 * @endcode
 *
 * - - - -
 *
 * @section doc_amyoc_guide_installation_template 2 Installation Template: inc.ins.mk
 *
 * - The installation template is suitable for prebuild packages
 * - Supported target and corresponding variables to be set:
 *   - <b>install_libs</b>: library set to be installed
 *     - Users are required to configure the variable of library set <b>\$(INSTALL_LIBRARIES)</b> that will be installed.
 *     - When `inc.app.mk` is used to compile applications, libraries generated in compiling will be added
 *       to the LIB_TARGETS variable; INSTALL_LIBRARIES is set to <b>\$(LIB_TARGETS)</b> by default
 *     - The installation directory is <b>\$(INS_PREFIX)/usr/lib</b>
 *   - <b>install_base_libs</b>: library set to be installed
 *     - Users must configure the variable of the library set <b>\$(INSTALL_BASE_LIBRARIES)</b> that will be installed.
 *       This variable's default value is INSTALL_LIBRARIES
 *     - The installation directory is <b>\$(INS_PREFIX)/lib</b>
 *   - <b>install_bins</b>: executable binaries to be installed
 *     - Users are required to configure the variable of executable binaries <b>\$(INSTALL_BINARIES)</b> that will be installed
 *     - When `inc.app.mk` is used to compile applications, executable binaries generated in compiling will be
 *       added to the BIN_TARGETS variable; INSTALL_BINARIES is set to <b>\$(BIN_TARGETS)</b> by default
 *     - The installation directory is <b>\$(INS_PREFIX)/usr/bin</b>
 *   - <b>install_base_bins</b>: executable binaries to be installed
 *     - Users are required to configure the variable of executable binaries <b>\$(INSTALL_BASE_BINARIES)</b> that will be installed.
 *       This variable's default value is INSTALL_BINARIES
 *     - The installation directory is <b>\$(INS_PREFIX)/bin</b>
 *   - <b>install_hdrs</b>: header files to be installed
 *     - Users are required to configure the header file variable <b>\$(INSTALL_HEADERS)</b> that will be installed
 *     - Installing directory is <b>\$(INS_PREFIX)/usr/include/(INSTALL_HDR)</b>
 *   - <b>install_datas</b>: data files to be installed
 *     - Users are required to configure the data file variable <b>\$(INSTALL_DATAS)</b> that will be installed
 *     - The installation directory is <b>\$(INS_PREFIX)/usr/share</b>
 *   - <b>install_datas_xxx / install_to_dir_xxx / install_tofile_xxx</b>: data files that are installed to the specified directory
 *     - Data files to be installed are specified by INSTALL_DATAS_xxx / INSTALL_TODIR_xxx / INSTALL_TOFILE_xxx
 *     - The defined values consist of two parts: the last item ending with '/' is the target path to be installed; the
 *       rest are files to be installed.
 *     - install_datas_xxx's installation directory is <b>\$(INS_PREFIX)/usr/share$(last item of INSTALL_DATAS_xxx)</b>
 *     - install_todir_xxx's installation directory is <b>\$(INS_PREFIX)$(last item of INSTALL_TODIR_xxx)</b>
 *     - install_tofile_xxx's installation directory is <b>\$(INS_PREFIX)$(last item of INSTALL_TOFILE_xxx)</b>
 *
 * @par Examples: Makefile to create two empty files, testa, and testb
 *
 * @code {.c}
 * INSTALL_DATAS_test = testa testb /testa/testb
 * INSTALL_TODIR_test = testa testb /usr/local/bin
 * INSTALL_TOFILE_testa = testa /etc/a.conf
 * INSTALL_TOFILE_testb = testb /etc/b.conf
 *
 * all: install_datas_test install_todir_test install_tofile_testa install_tofile_testb
 * include $(ENV_MAKE_DIR)/inc.ins.mk
 * @endcode
 *
 * Tree view of installed files:<br>
 * @code {.c}
 * sysroot
 * ├── etc
 * │   ├── a.conf
 * │   └── b.conf
 * └── usr
 *     ├── local
 *     │   └── bin
 *     │       ├── testa
 *     │       └── testb
 *     └── share
 *         └── testa
 *             └── testb
 *                 ├── testa
 *                 └── testb
 * @endcode
 *
 * @par Example: `board/amba.mk`
 *
 * @code {.c}
 * PACKAGE_NAME = board
 *
 * include $(ENV_MAKE_DIR)/inc.env.mk
 *
 * G_CONF_PATH ?= $(ENV_TOP_OUT)/config
 * include $(G_CONF_PATH)/.config
 * DRAM_CONFIG = $(shell grep ^CONFIG_BOARD_VERSION $(G_CONF_PATH)/.config | \
 *                 sed -e s/^CONFIG_BOARD_VERSION_// | sed -e s/=y// | tr [:upper:] [:lower:])
 *
 * .PHONY : all clean install
 *
 * all:
 *   @echo "Build $(PACKAGE_NAME) Done."
 *
 * clean:
 *   @rm -f $(OUT_PATH)/$(AMBA_BOARD).dts
 *   @echo "Clean $(PACKAGE_NAME) Done."
 *
 * INSTALL_TOFILE_dt_s = $(OUT_PATH)/$(AMBA_BOARD).S /usr/share/bsp/$(AMBA_SOC)_devicetree.S
 * INSTALL_TOFILE_dt_dtb = $(OUT_PATH)/$(AMBA_BOARD)/.dtb /usr/share/bsp/$(AMBA_SOC)/_devicetree.dtb
 * INSTALL_TOFILE_ddr = $(AMBA_BOARD)/bsp/$(DRAM_CONFIG)/.ini /usr/share/bsp/$(AMBA_SOC)/_ddr_config.in
 * INSTALL_TOFILE_bsp_c = $(AMBA_BOARD)/bsp/bsp.c /usr/share/bsp/bsp.c
 * INSTALL_TOFILE_bsp_h = $(AMBA_BOARD)/bsp/bsp.h /usr/share/bsp/bsp.h
 * INSTALL_HEADERS = $(AMBA_BOARD)/bsp/\*.h
 * INSTALL_TOFILE_conf_c = $(G_CONFIG_PATH)/.config /usr/include/$(PACKAGE_NAME)/board_config
 * INSTALL_TOFILE_conf_h = $(G_CONFIG_PATH)/.config.h /usr/include/$(PACKAGE_NAME)/board_config.h
 * include $(ENV_MAKE_DIR)/inc.ins.mk
 *
 * install: install_tofile_dt_s install_tofile_dt_dtb install_tofile_ddr \
 *          install_tofile_bsp_c install_tofile_bsp_h install_hdrs \
 *          install_tofile_conf_c install_tofile_conf_h
 * @endcode
 *
 * @par Example: `prebuild/oss/armv8-a/liblua/amba.mk`
 *
 * @code {.c}
 *
 * #DEPS(amba.mk) prebuild-liblua(jobserver):
 *
 * PACKAGE_NAME = liblua
 *
 * INSTALL_LIBRARIES = usr/lib/\*
 * INSTALL_HEADERS = usr/include/liblua/\*
 *
 * .PHONY: all clean install
 *
 * all:
 * 	 @echo "Build $(PACKAGE_NAME) Done."
 *
 * include $(ENV_MAKE_DIR)/inc.ins.mk
 *
 * clean:
 * 	 @echo "Clean $(PACKAGE_NAME) Done."
 *
 * install: install_libs install_hdrs
 * @endcode
 *
 * - - - -
 *
 * @section doc_amyoc_guide_application_template 3 Application Template: inc.app.mk
 *
 * - The application template is suitable to compile libraries and executable binaries. It includes
 *   content for `inc.env.mk` and `inc.ins.mk`
 *
 * - Supported targets:
 *   - <b>LIBA_NAME</b>: the static library name in single library compilation
 *     - The file path of static libraries in compilation will be added into LIB_TARGETS
 *   - <b>LIBSO_NAME</b>: the dynamic library name in single library compilation
 *     - LIBSO_NAME can be set as LIBRARY_NAME MAJOR_VERSION MINOR_VERSION PATCH_VERSION, for example
 *       - LIBSO_NAME = libtest.so 1 2 3; dynamic library will be generated as libtest.so.1.2.3; symbol link libtest.so and libtest.so.1 will also be created
 *       - LIBSO_NAME = libtest.so 1 2; dynamic library will be generated as libtest.so.1.2; symbol link libtest.so and libtest.so.1 will also be created
 *       - LIBSO_NAME = libtest.so 1; dynamic library will be generated as libtest.so.1; symbol link libtest.so will also be created
 *       - LIBSO_NAME = libtest.so; dynamic library will be generated as libtest.so and no symbol link will be generated
 *     - If LIBSO_NAME has a version number, the default name will be libxxxx.so.x. The default value can be overwritten by specified LDFLAGS:
 *       - For example, LDFLAGS += -Wl,-soname=libxxxx.so
 *     - The file path of static libraries and symbol links will be added into LIB_TARGETS
 *   - <b>BIN_NAME</b>: the executable binary name in single binary compilation
 *     - Executable binaries will be added into LIB_TARGETS
 *
 * - Functions:
 *   - <b>$(eval $(call add-liba-build, name of static library, list of source files))</b>: create the compiling rules of static libraries
 *   - <b>$(eval $(call add-liba-build, name of static library, list of source files, list of dependent static library paths))</b>: create the compiling rules of static libraries
 *     - The contents of dependent static libraries will be appended to the generated static library
 *   - <b>$(eval $(call add-libso-build, name of dynamic library, list of source files))</b>: create the compiling rules of dynamic libraries
 *     - Dynamic library's name can be set as LIBRARY_NAME MAJOR_VERSION MINOR_VERSION PATCH_VERSION. For more details, take reference from LIBSO_NAME's description
 *   - <b>$(eval $(call add-libso-build, name of dynamic library, list of source files, parameters for link))</b>: create the compiling rules of dynamic libraries with links
 *   - <b>$(eval $(call add-bin-build, name of executable binary, list of source files))</b>: create the compiling rules of executable file
 *   - <b>$(eval $(call add-bin-build, name of executable binary, list of source files, parameters for link))</b>: create the compiling rules of the executable files with link parameters
 *   - <b>$(call extract_obj, name of flag, list of source files, value of flag)</b>: add compiling flag for specified source file separately
 *     - Example: $(call set_flags, CFLAGS, main.c src/read.c src/write.c, -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE)
 *
 * @note
 *   The functions above are provided because multiple libraries and / or executable binaries can be compiled in a Makefile.
 *
 * - Variables that can be set:
 *   - <b>SRC_PATH</b>: directory of source files in the package. By default, source files of a package are located in root directory. Some package' source files are placed in SRC
 *     - Multiple directories of a package's source files can be specified: SRC_PATH = src1 src2 src3
 *   - <b>IGNORE_PATH</b>: directories that will be ignored when source files are searched. By default, directories with names ending in `.git`, scripts, and output are ignored
 *   - <b>REG_SUFFIX</b>: specifies the suffix source files when they are searched. By default, source files with suffixes of c, cpp, and S will be searched
 *     - <b>Suffixes</b> can be choosen from the environment variables of <b>c</b>, <b>CPP_SUFFIX</b>, and <b>ASM_SUFFIX</b>
 *       - <b>CPP_SUFFIX</b>: suffixes of C++ source files. The default suffixes are cc, cp, cxx, cpp, CPP, c++, and C
 *       - <b>ASM_SUFFIX</b>: suffixes of assembly source files. The default suffixes are S, s, and asm
 *     - Example - add support of cxx type, which is defined in CPP_SUFFIX:
 *     @code {.c}
 *     REG_SUFFIX = c cpp S cxx
 *     include $(ENV_MAKE_DIR)/inc.app.mk
 *     @endcode
 *     - Example - add support of CXX type, which has not been defined in CPP_SUFFIX:
 *     @code {.c}
 *     REG_SUFFIX = c cpp S CXX
 *     CPP_SUFFIX = cc cp cxx cpp CPP c++ CXX
 *     include $(ENV_MAKE_DIR)/inc.app.mk
 *     $(eval $(call compile_obj, CXX, $$(CXX)))
 *     @endcode
 *   - <b>USING_CXX_BUILD_C</b>: source files that end with `.c` are compiled by the CXX compiler when this variable is set to 'y'
 *   - <b>SRCS</b>: all source files. By default, it contains all files end with .c, .cpp, and .S that are located in SRC_PATH
 *     - If the user specifies SRCS, SRC_PATH can also be set and "include" directories will be added to header searching directories.
 *     - If the user specifies SRCS, IGNORE_PATH will be ignored.
 *   - <b>CFLAGS</b>: users can set some global compiling flags for the package (used for gcc and g++ commands)
 *   - <b>AFLAGS</b>: users can set some global assembly flags for the package (usedas a command)
 *   - <b>LDFLAGS</b>: users can set some global linking flags for packages
 *   - <b>CFLAGS_xxx.o</b>: users can set the compiling flags for specified source files separately
 *   - <b>AFLAGS_xxx.o</b>: users can set the compiling flags for specified assembly files separately
 *   - <b>DEBUG</b>: the compiling parameters of "-O0 -g -ggdb" will be used when this variable is set to 'y'
 *
 * - Example: <em> `packages/libmcl/dsp_v5/amba.mk` </em>
 * @code {.c}
 * PACKAGE_NAME = libmcl
 * PACKAGE_DEPS = liblua generic-header ambvideo-header
 *
 * MCL_VER_PREFIX = MCL
 * MCL_VERSION_FILE = mcl_version.c
 * MCL_SO_VER_MAJOR  := $(shell awk '/define $(MCL_VER_PREFIX)_LIB_MAJOR/{print $$3}' $(MCL_VERSION_FILE))
 * MCL_SO_VER_MINOR  := $(shell awk '/define $(MCL_VER_PREFIX)_LIB_MINOR/{print $$3}' $(MCL_VERSION_FILE))
 * MCL_SO_VER_PATCH  := $(shell awk '/define $(MCL_VER_PREFIX)_LIB_PATCH/{print $$3}' $(MCL_VERSION_FILE))
 *
 * LIBA_NAME = libmcl.a
 * LIBSO_NAME = libmcl.so $(MCL_SO_VER_MAJOR) $(MCL_SO_VER_MINOR) $(MCL_SO_VER_PATCH)
 * INSTALL_HEADERS = mcl.h
 * LDFLAGS += -llua
 *
 * .PHONY: all clean install
 *
 * all:
 * 	 @echo "Build $(PACKAGE_NAME) Done."
 *
 * include $(ENV_MAKE_DIR)/inc.app.mk
 *
 * all: $(LIB_TARGETS)
 *
 * clean: clean_objs
 * 	 @-rm -f $(LIB_TARGETS)
 * 	 @echo "Clean $(PACKAGE_NAME) Done."
 *
 * install: install_libs install_hdrs
 * @endcode
 *
 * - Example: <em> `unit_test/private/idsp_test/dsp_v5/amba.mk` </em>
 * @code {.c}
 * PACKAGE_NAME = idsp-test
 * PACKAGE_DEPS = generic-header ambvideo-header liblua libimgflow libimgalgo
 *
 * BIN_NAME = test_aaa_service
 * SRCS = test_aaa_service.c product_parse_lua.c custom_img_flow_op.c
 * LDFLAGS += $(patsubst %,-l%,imgflow imgalgo img_dsp_v5_dyn lua m pthread dl)
 *
 * .PHONY: all clean install
 *
 * all:
 * 	 @echo "Build $(PACKAGE_NAME) Done."
 *
 * include $(ENV_MAKE_DIR)/inc.app.mk
 *
 * all: $(BIN_TARGETS)
 *
 * clean: clean_objs
 * 	 @-rm -f $(BIN_TARGETS)
 *   @echo "Clean $(PACKAGE_NAME) Done."
 *
 * install: install_bins
 * @endcode
 *
 * - Example: <em> `unit_test_private/iav_test/dsp_v5/amba.mk` </em>
 * @code {.c}
 * PACKAGE_NAME = iav-test
 * PACKAGE_DEPS = generic-header ambvideo-header
 * ## test_encode test_decode test_hevc_scalelist test_transcode test_multi_chan test_vin test_vin_cap
 * PACKAGE_DEPS += libmcl liblua
 * ## test_blur test_frame_sync test_efm
 * PACKAGE_DEPS += libiav-blur
 * ## test_privacymask
 * PACKAGE_DEPS += libutils prebuild-dewarp libiav-pm
 * ## test_efm
 * PACKAGE_DEPS += libiav-efm
 * ## test_mjpeg_filo test_stream test_stream_osd test_custom_pyramid test_img_scale test_yuvcap test_yuvcap_gpio
 * PACKAGE_DEPS += libdatatx
 * ## test_stream_osd
 * PACKAGE_DEPS += libtextinsert
 *
 * BOARD_CONFIG ?= $(ENV_DEP_ROOT)/usr/include/board/board_config
 * include $(BOARD_CONFIG)
 *
 * .PHONY: all clean install
 *
 * all:
 * 	@echo "Build $(PACKAGE_NAME) Done."
 *
 * include $(ENV_MAKE_DIR)/inc.app.mk
 *
 * largefile-cflags = -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE
 *
 * ### test_blur
 * test_blur-srcs = test_blur.c
 * test_blur-ldflags += $(patsubst %,-l%,iav_blur m)
 * $(eval $(call add-bin-build,test_blur,$(test_blur-srcs),$(test_blur-ldflags)))
 *
 * ...
 *
 * ### test_encode
 * test_encode-srcs = test_encode.c
 * test_encode-ldflags += $(patsubst %,-l%,mcl m dl)
 * $(eval $(call add-bin-build,test_encode,$(test_encode-srcs),$(test_encode-ldflags)))
 *
 * ### test_fast_efm
 * test_fast_efm-srcs = test_fast_efm.c
 * test_fast_efm-ldflags += $(patsubst %,-l%,pthread)
 * $(call set_flags,CFLAGS,$(test_fast_efm-srcs),$(largefile-cflags))
 * $(eval $(call add-bin-build,test_fast_efm,$(test_fast_efm-srcs),$(test_fast_efm-ldflags)))
 *
 * ### test_fastosd
 * test_fastosd-srcs = test_fastosd.c
 * $(eval $(call add-bin-build,test_fastosd,$(test_fastosd-srcs)))
 *
 * ...
 *
 * ### test_custom_vout
 * test_custom_vout-srcs = vout/test_custom_vout.c
 * test_custom_vout-ldflags += $(patsubst %,-l%,datatx)
 * $(call set_flags,CFLAGS,$(test_custom_vout-srcs),$(largefile-cflags))
 * $(eval $(call add-bin-build,test_custom_vout,$(test_custom_vout-srcs),$(test_custom_vout-ldflags)))
 *
 * all: $(BIN_TARGETS)
 *
 * clean: clean_objs
 * 	@-rm -f $(BIN_TARGETS)
 * 	@echo "Clean $(PACKAGE_NAME) Done."
 *
 * INSTALL_DATAS_bin = data/\*.bin /bin
 * INSTALL_DATAS_lua = scripts/$(AMBA_SOC)/\*.lua scripts/decode_scripts/\*.lua scripts/hevc_scalelist_scripts/\*.lua /ambarella/lua
 *
 * install: install_bins install_datas_bin install_datas_lua
 *
 * %: $(OUT_PATH)/%
 * 	@echo "Build $@ Done."
 *
 * @endcode
 *
 * - - - -
 *
 * @section doc_amyoc_guide_driver_template 4 Driver Template: inc.mod.mk
 *
 * - The application template is suitable to compile external kernel modules. It includes
 *   content for `inc.env.mk` and `inc.ins.mk`
 *
 * - Supported targets (for Makefile when KERNELRELEASE is empty):
 *   - <b>modules</b>: external kernel modules that will be compiled
 *   - <b>modules_clean</b>: cleans all output of compiling for kernel modules
 *   - <b>modules_install</b>: kernel modules that can be installed
 *     - The default installation path of external kernel modules is <b>\$(ENV_INS_ROOT)/lib/modules/<kernel_release>/extra</b>
 *   - <b>symvers_install</b>: installs `modules.symvers` to a specified location (this target is dependent on one of install_hdrs)
 *
 * - Variables that can be set (for Makefile when KERNELRELEASE is empty):
 *   - <b>MOD_MAKES</b>: users can specify some infomation in this module
 *   - <b>KERNEL_SRC</b>: directory of Linux kernel's source file (required)
 *   - <b>KERNEL_OUT</b>: directory of compiling output for Linux kernel (make -O KERN_OUT, required when kernel is compiled)
 *
 * - Supported target (for Kbuild when KERNELRELEASE is not empty):
 *   - <b>MOD_NAME</b>: module's name; can be multiple modules separated by space
 *
 * - Variables that can be set (for Kbuild when KERNELRELEASE is not empty):
 *   - <b>IGNORE_PATH</b>: directories that will be ignored when source files are searched. By default, directories with name ending in `.git`, scripts, and output are ignored
 *   - <b>SRCS</b>: all C source files and assembly files. By default, it contains all files that end with `.c` and `.S` in the current directory
 *   - <b>ccflags-y asflags-y ldflags-y</b>: parameters for compiling, assembling and linking, respectively
 *
 * - Function (for Kbuild when KERNELRELEASE is not empty):
 *   - <b>$(call translate_obj, list of source files)</b>: transforms names of source files to the standard KBUILD format with the suffix of `.o`
 *   - <b>$(call extract_obj, name of flag, list of source files, value of flag)</b>: adds compiling flag for specified source files separately
 *
 * - Example: <em> `drv_modules/private/video/dsp_v5/amba.mk` </em>
 * @code {.c}
 * PACKAGE_NAME  = kernel-module-ambvideo
 * PACKAGE_DEPS  = generic-header ambvideo-header firmware-ucode
 *
 * INSTALL_HEADERS := \
 * 		include/driver/vout_api.h \
 * 		include/driver/iav_utils.h \
 * 		include/driver/msg_print.h \
 * 		include/driver/specific/iav_config.h \
 * 		include/driver/specific/amba_arch_mem.h \
 * 		include/driver/specific/amba_arch_mem_lnx.h \
 * 		include/driver/vin_api.h \
 * 		include/driver/iav_event_notifier.h \
 * 		include/driver/vin_sensors.h
 *
 * all: modules
 * 	@echo "Build $(PACKAGE_NAME) Done."
 *
 * clean: modules_clean
 * 	@echo "Clean $(PACKAGE_NAME) Done."
 *
 * install: modules_install install_hdrs
 *
 * include $(ENV_MAKE_DIR)/inc.mod.mk
 * @endcode
 *
 * - Example: <em> `drv_modules/private/video/dsp_v5/Kbuild`  </em>
 * @code {.c}
 *
 * MOD_NAME     = iav dsp ambcma ambnl hwtimer imgproc
 *
 * include $(ENV_MAKE_DIR)/inc.mod.mk
 *
 * ccflags-y	+= \
 * 		-I$(src)/include \
 * 		-I$(src)/include/driver \
 * 		-I$(src)/include/driver/specific \
 * 		-I$(src)/include/uapi \
 * 		-I$(src)/include/uapi/specific
 *
 * # -----------------------------------------------------------------------------
 * # Kernel module: iav.ko
 * # -----------------------------------------------------------------------------
 * ccflags-y	+= -I$(src)/iav
 * iav_src		:= $(wildcard $(src)/iav/\*.c $(src)/iav/$(AMBA_SOC)/\*.c)
 * iav-y		:= $(call extract_obj,$(iav_src))
 *
 * # -----------------------------------------------------------------------------
 * # Kernel module: dsp.ko
 * # -----------------------------------------------------------------------------
 * ccflags-y	+= -I$(src)/dsp
 * dsp_src		:= $(wildcard $(src)/dsp/\*.c $(src)/dsp/$(AMBA_SOC)/\*.c)
 * dsp-y		:= $(call extract_obj,$(dsp_src))
 *
 * # -----------------------------------------------------------------------------
 * # Kernel module: ambcma.ko
 * # -----------------------------------------------------------------------------
 * ccflags-y	+= -I$(src)/ambcma
 * ambcma_src	:= $(patsubst %,ambcma/%,ambcma_drv.c ambcma_utils.c amb_dma_buf.c ama.c)
 * ambcma-y	:= $(call extract_obj,$(ambcma_src))
 *
 * # -----------------------------------------------------------------------------
 * # Kernel module: ambnl.ko
 * # -----------------------------------------------------------------------------
 * ccflags-y	+= -I$(src)/ambnl
 * ambnl_src	:= ambnl/ambnl_drv.c
 * ambnl-y	:= $(call extract_obj,$(ambnl_src))
 *
 * # -----------------------------------------------------------------------------
 * # Kernel module: hwtimer.ko
 * # -----------------------------------------------------------------------------
 * hwtimer_src	:= hw_timer/hw_timer.c
 * hwtimer-y	:= $(call extract_obj,$(hwtimer_src))
 *
 * # -----------------------------------------------------------------------------
 * # Kernel module: imgproc.ko
 * # -----------------------------------------------------------------------------
 * ccflags-y	+= -I$(src)/imgproc
 * imgproc_src	:= imgproc/imgproc_drv.c
 * imgproc-y	:= $(call extract_obj,$(imgproc_src))
 *
 * @endcode
 *
 * - Example: <em> `drv_modules/platform/vin/sensors/sony_imx274_mipi/amba.mk` </em>
 * @code {.c}
 * PACKAGE_NAME  = kernel-module-imx274-mipi
 * PACKAGE_DEPS  = generic-header ambvideo-header kernel-module-ambvideo
 *
 * all: modules
 * 	@echo "Build $(PACKAGE_NAME) Done."
 *
 * clean: modules_clean
 * 	@echo "Clean $(PACKAGE_NAME) Done."
 *
 * install: modules_install
 *
 * include $(ENV_MAKE_DIR)/inc.mod.mk
 * @endcode
 *
 * - Example: <em> `drv_modules/platform/vin/sensors/sony_imx274_mipi/amba.mk` </em>
 *
 * @code {.c}
 * MOD_NAME = imx274_mipi
 * SRCS = imx274.c
 *
 * include $(ENV_MAKE_DIR)/inc.mod.mk
 * @endcode
 *
 * - - - -
 *
 * @section doc_amyoc_guide_configuration_template 5 Configuration Template: inc.conf.mk
 *
 * The configuration template is suitable for packages to manage their on Kconfig, rather than
 * leaving them in the care of the board.
 *
 * - Supported targets:
 *   - <b>loadconfig</b>: loads default configuration
 *     - If `.config` does not exist, the configuration specified by DEF_CONFIG will load
 *   - <b>menuconfig</b>: graphical user interface (GUI) configuration tool
 *   - <b>syncconfig</b>: updates `.config` manually, then updates `config.h`
 *   - <b>cleanconfig</b>: cleans configuration files
 *   - <b>xxx_config</b>: selects xxx_config located in CONFIG_SAVE_PATH as the current configuration
 *   - <b>xxx_saveconfig</b>: saves current configuration to CONF_SAVE_PATH's xxx_config
 *   - <b>xxx_defconfig</b>: selects xxx_defconfig located in CONFIG_SAVE_PATH as the current configuration
 *   - <b>xxx_savedefconfig</b>: saves current configuration to CONF_SAVE_PATH's xxx_defconfig
 *
 * - The variables that can be set are as follows:
 *   - <b>OUT_PATH</b>: directory of compiling's output
 *   - <b>CONF_SRC</b>: directory of source file for the Kconfig tool; current is `build/kconfig`
 *   - <b>CONF_PATH</b>: directory of compiling's output for the Kconfig tool
 *   - <b>CONF_PREFIX</b>: sets variables for running configuration. The main two settings are as follows:
 *     - srctree=path_name</b>: in Kconfig, the relative directory of the "source" command to load other configurations is specified by srctree
 *       If srctree does not specify, the default directory is the one that runs conf / mconf
 *     - CONFIG_=""</b>: sets the prefix of each item in `.config` and `config.h`. If this variable is not set, the default prefix CONFIG_ is used
 *   - <b>CONFIG_HEADER</b>: sets the inclusion macro in config (such as #ifndef _XXX_CONFIG_H__). The default value is <b>__\$(PACKAGE_NAME)_CONFIG_H__</b>
 *     - The header file generated by Kconfig does not include "#ifdef xxx ... #define xxx ... #endif". This template adds this macro by sed command
 *   - <b>KCONFIG</b>: configuration file for parameters. The default is the package's Kconfig file
 *   - <b>CONF_SAVE_PATH</b>: configuration file's directory to fetch and save. The default is the package's configuration directory
 *   - <b>CONF_APPEND_CMD</b>: appended commands when the configuration changes
 *
 * - Example: <em> `boot/amboot/build/Makefile` </em>
 * @code {.c}
 * ...
 *
 * KCONFIG        = $(AMBOOT_TOPDIR)/AmConfig
 * CONF_SAVE_PATH = $(AMBOOT_TOPDIR)/defconfig
 * CONF_PREFIX    = srctree=$(AMBOOT_TOPDIR) CONFIG_=""
 * CONF_HEADER    = __AMBOOT_CONFIG_H__
 * OUT_PATH       = $(BUILD_DIR)
 * include $(ENV_MAKE_DIR)/inc.conf.mk
 * @endcode
 *
 * @note
 *   For Kconfig usage, users can also take reference from `build/bin/amba/inc-amba-build.mk` and `build/bin/yocto/inc-yocto-build.mk`.
 *   For these template make files (`inc.ins.mk`, `inc.app.mk`, `inc.mod.mk`), please include them after the target `all`.
 *
 * - - - -
 *
 */
/*!
 * @file doc_amyoc_dep.h
 * @brief document for doxygen amyoc generate dependency chain
 * @version 1.o
 * @date 2023-12-26
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

/*!
 * @page doc_amyoc_dep Generate Dependency Chain
 *
 * @section doc_amyoc_guide_command_usage_of_amba_build 1 Amba Build Command Option
 *
 * - `build/bin/amba/inc-amba-build.mk`
 *
 * @code {.c}
 * deps:
 * 	 @-mkdir -p $(OUT_PATH)
 * 	 @python3 $(ENV_TOOL_DIR)/common/gen_build_chain.py -m $(OUT_PATH)/auto.mk -k $(OUT_PATH)/Kconfig -t $(OUT_PATH)/Target -a $(OUT_PATH)/DEPS \
 *      -d amba.mk -c amba.kconf -v amba.vdeps -s $(ENV_TOP_DIR) -i $(IGNORE_DIRS) -l 5 -w $(KEYWORDS) -p 1
 * @endcode
 *
 * Command items in `gen_build_chain.py`:
 * <table>
 * <caption id="yocto_gen-py_amba">Table 1-1. Command Items in gen_build_chain.py of Amba Build.</caption>
 * <tr><th> Items                    <th> Function
 * <tr><td> -m <Makefile Path>       <td> Name of Makefile that was generated automatically in common compiling;<br>
 *                                        A top Makefile can be used to include sub Makefiles that was generated automatically. Then the all
 *                                        target can call <b>make \$(BUILD_JOBS) -s MAKEFLAGS=all_targets</b>;<br>
 *                                        to compile all packages by starting multi-thread.
 *                                        The jobserver must be specified before a package can begin in multi-thread compilation 
 * <tr><td> -k <Kconfig Path>        <td> Specifies the file path of all projects in which Kconfig is stored
 * <tr><td> -t <Target Path>         <td> Specifies the path of the file where the package name and source path list are stored
 * <tr><td> -a <Depend Path>         <td> Specifies the path of the file where the package dependency list is stored
 * <tr><td> -d <Search Depend Name>  <td> The name of the dependent file to be searched (containing the dependency rule statement).
 *                                        The dependency file can contain multiple dependencies
 * <tr><td> -c <Search Kconfig Name> <td> Name of configuration file for Kconfig that will be searched<br>
 *                                        Find the configuration file in the same directory as the dependent file. In the search process, the
 *                                        configuration file with the same suffix as name of package will be searched first, and then will search
 *                                        for the configuration file if it cannot be found
 * <tr><td> -v <Search Virtual Depend Name>
 *                                   <td> The name of virtual dependent file to be searched (containing the statements of the virtual dependent rule)
 * <tr><td> -s <Search Directories>  <td> Path for searching directories. Multiple directories are separated by commas
 * <tr><td> -i <Ignore Directories>  <td> Directories to be ignored. Dependent files in these specified direcotries will not be searched.
 *                                        Multiple directories can be specified by commas
 * <tr><td> -g <Go On Directories>   <td> Path for searching directories continuously. Multiple directories can be specified by commas;<br>
 *                                        The current directory's subdirectory will not be searched when "<Search Depend Name>" has been found or "<Go On Directories>" is not specified
 * <tr><td> -l <Max Layer Depth>     <td> Sets the maximum layer of menuconfig
 * <tr><td> -w <Keyword Directories> <td> Used for menuconfig. If the search path contains this directory, layer of this path is reduced by 1.
 *                                        Multiple directories can be specified by commas
 * <tr><td> -p <prepend Flag>        <td> Used for menuconfig. If no prefix for CONFIG_="" is set when the users run conf / mconf, this flag must set to 1 when the script runs
 * </table>
 *
 * - - - -
 *
 * @section doc_amyoc_guide_command_usage_of_yocto_build 2 Yocto Build Command Option
 *
 * - `build/bin/yocto/inc-yocto-build.mk`
 *
 * @code {.c}
 * deps: kconfig-native
 * 	 @mkdir -p $(shell dirname $(KCONFIG))
 * 	 @python3 $(ENV_TOOL_DIR)/common/gen_build_chain.py -k $(OUT_PATH)/Kconfig -t $(OUT_PATH)/Target \
 * 	   -c amba.kconf -v amba.vdeps -i $(IGNORE_DIRS) -l 3 -w $(KEYWORDS) -p 1 -u $(USER_METAS)
 *
 * CONF_APPEND_CMD = python3 $(ENV_TOOL_DIR)/common/gen_build_chain.py \
 * 					-t $(OUT_PATH)/Target -c $(CONFIG_PATH) \
 * 					-o $(IMAGE_PKG_PATH) -p $(PATCH_PKG_PATH) -i $(IGNORE_RECIPES) && \
 * ...
 * @endcode
 *
 * Command items in gen_build_chain.py:
 * <table>
 * <caption id="yocto_gen-py_yoc">Table 2-1. Command Items in gen_build_chain.py of Yocto Build.</caption>
 * <tr><th> Items                            <th> Function
 * <tr><td> -k <Kconfig Path>                <td> Specifies the file path of all projects in which Kconfig is stored. The normal build will also generate
 *                                                a target file in the same directory as Kconfig, in which all of a package's file paths, names, and dependencies are listed
 * <tr><td> -t <Target Path>                 <td> Specifies the path of the file where the package name and source path list are stored
 * <tr><td> -c <Search Kconfig Name>         <td> Same of the configuration file for Kconfig that will be searched;<br>
 *                                                To search the Kconfig configuration file, <b>\$(RECIPE_NAME).bbconfig</b> in the current directory has priority to be found
 *                                                If it cannot be found, the search path will transfer to what is specified by EXTERNALSRC of the bbappend file
 *                                                In the search process, the configuration file with the same suffix as the name of the package will be searched first, and
 *                                                then will search for the configuration file if it cannot be found
 * <tr><td> -v <Search Virtual Depend Name>   <td> The name of the virtual dependent file to be searched (containing the statements of the virtual dependent rule)
 * <tr><td> -i <Ignore Directories>           <td> Directories to be ignored. Dependent files in these specified direcotries will not be searched.
 *                                                 Multiple directories can be specified by commas
 * <tr><td> -l <Max Layer Depth>              <td> Sets the maximum layer of menuconfig
 * <tr><td> -w <Keyword Directories>          <td> Used for menuconfig. If the search path contains this directory, the layer of this path is reduced by 1.
 *                                                 Multiple directories can be specified by commas
 * <tr><td> -p <prepend Flag>                 <td> Used for menuconfig. If no prefix of CONFIG_="" is set when the users run conf / mconf, this flag must be set to 1 when the script runs
 * <tr><td> -u <User Metas>                   <td> Specifies the user layer in Yocto Build. Multiple layers are separated by commas. Only user-level packages perform dependency analysis
 * <tr><td> -o <Output Recipe Path>           <td> Specifies the path in which the package lists are stored
 * </table>
 *
 * - - - -
 *
 * @section doc_amyoc_guide_real_dependency_amba 3 Amba Build Regular Dependency
 *
 * - Real dependency information format: <b>$#DEPS(Makefile_Name) Target_Name(Other_Target_Names): Depend_Names</b>
 *
 * @htmlonly
 * <a href="../../real_dependency_amba_build.svg">
 * @endhtmlonly
 *
 * @image html real_dependency_amba_build.svg "Figure 3-1. Real Dependency Amba Build."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 *
 * - Dependency information format including sub-path: <b>#INCDEPS: Subdir_Names</b>
 *
 * @htmlonly
 * <a href="../../dependency_information_format_include_subpath.svg">
 * @endhtmlonly
 *
 * @image html dependency_information_format_include_subpath.svg "Figure 3-2. Dependency Information Format."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 *
 * - Format description:
 *   - <b>Makefile_Name</b>: the name of the Makefile to be run by make (can be empty). The "make" command can specify the Makefile when it runs <b>make -f Makefile_Name</b>
 *     - Makefile must contain three targets: all, clean, and install
 *     - The name of the Makeifle can include path (/). Searching sub-packages in sub-directories is supported. For example: test1/ or test2/wrapper.mk
 *     - "#INCDEPS" can search dependent files in sub-directories continously. Recursive is supported. For instance: #INCDEPS: test1 test2
 *   - <b>Target_Name</b>: current package's name ID
 *     - The keyword <em>ignore</em> is a special package name; it indicates that the package will be ignored
 *       It is used in searching operation to ignore the certain directory
 *   - <b>Other_Target_Names</b>: other targets of the current package. Multiple targets are separated by spaces
 *     - Targets with names of all, install, and clean in Other_Target_Names will be ignored
 *     - The keyword <em>prepare</em> is a special real target which indicates that "make prepare" must be run before performing "make" operation
 *       It is generally used to load the default configuration to `.config` when `.config` does not exist
 *     - The keyword <em>psysroot</em> is a special real target which indicates that "make psysroot" must be run before performing "make" operation
 *       - Then the package uses dependency sysroot under the OUT_PATH instead of `ENV_DEP_ROOT / ENV_DEP_ROOT` directory
 *     - The keyword <em>release</em> is a special real target which indicates that rootfs uses "make install" to install
 *       - If the release is not defined, rootfs will use "make install" to install
 *     - Keyword of <em>union</em> is a special virtual target and multiple packages can share the same Makefile
 *       - The target names of prepare, all, install, and clean are changed to Target_Name-prepare, Target_Name-all, Target_Name-install, and Target_Name-clean
 *       - Users can take reference from `ambarella/kernel/amba.mk` and `ambarella/kernel/linux-patch/amba.mk`
 *     - Keyword of <em>cache</em> is a special virtual target that indicates the package uses cache compilation
 *     - The keyword <em>jobserver</em> is a special virtual target which indicates that multi-thread compilation can be started by
 *       executing "export ENV_BUILD_JOBS=-j8" and adding <b>\$(ENV_BUILD_JOBS)</b> to the make command
 *       - Some packages's Makefile will not add the jobserver target when it includes the make command, such as the compilation of the external kernel module
 *   - <b>Depend_Names</b>: dependent packages' name ID of the current package. Multiple dependencies are separated by spaces
 *     - If circular dependence exists or dependency is not defined, the parsing operation will fail and error information will print on the screen:
 *       - For circular dependency: "ERROR: circular deps!"
 *       - For no definition of dependency: "ERROR: deps (%s) are not found!"
 *
 * @note
 *   The package's name ID (Target_Name Depend_Names) is a combination of lower-case letters, numbers, and underscores; Other_Target_Names has no such requirement.
 *
 * - - - -
 *
 * @section doc_amyoc_guide_real_dependency_yocto 4 Yocto Build Regular Dependency
 *
 * Yocto build dependencies are defined in recipe:
 * <table>
 * <caption id="yocto_recipe_class">Table 4-1. Yocto Build Dependencies.</caption>
 * <tr><th> Items             <th> Function
 * <tr><td> DEPENDS:          <td> Point dependent packages' name in the compiling stage;<br>
 *                                 Dependent packages of the machine (<b>\$(PACKAGE_NAME)-native</b>) may be
 *                                 required to be specified in Yocto, such as bash-native
 * <tr><td> RDEPENDS:${PN}    <td> Point dependent packages' name in the running stage. Dependent packages with dynamic
 *                                 libraries should be added into this variable
 *</table>
 *
 * - - - -
 *
 * @section doc_amyoc_guide_virtual_dependency 5 Virtual Dependency
 *
 * @par Virtual dependency format: <b>#VDEPS(Virtual_Type) Target_Name(Other_Infos): Depend_Names</b>
 *
 * @htmlonly
 * <a href="../../virtual_dependency_regex.svg">
 * @endhtmlonly
 *
 * @image html virtual_dependency_regex.svg "Figure 5-1. Virtual Dependency Regex."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 *
 * @par Format description
 *
 * - <b>Virtual_Type</b>: required; indicates a virtual package's type. Four types are now supported:
 *   - <b>menuconfig</b>: indicates to generate a menuconfig virtual package. All packages in the current directory (including sub-directories) have strong dependencies on this package
 *   - <b>config</b>: indicates to generate a config virtual package
 *   - <b>menuchoice</b>: indicates to generate a virtual package of choice. All packages in the current directory (including sub-directories) become sub-items of choice
 *   - <b>choice</b>: indicates to generate a virtual package of choice. Package lists are under Other_Infos become sub-item of choice
 * - <b>Virtual_Name</b>: required; name of the virtual package
 * - <b>Other_infos</b>: required for choice type; optional for others
 *   - For all types, a path item starting with '/' (optional) can appear; this indicates that it functions on the specified subdirectory, not on the current directory
 *     - For config and choice, the path item can be specified with a virtual path, for example, "/virtual" (virtual can be any word), where the virtual project is
 *       displayed under the current directory (not the parent directory)
 *   - For choice, package lists separated by spaces will become the choice's sub-item and the first package is the default-selected package
 *   - For menuchoice, default-selected package can be specified
 * - <b>Depend_Names</b>: optional, list of dependent items. The usage is basically the same with DEPS-statement, such as setting unselect, choice, and menuchoice.
 *   Select and imply are not supported
 *
 * @note
 *   A virtual dependency means that the package is not the actual package and will not be compiled. Virtual dependencies are only used to organize and manage actual packages.
 *   The rules for writing and using virtual packages are the same for normal and Yocto compilations.
 *
 * - - - -
 *
 * @section doc_amyoc_guide_special_dependencies 6 Special Dependency
 *
 * @subsection sub_amyoc_guide_spec_dep_virt_pkg 6.1 Virtual Package
 *
 *   - *depname: indicates that this dependent package is the virtual package with name depname. depname can also have the following special characters, which will
 *      continue to be parsed. For instance: *??depname
 *
 * @subsection sub_amyoc_guide_spec_dep_keyword 6.2 Keyword
 *
 * <table>
 * <caption id="yocto_recipe_keywords">Table 6-1. Special Dependency Keywords.</caption>
 * <tr><th> Keywords      <th> Function
 * <tr><td> finally       <td> Indicates that this package is the last to be compiled and is used to generate the file system and images.
 *                             This keyword is only used in strong dependencies for normal compilation
 * <tr><td> unselect      <td> Indicates that this package is not compiled (default n)
 * <tr><td> nokconfig     <td> Indicates that this package does not contain Kconfig configuration. When there are multiple packages in the same directory,
 *                             the Kconfig file for packages with Kconfig can be set to <b>\$(package_name).kconf</b>, while packages without Kconfig must be set nokconfig
 * </table>
 *
 * @subsection sub_amyoc_guide_spec_dep_spec_charactor 6.3 Special Character
 *
 * <table>
 * <caption id="yocto_recipe_special_character">Table 6-2. Special Character.</caption>
 * <tr><th> Character    <th> Function
 * <tr><td> !depname     <td> Indicates that this package conflicts with the depname package and they cannot be turned on at the same time (depends on !depname)
 * <tr><td> &depname     <td> Indicates that this package selects depname package weakly (imply depname). When this package is choosen, depname can also be selected. It can
 *                            be cancelled manually
 * <tr><td> &&depname    <td> Indicates that this package selects depname package strongly (select depname). When this package is choosen, depname can also be selected. It can
 *                            not be cancelled
 * <tr><td> ?depname     <td> Indicates that this package has weak dependency (do not install dynamic library) with depname. Weak dependency means that the package can be
 *                            compiled successfully even if the dependent package is not selected or does not exist
 * <tr><td> ??depname    <td> Similar to ?depname, ??depname indicates that this package has weak dependency (dynamic libraries are to be installed) with depname
 * <tr><td> depa|depb    <td> Indicates that this package has weak dependencies (do not install dynamic library) with depa, depb ... .
 *                            The package will be compiled successfully when at least one dependent package is selected
 * <tr><td> depa||depb   <td> Similar to depa|depb, this indicates that the package have weak dependency (dynamic libraries are to be installed) with depa, depb ...
 * <tr><td> & |          <td> & can be combined with | and indicates that one package has weak dependency with all real packages;<br>
 *                            Suitable for strongly selecting and has weak dependency with one of the pre-compiled and source packages;<br>
 *                            If the last '|' is omitted, the characters between "||" and "&" will be implicitly derived as <b>*build-\$(package_name) prebuild-\$(package_name) and package_name</b>;<br>
 *                            For example: &&||libtest will be implicitly derived as &&*build-libtest||prebuild-libtest||libtest<br>
 *                            For example: "&&*build-libtest||prebuild-libtest||libtest" indicates that the first existed package will be selected strongly and has weak dependency
 *                            with the other real packages
 * </table>
 *
 * @note
 *   - & can be used with ? and no combination order required. It indicates that the package is selected and has weak dependency. For example, "&&??depname": strongly selected and
 *     weak dependency; "??&depname": weak dependency and weak selected
 *   - If the word before | or || was omitted, it will be implicitly derived using the pre-compiled package or the source package. For example, ||libtest will be
 *     derived to prebuild-libtest||libtest
 *   - For general compilations, there is no difference for "? ??" or "| ||"
 *   - For Yocto build, the weak dependency of "? |" only sets DEPENDS, but "?? ||" will set <b>DEPENDS</b> and <b>DEPENDS:${PN}</b> at the same time
 *
 * @subsection sub_amyoc_guide_spec_dep_env_var 6.4 Environment Variable
 *
 * Environment variable:
 * <table>
 * <caption id="yocto_recipe_environment_variable">Table 6-3. Environment Variable.</caption>
 * <tr><th> Variable            <th> Function
 * <tr><td> ENVNAME=val1,val2   <td> Indicates that the value of the environment variable depended upon by this package is equal to val1 or val2
 * <tr><td> ENVNAME!=val1,val2  <td> Indicates that the value of the environment variable depended upon by this package is not equal to val1 and val2
 * </table>
 *
 * @subsection sub_amyoc_guide_spec_dep_yocto 6.5 Yocto Special Dependencies
 *
 * The special dependencies in Yocto are extended by Ambarella. In Amba build, special dependencies will set the element of Depend_Names in DEPS-statement.
 * For Yocto Build, they are assigned to EXTRADEPS of Recipe files.
 *
 * If a weak dependency exists in EXTRADEPS, "inherit weakdep" must be inherited. "*weakdep" class will parse config / .config that is used to
 * output the root directory. Then, it set <b>DEPENDS</b> and <b>DEPENDS:${PN}</b> by checking whether or not this item is selected.
 *
 * - - - -
 *
 * @section doc_amyoc_guide_amba_dep_graph 7 Amba Build Dependency Graph
 *
 * To make it easier for users to clearly find package dependencies, Ambarella has added a method
 * to generate a dependency graph, the details of the method are shown below:
 *
 * <b>gen_depends_image.sh</b> [para1]...[para4]
 *  - para1: Package name
 *  - para2: Path to the folder where the graphs are stored
 *  - para3: List of package names
 *    - Amba build: Path to the file where the package name and dependency list are
 *      stored (the path specified by -a in `gen_build_chain.py`)
 *    - Yocto build: Path to the file where package names and source paths are
 *      stored (the path specified by -t of `gen_build_chain.py`)
 *  - para4: Configuration file path
 *
 * <b>Instructions for generating graphs</b>:
 *  - Usage, make packagename-deps; output, `out_dir(top-level output directory)/config/depends`
 *  - Amba Build graph details
 * 	<table>
 * <caption id="amyoc_amba_dep_line">Table 7-1. Table Line Details.</caption>
 * <tr><th> Line           <th> Meaning
 * <tr><td> Solid lines    <td> Strong dependencies
 * <tr><td> Dashed lines   <td> Weak dependencies
 * <tr><td> Double line    <td> Either prebuild and srcbuild, or patch and unpatch
 * <tr><td> Green line     <td> The package is already selected in `.config`
 * <tr><td> Red line       <td> The package is not selected in `.config`
 *	</table>
 *
 *   <table>
 * <caption id="amyoc_amba_dep_box">Table 7-2. Box Color Details.</caption>
 * <tr><th> Box          <th> Meaning
 * <tr><td> Green box    <td> The package in `.config` is already selected
 * <tr><td> Red box      <td> The package is not selected in `.config`
 *	</table>
 *
 * @subsection sub_amyoc_graph_amba_dsp 7.1 DSP Unit Test
 *
 * @htmlonly
 * <a href="../../amba_iav-test.svg">
 * @endhtmlonly
 *
 * @image html amba_iav-test.svg "Figure 7-1. iav-test."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @image html amba_smartrc3-test.svg "Figure 7-2. smartrc3-test."
 * <br>
 * @image html amba_dewarp-test.svg "Figure 7-3. dewarp-test."
 * <br>
 * @image html amba_smartfb-test.svg "Figure 7-4. smartfb-test."
 * <br>
 * @image html amba_eis-test.svg "Figure 7-5. eis-test."
 * <br>
 *
 * @subsection sub_amyoc_graph_amba_cv 7.2 CV Unit Test
 *
 * @htmlonly
 * <a href="../../amba_cvflow-test.svg">
 * @endhtmlonly
 *
 * @image html amba_cvflow-test.svg "Figure 7-6. cvflow-test."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 * @image html amba_cv-test.svg "Figure 7-7. cv-test."
 * <br>
 *
 * @subsection sub_amyoc_graph_amba_eazyai 7.3 EazyAI
 *
 * @htmlonly
 * <a href="../../amba_eazyai-apps-test.svg">
 * @endhtmlonly
 *
 * @image html amba_eazyai-apps-test.svg "Figure 7-8. eazyai-apps-test."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 * @image html amba_libeazyai-arm-postprocess.svg "Figure 7-9. libeazyai-arm-postprocess."
 * <br>
 * @image html amba_libeazyai.svg "Figure 7-10. libeazyai."
 * <br>
 *
 * @htmlonly
 * <a href="../../amba_eazyai-unit-test.svg">
 * @endhtmlonly
 *
 * @image html amba_eazyai-unit-test.svg "Figure 7-11. eazyai-unit-test."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @subsection sub_amyoc_graph_amba_3a 7.4 3A
 *
 * @image html amba_idsp-test.svg "Figure 7-12. idsp-test."
 * <br>
 * @image html amba_libimgflow.svg "Figure 7-13. libimgflow."
 * <br>
 * @image html amba_libimgalgo.svg "Figure 7-14. libimgalgo."
 * <br>
 * @image html amba_ipc-imx274-datas.svg "Figure 7-15. ipc-imx274-datas."
 * <br>
 *
 * @subsection sub_amyoc_graph_amba_kernel 7.5 Amba Private Kernel Drivers
 *
 * @image html amba_kernel-module-ambvideo.svg "Figure 7-16. kernel-module-ambvideo."
 * <br>
 * @image html amba_kernel-module-ambcavalry.svg "Figure 7-17. kernel-module-ambcavalry."
 * <br>
 * @image html amba_kernel-module-max9296.svg "Figure 7-18. kernel-module-max9296."
 * <br>
 * @image html amba_kernel-module-imx274.svg "Figure 7-19. kernel-module-imx274."
 * <br>
 * @image html amba_kernel-module-imx274-mipi-brg.svg "Figure 7-20. kernel-module-imx274-mipi-brg."
 * <br>
 *
 * @subsection sub_amyoc_graph_amba_gstreamer 7.6 GStreamer
 *
 * @htmlonly
 * <a href="../../amba_libgstamba.svg">
 * @endhtmlonly
 *
 * @image html amba_libgstamba.svg "Figure 7-21. libgstamba."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../amba_libgstnnstreamer.svg">
 * @endhtmlonly
 *
 * @image html amba_libgstnnstreamer.svg "Figure 7-22. libgstnnstreamer."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../amba_gstd.svg">
 * @endhtmlonly
 *
 * @image html amba_gstd.svg "Figure 7-23. gstd."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../amba_gst-client.svg">
 * @endhtmlonly
 *
 * @image html amba_gst-client.svg "Figure 7-24. gst-client."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../amba_libgstd.svg">
 * @endhtmlonly
 *
 * @image html amba_libgstd.svg "Figure 7-25. libgstd.svg."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../amba_libgstc.svg">
 * @endhtmlonly
 *
 * @image html amba_libgstc.svg "Figure 7-26. libgstc."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @subsection sub_amyoc_graph_amba_prebuild 7.7 Prebuild SW Packages
 *
 * @image html amba_prebuild-alsa-plugins.svg "Figure 7-27. prebuild-alsa-plugins."
 * <br>
 * @image html amba_prebuild-alsa-utils.svg "Figure 7-28. prebuild-alsa-utils."
 * <br>
 * @image html amba_prebuild-pulseaudio.svg "Figure 7-29. prebuild-pulseaudio."
 * <br>
 *
 * - - - -
 *
 * @section doc_amyoc_guide_yocto_dep_graph 8 Yocto Build Dependency Graph
 *
 * <b>Instructions for generating graphs</b>:
 *  - Yocto Build graph details
 * 	<table>
 * <caption id="amyoc_yocto_dep_line">Table 8-1. Box Color Details.</caption>
 * <tr><th> Box          <th> Meaning
 * <tr><td> Green box    <td> The package in `.config` is already selected
 * <tr><td> Red box      <td> The package is not selected in `.config`
 * <tr><td> Blue box     <td> Package from communities such as Yocto
 *	</table>
 *
 * @subsection sub_amyoc_graph_yocto_dsp 8.1 DSP Unit Test
 *
 * @image html yocto_iav-test.svg "Figure 8-1. iav-test."
 * <br>
 *
 * @htmlonly
 * <a href="../../yocto_smartrc3-test.svg">
 * @endhtmlonly
 *
 * @image html yocto_smartrc3-test.svg "Figure 8-2. smartrc3-test."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @image html yocto_dewarp-test.svg "Figure 8-3. dewarp-test."
 * <br>
 * @image html yocto_smartfb-test.svg "Figure 8-4. smartfb-test."
 * <br>
 * @image html yocto_eis-test.svg "Figure 8-5. eis-test."
 * <br>
 *
 * @subsection sub_amyoc_graph_yocto_cv 8.2 CV Unit Test
 *
 * @htmlonly
 * <a href="../../yocto_cvflow-test.svg">
 * @endhtmlonly
 *
 * @image html yocto_cvflow-test.svg "Figure 8-6. cvflow-test."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @image html yocto_cv-test.svg "Figure 8-7. cv-test."
 * <br>
 *
 * @subsection sub_amyoc_graph_yocto_eazyai 8.3 EazyAI
 *
 * @htmlonly
 * <a href="../../yocto_eazyai-apps-test.svg">
 * @endhtmlonly
 *
 * @image html yocto_eazyai-apps-test.svg "Figure 8-8. eazyai-apps-test."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../yocto_libeazyai-arm-postprocess.svg">
 * @endhtmlonly
 *
 * @image html yocto_libeazyai-arm-postprocess.svg "Figure 8-9. libeazyai-arm-postprocess."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../yocto_libeazyai.svg">
 * @endhtmlonly
 *
 * @image html yocto_libeazyai.svg "Figure 8-10. libeazyai."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../yocto_eazyai-unit-test.svg">
 * @endhtmlonly
 *
 * @image html yocto_eazyai-unit-test.svg "Figure 8-11. eazyai-unit-test."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @subsection sub_amyoc_graph_yocto_3a 8.4 3A
 *
 * @image html yocto_idsp-test.svg "Figure 8-12. idsp-test."
 * <br>
 * @image html yocto_libimgflow.svg "Figure 8-13. libimgflow."
 * <br>
 * @image html yocto_libimgalgo.svg "Figure 8-14. libimgalgo."
 * <br>
 * @image html yocto_ipc-imx274-datas.svg "Figure 8-15. ipc-imx274-datas."
 * <br>
 *
 * @subsection sub_amyoc_graph_yocto_amba 8.5 Amba Private Kernel Drivers
 *
 * @image html yocto_kernel-module-ambvideo.svg "Figure 8-16. kernel-module-ambvideo."
 * <br>
 * @image html yocto_kernel-module-ambcavalry.svg "Figure 8-17. kernel-module-ambcavalry."
 * <br>
 * @image html yocto_kernel-module-max9296.svg "Figure 8-18. kernel-module-max9296."
 * <br>
 * @image html yocto_kernel-module-imx274.svg "Figure 8-19. kernel-module-imx274."
 * <br>
 * @image html yocto_kernel-module-imx274-mipi-brg.svg "Figure 8-20. kernel-module-imx274-mipi-brg."
 * <br>
 *
 * @subsection sub_amyoc_graph_yocto_prebuild 8.6 Prebuild SW Packages
 *
 * @htmlonly
 * <a href="../../yocto_prebuild-alsa-plugins.svg">
 * @endhtmlonly
 *
 * @image html yocto_prebuild-alsa-plugins.svg "Figure 8-21. prebuild-alsa-plugins."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../yocto_prebuild-alsa-utils.svg">
 * @endhtmlonly
 *
 * @image html yocto_prebuild-alsa-utils.svg "Figure 8-22. prebuild-alsa-utils."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * @htmlonly
 * <a href="../../yocto_prebuild-pulseaudio.svg">
 * @endhtmlonly
 *
 * @image html yocto_prebuild-pulseaudio.svg "Figure 8-23. prebuild-pulseaudio."
 *
 * @htmlonly
 * </a>
 * @endhtmlonly
 * <br>
 *
 * - - - -
 *
 */
/*!
 * @file doc_amyoc_oss.h
 * @brief document for doxygen amyoc OSS source code build
 * @version 1.o
 * @date 2023-12-26
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

/*!
 * @page doc_amyoc_oss OSS Source Code Build by Amba Build
 *
 * This script only functions with Amba Build.
 *
 * @section doc_amyoc_guide_download_packages 1 Download Packages: fetch_package.sh
 *
 * Usage:
 * - <b>fetch_package.sh method url package</b>
 * - <b>fetch_package.sh method url package outdir outname</b>
 *   - <b>method</b>: package download method; currently supports four methods
 *     - tar: Use the command `curl` to download the package and use the command `tar` to decompress it.
 *       The package name suffix should end with `tar.gz`, `tar.bz2`, `tar.xz`, `tar`, and so on.
 *     - zip: Use the command `curl` to download the package and use the command `unzip` to decompress the package.
 *       The package name suffix should be end with `gz`, `zip`, and so on.
 *     - git: Use the command `curl` to download the package `$package-git-xxx.tar.gz` first from the mirror server
 *       and then run the command `git pull`. Otherwise, use the command `git clone` to download the package.
 *     - svn: Use the command `curl` to download the package `$package-svn-xxx.tar.gz` first from the mirror server
 *       and then run the command `svn up`. Otherwise, use the command `svn checkout` to download the package.
 *     @note
 *       - The command `curl` will try the mirror URL specified by `$ENV_MIRROR_URL` first.
 *       - When the `outdir` and the `outname` are not specified, the package will only be downloaded;
 *         it will not be copied or decompressed to the output.
 *   - <b>urls</b>: The download link and attributes
 *     - tar / zip: Ambarella recommends setting `md5`, for example:
 *       - `https://xxx/xxx.tar.xz;md5=yyy`
 *     - git: Ambarella recommends setting `branch` / `tag` or `rev` (revision). However, `tag` and `rev` should not be set together, for example:
 *       - `https://xxx/xxx.git;branch=xxx;tag=yyy`
 *       - `https://xxx/xxx.git;branch=xxx;rev=yyy`
 *       - `https://xxx/xxx.git;tag=yyy`
 *       - `https://xxx/xxx.git;rev=yyy`
 *     - svn: Ambarella recommends setting `rev`, for example:
 *       - `https://xxx/xxx;rev=yyy`
 *   - <b>package</b>: When using the `tar` or `zip` methods, the package is the saved file name.
 *     When using the `git` or `svn` methods, the package is the saved folder name. It will be saved under the directory `$ENV_DOWN_DIR`
 *   - <b>outdir</b>: The directory to extract to or copy to when compiling
 *   - <b>outname</b>: The folder name of the package under `outdir`
 * - <b>fetch_package.sh sync</b>: Updates all git and svn packages under the directory `$ENV_DOWN_DIR`
 *
 * - - - -
 *
 * @section doc_amyoc_guide_patch_package 2 Patch Package: exec_patch.sh
 * - Two packages are created for each patch, the patch package and the unpatch package.
 *   The format of the package name must be {source code package name}-patch-{patch ID} and {source code package name}-unpatch-{patch ID}.
 * - The source code package weakly depends on these two packages.
 *   The `Depend_Names` in source code package `#DEPS` statement adds the two packages mentioned above;
 *   the format can be `xxx-patch-xxx|xxx-unpatch-xxx`.
 * - If a virtual dependency rule file is used, the format is as `#VDEPS(choice) xxx-patch-xxx-choice(xxx-unpatch-xxx xxx-patch-xxx):`
 * - All patch packages of the source code package share a Makefile. The example is as follows:
 *   - <b>PATCH_PACKAGE</b>: Source code package name
 *   - <b>PATCH_TOPATH</b>: Source code path
 *   - <b>PATCH_FOLDER</b>: Patch storage path
 *   - <b>PATCH_NAME_{patch ID}</b>: Patch name; can be multiple patches
 *
 * - Example: Source code package patching template
 *   @code {.c}
 *   PATCH_SCRIPT        := $(ENV_TOOL_DIR)/amba/exec_patch.sh
 *   PATCH_PACKAGE       := xxx
 *   PATCH_TOPATH        := xxx
 *
 *   PATCH_FOLDER        := xxx
 *   PATCH_NAME_xxx      := 0001-xxx.patch
 *   PATCH_NAME_yyy      := 0001-yyy.patch 0002-yyy.patch
 *
 *   $(PATCH_PACKAGE)-unpatch-all:
 *     @$(PATCH_SCRIPT) unpatch $(PATCH_FOLDER) $(PATCH_TOPATH)
 *     @echo "Unpatch $(PATCH_TOPATH) Done."
 *
 *   $(PATCH_PACKAGE)-patch-%-all:
 *     @$(PATCH_SCRIPT) patch "$(patsubst %,$(PATCH_FOLDER)/%,$(PATCH_NAME_$(patsubst $(PATCH_PACKAGE)-patch-%-all,%,$@)))" $(PATCH_TOPATH)
 *     @echo "Build $(patsubst %-all,%,$@) Done."
 *
 *   $(PATCH_PACKAGE)-unpatch-%-all:
 *     @$(PATCH_SCRIPT) unpatch "$(patsubst %,$(PATCH_FOLDER)/%,$(PATCH_NAME_$(patsubst $(PATCH_PACKAGE)-unpatch-%-all,%,$@)))" $(PATCH_TOPATH)
 *     @echo "Build $(patsubst %-all,%,$@) Done."
 *
 *   %-clean:
 * 	   @
 *
 *   %-install:
 *     @
 *   @endcode
 *
 * - - - -
 *
 */
/*!
 * @file doc_yocto_recipes.h
 * @brief description document of yocto recipes file
 * @version 1.o
 * @date 2022-11-22
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

/*!
 * @page doc_yocto_recipes Yocto Recipe
 *
 * @section doc_yocto_rec_sec_class 1. Class Files
 *
 * Environment variables can be defined in the class file `meta-xxx/classes/xxx.bbclass`
 * and inherited by the package recipe file (inherit xxx); for example, `ambaenv.bbclass`.
 * @code {.c}
 * export ENV_TOP_DIR
 * export CONF_PATH = "${STAGING_BINDIR_NATIVE}"
 * export OUT_PATH = "${WORKDIR}/build"
 * export ENV_INS_ROOT = "${WORKDIR}/image"
 * export ENV_DEP_ROOT = "${WORKDIR}/recipe-sysroot"
 * export ENV_CFG_ROOT = "${TOPDIR}/config"
 * export ENV_BUILD_MODE
 *
 * export AMBA_BOARD
 * export AMBA_SOC
 * export AMBA_CPU_ARCH
 * export AMBA_DSP_ARCH
 * export AMBA_CAVALRY_ARCH
 * @endcode
 *
 * Some common functions and tasks can also be placed in class files, such as `kconfig.bbclass`.
 * @code {.c}
 * inherit terminal
 *
 * KCONFIG_CONFIG_COMMAND ??= "menuconfig"
 * KCONFIG_CONFIG_PATH ??= "${B}/.config"
 *
 * python do_setrecompile () {
 *     if hasattr(bb.build, 'write_taint'):
 *         bb.build.write_taint('do_compile', d)
 * }
 *
 * do_setrecompile[nostamp] = "1"
 * addtask setrecompile
 *
 * python do_menuconfig() {
 *     config = d.getVar('KCONFIG_CONFIG_PATH')
 *
 *     try:
 *         mtime = os.path.getmtime(config)
 *     except OSError:
 *         mtime = 0
 *
 *     oe_terminal("sh -c \"make %s; if [ \\$? -ne 0 ]; then echo 'Command failed.'; printf 'Press any key to continue... '; read r; fi\"" % d.getVar('KCONFIG_CONFIG_COMMAND'),
 *         d.getVar('PN') + ' Configuration', d)
 *
 *     if hasattr(bb.build, 'write_taint'):
 *         try:
 *             newmtime = os.path.getmtime(config)
 *         except OSError:
 *             newmtime = 0
 *
 *         if newmtime != mtime:
 *             bb.build.write_taint('do_compile', d)
 * }
 *
 * do_menuconfig[depends] += "kconfig-native:do_populate_sysroot"
 * do_menuconfig[nostamp] = "1"
 * do_menuconfig[dirs] = "${B}"
 * addtask menuconfig after do_configure
 * @endcode
 *
 * @note
 * If the <b>do_setrecompile</b> function is not used, the target package will
 * not be recompiled after modifying the configuration file.
 *
 * - - - -
 *
 * @section doc_yocto_rec_sec_recipes 2. Recipe Files
 *
 * Create a basic recipe: <b>recipetool create -o <xxx.bb> <package_src_dir></b>.
 * The content that the user must add manually is shown below.
 *
 * @subsection sub_yocto_rec_pa 2.1 Add Package Dependencies
 *
 * If a package depends on other packages, add <b>DEPENDS</b> to the recipes.
 *   For example, <b>DEPENDS += "package1 package2"</b>
 *
 * If a package links other packages (<b>LDFLAGS += -lname1 -lname2</b>), add <b>RDEPENDS</b>
 *   to the recipes. For example, <b>RDEPENDS:${PN} += "package1 package2"</b>
 *
 * @subsection sub_yocto_rec_in 2.2 Add Inherited Classes
 * The following table lists the main inherited classes and their functions.
 * <table>
 * <caption id="yocto_recipe_class">Table 2-1. Inherited Classes.</caption>
 * <tr><th> Inherited classes     <th> Function
 * <tr><td> inherit ambaenv       <td> Use Ambarella environment variables
 * <tr><td> inherit kconfig       <td> Use menuconfig
 * <tr><td> inherit sanity        <td> Compile the application with Makefile
 * <tr><td> inherit cmake         <td> Compile the application with cmake
 * <tr><td> inherit module        <td> Compile external kernel module
 * <tr><td> inherit native        <td> Compile host native tool
 * </table>
 *
 * @note
 * - If menuconfig is compiled by `make -f wrapper.mk menuconfig`, users are required to
 * set <b>KCONFIG_CONFIG_COMMAND = "-f wrapper.mk menuconfig"</b> in the recipes.
 * - If the directory where .config is stored is also the output directory of the Yocto Build,
 * users are required to set <b>KCONFIG_CONFIG_PATH = "${OUT_PATH}/.config"</b> in the recipes.
 *
 * @subsection sub_yocto_rec_and 2.3 Installation and Packaging
 *
 * Variables set for packaging:
 *   - <b>FILES:${PN} = "${base_libdir} ${libdir} ${bindir} ${datadir}"</b>: specifies the list of
 *    directories or files that are required to be included in the release package
 *   - <b>FILES:${PN}-dev = "${includedir}"</b>: specifies the list of directories or files that
 *    must be included in the development package; for example, header files and static libraries
 *
 * @note
 * `includedir` points to `xxx/usr/include` and `base_libdir` points to `xxx/lib`. For more information about
 * the Yocto directory, refer to `meta/conf/bitbake.conf` in the poky project.<br>
 * It may be necessary to specify properly which files to package rather than which directories,
 * in order to avoid overlap between packages (for example, attaching recipes from official packages).
 *
 * Inherit sanity or inherit cmake:
 *  - When using "inherit sanity" or "inherit cmake", users must appropriately specify the package
 *    directory. Otherwise, the do_package task will result in an error
 *
 * Inherit module:
 *  - When using the inherit module, users are not required to to set the package
 *    directory of header and module files. If users install other files, they should
 *    specify the package path of other files
 *
 * Ignore certain warnings and errors:
 *  - <b>ALLOW_EMPTY:${PN} = "1"</b>：ignore "do_rootfs" errors caused by package installation
 *    files that are empty, or are only header files
 *  - <b>INSANE_SKIP:${PN} += "dev-so"</b>: ignore the error that the installed file is only
 *   a symbolic link
 *  - For more information, refer to https://docs.yoctoproject.org/ref-manual/classes.html?highlight=sanity#insane-bbclass
 *
 * @code {.c}
 * LICENSE = "LGPL-2.0-or-later"
 * LIC_FILES_CHKSUM = ""
 *
 * # No information for SRC_URI yet (only an external source tree was specified)
 * SRC_URI = ""
 *
 * DEPENDS += "package1 package2"
 * RDEPENDS:${PN} += "package1 package2"
 *
 * inherit ambaenv
 * #KCONFIG_CONFIG_COMMAND = "-f wrapper.mk menuconfig"
 * #KCONFIG_CONFIG_PATH = "${OUT_PATH}/.config"
 * #inherit kconfig
 * inherit sanity
 * #inherit cmake
 * #inherit module
 * #inherit native
 *
 * # NOTE: this is a Makefile-only piece of software, so we cannot generate much of the
 * # recipe automatically - you will need to examine the Makefile yourself and ensure
 * # that the appropriate arguments are passed in.
 *
 * do_configure () {
 *  # Specify any needed configure commands here
 *  :
 * }
 *
 * do_compile () {
 *  # You will almost certainly need to add additional arguments here
 *  oe_runmake
 * }
 *
 * do_install () {
 *  # NOTE: unable to determine what to put here - there is a Makefile but no
 *  # target named "install", so you will need to define this yourself
 *  oe_runmake install
 * }
 *
 * ALLOW_EMPTY:${PN} = "1"
 * INSANE_SKIP:${PN} += "dev-so"
 * FILES:${PN}-dev = "${includedir}"
 * FILES:${PN} = "${base_libdir} ${libdir} ${bindir} ${datadir}"
 * @endcode
 *
 * @note
 * Starting from version 3.4, the override style syntax for variables has changed from
 * underline(_) to colon(:). https://docs.yoctoproject.org/migration-guides/migration-3.4.html#override-syntax-changes
 *
 * - - - -
 *
 * @section doc_yocto_rec_sec_append 3. Recipe Append Files
 *
 * The main role of the recipe append files is to indicate the package source code directory
 * and the Makefile directory, which are usually the same.
 *
 * <b>EXTERNALSRC</b>: the package source code directory. The YOCTO build system checks this
 * directory to see if it must be recompiled.
 *  - If only part of the source code exists in the `EXTERNALSRC` directory, then users must
 *    append files or directories for verification and append the <b>file-checksums</b> flag of
 *    the task; otherwise, the source code will not be recompiled after modification
 *  - Users can inherit the class `extrasrc.bbclass` to perform the appending
 *   - `EXTRASRC_CONFIGURE`: appends the file or directory for the do_configure task
 *   - `EXTRASRC_COMPILE`: appends the file or directory that performs the do_compile task
 *   - `EXTRASRC_INSTALL`: appends the file or directory that performs the do_install task
 *
 *  @code {.c}
 * python () {
 *     tasks = ['configure', 'compile', 'install']
 *
 *     for task in tasks:
 *         task_name = 'do_%s' % (task)
 *         src_name = 'EXTRASRC_%s' % (task.upper())
 *         src_str = d.getVar(src_name)
 *
 *         if src_str:
 *             srcs = src_str.split()
 *             for src in srcs:
 *                 if os.path.exists(src):
 *                     if os.path.isdir(src):
 *                         d.appendVarFlag(task_name, 'file-checksums', ' %s/*:True' % (src))
                       else:
                           d.appendVarFlag(task_name, 'file-checksums', ' %s:True' % (src))
                       #bb.warn('%s is appended in %s of %s\n' % (d.getVarFlag(task_name, 'file-checksums'), task_name, d.getVar('PN')))
                   else:
                       bb.warn('%s is not existed in %s of %s\n' % (src, task_name, d.getVar('PN')))
   }
   @endcode
 *
 *  - For example, append recipes (`ambarella/metadata/meta-ambalib/recipes-video/libiav-efm/libiav-efm.bbappend`)
 *   @code {.c}
 * inherit externalsrc
 * EXTERNALSRC = "${ENV_TOP_DIR}/packages/iav_utils/dsp_${AMBA_DSP_ARCH}/efm"
 * EXTERNALSRC_BUILD = "${ENV_TOP_DIR}/packages/iav_utils/dsp_${AMBA_DSP_ARCH}/efm"
 *
 * EXTRASRC_COMPILE := "${EXTERNALSRC}/../util"
 * inherit extrasrc
 * @endcode
 *
 *   @note
 * In the append recipe file, <b>inherit extrasrc</b> must be placed after <b>inherit
 * externalsrc</b> because the `externalsrc class` overrides <b>file-checksums</b>.
 *
 * <b>EXTERNALSRC_BUILD</b>: `EXTERNALSRC_BUILD` specifies the directory where the make
 * command runs, which may be different from `EXTERNALSRC`.
 *
 * @code {.c}
 * inherit externalsrc
 * EXTERNALSRC = "${ENV_TOP_DIR}/<package_src>"
 * EXTERNALSRC_BUILD = "${ENV_TOP_DIR}/<make_path>"
 * @endcode
 *
 * - - - -
 *
 * @section doc_yocto_rec_sec_patch 4. Patch Hotfix
 *
 * @subsection sub_amyoc_hot_off 4.1 Typical Method of Yocto Patching
 * ##Method
 * - Create a new folder named `recipe name` or `files` in the current directory
 *   of the recipe file and place the patch in this folder
 *	@note
 *  There are more file folders than those listed above used for patch searching, but Ambarella
 *  commonly uses a folder named `recipe name`.
 *
 * - The recipe simply adds the patch filename declaration without adding the folder
 *   path `SRC_URI += "file://0001-xxx.patch"`
 * - If the recipe inherits from the externalsrc class, users must also set
 *   `RCTREECOVEREDTASKS = "do_unpack do_fetch"`
 *  @note
 *  The externalsrc class removes the <b>do_patch task</b> by default, so users
 *  must set <b>RCTREECOVEREDTASKS</b>.
 *
 * ##Advantages
 * - Easy to implement
 *
 * ##Disadvantages
 * - There is no way to determine if the patch is effective
 * - By default, patching is performed only once. If the patch is removed in some special way,
 *   the patch will not be applied after recompilation
 * - This patching method generates a temporary folder in the source directory and
 *   applies the patch directly to source code, such as through the generation of `.pc/` or `patches/`
 *
 * @subsection sub_amyoc_hot_cus 4.2 Customized Patching Method
 * ##Method
 * - Create two packages per patch: a patching package and a depatching package. The
 *   recipe names must be in the format of `xxx-patch-xxx` and `xxx-unpatch-xxx`
 * - The source package weakly depends on these two packages; add
 *   <b>EXTRADEPS = "xxx-patch-xxx|xxx-unpatch-xxx"</b> and <b>inherit weakdep</b>
 * - Create a virtual dependency rule <b>#VDEPS(choice) xxx-patch-xxx-choice(xxx-unpatch-xxx xxx-patch-xxx):</b>
 * - Patch packages write recipes according to the normal rules. Note that the
 *   recipes depend on the patch host toolkit and inherit the patch status check class
 * 	 <b>inherit externalpatch</b>
 *   @note
 *  The role of the externalpatch class is to verify that the patch is applied, and thus
 *  decide whether or not to patch or force depatch.
 *
 *  @code {.c}
 * EXTERNALPATCH_SRC = "patch filename with path"
 * EXTERNALPATCH_DST = "patchtarget code directory"
 * EXTERNALPATCH_OPT = "patch or unpatch"
 * inherit externalpatch
 * @endcode
 *
 * ##Advantages
 * - Supports both patching and un-patching
 * - Patching and un-patching are guaranteed to function correctly, regardless of
 *   where the patching / un-patching is performed
 * - Only the corresponding patch files are modified in the source directory;
 *   no additional temporary files or folders are generated
 * - Patch files can be placed in any directory, and can also share a Makefile with
 *   other compilation methods
 *
 * ##Disadvantages
 * - Slightly complicated to implement
 * - Because the recipe is dynamically modified, it must be re-compiled twice
 *   when the patch option is changed
 *
 * ##Example
 * - Reference Linux patching `ambarella/metadata/meta-ambabsp/recipes-kernel/linux-patch`
 * and `ambarella/kernel/linux-patch`.
 *
 * - - - -
 *
 * @section doc_yocto_rec_sec_example 5. Examples of Recipe Files
 *
 * @subsection append_rec_exa_1 Example 1. Build library
 *
 * `ambarella/metadata/meta-ambalib/recipes-video/libmcl/libmcl.bb`
 *
 * @code {.c}
 * LICENSE = "LGPL-2.0-or-later"
 * LIC_FILES_CHKSUM = ""
 * SRC_URI = ""
 *
 * DEPENDS += "ambvideo-header"          # dependencies
 * EXTRADEPS = "liblua||prebuild-liblua" # Ambarella extensions, two weak dependencies must be selected
 *
 * inherit ambaenv # Ambarella environment variable
 * inherit weakdep # Use weak dependencies to set DEPENDS and RDEPENDS by analyzing whether the .config is y
 * inherit sanity # Inherit this class using the Makefile compilation lib
 *
 * do_configure () {
 * 	:                                   # configure command, doesn't manage configuration itself so it's an empty command
 * }
 *
 * do_compile () {
 * 	oe_runmake -f amba.mk               # Compile, oe_runmake is equivalent to make
 * }
 *
 * do_install () {
 * 	oe_runmake -f amba.mk install      # install
 * }
 *
 * INSANE_SKIP:${PN} += "dev-so"       # Ignore symbolic link errors
 * FILES:${PN}-dev = "${includedir}"   # Development package packaged files
 * FILES:${PN} = "${libdir}" # Files packaged by the release package
 * @endcode
 *
 * @subsection append_rec_exa_2 Example 2. Build application
 *
 * `ambarella/metadata/meta-ambaapp/recipes-test/iav-test/iav-test.bb`
 *
 * @code {.c}
 * LICENSE = "AMBARELLA-3-Clause"
 * LIC_FILES_CHKSUM = "file://LICENSE-AMBARELLA-3-Clause;md5=ae926a6983bc3425ac85f7ad9379b793"
 * NO_GENERIC_LICENSE[AMBARELLA-3-Clause] = "LICENSE-AMBARELLA-3-Clause"
 *
 * SRC_URI = ""
 *
 * DEPENDS += "ambvideo-header libmcl libiav-pm libiav-blur libiav-efm libdatatx"
 * RDEPENDS:${PN} += "libmcl libiav-pm libiav-blur libiav-efm"    # with dynamic library dependencies
 * EXTRADEPS = "liblua||prebuild-liblua ? ? libtextinsert"        # Special dependencies for Ambarella extensions
 *
 * inherit ambaenv                                                # Ambarella environment variables
 * inherit weakdep                                                # Use weak dependency inheritance to set DEPENDS and RDEPENDS by analyzing whether the .config is y
 * inherit sanity                                                 # use Makefile to compile the app to inherit this class
 *
 * do_configure () {
 * 	:
 * }
 *
 * do_compile () {
 * 	oe_runmake -f amba.mk
 * }
 *
 * do_install () {
 * 	oe_runmake -f amba.mk install
 * }
 *
 * FILES:${PN} += "${bindir} ${datadir}"
 * @endcode
 *
 * @subsection append_rec_exa_3 Example 3. Install prebuild libraries
 *
 * `ambarella/metadata/meta-ambalib/recipes-prebuild/prebuild-dewarp/prebuild-dewarp.bb`
 *
 * @code {.c}
 * LICENSE = "AMBARELLA-2-Clause"
 * LIC_FILES_CHKSUM = "file://LICENSE-AMBARELLA-2-Clause;md5=5bc624162af1ddf55df69fe0c4552811"
 * NO_GENERIC_LICENSE[AMBARELLA-2-Clause] = "LICENSE-AMBARELLA-2-Clause"
 *
 * SRC_URI = ""
 *
 * DEPENDS += "libutils libdewarp-lua"
 * RDEPENDS:${PN} += "libutils libdewarp-lua"
 *
 * inherit ambaenv
 * inherit sanity
 *
 * do_configure () {
 * 	# Specify any needed configure commands here
 * 	:
 * }
 *
 * do_compile () {
 * 	oe_runmake -f amba.mk
 * }
 *
 * do_install () {
 * 	oe_runmake -f amba.mk install
 * }
 *
 * INSANE_SKIP:${PN} += "dev-so already-stripped"  # already-stripped ,to ignore errors caused by dynamic libraries that have been strip
 * FILES:${PN}-dev = "${includedir}"
 * FILES:${PN} = "${libdir}"
 * @endcode
 *
 * @subsection append_rec_exa_4 Example 4. Compile cJSON by adding the wrapper for cmake
 *
 * @code {.c}
 * LICENSE = "LGPL-2.0-or-later"
 * LIC_FILES_CHKSUM = ""
 *
 * SRC_URI = ""
 *
 * DEPENDS += "cmake-native"               # Yocto does not use the host's cmake utility, but relies on its own compiled cmake
 *
 * inherit ambaenv
 * inherit sanity
 *
 * do_configure () {
 * 	:
 * }
 *
 * do_compile () {
 * 	oe_runmake -f amba.mk
 * }
 *
 * do_install () {
 * 	oe_runmake -f amba.mk install
 * }
 *
 * INSANE_SKIP:${PN} += "dev-so"
 * FILES:${PN}-dev = "${includedir}"
 * FILES:${PN} = "${libdir}"
 * @endcode
 *
 * @subsection append_rec_exa_5 Example 5. Build kernel modules
 *
 * `ambarella/metadata/meta-ambabsp/recipes-sensor/kernel-module-imx274-mipi/kernel-module-imx274-mipi.bb`
 *
 * @code {.c}
 * LICENSE = "GPL-2.0-or-later"
 * LIC_FILES_CHKSUM = ""
 *
 * SRC_URI = ""
 *
 * DEPENDS += "kernel-module-ambvideo"
 * EXTRADEPS = "unselect"                  # Special dependencies for Ambarella extensions, unselect means this package is configured as `default n` in the script parsing Kconfig
 * inherit ambaenv
 * inherit module                          # Use Makefile to build the mod to inherit this class
 *
 * do_configure () {
 * 	:
 * }
 *
 * do_compile () {
 * 	oe_runmake -f amba.mk
 * }
 *
 * do_install () {
 * 	oe_runmake -f amba.mk install
 * }
 * @endcode
 *
 * - - - -
 *
 * @section yocto_meta_layers 6. Yocto Meta Layers
 *
 * @subsection ambarella_meta_layers 6.1 Ambarella Meta Layers
 * The following table lists all the Meta Layers provided by Ambarella.
 * <table>
 * <caption id="table_amba_meta_layers">Table 6-1. Amba Meta Layers.</caption>
 * <tr><th> Meta-Layers Location   <th> Layer Name           <th> More information
 * <tr><td rowspan="7"> metadata   <td> meta-ambabsp         <td> boot, board, kernel, amba private drivers(video, sensors, VP...)
 * <tr>                            <td> meta-ambalib         <td> amba private libraries, middleware and amba tools(load_ucode, dsplog_cap)
 * <tr>                            <td> meta-ambaapp         <td> amba unit test apps, demo apps and debug tools
 * <tr>                            <td> meta-ambasecurity    <td> software packages and tools about security
 * <tr>                            <td> meta-amrtos          <td> software packages of AMRTOS supported by ambarella
 * <tr>                            <td> meta-external        <td> external software packages provided by other vendors
 * <tr>                            <td> meta-thirdparty      <td> OSS libraries & tools and other 3rd-party prebuild libraries & tools
 * </table>
 *
 * @subsection oss_meta_layers 6.2 OSS Meta Layers
 * The following table lists all the OSS Meta Layers used in the SDK.
 * <table>
 * <caption id="table_oss_meta_layers">Table 6-2. Oss Meta Layers.</caption>
 * <tr><th> Meta-Layers Location   <th> Layer Name           <th> More information
 * <tr><td> build                  <td> poky                 <td> https://git.yoctoproject.org/poky
 * <tr><td rowspan="3"> oss_yocto  <td> meta-openembedded    <td> https://git.openembedded.org/meta-openembedded
 * <tr>                            <td> meta-ros             <td> https://github.com/ros/meta-ros
 * <tr>                            <td> meta-selinux         <td> https://github.com/ni/meta-selinux
 * </table>
 *
 * @note
 * Amba won’t change/maintain the source code of Third-Party Meta Layers, but only sync the latest update periodically.
 *
 * - - - -
 *
 * @section doc_yocto_rec_sec_commerial_3rd_party 7. Commerial Third-Party Libraries
 *
 * The following table lists the commerial third-party libraries used by some Yocto Build software packages.
 * If users have deep concern on the license of these libraries and do not use them in real products,
 * they can directly remove the software packages and recipes of these libraries.
 *
 * <table>
 * <caption id="commerial_3rd_party">Table 7-1. Commerial Third-Party Libraries.</caption>
 * <tr><th> Library               <th> Software Packages that Depends
 * <tr><td> FFmpeg                <td> gstreamer
 * <tr><td> x265                  <td> TBD
 * </table>
 *
 * - - - -
 *
 * @section doc_yocto_rec_sec_single_multi_sub 8. Single Package with Multiple Sub-Packages
 *
 * @subsection doc_yocto_sub_single_introduction 8.1 Introduction
 * When using open source software (OSS) packages supported by the Yocto Community, there will
 * be cases where a single OSS package contains multiple separated sub-packages.
 *
 * The following table lists some common source packages and their sub-packages:
 * <table>
 * <caption id="package_mutil_sub_package">Table 8-1. Single Package with Multiple Sub-Packages.</caption>
 * <tr><th> <div style="width:320px" align="left"><B>Source Package</B></div>
 * <th> <div style="width:320px" align="left"><B>Sub-Packages</B></div>
 * <tr><td rowspan="3">PulseAudio            <td> pulseaudio-pa-info
 * <tr>                                      <td> pulseaudio-server
 * <tr>                                      <td> pulseaudio-misc
 * </table>
 *
 * @subsection doc_yocto_sub_single_guide 8.2 Add Sub-Packages to Source Package Installation
 * The current software development kit (SDK) provides convenience for users to easily select the OSS packages
 * through "make menuconfig", while it can only retrieve the OSS packages that have the
 * same name as its recipe file. Once finished with menuconfig, an ipcam-image.bb will be
 * generated automatically to add all selected software packages into the build
 * and install queue. If a target OSS package has multiple sub-packages, its
 * sub-packages that have a different name from the recipe file will not be selected.
 * To resolve this issue, users can follow the steps to add these sub-packages specifically.
 * PulseAudio is used as an example:
 *
 * <b>#1</b>. Add the subpackage name to the `IMAGE_INSTALL` variable in the `ipcam-image.bbappend` file.
 * @code {.c}
 * ambarella/metadata/meta-ambabsp/recipes-core/images/ipcam-image.bbappend
 *
 * IMAGE_INSTALL:append = " \
 *           pulseaudio-pa-info \
 *           pulseaudio-server \
 *           pulseaudio-misc \
 *           "
 * @endcode
 *
 * <b>#2</b>. Add the OSS package name to the `DEPENDS` variable and add the sub-package name to the
 * `RDEPENDS:${PN}` variable in any recipe file. If a target package depends on
 * PulseAudio's subpackages, the user can modify the `DEPENDS' and 'RDEPENDS:${PN}'
 * variable in the target package's recipe file.
 *
 * @code {.c}
 *
 * DEPENDS += "pulseaudio"
 * RDEPENDS:${PN} += "\
 *              libpulse \
 *              libpulse-mainloop-glib \
 *              libpulse-simple \
 *              libpulsecommon \
 *              libpulsecore \
 *              pulseaudio-pa-info \
 *              pulseaudio-server \
 *              pulseaudio-misc \
 *              "
 *
 * @endcode
 *
 * Users can also use this method to add other software packages into the
 * current compilation target.
 *
 * - - - -
 *
 * @section doc_yocto_rec_difference_3rd_party 9. The Difference of Big OSS Modules
 *
 * The following table lists the difference of the BIG OSS modules between Amba Build and Yocto Build.
 *
 * <table>
 * <caption id="difference_3rd_party">Table 9-1. Difference Of Big OSS Modules</caption>
 * <tr><th> OSS         <th> Amba Build                                     <th> Yocto Build
 * <tr><td> Busybox     <td> ambarella/prebuild/oss/<CPU_ARCH>/busybox      <td> ambarella/build/poky/meta/recipes-core/busybox
 * <tr><td> Systemd     <td> ambarella/prebuild/oss/<CPU_ARCH>/systemd      <td> ambarella/build/poky/meta/recipes-core/systemd
 * <tr><td> ROS2        <td> Not supported                                  <td> ambarella/oss_yocto/meta-ros/meta-ros2-galactic
 * <tr><td> iceoryx     <td> ambarella/prebuild/oss/<CPU_ARCH>/iceoryx-*    <td> ambarella/oss_yocto/meta-ros/meta-ros2-galactic/generated-recipes/iceoryx
 * <tr><td> CycloneDDS  <td> ambarella/prebuild/oss/<CPU_ARCH>/cyclonedds*  <td> ambarella/oss_yocto/meta-ros/meta-ros2-galactic/generated-recipes/cyclonedds
 * <tr><td> OpenCV4     <td> ambarella/prebuild/oss/<CPU_ARCH>/opencv       <td> ambarella/oss_yocto/meta-openembedded/meta-oe/recipes-support/opencv
 * <tr><td> FFmpeg      <td> Not supported                                  <td> ambarella/build/poky/meta/recipes-multimedia/ffmpeg
 * <tr><td> GStreamer   <td> ambarella/prebuild/oss/<CPU_ARCH>/gstreamer1*  <td> ambarella/build/poky/meta/recipes-multimedia/gstreamer
 * <tr><td> PulseAudio  <td> ambarella/prebuild/oss/<CPU_ARCH>/pulseaudio   <td> ambarella/build/poky/meta/recipes-multimedia/pulseaudio
 * <tr><td> ALSA        <td> ambarella/prebuild/oss/<CPU_ARCH>/alsa-*       <td> ambarella/build/poky/meta/recipes-multimedia/alsa
 * <tr><td> Python3     <td> ambarella/prebuild/oss/<CPU_ARCH>/python3      <td> ambarella/build/poky/meta/recipes-devtools/python
 * <tr><td> Flask       <td> Not supported                                  <td> ambarella/oss_yocto/meta-openembedded/meta-python/recipes-devtools/python
 * <tr><td> SElinux     <td> ambarella/prebuild/oss/<CPU_ARCH>/libselinux   <td> ambarella/oss_yocto/meta-selinux/recipes-security
 * <tr><td> SQLite3     <td> ambarella/prebuild/oss/<CPU_ARCH>/sqlite       <td> ambarella/build/poky/meta/recipes-support/sqlite
 * </table>
 *
 * @note
 * - For Amba Build: it uses the prebuild OSSs compiled by Ambarella.
 * - For Yocto Build: it uses the OSSs provided by OSS community.
 *
 * - - - -
 *
 */
/*!
 * @file doc_yocto_faq.h
 * @brief document for doxygen amyoc FAQs
 * @version 1.0
 * @date 2022-11-28
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

/*!
 * @page doc_yocto_faq Yocto FAQ
 *
 * @section yocto_faq1 Question 1: What are the Yocto official documents to learn?
 * <b>Answer:</b> As shown below:<br>
 * ★★★: Three-star documents are suggested to be mastered well<br>
 * ★★☆: Two-star documents can be mastered basically<br>
 * ★☆☆: One-star documents can be used as reference<br>
 *
 * - Getting Started Knowledge:
 *   - Yocto Project Quick Build ★★★  https://docs.yoctoproject.org/brief-yoctoprojectqs/index.html
 *   - Usage Advice ★★☆  https://docs.yoctoproject.org/what-i-wish-id-known.html
 *   - Introducing the Yocto Project ★★☆  https://docs.yoctoproject.org/overview-manual/yp-intro.html
 *   - Yocto Project Concepts ★★★  https://docs.yoctoproject.org/overview-manual/concepts.html
 * - Reference Manual (https://docs.yoctoproject.org/ref-manual/index.html)
 *   - Source Directory Structure ★★★ https://docs.yoctoproject.org/ref-manual/structure.html
 *   - Classes ★☆☆  https://docs.yoctoproject.org/ref-manual/classes.html
 *     - QA check, insane.bbclass ★★☆  https://docs.yoctoproject.org/ref-manual/classes.html#insane-bbclass
 *   - Tasks ★★★  https://docs.yoctoproject.org/ref-manual/tasks.html
 *   - Devtool Quick Reference ★☆☆  https://docs.yoctoproject.org/ref-manual/devtool-reference.html
 *   - QA Error and Warning Messages ★★☆  https://docs.yoctoproject.org/ref-manual/qa-checks.html
 *   - Variables Glossary ★☆☆  https://docs.yoctoproject.org/ref-manual/variables.html
 * - Development Manual:
 *   - Board support packages (BSP) — Developer’s Guide ★★☆  https://docs.yoctoproject.org/bsp-guide/bsp.html
 *   - Yocto Project Linux Kernel Development Manual ★★☆  https://docs.yoctoproject.org/kernel-dev/index.html
 *   - Common Tasks ★★☆  https://docs.yoctoproject.org/dev-manual/common-tasks.html
 *     - Understanding and Creating Layers ★★★ https://docs.yoctoproject.org/dev-manual/common-tasks.html#understanding-and-creating-layers
 *     - Customizing Images ★★★  https://docs.yoctoproject.org/dev-manual/common-tasks.html#customizing-images
 *     - Writing a New Recipe ★★★  https://docs.yoctoproject.org/dev-manual/common-tasks.html#writing-a-new-recipe
 *     - Adding a New Machine ★★★  https://docs.yoctoproject.org/dev-manual/common-tasks.html#adding-a-new-machine
 *     - Understanding package ★★★  https://docs.yoctoproject.org/dev-manual/common-tasks.html#working-with-pre-built-libraries
 * - BitBake User Manual (https://docs.yoctoproject.org/bitbake/2.0/index.html)
 *     - Overview ★★☆  https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-intro.html
 *     - Execution ★☆☆  https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-execution.html
 *     - Syntax and Operators ★★★  https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-metadata.html
 *     - File Download Support ★☆☆  https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-fetching.html
 *     - Variables Glossary ★☆☆  https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-ref-variables.html
 *
 * - - - -
 *
 * @section yocto_faq2 Question 2: Which is better: Yocto or Buildroot?
 * <b>Answer:</b> There is no clear answer which is better, but one may be better or worse for use cases for embedded systems.
 *
 *  - `Yocto`: Yocto is more suitable for larger projects because it is widely used and is
 *             actively supported by the community with more tools, features, and open source software (OSS) packages available.
 *   - <b>Pros:</b>
 *     - Yocto is widely used with many semiconductors. This makes it more compatible
 *       with a wider number of embedded device boards.
 *     - It is widely and actively supported by the community, and has more tools, features, and OSS packages available.
 *     - Based on its implementation of layers, it is much easier for users to integrate their own
 *       layers of software packages into the Yocto software development kit (SDK) provided by the system on chip (SoC) or board vendors.
 *   - <b>Cons:</b>
 *     - The learning curve is relatively steep when getting started.
 *     - The build time is quite long with super huge temporary files.
 *
 *  - `Buildroot`: Buildroot is more practical for smaller projects because it is built to be
 *                 simple and quick to deploy, especially when compared to Yocto, whose learning curve
 *                 is relatively steep when getting started.
 *   - <b>Pros:</b>
 *     - Buildroot is built to be easy. Its core build system is written in Make and is small enough
 *       for users to understand quickly.
 *     - The build time is significantly shorter than that of Yocto build.
 *   - <b>Cons:</b>
 *     - Buildroot has less popularity than Yocto, which means that it is maintained and supported by
 *       a smaller community with a less-active ecosystem.
 *     - There is a lack of incremental builds. When users want to make an update, even a small
 *       change, users must rebuild the entire image.
 *     - Buildroot focuses on simplicity, which means that it is much harder to customize.
 *
 * Users can refer to this link for more comments about the pros and cons of Yocto and Buildroot:
 * https://www.incredibuild.com/blog/yocto-or-buildroot-which-to-use-when-building-your-custom-embedded-systems
 *
 * - - - -
 *
 * @section yocto_faq3 Question 3: Can customers download and use Poky from the Yocto community?
 * <b>Answer:</b> Yes. Customers can download and use Poky directly from the Yocto community.
 * Ambarella suggests using 4.0 (Kirstone) or a higher version. For Poky included in the Cooper SDK base package,
 * it will be upgraded to Kirstone 4.0.5.
 *
 * - - - -
 *
 * @section yocto_faq4 Question 4: Can customers download and use the Linux kernel from the community?
 * <b>Answer:</b> Yes, but Ambarella suggests using the same kernel version as the SDK.
 * In the formal Cooper SDK, Ambarella provides the kernel package in the format of linux-5.15.tar.bz2 (for example, kernel 5.15.76
 * in the Cooper SDK base package) + linux-5.15-ambarella.patch. With linux-5.15-ambarella.patch, customers can download
 * pure Linux from the community and then apply this patch.
 *
 * - - - -
 *
 * @section yocto_faq5 Question 5: How does the Cooper SDK Yocto build manage the OSS supported by Yocto Poky?
 * <b>Answer:</b> For Yocto build, all OSS (including BusyBox) use the ones supported by Poky from the community. Ambarella only
 * keeps the prebuild ones that are now NOT supported by Poky. For Amba build, it will keep using prebuild OSS libs.
 *
 * - - - -
 *
 * @section yocto_faq6 Question 6: What is the main difference between Yocto compilation and regular compilation?
 * <b>Answer:</b> Regular compilation uses the host build environment; Yocto compiles each package with its own output
 * directory WORKDIR (https://docs.yoctoproject.org/ref-manual/variables.html#term-WORKDIR),
 * and configures the compilation environment in the output directory.
 *
 * - `${WORKDIR}/build`: compiled output directory (only for source code and compiled output separately)
 * - `${WORKDIR}/recipe-sysroot`: system dependencies root folder
 * - `${WORKDIR}/recipe-sysroot-native`: build host software tool root folder
 * - `${WORKDIR}/image`: installation root directory
 * - `${WORKDIR}/temp`: directory for storing compiled logs and scripts
 *
 * Yocto copies the required host tools and dependent files to its own working directory and
 * creates a clean shell environment to run tasks.
 *
 * Yocto manages the relationships between packages according to certain rules.
 *
 * - - - -
 *
 * @section yocto_faq7 Question 7: How does Yocto export environment variables?
 * <b>Answer:</b> Yocto cannot use the environment variables exported in the shell. The environment
 * variables in Yocto are defined in `conf/local.conf` in the output directory and are
 * exported one by one in the recipe file via <b>export <varname></b>.
 *
 * Users can check which variables are exported in the `${WORKDIR}/temp/run.do_compile` file.
 *
 * For more details about exporting variables to the environment, refer to the page
 * (https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-metadata.html?highlight=nostamp#exporting-variables-to-the-environment)
 *
 * - - - -
 *
 * @section yocto_faq8 Question 8: What are the common Yocto commands?
 *  <b>Answer:</b> The main commands are as follows:
 *
 *  - bitbake command (https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-intro.html#the-bitbake-command)
 *    - bitbake packagename: build packagename
 *    - bitbake -c taskname packagename: execute the "taskname" task of packagename
 *    - bitbake -e packagename: display the generated task environment script
 *  - recipetool command (https://docs.yoctoproject.org/dev-manual/common-tasks.html#locate-or-automatically-create-a-base-recipe)
 *    - recipetool create -o xxx.bb src_path: generate a recipe based on source code
 *  - bitbake-layers command (https://docs.yoctoproject.org/bsp-guide/bsp.html?highlight=bitbake+layers#creating-a-new-bsp-layer-using-the-bitbake-layers-script)
 *    - bitbake-layers create-layer xxx && mv xxx meta-xxx: create a new general layer
 *    - bitbake-layers add-layer meta-xxx: add a layer to the current configuration
 *
 * - - - -
 *
 * @section yocto_faq9 Question 9: Which configuration files should users pay attention to in Yocto build?
 * <b>Answer:</b> The main configuration files are as follows:
 *
 *  - `TOPDIR`: points to the build directory. BitBake automatically sets this variable.
 * https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-ref-variables.html#term-TOPDIR
 *  - `poky/meta/conf/bitbake.conf`: default configuration file; most variables are defined here.
 * https://docs.yoctoproject.org/ref-manual/structure.html?highlight=bitbake+conf#meta-conf
 *  - `${TOPDIR}/conf/local.conf`: this configuration file contains all local user configurations
 * for the build environment. Any variable set here overrides any variable set elsewhere within the environment
 * https://docs.yoctoproject.org/ref-manual/structure.html?highlight=local+conf#build-conf-local-conf
 *  - `${TOPDIR}/conf/bblayers.conf`: the configuration of the layers in the current configuration
 * can be found in this file.
 * https://docs.yoctoproject.org/ref-manual/structure.html?highlight=local+conf#build-conf-bblayers-conf
 *  - `meta-xxx/conf/layer.conf`: this configuration file primarily configures how the build system finds
 * the recipe file configurations.
 * https://docs.yoctoproject.org/dev-manual/common-tasks.html?highlight=layer+conf#creating-your-own-layer
 *  - `meta-xxx/conf/machine/xxx.conf`: machine configuration. The layer with the machine configuration
 * is the BSP layer. Meanwhile, each BSP layer requires at least one machine file.
 * https://docs.yoctoproject.org/bsp-guide/bsp.html?highlight=machine+conf#hardware-configuration-options
 *
 * - - - -
 *
 * @section yocto_faq10 Question 10: How are variables used in Yocto?
 *  <b>Answer:</b> For more information, refer to the basic syntax page
 * (https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-metadata.html#basic-syntax)
 * and the conditional syntax page
 * (https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-metadata.html#conditional-syntax-overrides).
 *
 * - To get the value of a variable, users should use braces <b>${var}</b>
 * - Unlike in Bourne shells, single quotes function identically to double quotes in all other
 *   ways. They do not suppress variable expansions
 * - The operators that define or modify variables are as shown below:
 *   - <b>assign</b>: = := ? = ?? =
 *     - <b>= ?= ??=</b> : when a variable exists as the value left of the equal sign, the variable
 *       to the right of the equal sign is the last extension (the final value of the variable)
 *     - <b>:= :</b> the variable to the left of the equal sign is the immediate extension
 *       (the value of the variable at the current position)
 *     - <b>?=</b> : sets the default value (assign value only when the variable is empty)
 *     - <b>??=</b> : sets weak defaults (parse the statement at the end of the parsing process.
 *       When the variable is not defined, the value is retained; and the last
 *       is valid when multiple "??=" exist)
 *   - <b>Append</b> :  += =+ .= =. :append :prepend; <b>Delete</b> :  :remove
 *     - <b>+= .= :append</b> post-append (the new value is placed after the original value)
 *       <b>=+ =. :prepend</b> preappend (the new value is placed before the original value)
 *     - <b>+= =+</b> automatically adds a space between the new value and the original value
 *       <b>.= =. :append :prepend</b> does not add a space between the new value and the original value;
 *       users must add it manually
 *     - <b>+= =+ .= =.</b> immediately parses (append immediately when parsing the current statement)
 *       <b>:append :prepend</b> final parsing (append when parsing the statement after the
 *       parsing process is finished)
 *     - <b>:remove</b> removes all existing values (multiple values separated by spaces) that are
 *       the same as the set value
 *   - <b>Conditions</b>: OVERRIDES
 *     - The condition declaration uses the <b>OVERRIDES</b> keyword; only lowercase characters,
 *       numbers, and underscores can be used for condition names; multiple conditions are separated by colons
 *       - OVERRIDES = "cond1:cond2"
 *       - OVERRIDES:append = ":cond3"
 *     - Defines or modifies the corresponding variable only when the condition is defined;
 *       for example, var:cond1:append = "xxx"
 * - Unset variable: unset
 * - Define flag: var[flag_name]; users can use the brackets var[flag_name] to define the flag of a variable
 *   - Defining a new variable's flag can be interpreted as creating a new variable. It is
 *     similar to treating a variable as an array, with the variable name corresponding to
 *     the array name and the flag corresponding to the index subscript of the array
 *   - Task variables have some public flags.
 *     https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-metadata.html#variable-flags
 *   - The operators that define or modify a variable and unset can be used in the variable's flag
 *
 * - - - -
 *
 * @section yocto_faq11 Question 11: How can shared files be included in Yocto?
 * <b>Answer:</b> The four ways to include shared files in Yocto are as shown below:
 * https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-metadata.html#sharing-functionality
 *
 * - Inherited classes: <b>inherit <class_name></b> and <b>INHERIT += <class_name></b>
 *   - Only inherit class files (`*.bbclass`)
 *   - Inherit can only be used in recipe and class files (`*.bb` / `*.bbappend` / `*.bbclass`),
 *     <b>INHERIT</b> can only be used in configuration files (`*.conf`)
 *   - Class files can be retrieved not only in the current layer directory, but also
 *     in other layer directories defined by BBLAYER variables in the `conf/bblayers.conf` file
 *     BBLAYER variables: https://docs.yoctoproject.org/ref-manual/variables.html?highlight=bblayers#term-BBLAYERS
 * - Include files: <b>include <file_path></b> and <b>require <file_path></b>
 *   - The included file can be any type of file, but Ambarella generally names it *.inc
 *   - The include and require directives can be used in any type of file
 *   - The include directive does not report an error if the file it contains does not exist, while the
 *     require directive does
 *   - If `<file_path>` is a relative path, then the base path is from the
 *     BBLAYER variable in the `conf/bblayers.conf` file to find the first match
 *   - The recipe file(*.bb) can use the THISDIR variable to indicate the directory
 *     where the recipe file is located.
 *     For example, include `usertask.inc`: include ${THISDIR}/usertask.inc
 *     THISDIR variable: https://docs.yoctoproject.org/ref-manual/variables.html?highlight=thisdir#term-THISDIR
 *
 * - - - -
 *
 * @section yocto_faq12 Question 12: How does Yocto build function under network file system (NFS)?
 * <b>Answer:</b> Yocto does not support compiling under NFS by default, because the
 * compilation speed is slow and there may be permission problems. For more information, refer to the page
 * https://bugzilla.yoctoproject.org/show_bug.cgi?id=5442#c8.
 *
 * Users can disable the NFS checks in the official Poky project to make it compile successfully
 * using the following method; however, but there is no guarantee that other problems will not occur.
 * @code {.c}
 * diff --git a/meta/classes/sanity.bbclass b/meta/classes/sanity.bbclass
 * index b1fac107d5..afbafe2382 100644
 * --- a/meta/classes/sanity.bbclass
 * +++ b/meta/classes/sanity.bbclass
 * @@ -722,7 +722,7 @@ def check_sanity_version_change(status, d):
 *      status.addresult(check_path_length(tmpdir, "TMPDIR", 410))
 *
 *      # Check that TMPDIR isn't located on nfs
 * -    status.addresult(check_not_nfs(tmpdir, "TMPDIR"))
 * +    #status.addresult(check_not_nfs(tmpdir, "TMPDIR"))
 *
 *      # Check for case-insensitive file systems (such as Linux in Docker on
 *      # macOS with default HFS+ file system)
 * @endcode
 *
 * - - - -
 *
 * @section yocto_faq13 Question 13: Where is the Yocto directory structure defined?
 * <b>Answer:</b> To understand the role of directories, refer to the page
 * (https://docs.yoctoproject.org/ref-manual/structure.html).
 * Check the Poky configuration file `meta/conf/bitbake.conf` for detailed definitions of
 * directory variables.
 *
 * - - - -
 *
 * @section yocto_faq14 Question 14: What do downloads and sstate-cache have?
 * <b>Answer:</b> `downloads` stores the source code; `sstate-cache` stores the compiled files. They can
 * use the variables <b>DL_DIR</b> and <b>SSTATE_DIR</b> to specify the save directory
 * respectively.
 * DL_DIR: https://docs.yoctoproject.org/ref-manual/variables.html?highlight=dl_dir#term-DL_DIR
 * SSTATE_DIR: https://docs.yoctoproject.org/ref-manual/variables.html#term-SSTATE_DIR
 *
 * As shown below, they are stored in a common location so that all boards can share a resource.
 * @code {.c}
 * DL_DIR = "${TOPDIR}/../downloads"
 * SSTATE_DIR = "${TOPDIR}/../sstate-cache"
 * @endcode
 *
 * - - - -
 *
 * @section yocto_faq15 Question 15: How can users establish local mirror servers to speed up the build?
 *  <b>Answer:</b> The first time building firmware through Yocto build usually takes many hours.
 * This is because all required aspects, including compiler tools and OSS software packages, must be downloaded in
 * advance. This is quite time-consuming.
 * To save time, Ambarella suggests establishing the mirror server so that the required tools are only downloaded
 * once, and then can be shared with other users. Users can follow the directions below to establish the
 * mirror server.<br>
 * 1. Copy the `downloads` and `sstate-cache` generated
 * by the first build to a specific directory, such as `mirror`.
 * 2. Run the HTTP server in the `mirror` directory;
 * for example, <b>python -m http.server 8080</b>.
 * 3. Add a setting to `conf/local.conf` in the output directory, for example:
 *
 * @code {.c}
 * SSTATE_MIRRORS = "file://.* http://127.0.0.1:8080/sstate-cache/PATH;downloadfilename=PATH"
 * SOURCE_MIRROR_URL = "http://127.0.0.1:8080/downloads"
 * INHERIT += "own-mirrors"
 * @endcode
 *
 * - - - -
 *
 * @section yocto_faq16 Question 16: What are the Yocto rules for getting source code and not recompiling?
 * <b>Answer:</b> The rule that Yocto does not recompile is shown below:
 * (https://docs.yoctoproject.org/overview-manual/concepts.html#shared-state-cache):
 * - Check if there is a compiled package with the same timestamp in the local
 *   `SSTATE_DIR` folder; if yes, there is no requirement to recompile. Otherwise, check the next.
 *   For information about <b>recompile</b>, refer to the page
 *   https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-execution.html#setscene.
 * - Check if there is a compiled package with the same timestamp in the
 *   `SSTATE_MIRRORS` folder on the network. If so, copy the compiled package
 *   from the network directly to the local SSTATE_DIR without recompiling.
 *   Otherwise, check the next line.
 * - Get the source code to compile and copy the compiled package to the local `SSTATE_DIR`.
 *
 * The rule for Yocto to get the source code is shown below:
 * (https://docs.yoctoproject.org/bitbake/2.0/bitbake-user-manual/bitbake-user-manual-fetching.html):
 * - If the downloaded source code exists in the local `DL_DIR` directory with the same hash value,
 *   unzip it directly from the local directory.
 * - If the downloaded source code exists in the `SORUCE_MIRROR_URL` folder on the network with
 *   the same hash value, download it to the local directory and then decompress. Otherwise,
 *   check the next.
 * - Download the source code from the `SRC_URI` link specified in the recipe file if the
 *   download fails.
 * - Download the source code from the official Yocto mirror.
 *
 * - - - -
 *
 * @section yocto_faq17 Question 17: How are official open source package compilation errors managed?
 * <b>Answer:</b> The Yocto official recipe is used to compile the open source package.
 * The <b>cache</b> may cause this error, or there may be insufficient system memory causing
 * compilation errors. Running clean-up may resolve the issue. See the example below:
 *
 * error log:
 * @code {.c}
 * ERROR: Task (USER_AMYOC_SDK_FOLDER/ambarella/build/poky/meta/recipes-connectivity/openssl/openssl_3.0.4.bb:do_package_write_rpm) failed with exit code '1'
 * ERROR: Task (USER_AMYOC_SDK_FOLDER/ambarella/build/poky/meta/recipes-devtools/gcc/gcc_11.3.bb:do_compile) failed with exit code '1'
 * @endcode
 *
 * Solution:
 * @code {.c}
 * build # bitbake -c clean openssl && bitbake openssl  # openssl_3.0.4.bb
 * build # bitbake -c clean gcc && bitbake gcc          # gcc_11.3.bb
 * @endcode
 *
 * - - - -
 *
 * @section yocto_faq18 Question 18: Why does the recipe file name of an external Linux module start with kernel-module-?
 * <b>Answer:</b> See Poky's source code for `meta/classes/module.bbclass`.
 * @code {.c}
 * python __anonymous () {
 * depends = d.getVar('DEPENDS')
 * extra_symbols = []
 * for dep in depends.split():
 * 	if dep.startswith("kernel-module-"):
 * 		extra_symbols.append("${STAGING_INCDIR}/" + dep + "/Module.symvers")
 * d.setVar('KBUILD_EXTRA_SYMBOLS', " ".join(extra_symbols))
 * }
 * @endcode
 *
 * The module class automatically adds the symbol export file `Module.symvers` of dependent modules
 * to the <b>KBUILD_EXTRA_SYMBOLS</b> variable.
 * <b>KBUILD_EXTRA_SYMBOLS</b>: https://www.kernel.org/doc/html/latest/kbuild/kbuild.html?highlight=kbuild_extra_symbols
 *
 * `Module.symvers` contains a list of <b>EXPORT_SYMBOL(func)</b> exported symbols.
 * If users do not specify this file for the dependency package, the compilation will fail.
 *
 * The inc.mod.mk template automatically adds Module.symvers, so it is acceptable to
 * name it kernel-module-.
 *
 * - - - -
 *
 * @section yocto_faq19 Question 19: How can the compiler be prevented from creating symlinks
 * oe/workdir / oe-logs in the source code directory?
 * <b>Answer:</b> Look for the <b>EXTERNALSRC_SYMLINKS</b> variable (EXTERNALSRC_SYMLINKS?= "oe-workdir:${WORKDIR} oe-logs:${T}")
 * in the Poky project source code of `meta/classes/externalsrc.bbclass`, and set this variable to
 * null(EXTERNALSRC_SYMLINKS ?= "") in `conf/local.conf` in the output directory to disable its creation.
 *
 *  - Oe-workdir: points to the root directory of the package output `${WORKDIR}`
 *  - Oe-logs: points to the package output log and script directory `${WORKDIR}/temp`
 *
 * - - - -
 *
 * @section yocto_faq20 Question 20: How is the error message "ERROR: Please use a umask which allows a+rx and u+rwx" resolved and managed?
 * <b>Answer:</b> The Yocto build system requires permissions of the created folder to be at least 755, and the
 * permissions of the created file to be at least 644. If the following error occurs, check
 * the umask value of the current shell environment configuration. Users can run the
 * <b>"umask 022"</b> command to fix the issue.
 *
 * For directories, the maximum default permission is 777; for files, the maximum default
 * permission is 666. The initial permissions for files and directories are obtained by calculating the following:
 * <b>initial permission = maximum default permission - umask permission</b>.
 *
 * @code {.c}
 * $ make
 * Clean done!
 * /usr/lib/python3/dist-packages/html5lib/_trie/_base.py:3: DeprecationWarning: Using or importing the ABCs from 'collections' instead of from 'collections.abc' is deprecated since Python 3.3, and in 3.10 it will stop working
 *   from collections import Mapping
 *WARNING: You are using a local hash equivalence server but have configured an sstate mirror. This will likely mean no sstate will match from the mirror. You may wish to disable the hash equivalence use (BB_HASHSERVE), or use a hash equivalence server alongside the sstate mirror.
 *ERROR:  OE-core's config sanity checker detected a potential misconfiguration.
 *    Either fix the cause of this error or at your own risk disable the checker (see sanity.conf).
 *    Following is the list of potential problems / advisories:
 *
 *    Please use a umask which allows a+rx and u+rwx
 * @endcode
 *
 * - - - -
 *
 * @section yocto_faq21 Question 21: How is the quality assurance (QA) issue [ldflags] resolved?
 *  <b>Answer</b> Error log:
 * @code {.c}
 * File '<file>' in package '<package>' doesn't have GNU_HASH (didn't pass LDFLAGS?)
 * @endcode
 *
 * This error occurs because LDFLAGS passes the link parameter
 * <b>-Wl,--hash-style=gnu</b> by default, but not the compile library without using this link parameter.
 *
 * Three solutions are as shown below:
 * - Compile the dynamic library with the linking parameter <b>-Wl,--hash-style=gnu</b>
 * - Change the default link parameter to sysv; add <b>LINKER_HASH_STYLE = "sysv"</b> to
 *   `conf/local.conf` in the output directory
 * - Ignore the error; add <b>INSANE_SKIP:${PN} += "ldflags"</b> to the recipe file
 *
 * For more details regarding the difference between gnu and sysv, refer to the page
 * https://answerywj.com/2020/05/14/ld-hash-style/.
 *
 * - - - -
 *
 * @section yocto_faq22 Question 22: How is the QA issue [dev-so] resolved?
 * <b>Answer:</b> Error log:
 * @code {.c}
 * non -dev/-dbg/nativesdk- package contains symlink .so: <packagename> path '<path>' [dev-so]
 * @endcode
 *
 * This error occurs beause the release package is packed with symbolic links. For more
 * details, refer to the page
 * https://docs.yoctoproject.org/dev-manual/common-tasks.html#working-with-pre-built-libraries.
 *
 * The two solutions are as follows:
 * - Ignore the error and add <b>INSANE_SKIP:${PN} += "dev-so"</b> to the recipe
 *   file (Ambarella Yocto build is the current methods used)
 * - More detailed descriptions of packaged objects are in the recipe, as shown below:
 * @code {.c}
 * FILES:${PN}-dev = "${includedir} ${libdir}/lib*.so"
 * FILES:${PN} = "${libdir}/lib*.so.*.*.*"
 * @endcode
 *
 * - - - -
 *
 * @section yocto_faq23 Question 23: How is the QA issue [file-rdeps] resolved?
 * <b>Answer:</b> Error log:
 * @code {.c}
 * <packagename> requires <files>, but no providers in its RDEPENDS [file-rdeps]
 * @endcode
 *
 * If LDFLAGS specifies <b>-lsonamea</b> when compiling, users must add
 * <b>RDEPENDS:${PN} += "packagename1 packagename2"</b> to the recipe file.
 * If the error persists and the dependent dynamic library is versioned,
 * compile the dependent dynamic library with the link parameter <b>-Wl,-soname=libxxx.so</b>.
 *
 * For more details about link parameters, refer to the page
 * https://www.cnblogs.com/wangshaowei/p/11285332.html.
 *
 * - - - -
 *
 * @section yocto_faq24 Question 24: How is the QA issue [already-stripped] resolved?
 * <b>Answer:</b> Error log:
 * @code {.c}
 * File '<file>' from <recipename> was already stripped, this will prevent future debugging! [already-stripped]
 * @endcode
 *
 * This error occurs because the installed executable or dynamic library used the
 * strip command to remove debugging information. The user installation file should not
 * run first with the <b>$(STRIP)</b> command.
 *
 * If the user is unable to rebuild the library, the problem can be solved by ignoring the
 * error. Add <b>INSANE_SKIP:${PN} += "already-stripped"</b> to the recipe file.
 *
 * - - - -
 *
 * @section yocto_faq25 Question 25: How is the error message "Error: Unable to find a match: <packagename>" managed?
 * <b>Answer:</b> This error occurs during the do_rootfs task and is caused because a package
 * does not have any output, or the output is only header files and / or static library files.
 *
 * Two solutions are as shown below:
 * - Ignore the error and add <b>ALLOW_EMPTY:${PN} = "1"</b> to the recipe file.<br>
 * - Do not add this error package to the do_rootfs task variable <b>IMAGE_INSTALL:append</b>,
 *   and modify the <b>IGNORES_RECIPES</b> variable in `build/bin/yocto/inc-yocto-build.mk`.
 *
 * - - - -
 *
 * @section yocto_faq26 Question 26: How are errors such as "Error: Transaction test error" managed?
 * <b>Answer:</b> Error log:
 * @code {.c}
 * xxx do_rootfs: Could not invoke dnf. Command...
 * package_xxx
 * package_xxxx
 * ....
 * Error: Transaction test error: file xxx conflicts between attempted installs of xxx and xxx
 * @endcode
 *
 * The error is caused by the fact that the pathname of the file installed by a package
 * is the same as the pathname of the file installed by other packages. Users can only
 * change the file installed by one of the packages.
 *
 * Sometimes, users use their own recipe to compile open source packages, and the Yocto build system
 * also has a default recipe. The <b>do_rootfs</b> task may also run with errors.
 * For example, if users use their own recipe to compile the zlib open source library, the
 * <b>do_rootfs</b> task will report the following error:
 * @code {.c}
 * Error:
 *  Problem: package libkmod2-29-r0.cortexa53 requires libz1 >= 1.2.11, but none of the providers can be installed
 *   - package systemd-1:250.5-r0.cortexa53 requires libkmod.so.2()(64bit), but none of the providers can be installed
 *   - package systemd-1:250.5-r0.cortexa53 requires libkmod.so.2(LIBKMOD_5)(64bit), but none of the providers can be installed
 *   - package systemd-1:250.5-r0.cortexa53 requires libkmod2 >= 29, but none of the providers can be installed
 *   - cannot install both libz1-1.2.11-r0.cortexa53 and libz1-1.0-r0.cortexa53
 *   - package packagegroup-core-boot-1.0-r17.v5 requires systemd, but none of the providers can be installed
 *   - conflicting requests
 * (try to add '--allowerasing' to command line to replace conflicting packages or '--skip-broken' to skip uninstallable packages)
 * @endcode
 *
 * Then, users can delete the custom recipe and use the official recipe instead.
 *
 * - - - -
 *
 * @section yocto_faq27 Question 27: How can the recipe be prepared so that the package can be recompiled at each time?
 * <b>Answer:</b> If a package is to be recompiled in each build, such as in AMBoot, the user can
 * use <b>bitbake -f packagename</b> to force the build; however, the following warning will appear:
 * <b>WARNING: xxx.bb:do_build is tainted from a forced run</b>
 * If a package does not require mandatory compilation but requires recompilation
 * each time, the user must set the task attribute <b>do_compile[nostamp] = "1"</b>
 * in the recipe file.
 * For more information about variable flags, refer to the page
 * https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-metadata.html?highlight=nostamp#variable-flags.
 *
 * - - - -
 *
 * @section yocto_faq28 Question 28: How are new user-customized tasks created?
 * <b>Answer:</b> Users require at least three elements to create a task: task function, execution directory,
 * and task declaration. If the task depends on other packages, users must also
 * set the dependencies.
 *
 * The dirs depends and postfuncs properties are referenced in variable flags
 * (https://docs.yoctoproject.org/bitbake/bitbake-user-manual/bitbake-user-manual-metadata.html?highlight=nostamp#variable-flags),
 * where the last directory listed in dirs is used as the task's current working directory.
 * The addtask can also be added before (run this task before other tasks) and
 * after (run this task before other tasks) instructions.
 * @code {.c}
 * do_${task_name} () {
 * 	oe_runmake ${task_name}
 * }
 * do_${task_name}[dirs] = "${B}"
 * do_${task_name}[depends] += "depend_package_name1:task_name depend_package_name2:task_name"
 * addtask ${task_name}
 * @endcode
 *
 * Add task to the board's build recipe: add the cv25_yocto_config task to
 * load specific Kconfig configuration.
 * @code {.c}
 * do_cv25_yocto_config () {
 * 	oe_runmake -f amba.mk cv25_yocto_config
 * }
 * do_cv25_yocto_config[dirs] = "${B}"
 * do_cv25_yocto_config[nostamp] = "1"
 * do_cv25_yocto_config[depends] += "kconfig-native:do_populate_sysroot"
 * do_cv25_yocto_config[postfuncs] += "do_setrecompile"
 * addtask cv25_yocto_config
 * @endcode
 *
 * - - - -
 *
 * @section yocto_faq29 Question 29: How are local Yocto builds accelerated?
 * <b>Answer:</b> To save resources, Ambarella limits the maximum number of tasks which can run
 * in parallel at any one time. Users can speed up a local Yocto build by explicitly modifying or simply
 * deleting the `BB_NUMBER_THREADS` variable in the script `ambarella/build/envyocto-build.env`.
 * If the user removes this variable in the script file, they set this variable to
 * the maximum number of CPUs on the user local build host.
 * For more information about the `BB_NUMBER_THREADS` variable, refer to the page
 * https://docs.yoctoproject.org/4.0.6/singleindex.html#term-BB_NUMBER_THREADS.
 *
 * For example, modify `BB_NUMBER_THREADS` to 64:
 * @code {.c}
 * ambarella/build/env/yocto-build.env
 *
 * ...
 * # Setting the machine in the "meta-xxx/conf/machine/"
 * MACHINE = "${AMBA_SOC_SERIES}"
 *
 * # Setting the maximum number of threads BitBake simultaneously executes
 * BB_NUMBER_THREADS = "64"
 *
 * # Setting the save path of image
 * DEPLOY_DIR_IMAGE = "\${TOPDIR}/images"
 * ...
 * @endcode
 *
 * @note
 * The value of `BB_NUMBER_THREADS` should not be greater than the maximum number of CPUs on
 * the user local build host.
 *
 * - - - -
 *
 * @section yocto_faq30 Question 30: How is the fetcher issue "Fetcher failure for URL: 'https://yoctoproject.org/connectivity.html'." resolved?
 * <b>Answer:</b> This issue is caused by inability to access the Yocto connectivity URL,
 * the check is executed by the function `check_connectivity` in `build/poky/meta/classes/sanity.bbclass`.
 * Users can directly close this check: add `CONNECTIVITY_CHECK_URIS = ""` to
 * `ambarella/out/yocto_out/<board>/conf/local.conf`.
 *
 * - - - -
 *
 * @section yocto_faq31 Question 31: How is the error message "meson: error: unrecognized arguments: --pkg-config-path" in Ubuntu resolved?
 * <b>Answer:</b> Error log:
 * @code {.c}
 * meson: error: unrecognized arguments: --pkg-config-path=/home/mk/Code/cv2x_linux_sdk_4.0/out/amba_out/cv22_walnut/sysroot/usr/lib/pkgconfig
 * amba.mk:543: recipe for target 'all' failed
 * make[2]: *** [all] Error 2
 * /home/mk/Code/cv2x_linux_sdk_4.0/ambarella/out/amba_out/cv22_walnut/config/auto.mk:12282: recipe for target 'oryxv2' failed
 * @endcode
 *
 * This error occurs because the version of meson (0.45.1) used to compile oryxv2 module is too old.
 * Following shell script can help users to upgrade meson to a new one. Before using the following shell script,
 * users must install <b> python3 </b> and <b> python3-pip </b>:
 *
 * @code {.c}
 * #!/bin/bash
 *
 * # Version of meson should be greater than 0.56.0
 * MESON_REFER_MAJOR=0
 * MESON_REFER_MINOR=56
 * MESON_REFER_PATCH=0
 *
 * # Check whether meson has been installed or not
 * MESON_PATH=$(which meson)
 *
 * # Flag indicates whether a newer meson needs to be installed.
 * MESON_NEED_INSTALL_FLAG=0
 *
 * if [[ x$MESON_PATH != x ]]; then
 *   # meson has been install, we need to check the version of meson.
 *   MESON_VERSION=`meson --version`
 *   MESON_VERSION_MAJOR=`echo $MESON_VERSION | cut -d '.' -f 1`
 *   MESON_VERSION_MINOR=`echo $MESON_VERSION | cut -d '.' -f 2`
 *   MESON_VERSION_PATCH=`echo $MESON_VERSION | cut -d '.' -f 3`
 *   if [[ $MESON_VERSION_MAJOR -lt $MESON_REFER_MAJOR ]]; then
 * 	   MESON_NEED_INSTALL_FLAG=1
 * 	   echo "version of meson ($MESON_VERSION) in your building machine is too old and it will be reinstall."
 *   elif [[ $MESON_VERSION_MAJOR -eq $MESON_REFER_MAJOR ]]; then
 * 	   if [[ $MESON_VERSION_MINOR -lt $MESON_REFER_MINOR ]]; then
 * 	 	   MESON_NEED_INSTALL_FLAG=1
 * 		   echo "version of meson ($MESON_VERSION) in your building machine is too old and it will be reinstall."
 * 	   elif [[ $MESON_VERSION_MINOR -eq $MESON_REFER_MINOR ]]; then
 * 		   if [[ $MESON_VERSION_PATCH -lt $MESON_REFER_PATCH ]]; then
 * 			   MESON_NEED_INSTALL_FLAG=1
 * 			   echo "version of meson ($MESON_VERSION) in your building machine is too old and it will be reinstall."
 * 		   fi
 * 	   fi
 *   fi
 *
 *   # Check whether meson on building machine needs to be reinstall.
 *   if [[ $MESON_NEED_INSTALL_FLAG -eq 1 ]]; then
 *     sudo apt-get purge meson
 *   fi
 * else
 * 	 MESON_NEED_INSTALL_FLAG=1
 * fi
 *
 * if [[ $MESON_NEED_INSTALL_FLAG -eq 1 ]]; then
 * 	 echo "Meson with version 1.0 will be installed."
 * 	 sudo pip3 install meson==1.0
 * fi
 * @endcode
 *
 * - - - -
 *
 * @section yocto_faq32 Question 32: How is the error message "Transaction test error: file /usr/lib/systemd conflicts between attempted installs" resolved?
 * <b>Answer:</b> Error log:
 * @code {.c}
 * Error: Transaction test error:
 * file /usr/lib/systemd conflicts between attempted installs of network-init-0.0.1-r0.cortexa53_crypto and dsp-reset-service-1.0-r0.cortexa53_crypto
 * file /usr/lib/systemd/system conflicts between attempted installs of network-init-0.0.1-r0.cortexa53_crypto and dsp-reset-service-1.0-r0.cortexa53_crypto
 * @endcode
 *
 * This error is caused by files permissions, users can try this way to fix the issue.
 * @code {.c}
 * cooper_sdk/ambarella$ cd rootfs/network/
 * cooper_sdk/ambarella/rootfs/network/$ find -type f -exec chmod 644 {} \;
 * cooper_sdk/ambarella/rootfs/network/$ find -type d -exec chmod 755 {} \;
 * @endcode
 * Then, users can re-compile (Do not delete 'out/' but must rerun make ipcam_config before make).
 *
 * If this solution does not work, users can try another way (set the umask value to 0022 and pull the code again).
 *
 * - - - -
 *
 * @section yocto_faq33 Question 33: How to prepare Yocto mirror and sstate-cache?
 * Follow the steps below to prepare Yocto mirror and sstate-cache:
 * @code {.c}
 * 1. Clean up the SDK output.
 *    cooper_sdk/ambarella$ rm -rf out
 * 2. Initialize the Yocto environment. (such as cv22_walnut)
 *    cooper_sdk/ambarella$ source build/env/yocto-build.env cv22_walnut
 * 3. Modify the local.conf to set the SSTATE_MIRRORS and SOURCE_MIRROR_URL to invalid values, and add a line: BB_GENERATE_MIRROR_TARBALLS = "1"
 *    cooper_sdk/ambarella/out/yocto_out/cv22_walnut$ vi conf/local.conf
 * 4. Choose a config and select OSS as many as possible.
 *    cooper_sdk/ambarella/out/yocto_out/cv22_walnut$ make ipcam_config i=ros-image
 * 5. Fetch the source code.
 *    cooper_sdk/ambarella/out/yocto_out/cv22_walnut$ bitbake ros-image --runonly=fetch
 * 6. Compile.
 *    cooper_sdk/ambarella/out/yocto_out/cv22_walnut$ make ros-image
 * @endcode
 * After the operations above are completed, users can find the cache below `out/mirror-cache`.
 *
 * - - - -
 *
 */
