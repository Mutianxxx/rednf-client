
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e7c30 <.text>:
  4e7c30: 55                           	push	ebp
  4e7c31: 8b ec                        	mov	ebp, esp
  4e7c33: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  4e7c36: 56                           	push	esi
  4e7c37: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
  4e7c3a: 50                           	push	eax
  4e7c3b: 56                           	push	esi
  4e7c3c: e8 af fd ff ff               	call	0x4e79f0
  4e7c41: 8b c6                        	mov	eax, esi
  4e7c43: 5e                           	pop	esi
  4e7c44: 5d                           	pop	ebp
  4e7c45: c2 08 00                     	ret	0x8
  4e7c48: cc                           	int3
  4e7c49: cc                           	int3
  4e7c4a: cc                           	int3
  4e7c4b: cc                           	int3
  4e7c4c: cc                           	int3
  4e7c4d: cc                           	int3
  4e7c4e: cc                           	int3
  4e7c4f: cc                           	int3
  4e7c50: 55                           	push	ebp
  4e7c51: 8b ec                        	mov	ebp, esp
  4e7c53: 6a ff                        	push	-0x1
  4e7c55: 68 58 32 41 01               	push	0x1413258
  4e7c5a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4e7c60: 50                           	push	eax
  4e7c61: 83 ec 3c                     	sub	esp, 0x3c
  4e7c64: 53                           	push	ebx
  4e7c65: 56                           	push	esi
  4e7c66: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4e7c6b: 33 c5                        	xor	eax, ebp
  4e7c6d: 50                           	push	eax
  4e7c6e: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4e7c71: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4e7c77: e8 94 e7 21 00               	call	0x706410 <.text+0x21e7e0>
  4e7c7c: 8b c8                        	mov	ecx, eax
  4e7c7e: e8 ed 47 27 00               	call	0x75c470 <.text+0x274840>
  4e7c83: 83 f8 01                     	cmp	eax, 0x1
  4e7c86: 0f 85 e1 01 00 00            	jne	0x4e7e6d <.text+0x23d>
  4e7c8c: 8d 45 e4                     	lea	eax, [ebp - 0x1c]
  4e7c8f: 50                           	push	eax
  4e7c90: b9 00 e1 d9 01               	mov	ecx, 0x1d9e100
  4e7c95: e8 b6 81 07 00               	call	0x55fe50 <.text+0x78220>
  4e7c9a: 33 db                        	xor	ebx, ebx
  4e7c9c: 8d 64 24 00                  	lea	esp, [esp]
  4e7ca0: 8d 4d cc                     	lea	ecx, [ebp - 0x34]
  4e7ca3: 51                           	push	ecx
  4e7ca4: b9 00 e1 d9 01               	mov	ecx, 0x1d9e100
  4e7ca9: e8 92 c6 2d 00               	call	0x7c4340 <.text+0x2dc710>
  4e7cae: 8b 75 e4                     	mov	esi, dword ptr [ebp - 0x1c]
  4e7cb1: 3b f3                        	cmp	esi, ebx
  4e7cb3: 0f 84 ed 00 00 00            	je	0x4e7da6 <.text+0x176>
  4e7cb9: 8b 16                        	mov	edx, dword ptr [esi]
  4e7cbb: 3b d3                        	cmp	edx, ebx
  4e7cbd: 0f 84                        	<unknown>
  4e7cbf: e3                           	<unknown>
