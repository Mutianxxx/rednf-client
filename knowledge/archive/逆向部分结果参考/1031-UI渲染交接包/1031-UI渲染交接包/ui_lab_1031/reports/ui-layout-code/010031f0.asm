
<stdin>:	file format elf32-i386

Disassembly of section .text:

010031f0 <.text>:
 10031f0: 55                           	push	ebp
 10031f1: 8b ec                        	mov	ebp, esp
 10031f3: 6a ff                        	push	-0x1
 10031f5: 68 62 59 42 01               	push	0x1425962
 10031fa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1003200: 50                           	push	eax
 1003201: 51                           	push	ecx
 1003202: 56                           	push	esi
 1003203: 57                           	push	edi
 1003204: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 1003209: 33 c5                        	xor	eax, ebp
 100320b: 50                           	push	eax
 100320c: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 100320f: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 1003215: 8b f9                        	mov	edi, ecx
 1003217: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 100321a: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 100321d: 3b f1                        	cmp	esi, ecx
 100321f: 73 50                        	jae	0x1003271 <.text+0x81>
 1003221: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
 1003224: 3b c6                        	cmp	eax, esi
 1003226: 77 49                        	ja	0x1003271 <.text+0x81>
 1003228: 2b f0                        	sub	esi, eax
 100322a: b8 93 24 49 92               	mov	eax, 0x92492493
 100322f: f7 ee                        	imul	esi
 1003231: 03 d6                        	add	edx, esi
 1003233: c1 fa 05                     	sar	edx, 0x5
 1003236: 8b f2                        	mov	esi, edx
 1003238: c1 ee 1f                     	shr	esi, 0x1f
 100323b: 03 f2                        	add	esi, edx
 100323d: 3b 4f 0c                     	cmp	ecx, dword ptr [edi + 0xc]
 1003240: 75 09                        	jne	0x100324b <.text+0x5b>
 1003242: 6a 01                        	push	0x1
 1003244: 8b cf                        	mov	ecx, edi
 1003246: e8 15 ff ff ff               	call	0x1003160
 100324b: 8b 4f 04                     	mov	ecx, dword ptr [edi + 0x4]
 100324e: 8d 04 f5 00 00 00 00         	lea	eax, [8*esi]
 1003255: 2b c6                        	sub	eax, esi
 1003257: 8d 04 c1                     	lea	eax, [ecx + 8*eax]
 100325a: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 100325d: 89 4d 08                     	mov	dword ptr [ebp + 0x8], ecx
 1003260: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 1003263: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 100326a: 85 c9                        	test	ecx, ecx
 100326c: 74 2b                        	je	0x1003299 <.text+0xa9>
 100326e: 50                           	push	eax
 100326f: eb 23                        	jmp	0x1003294 <.text+0xa4>
 1003271: 3b 4f 0c                     	cmp	ecx, dword ptr [edi + 0xc]
 1003274: 75 09                        	jne	0x100327f <.text+0x8f>
 1003276: 6a 01                        	push	0x1
 1003278: 8b cf                        	mov	ecx, edi
 100327a: e8 e1 fe ff ff               	call	0x1003160
 100327f: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
 1003282: 89 4d 08                     	mov	dword ptr [ebp + 0x8], ecx
 1003285: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 1003288: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 100328f: 85 c9                        	test	ecx, ecx
 1003291: 74 06                        	je	0x1003299 <.text+0xa9>
 1003293: 56                           	push	esi
 1003294: e8 07 fb ff ff               	call	0x1002da0
 1003299: 83 47 08 38                  	add	dword ptr [edi + 0x8], 0x38
 100329d: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 10032a0: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 10032a7: 59                           	pop	ecx
 10032a8: 5f                           	pop	edi
 10032a9: 5e                           	pop	esi
 10032aa: 8b e5                        	mov	esp, ebp
 10032ac: 5d                           	pop	ebp
 10032ad: c2 04 00                     	ret	0x4
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
 10032f1: 72 08                        	jb	0x10032fb <.text+0x10b>
 10032f3: 8b 80 e0 03 00 00            	mov	eax, dword ptr [eax + 0x3e0]
 10032f9: eb 05                        	jmp	0x1003300 <.text+0x110>
 10032fb: 05 e0 03 00 00               	add	eax, 0x3e0
 1003300: 50                           	push	eax
 1003301: 68 78 21 56 01               	push	0x1562178
 1003306: e8 e5 cb 19 00               	call	0x119fef0 <.text+0x19cd00>
 100330b: 83 c4 04                     	add	esp, 0x4
 100330e: 50                           	push	eax
 100330f: e8 0c 03 22 00               	call	0x1223620 <.text+0x220430>
 1003314: 83 c4 08                     	add	esp, 0x8
 1003317: 84 c0                        	test	al, al
 1003319: 75 1c                        	jne	0x1003337 <.text+0x147>
 100331b: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 100331e: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 1003325: 59                           	pop	ecx
 1003326: 5f                           	pop	edi
 1003327: 5e                           	pop	esi
 1003328: 5b                           	pop	ebx
 1003329: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 100332c: 33 cd                        	xor	ecx, ebp
 100332e: e8 a5 3e 3d 00               	call	0x13d71d8 <.text+0x3d3fe8>
 1003333: 8b e5                        	mov	esp, ebp
 1003335: 5d                           	pop	ebp
 1003336: c3                           	ret
 1003337: 33 db                        	xor	ebx, ebx
 1003339: 56                           	push	esi
 100333a: 89 5d b0                     	mov	dword ptr [ebp - 0x50], ebx
 100333d: e8 d8 37 3d 00               	call	0x13d6b1a <.text+0x3d392a>
 1003342: 83 c4 04                     	add	esp, 0x4
 1003345: 3b c3                        	cmp	eax, ebx
 1003347: 0f 84 ef 03 00 00            	je	0x100373c <.text+0x54c>
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
