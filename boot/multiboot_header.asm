section .multiboot_header
header_start:
	dd 0xe85250d6			; multiboot 2's magic number
	dd 0				; architecure (i386 protected)
	dd header_end - header_start	; header length
	;; Checksum
	dd 0x100000000 - (0xe85250d6 + 0 + (header_end - header_start))
	dw 0			; type
	dw 0			; flags
	dd 8			; size
header_end:
