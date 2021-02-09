#include "initrd.h"
#include <types.h>

struct initrd_superblock {
	unsigned char magic;
	int ninode;
} __attribute__((packed, aligned(1)));

struct initrd_inode {
	char name[128];
	ulong offset;
	ulong length;
} __attribute__((packed, aligned(1)));
