
<stdin>:	file format elf32-i386

Disassembly of section .text:

100168da <.text>:
100168da: 56                           	push	esi
100168db: 8b f1                        	mov	esi, ecx
100168dd: 8b 86 ac 00 00 00            	mov	eax, dword ptr [esi + 0xac]
100168e3: 85 c0                        	test	eax, eax
100168e5: 74 06                        	je	0x100168ed <.text+0x13>
100168e7: 83 78 10 05                  	cmp	dword ptr [eax + 0x10], 0x5
100168eb: 74 12                        	je	0x100168ff <.text+0x25>
100168ed: e8 c0 0b 00 00               	call	0x100174b2 <.text+0xbd8>
100168f2: 80 78 14 00                  	cmp	byte ptr [eax + 0x14], 0x0
100168f6: 75 07                        	jne	0x100168ff <.text+0x25>
100168f8: 8b ce                        	mov	ecx, esi
100168fa: e8 ab ff ff ff               	call	0x100168aa
100168ff: 8b 86 bc 00 00 00            	mov	eax, dword ptr [esi + 0xbc]
10016905: 85 c0                        	test	eax, eax
10016907: 74 02                        	je	0x1001690b <.text+0x31>
10016909: ff d0                        	call	eax
1001690b: 8b 46 38                     	mov	eax, dword ptr [esi + 0x38]
1001690e: 5e                           	pop	esi
1001690f: c3                           	ret
