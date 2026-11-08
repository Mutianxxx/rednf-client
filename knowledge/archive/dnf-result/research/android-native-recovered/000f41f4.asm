000f41f4: f0b5	push	{r4, r5, r6, r7, lr}
000f41f6: 5f46	mov	r7, fp
000f41f8: 5646	mov	r6, sl
000f41fa: 4d46	mov	r5, sb
000f41fc: 4446	mov	r4, r8
000f41fe: f0b4	push	{r4, r5, r6, r7}
000f4200: a1b0	sub	sp, #0x84
000f4202: 8b46	mov	fp, r1
000f4204: 0392	str	r2, [sp, #0xc]
000f4206: 15a9	add	r1, sp, #0x54
000f4208: 0022	movs	r2, #0
000f420a: 0493	str	r3, [sp, #0x10]
000f420c: 5b46	mov	r3, fp
000f420e: 4a60	str	r2, [r1, #4]
000f4210: 8a60	str	r2, [r1, #8]
000f4212: ca60	str	r2, [r1, #0xc]
000f4214: 0a61	str	r2, [r1, #0x10]
000f4216: 4a61	str	r2, [r1, #0x14]
000f4218: 8a61	str	r2, [r1, #0x18]
000f421a: ca61	str	r2, [r1, #0x1c]
000f421c: 0a62	str	r2, [r1, #0x20]
000f421e: 4a62	str	r2, [r1, #0x24]
000f4220: 0790	str	r0, [sp, #0x1c]
000f4222: 1592	str	r2, [sp, #0x54]
000f4224: 2a9c	ldr	r4, [sp, #0xa8]
000f4226: 2b9d	ldr	r5, [sp, #0xac]
000f4228: 1a61	str	r2, [r3, #0x10]
000f422a: 5a61	str	r2, [r3, #0x14]
000f422c: 039b	ldr	r3, [sp, #0xc]
000f422e: 8846	mov	r8, r1
000f4230: 6946	mov	r1, sp
000f4232: 7c31	adds	r1, #0x7c
000f4234: 0891	str	r1, [sp, #0x20]
000f4236: 0191	str	r1, [sp, #4]
000f4238: 0a33	adds	r3, #0xa
000f423a: 0798	ldr	r0, [sp, #0x1c]
000f423c: 0821	movs	r1, #8
000f423e: 0092	str	r2, [sp]
000f4240: f5f742f8	bl	#0xe92c8
000f4244: 5a46	mov	r2, fp
000f4246: 5061	str	r0, [r2, #0x14]
000f4248: 8246	mov	sl, r0
000f424a: 1f98	ldr	r0, [sp, #0x7c]
000f424c: 0028	cmp	r0, #0
000f424e: 74d1	bne	#0xf433a
000f4250: 039b	ldr	r3, [sp, #0xc]
000f4252: 002b	cmp	r3, #0
000f4254: 46d0	beq	#0xf42e4
000f4256: 514b	ldr	r3, [pc, #0x144]
000f4258: 514f	ldr	r7, [pc, #0x144]
000f425a: 0021	movs	r1, #0
000f425c: 7b44	add	r3, pc
000f425e: 8946	mov	sb, r1
000f4260: 4433	adds	r3, #0x44
000f4262: 4146	mov	r1, r8
000f4264: 7f44	add	r7, pc
000f4266: 0593	str	r3, [sp, #0x14]
000f4268: 6c37	adds	r7, #0x6c
000f426a: 0992	str	r2, [sp, #0x24]
000f426c: a346	mov	fp, r4
000f426e: 0691	str	r1, [sp, #0x18]
000f4270: a846	mov	r8, r5
000f4272: 4046	mov	r0, r8
000f4274: 4946	mov	r1, sb
000f4276: 049a	ldr	r2, [sp, #0x10]
000f4278: 9047	blx	r2
000f427a: 061e	subs	r6, r0, #0
000f427c: 29d0	beq	#0xf42d2
000f427e: 059d	ldr	r5, [sp, #0x14]
000f4280: 0024	movs	r4, #0
000f4282: 01cd	ldm	r5!, {r0}
000f4284: 311c	adds	r1, r6, #0
000f4286: 3818	adds	r0, r7, r0
000f4288: 41f706e9	blx	#0x35498
000f428c: 0028	cmp	r0, #0
000f428e: 5bd0	beq	#0xf4348
000f4290: 0134	adds	r4, #1
000f4292: 0a2c	cmp	r4, #0xa
000f4294: f5d1	bne	#0xf4282
000f4296: 301c	adds	r0, r6, #0
000f4298: fff78efe	bl	#0xf3fb8
000f429c: 4300	lsls	r3, r0, #1
000f429e: 002b	cmp	r3, #0
000f42a0: 11d0	beq	#0xf42c6
000f42a2: 404b	ldr	r3, [pc, #0x100]
000f42a4: 0022	movs	r2, #0
000f42a6: 7b44	add	r3, pc
000f42a8: 4433	adds	r3, #0x44
000f42aa: 0433	adds	r3, #4
000f42ac: 191f	subs	r1, r3, #4
000f42ae: 0968	ldr	r1, [r1]
000f42b0: 8842	cmp	r0, r1
000f42b2: 55d0	beq	#0xf4360
000f42b4: 0132	adds	r2, #1
000f42b6: 0a2a	cmp	r2, #0xa
000f42b8: f7d1	bne	#0xf42aa
000f42ba: 5246	mov	r2, sl
000f42bc: 4b46	mov	r3, sb
000f42be: 0821	movs	r1, #8
000f42c0: 1060	str	r0, [r2]
000f42c2: 5360	str	r3, [r2, #4]
000f42c4: 8a44	add	sl, r1
000f42c6: 5a46	mov	r2, fp
000f42c8: 002a	cmp	r2, #0
000f42ca: 02d0	beq	#0xf42d2
000f42cc: 4046	mov	r0, r8
000f42ce: 311c	adds	r1, r6, #0
000f42d0: d847	blx	fp
000f42d2: 0399	ldr	r1, [sp, #0xc]
000f42d4: 0123	movs	r3, #1
000f42d6: 9944	add	sb, r3
000f42d8: 8945	cmp	sb, r1
000f42da: cad1	bne	#0xf4272
000f42dc: 099a	ldr	r2, [sp, #0x24]
000f42de: 069b	ldr	r3, [sp, #0x18]
000f42e0: 9346	mov	fp, r2
000f42e2: 9846	mov	r8, r3
000f42e4: 304a	ldr	r2, [pc, #0xc0]
000f42e6: 0023	movs	r3, #0
000f42e8: 0ba9	add	r1, sp, #0x2c
000f42ea: 7a44	add	r2, pc
000f42ec: 101c	adds	r0, r2, #0
000f42ee: 4430	adds	r0, #0x44
000f42f0: 5446	mov	r4, sl
000f42f2: 4546	mov	r5, r8
000f42f4: 02e0	b	#0xf42fc
000f42f6: 0433	adds	r3, #4
000f42f8: 282b	cmp	r3, #0x28
000f42fa: 0ad0	beq	#0xf4312
000f42fc: ea58	ldr	r2, [r5, r3]
000f42fe: 012a	cmp	r2, #1
000f4300: f9d1	bne	#0xf42f6
000f4302: c258	ldr	r2, [r0, r3]
000f4304: 2260	str	r2, [r4]
000f4306: ca58	ldr	r2, [r1, r3]
000f4308: 0433	adds	r3, #4
000f430a: 6260	str	r2, [r4, #4]
000f430c: 0834	adds	r4, #8
000f430e: 282b	cmp	r3, #0x28
000f4310: f4d1	bne	#0xf42fc
000f4312: 5a46	mov	r2, fp
000f4314: 5169	ldr	r1, [r2, #0x14]
000f4316: 641a	subs	r4, r4, r1
000f4318: e410	asrs	r4, r4, #3
000f431a: 002c	cmp	r4, #0
000f431c: 25d0	beq	#0xf436a
000f431e: 039a	ldr	r2, [sp, #0xc]
000f4320: 5308	lsrs	r3, r2, #1
000f4322: 9c42	cmp	r4, r3
000f4324: 2bd3	blo	#0xf437e
000f4326: 214b	ldr	r3, [pc, #0x84]
000f4328: 081c	adds	r0, r1, #0
000f432a: 0822	movs	r2, #8
000f432c: 7b44	add	r3, pc
000f432e: 211c	adds	r1, r4, #0
000f4330: 41f746e8	blx	#0x353c0
000f4334: 1f98	ldr	r0, [sp, #0x7c]
000f4336: 5a46	mov	r2, fp
000f4338: 1461	str	r4, [r2, #0x10]
000f433a: 21b0	add	sp, #0x84
000f433c: 3cbc	pop	{r2, r3, r4, r5}
000f433e: 9046	mov	r8, r2
000f4340: 9946	mov	sb, r3
000f4342: a246	mov	sl, r4
000f4344: ab46	mov	fp, r5
000f4346: f0bd	pop	{r4, r5, r6, r7, pc}
000f4348: 0699	ldr	r1, [sp, #0x18]
000f434a: a400	lsls	r4, r4, #2
000f434c: 0b19	adds	r3, r1, r4
000f434e: 1a68	ldr	r2, [r3]
000f4350: 002a	cmp	r2, #0
000f4352: a0d1	bne	#0xf4296
000f4354: 0122	movs	r2, #1
000f4356: 1a60	str	r2, [r3]
000f4358: 0bab	add	r3, sp, #0x2c
000f435a: 4a46	mov	r2, sb
000f435c: 1a51	str	r2, [r3, r4]
000f435e: 9ae7	b	#0xf4296
000f4360: 0699	ldr	r1, [sp, #0x18]
000f4362: 9200	lsls	r2, r2, #2
000f4364: 0223	movs	r3, #2
000f4366: 8b50	str	r3, [r1, r2]
000f4368: a7e7	b	#0xf42ba
000f436a: 0798	ldr	r0, [sp, #0x1c]
000f436c: f3f79cfe	bl	#0xe80a8
000f4370: 5b46	mov	r3, fp
000f4372: 5c61	str	r4, [r3, #0x14]
000f4374: 1f98	ldr	r0, [sp, #0x7c]
000f4376: 0028	cmp	r0, #0
000f4378: ddd1	bne	#0xf4336
000f437a: a320	movs	r0, #0xa3
000f437c: dbe7	b	#0xf4336
000f437e: 089b	ldr	r3, [sp, #0x20]
000f4380: 0091	str	r1, [sp]
000f4382: 0798	ldr	r0, [sp, #0x1c]
000f4384: 0193	str	r3, [sp, #4]
000f4386: 0821	movs	r1, #8
000f4388: 231c	adds	r3, r4, #0
000f438a: f4f79dff	bl	#0xe92c8
000f438e: 5946	mov	r1, fp
000f4390: 0023	movs	r3, #0
000f4392: 4861	str	r0, [r1, #0x14]
000f4394: 1f93	str	r3, [sp, #0x7c]
000f4396: 011c	adds	r1, r0, #0
000f4398: c5e7	b	#0xf4326
000f439a: c046	mov	r8, r8
000f439c: 9437	adds	r7, #0x94
000f439e: 0500	movs	r5, r0
000f43a0: 8c37	adds	r7, #0x8c
000f43a2: 0500	movs	r5, r0
000f43a4: ca37	adds	r7, #0xca
000f43a6: 0500	movs	r5, r0
000f43a8: 8637	adds	r7, #0x86
000f43aa: 0500	movs	r5, r0
000f43ac: 51fdffff	ldc2l	p15, c15, [r1, #-0x3fc]
