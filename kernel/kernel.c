#include <io.h>
#include <types.h>

#include "initrd.h"
#include "multiboot2.h"

int
kernel_main(ulong magic, ulong multiboot_header)
{
	struct multiboot2_tag *tag;

	clear_terminal();
	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		puts("Error: invalid multiboot2 magic number");
		return -1;
	}
	puts("Hello world!");

	for (tag = (struct multiboot2_tag *)(multiboot_header + 8);
	     tag->type != MULTIBOOT2_END;
	     tag = (struct multiboot2_tag *)((byte *)tag +
	                                     ((tag->size + 7) & ~7))) {
		if (tag->type == MULTIBOOT2_MODULE) {
			struct multiboot2_tag_module *m =
				(struct multiboot2_tag_module *)tag;
			putchar(((char *)(ulong)m->mod_start)[0]);
			putchar('*');
			puts((char *)m->string);
		}
	}
	while(1);
}
