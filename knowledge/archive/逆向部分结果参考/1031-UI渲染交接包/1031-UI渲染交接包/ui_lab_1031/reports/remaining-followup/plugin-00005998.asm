
<stdin>:	file format elf32-i386

Disassembly of section .text:

10005998 <.text>:
10005998: 6a 0c                        	push	0xc
1000599a: 68 e8 d1 01 10               	push	0x1001d1e8
1000599f: e8 7c 38 00 00               	call	0x10009220 <.text+0x3888>
100059a4: 8b f9                        	mov	edi, ecx
100059a6: 8b f2                        	mov	esi, edx
100059a8: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
100059ab: 33 c0                        	xor	eax, eax
100059ad: 40                           	inc	eax
100059ae: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
100059b1: 85 f6                        	test	esi, esi
100059b3: 75 0c                        	jne	0x100059c1 <.text+0x29>
100059b5: 39 15 38 65 02 10            	cmp	dword ptr [0x10026538], edx
100059bb: 0f 84 c5 00 00 00            	je	0x10005a86 <.text+0xee>
100059c1: 83 65 fc 00                  	and	dword ptr [ebp - 0x4], 0x0
100059c5: 3b f0                        	cmp	esi, eax
100059c7: 74 05                        	je	0x100059ce <.text+0x36>
100059c9: 83 fe 02                     	cmp	esi, 0x2
100059cc: 75 2e                        	jne	0x100059fc <.text+0x64>
100059ce: a1 c0 a1 01 10               	mov	eax, dword ptr [0x1001a1c0]
100059d3: 85 c0                        	test	eax, eax
100059d5: 74 08                        	je	0x100059df <.text+0x47>
100059d7: 57                           	push	edi
100059d8: 56                           	push	esi
100059d9: 53                           	push	ebx
100059da: ff d0                        	call	eax
100059dc: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
100059df: 83 7d e4 00                  	cmp	dword ptr [ebp - 0x1c], 0x0
100059e3: 0f 84 96 00 00 00            	je	0x10005a7f <.text+0xe7>
100059e9: 57                           	push	edi
100059ea: 56                           	push	esi
100059eb: 53                           	push	ebx
100059ec: e8 43 fe ff ff               	call	0x10005834
100059f1: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
100059f4: 85 c0                        	test	eax, eax
100059f6: 0f 84 83 00 00 00            	je	0x10005a7f <.text+0xe7>
100059fc: 57                           	push	edi
100059fd: 56                           	push	esi
100059fe: 53                           	push	ebx
100059ff: e8 2c f5 ff ff               	call	0x10004f30
10005a04: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
10005a07: 83 fe 01                     	cmp	esi, 0x1
10005a0a: 75 24                        	jne	0x10005a30 <.text+0x98>
10005a0c: 85 c0                        	test	eax, eax
10005a0e: 75 20                        	jne	0x10005a30 <.text+0x98>
10005a10: 57                           	push	edi
10005a11: 50                           	push	eax
10005a12: 53                           	push	ebx
10005a13: e8 18 f5 ff ff               	call	0x10004f30
10005a18: 57                           	push	edi
10005a19: 6a 00                        	push	0x0
10005a1b: 53                           	push	ebx
10005a1c: e8 13 fe ff ff               	call	0x10005834
10005a21: a1 c0 a1 01 10               	mov	eax, dword ptr [0x1001a1c0]
10005a26: 85 c0                        	test	eax, eax
10005a28: 74 06                        	je	0x10005a30 <.text+0x98>
10005a2a: 57                           	push	edi
10005a2b: 6a 00                        	push	0x0
10005a2d: 53                           	push	ebx
10005a2e: ff d0                        	call	eax
10005a30: 85 f6                        	test	esi, esi
10005a32: 74 05                        	je	0x10005a39 <.text+0xa1>
10005a34: 83 fe 03                     	cmp	esi, 0x3
10005a37: 75 26                        	jne	0x10005a5f <.text+0xc7>
10005a39: 57                           	push	edi
10005a3a: 56                           	push	esi
10005a3b: 53                           	push	ebx
10005a3c: e8 f3 fd ff ff               	call	0x10005834
10005a41: 85 c0                        	test	eax, eax
10005a43: 75 03                        	jne	0x10005a48 <.text+0xb0>
10005a45: 21 45 e4                     	and	dword ptr [ebp - 0x1c], eax
10005a48: 83 7d e4 00                  	cmp	dword ptr [ebp - 0x1c], 0x0
10005a4c: 74 11                        	je	0x10005a5f <.text+0xc7>
10005a4e: a1 c0 a1 01 10               	mov	eax, dword ptr [0x1001a1c0]
10005a53: 85 c0                        	test	eax, eax
10005a55: 74 08                        	je	0x10005a5f <.text+0xc7>
10005a57: 57                           	push	edi
10005a58: 56                           	push	esi
10005a59: 53                           	push	ebx
10005a5a: ff d0                        	call	eax
10005a5c: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
10005a5f: c7 45 fc fe ff ff ff         	mov	dword ptr [ebp - 0x4], 0xfffffffe
10005a66: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
10005a69: eb 1d                        	jmp	0x10005a88 <.text+0xf0>
10005a6b: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
10005a6e: 8b 08                        	mov	ecx, dword ptr [eax]
10005a70: 8b 09                        	mov	ecx, dword ptr [ecx]
10005a72: 50                           	push	eax
10005a73: 51                           	push	ecx
10005a74: e8 a0 46 00 00               	call	0x1000a119 <.text+0x4781>
10005a79: 59                           	pop	ecx
10005a7a: 59                           	pop	ecx
10005a7b: c3                           	ret
10005a7c: 8b 65 e8                     	mov	esp, dword ptr [ebp - 0x18]
10005a7f: c7 45 fc fe ff ff ff         	mov	dword ptr [ebp - 0x4], 0xfffffffe
10005a86: 33 c0                        	xor	eax, eax
10005a88: e8 d8 37 00 00               	call	0x10009265 <.text+0x38cd>
10005a8d: c3                           	ret
