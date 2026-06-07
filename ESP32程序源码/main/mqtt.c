#include <stdio.h>

#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "id.h"
#include "mqtt_client.h"
#include "myconfig.h"
#include "uart.h"
static const char *TAG = "mqtt.c";
esp_mqtt_client_handle_t client;
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data) {
    ESP_LOGD(TAG, "Event dispatched from event loop base=%s, event_id=%" PRIi32 "", base, event_id);
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;
    switch ((esp_mqtt_event_id_t)event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            char topic[40] = {0};
            strcat(topic, "sipc/trash/");
            strcat(topic, id_get());
            strcat(topic, "/open");
            esp_mqtt_client_subscribe(client, topic, 1);
            topic[0] = 0;
            strcat(topic, "sipc/trash/");
            strcat(topic, id_get());
            strcat(topic, "/open1");
            esp_mqtt_client_subscribe(client, topic, 1);
            topic[0] = 0;
            strcat(topic, "sipc/trash/");
            strcat(topic, id_get());
            strcat(topic, "/open2");
            esp_mqtt_client_subscribe(client, topic, 1);
            topic[0] = 0;
            strcat(topic, "sipc/trash/");
            strcat(topic, id_get());
            strcat(topic, "/open3");
            esp_mqtt_client_subscribe(client, topic, 1);
            topic[0] = 0;
            strcat(topic, "sipc/trash/");
            strcat(topic, id_get());
            strcat(topic, "/open4");
            esp_mqtt_client_subscribe(client, topic, 1);
            break;
        case MQTT_EVENT_DISCONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
            break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            ESP_LOGI(TAG, "TOPIC=%.*s", event->topic_len, event->topic);
            ESP_LOGI(TAG, "DATA=%.*s", event->data_len, event->data);
            char datatopic[40] = {0};
            strncpy(datatopic, event->topic, event->topic_len);
            char topicp4[10] = {0};
            for (int i = 0; datatopic[i + 24]; i++) {
                topicp4[i] = datatopic[i + 24];
            }
            ESP_LOGI(TAG, "topicp4: %s", topicp4);
            if (strcmp(topicp4, "open") == 0) {
                uart_open_all();
            } else if (strcmp(topicp4, "open1") == 0) {
                uart_open_residual();
            } else if (strcmp(topicp4, "open2") == 0) {
                uart_open_recyclable();
            } else if (strcmp(topicp4, "open3") == 0) {
                uart_open_food();
            } else if (strcmp(topicp4, "open4") == 0) {
                uart_open_hazardous();
            }
            break;
        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
            if (event->error_handle->error_type == MQTT_ERROR_TYPE_TCP_TRANSPORT) {
                ESP_LOGI(TAG, "Last errno string (%s)", strerror(event->error_handle->esp_transport_sock_errno));
            }
            break;
        default:
            ESP_LOGI(TAG, "Other event id:%d", event->event_id);
            break;
    }
}

int mqtt_pub(const char *topic, const char *data) {
    ESP_LOGI(TAG, "topic: %s, data: %s", topic, data);
    return esp_mqtt_client_publish(client, topic, data, 0, 1, 0);
}

int mqtt_pub_lid() {
    char topic[40] = {0};
    strcat(topic, "sipc/trash/");
    strcat(topic, id_get());
    strcat(topic, "/lid");

    return mqtt_pub(topic, "0");
}
static int mqtt_pub_count(int n) {
    // n 第几个桶
    char topic[40] = {0};
    strcat(topic, "sipc/trash/");
    strcat(topic, id_get());
    strcat(topic, "/count");
    char data[5] = {0};
    sprintf(data, "%d", n);
    return mqtt_pub(topic, data);
}
int mqtt_pub_residual_count(void) {
    return mqtt_pub_count(0);
}
int mqtt_pub_recyclable_count(void) {
    return mqtt_pub_count(1);
}
int mqtt_pub_food_count(void) {
    return mqtt_pub_count(2);
}
int mqtt_pub_hazardous_count(void) {
    return mqtt_pub_count(3);
}

int mqtt_pub_value(int m, int s) {
    char topic[40] = {0};
    strcat(topic, "sipc/trash/");
    strcat(topic, id_get());
    strcat(topic, "/value");
    char data[5] = {0};
    sprintf(data, "%d,%d", m, s);
    return mqtt_pub(topic, data);
}
int mqtt_pub_full() {
    char topic[40] = {0};
    strcat(topic, "sipc/trash/");
    strcat(topic, id_get());
    strcat(topic, "/full");

    return mqtt_pub(topic, "0");
}
int mqtt_pub_break() {
    char topic[40] = {0};
    strcat(topic, "sipc/trash/");
    strcat(topic, id_get());
    strcat(topic, "/break");

    return mqtt_pub(topic, "0");
}

int mqtt_pub_danger(int trigger) {
    // 0 手动
    // 1 自动
    char topic[40] = {0};
    strcat(topic, "sipc/trash/");
    strcat(topic, id_get());
    strcat(topic, "/danger");
    if (trigger == 0)
        return mqtt_pub(topic, "0");
    else
        return mqtt_pub(topic, "1");
}

void mqtt_init(void) {
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = MYCONFIG_MQTT_BROKER,
    };
    client = esp_mqtt_client_init(&mqtt_cfg);
    /* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}