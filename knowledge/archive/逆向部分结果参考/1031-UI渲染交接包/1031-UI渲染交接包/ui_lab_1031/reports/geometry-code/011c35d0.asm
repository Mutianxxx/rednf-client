
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c35d0 <.text>:
 11c35d0: 55                           	push	ebp
 11c35d1: 8b ec                        	mov	ebp, esp
 11c35d3: 51                           	push	ecx
 11c35d4: 56                           	push	esi
 11c35d5: 8b f1                        	mov	esi, ecx
 11c35d7: 80 7e 0c 00                  	cmp	byte ptr [esi + 0xc], 0x0
 11c35db: 0f 84 3d 09 00 00            	je	0x11c3f1e <.text+0x94e>
 11c35e1: 83 be 4c 03 00 00 00         	cmp	dword ptr [esi + 0x34c], 0x0
 11c35e8: 76 0a                        	jbe	0x11c35f4 <.text+0x24>
 11c35ea: e8 91 fb ff ff               	call	0x11c3180
 11c35ef: 5e                           	pop	esi
 11c35f0: 8b e5                        	mov	esp, ebp
 11c35f2: 5d                           	pop	ebp
 11c35f3: c3                           	ret
 11c35f4: 80 7e 0d 00                  	cmp	byte ptr [esi + 0xd], 0x0
 11c35f8: 53                           	push	ebx
 11c35f9: 57                           	push	edi
 11c35fa: 0f 84 a9 07 00 00            	je	0x11c3da9 <.text+0x7d9>
 11c3600: e8 bb a9 ff ff               	call	0x11bdfc0
 11c3605: 84 c0                        	test	al, al
 11c3607: 74 40                        	je	0x11c3649 <.text+0x79>
 11c3609: 83 be e0 02 00 00 00         	cmp	dword ptr [esi + 0x2e0], 0x0
 11c3610: 74 37                        	je	0x11c3649 <.text+0x79>
 11c3612: 83 be e4 02 00 00 08         	cmp	dword ptr [esi + 0x2e4], 0x8
 11c3619: 72 08                        	jb	0x11c3623 <.text+0x53>
 11c361b: 8b 86 d0 02 00 00            	mov	eax, dword ptr [esi + 0x2d0]
 11c3621: eb 06                        	jmp	0x11c3629 <.text+0x59>
 11c3623: 8d 86 d0 02 00 00            	lea	eax, [esi + 0x2d0]
 11c3629: 6a 00                        	push	0x0
 11c362b: 6a 00                        	push	0x0
 11c362d: 6a ff                        	push	-0x1
 11c362f: 68 ff ff 00 00               	push	0xffff
 11c3634: 6a 00                        	push	0x0
 11c3636: 6a 00                        	push	0x0
 11c3638: 6a 00                        	push	0x0
 11c363a: 6a 00                        	push	0x0
 11c363c: 50                           	push	eax
 11c363d: e8 6e 7a fd ff               	call	0x119b0b0
 11c3642: 8b c8                        	mov	ecx, eax
 11c3644: e8 47 62 fd ff               	call	0x1199890
 11c3649: 8b ce                        	mov	ecx, esi
 11c364b: e8 a0 aa ff ff               	call	0x11be0f0
 11c3650: 84 c0                        	test	al, al
 11c3652: 0f 84 85 02 00 00            	je	0x11c38dd <.text+0x30d>
 11c3658: 83 be 54 03 00 00 01         	cmp	dword ptr [esi + 0x354], 0x1
 11c365f: 8b 86 64 03 00 00            	mov	eax, dword ptr [esi + 0x364]
 11c3665: 8b be 74 03 00 00            	mov	edi, dword ptr [esi + 0x374]
 11c366b: 8b 9e 84 03 00 00            	mov	ebx, dword ptr [esi + 0x384]
 11c3671: 0f 57 c0                     	xorps	xmm0, xmm0
 11c3674: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11c3677: 75 71                        	jne	0x11c36ea <.text+0x11a>
 11c3679: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11c367f: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c3682: 0f b6 c0                     	movzx	eax, al
 11c3685: 83 ec 08                     	sub	esp, 0x8
 11c3688: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c368e: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c3693: c1 e0 18                     	shl	eax, 0x18
 11c3696: 0d ff ff ff 00               	or	eax, 0xffffff
 11c369b: 50                           	push	eax
 11c369c: 8b 46 14                     	mov	eax, dword ptr [esi + 0x14]
 11c369f: 83 ec 0c                     	sub	esp, 0xc
 11c36a2: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c36a8: f3 0f 10 86 90 03 00 00      	movss	xmm0, dword ptr [esi + 0x390]
 11c36b0: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c36b6: f3 0f 10 86 8c 03 00 00      	movss	xmm0, dword ptr [esi + 0x38c]
 11c36be: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c36c3: 51                           	push	ecx
 11c36c4: 03 d3                        	add	edx, ebx
 11c36c6: 52                           	push	edx
 11c36c7: 03 c7                        	add	eax, edi
 11c36c9: 50                           	push	eax
 11c36ca: 8b ce                        	mov	ecx, esi
 11c36cc: e8 3f ad ff ff               	call	0x11be410
 11c36d1: 8b c8                        	mov	ecx, eax
 11c36d3: e8 08 0b ff ff               	call	0x11b41e0
 11c36d8: 6a 00                        	push	0x0
 11c36da: 6a 02                        	push	0x2
 11c36dc: e8 7f fd fe ff               	call	0x11b3460
 11c36e1: 0f 57 c0                     	xorps	xmm0, xmm0
 11c36e4: 8b 45 fc                     	mov	eax, dword ptr [ebp - 0x4]
 11c36e7: 83 c4 08                     	add	esp, 0x8
 11c36ea: 83 ec 08                     	sub	esp, 0x8
 11c36ed: 80 be 58 03 00 00 00         	cmp	byte ptr [esi + 0x358], 0x0
 11c36f4: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c36fa: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c36ff: 0f 84 86 00 00 00            	je	0x11c378b <.text+0x1bb>
 11c3705: 8b 96 b8 02 00 00            	mov	edx, dword ptr [esi + 0x2b8]
 11c370b: 0f b6 c8                     	movzx	ecx, al
 11c370e: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
 11c3711: c1 e1 18                     	shl	ecx, 0x18
 11c3714: 81 c9 ff ff ff 00            	or	ecx, 0xffffff
 11c371a: 51                           	push	ecx
 11c371b: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c371e: 83 ec 0c                     	sub	esp, 0xc
 11c3721: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c3727: f3 0f 10 86 90 03 00 00      	movss	xmm0, dword ptr [esi + 0x390]
 11c372f: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c3735: f3 0f 10 86 8c 03 00 00      	movss	xmm0, dword ptr [esi + 0x38c]
 11c373d: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c3742: 52                           	push	edx
 11c3743: 03 c3                        	add	eax, ebx
 11c3745: 03 cf                        	add	ecx, edi
 11c3747: 50                           	push	eax
 11c3748: 51                           	push	ecx
 11c3749: 8b ce                        	mov	ecx, esi
 11c374b: e8 c0 ac ff ff               	call	0x11be410
 11c3750: 8b c8                        	mov	ecx, eax
 11c3752: e8 89 0a ff ff               	call	0x11b41e0
 11c3757: 6a 00                        	push	0x0
 11c3759: 6a 02                        	push	0x2
 11c375b: e8 00 fd fe ff               	call	0x11b3460
 11c3760: 8b 96 bc 02 00 00            	mov	edx, dword ptr [esi + 0x2bc]
 11c3766: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
 11c3769: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c376c: 83 c4 08                     	add	esp, 0x8
 11c376f: 52                           	push	edx
 11c3770: 03 c3                        	add	eax, ebx
 11c3772: 03 cf                        	add	ecx, edi
 11c3774: 50                           	push	eax
 11c3775: 51                           	push	ecx
 11c3776: 8b ce                        	mov	ecx, esi
 11c3778: e8 93 ac ff ff               	call	0x11be410
 11c377d: 8b c8                        	mov	ecx, eax
 11c377f: e8 cc 01 ff ff               	call	0x11b3950
 11c3784: e8 e7 fd fe ff               	call	0x11b3570
 11c3789: eb 52                        	jmp	0x11c37dd <.text+0x20d>
 11c378b: 8b 4e 18                     	mov	ecx, dword ptr [esi + 0x18]
 11c378e: 0f b6 d0                     	movzx	edx, al
 11c3791: 8b 86 bc 02 00 00            	mov	eax, dword ptr [esi + 0x2bc]
 11c3797: c1 e2 18                     	shl	edx, 0x18
 11c379a: 81 ca ff ff ff 00            	or	edx, 0xffffff
 11c37a0: 52                           	push	edx
 11c37a1: 8b 56 14                     	mov	edx, dword ptr [esi + 0x14]
 11c37a4: 83 ec 0c                     	sub	esp, 0xc
 11c37a7: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11c37ad: f3 0f 10 86 90 03 00 00      	movss	xmm0, dword ptr [esi + 0x390]
 11c37b5: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11c37bb: f3 0f 10 86 8c 03 00 00      	movss	xmm0, dword ptr [esi + 0x38c]
 11c37c3: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11c37c8: 50                           	push	eax
 11c37c9: 03 cb                        	add	ecx, ebx
 11c37cb: 51                           	push	ecx
 11c37cc: 03 d7                        	add	edx, edi
 11c37ce: 52                           	push	edx
 11c37cf: 8b ce                        	mov	ecx, esi
 11c37d1: e8 3a ac ff ff               	call	0x11be410
 11c37d6: 8b c8                        	mov	ecx, eax
 11c37d8: e8 03 0a ff ff               	call	0x11b41e0
 11c37dd: 83 be                        	<unknown>
 11c37df: 54                           	push	esp
