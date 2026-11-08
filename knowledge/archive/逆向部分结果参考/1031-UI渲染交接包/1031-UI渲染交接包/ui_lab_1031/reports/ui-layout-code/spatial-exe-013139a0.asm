
<stdin>:	file format elf32-i386

Disassembly of section .text:

013139a0 <.text>:
 13139a0: 56                           	push	esi
 13139a1: 57                           	push	edi
 13139a2: 8b f1                        	mov	esi, ecx
 13139a4: 68 78 21 56 01               	push	0x1562178
 13139a9: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 13139af: e8 3c c5 e8 ff               	call	0x119fef0
 13139b4: 8b c8                        	mov	ecx, eax
 13139b6: 83 c4 04                     	add	esp, 0x4
 13139b9: 8d 79 02                     	lea	edi, [ecx + 0x2]
 13139bc: 8d 64 24 00                  	lea	esp, [esp]
 13139c0: 66 8b 11                     	mov	dx, word ptr [ecx]
 13139c3: 83 c1 02                     	add	ecx, 0x2
 13139c6: 66 85 d2                     	test	dx, dx
 13139c9: 75 f5                        	jne	0x13139c0 <.text+0x20>
 13139cb: 2b cf                        	sub	ecx, edi
 13139cd: d1 f9                        	sar	ecx
 13139cf: 51                           	push	ecx
 13139d0: 50                           	push	eax
 13139d1: 8d 4e 18                     	lea	ecx, [esi + 0x18]
 13139d4: e8 57 c6 0f ff               	call	0x410030
 13139d9: 5f                           	pop	edi
 13139da: c7 46 38 00 00 00 00         	mov	dword ptr [esi + 0x38], 0x0
 13139e1: 8d 4e 04                     	lea	ecx, [esi + 0x4]
 13139e4: 5e                           	pop	esi
 13139e5: e9 26 31 e2 ff               	jmp	0x1136b10
 13139ea: cc                           	int3
 13139eb: cc                           	int3
 13139ec: cc                           	int3
 13139ed: cc                           	int3
 13139ee: cc                           	int3
 13139ef: cc                           	int3
 13139f0: 55                           	push	ebp
 13139f1: 8b ec                        	mov	ebp, esp
 13139f3: 6a ff                        	push	-0x1
 13139f5: 68 56 a6 4d 01               	push	0x14da656
 13139fa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1313a00: 50                           	push	eax
 1313a01: 83 ec 24                     	sub	esp, 0x24
 1313a04: 53                           	push	ebx
 1313a05: 56                           	push	esi
 1313a06: 57                           	push	edi
 1313a07: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1313a0c: 33 c5                        	xor	eax, ebp
 1313a0e: 50                           	push	eax
 1313a0f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1313a12: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1313a18: 8b d9                        	mov	ebx, ecx
 1313a1a: 89 5d e8                     	mov	dword ptr [ebp - 0x18], ebx
 1313a1d: 8d 7b 04                     	lea	edi, [ebx + 0x4]
 1313a20: 33 f6                        	xor	esi, esi
 1313a22: 6a 08                        	push	0x8
 1313a24: 89 37                        	mov	dword ptr [edi], esi
 1313a26: e8 ef 30 0c 00               	call	0x13d6b1a <.text+0xc317a>
 1313a2b: 83 c4 04                     	add	esp, 0x4
 1313a2e: 3b c6                        	cmp	eax, esi
 1313a30: 0f 84 c9 00 00 00            	je	0x1313aff <.text+0x15f>
 1313a36: 89 07                        	mov	dword ptr [edi], eax
 1313a38: 89 70 04                     	mov	dword ptr [eax + 0x4], esi
 1313a3b: 33 c9                        	xor	ecx, ecx
 1313a3d: 89 08                        	mov	dword ptr [eax], ecx
 1313a3f: 8b 07                        	mov	eax, dword ptr [edi]
 1313a41: 89 38                        	mov	dword ptr [eax], edi
 1313a43: 89 77 04                     	mov	dword ptr [edi + 0x4], esi
 1313a46: 89 77 08                     	mov	dword ptr [edi + 0x8], esi
 1313a49: 89 77 0c                     	mov	dword ptr [edi + 0xc], esi
 1313a4c: 89 75 fc                     	mov	dword ptr [ebp - 0x4], esi
 1313a4f: 8d 73 18                     	lea	esi, [ebx + 0x18]
 1313a52: 6a 08                        	push	0x8
 1313a54: 89 0e                        	mov	dword ptr [esi], ecx
 1313a56: e8 bf 30 0c 00               	call	0x13d6b1a <.text+0xc317a>
 1313a5b: 33 c9                        	xor	ecx, ecx
 1313a5d: 83 c4 04                     	add	esp, 0x4
 1313a60: 3b c1                        	cmp	eax, ecx
 1313a62: 74 77                        	je	0x1313adb <.text+0x13b>
 1313a64: 89 06                        	mov	dword ptr [esi], eax
 1313a66: 33 d2                        	xor	edx, edx
 1313a68: 89 08                        	mov	dword ptr [eax], ecx
 1313a6a: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1313a6d: 8b 0e                        	mov	ecx, dword ptr [esi]
 1313a6f: 89 31                        	mov	dword ptr [ecx], esi
 1313a71: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 1313a78: 89 56 14                     	mov	dword ptr [esi + 0x14], edx
 1313a7b: 66 89 56 04                  	mov	word ptr [esi + 0x4], dx
 1313a7f: 68 78 21 56 01               	push	0x1562178
 1313a84: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1313a88: 89 13                        	mov	dword ptr [ebx], edx
 1313a8a: e8 61 c4 e8 ff               	call	0x119fef0
 1313a8f: 8b c8                        	mov	ecx, eax
 1313a91: 8d 51 02                     	lea	edx, [ecx + 0x2]
 1313a94: 83 c4 04                     	add	esp, 0x4
 1313a97: 89 55 f0                     	mov	dword ptr [ebp - 0x10], edx
 1313a9a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
