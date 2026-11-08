
<stdin>:	file format elf32-i386

Disassembly of section .text:

011374f0 <.text>:
 11374f0: 90                           	nop
 11374f1: 0f 91 01                     	setno	byte ptr [ecx]
 11374f4: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 11374f7: 52                           	push	edx
 11374f8: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 11374ff: e8 96 f6 29 00               	call	0x13d6b9a <.text+0x29f6aa>
 1137504: cc                           	int3
 1137505: cc                           	int3
 1137506: cc                           	int3
 1137507: cc                           	int3
 1137508: cc                           	int3
 1137509: cc                           	int3
 113750a: cc                           	int3
 113750b: cc                           	int3
 113750c: cc                           	int3
 113750d: cc                           	int3
 113750e: cc                           	int3
 113750f: cc                           	int3
 1137510: 56                           	push	esi
 1137511: 57                           	push	edi
 1137512: 8b f1                        	mov	esi, ecx
 1137514: 68 78 21 56 01               	push	0x1562178
 1137519: c7 06 00 00 00 00            	mov	dword ptr [esi], 0x0
 113751f: e8 cc 89 06 00               	call	0x119fef0 <.text+0x68a00>
 1137524: 8b c8                        	mov	ecx, eax
 1137526: 83 c4 04                     	add	esp, 0x4
 1137529: 8d 79 02                     	lea	edi, [ecx + 0x2]
 113752c: 8d 64 24 00                  	lea	esp, [esp]
 1137530: 66 8b 11                     	mov	dx, word ptr [ecx]
 1137533: 83 c1 02                     	add	ecx, 0x2
 1137536: 66 85 d2                     	test	dx, dx
 1137539: 75 f5                        	jne	0x1137530 <.text+0x40>
 113753b: 2b cf                        	sub	ecx, edi
 113753d: d1 f9                        	sar	ecx
 113753f: 51                           	push	ecx
 1137540: 50                           	push	eax
 1137541: 8d 4e 04                     	lea	ecx, [esi + 0x4]
 1137544: e8 e7 8a 2d ff               	call	0x410030
 1137549: 68 78 21 56 01               	push	0x1562178
 113754e: e8 9d 89 06 00               	call	0x119fef0 <.text+0x68a00>
 1137553: 8b c8                        	mov	ecx, eax
 1137555: 83 c4 04                     	add	esp, 0x4
 1137558: 8d 79 02                     	lea	edi, [ecx + 0x2]
 113755b: eb 03                        	jmp	0x1137560 <.text+0x70>
 113755d: 8d 49 00                     	lea	ecx, [ecx]
 1137560: 66 8b 11                     	mov	dx, word ptr [ecx]
 1137563: 83 c1 02                     	add	ecx, 0x2
 1137566: 66 85 d2                     	test	dx, dx
 1137569: 75 f5                        	jne	0x1137560 <.text+0x70>
 113756b: 2b cf                        	sub	ecx, edi
 113756d: d1 f9                        	sar	ecx
 113756f: 51                           	push	ecx
 1137570: 50                           	push	eax
 1137571: 8d 4e 24                     	lea	ecx, [esi + 0x24]
 1137574: e8 b7 8a 2d ff               	call	0x410030
 1137579: 8d 4e 68                     	lea	ecx, [esi + 0x68]
 113757c: c7 46 64 00 00 00 00         	mov	dword ptr [esi + 0x64], 0x0
 1137583: e8 88 ff 60 ff               	call	0x747510
 1137588: 8d 8e 80 00 00 00            	lea	ecx, [esi + 0x80]
 113758e: c6 46 7c 00                  	mov	byte ptr [esi + 0x7c], 0x0
 1137592: e8 b9 1f 25 00               	call	0x1389550 <.text+0x252060>
 1137597: 8d 8e 94 00 00 00            	lea	ecx, [esi + 0x94]
 113759d: e8 3e 4c 19 00               	call	0x12cc1e0 <.text+0x194cf0>
 11375a2: 8d 8e a8 00 00 00            	lea	ecx, [esi + 0xa8]
 11375a8: e8 a3 1f 25 00               	call	0x1389550 <.text+0x252060>
 11375ad: 5f                           	pop	edi
 11375ae: 8d 8e bc 00 00 00            	lea	ecx, [esi + 0xbc]
 11375b4: 5e                           	pop	esi
 11375b5: e9 26 4c 19 00               	jmp	0x12cc1e0 <.text+0x194cf0>
 11375ba: cc                           	int3
 11375bb: cc                           	int3
 11375bc: cc                           	int3
 11375bd: cc                           	int3
 11375be: cc                           	int3
 11375bf: cc                           	int3
 11375c0: 55                           	push	ebp
 11375c1: 8b ec                        	mov	ebp, esp
 11375c3: 6a ff                        	push	-0x1
 11375c5: 68 d4 fc 4b 01               	push	0x14bfcd4
 11375ca: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 11375d0: 50                           	push	eax
 11375d1: 83 ec 24                     	sub	esp, 0x24
 11375d4: 53                           	push	ebx
 11375d5: 56                           	push	esi
 11375d6: 57                           	push	edi
 11375d7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11375dc: 33 c5                        	xor	eax, ebp
 11375de: 50                           	push	eax
 11375df: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 11375e2: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 11375e8: 8b f1                        	mov	esi, ecx
 11375ea: 89 75 e8                     	mov	dword ptr [ebp - 0x18], esi
 11375ed: 8d 5e 04                     	lea	ebx, [esi + 0x4]
 11375f0: 33 ff                        	xor	edi, edi
 11375f2: 6a 08                        	push	0x8
 11375f4: 89 3b                        	mov	dword ptr [ebx], edi
 11375f6: e8 1f f5 29 00               	call	0x13d6b1a <.text+0x29f62a>
 11375fb: 83 c4 04                     	add	esp, 0x4
 11375fe: 3b c7                        	cmp	eax, edi
 1137600: 0f 84 cc 01 00 00            	je	0x11377d2 <.text+0x2e2>
 1137606: 89 03                        	mov	dword ptr [ebx], eax
 1137608: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
 113760b: 33 c9                        	xor	ecx, ecx
 113760d: 89 08                        	mov	dword ptr [eax], ecx
 113760f: 8b 03                        	mov	eax, dword ptr [ebx]
 1137611: 89 18                        	mov	dword ptr [eax], ebx
 1137613: c7 43 18 07 00 00 00         	mov	dword ptr [ebx + 0x18], 0x7
 113761a: 89 7b 14                     	mov	dword ptr [ebx + 0x14], edi
 113761d: 66 89 4b 04                  	mov	word ptr [ebx + 0x4], cx
 1137621: 8d 5e 24                     	lea	ebx, [esi + 0x24]
 1137624: 6a 08                        	push	0x8
 1137626: 89 7d fc                     	mov	dword ptr [ebp - 0x4], edi
 1137629: 89 3b                        	mov	dword ptr [ebx], edi
 113762b: e8 ea f4 29 00               	call	0x13d6b1a <.text+0x29f62a>
 1137630: 83 c4 04                     	add	esp, 0x4
 1137633: 3b c7                        	cmp	eax, edi
 1137635: 0f 84 73 01 00 00            	je	0x11377ae <.text+0x2be>
 113763b: 89 03                        	mov	dword ptr [ebx], eax
 113763d: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
 1137640: 33 c9                        	xor	ecx, ecx
 1137642: 89 08                        	mov	dword ptr [eax], ecx
 1137644: 8b 13                        	mov	edx, dword ptr [ebx]
 1137646: 89 1a                        	mov	dword ptr [edx], ebx
 1137648: 33 c0                        	xor	eax, eax
 113764a: c7 43 18 07 00 00 00         	mov	dword ptr [ebx + 0x18], 0x7
 1137651: 89 7b 14                     	mov	dword ptr [ebx + 0x14], edi
 1137654: 66 89 43 04                  	mov	word ptr [ebx + 0x4], ax
 1137658: 8d 5e 44                     	lea	ebx, [esi + 0x44]
 113765b: 6a 08                        	push	0x8
 113765d: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1137661: 89 3b                        	mov	dword ptr [ebx], edi
 1137663: e8 b2 f4 29 00               	call	0x13d6b1a <.text+0x29f62a>
 1137668: 83 c4 04                     	add	esp, 0x4
 113766b: 3b c7                        	cmp	eax, edi
 113766d: 0f 84 ef 01 00 00            	je	0x1137862 <.text+0x372>
 1137673: 89 03                        	mov	dword ptr [ebx], eax
 1137675: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
 1137678: 33 c9                        	xor	ecx, ecx
 113767a: 89 08                        	mov	dword ptr [eax], ecx
 113767c: 8b 0b                        	mov	ecx, dword ptr [ebx]
 113767e: 89 19                        	mov	dword ptr [ecx], ebx
 1137680: 33 d2                        	xor	edx, edx
 1137682: c7 43 18 07 00 00 00         	mov	dword ptr [ebx + 0x18], 0x7
 1137689: 89 7b 14                     	mov	dword ptr [ebx + 0x14], edi
 113768c: 66 89 53 04                  	mov	word ptr [ebx + 0x4], dx
 1137690: 8d 5e 68                     	lea	ebx, [esi + 0x68]
 1137693: 6a 08                        	push	0x8
 1137695: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 1137699: 89 3b                        	mov	dword ptr [ebx], edi
 113769b: e8 7a f4 29 00               	call	0x13d6b1a <.text+0x29f62a>
 11376a0: 83 c4 04                     	add	esp, 0x4
 11376a3: 3b c7                        	cmp	eax, edi
 11376a5: 0f 84 93 01 00 00            	je	0x113783e <.text+0x34e>
 11376ab: 89 03                        	mov	dword ptr [ebx], eax
 11376ad: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
 11376b0: 33 c9                        	xor	ecx, ecx
 11376b2: 89 08                        	mov	dword ptr [eax], ecx
 11376b4: 8b 03                        	mov	eax, dword ptr [ebx]
 11376b6: 89 18                        	mov	dword ptr [eax], ebx
 11376b8: 89 7b 04                     	mov	dword ptr [ebx + 0x4], edi
 11376bb: 89 7b 08                     	mov	dword ptr [ebx + 0x8], edi
 11376be: 89 7b 0c                     	mov	dword ptr [ebx + 0xc], edi
 11376c1: 8d 9e 80 00 00 00            	lea	ebx, [esi + 0x80]
 11376c7: 6a 08                        	push	0x8
 11376c9: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 11376cd: 89 3b                        	mov	dword ptr [ebx], edi
 11376cf: e8 46 f4 29 00               	call	0x13d6b1a <.text+0x29f62a>
 11376d4: 83 c4 04                     	add	esp, 0x4
 11376d7: 3b c7                        	cmp	eax, edi
 11376d9: 0f 84 3b 01 00 00            	je	0x113781a <.text+0x32a>
 11376df: 89 03                        	mov	dword ptr [ebx], eax
 11376e1: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
 11376e4: 33 c9                        	xor	ecx, ecx
 11376e6: 89 08                        	mov	dword ptr [eax], ecx
 11376e8: 8b 0b                        	mov	ecx, dword ptr [ebx]
 11376ea: 89 19                        	mov	dword ptr [ecx], ebx
 11376ec: 89 7b 04                     	mov	dword ptr [ebx + 0x4], edi
 11376ef: 89 7b 08                     	mov	dword ptr [ebx + 0x8], edi
 11376f2: 89 7b 0c                     	mov	dword ptr [ebx + 0xc], edi
 11376f5: 8d 9e 94 00 00 00            	lea	ebx, [esi + 0x94]
 11376fb: 6a 08                        	push	0x8
 11376fd: c6 45 fc 04                  	mov	byte ptr [ebp - 0x4], 0x4
 1137701: 89 3b                        	mov	dword ptr [ebx], edi
 1137703: e8 12 f4 29 00               	call	0x13d6b1a <.text+0x29f62a>
 1137708: 83 c4 04                     	add	esp, 0x4
 113770b: 3b c7                        	cmp	eax, edi
 113770d: 0f 84 e3 00 00 00            	je	0x11377f6 <.text+0x306>
 1137713: 89 03                        	mov	dword ptr [ebx], eax
 1137715: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
 1137718: 33 c9                        	xor	ecx, ecx
 113771a: 89 08                        	mov	dword ptr [eax], ecx
 113771c: 8b 13                        	mov	edx, dword ptr [ebx]
 113771e: 89 1a                        	mov	dword ptr [edx], ebx
 1137720: 89 7b 04                     	mov	dword ptr [ebx + 0x4], edi
 1137723: 89 7b 08                     	mov	dword ptr [ebx + 0x8], edi
 1137726: 89 7b 0c                     	mov	dword ptr [ebx + 0xc], edi
 1137729: 8d 9e a8 00 00 00            	lea	ebx, [esi + 0xa8]
 113772f: 6a 08                        	push	0x8
 1137731: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
 1137735: 89 3b                        	mov	dword ptr [ebx], edi
 1137737: e8 de f3 29 00               	call	0x13d6b1a <.text+0x29f62a>
 113773c: 83 c4 04                     	add	esp, 0x4
 113773f: 3b c7                        	cmp	eax, edi
 1137741: 0f 84 8b 00 00 00            	je	0x11377d2 <.text+0x2e2>
 1137747: 89 03                        	mov	dword ptr [ebx], eax
 1137749: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
 113774c: 33 c9                        	xor	ecx, ecx
 113774e: 89 08                        	mov	dword ptr [eax], ecx
 1137750: 8b 03                        	mov	eax, dword ptr [ebx]
 1137752: 89 18                        	mov	dword ptr [eax], ebx
 1137754: 89 7b 04                     	mov	dword ptr [ebx + 0x4], edi
 1137757: 89 7b 08                     	mov	dword ptr [ebx + 0x8], edi
 113775a: 89 7b 0c                     	mov	dword ptr [ebx + 0xc], edi
 113775d: 8d 9e bc 00 00 00            	lea	ebx, [esi + 0xbc]
 1137763: 6a 08                        	push	0x8
 1137765: c6 45 fc 06                  	mov	byte ptr [ebp - 0x4], 0x6
 1137769: 89 3b                        	mov	dword ptr [ebx], edi
 113776b: e8 aa f3 29 00               	call	0x13d6b1a <.text+0x29f62a>
 1137770: 83 c4 04                     	add	esp, 0x4
 1137773: 3b c7                        	cmp	eax, edi
 1137775: 74 37                        	je	0x11377ae <.text+0x2be>
 1137777: 89 03                        	mov	dword ptr [ebx], eax
 1137779: 33 c9                        	xor	ecx, ecx
 113777b: 89 08                        	mov	dword ptr [eax], ecx
 113777d: 33 d2                        	xor	edx, edx
 113777f: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1137782: 8b 0b                        	mov	ecx, dword ptr [ebx]
 1137784: 89 19                        	mov	dword ptr [ecx], ebx
 1137786: 89 7b 04                     	mov	dword ptr [ebx + 0x4], edi
 1137789: 89 7b 08                     	mov	dword ptr [ebx + 0x8], edi
 113778c: 89 7b 0c                     	mov	dword ptr [ebx + 0xc], edi
 113778f: 8b ce                        	mov	ecx, esi
 1137791: c6 45 fc 07                  	mov	byte ptr [ebp - 0x4], 0x7
 1137795: e8 76 fd ff ff               	call	0x1137510 <.text+0x20>
 113779a: 8b c6                        	mov	eax, esi
 113779c: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 113779f: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11377a6: 59                           	pop	ecx
 11377a7: 5f                           	pop	edi
 11377a8: 5e                           	pop	esi
 11377a9: 5b                           	pop	ebx
 11377aa: 8b e5                        	mov	esp, ebp
 11377ac: 5d                           	pop	ebp
 11377ad: c3                           	ret
 11377ae: 8d 55 f0                     	lea	edx, [ebp - 0x10]
 11377b1: 52                           	push	edx
 11377b2: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 11377b5: 89 7d f0                     	mov	dword ptr [ebp - 0x10], edi
 11377b8: e8 0d ed 29 00               	call	0x13d64ca <.text+0x29efda>
 11377bd: 68 90 0f 91 01               	push	0x1910f90
 11377c2: 8d 45 dc                     	lea	eax, [ebp - 0x24]
 11377c5: 50                           	push	eax
 11377c6: c7 45 dc 84 20 56 01         	mov	dword ptr [ebp - 0x24], 0x1562084
 11377cd: e8 c8 f3 29 00               	call	0x13d6b9a <.text+0x29f6aa>
 11377d2: 8d 4d ec                     	lea	ecx, [ebp - 0x14]
 11377d5: 51                           	push	ecx
 11377d6: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11377d9: 89 7d ec                     	mov	dword ptr [ebp - 0x14], edi
 11377dc: e8 e9 ec 29 00               	call	0x13d64ca <.text+0x29efda>
 11377e1: 68 90 0f 91 01               	push	0x1910f90
 11377e6: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 11377e9: 52                           	push	edx
 11377ea: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 11377f1: e8 a4 f3 29 00               	call	0x13d6b9a <.text+0x29f6aa>
 11377f6: 8d 45 f0                     	lea	eax, [ebp - 0x10]
 11377f9: 50                           	push	eax
 11377fa: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 11377fd: 89 7d f0                     	mov	dword ptr [ebp - 0x10], edi
 1137800: e8 c5 ec 29 00               	call	0x13d64ca <.text+0x29efda>
 1137805: 68 90 0f 91 01               	push	0x1910f90
 113780a: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 113780d: 51                           	push	ecx
 113780e: c7 45 dc 84 20 56 01         	mov	dword ptr [ebp - 0x24], 0x1562084
 1137815: e8 80 f3 29 00               	call	0x13d6b9a <.text+0x29f6aa>
 113781a: 8d 55 ec                     	lea	edx, [ebp - 0x14]
 113781d: 52                           	push	edx
 113781e: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1137821: 89 7d ec                     	mov	dword ptr [ebp - 0x14], edi
 1137824: e8 a1 ec 29 00               	call	0x13d64ca <.text+0x29efda>
 1137829: 68 90 0f 91 01               	push	0x1910f90
 113782e: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 1137831: 50                           	push	eax
 1137832: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 1137839: e8 5c f3 29 00               	call	0x13d6b9a <.text+0x29f6aa>
 113783e: 8d 4d f0                     	lea	ecx, [ebp - 0x10]
 1137841: 51                           	push	ecx
 1137842: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 1137845: 89 7d f0                     	mov	dword ptr [ebp - 0x10], edi
 1137848: e8 7d ec 29 00               	call	0x13d64ca <.text+0x29efda>
 113784d: 68 90 0f 91 01               	push	0x1910f90
 1137852: 8d 55 dc                     	lea	edx, [ebp - 0x24]
 1137855: 52                           	push	edx
 1137856: c7 45 dc 84 20 56 01         	mov	dword ptr [ebp - 0x24], 0x1562084
 113785d: e8 38 f3 29 00               	call	0x13d6b9a <.text+0x29f6aa>
 1137862: 8d 45 ec                     	lea	eax, [ebp - 0x14]
 1137865: 50                           	push	eax
 1137866: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1137869: 89 7d ec                     	mov	dword ptr [ebp - 0x14], edi
 113786c: e8 59 ec 29 00               	call	0x13d64ca <.text+0x29efda>
 1137871: 68 90 0f 91 01               	push	0x1910f90
 1137876: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1137879: 51                           	push	ecx
 113787a: c7 45 d0 84 20 56 01         	mov	dword ptr [ebp - 0x30], 0x1562084
 1137881: e8 14 f3 29 00               	call	0x13d6b9a <.text+0x29f6aa>
 1137886: cc                           	int3
 1137887: cc                           	int3
 1137888: cc                           	int3
 1137889: cc                           	int3
 113788a: cc                           	int3
 113788b: cc                           	int3
 113788c: cc                           	int3
 113788d: cc                           	int3
 113788e: cc                           	int3
 113788f: cc                           	int3
 1137890: 56                           	push	esi
 1137891: 8b f1                        	mov	esi, ecx
 1137893: 8b 86 c0 00 00 00            	mov	eax, dword ptr [esi + 0xc0]
 1137899: 57                           	push	edi
 113789a: 33 ff                        	xor	edi, edi
 113789c: 3b c7                        	cmp	eax, edi
 113789e: 74 09                        	je	0x11378a9 <.text+0x3b9>
