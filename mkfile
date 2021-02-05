MKSHELL=$PLAN9/bin/rc

OFILES=kernel/kernel.o\
	boot/boot.o
IMG=kernel8
LIB=lib/uart.a

$IMG.img: $OFILES $IMG.elf
	aarch64-elf-objcopy $IMG.elf -O binary $IMG.img

$IMG.elf: $LIB
	aarch64-elf-gcc -T \
	    scripts/linker.ld \
	    -o $IMG.elf \
	    -ffreestanding \
	    -nostdlib $OFILES $LIB -lgcc

nuke:V:
	for (file in $OFILES $LIB $IMG.elf)
	    rm -f $file

test:V: $IMG.img
	qemu-system-aarch64 -M raspi3 -serial stdio -kernel $IMG.img

%.o:
	cd `{dirname $stem.o}; mk

%.a:
	cd lib; mk `{basename $stem}.a

