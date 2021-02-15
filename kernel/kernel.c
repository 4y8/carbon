#include <io.h>
#include <types.h>
#include <libc.h>
#include <fmt.h>

#include "initrd.h"
#include "multiboot2.h"

int
kernel_main(ulong magic, ulong multiboot_header)
{
	clear_terminal();
	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		puts("Error: invalid multiboot2 magic number");
		return -1;
	}
	puts("Hello world!");

	multiboot2_init(multiboot_header + 8);
	print("%b, %s", 0b1011, "Hello");

	while(1);
}
