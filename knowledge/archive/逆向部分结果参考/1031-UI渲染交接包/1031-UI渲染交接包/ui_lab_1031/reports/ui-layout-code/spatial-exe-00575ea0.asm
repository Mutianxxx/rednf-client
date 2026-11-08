
<stdin>:	file format elf32-i386

Disassembly of section .text:

00575ea0 <.text>:
  575ea0: 55                           	push	ebp
  575ea1: 8b ec                        	mov	ebp, esp
  575ea3: 83 ec 4c                     	sub	esp, 0x4c
  575ea6: 56                           	push	esi
  575ea7: 89 4d dc                     	mov	dword ptr [ebp - 0x24], ecx
  575eaa: 8b 89 e4 02 00 00            	mov	ecx, dword ptr [ecx + 0x2e4]
  575eb0: 33 f6                        	xor	esi, esi
  575eb2: 3b ce                        	cmp	ecx, esi
  575eb4: 0f 84 f9 01 00 00            	je	0x5760b3 <.text+0x213>
  575eba: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  575ebd: 2b 51 50                     	sub	edx, dword ptr [ecx + 0x50]
  575ec0: 83 c1 4c                     	add	ecx, 0x4c
  575ec3: b8 67 66 66 66               	mov	eax, 0x66666667
  575ec8: f7 ea                        	imul	edx
  575eca: c1 fa 05                     	sar	edx, 0x5
  575ecd: 8b c2                        	mov	eax, edx
  575ecf: c1 e8 1f                     	shr	eax, 0x1f
  575ed2: 03 c2                        	add	eax, edx
  575ed4: 0f 84 d9 01 00 00            	je	0x5760b3 <.text+0x213>
  575eda: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  575edd: 2b 51 04                     	sub	edx, dword ptr [ecx + 0x4]
  575ee0: b8 67 66 66 66               	mov	eax, 0x66666667
  575ee5: f7 ea                        	imul	edx
  575ee7: c1 fa 05                     	sar	edx, 0x5
  575eea: 8b c2                        	mov	eax, edx
  575eec: c1 e8 1f                     	shr	eax, 0x1f
  575eef: 03 c2                        	add	eax, edx
  575ef1: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
  575ef4: 0f 84 b9 01 00 00            	je	0x5760b3 <.text+0x213>
  575efa: 53                           	push	ebx
  575efb: 57                           	push	edi
  575efc: 89 75 e8                     	mov	dword ptr [ebp - 0x18], esi
  575eff: 90                           	nop
  575f00: 8b 71 04                     	mov	esi, dword ptr [ecx + 0x4]
  575f03: 8b 49 08                     	mov	ecx, dword ptr [ecx + 0x8]
  575f06: 2b ce                        	sub	ecx, esi
  575f08: b8 67 66 66 66               	mov	eax, 0x66666667
  575f0d: f7 e9                        	imul	ecx
  575f0f: c1 fa 05                     	sar	edx, 0x5
  575f12: 8b ca                        	mov	ecx, edx
  575f14: c1 e9 1f                     	shr	ecx, 0x1f
  575f17: 03 ca                        	add	ecx, edx
  575f19: 39 4d ec                     	cmp	dword ptr [ebp - 0x14], ecx
  575f1c: 0f 83 96 01 00 00            	jae	0x5760b8 <.text+0x218>
  575f22: 03 75 e8                     	add	esi, dword ptr [ebp - 0x18]
  575f25: 89 75 e4                     	mov	dword ptr [ebp - 0x1c], esi
  575f28: 0f 84 83 01 00 00            	je	0x5760b1 <.text+0x211>
  575f2e: 8b 7e 3c                     	mov	edi, dword ptr [esi + 0x3c]
  575f31: 8b 4e 40                     	mov	ecx, dword ptr [esi + 0x40]
  575f34: 2b cf                        	sub	ecx, edi
  575f36: b8 89 88 88 88               	mov	eax, 0x88888889
  575f3b: f7 e9                        	imul	ecx
  575f3d: 03 d1                        	add	edx, ecx
  575f3f: c1 fa 05                     	sar	edx, 0x5
  575f42: 8b c2                        	mov	eax, edx
  575f44: 33 db                        	xor	ebx, ebx
  575f46: c1 e8 1f                     	shr	eax, 0x1f
  575f49: 03 c2                        	add	eax, edx
  575f4b: 89 5d e0                     	mov	dword ptr [ebp - 0x20], ebx
  575f4e: 0f 84 27 01 00 00            	je	0x57607b <.text+0x1db>
  575f54: 33 d2                        	xor	edx, edx
  575f56: 89 55 f0                     	mov	dword ptr [ebp - 0x10], edx
  575f59: eb 07                        	jmp	0x575f62 <.text+0xc2>
  575f5b: eb 03                        	jmp	0x575f60 <.text+0xc0>
  575f5d: 8d 49 00                     	lea	ecx, [ecx]
  575f60: 33 d2                        	xor	edx, edx
  575f62: 89 55 f4                     	mov	dword ptr [ebp - 0xc], edx
  575f65: 3b d8                        	cmp	ebx, eax
  575f67: 0f 83 4b 01 00 00            	jae	0x5760b8 <.text+0x218>
  575f6d: 03 7d f0                     	add	edi, dword ptr [ebp - 0x10]
  575f70: 3b fa                        	cmp	edi, edx
  575f72: 0f 84 39 01 00 00            	je	0x5760b1 <.text+0x211>
  575f78: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
  575f7b: 8b 47 0c                     	mov	eax, dword ptr [edi + 0xc]
  575f7e: 2b c1                        	sub	eax, ecx
  575f80: c1 f8 04                     	sar	eax, 0x4
  575f83: 89 55 fc                     	mov	dword ptr [ebp - 0x4], edx
  575f86: 3b c2                        	cmp	eax, edx
  575f88: 0f 86 c2 00 00 00            	jbe	0x576050 <.text+0x1b0>
  575f8e: 89 55 f8                     	mov	dword ptr [ebp - 0x8], edx
  575f91: 8b 16                        	mov	edx, dword ptr [esi]
  575f93: ff 45 f4                     	inc	dword ptr [ebp - 0xc]
  575f96: 89 55 cc                     	mov	dword ptr [ebp - 0x34], edx
  575f99: 8b 17                        	mov	edx, dword ptr [edi]
  575f9b: 89 55 d0                     	mov	dword ptr [ebp - 0x30], edx
  575f9e: 39 45 fc                     	cmp	dword ptr [ebp - 0x4], eax
  575fa1: 0f 83 11 01 00 00            	jae	0x5760b8 <.text+0x218>
  575fa7: 8b 5d f8                     	mov	ebx, dword ptr [ebp - 0x8]
  575faa: 8b 75 dc                     	mov	esi, dword ptr [ebp - 0x24]
  575fad: 03 d9                        	add	ebx, ecx
  575faf: 8d 4d c0                     	lea	ecx, [ebp - 0x40]
  575fb2: 81 c6 e8 02 00 00            	add	esi, 0x2e8
  575fb8: 51                           	push	ecx
  575fb9: 8b ce                        	mov	ecx, esi
  575fbb: e8 80 e3 24 00               	call	0x7c4340 <.text+0x24e4a0>
  575fc0: 53                           	push	ebx
  575fc1: 8d 55 b4                     	lea	edx, [ebp - 0x4c]
  575fc4: 52                           	push	edx
  575fc5: 8b ce                        	mov	ecx, esi
  575fc7: 89 45 d8                     	mov	dword ptr [ebp - 0x28], eax
  575fca: e8 81 26 0b 00               	call	0x628650 <.text+0xb27b0>
  575fcf: 8b 08                        	mov	ecx, dword ptr [eax]
  575fd1: 85 c9                        	test	ecx, ecx
  575fd3: 0f 84 df 00 00 00            	je	0x5760b8 <.text+0x218>
  575fd9: 8b 09                        	mov	ecx, dword ptr [ecx]
  575fdb: 85 c9                        	test	ecx, ecx
  575fdd: 0f 84 d5 00 00 00            	je	0x5760b8 <.text+0x218>
  575fe3: 8b 5d d8                     	mov	ebx, dword ptr [ebp - 0x28]
  575fe6: 8b 13                        	mov	edx, dword ptr [ebx]
  575fe8: 85 d2                        	test	edx, edx
  575fea: 74 02                        	je	0x575fee <.text+0x14e>
  575fec: 8b 12                        	mov	edx, dword ptr [edx]
  575fee: 3b ca                        	cmp	ecx, edx
  575ff0: 0f 85 c2 00 00 00            	jne	0x5760b8 <.text+0x218>
  575ff6: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  575ff9: 3b 43 08                     	cmp	eax, dword ptr [ebx + 0x8]
  575ffc: 75 2e                        	jne	0x57602c <.text+0x18c>
  575ffe: 8b 47 08                     	mov	eax, dword ptr [edi + 0x8]
  576001: 8b 4f 0c                     	mov	ecx, dword ptr [edi + 0xc]
  576004: 2b c8                        	sub	ecx, eax
  576006: c1 f9 04                     	sar	ecx, 0x4
  576009: 39 4d fc                     	cmp	dword ptr [ebp - 0x4], ecx
  57600c: 0f 83 a6 00 00 00            	jae	0x5760b8 <.text+0x218>
  576012: 03 45 f8                     	add	eax, dword ptr [ebp - 0x8]
  576015: 8b ce                        	mov	ecx, esi
  576017: 50                           	push	eax
  576018: e8 43 fb ff ff               	call	0x575b60
  57601d: f3 0f 7e 45 cc               	movq	xmm0, qword ptr [ebp - 0x34]
  576022: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  576025: 66 0f d6 00                  	movq	qword ptr [eax], xmm0
  576029: 89 48 08                     	mov	dword ptr [eax + 0x8], ecx
  57602c: 8b 4f 08                     	mov	ecx, dword ptr [edi + 0x8]
  57602f: 8b 47 0c                     	mov	eax, dword ptr [edi + 0xc]
  576032: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
  576035: 83 45 f8 10                  	add	dword ptr [ebp - 0x8], 0x10
  576039: 8b 75 e4                     	mov	esi, dword ptr [ebp - 0x1c]
  57603c: 2b c1                        	sub	eax, ecx
  57603e: 42                           	inc	edx
  57603f: c1 f8 04                     	sar	eax, 0x4
  576042: 89 55 fc                     	mov	dword ptr [ebp - 0x4], edx
  576045: 3b d0                        	cmp	edx, eax
  576047: 0f 82 44 ff ff ff            	jb	0x575f91 <.text+0xf1>
  57604d: 8b 5d e0                     	mov	ebx, dword ptr [ebp - 0x20]
  576050: 8b 7e 3c                     	mov	edi, dword ptr [esi + 0x3c]
  576053: 8b 4e 40                     	mov	ecx, dword ptr [esi + 0x40]
  576056: 83 45 f0 3c                  	add	dword ptr [ebp - 0x10], 0x3c
  57605a: 2b cf                        	sub	ecx, edi
  57605c: b8 89 88 88 88               	mov	eax, 0x88888889
  576061: f7 e9                        	imul	ecx
  576063: 03 d1                        	add	edx, ecx
  576065: c1 fa 05                     	sar	edx, 0x5
  576068: 8b c2                        	mov	eax, edx
  57606a: c1 e8 1f                     	shr	eax, 0x1f
  57606d: 43                           	inc	ebx
  57606e: 03 c2                        	add	eax, edx
  576070: 89 5d e0                     	mov	dword ptr [ebp - 0x20], ebx
  576073: 3b d8                        	cmp	ebx, eax
  576075: 0f 82 e5 fe ff ff            	jb	0x575f60 <.text+0xc0>
  57607b: 8b 55 dc                     	mov	edx, dword ptr [ebp - 0x24]
  57607e: 8b 8a e4 02 00 00            	mov	ecx, dword ptr [edx + 0x2e4]
  576084: 8b 51 54                     	mov	edx, dword ptr [ecx + 0x54]
  576087: 2b 51 50                     	sub	edx, dword ptr [ecx + 0x50]
  57608a: 8b 75 ec                     	mov	esi, dword ptr [ebp - 0x14]
  57608d: 83 45 e8 50                  	add	dword ptr [ebp - 0x18], 0x50
  576091: 83 c1 4c                     	add	ecx, 0x4c
  576094: b8 67 66 66 66               	mov	eax, 0x66666667
  576099: f7 ea                        	imul	edx
  57609b: c1 fa 05                     	sar	edx, 0x5
  57609e: 8b c2                        	mov	eax, edx
  5760a0: c1 e8 1f                     	shr	eax, 0x1f
  5760a3: 46                           	inc	esi
  5760a4: 03 c2                        	add	eax, edx
  5760a6: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
  5760a9: 3b f0                        	cmp	esi, eax
  5760ab: 0f 82 4f fe ff ff            	jb	0x575f00 <.text+0x60>
  5760b1: 5f                           	pop	edi
  5760b2: 5b                           	pop	ebx
  5760b3: 5e                           	pop	esi
  5760b4: 8b e5                        	mov	esp, ebp
  5760b6: 5d                           	pop	ebp
  5760b7: c3                           	ret
  5760b8: e8 ea 0c e6 00               	call	0x13d6da7 <.text+0xe60f07>
  5760bd: cc                           	int3
  5760be: cc                           	int3
  5760bf: cc                           	int3
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
  5760eb: 74 0a                        	je	0x5760f7 <.text+0x257>
  5760ed: 8b 12                        	mov	edx, dword ptr [edx]
  5760ef: 85 d2                        	test	edx, edx
  5760f1: 74 04                        	je	0x5760f7 <.text+0x257>
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
  576127: 74 0a                        	je	0x576133 <.text+0x293>
  576129: 8b 12                        	mov	edx, dword ptr [edx]
  57612b: 85 d2                        	test	edx, edx
  57612d: 74 04                        	je	0x576133 <.text+0x293>
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
  576160: 74 0a                        	je	0x57616c <.text+0x2cc>
  576162: 68 a4 21 56 01               	push	0x15621a4
  576167: e8 ab b6 e4 00               	call	0x13c1817 <.text+0xe4b977>
  57616c: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  57616f: 85 c0                        	test	eax, eax
  576171: 0f 84 84 02 00 00            	je	0x5763fb <.text+0x55b>
  576177: 83 38 00                     	cmp	dword ptr [eax], 0x0
  57617a: 0f 84 7b 02 00 00            	je	0x5763fb <.text+0x55b>
  576180: 57                           	push	edi
  576181: 8d 4d 0c                     	lea	ecx, [ebp + 0xc]
  576184: e8 c7 3e f2 ff               	call	0x49a050
  576189: 8b 13                        	mov	edx, dword ptr [ebx]
  57618b: 80 7a 39 00                  	cmp	byte ptr [edx + 0x39], 0x0
  57618f: 74 05                        	je	0x576196 <.text+0x2f6>
  576191: 8b 7b 08                     	mov	edi, dword ptr [ebx + 0x8]
  576194: eb 17                        	jmp	0x5761ad <.text+0x30d>
  576196: 8b 43 08                     	mov	eax, dword ptr [ebx + 0x8]
  576199: 80 78 39 00                  	cmp	byte ptr [eax + 0x39], 0x0
  57619d: 74 04                        	je	0x5761a3 <.text+0x303>
  57619f: 8b fa                        	mov	edi, edx
  5761a1: eb 0a                        	jmp	0x5761ad <.text+0x30d>
  5761a3: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
  5761a6: 8b 78 08                     	mov	edi, dword ptr [eax + 0x8]
  5761a9: 3b c3                        	cmp	eax, ebx
  5761ab: 75 79                        	jne	0x576226 <.text+0x386>
  5761ad: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  5761b1: 8b 73 04                     	mov	esi, dword ptr [ebx + 0x4]
  5761b4: 75 03                        	jne	0x5761b9 <.text+0x319>
  5761b6: 89 77 04                     	mov	dword ptr [edi + 0x4], esi
  5761b9: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  5761bc: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  5761bf: 39 58 04                     	cmp	dword ptr [eax + 0x4], ebx
  5761c2: 75 05                        	jne	0x5761c9 <.text+0x329>
  5761c4: 89 78 04                     	mov	dword ptr [eax + 0x4], edi
  5761c7: eb 0b                        	jmp	0x5761d4 <.text+0x334>
  5761c9: 39 1e                        	cmp	dword ptr [esi], ebx
  5761cb: 75 04                        	jne	0x5761d1 <.text+0x331>
  5761cd: 89 3e                        	mov	dword ptr [esi], edi
  5761cf: eb 03                        	jmp	0x5761d4 <.text+0x334>
  5761d1: 89 7e 08                     	mov	dword ptr [esi + 0x8], edi
  5761d4: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  5761d7: 39 18                        	cmp	dword ptr [eax], ebx
  5761d9: 75 1b                        	jne	0x5761f6 <.text+0x356>
  5761db: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  5761df: 74 04                        	je	0x5761e5 <.text+0x345>
  5761e1: 8b c6                        	mov	eax, esi
  5761e3: eb 0c                        	jmp	0x5761f1 <.text+0x351>
  5761e5: 57                           	push	edi
  5761e6: e8 45 3e f2 ff               	call	0x49a030
  5761eb: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  5761ee: 83 c4 04                     	add	esp, 0x4
  5761f1: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  5761f4: 89 02                        	mov	dword ptr [edx], eax
  5761f6: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  5761f9: 39 58 08                     	cmp	dword ptr [eax + 0x8], ebx
  5761fc: 0f 85 81 00 00 00            	jne	0x576283 <.text+0x3e3>
  576202: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  576206: 74 0a                        	je	0x576212 <.text+0x372>
  576208: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  57620b: 8b c6                        	mov	eax, esi
  57620d: 89 42 08                     	mov	dword ptr [edx + 0x8], eax
  576210: eb 71                        	jmp	0x576283 <.text+0x3e3>
  576212: 57                           	push	edi
  576213: e8 f8 3d f2 ff               	call	0x49a010
  576218: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  57621b: 8b 51 08                     	mov	edx, dword ptr [ecx + 0x8]
  57621e: 83 c4 04                     	add	esp, 0x4
  576221: 89 42 08                     	mov	dword ptr [edx + 0x8], eax
  576224: eb 5d                        	jmp	0x576283 <.text+0x3e3>
  576226: 89 42 04                     	mov	dword ptr [edx + 0x4], eax
  576229: 8b 13                        	mov	edx, dword ptr [ebx]
  57622b: 89 10                        	mov	dword ptr [eax], edx
  57622d: 3b 43 08                     	cmp	eax, dword ptr [ebx + 0x8]
  576230: 75 04                        	jne	0x576236 <.text+0x396>
  576232: 8b f0                        	mov	esi, eax
  576234: eb 1a                        	jmp	0x576250 <.text+0x3b0>
  576236: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  57623a: 8b 70 04                     	mov	esi, dword ptr [eax + 0x4]
  57623d: 75 03                        	jne	0x576242 <.text+0x3a2>
  57623f: 89 77 04                     	mov	dword ptr [edi + 0x4], esi
  576242: 89 3e                        	mov	dword ptr [esi], edi
  576244: 8b 53 08                     	mov	edx, dword ptr [ebx + 0x8]
  576247: 89 50 08                     	mov	dword ptr [eax + 0x8], edx
  57624a: 8b 4b 08                     	mov	ecx, dword ptr [ebx + 0x8]
  57624d: 89 41 04                     	mov	dword ptr [ecx + 0x4], eax
  576250: 8b 55 fc                     	mov	edx, dword ptr [ebp - 0x4]
  576253: 8b 4a 08                     	mov	ecx, dword ptr [edx + 0x8]
  576256: 39 59 04                     	cmp	dword ptr [ecx + 0x4], ebx
  576259: 75 05                        	jne	0x576260 <.text+0x3c0>
  57625b: 89 41 04                     	mov	dword ptr [ecx + 0x4], eax
  57625e: eb 0e                        	jmp	0x57626e <.text+0x3ce>
  576260: 8b 4b 04                     	mov	ecx, dword ptr [ebx + 0x4]
  576263: 39 19                        	cmp	dword ptr [ecx], ebx
  576265: 75 04                        	jne	0x57626b <.text+0x3cb>
  576267: 89 01                        	mov	dword ptr [ecx], eax
  576269: eb 03                        	jmp	0x57626e <.text+0x3ce>
  57626b: 89 41 08                     	mov	dword ptr [ecx + 0x8], eax
  57626e: 8b 4b 04                     	mov	ecx, dword ptr [ebx + 0x4]
  576271: 89 48 04                     	mov	dword ptr [eax + 0x4], ecx
  576274: 8a 48 38                     	mov	cl, byte ptr [eax + 0x38]
  576277: 8a 53 38                     	mov	dl, byte ptr [ebx + 0x38]
  57627a: 88 50 38                     	mov	byte ptr [eax + 0x38], dl
  57627d: 88 4b 38                     	mov	byte ptr [ebx + 0x38], cl
  576280: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  576283: 80 7b 38 01                  	cmp	byte ptr [ebx + 0x38], 0x1
  576287: 0f 85 0e 01 00 00            	jne	0x57639b <.text+0x4fb>
  57628d: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  576290: 3b 78 04                     	cmp	edi, dword ptr [eax + 0x4]
  576293: 0f 84 fe 00 00 00            	je	0x576397 <.text+0x4f7>
  576299: 8d a4 24 00 00 00 00         	lea	esp, [esp]
  5762a0: 80 7f 38 01                  	cmp	byte ptr [edi + 0x38], 0x1
  5762a4: 0f 85 ed 00 00 00            	jne	0x576397 <.text+0x4f7>
  5762aa: 8b 06                        	mov	eax, dword ptr [esi]
  5762ac: 3b f8                        	cmp	edi, eax
  5762ae: 75 6c                        	jne	0x57631c <.text+0x47c>
  5762b0: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  5762b3: 80 78 38 00                  	cmp	byte ptr [eax + 0x38], 0x0
  5762b7: 75 14                        	jne	0x5762cd <.text+0x42d>
  5762b9: c6 40 38 01                  	mov	byte ptr [eax + 0x38], 0x1
  5762bd: 56                           	push	esi
  5762be: c6 46 38 00                  	mov	byte ptr [esi + 0x38], 0x0
  5762c2: e8 89 b1 ff ff               	call	0x571450
  5762c7: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  5762ca: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  5762cd: 80 78 39 00                  	cmp	byte ptr [eax + 0x39], 0x0
  5762d1: 75 7d                        	jne	0x576350 <.text+0x4b0>
  5762d3: 8b 10                        	mov	edx, dword ptr [eax]
  5762d5: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  5762d9: 75 09                        	jne	0x5762e4 <.text+0x444>
  5762db: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  5762de: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  5762e2: 74 68                        	je	0x57634c <.text+0x4ac>
  5762e4: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  5762e7: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  5762eb: 75 16                        	jne	0x576303 <.text+0x463>
  5762ed: 8b 10                        	mov	edx, dword ptr [eax]
  5762ef: c6 42 38 01                  	mov	byte ptr [edx + 0x38], 0x1
  5762f3: 50                           	push	eax
  5762f4: c6 40 38 00                  	mov	byte ptr [eax + 0x38], 0x0
  5762f8: e8 23 2f 3f 00               	call	0x969220 <.text+0x3f3380>
  5762fd: 8b 46 08                     	mov	eax, dword ptr [esi + 0x8]
  576300: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  576303: 8a 56 38                     	mov	dl, byte ptr [esi + 0x38]
  576306: 88 50 38                     	mov	byte ptr [eax + 0x38], dl
  576309: c6 46 38 01                  	mov	byte ptr [esi + 0x38], 0x1
  57630d: 8b 40 08                     	mov	eax, dword ptr [eax + 0x8]
  576310: 56                           	push	esi
  576311: c6 40 38 01                  	mov	byte ptr [eax + 0x38], 0x1
  576315: e8 36 b1 ff ff               	call	0x571450
  57631a: eb 7b                        	jmp	0x576397 <.text+0x4f7>
  57631c: 80 78 38 00                  	cmp	byte ptr [eax + 0x38], 0x0
  576320: 75 13                        	jne	0x576335 <.text+0x495>
  576322: c6 40 38 01                  	mov	byte ptr [eax + 0x38], 0x1
  576326: 56                           	push	esi
  576327: c6 46 38 00                  	mov	byte ptr [esi + 0x38], 0x0
  57632b: e8 f0 2e 3f 00               	call	0x969220 <.text+0x3f3380>
  576330: 8b 06                        	mov	eax, dword ptr [esi]
  576332: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  576335: 80 78 39 00                  	cmp	byte ptr [eax + 0x39], 0x0
  576339: 75 15                        	jne	0x576350 <.text+0x4b0>
  57633b: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
  57633e: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  576342: 75 1f                        	jne	0x576363 <.text+0x4c3>
  576344: 8b 10                        	mov	edx, dword ptr [eax]
  576346: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  57634a: 75 17                        	jne	0x576363 <.text+0x4c3>
  57634c: c6 40 38 00                  	mov	byte ptr [eax + 0x38], 0x0
  576350: 8b 41 08                     	mov	eax, dword ptr [ecx + 0x8]
  576353: 8b fe                        	mov	edi, esi
  576355: 8b 76 04                     	mov	esi, dword ptr [esi + 0x4]
  576358: 3b 78 04                     	cmp	edi, dword ptr [eax + 0x4]
  57635b: 0f 85 3f ff ff ff            	jne	0x5762a0 <.text+0x400>
  576361: eb 34                        	jmp	0x576397 <.text+0x4f7>
  576363: 8b 10                        	mov	edx, dword ptr [eax]
  576365: 80 7a 38 01                  	cmp	byte ptr [edx + 0x38], 0x1
  576369: 75 16                        	jne	0x576381 <.text+0x4e1>
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
  576392: e8 89 2e 3f 00               	call	0x969220 <.text+0x3f3380>
  576397: c6 47 38 01                  	mov	byte ptr [edi + 0x38], 0x1
  57639b: 83 7b 30 08                  	cmp	dword ptr [ebx + 0x30], 0x8
  57639f: 5f                           	pop	edi
  5763a0: 72 0c                        	jb	0x5763ae <.text+0x50e>
  5763a2: 8b 4b 1c                     	mov	ecx, dword ptr [ebx + 0x1c]
  5763a5: 51                           	push	ecx
  5763a6: e8 7c f7 e5 00               	call	0x13d5b27 <.text+0xe5fc87>
  5763ab: 83 c4 04                     	add	esp, 0x4
  5763ae: 33 f6                        	xor	esi, esi
  5763b0: 33 d2                        	xor	edx, edx
  5763b2: c7 43 30 07 00 00 00         	mov	dword ptr [ebx + 0x30], 0x7
  5763b9: 89 73 2c                     	mov	dword ptr [ebx + 0x2c], esi
  5763bc: 66 89 53 1c                  	mov	word ptr [ebx + 0x1c], dx
  5763c0: 8b 43 18                     	mov	eax, dword ptr [ebx + 0x18]
  5763c3: 50                           	push	eax
  5763c4: e8 5e f7 e5 00               	call	0x13d5b27 <.text+0xe5fc87>
  5763c9: 53                           	push	ebx
  5763ca: 89 73 18                     	mov	dword ptr [ebx + 0x18], esi
  5763cd: e8 55 f7 e5 00               	call	0x13d5b27 <.text+0xe5fc87>
  5763d2: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
  5763d5: 8b 41 0c                     	mov	eax, dword ptr [ecx + 0xc]
  5763d8: 83 c4 08                     	add	esp, 0x8
  5763db: 3b c6                        	cmp	eax, esi
  5763dd: 76 04                        	jbe	0x5763e3 <.text+0x543>
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
  5763fb: e8 a7 09 e6 00               	call	0x13d6da7 <.text+0xe60f07>
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
  576421: 75 54                        	jne	0x576477 <.text+0x5d7>
  576423: 8b 47 08                     	mov	eax, dword ptr [edi + 0x8]
  576426: 50                           	push	eax
  576427: 8b cb                        	mov	ecx, ebx
  576429: e8 e2 ff ff ff               	call	0x576410 <.text+0x570>
  57642e: 83 7e 30 08                  	cmp	dword ptr [esi + 0x30], 0x8
  576432: 8b 3f                        	mov	edi, dword ptr [edi]
  576434: 72 0c                        	jb	0x576442 <.text+0x5a2>
  576436: 8b 4e 1c                     	mov	ecx, dword ptr [esi + 0x1c]
  576439: 51                           	push	ecx
  57643a: e8 e8 f6 e5 00               	call	0x13d5b27 <.text+0xe5fc87>
  57643f: 83 c4 04                     	add	esp, 0x4
  576442: 33 d2                        	xor	edx, edx
  576444: c7 46 30 07 00 00 00         	mov	dword ptr [esi + 0x30], 0x7
  57644b: c7 46 2c 00 00 00 00         	mov	dword ptr [esi + 0x2c], 0x0
  576452: 66 89 56 1c                  	mov	word ptr [esi + 0x1c], dx
  576456: 8b 46 18                     	mov	eax, dword ptr [esi + 0x18]
  576459: 50                           	push	eax
  57645a: e8 c8 f6 e5 00               	call	0x13d5b27 <.text+0xe5fc87>
  57645f: 56                           	push	esi
  576460: c7 46 18 00 00 00 00         	mov	dword ptr [esi + 0x18], 0x0
  576467: e8 bb f6 e5 00               	call	0x13d5b27 <.text+0xe5fc87>
  57646c: 83 c4 08                     	add	esp, 0x8
  57646f: 80 7f 39 00                  	cmp	byte ptr [edi + 0x39], 0x0
  576473: 8b f7                        	mov	esi, edi
  576475: 74 ac                        	je	0x576423 <.text+0x583>
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
  5764bd: 75 48                        	jne	0x576507 <.text+0x667>
  5764bf: 8d 4f 0c                     	lea	ecx, [edi + 0xc]
  5764c2: 51                           	push	ecx
  5764c3: 8b cb                        	mov	ecx, ebx
  5764c5: e8 56 f6 d6 00               	call	0x12e5b20 <.text+0xd6fc80>
  5764ca: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
  5764cd: 8b 4d ec                     	mov	ecx, dword ptr [ebp - 0x14]
  5764d0: 8b f0                        	mov	esi, eax
  5764d2: 89 56 04                     	mov	dword ptr [esi + 0x4], edx
  5764d5: 8a 47 38                     	mov	al, byte ptr [edi + 0x38]
  5764d8: 88 46 38                     	mov	byte ptr [esi + 0x38], al
  5764db: 80 79 39 00                  	cmp	byte ptr [ecx + 0x39], 0x0
  5764df: 74 03                        	je	0x5764e4 <.text+0x644>
  5764e1: 89 75 ec                     	mov	dword ptr [ebp - 0x14], esi
  5764e4: 8b 17                        	mov	edx, dword ptr [edi]
  5764e6: 56                           	push	esi
  5764e7: 52                           	push	edx
  5764e8: 8b cb                        	mov	ecx, ebx
  5764ea: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  5764f1: e8 8a ff ff ff               	call	0x576480 <.text+0x5e0>
  5764f6: 89 06                        	mov	dword ptr [esi], eax
  5764f8: 8b 47 08                     	mov	eax, dword ptr [edi + 0x8]
  5764fb: 56                           	push	esi
  5764fc: 50                           	push	eax
  5764fd: 8b cb                        	mov	ecx, ebx
  5764ff: e8 7c ff ff ff               	call	0x576480 <.text+0x5e0>
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
