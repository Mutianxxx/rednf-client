
<stdin>:	file format elf32-i386

Disassembly of section .text:

01324680 <.text>:
 1324680: 87 01                        	xchg	dword ptr [ecx], eax
 1324682: e8 69 b8 e7 ff               	call	0x119fef0
 1324687: 50                           	push	eax
 1324688: 8d 8d 1c fe ff ff            	lea	ecx, [ebp - 0x1e4]
 132468e: 51                           	push	ecx
 132468f: e8 7c ef e7 ff               	call	0x11a3610
 1324694: 83 c4 0c                     	add	esp, 0xc
 1324697: 84 c0                        	test	al, al
 1324699: 74 12                        	je	0x13246ad <.text+0x2d>
 132469b: 8b 95 18 fe ff ff            	mov	edx, dword ptr [ebp - 0x1e8]
 13246a1: c7 42 14 01 00 00 00         	mov	dword ptr [edx + 0x14], 0x1
 13246a8: e9 80 49 00 00               	jmp	0x132902d <.text+0x49ad>
 13246ad: 68 c8 ba 88 01               	push	0x188bac8
 13246b2: e8 39 b8 e7 ff               	call	0x119fef0
 13246b7: 50                           	push	eax
 13246b8: 8d 85 1c fe ff ff            	lea	eax, [ebp - 0x1e4]
 13246be: 50                           	push	eax
 13246bf: e8 4c ef e7 ff               	call	0x11a3610
 13246c4: 83 c4 0c                     	add	esp, 0xc
 13246c7: 84 c0                        	test	al, al
 13246c9: 0f 84 5e 49 00 00            	je	0x132902d <.text+0x49ad>
 13246cf: 8b 8d 18 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e8]
 13246d5: c7 41 14 02 00 00 00         	mov	dword ptr [ecx + 0x14], 0x2
 13246dc: e9 4c 49 00 00               	jmp	0x132902d <.text+0x49ad>
 13246e1: 68 fc 4b 88 01               	push	0x1884bfc
 13246e6: e8 05 b8 e7 ff               	call	0x119fef0
 13246eb: 50                           	push	eax
 13246ec: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 13246ef: 52                           	push	edx
 13246f0: e8 8b d6 0d ff               	call	0x401d80
 13246f5: 83 c4 0c                     	add	esp, 0xc
 13246f8: 84 c0                        	test	al, al
 13246fa: 74 1b                        	je	0x1324717 <.text+0x97>
 13246fc: 6a 00                        	push	0x0
 13246fe: e8 5d ef ef ff               	call	0x1223660
 1324703: 8b 8d 18 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e8]
 1324709: 83 c4 04                     	add	esp, 0x4
 132470c: 89 81 0c 05 00 00            	mov	dword ptr [ecx + 0x50c], eax
 1324712: e9 16 49 00 00               	jmp	0x132902d <.text+0x49ad>
 1324717: 68 14 47 88 01               	push	0x1884714
 132471c: e8 cf b7 e7 ff               	call	0x119fef0
 1324721: 50                           	push	eax
 1324722: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 1324725: 52                           	push	edx
 1324726: e8 55 d6 0d ff               	call	0x401d80
 132472b: 83 c4 0c                     	add	esp, 0xc
 132472e: 84 c0                        	test	al, al
 1324730: 0f 84 7f 01 00 00            	je	0x13248b5 <.text+0x235>
 1324736: 8b 8d 18 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e8]
 132473c: 83 c1 18                     	add	ecx, 0x18
 132473f: 89 8d ec fd ff ff            	mov	dword ptr [ebp - 0x214], ecx
 1324745: e8 96 7a fa ff               	call	0x12cc1e0
 132474a: 8d 85 1c fe ff ff            	lea	eax, [ebp - 0x1e4]
 1324750: 50                           	push	eax
 1324751: e8 6a f1 ef ff               	call	0x12238c0
 1324756: 83 c4 04                     	add	esp, 0x4
 1324759: 8d 8d 1c fe ff ff            	lea	ecx, [ebp - 0x1e4]
 132475f: e8 0c ee e7 ff               	call	0x11a3570
 1324764: 8b c8                        	mov	ecx, eax
 1324766: e8 15 ee e7 ff               	call	0x11a3580
 132476b: 33 ff                        	xor	edi, edi
 132476d: 8d 70 ff                     	lea	esi, [eax - 0x1]
 1324770: 89 bd fc fd ff ff            	mov	dword ptr [ebp - 0x204], edi
 1324776: c7 85 f4 fd ff ff ff ff ff ff	mov	dword ptr [ebp - 0x20c], 0xffffffff
 1324780: 89 b5 bc fd ff ff            	mov	dword ptr [ebp - 0x244], esi
 1324786: 3b f7                        	cmp	esi, edi
 1324788: 0f 8e 9f 48 00 00            	jle	0x132902d <.text+0x49ad>
 132478e: 8b ff                        	mov	edi, edi
 1324790: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1324793: e8 f8 da d8 ff               	call	0x10b2290
 1324798: 8b 8d 1c fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e4]
 132479e: 8d 14 79                     	lea	edx, [ecx + 2*edi]
 13247a1: 6a 02                        	push	0x2
 13247a3: 52                           	push	edx
 13247a4: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 13247a7: c6 45 fc 06                  	mov	byte ptr [ebp - 0x4], 0x6
 13247ab: e8 80 bf 0e ff               	call	0x410730
 13247b0: 8b 45 c8                     	mov	eax, dword ptr [ebp - 0x38]
 13247b3: 8b 55 b4                     	mov	edx, dword ptr [ebp - 0x4c]
 13247b6: 8b ca                        	mov	ecx, edx
 13247b8: 83 f8 08                     	cmp	eax, 0x8
 13247bb: 73 03                        	jae	0x13247c0 <.text+0x140>
 13247bd: 8d 4d b4                     	lea	ecx, [ebp - 0x4c]
 13247c0: 66 83 39 0d                  	cmp	word ptr [ecx], 0xd
 13247c4: 0f 84 c4 00 00 00            	je	0x132488e <.text+0x20e>
 13247ca: 8b ca                        	mov	ecx, edx
 13247cc: 83 f8 08                     	cmp	eax, 0x8
 13247cf: 73 03                        	jae	0x13247d4 <.text+0x154>
 13247d1: 8d 4d b4                     	lea	ecx, [ebp - 0x4c]
 13247d4: 66 83 39 0a                  	cmp	word ptr [ecx], 0xa
 13247d8: 0f 84 b0 00 00 00            	je	0x132488e <.text+0x20e>
 13247de: 83 f8 08                     	cmp	eax, 0x8
 13247e1: 8b c2                        	mov	eax, edx
 13247e3: 73 03                        	jae	0x13247e8 <.text+0x168>
 13247e5: 8d 45 b4                     	lea	eax, [ebp - 0x4c]
 13247e8: 66 83 38 20                  	cmp	word ptr [eax], 0x20
 13247ec: 0f 84 9c 00 00 00            	je	0x132488e <.text+0x20e>
 13247f2: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 13247f5: 33 f6                        	xor	esi, esi
 13247f7: e8 24 d4 0d ff               	call	0x401c20
 13247fc: 0f b7 10                     	movzx	edx, word ptr [eax]
 13247ff: 90                           	nop
 1324800: 8b 0c b5 98 1b da 01         	mov	ecx, dword ptr [4*esi + 0x1da1b98]
 1324807: 66 3b 11                     	cmp	dx, word ptr [ecx]
 132480a: 75 0a                        	jne	0x1324816 <.text+0x196>
 132480c: 66 8b 58 02                  	mov	bx, word ptr [eax + 0x2]
 1324810: 66 3b 59 02                  	cmp	bx, word ptr [ecx + 0x2]
 1324814: 74 06                        	je	0x132481c <.text+0x19c>
 1324816: 46                           	inc	esi
 1324817: 83 fe 10                     	cmp	esi, 0x10
 132481a: 7c e4                        	jl	0x1324800 <.text+0x180>
 132481c: 83 fe 10                     	cmp	esi, 0x10
 132481f: 75 1b                        	jne	0x132483c <.text+0x1bc>
 1324821: ff 85 fc fd ff ff            	inc	dword ptr [ebp - 0x204]
 1324827: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 132482a: 47                           	inc	edi
 132482b: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
 132482f: e8 bc 3d 13 ff               	call	0x4585f0
 1324834: 8b b5 bc fd ff ff            	mov	esi, dword ptr [ebp - 0x244]
 132483a: eb 5f                        	jmp	0x132489b <.text+0x21b>
 132483c: 8b 85 f4 fd ff ff            	mov	eax, dword ptr [ebp - 0x20c]
 1324842: 83 f8 ff                     	cmp	eax, -0x1
 1324845: 75 08                        	jne	0x132484f <.text+0x1cf>
 1324847: 89 b5 f4 fd ff ff            	mov	dword ptr [ebp - 0x20c], esi
 132484d: eb 28                        	jmp	0x1324877 <.text+0x1f7>
 132484f: 8b 8d ec fd ff ff            	mov	ecx, dword ptr [ebp - 0x214]
 1324855: 89 85 70 fc ff ff            	mov	dword ptr [ebp - 0x390], eax
 132485b: 8d 85 70 fc ff ff            	lea	eax, [ebp - 0x390]
 1324861: 50                           	push	eax
 1324862: 89 b5 74 fc ff ff            	mov	dword ptr [ebp - 0x38c], esi
 1324868: e8 c3 bd 1f ff               	call	0x520630
 132486d: c7 85 f4 fd ff ff ff ff ff ff	mov	dword ptr [ebp - 0x20c], 0xffffffff
 1324877: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 132487a: 83 c7 02                     	add	edi, 0x2
 132487d: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
 1324881: e8 6a 3d 13 ff               	call	0x4585f0
 1324886: 8b b5 bc fd ff ff            	mov	esi, dword ptr [ebp - 0x244]
 132488c: eb 0d                        	jmp	0x132489b <.text+0x21b>
 132488e: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1324891: 47                           	inc	edi
 1324892: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
 1324896: e8 55 3d 13 ff               	call	0x4585f0
 132489b: 3b fe                        	cmp	edi, esi
 132489d: 0f 8c ed fe ff ff            	jl	0x1324790 <.text+0x110>
 13248a3: 83 bd fc fd ff ff 00         	cmp	dword ptr [ebp - 0x204], 0x0
 13248aa: 0f 85 84 48 00 00            	jne	0x1329134 <.text+0x4ab4>
 13248b0: e9 78 47 00 00               	jmp	0x132902d <.text+0x49ad>
 13248b5: 68 a4 c8 87 01               	push	0x187c8a4
 13248ba: e8 31 b6 e7 ff               	call	0x119fef0
 13248bf: 50                           	push	eax
 13248c0: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 13248c3: 51                           	push	ecx
 13248c4: e8 b7 d4 0d ff               	call	0x401d80
 13248c9: 83 c4 0c                     	add	esp, 0xc
 13248cc: 84 c0                        	test	al, al
 13248ce: 74 5a                        	je	0x132492a <.text+0x2aa>
 13248d0: 8b b5 18 fe ff ff            	mov	esi, dword ptr [ebp - 0x1e8]
 13248d6: 8d 8e c0 00 00 00            	lea	ecx, [esi + 0xc0]
 13248dc: e8 3f bf 11 ff               	call	0x440820
 13248e1: 8d 95 1c fe ff ff            	lea	edx, [ebp - 0x1e4]
 13248e7: 52                           	push	edx
 13248e8: e8 d3 ef ef ff               	call	0x12238c0
 13248ed: 83 c4 04                     	add	esp, 0x4
 13248f0: 84 c0                        	test	al, al
 13248f2: 0f 84 35 47 00 00            	je	0x132902d <.text+0x49ad>
 13248f8: eb 06                        	jmp	0x1324900 <.text+0x280>
 13248fa: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 1324900: 8d 85 1c fe ff ff            	lea	eax, [ebp - 0x1e4]
 1324906: 50                           	push	eax
 1324907: 8d 8e c0 00 00 00            	lea	ecx, [esi + 0xc0]
 132490d: e8 5e 98 3d ff               	call	0x6fe170
 1324912: 8d 8d 1c fe ff ff            	lea	ecx, [ebp - 0x1e4]
 1324918: 51                           	push	ecx
 1324919: e8 a2 ef ef ff               	call	0x12238c0
 132491e: 83 c4 04                     	add	esp, 0x4
 1324921: 84 c0                        	test	al, al
 1324923: 75 db                        	jne	0x1324900 <.text+0x280>
 1324925: e9 03 47 00 00               	jmp	0x132902d <.text+0x49ad>
 132492a: 68 a0 ba 88 01               	push	0x188baa0
 132492f: e8 bc b5 e7 ff               	call	0x119fef0
 1324934: 50                           	push	eax
 1324935: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 1324938: 52                           	push	edx
 1324939: e8 42 d4 0d ff               	call	0x401d80
 132493e: 83 c4 0c                     	add	esp, 0xc
 1324941: 84 c0                        	test	al, al
 1324943: 74 55                        	je	0x132499a <.text+0x31a>
 1324945: 8b b5 18 fe ff ff            	mov	esi, dword ptr [ebp - 0x1e8]
 132494b: 8d 8e d4 00 00 00            	lea	ecx, [esi + 0xd4]
 1324951: e8 ca be 11 ff               	call	0x440820
 1324956: 8d 85 1c fe ff ff            	lea	eax, [ebp - 0x1e4]
 132495c: 50                           	push	eax
 132495d: e8 5e ef ef ff               	call	0x12238c0
 1324962: 83 c4 04                     	add	esp, 0x4
 1324965: 84 c0                        	test	al, al
 1324967: 0f 84 c0 46 00 00            	je	0x132902d <.text+0x49ad>
 132496d: 8d 49 00                     	lea	ecx, [ecx]
 1324970: 8d 8d 1c fe ff ff            	lea	ecx, [ebp - 0x1e4]
 1324976: 51                           	push	ecx
 1324977: 8d 8e d4 00 00 00            	lea	ecx, [esi + 0xd4]
 132497d: e8 ee 97 3d ff               	call	0x6fe170
 1324982: 8d 95 1c fe ff ff            	lea	edx, [ebp - 0x1e4]
 1324988: 52                           	push	edx
 1324989: e8 32 ef ef ff               	call	0x12238c0
 132498e: 83 c4 04                     	add	esp, 0x4
 1324991: 84 c0                        	test	al, al
 1324993: 75 db                        	jne	0x1324970 <.text+0x2f0>
 1324995: e9 93 46 00 00               	jmp	0x132902d <.text+0x49ad>
 132499a: 68 a4 f9 86 01               	push	0x186f9a4
 132499f: e8 4c b5 e7 ff               	call	0x119fef0
 13249a4: 50                           	push	eax
 13249a5: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 13249a8: 50                           	push	eax
 13249a9: e8 d2 d3 0d ff               	call	0x401d80
 13249ae: 83 c4 0c                     	add	esp, 0xc
 13249b1: 84 c0                        	test	al, al
 13249b3: 74 2c                        	je	0x13249e1 <.text+0x361>
 13249b5: 8d 8d 1c fe ff ff            	lea	ecx, [ebp - 0x1e4]
 13249bb: 51                           	push	ecx
 13249bc: e8 ff ee ef ff               	call	0x12238c0
 13249c1: 8b 95 1c fe ff ff            	mov	edx, dword ptr [ebp - 0x1e4]
 13249c7: 52                           	push	edx
 13249c8: e8 c3 f5 ef ff               	call	0x1223f90
 13249cd: 8b 8d 18 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e8]
 13249d3: 83 c4 08                     	add	esp, 0x8
 13249d6: 89 81 bc 00 00 00            	mov	dword ptr [ecx + 0xbc], eax
 13249dc: e9 4c 46 00 00               	jmp	0x132902d <.text+0x49ad>
 13249e1: 68 70 ba 88 01               	push	0x188ba70
 13249e6: e8 05 b5 e7 ff               	call	0x119fef0
 13249eb: 50                           	push	eax
 13249ec: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 13249ef: 52                           	push	edx
 13249f0: e8 8b d3 0d ff               	call	0x401d80
 13249f5: 83 c4 0c                     	add	esp, 0xc
 13249f8: 84 c0                        	test	al, al
 13249fa: 74 1b                        	je	0x1324a17 <.text+0x397>
 13249fc: 6a 00                        	push	0x0
 13249fe: e8 5d ec ef ff               	call	0x1223660
 1324a03: 8b 8d 18 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e8]
 1324a09: 83 c4 04                     	add	esp, 0x4
 1324a0c: 89 81 e8 00 00 00            	mov	dword ptr [ecx + 0xe8], eax
 1324a12: e9 16 46 00 00               	jmp	0x132902d <.text+0x49ad>
 1324a17: 68 3c ba 88 01               	push	0x188ba3c
 1324a1c: e8 cf b4 e7 ff               	call	0x119fef0
 1324a21: 50                           	push	eax
 1324a22: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 1324a25: 52                           	push	edx
 1324a26: e8 55 d3 0d ff               	call	0x401d80
 1324a2b: 83 c4 0c                     	add	esp, 0xc
 1324a2e: 84 c0                        	test	al, al
 1324a30: 74 1b                        	je	0x1324a4d <.text+0x3cd>
 1324a32: 6a 00                        	push	0x0
 1324a34: e8 27 ec ef ff               	call	0x1223660
 1324a39: 8b 8d 18 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e8]
 1324a3f: 83 c4 04                     	add	esp, 0x4
 1324a42: 89 81 ec 00 00 00            	mov	dword ptr [ecx + 0xec], eax
 1324a48: e9 e0 45 00 00               	jmp	0x132902d <.text+0x49ad>
 1324a4d: 68 0c ba 88 01               	push	0x188ba0c
 1324a52: e8 99 b4 e7 ff               	call	0x119fef0
 1324a57: 50                           	push	eax
 1324a58: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 1324a5b: 52                           	push	edx
 1324a5c: e8 1f d3 0d ff               	call	0x401d80
 1324a61: 83 c4 0c                     	add	esp, 0xc
 1324a64: 84 c0                        	test	al, al
 1324a66: 74 1b                        	je	0x1324a83 <.text+0x403>
 1324a68: 6a 00                        	push	0x0
 1324a6a: e8 f1 eb ef ff               	call	0x1223660
 1324a6f: 8b 8d 18 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e8]
 1324a75: 83 c4 04                     	add	esp, 0x4
 1324a78: 89 81 f0 00 00 00            	mov	dword ptr [ecx + 0xf0], eax
 1324a7e: e9 aa 45 00 00               	jmp	0x132902d <.text+0x49ad>
 1324a83: 68 d4 b9 88 01               	push	0x188b9d4
 1324a88: e8 63 b4 e7 ff               	call	0x119fef0
 1324a8d: 50                           	push	eax
 1324a8e: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 1324a91: 52                           	push	edx
 1324a92: e8 e9 d2 0d ff               	call	0x401d80
 1324a97: 83 c4 0c                     	add	esp, 0xc
 1324a9a: 84 c0                        	test	al, al
 1324a9c: 0f 84 06 07 00 00            	je	0x13251a8 <.text+0xb28>
 1324aa2: 8b 8d 18 fe ff ff            	mov	ecx, dword ptr [ebp - 0x1e8]
 1324aa8: 81 c1 00 01 00 00            	add	ecx, 0x100
 1324aae: 89 8d ec fd ff ff            	mov	dword ptr [ebp - 0x214], ecx
 1324ab4: e8 e7 60 e1 ff               	call	0x113aba0
 1324ab9: 8d 8d 0c ff ff ff            	lea	ecx, [ebp - 0xf4]
 1324abf: e8 0c 9f ff ff               	call	0x131e9d0
 1324ac4: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1324ac7: c6 45 fc 07                  	mov	byte ptr [ebp - 0x4], 0x7
 1324acb: e8 c0 d7 d8 ff               	call	0x10b2290
 1324ad0: bb d7 01 00 00               	mov	ebx, 0x1d7
 1324ad5: c6 45 fc 08                  	mov	byte ptr [ebp - 0x4], 0x8
 1324ad9: c6 85 12 fe ff ff 00         	mov	byte ptr [ebp - 0x1ee], 0x0
 1324ae0: 8d 7b 0c                     	lea	edi, [ebx + 0xc]
 1324ae3: 8d 45 b0                     	lea	eax, [ebp - 0x50]
 1324ae6: 6a 01                        	push	0x1
 1324ae8: 50                           	push	eax
 1324ae9: e8 22 07 f0 ff               	call	0x1225210
 1324aee: 83 c4 08                     	add	esp, 0x8
 1324af1: 84 c0                        	test	al, al
 1324af3: 0f 84 28 46 00 00            	je	0x1329121 <.text+0x4aa1>
 1324af9: 8d a4 24 00 00 00 00         	lea	esp, [esp]
 1324b00: f6 05 98 1c da 01 01         	test	byte ptr [0x1da1c98], 0x1
 1324b07: 75 26                        	jne	0x1324b2f <.text+0x4af>
 1324b09: 83 0d 98 1c da 01 01         	or	dword ptr [0x1da1c98], 0x1
 1324b10: b9 84 1c da 01               	mov	ecx, 0x1da1c84
 1324b15: c6 45 fc 09                  	mov	byte ptr [ebp - 0x4], 0x9
 1324b19: e8 d2 9d 60 ff               	call	0x92e8f0
 1324b1e: 68 f0 80 55 01               	push	0x15580f0
 1324b23: e8 e2 27 0b 00               	call	0x13d730a <.text+0xb2c8a>
 1324b28: 83 c4 04                     	add	esp, 0x4
 1324b2b: c6 45 fc 08                  	mov	byte ptr [ebp - 0x4], 0x8
 1324b2f: f6 05 98 1c da 01 02         	test	byte ptr [0x1da1c98], 0x2
 1324b36: 75 26                        	jne	0x1324b5e <.text+0x4de>
 1324b38: 83 0d 98 1c da 01 02         	or	dword ptr [0x1da1c98], 0x2
 1324b3f: b9 80 1c da 01               	mov	ecx, 0x1da1c80
 1324b44: c6 45 fc 0a                  	mov	byte ptr [ebp - 0x4], 0xa
 1324b48: e8 03 06 e8 ff               	call	0x11a5150
 1324b4d: 68 b0 7e 55 01               	push	0x1557eb0
 1324b52: e8 b3 27 0b 00               	call	0x13d730a <.text+0xb2c8a>
 1324b57: 83 c4 04                     	add	esp, 0x4
 1324b5a: c6 45 fc 08                  	mov	byte ptr [ebp - 0x4], 0x8
 1324b5e: 80 3d 7c 1c da 01 00         	cmp	byte ptr [0x1da1c7c], 0x0
 1324b65: 74 71                        	je	0x1324bd8 <.text+0x558>
 1324b67: 83 7d c8 08                  	cmp	dword ptr [ebp - 0x38], 0x8
 1324b6b: 72 0b                        	jb	0x1324b78 <.text+0x4f8>
 1324b6d: 8b 4d b4                     	mov	ecx, dword ptr [ebp - 0x4c]
 1324b70: 89 8d 08 fe ff ff            	mov	dword ptr [ebp - 0x1f8], ecx
 1324b76: eb 09                        	jmp	0x1324b81 <.text+0x501>
 1324b78: 8d 55 b4                     	lea	edx, [ebp - 0x4c]
 1324b7b: 89 95                        	<unknown>
 1324b7d: 08 fe                        	or	dh, bh
 1324b7f: ff                           	<unknown>
