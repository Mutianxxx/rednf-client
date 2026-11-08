
<stdin>:	file format elf32-i386

Disassembly of section .text:

011da600 <.text>:
 11da600: 83 f8 04                     	cmp	eax, 0x4
 11da603: 73 eb                        	jae	0x11da5f0
 11da605: 5e                           	pop	esi
 11da606: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da609: 33 cd                        	xor	ecx, ebp
 11da60b: e8 c8 cb 1f 00               	call	0x13d71d8 <.text+0x1fcbd8>
 11da610: 8b e5                        	mov	esp, ebp
 11da612: 5d                           	pop	ebp
 11da613: c3                           	ret
 11da614: 8b 06                        	mov	eax, dword ptr [esi]
 11da616: 8b 90 bc 00 00 00            	mov	edx, dword ptr [eax + 0xbc]
 11da61c: 8d 4d e4                     	lea	ecx, [ebp - 0x1c]
 11da61f: 51                           	push	ecx
 11da620: 56                           	push	esi
 11da621: ff d2                        	call	edx
 11da623: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da626: 33 cd                        	xor	ecx, ebp
 11da628: 5e                           	pop	esi
 11da629: e8 aa cb 1f 00               	call	0x13d71d8 <.text+0x1fcbd8>
 11da62e: 8b e5                        	mov	esp, ebp
 11da630: 5d                           	pop	ebp
 11da631: c3                           	ret
 11da632: cc                           	int3
 11da633: cc                           	int3
 11da634: cc                           	int3
 11da635: cc                           	int3
 11da636: cc                           	int3
 11da637: cc                           	int3
 11da638: cc                           	int3
 11da639: cc                           	int3
 11da63a: cc                           	int3
 11da63b: cc                           	int3
 11da63c: cc                           	int3
 11da63d: cc                           	int3
 11da63e: cc                           	int3
 11da63f: cc                           	int3
 11da640: 55                           	push	ebp
 11da641: 8b ec                        	mov	ebp, esp
 11da643: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11da646: a3 14 70 b5 01               	mov	dword ptr [0x1b57014], eax
 11da64b: 5d                           	pop	ebp
 11da64c: c3                           	ret
 11da64d: cc                           	int3
 11da64e: cc                           	int3
 11da64f: cc                           	int3
 11da650: 55                           	push	ebp
 11da651: 8b ec                        	mov	ebp, esp
 11da653: 53                           	push	ebx
 11da654: 56                           	push	esi
 11da655: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11da658: 57                           	push	edi
 11da659: 8b f9                        	mov	edi, ecx
 11da65b: 8b 1f                        	mov	ebx, dword ptr [edi]
 11da65d: 8b ce                        	mov	ecx, esi
 11da65f: e8 2c 97 fd ff               	call	0x11b3d90
 11da664: 50                           	push	eax
 11da665: 8b ce                        	mov	ecx, esi
 11da667: e8 14 97 fd ff               	call	0x11b3d80
 11da66c: 50                           	push	eax
 11da66d: 8b 43 0c                     	mov	eax, dword ptr [ebx + 0xc]
 11da670: 8b cf                        	mov	ecx, edi
 11da672: ff d0                        	call	eax
 11da674: 85 c0                        	test	eax, eax
 11da676: 0f 88 8e 00 00 00            	js	0x11da70a <.text+0x10a>
 11da67c: 8b ce                        	mov	ecx, esi
 11da67e: e8 fd e9 3d ff               	call	0x5b9080
 11da683: 83 f8 08                     	cmp	eax, 0x8
 11da686: 74 24                        	je	0x11da6ac <.text+0xac>
 11da688: 8b ce                        	mov	ecx, esi
 11da68a: e8 f1 e9 3d ff               	call	0x5b9080
 11da68f: 83 f8 10                     	cmp	eax, 0x10
 11da692: 74 18                        	je	0x11da6ac <.text+0xac>
 11da694: 8b ce                        	mov	ecx, esi
 11da696: e8 e5 e9 3d ff               	call	0x5b9080
 11da69b: 83 f8 0e                     	cmp	eax, 0xe
 11da69e: 74 0c                        	je	0x11da6ac <.text+0xac>
 11da6a0: 8b ce                        	mov	ecx, esi
 11da6a2: e8 d9 e9 3d ff               	call	0x5b9080
 11da6a7: 83 f8 0f                     	cmp	eax, 0xf
 11da6aa: 75 59                        	jne	0x11da705 <.text+0x105>
 11da6ac: 8b ce                        	mov	ecx, esi
 11da6ae: e8 ed 96 fd ff               	call	0x11b3da0
 11da6b3: 8b ce                        	mov	ecx, esi
 11da6b5: 8b d8                        	mov	ebx, eax
 11da6b7: e8 f4 96 fd ff               	call	0x11b3db0
 11da6bc: 6a 00                        	push	0x0
 11da6be: 6a 00                        	push	0x0
 11da6c0: 8b ce                        	mov	ecx, esi
 11da6c2: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
 11da6c5: e8 66 96 fd ff               	call	0x11b3d30
 11da6ca: 56                           	push	esi
 11da6cb: 6a 00                        	push	0x0
 11da6cd: 6a 00                        	push	0x0
 11da6cf: 8b cf                        	mov	ecx, edi
 11da6d1: e8 7a 92 fd ff               	call	0x11b3950
 11da6d6: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11da6d9: 51                           	push	ecx
 11da6da: 53                           	push	ebx
 11da6db: 8b ce                        	mov	ecx, esi
 11da6dd: e8 4e 96 fd ff               	call	0x11b3d30
 11da6e2: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11da6e5: 52                           	push	edx
 11da6e6: 53                           	push	ebx
 11da6e7: 8b cf                        	mov	ecx, edi
 11da6e9: e8 42 96 fd ff               	call	0x11b3d30
 11da6ee: 8b cf                        	mov	ecx, edi
 11da6f0: e8 db 96 fd ff               	call	0x11b3dd0
 11da6f5: 50                           	push	eax
 11da6f6: 8b cf                        	mov	ecx, edi
 11da6f8: e8 c3 96 fd ff               	call	0x11b3dc0
 11da6fd: 50                           	push	eax
 11da6fe: 8b ce                        	mov	ecx, esi
 11da700: e8 4b 96 fd ff               	call	0x11b3d50
 11da705: b8 01 00 00 00               	mov	eax, 0x1
 11da70a: 5f                           	pop	edi
 11da70b: 5e                           	pop	esi
 11da70c: 5b                           	pop	ebx
 11da70d: 5d                           	pop	ebp
 11da70e: c2 04 00                     	ret	0x4
 11da711: cc                           	int3
 11da712: cc                           	int3
 11da713: cc                           	int3
 11da714: cc                           	int3
 11da715: cc                           	int3
 11da716: cc                           	int3
 11da717: cc                           	int3
 11da718: cc                           	int3
 11da719: cc                           	int3
 11da71a: cc                           	int3
 11da71b: cc                           	int3
 11da71c: cc                           	int3
 11da71d: cc                           	int3
 11da71e: cc                           	int3
 11da71f: cc                           	int3
 11da720: 55                           	push	ebp
 11da721: 8b ec                        	mov	ebp, esp
 11da723: 83 ec 28                     	sub	esp, 0x28
 11da726: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11da72b: 33 c5                        	xor	eax, ebp
 11da72d: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11da730: 56                           	push	esi
 11da731: 8b f1                        	mov	esi, ecx
 11da733: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11da737: 57                           	push	edi
 11da738: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 11da73b: 74 17                        	je	0x11da754 <.text+0x154>
 11da73d: 5f                           	pop	edi
 11da73e: b8 02 00 00 80               	mov	eax, 0x80000002
 11da743: 5e                           	pop	esi
 11da744: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da747: 33 cd                        	xor	ecx, ebp
 11da749: e8 8a ca 1f 00               	call	0x13d71d8 <.text+0x1fcbd8>
 11da74e: 8b e5                        	mov	esp, ebp
 11da750: 5d                           	pop	ebp
 11da751: c2 04 00                     	ret	0x4
 11da754: 53                           	push	ebx
 11da755: c6 46 04 01                  	mov	byte ptr [esi + 0x4], 0x1
 11da759: ff 15 88 a5 55 01            	call	dword ptr [0x155a588]
 11da75f: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
 11da762: 51                           	push	ecx
 11da763: 89 46 54                     	mov	dword ptr [esi + 0x54], eax
 11da766: 8b 07                        	mov	eax, dword ptr [edi]
 11da768: 8b 50 44                     	mov	edx, dword ptr [eax + 0x44]
 11da76b: 6a 00                        	push	0x0
 11da76d: 57                           	push	edi
 11da76e: ff d2                        	call	edx
 11da770: 8b ce                        	mov	ecx, esi
 11da772: e8 29 96 fd ff               	call	0x11b3da0
 11da777: 8b ce                        	mov	ecx, esi
 11da779: 8b d8                        	mov	ebx, eax
 11da77b: e8 30 96 fd ff               	call	0x11b3db0
 11da780: 8b 4d f8                     	mov	ecx, dword ptr [ebp - 0x8]
 11da783: 89 45 d8                     	mov	dword ptr [ebp - 0x28], eax
 11da786: 8b 45 f4                     	mov	eax, dword ptr [ebp - 0xc]
 11da789: 66 89 4e 1e                  	mov	word ptr [esi + 0x1e], cx
 11da78d: 66 89 4e 26                  	mov	word ptr [esi + 0x26], cx
 11da791: 8b ce                        	mov	ecx, esi
 11da793: 66 89 46 1c                  	mov	word ptr [esi + 0x1c], ax
 11da797: 66 89 46 24                  	mov	word ptr [esi + 0x24], ax
 11da79b: e8 f0 95 fd ff               	call	0x11b3d90
 11da7a0: 03 45 d8                     	add	eax, dword ptr [ebp - 0x28]
 11da7a3: 8b ce                        	mov	ecx, esi
 11da7a5: 50                           	push	eax
 11da7a6: e8 d5 95 fd ff               	call	0x11b3d80
 11da7ab: 03 c3                        	add	eax, ebx
 11da7ad: 50                           	push	eax
 11da7ae: 6a 00                        	push	0x0
 11da7b0: 8d 46 28                     	lea	eax, [esi + 0x28]
 11da7b3: 6a 00                        	push	0x0
 11da7b5: 50                           	push	eax
 11da7b6: e8 45 8e fd ff               	call	0x11b3600
 11da7bb: 89 7e 5c                     	mov	dword ptr [esi + 0x5c], edi
 11da7be: 8b 0f                        	mov	ecx, dword ptr [edi]
 11da7c0: 8b 51 04                     	mov	edx, dword ptr [ecx + 0x4]
 11da7c3: 83 c4 14                     	add	esp, 0x14
 11da7c6: 57                           	push	edi
 11da7c7: ff d2                        	call	edx
 11da7c9: 83 7d e8 01                  	cmp	dword ptr [ebp - 0x18], 0x1
 11da7cd: 5b                           	pop	ebx
 11da7ce: 75 58                        	jne	0x11da828 <.text+0x228>
 11da7d0: 8b 46 5c                     	mov	eax, dword ptr [esi + 0x5c]
 11da7d3: 8b 08                        	mov	ecx, dword ptr [eax]
 11da7d5: 8d 56 60                     	lea	edx, [esi + 0x60]
 11da7d8: 52                           	push	edx
 11da7d9: 6a 00                        	push	0x0
 11da7db: 50                           	push	eax
 11da7dc: 8b 41 48                     	mov	eax, dword ptr [ecx + 0x48]
 11da7df: ff d0                        	call	eax
 11da7e1: 8b 16                        	mov	edx, dword ptr [esi]
 11da7e3: 8b f8                        	mov	edi, eax
 11da7e5: 8b ce                        	mov	ecx, esi
 11da7e7: 85 ff                        	test	edi, edi
 11da7e9: 78 24                        	js	0x11da80f <.text+0x20f>
 11da7eb: 8b 42 70                     	mov	eax, dword ptr [edx + 0x70]
 11da7ee: ff d0                        	call	eax
 11da7f0: 8b 16                        	mov	edx, dword ptr [esi]
 11da7f2: 8b 42 74                     	mov	eax, dword ptr [edx + 0x74]
 11da7f5: 8b ce                        	mov	ecx, esi
 11da7f7: ff d0                        	call	eax
 11da7f9: 8b 16                        	mov	edx, dword ptr [esi]
 11da7fb: 8b 82 bc 00 00 00            	mov	eax, dword ptr [edx + 0xbc]
 11da801: 8b ce                        	mov	ecx, esi
 11da803: ff d0                        	call	eax
 11da805: 8b f8                        	mov	edi, eax
 11da807: 85 ff                        	test	edi, edi
 11da809: 79 1d                        	jns	0x11da828 <.text+0x228>
 11da80b: 8b 16                        	mov	edx, dword ptr [esi]
 11da80d: 8b ce                        	mov	ecx, esi
 11da80f: 8b 42 14                     	mov	eax, dword ptr [edx + 0x14]
 11da812: ff d0                        	call	eax
 11da814: 8b c7                        	mov	eax, edi
 11da816: 5f                           	pop	edi
 11da817: 5e                           	pop	esi
 11da818: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da81b: 33 cd                        	xor	ecx, ebp
 11da81d: e8 b6 c9 1f 00               	call	0x13d71d8 <.text+0x1fcbd8>
 11da822: 8b e5                        	mov	esp, ebp
 11da824: 5d                           	pop	ebp
 11da825: c2 04 00                     	ret	0x4
 11da828: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da82b: 5f                           	pop	edi
 11da82c: 33 cd                        	xor	ecx, ebp
 11da82e: b8 01 00 00 00               	mov	eax, 0x1
 11da833: 5e                           	pop	esi
 11da834: e8 9f c9 1f 00               	call	0x13d71d8 <.text+0x1fcbd8>
 11da839: 8b e5                        	mov	esp, ebp
 11da83b: 5d                           	pop	ebp
 11da83c: c2 04 00                     	ret	0x4
 11da83f: cc                           	int3
 11da840: 56                           	push	esi
 11da841: 8b f1                        	mov	esi, ecx
 11da843: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11da847: 74 64                        	je	0x11da8ad <.text+0x2ad>
 11da849: e8 52 90 fd ff               	call	0x11b38a0
 11da84e: 85 c0                        	test	eax, eax
 11da850: 75 5b                        	jne	0x11da8ad <.text+0x2ad>
 11da852: 8b 46 60                     	mov	eax, dword ptr [esi + 0x60]
 11da855: 85 c0                        	test	eax, eax
 11da857: 74 08                        	je	0x11da861 <.text+0x261>
 11da859: 8b 08                        	mov	ecx, dword ptr [eax]
 11da85b: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
 11da85e: 50                           	push	eax
 11da85f: ff d2                        	call	edx
 11da861: 8b 46 5c                     	mov	eax, dword ptr [esi + 0x5c]
 11da864: c7 46 60 00 00 00 00         	mov	dword ptr [esi + 0x60], 0x0
 11da86b: 85 c0                        	test	eax, eax
 11da86d: 74 3a                        	je	0x11da8a9 <.text+0x2a9>
 11da86f: 8b 08                        	mov	ecx, dword ptr [eax]
 11da871: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
 11da874: 57                           	push	edi
 11da875: 50                           	push	eax
 11da876: ff d2                        	call	edx
 11da878: 8b ce                        	mov	ecx, esi
 11da87a: c7 46 5c 00 00 00 00         	mov	dword ptr [esi + 0x5c], 0x0
 11da881: e8 7a 95 fd ff               	call	0x11b3e00
 11da886: 8b f8                        	mov	edi, eax
 11da888: 0f af 7e 10                  	imul	edi, dword ptr [esi + 0x10]
 11da88c: 6a 00                        	push	0x0
 11da88e: 8b ce                        	mov	ecx, esi
 11da890: e8 fb 94 fd ff               	call	0x11b3d90
 11da895: 03 c0                        	add	eax, eax
 11da897: 03 c0                        	add	eax, eax
 11da899: f7 df                        	neg	edi
 11da89b: 2b f8                        	sub	edi, eax
 11da89d: 57                           	push	edi
 11da89e: 6a 01                        	push	0x1
 11da8a0: e8 2b f5 fd ff               	call	0x11b9dd0
 11da8a5: 83 c4 0c                     	add	esp, 0xc
 11da8a8: 5f                           	pop	edi
 11da8a9: c6 46 04 00                  	mov	byte ptr [esi + 0x4], 0x0
 11da8ad: b8 01 00 00 00               	mov	eax, 0x1
 11da8b2: 5e                           	pop	esi
 11da8b3: c3                           	ret
 11da8b4: cc                           	int3
 11da8b5: cc                           	int3
 11da8b6: cc                           	int3
 11da8b7: cc                           	int3
 11da8b8: cc                           	int3
 11da8b9: cc                           	int3
 11da8ba: cc                           	int3
 11da8bb: cc                           	int3
 11da8bc: cc                           	int3
 11da8bd: cc                           	int3
 11da8be: cc                           	int3
 11da8bf: cc                           	int3
