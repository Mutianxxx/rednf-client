
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bf510 <.text>:
 11bf510: 55                           	push	ebp
 11bf511: 8b ec                        	mov	ebp, esp
 11bf513: 83 ec 1c                     	sub	esp, 0x1c
 11bf516: 53                           	push	ebx
 11bf517: 56                           	push	esi
 11bf518: 8b f1                        	mov	esi, ecx
 11bf51a: 83 be ac 02 00 00 00         	cmp	dword ptr [esi + 0x2ac], 0x0
 11bf521: 57                           	push	edi
 11bf522: 74 2e                        	je	0x11bf552 <.text+0x42>
 11bf524: 8b 86 ac 02 00 00            	mov	eax, dword ptr [esi + 0x2ac]
 11bf52a: 8b 4e 18                     	mov	ecx, dword ptr [esi + 0x18]
 11bf52d: 8b 78 0c                     	mov	edi, dword ptr [eax + 0xc]
 11bf530: 8b 56 14                     	mov	edx, dword ptr [esi + 0x14]
 11bf533: 03 f9                        	add	edi, ecx
 11bf535: 57                           	push	edi
 11bf536: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
 11bf539: 03 fa                        	add	edi, edx
 11bf53b: 57                           	push	edi
 11bf53c: 8b 78 04                     	mov	edi, dword ptr [eax + 0x4]
 11bf53f: 8b 00                        	mov	eax, dword ptr [eax]
 11bf541: 03 f9                        	add	edi, ecx
 11bf543: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11bf549: 57                           	push	edi
 11bf54a: 03 c2                        	add	eax, edx
 11bf54c: 50                           	push	eax
 11bf54d: e8 be 51 ff ff               	call	0x11b4710
 11bf552: 8b 16                        	mov	edx, dword ptr [esi]
 11bf554: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11bf557: 8b ce                        	mov	ecx, esi
 11bf559: ff d0                        	call	eax
 11bf55b: 8d 4e 48                     	lea	ecx, [esi + 0x48]
 11bf55e: e8 fd 21 1d 00               	call	0x1391760 <.text+0x1d2250>
 11bf563: 85 c0                        	test	eax, eax
 11bf565: 74 7f                        	je	0x11bf5e6 <.text+0xd6>
 11bf567: 8b 1d 7c 71 b5 01            	mov	ebx, dword ptr [0x1b5717c]
 11bf56d: 85 db                        	test	ebx, ebx
 11bf56f: 74 2f                        	je	0x11bf5a0 <.text+0x90>
 11bf571: 8b 3d 68 71 b5 01            	mov	edi, dword ptr [0x1b57168]
 11bf577: 8d 4e 48                     	lea	ecx, [esi + 0x48]
 11bf57a: e8 01 9b 3f ff               	call	0x5b9080
 11bf57f: 8b 4e 40                     	mov	ecx, dword ptr [esi + 0x40]
 11bf582: 8b 56 30                     	mov	edx, dword ptr [esi + 0x30]
 11bf585: 03 56 18                     	add	edx, dword ptr [esi + 0x18]
 11bf588: 50                           	push	eax
 11bf589: 8b 46 2c                     	mov	eax, dword ptr [esi + 0x2c]
 11bf58c: 03 46 14                     	add	eax, dword ptr [esi + 0x14]
 11bf58f: 6a 00                        	push	0x0
 11bf591: 6a 00                        	push	0x0
 11bf593: 51                           	push	ecx
 11bf594: 52                           	push	edx
 11bf595: 50                           	push	eax
 11bf596: 57                           	push	edi
 11bf597: 8b cb                        	mov	ecx, ebx
 11bf599: e8 d2 96 00 00               	call	0x11c8c70 <.text+0x9760>
 11bf59e: eb 46                        	jmp	0x11bf5e6 <.text+0xd6>
 11bf5a0: 8b 0d 68 71 b5 01            	mov	ecx, dword ptr [0x1b57168]
 11bf5a6: 8b 11                        	mov	edx, dword ptr [ecx]
 11bf5a8: 8b 42 4c                     	mov	eax, dword ptr [edx + 0x4c]
 11bf5ab: 6a 00                        	push	0x0
 11bf5ad: ff d0                        	call	eax
 11bf5af: 8b 1d 68 71 b5 01            	mov	ebx, dword ptr [0x1b57168]
 11bf5b5: 8b 3b                        	mov	edi, dword ptr [ebx]
 11bf5b7: 8d 4e 48                     	lea	ecx, [esi + 0x48]
 11bf5ba: e8 c1 9a 3f ff               	call	0x5b9080
 11bf5bf: 8b 4e 40                     	mov	ecx, dword ptr [esi + 0x40]
 11bf5c2: 8b 56 30                     	mov	edx, dword ptr [esi + 0x30]
 11bf5c5: 03 56 18                     	add	edx, dword ptr [esi + 0x18]
 11bf5c8: 50                           	push	eax
 11bf5c9: 8b 46 2c                     	mov	eax, dword ptr [esi + 0x2c]
 11bf5cc: 03 46 14                     	add	eax, dword ptr [esi + 0x14]
 11bf5cf: 51                           	push	ecx
 11bf5d0: 52                           	push	edx
 11bf5d1: 8b 57 5c                     	mov	edx, dword ptr [edi + 0x5c]
 11bf5d4: 50                           	push	eax
 11bf5d5: 8b cb                        	mov	ecx, ebx
 11bf5d7: ff d2                        	call	edx
 11bf5d9: 8b 0d 68 71 b5 01            	mov	ecx, dword ptr [0x1b57168]
 11bf5df: 8b 01                        	mov	eax, dword ptr [ecx]
 11bf5e1: 8b 50 50                     	mov	edx, dword ptr [eax + 0x50]
 11bf5e4: ff d2                        	call	edx
 11bf5e6: 8b 46 60                     	mov	eax, dword ptr [esi + 0x60]
 11bf5e9: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11bf5ec: 85 c0                        	test	eax, eax
 11bf5ee: 74 3b                        	je	0x11bf62b <.text+0x11b>
 11bf5f0: 80 7e 0d 00                  	cmp	byte ptr [esi + 0xd], 0x0
 11bf5f4: 74 35                        	je	0x11bf62b <.text+0x11b>
 11bf5f6: 8b 0d f0 24 a4 01            	mov	ecx, dword ptr [0x1a424f0]
 11bf5fc: 3b 4e 34                     	cmp	ecx, dword ptr [esi + 0x34]
 11bf5ff: 0f 94 c1                     	sete	cl
 11bf602: 84 c9                        	test	cl, cl
 11bf604: 74 25                        	je	0x11bf62b <.text+0x11b>
 11bf606: 8b 38                        	mov	edi, dword ptr [eax]
 11bf608: e8 c3 87 00 00               	call	0x11c7dd0 <.text+0x88c0>
 11bf60d: 0f b7 d8                     	movzx	ebx, ax
 11bf610: c1 e3 10                     	shl	ebx, 0x10
 11bf613: e8 a8 87 00 00               	call	0x11c7dc0 <.text+0x88b0>
 11bf618: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11bf61b: 0f b7 d0                     	movzx	edx, ax
 11bf61e: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
 11bf621: 0b d3                        	or	edx, ebx
 11bf623: 52                           	push	edx
 11bf624: 6a 00                        	push	0x0
 11bf626: 6a 0c                        	push	0xc
 11bf628: 56                           	push	esi
 11bf629: ff d0                        	call	eax
 11bf62b: 83 7e 44 00                  	cmp	dword ptr [esi + 0x44], 0x0
 11bf62f: 74 0a                        	je	0x11bf63b <.text+0x12b>
 11bf631: 8b 4e 44                     	mov	ecx, dword ptr [esi + 0x44]
 11bf634: 8b 11                        	mov	edx, dword ptr [ecx]
 11bf636: 8b 02                        	mov	eax, dword ptr [edx]
 11bf638: 56                           	push	esi
 11bf639: ff d0                        	call	eax
 11bf63b: 8b 16                        	mov	edx, dword ptr [esi]
 11bf63d: 8b 42 30                     	mov	eax, dword ptr [edx + 0x30]
 11bf640: 8b ce                        	mov	ecx, esi
 11bf642: ff d0                        	call	eax
 11bf644: 8d 55 f0                     	lea	edx, [ebp - 0x10]
 11bf647: 8d 4e 64                     	lea	ecx, [esi + 0x64]
 11bf64a: 52                           	push	edx
 11bf64b: e8 c0 e0 15 00               	call	0x131d710 <.text+0x15e200>
 11bf650: 8b 5d f0                     	mov	ebx, dword ptr [ebp - 0x10]
 11bf653: 8d 45 e4                     	lea	eax, [ebp - 0x1c]
 11bf656: 50                           	push	eax
 11bf657: 8d 4e 64                     	lea	ecx, [esi + 0x64]
 11bf65a: e8 11 6b fb ff               	call	0x1176170
 11bf65f: 85 db                        	test	ebx, ebx
 11bf661: 74 7b                        	je	0x11bf6de <.text+0x1ce>
 11bf663: 8b 13                        	mov	edx, dword ptr [ebx]
 11bf665: 85 d2                        	test	edx, edx
 11bf667: 74 75                        	je	0x11bf6de <.text+0x1ce>
 11bf669: 8b 08                        	mov	ecx, dword ptr [eax]
 11bf66b: 85 c9                        	test	ecx, ecx
 11bf66d: 74 02                        	je	0x11bf671 <.text+0x161>
 11bf66f: 8b 09                        	mov	ecx, dword ptr [ecx]
 11bf671: 3b d1                        	cmp	edx, ecx
 11bf673: 75 69                        	jne	0x11bf6de <.text+0x1ce>
 11bf675: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 11bf678: 3b 48 08                     	cmp	ecx, dword ptr [eax + 0x8]
 11bf67b: 74 66                        	je	0x11bf6e3 <.text+0x1d3>
 11bf67d: 8b c2                        	mov	eax, edx
 11bf67f: 85 c0                        	test	eax, eax
 11bf681: 74 5b                        	je	0x11bf6de <.text+0x1ce>
 11bf683: 85 c9                        	test	ecx, ecx
 11bf685: 74 57                        	je	0x11bf6de <.text+0x1ce>
 11bf687: 3b 48 04                     	cmp	ecx, dword ptr [eax + 0x4]
 11bf68a: 74 52                        	je	0x11bf6de <.text+0x1ce>
 11bf68c: 8b 79 08                     	mov	edi, dword ptr [ecx + 0x8]
 11bf68f: 85 ff                        	test	edi, edi
 11bf691: 74 36                        	je	0x11bf6c9 <.text+0x1b9>
 11bf693: 80 7f 0c 00                  	cmp	byte ptr [edi + 0xc], 0x0
 11bf697: 74 1d                        	je	0x11bf6b6 <.text+0x1a6>
 11bf699: 8b cf                        	mov	ecx, edi
 11bf69b: e8 70 fe ff ff               	call	0x11bf510 <.text>
 11bf6a0: 80 7f 0d 00                  	cmp	byte ptr [edi + 0xd], 0x0
 11bf6a4: 74 0d                        	je	0x11bf6b3 <.text+0x1a3>
 11bf6a6: 80 7f 0e 00                  	cmp	byte ptr [edi + 0xe], 0x0
 11bf6aa: 74 07                        	je	0x11bf6b3 <.text+0x1a3>
 11bf6ac: 8b cf                        	mov	ecx, edi
 11bf6ae: e8 ed fb ff ff               	call	0x11bf2a0
 11bf6b3: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 11bf6b6: 8b 7f 60                     	mov	edi, dword ptr [edi + 0x60]
 11bf6b9: 85 ff                        	test	edi, edi
 11bf6bb: 74 0c                        	je	0x11bf6c9 <.text+0x1b9>
 11bf6bd: 8b 17                        	mov	edx, dword ptr [edi]
 11bf6bf: 8b 42 08                     	mov	eax, dword ptr [edx + 0x8]
 11bf6c2: 8b cf                        	mov	ecx, edi
 11bf6c4: ff d0                        	call	eax
 11bf6c6: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 11bf6c9: 8b 03                        	mov	eax, dword ptr [ebx]
 11bf6cb: 85 c0                        	test	eax, eax
 11bf6cd: 74 0f                        	je	0x11bf6de <.text+0x1ce>
 11bf6cf: 3b 48 04                     	cmp	ecx, dword ptr [eax + 0x4]
 11bf6d2: 74 0a                        	je	0x11bf6de <.text+0x1ce>
 11bf6d4: 8b 09                        	mov	ecx, dword ptr [ecx]
 11bf6d6: 89 4d f8                     	mov	dword ptr [ebp - 0x8], ecx
 11bf6d9: e9 75 ff ff ff               	jmp	0x11bf653 <.text+0x143>
 11bf6de: e8 c4 76 21 00               	call	0x13d6da7 <.text+0x217897>
 11bf6e3: 8b 16                        	mov	edx, dword ptr [esi]
 11bf6e5: 8b 42 2c                     	mov	eax, dword ptr [edx + 0x2c]
 11bf6e8: 8b ce                        	mov	ecx, esi
 11bf6ea: ff d0                        	call	eax
 11bf6ec: 83 be ac 02 00 00 00         	cmp	dword ptr [esi + 0x2ac], 0x0
 11bf6f3: 5f                           	pop	edi
 11bf6f4: 5e                           	pop	esi
 11bf6f5: 5b                           	pop	ebx
 11bf6f6: 74 19                        	je	0x11bf711 <.text+0x201>
 11bf6f8: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11bf6fe: 68 58 02 00 00               	push	0x258
 11bf703: 68 20 03 00 00               	push	0x320
 11bf708: 6a 00                        	push	0x0
 11bf70a: 6a 00                        	push	0x0
 11bf70c: e8 ff 4f ff ff               	call	0x11b4710
 11bf711: b8 01 00 00 00               	mov	eax, 0x1
 11bf716: 8b e5                        	mov	esp, ebp
 11bf718: 5d                           	pop	ebp
 11bf719: c3                           	ret
 11bf71a: cc                           	int3
 11bf71b: cc                           	int3
 11bf71c: cc                           	int3
 11bf71d: cc                           	int3
 11bf71e: cc                           	int3
 11bf71f: cc                           	int3
