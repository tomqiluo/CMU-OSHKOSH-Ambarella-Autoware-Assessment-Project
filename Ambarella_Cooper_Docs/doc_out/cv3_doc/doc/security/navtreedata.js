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
  [ "Security", "index.html", [
    [ "Overview", "dc/de9/security_overview.html", [
      [ "1. System Security Solution", "dc/de9/security_overview.html#sec_solution", [
        [ "1.1 Pan Shi Security Features", "dc/de9/security_overview.html#sec_related_sec_features", null ]
      ] ],
      [ "2. Security Software Hierarchy", "dc/de9/security_overview.html#sec_sw_hierarchy", null ],
      [ "3. Introduction to Partitions", "dc/de9/security_overview.html#partitions", null ]
    ] ],
    [ "System Integrity Protection", "df/d7d/sys_integrity_protection.html", [
      [ "1. Secure Boot by Built-In Hardware Engine", "df/d7d/sys_integrity_protection.html#sec_boot", [
        [ "1.1 Authentication Chain", "df/d7d/sys_integrity_protection.html#auth_chain", null ],
        [ "1.2 Chain of Trust", "df/d7d/sys_integrity_protection.html#cot", null ],
        [ "1.3 Chosen Cryptography Algorithms", "df/d7d/sys_integrity_protection.html#chose_crypt_alg", null ],
        [ "1.4 System Memory Layout", "df/d7d/sys_integrity_protection.html#mem_layout", [
          [ "1.4.1 With Arm TrustZone", "df/d7d/sys_integrity_protection.html#mem_layout_with_tz", null ],
          [ "1.4.2 Without Arm TrustZone", "df/d7d/sys_integrity_protection.html#mem_layout_without_tz", null ]
        ] ],
        [ "1.5 User Guide", "df/d7d/sys_integrity_protection.html#sec_boot_user_guide", null ]
      ] ],
      [ "2. Secure Over the Air (OTA)", "df/d7d/sys_integrity_protection.html#sec_ota", [
        [ "2.1. Online Upgrade", "df/d7d/sys_integrity_protection.html#online_upgrade", [
          [ "2.1.1 Partition Locations with Secure Boot Enabled", "df/d7d/sys_integrity_protection.html#partition_with_sec_boot_on", null ],
          [ "2.1.2 Enable the Upgrade Tool", "df/d7d/sys_integrity_protection.html#enable_upgrade_tool", null ],
          [ "2.1.3 Upgrade the Partition on Board", "df/d7d/sys_integrity_protection.html#upgrade_partition_on_board", null ]
        ] ],
        [ "2.2 Rescue Mode", "df/d7d/sys_integrity_protection.html#rescue_mode", [
          [ "2.2.1 Rescue Mode with External MCU", "df/d7d/sys_integrity_protection.html#rescue_mode_with_mcu", null ],
          [ "2.2.2 Rescue Mode without External MCU (V2)", "df/d7d/sys_integrity_protection.html#rescue_mode_without_mcu", null ]
        ] ]
      ] ],
      [ "3. Linux Dm-verity", "df/d7d/sys_integrity_protection.html#dm_verity", [
        [ "3.1 Set Up dm-verity on the Ambarella Platform", "df/d7d/sys_integrity_protection.html#set_up_dm_verity", null ],
        [ "3.2 Use Dm-verity", "df/d7d/sys_integrity_protection.html#use_dm_verity", null ],
        [ "3.3 Enable Dm-verity with Signed DTB", "df/d7d/sys_integrity_protection.html#dm_verity_with_sign_dtb", null ],
        [ "3.4 Dm-verity on NAND", "df/d7d/sys_integrity_protection.html#dm_verity_on_nand", [
          [ "3.4.1 Dm-verity for SquashFS with Initramfs", "df/d7d/sys_integrity_protection.html#dm_verity_for_squashFS_with_initramfs", null ],
          [ "3.4.2 Dm-verity for SquashFS without Initramfs", "df/d7d/sys_integrity_protection.html#dm_verity_for_squashfs_without_initramfs", null ]
        ] ]
      ] ]
    ] ],
    [ "System Reinforcement", "db/d12/system_reinforcement.html", [
      [ "1. Secure Enhanced Bootloader", "db/d12/system_reinforcement.html#SEBLD", [
        [ "1.1 Prepare the Key Pair", "db/d12/system_reinforcement.html#perpare_sebld_key", [
          [ "1.1.2 Use an Existing Key Pair", "db/d12/system_reinforcement.html#use_an_existing_key_pair", null ]
        ] ],
        [ "1.2 Prepare the Configuration Partition", "db/d12/system_reinforcement.html#perpare_cfg_partition", null ],
        [ "1.3 Prepare Android Fastboot", "db/d12/system_reinforcement.html#prepare_android_fastboot", [
          [ "1.3.1 Get Android Fastboot Tools", "db/d12/system_reinforcement.html#get_android_fastboot_tools", null ],
          [ "1.3.2 Enter Android Fastboot on the EVK", "db/d12/system_reinforcement.html#enter_android_fastboot", null ]
        ] ],
        [ "1.4 User Guide", "db/d12/system_reinforcement.html#sebld_user_guide", [
          [ "1.4.1 Via AMBoot Console", "db/d12/system_reinforcement.html#sebld_via_amboot_console", null ],
          [ "1.4.2 Via Android Fastboot", "db/d12/system_reinforcement.html#sebld_via_android_fastboot", null ]
        ] ]
      ] ],
      [ "2. Secure Enhanced Linux (SELinux)", "db/d12/system_reinforcement.html#selinux", [
        [ "2.1 SELinux Overview", "db/d12/system_reinforcement.html#selinux_overview", [
          [ "2.1.1 Introduction", "db/d12/system_reinforcement.html#selinux_introduction", null ],
          [ "2.1.2 Core SELinux Components", "db/d12/system_reinforcement.html#core_selinux_components", null ],
          [ "2.1.3 Mandatory Access Control", "db/d12/system_reinforcement.html#mandatory_access_control", null ],
          [ "2.1.4 SELinux Users", "db/d12/system_reinforcement.html#selinux_users", null ],
          [ "2.1.5 Role-Based Access Control", "db/d12/system_reinforcement.html#rbac", null ],
          [ "2.1.7 Subjects", "db/d12/system_reinforcement.html#selinux_subjects", null ],
          [ "2.1.8 Objects", "db/d12/system_reinforcement.html#selinux_objects", null ],
          [ "2.1.9 SELinux Modes", "db/d12/system_reinforcement.html#selinux_modes", null ],
          [ "2.1.10 Auditing SELinux Events", "db/d12/system_reinforcement.html#auditing_selinux_events", null ]
        ] ],
        [ "2.2 SELinux User Guide for Ambarella", "db/d12/system_reinforcement.html#selinux_amba_user_guide", [
          [ "2.2.1 Ambarella SELinux Support", "db/d12/system_reinforcement.html#amba_selinux_support", null ],
          [ "2.2.2 Enable SELinux on the Ambarella Platform", "db/d12/system_reinforcement.html#enable_selinux_on_amba", null ],
          [ "2.2.3 SELinux Commands", "db/d12/system_reinforcement.html#selinux_command", null ],
          [ "2.2.4 SELinux Configuration Files", "db/d12/system_reinforcement.html#selinux_config_files", null ],
          [ "2.2.5 Policy Configuration Files", "db/d12/system_reinforcement.html#policy_config_files", null ],
          [ "2.2.6 Customize Policy", "db/d12/system_reinforcement.html#customize_policy", null ]
        ] ]
      ] ],
      [ "3. TEE and Arm TrustZone", "db/d12/system_reinforcement.html#tee_and_trustzone", [
        [ "3.1. Arm® TrustZone®", "db/d12/system_reinforcement.html#arm_trustzone", null ],
        [ "3.2. Arm Trusted Firmware", "db/d12/system_reinforcement.html#arm_trusted_firmware", null ],
        [ "3.3. OP-TEE", "db/d12/system_reinforcement.html#op_tee", null ],
        [ "3.4. Trusted Application and Client Application", "db/d12/system_reinforcement.html#ta_and_ca", null ],
        [ "3.5 Source Code Location in the SDK Package", "db/d12/system_reinforcement.html#source_code_location_in_sdk", null ]
      ] ],
      [ "4. Anti-Rollback", "db/d12/system_reinforcement.html#anti_rollback", null ],
      [ "5. Disable the Hardware Debug Port", "db/d12/system_reinforcement.html#disable_hw_debug_port", null ],
      [ "6. Disable the Non-Secure Protocol / Port", "db/d12/system_reinforcement.html#disable_no_secure_protocol", null ],
      [ "7. Buffer Overflow Attack Resistance", "db/d12/system_reinforcement.html#buffer_overflow_attack_resistance", [
        [ "7.1. Address Space Layout Randomization", "db/d12/system_reinforcement.html#add_space_layout_randomization", null ],
        [ "7.2. Position Independent Executable", "db/d12/system_reinforcement.html#pos_independent_executable", null ],
        [ "7.3. No-eXecute Protect", "db/d12/system_reinforcement.html#no_execute_protect", null ],
        [ "7.4. Stack Protector", "db/d12/system_reinforcement.html#stack_protector", null ],
        [ "7.5. FORTIFY", "db/d12/system_reinforcement.html#fortify", null ],
        [ "7.6. Read-Only Relocation", "db/d12/system_reinforcement.html#read_only_relocation", null ]
      ] ],
      [ "8. DRAM Scrambling", "db/d12/system_reinforcement.html#dram_scrambling", null ],
      [ "9. CVE Fix Strategy", "db/d12/system_reinforcement.html#cve_fix_strategy", null ]
    ] ],
    [ "Data Storage Protection", "d1/d37/data_storage_protection.html", [
      [ "1. Data Partition Encryption", "d1/d37/data_storage_protection.html#data_part_enc", [
        [ "1.1 dm-crypt", "d1/d37/data_storage_protection.html#dm_crypt", [
          [ "1.1.1 Set Up dm-crypt on the Ambarella Platform", "d1/d37/data_storage_protection.html#setup_dm_crypt_on_amba_platform", null ],
          [ "1.1.2 Use Cryptsetup to Run dm-crypt", "d1/d37/data_storage_protection.html#use_cryptosetup_to_run_dm_crypt", null ]
        ] ]
      ] ],
      [ "2. Data Encryption Protection", "d1/d37/data_storage_protection.html#data_enc_protection", [
        [ "2.1 Data Encryption Algorithm", "d1/d37/data_storage_protection.html#data_enc_alg", null ],
        [ "2.2 Cryptography Library", "d1/d37/data_storage_protection.html#crypto_lib", null ],
        [ "2.3 Lightweight Cryptography Library in Linux", "d1/d37/data_storage_protection.html#lightweight_crypto_lib", null ],
        [ "2.4 Native AES with Crypto Extension Instructions in Linux", "d1/d37/data_storage_protection.html#native_aes_with_crypto_extension", null ],
        [ "2.5 Mbed TLS in ATF", "d1/d37/data_storage_protection.html#mbed_tls_in_atf", null ]
      ] ],
      [ "3. Secure Storage", "d1/d37/data_storage_protection.html#secure_storage", [
        [ "3.1 Data at Rest Protection", "d1/d37/data_storage_protection.html#data_at_rest_protection", null ],
        [ "3.2 Data Protection by Passphrase", "d1/d37/data_storage_protection.html#data_protection_by_passphrase", null ]
      ] ]
    ] ],
    [ "Data Transfer Protection", "df/d19/data_transfer_protection.html", [
      [ "1. SSL and TLS", "df/d19/data_transfer_protection.html#ssl_and_tls", [
        [ "1.1 SSL Protocols", "df/d19/data_transfer_protection.html#ssl_protocols", [
          [ "1.1.2 SSL Record Protocol", "df/d19/data_transfer_protection.html#ssl_record_protocol", null ],
          [ "1.1.3 Handshake Protocol", "df/d19/data_transfer_protection.html#handshake_protocol", null ],
          [ "1.1.4 Change-Cipher Protocol", "df/d19/data_transfer_protection.html#change_cipher_protocol", null ],
          [ "1.1.5 Alert Protocol", "df/d19/data_transfer_protection.html#alert_protocol", null ]
        ] ],
        [ "1.2 SSL Work Flow", "df/d19/data_transfer_protection.html#ssl_work_flow", null ]
      ] ],
      [ "2. TLS Solutions in the Ambarella SDK", "df/d19/data_transfer_protection.html#tls_solution_in_amba", [
        [ "2.1 TLS Client in Normal World", "df/d19/data_transfer_protection.html#tls_client_in_normal_world", null ]
      ] ],
      [ "3. Secure Connection in CVflow®", "df/d19/data_transfer_protection.html#secure_connection_in_cvflow", null ]
    ] ],
    [ "Intellectual Property Protection", "d0/dfd/system_integrity_protection.html", [
      [ "1. Unit License Protection", "d0/dfd/system_integrity_protection.html#ulp", [
        [ "1.1 Non-Forgeable Unique ID", "d0/dfd/system_integrity_protection.html#non_forgeable_uuid", null ],
        [ "1.2 Unit License Protection Concept", "d0/dfd/system_integrity_protection.html#ulp_concept", null ],
        [ "1.4 License Deployment Process", "d0/dfd/system_integrity_protection.html#license_deployment_process", null ],
        [ "1.5 License Verification Process", "d0/dfd/system_integrity_protection.html#license_verification_process", [
          [ "1.5.1 Local License Verification Process", "d0/dfd/system_integrity_protection.html#local_license_verification_process", null ],
          [ "1.5.2 Non-Forgeable Unique ID for Online Verification", "d0/dfd/system_integrity_protection.html#non_forgable_uuid", null ],
          [ "1.5.3 Comparing with Other Unit License Approaches", "d0/dfd/system_integrity_protection.html#compare_with_ither_ul", null ]
        ] ],
        [ "1.6 On-Chip Software Hierarchy", "d0/dfd/system_integrity_protection.html#on_chip_sw_hierarchy", null ],
        [ "1.7 Software Hierarchy on the Linux PC", "d0/dfd/system_integrity_protection.html#sw_hierarchy_on_linux_pc", null ],
        [ "1.8 Support for Multiple Customers", "d0/dfd/system_integrity_protection.html#muti_customers_support", null ]
      ] ],
      [ "2. Unit License Protection User Guide", "d0/dfd/system_integrity_protection.html#ulp_user_guide", [
        [ "2.1 Compile Unit License Protection Sample Code", "d0/dfd/system_integrity_protection.html#compile_ulp_sample_code", [
          [ "2.1.1 Compile Sample Code on the SoC", "d0/dfd/system_integrity_protection.html#sample_code_on_pc", null ],
          [ "2.1.2 Prerequisites", "d0/dfd/system_integrity_protection.html#ulp_prerequisites", null ],
          [ "2.1.3 Compile Sample Code on Linux (Ubuntu)", "d0/dfd/system_integrity_protection.html#sample_code_on_linux", null ]
        ] ],
        [ "2.2 Launch from Scratch User Guide", "d0/dfd/system_integrity_protection.html#launch_from_scratch", [
          [ "2.2.1 Compile and Install Configurations", "d0/dfd/system_integrity_protection.html#compile_installl_config", null ],
          [ "2.2.2 Launch the License Server", "d0/dfd/system_integrity_protection.html#launch_license_server", null ],
          [ "2.2.3 Launch the Deployment Tool", "d0/dfd/system_integrity_protection.html#launch_deployment_tool", null ],
          [ "2.2.4 Approve an Account", "d0/dfd/system_integrity_protection.html#approve_account", null ],
          [ "2.2.5 Run the Provisioning Tool to Deploy the License", "d0/dfd/system_integrity_protection.html#run_provision_tool_to_deploy_license", null ]
        ] ],
        [ "2.3 Run Sample Code to Check the License", "d0/dfd/system_integrity_protection.html#run_sample_code_to_check_license", null ],
        [ "2.4 Quick Launch User Guide", "d0/dfd/system_integrity_protection.html#quick_launch_user_guide", [
          [ "2.4.1 Compile and Install the Pre-Set Test Files", "d0/dfd/system_integrity_protection.html#compille_and_install_pre_set_test_fille", null ],
          [ "2.4.3 Launch the Deployment Tool", "d0/dfd/system_integrity_protection.html#launch_dev_tool", null ],
          [ "2.4.5 Run the Provisioning Tool to Deploy the License", "d0/dfd/system_integrity_protection.html#run_provision_tool_to_deplloy_license", null ],
          [ "2.4.6 Run the Sample Code to Check the License", "d0/dfd/system_integrity_protection.html#run_sample_code_to_check_the_license", null ]
        ] ],
        [ "2.5 Configurations for Programs and the Database", "d0/dfd/system_integrity_protection.html#config_for_programs_and_database", [
          [ "2.5.1 License Server Configuration", "d0/dfd/system_integrity_protection.html#license_server_config", null ],
          [ "2.5.2 Deployment Tool Configuration", "d0/dfd/system_integrity_protection.html#deployment_tool_config", null ],
          [ "2.5.3 Provisioning Tool Configuration", "d0/dfd/system_integrity_protection.html#provisioning_tool_config", null ],
          [ "2.5.4 Database Configuration", "d0/dfd/system_integrity_protection.html#database_config", null ],
          [ "2.5.5 Metadata", "d0/dfd/system_integrity_protection.html#metadata", null ]
        ] ],
        [ "2.6 Offline Issuer", "d0/dfd/system_integrity_protection.html#offline_issuer", null ]
      ] ],
      [ "3. Neural Network Model Protection", "d0/dfd/system_integrity_protection.html#neural_network_model_protection", [
        [ "3.1 NN Model Protection", "d0/dfd/system_integrity_protection.html#NN_model_protection", null ],
        [ "3.2 Deployment Process", "d0/dfd/system_integrity_protection.html#deployment_process", null ],
        [ "3.3 Online Upgrade Process", "d0/dfd/system_integrity_protection.html#online_upgrade_process", null ],
        [ "3.4 Device Working Process", "d0/dfd/system_integrity_protection.html#device_working_process", null ],
        [ "3.5 Software Hierarchy on Chip", "d0/dfd/system_integrity_protection.html#sw_hierarchy_on_chip", null ],
        [ "3.6 Software Hierarchy on Linux PC", "d0/dfd/system_integrity_protection.html#sw_hierarchy_on_pc", null ],
        [ "3.7 Support Multiple Customers", "d0/dfd/system_integrity_protection.html#support_muti_customers", null ]
      ] ],
      [ "4. Neural Network Model Protection User Guide", "d0/dfd/system_integrity_protection.html#neural_network_model_protections_user_guide", [
        [ "4.1 Compile NN Model Protection Sample Code", "d0/dfd/system_integrity_protection.html#compile_nn_model_protection_code", [
          [ "4.1.1 Compile Sample Code on the SoC", "d0/dfd/system_integrity_protection.html#compile_nmp_sample_code_on_soc", null ],
          [ "4.1.2 Compile Sample Code on Linux (Ubuntu)", "d0/dfd/system_integrity_protection.html#compile_nmp_sample_code_on_linux", null ]
        ] ],
        [ "4.2 Derive the PEK and Encrypt Model", "d0/dfd/system_integrity_protection.html#derive_pek_and_enc_model", [
          [ "4.2.1 Derive the PEK", "d0/dfd/system_integrity_protection.html#dervie_pek", null ]
        ] ],
        [ "4.2.2 Encrypt Model with PEK", "d0/dfd/system_integrity_protection.html#enc_model_with_pek", null ],
        [ "4.3 Launch-from-Scratch User Guide", "d0/dfd/system_integrity_protection.html#nmp_launch_from_scratch_user_guide", [
          [ "4.3.1 Compile and Install Configurations", "d0/dfd/system_integrity_protection.html#nmp_scratch_compile_and_install_config", null ],
          [ "4.3.2 Launch the License Server", "d0/dfd/system_integrity_protection.html#nmp_launch_license_server", null ],
          [ "4.3.3 Launch the Deployment Tool", "d0/dfd/system_integrity_protection.html#nmp_launch_deployment_tool", null ],
          [ "4.3.4 Approve An Account", "d0/dfd/system_integrity_protection.html#nmp_approve_account", null ],
          [ "4.3.5 Run the Provisioning Tool to Deploy PEK", "d0/dfd/system_integrity_protection.html#nmp_run_provisiong_tool_to_deploy_pek", null ]
        ] ],
        [ "4.4 Quick-Launch User Guide", "d0/dfd/system_integrity_protection.html#nmp_quick_launch_user_guide", [
          [ "4.4.1 Compile and Install the Pre-Set Test Files", "d0/dfd/system_integrity_protection.html#nmp_quick_compile_install_preset_test_file", null ],
          [ "4.4.2 Launch the License Server", "d0/dfd/system_integrity_protection.html#nmp_quick_launch_license_server", null ],
          [ "4.3.3 Launch the Deployment Tool", "d0/dfd/system_integrity_protection.html#nmp_quick_launch_deployment_tool", null ],
          [ "4.3.4 Approve An Account", "d0/dfd/system_integrity_protection.html#nmp_quick_approve_account", null ],
          [ "4.3.5 Run the Provisioning Tool to Deploy PEK", "d0/dfd/system_integrity_protection.html#nmp_quick_run_provisiong_tool_to_deploy_pek", null ]
        ] ]
      ] ],
      [ "5. ULP NMP Key Tools", "d0/dfd/system_integrity_protection.html#ulp_nmp_key_tool", [
        [ "5.1 Change Key Passphrase", "d0/dfd/system_integrity_protection.html#change_key_passphrase", null ]
      ] ]
    ] ],
    [ "User Privacy Protection", "d3/d97/user_privacy_protection.html", null ],
    [ "Secure Hardware", "da/d0f/secure_hardware.html", [
      [ "0. Revision History", "da/d0f/secure_hardware.html#otp_history", null ],
      [ "1. One-Time Programmable", "da/d0f/secure_hardware.html#otp", [
        [ "1.1. OTP Data Layout", "da/d0f/secure_hardware.html#otp_layout", null ],
        [ "1.2. Program OTP", "da/d0f/secure_hardware.html#program_otp", null ],
        [ "1.3. Typical Scenarios for Each OTP Region", "da/d0f/secure_hardware.html#otp_scenarios", null ]
      ] ],
      [ "2. Unique ID", "da/d0f/secure_hardware.html#uuid", [
        [ "2.1 Read DSP-Unique ID from IOCTL", "da/d0f/secure_hardware.html#read_dsp_uuid", null ],
        [ "2.2 Read the Ambarella Unique ID with TrustZone Enabled", "da/d0f/secure_hardware.html#read_amba_uuid_with_tz", null ],
        [ "2.3 Read the Ambarella Unique ID with TrustZone Disabled", "da/d0f/secure_hardware.html#read_amba_uuid_without_tz", null ]
      ] ],
      [ "3. Monotonic Counter", "da/d0f/secure_hardware.html#mono_counter", null ],
      [ "4. True Random Number Generator", "da/d0f/secure_hardware.html#TRNG", null ],
      [ "5. Disable JTAG and USB Boot", "da/d0f/secure_hardware.html#disable_jtag_usb_boot", null ]
    ] ],
    [ "Key Management", "db/dfb/key_management.html", [
      [ "1. Public Keys on the Device", "db/dfb/key_management.html#pub_key_on_dev", null ],
      [ "2. Private Keys in Local (Default Approach)", "db/dfb/key_management.html#pri_key_in_local", null ],
      [ "3. Private Keys at the Remote Server (RPC Toolkit)", "db/dfb/key_management.html#pri_key_rpc", null ],
      [ "4. Revoking the RoT Key", "db/dfb/key_management.html#revoke_rot_key", null ],
      [ "5. User Guide", "db/dfb/key_management.html#key_management_user_guide", [
        [ "5.1. Preparing the Key Pairs", "db/dfb/key_management.html#prepare_key_pairs", [
          [ "5.1.1 Generating New Keys for the Local Approach (Optional)", "db/dfb/key_management.html#generate_new_key_pairs", null ],
          [ "5.1.2 Generating New Keys for the RPC Approach (Optional)", "db/dfb/key_management.html#generate_new_key_pairs_for_rpc", null ]
        ] ],
        [ "5.2 Specify RoT Key Index in BST Header", "db/dfb/key_management.html#specify_rot_key_index", null ],
        [ "5.3 Compiling the SDK with a Secure Boot", "db/dfb/key_management.html#compile_sdk_with_secure_boot", null ],
        [ "5.4 Setting Up the RPC Environment", "db/dfb/key_management.html#set_up_rpc_env", [
          [ "5.4.1 Running the Development Server", "db/dfb/key_management.html#run_dev_server", null ],
          [ "5.4.2 Running the Development Daemon", "db/dfb/key_management.html#run_dev_daemon", null ]
        ] ],
        [ "5.5 Programming a Public Key into OTP", "db/dfb/key_management.html#program_public_key_into_otp", null ],
        [ "5.6 Enabling Secure Boot", "db/dfb/key_management.html#enable_sec_boot", [
          [ "5.6.1 Enabling Boot with a POC Pin", "db/dfb/key_management.html#enable_sec_boot_with_poc_pin", null ],
          [ "5.6.2 Permanently Setting Secure Boot", "db/dfb/key_management.html#permanently_set_se_boot", null ]
        ] ],
        [ "5.7 Running Secure Boot", "db/dfb/key_management.html#run_se_boot", null ],
        [ "5.8 RoT Key Revocation", "db/dfb/key_management.html#rot_revoke", null ]
      ] ]
    ] ],
    [ "Crypto Performance", "d4/dc0/crypto_performance.html", null ],
    [ "Design Guide", "db/df1/design_guide.html", [
      [ "1. Development Board", "db/df1/design_guide.html#for_dev_board", null ],
      [ "2. Hardware Schematic Diagram", "db/df1/design_guide.html#hw_schematic_diag", null ],
      [ "3. Mass-Production Process", "db/df1/design_guide.html#mass_production_process", null ]
    ] ],
    [ "Validation Guide", "d2/d1d/security_validation_guide.html", [
      [ "0. Revision History", "d2/d1d/security_validation_guide.html#validation_guide_history", null ],
      [ "1. Secure Boot", "d2/d1d/security_validation_guide.html#test_secure_boot", [
        [ "1.1 Generate Keys for Secure Boot", "d2/d1d/security_validation_guide.html#generate_secure_boot_keys", [
          [ "1.1.1 Generate Keys for the Local Approach", "d2/d1d/security_validation_guide.html#generate_secure_boot_keys_local", null ],
          [ "1.1.2 Generate Keys for the RPC Approach", "d2/d1d/security_validation_guide.html#generate_secure_boot_keys_rpc", null ]
        ] ],
        [ "1.2 Compile the SDK with Secure Boot", "d2/d1d/security_validation_guide.html#validation_compile_sdk_with_secure_boot", [
          [ "1.2.1 Using Ambarella RPC Toolkits", "d2/d1d/security_validation_guide.html#compile_secure_boot_with_rpc", null ],
          [ "1.2.2 Using AWS KMS", "d2/d1d/security_validation_guide.html#compile_secure_boot_with_aws_kms", null ],
          [ "1.2.3 Using Other Key Management Services", "d2/d1d/security_validation_guide.html#compile_secure_boot_with_other_key_management_service", null ]
        ] ],
        [ "1.3 Programming a Public Key into OTP", "d2/d1d/security_validation_guide.html#validation_program_public_key_into_otp", null ],
        [ "1.4 Enabling Secure Boot", "d2/d1d/security_validation_guide.html#validation_enable_sec_boot", null ],
        [ "1.5 Running Secure Boot", "d2/d1d/security_validation_guide.html#validation_run_se_boot", null ],
        [ "1.6 Test Suite For Secure Boot", "d2/d1d/security_validation_guide.html#test_suite_for_secure_boot", [
          [ "1.6.1 Test Suite For Authentication Chain", "d2/d1d/security_validation_guide.html#test_suite_secure_boot_auth_chain", null ],
          [ "1.6.2 Test Suite For RPC Toolkit", "d2/d1d/security_validation_guide.html#test_suite_rpc_toolkit", null ],
          [ "1.6.3 Test Suite For Key Revocation", "d2/d1d/security_validation_guide.html#test_suite_key_revocation", null ]
        ] ]
      ] ],
      [ "2. OP-TEE", "d2/d1d/security_validation_guide.html#test_optee", null ],
      [ "3. Secure Over The Air", "d2/d1d/security_validation_guide.html#test_ota", [
        [ "3.1 Online Upgrade", "d2/d1d/security_validation_guide.html#test_online_upgrade", null ],
        [ "3.2 Rescue Mode", "d2/d1d/security_validation_guide.html#test_rescue_mode", null ],
        [ "3.3 Linux Dm-verity", "d2/d1d/security_validation_guide.html#test_dm_verity", null ]
      ] ],
      [ "4. Secure Enhanced Bootloader", "d2/d1d/security_validation_guide.html#test_sebld", null ],
      [ "5. Dm Crpypt", "d2/d1d/security_validation_guide.html#test_dm_crypt", null ],
      [ "6. Data Encryption", "d2/d1d/security_validation_guide.html#test_data_encryption", [
        [ "6.1 Data Encryption in OP-TEE", "d2/d1d/security_validation_guide.html#data_encryption_optee", null ]
      ] ],
      [ "7. Secure Storage", "d2/d1d/security_validation_guide.html#test_secure_storage", null ],
      [ "8. Unit License Protection", "d2/d1d/security_validation_guide.html#test_ulp", null ],
      [ "9. Neural Network Model Protection", "d2/d1d/security_validation_guide.html#test_nmp", null ],
      [ "10. OTP", "d2/d1d/security_validation_guide.html#test_otp", null ],
      [ "11. Random Number Generator", "d2/d1d/security_validation_guide.html#test_rng", null ],
      [ "12. Key tools", "d2/d1d/security_validation_guide.html#test_key_tools", null ],
      [ "13. Crypto Performace", "d2/d1d/security_validation_guide.html#test_crypto_performance", [
        [ "13.1 Openssl Crypto Performace", "d2/d1d/security_validation_guide.html#test_crypto_performance_openssl", null ],
        [ "13.2 OP-TEE Crypto Performace", "d2/d1d/security_validation_guide.html#test_crypto_performance_optee", null ]
      ] ]
    ] ],
    [ "Migration Guide", "d2/dad/migration_guide.html", [
      [ "0. Revision History", "d2/dad/migration_guide.html#migration_guide_history", null ],
      [ "1. Introduction", "d2/dad/migration_guide.html#migration_guide_introduction", null ],
      [ "2. Key Algorithm", "d2/dad/migration_guide.html#key_alg", null ],
      [ "3. Public Key Slot in OTP", "d2/dad/migration_guide.html#pub_key", null ],
      [ "4. POC[6] Behavior", "d2/dad/migration_guide.html#poc6", null ],
      [ "5. Secure USB Boot", "d2/dad/migration_guide.html#sec_usb_boot", null ],
      [ "6. Key Program", "d2/dad/migration_guide.html#key_program", null ]
    ] ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"d0/dfd/system_integrity_protection.html",
"df/d7d/sys_integrity_protection.html#upgrade_partition_on_board"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';