
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c49f0 <.text>:
 11c49f0: 55                           	push	ebp
 11c49f1: 8b ec                        	mov	ebp, esp
 11c49f3: 6a ff                        	push	-0x1
 11c49f5: 68 28 b9 40 01               	push	0x140b928
 11c49fa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c4a00: 50                           	push	eax
 11c4a01: 56                           	push	esi
 11c4a02: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c4a07: 33 c5                        	xor	eax, ebp
 11c4a09: 50                           	push	eax
 11c4a0a: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c4a0d: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c4a13: 8b f1                        	mov	esi, ecx
 11c4a15: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c4a1c: 8d 8e 14 03 00 00            	lea	ecx, [esi + 0x314]
 11c4a22: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11c4a29: c7 41 14 00 00 00 00         	mov	dword ptr [ecx + 0x14], 0x0
 11c4a30: 72 05                        	jb	0x11c4a37 <.text+0x47>
 11c4a32: 8b 41 04                     	mov	eax, dword ptr [ecx + 0x4]
 11c4a35: eb 03                        	jmp	0x11c4a3a <.text+0x4a>
 11c4a37: 8d 41 04                     	lea	eax, [ecx + 0x4]
 11c4a3a: 33 d2                        	xor	edx, edx
 11c4a3c: 6a ff                        	push	-0x1
 11c4a3e: 66 89 10                     	mov	word ptr [eax], dx
 11c4a41: 52                           	push	edx
 11c4a42: 8d 45 08                     	lea	eax, [ebp + 0x8]
 11c4a45: 50                           	push	eax
 11c4a46: e8 e5 08 24 ff               	call	0x405330
 11c4a4b: 83 7d 20 08                  	cmp	dword ptr [ebp + 0x20], 0x8
 11c4a4f: 8b 4d 28                     	mov	ecx, dword ptr [ebp + 0x28]
 11c4a52: 8b 55 2c                     	mov	edx, dword ptr [ebp + 0x2c]
 11c4a55: 8b 45 30                     	mov	eax, dword ptr [ebp + 0x30]
 11c4a58: 89 8e 34 03 00 00            	mov	dword ptr [esi + 0x334], ecx
 11c4a5e: 8b 4d 34                     	mov	ecx, dword ptr [ebp + 0x34]
 11c4a61: 89 96 38 03 00 00            	mov	dword ptr [esi + 0x338], edx
 11c4a67: 89 86 3c 03 00 00            	mov	dword ptr [esi + 0x33c], eax
 11c4a6d: 89 8e 40 03 00 00            	mov	dword ptr [esi + 0x340], ecx
 11c4a73: 72 0c                        	jb	0x11c4a81 <.text+0x91>
 11c4a75: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11c4a78: 52                           	push	edx
 11c4a79: e8 a9 10 21 00               	call	0x13d5b27 <.text+0x211137>
 11c4a7e: 83 c4 04                     	add	esp, 0x4
 11c4a81: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11c4a84: 33 c0                        	xor	eax, eax
 11c4a86: 51                           	push	ecx
 11c4a87: c7 45 20 07 00 00 00         	mov	dword ptr [ebp + 0x20], 0x7
 11c4a8e: c7 45 1c 00 00 00 00         	mov	dword ptr [ebp + 0x1c], 0x0
 11c4a95: 66 89 45 0c                  	mov	word ptr [ebp + 0xc], ax
 11c4a99: e8 89 10 21 00               	call	0x13d5b27 <.text+0x211137>
 11c4a9e: 83 c4                        	<unknown>
