#include <stdlib.h>

// These are paths to folders in /sys which contain "uevent" file
// need to init this device.
// MultiROM needs to init framebuffer, mmc blocks, input devices,
// some ADB-related stuff and USB drives, if OTG is supported
// You can use * at the end to init this folder and all its subfolders
const char *mr_init_devices[] =
{
	"/sys/class/graphics/fb0",
	
	"/sys/block/mmcblk0*",
	"/sys/block/mmcblk0/mmcblk0*",
	"/sys/block/mmcblk0/mmcblk0p1", //modem
	"/sys/block/mmcblk0/mmcblk0p14", //system
	"/sys/block/mmcblk0/mmcblk0p28", //data
	"/sys/block/mmcblk0/mmcblk0p16", //cache
	"/sys/block/mmcblk0/mmcblk0p15", //persist
	"/sys/block/mmcblk0/mmcblk0p7", //boot
	"/sys/block/mmcblk0/mmcblk0p17", //recovery
	"/sys/block/mmcblk0/mmcblk0p21", //misc
	"/sys/block/mmcblk0/mmcblk0p10", //efs1
	"/sys/block/mmcblk0/mmcblk0p11", //efs2
	
	"/sys/devices/gpio_keys.83/input*",
	"/sys/devices/virtual/input*",
	"/sys/devices/virtual/misc/uinput",
	"/sys/devices/f9924000.i2c/i2c-2/2-0020/input*",
	
	// USB drive
	"/sys/bus/platform/drivers/xhci-hcd*",
	
	// for adb
	"/sys/devices/virtual/tty/ptmx",
	"/sys/devices/virtual/misc/android_adb",
	"/sys/devices/virtual/android_usb/android0/f_adb",
	"/sys/bus/usb",
	
	// for qualcomm overlay - /dev/ion
	"/sys/devices/virtual/misc/ion",
	
	// Encryption
	"/sys/devices/virtual/misc/device-mapper",
	"/sys/devices/virtual/qseecom/qseecom",

	NULL
};
