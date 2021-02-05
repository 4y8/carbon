MKSHELL=$PLAN9/bin/rc

OFILES=kernel/kernel.o\
	boot/boot.o
IMG=carbon

$IMG.img: $OFILES $IMG.elf
	aarch64-elf-objcopy $IMG.elf -O binary $IMG.img

$IMG.elf:
	aarch64-elf-gcc -T \
	    scripts/linker.ld \
	    -o $IMG.elf \
	    -ffreestanding \
	    -nostdlib $OFILES -lgcc


nuke:V:
	for (file in $OFILES)
	    rm $file

test:V: carbon.img
	qemu-system-aarch64 -M raspi3 -serial stdio -kernel carbon.img

%.o:
	cd `{dirname $stem.o}; mk; cd `{git rev-parse --show-toplevel}
