000f123c: f8b5	push	{r3, r4, r5, r6, r7, lr}
000f123e: 4f46	mov	r7, sb
000f1240: 4646	mov	r6, r8
000f1242: c0b4	push	{r6, r7}
000f1244: 1d1c	adds	r5, r3, #0
000f1246: 08ab	add	r3, sp, #0x20
000f1248: 1b78	ldrb	r3, [r3]
000f124a: 041c	adds	r4, r0, #0
000f124c: 161c	adds	r6, r2, #0
000f124e: 0020	movs	r0, #0
000f1250: 9946	mov	sb, r3
000f1252: 0122	movs	r2, #1
000f1254: 4423	movs	r3, #0x44
000f1256: 2064	str	r0, [r4, #0x40]
000f1258: e254	strb	r2, [r4, r3]
000f125a: 6160	str	r1, [r4, #4]
000f125c: a560	str	r5, [r4, #8]
000f125e: 4b6e	ldr	r3, [r1, #0x64]
000f1260: 8046	mov	r8, r0
000f1262: 2360	str	r3, [r4]
000f1264: 002d	cmp	r5, #0
000f1266: 14d0	beq	#0xf1292
000f1268: 9c27	movs	r7, #0x9c
000f126a: eb59	ldr	r3, [r5, r7]
000f126c: 1868	ldr	r0, [r3]
000f126e: 031c	adds	r3, r0, #0
000f1270: 1433	adds	r3, #0x14
000f1272: 2361	str	r3, [r4, #0x10]
000f1274: 2433	adds	r3, #0x24
000f1276: 6361	str	r3, [r4, #0x14]
000f1278: e060	str	r0, [r4, #0xc]
000f127a: f5f75ff8	bl	#0xe633c
000f127e: b36a	ldr	r3, [r6, #0x28]
000f1280: 4146	mov	r1, r8
000f1282: 4a46	mov	r2, sb
000f1284: e364	str	r3, [r4, #0x4c]
000f1286: a164	str	r1, [r4, #0x48]
000f1288: 002a	cmp	r2, #0
000f128a: 02d0	beq	#0xf1292
000f128c: eb59	ldr	r3, [r5, r7]
000f128e: 5b6a	ldr	r3, [r3, #0x24]
000f1290: a364	str	r3, [r4, #0x48]
000f1292: 0023	movs	r3, #0
000f1294: a361	str	r3, [r4, #0x18]
000f1296: e361	str	r3, [r4, #0x1c]
000f1298: 2362	str	r3, [r4, #0x20]
000f129a: 6362	str	r3, [r4, #0x24]
000f129c: a362	str	r3, [r4, #0x28]
000f129e: e362	str	r3, [r4, #0x2c]
000f12a0: 064b	ldr	r3, [pc, #0x18]
000f12a2: 5034	adds	r4, #0x50
000f12a4: 7b44	add	r3, pc
000f12a6: 1b68	ldr	r3, [r3]
000f12a8: 07cb	ldm	r3!, {r0, r1, r2}
000f12aa: 07c4	stm	r4!, {r0, r1, r2}
000f12ac: 07cb	ldm	r3!, {r0, r1, r2}
000f12ae: 07c4	stm	r4!, {r0, r1, r2}
000f12b0: 03cb	ldm	r3!, {r0, r1}
000f12b2: 03c4	stm	r4!, {r0, r1}
000f12b4: 0cbc	pop	{r2, r3}
000f12b6: 9046	mov	r8, r2
000f12b8: 9946	mov	sb, r3
000f12ba: f8bd	pop	{r3, r4, r5, r6, r7, pc}
000f12bc: 3c9f	ldr	r7, [sp, #0xf0]
000f12be: 0600	movs	r6, r0
