
<stdin>:	file format elf32-i386

Disassembly of section .text:

01002e80 <.text>:
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
 1002ead: e8 3e d0 19 00               	call	0x119fef0 <.text+0x19d070>
 1002eb2: 8b c8                        	mov	ecx, eax
 1002eb4: 83 c4 04                     	add	esp, 0x4
 1002eb7: 8d 59 02                     	lea	ebx, [ecx + 0x2]
 1002eba: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 1002ec0: 66 8b 11                     	mov	dx, word ptr [ecx]
 1002ec3: 83 c1 02                     	add	ecx, 0x2
 1002ec6: 66 85 d2                     	test	dx, dx
 1002ec9: 75 f5                        	jne	0x1002ec0 <.text+0x40>
 1002ecb: 2b cb                        	sub	ecx, ebx
 1002ecd: d1 f9                        	sar	ecx
 1002ecf: 51                           	push	ecx
 1002ed0: 50                           	push	eax
 1002ed1: 8d 4e 18                     	lea	ecx, [esi + 0x18]
 1002ed4: e8 57 d1 40 ff               	call	0x410030
 1002ed9: 5e                           	pop	esi
 1002eda: 5b                           	pop	ebx
 1002edb: c3                           	ret
