
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
