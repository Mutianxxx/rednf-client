
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c4ac0 <.text>:
 11c4ac0: 55                           	push	ebp
 11c4ac1: 8b ec                        	mov	ebp, esp
 11c4ac3: 56                           	push	esi
 11c4ac4: 8b f1                        	mov	esi, ecx
 11c4ac6: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11c4aca: 74 0a                        	je	0x11c4ad6 <.text+0x16>
 11c4acc: b8 02 00 00 80               	mov	eax, 0x80000002
 11c4ad1: 5e                           	pop	esi
 11c4ad2: 5d                           	pop	ebp
 11c4ad3: c2 1c 00                     	ret	0x1c
 11c4ad6: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c4ad9: 57                           	push	edi
 11c4ada: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 11c4add: 50                           	push	eax
 11c4ade: 8b cf                        	mov	ecx, edi
 11c4ae0: e8 eb 00 ff ff               	call	0x11b4bd0
 11c4ae5: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11c4ae8: 51                           	push	ecx
 11c4ae9: 8b cf                        	mov	ecx, edi
 11c4aeb: 89 86 b8 02 00 00            	mov	dword ptr [esi + 0x2b8], eax
 11c4af1: e8 da 00 ff ff               	call	0x11b4bd0
 11c4af6: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
 11c4af9: 52                           	push	edx
 11c4afa: 8b cf                        	mov	ecx, edi
 11c4afc: 89 86 c0 02 00 00            	mov	dword ptr [esi + 0x2c0], eax
 11c4b02: e8 c9 00 ff ff               	call	0x11b4bd0
 11c4b07: 89 86 bc 02 00 00            	mov	dword ptr [esi + 0x2bc], eax
 11c4b0d: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11c4b10: 83 f8 ff                     	cmp	eax, -0x1
 11c4b13: 74 0e                        	je	0x11c4b23 <.text+0x63>
 11c4b15: 50                           	push	eax
 11c4b16: 8b cf                        	mov	ecx, edi
 11c4b18: e8 b3 00 ff ff               	call	0x11b4bd0
 11c4b1d: 89 86 c4 02 00 00            	mov	dword ptr [esi + 0x2c4], eax
 11c4b23: 8b 55 1c                     	mov	edx, dword ptr [ebp + 0x1c]
 11c4b26: 85 d2                        	test	edx, edx
 11c4b28: 74 19                        	je	0x11c4b43 <.text+0x83>
 11c4b2a: 8b c2                        	mov	eax, edx
 11c4b2c: 8d 78 02                     	lea	edi, [eax + 0x2]
 11c4b2f: 90                           	nop
 11c4b30: 66 8b 08                     	mov	cx, word ptr [eax]
 11c4b33: 83 c0 02                     	add	eax, 0x2
 11c4b36: 66 85 c9                     	test	cx, cx
 11c4b39: 75 f5                        	jne	0x11c4b30 <.text+0x70>
 11c4b3b: 2b c7                        	sub	eax, edi
 11c4b3d: d1 f8                        	sar	eax
 11c4b3f: 50                           	push	eax
 11c4b40: 52                           	push	edx
 11c4b41: eb 23                        	jmp	0x11c4b66 <.text+0xa6>
 11c4b43: 68 6c 6c 56 01               	push	0x1566c6c
 11c4b48: e8 a3 b3 fd ff               	call	0x119fef0
 11c4b4d: 8b c8                        	mov	ecx, eax
 11c4b4f: 83 c4 04                     	add	esp, 0x4
 11c4b52: 8d 79 02                     	lea	edi, [ecx + 0x2]
 11c4b55: 66 8b 11                     	mov	dx, word ptr [ecx]
 11c4b58: 83 c1 02                     	add	ecx, 0x2
 11c4b5b: 66 85 d2                     	test	dx, dx
 11c4b5e: 75 f5                        	jne	0x11c4b55 <.text+0x95>
 11c4b60: 2b cf                        	sub	ecx, edi
 11c4b62: d1 f9                        	sar	ecx
 11c4b64: 51                           	push	ecx
 11c4b65: 50                           	push	eax
 11c4b66: 8d 8e cc 02 00 00            	lea	ecx, [esi + 0x2cc]
 11c4b6c: e8 bf bb 24 ff               	call	0x410730
 11c4b71: 8b 55 20                     	mov	edx, dword ptr [ebp + 0x20]
 11c4b74: 85 d2                        	test	edx, edx
 11c4b76: 74 1b                        	je	0x11c4b93 <.text+0xd3>
 11c4b78: 8b c2                        	mov	eax, edx
 11c4b7a: 8d 78 02                     	lea	edi, [eax + 0x2]
 11c4b7d: 8d 49 00                     	lea	ecx, [ecx]
 11c4b80: 66 8b 08                     	mov	cx, word ptr [eax]
 11c4b83: 83 c0 02                     	add	eax, 0x2
 11c4b86: 66 85 c9                     	test	cx, cx
 11c4b89: 75 f5                        	jne	0x11c4b80 <.text+0xc0>
 11c4b8b: 2b c7                        	sub	eax, edi
 11c4b8d: d1 f8                        	sar	eax
 11c4b8f: 50                           	push	eax
 11c4b90: 52                           	push	edx
 11c4b91: eb 23                        	jmp	0x11c4bb6 <.text+0xf6>
 11c4b93: 68 d8 7a 56 01               	push	0x1567ad8
 11c4b98: e8 53 b3 fd ff               	call	0x119fef0
 11c4b9d: 8b c8                        	mov	ecx, eax
 11c4b9f: 83 c4 04                     	add	esp, 0x4
 11c4ba2: 8d 79 02                     	lea	edi, [ecx + 0x2]
 11c4ba5: 66 8b 11                     	mov	dx, word ptr [ecx]
 11c4ba8: 83 c1 02                     	add	ecx, 0x2
 11c4bab: 66 85 d2                     	test	dx, dx
 11c4bae: 75 f5                        	jne	0x11c4ba5 <.text+0xe5>
 11c4bb0: 2b cf                        	sub	ecx, edi
 11c4bb2: d1 f9                        	sar	ecx
 11c4bb4: 51                           	push	ecx
 11c4bb5: 50                           	push	eax
 11c4bb6: 8d 8e ec 02 00 00            	lea	ecx, [esi + 0x2ec]
 11c4bbc: e8 6f bb 24 ff               	call	0x410730
 11c4bc1: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11c4bc7: e8 f4 f1 fe ff               	call	0x11b3dc0
 11c4bcc: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11c4bd2: 89 46 38                     	mov	dword ptr [esi + 0x38], eax
 11c4bd5: e8 f6 f1 fe ff               	call	0x11b3dd0
 11c4bda: 89 46 3c                     	mov	dword ptr [esi + 0x3c], eax
 11c4bdd: b8 ff ff b8 ff               	mov	eax, 0xffb8ffff
 11c4be2: 89 86 38 03 00 00            	mov	dword ptr [esi + 0x338], eax
 11c4be8: 89 86 3c 03 00 00            	mov	dword ptr [esi + 0x33c], eax
 11c4bee: b8 01 00 00 00               	mov	eax, 0x1
 11c4bf3: 5f                           	pop	edi
 11c4bf4: c7 86 10 03 00 00 00 00 00 00	mov	dword ptr [esi + 0x310], 0x0
 11c4bfe: c7 86 34 03 00 00 dd c5 93 ff	mov	dword ptr [esi + 0x334], 0xff93c5dd
 11c4c08: c7 86 40 03 00 00 8c 8c 8c ff	mov	dword ptr [esi + 0x340], 0xff8c8c8c
 11c4c12: c6 86 94 03 00 00 00         	mov	byte ptr [esi + 0x394], 0x0
 11c4c19: c7 86 98 03 00 00 ff ff ff ff	mov	dword ptr [esi + 0x398], 0xffffffff
 11c4c23: 88 46 04                     	mov	byte ptr [esi + 0x4], al
 11c4c26: 5e                           	pop	esi
 11c4c27: 5d                           	pop	ebp
 11c4c28: c2 1c 00                     	ret	0x1c
