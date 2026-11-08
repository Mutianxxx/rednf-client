
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c3180 <.text>:
 11c3180: 53                           	push	ebx
 11c3181: 56                           	push	esi
 11c3182: 8b f1                        	mov	esi, ecx
 11c3184: 80 7e 0d 00                  	cmp	byte ptr [esi + 0xd], 0x0
 11c3188: 57                           	push	edi
 11c3189: 0f 84 35 03 00 00            	je	0x11c34c4 <.text+0x344>
 11c318f: e8 2c ae ff ff               	call	0x11bdfc0
 11c3194: bf 08 00 00 00               	mov	edi, 0x8
 11c3199: 84 c0                        	test	al, al
 11c319b: 74 3f                        	je	0x11c31dc <.text+0x5c>
 11c319d: 83 be e0 02 00 00 00         	cmp	dword ptr [esi + 0x2e0], 0x0
 11c31a4: 74 36                        	je	0x11c31dc <.text+0x5c>
 11c31a6: 39 be e4 02 00 00            	cmp	dword ptr [esi + 0x2e4], edi
 11c31ac: 72 08                        	jb	0x11c31b6 <.text+0x36>
 11c31ae: 8b 86 d0 02 00 00            	mov	eax, dword ptr [esi + 0x2d0]
 11c31b4: eb 06                        	jmp	0x11c31bc <.text+0x3c>
 11c31b6: 8d 86 d0 02 00 00            	lea	eax, [esi + 0x2d0]
 11c31bc: 6a 00                        	push	0x0
 11c31be: 6a 00                        	push	0x0
 11c31c0: 6a ff                        	push	-0x1
 11c31c2: 68 ff ff 00 00               	push	0xffff
 11c31c7: 6a 00                        	push	0x0
 11c31c9: 6a 00                        	push	0x0
 11c31cb: 6a 00                        	push	0x0
 11c31cd: 6a 00                        	push	0x0
 11c31cf: 50                           	push	eax
 11c31d0: e8 db 7e fd ff               	call	0x119b0b0
 11c31d5: 8b c8                        	mov	ecx, eax
 11c31d7: e8 b4 66 fd ff               	call	0x1199890
 11c31dc: 8b ce                        	mov	ecx, esi
 11c31de: e8 0d af ff ff               	call	0x11be0f0
 11c31e3: 8b ce                        	mov	ecx, esi
 11c31e5: 84 c0                        	test	al, al
 11c31e7: 0f 84 fe 00 00 00            	je	0x11c32eb <.text+0x16b>
 11c31ed: 6a 02                        	push	0x2
 11c31ef: e8 bc fb ff ff               	call	0x11c2db0
 11c31f4: 80 be 0d 03 00 00 00         	cmp	byte ptr [esi + 0x30d], 0x0
 11c31fb: 75 07                        	jne	0x11c3204 <.text+0x84>
 11c31fd: c6 86 0d 03 00 00 01         	mov	byte ptr [esi + 0x30d], 0x1
 11c3204: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c320a: 85 c9                        	test	ecx, ecx
 11c320c: 0f 84 ab 03 00 00            	je	0x11c35bd <.text+0x43d>
 11c3212: 39 be 2c 03 00 00            	cmp	dword ptr [esi + 0x32c], edi
 11c3218: 8d be 18 03 00 00            	lea	edi, [esi + 0x318]
 11c321e: 72 04                        	jb	0x11c3224 <.text+0xa4>
 11c3220: 8b 07                        	mov	eax, dword ptr [edi]
 11c3222: eb 02                        	jmp	0x11c3226 <.text+0xa6>
 11c3224: 8b c7                        	mov	eax, edi
 11c3226: 8b 11                        	mov	edx, dword ptr [ecx]
 11c3228: 6a ff                        	push	-0x1
 11c322a: 50                           	push	eax
 11c322b: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c322e: ff d0                        	call	eax
 11c3230: 80 be 44 03 00 00 00         	cmp	byte ptr [esi + 0x344], 0x0
 11c3237: 8b d8                        	mov	ebx, eax
 11c3239: 74 61                        	je	0x11c329c <.text+0x11c>
 11c323b: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c3242: 72 04                        	jb	0x11c3248 <.text+0xc8>
 11c3244: 8b 07                        	mov	eax, dword ptr [edi]
 11c3246: eb 02                        	jmp	0x11c324a <.text+0xca>
 11c3248: 8b c7                        	mov	eax, edi
 11c324a: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c3250: 8b 96 48 03 00 00            	mov	edx, dword ptr [esi + 0x348]
 11c3256: 50                           	push	eax
 11c3257: 8b 01                        	mov	eax, dword ptr [ecx]
 11c3259: 6a 00                        	push	0x0
 11c325b: 6a 00                        	push	0x0
 11c325d: 52                           	push	edx
 11c325e: 8b 50 18                     	mov	edx, dword ptr [eax + 0x18]
 11c3261: ff d2                        	call	edx
 11c3263: 8b 4e 3c                     	mov	ecx, dword ptr [esi + 0x3c]
 11c3266: 2b c8                        	sub	ecx, eax
 11c3268: 8b c1                        	mov	eax, ecx
 11c326a: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c326d: 99                           	cdq
 11c326e: 2b c2                        	sub	eax, edx
 11c3270: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c3273: d1 f8                        	sar	eax
 11c3275: 8d 44 10 02                  	lea	eax, [eax + edx + 0x2]
 11c3279: 50                           	push	eax
 11c327a: 8b 46 38                     	mov	eax, dword ptr [esi + 0x38]
 11c327d: 2b c3                        	sub	eax, ebx
 11c327f: 99                           	cdq
 11c3280: 2b c2                        	sub	eax, edx
 11c3282: d1 f8                        	sar	eax
 11c3284: 8d 54 08 02                  	lea	edx, [eax + ecx + 0x2]
 11c3288: 52                           	push	edx
 11c3289: 8b ce                        	mov	ecx, esi
 11c328b: e8 80 b1 ff ff               	call	0x11be410
 11c3290: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c3296: 50                           	push	eax
 11c3297: e8 d4 59 00 00               	call	0x11c8c70 <.text+0x5af0>
 11c329c: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c32a3: 72 02                        	jb	0x11c32a7 <.text+0x127>
 11c32a5: 8b 3f                        	mov	edi, dword ptr [edi]
 11c32a7: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c32ad: 8b 86 3c 03 00 00            	mov	eax, dword ptr [esi + 0x33c]
 11c32b3: 8b 11                        	mov	edx, dword ptr [ecx]
 11c32b5: 57                           	push	edi
 11c32b6: 6a 00                        	push	0x0
 11c32b8: 6a 00                        	push	0x0
 11c32ba: 50                           	push	eax
 11c32bb: 8b 42 18                     	mov	eax, dword ptr [edx + 0x18]
 11c32be: ff d0                        	call	eax
 11c32c0: 8b 4e 3c                     	mov	ecx, dword ptr [esi + 0x3c]
 11c32c3: 2b c8                        	sub	ecx, eax
 11c32c5: 8b c1                        	mov	eax, ecx
 11c32c7: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c32ca: 99                           	cdq
 11c32cb: 2b c2                        	sub	eax, edx
 11c32cd: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c32d0: d1 f8                        	sar	eax
 11c32d2: 8d 44 10 01                  	lea	eax, [eax + edx + 0x1]
 11c32d6: 50                           	push	eax
 11c32d7: 8b 46 38                     	mov	eax, dword ptr [esi + 0x38]
 11c32da: 2b c3                        	sub	eax, ebx
 11c32dc: 99                           	cdq
 11c32dd: 2b c2                        	sub	eax, edx
 11c32df: d1 f8                        	sar	eax
 11c32e1: 8d 54 08 02                  	lea	edx, [eax + ecx + 0x2]
 11c32e5: 52                           	push	edx
 11c32e6: e9 bf 02 00 00               	jmp	0x11c35aa <.text+0x42a>
 11c32eb: e8 30 ad ff ff               	call	0x11be020
 11c32f0: 84 c0                        	test	al, al
 11c32f2: 0f 85 cf 00 00 00            	jne	0x11c33c7 <.text+0x247>
 11c32f8: 8b ce                        	mov	ecx, esi
 11c32fa: e8 b1 af ff ff               	call	0x11be2b0
 11c32ff: 84 c0                        	test	al, al
 11c3301: 0f 85 c0 00 00 00            	jne	0x11c33c7 <.text+0x247>
 11c3307: 6a 00                        	push	0x0
 11c3309: 8b ce                        	mov	ecx, esi
 11c330b: e8 a0 fa ff ff               	call	0x11c2db0
 11c3310: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c3316: 66 c7 86 0c 03 00 00 00 00   	mov	word ptr [esi + 0x30c], 0x0
 11c331f: 85 c9                        	test	ecx, ecx
 11c3321: 0f 84 96 02 00 00            	je	0x11c35bd <.text+0x43d>
 11c3327: 39 be 2c 03 00 00            	cmp	dword ptr [esi + 0x32c], edi
 11c332d: 8d be 18 03 00 00            	lea	edi, [esi + 0x318]
 11c3333: 72 04                        	jb	0x11c3339 <.text+0x1b9>
 11c3335: 8b 07                        	mov	eax, dword ptr [edi]
 11c3337: eb 02                        	jmp	0x11c333b <.text+0x1bb>
 11c3339: 8b c7                        	mov	eax, edi
 11c333b: 8b 11                        	mov	edx, dword ptr [ecx]
 11c333d: 6a ff                        	push	-0x1
 11c333f: 50                           	push	eax
 11c3340: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c3343: ff d0                        	call	eax
 11c3345: 80 be 44 03 00 00 00         	cmp	byte ptr [esi + 0x344], 0x0
 11c334c: 8b d8                        	mov	ebx, eax
 11c334e: 74 61                        	je	0x11c33b1 <.text+0x231>
 11c3350: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c3357: 72 04                        	jb	0x11c335d <.text+0x1dd>
 11c3359: 8b 07                        	mov	eax, dword ptr [edi]
 11c335b: eb 02                        	jmp	0x11c335f <.text+0x1df>
 11c335d: 8b c7                        	mov	eax, edi
 11c335f: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c3365: 8b 96 48 03 00 00            	mov	edx, dword ptr [esi + 0x348]
 11c336b: 50                           	push	eax
 11c336c: 8b 01                        	mov	eax, dword ptr [ecx]
 11c336e: 6a 00                        	push	0x0
 11c3370: 6a 00                        	push	0x0
 11c3372: 52                           	push	edx
 11c3373: 8b 50 18                     	mov	edx, dword ptr [eax + 0x18]
 11c3376: ff d2                        	call	edx
 11c3378: 8b 4e 3c                     	mov	ecx, dword ptr [esi + 0x3c]
 11c337b: 2b c8                        	sub	ecx, eax
 11c337d: 8b c1                        	mov	eax, ecx
 11c337f: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c3382: 99                           	cdq
 11c3383: 2b c2                        	sub	eax, edx
 11c3385: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c3388: d1 f8                        	sar	eax
 11c338a: 8d 44 10 01                  	lea	eax, [eax + edx + 0x1]
 11c338e: 50                           	push	eax
 11c338f: 8b 46 38                     	mov	eax, dword ptr [esi + 0x38]
 11c3392: 2b c3                        	sub	eax, ebx
 11c3394: 99                           	cdq
 11c3395: 2b c2                        	sub	eax, edx
 11c3397: d1 f8                        	sar	eax
 11c3399: 8d 54 08 01                  	lea	edx, [eax + ecx + 0x1]
 11c339d: 52                           	push	edx
 11c339e: 8b ce                        	mov	ecx, esi
 11c33a0: e8 6b b0 ff ff               	call	0x11be410
 11c33a5: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c33ab: 50                           	push	eax
 11c33ac: e8 bf 58 00 00               	call	0x11c8c70 <.text+0x5af0>
 11c33b1: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c33b8: 72 02                        	jb	0x11c33bc <.text+0x23c>
 11c33ba: 8b 3f                        	mov	edi, dword ptr [edi]
 11c33bc: 8b 86 34 03 00 00            	mov	eax, dword ptr [esi + 0x334]
 11c33c2: e9 ae 01 00 00               	jmp	0x11c3575 <.text+0x3f5>
 11c33c7: 6a 01                        	push	0x1
 11c33c9: 8b ce                        	mov	ecx, esi
 11c33cb: e8 e0 f9 ff ff               	call	0x11c2db0
 11c33d0: 80 be 0c 03 00 00 00         	cmp	byte ptr [esi + 0x30c], 0x0
 11c33d7: 75 3d                        	jne	0x11c3416 <.text+0x296>
 11c33d9: 39 be 04 03 00 00            	cmp	dword ptr [esi + 0x304], edi
 11c33df: 72 08                        	jb	0x11c33e9 <.text+0x269>
 11c33e1: 8b 86 f0 02 00 00            	mov	eax, dword ptr [esi + 0x2f0]
 11c33e7: eb 06                        	jmp	0x11c33ef <.text+0x26f>
 11c33e9: 8d 86 f0 02 00 00            	lea	eax, [esi + 0x2f0]
 11c33ef: 6a 00                        	push	0x0
 11c33f1: 6a 00                        	push	0x0
 11c33f3: 6a ff                        	push	-0x1
 11c33f5: 68 ff ff 00 00               	push	0xffff
 11c33fa: 6a 00                        	push	0x0
 11c33fc: 6a 00                        	push	0x0
 11c33fe: 6a 00                        	push	0x0
 11c3400: 6a 00                        	push	0x0
 11c3402: 50                           	push	eax
 11c3403: e8 a8 7c fd ff               	call	0x119b0b0
 11c3408: 8b c8                        	mov	ecx, eax
 11c340a: e8 81 64 fd ff               	call	0x1199890
 11c340f: c6 86 0c 03 00 00 01         	mov	byte ptr [esi + 0x30c], 0x1
 11c3416: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c341c: 85 c9                        	test	ecx, ecx
 11c341e: 0f 84 99 01 00 00            	je	0x11c35bd <.text+0x43d>
 11c3424: 39 be 2c 03 00 00            	cmp	dword ptr [esi + 0x32c], edi
 11c342a: 8d be 18 03 00 00            	lea	edi, [esi + 0x318]
 11c3430: 72 04                        	jb	0x11c3436 <.text+0x2b6>
 11c3432: 8b 07                        	mov	eax, dword ptr [edi]
 11c3434: eb 02                        	jmp	0x11c3438 <.text+0x2b8>
 11c3436: 8b c7                        	mov	eax, edi
 11c3438: 8b 11                        	mov	edx, dword ptr [ecx]
 11c343a: 6a ff                        	push	-0x1
 11c343c: 50                           	push	eax
 11c343d: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c3440: ff d0                        	call	eax
 11c3442: 80 be 44 03 00 00 00         	cmp	byte ptr [esi + 0x344], 0x0
 11c3449: 8b d8                        	mov	ebx, eax
 11c344b: 74 61                        	je	0x11c34ae <.text+0x32e>
 11c344d: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c3454: 72 04                        	jb	0x11c345a <.text+0x2da>
 11c3456: 8b 07                        	mov	eax, dword ptr [edi]
 11c3458: eb 02                        	jmp	0x11c345c <.text+0x2dc>
 11c345a: 8b c7                        	mov	eax, edi
 11c345c: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c3462: 8b 96 48 03 00 00            	mov	edx, dword ptr [esi + 0x348]
 11c3468: 50                           	push	eax
 11c3469: 8b 01                        	mov	eax, dword ptr [ecx]
 11c346b: 6a 00                        	push	0x0
 11c346d: 6a 00                        	push	0x0
 11c346f: 52                           	push	edx
 11c3470: 8b 50 18                     	mov	edx, dword ptr [eax + 0x18]
 11c3473: ff d2                        	call	edx
 11c3475: 8b 4e 3c                     	mov	ecx, dword ptr [esi + 0x3c]
 11c3478: 2b c8                        	sub	ecx, eax
 11c347a: 8b c1                        	mov	eax, ecx
 11c347c: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c347f: 99                           	cdq
 11c3480: 2b c2                        	sub	eax, edx
 11c3482: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c3485: d1 f8                        	sar	eax
 11c3487: 8d 44 10 01                  	lea	eax, [eax + edx + 0x1]
 11c348b: 50                           	push	eax
 11c348c: 8b 46 38                     	mov	eax, dword ptr [esi + 0x38]
 11c348f: 2b c3                        	sub	eax, ebx
 11c3491: 99                           	cdq
 11c3492: 2b c2                        	sub	eax, edx
 11c3494: d1 f8                        	sar	eax
 11c3496: 8d 54 08 01                  	lea	edx, [eax + ecx + 0x1]
 11c349a: 52                           	push	edx
 11c349b: 8b ce                        	mov	ecx, esi
 11c349d: e8 6e af ff ff               	call	0x11be410
 11c34a2: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c34a8: 50                           	push	eax
 11c34a9: e8 c2 57 00 00               	call	0x11c8c70 <.text+0x5af0>
 11c34ae: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c34b5: 72 02                        	jb	0x11c34b9 <.text+0x339>
 11c34b7: 8b 3f                        	mov	edi, dword ptr [edi]
 11c34b9: 8b 86 38 03 00 00            	mov	eax, dword ptr [esi + 0x338]
 11c34bf: e9 b1 00 00 00               	jmp	0x11c3575 <.text+0x3f5>
 11c34c4: 6a 03                        	push	0x3
 11c34c6: e8 e5 f8 ff ff               	call	0x11c2db0
 11c34cb: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c34d1: 85 c9                        	test	ecx, ecx
 11c34d3: 0f 84 e4 00 00 00            	je	0x11c35bd <.text+0x43d>
 11c34d9: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c34e0: 8d be 18 03 00 00            	lea	edi, [esi + 0x318]
 11c34e6: 72 04                        	jb	0x11c34ec <.text+0x36c>
 11c34e8: 8b 07                        	mov	eax, dword ptr [edi]
 11c34ea: eb 02                        	jmp	0x11c34ee <.text+0x36e>
 11c34ec: 8b c7                        	mov	eax, edi
 11c34ee: 8b 11                        	mov	edx, dword ptr [ecx]
 11c34f0: 6a ff                        	push	-0x1
 11c34f2: 50                           	push	eax
 11c34f3: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c34f6: ff d0                        	call	eax
 11c34f8: 80 be 44 03 00 00 00         	cmp	byte ptr [esi + 0x344], 0x0
 11c34ff: 8b d8                        	mov	ebx, eax
 11c3501: 74 61                        	je	0x11c3564 <.text+0x3e4>
 11c3503: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c350a: 72 04                        	jb	0x11c3510 <.text+0x390>
 11c350c: 8b 07                        	mov	eax, dword ptr [edi]
 11c350e: eb 02                        	jmp	0x11c3512 <.text+0x392>
 11c3510: 8b c7                        	mov	eax, edi
 11c3512: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c3518: 8b 96 48 03 00 00            	mov	edx, dword ptr [esi + 0x348]
 11c351e: 50                           	push	eax
 11c351f: 8b 01                        	mov	eax, dword ptr [ecx]
 11c3521: 6a 00                        	push	0x0
 11c3523: 6a 00                        	push	0x0
 11c3525: 52                           	push	edx
 11c3526: 8b 50 18                     	mov	edx, dword ptr [eax + 0x18]
 11c3529: ff d2                        	call	edx
 11c352b: 8b 4e 3c                     	mov	ecx, dword ptr [esi + 0x3c]
 11c352e: 2b c8                        	sub	ecx, eax
 11c3530: 8b c1                        	mov	eax, ecx
 11c3532: 8b 4e 14                     	mov	ecx, dword ptr [esi + 0x14]
 11c3535: 99                           	cdq
 11c3536: 2b c2                        	sub	eax, edx
 11c3538: 8b 56 18                     	mov	edx, dword ptr [esi + 0x18]
 11c353b: d1 f8                        	sar	eax
 11c353d: 8d 44 10 01                  	lea	eax, [eax + edx + 0x1]
 11c3541: 50                           	push	eax
 11c3542: 8b 46 38                     	mov	eax, dword ptr [esi + 0x38]
 11c3545: 2b c3                        	sub	eax, ebx
 11c3547: 99                           	cdq
 11c3548: 2b c2                        	sub	eax, edx
 11c354a: d1 f8                        	sar	eax
 11c354c: 8d 54 08 01                  	lea	edx, [eax + ecx + 0x1]
 11c3550: 52                           	push	edx
 11c3551: 8b ce                        	mov	ecx, esi
 11c3553: e8 b8 ae ff ff               	call	0x11be410
 11c3558: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c355e: 50                           	push	eax
 11c355f: e8 0c 57 00 00               	call	0x11c8c70 <.text+0x5af0>
 11c3564: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c356b: 72 02                        	jb	0x11c356f <.text+0x3ef>
 11c356d: 8b 3f                        	mov	edi, dword ptr [edi]
 11c356f: 8b 86 40 03 00 00            	mov	eax, dword ptr [esi + 0x340]
 11c3575: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c357b: 8b 11                        	mov	edx, dword ptr [ecx]
 11c357d: 57                           	push	edi
 11c357e: 6a 00                        	push	0x0
 11c3580: 6a 00                        	push	0x0
 11c3582: 50                           	push	eax
 11c3583: 8b 42 18                     	mov	eax, dword ptr [edx + 0x18]
 11c3586: ff d0                        	call	eax
 11c3588: 8b 4e 3c                     	mov	ecx, dword ptr [esi + 0x3c]
 11c358b: 2b c8                        	sub	ecx, eax
 11c358d: 8b c1                        	mov	eax, ecx
 11c358f: 99                           	cdq
 11c3590: 2b c2                        	sub	eax, edx
 11c3592: d1 f8                        	sar	eax
 11c3594: 03 46 18                     	add	eax, dword ptr [esi + 0x18]
 11c3597: 50                           	push	eax
 11c3598: 8b 46 38                     	mov	eax, dword ptr [esi + 0x38]
 11c359b: 2b c3                        	sub	eax, ebx
 11c359d: 99                           	cdq
 11c359e: 2b c2                        	sub	eax, edx
 11c35a0: 8b 56 14                     	mov	edx, dword ptr [esi + 0x14]
 11c35a3: d1 f8                        	sar	eax
 11c35a5: 8d 44 10 01                  	lea	eax, [eax + edx + 0x1]
 11c35a9: 50                           	push	eax
 11c35aa: 8b ce                        	mov	ecx, esi
 11c35ac: e8 5f ae ff ff               	call	0x11be410
 11c35b1: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c35b7: 50                           	push	eax
 11c35b8: e8 b3 56 00 00               	call	0x11c8c70 <.text+0x5af0>
 11c35bd: 5f                           	pop	edi
 11c35be: 5e                           	pop	esi
 11c35bf: 5b                           	pop	ebx
 11c35c0: c3                           	ret
 11c35c1: cc                           	int3
 11c35c2: cc                           	int3
 11c35c3: cc                           	int3
 11c35c4: cc                           	int3
 11c35c5: cc                           	int3
 11c35c6: cc                           	int3
 11c35c7: cc                           	int3
 11c35c8: cc                           	int3
 11c35c9: cc                           	int3
 11c35ca: cc                           	int3
 11c35cb: cc                           	int3
 11c35cc: cc                           	int3
 11c35cd: cc                           	int3
 11c35ce: cc                           	int3
 11c35cf: cc                           	int3
