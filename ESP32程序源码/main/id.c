#include "id.h"

#include <stdio.h>

#include "esp_mac.h"
static char id[20] = {0};

void id_init(void) {
    uint8_t t[10] = {0};
    esp_efuse_mac_get_default(t);
    sprintf(id, "%X%X%X%X%X%X", t[0], t[1], t[2], t[3], t[4], t[5]);
}
char *id_get(void) {
    return id;
}
