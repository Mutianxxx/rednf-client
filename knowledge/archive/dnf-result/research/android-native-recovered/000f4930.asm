000f4930: f0b5	push	{r4, r5, r6, r7, lr}
000f4932: 5f46	mov	r7, fp
000f4934: 5646	mov	r6, sl
000f4936: 4d46	mov	r5, sb
000f4938: 4446	mov	r4, r8
000f493a: f0b4	push	{r4, r5, r6, r7}
000f493c: 071c	adds	r7, r0, #0
000f493e: b837	adds	r7, #0xb8
000f4940: 4763	str	r7, [r0, #0x34]
000f4942: 041c	adds	r4, r0, #0
000f4944: 406c	ldr	r0, [r0, #0x44]
000f4946: 89b0	sub	sp, #0x24
000f4948: b861	str	r0, [r7, #0x18]
000f494a: a06c	ldr	r0, [r4, #0x48]
000f494c: f861	str	r0, [r7, #0x1c]
000f494e: 606b	ldr	r0, [r4, #0x34]
000f4950: 0161	str	r1, [r0, #0x10]
000f4952: 616b	ldr	r1, [r4, #0x34]
000f4954: 4a61	str	r2, [r1, #0x14]
000f4956: 626b	ldr	r2, [r4, #0x34]
000f4958: 4849	ldr	r1, [pc, #0x120]
000f495a: 9360	str	r3, [r2, #8]
000f495c: 636b	ldr	r3, [r4, #0x34]
000f495e: 129a	ldr	r2, [sp, #0x48]
000f4960: 8846	mov	r8, r1
000f4962: f844	add	r8, pc
000f4964: da60	str	r2, [r3, #0xc]
000f4966: 636b	ldr	r3, [r4, #0x34]
000f4968: 139a	ldr	r2, [sp, #0x4c]
000f496a: 1a60	str	r2, [r3]
000f496c: 149a	ldr	r2, [sp, #0x50]
000f496e: 636b	ldr	r3, [r4, #0x34]
000f4970: 5a60	str	r2, [r3, #4]
000f4972: 434a	ldr	r2, [pc, #0x10c]
000f4974: 606b	ldr	r0, [r4, #0x34]
000f4976: 9246	mov	sl, r2
000f4978: fa44	add	sl, pc
000f497a: 0fe0	b	#0xf499c
000f497c: 1e1c	adds	r6, r3, #0
000f497e: ab46	mov	fp, r5
000f4980: 8c46	mov	ip, r1
000f4982: 8a42	cmp	r2, r1
000f4984: 01dd	ble	#0xf498a
000f4986: 9446	mov	ip, r2
000f4988: 0a1c	adds	r2, r1, #0
000f498a: b445	cmp	ip, r6
000f498c: 11dd	ble	#0xf49b2
000f498e: fff70bfe	bl	#0xf45a8
000f4992: 606b	ldr	r0, [r4, #0x34]
000f4994: 1830	adds	r0, #0x18
000f4996: 6063	str	r0, [r4, #0x34]
000f4998: 8742	cmp	r7, r0
000f499a: 45d8	bhi	#0xf4a28
000f499c: 0668	ldr	r6, [r0]
000f499e: c369	ldr	r3, [r0, #0x1c]
000f49a0: 4568	ldr	r5, [r0, #4]
000f49a2: 4269	ldr	r2, [r0, #0x14]
000f49a4: c168	ldr	r1, [r0, #0xc]
000f49a6: b146	mov	sb, r6
000f49a8: ab42	cmp	r3, r5
000f49aa: e7dc	bgt	#0xf497c
000f49ac: 2e1c	adds	r6, r5, #0
000f49ae: 9b46	mov	fp, r3
000f49b0: e6e7	b	#0xf4980
000f49b2: 5a45	cmp	r2, fp
000f49b4: ebdb	blt	#0xf498e
000f49b6: ab42	cmp	r3, r5
000f49b8: 41d0	beq	#0xf4a3e
000f49ba: de0f	lsrs	r6, r3, #0x1f
000f49bc: ea17	asrs	r2, r5, #0x1f
000f49be: 616e	ldr	r1, [r4, #0x64]
000f49c0: 9d42	cmp	r5, r3
000f49c2: 5641	adcs	r6, r2
000f49c4: 0220	movs	r0, #2
000f49c6: 861b	subs	r6, r0, r6
000f49c8: 0391	str	r1, [sp, #0xc]
000f49ca: 8e42	cmp	r6, r1
000f49cc: 1dd0	beq	#0xf4a0a
000f49ce: 012e	cmp	r6, #1
000f49d0: 44d0	beq	#0xf4a5c
000f49d2: 6168	ldr	r1, [r4, #4]
000f49d4: 0139	subs	r1, #1
000f49d6: 0b40	ands	r3, r1
000f49d8: 0593	str	r3, [sp, #0x14]
000f49da: 0598	ldr	r0, [sp, #0x14]
000f49dc: a368	ldr	r3, [r4, #8]
000f49de: 059a	ldr	r2, [sp, #0x14]
000f49e0: c017	asrs	r0, r0, #0x1f
000f49e2: d90f	lsrs	r1, r3, #0x1f
000f49e4: 9a42	cmp	r2, r3
000f49e6: 4841	adcs	r0, r1
000f49e8: 8346	mov	fp, r0
000f49ea: 0398	ldr	r0, [sp, #0xc]
000f49ec: 0028	cmp	r0, #0
000f49ee: 05d0	beq	#0xf49fc
000f49f0: 201c	adds	r0, r4, #0
000f49f2: 5946	mov	r1, fp
000f49f4: fff734fd	bl	#0xf4460
000f49f8: 0028	cmp	r0, #0
000f49fa: 2dd1	bne	#0xf4a58
000f49fc: 201c	adds	r0, r4, #0
000f49fe: 311c	adds	r1, r6, #0
000f4a00: 5a46	mov	r2, fp
000f4a02: fff7ddfc	bl	#0xf43c0
000f4a06: 0028	cmp	r0, #0
000f4a08: 26d1	bne	#0xf4a58
000f4a0a: 012e	cmp	r6, #1
000f4a0c: 1ad0	beq	#0xf4a44
000f4a0e: 226d	ldr	r2, [r4, #0x50]
000f4a10: e36c	ldr	r3, [r4, #0x4c]
000f4a12: 201c	adds	r0, r4, #0
000f4a14: 0092	str	r2, [sp]
000f4a16: 0321	movs	r1, #3
000f4a18: 4246	mov	r2, r8
000f4a1a: fff7bdfe	bl	#0xf4798
000f4a1e: 0028	cmp	r0, #0
000f4a20: 1ad1	bne	#0xf4a58
000f4a22: 606b	ldr	r0, [r4, #0x34]
000f4a24: 8742	cmp	r7, r0
000f4a26: b9d9	bls	#0xf499c
000f4a28: 4946	mov	r1, sb
000f4a2a: 6164	str	r1, [r4, #0x44]
000f4a2c: a564	str	r5, [r4, #0x48]
000f4a2e: 0020	movs	r0, #0
000f4a30: 09b0	add	sp, #0x24
000f4a32: 3cbc	pop	{r2, r3, r4, r5}
000f4a34: 9046	mov	r8, r2
000f4a36: 9946	mov	sb, r3
000f4a38: a246	mov	sl, r4
000f4a3a: ab46	mov	fp, r5
000f4a3c: f0bd	pop	{r4, r5, r6, r7, pc}
000f4a3e: 1838	subs	r0, #0x18
000f4a40: 6063	str	r0, [r4, #0x34]
000f4a42: a9e7	b	#0xf4998
000f4a44: 226d	ldr	r2, [r4, #0x50]
000f4a46: e36c	ldr	r3, [r4, #0x4c]
000f4a48: 201c	adds	r0, r4, #0
000f4a4a: 0092	str	r2, [sp]
000f4a4c: 0321	movs	r1, #3
000f4a4e: 5246	mov	r2, sl
000f4a50: fff7ecfd	bl	#0xf462c
000f4a54: 0028	cmp	r0, #0
000f4a56: e4d0	beq	#0xf4a22
000f4a58: 0120	movs	r0, #1
000f4a5a: e9e7	b	#0xf4a30
000f4a5c: 6168	ldr	r1, [r4, #4]
000f4a5e: a268	ldr	r2, [r4, #8]
000f4a60: 5818	adds	r0, r3, r1
000f4a62: 0138	subs	r0, #1
000f4a64: 4942	rsbs	r1, r1, #0
000f4a66: 0140	ands	r1, r0
000f4a68: c91a	subs	r1, r1, r3
000f4a6a: 0591	str	r1, [sp, #0x14]
000f4a6c: 0598	ldr	r0, [sp, #0x14]
000f4a6e: c917	asrs	r1, r1, #0x1f
000f4a70: d30f	lsrs	r3, r2, #0x1f
000f4a72: 9042	cmp	r0, r2
000f4a74: 5941	adcs	r1, r3
000f4a76: 8b46	mov	fp, r1
000f4a78: b7e7	b	#0xf49ea
000f4a7a: c046	mov	r8, r8
000f4a7c: 43fcffff	mcrr2	p15, #0xf, pc, r3, c15
000f4a80: 2dfcffff	stc2	p15, c15, [sp], #-0x3fc
