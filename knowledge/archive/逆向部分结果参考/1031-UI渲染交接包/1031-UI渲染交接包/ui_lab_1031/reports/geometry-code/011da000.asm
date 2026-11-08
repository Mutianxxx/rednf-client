
<stdin>:	file format elf32-i386

Disassembly of section .text:

011da000 <.text>:
 11da000: 21 8d 8e f4 02 00            	and	dword ptr [ebp + 0x2f48e], ecx
 11da006: 00 c7                        	add	bh, al
 11da008: 05 00 70 b5 01               	add	eax, 0x1b57000
 11da00d: 00 00                        	add	byte ptr [eax], al
 11da00f: 00 00                        	add	byte ptr [eax], al
 11da011: e8 5a 72 00 00               	call	0x11e1270 <.text+0x7270>
 11da016: 6a 00                        	push	0x0
 11da018: e8 63 b3 00 00               	call	0x11e5380 <.text+0xb380>
 11da01d: 83 c4 04                     	add	esp, 0x4
 11da020: eb 17                        	jmp	0x11da039 <.text+0x39>
 11da022: 8b ce                        	mov	ecx, esi
 11da024: e8 f7 43 fe ff               	call	0x11be420
 11da029: 50                           	push	eax
 11da02a: e8 61 b3 00 00               	call	0x11e5390 <.text+0xb390>
 11da02f: 6a 01                        	push	0x1
 11da031: e8 4a b3 00 00               	call	0x11e5380 <.text+0xb380>
 11da036: 83 c4 08                     	add	esp, 0x8
 11da039: 85 ff                        	test	edi, edi
 11da03b: 0f 84 0e 02 00 00            	je	0x11da24f <.text+0x24f>
 11da041: e8 ba b2 00 00               	call	0x11e5300 <.text+0xb300>
 11da046: 84 c0                        	test	al, al
 11da048: 0f b7 03                     	movzx	eax, word ptr [ebx]
 11da04b: 0f 84 b8 00 00 00            	je	0x11da109 <.text+0x109>
 11da051: 83 f8 08                     	cmp	eax, 0x8
 11da054: 0f 84 f5 01 00 00            	je	0x11da24f <.text+0x24f>
 11da05a: 66 83 f8 1b                  	cmp	ax, 0x1b
 11da05e: 0f 84 45 01 00 00            	je	0x11da1a9 <.text+0x1a9>
 11da064: 80 be c5 02 00 00 00         	cmp	byte ptr [esi + 0x2c5], 0x0
 11da06b: 0f 84 ad 00 00 00            	je	0x11da11e <.text+0x11e>
 11da071: 8b 86 cc 02 00 00            	mov	eax, dword ptr [esi + 0x2cc]
 11da077: 8b 8e d0 02 00 00            	mov	ecx, dword ptr [esi + 0x2d0]
 11da07d: 8b 16                        	mov	edx, dword ptr [esi]
 11da07f: 8b 92 b0 00 00 00            	mov	edx, dword ptr [edx + 0xb0]
 11da085: 2b c8                        	sub	ecx, eax
 11da087: 51                           	push	ecx
 11da088: 50                           	push	eax
 11da089: 8b ce                        	mov	ecx, esi
 11da08b: ff d2                        	call	edx
 11da08d: 53                           	push	ebx
 11da08e: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11da091: e8 8a 7e 23 ff               	call	0x411f20
 11da096: 8b 8e cc 02 00 00            	mov	ecx, dword ptr [esi + 0x2cc]
 11da09c: 8b 86 68 03 00 00            	mov	eax, dword ptr [esi + 0x368]
 11da0a2: 8b 38                        	mov	edi, dword ptr [eax]
 11da0a4: 51                           	push	ecx
 11da0a5: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da0ab: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
 11da0b2: e8 c9 ef 3d ff               	call	0x5b9080
 11da0b7: 8b 8e 68 03 00 00            	mov	ecx, dword ptr [esi + 0x368]
 11da0bd: 50                           	push	eax
 11da0be: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
 11da0c1: 8d 55 d0                     	lea	edx, [ebp - 0x30]
 11da0c4: 52                           	push	edx
 11da0c5: ff d0                        	call	eax
 11da0c7: 83 7d e4 00                  	cmp	dword ptr [ebp - 0x1c], 0x0
 11da0cb: 0f 84 c2 00 00 00            	je	0x11da193 <.text+0x193>
 11da0d1: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 11da0d5: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 11da0d8: 73 03                        	jae	0x11da0dd <.text+0xdd>
 11da0da: 8d 45 d4                     	lea	eax, [ebp - 0x2c]
 11da0dd: 8b 16                        	mov	edx, dword ptr [esi]
 11da0df: 8b 92 ac 00 00 00            	mov	edx, dword ptr [edx + 0xac]
 11da0e5: 50                           	push	eax
 11da0e6: 8b 86 cc 02 00 00            	mov	eax, dword ptr [esi + 0x2cc]
 11da0ec: 50                           	push	eax
 11da0ed: 8b ce                        	mov	ecx, esi
 11da0ef: ff d2                        	call	edx
 11da0f1: ff 8e c8 02 00 00            	dec	dword ptr [esi + 0x2c8]
 11da0f7: 0f 89 81 00 00 00            	jns	0x11da17e <.text+0x17e>
 11da0fd: c7 86 c8 02 00 00 00 00 00 00	mov	dword ptr [esi + 0x2c8], 0x0
 11da107: eb 75                        	jmp	0x11da17e <.text+0x17e>
 11da109: 83 f8 08                     	cmp	eax, 0x8
 11da10c: 0f 85 48 ff ff ff            	jne	0x11da05a <.text+0x5a>
 11da112: 8b ce                        	mov	ecx, esi
 11da114: e8 17 f3 ff ff               	call	0x11d9430
 11da119: e9 8b 00 00 00               	jmp	0x11da1a9 <.text+0x1a9>
 11da11e: 53                           	push	ebx
 11da11f: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11da122: e8 f9 7d 23 ff               	call	0x411f20
 11da127: 8b 8e 68 03 00 00            	mov	ecx, dword ptr [esi + 0x368]
 11da12d: 8b 96 c8 02 00 00            	mov	edx, dword ptr [esi + 0x2c8]
 11da133: 8b 39                        	mov	edi, dword ptr [ecx]
 11da135: 52                           	push	edx
 11da136: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da13c: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
 11da143: e8 38 ef 3d ff               	call	0x5b9080
 11da148: 8b 8e 68 03 00 00            	mov	ecx, dword ptr [esi + 0x368]
 11da14e: 8b 57 04                     	mov	edx, dword ptr [edi + 0x4]
 11da151: 50                           	push	eax
 11da152: 8d 45 d0                     	lea	eax, [ebp - 0x30]
 11da155: 50                           	push	eax
 11da156: ff d2                        	call	edx
 11da158: 83 7d e4 00                  	cmp	dword ptr [ebp - 0x1c], 0x0
 11da15c: 74 3c                        	je	0x11da19a <.text+0x19a>
 11da15e: 83 7d e8 08                  	cmp	dword ptr [ebp - 0x18], 0x8
 11da162: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
 11da165: 73 03                        	jae	0x11da16a <.text+0x16a>
 11da167: 8d 45 d4                     	lea	eax, [ebp - 0x2c]
 11da16a: 8b 16                        	mov	edx, dword ptr [esi]
 11da16c: 8b 92 ac 00 00 00            	mov	edx, dword ptr [edx + 0xac]
 11da172: 50                           	push	eax
 11da173: 8b 86 c8 02 00 00            	mov	eax, dword ptr [esi + 0x2c8]
 11da179: 50                           	push	eax
 11da17a: 8b ce                        	mov	ecx, esi
 11da17c: ff d2                        	call	edx
 11da17e: 8b 45 e4                     	mov	eax, dword ptr [ebp - 0x1c]
 11da181: 01 86 c8 02 00 00            	add	dword ptr [esi + 0x2c8], eax
 11da187: 8b 86 c8 02 00 00            	mov	eax, dword ptr [esi + 0x2c8]
 11da18d: 89 86 cc 02 00 00            	mov	dword ptr [esi + 0x2cc], eax
 11da193: c6 86 38 03 00 00 01         	mov	byte ptr [esi + 0x338], 0x1
 11da19a: 8d 4d d0                     	lea	ecx, [ebp - 0x30]
 11da19d: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11da1a4: e8 47 e4 27 ff               	call	0x4585f0
 11da1a9: 66 83 3b 08                  	cmp	word ptr [ebx], 0x8
 11da1ad: 75 06                        	jne	0x11da1b5 <.text+0x1b5>
 11da1af: 83 7d 84 00                  	cmp	dword ptr [ebp - 0x7c], 0x0
 11da1b3: 75 07                        	jne	0x11da1bc <.text+0x1bc>
 11da1b5: c6 86 c5 02 00 00 00         	mov	byte ptr [esi + 0x2c5], 0x0
 11da1bc: e8 cf b0 00 00               	call	0x11e5290 <.text+0xb290>
 11da1c1: 8b 8e c8 02 00 00            	mov	ecx, dword ptr [esi + 0x2c8]
 11da1c7: 51                           	push	ecx
 11da1c8: 8b ce                        	mov	ecx, esi
 11da1ca: e8 71 e7 ff ff               	call	0x11d8940
 11da1cf: 8b ce                        	mov	ecx, esi
 11da1d1: 89 86 30 03 00 00            	mov	dword ptr [esi + 0x330], eax
 11da1d7: e8 44 42 fe ff               	call	0x11be420
 11da1dc: 8b 96 bc 02 00 00            	mov	edx, dword ptr [esi + 0x2bc]
 11da1e2: 8b d8                        	mov	ebx, eax
 11da1e4: 8b 3b                        	mov	edi, dword ptr [ebx]
 11da1e6: 52                           	push	edx
 11da1e7: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da1ed: e8 8e ee 3d ff               	call	0x5b9080
 11da1f2: 50                           	push	eax
 11da1f3: 8b 47 3c                     	mov	eax, dword ptr [edi + 0x3c]
 11da1f6: 8b cb                        	mov	ecx, ebx
 11da1f8: ff d0                        	call	eax
 11da1fa: 8b 8e 58 03 00 00            	mov	ecx, dword ptr [esi + 0x358]
 11da200: 89 86 5c 03 00 00            	mov	dword ptr [esi + 0x35c], eax
 11da206: 8b 86 30 03 00 00            	mov	eax, dword ptr [esi + 0x330]
 11da20c: 3b c1                        	cmp	eax, ecx
 11da20e: 72 0c                        	jb	0x11da21c <.text+0x21c>
 11da210: 8b 96 54 03 00 00            	mov	edx, dword ptr [esi + 0x354]
 11da216: 03 d1                        	add	edx, ecx
 11da218: 3b c2                        	cmp	eax, edx
 11da21a: 72 38                        	jb	0x11da254 <.text+0x254>
 11da21c: 2b 86 54 03 00 00            	sub	eax, dword ptr [esi + 0x354]
 11da222: 78 09                        	js	0x11da22d <.text+0x22d>
 11da224: 40                           	inc	eax
 11da225: 89 86 58 03 00 00            	mov	dword ptr [esi + 0x358], eax
 11da22b: eb 0a                        	jmp	0x11da237 <.text+0x237>
 11da22d: c7 86 58 03 00 00 00 00 00 00	mov	dword ptr [esi + 0x358], 0x0
 11da237: 8b 8e 60 03 00 00            	mov	ecx, dword ptr [esi + 0x360]
 11da23d: 85 c9                        	test	ecx, ecx
 11da23f: 74 13                        	je	0x11da254 <.text+0x254>
 11da241: 8b 86 58 03 00 00            	mov	eax, dword ptr [esi + 0x358]
 11da247: 50                           	push	eax
 11da248: e8 73 d6 fe ff               	call	0x11c78c0
 11da24d: eb 05                        	jmp	0x11da254 <.text+0x254>
 11da24f: e8 cc b0 00 00               	call	0x11e5320 <.text+0xb320>
 11da254: 8b 5d 84                     	mov	ebx, dword ptr [ebp - 0x7c]
 11da257: 85 db                        	test	ebx, ebx
 11da259: 0f 84 da 01 00 00            	je	0x11da439 <.text+0x439>
 11da25f: 80 be c5 02 00 00 00         	cmp	byte ptr [esi + 0x2c5], 0x0
 11da266: 74 40                        	je	0x11da2a8 <.text+0x2a8>
 11da268: 8b 86 cc 02 00 00            	mov	eax, dword ptr [esi + 0x2cc]
 11da26e: 8b 8e d0 02 00 00            	mov	ecx, dword ptr [esi + 0x2d0]
 11da274: 8b 16                        	mov	edx, dword ptr [esi]
 11da276: 8b 92 b0 00 00 00            	mov	edx, dword ptr [edx + 0xb0]
 11da27c: 2b c8                        	sub	ecx, eax
 11da27e: 51                           	push	ecx
 11da27f: 50                           	push	eax
 11da280: 8b ce                        	mov	ecx, esi
 11da282: ff d2                        	call	edx
 11da284: 8b be cc 02 00 00            	mov	edi, dword ptr [esi + 0x2cc]
 11da28a: e8 e1 b0 00 00               	call	0x11e5370 <.text+0xb370>
 11da28f: 03 c7                        	add	eax, edi
 11da291: 03 fb                        	add	edi, ebx
 11da293: 89 86 3c 03 00 00            	mov	dword ptr [esi + 0x33c], eax
 11da299: 89 be d0 02 00 00            	mov	dword ptr [esi + 0x2d0], edi
 11da29f: c6 86 38 03 00 00 01         	mov	byte ptr [esi + 0x338], 0x1
 11da2a6: eb 12                        	jmp	0x11da2ba <.text+0x2ba>
 11da2a8: 8b 86 c8 02 00 00            	mov	eax, dword ptr [esi + 0x2c8]
 11da2ae: 89 86 cc 02 00 00            	mov	dword ptr [esi + 0x2cc], eax
 11da2b4: 89 86 d0 02 00 00            	mov	dword ptr [esi + 0x2d0], eax
 11da2ba: 80 be c5 02 00 00 00         	cmp	byte ptr [esi + 0x2c5], 0x0
 11da2c1: 75 73                        	jne	0x11da336 <.text+0x336>
 11da2c3: 8b 45 88                     	mov	eax, dword ptr [ebp - 0x78]
 11da2c6: 50                           	push	eax
 11da2c7: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
 11da2ca: e8 51 7c 23 ff               	call	0x411f20
 11da2cf: 8b 8e 68 03 00 00            	mov	ecx, dword ptr [esi + 0x368]
 11da2d5: 8b 96 cc 02 00 00            	mov	edx, dword ptr [esi + 0x2cc]
 11da2db: 8b 39                        	mov	edi, dword ptr [ecx]
 11da2dd: 52                           	push	edx
 11da2de: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da2e4: c7 45 fc 02 00 00 00         	mov	dword ptr [ebp - 0x4], 0x2
 11da2eb: e8 90 ed 3d ff               	call	0x5b9080
 11da2f0: 8b 8e 68 03 00 00            	mov	ecx, dword ptr [esi + 0x368]
 11da2f6: 8b 57 04                     	mov	edx, dword ptr [edi + 0x4]
 11da2f9: 50                           	push	eax
 11da2fa: 8d 45 90                     	lea	eax, [ebp - 0x70]
 11da2fd: 50                           	push	eax
 11da2fe: ff d2                        	call	edx
 11da300: 83 7d a4 00                  	cmp	dword ptr [ebp - 0x5c], 0x0
 11da304: 74 21                        	je	0x11da327 <.text+0x327>
 11da306: 8b 86 cc 02 00 00            	mov	eax, dword ptr [esi + 0x2cc]
 11da30c: ff 86 c8 02 00 00            	inc	dword ptr [esi + 0x2c8]
 11da312: 03 c3                        	add	eax, ebx
 11da314: 89 86 3c 03 00 00            	mov	dword ptr [esi + 0x33c], eax
 11da31a: 89 86 d0 02 00 00            	mov	dword ptr [esi + 0x2d0], eax
 11da320: c6 86 c5 02 00 00 01         	mov	byte ptr [esi + 0x2c5], 0x1
 11da327: 8d 4d 90                     	lea	ecx, [ebp - 0x70]
 11da32a: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11da331: e8 ba e2 27 ff               	call	0x4585f0
 11da336: 8b 4d 88                     	mov	ecx, dword ptr [ebp - 0x78]
 11da339: 51                           	push	ecx
 11da33a: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 11da33d: e8 de 7b 23 ff               	call	0x411f20
 11da342: 8b 86 cc 02 00 00            	mov	eax, dword ptr [esi + 0x2cc]
 11da348: 8b 96 68 03 00 00            	mov	edx, dword ptr [esi + 0x368]
 11da34e: 8b 3a                        	mov	edi, dword ptr [edx]
 11da350: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da356: 50                           	push	eax
 11da357: c7 45 fc 03 00 00 00         	mov	dword ptr [ebp - 0x4], 0x3
 11da35e: e8 1d ed 3d ff               	call	0x5b9080
 11da363: 8b 57 04                     	mov	edx, dword ptr [edi + 0x4]
 11da366: 50                           	push	eax
 11da367: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 11da36a: 51                           	push	ecx
 11da36b: 8b 8e 68 03 00 00            	mov	ecx, dword ptr [esi + 0x368]
 11da371: ff d2                        	call	edx
 11da373: 83 7d c4 00                  	cmp	dword ptr [ebp - 0x3c], 0x0
 11da377: 74 20                        	je	0x11da399 <.text+0x399>
 11da379: 83 7d c8 08                  	cmp	dword ptr [ebp - 0x38], 0x8
 11da37d: 8b 45 b4                     	mov	eax, dword ptr [ebp - 0x4c]
 11da380: 73 03                        	jae	0x11da385 <.text+0x385>
 11da382: 8d 45 b4                     	lea	eax, [ebp - 0x4c]
 11da385: 8b 16                        	mov	edx, dword ptr [esi]
 11da387: 8b 92 ac 00 00 00            	mov	edx, dword ptr [edx + 0xac]
 11da38d: 50                           	push	eax
 11da38e: 8b 86 cc 02 00 00            	mov	eax, dword ptr [esi + 0x2cc]
 11da394: 50                           	push	eax
 11da395: 8b ce                        	mov	ecx, esi
 11da397: ff d2                        	call	edx
 11da399: e8 12 af 00 00               	call	0x11e52b0 <.text+0xb2b0>
 11da39e: 8b 86 3c 03 00 00            	mov	eax, dword ptr [esi + 0x33c]
 11da3a4: 50                           	push	eax
 11da3a5: 8b ce                        	mov	ecx, esi
 11da3a7: e8 94 e5 ff ff               	call	0x11d8940
 11da3ac: 8b ce                        	mov	ecx, esi
 11da3ae: 89 86 30 03 00 00            	mov	dword ptr [esi + 0x330], eax
 11da3b4: e8 67 40 fe ff               	call	0x11be420
 11da3b9: 8b 8e bc 02 00 00            	mov	ecx, dword ptr [esi + 0x2bc]
 11da3bf: 8b d8                        	mov	ebx, eax
 11da3c1: 8b 3b                        	mov	edi, dword ptr [ebx]
 11da3c3: 51                           	push	ecx
 11da3c4: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da3ca: e8 b1 ec 3d ff               	call	0x5b9080
 11da3cf: 8b 57 3c                     	mov	edx, dword ptr [edi + 0x3c]
 11da3d2: 50                           	push	eax
 11da3d3: 8b cb                        	mov	ecx, ebx
 11da3d5: ff d2                        	call	edx
 11da3d7: 8b 8e 58 03 00 00            	mov	ecx, dword ptr [esi + 0x358]
 11da3dd: 89 86 5c 03 00 00            	mov	dword ptr [esi + 0x35c], eax
 11da3e3: 8b 86 30 03 00 00            	mov	eax, dword ptr [esi + 0x330]
 11da3e9: 3b c1                        	cmp	eax, ecx
 11da3eb: 72 0c                        	jb	0x11da3f9 <.text+0x3f9>
 11da3ed: 8b 96 54 03 00 00            	mov	edx, dword ptr [esi + 0x354]
 11da3f3: 03 d1                        	add	edx, ecx
 11da3f5: 3b c2                        	cmp	eax, edx
 11da3f7: 72 31                        	jb	0x11da42a <.text+0x42a>
 11da3f9: 2b 86 54 03 00 00            	sub	eax, dword ptr [esi + 0x354]
 11da3ff: 78 09                        	js	0x11da40a <.text+0x40a>
 11da401: 40                           	inc	eax
 11da402: 89 86 58 03 00 00            	mov	dword ptr [esi + 0x358], eax
 11da408: eb 0a                        	jmp	0x11da414 <.text+0x414>
 11da40a: c7 86 58 03 00 00 00 00 00 00	mov	dword ptr [esi + 0x358], 0x0
 11da414: 8b 8e 60 03 00 00            	mov	ecx, dword ptr [esi + 0x360]
 11da41a: 85 c9                        	test	ecx, ecx
 11da41c: 74 0c                        	je	0x11da42a <.text+0x42a>
 11da41e: 8b 86 58 03 00 00            	mov	eax, dword ptr [esi + 0x358]
 11da424: 50                           	push	eax
 11da425: e8 96 d4 fe ff               	call	0x11c78c0
 11da42a: 8d 4d b0                     	lea	ecx, [ebp - 0x50]
 11da42d: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 11da434: e8 b7 e1 27 ff               	call	0x4585f0
 11da439: 8b ce                        	mov	ecx, esi
 11da43b: e8 90 f8 ff ff               	call	0x11d9cd0
 11da440: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da446: e8 55 6c 00 00               	call	0x11e10a0 <.text+0x70a0>
 11da44b: 84 c0                        	test	al, al
 11da44d: 75 1a                        	jne	0x11da469 <.text+0x469>
 11da44f: 8d 8e 08 03 00 00            	lea	ecx, [esi + 0x308]
 11da455: e8 46 6c 00 00               	call	0x11e10a0 <.text+0x70a0>
 11da45a: 84 c0                        	test	al, al
 11da45c: 75 0b                        	jne	0x11da469 <.text+0x469>
 11da45e: 8d 8e 08 03 00 00            	lea	ecx, [esi + 0x308]
 11da464: e8 07 6e 00 00               	call	0x11e1270 <.text+0x7270>
 11da469: 83 be 60 03 00 00 00         	cmp	dword ptr [esi + 0x360], 0x0
 11da470: 0f 84 e3 00 00 00            	je	0x11da559 <.text+0x559>
 11da476: 80 7d 8f 00                  	cmp	byte ptr [ebp - 0x71], 0x0
 11da47a: 0f 84 c8 00 00 00            	je	0x11da548 <.text+0x548>
 11da480: 8b 8e c8 02 00 00            	mov	ecx, dword ptr [esi + 0x2c8]
 11da486: bb 01 00 00 00               	mov	ebx, 0x1
 11da48b: 2b cb                        	sub	ecx, ebx
 11da48d: 51                           	push	ecx
 11da48e: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da494: e8 17 6c 00 00               	call	0x11e10b0 <.text+0x70b0>
 11da499: 66 83 f8 0a                  	cmp	ax, 0xa
 11da49d: 74 26                        	je	0x11da4c5 <.text+0x4c5>
 11da49f: 68 e0 56 56 01               	push	0x15656e0
 11da4a4: e8 47 5a fc ff               	call	0x119fef0
 11da4a9: 8b 96 c8 02 00 00            	mov	edx, dword ptr [esi + 0x2c8]
 11da4af: 83 c4 04                     	add	esp, 0x4
 11da4b2: 50                           	push	eax
 11da4b3: 52                           	push	edx
 11da4b4: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da4ba: e8 b1 68 00 00               	call	0x11e0d70 <.text+0x6d70>
 11da4bf: 01 9e c8 02 00 00            	add	dword ptr [esi + 0x2c8], ebx
 11da4c5: 01 9e 30 03 00 00            	add	dword ptr [esi + 0x330], ebx
 11da4cb: 8b 86 30 03 00 00            	mov	eax, dword ptr [esi + 0x330]
 11da4d1: 2b 86 54 03 00 00            	sub	eax, dword ptr [esi + 0x354]
 11da4d7: 78 09                        	js	0x11da4e2 <.text+0x4e2>
 11da4d9: 40                           	inc	eax
 11da4da: 89 86 58 03 00 00            	mov	dword ptr [esi + 0x358], eax
 11da4e0: eb 0a                        	jmp	0x11da4ec <.text+0x4ec>
 11da4e2: c7 86 58 03 00 00 00 00 00 00	mov	dword ptr [esi + 0x358], 0x0
 11da4ec: 8b ce                        	mov	ecx, esi
 11da4ee: e8 2d 3f fe ff               	call	0x11be420
 11da4f3: 8b d8                        	mov	ebx, eax
 11da4f5: 8b 86 bc 02 00 00            	mov	eax, dword ptr [esi + 0x2bc]
 11da4fb: 8b 3b                        	mov	edi, dword ptr [ebx]
 11da4fd: 50                           	push	eax
 11da4fe: 8d 8e f4 02 00 00            	lea	ecx, [esi + 0x2f4]
 11da504: e8 77 eb 3d ff               	call	0x5b9080
 11da509: 8b 57 3c                     	mov	edx, dword ptr [edi + 0x3c]
 11da50c: 50                           	push	eax
 11da50d: 8b cb                        	mov	ecx, ebx
 11da50f: ff d2                        	call	edx
 11da511: 8b 8e 60 03 00 00            	mov	ecx, dword ptr [esi + 0x360]
 11da517: 89 86 5c 03 00 00            	mov	dword ptr [esi + 0x35c], eax
 11da51d: 2b 86 54 03 00 00            	sub	eax, dword ptr [esi + 0x354]
 11da523: 8b 11                        	mov	edx, dword ptr [ecx]
 11da525: 85 c0                        	test	eax, eax
 11da527: 7e 03                        	jle	0x11da52c <.text+0x52c>
 11da529: 50                           	push	eax
 11da52a: eb 02                        	jmp	0x11da52e <.text+0x52e>
 11da52c: 6a 00                        	push	0x0
 11da52e: 8b 82 9c 00 00 00            	mov	eax, dword ptr [edx + 0x9c]
 11da534: ff d0                        	call	eax
 11da536: 8b 8e 58 03 00 00            	mov	ecx, dword ptr [esi + 0x358]
 11da53c: 51                           	push	ecx
 11da53d: 8b 8e 60 03 00 00            	mov	ecx, dword ptr [esi + 0x360]
 11da543: e8 78 d3 fe ff               	call	0x11c78c0
 11da548: 8b 8e 60 03 00 00            	mov	ecx, dword ptr [esi + 0x360]
 11da54e: e8 7d d3 fe ff               	call	0x11c78d0
 11da553: 89 86 58 03 00 00            	mov	dword ptr [esi + 0x358], eax
 11da559: 8b 16                        	mov	edx, dword ptr [esi]
 11da55b: 8b 42 28                     	mov	eax, dword ptr [edx + 0x28]
 11da55e: 8b ce                        	mov	ecx, esi
 11da560: ff d0                        	call	eax
 11da562: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 11da565: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 11da56c: 59                           	pop	ecx
 11da56d: 5f                           	pop	edi
 11da56e: 5e                           	pop	esi
 11da56f: 5b                           	pop	ebx
 11da570: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 11da573: 33 cd                        	xor	ecx, ebp
 11da575: e8 5e cc 1f 00               	call	0x13d71d8 <.text+0x1fd1d8>
 11da57a: 8b e5                        	mov	esp, ebp
 11da57c: 5d                           	pop	ebp
 11da57d: c3                           	ret
 11da57e: cc                           	int3
 11da57f: cc                           	int3
 11da580: 55                           	push	ebp
 11da581: 8b ec                        	mov	ebp, esp
 11da583: 83 ec 34                     	sub	esp, 0x34
 11da586: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11da58b: 33 c5                        	xor	eax, ebp
 11da58d: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11da590: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11da593: 56                           	push	esi
 11da594: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
 11da597: e8 e4 90 fd ff               	call	0x11b3680
 11da59c: 0f bf 08                     	movsx	ecx, word ptr [eax]
 11da59f: 0f 57 c0                     	xorps	xmm0, xmm0
 11da5a2: 89 4d e4                     	mov	dword ptr [ebp - 0x1c], ecx
 11da5a5: 0f bf 50 02                  	movsx	edx, word ptr [eax + 0x2]
 11da5a9: 89 55 e8                     	mov	dword ptr [ebp - 0x18], edx
 11da5ac: 0f bf 10                     	movsx	edx, word ptr [eax]
 11da5af: 0f bf 48 04                  	movsx	ecx, word ptr [eax + 0x4]
 11da5b3: 2b ca                        	sub	ecx, edx
 11da5b5: 89 4d ec                     	mov	dword ptr [ebp - 0x14], ecx
 11da5b8: 0f bf 50 02                  	movsx	edx, word ptr [eax + 0x2]
 11da5bc: 0f bf 48 06                  	movsx	ecx, word ptr [eax + 0x6]
 11da5c0: 8b 06                        	mov	eax, dword ptr [esi]
 11da5c2: 2b ca                        	sub	ecx, edx
 11da5c4: 8b 90 c0 00 00 00            	mov	edx, dword ptr [eax + 0xc0]
 11da5ca: 89 4d f0                     	mov	dword ptr [ebp - 0x10], ecx
 11da5cd: 8d 4d cc                     	lea	ecx, [ebp - 0x34]
 11da5d0: 51                           	push	ecx
 11da5d1: f3 0f 11 45 f4               	movss	dword ptr [ebp - 0xc], xmm0
 11da5d6: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11da5de: 56                           	push	esi
 11da5df: f3 0f 11 45 f8               	movss	dword ptr [ebp - 0x8], xmm0
 11da5e4: ff d2                        	call	edx
 11da5e6: b8 18 00 00 00               	mov	eax, 0x18
 11da5eb: 33 c9                        	xor	ecx, ecx
 11da5ed: 8d 49 00                     	lea	ecx, [ecx]
 11da5f0: 8b 54 0d cc                  	mov	edx, dword ptr [ebp + ecx - 0x34]
 11da5f4: 3b 54 0d e4                  	cmp	edx, dword ptr [ebp + ecx - 0x1c]
 11da5f8: 75 1a                        	jne	0x11da614 <.text+0x614>
 11da5fa: 83 e8 04                     	sub	eax, 0x4
 11da5fd: 83 c1 04                     	add	ecx, 0x4
 11da600: 83 f8 04                     	cmp	eax, 0x4
 11da603: 73 eb                        	jae	0x11da5f0 <.text+0x5f0>
 11da605: 5e                           	pop	esi
 11da606: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da609: 33 cd                        	xor	ecx, ebp
 11da60b: e8 c8 cb 1f 00               	call	0x13d71d8 <.text+0x1fd1d8>
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
 11da629: e8 aa cb 1f 00               	call	0x13d71d8 <.text+0x1fd1d8>
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
 11da676: 0f 88 8e 00 00 00            	js	0x11da70a <.text+0x70a>
 11da67c: 8b ce                        	mov	ecx, esi
 11da67e: e8 fd e9 3d ff               	call	0x5b9080
 11da683: 83 f8 08                     	cmp	eax, 0x8
 11da686: 74 24                        	je	0x11da6ac <.text+0x6ac>
 11da688: 8b ce                        	mov	ecx, esi
 11da68a: e8 f1 e9 3d ff               	call	0x5b9080
 11da68f: 83 f8 10                     	cmp	eax, 0x10
 11da692: 74 18                        	je	0x11da6ac <.text+0x6ac>
 11da694: 8b ce                        	mov	ecx, esi
 11da696: e8 e5 e9 3d ff               	call	0x5b9080
 11da69b: 83 f8 0e                     	cmp	eax, 0xe
 11da69e: 74 0c                        	je	0x11da6ac <.text+0x6ac>
 11da6a0: 8b ce                        	mov	ecx, esi
 11da6a2: e8 d9 e9 3d ff               	call	0x5b9080
 11da6a7: 83 f8 0f                     	cmp	eax, 0xf
 11da6aa: 75 59                        	jne	0x11da705 <.text+0x705>
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
 11da73b: 74 17                        	je	0x11da754 <.text+0x754>
 11da73d: 5f                           	pop	edi
 11da73e: b8 02 00 00 80               	mov	eax, 0x80000002
 11da743: 5e                           	pop	esi
 11da744: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da747: 33 cd                        	xor	ecx, ebp
 11da749: e8 8a ca 1f 00               	call	0x13d71d8 <.text+0x1fd1d8>
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
 11da7ce: 75 58                        	jne	0x11da828 <.text+0x828>
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
 11da7e9: 78 24                        	js	0x11da80f <.text+0x80f>
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
 11da809: 79 1d                        	jns	0x11da828 <.text+0x828>
 11da80b: 8b 16                        	mov	edx, dword ptr [esi]
 11da80d: 8b ce                        	mov	ecx, esi
 11da80f: 8b 42 14                     	mov	eax, dword ptr [edx + 0x14]
 11da812: ff d0                        	call	eax
 11da814: 8b c7                        	mov	eax, edi
 11da816: 5f                           	pop	edi
 11da817: 5e                           	pop	esi
 11da818: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da81b: 33 cd                        	xor	ecx, ebp
 11da81d: e8 b6 c9 1f 00               	call	0x13d71d8 <.text+0x1fd1d8>
 11da822: 8b e5                        	mov	esp, ebp
 11da824: 5d                           	pop	ebp
 11da825: c2 04 00                     	ret	0x4
 11da828: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11da82b: 5f                           	pop	edi
 11da82c: 33 cd                        	xor	ecx, ebp
 11da82e: b8 01 00 00 00               	mov	eax, 0x1
 11da833: 5e                           	pop	esi
 11da834: e8 9f c9 1f 00               	call	0x13d71d8 <.text+0x1fd1d8>
 11da839: 8b e5                        	mov	esp, ebp
 11da83b: 5d                           	pop	ebp
 11da83c: c2 04 00                     	ret	0x4
 11da83f: cc                           	int3
 11da840: 56                           	push	esi
 11da841: 8b f1                        	mov	esi, ecx
 11da843: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11da847: 74 64                        	je	0x11da8ad <.text+0x8ad>
 11da849: e8 52 90 fd ff               	call	0x11b38a0
 11da84e: 85 c0                        	test	eax, eax
 11da850: 75 5b                        	jne	0x11da8ad <.text+0x8ad>
 11da852: 8b 46 60                     	mov	eax, dword ptr [esi + 0x60]
 11da855: 85 c0                        	test	eax, eax
 11da857: 74 08                        	je	0x11da861 <.text+0x861>
 11da859: 8b 08                        	mov	ecx, dword ptr [eax]
 11da85b: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
 11da85e: 50                           	push	eax
 11da85f: ff d2                        	call	edx
 11da861: 8b 46 5c                     	mov	eax, dword ptr [esi + 0x5c]
 11da864: c7 46 60 00 00 00 00         	mov	dword ptr [esi + 0x60], 0x0
 11da86b: 85 c0                        	test	eax, eax
 11da86d: 74 3a                        	je	0x11da8a9 <.text+0x8a9>
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
