#include <fs.h>
#include <types.h>

#define MAGIC_NUMBER 0x42

struct superblock {
	byte magic_number;
	long nfree_blocks;
	byte *free_blocks;
};

enum file_type {
	FT_DIRECTORY,
	FT_FILE,
	FT_LINK
};

struct inode {
	byte owner;
	byte type;
	uint nlink;
	ulong size;
	byte *direct_blocks[10];
};
