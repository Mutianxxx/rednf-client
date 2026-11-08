
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b3690 <.text>:
 11b3690: 0f bf 41 28                  	movsx	eax, word ptr [ecx + 0x28]
 11b3694: a3 30 58 b5 01               	mov	dword ptr [0x1b55830], eax
 11b3699: 0f bf 51 2a                  	movsx	edx, word ptr [ecx + 0x2a]
 11b369d: 89 15 34 58 b5 01            	mov	dword ptr [0x1b55834], edx
 11b36a3: 0f bf 41 2c                  	movsx	eax, word ptr [ecx + 0x2c]
 11b36a7: a3 38 58 b5 01               	mov	dword ptr [0x1b55838], eax
 11b36ac: 0f bf 49 2e                  	movsx	ecx, word ptr [ecx + 0x2e]
 11b36b0: 89 0d 3c 58 b5 01            	mov	dword ptr [0x1b5583c], ecx
 11b36b6: b8 30 58 b5 01               	mov	eax, 0x1b55830
 11b36bb: c3                           	ret
 11b36bc: cc                           	int3
 11b36bd: cc                           	int3
 11b36be: cc                           	int3
 11b36bf: cc                           	int3
 11b36c0: 55                           	push	ebp
 11b36c1: 8b ec                        	mov	ebp, esp
 11b36c3: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11b36c6: 8b 4d 14                     	mov	ecx, dword ptr [ebp + 0x14]
 11b36c9: 8b 55 10                     	mov	edx, dword ptr [ebp + 0x10]
 11b36cc: 50                           	push	eax
 11b36cd: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11b36d0: 51                           	push	ecx
 11b36d1: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b36d4: 52                           	push	edx
 11b36d5: 50                           	push	eax
 11b36d6: 51                           	push	ecx
 11b36d7: e8 64 fe 03 00               	call	0x11f3540 <.text+0x3feb0>
 11b36dc: 8b c8                        	mov	ecx, eax
 11b36de: e8 dd f9 03 00               	call	0x11f30c0 <.text+0x3fa30>
 11b36e3: 5d                           	pop	ebp
 11b36e4: c2 14 00                     	ret	0x14
 11b36e7: cc                           	int3
 11b36e8: cc                           	int3
 11b36e9: cc                           	int3
 11b36ea: cc                           	int3
 11b36eb: cc                           	int3
 11b36ec: cc                           	int3
 11b36ed: cc                           	int3
 11b36ee: cc                           	int3
 11b36ef: cc                           	int3
 11b36f0: 55                           	push	ebp
 11b36f1: 8b ec                        	mov	ebp, esp
 11b36f3: 83 ec 18                     	sub	esp, 0x18
 11b36f6: 56                           	push	esi
 11b36f7: 8b f1                        	mov	esi, ecx
 11b36f9: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11b36fc: 85 c9                        	test	ecx, ecx
 11b36fe: 75 1c                        	jne	0x11b371c <.text+0x8c>
 11b3700: 8b 4d 14                     	mov	ecx, dword ptr [ebp + 0x14]
 11b3703: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11b3706: 8b 06                        	mov	eax, dword ptr [esi]
 11b3708: 51                           	push	ecx
 11b3709: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11b370c: 52                           	push	edx
 11b370d: 8b 50 20                     	mov	edx, dword ptr [eax + 0x20]
 11b3710: 51                           	push	ecx
 11b3711: 8b ce                        	mov	ecx, esi
 11b3713: ff d2                        	call	edx
 11b3715: 5e                           	pop	esi
 11b3716: 8b e5                        	mov	esp, ebp
 11b3718: 5d                           	pop	ebp
 11b3719: c2 10 00                     	ret	0x10
 11b371c: 89 4d fc                     	mov	dword ptr [ebp - 0x4], ecx
 11b371f: c7 45 f8 00 00 00 00         	mov	dword ptr [ebp - 0x8], 0x0
 11b3726: 85 c9                        	test	ecx, ecx
 11b3728: 0f 84 ef 00 00 00            	je	0x11b381d <.text+0x18d>
 11b372e: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11b3731: 53                           	push	ebx
 11b3732: 57                           	push	edi
 11b3733: 8b da                        	mov	ebx, edx
 11b3735: 8d 04 0a                     	lea	eax, [edx + ecx]
 11b3738: 2b d9                        	sub	ebx, ecx
 11b373a: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11b373d: 8b fa                        	mov	edi, edx
 11b373f: 2b f9                        	sub	edi, ecx
 11b3741: 89 4d 0c                     	mov	dword ptr [ebp + 0xc], ecx
 11b3744: 2b ca                        	sub	ecx, edx
 11b3746: 89 7d f4                     	mov	dword ptr [ebp - 0xc], edi
 11b3749: 8b 7d 14                     	mov	edi, dword ptr [ebp + 0x14]
 11b374c: 89 55 08                     	mov	dword ptr [ebp + 0x8], edx
 11b374f: 89                           	<unknown>
