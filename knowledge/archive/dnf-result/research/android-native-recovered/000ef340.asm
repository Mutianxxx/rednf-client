000ef340: f0b5	push	{r4, r5, r6, r7, lr}
000ef342: 5746	mov	r7, sl
000ef344: 4e46	mov	r6, sb
000ef346: 4546	mov	r5, r8
000ef348: e0b4	push	{r5, r6, r7}
000ef34a: 4369	ldr	r3, [r0, #0x14]
000ef34c: 002b	cmp	r3, #0
000ef34e: 2dd0	beq	#0xef3ac
000ef350: 1d88	ldrh	r5, [r3]
000ef352: 0022	movs	r2, #0
000ef354: 2904	lsls	r1, r5, #0x10
000ef356: 0814	asrs	r0, r1, #0x10
000ef358: 0128	cmp	r0, #1
000ef35a: 04dd	ble	#0xef366
000ef35c: da68	ldr	r2, [r3, #0xc]
000ef35e: 0238	subs	r0, #2
000ef360: 4000	lsls	r0, r0, #1
000ef362: 825e	ldrsh	r2, [r0, r2]
000ef364: 0132	adds	r2, #1
000ef366: 5e88	ldrh	r6, [r3, #2]
000ef368: 3004	lsls	r0, r6, #0x10
000ef36a: 0014	asrs	r0, r0, #0x10
000ef36c: 0128	cmp	r0, #1
000ef36e: 0fdd	ble	#0xef390
000ef370: 5c68	ldr	r4, [r3, #4]
000ef372: 0138	subs	r0, #1
000ef374: 8246	mov	sl, r0
000ef376: c000	lsls	r0, r0, #3
000ef378: 8446	mov	ip, r0
000ef37a: 9868	ldr	r0, [r3, #8]
000ef37c: a046	mov	r8, r4
000ef37e: d700	lsls	r7, r2, #3
000ef380: 4744	add	r7, r8
000ef382: 8146	mov	sb, r0
000ef384: 3868	ldr	r0, [r7]
000ef386: 6444	add	r4, ip
000ef388: 8046	mov	r8, r0
000ef38a: 2068	ldr	r0, [r4]
000ef38c: 8045	cmp	r8, r0
000ef38e: 12d0	beq	#0xef3b6
000ef390: 0914	asrs	r1, r1, #0x10
000ef392: 0029	cmp	r1, #0
000ef394: 0add	ble	#0xef3ac
000ef396: 5888	ldrh	r0, [r3, #2]
000ef398: 0404	lsls	r4, r0, #0x10
000ef39a: 2414	asrs	r4, r4, #0x10
000ef39c: 013c	subs	r4, #1
000ef39e: a242	cmp	r2, r4
000ef3a0: 16d0	beq	#0xef3d0
000ef3a2: db68	ldr	r3, [r3, #0xc]
000ef3a4: 0139	subs	r1, #1
000ef3a6: 4900	lsls	r1, r1, #1
000ef3a8: 0138	subs	r0, #1
000ef3aa: c852	strh	r0, [r1, r3]
000ef3ac: 1cbc	pop	{r2, r3, r4}
000ef3ae: 9046	mov	r8, r2
000ef3b0: 9946	mov	sb, r3
000ef3b2: a246	mov	sl, r4
000ef3b4: f0bd	pop	{r4, r5, r6, r7, pc}
000ef3b6: 7f68	ldr	r7, [r7, #4]
000ef3b8: 6468	ldr	r4, [r4, #4]
000ef3ba: a742	cmp	r7, r4
000ef3bc: e8d1	bne	#0xef390
000ef3be: 4c46	mov	r4, sb
000ef3c0: 5444	add	r4, sl
000ef3c2: 2078	ldrb	r0, [r4]
000ef3c4: 0128	cmp	r0, #1
000ef3c6: e3d1	bne	#0xef390
000ef3c8: 013e	subs	r6, #1
000ef3ca: 5e80	strh	r6, [r3, #2]
000ef3cc: 2904	lsls	r1, r5, #0x10
000ef3ce: dfe7	b	#0xef390
000ef3d0: 013d	subs	r5, #1
000ef3d2: 0138	subs	r0, #1
000ef3d4: 1d80	strh	r5, [r3]
000ef3d6: 5880	strh	r0, [r3, #2]
000ef3d8: e8e7	b	#0xef3ac
