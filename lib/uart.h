#ifndef __UART_H_
#define __UART_H_

void uart_putc(unsigned char c);
void uart_puts(const char *s);
char uart_getc(void);

#endif /* __UART_H_ */
