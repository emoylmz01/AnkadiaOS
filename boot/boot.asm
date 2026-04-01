MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
FLAGS    equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 16
stack_bottom:
resb 16384 ; 16 KB yığın (stack)
stack_top:

section .text
global _start:function (_start.end - _start)
extern kmain ; kernel.c içindeki asıl fonksiyonumuz

_start:
	; Korumalı moda (protected mode) geçiş sonrası 
	; yığın (stack) imlecini belirliyoruz.
	mov esp, stack_top

	; GDT yükleme işlemleri için register sıfırlaması
	push ebx
	push eax
	
	; C ile yazdığımız kernel ana fonksiyonumuza atlıyoruz
	call kmain

	; Eğer kernel'den dönülürse sistemi güvenli bir şekilde durdur.
	cli
.hang:	hlt
	jmp .hang
.end:
