
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
 1002edc: cc                           	int3
 1002edd: cc                           	int3
 1002ede: cc                           	int3
 1002edf: cc                           	int3
 1002ee0: 55                           	push	ebp
 1002ee1: 8b ec                        	mov	ebp, esp
 1002ee3: 56                           	push	esi
 1002ee4: 8b 75 0c                     	mov	esi, dword ptr [ebp + 0xc]
 1002ee7: 83 7e 30 08                  	cmp	dword ptr [esi + 0x30], 0x8
 1002eeb: 72 0c                        	jb	0x1002ef9 <.text+0x79>
 1002eed: 8b 46 1c                     	mov	eax, dword ptr [esi + 0x1c]
 1002ef0: 50                           	push	eax
 1002ef1: e8 31 2c 3d 00               	call	0x13d5b27 <.text+0x3d2ca7>
 1002ef6: 83 c4 04                     	add	esp, 0x4
 1002ef9: 33 c9                        	xor	ecx, ecx
 1002efb: c7 46 30 07 00 00 00         	mov	dword ptr [esi + 0x30], 0x7
 1002f02: c7 46 2c 00 00 00 00         	mov	dword ptr [esi + 0x2c], 0x0
 1002f09: 66 89 4e 1c                  	mov	word ptr [esi + 0x1c], cx
 1002f0d: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 1002f10: 52                           	push	edx
 1002f11: e8 11 2c 3d 00               	call	0x13d5b27 <.text+0x3d2ca7>
 1002f16: 83 c4 04                     	add	esp, 0x4
 1002f19: c7 46 18 00 00 00 00         	mov	dword ptr [esi + 0x18], 0x0
 1002f20: 5e                           	pop	esi
 1002f21: 5d                           	pop	ebp
 1002f22: c3                           	ret
 1002f23: cc                           	int3
 1002f24: cc                           	int3
 1002f25: cc                           	int3
 1002f26: cc                           	int3
 1002f27: cc                           	int3
 1002f28: cc                           	int3
 1002f29: cc                           	int3
 1002f2a: cc                           	int3
 1002f2b: cc                           	int3
 1002f2c: cc                           	int3
 1002f2d: cc                           	int3
 1002f2e: cc                           	int3
 1002f2f: cc                           	int3
 1002f30: 55                           	push	ebp
 1002f31: 8b ec                        	mov	ebp, esp
 1002f33: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 1002f36: 53                           	push	ebx
 1002f37: 8b 5d 0c                     	mov	ebx, dword ptr [ebp + 0xc]
 1002f3a: 3b c3                        	cmp	eax, ebx
 1002f3c: 74 42                        	je	0x1002f80 <.text+0x100>
 1002f3e: 56                           	push	esi
 1002f3f: 57                           	push	edi
 1002f40: 8d 70 30                     	lea	esi, [eax + 0x30]
 1002f43: 33 ff                        	xor	edi, edi
 1002f45: 83 3e 08                     	cmp	dword ptr [esi], 0x8
 1002f48: 72 0c                        	jb	0x1002f56 <.text+0xd6>
 1002f4a: 8b 46 ec                     	mov	eax, dword ptr [esi - 0x14]
 1002f4d: 50                           	push	eax
 1002f4e: e8 d4 2b 3d 00               	call	0x13d5b27 <.text+0x3d2ca7>
 1002f53: 83 c4 04                     	add	esp, 0x4
 1002f56: 33 c9                        	xor	ecx, ecx
 1002f58: c7 06 07 00 00 00            	mov	dword ptr [esi], 0x7
 1002f5e: 89 7e                        	<unknown>
