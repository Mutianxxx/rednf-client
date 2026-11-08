
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b4bd0 <.text>:
 11b4bd0: 55                           	push	ebp
 11b4bd1: 8b ec                        	mov	ebp, esp
 11b4bd3: 56                           	push	esi
 11b4bd4: 8b f1                        	mov	esi, ecx
 11b4bd6: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
 11b4bd9: 8b 4e 5c                     	mov	ecx, dword ptr [esi + 0x5c]
 11b4bdc: 2b c8                        	sub	ecx, eax
 11b4bde: 57                           	push	edi
 11b4bdf: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 11b4be2: c1 f9 04                     	sar	ecx, 0x4
 11b4be5: 3b f9                        	cmp	edi, ecx
 11b4be7: 72 7d                        	jb	0x11b4c66 <.text+0x96>
 11b4be9: 68 18 a1 85 01               	push	0x185a118
 11b4bee: e8 fd b2 fe ff               	call	0x119fef0
 11b4bf3: 83 c4 04                     	add	esp, 0x4
 11b4bf6: f6 86 98 00 00 00 01         	test	byte ptr [esi + 0x98], 0x1
 11b4bfd: 0f 85 d5 00 00 00            	jne	0x11b4cd8 <.text+0x108>
 11b4c03: 83 7e 48 08                  	cmp	dword ptr [esi + 0x48], 0x8
 11b4c07: 72 05                        	jb	0x11b4c0e <.text+0x3e>
 11b4c09: 8b 4e 34                     	mov	ecx, dword ptr [esi + 0x34]
 11b4c0c: eb 03                        	jmp	0x11b4c11 <.text+0x41>
 11b4c0e: 8d 4e 34                     	lea	ecx, [esi + 0x34]
 11b4c11: 57                           	push	edi
 11b4c12: 51                           	push	ecx
 11b4c13: 50                           	push	eax
 11b4c14: 68 c8 a0 85 01               	push	0x185a0c8
 11b4c19: e8 d2 b2 fe ff               	call	0x119fef0
 11b4c1e: 83 c4 04                     	add	esp, 0x4
 11b4c21: 50                           	push	eax
 11b4c22: 68 88 09 00 00               	push	0x988
 11b4c27: 68 78 a0 85 01               	push	0x185a078
 11b4c2c: e8 bf b2 fe ff               	call	0x119fef0
 11b4c31: 83 c4 04                     	add	esp, 0x4
 11b4c34: 50                           	push	eax
 11b4c35: 68 e0 9f 85 01               	push	0x1859fe0
 11b4c3a: e8 b1 b2 fe ff               	call	0x119fef0
 11b4c3f: 83 c4 04                     	add	esp, 0x4
 11b4c42: 50                           	push	eax
 11b4c43: 6a 00                        	push	0x0
 11b4c45: e8 96 e0 fe ff               	call	0x11a2ce0
 11b4c4a: 83 8e 98 00 00 00 01         	or	dword ptr [esi + 0x98], 0x1
 11b4c51: 83 c4 20                     	add	esp, 0x20
 11b4c54: e8 77 60 00 00               	call	0x11bacd0 <.text+0x6100>
 11b4c59: 8b c8                        	mov	ecx, eax
 11b4c5b: e8 40 61 00 00               	call	0x11bada0 <.text+0x61d0>
 11b4c60: 5f                           	pop	edi
 11b4c61: 5e                           	pop	esi
 11b4c62: 5d                           	pop	ebp
 11b4c63: c2 04 00                     	ret	0x4
 11b4c66: 8b d7                        	mov	edx, edi
 11b4c68: 03 d2                        	add	edx, edx
 11b4c6a: 8b 04 d0                     	mov	eax, dword ptr [eax + 8*edx]
 11b4c6d: 85 c0                        	test	eax, eax
 11b4c6f: 75                           	<unknown>
