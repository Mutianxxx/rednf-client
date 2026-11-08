
<stdin>:	file format elf32-i386

Disassembly of section .text:

0057e0d0 <.text>:
  57e0d0: ce                           	into
  57e0d1: e8 5a 1a fd ff               	call	0x54fb30
  57e0d6: eb 02                        	jmp	0x57e0da <.text+0xa>
  57e0d8: 33 f6                        	xor	esi, esi
  57e0da: 89 b7 fc 01 00 00            	mov	dword ptr [edi + 0x1fc], esi
  57e0e0: a1 e4 64 b5 01               	mov	eax, dword ptr [0x1b564e4]
  57e0e5: 8b 30                        	mov	esi, dword ptr [eax]
  57e0e7: 68 40 b0 58 01               	push	0x158b040
  57e0ec: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  57e0f3: e8 f8 1d c2 00               	call	0x119fef0 <.text+0xc21e20>
  57e0f8: 8b 0d e4 64 b5 01            	mov	ecx, dword ptr [0x1b564e4]
  57e0fe: 8b 56 10                     	mov	edx, dword ptr [esi + 0x10]
  57e101: 83 c4 04                     	add	esp, 0x4
  57e104: 50                           	push	eax
  57e105: ff d2                        	call	edx
  57e107: 6a 28                        	push	0x28
  57e109: 89 87 9c 03 00 00            	mov	dword ptr [edi + 0x39c], eax
  57e10f: e8 06 8a e5 00               	call	0x13d6b1a <.text+0xe58a4a>
  57e114: 83 c4 04                     	add	esp, 0x4
  57e117: 89 85 74 ff ff ff            	mov	dword ptr [ebp - 0x8c], eax
  57e11d: c7 45 fc 03 00 00 00         	mov	dword ptr [ebp - 0x4], 0x3
  57e124: 3b c3                        	cmp	eax, ebx
  57e126: 74 09                        	je	0x57e131 <.text+0x61>
  57e128: 8b c8                        	mov	ecx, eax
  57e12a: e8 31 a8 d6 00               	call	0x12e8960 <.text+0xd6a890>
  57e12f: eb 02                        	jmp	0x57e133 <.text+0x63>
  57e131: 33 c0                        	xor	eax, eax
  57e133: 68 e8 af 58 01               	push	0x158afe8
  57e138: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  57e13f: 89 87 64 03 00 00            	mov	dword ptr [edi + 0x364], eax
  57e145: e8 a6 1d c2 00               	call	0x119fef0 <.text+0xc21e20>
  57e14a: 8b 8f 64 03 00 00            	mov	ecx, dword ptr [edi + 0x364]
  57e150: 83 c4 04                     	add	esp, 0x4
  57e153: 50                           	push	eax
  57e154: e8 b7 93 d6 00               	call	0x12e7510 <.text+0xd69440>
  57e159: 8b 0d 0c f7 a6 01            	mov	ecx, dword ptr [0x1a6f70c]
  57e15f: 6a 01                        	push	0x1
  57e161: e8 ea 79 bb 00               	call	0x1135b50 <.text+0xbb7a80>
  57e166: 8b cf                        	mov	ecx, edi
  57e168: 89 87 e4 02 00 00            	mov	dword ptr [edi + 0x2e4], eax
  57e16e: e8 2d 7d ff ff               	call	0x575ea0
  57e173: 68 b4 af 58 01               	push	0x158afb4
  57e178: e8 73 1d c2 00               	call	0x119fef0 <.text+0xc21e20>
  57e17d: 68 88 af 58 01               	push	0x158af88
  57e182: 8b f0                        	mov	esi, eax
  57e184: e8 67 1d c2 00               	call	0x119fef0 <.text+0xc21e20>
  57e189: 83 c4 08                     	add	esp, 0x8
  57e18c: 3b f3                        	cmp	esi, ebx
  57e18e: 0f 84 e8 0c 00 00            	je	0x57ee7c <.text+0xdac>
  57e194: 56                           	push	esi
  57e195: 50                           	push	eax
  57e196: e8 85 54 ca 00               	call	0x1223620 <.text+0xca5550>
  57e19b: 83 c4 08                     	add	esp, 0x8
  57e19e: 84 c0                        	test	al, al
  57e1a0: 0f 84 d6 0c 00 00            	je	0x57ee7c <.text+0xdac>
  57e1a6: 6a 08                        	push	0x8
  57e1a8: 89 5d 90                     	mov	dword ptr [ebp - 0x70], ebx
  57e1ab: e8 6a 89 e5 00               	call	0x13d6b1a <.text+0xe58a4a>
  57e1b0: 83 c4 04                     	add	esp, 0x4
  57e1b3: 3b c3                        	cmp	eax, ebx
  57e1b5: 0f 84 e1 0d 00 00            	je	0x57ef9c <.text+0xecc>
  57e1bb: 89 45 90                     	mov	dword ptr [ebp - 0x70], eax
  57e1be: 89 58 04                     	mov	dword ptr [eax + 0x4], ebx
  57e1c1: 33 c9                        	xor	ecx, ecx
  57e1c3: 89 08                        	mov	dword ptr [eax], ecx
  57e1c5: 8b 4d 90                     	mov	ecx, dword ptr [ebp - 0x70]
  57e1c8: 8d 45 90                     	lea	eax, [ebp - 0x70]
  57e1cb: 89 01                        	mov	dword ptr [ecx], eax
  57e1cd: bf 07 00 00 00               	mov	edi, 0x7
  57e1d2: 33 d2                        	xor	edx, edx
  57e1d4: 89 7d a8                     	mov	dword ptr [ebp - 0x58], edi
  57e1d7: 89 5d a4                     	mov	dword ptr [ebp - 0x5c], ebx
  57e1da: 66 89 55 94                  	mov	word ptr [ebp - 0x6c], dx
  57e1de: 6a 08                        	push	0x8
  57e1e0: c7 45 fc 04 00 00 00         	mov	dword ptr [ebp - 0x4], 0x4
  57e1e7: 89 5d b0                     	mov	dword ptr [ebp - 0x50], ebx
  57e1ea: e8 2b 89 e5 00               	call	0x13d6b1a <.text+0xe58a4a>
  57e1ef: 83 c4 04                     	add	esp, 0x4
  57e1f2: 3b c3                        	cmp	eax, ebx
  57e1f4: 0f 84 08 0e 00 00            	je	0x57f002 <.text+0xf32>
  57e1fa: 89 45 b0                     	mov	dword ptr [ebp - 0x50], eax
  57e1fd: 89 58 04                     	mov	dword ptr [eax + 0x4], ebx
  57e200: 33 c9                        	xor	ecx, ecx
  57e202: 89 08                        	mov	dword ptr [eax], ecx
  57e204: 8b 4d b0                     	mov	ecx, dword ptr [ebp - 0x50]
  57e207: 8d 45 b0                     	lea	eax, [ebp - 0x50]
  57e20a: 89 01                        	mov	dword ptr [ecx], eax
  57e20c: 33 d2                        	xor	edx, edx
  57e20e: 89 7d c8                     	mov	dword ptr [ebp - 0x38], edi
  57e211: 89 5d c4                     	mov	dword ptr [ebp - 0x3c], ebx
  57e214: 66 89 55 b4                  	mov	word ptr [ebp - 0x4c], dx
  57e218: 8d 8d 58 ff ff ff            	lea	ecx, [ebp - 0xa8]
  57e21e: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
  57e222: e8 69 e0 ff ff               	call	0x57c290
  57e227: 6a 01                        	push	0x1
  57e229: 8d 45 80                     	lea	eax, [ebp - 0x80]
  57e22c: 50                           	push	eax
  57e22d: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
  57e230: 51                           	push	ecx
  57e231: 8d 55 84                     	lea	edx, [ebp - 0x7c]
  57e234: 52                           	push	edx
  57e235: c6 45 fc 06                  	mov	byte ptr [ebp - 0x4], 0x6
  57e239: e8 22 7e ca 00               	call	0x1226060 <.text+0xca7f90>
  57e23e: 83 c4 10                     	add	esp, 0x10
  57e241: 84 c0                        	test	al, al
  57e243: 0f 84 a9 0b 00 00            	je	0x57edf2 <.text+0xd22>
  57e249: 8d a4 24 00 00 00 00         	lea	esp, [esp]
  57e250: 83 7d 84 02                  	cmp	dword ptr [ebp - 0x7c], 0x2
  57e254: 0f 85 7a 0b 00 00            	jne	0x57edd4 <.text+0xd04>
  57e25a: 68 60 af 58 01               	push	0x158af60
  57e25f: e8 8c 1c c2 00               	call	0x119fef0 <.text+0xc21e20>
  57e264: 8b c8                        	mov	ecx, eax
  57e266: 83 c4 04                     	add	esp, 0x4
  57e269: 8d 71 02                     	lea	esi, [ecx + 0x2]
  57e26c: 8d 64 24 00                  	lea	esp, [esp]
  57e270: 66 8b 11                     	mov	dx, word ptr [ecx]
  57e273: 83 c1 02                     	add	ecx, 0x2
  57e276: 66 3b d3                     	cmp	dx, bx
  57e279: 75 f5                        	jne	0x57e270 <.text+0x1a0>
  57e27b: 2b ce                        	sub	ecx, esi
  57e27d: d1 f9                        	sar	ecx
  57e27f: 51                           	push	ecx
  57e280: 50                           	push	eax
  57e281: 8b 45 c4                     	mov	eax, dword ptr [ebp - 0x3c]
  57e284: 50                           	push	eax
  57e285: 53                           	push	ebx
  57e286: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
  57e289: e8 a2 39 e8 ff               	call	0x401c30
  57e28e: 85 c0                        	test	eax, eax
  57e290: 0f 85 d4 01 00 00            	jne	0x57e46a <.text+0x39a>
  57e296: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
  57e299: e8 d2 33 d1 00               	call	0x1291670 <.text+0xd135a0>
  57e29e: 8d 4d 8f                     	lea	ecx, [ebp - 0x71]
  57e2a1: 51                           	push	ecx
  57e2a2: c6 45 fc 07                  	mov	byte ptr [ebp - 0x4], 0x7
  57e2a6: e8 b5 53 ca 00               	call	0x1223660 <.text+0xca5590>
  57e2ab: 83 c4 04                     	add	esp, 0x4
  57e2ae: 8b f0                        	mov	esi, eax
  57e2b0: 38 5d 8f                     	cmp	byte ptr [ebp - 0x71], bl
  57e2b3: 0f 84 57 01 00 00            	je	0x57e410 <.text+0x340>
  57e2b9: 8d a4 24 00 00 00 00         	lea	esp, [esp]
  57e2c0: 8d 55 8f                     	lea	edx, [ebp - 0x71]
  57e2c3: 52                           	push	edx
  57e2c4: e8 97 53 ca 00               	call	0x1223660 <.text+0xca5590>
  57e2c9: 83 c4 04                     	add	esp, 0x4
  57e2cc: 8b f8                        	mov	edi, eax
  57e2ce: 38 5d 8f                     	cmp	byte ptr [ebp - 0x71], bl
  57e2d1: 0f 84 53 01 00 00            	je	0x57e42a <.text+0x35a>
  57e2d7: 8d 45 8f                     	lea	eax, [ebp - 0x71]
  57e2da: 50                           	push	eax
  57e2db: e8 80 53 ca 00               	call	0x1223660 <.text+0xca5590>
  57e2e0: 83 c4 04                     	add	esp, 0x4
  57e2e3: 38 5d 8f                     	cmp	byte ptr [ebp - 0x71], bl
  57e2e6: 0f 84 44 01 00 00            	je	0x57e430 <.text+0x360>
  57e2ec: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  57e2ef: 51                           	push	ecx
  57e2f0: 8d 95 7c ff ff ff            	lea	edx, [ebp - 0x84]
  57e2f6: 52                           	push	edx
  57e2f7: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
  57e2fa: 89 85 7c ff ff ff            	mov	dword ptr [ebp - 0x84], eax
  57e300: e8 2b 26 c2 00               	call	0x11a0930 <.text+0xc22860>
  57e305: 8d 45 ec                     	lea	eax, [ebp - 0x14]
  57e308: 50                           	push	eax
  57e309: 8d 8d 7c ff ff ff            	lea	ecx, [ebp - 0x84]
  57e30f: 51                           	push	ecx
  57e310: 8d 4d e4                     	lea	ecx, [ebp - 0x1c]
  57e313: 89 bd 7c ff ff ff            	mov	dword ptr [ebp - 0x84], edi
  57e319: e8 12 26 c2 00               	call	0x11a0930 <.text+0xc22860>
  57e31e: 8d 8d 18 ff ff ff            	lea	ecx, [ebp - 0xe8]
  57e324: e8 47 41 c2 00               	call	0x11a2470 <.text+0xc243a0>
  57e329: 8d 95 20 ff ff ff            	lea	edx, [ebp - 0xe0]
  57e32f: 52                           	push	edx
  57e330: 8d 85 7c ff ff ff            	lea	eax, [ebp - 0x84]
  57e336: 50                           	push	eax
  57e337: 8d 8d 18 ff ff ff            	lea	ecx, [ebp - 0xe8]
  57e33d: c6 45 fc 0b                  	mov	byte ptr [ebp - 0x4], 0xb
  57e341: 89 b5 7c ff ff ff            	mov	dword ptr [ebp - 0x84], esi
  57e347: e8 e4 25 c2 00               	call	0x11a0930 <.text+0xc22860>
  57e34c: 8d 8d 18 ff ff ff            	lea	ecx, [ebp - 0xe8]
  57e352: 51                           	push	ecx
  57e353: 8b 8d 78 ff ff ff            	mov	ecx, dword ptr [ebp - 0x88]
  57e359: 81 c1 14 02 00 00            	add	ecx, 0x214
  57e35f: c6 45 fc 0c                  	mov	byte ptr [ebp - 0x4], 0xc
  57e363: e8 38 76 ff ff               	call	0x5759a0
  57e368: 8d 95 28 ff ff ff            	lea	edx, [ebp - 0xd8]
  57e36e: 8b f0                        	mov	esi, eax
  57e370: 52                           	push	edx
  57e371: 8d 45 e0                     	lea	eax, [ebp - 0x20]
  57e374: 50                           	push	eax
  57e375: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
  57e378: e8 63 2a c2 00               	call	0x11a0de0 <.text+0xc22d10>
  57e37d: 8b 8d 28 ff ff ff            	mov	ecx, dword ptr [ebp - 0xd8]
  57e383: 8d 56 08                     	lea	edx, [esi + 0x8]
  57e386: 52                           	push	edx
  57e387: 8d 45 88                     	lea	eax, [ebp - 0x78]
  57e38a: 89 4d 88                     	mov	dword ptr [ebp - 0x78], ecx
  57e38d: 50                           	push	eax
  57e38e: 8b ce                        	mov	ecx, esi
  57e390: e8 9b 25 c2 00               	call	0x11a0930 <.text+0xc22860>
  57e395: 8d 8d 24 ff ff ff            	lea	ecx, [ebp - 0xdc]
  57e39b: 51                           	push	ecx
  57e39c: 8d 55 ec                     	lea	edx, [ebp - 0x14]
  57e39f: 52                           	push	edx
  57e3a0: 8d 4d e4                     	lea	ecx, [ebp - 0x1c]
  57e3a3: e8 38 2a c2 00               	call	0x11a0de0 <.text+0xc22d10>
  57e3a8: 8b 85 24 ff ff ff            	mov	eax, dword ptr [ebp - 0xdc]
  57e3ae: 8d 4e 14                     	lea	ecx, [esi + 0x14]
  57e3b1: 51                           	push	ecx
  57e3b2: 8d 55 88                     	lea	edx, [ebp - 0x78]
  57e3b5: 52                           	push	edx
  57e3b6: 8d 4e 0c                     	lea	ecx, [esi + 0xc]
  57e3b9: 89 45 88                     	mov	dword ptr [ebp - 0x78], eax
  57e3bc: e8 6f 25 c2 00               	call	0x11a0930 <.text+0xc22860>
  57e3c1: 8d 8d 18 ff ff ff            	lea	ecx, [ebp - 0xe8]
  57e3c7: c6 45 fc 07                  	mov	byte ptr [ebp - 0x4], 0x7
  57e3cb: e8 f0 28 c2 00               	call	0x11a0cc0 <.text+0xc22bf0>
