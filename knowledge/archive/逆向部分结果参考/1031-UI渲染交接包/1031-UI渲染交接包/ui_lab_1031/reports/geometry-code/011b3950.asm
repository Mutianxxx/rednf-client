
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b3950 <.text>:
 11b3950: 55                           	push	ebp
 11b3951: 8b ec                        	mov	ebp, esp
 11b3953: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11b3956: 85 c0                        	test	eax, eax
 11b3958: 74 15                        	je	0x11b396f <.text+0x1f>
 11b395a: 8b 10                        	mov	edx, dword ptr [eax]
 11b395c: 8b 92 b4 00 00 00            	mov	edx, dword ptr [edx + 0xb4]
 11b3962: 51                           	push	ecx
 11b3963: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11b3966: 51                           	push	ecx
 11b3967: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b396a: 51                           	push	ecx
 11b396b: 8b c8                        	mov	ecx, eax
 11b396d: ff d2                        	call	edx
 11b396f: 5d                           	pop	ebp
 11b3970: c2 0c 00                     	ret	0xc
 11b3973: cc                           	int3
 11b3974: cc                           	int3
 11b3975: cc                           	int3
 11b3976: cc                           	int3
 11b3977: cc                           	int3
 11b3978: cc                           	int3
 11b3979: cc                           	int3
 11b397a: cc                           	int3
 11b397b: cc                           	int3
 11b397c: cc                           	int3
 11b397d: cc                           	int3
 11b397e: cc                           	int3
 11b397f: cc                           	int3
 11b3980: 55                           	push	ebp
 11b3981: 8b ec                        	mov	ebp, esp
 11b3983: 8b d1                        	mov	edx, ecx
 11b3985: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11b3988: 85 c9                        	test	ecx, ecx
 11b398a: 74 72                        	je	0x11b39fe <.text+0xae>
 11b398c: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
 11b398f: f3 0f 10 05 b4 61 56 01      	movss	xmm0, dword ptr [0x15661b4]
 11b3997: 53                           	push	ebx
 11b3998: 56                           	push	esi
 11b3999: 57                           	push	edi
 11b399a: 8b 31                        	mov	esi, dword ptr [ecx]
 11b399c: 6a 24                        	push	0x24
 11b399e: 50                           	push	eax
 11b399f: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11b39a2: 83 ec 14                     	sub	esp, 0x14
 11b39a5: f3 0f 11 44 24 10            	movss	dword ptr [esp + 0x10], xmm0
 11b39ab: f3 0f 11 44 24 0c            	movss	dword ptr [esp + 0xc], xmm0
 11b39b1: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11b39b9: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11b39bf: 8b f8                        	mov	edi, eax
 11b39c1: 0f b6 d8                     	movzx	ebx, al
 11b39c4: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11b39ca: 0f 57 c0                     	xorps	xmm0, xmm0
 11b39cd: c1 ef 10                     	shr	edi, 0x10
 11b39d0: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b39d5: 81 e7 ff 00 00 00            	and	edi, 0xff
 11b39db: c1 e3 10                     	shl	ebx, 0x10
 11b39de: 6a 00                        	push	0x0
 11b39e0: 25 00 ff 00 ff               	and	eax, 0xff00ff00
 11b39e5: 0b fb                        	or	edi, ebx
 11b39e7: 0b f8                        	or	edi, eax
 11b39e9: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b39ec: 57                           	push	edi
 11b39ed: 52                           	push	edx
 11b39ee: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11b39f1: 52                           	push	edx
 11b39f2: 8b 96 ac 00 00 00            	mov	edx, dword ptr [esi + 0xac]
 11b39f8: 50                           	push	eax
 11b39f9: ff d2                        	call	edx
 11b39fb: 5f                           	pop	edi
 11b39fc: 5e                           	pop	esi
 11b39fd: 5b                           	pop	ebx
 11b39fe: 5d                           	pop	ebp
 11b39ff: c2 14 00                     	ret	0x14
 11b3a02: cc                           	int3
 11b3a03: cc                           	int3
 11b3a04: cc                           	int3
 11b3a05: cc                           	int3
 11b3a06: cc                           	int3
 11b3a07: cc                           	int3
 11b3a08: cc                           	int3
 11b3a09: cc                           	int3
 11b3a0a: cc                           	int3
 11b3a0b: cc                           	int3
 11b3a0c: cc                           	int3
 11b3a0d: cc                           	int3
 11b3a0e: cc                           	int3
 11b3a0f: cc                           	int3
 11b3a10: 55                           	push	ebp
 11b3a11: 8b ec                        	mov	ebp, esp
 11b3a13: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11b3a16: 85 c0                        	test	eax, eax
 11b3a18: 74 13                        	je	0x11b3a2d <.text+0xdd>
 11b3a1a: 8b 10                        	mov	edx, dword ptr [eax]
 11b3a1c: 8b 92 b8 00 00 00            	mov	edx, dword ptr [edx + 0xb8]
 11b3a22: 51                           	push	ecx
 11b3a23: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b3a26: 6a 00                        	push	0x0
 11b3a28: 51                           	push	ecx
 11b3a29: 8b c8                        	mov	ecx, eax
 11b3a2b: ff d2                        	call	edx
 11b3a2d: 5d                           	pop	ebp
 11b3a2e: c2 08 00                     	ret	0x8
 11b3a31: cc                           	int3
 11b3a32: cc                           	int3
 11b3a33: cc                           	int3
 11b3a34: cc                           	int3
 11b3a35: cc                           	int3
 11b3a36: cc                           	int3
 11b3a37: cc                           	int3
 11b3a38: cc                           	int3
 11b3a39: cc                           	int3
 11b3a3a: cc                           	int3
 11b3a3b: cc                           	int3
 11b3a3c: cc                           	int3
 11b3a3d: cc                           	int3
 11b3a3e: cc                           	int3
 11b3a3f: cc                           	int3
 11b3a40: 55                           	push	ebp
 11b3a41: 8b ec                        	mov	ebp, esp
 11b3a43: 8b d1                        	mov	edx, ecx
 11b3a45: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11b3a48: 85 c9                        	test	ecx, ecx
 11b3a4a: 74 78                        	je	0x11b3ac4 <.text+0x174>
 11b3a4c: f3 0f 10 45 28               	movss	xmm0, dword ptr [ebp + 0x28]
 11b3a51: 8b 45 2c                     	mov	eax, dword ptr [ebp + 0x2c]
 11b3a54: 53                           	push	ebx
 11b3a55: 56                           	push	esi
 11b3a56: 57                           	push	edi
 11b3a57: 6a 24                        	push	0x24
 11b3a59: 6a 00                        	push	0x0
 11b3a5b: 83 ec 14                     	sub	esp, 0x14
 11b3a5e: f3 0f 11 44 24 10            	movss	dword ptr [esp + 0x10], xmm0
 11b3a64: f3 0f 10 45 24               	movss	xmm0, dword ptr [ebp + 0x24]
 11b3a69: f3 0f 11 44 24 0c            	movss	dword ptr [esp + 0xc], xmm0
 11b3a6f: f3 0f 10 45 18               	movss	xmm0, dword ptr [ebp + 0x18]
 11b3a74: 8b 31                        	mov	esi, dword ptr [ecx]
 11b3a76: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11b3a7c: f3 0f 10 45 14               	movss	xmm0, dword ptr [ebp + 0x14]
 11b3a81: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11b3a87: f3 0f 10 45 1c               	movss	xmm0, dword ptr [ebp + 0x1c]
 11b3a8c: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b3a91: 50                           	push	eax
 11b3a92: 8b 45 20                     	mov	eax, dword ptr [ebp + 0x20]
 11b3a95: 8b f8                        	mov	edi, eax
 11b3a97: 0f b6 d8                     	movzx	ebx, al
 11b3a9a: c1 ef 10                     	shr	edi, 0x10
 11b3a9d: 81 e7 ff 00 00 00            	and	edi, 0xff
 11b3aa3: c1 e3 10                     	shl	ebx, 0x10
 11b3aa6: 25 00 ff 00 ff               	and	eax, 0xff00ff00
 11b3aab: 0b fb                        	or	edi, ebx
 11b3aad: 0b f8                        	or	edi, eax
 11b3aaf: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b3ab2: 57                           	push	edi
 11b3ab3: 52                           	push	edx
 11b3ab4: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11b3ab7: 52                           	push	edx
 11b3ab8: 8b 96 ac 00 00 00            	mov	edx, dword ptr [esi + 0xac]
 11b3abe: 50                           	push	eax
 11b3abf: ff d2                        	call	edx
 11b3ac1: 5f                           	pop	edi
 11b3ac2: 5e                           	pop	esi
 11b3ac3: 5b                           	pop	ebx
 11b3ac4: 5d                           	pop	ebp
 11b3ac5: c2 28 00                     	ret	0x28
 11b3ac8: cc                           	int3
 11b3ac9: cc                           	int3
 11b3aca: cc                           	int3
 11b3acb: cc                           	int3
 11b3acc: cc                           	int3
 11b3acd: cc                           	int3
 11b3ace: cc                           	int3
 11b3acf: cc                           	int3
 11b3ad0: 55                           	push	ebp
 11b3ad1: 8b ec                        	mov	ebp, esp
 11b3ad3: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11b3ad6: 85 c0                        	test	eax, eax
 11b3ad8: 74 50                        	je	0x11b3b2a <.text+0x1da>
 11b3ada: 0f 57 c0                     	xorps	xmm0, xmm0
 11b3add: f3 0f 10 4d 18               	movss	xmm1, dword ptr [ebp + 0x18]
 11b3ae2: 56                           	push	esi
 11b3ae3: 8b 75 1c                     	mov	esi, dword ptr [ebp + 0x1c]
 11b3ae6: 8b 10                        	mov	edx, dword ptr [eax]
 11b3ae8: 8b 92 ac 00 00 00            	mov	edx, dword ptr [edx + 0xac]
 11b3aee: 6a 24                        	push	0x24
 11b3af0: 56                           	push	esi
 11b3af1: 8b 75 20                     	mov	esi, dword ptr [ebp + 0x20]
 11b3af4: 83 ec 14                     	sub	esp, 0x14
 11b3af7: f3 0f 11 44 24 10            	movss	dword ptr [esp + 0x10], xmm0
 11b3afd: f3 0f 11 44 24 0c            	movss	dword ptr [esp + 0xc], xmm0
 11b3b03: f3 0f 11 4c 24 08            	movss	dword ptr [esp + 0x8], xmm1
 11b3b09: f3 0f 10 4d 14               	movss	xmm1, dword ptr [ebp + 0x14]
 11b3b0e: f3 0f 11 4c 24 04            	movss	dword ptr [esp + 0x4], xmm1
 11b3b14: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b3b19: 6a 00                        	push	0x0
 11b3b1b: 56                           	push	esi
 11b3b1c: 51                           	push	ecx
 11b3b1d: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11b3b20: 51                           	push	ecx
 11b3b21: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b3b24: 51                           	push	ecx
 11b3b25: 8b c8                        	mov	ecx, eax
 11b3b27: ff d2                        	call	edx
 11b3b29: 5e                           	pop	esi
 11b3b2a: 5d                           	pop	ebp
 11b3b2b: c2 1c 00                     	ret	0x1c
 11b3b2e: cc                           	int3
 11b3b2f: cc                           	int3
 11b3b30: 55                           	push	ebp
 11b3b31: 8b ec                        	mov	ebp, esp
 11b3b33: 83 ec 0c                     	sub	esp, 0xc
 11b3b36: 89 4d f4                     	mov	dword ptr [ebp - 0xc], ecx
 11b3b39: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b3b3c: 8b 01                        	mov	eax, dword ptr [ecx]
 11b3b3e: 53                           	push	ebx
 11b3b3f: 8b 59 08                     	mov	ebx, dword ptr [ecx + 0x8]
 11b3b42: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 11b3b45: 3b c3                        	cmp	eax, ebx
 11b3b47: 0f 84 61 01 00 00            	je	0x11b3cae <.text+0x35e>
 11b3b4d: 8b 51 04                     	mov	edx, dword ptr [ecx + 0x4]
 11b3b50: 8b 49 0c                     	mov	ecx, dword ptr [ecx + 0xc]
 11b3b53: 89 4d f8                     	mov	dword ptr [ebp - 0x8], ecx
 11b3b56: 3b d1                        	cmp	edx, ecx
 11b3b58: 0f 84 50 01 00 00            	je	0x11b3cae <.text+0x35e>
 11b3b5e: 56                           	push	esi
 11b3b5f: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 11b3b62: 57                           	push	edi
 11b3b63: 8b 7e 08                     	mov	edi, dword ptr [esi + 0x8]
 11b3b66: 2b 3e                        	sub	edi, dword ptr [esi]
 11b3b68: 2b ca                        	sub	ecx, edx
 11b3b6a: 0f 57 c0                     	xorps	xmm0, xmm0
 11b3b6d: f3 0f 2a c7                  	cvtsi2ss	xmm0, edi
 11b3b71: 8b 7d 18                     	mov	edi, dword ptr [ebp + 0x18]
 11b3b74: 2b d8                        	sub	ebx, eax
 11b3b76: 0f 57 c9                     	xorps	xmm1, xmm1
 11b3b79: 89 4d 08                     	mov	dword ptr [ebp + 0x8], ecx
 11b3b7c: f3 0f 2a cb                  	cvtsi2ss	xmm1, ebx
 11b3b80: f3 0f 5e c8                  	divss	xmm1, xmm0
 11b3b84: 0f 57 c0                     	xorps	xmm0, xmm0
 11b3b87: f3 0f 2a c1                  	cvtsi2ss	xmm0, ecx
 11b3b8b: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
 11b3b8e: 2b 4e 04                     	sub	ecx, dword ptr [esi + 0x4]
 11b3b91: 0f 57 d2                     	xorps	xmm2, xmm2
 11b3b94: f3 0f 2a d1                  	cvtsi2ss	xmm2, ecx
 11b3b98: 0f b6 4d 18                  	movzx	ecx, byte ptr [ebp + 0x18]
 11b3b9c: c1 ef 10                     	shr	edi, 0x10
 11b3b9f: c1 e1 10                     	shl	ecx, 0x10
 11b3ba2: 81 e7 ff 00 00 00            	and	edi, 0xff
 11b3ba8: 0b f9                        	or	edi, ecx
 11b3baa: 80 7d 1c 00                  	cmp	byte ptr [ebp + 0x1c], 0x0
 11b3bae: 8b 4d 18                     	mov	ecx, dword ptr [ebp + 0x18]
 11b3bb1: f3 0f 5e c2                  	divss	xmm0, xmm2
 11b3bb5: f3 0f 11 0d 4c 58 b5 01      	movss	dword ptr [0x1b5584c], xmm1
 11b3bbd: f3 0f 11 05 48 58 b5 01      	movss	dword ptr [0x1b55848], xmm0
 11b3bc5: 74 08                        	je	0x11b3bcf <.text+0x27f>
 11b3bc7: 81 e1 00 ff 00 80            	and	ecx, 0x8000ff00
 11b3bcd: eb 06                        	jmp	0x11b3bd5 <.text+0x285>
 11b3bcf: 81 e1 00 ff 00 ff            	and	ecx, 0xff00ff00
 11b3bd5: 0b f9                        	or	edi, ecx
 11b3bd7: 8a 4d 24                     	mov	cl, byte ptr [ebp + 0x24]
 11b3bda: a3 44 58 b5 01               	mov	dword ptr [0x1b55844], eax
 11b3bdf: 89 15 40 58 b5 01            	mov	dword ptr [0x1b55840], edx
 11b3be5: f6 c1 02                     	test	cl, 0x2
 11b3be8: 74 0b                        	je	0x11b3bf5 <.text+0x2a5>
 11b3bea: 2b 45 fc                     	sub	eax, dword ptr [ebp - 0x4]
 11b3bed: 01 05 44 58 b5 01            	add	dword ptr [0x1b55844], eax
 11b3bf3: eb 0f                        	jmp	0x11b3c04 <.text+0x2b4>
 11b3bf5: f6 c1 04                     	test	cl, 0x4
 11b3bf8: 74 0d                        	je	0x11b3c07 <.text+0x2b7>
 11b3bfa: 8b c3                        	mov	eax, ebx
 11b3bfc: d1 f8                        	sar	eax
 11b3bfe: 29 05 44 58 b5 01            	sub	dword ptr [0x1b55844], eax
 11b3c04: 8a 4d 24                     	mov	cl, byte ptr [ebp + 0x24]
 11b3c07: f6 c1 10                     	test	cl, 0x10
 11b3c0a: 74 0b                        	je	0x11b3c17 <.text+0x2c7>
 11b3c0c: 2b 55 f8                     	sub	edx, dword ptr [ebp - 0x8]
 11b3c0f: 01 15 40 58 b5 01            	add	dword ptr [0x1b55840], edx
 11b3c15: eb 10                        	jmp	0x11b3c27 <.text+0x2d7>
 11b3c17: f6 c1 20                     	test	cl, 0x20
 11b3c1a: 74 0b                        	je	0x11b3c27 <.text+0x2d7>
 11b3c1c: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b3c1f: d1 f9                        	sar	ecx
 11b3c21: 29 0d 40 58 b5 01            	sub	dword ptr [0x1b55840], ecx
 11b3c27: 8a 45 20                     	mov	al, byte ptr [ebp + 0x20]
 11b3c2a: f3 0f 10 15 80 58 56 01      	movss	xmm2, dword ptr [0x1565880]
 11b3c32: a8 02                        	test	al, 0x2
 11b3c34: 74 11                        	je	0x11b3c47 <.text+0x2f7>
 11b3c36: 01 1d 44 58 b5 01            	add	dword ptr [0x1b55844], ebx
 11b3c3c: 0f 57 ca                     	xorps	xmm1, xmm2
 11b3c3f: f3 0f 11 0d 4c 58 b5 01      	movss	dword ptr [0x1b5584c], xmm1
 11b3c47: a8 01                        	test	al, 0x1
 11b3c49: 74 14                        	je	0x11b3c5f <.text+0x30f>
 11b3c4b: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11b3c4e: 01 15 40 58 b5 01            	add	dword ptr [0x1b55840], edx
 11b3c54: 0f 57 c2                     	xorps	xmm0, xmm2
 11b3c57: f3 0f 11 05 48 58 b5 01      	movss	dword ptr [0x1b55848], xmm0
 11b3c5f: 0f 57 d2                     	xorps	xmm2, xmm2
 11b3c62: 8b 55 10                     	mov	edx, dword ptr [ebp + 0x10]
 11b3c65: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11b3c68: 8b 01                        	mov	eax, dword ptr [ecx]
 11b3c6a: 8b 80 ac 00 00 00            	mov	eax, dword ptr [eax + 0xac]
 11b3c70: 6a 24                        	push	0x24
 11b3c72: 56                           	push	esi
 11b3c73: 83 ec 14                     	sub	esp, 0x14
 11b3c76: f3 0f 11 54 24 10            	movss	dword ptr [esp + 0x10], xmm2
 11b3c7c: f3 0f 11 54 24 0c            	movss	dword ptr [esp + 0xc], xmm2
 11b3c82: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11b3c88: f3 0f 10 45 14               	movss	xmm0, dword ptr [ebp + 0x14]
 11b3c8d: f3 0f 11 4c 24 04            	movss	dword ptr [esp + 0x4], xmm1
 11b3c93: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11b3c98: 6a 00                        	push	0x0
 11b3c9a: 57                           	push	edi
 11b3c9b: 52                           	push	edx
 11b3c9c: 8b 15 40 58 b5 01            	mov	edx, dword ptr [0x1b55840]
 11b3ca2: 52                           	push	edx
 11b3ca3: 8b 15 44 58 b5 01            	mov	edx, dword ptr [0x1b55844]
 11b3ca9: 52                           	push	edx
 11b3caa: ff d0                        	call	eax
 11b3cac: 5f                           	pop	edi
 11b3cad: 5e                           	pop	esi
 11b3cae: 5b                           	pop	ebx
 11b3caf: 8b e5                        	mov	esp, ebp
 11b3cb1: 5d                           	pop	ebp
 11b3cb2: c2 20 00                     	ret	0x20
 11b3cb5: cc                           	int3
 11b3cb6: cc                           	int3
 11b3cb7: cc                           	int3
 11b3cb8: cc                           	int3
 11b3cb9: cc                           	int3
 11b3cba: cc                           	int3
 11b3cbb: cc                           	int3
 11b3cbc: cc                           	int3
 11b3cbd: cc                           	int3
 11b3cbe: cc                           	int3
 11b3cbf: cc                           	int3
 11b3cc0: 55                           	push	ebp
 11b3cc1: 8b ec                        	mov	ebp, esp
 11b3cc3: 6a ff                        	push	-0x1
 11b3cc5: 68 38 7c 4c 01               	push	0x14c7c38
 11b3cca: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11b3cd0: 50                           	push	eax
 11b3cd1: 51                           	push	ecx
 11b3cd2: 56                           	push	esi
 11b3cd3: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11b3cd8: 33 c5                        	xor	eax, ebp
 11b3cda: 50                           	push	eax
 11b3cdb: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11b3cde: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11b3ce4: 8b f1                        	mov	esi, ecx
 11b3ce6: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
 11b3ce9: c7 06 0c 9e 85 01            	mov	dword ptr [esi], 0x1859e0c
 11b3cef: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11b3cf6: ff 15 b0 9e 85 01            	call	dword ptr [0x1859eb0]
 11b3cfc: 8b ce                        	mov	ecx, esi
 11b3cfe: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11b3d05: e8 46 87 01 00               	call	0x11cc450 <.text+0x18b00>
 11b3d0a: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11b3d0d: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11b3d14: 59                           	pop	ecx
 11b3d15: 5e                           	pop	esi
 11b3d16: 8b e5                        	mov	esp, ebp
 11b3d18: 5d                           	pop	ebp
 11b3d19: c3                           	ret
 11b3d1a: cc                           	int3
 11b3d1b: cc                           	int3
 11b3d1c: cc                           	int3
 11b3d1d: cc                           	int3
 11b3d1e: cc                           	int3
 11b3d1f: cc                           	int3
 11b3d20: c2 18 00                     	ret	0x18
 11b3d23: cc                           	int3
 11b3d24: cc                           	int3
 11b3d25: cc                           	int3
 11b3d26: cc                           	int3
 11b3d27: cc                           	int3
 11b3d28: cc                           	int3
 11b3d29: cc                           	int3
 11b3d2a: cc                           	int3
 11b3d2b: cc                           	int3
 11b3d2c: cc                           	int3
 11b3d2d: cc                           	int3
 11b3d2e: cc                           	int3
 11b3d2f: cc                           	int3
 11b3d30: 55                           	push	ebp
 11b3d31: 8b ec                        	mov	ebp, esp
 11b3d33: 66 8b 45 08                  	mov	ax, word ptr [ebp + 0x8]
 11b3d37: 66 8b 55 0c                  	mov	dx, word ptr [ebp + 0xc]
 11b3d3b: 66 89 41 20                  	mov	word ptr [ecx + 0x20], ax
 11b3d3f: 66                           	data16
