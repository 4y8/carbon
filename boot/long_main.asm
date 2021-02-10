global long_main

section .text
bits 64
long_main:
	mov ax, 0
	mov ss, ax
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	;; Get arguments given by the bootloader
	mov esi, [rsp]
	mov edi, [rsp + 4]
	extern kernel_main
	call kernel_main
	hlt
