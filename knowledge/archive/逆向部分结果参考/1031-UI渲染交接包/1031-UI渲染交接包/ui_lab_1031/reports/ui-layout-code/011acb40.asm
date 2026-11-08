
<stdin>:	file format elf32-i386

Disassembly of section .text:

011acb40 <.text>:
 11acb40: 55                           	push	ebp
 11acb41: 8b ec                        	mov	ebp, esp
 11acb43: 83 ec 18                     	sub	esp, 0x18
 11acb46: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11acb49: 53                           	push	ebx
 11acb4a: 56                           	push	esi
 11acb4b: 8b f1                        	mov	esi, ecx
 11acb4d: c7 45 f4 00 00 00 00         	mov	dword ptr [ebp - 0xc], 0x0
 11acb54: c7 45 f8 00 00 00 00         	mov	dword ptr [ebp - 0x8], 0x0
 11acb5b: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11acb62: 85 c0                        	test	eax, eax
 11acb64: 0f 84 a9 00 00 00            	je	0x11acc13 <.text+0xd3>
 11acb6a: 83 7d 0c 00                  	cmp	dword ptr [ebp + 0xc], 0x0
 11acb6e: 0f 84 9f 00 00 00            	je	0x11acc13 <.text+0xd3>
 11acb74: 8b 5d 10                     	mov	ebx, dword ptr [ebp + 0x10]
 11acb77: 85 db                        	test	ebx, ebx
 11acb79: 0f 84 94 00 00 00            	je	0x11acc13 <.text+0xd3>
 11acb7f: 50                           	push	eax
 11acb80: 8d 45 e8                     	lea	eax, [ebp - 0x18]
 11acb83: 50                           	push	eax
 11acb84: e8 37 fa ff ff               	call	0x11ac5c0
 11acb89: 8b 08                        	mov	ecx, dword ptr [eax]
 11acb8b: 85 c9                        	test	ecx, ecx
 11acb8d: 74 0b                        	je	0x11acb9a <.text+0x5a>
 11acb8f: 8b 09                        	mov	ecx, dword ptr [ecx]
 11acb91: 85 c9                        	test	ecx, ecx
 11acb93: 74 05                        	je	0x11acb9a <.text+0x5a>
 11acb95: 8b 09                        	mov	ecx, dword ptr [ecx]
 11acb97: 89 4d f4                     	mov	dword ptr [ebp - 0xc], ecx
 11acb9a: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
 11acb9d: 8d 45 e8                     	lea	eax, [ebp - 0x18]
 11acba0: 50                           	push	eax
 11acba1: 8d 4e 10                     	lea	ecx, [esi + 0x10]
 11acba4: 89 55 fc                     	mov	dword ptr [ebp - 0x4], edx
 11acba7: e8 94 77 61 ff               	call	0x7c4340
 11acbac: 50                           	push	eax
 11acbad: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
 11acbb0: e8 ab e8 25 ff               	call	0x40b460
 11acbb5: 84 c0                        	test	al, al
 11acbb7: 74 15                        	je	0x11acbce <.text+0x8e>
 11acbb9: 68 9c 97 85 01               	push	0x185979c
 11acbbe: e8 2d 33 ff ff               	call	0x119fef0
 11acbc3: 83 c4 04                     	add	esp, 0x4
 11acbc6: 50                           	push	eax
 11acbc7: 68 33 03 00 00               	push	0x333
 11acbcc: eb 58                        	jmp	0x11acc26 <.text+0xe6>
 11acbce: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
 11acbd1: e8 6a 8a b3 ff               	call	0xce5640
 11acbd6: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11acbd9: 8b 10                        	mov	edx, dword ptr [eax]
 11acbdb: 53                           	push	ebx
 11acbdc: 51                           	push	ecx
 11acbdd: 52                           	push	edx
 11acbde: 56                           	push	esi
 11acbdf: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
 11acbe2: e8 59 8a b3 ff               	call	0xce5640
 11acbe7: 8d 48 04                     	lea	ecx, [eax + 0x4]
 11acbea: e8 81 f9 ff ff               	call	0x11ac570
 11acbef: 83 f8 01                     	cmp	eax, 0x1
 11acbf2: 75 15                        	jne	0x11acc09 <.text+0xc9>
 11acbf4: 68 9c 97 85 01               	push	0x185979c
 11acbf9: e8 f2 32 ff ff               	call	0x119fef0
 11acbfe: 83 c4 04                     	add	esp, 0x4
 11acc01: 50                           	push	eax
 11acc02: 68 39 03 00 00               	push	0x339
 11acc07: eb 1d                        	jmp	0x11acc26 <.text+0xe6>
 11acc09: 5e                           	pop	esi
 11acc0a: 33 c0                        	xor	eax, eax
 11acc0c: 5b                           	pop	ebx
 11acc0d: 8b e5                        	mov	esp, ebp
 11acc0f: 5d                           	pop	ebp
 11acc10: c2 0c 00                     	ret	0xc
 11acc13: 68 9c 97 85 01               	push	0x185979c
 11acc18: e8 d3 32 ff ff               	call	0x119fef0
 11acc1d: 83 c4 04                     	add	esp, 0x4
 11acc20: 50                           	push	eax
 11acc21: 68 2c 03 00 00               	push	0x32c
 11acc26: 68 d0 94 85 01               	push	0x18594d0
 11acc2b: e8 c0 32 ff ff               	call	0x119fef0
 11acc30: 83 c4 04                     	add	esp, 0x4
 11acc33: 50                           	push	eax
 11acc34: 68 b4 94 85 01               	push	0x18594b4
 11acc39: e8 f3 04 23 00               	call	0x13dd131 <.text+0x2305f1>
 11acc3e: 83 c0 20                     	add	eax, 0x20
 11acc41: 50                           	push	eax
 11acc42: e8 2f fc 22 00               	call	0x13dc876 <.text+0x22fd36>
 11acc47: 83 c4 14                     	add	esp, 0x14
 11acc4a: 5e                           	pop	esi
 11acc4b: b8 01 00 00 00               	mov	eax, 0x1
 11acc50: 5b                           	pop	ebx
 11acc51: 8b e5                        	mov	esp, ebp
 11acc53: 5d                           	pop	ebp
 11acc54: c2 0c 00                     	ret	0xc
 11acc57: cc                           	int3
 11acc58: cc                           	int3
 11acc59: cc                           	int3
 11acc5a: cc                           	int3
 11acc5b: cc                           	int3
 11acc5c: cc                           	int3
 11acc5d: cc                           	int3
 11acc5e: cc                           	int3
 11acc5f: cc                           	int3
 11acc60: 55                           	push	ebp
 11acc61: 8b ec                        	mov	ebp, esp
 11acc63: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11acc66: 83 ec 0c                     	sub	esp, 0xc
 11acc69: 53                           	push	ebx
 11acc6a: 56                           	push	esi
 11acc6b: 57                           	push	edi
 11acc6c: 8b f9                        	mov	edi, ecx
 11acc6e: 50                           	push	eax
 11acc6f: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
 11acc72: 51                           	push	ecx
 11acc73: 8b cf                        	mov	ecx, edi
 11acc75: 33 db                        	xor	ebx, ebx
 11acc77: e8 44 f9 ff ff               	call	0x11ac5c0
 11acc7c: 8b 08                        	mov	ecx, dword ptr [eax]
 11acc7e: 85 c9                        	test	ecx, ecx
 11acc80: 74 08                        	je	0x11acc8a <.text+0x14a>
 11acc82: 8b 09                        	mov	ecx, dword ptr [ecx]
 11acc84: 85 c9                        	test	ecx, ecx
 11acc86: 74 02                        	je	0x11acc8a <.text+0x14a>
 11acc88: 8b 19                        	mov	ebx, dword ptr [ecx]
 11acc8a: 8b 70 08                     	mov	esi, dword ptr [eax + 0x8]
 11acc8d: 8d 55 f4                     	lea	edx, [ebp - 0xc]
 11acc90: 52                           	push	edx
 11acc91: 8d 4f 10                     	lea	ecx, [edi + 0x10]
 11acc94: e8 a7 76 61 ff               	call	0x7c4340
 11acc99: 85 db                        	test	ebx, ebx
 11acc9b: 74 06                        	je	0x11acca3 <.text+0x163>
 11acc9d: 8b 13                        	mov	edx, dword ptr [ebx]
 11acc9f: 85 d2                        	test	edx, edx
 11acca1: 75 05                        	jne	0x11acca8 <.text+0x168>
 11acca3: e8 ff a0 22 00               	call	0x13d6da7 <.text+0x22a267>
 11acca8: 8b 08                        	mov	ecx, dword ptr [eax]
 11accaa: 85 c9                        	test	ecx, ecx
 11accac: 74 02                        	je	0x11accb0 <.text+0x170>
 11accae: 8b 09                        	mov	ecx, dword ptr [ecx]
 11accb0: 3b d1                        	cmp	edx, ecx
 11accb2: 74 05                        	je	0x11accb9 <.text+0x179>
 11accb4: e8 ee a0 22 00               	call	0x13d6da7 <.text+0x22a267>
 11accb9: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
 11accbc: 74 58                        	je	0x11acd16 <.text+0x1d6>
 11accbe: 8b c2                        	mov	eax, edx
 11accc0: 85 c0                        	test	eax, eax
 11accc2: 75 05                        	jne	0x11accc9 <.text+0x189>
 11accc4: e8 de a0 22 00               	call	0x13d6da7 <.text+0x22a267>
 11accc9: 85 f6                        	test	esi, esi
 11acccb: 74 d6                        	je	0x11acca3 <.text+0x163>
 11acccd: 39 70 04                     	cmp	dword ptr [eax + 0x4], esi
 11accd0: 77 d1                        	ja	0x11acca3 <.text+0x163>
 11accd2: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
 11accd5: 73 cc                        	jae	0x11acca3 <.text+0x163>
 11accd7: 8b 4e 38                     	mov	ecx, dword ptr [esi + 0x38]
 11accda: 85 c9                        	test	ecx, ecx
 11accdc: 74 38                        	je	0x11acd16 <.text+0x1d6>
 11accde: 85 c0                        	test	eax, eax
 11acce0: 75 05                        	jne	0x11acce7 <.text+0x1a7>
 11acce2: e8 c0 a0 22 00               	call	0x13d6da7 <.text+0x22a267>
 11acce7: 39 70 04                     	cmp	dword ptr [eax + 0x4], esi
 11accea: 77 b7                        	ja	0x11acca3 <.text+0x163>
 11accec: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
 11accef: 73 b2                        	jae	0x11acca3 <.text+0x163>
 11accf1: 51                           	push	ecx
 11accf2: e8 a3 a6 22 00               	call	0x13d739a <.text+0x22a85a>
 11accf7: 8b 03                        	mov	eax, dword ptr [ebx]
 11accf9: 83 c4 04                     	add	esp, 0x4
 11accfc: 85 c0                        	test	eax, eax
 11accfe: 75 05                        	jne	0x11acd05 <.text+0x1c5>
 11acd00: e8 a2 a0 22 00               	call	0x13d6da7 <.text+0x22a267>
 11acd05: 39 70 04                     	cmp	dword ptr [eax + 0x4], esi
 11acd08: 77 99                        	ja	0x11acca3 <.text+0x163>
 11acd0a: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
 11acd0d: 73 94                        	jae	0x11acca3 <.text+0x163>
 11acd0f: c7 46 38 00 00 00 00         	mov	dword ptr [esi + 0x38], 0x0
 11acd16: 5f                           	pop	edi
 11acd17: 5e                           	pop	esi
 11acd18: 5b                           	pop	ebx
 11acd19: 8b e5                        	mov	esp, ebp
 11acd1b: 5d                           	pop	ebp
 11acd1c: c2 04 00                     	ret	0x4
 11acd1f: cc                           	int3
 11acd20: 55                           	push	ebp
 11acd21: 8b ec                        	mov	ebp, esp
 11acd23: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11acd26: 3b 45 0c                     	cmp	eax, dword ptr [ebp + 0xc]
 11acd29: 74 5b                        	je	0x11acd86 <.text+0x246>
 11acd2b: 53                           	push	ebx
 11acd2c: 8b 5d 10                     	mov	ebx, dword ptr [ebp + 0x10]
 11acd2f: 56                           	push	esi
 11acd30: 57                           	push	edi
 11acd31: 8d 7b 28                     	lea	edi, [ebx + 0x28]
 11acd34: 8d 70 28                     	lea	esi, [eax + 0x28]
 11acd37: 8b 46 d8                     	mov	eax, dword ptr [esi - 0x28]
 11acd3a: 89 03                        	mov	dword ptr [ebx], eax
 11acd3c: 8b 4e dc                     	mov	ecx, dword ptr [esi - 0x24]
 11acd3f: 6a ff                        	push	-0x1
 11acd41: 6a 00                        	push	0x0
 11acd43: 8d 56 e0                     	lea	edx, [esi - 0x20]
 11acd46: 89 4f dc                     	mov	dword ptr [edi - 0x24], ecx
 11acd49: 52                           	push	edx
 11acd4a: 8d 4f e0                     	lea	ecx, [edi - 0x20]
 11acd4d: e8 de 85 25 ff               	call	0x405330
 11acd52: 8b 06                        	mov	eax, dword ptr [esi]
 11acd54: 89 07                        	mov	dword ptr [edi], eax
 11acd56: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
 11acd59: 89 4f 04                     	mov	dword ptr [edi + 0x4], ecx
 11acd5c: 8b 56 08                     	mov	edx, dword ptr [esi + 0x8]
 11acd5f: 89 57 08                     	mov	dword ptr [edi + 0x8], edx
 11acd62: 8b 46 0c                     	mov	eax, dword ptr [esi + 0xc]
 11acd65: 89 47 0c                     	mov	dword ptr [edi + 0xc], eax
 11acd68: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11acd6b: 83 c6 3c                     	add	esi, 0x3c
 11acd6e: 89 4f 10                     	mov	dword ptr [edi + 0x10], ecx
 11acd71: 8d 56 d8                     	lea	edx, [esi - 0x28]
 11acd74: 83 c3 3c                     	add	ebx, 0x3c
 11acd77: 83 c7 3c                     	add	edi, 0x3c
 11acd7a: 3b 55 0c                     	cmp	edx, dword ptr [ebp + 0xc]
 11acd7d: 75 b8                        	jne	0x11acd37 <.text+0x1f7>
 11acd7f: 5f                           	pop	edi
 11acd80: 5e                           	pop	esi
 11acd81: 8b c3                        	mov	eax, ebx
 11acd83: 5b                           	pop	ebx
 11acd84: 5d                           	pop	ebp
 11acd85: c3                           	ret
 11acd86: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11acd89: 5d                           	pop	ebp
 11acd8a: c3                           	ret
 11acd8b: cc                           	int3
 11acd8c: cc                           	int3
 11acd8d: cc                           	int3
 11acd8e: cc                           	int3
 11acd8f: cc                           	int3
 11acd90: 55                           	push	ebp
 11acd91: 8b ec                        	mov	ebp, esp
 11acd93: 83 ec 18                     	sub	esp, 0x18
 11acd96: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11acd99: 56                           	push	esi
 11acd9a: 8b f1                        	mov	esi, ecx
 11acd9c: 50                           	push	eax
 11acd9d: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
