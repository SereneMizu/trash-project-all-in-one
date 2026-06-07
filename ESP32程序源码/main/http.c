#include "esp_http_client.h"
#include "esp_log.h"
#include "myconfig.h"
static const char* TAG = "http.c";

#define RESP_BUF_SIZE 128

static char* resp_buf;

char* http_post_file(char* url, char* file_data, int file_length) {
    char* data_before_file =
        "--------------------------jPsBaFD9zO74ul5EgP4fpe\r\n"
        "Content-Disposition: form-data; name=\"file\"; filename=\"file.jpg\"\r\n"
        "Content-Type: image/jpeg\r\n\r\n";
    char* data_after_file = "\r\n--------------------------jPsBaFD9zO74ul5EgP4fpe--\r\n";
    // int post_data_size = strlen(data_before_file) + strlen(data_before_file) + file_length ;
    // char* post_data = (char*)malloc(sizeof(char) * post_data_size);
    // post_data[0] = 0;
    // strcat(post_data, data_before_file);
    // strncat(post_data, file_data, strlen(data_before_file) + file_length);
    // strcat(post_data, data_after_file);

    resp_buf = (char*)malloc(sizeof(char) * RESP_BUF_SIZE);
    esp_http_client_config_t config = {
        .url = url,
        .method = HTTP_METHOD_POST,
        .user_data = resp_buf,
        .disable_auto_redirect = true,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_header(client, "Content-Type", "multipart/form-data;boundary=------------------------jPsBaFD9zO74ul5EgP4fpe");
    // esp_http_client_set_post_field(client, post_data, post_data_size - 1);
    esp_http_client_set_timeout_ms(client, 1000 * 60);
    // esp_err_t err = esp_http_client_perform(client);
    // if (err == ESP_OK) {
    //     ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %" PRId64,
    //              esp_http_client_get_status_code(client),
    //              esp_http_client_get_content_length(client));
    // } else {
    //     ESP_LOGE(TAG, "HTTP POST request failed: %s", esp_err_to_name(err));
    // }
    esp_http_client_open(client, strlen(data_before_file) + strlen(data_after_file) + file_length);
    int wlen = esp_http_client_write(client, data_before_file, strlen(data_before_file));
    if (wlen < 0) {
        ESP_LOGE(TAG, "Write failed before");
    }
    wlen = esp_http_client_write(client, file_data, file_length);
    if (wlen < 0) {
        ESP_LOGE(TAG, "Write failed data");
    }
    wlen = esp_http_client_write(client, data_after_file, strlen(data_after_file));
    if (wlen < 0) {
        ESP_LOGE(TAG, "Write failed after");
    }

    int content_length = esp_http_client_fetch_headers(client);
    if (content_length < 0) {
        ESP_LOGE(TAG, "HTTP client fetch headers failed");
    } else {
        int data_read = esp_http_client_read_response(client, resp_buf, RESP_BUF_SIZE);
        if (data_read >= 0) {
            int len = esp_http_client_get_content_length(client);
            ESP_LOGI(TAG, "HTTP POST Status = %d, content_length = %d",
                     esp_http_client_get_status_code(client),
                     len);
            resp_buf[len] = 0;
            ESP_LOG_BUFFER_HEX(TAG, resp_buf, strlen(resp_buf));
        } else {
            ESP_LOGE(TAG, "Failed to read response");
        }
    }
    esp_http_client_cleanup(client);

    return resp_buf;
}

void http_free_resp(char* resp_buf) {
    free(resp_buf);
}