
<stdin>:	file format elf32-i386

Disassembly of section .text:

0057c900 <.text>:
  57c900: 80 10 00                     	adc	byte ptr [eax], 0x0
  57c903: 8d 55 e4                     	lea	edx, [ebp - 0x1c]
  57c906: 52                           	push	edx
  57c907: 8b ce                        	mov	ecx, esi
  57c909: e8 02 fb ff ff               	call	0x57c410
  57c90e: 8b 7d 18                     	mov	edi, dword ptr [ebp + 0x18]
  57c911: 8b 5d 0c                     	mov	ebx, dword ptr [ebp + 0xc]
  57c914: eb ba                        	jmp	0x57c8d0
  57c916: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  57c919: c7 00 00 00 00 00            	mov	dword ptr [eax], 0x0
  57c91f: c7 40 04 00 00 00 00         	mov	dword ptr [eax + 0x4], 0x0
  57c926: 89 48 08                     	mov	dword ptr [eax + 0x8], ecx
  57c929: 85 f6                        	test	esi, esi
  57c92b: 74 04                        	je	0x57c931 <.text+0x31>
  57c92d: 8b 0e                        	mov	ecx, dword ptr [esi]
  57c92f: 89 08                        	mov	dword ptr [eax], ecx
  57c931: 5f                           	pop	edi
  57c932: 5e                           	pop	esi
  57c933: 5b                           	pop	ebx
  57c934: 8b e5                        	mov	esp, ebp
  57c936: 5d                           	pop	ebp
  57c937: c2 1c 00                     	ret	0x1c
  57c93a: cc                           	int3
  57c93b: cc                           	int3
  57c93c: cc                           	int3
  57c93d: cc                           	int3
  57c93e: cc                           	int3
  57c93f: cc                           	int3
  57c940: 55                           	push	ebp
  57c941: 8b ec                        	mov	ebp, esp
  57c943: 53                           	push	ebx
  57c944: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
  57c947: 8b 43 08                     	mov	eax, dword ptr [ebx + 0x8]
  57c94a: 8b 40 04                     	mov	eax, dword ptr [eax + 0x4]
  57c94d: 56                           	push	esi
  57c94e: 57                           	push	edi
  57c94f: 8b f1                        	mov	esi, ecx
  57c951: 8b 7e 08                     	mov	edi, dword ptr [esi + 0x8]
  57c954: 57                           	push	edi
  57c955: 50                           	push	eax
  57c956: e8 85 fd ff ff               	call	0x57c6e0
  57c95b: 89 47 04                     	mov	dword ptr [edi + 0x4], eax
  57c95e: 8b 4b 0c                     	mov	ecx, dword ptr [ebx + 0xc]
  57c961: 8b 56 08                     	mov	edx, dword ptr [esi + 0x8]
  57c964: 89 4e 0c                     	mov	dword ptr [esi + 0xc], ecx
  57c967: 8b 42 04                     	mov	eax, dword ptr [edx + 0x4]
  57c96a: 80 78 25 00                  	cmp	byte ptr [eax + 0x25], 0x0
  57c96e: 75 38                        	jne	0x57c9a8 <.text+0xa8>
  57c970: 8b 08                        	mov	ecx, dword ptr [eax]
  57c972: 80 79 25 00                  	cmp	byte ptr [ecx + 0x25], 0x0
  57c976: 75 0a                        	jne	0x57c982 <.text+0x82>
  57c978: 8b c1                        	mov	eax, ecx
  57c97a: 8b 08                        	mov	ecx, dword ptr [eax]
  57c97c: 80 79 25 00                  	cmp	byte ptr [ecx + 0x25], 0x0
  57c980: 74 f6                        	je	0x57c978 <.text+0x78>
  57c982: 89 02                        	mov	dword ptr [edx], eax
  57c984: 8b 76 08                     	mov	esi, dword ptr [esi + 0x8]
  57c987: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
  57c98a: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  57c98d: 80 78 25 00                  	cmp	byte ptr [eax + 0x25], 0x0
  57c991: 75 0b                        	jne	0x57c99e <.text+0x9e>
  57c993: 8b c8                        	mov	ecx, eax
  57c995: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  57c998: 80 78 25 00                  	cmp	byte ptr [eax + 0x25], 0x0
  57c99c: 74 f5                        	je	0x57c993 <.text+0x93>
  57c99e: 5f                           	pop	edi
  57c99f: 89 4e 08                     	mov	dword ptr [esi + 0x8], ecx
  57c9a2: 5e                           	pop	esi
  57c9a3: 5b                           	pop	ebx
  57c9a4: 5d                           	pop	ebp
  57c9a5: c2 04 00                     	ret	0x4
  57c9a8: 89 12                        	mov	dword ptr [edx], edx
  57c9aa: 8b 76 08                     	mov	esi, dword ptr [esi + 0x8]
  57c9ad: 5f                           	pop	edi
  57c9ae: 89 76 08                     	mov	dword ptr [esi + 0x8], esi
  57c9b1: 5e                           	pop	esi
  57c9b2: 5b                           	pop	ebx
  57c9b3: 5d                           	pop	ebp
  57c9b4: c2 04 00                     	ret	0x4
  57c9b7: cc                           	int3
  57c9b8: cc                           	int3
  57c9b9: cc                           	int3
  57c9ba: cc                           	int3
  57c9bb: cc                           	int3
  57c9bc: cc                           	int3
  57c9bd: cc                           	int3
  57c9be: cc                           	int3
  57c9bf: cc                           	int3
  57c9c0: 55                           	push	ebp
  57c9c1: 8b ec                        	mov	ebp, esp
  57c9c3: 83 ec 24                     	sub	esp, 0x24
  57c9c6: 53                           	push	ebx
  57c9c7: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
  57c9ca: 56                           	push	esi
  57c9cb: 8b f1                        	mov	esi, ecx
  57c9cd: 3b f3                        	cmp	esi, ebx
  57c9cf: 74 7d                        	je	0x57ca4e <.text+0x14e>
  57c9d1: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  57c9d4: 50                           	push	eax
  57c9d5: e8 66 79 24 00               	call	0x7c4340 <.text+0x247a40>
  57c9da: 83 ec 0c                     	sub	esp, 0xc
  57c9dd: 8b cc                        	mov	ecx, esp
  57c9df: c7 01 00 00 00 00            	mov	dword ptr [ecx], 0x0
  57c9e5: c7 41 04 00 00 00 00         	mov	dword ptr [ecx + 0x4], 0x0
  57c9ec: 8b 10                        	mov	edx, dword ptr [eax]
  57c9ee: 89 65 08                     	mov	dword ptr [ebp + 0x8], esp
  57c9f1: 85 d2                        	test	edx, edx
  57c9f3: 74 0a                        	je	0x57c9ff <.text+0xff>
  57c9f5: 8b 12                        	mov	edx, dword ptr [edx]
  57c9f7: 85 d2                        	test	edx, edx
  57c9f9: 74 04                        	je	0x57c9ff <.text+0xff>
  57c9fb: 8b 12                        	mov	edx, dword ptr [edx]
  57c9fd: 89 11                        	mov	dword ptr [ecx], edx
  57c9ff: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  57ca02: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  57ca05: 8d 4d e8                     	lea	ecx, [ebp - 0x18]
  57ca08: 51                           	push	ecx
  57ca09: 8b ce                        	mov	ecx, esi
  57ca0b: e8 40 34 fe ff               	call	0x55fe50
  57ca10: 83 ec 0c                     	sub	esp, 0xc
  57ca13: 8b cc                        	mov	ecx, esp
  57ca15: c7 01 00 00 00 00            	mov	dword ptr [ecx], 0x0
  57ca1b: c7 41 04 00 00 00 00         	mov	dword ptr [ecx + 0x4], 0x0
  57ca22: 8b 10                        	mov	edx, dword ptr [eax]
  57ca24: 89 65 08                     	mov	dword ptr [ebp + 0x8], esp
  57ca27: 85 d2                        	test	edx, edx
  57ca29: 74 0a                        	je	0x57ca35 <.text+0x135>
  57ca2b: 8b 12                        	mov	edx, dword ptr [edx]
  57ca2d: 85 d2                        	test	edx, edx
  57ca2f: 74 04                        	je	0x57ca35 <.text+0x135>
  57ca31: 8b 12                        	mov	edx, dword ptr [edx]
  57ca33: 89 11                        	mov	dword ptr [ecx], edx
  57ca35: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  57ca38: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  57ca3b: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
  57ca3e: 51                           	push	ecx
  57ca3f: 8b ce                        	mov	ecx, esi
  57ca41: e8 da fd ff ff               	call	0x57c820
  57ca46: 53                           	push	ebx
  57ca47: 8b ce                        	mov	ecx, esi
  57ca49: e8 f2 fe ff ff               	call	0x57c940 <.text+0x40>
  57ca4e: 8b c6                        	mov	eax, esi
  57ca50: 5e                           	pop	esi
  57ca51: 5b                           	pop	ebx
  57ca52: 8b e5                        	mov	esp, ebp
  57ca54: 5d                           	pop	ebp
  57ca55: c2 04 00                     	ret	0x4
  57ca58: cc                           	int3
  57ca59: cc                           	int3
  57ca5a: cc                           	int3
  57ca5b: cc                           	int3
  57ca5c: cc                           	int3
  57ca5d: cc                           	int3
  57ca5e: cc                           	int3
  57ca5f: cc                           	int3
  57ca60: 55                           	push	ebp
  57ca61: 8b ec                        	mov	ebp, esp
  57ca63: 83 ec 28                     	sub	esp, 0x28
  57ca66: 56                           	push	esi
  57ca67: 8d 45 f0                     	lea	eax, [ebp - 0x10]
  57ca6a: 50                           	push	eax
  57ca6b: 8b f1                        	mov	esi, ecx
  57ca6d: e8 ce 78 24 00               	call	0x7c4340 <.text+0x247a40>
  57ca72: 83 ec 0c                     	sub	esp, 0xc
  57ca75: 8b cc                        	mov	ecx, esp
  57ca77: c7 01 00 00 00 00            	mov	dword ptr [ecx], 0x0
  57ca7d: c7 41 04 00 00 00 00         	mov	dword ptr [ecx + 0x4], 0x0
  57ca84: 8b 10                        	mov	edx, dword ptr [eax]
  57ca86: 89 65 fc                     	mov	dword ptr [ebp - 0x4], esp
  57ca89: 85 d2                        	test	edx, edx
  57ca8b: 74 0a                        	je	0x57ca97 <.text+0x197>
  57ca8d: 8b 12                        	mov	edx, dword ptr [edx]
  57ca8f: 85 d2                        	test	edx, edx
  57ca91: 74 04                        	je	0x57ca97 <.text+0x197>
  57ca93: 8b 12                        	mov	edx, dword ptr [edx]
  57ca95: 89 11                        	mov	dword ptr [ecx], edx
  57ca97: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  57ca9a: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  57ca9d: 8d 4d e4                     	lea	ecx, [ebp - 0x1c]
  57caa0: 51                           	push	ecx
  57caa1: 8b ce                        	mov	ecx, esi
  57caa3: e8 a8 33 fe ff               	call	0x55fe50
  57caa8: 83 ec 0c                     	sub	esp, 0xc
  57caab: 8b cc                        	mov	ecx, esp
  57caad: c7 01 00 00 00 00            	mov	dword ptr [ecx], 0x0
  57cab3: c7 41 04 00 00 00 00         	mov	dword ptr [ecx + 0x4], 0x0
  57caba: 8b 10                        	mov	edx, dword ptr [eax]
  57cabc: 89 65 fc                     	mov	dword ptr [ebp - 0x4], esp
  57cabf: 85 d2                        	test	edx, edx
  57cac1: 74 0a                        	je	0x57cacd <.text+0x1cd>
  57cac3: 8b 12                        	mov	edx, dword ptr [edx]
  57cac5: 85 d2                        	test	edx, edx
  57cac7: 74 04                        	je	0x57cacd <.text+0x1cd>
  57cac9: 8b 12                        	mov	edx, dword ptr [edx]
  57cacb: 89 11                        	mov	dword ptr [ecx], edx
  57cacd: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  57cad0: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  57cad3: 8d 4d d8                     	lea	ecx, [ebp - 0x28]
  57cad6: 51                           	push	ecx
  57cad7: 8b ce                        	mov	ecx, esi
  57cad9: e8 42 fd ff ff               	call	0x57c820
  57cade: 5e                           	pop	esi
  57cadf: 8b e5                        	mov	esp, ebp
  57cae1: 5d                           	pop	ebp
  57cae2: c3                           	ret
  57cae3: cc                           	int3
  57cae4: cc                           	int3
  57cae5: cc                           	int3
  57cae6: cc                           	int3
  57cae7: cc                           	int3
  57cae8: cc                           	int3
  57cae9: cc                           	int3
  57caea: cc                           	int3
  57caeb: cc                           	int3
  57caec: cc                           	int3
  57caed: cc                           	int3
  57caee: cc                           	int3
  57caef: cc                           	int3
  57caf0: 55                           	push	ebp
  57caf1: 8b ec                        	mov	ebp, esp
  57caf3: 6a ff                        	push	-0x1
  57caf5: 68 09 d5 41 01               	push	0x141d509
  57cafa: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  57cb00: 50                           	push	eax
  57cb01: 83 ec 28                     	sub	esp, 0x28
  57cb04: 56                           	push	esi
  57cb05: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  57cb0a: 33 c5                        	xor	eax, ebp
  57cb0c: 50                           	push	eax
  57cb0d: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  57cb10: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  57cb16: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
  57cb19: 50                           	push	eax
  57cb1a: 8d 4d cc                     	lea	ecx, [ebp - 0x34]
  57cb1d: c7 45 ec 00 00 00 00         	mov	dword ptr [ebp - 0x14], 0x0
  57cb24: e8 37 f3 ff ff               	call	0x57be60
  57cb29: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  57cb2c: c7 45 fc 01 00 00 00         	mov	dword ptr [ebp - 0x4], 0x1
  57cb33: e8 38 59 c2 00               	call	0x11a2470 <.text+0xc25b70>
  57cb38: 8d 4d 0c                     	lea	ecx, [ebp + 0xc]
  57cb3b: 51                           	push	ecx
  57cb3c: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
  57cb3f: 8d 51 08                     	lea	edx, [ecx + 0x8]
  57cb42: 52                           	push	edx
  57cb43: c6 45 fc 02                  	mov	byte ptr [ebp - 0x4], 0x2
  57cb47: e8 94 42 c2 00               	call	0x11a0de0 <.text+0xc244e0>
  57cb4c: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  57cb4f: 8d 4d e8                     	lea	ecx, [ebp - 0x18]
  57cb52: 51                           	push	ecx
  57cb53: 8d 55 f0                     	lea	edx, [ebp - 0x10]
  57cb56: 52                           	push	edx
  57cb57: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  57cb5a: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  57cb5d: e8 ce 3d c2 00               	call	0x11a0930 <.text+0xc24030>
  57cb62: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
  57cb65: 8b ce                        	mov	ecx, esi
  57cb67: c6 45 fc 03                  	mov	byte ptr [ebp - 0x4], 0x3
  57cb6b: e8 00 59 c2 00               	call	0x11a2470 <.text+0xc25b70>
  57cb70: 8d 45 0c                     	lea	eax, [ebp + 0xc]
  57cb73: 50                           	push	eax
  57cb74: 8d 4d e8                     	lea	ecx, [ebp - 0x18]
  57cb77: 51                           	push	ecx
  57cb78: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  57cb7b: c6 45 fc 04                  	mov	byte ptr [ebp - 0x4], 0x4
  57cb7f: e8 5c 42 c2 00               	call	0x11a0de0 <.text+0xc244e0>
  57cb84: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
  57cb87: 8d 46 08                     	lea	eax, [esi + 0x8]
  57cb8a: 50                           	push	eax
  57cb8b: 8d 4d f0                     	lea	ecx, [ebp - 0x10]
  57cb8e: 51                           	push	ecx
  57cb8f: 8b ce                        	mov	ecx, esi
  57cb91: 89 55 f0                     	mov	dword ptr [ebp - 0x10], edx
  57cb94: e8 97 3d c2 00               	call	0x11a0930 <.text+0xc24030>
  57cb99: 8d 55 cc                     	lea	edx, [ebp - 0x34]
  57cb9c: 8d 4e 0c                     	lea	ecx, [esi + 0xc]
  57cb9f: 52                           	push	edx
  57cba0: c6 45 fc 05                  	mov	byte ptr [ebp - 0x4], 0x5
  57cba4: e8 c7 f3 ff ff               	call	0x57bf70
  57cba9: 8d 4d e0                     	lea	ecx, [ebp - 0x20]
  57cbac: c7 45 ec 01 00 00 00         	mov	dword ptr [ebp - 0x14], 0x1
  57cbb3: c6 45 fc 01                  	mov	byte ptr [ebp - 0x4], 0x1
  57cbb7: e8 04 41 c2 00               	call	0x11a0cc0 <.text+0xc243c0>
  57cbbc: 8d 4d cc                     	lea	ecx, [ebp - 0x34]
  57cbbf: c7 45 fc 06 00 00 00         	mov	dword ptr [ebp - 0x4], 0x6
  57cbc6: e8 b5 f1 ff ff               	call	0x57bd80
  57cbcb: 8b 45 d4                     	mov	eax, dword ptr [ebp - 0x2c]
  57cbce: 50                           	push	eax
  57cbcf: e8 53 8f e5 00               	call	0x13d5b27 <.text+0xe59227>
  57cbd4: 8b 4d cc                     	mov	ecx, dword ptr [ebp - 0x34]
  57cbd7: 51                           	push	ecx
  57cbd8: e8 4a 8f e5 00               	call	0x13d5b27 <.text+0xe59227>
  57cbdd: 83 c4 08                     	add	esp, 0x8
  57cbe0: 8b c6                        	mov	eax, esi
  57cbe2: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  57cbe5: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  57cbec: 59                           	pop	ecx
  57cbed: 5e                           	pop	esi
  57cbee: 8b e5                        	mov	esp, ebp
  57cbf0: 5d                           	pop	ebp
  57cbf1: c3                           	ret
  57cbf2: cc                           	int3
  57cbf3: cc                           	int3
  57cbf4: cc                           	int3
  57cbf5: cc                           	int3
  57cbf6: cc                           	int3
  57cbf7: cc                           	int3
  57cbf8: cc                           	int3
  57cbf9: cc                           	int3
  57cbfa: cc                           	int3
  57cbfb: cc                           	int3
  57cbfc: cc                           	int3
  57cbfd: cc                           	int3
  57cbfe: cc                           	int3
  57cbff: cc                           	int3
