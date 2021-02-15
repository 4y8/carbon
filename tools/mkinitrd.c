#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct initrd_superblock {
	unsigned char magic;
	unsigned int ninode;
} __attribute__((packed));

struct initrd_inode {
	char name[128];
	char type;
	unsigned long offset;
	unsigned long length;
} __attribute__((packed));

long offset = 0;
FILE *ofile;

static void
ewrite(void *buf, size_t size)
{
	if (1 == fwrite(buf, size, 1, ofile)) {
		offset += size;
	} else {
		exit(1);
	}
}

int
main(int argc, char **argv)
{
	FILE *ifile;
	struct initrd_inode inodes[argc - 1];
	struct initrd_superblock superblock;
	char *buf;

	ofile = fopen("./initrd.img", "w");

	superblock.magic = 0x42;
	superblock.ninode = argc - 1;
	ewrite(&superblock, sizeof(superblock));

	memset(inodes, 1, sizeof(inodes));
	ewrite(inodes, sizeof(inodes));
	for (int i = 1; i < argc; ++i) {
		strncpy(inodes[i - 1].name, argv[i], 128);
		ifile = fopen(argv[i], "r");
		fseek(ifile, 0, SEEK_END);
		inodes[i - 1].length = ftell(ifile);
		inodes[i - 1].offset = offset;
		inodes[i - 1].type = 0;

		fseek(ifile, 0, SEEK_SET);
		buf = malloc(inodes[i - 1].length);
		fread(buf, inodes[i - 1].length, 1, ifile);
		ewrite(buf, inodes[i - 1].length);
		free(buf);

		fclose(ifile);
	}
	fseek(ofile, sizeof(superblock), SEEK_SET);
	ewrite(inodes, sizeof(inodes));
	fclose(ofile);
}
