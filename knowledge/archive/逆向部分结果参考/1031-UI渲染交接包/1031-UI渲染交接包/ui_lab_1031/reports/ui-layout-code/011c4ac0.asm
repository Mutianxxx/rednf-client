
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
 11c4c2b: cc                           	int3
 11c4c2c: cc                           	int3
 11c4c2d: cc                           	int3
 11c4c2e: cc                           	int3
 11c4c2f: cc                           	int3
 11c4c30: 55                           	push	ebp
 11c4c31: 8b ec                        	mov	ebp, esp
 11c4c33: 6a ff                        	push	-0x1
 11c4c35: 68 48 80 4c 01               	push	0x14c8048
 11c4c3a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c4c40: 50                           	push	eax
 11c4c41: 83 ec 10                     	sub	esp, 0x10
 11c4c44: 53                           	push	ebx
 11c4c45: 56                           	push	esi
 11c4c46: 57                           	push	edi
 11c4c47: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c4c4c: 33 c5                        	xor	eax, ebp
 11c4c4e: 50                           	push	eax
 11c4c4f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c4c52: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c4c58: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
 11c4c5b: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 11c4c5e: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c4c61: 8b 5d 3c                     	mov	ebx, dword ptr [ebp + 0x3c]
 11c4c64: 8b f1                        	mov	esi, ecx
 11c4c66: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11c4c69: 89 4d e8                     	mov	dword ptr [ebp - 0x18], ecx
 11c4c6c: 8b 4d 40                     	mov	ecx, dword ptr [ebp + 0x40]
 11c4c6f: 89 55 f0                     	mov	dword ptr [ebp - 0x10], edx
 11c4c72: 8b 55 44                     	mov	edx, dword ptr [ebp + 0x44]
 11c4c75: 89 4d ec                     	mov	dword ptr [ebp - 0x14], ecx
 11c4c78: 89 55 e4                     	mov	dword ptr [ebp - 0x1c], edx
 11c4c7b: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11c4c7f: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11c4c86: 74 39                        	je	0x11c4cc1 <.text+0x201>
 11c4c88: 83 7d 30 08                  	cmp	dword ptr [ebp + 0x30], 0x8
 11c4c8c: 72 0c                        	jb	0x11c4c9a <.text+0x1da>
 11c4c8e: 8b 45 1c                     	mov	eax, dword ptr [ebp + 0x1c]
 11c4c91: 50                           	push	eax
 11c4c92: e8 90 0e 21 00               	call	0x13d5b27 <.text+0x211067>
 11c4c97: 83 c4 04                     	add	esp, 0x4
 11c4c9a: 8b 55 18                     	mov	edx, dword ptr [ebp + 0x18]
 11c4c9d: 33 c9                        	xor	ecx, ecx
 11c4c9f: 52                           	push	edx
 11c4ca0: c7 45 30 07 00 00 00         	mov	dword ptr [ebp + 0x30], 0x7
 11c4ca7: c7 45 2c 00 00 00 00         	mov	dword ptr [ebp + 0x2c], 0x0
 11c4cae: 66 89 4d 1c                  	mov	word ptr [ebp + 0x1c], cx
 11c4cb2: e8 70 0e 21 00               	call	0x13d5b27 <.text+0x211067>
 11c4cb7: b8 02 00 00 80               	mov	eax, 0x80000002
 11c4cbc: e9 8f 01 00 00               	jmp	0x11c4e50 <.text+0x390>
 11c4cc1: 50                           	push	eax
 11c4cc2: 8b cf                        	mov	ecx, edi
 11c4cc4: e8 07 ff fe ff               	call	0x11b4bd0
 11c4cc9: 89 86 b8 02 00 00            	mov	dword ptr [esi + 0x2b8], eax
 11c4ccf: 8b 45 e8                     	mov	eax, dword ptr [ebp - 0x18]
 11c4cd2: 50                           	push	eax
 11c4cd3: 8b cf                        	mov	ecx, edi
 11c4cd5: e8 f6 fe fe ff               	call	0x11b4bd0
 11c4cda: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 11c4cdd: 51                           	push	ecx
 11c4cde: 8b cf                        	mov	ecx, edi
 11c4ce0: 89 86 c0 02 00 00            	mov	dword ptr [esi + 0x2c0], eax
 11c4ce6: e8 e5 fe fe ff               	call	0x11b4bd0
 11c4ceb: 89 86 bc 02 00 00            	mov	dword ptr [esi + 0x2bc], eax
 11c4cf1: 83 fb ff                     	cmp	ebx, -0x1
 11c4cf4: 74 0e                        	je	0x11c4d04 <.text+0x244>
 11c4cf6: 53                           	push	ebx
 11c4cf7: 8b cf                        	mov	ecx, edi
 11c4cf9: e8 d2 fe fe ff               	call	0x11b4bd0
 11c4cfe: 89 86 c4 02 00 00            	mov	dword ptr [esi + 0x2c4], eax
 11c4d04: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
 11c4d07: 85 d2                        	test	edx, edx
 11c4d09: 74 18                        	je	0x11c4d23 <.text+0x263>
 11c4d0b: 8b c2                        	mov	eax, edx
 11c4d0d: 8d 78 02                     	lea	edi, [eax + 0x2]
 11c4d10: 66 8b 08                     	mov	cx, word ptr [eax]
 11c4d13: 83 c0 02                     	add	eax, 0x2
 11c4d16: 66 85 c9                     	test	cx, cx
 11c4d19: 75 f5                        	jne	0x11c4d10 <.text+0x250>
 11c4d1b: 2b c7                        	sub	eax, edi
 11c4d1d: d1 f8                        	sar	eax
 11c4d1f: 50                           	push	eax
 11c4d20: 52                           	push	edx
 11c4d21: eb 23                        	jmp	0x11c4d46 <.text+0x286>
 11c4d23: 68 6c 6c 56 01               	push	0x1566c6c
 11c4d28: e8 c3 b1 fd ff               	call	0x119fef0
 11c4d2d: 8b c8                        	mov	ecx, eax
 11c4d2f: 83 c4 04                     	add	esp, 0x4
 11c4d32: 8d 79 02                     	lea	edi, [ecx + 0x2]
 11c4d35: 66 8b 11                     	mov	dx, word ptr [ecx]
 11c4d38: 83 c1 02                     	add	ecx, 0x2
 11c4d3b: 66 85 d2                     	test	dx, dx
 11c4d3e: 75 f5                        	jne	0x11c4d35 <.text+0x275>
 11c4d40: 2b cf                        	sub	ecx, edi
 11c4d42: d1 f9                        	sar	ecx
 11c4d44: 51                           	push	ecx
 11c4d45: 50                           	push	eax
 11c4d46: 8d 8e cc 02 00 00            	lea	ecx, [esi + 0x2cc]
 11c4d4c: e8 df b9 24 ff               	call	0x410730
 11c4d51: 8b 55 e4                     	mov	edx, dword ptr [ebp - 0x1c]
 11c4d54: 85 d2                        	test	edx, edx
 11c4d56: 74 1b                        	je	0x11c4d73 <.text+0x2b3>
 11c4d58: 8b c2                        	mov	eax, edx
 11c4d5a: 8d 78 02                     	lea	edi, [eax + 0x2]
 11c4d5d: 8d 49 00                     	lea	ecx, [ecx]
 11c4d60: 66 8b 08                     	mov	cx, word ptr [eax]
 11c4d63: 83 c0 02                     	add	eax, 0x2
 11c4d66: 66 85 c9                     	test	cx, cx
 11c4d69: 75 f5                        	jne	0x11c4d60 <.text+0x2a0>
 11c4d6b: 2b c7                        	sub	eax, edi
 11c4d6d: d1 f8                        	sar	eax
 11c4d6f: 50                           	push	eax
 11c4d70: 52                           	push	edx
 11c4d71: eb 23                        	jmp	0x11c4d96 <.text+0x2d6>
 11c4d73: 68 d8 7a 56 01               	push	0x1567ad8
 11c4d78: e8 73 b1 fd ff               	call	0x119fef0
 11c4d7d: 8b c8                        	mov	ecx, eax
 11c4d7f: 83 c4 04                     	add	esp, 0x4
 11c4d82: 8d 79 02                     	lea	edi, [ecx + 0x2]
 11c4d85: 66 8b 11                     	mov	dx, word ptr [ecx]
 11c4d88: 83 c1 02                     	add	ecx, 0x2
 11c4d8b: 66 85 d2                     	test	dx, dx
 11c4d8e: 75 f5                        	jne	0x11c4d85 <.text+0x2c5>
 11c4d90: 2b cf                        	sub	ecx, edi
 11c4d92: d1 f9                        	sar	ecx
 11c4d94: 51                           	push	ecx
 11c4d95: 50                           	push	eax
 11c4d96: 8d 8e ec 02 00 00            	lea	ecx, [esi + 0x2ec]
 11c4d9c: e8 8f b9 24 ff               	call	0x410730
 11c4da1: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11c4da7: e8 14 f0 fe ff               	call	0x11b3dc0
 11c4dac: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11c4db2: 89 46 38                     	mov	dword ptr [esi + 0x38], eax
 11c4db5: e8 16 f0 fe ff               	call	0x11b3dd0
 11c4dba: 8b 55 38                     	mov	edx, dword ptr [ebp + 0x38]
 11c4dbd: 6a ff                        	push	-0x1
 11c4dbf: 6a 00                        	push	0x0
 11c4dc1: 8d 4d 18                     	lea	ecx, [ebp + 0x18]
 11c4dc4: 89 46 3c                     	mov	dword ptr [esi + 0x3c], eax
 11c4dc7: 8a 45 48                     	mov	al, byte ptr [ebp + 0x48]
 11c4dca: 51                           	push	ecx
 11c4dcb: 8d 8e 14 03 00 00            	lea	ecx, [esi + 0x314]
 11c4dd1: 89 96 10 03 00 00            	mov	dword ptr [esi + 0x310], edx
 11c4dd7: 88 86 44 03 00 00            	mov	byte ptr [esi + 0x344], al
 11c4ddd: e8 4e 05 24 ff               	call	0x405330
 11c4de2: 83 7d 30 08                  	cmp	dword ptr [ebp + 0x30], 0x8
 11c4de6: b8 ff ff b8 ff               	mov	eax, 0xffb8ffff
 11c4deb: c7 86 34 03 00 00 dd c5 93 ff	mov	dword ptr [esi + 0x334], 0xff93c5dd
 11c4df5: 89 86 38 03 00 00            	mov	dword ptr [esi + 0x338], eax
 11c4dfb: 89 86 3c 03 00 00            	mov	dword ptr [esi + 0x33c], eax
 11c4e01: c7 86 40 03 00 00 8c 8c 8c ff	mov	dword ptr [esi + 0x340], 0xff8c8c8c
 11c4e0b: c6 86 94 03 00 00 00         	mov	byte ptr [esi + 0x394], 0x0
 11c4e12: c7 86 98 03 00 00 ff ff ff ff	mov	dword ptr [esi + 0x398], 0xffffffff
 11c4e1c: c6 46 04 01                  	mov	byte ptr [esi + 0x4], 0x1
 11c4e20: 72 0c                        	jb	0x11c4e2e <.text+0x36e>
 11c4e22: 8b 55 1c                     	mov	edx, dword ptr [ebp + 0x1c]
 11c4e25: 52                           	push	edx
 11c4e26: e8 fc 0c 21 00               	call	0x13d5b27 <.text+0x211067>
 11c4e2b: 83 c4 04                     	add	esp, 0x4
 11c4e2e: 8b 4d 18                     	mov	ecx, dword ptr [ebp + 0x18]
 11c4e31: 33 c0                        	xor	eax, eax
 11c4e33: 51                           	push	ecx
 11c4e34: c7 45 30 07 00 00 00         	mov	dword ptr [ebp + 0x30], 0x7
 11c4e3b: c7 45 2c 00 00 00 00         	mov	dword ptr [ebp + 0x2c], 0x0
 11c4e42: 66 89 45 1c                  	mov	word ptr [ebp + 0x1c], ax
 11c4e46: e8 dc 0c 21 00               	call	0x13d5b27 <.text+0x211067>
 11c4e4b: b8 01 00 00 00               	mov	eax, 0x1
 11c4e50: 83 c4 04                     	add	esp, 0x4
 11c4e53: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c4e56: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11c4e5d: 59                           	pop	ecx
 11c4e5e: 5f                           	pop	edi
 11c4e5f: 5e                           	pop	esi
 11c4e60: 5b                           	pop	ebx
 11c4e61: 8b e5                        	mov	esp, ebp
 11c4e63: 5d                           	pop	ebp
 11c4e64: c2 44 00                     	ret	0x44
 11c4e67: cc                           	int3
 11c4e68: cc                           	int3
 11c4e69: cc                           	int3
 11c4e6a: cc                           	int3
 11c4e6b: cc                           	int3
 11c4e6c: cc                           	int3
 11c4e6d: cc                           	int3
 11c4e6e: cc                           	int3
 11c4e6f: cc                           	int3
 11c4e70: 55                           	push	ebp
 11c4e71: 8b ec                        	mov	ebp, esp
 11c4e73: 6a ff                        	push	-0x1
 11c4e75: 68 78 80 4c 01               	push	0x14c8078
 11c4e7a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c4e80: 50                           	push	eax
 11c4e81: 53                           	push	ebx
 11c4e82: 56                           	push	esi
 11c4e83: 57                           	push	edi
 11c4e84: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c4e89: 33 c5                        	xor	eax, ebp
 11c4e8b: 50                           	push	eax
 11c4e8c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c4e8f: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c4e95: 8b 55 30                     	mov	edx, dword ptr [ebp + 0x30]
 11c4e98: 8b 5d 34                     	mov	ebx, dword ptr [ebp + 0x34]
 11c4e9b: 8b f1                        	mov	esi, ecx
 11c4e9d: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11c4ea1: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11c4ea8: 74 39                        	je	0x11c4ee3 <.text+0x423>
 11c4eaa: 83 7d 24 08                  	cmp	dword ptr [ebp + 0x24], 0x8
 11c4eae: 72 0c                        	jb	0x11c4ebc <.text+0x3fc>
 11c4eb0: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11c4eb3: 50                           	push	eax
 11c4eb4: e8 6e 0c 21 00               	call	0x13d5b27 <.text+0x211067>
 11c4eb9: 83 c4 04                     	add	esp, 0x4
 11c4ebc: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11c4ebf: 33                           	<unknown>
