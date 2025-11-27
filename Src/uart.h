#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init(void);
void uart_write(uint8_t ch);
uint8_t uart_read(void);
void uart_print(const char *str);


#endif /* UART_H_ */
