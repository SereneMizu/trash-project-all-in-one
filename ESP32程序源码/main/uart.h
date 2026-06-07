#ifndef __UART_H
#define __UART_H

void uart_init(void);
void uart_open_residual(void);
void uart_open_recyclable(void);
void uart_open_food(void);
void uart_open_hazardous(void);
void uart_open_all(void);
#endif