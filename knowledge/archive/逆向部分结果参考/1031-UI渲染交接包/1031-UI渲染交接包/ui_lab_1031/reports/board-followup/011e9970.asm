
<stdin>:	file format elf32-i386

Disassembly of section .text:

011e9970 <.text>:
 11e9970: 55                           	push	ebp
 11e9971: 8b ec                        	mov	ebp, esp
 11e9973: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11e9976: 83 e8 00                     	sub	eax, 0x0
 11e9979: 74 14                        	je	0x11e998f <.text+0x1f>
 11e997b: 48                           	dec	eax
 11e997c: 75 1e                        	jne	0x11e999c <.text+0x2c>
 11e997e: 8b 81 b8 02 00 00            	mov	eax, dword ptr [ecx + 0x2b8]
 11e9984: c7 40 24 01 00 00 00         	mov	dword ptr [eax + 0x24], 0x1
 11e998b: 5d                           	pop	ebp
 11e998c: c2 04 00                     	ret	0x4
 11e998f: 8b 89 b8 02 00 00            	mov	ecx, dword ptr [ecx + 0x2b8]
 11e9995: c7 41 24 00 00 00 00         	mov	dword ptr [ecx + 0x24], 0x0
 11e999c: 5d                           	pop	ebp
 11e999d: c2 04 00                     	ret	0x4
