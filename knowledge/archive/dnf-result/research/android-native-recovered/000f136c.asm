000f136c: 70b5	push	{r4, r5, r6, lr}
000f136e: 4468	ldr	r4, [r0, #4]
000f1370: 0d1c	adds	r5, r1, #0
000f1372: e368	ldr	r3, [r4, #0xc]
000f1374: 012b	cmp	r3, #1
000f1376: 15dd	ble	#0xf13a4
000f1378: 0026	movs	r6, #0
000f137a: e660	str	r6, [r4, #0xc]
000f137c: 201c	adds	r0, r4, #0
000f137e: fef70ff9	bl	#0xef5a0
000f1382: 0028	cmp	r0, #0
000f1384: 04d1	bne	#0xf1390
000f1386: e368	ldr	r3, [r4, #0xc]
000f1388: 022b	cmp	r3, #2
000f138a: 01dc	bgt	#0xf1390
000f138c: 022b	cmp	r3, #2
000f138e: f4d0	beq	#0xf137a
000f1390: 002d	cmp	r5, #0
000f1392: 06d0	beq	#0xf13a2
000f1394: 0023	movs	r3, #0
000f1396: 0028	cmp	r0, #0
000f1398: 02d0	beq	#0xf13a0
000f139a: 2368	ldr	r3, [r4]
000f139c: 013b	subs	r3, #1
000f139e: 1b1a	subs	r3, r3, r0
000f13a0: 2b60	str	r3, [r5]
000f13a2: 70bd	pop	{r4, r5, r6, pc}
000f13a4: 201c	adds	r0, r4, #0
000f13a6: fef725f9	bl	#0xef5f4
000f13aa: e5e7	b	#0xf1378
