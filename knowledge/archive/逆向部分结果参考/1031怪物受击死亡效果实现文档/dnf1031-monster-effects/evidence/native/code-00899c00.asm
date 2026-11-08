
D:\game\DNF1031客户端-20260708\combat_ui_1031\reports\code-00899c00.elf:	file format elf32-i386

Disassembly of section .text:

00899c00 <.text>:
  899c00: 85 c0                        	test	eax, eax
  899c02: 75 05                        	jne	0x899c09 <.text+0x9>
  899c04: e8 9e d1 b3 00               	call	0x13d6da7 <.text+0xb3d1a7>
  899c09: 8b 01                        	mov	eax, dword ptr [ecx]
  899c0b: 8b 16                        	mov	edx, dword ptr [esi]
  899c0d: 8b 92 38 01 00 00            	mov	edx, dword ptr [edx + 0x138]
  899c13: 50                           	push	eax
  899c14: 8b ce                        	mov	ecx, esi
  899c16: ff d2                        	call	edx
  899c18: 8b 86 50 4b 00 00            	mov	eax, dword ptr [esi + 0x4b50]
  899c1e: 8b 8e 54 4b 00 00            	mov	ecx, dword ptr [esi + 0x4b54]
  899c24: 2b c8                        	sub	ecx, eax
  899c26: c1 f9 02                     	sar	ecx, 0x2
  899c29: 83 f9 01                     	cmp	ecx, 0x1
  899c2c: 77 05                        	ja	0x899c33 <.text+0x33>
  899c2e: e8 74 d1 b3 00               	call	0x13d6da7 <.text+0xb3d1a7>
  899c33: 8b 16                        	mov	edx, dword ptr [esi]
  899c35: 8b 40 04                     	mov	eax, dword ptr [eax + 0x4]
  899c38: 8b 92 38 01 00 00            	mov	edx, dword ptr [edx + 0x138]
  899c3e: 50                           	push	eax
  899c3f: 8b ce                        	mov	ecx, esi
  899c41: ff d2                        	call	edx
  899c43: 8b 86 50 4b 00 00            	mov	eax, dword ptr [esi + 0x4b50]
  899c49: 8b 8e 54 4b 00 00            	mov	ecx, dword ptr [esi + 0x4b54]
  899c4f: 2b c8                        	sub	ecx, eax
  899c51: c1 f9 02                     	sar	ecx, 0x2
  899c54: 83 f9 02                     	cmp	ecx, 0x2
  899c57: 77 05                        	ja	0x899c5e <.text+0x5e>
  899c59: e8 49 d1 b3 00               	call	0x13d6da7 <.text+0xb3d1a7>
  899c5e: 8b 16                        	mov	edx, dword ptr [esi]
  899c60: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  899c63: 8b 92 38 01 00 00            	mov	edx, dword ptr [edx + 0x138]
  899c69: 50                           	push	eax
  899c6a: 8b ce                        	mov	ecx, esi
  899c6c: ff d2                        	call	edx
  899c6e: 8b 86 50 4b 00 00            	mov	eax, dword ptr [esi + 0x4b50]
  899c74: 8b 8e 54 4b 00 00            	mov	ecx, dword ptr [esi + 0x4b54]
  899c7a: 2b c8                        	sub	ecx, eax
  899c7c: c1 f9 02                     	sar	ecx, 0x2
  899c7f: 83 f9 03                     	cmp	ecx, 0x3
  899c82: 77 05                        	ja	0x899c89 <.text+0x89>
  899c84: e8 1e d1 b3 00               	call	0x13d6da7 <.text+0xb3d1a7>
  899c89: 8b 16                        	mov	edx, dword ptr [esi]
  899c8b: 8b 40 0c                     	mov	eax, dword ptr [eax + 0xc]
  899c8e: 8b 92 38 01 00 00            	mov	edx, dword ptr [edx + 0x138]
  899c94: 50                           	push	eax
  899c95: 8b ce                        	mov	ecx, esi
  899c97: ff d2                        	call	edx
  899c99: 8b 86 50 4b 00 00            	mov	eax, dword ptr [esi + 0x4b50]
  899c9f: 8b 8e 54 4b 00 00            	mov	ecx, dword ptr [esi + 0x4b54]
  899ca5: 2b c8                        	sub	ecx, eax
  899ca7: c1 f9 02                     	sar	ecx, 0x2
  899caa: 83 f9 04                     	cmp	ecx, 0x4
  899cad: 77 05                        	ja	0x899cb4 <.text+0xb4>
  899caf: e8 f3 d0 b3 00               	call	0x13d6da7 <.text+0xb3d1a7>
  899cb4: 8b 16                        	mov	edx, dword ptr [esi]
  899cb6: 8b 40 10                     	mov	eax, dword ptr [eax + 0x10]
  899cb9: 8b 92 38 01 00 00            	mov	edx, dword ptr [edx + 0x138]
  899cbf: 50                           	push	eax
  899cc0: 8b ce                        	mov	ecx, esi
  899cc2: ff d2                        	call	edx
  899cc4: 8b 8e 80 48 00 00            	mov	ecx, dword ptr [esi + 0x4880]
  899cca: 2b 8e 7c 48 00 00            	sub	ecx, dword ptr [esi + 0x487c]
  899cd0: b8 67 66 66 66               	mov	eax, 0x66666667
  899cd5: f7 e9                        	imul	ecx
  899cd7: c1 fa 03                     	sar	edx, 0x3
  899cda: 8b c2                        	mov	eax, edx
  899cdc: c1 e8 1f                     	shr	eax, 0x1f
  899cdf: 03 c2                        	add	eax, edx
  899ce1: 0f 84 a7 00 00 00            	je	0x899d8e <.text+0x18e>
  899ce7: 89 7d ec                     	mov	dword ptr [ebp - 0x14], edi
  899cea: 3b c7                        	cmp	eax, edi
  899cec: 0f 86 9c 00 00 00            	jbe	0x899d8e <.text+0x18e>
  899cf2: 33 db                        	xor	ebx, ebx
  899cf4: eb 0a                        	jmp	0x899d00 <.text+0x100>
  899cf6: 8d a4 24 00 00 00 00         	lea	esp, [esp]
  899cfd: 8d 49 00                     	lea	ecx, [ecx]
  899d00: 8b 8e 7c 48 00 00            	mov	ecx, dword ptr [esi + 0x487c]
  899d06: 8b 96 80 48 00 00            	mov	edx, dword ptr [esi + 0x4880]
  899d0c: 2b d1                        	sub	edx, ecx
  899d0e: b8 67 66 66 66               	mov	eax, 0x66666667
  899d13: f7 ea                        	imul	edx
  899d15: c1 fa 03                     	sar	edx, 0x3
  899d18: 8b c2                        	mov	eax, edx
  899d1a: c1 e8 1f                     	shr	eax, 0x1f
  899d1d: 03 c2                        	add	eax, edx
  899d1f: 39 45 ec                     	cmp	dword ptr [ebp - 0x14], eax
  899d22: 0f 83 80 fb ff ff            	jae	0x8998a8
  899d28: 8b 54 39 08                  	mov	edx, dword ptr [ecx + edi + 0x8]
  899d2c: 2b 54 39 04                  	sub	edx, dword ptr [ecx + edi + 0x4]
  899d30: c1 fa 02                     	sar	edx, 0x2
  899d33: 3b da                        	cmp	ebx, edx
  899d35: 73 28                        	jae	0x899d5f <.text+0x15f>
  899d37: 8b 44 39 04                  	mov	eax, dword ptr [ecx + edi + 0x4]
  899d3b: 8b 4c 39 08                  	mov	ecx, dword ptr [ecx + edi + 0x8]
  899d3f: 2b c8                        	sub	ecx, eax
  899d41: c1 f9 02                     	sar	ecx, 0x2
  899d44: 3b d9                        	cmp	ebx, ecx
  899d46: 0f 83 5c fb ff ff            	jae	0x8998a8
  899d4c: 8b 16                        	mov	edx, dword ptr [esi]
  899d4e: 8b 04 98                     	mov	eax, dword ptr [eax + 4*ebx]
  899d51: 8b 92 38 01 00 00            	mov	edx, dword ptr [edx + 0x138]
  899d57: 50                           	push	eax
  899d58: 8b ce                        	mov	ecx, esi
  899d5a: ff d2                        	call	edx
  899d5c: 43                           	inc	ebx
  899d5d: eb a1                        	jmp	0x899d00 <.text+0x100>
  899d5f: 8b 8e 80 48 00 00            	mov	ecx, dword ptr [esi + 0x4880]
  899d65: 2b 8e 7c 48 00 00            	sub	ecx, dword ptr [esi + 0x487c]
  899d6b: 8b 5d ec                     	mov	ebx, dword ptr [ebp - 0x14]
  899d6e: b8 67 66 66 66               	mov	eax, 0x66666667
  899d73: f7 e9                        	imul	ecx
  899d75: c1 fa 03                     	sar	edx, 0x3
  899d78: 8b c2                        	mov	eax, edx
  899d7a: c1 e8 1f                     	shr	eax, 0x1f
  899d7d: 43                           	inc	ebx
  899d7e: 03 c2                        	add	eax, edx
  899d80: 83 c7 14                     	add	edi, 0x14
  899d83: 89 5d ec                     	mov	dword ptr [ebp - 0x14], ebx
  899d86: 3b d8                        	cmp	ebx, eax
  899d88: 0f 82 64 ff ff ff            	jb	0x899cf2 <.text+0xf2>
  899d8e: 6a 00                        	push	0x0
  899d90: e8 cb 70 5b 00               	call	0xe50e60 <.text+0x5b7260>
  899d95: 99                           	cdq
  899d96: b9 64 00 00 00               	mov	ecx, 0x64
  899d9b: f7 f9                        	idiv	ecx
  899d9d: 83 c4 04                     	add	esp, 0x4
  899da0: 83 fa 0f                     	cmp	edx, 0xf
  899da3: 7d 10                        	jge	0x899db5 <.text+0x1b5>
  899da5: 8b 16                        	mov	edx, dword ptr [esi]
  899da7: 8b 82 c8 06 00 00            	mov	eax, dword ptr [edx + 0x6c8]
  899dad: 6a ff                        	push	-0x1
  899daf: 6a 66                        	push	0x66
  899db1: 8b ce                        	mov	ecx, esi
  899db3: ff d0                        	call	eax
  899db5: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
  899db8: 8b 41 04                     	mov	eax, dword ptr [ecx + 0x4]
  899dbb: 8b 49 08                     	mov	ecx, dword ptr [ecx + 0x8]
  899dbe: 2b c8                        	sub	ecx, eax
  899dc0: c1 f9 02                     	sar	ecx, 0x2
  899dc3: 85 c9                        	test	ecx, ecx
  899dc5: 75 05                        	jne	0x899dcc <.text+0x1cc>
  899dc7: e8 db cf b3 00               	call	0x13d6da7 <.text+0xb3d1a7>
  899dcc: 8b 38                        	mov	edi, dword ptr [eax]
  899dce: 6a 02                        	push	0x2
  899dd0: 8d 4d f3                     	lea	ecx, [ebp - 0xd]
  899dd3: 89 7d d8                     	mov	dword ptr [ebp - 0x28], edi
  899dd6: e8 b5 11 ec ff               	call	0x75af90
  899ddb: e8 30 c6 e6 ff               	call	0x706410
  899de0: 8a 90 8c 03 00 00            	mov	dl, byte ptr [eax + 0x38c]
  899de6: 8d 45 f3                     	lea	eax, [ebp - 0xd]
  899de9: 50                           	push	eax
  899dea: 8d 4d f2                     	lea	ecx, [ebp - 0xe]
  899ded: 88 55 f2                     	mov	byte ptr [ebp - 0xe], dl
  899df0: e8 6b f8 eb ff               	call	0x759660
  899df5: 84 c0                        	test	al, al
  899df7: 74 0c                        	je	0x899e05 <.text+0x205>
  899df9: c7 86 20 3d 00 00 64 00 00 00	mov	dword ptr [esi + 0x3d20], 0x64
  899e03: eb 49                        	jmp	0x899e4e <.text+0x24e>
  899e05: 8b 16                        	mov	edx, dword ptr [esi]
  899e07: 8b 82 a8 02 00 00            	mov	eax, dword ptr [edx + 0x2a8]
  899e0d: 8b ce                        	mov	ecx, esi
  899e0f: ff d0                        	call	eax
  899e11: 8b 16                        	mov	edx, dword ptr [esi]
  899e13: 8b d8                        	mov	ebx, eax
  899e15: 8b 42 48                     	mov	eax, dword ptr [edx + 0x48]
  899e18: 8b ce                        	mov	ecx, esi
  899e1a: ff d0                        	call	eax
  899e1c: 0f af d8                     	imul	ebx, eax
  899e1f: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  899e22: 6a 64                        	push	0x64
  899e24: 51                           	push	ecx
  899e25: 89 5d e0                     	mov	dword ptr [ebp - 0x20], ebx
  899e28: e8 33 70 5b 00               	call	0xe50e60 <.text+0x5b7260>
  899e2d: 99                           	cdq
  899e2e: b9 65 00 00 00               	mov	ecx, 0x65
  899e33: f7 f9                        	idiv	ecx
  899e35: 83 c4 04                     	add	esp, 0x4
  899e38: 52                           	push	edx
  899e39: 68 fa 00 00 00               	push	0xfa
  899e3e: 6a 64                        	push	0x64
  899e40: e8 7b fa 91 00               	call	0x11b98c0 <.text+0x91fcc0>
  899e45: 83 c4 10                     	add	esp, 0x10
  899e48: 89 86 20 3d 00 00            	mov	dword ptr [esi + 0x3d20], eax
  899e4e: 85 ff                        	test	edi, edi
  899e50: 75 41                        	jne	0x899e93 <.text+0x293>
  899e52: 8b 16                        	mov	edx, dword ptr [esi]
  899e54: 8b 82 e4 07 00 00            	mov	eax, dword ptr [edx + 0x7e4]
  899e5a: 8b ce                        	mov	ecx, esi
  899e5c: ff d0                        	call	eax
  899e5e: 8b 16                        	mov	edx, dword ptr [esi]
  899e60: 8b 82 28 07 00 00            	mov	eax, dword ptr [edx + 0x728]
  899e66: 8b ce                        	mov	ecx, esi
  899e68: ff d0                        	call	eax
  899e6a: 84 c0                        	test	al, al
  899e6c: 0f 85 22 01 00 00            	jne	0x899f94 <.text+0x394>
  899e72: 8d 8e 24 47 00 00            	lea	ecx, [esi + 0x4724]
  899e78: e8 73 05 92 00               	call	0x11ba3f0 <.text+0x9207f0>
  899e7d: 57                           	push	edi
  899e7e: 68 88 13 00 00               	push	0x1388
  899e83: 8d 8e 24 47 00 00            	lea	ecx, [esi + 0x4724]
  899e89: e8 82 0b 92 00               	call	0x11baa10 <.text+0x920e10>
  899e8e: e9 01 01 00 00               	jmp	0x899f94 <.text+0x394>
  899e93: 8b 9e 74 3a 00 00            	mov	ebx, dword ptr [esi + 0x3a74]
  899e99: 68 34 02 00 00               	push	0x234
  899e9e: f7 d3                        	not	ebx
  899ea0: e8 db 64 91 00               	call	0x11b0380 <.text+0x916780>
  899ea5: 8b f8                        	mov	edi, eax
  899ea7: 83 c4 04                     	add	esp, 0x4
  899eaa: 89 7d d4                     	mov	dword ptr [ebp - 0x2c], edi
  899ead: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
  899eb4: 85 ff                        	test	edi, edi
  899eb6: 74 59                        	je	0x899f11 <.text+0x311>
  899eb8: 8b 8e 20 3d 00 00            	mov	ecx, dword ptr [esi + 0x3d20]
  899ebe: 8b 96 70 3a 00 00            	mov	edx, dword ptr [esi + 0x3a70]
  899ec4: 56                           	push	esi
  899ec5: 89 4d e0                     	mov	dword ptr [ebp - 0x20], ecx
  899ec8: 89 55 ec                     	mov	dword ptr [ebp - 0x14], edx
  899ecb: e8 e0 f3 ec ff               	call	0x7692b0
  899ed0: 83 c4 04                     	add	esp, 0x4
  899ed3: 8b cf                        	mov	ecx, edi
  899ed5: 89 45 dc                     	mov	dword ptr [ebp - 0x24], eax
  899ed8: e8 e3 7e ba ff               	call	0x441dc0
  899edd: 8b cf                        	mov	ecx, edi
  899edf: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
  899ee3: c7 07 94 ed 5c 01            	mov	dword ptr [edi], 0x15ced94
  899ee9: c7 47 08 44 ed 5c 01         	mov	dword ptr [edi + 0x8], 0x15ced44
  899ef0: e8 bb 11 5a 00               	call	0xe3b0b0 <.text+0x5a14b0>
  899ef5: 8b 45 e0                     	mov	eax, dword ptr [ebp - 0x20]
  899ef8: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
  899efb: 8b 55 dc                     	mov	edx, dword ptr [ebp - 0x24]
  899efe: 6a 04                        	push	0x4
  899f00: 53                           	push	ebx
  899f01: 50                           	push	eax
  899f02: 8b 45 d8                     	mov	eax, dword ptr [ebp - 0x28]
  899f05: 51                           	push	ecx
  899f06: 52                           	push	edx
  899f07: 50                           	push	eax
  899f08: 8b cf                        	mov	ecx, edi
  899f0a: e8 11 25 5a 00               	call	0xe3c420 <.text+0x5a2820>
  899f0f: eb 02                        	jmp	0x899f13 <.text+0x313>
  899f11: 33 ff                        	xor	edi, edi
  899f13: 8b 8e b8 00 00 00            	mov	ecx, dword ptr [esi + 0xb8]
  899f19: 6a 00                        	push	0x0
  899f1b: 6a 00                        	push	0x0
  899f1d: 56                           	push	esi
  899f1e: 57                           	push	edi
  899f1f: 6a 00                        	push	0x0
  899f21: 6a 02                        	push	0x2
  899f23: 56                           	push	esi
  899f24: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  899f2b: e8 b0 4a 01 00               	call	0x8ae9e0 <.text+0x14de0>
  899f30: 8b 16                        	mov	edx, dword ptr [esi]
  899f32: 8b 82 ac 00 00 00            	mov	eax, dword ptr [edx + 0xac]
  899f38: 8b 1f                        	mov	ebx, dword ptr [edi]
  899f3a: 8b ce                        	mov	ecx, esi
  899f3c: ff d0                        	call	eax
  899f3e: 8b c8                        	mov	ecx, eax
  899f40: 8b 86 7c 01 00 00            	mov	eax, dword ptr [esi + 0x17c]
  899f46: 99                           	cdq
  899f47: 2b c2                        	sub	eax, edx
  899f49: 8b 16                        	mov	edx, dword ptr [esi]
  899f4b: d1 f8                        	sar	eax
  899f4d: 03 c8                        	add	ecx, eax
  899f4f: 8b 82 a8 00 00 00            	mov	eax, dword ptr [edx + 0xa8]
  899f55: 51                           	push	ecx
  899f56: 8b ce                        	mov	ecx, esi
  899f58: ff d0                        	call	eax
  899f5a: 8b 16                        	mov	edx, dword ptr [esi]
  899f5c: 50                           	push	eax
  899f5d: 8b 82 a4 00 00 00            	mov	eax, dword ptr [edx + 0xa4]
  899f63: 8b ce                        	mov	ecx, esi
  899f65: ff d0                        	call	eax
  899f67: 8b 93 98 00 00 00            	mov	edx, dword ptr [ebx + 0x98]
  899f6d: 50                           	push	eax
  899f6e: 8b cf                        	mov	ecx, edi
  899f70: ff d2                        	call	edx
  899f72: 8b 06                        	mov	eax, dword ptr [esi]
  899f74: 8b 90 28 07 00 00            	mov	edx, dword ptr [eax + 0x728]
  899f7a: 8b ce                        	mov	ecx, esi
  899f7c: ff d2                        	call	edx
  899f7e: 84 c0                        	test	al, al
  899f80: 75 12                        	jne	0x899f94 <.text+0x394>
  899f82: 8b 06                        	mov	eax, dword ptr [esi]
  899f84: 8b 90 80 01 00 00            	mov	edx, dword ptr [eax + 0x180]
  899f8a: 6a ff                        	push	-0x1
  899f8c: 6a 05                        	push	0x5
  899f8e: 6a 01                        	push	0x1
  899f90: 8b ce                        	mov	ecx, esi
  899f92: ff d2                        	call	edx
  899f94: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
  899f97: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
  899f9a: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
  899f9d: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
  899fa0: 50                           	push	eax
  899fa1: 51                           	push	ecx
  899fa2: 52                           	push	edx
  899fa3: 53                           	push	ebx
  899fa4: 8b ce                        	mov	ecx, esi
  899fa6: e8 35 c1 f9 ff               	call	0x8360e0
  899fab: 8b 06                        	mov	eax, dword ptr [esi]
  899fad: 8b 90 ac 05 00 00            	mov	edx, dword ptr [eax + 0x5ac]
  899fb3: 8b ce                        	mov	ecx, esi
  899fb5: ff d2                        	call	edx
  899fb7: 3b d8                        	cmp	ebx, eax
  899fb9: 7c 52                        	jl	0x89a00d <.text+0x40d>
  899fbb: 8b 06                        	mov	eax, dword ptr [esi]
  899fbd: 8b 50 3c                     	mov	edx, dword ptr [eax + 0x3c]
  899fc0: 8b ce                        	mov	ecx, esi
  899fc2: ff d2                        	call	edx
  899fc4: 84 c0                        	test	al, al
  899fc6: 74 45                        	je	0x89a00d <.text+0x40d>
  899fc8: 8b 3e                        	mov	edi, dword ptr [esi]
  899fca: 8b 87 ac 05 00 00            	mov	eax, dword ptr [edi + 0x5ac]
  899fd0: 8b ce                        	mov	ecx, esi
  899fd2: ff d0                        	call	eax
  899fd4: 8b 97 d0 04 00 00            	mov	edx, dword ptr [edi + 0x4d0]
  899fda: 8b cb                        	mov	ecx, ebx
  899fdc: 2b c8                        	sub	ecx, eax
  899fde: 51                           	push	ecx
  899fdf: 8b ce                        	mov	ecx, esi
  899fe1: ff d2                        	call	edx
  899fe3: 85 c0                        	test	eax, eax
  899fe5: 74 26                        	je	0x89a00d <.text+0x40d>
  899fe7: 8b 3e                        	mov	edi, dword ptr [esi]
  899fe9: 8b 87 ac 05 00 00            	mov	eax, dword ptr [edi + 0x5ac]
  899fef: 8b ce                        	mov	ecx, esi
  899ff1: ff d0                        	call	eax
  899ff3: 8b 97 d0 04 00 00            	mov	edx, dword ptr [edi + 0x4d0]
  899ff9: 8b cb                        	mov	ecx, ebx
  899ffb: 2b c8                        	sub	ecx, eax
  899ffd: 51                           	push	ecx
  899ffe: 8b ce                        	mov	ecx, esi
  89a000: ff d2                        	call	edx
  89a002: 50                           	push	eax
  89a003: 8b 87 44 01 00 00            	mov	eax, dword ptr [edi + 0x144]
  89a009: 8b ce                        	mov	ecx, esi
  89a00b: ff d0                        	call	eax
  89a00d: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
  89a010: 83 f8 03                     	cmp	eax, 0x3
  89a013: 0f 84 04 01 00 00            	je	0x89a11d <.text+0x51d>
  89a019: 83 f8 08                     	cmp	eax, 0x8
  89a01c: 0f 85 07 01 00 00            	jne	0x89a129 <.text+0x529>
  89a022: 8b 8e 80 48 00 00            	mov	ecx, dword ptr [esi + 0x4880]
  89a028: 2b 8e 7c 48 00 00            	sub	ecx, dword ptr [esi + 0x487c]
  89a02e: b8 67 66 66 66               	mov	eax, 0x66666667
  89a033: f7 e9                        	imul	ecx
  89a035: c1 fa 03                     	sar	edx, 0x3
  89a038: 8b c2                        	mov	eax, edx
  89a03a: c1 e8 1f                     	shr	eax, 0x1f
  89a03d: 03 c2                        	add	eax, edx
  89a03f: 0f 84 cf 00 00 00            	je	0x89a114 <.text+0x514>
  89a045: c7 45 ec 00 00 00 00         	mov	dword ptr [ebp - 0x14], 0x0
  89a04c: 85 c0                        	test	eax, eax
  89a04e: 0f 84 c0 00 00 00            	je	0x89a114 <.text+0x514>
  89a054: 33 db                        	xor	ebx, ebx
  89a056: eb 08                        	jmp	0x89a060 <.text+0x460>
  89a058: 8d a4 24 00 00 00 00         	lea	esp, [esp]
  89a05f: 90                           	nop
  89a060: 33 ff                        	xor	edi, edi
  89a062: 8b 8e 7c 48 00 00            	mov	ecx, dword ptr [esi + 0x487c]
  89a068: 8b 96 80 48 00 00            	mov	edx, dword ptr [esi + 0x4880]
  89a06e: 2b d1                        	sub	edx, ecx
  89a070: b8 67 66 66 66               	mov	eax, 0x66666667
  89a075: f7 ea                        	imul	edx
  89a077: c1 fa 03                     	sar	edx, 0x3
  89a07a: 8b c2                        	mov	eax, edx
  89a07c: c1 e8 1f                     	shr	eax, 0x1f
  89a07f: 03 c2                        	add	eax, edx
  89a081: 39 45 ec                     	cmp	dword ptr [ebp - 0x14], eax
  89a084: 0f 83 1e f8 ff ff            	jae	0x8998a8
  89a08a: 8b 54 19 08                  	mov	edx, dword ptr [ecx + ebx + 0x8]
  89a08e: 2b 54 19 04                  	sub	edx, dword ptr [ecx + ebx + 0x4]
  89a092: c1 fa 02                     	sar	edx, 0x2
  89a095: 3b fa                        	cmp	edi, edx
  89a097: 73 49                        	jae	0x89a0e2 <.text+0x4e2>
  89a099: 8b 44 19 04                  	mov	eax, dword ptr [ecx + ebx + 0x4]
  89a09d: 8b 54 19 08                  	mov	edx, dword ptr [ecx + ebx + 0x8]
  89a0a1: 2b d0                        	sub	edx, eax
  89a0a3: c1 fa 02                     	sar	edx, 0x2
  89a0a6: 3b fa                        	cmp	edi, edx
  89a0a8: 0f 83 fa f7 ff ff            	jae	0x8998a8
  89a0ae: 8b 04 b8                     	mov	eax, dword ptr [eax + 4*edi]
  89a0b1: f6 80 ec 01 00 00 08         	test	byte ptr [eax + 0x1ec], 0x8
  89a0b8: 74 25                        	je	0x89a0df <.text+0x4df>
  89a0ba: 8b 44 19 04                  	mov	eax, dword ptr [ecx + ebx + 0x4]
  89a0be: 8b 4c 19 08                  	mov	ecx, dword ptr [ecx + ebx + 0x8]
  89a0c2: 2b c8                        	sub	ecx, eax
  89a0c4: c1 f9 02                     	sar	ecx, 0x2
  89a0c7: 3b f9                        	cmp	edi, ecx
  89a0c9: 0f 83 d9 f7 ff ff            	jae	0x8998a8
  89a0cf: 8b 16                        	mov	edx, dword ptr [esi]
  89a0d1: 8b 04 b8                     	mov	eax, dword ptr [eax + 4*edi]
  89a0d4: 8b 92 38 01 00 00            	mov	edx, dword ptr [edx + 0x138]
  89a0da: 50                           	push	eax
  89a0db: 8b ce                        	mov	ecx, esi
  89a0dd: ff d2                        	call	edx
  89a0df: 47                           	inc	edi
  89a0e0: eb 80                        	jmp	0x89a062 <.text+0x462>
  89a0e2: 8b 8e 80 48 00 00            	mov	ecx, dword ptr [esi + 0x4880]
  89a0e8: 2b 8e 7c 48 00 00            	sub	ecx, dword ptr [esi + 0x487c]
  89a0ee: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
  89a0f1: b8 67 66 66 66               	mov	eax, 0x66666667
  89a0f6: f7 e9                        	imul	ecx
  89a0f8: c1 fa 03                     	sar	edx, 0x3
  89a0fb: 8b c2                        	mov	eax, edx
  89a0fd: c1 e8 1f                     	shr	eax, 0x1f
  89a100: 47                           	inc	edi
  89a101: 03 c2                        	add	eax, edx
  89a103: 83 c3 14                     	add	ebx, 0x14
  89a106: 89 7d ec                     	mov	dword ptr [ebp - 0x14], edi
  89a109: 3b f8                        	cmp	edi, eax
  89a10b: 0f 82 4f ff ff ff            	jb	0x89a060 <.text+0x460>
  89a111: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
  89a114: c6 86 b0 4a 00 00 00         	mov	byte ptr [esi + 0x4ab0], 0x0
  89a11b: eb 0c                        	jmp	0x89a129 <.text+0x529>
  89a11d: 8b 16                        	mov	edx, dword ptr [esi]
  89a11f: 8b 82 f8 07 00 00            	mov	eax, dword ptr [edx + 0x7f8]
  89a125: 8b ce                        	mov	ecx, esi
  89a127: ff d0                        	call	eax
  89a129: 83 fb 08                     	cmp	ebx, 0x8
  89a12c: 0f 85 e3 01 00 00            	jne	0x89a315 <.text+0x715>
  89a132: 8b 55 e8                     	mov	edx, dword ptr [ebp - 0x18]
  89a135: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
  89a138: 51                           	push	ecx
  89a139: 52                           	push	edx
  89a13a: 8d 8e b8 34 00 00            	lea	ecx, [esi + 0x34b8]
  89a140: e8 9b 6c 90 00               	call	0x11a0de0 <.text+0x9071e0>
  89a145: 8b 9e 7c 48 00 00            	mov	ebx, dword ptr [esi + 0x487c]
  89a14b: 8b 8e                        	<unknown>
  89a14d: 80 48 00                     	<unknown>
