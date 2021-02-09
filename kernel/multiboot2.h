#ifndef __MULTIBOOT2_H_
#define __MULTIBOOT2_H_

#include <types.h>

#define MULTIBOOT2_BOOTLOADER_MAGIC 0x36d76289

enum {
	MULTIBOOT2_END = 0,
	MULTIBOOT2_MODULE = 1,
	MULTIBOOT2_STRING = 3
};

struct multiboot2_tag {
	u32 type;
	u32 size;
} __attribute__((packed));

struct multiboot2_tag_module {
	u32 type;
	u32 size;
	u32 mod_start;
	u32 mod_end;
	char *string;
} __attribute__((packed));

struct multiboot2_tag_string {
	u32 type;
	u32 size;
	char *string;
} __attribute__((packed));

#endif /* __MULTIBOOT2_H_ */
