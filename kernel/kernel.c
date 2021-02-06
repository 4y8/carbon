#include <types.h>
#include <uart.h>

int
main()
{
	uart_init();
	uart_puts("Hello\n");
	while (1)
		uart_putc(uart_getc());
}
