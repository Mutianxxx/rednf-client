
<stdin>:	file format elf32-i386

Disassembly of section .text:

0120ec70 <.text>:
 120ec70: 55                           	push	ebp
 120ec71: 8b ec                        	mov	ebp, esp
 120ec73: 81 ec 6c 03 00 00            	sub	esp, 0x36c
 120ec79: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 120ec7e: 33 c5                        	xor	eax, ebp
 120ec80: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 120ec83: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 120ec86: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
 120ec89: 53                           	push	ebx
 120ec8a: 56                           	push	esi
 120ec8b: 8b 75 20                     	mov	esi, dword ptr [ebp + 0x20]
 120ec8e: 8b d9                        	mov	ebx, ecx
 120ec90: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 120ec93: 57                           	push	edi
 120ec94: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 120ec97: 89 85 c8 fc ff ff            	mov	dword ptr [ebp - 0x338], eax
 120ec9d: 89 8d c4 fc ff ff            	mov	dword ptr [ebp - 0x33c], ecx
 120eca3: 89 95 c0 fc ff ff            	mov	dword ptr [ebp - 0x340], edx
 120eca9: e8 92 48 fe ff               	call	0x11f3540
 120ecae: 8b c8                        	mov	ecx, eax
 120ecb0: e8 7b 2e fe ff               	call	0x11f1b30
 120ecb5: 8b 43 08                     	mov	eax, dword ptr [ebx + 0x8]
 120ecb8: 85 c0                        	test	eax, eax
 120ecba: 0f 84 ff 1f 00 00            	je	0x1210cbf <.text+0x204f>
 120ecc0: 83 7b 0c 00                  	cmp	dword ptr [ebx + 0xc], 0x0
 120ecc4: 0f 84 f5 1f 00 00            	je	0x1210cbf <.text+0x204f>
 120ecca: 8b 08                        	mov	ecx, dword ptr [eax]
 120eccc: 68 00 20 00 00               	push	0x2000
 120ecd1: 8d 95 e8 fc ff ff            	lea	edx, [ebp - 0x318]
 120ecd7: 52                           	push	edx
 120ecd8: 68 80 02 00 00               	push	0x280
 120ecdd: 6a 00                        	push	0x0
 120ecdf: 50                           	push	eax
 120ece0: 8b 41 2c                     	mov	eax, dword ptr [ecx + 0x2c]
 120ece3: ff d0                        	call	eax
 120ece5: 89 43 04                     	mov	dword ptr [ebx + 0x4], eax
 120ece8: 85 c0                        	test	eax, eax
 120ecea: 0f 88 d4 1f 00 00            	js	0x1210cc4 <.text+0x2054>
 120ecf0: 8b 43 0c                     	mov	eax, dword ptr [ebx + 0xc]
 120ecf3: 8b 08                        	mov	ecx, dword ptr [eax]
 120ecf5: 68 00 20 00 00               	push	0x2000
 120ecfa: 8d 95 e4 fc ff ff            	lea	edx, [ebp - 0x31c]
 120ed00: 52                           	push	edx
 120ed01: 68 80 00 00 00               	push	0x80
 120ed06: 6a 00                        	push	0x0
 120ed08: 50                           	push	eax
 120ed09: 8b 41 2c                     	mov	eax, dword ptr [ecx + 0x2c]
 120ed0c: ff d0                        	call	eax
 120ed0e: 89 43 04                     	mov	dword ptr [ebx + 0x4], eax
 120ed11: 85 c0                        	test	eax, eax
 120ed13: 79 21                        	jns	0x120ed36 <.text+0xc6>
 120ed15: 8b 43 08                     	mov	eax, dword ptr [ebx + 0x8]
 120ed18: 8b 08                        	mov	ecx, dword ptr [eax]
 120ed1a: 8b 51 30                     	mov	edx, dword ptr [ecx + 0x30]
 120ed1d: 50                           	push	eax
 120ed1e: ff d2                        	call	edx
 120ed20: 8b 43 04                     	mov	eax, dword ptr [ebx + 0x4]
 120ed23: 5f                           	pop	edi
 120ed24: 5e                           	pop	esi
 120ed25: 5b                           	pop	ebx
 120ed26: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 120ed29: 33 cd                        	xor	ecx, ebp
 120ed2b: e8 a8 84 1c 00               	call	0x13d71d8 <.text+0x1c8568>
 120ed30: 8b e5                        	mov	esp, ebp
 120ed32: 5d                           	pop	ebp
 120ed33: c2 2c 00                     	ret	0x2c
 120ed36: 8b 85 c0 fc ff ff            	mov	eax, dword ptr [ebp - 0x340]
 120ed3c: 8b 08                        	mov	ecx, dword ptr [eax]
 120ed3e: 8d 95 ac fd ff ff            	lea	edx, [ebp - 0x254]
 120ed44: 52                           	push	edx
 120ed45: 6a 00                        	push	0x0
 120ed47: 50                           	push	eax
 120ed48: 8b 41 44                     	mov	eax, dword ptr [ecx + 0x44]
 120ed4b: ff d0                        	call	eax
 120ed4d: 8b 0e                        	mov	ecx, dword ptr [esi]
 120ed4f: 8b 45 1c                     	mov	eax, dword ptr [ebp + 0x1c]
 120ed52: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 120ed55: f3 0f 10 58 04               	movss	xmm3, dword ptr [eax + 0x4]
 120ed5a: f3 0f 10 7e 04               	movss	xmm7, dword ptr [esi + 0x4]
 120ed5f: 89 8d ac fc ff ff            	mov	dword ptr [ebp - 0x354], ecx
 120ed65: 8b 8d c8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x338]
 120ed6b: f3 0f 10 09                  	movss	xmm1, dword ptr [ecx]
 120ed6f: f3 0f 10 85 ac fc ff ff      	movss	xmm0, dword ptr [ebp - 0x354]
 120ed77: 0f 28 e0                     	movaps	xmm4, xmm0
 120ed7a: f3 0f 5c e1                  	subss	xmm4, xmm1
 120ed7e: f3 0f 11 8d 98 fc ff ff      	movss	dword ptr [ebp - 0x368], xmm1
 120ed86: f3 0f 10 08                  	movss	xmm1, dword ptr [eax]
 120ed8a: 0f 28 d1                     	movaps	xmm2, xmm1
 120ed8d: f3 0f 59 d4                  	mulss	xmm2, xmm4
 120ed91: f3 0f 5c c2                  	subss	xmm0, xmm2
 120ed95: f3 0f 58 07                  	addss	xmm0, dword ptr [edi]
 120ed99: 89 95 b0 fc ff ff            	mov	dword ptr [ebp - 0x350], edx
 120ed9f: 8b 95 c4 fc ff ff            	mov	edx, dword ptr [ebp - 0x33c]
 120eda5: 66 0f 6e 12                  	movd	xmm2, dword ptr [edx]
 120eda9: 0f 5b d2                     	cvtdq2ps	xmm2, xmm2
 120edac: f3 0f 5c c2                  	subss	xmm0, xmm2
 120edb0: f3 0f 10 95 b0 fc ff ff      	movss	xmm2, dword ptr [ebp - 0x350]
 120edb8: 0f 28 ea                     	movaps	xmm5, xmm2
 120edbb: f3 0f 5c 69 04               	subss	xmm5, dword ptr [ecx + 0x4]
 120edc0: 8b 8d c4 fd ff ff            	mov	ecx, dword ptr [ebp - 0x23c]
 120edc6: 0f 28 f3                     	movaps	xmm6, xmm3
 120edc9: f3 0f 59 f5                  	mulss	xmm6, xmm5
 120edcd: f3 0f 5c d6                  	subss	xmm2, xmm6
 120edd1: 66 0f 6e 72 04               	movd	xmm6, dword ptr [edx + 0x4]
 120edd6: f3 0f 58 57 04               	addss	xmm2, dword ptr [edi + 0x4]
 120eddb: 0f 5b f6                     	cvtdq2ps	xmm6, xmm6
 120edde: f3 0f 11 a5 d4 fc ff ff      	movss	dword ptr [ebp - 0x32c], xmm4
 120ede6: d9 85 d4 fc ff ff            	fld	dword ptr [ebp - 0x32c]
 120edec: f3 0f 5c d6                  	subss	xmm2, xmm6
 120edf0: f3 0f 10 36                  	movss	xmm6, dword ptr [esi]
 120edf4: f3 0f 11 8d d0 fc ff ff      	movss	dword ptr [ebp - 0x330], xmm1
 120edfc: 41                           	inc	ecx
 120edfd: f3 0f 11 ad dc fc ff ff      	movss	dword ptr [ebp - 0x324], xmm5
 120ee05: d9 85 dc fc ff ff            	fld	dword ptr [ebp - 0x324]
 120ee0b: f3 0f 11 b5 b0 fc ff ff      	movss	dword ptr [ebp - 0x350], xmm6
 120ee13: f3 0f 58 37                  	addss	xmm6, dword ptr [edi]
 120ee17: f3 0f 11 bd bc fc ff ff      	movss	dword ptr [ebp - 0x344], xmm7
 120ee1f: f3 0f 58 7f 04               	addss	xmm7, dword ptr [edi + 0x4]
 120ee24: f3 0f 59 cc                  	mulss	xmm1, xmm4
 120ee28: f3 0f 59 dd                  	mulss	xmm3, xmm5
 120ee2c: 89 8d d4 fc ff ff            	mov	dword ptr [ebp - 0x32c], ecx
 120ee32: db 85 d4 fc ff ff            	fild	dword ptr [ebp - 0x32c]
 120ee38: f3 0f 58 ce                  	addss	xmm1, xmm6
 120ee3c: f3 0f 58 df                  	addss	xmm3, xmm7
 120ee40: f3 0f 11 85 a0 fc ff ff      	movss	dword ptr [ebp - 0x360], xmm0
 120ee48: f3 0f 11 8d a8 fc ff ff      	movss	dword ptr [ebp - 0x358], xmm1
 120ee50: f3 0f 11 9d b8 fc ff ff      	movss	dword ptr [ebp - 0x348], xmm3
 120ee58: 79 06                        	jns	0x120ee60 <.text+0x1f0>
 120ee5a: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 120ee60: de fa                        	fdivp	st(2), st
 120ee62: 8b 8d c8 fd ff ff            	mov	ecx, dword ptr [ebp - 0x238]
 120ee68: 8d 51 02                     	lea	edx, [ecx + 0x2]
 120ee6b: 89 95 d4 fc ff ff            	mov	dword ptr [ebp - 0x32c], edx
 120ee71: d9 c9                        	fxch	st(1)
 120ee73: d9 9d e0 fc ff ff            	fstp	dword ptr [ebp - 0x320]
 120ee79: db 85 d4 fc ff ff            	fild	dword ptr [ebp - 0x32c]
 120ee7f: 85 d2                        	test	edx, edx
 120ee81: 79 06                        	jns	0x120ee89 <.text+0x219>
 120ee83: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 120ee89: f3 0f 2c 95 a0 fc ff ff      	cvttss2si	edx, dword ptr [ebp - 0x360]
 120ee91: de f9                        	fdivp	st(1), st
 120ee93: f3 0f 10 05 84 21 56 01      	movss	xmm0, dword ptr [0x1562184]
 120ee9b: 0f 57 e4                     	xorps	xmm4, xmm4
 120ee9e: f3 0f 2a e2                  	cvtsi2ss	xmm4, edx
 120eea2: f3 0f 2c d2                  	cvttss2si	edx, xmm2
 120eea6: 0f 57 d2                     	xorps	xmm2, xmm2
 120eea9: f3 0f 2a d2                  	cvtsi2ss	xmm2, edx
 120eead: f3 0f 2c d6                  	cvttss2si	edx, xmm6
 120eeb1: 0f 57 c9                     	xorps	xmm1, xmm1
 120eeb4: f3 0f 2a ca                  	cvtsi2ss	xmm1, edx
 120eeb8: f3 0f 2c d7                  	cvttss2si	edx, xmm7
 120eebc: f3 0f 10 3d fc 20 56 01      	movss	xmm7, dword ptr [0x15620fc]
 120eec4: 0f 57 db                     	xorps	xmm3, xmm3
 120eec7: f3 0f 2a da                  	cvtsi2ss	xmm3, edx
 120eecb: f3 0f 2c 95 a8 fc ff ff      	cvttss2si	edx, dword ptr [ebp - 0x358]
 120eed3: 0f 57 ed                     	xorps	xmm5, xmm5
 120eed6: f3 0f 2a ea                  	cvtsi2ss	xmm5, edx
 120eeda: f3 0f 2c 95 b8 fc ff ff      	cvttss2si	edx, dword ptr [ebp - 0x348]
 120eee2: 0f 57 f6                     	xorps	xmm6, xmm6
 120eee5: f3 0f 2a f2                  	cvtsi2ss	xmm6, edx
 120eee9: 8b 55 30                     	mov	edx, dword ptr [ebp + 0x30]
 120eeec: f3 0f 5c c8                  	subss	xmm1, xmm0
 120eef0: f3 0f 5c d8                  	subss	xmm3, xmm0
 120eef4: f3 0f 5c e0                  	subss	xmm4, xmm0
 120eef8: f3 0f 5c d0                  	subss	xmm2, xmm0
 120eefc: f3 0f 11 8d d4 fc ff ff      	movss	dword ptr [ebp - 0x32c], xmm1
 120ef04: f3 0f 11 9d dc fc ff ff      	movss	dword ptr [ebp - 0x324], xmm3
 120ef0c: f3 0f 5c e8                  	subss	xmm5, xmm0
 120ef10: f3 0f 5c f0                  	subss	xmm6, xmm0
 120ef14: d9 9d d8 fc ff ff            	fstp	dword ptr [ebp - 0x328]
 120ef1a: 85 d2                        	test	edx, edx
 120ef1c: 0f 85 81 01 00 00            	jne	0x120f0a3 <.text+0x433>
 120ef22: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120ef28: f3 0f 11 20                  	movss	dword ptr [eax], xmm4
 120ef2c: 8b 8d e8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x318]
 120ef32: 0f 57 c0                     	xorps	xmm0, xmm0
 120ef35: f3 0f 11 59 04               	movss	dword ptr [ecx + 0x4], xmm3
 120ef3a: 8b 95 e8 fc ff ff            	mov	edx, dword ptr [ebp - 0x318]
 120ef40: f3 0f 11 42 0c               	movss	dword ptr [edx + 0xc], xmm0
 120ef45: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120ef4b: f3 0f 10 ad d8 fc ff ff      	movss	xmm5, dword ptr [ebp - 0x328]
 120ef53: f3 0f 11 68 10               	movss	dword ptr [eax + 0x10], xmm5
 120ef58: 8b 8d e8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x318]
 120ef5e: f3 0f 11 41 08               	movss	dword ptr [ecx + 0x8], xmm0
 120ef63: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120ef69: 83 c0 14                     	add	eax, 0x14
 120ef6c: 89 85 e8 fc ff ff            	mov	dword ptr [ebp - 0x318], eax
 120ef72: f3 0f 11 20                  	movss	dword ptr [eax], xmm4
 120ef76: 8b 95 e8 fc ff ff            	mov	edx, dword ptr [ebp - 0x318]
 120ef7c: f3 0f 11 52 04               	movss	dword ptr [edx + 0x4], xmm2
 120ef81: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120ef87: f3 0f 11 40 0c               	movss	dword ptr [eax + 0xc], xmm0
 120ef8c: 8b 8d e8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x318]
 120ef92: f3 0f 11 41 10               	movss	dword ptr [ecx + 0x10], xmm0
 120ef97: 8b 95 e8 fc ff ff            	mov	edx, dword ptr [ebp - 0x318]
 120ef9d: f3 0f 11 42 08               	movss	dword ptr [edx + 0x8], xmm0
 120efa2: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120efa8: 83 c0 14                     	add	eax, 0x14
 120efab: 89 85 e8 fc ff ff            	mov	dword ptr [ebp - 0x318], eax
 120efb1: f3 0f 11 08                  	movss	dword ptr [eax], xmm1
 120efb5: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120efbb: f3 0f 11 58 04               	movss	dword ptr [eax + 0x4], xmm3
 120efc0: 8b 8d e8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x318]
 120efc6: f3 0f 10 9d e0 fc ff ff      	movss	xmm3, dword ptr [ebp - 0x320]
 120efce: f3 0f 11 59 0c               	movss	dword ptr [ecx + 0xc], xmm3
 120efd3: 8b 95 e8 fc ff ff            	mov	edx, dword ptr [ebp - 0x318]
 120efd9: f3 0f 11 6a 10               	movss	dword ptr [edx + 0x10], xmm5
 120efde: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120efe4: f3 0f 11 40 08               	movss	dword ptr [eax + 0x8], xmm0
 120efe9: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120efef: 83 c0 14                     	add	eax, 0x14
 120eff2: 89 85 e8 fc ff ff            	mov	dword ptr [ebp - 0x318], eax
 120eff8: f3 0f 11 08                  	movss	dword ptr [eax], xmm1
 120effc: 8b 8d e8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x318]
 120f002: f3 0f 11 51 04               	movss	dword ptr [ecx + 0x4], xmm2
 120f007: 8b 95 e8 fc ff ff            	mov	edx, dword ptr [ebp - 0x318]
 120f00d: f3 0f 11 5a 0c               	movss	dword ptr [edx + 0xc], xmm3
 120f012: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120f018: f3 0f 11 40 10               	movss	dword ptr [eax + 0x10], xmm0
 120f01d: 8b 8d e8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x318]
 120f023: f3 0f 11 41 08               	movss	dword ptr [ecx + 0x8], xmm0
 120f028: 8b 85 e4 fc ff ff            	mov	eax, dword ptr [ebp - 0x31c]
 120f02e: 83 85 e8 fc ff ff 14         	add	dword ptr [ebp - 0x318], 0x14
 120f035: 33 d2                        	xor	edx, edx
 120f037: 66 89 10                     	mov	word ptr [eax], dx
 120f03a: 8b 85 e4 fc ff ff            	mov	eax, dword ptr [ebp - 0x31c]
 120f040: b9 02 00 00 00               	mov	ecx, 0x2
 120f045: 03 c1                        	add	eax, ecx
 120f047: 89 85 e4 fc ff ff            	mov	dword ptr [ebp - 0x31c], eax
 120f04d: ba 01 00 00 00               	mov	edx, 0x1
 120f052: 66 89 10                     	mov	word ptr [eax], dx
 120f055: 8b 85 e4 fc ff ff            	mov	eax, dword ptr [ebp - 0x31c]
 120f05b: 03 c1                        	add	eax, ecx
 120f05d: 89 85 e4 fc ff ff            	mov	dword ptr [ebp - 0x31c], eax
 120f063: 8b d1                        	mov	edx, ecx
 120f065: 66 89 10                     	mov	word ptr [eax], dx
 120f068: 8b 85 e4 fc ff ff            	mov	eax, dword ptr [ebp - 0x31c]
 120f06e: 03 c1                        	add	eax, ecx
 120f070: 89 85 e4 fc ff ff            	mov	dword ptr [ebp - 0x31c], eax
 120f076: ba 03 00 00 00               	mov	edx, 0x3
 120f07b: 66 89 10                     	mov	word ptr [eax], dx
 120f07e: 01 8d e4 fc ff ff            	add	dword ptr [ebp - 0x31c], ecx
 120f084: c7 85 d8 fc ff ff 04 00 00 00	mov	dword ptr [ebp - 0x328], 0x4
 120f08e: 89 8d dc fc ff ff            	mov	dword ptr [ebp - 0x324], ecx
 120f094: c7 85 e0 fc ff ff 05 00 00 00	mov	dword ptr [ebp - 0x320], 0x5
 120f09e: e9 2c 12 00 00               	jmp	0x12102cf <.text+0x165f>
 120f0a3: 83 fa 03                     	cmp	edx, 0x3
 120f0a6: 0f 85 90 03 00 00            	jne	0x120f43c <.text+0x7cc>
 120f0ac: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120f0b2: f3 0f 11 20                  	movss	dword ptr [eax], xmm4
 120f0b6: 8b 8d e8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x318]
 120f0bc: 0f 57 c0                     	xorps	xmm0, xmm0
 120f0bf: f3 0f 11 71 04               	movss	dword ptr [ecx + 0x4], xmm6
 120f0c4: 8b 95 e8 fc ff ff            	mov	edx, dword ptr [ebp - 0x318]
 120f0ca: f3 0f 11 42 0c               	movss	dword ptr [edx + 0xc], xmm0
 120f0cf: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120f0d5: f3 0f 11 40 10               	movss	dword ptr [eax + 0x10], xmm0
 120f0da: 8b 8d e8 fc ff ff            	mov	ecx, dword ptr [ebp - 0x318]
 120f0e0: f3 0f 11 41 08               	movss	dword ptr [ecx + 0x8], xmm0
 120f0e5: 8b 85 e8 fc ff ff            	mov	eax, dword ptr [ebp - 0x318]
 120f0eb: f3 0f 10 bd                  	<unknown>
 120f0ef: d8                           	<unknown>
