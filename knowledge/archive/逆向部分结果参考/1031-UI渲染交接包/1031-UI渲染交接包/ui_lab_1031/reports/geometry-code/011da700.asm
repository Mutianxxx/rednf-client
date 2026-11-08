
<stdin>:	file format elf32-i386

Disassembly of section .text:

011da700 <.text>:
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
 11da73b: 74 17                        	je	0x11da754 <.text+0x54>
 11da73d: 5f                           	pop	edi
 11da73e: b8 02 00 00 80               	mov	eax, 0x80000002
 11da743: 5e                           	pop	esi
 11da744: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da747: 33 cd                        	xor	ecx, ebp
 11da749: e8 8a ca 1f 00               	call	0x13d71d8 <.text+0x1fcad8>
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
 11da7ce: 75 58                        	jne	0x11da828 <.text+0x128>
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
 11da7e9: 78 24                        	js	0x11da80f <.text+0x10f>
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
 11da809: 79 1d                        	jns	0x11da828 <.text+0x128>
 11da80b: 8b 16                        	mov	edx, dword ptr [esi]
 11da80d: 8b ce                        	mov	ecx, esi
 11da80f: 8b 42 14                     	mov	eax, dword ptr [edx + 0x14]
 11da812: ff d0                        	call	eax
 11da814: 8b c7                        	mov	eax, edi
 11da816: 5f                           	pop	edi
 11da817: 5e                           	pop	esi
 11da818: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da81b: 33 cd                        	xor	ecx, ebp
 11da81d: e8 b6 c9 1f 00               	call	0x13d71d8 <.text+0x1fcad8>
 11da822: 8b e5                        	mov	esp, ebp
 11da824: 5d                           	pop	ebp
 11da825: c2 04 00                     	ret	0x4
 11da828: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da82b: 5f                           	pop	edi
 11da82c: 33 cd                        	xor	ecx, ebp
 11da82e: b8                           	<unknown>
 11da82f: 01                           	<unknown>
