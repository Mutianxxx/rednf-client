
<stdin>:	file format elf32-i386

Disassembly of section .text:

011bb1b0 <.text>:
 11bb1b0: 55                           	push	ebp
 11bb1b1: 8b ec                        	mov	ebp, esp
 11bb1b3: 8b 41 24                     	mov	eax, dword ptr [ecx + 0x24]
 11bb1b6: 8b 51 28                     	mov	edx, dword ptr [ecx + 0x28]
 11bb1b9: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11bb1bc: 2b d0                        	sub	edx, eax
 11bb1be: c1 fa 02                     	sar	edx, 0x2
 11bb1c1: 3b ca                        	cmp	ecx, edx
 11bb1c3: 73 07                        	jae	0x11bb1cc <.text+0x1c>
 11bb1c5: 8b 04 88                     	mov	eax, dword ptr [eax + 4*ecx]
 11bb1c8: 5d                           	pop	ebp
 11bb1c9: c2 04 00                     	ret	0x4
 11bb1cc: 33 c0                        	xor	eax, eax
 11bb1ce: 5d                           	pop	ebp
 11bb1cf: c2 04 00                     	ret	0x4
 11bb1d2: cc                           	int3
 11bb1d3: cc                           	int3
 11bb1d4: cc                           	int3
 11bb1d5: cc                           	int3
 11bb1d6: cc                           	int3
 11bb1d7: cc                           	int3
 11bb1d8: cc                           	int3
 11bb1d9: cc                           	int3
 11bb1da: cc                           	int3
 11bb1db: cc                           	int3
 11bb1dc: cc                           	int3
 11bb1dd: cc                           	int3
 11bb1de: cc                           	int3
 11bb1df: cc                           	int3
 11bb1e0: 55                           	push	ebp
 11bb1e1: 8b ec                        	mov	ebp, esp
 11bb1e3: 51                           	push	ecx
 11bb1e4: 53                           	push	ebx
 11bb1e5: 56                           	push	esi
 11bb1e6: 8b f1                        	mov	esi, ecx
 11bb1e8: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11bb1eb: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 11bb1ee: 2b c1                        	sub	eax, ecx
 11bb1f0: 57                           	push	edi
 11bb1f1: 33 ff                        	xor	edi, edi
 11bb1f3: c1 f8 05                     	sar	eax, 0x5
 11bb1f6: 3b f8                        	cmp	edi, eax
 11bb1f8: 73 3f                        	jae	0x11bb239 <.text+0x89>
 11bb1fa: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11bb1fd: 89 7d fc                     	mov	dword ptr [ebp - 0x4], edi
 11bb200: 03 4d fc                     	add	ecx, dword ptr [ebp - 0x4]
 11bb203: 83 7b 18 08                  	cmp	dword ptr [ebx + 0x18], 0x8
 11bb207: 8b 53 14                     	mov	edx, dword ptr [ebx + 0x14]
 11bb20a: 72 05                        	jb	0x11bb211 <.text+0x61>
 11bb20c: 8b 43 04                     	mov	eax, dword ptr [ebx + 0x4]
 11bb20f: eb 03                        	jmp	0x11bb214 <.text+0x64>
 11bb211: 8d 43 04                     	lea	eax, [ebx + 0x4]
 11bb214: 52                           	push	edx
 11bb215: 8b 51 14                     	mov	edx, dword ptr [ecx + 0x14]
 11bb218: 50                           	push	eax
 11bb219: 52                           	push	edx
 11bb21a: 6a 00                        	push	0x0
 11bb21c: e8 0f 6a 24 ff               	call	0x401c30
 11bb221: 85 c0                        	test	eax, eax
 11bb223: 74 1f                        	je	0x11bb244 <.text+0x94>
 11bb225: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11bb228: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 11bb22b: 83 45 fc 20                  	add	dword ptr [ebp - 0x4], 0x20
 11bb22f: 2b c1                        	sub	eax, ecx
 11bb231: 47                           	inc	edi
 11bb232: c1 f8 05                     	sar	eax, 0x5
 11bb235: 3b f8                        	cmp	edi, eax
 11bb237: 72 c7                        	jb	0x11bb200 <.text+0x50>
 11bb239: 5f                           	pop	edi
 11bb23a: 5e                           	pop	esi
 11bb23b: 33 c0                        	xor	eax, eax
 11bb23d: 5b                           	pop	ebx
 11bb23e: 8b e5                        	mov	esp, ebp
 11bb240: 5d                           	pop	ebp
 11bb241: c2 04 00                     	ret	0x4
 11bb244: 83 ff ff                     	cmp	edi, -0x1
 11bb247: 74 f0                        	je	0x11bb239 <.text+0x89>
 11bb249: 8b 46 24                     	mov	eax, dword ptr [esi + 0x24]
 11bb24c: 8b 4e 28                     	mov	ecx, dword ptr [esi + 0x28]
 11bb24f: 2b c8                        	sub	ecx, eax
 11bb251: c1 f9 02                     	sar	ecx, 0x2
 11bb254: 3b f9                        	cmp	edi, ecx
 11bb256: 72 05                        	jb	0x11bb25d <.text+0xad>
 11bb258: e8 4a bb 21 00               	call	0x13d6da7 <.text+0x21bbf7>
 11bb25d: 8b 04 b8                     	mov	eax, dword ptr [eax + 4*edi]
 11bb260: 5f                           	pop	edi
 11bb261: 5e                           	pop	esi
 11bb262: 5b                           	pop	ebx
 11bb263: 8b e5                        	mov	esp, ebp
 11bb265: 5d                           	pop	ebp
 11bb266: c2 04 00                     	ret	0x4
 11bb269: cc                           	int3
 11bb26a: cc                           	int3
 11bb26b: cc                           	int3
 11bb26c: cc                           	int3
 11bb26d: cc                           	int3
 11bb26e: cc                           	int3
 11bb26f: cc                           	int3
 11bb270: 55                           	push	ebp
 11bb271: 8b ec                        	mov	ebp, esp
 11bb273: 83 ec 2c                     	sub	esp, 0x2c
 11bb276: 53                           	push	ebx
 11bb277: 56                           	push	esi
 11bb278: 8b f1                        	mov	esi, ecx
 11bb27a: 57                           	push	edi
 11bb27b: 8d 45 e0                     	lea	eax, [ebp - 0x20]
 11bb27e: 8d 4e 0c                     	lea	ecx, [esi + 0xc]
 11bb281: 33 db                        	xor	ebx, ebx
 11bb283: 50                           	push	eax
 11bb284: 89 5d f8                     	mov	dword ptr [ebp - 0x8], ebx
 11bb287: 89 4d fc                     	mov	dword ptr [ebp - 0x4], ecx
 11bb28a: e8 e1 ae fb ff               	call	0x1176170
 11bb28f: 8d 55 ec                     	lea	edx, [ebp - 0x14]
 11bb292: 8d 4e 20                     	lea	ecx, [esi + 0x20]
 11bb295: 52                           	push	edx
 11bb296: 89 4d f8                     	mov	dword ptr [ebp - 0x8], ecx
 11bb299: e8 d2 ae fb ff               	call	0x1176170
 11bb29e: 8b 7d e0                     	mov	edi, dword ptr [ebp - 0x20]
 11bb2a1: 8b 75 e8                     	mov	esi, dword ptr [ebp - 0x18]
 11bb2a4: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11bb2a7: 8d 45 e0                     	lea	eax, [ebp - 0x20]
 11bb2aa: 50                           	push	eax
 11bb2ab: 83 cb 01                     	or	ebx, 0x1
 11bb2ae: e8                           	<unknown>
 11bb2af: 8d                           	<unknown>
