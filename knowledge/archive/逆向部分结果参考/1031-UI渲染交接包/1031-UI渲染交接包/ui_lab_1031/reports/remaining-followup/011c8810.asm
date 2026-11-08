
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c8810 <.text>:
 11c8810: 55                           	push	ebp
 11c8811: 8b ec                        	mov	ebp, esp
 11c8813: 83 ec 0c                     	sub	esp, 0xc
 11c8816: 80 3d 80 22 a4 01 00         	cmp	byte ptr [0x1a42280], 0x0
 11c881d: c6 45 ff 00                  	mov	byte ptr [ebp - 0x1], 0x0
 11c8821: c6 05 1c 65 b5 01 00         	mov	byte ptr [0x1b5651c], 0x0
 11c8828: 0f 84 d2 02 00 00            	je	0x11c8b00 <.text+0x2f0>
 11c882e: 53                           	push	ebx
 11c882f: 56                           	push	esi
 11c8830: bb 01 00 00 00               	mov	ebx, 0x1
 11c8835: 57                           	push	edi
 11c8836: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 11c8839: 38 1d 24 65 b5 01            	cmp	byte ptr [0x1b56524], bl
 11c883f: 0f 85 f5 00 00 00            	jne	0x11c893a <.text+0x12a>
 11c8845: 8b 0d 28 65 b5 01            	mov	ecx, dword ptr [0x1b56528]
 11c884b: e8 e0 a9 76 01               	call	0x2933230 <.text+0x176aa20>
 11c8850: 8b 0d 28 65 b5 01            	mov	ecx, dword ptr [0x1b56528]
 11c8856: 83 c1 20                     	add	ecx, 0x20
 11c8859: 8d 45 f8                     	lea	eax, [ebp - 0x8]
 11c885c: 50                           	push	eax
 11c885d: 8d 51 08                     	lea	edx, [ecx + 0x8]
 11c8860: 52                           	push	edx
 11c8861: e8 7a 85 fd ff               	call	0x11a0de0
 11c8866: 8b 75 f8                     	mov	esi, dword ptr [ebp - 0x8]
 11c8869: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c886c: 50                           	push	eax
 11c886d: 68 54 65 b5 01               	push	0x1b56554
 11c8872: b9 4c 65 b5 01               	mov	ecx, 0x1b5654c
 11c8877: e8 64 85 fd ff               	call	0x11a0de0
 11c887c: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c887f: 03 ce                        	add	ecx, esi
 11c8881: 89 0d 04 65 b5 01            	mov	dword ptr [0x1b56504], ecx
 11c8887: 8b 0d 28 65 b5 01            	mov	ecx, dword ptr [0x1b56528]
 11c888d: 83 c1 2c                     	add	ecx, 0x2c
 11c8890: 8d 55 f4                     	lea	edx, [ebp - 0xc]
 11c8893: 52                           	push	edx
 11c8894: 8d 41 08                     	lea	eax, [ecx + 0x8]
 11c8897: 50                           	push	eax
 11c8898: e8 43 85 fd ff               	call	0x11a0de0
 11c889d: 8b 75 f4                     	mov	esi, dword ptr [ebp - 0xc]
 11c88a0: 8d 4d f8                     	lea	ecx, [ebp - 0x8]
 11c88a3: 51                           	push	ecx
 11c88a4: 68 60 65 b5 01               	push	0x1b56560
 11c88a9: b9 58 65 b5 01               	mov	ecx, 0x1b56558
 11c88ae: e8 2d 85 fd ff               	call	0x11a0de0
 11c88b3: 03 75 f8                     	add	esi, dword ptr [ebp - 0x8]
 11c88b6: 80 3d 1e 65 b5 01 00         	cmp	byte ptr [0x1b5651e], 0x0
 11c88bd: 89 35 08 65 b5 01            	mov	dword ptr [0x1b56508], esi
 11c88c3: 0f 85 b3 01 00 00            	jne	0x11c8a7c <.text+0x26c>
 11c88c9: 8b 0d 28 65 b5 01            	mov	ecx, dword ptr [0x1b56528]
 11c88cf: 8a 41 18                     	mov	al, byte ptr [ecx + 0x18]
 11c88d2: c0 e8 07                     	shr	al, 0x7
 11c88d5: 38 05 19 65 b5 01            	cmp	byte ptr [0x1b56519], al
 11c88db: 74 23                        	je	0x11c8900 <.text+0xf0>
 11c88dd: 0f b6 d0                     	movzx	edx, al
 11c88e0: f7 da                        	neg	edx
 11c88e2: 1b d2                        	sbb	edx, edx
 11c88e4: 83 e2 f9                     	and	edx, -0x7
 11c88e7: 83 c2 08                     	add	edx, 0x8
 11c88ea: a2 18 65 b5 01               	mov	byte ptr [0x1b56518], al
 11c88ef: 89 15 0c 65 b5 01            	mov	dword ptr [0x1b5650c], edx
 11c88f5: a2 19 65 b5 01               	mov	byte ptr [0x1b56519], al
 11c88fa: 88 1d 1c 65 b5 01            	mov	byte ptr [0x1b5651c], bl
 11c8900: 8a 41 19                     	mov	al, byte ptr [ecx + 0x19]
 11c8903: c0 e8 07                     	shr	al, 0x7
 11c8906: 38 05 1b 65 b5 01            	cmp	byte ptr [0x1b5651b], al
 11c890c: 0f 84 6a 01 00 00            	je	0x11c8a7c <.text+0x26c>
 11c8912: 0f b6 c8                     	movzx	ecx, al
 11c8915: f7 d9                        	neg	ecx
 11c8917: 1b c9                        	sbb	ecx, ecx
 11c8919: 83 e1 f2                     	and	ecx, -0xe
 11c891c: 83 c1 10                     	add	ecx, 0x10
 11c891f: a2 1a 65 b5 01               	mov	byte ptr [0x1b5651a], al
 11c8924: 89 0d 10 65 b5 01            	mov	dword ptr [0x1b56510], ecx
 11c892a: a2 1b 65 b5 01               	mov	byte ptr [0x1b5651b], al
 11c892f: 88 1d 1c 65 b5 01            	mov	byte ptr [0x1b5651c], bl
 11c8935: e9 42 01 00 00               	jmp	0x11c8a7c <.text+0x26c>
 11c893a: 81 ff 0a 02 00 00            	cmp	edi, 0x20a
 11c8940: 74 43                        	je	0x11c8985 <.text+0x175>
 11c8942: 8d 55 f4                     	lea	edx, [ebp - 0xc]
 11c8945: 52                           	push	edx
 11c8946: 68 54 65 b5 01               	push	0x1b56554
 11c894b: b9 4c 65 b5 01               	mov	ecx, 0x1b5654c
 11c8950: e8 8b 84 fd ff               	call	0x11a0de0
 11c8955: 8b 75 10                     	mov	esi, dword ptr [ebp + 0x10]
 11c8958: 0f bf c6                     	movsx	eax, si
 11c895b: 03 45 f4                     	add	eax, dword ptr [ebp - 0xc]
 11c895e: 8d 4d f4                     	lea	ecx, [ebp - 0xc]
 11c8961: 51                           	push	ecx
 11c8962: 68 60 65 b5 01               	push	0x1b56560
 11c8967: b9 58 65 b5 01               	mov	ecx, 0x1b56558
 11c896c: a3 04 65 b5 01               	mov	dword ptr [0x1b56504], eax
 11c8971: e8 6a 84 fd ff               	call	0x11a0de0
 11c8976: c1 ee 10                     	shr	esi, 0x10
 11c8979: 0f bf d6                     	movsx	edx, si
 11c897c: 03 55 f4                     	add	edx, dword ptr [ebp - 0xc]
 11c897f: 89 15 08 65 b5 01            	mov	dword ptr [0x1b56508], edx
 11c8985: 80 3d 1e 65 b5 01 00         	cmp	byte ptr [0x1b5651e], 0x0
 11c898c: 0f 85 dc 00 00 00            	jne	0x11c8a6e <.text+0x25e>
 11c8992: 81 ff 01 02 00 00            	cmp	edi, 0x201
 11c8998: 77 38                        	ja	0x11c89d2 <.text+0x1c2>
 11c899a: 74 1f                        	je	0x11c89bb <.text+0x1ab>
 11c899c: 8b c7                        	mov	eax, edi
 11c899e: 83 e8 00                     	sub	eax, 0x0
 11c89a1: 74 10                        	je	0x11c89b3 <.text+0x1a3>
 11c89a3: 2b c3                        	sub	eax, ebx
 11c89a5: 0f 85 d1 00 00 00            	jne	0x11c8a7c <.text+0x26c>
 11c89ab: 88 45 ff                     	mov	byte ptr [ebp - 0x1], al
 11c89ae: e9 c9 00 00 00               	jmp	0x11c8a7c <.text+0x26c>
 11c89b3: 88 5d ff                     	mov	byte ptr [ebp - 0x1], bl
 11c89b6: e9 c1 00 00 00               	jmp	0x11c8a7c <.text+0x26c>
 11c89bb: 89 1d 0c 65 b5 01            	mov	dword ptr [0x1b5650c], ebx
 11c89c1: 88 1d 18 65 b5 01            	mov	byte ptr [0x1b56518], bl
 11c89c7: 88 1d 1c 65 b5 01            	mov	byte ptr [0x1b5651c], bl
 11c89cd: e9 aa 00 00 00               	jmp	0x11c8a7c <.text+0x26c>
 11c89d2: 8d 87 fe fd ff ff            	lea	eax, [edi - 0x202]
 11c89d8: 83 f8 08                     	cmp	eax, 0x8
 11c89db: 0f 87 9b 00 00 00            	ja	0x11c8a7c <.text+0x26c>
 11c89e1: ff 24 85 04 8b 1c 01         	jmp	dword ptr [4*eax + 0x11c8b04]
 11c89e8: c7 05 10 65 b5 01 02 00 00 00	mov	dword ptr [0x1b56510], 0x2
 11c89f2: 88 1d 1a 65 b5 01            	mov	byte ptr [0x1b5651a], bl
 11c89f8: 88 1d 1c 65 b5 01            	mov	byte ptr [0x1b5651c], bl
 11c89fe: eb 7c                        	jmp	0x11c8a7c <.text+0x26c>
 11c8a00: c7 05 0c 65 b5 01 40 00 00 00	mov	dword ptr [0x1b5650c], 0x40
 11c8a0a: eb 70                        	jmp	0x11c8a7c <.text+0x26c>
 11c8a0c: c7 05 0c 65 b5 01 08 00 00 00	mov	dword ptr [0x1b5650c], 0x8
 11c8a16: c6 05 18 65 b5 01 00         	mov	byte ptr [0x1b56518], 0x0
 11c8a1d: 88 1d 1d 65 b5 01            	mov	byte ptr [0x1b5651d], bl
 11c8a23: eb 57                        	jmp	0x11c8a7c <.text+0x26c>
 11c8a25: c7 05 10 65 b5 01 10 00 00 00	mov	dword ptr [0x1b56510], 0x10
 11c8a2f: c6 05 1a 65 b5 01 00         	mov	byte ptr [0x1b5651a], 0x0
 11c8a36: 88 1d 1d 65 b5 01            	mov	byte ptr [0x1b5651d], bl
 11c8a3c: eb 3e                        	jmp	0x11c8a7c <.text+0x26c>
 11c8a3e: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c8a41: c1 e8 10                     	shr	eax, 0x10
 11c8a44: 98                           	cwde
 11c8a45: a3 2c 65 b5 01               	mov	dword ptr [0x1b5652c], eax
 11c8a4a: 85 c0                        	test	eax, eax
 11c8a4c: 7e 0f                        	jle	0x11c8a5d <.text+0x24d>
 11c8a4e: 88 1d 25 65 b5 01            	mov	byte ptr [0x1b56525], bl
 11c8a54: c6 05 26 65 b5 01 00         	mov	byte ptr [0x1b56526], 0x0
 11c8a5b: eb 1f                        	jmp	0x11c8a7c <.text+0x26c>
 11c8a5d: 79 1d                        	jns	0x11c8a7c <.text+0x26c>
 11c8a5f: c6 05 25 65 b5 01 00         	mov	byte ptr [0x1b56525], 0x0
 11c8a66: 88 1d 26 65 b5 01            	mov	byte ptr [0x1b56526], bl
 11c8a6c: eb 0e                        	jmp	0x11c8a7c <.text+0x26c>
 11c8a6e: 8d 4d 08                     	lea	ecx, [ebp + 0x8]
 11c8a71: 51                           	push	ecx
 11c8a72: b9 34 65 b5 01               	mov	ecx, 0x1b56534
 11c8a77: e8 b4 49 38 ff               	call	0x54d430
 11c8a7c: 8b 0d 20 65 b5 01            	mov	ecx, dword ptr [0x1b56520]
 11c8a82: 85 c9                        	test	ecx, ecx
 11c8a84: 74 0f                        	je	0x11c8a95 <.text+0x285>
 11c8a86: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11c8a89: 8b 11                        	mov	edx, dword ptr [ecx]
 11c8a8b: 8b 12                        	mov	edx, dword ptr [edx]
 11c8a8d: 50                           	push	eax
 11c8a8e: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c8a91: 50                           	push	eax
 11c8a92: 57                           	push	edi
 11c8a93: ff d2                        	call	edx
 11c8a95: 8b 0d fc 6f b5 01            	mov	ecx, dword ptr [0x1b56ffc]
 11c8a9b: 8b 01                        	mov	eax, dword ptr [ecx]
 11c8a9d: 8b 50 1c                     	mov	edx, dword ptr [eax + 0x1c]
 11c8aa0: ff d2                        	call	edx
 11c8aa2: 84 c0                        	test	al, al
 11c8aa4: 74 57                        	je	0x11c8afd <.text+0x2ed>
 11c8aa6: 80 7d ff 00                  	cmp	byte ptr [ebp - 0x1], 0x0
 11c8aaa: 75 51                        	jne	0x11c8afd <.text+0x2ed>
 11c8aac: 8b 0d 04 65 b5 01            	mov	ecx, dword ptr [0x1b56504]
 11c8ab2: 32 c0                        	xor	al, al
 11c8ab4: 81 f9 20 03 00 00            	cmp	ecx, 0x320
 11c8aba: 7e 0d                        	jle	0x11c8ac9 <.text+0x2b9>
 11c8abc: b9 20 03 00 00               	mov	ecx, 0x320
 11c8ac1: 89 0d 04 65 b5 01            	mov	dword ptr [0x1b56504], ecx
 11c8ac7: 8a c3                        	mov	al, bl
 11c8ac9: 8b 15 08 65 b5 01            	mov	edx, dword ptr [0x1b56508]
 11c8acf: 81 fa 58 02 00 00            	cmp	edx, 0x258
 11c8ad5: 7e 1a                        	jle	0x11c8af1 <.text+0x2e1>
 11c8ad7: ba 58 02 00 00               	mov	edx, 0x258
 11c8adc: 52                           	push	edx
 11c8add: 51                           	push	ecx
 11c8ade: 89 15 08 65 b5 01            	mov	dword ptr [0x1b56508], edx
 11c8ae4: ff 15 64 a4 55 01            	call	dword ptr [0x155a464]
 11c8aea: 5f                           	pop	edi
 11c8aeb: 5e                           	pop	esi
 11c8aec: 5b                           	pop	ebx
 11c8aed: 8b e5                        	mov	esp, ebp
 11c8aef: 5d                           	pop	ebp
 11c8af0: c3                           	ret
 11c8af1: 84 c0                        	test	al, al
 11c8af3: 74 08                        	je	0x11c8afd <.text+0x2ed>
 11c8af5: 52                           	push	edx
 11c8af6: 51                           	push	ecx
 11c8af7: ff 15 64 a4 55 01            	call	dword ptr [0x155a464]
 11c8afd: 5f                           	pop	edi
 11c8afe: 5e                           	pop	esi
 11c8aff: 5b                           	pop	ebx
 11c8b00: 8b e5                        	mov	esp, ebp
 11c8b02: 5d                           	pop	ebp
 11c8b03: c3                           	ret
