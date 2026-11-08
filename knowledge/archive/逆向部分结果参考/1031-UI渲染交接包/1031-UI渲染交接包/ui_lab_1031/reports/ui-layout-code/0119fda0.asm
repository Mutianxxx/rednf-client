
<stdin>:	file format elf32-i386

Disassembly of section .text:

0119fda0 <.text>:
 119fda0: 55                           	push	ebp
 119fda1: 8b ec                        	mov	ebp, esp
 119fda3: 83 ec 1c                     	sub	esp, 0x1c
 119fda6: 83 3d 08 8a b0 01 00         	cmp	dword ptr [0x1b08a08], 0x0
 119fdad: 75 14                        	jne	0x119fdc3 <.text+0x23>
 119fdaf: 80 3d 04 8a b0 01 00         	cmp	byte ptr [0x1b08a04], 0x0
 119fdb6: 74 06                        	je	0x119fdbe <.text+0x1e>
 119fdb8: 33 c0                        	xor	eax, eax
 119fdba: 8b e5                        	mov	esp, ebp
 119fdbc: 5d                           	pop	ebp
 119fdbd: c3                           	ret
 119fdbe: e8 3d ff ff ff               	call	0x119fd00
 119fdc3: 53                           	push	ebx
 119fdc4: 56                           	push	esi
 119fdc5: 68 00 8a b0 01               	push	0x1b08a00
 119fdca: e8 31 4e 00 00               	call	0x11a4c00 <.text+0x4e60>
 119fdcf: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 119fdd2: 83 c4 04                     	add	esp, 0x4
 119fdd5: 8d 45 fc                     	lea	eax, [ebp - 0x4]
 119fdd8: 50                           	push	eax
 119fdd9: 8d 4d e8                     	lea	ecx, [ebp - 0x18]
 119fddc: 51                           	push	ecx
 119fddd: 8b 0d 08 8a b0 01            	mov	ecx, dword ptr [0x1b08a08]
 119fde3: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 119fde6: e8 65 a7 d1 ff               	call	0xeba550
 119fdeb: 8b 08                        	mov	ecx, dword ptr [eax]
 119fded: 33 f6                        	xor	esi, esi
 119fdef: 85 c9                        	test	ecx, ecx
 119fdf1: 74 08                        	je	0x119fdfb <.text+0x5b>
 119fdf3: 8b 09                        	mov	ecx, dword ptr [ecx]
 119fdf5: 85 c9                        	test	ecx, ecx
 119fdf7: 74 02                        	je	0x119fdfb <.text+0x5b>
 119fdf9: 8b 31                        	mov	esi, dword ptr [ecx]
 119fdfb: 8b 0d 08 8a b0 01            	mov	ecx, dword ptr [0x1b08a08]
 119fe01: 57                           	push	edi
 119fe02: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
 119fe05: 8d 55 f4                     	lea	edx, [ebp - 0xc]
 119fe08: 52                           	push	edx
 119fe09: e8 82 f9 60 ff               	call	0x7af790
 119fe0e: 85 f6                        	test	esi, esi
 119fe10: 0f 84 af 00 00 00            	je	0x119fec5 <.text+0x125>
 119fe16: 8b 36                        	mov	esi, dword ptr [esi]
 119fe18: 85 f6                        	test	esi, esi
 119fe1a: 0f 84 a5 00 00 00            	je	0x119fec5 <.text+0x125>
 119fe20: 8b 08                        	mov	ecx, dword ptr [eax]
 119fe22: 85 c9                        	test	ecx, ecx
 119fe24: 74 02                        	je	0x119fe28 <.text+0x88>
 119fe26: 8b 09                        	mov	ecx, dword ptr [ecx]
 119fe28: 3b f1                        	cmp	esi, ecx
 119fe2a: 0f 85 95 00 00 00            	jne	0x119fec5 <.text+0x125>
 119fe30: 68 00 8a b0 01               	push	0x1b08a00
 119fe35: 3b 78 08                     	cmp	edi, dword ptr [eax + 0x8]
 119fe38: 74 14                        	je	0x119fe4e <.text+0xae>
 119fe3a: 8b 77 0c                     	mov	esi, dword ptr [edi + 0xc]
 119fe3d: e8 ee 4d 00 00               	call	0x11a4c30 <.text+0x4e90>
 119fe42: 83 c4 04                     	add	esp, 0x4
 119fe45: 5f                           	pop	edi
 119fe46: 8b c6                        	mov	eax, esi
 119fe48: 5e                           	pop	esi
 119fe49: 5b                           	pop	ebx
 119fe4a: 8b e5                        	mov	esp, ebp
 119fe4c: 5d                           	pop	ebp
 119fe4d: c3                           	ret
 119fe4e: e8 dd 4d 00 00               	call	0x11a4c30 <.text+0x4e90>
 119fe53: 68 00 8a b0 01               	push	0x1b08a00
 119fe58: e8 33 4e 00 00               	call	0x11a4c90 <.text+0x4ef0>
 119fe5d: 8a 43 01                     	mov	al, byte ptr [ebx + 0x1]
 119fe60: 24 fe                        	and	al, -0x2
 119fe62: 0f b6 f8                     	movzx	edi, al
 119fe65: 0f b7 43 02                  	movzx	eax, word ptr [ebx + 0x2]
 119fe69: 8b f7                        	mov	esi, edi
 119fe6b: c1 e6 07                     	shl	esi, 0x7
 119fe6e: 0b f7                        	or	esi, edi
 119fe70: 33 f0                        	xor	esi, eax
 119fe72: 0f af 75 0c                  	imul	esi, dword ptr [ebp + 0xc]
 119fe76: 56                           	push	esi
 119fe77: e8 44 f7 ff ff               	call	0x119f5c0
 119fe7c: 81 cf a0 4c 71 9a            	or	edi, 0x9a714ca0
 119fe82: 57                           	push	edi
 119fe83: 8b d8                        	mov	ebx, eax
 119fe85: 53                           	push	ebx
 119fe86: 56                           	push	esi
 119fe87: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 119fe8a: 8d 4e 04                     	lea	ecx, [esi + 0x4]
 119fe8d: 51                           	push	ecx
 119fe8e: e8 cd f6 ff ff               	call	0x119f560
 119fe93: 8b 0d 08 8a b0 01            	mov	ecx, dword ptr [0x1b08a08]
 119fe99: 83 c4 1c                     	add	esp, 0x1c
 119fe9c: 8d 55 f8                     	lea	edx, [ebp - 0x8]
 119fe9f: 52                           	push	edx
 119fea0: 8d 45 e4                     	lea	eax, [ebp - 0x1c]
 119fea3: 50                           	push	eax
 119fea4: 89 75 f8                     	mov	dword ptr [ebp - 0x8], esi
 119fea7: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 119feaa: e8 f1 fc ff ff               	call	0x119fba0
 119feaf: 68 00 8a b0 01               	push	0x1b08a00
 119feb4: e8 27 4e 00 00               	call	0x11a4ce0 <.text+0x4f40>
 119feb9: 83 c4 04                     	add	esp, 0x4
 119febc: 5f                           	pop	edi
 119febd: 5e                           	pop	esi
 119febe: 8b c3                        	mov	eax, ebx
 119fec0: 5b                           	pop	ebx
 119fec1: 8b e5                        	mov	esp, ebp
 119fec3: 5d                           	pop	ebp
 119fec4: c3                           	ret
 119fec5: e8 dd 6e 23 00               	call	0x13d6da7 <.text+0x237007>
 119feca: cc                           	int3
 119fecb: cc                           	int3
 119fecc: cc                           	int3
 119fecd: cc                           	int3
 119fece: cc                           	int3
 119fecf: cc                           	int3
 119fed0: 55                           	push	ebp
 119fed1: 8b ec                        	mov	ebp, esp
 119fed3: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 119fed6: 8a 08                        	mov	cl, byte ptr [eax]
 119fed8: 80 f9 a1                     	cmp	cl, -0x5f
 119fedb: 75 05                        	jne	0x119fee2 <.text+0x142>
 119fedd: 83 c0 04                     	add	eax, 0x4
 119fee0: 5d                           	pop	ebp
 119fee1: c3                           	ret
 119fee2: 6a 01                        	push	0x1
 119fee4: 50                           	push	eax
 119fee5: e8 b6 fe ff ff               	call	0x119fda0 <.text>
 119feea: 83 c4 08                     	add	esp, 0x8
 119feed: 5d                           	pop	ebp
 119feee: c3                           	ret
 119feef: cc                           	int3
