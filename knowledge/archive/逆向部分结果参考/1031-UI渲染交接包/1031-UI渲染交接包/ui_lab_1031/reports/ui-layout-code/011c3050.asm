
<stdin>:	file format elf32-i386

Disassembly of section .text:

011c3050 <.text>:
 11c3050: 55                           	push	ebp
 11c3051: 8b ec                        	mov	ebp, esp
 11c3053: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11c3056: 89 81 5c 03 00 00            	mov	dword ptr [ecx + 0x35c], eax
 11c305c: 89 81 60 03 00 00            	mov	dword ptr [ecx + 0x360], eax
 11c3062: 89 81 64 03 00 00            	mov	dword ptr [ecx + 0x364], eax
 11c3068: 89 81 68 03 00 00            	mov	dword ptr [ecx + 0x368], eax
 11c306e: 5d                           	pop	ebp
 11c306f: c2 04 00                     	ret	0x4
 11c3072: cc                           	int3
 11c3073: cc                           	int3
 11c3074: cc                           	int3
 11c3075: cc                           	int3
 11c3076: cc                           	int3
 11c3077: cc                           	int3
 11c3078: cc                           	int3
 11c3079: cc                           	int3
 11c307a: cc                           	int3
 11c307b: cc                           	int3
 11c307c: cc                           	int3
 11c307d: cc                           	int3
 11c307e: cc                           	int3
 11c307f: cc                           	int3
 11c3080: 55                           	push	ebp
 11c3081: 8b ec                        	mov	ebp, esp
 11c3083: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c3086: 83 f8 03                     	cmp	eax, 0x3
 11c3089: 77 0a                        	ja	0x11c3095 <.text+0x45>
 11c308b: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11c308e: 89 94 81 5c 03 00 00         	mov	dword ptr [ecx + 4*eax + 0x35c], edx
 11c3095: 5d                           	pop	ebp
 11c3096: c2 08 00                     	ret	0x8
 11c3099: cc                           	int3
 11c309a: cc                           	int3
 11c309b: cc                           	int3
 11c309c: cc                           	int3
 11c309d: cc                           	int3
 11c309e: cc                           	int3
 11c309f: cc                           	int3
 11c30a0: 55                           	push	ebp
 11c30a1: 8b ec                        	mov	ebp, esp
 11c30a3: 8b 45 10                     	mov	eax, dword ptr [ebp + 0x10]
 11c30a6: 83 f8 03                     	cmp	eax, 0x3
 11c30a9: 77 14                        	ja	0x11c30bf <.text+0x6f>
 11c30ab: 8b 55 08                     	mov	edx, dword ptr [ebp + 0x8]
 11c30ae: 89 94 81 6c 03 00 00         	mov	dword ptr [ecx + 4*eax + 0x36c], edx
 11c30b5: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
 11c30b8: 89 94 81 7c 03 00 00         	mov	dword ptr [ecx + 4*eax + 0x37c], edx
 11c30bf: 5d                           	pop	ebp
 11c30c0: c2 0c 00                     	ret	0xc
 11c30c3: cc                           	int3
 11c30c4: cc                           	int3
 11c30c5: cc                           	int3
 11c30c6: cc                           	int3
 11c30c7: cc                           	int3
 11c30c8: cc                           	int3
 11c30c9: cc                           	int3
 11c30ca: cc                           	int3
 11c30cb: cc                           	int3
 11c30cc: cc                           	int3
 11c30cd: cc                           	int3
 11c30ce: cc                           	int3
 11c30cf: cc                           	int3
 11c30d0: 55                           	push	ebp
 11c30d1: 8b ec                        	mov	ebp, esp
 11c30d3: f3 0f 10 45 08               	movss	xmm0, dword ptr [ebp + 0x8]
 11c30d8: f3 0f 11 81 8c 03 00 00      	movss	dword ptr [ecx + 0x38c], xmm0
 11c30e0: f3 0f 10 45 0c               	movss	xmm0, dword ptr [ebp + 0xc]
 11c30e5: f3 0f 11 81 90 03 00 00      	movss	dword ptr [ecx + 0x390], xmm0
 11c30ed: 5d                           	pop	ebp
 11c30ee: c2 08 00                     	ret	0x8
 11c30f1: cc                           	int3
 11c30f2: cc                           	int3
 11c30f3: cc                           	int3
 11c30f4: cc                           	int3
 11c30f5: cc                           	int3
 11c30f6: cc                           	int3
 11c30f7: cc                           	int3
 11c30f8: cc                           	int3
 11c30f9: cc                           	int3
 11c30fa: cc                           	int3
 11c30fb: cc                           	int3
 11c30fc: cc                           	int3
 11c30fd: cc                           	int3
 11c30fe: cc                           	int3
 11c30ff: cc                           	int3
 11c3100: 55                           	push	ebp
 11c3101: 8b ec                        	mov	ebp, esp
 11c3103: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
 11c3106: 8b 84 81 34 03 00 00         	mov	eax, dword ptr [ecx + 4*eax + 0x334]
 11c310d: 5d                           	pop	ebp
 11c310e: c2 04 00                     	ret	0x4
 11c3111: cc                           	int3
 11c3112: cc                           	int3
 11c3113: cc                           	int3
 11c3114: cc                           	int3
 11c3115: cc                           	int3
 11c3116: cc                           	int3
 11c3117: cc                           	int3
 11c3118: cc                           	int3
 11c3119: cc                           	int3
 11c311a: cc                           	int3
 11c311b: cc                           	int3
 11c311c: cc                           	int3
 11c311d: cc                           	int3
 11c311e: cc                           	int3
 11c311f: cc                           	int3
 11c3120: 55                           	push	ebp
 11c3121: 8b ec                        	mov	ebp, esp
 11c3123: 8a 45 08                     	mov	al, byte ptr [ebp + 0x8]
 11c3126: 88 81 58 03 00 00            	mov	byte ptr [ecx + 0x358], al
 11c312c: 5d                           	pop	ebp
 11c312d: c2 04 00                     	ret	0x4
 11c3130: 55                           	push	ebp
 11c3131: 8b ec                        	mov	ebp, esp
 11c3133: 56                           	push	esi
 11c3134: 8b f1                        	mov	esi, ecx
 11c3136: 80 7e 04 00                  	cmp	byte ptr [esi + 0x4], 0x0
 11c313a: 74 39                        	je	0x11c3175 <.text+0x125>
 11c313c: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11c313f: 83 f8 ff                     	cmp	eax, -0x1
 11c3142: 74 31                        	je	0x11c3175 <.text+0x125>
 11c3144: 8b 4d 08                     	mov	ecx, dword ptr [ebp + 0x8]
 11c3147: 50                           	push	eax
 11c3148: e8 83 1a ff ff               	call	0x11b4bd0
 11c314d: 8b c8                        	mov	ecx, eax
 11c314f: 89 86 9c 03 00 00            	mov	dword ptr [esi + 0x39c], eax
 11c3155: e8 66 0c ff ff               	call	0x11b3dc0
 11c315a: 8b 8e 9c 03 00 00            	mov	ecx, dword ptr [esi + 0x39c]
 11c3160: 89 46 38                     	mov	dword ptr [esi + 0x38], eax
 11c3163: e8 68 0c ff ff               	call	0x11b3dd0
 11c3168: 89 46 3c                     	mov	dword ptr [esi + 0x3c], eax
 11c316b: b8 01 00 00 00               	mov	eax, 0x1
 11c3170: 5e                           	pop	esi
 11c3171: 5d                           	pop	ebp
 11c3172: c2 08 00                     	ret	0x8
 11c3175: b8 01 00 00 80               	mov	eax, 0x80000001
 11c317a: 5e                           	pop	esi
 11c317b: 5d                           	pop	ebp
 11c317c: c2 08 00                     	ret	0x8
 11c317f: cc                           	int3
 11c3180: 53                           	push	ebx
 11c3181: 56                           	push	esi
 11c3182: 8b f1                        	mov	esi, ecx
 11c3184: 80 7e 0d 00                  	cmp	byte ptr [esi + 0xd], 0x0
 11c3188: 57                           	push	edi
 11c3189: 0f 84 35 03 00 00            	je	0x11c34c4 <.text+0x474>
 11c318f: e8 2c ae ff ff               	call	0x11bdfc0
 11c3194: bf 08 00 00 00               	mov	edi, 0x8
 11c3199: 84 c0                        	test	al, al
 11c319b: 74 3f                        	je	0x11c31dc <.text+0x18c>
 11c319d: 83 be e0 02 00 00 00         	cmp	dword ptr [esi + 0x2e0], 0x0
 11c31a4: 74 36                        	je	0x11c31dc <.text+0x18c>
 11c31a6: 39 be e4 02 00 00            	cmp	dword ptr [esi + 0x2e4], edi
 11c31ac: 72 08                        	jb	0x11c31b6 <.text+0x166>
 11c31ae: 8b 86 d0 02 00 00            	mov	eax, dword ptr [esi + 0x2d0]
 11c31b4: eb 06                        	jmp	0x11c31bc <.text+0x16c>
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
 11c31e7: 0f 84 fe 00 00 00            	je	0x11c32eb <.text+0x29b>
 11c31ed: 6a 02                        	push	0x2
 11c31ef: e8 bc fb ff ff               	call	0x11c2db0
 11c31f4: 80 be 0d 03 00 00 00         	cmp	byte ptr [esi + 0x30d], 0x0
 11c31fb: 75 07                        	jne	0x11c3204 <.text+0x1b4>
 11c31fd: c6 86 0d 03 00 00 01         	mov	byte ptr [esi + 0x30d], 0x1
 11c3204: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c320a: 85 c9                        	test	ecx, ecx
 11c320c: 0f 84 ab 03 00 00            	je	0x11c35bd <.text+0x56d>
 11c3212: 39 be 2c 03 00 00            	cmp	dword ptr [esi + 0x32c], edi
 11c3218: 8d be 18 03 00 00            	lea	edi, [esi + 0x318]
 11c321e: 72 04                        	jb	0x11c3224 <.text+0x1d4>
 11c3220: 8b 07                        	mov	eax, dword ptr [edi]
 11c3222: eb 02                        	jmp	0x11c3226 <.text+0x1d6>
 11c3224: 8b c7                        	mov	eax, edi
 11c3226: 8b 11                        	mov	edx, dword ptr [ecx]
 11c3228: 6a ff                        	push	-0x1
 11c322a: 50                           	push	eax
 11c322b: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c322e: ff d0                        	call	eax
 11c3230: 80 be 44 03 00 00 00         	cmp	byte ptr [esi + 0x344], 0x0
 11c3237: 8b d8                        	mov	ebx, eax
 11c3239: 74 61                        	je	0x11c329c <.text+0x24c>
 11c323b: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c3242: 72 04                        	jb	0x11c3248 <.text+0x1f8>
 11c3244: 8b 07                        	mov	eax, dword ptr [edi]
 11c3246: eb 02                        	jmp	0x11c324a <.text+0x1fa>
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
 11c3297: e8 d4 59 00 00               	call	0x11c8c70 <.text+0x5c20>
 11c329c: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c32a3: 72 02                        	jb	0x11c32a7 <.text+0x257>
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
 11c32e6: e9 bf 02 00 00               	jmp	0x11c35aa <.text+0x55a>
 11c32eb: e8 30 ad ff ff               	call	0x11be020
 11c32f0: 84 c0                        	test	al, al
 11c32f2: 0f 85 cf 00 00 00            	jne	0x11c33c7 <.text+0x377>
 11c32f8: 8b ce                        	mov	ecx, esi
 11c32fa: e8 b1 af ff ff               	call	0x11be2b0
 11c32ff: 84 c0                        	test	al, al
 11c3301: 0f 85 c0 00 00 00            	jne	0x11c33c7 <.text+0x377>
 11c3307: 6a 00                        	push	0x0
 11c3309: 8b ce                        	mov	ecx, esi
 11c330b: e8 a0 fa ff ff               	call	0x11c2db0
 11c3310: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c3316: 66 c7 86 0c 03 00 00 00 00   	mov	word ptr [esi + 0x30c], 0x0
 11c331f: 85 c9                        	test	ecx, ecx
 11c3321: 0f 84 96 02 00 00            	je	0x11c35bd <.text+0x56d>
 11c3327: 39 be 2c 03 00 00            	cmp	dword ptr [esi + 0x32c], edi
 11c332d: 8d be 18 03 00 00            	lea	edi, [esi + 0x318]
 11c3333: 72 04                        	jb	0x11c3339 <.text+0x2e9>
 11c3335: 8b 07                        	mov	eax, dword ptr [edi]
 11c3337: eb 02                        	jmp	0x11c333b <.text+0x2eb>
 11c3339: 8b c7                        	mov	eax, edi
 11c333b: 8b 11                        	mov	edx, dword ptr [ecx]
 11c333d: 6a ff                        	push	-0x1
 11c333f: 50                           	push	eax
 11c3340: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c3343: ff d0                        	call	eax
 11c3345: 80 be 44 03 00 00 00         	cmp	byte ptr [esi + 0x344], 0x0
 11c334c: 8b d8                        	mov	ebx, eax
 11c334e: 74 61                        	je	0x11c33b1 <.text+0x361>
 11c3350: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c3357: 72 04                        	jb	0x11c335d <.text+0x30d>
 11c3359: 8b 07                        	mov	eax, dword ptr [edi]
 11c335b: eb 02                        	jmp	0x11c335f <.text+0x30f>
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
 11c33ac: e8 bf 58 00 00               	call	0x11c8c70 <.text+0x5c20>
 11c33b1: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c33b8: 72 02                        	jb	0x11c33bc <.text+0x36c>
 11c33ba: 8b 3f                        	mov	edi, dword ptr [edi]
 11c33bc: 8b 86 34 03 00 00            	mov	eax, dword ptr [esi + 0x334]
 11c33c2: e9 ae 01 00 00               	jmp	0x11c3575 <.text+0x525>
 11c33c7: 6a 01                        	push	0x1
 11c33c9: 8b ce                        	mov	ecx, esi
 11c33cb: e8 e0 f9 ff ff               	call	0x11c2db0
 11c33d0: 80 be 0c 03 00 00 00         	cmp	byte ptr [esi + 0x30c], 0x0
 11c33d7: 75 3d                        	jne	0x11c3416 <.text+0x3c6>
 11c33d9: 39 be 04 03 00 00            	cmp	dword ptr [esi + 0x304], edi
 11c33df: 72 08                        	jb	0x11c33e9 <.text+0x399>
 11c33e1: 8b 86 f0 02 00 00            	mov	eax, dword ptr [esi + 0x2f0]
 11c33e7: eb 06                        	jmp	0x11c33ef <.text+0x39f>
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
 11c341e: 0f 84 99 01 00 00            	je	0x11c35bd <.text+0x56d>
 11c3424: 39 be 2c 03 00 00            	cmp	dword ptr [esi + 0x32c], edi
 11c342a: 8d be 18 03 00 00            	lea	edi, [esi + 0x318]
 11c3430: 72 04                        	jb	0x11c3436 <.text+0x3e6>
 11c3432: 8b 07                        	mov	eax, dword ptr [edi]
 11c3434: eb 02                        	jmp	0x11c3438 <.text+0x3e8>
 11c3436: 8b c7                        	mov	eax, edi
 11c3438: 8b 11                        	mov	edx, dword ptr [ecx]
 11c343a: 6a ff                        	push	-0x1
 11c343c: 50                           	push	eax
 11c343d: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c3440: ff d0                        	call	eax
 11c3442: 80 be 44 03 00 00 00         	cmp	byte ptr [esi + 0x344], 0x0
 11c3449: 8b d8                        	mov	ebx, eax
 11c344b: 74 61                        	je	0x11c34ae <.text+0x45e>
 11c344d: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c3454: 72 04                        	jb	0x11c345a <.text+0x40a>
 11c3456: 8b 07                        	mov	eax, dword ptr [edi]
 11c3458: eb 02                        	jmp	0x11c345c <.text+0x40c>
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
 11c34a9: e8 c2 57 00 00               	call	0x11c8c70 <.text+0x5c20>
 11c34ae: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c34b5: 72 02                        	jb	0x11c34b9 <.text+0x469>
 11c34b7: 8b 3f                        	mov	edi, dword ptr [edi]
 11c34b9: 8b 86 38 03 00 00            	mov	eax, dword ptr [esi + 0x338]
 11c34bf: e9 b1 00 00 00               	jmp	0x11c3575 <.text+0x525>
 11c34c4: 6a 03                        	push	0x3
 11c34c6: e8 e5 f8 ff ff               	call	0x11c2db0
 11c34cb: 8b 8e 10 03 00 00            	mov	ecx, dword ptr [esi + 0x310]
 11c34d1: 85 c9                        	test	ecx, ecx
 11c34d3: 0f 84 e4 00 00 00            	je	0x11c35bd <.text+0x56d>
 11c34d9: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c34e0: 8d be 18 03 00 00            	lea	edi, [esi + 0x318]
 11c34e6: 72 04                        	jb	0x11c34ec <.text+0x49c>
 11c34e8: 8b 07                        	mov	eax, dword ptr [edi]
 11c34ea: eb 02                        	jmp	0x11c34ee <.text+0x49e>
 11c34ec: 8b c7                        	mov	eax, edi
 11c34ee: 8b 11                        	mov	edx, dword ptr [ecx]
 11c34f0: 6a ff                        	push	-0x1
 11c34f2: 50                           	push	eax
 11c34f3: 8b 42 24                     	mov	eax, dword ptr [edx + 0x24]
 11c34f6: ff d0                        	call	eax
 11c34f8: 80 be 44 03 00 00 00         	cmp	byte ptr [esi + 0x344], 0x0
 11c34ff: 8b d8                        	mov	ebx, eax
 11c3501: 74 61                        	je	0x11c3564 <.text+0x514>
 11c3503: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c350a: 72 04                        	jb	0x11c3510 <.text+0x4c0>
 11c350c: 8b 07                        	mov	eax, dword ptr [edi]
 11c350e: eb 02                        	jmp	0x11c3512 <.text+0x4c2>
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
 11c355f: e8 0c 57 00 00               	call	0x11c8c70 <.text+0x5c20>
 11c3564: 83 be 2c 03 00 00 08         	cmp	dword ptr [esi + 0x32c], 0x8
 11c356b: 72 02                        	jb	0x11c356f <.text+0x51f>
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
 11c35ac: e8                           	<unknown>
 11c35ad: 5f                           	pop	edi
 11c35ae: ae                           	scasb	al, byte ptr es:[edi]
 11c35af: ff                           	<unknown>
