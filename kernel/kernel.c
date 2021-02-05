#include <types.h>
#include <uart.h>

int
kernel_main(u64 dtb_ptr32, u64 x1, u64 x2, u64 x3)
{
	(void)dtb_ptr32;
	(void)x1;
	(void)x2;
	(void)x3;
	uart_puts("Hello");
	while (1);
}
