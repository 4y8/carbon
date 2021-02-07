<config.mk

MKSHELL=$PLAN9/bin/rc

FILES=boot/boot.o boot/multiboot_header.o
kernel=kernel.bin
iso=carbon.iso

all:V: $iso

$iso: $OFILES $kernel
	mkdir iso iso/boot iso/boot/grub
	cp boot/grub.cfg iso/boot/grub
	cp kernel.bin iso/boot
	grub-mkrescue -o $iso iso
	rm -rf iso

nuke:V:
	rm -rf iso

$kernel: $OFILES
	ld -n -o $kernel -T linker.ld $OFILES

%.o:
	cd `{dirname $stem}; mk `{basename $stem}.o

run:V:
	qemu-system-x86_64 -cdrom $iso
