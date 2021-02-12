#ifndef __INITRD_H_
#define __INITRD_H_

#include "multiboot2.h"

void initrd_load(struct multiboot2_tag_module *module);

#endif /* __INITRD_H_ */
