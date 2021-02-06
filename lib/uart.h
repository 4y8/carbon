#ifndef __UART_H_
#define __UART_H_

void uart_init(void);
void uart_putc(unsigned int c);
void uart_puts(const char *s);
char uart_getc(void);

#endif /* __UART_H_ */
