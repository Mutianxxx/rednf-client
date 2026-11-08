
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c46a0 <.text>:
 11c46a0: 55                           	push	ebp
 11c46a1: 8b ec                        	mov	ebp, esp
 11c46a3: 6a ff                        	push	-0x1
 11c46a5: 68 b8 c2 4c 01               	push	0x14cc2b8
 11c46aa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c46b0: 50                           	push	eax
 11c46b1: 83 ec 44                     	sub	esp, 0x44
 11c46b4: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c46b9: 33 c5                        	xor	eax, ebp
 11c46bb: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 11c46be: 53                           	push	ebx
 11c46bf: 56                           	push	esi
 11c46c0: 57                           	push	edi
 11c46c1: 50                           	push	eax
 11c46c2: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c46c5: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c46cb: a1 e4 64 b5 01               	mov	eax, dword ptr [0x1b564e4]
 11c46d0: 8b 38                        	mov	edi, dword ptr [eax]
 11c46d2: 68 d8 50 56 01               	push	0x15650d8
 11c46d7: 8b f1                        	mov	esi, ecx
 11c46d9: e8 12 b8 fd ff               	call	0x119fef0
 11c46de: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
 11c46e4: 8b 57 10                     	mov	edx, dword ptr [edi + 0x10]
 11c46e7: 83 c4 04                     	add	esp, 0x4
 11c46ea: 50                           	push	eax
 11c46eb: ff d2                        	call	edx
 11c46ed: 89 86 50 03 00 00            	mov	dword ptr [esi + 0x350], eax
 11c46f3: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 11c46f6: 50                           	push	eax
 11c46f7: 8b ce                        	mov	ecx, esi
 11c46f9: e8 42 fd ff ff               	call	0x11c4440
 11c46fe: 8b 40 14                     	mov	eax, dword ptr [eax + 0x14]
 11c4701: bf 08 00 00 00               	mov	edi, 0x8
 11c4706: 3b c7                        	cmp	eax, edi
 11c4708: 0f 97 c3                     	seta	bl
 11c470b: 39 7d e8                     	cmp	dword ptr [ebp - 0x18], edi
 11c470e: 72 0c                        	jb	0x11c471c <.text+0x7c>
 11c4710: 8b 4d d4                     	mov	ecx, dword ptr [ebp - 0x2c]
 11c4713: 51                           	push	ecx
 11c4714: e8 0e 14 21 00               	call	0x13d5b27 <.text+0x211487>
 11c4719: 83 c4 04                     	add	esp, 0x4
 11c471c: 8b 45 d0                     	mov	eax, dword ptr [ebp - 0x30]
 11c471f: 33 d2                        	xor	edx, edx
 11c4721: 50                           	push	eax
 11c4722: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 11c4729: c7 45 e4 00 00 00 00         	mov	dword ptr [ebp - 0x1c], 0x0
 11c4730: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
 11c4734: e8 ee 13 21 00               	call	0x13d5b27 <.text+0x211487>
 11c4739: 83 c4 04                     	add	esp, 0x4
 11c473c: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11c473f: 51                           	push	ecx
 11c4740: 8b ce                        	mov	ecx, esi
 11c4742: e8 f9 fc ff ff               	call	0x11c4440
 11c4747: 84 db                        	test	bl, bl
 11c4749: 74 65                        	je	0x11c47b0 <.text+0x110>
 11c474b: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11c4752: 39 78 18                     	cmp	dword ptr [eax + 0x18], edi
 11c4755: 72 05                        	jb	0x11c475c <.text+0xbc>
 11c4757: 8b 40 04                     	mov	eax, dword ptr [eax + 0x4]
 11c475a: eb 03                        	jmp	0x11c475f <.text+0xbf>
 11c475c: 83 c0 04                     	add	eax, 0x4
 11c475f: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c4765: 8b 11                        	mov	edx, dword ptr [ecx]
 11c4767: 6a ff                        	push	-0x1
 11c4769: 50                           	push	eax
 11c476a: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c476d: ff d0                        	call	eax
 11c476f: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 11c4773: 8d 78 1c                     	lea	edi, [eax + 0x1c]
 11c4776: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11c477d: 72 0c                        	jb	0x11c478b <.text+0xeb>
 11c477f: 8b 4d d4                     	mov	ecx, dword ptr [ebp - 0x2c]
 11c4782: 51                           	push	ecx
 11c4783: e8 9f 13 21 00               	call	0x13d5b27 <.text+0x211487>
 11c4788: 83 c4 04                     	add	esp, 0x4
 11c478b: 8b 45 d0                     	mov	eax, dword ptr [ebp - 0x30]
 11c478e: 33 d2                        	xor	edx, edx
 11c4790: 50                           	push	eax
 11c4791: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 11c4798: c7 45 e4 00 00 00 00         	mov	dword ptr [ebp - 0x1c], 0x0
 11c479f: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
 11c47a3: e8 7f 13 21 00               	call	0x13d5b27 <.text+0x211487>
 11c47a8: 83 c4 04                     	add	esp, 0x4
 11c47ab: e9 a2 00 00 00               	jmp	0x11c4852 <.text+0x1b2>
 11c47b0: 83 78 14 06                  	cmp	dword ptr [eax + 0x14], 0x6
 11c47b4: 0f 97 c3                     	seta	bl
 11c47b7: 39 7d e8                     	cmp	dword ptr [ebp - 0x18], edi
 11c47ba: 72 0c                        	jb	0x11c47c8 <.text+0x128>
 11c47bc: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
 11c47bf: 52                           	push	edx
 11c47c0: e8 62 13 21 00               	call	0x13d5b27 <.text+0x211487>
 11c47c5: 83 c4 04                     	add	esp, 0x4
 11c47c8: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
 11c47cb: 33 c0                        	xor	eax, eax
 11c47cd: 51                           	push	ecx
 11c47ce: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 11c47d5: c7 45 e4 00 00 00 00         	mov	dword ptr [ebp - 0x1c], 0x0
 11c47dc: 66 89 45 d4                  	mov	word ptr [ebp - 0x2c], ax
 11c47e0: e8 42 13 21 00               	call	0x13d5b27 <.text+0x211487>
 11c47e5: 83 c4 04                     	add	esp, 0x4
 11c47e8: 84 db                        	test	bl, bl
 11c47ea: 74 04                        	je	0x11c47f0 <.text+0x150>
 11c47ec: 6a 42                        	push	0x42
 11c47ee: eb 4e                        	jmp	0x11c483e <.text+0x19e>
 11c47f0: 8d 55 b0                     	lea	edx, [ebp - 0x50]
 11c47f3: 52                           	push	edx
 11c47f4: 8b ce                        	mov	ecx, esi
 11c47f6: e8 45 fc ff ff               	call	0x11c4440
 11c47fb: 83 78 14 04                  	cmp	dword ptr [eax + 0x14], 0x4
 11c47ff: 0f 97 c3                     	seta	bl
 11c4802: 39 7d c8                     	cmp	dword ptr [ebp - 0x38], edi
 11c4805: 72 0c                        	jb	0x11c4813 <.text+0x173>
 11c4807: 8b 45 b4                     	mov	eax, dword ptr [ebp - 0x4c]
 11c480a: 50                           	push	eax
 11c480b: e8 17 13 21 00               	call	0x13d5b27 <.text+0x211487>
 11c4810: 83 c4 04                     	add	esp, 0x4
 11c4813: 8b 55 b0                     	mov	edx, dword ptr [ebp - 0x50]
 11c4816: 33 c9                        	xor	ecx, ecx
 11c4818: 33 ff                        	xor	edi, edi
 11c481a: 52                           	push	edx
 11c481b: c7 45 c8 07 00 00 00         	mov	dword ptr [ebp - 0x38], 0x7
 11c4822: 89 7d c4                     	mov	dword ptr [ebp - 0x3c], edi
 11c4825: 66 89 4d b4                  	mov	word ptr [ebp - 0x4c], cx
 11c4829: e8 f9 12 21 00               	call	0x13d5b27 <.text+0x211487>
 11c482e: 83 c4 04                     	add	esp, 0x4
 11c4831: 89 7d b0                     	mov	dword ptr [ebp - 0x50], edi
 11c4834: 84 db                        	test	bl, bl
 11c4836: 74 04                        	je	0x11c483c <.text+0x19c>
 11c4838: 6a 5a                        	push	0x5a
 11c483a: eb 02                        	jmp	0x11c483e <.text+0x19e>
 11c483c: 6a 0c                        	push	0xc
 11c483e: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c4844: e8 87 03 ff ff               	call	0x11b4bd0
 11c4849: 8b c8                        	mov	ecx, eax
 11c484b: e8 30 f5 fe ff               	call	0x11b3d80
 11c4850: 8b f8                        	mov	edi, eax
 11c4852: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c4858: 68 af 00 00 00               	push	0xaf
 11c485d: 89 7e 38                     	mov	dword ptr [esi + 0x38], edi
 11c4860: e8 6b 03 ff ff               	call	0x11b4bd0
 11c4865: 8b c8                        	mov	ecx, eax
 11c4867: e8 64 f5 fe ff               	call	0x11b3dd0
 11c486c: 89 46 3c                     	mov	dword ptr [esi + 0x3c], eax
 11c486f: 83 3d e8 64 b5 01 00         	cmp	dword ptr [0x1b564e8], 0x0
 11c4876: 75 37                        	jne	0x11c48af <.text+0x20f>
 11c4878: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c487e: 68 af 00 00 00               	push	0xaf
 11c4883: e8 48 03 ff ff               	call	0x11b4bd0
 11c4888: 8b c8                        	mov	ecx, eax
 11c488a: e8 31 f5 fe ff               	call	0x11b3dc0
 11c488f: 8b 8e 50 03 00 00            	mov	ecx, dword ptr [esi + 0x350]
 11c4895: 68 b1 00 00 00               	push	0xb1
 11c489a: 8b d8                        	mov	ebx, eax
 11c489c: e8 2f 03 ff ff               	call	0x11b4bd0
 11c48a1: 8b c8                        	mov	ecx, eax
 11c48a3: e8 18 f5 fe ff               	call	0x11b3dc0
 11c48a8: 03 c3                        	add	eax, ebx
 11c48aa: a3 e8 64 b5 01               	mov	dword ptr [0x1b564e8], eax
 11c48af: 85 ff                        	test	edi, edi
 11c48b1: 74 06                        	je	0x11c48b9 <.text+0x219>
 11c48b3: 89 be 4c 03 00 00            	mov	dword ptr [esi + 0x34c], edi
 11c48b9: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c48bc: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11c48c3: 59                           	pop	ecx
 11c48c4: 5f                           	pop	edi
 11c48c5: 5e                           	pop	esi
 11c48c6: 5b                           	pop	ebx
 11c48c7: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 11c48ca: 33 cd                        	xor	ecx, ebp
 11c48cc: e8 07 29 21 00               	call	0x13d71d8 <.text+0x212b38>
 11c48d1: 8b e5                        	mov	esp, ebp
 11c48d3: 5d                           	pop	ebp
 11c48d4: c3                           	ret
 11c48d5: cc                           	int3
 11c48d6: cc                           	int3
 11c48d7: cc                           	int3
 11c48d8: cc                           	int3
 11c48d9: cc                           	int3
 11c48da: cc                           	int3
 11c48db: cc                           	int3
 11c48dc: cc                           	int3
 11c48dd: cc                           	int3
 11c48de: cc                           	int3
 11c48df: cc                           	int3
 11c48e0: 55                           	push	ebp
 11c48e1: 8b ec                        	mov	ebp, esp
 11c48e3: 6a ff                        	push	-0x1
 11c48e5: 68 70 f7 4a 01               	push	0x14af770
 11c48ea: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11c48f0: 50                           	push	eax
 11c48f1: 83 ec 14                     	sub	esp, 0x14
 11c48f4: 53                           	push	ebx
 11c48f5: 56                           	push	esi
 11c48f6: 57                           	push	edi
 11c48f7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11c48fc: 33 c5                        	xor	eax, ebp
 11c48fe: 50                           	push	eax
 11c48ff: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11c4902: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11c4908: 8b f9                        	mov	edi, ecx
 11c490a: 68 8c 8c 8c ff               	push	0xff8c8c8c
 11c490f: 68 ff ff b8 ff               	push	0xffb8ffff
 11c4914: 68 ff ff b8 ff               	push	0xffb8ffff
 11c4919: 68 dd c5 93 ff               	push	0xff93c5dd
 11c491e: 83 ec 20                     	sub	esp, 0x20
 11c4921: 8b f4                        	mov	esi, esp
 11c4923: 33 db                        	xor	ebx, ebx
 11c4925: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
 11c4928: 6a 08                        	push	0x8
 11c492a: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 11c492d: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
 11c4930: 89 1e                        	mov	dword ptr [esi], ebx
 11c4932: e8 e3 21 21 00               	call	0x13d6b1a <.text+0x21247a>
 11c4937: 83 c4 04                     	add	esp, 0x4
 11c493a: 3b c3                        	cmp	eax, ebx
 11c493c: 0f 84 80 00 00 00            	je	0x11c49c2 <.text+0x322>
 11c4942: 89 06                        	mov	dword ptr [esi], eax
 11c4944: 33 c9                        	xor	ecx, ecx
 11c4946: 33 d2                        	xor	edx, edx
 11c4948: 89 08                        	mov	dword ptr [eax], ecx
 11c494a: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 11c494d: 8b 06                        	mov	eax, dword ptr [esi]
 11c494f: 89 30                        	mov	dword ptr [eax], esi
 11c4951: 6a ff                        	push	-0x1
 11c4953: c7 46 18 07 00 00 00         	mov	dword ptr [esi + 0x18], 0x7
 11c495a: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11c495d: 53                           	push	ebx
 11c495e: 8d 55 08                     	lea	edx, [ebp + 0x8]
 11c4961: 66 89 4e 04                  	mov	word ptr [esi + 0x4], cx
 11c4965: 52                           	push	edx
 11c4966: 8b ce                        	mov	ecx, esi
 11c4968: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 11c496c: e8 bf 09 24 ff               	call	0x405330
 11c4971: 8b 07                        	mov	eax, dword ptr [edi]
 11c4973: 8b 90 b4 00 00 00            	mov	edx, dword ptr [eax + 0xb4]
 11c4979: 8b cf                        	mov	ecx, edi
 11c497b: 88 5d fc                     	mov	byte ptr [ebp - 0x4], bl
 11c497e: ff d2                        	call	edx
 11c4980: 83 7d 20 08                  	cmp	dword ptr [ebp + 0x20], 0x8
 11c4984: 72 0c                        	jb	0x11c4992 <.text+0x2f2>
 11c4986: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c4989: 50                           	push	eax
 11c498a: e8 98 11 21 00               	call	0x13d5b27 <.text+0x211487>
 11c498f: 83 c4 04                     	add	esp, 0x4
 11c4992: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11c4995: 33 c9                        	xor	ecx, ecx
 11c4997: 52                           	push	edx
 11c4998: c7 45 20 07 00 00 00         	mov	dword ptr [ebp + 0x20], 0x7
 11c499f: 89 5d 1c                     	mov	dword ptr [ebp + 0x1c], ebx
 11c49a2: 66 89 4d 0c                  	mov	word ptr [ebp + 0xc], cx
 11c49a6: e8 7c 11 21 00               	call	0x13d5b27 <.text+0x211487>
 11c49ab: 83 c4 04                     	add	esp, 0x4
 11c49ae: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11c49b1: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11c49b8: 59                           	pop	ecx
 11c49b9: 5f                           	pop	edi
 11c49ba: 5e                           	pop	esi
 11c49bb: 5b                           	pop	ebx
 11c49bc: 8b e5                        	mov	esp, ebp
 11c49be: 5d                           	pop	ebp
 11c49bf: c2 20 00                     	ret	0x20
 11c49c2: 8d 45 f0                     	lea	eax, [ebp - 0x10]
 11c49c5: 50                           	push	eax
 11c49c6: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
 11c49c9: 89 5d f0                     	mov	dword ptr [ebp - 0x10], ebx
 11c49cc: e8 f9 1a 21 00               	call	0x13d64ca <.text+0x211e2a>
 11c49d1: 68 90 0f 91 01               	push	0x1910f90
 11c49d6: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
 11c49d9: 51                           	push	ecx
 11c49da: c7 45 e0 84 20 56 01         	mov	dword ptr [ebp - 0x20], 0x1562084
 11c49e1: e8 b4 21 21 00               	call	0x13d6b9a <.text+0x2124fa>
 11c49e6: cc                           	int3
 11c49e7: cc                           	int3
