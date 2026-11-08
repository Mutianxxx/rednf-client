
<stdin>:	file format elf32-i386

Disassembly of section .text:

01072820 <.text>:
 1072820: 55                           	push	ebp
 1072821: 8b ec                        	mov	ebp, esp
 1072823: 6a ff                        	push	-0x1
 1072825: 68 b1 76 4b 01               	push	0x14b76b1
 107282a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1072830: 50                           	push	eax
 1072831: 81 ec 9c 00 00 00            	sub	esp, 0x9c
 1072837: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 107283c: 33 c5                        	xor	eax, ebp
 107283e: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 1072841: 53                           	push	ebx
 1072842: 56                           	push	esi
 1072843: 57                           	push	edi
 1072844: 50                           	push	eax
 1072845: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1072848: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 107284e: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 1072851: 8b f1                        	mov	esi, ecx
 1072853: 8b 4e 6c                     	mov	ecx, dword ptr [esi + 0x6c]
 1072856: 2b 4e 68                     	sub	ecx, dword ptr [esi + 0x68]
 1072859: 89 75 c8                     	mov	dword ptr [ebp - 0x38], esi
 107285c: c1 f9 02                     	sar	ecx, 0x2
 107285f: 89 45 b8                     	mov	dword ptr [ebp - 0x48], eax
 1072862: 83 f9 0b                     	cmp	ecx, 0xb
 1072865: 73 07                        	jae	0x107286e <.text+0x4e>
 1072867: 33 c0                        	xor	eax, eax
 1072869: e9 06 05 00 00               	jmp	0x1072d74 <.text+0x554>
 107286e: 8b 4e 54                     	mov	ecx, dword ptr [esi + 0x54]
 1072871: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
 1072874: 2b c1                        	sub	eax, ecx
 1072876: c1 f8 05                     	sar	eax, 0x5
 1072879: 83 f8 01                     	cmp	eax, 0x1
 107287c: 72 e9                        	jb	0x1072867 <.text+0x47>
 107287e: 33 db                        	xor	ebx, ebx
 1072880: 3b c3                        	cmp	eax, ebx
 1072882: 77 05                        	ja	0x1072889 <.text+0x69>
 1072884: e8 1e 45 36 00               	call	0x13d6da7 <.text+0x364587>
 1072889: 83 79 18 08                  	cmp	dword ptr [ecx + 0x18], 0x8
 107288d: 72 05                        	jb	0x1072894 <.text+0x74>
 107288f: 8b 49 04                     	mov	ecx, dword ptr [ecx + 0x4]
 1072892: eb 03                        	jmp	0x1072897 <.text+0x77>
 1072894: 83 c1 04                     	add	ecx, 0x4
 1072897: a1 e4 64 b5 01               	mov	eax, dword ptr [0x1b564e4]
 107289c: 8b 10                        	mov	edx, dword ptr [eax]
 107289e: 51                           	push	ecx
 107289f: 8b c8                        	mov	ecx, eax
 10728a1: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 10728a4: ff d0                        	call	eax
 10728a6: 89 45 cc                     	mov	dword ptr [ebp - 0x34], eax
 10728a9: 3b c3                        	cmp	eax, ebx
 10728ab: 74 ba                        	je	0x1072867 <.text+0x47>
 10728ad: 8b 4e 54                     	mov	ecx, dword ptr [esi + 0x54]
 10728b0: 8b 46 58                     	mov	eax, dword ptr [esi + 0x58]
 10728b3: 2b c1                        	sub	eax, ecx
 10728b5: ba 01 00 00 00               	mov	edx, 0x1
 10728ba: c1 f8 05                     	sar	eax, 0x5
 10728bd: 89 5d b4                     	mov	dword ptr [ebp - 0x4c], ebx
 10728c0: 89 55 bc                     	mov	dword ptr [ebp - 0x44], edx
 10728c3: 3b c2                        	cmp	eax, edx
 10728c5: 0f 86 a6 02 00 00            	jbe	0x1072b71 <.text+0x351>
 10728cb: be 20 00 00 00               	mov	esi, 0x20
 10728d0: 89 75 b0                     	mov	dword ptr [ebp - 0x50], esi
 10728d3: 3b d0                        	cmp	edx, eax
 10728d5: 73 ad                        	jae	0x1072884 <.text+0x64>
 10728d7: 6a 08                        	push	0x8
 10728d9: 03 f1                        	add	esi, ecx
 10728db: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 10728de: e8 37 42 36 00               	call	0x13d6b1a <.text+0x3642fa>
 10728e3: 83 c4 04                     	add	esp, 0x4
 10728e6: 3b c3                        	cmp	eax, ebx
 10728e8: 0f 84 f1 02 00 00            	je	0x1072bdf <.text+0x3bf>
 10728ee: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
 10728f1: 33 c9                        	xor	ecx, ecx
 10728f3: 33 d2                        	xor	edx, edx
 10728f5: 89 08                        	mov	dword ptr [eax], ecx
 10728f7: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 10728fa: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 10728fd: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1072900: 89 0a                        	mov	dword ptr [edx], ecx
 1072902: 6a ff                        	push	-0x1
 1072904: 53                           	push	ebx
 1072905: 33 c0                        	xor	eax, eax
 1072907: 56                           	push	esi
 1072908: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 107290b: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 1072912: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 1072915: 66 89 45 d4                  	mov	word ptr [ebp - 0x2c], ax
 1072919: e8 12 2a 39 ff               	call	0x405330
 107291e: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 1072925: eb 09                        	jmp	0x1072930 <.text+0x110>
 1072927: 8d a4 24 00 00 00 00         	lea	esp, [esp]
 107292e: 8b ff                        	mov	edi, edi
 1072930: f6 05 08 84 af 01 01         	test	byte ptr [0x1af8408], 0x1
 1072937: 0f 85 94 00 00 00            	jne	0x10729d1 <.text+0x1b1>
 107293d: 83 0d 08 84 af 01 01         	or	dword ptr [0x1af8408], 0x1
 1072944: 6a 08                        	push	0x8
 1072946: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 107294a: 89 1d f4 83 af 01            	mov	dword ptr [0x1af83f4], ebx
 1072950: e8 c5 41 36 00               	call	0x13d6b1a <.text+0x3642fa>
 1072955: 83 c4 04                     	add	esp, 0x4
 1072958: 3b c3                        	cmp	eax, ebx
 107295a: 0f 84 5b 02 00 00            	je	0x1072bbb <.text+0x39b>
 1072960: a3 f4 83 af 01               	mov	dword ptr [0x1af83f4], eax
 1072965: 33 c9                        	xor	ecx, ecx
 1072967: 33 d2                        	xor	edx, edx
 1072969: 89 08                        	mov	dword ptr [eax], ecx
 107296b: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 107296e: 8b 0d f4 83 af 01            	mov	ecx, dword ptr [0x1af83f4]
 1072974: c7 01 f4 83 af 01            	mov	dword ptr [ecx], 0x1af83f4
 107297a: 6a 18                        	push	0x18
 107297c: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 1072980: 89 1d 00 84 af 01            	mov	dword ptr [0x1af8400], ebx
 1072986: e8 8f 41 36 00               	call	0x13d6b1a <.text+0x3642fa>
 107298b: 83 c4 04                     	add	esp, 0x4
 107298e: 3b c3                        	cmp	eax, ebx
 1072990: 0f 84 01 02 00 00            	je	0x1072b97 <.text+0x377>
 1072996: a3 fc 83 af 01               	mov	dword ptr [0x1af83fc], eax
 107299b: 89 00                        	mov	dword ptr [eax], eax
 107299d: a1 fc 83 af 01               	mov	eax, dword ptr [0x1af83fc]
 10729a2: 89 40 04                     	mov	dword ptr [eax + 0x4], eax
 10729a5: a1 fc 83 af 01               	mov	eax, dword ptr [0x1af83fc]
 10729aa: 89 40 08                     	mov	dword ptr [eax + 0x8], eax
 10729ad: 8b 15 fc 83 af 01            	mov	edx, dword ptr [0x1af83fc]
 10729b3: c6 42 14 01                  	mov	byte ptr [edx + 0x14], 0x1
 10729b7: a1 fc 83 af 01               	mov	eax, dword ptr [0x1af83fc]
 10729bc: 68 80 06 55 01               	push	0x1550680
 10729c1: c6 40 15 01                  	mov	byte ptr [eax + 0x15], 0x1
 10729c5: e8 40 49 36 00               	call	0x13d730a <.text+0x364aea>
 10729ca: 83 c4 04                     	add	esp, 0x4
 10729cd: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 10729d1: f6 05 08 84 af 01 02         	test	byte ptr [0x1af8408], 0x2
 10729d8: 75 26                        	jne	0x1072a00 <.text+0x1e0>
 10729da: 83 0d 08 84 af 01 02         	or	dword ptr [0x1af8408], 0x2
 10729e1: b9 f0 83 af 01               	mov	ecx, 0x1af83f0
 10729e6: c6 45 fc 04                  	mov	byte ptr [ebp - 0x4], 0x4
 10729ea: e8 61 27 13 00               	call	0x11a5150 <.text+0x132930>
 10729ef: 68 e0 02 55 01               	push	0x15502e0
 10729f4: e8 11 49 36 00               	call	0x13d730a <.text+0x364aea>
 10729f9: 83 c4 04                     	add	esp, 0x4
 10729fc: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1072a00: 38 1d ec 83 af 01            	cmp	byte ptr [0x1af83ec], bl
 1072a06: 0f 84 be 00 00 00            	je	0x1072aca <.text+0x2aa>
 1072a0c: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1072a0f: e8 0c f2 38 ff               	call	0x401c20
 1072a14: 8d 4d c4                     	lea	ecx, [ebp - 0x3c]
 1072a17: 51                           	push	ecx
 1072a18: 8d 95 68 ff ff ff            	lea	edx, [ebp - 0x98]
 1072a1e: 52                           	push	edx
 1072a1f: b9 f4 83 af 01               	mov	ecx, 0x1af83f4
 1072a24: 89 45 c4                     	mov	dword ptr [ebp - 0x3c], eax
 1072a27: e8 e4 5c 3e ff               	call	0x458710
 1072a2c: 8b 08                        	mov	ecx, dword ptr [eax]
 1072a2e: 33 f6                        	xor	esi, esi
 1072a30: 3b cb                        	cmp	ecx, ebx
 1072a32: 74 08                        	je	0x1072a3c <.text+0x21c>
 1072a34: 8b 09                        	mov	ecx, dword ptr [ecx]
 1072a36: 3b cb                        	cmp	ecx, ebx
 1072a38: 74 02                        	je	0x1072a3c <.text+0x21c>
 1072a3a: 8b 31                        	mov	esi, dword ptr [ecx]
 1072a3c: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
 1072a3f: 8d 85 74 ff ff ff            	lea	eax, [ebp - 0x8c]
 1072a45: 50                           	push	eax
 1072a46: b9 f4 83 af 01               	mov	ecx, 0x1af83f4
 1072a4b: e8 f0 18 75 ff               	call	0x7c4340
 1072a50: 3b f3                        	cmp	esi, ebx
 1072a52: 0f 84 2c fe ff ff            	je	0x1072884 <.text+0x64>
 1072a58: 8b 36                        	mov	esi, dword ptr [esi]
 1072a5a: 3b f3                        	cmp	esi, ebx
 1072a5c: 0f 84 22 fe ff ff            	je	0x1072884 <.text+0x64>
 1072a62: 8b 08                        	mov	ecx, dword ptr [eax]
 1072a64: 3b cb                        	cmp	ecx, ebx
 1072a66: 75 04                        	jne	0x1072a6c <.text+0x24c>
 1072a68: 33 c9                        	xor	ecx, ecx
 1072a6a: eb 02                        	jmp	0x1072a6e <.text+0x24e>
 1072a6c: 8b 09                        	mov	ecx, dword ptr [ecx]
 1072a6e: 3b f1                        	cmp	esi, ecx
 1072a70: 0f 85 0e fe ff ff            	jne	0x1072884 <.text+0x64>
 1072a76: 3b 78 08                     	cmp	edi, dword ptr [eax + 0x8]
 1072a79: 0f 94 c0                     	sete	al
 1072a7c: 3a c3                        	cmp	al, bl
 1072a7e: 0f 94 c0                     	sete	al
 1072a81: 3a c3                        	cmp	al, bl
 1072a83: 74 6d                        	je	0x1072af2 <.text+0x2d2>
 1072a85: 8b 7f 10                     	mov	edi, dword ptr [edi + 0x10]
 1072a88: 3b fb                        	cmp	edi, ebx
 1072a8a: 74 08                        	je	0x1072a94 <.text+0x274>
 1072a8c: 81 ff 79 09 00 00            	cmp	edi, 0x979
 1072a92: 75 5e                        	jne	0x1072af2 <.text+0x2d2>
 1072a94: 38 1d ec 83 af 01            	cmp	byte ptr [0x1af83ec], bl
 1072a9a: 75 4f                        	jne	0x1072aeb <.text+0x2cb>
 1072a9c: 68 2c f2 82 01               	push	0x182f22c
 1072aa1: e8 4a d4 12 00               	call	0x119fef0 <.text+0x12d6d0>
 1072aa6: 83 c4 04                     	add	esp, 0x4
 1072aa9: 8d 4d a4                     	lea	ecx, [ebp - 0x5c]
 1072aac: 51                           	push	ecx
 1072aad: 8d 95 58 ff ff ff            	lea	edx, [ebp - 0xa8]
 1072ab3: 52                           	push	edx
 1072ab4: b9 f4 83 af 01               	mov	ecx, 0x1af83f4
 1072ab9: 89 45 a4                     	mov	dword ptr [ebp - 0x5c], eax
 1072abc: c7 45 a8 79 09 00 00         	mov	dword ptr [ebp - 0x58], 0x979
 1072ac3: e8 08 61 3e ff               	call	0x458bd0
 1072ac8: eb 28                        	jmp	0x1072af2 <.text+0x2d2>
 1072aca: b9 f0 83 af 01               	mov	ecx, 0x1af83f0
 1072acf: e8 ec 20 13 00               	call	0x11a4bc0 <.text+0x1323a0>
 1072ad4: 38 1d ec 83 af 01            	cmp	byte ptr [0x1af83ec], bl
 1072ada: 74 c0                        	je	0x1072a9c <.text+0x27c>
 1072adc: b9 f0 83 af 01               	mov	ecx, 0x1af83f0
 1072ae1: e8 0a 21 13 00               	call	0x11a4bf0 <.text+0x1323d0>
 1072ae6: e9 45 fe ff ff               	jmp	0x1072930 <.text+0x110>
 1072aeb: c7 45 b4 01 00 00 00         	mov	dword ptr [ebp - 0x4c], 0x1
 1072af2: 38 1d ec 83 af 01            	cmp	byte ptr [0x1af83ec], bl
 1072af8: 75 16                        	jne	0x1072b10 <.text+0x2f0>
 1072afa: b9 f0 83 af 01               	mov	ecx, 0x1af83f0
 1072aff: e8 ec 20 13 00               	call	0x11a4bf0 <.text+0x1323d0>
 1072b04: c6 05 ec 83 af 01 01         	mov	byte ptr [0x1af83ec], 0x1
 1072b0b: e9 20 fe ff ff               	jmp	0x1072930 <.text+0x110>
 1072b10: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 1072b14: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1072b1b: 72 0c                        	jb	0x1072b29 <.text+0x309>
 1072b1d: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 1072b20: 50                           	push	eax
 1072b21: e8 01 30 36 00               	call	0x13d5b27 <.text+0x363307>
 1072b26: 83 c4 04                     	add	esp, 0x4
 1072b29: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 1072b2c: 33 c9                        	xor	ecx, ecx
 1072b2e: 52                           	push	edx
 1072b2f: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 1072b36: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 1072b39: 66 89 4d d4                  	mov	word ptr [ebp - 0x2c], cx
 1072b3d: e8 e5 2f 36 00               	call	0x13d5b27 <.text+0x363307>
 1072b42: 8b 45 c8                     	mov	eax, dword ptr [ebp - 0x38]
 1072b45: 8b 48 54                     	mov	ecx, dword ptr [eax + 0x54]
 1072b48: 8b 40 58                     	mov	eax, dword ptr [eax + 0x58]
 1072b4b: 8b 55 bc                     	mov	edx, dword ptr [ebp - 0x44]
 1072b4e: 8b 75 b0                     	mov	esi, dword ptr [ebp - 0x50]
 1072b51: 2b c1                        	sub	eax, ecx
 1072b53: 42                           	inc	edx
 1072b54: 83 c6 20                     	add	esi, 0x20
 1072b57: c1 f8 05                     	sar	eax, 0x5
 1072b5a: 83 c4 04                     	add	esp, 0x4
 1072b5d: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 1072b60: 89 55 bc                     	mov	dword ptr [ebp - 0x44], edx
 1072b63: 89 75 b0                     	mov	dword ptr [ebp - 0x50], esi
 1072b66: 3b d0                        	cmp	edx, eax
 1072b68: 0f 82 69 fd ff ff            	jb	0x10728d7 <.text+0xb7>
 1072b6e: 8b 75 c8                     	mov	esi, dword ptr [ebp - 0x38]
 1072b71: 68 bc 02 00 00               	push	0x2bc
 1072b76: e8 05 d8 13 00               	call	0x11b0380 <.text+0x13db60>
 1072b7b: 83 c4 04                     	add	esp, 0x4
 1072b7e: 89 45 c0                     	mov	dword ptr [ebp - 0x40], eax
 1072b81: c7 45 fc 05 00 00 00         	mov	dword ptr [ebp - 0x4], 0x5
 1072b88: 3b c3                        	cmp	eax, ebx
 1072b8a: 74 77                        	je	0x1072c03 <.text+0x3e3>
 1072b8c: 8b c8                        	mov	ecx, eax
 1072b8e: e8 4d 6d 17 00               	call	0x11e98e0 <.text+0x1770c0>
 1072b93: 8b f8                        	mov	edi, eax
 1072b95: eb 6e                        	jmp	0x1072c05 <.text+0x3e5>
 1072b97: 8d 45 c4                     	lea	eax, [ebp - 0x3c]
 1072b9a: 50                           	push	eax
 1072b9b: 8d 4d 98                     	lea	ecx, [ebp - 0x68]
 1072b9e: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
 1072ba1: e8 24 39 36 00               	call	0x13d64ca <.text+0x363caa>
 1072ba6: 68 90 0f 91 01               	push	0x1910f90
 1072bab: 8d 4d 98                     	lea	ecx, [ebp - 0x68]
 1072bae: 51                           	push	ecx
 1072baf: c7 45 98 84 20 56 01         	mov	dword ptr [ebp - 0x68], 0x1562084
 1072bb6: e8 df 3f 36 00               	call	0x13d6b9a <.text+0x36437a>
 1072bbb: 8d 55 ac                     	lea	edx, [ebp - 0x54]
 1072bbe: 52                           	push	edx
 1072bbf: 8d 4d 8c                     	lea	ecx, [ebp - 0x74]
 1072bc2: 89 5d ac                     	mov	dword ptr [ebp - 0x54], ebx
 1072bc5: e8 00 39 36 00               	call	0x13d64ca <.text+0x363caa>
 1072bca: 68 90 0f 91 01               	push	0x1910f90
 1072bcf: 8d 45 8c                     	lea	eax, [ebp - 0x74]
 1072bd2: 50                           	push	eax
 1072bd3: c7 45 8c 84 20 56 01         	mov	dword ptr [ebp - 0x74], 0x1562084
 1072bda: e8 bb 3f 36 00               	call	0x13d6b9a <.text+0x36437a>
 1072bdf: 8d 4d c0                     	lea	ecx, [ebp - 0x40]
 1072be2: 51                           	push	ecx
 1072be3: 8d 4d 80                     	lea	ecx, [ebp - 0x80]
 1072be6: 89 5d c0                     	mov	dword ptr [ebp - 0x40], ebx
 1072be9: e8 dc 38 36 00               	call	0x13d64ca <.text+0x363caa>
 1072bee: 68 90 0f 91 01               	push	0x1910f90
 1072bf3: 8d 55 80                     	lea	edx, [ebp - 0x80]
 1072bf6: 52                           	push	edx
 1072bf7: c7 45 80 84 20 56 01         	mov	dword ptr [ebp - 0x80], 0x1562084
 1072bfe: e8 97 3f 36 00               	call	0x13d6b9a <.text+0x36437a>
 1072c03: 33 ff                        	xor	edi, edi
 1072c05: 8b 4d b8                     	mov	ecx, dword ptr [ebp - 0x48]
 1072c08: 6a 01                        	push	0x1
 1072c0a: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1072c11: e8 ea b6 14 00               	call	0x11be300 <.text+0x14bae0>
 1072c16: 03 46 4c                     	add	eax, dword ptr [esi + 0x4c]
 1072c19: 8b 4d b8                     	mov	ecx, dword ptr [ebp - 0x48]
 1072c1c: 50                           	push	eax
 1072c1d: e8 3e d3 3b ff               	call	0x42ff60
 1072c22: 03 46 48                     	add	eax, dword ptr [esi + 0x48]
 1072c25: 8b cf                        	mov	ecx, edi
 1072c27: 50                           	push	eax
 1072c28: e8 a3 be 14 00               	call	0x11bead0 <.text+0x14c2b0>
 1072c2d: 8b 45 c8                     	mov	eax, dword ptr [ebp - 0x38]
 1072c30: 8b 40 6c                     	mov	eax, dword ptr [eax + 0x6c]
 1072c33: 8b 76 68                     	mov	esi, dword ptr [esi + 0x68]
 1072c36: 2b c6                        	sub	eax, esi
 1072c38: c1 f8 02                     	sar	eax, 0x2
 1072c3b: 83 f8 0a                     	cmp	eax, 0xa
 1072c3e: 77 05                        	ja	0x1072c45 <.text+0x425>
 1072c40: e8 62 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c45: 83 f8 09                     	cmp	eax, 0x9
 1072c48: 77 05                        	ja	0x1072c4f <.text+0x42f>
 1072c4a: e8 58 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c4f: 83 f8 08                     	cmp	eax, 0x8
 1072c52: 77 05                        	ja	0x1072c59 <.text+0x439>
 1072c54: e8 4e 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c59: 83 f8 07                     	cmp	eax, 0x7
 1072c5c: 77 05                        	ja	0x1072c63 <.text+0x443>
 1072c5e: e8 44 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c63: 83 f8 06                     	cmp	eax, 0x6
 1072c66: 77 05                        	ja	0x1072c6d <.text+0x44d>
 1072c68: e8 3a 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c6d: 83 f8 05                     	cmp	eax, 0x5
 1072c70: 77 05                        	ja	0x1072c77 <.text+0x457>
 1072c72: e8 30 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c77: 83 f8 04                     	cmp	eax, 0x4
 1072c7a: 77 05                        	ja	0x1072c81 <.text+0x461>
 1072c7c: e8 26 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c81: 83 f8 03                     	cmp	eax, 0x3
 1072c84: 77 05                        	ja	0x1072c8b <.text+0x46b>
 1072c86: e8 1c 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c8b: 83 f8 02                     	cmp	eax, 0x2
 1072c8e: 77 05                        	ja	0x1072c95 <.text+0x475>
 1072c90: e8 12 41 36 00               	call	0x13d6da7 <.text+0x364587>
 1072c95: 8b 4e 28                     	mov	ecx, dword ptr [esi + 0x28]
 1072c98: 51                           	push	ecx
 1072c99: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072c9c: e8 2f 1f 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072ca1: 8b 56 24                     	mov	edx, dword ptr [esi + 0x24]
 1072ca4: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072ca7: 50                           	push	eax
 1072ca8: 52                           	push	edx
 1072ca9: e8 22 1f 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072cae: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072cb1: 50                           	push	eax
 1072cb2: 8b 46 20                     	mov	eax, dword ptr [esi + 0x20]
 1072cb5: 50                           	push	eax
 1072cb6: e8 15 1f 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072cbb: 8b 4e 1c                     	mov	ecx, dword ptr [esi + 0x1c]
 1072cbe: 50                           	push	eax
 1072cbf: 51                           	push	ecx
 1072cc0: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072cc3: e8 08 1f 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072cc8: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 1072ccb: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072cce: 50                           	push	eax
 1072ccf: 52                           	push	edx
 1072cd0: e8 fb 1e 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072cd5: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072cd8: 50                           	push	eax
 1072cd9: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 1072cdc: 50                           	push	eax
 1072cdd: e8 ee 1e 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072ce2: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 1072ce5: 50                           	push	eax
 1072ce6: 51                           	push	ecx
 1072ce7: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072cea: e8 e1 1e 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072cef: 8b 56 0c                     	mov	edx, dword ptr [esi + 0xc]
 1072cf2: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072cf5: 50                           	push	eax
 1072cf6: 52                           	push	edx
 1072cf7: e8 d4 1e 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072cfc: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
 1072cff: 50                           	push	eax
 1072d00: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
 1072d03: 50                           	push	eax
 1072d04: e8 c7 1e 14 00               	call	0x11b4bd0 <.text+0x1423b0>
 1072d09: 50                           	push	eax
 1072d0a: 8b cf                        	mov	ecx, edi
 1072d0c: e8 9f 6e 17 00               	call	0x11e9bb0 <.text+0x177390>
 1072d11: 8b 75 b4                     	mov	esi, dword ptr [ebp - 0x4c]
 1072d14: 56                           	push	esi
 1072d15: 8b cf                        	mov	ecx, edi
 1072d17: e8 54 6c 17 00               	call	0x11e9970 <.text+0x177150>
 1072d1c: 8b 45 c8                     	mov	eax, dword ptr [ebp - 0x38]
 1072d1f: 8b 48 68                     	mov	ecx, dword ptr [eax + 0x68]
 1072d22: 8b 40 6c                     	mov	eax, dword ptr [eax + 0x6c]
 1072d25: 2b c1                        	sub	eax, ecx
 1072d27: c1 f8 02                     	sar	eax, 0x2
 1072d2a: 83 fe 01                     	cmp	esi, 0x1
 1072d2d: 75 22                        	jne	0x1072d51 <.text+0x531>
 1072d2f: 3b c6                        	cmp	eax, esi
 1072d31: 77 05                        	ja	0x1072d38 <.text+0x518>
 1072d33: e8 6f 40 36 00               	call	0x13d6da7 <.text+0x364587>
 1072d38: 3b c3                        	cmp	eax, ebx
 1072d3a: 77 05                        	ja	0x1072d41 <.text+0x521>
 1072d3c: e8 66 40 36 00               	call	0x13d6da7 <.text+0x364587>
 1072d41: 8b 51 04                     	mov	edx, dword ptr [ecx + 0x4]
 1072d44: 8b 01                        	mov	eax, dword ptr [ecx]
 1072d46: 52                           	push	edx
 1072d47: 50                           	push	eax
 1072d48: 8b cf                        	mov	ecx, edi
 1072d4a: e8 51 6c 17 00               	call	0x11e99a0 <.text+0x177180>
 1072d4f: eb 21                        	jmp	0x1072d72 <.text+0x552>
 1072d51: 83 f8 01                     	cmp	eax, 0x1
 1072d54: 77 05                        	ja	0x1072d5b <.text+0x53b>
 1072d56: e8 4c 40 36 00               	call	0x13d6da7 <.text+0x364587>
 1072d5b: 3b c3                        	cmp	eax, ebx
 1072d5d: 77 05                        	ja	0x1072d64 <.text+0x544>
 1072d5f: e8 43 40 36 00               	call	0x13d6da7 <.text+0x364587>
 1072d64: 8b 51 04                     	mov	edx, dword ptr [ecx + 0x4]
 1072d67: 8b 01                        	mov	eax, dword ptr [ecx]
 1072d69: 52                           	push	edx
 1072d6a: 50                           	push	eax
 1072d6b: 8b cf                        	mov	ecx, edi
 1072d6d: e8 fe b5 14 00               	call	0x11be370 <.text+0x14bb50>
 1072d72: 8b c7                        	mov	eax, edi
 1072d74: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1072d77: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1072d7e: 59                           	pop	ecx
 1072d7f: 5f                           	pop	edi
 1072d80: 5e                           	pop	esi
 1072d81: 5b                           	pop	ebx
 1072d82: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 1072d85: 33 cd                        	xor	ecx, ebp
 1072d87: e8 4c 44 36 00               	call	0x13d71d8 <.text+0x3649b8>
 1072d8c: 8b e5                        	mov	esp, ebp
 1072d8e: 5d                           	pop	ebp
 1072d8f: c2 04 00                     	ret	0x4
 1072d92: cc                           	int3
 1072d93: cc                           	int3
 1072d94: cc                           	int3
 1072d95: cc                           	int3
 1072d96: cc                           	int3
 1072d97: cc                           	int3
 1072d98: cc                           	int3
 1072d99: cc                           	int3
 1072d9a: cc                           	int3
 1072d9b: cc                           	int3
 1072d9c: cc                           	int3
 1072d9d: cc                           	int3
 1072d9e: cc                           	int3
 1072d9f: cc                           	int3
 1072da0: 55                           	push	ebp
 1072da1: 8b ec                        	mov	ebp, esp
 1072da3: 6a ff                        	push	-0x1
 1072da5: 68 11 77 4b 01               	push	0x14b7711
 1072daa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1072db0: 50                           	push	eax
 1072db1: 83 ec 70                     	sub	esp, 0x70
 1072db4: 53                           	push	ebx
 1072db5: 56                           	push	esi
 1072db6: 57                           	push	edi
 1072db7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1072dbc: 33 c5                        	xor	eax, ebp
 1072dbe: 50                           	push	eax
 1072dbf: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1072dc2: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1072dc8: 8b d1                        	mov	edx, ecx
 1072dca: 89 55 ec                     	mov	dword ptr [ebp - 0x14], edx
 1072dcd: 8b 4a 68                     	mov	ecx, dword ptr [edx + 0x68]
 1072dd0: 8b 42 6c                     	mov	eax, dword ptr [edx + 0x6c]
 1072dd3: 2b c1                        	sub	eax, ecx
 1072dd5: c1 f8 02                     	sar	eax, 0x2
 1072dd8: 33 db                        	xor	ebx, ebx
 1072dda: c7 45 dc 64 00 00 00         	mov	dword ptr [ebp - 0x24], 0x64
 1072de1: 3b c3                        	cmp	eax, ebx
 1072de3: 76 05                        	jbe	0x1072dea <.text+0x5ca>
 1072de5: 8b 31                        	mov	esi, dword ptr [ecx]
 1072de7: 89 75 dc                     	mov	dword ptr [ebp - 0x24], esi
 1072dea: c7 45 d8 96 00 00 00         	mov	dword ptr [ebp - 0x28], 0x96
 1072df1: 83 f8 01                     	cmp	eax, 0x1
 1072df4: 76 06                        	jbe	0x1072dfc <.text+0x5dc>
 1072df6: 8b 41 04                     	mov	eax, dword ptr [ecx + 0x4]
 1072df9: 89 45 d8                     	mov	dword ptr [ebp - 0x28], eax
 1072dfc: 8b 42 58                     	mov	eax, dword ptr [edx + 0x58]
 1072dff: 2b 42 54                     	sub	eax, dword ptr [edx + 0x54]
 1072e02: 33 c9                        	xor	ecx, ecx
 1072e04: c1 f8 05                     	sar	eax, 0x5
 1072e07: 88 5d f3                     	mov	byte ptr [ebp - 0xd], bl
 1072e0a: 89 45 d4                     	mov	dword ptr [ebp - 0x2c], eax
 1072e0d: 89 4d e4                     	mov	dword ptr [ebp - 0x1c], ecx
 1072e10: 3b c3                        	cmp	eax, ebx
 1072e12: 0f 8e 73 02 00 00            	jle	0x107308b <.text+0x86b>
 1072e18: 33 f6                        	xor	esi, esi
 1072e1a: 89 75 e0                     	mov	dword ptr [ebp - 0x20], esi
 1072e1d: 8d 49 00                     	lea	ecx, [ecx]
 1072e20: 8b 42 54                     	mov	eax, dword ptr [edx + 0x54]
 1072e23: 8b 52 58                     	mov	edx, dword ptr [edx + 0x58]
 1072e26: 2b d0                        	sub	edx, eax
 1072e28: c1 fa 05                     	sar	edx, 0x5
 1072e2b: 3b ca                        	cmp	ecx, edx
 1072e2d: 0f 83 0b 02 00 00            	jae	0x107303e <.text+0x81e>
 1072e33: 83 7c 06 18 08               	cmp	dword ptr [esi + eax + 0x18], 0x8
 1072e38: 72 09                        	jb	0x1072e43 <.text+0x623>
 1072e3a: 8b 44 06 04                  	mov	eax, dword ptr [esi + eax + 0x4]
 1072e3e: 89 45 e8                     	mov	dword ptr [ebp - 0x18], eax
 1072e41: eb 0d                        	jmp	0x1072e50 <.text+0x630>
 1072e43: 8d 4c 06 04                  	lea	ecx, [esi + eax + 0x4]
 1072e47: 89 4d e8                     	mov	dword ptr [ebp - 0x18], ecx
 1072e4a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 1072e50: f6 05 28 84 af 01 01         	test	byte ptr [0x1af8428], 0x1
 1072e57: 0f 85 96 00 00 00            	jne	0x1072ef3 <.text+0x6d3>
 1072e5d: 83 0d 28 84 af 01 01         	or	dword ptr [0x1af8428], 0x1
 1072e64: 6a 08                        	push	0x8
 1072e66: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 1072e69: 89 1d 14 84 af 01            	mov	dword ptr [0x1af8414], ebx
 1072e6f: e8 a6 3c 36 00               	call	0x13d6b1a <.text+0x3642fa>
 1072e74: 83 c4 04                     	add	esp, 0x4
 1072e77: 3b c3                        	cmp	eax, ebx
 1072e79: 0f 84 e8 01 00 00            	je	0x1073067 <.text+0x847>
 1072e7f: a3 14 84 af 01               	mov	dword ptr [0x1af8414], eax
 1072e84: 33 d2                        	xor	edx, edx
 1072e86: 33 c9                        	xor	ecx, ecx
 1072e88: 89 08                        	mov	dword ptr [eax], ecx
 1072e8a: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1072e8d: 8b 15 14 84 af 01            	mov	edx, dword ptr [0x1af8414]
 1072e93: c7 02 14 84 af 01            	mov	dword ptr [edx], 0x1af8414
 1072e99: 6a 18                        	push	0x18
 1072e9b: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1072e9f: 89 1d 20 84 af 01            	mov	dword ptr [0x1af8420], ebx
 1072ea5: e8 70 3c 36 00               	call	0x13d6b1a <.text+0x3642fa>
 1072eaa: 83 c4 04                     	add	esp, 0x4
 1072ead: 3b c3                        	cmp	eax, ebx
 1072eaf: 0f 84 8e 01 00 00            	je	0x1073043 <.text+0x823>
 1072eb5: a3 1c 84 af 01               	mov	dword ptr [0x1af841c], eax
 1072eba: 89 00                        	mov	dword ptr [eax], eax
 1072ebc: a1 1c 84 af 01               	mov	eax, dword ptr [0x1af841c]
 1072ec1: 89 40 04                     	mov	dword ptr [eax + 0x4], eax
 1072ec4: a1 1c 84 af 01               	mov	eax, dword ptr [0x1af841c]
 1072ec9: 89 40 08                     	mov	dword ptr [eax + 0x8], eax
 1072ecc: a1 1c 84 af 01               	mov	eax, dword ptr [0x1af841c]
 1072ed1: c6 40 14 01                  	mov	byte ptr [eax + 0x14], 0x1
 1072ed5: 8b 0d 1c 84 af 01            	mov	ecx, dword ptr [0x1af841c]
 1072edb: 68 f0 06 55 01               	push	0x15506f0
 1072ee0: c6 41 15 01                  	mov	byte ptr [ecx + 0x15], 0x1
 1072ee4: e8 21 44 36 00               	call	0x13d730a <.text+0x364aea>
 1072ee9: 83 c4 04                     	add	esp, 0x4
 1072eec: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1072ef3: f6 05 28 84 af 01 02         	test	byte ptr [0x1af8428], 0x2
 1072efa: 75 2c                        	jne	0x1072f28 <.text+0x708>
 1072efc: b8 02 00 00 00               	mov	eax, 0x2
 1072f01: 09 05 28 84 af 01            	or	dword ptr [0x1af8428], eax
 1072f07: b9 10 84 af 01               	mov	ecx, 0x1af8410
 1072f0c: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 1072f0f: e8 3c 22 13 00               	call	0x11a5150 <.text+0x132930>
 1072f14: 68 f0 02 55 01               	push	0x15502f0
 1072f19: e8 ec 43 36 00               	call	0x13d730a <.text+0x364aea>
 1072f1e: 83 c4 04                     	add	esp, 0x4
 1072f21: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1072f28: 38 1d 0c 84 af 01            	cmp	byte ptr [0x1af840c], bl
 1072f2e: 0f 84 aa 00 00 00            	je	0x1072fde <.text+0x7be>
 1072f34: 8d 55 e8                     	lea	edx, [ebp - 0x18]
 1072f37: 52                           	push	edx
 1072f38: 8d 45 a0                     	lea	eax, [ebp - 0x60]
 1072f3b: 50                           	push	eax
 1072f3c: b9 14 84 af 01               	mov	ecx, 0x1af8414
 1072f41: e8 ca 57 3e ff               	call	0x458710
 1072f46: 8b 08                        	mov	ecx, dword ptr [eax]
 1072f48: 33 f6                        	xor	esi, esi
 1072f4a: 3b cb                        	cmp	ecx, ebx
 1072f4c: 74 08                        	je	0x1072f56 <.text+0x736>
 1072f4e: 8b 09                        	mov	ecx, dword ptr [ecx]
 1072f50: 3b cb                        	cmp	ecx, ebx
 1072f52: 74 02                        	je	0x1072f56 <.text+0x736>
 1072f54: 8b 31                        	mov	esi, dword ptr [ecx]
 1072f56: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
 1072f59: 8d 4d 94                     	lea	ecx, [ebp - 0x6c]
 1072f5c: 51                           	push	ecx
 1072f5d: b9 14 84 af 01               	mov	ecx, 0x1af8414
 1072f62: e8 d9 13 75 ff               	call	0x7c4340
 1072f67: 3b f3                        	cmp	esi, ebx
 1072f69: 0f 84 cf 00 00 00            	je	0x107303e <.text+0x81e>
 1072f6f: 8b                           	<unknown>
