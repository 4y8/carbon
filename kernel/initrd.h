#ifndef __INITRD_H_
#define __INITRD_H_

#include <types.h>
#include <fs.h>

#include "multiboot2.h"

void initrd_load(struct multiboot2_tag_module *module);

int initrd_open(char *file);

ulong initrd_read(int fd, byte *buf, ulong size);

void initrd_seek(int fd, ulong n, enum seek type);

void initrd_close(int fd);

ulong initrd_tell(int fd);

#endif /* __INITRD_H_ */
