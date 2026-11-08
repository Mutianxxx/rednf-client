
<stdin>:	file format elf32-i386

Disassembly of section .text:

010038a5 <.text>:
 10038a5: 83 be f4 03 00 00 08         	cmp	dword ptr [esi + 0x3f4], 0x8
 10038ac: 72 08                        	jb	0x10038b6 <.text+0x11>
 10038ae: 8b b6 e0 03 00 00            	mov	esi, dword ptr [esi + 0x3e0]
 10038b4: eb 06                        	jmp	0x10038bc <.text+0x17>
 10038b6: 81 c6 e0 03 00 00            	add	esi, 0x3e0
 10038bc: 56                           	push	esi
 10038bd: 68 78 21 56 01               	push	0x1562178
 10038c2: e8 29 c6 19 00               	call	0x119fef0 <.text+0x19c64b>
 10038c7: 83 c4 04                     	add	esp, 0x4
 10038ca: 50                           	push	eax
 10038cb: e8 50 fd 21 00               	call	0x1223620 <.text+0x21fd7b>
 10038d0: 83 c4 08                     	add	esp, 0x8
 10038d3: 84 c0                        	test	al, al
 10038d5: 75 07                        	jne	0x10038de <.text+0x39>
 10038d7: 32 db                        	xor	bl, bl
 10038d9: e9 9d 03 00 00               	jmp	0x1003c7b <.text+0x3d6>
 10038de: 6a 08                        	push	0x8
 10038e0: 89 5d b0                     	mov	dword ptr [ebp - 0x50], ebx
 10038e3: e8 32 32 3d 00               	call	0x13d6b1a <.text+0x3d3275>
 10038e8: 83 c4 04                     	add	esp, 0x4
 10038eb: 3b c3                        	cmp	eax, ebx
 10038ed: 0f 84 39 04 00 00            	je	0x1003d2c <.text+0x487>
 10038f3: 89 45 b0                     	mov	dword ptr [ebp - 0x50], eax
 10038f6: 33 c9                        	xor	ecx, ecx
 10038f8: 89 08                        	mov	dword ptr [eax], ecx
 10038fa: 33 d2                        	xor	edx, edx
 10038fc: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 10038ff: 8b 55 b0                     	mov	edx, dword ptr [ebp - 0x50]
 1003902: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1003905: 89 0a                        	mov	dword ptr [edx], ecx
 1003907: bf 07 00 00 00               	mov	edi, 0x7
 100390c: 33 c0                        	xor	eax, eax
 100390e: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
 1003911: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
 1003914: 66 89 45 b4                  	mov	word ptr [ebp - 0x4c], ax
 1003918: 6a 08                        	push	0x8
 100391a: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 100391e: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 1003921: e8 f4 31 3d 00               	call	0x13d6b1a <.text+0x3d3275>
 1003926: 83 c4 04                     	add	esp, 0x4
 1003929: 3b c3                        	cmp	eax, ebx
 100392b: 0f 84 c8 03 00 00            	je	0x1003cf9 <.text+0x454>
 1003931: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
 1003934: 33 c9                        	xor	ecx, ecx
 1003936: 89 08                        	mov	dword ptr [eax], ecx
 1003938: 33 d2                        	xor	edx, edx
 100393a: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 100393d: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 1003940: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1003943: 89 0a                        	mov	dword ptr [edx], ecx
 1003945: 33 c0                        	xor	eax, eax
 1003947: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 100394a: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 100394d: 66 89 45 d4                  	mov	word ptr [ebp - 0x2c], ax
 1003951: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1003954: 6a 01                        	push	0x1
 1003956: 51                           	push	ecx
 1003957: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 100395b: e8 b0 18 22 00               	call	0x1225210 <.text+0x22196b>
 1003960: 83 c4 08                     	add	esp, 0x8
 1003963: 84 c0                        	test	al, al
 1003965: 0f 84 b4 02 00 00            	je	0x1003c1f <.text+0x37a>
 100396b: eb 03                        	jmp	0x1003970 <.text+0xcb>
 100396d: 8d 49 00                     	lea	ecx, [ecx]
 1003970: 68 ec b0 82 01               	push	0x182b0ec
 1003975: e8 76 c5 19 00               	call	0x119fef0 <.text+0x19c64b>
 100397a: 8b c8                        	mov	ecx, eax
 100397c: 83 c4 04                     	add	esp, 0x4
 100397f: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003982: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003985: 83 c1 02                     	add	ecx, 0x2
 1003988: 66 3b d3                     	cmp	dx, bx
 100398b: 75 f5                        	jne	0x1003982 <.text+0xdd>
 100398d: 8b 55 c4                     	mov	edx, dword ptr [ebp - 0x3c]
 1003990: 2b ce                        	sub	ecx, esi
 1003992: d1 f9                        	sar	ecx
 1003994: 51                           	push	ecx
 1003995: 50                           	push	eax
 1003996: 52                           	push	edx
 1003997: 53                           	push	ebx
 1003998: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 100399b: e8 90 e2 3f ff               	call	0x401c30
 10039a0: 85 c0                        	test	eax, eax
 10039a2: 0f 85 61 02 00 00            	jne	0x1003c09 <.text+0x364>
 10039a8: 6a 08                        	push	0x8
 10039aa: 89 5d 90                     	mov	dword ptr [ebp - 0x70], ebx
 10039ad: e8 68 31 3d 00               	call	0x13d6b1a <.text+0x3d3275>
 10039b2: 83 c4 04                     	add	esp, 0x4
 10039b5: 3b c3                        	cmp	eax, ebx
 10039b7: 0f 84 09 03 00 00            	je	0x1003cc6 <.text+0x421>
 10039bd: 89 45 90                     	mov	dword ptr [ebp - 0x70], eax
 10039c0: 33 c9                        	xor	ecx, ecx
 10039c2: 89 08                        	mov	dword ptr [eax], ecx
 10039c4: 33 d2                        	xor	edx, edx
 10039c6: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 10039c9: 8b 4d 90                     	mov	ecx, dword ptr [ebp - 0x70]
 10039cc: 8d 45 90                     	lea	eax, [ebp - 0x70]
 10039cf: 89 01                        	mov	dword ptr [ecx], eax
 10039d1: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
 10039d4: 89 5d a4                     	mov	dword ptr [ebp - 0x5c], ebx
 10039d7: 66 89 55 94                  	mov	word ptr [ebp - 0x6c], dx
 10039db: 83 c8 ff                     	or	eax, -0x1
 10039de: 68 78 21 56 01               	push	0x1562178
 10039e3: c6 45 fc 04                  	mov	byte ptr [ebp - 0x4], 0x4
 10039e7: 89 9d 78 ff ff ff            	mov	dword ptr [ebp - 0x88], ebx
 10039ed: 89 9d 7c ff ff ff            	mov	dword ptr [ebp - 0x84], ebx
 10039f3: 89 5d 80                     	mov	dword ptr [ebp - 0x80], ebx
 10039f6: 89 5d 84                     	mov	dword ptr [ebp - 0x7c], ebx
 10039f9: 89 45 88                     	mov	dword ptr [ebp - 0x78], eax
 10039fc: 89 45 8c                     	mov	dword ptr [ebp - 0x74], eax
 10039ff: e8 ec c4 19 00               	call	0x119fef0 <.text+0x19c64b>
 1003a04: 8b c8                        	mov	ecx, eax
 1003a06: 83 c4 04                     	add	esp, 0x4
 1003a09: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003a0c: 8d 64 24 00                  	lea	esp, [esp]
 1003a10: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003a13: 83 c1 02                     	add	ecx, 0x2
 1003a16: 66 3b d3                     	cmp	dx, bx
 1003a19: 75 f5                        	jne	0x1003a10 <.text+0x16b>
 1003a1b: 2b ce                        	sub	ecx, esi
 1003a1d: d1 f9                        	sar	ecx
 1003a1f: 51                           	push	ecx
 1003a20: 50                           	push	eax
 1003a21: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
 1003a24: e8 07 c6 40 ff               	call	0x410030
 1003a29: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 1003a2c: 50                           	push	eax
 1003a2d: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
 1003a31: e8 1a 17 22 00               	call	0x1225150 <.text+0x2218ab>
 1003a36: 83 c4 04                     	add	esp, 0x4
 1003a39: 84 c0                        	test	al, al
 1003a3b: 0f 84 88 01 00 00            	je	0x1003bc9 <.text+0x324>
 1003a41: 68 cc b0 82 01               	push	0x182b0cc
 1003a46: e8 a5 c4 19 00               	call	0x119fef0 <.text+0x19c64b>
 1003a4b: 8b c8                        	mov	ecx, eax
 1003a4d: 83 c4 04                     	add	esp, 0x4
 1003a50: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003a53: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003a56: 83 c1 02                     	add	ecx, 0x2
 1003a59: 66 3b d3                     	cmp	dx, bx
 1003a5c: 75 f5                        	jne	0x1003a53 <.text+0x1ae>
 1003a5e: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
 1003a61: 2b ce                        	sub	ecx, esi
 1003a63: d1 f9                        	sar	ecx
 1003a65: 8b f7                        	mov	esi, edi
 1003a67: 3b f9                        	cmp	edi, ecx
 1003a69: 72 02                        	jb	0x1003a6d <.text+0x1c8>
 1003a6b: 8b f1                        	mov	esi, ecx
 1003a6d: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 1003a71: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
 1003a74: 73 03                        	jae	0x1003a79 <.text+0x1d4>
 1003a76: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
 1003a79: 3b f3                        	cmp	esi, ebx
 1003a7b: 76 24                        	jbe	0x1003aa1 <.text+0x1fc>
 1003a7d: 8d 49 00                     	lea	ecx, [ecx]
 1003a80: 66 8b 1a                     	mov	bx, word ptr [edx]
 1003a83: 66 3b 18                     	cmp	bx, word ptr [eax]
 1003a86: 75 0d                        	jne	0x1003a95 <.text+0x1f0>
 1003a88: 83 c2 02                     	add	edx, 0x2
 1003a8b: 83 c0 02                     	add	eax, 0x2
 1003a8e: 4e                           	dec	esi
 1003a8f: 75 ef                        	jne	0x1003a80 <.text+0x1db>
 1003a91: 33 db                        	xor	ebx, ebx
 1003a93: eb 0c                        	jmp	0x1003aa1 <.text+0x1fc>
 1003a95: 1b c0                        	sbb	eax, eax
 1003a97: 83 e0 fe                     	and	eax, -0x2
 1003a9a: 40                           	inc	eax
 1003a9b: 33 db                        	xor	ebx, ebx
 1003a9d: 3b c3                        	cmp	eax, ebx
 1003a9f: 75 12                        	jne	0x1003ab3 <.text+0x20e>
 1003aa1: 3b f9                        	cmp	edi, ecx
 1003aa3: 73 05                        	jae	0x1003aaa <.text+0x205>
 1003aa5: 83 c8 ff                     	or	eax, -0x1
 1003aa8: eb 07                        	jmp	0x1003ab1 <.text+0x20c>
 1003aaa: 33 c0                        	xor	eax, eax
 1003aac: 3b f9                        	cmp	edi, ecx
 1003aae: 0f 95 c0                     	setne	al
 1003ab1: 3b c3                        	cmp	eax, ebx
 1003ab3: 0f 94 c0                     	sete	al
 1003ab6: 84 c0                        	test	al, al
 1003ab8: 74 11                        	je	0x1003acb <.text+0x226>
 1003aba: 53                           	push	ebx
 1003abb: e8 a0 fb 21 00               	call	0x1223660 <.text+0x21fdbb>
 1003ac0: 89 85 78 ff ff ff            	mov	dword ptr [ebp - 0x88], eax
 1003ac6: e9 e2 00 00 00               	jmp	0x1003bad <.text+0x308>
 1003acb: 68 30 1c 57 01               	push	0x1571c30
 1003ad0: e8 1b c4 19 00               	call	0x119fef0 <.text+0x19c64b>
 1003ad5: 8b c8                        	mov	ecx, eax
 1003ad7: 83 c4 04                     	add	esp, 0x4
 1003ada: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003add: 8d 49 00                     	lea	ecx, [ecx]
 1003ae0: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003ae3: 83 c1 02                     	add	ecx, 0x2
 1003ae6: 66 3b d3                     	cmp	dx, bx
 1003ae9: 75 f5                        	jne	0x1003ae0 <.text+0x23b>
 1003aeb: 2b ce                        	sub	ecx, esi
 1003aed: d1 f9                        	sar	ecx
 1003aef: 51                           	push	ecx
 1003af0: 50                           	push	eax
 1003af1: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 1003af4: 50                           	push	eax
 1003af5: 53                           	push	ebx
 1003af6: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1003af9: e8 32 e1 3f ff               	call	0x401c30
 1003afe: 85 c0                        	test	eax, eax
 1003b00: 75 0e                        	jne	0x1003b10 <.text+0x26b>
 1003b02: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
 1003b05: 51                           	push	ecx
 1003b06: e8 45 16 22 00               	call	0x1225150 <.text+0x2218ab>
 1003b0b: e9 9d 00 00 00               	jmp	0x1003bad <.text+0x308>
 1003b10: 68 a4 b0 82 01               	push	0x182b0a4
 1003b15: e8 d6 c3 19 00               	call	0x119fef0 <.text+0x19c64b>
 1003b1a: 8b c8                        	mov	ecx, eax
 1003b1c: 83 c4 04                     	add	esp, 0x4
 1003b1f: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003b22: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003b25: 83 c1 02                     	add	ecx, 0x2
 1003b28: 66 3b d3                     	cmp	dx, bx
 1003b2b: 75 f5                        	jne	0x1003b22 <.text+0x27d>
 1003b2d: 8b 55 e4                     	mov	edx, dword ptr [ebp - 0x1c]
 1003b30: 2b ce                        	sub	ecx, esi
 1003b32: d1 f9                        	sar	ecx
 1003b34: 51                           	push	ecx
 1003b35: 50                           	push	eax
 1003b36: 52                           	push	edx
 1003b37: 53                           	push	ebx
 1003b38: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1003b3b: e8 f0 e0 3f ff               	call	0x401c30
 1003b40: 85 c0                        	test	eax, eax
 1003b42: 75 2c                        	jne	0x1003b70 <.text+0x2cb>
 1003b44: 53                           	push	ebx
 1003b45: e8 16 fb 21 00               	call	0x1223660 <.text+0x21fdbb>
 1003b4a: 53                           	push	ebx
 1003b4b: 89 85 7c ff ff ff            	mov	dword ptr [ebp - 0x84], eax
 1003b51: e8 0a fb 21 00               	call	0x1223660 <.text+0x21fdbb>
 1003b56: 53                           	push	ebx
 1003b57: 89 45 80                     	mov	dword ptr [ebp - 0x80], eax
 1003b5a: e8 01 fb 21 00               	call	0x1223660 <.text+0x21fdbb>
 1003b5f: 53                           	push	ebx
 1003b60: 89 45 84                     	mov	dword ptr [ebp - 0x7c], eax
 1003b63: e8 f8 fa 21 00               	call	0x1223660 <.text+0x21fdbb>
 1003b68: 83 c4 10                     	add	esp, 0x10
 1003b6b: 89 45 88                     	mov	dword ptr [ebp - 0x78], eax
 1003b6e: eb 40                        	jmp	0x1003bb0 <.text+0x30b>
 1003b70: 68 78 b0 82 01               	push	0x182b078
 1003b75: e8 76 c3 19 00               	call	0x119fef0 <.text+0x19c64b>
 1003b7a: 8b c8                        	mov	ecx, eax
 1003b7c: 83 c4 04                     	add	esp, 0x4
 1003b7f: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003b82: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003b85: 83 c1 02                     	add	ecx, 0x2
 1003b88: 66 3b d3                     	cmp	dx, bx
 1003b8b: 75 f5                        	jne	0x1003b82 <.text+0x2dd>
 1003b8d: 2b ce                        	sub	ecx, esi
 1003b8f: d1 f9                        	sar	ecx
 1003b91: 51                           	push	ecx
 1003b92: 50                           	push	eax
 1003b93: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 1003b96: 50                           	push	eax
 1003b97: 53                           	push	ebx
 1003b98: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1003b9b: e8 90 e0 3f ff               	call	0x401c30
 1003ba0: 85 c0                        	test	eax, eax
 1003ba2: 75 0c                        	jne	0x1003bb0 <.text+0x30b>
 1003ba4: 53                           	push	ebx
 1003ba5: e8 b6 fa 21 00               	call	0x1223660 <.text+0x21fdbb>
 1003baa: 89 45 8c                     	mov	dword ptr [ebp - 0x74], eax
 1003bad: 83 c4 04                     	add	esp, 0x4
 1003bb0: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1003bb3: 51                           	push	ecx
 1003bb4: e8 97 15 22 00               	call	0x1225150 <.text+0x2218ab>
 1003bb9: 83 c4 04                     	add	esp, 0x4
 1003bbc: 84 c0                        	test	al, al
 1003bbe: 0f 85 7d fe ff ff            	jne	0x1003a41 <.text+0x19c>
 1003bc4: bf 07 00 00 00               	mov	edi, 0x7
 1003bc9: 8b 8d 1c ff ff ff            	mov	ecx, dword ptr [ebp - 0xe4]
 1003bcf: 8d 95 78 ff ff ff            	lea	edx, [ebp - 0x88]
 1003bd5: 52                           	push	edx
 1003bd6: e8 15 f6 ff ff               	call	0x10031f0
 1003bdb: 83 7d a8 08                  	cmp	dword ptr [ebp - 0x58], 0x8
 1003bdf: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 1003be3: 72 0c                        	jb	0x1003bf1 <.text+0x34c>
 1003be5: 8b 45 94                     	mov	eax, dword ptr [ebp - 0x6c]
 1003be8: 50                           	push	eax
 1003be9: e8 39 1f 3d 00               	call	0x13d5b27 <.text+0x3d2282>
 1003bee: 83 c4 04                     	add	esp, 0x4
 1003bf1: 8b 55 90                     	mov	edx, dword ptr [ebp - 0x70]
 1003bf4: 33 c9                        	xor	ecx, ecx
 1003bf6: 52                           	push	edx
 1003bf7: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
 1003bfa: 89 5d a4                     	mov	dword ptr [ebp - 0x5c], ebx
 1003bfd: 66 89 4d 94                  	mov	word ptr [ebp - 0x6c], cx
 1003c01: e8 21 1f 3d 00               	call	0x13d5b27 <.text+0x3d2282>
 1003c06: 83 c4 04                     	add	esp, 0x4
 1003c09: 8d 45 b0                     	lea	eax, [ebp - 0x50]
 1003c0c: 6a 01                        	push	0x1
 1003c0e: 50                           	push	eax
 1003c0f: e8 fc 15 22 00               	call	0x1225210 <.text+0x22196b>
 1003c14: 83 c4 08                     	add	esp, 0x8
 1003c17: 84 c0                        	test	al, al
 1003c19: 0f 85 51 fd ff ff            	jne	0x1003970 <.text+0xcb>
 1003c1f: be 08 00 00 00               	mov	esi, 0x8
 1003c24: 39 75 e8                     	cmp	dword ptr [ebp - 0x18], esi
 1003c27: 72 0c                        	jb	0x1003c35 <.text+0x390>
 1003c29: 8b 4d d4                     	mov	ecx, dword ptr [ebp - 0x2c]
 1003c2c: 51                           	push	ecx
 1003c2d: e8 f5 1e 3d 00               	call	0x13d5b27 <.text+0x3d2282>
 1003c32: 83 c4 04                     	add	esp, 0x4
 1003c35: 8b 45 d0                     	mov	eax, dword ptr [ebp - 0x30]
 1003c38: 33 d2                        	xor	edx, edx
 1003c3a: 50                           	push	eax
 1003c3b: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 1003c3e: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 1003c41: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
 1003c45: e8 dd 1e 3d 00               	call	0x13d5b27 <.text+0x3d2282>
 1003c4a: 83 c4 04                     	add	esp, 0x4
 1003c4d: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 1003c50: 39 75 c8                     	cmp	dword ptr [ebp - 0x38], esi
 1003c53: 72 0c                        	jb	0x1003c61 <.text+0x3bc>
 1003c55: 8b 4d b4                     	mov	ecx, dword ptr [ebp - 0x4c]
 1003c58: 51                           	push	ecx
 1003c59: e8 c9 1e 3d 00               	call	0x13d5b27 <.text+0x3d2282>
 1003c5e: 83 c4 04                     	add	esp, 0x4
 1003c61: 8b 45 b0                     	mov	eax, dword ptr [ebp - 0x50]
 1003c64: 33 d2                        	xor	edx, edx
 1003c66: 50                           	push	eax
 1003c67: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
 1003c6a: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
 1003c6d: 66 89 55 b4                  	mov	word ptr [ebp - 0x4c], dx
 1003c71: e8 b1 1e 3d 00               	call	0x13d5b27 <.text+0x3d2282>
 1003c76: 83 c4 04                     	add	esp, 0x4
 1003c79: b3 01                        	mov	bl, 0x1
 1003c7b: 83 bd 70 ff ff ff 08         	cmp	dword ptr [ebp - 0x90], 0x8
 1003c82: 72 0f                        	jb	0x1003c93 <.text+0x3ee>
 1003c84: 8b 8d 5c ff ff ff            	mov	ecx, dword ptr [ebp - 0xa4]
 1003c8a: 51                           	push	ecx
 1003c8b: e8 97 1e 3d 00               	call	0x13d5b27 <.text+0x3d2282>
 1003c90: 83 c4 04                     	add	esp, 0x4
 1003c93: 8b 85 58 ff ff ff            	mov	eax, dword ptr [ebp - 0xa8]
 1003c99: 33 d2                        	xor	edx, edx
 1003c9b: 50                           	push	eax
 1003c9c: c7 85 70 ff ff ff            	<unknown>
 1003ca2: 07                           	pop	es
 1003ca3: 00 00                        	add	byte ptr [eax], al
