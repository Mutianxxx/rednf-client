
<stdin>:	file format elf32-i386

Disassembly of section .text:

011be020 <.text>:
 11be020: 80 79 0d 00                  	cmp	byte ptr [ecx + 0xd], 0x0
 11be024: 75 03                        	jne	0x11be029 <.text+0x9>
 11be026: 32 c0                        	xor	al, al
 11be028: c3                           	ret
 11be029: 8b 15 f0 24 a4 01            	mov	edx, dword ptr [0x1a424f0]
 11be02f: 33 c0                        	xor	eax, eax
 11be031: 3b 51 34                     	cmp	edx, dword ptr [ecx + 0x34]
 11be034: 0f 94 c0                     	sete	al
 11be037: c3                           	ret
