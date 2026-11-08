
<stdin>:	file format elf32-i386

Disassembly of section .text:

011a68c0 <.text>:
 11a68c0: 55                           	push	ebp
 11a68c1: 8b ec                        	mov	ebp, esp
 11a68c3: 81 ec 18 04 00 00            	sub	esp, 0x418
 11a68c9: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11a68ce: 33 c5                        	xor	eax, ebp
 11a68d0: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11a68d3: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11a68d6: 53                           	push	ebx
 11a68d7: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11a68da: 56                           	push	esi
 11a68db: 8b 75 10                     	mov	esi, dword ptr [ebp + 0x10]
 11a68de: 57                           	push	edi
 11a68df: 8b f9                        	mov	edi, ecx
 11a68e1: 89 85 f8 fb ff ff            	mov	dword ptr [ebp - 0x408], eax
 11a68e7: 85 f6                        	test	esi, esi
 11a68e9: 0f 85 86 00 00 00            	jne	0x11a6975 <.text+0xb5>
 11a68ef: 8d b5 e8 fb ff ff            	lea	esi, [ebp - 0x418]
 11a68f5: 8b ce                        	mov	ecx, esi
 11a68f7: e8 74 0d 00 00               	call	0x11a7670 <.text+0xdb0>
 11a68fc: 8b 87 04 61 00 00            	mov	eax, dword ptr [edi + 0x6104]
 11a6902: 85 c0                        	test	eax, eax
 11a6904: 74 14                        	je	0x11a691a <.text+0x5a>
 11a6906: 8b 95 f8 fb ff ff            	mov	edx, dword ptr [ebp - 0x408]
 11a690c: 8b ce                        	mov	ecx, esi
 11a690e: 51                           	push	ecx
 11a690f: 52                           	push	edx
 11a6910: 53                           	push	ebx
 11a6911: ff d0                        	call	eax
 11a6913: 83 c4 0c                     	add	esp, 0xc
 11a6916: 84 c0                        	test	al, al
 11a6918: 75 5b                        	jne	0x11a6975 <.text+0xb5>
 11a691a: 83 bf 00 61 00 00 00         	cmp	dword ptr [edi + 0x6100], 0x0
 11a6921: 74 3d                        	je	0x11a6960 <.text+0xa0>
 11a6923: 8b 85 f8 fb ff ff            	mov	eax, dword ptr [ebp - 0x408]
 11a6929: 50                           	push	eax
 11a692a: e8 d1 96 ff ff               	call	0x11a0000
 11a692f: 83 c4 04                     	add	esp, 0x4
 11a6932: 50                           	push	eax
 11a6933: 53                           	push	ebx
 11a6934: e8 c7 96 ff ff               	call	0x11a0000
 11a6939: 83 c4 04                     	add	esp, 0x4
 11a693c: 50                           	push	eax
 11a693d: 8d 8d fc fb ff ff            	lea	ecx, [ebp - 0x404]
 11a6943: 68 d8 6c 85 01               	push	0x1856cd8
 11a6948: 51                           	push	ecx
 11a6949: e8 e2 ee ff ff               	call	0x11a5830
 11a694e: 8b 87 00 61 00 00            	mov	eax, dword ptr [edi + 0x6100]
 11a6954: 8d 95 fc fb ff ff            	lea	edx, [ebp - 0x404]
 11a695a: 52                           	push	edx
 11a695b: ff d0                        	call	eax
 11a695d: 83 c4 14                     	add	esp, 0x14
 11a6960: 5f                           	pop	edi
 11a6961: 5e                           	pop	esi
 11a6962: 32 c0                        	xor	al, al
 11a6964: 5b                           	pop	ebx
 11a6965: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11a6968: 33 cd                        	xor	ecx, ebp
 11a696a: e8 69 08 23 00               	call	0x13d71d8 <.text+0x230918>
 11a696f: 8b e5                        	mov	esp, ebp
 11a6971: 5d                           	pop	ebp
 11a6972: c2 0c 00                     	ret	0xc
 11a6975: 83 7e 04 02                  	cmp	dword ptr [esi + 0x4], 0x2
 11a6979: 72 36                        	jb	0x11a69b1 <.text+0xf1>
 11a697b: 6a 00                        	push	0x0
 11a697d: 6a 02                        	push	0x2
 11a697f: 8d 8d f4 fb ff ff            	lea	ecx, [ebp - 0x40c]
 11a6985: 51                           	push	ecx
 11a6986: 8b 0e                        	mov	ecx, dword ptr [esi]
 11a6988: e8 43 f7 ff ff               	call	0x11a60d0
 11a698d: 8b 0e                        	mov	ecx, dword ptr [esi]
 11a698f: 6a 01                        	push	0x1
 11a6991: 6a ff                        	push	-0x1
 11a6993: 6a fe                        	push	-0x2
 11a6995: e8 86 f3 ff ff               	call	0x11a5d20
 11a699a: ba b0 d0 00 00               	mov	edx, 0xd0b0
 11a699f: 66 39 95 f4 fb ff ff         	cmp	word ptr [ebp - 0x40c], dx
 11a69a6: 75 09                        	jne	0x11a69b1 <.text+0xf1>
 11a69a8: c7 47 14 01 00 00 00         	mov	dword ptr [edi + 0x14], 0x1
 11a69af: eb 07                        	jmp	0x11a69b8 <.text+0xf8>
 11a69b1: c7 47 14 00 00 00 00         	mov	dword ptr [edi + 0x14], 0x0
 11a69b8: 8b 47 14                     	mov	eax, dword ptr [edi + 0x14]
 11a69bb: 85 c0                        	test	eax, eax
 11a69bd: 75 24                        	jne	0x11a69e3 <.text+0x123>
 11a69bf: 8b 85 f8 fb ff ff            	mov	eax, dword ptr [ebp - 0x408]
 11a69c5: 56                           	push	esi
 11a69c6: 50                           	push	eax
 11a69c7: 53                           	push	ebx
 11a69c8: 8d 4f 18                     	lea	ecx, [edi + 0x18]
 11a69cb: e8 70 1d 00 00               	call	0x11a8740 <.text+0x1e80>
 11a69d0: 5f                           	pop	edi
 11a69d1: 5e                           	pop	esi
 11a69d2: 5b                           	pop	ebx
 11a69d3: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11a69d6: 33 cd                        	xor	ecx, ebp
 11a69d8: e8 fb 07 23 00               	call	0x13d71d8 <.text+0x230918>
 11a69dd: 8b e5                        	mov	esp, ebp
 11a69df: 5d                           	pop	ebp
 11a69e0: c2 0c 00                     	ret	0xc
 11a69e3: 83 f8 01                     	cmp	eax, 0x1
 11a69e6: 0f 85 74 ff ff ff            	jne	0x11a6960 <.text+0xa0>
 11a69ec: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
 11a69ef: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
 11a69f2: 51                           	push	ecx
 11a69f3: 85 c0                        	test	eax, eax
 11a69f5: 74 41                        	je	0x11a6a38 <.text+0x178>
 11a69f7: 8b 95 f8 fb ff ff            	mov	edx, dword ptr [ebp - 0x408]
 11a69fd: 50                           	push	eax
 11a69fe: 52                           	push	edx
 11a69ff: 53                           	push	ebx
 11a6a00: 8d 8f c4 40 00 00            	lea	ecx, [edi + 0x40c4]
 11a6a06: e8 85 2c 00 00               	call	0x11a9690 <.text+0x2dd0>
 11a6a0b: 8b 36                        	mov	esi, dword ptr [esi]
 11a6a0d: 8a d8                        	mov	bl, al
 11a6a0f: 85 f6                        	test	esi, esi
 11a6a11: 74 10                        	je	0x11a6a23 <.text+0x163>
 11a6a13: 8b 06                        	mov	eax, dword ptr [esi]
 11a6a15: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
 11a6a18: 8b 14 31                     	mov	edx, dword ptr [ecx + esi]
 11a6a1b: 8b 02                        	mov	eax, dword ptr [edx]
 11a6a1d: 03 ce                        	add	ecx, esi
 11a6a1f: 6a 01                        	push	0x1
 11a6a21: ff d0                        	call	eax
 11a6a23: 5f                           	pop	edi
 11a6a24: 5e                           	pop	esi
 11a6a25: 8a c3                        	mov	al, bl
 11a6a27: 5b                           	pop	ebx
 11a6a28: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11a6a2b: 33 cd                        	xor	ecx, ebp
 11a6a2d: e8 a6 07 23 00               	call	0x13d71d8 <.text+0x230918>
 11a6a32: 8b e5                        	mov	esp, ebp
 11a6a34: 5d                           	pop	ebp
 11a6a35: c2 0c 00                     	ret	0xc
 11a6a38: e8 57 ae 21 00               	call	0x13c1894 <.text+0x21afd4>
 11a6a3d: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 11a6a40: 8b 0e                        	mov	ecx, dword ptr [esi]
 11a6a42: 83 c4 04                     	add	esp, 0x4
 11a6a45: 6a 00                        	push	0x0
 11a6a47: 52                           	push	edx
 11a6a48: 50                           	push	eax
 11a6a49: 89 85 f4 fb ff ff            	mov	dword ptr [ebp - 0x40c], eax
 11a6a4f: e8 7c f6 ff ff               	call	0x11a60d0
 11a6a54: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
 11a6a57: 8b 8d f4 fb ff ff            	mov	ecx, dword ptr [ebp - 0x40c]
 11a6a5d: 8b 95 f8 fb ff ff            	mov	edx, dword ptr [ebp - 0x408]
 11a6a63: 50                           	push	eax
 11a6a64: 51                           	push	ecx
 11a6a65: 52                           	push	edx
 11a6a66: 53                           	push	ebx
 11a6a67: 8d 8f c4 40 00 00            	lea	ecx, [edi + 0x40c4]
 11a6a6d: e8 1e 2c 00 00               	call	0x11a9690 <.text+0x2dd0>
 11a6a72: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11a6a75: 5f                           	pop	edi
 11a6a76: 5e                           	pop	esi
 11a6a77: 33 cd                        	xor	ecx, ebp
 11a6a79: 5b                           	pop	ebx
 11a6a7a: e8 59 07 23 00               	call	0x13d71d8 <.text+0x230918>
 11a6a7f: 8b e5                        	mov	esp, ebp
 11a6a81: 5d                           	pop	ebp
 11a6a82: c2 0c 00                     	ret	0xc
 11a6a85: cc                           	int3
 11a6a86: cc                           	int3
 11a6a87: cc                           	int3
 11a6a88: cc                           	int3
 11a6a89: cc                           	int3
 11a6a8a: cc                           	int3
 11a6a8b: cc                           	int3
 11a6a8c: cc                           	int3
 11a6a8d: cc                           	int3
 11a6a8e: cc                           	int3
 11a6a8f: cc                           	int3
 11a6a90: 55                           	push	ebp
 11a6a91: 8b ec                        	mov	ebp, esp
 11a6a93: 6a ff                        	push	-0x1
 11a6a95: 68 16 69 4c 01               	push	0x14c6916
 11a6a9a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11a6aa0: 50                           	push	eax
 11a6aa1: 56                           	push	esi
 11a6aa2: 57                           	push	edi
 11a6aa3: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11a6aa8: 33 c5                        	xor	eax, ebp
 11a6aaa: 50                           	push	eax
 11a6aab: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11a6aae: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11a6ab4: 8b 7d 10                     	mov	edi, dword ptr [ebp + 0x10]
 11a6ab7: 85 ff                        	test	edi, edi
 11a6ab9: 74 41                        	je	0x11a6afc <.text+0x23c>
 11a6abb: 68 b0 00 00 00               	push	0xb0
 11a6ac0: e8 55 00 23 00               	call	0x13d6b1a <.text+0x23025a>
 11a6ac5: 83 c4 04                     	add	esp, 0x4
 11a6ac8: 89 45 10                     	mov	dword ptr [ebp + 0x10], eax
 11a6acb: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 11a6ace: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11a6ad5: 85 c0                        	test	eax, eax
 11a6ad7: 74 16                        	je	0x11a6aef <.text+0x22f>
 11a6ad9: 6a 01                        	push	0x1
 11a6adb: 57                           	push	edi
 11a6adc: 56                           	push	esi
 11a6add: 8b c8                        	mov	ecx, eax
 11a6adf: e8 dc 0a f5 ff               	call	0x10f75c0
 11a6ae4: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11a6ae7: 89 79 04                     	mov	dword ptr [ecx + 0x4], edi
 11a6aea: 89 71 08                     	mov	dword ptr [ecx + 0x8], esi
 11a6aed: eb 53                        	jmp	0x11a6b42 <.text+0x282>
 11a6aef: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11a6af2: 33 c0                        	xor	eax, eax
 11a6af4: 89 79 04                     	mov	dword ptr [ecx + 0x4], edi
 11a6af7: 89 71 08                     	mov	dword ptr [ecx + 0x8], esi
 11a6afa: eb 46                        	jmp	0x11a6b42 <.text+0x282>
 11a6afc: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11a6aff: 50                           	push	eax
 11a6b00: e8 22 f0 22 00               	call	0x13d5b27 <.text+0x22f267>
 11a6b05: 68 b0 00 00 00               	push	0xb0
 11a6b0a: e8 0b 00 23 00               	call	0x13d6b1a <.text+0x23025a>
 11a6b0f: 83 c4 08                     	add	esp, 0x8
 11a6b12: 89 45 0c                     	mov	dword ptr [ebp + 0xc], eax
 11a6b15: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 11a6b1c: 85 c0                        	test	eax, eax
 11a6b1e: 74 16                        	je	0x11a6b36 <.text+0x276>
 11a6b20: 8b 0d 04 1f a4 01            	mov	ecx, dword ptr [0x1a41f04]
 11a6b26: 6a 01                        	push	0x1
 11a6b28: 6a 00                        	push	0x0
 11a6b2a: 6a 01                        	push	0x1
 11a6b2c: 51                           	push	ecx
 11a6b2d: 8b c8                        	mov	ecx, eax
 11a6b2f: e8 7c bf ca ff               	call	0xe52ab0
 11a6b34: eb 02                        	jmp	0x11a6b38 <.text+0x278>
 11a6b36: 33 c0                        	xor	eax, eax
 11a6b38: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11a6b3b: c7 41 04 01 00 00 00         	mov	dword ptr [ecx + 0x4], 0x1
 11a6b42: 89 01                        	mov	dword ptr [ecx], eax
 11a6b44: b0 01                        	mov	al, 0x1
 11a6b46: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11a6b49: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11a6b50: 59                           	pop	ecx
 11a6b51: 5f                           	pop	edi
 11a6b52: 5e                           	pop	esi
 11a6b53: 8b e5                        	mov	esp, ebp
 11a6b55: 5d                           	pop	ebp
 11a6b56: c2 0c 00                     	ret	0xc
 11a6b59: cc                           	int3
 11a6b5a: cc                           	int3
 11a6b5b: cc                           	int3
 11a6b5c: cc                           	int3
 11a6b5d: cc                           	int3
 11a6b5e: cc                           	int3
 11a6b5f: cc                           	int3
 11a6b60: 55                           	push	ebp
 11a6b61: 8b ec                        	mov	ebp, esp
 11a6b63: 6a ff                        	push	-0x1
 11a6b65: 68 48 69 4c 01               	push	0x14c6948
 11a6b6a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11a6b70: 50                           	push	eax
 11a6b71: 83 ec 64                     	sub	esp, 0x64
 11a6b74: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11a6b79: 33 c5                        	xor	eax, ebp
 11a6b7b: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 11a6b7e: 53                           	push	ebx
 11a6b7f: 56                           	push	esi
 11a6b80: 57                           	push	edi
 11a6b81: 50                           	push	eax
 11a6b82: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11a6b85: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11a6b8b: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11a6b8e: 33 f6                        	xor	esi, esi
 11a6b90: 8b f9                        	mov	edi, ecx
 11a6b92: 89 75 cc                     	mov	dword ptr [ebp - 0x34], esi
 11a6b95: 83 fb ff                     	cmp	ebx, -0x1
 11a6b98: 75 07                        	jne	0x11a6ba1 <.text+0x2e1>
 11a6b9a: 33 c0                        	xor	eax, eax
 11a6b9c: e9 df 02 00 00               	jmp	0x11a6e80 <.text+0x5c0>
 11a6ba1: 8b 47 24                     	mov	eax, dword ptr [edi + 0x24]
 11a6ba4: 39 30                        	cmp	dword ptr [eax], esi
 11a6ba6: 74 22                        	je	0x11a6bca <.text+0x30a>
 11a6ba8: 8b 08                        	mov	ecx, dword ptr [eax]
 11a6baa: 8b 47 34                     	mov	eax, dword ptr [edi + 0x34]
 11a6bad: 8b 10                        	mov	edx, dword ptr [eax]
 11a6baf: 03 d1                        	add	edx, ecx
 11a6bb1: 3b ca                        	cmp	ecx, edx
 11a6bb3: 73 15                        	jae	0x11a6bca <.text+0x30a>
 11a6bb5: ff 08                        	dec	dword ptr [eax]
 11a6bb7: 8b 47 24                     	mov	eax, dword ptr [edi + 0x24]
 11a6bba: 8b 08                        	mov	ecx, dword ptr [eax]
 11a6bbc: 8d 51 01                     	lea	edx, [ecx + 0x1]
 11a6bbf: 89                           	<unknown>
