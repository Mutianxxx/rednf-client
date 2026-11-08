
<stdin>:	file format elf32-i386

Disassembly of section .text:

01002c60 <.text>:
 1002c60: 8b b3 c8 03 00 00            	mov	esi, dword ptr [ebx + 0x3c8]
 1002c66: 2b ce                        	sub	ecx, esi
 1002c68: b8 93 24 49 92               	mov	eax, 0x92492493
 1002c6d: f7 e9                        	imul	ecx
 1002c6f: 03 d1                        	add	edx, ecx
 1002c71: c1 fa 05                     	sar	edx, 0x5
 1002c74: 8b c2                        	mov	eax, edx
 1002c76: c1 e8 1f                     	shr	eax, 0x1f
 1002c79: 03 c2                        	add	eax, edx
 1002c7b: 3b f8                        	cmp	edi, eax
 1002c7d: 0f 83 87 00 00 00            	jae	0x1002d0a <.text+0xaa>
 1002c83: 8d 0c fd 00 00 00 00         	lea	ecx, [8*edi]
 1002c8a: 2b cf                        	sub	ecx, edi
 1002c8c: 68 78 21 56 01               	push	0x1562178
 1002c91: 8d 34 ce                     	lea	esi, [esi + 8*ecx]
 1002c94: e8 57 d2 19 00               	call	0x119fef0 <.text+0x19d290>
 1002c99: 8b c8                        	mov	ecx, eax
 1002c9b: 8d 51 02                     	lea	edx, [ecx + 0x2]
 1002c9e: 83 c4 04                     	add	esp, 0x4
 1002ca1: 8d 7e 18                     	lea	edi, [esi + 0x18]
 1002ca4: 89 55 fc                     	mov	dword ptr [ebp - 0x4], edx
 1002ca7: 66 8b 11                     	mov	dx, word ptr [ecx]
 1002caa: 83 c1 02                     	add	ecx, 0x2
 1002cad: 66 85 d2                     	test	dx, dx
 1002cb0: 75 f5                        	jne	0x1002ca7 <.text+0x47>
 1002cb2: 2b 4d fc                     	sub	ecx, dword ptr [ebp - 0x4]
 1002cb5: d1 f9                        	sar	ecx
 1002cb7: 51                           	push	ecx
 1002cb8: 50                           	push	eax
 1002cb9: 8b 47 14                     	mov	eax, dword ptr [edi + 0x14]
 1002cbc: 50                           	push	eax
 1002cbd: 6a 00                        	push	0x0
 1002cbf: 8b cf                        	mov	ecx, edi
 1002cc1: e8 6a ef 3f ff               	call	0x401c30
 1002cc6: 85 c0                        	test	eax, eax
 1002cc8: 74 2c                        	je	0x1002cf6 <.text+0x96>
 1002cca: 83 7f 18 08                  	cmp	dword ptr [edi + 0x18], 0x8
 1002cce: 72 13                        	jb	0x1002ce3 <.text+0x83>
 1002cd0: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 1002cd6: 8b 7f 04                     	mov	edi, dword ptr [edi + 0x4]
 1002cd9: 8b 11                        	mov	edx, dword ptr [ecx]
 1002cdb: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 1002cde: 57                           	push	edi
 1002cdf: ff d0                        	call	eax
 1002ce1: eb 21                        	jmp	0x1002d04 <.text+0xa4>
 1002ce3: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 1002ce9: 8b 11                        	mov	edx, dword ptr [ecx]
 1002ceb: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 1002cee: 83 c7 04                     	add	edi, 0x4
 1002cf1: 57                           	push	edi
 1002cf2: ff d0                        	call	eax
 1002cf4: eb 0e                        	jmp	0x1002d04 <.text+0xa4>
 1002cf6: 8b 0e                        	mov	ecx, dword ptr [esi]
 1002cf8: 51                           	push	ecx
 1002cf9: 8b 0d 70 a8 a6 01            	mov	ecx, dword ptr [0x1a6a870]
 1002cff: e8 ac 84 1b 00               	call	0x11bb1b0 <.text+0x1b8550>
 1002d04: 8b f8                        	mov	edi, eax
 1002d06: 85 ff                        	test	edi, edi
 1002d08: 75 0b                        	jne	0x1002d15 <.text+0xb5>
 1002d0a: 5e                           	pop	esi
 1002d0b: 5f                           	pop	edi
 1002d0c: 32 c0                        	xor	al, al
 1002d0e: 5b                           	pop	ebx
 1002d0f: 8b e5                        	mov	esp, ebp
 1002d11: 5d                           	pop	ebp
 1002d12: c2 04 00                     	ret	0x4
 1002d15: 6a 03                        	push	0x3
 1002d17: 8b cf                        	mov	ecx, edi
 1002d19: e8 22 6b 7b ff               	call	0x7b9840
 1002d1e: 8b 13                        	mov	edx, dword ptr [ebx]
 1002d20: 8b 42 08                     	mov	eax, dword ptr [edx + 0x8]
 1002d23: 8b cb                        	mov	ecx, ebx
 1002d25: ff d0                        	call	eax
 1002d27: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 1002d2a: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 1002d2d: 8b 13                        	mov	edx, dword ptr [ebx]
 1002d2f: 8b 92 b0 00 00 00            	mov	edx, dword ptr [edx + 0xb0]
 1002d35: 50                           	push	eax
 1002d36: 8b 46 0c                     	mov	eax, dword ptr [esi + 0xc]
 1002d39: 51                           	push	ecx
 1002d3a: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
 1002d3d: 50                           	push	eax
 1002d3e: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
 1002d41: 51                           	push	ecx
 1002d42: 50                           	push	eax
 1002d43: 57                           	push	edi
 1002d44: 8b cb                        	mov	ecx, ebx
 1002d46: ff d2                        	call	edx
 1002d48: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 1002d4b: 5e                           	pop	esi
 1002d4c: 89 83 d8 03 00 00            	mov	dword ptr [ebx + 0x3d8], eax
 1002d52: 5f                           	pop	edi
 1002d53: b0 01                        	mov	al, 0x1
 1002d55: 5b                           	pop	ebx
 1002d56: 8b e5                        	mov	esp, ebp
 1002d58: 5d                           	pop	ebp
 1002d59: c2 04 00                     	ret	0x4
 1002d5c: cc                           	int3
 1002d5d: cc                           	int3
 1002d5e: cc                           	int3
 1002d5f: cc                           	int3
 1002d60: 56                           	push	esi
 1002d61: 8b f1                        	mov	esi, ecx
 1002d63: 83 7e 30 08                  	cmp	dword ptr [esi + 0x30], 0x8
 1002d67: 72 0c                        	jb	0x1002d75 <.text+0x115>
 1002d69: 8b 46 1c                     	mov	eax, dword ptr [esi + 0x1c]
 1002d6c: 50                           	push	eax
 1002d6d: e8 b5 2d 3d 00               	call	0x13d5b27 <.text+0x3d2ec7>
 1002d72: 83 c4 04                     	add	esp, 0x4
 1002d75: 33 c9                        	xor	ecx, ecx
 1002d77: c7 46 30 07 00 00 00         	mov	dword ptr [esi + 0x30], 0x7
 1002d7e: c7 46 2c 00 00 00 00         	mov	dword ptr [esi + 0x2c], 0x0
 1002d85: 66 89 4e 1c                  	mov	word ptr [esi + 0x1c], cx
 1002d89: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 1002d8c: 52                           	push	edx
 1002d8d: e8 95 2d 3d 00               	call	0x13d5b27 <.text+0x3d2ec7>
 1002d92: 83 c4 04                     	add	esp, 0x4
 1002d95: c7 46 18 00 00 00 00         	mov	dword ptr [esi + 0x18], 0x0
 1002d9c: 5e                           	pop	esi
 1002d9d: c3                           	ret
 1002d9e: cc                           	int3
 1002d9f: cc                           	int3
