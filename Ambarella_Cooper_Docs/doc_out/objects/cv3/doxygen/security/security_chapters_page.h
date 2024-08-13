/*!
 * @file doc_security_ov_page.h
 * @brief
 * @version 1.0
 * @date 2022-07-21
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
 * @page security_overview Overview
 *
 * @section sec_solution 1. System Security Solution
 *
 * The Ambarella system on chip (SoC) provides a total system security solution called <b>Pan Shi</b>.
 *
 * Pan Shi covers six major aspects:
 * - System integrity protection
 * - System reinforcement
 * - Data storage protection
 * - Data transfer protection
 * - Intellectual property protection
 * - User privacy protection
 *
 * Pan Shi includes both hardware (chip-level and circuit-level) security design and software
 * (firmware, operating system (OS)), as well as user-space software security design.
 * Pan Shi employs highly-advanced cryptography algorithms and widely-used security protocols,
 * industry standard architecture, and security methodology.
 *
 * The Pan Shi design philosophy is open, flexible, efficient, renewable, defense in depth (DID),
 * and compartmental, making it an optimal solution for system security.
 * @image html aspects_of_pan_shi.png "Figure 1-1. Six Major Aspects of Pan Shi."
 *
 * This section provides the guidelines for the system and software design of the Pan Shi
 * security solution, which is provided in the Ambarella Flexible Linux Software Development Kit (SDK).
 *
 * The following essential security features for Pan Shi will be introduced:
 * - Secure boot
 * - Trusted execution environment (TEE) and Arm® TrustZone®
 * - Secure enhanced bootloader (BLD)
 * - Data encryption and secure storage
 * - Unit license protection (ULP)
 * - Neural network (NN) model protection
 * - Mandatory access control (MAC) mechanism (such as SELinux)
 * - Secure hardware
 * - Unique ID
 * - One-time programmable (OTP)
 * - True random number generator (TRNG)
 * - And more
 *
 * @subsection sec_related_sec_features 1.1 Pan Shi Security Features
 *
 * The table on the following page shows the relationship between Pan Shi and the detailed security features.
 * <table>
 * <caption id="pan_shi_aspects"></caption>
 * <tr><th align="left">Pan Shi Aspect<th align="left">Security Feature<th align="left">Brief Description
 * <tr><td rowspan="3"><B>System integrity protection</B>
 *                      <td> Secure boot                                                   <td> Guarantees that the booted firmware is not tampered with
 * <tr>                 <td> Secure over the air (OTA)                                     <td> Guarantees that the upgraded firmware is not tampered with
 * <tr>                 <td> Linux dm-verity                                               <td> Detects if the file system has been tampered with
 * <tr><td rowspan="8"><B>System reinforcement</B>
 *                      <td> Secure enhanced bootloader                                    <td> Authenticates before executing the command in the bootloader
 * <tr>                 <td> Secure enhanced Linux                                         <td> Mandatory access control
 * <tr>                 <td> Arm® TrustZone®                                               <td> Trusted execution environment
 * <tr>                 <td> Anti-rollback                                                 <td> Prevents the rollback attack
 * <tr>                 <td> Disable hardware debug port                                   <td> Prevents attacks via the hardware debug tool
 * <tr>                 <td> Disable non-secure protocol / port                            <td> Minimizes attacking surface
 * <tr>                 <td> Resistance to the buffer overflow attack                      <td> Increases the difficulty of the buffer overflow attack
 * <tr>                 <td> Dynamic random-access memory (DRAM) scrambling                <td> Prevents runtime memory sniffers
 * <tr><td rowspan="3"><B>Data storage protection</B>
 *                      <td> Linux dm-crypt                                                <td> Partition encryption
 * <tr>                 <td> Secure storage by OP-TEE                                      <td> Secure storage
 * <tr>                 <td> Data encryption and data at rest protection                   <td> Data encryption and data at rest protection
 * <tr><td rowspan="3"><B>Data transfer protection</B>
 *                      <td> TLS in Linux                                                  <td> Secures connection between the Linux application and the cloud
 * <tr>                 <td> TLS in OP-TEE                                                 <td> Secures connection between the trusted application (TA) and the cloud
 * <tr>                 <td> Secure connection in CVflow®                                  <td> Secures the connection between CVflow® and the cloud
 * <tr><td rowspan="2"><B>Intellectual property protection</B>
 *                      <td> ULP by CVflow® and CV0                                        <td> Unit license by CVflow and CV0
 * <tr>                 <td> NN model protection                                           <td> NN model protection by CVflow
 * <tr><td rowspan="3"><B>User privacy protection</B>
 *                      <td> Application programming interface (API) for vision processing <td> Secure vision processing
 * <tr>                 <td> API for secure storage                                        <td> Stores data securely on the device
 * <tr>                 <td> API for secure transfer                                       <td> Transfers only non-user privacy data to cloud securely
 * </table>
 *
 * - - - -
 *
 * @section sec_sw_hierarchy 2. Security Software Hierarchy
 *
 * The following diagram shows the software framework of the SoC.
 *
 * @image html sw_hierarchy_on_chip.png "Figure 2-1. Software Hierarchy on Chip."
 *
 * The following diagram shows the software framework for the Linux PC.
 *
 * @image html sw_hierarchy_for_linux_pc.png "Figure 2-2. Software Hierarchy for the Linux PC."
 *
 * - - - -
 * @section partitions 3. Introduction to Partitions
 *
 * The following describes the partitions.
 * - <B>Bootstrap (BST):</B> The BST size is 8 KB with a 32-byte signature at the tail.  BST is signed with the root of trust (RoT) key
 * - <B>Arm-trusted firmware (ATF):</B> ATF stores BL2 (ATF).  BL2 is used to load and verify the following modules: BL31, BL32, BL33, chain of trust (CoT), and DTB.  ATF is signed with the RoT key
 * - <B>Bootloader (BLD):</B> BLD stores the firmware-in-package (FIP), which includes BL31, BL32, and BL33.  BL31 is the secure monitor for ATF, BL32 is the trusted OS (OP-TEE-OS), and BL33 is for the AMBoot / other bootloader.  BL31, BL32, and BL33 are signed with keys in CoT certificates.
 * - <B>Primary (PRI) / secondary (SEC):</B> PRI / SEC stores the Linux kernel.  The Linux kernel is signed with a kernel key
 * - <B>Linux (LNX):</B> LNX stores the Linux file system
 * - <B>Partition table (PTB)</B>
 *
 *
 */

/*!
 * @file system_integrity_protection.h
 * @brief
 * @version 1.0
 * @date 2023-12-11
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
 * @page sys_integrity_protection System Integrity Protection
 * @section sec_boot 1. Secure Boot by Built-In Hardware Engine
 *
 * Secure boot is a mechanism which guarantees that only the trusted firmware is executed.
 * Typically, the digital signature is used to identify if the loaded firmware is secure or corrupt.
 * Only the private key owner is able to generate the correct digital signature, and the public key on the device is protected by hardware, such as one-time programmable (OTP).
 * The private key and the public key in OTP constitute the "key pair."
 *
 * The boot sequence includes several components which must authenticate the following component before it can be executed.
 * The complete authentication chain that includes the "not-tampered public key" and the "not-leaked private key" successfully achieves the secure boot.
 *
 * @subsection auth_chain 1.1 Authentication Chain
 *
 * Code execution begins with the code built into the system on chip (SoC)'s read-only memory (ROM).  The ROM code with the digital signature check capability is called Secure ROM.
 *
 * The following diagram illustrates the @ref Authentication_Chain_of_the_Secure_Boot_With_Arm_TrustZone and @ref Authentication_Chain_of_the_Secure_Boot_Without_Arm_TrustZone.
 * The black line indicates the boot sequence, while the blue dashed line represents the authentication key and target.
 *
 * @anchor Authentication_Chain_of_the_Secure_Boot_With_Arm_TrustZone
 * @image html auth_chain_sec_boot.png "Figure 1-1. Authentication Chain of Secure Boot With Arm® TrustZone®."
 *
 * @anchor Authentication_Chain_of_the_Secure_Boot_Without_Arm_TrustZone
 * @image html auth_chain_without_sec_boot.png "Figure 1-2. Authentication Chain of the Secure Boot Without Arm TrustZone."
 *
 * The secure boot authentication chain includes three stages, as follows:
 * -# First, the Secure ROM code covers ROM to bootstrapper (BST), and BST to BL2 (ATF)
 * -# Next, the Arm trusted firmware (ATF) (BL2) code covers the second stage:
 *  - BL2 (ATF) to BL31 (ATF)
 *  - BL2 (ATF) to BL32 (OP-TEE)
 *  - BL2 (ATF) to BL33 (AMBoot)
 * -# Finally, the AMBoot code (BL33) covers the third stage:
 *  - BL33 (AMBoot) to the Linux kernel
 * OTP stores the root of trust (RoT) public key (PK).  The RoT PK is used to authenticate the BST and the ATF (BL2).
 * The keys in chain of trust (CoT) certificates are used to authenticate BL31, BL32, and BL33.  The kernel key authenticates the Linux kernel.
 *
 * @subsection cot 1.2 Chain of Trust
 *
 * ATF defines the CoT, which describes the root key (CoT root) and its derived keys.
 * The figure illustrates the ATF chain of trust.
 *
 * @anchor Chain_of_Trust_as_Defined_by_ATF
 * @image html chain_of_trust.png "Figure 1-3. Chain of Trust as Defined by ATF."
 *
 * @subsection chose_crypt_alg 1.3 Chosen Cryptography Algorithms
 *
 * The secure boot employs EdDSA (ED25519 and SHA2-512) for digital signature authentication.
 * The CoT in ATF uses RSA or ellipse curve cryptography (ECC) as an asymmetric cryptography.
 *
 * @subsection mem_layout 1.4 System Memory Layout
 * When a secure operating system (OS) (BL32) is required for Arm TrustZone, it will require approximately 16 MB of memory.  The tables below provide the different system memory
 * layouts with and without Arm TrustZone.
 * Users can also update the BL33 start address and the Linux (kernel) start address in menuconfig.
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *	boot  --->
 *	 amboot (boot/ambamk)  --->
 *	  Ambarella Firmware Configuration  --->
 *	   Memory Options --->
 *	    (0x01c00000) AMBoot starting address  // BL33 start address
 *	 Memory --->
 *	  (0x02000000) Kernel start address    // Linux (Kernel) start address
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *	recipes-bsp  --->
 *	 amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *	  Ambarella Firmware Configuration  --->
 *	   Memory Options --->
 *	    (0x01c00000) AMBoot starting address  // BL33 start address
 *	 Memory --->
 *	  (0x02000000) Kernel start address    // Linux (Kernel) start address
 * @endcode
 *
 * @note
 * When the bootloader (BLD) address changes with Arm TrustZone enabled, the firmware programming start address must be changed accordingly.  Otherwise, the firmware programming
 * will conflict with the bootloader in memory.  Re-downloading non-TrustZone firmware will fail, for example, when the board is using TrustZone-enabled firmware.  To prevent this
 * potential failure, change the firmware programming start address of the non-TrustZone firmware, then re-compile.
 *
 * @subsubsection mem_layout_with_tz 1.4.1 With Arm TrustZone
 * Users can refer to `ambarella\boot\amboot\doc\mem_layout.txt`.
 *
 * <table>
 * <caption id="System_Memory_Layouts_with_Arm_TrustZone">Table 1-1. System Memory Layouts with Arm TrustZone.</caption>
 * <tr><th align="left">Major<th align="left">Sub1<th align="left">Sub2<th align="left">Start Address<th align="left">End Address<th align="left">Total Size
 * <tr><td rowspan="4"><B>Secure World Memory</B>
					<td>ATF (BL2)<td>  <td>0x00000000<td>0x0007FFFF<td>512 KB
 * <tr>				<td>ATF (BL31)<td> <td>0x00080000<td>0x000FFFFF<td>512 KB
 * <tr><td rowspan="2">Open portable trusted execution environment (OP-TEE) (BL32)<td>Trusted execution environment (TEE) memory<td>0x00100000<td>0x001FFFFF<td>1 MB
 * <tr>							   <td>Trusted application (TA) memory<td>0x00200000<td>0x013FFFFF<td>18 MB
 * <tr><td rowspan="4"><B>Normal World Memory</B>
 *					<td>Shared memory<td> <td>0x01400000<td>0x017FFFFF<td>4 MB
 * <tr>				<td>EL2 RSVD<td> <td>0x01800000<td>0x01BFFFFF<td>4 MB
 * <tr>				<td>BLD (BL33)<td> <td>0x01C00000<td>0x01FFFFFF<td>4 MB
 * <tr>				<td>Linux<td> <td>0x02000000<td> <td>Total: 32 MB
 * </table>
 *
 * @subsubsection mem_layout_without_tz 1.4.2 Without Arm TrustZone
 *
 * <table>
 * <caption id="System_Memory_Layouts_without_Arm_TrustZone">Table 1-2. System Memory Layouts without Arm TrustZone.</caption>
 * <tr><th align="left">Modules<th align="left">Start Address<th align="left">End Address<th align="left">Total Size
 * <tr>				<td><B>ATF (BL2)</B><td>0x00000000<td>0x0007FFFF<td>512 KB
 * <tr>				<td><B>ATF (BL31)</B><td>0x00080000<td>0x000FFFFF<td>512 KB
 * <tr>				<td><B>BLD (BL33)</B><td>0x00100000<td>0x0047FFFF<td>3.5 MB
 * <tr>				<td><B>Linux</B> <td>0x01C00000<td> <td>Total size: 28 MB
 * </table>
 *
 * @subsection sec_boot_user_guide 1.5 User Guide
 * Refer to @ref key_management for more information.
 *
 * @section sec_ota 2. Secure Over the Air (OTA)
 *
 * @subsection online_upgrade 2.1. Online Upgrade
 * Users can upgrade each partition with the tools provided by Ambarella.
 *
 * @subsubsection partition_with_sec_boot_on 2.1.1 Partition Locations with Secure Boot Enabled
 * When secure boot is enabled, partitions such as BST, BLD, ATF, and primary (PRI) are signed.  The items below list their locations.
 *
 * <B>Amba build:</B>
 * - <B>BST:</B> `ambarella/out/<board> /objects/boot/amboot/bst_release.bin.signed`
 * - <B>BLD:</B> `ambarella/out/<board>/objects/boot/amboot/fip.bin`
 * - <B>ATF:</B>  `ambarella/out/<board>/objects/boot/amboot/atf.bin.signed`
 * - <B>PRI:</B>  `ambarella/out/<board>/images/Image.SIGNED`
 *
 * <B>Yocto build:</B>
 * - <B>BST:</B> `ambarella/out/<board>/tmp/work/cortexa53-crypto-poky-linux/amboot/1.0-r0/amboot-1.0/bst_release.bin.signed`
 * - <B>BLD:</B> `ambarella/tmp/work/cortexa53-crypto-poky-linux/amboot/1.0-r0/amboot-1.0/fip.bin`
 * - <B>ATF:</B> `ambarella/tmp/work/cortexa53-crypto-poky-linux/amboot/1.0-r0/amboot-1.0/atf.bin.signed`
 * - <B>PRI:</B> `ambarella/out/<board>/images/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED`
 *
 * @subsubsection enable_upgrade_tool 2.1.2 Enable the Upgrade Tool
 * To enable the upgrade tool, select the following items in `make menuconfig`.
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *	app  --->
 *	 utility  --->
 *	  upgrade_partition  --->
 *	   upgrade-partition (app/utility/upgrade_partition/app)
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *	meta-ambaapp  --->
 *	 recipes-upgrade-partition  --->
 *	   upgrade-partition (meta-ambaapp/recipes-upgrade-partition/upgrade-partition)
 * @endcode
 *
 * @subsubsection upgrade_partition_on_board 2.1.3 Upgrade the Partition on Board
 * -# Place or mount the partition to be upgraded on the board (use `/mnt/partition/<partition file>` for example).
 * -# Upgrade the partition with tools.  Below are two examples, one for the electronic logic gate NAND and one for the embedded multi-media controller (eMMC).
 * -# The following lists the partition file locations.<br>
 * <B>BST partition file:</B>
 * @code
 * a. amba-build:
 *  ambarella/out/amba_out/cv5_timn/amboot/bst_release.bin.signed
 * b. yocto-build:
 *  ambarella/out/yocto_out/cv5_timn/tmp/work/cortexa76-poky-linux/amboot/1.0-r0/ deploy-amboot/bst_release.bin.signed
 * @endcode
 * <B>ATF partition file:</B>
 * @code
 * a. amba-build:
 * ambarella/out/amba_out/cv5_timn/amboot/atf.bin.signed
 * b. yocto-build:
 * ambarella/out/yocto_out/cv5_timn/tmp/work/cortexa76-poky-linux/amboot/1.0-r0/deploy-amboot/atf.bin.signed
 * @endcode
 * <B>BLD partition file:</B>
 * @code
 *  a. amba-build:
 *  ambarella/out/amba_out/cv5_timn/amboot/fip.bin
 *  b. yocto-build:
 *  ambarella/out/yocto_out/cv5_timn/tmp/work/cortexa76-poky-linux/amboot/1.0-r0/deploy-amboot/fip.bin
 * @endcode
 * <B>BAK partition file</B>
 * @code
 * a. amba-build:
 * ambarella/out/amba_out/cv5_timn/amboot/bakfw/bst_bld_atf_release.bin
 * b. yocto-build:
 * ambarella/out/yocto_out/cv5_timn/tmp/work/cortexa76-poky-linux/amboot/1.0-r0/ amboot-1.0/bakfw/bst_bld_atf_release.bin
 * @endcode
 * <B>Linux kernel file:</B>
 * @code
 * a. amba-build:
 * ambarella/out/amba_out/cv5_timn/kernel/Image.SIGNED
 * b. yocto-build:
 * ambarella/out/yocto_out/cv5_timn/images/Image--5.15.120-r0-cv5x-20230801023530.bin.SIGNED
 * @endcode
 * <B>Linux rootfs file:</B>
 * @code
 *  a. amba-build:
 *  1) NAND
 *   ambarella/out/amba_out/cv5_timn/rootfs/ubifs
 *  2) EMMC
 *  ambarella/out/amba_out/cv5_timn/rootfs/ext4
 *  yocto-build:
 *  1) NAND
 *  ambarella/out/yocto_out/cv5_timn/images/ipcam-image-cv5x-20230526073637.rootfs.ubi
 *  2) EMMC
 *  ambarella/out/yocto_out/cv5_timn/images/ipcam-image-cv5x-20230526073637.rootfs.ext4
 * @endcode
 * -# The commands to erase / upgrade partitions are as follows:
 * - <B>NAND:</B>
 *
 *  Amba build:
 * @code
 * BST:    flash_eraseall /dev/mtd0       upgrade_partition -p    /dev/mtd0  /sdcard/bst_release.bin.signed
 * BLD:    flash_eraseall /dev/mtd1       upgrade_partition -p -G /dev/mtd1  /sdcard/fip.bin
 * ATF:    flash_z`eraseall /dev/mtd3       upgrade_partition -p -H /dev/mtd3  /sdcard/atf.bin.signed
 * PRI:    flash_eraseall /dev/mtd5       upgrade_partition -p -K /dev/mtd5  /sdcard/Image.SIGNED
 * PBA:    flash_eraseall /dev/mtd4       upgrade_partition -p -Q /dev/mtd4  /sdcard/Image.SIGNED
 * LNX:    flash_eraseall /dev/mtd8       upgrade_partition -p -W /dev/mtd8  /sdcard/ubifs
 * ROM:    flash_eraseall /dev/mtd7       upgrade_partition -p -R /dev/mtd7  /sdcard/ubifs
 * BAK:    flash_eraseall /dev/mtd6       upgrade_partition -p -B /dev/mtd6  /sdcard/.bin file for backup（bst_bld_atf_release.bin）
 * @endcode
 *
 *  Yocto build:
 * @code
 * BST:    flash_eraseall /dev/mtd0       upgrade_partition -p    /dev/mtd0  /sdcard/bst_release.bin.signed
 * BLD:    flash_eraseall /dev/mtd1       upgrade_partition -p -G /dev/mtd1  /sdcard/fip.bin
 * ATF:    flash_eraseall /dev/mtd3       upgrade_partition -p -H /dev/mtd3  /sdcard/atf.bin.signed
 * PRI:    flash_eraseall /dev/mtd5       upgrade_partition -p -K /dev/mtd5  /sdcard/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED
 * PBA:    flash_eraseall /dev/mtd4       upgrade_partition -p -Q /dev/mtd4  /sdcard/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED
 * LNX:    flash_eraseall /dev/mtd8       upgrade_partition -p -W /dev/mtd8  /sdcard/ipcam-image-cv5x-20230526073637.rootfs.ubi
 * ROM:    flash_eraseall /dev/mtd7       upgrade_partition -p -R /dev/mtd7  /sdcard/ipcam-image-cv5x-20230526073637.rootfs.ubi
 * BAK:    flash_eraseall /dev/mtd6       upgrade_partition -p -B /dev/mtd6  /sdcard/bst_bld_atf_release.bin
 * @endcode
 *
 * - <B>eMMC</B>
 *
 *  Amba build:
 * @code
 * BST:    dd if=/dev/zero of=/dev/mmcblk0p1       upgrade_partition -p    /dev/mmcblk0p1  /sdcard/bst_release.bin.signed
 * BLD:    dd if=/dev/zero of=/dev/mmcblk0p2       upgrade_partition -p -G /dev/mmcblk0p2  /sdcard/fip.bin
 * ATF:    dd if=/dev/zero of=/dev/mmcblk0p4       upgrade_partition -p -H /dev/mmcblk0p4  /sdcard/atf.bin.signed
 * PRI:    dd if=/dev/zero of=/dev/mmcblk0p6       upgrade_partition -p -K /dev/mmcblk0p6  /sdcard/Image.SIGNED
 * PBA:    dd if=/dev/zero of=/dev/mmcblk0p5       upgrade_partition -p -Q /dev/mmcblk0p5  /sdcard/Image.SIGNED
 * LNX:    dd if=/dev/zero of=/dev/mmcblk0p9       upgrade_partition -p -W /dev/mmcblk0p9  /sdcard/ubifs
 * ROM:    dd if=/dev/zero of=/dev/mmcblk0p8       upgrade_partition -p -R /dev/mmcblk0p8  /sdcard/ubifs
 * BAK:    dd if=/dev/zero of=/dev/mmcblk0p7       upgrade_partition -p -B /dev/mmcblk0p7  /sdcard/.bin file for backup（bst_bld_atf_release.bin）
 * @endcode
 *
 *  Yocto build:
 * @code
 * BST:    dd if=/dev/zero of=/dev/mmcblk0boot0    upgrade_partition -p -b 1    /dev/mmcblk0boot0  /sdcard/bst_release.bin.signed
 * BLD:    dd if=/dev/zero of=/dev/mmcblk0p2       upgrade_partition -p -b 1 -G /dev/mmcblk0p2  /sdcard/fip.bin
 * ATF:    dd if=/dev/zero of=/dev/mmcblk0p4       upgrade_partition -p -b 1 -H /dev/mmcblk0p4  /sdcard/atf.bin.signed
 * PRI:    dd if=/dev/zero of=/dev/mmcblk0p6       upgrade_partition -p -b 1 -K /dev/mmcblk0p6  /sdcard/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED
 * PBA:    dd if=/dev/zero of=/dev/mmcblk0p5       upgrade_partition -p -b 1 -Q /dev/mmcblk0p5  /sdcard/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED
 * LNX:    dd if=/dev/zero of=/dev/mmcblk0p9       upgrade_partition -p -b 1 -W /dev/mmcblk0p9  /sdcard/ipcam-image-cv5x-20230526073637.rootfs.ext4
 * ROM:    dd if=/dev/zero of=/dev/mmcblk0p8       upgrade_partition -p -b 1 -R /dev/mmcblk0p8  /sdcard/ipcam-image-cv5x-20230526073637.rootfs.ext4
 * BAK:    dd if=/dev/zero of=/dev/mmcblk0p7       upgrade_partition -p -b 1 -B /dev/mmcblk0p7  /sdcard/bst_bld_atf_release.bin
 * @endcode
 *
 * @note
 * Partitions are located in different places with different file systems; users must change the upgrade command line to fit their own environment.  Users can find the partition location from the boot log:
 * @code
 * [1.060741]  (bst): 0x0000000000000000, 0x0000000000001000
 * [1.066215]  (bld): 0x0000000000001000, 0x0000000000100000
 * [1.071684]  (ptb): 0x0000000000101000, 0x00000000000e0000
 * [1.077152]  (atf): 0x00000000001e1000, 0x0000000000100000
 * [1.082620]  (pba): 0x00000000002e1000, 0x0000000001000000
 * [1.088088]  (pri): 0x00000000012e1000, 0x0000000001000000
 * [1.093559]  (lnx): 0x00000000022e1000, 0x0000000020000000
 * [1.099032]  (raw): 0x00000000222e1000, 0x00000001afeef000
 * [1.104496]  mmcblk0: p1(bst) p2(bld) p3(ptb) p4(atf) p5(pba) p6(pri) p7(lnx) p8(raw)
 * @endcode
 *
 * @subsection rescue_mode 2.2 Rescue Mode
 * Rescue mode uses the recovery partition (BAK) as a back-up boot option.
 * When there is an authentication failure (or a digital signature check failure), the boot can switch to rescue mode and boot from the recovery partition.
 * An authentication failure indicates unexpected contents in the external storage, which could be caused by an attack, an aging device, sudden power loss, or a system upgrade abortion, among
 * other causes.  Rescue mode enables manufacturers to attempt to repair the device online.
 * The figure below illustrates the boot sequence (red text represents the partition names), including rescue mode and the secure BAK partition with a digital signature.
 * In the BAK partition, only BL2, BL31, BL32, and BL33 can be included.
 *
 * @anchor Authentication_Chain_and_Partition_Layout_in_Rescue_Mode
 * @image html auth_chain_in_res_mode.png "Figure 1-4. Authentication Chain and Partition Layout in Rescue Mode."
 *
 * @note
 * - Firmware inside the recovery partition also includes a valid digital signature.
 * - If the BST is broken, rescue mode cannot function; the CPU will remain at Secure ROM until the damaged NAND is replaced.
 *
 * @subsubsection rescue_mode_with_mcu 2.2.1 Rescue Mode with External MCU
 * Due to the BST code size limit, selecting the normal boot path and the rescue boot path is explicitly triggered via the external microcontroller unit (MCU); therefore, an external MCU is
 * required for this rescue mode.
 *
 * @subsubsection rescue_mode_without_mcu 2.2.2 Rescue Mode without External MCU (V2)
 * On chips such as CV5x / CV7x, on which the BST code size is sufficient in order to embed auto-selected "normal boot" and "rescue boot" logic, Ambarella plans to enable "Rescue Mode v2",
 * which can function without an external MCU.
 * In Rescue Mode V2, the system selects “normal boot path” or “rescue boot path” automatically at the bootloader stage.  If the “normal boot path” fails multiple times, the system will reset
 * and attempt the “rescue boot path”.
 * There are two copies for A/B ping-pong switching for the Linux kernel and rootfs partitions.  The PRI and LNX partitions are A’s kernel and rootfs, while the PBA and ROM partitions are B’s
 * kernel and rootfs.  A and B are also fail-safe; the system will record the “last workable kernel and rootfs”.  If the “last workable kernel and rootfs” does not function, the system
 * marks the “last workable kernel and rootfs” to the other set and then resets the boot process.  Both the “normal boot path” and “rescue boot path” can function with A and B.
 * The success of kernel+Roofts boot is guarded by a watchdog; by default, the watchdog is internal.  If there is an external watchdog, support for “disable external watchdog” must be added.
 *
 * @anchor Authentication_Chain_and_Partition_Layout_in_Rescue_Mode_V2
 * @image html auth_chain_in_res_mode_v2.png "Figure 1-5. Authentication Chain and Partition Layout in Rescue Mode V2." 、
 *
 * Rescue Mode v2 is designed to guarantee fail-safes during system upgrade, except in very extreme cases (for example, the BST partition upgrade is aborted or the BST partition is damaged).
 * The recommended upgrade processes for different scenarios are listed below.  Except for the “BST partition” issue, all cases care fail-safe, meaning that the system is able to boot into
 * Linux and continue to complete the upgrade process.
 * The BST is located at the first NAND block.  The NAND manufacturer ensures that the first block is not easily corrupted.  OTA can perform a sanity check of the BST partition content before
 * programming the BST partition (a signature check with the RoT key inside OTP, as well as a cyclic redundancy check (CRC) for the partition).  Because the BST partition is small, the program
 * runs quickly.  A sudden loss of power in such a small time frame is extremely unlikely.
 * The result is a well-designed OTA process that, with Rescue Mode v2, covers almost all OTA failure cases.
 *
 * <table>
 * <caption id="Recommended_Upgrade_Processes_for_Different_Scenarios">Table 1-3.Recommended Upgrade Processes for Different Scenarios</caption>
 * <tr><th align="left">Scenarios<th align="left">Affect Partitions<th align="left">Recommended Steps<th align="left">Fail-safe Description<th align="left">Possibility<th align="left">Severity
 * <tr><td rowspan="4">RoT key revocation<td rowspan="4">BST, ATF, BLD, BAK
 *     <td rowspan="4">Step 1: upgrade BAK (new key)<br>Step 2: revoke RoT key<br>Step 3: upgrade BST (new key)<br>Step 4: upgrade ATF
 *     <td>Update BAK failed: no issues, the “normal boot path” is still OK<td> <td>Minor
 * <tr><td>Revoke key failed: no issues, “normal boot path” is OK<td> <td>Minor
 * <tr><td>Upgrade BST failed: return material authorization (RMA) is required; reprogram NAND or replace NAND<td>Very small<td>Critical
 * <tr><td>Upgrade ATF, BLD partition failed: no problem, “rescue boot path” is OK<td> <td>Minor
 * <tr><td rowspan="4">Kernel key revocation<td rowspan="4">BLD, BAK, PRI, LNX, PBA, ROM
 *     <td rowspan="4">Step 1: upgrade BAK (new key)<br>Step 2: upgrade PBA, ROM (new key)<br>Step 3: upgrade ATF, BLD (new key)<br>Step 4: upgrade PRI, LNX (new key)
 *     <td>Update BAK failed: no issues, “normal boot path” is OK<td> <td>Minor
 * <tr><td>Update PBA, ROM failed: no issues, “normal boot path” is OK<td> <td>Minor
 * <tr><td>Update ATF, BLD failed: no issues, “rescue boot path + B” is OK<td>Very small<td>Critical
 * <tr><td>Update PRI, LNX failed: no issues, “rescue boot path” + B is OK<td> <td>Minor
 * <tr><td>BST update / bugfix<td>BST<td>Update BST<td>Upgrade BST failed: RMA is required, reprogram NAND or replace NAND<td>Very small<td>Critical
 * <tr><td rowspan="2">ATF update / bugfix<td rowspan="2">ATF, BLD, BAK
 *     <td rowspan="2">Step 1: upgrade BAK<br>Step 2: upgrade ATF, BLD
 *     <td>BAK failed: no issues, “normal boot path” is OK<td> <td>Minor
 * <tr><td>Upgrade ATF, BLD failed: no issues, “rescue boot path” is OK<td> <td>Minor
 * <tr><td rowspan="2">OP-TEE OS and AMBoot update / bugfix<td rowspan="2">BLD, BAK
 *     <td rowspan="2">Step 1: upgrade BAK<br>Step 2: upgrade BLD
 *     <td>BAK failed: no issues, “normal boot path” is OK<td> <td>Minor
 * <tr><td>Upgrade BLD failed: no issues, “rescue boot path” is OK<td> <td>Minor
 * <tr><td>Update Linux, maintain compatibility<td>PRI, LNX<td>Update PRI, LNX<td>Upgrade PRI, LNX failed: no issues, B (PBA, ROM) is OK<td> <td>Minor
 * <tr><td rowspan="2">Update Linux, do not maintain compatibility<td rowspan="2">PRI, LNX, PBA, ROM
 *     <td rowspan="2">Step 1: upgrade PBA, ROM<br>Step 2: upgrade PRI, LNX
 *     <td>Upgrade PBA, ROM failed: no issues, A (PRI, LNX) is OK<td> <td>Minor
 * <tr><td>Upgrade PRI, LNX failed: no issues, B (PBA, ROM) is OK <td> <td>Minor
 * <tr><td rowspan="3">Update Linux, do not maintain compatibility<td rowspan="3">BST, ATF, BLD, BAK, PRI, LNX, PBA, ROM
 *     <td rowspan="3">Step 1: upgrade BAK, PBA, and ROM<br>Step 2: upgrade BST<br>Step 3: upgrade ATF, BLD, PRI, and LNX
 *     <td>Upgrade BAK, PBA, ROM failed: no issues, “normal boot path” + A is OK<td> <td>Minor
 * <tr><td>Upgrade BST failed: RMA is required, reprogram NAND or replace NAND<td>Very small<td>Critical
 * <tr><td>Upgrade ATF, BLD, PRI, LNX failed: no issues, “rescue boot path” + B is OK<td> <td>Minor
 * </table>
 *
 * <B>Getting Started</B>
 *
 * To build firmware with Rescue Mode v2, the following configurations must be selected in menuconfig. Or, users can use the existing board configuration: `xxx_rescue_config` or
 * `xxx_emmc_rescue_config`.
 * Select `Recovery Firmware Images` in `menuconfig`:
 * @code
 *  Prompt: Build Recovery Firmware Images
 * │   Depends on: CONFIG_BOOT [=y] && CONFIG_BOOTLOADER_AMBOOT [=y]
 * │   Location:
 * │    Main menu
 * │     -> meta-ambabsp
 * │      -> recipes-bsp
 * │       -> boot (meta-ambabsp/recipes-bsp/boot) (CONFIG_BOOT [=y])
 * │        -> Bootloader
 * │         -> Ambarella Firmware Configuration
 * │          -> AMBoot Options
 * │           -> Build Recovery Firmware Images (BUILD_FIRMWARE_RECOVERY [=y])
 * @endcode
 * Select `Without External MCU` in `menuconfig`:
 * @code
 * │   Prompt: Build Recovery Firmware Images
 * │   Depends on: CONFIG_BOOT [=y] && CONFIG_BOOTLOADER_AMBOOT [=y]
 * │   Location:
 * │	    Main menu
 * │     -> meta-ambabsp
 * │      -> recipes-bsp
 * │       -> boot (meta-ambabsp/recipes-bsp/boot) (CONFIG_BOOT [=y])
 * │        -> Bootloader
 * │         -> Ambarella Firmware Configuration
 * │          -> AMBoot Options
 * │           -> Build Recovery Firmware Images (BUILD_FIRMWARE_RECOVERY [=y])
 * @endcode
 * Select `Without External MCU` in `menuconfig`:
 * @code
 * │   Prompt: Auto Recovery Without External MCU
 * │   Depends on: CONFIG_BOOT [=y] && CONFIG_BOOTLOADER_AMBOOT [=y] && BUILD_FIRMWARE_RECOVERY [=y]
 * │   Location:
 * │    Main menu
 * │     -> meta-ambabsp
 * │      -> recipes-bsp
 * │       -> boot (meta-ambabsp/recipes-bsp/boot) (CONFIG_BOOT [=y])
 * │        -> Bootloader
 * │         -> Ambarella Firmware Configuration
 * │          -> AMBoot Options
 * │           -> Build Recovery Firmware Images (BUILD_FIRMWARE_RECOVERY [=y])
 * │            -> Auto Recovery Without External MCU
 * @endcode
 * Select `mtd-utils` in `menuconfig` (NAND):
 * @code
 * │   Prompt: mtd-utils (meta/recipes-devtools/mtd)
 * │   Location:
 * │    Main menu
 * │     -> meta
 * │      -> recipes-devtools
 * │       -> mtd-utils
 * @endcode
 * Select the bootstat driver in `menuconfig`:
 * @code
 * │   Prompt: kernel-module-bootstat (meta-ambabsp/recipes-bootstat/kernel-module-bootstat)│
 * │   Location:
 * │    Main menu
 * │     -> meta-ambabsp
 * │      -> recipes-bootstat
 * │       -> kernel-module-bootstat
 * @endcode
 * @note
 * If using eMMC, the boot arguments (bootargs) must be changed. In `ambarella/<board>/ bsp/xxx.dts`, change the bootargs to `console=ttyS0 noinitrd root=/dev/mmcblk0p9 rw rootfstype=ext4 rootwait`.
 *
 * <B>Check the Current Boot Mode</B>
 *
 * Users can check the kernel command line to see which partitions are used for the file system.
 *
 *  - <B>NAND:</B>
 *
 * If the file system is from the LNX partition, the kernel command line is printed as follows: `console=ttyS0 ubi.mtd=lnx root=ubi0:rootfs rw rootfstype=ubifs`.
 * If the file system is from the ROM partition, the kernel command line is printed as follows: `console=ttyS0 ubi.mtd=rom root=ubi0:rootfs rw rootfstype=ubifs`.
 *
 *  - <B>eMMC:</B>
 *
 * If the file system is from the LNX partition, the kernel command line is printed as follows: `console=ttyS0 noinitrd root=/dev/mmcblk0p9 rw rootfstype=ext4 rootwait`.
 * If the file system is from the ROM partition, the kernel command line is printed as follows: `console=ttyS0 noinitrd root=/dev/mmcblk0p8 rw rootfstype=ext4 rootwait`.
 *
 * <B>Check the Current Boot Path</B>
 * @code
 * Board# modprobe bootstat
 * Board# cat /proc/ambarella/bootstat
 *        boot   statu 0x0                        ---> Bootfrom Normal Mode
 *        system statu 0x5a5a                     ---> Bootfrom PRI+LNX
 *
 * Board# modprobe bootstat
 * Board# cat /proc/ambarella/bootstat
 *        boot   statu 0x35a5a                    ---> Bootfrom Recovery Mode
 *        system statu 0x5a5a                     ---> Bootfrom PRI+LNX
 *
 * Board# modprobe bootstat
 * Board# cat /proc/ambarella/bootstat
 *        statu 0x35a5a                    ---> Bootfrom Recovery Mode
 *        system statu 0xc0015a5a Swap            ---> Bootfrom PBA+ROM
 * @endcode
 * - <B>System Upgrade with RoT Key Revocation</B>
 * -# Upgrade the BAK partition with a new RoT key.
 *
 *  - <B>NAND:</B>
 * @code
 * board# flash_eraseall /dev/mtd6
 * board# upgrade_partition -p -B /dev/mtd6  /sdcard/bst_bld_atf_release.bin
 * @endcode
 *  - <B>eMMC:</B>
 * @code
 * board# upgrade_partition -p -b 1 -B /dev/mmcblk0p7  /sdcard/bst_bld_atf_release.bin
 * board# modprobe bootstat
 * board# echo 0 > /proc/ambarella/bootstat
 * board# reboot
 * board# modprobe bootstat
 * board# cat /proc/ambarella/bootstat
 * @endcode
 * Check if the system boots successfully from "Normal Mode + PRI+LNX".
 * -# Upgrade the BST partition with a new RoT key.  Revoke key1 (new RoT key).
 * @code
 * board# modprobe optee
 * board# tee-supplicant&
 * @endcode
 *  - <B>NAND:</B>
 * @code
 * board# flash_eraseall /dev/mtd0
 * board# upgrade_partition -p     /dev/mtd0  /sdcard/bst_release.bin.signed
 * @endcode
 *  - <B>eMMC:</B>
 * @code
 * board# echo 0 > /sys/block/mmcblk0boot/force_ro
 * board# upgrade_partition -p -b 1 /dev/mmcblk0boot0  /sdcard/bst_release.bin.signed
 * board# test_program_otp --revokekey 0
 * board# modprobe bootstat
 * board# echo 0 > /proc/ambarella/bootstat
 * board# reboot
 * board# modprobe bootstat
 * board# cat /proc/ambarella/bootstat
 * @endcode
 * Check if the system fails at the BST stage, and then check if it can recover.
 * a)  Boot will fail at the BST stage several times; there is no print at the serial port.
 * b)  The system will boot from "Recover mode + PRI+LNX".
 * -# Upgrade the ATF partition to the new RoT key.
 *  - <B>NAND:</B>
 * @code
 * board# flash_eraseall /dev/mtd3
 * board# upgrade_partition -p -H /dev/mtd3  /sdcard/atf.bin.signed
 * @endcode
 *  - <B>eMMC:</B>
 * @code
 * board# upgrade_partition -p -b 1 -H /dev/mmcblk0p4  /sdcard/atf.bin.signed
 * board# modprobe bootstat
 * board# echo 0 > /proc/ambarella/bootstat
 * board# reboot
 * board# modprobe bootstat
 * board# cat /proc/ambarella/bootstat
 * @endcode
 * Check if the system fails at the BL2 stage, and then check if it can recover.
 * a)  Boot fails at the BL2 stage several times; there is no "BL2: Booting BL31".
 * b)  Then, the system boots from "Recovery Mode + PRI+LNX".
 * -# Update the BLD partition with the new RoT key.
 *
 *  - <B>NAND:</B>
 * @code
 * board# flash_eraseall /dev/mtd1
 * board# upgrade_partition -p -G /dev/mtd1  /sdcard/fip.bin
 * @endcode
 *  - <B>eMMC:</B>
 * @code
 * board# upgrade_partition -p -b 1 -G /dev/mmcblk0p2  /sdcard/fip.bin
 * board# modprobe bootstat
 * board# echo 0 > /proc/ambarella/bootstat
 * board# reboot
 * board# modprobe bootstat
 * board# cat /proc/ambarella/bootstat
 * @endcode
 * Check if the system boots successfully from "Normal Mode + PRI+LNX".
 *
 * - <B>System Upgrade with Kernel Key Revocation</B>
 * -# Update the BAK, PBA, and ROM partitions with the new kernel key.
 *
 *  - <B>NAND:</B>
 * @code
 * board# flash_eraseall /dev/mtd6
 * board# upgrade_partition -p -B /dev/mtd6  /sdcard/bst_bld_atf_release.bin
 * board# flash_eraseall /dev/mtd4
 * board# upgrade_partition -p -Q /dev/mtd4  /sdcard/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED
 * board# flash_eraseall /dev/mtd7
 * board# upgrade_partition -p -R /dev/mtd7  /sdcard/ipcam-image-cv5x-20230526073637.rootfs.ubi
 * board# upgrade_partition -S 2
 * @endcode
 *  - <B>eMMC:</B>
 * @code
 * board# upgrade_partition -p -b 1 -B /dev/mmcblk0p7  /sdcard/bst_bld_atf_release.bin
 * board# upgrade_partition -p -b 1 -Q /dev/mmcblk0p5  /sdcard/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED
 * board# upgrade_partition -p -b 1 -R /dev/mmcblk0p8  /sdcard/ipcam-image-cv5x-20230526073637.rootfs.ext4
 * board# upgrade_partition -b 1 -S 2
 * @endcode
 * -# Update the BLD partition with a new kernel key.
 *
 *  - <B>NAND:</B>
 * @code
 * board# flash_eraseall /dev/mtd1
 * board# upgrade_partition -p -G /dev/mtd1  /sdcard/fip.bin
 * @endcode
 *  - <B>eMMC:</B>
 * @code
 * board# upgrade_partition -p -b 1 -G /dev/mmcblk0p2  /sdcard/fip.bin
 * board# modprobe bootstat
 * board# echo 0 > /proc/ambarella/bootstat
 * board# reboot
 * board# modprobe bootstat
 * board# cat /proc/ambarella/bootstat
 * @endcode
 * Check if the system fails at the BLD stage, then check if it can recover.
 * a)  Boot fails at the BLD stage several times; "Authenticate "PRI": failed".
 * b)  Then, the system will boot from "Normal mode + PBA+ROM".
 * -# Update the PRI partition with a new kernel key.
 *
 *  - <B>NAND:</B>
 * @code
 * board# flash_eraseall /dev/mtd5
 * board# upgrade_partition -p -K /dev/mtd5  /sdcard/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED
 * board# upgrade_partition -S 0
 * @endcode
 *  - <B>eMMC:</B>
 * @code
 * board# upgrade_partition -p -b 1 -K /dev/mmcblk0p6  /sdcard/Image--5.15.112-r0-cv5x-20230526072630.bin.SIGNED
 * board# upgrade_partition -b 1 -S 0
 * board# modprobe bootstat
 * board# echo 0 > /proc/ambarella/bootstat
 * board# reboot
 * board# modprobe bootstat
 * board# cat /proc/ambarella/bootstat
 * @endcode
 * Check if the system boots successfully from "Normal Mode + PRI+LNX".
 * -# Update the LNX partition.
 *
 *  - <B>NAND:</B>
 * @code
 * board# upgrade_partition -S 2
 * board# reboot
 * board# flash_eraseall /dev/mtd8
 * board# upgrade_partition -p -W /dev/mtd8  /sdcard/ipcam-image-cv5x-20230526073637.rootfs.ubi
 * board# upgrade_partition -S 0
 * @endcode
 *  - <B>eMMC:</B>
 * @code
 * board# upgrade_partition -b 1 -S 2
 * board# reboot
 * board# upgrade_partition -p -b 1 -W /dev/mmcblk0p9  /sdcard/ipcam-image-cv5x-20230526073637.rootfs.ext4
 * board# upgrade_partition -b 1 -S 0
 * board# modprobe bootstat
 * board# echo 0 > /proc/ambarella/bootstat
 * board# reboot
 * board# modprobe bootstat
 * board# cat /proc/ambarella/bootstat
 * @endcode
 * Check if the system boots successfully from "Normal Mode + PRI+LNX".
 *
 * @section dm_verity 3. Linux Dm-verity
 * The device mapper’s “verity” target provides the transparent integrity checking of block devices using a cryptographic digest provided by the kernel crypto application programming interface
 * (API).  This target is read-only.
 * Dm-verity cannot function on memory technology devices (MTDs).
 *
 * @subsection set_up_dm_verity 3.1 Set Up dm-verity on the Ambarella Platform
 * The following lists the steps to set up dm-verity:
 * -# Configure the Linux kernel:
 * @code
 * build$ make linux_menuconfig
 *          ->Device Drivers
 *           >Multiple devices driver support (RAID and LVM)
 *            >Device mapper support
 *               DM "dm-mod.create=" parameter support
 *               >Verity target support
 *                >Verity data device root hash signature verification support
 * @endcode
 * -# Configure the Ambarella platform:
 * Users can enable dm-crypt and test it from the user space.
 * Dm-crypt requires an extra partition to store hash maps; the swap (SWP) partition is used as an example:
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *        > prebuild  --->
 *         > oss  --->
 *          > prebuild-cryptsetup (prebuild/oss/armv8-a/cryptsetup)  --
 *           > Add cryptsetup utils into root_fs
 *         > prebuild-device-mapper (prebuild/oss/armv8-a/device-mapper)  --
 *          > Add device-mapper utils into root_fs
 *        > rootfs  --->
 *         > rootfs (rootfs/system)  --->
 *          > Linux Root File System (EXT4)  --->
 *        > boot  --->
 *         > amboot (boot/ambamk)  --->
 *         > Ambarella Bootloader Configuration
 *          > AMBoot Options
 *           > Firmware Options
 *            > Swap Partition
 *            ($(AMB_TOPDIR)/amboot/vif/swp.bin) SWP image
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *        > meta-oe  --->
 *         > recipes-crypto  --->
 *          > cryptsetup (meta-oe/recipes-crypto/cryptsetup)
 *          > recipes-support  --->
 *           > libdevmapper (meta-oe/recipes-support/lvm2)
 *        > meta-ambabsp  --->
 *         > recipes-bsp  --->
 *          > amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *           > Ambarella Bootloader Configuration
 *            > AMBoot Options
 *           > Firmware Options
 *            > Swap Partition
 *             ($(AMB_TOPDIR)/amboot/vif/swp.bin) SWP image
 * @endcode
 *
 * Use the command below to generate a blank `swp.bin`.
 * @code
 * build$ dd if=/dev/zero of=swp.bin bs=1024 count=20480
 * @endcode
 * Define the SWP partition size in `ambarella/boards/<board_name>/bsp/partition/emmc.h`.
 * @code
 * #define AMBOOT_SWP_SIZE		(20 * 1024 * 1024)
 * @endcode
 *
 * @subsection use_dm_verity 3.2 Use Dm-verity
 * Follow the steps below to use dm-verity on the board:
 * -# Retrieve the file system block size on the PC.
 * @code
 * build$ tune2fs –l ambarella/out/cv5_timn/rootfs/ext4
 * @endcode
 * -# Set up dm-verity on the board.
 * Partitions: mmcblk0: p1(bst) p2(bld) p3(ptb) p4(atf) p5(pba) p6(pri) p7(lnx) p8(swp)
 * @code
 * board# blockdev –getsz /dev/mmcblk0p7
 * 1024000
 * board# veritysetup format /dev/mmcblk0p7 /dev/mmcblk0p8 –data-block-size=1024
 * Data blocks:	512000
 * Data block size:	1024
 * Hash block size:	4096
 * Hash algorithm:	sha256
 * Salt:			4e884d15950b027c65fd0ab8e78131ccf0016c765507c53a299e5e699da74b23
 * Root hash: 		87e678a6e7c017ffaac5f9d5eb11484539668b1b555061918e26922d6fc0d144
 * @endcode
 * -# Enter into AMBoot.
 * @code
 * fdt cmdline console=ttyS0 noinitrd rw rootfstype=ext4 init=/linuxrc rootwait dm-mod.create="dm-verity,,0,ro, 0 1024000 verity 1 /dev/mmcblk0p7 /dev/mmcblk0p8 1024 4096 512000 1 sha256 87e678a6e7c017ffaac5f9d5eb11484539668b1b555061918e26922d6fc0d144 4e884d15950b027c65fd0ab8e78131ccf0016c765507c53a299e5e699da74b23" root=/dev/dm-0
 * @endcode
 *
 * @note
 * For setups using the device mapper on top of the asynchronously probed block devices (MMC, USB, and more), it may be necessary to tell dm-init to explicitly wait for them to become available
 * before setting up the device mapper tables.  This can be performed with the `dm-mod.waitfor=` module parameter, which uses a list of devices to wait for:
 * @code
 * dm-mod.waitfor=<device1>[,..,<deviceN>]
 * @endcode
 * Then, the commandline written in AMBoot changes to the following:
 * @code
 * fdt cmdline console=ttyS0 noinitrd rw rootfstype=ext4 init=/linuxrc rootwait dm-mod.waitfor=/dev/mmcblk0boot0 dm-mod.create="dm-verity,,0,ro, 0 1024000 verity 1 /dev/mmcblk0p7 /dev/mmcblk0p8 1024 4096 512000 1 sha256 87e678a6e7c017ffaac5f9d5eb11484539668b1b555061918e26922d6fc0d144 4e884d15950b027c65fd0ab8e78131ccf0016c765507c53a299e5e699da74b23" root=/dev/dm-0
 * @endcode
 *
 * @subsection dm_verity_with_sign_dtb 3.3 Enable Dm-verity with Signed DTB
 * If users are required to use signed device tree blob (DTB) and dm-verity together, bootargs cannot be changed.
 * Follow the below steps to enable both:
 * -# Compile and generate the firmware with both the signed DTB and dm-verity; save the `rootfs.ext4`.
 * -# Burn the firmware to the board and run `blockdev`.
 * @code
 * board# blockdev --getsz /dev/mmcblk0p6
 * 1048576
 * @endcode
 * -# Create a hashtree using a rootfs partition on the evaluation kit (EVK) and save it to the `hash_evk.img`, save the root hash and salt values to `evk_verity.txt`.
 * @code
 * board# veritysetup format /dev/mmcblk0p6 hash_evk.img --data-block-size=1024
 *        VERITY header information for hash_evk.img
 *        UUID:                   6b56a58b-2d71-460d-98e1-4d2fa4cbcd43
 *        Hash type:              1
 *        Data blocks:            524288
 *        Data block size:        1024
 *        Hash block size:        4096
 *        Hash algorithm:         sha256
 *        Salt:                   83870773ca1164fe5a8e79a990e6281d22c74f491f2df0bb735827b2f1165bb2
 *       Root hash:              8991988d265251a0d016450f3580a8f2f1a26e685d65214aff21c61df9577c20
 * @endcode
 * -# Change the LNX image to `rootfs.ext4` saved in ste p1, set the SWP image to `hash_evk.img`, and add dm-verity related commands to the command line.
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 * 		 > boot  --->
 * 			  > amboot (boot/ambamk)  --->
 * 			   > Ambarella Bootloader Configuration  --->
 * 			    > AMBoot Options
 * 			     > Commoon Boot Options
 * 			      > (console=ttyS0 noinitrd rw rootfstype=ext4 init=/linuxrc rootwait dm-mod.waitfor=/dev/mmcblk0boot0 dm-mod.create="dm-verity,,0,ro, 0 1048576 verity 1 /dev/mmcblk0p6 /dev/mmcblk0p7 1024 4096 524288 1 sha256 8991988d265251a0d016450f3580a8f2f1a26e685d65214aff21c61df9577c20  83870773ca1164fe5a8e79a990e6281d22c74f491f2df0bb735827b2f1165bb2" root=/dev/dm-0) Booting cmdline
 * 			    > Firmware Options
 * 			     > Linux Partition
 * 			      (rootfs.ext4) Linux FS image
 * 			     > Swap Partition
 * 			      (hash_evk.img) SWP image
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 * 		 > meta-ambabsp  --->
 * 		  > recipes-bsp  --->
 * 		   > amboot (meta-ambabsp/recipes-bsp/boot)  --->
 * 		 > Ambarella Bootloader Configuration
 * 		  > AMBoot Options
 * 		   > Commoon Boot Options
 * 		    > (console=ttyS0 noinitrd rw rootfstype=ext4 init=/linuxrc rootwait dm-mod.waitfor=/dev/mmcblk0boot0 dm-mod.create="dm-verity,,0,ro, 0 1048576 verity 1 /dev/mmcblk0p6 /dev/mmcblk0p7 1024 4096 524288 1 sha256 8991988d265251a0d016450f3580a8f2f1a26e685d65214aff21c61df9577c20  83870773ca1164fe5a8e79a990e6281d22c74f491f2df0bb735827b2f1165bb2" root=/dev/dm-0) Booting cmdline
 * 		  > Firmware Options
 * 		   > Linux Partition
 * 		    (rootfs.ext4) Linux FS image
 * 		     > Swap Partition
 * 		      (hash_evk.img) SWP image
 * @endcode
 *
 * -# Compile and generate the new firmware with the `rootfs.ext4` in step 1, the hash tree stored in the SWP partition, and the signed DTB with bootargs that enable dm-verity.
 *
 * @subsection dm_verity_on_nand 3.4 Dm-verity on NAND
 * The dm-verity feature must function with a read-only file system that runs on a block device; SquashFS is a candidate.
 *
 * @note
 * Dm-verity cannot support unsorted block image file system (UBIFS), as UBIFS does not run on block devices.
 *
 * @subsubsection dm_verity_for_squashFS_with_initramfs 3.4.1 Dm-verity for SquashFS with Initramfs
 * Using <B>initramfs</B> is straight-forward and flexible, enabling users to more-easily adjust or calculate verification arguments from Initramfs.
 *
 * <B>Usage: </B>
 * - `make menuconfig_public_linux` and ensure that the configurations below are enabled:
 * @code
 * CONFIG_MTD_UBI_BLOCK=y
 * CONFIG_DM_VERITY=y
 * @endcode
 * - `make menuconfig` and ensure that the configurations below are enabled:
 * @code
 * LNX=$(AMB_BOARD_OUT)/rootfs/squashfs
 * LNX_VIF=$(AMBOOT_TOPDIR)/vif/squashfs.info
 * CONFIG_AMBARELLA_ROOTFS_SQUASHFS=y
 * CONFIG_SQUASHFS_DM_VERITY=y
 * CONFIG_BUILD_INITRAMFS=y
 * CONFIG_INITRAMFS_DYNAMIC_BUSYBOX=y
 * CONFIG_INITRAMFS_DM_TOOLS=y
 * @endcode
 * - Add the options below into the kernel command line (for example, bootargs in device trees (DTS)):
 * @code
 * console=ttyS0 ubi.mtd=lnx ubi.block=0,0 ubi.block=0,1 root=/dev/mapper/dm-root ro rootfstype=squashfs init=/linuxrc
 * @endcode
 *
 * @subsubsection dm_verity_for_squashfs_without_initramfs 3.4.2 Dm-verity for SquashFS without Initramfs
 * Using <B>initramfs</B> may add undesirable boot time and storage requirements to the system.
 * If the system is operating with VERY strict boot timing or storage requirements, skipping initramfs may be beneficial.
 *
 * <B>Usage: </B>
 * - `make menuconfig_public_linux` and ensure that the configurations below are enabled:
 * @code
 * CONFIG_MTD_UBI_BLOCK=y
 * CONFIG_DM_VERITY=y
 * CONFIG_DM_INIT=y
 * - `make menuconfig` and ensure that the configurations below are enabled:
 * @code
 * LNX=$(AMB_BOARD_OUT)/rootfs/squashfs
 * LNX_VIF=$(AMBOOT_TOPDIR)/vif/squashfs.info
 * CONFIG_AMBARELLA_ROOTFS_SQUASHFS=y
 * CONFIG_SQUASHFS_DM_VERITY=y
 * and also please disable CONFIG_BUILD_INITRAMFS
 * @endcode
 * - Use `make` to build the firmware.  Then, users can find information related to <B>dm-verity</B> in `$(AMB_BOARD_OUT)/rootfs/dm-verity.info`
 * - Add the options below into the kernel command line (for example, bootargs in DTS):
 * @code
 * console=ttyS0 ubi.mtd=lnx ubi.block=0,0 ubi.block=0,1 root=/dev/dm-0 rootfstype=squashfs init=/linuxrc dm-mod.create=\"dm-root,,,ro,0 117256 verity 1 /dev/ubiblock0_0 /dev/ubiblock0_1 4096 4096 14657 1 sha256 3196082c8db1529244fa96ff7372ebbf2935fd117a925bc4b802a44265fc2864 25d2ec914df6dbe3fac237a3c08f74bd3fa35bf6fc6346359c0cf35af5162f88\"
 * @endcode
 * Here, "dm-mod.create" is used to pass DM table information into the kernel.
 * Its format is as follows:
 * @code
 * dm-mod.create="<name>,<uuid>,<minor>,<flags>,[dm_table_params {dm_verity_params}]"
 * Where dm_table_params="<start_sector> <num_sectors> <target_type> <dm_verity_params>"
 * And dm_verity_params="<version> <dev> <hash_dev> <data_block_size> <hash_block_size> <num_data_blocks> \
 * <hash_start_block> <algorithm> <digest> <salt> [<#opt_params> <opt_params>]"
 * @endcode
 *
 * @note
 * - Here, Ambarella provides an example string for "dm-mod.create".  User-created strings must be different from this example.  All required values in `dm-mod.create` can be found in `$(AMB_BOARD_OUT)/rootfs/dm-verity.info`.
 * - `<uuid>` and `<minor>` are not required, so they can be left empty.
 * - `<num_sectors>` is calculated via "Data blocks" * "Data block size" / `Sector_size`.  The most common value for `Sector_size` is 512.
 * - For details, refer to `LINUX/Documentation/admin-guide/device-mapper/dm-init.rst`.
 *
 * - Build the firmware again via `make amboot`.
 *
 * @note
 * Do not use `make` to rebuild the firmware in this step; otherwise, the HASH value for SquashFS will be changed.
 *
 *//*!
 * @file system_reinforcement.h
 * @brief
 * @version 1.0
 * @date 2023-12-11
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
 * @page system_reinforcement System Reinforcement
 * @section SEBLD 1. Secure Enhanced Bootloader
 * The secure enhanced bootloader (SEBLD) is a bootloader with public key authentication; only users who pass the authentication can execute commands inside the BLD console.
 * The BLD generates a random challenge to the user with an embedded public key, and users must provide the correct response (the digital signature of the random challenge).
 * Otherwise, the commands in the BLD are not executed.  Only the private key owner can generate the correct response.
 *
 * @subsection perpare_sebld_key 1.1 Prepare the Key Pair
 * The SEBLD’s public key is embedded inside the BLD firmware.
 * For RSA2048 + SHA256, the public key is in C source file format, located in the folder `ambarella/security/boot_security/locker_pubkey.c`.
 * For ED25519 + SHA512, the public key is embedded with `.bin` format, located in the folder `ambarella/security/tz_sb_keys/local_keys/sebld_keys/ed25519/ pub_sebld.bin`.
 * Before this feature is used, users should already have their own key pair.  This can be performed by generating a new key pair, or using an existing key pair.  The private key
 * should be kept confidential.
 *
 * @subsubsection 1.1.1 Generate a New Key Pair
 * Use the command below to replace the default key pairs that accompany the software development kit (SDK).
 * @code
 * build$ cd ambarella/security/security_tools/scripts
 * build$ ./gen_sebld_key.sh ed25519
 * @endcode
 *
 * @subsubsection use_an_existing_key_pair 1.1.2 Use an Existing Key Pair
 * Replace the existing private key in `ambarella/security/tz_sb_keys/local_keys/sebld_keys`.
 * Use the command below to derive the corresponding public key:
 * @code
 * build$ cd ambarella/security/security_tools/scripts
 * build$ ./derive_sebld_pub_key.sh ed25519
 * @endcode
 *
 * @note
 * - The private key should be kept confidential.
 * - Ambarella recommends removing both `pri_sebld.bin` from the source code after the public key is derived.
 *
 * @subsection perpare_cfg_partition 1.2 Prepare the Configuration Partition
 * Ambarella recommends storing the lock / unlock state in the configuration (CFG) partition.  However, because the CFG partition is not enabled by default, users must first
 * enable it.
 * To enable the CFG partition, follow the steps below (Yocto build is used as an example).
 * If using the legacy firmware layout, the CFG partition must be selected in menuconfig:
 * @code
 * build$ make menuconfig
 *        > meta-ambabsp  --->
 *         > recipes-bsp  --->
 *          > amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *           > Ambarella Firmware Configuration --->
 *            Firmware Options --->
 *             Configuration Partition --->
 *             ($(AMB_TOPDIR)/amboot/vif/cfg.bin) CFG
 *             ($(AMB_TOPDIR)/amboot/vif/cfg.info) CFG Version File
 * @endcode
 * If using the flexible firmware layout, add the CFG partition in the profile file:
 * @code
 * ifeq ($(SEBLD_STORE_IN_CFG), y)
 * IMAGE_7_NAME   := cfg
 * IMAGE_7_FILE   := $(ENV_TOP_DIR)/security/boot_security/cfg.bin
 * IMAGE_7_ADDR   := -1
 * IMAGE_7_FLAG   := force
 * endif
 * @endcode
 * Use the command below to generate a blank `cfg.bin`.
 * @code
 * build$ dd if=/dev/zero of=cfg.bin bs=1024 count=1
 * @endcode
 * Or, use the pre-generated blank `cfg.bin` file in `ambarella/security/boot_security/cfg.bin`.
 * Modify `ambarella/boards/cv5_timn/bsp.h`, and then set `AMBOOT_CFG_SIZE:`
 * @code
 * #define AMBOOT_CFG_SIZE                (AMBOOT_MIN_PART_SIZE * 4)
 * @endcode
 *
 * @note
 * - If there is no CFG partition in a product, the backup plan is to store the lock state in the PTB partition.
 * - Check the MACROs in `ambarella/security/boot_security/locker.c` (for SDK 1.0, use the keys in `ambarella/packages/security/boot_security/locker.c`).
 * - “STORE_LOCK_STATUS” indicates the locker state.
 * - “STORE_IN_CFG” indicates that the locker state should be stored in the CFG partition rather than in the PTB partition.
 *
 * @subsection prepare_android_fastboot 1.3 Prepare Android Fastboot
 * @subsubsection get_android_fastboot_tools 1.3.1 Get Android Fastboot Tools
 * Android Fastboot tools can be downloaded from @ref https://www.teamandroid.com/2017/05/06/download-adb-fastboot-android-sdk-platform-tools/.
 *
 * @subsubsection enter_android_fastboot 1.3.2 Enter Android Fastboot on the EVK
 * There are two approaches to enter Android Fastboot on an evaluation kit (EVK) board:
 * - Execute “Fastboot” on the AMBoot console
 * - Enter Android Fastboot directly via general purpose input / output (GPIO)
 *
 * If the product does not have a serial port, Ambarella recommends that users choose the latter approach.
 * For the latter approach, the board support package (BSP) code must be modified in order to enter into Android Fastboot directly via `GPIO_DEBUG`.
 * Add the highlighted part below in `ambarella/boards/cv5_timn/bsp/bsp.c`:
 * @code
 * int amboot_bsp_entry(flpart_table_t *pptb)
 * {
 * 	int retval = 0;
 * 	flpart_table_t ptb;
 *
 * 	{//add to setup debug gpio for fastboot
 * 	#define AMBARELLA_DEBUG_GPIO    107
 * 		gpio_config_sw_in(AMBARELLA_DEBUG_GPIO);
 * 		if (!gpio_get(AMBARELLA_DEBUG_GPIO))
 * 			return 4;
 * 	}
 *
 * 	/* Read the partition table */
 * 	retval = flprog_get_part_table(&ptb);
 * 	if (retval < 0) {
 * 		return retval;
 * 	}
 *
 * 	/* BIOS boot */
 * 	if (ptb.dev.rsv[0] > 0) {
 * 		printf("Find BIOS boot flag\n");
 * 		retval = ptb.dev.rsv[0];
 * 	}
 *
 * 	return retval;
 * }
 * @endcode
 *
 * @subsection sebld_user_guide 1.4 User Guide
 * There are two approaches to execute commands in the bootloader: the first uses the AMBoot console; the second uses Android Fastboot.  The following sections demonstrate these
 * two approaches (using the ed25519 key for example).
 *
 * @subsubsection sebld_via_amboot_console 1.4.1 Via AMBoot Console
 * - Compile options:
 * To enable SEBLD, select the following items in “make menuconfig”:
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *        security  --->
 *         [*] boot-security (security/boot_security)  --->
 *          [*]   Security-Enhanced BLD Support [locker]  --->
 * @endcode
 * 
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *        meta-ambasecurity  --->
 *         recipes-boot-security  --->
 *          [*] boot-security (meta-ambasecurity/recipes-boot-security/boot-security)  --->
 *           [*]   Security-Enhanced BLD Support [locker]  --->
 * @endcode
 *
 * -# Enter the AMBoot console (press <B>Enter</B> and reboot).
 * -# Get the challenge.
 * @code
 * amboot> sebld challenge
 * @endcode
 * The 40-byte challenge is shown below.
 * @code
 * amboot > sebld challenge
 * fa3177810ee1078bb34f8118539e9046n4q6a6x5
 * @endcode
 * -# Use the private key to sign the challenge (ED25519 for example; RSA2048 is similar).
 * @code
 * build$ cd ambarella/packages/security/build/sebld_tool
 * build$ ./sebld_disable fa3177810ee1078bb34f8118539e9046n4q6a6x5 ed25519 ../../keys/local_keys/sebld_keys/ed25519/pri_sebld.bin
 * dbf7f77265bb9f2e9e92f2539af6900e2ffa96de854f82df28d754c71601e20964814d65930a5e6cb796b925d07920e4c87dcbd81d90f744e000d7e1ef860c0b
 * @endcode
 *
 * -# Use the signature to unlock the BLD in the AMBoot console:
 * @code
 * amboot> sebld challenge
 * fa3177810ee1078bb34f8118539e9046n4q6a6x5
 * amboot> sebld disable dbf7f77265bb9f2e9e92f2539af6900e2ffa96de854f82df28d754c71601e20964814d65930a5e6cb796b925d07920e4c87dcbd81d90f744e000d7e1ef860c0b
 * store signature:
 * dbf7f77265bb9f2e9e92f2539af6900e2ffa96de854f82df28d754c71601e20964814d65930a5e6cb796b925d07920e4c87dcbd81d90f744e000d7e1ef860c0b 
 * @endcode
 *
 * When the bootloader is unlocked, inputting `help` lists the available commands.
 * 
 * -# Lock BLD:
 * @code
 * amboot> selbd enable
 * @endcode
 * The message below signifies that no command is available after it is locked.
 * @code
 * amboot>help
 * Security-Enhanced BLD is enable
 * @endcode
 *
 * @subsubsection sebld_via_android_fastboot 1.4.2 Via Android Fastboot
 *
 * - Compile Options
 * To enable SEBLD and Android Fastboot, select the following items in “make menuconfig”:
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *        boot  --->
 *         [*] amboot (boot/ambamk)  --->
 *            Ambarella Bootloader Configuration  --->
 *             AMBoot Options  --->
 *              Common Boot Options  --->
 *        security  --->
 *         [*] boot-security (security/boot_security)  --->
 *          [*]   Security-Enhanced BLD Support [locker]  --->
 * @endcode
 * 
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *        meta-ambabsp  --->
 *         recipes-bsp  --->
 *          [*] amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *            Ambarella Bootloader Configuration  --->
 *             AMBoot Options  --->
 *              Common Boot Options  --->
 *               [* ] Android Fastboot Support
 *        meta-ambasecurity  --->
 *         recipes-boot-security  --->
 *          [*] boot-security (meta-ambasecurity/recipes-boot-security/boot-security)  --->
 *           [*]   Security-Enhanced BLD Support [locker]  --->
 * @endcode
 *
 * Follow the steps below to execute the lock and unlock functions.
 * -# Enter Android Fastboot by pressing the `GPIO_DEBUG` button and rebooting.
 * An example of the board entering Android Fastboot is provided below.
 * @anchor Android_Fastboot
 * @image html android_fastboot_console.png "Figure 1-1. Android Fastboot."
 *
 * -# Get the challenge.
 * @code
 * host$ fastboot.exe getvar challenge
 * challenge: fa3177810ee1078bb34f8118539e9046l7r5a4v6 
 * Finished. Total time: 0.009s
 * @endcode
 *
 * -# Use the private key to sign the challenge.
 * @code
 * build$ cd ambarella/packages/security/build/sebld_tool
 * build$ ./sebld_disable fa3177810ee1078bb34f8118539e9046l7r5a4v6 ed25519 ../../keys/local_keys/sebld_keys/ed25519/pri_sebld.bin
 * @endcode
 *
 * The signature file is `sebld.sign`.  Copy `sebld.sign` to the Android Fastboot tool folder.
 *
 * -# Upload the signature to the board.
 * @code
 * host$ fastboot.exe signature sebld.sign
 * @endcode
 *
 * -# Unlock the BLD.
 * @code
 * host$ fastboot.exe oem unlock
 * @endcode
 * The following message will be displayed if the unlock was successful.
 * @anchor Unlock_Android_Fastboot_Successful
 * @image html unlock_android_fastboot.png "Figure 1-2. Unlock Android Fastboot Successful."
 * Then, the other Android Fastboot commands are available for use.
 * For example, the “boot” command can download firmware, such as AmbaUSB:
 * @code
 * host$ fastboot.exe boot bld_release.bin
 * @endcode
 * -# Lock the BLD.
 * @code
 * host$ fastboot.exe boot bld_release.bin
 * @endcode
 *
 * @section selinux 2. Secure Enhanced Linux (SELinux)
 * @subsection selinux_overview 2.1 SELinux Overview
 * @subsubsection selinux_introduction 2.1.1 Introduction
 * SELinux is the primary mandatory access control (MAC) mechanism built into a number of GNU / Linux distributions.  SELinux originally began as the Flux Advanced Security Kernel
 * (FLASK), developed by the Utah University Flux team and the U.S. Department of Defense.  The development was later enhanced by the National Security Agency (NSA) and released
 * as an open source software (OSS).
 *
 * @subsubsection core_selinux_components 2.1.2 Core SELinux Components
 * The following figure shows a high-level diagram of the SELinux core components that manage the enforcement of the policy and is comprised of the following:
 * - An object manager that knows the actions required for a particular resource (such as a file) and can enforce those actions (for example, allows it to write to a file, if permitted by the policy)
 * - A security server that makes decisions regarding the subject’s right to perform the requested action on the object, based on the existing security policy rules
 * - A security policy that describes the rules using the SELinux policy language
 * - An access vector cache (AVC) that improves system performance by caching security server decisions
 * @anchor High_Level_Core_SELinux_Components
 * @image html high_level_core_selinux_components.png "Figure 2-1. High-Level Core SELinux Components."
 *
 * @subsubsection mandatory_access_control 2.1.3 Mandatory Access Control
 * Mandatory access control is a type of access control in which the operating system (OS) is used to constrain a user or process (the subject) from accessing or performing an
 * operation on an object (such as file, disk, memory, and more).
 * Each of the subjects and objects include a set of security attributes that can be interrogated by the OS to check if the requested operation can be performed.
 * For SELinux, the following are true:
 * - Subjects are processes
 * - Objects are system resources, such as files and sockets
 * - Security attributes are the security context
 * - The security server within the Linux kernel authorizes access using the security policy that describes the rules that must be enforced
 *
 * @subsubsection selinux_users 2.1.4 SELinux Users
 * Users in `GNU / Linux` are generally associated with human users (such as Alice and Bob) or operator / system functions (such as admin).  While this can be implemented in
 * SELinux, SELinux usernames are generally groups or classes of users.  For example, all standard system users can be assigned an SELinux username of `user_u`.  Administration
 * staff can be assigned under `staff_u`.
 *
 * @subsubsection rbac 2.1.5 Role-Based Access Control
 * To further control access to type enforcement (TE) domains, SELinux uses role-based access control (RBAC).  This feature enables SELinux users to be associated with one or more
 * roles, where each role is then associated with one or more domain types, as shown in the figure below.
 * @anchor Role_Based_Access_Control
 * @image html role_based_access_control.png "Figure 2-2. Role-Based Access Control."
 *
 * @subsubsection security_context 2.1.6 Security Context
 * SELinux requires security context to be associated with each process (or subject) and object that is used by the security server to decide if access is permitted, as defined by
 * the policy.
 * The security context is additionally known as a ‘security label’.
 * Within SELinux, the security context is represented as variable-length strings that define the SELinux user, their role, a type identifier, and an optional MCS / MLS security
 * range level shown below.
 * `user:role:type[:range]`
 * The following table describes the user, role, type, and range within the security context.
 * <table>
 * <caption id="security_context">Table 2-1. Security Context.</caption>
 * <tr><th align="left">User<th align="left">Role<th align="left">Type<th align="left">Range
 * <tr><td>The SELinux user identity can be associated with one or more roles that the SELinux user is allowed to use
 *     <td>The SELinux role can be associated with one or more types that the SELinux user is allowed to access
 *     <td>When a type is associated with a process, it defines what processes (or domains) the SELinux user (the subject) can access.  When a type is associated with an object, it defines what access permissions are available to the SELinux object
 *     <td>This field is known as a level; it is only present if the policy supports MCS or MLS.  The entry can consist of the following:<br>
 *      - A single security level that contains a sensitivity level and zero or more categories (for example, s0, s1:c0)
 *      - A range that consists of two security levels separated by a hyphen (for example, ss0-s15:c0.c1023)
 * </table>
 *
 * @subsubsection selinux_subjects 2.1.7 Subjects
 * A subject is an active entity (generally in the form of a person, process, or device) that enables information to flow among objects or that changes the system state.
 * Within SELinux, a subject is an active process with an associated security context.  However, a process can also be referred to as an object, depending on the context.  For example:
 * - A running process (such as an active entity) is a subject because it causes information to flow among objects or can change the system state
 * - The process can also be referred to as an object because each process has an associated object class called “process.”  This process “object” defines what permissions the policy is allowed to grant or deny on the active process
 *
 * @subsubsection selinux_objects 2.1.8 Objects
 * Within SELinux, an object is a resource (such as files, sockets, pipes, or network interfaces) that are accessed via processes (also known as subjects).  These objects are
 * classified according to which resource they provide access permissions relevant to their purpose (for example, read, receive, and write), and are assigned a security context.
 * Each object consists of a class identifier that defines its purpose (for example, file or socket), along with a set of permissions (also known as access vectors) that describe
 * what services the object can manage (read, write, send, and so on).  When an object is instantiated, it will be allocated a name (for example, a file could be called `configured`,
 * a `socket`, or `my_connection`) and a security context (for example, `system_u:object_r:selinux_config_t`).
 *
 * @subsubsection selinux_modes 2.1.9 SELinux Modes
 * SELinux includes three major operation modes:
 * - Enforcing: SELinux is enforcing the loaded policy
 * - Permissive: SELinux has loaded the policy, but is not enforcing the policy rules.  This is generally used for testing as the audit log contains the AVC-denied messages
 * - Disabled: The SELinux infrastructure is not enabled; therefore, no policy can be loaded
 * These flags are set in the `/etc/selinx/config` file.
 *
 * @subsubsection auditing_selinux_events 2.1.10 Auditing SELinux Events
 * SELinux includes two main types of audit events: AVC audit events and SELinux-aware application events.
 * AVC audit events are generated by the AVC subsystem as a result of access denials, or where specific events have requested an audit message.
 * SELinux-aware application events are generated by the SELinux kernel services and SELinux-aware applications for events, such as system errors, initialization, policy loading,
 * changing Boolean states, setting of enforcing / permissive mode, and relabeling.
 * 
 * <b>AVC Audit Events</b>
 * The table below describes the general format of AVC audit messages in `/var/log/audit/audit.log` when access has been denied or an audit event has been specifically requested.
 * <table>
 * <caption id="AVC_Audit">Table 2-2. AVC Audit Message Description.</caption>
 * <tr><th align="left">Keyword<th align="left">Description
 * <tr><td>type<td>For SELinux AVC events:<br>`type = AVC` – for kernel events<br>`type = USER_AVC` – for user-space object manager events<br>The AVC event can always be tied to the relevant `SYSCALL` event as they have the same `serial_nmuber` in the `msg = audit (time: serial_number)` field
 * <tr><td>msg<td>Contains the audit keyword with a reference number (for example, `msg = audit(1243332701.74:101)`)
 * <tr><td>avc<td>Will be either denied when access has been <B>denied</B> or <B>granted</B> when an `audit allow` rule has been defined by the policy
 * <tr><td>pid<td rowspan="2">If it is a task, log the process ID (pid) and the name of the executable file (comm)
 * <tr><td>comm
 * <tr><td>capability	<td>If it is a capability event, log the identifier
 * <tr><td>path<td rowspan="4">If it is a file system event, log the relevant information.  Note that the `name` field may not always be present
 * <tr><td>name
 * <tr><td>dev
 * <tr><td>ino
 * <tr><td>laddr<td rowspan="4">If it is a socket event, log the source / destination address and ports for IP4 and IP6 sockets `AF_INET`
 * <tr><td>lport
 * <tr><td>faddr
 * <tr><td>fport
 * <tr><td>path<td>If it is a file socket event, log the path `AF_UNIX`
 * <tr><td>saddr<td rowspan="5">If it is a network event, log the source / destination addresses and ports with the network interface for IP4 or IP6 networks `AF_INET`
 * <tr><td>src
 * <tr><td>daddr
 * <tr><td>dest
 * <tr><td>netif
 * <tr><td>sauid<td rowspan="4">IPSec security association identifiers
 * <tr><td>hostname
 * <tr><td>addr
 * <tr><td>terminal
 * <tr><td>resid<td rowspan="2">X-Windows resource ID and type
 * <tr><td>restype
 * <tr><td>scontext<td>The security context of the source or subject
 * <tr><td>tcontext<td>The security context of the target or object
 * <tr><td>tclass<td>The object class of the target or object
 * </table>
 *
 * The following is an `audit.log` example:
 * @code
 * type=AVC msg=audit(1242575005.122:101): avc: denied { rename } for pid=2508
 * comm="canberra-gtk-pl" name="c73a516004b572d8c845c74c49b2511d:runtime.tmp"
 * dev=dm-0 ino=188999 scontext=test_u:staff_r:oddjob_mkhomedir_t:s0
 * tcontext=test_u:object_r:gnome_home_t:s0 tclass=lnk_file
 * type=AVC msg=audit(1242575005.122:101): avc: denied { unlink } for pid=2508
 * comm="canberra-gtk-pl" name="c73a516004b572d8c845c74c49b2511d:runtime" dev=dm-0
 * ino=188578 scontext=test_u:staff_r:oddjob_mkhomedir_t:s0
 * tcontext=system_u:object_r:gnome_home_t:s0 tclass=lnk_file
 * type=SYSCALL msg=audit(1242575005.122:101): arch=40000003 syscall=38 success=yes
 * exit=0 a0=82d2760 a1=82d2850 a2=da6660 a3=82cb550 items=0 ppid=2179 pid=2508
 * auid=500 uid=500 gid=500 euid=500 suid=500 fsuid=500 egid=500 sgid=500 fsgid=500
 * tty=(none) ses=1 comm="canberra-gtk-pl" exe="/usr/bin/canberra-gtk-play"
 * subj=test_u:staff_r:oddjob_mkhomedir_t:s0 key=(null)
 * @endcode
 *
 * @subsection selinux_amba_user_guide 2.2 SELinux User Guide for Ambarella
 * @subsubsection amba_selinux_support 2.2.1 Ambarella SELinux Support
 * Currently, only EXT4 can completely support SELinux (label with XATTR and change it).
 * UBIFS can label XATTR, but cannot change it.
 * @note
 * Only embedded multi-media card (eMMC) storage can support the EXT4 file system.
 *
 * @subsubsection enable_selinux_on_amba 2.2.2 Enable SELinux on the Ambarella Platform
 * There are two methods for configuring SELinux on the Ambarella platform: using the default configuration by Ambarella or manually setting up the SELinux configuration.
 *
 * <b>Use the Default Configuration</b><br>
 * Ambarella offers a default configuration to set up SELinux.  Follow the steps below to set up the SELinux configuration:
 * @code
 * build$ make sync_build_mkcfg
 * build$ make xxxxx_selinux_config
 * build$ make defconfig_pulbic_linux
 * build$ make –j16
 * @endcode
 *
 * <b>Setting Up SELinux Configuration Manually</b>
 * SELinux can be set up manually.  Follow the steps below to set up SELinux in menuconfig:
 * @code
 * build$ make linux_menuconfig
 *        > General steps
 *         > Auditing support
 *        > Security options
 *         > Enable different security models
 *         > Enable the securityfs filesystem
 *         > Socket and Networking Security Hooks
 *         > NSA SELinux support
 *         > NSA SELinux boot parameter
 *         > NSA SELinux runtime disable
 *         > NSA SELinux Development Support
 *         > NSA SELinux AVC Statistics
 *         > (1)NSA SELinux checkreqprot default value
 *         > First legacy 'major LSM' to be initialized (SELinux)
 *         > (lockdown,yama,loadpin,safesetid,integrity, selinux) Ordered list of enabled LSMs
 * @endcode
 * @note
 * If using SELinux with the UBIFS file system, in "File systems", select "UBIFS XATTR support" in "Miscellaneous file systems".
 *
 * @code
 * build$ make menuconfig
 *        > prebuild
 *         > oss
 *          > -*- prebuild-audit (prebuild/oss/armv8-a/audit)
 *           > [*]   Add audit service into root_fs
 *          > [*] prebuild-policycoreutils (prebuild/oss/armv8-a/policycoreutils)
 *           > [*]   SELINUX policy from Fedora system
 *           > [*]   Add restorecond service into root_fs
 * @endcode
 * @note
 * When using the UBIFS file system, in `rootfs -> rootfs`, select `Initialize file labeling with XATTR`.
 * For SELinux, if the SELinux `file_context` file must be changed, then change the file context address.
 *
 * @subsubsection selinux_command 2.2.3 SELinux Commands
 * <b>Print Security Context</b><br>
 * The command `-Z` is used to print the security context for the file `/process/user`.
 *
 * For example:
 * @code
 * board# ls -Z
 *        system_u:object_r:usr_t:s0       selinux_test.txt
 * board# id -Z
 *        system_u:system_r:local_login_t:s0-s0:c0.c1023
 * board# ps -Z |grep nginx
 *        system_u:system_r:httpd_t:s0          271 root      0:00 nginx: master process /usr/sbin/nginx -c /etc/nginx/nginx.conf
 *        system_u:system_r:httpd_t:s0          272 nginx     0:00 nginx: worker process
 *        system_u:system_r:httpd_t:s0          273 nginx     0:00 nginx: worker process
 *        system_u:system_r:httpd_t:s0          274 nginx     0:00 nginx: worker process
 *        system_u:system_r:httpd_t:s0          275 nginx     0:00 nginx: worker process
 * @endcode
 *
 *  <B>Get the SELinux Status</b><br>
 * `sestatus` is used to obtain the status of the system running SELinux.
 *  - Usage: `sestatus [OPTION]`
 *  - `-v`: verbose check of process and file contexts
 *  - `-b`: display the current state of Booleans
 *  - If there are no options, `sestatus` displays the SELinux status
 *
 * For example:
 * @code
 * board# sestatus
 *        SELinux status:                 enabled
 *        SELinuxfs mount:                /sys/fs/selinux
 *        SELinux root directory:         /etc/selinux
 *        Loaded policy name:             targeted
 *        Current mode:                   permissive
 *        Mode from config file:          permissive
 *        Policy MLS status:              enabled
 *        Policy deny_unknown status:     allowed
 *        Memory protection checking:     requested (insecure)
 *        Max kernel policy version:      31
 *
 * <b>Get and Modify SELinux Mode</b><br>
 * `getenforce` is used to get the mode SELinux is running in.  `setenforce` is used to modify the mode SELinux is running in.
 * Use `Enforcing` or `1` to put SELinux in enforcing mode.  Use `Permissive` or `0` to put SELinux in permissive mode.
 * For example:
 * @code
 * board# getenforce
 *        Permissive
 * board# setenforce 1
 * board# getenforce
 *        Enforcing
 * @endcode
 * @note
 * SELinux mode changes using `setenforce`, which is recovered after a reboot.  If users want to change the SELinux mode permanently or disable SELinux, they must modify `/etc/selinux/config`.
 * For more information, refer to @ref selinux_config_files.
 *
 * <b>Change the Security Context</b><br>
 * `chcon` is used to change the security context.
 * @code
 * Usage: chcon [OPTIONS] CONTEXT FILE...
 *         chcon [OPTIONS] [-u USER] [-r ROLE] [-l RANGE] [-t TYPE] FILE...
 *         chcon [OPTIONS] --reference=RFILE FILE...
 *         -v      Verbose
 *         -c      Report changes made
 *         -h      Affect symlinks instead of their targets
 *         -f      Suppress most error messages
 *         --reference RFILE  Use RFILE's group instead of using a CONTEXT value
 *         -u USER  Set user/role/type/range in the target security context
 *         -r ROLE
 *         -t TYPE
 *         -l RNG
 *         -R      Recurse
 * @endcode
 * For example:
 * @code
 * board# ls -Z
 *        system_u:object_r:admin_home_t:s0 selinux_test.txt
 * board# chcon -t usr_t selinux_test.txt
 * board# ls -Z
 *        system_u:object_r:usr_t:s0       selinux_test.txt
 * @endcode
 * @note
 * Only an eMMC board with an EXT4 file system can change the security context.
   *
 * @subsubsection selinux_config_files 2.2.4 SELinux Configuration Files
 * This configuration file controls the SELinux state; it is located in `/etc/selinux/config`.  It uses the following parameters:
 * @code
 * SELINUX=enforcing|permissive|disabled
 * SELINUXTYPE=policy_name
 * @endcode
 *
 * Editing the value in this file can change the SELinux state, as follows:
 * <table>
 * <caption id="selinux_config_values">Table 2-3. /etc/selinux/config Values.</caption>
 * <tr><th align="left">SELinux<th align="left">SELinux Type
 * <tr><td> This entry can contain one of three values:<br>
 *           <B>Enforcing</B>: SELinux security policy is enforced<br>
 *           <B>Permissive</B>: SELinux logs warnings instead of enforcing the policy<br>
 *           <B>Disabled</B>: No SELinux policy is loaded
 *      <td> The `policy_name` is used as the directory name where the active policy and its configuration files will locate and load the policy contained within this directory structure.<br>
 *           `/etc/selinux/<policy_name>`
 * </table>
 *
 * @subsubsection policy_config_files 2.2.5 Policy Configuration Files
 * Each file discussed in this section is related to the policy name, as follows:
 * `/etc/selinx/<policy_name>` (Ambarella uses `targeted` by default)
 * - `Seusers`<br>
 * The seusers file is used by login programs and maps the GNU / Linux user to the SELinux user.  A typical login sequence would be as follows:
 *  - Using the GNU / Linux `user_id`, look up the `seuser_id` from this file.  If an entry cannot be found, use `__default__entry`.
 *  - To determine the remaining context to be used as the security context, read the `./contexts/users/[user_id]` file.  If this file is not present, check for a default context in the `./contexts/default_contexts` file.  If no default context is found, read the `./contexs/failsafe_context` file to enable a failed safe context to be set.
 * Example of seusers file contents:
 * @code
 * system_u:system_u
 * root:root
 * __default__:user_u
 * @endcode
 *
 * - `Policy / policy.<ver>`<br>
 * This is the binary policy file that is loaded into the kernel to enforce the policy.
 * - `Contexts / customizable_types`<br>
 * The `customizable_types` file contains a list of types that will not be re-labeled by the `setfiles` or `restorecon` commands.  The commands check this file before re-labeling and exclude those in the list unless the `–F` flag is used.
 * Example of file contents:
 * @code
 * container_file_t
 * sandbox_file_t
 * svirt_image_t
 * svirt_home_t
 * svirt_sandbox_file_t
 * virt_content_t
 * httpd_user_htaccess_t
 * httpd_user_script_exec_t
 * httpd_user_rw_content_t
 * httpd_user_ra_content_t
 * httpd_user_content_t
 * git_session_content_t
 * home_bin_t
 * user_tty_device_t
 * @endcode
 *
 * - `Contexts / default_contexts`<br>
 * The `default_context` file is used by SELinux-aware applications that are required to set a security context for user processes (generally the login applications).
 * The following is an example of `default_contexts` contents:
 * @code
 * system_r:crond_t:s0 system_r:system_crond_t:s0
 * system_r:local_login_t:s0 user_r:user_t:s0
 * system_r:remote_login_t:s0 user_r:user_t:s0
 * system_r:sshd_t:s0 user_r:user_t:s0
 * system_r:sulogin_t:s0 sysadm_r:sysadm_t:s0
 * system_r:xdm_t:s0 user_r:user_t:s0
 * @endcode
 *
 * - `Contexts / Files / file_contexts`<br>
 * The `file_contexts` file is used by a number of SELinux-aware commands (`setfiles`, `fixfiles`, `matchpatchcon`, and `restorecon`) to re-label either part or all of the file system.
 * The format of the `file_context` file is as follows.
 * Each line within the file consists of the following:
 * @code
 * pathname_regexp [file_type] opt_security_context
 * @endcode
 * <table>
 * <caption id="file_context_para">Table 2-4. Parameters for file_context</caption>
 * <tr><th align="left">pathname_regexp<th align="left">file_type<th align="left">opt_security_context
 * <tr><td>An entry that defines the path name that may be in the form of a regular expression
 *      <td>One of the following optional file_type entries:<br>-b: Block device<br>-c: Character device<br>-d: Directory<br>-p: Named pipe<br>-l: Symbolic link<br>-s: Socket file
 *      <td>This can be either:<br> The security context<br> A value of <<none>> can be used to indicate that matching files must not be re-labeled
 * </table>
 *
 * The following is an example of `file_contexts` contents:
 * @code
 * /.* system_u:object_r:default_t:s0
 * /[^/]+ -- system_u:object_r:etc_runtime_t:s0
 * /a?quota\.(user|group) -- system_u:object_r:quota_db_t:s0
 * /nsr(/.*)? system_u:object_r:var_t:s0
 * /sys(/.*)? system_u:object_r:sysfs_t:s0
 * ...
 * /etc/ntop.* system_u:object_r:ntop_etc_t:s0
 * HOME_DIR/.+ system_u:object_r:user_home_t:s0
 * /dev/dri/.+ -c system_u:object_r:dri_device_t:s0
 * ...
 * /tmp/gconfd-USER -d system_u:object_r:user_tmp_t:s0
 * ...
 * /tmp/gconfd-USER/.* -- system_u:object_r:gconf_tmp_t:s0
 * ...
 * HOME_ROOT/\.journal <<none>>
 * @endcode
 *
 * @subsubsection customize_policy 2.2.6 Customize Policy
 * Users can customize their own policy to fit their systems by adding a new SELinux module.
 * <b>Create Module CIL Files</b><br>
 * To create a new module, create a `cil` file and write the rules:
 * @code
 * board# vi test_policy.cil
 *       (allow systemd_logind_t init_var_lib_t (lnk_file (read)))
 * @endcode
 * This rule indicates that when the source file is `system_logind_t`, the targeted file is `init_var_lib_t`, the object class is `lnk_file`, and the object permission is `read`.
 *  Thus, the operation is allowed.
 *
 * <b>Install the Module</b><br>
 * Use the semodule `–i` to install the module:
 * @code
 * board# semodule –i test_policy.cil
 * @endcode
 *
 * <b>Update the Module</b><br>
 * -# Obtain `cil` files from the module (if the user already has the cil files, this step can be skipped).
 * @code
 * board# semodule -c --extract test_policy
 * @endcode
 * -# Add the rules to the `cil` file.
 * @code
 * board# echo '(allow systemd_rfkill_t init_var_lib_t (lnk_file (read)))' >> test_policy.cil
 * @endcode
 * -# Install a new module.
 * @code
 * board#semodule –i test_policy.cil
 * @endcode
 *
 * <b>Check the Policy</b><br>
 * Use `selinux_check_access` to determine if the rules have been written into the policy.
 * @code
 * board# selinux_check_access system_u:system_r:systemd_rfkill_t:s0   system_u:object_r:init_var_lib_t:s0 lnk_file read
 * @endcode
 * If the module was not successfully installed, the following error message appears:
 * @code
 * avc:  denied  { read } for  scontext=system_u:system_r:systemd_rfkill_t:s0 tcontext=system_u:object_r:iit_var_lib_t:s0 tclass=lnk_file permissive=1
 * @endcode
 *
 * @section tee_and_trustzone 3. TEE and Arm TrustZone
 * TEE is a specification / standard from GlobalPlatform (GP), a non-profit industry association.  One of TEE’s implementations is Arm TrustZone.
 * For more information about GP, visit the following link: @ref https://globalplatform.org/.
 * TEE specification can be found here: @ref https://globalplatform.org/specs-library/?filter-committee=tee
 * For more information about TEE programming, users can refer to TEE API and TEE client API specifications as follows: <em>GPD_TEE_Internal_Core_API_Specification_v1.3.1_PublicRelease_CC.pdf</em> and <em>TEE_Client_API_Specification-V1.0_c.pdf</em>
 *
 * @subsection arm_trustzone 3.1. Arm® TrustZone®
 * Arm TrustZone technology offers an efficient, system-wide approach to security with hardware-enforced isolation built into the CPU.  TrustZone provides the perfect starting
 * point for establishing a device root of trust (RoT) based on platform security architecture (PSA) guidelines.
 * For more information, visit @ref https://www.arm.com/technologies/trustzone-for-cortex-a.
 * @anchor The_System_Diagram_of_Arm_TrustZone
 * @image html sys_diag_of_arm_trustzone.png "Figure 3.1. System Diagram of Arm TrustZone"
 * On Ambarella platforms, Arm TrustZone can be enabled in the flexible Linux SDK.
 * In the flexible Linux SDK, Linux functions as the rich OS, the open portable trusted execution environment (OP-TEE) as the trusted operating system (TOS), and Arm trusted firmware
 * (ATF) as the trusted firmware / secure monitor.  The hypervisor and multiple-rich OS are not implemented in the SDK.
 * The following diagram illustrates Arm TrustZone in the Ambarella Flexible Linux SDK.
 * @anchor Arm_TrustZone_in_Linux_SDK
 * @image html arm_trustzone_in_linux_sdk.png "Figure 3.2 Arm TrustZone in Linux SDK"
 *
 * @subsection arm_trusted_firmware 3.2. Arm Trusted Firmware
 * ATF is the reference software for Arm TrustZone.  It implements a secure monitor, which manages the switch between the normal world (rich OS) and the secure world (secure OS).
 * ATF also implements authentication during the boot stage (secure boot).  During this process, the Ambarella Linux SDK employs a partial authentication chain for secure boot via
 * the built-in hardware engine: BL2 authenticates BL31, BL32, and BL33.
 *
 * @subsection op_tee 3.3. OP-TEE
 * OP-TEE is an open source project, which implements the GlobalPlatform TEE system architecture specifications and serves as a TOS.  OP-TEE provides the TEE application programming
 * interface (API) and the TEE client API, and implements a TEE-suppliant.  The TEE API, as defined by the GlobalPlatform TEE standard, is for the development of trusted applications
 * (TAs).  The TOS is accessible from the rich OS (Linux) using the GlobalPlatform TEE client API specification.  The TEE client API is used to trigger the secure execution of
 * applications within the TEE.  The TEE-supplicant loads the TA from the rich OS into the secure OS for execution.
 * The following diagram shows the software stack of Arm TrustZone (Linux, OP-TEE, and ATF).
 *
 * @anchor The_Software_Stack_of_a_TrustZone
 * @image html sw_stack_of_trustzone.png "Figure 3.3 Software Stack of TrustZone (Linux, OP-TEE, and ATF)"
 *
 * @note
 * - Refer to @ref https://www.op-tee.org/ to access the OP-TEE home page.<br>
 * - Refer to @ref https://github.com/OP-TEE/ to access the project.<br>
 * - Refer to @ref https://optee.readthedocs.io/ to check OP-TEE documents.
 *
 * @subsection ta_and_ca 3.4. Trusted Application and Client Application
 * The TA functions in the secure world in OP-TEE.  It can be a user TA, which operates in the TEE user space, or a pseudo TA (PTA), which operates in the TEE kernel space.
 * The user TA includes a signature and resides in the normal world storage.  The PTA is embedded in the trusted OS (OP-TEE-OS).  Each TA includes a universally unique identifier
 * (UUID) as its identity.  When a normal TA is requested, it is loaded by a TEE-supplicant in rich the OS and conveyed to the secure world after the digital signature has been
 * verified.
 * The client application (CA) functions in the normal world.
 * The SDK locations for the modules are as follows:
 * - TEE_Client_API:			`SDK/ambarella/boot/tee/optee_client/libteec`
 * - RPC service:			`SDK/ambarella/boot/tee/optee_client/tee-supplicant`
 * - OP-TEE driver:			`SDK/ambarella/kernel/linux-5.15/drivers/tee/optee`
 * - TEE_Internal_API:			`SDK/ambarella/boot/tee/optee_os/lib/libutee/include`
 * OP-TEE’s user TAs are signed by `SDK/ambarella/boot/tee/optee_os/keys/default_ta.pem`.
 * @note
 * Each TA in the secure world should include a UUID to enable the CA application to locate it through the TEE API in the normal world.
 *
 * @subsection source_code_location_in_sdk 3.5 Source Code Location in the SDK Package
 *
 * The following lists locations of the source files.
 * - ATF:				`SDK/ambarella/boot/tee/arm-trusted-firmware`
 * - Cryptography library:		`SDK/ambarella/boot/tee/mbedtls`
 * - OP-TEE_OS:				`SDK/ambarella/boot/tee/optee_os`
 * - OP-TEE_Client:			`SDK/ambarella/boot/tee/optee_client`
 * - OP-TEE_Test:			`SDK/ambarella/boot/tee/optee_test`
 *
 * @section anti_rollback 4. Anti-Rollback
 * To prevent the software version from being rolled backed by a hacker (a method used by hackers to exploit known security vulnerabilities in older software versions), the
 * Ambarella CV5x / CV7x series provides a hardware monotonic counter, which can be used for anti-rollback.
 *
 * @section disable_hw_debug_port 5. Disable the Hardware Debug Port
 * Ambarella recommends removing or disabling hardware debug ports, including force USB boot and joint test action group (JTAG).
 * On CV5x, force USB boot is disabled when secure boot is enabled.  Additionally, there is an eFUSE bit that can be used to disable JTAG.
 *
 * @section disable_no_secure_protocol 6. Disable the Non-Secure Protocol / Port
 * Ambarella recommends disabling all ports for non-secure protocols.  The following is a widely used, non-secure protocol list: Telnet (port 23), file transfer protocol (FTP)
 * (port 21), trivial file transfer protocol (TFTP) (port 69), hypertext transfer protocol (HTTP) (port 80), and system gateway (port 19531).
 * For remote login, secure shell (SSH) is more secure than Telnet and HTTPS is more secure than HTTP.
 * The following command enables users to check what port is opened using the portscan tool, `nmap`:
 * @code
 * #apt-get install nmap
 * nmap -A 10.0.0.2
 * nmap -A –p1-65535 10.0.0.2
 * @endcode
 *
 * @section buffer_overflow_attack_resistance 7. Buffer Overflow Attack Resistance
 * Hackers commonly use buffer overflow attacks.  To resist a buffer overflow attack, Ambarella recommends that users enable the following items supported by the SDK.
 * Additionally, users should remove / reduce software bugs, especially string manipulation functions.  Users are forbidden from using unsafe string functions, such as `strcpy`,
 * `strcat`, and `sprintf`.  As an alternative, Ambarella recommends using `strncpy` and `snprintf`.
 *
 * @subsection add_space_layout_randomization 7.1. Address Space Layout Randomization
 * Address space layout randomization (ASLR) increases the difficulty of a buffer overflow attack.  Linux supports ASLR.  Use the command below to enable it on Ambarella chips:
 * @code
 * echo 2 > /proc/sys/kernel/randomize_va_space
 * @endcode
 *
 * @subsection pos_independent_executable 7.2. Position Independent Executable
 * Position independent executable (PIE) enables code to be executed at different places, thus increasing the difficulty of a buffer overflow attack.  PIE is supported by the GNU
 * compiler collection (GCC), as shown below:
 * @code
 * -fPIE -pie
 * @endcode
 *
 * @subsection no_execute_protect 7.3. No-eXecute Protect
 * No-eXecute protect (NX) prevents execution on the no-execute part and is enabled, by default, in GCC.  The following demonstrates how to enable and disable NX.
 * - Disable NX:
 * `-z execstack`
 * - Enable NX:
 * `-z noexecstack`
 *
 * @subsection stack_protector 7.4. Stack Protector
 * GCC supports stack protection.  The compile option enables the stack protector.
 * - Protect functions that have string / char local variables:
 * `-fstack-protector`
 * - Protect all functions:
 * `-fstack-protector-all`
 *
 * @subsection fortify 7.5. FORTIFY
 * FORTIFY is a GCC feature that can be used for code and runtime checks if there is a potential buffer overflow risk.
 * - Buffer overflow check at the compile stage:
 * `-D_FORTIFY_SOURCE=1`
 * - Buffer overflow check at both the compile and runtime stages:
 * `-D_FORTIFY_SOURCE=2`
 *
 * @subsection read_only_relocation 7.6. Read-Only Relocation
 * GCC supports read-only relocation (RELRO), which means the relocation region is read-only.  RELRO can increase the difficulty of a buffer overflow attack and can be used to
 * protect the global offset table (GOT).
 * By default, the RELRO setting is partial (partial RELRO means the GOT is writable).
 * - Disable RELRO:
 * `-z norelro`
 * - Partial RELRO:
 * `-z,relro -z lazy`
 * - Full RELRO:
 * `-z,relro -z,now`
 *
 * @section dram_scrambling 8. DRAM Scrambling
 * Dynamic random-access memory (DRAM) scrambling is automatically enabled when secure boot is enabled; it is designed to prevent a potential sniffer on the physical DRAM memory.
 *
 * @section cve_fix_strategy 9. CVE Fix Strategy
 * Regarding CVE fixes, Ambarella synchronizes up to the latest version of the Linux kernel and open sourse software (OSS) modules, then provide the updates inside the SDK package
 * (quarterly or bi-quarterly) for both Linux kernel and OSS module fixes.
 * For these open source modules, Ambarella relies only on the community updates, but will not provide its own fixes for these modules.
 * This is a general support rule of CVE fixes for all Cooper Linux SDK customers. 
 *//*!
 * @file data_storage_protection.h
 * @brief
 * @version 1.0
 * @date 2023-12-13
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
 * @page data_storage_protection Data Storage Protection
 * @section data_part_enc 1. Data Partition Encryption
 * The Ambarella Flexible Linux Software Development Kit (SDK) supports dm-crypt, a standard feature in Linux for data partition encryption (DPE), 
*  which encrypts the entire partition.
 *
 * @subsection dm_crypt 1.1 dm-crypt
 * Using the Linux kernel’s crypto application programming interface (API) framework and device mapper subsystem, dm-crypt enables administrators to encrypt entire disks, logical
 * volumes, partitions, and single files.
 * The dm-crypt subsystem supports the Linux unified key setup (LUKS) structure, which enables multiple keys to access the encrypted data, as well as the ability to manipulate the
 * keys (such as changing the keys, adding additional passphrases, and more.)
 *
 * @subsubsection setup_dm_crypt_on_amba_platform 1.1.1 Set Up dm-crypt on the Ambarella Platform
 * Follow the steps below to set up dm-crypt:
 * -# The configuration for the Linux kernel is as follows:
 * @code
 * build$ make linux_menuconfig
 *        ->[*] ARM64 Accelerated Cryptograohic Algorithems
 *         -><*> AES core cipher using ARMv8 Crypto Extensions
 *          <*> AES in ECB/CBC/CTR/XTS modes using ARMv8 Crypto Extensions
 *
 *        ->Cryptographic API
 *         -><M> User-sapce interface for sysmmetric key cipher algorithms
 *
 *        ->Device Drivers
 *         ->[*] Multiple devices driver support (RAID and LVM)
           -><M> Device mapper support
 *          <M> Crypt target support
 * @endcode
 * -# The configuration for the Ambarella platform is as follows:
 * Users can enable dm-crypt and test it from the user space.
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *        -> prebuild  --->
 *         > oss  --->
 *          > prebuild-cryptsetup (prebuild/oss/armv8-a/cryptsetup)  --
 *           > Add cryptsetup utils into root_fs
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *        > meta-oe  --->
 *         > recipes-crypto  --->
 *          > cryptsetup (meta-oe/recipes-crypto/cryptsetup)
 * @endcode
 *
 * @subsubsection use_cryptosetup_to_run_dm_crypt 1.1.2 Use Cryptsetup to Run dm-crypt
 * Cryptsetup is a command-line tool that interfaces with dm-crypt for creating, accessing, and managing encrypted devices.  The following is a simple test for cryptsetup:
 * @code
 * // modprobe
 * modprobe dm-crypt
 * modprobe  algif_skcipher
 *
 * // Create a simple image for test
 * dd if=/dev/zero of=./secret.img bs=1M count=50
 * losetup /dev/loop8 ./secret.img
 *
 * // create encrypt fs on image
 * cryptsetup -y create test_encrypt_fs   /dev/loop8
 *
 * //setup file system and mount
 * mkfs.ext2 /dev/mapper/test_encrypt_fs
 * mkdir  /mnt/test_encrypt_fs
 * mount /dev/mapper/test_encrypt_fs /mnt/test_encrypt_fs -t ext2
 * @endcode
 *
 * @subsubsection 1.1.3 benchmark_for_aes_with_crypto_exten Benchmark for AES with Crypto Extensions
 * Cryptosetup uses Armv8 crypto extensions to accelerate the advanced encryption standard (AES) speed.  Follow the steps below to test AES performance:
 * @code
 * board# cryptsetup benchmark -c aes-ecb -s 256
 * Tests are approximate using memory only (no storage IO).
 * Algorithm |       Key |      Encryption |      Decryption
 *     aes-ecb        256b       368.6 MiB/s       368.3 MiB/s
 * board# cryptsetup benchmark -c aes-cbc -s 256 -v
 * Tests are approximate using memory only (no storage IO).
 * Algorithm |       Key |      Encryption |      Decryption
 *     aes-cbc        256b       271.0 MiB/s       341.0 MiB/s
 * board# cryptsetup benchmark -c aes-ctr -s 256
 *  Tests are approximate using memory only (no storage IO).
 * Algorithm |       Key |      Encryption |      Decryption
 *    aes-ctr        256b       340.6 MiB/s       342.3 MiB/s
 * board# cryptsetup benchmark -c aes-xts -s 256
 *  Tests are approximate using memory only (no storage IO).
 * Algorithm |       Key |      Encryption |      Decryption
 * aes-xts        256b       349.3 MiB/s       351.7 MiB/s
 * @endcode
 *
 * @section data_enc_protection 2. Data Encryption Protection
 * Ambarella provides different crypto libraries for data encryption.
 *
 * @subsection data_enc_alg 2.1 Data Encryption Algorithm
 * AES is a popular block cipher for data encryption.
 * The Ambarella SDK supports 128-bit, 192-bit, and 256- bit AES, as well as ECB / CBC / CTR / XTR modes.  Ambarella recommends using the AES algorithm.
 *
 * @subsection crypto_lib 2.2 Cryptography Library
 * The paths for the prebuilt library and OpenSSL sample code are listed below:
 *  - OpenSSL prebuilt library: `ambarella/prebuild/oss/armv8-a/openssl`
 *  - AES OpenSSL sample code: `ambarella/security/validation/crypto_performance/ openssl`
 * @note
 * OpenSSL can use the Armv8 crypto extension instructions to achieve a high AES performance.
 *
 * @subsection lightweight_crypto_lib 2.3 Lightweight Cryptography Library in Linux
 * The paths for library and sample code for the lightweight cryptography library in Linux are provided below.
 *  - Library code: `ambarella/security/lw_cryptography/src`
 *  - Sample code: `ambarella/security/lw_cryptography/unit_test`
 * @note
 * The lightweight cryptography library does not use Armv8 crypto extension instructions, and its AES performance is sub-optimal.
 *
 * @subsection native_aes_with_crypto_extension 2.4 Native AES with Crypto Extension Instructions in Linux
 * The paths for the native AES with crypto extension instructions in Linux are as follows:
 *  - Library code: `ambarella/security/crypto_engine/src/armv8_crypto_extension`
 *  - Sample code: `ambarella/security/crypto_engine/unit_test`
 *
 * @subsection mbed_tls_in_atf 2.5 Mbed TLS in ATF
 * The path for Mbed TLS in Arm® trusted firmware (ATF) is as follows:
 *  - Library code: `ambarella/boot/tee/mbedtls`
 *
 * @section secure_storage 3. Secure Storage
 * Secure storage refers to data-at-rest protection (DARP), or data in an encrypted form in external storage.
 *
 * @subsection data_at_rest_protection 3.1 Data at Rest Protection
 * The data encryption key is managed by the trusted OS (OP-TEE), and is inaccessible from the unsecure world.  The following diagram displays the data encryption flow.
 * Abbreviations used in the diagram include the following:
 *  - HUK: hardware-unique encryption key, unique to each chip, on one-time programmable (OTP)
 *  - SSK: secure storage key, unique to each chip
 *  - TSK: trusted application storage key, unique to each application
 *  - FEK: file encryption key, random per file
 *  - HMAC: hash-based message authentication code
 *
 * @anchor Data_Encryption_Diagram
 * @image html data_encryption_diag.png "Figure 3-1. Data Encryption Diagram."
 * The paths for the example code of the client application (CA) and for the trusted application (TA) are as follows:
 *  - CA: `ambarella/boot/tee/optee_test/host/test_secure_storage`
 *  - TA: `ambarella/boot/tee/optee_test/ta/test_secure_storage`
 *
 * @subsection data_protection_by_passphrase 3.2 Data Protection by Passphrase
 * Data protection by passphrase is demonstrated on the following page.
 * @anchor Data_Protection_by_Passphrase_Diagram
 * @image html data_protection_by_passphrase.png "Figure 3-2. Data Protection by Passphrase Diagram."
 * The paths for the example code of the CA and TA are as follows:
 *  - CA: `ambarella/boot/tee/optee_test/host/data_encryption_aes_v2`
 *  - TA: `ambarella/boot/tee/optee_test/ta/data_encryption_aes_v2`
 *//*!
 * @file data_transfer_protection.h
 * @brief
 * @version 1.0
 * @date 2023-12-14
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
 * @page data_transfer_protection Data Transfer Protection
 *
 * For data transfer protection, Ambarella recommends choosing the widely used transport layer security (TLS); 
 * it is the best practice for data transfer protection.  The Ambarella software development kit (SDK) supports TLS in both Linux and the trusted operating system (TOS) (open
 * portable trusted execution environment (OP-TEE)).  
 * Additionally, a similar secure connection is supported in CVflow.
 * 
 * @section ssl_and_tls 1. SSL and TLS
 * Secure socket layer (SSL) and its successor, TLS, are protocols for establishing authenticated and
 * encrypted links between networked computers.  SSL encrypts the data being transmitted so that a third
 * party cannot eavesdrop on the transmission and view the data being transmitted.  Only the user’s
 * computer and the secure server are able to recognize the data.
 *
 * @subsection ssl_protocols 1.1 SSL Protocols
 * SSL protocols include the SSL record protocol, handshake protocol, change-cipher specification protocol, and alert protocol.
 *
 * @subsubsection 1.1.1 ssl_protocol_stack SSL Protocol Stack
 * The figure below shows the SSL protocol stack:
 * <table>
 * <caption id="ssl_protocol_stack">Table 1-1. SSL Protocol Stack.</caption>
 * <tr><th align="left">Handshake Protocol<th align="left">Change Cipher Spec Protocol<th align="left">Alert Protocol<th align="left">HTTP
 * <tr><td align="center" colspan="4">SSL Record Protocol
 * <tr><td align="center" colspan="4">TCP
 * <tr><td align="center" colspan="4">IP
 * </table>
 *
 * @subsubsection ssl_record_protocol 1.1.2 SSL Record Protocol
 * SSL record protocol provides two services to the SSL connection:
 *  - Confidentality
 *  - Message integrity
 * In the SSL record protocol application, data is divided into fragments.  The fragments are compressed, and then the encrypted MAC generated by algorithms (such secure hash
 * protocol (SHA)) is appended.  Subsequently, the encryption of the data is completed and the last SSL header is appended to the data.
 *
 * @subsubsection handshake_protocol 1.1.3 Handshake Protocol
 * The handshake protocol is used to establish sessions.  This protocol enables the client and the server to mutually authenticate by sending a series of messages to one another.
 *
 * @subsubsection change_cipher_protocol 1.1.4 Change-Cipher Protocol
 * This protocol uses the SSL record protocol.  Unless the handshake protocol is completed, the SSL record output will be in a pending state.  After the handshake protocol, the
 * pending state is converted into the current state.
 * The change-cipher protocol consists of a single message, which is one byte in length and can have only one value.  This protocol causes the pending state to be copied into the
 * current state.
 *
 * @subsubsection alert_protocol 1.1.5 Alert Protocol
 * This protocol is used to convey SSL-related alerts to the peer entity.  Each message in this protocol contains two bytes: 1-byte level and 1-byte alert.
 *
 * @subsection ssl_work_flow 1.2 SSL Work Flow
 * An SSL session is established over a TCP socket.  The following sequence demonstrates the flow for an existing TCP application that has been modified to use SSL:
 *  -# `CLIENT_HELLO`: the client sends a `CLIENT_HELLO` command to the server, which includes the following:
 *   - The highest SSL and TLS version supported by the client
 *   - Ciphers supported by the client (listed in order of preference)
 *   - Data compression methods supported by the client
 *   - Session ID.  If the client is starting a new SSL session, the session ID is 0
 *   - Random data generated by the client for use in the key generation process
 *  -# `SERVER_HELLO`: the server sends a `SERVER_HELLO` command to the client, which includes the SSL or TLS version that will be used for the SSL session.  The cipher will also be used for the SSL session.  Note that the session ID is for the SSL session.  Additionally, random data will be generated by the server for use in the key generation process
 *  -# `CERTIFICATE`: the server sends the `CERTIFICATE` command.  This command includes the server’s certificate and, optionally, a chain of certificates beginning with the certificate of the client application (CA) that assigned the server’s certificate
 *  -# `SERVER_DONE`: the server sends the `SERVER_DONE` command, which indicates that the server has completed this phase of the SSL handshake.  If client authentication is performed, additional commands will flow between the client and the server following the `SERVER_DONE` command
 *  -# `CERTIFICATE_VERIFY`: the client informs the server that it has verified the server’s certificate
 *  -# `CHANGE_CIPHER_SPEC`: the client sends the `CHANGE_CIPHER_SPEC` command.  This command indicates that the contents of subsequent SSL record data sent by the client during the SSL session will be encrypted.  The 5-byte SSL record headers are never encrypted
 *  -# `FINSHED`: the client sends the `FINSHED` command.  This command includes a digest of all SSL handshake commands that have flowed between the server and the client up to this point.
 * The figure below demonstrates an SSL handshake.
 * @anchor SSL_Handshake
 * @image html ssl_handshake.png "Figure 1-1. SSL Handshake."
 *
 * @section tls_solution_in_amba 2. TLS Solutions in the Ambarella SDK
 * Ambarella uses OpenSSL in the normal world and MbedTLS in the secure world to set up TLS connections.  Users can set up a TLS server and make a connection with the chip.  The
 * TLS client can be set up in both the normal world (Linux) and the secure world (OP-TEE).
 * The path for example code of the TLS server is `packages/security/reference_code/openssl_tls_test/openssl_tls_test_server`.
 *
 * @subsection tls_client_in_normal_world 2.1 TLS Client in Normal World
 * Ambarella uses OpenSSL to set up a TLS connection in the normal world.  The TLS work flow is provided, as shown below:
 * @anchor TLS_Connection_Between_the_Server_and_Normal World
 * @image html fig_tls_connection.png "Figure 1-2. TLS Connection Between the Server and Normal World."
 * The path for example code of the TLS client in the normal world is `packages/security/reference_code/openssl_tls_test/openssl_tls_test_client`.
 *
 * @section secure_connection_in_cvflow 3. Secure Connection in CVflow®
 * CVflow supports ED25519 and X25519, which provide support for secure connections.
 *
 *//*!
 * @file system_integrity_protection.h
 * @brief
 * @version 1.0
 * @date 2023-12-14
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
 * @page system_integrity_protection Intellectual Property Protection
 * Pan Shi provides two major features for intellectual property protection: unit licence protection (ULP), 
 * which prevents one license from covering multiple devices, and neural network (NN) model protection (NMP), 
 * which protects the vendor’s NN model from being reverse-engineered by attackers.
 *
 * @section ulp 1. Unit License Protection
 * For unit license protection (ULP), the software / algorithm vendor issues a unit license to devices: 
 * the device with the unit license is able to run the vendor’s software / algorithm; 
 * however, the device without the unit license is not able to run the vendor’s software / algorithm.
 * There are two online verification approaches: unique ID and non-forgeable unique ID.
 * Additionally, there are two on-chip verification approaches: via the external hardware module and via AMBA on-chip verification.
 * Online verification offers better device management, while the on-chip verification is faster and is lower cost because it 
 * does not require verification cloud service.
 *
 * <table>
 * <caption id="unit_license_difference">Table 1-1. Comparisons Between Different Unit License Approaches.</caption>
 * <tr><th align="left"> <th align="left">Unique ID<th align="left">Non-Forgeable Unique ID<th align="left">External HW Module<th align="left">Ambarella On-Chip Verification
 * <tr><th>Cost<td>No extra cost<td>No extra cost<td>HW module cost<td>No extra cost
 * <tr><th>Forge License<td>Easy (duplicate unique ID)<td>Difficult<td>Difficult<td>Difficult
 * <tr><th>Requires Online Verification<td>Yes<td>Yes<td>Depends on implementation<td>Not required
 * <tr><th>Verify Time Cost<td>Typical 500 ms – 2000 ms, varies with different networks and servers<td>Typical 500 ms – 2000 ms, varies with different networks and servers<td>Typical 20 ms – 1000 ms, varies with different hardware<td>CV0 3 ms or CVflow 900 ms
 * </table>
 *
 * @subsection non_forgeable_uuid 1.1 Non-Forgeable Unique ID
 * Individual devices must possess unique IDs, and therefore require different unit licenses.  If the unique ID is forgeable, the attacker is able to tamper with a batch of devices
 * with one unique ID.
 * The following diagram shows the problems of a forgeable, unique ID (marked in yellow on the right side).
 *
 * @anchor Problems_of_Forgeable_Unique_ID
 * @image html forgeable_uuid_problem.png "Figure 1-1. Problems of Forgeable Unique ID."
 * Vendors who choose the online verification approach must use a non-forgeable, unique ID to protect the unit license.
 * The ULP in the Ambarella Flexible Linux Software Development Kit (SDK) supports both non-forgeable unique ID and AMBA on-chip verification.
 *
 * @subsection ulp_concept 1.2 Unit License Protection Concept
 * The software / algorithm vendor uses its private key to issue a “unit license” to each device.  
 * If a device has a valid unit license, then it is able to run the vendor’s software / algorithm; 
 * otherwise, the vendor’s software / algorithm is not available.  Vendors can use this mechanism to charge per device unit.
 * A device with a unit license is called an “activated device”; a device without a unit license is called a “not-activated device”.
 *
 * @anchor Activated_Device_and_Not_Activated_Device
 * @image html activated_device_and_not_activated_device.png "Figure 1-2. Activated Device and Not-Activated Device."
 *
 * @subsection related_keys_and_certs 1.3 Related Keys and Certificates
 * This section describes the keys and certificates associated with the ULP solution, followed by a table listing the format, owner, confidentiality, and storage information of
 * the related keys and certificates.<br>
 * - The vendor license key (VLK) is an asymmetric key (ED25519).  The vendor generates the VLK and must maintain confidentiality of the private VLK.  The private VLK owner is able
 * to issue a unit license; therefore, the vendor maintains the private VLK’s confidentiality.  The owner is the only entity to issue the unit license.  The vendor must send the
 * public VLK to Ambarella, and Ambarella will issue a license certificate to the vendor.  The public VLK is embedded inside the license certificate.<br>
 *
 * - The Ambarella certificate key (ACK) is an asymmetric key (ED25519).  Ambarella uses the ACK to issue a license certificate for vendors.<br>
 *
 * - The Ambarella platform key (APK) is an asymmetric key (ED25519).  The APK is used in scenarios where providing the ULP transaction is being conducted on the actual Ambarella
 * platform, not a simulator.  Note that there are two APKs: one for CVflow, and one for the CV0 library.<br>
 *
 * - The device identity key (DIK) is an asymmetric key (ED25519).  The DIK is dynamically derived from the chip hardware’s unique information and the vendor’s license certificate;
 * therefore, it is not statically stored on the chip.  Additionally, the DIK is unique per chip: different vendors will have unique DIKs.  This design prevents cross-vendor
 * attacks and analyses.<br>
 *
 * - The client key is the vendor’s customer identity key; it is also asymmetric (ED25519).  The vendor’s customer must keep the private client key confidential.  The public client
 * key is sent to the vendor’s license server during registration, and the vendor’s server stores it in its database.<br>
 *
 * - The certificate authority key is an asymmetric key (RSA or ECDSA), which is used to sign the client application (CA) certificate or the server certificates.<br>
 *
 * - The server key is the server’s identity key; it is also asymmetric (RSA or ECDSA).  The server key proves that the server is not fake during TLS.<br>
 *
 * - The license certificate, which is issued by Ambarella, embeds and protects both the public VLK and the public APK.  It is a binary file with a length of 256 bytes.  Typically,
 * the license certificate is distributed together with the vendor’s software package.  The license certificate is required for chips that invoke ULP-related application
 * programming interfaces (APIs).<br>
 *
 * - The CA certificate is the root certificate of the TLS, issued by the vendor or a third-party CA.  The CA certificate is in a standard x.509 format.<br>
 *
 * - The server certificate is a certificate of a server that is part of the chain of trust (CoT), while the CA certificate is the root of the CoT.<br>
 *
 * - The device encryption key (DEK) is a symmetric key (advanced encryption standard (AES)).  The DEK is dynamically derived from the chip hardware’s unique information and
 * vendor’s license certificate; therefore, it is not statically stored on the chip.  The DEK is unique per chip; some vendors will have different DEKs for the same chip.  This
 * design prevents cross-vendor attacks and analyses.<br>
 *
 * - The package encryption key (PEK) is a symmetric key (AES).  Because the PEK is used to encrypt the neural network (NN) model, the vendor must maintain the PEK’s confidentiality.<br>
 *
 * @note
 * The DEK and PEK are only required for ‘ULP + NMP’ cases.  If only the ULP case is used, users can disregard the DEK and PEK.<br>
 * The following table lists the related keys and certificates.
 * <table>
 * <caption id="related_keys_and_certs">Table 1-2. Related Keys and Certificates.</caption>
 * <tr><th align="left"> <th align="left"> <th align="left">Format<th align="left">Owner<th align="left">Keep Confidential<th align="left">Storage and Comment
 * <tr><td rowspan="2">VLK<td>Private<td rowspan="2">ED25519<td rowspan="2">Vendor<td>Yes, the vendor keeps the private VLK confidential<td>Stored at the vendor license server in encrypted form
 * <tr><td>Public<td><B>No</B>, the vendor sends the public VLK to Ambarella<td>Stored at the license certificate
 * <tr><td rowspan="2">ACK<td>Prvate<td rowspan="2">ED25519<td rowspan="2">Ambarella<td>Yes, Ambarella keeps the private ACK confidential<td>
 * <tr><td>Public<td>Yes, the chip keeps the public ACK confidential<td>
 * <tr><td rowspan="2">APK<td>Private<td rowspan="2">ED25519<td rowspan="2">Chip<td>Yes, the chip keeps the private APK confidential<td>
 * <tr><td>Public<td><B>No</B>, the public APK is inside the license certificate<td>Stored at the license certificate
 * <tr><td rowspan="2">DIK<td>Private<td rowspan="2">ED25519<td rowspan="2">Chip<td>Yes, the chip keeps the private DIK confidential<td rowspan="2">The DIK is unique per chip.  On the same chip, different vendors (different license certificates) will receive different DIKs
 * <tr><td>Public<td><B>No</B>, the public DIK is a device unique ID
 * <tr><td rowspan="2">Client key<td>Private<td rowspan="2">ED25519<td rowspan="2">Vendor’s customer<td>Yes, the vendor’s customer keeps the private client key confidential<td>Stored at the deployment tool side in encrypted form
 * <tr><td>Public<td><B>No</B>, the vendor’s customer sends the public client key to the vendor license server<td>Stored at the license server’s database
 * <tr><td rowspan="2">CA key<td>Private<td rowspan="2">RSA or ECDSA<td rowspan="2">Vendor or third-party CA<td>Yes, the vendor or third-party CA keeps the private CA key confidential	<td>
 * <tr><td>Public<td> <td>
 * <tr><td rowspan="2">Server key<td>Private<td rowspan="2">RSA or ECDSA<td rowspan="2">Vendor<td>Yes, the vendor keeps the private server key confidential<td>
 * <tr><td>Public<td> <td>
 * <tr><td colspan="2">License certificate<td>Binary<td>Ambarella and Vendor<td>No, Ambarella issues a certificate to the vendor<td>Distributed by the vendor
 * <tr><td colspan="2">CA certificate<td>X.509<td>Vendor<td><B>No</B>, the vendor distributes its CA certificate to its customer<td>Stored at the vendor’s server side and the client’s deployment tool
 * <tr><td colspan="2">Server certificate<td>X.509<td>Vendor<td><B>No</B><td>Stored at the vendor’s server and the client’s deployment tool
 * <tr><td colspan="2">DEK (Optional)<td>AES<td>Chip<td>Yes, the chip keeps the DEK confidential<td>DEK is unique per chip. On the same chip, different vendors (different license certificates) will receive different DEKs
 * <tr><td colspan="2">PEK (Optional)<td>AES<td>Vendor<td>Yes, the vendor keeps the PEK confidential<td>Stored at the vendor’s license server in encrypted form
 * </table>
 *
 * @subsection license_deployment_process 1.4 License Deployment Process
 * The vendor generates a VLK and uses this VLK to issue licenses via a license server.  Each manufacturer (customer of the vendor) uses a deployment tool to distribute the unit
 * license (activating devices).  The manufacturer must register an account with the vendor’s approval.  The vendor also specifies the number of licenses for each account
 * (manufacturer).
 * The connection between the manufacturer’s deployment tool and the vendor’s license server uses TLS, along with a bi-directional authentication process.  This design prevents
 * attacks from the internet.
 * The DIK is used as a device ID; the VLK sign “public DIK + meta” is used as a unit license.  If the vendor maintains confidentiality of its private VLK, then only the vendor
 * can generate unit licenses.
 * Because each device has a unique device ID (public DIK), each unit license applies only to a single device.
 * @note
 * Engineering samples may have the same device ID, but mass-production (MP) chips have unique device IDs.
 * Note that the unit license file is 256 bytes; therefore, the deployment process will require a writeable space to store the unit license file.  The unit license file location
 * is configurable in the `.lc` file.  The product design must consider the writable space in the file system for this feature.
 *
 * @anchor Fig_License_Deployment_Process
 * @image html license_deployment_process.png "Figure 1-3. License Deployment Process."
 *
 * @subsection license_verification_process 1.5 License Verification Process
 * There are two license verification methods: local verification and online verification.  The Ambarella Flexible Linux SDK supports both methods, and the vendor can choose
 * according to their requirements.  While local verification is fast and does not require cloud service for the license verification, online license verification provides better
 * management for devices.
 *
 * @subsubsection local_license_verification_process 1.5.1 Local License Verification Process
 * Ambarella’s CVflow / CV0 library performs a unit license check and reports the result to the vendor’s software.  This license verification process does not require network access.
 * The license verification process is as follows: “Pub ACK” -> verify “license certificate” -> retrieve “Pub VLK” -> verify that the “unit license” is valid.
 * The vendor’s software triggers the license verification process by invoking the related application programming interfaces (APIs).  For more details on verifying license APIs,
 * refer to `ambarella/security/ulp_nmp/common/platform_ cvflow.c` and `platform_cv0.c`.
 * 
 * The APIs are as shown below.
 * @code
 * CVflow: ioctl(thiz->fd, CAVALRY_ULP_VERIFY_LICENSE, &ulp_verfiy_lic)
 * CV0 Library: thiz->library.ulp_verify_license()
 * @endcode
 * 
 * The CVflow / CV0 library response also includes the `ED25519_sign` (APK, challenge) and the `ED25519_sign` (DIK, challenge).  The challenge is sent by the vendor’s software
 * and is a nonce from the random number generator (RNG).
 * The challenge includes a random nonce in order to prevent a “replay attack”.  The replay attack records and reuses historic valid responses.  As such, the random nonce guarantees
 * that each challenge is different; consequently, historically valid responses cannot be reused.
 *
 * @subsubsection non_forgable_uuid 1.5.2 Non-Forgeable Unique ID for Online Verification
 * ULP implementation also supports online license verification.  The key purpose is to provide a non-forgeable unique ID.
 * The non-forgeable unique ID includes a random challenge, a unique ID, and an APK signature.  The server generates the random challenge and verifies the APK signature in order
 * to ensure that the unique ID has not been forged.
 *
 * @anchor Non_Forgeable_Unique_ID
 * @image html non_forgeable_uuid.png "Figure 1-4. Non-Forgeable Unique ID."
 *
 * @subsubsection compare_with_ither_ul 1.5.3 Comparing with Other Unit License Approaches
 * There are four approaches for unit license protection: “unique ID + online verification”; “non-forgeable unique ID + online verification”; “external hardware module”; and
 * “AMBA chip verification”.
 * The primary difference between a unique ID and a non-forgeable unique ID is that the non-forgeable unique ID can prevent multiple chips from being exploited with a tampered
 * duplicated ID running on a single license.
 * Additionally, the primary difference between the external hardware module and the Ambarella chip verification is cost.
 * As described previously, the Ambarella Flexible Linux SDK supports two approaches: “non-forgeable unique ID + online verification” and “AMBA chip verification”.
 * The comparison list is as follows.
 * <table>
 * <caption id="compare_different_ul">Table 1-3. Comparison Table of Different Unit License Approaches.</caption>
 * <tr><th align="left"><th align="left">Unique ID<th align="left">Non-Forgeable Unique ID<th align="left">External Hardware Module<th align="left">Ambarella Chip Verification
 * <tr><td>Cost<td>No extra cost<td>No extra cost<td>Hardware module cost<td>No extra cost
 * <tr><td>Forge license difficulty<td>Easy (duplicate unique ID)<td>Difficult<td>Difficult<td>Difficult
 * <tr><td>Online verification service requirement<td>Required<td>Required<td>Depends on the implementation<td>Not required
 * <tr><td>Speed of license verification<td>Depends on the network speed and the server capability<td>Depends on the network speed and the server capability<td>Fast<td>Fast
 * </table>
 *
 * @subsection on_chip_sw_hierarchy 1.6 On-Chip Software Hierarchy
 * For the green-colored components shown in the following image, the Linux SDK provides sample code for the evaluation of the information maintained by the software vendor.
 * For the blue-colored components, the SDK includes the source code.
 *
 * @anchor On_Chip_Software_Hierarchy
 * @image html on_chip_sw_hierarchy.png "Figure 1-5. On-Chip Software Hierarchy."
 *
 * @subsection sw_hierarchy_on_linux_pc 1.7 Software Hierarchy on the Linux PC
 * For the green-colored components shown below, the Linux SDK provides the sample code for the evaluation of the information maintained by the software vendor.
 *
 * @anchor Software_Hierarchy_on_the_Linux_PC
 * @image html sw_hierarchy_on_linux_pc.png "Figure 1-6. Software Hierarchy on the Linux PC."
 *
 * @subsection muti_customers_support 1.8 Support for Multiple Customers
 * With the reference code, the vendor is able to support multiple customers, and the license server manages transactions in parallel.  The system diagram, showing support for
 * multiple customers, is below.
 *
 * @anchor Multiple_Customers_Support
 * @image html muti_customers_support.png "Figure 1-5. System Diagram Showing Support for Multiple Customers."
 *
 * @section ulp_user_guide 2. Unit License Protection User Guide
 *
 * @subsection compile_ulp_sample_code 2.1 Compile Unit License Protection Sample Code
 * The Ambarella ULP sample code (demonstrated in the following sections) includes two parts: one part runs on the SoC, and the other runs on Linux (Ubuntu).
 *
 * @subsubsection sample_code_on_pc 2.1.1 Compile Sample Code on the SoC
 * Select 'menuconfig' below.
 *
 * <B>Amba build:</B>
 * @code
 * -> security  --->
 * -> ulp-nmp (security/ulp_nmp) --->
 *  -> ulp-nmp (security/ulp_nmp)
 *   -> ULP and NMP by CVflow
 *   -> ULP by CV0 Library
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * -> meta-ambasecurity  --->
 *  -> recipes-ulpnmp  --->
 *   -> ulpnmp (meta-ambasecurity/recipes-ulpnmp/ulpnmp)  --->
 *    -> ulpnmp (meta-ambasecurity/recipes-ulpnmp/ulpnmp)
 *     -> ULP and NMP by CVflow
 *     -> ULP by CV0 Library
 * @endcode
 *
 * On CV5x / CV7x / CV3 chips, “by CVflow” and “by CV0 library” can be selected simultaneously.
 * The license deploys and verifies the unit test (`ulp_nmp_pt_activate` and `ulp_nmp_pt_check_license`), which is located under `/usr/local/bin/` on the SoC.
 * The default option uses the default key and certificate to set up the ULP and NMP (refer to @ref quick_launch_user_guide).  If using the key generated by the user, “ULP use
 * product certs” must be selected (refer to @ref launch_from_scratch).
 *
 * @subsubsection ulp_prerequisites 2.1.2 Prerequisites
 * Because the sample code on Linux (Ubuntu) requires OpenSSL, install it first.  The minimum-required version of OpenSSL is 1.0.2.
 * @code
 * apt-get install openssl
 * @endcode
 * Generate a random seed for OpenSSL.
 * @code
 * cd ~
 * openssl rand -out .rnd 1
 * @endcode
 *
 * @subsubsection sample_code_on_linux 2.1.3 Compile Sample Code on Linux (Ubuntu)
 * Go to the source code location and compile.
 * @code
 * cd $(SDK)/ambarella/security/ulp_nmp
 * make && make install && make install_configs
 * @endcode
 *
 * The servers and tools are placed in `$(SDK)/ambarella/security/build/`.
 *
 * @subsection launch_from_scratch 2.2 Launch from Scratch User Guide
 * Components related to ULP include the license server, the deployment tool, and the provisioning tool on the device.
 * The following sections describe how to launch the license server and tools after compiling and installing the configurations.
 * Users can also refer to the help file located at `$(SDK)/ambarella/security/ulp_nmp/doc/ulp_ from_scratch_steps.txt`.
 *
 * @note
 * This chapter includes key generation.  Keep the private key and encryption key confidential, retain the passphrase for each key, and enable backup storage for the keys.  There
 * is no recovery option for a lost key file or forgotten passphrase.
 *
 * @subsubsection compile_installl_config 2.2.1 Compile and Install Configurations
 * Go to the source code location, compile, and install.
 * @code
 * build $ cd $(SDK)/ambarella/security/ulp_nmp
 * build $ make && make install && make install_configs
 * @endcode
 *
 * @subsection launch_license_server 2.2.2 Launch the License Server
 * Go to the license sever location.
 * @code
 * build $
 * cd $(SDK)/ambarella/security/build/ulp_nmp_license_server/
 * @endcode
 *
 * <b>First-Time Setup</b><br>
 * The license server requires some prerequisites: the CA key and certificate, the server key and certificate, the vendor license key and certificate, the package encryption key,
 * and so on.  The “first time setup” steps show how to generate or get those prerequisites.  Typically,“first time setup” must be performed only once because it generates new keys
 * and replaces existing keys.  If the key file is replaced, there is no way to recover it.  Users must be very cautious when executing those command lines; only do so when necessary.
 * @note
 * Before generating keys, change the key passphrases `-pass pass:1234` and `--passphrase 1234` for the following command lines.  `1234` is the default passphrase for test purposes only; <B>DO NOT</B> use it in production.
 * 
 * -# Generate a CA key and a CA certificate.
 * @code
 * build $ openssl genpkey -algorithm RSA -out ./keys/priv_ca.pem -pkeyopt rsa_keygen_bits:2048 -pkeyopt rsa_keygen_pubexp:65537 -pass pass:1234 -aes-256-cbc
 * build $ openssl req -new -x509 -days 3650 -key ./keys/priv_ca.pem -out ./certs/ca.crt -subj "/C=CN/ST=SH/L=PD/O=test/OU=test/CN=testCA/emailAddress=ca@test.com"
 * @endcode
 *
 * -# Generate a server key and issue a server certificate.
 * @code
 * build $ openssl genpkey -algorithm RSA -out ./keys/priv_svr.pem -pkeyopt rsa_keygen_bits:2048 -pkeyopt rsa_keygen_pubexp:65537 -pass pass:1234 -aes-256-cbc build $ openssl req -new -key ./keys/priv_svr.pem -out server.csr -subj /C=CN/ST=SH/L=PD/O=test/OU=test/CN=testSVR/emailAddress=svr@test.com
 * build $ openssl x509 -req -days 3650 -CA ./certs/ca.crt -CAkey ./keys/priv_ca.pem -CAserial ca.srl -CAcreateserial -in server.csr -out ./certs/server.crt
 * @endcode
 *
 * -# Generate the VLK.
 * @code
 * build $ ../ulp_nmp_key_tool/ulp_nmp_key_tool --gen-ed25519 vlk --path ./keys/ --passphrase 1234
 * @endcode
 *
 * -# Generate the PEK.  This step is only necessary when it is combined with NMP; otherwise, it can be skipped.
 * @code
 * build $ ../ulp_nmp_key_tool/ulp_nmp_key_tool --gen-aesctr pek --path ./keys/ --passphrase 1234
 * @endcode
 *
 * -# Send the public VLK to Ambarella, and get the license certificate from Ambarella.  Note that “by CVflow” and “by CV0 library” are different certificate files.
 * -# Copy the license certificate to `product_certs/`.
 *
 * By CVflow:
 * @code
 * build $ cp license_cert.bin ./certs/
 * @endcode
 *
 * By CV0:
 * @code
 * build $ cp license_cert_cv0.bin ./certs/
 * @endcode
 *
 * -# Copy the license certificate file for the device.
 * @code
 * build $ cp ./certs/ ../ulp_nmp_simulate_device –rf
 * @endcode
 *
 * <b>Launch the License Server</b><br>
 * When the prerequisites are ready, the command line below will launch a license server.  Choose `ulp_license_svr_cvflow.lc` or `ulp_license_svr_cv0.lc` accordingly, as they use
 * different certificate files.
 *
 * By CVflow:
 * @code
 * build $ ./ulp_nmp_license_server lc_configs/ulp_license_svr_cvflow.lc
 * @endcode
 *
 * By CV0 library:
 * @code
 * build $ ./ulp_nmp_license_server lc_configs/ulp_license_svr_cv0.lc
 * @endcode
 *
 * After entering the correct passphrases for “private server key,” “private VLK key,” and “PEK,” the server is running and the console displays the following information:
 * @code
 * load lc config (lc_configs/ulp_license_svr_xxx.lc) done
 * NN Model Protection Disabled
 * Check pre-requirement done
 * initialize_db (db path: db, total license file: total_license_num.txt) done
 *  * new_ssl_server_ctx done
 * Enter PEM pass phrase:
 * server_set_ca_cert_key done
 * load_license_cert done
 * Enter private VLK's passphrase:
 * verify shadow done
 * decrypt vlk priv done
 * get vlk pub done
 * store vlk pub done
 * load_priv_vlk_enc done
 * open and listen 19000 ...
 * open and listen 19000 done
 * @endcode
 *
 * @note
 * The highlighted portions are the prompts for users to enter the default passphrase “1234.”  Users must immediately change the default passphrase to a more secure passphrase,
 * as “1234” is used for test purposes only.
 *
 * @subsubsection launch_deployment_tool 2.2.3 Launch the Deployment Tool
 *
 * Go to the following location to find the deployment tool.
 * @code
 * build $
 * cd $(SDK)/ambarella/security/build/ulp_nmp_deployment_tool
 * @endcode
 *
 * <b>First-Time Setup</b><br>
 * The deployment tool requires the following prerequisites: the CA certificate, the public vendor license key, and the account key.  The “first-time setup” steps show how to
 * generate or obtain the prerequisites.  Typically, “first-time setup” is required only once.  However, because the setup process generates keys and replaces existing keys,
 * users must execute command lines with caution, and only when necessary, as the key file is not recoverable.
 * 
 * @note
 * Before generating keys, change the passphrases “-pass pass:1234” and “--passphrase 1234” for the following command lines.  “1234” is the default passphrase for test purposes only; DO NOT use it in production.
 *
 * -# Obtain the CA certificate and the public VLK from the vendor.
 * @code
 * build $ cp ca.crt ./certs/
 * build $ cp pub_vlk.bin ./keys/
 * @endcode
 *
 * -# Generate the client key for the account.
 * @code
 * build $ ../ulp_nmp_key_tool/ulp_nmp_key_tool --gen-ed25519 cli --path ./keys/ --passphrase 1234
 * @endcode
 *
 * <b>Launch the Deployment Tool</b><br>
 * When the prerequisites are ready, the command line below will launch the deployment tool.
 *
 * @note
 * Users must specify the correct license server IP address and port in `ulp_nmp_deployment_tool.lc`.
 * The deployment tool then prompts users to enter the client’s private key passphrase.  This key is the identity key for the client (vendor’s customer).
 * @code
 * new_ssl_client_ctx done
 * load vlk done
 * Enter cli priv's passphrase:
 * @endcode
 *
 * After entering the private key’s passphrase (<b>“1234” + ENTER</b>), the deployment tool runs, and the console displays the following information:
 * @code
 * verify shadow done
 * decrypt cli priv done
 * get cli pub done
 * store cli pub done
 * load cli done
 * Connecting to localhost:19000 ...
 * Connect to localhost:19000 done
 * [Handshake]: check protocol version done
 *
 * [Authenticate]: challenge to peer
 * 0x0f, 0xd5, 0xd4, 0x04, 0x70, 0x48, 0x06, 0x6e,
 * 0x55, 0xbc, 0x8a, 0xf4, 0x91, 0x26, 0x34, 0xe5,
 * 0xda, 0xd8, 0xa2, 0x10, 0x1b, 0xee, 0x35, 0x90,
 * 0x94, 0x23, 0x9f, 0xbc, 0xc1, 0xbc, 0x91, 0x7f,
 * [Authenticate]: response from peer
 * 0xea, 0x41, 0xe7, 0x06, 0x65, 0xee, 0x0b, 0xc1,
 * 0xf5, 0xf0, 0xd3, 0x94, 0x7c, 0x19, 0x56, 0x97,
 * 0xc8, 0x31, 0xf3, 0xf7, 0x1c, 0xc8, 0x9a, 0x6e,
 * 0xd1, 0x7a, 0xc4, 0x80, 0x7f, 0x81, 0xd8, 0x90,
 * 0xfa, 0xb6, 0x6f, 0x89, 0x76, 0x1b, 0x3f, 0xae,
 * 0xcb, 0x13, 0x5c, 0x39, 0x5e, 0xcf, 0xbc, 0xe5,
 * 0x00, 0xaa, 0x4c, 0xe0, 0xf2, 0x61, 0xe1, 0xa7,
 * 0x70, 0xe2, 0xdb, 0x25, 0x43, 0x84, 0x64, 0x08,
 * [Authenticate]: client authenticate server done
 *
 * login: amba_test
 * @endcode
 *
 * The login prompt is displayed.  If the account is unregistered, users must register it.  There are two approaches to registering an account: manual and interactive.
 * For the manual approach, users send the “account name” and “public account key file” to the server side and wait for the server side’s approval.  For more details regarding
 * manual approval on the server side, refer to @ref Approve_an_Account_Manually.
 * For the interactive approach, see the information below.  For more details regarding interactive approval on the server side, refer to @ref Approve_an_Account_Interactively.
 * Users must type <b>“y + ENTER”</b> to post a registration request to the server.
 *
 * @code
 * [Register]: (zhe) is not in account list, register ('y' or 'Y')? or re-enter username to login again ('l' or 'L')?
 * @endcode
 *
 * Next, users must wait for approval from the server side.  The server side also specifies the total number of licenses for this account.
 * After approval, the console outputs the log, as shown below, including the total number of licenses.  The deployment tool is now ready to activate the device.
 * 
 * @code
 * [Register]: register done
 * [Handshake]: login done
 *
 * [Authenticate]: challenge from peer
 * 0x8a, 0xf5, 0x11, 0xeb, 0xf7, 0x8e, 0x36, 0x2a,
 * 0x82, 0x36, 0x21, 0x5f, 0xa2, 0xe2, 0x94, 0x97,
 * 0x28, 0x9e, 0xaa, 0x03, 0x37, 0xeb, 0xaa, 0x81,
 * 0x5e, 0x8e, 0xc7, 0x69, 0x85, 0xd0, 0xb6, 0x92,
 * [Authenticate]: response to peer
 * 0xdc, 0x77, 0xb5, 0x9c, 0x63, 0x96, 0x88, 0xfc,
 * 0x1a, 0x94, 0x2b, 0x99, 0xdb, 0xa3, 0xf7, 0x39,
 * 0x7f, 0xc8, 0xac, 0x97, 0xb0, 0x50, 0x22, 0x6b,
 * 0x23, 0x33, 0x60, 0xd9, 0x40, 0xbd, 0x77, 0xdc,
 * 0x7e, 0x9a, 0x00, 0x40, 0xc3, 0x7f, 0xa5, 0x68,
 * 0x7a, 0xc7, 0x30, 0xe4, 0x65, 0xab, 0x1a, 0xb5,
 * 0xc2, 0x38, 0xcf, 0x6f, 0x27, 0x29, 0x88, 0x39,
 * 0xfd, 0x07, 0xaf, 0xba, 0x54, 0xa6, 0xb0, 0x0a,
 * [Handshake]: server authenticate client done
 * receive license number: 1000
 * 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xe8,
 * NN model protection is available
 * @endcode
 *
 * @subsubsection approve_account 2.2.4 Approve an Account
 * There are two approaches to approve an account: interactive and manual.
 *
 * <b>Approve an Account Interactively</b><br>
 * @code
 * [Login]: user_name (amba_test)
 * [Login]: user account does NOT exist
 *
 * [Register]: new user (amba_test), approve('y' or 'Y') or not?
 * @endcode
 *
 * Type <b>“y + ENTER”</b> to approve.
 * Next, specify the “granted license number” and the “metadata index” for this account to complete registration.  The console displays this account’s settings, as shown below.
 *
 * @code
 * [Register]: grant number of license for new user (amba_test):
 * 1000
 * [Register]: granted license number: 1000
 * [Register]: specify metadata index for new user (amba_test):
 * 0
 * [Register]: specified metadata index: 0
 * [Register]: add user (amba_test) into db done
 * [Register]: send status code done
 * @endcode
 *
 * @anchor Approve_an_Account_Interactively
 * <b>Approve an Account Interactively</b><br>
 *
 * After a new account is registered on the server side, the following prompt appears:
 * @code
 * [Login]: user_name (amba_test)
 * [Login]: user account does NOT exist
 *
 * [Register]: new user (amba_test), approve('y' or 'Y') or not?
 * @endcode
 *
 * Type “y + ENTER” to approve.
 * Next, specify the “granted license number” and the “metadata index” for this account to complete registration.  The console will display this account’s settings, as follows.
 *
 * @code
 * [Register]: grant number of license for new user (amba_test):
 * 1000
 * [Register]: granted license number: 1000
 * [Register]: specify metadata index for new user (amba_test):
 * 0
 * [Register]: specified metadata index: 0
 * [Register]: add user (amba_test) into db done
 * [Register]: send status code done
 * @endcode
 *
 * @anchor Approve_an_Account_Manually
 * <b>Approve an Account Manually</b><br>
 *
 * -# Go to the database directory of the license server.
 * @code
 * build $
 * cd $(SDK)/ambarella/security/build/ulp_nmp_license_server/db/
 * @endcode
 *
 * -# Create a new `dir`.  The `.dir` name is the account name.
 * @code
 * build $ mkdir zhe
 * @endcode
 *
 * -# Copy the account’s public key file to this folder.  Then, create two new text files: one is for the total license number (`total_license_num.txt`), and the other for the metadata index (`metadata_ index.txt`).  The files are as shown below.
 * @code
 * -rw-rw-r-- 1 zhe zhe    1 7月   8 19:35 metadata_index.txt
 * -rw-rw-r-- 1 zhe zhe   32 7月   8 19:35 pub_cli.bin
 * -rw-rw-r-- 1 zhe zhe    5 7月   8 19:35 total_license_num.txt
 * @endcode
 *
 * Those two text files contain one digital number, so the user can edit the number as required.  For example, `total_license_num.txt` has a digital number of 10000, and
 * `metadata_index.txt` has a digital number of 0.
 * After this process is complete, restart the license server program.
 *
 * @subsubsection run_provision_tool_to_deploy_license 2.2.5 Run the Provisioning Tool to Deploy the License
 * By default, the IP address of the device is 10.0.0.2.  Once `ulp_nmp_pt_activate` is running, the deployment tool connects to it via `device_url:device_port` in the `.lc` file.
 * To prepare for the running of the provisioning tool (PT), users must copy `ambarella/security/build/ulp_nmp_simulate_device` to `DEVICE_PATH`.  Then, the provisioning tool can
 * run on the device.
 *
 * <b>PT Tool by CVflow</b>
 * @code
 * init.sh --na
 * modprobe cavalry
 * cavalry_load -f /lib/firmware/cavalry.bin -r
 * test_encode --idle 	--nopreview
 * ulp_nmp_pt_activate $(DEVICE_PATH)/lc_configs/pt_cvflow.lc
 * @endcode
 * After activation, `pub_dik_cvflow.bin` and `unit_license_cvflow.bin` are generated.  For this chip, `unit_license_cvflow.bin` is the unit license.
 *
 * <b>PT Tool by CV0 Library</b>
 * @code
 * init.sh --na
 * test_encode --idle --nopreview
 * ulp_nmp_pt_activate $(DEVICE_PATH)/lc_configs/pt_cv0.lc
 * @endcode
 * 
 * After activation, `pub_dik_cv0.bin` and `unit_license_cv0.bin` are generated.  For this chip, `unit_license_cv0.bin` is the unit license.
 *
 * @subsection run_sample_code_to_check_license 2.3 Run Sample Code to Check the License
 * To prepare for the running of the provisioning tool, users must copy `ambarella/security/build/ulp_nmp_simulate_device` to `DEVICE_PATH`.  Then, the provisioning tool can run
 * on the device.
 *
 * <b>PT Tool by CVflow</b>
 * @code
 * init.sh --na
 * modprobe cavalry
 * cavalry_load -f /lib/firmware/cavalry.bin -r
 * test_encode --idle --nopreview
 * ulp_nmp_pt_check_license $(DEVICE_PATH)/lc_configs/pt_cvflow.lc
 * @endcode
 * `ulp_nmp_pt_check_license` reports the check license result.
 *
 * <b>PT Tool by CV0 Library</b>
 * @code
 * init.sh --na
 * test_encode --idle --nopreview
 * ulp_nmp_pt_check_license $(DEVICE_PATH)/lc_configs/pt_cv0.lc
 * init.sh --na
 * test_encode --idle --nopreview
 * ulp_nmp_pt_check_license $(DEVICE_PATH)/lc_configs/pt_cv0.lc
 * @endcode
 * `ulp_nmp_pt_check_license` reports the check license result.
 *
 * @note
 * The software vendor must integrate this check code into the software.
 * The function call (thiz->platform.verify_license) checks the Cvflow- / CV0 library-returned response and checks the response’s signatures.  Note that the random challenge is
 * created by an RNG so as to prevent a replay attack.
 *
 * @subsection quick_launch_user_guide 2.4 Quick Launch User Guide
 * ULP-related components include the license server, the deployment tool, and the provisioning tools on the device.  The following sections describe how to proceed with setting
 * up and using the pre-set test files.
 * Users can also refer to the help file located at `$(SDK)/ambarella/security/ulp_nmp/doc/ulp_quick_launch_steps.txt`.
 *
 * @note
 * The process in this chapter copies the pre-set keys and certificates to the `server/deployment_tool/provisioning_tool` location; therefore, it will replace the existing keys
 * and certificates.  If those existing keys and certificates are required, back them up first.  Otherwise, those replaced keys and certificates will be lost.
 *
 * @subsubsection compille_and_install_pre_set_test_fille 2.4.1 Compile and Install the Pre-Set Test Files
 * Go to the source code location, compile it, and install it together with the pre-set test files.
 * @code
 * build $ cd $(SDK)/ambarella/security/ulp_nmp
 * build $ make && make install
 * build $ make install_preset_test_files
 * @endcode
 *
 * @subsubsection launch_license_server 2.4.2 Launch the License Server
 * Go to the license server’s location and launch the server.
 * @code
 * build $
 * cd $(SDK)/ambarella/security/build/ulp_nmp_license_server/
 * @endcode
 *
 * By CVflow:
 * @code
 * build $ ./ulp_nmp_license_server lc_configs/ulp_license_svr_cvflow.lc
 * @endcode
 *
 * By CV0 library:
 * @code
 * build $ ./ulp_nmp_license_server lc_configs/ulp_license_svr_cv0.lc
 * @endcode
 *
 * After entering the correct passphrases for the private server key, the private VLK key, and PEK, the server begins running.
 *
 * @subsubsection launch_dev_tool 2.4.3 Launch the Deployment Tool
 * Go to the following location to launch the deployment tool.
 * @code
 * build $ cd ambarella/security/build/ulp_nmp_deployment_tool/
 * build $ ./ulp_nmp_deployment_tool lc_configs/ulp_nmp_deployment_tool.lc
 * @endcode
 *
 * @note
 * Users must specify the correct license server IP address and port in `ulp_nmp_deployment_tool.lc`.
 *
 * The deployment tool then prompts the user to enter the client’s private key passphrase.  This key is the identity key for clients (vendor’s customer).
 * @code
 * new_ssl_client_ctx done
 * load vlk done
 * Enter cli priv's passphrase:
 * @endcode
 *
 * After entering the private key’s passphrase (<b>“1234 + ENTER”</b>), the deployment tool begins.
 *
 * @subsubsection approve_account 2.4.4 Approve an Account
 * There are two approaches for approving an account: interactive and manual.
 *
 * @anchor Approve_Account_Interactively
 * <b>Approve an Account Interactively</b><br>
 *
 * After a new account is registered on the server side, the following prompt appears:
 * @code
 * [Login]: user_name (amba_test)
 * [Login]: user account does NOT exist
 *
 * [Register]: new user (amba_test), approve('y' or 'Y') or not?
 * @endcode
 *
 * Type <b>“y + ENTER”</b> to approve.
 * Next, specify the granted license number and the metadata index in order for this account to complete the registration.  The console will display this account’s settings, as
 * shown below.
 *
 * @code
 * [Register]: grant number of license for new user (amba_test):
 * 1000
 * [Register]: granted license number: 1000
 * [Register]: specify metadata index for new user (amba_test):
 * 0
 * [Register]: specified metadata index: 0
 * [Register]: add user (amba_test) into db done
 * [Register]: send status code done
 * @endcode
 *
 * @anchor Approve_Account_Manually
 * <b>Approve an Account Manually</b><br>
 *
 * Go to the database directory of the license server.
 * @code
 * build $
 * cd $(SDK)/ambarella/security/build/ulp_nmp_license_server/db/
 * @endcode
 * Make a new dir.  The dir name is the account name.
 * @code
 * build $ mkdir amba_test
 * @endcode
 *
 * Copy the account’s public key file to this folder and create two new text files: one is for the total license number `total_license_num.txt` , and the other is for the metadata
 * index `metadata_index.txt`.  The files are as shown below.
 * -rw-rw-r-- 1 amba_test amba_test    1 JUN   8 19:35 metadata_index.txt
 * -rw-rw-r-- 1 amba_test amba_test   32 JUN   8 19:35 pub_cli.bin
 * -rw-rw-r-- 1 amba_test amba_test    5 JUN   8 19:35 total_license_num.txt
 *
 * Those two text files only contain one digital number, so the user can edit the number as required.  For example, `total_license_num.txt` has a digital number of 10000 and
 * `metadata_index.txt` has a digital number of 0.
 *
 * @subsubsection run_provision_tool_to_deplloy_license 2.4.5 Run the Provisioning Tool to Deploy the License
 * Refer to @ref run_provision_tool_to_deploy_license for more information.
 *
 * @subsubsection run_sample_code_to_check_the_license 2.4.6 Run the Sample Code to Check the License
 * Refer to @ref run_sample_code_to_check_license for more information.
 *
 * @subsection config_for_programs_and_database 2.5 Configurations for Programs and the Database
 *
 * @subsubsection license_server_config 2.5.1 License Server Configuration
 * The location of the configuration file for the license server is as follows:
 * `$(SDK)/ambarella/security/ulp_nmp/license_server/lc_configs/ulp_license_svr_cvflow.lc` or `ulp_license_svr_cv0.lc`
 * 
 * @code
 * ULP_NMP_LicenseServer
 *  Config
 *   nn_model_protection = 0
 *   debug_log = 1
 *   listen_port = 19000
 *   db_path = db
 *   priv_ca_pem = ./keys/priv_ca.pem
 *   ca_crt = ./certs/ca.crt
 *   server_crt = ./certs/server.crt
 *   priv_svr_pem = ./keys/priv_svr.pem
 *   pub_cli_bin = pub_cli.bin
 *   cli_total_license_num = total_license_num.txt
 *   cli_metadata_index = metadata_index.txt
 *   priv_vlk_enc = ./keys/priv_vlk_enc.bin
 *   priv_vlk_enc_shadow = ./keys/priv_vlk_enc.shadow
 *   pub_vlk = ./keys/pub_vlk.bin
 *   license_cert = ./certs/license_cert.bin
 * @endcode
 *
 * The following describes each field:
 * - nn_model_protection: NMP is enabled or disabled.  If users only require a per-unit license, this field is disabled
 * - debug_log: if set to 1, it will print the debug information
 * - listen_port: the listening TCP port
 * - db_path: the database path
 * - priv_ca_pem: the CA private key that signs the CA certificate
 * - ca_crt: the CA certificate, in X509 format.  The CA certificate is the root certificate of a CoT
 * - server_crt: the server certificate, in X509 format.  The server certificate is signed by the CA
 * - priv_svr_pem: the server private key.  The server’s public key is inside the server certificate
 * - pub_cli_bin: each client’s (account) public key file name in the database
 * - cli_total_license_num: each client’s (account) license total number file name in the database
 * - cli_metadata_index: each client’s (account) metadata index file name in the database
 * - priv_vlk_enc: the private VLK file in encrypted form
 * - priv_vlk_enc_shadow: the private VLK file’s passphrase shadow file
 * - pub_vlk: the public VLK file
 * - license_cert: the license certificate from Ambarella in binary format
 *
 * @subsubsection deployment_tool_config 2.5.2 Deployment Tool Configuration
 * The location of the configuration file for the license server is `$(SDK)/ambarella/security/ulp_nmp/deployment_tool/lc_configs/ulp_nmp_deployment_tool.lc`.
 *
 * @code
 * ULP_NMP_DeploymentTool
 *  Config
 *   debug_log = 1
 *   remote_url = localhost
 *   remote_port = 19000
 *   device_url = 10.0.0.2
 *   device_port = 9292
 *   ca_crt = ./certs/ca.crt
 *   pub_vlk = ./keys/pub_vlk.bin
 *   priv_cli_enc_bin = ./keys/priv_cli_enc.bin
 *   pub_cli_bin = ./keys/pub_cli.bin
 * @endcode
 *
 * The following describes each field.
 * - debug_log: if set to 1, it will print the debug information
 * - remote_url: the license server’s URL or IP address
 * - remote_port: the license server’s TCP port
 * - device_url: the device’s IP address
 * - device_port: the device’s TCP port
 * - ca_crt: the CA certificate, in X509 format.  The CA certificate includes a CA’s public key
 * - pub_vlk: the public VLK key
 * - priv_cli_enc_bin: the client’s (account) private key in encrypted form
 * - pub_cli_bin: the client’s (account) public key
 *
 * @subsubsection provisioning_tool_config 2.5.3 Provisioning Tool Configuration
 * The provisioning tool includes `ulp_nmp_pt_activate` and `ulp_nmp_pt_check_license`.
 * The location of the configuration file for the provisioning tool is `$(SDK)/ambarella/security/ulp_nmp/provisioning_tool/lc_configs/pt_cvflow.lc` or `pt_cv0.lc`.
 * 
 * @code
 * ULP_NMP_ProvisioningTool
 *  Config
 *   debug_log = 1
 *   listen_port = 9292
 *   license_cert = license_cert.bin
 *   platform = cvflow
 *   unique_id_file = cavalry_pub_dik.bin
 *   unit_license_file = unit_license_cavalry.bin
 *   dek_encrypt_pek_file = dev_encrypt_pek.bin
 *   digest_file = dev_encrypt_pek.digest
 * @endcode
 *
 * The following describes each field:
 * - debug_log: if set to 1, it will print the debug information
 * - listen_port: the device’s listening port (TCP)
 * - license_cert: the license certificate
 * - platform: CVflow or CV0; this is the field to choose from the CVflow or CV0 library approach
 * - unique_id_file: the unique ID file
 * - unit_license_file: the unit license file
 * - dek_encrypt_pek_file: the DEK encrypt PEK file
 * - digest_file: the digest file
 *
 * @subsubsection database_config 2.5.4 Database Configuration
 * By default, the database path is under the server’s directory: `$(SDK)/ambarella/security/ build/ulp_nmp_license_server/db`.
 *
 * @note
 * - Under the database, the first level subdirectory is an account.
 * - Each account’s subdirectory includes three files: `pub_cli.bin`, `metadata_index.txt`, and `total_license_num.txt`.
 * - Users can check and edit the total license number and metadata index for each account.
 * - In addition to the online register / approve account, creating the subdirectory and then placing those three files has the same function as the register / approve account.
 * - When the account starts to activate devices, the account’s subdirectory records each activated device’s information: the unique ID and the unit license file.  Those files are located in the subdirectory of the unique ID.
 *
 * @subsubsection metadata 2.5.5 Metadata
 * The license is a signature of the “unique_id + metadata”.  Metadata is managed by the software vendor; the vendor is able to embed the information into the license as required.
 * Additionally, the license server supports multiple metadata types, so the software vendor is able to apply various types of metadata for different customers.
 * Typically, metadata is used by the vendor to identify the unit license’s capability.  Different price points receive different services.
 * It is easy for vendors to modify the metadata definition in the source code; check `metadata.c` at the license server.
 * The `metadata.c` is a reference implementation of eight metadata.
 *
 * @subsection offline_issuer 2.6 Offline Issuer
 * If users are not required to use the license server to distribute (issue) a license, they can issue a license manually using an offline approach.
 * For additional help, refer to `$(SDK)/ambarella/security/ulp_nmp/doc/ offline_issuer_steps.txt`.
 * 
 * Go to the offline issuer location:
 * @code
 * build $ cd ambarella/security/build/ulp_nmp_license_server/
 * @endcode
 * 
 * Offline issuer command:
 * @code
 * build $ ./ulp_nmp_offline_issuer lc_configs/ulp_nmp_license_svr.lc <uid_file> <meta index> <unit license file>
 * @endcode
 * 
 * The parameters of the `ulp_nmp_offline_issuer` are described below:
 * - <uid_file>: the `cavalry_pub_dik.bin` from the target device (chip)
 * - <meta index>: the index of the metadata
 * - <unit license file>: the unit license file to issue a license for the device
 *
 * The process is as follows:
 * -# Obtain pub_dik_cvflow.bin or public_dik_cv0 from the target device (chip).
 * -# Use the offline tool to generate the license manually.
 * -# Deploy the license file to the device (unit_license_cvflow.bin or unit_license_cv0.bin)
 *
 * @section neural_network_model_protection 3. Neural Network Model Protection
 * NMP protects NN models on Ambarella chips.  The NN model in NAND and in memory are in encrypted forms.  When enabling NMP, CVflow loads the encrypted model, decrypts it, and
 * then executes it.
 * There is a secure channel for the vendor server to transfer the model’s encryption key to CVflow in the deployment stage.  CVflow re-encrypts the model key and stores it in
 * NAND.
 *
 * @subsection NN_model_protection 3.1 NN Model Protection
 * The NN model exists in encrypted form on the Linux side.  Then, when it is loaded into CVflow, it is decrypted and executed.
 * @anchor NN_Model_Protection_Concept
 * @image html nn_model_protection_concept.png "Figure 3.1 NN Model Protection Concept."
 *
 * @subsection deployment_process 3.2 Deployment Process
 * The primary objective of NMP is to protect the model encryption keys.  There are two main keys: PEK and DEK.  The PEK, generated by the vendor, is used to encrypt the NN model
 * within a software release package.  It is the vendor’s responsibility to keep the PEK confidential.  DEK is used to encrypt the PEK on the device.  The DEK is unique for each
 * chip and can only be accessed by CVflow.  When CVflow receives the PEK, it decrypts and re-encrypts the PEK with the DEK; then, the re-encrypted PEK is stored back to the file
 * system.
 * A major design target of the deployment process is the secure distribution of the PEK to CVflow.  The Ambarella SDK uses X25519 for key exchange, in addition to ED25519 for
 * identity authentication, in order to set up a secure channel between the software vendor’s server and CVflow.  To enhance the security level, the sample code in the SDK uses
 * a bi-directional authenticated TLS for internet communication.   The two cryptography layers of defense include TLS (RSA / ECDSA + DH / ECDH) and ED25519 + X25519.
 * The deployment process is typically used in conjunction with “unit license” distribution.  For unit license protection, refer to @ref ulp.
 * @anchor Distributing_the_PEK_in_a_Secure_Channel.
 * @image html distribute_pek_in_secure_channel.png "Figure 3.2 Distributing the PEK in a Secure Channel."
 *
 * @subsection online_upgrade_process 3.3 Online Upgrade Process
 * If the vendor’s PEK remains the same, the online upgrade is the same as the plaintext NN model upgrade.  Additionally, if the PEK does not change, the DEK-encrypted PEK is not
 * required to change.
 * However, if the PEK changes, the device can re-trigger a new key exchange for the new PEK; CVflow then re-encrypts the new PEK and stores it back on the Linux side.
 * @anchor Distributing_the_PEK_in_a_Secure_Channel.
 * @image html distribute_pek_in_secure_channel.png "Figure 3.3 Distributing the PEK in a Secure Channel."
 *
 * @subsection device_working_process 3.4 Device Working Process
 * CVflow loads the encrypted model, along with the encrypted PEK and digest.  CVflow decrypts the PEK first, and then uses the PEK to decrypt the NN model and execute the model.
 * @anchor Device_Working_Process.
 * @image html device_working_process.png "Figure 3.4 Device Working Process."
 *
 * @subsection sw_hierarchy_on_chip 3.5 Software Hierarchy on Chip
 * For green-colored components, the Linux SDK provides the sample code for evaluation.  The software vendor is responsible for their maintenance.
 * @anchor Software_Hierarchy_on_Chip.
 * @image html fig_sw_hierarchy_on_chip.png "Figure 3.5 Software Hierarchy on Chip."
 *
 * @subsection sw_hierarchy_on_pc 3.6 Software Hierarchy on Linux PC
 * For green-colored components in the following image, the Linux SDK provides the sample code for evaluation.  The software vendor is responsible for their maintenance.
 * @anchor Software_Hierarchy_on_PC.
 * @image html fig_sw_hierarchy_on_pc.png "Figure 3.6 Software Hierarchy on PC."
 *
 * @subsection support_muti_customers 3.7 Support Multiple Customers
 * Each software vendor can support multiple customers.  Additionally, the license server and upgrade server can manage transactions in parallel, as shown below.
 * @anchor Muti_Customer_Support
 * @image html muti_customer_support.png "Figure 3.7 Multi-Customer Support."
 *
 * @section neural_network_model_protections_user_guide 4. Neural Network Model Protection User Guide
 * @subsection compile_nn_model_protection_code 4.1 Compile NN Model Protection Sample Code
 * Users can compile the Ambarella NN model protection sample code on the SoC and on the Linux (Ubuntu) platform.  Refer to the following to compile the sample code.
 *
 * @subsubsection compile_nmp_sample_code_on_soc 4.1.1 Compile Sample Code on the SoC
 * Select `menuconfig` below.
 *
 * <B>Amba build:</B>
 * @code
 *   security  --->
 *    ulp-nmp (security/ulp_nmp)
 *     ULP and NMP by CVflow
 * @endcode
 * The provisioning tools (`ulp_nmp_pt_activate`) are under `/usr/local/bin/` on the SoC.
 *
 * <B>Yocto build:</B>
 * @code
 * -> meta-ambasecurity  --->
 *  -> recipes-ulpnmp  --->
 *   -> ulpnmp (meta-ambasecurity/recipes-ulpnmp/ulpnmp)  --->
 *    -> ulpnmp (meta-ambasecurity/recipes-ulpnmp/ulpnmp)
 *     -> ULP and NMP by CVflow
 * @endcode
 *
 * @subsubsection compile_nmp_sample_code_on_linux 4.1.2 Compile Sample Code on Linux (Ubuntu)
 * Go to the source code location and compile.
 * @code
 * cd $(SDK)/ambarella/security/ulp_nmp
 * make && make install && make install_configs
 * @endcode
 *
 * The servers and tools are placed on `$(SDK)/ambarella/security/build/`.
 *
 * @subsection derive_pek_and_enc_model 4.2 Derive the PEK and Encrypt Model
 * For a encrypted NN model with PEK, users can also refer to `$(SDK)/ambarella/security/ ulp_nmp/doc/derive_pek_and_encrypt_model.txt`.
 *
 * @subsubsection dervie_pek 4.2.1 Derive the PEK
 * Go to the following license server location:
 * @code
 * build $ cd ambarella/security/build/ulp_nmp_license_server
 * @endcode
 *
 * Generate the PEK if it is not yet generated.  If PEK is already generated, re-generation is not required.
 * @code
 * build $ ../ulp_nmp_key_tool/ulp_nmp_key_tool --gen-aesctr pek --path ./keys/ --passphrase 1234
 * @endcode
 *
 * Decrypt the PEK:
 * @code
 * build $ ../ulp_nmp_key_tool/ulp_nmp_key_tool --decrypt ./keys/pek_enc.bin ./keys/pek.bin --shadow ./keys/pek_enc.shadow --passphrase 1234
 * ./keys/pek_enc.bin is the encrypted form of the PEK, and ./keys/pek.bin is the PEK; users should use pek.bin for model encryption.
 * @endcode
 *
 * @subsection enc_model_with_pek 4.2.2 Encrypt Model with PEK
 * Encrypt the model via the PEK:
 * @code
 * build $ cavalry_gen -d vas_output -k pek.bin -f net_enc.bin
 * @endcode
 *
 * For more information about Cavalry generation and `vas_output`, refer to the related CVflow documents.
 * 
 * Show model encryption status:
 * @code
 * BOARD# test_nnctrl -b net_enc.bin --show-encrypt
 * @endcode
 * 
 * Load the encrypted model and execute:
 * @code
 * BOARD# test_nnctrl -b net_enc.bin --in input=input.bin --out output=out.bin --cert license_cert.bin --key dev_encrypt_pek.bin --digest dev_encrypt_pek.digest
 * @endcode
 * 
 * The `dev_encrpted_pek.bin` and `dev_encrypted_pek.digest` are generated after deployment (device activation).
 * Note that Cavalry must be loaded first on the chip.
 * @code
 * BOARD# init.sh --na
 * BOARD# modprobe cavalry
 * BOARD# cavalry_load -f /lib/firmware/cavalry.bin –r
 * @endcode
 *
 * @subsection nmp_launch_from_scratch_user_guide 4.3 Launch-from-Scratch User Guide
 * Components related to NMP include the license server, the deployment tool, and the provisioning tool on the device.
 * The following sections describe how to launch the license server and tools after compiling and installing the configurations.
 * Users can also refer to the help file located at `$(SDK)/ambarella/security/ulp_nmp/doc/ulp_nmp_from_scratch_steps.txt`.
 * 
 * @note
 * The process in this chapter includes key generation.  It is important that users keep the private key and encryption key confidential, in addition to maintaining a record and
 * backup of the key passphrases, as security of the system is dependent on proper key maintenance.  Moreover, because there is no method for recovering lost or forgotten key files,
 * it is vital that users prioritize key maintence in order to maintain system security.
 *
 * @subsubsection nmp_scratch_compile_and_install_config 4.3.1 Compile and Install Configurations
 * Go to the source code location, then compile and install the configurations.
 * @code
 * build $ cd $(SDK)/ambarella/security/ulp_nmp
 * build $ make && make install && make install_configs
 * @endcode
 *
 * @subsubsection nmp_launch_license_server 4.3.2 Launch the License Server
 * Refer to @ref launch_license_server for more information.
 * Only change the .lc file when launching the server.
 * @code
 * build $ ./ulp_nmp_license_server lc_configs/ulp_nmp_license_svr_cvflow.lc
 * @endcode
 *
 * @subsubsection nmp_launch_deployment_tool 4.3.3 Launch the Deployment Tool
 * Refer to @ref launch_deployment_tool for more information.
 *
 * @subsubsection nmp_approve_account 4.3.4 Approve An Account
 * Refer to @ref approve_account for more information.
 *
 * @subsubsection nmp_run_provisiong_tool_to_deploy_pek 4.3.5 Run the Provisioning Tool to Deploy PEK
 * By default, the IP address of the device is 10.0.0.2.  Once `ulp_nmp_pt_activate` is running, the deployment tool connects to it via `device_url:device_port` in the .lc file.
 * To prepare, copy `ambarella/security/build/ulp_nmp_simulate_device` to `DEVICE_PATH`.  Then, run the provisioning tool on the device.
 * @code
 * init.sh --na
 * modprobe cavalry
 * cavalry_load -f /lib/firmware/cavalry.bin -r
 * test_encode --idle --nopreview
 * ulp_nmp_pt_activate $(DEVICE_PATH)/lc_configs/pt_cvflow.lc
 * @endcode
 *
 * After activation, `pub_dik_cvflow.bin` and `unit_license_cvflow.bin` will be generated; `unit_license_cvflow.bin` is the unit license for this chip.
 * At the same time, a re-encrypted PEK `dev_encrypt_pek.bin` and a digest file `dev_encrypt_ pek.digest` are generated.
 * Those two files are required for CVflow load encrypted modeling and execution.  Refer to @ref enc_model_with_pek for more information.
 *
 * @subsection nmp_quick_launch_user_guide 4.4 Quick-Launch User Guide
 * NMP-related components include the license server, the deployment tool, and the provisioning tools on the device.  The following sections describe how to proceed with setup
 * using the pre-set test files.
 * Users can also refer to the help file located at `$(SDK)/ambarella/security/ulp_nmp/doc/ ulp_nmp_quick_launch_steps.txt`.
 *
 * @note
 * Because the process in this chapter includes copying the pre-set keys and certificates to the `server/deployment_tool/provisioning_tool` location, it will replace the current
 * keys and certificates.  If the current keys and certificates are still required, perform a backup; otherwise, the keys and certificate will be overwritten.
 *
 * @subsubsection nmp_quick_compile_install_preset_test_file 4.4.1 Compile and Install the Pre-Set Test Files
 * Go to the source code location.  Then, compile and install together with the pre-set test files.
 * @code
 * build $ cd $(SDK)/ambarella/security/ulp_nmp
 * build $ make && make install
 * build $ make install_preset_test_files
 * @endcode
 *
 * @subsubsection nmp_quick_launch_license_server 4.4.2 Launch the License Server
 * Refer to @ref launch_license_server for more information.
 * Only change the .lc file when launching the server.
 * @code
 * build $ ./ulp_nmp_license_server lc_configs/ulp_nmp_license_svr_cvflow.lc
 * @endcode
 *
 * @subsubsection nmp_quick_launch_deployment_tool 4.3.3 Launch the Deployment Tool
 * Refer to @ref launch_deployment_tool for more information.
 *
 * @subsubsection nmp_quick_approve_account 4.3.4 Approve An Account
 * Refer to @ref approve_account for more information.
 *
 * @subsubsection nmp_quick_run_provisiong_tool_to_deploy_pek 4.3.5 Run the Provisioning Tool to Deploy PEK
 * Refer to @ref nmp_run_provisiong_tool_to_deploy_pek for more information.
 *
 * @section ulp_nmp_key_tool 5. ULP NMP Key Tools
 * The ULP NMP key tool can be used to generate the AES key `*.bin`, its encrypted form `*_enc.bin`, and the corresponding shadow file `*.shadow`.
 *
 * @subsection change_key_passphrase 5.1 Change Key Passphrase
 * In some cases, users may be required to change the key’s passphrase.  The following examples demonstrate how to change the VLK passphrase, re-encrypt the key (client account
 * key), and generate the corresponding shadow file.
 *
 * <B>Decrypt with Old Passphrase</B>
 * @code
 * ./ulp_nmp_key_tool --decrypt priv_cli_enc.bin priv_cli.bin --passprase 1234 --shadow priv_cli_enc.shadow
 * @endcode
 *
 * <B>Remove Old Encrypted File and Shadow File</B>
 * @code
 * rm priv_cli_enc.shadow -rf
 * rm priv_cli_enc.bin -rf
 * rm pub_cli_enc.bin -rf
 * @endcode
 *
 * <B>Re-Encrypt with New Passphrase</B>
 * @code
 * ./ulp_nmp_key_tool --encrypt priv_cli.bin priv_cli_enc.bin --passphrase 2345 --shadow priv_cli_enc.shadow
 * ./ulp_nmp_key_tool --encrypt pub_cli.bin pub_cli_enc.bin --passphrase 2345 --shadow priv_cli_enc.shadow
 * @endcode
 *
 * <B>Remove the Plaintext Private Key</B>
 * @code
 * rm priv_cli.bin -rf
 * @endcode
 *//*!
 * @file user_privacy_protection.h
 * @brief
 * @version 1.0
 * @date 2023-12-16
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
 * @page user_privacy_protection User Privacy Protection
 * User privacy protection is a production-level concept.  Ambarella’s chips and software development kit (SDK) include essential base functions for user privacy protection.  The
 * Ambarella Flexible Linux SDK supports image / video processing and video content analysis (VCA), which can retrieve information without using personal information.  The secure
 * storage can be used to protect data on the device.  The secure connection prevents information from leaking during the transfer.
 *
 * The recommended principle of the user privacy protection is as follows:
 *  - Personal privacy information remains with the device.  The information is stored in encrypted form with a hardware-planted key, and is never exposed to the external world.  As a result, only the device retains the key
 *  - Only the information without privacy can be transferred to the cloud server.  The transfer process is performed via a secure connection with bi-directional authentication
 *//*!
 * @file secure_hardware.h
 * @brief
 * @version 1.0
 * @date 2023-12-17
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
 * @page secure_hardware Secure Hardware
 *
 * @section otp_history 0. Revision History
 * <table>
 * <caption id="secure_hardware_history"></caption>
 * <tr><th>Version<th> Updated Date<th align="left"> Modification
 * <tr><td>0.0.1<td>20231217<td> Initial Version
 * </table>
 *
 * @section otp 1. One-Time Programmable
 * One-time programmable (OTP) is a hardware component inside the CV5x / CV7x / CV3 system on chip (SoC).  The total size of OTP is 8 KB.
 * 
 * - - - -
 *
 * @subsection otp_layout 1.1. OTP Data Layout
 *
 * OTP can be programmed only once; if programmed incorrectly, the chip will become unusable.
 * Ambarella's OTP has 32768 bits.  The layout of OTP is divided into two sections: the Ambarella-defined sections, which comprises the first 16128 bits, and the user-defined
 * sections, which comprises the remainder.
 * The following table displays the properties of the Ambarella-defined OTP.
 *
 * <table>
 * <caption id="otp_data_layout">Table 1-1. OTP Data Layout.</caption>
 * <tr><th align="left">No.<th align="left">Bit Address (DEC)<th align="left">Bit Address (HEX)<th align="left">Bits<th align="left">OTP Function<th align="left">Lock Bit
 * <tr><td>1<td>0 - 63<td>0x0000 - 0x003F<td>64<td>Reserved by Ambarella<td>Lock bit 0
 * <tr><td>2<td>64 - 86<td>0x0040 - 0x0056<td>23<td>sys_config<td rowspan="9">Lock bit 3
 * <tr><td>3<td>87 - 92<td>0x0057 - 0x005C<td>6<td>unused
 * <tr><td>4<td>93 - 93<td>0x005D -0x005D<td>1<td>sys_config
 * <tr><td>5<td>94 - 95<td>0x005E -0x005F<td>2<td>sys_config
 * <tr><td>6<td>96 - 118<td>0x0060 - 0x0076<td>23<td>sys_config
 * <tr><td>7<td>119 - 124<td>0x0077 - 0x007C<td>6<td>unused
 * <tr><td>8<td>125 - 125<td>0x007D - 0x007D<td>1<td>sys_config
 * <tr><td>9<td>126 - 126<td>0x007F - 0x007E<td>1<td>sys_config
 * <tr><td>19<td>127 - 127<td>0x007F - 0x007F<td>1<td>efuse_disable_jtag
 * <tr><td>11<td>128 - 191<td>0x0080 - 0x00BF<td>64<td>Reserved by Ambarella<td>Lock bit 2
 * <tr><td>12<td>192 - 223<td>0x00C0 - 0x00DF<td>32<td>write_lock<td>No lock
 * <tr><td>13<td>224 - 255<td>0x00E0 - 0x00FF<td>32<td>cst_seed<td>Lock bit 4
 * <tr><td>14<td>256 - 383<td>0x0100 - 0x017F<td>128<td>Unique ID<td>Lock bit 1
 * <tr><td>15<td>384 - 511<td>0x0180 - 0x01FF<td>128<td>cst_cuk<td>Lock bit 4
 * <tr><td>16<td>512 - 767<td>0x0200 - 0x02FF<td>256<td>Reserved by Ambarella<td rowspan="2">Lock bit 0
 * <tr><td>17<td>768 - 15999<td>0x0300 - 0x3E7F<td>15232<td>Reserved by Ambarella
 * <tr><td>18<td>16000 - 16015<td>0x3E80 - 0x3E8F<td>16<td>data_invalid<td rowspan="5">No lock
 * <tr><td>19<td>16016 - 16016<td>0x3E90 - 0x3E90<td>1<td>anti_rollback_en
 * <tr><td>20<td>16017 - 16017<td>0x3E91 - 0x3E91<td>1<td>secure_usb_boot_disable
 * <tr><td>21<td>16018 - 16031<td>0x3E92 - 0x3E9F<td>14<td>misc_config
 * <tr><td>22<td>16032 - 16127<td>0x3EA0 - 0x3EFF<td>96<td>bst_ver_cnt
 * <tr><td>23<td>16128 - 16255<td>0x3F00 - 0x3F7F<td>128<td>serial_number<td>Lock bit 5
 * <tr><td>24<td>16256 - 16383<td>0x3F00 - 0x3FFF<td>128<td>OTP_TEST<td>Lock bit 6
 * <tr><td>25<td>16384 - 16639<td>0x4000 - 0x40FF<td>256<td>HUK<td>Lock bit 11
 * <tr><td>26<td>16640 - 16895<td>0x4100 - 0x41FF<td>256<td>USER_CUK<td>Lock bit 12
 * <tr><td>27<td>16896 - 17151<td>0x4200 - 0x42FF<td>256<td>AES_KEY_0<td>Lock bit 13
 * <tr><td>28<td>17152 - 17407<td>0x4300 - 0x43FF<td>256<td>AES_KEY_1<td>Lock bit 14
 * <tr><td>29<td>16408 - 17663<td>0x4400 - 0x44FF<td>256<td>AES_KEY_2<td>Lock bit 15
 * <tr><td>30<td>16664 - 17919<td>0x4500 - 0x45FF<td>256<td>AES_KEY_3<td>Lock bit 16
 * <tr><td>31<td>17920 - 18175<td>0x4600 - 0x46FF<td>256<td>ECC_KEY_0<td>Lock bit 17
 * <tr><td>32<td>18176 - 18431<td>0x4700 - 0x47FF<td>256<td>ECC_KEY_1<td>Lock bit 18
 * <tr><td>33<td>18432 - 18687<td>0x4800 - 0x48FF<td>256<td>ECC_KEY_2<td>Lock bit 19
 * <tr><td>34<td>18688 - 18943<td>0x4900 - 0x49FF<td>256<td>ECC_KEY_3<td>Lock bit 20
 * <tr><td>35<td>18944 - 19199<td>0x4A00 - 0x4AFF<td>256<td>USER_SLOT_0<td>Lock bit 21
 * <tr><td>36<td>19200 - 19455<td>0x4B00 - 0x4BFF<td>256<td>USER_SLOT_1<td>Lock bit 22
 * <tr><td>37<td>19456 - 19711<td>0x4C00 - 0x4CFF<td>256<td>USER_SLOT_2<td>Lock bit 23
 * <tr><td>38<td>19712 - 19967<td>0x4D00 - 0x4DFF<td>256<td>USER_SLOT_3<td>Lock bit 24
 * <tr><td>39<td>19968 - 20223<td>0x4E00 - 0x4EFF<td>256<td>USER_SLOT_4<td>Lock bit 25
 * <tr><td>40<td>20224 - 20479<td>0x4F00 - 0x4FFF<td>256<td>USER_SLOT_5<td>Lock bit 26
 * <tr><td>41<td>20480 - 20735<td>0x5000 - 0x50FF<td>256<td>ROT_KEY_0<td rowspan="16">Lock bit 8
 * <tr><td>42<td>20736 - 20991<td>0x5100 - 0x51FF<td>256<td>ROT_KEY_1
 * <tr><td>43<td>20736 - 20991<td>0x5200 - 0x52FF<td>256<td>ROT_KEY_2
 * <tr><td>44<td>20992 - 21503<td>0x5300 - 0x53FF<td>256<td>ROT_KEY_3
 * <tr><td>45<td>21504 - 21759<td>0x5400 - 0x54FF<td>256<td>ROT_KEY_4
 * <tr><td>46<td>21760 - 22015<td>0x5500 - 0x55FF<td>256<td>ROT_KEY_5
 * <tr><td>47<td>22016 - 22271<td>0x5600 - 0x56FF<td>256<td>ROT_KEY_6
 * <tr><td>48<td>22272 - 22527<td>0x5700 - 0x57FF<td>256<td>ROT_KEY_7
 * <tr><td>49<td>22528 - 22783<td>0x5800 - 0x58FF<td>256<td>ROT_KEY_8
 * <tr><td>50<td>22784 - 23039<td>0x5900 - 0x59FF<td>256<td>ROT_KEY_9
 * <tr><td>51<td>23040 - 23295<td>0x5A00 - 0x5AFF<td>256<td>ROT_KEY_10
 * <tr><td>52<td>23296 - 23551<td>0x5B00 - 0x5BFF<td>256<td>ROT_KEY_11
 * <tr><td>53<td>23552 - 23807<td>0x5C00 - 0x5CFF<td>256<td>ROT_KEY_12
 * <tr><td>54<td>23808 - 24063<td>0x5D00 - 0x5DFF<td>256<td>ROT_KEY_13
 * <tr><td>55<td>24064 - 24319<td>0x5E00 - 0x5EFF<td>256<td>ROT_KEY_14
 * <tr><td>56<td>24320 - 24575<td>0x5F00 - 0x5FFF<td>256<td>ROT_KEY_15
 * <tr><td>57<td>24576 - 24831<td>0x6000 - 0x60FF<td>256<td>MONO_COUNT_0<td rowspan="6">No lock
 * <tr><td>58<td>24832 - 25087<td>0x6100 - 0x61FF<td>256<td>MONO_COUNT_1
 * <tr><td>59<td>25088 - 25599<td>0x6200 - 0x63FF<td>512<td>MONO_COUNT_2
 * <tr><td>60<td>25600 - 26623<td>0x6400 - 0x67FF<td>1024<td>USER_DATA_0
 * <tr><td>61<td>26624 - 27647<td>0x6800 - 0x6BFF<td>1024<td>USER_DATA_1
 * <tr><td>62<td>27648 - 28671<td>0x6C00 - 0x6FFF<td>1024<td>USER_DATA_2
 * <tr><td>63<td>28672 - 29695<td>0x7000 - 0x73FF<td>1024<td>USER_SLOT_6<td>Lock bit 27
 * <tr><td>64<td>29696 - 30719<td>0x7400 - 0x77FF<td>1024<td>USER_SLOT_7<td>Lock bit 28
 * <tr><td>65<td>30720 - 31743<td>0x7800 - 0x7BFF<td>1024<td>USER_SLOT_8<td>Lock bit 29
 * <tr><td>66<td>31744 - 32767<td>0x7C00 - 0x7FFF<td>1024<td>USER_SLOT_9<td>Lock bit 30
 * </table>
 *
 * - - - -
 *
 * @subsection program_otp 1.2. Program OTP
 *
 * The Ambarella software development kit (SDK) supports programming OTP with or without a trusted operating system (TOS), such as the open programmable trusted execution 
 * environment (OP-TEE).
 * When there is a TOS, use `test_program_otp`.  When there is no TOS, use `test_otp`.
 * The `test_program_otp` includes the client application (CA) and the pseudo trusted application (PTA) to program / read the OTP:
 *  - CA: `SDK/external/tee/optee_test/host/test_program_otp.c`
 *  - PTA: `SDK/external/tee/optee_os/core/arch/arm/pta/pta_ambarella_otp.c`
 *
 * Below are `test_program_otp` options:
 * @code
 * --writepubkey [%%d] [%%s] [%%d]': '--writepubkey' writes (%%d'th) the root of trust (RoT) public key (file name %%s) and locks (%%d)\n
 * --readpubkey [%%d]': '--readpubkey' reads (%%d'th) the RoT public key
 * --readpubkeydigest [%%d]': '--readpubkeydigest' reads (%%d'th) the RoT public key's digest
 * --readambauniqueid: reads the Ambarella-unique ID
 * --readmonocounter [%%d]': reads the mono counter, (%%d'th counter)
 * --increasemonocounter [%%d]': increases the mono counter, (%%d'th counter)
 * --writecustomeruid [%%s] [%%d]': writes the customer ID (file name %%s) (lock or not %%d)
 * --readcustomeruid': reads the customer ID
 * --permanentlyenablesecureboot': permanently enables secure boot
 * --generatehuk': generates the hardware-unique encryption key
 * --writeaeskey [%%d] [%%d]': '--writeaeskey' writes (%%d'th) the advanced encryption standard (AES) key, (lock or not %%d)
 * --writeecckey [%%d] [%%d]': '--writeecckey' writes (%%d'th) the elliptic curve cryptography (key), (lock or not %%d)
 * --writeusrslotg0 [%%d] [%%s] [%%d]': '--writeusrslotg0' writes (%%d'th) usr slot g0 (file name %%s), (lock or not %%d)
 * --readusrslotg0 [%%d]': '--readusrslotg0' reads (%%d'th) the usr slot g0 region
 * --writehex2usrslotg0 [%%d] [%%s]': '--writehex2usrslotg0' writes (%%d'th) usr slot g0 with a hex string
 * --writeusrslotg1 [%%d] [%%s] [%%d]': '--writeusrslotg1' writes (%%d'th) usr slot g1 (file name %%s), (lock or not %%d)
 * --readusrslotg1 [%%d]': '--readusrslotg1' reads (%%d'th) the usr slot g1 region
 * --writehex2usrslotg1 [%%d] [%%s]': '--writehex2usrslotg1' writes (%%d'th) usr slot g1 with a hex string
 * --writetestregion [%%s] [%%d]': '--writetestregion' writes the test region (file name %%s), (lock or not %%d)
 * --readtestregion': '--readtestregion' reads the test region
 * --writehex2testregion [%%s]': '--writehex2testregion' writes the test region with a hex string
 * --revokekey [%%d]': '--revokekey' revoke (%%d'th) the key
 * --queryotpsetting': '--queryotpsetting' queries the OTP setting
 * --setjtagefuse': '--setjtagefuse' will sets the JTAG eFUSE bit
 * --writesysconfig [%%x] [%%x] [%%d]': '--writesysconfig' writes sysconfig; the first is sysconfig, the second is sysconfig_mask, the last is lock
 * --querysysconfig': '--querysysconfig' queries sysconfig
 * --writemiscconfig [%%x]': '--writemiscconfig' writes miscellaneous configurations; the parameter is misc config
 * --querymiscconfig': '--querymiscconfig' queries misc config
 * --writecstseedcuk': '--writecstseedcuk' writes the customer-planted seed and CUK
 * --querycstseed': '--querycstseed' queries the customer-planted seed
 * --querycstcuk': '--querycstcuk' queries the customer-planted CUK
 * --writeusrcuk': '--writeusrcuk' writes the user-planted CUK
 * --queryusrcuk': '--queryusrcuk' queries the user-planted CUK
 * --increasebstver': '--increasebstver' increases the BST version
 * --querybstver': '--querybstver' queries the BST version
    //printf("\t'--enantirollback': '--enantirollback' enables BST anti-rollback
 * --dissecureusbboot': '--dissecureusbboot' disables secure USB boot
 * --lockallrotpubkeys': '--lockallrotpubkeys' locks all RoT public keys
 * --lockzonea': '--lockzonea' locks zone A, include sysconfig
 * --simulate': '--simulate' simulates OTP write; only prints the OTP write address and size.  OTP is not actually written
 * --dailytest [%%d]': '--dailytest' performs a daily test covering all APIs; [%%d] means to try to write one bit in the test region
 * --help': prints help
 * @endcode
 *
 * The following are the `test_program_otp` prerequisites:
 *
 * @code
 * board# modprobe optee
 * board# tee-supplicant &
 * @endcode
 *
 * The following completes an OTP daily test:
 *
 * @code
 * board# test_program_otp --dailytest 0
 * @endcode
 *
 * The `test_otp` functions when there is no TOS (OP-TEE), depending on the `amba_otp` driver.
 * Further, it includes a similar option to the `test_program_otp`, as shown below:
 *
 * @code
 * --writepubkey [%%d] [%%s] [%%d]': '--writepubkey' writes (%%d'th) the ROT public key (file name %%s) (lock or not %%d)
 * --readpubkey [%%d]': '--readpubkey' reads (%%d'th) the RoT public key
 * --readambauniqueid: reads the Ambarella-unique ID
 * --readmonocounter': reads the mono counter
 * --increasemonocounter': increases the mono counter
 * --writecustomeruid [%%s] [%%d]': writes the customer-unique ID (file name %%s) (lock or not %%d)
 * --readcustomeruid': reads the customer-unique ID
 * --permanentlyenablesecureboot': permanently enables secure boot
 * --generatehuk': generates the hardware-unique encryption key
 * --writeaeskey [%%d] [%%d]': '--writeaeskey' writes (%%d'th) the AES key, (lock or not %%d)
 * --writeecckey [%%d] [%%d]': '--writeecckey' writes (%%d'th) the ECC key, (lock or not %%d)
 * --writeusrslotg0 [%%d] [%%s] [%%d]': '--writeusrslotg0' will write (%%d'th) usr slot g0 (file name %%s), (lock or not %%d)
 * --readusrslotg0 [%%d]': '--readusrslotg0' will read (%%d'th) usr slot g0 region
 * --writehex2usrslotg0 [%%d] [%%s]': '--writehex2usrslotg0' writes (%%d'th) usr slot g0 with a hex string
 * --writetestregion [%%s] [%%d]': '--writetestregion' write the test region (file name %%s), (lock or not %%d)
 * --readtestregion': '--readtestregion' read the test region
 * --writehex2testregion [%%s]': '--writehex2testregion' writes the test region with a hex string
 * --revokekey [%%d]': '--revokekey' revokes (%%d'th) the key
 * --lockpubkey [%%d]': '--lockpubkey' locks (%%d'th) the key
 * --queryotpsetting': '--queryotpsetting' queries the OTP setting
 * --setjtagefuse': '--setjtagefuse' sets the JTAG eFUSE bit
 * --lockzonea': '--lockzonea' locks zone A, include sysconfig
 * --writesysconfig [%%x] [%%x] [%%d]': '--writesysconfig' writes sysconfig; the first is sysconfig, the second is sysconfig_mask, the last is lock
 * --querysysconfig': '--querysysconfig' queries sysconfig
 * --writemiscconfig [%%x]': '--writemiscconfig' writes miscellaneous configurations; the parameter is `misc config`
 * --querymiscconfig': '--querymiscconfig' queries misc config
 * --simulate': '--simulate' simulates an OTP write; it prints the OTP write address and size.  OTP is not actually written
 * --dailytest [%%d]': '--dailytest' performs a daily test covering all APIs; [%%d] means to try to write one bit in the test region
 * --help': print help
 *
 * The following is the `test_otp` prerequisite:
 *
 * @code
 * board # modprobe amba_otp
 * @endcode
 *
 * The following performs an OTP daily test:
 *
 * @code
 * board # test_otp -dailytest 0
 * @endcode
 *
 * - - - -
 *
 * @subsection otp_scenarios 1.3. Typical Scenarios for Each OTP Region
 *
 * The table below describes each OTP region’s typical scenario.  ‘Mandatory’ means this region’s definition is defined by Ambarella.  ‘Recommended’ means this region can be
 * customized.  If users want to change a recommended region’s usage, the corresponding changes in code are also required.
 * <table>
 * <caption id="table_otp_scenarios">Table 1-2. Typical Scenarios for Each OTP Region.</caption>
 * <tr><th align="left">OTP Region <th align="left">Definition<th align="left">Scenario<th align="left">Comment
 * <tr><td>sys_config<td>Mandatory<td>Configuration<td>System configuration
 * <tr><td>efuse_disable_jtag<td>Mandatory<td>Configuration<td>Disable hardware debug port
 * <tr><td>write_lock<td>Mandatory<td>Lock bits<td>Each bit locks an OTP region
 * <tr><td>cst_seed<td>Recommended<td>Planted seed / key<td>Customer-planted seed
 * <tr><td>Unique ID<td>Mandatory<td>Unique ID<td>Chip-unique ID
 * <tr><td>cst_cuk<td>Recommended<td>Planted seed / key<td>Customer-planted key
 * <tr><td>data_invalid<td>Mandatory<td>Secure boot<td>For RoT key revocation
 * <tr><td>secure_usb_boot_disable<td>Mandatory<td>Configuration<td>Disables secure USB boot
 * <tr><td>misc_config<td>Recommended<td>Configuration<td>Customized configuration
 * <tr><td>bst_ver_cnt<td>Recommended<td>Anti-rollback<td>Monotonic counters can be used by the OTA program
 * <tr><td>serial_number<td>Recommended<td>Serial number<td>Product serial number
 * <tr><td>OTP_TEST<td>Recommended<td>OTP function test<td>OTP read / write function test
 * <tr><td>HUK<td>Mandatory<td>Chip key<td>Root of TEE secure storage
 * <tr><td>USER_CUK<td>Recommended<td>Planted seed / key<td>User-planted key
 * <tr><td>AES_KEY_0 ~ AES_KEY_3<td>Recommended<td>Data encryption key<td>Data encryption key; users can specify their access to be secure world only or normal world accessible
 * <tr><td>ECC_KEY_0 ~ ECC_KEY_3<td>Recommended<td>Authentication key<td>Authentication key; users can specify their access to be secure world only or normal world accessible
 * <tr><td>USER_SLOT_0 ~ USER_SLOT_5<td>Recommended<td>Lockable data<td>Customized data (lockable)
 * <tr><td>ROT_KEY_0 ~ ROT_KEY_15<td>Mandatory<td>Root of trust key<td>RoT key
 * <tr><td>MONO_COUNT_0 ~ MONO_COUNT_2<td>Recommended<td>Anti-rollback<td>Monotonic counters can be used by OTA program
 * <tr><td>USER_DATA_0 ~ USER_DATA_2<td>Recommended<td>Data<td>Customized data
 * <tr><td>USER_SLOT_6 ~ USER_SLOT_9<td>Recommended<td>Lockable data<td>Customized data (lockable)
 * </table>
 *
 * - - - -
 *
 * @section uuid 2. Unique ID
 * There are three types of unique IDs.  The first is the 256-bit digital signal processor (DSP)-unique ID, which is available after booting the DSP.  The second type is the
 * 128-bit Ambarella-unique ID inside the OTP.  These two ID types are maintained by Ambarella, and are easily accessible to the user.  The third type is another 128-bit space
 * inside the OTP for the user’s unique ID.  Users can define and program their own ID.
 *
 * @subsection read_dsp_uuid 2.1 Read DSP-Unique ID from IOCTL
 * Use the input / output control (IOCTL) `IAV_IOC_QUERY_INFO`.  The sample code is provided below:
 * @code
 * struct iav_queryinfo query_unique_id;
 * memset(&query_unique_id, 0x0, sizeof(query_unique_id));
 * query_unique_id.qid = IAV_INFO_UNIQUE_ID;
 * ret = ioctl(iav_fd, IAV_IOC_QUERY_INFO, &query_unique_id);
 * @endcode
 *
 * @subsection read_amba_uuid_with_tz 2.2 Read the Ambarella Unique ID with TrustZone Enabled
 * When Arm TrustZone is enabled, use the following steps to read the unique ID:
 * @code
 * BOARD# modprobe optee
 * BOARD# tee-supplicant &
 * BOARD# test_program_otp –-readambauniqueid
 * @endcode
 *
 * @subsection read_amba_uuid_without_tz 2.3 Read the Ambarella Unique ID with TrustZone Disabled
 * When TrustZone is disabled, use the `amba_otp` driver to access OTP with the configuration
 * below.  This module is mutually exclusive with TrustZone; therefore, if TrustZone
 * is enabled, it will not function.
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *  drv_modules  --->
 *   private  --->
 *    kernel-module-ambotp (drv_modules/private/amba_otp/dsp_v5)
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 * 	meta-ambabsp  --->
 *   recipes-otp  --->
 *    kernel-module-ambotp (meta-ambabsp/recipes-otp/kernel-module-ambotp)
 * @endcode
 *
 * Next, use the following steps to read the Ambarella-unique ID:
 * @code
 * BOARD# modprobe amba_otp
 * BOARD# cat /proc/ambarella/amba_unique_id
 * @endcode
 * The following reads the unique ID with `test_otp`:
 * @code
 * BOARD# modprobe amba_otp
 * BOARD# test_otp –-readambauniqueid
 * @endcode
 *
 * - - - -
 *
 * @section mono_counter 3. Monotonic Counter
 *
 * The hardware monotonic counter is used to prevent a downgrade attack.
 * A downgrade attack refers to an attacker downgrading or rolling back firmware
 * to an older version in order to exploit the known security vulnerabilities.
 * A version binding check with the hardware monotonic counter can detect and prevent
 * this kind of attack. There are three monotonic counters on CV5x / CV7x / CV3, the
 * first two are 256 bits, and the third is 512 bits.
 *
 * - - - -
 *
 * @section TRNG 4. True Random Number Generator
 *
 * The CV5x / CV7x / CV3 chip family includes true random number generator (TRNG) hardware.
 * The entropy source of the TRNG is the thermal noise of the SoC. The Ambarella Linux SDK has
 * enabled it in both the rich OS (Linux) and the TOS (OP-TEE).
 * Drivers can be found in the following paths:
 *  - TRNG driver in OP-TEE:  `ambarella/boot/tee/optee_os/core/drivers/ambarella_trng.c`
 *  - TRNG driver in Linux:  `ambarella/kernel/linux-5.15/drivers/char/hw_random/ambarella-rng.c`
 *  - TRNG driver in AMBoot:  `ambarella/boot/amboot/src/bld/rng.c`
 *  - Sample code in Linux:  `ambarella/security/validation/rng_quality`
 * Use the command below to obtain the random number from the TRNG:
 * @code
 * BOARD# rng_quality –str /dev/hwrng --rng_num 10000 --file_num 1
 * @endcode
 *
 * Check the following configuration to build a binary with TRNG enabled:
 *
 * @anchor RNG_Quality_Test
 * -# To enable the hardware RNG in Linux, select the following command:
 * @code
 * build$ make linux_menuconfig
 *  Device Drivers  --->
 *   Character devices  -->
 *    <M> Hardware Random Number Generator Core Support  --->
 *     <M> Ambarella HW Random Number Generator support
 * @endcode
 * OP-TEE-OS uses the hardware RNG.  No extra user application code is required.
 * -# To enable `test_random` in Linux, select the following command:<br>
 * <B>Amba build</B>
 * @code
 * build$ make menuconfig
 *  meta-ambasecurity  --->
 *   recipes-security-validation  --->
 *    rngtest (meta-ambasecurity/recipes-security-validation/rngtest)
 * @endcode
 * <B>Yocto build</B>
 * @code
 * build$ make menuconfig
 *  security  --->
 *   validation  --->
 *    rngtest (security/validation/rng_quality)
 * @endcode
 *
 * -# Generate RNG on the device:
 * @code
 * // Test for /dev/random
 * BOARD# ./rng_quality_test --str /dev/random --rng_num 3000000 --file_num 3 --t
 * // Test for /dev/urandom
 * BOARD# ./rng_quality_test --str /dev/urandom --rng_num 3000000 --file_num 3 --t
 * // Test for hwrng
 * BOARD# ./rng_quality_test --str /dev/hwrng --rng_num 3000000 --file_num 3 --t
 * @endcode
 *
 * -# Check the RNG quality:
 * Users can use the tools provided by NIST to check the RNG quality.
 * For more details about the tools, refer to @ref https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-22r1a.pdf.
 * @note
 * The Ambarella SDK provides this tool in `ambarella/security/validation/rng_quality/sts-2.1.2`.
 *
 * - - - -
 *
 * @section disable_jtag_usb_boot 5. Disable JTAG and USB Boot
 * JTAG and USB boot are used only for debugging purposes.  Ambarella recommends that users disable them in an actual-use cases.
 * @note
 * - Force USB boot is automatically disabled when secure boot is enabled.
 * - The JTAG eFUSE bit (OTP63) must be set for JTAG, and then JTAG can be disabled.
 *
 * Use either of the following commands:
 * @code #test_program_otp –-setjtagefuse @endcode
 * Or
 * @code #test_otp --setjtagefuse @endcode
 * The two commands above set the JTAG eFUSE bit.
 * After the JTAG eFUSE bit has been set, the `JTAG_EN` register (AHBSP_JTAG_EN_REG) can toggle JTAG on / off.
 * `mmio_clrbits_32(AHBSP_JTAG_EN_REG, BIT(0));`
 *
 * The logic is provided as shown in the table below.
 * <table>
 * <caption id="jtag_efuse_and_reg_logic">Table 1-3. Logic JTAG eFUSE and Register Logic Table.</caption>
 * <tr><th align="left"> <th align="left">JTAG_en = 0<th align="left">JTAG_en = 1
 * <tr><td>JTAG_efuse = 0<td>JTAG available<td>JTAG available
 * <tr><td>JTAG_efuse = 1<td>JTAG NOT available<td>JTAG available
 * </table>
 *
 * In the flexible Linux SDK, the JTAG_en is 0 by default.  The scenarios are as follows:
 * - `JTAG_en` = 0, `JTAG_efuse` = 0: in the development stage, JTAG is available for
 *   debugging purposes
 * - `JTAG_en` = 0: `JTAG_efuse` will be set to 1 in the factory (during the mass-production
 *   (MP) process), then the JTAG is disabled (JTAG not available) to enhance
 *   the product’s security level
 * - `JTAG_en` = 1, `JTAG_efuse` = 1: performed by special firmware (the special firmware
 *   writes `JTAG_en` to 1 in the secure world); bring back the JTAG for the return material
 *   authorization (RMA) process’s debugging and analysis
 *
 * @note
 * Users can add `mmio_setbits_32(AHBSP_JTAG_EN_REG, BIT(0))` in `ambarealla/boot/tee/arm-trusted-firmware/ambarella/ambarella_security.c` to enable JTAG for the RMA process.
 * @code
 * void ambarella_security_setup(void)
 * {
 *          uint32_t i;
 *
 *         assert(boot_cookie_ptr()->bld_ram_start == BL33_BASE);
 *
 * #if (AMBARELLA_SUPPORT_SEURITY_CTRL == 1)
 *          /* Disable all devices's security by default in cold boot */
 *         ambarella_device_security_restore();
 * #endif
 *
 *         for (i = 0; i <= NIC_GPV_MASTER_PORT; i++)
 *                  mmio_write_32(NIC_GPV_REG(0x08 + i * 4), NON_SECURE);
 *
 *          mmio_write_32(NIC_GPV_REG(NIC_GPV_SLAVE_PORT_AXI), SECURE);
 *
 *          mmio_setbits_32(AHBSP_JTAG_EN_REG, BIT(0));		//add this line to enable JTAG
 *
 *          isb();
 *          dsb();
 *
 *          /* setup platform ATT (Address Translation Table) */
 *         ambarella_att_setup();
 *
 *          /* If secure boot is disabled, no need to setup Secure Memory */
 *          if (!ambarella_is_secure_boot())
 *                    return;
 *
 *          ambarella_secure_memory_setup();
 * }
 * @endcode
 *//*!
 * @file key_management.h
 * @brief
 * @version 1.0
 * @date 2023-12-17
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
 * @page key_management Key Management
 *
 * @section key_management_history 0. Revision History
 * <table>
 * <caption id="key_management_history"></caption>
 * <tr><th>Version<th> Updated Date<th align="left"> Modification
 * <tr><td>0.0.1<td>20231217<td> Initial Version
 * </table>
 *
 * Key management is a crucial aspect of security.  Secure boot is based on the digital signature process, which requires a private key to generate the signature (sign signature),
 * as well as a public key to verify it.  Private keys must be kept confidential, as the public keys are deployed on the device.  Ambarella chips use one-time programmable (OTP)
 * to prevent tampering of public keys.
 * As private keys are required for compiling firmware, they are located in the Arm® trusted firmware (ATF) / open portable trusted execution environment (OP-TEE) source code directory.  Developers, QAs, maintainers, and manufacturers can access private keys directly, thus presenting a high risk of key leakage.
 * To address this issue, the Ambarella Flexible Linux Software Development Kit (SDK) introduces the remote procedure call (RPC) toolkit.
 * The Ambarella SDK also supports cloud-based key management via the Amazon key management service (KMS) for secure boot and Arm® TrustZone®.  Because cloud-based KMS is provided
 * by the cloud service vendor, this feature is provided as a separate patch; it is not a standard part of the Ambarella SDK.  This feature can be requested from the Ambarella
 * contact window.  Detailed descriptions of cloud-based key management is beyond the scope of this document.
 * This chapter provides an overview of key management.
 * - Section @ref pub_key_on_dev
 * - Section @ref pri_key_in_local
 * - Section @ref pri_key_rpc
 * - Section @ref revoke_rot_key
 * - Section @ref key_management_user_guide
 *
 * @section pub_key_on_dev 1. Public Keys on the Device
 * The local root of trust (RoT) public key (PK) can be found at `ambarella/security/tz_sb_keys/local_keys/rot_keys/ed25519/pub_rot.bin` and tThe remote RoT PK can be found
 * on the server side at `ambarella/security/build/tz_dev_server/pub_rot.bin`.
 * The RoT PK is programmed into one-time programmable (OTP) and is used as the root of trust for secure boot.  The ATF keys are derived from the RoT key, and then embedded in the
 * firmware binary.  For OP-TEE, the trusted application (TA) public key is embedded into the OP-TEE-OS binary.  The public key for authenticating the Linux kernel is embedded into
 * the AMBoot binary.
 * @note
 * There are 16 RoT key slots in OTP; customers <B>MUST</B> program 16 RoT keys during the mass-production (MP) process.  Leaving empty RoT key slots can lead to system security
 * risks.
 *
 * @section pri_key_in_local 2. Private Keys in Local (Default Approach)
 * There are three major keys: the RoT key, which is used for secure boot; the kernel key, for Linux kernel authentication; and the TA key, for TA binary authentication.
 * In the default approach, these keys can be found in the source code directory.
 *  - RoT private key: `ambarella/security/tz_sb_keys/local_keys/rot_keys/ed25519/pri_rot.bin`
 *  - Kernel private key: `ambarella/security/tz_sb_keys/local_keys/kernel_keys/ed25519/pri_kernel.bin`
 *  - CoT root key: `ambarella/security/tz_sb_keys/local_keys/cot_root_keys/rsa2048/pri_cot_root.pem`
 *  - TA private key: `ambarella/boot/tee/optee_os/keys/default_ta.pem`
 *
 * @section pri_key_rpc 3. Private Keys at the Remote Server (RPC Toolkit)
 * In this section, Ambarella introduces a new method of key management: the RPC toolkit.  This kit is compatible with the original tools in ATF / OP-TEE, while restricting private
 * key access to administrators.
 * With the RPC toolkit, developers, quality assurances (QAs), maintainers, and manufacturers can compile ATF / OP-TEE without directly accessing the private key.  This toolkit
 * contains a daemon program, tool proxies on the developer side, a server that maintains the private keys, and a signing service.  The makefile can request a signing service via
 * tool proxies, which connects the daemon.  Then, the daemon requests the signing service over a TLS connection with the server, which is a safe connection used to prevent a
 * "middle-man attack".
 * The following diagram shows the three components of the development toolkit: the developer server, the daemon, and the tool proxy.  Developers can share a single server with
 * both an individual daemon and with the tool proxies.
 *
 * @anchor Data_Encryption_Diagram
 * @image html rpc_toolkit.png "Figure 1-1. RPC Toolkit."
 *
 * The tool proxies provide identical services with the original tools in ATF / OP-TEE.  However, there is one difference: the private keys are not local; they exist only on the
 * remote server side.
 * The keys on the server are located in the following paths:
 *  - RoT private key: `ambarella/security/build/tz_dev_server/rot_private.pem`
 *  - Kernel private key: `ambarella/security/build/tz_dev_server/kernel_private.pem`
 *  - CoT root key: `ambarella/security/build/tz_dev_server/pri_cot_root.pem`
 *  - TA private key: `ambarella/security/build/tz_dev_server/default_ta.pem`
 *
 * @section revoke_rot_key 4. Revoking the RoT Key
 * There are 16 RSA key slots in OTP, which makes it possible to revoke the RoT key. The manufacturer should writes all 16 RSA keys in OTP, and then locks them during the
 * manufacturing stage so that each key can cover several years.  For example, the first key can cover ten years, the second key can cover the next ten years, and so on.
 * Although there is an invalid bit in OTP for the first two keys, the last key cannot be revoked.  When a key is marked as invalid, secure boot will switch to the next key.
 * A brief example of the public key revocation mechanism: there are invalid bits for the first two RoT keys.  Secure read-only memory (ROM) / BST / BL2 checks those invalid bits
 * before loading the RoT key.  If the invalid bit is set, Secure ROM / BST / BL2 will load the next key.
 *
 * @section key_management_user_guide 5. User Guide
 * @subsection prepare_key_pairs 5.1. Preparing the Key Pairs
 * For users working with one project only, one key set is sufficient.  The project leader chooses the key set and then sends it to the other members in the project.  It is
 * acceptable to use an existing key set for this use case.  The following sections describe how to generate a new key set, as well as how to use an existing key set for both local
 * and RPC approaches.
 *
 * @subsubsection generate_new_key_pairs 5.1.1 Generating New Keys for the Local Approach (Optional)
 * Use the commands below to generate new keys.  The SDK is released with default key pairs, so the commands are used to replace the default set.  Ensure that new keys are
 * necessary before proceeding, and remember to save the generated keys.
 * -# Generate a new pair of RoT keys (including the public key bin):
 * @code
 * build$ cd ambarella/security/security_tools/scripts/
 * build$ chmod +x gen_rot_key.sh
 * build$ ./gen_rot_key.sh ed25519
 * @endcode
 *
 * -# Generate a new kernel private key:
 * @code
 * build$ cd ambarella/security/security_tools/scripts/
 * build$ chmod +x gen_kernel_key.sh
 * build$ ./gen_kernel_key.sh ed25519
 * @endcode
 *
 * -# Generate a new TA private key:
 * @code
 * build$ cd ambarella/security/security_tools/scripts/
 * build$ chmod +x gen_optee_ta_key.sh
 * build$ ./gen_optee_ta_key.sh
 * @endcode
 *
 * -# Generate a new CoT Root private key:
 * @code
 * build$ cd ambarella/security/security_tools/scripts/
 * build$ chmod +x gen_cot_root_key.sh
 * build$ ./gen_cot_root_key.sh
 * @endcode
 *
 * @subsubsection generate_new_key_pairs_for_rpc 5.1.2 Generating New Keys for the RPC Approach (Optional)
 * When users prepare the development server, these keys will automatically be generated.
 *
 * @subsection specify_rot_key_index 5.2 Specify RoT Key Index in BST Header
 * There is a key index field in the BST header.  Users can modify `ambarella/boot/amboot/vif/bst.info` to specify the RoT key index.<br>
 * <B>#define BST_SEC_KEYINX     0x0000</B>
 *
 * @subsection compile_sdk_with_secure_boot 5.3 Compiling the SDK with a Secure Boot
 * When compiling the SDK, users must ensure that the secure boot configuration is selected.  If the system includes Arm TrustZone, use `xxxx_trustzone_config`.  If the system
 * does not include Arm TrustZone, use `xxxx_secure_boot_without_trustzone_config`.  The steps for compiling are as follows.
 *
 * <B>Amba build:</B>
 * @code
 * build$ source build/env/amba-build.env
 * select the board
 * build$ make ipcam_tz_config
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ source build/env/yocto-build.env
 * Select the board
 * Build# make ipcam_tz_config
 * @endcode
 *
 * By default, the compiler chooses the local approach (private keys in a local place in the source code).
 * To use the RPC approach, select the following items in `make menuconfig`.
 *
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *  security  --->
 *   boot-security (security/boot_security)  --->
 *    [*] Using RPC(Remote Procedure Call) Toolkit For Trust Zone --->
 *     (9088) Local port
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *  meta-ambabsp  --->
 *   recipes-boot-security  --->
 *    boot-security (meta-ambasecurity/recipes-boot-security/boot-security)  --->
 * @endcode
 *
 * @note
 * - The “local port” is used for the development tool proxy and daemon.  If several developers use the same PC or server for compiling, each developer must choose a different port.
 * - Users must ensure that the RPC development server and the daemon are configured before compiling to use the remote approach.  Instructions on how to configure the correct environment are described in the next section.
 *
 * <b>Compile the SDK</b>
 * @code
 * build$ make
 * @endcode
 *
 * @note
 * OP-TEE versions 3.8 and later require Python 3 (3.6.9).  Users must ensure that the build machine has the correct Python version.  If a Python report error occurs, users must install the related Python modules using the following commands:
 * @code
 * build$ sudo apt install python3-pyelftools
 * build$ sudo apt install python3-pip
 * build$ pip3 install pycryptodomex
 * @endcode
 *
 * @subsection set_up_rpc_env 5.4 Setting Up the RPC Environment
 * The RPC toolkits can be found under `ambarella/security/build`:
 *  - Compiled development server: `./tz_dev_server/tz_dev_server_v2`
 *  - Compiled development daemon: `./tz_dev_daemon/tz_dev_daemon`
 *  - Compiled tool proxies: `./tz_dev_proxy/`
 * For detailed steps, refer to `ambarella/security/build/trustzone_secure_boot_toolkit_help.txt`.
 *
 * @subsubsection run_dev_server 5.4.1 Running the Development Server
 * Running the server program on the privileged server requires several keys and a certificate.  Refer to the following steps to generate the keys and to start the server program.
 * -# Create a server identity key pair.  Ambarella strongly recommends that users select a passphrase that is more secure than “1234”, as shown in the example below:<br>
 * `# openssl genpkey -algorithm RSA -out server_priv_key.pem -pkeyopt rsa_keygen_bits:2048 -pkeyopt rsa_keygen_pubexp:65537 -pass pass:1234 -aes-256-cbc`
 * -# Generate the self-signed certificate:<br>
 * `# openssl req -new -x509 -days 3650 -key server_priv_key.pem -out server.crt -subj /C=CN/ST=SH/L=PD/O=amba/OU=system/CN=amba/emailAddress=abcdefg@ambarella.com`
 * -# Run the development server:
 * @code
 * # cd tz_dev_server
 * # ./tz_dev_server_v2 ./db 9002
 * @endcode
 *
 * @note
 * - The folder `db` stores all approved developer accounts.
 * - The first time the development server operates, the application asks the user to generate the private keys.  Type <b>“y” + Enter</b> to run the server.
 *
 * @subsubsection run_dev_daemon 5.4.2 Running the Development Daemon
 * Running the development daemon as a client requires an identity key and a public key from the server `server_pub_key.txt`.  The administrator must distribute the server’s public
 * key to developers, who can then compile the SDK using the secure boot feature.  Follow the hints provided in `tz_dev_daemon` to generate an identity key.
 * -# Generate an RSA key pair.  Remember to use a passphrase that is more secure than the one shown below:
 * @code # openssl genpkey -algorithm RSA -out client_priv_key.pem -pkeyopt rsa_keygen_bits:2048 -pkeyopt rsa_keygen_pubexp:65537 -pass pass:1234 -aes-256-cbc @endcode
 * -# Run the development daemon with the IP, port, and local port of the remote server.  This enables the compiler tools to make the request:
 * @code # ./tz_dev_daemon 10.4.8.67 9002 9088 @endcode
 * The first time the daemon operates, the user will be asked to register a new account.  Enter a unique name, then type <b>“y” + Enter</b> to proceed.
 * The newly registered account must be approved by the administrator.  On the server side, a prompt appears awaiting administrator approval.  Administrators must type <b>“y” + Enter</b>
 * to approve the registered user.
 * After the new registration is complete, the daemon begins running.  If the account is already registered, the daemon will begin running after login.
 * @note
 * The mutual authentication of the server and the daemon are based on their key pairs.
 *
 * @subsection program_public_key_into_otp 5.5 Programming a Public Key into OTP
 * If the public key is not programmed into OTP, the first two authentications will be skipped (Secure ROM -> BST, BST -> BL2).
 * There are three public key slots in OTP.  The manufacturer can revoke the first two public keys after some time.  For example, it is possible to revoke the first key after a
 * decade, the second key after the next decade, and keep the last key for the remaining years.  However, the last key is irrevocable.  To prevent an attacker from programming the
 * last public key, Ambarella strongly recommends that the manufacturer programs all three keys in OTP at the factory.
 *
 * Use the following steps to program the OTP with the RSA public key (with Arm TrustZone):
 * @code
 * BOARD# modprobe optee
 * BOARD# tee-supplicant&
 * BOARD# test_program_otp --writepubkey 0 /sdcard/rot_public.bin
 * BOARD# test_program_otp --readpubkey 0 		// Read it back from OTP
 * @endcode
 *
 * Use the following steps to program the OTP with the RSA public key (without Arm TrustZone):
 * @code
 * BOARD# modprobe amba_otp
 * BOARD# test_otp --writepubkey 0 /sdcard/rot_public.bin
 * BOARD# test_otp --readpubkey 0 		// Read it back from OTP
 * @endcode
 *
 * @note
 * The `rot_public.bin` is located in a local folder or on the remote server.  For more details, refer to @ref pub_key_on_dev
 *
 * @subsection enable_sec_boot 5.6 Enabling Secure Boot
 * During the debugging process, Ambarella recommends that users enable secure boot with a power-on configuration (POC) pin, which is revocable.  In the manufacturing stage, secure
 * boot must be permanently enabled so that attackers cannot disable it on the real product.
 * Force USB boot is automatically disabled when secure boot is enabled.
 *
 * @subsubsection enable_sec_boot_with_poc_pin 5.6.1 Enabling Boot with a POC Pin
 * POC[6] must be pulled high with a secure boot-enabled image; otherwise, the boot-up will fail.
 * All 16 RoT keys must be locked explicitly first, then secure boot can take effect.  Otherwise, the ROM checks BST, and the BST check of BL2 will be skipped.
 *
 * @subsubsection permanently_set_se_boot 5.6.2 Permanently Setting Secure Boot
 * Use the eFUSE bit to permanently set secure boot.  If secure boot is permanently enabled, the POC pin cannot enable or disable secure boot.
 * Because this process is irrevocable, use caution while performing this operation.
 *
 * When the system is with Arm TrustZone:
 * @code
 * BOARD# modprobe optee
 * BOARD# tee-supplicant&
 * BOARD# test_program_otp --permanentlyenablesecureboot
 * @endcode
 *
 * When the system is without Arm TrustZone:
 * @code
 * BOARD# modprobe amba_otp
 * BOARD# test_otp --permanentlyenablesecureboot
 * @endcode
 *
 * Typically, this step is performed during the manufacturing process.
 * On the CV5x / CV7x / CV3 EVK board, the compiler must additionally select "Force to enable secure boot" in menuconfig.
 *
 * @subsection run_se_boot 5.7 Running Secure Boot
 * If the public key is not programmed in OTP, or if secure boot is disabled, the first two authentications will be skipped.  The console will print a `Skipping ROTPK verification`
 * message, as shown below:
 * @code
 * NOTICE:  BL2: v1.5(release):v1.5-30-g70336698
 * NOTICE:  BL2: Built : 11:46:57, Sep 29 2018
 * NOTICE:  ROTPK is not deployed on platform. Skipping ROTPK verification.
 * NOTICE:  BL2: Booting BL31
 *
 * NOTICE:  BL31: Secure code at 0x100000
 * NOTICE:  BL31: Non Secure code at 0x1000000
 * NOTICE:  BL31: v1.5(release):v1.5-30-g70336698
 * NOTICE:  BL31: Built : 11:47:12, Sep 29 2018
 *
 * NOTICE:  Verify OK.
 * Authenticate Kernel: pass.
 * @endcode
 *
 * If the public key is programmed in OTP and secure boot is enabled, the full chain of authentications will take effect.
 * The console prints the message, as shown below:
 * @code
 * NOTICE:  BL2: v1.5(release):v1.5-30-g70336698
 * NOTICE:  BL2: Built : 11:46:57, Sep 29 2018
 * NOTICE:  BL2: Booting BL31
 *
 * NOTICE:  BL31: Secure code at 0x100000
 * NOTICE:  BL31: Non Secure code at 0x1000000
 * NOTICE:  BL31: v1.5(release):v1.5-30-g70336698
 * NOTICE:  BL31: Built : 11:47:12, Sep 29 2018
 *
 * NOTICE:  Verify OK.
 * Authenticate Kernel: pass.
 * @endcode
 *
 * @subsection rot_revoke 5.8 RoT Key Revocation
 * For APIs that can revoke the first two public keys, use the command below (with Arm TrustZone):
 * @code
 * BOARD# modprobe optee
 * BOARD# tee-supplicant&
 * BOARD# test_program_otp --revokekey %%d
 * @endcode
 *
 * For APIs that can revoke the first two public keys, use the command below (without Arm TrustZone):
 * @code
 * BOARD# modprobe amba_otp
 * BOARD# test_otp --revokekey %%d
 * @endcode
 */






/*!
 * @file crypto_performance.h
 * @brief
 * @version 1.0
 * @date 2023-12-17
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
 * @page crypto_performance Crypto Performance
 *
 * @section crpypto_performance_history 0. Revision History
 * <table>
 * <caption id="crpypto_performance_history"></caption>
 * <tr><th>Version<th> Updated Date<th align="left"> Modification
 * <tr><td>0.0.1<td>20231217<td> Initial Version
 * </table>
 *
 * Armv8 includes a crypto extension, which is a hardware module dedicated for crypto computation, such as the advanced encryption standard (AES) and secure hash algorithm (SHA).
 * It can be used with the Armv8 crypto extension instructions.  Ambarella recommends using it in conjunction with the OpenSSL library, as it comes equipped with Armv8 crypto
 * extension instructions.
 *
 * As OpenSSL provides many approaches for running the same computations as AES, users must choose the approach that utilizes the Armv8 crypto extension instructions; not doing so
 * can produce lower-than-expected results.
 * Rather than using OpenSSL, users can directly utilize the Armv8 crypto instructions.  Refer to the following sample code:
 *  - Rather than using `ambarella/security/crypto_engine/src/armv8_crypto_extension`, choose “computing via Armv8 crypto instructions” in OpenSSL; refer to the sample code located at `Ambarella/security/crypto_performance/openssl`
 *  - To obtain the crypto performance benchmarks, refer to `ambarella/security/crypto_performance/openssl/help_crypto_performance.txt`
 * The CV5x crypto performance table is provided below.  Broad configurations, with different CPU / dynamic random-access memory (DRAM) frequency settings, can result in slight 
 * differences.
 *
 * <table>
 * <caption id="table_crypto_performance">Table 1-2. Crypto Performance Table.</caption>
 * <tr><th align="left">Category<th align="left">Cryptography Algorithm<th align="left">Computing Operation<th align="left">Performance<th align="left">
 * <tr><td rowspan="10">Symmetric cryptography for data encryption<td rowspan="3">AES-128<td>AES-128 GCM (block size = 1024<td>1162 MB per second
 * <tr>		                                                                            <td>AES-128 CTR  (block size = 1024)<td>1881 MB per second
 * <tr>		                                                                            <td>AES-128 CBC  (block size = 1024)<td>1982 MB per second
 * <tr>		                                                     <td rowspan="3">AES-192<td>AES-192 GCM  (block size = 1024)<td>1071 MB per second
 * <tr>		                                                                            <td>AES-192 CTR  (block size = 1024)<td>1639 MB per second
 * <tr>		                                                                            <td>AES-192 CBC  (block size = 1024)<td>1743 MB per second
 * <tr>		                                                     <td rowspan="3">AES-256<td>AES-256 GCM  (block size = 1024)<td>992 MB per second
 * <tr>		                                                                            <td>AES-256 CTR  (block size = 1024)<td>1461 MB per second
 * <tr>		                                                                            <td>AES-256 CBC  (block size = 1024)<td>1534 MB per second
 * <tr>		                                                                     <td>SM4<td>SM4 (block size = 1024 byte)<td>60 MB per second
 * <tr><td rowspan="16">Asymmetric cryptography for authentication (digital signature sign / verify)<td rowspan="2">RSA-2048<td>RSA-2048 sign<td>189 times per second
 * <tr>                                                                                                                     <td>RSA-2048 verify<td>6889 times per second
 * <tr>                                                                                             <td rowspan="2">RSA-3072<td>RSA-3072 sign<td>60 times per second
 * <tr>                                                                                                                     <td>RSA-3072 verify<td>3117 times per second
 * <tr>                                                                                             <td rowspan="2">RSA-4096<td>RSA-4096 sign<td>26 times per second
 * <tr>                                                                                                                     <td>RSA-4096 verify<td>1767 times per second
 * <tr>                                                                                             <td rowspan="2">ECDSA (NIST-p224)<td>ECDSA (NIST-p224) sign<td>6827 times per second
 * <tr>                                                                                                                     <td>ECDSA (NIST-p224) verify<td>2830 times per second
 * <tr>                                                                                             <td rowspan="2">ECDSA (NIST-p256)<td>ECDSA (NIST-p256) sign<td>12193 times per second
 * <tr>                                                                                                                     <td>ECDSA (NIST-p256) verify<td>3545 times per second
 * <tr>                                                                                             <td rowspan="2">ECDSA (NIST-p384)<td>ECDSA (NIST-p384) sign<td>289 times per second
 * <tr>                                                                                                                     <td>ECDSA (NIST-p384) verify<td>391 times per second
 * <tr>                                                                                             <td rowspan="2">ECDSA (NIST-p521)<td>ECDSA (NIST-p521) sign<td>705 times per second
 * <tr>                                                                                                                     <td>ECDSA (NIST-p521) verify<td>330 times per second
 * <tr>                                                                                             <td rowspan="2">ED25519<td>ED25519 sign<td>13545 times per second
 * <tr>                                                                                                                     <td>ED25519 verify<td>4452 times per second
 * <tr><td rowspan="7">Secure hash function<td rowspan="3">SHA2<td>SHA2-256 (block size = 1024)<td>1001 MB per second
 * <tr>		                                                   <td>SHA2-384 (block size = 1024)<td>261 MB per second
 * <tr>		                                                   <td>SHA2-512 (block size = 1024)<td>261 MB per second
 * <tr>                                    <td rowspan="3">SHA3<td>SHA3-256 (block size = 1024)<td>201 MB per second
 * <tr>		                                                   <td>SHA3-384 (block size = 1024)<td>156 MB per second
 * <tr>		                                                   <td>SHA3-512 (block size = 1024)<td>108 MB per second
 * <tr>		                                            <td>SM3<td>SM3<td>148 MB per second
 * <tr><td rowspan="4">HMAC               <td rowspan="2">HMAC SHA2<td>HMAC SHA2-256 (block size = 1024)<td>980 MB per second
 * <tr>                                                            <td>HMAC SHA2-512 (block size = 1024)<td>255 MB per second
 * <tr>                                   <td rowspan="2">HMAC SHA3<td>HMAC SHA3-256 (block size = 1024)<td>197 MB per second
 * <tr>                                                            <td>HMAC SHA3-512 (block size = 1024)<td>107 MB per second
 * </table>
 *
 * The CV5x crypto performance table (in the open portable trusted execution environment (OP-TEE)) is provided below.  Board configurations, with different CPU / DRAM frequency
 * settings, can result in slight differences.
 * <table>
 * <caption id="table_crypto_performance">Table 1-2. Crypto Performance (in OP-TEE) Table.</caption>
 * <tr><th align="left">Category<th align="left">Cryptography Algorithm<th align="left">Computing Operation<th align="left">Performance
 * <tr><td rowspan="9">Symmetric cryptography for data encryption<td rowspan="3">AES-128<td>AES-128 GCM (buffer size = 131072)<td>814 MB per second
 * <tr>		                                                                            <td>AES-128 CTR (buffer size = 131072)<td>1100 MB per second
 * <tr>		                                                                            <td>AES-128 CBC (buffer size = 131072)<td>679 MB per second
 * <tr>		                                                     <td rowspan="3">AES-192<td>AES-192 GCM (buffer size = 131072)<td>769 MB per second
 * <tr>		                                                                            <td>AES-192 CTR (buffer size = 131072)<td>1006 MB per second
 * <tr>		                                                                            <td>AES-192 CBC (buffer size = 131072)<td>607 MB per second
 * <tr>		                                                     <td rowspan="3">AES-256<td>AES-256 GCM (buffer size = 131072)<td>718 MB per second
 * <tr>		                                                                            <td>AES-256 CTR (buffer size = 131072)<td>941 MB per second
 * <tr>		                                                                            <td>AES-256 CBC (buffer size = 131072)<td>556 MB per second
 * <tr><td rowspan="3">Secure hash function<td rowspan="3">SHA2<td>SHA2-256 (buffer size = 131072)<td>710 MB per second
 * <tr>		                                                   <td>SHA2-384 (buffer size = 131072)<td>52 MB per second
 * <tr>		                                                   <td>SHA2-512 (buffer size = 131072)<td>52 MB per second
 * </table>
 *
 * For other chips such as CV7x / CV3, users can refer to @ref Crypto_Performace to test the crypto performance for chips
 *//*!
 * @file design_guide.h
 * @brief
 * @version 1.0
 * @date 2023-12-17
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
 * @page design_guide Design Guide
 *
 * @section design_guide_history 0. Revision History
 * <table>
 * <caption id="design_guide_history"></caption>
 * <tr><th>Version<th> Updated Date<th align="left"> Modification
 * <tr><td>0.0.1<td>20231217<td> Initial version
 * </table>
 *
 * There are some differences between different CV5x / CV7x / CV3 chips.  This chapter provides important information relating to the design stage.
 *
 * @section for_dev_board 1. Development Board
 * To toggle secure boot on / off, use POC[6], the dual in-line package (DIP) switch on the development board.
 * Do not use "permanently enable secure boot" on the development board or on the evaluation kit (EVK).
 *
 * @section hw_schematic_diag 2. Hardware Schematic Diagram
 * Users must send the hardware schematic diagram to the Ambarella hardware team to review in order to guarantee that the schematic is correct.
 *
 * @section mass_production_process 3. Mass-Production Process
 * In the mass-production (MP) process, users must write all three root of trust (RoT) keys into one-time programmable (OTP), because leaving blank RoT key slots can cause security
 * issues in the product.  "Permanently enable secure boot" must be applied during the MP process in order to guarantee that there is no way to bypass the secure boot check.
 *//*!
 * @file security_validation_guide.h
 * @brief
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
 
 /*!
 * @page security_validation_guide Validation Guide
 *
 * @section validation_guide_history 0. Revision History
 * <table>
 * <caption id="security_validation_guide_history"></caption>
 * <tr><th>Version<th> Updated Date<th align="left"> Modification
 * <tr><td>0.0.1<td>20231221<td> Initial version
 * </table>
 *
 * Users can follow this guide to test the security features on CV5x / CV7x / CV3
 * <table>
 * <caption id="security_validation_guide"></caption>
 * <tr><th align="left">Secure aspects<th align="left">Security Features<th align="left">Validation Guide
 * <tr><td rowspan="4">System Integrity Protection<td> Secure Boot <td align="center"> @ref Secure_Boot
 * <tr>                                           <td> Online Upgarde <td align="center"> @ref Online_Upgrade
 * <tr>                                           <td> Rescue Mode <td align="center"> @ref Rescue_Mode
 * <tr>                                           <td> Linux DM-Verity <td align="center"> @ref Linux_Dm_verity
 * <tr><td rowspan="2">System Reinforcement       <td> Secure Enhanced Bootloader <td align="center"> @ref Secure_Enhanced_Bootloader
 * <tr>                                           <td> OP-TEE <td align="center"> @ref OP_TEE
 * <tr><td rowspan="3">Data Storage Protection    <td> DM-Crypt <td align="center"> @ref Dm_Crpypt
 * <tr>                                           <td> Data Encryption <td align="center"> @ref Data_Encryption
 * <tr>                                           <td> Secure Storage <td align="center"> @ref Secure_Storage
 * <tr><td rowspan="2"> Intellectual Property Protection <td> Unit License Protection <td align="center"> @ref Unit_License_Protection
 * <tr>                                                  <td> Neural Network Model Protection <td align="center"> @ref Neural_Network_Model_Protection
 * <tr><td rowspan="2"> Secure Hardware          <td> OTP <td align="center"> @ref One_Time_Programmable
 * <tr>                                           <td> RNG <td align="center"> @ref Random_Number_Generator
 * <tr><td>                                       <td> Key Tools <td align="center"> @ref Key_tools
 * </table>
 *
 * @anchor Secure_Boot
 * @section test_secure_boot 1. Secure Boot
 *
 * By default, Ambarella provides three methods for users to store keys:
 * - In the local software development kit (SDK)
 * - Use the remote procedure call (RPC) toolkits provided by Ambarella
 * - Use Amazom Web Service (AWS) Key Management Service (KMS)
 * Users also can use their own key management service to store keys.
 * 
 * @subsection generate_secure_boot_keys 1.1 Generate Keys for Secure Boot
 *
 * @subsubsection generate_secure_boot_keys_local 1.1.1 Generate Keys for the Local Approach
 * Refer to @ref generate_new_key_pairs for more information.
 *
 * @subsubsection generate_secure_boot_keys_rpc 1.1.2 Generate Keys for the RPC Approach
 * When users prepare the development server, these keys will automatically be generated.<br>
 * Users can refer to @ref set_up_rpc_env to set up RPC enviroment.
 * 
 * @subsection validation_compile_sdk_with_secure_boot 1.2 Compile the SDK with Secure Boot
 * If users use the default configuration file provided by Ambarella, they can can refer to @ref compile_sdk_with_secure_boot.<br>
 * If users want to enable secure boot with Arm® TrustZone® from a non-secure boot configuration, the following options should be selected:<br>
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *  boot  --->
 *  [*] amboot (boot/ambamk)  --->
 *   Ambarella Bootloader Configuration  --->
 *    AMBoot Options  --->
 *     [*] Boot with TrustZone  --->
 *      -*-   Secure Boot with Signature
 *       -*-   Secure DTB with Signature (SOC Firmware Config)
 *        [*]   Boot with trusted OS(OPTEE)
 *  tee  --->
 *   [*] arm-tf (boot/tee/ambamk)
 *   [*] optee-client (boot/tee/ambamk)
 *   [*] optee-os (boot/tee/ambamk)
 *   [*] optee-test (boot/tee/ambamk)
 *  security  --->
 *  [*] boot-security (security/boot_security)  --->
 *   [*]   Bootloader Authenticate Linux Kernel  --->
 *    [*]   Bootloader Embed Kernel Public Bin Key
 *     Bootloader Authenticate Linux Kernel Algorithm (ED25519)  --->
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *  meta-ambabsp  --->
 *   recipes-bsp  --->
 *    [*] amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *     Ambarella Bootloader Configuration  --->
 *      AMBoot Options  --->
 *       [*] Boot with TrustZone  --->
 *        -*-   Secure Boot with Signature
 *         -*-   Secure DTB with Signature (SOC Firmware Config)
 *          [*]   Boot with trusted OS(OPTEE)
 *       [*] arm-tf (meta-ambabsp/recipes-bsp/boot) 
 *   recipes-tee  --->
 *    [*] optee-os (meta-ambabsp/recipes-tee/optee-os)
 *     [*] opteeclient (meta-ambabsp/recipes-tee/opteeclient)
 *      [*]   opteetest (meta-ambabsp/recipes-tee/opteetest)
 *  meta-ambasecurity  --->
 *   recipes-boot-security  --->
 *    [*] boot-security (meta-ambasecurity/recipes-boot-security/boot-security)  --->
 *     [*]   Bootloader Authenticate Linux Kernel  --->
 *      [*]   Bootloader Embed Kernel Public Bin Key
 *        Bootloader Authenticate Linux Kernel Algorithm (ED25519)  --->
 * @endcode
 *
 * Users also must modify the system memory layout to enable secure boot with TrustZone; refer to @ref mem_layout for more information.
 *
 * If users want to enable secure boot without TrustZone from a non-secure boot configuration, the following options should be selected:<br>
 * <B>Amba build:</B>
 * @code
 * build$ make menuconfig
 *  boot  --->
 *  [*] amboot (boot/ambamk)  --->
 *   Ambarella Bootloader Configuration  --->
 *    AMBoot Options  --->
 *     [*] Boot with TrustZone  --->
 *      -*-   Secure Boot with Signature
 *       -*-   Secure DTB with Signature (SOC Firmware Config)
 *  tee  --->
 *   [*] arm-tf (boot/tee/ambamk)
 *  security  --->
 *  [*] boot-security (security/boot_security)  --->
 *   [*]   Bootloader Authenticate Linux Kernel  --->
 *    [*]   Bootloader Embed Kernel Public Bin Key
 *     Bootloader Authenticate Linux Kernel Algorithm (ED25519)  --->
 * @endcode
 *
 * <B>Yocto build:</B>
 * @code
 * build$ make menuconfig
 *  meta-ambabsp  --->
 *   recipes-bsp  --->
 *    [*] amboot (meta-ambabsp/recipes-bsp/boot)  --->
 *     Ambarella Bootloader Configuration  --->
 *      AMBoot Options  --->
 *       [*] Boot with TrustZone  --->
 *        -*-   Secure Boot with Signature
 *         -*-   Secure DTB with Signature (SOC Firmware Config)
 *       [*] arm-tf (meta-ambabsp/recipes-bsp/boot) 
 *   recipes-tee  --->
 *    [*] optee-os (meta-ambabsp/recipes-tee/optee-os)
 *  meta-ambasecurity  --->
 *   recipes-boot-security  --->
 *    [*] boot-security (meta-ambasecurity/recipes-boot-security/boot-security)  --->
 *     [*]   Bootloader Authenticate Linux Kernel  --->
 *      [*]   Bootloader Embed Kernel Public Bin Key
 *        Bootloader Authenticate Linux Kernel Algorithm (ED25519)  --->
 * @endcode
 *
 * By default, the Ambarella SDK stores keys in the local approach.  Users can store keys in other locations:
 *
 * @subsubsection compile_secure_boot_with_rpc 1.2.1 Using Ambarella RPC Toolkits
 * -# Set up the RPC enviroment; refer to set_up_rpc_env.
 * -# Select RPC in the menuconfig base configuration file with secure boot enabled:<br>
 *  <B> Amba Build </B>
 *  @code
 *  build$ make menuconfig
 *   security  --->
 *   [*] boot-security (security/boot_security)  --->
 *     [*]   Using RPC(Remote Procedure Call) Toolkit to sign binary  --->
 *  @endcode
 *
 *  <B>Yocto build:</B>
 *  @code
 *  build$ make menuconfig
 *  *  meta-ambasecurity  --->
 *   recipes-boot-security  --->
 *    [*] boot-security (meta-ambasecurity/recipes-boot-security/boot-security)  --->
 *     [*]   Using RPC(Remote Procedure Call) Toolkit to sign binary  --->
 *  @endcode
 *
 * -# Compile the SDK with the RPC enviroment enabled.
 *
 * @subsubsection compile_secure_boot_with_aws_kms 1.2.2 Using AWS KMS
 * -# Compile the security tools.
 *  @code
 *  cd ambarella/security/plugins/aws_kms/aws_kms_openssl_engine_amba && make
 *  cd ambarella/security/security_tools && make && make install
 *  @endcode
 *
 * -# Set up the KMS key and environment (users can use their own keys):
 *  @code
 *   aws configure
 *   AWS Access Key ID [None]: abc
 *   AWS Secret Access Key [None]: abc
 *   Default region name [None]: cn-north-1
 *   Default output format [None]:
 *  @endcode
 *
 * -# Get the public RoT key (must be programmed into OTP) and the kernel key (must be compiled into `boot_loader`)
 *  @code
 *  //get public rot key, copy pem to .pem file (pub_rot.pem)
 *  openssl pkey -engine aws_kms -inform engine -in arn:aws-cn:kms:cn-north-1:1234567890ab:key/12345678-abcd-efgh-1234-1234567890ab -pubout -text -out pub_rot.pem
 *
 *  // convert public rot key (.pem -> .txt -> .bin)
 *  ambarella/security/build/generic_tools/key_convertor --in pub_rot.pem --out pub_rot.txt --convertpem
 *  ambarella/security/build/generic_tools/key_convertor --in pub_rot.txt --out pub_rot.bin --generatepubkeybin
 *
 *  //get public kernel key, copy pem to .pem file (pub_kernel.pem)
 *  openssl pkey -engine aws_kms -inform engine -in arn:aws-cn:kms:cn-north-1:1234567890ab:key/12345678-abcd-efgh-1234-1234567890ab -pubout -text -out pub_kernel.pem
 *
 *  // convert public kernel key (.txt)
 *  ambarella/security/build/generic_tools/key_convertor --in pub_kernel.pem --out pub_kernel.txt --convertpem
 *  
 *  // convert public kernel key (.c)
 *  ambarella/security/build/sbss_dev_gen_key/sbss_dev_gen_key --convert pub_kernel.txt ambarella/security/boot_security/rsa2048_exp65537_pubkey.c
 *  @endcode
 *
 * -# Select `Using AWS KMS key to sign binary` in the menuconfig base in the configuration file with secure boot enabled:<br>
 *  <B>Amba build: </B>
 *  @code
 *  build$ make menuconfig
 *   security  --->
 *   [*] boot-security (security/boot_security)  --->
 *     [*]   Using AWS KMS key to sign binary
 *     () Rot-key	//add KMS key in menuconfig
 *     ...
 *     () Kernel-key
 *  @endcode
 *
 *  <B>Yocto build:</B>
 *  @code
 *  build$ make menuconfig
 *  *  meta-ambasecurity  --->
 *   recipes-boot-security  --->
 *    [*] boot-security (meta-ambasecurity/recipes-boot-security/boot-security)  --->
 *     [*]   Using AWS KMS key to sign binary
 *     () Rot-key	//add KMS key in menuconfig
 *     ...
 *     () Kernel-key
 *  @endcode
 *
 * -# Compile the SDK:
 *  @code
 *  make arm-tf_clean (clean ATF first to ensure the cert_create tool is built with ams-kms engine)
 *  make
 *  @endcode
 *
 * @subsubsection compile_secure_boot_with_other_key_management_service 1.2.3 Using Other Key Management Services
 * If users have their own key management service and they want to use the keys in it for secure boot, the following Makefile must be modified with their own key signing methods:<br>
 *  - For the kernel key, RoT key, and CoT root key, check ` ambarella/security/boot_security/Makefile.security`<br>
 *  - For the trusted application (TA) key in the open-portable trusted execution environment (OP-TEE), check the lines in the following files:<br>
 * In `ambarella/boot/tee/optee_os`:
 * @code
 * mk/config.mk:222
 * core/sub.mk:15
 * ta/ta.mk:175
 * ta/arch/arm/link_shlib.mk:6
 * ta/arch/arm/link_shlib.mk:57
 * ta/arch/arm/link.mk:5
 * ta/arch/arm/link.mk:119
 * @endcode
 *
 *
 * @subsection validation_program_public_key_into_otp 1.3 Programming a Public Key into OTP
 * Refer to @ref program_public_key_into_otp for more information.
 *
 * @subsection validation_enable_sec_boot 1.4 Enabling Secure Boot
 * Refer to @ref enable_sec_boot for more information.
 *
 * @subsection validation_run_se_boot 1.5 Running Secure Boot
 * Refer to @ref run_se_boot for more information.
 *
 * @subsection test_suite_for_secure_boot 1.6 Test Suite For Secure Boot
 * Users can follow the steps below to test whether secure boot is able to function:
 *
 * @subsubsection test_suite_secure_boot_auth_chain 1.6.1 Test Suite For Authentication Chain
 * The secure boot authentication chain inculudes three stages (refer to @ref auth_chain). If users use the wrong key to sign different partition, boot fails at different stages:
 * -# Prepare two sets of images signed with key pair A and key pair B. Burn image A onto the board.
 * -# Upgrade image B's kernel parition onto the board and reboot.
 *  - Boot should fail at the BLD stage, with secure boot enabled or disabled:
 * @code
 * Authenticate "kernel": failed
 * @endcode
 *
 * -# Burn image A onto the board, upgrade image B's BLD partition onto board, then reboot.
 *  - With secure boot enabled:<br> boot should fail at the BL2 stage
 *  - With secure boot disabled:<br> BL2 check pass; boot failed at BLD stage (because the kernel key in BLD changed)
 * @code
 * Authenticate "kernel": failed
 * @endcode
 *
 * -# Burn image A onto the board, then upgrade image B's Arm trusted firmware (ATF) partition onto the board and reboot
 *  - Boot should fail at the BST stage, with secure boot enabled (no print at console)
 *
 * -# Burn image A onto the board, then upgrade image B's BST partition onto the board and reboot
 *  - Boot should fail at the ROM stage, with secure boot enabled (no print at console)
 *
 * @subsubsection test_suite_rpc_toolkit 1.6.2 Test Suite For RPC Toolkit
 * -# Set up the RPC toolkit; refer to @ref generate_secure_boot_keys_rpc for more information.
 * -# Compile the SDK with three sets of keys:
 *  - Set A is with default local keys
 *  - Set B is with new generated keys (RPC approach)
 *  - Set C is with new generated keys (RPC approach), replace with the default RoT key in the RPC server:
 * @code
 * ambarella/security/keys/local_keys/rot_keys/ed25519/pri_rot.bin ambarella/security/build/tz_dev_server/pri_rot.bin
 * @endcode
 *
 * Case 1: Set A images should boot successfully, with secure boot enabled<br>
 * Case 2: Set C images should boot successfully, with secure boot enabled<br>
 * Case 3: Set A images + Set B’s kernel partition `k`ernel_release.elf`) via AmbaUSB<br>
 *       >>> Boot should fail at the BLD stage, with secure boot enabled<br>
 * Case 4: Set A images + Set B’s BLD partition (`bld_release.elf`) via AmbaUSB<br>
 *       >>> Boot should fail at the BL2 stage, with secure boot enabled<br>
 *       >>> BL2 check pass, boot failed at the BLD stage (because the kernel key in BLD changed), with secure boot disabled<br>
 * Case 5: Set A images + Set B’s ATF partition (atf_release.elf) via AmbaUSB<br>
 *       >>> Boot should fail at the BST stage, with secure boot enabled (no print at console)<br>
 *       >>> Boot was successful, with secure boot disabled<br>
 * Case 6: Set A images + Set B’s BST partition (`bst_release.elf`) via AmbaUSB<br>
 *       >>> Boot should fail at the ROM stage, with secure boot enabled (no print at console)<br>
 *       >>> Boot was successful, with secure boot disabled<br>
 *
 * @subsubsection test_suite_key_revocation 1.6.3 Test Suite For Key Revocation
 * -# Write 16 RoT  keys(key0, key1, key2, and so on) into OTP and lock them.
 *  - By default, the firmware is compiled with key0, and the board can boot successfully
 * -# Revoke key0 and reboot.
 *  @code
 *  BOARD# modprobe optee
 *  BOARD# tee-supplicant &
 *  BOARD# test_program_otp --revokekey
 *  BOARD# reboot
 *  @endcode
 *  - The boot fails because key0 was revoked
 * -# Replace the key with key1 and compile a new image.
 * @note
 * When using key1, the key index in `ambarella/boot/amboot/vif/bst.info` must be changed:
 * @code
 * #define BST_SEC_KEYINX	0x0001
 * @endcode
 *
 * -# Burn the new image (signed with key1) and boot.
 *  - The expected result is 'boot sucess'
 *
 * @anchor OP_TEE
 * @section test_optee 2. OP-TEE
 * Users can use the `xtest` command in OP-TEE to test OP-TEE related features:
 * @code
 * BOARD# modprobe optee
 * BOARD# tee-supplicant &
 * BOARD# xtest
 * BOARD# >>> check xtest result
 * BOARD# xtest --sha-perf
 * BOARD# >>>check sha performance result
 * BOARD# xtest --aes-perf
 * BOARD# >>>check aes performance result
 * @endcode
 *
 * @section test_ota 3. Secure Over The Air
 * @anchor Online_Upgrade
 * @subsection test_online_upgrade 3.1 Online Upgrade
 * Refer to @ref online_upgrade for more information.
 *
 * @anchor Rescue_Mode
 * @subsection test_rescue_mode 3.2 Rescue Mode
 * Refer to @ref rescue_mode for more information.
 *
 * @anchor Linux_Dm_verity
 * @subsection test_dm_verity 3.3 Linux Dm-verity
 * Refer to @ref set_up_dm_verity for more information.
 *
 * @anchor Secure_Enhanced_Bootloader
 * @section test_sebld 4. Secure Enhanced Bootloader
 * Refer to @ref SEBLD for more information.
 *
 * @anchor Dm_Crpypt
 * @section test_dm_crypt 5. Dm Crpypt
 * Refer to @ref dm_crypt for more information.
 *
 * @anchor Data_Encryption
 * @section test_data_encryption 6. Data Encryption
 * @subsection data_encryption_optee 6.1 Data Encryption in OP-TEE
 * Use `data_encryption_aes_v2_test` to perform AES encryption / decryption in OP-TEE:
 * @code
 * BOARD# modprobe optee
 * BOARD# tee-supplicant &
 * //encrypt data
 * BOARD# data_encryption_aes_v2_test --in input.bin --out enc.bin --mode XTS --op enc --len 128
 * //decrypt data
 * BOARD# data_encryption _aes_v2_test --in enc.bin --out dec.bin --mode XTS --op dec --len 128
 * @endcode
 * Both `input.bin` and `dec.bin` must be the same.
 *
 * @anchor Secure_Storage
 * @section test_secure_storage 7. Secure Storage
 * Use `test_secure_storage` to test secure storage in OP-TEE.  For secure storage datails, refer to @ref data_at_rest_protection.
 * @code
 * BOARD# modprobe optee
 * BOARD# tee-supplicant &
 * BOARD# test_secure_storage --storebuffer testbuffer a
 * BOARD# test_secure_storage --load2buffer a
 * BOARD# >>Load string object (a): testbuffer
 * The output buffer should be the same as the input buffer.
 *
 * BOARD# test_secure_storage --storefile test.txt b
 * BOARD# test_secure_storage --load2file b test_out.txt
 * BOARD# diff test.txt test_out.txt
 * The two files should be the same.
 * @endcode
 *
 * @anchor Unit_License_Protection
 * @section test_ulp 8. Unit License Protection 
 * Refer to @ref ulp_user_guide for more information.
 *
 * @anchor Neural_Network_Model_Protection
 * @section test_nmp 9. Neural Network Model Protection
 * Check the results between the RAW neural network (NN) model and the encrypted model
 *
 * Refer to @ref compile_nn_model_protection_code for the usage of neural network model protection (NMP).
 * -# Run the scripts in `ambarella/security/security_tools/scripts/test_encrypt_network_output.sh`.
 *  The result should be the same, and CRC should not change with multi loop.
 * -# Performance should be amost the same for both RAW and encoded NNs:
 * @code
 * BOARD# cavalry_gen -d vas_output -k pek.bin -f bvlc_googlenet_enc.bin
 * BOARD# test_nnctrl -b pnet_enc.bin  --in data=13.bin --out prob1=prob1_enc.bin --out conv4-2=conv4-2_enc.bin -v
 * BOARD# test_nnctrl -b pnet_enc.bin  --in data=13.bin --out prob1=prob1_enc.bin --out conv4-2=conv4-2_enc.bin --cert \
 * /usr/local/bin/ulp_nmp_test/certs/license_cert.bin --key /usr/local/bin/ulp_nmp_test/dev_encrypt_pek.bin --digest \
 * /usr/local/bin/ulp_nmp_test/dev_encrypt_pek.digest
 * @endcode
 *
 * @anchor One_Time_Programmable
 * @section test_otp 10. OTP
 * Refer to @ref program_otp for more information,
 * Generally, users can use `--daily test` to test OTP: <br>
 * <B>With TrustZone: </B>
 * @code
 * BOARD# modprobe optee
 * BOARD# tee-supplicant &
 * BOARD# test_program_otp --dailytest 1
 * @endcode
 *
 * <B>Without TrustZone: </B>
 * @code
 * BOARD# modprobe amba_otp
 * BOARD# test_otp --dailytest 1
 * @endcode
 *
 * @anchor Random_Number_Generator
 * @section test_rng 11. Random Number Generator
 * Refer to @ref RNG_Quality_Test for more information.
 *
 * @anchor Key_tools
 * @section test_key_tools 12. Key tools
 * Ambarella provides several key tools for security issues; refer to the following to test them:<br>
 * <B>`test_pkey_openssl`: </B> 
 * @code
 * build$ cd ambarella/security/security_tools/pkey_openssl
 * build$ make 
 * build$ test_pkey_openssl --genkey a.priv a.pub ed25519 sha512
 * build$ test_pkey_openssl --sign test.file a.priv test.sign
 * build$ test_pkey_openssl --verify test.file a.pub test.sign
 * 
 * build$ test_pkey_openssl_v2 --sign test.file abc_pri.pem test.sign
 * build$ test_pkey_openssl_v2 --verify test.file abc_pub.pem test.sign
 * @endcode
 *
 * <B>`key_convertor`: </B> 
 * @code
 * build$ cd ambarella/security/build/generic_tools
 * build$ cp ../../tz_sb_keys/local_keys/cot_root_keys/rsa2048/ * ./
 *
 * //run cmdlines in usage, compare the result
 * build$ ./key_convertor --in pri_cot_root.txt --out test_private.pem --converttxt --private
 * build$ ./key_convertor --in pub_cot_root.txt --out test_public.pem --converttxt
 * build$ diff pri_cot_root.pem test_private.pem
 * build$ diff pub_cot_root.pem test_public.pem
 * build$ ./key_convertor --in pub_cot_root.txt --out test_public.bin --generatepubkeybin
 * build$ diff test_public.bin pub_cot_root.bin
 * build$ ./key_convertor --in pri_cot_root.pem --out test_private.txt --convertpem --private
 * build$ diff pri_cot_root.txt test_private.txt
 * build$ ./key_convertor --in pub_cot_root.pem --out test_public.txt --convertpem
 * build$ diff test_public.txt pub_cot_root.txt
 * build$ ./key_convertor --in pri_cot_root.txt --out test_private.pem --converttxt --private --encrypt
 * @endcode
 *
 * <B>`key_tool_ed25519`: </B> 
 * @code
 * build$ key_tool_ed25519 --genkey new
 * build$ key_tool_ed25519 --genkey new2
 *
 * build$ key_tool_ed25519 --sign test.file pri_new.bin new.sign
 * build$ key_tool_ed25519 --sign test2.file pri_new.bin new2.sign
 *
 * //should get pass(no return)
 * build$ key_tool_ed25519 --verify test.file pub_new.bin new.sign
 * build$ key_tool_ed25519 --verify test2.file pub_new.bin new2.sign
 *
 * //should get failed([error]: verify_signature failed, ret -100)
 * build$ key_tool_ed25519 --verify test.file pub_new.bin new2.sign
 * build$ key_tool_ed25519 --verify test.file pub_new2.bin new.sign 
 * build$ key_tool_ed25519 --verify test2.file pub_new.bin new.sign
 *
 * build$ cp test2.file test3.file
 * build$ key_tool_ed25519 --sign test3.file pri_new.bin --embeded
 * build$ key_tool_ed25519 --verify test3.file pub_new.bin --embeded
 * //should fail
 * build$ key_tool_ed25519 --verify test3.file pub_new.bin --embeded\
 * @endcode
 *
 * <B>`test_digital_signature` </B>
 * @code
 * build$ test_digital_signature --genrsakey new
 * build$ test_digital_signature --genrsakey new2
 *
 * build$ test_digital_signature --sign test.file new_private.txt new.sign
 * build$ test_digital_signature --sign test2.file new_private.txt new2.sign
 *
 * //should get pass(no return)
 * build$ test_digital_signature --verifysign test.file new_public.txt new.sign
 * build$ test_digital_signature --verifysign test2.file new_public.txt new2.sign
 *
 * build$ test_digital_signature --verifysign test.file new_public.bin new.sign --binkey
 * build$ test_digital_signature --verifysign test2.file new_public.bin new2.sign --binkey
 *
 * //should get failed([error]: verify_signature failed, ret -7)
 * build$ test_digital_signature --verifysign test.file new_public.txt new2.sign
 * build$ test_digital_signature --verifysign test.file new2_public.txt new.sign 
 * build$ test_digital_signature --verifysign test2.file new_public.txt new.sign
 *
 * build$ test_digital_signature --verifysign test.file new_public.bin new2.sign --binkey
 * build$ test_digital_signature --verifysign test.file new2_public.bin new.sign --binkey
 * build$ test_digital_signature --verifysign test2.file new_public.bin new.sign --binkey
 *
 * build$ cp test2.file test3.file
 * build$ test_digital_signature --sign test3.file new_private.txt --embeded
 * build$ test_digital_signature --verifysign test3.file new_public.txt --embeded
 * build$ test_digital_signature --verifysign test3.file new_public.bin  --embeded --binkey
 *
 * //should fail
 * build$ test_digital_signature --verifysign test1.file new_public.txt --embeded
 * @endcode
 *
 * @anchor Crypto_Performace
 * @section test_crypto_performance 13. Crypto Performace
 * Users can test the crypto performance for Ambarella chips.
 * @subsection test_crypto_performance_openssl 13.1 Openssl Crypto Performace
 * Refer to `ambarella/security/validation/crypto_performance/openssl/help_crypto_performance.txt` for more information.
 *
 * @subsection test_crypto_performance_optee 13.2 OP-TEE Crypto Performace
 * Refer to `ambarella/security/validation/crypto_performance/optee/help_crypto_performance.txt` for more information.
 *//*!
 * @file doc_migration_guide.h
 * @brief This is a .h file for doxygen document system
 * @version 0.0
 * @date 2020-03-25
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
 */

 /*!
  * @page migration_guide Migration Guide
  *
  * @section migration_guide_history 0. Revision History
  * <table>
  * <caption id="otp_rev_history"></caption>
  * <tr><th>Version<th> Updated Date<th align="left"> Modification
  * <tr><td>0.0.1<td>20221118<td> Initial Version
  * </table>
  *
  * - - - -
  *
  * @section migration_guide_introduction 1. Introduction
  * The points below aid customers through the migration process from CV2x to CV5x / CV7x / CV3.
  *
  * - - - -
  *
  * @section key_alg 2. Key Algorithm
  * In CV2x, Ambaella uses 'RSA2048 + SHA256' for secure boot. For secure enhancement, Ambaella uses 'ED25519 + SHA512' for secure boot in CV5x / CV7x / CV3.
  * Due to the cryptography algorithm upgrade, there're some corresponding changes, such as key size and key slot number, key tools, and remote procedure call (RPC) toolkit version.
  *
  * - - - -
  *
  * @section pub_key 3. Public Key Slot in OTP
  * In CV2x, one-time programmable (OTP) can store three key pairs. In CV5x / CV7x / CV3, OTP can store sixteen key pairs;thus this is a capability enhancement.
  *
  * - - - -
  *
  * @section poc6 4. POC[6] Behavior
  * Due to changes in the key selection approach, Ambarella has introduced a new bootstrapper (BST): "BST with a binary header, which includes key index", and "BST without binary header".
  * To maintain compatibility with the original BST header, the current design is as follows: when secure boot is enabled, ROM code will treat that the BST has a header; when secure boot is disabled, ROM code will treat the BST has no header.
  * If customers choose secure boot firmware (FW), POC[6] must be always <B>ON</B>.
  * <B>POC[6] is unable to 'toggle secure boot on/off' unlike CV2x. Because secure USB boot mode is available when secure boot is enabled, users can use USB boot to flash new FW. Secure boot is not required to be turned off (POC[6] does not need to be pulled off)</B>.
  *
  * - - - -
  *
  * @section sec_usb_boot 5. Secure USB Boot
  * When secure boot is enabled on CV5x / CV7x / CV3, <B>USB boot mode is still available</B> (UST also has a signature).
  * If costumers want to disable secure USB boot, test_pogram_otp (firmware with TrustZone) or test_otp (firmware without TrustZone) can be used:
  * @code
  * #test_program_otp --dissecureusbboot
  * @endcode
  * or,
  * @code
  * #test_otp -dissecureusbboot
  * @endcode
  *
  * Since secure USB boot also has signature protection, it's <B>NOT</B> recommended to disable this feature, secure USB boot can be used as a recovery mode in RMA process.
  *
  * - - - -
  *
  * @section key_program 6. Key Program
  * In CV5x / CV7x / CV3, secure boot will only take effect after "all key locked". <B>Customers must write all public keys into OTP and lock them once</B>.
  *
  * If customers use the RPC approach, the remote server changed from tz_dev_server to tz_dev_server_v2, and the usage is the same (tz_dev_server_v2 <db> <portnum_string> [--autoapprove] [--maxaccount %d]).
  *
  * Below are the steps to program keys in CV5x / CV7x / CV3 (step 2 and 3 are additional steps with the RPC server):
  * 1.  Generate sixteen key pairs (use key_tool_ed25519 in <tt>ambarella/packages/security/key_tools/prebuild/key_tool_ed25519</tt>)
  * 2.  Name key0 (the first key used for the firmware) as pri_rot.bin and copy it to the RPC server's folder
  * 3.  Set up server and daemon (refer to <tt>ambarella/packages/security/build/trustzone_secure_boot_toolkit_help.txt</tt>)
  * 4.  Compile the firmware
  * 5.  Program sixteen keys into OTP and lock them
  * 6.  Program the firmware
  *
  * If root of trust (RoT) key revocation is required, the key index in FW and RoT key at the server side must always match.
  * For example, the process is as shown: replace nth pri_rot.bin at the server side, restart the server, change BST's key index to nth and recompile the SDK.
  */


