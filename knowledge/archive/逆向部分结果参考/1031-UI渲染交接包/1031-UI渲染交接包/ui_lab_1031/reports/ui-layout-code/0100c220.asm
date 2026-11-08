
<stdin>:	file format elf32-i386

Disassembly of section .text:

0100c220 <.text>:
 100c220: c0 0f 84                     	ror	byte ptr [edi], 0x84
 100c223: 17                           	pop	ss
 100c224: 01 00                        	add	dword ptr [eax], eax
 100c226: 00 8b bf e8 02 00            	add	byte ptr [ebx + 0x2e8bf], cl
 100c22c: 00 89 7d fc 85 ff            	add	byte ptr [ecx - 0x7a0383], cl
 100c232: 0f 84 06 01 00 00            	je	0x100c33e <.text+0x11e>
 100c238: 32 db                        	xor	bl, bl
 100c23a: 83 ff 01                     	cmp	edi, 0x1
 100c23d: 75 52                        	jne	0x100c291 <.text+0x71>
 100c23f: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 100c245: 68 ee 00 00 00               	push	0xee
 100c24a: e8 51 92 e6 ff               	call	0xe754a0
 100c24f: 8b f8                        	mov	edi, eax
 100c251: 85 ff                        	test	edi, edi
 100c253: 74 3c                        	je	0x100c291 <.text+0x71>
 100c255: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 100c25b: 68 ee 00 00 00               	push	0xee
 100c260: e8 eb 57 e6 ff               	call	0xe71a50
 100c265: 84 c0                        	test	al, al
 100c267: 74 28                        	je	0x100c291 <.text+0x71>
 100c269: 6a 00                        	push	0x0
 100c26b: 68 60 11 9e 01               	push	0x19e1160
 100c270: 68 10 94 9d 01               	push	0x19d9410
 100c275: 6a 00                        	push	0x0
 100c277: 57                           	push	edi
 100c278: e8 62 b4 3c 00               	call	0x13d76df <.text+0x3cb4bf>
 100c27d: 83 c4 14                     	add	esp, 0x14
 100c280: 85 c0                        	test	eax, eax
 100c282: 74 0d                        	je	0x100c291 <.text+0x71>
 100c284: 8b c8                        	mov	ecx, eax
 100c286: e8 a5 dc 6a ff               	call	0x6b9f30
 100c28b: 84 c0                        	test	al, al
 100c28d: 74 02                        	je	0x100c291 <.text+0x71>
 100c28f: b3 01                        	mov	bl, 0x1
 100c291: 8b 8e f8 00 00 00            	mov	ecx, dword ptr [esi + 0xf8]
 100c297: 6a 00                        	push	0x0
 100c299: 68 5c e6 a3 01               	push	0x1a3e65c
 100c29e: 68 78 99 9d 01               	push	0x19d9978
 100c2a3: 6a 00                        	push	0x0
 100c2a5: 51                           	push	ecx
 100c2a6: e8 34 b4 3c 00               	call	0x13d76df <.text+0x3cb4bf>
 100c2ab: 83 c4 14                     	add	esp, 0x14
 100c2ae: 84 db                        	test	bl, bl
 100c2b0: 0f 85 88 00 00 00            	jne	0x100c33e <.text+0x11e>
 100c2b6: 85 c0                        	test	eax, eax
 100c2b8: 0f 84 80 00 00 00            	je	0x100c33e <.text+0x11e>
 100c2be: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
 100c2c1: 52                           	push	edx
 100c2c2: 8b c8                        	mov	ecx, eax
 100c2c4: e8 77 69 ff ff               	call	0x1002c40
 100c2c9: 84 c0                        	test	al, al
 100c2cb: 74 71                        	je	0x100c33e <.text+0x11e>
 100c2cd: e8 3e a1 6f ff               	call	0x706410
 100c2d2: 8b c8                        	mov	ecx, eax
 100c2d4: e8 47 e5 74 ff               	call	0x75a820
 100c2d9: 84 c0                        	test	al, al
 100c2db: 75 61                        	jne	0x100c33e <.text+0x11e>
 100c2dd: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 100c2e0: e8 7b 3c 42 ff               	call	0x42ff60
 100c2e5: 8b be a0 01 00 00            	mov	edi, dword ptr [esi + 0x1a0]
 100c2eb: 2b be 9c 01 00 00            	sub	edi, dword ptr [esi + 0x19c]
 100c2f1: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 100c2f4: 8d 9e 98 01 00 00            	lea	ebx, [esi + 0x198]
 100c2fa: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 100c2fd: c1 ff 02                     	sar	edi, 0x2
 100c300: e8 fb 1f 1b 00               	call	0x11be300 <.text+0x1b20e0>
 100c305: 8b 8e f8 00 00 00            	mov	ecx, dword ptr [esi + 0xf8]
 100c30b: 47                           	inc	edi
 100c30c: 6b ff 15                     	imul	edi, edi, 0x15
 100c30f: 03 c7                        	add	eax, edi
 100c311: 6a 01                        	push	0x1
 100c313: 50                           	push	eax
 100c314: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
 100c317: 50                           	push	eax
 100c318: e8 b3 27 1b 00               	call	0x11bead0 <.text+0x1b28b0>
 100c31d: 8b 8e f8 00 00 00            	mov	ecx, dword ptr [esi + 0xf8]
 100c323: 8b 11                        	mov	edx, dword ptr [ecx]
 100c325: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 100c328: 6a 01                        	push	0x1
 100c32a: ff d0                        	call	eax
 100c32c: 8d 4d fc                     	lea	ecx, [ebp - 0x4]
 100c32f: 51                           	push	ecx
 100c330: 8b cb                        	mov	ecx, ebx
 100c332: c7 45 fc 23 00 00 00         	mov	dword ptr [ebp - 0x4], 0x23
 100c339: e8 32 74 48 ff               	call	0x493770
 100c33e: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 100c341: 8d 50 10                     	lea	edx, [eax + 0x10]
 100c344: 85 d2                        	test	edx, edx
 100c346: 0f 84 19 01 00 00            	je	0x100c465 <.text+0x245>
 100c34c: 8b 80 e8 02 00 00            	mov	eax, dword ptr [eax + 0x2e8]
 100c352: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 100c355: 85 c0                        	test	eax, eax
 100c357: 0f 84 08 01 00 00            	je	0x100c465 <.text+0x245>
 100c35d: 32 db                        	xor	bl, bl
 100c35f: 83 f8 01                     	cmp	eax, 0x1
 100c362: 75 52                        	jne	0x100c3b6 <.text+0x196>
 100c364: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 100c36a: 68 ee 00 00 00               	push	0xee
 100c36f: e8 2c 91 e6 ff               	call	0xe754a0
 100c374: 8b f8                        	mov	edi, eax
 100c376: 85 ff                        	test	edi, edi
 100c378: 74 3c                        	je	0x100c3b6 <.text+0x196>
 100c37a: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 100c380: 68 ee 00 00 00               	push	0xee
 100c385: e8 c6 56 e6 ff               	call	0xe71a50
 100c38a: 84 c0                        	test	al, al
 100c38c: 74 28                        	je	0x100c3b6 <.text+0x196>
 100c38e: 6a 00                        	push	0x0
 100c390: 68 60 11 9e 01               	push	0x19e1160
 100c395: 68 10 94 9d 01               	push	0x19d9410
 100c39a: 6a 00                        	push	0x0
 100c39c: 57                           	push	edi
 100c39d: e8 3d b3 3c 00               	call	0x13d76df <.text+0x3cb4bf>
 100c3a2: 83 c4 14                     	add	esp, 0x14
 100c3a5: 85 c0                        	test	eax, eax
 100c3a7: 74 0d                        	je	0x100c3b6 <.text+0x196>
 100c3a9: 8b c8                        	mov	ecx, eax
 100c3ab: e8 80 db 6a ff               	call	0x6b9f30
 100c3b0: 84 c0                        	test	al, al
 100c3b2: 74 02                        	je	0x100c3b6 <.text+0x196>
 100c3b4: b3 01                        	mov	bl, 0x1
 100c3b6: 8b 86 fc 00 00 00            	mov	eax, dword ptr [esi + 0xfc]
 100c3bc: 6a 00                        	push	0x0
 100c3be: 68 5c e6 a3 01               	push	0x1a3e65c
 100c3c3: 68 78 99 9d 01               	push	0x19d9978
 100c3c8: 6a 00                        	push	0x0
 100c3ca: 50                           	push	eax
 100c3cb: e8 0f b3 3c 00               	call	0x13d76df <.text+0x3cb4bf>
 100c3d0: 83 c4 14                     	add	esp, 0x14
 100c3d3: 84 db                        	test	bl, bl
 100c3d5: 0f 85 8a 00 00 00            	jne	0x100c465 <.text+0x245>
 100c3db: 85 c0                        	test	eax, eax
 100c3dd: 0f 84 82 00 00 00            	je	0x100c465 <.text+0x245>
 100c3e3: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 100c3e6: 51                           	push	ecx
 100c3e7: 8b c8                        	mov	ecx, eax
 100c3e9: e8 52 68 ff ff               	call	0x1002c40
 100c3ee: 84 c0                        	test	al, al
 100c3f0: 74 73                        	je	0x100c465 <.text+0x245>
 100c3f2: e8 19 a0 6f ff               	call	0x706410
 100c3f7: 8b c8                        	mov	ecx, eax
 100c3f9: e8 22 e4 74 ff               	call	0x75a820
 100c3fe: 84 c0                        	test	al, al
 100c400: 75 63                        	jne	0x100c465 <.text+0x245>
 100c402: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 100c405: e8 56 3b 42 ff               	call	0x42ff60
 100c40a: 8b be a0 01 00 00            	mov	edi, dword ptr [esi + 0x1a0]
 100c410: 2b be 9c 01 00 00            	sub	edi, dword ptr [esi + 0x19c]
 100c416: 8b 4e 68                     	mov	ecx, dword ptr [esi + 0x68]
 100c419: 8d 9e 98 01 00 00            	lea	ebx, [esi + 0x198]
 100c41f: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 100c422: c1 ff 02                     	sar	edi, 0x2
 100c425: e8 d6 1e 1b 00               	call	0x11be300 <.text+0x1b20e0>
 100c42a: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 100c42d: 8b 8e fc 00 00 00            	mov	ecx, dword ptr [esi + 0xfc]
 100c433: 47                           	inc	edi
 100c434: 6b ff 15                     	imul	edi, edi, 0x15
 100c437: 6a 01                        	push	0x1
 100c439: 03 c7                        	add	eax, edi
 100c43b: 50                           	push	eax
 100c43c: 52                           	push	edx
 100c43d: e8 8e 26 1b 00               	call	0x11bead0 <.text+0x1b28b0>
 100c442: 8b b6 fc 00 00 00            	mov	esi, dword ptr [esi + 0xfc]
 100c448: 8b 06                        	mov	eax, dword ptr [esi]
 100c44a: 8b 50 10                     	mov	edx, dword ptr [eax + 0x10]
 100c44d: 6a 01                        	push	0x1
 100c44f: 8b ce                        	mov	ecx, esi
 100c451: ff d2                        	call	edx
 100c453: 8d 45 08                     	lea	eax, [ebp + 0x8]
 100c456: 50                           	push	eax
 100c457: 8b cb                        	mov	ecx, ebx
 100c459: c7 45 08 24 00 00 00         	mov	dword ptr [ebp + 0x8], 0x24
 100c460: e8 0b 73 48 ff               	call	0x493770
 100c465: 5b                           	pop	ebx
 100c466: 5f                           	pop	edi
 100c467: 5e                           	pop	esi
 100c468: 8b e5                        	mov	esp, ebp
 100c46a: 5d                           	pop	ebp
 100c46b: c2 04 00                     	ret	0x4
 100c46e: cc                           	int3
 100c46f: cc                           	int3
 100c470: 55                           	push	ebp
 100c471: 8b ec                        	mov	ebp, esp
 100c473: 56                           	push	esi
 100c474: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 100c477: 57                           	push	edi
 100c478: 8b f9                        	mov	edi, ecx
 100c47a: 85 f6                        	test	esi, esi
 100c47c: 0f 84 88 00 00 00            	je	0x100c50a <.text+0x2ea>
 100c482: e8 89 9f 6f ff               	call	0x706410
 100c487: 8b c8                        	mov	ecx, eax
 100c489: e8 12 00 75 ff               	call	0x75c4a0
 100c48e: 84 c0                        	test	al, al
 100c490: 74 78                        	je	0x100c50a <.text+0x2ea>
 100c492: 8b ce                        	mov	ecx, esi
 100c494: e8 97 68 91 ff               	call	0x922d30
 100c499: 84 c0                        	test	al, al
 100c49b: 74 6d                        	je	0x100c50a <.text+0x2ea>
 100c49d: 53                           	push	ebx
 100c49e: e8                           	<unknown>
 100c49f: 6d                           	insd	dword ptr es:[edi], dx
