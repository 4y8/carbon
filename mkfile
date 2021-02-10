<config.mk

MKSHELL=$PLAN9/bin/rc

ASMOFILES=boot/boot.o boot/multiboot_header.o boot/long_main.o
KERNELOFILES=kernel/kernel.o
OFILES=$ASMOFILES $KERNELOFILES
KERNEL=kernel.bin
ISO=carbon.iso
LIB=libio.a
LIBFLAGS=${LIB:lib%.a=-l%}

all:V: $ISO

$ISO: $KERNEL initrd.img boot/grub.cfg
	mkdir -p iso iso/boot iso/boot/grub iso/fs
	cp initrd.img iso/fs/initrd
	cp boot/grub.cfg iso/boot/grub/grub.cfg
	cp $KERNEL iso/boot
	grub-mkrescue -o $ISO iso

nuke:V:
	for (file in iso $OFILES $ISO $KERNEL)
	    rm -rf $file

$KERNEL: $OFILES $LIB
	$LD $LDFLAGS -n -o $KERNEL -T linker.ld $OFILES $LIBFLAGS

initrd.img: mkinitrd
	./mkinitrd initrd/*

%.o: %.c
	cd `{dirname $stem}; mk `{basename $stem}.o

%.o: %.asm
	cd `{dirname $stem}; mk `{basename $stem}.o

lib%.a: lib/%.c
	cd lib; mk lib$stem.a

%: tools/%.c
	cd tools; mk $stem; cp $stem $ROOT/

run:V: $ISO
	qemu-system-x86_64 -cdrom $ISO
