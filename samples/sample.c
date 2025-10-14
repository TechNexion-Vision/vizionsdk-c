#include <stdio.h>
#include "vizionsdk.h"
#include "vx_public_types.h"

char* type2str(vx_camera_interface_type type) {
    switch (type) {
        case INTERFACE_USB:
            return "USB";
        case INTERFACE_MIPI_CSI2:
            return "MIPI";
        case INTERFACE_ETHERNET:
            return "ETHERNET";
    }
    return "";
}

char* format2str(vx_image_format type) {
    switch (type) {
        case NONE:
            return "NONE";
        case YUY2:
            return "YUY2";
        case UYVY:
            return "UYVY";
        case NV12:
            return "NV12";
        case MJPG:
            return "MJPG";
        case BGRA:
            return "BGRA";
        case BGRX:
            return "BGRX";
        case BGR:
            return "BGR";
        case RGB16:
            return "RGB16";
        case RGB:
            return "RGB";
    }
    return "";
}

int main() {
    hello_vizionsdk();

    // get device list
    const char**dev_list = NULL;
    int dev_num = vx_discover_camera_devices(&dev_list);
    int i = 0;
    printf("Found %d device.\n", dev_num);
    while (dev_list[i] != NULL) {
        printf("[%d] %s\n", i, dev_list[i]);
        i++;
    }

    // initialize camera device
    printf("Start to initial device: %s\n", dev_list[0]);
    vx_camera cam = vx_initial_camera_device(0);

    // open camera
    int ret = vx_open(cam);
    printf("Camera open: %d\n", ret);

    // get device name
    const char* dev_name;
    ret = vx_get_device_name(cam, &dev_name);
    printf("Device Name: %s\n", dev_name);

    // get interface type
    vx_camera_interface_type type;
    ret = vx_get_device_interface_type(cam, &type);
    char* type_name = type2str(type);
    printf("Interface type: %s\n", type_name);

    const vx_format* fmt_list = NULL;
    ret = vx_get_format_list(cam, &fmt_list);
    vx_format mjpgFormat;
    int min_width = 1920;
    int min_height = 1080;
    if (ret == 0) {
        i = 0;
        while (fmt_list[i].width != 0 && fmt_list[i].height != 0) {
            if (fmt_list[i].format == MJPG && ((fmt_list[i].width * fmt_list[i].height) < (min_width * min_height))) {
                min_width = fmt_list[i].width;
                min_height = fmt_list[i].height;
                mjpgFormat = fmt_list[i];
                break;
            }
            i++;
        }
    }

    char* fmt_name = format2str(mjpgFormat.format);
    printf("%s %d x %d @ %d fps\n", fmt_name, mjpgFormat.width, mjpgFormat.height, mjpgFormat.framerate);

    ret = vx_set_format(cam, mjpgFormat);
    printf("Set camera format: %d\n", ret);

    ret = vx_start_streaming(cam);
    printf("Camera start streaming: %d\n", ret);

    int min, max, step, def;
    ret = vx_get_uvc_image_processing_range(cam, UVC_IMAGE_BRIGHTNESS, &min, &max, &step, &def);
    printf("Result: %d, Brightness range %d ~ %d step: %d, def: %d\n", ret, min, max, step, def);

    ret = vx_set_uvc_image_processing(cam, UVC_IMAGE_BRIGHTNESS, 12, 0);
    printf("Result: %d, Brightness set to %d\n", ret, 12);

    ret = vx_stop_streaming(cam);
    printf("Stop streaming: %d\n", ret);

    ret = vx_close(cam);
    printf("Camera Close: %d\n", ret);

    // cleanup the resource
    vx_release_device_list(dev_list);
    vx_release_format_list(fmt_list);
    vx_release_camera(cam);
    return 0;
}