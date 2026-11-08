
<stdin>:	file format elf32-i386

Disassembly of section .text:

01314800 <.text>:
 1314800: 55                           	push	ebp
 1314801: 8b ec                        	mov	ebp, esp
 1314803: 6a ff                        	push	-0x1
 1314805: 68 56 a8 4d 01               	push	0x14da856
 131480a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
 1314810: 50                           	push	eax
 1314811: 81 ec 38 01 00 00            	sub	esp, 0x138
 1314817: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 131481c: 33 c5                        	xor	eax, ebp
 131481e: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 1314821: 53                           	push	ebx
 1314822: 56                           	push	esi
 1314823: 57                           	push	edi
 1314824: 50                           	push	eax
 1314825: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 1314828: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
 131482e: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 1314831: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 1314834: 50                           	push	eax
 1314835: 68 e0 0e da 01               	push	0x1da0ee0
 131483a: 89 b5 1c ff ff ff            	mov	dword ptr [ebp - 0xe4], esi
 1314840: 89 85 f4 fe ff ff            	mov	dword ptr [ebp - 0x10c], eax
 1314846: e8 d5 ed f0 ff               	call	0x1223620
 131484b: 83 c4 08                     	add	esp, 0x8
 131484e: 84 c0                        	test	al, al
 1314850: 75 1c                        	jne	0x131486e <.text+0x6e>
 1314852: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1314855: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 131485c: 59                           	pop	ecx
 131485d: 5f                           	pop	edi
 131485e: 5e                           	pop	esi
 131485f: 5b                           	pop	ebx
 1314860: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 1314863: 33 cd                        	xor	ecx, ebp
 1314865: e8 6e 29 0c 00               	call	0x13d71d8 <.text+0xc29d8>
 131486a: 8b e5                        	mov	esp, ebp
 131486c: 5d                           	pop	ebp
 131486d: c3                           	ret
 131486e: 8b ce                        	mov	ecx, esi
 1314870: e8 1b e6 e2 ff               	call	0x1142e90
 1314875: 33 db                        	xor	ebx, ebx
 1314877: 6a 08                        	push	0x8
 1314879: 89 5d d0                     	mov	dword ptr [ebp - 0x30], ebx
 131487c: e8 99 22 0c 00               	call	0x13d6b1a <.text+0xc231a>
 1314881: 83 c4 04                     	add	esp, 0x4
 1314884: 3b c3                        	cmp	eax, ebx
 1314886: 0f 84 af 07 00 00            	je	0x131503b <.text+0x83b>
 131488c: 89 45 d0                     	mov	dword ptr [ebp - 0x30], eax
 131488f: 89 58 04                     	mov	dword ptr [eax + 0x4], ebx
 1314892: 33 c9                        	xor	ecx, ecx
 1314894: 89 08                        	mov	dword ptr [eax], ecx
 1314896: 8b 4d d0                     	mov	ecx, dword ptr [ebp - 0x30]
 1314899: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 131489c: 89 01                        	mov	dword ptr [ecx], eax
 131489e: 33 d2                        	xor	edx, edx
 13148a0: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 13148a7: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 13148aa: 66 89 55 d4                  	mov	word ptr [ebp - 0x2c], dx
 13148ae: 6a 01                        	push	0x1
 13148b0: 50                           	push	eax
 13148b1: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
 13148b4: 88 9d 23 ff ff ff            	mov	byte ptr [ebp - 0xdd], bl
 13148ba: e8 51 09 f1 ff               	call	0x1225210
 13148bf: 83 c4 08                     	add	esp, 0x8
 13148c2: 84 c0                        	test	al, al
 13148c4: 0f 84 eb 06 00 00            	je	0x1314fb5 <.text+0x7b5>
 13148ca: 83 cf ff                     	or	edi, -0x1
 13148cd: 8d 49 00                     	lea	ecx, [ecx]
 13148d0: 68 98 75 58 01               	push	0x1587598
 13148d5: e8 16 b6 e8 ff               	call	0x119fef0
 13148da: 8b c8                        	mov	ecx, eax
 13148dc: 83 c4 04                     	add	esp, 0x4
 13148df: 8d 71 02                     	lea	esi, [ecx + 0x2]
 13148e2: 66 8b 11                     	mov	dx, word ptr [ecx]
 13148e5: 83 c1 02                     	add	ecx, 0x2
 13148e8: 66 3b d3                     	cmp	dx, bx
 13148eb: 75 f5                        	jne	0x13148e2 <.text+0xe2>
 13148ed: 2b ce                        	sub	ecx, esi
 13148ef: d1 f9                        	sar	ecx
 13148f1: 51                           	push	ecx
 13148f2: 8b 4d e4                     	mov	ecx, dword ptr [ebp - 0x1c]
 13148f5: 50                           	push	eax
 13148f6: 51                           	push	ecx
 13148f7: 53                           	push	ebx
 13148f8: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 13148fb: e8 30 d3 0e ff               	call	0x401c30
 1314900: 85 c0                        	test	eax, eax
 1314902: 75 17                        	jne	0x131491b <.text+0x11b>
 1314904: 8b 95 1c ff ff ff            	mov	edx, dword ptr [ebp - 0xe4]
 131490a: 83 c2 0c                     	add	edx, 0xc
 131490d: 52                           	push	edx
 131490e: e8 3d 08 f1 ff               	call	0x1225150
 1314913: 83 c4 04                     	add	esp, 0x4
 1314916: e9 68 06 00 00               	jmp	0x1314f83 <.text+0x783>
 131491b: 68 58 02 88 01               	push	0x1880258
 1314920: e8 cb b5 e8 ff               	call	0x119fef0
 1314925: 8b c8                        	mov	ecx, eax
 1314927: 83 c4 04                     	add	esp, 0x4
 131492a: 8d 71 02                     	lea	esi, [ecx + 0x2]
 131492d: 8d 49 00                     	lea	ecx, [ecx]
 1314930: 66 8b 11                     	mov	dx, word ptr [ecx]
 1314933: 83 c1 02                     	add	ecx, 0x2
 1314936: 66 3b d3                     	cmp	dx, bx
 1314939: 75 f5                        	jne	0x1314930 <.text+0x130>
 131493b: 2b ce                        	sub	ecx, esi
 131493d: d1 f9                        	sar	ecx
 131493f: 51                           	push	ecx
 1314940: 50                           	push	eax
 1314941: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 1314944: 50                           	push	eax
 1314945: 53                           	push	ebx
 1314946: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 1314949: e8 e2 d2 0e ff               	call	0x401c30
 131494e: 85 c0                        	test	eax, eax
 1314950: 75 20                        	jne	0x1314972 <.text+0x172>
 1314952: 8b b5 1c ff ff ff            	mov	esi, dword ptr [ebp - 0xe4]
 1314958: 8d 4e 2c                     	lea	ecx, [esi + 0x2c]
 131495b: 51                           	push	ecx
 131495c: e8 ef 07 f1 ff               	call	0x1225150
 1314961: 53                           	push	ebx
 1314962: e8 f9 ec f0 ff               	call	0x1223660
 1314967: 83 c4 08                     	add	esp, 0x8
 131496a: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
 131496d: e9 11 06 00 00               	jmp	0x1314f83 <.text+0x783>
 1314972: 68 20 d8 56 01               	push	0x156d820
 1314977: e8 74 b5 e8 ff               	call	0x119fef0
 131497c: 8b c8                        	mov	ecx, eax
 131497e: 83 c4 04                     	add	esp, 0x4
 1314981: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1314984: 66 8b 11                     	mov	dx, word ptr [ecx]
 1314987: 83 c1 02                     	add	ecx, 0x2
 131498a: 66 3b d3                     	cmp	dx, bx
 131498d: 75 f5                        	jne	0x1314984 <.text+0x184>
 131498f: 8b 55 e4                     	mov	edx, dword ptr [ebp - 0x1c]
 1314992: 2b ce                        	sub	ecx, esi
 1314994: d1 f9                        	sar	ecx
 1314996: 51                           	push	ecx
 1314997: 50                           	push	eax
 1314998: 52                           	push	edx
 1314999: 53                           	push	ebx
 131499a: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 131499d: e8 8e d2 0e ff               	call	0x401c30
 13149a2: 85 c0                        	test	eax, eax
 13149a4: 75 29                        	jne	0x13149cf <.text+0x1cf>
 13149a6: 8d 85 23 ff ff ff            	lea	eax, [ebp - 0xdd]
 13149ac: 50                           	push	eax
 13149ad: e8 ae ec f0 ff               	call	0x1223660
 13149b2: 83 c4 04                     	add	esp, 0x4
 13149b5: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 13149bb: 0f 84 f4 05 00 00            	je	0x1314fb5 <.text+0x7b5>
 13149c1: 8b 8d 1c ff ff ff            	mov	ecx, dword ptr [ebp - 0xe4]
 13149c7: 89 41 04                     	mov	dword ptr [ecx + 0x4], eax
 13149ca: e9 b4 05 00 00               	jmp	0x1314f83 <.text+0x783>
 13149cf: 68 38 2c 7f 01               	push	0x17f2c38
 13149d4: e8 17 b5 e8 ff               	call	0x119fef0
 13149d9: 8b c8                        	mov	ecx, eax
 13149db: 83 c4 04                     	add	esp, 0x4
 13149de: 8d 71 02                     	lea	esi, [ecx + 0x2]
 13149e1: 66 8b 11                     	mov	dx, word ptr [ecx]
 13149e4: 83 c1 02                     	add	ecx, 0x2
 13149e7: 66 3b d3                     	cmp	dx, bx
 13149ea: 75 f5                        	jne	0x13149e1 <.text+0x1e1>
 13149ec: 8b 55 e4                     	mov	edx, dword ptr [ebp - 0x1c]
 13149ef: 2b ce                        	sub	ecx, esi
 13149f1: d1 f9                        	sar	ecx
 13149f3: 51                           	push	ecx
 13149f4: 50                           	push	eax
 13149f5: 52                           	push	edx
 13149f6: 53                           	push	ebx
 13149f7: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 13149fa: e8 31 d2 0e ff               	call	0x401c30
 13149ff: 85 c0                        	test	eax, eax
 1314a01: 0f 85 7c 05 00 00            	jne	0x1314f83 <.text+0x783>
 1314a07: 6a 08                        	push	0x8
 1314a09: 89 5d b0                     	mov	dword ptr [ebp - 0x50], ebx
 1314a0c: e8 09 21 0c 00               	call	0x13d6b1a <.text+0xc231a>
 1314a11: 83 c4 04                     	add	esp, 0x4
 1314a14: 3b c3                        	cmp	eax, ebx
 1314a16: 0f 84 ec 05 00 00            	je	0x1315008 <.text+0x808>
 1314a1c: 89 45 b0                     	mov	dword ptr [ebp - 0x50], eax
 1314a1f: 33 c9                        	xor	ecx, ecx
 1314a21: 89 08                        	mov	dword ptr [eax], ecx
 1314a23: 33 d2                        	xor	edx, edx
 1314a25: 89 50 04                     	mov	dword ptr [eax + 0x4], edx
 1314a28: 8b 4d b0                     	mov	ecx, dword ptr [ebp - 0x50]
 1314a2b: 8d 45 b0                     	lea	eax, [ebp - 0x50]
 1314a2e: 89 01                        	mov	dword ptr [ecx], eax
 1314a30: c7 45 c8 07 00 00 00         	mov	dword ptr [ebp - 0x38], 0x7
 1314a37: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
 1314a3a: 66 89 55 b4                  	mov	word ptr [ebp - 0x4c], dx
 1314a3e: 8d 8d 24 ff ff ff            	lea	ecx, [ebp - 0xdc]
 1314a44: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1314a48: e8 d3 f8 ff ff               	call	0x1314320
 1314a4d: 8d 8d 24 ff ff ff            	lea	ecx, [ebp - 0xdc]
 1314a53: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
 1314a57: e8 64 f8 ff ff               	call	0x13142c0
 1314a5c: 8d 85 23 ff ff ff            	lea	eax, [ebp - 0xdd]
 1314a62: 50                           	push	eax
 1314a63: e8 f8 eb f0 ff               	call	0x1223660
 1314a68: 83 c4 04                     	add	esp, 0x4
 1314a6b: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314a71: 0f 84 24 05 00 00            	je	0x1314f9b <.text+0x79b>
 1314a77: 8d 8d 74 ff ff ff            	lea	ecx, [ebp - 0x8c]
 1314a7d: 89 85 24 ff ff ff            	mov	dword ptr [ebp - 0xdc], eax
 1314a83: e8 68 ef ff ff               	call	0x13139f0
 1314a88: 8d 8d 74 ff ff ff            	lea	ecx, [ebp - 0x8c]
 1314a8e: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
 1314a92: e8 09 ef ff ff               	call	0x13139a0
 1314a97: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314a9a: 6a 01                        	push	0x1
 1314a9c: 51                           	push	ecx
 1314a9d: e8 6e 07 f1 ff               	call	0x1225210
 1314aa2: 83 c4 08                     	add	esp, 0x8
 1314aa5: 84 c0                        	test	al, al
 1314aa7: 0f 84 b1 04 00 00            	je	0x1314f5e <.text+0x75e>
 1314aad: 8d 49 00                     	lea	ecx, [ecx]
 1314ab0: 68 44 85 88 01               	push	0x1888544
 1314ab5: e8 36 b4 e8 ff               	call	0x119fef0
 1314aba: 8b c8                        	mov	ecx, eax
 1314abc: 83 c4 04                     	add	esp, 0x4
 1314abf: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1314ac2: 66 8b 11                     	mov	dx, word ptr [ecx]
 1314ac5: 83 c1 02                     	add	ecx, 0x2
 1314ac8: 66 3b d3                     	cmp	dx, bx
 1314acb: 75 f5                        	jne	0x1314ac2 <.text+0x2c2>
 1314acd: 8b 55 c4                     	mov	edx, dword ptr [ebp - 0x3c]
 1314ad0: 2b ce                        	sub	ecx, esi
 1314ad2: d1 f9                        	sar	ecx
 1314ad4: 51                           	push	ecx
 1314ad5: 50                           	push	eax
 1314ad6: 52                           	push	edx
 1314ad7: 53                           	push	ebx
 1314ad8: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314adb: e8 50 d1 0e ff               	call	0x401c30
 1314ae0: 85 c0                        	test	eax, eax
 1314ae2: 75 69                        	jne	0x1314b4d <.text+0x34d>
 1314ae4: 68 78 21 56 01               	push	0x1562178
 1314ae9: 89 9d 74 ff ff ff            	mov	dword ptr [ebp - 0x8c], ebx
 1314aef: e8 fc b3 e8 ff               	call	0x119fef0
 1314af4: 8b c8                        	mov	ecx, eax
 1314af6: 83 c4 04                     	add	esp, 0x4
 1314af9: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1314afc: 8d 64 24 00                  	lea	esp, [esp]
 1314b00: 66 8b 11                     	mov	dx, word ptr [ecx]
 1314b03: 83 c1 02                     	add	ecx, 0x2
 1314b06: 66 3b d3                     	cmp	dx, bx
 1314b09: 75 f5                        	jne	0x1314b00 <.text+0x300>
 1314b0b: 2b ce                        	sub	ecx, esi
 1314b0d: d1 f9                        	sar	ecx
 1314b0f: 51                           	push	ecx
 1314b10: 50                           	push	eax
 1314b11: 8d 4d 8c                     	lea	ecx, [ebp - 0x74]
 1314b14: e8 17 b5 0f ff               	call	0x410030
 1314b19: 8d 8d 78 ff ff ff            	lea	ecx, [ebp - 0x88]
 1314b1f: 89 5d ac                     	mov	dword ptr [ebp - 0x54], ebx
 1314b22: e8 e9 1f e2 ff               	call	0x1136b10
 1314b27: 8d 85 23 ff ff ff            	lea	eax, [ebp - 0xdd]
 1314b2d: 50                           	push	eax
 1314b2e: e8 2d eb f0 ff               	call	0x1223660
 1314b33: 83 c4 04                     	add	esp, 0x4
 1314b36: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314b3c: 0f 84 1c 04 00 00            	je	0x1314f5e <.text+0x75e>
 1314b42: 89 85 74 ff ff ff            	mov	dword ptr [ebp - 0x8c], eax
 1314b48: e9 6e 02 00 00               	jmp	0x1314dbb <.text+0x5bb>
 1314b4d: 68 20 85 88 01               	push	0x1888520
 1314b52: e8 99 b3 e8 ff               	call	0x119fef0
 1314b57: 8b c8                        	mov	ecx, eax
 1314b59: 83 c4 04                     	add	esp, 0x4
 1314b5c: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1314b5f: 90                           	nop
 1314b60: 66 8b 11                     	mov	dx, word ptr [ecx]
 1314b63: 83 c1 02                     	add	ecx, 0x2
 1314b66: 66 3b d3                     	cmp	dx, bx
 1314b69: 75 f5                        	jne	0x1314b60 <.text+0x360>
 1314b6b: 2b ce                        	sub	ecx, esi
 1314b6d: d1 f9                        	sar	ecx
 1314b6f: 51                           	push	ecx
 1314b70: 8b 4d c4                     	mov	ecx, dword ptr [ebp - 0x3c]
 1314b73: 50                           	push	eax
 1314b74: 51                           	push	ecx
 1314b75: 53                           	push	ebx
 1314b76: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314b79: e8 b2 d0 0e ff               	call	0x401c30
 1314b7e: 85 c0                        	test	eax, eax
 1314b80: 75 14                        	jne	0x1314b96 <.text+0x396>
 1314b82: 8d 95 28 ff ff ff            	lea	edx, [ebp - 0xd8]
 1314b88: 52                           	push	edx
 1314b89: e8 c2 05 f1 ff               	call	0x1225150
 1314b8e: 83 c4 04                     	add	esp, 0x4
 1314b91: e9 25 02 00 00               	jmp	0x1314dbb <.text+0x5bb>
 1314b96: 68 f8 84 88 01               	push	0x18884f8
 1314b9b: e8 50 b3 e8 ff               	call	0x119fef0
 1314ba0: 8b c8                        	mov	ecx, eax
 1314ba2: 83 c4 04                     	add	esp, 0x4
 1314ba5: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1314ba8: eb 06                        	jmp	0x1314bb0 <.text+0x3b0>
 1314baa: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 1314bb0: 66 8b 11                     	mov	dx, word ptr [ecx]
 1314bb3: 83 c1 02                     	add	ecx, 0x2
 1314bb6: 66 3b d3                     	cmp	dx, bx
 1314bb9: 75 f5                        	jne	0x1314bb0 <.text+0x3b0>
 1314bbb: 2b ce                        	sub	ecx, esi
 1314bbd: d1 f9                        	sar	ecx
 1314bbf: 51                           	push	ecx
 1314bc0: 50                           	push	eax
 1314bc1: 8b 45 c4                     	mov	eax, dword ptr [ebp - 0x3c]
 1314bc4: 50                           	push	eax
 1314bc5: 53                           	push	ebx
 1314bc6: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314bc9: e8 62 d0 0e ff               	call	0x401c30
 1314bce: 85 c0                        	test	eax, eax
 1314bd0: 75 1a                        	jne	0x1314bec <.text+0x3ec>
 1314bd2: 8d 4d 8c                     	lea	ecx, [ebp - 0x74]
 1314bd5: 51                           	push	ecx
 1314bd6: e8 75 05 f1 ff               	call	0x1225150
 1314bdb: 53                           	push	ebx
 1314bdc: e8 7f ea f0 ff               	call	0x1223660
 1314be1: 83 c4 08                     	add	esp, 0x8
 1314be4: 89 45 ac                     	mov	dword ptr [ebp - 0x54], eax
 1314be7: e9 cf 01 00 00               	jmp	0x1314dbb <.text+0x5bb>
 1314bec: 68 d8 84 88 01               	push	0x18884d8
 1314bf1: e8 fa b2 e8 ff               	call	0x119fef0
 1314bf6: 8b c8                        	mov	ecx, eax
 1314bf8: 83 c4 04                     	add	esp, 0x4
 1314bfb: 8d 71 02                     	lea	esi, [ecx + 0x2]
 1314bfe: 8b ff                        	mov	edi, edi
 1314c00: 66 8b 11                     	mov	dx, word ptr [ecx]
 1314c03: 83 c1 02                     	add	ecx, 0x2
 1314c06: 66 3b d3                     	cmp	dx, bx
 1314c09: 75 f5                        	jne	0x1314c00 <.text+0x400>
 1314c0b: 8b 55 c4                     	mov	edx, dword ptr [ebp - 0x3c]
 1314c0e: 2b ce                        	sub	ecx, esi
 1314c10: d1 f9                        	sar	ecx
 1314c12: 51                           	push	ecx
 1314c13: 50                           	push	eax
 1314c14: 52                           	push	edx
 1314c15: 53                           	push	ebx
 1314c16: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314c19: e8 12 d0 0e ff               	call	0x401c30
 1314c1e: 85 c0                        	test	eax, eax
 1314c20: 0f 85 b0 01 00 00            	jne	0x1314dd6 <.text+0x5d6>
 1314c26: 8d 85 23 ff ff ff            	lea	eax, [ebp - 0xdd]
 1314c2c: 50                           	push	eax
 1314c2d: 89 bd 08 ff ff ff            	mov	dword ptr [ebp - 0xf8], edi
 1314c33: 89 bd 0c ff ff ff            	mov	dword ptr [ebp - 0xf4], edi
 1314c39: 89 bd 10 ff ff ff            	mov	dword ptr [ebp - 0xf0], edi
 1314c3f: 89 bd 14 ff ff ff            	mov	dword ptr [ebp - 0xec], edi
 1314c45: 89 bd 18 ff ff ff            	mov	dword ptr [ebp - 0xe8], edi
 1314c4b: e8 10 ea f0 ff               	call	0x1223660
 1314c50: 83 c4 04                     	add	esp, 0x4
 1314c53: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314c59: 0f 84 5c 01 00 00            	je	0x1314dbb <.text+0x5bb>
 1314c5f: 90                           	nop
 1314c60: 8d 8d 23 ff ff ff            	lea	ecx, [ebp - 0xdd]
 1314c66: 51                           	push	ecx
 1314c67: 89 85 08 ff ff ff            	mov	dword ptr [ebp - 0xf8], eax
 1314c6d: e8 ee e9 f0 ff               	call	0x1223660
 1314c72: 83 c4 04                     	add	esp, 0x4
 1314c75: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314c7b: 0f 84 37 01 00 00            	je	0x1314db8 <.text+0x5b8>
 1314c81: 8d 95 23 ff ff ff            	lea	edx, [ebp - 0xdd]
 1314c87: 52                           	push	edx
 1314c88: 89 85 0c ff ff ff            	mov	dword ptr [ebp - 0xf4], eax
 1314c8e: e8 cd e9 f0 ff               	call	0x1223660
 1314c93: 83 c4 04                     	add	esp, 0x4
 1314c96: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314c9c: 0f 84 16 01 00 00            	je	0x1314db8 <.text+0x5b8>
 1314ca2: 89 85 10 ff ff ff            	mov	dword ptr [ebp - 0xf0], eax
 1314ca8: 8d 85 23 ff ff ff            	lea	eax, [ebp - 0xdd]
 1314cae: 50                           	push	eax
 1314caf: e8 ac e9 f0 ff               	call	0x1223660
 1314cb4: 83 c4 04                     	add	esp, 0x4
 1314cb7: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314cbd: 0f 84 f5 00 00 00            	je	0x1314db8 <.text+0x5b8>
 1314cc3: 8d 8d 23 ff ff ff            	lea	ecx, [ebp - 0xdd]
 1314cc9: 51                           	push	ecx
 1314cca: 89 85 14 ff ff ff            	mov	dword ptr [ebp - 0xec], eax
 1314cd0: e8 8b e9 f0 ff               	call	0x1223660
 1314cd5: 83 c4 04                     	add	esp, 0x4
 1314cd8: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314cde: 0f 84 d4 00 00 00            	je	0x1314db8 <.text+0x5b8>
 1314ce4: 8d 95 c8 fe ff ff            	lea	edx, [ebp - 0x138]
 1314cea: 8b f8                        	mov	edi, eax
 1314cec: 52                           	push	edx
 1314ced: 8d 8d 48 ff ff ff            	lea	ecx, [ebp - 0xb8]
 1314cf3: 89 bd 18 ff ff ff            	mov	dword ptr [ebp - 0xe8], edi
 1314cf9: e8 42 f6 4a ff               	call	0x7c4340
 1314cfe: 8b f0                        	mov	esi, eax
 1314d00: 8d 85 08 ff ff ff            	lea	eax, [ebp - 0xf8]
 1314d06: 50                           	push	eax
 1314d07: 8d 8d bc fe ff ff            	lea	ecx, [ebp - 0x144]
 1314d0d: 51                           	push	ecx
 1314d0e: 8d 8d 48 ff ff ff            	lea	ecx, [ebp - 0xb8]
 1314d14: e8 47 ae 14 ff               	call	0x45fb60
 1314d19: 8b 08                        	mov	ecx, dword ptr [eax]
 1314d1b: 3b cb                        	cmp	ecx, ebx
 1314d1d: 0f 84 e0 02 00 00            	je	0x1315003 <.text+0x803>
 1314d23: 8b 09                        	mov	ecx, dword ptr [ecx]
 1314d25: 3b cb                        	cmp	ecx, ebx
 1314d27: 0f 84 d6 02 00 00            	je	0x1315003 <.text+0x803>
 1314d2d: 8b 16                        	mov	edx, dword ptr [esi]
 1314d2f: 3b d3                        	cmp	edx, ebx
 1314d31: 75 04                        	jne	0x1314d37 <.text+0x537>
 1314d33: 33 d2                        	xor	edx, edx
 1314d35: eb 02                        	jmp	0x1314d39 <.text+0x539>
 1314d37: 8b 12                        	mov	edx, dword ptr [edx]
 1314d39: 3b ca                        	cmp	ecx, edx
 1314d3b: 0f 85 c2 02 00 00            	jne	0x1315003 <.text+0x803>
 1314d41: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
 1314d44: 3b 56 08                     	cmp	edx, dword ptr [esi + 0x8]
 1314d47: 0f 94 c0                     	sete	al
 1314d4a: 3a c3                        	cmp	al, bl
 1314d4c: 74 2e                        	je	0x1314d7c <.text+0x57c>
 1314d4e: 8d 85 08 ff ff ff            	lea	eax, [ebp - 0xf8]
 1314d54: 50                           	push	eax
 1314d55: 8d 8d 48 ff ff ff            	lea	ecx, [ebp - 0xb8]
 1314d5b: e8 00 a6 e0 ff               	call	0x111f360
 1314d60: f3 0f 7e 85 08 ff ff ff      	movq	xmm0, qword ptr [ebp - 0xf8]
 1314d68: 66 0f d6 00                  	movq	qword ptr [eax], xmm0
 1314d6c: f3 0f 7e 85 10 ff ff ff      	movq	xmm0, qword ptr [ebp - 0xf0]
 1314d74: 66 0f d6 40 08               	movq	qword ptr [eax + 0x8], xmm0
 1314d79: 89 78 10                     	mov	dword ptr [eax + 0x10], edi
 1314d7c: 83 c8 ff                     	or	eax, -0x1
 1314d7f: 8d 8d 23 ff ff ff            	lea	ecx, [ebp - 0xdd]
 1314d85: 51                           	push	ecx
 1314d86: 89 85 08 ff ff ff            	mov	dword ptr [ebp - 0xf8], eax
 1314d8c: 89 85 0c ff ff ff            	mov	dword ptr [ebp - 0xf4], eax
 1314d92: 89 85 10 ff ff ff            	mov	dword ptr [ebp - 0xf0], eax
 1314d98: 89 85 14 ff ff ff            	mov	dword ptr [ebp - 0xec], eax
 1314d9e: 89 85 18 ff ff ff            	mov	dword ptr [ebp - 0xe8], eax
 1314da4: e8 b7 e8 f0 ff               	call	0x1223660
 1314da9: 83 c4 04                     	add	esp, 0x4
 1314dac: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314db2: 0f 85 a8 fe ff ff            	jne	0x1314c60 <.text+0x460>
 1314db8: 83 cf ff                     	or	edi, -0x1
 1314dbb: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314dbe: 6a 01                        	push	0x1
 1314dc0: 51                           	push	ecx
 1314dc1: e8 4a 04 f1 ff               	call	0x1225210
 1314dc6: 83 c4 08                     	add	esp, 0x8
 1314dc9: 84 c0                        	test	al, al
 1314dcb: 0f 85 df fc ff ff            	jne	0x1314ab0 <.text+0x2b0>
 1314dd1: e9 88 01 00 00               	jmp	0x1314f5e <.text+0x75e>
 1314dd6: 68 c0 84 88 01               	push	0x18884c0
 1314ddb: e8 10 b1 e8 ff               	call	0x119fef0
 1314de0: 50                           	push	eax
 1314de1: 8d 55 b0                     	lea	edx, [ebp - 0x50]
 1314de4: 52                           	push	edx
 1314de5: e8 96 cf 0e ff               	call	0x401d80
 1314dea: 83 c4 0c                     	add	esp, 0xc
 1314ded: 84 c0                        	test	al, al
 1314def: 0f 84 f8 00 00 00            	je	0x1314eed <.text+0x6ed>
 1314df5: 8d 85 23 ff ff ff            	lea	eax, [ebp - 0xdd]
 1314dfb: 50                           	push	eax
 1314dfc: 89 9d f8 fe ff ff            	mov	dword ptr [ebp - 0x108], ebx
 1314e02: 89 9d fc fe ff ff            	mov	dword ptr [ebp - 0x104], ebx
 1314e08: 89 9d 00 ff ff ff            	mov	dword ptr [ebp - 0x100], ebx
 1314e0e: 89 9d 04 ff ff ff            	mov	dword ptr [ebp - 0xfc], ebx
 1314e14: e8 47 e8 f0 ff               	call	0x1223660
 1314e19: 83 c4 04                     	add	esp, 0x4
 1314e1c: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314e22: 0f 84 ae 00 00 00            	je	0x1314ed6 <.text+0x6d6>
 1314e28: eb 06                        	jmp	0x1314e30 <.text+0x630>
 1314e2a: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
 1314e30: 8d 8d 23 ff ff ff            	lea	ecx, [ebp - 0xdd]
 1314e36: 51                           	push	ecx
 1314e37: 89 85 f8 fe ff ff            	mov	dword ptr [ebp - 0x108], eax
 1314e3d: e8 1e e8 f0 ff               	call	0x1223660
 1314e42: 83 c4 04                     	add	esp, 0x4
 1314e45: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314e4b: 0f 84 85 00 00 00            	je	0x1314ed6 <.text+0x6d6>
 1314e51: 8d 95 23 ff ff ff            	lea	edx, [ebp - 0xdd]
 1314e57: 52                           	push	edx
 1314e58: 89 85 fc fe ff ff            	mov	dword ptr [ebp - 0x104], eax
 1314e5e: e8 fd e7 f0 ff               	call	0x1223660
 1314e63: 83 c4 04                     	add	esp, 0x4
 1314e66: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314e6c: 74 68                        	je	0x1314ed6 <.text+0x6d6>
 1314e6e: 89 85 00 ff ff ff            	mov	dword ptr [ebp - 0x100], eax
 1314e74: 8d 85 23 ff ff ff            	lea	eax, [ebp - 0xdd]
 1314e7a: 50                           	push	eax
 1314e7b: e8 e0 e7 f0 ff               	call	0x1223660
 1314e80: 83 c4 04                     	add	esp, 0x4
 1314e83: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314e89: 74 4b                        	je	0x1314ed6 <.text+0x6d6>
 1314e8b: 8d 8d f8 fe ff ff            	lea	ecx, [ebp - 0x108]
 1314e91: 51                           	push	ecx
 1314e92: 8d 8d 78 ff ff ff            	lea	ecx, [ebp - 0x88]
 1314e98: 89 85 04 ff ff ff            	mov	dword ptr [ebp - 0xfc], eax
 1314e9e: e8 cd 54 fd ff               	call	0x12ea370
 1314ea3: 8d 95 23 ff ff ff            	lea	edx, [ebp - 0xdd]
 1314ea9: 52                           	push	edx
 1314eaa: 89 9d f8 fe ff ff            	mov	dword ptr [ebp - 0x108], ebx
 1314eb0: 89 9d fc fe ff ff            	mov	dword ptr [ebp - 0x104], ebx
 1314eb6: 89 9d 00 ff ff ff            	mov	dword ptr [ebp - 0x100], ebx
 1314ebc: 89 9d 04 ff ff ff            	mov	dword ptr [ebp - 0xfc], ebx
 1314ec2: e8 99 e7 f0 ff               	call	0x1223660
 1314ec7: 83 c4 04                     	add	esp, 0x4
 1314eca: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314ed0: 0f 85 5a ff ff ff            	jne	0x1314e30 <.text+0x630>
 1314ed6: 8d 85 74 ff ff ff            	lea	eax, [ebp - 0x8c]
 1314edc: 50                           	push	eax
 1314edd: 8d 8d 5c ff ff ff            	lea	ecx, [ebp - 0xa4]
 1314ee3: e8 38 f5 ff ff               	call	0x1314420
 1314ee8: e9 ce fe ff ff               	jmp	0x1314dbb <.text+0x5bb>
 1314eed: 68 a0 84 88 01               	push	0x18884a0
 1314ef2: e8 f9 af e8 ff               	call	0x119fef0
 1314ef7: 50                           	push	eax
 1314ef8: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314efb: 51                           	push	ecx
 1314efc: e8 7f ce 0e ff               	call	0x401d80
 1314f01: 83 c4 0c                     	add	esp, 0xc
 1314f04: 84 c0                        	test	al, al
 1314f06: 74 22                        	je	0x1314f2a <.text+0x72a>
 1314f08: 8d 95 23 ff ff ff            	lea	edx, [ebp - 0xdd]
 1314f0e: 52                           	push	edx
 1314f0f: e8 4c e7 f0 ff               	call	0x1223660
 1314f14: 83 c4 04                     	add	esp, 0x4
 1314f17: 38 9d 23 ff ff ff            	cmp	byte ptr [ebp - 0xdd], bl
 1314f1d: 74 3f                        	je	0x1314f5e <.text+0x75e>
 1314f1f: 89 85 70 ff ff ff            	mov	dword ptr [ebp - 0x90], eax
 1314f25: e9 91 fe ff ff               	jmp	0x1314dbb <.text+0x5bb>
 1314f2a: 68 20 2c 7f 01               	push	0x17f2c20
 1314f2f: e8 bc af e8 ff               	call	0x119fef0
 1314f34: 50                           	push	eax
 1314f35: 8d 45 b0                     	lea	eax, [ebp - 0x50]
 1314f38: 50                           	push	eax
 1314f39: e8 42 ce 0e ff               	call	0x401d80
 1314f3e: 83 c4 0c                     	add	esp, 0xc
 1314f41: 84 c0                        	test	al, al
 1314f43: 0f 84 72 fe ff ff            	je	0x1314dbb <.text+0x5bb>
 1314f49: 8b 8d 1c ff ff ff            	mov	ecx, dword ptr [ebp - 0xe4]
 1314f4f: 8d 95 24 ff ff ff            	lea	edx, [ebp - 0xdc]
 1314f55: 52                           	push	edx
 1314f56: 83 c1 4c                     	add	ecx, 0x4c
 1314f59: e8 e2 f7 ff ff               	call	0x1314740
 1314f5e: 8d 8d 74 ff ff ff            	lea	ecx, [ebp - 0x8c]
 1314f64: e8 e7 1e e2 ff               	call	0x1136e50
 1314f69: 8d 8d 24 ff ff ff            	lea	ecx, [ebp - 0xdc]
 1314f6f: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1314f73: e8 b8 9f e2 ff               	call	0x113ef30
 1314f78: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314f7b: 88 5d fc                     	mov	byte ptr [ebp - 0x4], bl
 1314f7e: e8 6d 36 14 ff               	call	0x4585f0
 1314f83: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 1314f86: 6a 01                        	push	0x1
 1314f88: 50                           	push	eax
 1314f89: e8 82 02 f1 ff               	call	0x1225210
 1314f8e: 83 c4 08                     	add	esp, 0x8
 1314f91: 84 c0                        	test	al, al
 1314f93: 0f 85 37 f9 ff ff            	jne	0x13148d0 <.text+0xd0>
 1314f99: eb 1a                        	jmp	0x1314fb5 <.text+0x7b5>
 1314f9b: 8d 8d 24 ff ff ff            	lea	ecx, [ebp - 0xdc]
 1314fa1: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
 1314fa5: e8 86 9f e2 ff               	call	0x113ef30
 1314faa: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 1314fad: 88 5d fc                     	mov	byte ptr [ebp - 0x4], bl
 1314fb0: e8 3b 36 14 ff               	call	0x4585f0
 1314fb5: 8b 8d f4 fe ff ff            	mov	ecx, dword ptr [ebp - 0x10c]
 1314fbb: 51                           	push	ecx
 1314fbc: b9 e4 10 da 01               	mov	ecx, 0x1da10e4
 1314fc1: e8 fa fb f0 ff               	call	0x1224bc0
 1314fc6: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 1314fca: 8b 95 1c ff ff ff            	mov	edx, dword ptr [ebp - 0xe4]
 1314fd0: 89 02                        	mov	dword ptr [edx], eax
 1314fd2: 72 0c                        	jb	0x1314fe0 <.text+0x7e0>
 1314fd4: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 1314fd7: 50                           	push	eax
 1314fd8: e8 4a 0b 0c 00               	call	0x13d5b27 <.text+0xc1327>
 1314fdd: 83 c4 04                     	add	esp, 0x4
 1314fe0: 8b 55 d0                     	mov	edx, dword ptr [ebp - 0x30]
 1314fe3: 33 c9                        	xor	ecx, ecx
 1314fe5: 52                           	push	edx
 1314fe6: c7 45 e8 07 00 00 00         	mov	dword ptr [ebp - 0x18], 0x7
 1314fed: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
 1314ff0: 66 89 4d d4                  	mov	word ptr [ebp - 0x2c], cx
 1314ff4: e8 2e 0b 0c 00               	call	0x13d5b27 <.text+0xc1327>
 1314ff9: 83 c4 04                     	add	esp, 0x4
 1314ffc: b0 01                        	mov	al, 0x1
 1314ffe: e9 4f f8 ff ff               	jmp	0x1314852 <.text+0x52>
 1315003: e8 9f 1d 0c 00               	call	0x13d6da7 <.text+0xc25a7>
 1315008: 8d 85 ec fe ff ff            	lea	eax, [ebp - 0x114]
 131500e: 50                           	push	eax
 131500f: 8d 8d d4 fe ff ff            	lea	ecx, [ebp - 0x12c]
 1315015: 89 9d ec fe ff ff            	mov	dword ptr [ebp - 0x114], ebx
 131501b: e8 aa 14 0c 00               	call	0x13d64ca <.text+0xc1cca>
 1315020: 68 90 0f 91 01               	push	0x1910f90
 1315025: 8d 8d d4 fe ff ff            	lea	ecx, [ebp - 0x12c]
 131502b: 51                           	push	ecx
 131502c: c7 85 d4 fe ff ff 84 20 56 01	mov	dword ptr [ebp - 0x12c], 0x1562084
 1315036: e8 5f 1b 0c 00               	call	0x13d6b9a <.text+0xc239a>
 131503b: 8d 95 f0 fe ff ff            	lea	edx, [ebp - 0x110]
 1315041: 52                           	push	edx
 1315042: 8d 8d e0 fe ff ff            	lea	ecx, [ebp - 0x120]
 1315048: 89 9d f0 fe ff ff            	mov	dword ptr [ebp - 0x110], ebx
 131504e: e8 77 14 0c 00               	call	0x13d64ca <.text+0xc1cca>
 1315053: 68 90 0f 91 01               	push	0x1910f90
 1315058: 8d 85 e0 fe ff ff            	lea	eax, [ebp - 0x120]
 131505e: 50                           	push	eax
 131505f: c7 85 e0 fe ff ff 84 20 56 01	mov	dword ptr [ebp - 0x120], 0x1562084
 1315069: e8 2c 1b 0c 00               	call	0x13d6b9a <.text+0xc239a>
 131506e: cc                           	int3
 131506f: cc                           	int3
