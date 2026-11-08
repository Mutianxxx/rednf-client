
<stdin>:	file format elf32-i386

Disassembly of section .text:

012250c0 <.text>:
 12250c0: 11 06                        	adc	dword ptr [esi], eax
 12250c2: 33 c0                        	xor	eax, eax
 12250c4: 5e                           	pop	esi
 12250c5: 5d                           	pop	ebp
 12250c6: c3                           	ret
 12250c7: 83 f8 03                     	cmp	eax, 0x3
 12250ca: 75 1a                        	jne	0x12250e6 <.text+0x26>
 12250cc: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 12250d1: e8 0a 05 f8 ff               	call	0x11a55e0
 12250d6: 0f 57 c0                     	xorps	xmm0, xmm0
 12250d9: f3 0f 2a c0                  	cvtsi2ss	xmm0, eax
 12250dd: f3 0f 11 06                  	movss	dword ptr [esi], xmm0
 12250e1: 33 c0                        	xor	eax, eax
 12250e3: 5e                           	pop	esi
 12250e4: 5d                           	pop	ebp
 12250e5: c3                           	ret
 12250e6: 83 f8 04                     	cmp	eax, 0x4
 12250e9: 75 11                        	jne	0x12250fc <.text+0x3c>
 12250eb: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 12250f0: e8 2b 05 f8 ff               	call	0x11a5620
 12250f5: d9 1e                        	fstp	dword ptr [esi]
 12250f7: 33 c0                        	xor	eax, eax
 12250f9: 5e                           	pop	esi
 12250fa: 5d                           	pop	ebp
 12250fb: c3                           	ret
 12250fc: 83 f8 07                     	cmp	eax, 0x7
 12250ff: 75 40                        	jne	0x1225141 <.text+0x81>
 1225101: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225106: e8 55 05 f8 ff               	call	0x11a5660
 122510b: 50                           	push	eax
 122510c: e8 6f ae f7 ff               	call	0x119ff80
 1225111: 8b c8                        	mov	ecx, eax
 1225113: 83 c4 04                     	add	esp, 0x4
 1225116: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1225119: 8d a4 24 00 00 00 00         	lea	esp, [esp]
 1225120: 66 8b 11                     	mov	dx, word ptr [ecx]
 1225123: 83 c1 02                     	add	ecx, 0x2
 1225126: 66 85 d2                     	test	dx, dx
 1225129: 75 f5                        	jne	0x1225120 <.text+0x60>
 122512b: 2b ce                        	sub	ecx, esi
 122512d: d1 f9                        	sar	ecx
 122512f: 51                           	push	ecx
 1225130: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 1225133: 50                           	push	eax
 1225134: e8 f7 ae 1e ff               	call	0x410030
 1225139: b8 01 00 00 00               	mov	eax, 0x1
 122513e: 5e                           	pop	esi
 122513f: 5d                           	pop	ebp
 1225140: c3                           	ret
 1225141: 83 c8 ff                     	or	eax, -0x1
 1225144: 5e                           	pop	esi
 1225145: 5d                           	pop	ebp
 1225146: c3                           	ret
 1225147: cc                           	int3
 1225148: cc                           	int3
 1225149: cc                           	int3
 122514a: cc                           	int3
 122514b: cc                           	int3
 122514c: cc                           	int3
 122514d: cc                           	int3
 122514e: cc                           	int3
 122514f: cc                           	int3
 1225150: 55                           	push	ebp
 1225151: 8b ec                        	mov	ebp, esp
 1225153: 53                           	push	ebx
 1225154: 56                           	push	esi
 1225155: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122515a: 32 db                        	xor	bl, bl
 122515c: e8 4f 03 f8 ff               	call	0x11a54b0
 1225161: 83 e8 07                     	sub	eax, 0x7
 1225164: 74 60                        	je	0x12251c6 <.text+0x106>
 1225166: 83 e8 02                     	sub	eax, 0x2
 1225169: 0f 85 90 00 00 00            	jne	0x12251ff <.text+0x13f>
 122516f: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225174: e8 07 05 f8 ff               	call	0x11a5680
 1225179: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122517e: 8b f0                        	mov	esi, eax
 1225180: e8 2b 03 f8 ff               	call	0x11a54b0
 1225185: 83 f8 0a                     	cmp	eax, 0xa
 1225188: 75 75                        	jne	0x12251ff <.text+0x13f>
 122518a: 6a 00                        	push	0x0
 122518c: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225191: e8 8a 05 f8 ff               	call	0x11a5720
 1225196: 50                           	push	eax
 1225197: 56                           	push	esi
 1225198: b9 68 d4 d2 01               	mov	ecx, 0x1d2d468
 122519d: e8 2e 47 0a 00               	call	0x12c98d0 <.text+0xa4810>
 12251a2: 8b c8                        	mov	ecx, eax
 12251a4: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12251a7: 66 8b 11                     	mov	dx, word ptr [ecx]
 12251aa: 83 c1 02                     	add	ecx, 0x2
 12251ad: 66 85 d2                     	test	dx, dx
 12251b0: 75 f5                        	jne	0x12251a7 <.text+0xe7>
 12251b2: 2b ce                        	sub	ecx, esi
 12251b4: d1 f9                        	sar	ecx
 12251b6: 51                           	push	ecx
 12251b7: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 12251ba: 50                           	push	eax
 12251bb: e8 70 ae 1e ff               	call	0x410030
 12251c0: 5e                           	pop	esi
 12251c1: b0 01                        	mov	al, 0x1
 12251c3: 5b                           	pop	ebx
 12251c4: 5d                           	pop	ebp
 12251c5: c3                           	ret
 12251c6: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 12251cb: e8 90 04 f8 ff               	call	0x11a5660
 12251d0: 50                           	push	eax
 12251d1: e8 aa ad f7 ff               	call	0x119ff80
 12251d6: 8b c8                        	mov	ecx, eax
 12251d8: 83 c4 04                     	add	esp, 0x4
 12251db: 8d 71 02                     	lea	esi, [ecx + 0x2]
 12251de: 8b ff                        	mov	edi, edi
 12251e0: 66 8b 11                     	mov	dx, word ptr [ecx]
 12251e3: 83 c1 02                     	add	ecx, 0x2
 12251e6: 66 85 d2                     	test	dx, dx
 12251e9: 75 f5                        	jne	0x12251e0 <.text+0x120>
 12251eb: 2b ce                        	sub	ecx, esi
 12251ed: d1 f9                        	sar	ecx
 12251ef: 51                           	push	ecx
 12251f0: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 12251f3: 50                           	push	eax
 12251f4: e8 37 ae 1e ff               	call	0x410030
 12251f9: 5e                           	pop	esi
 12251fa: b0 01                        	mov	al, 0x1
 12251fc: 5b                           	pop	ebx
 12251fd: 5d                           	pop	ebp
 12251fe: c3                           	ret
 12251ff: 5e                           	pop	esi
 1225200: 8a c3                        	mov	al, bl
 1225202: 5b                           	pop	ebx
 1225203: 5d                           	pop	ebp
 1225204: c3                           	ret
 1225205: cc                           	int3
 1225206: cc                           	int3
 1225207: cc                           	int3
 1225208: cc                           	int3
 1225209: cc                           	int3
 122520a: cc                           	int3
 122520b: cc                           	int3
 122520c: cc                           	int3
 122520d: cc                           	int3
 122520e: cc                           	int3
 122520f: cc                           	int3
 1225210: 55                           	push	ebp
 1225211: 8b ec                        	mov	ebp, esp
 1225213: 6a ff                        	push	-0x1
 1225215: 68 a0 b7 4c 01               	push	0x14cb7a0
 122521a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1225220: 50                           	push	eax
 1225221: 83 ec 4c                     	sub	esp, 0x4c
 1225224: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1225229: 33 c5                        	xor	eax, ebp
 122522b: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 122522e: 53                           	push	ebx
 122522f: 56                           	push	esi
 1225230: 57                           	push	edi
 1225231: 50                           	push	eax
 1225232: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1225235: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 122523b: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 122523e: 89 45 a8                     	mov	dword ptr [ebp - 0x58], eax
 1225241: c6 45 af 01                  	mov	byte ptr [ebp - 0x51], 0x1
 1225245: bb 08 00 00 00               	mov	ebx, 0x8
 122524a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 1225250: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225255: e8 56 02 f8 ff               	call	0x11a54b0
 122525a: 83 f8 05                     	cmp	eax, 0x5
 122525d: 0f 84 14 01 00 00            	je	0x1225377 <.text+0x2b7>
 1225263: 32 c9                        	xor	cl, cl
 1225265: 88 4d af                     	mov	byte ptr [ebp - 0x51], cl
 1225268: 85 c0                        	test	eax, eax
 122526a: 0f 84 3e 01 00 00            	je	0x12253ae <.text+0x2ee>
 1225270: 80 7d 0c 01                  	cmp	byte ptr [ebp + 0xc], 0x1
 1225274: 75 da                        	jne	0x1225250 <.text+0x190>
 1225276: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1225279: 51                           	push	ecx
 122527a: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122527f: e8 cc 1e f8 ff               	call	0x11a7150
 1225284: 8b f0                        	mov	esi, eax
 1225286: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 1225289: 52                           	push	edx
 122528a: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122528f: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 1225296: e8 65 1e f8 ff               	call	0x11a7100
 122529b: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 122529f: 39 5e 18                     	cmp	dword ptr [esi + 0x18], ebx
 12252a2: 72 05                        	jb	0x12252a9 <.text+0x1e9>
 12252a4: 8b 76 04                     	mov	esi, dword ptr [esi + 0x4]
 12252a7: eb 03                        	jmp	0x12252ac <.text+0x1ec>
 12252a9: 83 c6 04                     	add	esi, 0x4
 12252ac: 39 58 18                     	cmp	dword ptr [eax + 0x18], ebx
 12252af: 72 05                        	jb	0x12252b6 <.text+0x1f6>
 12252b1: 8b 78 04                     	mov	edi, dword ptr [eax + 0x4]
 12252b4: eb 03                        	jmp	0x12252b9 <.text+0x1f9>
 12252b6: 8d 78 04                     	lea	edi, [eax + 0x4]
 12252b9: 56                           	push	esi
 12252ba: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 12252bf: e8 dc 04 f8 ff               	call	0x11a57a0
 12252c4: 50                           	push	eax
 12252c5: 57                           	push	edi
 12252c6: 68 f0 42 86 01               	push	0x18642f0
 12252cb: e8 20 ac f7 ff               	call	0x119fef0
 12252d0: 83 c4 04                     	add	esp, 0x4
 12252d3: 50                           	push	eax
 12252d4: 68 88 42 86 01               	push	0x1864288
 12252d9: e8 12 ac f7 ff               	call	0x119fef0
 12252de: 83 c4 04                     	add	esp, 0x4
 12252e1: 50                           	push	eax
 12252e2: 68 55 05 00 00               	push	0x555
 12252e7: 68 f0 42 86 01               	push	0x18642f0
 12252ec: e8 ff ab f7 ff               	call	0x119fef0
 12252f1: 83 c4 04                     	add	esp, 0x4
 12252f4: 50                           	push	eax
 12252f5: 68 c0 39 86 01               	push	0x18639c0
 12252fa: e8 f1 ab f7 ff               	call	0x119fef0
 12252ff: 83 c4 04                     	add	esp, 0x4
 1225302: 50                           	push	eax
 1225303: 33 f6                        	xor	esi, esi
 1225305: 56                           	push	esi
 1225306: e8 d5 d9 f7 ff               	call	0x11a2ce0
 122530b: 83 c4 24                     	add	esp, 0x24
 122530e: 39 5d e8                     	cmp	dword ptr [ebp - 0x18], ebx
 1225311: 72 0c                        	jb	0x122531f <.text+0x25f>
 1225313: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 1225316: 50                           	push	eax
 1225317: e8 0b 08 1b 00               	call	0x13d5b27 <.text+0x1b0a67>
 122531c: 83 c4 04                     	add	esp, 0x4
 122531f: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 1225322: 33 c9                        	xor	ecx, ecx
 1225324: bf 07 00 00 00               	mov	edi, 0x7
 1225329: 52                           	push	edx
 122532a: 89 7d e8                     	mov	dword ptr [ebp - 0x18], edi
 122532d: 89 75 e4                     	mov	dword ptr [ebp - 0x1c], esi
 1225330: 66 89 4d d4                  	mov	word ptr [ebp - 0x2c], cx
 1225334: e8 ee 07 1b 00               	call	0x13d5b27 <.text+0x1b0a67>
 1225339: 83 c4 04                     	add	esp, 0x4
 122533c: 89 75 d0                     	mov	dword ptr [ebp - 0x30], esi
 122533f: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 1225346: 39 5d c8                     	cmp	dword ptr [ebp - 0x38], ebx
 1225349: 72 0c                        	jb	0x1225357 <.text+0x297>
 122534b: 8b 45 b4                     	mov	eax, dword ptr [ebp - 0x4c]
 122534e: 50                           	push	eax
 122534f: e8 d3 07 1b 00               	call	0x13d5b27 <.text+0x1b0a67>
 1225354: 83 c4 04                     	add	esp, 0x4
 1225357: 8b 55 b0                     	mov	edx, dword ptr [ebp - 0x50]
 122535a: 33 c9                        	xor	ecx, ecx
 122535c: 52                           	push	edx
 122535d: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
 1225360: 89 75 c4                     	mov	dword ptr [ebp - 0x3c], esi
 1225363: 66 89 4d b4                  	mov	word ptr [ebp - 0x4c], cx
 1225367: e8 bb 07 1b 00               	call	0x13d5b27 <.text+0x1b0a67>
 122536c: 83 c4 04                     	add	esp, 0x4
 122536f: 89 75 b0                     	mov	dword ptr [ebp - 0x50], esi
 1225372: e9 d9 fe ff ff               	jmp	0x1225250 <.text+0x190>
 1225377: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 122537c: e8 bf 02 f8 ff               	call	0x11a5640
 1225381: 50                           	push	eax
 1225382: e8 f9 ab f7 ff               	call	0x119ff80
 1225387: 8b c8                        	mov	ecx, eax
 1225389: 83 c4 04                     	add	esp, 0x4
 122538c: 8d 71 02                     	lea	esi, [ecx + 0x2]
 122538f: 90                           	nop
 1225390: 66 8b 11                     	mov	dx, word ptr [ecx]
 1225393: 83 c1 02                     	add	ecx, 0x2
 1225396: 66 85 d2                     	test	dx, dx
 1225399: 75 f5                        	jne	0x1225390 <.text+0x2d0>
 122539b: 2b ce                        	sub	ecx, esi
 122539d: d1 f9                        	sar	ecx
 122539f: 51                           	push	ecx
 12253a0: 8b 4d a8                     	mov	ecx, dword ptr [ebp - 0x58]
 12253a3: 50                           	push	eax
 12253a4: e8 87 ac 1e ff               	call	0x410030
 12253a9: 8a 45 af                     	mov	al, byte ptr [ebp - 0x51]
 12253ac: eb 02                        	jmp	0x12253b0 <.text+0x2f0>
 12253ae: 8a c1                        	mov	al, cl
 12253b0: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 12253b3: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 12253ba: 59                           	pop	ecx
 12253bb: 5f                           	pop	edi
 12253bc: 5e                           	pop	esi
 12253bd: 5b                           	pop	ebx
 12253be: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 12253c1: 33 cd                        	xor	ecx, ebp
 12253c3: e8 10 1e 1b 00               	call	0x13d71d8 <.text+0x1b2118>
 12253c8: 8b e5                        	mov	esp, ebp
 12253ca: 5d                           	pop	ebp
 12253cb: c3                           	ret
 12253cc: cc                           	int3
 12253cd: cc                           	int3
 12253ce: cc                           	int3
 12253cf: cc                           	int3
 12253d0: 55                           	push	ebp
 12253d1: 8b ec                        	mov	ebp, esp
 12253d3: 6a ff                        	push	-0x1
 12253d5: 68 e0 b7 4c 01               	push	0x14cb7e0
 12253da: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 12253e0: 50                           	push	eax
 12253e1: 83 ec 50                     	sub	esp, 0x50
 12253e4: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 12253e9: 33 c5                        	xor	eax, ebp
 12253eb: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 12253ee: 53                           	push	ebx
 12253ef: 56                           	push	esi
 12253f0: 57                           	push	edi
 12253f1: 50                           	push	eax
 12253f2: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 12253f5: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 12253fb: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 12253fe: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 1225401: 89 7d a4                     	mov	dword ptr [ebp - 0x5c], edi
 1225404: 89 45 a8                     	mov	dword ptr [ebp - 0x58], eax
 1225407: c6 45 af 01                  	mov	byte ptr [ebp - 0x51], 0x1
 122540b: c6 07 01                     	mov	byte ptr [edi], 0x1
 122540e: bb 08 00 00 00               	mov	ebx, 0x8
 1225413: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225418: e8 93 00 f8 ff               	call	0x11a54b0
 122541d: 83 f8 07                     	cmp	eax, 0x7
 1225420: 0f 84 77 01 00 00            	je	0x122559d <.text+0x4dd>
 1225426: 83 f8 05                     	cmp	eax, 0x5
 1225429: 0f 84 a6 01 00 00            	je	0x12255d5 <.text+0x515>
 122542f: 83 f8 09                     	cmp	eax, 0x9
 1225432: 75 4c                        	jne	0x1225480 <.text+0x3c0>
 1225434: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225439: e8 42 02 f8 ff               	call	0x11a5680
 122543e: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225443: 8b f0                        	mov	esi, eax
 1225445: e8 66 00 f8 ff               	call	0x11a54b0
 122544a: 83 f8 0a                     	cmp	eax, 0xa
 122544d: 75 40                        	jne	0x122548f <.text+0x3cf>
 122544f: 6a 00                        	push	0x0
 1225451: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 1225456: e8 c5 02 f8 ff               	call	0x11a5720
 122545b: 50                           	push	eax
 122545c: 56                           	push	esi
 122545d: b9 68 d4 d2 01               	mov	ecx, 0x1d2d468
 1225462: e8 69 44 0a 00               	call	0x12c98d0 <.text+0xa4810>
 1225467: 8b c8                        	mov	ecx, eax
 1225469: 8d 71 02                     	lea	esi, [ecx + 0x2]
 122546c: 8d 64 24 00                  	lea	esp, [esp]
 1225470: 66 8b 11                     	mov	dx, word ptr [ecx]
 1225473: 83 c1 02                     	add	ecx, 0x2
 1225476: 66 85 d2                     	test	dx, dx
 1225479: 75 f5                        	jne	0x1225470 <.text+0x3b0>
 122547b: e9 40 01 00 00               	jmp	0x12255c0 <.text+0x500>
 1225480: 32 c9                        	xor	cl, cl
 1225482: 88 4d af                     	mov	byte ptr [ebp - 0x51], cl
 1225485: 88 0f                        	mov	byte ptr [edi], cl
 1225487: 85 c0                        	test	eax, eax
 1225489: 0f 84 7f 01 00 00            	je	0x122560e <.text+0x54e>
 122548f: 80 7d 10 01                  	cmp	byte ptr [ebp + 0x10], 0x1
 1225493: 0f 85 7a ff ff ff            	jne	0x1225413 <.text+0x353>
 1225499: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 122549c: 51                           	push	ecx
 122549d: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 12254a2: e8 a9 1c f8 ff               	call	0x11a7150
 12254a7: 8b f0                        	mov	esi, eax
 12254a9: 8d 55 b0                     	lea	edx, [ebp - 0x50]
 12254ac: 52                           	push	edx
 12254ad: b9 60 73 d2 01               	mov	ecx, 0x1d27360
 12254b2: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 12254b9: e8 42 1c f8 ff               	call	0x11a7100
 12254be: c6 45                        	<unknown>
