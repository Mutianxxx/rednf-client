
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e9a80 <.text>:
  4e9a80: 55                           	push	ebp
  4e9a81: 8b ec                        	mov	ebp, esp
  4e9a83: 6a ff                        	push	-0x1
  4e9a85: 68 5b 34 41 01               	push	0x141345b
  4e9a8a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4e9a90: 50                           	push	eax
  4e9a91: 83 ec 0c                     	sub	esp, 0xc
  4e9a94: 53                           	push	ebx
  4e9a95: 56                           	push	esi
  4e9a96: 57                           	push	edi
  4e9a97: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4e9a9c: 33 c5                        	xor	eax, ebp
  4e9a9e: 50                           	push	eax
  4e9a9f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4e9aa2: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4e9aa8: 8b f1                        	mov	esi, ecx
  4e9aaa: e8 b1 be 46 00               	call	0x955960 <.text+0x46bee0>
  4e9aaf: 8b c8                        	mov	ecx, eax
  4e9ab1: e8 4a b9 46 00               	call	0x955400 <.text+0x46b980>
  4e9ab6: 8b d8                        	mov	ebx, eax
  4e9ab8: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
  4e9abb: e8 a0 be 46 00               	call	0x955960 <.text+0x46bee0>
  4e9ac0: 8b c8                        	mov	ecx, eax
  4e9ac2: e8 39 b8 46 00               	call	0x955300 <.text+0x46b880>
  4e9ac7: 6a 68                        	push	0x68
  4e9ac9: 8b ce                        	mov	ecx, esi
  4e9acb: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  4e9ace: e8 4d e4 ff ff               	call	0x4e7f20
  4e9ad3: 85 c0                        	test	eax, eax
  4e9ad5: 74 06                        	je	0x4e9add <.text+0x5d>
  4e9ad7: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9adb: 75 57                        	jne	0x4e9b34 <.text+0xb4>
  4e9add: 6a 68                        	push	0x68
  4e9adf: 8b ce                        	mov	ecx, esi
  4e9ae1: e8 3a e4 ff ff               	call	0x4e7f20
  4e9ae6: 85 c0                        	test	eax, eax
  4e9ae8: 74 06                        	je	0x4e9af0 <.text+0x70>
  4e9aea: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9aee: 75 44                        	jne	0x4e9b34 <.text+0xb4>
  4e9af0: 6a 68                        	push	0x68
  4e9af2: 8b ce                        	mov	ecx, esi
  4e9af4: e8 27 fa ff ff               	call	0x4e9520
  4e9af9: 8b f8                        	mov	edi, eax
  4e9afb: 85 ff                        	test	edi, edi
  4e9afd: 74 35                        	je	0x4e9b34 <.text+0xb4>
  4e9aff: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e9b05: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e9b0b: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e9b0f: 85 c9                        	test	ecx, ecx
  4e9b11: 74 08                        	je	0x4e9b1b <.text+0x9b>
  4e9b13: 8b 07                        	mov	eax, dword ptr [edi]
  4e9b15: 50                           	push	eax
  4e9b16: e8 15 58 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9b1b: 85 db                        	test	ebx, ebx
  4e9b1d: 74 0b                        	je	0x4e9b2a <.text+0xaa>
  4e9b1f: 8b 4f 04                     	mov	ecx, dword ptr [edi + 0x4]
  4e9b22: 51                           	push	ecx
  4e9b23: 8b cb                        	mov	ecx, ebx
  4e9b25: e8 06 58 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9b2a: 8b ce                        	mov	ecx, esi
  4e9b2c: e8 5f dc ff ff               	call	0x4e7790
  4e9b31: 8b 5d ec                     	mov	ebx, dword ptr [ebp - 0x14]
  4e9b34: 6a 0b                        	push	0xb
  4e9b36: 8b ce                        	mov	ecx, esi
  4e9b38: e8 e3 e3 ff ff               	call	0x4e7f20
  4e9b3d: 85 c0                        	test	eax, eax
  4e9b3f: 74 06                        	je	0x4e9b47 <.text+0xc7>
  4e9b41: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9b45: 75 40                        	jne	0x4e9b87 <.text+0x107>
  4e9b47: 8b 0d 18 f7 a6 01            	mov	ecx, dword ptr [0x1a6f718]
  4e9b4d: 85 c9                        	test	ecx, ecx
  4e9b4f: 74 36                        	je	0x4e9b87 <.text+0x107>
  4e9b51: e8 aa b4 43 00               	call	0x925000 <.text+0x43b580>
  4e9b56: 85 c0                        	test	eax, eax
  4e9b58: 74 2d                        	je	0x4e9b87 <.text+0x107>
  4e9b5a: 8b 0d 18 f7 a6 01            	mov	ecx, dword ptr [0x1a6f718]
  4e9b60: e8 9b b4 43 00               	call	0x925000 <.text+0x43b580>
  4e9b65: 8d 88 84 02 00 00            	lea	ecx, [eax + 0x284]
  4e9b6b: 8d 55 e8                     	lea	edx, [ebp - 0x18]
  4e9b6e: 52                           	push	edx
  4e9b6f: 8d 41 08                     	lea	eax, [ecx + 0x8]
  4e9b72: 50                           	push	eax
  4e9b73: e8 68 72 cb 00               	call	0x11a0de0 <.text+0xcb7360>
  4e9b78: 83 7d e8 00                  	cmp	dword ptr [ebp - 0x18], 0x0
  4e9b7c: 74 09                        	je	0x4e9b87 <.text+0x107>
  4e9b7e: 6a 2a                        	push	0x2a
  4e9b80: 8b ce                        	mov	ecx, esi
  4e9b82: e8 e9 fb ff ff               	call	0x4e9770
  4e9b87: 85 db                        	test	ebx, ebx
  4e9b89: 75 09                        	jne	0x4e9b94 <.text+0x114>
  4e9b8b: 39 5d f0                     	cmp	dword ptr [ebp - 0x10], ebx
  4e9b8e: 0f 84 81 00 00 00            	je	0x4e9c15 <.text+0x195>
  4e9b94: e8 77 c8 21 00               	call	0x706410 <.text+0x21c990>
  4e9b99: 8b c8                        	mov	ecx, eax
  4e9b9b: e8 d0 28 27 00               	call	0x75c470 <.text+0x2729f0>
  4e9ba0: 83 f8 01                     	cmp	eax, 0x1
  4e9ba3: 75 56                        	jne	0x4e9bfb <.text+0x17b>
  4e9ba5: 6a 07                        	push	0x7
  4e9ba7: 8b ce                        	mov	ecx, esi
  4e9ba9: e8 72 e3 ff ff               	call	0x4e7f20
  4e9bae: 85 c0                        	test	eax, eax
  4e9bb0: 74 06                        	je	0x4e9bb8 <.text+0x138>
  4e9bb2: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9bb6: 75 66                        	jne	0x4e9c1e <.text+0x19e>
  4e9bb8: 6a 07                        	push	0x7
  4e9bba: 8b ce                        	mov	ecx, esi
  4e9bbc: e8 5f f9 ff ff               	call	0x4e9520
  4e9bc1: 8b f8                        	mov	edi, eax
  4e9bc3: 85 ff                        	test	edi, edi
  4e9bc5: 74 57                        	je	0x4e9c1e <.text+0x19e>
  4e9bc7: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e9bcd: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e9bd3: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e9bd7: 85 c9                        	test	ecx, ecx
  4e9bd9: 74 08                        	je	0x4e9be3 <.text+0x163>
  4e9bdb: 8b 17                        	mov	edx, dword ptr [edi]
  4e9bdd: 52                           	push	edx
  4e9bde: e8 4d 57 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9be3: 85 db                        	test	ebx, ebx
  4e9be5: 74 0b                        	je	0x4e9bf2 <.text+0x172>
  4e9be7: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e9bea: 50                           	push	eax
  4e9beb: 8b cb                        	mov	ecx, ebx
  4e9bed: e8 3e 57 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9bf2: 8b ce                        	mov	ecx, esi
  4e9bf4: e8 97 db ff ff               	call	0x4e7790
  4e9bf9: eb 23                        	jmp	0x4e9c1e <.text+0x19e>
  4e9bfb: 85 db                        	test	ebx, ebx
  4e9bfd: 75 05                        	jne	0x4e9c04 <.text+0x184>
  4e9bff: 39 5d f0                     	cmp	dword ptr [ebp - 0x10], ebx
  4e9c02: 74 11                        	je	0x4e9c15 <.text+0x195>
  4e9c04: e8 07 c8 21 00               	call	0x706410 <.text+0x21c990>
  4e9c09: 8b c8                        	mov	ecx, eax
  4e9c0b: e8 60 28 27 00               	call	0x75c470 <.text+0x2729f0>
  4e9c10: 83 f8 01                     	cmp	eax, 0x1
  4e9c13: 74 09                        	je	0x4e9c1e <.text+0x19e>
  4e9c15: 6a 07                        	push	0x7
  4e9c17: 8b ce                        	mov	ecx, esi
  4e9c19: e8 62 e7 ff ff               	call	0x4e8380
  4e9c1e: 8b 0d 0c 79 ac 01            	mov	ecx, dword ptr [0x1ac790c]
  4e9c24: 85 c9                        	test	ecx, ecx
  4e9c26: 74 38                        	je	0x4e9c60 <.text+0x1e0>
  4e9c28: 8b 11                        	mov	edx, dword ptr [ecx]
  4e9c2a: 8b 82 5c 07 00 00            	mov	eax, dword ptr [edx + 0x75c]
  4e9c30: ff d0                        	call	eax
  4e9c32: 83 f8 64                     	cmp	eax, 0x64
  4e9c35: 75 0b                        	jne	0x4e9c42 <.text+0x1c2>
  4e9c37: 6a 06                        	push	0x6
  4e9c39: 8b ce                        	mov	ecx, esi
  4e9c3b: e8 40 e7 ff ff               	call	0x4e8380
  4e9c40: eb 1e                        	jmp	0x4e9c60 <.text+0x1e0>
  4e9c42: 8b 0d 0c 79 ac 01            	mov	ecx, dword ptr [0x1ac790c]
  4e9c48: 8b 11                        	mov	edx, dword ptr [ecx]
  4e9c4a: 8b 82 5c 07 00 00            	mov	eax, dword ptr [edx + 0x75c]
  4e9c50: ff d0                        	call	eax
  4e9c52: 83 f8 64                     	cmp	eax, 0x64
  4e9c55: 7d 09                        	jge	0x4e9c60 <.text+0x1e0>
  4e9c57: 6a 06                        	push	0x6
  4e9c59: 8b ce                        	mov	ecx, esi
  4e9c5b: e8 10 fb ff ff               	call	0x4e9770
  4e9c60: a1 74 f7 a6 01               	mov	eax, dword ptr [0x1a6f774]
  4e9c65: 8b 88 78 01 00 00            	mov	ecx, dword ptr [eax + 0x178]
  4e9c6b: 3b 88 7c 01 00 00            	cmp	ecx, dword ptr [eax + 0x17c]
  4e9c71: 74 32                        	je	0x4e9ca5 <.text+0x225>
  4e9c73: e8 98 c7 21 00               	call	0x706410 <.text+0x21c990>
  4e9c78: 8b c8                        	mov	ecx, eax
  4e9c7a: e8 f1 27 27 00               	call	0x75c470 <.text+0x2729f0>
  4e9c7f: 83 f8 01                     	cmp	eax, 0x1
  4e9c82: 75 1c                        	jne	0x4e9ca0 <.text+0x220>
  4e9c84: 8b 0d 74 f7 a6 01            	mov	ecx, dword ptr [0x1a6f774]
  4e9c8a: 6a 05                        	push	0x5
  4e9c8c: e8 6f 0d 41 00               	call	0x8faa00 <.text+0x410f80>
  4e9c91: 84 c0                        	test	al, al
  4e9c93: 74 38                        	je	0x4e9ccd <.text+0x24d>
  4e9c95: 6a 01                        	push	0x1
  4e9c97: 8b ce                        	mov	ecx, esi
  4e9c99: e8 d2 fa ff ff               	call	0x4e9770
  4e9c9e: eb 2d                        	jmp	0x4e9ccd <.text+0x24d>
  4e9ca0: a1 74 f7 a6 01               	mov	eax, dword ptr [0x1a6f774]
  4e9ca5: 8b 90 78 01 00 00            	mov	edx, dword ptr [eax + 0x178]
  4e9cab: 3b 90 7c 01 00 00            	cmp	edx, dword ptr [eax + 0x17c]
  4e9cb1: 74 11                        	je	0x4e9cc4 <.text+0x244>
  4e9cb3: e8 58 c7 21 00               	call	0x706410 <.text+0x21c990>
  4e9cb8: 8b c8                        	mov	ecx, eax
  4e9cba: e8 b1 27 27 00               	call	0x75c470 <.text+0x2729f0>
  4e9cbf: 83 f8 01                     	cmp	eax, 0x1
  4e9cc2: 74 09                        	je	0x4e9ccd <.text+0x24d>
  4e9cc4: 6a 01                        	push	0x1
  4e9cc6: 8b ce                        	mov	ecx, esi
  4e9cc8: e8 b3 e6 ff ff               	call	0x4e8380
  4e9ccd: a1 74 f7 a6 01               	mov	eax, dword ptr [0x1a6f774]
  4e9cd2: 83 b8 00 01 00 00 00         	cmp	dword ptr [eax + 0x100], 0x0
  4e9cd9: 6a 02                        	push	0x2
  4e9cdb: 8b ce                        	mov	ecx, esi
  4e9cdd: 74 52                        	je	0x4e9d31 <.text+0x2b1>
  4e9cdf: e8 3c e2 ff ff               	call	0x4e7f20
  4e9ce4: 85 c0                        	test	eax, eax
  4e9ce6: 74 06                        	je	0x4e9cee <.text+0x26e>
  4e9ce8: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9cec: 75 48                        	jne	0x4e9d36 <.text+0x2b6>
  4e9cee: 6a 02                        	push	0x2
  4e9cf0: 8b ce                        	mov	ecx, esi
  4e9cf2: e8 29 f8 ff ff               	call	0x4e9520
  4e9cf7: 8b f8                        	mov	edi, eax
  4e9cf9: 85 ff                        	test	edi, edi
  4e9cfb: 74 39                        	je	0x4e9d36 <.text+0x2b6>
  4e9cfd: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e9d03: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e9d09: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e9d0d: 85 c9                        	test	ecx, ecx
  4e9d0f: 74 08                        	je	0x4e9d19 <.text+0x299>
  4e9d11: 8b 17                        	mov	edx, dword ptr [edi]
  4e9d13: 52                           	push	edx
  4e9d14: e8 17 56 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9d19: 85 db                        	test	ebx, ebx
  4e9d1b: 74 0b                        	je	0x4e9d28 <.text+0x2a8>
  4e9d1d: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e9d20: 50                           	push	eax
  4e9d21: 8b cb                        	mov	ecx, ebx
  4e9d23: e8 08 56 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9d28: 8b ce                        	mov	ecx, esi
  4e9d2a: e8 61 da ff ff               	call	0x4e7790
  4e9d2f: eb 05                        	jmp	0x4e9d36 <.text+0x2b6>
  4e9d31: e8 4a e6 ff ff               	call	0x4e8380
  4e9d36: 8b 0d 74 f7 a6 01            	mov	ecx, dword ptr [0x1a6f774]
  4e9d3c: 6a 00                        	push	0x0
  4e9d3e: e8 9d e7 40 00               	call	0x8f84e0 <.text+0x40ea60>
  4e9d43: 6a 00                        	push	0x0
  4e9d45: 84 c0                        	test	al, al
  4e9d47: 74 54                        	je	0x4e9d9d <.text+0x31d>
  4e9d49: 8b ce                        	mov	ecx, esi
  4e9d4b: e8 d0 e1 ff ff               	call	0x4e7f20
  4e9d50: 85 c0                        	test	eax, eax
  4e9d52: 74 06                        	je	0x4e9d5a <.text+0x2da>
  4e9d54: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9d58: 75 5b                        	jne	0x4e9db5 <.text+0x335>
  4e9d5a: 6a 00                        	push	0x0
  4e9d5c: 8b ce                        	mov	ecx, esi
  4e9d5e: e8 bd f7 ff ff               	call	0x4e9520
  4e9d63: 8b f8                        	mov	edi, eax
  4e9d65: 85 ff                        	test	edi, edi
  4e9d67: 74 4c                        	je	0x4e9db5 <.text+0x335>
  4e9d69: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e9d6f: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e9d75: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e9d79: 85 c9                        	test	ecx, ecx
  4e9d7b: 74 08                        	je	0x4e9d85 <.text+0x305>
  4e9d7d: 8b 17                        	mov	edx, dword ptr [edi]
  4e9d7f: 52                           	push	edx
  4e9d80: e8 ab 55 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9d85: 85 db                        	test	ebx, ebx
  4e9d87: 74 0b                        	je	0x4e9d94 <.text+0x314>
  4e9d89: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e9d8c: 50                           	push	eax
  4e9d8d: 8b cb                        	mov	ecx, ebx
  4e9d8f: e8 9c 55 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9d94: 8b ce                        	mov	ecx, esi
  4e9d96: e8 f5 d9 ff ff               	call	0x4e7790
  4e9d9b: eb 18                        	jmp	0x4e9db5 <.text+0x335>
  4e9d9d: 8b 0d 74 f7 a6 01            	mov	ecx, dword ptr [0x1a6f774]
  4e9da3: e8 38 e7 40 00               	call	0x8f84e0 <.text+0x40ea60>
  4e9da8: 84 c0                        	test	al, al
  4e9daa: 75 09                        	jne	0x4e9db5 <.text+0x335>
  4e9dac: 6a 00                        	push	0x0
  4e9dae: 8b ce                        	mov	ecx, esi
  4e9db0: e8 cb e5 ff ff               	call	0x4e8380
  4e9db5: e8 56 c6 21 00               	call	0x706410 <.text+0x21c990>
  4e9dba: 6a 21                        	push	0x21
  4e9dbc: 8b c8                        	mov	ecx, eax
  4e9dbe: e8 dd 17 27 00               	call	0x75b5a0 <.text+0x271b20>
  4e9dc3: 6a 08                        	push	0x8
  4e9dc5: 8b ce                        	mov	ecx, esi
  4e9dc7: 84 c0                        	test	al, al
  4e9dc9: 74 52                        	je	0x4e9e1d <.text+0x39d>
  4e9dcb: e8 50 e1 ff ff               	call	0x4e7f20
  4e9dd0: 85 c0                        	test	eax, eax
  4e9dd2: 74 06                        	je	0x4e9dda <.text+0x35a>
  4e9dd4: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9dd8: 75 48                        	jne	0x4e9e22 <.text+0x3a2>
  4e9dda: 6a 08                        	push	0x8
  4e9ddc: 8b ce                        	mov	ecx, esi
  4e9dde: e8 3d f7 ff ff               	call	0x4e9520
  4e9de3: 8b f8                        	mov	edi, eax
  4e9de5: 85 ff                        	test	edi, edi
  4e9de7: 74 39                        	je	0x4e9e22 <.text+0x3a2>
  4e9de9: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e9def: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e9df5: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e9df9: 85 c9                        	test	ecx, ecx
  4e9dfb: 74 08                        	je	0x4e9e05 <.text+0x385>
  4e9dfd: 8b 17                        	mov	edx, dword ptr [edi]
  4e9dff: 52                           	push	edx
  4e9e00: e8 2b 55 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9e05: 85 db                        	test	ebx, ebx
  4e9e07: 74 0b                        	je	0x4e9e14 <.text+0x394>
  4e9e09: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e9e0c: 50                           	push	eax
  4e9e0d: 8b cb                        	mov	ecx, ebx
  4e9e0f: e8 1c 55 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9e14: 8b ce                        	mov	ecx, esi
  4e9e16: e8 75 d9 ff ff               	call	0x4e7790
  4e9e1b: eb 05                        	jmp	0x4e9e22 <.text+0x3a2>
  4e9e1d: e8 5e e5 ff ff               	call	0x4e8380
  4e9e22: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
  4e9e28: 8b 89 b4 42 00 00            	mov	ecx, dword ptr [ecx + 0x42b4]
  4e9e2e: e8 1d fe f1 ff               	call	0x409c50
  4e9e33: 6a 12                        	push	0x12
  4e9e35: 8b ce                        	mov	ecx, esi
  4e9e37: 84 c0                        	test	al, al
  4e9e39: 74 52                        	je	0x4e9e8d <.text+0x40d>
  4e9e3b: e8 e0 e0 ff ff               	call	0x4e7f20
  4e9e40: 85 c0                        	test	eax, eax
  4e9e42: 74 06                        	je	0x4e9e4a <.text+0x3ca>
  4e9e44: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9e48: 75 48                        	jne	0x4e9e92 <.text+0x412>
  4e9e4a: 6a 12                        	push	0x12
  4e9e4c: 8b ce                        	mov	ecx, esi
  4e9e4e: e8 cd f6 ff ff               	call	0x4e9520
  4e9e53: 8b f8                        	mov	edi, eax
  4e9e55: 85 ff                        	test	edi, edi
  4e9e57: 74 39                        	je	0x4e9e92 <.text+0x412>
  4e9e59: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e9e5f: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e9e65: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e9e69: 85 c9                        	test	ecx, ecx
  4e9e6b: 74 08                        	je	0x4e9e75 <.text+0x3f5>
  4e9e6d: 8b 17                        	mov	edx, dword ptr [edi]
  4e9e6f: 52                           	push	edx
  4e9e70: e8 bb 54 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9e75: 85 db                        	test	ebx, ebx
  4e9e77: 74 0b                        	je	0x4e9e84 <.text+0x404>
  4e9e79: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e9e7c: 50                           	push	eax
  4e9e7d: 8b cb                        	mov	ecx, ebx
  4e9e7f: e8 ac 54 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9e84: 8b ce                        	mov	ecx, esi
  4e9e86: e8 05 d9 ff ff               	call	0x4e7790
  4e9e8b: eb 05                        	jmp	0x4e9e92 <.text+0x412>
  4e9e8d: e8 ee e4 ff ff               	call	0x4e8380
  4e9e92: e8 79 c5 21 00               	call	0x706410 <.text+0x21c990>
  4e9e97: 8b c8                        	mov	ecx, eax
  4e9e99: e8 d2 25 27 00               	call	0x75c470 <.text+0x2729f0>
  4e9e9e: 6a 0a                        	push	0xa
  4e9ea0: 8b ce                        	mov	ecx, esi
  4e9ea2: 83 f8 0a                     	cmp	eax, 0xa
  4e9ea5: 75 52                        	jne	0x4e9ef9 <.text+0x479>
  4e9ea7: e8 74 e0 ff ff               	call	0x4e7f20
  4e9eac: 85 c0                        	test	eax, eax
  4e9eae: 74 06                        	je	0x4e9eb6 <.text+0x436>
  4e9eb0: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9eb4: 75 48                        	jne	0x4e9efe <.text+0x47e>
  4e9eb6: 6a 0a                        	push	0xa
  4e9eb8: 8b ce                        	mov	ecx, esi
  4e9eba: e8 61 f6 ff ff               	call	0x4e9520
  4e9ebf: 8b f8                        	mov	edi, eax
  4e9ec1: 85 ff                        	test	edi, edi
  4e9ec3: 74 39                        	je	0x4e9efe <.text+0x47e>
  4e9ec5: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e9ecb: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e9ed1: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e9ed5: 85 c9                        	test	ecx, ecx
  4e9ed7: 74 08                        	je	0x4e9ee1 <.text+0x461>
  4e9ed9: 8b 17                        	mov	edx, dword ptr [edi]
  4e9edb: 52                           	push	edx
  4e9edc: e8 4f 54 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9ee1: 85 db                        	test	ebx, ebx
  4e9ee3: 74 0b                        	je	0x4e9ef0 <.text+0x470>
  4e9ee5: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e9ee8: 50                           	push	eax
  4e9ee9: 8b cb                        	mov	ecx, ebx
  4e9eeb: e8 40 54 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9ef0: 8b ce                        	mov	ecx, esi
  4e9ef2: e8 99 d8 ff ff               	call	0x4e7790
  4e9ef7: eb 05                        	jmp	0x4e9efe <.text+0x47e>
  4e9ef9: e8 82 e4 ff ff               	call	0x4e8380
  4e9efe: e8 cd a5 c9 00               	call	0x11844d0 <.text+0xc9aa50>
  4e9f03: 8b c8                        	mov	ecx, eax
  4e9f05: e8 f6 9b c9 00               	call	0x1183b00 <.text+0xc9a080>
  4e9f0a: 6a 0c                        	push	0xc
  4e9f0c: 8b ce                        	mov	ecx, esi
  4e9f0e: 84 c0                        	test	al, al
  4e9f10: 74 52                        	je	0x4e9f64 <.text+0x4e4>
  4e9f12: e8 09 e0 ff ff               	call	0x4e7f20
  4e9f17: 85 c0                        	test	eax, eax
  4e9f19: 74 06                        	je	0x4e9f21 <.text+0x4a1>
  4e9f1b: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9f1f: 75 48                        	jne	0x4e9f69 <.text+0x4e9>
  4e9f21: 6a 0c                        	push	0xc
  4e9f23: 8b ce                        	mov	ecx, esi
  4e9f25: e8 f6 f5 ff ff               	call	0x4e9520
  4e9f2a: 8b f8                        	mov	edi, eax
  4e9f2c: 85 ff                        	test	edi, edi
  4e9f2e: 74 39                        	je	0x4e9f69 <.text+0x4e9>
  4e9f30: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e9f36: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e9f3c: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e9f40: 85 c9                        	test	ecx, ecx
  4e9f42: 74 08                        	je	0x4e9f4c <.text+0x4cc>
  4e9f44: 8b 17                        	mov	edx, dword ptr [edi]
  4e9f46: 52                           	push	edx
  4e9f47: e8 e4 53 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9f4c: 85 db                        	test	ebx, ebx
  4e9f4e: 74 0b                        	je	0x4e9f5b <.text+0x4db>
  4e9f50: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e9f53: 50                           	push	eax
  4e9f54: 8b cb                        	mov	ecx, ebx
  4e9f56: e8 d5 53 cd 00               	call	0x11bf330 <.text+0xcd58b0>
  4e9f5b: 8b ce                        	mov	ecx, esi
  4e9f5d: e8 2e d8 ff ff               	call	0x4e7790
  4e9f62: eb 05                        	jmp	0x4e9f69 <.text+0x4e9>
  4e9f64: e8 17 e4 ff ff               	call	0x4e8380
  4e9f69: 6a 1b                        	push	0x1b
  4e9f6b: 8b ce                        	mov	ecx, esi
  4e9f6d: e8 ae df ff ff               	call	0x4e7f20
  4e9f72: 85 c0                        	test	eax, eax
  4e9f74: 74 06                        	je	0x4e9f7c <.text+0x4fc>
  4e9f76: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9f7a: 75 25                        	jne	0x4e9fa1 <.text+0x521>
  4e9f7c: 8b 0d                        	<unknown>
  4e9f7e: 18 f7                        	sbb	bh, dh
