
<stdin>:	file format elf32-i386

Disassembly of section .text:

0100fef0 <.text>:
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
 100ff1d: e8 0e 40 1b 00               	call	0x11c3f30 <.text+0x1b4040>
 100ff22: 33 db                        	xor	ebx, ebx
 100ff24: c7 07 f4 b8 82 01            	mov	dword ptr [edi], 0x182b8f4
 100ff2a: 8d b7 c4 03 00 00            	lea	esi, [edi + 0x3c4]
 100ff30: 6a 08                        	push	0x8
 100ff32: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 100ff35: 89 1e                        	mov	dword ptr [esi], ebx
 100ff37: e8 de 6b 3c 00               	call	0x13d6b1a <.text+0x3c6c2a>
 100ff3c: 83 c4 04                     	add	esp, 0x4
 100ff3f: 3b c3                        	cmp	eax, ebx
 100ff41: 0f 84 a3 00 00 00            	je	0x100ffea <.text+0xfa>
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
 100ff6d: e8 a8 6b 3c 00               	call	0x13d6b1a <.text+0x3c6c2a>
 100ff72: 83 c4 04                     	add	esp, 0x4
 100ff75: 3b c3                        	cmp	eax, ebx
 100ff77: 74 4d                        	je	0x100ffc6 <.text+0xd6>
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
