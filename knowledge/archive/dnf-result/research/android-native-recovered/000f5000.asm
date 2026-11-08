000f5000: f0b5	push	{r4, r5, r6, r7, lr}
000f5002: 5f46	mov	r7, fp
000f5004: 5646	mov	r6, sl
000f5006: 4d46	mov	r5, sb
000f5008: 4446	mov	r4, r8
000f500a: f0b4	push	{r4, r5, r6, r7}
000f500c: 0c1c	adds	r4, r1, #0
000f500e: 171c	adds	r7, r2, #0
000f5010: 896c	ldr	r1, [r1, #0x48]
000f5012: 8269	ldr	r2, [r0, #0x18]
000f5014: 97b0	sub	sp, #0x5c
000f5016: 051c	adds	r5, r0, #0
000f5018: 9142	cmp	r1, r2
000f501a: 08d0	beq	#0xf502e
000f501c: 0627	movs	r7, #6
000f501e: 17b0	add	sp, #0x5c
000f5020: 381c	adds	r0, r7, #0
000f5022: 3cbc	pop	{r2, r3, r4, r5}
000f5024: 9046	mov	r8, r2
000f5026: 9946	mov	sb, r3
000f5028: a246	mov	sl, r4
000f502a: ab46	mov	fp, r5
000f502c: f0bd	pop	{r4, r5, r6, r7, pc}
000f502e: 022f	cmp	r7, #2
000f5030: 00d1	bne	#0xf5034
000f5032: 8ee0	b	#0xf5152
000f5034: 574a	ldr	r2, [pc, #0x15c]
000f5036: 4169	ldr	r1, [r0, #0x14]
000f5038: 7a44	add	r2, pc
000f503a: 1268	ldr	r2, [r2]
000f503c: 9142	cmp	r1, r2
000f503e: 00d1	bne	#0xf5042
000f5040: 8ee0	b	#0xf5160
000f5042: 6c21	movs	r1, #0x6c
000f5044: 0919	adds	r1, r1, r4
000f5046: 8946	mov	sb, r1
000f5048: 002b	cmp	r3, #0
000f504a: 04d0	beq	#0xf5056
000f504c: 1968	ldr	r1, [r3]
000f504e: 5a68	ldr	r2, [r3, #4]
000f5050: 4846	mov	r0, sb
000f5052: f2f73df9	bl	#0xe72d0
000f5056: 11ae	add	r6, sp, #0x44
000f5058: 4846	mov	r0, sb
000f505a: 311c	adds	r1, r6, #0
000f505c: f2f702f9	bl	#0xe7264
000f5060: 7268	ldr	r2, [r6, #4]
000f5062: 3f23	movs	r3, #0x3f
000f5064: 1199	ldr	r1, [sp, #0x44]
000f5066: 2032	adds	r2, #0x20
000f5068: 9a43	bics	r2, r3
000f506a: b068	ldr	r0, [r6, #8]
000f506c: 9046	mov	r8, r2
000f506e: 7260	str	r2, [r6, #4]
000f5070: f268	ldr	r2, [r6, #0xc]
000f5072: 2031	adds	r1, #0x20
000f5074: 2030	adds	r0, #0x20
000f5076: 9943	bics	r1, r3
000f5078: 9843	bics	r0, r3
000f507a: 9446	mov	ip, r2
000f507c: 2022	movs	r2, #0x20
000f507e: 1191	str	r1, [sp, #0x44]
000f5080: 9444	add	ip, r2
000f5082: 411a	subs	r1, r0, r1
000f5084: 8911	asrs	r1, r1, #6
000f5086: 6246	mov	r2, ip
000f5088: 9a43	bics	r2, r3
000f508a: 8a46	mov	sl, r1
000f508c: 4146	mov	r1, r8
000f508e: 131c	adds	r3, r2, #0
000f5090: 521a	subs	r2, r2, r1
000f5092: 9211	asrs	r2, r2, #6
000f5094: 9046	mov	r8, r2
000f5096: 404a	ldr	r2, [pc, #0x100]
000f5098: b060	str	r0, [r6, #8]
000f509a: 9045	cmp	r8, r2
000f509c: bed8	bhi	#0xf501c
000f509e: 9245	cmp	sl, r2
000f50a0: bcd8	bhi	#0xf501c
000f50a2: f360	str	r3, [r6, #0xc]
000f50a4: aa68	ldr	r2, [r5, #8]
000f50a6: 9c23	movs	r3, #0x9c
000f50a8: 9b46	mov	fp, r3
000f50aa: e358	ldr	r3, [r4, r3]
000f50ac: 0392	str	r2, [sp, #0xc]
000f50ae: 0121	movs	r1, #1
000f50b0: 5b68	ldr	r3, [r3, #4]
000f50b2: 1942	tst	r1, r3
000f50b4: 5ed1	bne	#0xf5174
000f50b6: 0222	movs	r2, #2
000f50b8: 1742	tst	r7, r2
000f50ba: 53d1	bne	#0xf5164
000f50bc: 5346	mov	r3, sl
000f50be: 0321	movs	r1, #3
000f50c0: 0333	adds	r3, #3
000f50c2: 8b43	bics	r3, r1
000f50c4: 5e21	movs	r1, #0x5e
000f50c6: 6254	strb	r2, [r4, r1]
000f50c8: 8022	movs	r2, #0x80
000f50ca: 5200	lsls	r2, r2, #1
000f50cc: 5c21	movs	r1, #0x5c
000f50ce: 6252	strh	r2, [r4, r1]
000f50d0: 5246	mov	r2, sl
000f50d2: 2265	str	r2, [r4, #0x50]
000f50d4: 0022	movs	r2, #0
000f50d6: 4146	mov	r1, r8
000f50d8: 0092	str	r2, [sp]
000f50da: 15aa	add	r2, sp, #0x54
000f50dc: 0192	str	r2, [sp, #4]
000f50de: e164	str	r1, [r4, #0x4c]
000f50e0: 6365	str	r3, [r4, #0x54]
000f50e2: 0398	ldr	r0, [sp, #0xc]
000f50e4: 0022	movs	r2, #0
000f50e6: f4f7eff8	bl	#0xe92c8
000f50ea: 159f	ldr	r7, [sp, #0x54]
000f50ec: a065	str	r0, [r4, #0x58]
000f50ee: 002f	cmp	r7, #0
000f50f0: 95d1	bne	#0xf501e
000f50f2: 9c23	movs	r3, #0x9c
000f50f4: e358	ldr	r3, [r4, r3]
000f50f6: 0122	movs	r2, #1
000f50f8: 9046	mov	r8, r2
000f50fa: 5a68	ldr	r2, [r3, #4]
000f50fc: 4146	mov	r1, r8
000f50fe: 4846	mov	r0, sb
000f5100: 0a43	orrs	r2, r1
000f5102: 5a60	str	r2, [r3, #4]
000f5104: 1199	ldr	r1, [sp, #0x44]
000f5106: 7268	ldr	r2, [r6, #4]
000f5108: 4942	rsbs	r1, r1, #0
000f510a: 5242	rsbs	r2, r2, #0
000f510c: f2f7e0f8	bl	#0xe72d0
000f5110: 231c	adds	r3, r4, #0
000f5112: 05a9	add	r1, sp, #0x14
000f5114: 4c33	adds	r3, #0x4c
000f5116: 4a46	mov	r2, sb
000f5118: 0593	str	r3, [sp, #0x14]
000f511a: 4a60	str	r2, [r1, #4]
000f511c: 8f60	str	r7, [r1, #8]
000f511e: 5e23	movs	r3, #0x5e
000f5120: e35c	ldrb	r3, [r4, r3]
000f5122: 022b	cmp	r3, #2
000f5124: 33d0	beq	#0xf518e
000f5126: 2b6c	ldr	r3, [r5, #0x40]
000f5128: e86b	ldr	r0, [r5, #0x3c]
000f512a: 9847	blx	r3
000f512c: 7268	ldr	r2, [r6, #4]
000f512e: 1590	str	r0, [sp, #0x54]
000f5130: 1199	ldr	r1, [sp, #0x44]
000f5132: 4846	mov	r0, sb
000f5134: f2f7ccf8	bl	#0xe72d0
000f5138: 159f	ldr	r7, [sp, #0x54]
000f513a: 002f	cmp	r7, #0
000f513c: 00d0	beq	#0xf5140
000f513e: 6ee7	b	#0xf501e
000f5140: 164b	ldr	r3, [pc, #0x58]
000f5142: a364	str	r3, [r4, #0x48]
000f5144: 119b	ldr	r3, [sp, #0x44]
000f5146: 9b11	asrs	r3, r3, #6
000f5148: 6366	str	r3, [r4, #0x64]
000f514a: f368	ldr	r3, [r6, #0xc]
000f514c: 9b11	asrs	r3, r3, #6
000f514e: a366	str	r3, [r4, #0x68]
000f5150: 65e7	b	#0xf501e
000f5152: 134a	ldr	r2, [pc, #0x4c]
000f5154: 4169	ldr	r1, [r0, #0x14]
000f5156: 7a44	add	r2, pc
000f5158: 1268	ldr	r2, [r2]
000f515a: 9142	cmp	r1, r2
000f515c: 00d0	beq	#0xf5160
000f515e: 70e7	b	#0xf5042
000f5160: 1327	movs	r7, #0x13
000f5162: 5ce7	b	#0xf501e
000f5164: 5346	mov	r3, sl
000f5166: 0f33	adds	r3, #0xf
000f5168: 1b09	lsrs	r3, r3, #4
000f516a: 0121	movs	r1, #1
000f516c: 5e22	movs	r2, #0x5e
000f516e: 5b00	lsls	r3, r3, #1
000f5170: a154	strb	r1, [r4, r2]
000f5172: ade7	b	#0xf50d0
000f5174: a16d	ldr	r1, [r4, #0x58]
000f5176: 101c	adds	r0, r2, #0
000f5178: f2f796ff	bl	#0xe80a8
000f517c: 0023	movs	r3, #0
000f517e: a365	str	r3, [r4, #0x58]
000f5180: 5a46	mov	r2, fp
000f5182: a358	ldr	r3, [r4, r2]
000f5184: 0121	movs	r1, #1
000f5186: 5a68	ldr	r2, [r3, #4]
000f5188: 8a43	bics	r2, r1
000f518a: 5a60	str	r2, [r3, #4]
000f518c: 93e7	b	#0xf50b6
000f518e: 4346	mov	r3, r8
000f5190: 8b60	str	r3, [r1, #8]
000f5192: c8e7	b	#0xf5126
000f5194: 2c63	str	r4, [r5, #0x30]
000f5196: 0600	movs	r6, r0
000f5198: ffff	.byte	0xff, 0xff
000f519a: 0000	movs	r0, r0
000f519c: 7374	strb	r3, [r6, #0x11]
000f519e: 6962	str	r1, [r5, #0x24]
000f51a0: 125f	ldrsh	r2, [r2, r4]
000f51a2: 0600	movs	r6, r0
