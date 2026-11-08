
<stdin>:	file format elf32-i386

Disassembly of section .text:

004ec110 <.text>:
  4ec110: ff 8d 55 e4 52 8d            	dec	dword ptr [ebp - 0x72ad1bab]
  4ec116: 45                           	inc	ebp
  4ec117: d4 50                        	aam	0x50
  4ec119: 8b ce                        	mov	ecx, esi
  4ec11b: c7 45 e4 cb 00 00 00         	mov	dword ptr [ebp - 0x1c], 0xcb
  4ec122: c7 45 e8 80 68 4e 00         	mov	dword ptr [ebp - 0x18], 0x4e6880
  4ec129: e8 b2 c6 fe ff               	call	0x4d87e0
  4ec12e: 8d 4d e4                     	lea	ecx, [ebp - 0x1c]
  4ec131: 51                           	push	ecx
  4ec132: 8d 55 d4                     	lea	edx, [ebp - 0x2c]
  4ec135: 52                           	push	edx
  4ec136: 8b ce                        	mov	ecx, esi
  4ec138: c7 45 e4 2c 01 00 00         	mov	dword ptr [ebp - 0x1c], 0x12c
  4ec13f: c7 45 e8 c0 68 4e 00         	mov	dword ptr [ebp - 0x18], 0x4e68c0
  4ec146: e8 95 c6 fe ff               	call	0x4d87e0
  4ec14b: 8b c6                        	mov	eax, esi
  4ec14d: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4ec150: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4ec157: 59                           	pop	ecx
  4ec158: 5e                           	pop	esi
  4ec159: 8b e5                        	mov	esp, ebp
  4ec15b: 5d                           	pop	ebp
  4ec15c: c3                           	ret
  4ec15d: cc                           	int3
  4ec15e: cc                           	int3
  4ec15f: cc                           	int3
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
  4ec19a: e8 e1 41 cc 00               	call	0x11b0380 <.text+0xcc4270>
  4ec19f: 83 c4 04                     	add	esp, 0x4
  4ec1a2: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
  4ec1a5: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  4ec1ac: 85 c0                        	test	eax, eax
  4ec1ae: 74 09                        	je	0x4ec1b9 <.text+0xa9>
  4ec1b0: 8b c8                        	mov	ecx, eax
  4ec1b2: e8 c9 2d cd 00               	call	0x11bef80 <.text+0xcd2e70>
  4ec1b7: eb 02                        	jmp	0x4ec1bb <.text+0xab>
  4ec1b9: 33 c0                        	xor	eax, eax
  4ec1bb: 83 cb ff                     	or	ebx, -0x1
  4ec1be: 68 b8 02 00 00               	push	0x2b8
  4ec1c3: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec1c6: 89 86 b4 00 00 00            	mov	dword ptr [esi + 0xb4], eax
  4ec1cc: e8 af 41 cc 00               	call	0x11b0380 <.text+0xcc4270>
  4ec1d1: 83 c4 04                     	add	esp, 0x4
  4ec1d4: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
  4ec1d7: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
  4ec1de: 85 c0                        	test	eax, eax
  4ec1e0: 74 09                        	je	0x4ec1eb <.text+0xdb>
  4ec1e2: 8b c8                        	mov	ecx, eax
  4ec1e4: e8 97 2d cd 00               	call	0x11bef80 <.text+0xcd2e70>
  4ec1e9: eb 02                        	jmp	0x4ec1ed <.text+0xdd>
  4ec1eb: 33 c0                        	xor	eax, eax
  4ec1ed: 68 b8 02 00 00               	push	0x2b8
  4ec1f2: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec1f5: 89 86 b8 00 00 00            	mov	dword ptr [esi + 0xb8], eax
  4ec1fb: e8 80 41 cc 00               	call	0x11b0380 <.text+0xcc4270>
  4ec200: 83 c4 04                     	add	esp, 0x4
  4ec203: 89 45 08                     	mov	dword ptr [ebp + 0x8], eax
  4ec206: c7 45 fc 02 00 00 00         	mov	dword ptr [ebp - 0x4], 0x2
  4ec20d: 85 c0                        	test	eax, eax
  4ec20f: 74 09                        	je	0x4ec21a <.text+0x10a>
  4ec211: 8b c8                        	mov	ecx, eax
  4ec213: e8 68 2d cd 00               	call	0x11bef80 <.text+0xcd2e70>
  4ec218: eb 02                        	jmp	0x4ec21c <.text+0x10c>
  4ec21a: 33 c0                        	xor	eax, eax
  4ec21c: 89 86 bc 00 00 00            	mov	dword ptr [esi + 0xbc], eax
  4ec222: 8b 86 b4 00 00 00            	mov	eax, dword ptr [esi + 0xb4]
  4ec228: 50                           	push	eax
  4ec229: 8b cf                        	mov	ecx, edi
  4ec22b: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4ec22e: e8 fd 30 cd 00               	call	0x11bf330 <.text+0xcd3220>
  4ec233: 8b 8e b8 00 00 00            	mov	ecx, dword ptr [esi + 0xb8]
  4ec239: 51                           	push	ecx
  4ec23a: 8b cf                        	mov	ecx, edi
  4ec23c: e8 ef 30 cd 00               	call	0x11bf330 <.text+0xcd3220>
  4ec241: 8b 96 bc 00 00 00            	mov	edx, dword ptr [esi + 0xbc]
  4ec247: 52                           	push	edx
  4ec248: 8b cf                        	mov	ecx, edi
  4ec24a: e8 e1 30 cd 00               	call	0x11bf330 <.text+0xcd3220>
  4ec24f: 8b                           	<unknown>
