
<stdin>:	file format elf32-i386

Disassembly of section .text:

010f78f0 <.text>:
 10f78f0: fa                           	cli
 10f78f1: 04 8b                        	add	al, -0x75
 10f78f3: c2 c1 e8                     	ret	-0x173f
 10f78f6: 1f                           	pop	ds
 10f78f7: 03 c2                        	add	eax, edx
 10f78f9: 33 c9                        	xor	ecx, ecx
 10f78fb: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 10f78fe: 89 4d f8                     	mov	dword ptr [ebp - 0x8], ecx
 10f7901: 3b c1                        	cmp	eax, ecx
 10f7903: 0f 8e 5c 04 00 00            	jle	0x10f7d65 <.text+0x475>
 10f7909: 57                           	push	edi
 10f790a: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 10f790d: 89 4d fc                     	mov	dword ptr [ebp - 0x4], ecx
 10f7910: 56                           	push	esi
 10f7911: 8b b3 f8 1d 00 00            	mov	esi, dword ptr [ebx + 0x1df8]
 10f7917: 8b 8b fc 1d 00 00            	mov	ecx, dword ptr [ebx + 0x1dfc]
 10f791d: 2b ce                        	sub	ecx, esi
 10f791f: b8 39 8e e3 38               	mov	eax, 0x38e38e39
 10f7924: f7 e9                        	imul	ecx
 10f7926: c1 fa 04                     	sar	edx, 0x4
 10f7929: 8b c2                        	mov	eax, edx
 10f792b: c1 e8 1f                     	shr	eax, 0x1f
 10f792e: 03 c2                        	add	eax, edx
 10f7930: 3b 45 f8                     	cmp	eax, dword ptr [ebp - 0x8]
 10f7933: 76 40                        	jbe	0x10f7975 <.text+0x85>
 10f7935: 03 75 fc                     	add	esi, dword ptr [ebp - 0x4]
 10f7938: 83 7f 3c 08                  	cmp	dword ptr [edi + 0x3c], 0x8
 10f793c: 8b 4f 38                     	mov	ecx, dword ptr [edi + 0x38]
 10f793f: 72 05                        	jb	0x10f7946 <.text+0x56>
 10f7941: 8b 47 28                     	mov	eax, dword ptr [edi + 0x28]
 10f7944: eb 03                        	jmp	0x10f7949 <.text+0x59>
 10f7946: 8d 47 28                     	lea	eax, [edi + 0x28]
 10f7949: 8b 56 14                     	mov	edx, dword ptr [esi + 0x14]
 10f794c: 51                           	push	ecx
 10f794d: 50                           	push	eax
 10f794e: 52                           	push	edx
 10f794f: 6a 00                        	push	0x0
 10f7951: 8b ce                        	mov	ecx, esi
 10f7953: e8 d8 a2 30 ff               	call	0x401c30
 10f7958: 85 c0                        	test	eax, eax
 10f795a: 74 23                        	je	0x10f797f <.text+0x8f>
 10f795c: 8b 45 f8                     	mov	eax, dword ptr [ebp - 0x8]
 10f795f: 83 45 fc 48                  	add	dword ptr [ebp - 0x4], 0x48
 10f7963: 40                           	inc	eax
 10f7964: 89 45 f8                     	mov	dword ptr [ebp - 0x8], eax
 10f7967: 3b 45 f0                     	cmp	eax, dword ptr [ebp - 0x10]
 10f796a: 7c a5                        	jl	0x10f7911 <.text+0x21>
 10f796c: 5e                           	pop	esi
 10f796d: 5f                           	pop	edi
 10f796e: 5b                           	pop	ebx
 10f796f: 8b e5                        	mov	esp, ebp
 10f7971: 5d                           	pop	ebp
 10f7972: c2 04 00                     	ret	0x4
 10f7975: 68 c8 22 56 01               	push	0x15622c8
 10f797a: e8 98 9e 2c 00               	call	0x13c1817 <.text+0x2c9f27>
 10f797f: 8b 7f 64                     	mov	edi, dword ptr [edi + 0x64]
 10f7982: 8b 5f 08                     	mov	ebx, dword ptr [edi + 0x8]
 10f7985: 2b 5f 04                     	sub	ebx, dword ptr [edi + 0x4]
 10f7988: 83 c6 28                     	add	esi, 0x28
 10f798b: c1 fb 02                     	sar	ebx, 0x2
 10f798e: ba 08 00 00 00               	mov	edx, 0x8
 10f7993: 89 7d f0                     	mov	dword ptr [ebp - 0x10], edi
 10f7996: 89 5d f8                     	mov	dword ptr [ebp - 0x8], ebx
 10f7999: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
 10f799c: c7 46 14 00 00 00 00         	mov	dword ptr [esi + 0x14], 0x0
 10f79a3: 8d 46 04                     	lea	eax, [esi + 0x4]
 10f79a6: 39 56 18                     	cmp	dword ptr [esi + 0x18], edx
 10f79a9: 72 04                        	jb	0x10f79af <.text+0xbf>
 10f79ab: 8b 08                        	mov	ecx, dword ptr [eax]
 10f79ad: eb 02                        	jmp	0x10f79b1 <.text+0xc1>
 10f79af: 8b c8                        	mov	ecx, eax
 10f79b1: 33 ff                        	xor	edi, edi
 10f79b3: 66 89 39                     	mov	word ptr [ecx], di
 10f79b6: 33 c9                        	xor	ecx, ecx
 10f79b8: 3b d9                        	cmp	ebx, ecx
 10f79ba: 0f 8e 94 03 00 00            	jle	0x10f7d54 <.text+0x464>
 10f79c0: 8d 45 bc                     	lea	eax, [ebp - 0x44]
 10f79c3: 89 4d e8                     	mov	dword ptr [ebp - 0x18], ecx
 10f79c6: 50                           	push	eax
 10f79c7: b9 50 f7 d9 01               	mov	ecx, 0x1d9f750
 10f79cc: e8 7f 84 46 ff               	call	0x55fe50
 10f79d1: 8d 4d 98                     	lea	ecx, [ebp - 0x68]
 10f79d4: 51                           	push	ecx
 10f79d5: b9 50 f7 d9 01               	mov	ecx, 0x1d9f750
 10f79da: e8 61 c9 6c ff               	call	0x7c4340
 10f79df: 8b 75 bc                     	mov	esi, dword ptr [ebp - 0x44]
 10f79e2: 85 f6                        	test	esi, esi
 10f79e4: 0f 84 65 03 00 00            	je	0x10f7d4f <.text+0x45f>
 10f79ea: 8b 16                        	mov	edx, dword ptr [esi]
 10f79ec: 85 d2                        	test	edx, edx
 10f79ee: 0f 84 5b 03 00 00            	je	0x10f7d4f <.text+0x45f>
 10f79f4: 8b 08                        	mov	ecx, dword ptr [eax]
 10f79f6: 85 c9                        	test	ecx, ecx
 10f79f8: 74 02                        	je	0x10f79fc <.text+0x10c>
 10f79fa: 8b 09                        	mov	ecx, dword ptr [ecx]
 10f79fc: 3b d1                        	cmp	edx, ecx
 10f79fe: 0f 85 4b 03 00 00            	jne	0x10f7d4f <.text+0x45f>
 10f7a04: 8b 4d c4                     	mov	ecx, dword ptr [ebp - 0x3c]
 10f7a07: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
 10f7a0a: 0f 84 53 03 00 00            	je	0x10f7d63 <.text+0x473>
 10f7a10: 8b c2                        	mov	eax, edx
 10f7a12: 85 c0                        	test	eax, eax
 10f7a14: 0f 84 35 03 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7a1a: 85 c9                        	test	ecx, ecx
 10f7a1c: 0f 84 2d 03 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7a22: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
 10f7a25: 0f 84 24 03 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7a2b: 8b 51 0c                     	mov	edx, dword ptr [ecx + 0xc]
 10f7a2e: 8b 0d dc f6 a6 01            	mov	ecx, dword ptr [0x1a6f6dc]
 10f7a34: 52                           	push	edx
 10f7a35: e8 16 e1 03 00               	call	0x1135b50 <.text+0x3e260>
 10f7a3a: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
 10f7a3d: 85 c0                        	test	eax, eax
 10f7a3f: 0f 84 f4 02 00 00            	je	0x10f7d39 <.text+0x449>
 10f7a45: 33 ff                        	xor	edi, edi
 10f7a47: 89 7d 08                     	mov	dword ptr [ebp + 0x8], edi
 10f7a4a: 39 7d f8                     	cmp	dword ptr [ebp - 0x8], edi
 10f7a4d: 0f 8e e6 02 00 00            	jle	0x10f7d39 <.text+0x449>
 10f7a53: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 10f7a56: 8b 41 04                     	mov	eax, dword ptr [ecx + 0x4]
 10f7a59: 8b 49 08                     	mov	ecx, dword ptr [ecx + 0x8]
 10f7a5c: 2b c8                        	sub	ecx, eax
 10f7a5e: c1 f9 02                     	sar	ecx, 0x2
 10f7a61: 3b cf                        	cmp	ecx, edi
 10f7a63: 0f 86 0c ff ff ff            	jbe	0x10f7975 <.text+0x85>
 10f7a69: 8b 14 b8                     	mov	edx, dword ptr [eax + 4*edi]
 10f7a6c: 8b 5d e4                     	mov	ebx, dword ptr [ebp - 0x1c]
 10f7a6f: 8d 45 d4                     	lea	eax, [ebp - 0x2c]
 10f7a72: 50                           	push	eax
 10f7a73: 8d 4b 68                     	lea	ecx, [ebx + 0x68]
 10f7a76: 89 55 f4                     	mov	dword ptr [ebp - 0xc], edx
 10f7a79: e8 f2 e6 07 00               	call	0x1176170 <.text+0x7e880>
 10f7a7e: 8b ff                        	mov	edi, edi
 10f7a80: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 10f7a83: 51                           	push	ecx
 10f7a84: 8d 4b 68                     	lea	ecx, [ebx + 0x68]
 10f7a87: e8 b4 c8 6c ff               	call	0x7c4340
 10f7a8c: 8b 75 d4                     	mov	esi, dword ptr [ebp - 0x2c]
 10f7a8f: 85 f6                        	test	esi, esi
 10f7a91: 0f 84 b8 02 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7a97: 8b 16                        	mov	edx, dword ptr [esi]
 10f7a99: 85 d2                        	test	edx, edx
 10f7a9b: 0f 84 ae 02 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7aa1: 8b 08                        	mov	ecx, dword ptr [eax]
 10f7aa3: 85 c9                        	test	ecx, ecx
 10f7aa5: 74 02                        	je	0x10f7aa9 <.text+0x1b9>
 10f7aa7: 8b 09                        	mov	ecx, dword ptr [ecx]
 10f7aa9: 3b d1                        	cmp	edx, ecx
 10f7aab: 0f 85 9e 02 00 00            	jne	0x10f7d4f <.text+0x45f>
 10f7ab1: 8b 4d dc                     	mov	ecx, dword ptr [ebp - 0x24]
 10f7ab4: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
 10f7ab7: 74 3e                        	je	0x10f7af7 <.text+0x207>
 10f7ab9: 8b c2                        	mov	eax, edx
 10f7abb: 85 c0                        	test	eax, eax
 10f7abd: 0f 84 8c 02 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7ac3: 85 c9                        	test	ecx, ecx
 10f7ac5: 0f 84 84 02 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7acb: 39 48 04                     	cmp	dword ptr [eax + 0x4], ecx
 10f7ace: 0f 87 7b 02 00 00            	ja	0x10f7d4f <.text+0x45f>
 10f7ad4: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
 10f7ad7: 0f 83 72 02 00 00            	jae	0x10f7d4f <.text+0x45f>
 10f7add: 8b 55 f4                     	mov	edx, dword ptr [ebp - 0xc]
 10f7ae0: 3b 11                        	cmp	edx, dword ptr [ecx]
 10f7ae2: 74 10                        	je	0x10f7af4 <.text+0x204>
 10f7ae4: 6a 00                        	push	0x0
 10f7ae6: 8d 45 80                     	lea	eax, [ebp - 0x80]
 10f7ae9: 50                           	push	eax
 10f7aea: 8d 4d d4                     	lea	ecx, [ebp - 0x2c]
 10f7aed: e8 ee ed 77 ff               	call	0x8768e0
 10f7af2: eb 8c                        	jmp	0x10f7a80 <.text+0x190>
 10f7af4: ff 45 08                     	inc	dword ptr [ebp + 0x8]
 10f7af7: 47                           	inc	edi
 10f7af8: 3b 7d f8                     	cmp	edi, dword ptr [ebp - 0x8]
 10f7afb: 0f 8c 52 ff ff ff            	jl	0x10f7a53 <.text+0x163>
 10f7b01: 83 7d 08 00                  	cmp	dword ptr [ebp + 0x8], 0x0
 10f7b05: 0f 84 2e 02 00 00            	je	0x10f7d39 <.text+0x449>
 10f7b0b: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 10f7b0e: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
 10f7b11: 01 4d e8                     	add	dword ptr [ebp - 0x18], ecx
 10f7b14: 33 d2                        	xor	edx, edx
 10f7b16: 83 c7 68                     	add	edi, 0x68
 10f7b19: 89 55 fc                     	mov	dword ptr [ebp - 0x4], edx
 10f7b1c: 89 55 f4                     	mov	dword ptr [ebp - 0xc], edx
 10f7b1f: 89 7d e0                     	mov	dword ptr [ebp - 0x20], edi
 10f7b22: eb 03                        	jmp	0x10f7b27 <.text+0x237>
 10f7b24: 8b 55 f4                     	mov	edx, dword ptr [ebp - 0xc]
 10f7b27: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 10f7b2a: 8b 41 04                     	mov	eax, dword ptr [ecx + 0x4]
 10f7b2d: 8b 49 08                     	mov	ecx, dword ptr [ecx + 0x8]
 10f7b30: 2b c8                        	sub	ecx, eax
 10f7b32: c1 f9 02                     	sar	ecx, 0x2
 10f7b35: 3b ca                        	cmp	ecx, edx
 10f7b37: 0f 86 38 fe ff ff            	jbe	0x10f7975 <.text+0x85>
 10f7b3d: 8b 1c 90                     	mov	ebx, dword ptr [eax + 4*edx]
 10f7b40: 8d 55 c8                     	lea	edx, [ebp - 0x38]
 10f7b43: 52                           	push	edx
 10f7b44: 8b cf                        	mov	ecx, edi
 10f7b46: e8 25 e6 07 00               	call	0x1176170 <.text+0x7e880>
 10f7b4b: eb 03                        	jmp	0x10f7b50 <.text+0x260>
 10f7b4d: 8d 49 00                     	lea	ecx, [ecx]
 10f7b50: 8d 45 a4                     	lea	eax, [ebp - 0x5c]
 10f7b53: 50                           	push	eax
 10f7b54: 8b cf                        	mov	ecx, edi
 10f7b56: e8 e5 c7 6c ff               	call	0x7c4340
 10f7b5b: 8b 75 c8                     	mov	esi, dword ptr [ebp - 0x38]
 10f7b5e: 85 f6                        	test	esi, esi
 10f7b60: 0f 84 e9 01 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7b66: 8b 16                        	mov	edx, dword ptr [esi]
 10f7b68: 85 d2                        	test	edx, edx
 10f7b6a: 0f 84 df 01 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7b70: 8b 08                        	mov	ecx, dword ptr [eax]
 10f7b72: 85 c9                        	test	ecx, ecx
 10f7b74: 74 02                        	je	0x10f7b78 <.text+0x288>
 10f7b76: 8b 09                        	mov	ecx, dword ptr [ecx]
 10f7b78: 3b d1                        	cmp	edx, ecx
 10f7b7a: 0f 85 cf 01 00 00            	jne	0x10f7d4f <.text+0x45f>
 10f7b80: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
 10f7b83: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
 10f7b86: 0f 84 68 01 00 00            	je	0x10f7cf4 <.text+0x404>
 10f7b8c: 8b c2                        	mov	eax, edx
 10f7b8e: 85 c0                        	test	eax, eax
 10f7b90: 0f 84 b9 01 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7b96: 85 c9                        	test	ecx, ecx
 10f7b98: 0f 84 b1 01 00 00            	je	0x10f7d4f <.text+0x45f>
 10f7b9e: 39 48 04                     	cmp	dword ptr [eax + 0x4], ecx
 10f7ba1: 0f 87 a8 01 00 00            	ja	0x10f7d4f <.text+0x45f>
 10f7ba7: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
 10f7baa: 0f 83 9f 01 00 00            	jae	0x10f7d4f <.text+0x45f>
 10f7bb0: 3b 19                        	cmp	ebx, dword ptr [ecx]
 10f7bb2: 74 10                        	je	0x10f7bc4 <.text+0x2d4>
 10f7bb4: 6a 00                        	push	0x0
 10f7bb6: 8d 4d 8c                     	lea	ecx, [ebp - 0x74]
 10f7bb9: 51                           	push	ecx
 10f7bba: 8d 4d c8                     	lea	ecx, [ebp - 0x38]
 10f7bbd: e8 1e ed 77 ff               	call	0x8768e0
 10f7bc2: eb 8c                        	jmp	0x10f7b50 <.text+0x260>
 10f7bc4: 83 7d fc 00                  	cmp	dword ptr [ebp - 0x4], 0x0
 10f7bc8: 75 70                        	jne	0x10f7c3a <.text+0x34a>
 10f7bca: 68 78 55 83 01               	push	0x1835578
 10f7bcf: e8 1c 83 0a 00               	call	0x119fef0 <.text+0xa8600>
 10f7bd4: 8b c8                        	mov	ecx, eax
 10f7bd6: 83 c4 04                     	add	esp, 0x4
 10f7bd9: 8d 71 02                     	lea	esi, [ecx + 0x2]
 10f7bdc: 8d 64 24 00                  	lea	esp, [esp]
 10f7be0: 66 8b 11                     	mov	dx, word ptr [ecx]
 10f7be3: 83 c1 02                     	add	ecx, 0x2
 10f7be6: 66 85 d2                     	test	dx, dx
 10f7be9: 75 f5                        	jne	0x10f7be0 <.text+0x2f0>
 10f7beb: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
 10f7bee: 2b ce                        	sub	ecx, esi
 10f7bf0: d1 f9                        	sar	ecx
 10f7bf2: 51                           	push	ecx
 10f7bf3: 50                           	push	eax
 10f7bf4: 8b cf                        	mov	ecx, edi
 10f7bf6: e8 35 8b 31 ff               	call	0x410730
 10f7bfb: 8b 55 e4                     	mov	edx, dword ptr [ebp - 0x1c]
 10f7bfe: 6a ff                        	push	-0x1
 10f7c00: 6a 00                        	push	0x0
 10f7c02: 83 c2 04                     	add	edx, 0x4
 10f7c05: 52                           	push	edx
 10f7c06: 8b cf                        	mov	ecx, edi
 10f7c08: e8 73 7c 31 ff               	call	0x40f880
 10f7c0d: 68 e0 56 56 01               	push	0x15656e0
 10f7c12: e8 d9 82 0a 00               	call	0x119fef0 <.text+0xa8600>
 10f7c17: 8b c8                        	mov	ecx, eax
 10f7c19: 83 c4 04                     	add	esp, 0x4
 10f7c1c: 8d 71 02                     	lea	esi, [ecx + 0x2]
 10f7c1f: 90                           	nop
 10f7c20: 66 8b 11                     	mov	dx, word ptr [ecx]
 10f7c23: 83 c1 02                     	add	ecx, 0x2
 10f7c26: 66 85 d2                     	test	dx, dx
 10f7c29: 75 f5                        	jne	0x10f7c20 <.text+0x330>
 10f7c2b: 2b ce                        	sub	ecx, esi
 10f7c2d: d1 f9                        	sar	ecx
 10f7c2f: 51                           	push	ecx
 10f7c30: 50                           	push	eax
 10f7c31: 8b cf                        	mov	ecx, edi
 10f7c33: e8 f8 8a 31 ff               	call	0x410730
 10f7c38: eb 03                        	jmp	0x10f7c3d <.text+0x34d>
 10f7c3a: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
 10f7c3d: 8b 0d e8 f6 a6 01            	mov	ecx, dword ptr [0x1a6f6e8]
 10f7c43: 53                           	push	ebx
 10f7c44: e8 07 df 03 00               	call	0x1135b50 <.text+0x3e260>
 10f7c49: 85 c0                        	test	eax, eax
 10f7c4b: 0f 84 99 00 00 00            	je	0x10f7cea <.text+0x3fa>
 10f7c51: 8b 0d e8 f6 a6 01            	mov	ecx, dword ptr [0x1a6f6e8]
 10f7c57: 53                           	push	ebx
 10f7c58: e8 f3 de 03 00               	call	0x1135b50 <.text+0x3e260>
 10f7c5d: 6a ff                        	push	-0x1
 10f7c5f: 6a 00                        	push	0x0
 10f7c61: 83 c0 1c                     	add	eax, 0x1c
 10f7c64: 50                           	push	eax
 10f7c65: 8b cf                        	mov	ecx, edi
 10f7c67: e8 14 7c 31 ff               	call	0x40f880
 10f7c6c: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 10f7c6f: 4e                           	dec	esi
 10f7c70: 39 75 fc                     	cmp	dword ptr [ebp - 0x4], esi
 10f7c73: 74 2a                        	je	0x10f7c9f <.text+0x3af>
 10f7c75: 68 ec 56 56 01               	push	0x15656ec
 10f7c7a: e8 71 82 0a 00               	call	0x119fef0 <.text+0xa8600>
 10f7c7f: 8b c8                        	mov	ecx, eax
 10f7c81: 83 c4 04                     	add	esp, 0x4
 10f7c84: 8d 59 02                     	lea	ebx, [ecx + 0x2]
 10f7c87: 66 8b 11                     	mov	dx, word ptr [ecx]
 10f7c8a: 83 c1 02                     	add	ecx, 0x2
 10f7c8d: 66 85 d2                     	test	dx, dx
 10f7c90: 75 f5                        	jne	0x10f7c87 <.text+0x397>
 10f7c92: 2b cb                        	sub	ecx, ebx
 10f7c94: d1 f9                        	sar	ecx
 10f7c96: 51                           	push	ecx
 10f7c97: 50                           	push	eax
 10f7c98: 8b cf                        	mov	ecx, edi
 10f7c9a: e8 91 8a 31 ff               	call	0x410730
 10f7c9f: 8b 5d fc                     	mov	ebx, dword ptr [ebp - 0x4]
 10f7ca2: 85 db                        	test	ebx, ebx
 10f7ca4: 74 47                        	je	0x10f7ced <.text+0x3fd>
 10f7ca6: 3b de                        	cmp	ebx, esi
 10f7ca8: 74 43                        	je	0x10f7ced <.text+0x3fd>
 10f7caa: 8d 43 01                     	lea	eax, [ebx + 0x1]
 10f7cad: 99                           	cdq
 10f7cae: b9 03 00 00 00               	mov	ecx, 0x3
 10f7cb3: f7 f9                        	idiv	ecx
 10f7cb5: 85 d2                        	test	edx, edx
 10f7cb7: 75 34                        	jne	0x10f7ced <.text+0x3fd>
 10f7cb9: 68 e0 56 56 01               	push	0x15656e0
 10f7cbe: e8 2d 82 0a 00               	call	0x119fef0 <.text+0xa8600>
 10f7cc3: 8b c8                        	mov	ecx, eax
 10f7cc5: 83 c4 04                     	add	esp, 0x4
 10f7cc8: 8d 71 02                     	lea	esi, [ecx + 0x2]
 10f7ccb: eb 03                        	jmp	0x10f7cd0 <.text+0x3e0>
 10f7ccd: 8d 49 00                     	lea	ecx, [ecx]
 10f7cd0: 66 8b 11                     	mov	dx, word ptr [ecx]
 10f7cd3: 83 c1 02                     	add	ecx, 0x2
 10f7cd6: 66 85 d2                     	test	dx, dx
 10f7cd9: 75 f5                        	jne	0x10f7cd0 <.text+0x3e0>
 10f7cdb: 2b ce                        	sub	ecx, esi
 10f7cdd: d1 f9                        	sar	ecx
 10f7cdf: 51                           	push	ecx
 10f7ce0: 50                           	push	eax
 10f7ce1: 8b cf                        	mov	ecx, edi
 10f7ce3: e8 48 8a 31 ff               	call	0x410730
 10f7ce8: eb 03                        	jmp	0x10f7ced <.text+0x3fd>
 10f7cea: 8b 5d fc                     	mov	ebx, dword ptr [ebp - 0x4]
 10f7ced: 8b 7d e0                     	mov	edi, dword ptr [ebp - 0x20]
 10f7cf0: 43                           	inc	ebx
 10f7cf1: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 10f7cf4: 8b 45 f4                     	mov	eax, dword ptr [ebp - 0xc]
 10f7cf7: 40                           	inc	eax
 10f7cf8: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
 10f7cfb: 3b 45 f8                     	cmp	eax, dword ptr [ebp - 0x8]
 10f7cfe: 0f 8c 20 fe ff ff            	jl	0x10f7b24 <.text+0x234>
 10f7d04: 8b 55 f8                     	mov	edx, dword ptr [ebp - 0x8]
 10f7d07: 39 55 e8                     	cmp	dword ptr [ebp - 0x18], edx
 10f7d0a: 74 2d                        	je	0x10f7d39 <.text+0x449>
 10f7d0c: 68 6c 85 57 01               	push	0x157856c
 10f7d11: e8 da 81 0a 00               	call	0x119fef0 <.text+0xa8600>
 10f7d16: 8b c8                        	mov	ecx, eax
 10f7d18: 83 c4 04                     	add	esp, 0x4
 10f7d1b: 8d 71 02                     	lea	esi, [ecx + 0x2]
 10f7d1e: 8b ff                        	mov	edi, edi
 10f7d20: 66 8b 11                     	mov	dx, word ptr [ecx]
 10f7d23: 83 c1 02                     	add	ecx, 0x2
 10f7d26: 66 85 d2                     	test	dx, dx
 10f7d29: 75 f5                        	jne	0x10f7d20 <.text+0x430>
 10f7d2b: 2b ce                        	sub	ecx, esi
 10f7d2d: d1 f9                        	sar	ecx
 10f7d2f: 51                           	push	ecx
 10f7d30: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
 10f7d33: 50                           	push	eax
 10f7d34: e8 f7 89 31 ff               	call	0x410730
 10f7d39: 6a 00                        	push	0x0
 10f7d3b: 8d 85 74 ff ff ff            	lea	eax, [ebp - 0x8c]
 10f7d41: 50                           	push	eax
 10f7d42: 8d 4d bc                     	lea	ecx, [ebp - 0x44]
 10f7d45: e8 d6 bb 72 ff               	call	0x823920
 10f7d4a: e9 82 fc ff ff               	jmp	0x10f79d1 <.text+0xe1>
 10f7d4f: e8 53 f0 2d 00               	call	0x13d6da7 <.text+0x2df4b7>
 10f7d54: 89 4e 14                     	mov	dword ptr [esi + 0x14], ecx
 10f7d57: 39 56 18                     	cmp	dword ptr [esi + 0x18], edx
 10f7d5a: 72 02                        	jb	0x10f7d5e <.text+0x46e>
 10f7d5c: 8b 00                        	mov	eax, dword ptr [eax]
 10f7d5e: 33 c9                        	xor	ecx, ecx
 10f7d60: 66 89 08                     	mov	word ptr [eax], cx
 10f7d63: 5e                           	pop	esi
 10f7d64: 5f                           	pop	edi
 10f7d65: 5b                           	pop	ebx
 10f7d66: 8b e5                        	mov	esp, ebp
 10f7d68: 5d                           	pop	ebp
 10f7d69: c2 04 00                     	ret	0x4
 10f7d6c: cc                           	int3
 10f7d6d: cc                           	int3
 10f7d6e: cc                           	int3
 10f7d6f: cc                           	int3
 10f7d70: 55                           	push	ebp
 10f7d71: 8b ec                        	mov	ebp, esp
 10f7d73: 6a ff                        	push	-0x1
 10f7d75: 68 d8 cb 4b 01               	push	0x14bcbd8
 10f7d7a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 10f7d80: 50                           	push	eax
 10f7d81: 83 ec 68                     	sub	esp, 0x68
 10f7d84: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 10f7d89: 33 c5                        	xor	eax, ebp
 10f7d8b: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 10f7d8e: 53                           	push	ebx
 10f7d8f: 56                           	push	esi
 10f7d90: 57                           	push	edi
 10f7d91: 50                           	push	eax
 10f7d92: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 10f7d95: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 10f7d9b: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 10f7d9e: 8b f9                        	mov	edi, ecx
 10f7da0: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 10f7da3: 33 db                        	xor	ebx, ebx
 10f7da5: 89 5d a0                     	mov	dword ptr [ebp - 0x60], ebx
 10f7da8: 8b 97 fc 1d 00 00            	mov	edx, dword ptr [edi + 0x1dfc]
 10f7dae: 2b 97 f8 1d 00 00            	sub	edx, dword ptr [edi + 0x1df8]
 10f7db4: b8 39 8e e3 38               	mov	eax, 0x38e38e39
 10f7db9: f7 ea                        	imul	edx
 10f7dbb: c1 fa 04                     	sar	edx, 0x4
 10f7dbe: 8b c2                        	mov	eax, edx
 10f7dc0: c1 e8 1f                     	shr	eax, 0x1f
 10f7dc3: 03 c2                        	add	eax, edx
 10f7dc5: 89 75 8c                     	mov	dword ptr [ebp - 0x74], esi
 10f7dc8: 89 4d 9c                     	mov	dword ptr [ebp - 0x64], ecx
 10f7dcb: 74 67                        	je	0x10f7e34 <.text+0x544>
 10f7dcd: 89 5d a4                     	mov	dword ptr [ebp - 0x5c], ebx
 10f7dd0: eb 03                        	jmp	0x10f7dd5 <.text+0x4e5>
 10f7dd2: 8b 4d 9c                     	mov	ecx, dword ptr [ebp - 0x64]
 10f7dd5: 3b c3                        	cmp	eax, ebx
 10f7dd7: 0f 86 f9 00 00 00            	jbe	0x10f7ed6 <.text+0x5e6>
 10f7ddd: 8b 87 f8 1d 00 00            	mov	eax, dword ptr [edi + 0x1df8]
 10f7de3: 03 45 a4                     	add	eax, dword ptr [ebp - 0x5c]
 10f7de6: 83 79 18 08                  	cmp	dword ptr [ecx + 0x18], 0x8
 10f7dea: 8b 51 14                     	mov	edx, dword ptr [ecx + 0x14]
 10f7ded: 72 05                        	jb	0x10f7df4 <.text+0x504>
 10f7def: 8b                           	<unknown>
