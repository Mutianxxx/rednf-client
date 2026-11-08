
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c2d00 <.text>:
 11c2d00: 56                           	push	esi
 11c2d01: 8b f1                        	mov	esi, ecx
 11c2d03: e8 48 b5 ff ff               	call	0x11be250
 11c2d08: 84 c0                        	test	al, al
 11c2d0a: 0f 84 95 00 00 00            	je	0x11c2da5 <.text+0xa5>
 11c2d10: 83 be c8 02 00 00 00         	cmp	dword ptr [esi + 0x2c8], 0x0
 11c2d17: 0f 84 88 00 00 00            	je	0x11c2da5 <.text+0xa5>
 11c2d1d: 6a 00                        	push	0x0
 11c2d1f: 6a 02                        	push	0x2
 11c2d21: e8 3a 07 ff ff               	call	0x11b3460
 11c2d26: f3 0f 10 05 50 22 56 01      	movss	xmm0, dword ptr [0x1562250]
 11c2d2e: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2d34: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2d39: 68 90 01 00 00               	push	0x190
 11c2d3e: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11c2d44: 50                           	push	eax
 11c2d45: 68 82 00 00 00               	push	0x82
 11c2d4a: 68 ff 00 00 00               	push	0xff
 11c2d4f: e8 0c 6c ff ff               	call	0x11b9960
 11c2d54: 0f 57 c0                     	xorps	xmm0, xmm0
 11c2d57: 8b 8e c8 02 00 00            	mov	ecx, dword ptr [esi + 0x2c8]
 11c2d5d: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c2d60: 0f b6 c0                     	movzx	eax, al
 11c2d63: 83 c4 10                     	add	esp, 0x10
 11c2d66: c1 e0 18                     	shl	eax, 0x18
 11c2d69: 0d ff ff ff 00               	or	eax, 0xffffff
 11c2d6e: 50                           	push	eax
 11c2d6f: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 11c2d72: 83 ec 0c                     	sub	esp, 0xc
 11c2d75: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c2d7b: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11c2d83: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c2d89: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c2d8e: 51                           	push	ecx
 11c2d8f: 52                           	push	edx
 11c2d90: 50                           	push	eax
 11c2d91: 8b ce                        	mov	ecx, esi
 11c2d93: e8 78 b6 ff ff               	call	0x11be410
 11c2d98: 8b c8                        	mov	ecx, eax
 11c2d9a: e8 41 14 ff ff               	call	0x11b41e0
 11c2d9f: 5e                           	pop	esi
 11c2da0: e9 cb 07 ff ff               	jmp	0x11b3570
 11c2da5: 5e                           	pop	esi
 11c2da6: c3                           	ret
