
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <string.h>
#include <sys/param.h>

#include "camera.h"
#include "driver/gpio.h"
#include "esp_event.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hmi.h"
#include "id.h"
#include "mqtt.h"
#include "myconfig.h"
#include "uart.h"
#include "wifi_sta.h"

#ifndef portTICK_RATE_MS
#define portTICK_RATE_MS portTICK_PERIOD_MS
#endif

static const char* TAG = "main.c";

void app_main(void) {
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    hmi_init();
    id_init();
    wifi_wait_connect();
    mqtt_init();
    uart_init();
    gpio_set_direction(MYCONFIG_LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(MYCONFIG_CAMERA_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(MYCONFIG_CAMERA_PIN, GPIO_PULLDOWN_ENABLE);

    ESP_LOGI(TAG, "%s", id_get());

    if (init_camera() != ESP_OK) {
        ESP_LOGE(TAG, "摄像头初始化失败");
        return;
    }

    while (1) {
        if (gpio_get_level(MYCONFIG_CAMERA_PIN) == 1) {
            vTaskDelay(2000 / portTICK_RATE_MS);
            int res = take_picture_and_detect();
            if (res >= 0) {
                vTaskDelay(12000 / portTICK_RATE_MS);
            }
        }
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}
