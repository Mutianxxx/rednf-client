000f12c0: f0b5	push	{r4, r5, r6, r7, lr}
000f12c2: 4746	mov	r7, r8
000f12c4: 80b4	push	{r7}
000f12c6: 82b0	sub	sp, #8
000f12c8: 0d1c	adds	r5, r1, #0
000f12ca: 171c	adds	r7, r2, #0
000f12cc: 0021	movs	r1, #0
000f12ce: 1e4a	ldr	r2, [pc, #0x78]
000f12d0: 9846	mov	r8, r3
000f12d2: 0aab	add	r3, sp, #0x28
000f12d4: 1e78	ldrb	r6, [r3]
000f12d6: 041c	adds	r4, r0, #0
000f12d8: 44f760e8	blx	#0x3539c
000f12dc: 1b49	ldr	r1, [pc, #0x6c]
000f12de: 286e	ldr	r0, [r5, #0x60]
000f12e0: 7944	add	r1, pc
000f12e2: f5f737fd	bl	#0xe6d54
000f12e6: 0723	movs	r3, #7
000f12e8: 0028	cmp	r0, #0
000f12ea: 28d0	beq	#0xf133e
000f12ec: 184b	ldr	r3, [pc, #0x60]
000f12ee: 3a1c	adds	r2, r7, #0
000f12f0: 291c	adds	r1, r5, #0
000f12f2: e050	str	r0, [r4, r3]
000f12f4: 4346	mov	r3, r8
000f12f6: 201c	adds	r0, r4, #0
000f12f8: 0096	str	r6, [sp]
000f12fa: fff79fff	bl	#0xf123c
000f12fe: 2a69	ldr	r2, [r5, #0x10]
000f1300: a923	movs	r3, #0xa9
000f1302: db00	lsls	r3, r3, #3
000f1304: e250	str	r2, [r4, r3]
000f1306: 134b	ldr	r3, [pc, #0x4c]
000f1308: 089a	ldr	r2, [sp, #0x20]
000f130a: e250	str	r2, [r4, r3]
000f130c: 0b9a	ldr	r2, [sp, #0x2c]
000f130e: 7033	adds	r3, #0x70
000f1310: e250	str	r2, [r4, r3]
000f1312: 099a	ldr	r2, [sp, #0x24]
000f1314: b723	movs	r3, #0xb7
000f1316: db00	lsls	r3, r3, #3
000f1318: e250	str	r2, [r4, r3]
000f131a: 0c9a	ldr	r2, [sp, #0x30]
000f131c: b823	movs	r3, #0xb8
000f131e: db00	lsls	r3, r3, #3
000f1320: e250	str	r2, [r4, r3]
000f1322: 0d4b	ldr	r3, [pc, #0x34]
000f1324: 0d4a	ldr	r2, [pc, #0x34]
000f1326: 7b44	add	r3, pc
000f1328: a350	str	r3, [r4, r2]
000f132a: 0d4a	ldr	r2, [pc, #0x34]
000f132c: b923	movs	r3, #0xb9
000f132e: db00	lsls	r3, r3, #3
000f1330: 7a44	add	r2, pc
000f1332: e250	str	r2, [r4, r3]
000f1334: 0b4b	ldr	r3, [pc, #0x2c]
000f1336: 0c4a	ldr	r2, [pc, #0x30]
000f1338: 7b44	add	r3, pc
000f133a: a350	str	r3, [r4, r2]
000f133c: 0023	movs	r3, #0
000f133e: 02b0	add	sp, #8
000f1340: 181c	adds	r0, r3, #0
000f1342: 04bc	pop	{r2}
000f1344: 9046	mov	r8, r2
000f1346: f0bd	pop	{r4, r5, r6, r7, pc}
000f1348: dc05	lsls	r4, r3, #0x17
000f134a: 0000	movs	r0, r0
000f134c: d075	strb	r0, [r2, #0x17]
000f134e: 0400	movs	r4, r0
000f1350: 4405	lsls	r4, r0, #0x15
000f1352: 0000	movs	r0, r0
000f1354: 4c05	lsls	r4, r1, #0x15
000f1356: 0000	movs	r0, r0
000f1358: 97ff	.byte	0x97, 0xff
000f135a: ffff	.byte	0xff, 0xff
000f135c: c405	lsls	r4, r0, #0x17
000f135e: 0000	movs	r0, r0
000f1360: d9e0	b	#0xf1516
000f1362: ffffbdf1	vsra.u64	d31, d29, #1
000f1366: ffff	.byte	0xff, 0xff
000f1368: cc05	lsls	r4, r1, #0x17
000f136a: 0000	movs	r0, r0
