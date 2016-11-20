/*
 * This file contains device specific hooks.
 * Always enclose hooks to #if MR_DEVICE_HOOKS >= ver
 * with corresponding hook version!
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <errno.h>

#include <log.h>

#if MR_DEVICE_HOOKS >= 1
int mrom_hook_after_android_mounts(__attribute__((unused)) const char *busybox_path,
                                __attribute__((unused)) const char *base_path,
                                __attribute__((unused)) int type)
{
    return 0;
}
#endif /* MR_DEVICE_HOOKS >= 1 */


#if MR_DEVICE_HOOKS >= 2
// Screen gets cleared immediatelly after closing the framebuffer on this device,
// give user a while to read the message box until it dissapears.
void mrom_hook_before_fb_close(void)
{
    usleep(800000);
}
#endif /* MR_DEVICE_HOOKS >= 2 */


#if MR_DEVICE_HOOKS >= 3
static time_t gettime(void)
{
    struct timespec ts;
    int ret;

    ret = clock_gettime(CLOCK_MONOTONIC, &ts);
    if (ret < 0) {
        ERROR("clock_gettime(CLOCK_MONOTONIC) failed: %s\n", strerror(errno));
        return 0;
    }

    return ts.tv_sec;
}

static int wait_for_file(const char *filename, int timeout)
{
    struct stat info;
    time_t timeout_time = gettime() + timeout;
    int ret = -1;
    int waited = 0;

    while (gettime() < timeout_time && ((ret = stat(filename, &info)) < 0))
    {
        waited = 1;
        usleep(30000);
    }

    if(ret >= 0)
        return waited;
    else
        return ret;
}

static int read_file(const char *path, char *dest, int dest_size)
{
    int res = 0;
    FILE *f = fopen(path, "r");
    if(!f)
        return res;

    res = fgets(dest, dest_size, f) != NULL;
    fclose(f);
    return res;
}

static int write_file(const char *path, const char *what)
{
    int res = 0;
    FILE *f = fopen(path, "w");
    if(!f)
        return res;

    res = fputs(what, f) >= 0;
    fclose(f);
    return res;
}

static void set_cpu_governor(void)
{
    size_t i;
    char buff[256];
    static const char *governors[] = { "ondemand", "interactive" };

    if(!read_file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor", buff, sizeof(buff)))
        return;

    if(strncmp(buff, "performance", 11) != 0)
        return;

    if(!read_file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_available_governors", buff, sizeof(buff)))
        return;

    for(i = 0; i < sizeof(governors)/sizeof(governors[0]); ++i)
    {
        if(strstr(buff, governors[i]))
        {
            write_file("/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor", governors[i]);
            write_file("/sys/devices/system/cpu/cpu1/cpufreq/scaling_governor", governors[i]);
            write_file("/sys/devices/system/cpu/cpu2/cpufreq/scaling_governor", governors[i]);
            write_file("/sys/devices/system/cpu/cpu3/cpufreq/scaling_governor", governors[i]);
            break;
        }
    }
}

void tramp_hook_before_device_init(void)
{
    // hammerhead's kernel has "performance" as default
    set_cpu_governor();
}
#endif /* MR_DEVICE_HOOKS >= 3 */

#if MR_DEVICE_HOOKS >= 4
int mrom_hook_allow_incomplete_fstab(void)
{
    return 1;
}
#endif
