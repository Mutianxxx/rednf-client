
<stdin>:	file format elf32-i386

Disassembly of section .text:

005789f0 <.text>:
  5789f0: 8b 48 28                     	mov	ecx, dword ptr [eax + 0x28]
  5789f3: 8b 40 2c                     	mov	eax, dword ptr [eax + 0x2c]
  5789f6: 2b c1                        	sub	eax, ecx
  5789f8: c1 f8 03                     	sar	eax, 0x3
  5789fb: 3b f0                        	cmp	esi, eax
  5789fd: 73 3c                        	jae	0x578a3b <.text+0x4b>
  5789ff: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  578a02: 3b 14 f1                     	cmp	edx, dword ptr [ecx + 8*esi]
  578a05: 57                           	push	edi
  578a06: 8b cb                        	mov	ecx, ebx
  578a08: 74 1d                        	je	0x578a27 <.text+0x37>
  578a0a: 46                           	inc	esi
  578a0b: e8 70 f9 ff ff               	call	0x578380
  578a10: 8b 48 2c                     	mov	ecx, dword ptr [eax + 0x2c]
  578a13: 2b 48 28                     	sub	ecx, dword ptr [eax + 0x28]
  578a16: c1 f9 03                     	sar	ecx, 0x3
  578a19: 3b f1                        	cmp	esi, ecx
  578a1b: 72 cb                        	jb	0x5789e8
  578a1d: 5e                           	pop	esi
  578a1e: 5f                           	pop	edi
  578a1f: 83 c8 ff                     	or	eax, -0x1
  578a22: 5b                           	pop	ebx
  578a23: 5d                           	pop	ebp
  578a24: c2 04 00                     	ret	0x4
  578a27: e8 54 f9 ff ff               	call	0x578380
  578a2c: 8b 48 28                     	mov	ecx, dword ptr [eax + 0x28]
  578a2f: 8b 50 2c                     	mov	edx, dword ptr [eax + 0x2c]
  578a32: 2b d1                        	sub	edx, ecx
  578a34: c1 fa 03                     	sar	edx, 0x3
  578a37: 3b f2                        	cmp	esi, edx
  578a39: 72 05                        	jb	0x578a40 <.text+0x50>
  578a3b: e8 67 e3 e5 00               	call	0x13d6da7 <.text+0xe5e3b7>
  578a40: 8b 44 f1 04                  	mov	eax, dword ptr [ecx + 8*esi + 0x4]
  578a44: 5e                           	pop	esi
  578a45: 5f                           	pop	edi
  578a46: 5b                           	pop	ebx
  578a47: 5d                           	pop	ebp
  578a48: c2 04 00                     	ret	0x4
  578a4b: cc                           	int3
  578a4c: cc                           	int3
  578a4d: cc                           	int3
  578a4e: cc                           	int3
  578a4f: cc                           	int3
  578a50: 55                           	push	ebp
  578a51: 8b ec                        	mov	ebp, esp
  578a53: 83 ec 10                     	sub	esp, 0x10
  578a56: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
  578a59: 8b 89 e4 02 00 00            	mov	ecx, dword ptr [ecx + 0x2e4]
  578a5f: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578a62: 2b 51 50                     	sub	edx, dword ptr [ecx + 0x50]
  578a65: b8 67 66 66 66               	mov	eax, 0x66666667
  578a6a: f7 ea                        	imul	edx
  578a6c: 53                           	push	ebx
  578a6d: c1 fa 05                     	sar	edx, 0x5
  578a70: 56                           	push	esi
  578a71: 8b c2                        	mov	eax, edx
  578a73: 57                           	push	edi
  578a74: 33 db                        	xor	ebx, ebx
  578a76: 33 ff                        	xor	edi, edi
  578a78: c1 e8 1f                     	shr	eax, 0x1f
  578a7b: 03 c2                        	add	eax, edx
  578a7d: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  578a80: 89 7d f8                     	mov	dword ptr [ebp - 0x8], edi
  578a83: 0f 84 ce 01 00 00            	je	0x578c57 <.text+0x267>
  578a89: 89 5d f4                     	mov	dword ptr [ebp - 0xc], ebx
  578a8c: 8d 64 24 00                  	lea	esp, [esp]
  578a90: 8b 71 50                     	mov	esi, dword ptr [ecx + 0x50]
  578a93: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578a96: 2b d6                        	sub	edx, esi
  578a98: b8 67 66 66 66               	mov	eax, 0x66666667
  578a9d: f7 ea                        	imul	edx
  578a9f: c1 fa 05                     	sar	edx, 0x5
  578aa2: 8b c2                        	mov	eax, edx
  578aa4: c1 e8 1f                     	shr	eax, 0x1f
  578aa7: 03 c2                        	add	eax, edx
  578aa9: 3b f8                        	cmp	edi, eax
  578aab: 0f 83 b1 01 00 00            	jae	0x578c62 <.text+0x272>
  578ab1: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  578ab4: 3b 14 33                     	cmp	edx, dword ptr [ebx + esi]
  578ab7: 75 74                        	jne	0x578b2d <.text+0x13d>
  578ab9: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578abc: 2b d6                        	sub	edx, esi
  578abe: b8 67 66 66 66               	mov	eax, 0x66666667
  578ac3: f7 ea                        	imul	edx
  578ac5: c1 fa 05                     	sar	edx, 0x5
  578ac8: 8b c2                        	mov	eax, edx
  578aca: c1 e8 1f                     	shr	eax, 0x1f
  578acd: 03 c2                        	add	eax, edx
  578acf: 3b f8                        	cmp	edi, eax
  578ad1: 0f 83 8b 01 00 00            	jae	0x578c62 <.text+0x272>
  578ad7: 8d 04 33                     	lea	eax, [ebx + esi]
  578ada: 85 c0                        	test	eax, eax
  578adc: 74 4f                        	je	0x578b2d <.text+0x13d>
  578ade: 8b 58 3c                     	mov	ebx, dword ptr [eax + 0x3c]
  578ae1: 8b 70 40                     	mov	esi, dword ptr [eax + 0x40]
  578ae4: 2b f3                        	sub	esi, ebx
  578ae6: b8 89 88 88 88               	mov	eax, 0x88888889
  578aeb: f7 ee                        	imul	esi
  578aed: 03 d6                        	add	edx, esi
  578aef: c1 fa 05                     	sar	edx, 0x5
  578af2: 8b c2                        	mov	eax, edx
  578af4: c1 e8 1f                     	shr	eax, 0x1f
  578af7: 33 ff                        	xor	edi, edi
  578af9: 03 c2                        	add	eax, edx
  578afb: 74 30                        	je	0x578b2d <.text+0x13d>
  578afd: 8b d3                        	mov	edx, ebx
  578aff: 3b f8                        	cmp	edi, eax
  578b01: 0f 83 5b 01 00 00            	jae	0x578c62 <.text+0x272>
  578b07: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
  578b0a: 3b 32                        	cmp	esi, dword ptr [edx]
  578b0c: 74 0a                        	je	0x578b18 <.text+0x128>
  578b0e: 47                           	inc	edi
  578b0f: 83 c2 3c                     	add	edx, 0x3c
  578b12: 3b f8                        	cmp	edi, eax
  578b14: 72 f1                        	jb	0x578b07 <.text+0x117>
  578b16: eb 15                        	jmp	0x578b2d <.text+0x13d>
  578b18: 3b f8                        	cmp	edi, eax
  578b1a: 0f 83 42 01 00 00            	jae	0x578c62 <.text+0x272>
  578b20: 8b d7                        	mov	edx, edi
  578b22: c1 e2 04                     	shl	edx, 0x4
  578b25: 2b d7                        	sub	edx, edi
  578b27: 8d 04 93                     	lea	eax, [ebx + 4*edx]
  578b2a: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  578b2d: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578b30: 2b 51 50                     	sub	edx, dword ptr [ecx + 0x50]
  578b33: 8b 7d f8                     	mov	edi, dword ptr [ebp - 0x8]
  578b36: 8b 5d f4                     	mov	ebx, dword ptr [ebp - 0xc]
  578b39: b8 67 66 66 66               	mov	eax, 0x66666667
  578b3e: f7 ea                        	imul	edx
  578b40: c1 fa 05                     	sar	edx, 0x5
  578b43: 8b c2                        	mov	eax, edx
  578b45: c1 e8 1f                     	shr	eax, 0x1f
  578b48: 47                           	inc	edi
  578b49: 83 c3 50                     	add	ebx, 0x50
  578b4c: 03 c2                        	add	eax, edx
  578b4e: 89 7d f8                     	mov	dword ptr [ebp - 0x8], edi
  578b51: 89 5d f4                     	mov	dword ptr [ebp - 0xc], ebx
  578b54: 3b f8                        	cmp	edi, eax
  578b56: 0f 82 34 ff ff ff            	jb	0x578a90 <.text+0xa0>
  578b5c: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
  578b5f: 33 d2                        	xor	edx, edx
  578b61: 3b c2                        	cmp	eax, edx
  578b63: 0f 84 ee 00 00 00            	je	0x578c57 <.text+0x267>
  578b69: 8b 48 08                     	mov	ecx, dword ptr [eax + 0x8]
  578b6c: 8b 40 0c                     	mov	eax, dword ptr [eax + 0xc]
  578b6f: 2b c1                        	sub	eax, ecx
  578b71: c1 f8 04                     	sar	eax, 0x4
  578b74: 89 55 08                     	mov	dword ptr [ebp + 0x8], edx
  578b77: 3b c2                        	cmp	eax, edx
  578b79: 0f 86 d8 00 00 00            	jbe	0x578c57 <.text+0x267>
  578b7f: 89 55 0c                     	mov	dword ptr [ebp + 0xc], edx
  578b82: 3b 45 08                     	cmp	eax, dword ptr [ebp + 0x8]
  578b85: 0f 86 dc 00 00 00            	jbe	0x578c67 <.text+0x277>
  578b8b: 8b 5d f0                     	mov	ebx, dword ptr [ebp - 0x10]
  578b8e: 8b 93 00 03 00 00            	mov	edx, dword ptr [ebx + 0x300]
  578b94: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  578b97: 3b 14 08                     	cmp	edx, dword ptr [eax + ecx]
  578b9a: 0f 84 d1 00 00 00            	je	0x578c71 <.text+0x281>
  578ba0: 8d bb 04 03 00 00            	lea	edi, [ebx + 0x304]
  578ba6: 81 c3 d0 02 00 00            	add	ebx, 0x2d0
  578bac: 57                           	push	edi
  578bad: 8b cb                        	mov	ecx, ebx
  578baf: 33 f6                        	xor	esi, esi
  578bb1: e8 ca f7 ff ff               	call	0x578380
  578bb6: 8b 48 2c                     	mov	ecx, dword ptr [eax + 0x2c]
  578bb9: 2b 48 28                     	sub	ecx, dword ptr [eax + 0x28]
  578bbc: c1 f9 03                     	sar	ecx, 0x3
  578bbf: 85 c9                        	test	ecx, ecx
  578bc1: 74 73                        	je	0x578c36 <.text+0x246>
  578bc3: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  578bc6: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  578bc9: 8b 51 0c                     	mov	edx, dword ptr [ecx + 0xc]
  578bcc: 2b d0                        	sub	edx, eax
  578bce: c1 fa 04                     	sar	edx, 0x4
  578bd1: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
  578bd4: 3b 55 08                     	cmp	edx, dword ptr [ebp + 0x8]
  578bd7: 0f 86 8a 00 00 00            	jbe	0x578c67 <.text+0x277>
  578bdd: 57                           	push	edi
  578bde: 8b cb                        	mov	ecx, ebx
  578be0: e8 9b f7 ff ff               	call	0x578380
  578be5: 8b 48 28                     	mov	ecx, dword ptr [eax + 0x28]
  578be8: 8b 40 2c                     	mov	eax, dword ptr [eax + 0x2c]
  578beb: 2b c1                        	sub	eax, ecx
  578bed: c1 f8 03                     	sar	eax, 0x3
  578bf0: 3b f0                        	cmp	esi, eax
  578bf2: 73 6e                        	jae	0x578c62 <.text+0x272>
  578bf4: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
  578bf7: 8b 45 f4                     	mov	eax, dword ptr [ebp - 0xc]
  578bfa: 8b 14 02                     	mov	edx, dword ptr [edx + eax]
  578bfd: 3b 14 f1                     	cmp	edx, dword ptr [ecx + 8*esi]
  578c00: 75 1e                        	jne	0x578c20 <.text+0x230>
  578c02: 57                           	push	edi
  578c03: 8b cb                        	mov	ecx, ebx
  578c05: e8 76 f7 ff ff               	call	0x578380
  578c0a: 8b 48 28                     	mov	ecx, dword ptr [eax + 0x28]
  578c0d: 8b 40 2c                     	mov	eax, dword ptr [eax + 0x2c]
  578c10: 2b c1                        	sub	eax, ecx
  578c12: c1 f8 03                     	sar	eax, 0x3
  578c15: 3b f0                        	cmp	esi, eax
  578c17: 73 49                        	jae	0x578c62 <.text+0x272>
  578c19: 83 7c f1 04 ff               	cmp	dword ptr [ecx + 8*esi + 0x4], -0x1
  578c1e: 7d 51                        	jge	0x578c71 <.text+0x281>
  578c20: 57                           	push	edi
  578c21: 8b cb                        	mov	ecx, ebx
  578c23: 46                           	inc	esi
  578c24: e8 57 f7 ff ff               	call	0x578380
  578c29: 8b 48 2c                     	mov	ecx, dword ptr [eax + 0x2c]
  578c2c: 2b 48 28                     	sub	ecx, dword ptr [eax + 0x28]
  578c2f: c1 f9 03                     	sar	ecx, 0x3
  578c32: 3b f1                        	cmp	esi, ecx
  578c34: 72 8d                        	jb	0x578bc3 <.text+0x1d3>
  578c36: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
  578c39: 8b 48 08                     	mov	ecx, dword ptr [eax + 0x8]
  578c3c: 8b 40 0c                     	mov	eax, dword ptr [eax + 0xc]
  578c3f: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  578c42: 83 45 0c 10                  	add	dword ptr [ebp + 0xc], 0x10
  578c46: 2b c1                        	sub	eax, ecx
  578c48: 42                           	inc	edx
  578c49: c1 f8 04                     	sar	eax, 0x4
  578c4c: 89 55 08                     	mov	dword ptr [ebp + 0x8], edx
  578c4f: 3b d0                        	cmp	edx, eax
  578c51: 0f 82 2b ff ff ff            	jb	0x578b82 <.text+0x192>
  578c57: 5f                           	pop	edi
  578c58: 5e                           	pop	esi
  578c59: 32 c0                        	xor	al, al
  578c5b: 5b                           	pop	ebx
  578c5c: 8b e5                        	mov	esp, ebp
  578c5e: 5d                           	pop	ebp
  578c5f: c2 08 00                     	ret	0x8
  578c62: e8 40 e1 e5 00               	call	0x13d6da7 <.text+0xe5e3b7>
  578c67: 68 c8 22 56 01               	push	0x15622c8
  578c6c: e8 a6 8b e4 00               	call	0x13c1817 <.text+0xe48e27>
  578c71: 5f                           	pop	edi
  578c72: 5e                           	pop	esi
  578c73: b0 01                        	mov	al, 0x1
  578c75: 5b                           	pop	ebx
  578c76: 8b e5                        	mov	esp, ebp
  578c78: 5d                           	pop	ebp
  578c79: c2 08 00                     	ret	0x8
  578c7c: cc                           	int3
  578c7d: cc                           	int3
  578c7e: cc                           	int3
  578c7f: cc                           	int3
  578c80: 55                           	push	ebp
  578c81: 8b ec                        	mov	ebp, esp
  578c83: 83 ec 10                     	sub	esp, 0x10
  578c86: 53                           	push	ebx
  578c87: 8b d9                        	mov	ebx, ecx
  578c89: 8b 8b e4 02 00 00            	mov	ecx, dword ptr [ebx + 0x2e4]
  578c8f: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578c92: 2b 51 50                     	sub	edx, dword ptr [ecx + 0x50]
  578c95: 83 c1 4c                     	add	ecx, 0x4c
  578c98: b8 67 66 66 66               	mov	eax, 0x66666667
  578c9d: f7 ea                        	imul	edx
  578c9f: c1 fa 05                     	sar	edx, 0x5
  578ca2: 8b c2                        	mov	eax, edx
  578ca4: 56                           	push	esi
  578ca5: 33 f6                        	xor	esi, esi
  578ca7: c1 e8 1f                     	shr	eax, 0x1f
  578caa: 03 c2                        	add	eax, edx
  578cac: 57                           	push	edi
  578cad: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
  578cb0: 89 75 f8                     	mov	dword ptr [ebp - 0x8], esi
  578cb3: 0f 84 17 01 00 00            	je	0x578dd0 <.text+0x3e0>
  578cb9: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
  578cbc: 8d 64 24 00                  	lea	esp, [esp]
  578cc0: 8b 79 04                     	mov	edi, dword ptr [ecx + 0x4]
  578cc3: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  578cc6: 2b d7                        	sub	edx, edi
  578cc8: b8 67 66 66 66               	mov	eax, 0x66666667
  578ccd: f7 ea                        	imul	edx
  578ccf: c1 fa 05                     	sar	edx, 0x5
  578cd2: 8b c2                        	mov	eax, edx
  578cd4: c1 e8 1f                     	shr	eax, 0x1f
  578cd7: 03 c2                        	add	eax, edx
  578cd9: 3b f0                        	cmp	esi, eax
  578cdb: 0f 83 fa 00 00 00            	jae	0x578ddb <.text+0x3eb>
  578ce1: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  578ce4: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
  578ce7: 3b 14 38                     	cmp	edx, dword ptr [eax + edi]
  578cea: 0f 85 b0 00 00 00            	jne	0x578da0 <.text+0x3b0>
  578cf0: 8b 49 08                     	mov	ecx, dword ptr [ecx + 0x8]
  578cf3: 2b cf                        	sub	ecx, edi
  578cf5: b8 67 66 66 66               	mov	eax, 0x66666667
  578cfa: f7 e9                        	imul	ecx
  578cfc: c1 fa 05                     	sar	edx, 0x5
  578cff: 8b ca                        	mov	ecx, edx
  578d01: c1 e9 1f                     	shr	ecx, 0x1f
  578d04: 03 ca                        	add	ecx, edx
  578d06: 3b f1                        	cmp	esi, ecx
  578d08: 0f 83 cd 00 00 00            	jae	0x578ddb <.text+0x3eb>
  578d0e: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
  578d11: 03 c7                        	add	eax, edi
  578d13: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
  578d16: 0f 84 84 00 00 00            	je	0x578da0 <.text+0x3b0>
  578d1c: 8d bb 04 03 00 00            	lea	edi, [ebx + 0x304]
  578d22: 81 c3 d0 02 00 00            	add	ebx, 0x2d0
  578d28: 57                           	push	edi
  578d29: 8b cb                        	mov	ecx, ebx
  578d2b: 33 f6                        	xor	esi, esi
  578d2d: e8 4e f6 ff ff               	call	0x578380
  578d32: 8b 48 2c                     	mov	ecx, dword ptr [eax + 0x2c]
  578d35: 2b 48 28                     	sub	ecx, dword ptr [eax + 0x28]
  578d38: c1 f9 03                     	sar	ecx, 0x3
  578d3b: 85 c9                        	test	ecx, ecx
  578d3d: 74 5b                        	je	0x578d9a <.text+0x3aa>
  578d3f: 90                           	nop
  578d40: 57                           	push	edi
  578d41: 8b cb                        	mov	ecx, ebx
  578d43: e8 38 f6 ff ff               	call	0x578380
  578d48: 8b 48 28                     	mov	ecx, dword ptr [eax + 0x28]
  578d4b: 8b 50 2c                     	mov	edx, dword ptr [eax + 0x2c]
  578d4e: 2b d1                        	sub	edx, ecx
  578d50: c1 fa 03                     	sar	edx, 0x3
  578d53: 3b f2                        	cmp	esi, edx
  578d55: 0f 83 80 00 00 00            	jae	0x578ddb <.text+0x3eb>
  578d5b: 8b 45 f4                     	mov	eax, dword ptr [ebp - 0xc]
  578d5e: 8b 50 4c                     	mov	edx, dword ptr [eax + 0x4c]
  578d61: 3b 14 f1                     	cmp	edx, dword ptr [ecx + 8*esi]
  578d64: 75 1e                        	jne	0x578d84 <.text+0x394>
  578d66: 57                           	push	edi
  578d67: 8b cb                        	mov	ecx, ebx
  578d69: e8 12 f6 ff ff               	call	0x578380
  578d6e: 8b 48 28                     	mov	ecx, dword ptr [eax + 0x28]
  578d71: 8b 40 2c                     	mov	eax, dword ptr [eax + 0x2c]
  578d74: 2b c1                        	sub	eax, ecx
  578d76: c1 f8 03                     	sar	eax, 0x3
  578d79: 3b f0                        	cmp	esi, eax
  578d7b: 73 5e                        	jae	0x578ddb <.text+0x3eb>
  578d7d: 83 7c f1 04 ff               	cmp	dword ptr [ecx + 8*esi + 0x4], -0x1
  578d82: 7d 5c                        	jge	0x578de0 <.text+0x3f0>
  578d84: 57                           	push	edi
  578d85: 8b cb                        	mov	ecx, ebx
  578d87: 46                           	inc	esi
  578d88: e8 f3 f5 ff ff               	call	0x578380
  578d8d: 8b 48 2c                     	mov	ecx, dword ptr [eax + 0x2c]
  578d90: 2b 48 28                     	sub	ecx, dword ptr [eax + 0x28]
  578d93: c1 f9 03                     	sar	ecx, 0x3
  578d96: 3b f1                        	cmp	esi, ecx
  578d98: 72 a6                        	jb	0x578d40 <.text+0x350>
  578d9a: 8b 75 f8                     	mov	esi, dword ptr [ebp - 0x8]
  578d9d: 8b 5d f0                     	mov	ebx, dword ptr [ebp - 0x10]
  578da0: 8b 8b e4 02 00 00            	mov	ecx, dword ptr [ebx + 0x2e4]
  578da6: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578da9: 2b 51 50                     	sub	edx, dword ptr [ecx + 0x50]
  578dac: 83 45 fc 50                  	add	dword ptr [ebp - 0x4], 0x50
  578db0: 83 c1 4c                     	add	ecx, 0x4c
  578db3: b8 67 66 66 66               	mov	eax, 0x66666667
  578db8: f7 ea                        	imul	edx
  578dba: c1 fa 05                     	sar	edx, 0x5
  578dbd: 8b c2                        	mov	eax, edx
  578dbf: c1 e8 1f                     	shr	eax, 0x1f
  578dc2: 46                           	inc	esi
  578dc3: 03 c2                        	add	eax, edx
  578dc5: 89 75 f8                     	mov	dword ptr [ebp - 0x8], esi
  578dc8: 3b f0                        	cmp	esi, eax
  578dca: 0f 82 f0 fe ff ff            	jb	0x578cc0 <.text+0x2d0>
  578dd0: 5f                           	pop	edi
  578dd1: 5e                           	pop	esi
  578dd2: 32 c0                        	xor	al, al
  578dd4: 5b                           	pop	ebx
  578dd5: 8b e5                        	mov	esp, ebp
  578dd7: 5d                           	pop	ebp
  578dd8: c2 04 00                     	ret	0x4
  578ddb: e8 c7 df e5 00               	call	0x13d6da7 <.text+0xe5e3b7>
  578de0: 5f                           	pop	edi
  578de1: 5e                           	pop	esi
  578de2: b0 01                        	mov	al, 0x1
  578de4: 5b                           	pop	ebx
  578de5: 8b e5                        	mov	esp, ebp
  578de7: 5d                           	pop	ebp
  578de8: c2 04 00                     	ret	0x4
  578deb: cc                           	int3
  578dec: cc                           	int3
  578ded: cc                           	int3
  578dee: cc                           	int3
  578def: cc                           	int3
  578df0: 8d 81 04 03 00 00            	lea	eax, [ecx + 0x304]
  578df6: 50                           	push	eax
  578df7: 81 c1 d0 02 00 00            	add	ecx, 0x2d0
  578dfd: e8 7e f5 ff ff               	call	0x578380
  578e02: 8b c8                        	mov	ecx, eax
  578e04: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  578e07: 03 41 04                     	add	eax, dword ptr [ecx + 0x4]
  578e0a: c3                           	ret
  578e0b: cc                           	int3
  578e0c: cc                           	int3
  578e0d: cc                           	int3
  578e0e: cc                           	int3
  578e0f: cc                           	int3
  578e10: 8d 81 04 03 00 00            	lea	eax, [ecx + 0x304]
  578e16: 50                           	push	eax
  578e17: 81 c1 d0 02 00 00            	add	ecx, 0x2d0
  578e1d: e8 5e f5 ff ff               	call	0x578380
  578e22: 8b 40 14                     	mov	eax, dword ptr [eax + 0x14]
  578e25: c3                           	ret
  578e26: cc                           	int3
  578e27: cc                           	int3
  578e28: cc                           	int3
  578e29: cc                           	int3
  578e2a: cc                           	int3
  578e2b: cc                           	int3
  578e2c: cc                           	int3
  578e2d: cc                           	int3
  578e2e: cc                           	int3
  578e2f: cc                           	int3
  578e30: 55                           	push	ebp
  578e31: 8b ec                        	mov	ebp, esp
  578e33: 83 ec 30                     	sub	esp, 0x30
  578e36: 53                           	push	ebx
  578e37: 8b d9                        	mov	ebx, ecx
  578e39: 8b 8b e4 02 00 00            	mov	ecx, dword ptr [ebx + 0x2e4]
  578e3f: 57                           	push	edi
  578e40: 33 ff                        	xor	edi, edi
  578e42: 89 5d f8                     	mov	dword ptr [ebp - 0x8], ebx
  578e45: 3b cf                        	cmp	ecx, edi
  578e47: 0f 84 c7 02 00 00            	je	0x579114 <.text+0x724>
  578e4d: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578e50: 2b 51 50                     	sub	edx, dword ptr [ecx + 0x50]
  578e53: b8 67 66 66 66               	mov	eax, 0x66666667
  578e58: f7 ea                        	imul	edx
  578e5a: c1 fa 05                     	sar	edx, 0x5
  578e5d: 8b c2                        	mov	eax, edx
  578e5f: c1 e8 1f                     	shr	eax, 0x1f
  578e62: 03 c2                        	add	eax, edx
  578e64: 0f 84 aa 02 00 00            	je	0x579114 <.text+0x724>
  578e6a: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578e6d: 56                           	push	esi
  578e6e: 8b 71 50                     	mov	esi, dword ptr [ecx + 0x50]
  578e71: 2b d6                        	sub	edx, esi
  578e73: b8 67 66 66 66               	mov	eax, 0x66666667
  578e78: f7 ea                        	imul	edx
  578e7a: c1 fa 05                     	sar	edx, 0x5
  578e7d: 8b c2                        	mov	eax, edx
  578e7f: c1 e8 1f                     	shr	eax, 0x1f
  578e82: 03 c2                        	add	eax, edx
  578e84: 75 05                        	jne	0x578e8b <.text+0x49b>
  578e86: e8 1c df e5 00               	call	0x13d6da7 <.text+0xe5e3b7>
  578e8b: 8b 16                        	mov	edx, dword ptr [esi]
  578e8d: 89 93 fc 02 00 00            	mov	dword ptr [ebx + 0x2fc], edx
  578e93: c7 83 00 03 00 00 ff ff ff ff	mov	dword ptr [ebx + 0x300], 0xffffffff
  578e9d: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  578ea0: 2b 51 50                     	sub	edx, dword ptr [ecx + 0x50]
  578ea3: b8 67 66 66 66               	mov	eax, 0x66666667
  578ea8: f7 ea                        	imul	edx
  578eaa: c1 fa 05                     	sar	edx, 0x5
  578ead: 8b c2                        	mov	eax, edx
  578eaf: c1 e8 1f                     	shr	eax, 0x1f
  578eb2: 33 f6                        	xor	esi, esi
  578eb4: 03 c2                        	add	eax, edx
  578eb6: 89 7d ec                     	mov	dword ptr [ebp - 0x14], edi
  578eb9: 0f 84 54 02 00 00            	je	0x579113 <.text+0x723>
  578ebf: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
  578ec2: eb 03                        	jmp	0x578ec7 <.text+0x4d7>
  578ec4: 8b 75 d8                     	mov	esi, dword ptr [ebp - 0x28]
  578ec7: 8b 83 e4 02 00 00            	mov	eax, dword ptr [ebx + 0x2e4]
  578ecd: 8b 48 50                     	mov	ecx, dword ptr [eax + 0x50]
  578ed0: 8b 50 54                     	mov	edx, dword ptr [eax + 0x54]
  578ed3: 2b d1                        	sub	edx, ecx
  578ed5: b8 67 66 66 66               	mov	eax, 0x66666667
  578eda: f7 ea                        	imul	edx
  578edc: c1 fa 05                     	sar	edx, 0x5
  578edf: 8b c2                        	mov	eax, edx
  578ee1: c1 e8 1f                     	shr	eax, 0x1f
  578ee4: 03 c2                        	add	eax, edx
  578ee6: 89 75 d0                     	mov	dword ptr [ebp - 0x30], esi
  578ee9: 39 45 ec                     	cmp	dword ptr [ebp - 0x14], eax
  578eec: 73 98                        	jae	0x578e86 <.text+0x496>
  578eee: 8b 7d e8                     	mov	edi, dword ptr [ebp - 0x18]
  578ef1: 03 f9                        	add	edi, ecx
  578ef3: 89 7d d8                     	mov	dword ptr [ebp - 0x28], edi
  578ef6: 0f 84 75 01 00 00            	je	0x579071 <.text+0x681>
  578efc: 8b 07                        	mov	eax, dword ptr [edi]
  578efe: 89 83 fc 02 00 00            	mov	dword ptr [ebx + 0x2fc], eax
  578f04: 8b 47 3c                     	mov	eax, dword ptr [edi + 0x3c]
  578f07: 8b 77 40                     	mov	esi, dword ptr [edi + 0x40]
  578f0a: 2b f0                        	sub	esi, eax
  578f0c: 89 45 e0                     	mov	dword ptr [ebp - 0x20], eax
  578f0f: b8 89 88 88 88               	mov	eax, 0x88888889
  578f14: f7 ee                        	imul	esi
  578f16: 03 d6                        	add	edx, esi
  578f18: c1 fa 05                     	sar	edx, 0x5
  578f1b: 8b c2                        	mov	eax, edx
  578f1d: 33 c9                        	xor	ecx, ecx
  578f1f: c1 e8 1f                     	shr	eax, 0x1f
  578f22: 03 c2                        	add	eax, edx
  578f24: 89 4d d4                     	mov	dword ptr [ebp - 0x2c], ecx
  578f27: 0f 84 44 01 00 00            	je	0x579071 <.text+0x681>
  578f2d: 33 db                        	xor	ebx, ebx
  578f2f: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
  578f32: 3b c1                        	cmp	eax, ecx
  578f34: 0f 86 c4 01 00 00            	jbe	0x5790fe <.text+0x70e>
  578f3a: 8b 55 e0                     	mov	edx, dword ptr [ebp - 0x20]
  578f3d: 8d 44 13 0c                  	lea	eax, [ebx + edx + 0xc]
  578f41: 89 45 dc                     	mov	dword ptr [ebp - 0x24], eax
  578f44: 8b 00                        	mov	eax, dword ptr [eax]
  578f46: 2b 44 13 08                  	sub	eax, dword ptr [ebx + edx + 0x8]
  578f4a: 8d 54 13 08                  	lea	edx, [ebx + edx + 0x8]
  578f4e: c1 f8 04                     	sar	eax, 0x4
  578f51: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  578f58: 89 55 f0                     	mov	dword ptr [ebp - 0x10], edx
  578f5b: 85 c0                        	test	eax, eax
  578f5d: 0f 84 db 00 00 00            	je	0x57903e <.text+0x64e>
  578f63: 8b 5d f8                     	mov	ebx, dword ptr [ebp - 0x8]
  578f66: 8d bb 04 03 00 00            	lea	edi, [ebx + 0x304]
  578f6c: 81 c3 d0 02 00 00            	add	ebx, 0x2d0
  578f72: c7 45 f4 00 00 00 00         	mov	dword ptr [ebp - 0xc], 0x0
  578f79: 8d a4 24 00 00 00 00         	lea	esp, [esp]
  578f80: 57                           	push	edi
  578f81: 8b cb                        	mov	ecx, ebx
  578f83: 33 f6                        	xor	esi, esi
  578f85: e8 f6 f3 ff ff               	call	0x578380
  578f8a: 8b 48 2c                     	mov	ecx, dword ptr [eax + 0x2c]
  578f8d: 2b 48 28                     	sub	ecx, dword ptr [eax + 0x28]
  578f90: c1 f9 03                     	sar	ecx, 0x3
  578f93: 85 c9                        	test	ecx, ecx
  578f95: 74 7e                        	je	0x579015 <.text+0x625>
  578f97: 57                           	push	edi
  578f98: 8b cb                        	mov	ecx, ebx
  578f9a: e8 e1 f3 ff ff               	call	0x578380
  578f9f: 8b 48 28                     	mov	ecx, dword ptr [eax + 0x28]
  578fa2: 8b 50 2c                     	mov	edx, dword ptr [eax + 0x2c]
  578fa5: 2b d1                        	sub	edx, ecx
  578fa7: c1 fa 03                     	sar	edx, 0x3
  578faa: 3b f2                        	cmp	esi, edx
  578fac: 0f 83 d4 fe ff ff            	jae	0x578e86 <.text+0x496>
  578fb2: 8b 45 f0                     	mov	eax, dword ptr [ebp - 0x10]
  578fb5: 8b 55 dc                     	mov	edx, dword ptr [ebp - 0x24]
  578fb8: 8b 12                        	mov	edx, dword ptr [edx]
  578fba: 8b 00                        	mov	eax, dword ptr [eax]
  578fbc: 2b d0                        	sub	edx, eax
  578fbe: c1 fa 04                     	sar	edx, 0x4
  578fc1: 3b 55 fc                     	cmp	edx, dword ptr [ebp - 0x4]
  578fc4: 0f 86 34 01 00 00            	jbe	0x5790fe <.text+0x70e>
  578fca: 8b 55 f0                     	mov	edx, dword ptr [ebp - 0x10]
  578fcd: 8b 02                        	mov	eax, dword ptr [edx]
  578fcf: 8b 0c f1                     	mov	ecx, dword ptr [ecx + 8*esi]
  578fd2: 8b 55 f4                     	mov	edx, dword ptr [ebp - 0xc]
  578fd5: 3b 0c 02                     	cmp	ecx, dword ptr [edx + eax]
  578fd8: 57                           	push	edi
  578fd9: 8b cb                        	mov	ecx, ebx
  578fdb: 74 15                        	je	0x578ff2 <.text+0x602>
  578fdd: 46                           	inc	esi
  578fde: e8 9d f3 ff ff               	call	0x578380
  578fe3: 8b 48 2c                     	mov	ecx, dword ptr [eax + 0x2c]
  578fe6: 2b 48 28                     	sub	ecx, dword ptr [eax + 0x28]
  578fe9: c1 f9 03                     	sar	ecx, 0x3
  578fec: 3b f1                        	cmp	esi, ecx
  578fee: 72 a7                        	jb	0x578f97 <.text+0x5a7>
  578ff0: eb 23                        	jmp	0x579015 <.text+0x625>
  578ff2: e8 89 f3 ff ff               	call	0x578380
  578ff7: 8b 48 28                     	mov	ecx, dword ptr [eax + 0x28]
  578ffa: 8b 50 2c                     	mov	edx, dword ptr [eax + 0x2c]
  578ffd: 2b d1                        	sub	edx, ecx
  578fff: c1 fa 03                     	sar	edx, 0x3
  579002: 3b f2                        	cmp	esi, edx
  579004: 0f 83 7c fe ff ff            	jae	0x578e86 <.text+0x496>
  57900a: 83 7c f1 04 ff               	cmp	dword ptr [ecx + 8*esi + 0x4], -0x1
  57900f: 0f 84 93 00 00 00            	je	0x5790a8 <.text+0x6b8>
  579015: 8b 4d dc                     	mov	ecx, dword ptr [ebp - 0x24]
  579018: 8b 11                        	mov	edx, dword ptr [ecx]
  57901a: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
  57901d: 2b 11                        	sub	edx, dword ptr [ecx]
  57901f: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
  579022: 83 45 f4 10                  	add	dword ptr [ebp - 0xc], 0x10
  579026: 40                           	inc	eax
  579027: c1 fa 04                     	sar	edx, 0x4
  57902a: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  57902d: 3b c2                        	cmp	eax, edx
  57902f: 0f 82 4b ff ff ff            	jb	0x578f80 <.text+0x590>
  579035: 8b 4d d4                     	mov	ecx, dword ptr [ebp - 0x2c]
  579038: 8b 7d d8                     	mov	edi, dword ptr [ebp - 0x28]
  57903b: 8b 5d e4                     	mov	ebx, dword ptr [ebp - 0x1c]
  57903e: 8b 47 3c                     	mov	eax, dword ptr [edi + 0x3c]
  579041: 8b 77 40                     	mov	esi, dword ptr [edi + 0x40]
  579044: 2b f0                        	sub	esi, eax
  579046: 89 45 e0                     	mov	dword ptr [ebp - 0x20], eax
  579049: b8 89 88 88 88               	mov	eax, 0x88888889
  57904e: f7 ee                        	imul	esi
  579050: 03 d6                        	add	edx, esi
  579052: c1 fa 05                     	sar	edx, 0x5
  579055: 8b c2                        	mov	eax, edx
  579057: c1 e8 1f                     	shr	eax, 0x1f
  57905a: 41                           	inc	ecx
  57905b: 83 c3 3c                     	add	ebx, 0x3c
  57905e: 03 c2                        	add	eax, edx
  579060: 89 4d d4                     	mov	dword ptr [ebp - 0x2c], ecx
  579063: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
  579066: 3b c1                        	cmp	eax, ecx
  579068: 0f 87 cc fe ff ff            	ja	0x578f3a <.text+0x54a>
  57906e: 8b 5d f8                     	mov	ebx, dword ptr [ebp - 0x8]
  579071: 8b 83 e4 02 00 00            	mov	eax, dword ptr [ebx + 0x2e4]
  579077: 8b 50 54                     	mov	edx, dword ptr [eax + 0x54]
  57907a: 2b 50 50                     	sub	edx, dword ptr [eax + 0x50]
  57907d: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
  579080: 83 45 e8 50                  	add	dword ptr [ebp - 0x18], 0x50
  579084: b8 67 66 66 66               	mov	eax, 0x66666667
  579089: f7 ea                        	imul	edx
  57908b: c1 fa 05                     	sar	edx, 0x5
  57908e: 8b c2                        	mov	eax, edx
  579090: c1 e8 1f                     	shr	eax, 0x1f
  579093: 41                           	inc	ecx
  579094: 03 c2                        	add	eax, edx
  579096: 89 4d ec                     	mov	dword ptr [ebp - 0x14], ecx
  579099: 3b c8                        	cmp	ecx, eax
  57909b: 0f 82 23 fe ff ff            	jb	0x578ec4 <.text+0x4d4>
  5790a1: 5e                           	pop	esi
  5790a2: 5f                           	pop	edi
  5790a3: 5b                           	pop	ebx
  5790a4: 8b e5                        	mov	esp, ebp
  5790a6: 5d                           	pop	ebp
  5790a7: c3                           	ret
  5790a8: 8b 75 fc                     	mov	esi, dword ptr [ebp - 0x4]
  5790ab: 8b 5d f8                     	mov	ebx, dword ptr [ebp - 0x8]
  5790ae: 85 f6                        	test	esi, esi
  5790b0: 75 35                        	jne	0x5790e7 <.text+0x6f7>
  5790b2: 8d 8b 04 03 00 00            	lea	ecx, [ebx + 0x304]
  5790b8: 51                           	push	ecx
  5790b9: 8d 8b d0 02 00 00            	lea	ecx, [ebx + 0x2d0]
  5790bf: e8 bc f2 ff ff               	call	0x578380
  5790c4: 80 78 20 00                  	cmp	byte ptr [eax + 0x20], 0x0
  5790c8: 74 1d                        	je	0x5790e7 <.text+0x6f7>
  5790ca: 8b 7d d0                     	mov	edi, dword ptr [ebp - 0x30]
  5790cd: 85 ff                        	test	edi, edi
  5790cf: 74 16                        	je	0x5790e7 <.text+0x6f7>
  5790d1: 8b 17                        	mov	edx, dword ptr [edi]
  5790d3: 52                           	push	edx
  5790d4: 8b cb                        	mov	ecx, ebx
  5790d6: e8 a5 fb ff ff               	call	0x578c80 <.text+0x290>
  5790db: 84 c0                        	test	al, al
  5790dd: 74 08                        	je	0x5790e7 <.text+0x6f7>
  5790df: 8b 07                        	mov	eax, dword ptr [edi]
  5790e1: 89 83 fc 02 00 00            	mov	dword ptr [ebx + 0x2fc], eax
  5790e7: 8b 4d e4                     	mov	ecx, dword ptr [ebp - 0x1c]
  5790ea: 8b 55 e0                     	mov	edx, dword ptr [ebp - 0x20]
  5790ed: 8b 44 11 08                  	mov	eax, dword ptr [ecx + edx + 0x8]
  5790f1: 8b 4c 11 0c                  	mov	ecx, dword ptr [ecx + edx + 0xc]
  5790f5: 2b c8                        	sub	ecx, eax
  5790f7: c1 f9 04                     	sar	ecx, 0x4
  5790fa: 3b ce                        	cmp	ecx, esi
  5790fc: 77 0a                        	ja	0x579108 <.text+0x718>
  5790fe: 68 c8 22 56 01               	push	0x15622c8
  579103: e8 0f 87 e4 00               	call	0x13c1817 <.text+0xe48e27>
  579108: 03 f6                        	add	esi, esi
  57910a: 8b 14 f0                     	mov	edx, dword ptr [eax + 8*esi]
  57910d: 89 93 00 03 00 00            	mov	dword ptr [ebx + 0x300], edx
  579113: 5e                           	pop	esi
  579114: 5f                           	pop	edi
  579115: 5b                           	pop	ebx
  579116: 8b e5                        	mov	esp, ebp
  579118: 5d                           	pop	ebp
  579119: c3                           	ret
  57911a: cc                           	int3
  57911b: cc                           	int3
  57911c: cc                           	int3
  57911d: cc                           	int3
  57911e: cc                           	int3
  57911f: cc                           	int3
  579120: 55                           	push	ebp
  579121: 8b ec                        	mov	ebp, esp
  579123: 6a ff                        	push	-0x1
  579125: 68 53 d1 41 01               	push	0x141d153
  57912a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  579130: 50                           	push	eax
  579131: 83 ec 60                     	sub	esp, 0x60
  579134: 53                           	push	ebx
  579135: 56                           	push	esi
  579136: 57                           	push	edi
  579137: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  57913c: 33 c5                        	xor	eax, ebp
  57913e: 50                           	push	eax
  57913f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  579142: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  579148: 8b f9                        	mov	edi, ecx
  57914a: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
  57914d: 8d 4d 94                     	lea	ecx, [ebp - 0x6c]
  579150: e8 9b 57 3b 00               	call	0x92e8f0 <.text+0x3b5f00>
  579155: 33 db                        	xor	ebx, ebx
  579157: 8d 4d a8                     	lea	ecx, [ebp - 0x58]
  57915a: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  57915d: e8 8e 57 3b 00               	call	0x92e8f0 <.text+0x3b5f00>
  579162: 8d 4d bc                     	lea	ecx, [ebp - 0x44]
  579165: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  579169: e8 82 57 3b 00               	call	0x92e8f0 <.text+0x3b5f00>
  57916e: 8d 4d 94                     	lea	ecx, [ebp - 0x6c]
  579171: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
  579175: e8 26 22 03 00               	call	0x5ab3a0 <.text+0x329b0>
  57917a: 8d 4d a8                     	lea	ecx, [ebp - 0x58]
  57917d: e8 1e 22 03 00               	call	0x5ab3a0 <.text+0x329b0>
  579182: 8d 4d bc                     	lea	ecx, [ebp - 0x44]
  579185: e8 16 22 03 00               	call	0x5ab3a0 <.text+0x329b0>
  57918a: 8d b7 04 03 00 00            	lea	esi, [edi + 0x304]
  579190: 81 c7 d0 02 00 00            	add	edi, 0x2d0
  579196: 56                           	push	esi
  579197: 8b cf                        	mov	ecx, edi
  579199: c7 45 fc 03 00 00 00         	mov	dword ptr [ebp - 0x4], 0x3
  5791a0: e8 db f1 ff ff               	call	0x578380
  5791a5: 8b 48 40                     	mov	ecx, dword ptr [eax + 0x40]
  5791a8: 2b 48 3c                     	sub	ecx, dword ptr [eax + 0x3c]
  5791ab: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  5791b0: f7 e9                        	imul	ecx
  5791b2: d1 fa                        	sar	edx
  5791b4: 8b c2                        	mov	eax, edx
  5791b6: c1 e8 1f                     	shr	eax, 0x1f
  5791b9: 03 c2                        	add	eax, edx
  5791bb: 0f 84 a7 00 00 00            	je	0x579268 <.text+0x878>
  5791c1: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
  5791c4: 56                           	push	esi
  5791c5: 8b cf                        	mov	ecx, edi
  5791c7: e8 b4 f1 ff ff               	call	0x578380
  5791cc: 8b 50 3c                     	mov	edx, dword ptr [eax + 0x3c]
  5791cf: 8b 48 40                     	mov	ecx, dword ptr [eax + 0x40]
  5791d2: 2b ca                        	sub	ecx, edx
  5791d4: 89 55 ec                     	mov	dword ptr [ebp - 0x14], edx
  5791d7: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  5791dc: f7 e9                        	imul	ecx
  5791de: d1 fa                        	sar	edx
  5791e0: 8b ca                        	mov	ecx, edx
  5791e2: c1 e9 1f                     	shr	ecx, 0x1f
  5791e5: 03 ca                        	add	ecx, edx
  5791e7: 3b d9                        	cmp	ebx, ecx
  5791e9: 0f 83 7e 02 00 00            	jae	0x57946d <.text+0xa7d>
  5791ef: 56                           	push	esi
  5791f0: 8b cf                        	mov	ecx, edi
  5791f2: e8 89 f1 ff ff               	call	0x578380
  5791f7: 8b 48 3c                     	mov	ecx, dword ptr [eax + 0x3c]
  5791fa: 8b 50 40                     	mov	edx, dword ptr [eax + 0x40]
  5791fd: 2b d1                        	sub	edx, ecx
  5791ff: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  579204: f7 ea                        	imul	edx
  579206: d1 fa                        	sar	edx
  579208: 8b c2                        	mov	eax, edx
  57920a: c1 e8 1f                     	shr	eax, 0x1f
  57920d: 03 c2                        	add	eax, edx
  57920f: 3b d8                        	cmp	ebx, eax
  579211: 0f 83 56 02 00 00            	jae	0x57946d <.text+0xa7d>
  579217: 8b 45 f0                     	mov	eax, dword ptr [ebp - 0x10]
  57921a: 8b 4c 08 04                  	mov	ecx, dword ptr [eax + ecx + 0x4]
  57921e: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
  579221: 66 8b 44 10 08               	mov	ax, word ptr [eax + edx + 0x8]
  579226: 89 4d e0                     	mov	dword ptr [ebp - 0x20], ecx
  579229: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  57922c: 51                           	push	ecx
  57922d: 8d 55 d0                     	lea	edx, [ebp - 0x30]
  579230: 52                           	push	edx
  579231: 8d 4d 94                     	lea	ecx, [ebp - 0x6c]
  579234: 66 89 45 e4                  	mov	word ptr [ebp - 0x1c], ax
  579238: e8 e3 a9 ff ff               	call	0x573c20
  57923d: 83 45 f0 0c                  	add	dword ptr [ebp - 0x10], 0xc
  579241: 56                           	push	esi
  579242: 8b cf                        	mov	ecx, edi
  579244: 43                           	inc	ebx
  579245: e8 36 f1 ff ff               	call	0x578380
  57924a: 8b 48 40                     	mov	ecx, dword ptr [eax + 0x40]
  57924d: 2b 48 3c                     	sub	ecx, dword ptr [eax + 0x3c]
  579250: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  579255: f7 e9                        	imul	ecx
  579257: d1 fa                        	sar	edx
  579259: 8b c2                        	mov	eax, edx
  57925b: c1 e8 1f                     	shr	eax, 0x1f
  57925e: 03 c2                        	add	eax, edx
  579260: 3b d8                        	cmp	ebx, eax
  579262: 0f 82 5c ff ff ff            	jb	0x5791c4 <.text+0x7d4>
  579268: 56                           	push	esi
  579269: 8b cf                        	mov	ecx, edi
  57926b: 33 db                        	xor	ebx, ebx
  57926d: e8 0e f1 ff ff               	call	0x578380
  579272: 8b 48 54                     	mov	ecx, dword ptr [eax + 0x54]
  579275: 2b 48 50                     	sub	ecx, dword ptr [eax + 0x50]
  579278: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  57927d: f7 e9                        	imul	ecx
  57927f: d1 fa                        	sar	edx
  579281: 8b ca                        	mov	ecx, edx
  579283: c1 e9 1f                     	shr	ecx, 0x1f
  579286: 03 ca                        	add	ecx, edx
  579288: 0f 84 a7 00 00 00            	je	0x579335 <.text+0x945>
  57928e: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
  579291: 56                           	push	esi
  579292: 8b cf                        	mov	ecx, edi
  579294: e8 e7 f0 ff ff               	call	0x578380
  579299: 8b 50 50                     	mov	edx, dword ptr [eax + 0x50]
  57929c: 8b 48 54                     	mov	ecx, dword ptr [eax + 0x54]
  57929f: 2b ca                        	sub	ecx, edx
  5792a1: 89 55 ec                     	mov	dword ptr [ebp - 0x14], edx
  5792a4: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  5792a9: f7 e9                        	imul	ecx
  5792ab: d1 fa                        	sar	edx
  5792ad: 8b c2                        	mov	eax, edx
  5792af: c1 e8 1f                     	shr	eax, 0x1f
  5792b2: 03 c2                        	add	eax, edx
  5792b4: 3b d8                        	cmp	ebx, eax
  5792b6: 0f 83 b1 01 00 00            	jae	0x57946d <.text+0xa7d>
  5792bc: 56                           	push	esi
  5792bd: 8b cf                        	mov	ecx, edi
  5792bf: e8 bc f0 ff ff               	call	0x578380
  5792c4: 8b 48 50                     	mov	ecx, dword ptr [eax + 0x50]
  5792c7: 8b 50 54                     	mov	edx, dword ptr [eax + 0x54]
  5792ca: 2b d1                        	sub	edx, ecx
  5792cc: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  5792d1: f7 ea                        	imul	edx
  5792d3: d1 fa                        	sar	edx
  5792d5: 8b c2                        	mov	eax, edx
  5792d7: c1 e8 1f                     	shr	eax, 0x1f
  5792da: 03 c2                        	add	eax, edx
  5792dc: 3b d8                        	cmp	ebx, eax
  5792de: 0f 83 89 01 00 00            	jae	0x57946d <.text+0xa7d>
  5792e4: 8b 45 f0                     	mov	eax, dword ptr [ebp - 0x10]
  5792e7: 8b 4c 08 04                  	mov	ecx, dword ptr [eax + ecx + 0x4]
  5792eb: 8b 55 ec                     	mov	edx, dword ptr [ebp - 0x14]
  5792ee: 66 8b 44 10 08               	mov	ax, word ptr [eax + edx + 0x8]
  5792f3: 89 4d e0                     	mov	dword ptr [ebp - 0x20], ecx
  5792f6: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  5792f9: 51                           	push	ecx
  5792fa: 8d 55 d0                     	lea	edx, [ebp - 0x30]
  5792fd: 52                           	push	edx
  5792fe: 8d 4d a8                     	lea	ecx, [ebp - 0x58]
  579301: 66 89 45 e4                  	mov	word ptr [ebp - 0x1c], ax
  579305: e8 16 a9 ff ff               	call	0x573c20
  57930a: 83 45 f0 0c                  	add	dword ptr [ebp - 0x10], 0xc
  57930e: 56                           	push	esi
  57930f: 8b cf                        	mov	ecx, edi
  579311: 43                           	inc	ebx
  579312: e8 69 f0 ff ff               	call	0x578380
  579317: 8b 48 54                     	mov	ecx, dword ptr [eax + 0x54]
  57931a: 2b 48 50                     	sub	ecx, dword ptr [eax + 0x50]
  57931d: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  579322: f7 e9                        	imul	ecx
  579324: d1 fa                        	sar	edx
  579326: 8b c2                        	mov	eax, edx
  579328: c1 e8 1f                     	shr	eax, 0x1f
  57932b: 03 c2                        	add	eax, edx
  57932d: 3b d8                        	cmp	ebx, eax
  57932f: 0f 82 5c ff ff ff            	jb	0x579291 <.text+0x8a1>
  579335: 56                           	push	esi
  579336: 8b cf                        	mov	ecx, edi
  579338: 33 db                        	xor	ebx, ebx
  57933a: e8 41 f0 ff ff               	call	0x578380
  57933f: 8b 48 68                     	mov	ecx, dword ptr [eax + 0x68]
  579342: 2b 48 64                     	sub	ecx, dword ptr [eax + 0x64]
  579345: b8 ab aa aa 2a               	mov	eax, 0x2aaaaaab
  57934a: f7 e9                        	imul	ecx
  57934c: d1 fa                        	sar	edx
  57934e: 8b ca                        	mov	ecx, edx
  579350: c1 e9 1f                     	shr	ecx, 0x1f
  579353: 03 ca                        	add	ecx, edx
  579355: 0f 84 a9 00 00 00            	je	0x579404 <.text+0xa14>
  57935b: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
  57935e: 8b ff                        	mov	edi, edi
  579360: 56                           	push	esi
  579361: 8b cf                        	mov	ecx, edi
  579363: e8 18 f0 ff ff               	call	0x578380
  579368: 8b 50 64                     	mov	edx, dword ptr [eax + 0x64]
  57936b: 8b 48 68                     	mov	ecx, dword ptr [eax + 0x68]
  57936e: 2b ca                        	sub	ecx, edx
