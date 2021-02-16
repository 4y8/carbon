#include <libc.h>

#include "initrd.h"
#include "multiboot2.h"

#define SUPERBLOCK_MAGIC 0x42
#define MAX_FDS 1024

enum ftype {
	FILE, DIR
};

struct superblock {
	byte magic;
	uint ninode;
} __attribute__((packed));

struct inode {
	char name[128];
	byte type;
	ulong offset;
	ulong length;
} __attribute__((packed));

static struct {
	ulong pos;
	struct inode *inode;
} fds[MAX_FDS];

static byte *initrd_root;
static uint ninode;

void
initrd_load(struct multiboot2_tag_module *module)
{
	void *p;
	struct superblock *superblock;

	p = (void *)(ulong)module->mod_start;

	superblock = (struct superblock *)p;
	if (superblock->magic != SUPERBLOCK_MAGIC)
		return;
	ninode = superblock->ninode;
	initrd_root = ((byte *)p + sizeof(struct superblock));
}

int
initrd_open(char *file)
{
	unsigned int fd, i;

	for (i = 0; i < ninode; ++i) {
		if (streq(file, ((struct inode *)initrd_root)[i].name))
			break;
	}

	if (i == ninode)
		return -1;

	for (fd = 0; fd < MAX_FDS; ++fd) {
		if (fds[fd].inode == nil) {
			fds[fd].pos = 0;
			fds[fd].inode = (struct inode *)initrd_root + i;
		}
	}
	return fd;
}

ulong
initrd_read(int fd, byte *buf, ulong size)
{
	if (size + fds[fd].pos > fds[fd].inode->length)
		size = fds[fd].inode->length - fds[fd].pos;

	memcpy(initrd_root + fds[fd].inode->offset + fds[fd].pos, buf, size);
	return size;
}

void
initrd_seek(int fd, ulong n, int type)
{
	switch ((enum seek)type) {
	case SEEK_CUR:
		fds[fd].pos += n;
		break;
	case SEEK_BEGIN:
		fds[fd].pos = n;
		break;
	case SEEK_END:
		fds[fd].pos = fds[fd].inode->length + n;
		break;
	}
}

void
initrd_close(int fd)
{
	fds[fd].inode = nil;
}

ulong
initrd_tell(int fd)
{
	return fds[fd].pos;
}
