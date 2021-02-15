<config.mk

MKSHELL=$PLAN9/bin/rc

ASMOFILES=boot/boot.o boot/multiboot_header.o boot/long_main.o
KERNELOFILES=kernel/kernel.o kernel/multiboot2.o kernel/initrd.o
OFILES=$ASMOFILES $KERNELOFILES
KERNEL=kernel.bin
ISO=carbon.iso
LIB=io fmt fs string libc
LIBFILES=${LIB:%=lib/lib%.a}
LIBFLAGS=${LIB:%=-l%}

all:V: $ISO

$ISO: $KERNEL initrd.img boot/grub.cfg
	mkdir -p iso iso/boot iso/boot/grub
	cp initrd.img iso/initrd
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	cp $KERNEL iso/boot
	grub-mkrescue -o $ISO iso

nuke:V:
	for (file in iso $OFILES $ISO $KERNEL)
	    rm -rf $file

$KERNEL: $OFILES $LIBFILES
	$LD $LDFLAGS -n -o $KERNEL -T linker.ld $OFILES $LIBFLAGS

initrd.img: mkinitrd
	./mkinitrd initrd/*

lib/lib%.a: lib/%.o lib/%.h
	cd lib;	$AR rsc lib$stem.a $stem.o

%.o: %.c
	base=`{basename $stem}
	cd `{dirname $stem}; $CC $CFLAGS -c $base.c -o $base.o

%.o: %.asm
	cd `{dirname $stem}; nasm -felf64 `{basename $stem}.asm

%: tools/%.c
	cd tools; mk $stem; cp $stem $ROOT/

run:V: $ISO
	qemu-system-x86_64 -cdrom $ISO
