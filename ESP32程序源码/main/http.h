#ifndef __HTTP_H
#define __HTTP_H

char* http_post_file(char* url, uint8_t* file_data, size_t file_length);
void http_free_resp(char* resp_buf);

#endif