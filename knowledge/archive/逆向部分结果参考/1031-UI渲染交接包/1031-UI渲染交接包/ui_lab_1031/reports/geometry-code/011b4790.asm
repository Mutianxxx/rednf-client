
<stdin>:	file format elf32-i386

Disassembly of section .text:

011b4790 <.text>:
 11b4790: 53                           	push	ebx
 11b4791: 33 db                        	xor	ebx, ebx
 11b4793: 56                           	push	esi
 11b4794: 8b f1                        	mov	esi, ecx
 11b4796: 33 d2                        	xor	edx, edx
 11b4798: 89 5e 14                     	mov	dword ptr [esi + 0x14], ebx
 11b479b: 89 5e 48                     	mov	dword ptr [esi + 0x48], ebx
 11b479e: 83 66 44 fe                  	and	dword ptr [esi + 0x44], -0x2
 11b47a2: 89 56 20                     	mov	dword ptr [esi + 0x20], edx
 11b47a5: 33 c0                        	xor	eax, eax
 11b47a7: 33 c9                        	xor	ecx, ecx
 11b47a9: 89 46 1c                     	mov	dword ptr [esi + 0x1c], eax
 11b47ac: 89 4e 24                     	mov	dword ptr [esi + 0x24], ecx
 11b47af: c7 46 18 00 00 01 00         	mov	dword ptr [esi + 0x18], 0x10000
 11b47b6: 89 5e 4c                     	mov	dword ptr [esi + 0x4c], ebx
 11b47b9: 66 0f ef c0                  	pxor	xmm0, xmm0
 11b47bd: 66 0f d6 46 28               	movq	qword ptr [esi + 0x28], xmm0
 11b47c2: 8a 56 58                     	mov	dl, byte ptr [esi + 0x58]
 11b47c5: 80 e2 f2                     	and	dl, -0xe
 11b47c8: 89 5e 50                     	mov	dword ptr [esi + 0x50], ebx
 11b47cb: 80 ca 02                     	or	dl, 0x2
 11b47ce: 88 5e 50                     	mov	byte ptr [esi + 0x50], bl
 11b47d1: 81 4e 50 00 03 00 00         	or	dword ptr [esi + 0x50], 0x300
 11b47d8: 88 56 58                     	mov	byte ptr [esi + 0x58], dl
 11b47db: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11b47e1: 89 46 54                     	mov	dword ptr [esi + 0x54], eax
 11b47e4: 8a 46 58                     	mov	al, byte ptr [esi + 0x58]
 11b47e7: 24 f0                        	and	al, -0x10
 11b47e9: 0c 10                        	or	al, 0x10
 11b47eb: 88 5e 40                     	mov	byte ptr [esi + 0x40], bl
 11b47ee: 88 46 58                     	mov	byte ptr [esi + 0x58], al
 11b47f1: 5e                           	pop	esi
 11b47f2: 5b                           	pop	ebx
 11b47f3: c3                           	ret
 11b47f4: cc                           	int3
 11b47f5: cc                           	int3
 11b47f6: cc                           	int3
 11b47f7: cc                           	int3
 11b47f8: cc                           	int3
 11b47f9: cc                           	int3
 11b47fa: cc                           	int3
 11b47fb: cc                           	int3
 11b47fc: cc                           	int3
 11b47fd: cc                           	int3
 11b47fe: cc                           	int3
 11b47ff: cc                           	int3
 11b4800: 55                           	push	ebp
 11b4801: 8b ec                        	mov	ebp, esp
 11b4803: 56                           	push	esi
 11b4804: 8b f1                        	mov	esi, ecx
 11b4806: e8 35 7c 01 00               	call	0x11cc440 <.text+0x17cb0>
 11b480b: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b480e: c7 06 0c 9e 85 01            	mov	dword ptr [esi], 0x1859e0c
 11b4814: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
 11b4817: 8b ce                        	mov	ecx, esi
 11b4819: c7 46 44 00 00 00 00         	mov	dword ptr [esi + 0x44], 0x0
 11b4820: e8 6b ff ff ff               	call	0x11b4790 <.text>
 11b4825: 8b c6                        	mov	eax, esi
 11b4827: 5e                           	pop	esi
 11b4828: 5d                           	pop	ebp
 11b4829: c2 04 00                     	ret	0x4
 11b482c: cc                           	int3
 11b482d: cc                           	int3
 11b482e: cc                           	int3
 11b482f: cc                           	int3
 11b4830: 55                           	push	ebp
 11b4831: 8b ec                        	mov	ebp, esp
 11b4833: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b4836: a3 74 58 b5 01               	mov	dword ptr [0x1b55874], eax
 11b483b: 5d                           	pop	ebp
 11b483c: c3                           	ret
 11b483d: cc                           	int3
 11b483e: cc                           	int3
 11b483f: cc                           	int3
 11b4840: 55                           	push	ebp
 11b4841: 8b ec                        	mov	ebp, esp
 11b4843: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b4846: a3 70 58 b5 01               	mov	dword ptr [0x1b55870], eax
 11b484b: 5d                           	pop	ebp
 11b484c: c3                           	ret
 11b484d: cc                           	int3
 11b484e: cc                           	int3
 11b484f: cc                           	int3
 11b4850: 8d 81 a4 00 00 00            	lea	eax, [ecx + 0xa4]
 11b4856: c3                           	ret
 11b4857: cc                           	int3
 11b4858: cc                           	int3
 11b4859: cc                           	int3
 11b485a: cc                           	int3
 11b485b: cc                           	int3
 11b485c: cc                           	int3
 11b485d: cc                           	int3
 11b485e: cc                           	int3
 11b485f: cc                           	int3
 11b4860: 55                           	push	ebp
 11b4861: 8b ec                        	mov	ebp, esp
 11b4863: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11b4866: 57                           	push	edi
 11b4867: 8b f9                        	mov	edi, ecx
 11b4869: 8b 4f 58                     	mov	ecx, dword ptr [edi + 0x58]
 11b486c: 8b 57 5c                     	mov	edx, dword ptr [edi + 0x5c]
 11b486f: 2b d1                        	sub	edx, ecx
 11b4871: c1 fa 04                     	sar	edx, 0x4
 11b4874: 3b c2                        	cmp	eax, edx
 11b4876: 73 36                        	jae	0x11b48ae <.text+0x11e>
 11b4878: 03 c0                        	add	eax, eax
 11b487a: 56                           	push	esi
 11b487b: 8b 34 c1                     	mov	esi, dword ptr [ecx + 8*eax]
 11b487e: 85 f6                        	test	esi, esi
 11b4880: 74 2b                        	je	0x11b48ad <.text+0x11d>
 11b4882: 8b 06                        	mov	eax, dword ptr [esi]
 11b4884: 8b 90 9c 00 00 00            	mov	edx, dword ptr [eax + 0x9c]
 11b488a: 8b ce                        	mov	ecx, esi
 11b488c: ff d2                        	call	edx
 11b488e: 84 c0                        	test	al, al
 11b4890: 74 0c                        	je	0x11b489e <.text+0x10e>
 11b4892: 8b 06                        	mov	eax, dword ptr [esi]
 11b4894: 8b 90 94 00 00 00            	mov	edx, dword ptr [eax + 0x94]
 11b489a: 8b ce                        	mov	ecx, esi
 11b489c: ff d2                        	call	edx
 11b489e: 6a 00                        	push	0x0
 11b48a0: 8b ce                        	mov	ecx, esi
 11b48a2: e8 09 f0 ff ff               	call	0x11b38b0
 11b48a7: ff 87 94 00 00 00            	inc	dword ptr [edi + 0x94]
 11b48ad: 5e                           	pop	esi
 11b48ae: 5f                           	pop	edi
 11b48af: 5d                           	pop	ebp
 11b48b0: c2 04 00                     	ret	0x4
 11b48b3: cc                           	int3
 11b48b4: cc                           	int3
 11b48b5: cc                           	int3
 11b48b6: cc                           	int3
 11b48b7: cc                           	int3
 11b48b8: cc                           	int3
 11b48b9: cc                           	int3
 11b48ba: cc                           	int3
 11b48bb: cc                           	int3
 11b48bc: cc                           	int3
 11b48bd: cc                           	int3
 11b48be: cc                           	int3
 11b48bf: cc                           	int3
 11b48c0: 53                           	push	ebx
 11b48c1: 56                           	push	esi
 11b48c2: 6a 01                        	push	0x1
 11b48c4: 8b f1                        	mov	esi, ecx
 11b48c6: e8 05 53 00 00               	call	0x11b9bd0 <.text+0x5440>
 11b48cb: 8b 4e 58                     	mov	ecx, dword ptr [esi + 0x58]
 11b48ce: 8b 46 5c                     	mov	eax, dword ptr [esi + 0x5c]
 11b48d1: 2b c1                        	sub	eax, ecx
 11b48d3: c1 f8 04                     	sar	eax, 0x4
 11b48d6: 83 c4 04                     	add	esp, 0x4
 11b48d9: 33 db                        	xor	ebx, ebx
 11b48db: 85 c0                        	test	eax, eax
 11b48dd: 0f 84 c0 00 00 00            	je	0x11b49a3 <.text+0x213>
 11b48e3: 57                           	push	edi
 11b48e4: 33 ff                        	xor	edi, edi
 11b48e6: 3b d8                        	cmp	ebx, eax
 11b48e8: 0f 83 c4 00 00 00            	jae	0x11b49b2 <.text+0x222>
 11b48ee: a1                           	<unknown>
 11b48ef: 6c                           	insb	byte ptr es:[edi], dx
