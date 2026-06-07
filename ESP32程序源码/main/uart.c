#include "driver/uart.h"

#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt.h"
#include "myconfig.h"

#define BUF_SIZE (MYCONFIG_UART_BUF_SIZE)
#define RD_BUF_SIZE (BUF_SIZE)
#define UART_NUM UART_NUM_2

static const char *TAG = "uart.c";
static QueueHandle_t uart_queue;

void uart_send(char *str, size_t s) {
    ESP_LOGI(TAG, "UART SEND:");
    ESP_LOG_BUFFER_HEX(TAG, str, s);
    uart_write_bytes(UART_NUM, (const char *)str, s);
    uart_write_bytes(UART_NUM, "\x0d\x0a", 2);
}
void uart_open_residual(void) {
    uart_send("\xfe\x00\xff", 3);
}
void uart_open_recyclable(void) {
    uart_send("\xfe\x01\xff", 3);
}
void uart_open_food(void) {
    uart_send("\xfe\x02\xff", 3);
}
void uart_open_hazardous(void) {
    uart_send("\xfe\x03\xff", 3);
}
void uart_open_all(void) {
    uart_send("\xfe\x04\xff", 3);
}
static void uart_event_task(void *pvParameters) {
    uart_event_t event;
    uint8_t *dtmp = (uint8_t *)malloc(RD_BUF_SIZE);
    for (;;) {
        if (xQueueReceive(uart_queue, (void *)&event, (TickType_t)portMAX_DELAY)) {
            bzero(dtmp, RD_BUF_SIZE);
            // ESP_LOGI(TAG, "uart event:");
            switch (event.type) {
                case UART_DATA:
                    // ESP_LOGI(TAG, "[UART DATA SIZE]: %d", event.size);
                    uart_read_bytes(UART_NUM, dtmp, event.size, portMAX_DELAY);
                    ESP_LOGI(TAG, "UART RECV:");
                    ESP_LOG_BUFFER_HEX(TAG, dtmp, event.size);

                    // ESP_LOGI(TAG, "[UART DATA]: %d", dtmp[1]);
                    if (dtmp[0] == 0xfe) {
                        mqtt_pub_value((int)(dtmp[1]), (int)(dtmp[2]));
                    } else if (dtmp[0] == 0xfd) {
                        mqtt_pub_full();
                    }

                    break;
                case UART_FIFO_OVF:
                    ESP_LOGI(TAG, "hw fifo overflow");
                    uart_flush_input(UART_NUM);
                    xQueueReset(uart_queue);
                    break;
                case UART_BUFFER_FULL:
                    ESP_LOGI(TAG, "ring buffer full");
                    uart_flush_input(UART_NUM);
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
void uart_init(void) {
    uart_config_t uart1_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_param_config(UART_NUM, &uart1_config);
    uart_set_pin(UART_NUM, MYCONFIG_UART_TX_PIN, MYCONFIG_UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(UART_NUM, MYCONFIG_UART_BUF_SIZE, MYCONFIG_UART_BUF_SIZE, 20, &uart_queue, 0);
    uart_flush(UART_NUM);
    xTaskCreate(uart_event_task, "uart_event_task", 2048, NULL, 12, NULL);

    // while (1) {
    //     uart_send("click d0,1");
    //     vTaskDelay(1000 / portTICK_PERIOD_MS);
    // }
}
