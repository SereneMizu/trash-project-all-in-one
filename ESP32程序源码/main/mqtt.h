#ifndef __MQTT_H
#define __MQTT_H
void mqtt_init(void);
int mqtt_pub(const char *topic, const char *data);
int mqtt_pub_lid();
// int mqtt_pub_count(int n);

int mqtt_pub_residual_count(void);
int mqtt_pub_recyclable_count(void);
int mqtt_pub_food_count(void);
int mqtt_pub_hazardous_count(void);

int mqtt_pub_value(int m, int s);
int mqtt_pub_full();
int mqtt_pub_break();
int mqtt_pub_danger(int trigger);
#endif