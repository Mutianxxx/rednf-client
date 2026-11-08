
<stdin>:	file format elf32-i386

Disassembly of section .text:

01142e90 <.text>:
 1142e90: 56                           	push	esi
 1142e91: 8b f1                        	mov	esi, ecx
 1142e93: 57                           	push	edi
 1142e94: 68 78 21 56 01               	push	0x1562178
 1142e99: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 1142e9f: c7 46 04 00 00 00 00         	mov	dword ptr [esi + 0x4], 0x0
 1142ea6: e8 45 d0 05 00               	call	0x119fef0 <.text+0x5d060>
 1142eab: 8b c8                        	mov	ecx, eax
 1142ead: 83 c4 04                     	add	esp, 0x4
 1142eb0: 8d 79 02                     	lea	edi, [ecx + 0x2]
 1142eb3: 66 8b 11                     	mov	dx, word ptr [ecx]
 1142eb6: 83 c1 02                     	add	ecx, 0x2
 1142eb9: 66 85 d2                     	test	dx, dx
 1142ebc: 75 f5                        	jne	0x1142eb3 <.text+0x23>
 1142ebe: 2b cf                        	sub	ecx, edi
 1142ec0: d1 f9                        	sar	ecx
 1142ec2: 51                           	push	ecx
 1142ec3: 50                           	push	eax
 1142ec4: 8d 4e 0c                     	lea	ecx, [esi + 0xc]
 1142ec7: e8 64 d1 2c ff               	call	0x410030
 1142ecc: 68 78 21 56 01               	push	0x1562178
 1142ed1: e8 1a d0 05 00               	call	0x119fef0 <.text+0x5d060>
 1142ed6: 8b c8                        	mov	ecx, eax
 1142ed8: 83 c4 04                     	add	esp, 0x4
 1142edb: 8d 79 02                     	lea	edi, [ecx + 0x2]
 1142ede: 8b ff                        	mov	edi, edi
 1142ee0: 66 8b 11                     	mov	dx, word ptr [ecx]
 1142ee3: 83 c1 02                     	add	ecx, 0x2
 1142ee6: 66 85 d2                     	test	dx, dx
 1142ee9: 75 f5                        	jne	0x1142ee0 <.text+0x50>
 1142eeb: 2b cf                        	sub	ecx, edi
 1142eed: d1 f9                        	sar	ecx
 1142eef: 51                           	push	ecx
 1142ef0: 50                           	push	eax
 1142ef1: 8d 4e 2c                     	lea	ecx, [esi + 0x2c]
 1142ef4: e8 37 d1 2c ff               	call	0x410030
 1142ef9: 5f                           	pop	edi
 1142efa: c7 46 08 00 00 00 00         	mov	dword ptr [esi + 0x8], 0x0
 1142f01: 8d 4e 4c                     	lea	ecx, [esi + 0x4c]
 1142f04: 5e                           	pop	esi
 1142f05: e9 f6 fe ff ff               	jmp	0x1142e00
 1142f0a: cc                           	int3
 1142f0b: cc                           	int3
 1142f0c: cc                           	int3
 1142f0d: cc                           	int3
 1142f0e: cc                           	int3
 1142f0f: cc                           	int3
 1142f10: 55                           	push	ebp
 1142f11: 8b ec                        	mov	ebp, esp
 1142f13: 6a ff                        	push	-0x1
 1142f15: 68 d1 1a 4c 01               	push	0x14c1ad1
 1142f1a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1142f20: 50                           	push	eax
 1142f21: 83 ec 34                     	sub	esp, 0x34
 1142f24: 53                           	push	ebx
 1142f25: 56                           	push	esi
 1142f26: 57                           	push	edi
 1142f27: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1142f2c: 33 c5                        	xor	eax, ebp
 1142f2e: 50                           	push	eax
 1142f2f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1142f32: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1142f38: 8b f9                        	mov	edi, ecx
 1142f3a: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
 1142f3d: 8d 77 0c                     	lea	esi, [edi + 0xc]
 1142f40: 33 db                        	xor	ebx, ebx
 1142f42: 6a 08                        	push	0x8
 1142f44: 89 1e                        	mov	dword ptr [esi], ebx
 1142f46: e8 cf 3b 29 00               	call	0x13d6b1a <.text+0x293c8a>
 1142f4b: 83 c4 04                     	add	esp, 0x4
 1142f4e: 3b c3                        	cmp	eax, ebx
 1142f50: 0f 84 ec 00 00 00            	je	0x1143042 <.text+0x1b2>
 1142f56: 89 06                        	mov	dword ptr [esi], eax
 1142f58: 33 c9                        	xor	ecx, ecx
 1142f5a: 89 08                        	mov	dword ptr [eax], ecx
 1142f5c: 33 d2                        	xor	edx, edx
 1142f5e: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1142f61: 8b 06                        	mov	eax, dword ptr [esi]
 1142f63: 89 30                        	mov	dword ptr [eax], esi
 1142f65: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 1142f6c: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 1142f6f: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 1142f73: 8d 77 2c                     	lea	esi, [edi + 0x2c]
 1142f76: 6a 08                        	push	0x8
 1142f78: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 1142f7b: 89 1e                        	mov	dword ptr [esi], ebx
 1142f7d: e8 98 3b 29 00               	call	0x13d6b1a <.text+0x293c8a>
 1142f82: 83 c4 04                     	add	esp, 0x4
 1142f85: 3b c3                        	cmp	eax, ebx
 1142f87: 0f 84 91 00 00 00            	je	0x114301e <.text+0x18e>
 1142f8d: 89 06                        	mov	dword ptr [esi], eax
 1142f8f: 33 d2                        	xor	edx, edx
 1142f91: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1142f94: 33 c9                        	xor	ecx, ecx
 1142f96: 89 08                        	mov	dword ptr [eax], ecx
 1142f98: 8b 16                        	mov	edx, dword ptr [esi]
 1142f9a: 89 32                        	mov	dword ptr [edx], esi
 1142f9c: 33 c0                        	xor	eax, eax
 1142f9e: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 1142fa5: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 1142fa8: 66 89 46 04                  	mov	word ptr [esi + 0x4], ax
 1142fac: 8d 77 4c                     	lea	esi, [edi + 0x4c]
 1142faf: 6a 08                        	push	0x8
 1142fb1: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1142fb5: 89 1e                        	mov	dword ptr [esi], ebx
 1142fb7: e8 5e 3b 29 00               	call	0x13d6b1a <.text+0x293c8a>
 1142fbc: 83 c4 04                     	add	esp, 0x4
 1142fbf: 3b c3                        	cmp	eax, ebx
 1142fc1: 74 37                        	je	0x1142ffa <.text+0x16a>
 1142fc3: 89 06                        	mov	dword ptr [esi], eax
 1142fc5: 33 c9                        	xor	ecx, ecx
 1142fc7: 89 08                        	mov	dword ptr [eax], ecx
 1142fc9: 33 d2                        	xor	edx, edx
 1142fcb: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1142fce: 8b 0e                        	mov	ecx, dword ptr [esi]
 1142fd0: 89 31                        	mov	dword ptr [ecx], esi
 1142fd2: 89 5e 04                     	mov	dword ptr [esi + 0x4], ebx
 1142fd5: 89 5e 08                     	mov	dword ptr [esi + 0x8], ebx
 1142fd8: 89 5e 0c                     	mov	dword ptr [esi + 0xc], ebx
 1142fdb: 8b cf                        	mov	ecx, edi
 1142fdd: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 1142fe1: e8 aa fe ff ff               	call	0x1142e90 <.text>
 1142fe6: 8b c7                        	mov	eax, edi
 1142fe8: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1142feb: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1142ff2: 59                           	pop	ecx
 1142ff3: 5f                           	pop	edi
 1142ff4: 5e                           	pop	esi
 1142ff5: 5b                           	pop	ebx
 1142ff6: 8b e5                        	mov	esp, ebp
 1142ff8: 5d                           	pop	ebp
 1142ff9: c3                           	ret
 1142ffa: 8d 55 f0                     	lea	edx, [ebp - 0x10]
 1142ffd: 52                           	push	edx
 1142ffe: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
 1143001: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 1143004: e8 c1 34 29 00               	call	0x13d64ca <.text+0x29363a>
 1143009: 68 90 0f 91 01               	push	0x1910f90
 114300e: 8d 45 d8                     	lea	eax, [ebp - 0x28]
 1143011: 50                           	push	eax
 1143012: c7 45 d8 84 20 56 01         	mov	dword ptr [ebp - 0x28], 0x1562084
 1143019: e8 7c 3b 29 00               	call	0x13d6b9a <.text+0x293d0a>
 114301e: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 1143021: 51                           	push	ecx
 1143022: 8d 4d cc                     	lea	ecx, [ebp - 0x34]
 1143025: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
 1143028: e8 9d 34 29 00               	call	0x13d64ca <.text+0x29363a>
 114302d: 68 90 0f 91 01               	push	0x1910f90
 1143032: 8d 55 cc                     	lea	edx, [ebp - 0x34]
 1143035: 52                           	push	edx
 1143036: c7 45 cc 84 20 56 01         	mov	dword ptr [ebp - 0x34], 0x1562084
 114303d: e8                           	<unknown>
 114303e: 58                           	pop	eax
 114303f: 3b                           	<unknown>
