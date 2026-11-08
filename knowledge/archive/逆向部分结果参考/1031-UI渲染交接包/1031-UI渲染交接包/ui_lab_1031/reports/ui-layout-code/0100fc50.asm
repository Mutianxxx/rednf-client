
<stdin>:	file format elf32-i386

Disassembly of section .text:

0100fc50 <.text>:
 100fc50: 0f b6 56 64                  	movzx	edx, byte ptr [esi + 0x64]
 100fc54: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 100fc5a: 83 c4 10                     	add	esp, 0x10
 100fc5d: 52                           	push	edx
 100fc5e: 6a 00                        	push	0x0
 100fc60: 68 4b 01 00 00               	push	0x14b
 100fc65: e8 06 78 e6 ff               	call	0xe77470
 100fc6a: 8b f8                        	mov	edi, eax
 100fc6c: 85 ff                        	test	edi, edi
 100fc6e: 74 33                        	je	0x100fca3 <.text+0x53>
 100fc70: 6a ff                        	push	-0x1
 100fc72: 6a 00                        	push	0x0
 100fc74: 53                           	push	ebx
 100fc75: b9 68 3a af 01               	mov	ecx, 0x1af3a68
 100fc7a: e8 b1 56 3f ff               	call	0x405330
 100fc7f: 83 ec 20                     	sub	esp, 0x20
 100fc82: 8d 46 44                     	lea	eax, [esi + 0x44]
 100fc85: 8b cc                        	mov	ecx, esp
 100fc87: 89 a5 ec fe ff ff            	mov	dword ptr [ebp - 0x114], esp
 100fc8d: 50                           	push	eax
 100fc8e: e8 2d 0c 40 ff               	call	0x4108c0
 100fc93: 8b cf                        	mov	ecx, edi
 100fc95: e8 46 d8 ff ff               	call	0x100d4e0
 100fc9a: 8b 4e 3c                     	mov	ecx, dword ptr [esi + 0x3c]
 100fc9d: 89 8f a8 01 00 00            	mov	dword ptr [edi + 0x1a8], ecx
 100fca3: 8b ce                        	mov	ecx, esi
 100fca5: e8 36 bc ff ff               	call	0x100b8e0
 100fcaa: 6a 00                        	push	0x0
 100fcac: 6a 00                        	push	0x0
 100fcae: 6a ff                        	push	-0x1
 100fcb0: 68 b8 56 56 01               	push	0x15656b8
 100fcb5: e8 36 02 19 00               	call	0x119fef0 <.text+0x1902a0>
 100fcba: 83 c4 04                     	add	esp, 0x4
 100fcbd: 50                           	push	eax
 100fcbe: e8 9d 64 75 ff               	call	0x766160
 100fcc3: 8b 9d f0 fe ff ff            	mov	ebx, dword ptr [ebp - 0x110]
 100fcc9: bf 08 00 00 00               	mov	edi, 0x8
 100fcce: e9 ae 00 00 00               	jmp	0x100fd81 <.text+0x131>
 100fcd3: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
 100fcd9: 6a 41                        	push	0x41
 100fcdb: e8 50 2c 12 00               	call	0x1132930 <.text+0x122ce0>
 100fce0: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
 100fce6: 6a 17                        	push	0x17
 100fce8: e8 33 34 12 00               	call	0x1133120 <.text+0x1234d0>
 100fced: 39 7e 34                     	cmp	dword ptr [esi + 0x34], edi
 100fcf0: 72 05                        	jb	0x100fcf7 <.text+0xa7>
 100fcf2: 8b 46 20                     	mov	eax, dword ptr [esi + 0x20]
 100fcf5: eb 03                        	jmp	0x100fcfa <.text+0xaa>
 100fcf7: 8d 46 20                     	lea	eax, [esi + 0x20]
 100fcfa: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
 100fd00: 50                           	push	eax
 100fd01: e8 aa 35 12 00               	call	0x11332b0 <.text+0x123660>
 100fd06: e8 85 2d 12 00               	call	0x1132a90 <.text+0x122e40>
 100fd0b: 8b ce                        	mov	ecx, esi
 100fd0d: e8 ce bb ff ff               	call	0x100b8e0
 100fd12: eb 70                        	jmp	0x100fd84 <.text+0x134>
 100fd14: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
 100fd1a: 6a 41                        	push	0x41
 100fd1c: e8 0f 2c 12 00               	call	0x1132930 <.text+0x122ce0>
 100fd21: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
 100fd27: 6a 0c                        	push	0xc
 100fd29: e8 f2 33 12 00               	call	0x1133120 <.text+0x1234d0>
 100fd2e: 39 7e 34                     	cmp	dword ptr [esi + 0x34], edi
 100fd31: 0f 82 d8 fc ff ff            	jb	0x100fa0f
 100fd37: 8b 46 20                     	mov	eax, dword ptr [esi + 0x20]
 100fd3a: e9 d3 fc ff ff               	jmp	0x100fa12
 100fd3f: 39 7e 34                     	cmp	dword ptr [esi + 0x34], edi
 100fd42: 72 05                        	jb	0x100fd49 <.text+0xf9>
 100fd44: 8b 46 20                     	mov	eax, dword ptr [esi + 0x20]
 100fd47: eb 03                        	jmp	0x100fd4c <.text+0xfc>
 100fd49: 8d 46 20                     	lea	eax, [esi + 0x20]
 100fd4c: 8b 56 3c                     	mov	edx, dword ptr [esi + 0x3c]
 100fd4f: 52                           	push	edx
 100fd50: 50                           	push	eax
 100fd51: a1 50 f7 a6 01               	mov	eax, dword ptr [0x1a6f750]
 100fd56: 8b 88 7c 43 00 00            	mov	ecx, dword ptr [eax + 0x437c]
 100fd5c: e8 4f 92 f9 ff               	call	0xfa8fb0
 100fd61: 8b ce                        	mov	ecx, esi
 100fd63: e8 78 bb ff ff               	call	0x100b8e0
 100fd68: 6a 00                        	push	0x0
 100fd6a: 6a 00                        	push	0x0
 100fd6c: 6a ff                        	push	-0x1
 100fd6e: 68 b8 56 56 01               	push	0x15656b8
 100fd73: e8 78 01 19 00               	call	0x119fef0 <.text+0x1902a0>
 100fd78: 83 c4 04                     	add	esp, 0x4
 100fd7b: 50                           	push	eax
 100fd7c: e8 df 63 75 ff               	call	0x766160
 100fd81: 83 c4 10                     	add	esp, 0x10
 100fd84: 83 85 f4 fe ff ff 04         	add	dword ptr [ebp - 0x10c], 0x4
 100fd8b: 43                           	inc	ebx
 100fd8c: 8d 4b 06                     	lea	ecx, [ebx + 0x6]
 100fd8f: 89 9d f0 fe ff ff            	mov	dword ptr [ebp - 0x110], ebx
 100fd95: 83 f9 25                     	cmp	ecx, 0x25
 100fd98: 0f 8c 22 fb ff ff            	jl	0x100f8c0
 100fd9e: 5f                           	pop	edi
 100fd9f: 5e                           	pop	esi
 100fda0: 5b                           	pop	ebx
 100fda1: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 100fda4: 33 cd                        	xor	ecx, ebp
 100fda6: e8 2d 74 3c 00               	call	0x13d71d8 <.text+0x3c7588>
 100fdab: 8b e5                        	mov	esp, ebp
 100fdad: 5d                           	pop	ebp
 100fdae: c3                           	ret
 100fdaf: 6a 00                        	push	0x0
 100fdb1: 68 8e 94 00 00               	push	0x948e
 100fdb6: e8 a5 b4 21 00               	call	0x122b260 <.text+0x21b610>
 100fdbb: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 100fdc1: 83 c4 04                     	add	esp, 0x4
 100fdc4: 50                           	push	eax
 100fdc5: 68 10 01 00 00               	push	0x110
 100fdca: e8 a1 76 e6 ff               	call	0xe77470
 100fdcf: 5f                           	pop	edi
 100fdd0: 5e                           	pop	esi
 100fdd1: 5b                           	pop	ebx
 100fdd2: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 100fdd5: 33 cd                        	xor	ecx, ebp
 100fdd7: e8 fc 73 3c 00               	call	0x13d71d8 <.text+0x3c7588>
 100fddc: 8b e5                        	mov	esp, ebp
 100fdde: 5d                           	pop	ebp
 100fddf: c3                           	ret
 100fde0: 8b ce                        	mov	ecx, esi
 100fde2: e8 89 f6 ff ff               	call	0x100f470
 100fde7: 33 ff                        	xor	edi, edi
 100fde9: 8d 5e 6c                     	lea	ebx, [esi + 0x6c]
 100fdec: 8d 64 24 00                  	lea	esp, [esp]
 100fdf0: 8b 0b                        	mov	ecx, dword ptr [ebx]
 100fdf2: e8 c9 e1 1a 00               	call	0x11bdfc0 <.text+0x1ae370>
 100fdf7: 84 c0                        	test	al, al
 100fdf9: 74 08                        	je	0x100fe03 <.text+0x1b3>
 100fdfb: 57                           	push	edi
 100fdfc: 8b ce                        	mov	ecx, esi
 100fdfe: e8 00 67 86 01               	call	0x2876503 <.text+0x18668b3>
 100fe03: 47                           	inc	edi
 100fe04: 83 c3 04                     	add	ebx, 0x4
 100fe07: 83 ff 25                     	cmp	edi, 0x25
 100fe0a: 7c e4                        	jl	0x100fdf0 <.text+0x1a0>
 100fe0c: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 100fe0f: 5f                           	pop	edi
 100fe10: 5e                           	pop	esi
 100fe11: 33 cd                        	xor	ecx, ebp
 100fe13: 5b                           	pop	ebx
 100fe14: e8 bf 73 3c 00               	call	0x13d71d8 <.text+0x3c7588>
 100fe19: 8b e5                        	mov	esp, ebp
 100fe1b: 5d                           	pop	ebp
 100fe1c: c3                           	ret
 100fe1d: 8d 49 00                     	lea	ecx, [ecx]
 100fe20: 2f                           	das
 100fe21: f9                           	stc
 100fe22: 00 01                        	add	byte ptr [ecx], al
 100fe24: 9a fb 00 01 e5 f8 00         	lcall	0xf8, 0xe50100fb
 100fe2b: 01 df                        	add	edi, ebx
 100fe2d: f9                           	stc
 100fe2e: 00 01                        	add	byte ptr [ecx], al
 100fe30: 84 fd                        	test	ch, bh
 100fe32: 00 01                        	add	byte ptr [ecx], al
 100fe34: 0a f9                        	or	bh, cl
 100fe36: 00 01                        	add	byte ptr [ecx], al
 100fe38: 84 fd                        	test	ch, bh
 100fe3a: 00 01                        	add	byte ptr [ecx], al
 100fe3c: 84 fd                        	test	ch, bh
 100fe3e: 00 01                        	add	byte ptr [ecx], al
 100fe40: 84 fd                        	test	ch, bh
 100fe42: 00 01                        	add	byte ptr [ecx], al
 100fe44: cb                           	retf
 100fe45: fb                           	sti
 100fe46: 00 01                        	add	byte ptr [ecx], al
 100fe48: 76 f9                        	jbe	0x100fe43 <.text+0x1f3>
 100fe4a: 00 01                        	add	byte ptr [ecx], al
 100fe4c: 9b                           	wait
 100fe4d: f9                           	stc
 100fe4e: 00 01                        	add	byte ptr [ecx], al
 100fe50: bd f9 00 01 8d               	mov	ebp, 0x8d0100f9
 100fe55: fa                           	cli
 100fe56: 00 01                        	add	byte ptr [ecx], al
 100fe58: c8 fa 00 01                  	enter	0xfa, 0x1
 100fe5c: 06                           	push	es
 100fe5d: fb                           	sti
 100fe5e: 00 01                        	add	byte ptr [ecx], al
 100fe60: 28 fa                        	sub	dl, bh
 100fe62: 00 01                        	add	byte ptr [ecx], al
 100fe64: 4d                           	dec	ebp
 100fe65: fa                           	cli
 100fe66: 00 01                        	add	byte ptr [ecx], al
 100fe68: 2b fb                        	sub	edi, ebx
 100fe6a: 00 01                        	add	byte ptr [ecx], al
 100fe6c: 50                           	push	eax
 100fe6d: fb                           	sti
 100fe6e: 00 01                        	add	byte ptr [ecx], al
 100fe70: 75 fb                        	jne	0x100fe6d <.text+0x21d>
 100fe72: 00 01                        	add	byte ptr [ecx], al
 100fe74: f8                           	clc
 100fe75: fb                           	sti
 100fe76: 00 01                        	add	byte ptr [ecx], al
 100fe78: 1f                           	pop	ds
 100fe79: fc                           	cld
 100fe7a: 00 01                        	add	byte ptr [ecx], al
 100fe7c: d3 fc                        	sar	esp, cl
 100fe7e: 00 01                        	add	byte ptr [ecx], al
 100fe80: 14 fd                        	adc	al, -0x3
 100fe82: 00 01                        	add	byte ptr [ecx], al
 100fe84: 84 fd                        	test	ch, bh
 100fe86: 00 01                        	add	byte ptr [ecx], al
 100fe88: 3f                           	aas
 100fe89: fd                           	std
 100fe8a: 00 01                        	add	byte ptr [ecx], al
 100fe8c: cc                           	int3
 100fe8d: cc                           	int3
 100fe8e: cc                           	int3
 100fe8f: cc                           	int3
 100fe90: 55                           	push	ebp
 100fe91: 8b ec                        	mov	ebp, esp
 100fe93: 51                           	push	ecx
 100fe94: 56                           	push	esi
 100fe95: 8b f1                        	mov	esi, ecx
 100fe97: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
 100fe9a: 85 c0                        	test	eax, eax
 100fe9c: 74 1e                        	je	0x100febc <.text+0x26c>
 100fe9e: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 100fea1: 51                           	push	ecx
 100fea2: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
 100fea5: 8d 56 10                     	lea	edx, [esi + 0x10]
 100fea8: 52                           	push	edx
 100fea9: 51                           	push	ecx
 100feaa: 50                           	push	eax
 100feab: e8 80 30 ff ff               	call	0x1002f30
 100feb0: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 100feb3: 52                           	push	edx
 100feb4: e8 6e 5c 3c 00               	call	0x13d5b27 <.text+0x3c5ed7>
 100feb9: 83 c4 14                     	add	esp, 0x14
 100febc: 8b 06                        	mov	eax, dword ptr [esi]
 100febe: 50                           	push	eax
 100febf: c7 46 04 00 00 00 00         	mov	dword ptr [esi + 0x4], 0x0
 100fec6: c7 46 08 00 00 00 00         	mov	dword ptr [esi + 0x8], 0x0
 100fecd: c7 46 0c 00 00 00 00         	mov	dword ptr [esi + 0xc], 0x0
 100fed4: e8 4e 5c 3c 00               	call	0x13d5b27 <.text+0x3c5ed7>
 100fed9: 83 c4 04                     	add	esp, 0x4
 100fedc: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 100fee2: 5e                           	pop	esi
 100fee3: 8b e5                        	mov	esp, ebp
 100fee5: 5d                           	pop	ebp
 100fee6: c3                           	ret
 100fee7: cc                           	int3
 100fee8: cc                           	int3
 100fee9: cc                           	int3
 100feea: cc                           	int3
 100feeb: cc                           	int3
 100feec: cc                           	int3
 100feed: cc                           	int3
 100feee: cc                           	int3
 100feef: cc                           	int3
 100fef0: 55                           	push	ebp
 100fef1: 8b ec                        	mov	ebp, esp
 100fef3: 6a ff                        	push	-0x1
 100fef5: 68 14 35 4b 01               	push	0x14b3514
 100fefa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 100ff00: 50                           	push	eax
 100ff01: 83 ec 24                     	sub	esp, 0x24
 100ff04: 53                           	push	ebx
 100ff05: 56                           	push	esi
 100ff06: 57                           	push	edi
 100ff07: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 100ff0c: 33 c5                        	xor	eax, ebp
 100ff0e: 50                           	push	eax
 100ff0f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 100ff12: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 100ff18: 8b f9                        	mov	edi, ecx
 100ff1a: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 100ff1d: e8 0e 40 1b 00               	call	0x11c3f30 <.text+0x1b42e0>
 100ff22: 33 db                        	xor	ebx, ebx
 100ff24: c7 07 f4 b8 82 01            	mov	dword ptr [edi], 0x182b8f4
 100ff2a: 8d b7 c4 03 00 00            	lea	esi, [edi + 0x3c4]
 100ff30: 6a 08                        	push	0x8
 100ff32: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 100ff35: 89 1e                        	mov	dword ptr [esi], ebx
 100ff37: e8 de 6b 3c 00               	call	0x13d6b1a <.text+0x3c6eca>
 100ff3c: 83 c4 04                     	add	esp, 0x4
 100ff3f: 3b c3                        	cmp	eax, ebx
 100ff41: 0f 84 a3 00 00 00            	je	0x100ffea <.text+0x39a>
 100ff47: 89 06                        	mov	dword ptr [esi], eax
 100ff49: 33 c9                        	xor	ecx, ecx
 100ff4b: 89 08                        	mov	dword ptr [eax], ecx
 100ff4d: 33 d2                        	xor	edx, edx
 100ff4f: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 100ff52: 8b 06                        	mov	eax, dword ptr [esi]
 100ff54: 89 30                        	mov	dword ptr [eax], esi
 100ff56: 89 5e 04                     	mov	dword ptr [esi + 0x4], ebx
 100ff59: 89 5e 08                     	mov	dword ptr [esi + 0x8], ebx
 100ff5c: 89 5e 0c                     	mov	dword ptr [esi + 0xc], ebx
 100ff5f: 8d b7 dc 03 00 00            	lea	esi, [edi + 0x3dc]
 100ff65: 6a 08                        	push	0x8
 100ff67: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 100ff6b: 89 1e                        	mov	dword ptr [esi], ebx
 100ff6d: e8 a8 6b 3c 00               	call	0x13d6b1a <.text+0x3c6eca>
 100ff72: 83 c4 04                     	add	esp, 0x4
 100ff75: 3b c3                        	cmp	eax, ebx
 100ff77: 74 4d                        	je	0x100ffc6 <.text+0x376>
 100ff79: 89 06                        	mov	dword ptr [esi], eax
 100ff7b: 33 c9                        	xor	ecx, ecx
 100ff7d: 89 08                        	mov	dword ptr [eax], ecx
 100ff7f: 33 d2                        	xor	edx, edx
 100ff81: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 100ff84: 8b 0e                        	mov	ecx, dword ptr [esi]
 100ff86: 89 31                        	mov	dword ptr [ecx], esi
 100ff88: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 100ff8f: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 100ff92: 66 89 56 04                  	mov	word ptr [esi + 0x4], dx
 100ff96: 8b cf                        	mov	ecx, edi
 100ff98: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 100ff9c: e8 8f 2c ff ff               	call	0x1002c30
 100ffa1: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 100ffa4: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 100ffa7: 50                           	push	eax
 100ffa8: 51                           	push	ecx
 100ffa9: 8b cf                        	mov	ecx, edi
 100ffab: e8 c0 37 ff ff               	call	0x1003770
 100ffb0: 8b c7                        	mov	eax, edi
 100ffb2: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 100ffb5: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 100ffbc: 59                           	pop	ecx
 100ffbd: 5f                           	pop	edi
 100ffbe: 5e                           	pop	esi
 100ffbf: 5b                           	pop	ebx
 100ffc0: 8b e5                        	mov	esp, ebp
 100ffc2: 5d                           	pop	ebp
 100ffc3: c2 08 00                     	ret	0x8
 100ffc6: 8d 55 f0                     	lea	edx, [ebp - 0x10]
 100ffc9: 52                           	push	edx
 100ffca: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 100ffcd: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 100ffd0: e8 f5 64 3c 00               	call	0x13d64ca <.text+0x3c687a>
 100ffd5: 68 90 0f 91 01               	push	0x1910f90
 100ffda: 8d 45 dc                     	lea	eax, [ebp - 0x24]
 100ffdd: 50                           	push	eax
 100ffde: c7 45 dc 84 20 56 01         	mov	dword ptr [ebp - 0x24], 0x1562084
 100ffe5: e8 b0 6b 3c 00               	call	0x13d6b9a <.text+0x3c6f4a>
 100ffea: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 100ffed: 51                           	push	ecx
 100ffee: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 100fff1: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
 100fff4: e8 d1 64 3c 00               	call	0x13d64ca <.text+0x3c687a>
 100fff9: 68 90 0f 91 01               	push	0x1910f90
 100fffe: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 1010001: 52                           	push	edx
 1010002: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 1010009: e8 8c 6b 3c 00               	call	0x13d6b9a <.text+0x3c6f4a>
 101000e: cc                           	int3
 101000f: cc                           	int3
 1010010: 55                           	push	ebp
 1010011: 8b ec                        	mov	ebp, esp
 1010013: 51                           	push	ecx
 1010014: 56                           	push	esi
 1010015: 8b f1                        	mov	esi, ecx
 1010017: c7 06 f4 b8 82 01            	mov	dword ptr [esi], 0x182b8f4
 101001d: 83 be f4 03 00 00 08         	cmp	dword ptr [esi + 0x3f4], 0x8
 1010024: 57                           	push	edi
 1010025: 72 0f                        	jb	0x1010036 <.text+0x3e6>
 1010027: 8b 86 e0 03 00 00            	mov	eax, dword ptr [esi + 0x3e0]
 101002d: 50                           	push	eax
 101002e: e8 f4 5a 3c 00               	call	0x13d5b27 <.text+0x3c5ed7>
 1010033: 83 c4 04                     	add	esp, 0x4
 1010036: 33 ff                        	xor	edi, edi
 1010038: 33 c9                        	xor	ecx, ecx
 101003a: c7 86 f4 03 00 00 07 00 00 00	mov	dword ptr [esi + 0x3f4], 0x7
 1010044: 89 be f0 03 00 00            	mov	dword ptr [esi + 0x3f0], edi
 101004a: 66 89 8e e0 03 00 00         	mov	word ptr [esi + 0x3e0], cx
 1010051: 8b 96 dc 03 00 00            	mov	edx, dword ptr [esi + 0x3dc]
 1010057: 52                           	push	edx
 1010058: e8 ca 5a 3c 00               	call	0x13d5b27 <.text+0x3c5ed7>
 101005d: 89 be dc 03 00 00            	mov	dword ptr [esi + 0x3dc], edi
 1010063: 8b 86 c8 03 00 00            	mov	eax, dword ptr [esi + 0x3c8]
 1010069: 83 c4 04                     	add	esp, 0x4
 101006c: 3b c7                        	cmp	eax, edi
 101006e: 74 27                        	je	0x1010097 <.text+0x447>
 1010070: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 1010073: 51                           	push	ecx
 1010074: 8b 8e cc 03 00 00            	mov	ecx, dword ptr [esi + 0x3cc]
 101007a: 8d 96 d4 03 00 00            	lea	edx, [esi + 0x3d4]
 1010080: 52                           	push	edx
 1010081: 51                           	push	ecx
 1010082: 50                           	push	eax
 1010083: e8 a8 2e ff ff               	call	0x1002f30
 1010088: 8b 96 c8 03 00 00            	mov	edx, dword ptr [esi + 0x3c8]
 101008e: 52                           	push	edx
 101008f: e8 93 5a 3c 00               	call	0x13d5b27 <.text+0x3c5ed7>
 1010094: 83 c4 14                     	add	esp, 0x14
 1010097: 8b 86 c4 03 00 00            	mov	eax, dword ptr [esi + 0x3c4]
 101009d: 50                           	push	eax
 101009e: 89 be c8 03 00 00            	mov	dword ptr [esi + 0x3c8], edi
 10100a4: 89 be cc 03 00 00            	mov	dword ptr [esi + 0x3cc], edi
 10100aa: 89 be d0 03 00 00            	mov	dword ptr [esi + 0x3d0], edi
 10100b0: e8 72 5a 3c 00               	call	0x13d5b27 <.text+0x3c5ed7>
 10100b5: 83 c4 04                     	add	esp, 0x4
 10100b8: 8b ce                        	mov	ecx, esi
 10100ba: 89 be c4 03 00 00            	mov	dword ptr [esi + 0x3c4], edi
 10100c0: e8 4b 42 1b 00               	call	0x11c4310 <.text+0x1b46c0>
 10100c5: 5f                           	pop	edi
 10100c6: 5e                           	pop	esi
 10100c7: 8b e5                        	mov	esp, ebp
 10100c9: 5d                           	pop	ebp
 10100ca: c3                           	ret
 10100cb: cc                           	int3
 10100cc: cc                           	int3
 10100cd: cc                           	int3
 10100ce: cc                           	int3
 10100cf: cc                           	int3
 10100d0: 55                           	push	ebp
 10100d1: 8b ec                        	mov	ebp, esp
 10100d3: 56                           	push	esi
 10100d4: 8b f1                        	mov	esi, ecx
 10100d6: e8 35 ff ff ff               	call	0x1010010 <.text+0x3c0>
 10100db: f6 45 08 01                  	test	byte ptr [ebp + 0x8], 0x1
 10100df: 74 09                        	je	0x10100ea <.text+0x49a>
 10100e1: 56                           	push	esi
 10100e2: e8 d9 02 1a 00               	call	0x11b03c0 <.text+0x1a0770>
 10100e7: 83 c4 04                     	add	esp, 0x4
 10100ea: 8b c6                        	mov	eax, esi
 10100ec: 5e                           	pop	esi
 10100ed: 5d                           	pop	ebp
 10100ee: c2                           	<unknown>
 10100ef: 04                           	<unknown>
