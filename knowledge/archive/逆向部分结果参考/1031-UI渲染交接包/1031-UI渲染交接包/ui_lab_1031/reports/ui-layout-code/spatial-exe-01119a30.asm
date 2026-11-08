
<stdin>:	file format elf32-i386

Disassembly of section .text:

01119a30 <.text>:
 1119a30: 80 ff 8b                     	cmp	bh, -0x75
 1119a33: 0d 28 f7 a6 01               	or	eax, 0x1a6f728
 1119a38: 8b d8                        	mov	ebx, eax
 1119a3a: e8 81 ca 80 ff               	call	0x9264c0
 1119a3f: 3b c3                        	cmp	eax, ebx
 1119a41: 0f 94 c0                     	sete	al
 1119a44: 84 c0                        	test	al, al
 1119a46: 0f 85 bc 00 00 00            	jne	0x1119b08 <.text+0xd8>
 1119a4c: 8d 8e c4 01 00 00            	lea	ecx, [esi + 0x1c4]
 1119a52: 8d 55 08                     	lea	edx, [ebp + 0x8]
 1119a55: 52                           	push	edx
 1119a56: 8d 41 08                     	lea	eax, [ecx + 0x8]
 1119a59: 50                           	push	eax
 1119a5a: e8 81 73 08 00               	call	0x11a0de0 <.text+0x873b0>
 1119a5f: 83 7d 08 00                  	cmp	dword ptr [ebp + 0x8], 0x0
 1119a63: 75 3e                        	jne	0x1119aa3 <.text+0x73>
 1119a65: 83 be b0 03 00 00 00         	cmp	dword ptr [esi + 0x3b0], 0x0
 1119a6c: 74 35                        	je	0x1119aa3 <.text+0x73>
 1119a6e: 68 10 80 83 01               	push	0x1838010
 1119a73: e8 78 64 08 00               	call	0x119fef0 <.text+0x864c0>
 1119a78: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 1119a7e: 83 c4 04                     	add	esp, 0x4
 1119a81: 50                           	push	eax
 1119a82: e8 59 9f f4 ff               	call	0x10639e0
 1119a87: 8b c8                        	mov	ecx, eax
 1119a89: 85 c9                        	test	ecx, ecx
 1119a8b: 74 16                        	je	0x1119aa3 <.text+0x73>
 1119a8d: 83 be 6c 02 00 00 01         	cmp	dword ptr [esi + 0x26c], 0x1
 1119a94: 8b 11                        	mov	edx, dword ptr [ecx]
 1119a96: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 1119a99: 75 04                        	jne	0x1119a9f <.text+0x6f>
 1119a9b: 6a 01                        	push	0x1
 1119a9d: eb 02                        	jmp	0x1119aa1 <.text+0x71>
 1119a9f: 6a 00                        	push	0x0
 1119aa1: ff d0                        	call	eax
 1119aa3: 8b 86 6c 02 00 00            	mov	eax, dword ptr [esi + 0x26c]
 1119aa9: 83 e8 00                     	sub	eax, 0x0
 1119aac: 74 05                        	je	0x1119ab3 <.text+0x83>
 1119aae: 48                           	dec	eax
 1119aaf: 74 07                        	je	0x1119ab8 <.text+0x88>
 1119ab1: eb 55                        	jmp	0x1119b08 <.text+0xd8>
 1119ab3: 8b c7                        	mov	eax, edi
 1119ab5: 48                           	dec	eax
 1119ab6: 75 50                        	jne	0x1119b08 <.text+0xd8>
 1119ab8: 8b 86 04 01 00 00            	mov	eax, dword ptr [esi + 0x104]
 1119abe: 85 c0                        	test	eax, eax
 1119ac0: 75 06                        	jne	0x1119ac8 <.text+0x98>
 1119ac2: 8b 86 f4 00 00 00            	mov	eax, dword ptr [esi + 0xf4]
 1119ac8: 8b c8                        	mov	ecx, eax
 1119aca: e8 a1 75 42 ff               	call	0x541070
 1119acf: 85 c0                        	test	eax, eax
 1119ad1: 74 35                        	je	0x1119b08 <.text+0xd8>
 1119ad3: 8b 8e 04 01 00 00            	mov	ecx, dword ptr [esi + 0x104]
 1119ad9: 85 c9                        	test	ecx, ecx
 1119adb: 75 06                        	jne	0x1119ae3 <.text+0xb3>
 1119add: 8b 8e f4 00 00 00            	mov	ecx, dword ptr [esi + 0xf4]
 1119ae3: e8 88 75 42 ff               	call	0x541070
 1119ae8: 8b 96 04 01 00 00            	mov	edx, dword ptr [esi + 0x104]
 1119aee: 85 d2                        	test	edx, edx
 1119af0: 75 06                        	jne	0x1119af8 <.text+0xc8>
 1119af2: 8b 96 f4 00 00 00            	mov	edx, dword ptr [esi + 0xf4]
 1119af8: 8b 30                        	mov	esi, dword ptr [eax]
 1119afa: 6a 00                        	push	0x0
 1119afc: 6a 00                        	push	0x0
 1119afe: 6a 0d                        	push	0xd
 1119b00: 52                           	push	edx
 1119b01: 8b 56 04                     	mov	edx, dword ptr [esi + 0x4]
 1119b04: 8b c8                        	mov	ecx, eax
 1119b06: ff d2                        	call	edx
 1119b08: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 1119b0e: 6a 00                        	push	0x0
 1119b10: 6a ff                        	push	-0x1
 1119b12: 68 83 00 00 00               	push	0x83
 1119b17: e8 94 aa d5 ff               	call	0xe745b0
 1119b1c: 5f                           	pop	edi
 1119b1d: 5e                           	pop	esi
 1119b1e: 5b                           	pop	ebx
 1119b1f: 5d                           	pop	ebp
 1119b20: c2 04 00                     	ret	0x4
 1119b23: cc                           	int3
 1119b24: cc                           	int3
 1119b25: cc                           	int3
 1119b26: cc                           	int3
 1119b27: cc                           	int3
 1119b28: cc                           	int3
 1119b29: cc                           	int3
 1119b2a: cc                           	int3
 1119b2b: cc                           	int3
 1119b2c: cc                           	int3
 1119b2d: cc                           	int3
 1119b2e: cc                           	int3
 1119b2f: cc                           	int3
