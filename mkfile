<config.mk

MKSHELL=$PLAN9/bin/rc

ASMOFILES=boot/boot.o boot/multiboot_header.o boot/long_main.o
KERNELOFILES=kernel/kernel.o kernel/multiboot2.o kernel/initrd.o
OFILES=$ASMOFILES $KERNELOFILES
KERNEL=kernel.bin

ISO=carbon.iso

LIBC=lib/libc.a
LIBOFILES=lib/io.o lib/fmt.o lib/fs.o lib/string.o lib/libc.o lib/mem.o

all:V: $ISO

$ISO: $KERNEL initrd.img boot/grub.cfg
	mkdir -p iso iso/boot iso/boot/grub
	cp initrd.img iso/initrd
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	cp $KERNEL iso/boot
	grub-mkrescue -o $ISO iso

nuke:V:
	for (file in iso $OFILES $ISO $KERNEL $LIBC)
	    rm -rf $file

$KERNEL: $OFILES $LIBC
	$LD $LDFLAGS -n -o $KERNEL -T linker.ld $OFILES -lc

initrd.img: mkinitrd
	./mkinitrd initrd/*

%.o: %.c
	$CC $CFLAGS -c $stem.c -o $stem.o

%.o: %.asm
	nasm -felf64 $stem.asm -o $stem.o

%: tools/%.c
	cd tools; mk $stem; cp $stem $ROOT/

lib/libc.a: $LIBOFILES
	$AR rsc lib/libc.a $LIBOFILES

run:V: $ISO
	qemu-system-x86_64 -cdrom $ISO
