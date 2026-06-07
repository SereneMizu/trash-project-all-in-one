#include "wifi_sta.h"

#include <stdlib.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_netif.h"
#include "esp_smartconfig.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "hmi.h"
#include "myconfig.h"
#include "nvs_flash.h"

static const char *TAG = "wifi_sta.c";

static EventGroupHandle_t s_wifi_event_group;
static const int WIFI_CONNECTED_BIT = BIT0;
static const int ESPTOUCH_DONE_BIT = BIT2;
static const uint32_t WIFI_UPDATE = 128;

static void event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        esp_wifi_connect();
        xEventGroupClearBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);
        ESP_LOGI(TAG, "WiFi Got IP");
    } else if (event_base == SC_EVENT && event_id == SC_EVENT_SCAN_DONE) {
        ESP_LOGI(TAG, "Scan done");
    } else if (event_base == SC_EVENT && event_id == SC_EVENT_FOUND_CHANNEL) {
        ESP_LOGI(TAG, "Found channel");
    } else if (event_base == SC_EVENT && event_id == SC_EVENT_GOT_SSID_PSWD) {
        ESP_LOGI(TAG, "Got SSID and password");

        smartconfig_event_got_ssid_pswd_t *evt =
            (smartconfig_event_got_ssid_pswd_t *)event_data;
        wifi_config_t wifi_config;
        char ssid[33] = {0};
        char password[65] = {0};
        uint8_t rvd_data[33] = {0};

        bzero(&wifi_config, sizeof(wifi_config_t));
        memcpy(wifi_config.sta.ssid, evt->ssid, sizeof(wifi_config.sta.ssid));
        memcpy(wifi_config.sta.password, evt->password,
               sizeof(wifi_config.sta.password));

        memcpy(ssid, evt->ssid, sizeof(evt->ssid));
        memcpy(password, evt->password, sizeof(evt->password));
        ESP_LOGI(TAG, "SSID:%s", ssid);
        ESP_LOGI(TAG, "PASSWORD:%s", password);
        if (evt->type == SC_TYPE_ESPTOUCH_V2) {
            ESP_ERROR_CHECK(
                esp_smartconfig_get_rvd_data(rvd_data, sizeof(rvd_data)));
            ESP_LOGI(TAG, "RVD_DATA:");
            for (int i = 0; i < 33; i++) {
                printf("%02x ", rvd_data[i]);
            }
            printf("\n");
        }

        ESP_ERROR_CHECK(esp_wifi_disconnect());
        // 保存wifi名和密码
        nvs_handle_t wifi_nvs_handle;
        if (nvs_open("wifi_config", NVS_READWRITE, &wifi_nvs_handle) == ESP_OK) {
            ESP_LOGI(TAG, "writing wifi config");
            ESP_ERROR_CHECK(nvs_set_u32(wifi_nvs_handle, "wifi_update", WIFI_UPDATE));
            ESP_ERROR_CHECK(nvs_set_str(wifi_nvs_handle, "wifi_ssid", ssid));
            ESP_ERROR_CHECK(nvs_set_str(wifi_nvs_handle, "wifi_password", password));
            ESP_ERROR_CHECK(nvs_commit(wifi_nvs_handle));
        } else {
            ESP_LOGI(TAG, "write wifi config fail");
        }
        nvs_close(wifi_nvs_handle);

        ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
        esp_wifi_connect();
    } else if (event_base == SC_EVENT && event_id == SC_EVENT_SEND_ACK_DONE) {
        xEventGroupSetBits(s_wifi_event_group, ESPTOUCH_DONE_BIT);
    }
}

void wifi_try_smartconfig(void) {
    hmi_show_smartconfig();
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_ERROR_CHECK(esp_smartconfig_set_type(SC_TYPE_ESPTOUCH));
    smartconfig_start_config_t smartconfig_start_config =
        SMARTCONFIG_START_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_smartconfig_start(&smartconfig_start_config));
}

void wifi_wait_connect(void) {
    gpio_set_direction(MYCONFIG_WIFI_RESET_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(MYCONFIG_WIFI_RESET_PIN, GPIO_PULLUP_ONLY);

    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGI(TAG, "erase nvs flash");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    // nvs_handle_t wifi_nvs_handle;
    // if (nvs_open("wifi_config", NVS_READWRITE, &wifi_nvs_handle) == ESP_OK) {
    //     ESP_LOGI(TAG, "writing wifi config");
    //     ESP_ERROR_CHECK(nvs_set_u32(wifi_nvs_handle, "wifi_update", WIFI_UPDATE));
    //     ESP_ERROR_CHECK(nvs_set_str(wifi_nvs_handle, "wifi_ssid", "SIPC115 -2.4G"));
    //     ESP_ERROR_CHECK(nvs_set_str(wifi_nvs_handle, "wifi_password", "sipcprivate"));
    //     ESP_ERROR_CHECK(nvs_commit(wifi_nvs_handle));
    // } else {
    //     ESP_LOGI(TAG, "write wifi config fail");
    // }
    // nvs_close(wifi_nvs_handle);

    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_netif_init());
    s_wifi_event_group = xEventGroupCreate();

    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                               &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP,
                                               &event_handler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(SC_EVENT, ESP_EVENT_ANY_ID,
                                               &event_handler, NULL));

    if (gpio_get_level(MYCONFIG_WIFI_RESET_PIN) == 0) {
        ESP_LOGI(TAG, "waiting for new smartconfig");
        wifi_try_smartconfig();
    } else {
        ESP_LOGI(TAG, "waiting for wifi default config");
        int read_config_ok = 0;
        char *ssid;
        char *password;
        size_t len = 0;
        nvs_handle_t wifi_nvs_handle;
        if (nvs_open("wifi_config", NVS_READONLY, &wifi_nvs_handle) == ESP_OK) {
            ESP_LOGI(TAG, "reading wifi config");
            uint32_t wifi_update = 0;
            ESP_ERROR_CHECK(nvs_get_u32(wifi_nvs_handle, "wifi_update", &wifi_update));
            if (wifi_update == WIFI_UPDATE) {
                ESP_ERROR_CHECK(nvs_get_str(wifi_nvs_handle, "wifi_ssid", NULL, &len));
                ssid = (char *)malloc(len);
                ESP_ERROR_CHECK(nvs_get_str(wifi_nvs_handle, "wifi_ssid", ssid, &len));

                ESP_ERROR_CHECK(nvs_get_str(wifi_nvs_handle, "wifi_password", NULL, &len));
                password = (char *)malloc(len);
                ESP_ERROR_CHECK(nvs_get_str(wifi_nvs_handle, "wifi_password", password, &len));
                read_config_ok = 1;
            }
        } else {
            ESP_LOGI(TAG, "read wifi config fail");
        }
        nvs_close(wifi_nvs_handle);
        if (read_config_ok) {
            wifi_config_t wifi_config = {
                .sta = {.ssid = {0}, .password = {0}},
            };
            strcpy((char *)(wifi_config.sta.ssid), ssid);
            strcpy((char *)(wifi_config.sta.password), password);
            ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
            ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
            ESP_ERROR_CHECK(esp_wifi_start());
            ESP_ERROR_CHECK(esp_wifi_connect());
        } else {
            ESP_LOGI(TAG, "invalid wifi config, waiting for new smartconfig");
            wifi_try_smartconfig();
        }
    }
    while (1) {
        EventBits_t uxBits = xEventGroupWaitBits(s_wifi_event_group,
                                                 WIFI_CONNECTED_BIT | ESPTOUCH_DONE_BIT, true,
                                                 false, portMAX_DELAY);
        if (uxBits & WIFI_CONNECTED_BIT) {
            ESP_LOGI(TAG, "WiFi Connected to ap");
            break;
        }
        if (uxBits & ESPTOUCH_DONE_BIT) {
            ESP_LOGI(TAG, "smartconfig over");
            esp_smartconfig_stop();
        }
    }
    hmi_page_main();
}