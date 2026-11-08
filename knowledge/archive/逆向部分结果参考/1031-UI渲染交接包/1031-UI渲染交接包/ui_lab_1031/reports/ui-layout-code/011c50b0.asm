
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c50b0 <.text>:
 11c50b0: 55                           	push	ebp
 11c50b1: 8b ec                        	mov	ebp, esp
 11c50b3: 56                           	push	esi
 11c50b4: 8b f1                        	mov	esi, ecx
 11c50b6: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11c50ba: 74 0a                        	je	0x11c50c6 <.text+0x16>
 11c50bc: b8 02 00 00 80               	mov	eax, 0x80000002
 11c50c1: 5e                           	pop	esi
 11c50c2: 5d                           	pop	ebp
 11c50c3: c2 28 00                     	ret	0x28
 11c50c6: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c50c9: 53                           	push	ebx
 11c50ca: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11c50cd: 57                           	push	edi
 11c50ce: 50                           	push	eax
 11c50cf: 8b cb                        	mov	ecx, ebx
 11c50d1: e8 fa fa fe ff               	call	0x11b4bd0
 11c50d6: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
 11c50d9: 51                           	push	ecx
 11c50da: 8b cb                        	mov	ecx, ebx
 11c50dc: 89 86 b8 02 00 00            	mov	dword ptr [esi + 0x2b8], eax
 11c50e2: e8 e9 fa fe ff               	call	0x11b4bd0
 11c50e7: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
 11c50ea: 52                           	push	edx
 11c50eb: 8b cb                        	mov	ecx, ebx
 11c50ed: 89 86 c0 02 00 00            	mov	dword ptr [esi + 0x2c0], eax
 11c50f3: e8 d8 fa fe ff               	call	0x11b4bd0
 11c50f8: 89 86 bc 02 00 00            	mov	dword ptr [esi + 0x2bc], eax
 11c50fe: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11c5101: 83 f8 ff                     	cmp	eax, -0x1
 11c5104: 74 0e                        	je	0x11c5114 <.text+0x64>
 11c5106: 50                           	push	eax
 11c5107: 8b cb                        	mov	ecx, ebx
 11c5109: e8 c2 fa fe ff               	call	0x11b4bd0
 11c510e: 89 86 c4 02 00 00            	mov	dword ptr [esi + 0x2c4], eax
 11c5114: 8b 55 28                     	mov	edx, dword ptr [ebp + 0x28]
 11c5117: 85 d2                        	test	edx, edx
 11c5119: 74 18                        	je	0x11c5133 <.text+0x83>
 11c511b: 8b c2                        	mov	eax, edx
 11c511d: 8d 78 02                     	lea	edi, [eax + 0x2]
 11c5120: 66 8b 08                     	mov	cx, word ptr [eax]
 11c5123: 83 c0 02                     	add	eax, 0x2
 11c5126: 66 85 c9                     	test	cx, cx
 11c5129: 75 f5                        	jne	0x11c5120 <.text+0x70>
 11c512b: 2b c7                        	sub	eax, edi
 11c512d: d1 f8                        	sar	eax
 11c512f: 50                           	push	eax
 11c5130: 52                           	push	edx
 11c5131: eb 23                        	jmp	0x11c5156 <.text+0xa6>
 11c5133: 68 6c 6c 56 01               	push	0x1566c6c
 11c5138: e8 b3 ad fd ff               	call	0x119fef0
 11c513d: 8b c8                        	mov	ecx, eax
 11c513f: 83 c4 04                     	add	esp, 0x4
 11c5142: 8d 79 02                     	lea	edi, [ecx + 0x2]
 11c5145: 66 8b 11                     	mov	dx, word ptr [ecx]
 11c5148: 83 c1 02                     	add	ecx, 0x2
 11c514b: 66 85 d2                     	test	dx, dx
 11c514e: 75 f5                        	jne	0x11c5145 <.text+0x95>
 11c5150: 2b cf                        	sub	ecx, edi
 11c5152: d1 f9                        	sar	ecx
 11c5154: 51                           	push	ecx
 11c5155: 50                           	push	eax
 11c5156: 8d 8e cc 02 00 00            	lea	ecx, [esi + 0x2cc]
 11c515c: e8 cf b5 24 ff               	call	0x410730
 11c5161: 8b 55 2c                     	mov	edx, dword ptr [ebp + 0x2c]
 11c5164: 85 d2                        	test	edx, edx
 11c5166: 74 1b                        	je	0x11c5183 <.text+0xd3>
 11c5168: 8b c2                        	mov	eax, edx
 11c516a: 8d 78 02                     	lea	edi, [eax + 0x2]
 11c516d: 8d 49 00                     	lea	ecx, [ecx]
 11c5170: 66 8b 08                     	mov	cx, word ptr [eax]
 11c5173: 83 c0 02                     	add	eax, 0x2
 11c5176: 66 85 c9                     	test	cx, cx
 11c5179: 75 f5                        	jne	0x11c5170 <.text+0xc0>
 11c517b: 2b c7                        	sub	eax, edi
 11c517d: d1 f8                        	sar	eax
 11c517f: 50                           	push	eax
 11c5180: 52                           	push	edx
 11c5181: eb 23                        	jmp	0x11c51a6 <.text+0xf6>
 11c5183: 68 d8 7a 56 01               	push	0x1567ad8
 11c5188: e8 63 ad fd ff               	call	0x119fef0
 11c518d: 8b c8                        	mov	ecx, eax
 11c518f: 83 c4 04                     	add	esp, 0x4
 11c5192: 8d 79 02                     	lea	edi, [ecx + 0x2]
 11c5195: 66 8b 11                     	mov	dx, word ptr [ecx]
 11c5198: 83 c1 02                     	add	ecx, 0x2
 11c519b: 66 85 d2                     	test	dx, dx
 11c519e: 75 f5                        	jne	0x11c5195 <.text+0xe5>
 11c51a0: 2b cf                        	sub	ecx, edi
 11c51a2: d1 f9                        	sar	ecx
 11c51a4: 51                           	push	ecx
 11c51a5: 50                           	push	eax
 11c51a6: 8d 8e ec 02 00 00            	lea	ecx, [esi + 0x2ec]
 11c51ac: e8 7f b5 24 ff               	call	0x410730
 11c51b1: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11c51b7: e8 04 ec fe ff               	call	0x11b3dc0
 11c51bc: 8b 8e b8 02 00 00            	mov	ecx, dword ptr [esi + 0x2b8]
 11c51c2: 89 46 38                     	mov	dword ptr [esi + 0x38], eax
 11c51c5: e8 06 ec fe ff               	call	0x11b3dd0
 11c51ca: 89 46 3c                     	mov	dword ptr [esi + 0x3c], eax
 11c51cd: 8b 45 1c                     	mov	eax, dword ptr [ebp + 0x1c]
 11c51d0: 50                           	push	eax
 11c51d1: 8b cb                        	mov	ecx, ebx
 11c51d3: e8 f8 f9 fe ff               	call	0x11b4bd0
 11c51d8: 8a 4d 20                     	mov	cl, byte ptr [ebp + 0x20]
 11c51db: 8b 55 24                     	mov	edx, dword ptr [ebp + 0x24]
 11c51de: 89 86 9c 03 00 00            	mov	dword ptr [esi + 0x39c], eax
 11c51e4: 5f                           	pop	edi
 11c51e5: b8 01 00 00 00               	mov	eax, 0x1
 11c51ea: 5b                           	pop	ebx
 11c51eb: 88 8e 94 03 00 00            	mov	byte ptr [esi + 0x394], cl
 11c51f1: 89 96 98 03 00 00            	mov	dword ptr [esi + 0x398], edx
 11c51f7: 88 46 04                     	mov	byte ptr [esi + 0x4], al
 11c51fa: 5e                           	pop	esi
 11c51fb: 5d                           	pop	ebp
 11c51fc: c2 28 00                     	ret	0x28
 11c51ff: cc                           	int3
 11c5200: 55                           	push	ebp
 11c5201: 8b ec                        	mov	ebp, esp
 11c5203: 56                           	push	esi
 11c5204: 8b f1                        	mov	esi, ecx
 11c5206: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11c520a: 75 0a                        	jne	0x11c5216 <.text+0x166>
 11c520c: b8 01 00 00 80               	mov	eax, 0x80000001
 11c5211: 5e                           	pop	esi
 11c5212: 5d                           	pop	ebp
 11c5213: c2 1c 00                     	ret	0x1c
 11c5216: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c5219: 57                           	push	edi
 11c521a: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
 11c521d: 83 f8 ff                     	cmp	eax, -0x1
 11c5220: 74 26                        	je	0x11c5248 <.text+0x198>
 11c5222: 50                           	push	eax
 11c5223: 8b cf                        	mov	ecx, edi
 11c5225: e8 a6 f9 fe ff               	call	0x11b4bd0
 11c522a: 8b c8                        	mov	ecx, eax
 11c522c: 89 86                        	<unknown>
 11c522e: b8                           	<unknown>
 11c522f: 02                           	<unknown>
