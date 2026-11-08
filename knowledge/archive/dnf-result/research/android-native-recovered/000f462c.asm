000f462c: f0b5	push	{r4, r5, r6, r7, lr}
000f462e: 5f46	mov	r7, fp
000f4630: 5646	mov	r6, sl
000f4632: 4d46	mov	r5, sb
000f4634: 4446	mov	r4, r8
000f4636: f0b4	push	{r4, r5, r6, r7}
000f4638: 041c	adds	r4, r0, #0
000f463a: 656b	ldr	r5, [r4, #0x34]
000f463c: 83b0	sub	sp, #0xc
000f463e: c900	lsls	r1, r1, #3
000f4640: 0192	str	r2, [sp, #4]
000f4642: 8a46	mov	sl, r1
000f4644: 6918	adds	r1, r5, r1
000f4646: a76a	ldr	r7, [r4, #0x28]
000f4648: 0c98	ldr	r0, [sp, #0x30]
000f464a: 4a68	ldr	r2, [r1, #4]
000f464c: 6e68	ldr	r6, [r5, #4]
000f464e: b946	mov	sb, r7
000f4650: 8242	cmp	r2, r0
000f4652: 01dc	bgt	#0xf4658
000f4654: 9e42	cmp	r6, r3
000f4656: 0fda	bge	#0xf4678
000f4658: 5046	mov	r0, sl
000f465a: 4042	rsbs	r0, r0, #0
000f465c: 0090	str	r0, [sp]
000f465e: 009a	ldr	r2, [sp]
000f4660: 4946	mov	r1, sb
000f4662: a162	str	r1, [r4, #0x28]
000f4664: ad18	adds	r5, r5, r2
000f4666: 6563	str	r5, [r4, #0x34]
000f4668: 0020	movs	r0, #0
000f466a: 03b0	add	sp, #0xc
000f466c: 3cbc	pop	{r2, r3, r4, r5}
000f466e: 9046	mov	r8, r2
000f4670: 9946	mov	sb, r3
000f4672: a246	mov	sl, r4
000f4674: ab46	mov	fp, r5
000f4676: f0bd	pop	{r4, r5, r6, r7, pc}
000f4678: 6768	ldr	r7, [r4, #4]
000f467a: 8346	mov	fp, r0
000f467c: b846	mov	r8, r7
000f467e: 7f42	rsbs	r7, r7, #0
000f4680: 3e40	ands	r6, r7
000f4682: bc46	mov	ip, r7
000f4684: b345	cmp	fp, r6
000f4686: 13dc	bgt	#0xf46b0
000f4688: 9a42	cmp	r2, r3
000f468a: 14da	bge	#0xf46b6
000f468c: 1f1c	adds	r7, r3, #0
000f468e: 5622	movs	r2, #0x56
000f4690: a15c	ldrb	r1, [r4, r2]
000f4692: 0029	cmp	r1, #0
000f4694: 05d0	beq	#0xf46a2
000f4696: 2068	ldr	r0, [r4]
000f4698: a16d	ldr	r1, [r4, #0x58]
000f469a: 0341	asrs	r3, r0
000f469c: 4b61	str	r3, [r1, #0x14]
000f469e: 0023	movs	r3, #0
000f46a0: a354	strb	r3, [r4, r2]
000f46a2: 5f45	cmp	r7, fp
000f46a4: 24dd	ble	#0xf46f0
000f46a6: 5146	mov	r1, sl
000f46a8: 4942	rsbs	r1, r1, #0
000f46aa: 0091	str	r1, [sp]
000f46ac: 656b	ldr	r5, [r4, #0x34]
000f46ae: d6e7	b	#0xf465e
000f46b0: b346	mov	fp, r6
000f46b2: 9a42	cmp	r2, r3
000f46b4: eadb	blt	#0xf468c
000f46b6: 4746	mov	r7, r8
000f46b8: 4046	mov	r0, r8
000f46ba: 013f	subs	r7, #1
000f46bc: 1318	adds	r3, r2, r0
000f46be: 3a40	ands	r2, r7
000f46c0: 1204	lsls	r2, r2, #0x10
000f46c2: 013b	subs	r3, #1
000f46c4: 6646	mov	r6, ip
000f46c6: 1214	asrs	r2, r2, #0x10
000f46c8: 3340	ands	r3, r6
000f46ca: 002a	cmp	r2, #0
000f46cc: ded1	bne	#0xf468c
000f46ce: 5720	movs	r0, #0x57
000f46d0: 265c	ldrb	r6, [r4, r0]
000f46d2: 002e	cmp	r6, #0
000f46d4: 03d0	beq	#0xf46de
000f46d6: 0427	movs	r7, #4
000f46d8: 7f42	rsbs	r7, r7, #0
000f46da: b944	add	sb, r7
000f46dc: 2254	strb	r2, [r4, r0]
000f46de: 4846	mov	r0, sb
000f46e0: 0a68	ldr	r2, [r1]
000f46e2: 0430	adds	r0, #4
000f46e4: 8146	mov	sb, r0
000f46e6: 0438	subs	r0, #4
000f46e8: 04c0	stm	r0!, {r2}
000f46ea: 6768	ldr	r7, [r4, #4]
000f46ec: df19	adds	r7, r3, r7
000f46ee: cee7	b	#0xf468e
000f46f0: 5b46	mov	r3, fp
000f46f2: da1b	subs	r2, r3, r7
000f46f4: 2368	ldr	r3, [r4]
000f46f6: 1a41	asrs	r2, r3
000f46f8: 131c	adds	r3, r2, #0
000f46fa: 0133	adds	r3, #1
000f46fc: 626a	ldr	r2, [r4, #0x24]
000f46fe: 9b00	lsls	r3, r3, #2
000f4700: 4b44	add	r3, sb
000f4702: 9a42	cmp	r2, r3
000f4704: 29d9	bls	#0xf475a
000f4706: 5046	mov	r0, sl
000f4708: 5721	movs	r1, #0x57
000f470a: 4042	rsbs	r0, r0, #0
000f470c: 0022	movs	r2, #0
000f470e: 2e1c	adds	r6, r5, #0
000f4710: 0090	str	r0, [sp]
000f4712: 6254	strb	r2, [r4, r1]
000f4714: 7168	ldr	r1, [r6, #4]
000f4716: b846	mov	r8, r7
000f4718: 4d46	mov	r5, sb
000f471a: b146	mov	sb, r6
000f471c: 4145	cmp	r1, r8
000f471e: 29dd	ble	#0xf4774
000f4720: 5346	mov	r3, sl
000f4722: f718	adds	r7, r6, r3
000f4724: 7b68	ldr	r3, [r7, #4]
000f4726: 2269	ldr	r2, [r4, #0x10]
000f4728: c91a	subs	r1, r1, r3
000f472a: 9142	cmp	r1, r2
000f472c: 27da	bge	#0xf477e
000f472e: 3f68	ldr	r7, [r7]
000f4730: 3268	ldr	r2, [r6]
000f4732: 4046	mov	r0, r8
000f4734: c31a	subs	r3, r0, r3
000f4736: d21b	subs	r2, r2, r7
000f4738: 101c	adds	r0, r2, #0
000f473a: 5843	muls	r0, r3, r0
000f473c: 2df090e9	blx	#0x121a60
000f4740: c719	adds	r7, r0, r7
000f4742: 80c5	stm	r5!, {r7}
000f4744: 0099	ldr	r1, [sp]
000f4746: 6368	ldr	r3, [r4, #4]
000f4748: 7718	adds	r7, r6, r1
000f474a: 9844	add	r8, r3
000f474c: c345	cmp	fp, r8
000f474e: 01db	blt	#0xf4754
000f4750: b945	cmp	sb, r7
000f4752: 08d9	bls	#0xf4766
000f4754: a946	mov	sb, r5
000f4756: 656b	ldr	r5, [r4, #0x34]
000f4758: 81e7	b	#0xf465e
000f475a: 4e46	mov	r6, sb
000f475c: 6223	movs	r3, #0x62
000f475e: a662	str	r6, [r4, #0x28]
000f4760: e362	str	r3, [r4, #0x2c]
000f4762: 0120	movs	r0, #1
000f4764: 81e7	b	#0xf466a
000f4766: 5721	movs	r1, #0x57
000f4768: 0022	movs	r2, #0
000f476a: 3e1c	adds	r6, r7, #0
000f476c: 6254	strb	r2, [r4, r1]
000f476e: 7168	ldr	r1, [r6, #4]
000f4770: 4145	cmp	r1, r8
000f4772: d5dc	bgt	#0xf4720
000f4774: 4145	cmp	r1, r8
000f4776: 06d0	beq	#0xf4786
000f4778: 0098	ldr	r0, [sp]
000f477a: 3718	adds	r7, r6, r0
000f477c: e6e7	b	#0xf474c
000f477e: 301c	adds	r0, r6, #0
000f4780: 019e	ldr	r6, [sp, #4]
000f4782: b047	blx	r6
000f4784: e2e7	b	#0xf474c
000f4786: 0123	movs	r3, #1
000f4788: 5722	movs	r2, #0x57
000f478a: a354	strb	r3, [r4, r2]
000f478c: 3368	ldr	r3, [r6]
000f478e: 08c5	stm	r5!, {r3}
000f4790: 6368	ldr	r3, [r4, #4]
000f4792: 9844	add	r8, r3
000f4794: f0e7	b	#0xf4778
