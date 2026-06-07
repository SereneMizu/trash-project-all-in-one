#ifndef __CAMERA_H
#define __CAMERA_H

#include "esp_camera.h"

esp_err_t init_camera(void);
int take_picture_and_detect(void);

#endif