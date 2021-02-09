global start
extern long_main

section .text
bits 32
start:
	mov esp, stack_top

	;; Save the multiboot2 given by the bootloader
	push eax
	push ebx

	call set_up_page_tables
	call enable_paging

	lgdt [gdt64.pointer]
	jmp gdt64.code:long_main
	hlt

set_up_page_tables:
	mov eax, p3_table
	or eax, 0b11
	mov [p4_table], eax

	mov eax, p2_table
	or eax, 0b11
	mov [p3_table], eax

	mov ecx, 0
.map_p2_tables:
	mov eax, 0x200000
	mul ecx
	or eax, 0b10000011
	mov [p2_table + ecx * 8], eax

	inc ecx
	cmp ecx, 512
	jne .map_p2_tables

	ret

enable_paging:
	mov eax, p4_table
	mov cr3, eax

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	ret

section .rodata
gdt64:
	dq 0
.code: equ $ - gdt64
	dq (1<<43) | (1<<44) | (1<<47) | (1<<53)
.pointer:
	dw $ - gdt64 - 1
	dq gdt64

section .bss
align 4096
p4_table:
	resb 4096
p3_table:
	resb 4096
p2_table:
	resb 4096
stack_bottom:
	resq 4096
stack_top:
