<config.mk

MKSHELL=$PLAN9/bin/rc

ASMOFILES=boot/boot.o boot/multiboot_header.o boot/long_main.o
KERNELOFILES=kernel/kernel.o
OFILES=$ASMOFILES $KERNELOFILES
KERNEL=kernel.bin
ISO=carbon.iso

all:V: $ISO

$ISO: $KERNEL
	mkdir -p iso iso/boot iso/boot/grub
	cp boot/grub.cfg iso/boot/grub
	cp $KERNEL iso/boot
	grub-mkrescue -o $ISO iso

nuke:V:
	for (file in iso $OFILES $ISO $KERNEL)
	    rm -rf $file

$KERNEL: $OFILES
	$LD -n -o $KERNEL -T linker.ld $OFILES

%.o: %.c
	cd `{dirname $stem}; mk `{basename $stem}.o

%.o: %.asm
	cd `{dirname $stem}; mk `{basename $stem}.o

run:V: $ISO
	qemu-system-x86_64 -cdrom $ISO
