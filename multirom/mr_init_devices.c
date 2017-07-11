#include <stdlib.h>

// These are paths to folders in /sys which contain "uevent" file
// need to init this device.
// MultiROM needs to init framebuffer, mmc blocks, input devices,
// some ADB-related stuff and USB drives, if OTG is supported
// You can use * at the end to init this folder and all its subfolders
const char *mr_init_devices[] =
{
	"/sys/class/graphics/fb0",
        "/sys/devices/virtual/graphics/fb0",
        "/sys/class/graphics/fb1",
        "/sys/devices/virtual/graphics/fb1",
	
        "/sys/block/mmcblk0",
        "/sys/devices/msm_sdcc.1",
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/*",
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/mmc0:0001",
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/mmc0:0001/block/mmcblk0",
        // boot and data
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p7",
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p28",

        // system and cache
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p14",
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p16",

        // persist and firmware
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p15",
        "/sys/devices/msm_sdcc.1/mmc_host/mmc0/mmc0:0001/block/mmcblk0/mmcblk0p1",

        "/sys/bus/mmc",
        "/sys/bus/mmc/drivers/mmcblk",
        "/sys/module/mmc_core",
        "/sys/module/mmcblk",
        "/sys/module/sdhci",
        "/sys/module/sdhci/*",
        "/sys/module/sdhci_msm",
        "/sys/module/sdhci_msm/*",

        // for input
	"/sys/devices/virtual/input*",
	"/sys/devices/virtual/misc/uinput",
        "/sys/devices/gpio_keys.84/input*",
        "/sys/bus/platform/devices/gpio_keys.84/input*",
	"/sys/devices/virtual/misc/uinput/*",
        "/sys/devices/f9924000.i2c/i2c-2/2-0020/input*",
        "/sys/devices/f9924000.i2c/i2c-2/2-0020/input*",
        "/sys/devices/f9924000.i2c/i2c-2/2-0020/input/input0",
	
	// USB drive
	"/sys/bus/platform/drivers/xhci-hcd*",
	
	// for adb
	"/sys/devices/virtual/tty/ptmx",
	"/sys/devices/virtual/misc/android_adb",
	"/sys/devices/virtual/android_usb/android0/f_adb",
	"/sys/bus/usb",
	
        "/sys/bus*",
        "/sys/devices*",

	// for qualcomm overlay - /dev/ion
        "/sys/devices/virtual/misc/ion",
	
	// Encryption
	"/sys/devices/virtual/misc/device-mapper",
	"/sys/devices/virtual/qseecom/qseecom",

	NULL
};
