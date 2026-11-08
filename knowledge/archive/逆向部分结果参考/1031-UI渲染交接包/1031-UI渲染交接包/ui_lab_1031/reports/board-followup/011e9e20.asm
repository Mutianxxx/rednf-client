
<stdin>:	file format elf32-i386

Disassembly of section .text:

011e9e20 <.text>:
 11e9e20: 55                           	push	ebp
 11e9e21: 8b ec                        	mov	ebp, esp
 11e9e23: 83 ec 0c                     	sub	esp, 0xc
 11e9e26: 56                           	push	esi
 11e9e27: 8b f1                        	mov	esi, ecx
 11e9e29: 83 3e 00                     	cmp	dword ptr [esi], 0x0
 11e9e2c: 0f 84 53 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e32: 83 7e 04 00                  	cmp	dword ptr [esi + 0x4], 0x0
 11e9e36: 0f 84 49 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e3c: 83 7e 08 00                  	cmp	dword ptr [esi + 0x8], 0x0
 11e9e40: 0f 84 3f 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e46: 83 7e 0c 00                  	cmp	dword ptr [esi + 0xc], 0x0
 11e9e4a: 0f 84 35 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e50: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9e53: 85 c9                        	test	ecx, ecx
 11e9e55: 0f 84 2a 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e5b: 83 7e 14 00                  	cmp	dword ptr [esi + 0x14], 0x0
 11e9e5f: 0f 84 20 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e65: 83 7e 18 00                  	cmp	dword ptr [esi + 0x18], 0x0
 11e9e69: 0f 84 16 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e6f: 83 7e 1c 00                  	cmp	dword ptr [esi + 0x1c], 0x0
 11e9e73: 0f 84 0c 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e79: 83 7e 20 00                  	cmp	dword ptr [esi + 0x20], 0x0
 11e9e7d: 0f 84 02 03 00 00            	je	0x11ea185 <.text+0x365>
 11e9e83: e8 f8 9e fc ff               	call	0x11b3d80
 11e9e88: 85 c0                        	test	eax, eax
 11e9e8a: 0f 84 f5 02 00 00            	je	0x11ea185 <.text+0x365>
 11e9e90: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9e93: e8 f8 9e fc ff               	call	0x11b3d90
 11e9e98: 85 c0                        	test	eax, eax
 11e9e9a: 0f 84 e5 02 00 00            	je	0x11ea185 <.text+0x365>
 11e9ea0: db 45 10                     	fild	dword ptr [ebp + 0x10]
 11e9ea3: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11e9ea6: 57                           	push	edi
 11e9ea7: d9 5d 10                     	fstp	dword ptr [ebp + 0x10]
 11e9eaa: e8 d1 9e fc ff               	call	0x11b3d80
 11e9eaf: 8b 4e 0c                     	mov	ecx, dword ptr [esi + 0xc]
 11e9eb2: 8b f8                        	mov	edi, eax
 11e9eb4: e8 c7 9e fc ff               	call	0x11b3d80
 11e9eb9: 03 f8                        	add	edi, eax
 11e9ebb: 89 7d f8                     	mov	dword ptr [ebp - 0x8], edi
 11e9ebe: db 45 f8                     	fild	dword ptr [ebp - 0x8]
 11e9ec1: 79 06                        	jns	0x11e9ec9 <.text+0xa9>
 11e9ec3: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11e9ec9: d8 6d 10                     	fsubr	dword ptr [ebp + 0x10]
 11e9ecc: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9ecf: d9 5d 10                     	fstp	dword ptr [ebp + 0x10]
 11e9ed2: e8 a9 9e fc ff               	call	0x11b3d80
 11e9ed7: 89 45 f8                     	mov	dword ptr [ebp - 0x8], eax
 11e9eda: db 45 f8                     	fild	dword ptr [ebp - 0x8]
 11e9edd: 85 c0                        	test	eax, eax
 11e9edf: 79 06                        	jns	0x11e9ee7 <.text+0xc7>
 11e9ee1: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11e9ee7: d8 7d 10                     	fdivr	dword ptr [ebp + 0x10]
 11e9eea: 8b 4e 1c                     	mov	ecx, dword ptr [esi + 0x1c]
 11e9eed: d9 5d fc                     	fstp	dword ptr [ebp - 0x4]
 11e9ef0: db 45 14                     	fild	dword ptr [ebp + 0x14]
 11e9ef3: d9 5d 10                     	fstp	dword ptr [ebp + 0x10]
 11e9ef6: e8 95 9e fc ff               	call	0x11b3d90
 11e9efb: 8b 4e 04                     	mov	ecx, dword ptr [esi + 0x4]
 11e9efe: 8b f8                        	mov	edi, eax
 11e9f00: e8 8b 9e fc ff               	call	0x11b3d90
 11e9f05: 03 f8                        	add	edi, eax
 11e9f07: 89 7d 14                     	mov	dword ptr [ebp + 0x14], edi
 11e9f0a: db 45 14                     	fild	dword ptr [ebp + 0x14]
 11e9f0d: 79 06                        	jns	0x11e9f15 <.text+0xf5>
 11e9f0f: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11e9f15: d8 6d 10                     	fsubr	dword ptr [ebp + 0x10]
 11e9f18: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9f1b: d9 5d 10                     	fstp	dword ptr [ebp + 0x10]
 11e9f1e: e8 6d 9e fc ff               	call	0x11b3d90
 11e9f23: 89 45 14                     	mov	dword ptr [ebp + 0x14], eax
 11e9f26: db 45 14                     	fild	dword ptr [ebp + 0x14]
 11e9f29: 85 c0                        	test	eax, eax
 11e9f2b: 79 06                        	jns	0x11e9f33 <.text+0x113>
 11e9f2d: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11e9f33: d8 7d 10                     	fdivr	dword ptr [ebp + 0x10]
 11e9f36: d9 5d 10                     	fstp	dword ptr [ebp + 0x10]
 11e9f39: d9 45 fc                     	fld	dword ptr [ebp - 0x4]
 11e9f3c: d9 ee                        	fldz
 11e9f3e: df f1                        	fcompi	st, st(1)
 11e9f40: dd d8                        	fstp	st(0)
 11e9f42: 0f 83 3c 02 00 00            	jae	0x11ea184 <.text+0x364>
 11e9f48: 0f 57 c0                     	xorps	xmm0, xmm0
 11e9f4b: 0f 2f 45 10                  	comiss	xmm0, dword ptr [ebp + 0x10]
 11e9f4f: 0f 83 2f 02 00 00            	jae	0x11ea184 <.text+0x364>
 11e9f55: 8b 0e                        	mov	ecx, dword ptr [esi]
 11e9f57: 53                           	push	ebx
 11e9f58: e8 23 9e fc ff               	call	0x11b3d80
 11e9f5d: 8b 0e                        	mov	ecx, dword ptr [esi]
 11e9f5f: 8b f8                        	mov	edi, eax
 11e9f61: 03 7d 08                     	add	edi, dword ptr [ebp + 0x8]
 11e9f64: 89 7d 14                     	mov	dword ptr [ebp + 0x14], edi
 11e9f67: e8 24 9e fc ff               	call	0x11b3d90
 11e9f6c: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9f6f: 8b d8                        	mov	ebx, eax
 11e9f71: 03 5d 0c                     	add	ebx, dword ptr [ebp + 0xc]
 11e9f74: 89 5d f8                     	mov	dword ptr [ebp - 0x8], ebx
 11e9f77: e8 04 9e fc ff               	call	0x11b3d80
 11e9f7c: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
 11e9f7f: db 45 f4                     	fild	dword ptr [ebp - 0xc]
 11e9f82: 85 c0                        	test	eax, eax
 11e9f84: 79 06                        	jns	0x11e9f8c <.text+0x16c>
 11e9f86: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11e9f8c: d8 4d fc                     	fmul	dword ptr [ebp - 0x4]
 11e9f8f: da 45 14                     	fiadd	dword ptr [ebp + 0x14]
 11e9f92: d8 05 84 21 56 01            	fadd	dword ptr [0x1562184]
 11e9f98: e8 43 e4 1e 00               	call	0x13d83e0 <.text+0x1ee5c0>
 11e9f9d: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11e9fa0: 89 45 14                     	mov	dword ptr [ebp + 0x14], eax
 11e9fa3: e8 e8 9d fc ff               	call	0x11b3d90
 11e9fa8: 89 45 f4                     	mov	dword ptr [ebp - 0xc], eax
 11e9fab: db 45 f4                     	fild	dword ptr [ebp - 0xc]
 11e9fae: 85 c0                        	test	eax, eax
 11e9fb0: 79 06                        	jns	0x11e9fb8 <.text+0x198>
 11e9fb2: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11e9fb8: d8 4d 10                     	fmul	dword ptr [ebp + 0x10]
 11e9fbb: da 45 f8                     	fiadd	dword ptr [ebp - 0x8]
 11e9fbe: d8 05 84 21 56 01            	fadd	dword ptr [0x1562184]
 11e9fc4: e8 17 e4 1e 00               	call	0x13d83e0 <.text+0x1ee5c0>
 11e9fc9: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11e9fcc: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11e9fcf: 89 45 f8                     	mov	dword ptr [ebp - 0x8], eax
 11e9fd2: 8b 06                        	mov	eax, dword ptr [esi]
 11e9fd4: 50                           	push	eax
 11e9fd5: 51                           	push	ecx
 11e9fd6: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11e9fdc: 52                           	push	edx
 11e9fdd: e8 6e 99 fc ff               	call	0x11b3950
 11e9fe2: 0f 57 c0                     	xorps	xmm0, xmm0
 11e9fe5: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
 11e9fe8: 8b 4d 0c                     	mov	ecx, dword ptr [ebp + 0xc]
 11e9feb: 83 ec 08                     	sub	esp, 0x8
 11e9fee: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11e9ff4: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11e9ff9: 6a ff                        	push	-0x1
 11e9ffb: 83 ec 0c                     	sub	esp, 0xc
 11e9ffe: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11ea004: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11ea00c: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea012: f3 0f 10 45 fc               	movss	xmm0, dword ptr [ebp - 0x4]
 11ea017: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea01c: 50                           	push	eax
 11ea01d: 51                           	push	ecx
 11ea01e: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11ea024: 57                           	push	edi
 11ea025: e8 b6 a1 fc ff               	call	0x11b41e0
 11ea02a: 8b 56 08                     	mov	edx, dword ptr [esi + 0x8]
 11ea02d: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11ea030: 8b 4d 14                     	mov	ecx, dword ptr [ebp + 0x14]
 11ea033: 52                           	push	edx
 11ea034: 50                           	push	eax
 11ea035: 51                           	push	ecx
 11ea036: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11ea03c: e8 0f 99 fc ff               	call	0x11b3950
 11ea041: 0f 57 c0                     	xorps	xmm0, xmm0
 11ea044: 8b 56 0c                     	mov	edx, dword ptr [esi + 0xc]
 11ea047: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11ea04a: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11ea050: 83 ec 08                     	sub	esp, 0x8
 11ea053: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea059: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea05e: 6a ff                        	push	-0x1
 11ea060: 83 ec 0c                     	sub	esp, 0xc
 11ea063: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11ea069: f3 0f 10 45 10               	movss	xmm0, dword ptr [ebp + 0x10]
 11ea06e: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea074: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11ea07c: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea081: 52                           	push	edx
 11ea082: 53                           	push	ebx
 11ea083: 50                           	push	eax
 11ea084: e8 57 a1 fc ff               	call	0x11b41e0
 11ea089: 0f 57 c0                     	xorps	xmm0, xmm0
 11ea08c: 8b 4e 10                     	mov	ecx, dword ptr [esi + 0x10]
 11ea08f: 83 ec 08                     	sub	esp, 0x8
 11ea092: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea098: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea09d: 6a ff                        	push	-0x1
 11ea09f: 83 ec 0c                     	sub	esp, 0xc
 11ea0a2: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11ea0a8: f3 0f 10 45 10               	movss	xmm0, dword ptr [ebp + 0x10]
 11ea0ad: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea0b3: f3 0f 10 45 fc               	movss	xmm0, dword ptr [ebp - 0x4]
 11ea0b8: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea0bd: 51                           	push	ecx
 11ea0be: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11ea0c4: 53                           	push	ebx
 11ea0c5: 57                           	push	edi
 11ea0c6: e8 15 a1 fc ff               	call	0x11b41e0
 11ea0cb: 0f 57 c0                     	xorps	xmm0, xmm0
 11ea0ce: 83 ec 08                     	sub	esp, 0x8
 11ea0d1: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea0d7: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea0dc: 6a ff                        	push	-0x1
 11ea0de: 83 ec 0c                     	sub	esp, 0xc
 11ea0e1: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11ea0e7: f3 0f 10 45 10               	movss	xmm0, dword ptr [ebp + 0x10]
 11ea0ec: 8b 56 14                     	mov	edx, dword ptr [esi + 0x14]
 11ea0ef: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
 11ea0f2: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11ea0f8: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea0fe: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11ea106: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea10b: 52                           	push	edx
 11ea10c: 53                           	push	ebx
 11ea10d: 50                           	push	eax
 11ea10e: e8 cd a0 fc ff               	call	0x11b41e0
 11ea113: 8b 4e 18                     	mov	ecx, dword ptr [esi + 0x18]
 11ea116: 8b 5d f8                     	mov	ebx, dword ptr [ebp - 0x8]
 11ea119: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11ea11c: 51                           	push	ecx
 11ea11d: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11ea123: 53                           	push	ebx
 11ea124: 52                           	push	edx
 11ea125: e8 26 98 fc ff               	call	0x11b3950
 11ea12a: 0f 57 c0                     	xorps	xmm0, xmm0
 11ea12d: 8b 46 1c                     	mov	eax, dword ptr [esi + 0x1c]
 11ea130: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11ea136: 83 ec 08                     	sub	esp, 0x8
 11ea139: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea13f: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea144: 6a ff                        	push	-0x1
 11ea146: 83 ec 0c                     	sub	esp, 0xc
 11ea149: f3 0f 11 44 24 08            	movss	dword ptr [esp + 0x8], xmm0
 11ea14f: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11ea157: f3 0f 11 44 24 04            	movss	dword ptr [esp + 0x4], xmm0
 11ea15d: f3 0f 10 45 fc               	movss	xmm0, dword ptr [ebp - 0x4]
 11ea162: f3 0f 11 04 24               	movss	dword ptr [esp], xmm0
 11ea167: 50                           	push	eax
 11ea168: 53                           	push	ebx
 11ea169: 57                           	push	edi
 11ea16a: e8 71 a0 fc ff               	call	0x11b41e0
 11ea16f: 8b 4e 20                     	mov	ecx, dword ptr [esi + 0x20]
 11ea172: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
 11ea175: 51                           	push	ecx
 11ea176: 8b 0d 2c 58 b5 01            	mov	ecx, dword ptr [0x1b5582c]
 11ea17c: 53                           	push	ebx
 11ea17d: 52                           	push	edx
 11ea17e: e8 cd 97 fc ff               	call	0x11b3950
 11ea183: 5b                           	pop	ebx
 11ea184: 5f                           	pop	edi
 11ea185: 5e                           	pop	esi
 11ea186: 8b e5                        	mov	esp, ebp
 11ea188: 5d                           	pop	ebp
 11ea189: c2 10 00                     	ret	0x10
