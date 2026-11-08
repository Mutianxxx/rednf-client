0004e1a8: f0b5	push	{r4, r5, r6, r7, lr}
0004e1aa: 5f46	mov	r7, fp
0004e1ac: 5646	mov	r6, sl
0004e1ae: 4d46	mov	r5, sb
0004e1b0: 4446	mov	r4, r8
0004e1b2: f0b4	push	{r4, r5, r6, r7}
0004e1b4: 89b0	sub	sp, #0x24
0004e1b6: 0592	str	r2, [sp, #0x14]
0004e1b8: b522	movs	r2, #0xb5
0004e1ba: 5201	lsls	r2, r2, #5
0004e1bc: cc4b	ldr	r3, [pc, #0x330]
0004e1be: 8258	ldr	r2, [r0, r2]
0004e1c0: 0291	str	r1, [sp, #8]
0004e1c2: 7b44	add	r3, pc
0004e1c4: 002a	cmp	r2, #0
0004e1c6: 20d1	bne	#0x4e20a
0004e1c8: ca4b	ldr	r3, [pc, #0x328]
0004e1ca: c258	ldr	r2, [r0, r3]
0004e1cc: 043b	subs	r3, #4
0004e1ce: c45a	ldrh	r4, [r0, r3]
0004e1d0: 029f	ldr	r7, [sp, #8]
0004e1d2: 8021	movs	r1, #0x80
0004e1d4: c900	lsls	r1, r1, #3
0004e1d6: 7b18	adds	r3, r7, r1
0004e1d8: 5988	ldrh	r1, [r3, #2]
0004e1da: 1025	movs	r5, #0x10
0004e1dc: 6e1a	subs	r6, r5, r1
0004e1de: 9642	cmp	r6, r2
0004e1e0: 00da	bge	#0x4e1e4
0004e1e2: 9be1	b	#0x4e51c
0004e1e4: 1d88	ldrh	r5, [r3]
0004e1e6: 9540	lsls	r5, r2
0004e1e8: 2c43	orrs	r4, r5
0004e1ea: c24a	ldr	r2, [pc, #0x308]
0004e1ec: c24d	ldr	r5, [pc, #0x308]
0004e1ee: 4453	strh	r4, [r0, r5]
0004e1f0: 8458	ldr	r4, [r0, r2]
0004e1f2: 0919	adds	r1, r1, r4
0004e1f4: 8150	str	r1, [r0, r2]
0004e1f6: 5a88	ldrh	r2, [r3, #2]
0004e1f8: c04b	ldr	r3, [pc, #0x300]
0004e1fa: 09b0	add	sp, #0x24
0004e1fc: c250	str	r2, [r0, r3]
0004e1fe: 3cbc	pop	{r2, r3, r4, r5}
0004e200: 9046	mov	r8, r2
0004e202: 9946	mov	sb, r3
0004e204: a246	mov	sl, r4
0004e206: ab46	mov	fp, r5
0004e208: f0bd	pop	{r4, r5, r6, r7, pc}
0004e20a: bd4d	ldr	r5, [pc, #0x2f4]
0004e20c: ba49	ldr	r1, [pc, #0x2e8]
0004e20e: b94a	ldr	r2, [pc, #0x2e4]
0004e210: a946	mov	sb, r5
0004e212: bc4d	ldr	r5, [pc, #0x2f0]
0004e214: bc4e	ldr	r6, [pc, #0x2f0]
0004e216: 445a	ldrh	r4, [r0, r1]
0004e218: 5d19	adds	r5, r3, r5
0004e21a: 0495	str	r5, [sp, #0x10]
0004e21c: bb4d	ldr	r5, [pc, #0x2ec]
0004e21e: 8258	ldr	r2, [r0, r2]
0004e220: 0021	movs	r1, #0
0004e222: 5d19	adds	r5, r3, r5
0004e224: 0695	str	r5, [sp, #0x18]
0004e226: ba4d	ldr	r5, [pc, #0x2e8]
0004e228: b246	mov	sl, r6
0004e22a: 9846	mov	r8, r3
0004e22c: 5d19	adds	r5, r3, r5
0004e22e: 0795	str	r5, [sp, #0x1c]
0004e230: 2be0	b	#0x4e28a
0004e232: 029f	ldr	r7, [sp, #8]
0004e234: b600	lsls	r6, r6, #2
0004e236: 1025	movs	r5, #0x10
0004e238: be19	adds	r6, r7, r6
0004e23a: 7388	ldrh	r3, [r6, #2]
0004e23c: ef1a	subs	r7, r5, r3
0004e23e: 9742	cmp	r7, r2
0004e240: 00db	blt	#0x4e244
0004e242: 21e1	b	#0x4e488
0004e244: 3688	ldrh	r6, [r6]
0004e246: 8768	ldr	r7, [r0, #8]
0004e248: b446	mov	ip, r6
0004e24a: 9640	lsls	r6, r2
0004e24c: 321c	adds	r2, r6, #0
0004e24e: 2243	orrs	r2, r4
0004e250: a94e	ldr	r6, [pc, #0x2a4]
0004e252: 1404	lsls	r4, r2, #0x10
0004e254: 4269	ldr	r2, [r0, #0x14]
0004e256: 240c	lsrs	r4, r4, #0x10
0004e258: 8453	strh	r4, [r0, r6]
0004e25a: bc54	strb	r4, [r7, r2]
0004e25c: 875b	ldrh	r7, [r0, r6]
0004e25e: 8468	ldr	r4, [r0, #8]
0004e260: 0132	adds	r2, #1
0004e262: 3f0a	lsrs	r7, r7, #8
0004e264: a754	strb	r7, [r4, r2]
0004e266: a34f	ldr	r7, [pc, #0x28c]
0004e268: 0132	adds	r2, #1
0004e26a: 4261	str	r2, [r0, #0x14]
0004e26c: c259	ldr	r2, [r0, r7]
0004e26e: 6446	mov	r4, ip
0004e270: ad1a	subs	r5, r5, r2
0004e272: 2c41	asrs	r4, r5
0004e274: 2404	lsls	r4, r4, #0x10
0004e276: 103a	subs	r2, #0x10
0004e278: 240c	lsrs	r4, r4, #0x10
0004e27a: d218	adds	r2, r2, r3
0004e27c: 8453	strh	r4, [r0, r6]
0004e27e: c251	str	r2, [r0, r7]
0004e280: b523	movs	r3, #0xb5
0004e282: 5b01	lsls	r3, r3, #5
0004e284: c358	ldr	r3, [r0, r3]
0004e286: 9942	cmp	r1, r3
0004e288: a2d2	bhs	#0x4e1d0
0004e28a: 4f46	mov	r7, sb
0004e28c: c359	ldr	r3, [r0, r7]
0004e28e: 4d00	lsls	r5, r1, #1
0004e290: 5646	mov	r6, sl
0004e292: ed5a	ldrh	r5, [r5, r3]
0004e294: 8359	ldr	r3, [r0, r6]
0004e296: 5e5c	ldrb	r6, [r3, r1]
0004e298: 0131	adds	r1, #1
0004e29a: 002d	cmp	r5, #0
0004e29c: c9d0	beq	#0x4e232
0004e29e: 9d4b	ldr	r3, [pc, #0x274]
0004e2a0: 4746	mov	r7, r8
0004e2a2: fb58	ldr	r3, [r7, r3]
0004e2a4: 9b5d	ldrb	r3, [r3, r6]
0004e2a6: 0193	str	r3, [sp, #4]
0004e2a8: 0233	adds	r3, #2
0004e2aa: ff33	adds	r3, #0xff
0004e2ac: 9f00	lsls	r7, r3, #2
0004e2ae: 029b	ldr	r3, [sp, #8]
0004e2b0: db19	adds	r3, r3, r7
0004e2b2: 9c46	mov	ip, r3
0004e2b4: 5b88	ldrh	r3, [r3, #2]
0004e2b6: 1027	movs	r7, #0x10
0004e2b8: ff1a	subs	r7, r7, r3
0004e2ba: bb46	mov	fp, r7
0004e2bc: 9345	cmp	fp, r2
0004e2be: 00db	blt	#0x4e2c2
0004e2c0: d2e0	b	#0x4e468
0004e2c2: 6746	mov	r7, ip
0004e2c4: 3f88	ldrh	r7, [r7]
0004e2c6: 0397	str	r7, [sp, #0xc]
0004e2c8: 9740	lsls	r7, r2
0004e2ca: 3a1c	adds	r2, r7, #0
0004e2cc: 2243	orrs	r2, r4
0004e2ce: 1404	lsls	r4, r2, #0x10
0004e2d0: 894a	ldr	r2, [pc, #0x224]
0004e2d2: 240c	lsrs	r4, r4, #0x10
0004e2d4: 4769	ldr	r7, [r0, #0x14]
0004e2d6: 8452	strh	r4, [r0, r2]
0004e2d8: 8268	ldr	r2, [r0, #8]
0004e2da: bb46	mov	fp, r7
0004e2dc: 171c	adds	r7, r2, #0
0004e2de: 5f44	add	r7, fp
0004e2e0: 3c70	strb	r4, [r7]
0004e2e2: 854f	ldr	r7, [pc, #0x214]
0004e2e4: 8468	ldr	r4, [r0, #8]
0004e2e6: 5a46	mov	r2, fp
0004e2e8: c75b	ldrh	r7, [r0, r7]
0004e2ea: 0132	adds	r2, #1
0004e2ec: 3f0a	lsrs	r7, r7, #8
0004e2ee: a754	strb	r7, [r4, r2]
0004e2f0: 541c	adds	r4, r2, #1
0004e2f2: 4461	str	r4, [r0, #0x14]
0004e2f4: 7f4c	ldr	r4, [pc, #0x1fc]
0004e2f6: 1027	movs	r7, #0x10
0004e2f8: 0259	ldr	r2, [r0, r4]
0004e2fa: 9346	mov	fp, r2
0004e2fc: ba1a	subs	r2, r7, r2
0004e2fe: 039f	ldr	r7, [sp, #0xc]
0004e300: 1741	asrs	r7, r2
0004e302: 7d4a	ldr	r2, [pc, #0x1f4]
0004e304: 3f04	lsls	r7, r7, #0x10
0004e306: 3f0c	lsrs	r7, r7, #0x10
0004e308: 8752	strh	r7, [r0, r2]
0004e30a: 5a46	mov	r2, fp
0004e30c: 103a	subs	r2, #0x10
0004e30e: d318	adds	r3, r2, r3
0004e310: bc46	mov	ip, r7
0004e312: 0351	str	r3, [r0, r4]
0004e314: 019a	ldr	r2, [sp, #4]
0004e316: 049c	ldr	r4, [sp, #0x10]
0004e318: 9700	lsls	r7, r2, #2
0004e31a: 3a59	ldr	r2, [r7, r4]
0004e31c: 002a	cmp	r2, #0
0004e31e: 33d0	beq	#0x4e388
0004e320: e719	adds	r7, r4, r7
0004e322: 7c6f	ldr	r4, [r7, #0x74]
0004e324: 1027	movs	r7, #0x10
0004e326: 361b	subs	r6, r6, r4
0004e328: bc1a	subs	r4, r7, r2
0004e32a: 9c42	cmp	r4, r3
0004e32c: 00db	blt	#0x4e330
0004e32e: d0e0	b	#0x4e4d2
0004e330: 341c	adds	r4, r6, #0
0004e332: 9c40	lsls	r4, r3
0004e334: 6746	mov	r7, ip
0004e336: 231c	adds	r3, r4, #0
0004e338: 3b43	orrs	r3, r7
0004e33a: 1b04	lsls	r3, r3, #0x10
0004e33c: 1b0c	lsrs	r3, r3, #0x10
0004e33e: 9c46	mov	ip, r3
0004e340: 1c1c	adds	r4, r3, #0
0004e342: 6d4b	ldr	r3, [pc, #0x1b4]
0004e344: 4769	ldr	r7, [r0, #0x14]
0004e346: 3604	lsls	r6, r6, #0x10
0004e348: c452	strh	r4, [r0, r3]
0004e34a: 8368	ldr	r3, [r0, #8]
0004e34c: 6446	mov	r4, ip
0004e34e: 360c	lsrs	r6, r6, #0x10
0004e350: dc55	strb	r4, [r3, r7]
0004e352: 694b	ldr	r3, [pc, #0x1a4]
0004e354: 0137	adds	r7, #1
0004e356: 0397	str	r7, [sp, #0xc]
0004e358: c35a	ldrh	r3, [r0, r3]
0004e35a: 039c	ldr	r4, [sp, #0xc]
0004e35c: 8768	ldr	r7, [r0, #8]
0004e35e: b446	mov	ip, r6
0004e360: 1b0a	lsrs	r3, r3, #8
0004e362: 644e	ldr	r6, [pc, #0x190]
0004e364: 3b55	strb	r3, [r7, r4]
0004e366: 231c	adds	r3, r4, #0
0004e368: 0133	adds	r3, #1
0004e36a: 4361	str	r3, [r0, #0x14]
0004e36c: 8359	ldr	r3, [r0, r6]
0004e36e: 1024	movs	r4, #0x10
0004e370: e71a	subs	r7, r4, r3
0004e372: 6446	mov	r4, ip
0004e374: 3c41	asrs	r4, r7
0004e376: 2704	lsls	r7, r4, #0x10
0004e378: 3f0c	lsrs	r7, r7, #0x10
0004e37a: 3c1c	adds	r4, r7, #0
0004e37c: bc46	mov	ip, r7
0004e37e: 5e4f	ldr	r7, [pc, #0x178]
0004e380: 103b	subs	r3, #0x10
0004e382: 9b18	adds	r3, r3, r2
0004e384: c453	strh	r4, [r0, r7]
0004e386: 8351	str	r3, [r0, r6]
0004e388: 013d	subs	r5, #1
0004e38a: ff2d	cmp	r5, #0xff
0004e38c: 00d9	bls	#0x4e390
0004e38e: 94e0	b	#0x4e4ba
0004e390: 614a	ldr	r2, [pc, #0x184]
0004e392: 4446	mov	r4, r8
0004e394: a258	ldr	r2, [r4, r2]
0004e396: 575d	ldrb	r7, [r2, r5]
0004e398: 059a	ldr	r2, [sp, #0x14]
0004e39a: bf00	lsls	r7, r7, #2
0004e39c: d419	adds	r4, r2, r7
0004e39e: 6688	ldrh	r6, [r4, #2]
0004e3a0: 1022	movs	r2, #0x10
0004e3a2: 921b	subs	r2, r2, r6
0004e3a4: 9346	mov	fp, r2
0004e3a6: 9b45	cmp	fp, r3
0004e3a8: 7ada	bge	#0x4e4a0
0004e3aa: 2488	ldrh	r4, [r4]
0004e3ac: 524a	ldr	r2, [pc, #0x148]
0004e3ae: 0394	str	r4, [sp, #0xc]
0004e3b0: 9c40	lsls	r4, r3
0004e3b2: 231c	adds	r3, r4, #0
0004e3b4: 6446	mov	r4, ip
0004e3b6: 2343	orrs	r3, r4
0004e3b8: 1b04	lsls	r3, r3, #0x10
0004e3ba: 1b0c	lsrs	r3, r3, #0x10
0004e3bc: 8352	strh	r3, [r0, r2]
0004e3be: 4469	ldr	r4, [r0, #0x14]
0004e3c0: 8268	ldr	r2, [r0, #8]
0004e3c2: 9c46	mov	ip, r3
0004e3c4: 6346	mov	r3, ip
0004e3c6: 1355	strb	r3, [r2, r4]
0004e3c8: 4b4a	ldr	r2, [pc, #0x12c]
0004e3ca: 0134	adds	r4, #1
0004e3cc: 0194	str	r4, [sp, #4]
0004e3ce: 825a	ldrh	r2, [r0, r2]
0004e3d0: 019b	ldr	r3, [sp, #4]
0004e3d2: 8468	ldr	r4, [r0, #8]
0004e3d4: 120a	lsrs	r2, r2, #8
0004e3d6: e254	strb	r2, [r4, r3]
0004e3d8: 1c1c	adds	r4, r3, #0
0004e3da: 0134	adds	r4, #1
0004e3dc: 4461	str	r4, [r0, #0x14]
0004e3de: 454c	ldr	r4, [pc, #0x114]
0004e3e0: 1023	movs	r3, #0x10
0004e3e2: 0259	ldr	r2, [r0, r4]
0004e3e4: a446	mov	ip, r4
0004e3e6: 039c	ldr	r4, [sp, #0xc]
0004e3e8: 9346	mov	fp, r2
0004e3ea: 9a1a	subs	r2, r3, r2
0004e3ec: 1441	asrs	r4, r2
0004e3ee: 424a	ldr	r2, [pc, #0x108]
0004e3f0: 2404	lsls	r4, r4, #0x10
0004e3f2: 240c	lsrs	r4, r4, #0x10
0004e3f4: 8452	strh	r4, [r0, r2]
0004e3f6: 5a46	mov	r2, fp
0004e3f8: 103a	subs	r2, #0x10
0004e3fa: 9219	adds	r2, r2, r6
0004e3fc: 6346	mov	r3, ip
0004e3fe: c250	str	r2, [r0, r3]
0004e400: 069e	ldr	r6, [sp, #0x18]
0004e402: f319	adds	r3, r6, r7
0004e404: 9b6e	ldr	r3, [r3, #0x68]
0004e406: 002b	cmp	r3, #0
0004e408: 00d1	bne	#0x4e40c
0004e40a: 39e7	b	#0x4e280
0004e40c: 079e	ldr	r6, [sp, #0x1c]
0004e40e: f719	adds	r7, r6, r7
0004e410: 3e6e	ldr	r6, [r7, #0x60]
0004e412: ad1b	subs	r5, r5, r6
0004e414: 1026	movs	r6, #0x10
0004e416: f71a	subs	r7, r6, r3
0004e418: 9742	cmp	r7, r2
0004e41a: 57da	bge	#0x4e4cc
0004e41c: 2f1c	adds	r7, r5, #0
0004e41e: 9740	lsls	r7, r2
0004e420: 3a1c	adds	r2, r7, #0
0004e422: 2243	orrs	r2, r4
0004e424: 1404	lsls	r4, r2, #0x10
0004e426: 344a	ldr	r2, [pc, #0xd0]
0004e428: 240c	lsrs	r4, r4, #0x10
0004e42a: 4769	ldr	r7, [r0, #0x14]
0004e42c: 8452	strh	r4, [r0, r2]
0004e42e: 8268	ldr	r2, [r0, #8]
0004e430: a346	mov	fp, r4
0004e432: 5c46	mov	r4, fp
0004e434: d455	strb	r4, [r2, r7]
0004e436: 304a	ldr	r2, [pc, #0xc0]
0004e438: 0137	adds	r7, #1
0004e43a: 0397	str	r7, [sp, #0xc]
0004e43c: 825a	ldrh	r2, [r0, r2]
0004e43e: 039c	ldr	r4, [sp, #0xc]
0004e440: 8768	ldr	r7, [r0, #8]
0004e442: 120a	lsrs	r2, r2, #8
0004e444: 2d04	lsls	r5, r5, #0x10
0004e446: 3a55	strb	r2, [r7, r4]
0004e448: 221c	adds	r2, r4, #0
0004e44a: 2c0c	lsrs	r4, r5, #0x10
0004e44c: 294d	ldr	r5, [pc, #0xa4]
0004e44e: 0132	adds	r2, #1
0004e450: 4261	str	r2, [r0, #0x14]
0004e452: 4259	ldr	r2, [r0, r5]
0004e454: b61a	subs	r6, r6, r2
0004e456: 3441	asrs	r4, r6
0004e458: 274e	ldr	r6, [pc, #0x9c]
0004e45a: 2404	lsls	r4, r4, #0x10
0004e45c: 103a	subs	r2, #0x10
0004e45e: 240c	lsrs	r4, r4, #0x10
0004e460: d218	adds	r2, r2, r3
0004e462: 8453	strh	r4, [r0, r6]
0004e464: 4251	str	r2, [r0, r5]
0004e466: 0be7	b	#0x4e280
0004e468: 6746	mov	r7, ip
0004e46a: 3f88	ldrh	r7, [r7]
0004e46c: 9740	lsls	r7, r2
0004e46e: 3a1c	adds	r2, r7, #0
0004e470: 2243	orrs	r2, r4
0004e472: 1204	lsls	r2, r2, #0x10
0004e474: 120c	lsrs	r2, r2, #0x10
0004e476: 9446	mov	ip, r2
0004e478: 1f4a	ldr	r2, [pc, #0x7c]
0004e47a: 6446	mov	r4, ip
0004e47c: 8452	strh	r4, [r0, r2]
0004e47e: 0432	adds	r2, #4
0004e480: 8458	ldr	r4, [r0, r2]
0004e482: 1b19	adds	r3, r3, r4
0004e484: 8350	str	r3, [r0, r2]
0004e486: 45e7	b	#0x4e314
0004e488: 3588	ldrh	r5, [r6]
0004e48a: 9540	lsls	r5, r2
0004e48c: 2c43	orrs	r4, r5
0004e48e: 1a4a	ldr	r2, [pc, #0x68]
0004e490: 184d	ldr	r5, [pc, #0x60]
0004e492: 2404	lsls	r4, r4, #0x10
0004e494: 240c	lsrs	r4, r4, #0x10
0004e496: 8452	strh	r4, [r0, r2]
0004e498: 4259	ldr	r2, [r0, r5]
0004e49a: 9a18	adds	r2, r3, r2
0004e49c: 4251	str	r2, [r0, r5]
0004e49e: efe6	b	#0x4e280
0004e4a0: 2488	ldrh	r4, [r4]
0004e4a2: 6246	mov	r2, ip
0004e4a4: 9c40	lsls	r4, r3
0004e4a6: 1443	orrs	r4, r2
0004e4a8: 134b	ldr	r3, [pc, #0x4c]
0004e4aa: 2404	lsls	r4, r4, #0x10
0004e4ac: 240c	lsrs	r4, r4, #0x10
0004e4ae: c452	strh	r4, [r0, r3]
0004e4b0: 0433	adds	r3, #4
0004e4b2: c258	ldr	r2, [r0, r3]
0004e4b4: b218	adds	r2, r6, r2
0004e4b6: c250	str	r2, [r0, r3]
0004e4b8: a2e7	b	#0x4e400
0004e4ba: 174a	ldr	r2, [pc, #0x5c]
0004e4bc: 4646	mov	r6, r8
0004e4be: b458	ldr	r4, [r6, r2]
0004e4c0: ea09	lsrs	r2, r5, #7
0004e4c2: a218	adds	r2, r4, r2
0004e4c4: 0132	adds	r2, #1
0004e4c6: ff32	adds	r2, #0xff
0004e4c8: 1778	ldrb	r7, [r2]
0004e4ca: 65e7	b	#0x4e398
0004e4cc: 9540	lsls	r5, r2
0004e4ce: 2c43	orrs	r4, r5
0004e4d0: dde7	b	#0x4e48e
0004e4d2: 9e40	lsls	r6, r3
0004e4d4: 331c	adds	r3, r6, #0
0004e4d6: 6646	mov	r6, ip
0004e4d8: 3343	orrs	r3, r6
0004e4da: 1b04	lsls	r3, r3, #0x10
0004e4dc: 1b0c	lsrs	r3, r3, #0x10
0004e4de: 9c46	mov	ip, r3
0004e4e0: 044c	ldr	r4, [pc, #0x10]
0004e4e2: 054b	ldr	r3, [pc, #0x14]
0004e4e4: 6746	mov	r7, ip
0004e4e6: c752	strh	r7, [r0, r3]
0004e4e8: 0359	ldr	r3, [r0, r4]
0004e4ea: d318	adds	r3, r2, r3
0004e4ec: 0351	str	r3, [r0, r4]
0004e4ee: 4be7	b	#0x4e388
0004e4f0: c6ca	ldm	r2, {r1, r2, r6, r7}
0004e4f2: 1000	movs	r0, r2
0004e4f4: bc16	asrs	r4, r7, #0x1a
0004e4f6: 0000	movs	r0, r0
0004e4f8: b816	asrs	r0, r7, #0x1a
0004e4fa: 0000	movs	r0, r0
0004e4fc: b416	asrs	r4, r6, #0x1a
0004e4fe: 0000	movs	r0, r0
0004e500: a416	asrs	r4, r4, #0x1a
0004e502: 0000	movs	r0, r0
0004e504: 40fb	.byte	0x40, 0xfb
0004e506: fcff9816	vqshlu.s64	d17, d8, #0x3c
0004e50a: 0000	movs	r0, r0
0004e50c: c0fb	.byte	0xc0, 0xfb
0004e50e: fcff	.byte	0xfc, 0xff
0004e510: 40fcfcff	mcrr2	p15, #0xf, pc, r0, c12
0004e514: d807	lsls	r0, r3, #0x1f
0004e516: 0000	movs	r0, r0
0004e518: d008	lsrs	r0, r2, #3
0004e51a: 0000	movs	r0, r0
0004e51c: 1f88	ldrh	r7, [r3]
0004e51e: 3e1c	adds	r6, r7, #0
0004e520: 9640	lsls	r6, r2
0004e522: 3443	orrs	r4, r6
0004e524: 2604	lsls	r6, r4, #0x10
0004e526: 4469	ldr	r4, [r0, #0x14]
0004e528: 0d4a	ldr	r2, [pc, #0x34]
0004e52a: 360c	lsrs	r6, r6, #0x10
0004e52c: a046	mov	r8, r4
0004e52e: 8468	ldr	r4, [r0, #8]
0004e530: 8652	strh	r6, [r0, r2]
0004e532: 4444	add	r4, r8
0004e534: 2670	strb	r6, [r4]
0004e536: 0126	movs	r6, #1
0004e538: b246	mov	sl, r6
0004e53a: 8468	ldr	r4, [r0, #8]
0004e53c: 865a	ldrh	r6, [r0, r2]
0004e53e: c244	add	sl, r8
0004e540: 5444	add	r4, sl
0004e542: 360a	lsrs	r6, r6, #8
0004e544: 2670	strb	r6, [r4]
0004e546: 5446	mov	r4, sl
0004e548: 0134	adds	r4, #1
0004e54a: 4461	str	r4, [r0, #0x14]
0004e54c: 054c	ldr	r4, [pc, #0x14]
0004e54e: 0659	ldr	r6, [r0, r4]
0004e550: ad1b	subs	r5, r5, r6
0004e552: 103e	subs	r6, #0x10
0004e554: 2f41	asrs	r7, r5
0004e556: 7118	adds	r1, r6, r1
0004e558: 8752	strh	r7, [r0, r2]
0004e55a: 0151	str	r1, [r0, r4]
0004e55c: 4be6	b	#0x4e1f6
0004e55e: c046	mov	r8, r8
0004e560: b816	asrs	r0, r7, #0x1a
0004e562: 0000	movs	r0, r0
0004e564: bc16	asrs	r4, r7, #0x1a
0004e566: 0000	movs	r0, r0
