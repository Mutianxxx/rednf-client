
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be2b0 <.text>:
 11be2b0: 8b 15 00 25 a4 01            	mov	edx, dword ptr [0x1a42500]
 11be2b6: 33 c0                        	xor	eax, eax
 11be2b8: 3b 51 34                     	cmp	edx, dword ptr [ecx + 0x34]
 11be2bb: 0f 94 c0                     	sete	al
 11be2be: c3                           	ret
 11be2bf: cc                           	int3
