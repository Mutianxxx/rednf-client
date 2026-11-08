
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
