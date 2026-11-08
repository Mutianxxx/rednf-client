
<stdin>:	file format elf32-i386

Disassembly of section .text:

005760c0 <.text>:
  5760c0: 55                           	push	ebp
  5760c1: 8b ec                        	mov	ebp, esp
  5760c3: 83 ec 34                     	sub	esp, 0x34
  5760c6: 56                           	push	esi
  5760c7: 8d 45 ec                     	lea	eax, [ebp - 0x14]
  5760ca: 50                           	push	eax
  5760cb: 8b f1                        	mov	esi, ecx
  5760cd: e8 5e df f2 ff               	call	0x4a4030
  5760d2: 83 ec 10                     	sub	esp, 0x10
  5760d5: 8b cc                        	mov	ecx, esp
  5760d7: c7 01 00 00 00 00            	mov	dword ptr [ecx], 0x0
  5760dd: c7 41 04 00 00 00 00         	mov	dword ptr [ecx + 0x4], 0x0
  5760e4: 8b 10                        	mov	edx, dword ptr [eax]
  5760e6: 89 65 fc                     	mov	dword ptr [ebp - 0x4], esp
  5760e9: 85 d2                        	test	edx, edx
  5760eb: 74 0a                        	je	0x5760f7 <.text+0x37>
  5760ed: 8b 12                        	mov	edx, dword ptr [edx]
  5760ef: 85 d2                        	test	edx, edx
  5760f1: 74 04                        	je	0x5760f7 <.text+0x37>
  5760f3: 8b 12                        	mov	edx, dword ptr [edx]
  5760f5: 89 11                        	mov	dword ptr [ecx], edx
  5760f7: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  5760fa: 89 51 08                     	mov	dword ptr [ecx + 0x8], edx
  5760fd: 8b 40 0c                     	mov	eax, dword ptr [eax + 0xc]
  576100: 89 41 0c                     	mov	dword ptr [ecx + 0xc], eax
  576103: 8d 4d dc                     	lea	ecx, [ebp - 0x24]
  576106: 51                           	push	ecx
  576107: 8b ce                        	mov	ecx, esi
  576109: e8 62 d4 f2 ff               	call	0x4a3570
  57610e: 83 ec 10                     	sub	esp, 0x10
  576111: 8b cc                        	mov	ecx, esp
  576113: c7 01 00 00 00 00            	mov	dword ptr [ecx], 0x0
  576119: c7 41 04 00 00 00 00         	mov	dword ptr [ecx + 0x4], 0x0
  576120: 8b 10                        	mov	edx, dword ptr [eax]
  576122: 89 65 fc                     	mov	dword ptr [ebp - 0x4], esp
  576125: 85 d2                        	test	edx, edx
  576127: 74 0a                        	je	0x576133 <.text+0x73>
  576129: 8b 12                        	mov	edx, dword ptr [edx]
  57612b: 85 d2                        	test	edx, edx
  57612d: 74 04                        	je	0x576133 <.text+0x73>
  57612f: 8b 12                        	mov	edx, dword ptr [edx]
  576131: 89 11                        	mov	dword ptr [ecx], edx
  576133: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  576136: 89 51 08                     	mov	dword ptr [ecx + 0x8], edx
  576139: 8b 40 0c                     	mov	eax, dword ptr [eax + 0xc]
  57613c: 89 41 0c                     	mov	dword ptr [ecx + 0xc], eax
  57613f: 8d 4d cc                     	lea	ecx, [ebp - 0x34]
  576142: 51                           	push	ecx
  576143: 8b ce                        	mov	ecx, esi
  576145: e8 06 fb ff ff               	call	0x575c50
  57614a: 5e                           	pop	esi
  57614b: 8b e5                        	mov	esp, ebp
  57614d: 5d                           	pop	ebp
  57614e: c3                           	ret
  57614f: cc                           	int3
  576150: 55                           	push	ebp
  576151: 8b ec                        	mov	ebp, esp
  576153: 51                           	push	ecx
  576154: 53                           	push	ebx
  576155: 8b 5d 14                     	mov	ebx, dword ptr [ebp + 0x14]
  576158: 80 7b 39 00                  	cmp	byte ptr [ebx + 0x39], 0x0
  57615c: 56                           	push	esi
  57615d: 89 4d fc                     	mov	dword ptr [ebp - 0x4], ecx
  576160: 74 0a                        	je	0x57616c <.text+0xac>
  576162: 68 a4 21 56 01               	push	0x15621a4
  576167: e8 ab b6 e4 00               	call	0x13c1817 <.text+0xe4b757>
  57616c: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  57616f: 85 c0                        	test	eax, eax
  576171: 0f 84 84 02 00 00            	je	0x5763fb <.text+0x33b>
  576177: 83 38 00                     	cmp	dword ptr [eax], 0x0
  57617a: 0f 84 7b 02 00 00            	je	0x5763fb <.text+0x33b>
  576180: 57                           	push	edi
  576181: 8d 4d 0c                     	lea	ecx, [ebp + 0xc]
  576184: e8 c7 3e f2 ff               	call	0x49a050
  576189: 8b 13                        	mov	edx, dword ptr [ebx]
  57618b: 80 7a 39 00                  	cmp	byte ptr [edx + 0x39], 0x0
  57618f: 74 05                        	je	0x576196 <.text+0xd6>
  576191: 8b 7b 08                     	mov	edi, dword ptr [ebx + 0x8]
  576194: eb 17                        	jmp	0x5761ad <.text+0xed>
  576196: 8b 43 08                     	mov	eax, dword ptr [ebx + 0x8]
  576199: 80 78 39 00                  	cmp	byte ptr [eax + 0x39], 0x0
  57619d: 74 04                        	je	0x5761a3 <.text+0xe3>
  57619f: 8b fa                        	mov	edi, edx
  5761a1: eb 0a                        	jmp	0x5761ad <.text+0xed>
  5761a3: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
  5761a6: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
  5761a9: 3b c3                        	cmp	eax, ebx
  5761ab: 75 79                        	jne	0x576226 <.text+0x166>
  5761ad: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  5761b1: 8b 73 04                     	mov	esi, dword ptr [ebx + 0x4]
  5761b4: 75 03                        	jne	0x5761b9 <.text+0xf9>
  5761b6: 89 77 04                     	mov	dword ptr [edi + 0x4], esi
  5761b9: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  5761bc: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  5761bf: 39 58 04                     	cmp	dword ptr [eax + 0x4], ebx
  5761c2: 75 05                        	jne	0x5761c9 <.text+0x109>
  5761c4: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
  5761c7: eb 0b                        	jmp	0x5761d4 <.text+0x114>
  5761c9: 39 1e                        	cmp	dword ptr [esi], ebx
  5761cb: 75 04                        	jne	0x5761d1 <.text+0x111>
  5761cd: 89 3e                        	mov	dword ptr [esi], edi
  5761cf: eb 03                        	jmp	0x5761d4 <.text+0x114>
  5761d1: 89 7e 08                     	mov	dword ptr [esi + 0x8], edi
  5761d4: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  5761d7: 39 18                        	cmp	dword ptr [eax], ebx
  5761d9: 75 1b                        	jne	0x5761f6 <.text+0x136>
  5761db: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  5761df: 74 04                        	je	0x5761e5 <.text+0x125>
  5761e1: 8b c6                        	mov	eax, esi
  5761e3: eb 0c                        	jmp	0x5761f1 <.text+0x131>
  5761e5: 57                           	push	edi
  5761e6: e8 45 3e f2 ff               	call	0x49a030
  5761eb: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  5761ee: 83 c4 04                     	add	esp, 0x4
  5761f1: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  5761f4: 89 02                        	mov	dword ptr [edx], eax
  5761f6: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  5761f9: 39 58 08                     	cmp	dword ptr [eax + 0x8], ebx
  5761fc: 0f 85 81 00 00 00            	jne	0x576283 <.text+0x1c3>
  576202: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  576206: 74 0a                        	je	0x576212 <.text+0x152>
  576208: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  57620b: 8b c6                        	mov	eax, esi
  57620d: 89 42 08                     	mov	dword ptr [edx + 0x8], eax
  576210: eb 71                        	jmp	0x576283 <.text+0x1c3>
  576212: 57                           	push	edi
  576213: e8 f8 3d f2 ff               	call	0x49a010
  576218: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  57621b: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  57621e: 83 c4 04                     	add	esp, 0x4
  576221: 89 42 08                     	mov	dword ptr [edx + 0x8], eax
  576224: eb 5d                        	jmp	0x576283 <.text+0x1c3>
  576226: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  576229: 8b 13                        	mov	edx, dword ptr [ebx]
  57622b: 89 10                        	mov	dword ptr [eax], edx
  57622d: 3b 43 08                     	cmp	eax, dword ptr [ebx + 0x8]
  576230: 75 04                        	jne	0x576236 <.text+0x176>
  576232: 8b f0                        	mov	esi, eax
  576234: eb 1a                        	jmp	0x576250 <.text+0x190>
  576236: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  57623a: 8b 70 04                     	mov	esi, dword ptr [eax + 0x4]
  57623d: 75 03                        	jne	0x576242 <.text+0x182>
  57623f: 89 77 04                     	mov	dword ptr [edi + 0x4], esi
  576242: 89 3e                        	mov	dword ptr [esi], edi
  576244: 8b 53 08                     	mov	edx, dword ptr [ebx + 0x8]
  576247: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  57624a: 8b 4b 08                     	mov	ecx, dword ptr [ebx + 0x8]
  57624d: 89 41 04                     	mov	dword ptr [ecx + 0x4], eax
  576250: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
  576253: 8b 4a 08                     	mov	ecx, dword ptr [edx + 0x8]
  576256: 39 59 04                     	cmp	dword ptr [ecx + 0x4], ebx
  576259: 75 05                        	jne	0x576260 <.text+0x1a0>
  57625b: 89 41 04                     	mov	dword ptr [ecx + 0x4], eax
  57625e: eb 0e                        	jmp	0x57626e <.text+0x1ae>
  576260: 8b 4b 04                     	mov	ecx, dword ptr [ebx + 0x4]
  576263: 39 19                        	cmp	dword ptr [ecx], ebx
  576265: 75 04                        	jne	0x57626b <.text+0x1ab>
  576267: 89 01                        	mov	dword ptr [ecx], eax
  576269: eb 03                        	jmp	0x57626e <.text+0x1ae>
  57626b: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  57626e: 8b 4b 04                     	mov	ecx, dword ptr [ebx + 0x4]
  576271: 89 48 04                     	mov	dword ptr [eax + 0x4], ecx
  576274: 8a 48 38                     	mov	cl, byte ptr [eax + 0x38]
  576277: 8a 53 38                     	mov	dl, byte ptr [ebx + 0x38]
  57627a: 88 50 38                     	mov	byte ptr [eax + 0x38], dl
  57627d: 88 4b 38                     	mov	byte ptr [ebx + 0x38], cl
  576280: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  576283: 80 7b 38 01                  	cmp	byte ptr [ebx + 0x38], 0x1
  576287: 0f 85 0e 01 00 00            	jne	0x57639b <.text+0x2db>
  57628d: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  576290: 3b 78 04                     	cmp	edi, dword ptr [eax + 0x4]
  576293: 0f 84 fe 00 00 00            	je	0x576397 <.text+0x2d7>
  576299: 8d a4 24 00 00 00 00         	lea	esp, [esp]
  5762a0: 80 7f 38 01                  	cmp	byte ptr [edi + 0x38], 0x1
  5762a4: 0f 85 ed 00 00 00            	jne	0x576397 <.text+0x2d7>
  5762aa: 8b 06                        	mov	eax, dword ptr [esi]
  5762ac: 3b f8                        	cmp	edi, eax
  5762ae: 75 6c                        	jne	0x57631c <.text+0x25c>
  5762b0: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  5762b3: 80 78 38 00                  	cmp	byte ptr [eax + 0x38], 0x0
  5762b7: 75 14                        	jne	0x5762cd <.text+0x20d>
  5762b9: c6 40 38 01                  	mov	byte ptr [eax + 0x38], 0x1
  5762bd: 56                           	push	esi
  5762be: c6 46 38 00                  	mov	byte ptr [esi + 0x38], 0x0
  5762c2: e8 89 b1 ff ff               	call	0x571450
  5762c7: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  5762ca: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  5762cd: 80 78 39 00                  	cmp	byte ptr [eax + 0x39], 0x0
  5762d1: 75 7d                        	jne	0x576350 <.text+0x290>
  5762d3: 8b 10                        	mov	edx, dword ptr [eax]
  5762d5: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  5762d9: 75 09                        	jne	0x5762e4 <.text+0x224>
  5762db: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  5762de: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  5762e2: 74 68                        	je	0x57634c <.text+0x28c>
  5762e4: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  5762e7: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  5762eb: 75 16                        	jne	0x576303 <.text+0x243>
  5762ed: 8b 10                        	mov	edx, dword ptr [eax]
  5762ef: c6 42 38 01                  	mov	byte ptr [edx + 0x38], 0x1
  5762f3: 50                           	push	eax
  5762f4: c6 40 38 00                  	mov	byte ptr [eax + 0x38], 0x0
  5762f8: e8 23 2f 3f 00               	call	0x969220 <.text+0x3f3160>
  5762fd: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  576300: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  576303: 8a 56 38                     	mov	dl, byte ptr [esi + 0x38]
  576306: 88 50 38                     	mov	byte ptr [eax + 0x38], dl
  576309: c6 46 38 01                  	mov	byte ptr [esi + 0x38], 0x1
  57630d: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  576310: 56                           	push	esi
  576311: c6 40 38 01                  	mov	byte ptr [eax + 0x38], 0x1
  576315: e8 36 b1 ff ff               	call	0x571450
  57631a: eb 7b                        	jmp	0x576397 <.text+0x2d7>
  57631c: 80 78 38 00                  	cmp	byte ptr [eax + 0x38], 0x0
  576320: 75 13                        	jne	0x576335 <.text+0x275>
  576322: c6 40 38 01                  	mov	byte ptr [eax + 0x38], 0x1
  576326: 56                           	push	esi
  576327: c6 46 38 00                  	mov	byte ptr [esi + 0x38], 0x0
  57632b: e8 f0 2e 3f 00               	call	0x969220 <.text+0x3f3160>
  576330: 8b 06                        	mov	eax, dword ptr [esi]
  576332: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  576335: 80 78 39 00                  	cmp	byte ptr [eax + 0x39], 0x0
  576339: 75 15                        	jne	0x576350 <.text+0x290>
  57633b: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  57633e: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  576342: 75 1f                        	jne	0x576363 <.text+0x2a3>
  576344: 8b 10                        	mov	edx, dword ptr [eax]
  576346: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  57634a: 75 17                        	jne	0x576363 <.text+0x2a3>
  57634c: c6 40 38 00                  	mov	byte ptr [eax + 0x38], 0x0
  576350: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  576353: 8b fe                        	mov	edi, esi
  576355: 8b 76 04                     	mov	esi, dword ptr [esi + 0x4]
  576358: 3b 78 04                     	cmp	edi, dword ptr [eax + 0x4]
  57635b: 0f 85 3f ff ff ff            	jne	0x5762a0 <.text+0x1e0>
  576361: eb 34                        	jmp	0x576397 <.text+0x2d7>
  576363: 8b 10                        	mov	edx, dword ptr [eax]
  576365: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  576369: 75 16                        	jne	0x576381 <.text+0x2c1>
  57636b: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  57636e: c6 42 38 01                  	mov	byte ptr [edx + 0x38], 0x1
  576372: 50                           	push	eax
  576373: c6 40 38 00                  	mov	byte ptr [eax + 0x38], 0x0
  576377: e8 d4 b0 ff ff               	call	0x571450
  57637c: 8b 06                        	mov	eax, dword ptr [esi]
  57637e: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  576381: 8a 56 38                     	mov	dl, byte ptr [esi + 0x38]
  576384: 88 50 38                     	mov	byte ptr [eax + 0x38], dl
  576387: c6 46 38 01                  	mov	byte ptr [esi + 0x38], 0x1
  57638b: 8b 00                        	mov	eax, dword ptr [eax]
  57638d: 56                           	push	esi
  57638e: c6 40 38 01                  	mov	byte ptr [eax + 0x38], 0x1
  576392: e8 89 2e 3f 00               	call	0x969220 <.text+0x3f3160>
  576397: c6 47 38 01                  	mov	byte ptr [edi + 0x38], 0x1
  57639b: 83 7b 30 08                  	cmp	dword ptr [ebx + 0x30], 0x8
  57639f: 5f                           	pop	edi
  5763a0: 72 0c                        	jb	0x5763ae <.text+0x2ee>
  5763a2: 8b 4b 1c                     	mov	ecx, dword ptr [ebx + 0x1c]
  5763a5: 51                           	push	ecx
  5763a6: e8 7c f7 e5 00               	call	0x13d5b27 <.text+0xe5fa67>
  5763ab: 83 c4 04                     	add	esp, 0x4
  5763ae: 33 f6                        	xor	esi, esi
  5763b0: 33 d2                        	xor	edx, edx
  5763b2: c7 43 30 07 00 00 00         	mov	dword ptr [ebx + 0x30], 0x7
  5763b9: 89 73 2c                     	mov	dword ptr [ebx + 0x2c], esi
  5763bc: 66 89 53 1c                  	mov	word ptr [ebx + 0x1c], dx
  5763c0: 8b 43 18                     	mov	eax, dword ptr [ebx + 0x18]
  5763c3: 50                           	push	eax
  5763c4: e8 5e f7 e5 00               	call	0x13d5b27 <.text+0xe5fa67>
  5763c9: 53                           	push	ebx
  5763ca: 89 73 18                     	mov	dword ptr [ebx + 0x18], esi
  5763cd: e8 55 f7 e5 00               	call	0x13d5b27 <.text+0xe5fa67>
  5763d2: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  5763d5: 8b 41 0c                     	mov	eax, dword ptr [ecx + 0xc]
  5763d8: 83 c4 08                     	add	esp, 0x8
  5763db: 3b c6                        	cmp	eax, esi
  5763dd: 76 04                        	jbe	0x5763e3 <.text+0x323>
  5763df: 48                           	dec	eax
  5763e0: 89 41 0c                     	mov	dword ptr [ecx + 0xc], eax
  5763e3: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  5763e6: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
  5763e9: 8b 09                        	mov	ecx, dword ptr [ecx]
  5763eb: 89 70 04                     	mov	dword ptr [eax + 0x4], esi
  5763ee: 5e                           	pop	esi
  5763ef: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  5763f2: 89 08                        	mov	dword ptr [eax], ecx
  5763f4: 5b                           	pop	ebx
  5763f5: 8b e5                        	mov	esp, ebp
  5763f7: 5d                           	pop	ebp
  5763f8: c2 10 00                     	ret	0x10
  5763fb: e8 a7 09 e6 00               	call	0x13d6da7 <.text+0xe60ce7>
  576400: cc                           	int3
  576401: cc                           	int3
  576402: cc                           	int3
  576403: cc                           	int3
  576404: cc                           	int3
  576405: cc                           	int3
  576406: cc                           	int3
  576407: cc                           	int3
  576408: cc                           	int3
  576409: cc                           	int3
  57640a: cc                           	int3
  57640b: cc                           	int3
  57640c: cc                           	int3
  57640d: cc                           	int3
  57640e: cc                           	int3
  57640f: cc                           	int3
  576410: 55                           	push	ebp
  576411: 8b ec                        	mov	ebp, esp
  576413: 53                           	push	ebx
  576414: 56                           	push	esi
  576415: 8b 75 08                     	mov	esi, dword ptr [ebp + 0x8]
  576418: 80 7e 39 00                  	cmp	byte ptr [esi + 0x39], 0x0
  57641c: 57                           	push	edi
  57641d: 8b d9                        	mov	ebx, ecx
  57641f: 8b fe                        	mov	edi, esi
  576421: 75 54                        	jne	0x576477 <.text+0x3b7>
  576423: 8b 47 08                     	mov	eax, dword ptr [edi + 0x8]
  576426: 50                           	push	eax
  576427: 8b cb                        	mov	ecx, ebx
  576429: e8 e2 ff ff ff               	call	0x576410 <.text+0x350>
  57642e: 83 7e 30 08                  	cmp	dword ptr [esi + 0x30], 0x8
  576432: 8b 3f                        	mov	edi, dword ptr [edi]
  576434: 72 0c                        	jb	0x576442 <.text+0x382>
  576436: 8b 4e 1c                     	mov	ecx, dword ptr [esi + 0x1c]
  576439: 51                           	push	ecx
  57643a: e8 e8 f6 e5 00               	call	0x13d5b27 <.text+0xe5fa67>
  57643f: 83 c4 04                     	add	esp, 0x4
  576442: 33 d2                        	xor	edx, edx
  576444: c7 46 30 07 00 00 00         	mov	dword ptr [esi + 0x30], 0x7
  57644b: c7 46 2c 00 00 00 00         	mov	dword ptr [esi + 0x2c], 0x0
  576452: 66 89 56 1c                  	mov	word ptr [esi + 0x1c], dx
  576456: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
  576459: 50                           	push	eax
  57645a: e8 c8 f6 e5 00               	call	0x13d5b27 <.text+0xe5fa67>
  57645f: 56                           	push	esi
  576460: c7 46 18 00 00 00 00         	mov	dword ptr [esi + 0x18], 0x0
  576467: e8 bb f6 e5 00               	call	0x13d5b27 <.text+0xe5fa67>
  57646c: 83 c4 08                     	add	esp, 0x8
  57646f: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  576473: 8b f7                        	mov	esi, edi
  576475: 74 ac                        	je	0x576423 <.text+0x363>
  576477: 5f                           	pop	edi
  576478: 5e                           	pop	esi
  576479: 5b                           	pop	ebx
  57647a: 5d                           	pop	ebp
  57647b: c2 04 00                     	ret	0x4
  57647e: cc                           	int3
  57647f: cc                           	int3
  576480: 55                           	push	ebp
  576481: 8b ec                        	mov	ebp, esp
  576483: 6a ff                        	push	-0x1
  576485: 68 d0 cd 41 01               	push	0x141cdd0
  57648a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  576490: 50                           	push	eax
  576491: 83 ec 0c                     	sub	esp, 0xc
  576494: 53                           	push	ebx
  576495: 56                           	push	esi
  576496: 57                           	push	edi
  576497: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  57649c: 33 c5                        	xor	eax, ebp
  57649e: 50                           	push	eax
  57649f: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  5764a2: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  5764a8: 89 65 f0                     	mov	dword ptr [ebp - 0x10], esp
  5764ab: 8b d9                        	mov	ebx, ecx
  5764ad: 89 5d e8                     	mov	dword ptr [ebp - 0x18], ebx
  5764b0: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
  5764b3: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  5764b7: 8b 43 08                     	mov	eax, dword ptr [ebx + 0x8]
  5764ba: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
  5764bd: 75 48                        	jne	0x576507 <.text+0x447>
  5764bf: 8d 4f 0c                     	lea	ecx, [edi + 0xc]
  5764c2: 51                           	push	ecx
  5764c3: 8b cb                        	mov	ecx, ebx
  5764c5: e8 56 f6 d6 00               	call	0x12e5b20 <.text+0xd6fa60>
  5764ca: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
  5764cd: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
  5764d0: 8b f0                        	mov	esi, eax
  5764d2: 89 56 04                     	mov	dword ptr [esi + 0x4], edx
  5764d5: 8a 47 38                     	mov	al, byte ptr [edi + 0x38]
  5764d8: 88 46 38                     	mov	byte ptr [esi + 0x38], al
  5764db: 80 79 39 00                  	cmp	byte ptr [ecx + 0x39], 0x0
  5764df: 74 03                        	je	0x5764e4 <.text+0x424>
  5764e1: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
  5764e4: 8b 17                        	mov	edx, dword ptr [edi]
  5764e6: 56                           	push	esi
  5764e7: 52                           	push	edx
  5764e8: 8b cb                        	mov	ecx, ebx
  5764ea: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  5764f1: e8 8a ff ff ff               	call	0x576480 <.text+0x3c0>
  5764f6: 89 06                        	mov	dword ptr [esi], eax
  5764f8: 8b 47 08                     	mov	eax, dword ptr [edi + 0x8]
  5764fb: 56                           	push	esi
  5764fc: 50                           	push	eax
  5764fd: 8b cb                        	mov	ecx, ebx
  5764ff: e8 7c ff ff ff               	call	0x576480 <.text+0x3c0>
  576504: 89 46 08                     	mov	dword ptr [esi + 0x8], eax
  576507: 8b 45 ec                     	mov	eax, dword ptr [ebp - 0x14]
  57650a: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  57650d: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  576514: 59                           	pop	ecx
  576515: 5f                           	pop	edi
  576516: 5e                           	pop	esi
  576517: 5b                           	pop	ebx
  576518: 8b e5                        	mov	esp, ebp
  57651a: 5d                           	pop	ebp
  57651b: c2 08 00                     	ret	0x8
  57651e: 8b 4d                        	<unknown>
