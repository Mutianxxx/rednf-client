
<stdin>:	file format elf32-i386

Disassembly of section .text:

0111a320 <.text>:
 111a320: 55                           	push	ebp
 111a321: 8b ec                        	mov	ebp, esp
 111a323: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
 111a326: 56                           	push	esi
 111a327: 8b f1                        	mov	esi, ecx
 111a329: 88 86 f0 01 00 00            	mov	byte ptr [esi + 0x1f0], al
 111a32f: c7 86 18 01 00 00 00 00 00 00	mov	dword ptr [esi + 0x118], 0x0
 111a339: 84 c0                        	test	al, al
 111a33b: 0f 84 ac 01 00 00            	je	0x111a4ed <.text+0x1cd>
 111a341: 8b 86 9c 02 00 00            	mov	eax, dword ptr [esi + 0x29c]
 111a347: 8b 0d dc f6 a6 01            	mov	ecx, dword ptr [0x1a6f6dc]
 111a34d: 50                           	push	eax
 111a34e: e8 fd b7 01 00               	call	0x1135b50 <.text+0x1b830>
 111a353: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111a359: 85 c9                        	test	ecx, ecx
 111a35b: 74 1c                        	je	0x111a379 <.text+0x59>
 111a35d: 85 c0                        	test	eax, eax
 111a35f: 74 18                        	je	0x111a379 <.text+0x59>
 111a361: 83 78 5c 08                  	cmp	dword ptr [eax + 0x5c], 0x8
 111a365: 72 05                        	jb	0x111a36c <.text+0x4c>
 111a367: 8b 40 48                     	mov	eax, dword ptr [eax + 0x48]
 111a36a: eb 03                        	jmp	0x111a36f <.text+0x4f>
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
 111a384: e8 67 5b 08 00               	call	0x119fef0 <.text+0x85bd0>
 111a389: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a38f: 83 c4 04                     	add	esp, 0x4
 111a392: 50                           	push	eax
 111a393: e8 28 db f4 ff               	call	0x1067ec0
 111a398: 68 28 82 83 01               	push	0x1838228
 111a39d: e8 4e 5b 08 00               	call	0x119fef0 <.text+0x85bd0>
 111a3a2: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a3a8: 83 c4 04                     	add	esp, 0x4
 111a3ab: 50                           	push	eax
 111a3ac: e8 4f 97 f4 ff               	call	0x1063b00
 111a3b1: 68 e0 81 83 01               	push	0x18381e0
 111a3b6: 89 86 00 01 00 00            	mov	dword ptr [esi + 0x100], eax
 111a3bc: e8 2f 5b 08 00               	call	0x119fef0 <.text+0x85bd0>
 111a3c1: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a3c7: 83 c4 04                     	add	esp, 0x4
 111a3ca: 50                           	push	eax
 111a3cb: e8 30 97 f4 ff               	call	0x1063b00
 111a3d0: 68 9c 81 83 01               	push	0x183819c
 111a3d5: 89 86 04 01 00 00            	mov	dword ptr [esi + 0x104], eax
 111a3db: e8 10 5b 08 00               	call	0x119fef0 <.text+0x85bd0>
 111a3e0: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a3e6: 83 c4 04                     	add	esp, 0x4
 111a3e9: 50                           	push	eax
 111a3ea: e8 11 97 f4 ff               	call	0x1063b00
 111a3ef: 68 48 81 83 01               	push	0x1838148
 111a3f4: 8b d8                        	mov	ebx, eax
 111a3f6: e8 f5 5a 08 00               	call	0x119fef0 <.text+0x85bd0>
 111a3fb: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111a401: 83 c4 04                     	add	esp, 0x4
 111a404: 50                           	push	eax
 111a405: e8 d6 95 f4 ff               	call	0x10639e0
 111a40a: 68 00 81 83 01               	push	0x1838100
 111a40f: 89 86 10 01 00 00            	mov	dword ptr [esi + 0x110], eax
 111a415: e8 d6 5a 08 00               	call	0x119fef0 <.text+0x85bd0>
 111a41a: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a420: 83 c4 04                     	add	esp, 0x4
 111a423: 50                           	push	eax
 111a424: e8 b7 95 f4 ff               	call	0x10639e0
 111a429: 68 b0 80 83 01               	push	0x18380b0
 111a42e: 89 86 14 01 00 00            	mov	dword ptr [esi + 0x114], eax
 111a434: e8 b7 5a 08 00               	call	0x119fef0 <.text+0x85bd0>
 111a439: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a43f: 83 c4 04                     	add	esp, 0x4
 111a442: 50                           	push	eax
 111a443: e8 98 95 f4 ff               	call	0x10639e0
 111a448: 8b f8                        	mov	edi, eax
 111a44a: 85 ff                        	test	edi, edi
 111a44c: 74 1e                        	je	0x111a46c <.text+0x14c>
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
 111a46e: 74 16                        	je	0x111a486 <.text+0x166>
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
 111a48b: e8 60 5a 08 00               	call	0x119fef0 <.text+0x85bd0>
 111a490: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a496: 83 c4 04                     	add	esp, 0x4
 111a499: 50                           	push	eax
 111a49a: e8 61 96 f4 ff               	call	0x1063b00
 111a49f: 89 86 08 01 00 00            	mov	dword ptr [esi + 0x108], eax
 111a4a5: 8d be 00 01 00 00            	lea	edi, [esi + 0x100]
 111a4ab: bb 03 00 00 00               	mov	ebx, 0x3
 111a4b0: 8b 07                        	mov	eax, dword ptr [edi]
 111a4b2: 85 c0                        	test	eax, eax
 111a4b4: 75 0a                        	jne	0x111a4c0 <.text+0x1a0>
 111a4b6: 8b 86 f4 00 00 00            	mov	eax, dword ptr [esi + 0xf4]
 111a4bc: 85 c0                        	test	eax, eax
 111a4be: 74 20                        	je	0x111a4e0 <.text+0x1c0>
 111a4c0: 8b 0d 28 f7 a6 01            	mov	ecx, dword ptr [0x1a6f728]
 111a4c6: e8 a5 c0 80 ff               	call	0x926570
 111a4cb: 8b 0f                        	mov	ecx, dword ptr [edi]
 111a4cd: 85 c9                        	test	ecx, ecx
 111a4cf: 75 06                        	jne	0x111a4d7 <.text+0x1b7>
 111a4d1: 8b 8e f4 00 00 00            	mov	ecx, dword ptr [esi + 0xf4]
 111a4d7: 8b 11                        	mov	edx, dword ptr [ecx]
 111a4d9: 8b 42 18                     	mov	eax, dword ptr [edx + 0x18]
 111a4dc: 6a 00                        	push	0x0
 111a4de: ff d0                        	call	eax
 111a4e0: 83 c7 04                     	add	edi, 0x4
 111a4e3: 4b                           	dec	ebx
 111a4e4: 75 ca                        	jne	0x111a4b0 <.text+0x190>
 111a4e6: 5f                           	pop	edi
 111a4e7: 5b                           	pop	ebx
 111a4e8: 5e                           	pop	esi
 111a4e9: 5d                           	pop	ebp
 111a4ea: c2 04 00                     	ret	0x4
 111a4ed: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111a4f3: 8b 11                        	mov	edx, dword ptr [ecx]
 111a4f5: 8b 42 08                     	mov	eax, dword ptr [edx + 0x8]
 111a4f8: 6a 00                        	push	0x0
 111a4fa: ff d0                        	call	eax
 111a4fc: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111a502: e8 69 a4 f4 ff               	call	0x1064970
 111a507: 5e                           	pop	esi
 111a508: 5d                           	pop	ebp
 111a509: c2 04 00                     	ret	0x4
 111a50c: cc                           	int3
 111a50d: cc                           	int3
 111a50e: cc                           	int3
 111a50f: cc                           	int3
 111a510: 55                           	push	ebp
 111a511: 8b ec                        	mov	ebp, esp
 111a513: 81 ec 20 01 00 00            	sub	esp, 0x120
 111a519: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 111a51e: 33 c5                        	xor	eax, ebp
 111a520: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 111a523: 53                           	push	ebx
 111a524: 56                           	push	esi
 111a525: 57                           	push	edi
 111a526: 8d 99 74 03 00 00            	lea	ebx, [ecx + 0x374]
 111a52c: 8d 85 f0 fe ff ff            	lea	eax, [ebp - 0x110]
 111a532: 50                           	push	eax
 111a533: 8b cb                        	mov	ecx, ebx
 111a535: e8 36 bc 05 00               	call	0x1176170 <.text+0x5be50>
 111a53a: 8b b5 f8 fe ff ff            	mov	esi, dword ptr [ebp - 0x108]
