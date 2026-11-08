
<stdin>:	file format elf32-i386

Disassembly of section .text:

0111af80 <.text>:
 111af80: c6 85 fa fd ff ff 00         	mov	byte ptr [ebp - 0x206], 0x0
 111af87: c6 85 fb fd ff ff 00         	mov	byte ptr [ebp - 0x205], 0x0
 111af8e: 39 9e 44 02 00 00            	cmp	dword ptr [esi + 0x244], ebx
 111af94: 0f 84 5f 01 00 00            	je	0x111b0f9 <.text+0x179>
 111af9a: 8b 95 f4 fd ff ff            	mov	edx, dword ptr [ebp - 0x20c]
 111afa0: 52                           	push	edx
 111afa1: 8d 86 40 03 00 00            	lea	eax, [esi + 0x340]
 111afa7: 50                           	push	eax
 111afa8: 8d 8e 3c 03 00 00            	lea	ecx, [esi + 0x33c]
 111afae: 51                           	push	ecx
 111afaf: 8b ce                        	mov	ecx, esi
 111afb1: e8 ca d6 ff ff               	call	0x1118680
 111afb6: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111afbc: 85 c9                        	test	ecx, ecx
 111afbe: 0f 84 35 01 00 00            	je	0x111b0f9 <.text+0x179>
 111afc4: e8 e7 7b f8 ff               	call	0x10a2bb0
 111afc9: 85 c0                        	test	eax, eax
 111afcb: 0f 84 28 01 00 00            	je	0x111b0f9 <.text+0x179>
 111afd1: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111afd7: e8 d4 7b f8 ff               	call	0x10a2bb0
 111afdc: 8b c8                        	mov	ecx, eax
 111afde: e8 5d c0 5d ff               	call	0x6f7040
 111afe3: 8b f8                        	mov	edi, eax
 111afe5: 8d 95 e0 fd ff ff            	lea	edx, [ebp - 0x220]
 111afeb: 52                           	push	edx
 111afec: 8b cf                        	mov	ecx, edi
 111afee: 89 bd f4 fd ff ff            	mov	dword ptr [ebp - 0x20c], edi
 111aff4: e8 17 27 20 00               	call	0x131d710 <.text+0x202790>
 111aff9: 8d 85 d4 fd ff ff            	lea	eax, [ebp - 0x22c]
 111afff: 50                           	push	eax
 111b000: 8b cf                        	mov	ecx, edi
 111b002: e8 69 b1 05 00               	call	0x1176170 <.text+0x5b1f0>
 111b007: 50                           	push	eax
 111b008: 8d 8d e0 fd ff ff            	lea	ecx, [ebp - 0x220]
 111b00e: e8 dd 4d 81 ff               	call	0x92fdf0
 111b013: 84 c0                        	test	al, al
 111b015: 0f 84 de 00 00 00            	je	0x111b0f9 <.text+0x179>
 111b01b: eb 03                        	jmp	0x111b020 <.text+0xa0>
 111b01d: 8d 49 00                     	lea	ecx, [ecx]
 111b020: 8d 8d e0 fd ff ff            	lea	ecx, [ebp - 0x220]
 111b026: e8 f5 28 84 ff               	call	0x95d920
 111b02b: 8b 08                        	mov	ecx, dword ptr [eax]
 111b02d: e8                           	<unknown>
 111b02e: 4e                           	dec	esi
 111b02f: e0                           	<unknown>
