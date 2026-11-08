000f0124: f0b5	push	{r4, r5, r6, r7, lr}
000f0126: 5f46	mov	r7, fp
000f0128: 5646	mov	r6, sl
000f012a: 4d46	mov	r5, sb
000f012c: 4446	mov	r4, r8
000f012e: f0b4	push	{r4, r5, r6, r7}
000f0130: 93b0	sub	sp, #0x4c
000f0132: 0490	str	r0, [sp, #0x10]
000f0134: 6846	mov	r0, sp
000f0136: 3430	adds	r0, #0x34
000f0138: 0290	str	r0, [sp, #8]
000f013a: 0c1c	adds	r4, r1, #0
000f013c: 0498	ldr	r0, [sp, #0x10]
000f013e: 0299	ldr	r1, [sp, #8]
000f0140: 1f1c	adds	r7, r3, #0
000f0142: 161c	adds	r6, r2, #0
000f0144: fef7f6ff	bl	#0xef134
000f0148: 0299	ldr	r1, [sp, #8]
000f014a: 8b68	ldr	r3, [r1, #8]
000f014c: 002b	cmp	r3, #0
000f014e: 2bd0	beq	#0xf01a8
000f0150: 4868	ldr	r0, [r1, #4]
000f0152: 0d9a	ldr	r2, [sp, #0x34]
000f0154: a168	ldr	r1, [r4, #8]
000f0156: 8146	mov	sb, r0
000f0158: 1192	str	r2, [sp, #0x44]
000f015a: 0729	cmp	r1, #7
000f015c: 00d1	bne	#0xf0160
000f015e: aee0	b	#0xf02be
000f0160: 032b	cmp	r3, #3
000f0162: 00d1	bne	#0xf0166
000f0164: c5e0	b	#0xf02f2
000f0166: 0023	movs	r3, #0
000f0168: 0127	movs	r7, #1
000f016a: 784a	ldr	r2, [pc, #0x1e0]
000f016c: 9b00	lsls	r3, r3, #2
000f016e: 11a9	add	r1, sp, #0x44
000f0170: 9246	mov	sl, r2
000f0172: fa44	add	sl, pc
000f0174: 6846	mov	r0, sp
000f0176: f618	adds	r6, r6, r3
000f0178: 8b46	mov	fp, r1
000f017a: 09ab	add	r3, sp, #0x24
000f017c: 5146	mov	r1, sl
000f017e: 4030	adds	r0, #0x40
000f0180: ca46	mov	sl, sb
000f0182: 0790	str	r0, [sp, #0x1c]
000f0184: 0391	str	r1, [sp, #0xc]
000f0186: 9946	mov	sb, r3
000f0188: b846	mov	r8, r7
000f018a: 2369	ldr	r3, [r4, #0x10]
000f018c: 80ce	ldm	r6!, {r7}
000f018e: 5846	mov	r0, fp
000f0190: 5146	mov	r1, sl
000f0192: ff18	adds	r7, r7, r3
000f0194: fef740fe	bl	#0xeee18
000f0198: a368	ldr	r3, [r4, #8]
000f019a: 072b	cmp	r3, #7
000f019c: 04d8	bhi	#0xf01a8
000f019e: 0398	ldr	r0, [sp, #0xc]
000f01a0: 9b00	lsls	r3, r3, #2
000f01a2: 1b58	ldr	r3, [r3, r0]
000f01a4: 1b18	adds	r3, r3, r0
000f01a6: 9f46	mov	pc, r3
000f01a8: 0325	movs	r5, #3
000f01aa: 13b0	add	sp, #0x4c
000f01ac: 281c	adds	r0, r5, #0
000f01ae: 3cbc	pop	{r2, r3, r4, r5}
000f01b0: 9046	mov	r8, r2
000f01b2: 9946	mov	sb, r3
000f01b4: a246	mov	sl, r4
000f01b6: ab46	mov	fp, r5
000f01b8: f0bd	pop	{r4, r5, r6, r7, pc}
000f01ba: 0020	movs	r0, #0
000f01bc: 0090	str	r0, [sp]
000f01be: 5146	mov	r1, sl
000f01c0: 5846	mov	r0, fp
000f01c2: 0422	movs	r2, #4
000f01c4: 4b46	mov	r3, sb
000f01c6: fff78bfd	bl	#0xefce0
000f01ca: 0028	cmp	r0, #0
000f01cc: ecdb	blt	#0xf01a8
000f01ce: 4946	mov	r1, sb
000f01d0: 0868	ldr	r0, [r1]
000f01d2: f5f7ebfd	bl	#0xe5dac
000f01d6: 4a46	mov	r2, sb
000f01d8: 3860	str	r0, [r7]
000f01da: 5068	ldr	r0, [r2, #4]
000f01dc: f5f7e6fd	bl	#0xe5dac
000f01e0: 4b46	mov	r3, sb
000f01e2: 7860	str	r0, [r7, #4]
000f01e4: 9868	ldr	r0, [r3, #8]
000f01e6: f5f7e1fd	bl	#0xe5dac
000f01ea: 4946	mov	r1, sb
000f01ec: b860	str	r0, [r7, #8]
000f01ee: c868	ldr	r0, [r1, #0xc]
000f01f0: f5f7dcfd	bl	#0xe5dac
000f01f4: f860	str	r0, [r7, #0xc]
000f01f6: 0122	movs	r2, #1
000f01f8: 5242	rsbs	r2, r2, #0
000f01fa: 9044	add	r8, r2
000f01fc: 4346	mov	r3, r8
000f01fe: 002b	cmp	r3, #0
000f0200: c3d1	bne	#0xf018a
000f0202: 0025	movs	r5, #0
000f0204: d1e7	b	#0xf01aa
000f0206: 0499	ldr	r1, [sp, #0x10]
000f0208: 119b	ldr	r3, [sp, #0x44]
000f020a: 0d69	ldr	r5, [r1, #0x10]
000f020c: 9a45	cmp	sl, r3
000f020e: f2d9	bls	#0xf01f6
000f0210: 0298	ldr	r0, [sp, #8]
000f0212: 5246	mov	r2, sl
000f0214: d11a	subs	r1, r2, r3
000f0216: 8268	ldr	r2, [r0, #8]
000f0218: 042a	cmp	r2, #4
000f021a: 00d1	bne	#0xf021e
000f021c: 84e0	b	#0xf0328
000f021e: 022a	cmp	r2, #2
000f0220: c2d1	bne	#0xf01a8
000f0222: 0133	adds	r3, #1
000f0224: 0239	subs	r1, #2
000f0226: 1193	str	r3, [sp, #0x44]
000f0228: 0591	str	r1, [sp, #0x14]
000f022a: 3968	ldr	r1, [r7]
000f022c: 0029	cmp	r1, #0
000f022e: 04d0	beq	#0xf023a
000f0230: 281c	adds	r0, r5, #0
000f0232: f7f739ff	bl	#0xe80a8
000f0236: 0021	movs	r1, #0
000f0238: 3960	str	r1, [r7]
000f023a: 0599	ldr	r1, [sp, #0x14]
000f023c: 281c	adds	r0, r5, #0
000f023e: 079a	ldr	r2, [sp, #0x1c]
000f0240: 0131	adds	r1, #1
000f0242: f8f7b1fd	bl	#0xe8da8
000f0246: 109d	ldr	r5, [sp, #0x40]
000f0248: 0690	str	r0, [sp, #0x18]
000f024a: 002d	cmp	r5, #0
000f024c: add1	bne	#0xf01aa
000f024e: 059a	ldr	r2, [sp, #0x14]
000f0250: 1199	ldr	r1, [sp, #0x44]
000f0252: 44f748ef	blx	#0x350e4
000f0256: 069a	ldr	r2, [sp, #0x18]
000f0258: 059b	ldr	r3, [sp, #0x14]
000f025a: d554	strb	r5, [r2, r3]
000f025c: 3a60	str	r2, [r7]
000f025e: cae7	b	#0xf01f6
000f0260: 5846	mov	r0, fp
000f0262: 5146	mov	r1, sl
000f0264: 0322	movs	r2, #3
000f0266: fff7c5fb	bl	#0xef9f4
000f026a: 237d	ldrb	r3, [r4, #0x14]
000f026c: 022b	cmp	r3, #2
000f026e: 0fd0	beq	#0xf0290
000f0270: 042b	cmp	r3, #4
000f0272: 01d0	beq	#0xf0278
000f0274: 012b	cmp	r3, #1
000f0276: 01d0	beq	#0xf027c
000f0278: 3860	str	r0, [r7]
000f027a: bce7	b	#0xf01f6
000f027c: 3870	strb	r0, [r7]
000f027e: bae7	b	#0xf01f6
000f0280: 5846	mov	r0, fp
000f0282: 5146	mov	r1, sl
000f0284: 0022	movs	r2, #0
000f0286: fff7b5fb	bl	#0xef9f4
000f028a: 237d	ldrb	r3, [r4, #0x14]
000f028c: 022b	cmp	r3, #2
000f028e: efd1	bne	#0xf0270
000f0290: 3880	strh	r0, [r7]
000f0292: b0e7	b	#0xf01f6
000f0294: 5846	mov	r0, fp
000f0296: 5146	mov	r1, sl
000f0298: fff742fa	bl	#0xef720
000f029c: e5e7	b	#0xf026a
000f029e: 119b	ldr	r3, [sp, #0x44]
000f02a0: da1c	adds	r2, r3, #3
000f02a2: 9245	cmp	sl, r2
000f02a4: 02d9	bls	#0xf02ac
000f02a6: 1978	ldrb	r1, [r3]
000f02a8: 7429	cmp	r1, #0x74
000f02aa: 42d0	beq	#0xf0332
000f02ac: 191d	adds	r1, r3, #4
000f02ae: 8a45	cmp	sl, r1
000f02b0: 02d9	bls	#0xf02b8
000f02b2: 1878	ldrb	r0, [r3]
000f02b4: 6628	cmp	r0, #0x66
000f02b6: 27d0	beq	#0xf0308
000f02b8: 0020	movs	r0, #0
000f02ba: 1193	str	r3, [sp, #0x44]
000f02bc: d5e7	b	#0xf026a
000f02be: 049b	ldr	r3, [sp, #0x10]
000f02c0: 0499	ldr	r1, [sp, #0x10]
000f02c2: 0498	ldr	r0, [sp, #0x10]
000f02c4: 9b68	ldr	r3, [r3, #8]
000f02c6: 0968	ldr	r1, [r1]
000f02c8: 0132	adds	r2, #1
000f02ca: 9a46	mov	sl, r3
000f02cc: 4b46	mov	r3, sb
000f02ce: 013b	subs	r3, #1
000f02d0: 0260	str	r2, [r0]
000f02d2: 8360	str	r3, [r0, #8]
000f02d4: 09ad	add	r5, sp, #0x24
000f02d6: 8846	mov	r8, r1
000f02d8: 0498	ldr	r0, [sp, #0x10]
000f02da: 291c	adds	r1, r5, #0
000f02dc: fef72aff	bl	#0xef134
000f02e0: 049a	ldr	r2, [sp, #0x10]
000f02e2: 5346	mov	r3, sl
000f02e4: 4146	mov	r1, r8
000f02e6: 1160	str	r1, [r2]
000f02e8: 9360	str	r3, [r2, #8]
000f02ea: ab68	ldr	r3, [r5, #8]
000f02ec: 032b	cmp	r3, #3
000f02ee: 00d0	beq	#0xf02f2
000f02f0: 39e7	b	#0xf0166
000f02f2: 002f	cmp	r7, #0
000f02f4: 00d1	bne	#0xf02f8
000f02f6: 57e7	b	#0xf01a8
000f02f8: 119b	ldr	r3, [sp, #0x44]
000f02fa: 0120	movs	r0, #1
000f02fc: 4042	rsbs	r0, r0, #0
000f02fe: 0133	adds	r3, #1
000f0300: 1193	str	r3, [sp, #0x44]
000f0302: 8144	add	sb, r0
000f0304: 0123	movs	r3, #1
000f0306: 30e7	b	#0xf016a
000f0308: 5878	ldrb	r0, [r3, #1]
000f030a: 6128	cmp	r0, #0x61
000f030c: d4d1	bne	#0xf02b8
000f030e: 9878	ldrb	r0, [r3, #2]
000f0310: 6c28	cmp	r0, #0x6c
000f0312: d1d1	bne	#0xf02b8
000f0314: 1278	ldrb	r2, [r2]
000f0316: 732a	cmp	r2, #0x73
000f0318: ced1	bne	#0xf02b8
000f031a: 0a78	ldrb	r2, [r1]
000f031c: 652a	cmp	r2, #0x65
000f031e: cbd1	bne	#0xf02b8
000f0320: 0633	adds	r3, #6
000f0322: 0020	movs	r0, #0
000f0324: 1193	str	r3, [sp, #0x44]
000f0326: a0e7	b	#0xf026a
000f0328: 0139	subs	r1, #1
000f032a: 0133	adds	r3, #1
000f032c: 0591	str	r1, [sp, #0x14]
000f032e: 1193	str	r3, [sp, #0x44]
000f0330: 7be7	b	#0xf022a
000f0332: 5978	ldrb	r1, [r3, #1]
000f0334: 7229	cmp	r1, #0x72
000f0336: b9d1	bne	#0xf02ac
000f0338: 9978	ldrb	r1, [r3, #2]
000f033a: 7529	cmp	r1, #0x75
000f033c: b6d1	bne	#0xf02ac
000f033e: 1178	ldrb	r1, [r2]
000f0340: 6529	cmp	r1, #0x65
000f0342: b3d1	bne	#0xf02ac
000f0344: 0533	adds	r3, #5
000f0346: 0120	movs	r0, #1
000f0348: 1193	str	r3, [sp, #0x44]
000f034a: 8ee7	b	#0xf026a
000f034c: 3a82	strh	r2, [r7, #0x10]
000f034e: 0400	movs	r4, r0
