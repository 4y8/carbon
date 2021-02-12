#include <types.h>

#include "initrd.h"
#include "multiboot2.h"

#define SUPERBLOCK_MAGIC 0x42

enum ftype {
	FILE, DIR
};

struct superblock {
	byte magic;
	int ninode;
} __attribute__((packed));

struct inode {
	char name[128];
	byte type;
	ulong offset;
	ulong length;
} __attribute__((packed));

void
initrd_load(struct multiboot2_tag_module *module)
{
	void *p;
	struct superblock *superblock;
	struct inode *inodes;

	p = (void *)(ulong)module->mod_start;

	superblock = (struct superblock *)p;
	if (superblock->magic != SUPERBLOCK_MAGIC)
		return;
	inodes = (struct inode *)((byte *)p + sizeof(struct superblock));

	for (int i = 0; i < superblock->ninode; ++i) {
	}
}
