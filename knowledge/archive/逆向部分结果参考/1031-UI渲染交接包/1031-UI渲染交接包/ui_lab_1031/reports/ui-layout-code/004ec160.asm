
<stdin>:	file format elf32-i386

Disassembly of section .text:

004ec160 <.text>:
  4ec160: 55                           	push	ebp
  4ec161: 8b ec                        	mov	ebp, esp
  4ec163: 6a ff                        	push	-0x1
  4ec165: 68 72 36 41 01               	push	0x1413672
  4ec16a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4ec170: 50                           	push	eax
  4ec171: 53                           	push	ebx
  4ec172: 56                           	push	esi
  4ec173: 57                           	push	edi
  4ec174: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4ec179: 33 c5                        	xor	eax, ebp
  4ec17b: 50                           	push	eax
  4ec17c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4ec17f: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4ec185: 8b f1                        	mov	esi, ecx
  4ec187: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
  4ec18a: 89 be b0 00 00 00            	mov	dword ptr [esi + 0xb0], edi
  4ec190: e8 8b ef ff ff               	call	0x4eb120
  4ec195: 68 b8 02 00 00               	push	0x2b8
  4ec19a: e8 e1 41 cc 00               	call	0x11b0380 <.text+0xcc4220>
  4ec19f: 83 c4 04                     	add	esp, 0x4
  4ec1a2: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
  4ec1a5: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  4ec1ac: 85 c0                        	test	eax, eax
  4ec1ae: 74 09                        	je	0x4ec1b9 <.text+0x59>
  4ec1b0: 8b c8                        	mov	ecx, eax
  4ec1b2: e8 c9 2d cd 00               	call	0x11bef80 <.text+0xcd2e20>
  4ec1b7: eb 02                        	jmp	0x4ec1bb <.text+0x5b>
  4ec1b9: 33 c0                        	xor	eax, eax
  4ec1bb: 83 cb ff                     	or	ebx, -0x1
  4ec1be: 68 b8 02 00 00               	push	0x2b8
  4ec1c3: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec1c6: 89 86 b4 00 00 00            	mov	dword ptr [esi + 0xb4], eax
  4ec1cc: e8 af 41 cc 00               	call	0x11b0380 <.text+0xcc4220>
  4ec1d1: 83 c4 04                     	add	esp, 0x4
  4ec1d4: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
  4ec1d7: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
  4ec1de: 85 c0                        	test	eax, eax
  4ec1e0: 74 09                        	je	0x4ec1eb <.text+0x8b>
  4ec1e2: 8b c8                        	mov	ecx, eax
  4ec1e4: e8 97 2d cd 00               	call	0x11bef80 <.text+0xcd2e20>
  4ec1e9: eb 02                        	jmp	0x4ec1ed <.text+0x8d>
  4ec1eb: 33 c0                        	xor	eax, eax
  4ec1ed: 68 b8 02 00 00               	push	0x2b8
  4ec1f2: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec1f5: 89 86 b8 00 00 00            	mov	dword ptr [esi + 0xb8], eax
  4ec1fb: e8 80 41 cc 00               	call	0x11b0380 <.text+0xcc4220>
  4ec200: 83 c4 04                     	add	esp, 0x4
  4ec203: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
  4ec206: c7 45 fc 02 00 00 00         	mov	dword ptr [ebp - 0x4], 0x2
  4ec20d: 85 c0                        	test	eax, eax
  4ec20f: 74 09                        	je	0x4ec21a <.text+0xba>
  4ec211: 8b c8                        	mov	ecx, eax
  4ec213: e8 68 2d cd 00               	call	0x11bef80 <.text+0xcd2e20>
  4ec218: eb 02                        	jmp	0x4ec21c <.text+0xbc>
  4ec21a: 33 c0                        	xor	eax, eax
  4ec21c: 89 86 bc 00 00 00            	mov	dword ptr [esi + 0xbc], eax
  4ec222: 8b 86 b4 00 00 00            	mov	eax, dword ptr [esi + 0xb4]
  4ec228: 50                           	push	eax
  4ec229: 8b cf                        	mov	ecx, edi
  4ec22b: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec22e: e8 fd 30 cd 00               	call	0x11bf330 <.text+0xcd31d0>
  4ec233: 8b 8e b8 00 00 00            	mov	ecx, dword ptr [esi + 0xb8]
  4ec239: 51                           	push	ecx
  4ec23a: 8b cf                        	mov	ecx, edi
  4ec23c: e8 ef 30 cd 00               	call	0x11bf330 <.text+0xcd31d0>
  4ec241: 8b 96 bc 00 00 00            	mov	edx, dword ptr [esi + 0xbc]
  4ec247: 52                           	push	edx
  4ec248: 8b cf                        	mov	ecx, edi
  4ec24a: e8 e1 30 cd 00               	call	0x11bf330 <.text+0xcd31d0>
  4ec24f: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  4ec252: 8b 8e bc 00 00 00            	mov	ecx, dword ptr [esi + 0xbc]
  4ec258: 50                           	push	eax
  4ec259: e8 02 22 cd 00               	call	0x11be460 <.text+0xcd2300>
  4ec25e: 6a 3c                        	push	0x3c
  4ec260: e8 b5 a8 ee 00               	call	0x13d6b1a <.text+0xeea9ba>
  4ec265: 83 c4 04                     	add	esp, 0x4
  4ec268: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
  4ec26b: c7 45 fc 03 00 00 00         	mov	dword ptr [ebp - 0x4], 0x3
  4ec272: 85 c0                        	test	eax, eax
  4ec274: 74 10                        	je	0x4ec286 <.text+0x126>
  4ec276: 8b 8e b8 00 00 00            	mov	ecx, dword ptr [esi + 0xb8]
  4ec27c: 51                           	push	ecx
  4ec27d: 8b c8                        	mov	ecx, eax
  4ec27f: e8 3c 3d 02 00               	call	0x50ffc0 <.text+0x23e60>
  4ec284: eb 02                        	jmp	0x4ec288 <.text+0x128>
  4ec286: 33 c0                        	xor	eax, eax
  4ec288: 68 fc 01 00 00               	push	0x1fc
  4ec28d: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec290: 89 46 74                     	mov	dword ptr [esi + 0x74], eax
  4ec293: e8 e8 40 cc 00               	call	0x11b0380 <.text+0xcc4220>
  4ec298: 8b f8                        	mov	edi, eax
  4ec29a: 83 c4 04                     	add	esp, 0x4
  4ec29d: 89 7d 08                     	mov	dword ptr [ebp + 0x8], edi
  4ec2a0: c7 45 fc 04 00 00 00         	mov	dword ptr [ebp - 0x4], 0x4
  4ec2a7: 85 ff                        	test	edi, edi
  4ec2a9: 74 1b                        	je	0x4ec2c6 <.text+0x166>
  4ec2ab: 6a 00                        	push	0x0
  4ec2ad: 6a 01                        	push	0x1
  4ec2af: 68 18 7a 57 01               	push	0x1577a18
  4ec2b4: e8 37 3c cb 00               	call	0x119fef0 <.text+0xcb3d90>
  4ec2b9: 83 c4 04                     	add	esp, 0x4
  4ec2bc: 50                           	push	eax
  4ec2bd: 8b cf                        	mov	ecx, edi
  4ec2bf: e8 1c e2 ba 00               	call	0x109a4e0 <.text+0xbae380>
  4ec2c4: eb 02                        	jmp	0x4ec2c8 <.text+0x168>
  4ec2c6: 33 c0                        	xor	eax, eax
  4ec2c8: 68 fc 01 00 00               	push	0x1fc
  4ec2cd: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec2d0: a3 f0 c3 a4 01               	mov	dword ptr [0x1a4c3f0], eax
  4ec2d5: e8 a6 40 cc 00               	call	0x11b0380 <.text+0xcc4220>
  4ec2da: 8b f8                        	mov	edi, eax
  4ec2dc: 83 c4 04                     	add	esp, 0x4
  4ec2df: 89 7d 08                     	mov	dword ptr [ebp + 0x8], edi
  4ec2e2: c7 45 fc 05 00 00 00         	mov	dword ptr [ebp - 0x4], 0x5
  4ec2e9: 85 ff                        	test	edi, edi
  4ec2eb: 74 1b                        	je	0x4ec308 <.text+0x1a8>
  4ec2ed: 6a 00                        	push	0x0
  4ec2ef: 6a 01                        	push	0x1
  4ec2f1: 68 b8 79 57 01               	push	0x15779b8
  4ec2f6: e8 f5 3b cb 00               	call	0x119fef0 <.text+0xcb3d90>
  4ec2fb: 83 c4 04                     	add	esp, 0x4
  4ec2fe: 50                           	push	eax
  4ec2ff: 8b cf                        	mov	ecx, edi
  4ec301: e8 da e1 ba 00               	call	0x109a4e0 <.text+0xbae380>
  4ec306: eb 02                        	jmp	0x4ec30a <.text+0x1aa>
  4ec308: 33 c0                        	xor	eax, eax
  4ec30a: 8b ce                        	mov	ecx, esi
  4ec30c: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec30f: a3 f4 c3 a4 01               	mov	dword ptr [0x1a4c3f4], eax
  4ec314: e8 77 d0 ff ff               	call	0x4e9390
  4ec319: c6 06 01                     	mov	byte ptr [esi], 0x1
  4ec31c: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4ec31f: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4ec326: 59                           	pop	ecx
  4ec327: 5f                           	pop	edi
  4ec328: 5e                           	pop	esi
  4ec329: 5b                           	pop	ebx
  4ec32a: 8b e5                        	mov	esp, ebp
  4ec32c: 5d                           	pop	ebp
  4ec32d: c2 08 00                     	ret	0x8
  4ec330: c7 01 70 7a 57 01            	mov	dword ptr [ecx], 0x1577a70
  4ec336: c3                           	ret
  4ec337: cc                           	int3
  4ec338: cc                           	int3
  4ec339: cc                           	int3
  4ec33a: cc                           	int3
  4ec33b: cc                           	int3
  4ec33c: cc                           	int3
  4ec33d: cc                           	int3
  4ec33e: cc                           	int3
  4ec33f: cc                           	int3
  4ec340: 55                           	push	ebp
  4ec341: 8b ec                        	mov	ebp, esp
  4ec343: f6 45 08 01                  	test	byte ptr [ebp + 0x8], 0x1
  4ec347: 56                           	push	esi
  4ec348: 8b f1                        	mov	esi, ecx
  4ec34a: c7 06 70 7a 57 01            	mov	dword ptr [esi], 0x1577a70
  4ec350: 74 09                        	je	0x4ec35b <.text+0x1fb>
  4ec352: 56                           	push	esi
  4ec353: e8 cf 97 ee 00               	call	0x13d5b27 <.text+0xee99c7>
  4ec358: 83 c4 04                     	add	esp, 0x4
  4ec35b: 8b c6                        	mov	eax, esi
  4ec35d: 5e                           	pop	esi
  4ec35e: 5d                           	pop	ebp
  4ec35f: c2 04 00                     	ret	0x4
  4ec362: cc                           	int3
  4ec363: cc                           	int3
  4ec364: cc                           	int3
  4ec365: cc                           	int3
  4ec366: cc                           	int3
  4ec367: cc                           	int3
  4ec368: cc                           	int3
  4ec369: cc                           	int3
  4ec36a: cc                           	int3
  4ec36b: cc                           	int3
  4ec36c: cc                           	int3
  4ec36d: cc                           	int3
  4ec36e: cc                           	int3
  4ec36f: cc                           	int3
  4ec370: 55                           	push	ebp
  4ec371: 8b ec                        	mov	ebp, esp
  4ec373: 83 ec 28                     	sub	esp, 0x28
  4ec376: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4ec37b: 33 c5                        	xor	eax, ebp
  4ec37d: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  4ec380: 8d 45 d8                     	lea	eax, [ebp - 0x28]
  4ec383: 50                           	push	eax
  4ec384: e8 97 cb f1 ff               	call	0x408f20
  4ec389: 85 c0                        	test	eax, eax
  4ec38b: 74 11                        	je	0x4ec39e <.text+0x23e>
  4ec38d: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  4ec390: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  4ec393: 33 cd                        	xor	ecx, ebp
  4ec395: e8 3e ae ee 00               	call	0x13d71d8 <.text+0xeeb078>
  4ec39a: 8b e5                        	mov	esp, ebp
  4ec39c: 5d                           	pop	ebp
  4ec39d: c3                           	ret
  4ec39e: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  4ec3a1: 33 cd                        	xor	ecx, ebp
  4ec3a3: 83 c8 ff                     	or	eax, -0x1
  4ec3a6: e8 2d ae ee 00               	call	0x13d71d8 <.text+0xeeb078>
  4ec3ab: 8b e5                        	mov	esp, ebp
  4ec3ad: 5d                           	pop	ebp
  4ec3ae: c3                           	ret
  4ec3af: cc                           	int3
  4ec3b0: 55                           	push	ebp
  4ec3b1: 8b ec                        	mov	ebp, esp
  4ec3b3: 83 ec 28                     	sub	esp, 0x28
  4ec3b6: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4ec3bb: 33 c5                        	xor	eax, ebp
  4ec3bd: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  4ec3c0: 8d 45 d8                     	lea	eax, [ebp - 0x28]
  4ec3c3: 50                           	push	eax
  4ec3c4: e8 57 cb f1 ff               	call	0x408f20
  4ec3c9: 85 c0                        	test	eax, eax
  4ec3cb: 74 11                        	je	0x4ec3de <.text+0x27e>
  4ec3cd: 8b 40 04                     	mov	eax, dword ptr [eax + 0x4]
  4ec3d0: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  4ec3d3: 33 cd                        	xor	ecx, ebp
  4ec3d5: e8 fe ad ee 00               	call	0x13d71d8 <.text+0xeeb078>
  4ec3da: 8b e5                        	mov	esp, ebp
  4ec3dc: 5d                           	pop	ebp
  4ec3dd: c3                           	ret
  4ec3de: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  4ec3e1: 33 cd                        	xor	ecx, ebp
  4ec3e3: 83 c8 ff                     	or	eax, -0x1
  4ec3e6: e8 ed ad ee 00               	call	0x13d71d8 <.text+0xeeb078>
  4ec3eb: 8b e5                        	mov	esp, ebp
  4ec3ed: 5d                           	pop	ebp
  4ec3ee: c3                           	ret
  4ec3ef: cc                           	int3
  4ec3f0: 55                           	push	ebp
  4ec3f1: 8b ec                        	mov	ebp, esp
  4ec3f3: 83 ec 28                     	sub	esp, 0x28
  4ec3f6: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4ec3fb: 33 c5                        	xor	eax, ebp
  4ec3fd: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
  4ec400: 8d 45 d8                     	lea	eax, [ebp - 0x28]
  4ec403: 50                           	push	eax
  4ec404: e8 17 cb f1 ff               	call	0x408f20
  4ec409: 85 c0                        	test	eax, eax
  4ec40b: 74 10                        	je	0x4ec41d <.text+0x2bd>
  4ec40d: 8b 00                        	mov	eax, dword ptr [eax]
  4ec40f: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  4ec412: 33 cd                        	xor	ecx, ebp
  4ec414: e8 bf ad ee 00               	call	0x13d71d8 <.text+0xeeb078>
  4ec419: 8b e5                        	mov	esp, ebp
  4ec41b: 5d                           	pop	ebp
  4ec41c: c3                           	ret
  4ec41d: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  4ec420: 33 cd                        	xor	ecx, ebp
  4ec422: 83 c8 ff                     	or	eax, -0x1
  4ec425: e8 ae ad ee 00               	call	0x13d71d8 <.text+0xeeb078>
  4ec42a: 8b e5                        	mov	esp, ebp
  4ec42c: 5d                           	pop	ebp
  4ec42d: c3                           	ret
  4ec42e: cc                           	int3
  4ec42f: cc                           	int3
  4ec430: 55                           	push	ebp
  4ec431: 8b ec                        	mov	ebp, esp
  4ec433: 83 7d 08 03                  	cmp	dword ptr [ebp + 0x8], 0x3
  4ec437: 75 11                        	jne	0x4ec44a <.text+0x2ea>
  4ec439: 68 e8 03 00 00               	push	0x3e8
  4ec43e: e8 0d a8 f7 ff               	call	0x466c50
  4ec443: 8b c8                        	mov	ecx, eax
  4ec445: e8 86 a5 f7 ff               	call	0x4669d0
  4ec44a: 5d                           	pop	ebp
  4ec44b: c2 04 00                     	ret	0x4
  4ec44e: cc                           	int3
  4ec44f: cc                           	int3
  4ec450: 55                           	push	ebp
  4ec451: 8b ec                        	mov	ebp, esp
  4ec453: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  4ec456: 8b 08                        	mov	ecx, dword ptr [eax]
  4ec458: 80 79 15 00                  	cmp	byte ptr [ecx + 0x15], 0x0
  4ec45c: 75 0c                        	jne	0x4ec46a <.text+0x30a>
  4ec45e: 8b ff                        	mov	edi, edi
  4ec460: 8b c1                        	mov	eax, ecx
  4ec462: 8b 08                        	mov	ecx, dword ptr [eax]
  4ec464: 80 79 15 00                  	cmp	byte ptr [ecx + 0x15], 0x0
  4ec468: 74 f6                        	je	0x4ec460 <.text+0x300>
  4ec46a: 5d                           	pop	ebp
  4ec46b: c3                           	ret
  4ec46c: cc                           	int3
  4ec46d: cc                           	int3
  4ec46e: cc                           	int3
  4ec46f: cc                           	int3
  4ec470: 55                           	push	ebp
  4ec471: 8b ec                        	mov	ebp, esp
  4ec473: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  4ec476: 8b 48 08                     	mov	ecx, dword ptr [eax + 0x8]
  4ec479: 80 b9 a5 00 00 00 00         	cmp	byte ptr [ecx + 0xa5], 0x0
  4ec480: 75 0e                        	jne	0x4ec490 <.text+0x330>
  4ec482: 8b c1                        	mov	eax, ecx
  4ec484: 8b 48 08                     	mov	ecx, dword ptr [eax + 0x8]
  4ec487: 80 b9 a5 00 00 00 00         	cmp	byte ptr [ecx + 0xa5], 0x0
  4ec48e: 74 f2                        	je	0x4ec482 <.text+0x322>
  4ec490: 5d                           	pop	ebp
  4ec491: c3                           	ret
  4ec492: cc                           	int3
  4ec493: cc                           	int3
  4ec494: cc                           	int3
  4ec495: cc                           	int3
  4ec496: cc                           	int3
  4ec497: cc                           	int3
  4ec498: cc                           	int3
  4ec499: cc                           	int3
  4ec49a: cc                           	int3
  4ec49b: cc                           	int3
  4ec49c: cc                           	int3
  4ec49d: cc                           	int3
  4ec49e: cc                           	int3
  4ec49f: cc                           	int3
  4ec4a0: 8b c1                        	mov	eax, ecx
  4ec4a2: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  4ec4a5: 80 ba a5 00 00 00 00         	cmp	byte ptr [edx + 0xa5], 0x0
  4ec4ac: 75 4e                        	jne	0x4ec4fc <.text+0x39c>
  4ec4ae: 8b 4a 08                     	mov	ecx, dword ptr [edx + 0x8]
  4ec4b1: 80 b9 a5 00 00 00 00         	cmp	byte ptr [ecx + 0xa5], 0x0
  4ec4b8: 75 1c                        	jne	0x4ec4d6 <.text+0x376>
  4ec4ba: 8b 11                        	mov	edx, dword ptr [ecx]
  4ec4bc: 80 ba a5 00 00 00 00         	cmp	byte ptr [edx + 0xa5], 0x0
  4ec4c3: 75 0d                        	jne	0x4ec4d2 <.text+0x372>
  4ec4c5: 8b ca                        	mov	ecx, edx
  4ec4c7: 8b 11                        	mov	edx, dword ptr [ecx]
  4ec4c9: 80 ba a5 00 00 00 00         	cmp	byte ptr [edx + 0xa5], 0x0
  4ec4d0: 74 f3                        	je	0x4ec4c5 <.text+0x365>
  4ec4d2: 89 48 08                     	mov	dword ptr [eax + 0x8], ecx
  4ec4d5: c3                           	ret
  4ec4d6: 8b 52 04                     	mov	edx, dword ptr [edx + 0x4]
  4ec4d9: 80 ba a5 00 00 00 00         	cmp	byte ptr [edx + 0xa5], 0x0
  4ec4e0: 75 17                        	jne	0x4ec4f9 <.text+0x399>
  4ec4e2: 8b 48 08                     	mov	ecx, dword ptr [eax + 0x8]
  4ec4e5: 3b 4a 08                     	cmp	ecx, dword ptr [edx + 0x8]
  4ec4e8: 75 0f                        	jne	0x4ec4f9 <.text+0x399>
  4ec4ea: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  4ec4ed: 8b 52 04                     	mov	edx, dword ptr [edx + 0x4]
  4ec4f0: 80 ba a5 00 00 00 00         	cmp	byte ptr [edx + 0xa5], 0x0
  4ec4f7: 74 e9                        	je	0x4ec4e2 <.text+0x382>
  4ec4f9: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  4ec4fc: c3                           	ret
  4ec4fd: cc                           	int3
  4ec4fe: cc                           	int3
  4ec4ff: cc                           	int3
  4ec500: 55                           	push	ebp
  4ec501: 8b ec                        	mov	ebp, esp
  4ec503: 6a 00                        	push	0x0
  4ec505: e8 4b ca ee 00               	call	0x13d8f55 <.text+0xeecdf5>
  4ec50a: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
  4ec50d: 89 01                        	mov	dword ptr [ecx], eax
  4ec50f: 83 c4 04                     	add	esp, 0x4
  4ec512: 89 51 04                     	mov	dword ptr [ecx + 0x4], edx
  4ec515: 8b c1                        	mov	eax, ecx
  4ec517: 5d                           	pop	ebp
  4ec518: c2 04 00                     	ret	0x4
  4ec51b: cc                           	int3
  4ec51c: cc                           	int3
  4ec51d: cc                           	int3
  4ec51e: cc                           	int3
  4ec51f: cc                           	int3
  4ec520: 55                           	push	ebp
  4ec521: 8b ec                        	mov	ebp, esp
  4ec523: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
  4ec529: 68 ea 01 00 00               	push	0x1ea
  4ec52e: e8 fd 63 c4 00               	call	0x1132930 <.text+0xc467d0>
  4ec533: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  4ec536: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
  4ec53c: 50                           	push	eax
  4ec53d: e8 de 6b c4 00               	call	0x1133120 <.text+0xc46fc0>
  4ec542: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
  4ec545: 51                           	push	ecx
  4ec546: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
  4ec54c: e8 ff 6b c4 00               	call	0x1133150 <.text+0xc46ff0>
  4ec551: 8b 55 10                     	mov	edx, dword ptr [ebp + 0x10]
  4ec554: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
  4ec55a: 52                           	push	edx
  4ec55b: e8 c0 6b c4 00               	call	0x1133120 <.text+0xc46fc0>
  4ec560: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
  4ec563: 8b 0d 7c b3 af 01            	mov	ecx, dword ptr [0x1afb37c]
  4ec569: 50                           	push	eax
  4ec56a: e8 11 6c c4 00               	call	0x1133180 <.text+0xc47020>
  4ec56f: e8 1c 65 c4 00               	call	0x1132a90 <.text+0xc46930>
  4ec574: 5d                           	pop	ebp
  4ec575: c2 10 00                     	ret	0x10
  4ec578: cc                           	int3
  4ec579: cc                           	int3
  4ec57a: cc                           	int3
  4ec57b: cc                           	int3
  4ec57c: cc                           	int3
  4ec57d: cc                           	int3
  4ec57e: cc                           	int3
  4ec57f: cc                           	int3
  4ec580: 55                           	push	ebp
  4ec581: 8b ec                        	mov	ebp, esp
  4ec583: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  4ec586: 8b 42 08                     	mov	eax, dword ptr [edx + 0x8]
  4ec589: 56                           	push	esi
  4ec58a: 8b 30                        	mov	esi, dword ptr [eax]
  4ec58c: 89 72 08                     	mov	dword ptr [edx + 0x8], esi
  4ec58f: 8b 30                        	mov	esi, dword ptr [eax]
  4ec591: 80 be a5 00 00 00 00         	cmp	byte ptr [esi + 0xa5], 0x0
  4ec598: 75 03                        	jne	0x4ec59d <.text+0x43d>
  4ec59a: 89 56 04                     	mov	dword ptr [esi + 0x4], edx
  4ec59d: 8b 72 04                     	mov	esi, dword ptr [edx + 0x4]
  4ec5a0: 89 70 04                     	mov	dword ptr [eax + 0x4], esi
  4ec5a3: 8b 49 08                     	mov	ecx, dword ptr [ecx + 0x8]
  4ec5a6: 5e                           	pop	esi
  4ec5a7: 3b 51 04                     	cmp	edx, dword ptr [ecx + 0x4]
  4ec5aa: 75 0c                        	jne	0x4ec5b8 <.text+0x458>
  4ec5ac: 89 41 04                     	mov	dword ptr [ecx + 0x4], eax
  4ec5af: 89 10                        	mov	dword ptr [eax], edx
  4ec5b1: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  4ec5b4: 5d                           	pop	ebp
  4ec5b5: c2 04 00                     	ret	0x4
  4ec5b8: 8b 4a 04                     	mov	ecx, dword ptr [edx + 0x4]
  4ec5bb: 3b 11                        	cmp	edx, dword ptr [ecx]
  4ec5bd: 75 0b                        	jne	0x4ec5ca <.text+0x46a>
  4ec5bf: 89 01                        	mov	dword ptr [ecx], eax
  4ec5c1: 89 10                        	mov	dword ptr [eax], edx
  4ec5c3: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  4ec5c6: 5d                           	pop	ebp
  4ec5c7: c2 04 00                     	ret	0x4
  4ec5ca: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  4ec5cd: 89 10                        	mov	dword ptr [eax], edx
  4ec5cf: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  4ec5d2: 5d                           	pop	ebp
  4ec5d3: c2 04 00                     	ret	0x4
  4ec5d6: cc                           	int3
  4ec5d7: cc                           	int3
  4ec5d8: cc                           	int3
  4ec5d9: cc                           	int3
  4ec5da: cc                           	int3
  4ec5db: cc                           	int3
  4ec5dc: cc                           	int3
  4ec5dd: cc                           	int3
  4ec5de: cc                           	int3
  4ec5df: cc                           	int3
  4ec5e0: 55                           	push	ebp
  4ec5e1: 8b ec                        	mov	ebp, esp
  4ec5e3: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
  4ec5e6: 8b 02                        	mov	eax, dword ptr [edx]
  4ec5e8: 56                           	push	esi
  4ec5e9: 8b 70 08                     	mov	esi, dword ptr [eax + 0x8]
  4ec5ec: 89 32                        	mov	dword ptr [edx], esi
  4ec5ee: 8b 70 08                     	mov	esi, dword ptr [eax + 0x8]
  4ec5f1: 80 be a5 00 00 00 00         	cmp	byte ptr [esi + 0xa5], 0x0
  4ec5f8: 75 03                        	jne	0x4ec5fd <.text+0x49d>
  4ec5fa: 89 56 04                     	mov	dword ptr [esi + 0x4], edx
  4ec5fd: 8b 72 04                     	mov	esi, dword ptr [edx + 0x4]
  4ec600: 89 70 04                     	mov	dword ptr [eax + 0x4], esi
  4ec603: 8b 49 08                     	mov	ecx, dword ptr [ecx + 0x8]
  4ec606: 5e                           	pop	esi
  4ec607: 3b 51 04                     	cmp	edx, dword ptr [ecx + 0x4]
  4ec60a: 75 0d                        	jne	0x4ec619 <.text+0x4b9>
  4ec60c: 89 41 04                     	mov	dword ptr [ecx + 0x4], eax
  4ec60f: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  4ec612: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  4ec615: 5d                           	pop	ebp
  4ec616: c2 04 00                     	ret	0x4
  4ec619: 8b 4a 04                     	mov	ecx, dword ptr [edx + 0x4]
  4ec61c: 3b 51 08                     	cmp	edx, dword ptr [ecx + 0x8]
  4ec61f: 75 0d                        	jne	0x4ec62e <.text+0x4ce>
  4ec621: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  4ec624: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  4ec627: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  4ec62a: 5d                           	pop	ebp
  4ec62b: c2 04 00                     	ret	0x4
  4ec62e: 89 01                        	mov	dword ptr [ecx], eax
  4ec630: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  4ec633: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  4ec636: 5d                           	pop	ebp
  4ec637: c2 04 00                     	ret	0x4
  4ec63a: cc                           	int3
  4ec63b: cc                           	int3
  4ec63c: cc                           	int3
  4ec63d: cc                           	int3
  4ec63e: cc                           	int3
  4ec63f: cc                           	int3
  4ec640: 83 c8 ff                     	or	eax, -0x1
  4ec643: 56                           	push	esi
  4ec644: 8b f1                        	mov	esi, ecx
  4ec646: 57                           	push	edi
  4ec647: 89 06                        	mov	dword ptr [esi], eax
  4ec649: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
  4ec64c: 89 86 8c 00 00 00            	mov	dword ptr [esi + 0x8c], eax
  4ec652: c7 46 04 05 00 00 00         	mov	dword ptr [esi + 0x4], 0x5
  4ec659: 33 ff                        	xor	edi, edi
  4ec65b: b9 08 00 00 00               	mov	ecx, 0x8
