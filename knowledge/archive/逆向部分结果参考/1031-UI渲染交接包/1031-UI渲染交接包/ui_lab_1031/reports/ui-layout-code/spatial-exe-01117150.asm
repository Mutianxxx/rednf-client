
<stdin>:	file format elf32-i386

Disassembly of section .text:

01117150 <.text>:
 1117150: 84 c0                        	test	al, al
 1117152: 74 0c                        	je	0x1117160 <.text+0x10>
 1117154: e8 d7 ae 42 ff               	call	0x542030
 1117159: 8b c8                        	mov	ecx, eax
 111715b: e8 c0 a2 42 ff               	call	0x541420
 1117160: 8d 8d a0 fb ff ff            	lea	ecx, [ebp - 0x460]
 1117166: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
 111716d: e8 4e 6f 07 00               	call	0x118e0c0 <.text+0x76f70>
 1117172: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
 1117175: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
 111717c: 59                           	pop	ecx
 111717d: 5f                           	pop	edi
 111717e: 5e                           	pop	esi
 111717f: 5b                           	pop	ebx
 1117180: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
 1117183: 33 cd                        	xor	ecx, ebp
 1117185: e8 4e 00 2c 00               	call	0x13d71d8 <.text+0x2c0088>
 111718a: 8b e5                        	mov	esp, ebp
 111718c: 5d                           	pop	ebp
 111718d: c3                           	ret
 111718e: cc                           	int3
 111718f: cc                           	int3
 1117190: 55                           	push	ebp
 1117191: 8b ec                        	mov	ebp, esp
 1117193: 56                           	push	esi
 1117194: 8d b1 98 07 00 00            	lea	esi, [ecx + 0x798]
 111719a: 6a 01                        	push	0x1
 111719c: 8b ce                        	mov	ecx, esi
 111719e: e8 8d 32 0a 00               	call	0x11ba430 <.text+0xa32e0>
 11171a3: 8b ce                        	mov	ecx, esi
 11171a5: e8 46 32 0a 00               	call	0x11ba3f0 <.text+0xa32a0>
 11171aa: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11171ad: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11171b0: f7 d8                        	neg	eax
 11171b2: 50                           	push	eax
 11171b3: 51                           	push	ecx
 11171b4: 8b ce                        	mov	ecx, esi
 11171b6: e8 55 38 0a 00               	call	0x11baa10 <.text+0xa38c0>
 11171bb: 5e                           	pop	esi
 11171bc: 5d                           	pop	ebp
 11171bd: c2 08 00                     	ret	0x8
 11171c0: 55                           	push	ebp
 11171c1: 8b ec                        	mov	ebp, esp
 11171c3: 51                           	push	ecx
 11171c4: 53                           	push	ebx
 11171c5: 56                           	push	esi
 11171c6: 8b f1                        	mov	esi, ecx
 11171c8: 33 db                        	xor	ebx, ebx
 11171ca: 38 5e 04                     	cmp	byte ptr [esi + 0x4], bl
 11171cd: 0f 84 a3 02 00 00            	je	0x1117476 <.text+0x326>
 11171d3: 8b 8e f8 00 00 00            	mov	ecx, dword ptr [esi + 0xf8]
 11171d9: 88 5e 04                     	mov	byte ptr [esi + 0x4], bl
 11171dc: 3b cb                        	cmp	ecx, ebx
 11171de: 74 08                        	je	0x11171e8 <.text+0x98>
 11171e0: 8b 01                        	mov	eax, dword ptr [ecx]
 11171e2: 8b 10                        	mov	edx, dword ptr [eax]
 11171e4: 6a 01                        	push	0x1
 11171e6: ff d2                        	call	edx
 11171e8: 8b 8e fc 00 00 00            	mov	ecx, dword ptr [esi + 0xfc]
 11171ee: 89 9e f8 00 00 00            	mov	dword ptr [esi + 0xf8], ebx
 11171f4: 3b cb                        	cmp	ecx, ebx
 11171f6: 74 08                        	je	0x1117200 <.text+0xb0>
 11171f8: 8b 01                        	mov	eax, dword ptr [ecx]
 11171fa: 8b 10                        	mov	edx, dword ptr [eax]
 11171fc: 6a 01                        	push	0x1
 11171fe: ff d2                        	call	edx
 1117200: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 1117206: 89 9e fc 00 00 00            	mov	dword ptr [esi + 0xfc], ebx
 111720c: 3b cb                        	cmp	ecx, ebx
 111720e: 74 08                        	je	0x1117218 <.text+0xc8>
 1117210: 8b 01                        	mov	eax, dword ptr [ecx]
 1117212: 8b 10                        	mov	edx, dword ptr [eax]
 1117214: 6a 01                        	push	0x1
 1117216: ff d2                        	call	edx
 1117218: 8b 8e b4 03 00 00            	mov	ecx, dword ptr [esi + 0x3b4]
 111721e: 89 9e b0 03 00 00            	mov	dword ptr [esi + 0x3b0], ebx
 1117224: 3b cb                        	cmp	ecx, ebx
 1117226: 74 08                        	je	0x1117230 <.text+0xe0>
 1117228: 8b 01                        	mov	eax, dword ptr [ecx]
 111722a: 8b 10                        	mov	edx, dword ptr [eax]
 111722c: 6a 01                        	push	0x1
 111722e: ff d2                        	call	edx
 1117230: 8b 8e ac 03 00 00            	mov	ecx, dword ptr [esi + 0x3ac]
 1117236: 89 9e b4 03 00 00            	mov	dword ptr [esi + 0x3b4], ebx
 111723c: 3b cb                        	cmp	ecx, ebx
 111723e: 74 08                        	je	0x1117248 <.text+0xf8>
 1117240: 8b 01                        	mov	eax, dword ptr [ecx]
 1117242: 8b 10                        	mov	edx, dword ptr [eax]
 1117244: 6a 01                        	push	0x1
 1117246: ff d2                        	call	edx
 1117248: 8b 8e b8 03 00 00            	mov	ecx, dword ptr [esi + 0x3b8]
 111724e: 89 9e ac 03 00 00            	mov	dword ptr [esi + 0x3ac], ebx
 1117254: 3b cb                        	cmp	ecx, ebx
 1117256: 74 08                        	je	0x1117260 <.text+0x110>
 1117258: 8b 01                        	mov	eax, dword ptr [ecx]
 111725a: 8b 10                        	mov	edx, dword ptr [eax]
 111725c: 6a 01                        	push	0x1
 111725e: ff d2                        	call	edx
 1117260: 8b 4e 08                     	mov	ecx, dword ptr [esi + 0x8]
 1117263: 89 9e b8 03 00 00            	mov	dword ptr [esi + 0x3b8], ebx
 1117269: 3b cb                        	cmp	ecx, ebx
 111726b: 74 08                        	je	0x1117275 <.text+0x125>
 111726d: 8b 01                        	mov	eax, dword ptr [ecx]
 111726f: 8b                           	<unknown>
