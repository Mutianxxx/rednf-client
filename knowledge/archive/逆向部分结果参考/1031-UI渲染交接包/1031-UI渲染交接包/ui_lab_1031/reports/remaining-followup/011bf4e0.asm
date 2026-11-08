
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bf4e0 <.text>:
 11bf4e0: 55                           	push	ebp
 11bf4e1: 8b ec                        	mov	ebp, esp
 11bf4e3: 56                           	push	esi
 11bf4e4: 8b f1                        	mov	esi, ecx
 11bf4e6: e8 b5 fc ff ff               	call	0x11bf1a0
 11bf4eb: f6 45 08 01                  	test	byte ptr [ebp + 0x8], 0x1
 11bf4ef: 74 09                        	je	0x11bf4fa <.text+0x1a>
 11bf4f1: 56                           	push	esi
 11bf4f2: e8 c9 0e ff ff               	call	0x11b03c0
 11bf4f7: 83 c4 04                     	add	esp, 0x4
 11bf4fa: 8b c6                        	mov	eax, esi
 11bf4fc: 5e                           	pop	esi
 11bf4fd: 5d                           	pop	ebp
 11bf4fe: c2 04 00                     	ret	0x4
