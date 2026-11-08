
<stdin>:	file format elf32-i386

Disassembly of section .text:

010032b0 <.text>:
 10032b0: 55                           	push	ebp
 10032b1: 8b ec                        	mov	ebp, esp
 10032b3: 6a ff                        	push	-0x1
 10032b5: 68 f3 2c 4b 01               	push	0x14b2cf3
 10032ba: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 10032c0: 50                           	push	eax
 10032c1: 81 ec a0 00 00 00            	sub	esp, 0xa0
 10032c7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 10032cc: 33 c5                        	xor	eax, ebp
 10032ce: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 10032d1: 53                           	push	ebx
 10032d2: 56                           	push	esi
 10032d3: 57                           	push	edi
 10032d4: 50                           	push	eax
 10032d5: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 10032d8: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 10032de: 8b c1                        	mov	eax, ecx
 10032e0: be 08 00 00 00               	mov	esi, 0x8
 10032e5: 89 85 64 ff ff ff            	mov	dword ptr [ebp - 0x9c], eax
 10032eb: 39 b0 f4 03 00 00            	cmp	dword ptr [eax + 0x3f4], esi
 10032f1: 72 08                        	jb	0x10032fb <.text+0x4b>
 10032f3: 8b 80 e0 03 00 00            	mov	eax, dword ptr [eax + 0x3e0]
 10032f9: eb 05                        	jmp	0x1003300 <.text+0x50>
 10032fb: 05 e0 03 00 00               	add	eax, 0x3e0
 1003300: 50                           	push	eax
 1003301: 68 78 21 56 01               	push	0x1562178
 1003306: e8 e5 cb 19 00               	call	0x119fef0 <.text+0x19cc40>
 100330b: 83 c4 04                     	add	esp, 0x4
 100330e: 50                           	push	eax
 100330f: e8 0c 03 22 00               	call	0x1223620 <.text+0x220370>
 1003314: 83 c4 08                     	add	esp, 0x8
 1003317: 84 c0                        	test	al, al
 1003319: 75 1c                        	jne	0x1003337 <.text+0x87>
 100331b: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 100331e: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1003325: 59                           	pop	ecx
 1003326: 5f                           	pop	edi
 1003327: 5e                           	pop	esi
 1003328: 5b                           	pop	ebx
 1003329: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 100332c: 33 cd                        	xor	ecx, ebp
 100332e: e8 a5 3e 3d 00               	call	0x13d71d8 <.text+0x3d3f28>
 1003333: 8b e5                        	mov	esp, ebp
 1003335: 5d                           	pop	ebp
 1003336: c3                           	ret
 1003337: 33 db                        	xor	ebx, ebx
 1003339: 56                           	push	esi
 100333a: 89 5d b0                     	mov	dword ptr [ebp - 0x50], ebx
 100333d: e8 d8 37 3d 00               	call	0x13d6b1a <.text+0x3d386a>
 1003342: 83 c4 04                     	add	esp, 0x4
 1003345: 3b c3                        	cmp	eax, ebx
 1003347: 0f 84 ef 03 00 00            	je	0x100373c <.text+0x48c>
 100334d: 89 45 b0                     	mov	dword ptr [ebp - 0x50], eax
 1003350: 33 c9                        	xor	ecx, ecx
 1003352: 89 08                        	mov	dword ptr [eax], ecx
 1003354: 33 d2                        	xor	edx, edx
 1003356: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1003359: 8b 4d b0                     	mov	ecx, dword ptr [ebp - 0x50]
 100335c: 8d 45 b0                     	lea	eax, [ebp - 0x50]
 100335f: 89 01                        	mov	dword ptr [ecx], eax
 1003361: bf 07 00 00 00               	mov	edi, 0x7
 1003366: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
 1003369: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
 100336c: 66 89 55 b4                  	mov	word ptr [ebp - 0x4c], dx
 1003370: 56                           	push	esi
 1003371: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 1003374: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 1003377: e8 9e 37 3d 00               	call	0x13d6b1a <.text+0x3d386a>
 100337c: 83 c4 04                     	add	esp, 0x4
 100337f: 3b c3                        	cmp	eax, ebx
 1003381: 0f 84 82 03 00 00            	je	0x1003709 <.text+0x459>
 1003387: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
 100338a: 33 c9                        	xor	ecx, ecx
 100338c: 89 08                        	mov	dword ptr [eax], ecx
 100338e: 33 d2                        	xor	edx, edx
 1003390: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1003393: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
 1003396: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 1003399: 89 01                        	mov	dword ptr [ecx], eax
 100339b: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 100339e: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 10033a1: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
 10033a5: 8d 45 b0                     	lea	eax, [ebp - 0x50]
 10033a8: 6a 01                        	push	0x1
 10033aa: 50                           	push	eax
 10033ab: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 10033af: e8 5c 1e 22 00               	call	0x1225210 <.text+0x221f60>
 10033b4: 83 c4 08                     	add	esp, 0x8
 10033b7: 84 c0                        	test	al, al
 10033b9: 0f 84 bb 02 00 00            	je	0x100367a <.text+0x3ca>
 10033bf: 90                           	nop
 10033c0: 68 ec b0 82 01               	push	0x182b0ec
 10033c5: e8 26 cb 19 00               	call	0x119fef0 <.text+0x19cc40>
 10033ca: 8b c8                        	mov	ecx, eax
 10033cc: 83 c4 04                     	add	esp, 0x4
 10033cf: 8d 71 02                     	lea	esi, [ecx + 0x2]
 10033d2: 66 8b 11                     	mov	dx, word ptr [ecx]
 10033d5: 83 c1 02                     	add	ecx, 0x2
 10033d8: 66 3b d3                     	cmp	dx, bx
 10033db: 75 f5                        	jne	0x10033d2 <.text+0x122>
 10033dd: 2b ce                        	sub	ecx, esi
 10033df: d1 f9                        	sar	ecx
 10033e1: 51                           	push	ecx
 10033e2: 8b 4d c4                     	mov	ecx, dword ptr [ebp - 0x3c]
 10033e5: 50                           	push	eax
 10033e6: 51                           	push	ecx
 10033e7: 53                           	push	ebx
 10033e8: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 10033eb: e8 40 e8 3f ff               	call	0x401c30
 10033f0: 85 c0                        	test	eax, eax
 10033f2: 0f 85 67 02 00 00            	jne	0x100365f <.text+0x3af>
 10033f8: 6a 08                        	push	0x8
 10033fa: 89 5d 90                     	mov	dword ptr [ebp - 0x70], ebx
 10033fd: e8 18 37 3d 00               	call	0x13d6b1a <.text+0x3d386a>
 1003402: 83 c4 04                     	add	esp, 0x4
 1003405: 3b c3                        	cmp	eax, ebx
 1003407: 0f 84 c9 02 00 00            	je	0x10036d6 <.text+0x426>
 100340d: 89 45 90                     	mov	dword ptr [ebp - 0x70], eax
 1003410: 33 c9                        	xor	ecx, ecx
 1003412: 89 08                        	mov	dword ptr [eax], ecx
 1003414: 33 d2                        	xor	edx, edx
 1003416: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1003419: 8b 45 90                     	mov	eax, dword ptr [ebp - 0x70]
 100341c: 8d 55 90                     	lea	edx, [ebp - 0x70]
 100341f: 89 10                        	mov	dword ptr [eax], edx
 1003421: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
 1003424: 89 5d a4                     	mov	dword ptr [ebp - 0x5c], ebx
 1003427: 66 89 4d 94                  	mov	word ptr [ebp - 0x6c], cx
 100342b: 83 c8 ff                     	or	eax, -0x1
 100342e: 68 78 21 56 01               	push	0x1562178
 1003433: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 1003437: 89 9d 78 ff ff ff            	mov	dword ptr [ebp - 0x88], ebx
 100343d: 89 9d 7c ff ff ff            	mov	dword ptr [ebp - 0x84], ebx
 1003443: 89 5d 80                     	mov	dword ptr [ebp - 0x80], ebx
 1003446: 89 5d 84                     	mov	dword ptr [ebp - 0x7c], ebx
 1003449: 89 45 88                     	mov	dword ptr [ebp - 0x78], eax
 100344c: 89 45 8c                     	mov	dword ptr [ebp - 0x74], eax
 100344f: e8 9c ca 19 00               	call	0x119fef0 <.text+0x19cc40>
 1003454: 8b c8                        	mov	ecx, eax
 1003456: 83 c4 04                     	add	esp, 0x4
 1003459: 8d 71 02                     	lea	esi, [ecx + 0x2]
 100345c: 8d 64 24 00                  	lea	esp, [esp]
 1003460: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003463: 83 c1 02                     	add	ecx, 0x2
 1003466: 66 3b d3                     	cmp	dx, bx
 1003469: 75 f5                        	jne	0x1003460 <.text+0x1b0>
 100346b: 2b ce                        	sub	ecx, esi
 100346d: d1 f9                        	sar	ecx
 100346f: 51                           	push	ecx
 1003470: 50                           	push	eax
 1003471: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
 1003474: e8 b7 cb 40 ff               	call	0x410030
 1003479: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 100347c: 52                           	push	edx
 100347d: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 1003481: e8 ca 1c 22 00               	call	0x1225150 <.text+0x221ea0>
 1003486: 83 c4 04                     	add	esp, 0x4
 1003489: 3a c3                        	cmp	al, bl
 100348b: 0f 84 88 01 00 00            	je	0x1003619 <.text+0x369>
 1003491: 68 cc b0 82 01               	push	0x182b0cc
 1003496: e8 55 ca 19 00               	call	0x119fef0 <.text+0x19cc40>
 100349b: 8b c8                        	mov	ecx, eax
 100349d: 83 c4 04                     	add	esp, 0x4
 10034a0: 8d 71 02                     	lea	esi, [ecx + 0x2]
 10034a3: 66 8b 11                     	mov	dx, word ptr [ecx]
 10034a6: 83 c1 02                     	add	ecx, 0x2
 10034a9: 66 3b d3                     	cmp	dx, bx
 10034ac: 75 f5                        	jne	0x10034a3 <.text+0x1f3>
 10034ae: 8b 7d e4                     	mov	edi, dword ptr [ebp - 0x1c]
 10034b1: 2b ce                        	sub	ecx, esi
 10034b3: d1 f9                        	sar	ecx
 10034b5: 8b f7                        	mov	esi, edi
 10034b7: 3b f9                        	cmp	edi, ecx
 10034b9: 72 02                        	jb	0x10034bd <.text+0x20d>
 10034bb: 8b f1                        	mov	esi, ecx
 10034bd: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 10034c1: 8b 55 d4                     	mov	edx, dword ptr [ebp - 0x2c]
 10034c4: 73 03                        	jae	0x10034c9 <.text+0x219>
 10034c6: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
 10034c9: 3b f3                        	cmp	esi, ebx
 10034cb: 76 24                        	jbe	0x10034f1 <.text+0x241>
 10034cd: 8d 49 00                     	lea	ecx, [ecx]
 10034d0: 66 8b 1a                     	mov	bx, word ptr [edx]
 10034d3: 66 3b 18                     	cmp	bx, word ptr [eax]
 10034d6: 75 0d                        	jne	0x10034e5 <.text+0x235>
 10034d8: 83 c2 02                     	add	edx, 0x2
 10034db: 83 c0 02                     	add	eax, 0x2
 10034de: 4e                           	dec	esi
 10034df: 75 ef                        	jne	0x10034d0 <.text+0x220>
 10034e1: 33 db                        	xor	ebx, ebx
 10034e3: eb 0c                        	jmp	0x10034f1 <.text+0x241>
 10034e5: 1b c0                        	sbb	eax, eax
 10034e7: 83 e0 fe                     	and	eax, -0x2
 10034ea: 40                           	inc	eax
 10034eb: 33 db                        	xor	ebx, ebx
 10034ed: 3b c3                        	cmp	eax, ebx
 10034ef: 75 12                        	jne	0x1003503 <.text+0x253>
 10034f1: 3b f9                        	cmp	edi, ecx
 10034f3: 73 05                        	jae	0x10034fa <.text+0x24a>
 10034f5: 83 c8 ff                     	or	eax, -0x1
 10034f8: eb 07                        	jmp	0x1003501 <.text+0x251>
 10034fa: 33 c0                        	xor	eax, eax
 10034fc: 3b f9                        	cmp	edi, ecx
 10034fe: 0f 95 c0                     	setne	al
 1003501: 3b c3                        	cmp	eax, ebx
 1003503: 0f 94 c0                     	sete	al
 1003506: 3a c3                        	cmp	al, bl
 1003508: 74 11                        	je	0x100351b <.text+0x26b>
 100350a: 53                           	push	ebx
 100350b: e8 50 01 22 00               	call	0x1223660 <.text+0x2203b0>
 1003510: 89 85 78 ff ff ff            	mov	dword ptr [ebp - 0x88], eax
 1003516: e9 e2 00 00 00               	jmp	0x10035fd <.text+0x34d>
 100351b: 68 30 1c 57 01               	push	0x1571c30
 1003520: e8 cb c9 19 00               	call	0x119fef0 <.text+0x19cc40>
 1003525: 8b c8                        	mov	ecx, eax
 1003527: 83 c4 04                     	add	esp, 0x4
 100352a: 8d 71 02                     	lea	esi, [ecx + 0x2]
 100352d: 8d 49 00                     	lea	ecx, [ecx]
 1003530: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003533: 83 c1 02                     	add	ecx, 0x2
 1003536: 66 3b d3                     	cmp	dx, bx
 1003539: 75 f5                        	jne	0x1003530 <.text+0x280>
 100353b: 2b ce                        	sub	ecx, esi
 100353d: d1 f9                        	sar	ecx
 100353f: 51                           	push	ecx
 1003540: 50                           	push	eax
 1003541: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 1003544: 50                           	push	eax
 1003545: 53                           	push	ebx
 1003546: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1003549: e8 e2 e6 3f ff               	call	0x401c30
 100354e: 85 c0                        	test	eax, eax
 1003550: 75 0e                        	jne	0x1003560 <.text+0x2b0>
 1003552: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
 1003555: 51                           	push	ecx
 1003556: e8 f5 1b 22 00               	call	0x1225150 <.text+0x221ea0>
 100355b: e9 9d 00 00 00               	jmp	0x10035fd <.text+0x34d>
 1003560: 68 a4 b0 82 01               	push	0x182b0a4
 1003565: e8 86 c9 19 00               	call	0x119fef0 <.text+0x19cc40>
 100356a: 8b c8                        	mov	ecx, eax
 100356c: 83 c4 04                     	add	esp, 0x4
 100356f: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1003572: 66 8b 11                     	mov	dx, word ptr [ecx]
 1003575: 83 c1 02                     	add	ecx, 0x2
 1003578: 66 3b d3                     	cmp	dx, bx
 100357b: 75 f5                        	jne	0x1003572 <.text+0x2c2>
 100357d: 8b 55 e4                     	mov	edx, dword ptr [ebp - 0x1c]
 1003580: 2b ce                        	sub	ecx, esi
 1003582: d1 f9                        	sar	ecx
 1003584: 51                           	push	ecx
 1003585: 50                           	push	eax
 1003586: 52                           	push	edx
 1003587: 53                           	push	ebx
 1003588: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 100358b: e8 a0 e6 3f ff               	call	0x401c30
 1003590: 85 c0                        	test	eax, eax
 1003592: 75 2c                        	jne	0x10035c0 <.text+0x310>
 1003594: 53                           	push	ebx
 1003595: e8 c6 00 22 00               	call	0x1223660 <.text+0x2203b0>
 100359a: 53                           	push	ebx
 100359b: 89 85 7c ff ff ff            	mov	dword ptr [ebp - 0x84], eax
 10035a1: e8 ba 00 22 00               	call	0x1223660 <.text+0x2203b0>
 10035a6: 53                           	push	ebx
 10035a7: 89 45 80                     	mov	dword ptr [ebp - 0x80], eax
 10035aa: e8 b1 00 22 00               	call	0x1223660 <.text+0x2203b0>
 10035af: 53                           	push	ebx
 10035b0: 89 45 84                     	mov	dword ptr [ebp - 0x7c], eax
 10035b3: e8 a8 00 22 00               	call	0x1223660 <.text+0x2203b0>
 10035b8: 83 c4 10                     	add	esp, 0x10
 10035bb: 89 45 88                     	mov	dword ptr [ebp - 0x78], eax
 10035be: eb 40                        	jmp	0x1003600 <.text+0x350>
 10035c0: 68 78 b0 82 01               	push	0x182b078
 10035c5: e8 26 c9 19 00               	call	0x119fef0 <.text+0x19cc40>
 10035ca: 8b c8                        	mov	ecx, eax
 10035cc: 83 c4 04                     	add	esp, 0x4
 10035cf: 8d 71 02                     	lea	esi, [ecx + 0x2]
 10035d2: 66 8b 11                     	mov	dx, word ptr [ecx]
 10035d5: 83 c1 02                     	add	ecx, 0x2
 10035d8: 66 3b d3                     	cmp	dx, bx
 10035db: 75 f5                        	jne	0x10035d2 <.text+0x322>
 10035dd: 2b ce                        	sub	ecx, esi
 10035df: d1 f9                        	sar	ecx
 10035e1: 51                           	push	ecx
 10035e2: 50                           	push	eax
 10035e3: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 10035e6: 50                           	push	eax
 10035e7: 53                           	push	ebx
 10035e8: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 10035eb: e8 40 e6 3f ff               	call	0x401c30
 10035f0: 85 c0                        	test	eax, eax
 10035f2: 75 0c                        	jne	0x1003600 <.text+0x350>
 10035f4: 53                           	push	ebx
 10035f5: e8 66 00 22 00               	call	0x1223660 <.text+0x2203b0>
 10035fa: 89 45 8c                     	mov	dword ptr [ebp - 0x74], eax
 10035fd: 83 c4 04                     	add	esp, 0x4
 1003600: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1003603: 51                           	push	ecx
 1003604: e8 47 1b 22 00               	call	0x1225150 <.text+0x221ea0>
 1003609: 83 c4 04                     	add	esp, 0x4
 100360c: 3a c3                        	cmp	al, bl
 100360e: 0f 85 7d fe ff ff            	jne	0x1003491 <.text+0x1e1>
 1003614: bf 07 00 00 00               	mov	edi, 0x7
 1003619: 8b 8d 64 ff ff ff            	mov	ecx, dword ptr [ebp - 0x9c]
 100361f: 8d 95 78 ff ff ff            	lea	edx, [ebp - 0x88]
 1003625: 52                           	push	edx
 1003626: 81 c1 c4 03 00 00            	add	ecx, 0x3c4
 100362c: e8 bf fb ff ff               	call	0x10031f0
 1003631: 83 7d a8 08                  	cmp	dword ptr [ebp - 0x58], 0x8
 1003635: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1003639: 72 0c                        	jb	0x1003647 <.text+0x397>
 100363b: 8b 45 94                     	mov	eax, dword ptr [ebp - 0x6c]
 100363e: 50                           	push	eax
 100363f: e8 e3 24 3d 00               	call	0x13d5b27 <.text+0x3d2877>
 1003644: 83 c4 04                     	add	esp, 0x4
 1003647: 8b 55 90                     	mov	edx, dword ptr [ebp - 0x70]
 100364a: 33 c9                        	xor	ecx, ecx
 100364c: 52                           	push	edx
 100364d: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
 1003650: 89 5d a4                     	mov	dword ptr [ebp - 0x5c], ebx
 1003653: 66 89 4d 94                  	mov	word ptr [ebp - 0x6c], cx
 1003657: e8 cb 24 3d 00               	call	0x13d5b27 <.text+0x3d2877>
 100365c: 83 c4 04                     	add	esp, 0x4
 100365f: 8d 45 b0                     	lea	eax, [ebp - 0x50]
 1003662: 6a 01                        	push	0x1
 1003664: 50                           	push	eax
 1003665: e8 a6 1b 22 00               	call	0x1225210 <.text+0x221f60>
 100366a: 83 c4 08                     	add	esp, 0x8
 100366d: 84 c0                        	test	al, al
 100366f: 0f 85 4b fd ff ff            	jne	0x10033c0 <.text+0x110>
 1003675: be 08 00 00 00               	mov	esi, 0x8
 100367a: 39 75 e8                     	cmp	dword ptr [ebp - 0x18], esi
 100367d: 72 0c                        	jb	0x100368b <.text+0x3db>
 100367f: 8b 4d d4                     	mov	ecx, dword ptr [ebp - 0x2c]
 1003682: 51                           	push	ecx
 1003683: e8 9f 24 3d 00               	call	0x13d5b27 <.text+0x3d2877>
 1003688: 83 c4 04                     	add	esp, 0x4
 100368b: 8b 45 d0                     	mov	eax, dword ptr [ebp - 0x30]
 100368e: 33 d2                        	xor	edx, edx
 1003690: 50                           	push	eax
 1003691: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 1003694: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 1003697: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
 100369b: e8 87 24 3d 00               	call	0x13d5b27 <.text+0x3d2877>
 10036a0: 83 c4 04                     	add	esp, 0x4
 10036a3: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 10036a6: 39 75 c8                     	cmp	dword ptr [ebp - 0x38], esi
 10036a9: 72 0c                        	jb	0x10036b7 <.text+0x407>
 10036ab: 8b 4d b4                     	mov	ecx, dword ptr [ebp - 0x4c]
 10036ae: 51                           	push	ecx
 10036af: e8 73 24 3d 00               	call	0x13d5b27 <.text+0x3d2877>
 10036b4: 83 c4 04                     	add	esp, 0x4
 10036b7: 8b 45 b0                     	mov	eax, dword ptr [ebp - 0x50]
 10036ba: 33 d2                        	xor	edx, edx
 10036bc: 50                           	push	eax
 10036bd: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
 10036c0: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
 10036c3: 66 89 55 b4                  	mov	word ptr [ebp - 0x4c], dx
 10036c7: e8 5b 24 3d 00               	call	0x13d5b27 <.text+0x3d2877>
 10036cc: 83 c4 04                     	add	esp, 0x4
 10036cf: b0 01                        	mov	al, 0x1
