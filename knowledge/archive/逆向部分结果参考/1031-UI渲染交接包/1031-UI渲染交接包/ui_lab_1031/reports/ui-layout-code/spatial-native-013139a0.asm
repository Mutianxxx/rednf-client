
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
