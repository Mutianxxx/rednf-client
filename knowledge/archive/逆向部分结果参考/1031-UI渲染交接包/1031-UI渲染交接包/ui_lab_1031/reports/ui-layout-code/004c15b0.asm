
<stdin>:	file format elf32-i386

Disassembly of section .text:

004c15b0 <.text>:
  4c15b0: 55                           	push	ebp
  4c15b1: 8b ec                        	mov	ebp, esp
  4c15b3: 6a ff                        	push	-0x1
  4c15b5: 68 be 17 41 01               	push	0x14117be
  4c15ba: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4c15c0: 50                           	push	eax
  4c15c1: 83 ec 10                     	sub	esp, 0x10
  4c15c4: 53                           	push	ebx
  4c15c5: 56                           	push	esi
  4c15c6: 57                           	push	edi
  4c15c7: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4c15cc: 33 c5                        	xor	eax, ebp
  4c15ce: 50                           	push	eax
  4c15cf: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4c15d2: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4c15d8: 8b d9                        	mov	ebx, ecx
  4c15da: 89 5d e4                     	mov	dword ptr [ebp - 0x1c], ebx
  4c15dd: f6 05 d8 97 a4 01 01         	test	byte ptr [0x1a497d8], 0x1
  4c15e4: 75 2c                        	jne	0x4c1612 <.text+0x62>
  4c15e6: 83 0d d8 97 a4 01 01         	or	dword ptr [0x1a497d8], 0x1
  4c15ed: b9 18 97 a4 01               	mov	ecx, 0x1a49718
  4c15f2: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  4c15f9: e8 e2 7b 02 00               	call	0x4e91e0 <.text+0x27c30>
  4c15fe: 68 c0 3b 54 01               	push	0x1543bc0
  4c1603: e8 02 5d f1 00               	call	0x13d730a <.text+0xf15d5a>
  4c1608: 83 c4 04                     	add	esp, 0x4
  4c160b: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  4c1612: 6a 28                        	push	0x28
  4c1614: b9 18 97 a4 01               	mov	ecx, 0x1a49718
  4c1619: e8 e2 6a 02 00               	call	0x4e8100 <.text+0x26b50>
  4c161e: 8b f0                        	mov	esi, eax
  4c1620: 85 f6                        	test	esi, esi
  4c1622: 0f 84 e5 00 00 00            	je	0x4c170d <.text+0x15d>
  4c1628: 8b ce                        	mov	ecx, esi
  4c162a: e8 31 e9 f6 ff               	call	0x42ff60
  4c162f: 8b ce                        	mov	ecx, esi
  4c1631: 8b f8                        	mov	edi, eax
  4c1633: e8 c8 cc cf 00               	call	0x11be300 <.text+0xcfcd50>
  4c1638: 8b f0                        	mov	esi, eax
  4c163a: 8b 83 b0 0b 00 00            	mov	eax, dword ptr [ebx + 0xbb0]
  4c1640: 50                           	push	eax
  4c1641: 89 75 e8                     	mov	dword ptr [ebp - 0x18], esi
  4c1644: e8 57 dc b7 00               	call	0x103f2a0 <.text+0xb7dcf0>
  4c1649: 8b c8                        	mov	ecx, eax
  4c164b: e8 00 c4 b7 00               	call	0x103da50 <.text+0xb7c4a0>
  4c1650: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
  4c1653: 85 c0                        	test	eax, eax
  4c1655: 75 30                        	jne	0x4c1687 <.text+0xd7>
  4c1657: e8 b4 4d 24 00               	call	0x706410 <.text+0x244e60>
  4c165c: 8b 88 ac 00 00 00            	mov	ecx, dword ptr [eax + 0xac]
  4c1662: 8b 81 d4 00 00 00            	mov	eax, dword ptr [ecx + 0xd4]
  4c1668: 8b 93 b0 0b 00 00            	mov	edx, dword ptr [ebx + 0xbb0]
  4c166e: 50                           	push	eax
  4c166f: 52                           	push	edx
  4c1670: e8 2b dc b7 00               	call	0x103f2a0 <.text+0xb7dcf0>
  4c1675: 8b c8                        	mov	ecx, eax
  4c1677: e8 d4 c4 b7 00               	call	0x103db50 <.text+0xb7c5a0>
  4c167c: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
  4c167f: 85 c0                        	test	eax, eax
  4c1681: 0f 84 86 00 00 00            	je	0x4c170d <.text+0x15d>
  4c1687: 8d 5f 14                     	lea	ebx, [edi + 0x14]
  4c168a: c7 45 f0 14 00 00 00         	mov	dword ptr [ebp - 0x10], 0x14
  4c1691: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
  4c1697: 8b 01                        	mov	eax, dword ptr [ecx]
  4c1699: 8b 50 38                     	mov	edx, dword ptr [eax + 0x38]
  4c169c: 68 00 00 00 ff               	push	0xff000000
  4c16a1: 56                           	push	esi
  4c16a2: 53                           	push	ebx
  4c16a3: 56                           	push	esi
  4c16a4: 57                           	push	edi
  4c16a5: ff d2                        	call	edx
  4c16a7: 46                           	inc	esi
  4c16a8: ff 4d f0                     	dec	dword ptr [ebp - 0x10]
  4c16ab: 75 e4                        	jne	0x4c1691 <.text+0xe1>
  4c16ad: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
