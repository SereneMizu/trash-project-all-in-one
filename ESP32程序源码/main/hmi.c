#include <string.h>

#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt.h"
#include "myconfig.h"
#include "uart.h"
#define BUF_SIZE (MYCONFIG_UART_BUF_SIZE)
#define RD_BUF_SIZE (BUF_SIZE)
#define HMI_UART_NUM UART_NUM_1

// #define PATTERN_CHR_NUM (3)

static QueueHandle_t uart_queue;

static const char *TAG = "hmi.c";

static void hmi_send(char *str) {
    ESP_LOGI(TAG, "HMI SEND:");
    ESP_LOGI(TAG, "%s", str);
    uart_write_bytes(HMI_UART_NUM, (const char *)str, strlen(str));
    uart_write_bytes(HMI_UART_NUM, "\xff\xff\xff", 3);
}

void hmi_reset(void) {
    hmi_send("rest");
}
void hmi_show_smartconfig(void) {
    hmi_send("click ds,1");
}
void hmi_rubbish_is_gray(void) {
    hmi_send("click d0,1");
}
void hmi_rubbish_is_blue(void) {
    hmi_send("click d1,1");
}
void hmi_rubbish_is_green(void) {
    hmi_send("click d2,1");
}
void hmi_rubbish_is_red(void) {
    hmi_send("click d3,1");
}
void hmi_rubbish_reset(void) {
    hmi_send("click dr,1");
}
void hmi_page_main(void) {
    hmi_send("page main");
}
void hmi_page_boot(void) {
    hmi_send("page boot");
}

static void hmi_event_task(void *pvParameters) {
    uart_event_t event;
    uint8_t *dtmp = (uint8_t *)malloc(RD_BUF_SIZE);
    for (;;) {
        if (xQueueReceive(uart_queue, (void *)&event, (TickType_t)portMAX_DELAY)) {
            bzero(dtmp, RD_BUF_SIZE);
            // ESP_LOGI(TAG, "hmi event:");
            switch (event.type) {
                case UART_DATA:
                    uart_read_bytes(HMI_UART_NUM, dtmp, event.size, portMAX_DELAY);
                    ESP_LOGI(TAG, "HMI RECV:");
                    ESP_LOG_BUFFER_HEX(TAG, dtmp, event.size);
                    if (dtmp[1] == 0x00) {
                        uart_open_residual();
                        mqtt_pub_residual_count();
                    } else if (dtmp[1] == 0x01) {
                        uart_open_recyclable();
                        mqtt_pub_recyclable_count();
                    } else if (dtmp[1] == 0x02) {
                        uart_open_food();
                        mqtt_pub_food_count();
                    } else if (dtmp[1] == 0x03) {
                        uart_open_hazardous();
                        mqtt_pub_hazardous_count();
                    } else if (dtmp[1] == 0x10) {
                        mqtt_pub_break();
                    } else if (dtmp[1] == 0x11) {
                        mqtt_pub_danger(0);
                    }
                    break;
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    uart_flush_input(HMI_UART_NUM);
                    xQueueReset(uart_queue);
                    break;
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    uart_flush_input(HMI_UART_NUM);
                    xQueueReset(uart_queue);
                    break;
                case UART_BREAK:
                    ESP_LOGI(TAG, "uart rx break");
                    break;
                case UART_PARITY_ERR:
                    ESP_LOGI(TAG, "uart parity error");
                    break;
                case UART_FRAME_ERR:
                    ESP_LOGI(TAG, "uart frame error");
                    break;
                default:
                    ESP_LOGI(TAG, "uart event type: %d", event.type);
                    break;
            }
        }
    }
    free(dtmp);
    dtmp = NULL;
    vTaskDelete(NULL);
}
void hmi_init(void) {
    uart_config_t uart1_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_param_config(HMI_UART_NUM, &uart1_config);
    uart_set_pin(HMI_UART_NUM, MYCONFIG_HMI_TX_PIN, MYCONFIG_HMI_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(HMI_UART_NUM, MYCONFIG_UART_BUF_SIZE, MYCONFIG_UART_BUF_SIZE, 20, &uart_queue, 0);
    uart_flush(HMI_UART_NUM);
    // while (1) {
    //     hmi_send("click d0,1");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     hmi_send("click d1,1");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     hmi_send("click d2,1");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    //     hmi_send("click d3,1");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
    xTaskCreate(hmi_event_task, "hmi_event_task", 4096, NULL, 12, NULL);

    hmi_reset();
}
