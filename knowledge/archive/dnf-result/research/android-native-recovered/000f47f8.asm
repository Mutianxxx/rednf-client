000f47f8: f0b5	push	{r4, r5, r6, r7, lr}
000f47fa: 5f46	mov	r7, fp
000f47fc: 5646	mov	r6, sl
000f47fe: 4d46	mov	r5, sb
000f4800: 4446	mov	r4, r8
000f4802: f0b4	push	{r4, r5, r6, r7}
000f4804: 071c	adds	r7, r0, #0
000f4806: b837	adds	r7, #0xb8
000f4808: 4763	str	r7, [r0, #0x34]
000f480a: 041c	adds	r4, r0, #0
000f480c: 406c	ldr	r0, [r0, #0x44]
000f480e: 89b0	sub	sp, #0x24
000f4810: 3861	str	r0, [r7, #0x10]
000f4812: a06c	ldr	r0, [r4, #0x48]
000f4814: 7861	str	r0, [r7, #0x14]
000f4816: 606b	ldr	r0, [r4, #0x34]
000f4818: 8160	str	r1, [r0, #8]
000f481a: 616b	ldr	r1, [r4, #0x34]
000f481c: ca60	str	r2, [r1, #0xc]
000f481e: 626b	ldr	r2, [r4, #0x34]
000f4820: 4149	ldr	r1, [pc, #0x104]
000f4822: 1360	str	r3, [r2]
000f4824: 129a	ldr	r2, [sp, #0x48]
000f4826: 636b	ldr	r3, [r4, #0x34]
000f4828: 8846	mov	r8, r1
000f482a: f844	add	r8, pc
000f482c: 5a60	str	r2, [r3, #4]
000f482e: 3f4a	ldr	r2, [pc, #0xfc]
000f4830: 606b	ldr	r0, [r4, #0x34]
000f4832: 9246	mov	sl, r2
000f4834: fa44	add	sl, pc
000f4836: 0ae0	b	#0xf484e
000f4838: 191c	adds	r1, r3, #0
000f483a: 2e1c	adds	r6, r5, #0
000f483c: 8a42	cmp	r2, r1
000f483e: 11dd	ble	#0xf4864
000f4840: fff786fe	bl	#0xf4550
000f4844: 606b	ldr	r0, [r4, #0x34]
000f4846: 1030	adds	r0, #0x10
000f4848: 6063	str	r0, [r4, #0x34]
000f484a: 8742	cmp	r7, r0
000f484c: 42d8	bhi	#0xf48d4
000f484e: 0168	ldr	r1, [r0]
000f4850: 4369	ldr	r3, [r0, #0x14]
000f4852: 4568	ldr	r5, [r0, #4]
000f4854: c268	ldr	r2, [r0, #0xc]
000f4856: 8946	mov	sb, r1
000f4858: ab42	cmp	r3, r5
000f485a: eddc	bgt	#0xf4838
000f485c: 291c	adds	r1, r5, #0
000f485e: 1e1c	adds	r6, r3, #0
000f4860: 8a42	cmp	r2, r1
000f4862: eddc	bgt	#0xf4840
000f4864: b242	cmp	r2, r6
000f4866: ebdb	blt	#0xf4840
000f4868: ab42	cmp	r3, r5
000f486a: 3ed0	beq	#0xf48ea
000f486c: 0126	movs	r6, #1
000f486e: ab42	cmp	r3, r5
000f4870: 00db	blt	#0xf4874
000f4872: 0226	movs	r6, #2
000f4874: 626e	ldr	r2, [r4, #0x64]
000f4876: 0392	str	r2, [sp, #0xc]
000f4878: 9642	cmp	r6, r2
000f487a: 1cd0	beq	#0xf48b6
000f487c: 012e	cmp	r6, #1
000f487e: 43d0	beq	#0xf4908
000f4880: 6168	ldr	r1, [r4, #4]
000f4882: a068	ldr	r0, [r4, #8]
000f4884: 0139	subs	r1, #1
000f4886: 0b40	ands	r3, r1
000f4888: 0593	str	r3, [sp, #0x14]
000f488a: 059a	ldr	r2, [sp, #0x14]
000f488c: db17	asrs	r3, r3, #0x1f
000f488e: c10f	lsrs	r1, r0, #0x1f
000f4890: 8242	cmp	r2, r0
000f4892: 4b41	adcs	r3, r1
000f4894: 9b46	mov	fp, r3
000f4896: 0399	ldr	r1, [sp, #0xc]
000f4898: 0029	cmp	r1, #0
000f489a: 05d0	beq	#0xf48a8
000f489c: 201c	adds	r0, r4, #0
000f489e: 5946	mov	r1, fp
000f48a0: fff7defd	bl	#0xf4460
000f48a4: 0028	cmp	r0, #0
000f48a6: 2dd1	bne	#0xf4904
000f48a8: 201c	adds	r0, r4, #0
000f48aa: 311c	adds	r1, r6, #0
000f48ac: 5a46	mov	r2, fp
000f48ae: fff787fd	bl	#0xf43c0
000f48b2: 0028	cmp	r0, #0
000f48b4: 26d1	bne	#0xf4904
000f48b6: 012e	cmp	r6, #1
000f48b8: 1ad0	beq	#0xf48f0
000f48ba: 226d	ldr	r2, [r4, #0x50]
000f48bc: e36c	ldr	r3, [r4, #0x4c]
000f48be: 201c	adds	r0, r4, #0
000f48c0: 0092	str	r2, [sp]
000f48c2: 0221	movs	r1, #2
000f48c4: 4246	mov	r2, r8
000f48c6: fff767ff	bl	#0xf4798
000f48ca: 0028	cmp	r0, #0
000f48cc: 1ad1	bne	#0xf4904
000f48ce: 606b	ldr	r0, [r4, #0x34]
000f48d0: 8742	cmp	r7, r0
000f48d2: bcd9	bls	#0xf484e
000f48d4: 4a46	mov	r2, sb
000f48d6: 6264	str	r2, [r4, #0x44]
000f48d8: a564	str	r5, [r4, #0x48]
000f48da: 0020	movs	r0, #0
000f48dc: 09b0	add	sp, #0x24
000f48de: 3cbc	pop	{r2, r3, r4, r5}
000f48e0: 9046	mov	r8, r2
000f48e2: 9946	mov	sb, r3
000f48e4: a246	mov	sl, r4
000f48e6: ab46	mov	fp, r5
000f48e8: f0bd	pop	{r4, r5, r6, r7, pc}
000f48ea: 1038	subs	r0, #0x10
000f48ec: 6063	str	r0, [r4, #0x34]
000f48ee: ace7	b	#0xf484a
000f48f0: 226d	ldr	r2, [r4, #0x50]
000f48f2: e36c	ldr	r3, [r4, #0x4c]
000f48f4: 201c	adds	r0, r4, #0
000f48f6: 0092	str	r2, [sp]
000f48f8: 0221	movs	r1, #2
000f48fa: 5246	mov	r2, sl
000f48fc: fff796fe	bl	#0xf462c
000f4900: 0028	cmp	r0, #0
000f4902: e4d0	beq	#0xf48ce
000f4904: 0120	movs	r0, #1
000f4906: e9e7	b	#0xf48dc
000f4908: 6168	ldr	r1, [r4, #4]
000f490a: 5818	adds	r0, r3, r1
000f490c: 0138	subs	r0, #1
000f490e: 4942	rsbs	r1, r1, #0
000f4910: 0140	ands	r1, r0
000f4912: c91a	subs	r1, r1, r3
000f4914: 0591	str	r1, [sp, #0x14]
000f4916: a368	ldr	r3, [r4, #8]
000f4918: 059a	ldr	r2, [sp, #0x14]
000f491a: c917	asrs	r1, r1, #0x1f
000f491c: d80f	lsrs	r0, r3, #0x1f
000f491e: 9a42	cmp	r2, r3
000f4920: 4141	adcs	r1, r0
000f4922: 8b46	mov	fp, r1
000f4924: b7e7	b	#0xf4896
000f4926: c046	mov	r8, r8
000f4928: 23fdffff	stc2	p15, c15, [r3, #-0x3fc]!
000f492c: 19fdffff	ldc2	p15, c15, [sb, #-0x3fc]
