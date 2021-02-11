#ifndef __MULTIBOOT2_H_
#define __MULTIBOOT2_H_

#include <types.h>

#define MULTIBOOT2_BOOTLOADER_MAGIC 0x36d76289

enum {
	MULTIBOOT2_END = 0,
	MULTIBOOT2_CMDLINE = 1,
	MULTIBOOT2_BOOTLOADER_NAME = 2,
	MULTIBOOT2_MODULE = 3,
};

struct multiboot2_tag {
	u32 type;
	u32 size;
};

struct multiboot2_tag_module {
	u32 type;
	u32 size;
	u32 mod_start;
	u32 mod_end;
	char string[0];
};

struct multiboot2_tag_string {
	u32 type;
	u32 size;
	char string[0];
};

typedef void (*ModuleHandler)(struct multiboot2_tag_module *);

void multiboot2_init(ulong address);

void multiboot2_map_modules(ModuleHandler callback);

#endif /* __MULTIBOOT2_H_ */
