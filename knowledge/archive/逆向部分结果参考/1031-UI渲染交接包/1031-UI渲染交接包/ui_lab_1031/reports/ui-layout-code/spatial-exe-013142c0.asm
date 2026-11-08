
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
 1314320: 55                           	push	ebp
 1314321: 8b ec                        	mov	ebp, esp
 1314323: 6a ff                        	push	-0x1
 1314325: 68 b6 a7 4d 01               	push	0x14da7b6
 131432a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1314330: 50                           	push	eax
 1314331: 83 ec 24                     	sub	esp, 0x24
 1314334: 53                           	push	ebx
 1314335: 56                           	push	esi
 1314336: 57                           	push	edi
 1314337: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 131433c: 33 c5                        	xor	eax, ebp
 131433e: 50                           	push	eax
 131433f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1314342: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1314348: 8b f9                        	mov	edi, ecx
 131434a: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 131434d: 8d 77 04                     	lea	esi, [edi + 0x4]
 1314350: 33 db                        	xor	ebx, ebx
 1314352: 6a 08                        	push	0x8
 1314354: 89 1e                        	mov	dword ptr [esi], ebx
 1314356: e8 bf 27 0c 00               	call	0x13d6b1a <.text+0xc285a>
 131435b: 83 c4 04                     	add	esp, 0x4
 131435e: 3b c3                        	cmp	eax, ebx
