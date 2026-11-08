000f4114: f0b5	push	{r4, r5, r6, r7, lr}
000f4116: 4746	mov	r7, r8
000f4118: 80b4	push	{r7}
000f411a: 0369	ldr	r3, [r0, #0x10]
000f411c: 8846	mov	r8, r1
000f411e: 0d68	ldr	r5, [r1]
000f4120: 9c46	mov	ip, r3
000f4122: 002b	cmp	r3, #0
000f4124: 34d0	beq	#0xf4190
000f4126: 4169	ldr	r1, [r0, #0x14]
000f4128: 5c08	lsrs	r4, r3, #1
000f412a: e700	lsls	r7, r4, #3
000f412c: cf19	adds	r7, r1, r7
000f412e: 3a68	ldr	r2, [r7]
000f4130: 0135	adds	r5, #1
000f4132: aa42	cmp	r2, r5
000f4134: 26d0	beq	#0xf4184
000f4136: 6646	mov	r6, ip
000f4138: 0023	movs	r3, #0
000f413a: 0020	movs	r0, #0
000f413c: 0ce0	b	#0xf4158
000f413e: 9542	cmp	r5, r2
000f4140: 1ed9	bls	#0xf4180
000f4142: 631c	adds	r3, r4, #1
000f4144: 9e42	cmp	r6, r3
000f4146: 0fd9	bls	#0xf4168
000f4148: f41a	subs	r4, r6, r3
000f414a: 6408	lsrs	r4, r4, #1
000f414c: e418	adds	r4, r4, r3
000f414e: e700	lsls	r7, r4, #3
000f4150: cf19	adds	r7, r1, r7
000f4152: 3a68	ldr	r2, [r7]
000f4154: aa42	cmp	r2, r5
000f4156: 15d0	beq	#0xf4184
000f4158: 5200	lsls	r2, r2, #1
000f415a: 5208	lsrs	r2, r2, #1
000f415c: aa42	cmp	r2, r5
000f415e: eed1	bne	#0xf413e
000f4160: 261c	adds	r6, r4, #0
000f4162: 7868	ldr	r0, [r7, #4]
000f4164: 9e42	cmp	r6, r3
000f4166: efd8	bhi	#0xf4148
000f4168: 0028	cmp	r0, #0
000f416a: 0cd1	bne	#0xf4186
000f416c: 0025	movs	r5, #0
000f416e: 6345	cmp	r3, ip
000f4170: 09d2	bhs	#0xf4186
000f4172: db00	lsls	r3, r3, #3
000f4174: c918	adds	r1, r1, r3
000f4176: 0d68	ldr	r5, [r1]
000f4178: 4868	ldr	r0, [r1, #4]
000f417a: 6d00	lsls	r5, r5, #1
000f417c: 6d08	lsrs	r5, r5, #1
000f417e: 02e0	b	#0xf4186
000f4180: 261c	adds	r6, r4, #0
000f4182: dfe7	b	#0xf4144
000f4184: 7868	ldr	r0, [r7, #4]
000f4186: 4346	mov	r3, r8
000f4188: 1d60	str	r5, [r3]
000f418a: 04bc	pop	{r2}
000f418c: 9046	mov	r8, r2
000f418e: f0bd	pop	{r4, r5, r6, r7, pc}
000f4190: 0025	movs	r5, #0
000f4192: 0020	movs	r0, #0
000f4194: f7e7	b	#0xf4186
