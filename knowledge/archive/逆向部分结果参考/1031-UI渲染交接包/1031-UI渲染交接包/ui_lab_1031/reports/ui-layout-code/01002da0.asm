
<stdin>:	file format elf32-i386

Disassembly of section .text:

01002da0 <.text>:
 1002da0: 55                           	push	ebp
 1002da1: 8b ec                        	mov	ebp, esp
 1002da3: 6a ff                        	push	-0x1
 1002da5: 68 d8 51 4d 01               	push	0x14d51d8
 1002daa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1002db0: 50                           	push	eax
 1002db1: 83 ec 10                     	sub	esp, 0x10
 1002db4: 53                           	push	ebx
 1002db5: 56                           	push	esi
 1002db6: 57                           	push	edi
 1002db7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1002dbc: 33 c5                        	xor	eax, ebp
 1002dbe: 50                           	push	eax
 1002dbf: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1002dc2: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1002dc8: 8b f9                        	mov	edi, ecx
 1002dca: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 1002dcd: 8b 03                        	mov	eax, dword ptr [ebx]
 1002dcf: 89 07                        	mov	dword ptr [edi], eax
 1002dd1: 8b 4b 04                     	mov	ecx, dword ptr [ebx + 0x4]
 1002dd4: 89 4f 04                     	mov	dword ptr [edi + 0x4], ecx
 1002dd7: 8b 53 08                     	mov	edx, dword ptr [ebx + 0x8]
 1002dda: 89 57 08                     	mov	dword ptr [edi + 0x8], edx
 1002ddd: 8b 43 0c                     	mov	eax, dword ptr [ebx + 0xc]
 1002de0: 89 47 0c                     	mov	dword ptr [edi + 0xc], eax
 1002de3: 8b 4b 10                     	mov	ecx, dword ptr [ebx + 0x10]
 1002de6: 89 4f 10                     	mov	dword ptr [edi + 0x10], ecx
 1002de9: 8b 53 14                     	mov	edx, dword ptr [ebx + 0x14]
 1002dec: 8d 77 18                     	lea	esi, [edi + 0x18]
 1002def: 89 57 14                     	mov	dword ptr [edi + 0x14], edx
 1002df2: 6a 08                        	push	0x8
 1002df4: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
 1002df7: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 1002dfd: e8 18 3d 3d 00               	call	0x13d6b1a <.text+0x3d3d7a>
 1002e02: 33 c9                        	xor	ecx, ecx
 1002e04: 83 c4 04                     	add	esp, 0x4
 1002e07: 3b c1                        	cmp	eax, ecx
 1002e09: 74 44                        	je	0x1002e4f <.text+0xaf>
 1002e0b: 89 06                        	mov	dword ptr [esi], eax
 1002e0d: 33 d2                        	xor	edx, edx
 1002e0f: 89 08                        	mov	dword ptr [eax], ecx
 1002e11: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1002e14: 8b 06                        	mov	eax, dword ptr [esi]
 1002e16: 89 30                        	mov	dword ptr [eax], esi
 1002e18: 33 c0                        	xor	eax, eax
 1002e1a: 6a ff                        	push	-0x1
 1002e1c: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 1002e23: 89 46 14                     	mov	dword ptr [esi + 0x14], eax
 1002e26: 50                           	push	eax
 1002e27: 83 c3 18                     	add	ebx, 0x18
 1002e2a: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 1002e2e: 53                           	push	ebx
 1002e2f: 8b ce                        	mov	ecx, esi
 1002e31: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 1002e34: e8 f7 24 40 ff               	call	0x405330
 1002e39: 8b c7                        	mov	eax, edi
 1002e3b: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1002e3e: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1002e45: 59                           	pop	ecx
 1002e46: 5f                           	pop	edi
 1002e47: 5e                           	pop	esi
 1002e48: 5b                           	pop	ebx
 1002e49: 8b e5                        	mov	esp, ebp
 1002e4b: 5d                           	pop	ebp
 1002e4c: c2 04 00                     	ret	0x4
 1002e4f: 8d 55 08                     	lea	edx, [ebp + 0x8]
 1002e52: 89 4d 08                     	mov	dword ptr [ebp + 0x8], ecx
 1002e55: 52                           	push	edx
 1002e56: 8d 4d e4                     	lea	ecx, [ebp - 0x1c]
 1002e59: e8 6c 36 3d 00               	call	0x13d64ca <.text+0x3d372a>
 1002e5e: 68 90 0f 91 01               	push	0x1910f90
 1002e63: 8d 45 e4                     	lea	eax, [ebp - 0x1c]
 1002e66: 50                           	push	eax
 1002e67: c7 45 e4 84 20 56 01         	mov	dword ptr [ebp - 0x1c], 0x1562084
 1002e6e: e8 27 3d 3d 00               	call	0x13d6b9a <.text+0x3d3dfa>
 1002e73: cc                           	int3
 1002e74: cc                           	int3
 1002e75: cc                           	int3
 1002e76: cc                           	int3
 1002e77: cc                           	int3
 1002e78: cc                           	int3
 1002e79: cc                           	int3
 1002e7a: cc                           	int3
 1002e7b: cc                           	int3
 1002e7c: cc                           	int3
 1002e7d: cc                           	int3
 1002e7e: cc                           	int3
 1002e7f: cc                           	int3
 1002e80: 53                           	push	ebx
 1002e81: 56                           	push	esi
 1002e82: 8b f1                        	mov	esi, ecx
 1002e84: 83 c8 ff                     	or	eax, -0x1
 1002e87: 68 78 21 56 01               	push	0x1562178
 1002e8c: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 1002e92: c7 46 04 00 00 00 00         	mov	dword ptr [esi + 0x4], 0x0
 1002e99: c7 46 08 00 00 00 00         	mov	dword ptr [esi + 0x8], 0x0
 1002ea0: c7 46 0c 00 00 00 00         	mov	dword ptr [esi + 0xc], 0x0
 1002ea7: 89 46 10                     	mov	dword ptr [esi + 0x10], eax
 1002eaa: 89 46 14                     	mov	dword ptr [esi + 0x14], eax
 1002ead: e8 3e d0 19 00               	call	0x119fef0 <.text+0x19d150>
 1002eb2: 8b c8                        	mov	ecx, eax
 1002eb4: 83 c4 04                     	add	esp, 0x4
 1002eb7: 8d 59 02                     	lea	ebx, [ecx + 0x2]
 1002eba: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 1002ec0: 66 8b 11                     	mov	dx, word ptr [ecx]
 1002ec3: 83 c1 02                     	add	ecx, 0x2
 1002ec6: 66 85 d2                     	test	dx, dx
 1002ec9: 75 f5                        	jne	0x1002ec0 <.text+0x120>
 1002ecb: 2b cb                        	sub	ecx, ebx
 1002ecd: d1 f9                        	sar	ecx
 1002ecf: 51                           	push	ecx
 1002ed0: 50                           	push	eax
 1002ed1: 8d 4e 18                     	lea	ecx, [esi + 0x18]
 1002ed4: e8 57 d1 40 ff               	call	0x410030
 1002ed9: 5e                           	pop	esi
 1002eda: 5b                           	pop	ebx
 1002edb: c3                           	ret
 1002edc: cc                           	int3
 1002edd: cc                           	int3
 1002ede: cc                           	int3
 1002edf: cc                           	int3
 1002ee0: 55                           	push	ebp
 1002ee1: 8b ec                        	mov	ebp, esp
 1002ee3: 56                           	push	esi
 1002ee4: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 1002ee7: 83 7e 30 08                  	cmp	dword ptr [esi + 0x30], 0x8
 1002eeb: 72 0c                        	jb	0x1002ef9 <.text+0x159>
 1002eed: 8b 46 1c                     	mov	eax, dword ptr [esi + 0x1c]
 1002ef0: 50                           	push	eax
 1002ef1: e8 31 2c 3d 00               	call	0x13d5b27 <.text+0x3d2d87>
 1002ef6: 83 c4 04                     	add	esp, 0x4
 1002ef9: 33 c9                        	xor	ecx, ecx
 1002efb: c7 46 30 07 00 00 00         	mov	dword ptr [esi + 0x30], 0x7
 1002f02: c7 46 2c 00 00 00 00         	mov	dword ptr [esi + 0x2c], 0x0
 1002f09: 66 89 4e 1c                  	mov	word ptr [esi + 0x1c], cx
 1002f0d: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 1002f10: 52                           	push	edx
 1002f11: e8 11 2c 3d 00               	call	0x13d5b27 <.text+0x3d2d87>
 1002f16: 83 c4 04                     	add	esp, 0x4
 1002f19: c7 46 18 00 00 00 00         	mov	dword ptr [esi + 0x18], 0x0
 1002f20: 5e                           	pop	esi
 1002f21: 5d                           	pop	ebp
 1002f22: c3                           	ret
 1002f23: cc                           	int3
 1002f24: cc                           	int3
 1002f25: cc                           	int3
 1002f26: cc                           	int3
 1002f27: cc                           	int3
 1002f28: cc                           	int3
 1002f29: cc                           	int3
 1002f2a: cc                           	int3
 1002f2b: cc                           	int3
 1002f2c: cc                           	int3
 1002f2d: cc                           	int3
 1002f2e: cc                           	int3
 1002f2f: cc                           	int3
 1002f30: 55                           	push	ebp
 1002f31: 8b ec                        	mov	ebp, esp
 1002f33: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 1002f36: 53                           	push	ebx
 1002f37: 8b 5d 0c                     	mov	ebx, dword ptr [ebp + 0xc]
 1002f3a: 3b c3                        	cmp	eax, ebx
 1002f3c: 74 42                        	je	0x1002f80 <.text+0x1e0>
 1002f3e: 56                           	push	esi
 1002f3f: 57                           	push	edi
 1002f40: 8d 70 30                     	lea	esi, [eax + 0x30]
 1002f43: 33 ff                        	xor	edi, edi
 1002f45: 83 3e 08                     	cmp	dword ptr [esi], 0x8
 1002f48: 72 0c                        	jb	0x1002f56 <.text+0x1b6>
 1002f4a: 8b 46 ec                     	mov	eax, dword ptr [esi - 0x14]
 1002f4d: 50                           	push	eax
 1002f4e: e8 d4 2b 3d 00               	call	0x13d5b27 <.text+0x3d2d87>
 1002f53: 83 c4 04                     	add	esp, 0x4
 1002f56: 33 c9                        	xor	ecx, ecx
 1002f58: c7 06 07 00 00 00            	mov	dword ptr [esi], 0x7
 1002f5e: 89 7e fc                     	mov	dword ptr [esi - 0x4], edi
 1002f61: 66 89 4e ec                  	mov	word ptr [esi - 0x14], cx
 1002f65: 8b 56 e8                     	mov	edx, dword ptr [esi - 0x18]
 1002f68: 52                           	push	edx
 1002f69: e8 b9 2b 3d 00               	call	0x13d5b27 <.text+0x3d2d87>
 1002f6e: 89 7e e8                     	mov	dword ptr [esi - 0x18], edi
 1002f71: 83 c6 38                     	add	esi, 0x38
 1002f74: 8d 46 d0                     	lea	eax, [esi - 0x30]
 1002f77: 83 c4 04                     	add	esp, 0x4
 1002f7a: 3b c3                        	cmp	eax, ebx
 1002f7c: 75 c7                        	jne	0x1002f45 <.text+0x1a5>
 1002f7e: 5f                           	pop	edi
 1002f7f: 5e                           	pop	esi
 1002f80: 5b                           	pop	ebx
 1002f81: 5d                           	pop	ebp
 1002f82: c3                           	ret
 1002f83: cc                           	int3
 1002f84: cc                           	int3
 1002f85: cc                           	int3
 1002f86: cc                           	int3
 1002f87: cc                           	int3
 1002f88: cc                           	int3
 1002f89: cc                           	int3
 1002f8a: cc                           	int3
 1002f8b: cc                           	int3
 1002f8c: cc                           	int3
 1002f8d: cc                           	int3
 1002f8e: cc                           	int3
 1002f8f: cc                           	int3
 1002f90: 55                           	push	ebp
 1002f91: 8b ec                        	mov	ebp, esp
 1002f93: 6a ff                        	push	-0x1
 1002f95: 68 91 2c 4b 01               	push	0x14b2c91
 1002f9a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1002fa0: 50                           	push	eax
 1002fa1: 83 ec 08                     	sub	esp, 0x8
 1002fa4: 53                           	push	ebx
 1002fa5: 56                           	push	esi
 1002fa6: 57                           	push	edi
 1002fa7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1002fac: 33 c5                        	xor	eax, ebp
 1002fae: 50                           	push	eax
 1002faf: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1002fb2: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1002fb8: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
 1002fbb: 8b 75 10                     	mov	esi, dword ptr [ebp + 0x10]
 1002fbe: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 1002fc1: 33 db                        	xor	ebx, ebx
 1002fc3: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
 1002fc6: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 1002fc9: 8d a4 24 00 00 00 00         	lea	esp, [esp]
 1002fd0: 3b 7d 0c                     	cmp	edi, dword ptr [ebp + 0xc]
 1002fd3: 74 48                        	je	0x100301d <.text+0x27d>
 1002fd5: 89 75 08                     	mov	dword ptr [ebp + 0x8], esi
 1002fd8: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1002fdc: 3b f3                        	cmp	esi, ebx
 1002fde: 74 08                        	je	0x1002fe8 <.text+0x248>
 1002fe0: 57                           	push	edi
 1002fe1: 8b ce                        	mov	ecx, esi
 1002fe3: e8 b8 fd ff ff               	call	0x1002da0 <.text>
 1002fe8: 83 c6 38                     	add	esi, 0x38
 1002feb: 88 5d fc                     	mov	byte ptr [ebp - 0x4], bl
 1002fee: 89 75 10                     	mov	dword ptr [ebp + 0x10], esi
 1002ff1: 83 c7 38                     	add	edi, 0x38
 1002ff4: eb da                        	jmp	0x1002fd0 <.text+0x230>
 1002ff6: 8b 75 ec                     	mov	esi, dword ptr [ebp - 0x14]
 1002ff9: 8b 7d 10                     	mov	edi, dword ptr [ebp + 0x10]
 1002ffc: 3b f7                        	cmp	esi, edi
 1002ffe: 74 14                        	je	0x1003014 <.text+0x274>
 1003000: 8b 5d 14                     	mov	ebx, dword ptr [ebp + 0x14]
 1003003: 56                           	push	esi
 1003004: 53                           	push	ebx
 1003005: e8 d6 fe ff ff               	call	0x1002ee0 <.text+0x140>
 100300a: 83 c6 38                     	add	esi, 0x38
 100300d: 83 c4 08                     	add	esp, 0x8
 1003010: 3b f7                        	cmp	esi, edi
 1003012: 75 ef                        	jne	0x1003003 <.text+0x263>
 1003014: 33 db                        	xor	ebx, ebx
 1003016: 53                           	push	ebx
 1003017: 53                           	push	ebx
 1003018: e8 7d 3b 3d 00               	call	0x13d6b9a <.text+0x3d3dfa>
 100301d: 8b c6                        	mov	eax, esi
 100301f: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1003022: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1003029: 59                           	pop	ecx
 100302a: 5f                           	pop	edi
 100302b: 5e                           	pop	esi
 100302c: 5b                           	pop	ebx
 100302d: 8b e5                        	mov	esp, ebp
 100302f: 5d                           	pop	ebp
 1003030: c3                           	ret
 1003031: cc                           	int3
 1003032: cc                           	int3
 1003033: cc                           	int3
 1003034: cc                           	int3
 1003035: cc                           	int3
 1003036: cc                           	int3
 1003037: cc                           	int3
 1003038: cc                           	int3
 1003039: cc                           	int3
 100303a: cc                           	int3
 100303b: cc                           	int3
 100303c: cc                           	int3
 100303d: cc                           	int3
 100303e: cc                           	int3
 100303f: cc                           	int3
 1003040: 55                           	push	ebp
 1003041: 8b ec                        	mov	ebp, esp
 1003043: 6a ff                        	push	-0x1
 1003045: 68 b0 2c 4b 01               	push	0x14b2cb0
 100304a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1003050: 50                           	push	eax
 1003051: 83 ec 08                     	sub	esp, 0x8
 1003054: 53                           	push	ebx
 1003055: 56                           	push	esi
 1003056: 57                           	push	edi
 1003057: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 100305c: 33 c5                        	xor	eax, ebp
 100305e: 50                           	push	eax
 100305f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1003062: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1003068: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
 100306b: 8b f1                        	mov	esi, ecx
 100306d: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
