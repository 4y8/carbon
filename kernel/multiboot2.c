#include <types.h>

#include "multiboot2.h"

static ulong header_address;

void
multiboot2_init(ulong address)
{
	header_address = address;
}

void
multiboot2_map_modules(ModuleHandler callback)
{
	struct multiboot2_tag *tag;

	for (tag = (struct multiboot2_tag *)header_address;
	     tag->type != MULTIBOOT2_END;
	     tag = (struct multiboot2_tag *)((byte *)tag +
	                                     ((tag->size + 7) & ~7))) {
		if (tag->type == MULTIBOOT2_MODULE)
			callback((struct multiboot2_tag_module *)tag);
	}
}
