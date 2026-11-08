
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e9520 <.text>:
  4e9520: 55                           	push	ebp
  4e9521: 8b ec                        	mov	ebp, esp
  4e9523: 6a ff                        	push	-0x1
  4e9525: 68 01 34 41 01               	push	0x1413401
  4e952a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4e9530: 50                           	push	eax
  4e9531: 83 ec 24                     	sub	esp, 0x24
  4e9534: 53                           	push	ebx
  4e9535: 56                           	push	esi
  4e9536: 57                           	push	edi
  4e9537: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4e953c: 33 c5                        	xor	eax, ebp
  4e953e: 50                           	push	eax
  4e953f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4e9542: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4e9548: 8b f9                        	mov	edi, ecx
  4e954a: 89 7d e4                     	mov	dword ptr [ebp - 0x1c], edi
  4e954d: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
  4e9550: 53                           	push	ebx
  4e9551: e8 ca e9 ff ff               	call	0x4e7f20
  4e9556: 8b f0                        	mov	esi, eax
  4e9558: 85 f6                        	test	esi, esi
  4e955a: 0f 85 ec 01 00 00            	jne	0x4e974c <.text+0x22c>
  4e9560: 53                           	push	ebx
  4e9561: 8b cf                        	mov	ecx, edi
  4e9563: e8 28 ea ff ff               	call	0x4e7f90
  4e9568: 8b f8                        	mov	edi, eax
  4e956a: 85 ff                        	test	edi, edi
  4e956c: 0f 84 da 01 00 00            	je	0x4e974c <.text+0x22c>
  4e9572: 6a 0c                        	push	0xc
  4e9574: e8 a1 d5 ee 00               	call	0x13d6b1a <.text+0xeed5fa>
  4e9579: 83 c4 04                     	add	esp, 0x4
  4e957c: 3b c6                        	cmp	eax, esi
  4e957e: 74 0d                        	je	0x4e958d <.text+0x6d>
  4e9580: 89 30                        	mov	dword ptr [eax], esi
  4e9582: 89 70 04                     	mov	dword ptr [eax + 0x4], esi
  4e9585: 66 c7 40 08 01 00            	mov	word ptr [eax + 0x8], 0x1
  4e958b: 8b f0                        	mov	esi, eax
  4e958d: 89 75 e0                     	mov	dword ptr [ebp - 0x20], esi
  4e9590: 66 83 fb 64                  	cmp	bx, 0x64
  4e9594: 73 60                        	jae	0x4e95f6 <.text+0xd6>
  4e9596: 66 83 fb 18                  	cmp	bx, 0x18
  4e959a: 74 5a                        	je	0x4e95f6 <.text+0xd6>
  4e959c: 68 c4 03 00 00               	push	0x3c4
  4e95a1: e8 da 6d cc 00               	call	0x11b0380 <.text+0xcc6e60>
  4e95a6: 83 c4 04                     	add	esp, 0x4
  4e95a9: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  4e95ac: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
  4e95b3: 85 c0                        	test	eax, eax
  4e95b5: 0f 84 91 00 00 00            	je	0x4e964c <.text+0x12c>
  4e95bb: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e95be: 8b 15 e4 64 b5 01            	mov	edx, dword ptr [0x1b564e4]
  4e95c4: 8b 1a                        	mov	ebx, dword ptr [edx]
  4e95c6: 6a 00                        	push	0x0
  4e95c8: 8b c8                        	mov	ecx, eax
  4e95ca: 8d 50 02                     	lea	edx, [eax + 0x2]
  4e95cd: 52                           	push	edx
  4e95ce: 40                           	inc	eax
  4e95cf: 50                           	push	eax
  4e95d0: 51                           	push	ecx
  4e95d1: 51                           	push	ecx
  4e95d2: 68 30 78 57 01               	push	0x1577830
  4e95d7: e8 14 69 cb 00               	call	0x119fef0 <.text+0xcb69d0>
  4e95dc: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
  4e95e2: 83 c4 04                     	add	esp, 0x4
  4e95e5: 50                           	push	eax
  4e95e6: 8b 43 10                     	mov	eax, dword ptr [ebx + 0x10]
  4e95e9: ff d0                        	call	eax
  4e95eb: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
  4e95ee: 50                           	push	eax
  4e95ef: e8 0c ab cd 00               	call	0x11c4100 <.text+0xcdabe0>
  4e95f4: eb 58                        	jmp	0x4e964e <.text+0x12e>
  4e95f6: 68 c4 03 00 00               	push	0x3c4
  4e95fb: e8 80 6d cc 00               	call	0x11b0380 <.text+0xcc6e60>
  4e9600: 83 c4 04                     	add	esp, 0x4
  4e9603: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  4e9606: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  4e960d: 85 c0                        	test	eax, eax
  4e960f: 74 3b                        	je	0x4e964c <.text+0x12c>
  4e9611: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e9614: 8b 15 e4 64 b5 01            	mov	edx, dword ptr [0x1b564e4]
  4e961a: 8b 1a                        	mov	ebx, dword ptr [edx]
  4e961c: 6a 00                        	push	0x0
  4e961e: 8b c8                        	mov	ecx, eax
  4e9620: 8d 50 02                     	lea	edx, [eax + 0x2]
  4e9623: 52                           	push	edx
  4e9624: 40                           	inc	eax
  4e9625: 50                           	push	eax
  4e9626: 51                           	push	ecx
  4e9627: 51                           	push	ecx
  4e9628: 68 b0 77 57 01               	push	0x15777b0
  4e962d: e8 be 68 cb 00               	call	0x119fef0 <.text+0xcb69d0>
  4e9632: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
  4e9638: 83 c4 04                     	add	esp, 0x4
  4e963b: 50                           	push	eax
  4e963c: 8b 43 10                     	mov	eax, dword ptr [ebx + 0x10]
  4e963f: ff d0                        	call	eax
  4e9641: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
  4e9644: 50                           	push	eax
  4e9645: e8 b6 aa cd 00               	call	0x11c4100 <.text+0xcdabe0>
  4e964a: eb 02                        	jmp	0x4e964e <.text+0x12e>
  4e964c: 33 c0                        	xor	eax, eax
  4e964e: 83 cb ff                     	or	ebx, -0x1
  4e9651: 6a 01                        	push	0x1
  4e9653: 8b c8                        	mov	ecx, eax
  4e9655: 89 06                        	mov	dword ptr [esi], eax
  4e9657: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4e965a: e8 01 4d cd 00               	call	0x11be360 <.text+0xcd4e40>
  4e965f: 68 bc 02 00 00               	push	0x2bc
  4e9664: e8 17 6d cc 00               	call	0x11b0380 <.text+0xcc6e60>
  4e9669: 83 c4 04                     	add	esp, 0x4
  4e966c: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  4e966f: c7 45 fc 02 00 00 00         	mov	dword ptr [ebp - 0x4], 0x2
  4e9676: 85 c0                        	test	eax, eax
  4e9678: 74 09                        	je	0x4e9683 <.text+0x163>
  4e967a: 8b c8                        	mov	ecx, eax
  4e967c: e8 7f 84 ce 00               	call	0x11d1b00 <.text+0xce85e0>
  4e9681: eb 02                        	jmp	0x4e9685 <.text+0x165>
  4e9683: 33 c0                        	xor	eax, eax
  4e9685: 8b 0e                        	mov	ecx, dword ptr [esi]
  4e9687: 51                           	push	ecx
  4e9688: 8b c8                        	mov	ecx, eax
  4e968a: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4e968d: 89 46 04                     	mov	dword ptr [esi + 0x4], eax
  4e9690: e8 ab 76 ce 00               	call	0x11d0d40 <.text+0xce7820>
  4e9695: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e9698: 6a 01                        	push	0x1
  4e969a: e8 e1 76 ce 00               	call	0x11d0d80 <.text+0xce7860>
  4e969f: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e96a2: 68 be 00 00 00               	push	0xbe
  4e96a7: e8 34 7a ce 00               	call	0x11d10e0 <.text+0xce7bc0>
  4e96ac: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e96af: 68 98 3a 00 00               	push	0x3a98
  4e96b4: e8 77 77 ce 00               	call	0x11d0e30 <.text+0xce7910>
  4e96b9: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e96bc: 6a 02                        	push	0x2
  4e96be: e8 4d 77 ce 00               	call	0x11d0e10 <.text+0xce78f0>
  4e96c3: 83 7f 18 00                  	cmp	dword ptr [edi + 0x18], 0x0
  4e96c7: 74 62                        	je	0x4e972b <.text+0x20b>
  4e96c9: 8d 55 e8                     	lea	edx, [ebp - 0x18]
  4e96cc: 52                           	push	edx
  4e96cd: 8d 4f 08                     	lea	ecx, [edi + 0x8]
  4e96d0: c6 46 09 01                  	mov	byte ptr [esi + 0x9], 0x1
  4e96d4: e8 f7 77 ce 00               	call	0x11d0ed0 <.text+0xce79b0>
  4e96d9: 8b 5d e8                     	mov	ebx, dword ptr [ebp - 0x18]
  4e96dc: 85 db                        	test	ebx, ebx
  4e96de: 74 12                        	je	0x4e96f2 <.text+0x1d2>
  4e96e0: 8b 03                        	mov	eax, dword ptr [ebx]
  4e96e2: 85 c0                        	test	eax, eax
  4e96e4: 74 0c                        	je	0x4e96f2 <.text+0x1d2>
  4e96e6: 8b 7d f0                     	mov	edi, dword ptr [ebp - 0x10]
  4e96e9: 85 ff                        	test	edi, edi
  4e96eb: 74 05                        	je	0x4e96f2 <.text+0x1d2>
  4e96ed: 3b 78 04                     	cmp	edi, dword ptr [eax + 0x4]
  4e96f0: 75 05                        	jne	0x4e96f7 <.text+0x1d7>
  4e96f2: e8 b0 d6 ee 00               	call	0x13d6da7 <.text+0xeed887>
  4e96f7: 0f b6 47 08                  	movzx	eax, byte ptr [edi + 0x8]
  4e96fb: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e96fe: 50                           	push	eax
  4e96ff: e8 9c 76 ce 00               	call	0x11d0da0 <.text+0xce7880>
  4e9704: 8b 03                        	mov	eax, dword ptr [ebx]
  4e9706: 85 c0                        	test	eax, eax
  4e9708: 74 e8                        	je	0x4e96f2 <.text+0x1d2>
  4e970a: 3b 78 04                     	cmp	edi, dword ptr [eax + 0x4]
  4e970d: 75 05                        	jne	0x4e9714 <.text+0x1f4>
  4e970f: e8 93 d6 ee 00               	call	0x13d6da7 <.text+0xeed887>
  4e9714: 83 7f 24 08                  	cmp	dword ptr [edi + 0x24], 0x8
  4e9718: 72 05                        	jb	0x4e971f <.text+0x1ff>
  4e971a: 8b 7f 10                     	mov	edi, dword ptr [edi + 0x10]
  4e971d: eb 03                        	jmp	0x4e9722 <.text+0x202>
  4e971f: 83 c7 10                     	add	edi, 0x10
  4e9722: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  4e9725: 57                           	push	edi
  4e9726: e8 a5 79 ce 00               	call	0x11d10d0 <.text+0xce7bb0>
  4e972b: 66 8b 4d 08                  	mov	cx, word ptr [ebp + 0x8]
  4e972f: 66 89 4d ec                  	mov	word ptr [ebp - 0x14], cx
  4e9733: 8b 4d e4                     	mov	ecx, dword ptr [ebp - 0x1c]
  4e9736: 8d 55 ec                     	lea	edx, [ebp - 0x14]
  4e9739: 52                           	push	edx
  4e973a: 8d 45 d0                     	lea	eax, [ebp - 0x30]
  4e973d: 50                           	push	eax
  4e973e: 83 c1 04                     	add	ecx, 0x4
  4e9741: 89 75 f0                     	mov	dword ptr [ebp - 0x10], esi
  4e9744: e8 37 f9 ff ff               	call	0x4e9080
  4e9749: 8b 75 e0                     	mov	esi, dword ptr [ebp - 0x20]
  4e974c: 8b c6                        	mov	eax, esi
  4e974e: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4e9751: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4e9758: 59                           	pop	ecx
  4e9759: 5f                           	pop	edi
  4e975a: 5e                           	pop	esi
  4e975b: 5b                           	pop	ebx
  4e975c: 8b e5                        	mov	esp, ebp
  4e975e: 5d                           	pop	ebp
  4e975f: c2 04 00                     	ret	0x4
