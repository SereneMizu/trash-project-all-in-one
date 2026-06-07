idf_component_register(SRCS "id.c" "mqtt.c" "uart.c" "hmi.c" "http.c" "camera.c" "main.c" "wifi_sta.c" "http.c"
                        PRIV_INCLUDE_DIRS .
                        PRIV_REQUIRES nvs_flash esp_netif esp_wifi esp_event esp_http_client driver mqtt json)
