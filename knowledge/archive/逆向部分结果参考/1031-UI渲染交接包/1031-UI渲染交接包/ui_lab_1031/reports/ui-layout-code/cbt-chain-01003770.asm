
<stdin>:	file format elf32-i386

Disassembly of section .text:

01003770 <.text>:
 1003770: 55                           	push	ebp
 1003771: 8b ec                        	mov	ebp, esp
 1003773: 6a ff                        	push	-0x1
 1003775: 68 59 2d 4b 01               	push	0x14b2d59
 100377a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1003780: 50                           	push	eax
 1003781: 81 ec d8 00 00 00            	sub	esp, 0xd8
 1003787: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 100378c: 33 c5                        	xor	eax, ebp
 100378e: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 1003791: 53                           	push	ebx
 1003792: 56                           	push	esi
 1003793: 57                           	push	edi
 1003794: 50                           	push	eax
 1003795: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1003798: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 100379e: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 10037a1: 33 db                        	xor	ebx, ebx
 10037a3: 6a 08                        	push	0x8
 10037a5: 8b f1                        	mov	esi, ecx
 10037a7: 89 9d 58 ff ff ff            	mov	dword ptr [ebp - 0xa8], ebx
 10037ad: e8 68 33 3d 00               	call	0x13d6b1a <.text+0x3d33aa>
 10037b2: 83 c4 04                     	add	esp, 0x4
 10037b5: 3b c3                        	cmp	eax, ebx
 10037b7: 0f 84 a2 05 00 00            	je	0x1003d5f <.text+0x5ef>
 10037bd: 89 85 58 ff ff ff            	mov	dword ptr [ebp - 0xa8], eax
 10037c3: 33 c9                        	xor	ecx, ecx
 10037c5: 89 08                        	mov	dword ptr [eax], ecx
 10037c7: 33 d2                        	xor	edx, edx
 10037c9: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 10037cc: 8b 8d 58 ff ff ff            	mov	ecx, dword ptr [ebp - 0xa8]
 10037d2: 8d 85 58 ff ff ff            	lea	eax, [ebp - 0xa8]
 10037d8: 89 01                        	mov	dword ptr [ecx], eax
 10037da: c7 85 70 ff ff ff 07 00 00 00	mov	dword ptr [ebp - 0x90], 0x7
 10037e4: 89 9d 6c ff ff ff            	mov	dword ptr [ebp - 0x94], ebx
 10037ea: 66 89 95 5c ff ff ff         	mov	word ptr [ebp - 0xa4], dx
 10037f1: 8d 8d 40 ff ff ff            	lea	ecx, [ebp - 0xc0]
 10037f7: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 10037fa: e8 81 f6 ff ff               	call	0x1002e80
 10037ff: 8d 85 40 ff ff ff            	lea	eax, [ebp - 0xc0]
 1003805: 8d 8e c4 03 00 00            	lea	ecx, [esi + 0x3c4]
 100380b: 50                           	push	eax
 100380c: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 1003813: 89 8d 1c ff ff ff            	mov	dword ptr [ebp - 0xe4], ecx
 1003819: e8 d2 f9 ff ff               	call	0x10031f0
 100381e: 8b c7                        	mov	eax, edi
 1003820: 8d 50 02                     	lea	edx, [eax + 0x2]
 1003823: 66 8b 08                     	mov	cx, word ptr [eax]
 1003826: 83 c0 02                     	add	eax, 0x2
 1003829: 66 3b cb                     	cmp	cx, bx
 100382c: 75 f5                        	jne	0x1003823 <.text+0xb3>
 100382e: 2b c2                        	sub	eax, edx
 1003830: d1 f8                        	sar	eax
 1003832: 50                           	push	eax
 1003833: 57                           	push	edi
 1003834: 8d 8e dc 03 00 00            	lea	ecx, [esi + 0x3dc]
 100383a: e8 f1 c7 40 ff               	call	0x410030
 100383f: 80 7d 0c 00                  	cmp	byte ptr [ebp + 0xc], 0x0
 1003843: 74 60                        	je	0x10038a5 <.text+0x135>
 1003845: 83 bd 70 ff ff ff 08         	cmp	dword ptr [ebp - 0x90], 0x8
 100384c: 72 0f                        	jb	0x100385d <.text+0xed>
 100384e: 8b 8d 5c ff ff ff            	mov	ecx, dword ptr [ebp - 0xa4]
 1003854: 51                           	push	ecx
 1003855: e8 cd 22 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 100385a: 83 c4 04                     	add	esp, 0x4
 100385d: 8b 85 58 ff ff ff            	mov	eax, dword ptr [ebp - 0xa8]
 1003863: 33 d2                        	xor	edx, edx
 1003865: 50                           	push	eax
 1003866: c7 85 70 ff ff ff 07 00 00 00	mov	dword ptr [ebp - 0x90], 0x7
 1003870: 89 9d 6c ff ff ff            	mov	dword ptr [ebp - 0x94], ebx
 1003876: 66 89 95 5c ff ff ff         	mov	word ptr [ebp - 0xa4], dx
 100387d: e8 a5 22 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003882: 83 c4 04                     	add	esp, 0x4
 1003885: b0 01                        	mov	al, 0x1
 1003887: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 100388a: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1003891: 59                           	pop	ecx
 1003892: 5f                           	pop	edi
 1003893: 5e                           	pop	esi
 1003894: 5b                           	pop	ebx
 1003895: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 1003898: 33 cd                        	xor	ecx, ebp
 100389a: e8 39 39 3d 00               	call	0x13d71d8 <.text+0x3d3a68>
 100389f: 8b e5                        	mov	esp, ebp
 10038a1: 5d                           	pop	ebp
 10038a2: c2 08 00                     	ret	0x8
 10038a5: 83 be f4 03 00 00 08         	cmp	dword ptr [esi + 0x3f4], 0x8
 10038ac: 72 08                        	jb	0x10038b6 <.text+0x146>
 10038ae: 8b b6 e0 03 00 00            	mov	esi, dword ptr [esi + 0x3e0]
 10038b4: eb 06                        	jmp	0x10038bc <.text+0x14c>
 10038b6: 81 c6 e0 03 00 00            	add	esi, 0x3e0
 10038bc: 56                           	push	esi
 10038bd: 68 78 21 56 01               	push	0x1562178
 10038c2: e8 29 c6 19 00               	call	0x119fef0 <.text+0x19c780>
 10038c7: 83 c4 04                     	add	esp, 0x4
 10038ca: 50                           	push	eax
 10038cb: e8 50 fd 21 00               	call	0x1223620 <.text+0x21feb0>
 10038d0: 83 c4 08                     	add	esp, 0x8
 10038d3: 84 c0                        	test	al, al
 10038d5: 75 07                        	jne	0x10038de <.text+0x16e>
 10038d7: 32 db                        	xor	bl, bl
 10038d9: e9 9d 03 00 00               	jmp	0x1003c7b <.text+0x50b>
 10038de: 6a 08                        	push	0x8
 10038e0: 89 5d b0                     	mov	dword ptr [ebp - 0x50], ebx
 10038e3: e8 32 32 3d 00               	call	0x13d6b1a <.text+0x3d33aa>
 10038e8: 83 c4 04                     	add	esp, 0x4
 10038eb: 3b c3                        	cmp	eax, ebx
 10038ed: 0f 84 39 04 00 00            	je	0x1003d2c <.text+0x5bc>
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
 1003921: e8 f4 31 3d 00               	call	0x13d6b1a <.text+0x3d33aa>
 1003926: 83 c4 04                     	add	esp, 0x4
 1003929: 3b c3                        	cmp	eax, ebx
 100392b: 0f 84 c8 03 00 00            	je	0x1003cf9 <.text+0x589>
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
 100395b: e8 b0 18 22 00               	call	0x1225210 <.text+0x221aa0>
 1003960: 83 c4 08                     	add	esp, 0x8
 1003963: 84 c0                        	test	al, al
 1003965: 0f 84 b4 02 00 00            	je	0x1003c1f <.text+0x4af>
 100396b: eb 03                        	jmp	0x1003970 <.text+0x200>
 100396d: 8d 49 00                     	lea	ecx, [ecx]
 1003970: 68 ec b0 82 01               	push	0x182b0ec
 1003975: e8 76 c5 19 00               	call	0x119fef0 <.text+0x19c780>
 100397a: 8b c8                        	mov	ecx, eax
 100397c: 83 c4 04                     	add	esp, 0x4
 100397f: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003982: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003985: 83 c1 02                     	add	ecx, 0x2
 1003988: 66 3b d3                     	cmp	dx, bx
 100398b: 75 f5                        	jne	0x1003982 <.text+0x212>
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
 10039a2: 0f 85 61 02 00 00            	jne	0x1003c09 <.text+0x499>
 10039a8: 6a 08                        	push	0x8
 10039aa: 89 5d 90                     	mov	dword ptr [ebp - 0x70], ebx
 10039ad: e8 68 31 3d 00               	call	0x13d6b1a <.text+0x3d33aa>
 10039b2: 83 c4 04                     	add	esp, 0x4
 10039b5: 3b c3                        	cmp	eax, ebx
 10039b7: 0f 84 09 03 00 00            	je	0x1003cc6 <.text+0x556>
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
 10039ff: e8 ec c4 19 00               	call	0x119fef0 <.text+0x19c780>
 1003a04: 8b c8                        	mov	ecx, eax
 1003a06: 83 c4 04                     	add	esp, 0x4
 1003a09: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003a0c: 8d 64 24 00                  	lea	esp, [esp]
 1003a10: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003a13: 83 c1 02                     	add	ecx, 0x2
 1003a16: 66 3b d3                     	cmp	dx, bx
 1003a19: 75 f5                        	jne	0x1003a10 <.text+0x2a0>
 1003a1b: 2b ce                        	sub	ecx, esi
 1003a1d: d1 f9                        	sar	ecx
 1003a1f: 51                           	push	ecx
 1003a20: 50                           	push	eax
 1003a21: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
 1003a24: e8 07 c6 40 ff               	call	0x410030
 1003a29: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 1003a2c: 50                           	push	eax
 1003a2d: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
 1003a31: e8 1a 17 22 00               	call	0x1225150 <.text+0x2219e0>
 1003a36: 83 c4 04                     	add	esp, 0x4
 1003a39: 84 c0                        	test	al, al
 1003a3b: 0f 84 88 01 00 00            	je	0x1003bc9 <.text+0x459>
 1003a41: 68 cc b0 82 01               	push	0x182b0cc
 1003a46: e8 a5 c4 19 00               	call	0x119fef0 <.text+0x19c780>
 1003a4b: 8b c8                        	mov	ecx, eax
 1003a4d: 83 c4 04                     	add	esp, 0x4
 1003a50: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003a53: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003a56: 83 c1 02                     	add	ecx, 0x2
 1003a59: 66 3b d3                     	cmp	dx, bx
 1003a5c: 75 f5                        	jne	0x1003a53 <.text+0x2e3>
 1003a5e: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
 1003a61: 2b ce                        	sub	ecx, esi
 1003a63: d1 f9                        	sar	ecx
 1003a65: 8b f7                        	mov	esi, edi
 1003a67: 3b f9                        	cmp	edi, ecx
 1003a69: 72 02                        	jb	0x1003a6d <.text+0x2fd>
 1003a6b: 8b f1                        	mov	esi, ecx
 1003a6d: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 1003a71: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
 1003a74: 73 03                        	jae	0x1003a79 <.text+0x309>
 1003a76: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
 1003a79: 3b f3                        	cmp	esi, ebx
 1003a7b: 76 24                        	jbe	0x1003aa1 <.text+0x331>
 1003a7d: 8d 49 00                     	lea	ecx, [ecx]
 1003a80: 66 8b 1a                     	mov	bx, word ptr [edx]
 1003a83: 66 3b 18                     	cmp	bx, word ptr [eax]
 1003a86: 75 0d                        	jne	0x1003a95 <.text+0x325>
 1003a88: 83 c2 02                     	add	edx, 0x2
 1003a8b: 83 c0 02                     	add	eax, 0x2
 1003a8e: 4e                           	dec	esi
 1003a8f: 75 ef                        	jne	0x1003a80 <.text+0x310>
 1003a91: 33 db                        	xor	ebx, ebx
 1003a93: eb 0c                        	jmp	0x1003aa1 <.text+0x331>
 1003a95: 1b c0                        	sbb	eax, eax
 1003a97: 83 e0 fe                     	and	eax, -0x2
 1003a9a: 40                           	inc	eax
 1003a9b: 33 db                        	xor	ebx, ebx
 1003a9d: 3b c3                        	cmp	eax, ebx
 1003a9f: 75 12                        	jne	0x1003ab3 <.text+0x343>
 1003aa1: 3b f9                        	cmp	edi, ecx
 1003aa3: 73 05                        	jae	0x1003aaa <.text+0x33a>
 1003aa5: 83 c8 ff                     	or	eax, -0x1
 1003aa8: eb 07                        	jmp	0x1003ab1 <.text+0x341>
 1003aaa: 33 c0                        	xor	eax, eax
 1003aac: 3b f9                        	cmp	edi, ecx
 1003aae: 0f 95 c0                     	setne	al
 1003ab1: 3b c3                        	cmp	eax, ebx
 1003ab3: 0f 94 c0                     	sete	al
 1003ab6: 84 c0                        	test	al, al
 1003ab8: 74 11                        	je	0x1003acb <.text+0x35b>
 1003aba: 53                           	push	ebx
 1003abb: e8 a0 fb 21 00               	call	0x1223660 <.text+0x21fef0>
 1003ac0: 89 85 78 ff ff ff            	mov	dword ptr [ebp - 0x88], eax
 1003ac6: e9 e2 00 00 00               	jmp	0x1003bad <.text+0x43d>
 1003acb: 68 30 1c 57 01               	push	0x1571c30
 1003ad0: e8 1b c4 19 00               	call	0x119fef0 <.text+0x19c780>
 1003ad5: 8b c8                        	mov	ecx, eax
 1003ad7: 83 c4 04                     	add	esp, 0x4
 1003ada: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003add: 8d 49 00                     	lea	ecx, [ecx]
 1003ae0: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003ae3: 83 c1 02                     	add	ecx, 0x2
 1003ae6: 66 3b d3                     	cmp	dx, bx
 1003ae9: 75 f5                        	jne	0x1003ae0 <.text+0x370>
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
 1003b00: 75 0e                        	jne	0x1003b10 <.text+0x3a0>
 1003b02: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
 1003b05: 51                           	push	ecx
 1003b06: e8 45 16 22 00               	call	0x1225150 <.text+0x2219e0>
 1003b0b: e9 9d 00 00 00               	jmp	0x1003bad <.text+0x43d>
 1003b10: 68 a4 b0 82 01               	push	0x182b0a4
 1003b15: e8 d6 c3 19 00               	call	0x119fef0 <.text+0x19c780>
 1003b1a: 8b c8                        	mov	ecx, eax
 1003b1c: 83 c4 04                     	add	esp, 0x4
 1003b1f: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003b22: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003b25: 83 c1 02                     	add	ecx, 0x2
 1003b28: 66 3b d3                     	cmp	dx, bx
 1003b2b: 75 f5                        	jne	0x1003b22 <.text+0x3b2>
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
 1003b42: 75 2c                        	jne	0x1003b70 <.text+0x400>
 1003b44: 53                           	push	ebx
 1003b45: e8 16 fb 21 00               	call	0x1223660 <.text+0x21fef0>
 1003b4a: 53                           	push	ebx
 1003b4b: 89 85 7c ff ff ff            	mov	dword ptr [ebp - 0x84], eax
 1003b51: e8 0a fb 21 00               	call	0x1223660 <.text+0x21fef0>
 1003b56: 53                           	push	ebx
 1003b57: 89 45 80                     	mov	dword ptr [ebp - 0x80], eax
 1003b5a: e8 01 fb 21 00               	call	0x1223660 <.text+0x21fef0>
 1003b5f: 53                           	push	ebx
 1003b60: 89 45 84                     	mov	dword ptr [ebp - 0x7c], eax
 1003b63: e8 f8 fa 21 00               	call	0x1223660 <.text+0x21fef0>
 1003b68: 83 c4 10                     	add	esp, 0x10
 1003b6b: 89 45 88                     	mov	dword ptr [ebp - 0x78], eax
 1003b6e: eb 40                        	jmp	0x1003bb0 <.text+0x440>
 1003b70: 68 78 b0 82 01               	push	0x182b078
 1003b75: e8 76 c3 19 00               	call	0x119fef0 <.text+0x19c780>
 1003b7a: 8b c8                        	mov	ecx, eax
 1003b7c: 83 c4 04                     	add	esp, 0x4
 1003b7f: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003b82: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003b85: 83 c1 02                     	add	ecx, 0x2
 1003b88: 66 3b d3                     	cmp	dx, bx
 1003b8b: 75 f5                        	jne	0x1003b82 <.text+0x412>
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
 1003ba2: 75 0c                        	jne	0x1003bb0 <.text+0x440>
 1003ba4: 53                           	push	ebx
 1003ba5: e8 b6 fa 21 00               	call	0x1223660 <.text+0x21fef0>
 1003baa: 89 45 8c                     	mov	dword ptr [ebp - 0x74], eax
 1003bad: 83 c4 04                     	add	esp, 0x4
 1003bb0: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1003bb3: 51                           	push	ecx
 1003bb4: e8 97 15 22 00               	call	0x1225150 <.text+0x2219e0>
 1003bb9: 83 c4 04                     	add	esp, 0x4
 1003bbc: 84 c0                        	test	al, al
 1003bbe: 0f 85 7d fe ff ff            	jne	0x1003a41 <.text+0x2d1>
 1003bc4: bf 07 00 00 00               	mov	edi, 0x7
 1003bc9: 8b 8d 1c ff ff ff            	mov	ecx, dword ptr [ebp - 0xe4]
 1003bcf: 8d 95 78 ff ff ff            	lea	edx, [ebp - 0x88]
 1003bd5: 52                           	push	edx
 1003bd6: e8 15 f6 ff ff               	call	0x10031f0
 1003bdb: 83 7d a8 08                  	cmp	dword ptr [ebp - 0x58], 0x8
 1003bdf: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 1003be3: 72 0c                        	jb	0x1003bf1 <.text+0x481>
 1003be5: 8b 45 94                     	mov	eax, dword ptr [ebp - 0x6c]
 1003be8: 50                           	push	eax
 1003be9: e8 39 1f 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003bee: 83 c4 04                     	add	esp, 0x4
 1003bf1: 8b 55 90                     	mov	edx, dword ptr [ebp - 0x70]
 1003bf4: 33 c9                        	xor	ecx, ecx
 1003bf6: 52                           	push	edx
 1003bf7: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
 1003bfa: 89 5d a4                     	mov	dword ptr [ebp - 0x5c], ebx
 1003bfd: 66 89 4d 94                  	mov	word ptr [ebp - 0x6c], cx
 1003c01: e8 21 1f 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003c06: 83 c4 04                     	add	esp, 0x4
 1003c09: 8d 45 b0                     	lea	eax, [ebp - 0x50]
 1003c0c: 6a 01                        	push	0x1
 1003c0e: 50                           	push	eax
 1003c0f: e8 fc 15 22 00               	call	0x1225210 <.text+0x221aa0>
 1003c14: 83 c4 08                     	add	esp, 0x8
 1003c17: 84 c0                        	test	al, al
 1003c19: 0f 85 51 fd ff ff            	jne	0x1003970 <.text+0x200>
 1003c1f: be 08 00 00 00               	mov	esi, 0x8
 1003c24: 39 75 e8                     	cmp	dword ptr [ebp - 0x18], esi
 1003c27: 72 0c                        	jb	0x1003c35 <.text+0x4c5>
 1003c29: 8b 4d d4                     	mov	ecx, dword ptr [ebp - 0x2c]
 1003c2c: 51                           	push	ecx
 1003c2d: e8 f5 1e 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003c32: 83 c4 04                     	add	esp, 0x4
 1003c35: 8b 45 d0                     	mov	eax, dword ptr [ebp - 0x30]
 1003c38: 33 d2                        	xor	edx, edx
 1003c3a: 50                           	push	eax
 1003c3b: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 1003c3e: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 1003c41: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
 1003c45: e8 dd 1e 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003c4a: 83 c4 04                     	add	esp, 0x4
 1003c4d: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 1003c50: 39 75 c8                     	cmp	dword ptr [ebp - 0x38], esi
 1003c53: 72 0c                        	jb	0x1003c61 <.text+0x4f1>
 1003c55: 8b 4d b4                     	mov	ecx, dword ptr [ebp - 0x4c]
 1003c58: 51                           	push	ecx
 1003c59: e8 c9 1e 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003c5e: 83 c4 04                     	add	esp, 0x4
 1003c61: 8b 45 b0                     	mov	eax, dword ptr [ebp - 0x50]
 1003c64: 33 d2                        	xor	edx, edx
 1003c66: 50                           	push	eax
 1003c67: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
 1003c6a: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
 1003c6d: 66 89 55 b4                  	mov	word ptr [ebp - 0x4c], dx
 1003c71: e8 b1 1e 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003c76: 83 c4 04                     	add	esp, 0x4
 1003c79: b3 01                        	mov	bl, 0x1
 1003c7b: 83 bd 70 ff ff ff 08         	cmp	dword ptr [ebp - 0x90], 0x8
 1003c82: 72 0f                        	jb	0x1003c93 <.text+0x523>
 1003c84: 8b 8d 5c ff ff ff            	mov	ecx, dword ptr [ebp - 0xa4]
 1003c8a: 51                           	push	ecx
 1003c8b: e8 97 1e 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003c90: 83 c4 04                     	add	esp, 0x4
 1003c93: 8b 85 58 ff ff ff            	mov	eax, dword ptr [ebp - 0xa8]
 1003c99: 33 d2                        	xor	edx, edx
 1003c9b: 50                           	push	eax
 1003c9c: c7 85 70 ff ff ff 07 00 00 00	mov	dword ptr [ebp - 0x90], 0x7
 1003ca6: c7 85 6c ff ff ff 00 00 00 00	mov	dword ptr [ebp - 0x94], 0x0
 1003cb0: 66 89 95 5c ff ff ff         	mov	word ptr [ebp - 0xa4], dx
 1003cb7: e8 6b 1e 3d 00               	call	0x13d5b27 <.text+0x3d23b7>
 1003cbc: 83 c4 04                     	add	esp, 0x4
 1003cbf: 8a c3                        	mov	al, bl
 1003cc1: e9 c1 fb ff ff               	jmp	0x1003887 <.text+0x117>
 1003cc6: 8d 8d 38 ff ff ff            	lea	ecx, [ebp - 0xc8]
 1003ccc: 51                           	push	ecx
 1003ccd: 8d 8d 20 ff ff ff            	lea	ecx, [ebp - 0xe0]
 1003cd3: 89 9d 38 ff ff ff            	mov	dword ptr [ebp - 0xc8], ebx
 1003cd9: e8 ec 27 3d 00               	call	0x13d64ca <.text+0x3d2d5a>
 1003cde: 68 90 0f 91 01               	push	0x1910f90
 1003ce3: 8d 95 20 ff ff ff            	lea	edx, [ebp - 0xe0]
 1003ce9: 52                           	push	edx
 1003cea: c7 85 20 ff ff ff 84 20 56 01	mov	dword ptr [ebp - 0xe0], 0x1562084
 1003cf4: e8 a1 2e 3d 00               	call	0x13d6b9a <.text+0x3d342a>
 1003cf9: 8d 85 3c ff ff ff            	lea	eax, [ebp - 0xc4]
 1003cff: 50                           	push	eax
 1003d00: 8d 8d 2c ff ff ff            	lea	ecx, [ebp - 0xd4]
 1003d06: 89 9d 3c ff ff ff            	mov	dword ptr [ebp - 0xc4], ebx
 1003d0c: e8 b9 27 3d 00               	call	0x13d64ca <.text+0x3d2d5a>
 1003d11: 68 90 0f 91 01               	push	0x1910f90
 1003d16: 8d 8d 2c ff ff ff            	lea	ecx, [ebp - 0xd4]
 1003d1c: 51                           	push	ecx
 1003d1d: c7 85 2c ff ff ff 84 20 56 01	mov	dword ptr [ebp - 0xd4], 0x1562084
 1003d27: e8 6e 2e 3d 00               	call	0x13d6b9a <.text+0x3d342a>
 1003d2c: 8d 95 38 ff ff ff            	lea	edx, [ebp - 0xc8]
 1003d32: 52                           	push	edx
 1003d33: 8d 8d 20 ff ff ff            	lea	ecx, [ebp - 0xe0]
 1003d39: 89 9d 38 ff ff ff            	mov	dword ptr [ebp - 0xc8], ebx
 1003d3f: e8 86 27 3d 00               	call	0x13d64ca <.text+0x3d2d5a>
 1003d44: 68 90 0f 91 01               	push	0x1910f90
 1003d49: 8d 85 20 ff ff ff            	lea	eax, [ebp - 0xe0]
 1003d4f: 50                           	push	eax
 1003d50: c7 85 20 ff ff ff 84 20 56 01	mov	dword ptr [ebp - 0xe0], 0x1562084
 1003d5a: e8 3b 2e 3d 00               	call	0x13d6b9a <.text+0x3d342a>
 1003d5f: 8d 8d 3c ff ff ff            	lea	ecx, [ebp - 0xc4]
 1003d65: 51                           	push	ecx
 1003d66: 8d 8d 2c ff ff ff            	lea	ecx, [ebp - 0xd4]
 1003d6c: 89 9d 3c ff ff ff            	mov	dword ptr [ebp - 0xc4], ebx
 1003d72: e8 53 27 3d 00               	call	0x13d64ca <.text+0x3d2d5a>
 1003d77: 68 90 0f 91 01               	push	0x1910f90
 1003d7c: 8d 95 2c ff ff ff            	lea	edx, [ebp - 0xd4]
 1003d82: 52                           	push	edx
 1003d83: c7 85 2c ff ff ff 84 20 56 01	mov	dword ptr [ebp - 0xd4], 0x1562084
 1003d8d: e8 08 2e 3d 00               	call	0x13d6b9a <.text+0x3d342a>
 1003d92: cc                           	int3
 1003d93: cc                           	int3
 1003d94: cc                           	int3
 1003d95: cc                           	int3
 1003d96: cc                           	int3
 1003d97: cc                           	int3
 1003d98: cc                           	int3
 1003d99: cc                           	int3
 1003d9a: cc                           	int3
 1003d9b: cc                           	int3
 1003d9c: cc                           	int3
 1003d9d: cc                           	int3
 1003d9e: cc                           	int3
 1003d9f: cc                           	int3
