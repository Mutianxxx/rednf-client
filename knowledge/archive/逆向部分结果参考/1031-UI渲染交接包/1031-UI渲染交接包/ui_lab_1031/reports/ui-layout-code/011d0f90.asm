
<stdin>:	file format elf32-i386

Disassembly of section .text:

011d0f90 <.text>:
 11d0f90: 55                           	push	ebp
 11d0f91: 8b ec                        	mov	ebp, esp
 11d0f93: 51                           	push	ecx
 11d0f94: 53                           	push	ebx
 11d0f95: 56                           	push	esi
 11d0f96: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11d0f99: 8b d9                        	mov	ebx, ecx
 11d0f9b: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 11d0f9e: 85 f6                        	test	esi, esi
 11d0fa0: 75 0f                        	jne	0x11d0fb1 <.text+0x21>
 11d0fa2: 68 78 21 56 01               	push	0x1562178
 11d0fa7: e8 44 ef fc ff               	call	0x119fef0
 11d0fac: 83 c4 04                     	add	esp, 0x4
 11d0faf: 8b f0                        	mov	esi, eax
 11d0fb1: 8b c6                        	mov	eax, esi
 11d0fb3: 8d 50 02                     	lea	edx, [eax + 0x2]
 11d0fb6: 66 8b 08                     	mov	cx, word ptr [eax]
 11d0fb9: 83 c0 02                     	add	eax, 0x2
 11d0fbc: 66 85 c9                     	test	cx, cx
 11d0fbf: 75 f5                        	jne	0x11d0fb6 <.text+0x26>
 11d0fc1: 2b c2                        	sub	eax, edx
 11d0fc3: d1 f8                        	sar	eax
 11d0fc5: 50                           	push	eax
 11d0fc6: 56                           	push	esi
 11d0fc7: 8d 4b 20                     	lea	ecx, [ebx + 0x20]
 11d0fca: e8 61 f0 23 ff               	call	0x410030
 11d0fcf: 8b c6                        	mov	eax, esi
 11d0fd1: 8d 50 02                     	lea	edx, [eax + 0x2]
 11d0fd4: 66 8b 08                     	mov	cx, word ptr [eax]
 11d0fd7: 83 c0 02                     	add	eax, 0x2
 11d0fda: 66 85 c9                     	test	cx, cx
 11d0fdd: 75 f5                        	jne	0x11d0fd4 <.text+0x44>
 11d0fdf: 2b c2                        	sub	eax, edx
 11d0fe1: d1 f8                        	sar	eax
 11d0fe3: 50                           	push	eax
 11d0fe4: 8d 4b 40                     	lea	ecx, [ebx + 0x40]
 11d0fe7: 56                           	push	esi
 11d0fe8: e8 43 f0 23 ff               	call	0x410030
 11d0fed: 8b 0d 64 65 b5 01            	mov	ecx, dword ptr [0x1b56564]
 11d0ff3: 8b 01                        	mov	eax, dword ptr [ecx]
 11d0ff5: 8b 50 1c                     	mov	edx, dword ptr [eax + 0x1c]
 11d0ff8: ff d2                        	call	edx
 11d0ffa: 39 43 0c                     	cmp	dword ptr [ebx + 0xc], eax
 11d0ffd: 0f 8e b7 00 00 00            	jle	0x11d10ba <.text+0x12a>
 11d1003: 33 f6                        	xor	esi, esi
 11d1005: 39 73 54                     	cmp	dword ptr [ebx + 0x54], esi
 11d1008: 0f 86 ac 00 00 00            	jbe	0x11d10ba <.text+0x12a>
 11d100e: 57                           	push	edi
 11d100f: eb 03                        	jmp	0x11d1014 <.text+0x84>
 11d1011: 8b 5d fc                     	mov	ebx, dword ptr [ebp - 0x4]
 11d1014: 83 7b 58 08                  	cmp	dword ptr [ebx + 0x58], 0x8
 11d1018: 72 0b                        	jb	0x11d1025 <.text+0x95>
 11d101a: 8b 7b 44                     	mov	edi, dword ptr [ebx + 0x44]
 11d101d: 8d 43 44                     	lea	eax, [ebx + 0x44]
 11d1020: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 11d1023: eb 06                        	jmp	0x11d102b <.text+0x9b>
 11d1025: 8d 7b 44                     	lea	edi, [ebx + 0x44]
 11d1028: 89 7d 08                     	mov	dword ptr [ebp + 0x8], edi
 11d102b: 8b 0d 64 65 b5 01            	mov	ecx, dword ptr [0x1b56564]
 11d1031: 8b 01                        	mov	eax, dword ptr [ecx]
 11d1033: 8b 50 24                     	mov	edx, dword ptr [eax + 0x24]
 11d1036: 8b 5b 0c                     	mov	ebx, dword ptr [ebx + 0xc]
 11d1039: 6a ff                        	push	-0x1
 11d103b: 8d 3c 77                     	lea	edi, [edi + 2*esi]
 11d103e: 57                           	push	edi
 11d103f: ff d2                        	call	edx
 11d1041: 3b c3                        	cmp	eax, ebx
 11d1043: 7e 74                        	jle	0x11d10b9 <.text+0x129>
 11d1045: 8b 0d 64 65 b5 01            	mov	ecx, dword ptr [0x1b56564]
 11d104b: 8b 01                        	mov	eax, dword ptr [ecx]
 11d104d: 8b 50 2c                     	mov	edx, dword ptr [eax + 0x2c]
 11d1050: 53                           	push	ebx
 11d1051: 57                           	push	edi
 11d1052: ff d2                        	call	edx
 11d1054: 8b 7d fc                     	mov	edi, dword ptr [ebp - 0x4]
 11d1057: 85 c0                        	test	eax, eax
 11d1059: 7e 54                        	jle	0x11d10af <.text+0x11f>
 11d105b: 8b 4f 54                     	mov	ecx, dword ptr [edi + 0x54]
 11d105e: 8d 14 30                     	lea	edx, [eax + esi]
 11d1061: 3b d1                        	cmp	edx, ecx
 11d1063: 72 05                        	jb	0x11d106a <.text+0xda>
 11d1065: 2b ce                        	sub	ecx, esi
 11d1067: 8d 41 ff                     	lea	eax, [ecx - 0x1]
 11d106a: 03 f0                        	add	esi, eax
 11d106c: 3b 77 54                     	cmp	esi, dword ptr [edi + 0x54]
 11d106f: 73 51                        	jae	0x11d10c2 <.text+0x132>
 11d1071: 83 7f 58 08                  	cmp	dword ptr [edi + 0x58], 0x8
 11d1075: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11d1078: 72 02                        	jb	0x11d107c <.text+0xec>
 11d107a: 8b 00                        	mov	eax, dword ptr [eax]
 11d107c: 66 83 3c 70 0a               	cmp	word ptr [eax + 2*esi], 0xa
 11d1081: 74 2c                        	je	0x11d10af <.text+0x11f>
 11d1083: 68 e0 56 56 01               	push	0x15656e0
 11d1088: e8 63 ee fc ff               	call	0x119fef0
 11d108d: 8b c8                        	mov	ecx, eax
 11d108f: 83 c4 04                     	add	esp, 0x4
 11d1092: 8d 59 02                     	lea	ebx, [ecx + 0x2]
 11d1095: 66 8b 11                     	mov	dx, word ptr [ecx]
 11d1098: 83 c1 02                     	add	ecx, 0x2
 11d109b: 66 85 d2                     	test	dx, dx
 11d109e: 75 f5                        	jne	0x11d1095 <.text+0x105>
 11d10a0: 2b cb                        	sub	ecx, ebx
 11d10a2: d1 f9                        	sar	ecx
 11d10a4: 51                           	push	ecx
 11d10a5: 50                           	push	eax
 11d10a6: 56                           	push	esi
 11d10a7: 8d 4f 40                     	lea	ecx, [edi + 0x40]
 11d10aa: e8 31 53 5f ff               	call	0x7c63e0
 11d10af: 46                           	inc	esi
 11d10b0: 3b 77 54                     	cmp	esi, dword ptr [edi + 0x54]
 11d10b3: 0f 82 58 ff ff ff            	jb	0x11d1011 <.text+0x81>
 11d10b9: 5f                           	pop	edi
 11d10ba: 5e                           	pop	esi
 11d10bb: 5b                           	pop	ebx
 11d10bc: 8b e5                        	mov	esp, ebp
 11d10be: 5d                           	pop	ebp
 11d10bf: c2 04 00                     	ret	0x4
 11d10c2: e8 e0 5c 20 00               	call	0x13d6da7 <.text+0x205e17>
 11d10c7: cc                           	int3
 11d10c8: cc                           	int3
 11d10c9: cc                           	int3
 11d10ca: cc                           	int3
 11d10cb: cc                           	int3
 11d10cc: cc                           	int3
 11d10cd: cc                           	int3
 11d10ce: cc                           	int3
 11d10cf: cc                           	int3
