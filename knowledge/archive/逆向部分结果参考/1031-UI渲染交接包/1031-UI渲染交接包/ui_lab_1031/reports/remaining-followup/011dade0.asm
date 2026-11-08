
<stdin>:	file format elf32-i386

Disassembly of section .text:

011dade0 <.text>:
 11dade0: 55                           	push	ebp
 11dade1: 8b ec                        	mov	ebp, esp
 11dade3: 83 ec 3c                     	sub	esp, 0x3c
 11dade6: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11dadeb: 33 c5                        	xor	eax, ebp
 11daded: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11dadf0: 53                           	push	ebx
 11dadf1: 56                           	push	esi
 11dadf2: 8b 75 10                     	mov	esi, dword ptr [ebp + 0x10]
 11dadf5: 8b d9                        	mov	ebx, ecx
 11dadf7: 89 5d d8                     	mov	dword ptr [ebp - 0x28], ebx
 11dadfa: 89 75 e8                     	mov	dword ptr [ebp - 0x18], esi
 11dadfd: e8 6e fd ff ff               	call	0x11dab70
 11dae02: 84 c0                        	test	al, al
 11dae04: 0f 84 d8 02 00 00            	je	0x11db0e2 <.text+0x302>
 11dae0a: 8b ce                        	mov	ecx, esi
 11dae0c: e8 5f fd ff ff               	call	0x11dab70
 11dae11: 84 c0                        	test	al, al
 11dae13: 0f 84 c9 02 00 00            	je	0x11db0e2 <.text+0x302>
 11dae19: 57                           	push	edi
 11dae1a: 6a 04                        	push	0x4
 11dae1c: e8 af ed fd ff               	call	0x11b9bd0
 11dae21: 83 c4 04                     	add	esp, 0x4
 11dae24: 8b ce                        	mov	ecx, esi
 11dae26: e8 55 e2 3d ff               	call	0x5b9080
 11dae2b: 8b cb                        	mov	ecx, ebx
 11dae2d: 89 45 dc                     	mov	dword ptr [ebp - 0x24], eax
 11dae30: e8 6b 8f fd ff               	call	0x11b3da0
 11dae35: 8b cb                        	mov	ecx, ebx
 11dae37: 8b f0                        	mov	esi, eax
 11dae39: e8 72 8f fd ff               	call	0x11b3db0
 11dae3e: 03 75 08                     	add	esi, dword ptr [ebp + 0x8]
 11dae41: 8b f8                        	mov	edi, eax
 11dae43: 8b cb                        	mov	ecx, ebx
 11dae45: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
 11dae48: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
 11dae4b: e8 30 8f fd ff               	call	0x11b3d80
 11dae50: 03 45 ec                     	add	eax, dword ptr [ebp - 0x14]
 11dae53: 03 7d 0c                     	add	edi, dword ptr [ebp + 0xc]
 11dae56: 8b cb                        	mov	ecx, ebx
 11dae58: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
 11dae5b: 89 7d f0                     	mov	dword ptr [ebp - 0x10], edi
 11dae5e: e8 2d 8f fd ff               	call	0x11b3d90
 11dae63: 03 45 e4                     	add	eax, dword ptr [ebp - 0x1c]
 11dae66: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
 11dae69: 03 45 0c                     	add	eax, dword ptr [ebp + 0xc]
 11dae6c: 89 45 f8                     	mov	dword ptr [ebp - 0x8], eax
 11dae6f: e8 1c 88 fd ff               	call	0x11b3690
 11dae74: 50                           	push	eax
 11dae75: 8d 55 ec                     	lea	edx, [ebp - 0x14]
 11dae78: 52                           	push	edx
 11dae79: 8b c2                        	mov	eax, edx
 11dae7b: 50                           	push	eax
 11dae7c: ff 15 74 a4 55 01            	call	dword ptr [0x155a474]
 11dae82: 85 c0                        	test	eax, eax
 11dae84: 0f 84 57 02 00 00            	je	0x11db0e1 <.text+0x301>
 11dae8a: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
 11dae8d: 8b 55 f0                     	mov	edx, dword ptr [ebp - 0x10]
 11dae90: f7 df                        	neg	edi
 11dae92: 57                           	push	edi
 11dae93: f7 de                        	neg	esi
 11dae95: 56                           	push	esi
 11dae96: 8d 45 ec                     	lea	eax, [ebp - 0x14]
 11dae99: 50                           	push	eax
 11dae9a: 89 4d d0                     	mov	dword ptr [ebp - 0x30], ecx
 11dae9d: 89 55 d4                     	mov	dword ptr [ebp - 0x2c], edx
 11daea0: ff 15 cc a4 55 01            	call	dword ptr [0x155a4cc]
 11daea6: 8b 45 dc                     	mov	eax, dword ptr [ebp - 0x24]
 11daea9: 83 f8 0e                     	cmp	eax, 0xe
 11daeac: 74 30                        	je	0x11daede <.text+0xfe>
 11daeae: 83 f8 0f                     	cmp	eax, 0xf
 11daeb1: 74 2b                        	je	0x11daede <.text+0xfe>
 11daeb3: 8b 0d fc 6f b5 01            	mov	ecx, dword ptr [0x1b56ffc]
 11daeb9: e8 22 68 fd ff               	call	0x11b16e0
 11daebe: 8b 08                        	mov	ecx, dword ptr [eax]
 11daec0: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 11daec3: 52                           	push	edx
 11daec4: 8b 55 e8                     	mov	edx, dword ptr [ebp - 0x18]
 11daec7: 8b 52 60                     	mov	edx, dword ptr [edx + 0x60]
 11daeca: 52                           	push	edx
 11daecb: 8d 55 ec                     	lea	edx, [ebp - 0x14]
 11daece: 52                           	push	edx
 11daecf: 8b 53 60                     	mov	edx, dword ptr [ebx + 0x60]
 11daed2: 52                           	push	edx
 11daed3: 50                           	push	eax
 11daed4: 8b 41 78                     	mov	eax, dword ptr [ecx + 0x78]
 11daed7: ff d0                        	call	eax
 11daed9: e9 f7 01 00 00               	jmp	0x11db0d5 <.text+0x2f5>
 11daede: 8b 13                        	mov	edx, dword ptr [ebx]
 11daee0: 8b 82 9c 00 00 00            	mov	eax, dword ptr [edx + 0x9c]
 11daee6: 8b cb                        	mov	ecx, ebx
 11daee8: ff d0                        	call	eax
 11daeea: 84 c0                        	test	al, al
 11daeec: 0f 84 ef 01 00 00            	je	0x11db0e1 <.text+0x301>
 11daef2: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
 11daef5: e8 76 8e fd ff               	call	0x11b3d70
 11daefa: 8b f0                        	mov	esi, eax
 11daefc: 8b cb                        	mov	ecx, ebx
 11daefe: 89 75 c8                     	mov	dword ptr [ebp - 0x38], esi
 11daf01: e8 6a 8e fd ff               	call	0x11b3d70
 11daf06: 89 45 cc                     	mov	dword ptr [ebp - 0x34], eax
 11daf09: 85 f6                        	test	esi, esi
 11daf0b: 0f 84 c4 01 00 00            	je	0x11db0d5 <.text+0x2f5>
 11daf11: 85 c0                        	test	eax, eax
 11daf13: 0f 84 bc 01 00 00            	je	0x11db0d5 <.text+0x2f5>
 11daf19: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 11daf1c: 2b 4d f0                     	sub	ecx, dword ptr [ebp - 0x10]
 11daf1f: 33 ff                        	xor	edi, edi
 11daf21: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
 11daf24: 85 c9                        	test	ecx, ecx
 11daf26: 0f 8e 9c 01 00 00            	jle	0x11db0c8 <.text+0x2e8>
 11daf2c: eb 05                        	jmp	0x11daf33 <.text+0x153>
 11daf2e: 8b ff                        	mov	edi, edi
 11daf30: 8b 75 c8                     	mov	esi, dword ptr [ebp - 0x38]
 11daf33: 8b cb                        	mov	ecx, ebx
 11daf35: e8 46 e1 3d ff               	call	0x5b9080
 11daf3a: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
 11daf3d: 83 f8 10                     	cmp	eax, 0x10
 11daf40: 0f 85 e6 00 00 00            	jne	0x11db02c <.text+0x24c>
 11daf46: e8 25 d9 fc ff               	call	0x11a8870
 11daf4b: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
 11daf4e: 8d 0c 17                     	lea	ecx, [edi + edx]
 11daf51: 8b 16                        	mov	edx, dword ptr [esi]
 11daf53: 0f af c1                     	imul	eax, ecx
 11daf56: d1 e8                        	shr	eax
 11daf58: 8b cb                        	mov	ecx, ebx
 11daf5a: 8d 34 42                     	lea	esi, [edx + 2*eax]
 11daf5d: e8 0e d9 fc ff               	call	0x11a8870
 11daf62: 03 7d f0                     	add	edi, dword ptr [ebp - 0x10]
 11daf65: 8b 55 cc                     	mov	edx, dword ptr [ebp - 0x34]
 11daf68: 8b 0a                        	mov	ecx, dword ptr [edx]
 11daf6a: 0f af c7                     	imul	eax, edi
 11daf6d: c1 e8 02                     	shr	eax, 0x2
 11daf70: 8d 14 81                     	lea	edx, [ecx + 4*eax]
 11daf73: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
 11daf76: 89 55 e0                     	mov	dword ptr [ebp - 0x20], edx
 11daf79: 8b 55 f4                     	mov	edx, dword ptr [ebp - 0xc]
 11daf7c: 2b d0                        	sub	edx, eax
 11daf7e: 33 c9                        	xor	ecx, ecx
 11daf80: 85 d2                        	test	edx, edx
 11daf82: 0f 8e 2b 01 00 00            	jle	0x11db0b3 <.text+0x2d3>
 11daf88: 8b 55 e0                     	mov	edx, dword ptr [ebp - 0x20]
 11daf8b: 03 c1                        	add	eax, ecx
 11daf8d: 8d 14 82                     	lea	edx, [edx + 4*eax]
 11daf90: 8b 45 dc                     	mov	eax, dword ptr [ebp - 0x24]
 11daf93: 83 f8 0e                     	cmp	eax, 0xe
 11daf96: 75 39                        	jne	0x11dafd1 <.text+0x1f1>
 11daf98: 8b 02                        	mov	eax, dword ptr [edx]
 11daf9a: 3d 00 00 00 80               	cmp	eax, 0x80000000
 11daf9f: 72 75                        	jb	0x11db016 <.text+0x236>
 11dafa1: 8b f8                        	mov	edi, eax
 11dafa3: 8b d8                        	mov	ebx, eax
 11dafa5: c1 ef 06                     	shr	edi, 0x6
 11dafa8: c1 eb 13                     	shr	ebx, 0x13
 11dafab: c1 e8 10                     	shr	eax, 0x10
 11dafae: 81 e7 e0 03 00 00            	and	edi, 0x3e0
 11dafb4: 83 e3 1f                     	and	ebx, 0x1f
 11dafb7: 25 00 80 00 00               	and	eax, 0x8000
 11dafbc: 0b fb                        	or	edi, ebx
 11dafbe: 0b f8                        	or	edi, eax
 11dafc0: 66 8b 02                     	mov	ax, word ptr [edx]
 11dafc3: ba f8 00 00 00               	mov	edx, 0xf8
 11dafc8: 66 23 c2                     	and	ax, dx
 11dafcb: 66 c1 e0 07                  	shl	ax, 0x7
 11dafcf: eb 35                        	jmp	0x11db006 <.text+0x226>
 11dafd1: 83 f8 0f                     	cmp	eax, 0xf
 11dafd4: 75 40                        	jne	0x11db016 <.text+0x236>
 11dafd6: 8b 02                        	mov	eax, dword ptr [edx]
 11dafd8: 8b f8                        	mov	edi, eax
 11dafda: 8b d8                        	mov	ebx, eax
 11dafdc: c1 ef 08                     	shr	edi, 0x8
 11dafdf: c1 eb 14                     	shr	ebx, 0x14
 11dafe2: c1 e8 10                     	shr	eax, 0x10
 11dafe5: 81 e7 f0 00 00 00            	and	edi, 0xf0
 11dafeb: 83 e3 0f                     	and	ebx, 0xf
 11dafee: 25 00 f0 00 00               	and	eax, 0xf000
 11daff3: 0b fb                        	or	edi, ebx
 11daff5: 0b f8                        	or	edi, eax
 11daff7: 66 8b 02                     	mov	ax, word ptr [edx]
 11daffa: ba f0 00 00 00               	mov	edx, 0xf0
 11dafff: 66 23 c2                     	and	ax, dx
 11db002: 66 c1 e0 04                  	shl	ax, 0x4
 11db006: 8b 5d d8                     	mov	ebx, dword ptr [ebp - 0x28]
 11db009: 66 0b f8                     	or	di, ax
 11db00c: 8b 45 d0                     	mov	eax, dword ptr [ebp - 0x30]
 11db00f: 8d 14 01                     	lea	edx, [ecx + eax]
 11db012: 66 89 3c 56                  	mov	word ptr [esi + 2*edx], di
 11db016: 8b 55 f4                     	mov	edx, dword ptr [ebp - 0xc]
 11db019: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
 11db01c: 41                           	inc	ecx
 11db01d: 2b d0                        	sub	edx, eax
 11db01f: 3b ca                        	cmp	ecx, edx
 11db021: 0f 8c 61 ff ff ff            	jl	0x11daf88 <.text+0x1a8>
 11db027: e9 87 00 00 00               	jmp	0x11db0b3 <.text+0x2d3>
 11db02c: e8 3f d8 fc ff               	call	0x11a8870
 11db031: 8b 4d d4                     	mov	ecx, dword ptr [ebp - 0x2c]
 11db034: 8d 14 0f                     	lea	edx, [edi + ecx]
 11db037: 8b 0e                        	mov	ecx, dword ptr [esi]
 11db039: 0f af c2                     	imul	eax, edx
 11db03c: d1 e8                        	shr	eax
 11db03e: 8d 14 41                     	lea	edx, [ecx + 2*eax]
 11db041: 8b cb                        	mov	ecx, ebx
 11db043: 89 55 c4                     	mov	dword ptr [ebp - 0x3c], edx
 11db046: e8 25 d8 fc ff               	call	0x11a8870
 11db04b: 03 7d f0                     	add	edi, dword ptr [ebp - 0x10]
 11db04e: 8b 55 cc                     	mov	edx, dword ptr [ebp - 0x34]
 11db051: 8b 0a                        	mov	ecx, dword ptr [edx]
 11db053: 0f af c7                     	imul	eax, edi
 11db056: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
 11db059: d1 e8                        	shr	eax
 11db05b: 8d 14 41                     	lea	edx, [ecx + 2*eax]
 11db05e: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11db061: 2b cf                        	sub	ecx, edi
 11db063: 33 c0                        	xor	eax, eax
 11db065: 89 55 e0                     	mov	dword ptr [ebp - 0x20], edx
 11db068: 85 c9                        	test	ecx, ecx
 11db06a: 7e 47                        	jle	0x11db0b3 <.text+0x2d3>
 11db06c: 8b 55 dc                     	mov	edx, dword ptr [ebp - 0x24]
 11db06f: 83 ea 0e                     	sub	edx, 0xe
 11db072: f7 da                        	neg	edx
 11db074: 1b d2                        	sbb	edx, edx
 11db076: 83 e2 fd                     	and	edx, -0x3
 11db079: 83 c2 0f                     	add	edx, 0xf
 11db07c: 8d 64 24 00                  	lea	esp, [esp]
 11db080: 8b 75 e0                     	mov	esi, dword ptr [ebp - 0x20]
 11db083: 8d 0c 38                     	lea	ecx, [eax + edi]
 11db086: 0f b7 34 4e                  	movzx	esi, word ptr [esi + 2*ecx]
 11db08a: 8b de                        	mov	ebx, esi
 11db08c: 66 8b ca                     	mov	cx, dx
 11db08f: 66 d3 eb                     	shr	bx, cl
 11db092: 66 85 db                     	test	bx, bx
 11db095: 74 0f                        	je	0x11db0a6 <.text+0x2c6>
 11db097: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
 11db09a: 8b 7d c4                     	mov	edi, dword ptr [ebp - 0x3c]
 11db09d: 03 c8                        	add	ecx, eax
 11db09f: 66 89 34 4f                  	mov	word ptr [edi + 2*ecx], si
 11db0a3: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
 11db0a6: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11db0a9: 40                           	inc	eax
 11db0aa: 2b cf                        	sub	ecx, edi
 11db0ac: 3b c1                        	cmp	eax, ecx
 11db0ae: 7c d0                        	jl	0x11db080 <.text+0x2a0>
 11db0b0: 8b 5d d8                     	mov	ebx, dword ptr [ebp - 0x28]
 11db0b3: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
 11db0b6: 8b 55 f8                     	mov	edx, dword ptr [ebp - 0x8]
 11db0b9: 2b 55 f0                     	sub	edx, dword ptr [ebp - 0x10]
 11db0bc: 47                           	inc	edi
 11db0bd: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
 11db0c0: 3b fa                        	cmp	edi, edx
 11db0c2: 0f 8c 68 fe ff ff            	jl	0x11daf30 <.text+0x150>
 11db0c8: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
 11db0cb: 8b 01                        	mov	eax, dword ptr [ecx]
 11db0cd: 8b 90 94 00 00 00            	mov	edx, dword ptr [eax + 0x94]
 11db0d3: ff d2                        	call	edx
 11db0d5: 6a 00                        	push	0x0
 11db0d7: 6a 04                        	push	0x4
 11db0d9: e8 42 eb fd ff               	call	0x11b9c20
 11db0de: 83 c4 08                     	add	esp, 0x8
 11db0e1: 5f                           	pop	edi
 11db0e2: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11db0e5: 5e                           	pop	esi
 11db0e6: 33 cd                        	xor	ecx, ebp
 11db0e8: 5b                           	pop	ebx
 11db0e9: e8 ea c0 1f 00               	call	0x13d71d8 <.text+0x1fc3f8>
 11db0ee: 8b e5                        	mov	esp, ebp
 11db0f0: 5d                           	pop	ebp
 11db0f1: c2 0c 00                     	ret	0xc
