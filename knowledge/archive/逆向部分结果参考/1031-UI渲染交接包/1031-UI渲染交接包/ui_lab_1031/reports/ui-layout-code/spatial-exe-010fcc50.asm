
<stdin>:	file format elf32-i386

Disassembly of section .text:

010fcc50 <.text>:
 10fcc50: d8 e9                        	fsubr	st, st(1)
 10fcc52: 89 00                        	mov	dword ptr [eax], eax
 10fcc54: 00 00                        	add	byte ptr [eax], al
 10fcc56: 68 18 5a 83 01               	push	0x1835a18
 10fcc5b: e8 90 32 0a 00               	call	0x119fef0 <.text+0xa32a0>
 10fcc60: 8b c8                        	mov	ecx, eax
 10fcc62: 83 c4 04                     	add	esp, 0x4
 10fcc65: 8d 79 02                     	lea	edi, [ecx + 0x2]
 10fcc68: eb 06                        	jmp	0x10fcc70 <.text+0x20>
 10fcc6a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 10fcc70: 66 8b 11                     	mov	dx, word ptr [ecx]
 10fcc73: 83 c1 02                     	add	ecx, 0x2
 10fcc76: 66 85 d2                     	test	dx, dx
 10fcc79: 75 f5                        	jne	0x10fcc70 <.text+0x20>
 10fcc7b: 2b cf                        	sub	ecx, edi
 10fcc7d: d1 f9                        	sar	ecx
 10fcc7f: 51                           	push	ecx
 10fcc80: 50                           	push	eax
 10fcc81: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 10fcc84: 50                           	push	eax
 10fcc85: 6a 00                        	push	0x0
 10fcc87: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 10fcc8a: e8 a1 4f 30 ff               	call	0x401c30
 10fcc8f: 85 c0                        	test	eax, eax
 10fcc91: 75 0a                        	jne	0x10fcc9d <.text+0x4d>
 10fcc93: 50                           	push	eax
 10fcc94: e8 77 6a 12 00               	call	0x1223710 <.text+0x126ac0>
 10fcc99: dd d8                        	fstp	st(0)
 10fcc9b: eb 42                        	jmp	0x10fccdf <.text+0x8f>
 10fcc9d: 68 e8 59 83 01               	push	0x18359e8
 10fcca2: e8 49 32 0a 00               	call	0x119fef0 <.text+0xa32a0>
 10fcca7: 8b c8                        	mov	ecx, eax
 10fcca9: 83 c4 04                     	add	esp, 0x4
 10fccac: 8d 79 02                     	lea	edi, [ecx + 0x2]
 10fccaf: 90                           	nop
 10fccb0: 66 8b 11                     	mov	dx, word ptr [ecx]
 10fccb3: 83 c1 02                     	add	ecx, 0x2
 10fccb6: 66 85 d2                     	test	dx, dx
 10fccb9: 75 f5                        	jne	0x10fccb0 <.text+0x60>
 10fccbb: 2b cf                        	sub	ecx, edi
 10fccbd: d1 f9                        	sar	ecx
 10fccbf: 51                           	push	ecx
 10fccc0: 8b 4d e4                     	mov	ecx, dword ptr [ebp - 0x1c]
 10fccc3: 50                           	push	eax
 10fccc4: 51                           	push	ecx
 10fccc5: 6a 00                        	push	0x0
 10fccc7: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 10fccca: e8 61 4f 30 ff               	call	0x401c30
 10fcccf: 85 c0                        	test	eax, eax
 10fccd1: 75 0f                        	jne	0x10fcce2 <.text+0x92>
 10fccd3: 50                           	push	eax
 10fccd4: e8 37 6a 12 00               	call	0x1223710 <.text+0x126ac0>
 10fccd9: d9 9e 18 23 00 00            	fstp	dword ptr [esi + 0x2318]
 10fccdf: 83 c4 04                     	add	esp, 0x4
 10fcce2: bb 08 00 00 00               	mov	ebx, 0x8
 10fcce7: c6 45 fc 12                  	mov	byte ptr [ebp - 0x4], 0x12
 10fcceb: 39 5d a8                     	cmp	dword ptr [ebp - 0x58], ebx
 10fccee: 72 0c                        	jb	0x10fccfc <.text+0xac>
 10fccf0: 8b 55 94                     	mov	edx, dword ptr [ebp - 0x6c]
 10fccf3: 52                           	push	edx
 10fccf4: e8 2e 8e 2d 00               	call	0x13d5b27 <.text+0x2d8ed7>
 10fccf9: 83 c4 04                     	add	esp, 0x4
 10fccfc: 8b 4d 90                     	mov	ecx, dword ptr [ebp - 0x70]
 10fccff: 33 c0                        	xor	eax, eax
 10fcd01: bf 07 00 00 00               	mov	edi, 0x7
 10fcd06: 51                           	push	ecx
 10fcd07: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
 10fcd0a: c7 45 a4 00 00 00 00         	mov	dword ptr [ebp - 0x5c], 0x0
 10fcd11: 66 89 45 94                  	mov	word ptr [ebp - 0x6c], ax
 10fcd15: e8 0d 8e 2d 00               	call	0x13d5b27 <.text+0x2d8ed7>
 10fcd1a: 83 c4 04                     	add	esp, 0x4
 10fcd1d: c7 45 90 00 00 00 00         	mov	dword ptr [ebp - 0x70], 0x0
 10fcd24: 39 5d 80                     	cmp	dword ptr [ebp - 0x80], ebx
 10fcd27: 72 0f                        	jb	0x10fcd38 <.text+0xe8>
 10fcd29: 8b 95 6c ff ff ff            	mov	edx, dword ptr [ebp - 0x94]
 10fcd2f: 52                           	push	edx
 10fcd30: e8 f2 8d 2d 00               	call	0x13d5b27 <.text+0x2d8ed7>
 10fcd35: 83 c4 04                     	add	esp, 0x4
 10fcd38: 8b 8d 68 ff ff ff            	mov	ecx, dword ptr [ebp - 0x98]
 10fcd3e: 33 c0                        	xor	eax, eax
 10fcd40: 51                           	push	ecx
 10fcd41: 89 7d 80                     	mov	dword ptr [ebp - 0x80], edi
 10fcd44: c7 85 7c ff ff ff 00 00 00 00	mov	dword ptr [ebp - 0x84], 0x0
 10fcd4e: 66 89 85 6c ff ff ff         	mov	word ptr [ebp - 0x94], ax
 10fcd55: e8 cd 8d 2d 00               	call	0x13d5b27 <.text+0x2d8ed7>
 10fcd5a: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 10fcd5d: 6a 01                        	push	0x1
 10fcd5f: 52                           	push	edx
 10fcd60: e8 ab 84 12 00               	call	0x1225210 <.text+0x1285c0>
 10fcd65: 83 c4 0c                     	add	esp, 0xc
 10fcd68: 84 c0                        	test	al, al
 10fcd6a: 0f 85 20 fd ff ff            	jne	0x10fca90
 10fcd70: 33 ff                        	xor	edi, edi
 10fcd72: 8d 5f 07                     	lea	ebx, [edi + 0x7]
 10fcd75: 83 7d c8 08                  	cmp	dword ptr [ebp - 0x38], 0x8
 10fcd79: 72 0c                        	jb	0x10fcd87 <.text+0x137>
 10fcd7b: 8b 45 b4                     	mov	eax, dword ptr [ebp - 0x4c]
 10fcd7e: 50                           	push	eax
 10fcd7f: e8 a3 8d 2d 00               	call	0x13d5b27 <.text+0x2d8ed7>
 10fcd84: 83 c4 04                     	add	esp, 0x4
 10fcd87: 8b 55 b0                     	mov	edx, dword ptr [ebp - 0x50]
 10fcd8a: 33 c9                        	xor	ecx, ecx
 10fcd8c: 52                           	push	edx
 10fcd8d: 89 5d c8                     	mov	dword ptr [ebp - 0x38], ebx
 10fcd90: 89 7d c4                     	mov	dword ptr [ebp - 0x3c], edi
 10fcd93: 66 89 4d b4                  	mov	word ptr [ebp - 0x4c], cx
 10fcd97: e8 8b 8d 2d 00               	call	0x13d5b27 <.text+0x2d8ed7>
 10fcd9c: 83 c4 04                     	add	esp, 0x4
 10fcd9f: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 10fcda3: 89 7d b0                     	mov	dword ptr [ebp - 0x50], edi
 10fcda6: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 10fcdad: 72 0c                        	jb	0x10fcdbb <.text+0x16b>
 10fcdaf: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 10fcdb2: 50                           	push	eax
 10fcdb3: e8 6f 8d 2d 00               	call	0x13d5b27 <.text+0x2d8ed7>
 10fcdb8: 83 c4 04                     	add	esp, 0x4
 10fcdbb: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 10fcdbe: 33 c9                        	xor	ecx, ecx
 10fcdc0: 52                           	push	edx
 10fcdc1: 89 5d e8                     	mov	dword ptr [ebp - 0x18], ebx
 10fcdc4: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
 10fcdc7: 66 89 4d d4                  	mov	word ptr [ebp - 0x2c], cx
 10fcdcb: e8 57 8d 2d 00               	call	0x13d5b27 <.text+0x2d8ed7>
 10fcdd0: 83 c4 04                     	add	esp, 0x4
 10fcdd3: 89 7d d0                     	mov	dword ptr [ebp - 0x30], edi
 10fcdd6: 68 18 5d 83 01               	push	0x1835d18
 10fcddb: 83 cb ff                     	or	ebx, -0x1
 10fcdde: e8 0d 31 0a 00               	call	0x119fef0 <.text+0xa32a0>
 10fcde3: 68 b8 02 00 00               	push	0x2b8
 10fcde8: 8b f8                        	mov	edi, eax
 10fcdea: e8 91 35 0b 00               	call	0x11b0380 <.text+0xb3730>
 10fcdef: 83 c4 08                     	add	esp, 0x8
 10fcdf2: 89 85 64 ff ff ff            	mov	dword ptr [ebp - 0x9c], eax
 10fcdf8: c7 45 fc 14 00 00 00         	mov	dword ptr [ebp - 0x4], 0x14
 10fcdff: 85 c0                        	test	eax, eax
 10fce01: 74 09                        	je	0x10fce0c <.text+0x1bc>
 10fce03: 8b c8                        	mov	ecx, eax
 10fce05: e8 76 21 0c 00               	call	0x11bef80 <.text+0xc2330>
 10fce0a: eb 02                        	jmp	0x10fce0e <.text+0x1be>
 10fce0c: 33 c0                        	xor	eax, eax
 10fce0e: 6a 01                        	push	0x1
 10fce10: 6a 00                        	push	0x0
 10fce12: 6a 00                        	push	0x0
 10fce14: 8b c8                        	mov	ecx, eax
 10fce16: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 10fce19: 89 86 14 23 00 00            	mov	dword ptr [esi + 0x2314], eax
 10fce1f: e8 ac 1c 0c 00               	call	0x11bead0 <.text+0xc1e80>
 10fce24: 68 c0 00 00 00               	push	0xc0
 10fce29: e8 ec 9c 2d 00               	call	0x13d6b1a <.text+0x2d9eca>
 10fce2e: 83 c4 04                     	add	esp, 0x4
 10fce31: 89 85 64 ff ff ff            	mov	dword ptr [ebp - 0x9c], eax
 10fce37: c7 45 fc 15 00 00 00         	mov	dword ptr [ebp - 0x4], 0x15
 10fce3e: 85 c0                        	test	eax, eax
 10fce40: 74 10                        	je	0x10fce52 <.text+0x202>
 10fce42: 8b 8e 14 23 00 00            	mov	ecx, dword ptr [esi + 0x2314]
 10fce48: 51                           	push	ecx
 10fce49: 8b c8                        	mov	ecx, eax
 10fce4b: e8 5b c6 86 01               	call	0x29694ab <.text+0x186c85b>
 10fce50: eb 02                        	jmp	0x10fce54 <.text+0x204>
 10fce52: 33 c0                        	xor	eax, eax
 10fce54: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 10fce57: 89 86 10 23 00 00            	mov	dword ptr [esi + 0x2310], eax
 10fce5d: 85 ff                        	test	edi, edi
 10fce5f: 74 0c                        	je	0x10fce6d <.text+0x21d>
 10fce61: 6a 00                        	push	0x0
 10fce63: 6a 00                        	push	0x0
 10fce65: 57                           	push	edi
 10fce66: 8b c8                        	mov	ecx, eax
 10fce68: e8 53 b0 f6 ff               	call	0x1067ec0
 10fce6d: 68 c4 03 00 00               	push	0x3c4
 10fce72: e8 09 35 0b 00               	call	0x11b0380 <.text+0xb3730>
 10fce77: 83 c4 04                     	add	esp, 0x4
 10fce7a: 89 85 64 ff ff ff            	mov	dword ptr [ebp - 0x9c], eax
 10fce80: c7 45 fc 16 00 00 00         	mov	dword ptr [ebp - 0x4], 0x16
 10fce87: 85 c0                        	test	eax, eax
 10fce89: 74 19                        	je	0x10fcea4 <.text+0x254>
 10fce8b: 8b 56 34                     	mov	edx, dword ptr [esi + 0x34]
 10fce8e: 6a 00                        	push	0x0
 10fce90: 6a 00                        	push	0x0
 10fce92: 6a 00                        	push	0x0
 10fce94: 6a 00                        	push	0x0
 10fce96: 6a 00                        	push	0x0
 10fce98: 6a 00                        	push	0x0
 10fce9a: 52                           	push	edx
 10fce9b: 8b c8                        	mov	ecx, eax
 10fce9d: e8 1e 86 0c 00               	call	0x11c54c0 <.text+0xc8870>
 10fcea2: eb 02                        	jmp	0x10fcea6 <.text+0x256>
 10fcea4: 33 c0                        	xor	eax, eax
 10fcea6: 89 86 20 23 00 00            	mov	dword ptr [esi + 0x2320], eax
 10fceac: 8b 10                        	mov	edx, dword ptr [eax]
 10fceae: 8b c8                        	mov	ecx, eax
 10fceb0: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 10fceb3: 6a 00                        	push	0x0
 10fceb5: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 10fceb8: ff d0                        	call	eax
 10fceba: 8b 8e 20 23 00 00            	mov	ecx, dword ptr [esi + 0x2320]
 10fcec0: 51                           	push	ecx
 10fcec1: 8b 4e 28                     	mov	ecx, dword ptr [esi + 0x28]
 10fcec4: e8 67 24 0c 00               	call	0x11bf330 <.text+0xc26e0>
 10fcec9: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 10fcecc: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 10fced3: 59                           	pop	ecx
 10fced4: 5f                           	pop	edi
 10fced5: 5e                           	pop	esi
 10fced6: 5b                           	pop	ebx
 10fced7: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 10fceda: 33 cd                        	xor	ecx, ebp
 10fcedc: e8 f7 a2 2d 00               	call	0x13d71d8 <.text+0x2da588>
 10fcee1: 8b e5                        	mov	esp, ebp
 10fcee3: 5d                           	pop	ebp
 10fcee4: c3                           	ret
 10fcee5: 8d 95 60 ff ff ff            	lea	edx, [ebp - 0xa0]
 10fceeb: 52                           	push	edx
 10fceec: 8d 8d 4c ff ff ff            	lea	ecx, [ebp - 0xb4]
 10fcef2: 89 bd 60 ff ff ff            	mov	dword ptr [ebp - 0xa0], edi
 10fcef8: e8 cd 95 2d 00               	call	0x13d64ca <.text+0x2d987a>
 10fcefd: 68 90 0f 91 01               	push	0x1910f90
 10fcf02: 8d 85 4c ff ff ff            	lea	eax, [ebp - 0xb4]
 10fcf08: 50                           	push	eax
 10fcf09: c7 85 4c ff ff ff 84 20 56 01	mov	dword ptr [ebp - 0xb4], 0x1562084
 10fcf13: e8 82 9c 2d 00               	call	0x13d6b9a <.text+0x2d9f4a>
 10fcf18: 8d 8d 5c ff ff ff            	lea	ecx, [ebp - 0xa4]
 10fcf1e: 51                           	push	ecx
 10fcf1f: 8d 8d 40 ff ff ff            	lea	ecx, [ebp - 0xc0]
 10fcf25: 89 bd 5c ff ff ff            	mov	dword ptr [ebp - 0xa4], edi
 10fcf2b: e8 9a 95 2d 00               	call	0x13d64ca <.text+0x2d987a>
 10fcf30: 68 90 0f 91 01               	push	0x1910f90
 10fcf35: 8d 95 40 ff ff ff            	lea	edx, [ebp - 0xc0]
 10fcf3b: 52                           	push	edx
 10fcf3c: c7 85 40 ff ff ff 84 20 56 01	mov	dword ptr [ebp - 0xc0], 0x1562084
 10fcf46: e8 4f 9c 2d 00               	call	0x13d6b9a <.text+0x2d9f4a>
 10fcf4b: 8d 85 60 ff ff ff            	lea	eax, [ebp - 0xa0]
 10fcf51: 50                           	push	eax
 10fcf52: 8d 8d 40 ff ff ff            	lea	ecx, [ebp - 0xc0]
 10fcf58: c7 85 60 ff ff ff 00 00 00 00	mov	dword ptr [ebp - 0xa0], 0x0
 10fcf62: e8 63 95 2d 00               	call	0x13d64ca <.text+0x2d987a>
 10fcf67: 68 90 0f 91 01               	push	0x1910f90
 10fcf6c: 8d 8d 40 ff ff ff            	lea	ecx, [ebp - 0xc0]
 10fcf72: 51                           	push	ecx
 10fcf73: c7 85 40 ff ff ff 84 20 56 01	mov	dword ptr [ebp - 0xc0], 0x1562084
 10fcf7d: e8 18 9c 2d 00               	call	0x13d6b9a <.text+0x2d9f4a>
 10fcf82: cc                           	int3
 10fcf83: cc                           	int3
 10fcf84: cc                           	int3
 10fcf85: cc                           	int3
 10fcf86: cc                           	int3
 10fcf87: cc                           	int3
 10fcf88: cc                           	int3
 10fcf89: cc                           	int3
 10fcf8a: cc                           	int3
 10fcf8b: cc                           	int3
 10fcf8c: cc                           	int3
 10fcf8d: cc                           	int3
 10fcf8e: cc                           	int3
 10fcf8f: cc                           	int3
 10fcf90: 55                           	push	ebp
 10fcf91: 8b ec                        	mov	ebp, esp
 10fcf93: 56                           	push	esi
 10fcf94: 57                           	push	edi
 10fcf95: 8b f1                        	mov	esi, ecx
 10fcf97: 8d be dc 22 00 00            	lea	edi, [esi + 0x22dc]
 10fcf9d: 57                           	push	edi
 10fcf9e: ff 15 0c a1 55 01            	call	dword ptr [0x155a10c]
 10fcfa4: 80 be f4 22 00 00 00         	cmp	byte ptr [esi + 0x22f4], 0x0
 10fcfab: 74 16                        	je	0x10fcfc3 <.text+0x373>
 10fcfad: 8b 86 f8 22 00 00            	mov	eax, dword ptr [esi + 0x22f8]
 10fcfb3: 50                           	push	eax
 10fcfb4: 8d 4e f0                     	lea	ecx, [esi - 0x10]
 10fcfb7: e8 a4 f0 ff ff               	call	0x10fc060
 10fcfbc: c6 86 f4 22 00 00 00         	mov	byte ptr [esi + 0x22f4], 0x0
 10fcfc3: 57                           	push	edi
 10fcfc4: ff 15 08 a1 55 01            	call	dword ptr [0x155a108]
 10fcfca: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 10fcfd0: 80 b9 e4 42 00 00 ff         	cmp	byte ptr [ecx + 0x42e4], -0x1
 10fcfd7: 0f 84 e3 03 00 00            	je	0x10fd3c0 <.text+0x770>
 10fcfdd: 8b 8e 84 00 00 00            	mov	ecx, dword ptr [esi + 0x84]
 10fcfe3: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 10fcfe6: 53                           	push	ebx
 10fcfe7: 3b f9                        	cmp	edi, ecx
 10fcfe9: 0f 85 a2 00 00 00            	jne	0x10fd091 <.text+0x441>
 10fcfef: e8 cc 16 d7 ff               	call	0xe6e6c0
 10fcff4: 84 c0                        	test	al, al
 10fcff6: 0f 84 95 00 00 00            	je	0x10fd091 <.text+0x441>
 10fcffc: 68 90 01 00 00               	push	0x190
 10fd001: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 10fd007: 50                           	push	eax
 10fd008: 6a 78                        	push	0x78
 10fd00a: 6a 00                        	push	0x0
 10fd00c: e8 4f c9 0b 00               	call	0x11b9960 <.text+0xbcd10>
 10fd011: 6a 00                        	push	0x0
 10fd013: 6a 02                        	push	0x2
 10fd015: 8b d8                        	mov	ebx, eax
 10fd017: e8 44 64 0b 00               	call	0x11b3460 <.text+0xb6810>
 10fd01c: f3 0f 10 05 50 22 56 01      	movss	xmm0, dword ptr [0x1562250]
 10fd024: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
 10fd027: f3 0f 11 44 24 14            	movss	dword ptr [esp + 0x14], xmm0
 10fd02d: 83 c4 10                     	add	esp, 0x10
 10fd030: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 10fd035: 0f 57 c0                     	xorps	xmm0, xmm0
 10fd038: 0f b6 d3                     	movzx	edx, bl
 10fd03b: c1 e2 18                     	shl	edx, 0x18
 10fd03e: 81 ca ff ff ff 00            	or	edx, 0xffffff
 10fd044: 52                           	push	edx
 10fd045: 83 ec 0c                     	sub	esp, 0xc
 10fd048: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 10fd04e: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 10fd056: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 10fd05c: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 10fd061: 6a 0d                        	push	0xd
 10fd063: e8 68 7b 0b 00               	call	0x11b4bd0 <.text+0xb7f80>
 10fd068: 8b 8e 84 00 00 00            	mov	ecx, dword ptr [esi + 0x84]
 10fd06e: 50                           	push	eax
 10fd06f: e8 8c 12 0c 00               	call	0x11be300 <.text+0xc16b0>
 10fd074: 8b 8e 84 00 00 00            	mov	ecx, dword ptr [esi + 0x84]
 10fd07a: 50                           	push	eax
 10fd07b: e8 e0 2e 33 ff               	call	0x42ff60
 10fd080: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 10fd086: 50                           	push	eax
 10fd087: e8 54 71 0b 00               	call	0x11b41e0 <.text+0xb7590>
 10fd08c: e8 df 64 0b 00               	call	0x11b3570 <.text+0xb6920>
 10fd091: 3b 7e 18                     	cmp	edi, dword ptr [esi + 0x18]
 10fd094: 0f 85 e1 00 00 00            	jne	0x10fd17b <.text+0x52b>
 10fd09a: 8d 4e f0                     	lea	ecx, [esi - 0x10]
 10fd09d: e8 1e 9d ff ff               	call	0x10f6dc0
 10fd0a2: 8d 4e f0                     	lea	ecx, [esi - 0x10]
 10fd0a5: e8 e6 84 ff ff               	call	0x10f5590
 10fd0aa: bf 0e 00 00 00               	mov	edi, 0xe
 10fd0af: 39 7e 08                     	cmp	dword ptr [esi + 0x8], edi
 10fd0b2: 74 38                        	je	0x10fd0ec <.text+0x49c>
 10fd0b4: 8b 8e 00 23 00 00            	mov	ecx, dword ptr [esi + 0x2300]
 10fd0ba: 6a 00                        	push	0x0
 10fd0bc: 68 90 bb 9d 01               	push	0x19dbb90
 10fd0c1: 68 88 96 9d 01               	push	0x19d9688
 10fd0c6: 6a 00                        	push	0x0
 10fd0c8: 6a 01                        	push	0x1
 10fd0ca: 68 cf 00 00 00               	push	0xcf
 10fd0cf: e8 cc 61 f6 ff               	call	0x10632a0
 10fd0d4: 50                           	push	eax
 10fd0d5: e8 05 a6 2d 00               	call	0x13d76df <.text+0x2daa8f>
 10fd0da: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
 10fd0dd: 8d 54 09 02                  	lea	edx, [ecx + ecx + 0x2]
 10fd0e1: 83 c4 14                     	add	esp, 0x14
 10fd0e4: 52                           	push	edx
 10fd0e5: 8b c8                        	mov	ecx, eax
 10fd0e7: e8 34 58 0c 00               	call	0x11c2920 <.text+0xc5cd0>
 10fd0ec: 8b 8e 00 23 00 00            	mov	ecx, dword ptr [esi + 0x2300]
 10fd0f2: 6a 01                        	push	0x1
 10fd0f4: 68 d7 00 00 00               	push	0xd7
 10fd0f9: e8 a2 61 f6 ff               	call	0x10632a0
 10fd0fe: 85 c0                        	test	eax, eax
 10fd100: 74 0b                        	je	0x10fd10d <.text+0x4bd>
 10fd102: 8b 10                        	mov	edx, dword ptr [eax]
 10fd104: 8b c8                        	mov	ecx, eax
 10fd106: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 10fd109: 6a 01                        	push	0x1
 10fd10b: ff d0                        	call	eax
 10fd10d: 8b 8e 00 23 00 00            	mov	ecx, dword ptr [esi + 0x2300]
 10fd113: 6a 01                        	push	0x1
 10fd115: 68 d8 00 00 00               	push	0xd8
 10fd11a: e8 81 61 f6 ff               	call	0x10632a0
 10fd11f: 85                           	<unknown>
