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
  [ "Peripherals", "index.html", [
    [ "Audio", "dc/dfd/si_audio.html", [
      [ "1. Audio Architecture", "dc/dfd/si_audio.html#audio_arch", [
        [ "1.1 Audio Codec Block Diagram", "dc/dfd/si_audio.html#audio_codec_block_diagram", null ],
        [ "1.2 Advanced Linux Sound Architecture (ALSA)", "dc/dfd/si_audio.html#si_alsa_architecture", null ],
        [ "1.3 aplay / arecord", "dc/dfd/si_audio.html#aplay_arecord", null ]
      ] ],
      [ "2. ALSA Library", "dc/dfd/si_audio.html#audio_alsa", [
        [ "2.1 Install ALSA Driver", "dc/dfd/si_audio.html#install_alsa_dri_ver", null ],
        [ "2.2 Develop ALSA Applications", "dc/dfd/si_audio.html#develop_alsa_applications", null ]
      ] ],
      [ "3. AAC Encode Library", "dc/dfd/si_audio.html#audio_aac_enc", [
        [ "3.1 Data Structure", "dc/dfd/si_audio.html#data_structure", null ],
        [ "3.2 APIs", "dc/dfd/si_audio.html#apis", null ],
        [ "3.3 Sample Code", "dc/dfd/si_audio.html#sample_code", null ]
      ] ],
      [ "4. AAC Decode Library", "dc/dfd/si_audio.html#audio_aac_dec", [
        [ "4.1 Data Structure", "dc/dfd/si_audio.html#decode_data_structure", null ],
        [ "4.2 APIs", "dc/dfd/si_audio.html#decode_apis", null ],
        [ "4.3 Sample Code", "dc/dfd/si_audio.html#decode_sample_code", null ]
      ] ],
      [ "5. CV5x EVK with Analog and Digital MIC Support", "dc/dfd/si_audio.html#audio_mic_sup", [
        [ "5.1 CV52_Zr/CV5_Timn", "dc/dfd/si_audio.html#cv52_zr_and_cv5_Timn", null ]
      ] ]
    ] ],
    [ "File System", "d4/d64/si_fs.html", [
      [ "1. UBIFS (Recommended)", "d4/d64/si_fs.html#fs_ubi", [
        [ "1.1 Use UBIFS as Rootfs", "d4/d64/si_fs.html#ubi_rootfs", null ],
        [ "1.2 Test UBIFS", "d4/d64/si_fs.html#ubi_test", null ]
      ] ],
      [ "2. JFFS2", "d4/d64/si_fs.html#fs_jffs", [
        [ "2.1 Use JFFS2 as Rootfs", "d4/d64/si_fs.html#use_jffs2_as_rootfs", null ],
        [ "2.2 Test JFFS2", "d4/d64/si_fs.html#test_jffs2", null ]
      ] ],
      [ "3. Ext4", "d4/d64/si_fs.html#fs_ext4", [
        [ "3.1 Use Ext4 as Rootfs", "d4/d64/si_fs.html#use_ext4_as_rootfs", null ]
      ] ],
      [ "4. ExFAT", "d4/d64/si_fs.html#fs_exfat", [
        [ "4.1 Enable ExFAT", "d4/d64/si_fs.html#use_exfat_for_flash_cards", null ]
      ] ]
    ] ],
    [ "NAND", "dc/dac/si_nand.html", [
      [ "1. ECC Level", "dc/dac/si_nand.html#ecc_level", null ],
      [ "2. Boot Flow", "dc/dac/si_nand.html#boot_flow", [
        [ "2.1 NAND Boot Flow: Boot Sequence", "dc/dac/si_nand.html#nand_boot_flow", null ],
        [ "2.2 NAND Boot Flow: Load Linux Kernel and File System", "dc/dac/si_nand.html#nand_boot_flow_llf", null ]
      ] ]
    ] ],
    [ "EMMC", "de/d93/si_emmc.html", [
      [ "1. Hardware Setting", "de/d93/si_emmc.html#hardware_setting", [
        [ "1.1 POC Setting", "de/d93/si_emmc.html#poc_setting", null ]
      ] ],
      [ "2. Configuration and Compile", "de/d93/si_emmc.html#configuration_and_compile", null ]
    ] ],
    [ "Debugfs", "dd/df0/si_debugfs.html", [
      [ "1. GPIO Debug", "dd/df0/si_debugfs.html#gpio_debug", null ]
    ] ],
    [ "USB", "df/d51/si_usb.html", [
      [ "1. USB Device", "df/d51/si_usb.html#usb_device", [
        [ "1.1 USB Device: USB Mass Storage", "df/d51/si_usb.html#ud_usb_mass_storage", null ],
        [ "1.2 USB Device: USB Ethernet Device", "df/d51/si_usb.html#ud_usb_ethernet_device", null ],
        [ "1.4 USB Device: USB Serial", "df/d51/si_usb.html#ud_usb_serial", null ],
        [ "1.5 Troubleshooting", "df/d51/si_usb.html#ud_troubleshooting", null ]
      ] ],
      [ "2. USB Host", "df/d51/si_usb.html#usb_host", [
        [ "2.1 USB Host: Support USB Mass Storage Device", "df/d51/si_usb.html#uh_support_usb_mass_storage_device", null ],
        [ "2.2 USB Host: Mouse / Keyboard", "df/d51/si_usb.html#uh_mouse_keyboard", null ],
        [ "2.3 USB Host: Support USB Serial Device", "df/d51/si_usb.html#uh_support_usb_serial_device", null ],
        [ "2.4 USB Host: HS Electrical Test (Eye Diagram)", "df/d51/si_usb.html#uh_support_usb_eye_diagram_testing", null ],
        [ "2.5 USB Host: Support USB UVC Camera Device", "df/d51/si_usb.html#uh_support_usb_uvc_camera_device", null ]
      ] ],
      [ "3. USB Speed", "df/d51/si_usb.html#usb_speed", null ],
      [ "4. Ambarella UVC Camera", "df/d51/si_usb.html#amba_uvc_camera", [
        [ "4.1 Specifications", "df/d51/si_usb.html#uvc_cam_specifications", null ],
        [ "4.2 Build Firmware Support UVC", "df/d51/si_usb.html#uvc_cam_build_firmware", null ],
        [ "4.3 Stream Ambarella UVC", "df/d51/si_usb.html#uvc_cam_stream_ambarella_uvc", null ],
        [ "4.4 Ambarella UVC Latency", "df/d51/si_usb.html#ud_usb_uvc_latency", null ],
        [ "4.5 Test uvc-gadget", "df/d51/si_usb.html#ud_usb_device_uvc_gadget", null ],
        [ "4.6 USB FunctionFS Device (Cooper SDK)", "df/d51/si_usb.html#ud_usb_ffs_device", null ]
      ] ]
    ] ],
    [ "SD Card", "d0/da5/si_sd_card.html", [
      [ "1. SD Slot", "d0/da5/si_sd_card.html#uvc_cam_sd_slot", null ],
      [ "2. SD Card Type", "d0/da5/si_sd_card.html#uvc_cam_sd_card_type", null ],
      [ "3. Hardware and Software Preparation", "d0/da5/si_sd_card.html#hardware_software_preparation", [
        [ "3.1 CV5 EVK", "d0/da5/si_sd_card.html#cv5_evk", null ]
      ] ],
      [ "4. Mount and Format", "d0/da5/si_sd_card.html#mount_format", [
        [ "4.1 Mount an SD Card", "d0/da5/si_sd_card.html#mount_an_sd_card", null ],
        [ "4.2 Unmount an SD Card", "d0/da5/si_sd_card.html#unmount_an_sd_card", null ]
      ] ],
      [ "5. Write Performance", "d0/da5/si_sd_card.html#write_performance", null ],
      [ "6. Boot from Rootfs in the SD Card", "d0/da5/si_sd_card.html#boot_from_rootfs_in_sd_card", null ],
      [ "7. Troubleshooting", "d0/da5/si_sd_card.html#troubleshooting", null ]
    ] ],
    [ "WiFi", "db/d30/si_wifi.html", [
      [ "1. WiFi Modules with SDIO Interface", "db/d30/si_wifi.html#wifi_with_sdio_interface", null ],
      [ "2. Compile SDK Firmware with WiFi Driver", "db/d30/si_wifi.html#wifi_compile", null ],
      [ "3. WiFi Test on the EVK Board", "db/d30/si_wifi.html#WiFi_test", null ]
    ] ],
    [ "Bluetooth", "d8/d73/si_bluetooth.html", [
      [ "1. Bluetooth with UART Interface Device", "d8/d73/si_bluetooth.html#bluetooth_with_uart_interface_device", [
        [ "1.1 BCM43340", "d8/d73/si_bluetooth.html#bluetooth_bcm43340", null ],
        [ "1.2 BCM43438", "d8/d73/si_bluetooth.html#bluetooth_bcm43438", null ]
      ] ],
      [ "2. Bluez Stack", "d8/d73/si_bluetooth.html#bluez_stack", [
        [ "2.1 Setup BT A2DP profile", "d8/d73/si_bluetooth.html#setup_bt_a2dp_profile", null ]
      ] ]
    ] ],
    [ "SPI", "da/dcf/si_spi.html", [
      [ "1 Serial Peripheral Interface Introduction", "da/dcf/si_spi.html#doc_perihperals_spi_introduciton", [
        [ "1.1 SPI Interface", "da/dcf/si_spi.html#doc_perihperals_spi_interface", null ],
        [ "1.2 SPI Mode", "da/dcf/si_spi.html#doc_perihperals_spi_mode", null ]
      ] ],
      [ "2 Ambarella SPI", "da/dcf/si_spi.html#doc_perihperals_amba_spi", [
        [ "2.1 SPI Master", "da/dcf/si_spi.html#doc_perihperals_spi_master_setup", null ],
        [ "2.2 SPI Slave", "da/dcf/si_spi.html#doc_perihperals_spi_slave_setup", null ]
      ] ]
    ] ],
    [ "I2C", "db/dc8/si_i2c.html", null ],
    [ "PCI Express", "d8/d69/pci_express.html", [
      [ "Regular Endpoint Devices", "d8/d69/pci_express.html#autotoc_md3", [
        [ "nvme_ssd NVMe SSD", "d8/d69/pci_express.html#autotoc_md4", [
          [ "Throughput Result", "d8/d69/pci_express.html#autotoc_md5", null ]
        ] ],
        [ "GPU AMD ATI GPU", "d8/d69/pci_express.html#autotoc_md6", [
          [ "Troubleshooting", "d8/d69/pci_express.html#autotoc_md7", [
            [ "The video random-access memory (VRAM) is too large:", "d8/d69/pci_express.html#autotoc_md8", null ],
            [ "Ring Test Failed", "d8/d69/pci_express.html#autotoc_md9", null ]
          ] ]
        ] ],
        [ "PCIe Ethernet:", "d8/d69/pci_express.html#autotoc_md10", null ]
      ] ],
      [ "RC mode:", "d8/d69/pci_express.html#autotoc_md11", [
        [ "Troubleshooting:", "d8/d69/pci_express.html#autotoc_md12", [
          [ "RC often gets hung when read / write endpoints' BAR / CFG", "d8/d69/pci_express.html#autotoc_md13", null ],
          [ "Downstream EP devices cannot be recongized or are not functioning:", "d8/d69/pci_express.html#autotoc_md14", null ]
        ] ]
      ] ],
      [ "EP mode:", "d8/d69/pci_express.html#autotoc_md15", [
        [ "Rework may be required if a PC is used as the RC.", "d8/d69/pci_express.html#autotoc_md19", [
          [ "As an EP, rework is required.", "d8/d69/pci_express.html#autotoc_md16", [
            [ "CV3 and CV5:", "d8/d69/pci_express.html#autotoc_md17", null ]
          ] ],
          [ "CV72 EP Mode:", "d8/d69/pci_express.html#autotoc_md18", null ],
          [ "CV3:", "d8/d69/pci_express.html#autotoc_md20", null ],
          [ "CV72:", "d8/d69/pci_express.html#autotoc_md21", null ],
          [ "CV5:", "d8/d69/pci_express.html#autotoc_md22", null ]
        ] ]
      ] ],
      [ "Use I2C to read / write the clock generator on the board.", "d8/d69/pci_express.html#autotoc_md23", null ],
      [ "Disable unused lanes:", "d8/d69/pci_express.html#autotoc_md24", [
        [ "AMBoot:", "d8/d69/pci_express.html#autotoc_md25", null ],
        [ "Linux kernel:", "d8/d69/pci_express.html#autotoc_md26", null ]
      ] ],
      [ "Utilizing Alternate General Purpose Input / Output (GPIO) for Power Provision", "d8/d69/pci_express.html#autotoc_md27", null ]
    ] ],
    [ "Ethernet", "d3/d5b/si_ethernet.html", [
      [ "1. Show Ethernet Device Information", "d3/d5b/si_ethernet.html#show_ethernet_device_information", null ],
      [ "2. Modify IP Address", "d3/d5b/si_ethernet.html#modify_ip_address", null ],
      [ "3. Jumbo Frames", "d3/d5b/si_ethernet.html#jumbo_frames", null ],
      [ "4. Test the Ethernet Throughput", "d3/d5b/si_ethernet.html#test_the_ethernet_throughput", [
        [ "4.1 Test the Ethernet Throughput with the Speed 100 Mbps", "d3/d5b/si_ethernet.html#test_et_100", null ],
        [ "4.2 Test Ethernet Throughput with 10-Mbps Speed", "d3/d5b/si_ethernet.html#test_et_10", null ]
      ] ],
      [ "5. Reference Ethernet Throughput Test Result", "d3/d5b/si_ethernet.html#reference_ethernet_throughput_test_result", null ],
      [ "6. Configure VLAN Function", "d3/d5b/si_ethernet.html#configure_VLAN_function", null ],
      [ "7. Two Ethernet Ports Function Together", "d3/d5b/si_ethernet.html#dual_eth_work", null ]
    ] ],
    [ "PTP", "db/d1c/si_ptp.html", [
      [ "1 PTP Introduction", "db/d1c/si_ptp.html#ptp_introduction", null ],
      [ "2 PTP Examples on the Ambarella Platform", "db/d1c/si_ptp.html#ptp_on_ambarella_platform", [
        [ "2.1 Preparation", "db/d1c/si_ptp.html#ptp_on_ambarella_platform_preparation", null ],
        [ "2.2 Build the PTP Driver and the Linux PTP Tool (linuxptp)", "db/d1c/si_ptp.html#ptp_on_ambarella_platform_build", null ],
        [ "2.3 Testing on the EVK Board", "db/d1c/si_ptp.html#ptp_on_ambarella_platform_test", null ]
      ] ]
    ] ],
    [ "Miscellaneous", "d0/dd4/si_miscellaneous.html", [
      [ "1. Installing the TFTP Server", "d0/dd4/si_miscellaneous.html#installing_the_tftp_server", [
        [ "1.1 TFTPD for Windows", "d0/dd4/si_miscellaneous.html#tftpd_for_windows", null ],
        [ "1.2 TFTPD HPA for Ubuntu", "d0/dd4/si_miscellaneous.html#tftpd_hpa_for_ubuntu", null ]
      ] ],
      [ "2. Using Watchdog", "d0/dd4/si_miscellaneous.html#use_watchdog", null ]
    ] ],
    [ "JTAG", "d4/dcd/si_jtag.html", [
      [ "1. Setup the JTAG Code Viser with CVD64", "d4/dcd/si_jtag.html#set_up_jtag_code_viser_with_cvd64", [
        [ "1.1 Setup", "d4/dcd/si_jtag.html#setup_with_cvd64", null ],
        [ "1.2 Run", "d4/dcd/si_jtag.html#run_jtag_code_viser_with_cvd64", [
          [ "1.2.1 Cortex® - A53 Platforms", "d4/dcd/si_jtag.html#a53_platforms", null ],
          [ "1.2.2 Cortex® - A76 Platforms", "d4/dcd/si_jtag.html#a76_platforms", null ]
        ] ]
      ] ]
    ] ],
    [ "Temperature", "d7/de9/si_temperature.html", null ],
    [ "Files", "files.html", [
      [ "File List", "files.html", "files_dup" ]
    ] ]
  ] ]
];

var NAVTREEINDEX =
[
"d0/da5/si_sd_card.html"
];

var SYNCONMSG = 'click to disable panel synchronisation';
var SYNCOFFMSG = 'click to enable panel synchronisation';