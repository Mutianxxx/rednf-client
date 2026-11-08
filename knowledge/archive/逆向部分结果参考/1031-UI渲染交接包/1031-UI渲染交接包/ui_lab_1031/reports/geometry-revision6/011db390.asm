
<stdin>:	file format elf32-i386

Disassembly of section .text:

011db390 <.text>:
 11db390: 55                           	push	ebp
 11db391: 8b ec                        	mov	ebp, esp
 11db393: 83 ec 20                     	sub	esp, 0x20
 11db396: 83 7d 1c 00                  	cmp	dword ptr [ebp + 0x1c], 0x0
 11db39a: 56                           	push	esi
 11db39b: 8b f1                        	mov	esi, ecx
 11db39d: 75 5a                        	jne	0x11db3f9 <.text+0x69>
 11db39f: f3 0f 10 4d 24               	movss	xmm1, dword ptr [ebp + 0x24]
 11db3a4: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11db3ac: 0f 2e c8                     	ucomiss	xmm1, xmm0
 11db3af: 9f                           	lahf
 11db3b0: f6 c4 44                     	test	ah, 0x44
 11db3b3: 7a 12                        	jp	0x11db3c7 <.text+0x37>
 11db3b5: f3 0f 10 4d 28               	movss	xmm1, dword ptr [ebp + 0x28]
 11db3ba: 0f 2e c8                     	ucomiss	xmm1, xmm0
 11db3bd: 9f                           	lahf
 11db3be: f6 c4 44                     	test	ah, 0x44
 11db3c1: 7a 04                        	jp	0x11db3c7 <.text+0x37>
 11db3c3: 32 c0                        	xor	al, al
 11db3c5: eb 05                        	jmp	0x11db3cc <.text+0x3c>
 11db3c7: b8 01 00 00 00               	mov	eax, 0x1
 11db3cc: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11db3cf: 8b 76 5c                     	mov	esi, dword ptr [esi + 0x5c]
 11db3d2: 50                           	push	eax
 11db3d3: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11db3d6: 50                           	push	eax
 11db3d7: 51                           	push	ecx
 11db3d8: 8b 4d 14                     	mov	ecx, dword ptr [ebp + 0x14]
 11db3db: e8 a0 82 fd ff               	call	0x11b3680
 11db3e0: 8b 55 34                     	mov	edx, dword ptr [ebp + 0x34]
 11db3e3: 50                           	push	eax
 11db3e4: 52                           	push	edx
 11db3e5: 56                           	push	esi
 11db3e6: e8 55 81 01 00               	call	0x11f3540 <.text+0x181b0>
 11db3eb: 8b c8                        	mov	ecx, eax
 11db3ed: e8 6e 70 01 00               	call	0x11f2460 <.text+0x170d0>
 11db3f2: 5e                           	pop	esi
 11db3f3: 8b e5                        	mov	esp, ebp
 11db3f5: 5d                           	pop	ebp
 11db3f6: c2 34 00                     	ret	0x34
 11db3f9: e8 a2 79 fd ff               	call	0x11b2da0
 11db3fe: 8b c8                        	mov	ecx, eax
 11db400: e8 ab 62 fd ff               	call	0x11b16b0
 11db405: 84 c0                        	test	al, al
 11db407: 0f 85 ed 00 00 00            	jne	0x11db4fa <.text+0x16a>
 11db40d: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
 11db410: 50                           	push	eax
 11db411: e8 8a 79 fd ff               	call	0x11b2da0
 11db416: 8b c8                        	mov	ecx, eax
 11db418: e8 c3 62 fd ff               	call	0x11b16e0
 11db41d: 50                           	push	eax
 11db41e: e8 5d f1 ff ff               	call	0x11da580
 11db423: 83 c4 08                     	add	esp, 0x8
 11db426: e8 15 81 01 00               	call	0x11f3540 <.text+0x181b0>
 11db42b: 8b c8                        	mov	ecx, eax
 11db42d: e8 de 62 01 00               	call	0x11f1710 <.text+0x16380>
 11db432: 84 c0                        	test	al, al
 11db434: 74 0c                        	je	0x11db442 <.text+0xb2>
 11db436: e8 05 81 01 00               	call	0x11f3540 <.text+0x181b0>
 11db43b: 8b c8                        	mov	ecx, eax
 11db43d: e8 fe 66 01 00               	call	0x11f1b40 <.text+0x167b0>
 11db442: f3 0f 10 45 2c               	movss	xmm0, dword ptr [ebp + 0x2c]
 11db447: f3 0f 11 45 f8               	movss	dword ptr [ebp - 0x8], xmm0
 11db44c: f3 0f 10 45 30               	movss	xmm0, dword ptr [ebp + 0x30]
 11db451: f3 0f 11 45 fc               	movss	dword ptr [ebp - 0x4], xmm0
 11db456: f3 0f 10 45 24               	movss	xmm0, dword ptr [ebp + 0x24]
 11db45b: 53                           	push	ebx
 11db45c: f3 0f 11 45 f0               	movss	dword ptr [ebp - 0x10], xmm0
 11db461: f3 0f 10 45 28               	movss	xmm0, dword ptr [ebp + 0x28]
 11db466: 57                           	push	edi
 11db467: 8b 7e 5c                     	mov	edi, dword ptr [esi + 0x5c]
 11db46a: 8b ce                        	mov	ecx, esi
 11db46c: f3 0f 11 45 f4               	movss	dword ptr [ebp - 0xc], xmm0
 11db471: e8 2a 89 fd ff               	call	0x11b3da0
 11db476: 0f 57 c0                     	xorps	xmm0, xmm0
 11db479: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 11db47d: 8b ce                        	mov	ecx, esi
 11db47f: f3 0f 11 45 24               	movss	dword ptr [ebp + 0x24], xmm0
 11db484: e8 27 89 fd ff               	call	0x11b3db0
 11db489: 8b 4d 1c                     	mov	ecx, dword ptr [ebp + 0x1c]
 11db48c: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11db48f: f3 0f 10 4d 24               	movss	xmm1, dword ptr [ebp + 0x24]
 11db494: 8b 1d b4 28 c2 01            	mov	ebx, dword ptr [0x1c228b4]
 11db49a: 51                           	push	ecx
 11db49b: 0f 57 c0                     	xorps	xmm0, xmm0
 11db49e: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 11db4a2: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11db4a5: f3 0f 11 45 ec               	movss	dword ptr [ebp - 0x14], xmm0
 11db4aa: 66 0f 6e 45 0c               	movd	xmm0, dword ptr [ebp + 0xc]
 11db4af: 52                           	push	edx
 11db4b0: 0f 5b c0                     	cvtdq2ps	xmm0, xmm0
 11db4b3: 50                           	push	eax
 11db4b4: 51                           	push	ecx
 11db4b5: f3 0f 11 45 e0               	movss	dword ptr [ebp - 0x20], xmm0
 11db4ba: 66 0f 6e 45 10               	movd	xmm0, dword ptr [ebp + 0x10]
 11db4bf: 0f 5b c0                     	cvtdq2ps	xmm0, xmm0
 11db4c2: f3 0f 11 45 e4               	movss	dword ptr [ebp - 0x1c], xmm0
 11db4c7: f3 0f 10 45 20               	movss	xmm0, dword ptr [ebp + 0x20]
 11db4cc: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11db4d1: 8d 4d f8                     	lea	ecx, [ebp - 0x8]
 11db4d4: 51                           	push	ecx
 11db4d5: 8b 4d 14                     	mov	ecx, dword ptr [ebp + 0x14]
 11db4d8: 8d 55 f0                     	lea	edx, [ebp - 0x10]
 11db4db: 52                           	push	edx
 11db4dc: 56                           	push	esi
 11db4dd: 57                           	push	edi
 11db4de: f3 0f 11 4d e8               	movss	dword ptr [ebp - 0x18], xmm1
 11db4e3: e8 a8 81 fd ff               	call	0x11b3690
 11db4e8: 50                           	push	eax
 11db4e9: 8d 45 e8                     	lea	eax, [ebp - 0x18]
 11db4ec: 50                           	push	eax
 11db4ed: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
 11db4f0: 51                           	push	ecx
 11db4f1: 8b cb                        	mov	ecx, ebx
 11db4f3: e8 78 37 03 00               	call	0x120ec70 <.text+0x338e0>
 11db4f8: 5f                           	pop	edi
 11db4f9: 5b                           	pop	ebx
 11db4fa: 5e                           	pop	esi
 11db4fb: 8b e5                        	mov	esp, ebp
 11db4fd: 5d                           	pop	ebp
 11db4fe: c2 34 00                     	ret	0x34
