
<stdin>:	file format elf32-i386

Disassembly of section .text:

0111c3d0 <.text>:
 111c3d0: d5 ff                        	aad	-0x1
 111c3d2: 8b 0d 50 f7 a6 01            	mov	ecx, dword ptr [0x1a6f750]
 111c3d8: 6a 00                        	push	0x0
 111c3da: 6a ff                        	push	-0x1
 111c3dc: 68 81 00 00 00               	push	0x81
 111c3e1: e8 ca 81 d5 ff               	call	0xe745b0
 111c3e6: eb 30                        	jmp	0x111c418 <.text+0x48>
 111c3e8: 8d 8f 28 01 00 00            	lea	ecx, [edi + 0x128]
 111c3ee: e8 fd df 09 00               	call	0x11ba3f0 <.text+0x9e020>
 111c3f3: 6a 00                        	push	0x0
 111c3f5: 6a 00                        	push	0x0
 111c3f7: 8d 8f 28 01 00 00            	lea	ecx, [edi + 0x128]
 111c3fd: e8 0e e6 09 00               	call	0x11baa10 <.text+0x9e640>
 111c402: 68 4c 04 00 00               	push	0x44c
 111c407: 8d 8f 28 01 00 00            	lea	ecx, [edi + 0x128]
 111c40d: e8 8e e3 09 00               	call	0x11ba7a0 <.text+0x9e3d0>
 111c412: 8a 9f 7c 02 00 00            	mov	bl, byte ptr [edi + 0x27c]
 111c418: 8b 87 04 01 00 00            	mov	eax, dword ptr [edi + 0x104]
 111c41e: 85 c0                        	test	eax, eax
 111c420: 75 0a                        	jne	0x111c42c <.text+0x5c>
 111c422: 8b 87 f4 00 00 00            	mov	eax, dword ptr [edi + 0xf4]
 111c428: 85 c0                        	test	eax, eax
 111c42a: 74 51                        	je	0x111c47d <.text+0xad>
 111c42c: 8b 0d 28 f7 a6 01            	mov	ecx, dword ptr [0x1a6f728]
 111c432: 88 5d 08                     	mov	byte ptr [ebp + 0x8], bl
 111c435: e8 36 a1 80 ff               	call	0x926570
 111c43a: 85 c0                        	test	eax, eax
 111c43c: 74 22                        	je	0x111c460 <.text+0x90>
 111c43e: 84 db                        	test	bl, bl
 111c440: 74 1a                        	je	0x111c45c <.text+0x8c>
 111c442: 8b 0d 28 f7 a6 01            	mov	ecx, dword ptr [0x1a6f728]
 111c448: e8 23 a1 80 ff               	call	0x926570
 111c44d: 8b c8                        	mov	ecx, eax
 111c44f: e8 fc cf 58 ff               	call	0x6a9450
 111c454: c6 45 08 01                  	mov	byte ptr [ebp + 0x8], 0x1
 111c458: 84 c0                        	test	al, al
 111c45a: 74 04                        	je	0x111c460 <.text+0x90>
 111c45c: c6 45 08 00                  	mov	byte ptr [ebp + 0x8], 0x0
 111c460: 8b 87 04 01 00 00            	mov	eax, dword ptr [edi + 0x104]
 111c466: 85 c0                        	test	eax, eax
 111c468: 75 06                        	jne	0x111c470 <.text+0xa0>
 111c46a: 8b 87 f4 00 00 00            	mov	eax, dword ptr [edi + 0xf4]
 111c470: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 111c473: 8b 10                        	mov	edx, dword ptr [eax]
 111c475: 8b 52 18                     	mov	edx, dword ptr [edx + 0x18]
 111c478: 51                           	push	ecx
 111c479: 8b c8                        	mov	ecx, eax
 111c47b: ff d2                        	call	edx
 111c47d: 8b 8f b0 03 00 00            	mov	ecx, dword ptr [edi + 0x3b0]
 111c483: e8 28 67 f8 ff               	call	0x10a2bb0
 111c488: 8b c8                        	mov	ecx, eax
 111c48a: e8 b1 ab 5d ff               	call	0x6f7040
 111c48f: 8b f0                        	mov	esi, eax
 111c491: 8d 45 e0                     	lea	eax, [ebp - 0x20]
 111c494: 50                           	push	eax
 111c495: 8b ce                        	mov	ecx, esi
 111c497: e8 74 12 20 00               	call	0x131d710 <.text+0x201340>
 111c49c: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 111c49f: 51                           	push	ecx
 111c4a0: 8b ce                        	mov	ecx, esi
 111c4a2: e8 c9 9c 05 00               	call	0x1176170 <.text+0x59da0>
 111c4a7: 8b 5d e0                     	mov	ebx, dword ptr [ebp - 0x20]
 111c4aa: 8b 75 e8                     	mov	esi, dword ptr [ebp - 0x18]
 111c4ad: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
 111c4b0: 85 db                        	test	ebx, ebx
 111c4b2: 0f 84 8a 00 00 00            	je	0x111c542 <.text+0x172>
 111c4b8: 8b 03                        	mov	eax, dword ptr [ebx]
 111c4ba: 85 c0                        	test	eax, eax
 111c4bc: 0f 84 80 00 00 00            	je	0x111c542 <.text+0x172>
 111c4c2: 85 c9                        	test	ecx, ecx
 111c4c4: 74 02                        	je	0x111c4c8 <.text+0xf8>
 111c4c6: 8b 09                        	mov	ecx, dword ptr [ecx]
 111c4c8: 3b c1                        	cmp	eax, ecx
 111c4ca: 75 76                        	jne	0x111c542 <.text+0x172>
 111c4cc: 3b 75 f4                     	cmp	esi, dword ptr [ebp - 0xc]
 111c4cf: 74 76                        	je	0x111c547 <.text+0x177>
 111c4d1: 85 c0                        	test	eax, eax
 111c4d3: 74 6d                        	je	0x111c542 <.text+0x172>
 111c4d5: 85 f6                        	test	esi, esi
 111c4d7: 74 69                        	je	0x111c542 <.text+0x172>
 111c4d9: 3b 70 04                     	cmp	esi, dword ptr [eax + 0x4]
 111c4dc: 74 64                        	je	0x111c542 <.text+0x172>
 111c4de: 83 7e 08 00                  	cmp	dword ptr [esi + 0x8], 0x0
 111c4e2: 74 4c                        	je	0x111c530 <.text+0x160>
 111c4e4: 85 c0                        	test	eax, eax
 111c4e6: 74 5a                        	je	0x111c542 <.text+0x172>
 111c4e8: 3b 70 04                     	cmp	esi, dword ptr [eax + 0x4]
 111c4eb: 74 55                        	je	0x111c542 <.text+0x172>
 111c4ed: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
 111c4f0: e8 8b cb 49 ff               	call	0x5b9080
 111c4f5: 83 f8 0e                     	cmp	eax, 0xe
 111c4f8: 75 36                        	jne	0x111c530 <.text+0x160>
 111c4fa: 8b 03                        	mov	eax, dword ptr [ebx]
 111c4fc: 85 c0                        	test	eax, eax
 111c4fe: 74 42                        	je	0x111c542 <.text+0x172>
 111c500: 3b 70 04                     	cmp	esi, dword ptr [eax + 0x4]
 111c503: 74 3d                        	je	0x111c542 <.text+0x172>
 111c505: 8b 56 08                     	mov	edx, dword ptr [esi + 0x8]
 111c508: 6a 00                        	push	0x0
 111c50a: 68 74 9e a3 01               	push	0x1a39e74
 111c50f: 68 88 96 9d 01               	push	0x19d9688
 111c514: 6a 00                        	push	0x0
 111c516: 52                           	push	edx
 111c517: e8 c3 b1 2b 00               	call	0x13d76df <.text+0x2bb30f>
 111c51c: 83 c4 14                     	add	esp, 0x14
 111c51f: 85 c0                        	test	eax, eax
 111c521: 74 0d                        	je	0x111c530 <.text+0x160>
 111c523: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 111c526: 8b 10                        	mov	edx, dword ptr [eax]
 111c528: 8b 52 18                     	mov	edx, dword ptr [edx + 0x18]
 111c52b: 51                           	push	ecx
 111c52c: 8b c8                        	mov	ecx, eax
 111c52e: ff d2                        	call	edx
 111c530: 8b 03                        	mov	eax, dword ptr [ebx]
 111c532: 85 c0                        	test	eax, eax
 111c534: 74 0c                        	je	0x111c542 <.text+0x172>
 111c536: 3b 70 04                     	cmp	esi, dword ptr [eax + 0x4]
 111c539: 74 07                        	je	0x111c542 <.text+0x172>
 111c53b: 8b 36                        	mov	esi, dword ptr [esi]
 111c53d: e9 6b ff ff ff               	jmp	0x111c4ad <.text+0xdd>
 111c542: e8 60 a8 2b 00               	call	0x13d6da7 <.text+0x2ba9d7>
 111c547: 8b 8f b0 03 00 00            	mov	ecx, dword ptr [edi + 0x3b0]
 111c54d: 85 c9                        	test	ecx, ecx
 111c54f: 0f 84 c5 00 00 00            	je	0x111c61a <.text+0x24a>
 111c555: e8 56 66 f8 ff               	call	0x10a2bb0
 111c55a: 85 c0                        	test	eax, eax
 111c55c: 0f 84 b8 00 00 00            	je	0x111c61a <.text+0x24a>
 111c562: 8b 8f b0 03 00 00            	mov	ecx, dword ptr [edi + 0x3b0]
 111c568: e8 43 66 f8 ff               	call	0x10a2bb0
 111c56d: 8b c8                        	mov	ecx, eax
 111c56f: e8 cc aa 5d ff               	call	0x6f7040
 111c574: 8b d8                        	mov	ebx, eax
 111c576: 8d 45 ec                     	lea	eax, [ebp - 0x14]
 111c579: 50                           	push	eax
 111c57a: 8b cb                        	mov	ecx, ebx
 111c57c: e8 8f 11 20 00               	call	0x131d710 <.text+0x201340>
 111c581: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
 111c584: 51                           	push	ecx
 111c585: 8b cb                        	mov	ecx, ebx
 111c587: e8 e4 9b 05 00               	call	0x1176170 <.text+0x59da0>
 111c58c: 8b 7d ec                     	mov	edi, dword ptr [ebp - 0x14]
 111c58f: 85 ff                        	test	edi, edi
 111c591: 74 af                        	je	0x111c542 <.text+0x172>
 111c593: 8b 17                        	mov	edx, dword ptr [edi]
 111c595: 85 d2                        	test	edx, edx
 111c597: 74 a9                        	je	0x111c542 <.text+0x172>
 111c599: 8b 08                        	mov	ecx, dword ptr [eax]
 111c59b: 85 c9                        	test	ecx, ecx
 111c59d: 74 02                        	je	0x111c5a1 <.text+0x1d1>
 111c59f: 8b 09                        	mov	ecx, dword ptr [ecx]
 111c5a1: 3b d1                        	cmp	edx, ecx
 111c5a3: 75 9d                        	jne	0x111c542 <.text+0x172>
 111c5a5: 8b 75 f4                     	mov	esi, dword ptr [ebp - 0xc]
 111c5a8: 3b 70 08                     	cmp	esi, dword ptr [eax + 0x8]
 111c5ab: 74 6d                        	je	0x111c61a <.text+0x24a>
 111c5ad: 8b c2                        	mov	eax, edx
 111c5af: 85 c0                        	test	eax, eax
 111c5b1: 74 8f                        	je	0x111c542 <.text+0x172>
 111c5b3: 85 f6                        	test	esi, esi
 111c5b5: 74 8b                        	je	0x111c542 <.text+0x172>
 111c5b7: 3b 70 04                     	cmp	esi, dword ptr [eax + 0x4]
 111c5ba: 74 86                        	je	0x111c542 <.text+0x172>
 111c5bc: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
 111c5bf: e8 bc ca 49 ff               	call	0x5b9080
 111c5c4: 83 f8 0f                     	cmp	eax, 0xf
 111c5c7: 75 31                        	jne	0x111c5fa <.text+0x22a>
 111c5c9: 8b 07                        	mov	eax, dword ptr [edi]
 111c5cb: 85 c0                        	test	eax, eax
 111c5cd: 0f 84 6f ff ff ff            	je	0x111c542 <.text+0x172>
 111c5d3: 3b 70 04                     	cmp	esi, dword ptr [eax + 0x4]
 111c5d6: 0f 84 66 ff ff ff            	je	0x111c542 <.text+0x172>
 111c5dc: 8b 56 08                     	mov	edx, dword ptr [esi + 0x8]
 111c5df: 6a 00                        	push	0x0
 111c5e1: 68 b4 ed a3 01               	push	0x1a3edb4
 111c5e6: 68 88 96 9d 01               	push	0x19d9688
 111c5eb: 6a 00                        	push	0x0
 111c5ed: 52                           	push	edx
 111c5ee: e8 ec b0 2b 00               	call	0x13d76df <.text+0x2bb30f>
 111c5f3: 83 c4 14                     	add	esp, 0x14
 111c5f6: 85 c0                        	test	eax, eax
 111c5f8: 75 13                        	jne	0x111c60d <.text+0x23d>
 111c5fa: 6a 00                        	push	0x0
 111c5fc: 8d 45 d4                     	lea	eax, [ebp - 0x2c]
 111c5ff: 50                           	push	eax
