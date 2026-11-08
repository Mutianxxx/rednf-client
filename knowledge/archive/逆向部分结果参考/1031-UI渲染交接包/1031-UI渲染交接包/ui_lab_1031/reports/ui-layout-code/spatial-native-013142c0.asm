
<stdin>:	file format elf32-i386

Disassembly of section .text:

013142c0 <.text>:
 13142c0: 56                           	push	esi
 13142c1: 8b f1                        	mov	esi, ecx
 13142c3: 57                           	push	edi
 13142c4: 8d 4e 24                     	lea	ecx, [esi + 0x24]
 13142c7: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 13142cd: e8 2e 11 00 00               	call	0x1315400 <.text+0x1140>
 13142d2: 8d 4e 38                     	lea	ecx, [esi + 0x38]
 13142d5: e8 16 a9 e2 ff               	call	0x113ebf0
 13142da: 68 78 21 56 01               	push	0x1562178
 13142df: e8 0c bc e8 ff               	call	0x119fef0
 13142e4: 8b c8                        	mov	ecx, eax
 13142e6: 83 c4 04                     	add	esp, 0x4
 13142e9: 8d 79 02                     	lea	edi, [ecx + 0x2]
 13142ec: 8d 64 24 00                  	lea	esp, [esp]
 13142f0: 66 8b 11                     	mov	dx, word ptr [ecx]
 13142f3: 83 c1 02                     	add	ecx, 0x2
 13142f6: 66 85 d2                     	test	dx, dx
 13142f9: 75 f5                        	jne	0x13142f0 <.text+0x30>
 13142fb: 2b cf                        	sub	ecx, edi
 13142fd: d1 f9                        	sar	ecx
 13142ff: 51                           	push	ecx
 1314300: 50                           	push	eax
 1314301: 8d 4e 04                     	lea	ecx, [esi + 0x4]
 1314304: e8 27 bd 0f ff               	call	0x410030
 1314309: 5f                           	pop	edi
 131430a: c7 46 4c 00 00 00 00         	mov	dword ptr [esi + 0x4c], 0x0
 1314311: 5e                           	pop	esi
 1314312: c3                           	ret
 1314313: cc                           	int3
 1314314: cc                           	int3
 1314315: cc                           	int3
 1314316: cc                           	int3
 1314317: cc                           	int3
 1314318: cc                           	int3
 1314319: cc                           	int3
 131431a: cc                           	int3
 131431b: cc                           	int3
 131431c: cc                           	int3
 131431d: cc                           	int3
 131431e: cc                           	int3
 131431f: cc                           	int3
