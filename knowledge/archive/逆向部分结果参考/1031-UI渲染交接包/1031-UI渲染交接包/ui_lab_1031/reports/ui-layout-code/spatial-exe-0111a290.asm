
<stdin>:	file format elf32-i386

Disassembly of section .text:

0111a290 <.text>:
 111a290: 00 00                        	add	byte ptr [eax], al
 111a292: b8 f7 12 da 4b               	mov	eax, 0x4bda12f7
 111a297: f7 ea                        	imul	edx
 111a299: c1 fa 05                     	sar	edx, 0x5
 111a29c: 8b c2                        	mov	eax, edx
 111a29e: c1 e8 1f                     	shr	eax, 0x1f
 111a2a1: 03 c2                        	add	eax, edx
 111a2a3: 74 14                        	je	0x111a2b9 <.text+0x29>
 111a2a5: 3b c7                        	cmp	eax, edi
 111a2a7: 72 10                        	jb	0x111a2b9 <.text+0x29>
 111a2a9: 83 ff 0f                     	cmp	edi, 0xf
 111a2ac: 77 0b                        	ja	0x111a2b9 <.text+0x29>
 111a2ae: 57                           	push	edi
 111a2af: e8 ec b9 a0 ff               	call	0xb25ca0
 111a2b4: 8b 58 04                     	mov	ebx, dword ptr [eax + 0x4]
 111a2b7: eb 02                        	jmp	0x111a2bb <.text+0x2b>
 111a2b9: 33 db                        	xor	ebx, ebx
 111a2bb: 8b be 44 02 00 00            	mov	edi, dword ptr [esi + 0x244]
 111a2c1: 83 ff ff                     	cmp	edi, -0x1
 111a2c4: 74 43                        	je	0x111a309 <.text+0x79>
 111a2c6: 8b 96 38 02 00 00            	mov	edx, dword ptr [esi + 0x238]
 111a2cc: 2b 96 34 02 00 00            	sub	edx, dword ptr [esi + 0x234]
 111a2d2: 8d 8e 30 02 00 00            	lea	ecx, [esi + 0x230]
 111a2d8: b8 f7 12 da 4b               	mov	eax, 0x4bda12f7
 111a2dd: f7 ea                        	imul	edx
 111a2df: c1 fa 05                     	sar	edx, 0x5
 111a2e2: 8b c2                        	mov	eax, edx
 111a2e4: c1 e8 1f                     	shr	eax, 0x1f
 111a2e7: 03 c2                        	add	eax, edx
 111a2e9: 74 1e                        	je	0x111a309 <.text+0x79>
 111a2eb: 3b c7                        	cmp	eax, edi
 111a2ed: 72 1a                        	jb	0x111a309 <.text+0x79>
 111a2ef: 83 ff 0f                     	cmp	edi, 0xf
 111a2f2: 77 15                        	ja	0x111a309 <.text+0x79>
 111a2f4: 57                           	push	edi
 111a2f5: e8 a6 b9 a0 ff               	call	0xb25ca0
 111a2fa: 8b 00                        	mov	eax, dword ptr [eax]
 111a2fc: 53                           	push	ebx
 111a2fd: 50                           	push	eax
 111a2fe: 8b ce                        	mov	ecx, esi
 111a300: e8 ab f8 ff ff               	call	0x1119bb0
 111a305: 5f                           	pop	edi
 111a306: 5e                           	pop	esi
 111a307: 5b                           	pop	ebx
 111a308: c3                           	ret
 111a309: 83 c8 ff                     	or	eax, -0x1
 111a30c: 53                           	push	ebx
 111a30d: 50                           	push	eax
 111a30e: 8b ce                        	mov	ecx, esi
 111a310: e8 9b f8 ff ff               	call	0x1119bb0
 111a315: 5f                           	pop	edi
 111a316: 5e                           	pop	esi
 111a317: 5b                           	pop	ebx
 111a318: c3                           	ret
 111a319: cc                           	int3
 111a31a: cc                           	int3
 111a31b: cc                           	int3
 111a31c: cc                           	int3
 111a31d: cc                           	int3
 111a31e: cc                           	int3
 111a31f: cc                           	int3
 111a320: 55                           	push	ebp
 111a321: 8b ec                        	mov	ebp, esp
 111a323: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
 111a326: 56                           	push	esi
 111a327: 8b f1                        	mov	esi, ecx
 111a329: 88 86 f0 01 00 00            	mov	byte ptr [esi + 0x1f0], al
 111a32f: c7 86 18 01 00 00 00 00 00 00	mov	dword ptr [esi + 0x118], 0x0
 111a339: 84 c0                        	test	al, al
 111a33b: 0f 84 ac 01 00 00            	je	0x111a4ed <.text+0x25d>
 111a341: 8b 86 9c 02 00 00            	mov	eax, dword ptr [esi + 0x29c]
 111a347: 8b 0d dc f6 a6 01            	mov	ecx, dword ptr [0x1a6f6dc]
 111a34d: 50                           	push	eax
 111a34e: e8 fd b7 01 00               	call	0x1135b50 <.text+0x1b8c0>
 111a353: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111a359: 85 c9                        	test	ecx, ecx
 111a35b: 74 1c                        	je	0x111a379 <.text+0xe9>
 111a35d: 85 c0                        	test	eax, eax
 111a35f: 74 18                        	je	0x111a379 <.text+0xe9>
 111a361: 83 78 5c 08                  	cmp	dword ptr [eax + 0x5c], 0x8
 111a365: 72 05                        	jb	0x111a36c <.text+0xdc>
 111a367: 8b 40 48                     	mov	eax, dword ptr [eax + 0x48]
 111a36a: eb 03                        	jmp	0x111a36f <.text+0xdf>
 111a36c: 83 c0 48                     	add	eax, 0x48
 111a36f: 6a 00                        	push	0x0
 111a371: 6a 00                        	push	0x0
 111a373: 50                           	push	eax
 111a374: e8 47 db f4 ff               	call	0x1067ec0
 111a379: 53                           	push	ebx
 111a37a: 57                           	push	edi
 111a37b: 6a 00                        	push	0x0
 111a37d: 6a 00                        	push	0x0
 111a37f: 68 70 82 83 01               	push	0x1838270
 111a384: e8 67 5b 08 00               	call	0x119fef0 <.text+0x85c60>
 111a389: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a38f: 83 c4 04                     	add	esp, 0x4
 111a392: 50                           	push	eax
 111a393: e8 28 db f4 ff               	call	0x1067ec0
 111a398: 68 28 82 83 01               	push	0x1838228
 111a39d: e8 4e 5b 08 00               	call	0x119fef0 <.text+0x85c60>
 111a3a2: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a3a8: 83 c4 04                     	add	esp, 0x4
 111a3ab: 50                           	push	eax
 111a3ac: e8 4f 97 f4 ff               	call	0x1063b00
 111a3b1: 68 e0 81 83 01               	push	0x18381e0
 111a3b6: 89 86 00 01 00 00            	mov	dword ptr [esi + 0x100], eax
 111a3bc: e8 2f 5b 08 00               	call	0x119fef0 <.text+0x85c60>
 111a3c1: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a3c7: 83 c4 04                     	add	esp, 0x4
 111a3ca: 50                           	push	eax
 111a3cb: e8 30 97 f4 ff               	call	0x1063b00
 111a3d0: 68 9c 81 83 01               	push	0x183819c
 111a3d5: 89 86 04 01 00 00            	mov	dword ptr [esi + 0x104], eax
 111a3db: e8 10 5b 08 00               	call	0x119fef0 <.text+0x85c60>
 111a3e0: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a3e6: 83 c4 04                     	add	esp, 0x4
 111a3e9: 50                           	push	eax
 111a3ea: e8 11 97 f4 ff               	call	0x1063b00
 111a3ef: 68 48 81 83 01               	push	0x1838148
 111a3f4: 8b d8                        	mov	ebx, eax
 111a3f6: e8 f5 5a 08 00               	call	0x119fef0 <.text+0x85c60>
 111a3fb: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111a401: 83 c4 04                     	add	esp, 0x4
 111a404: 50                           	push	eax
 111a405: e8 d6 95 f4 ff               	call	0x10639e0
 111a40a: 68 00 81 83 01               	push	0x1838100
 111a40f: 89 86 10 01 00 00            	mov	dword ptr [esi + 0x110], eax
 111a415: e8 d6 5a 08 00               	call	0x119fef0 <.text+0x85c60>
 111a41a: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a420: 83 c4 04                     	add	esp, 0x4
 111a423: 50                           	push	eax
 111a424: e8 b7 95 f4 ff               	call	0x10639e0
 111a429: 68 b0 80 83 01               	push	0x18380b0
 111a42e: 89 86 14 01 00 00            	mov	dword ptr [esi + 0x114], eax
 111a434: e8 b7 5a 08 00               	call	0x119fef0 <.text+0x85c60>
 111a439: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a43f: 83 c4 04                     	add	esp, 0x4
 111a442: 50                           	push	eax
 111a443: e8 98 95 f4 ff               	call	0x10639e0
 111a448: 8b f8                        	mov	edi, eax
 111a44a: 85 ff                        	test	edi, edi
 111a44c: 74 1e                        	je	0x111a46c <.text+0x1dc>
 111a44e: 8b 07                        	mov	eax, dword ptr [edi]
 111a450: 83 c0 10                     	add	eax, 0x10
 111a453: 6a ff                        	push	-0x1
 111a455: 8b ce                        	mov	ecx, esi
 111a457: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 111a45a: e8 11 fc ff ff               	call	0x111a070
 111a45f: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 111a462: 0f b6 c8                     	movzx	ecx, al
 111a465: 8b 02                        	mov	eax, dword ptr [edx]
 111a467: 51                           	push	ecx
 111a468: 8b cf                        	mov	ecx, edi
 111a46a: ff d0                        	call	eax
 111a46c: 85 db                        	test	ebx, ebx
 111a46e: 74 16                        	je	0x111a486 <.text+0x1f6>
 111a470: 8b 13                        	mov	edx, dword ptr [ebx]
 111a472: 8b 42 18                     	mov	eax, dword ptr [edx + 0x18]
 111a475: 6a 00                        	push	0x0
 111a477: 8b cb                        	mov	ecx, ebx
 111a479: ff d0                        	call	eax
 111a47b: 8b 13                        	mov	edx, dword ptr [ebx]
 111a47d: 8b 42 10                     	mov	eax, dword ptr [edx + 0x10]
 111a480: 6a 00                        	push	0x0
 111a482: 8b cb                        	mov	ecx, ebx
 111a484: ff d0                        	call	eax
 111a486: 68 68 80 83 01               	push	0x1838068
 111a48b: e8 60 5a 08 00               	call	0x119fef0 <.text+0x85c60>
 111a490: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a496: 83 c4 04                     	add	esp, 0x4
 111a499: 50                           	push	eax
 111a49a: e8 61 96 f4 ff               	call	0x1063b00
 111a49f: 89 86 08 01 00 00            	mov	dword ptr [esi + 0x108], eax
 111a4a5: 8d be 00 01 00 00            	lea	edi, [esi + 0x100]
 111a4ab: bb 03 00 00 00               	mov	ebx, 0x3
