
<stdin>:	file format elf32-i386

Disassembly of section .text:

011f2460 <.text>:
 11f2460: 55                           	push	ebp
 11f2461: 8b ec                        	mov	ebp, esp
 11f2463: 83 ec 68                     	sub	esp, 0x68
 11f2466: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
 11f246b: 33 c5                        	xor	eax, ebp
 11f246d: 89 45 fc                     	mov	dword ptr [ebp - 0x4], eax
 11f2470: 80 3d 68 a8 bd 01 00         	cmp	byte ptr [0x1bda868], 0x0
 11f2477: 53                           	push	ebx
 11f2478: 8b 5d 08                     	mov	ebx, dword ptr [ebp + 0x8]
 11f247b: 56                           	push	esi
 11f247c: 57                           	push	edi
 11f247d: 8b 7d 10                     	mov	edi, dword ptr [ebp + 0x10]
 11f2480: 89 4d a4                     	mov	dword ptr [ebp - 0x5c], ecx
 11f2483: 0f 85 01 0b 00 00            	jne	0x11f2f8a <.text+0xb2a>
 11f2489: 85 db                        	test	ebx, ebx
 11f248b: 0f 84 f9 0a 00 00            	je	0x11f2f8a <.text+0xb2a>
 11f2491: 8b 03                        	mov	eax, dword ptr [ebx]
 11f2493: 8b 50 44                     	mov	edx, dword ptr [eax + 0x44]
 11f2496: 8d 4d c4                     	lea	ecx, [ebp - 0x3c]
 11f2499: 51                           	push	ecx
 11f249a: 6a 00                        	push	0x0
 11f249c: 53                           	push	ebx
 11f249d: ff d2                        	call	edx
 11f249f: db 45 dc                     	fild	dword ptr [ebp - 0x24]
 11f24a2: 8b 45 dc                     	mov	eax, dword ptr [ebp - 0x24]
 11f24a5: 85 c0                        	test	eax, eax
 11f24a7: 79 06                        	jns	0x11f24af <.text+0x4f>
 11f24a9: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11f24af: 8b 4d e0                     	mov	ecx, dword ptr [ebp - 0x20]
 11f24b2: d9 5d b4                     	fstp	dword ptr [ebp - 0x4c]
 11f24b5: db 45 e0                     	fild	dword ptr [ebp - 0x20]
 11f24b8: 85 c9                        	test	ecx, ecx
 11f24ba: 79 06                        	jns	0x11f24c2 <.text+0x62>
 11f24bc: d8 05 b4 61 56 01            	fadd	dword ptr [0x15661b4]
 11f24c2: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
 11f24c5: d9 5d b8                     	fstp	dword ptr [ebp - 0x48]
 11f24c8: f3 0f 10 1d 84 21 56 01      	movss	xmm3, dword ptr [0x1562184]
 11f24d0: 0f 57 ed                     	xorps	xmm5, xmm5
 11f24d3: 85 c0                        	test	eax, eax
 11f24d5: 0f 84 c2 00 00 00            	je	0x11f259d <.text+0x13d>
 11f24db: 8b 50 08                     	mov	edx, dword ptr [eax + 0x8]
 11f24de: 8b 70 0c                     	mov	esi, dword ptr [eax + 0xc]
 11f24e1: 2b 70 04                     	sub	esi, dword ptr [eax + 0x4]
 11f24e4: f3 0f 10 0d fc 20 56 01      	movss	xmm1, dword ptr [0x15620fc]
 11f24ec: 66 0f 6e 10                  	movd	xmm2, dword ptr [eax]
 11f24f0: 8b ca                        	mov	ecx, edx
 11f24f2: 2b 08                        	sub	ecx, dword ptr [eax]
 11f24f4: 80 7d 1c 00                  	cmp	byte ptr [ebp + 0x1c], 0x0
 11f24f8: 0f 57 c0                     	xorps	xmm0, xmm0
 11f24fb: f3 0f 2a c1                  	cvtsi2ss	xmm0, ecx
 11f24ff: f3 0f 11 45 b0               	movss	dword ptr [ebp - 0x50], xmm0
 11f2504: 0f 28 c1                     	movaps	xmm0, xmm1
 11f2507: f3 0f 5e 45 b4               	divss	xmm0, dword ptr [ebp - 0x4c]
 11f250c: f3 0f 5e 4d b8               	divss	xmm1, dword ptr [ebp - 0x48]
 11f2511: 0f 57 ff                     	xorps	xmm7, xmm7
 11f2514: f3 0f 2a fe                  	cvtsi2ss	xmm7, esi
 11f2518: 0f 5b d2                     	cvtdq2ps	xmm2, xmm2
 11f251b: 74 48                        	je	0x11f2565 <.text+0x105>
 11f251d: f3 0f 58 d3                  	addss	xmm2, xmm3
 11f2521: f3 0f 59 d0                  	mulss	xmm2, xmm0
 11f2525: f3 0f 11 55 ec               	movss	dword ptr [ebp - 0x14], xmm2
 11f252a: 66 0f 6e 50 04               	movd	xmm2, dword ptr [eax + 0x4]
 11f252f: 0f 5b d2                     	cvtdq2ps	xmm2, xmm2
 11f2532: f3 0f 58 d3                  	addss	xmm2, xmm3
 11f2536: f3 0f 59 d1                  	mulss	xmm2, xmm1
 11f253a: f3 0f 11 55 f0               	movss	dword ptr [ebp - 0x10], xmm2
 11f253f: 0f 57 d2                     	xorps	xmm2, xmm2
 11f2542: f3 0f 2a d2                  	cvtsi2ss	xmm2, edx
 11f2546: f3 0f 5c d3                  	subss	xmm2, xmm3
 11f254a: f3 0f 59 d0                  	mulss	xmm2, xmm0
 11f254e: 66 0f 6e 40 0c               	movd	xmm0, dword ptr [eax + 0xc]
 11f2553: 0f 5b c0                     	cvtdq2ps	xmm0, xmm0
 11f2556: f3 0f 5c c3                  	subss	xmm0, xmm3
 11f255a: f3 0f 11 55 f4               	movss	dword ptr [ebp - 0xc], xmm2
 11f255f: f3 0f 59 c1                  	mulss	xmm0, xmm1
 11f2563: eb 64                        	jmp	0x11f25c9 <.text+0x169>
 11f2565: f3 0f 59 d0                  	mulss	xmm2, xmm0
 11f2569: f3 0f 11 55 ec               	movss	dword ptr [ebp - 0x14], xmm2
 11f256e: 66 0f 6e 50 04               	movd	xmm2, dword ptr [eax + 0x4]
 11f2573: 0f 5b d2                     	cvtdq2ps	xmm2, xmm2
 11f2576: f3 0f 59 d1                  	mulss	xmm2, xmm1
 11f257a: f3 0f 11 55 f0               	movss	dword ptr [ebp - 0x10], xmm2
 11f257f: 0f 57 d2                     	xorps	xmm2, xmm2
 11f2582: f3 0f 2a d2                  	cvtsi2ss	xmm2, edx
 11f2586: f3 0f 59 d0                  	mulss	xmm2, xmm0
 11f258a: 66 0f 6e 40 0c               	movd	xmm0, dword ptr [eax + 0xc]
 11f258f: 0f 5b c0                     	cvtdq2ps	xmm0, xmm0
 11f2592: f3 0f 11 55 f4               	movss	dword ptr [ebp - 0xc], xmm2
 11f2597: f3 0f 59 c1                  	mulss	xmm0, xmm1
 11f259b: eb 2c                        	jmp	0x11f25c9 <.text+0x169>
 11f259d: f3 0f 10 45 b4               	movss	xmm0, dword ptr [ebp - 0x4c]
 11f25a2: f3 0f 10 7d b8               	movss	xmm7, dword ptr [ebp - 0x48]
 11f25a7: 8b 4d ac                     	mov	ecx, dword ptr [ebp - 0x54]
 11f25aa: 8b 75 ac                     	mov	esi, dword ptr [ebp - 0x54]
 11f25ad: f3 0f 11 45 b0               	movss	dword ptr [ebp - 0x50], xmm0
 11f25b2: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11f25ba: f3 0f 11 6d ec               	movss	dword ptr [ebp - 0x14], xmm5
 11f25bf: f3 0f 11 6d f0               	movss	dword ptr [ebp - 0x10], xmm5
 11f25c4: f3 0f 11 45 f4               	movss	dword ptr [ebp - 0xc], xmm0
 11f25c9: 80 3d 69 a8 bd 01 01         	cmp	byte ptr [0x1bda869], 0x1
 11f25d0: 8b 55 14                     	mov	edx, dword ptr [ebp + 0x14]
 11f25d3: f3 0f 10 52 10               	movss	xmm2, dword ptr [edx + 0x10]
 11f25d8: f3 0f 10 72 14               	movss	xmm6, dword ptr [edx + 0x14]
 11f25dd: f3 0f 11 45 f8               	movss	dword ptr [ebp - 0x8], xmm0
 11f25e2: f3 0f 10 02                  	movss	xmm0, dword ptr [edx]
 11f25e6: 0f 28 e0                     	movaps	xmm4, xmm0
 11f25e9: f3 0f 59 45 b0               	mulss	xmm0, dword ptr [ebp - 0x50]
 11f25ee: 0f 28 da                     	movaps	xmm3, xmm2
 11f25f1: f3 0f 59 15 b0 61 56 01      	mulss	xmm2, dword ptr [0x15661b0]
 11f25f9: f3 0f 59 df                  	mulss	xmm3, xmm7
 11f25fd: 0f 28 cb                     	movaps	xmm1, xmm3
 11f2600: f3 0f 59 e5                  	mulss	xmm4, xmm5
 11f2604: f3 0f 10 6a 30               	movss	xmm5, dword ptr [edx + 0x30]
 11f2609: f3 0f 58 cc                  	addss	xmm1, xmm4
 11f260d: f3 0f 58 cd                  	addss	xmm1, xmm5
 11f2611: f3 0f 11 4d b8               	movss	dword ptr [ebp - 0x48], xmm1
 11f2616: 0f 28 ce                     	movaps	xmm1, xmm6
 11f2619: f3 0f 59 35 b0 61 56 01      	mulss	xmm6, dword ptr [0x15661b0]
 11f2621: f3 0f 59 cf                  	mulss	xmm1, xmm7
 11f2625: f3 0f 10 7a 04               	movss	xmm7, dword ptr [edx + 0x4]
 11f262a: f3 0f 11 4d bc               	movss	dword ptr [ebp - 0x44], xmm1
 11f262f: f3 0f 11 7d ac               	movss	dword ptr [ebp - 0x54], xmm7
 11f2634: f3 0f 59 3d b0 61 56 01      	mulss	xmm7, dword ptr [0x15661b0]
 11f263c: f3 0f 58 cf                  	addss	xmm1, xmm7
 11f2640: f3 0f 11 7d a8               	movss	dword ptr [ebp - 0x58], xmm7
 11f2645: f3 0f 10 7a 34               	movss	xmm7, dword ptr [edx + 0x34]
 11f264a: f3 0f 58 cf                  	addss	xmm1, xmm7
 11f264e: f3 0f 11 4d b4               	movss	dword ptr [ebp - 0x4c], xmm1
 11f2653: 0f 28 ca                     	movaps	xmm1, xmm2
 11f2656: f3 0f 58 cc                  	addss	xmm1, xmm4
 11f265a: f3 0f 58 cd                  	addss	xmm1, xmm5
 11f265e: f3 0f 11 4d 98               	movss	dword ptr [ebp - 0x68], xmm1
 11f2663: 0f 28 ce                     	movaps	xmm1, xmm6
 11f2666: f3 0f 58 4d a8               	addss	xmm1, dword ptr [ebp - 0x58]
 11f266b: f3 0f 58 cf                  	addss	xmm1, xmm7
 11f266f: f3 0f 11 4d 9c               	movss	dword ptr [ebp - 0x64], xmm1
 11f2674: 0f 28 c8                     	movaps	xmm1, xmm0
 11f2677: f3 0f 58 cb                  	addss	xmm1, xmm3
 11f267b: f3 0f 58 cd                  	addss	xmm1, xmm5
 11f267f: f3 0f 11 4d a0               	movss	dword ptr [ebp - 0x60], xmm1
 11f2684: f3 0f 10 4d ac               	movss	xmm1, dword ptr [ebp - 0x54]
 11f2689: f3 0f 59 4d b0               	mulss	xmm1, dword ptr [ebp - 0x50]
 11f268e: 0f 28 d9                     	movaps	xmm3, xmm1
 11f2691: f3 0f 58 5d bc               	addss	xmm3, dword ptr [ebp - 0x44]
 11f2696: f3 0f 58 c2                  	addss	xmm0, xmm2
 11f269a: f3 0f 58 ce                  	addss	xmm1, xmm6
 11f269e: f3 0f 58 df                  	addss	xmm3, xmm7
 11f26a2: f3 0f 58 c5                  	addss	xmm0, xmm5
 11f26a6: f3 0f 58 cf                  	addss	xmm1, xmm7
 11f26aa: f3 0f 11 5d a8               	movss	dword ptr [ebp - 0x58], xmm3
 11f26af: f3 0f 11 45 b0               	movss	dword ptr [ebp - 0x50], xmm0
 11f26b4: f3 0f 11 4d bc               	movss	dword ptr [ebp - 0x44], xmm1
 11f26b9: 0f 85 be 05 00 00            	jne	0x11f2c7d <.text+0x81d>
 11f26bf: 85 c0                        	test	eax, eax
 11f26c1: 0f 84 92 02 00 00            	je	0x11f2959 <.text+0x4f9>
 11f26c7: 83 f9 0e                     	cmp	ecx, 0xe
 11f26ca: 0f 85 89 02 00 00            	jne	0x11f2959 <.text+0x4f9>
 11f26d0: 3b f1                        	cmp	esi, ecx
 11f26d2: 0f 85 81 02 00 00            	jne	0x11f2959 <.text+0x4f9>
 11f26d8: a1 50 a8 bd 01               	mov	eax, dword ptr [0x1bda850]
 11f26dd: ff 05 90 b1 c1 01            	inc	dword ptr [0x1c1b190]
 11f26e3: 3d 40 1f 00 00               	cmp	eax, 0x1f40
 11f26e8: 7d 23                        	jge	0x11f270d <.text+0x2ad>
 11f26ea: 8b 0d 48 a8 bd 01            	mov	ecx, dword ptr [0x1bda848]
 11f26f0: 6b c0 70                     	imul	eax, eax, 0x70
 11f26f3: 8b 11                        	mov	edx, dword ptr [ecx]
 11f26f5: 68 00 10 00 00               	push	0x1000
 11f26fa: 68 88 b1 c1 01               	push	0x1c1b188
 11f26ff: 6a 70                        	push	0x70
 11f2701: 50                           	push	eax
 11f2702: 8b 42 2c                     	mov	eax, dword ptr [edx + 0x2c]
 11f2705: 51                           	push	ecx
 11f2706: ff d0                        	call	eax
 11f2708: 8b 75 a4                     	mov	esi, dword ptr [ebp - 0x5c]
 11f270b: eb 32                        	jmp	0x11f273f <.text+0x2df>
 11f270d: 8b 75 a4                     	mov	esi, dword ptr [ebp - 0x5c]
 11f2710: 8b ce                        	mov	ecx, esi
 11f2712: e8 29 f4 ff ff               	call	0x11f1b40
 11f2717: a1 48 a8 bd 01               	mov	eax, dword ptr [0x1bda848]
 11f271c: 8b 10                        	mov	edx, dword ptr [eax]
 11f271e: 68 00 20 00 00               	push	0x2000
 11f2723: 68 88 b1 c1 01               	push	0x1c1b188
 11f2728: 33 c9                        	xor	ecx, ecx
 11f272a: 6a 70                        	push	0x70
 11f272c: 51                           	push	ecx
 11f272d: 50                           	push	eax
 11f272e: 8b 42 2c                     	mov	eax, dword ptr [edx + 0x2c]
 11f2731: 89 0d 50 a8 bd 01            	mov	dword ptr [0x1bda850], ecx
 11f2737: 89 0d 54 a8 bd 01            	mov	dword ptr [0x1bda854], ecx
 11f273d: ff d0                        	call	eax
 11f273f: 66 0f 6e 05 90 b1 c1 01      	movd	xmm0, dword ptr [0x1c1b190]
 11f2747: f3 0f 10 0d d4 c0 5a 01      	movss	xmm1, dword ptr [0x15ac0d4]
 11f274f: 0f 5b c0                     	cvtdq2ps	xmm0, xmm0
 11f2752: f3 0f 59 05 74 f3 85 01      	mulss	xmm0, dword ptr [0x185f374]
 11f275a: f3 0f 5c c8                  	subss	xmm1, xmm0
 11f275e: 85 c0                        	test	eax, eax
 11f2760: 0f 85 de 01 00 00            	jne	0x11f2944 <.text+0x4e4>
 11f2766: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f276c: f3 0f 10 05 84 21 56 01      	movss	xmm0, dword ptr [0x1562184]
 11f2774: f3 0f 10 55 b8               	movss	xmm2, dword ptr [ebp - 0x48]
 11f2779: f3 0f 10 65 ec               	movss	xmm4, dword ptr [ebp - 0x14]
 11f277e: f3 0f 10 75 f8               	movss	xmm6, dword ptr [ebp - 0x8]
 11f2783: f3 0f 10 5d 98               	movss	xmm3, dword ptr [ebp - 0x68]
 11f2788: f3 0f 5c d0                  	subss	xmm2, xmm0
 11f278c: f3 0f 11 11                  	movss	dword ptr [ecx], xmm2
 11f2790: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2796: f3 0f 10 55 b4               	movss	xmm2, dword ptr [ebp - 0x4c]
 11f279b: f3 0f 5c d0                  	subss	xmm2, xmm0
 11f279f: f3 0f 11 52 04               	movss	dword ptr [edx + 0x4], xmm2
 11f27a4: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f27a9: f3 0f 11 48 08               	movss	dword ptr [eax + 0x8], xmm1
 11f27ae: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f27b4: f3 0f 10 15 fc 20 56 01      	movss	xmm2, dword ptr [0x15620fc]
 11f27bc: f3 0f 11 51 0c               	movss	dword ptr [ecx + 0xc], xmm2
 11f27c1: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f27c7: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11f27ca: 89 42 10                     	mov	dword ptr [edx + 0x10], eax
 11f27cd: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f27d3: f3 0f 11 61 14               	movss	dword ptr [ecx + 0x14], xmm4
 11f27d8: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f27de: f3 0f 11 72 18               	movss	dword ptr [edx + 0x18], xmm6
 11f27e3: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f27e9: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f27ed: f3 0f 11 59 1c               	movss	dword ptr [ecx + 0x1c], xmm3
 11f27f2: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f27f8: f3 0f 10 5d 9c               	movss	xmm3, dword ptr [ebp - 0x64]
 11f27fd: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2801: f3 0f 11 5a 20               	movss	dword ptr [edx + 0x20], xmm3
 11f2806: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f280c: f3 0f 11 49 24               	movss	dword ptr [ecx + 0x24], xmm1
 11f2811: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2817: f3 0f 11 52 28               	movss	dword ptr [edx + 0x28], xmm2
 11f281c: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2822: 89 41 2c                     	mov	dword ptr [ecx + 0x2c], eax
 11f2825: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f282b: f3 0f 11 62 30               	movss	dword ptr [edx + 0x30], xmm4
 11f2830: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2836: f3 0f 10 65 f0               	movss	xmm4, dword ptr [ebp - 0x10]
 11f283b: f3 0f 10 5d a0               	movss	xmm3, dword ptr [ebp - 0x60]
 11f2840: f3 0f 11 61 34               	movss	dword ptr [ecx + 0x34], xmm4
 11f2845: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f284b: f3 0f 10 6d f4               	movss	xmm5, dword ptr [ebp - 0xc]
 11f2850: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2854: f3 0f 11 5a 38               	movss	dword ptr [edx + 0x38], xmm3
 11f2859: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f285f: f3 0f 10 5d a8               	movss	xmm3, dword ptr [ebp - 0x58]
 11f2864: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2868: f3 0f 11 59 3c               	movss	dword ptr [ecx + 0x3c], xmm3
 11f286d: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2873: f3 0f 11 4a 40               	movss	dword ptr [edx + 0x40], xmm1
 11f2878: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f287e: f3 0f 10 5d b0               	movss	xmm3, dword ptr [ebp - 0x50]
 11f2883: f3 0f 11 51 44               	movss	dword ptr [ecx + 0x44], xmm2
 11f2888: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f288e: 89 42 48                     	mov	dword ptr [edx + 0x48], eax
 11f2891: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2897: f3 0f 11 69 4c               	movss	dword ptr [ecx + 0x4c], xmm5
 11f289c: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f28a2: f3 0f 11 72 50               	movss	dword ptr [edx + 0x50], xmm6
 11f28a7: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f28ad: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f28b1: f3 0f 11 59 54               	movss	dword ptr [ecx + 0x54], xmm3
 11f28b6: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f28bc: f3 0f 10 5d bc               	movss	xmm3, dword ptr [ebp - 0x44]
 11f28c1: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f28c5: f3 0f 11 5a 58               	movss	dword ptr [edx + 0x58], xmm3
 11f28ca: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f28d0: f3 0f 11 49 5c               	movss	dword ptr [ecx + 0x5c], xmm1
 11f28d5: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f28db: f3 0f 11 52 60               	movss	dword ptr [edx + 0x60], xmm2
 11f28e0: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f28e6: 89 41 64                     	mov	dword ptr [ecx + 0x64], eax
 11f28e9: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f28ef: f3 0f 11 6a 68               	movss	dword ptr [edx + 0x68], xmm5
 11f28f4: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f28f9: f3 0f 11 60 6c               	movss	dword ptr [eax + 0x6c], xmm4
 11f28fe: a1 48 a8 bd 01               	mov	eax, dword ptr [0x1bda848]
 11f2903: 8b 08                        	mov	ecx, dword ptr [eax]
 11f2905: 8b 51 30                     	mov	edx, dword ptr [ecx + 0x30]
 11f2908: 50                           	push	eax
 11f2909: ff d2                        	call	edx
 11f290b: 8b 03                        	mov	eax, dword ptr [ebx]
 11f290d: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
 11f2910: 53                           	push	ebx
 11f2911: ff d1                        	call	ecx
 11f2913: 8b 15 50 a8 bd 01            	mov	edx, dword ptr [0x1bda850]
 11f2919: 52                           	push	edx
 11f291a: 53                           	push	ebx
 11f291b: 8b ce                        	mov	ecx, esi
 11f291d: e8 ae ee ff ff               	call	0x11f17d0
 11f2922: 84 c0                        	test	al, al
 11f2924: 0f 85 5a 06 00 00            	jne	0x11f2f84 <.text+0xb24>
 11f292a: 8b ce                        	mov	ecx, esi
 11f292c: e8 0f f2 ff ff               	call	0x11f1b40
 11f2931: a1 50 a8 bd 01               	mov	eax, dword ptr [0x1bda850]
 11f2936: 50                           	push	eax
 11f2937: 53                           	push	ebx
 11f2938: 8b ce                        	mov	ecx, esi
 11f293a: e8 91 ee ff ff               	call	0x11f17d0
 11f293f: e9 40 06 00 00               	jmp	0x11f2f84 <.text+0xb24>
 11f2944: 5f                           	pop	edi
 11f2945: 5e                           	pop	esi
 11f2946: 32 c0                        	xor	al, al
 11f2948: 5b                           	pop	ebx
 11f2949: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11f294c: 33 cd                        	xor	ecx, ebp
 11f294e: e8 85 48 1e 00               	call	0x13d71d8 <.text+0x1e4d78>
 11f2953: 8b e5                        	mov	esp, ebp
 11f2955: 5d                           	pop	ebp
 11f2956: c2 18 00                     	ret	0x18
 11f2959: 85 ff                        	test	edi, edi
 11f295b: 74 1f                        	je	0x11f297c <.text+0x51c>
 11f295d: 0f bf 4f 04                  	movsx	ecx, word ptr [edi + 0x4]
 11f2961: 0f bf 17                     	movsx	edx, word ptr [edi]
 11f2964: 2b ca                        	sub	ecx, edx
 11f2966: 0f 84 1e 06 00 00            	je	0x11f2f8a <.text+0xb2a>
 11f296c: 0f bf 47 06                  	movsx	eax, word ptr [edi + 0x6]
 11f2970: 0f bf 4f 02                  	movsx	ecx, word ptr [edi + 0x2]
 11f2974: 2b c1                        	sub	eax, ecx
 11f2976: 0f 84 0e 06 00 00            	je	0x11f2f8a <.text+0xb2a>
 11f297c: 83 7d c4 19                  	cmp	dword ptr [ebp - 0x3c], 0x19
 11f2980: 8b 75 18                     	mov	esi, dword ptr [ebp + 0x18]
 11f2983: 75 23                        	jne	0x11f29a8 <.text+0x548>
 11f2985: 8b 15 70 a8 bd 01            	mov	edx, dword ptr [0x1bda870]
 11f298b: 0b 15 74 a8 bd 01            	or	edx, dword ptr [0x1bda874]
 11f2991: 75 15                        	jne	0x11f29a8 <.text+0x548>
 11f2993: 83 fe ff                     	cmp	esi, -0x1
 11f2996: 75 10                        	jne	0x11f29a8 <.text+0x548>
 11f2998: 38 55 1c                     	cmp	byte ptr [ebp + 0x1c], dl
 11f299b: 75 0b                        	jne	0x11f29a8 <.text+0x548>
 11f299d: ff 05 90 b1 c1 01            	inc	dword ptr [0x1c1b190]
 11f29a3: 88 55 c3                     	mov	byte ptr [ebp - 0x3d], dl
 11f29a6: eb 04                        	jmp	0x11f29ac <.text+0x54c>
 11f29a8: c6 45 c3 01                  	mov	byte ptr [ebp - 0x3d], 0x1
 11f29ac: a1 50 a8 bd 01               	mov	eax, dword ptr [0x1bda850]
 11f29b1: 3d 40 1f 00 00               	cmp	eax, 0x1f40
 11f29b6: 7d 1b                        	jge	0x11f29d3 <.text+0x573>
 11f29b8: 8b 0d 48 a8 bd 01            	mov	ecx, dword ptr [0x1bda848]
 11f29be: 6b c0 70                     	imul	eax, eax, 0x70
 11f29c1: 8b 11                        	mov	edx, dword ptr [ecx]
 11f29c3: 68 00 10 00 00               	push	0x1000
 11f29c8: 68 88 b1 c1 01               	push	0x1c1b188
 11f29cd: 6a 70                        	push	0x70
 11f29cf: 50                           	push	eax
 11f29d0: 51                           	push	ecx
 11f29d1: eb 2b                        	jmp	0x11f29fe <.text+0x59e>
 11f29d3: 8b 4d a4                     	mov	ecx, dword ptr [ebp - 0x5c]
 11f29d6: e8 65 f1 ff ff               	call	0x11f1b40
 11f29db: a1 48 a8 bd 01               	mov	eax, dword ptr [0x1bda848]
 11f29e0: 8b 10                        	mov	edx, dword ptr [eax]
 11f29e2: 68 00 20 00 00               	push	0x2000
 11f29e7: 68 88 b1 c1 01               	push	0x1c1b188
 11f29ec: 33 c9                        	xor	ecx, ecx
 11f29ee: 6a 70                        	push	0x70
 11f29f0: 51                           	push	ecx
 11f29f1: 89 0d 50 a8 bd 01            	mov	dword ptr [0x1bda850], ecx
 11f29f7: 89 0d 54 a8 bd 01            	mov	dword ptr [0x1bda854], ecx
 11f29fd: 50                           	push	eax
 11f29fe: 8b 42 2c                     	mov	eax, dword ptr [edx + 0x2c]
 11f2a01: ff d0                        	call	eax
 11f2a03: 66 0f 6e 05 90 b1 c1 01      	movd	xmm0, dword ptr [0x1c1b190]
 11f2a0b: f3 0f 10 0d d4 c0 5a 01      	movss	xmm1, dword ptr [0x15ac0d4]
 11f2a13: 0f 5b c0                     	cvtdq2ps	xmm0, xmm0
 11f2a16: f3 0f 59 05 74 f3 85 01      	mulss	xmm0, dword ptr [0x185f374]
 11f2a1e: f3 0f 5c c8                  	subss	xmm1, xmm0
 11f2a22: 85 c0                        	test	eax, eax
 11f2a24: 0f 85 1a ff ff ff            	jne	0x11f2944 <.text+0x4e4>
 11f2a2a: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2a30: f3 0f 10 05 84 21 56 01      	movss	xmm0, dword ptr [0x1562184]
 11f2a38: f3 0f 10 55 b8               	movss	xmm2, dword ptr [ebp - 0x48]
 11f2a3d: f3 0f 10 65 ec               	movss	xmm4, dword ptr [ebp - 0x14]
 11f2a42: f3 0f 10 75 f8               	movss	xmm6, dword ptr [ebp - 0x8]
 11f2a47: f3 0f 10 5d 98               	movss	xmm3, dword ptr [ebp - 0x68]
 11f2a4c: f3 0f 5c d0                  	subss	xmm2, xmm0
 11f2a50: f3 0f 11 11                  	movss	dword ptr [ecx], xmm2
 11f2a54: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2a5a: f3 0f 10 55 b4               	movss	xmm2, dword ptr [ebp - 0x4c]
 11f2a5f: f3 0f 5c d0                  	subss	xmm2, xmm0
 11f2a63: f3 0f 11 52 04               	movss	dword ptr [edx + 0x4], xmm2
 11f2a68: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2a6d: f3 0f 11 48 08               	movss	dword ptr [eax + 0x8], xmm1
 11f2a72: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2a78: f3 0f 10 15 fc 20 56 01      	movss	xmm2, dword ptr [0x15620fc]
 11f2a80: f3 0f 11 51 0c               	movss	dword ptr [ecx + 0xc], xmm2
 11f2a85: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2a8b: 89 72 10                     	mov	dword ptr [edx + 0x10], esi
 11f2a8e: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2a93: f3 0f 11 60 14               	movss	dword ptr [eax + 0x14], xmm4
 11f2a98: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2a9e: f3 0f 11 71 18               	movss	dword ptr [ecx + 0x18], xmm6
 11f2aa3: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2aa9: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2aad: f3 0f 11 5a 1c               	movss	dword ptr [edx + 0x1c], xmm3
 11f2ab2: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2ab7: f3 0f 10 5d 9c               	movss	xmm3, dword ptr [ebp - 0x64]
 11f2abc: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2ac0: f3 0f 11 58 20               	movss	dword ptr [eax + 0x20], xmm3
 11f2ac5: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2acb: f3 0f 11 49 24               	movss	dword ptr [ecx + 0x24], xmm1
 11f2ad0: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2ad6: f3 0f 11 52 28               	movss	dword ptr [edx + 0x28], xmm2
 11f2adb: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2ae0: 89 70 2c                     	mov	dword ptr [eax + 0x2c], esi
 11f2ae3: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2ae9: f3 0f 11 61 30               	movss	dword ptr [ecx + 0x30], xmm4
 11f2aee: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2af4: f3 0f 10 65 f0               	movss	xmm4, dword ptr [ebp - 0x10]
 11f2af9: f3 0f 10 5d a0               	movss	xmm3, dword ptr [ebp - 0x60]
 11f2afe: f3 0f 11 62 34               	movss	dword ptr [edx + 0x34], xmm4
 11f2b03: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2b08: f3 0f 10 6d f4               	movss	xmm5, dword ptr [ebp - 0xc]
 11f2b0d: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2b11: f3 0f 11 58 38               	movss	dword ptr [eax + 0x38], xmm3
 11f2b16: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2b1c: f3 0f 10 5d a8               	movss	xmm3, dword ptr [ebp - 0x58]
 11f2b21: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2b25: f3 0f 11 59 3c               	movss	dword ptr [ecx + 0x3c], xmm3
 11f2b2a: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2b30: f3 0f 11 4a 40               	movss	dword ptr [edx + 0x40], xmm1
 11f2b35: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2b3a: f3 0f 10 5d b0               	movss	xmm3, dword ptr [ebp - 0x50]
 11f2b3f: f3 0f 11 50 44               	movss	dword ptr [eax + 0x44], xmm2
 11f2b44: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2b4a: 89 71 48                     	mov	dword ptr [ecx + 0x48], esi
 11f2b4d: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2b53: f3 0f 11 6a 4c               	movss	dword ptr [edx + 0x4c], xmm5
 11f2b58: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2b5d: f3 0f 11 70 50               	movss	dword ptr [eax + 0x50], xmm6
 11f2b62: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2b68: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2b6c: f3 0f 11 59 54               	movss	dword ptr [ecx + 0x54], xmm3
 11f2b71: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2b77: f3 0f 10 5d bc               	movss	xmm3, dword ptr [ebp - 0x44]
 11f2b7c: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2b80: f3 0f 11 5a 58               	movss	dword ptr [edx + 0x58], xmm3
 11f2b85: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2b8a: f3 0f 11 48 5c               	movss	dword ptr [eax + 0x5c], xmm1
 11f2b8f: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2b95: f3 0f 11 51 60               	movss	dword ptr [ecx + 0x60], xmm2
 11f2b9a: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2ba0: 89 72 64                     	mov	dword ptr [edx + 0x64], esi
 11f2ba3: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2ba8: f3 0f 11 68 68               	movss	dword ptr [eax + 0x68], xmm5
 11f2bad: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2bb3: f3 0f 11 61 6c               	movss	dword ptr [ecx + 0x6c], xmm4
 11f2bb8: a1 48 a8 bd 01               	mov	eax, dword ptr [0x1bda848]
 11f2bbd: 8b 10                        	mov	edx, dword ptr [eax]
 11f2bbf: 50                           	push	eax
 11f2bc0: 8b 42 30                     	mov	eax, dword ptr [edx + 0x30]
 11f2bc3: ff d0                        	call	eax
 11f2bc5: a1 8c b1 c1 01               	mov	eax, dword ptr [0x1c1b18c]
 11f2bca: 8a 4d c3                     	mov	cl, byte ptr [ebp - 0x3d]
 11f2bcd: 8b 15 70 a8 bd 01            	mov	edx, dword ptr [0x1bda870]
 11f2bd3: c1 e0 05                     	shl	eax, 0x5
 11f2bd6: 88 88 98 a8 bd 01            	mov	byte ptr [eax + 0x1bda898], cl
 11f2bdc: 8b 0d 74 a8 bd 01            	mov	ecx, dword ptr [0x1bda874]
 11f2be2: 89 90 88 a8 bd 01            	mov	dword ptr [eax + 0x1bda888], edx
 11f2be8: 8b 15 50 a8 bd 01            	mov	edx, dword ptr [0x1bda850]
 11f2bee: 89 88 8c a8 bd 01            	mov	dword ptr [eax + 0x1bda88c], ecx
 11f2bf4: 89 90 84 a8 bd 01            	mov	dword ptr [eax + 0x1bda884], edx
 11f2bfa: 89 98 80 a8 bd 01            	mov	dword ptr [eax + 0x1bda880], ebx
 11f2c00: 8b 03                        	mov	eax, dword ptr [ebx]
 11f2c02: 8b 48 04                     	mov	ecx, dword ptr [eax + 0x4]
 11f2c05: 53                           	push	ebx
 11f2c06: ff d1                        	call	ecx
 11f2c08: a1 8c b1 c1 01               	mov	eax, dword ptr [0x1c1b18c]
 11f2c0d: c1 e0 05                     	shl	eax, 0x5
 11f2c10: 85 ff                        	test	edi, edi
 11f2c12: 74 36                        	je	0x11f2c4a <.text+0x7ea>
 11f2c14: 0f b7 17                     	movzx	edx, word ptr [edi]
 11f2c17: ff 05 8c b1 c1 01            	inc	dword ptr [0x1c1b18c]
 11f2c1d: 66 89 90 90 a8 bd 01         	mov	word ptr [eax + 0x1bda890], dx
 11f2c24: 0f b7 4f 04                  	movzx	ecx, word ptr [edi + 0x4]
 11f2c28: 66 89 88 94 a8 bd 01         	mov	word ptr [eax + 0x1bda894], cx
 11f2c2f: 0f b7 57 02                  	movzx	edx, word ptr [edi + 0x2]
 11f2c33: 66 89 90 92 a8 bd 01         	mov	word ptr [eax + 0x1bda892], dx
 11f2c3a: 0f b7 4f 06                  	movzx	ecx, word ptr [edi + 0x6]
 11f2c3e: 66 89 88 96 a8 bd 01         	mov	word ptr [eax + 0x1bda896], cx
 11f2c45: e9 3a 03 00 00               	jmp	0x11f2f84 <.text+0xb24>
 11f2c4a: 33 d2                        	xor	edx, edx
 11f2c4c: ff 05 8c b1 c1 01            	inc	dword ptr [0x1c1b18c]
 11f2c52: 66 89 90 90 a8 bd 01         	mov	word ptr [eax + 0x1bda890], dx
 11f2c59: b9 20 03 00 00               	mov	ecx, 0x320
 11f2c5e: 66 89 88 94 a8 bd 01         	mov	word ptr [eax + 0x1bda894], cx
 11f2c65: b9 58 02 00 00               	mov	ecx, 0x258
 11f2c6a: 66 89 90 92 a8 bd 01         	mov	word ptr [eax + 0x1bda892], dx
 11f2c71: 66 89 88 96 a8 bd 01         	mov	word ptr [eax + 0x1bda896], cx
 11f2c78: e9 07 03 00 00               	jmp	0x11f2f84 <.text+0xb24>
 11f2c7d: be 70 a8 bd 01               	mov	esi, 0x1bda870
 11f2c82: e8 09 ec ff ff               	call	0x11f1890
 11f2c87: a1 50 a8 bd 01               	mov	eax, dword ptr [0x1bda850]
 11f2c8c: 3d 40 1f 00 00               	cmp	eax, 0x1f40
 11f2c91: 7d 20                        	jge	0x11f2cb3 <.text+0x853>
 11f2c93: 8b 0d 48 a8 bd 01            	mov	ecx, dword ptr [0x1bda848]
 11f2c99: 6b c0 70                     	imul	eax, eax, 0x70
 11f2c9c: 8b 11                        	mov	edx, dword ptr [ecx]
 11f2c9e: 68 00 10 00 00               	push	0x1000
 11f2ca3: 68 88 b1 c1 01               	push	0x1c1b188
 11f2ca8: 6a 70                        	push	0x70
 11f2caa: 50                           	push	eax
 11f2cab: 8b 42 2c                     	mov	eax, dword ptr [edx + 0x2c]
 11f2cae: 51                           	push	ecx
 11f2caf: ff d0                        	call	eax
 11f2cb1: eb 25                        	jmp	0x11f2cd8 <.text+0x878>
 11f2cb3: a1 48 a8 bd 01               	mov	eax, dword ptr [0x1bda848]
 11f2cb8: 8b 08                        	mov	ecx, dword ptr [eax]
 11f2cba: 8b 51 2c                     	mov	edx, dword ptr [ecx + 0x2c]
 11f2cbd: 68 00 20 00 00               	push	0x2000
 11f2cc2: 68 88 b1 c1 01               	push	0x1c1b188
 11f2cc7: 6a 70                        	push	0x70
 11f2cc9: 6a 00                        	push	0x0
 11f2ccb: 50                           	push	eax
 11f2ccc: c7 05 50 a8 bd 01 00 00 00 00	mov	dword ptr [0x1bda850], 0x0
 11f2cd6: ff d2                        	call	edx
 11f2cd8: 66 0f 6e 05 90 b1 c1 01      	movd	xmm0, dword ptr [0x1c1b190]
 11f2ce0: f3 0f 10 0d d4 c0 5a 01      	movss	xmm1, dword ptr [0x15ac0d4]
 11f2ce8: 0f 5b c0                     	cvtdq2ps	xmm0, xmm0
 11f2ceb: f3 0f 59 05 74 f3 85 01      	mulss	xmm0, dword ptr [0x185f374]
 11f2cf3: f3 0f 5c c8                  	subss	xmm1, xmm0
 11f2cf7: 85 c0                        	test	eax, eax
 11f2cf9: 0f 85 45 fc ff ff            	jne	0x11f2944 <.text+0x4e4>
 11f2cff: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2d04: f3 0f 10 05 84 21 56 01      	movss	xmm0, dword ptr [0x1562184]
 11f2d0c: f3 0f 10 55 b8               	movss	xmm2, dword ptr [ebp - 0x48]
 11f2d11: f3 0f 10 65 ec               	movss	xmm4, dword ptr [ebp - 0x14]
 11f2d16: f3 0f 10 75 f8               	movss	xmm6, dword ptr [ebp - 0x8]
 11f2d1b: f3 0f 10 5d 98               	movss	xmm3, dword ptr [ebp - 0x68]
 11f2d20: f3 0f 5c d0                  	subss	xmm2, xmm0
 11f2d24: f3 0f 11 10                  	movss	dword ptr [eax], xmm2
 11f2d28: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2d2e: f3 0f 10 55 b4               	movss	xmm2, dword ptr [ebp - 0x4c]
 11f2d33: f3 0f 5c d0                  	subss	xmm2, xmm0
 11f2d37: f3 0f 11 51 04               	movss	dword ptr [ecx + 0x4], xmm2
 11f2d3c: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2d42: f3 0f 11 4a 08               	movss	dword ptr [edx + 0x8], xmm1
 11f2d47: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2d4c: f3 0f 10 15 fc 20 56 01      	movss	xmm2, dword ptr [0x15620fc]
 11f2d54: f3 0f 11 50 0c               	movss	dword ptr [eax + 0xc], xmm2
 11f2d59: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2d5f: 8b 45 18                     	mov	eax, dword ptr [ebp + 0x18]
 11f2d62: 89 41 10                     	mov	dword ptr [ecx + 0x10], eax
 11f2d65: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2d6b: f3 0f 11 62 14               	movss	dword ptr [edx + 0x14], xmm4
 11f2d70: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2d76: f3 0f 11 71 18               	movss	dword ptr [ecx + 0x18], xmm6
 11f2d7b: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2d81: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2d85: f3 0f 11 5a 1c               	movss	dword ptr [edx + 0x1c], xmm3
 11f2d8a: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2d90: f3 0f 10 5d 9c               	movss	xmm3, dword ptr [ebp - 0x64]
 11f2d95: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2d99: f3 0f 11 59 20               	movss	dword ptr [ecx + 0x20], xmm3
 11f2d9e: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2da4: f3 0f 11 4a 24               	movss	dword ptr [edx + 0x24], xmm1
 11f2da9: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2daf: f3 0f 11 51 28               	movss	dword ptr [ecx + 0x28], xmm2
 11f2db4: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2dba: 89 42 2c                     	mov	dword ptr [edx + 0x2c], eax
 11f2dbd: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2dc3: f3 0f 11 61 30               	movss	dword ptr [ecx + 0x30], xmm4
 11f2dc8: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2dce: f3 0f 10 65 f0               	movss	xmm4, dword ptr [ebp - 0x10]
 11f2dd3: f3 0f 10 5d a0               	movss	xmm3, dword ptr [ebp - 0x60]
 11f2dd8: f3 0f 11 62 34               	movss	dword ptr [edx + 0x34], xmm4
 11f2ddd: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2de3: f3 0f 10 6d f4               	movss	xmm5, dword ptr [ebp - 0xc]
 11f2de8: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2dec: f3 0f 11 59 38               	movss	dword ptr [ecx + 0x38], xmm3
 11f2df1: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2df7: f3 0f 10 5d a8               	movss	xmm3, dword ptr [ebp - 0x58]
 11f2dfc: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2e00: f3 0f 11 5a 3c               	movss	dword ptr [edx + 0x3c], xmm3
 11f2e05: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2e0b: f3 0f 11 49 40               	movss	dword ptr [ecx + 0x40], xmm1
 11f2e10: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2e16: f3 0f 10 5d b0               	movss	xmm3, dword ptr [ebp - 0x50]
 11f2e1b: f3 0f 11 52 44               	movss	dword ptr [edx + 0x44], xmm2
 11f2e20: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2e26: 89 41 48                     	mov	dword ptr [ecx + 0x48], eax
 11f2e29: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2e2f: f3 0f 11 6a 4c               	movss	dword ptr [edx + 0x4c], xmm5
 11f2e34: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2e3a: f3 0f 11 71 50               	movss	dword ptr [ecx + 0x50], xmm6
 11f2e3f: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2e45: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2e49: f3 0f 11 5a 54               	movss	dword ptr [edx + 0x54], xmm3
 11f2e4e: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2e54: f3 0f 10 5d bc               	movss	xmm3, dword ptr [ebp - 0x44]
 11f2e59: f3 0f 5c d8                  	subss	xmm3, xmm0
 11f2e5d: f3 0f 11 59 58               	movss	dword ptr [ecx + 0x58], xmm3
 11f2e62: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2e68: f3 0f 11 4a 5c               	movss	dword ptr [edx + 0x5c], xmm1
 11f2e6d: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2e73: f3 0f 11 51 60               	movss	dword ptr [ecx + 0x60], xmm2
 11f2e78: 8b 15 88 b1 c1 01            	mov	edx, dword ptr [0x1c1b188]
 11f2e7e: 89 42 64                     	mov	dword ptr [edx + 0x64], eax
 11f2e81: a1 88 b1 c1 01               	mov	eax, dword ptr [0x1c1b188]
 11f2e86: f3 0f 11 68 68               	movss	dword ptr [eax + 0x68], xmm5
 11f2e8b: 8b 0d 88 b1 c1 01            	mov	ecx, dword ptr [0x1c1b188]
 11f2e91: f3 0f 11 61 6c               	movss	dword ptr [ecx + 0x6c], xmm4
 11f2e96: a1 48 a8 bd 01               	mov	eax, dword ptr [0x1bda848]
 11f2e9b: 8b 10                        	mov	edx, dword ptr [eax]
 11f2e9d: 50                           	push	eax
 11f2e9e: 8b 42 30                     	mov	eax, dword ptr [edx + 0x30]
 11f2ea1: ff d0                        	call	eax
 11f2ea3: 85 ff                        	test	edi, edi
 11f2ea5: 75 0d                        	jne	0x11f2eb4 <.text+0xa54>
 11f2ea7: 8b 4d a4                     	mov	ecx, dword ptr [ebp - 0x5c]
 11f2eaa: e8 71 e8 ff ff               	call	0x11f1720
 11f2eaf: e9 94 00 00 00               	jmp	0x11f2f48 <.text+0xae8>
 11f2eb4: ba 90 a8 bd 01               	mov	edx, 0x1bda890
 11f2eb9: b9 08 00 00 00               	mov	ecx, 0x8
 11f2ebe: 8b c7                        	mov	eax, edi
 11f2ec0: 2b d7                        	sub	edx, edi
 11f2ec2: 8b 34 10                     	mov	esi, dword ptr [eax + edx]
 11f2ec5: 3b 30                        	cmp	esi, dword ptr [eax]
 11f2ec7: 75 0d                        	jne	0x11f2ed6 <.text+0xa76>
 11f2ec9: 83 e9 04                     	sub	ecx, 0x4
 11f2ecc: 83 c0 04                     	add	eax, 0x4
 11f2ecf: 83 f9 04                     	cmp	ecx, 0x4
 11f2ed2: 73 ee                        	jae	0x11f2ec2 <.text+0xa62>
 11f2ed4: eb 72                        	jmp	0x11f2f48 <.text+0xae8>
 11f2ed6: 0f bf 07                     	movsx	eax, word ptr [edi]
 11f2ed9: 0f bf 57 04                  	movsx	edx, word ptr [edi + 0x4]
 11f2edd: 0f bf 4f 02                  	movsx	ecx, word ptr [edi + 0x2]
 11f2ee1: 0f 57 c0                     	xorps	xmm0, xmm0
 11f2ee4: 2b d0                        	sub	edx, eax
 11f2ee6: 89 45 e4                     	mov	dword ptr [ebp - 0x1c], eax
 11f2ee9: 0f bf 47 06                  	movsx	eax, word ptr [edi + 0x6]
 11f2eed: 2b c1                        	sub	eax, ecx
 11f2eef: 89 55 ec                     	mov	dword ptr [ebp - 0x14], edx
 11f2ef2: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
 11f2ef5: a1 94 b1 c1 01               	mov	eax, dword ptr [0x1c1b194]
 11f2efa: 8d 55 e4                     	lea	edx, [ebp - 0x1c]
 11f2efd: 89 4d e8                     	mov	dword ptr [ebp - 0x18], ecx
 11f2f00: 8b 08                        	mov	ecx, dword ptr [eax]
 11f2f02: 52                           	push	edx
 11f2f03: f3 0f 11 45 f4               	movss	dword ptr [ebp - 0xc], xmm0
 11f2f08: f3 0f 10 05 fc 20 56 01      	movss	xmm0, dword ptr [0x15620fc]
 11f2f10: 50                           	push	eax
 11f2f11: 8b 81 bc 00 00 00            	mov	eax, dword ptr [ecx + 0xbc]
 11f2f17: f3 0f 11 45 f8               	movss	dword ptr [ebp - 0x8], xmm0
 11f2f1c: ff d0                        	call	eax
 11f2f1e: 0f b7 0f                     	movzx	ecx, word ptr [edi]
 11f2f21: 66 89 0d 90 a8 bd 01         	mov	word ptr [0x1bda890], cx
 11f2f28: 66 8b 57 04                  	mov	dx, word ptr [edi + 0x4]
 11f2f2c: 66 89 15 94 a8 bd 01         	mov	word ptr [0x1bda894], dx
 11f2f33: 66 8b 47 02                  	mov	ax, word ptr [edi + 0x2]
 11f2f37: 66 a3 92 a8 bd 01            	mov	word ptr [0x1bda892], ax
 11f2f3d: 0f b7 4f 06                  	movzx	ecx, word ptr [edi + 0x6]
 11f2f41: 66 89 0d 96 a8 bd 01         	mov	word ptr [0x1bda896], cx
 11f2f48: a1 94 b1 c1 01               	mov	eax, dword ptr [0x1c1b194]
 11f2f4d: 8b 10                        	mov	edx, dword ptr [eax]
 11f2f4f: 53                           	push	ebx
 11f2f50: 6a 00                        	push	0x0
 11f2f52: 50                           	push	eax
 11f2f53: 8b 82 04 01 00 00            	mov	eax, dword ptr [edx + 0x104]
 11f2f59: ff d0                        	call	eax
 11f2f5b: a1 50 a8 bd 01               	mov	eax, dword ptr [0x1bda850]
 11f2f60: 8b 0d 94 b1 c1 01            	mov	ecx, dword ptr [0x1c1b194]
 11f2f66: 8b 11                        	mov	edx, dword ptr [ecx]
 11f2f68: 6a 02                        	push	0x2
 11f2f6a: 8d 34 40                     	lea	esi, [eax + 2*eax]
 11f2f6d: 03 f6                        	add	esi, esi
 11f2f6f: 56                           	push	esi
 11f2f70: 6a 04                        	push	0x4
 11f2f72: 03 c0                        	add	eax, eax
 11f2f74: 03 c0                        	add	eax, eax
 11f2f76: 50                           	push	eax
 11f2f77: 6a 00                        	push	0x0
 11f2f79: 6a 04                        	push	0x4
 11f2f7b: 51                           	push	ecx
 11f2f7c: 8b 8a 48 01 00 00            	mov	ecx, dword ptr [edx + 0x148]
 11f2f82: ff d1                        	call	ecx
 11f2f84: ff 05 50 a8 bd 01            	inc	dword ptr [0x1bda850]
 11f2f8a: 8b 4d fc                     	mov	ecx, dword ptr [ebp - 0x4]
 11f2f8d: 5f                           	pop	edi
 11f2f8e: 5e                           	pop	esi
 11f2f8f: 33                           	<unknown>
