
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
