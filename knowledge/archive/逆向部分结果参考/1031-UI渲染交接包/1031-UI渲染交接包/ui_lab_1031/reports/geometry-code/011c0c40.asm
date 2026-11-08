
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c0c40 <.text>:
 11c0c40: 83 ec 08                     	sub	esp, 0x8
 11c0c43: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c0c49: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c0c4e: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 11c0c51: db 45 08                     	fild	dword ptr [ebp + 0x8]
 11c0c54: 6a ff                        	push	-0x1
 11c0c56: 83 ec 08                     	sub	esp, 0x8
 11c0c59: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c0c5f: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11c0c67: d9 5d 08                     	fstp	dword ptr [ebp + 0x8]
 11c0c6a: 8b cf                        	mov	ecx, edi
 11c0c6c: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c0c71: e8 0a 31 ff ff               	call	0x11b3d80
 11c0c76: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
 11c0c79: db 45 f4                     	fild	dword ptr [ebp - 0xc]
 11c0c7c: 85 c0                        	test	eax, eax
 11c0c7e: 79 06                        	jns	0x11c0c86 <.text+0x46>
 11c0c80: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11c0c86: d8 7d 08                     	fdivr	dword ptr [ebp + 0x8]
 11c0c89: 8b 55 e4                     	mov	edx, dword ptr [ebp - 0x1c]
 11c0c8c: 51                           	push	ecx
 11c0c8d: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
 11c0c90: d9 1c 24                     	fstp	dword ptr [esp]
 11c0c93: 57                           	push	edi
 11c0c94: 51                           	push	ecx
 11c0c95: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11c0c9b: 52                           	push	edx
 11c0c9c: e8 3f 35 ff ff               	call	0x11b41e0
 11c0ca1: 0f 57 c0                     	xorps	xmm0, xmm0
 11c0ca4: 83 ec 08                     	sub	esp, 0x8
 11c0ca7: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c0cad: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c0cb2: 2b f3                        	sub	esi, ebx
 11c0cb4: 6a ff                        	push	-0x1
 11c0cb6: 89 75 08                     	mov	dword ptr [ebp + 0x8], esi
 11c0cb9: db 45 08                     	fild	dword ptr [ebp + 0x8]
 11c0cbc: 83 ec 08                     	sub	esp, 0x8
 11c0cbf: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c0cc5: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11c0ccd: 8b cf                        	mov	ecx, edi
 11c0ccf: d9 5d 08                     	fstp	dword ptr [ebp + 0x8]
 11c0cd2: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c0cd7: e8 a4 30 ff ff               	call	0x11b3d80
 11c0cdc: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
 11c0cdf: db 45 f4                     	fild	dword ptr [ebp - 0xc]
 11c0ce2: 85 c0                        	test	eax, eax
 11c0ce4: 79 06                        	jns	0x11c0cec <.text+0xac>
 11c0ce6: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11c0cec: d8 7d 08                     	fdivr	dword ptr [ebp + 0x8]
 11c0cef: 8b 45 d8                     	mov	eax, dword ptr [ebp - 0x28]
 11c0cf2: 51                           	push	ecx
 11c0cf3: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11c0cf9: d9 1c 24                     	fstp	dword ptr [esp]
 11c0cfc: 57                           	push	edi
 11c0cfd: 50                           	push	eax
 11c0cfe: 53                           	push	ebx
 11c0cff: e8 dc 34 ff ff               	call	0x11b41e0
 11c0d04: 5f                           	pop	edi
 11c0d05: 5e                           	pop	esi
 11c0d06: 5b                           	pop	ebx
 11c0d07: 8b e5                        	mov	esp, ebp
 11c0d09: 5d                           	pop	ebp
 11c0d0a: c3                           	ret
 11c0d0b: cc                           	int3
 11c0d0c: cc                           	int3
 11c0d0d: cc                           	int3
 11c0d0e: cc                           	int3
 11c0d0f: cc                           	int3
 11c0d10: 55                           	push	ebp
 11c0d11: 8b ec                        	mov	ebp, esp
 11c0d13: 83 ec 5c                     	sub	esp, 0x5c
 11c0d16: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c0d1b: 33 c5                        	xor	eax, ebp
 11c0d1d: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11c0d20: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11c0d23: 8b 91 bc 02 00 00            	mov	edx, dword ptr [ecx + 0x2bc]
 11c0d29: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c0d2c: 2b 42 20                     	sub	eax, dword ptr [edx + 0x20]
 11c0d2f: 53                           	push	ebx
 11c0d30: c1 f8 02                     	sar	eax, 0x2
 11c0d33: 56                           	push	esi
 11c0d34: 57                           	push	edi
 11c0d35: 89 4d d0                     	mov	dword ptr [ebp - 0x30], ecx
 11c0d38: 85 c0                        	test	eax, eax
 11c0d3a: 74 18                        	je	0x11c0d54 <.text+0x114>
 11c0d3c: 8b 42 20                     	mov	eax, dword ptr [edx + 0x20]
 11c0d3f: 8b 72 24                     	mov	esi, dword ptr [edx + 0x24]
 11c0d42: 2b f0                        	sub	esi, eax
 11c0d44: c1 fe 02                     	sar	esi, 0x2
 11c0d47: 85 f6                        	test	esi, esi
 11c0d49: 75 05                        	jne	0x11c0d50 <.text+0x110>
 11c0d4b: e8 57 60 21 00               	call	0x13d6da7 <.text+0x216167>
 11c0d50: 8b 38                        	mov	edi, dword ptr [eax]
 11c0d52: eb 02                        	jmp	0x11c0d56 <.text+0x116>
 11c0d54: 33 ff                        	xor	edi, edi
 11c0d56: 8b f2                        	mov	esi, edx
 11c0d58: 8b 46 24                     	mov	eax, dword ptr [esi + 0x24]
 11c0d5b: 2b 46 20                     	sub	eax, dword ptr [esi + 0x20]
 11c0d5e: 8b 5e 24                     	mov	ebx, dword ptr [esi + 0x24]
 11c0d61: 2b 5e 20                     	sub	ebx, dword ptr [esi + 0x20]
 11c0d64: c1 f8 02                     	sar	eax, 0x2
 11c0d67: 48                           	dec	eax
 11c0d68: c1 fb 02                     	sar	ebx, 0x2
 11c0d6b: 3b c3                        	cmp	eax, ebx
 11c0d6d: 73 19                        	jae	0x11c0d88 <.text+0x148>
 11c0d6f: 8b 72 20                     	mov	esi, dword ptr [edx + 0x20]
 11c0d72: 8b 52 24                     	mov	edx, dword ptr [edx + 0x24]
 11c0d75: 2b d6                        	sub	edx, esi
 11c0d77: c1 fa 02                     	sar	edx, 0x2
 11c0d7a: 3b c2                        	cmp	eax, edx
 11c0d7c: 72 05                        	jb	0x11c0d83 <.text+0x143>
 11c0d7e: e8                           	<unknown>
 11c0d7f: 24                           	<unknown>
