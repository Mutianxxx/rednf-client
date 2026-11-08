000f0420: 10b5	push	{r4, lr}
000f0422: 4469	ldr	r4, [r0, #0x14]
000f0424: 031c	adds	r3, r0, #0
000f0426: 0320	movs	r0, #3
000f0428: 002c	cmp	r4, #0
000f042a: 1cd0	beq	#0xf0466
000f042c: 4422	movs	r2, #0x44
000f042e: 9a5c	ldrb	r2, [r3, r2]
000f0430: 002a	cmp	r2, #0
000f0432: 19d0	beq	#0xf0468
000f0434: d868	ldr	r0, [r3, #0xc]
000f0436: 1421	movs	r1, #0x14
000f0438: 435e	ldrsh	r3, [r0, r1]
000f043a: 3821	movs	r1, #0x38
000f043c: 425e	ldrsh	r2, [r0, r1]
000f043e: d218	adds	r2, r2, r3
000f0440: 8368	ldr	r3, [r0, #8]
000f0442: 0132	adds	r2, #1
000f0444: 9a42	cmp	r2, r3
000f0446: 14d8	bhi	#0xf0472
000f0448: 2388	ldrh	r3, [r4]
000f044a: 1a04	lsls	r2, r3, #0x10
000f044c: 1214	asrs	r2, r2, #0x10
000f044e: 002a	cmp	r2, #0
000f0450: 06dd	ble	#0xf0460
000f0452: 6188	ldrh	r1, [r4, #2]
000f0454: e368	ldr	r3, [r4, #0xc]
000f0456: 013a	subs	r2, #1
000f0458: 5200	lsls	r2, r2, #1
000f045a: 0139	subs	r1, #1
000f045c: d152	strh	r1, [r2, r3]
000f045e: 2388	ldrh	r3, [r4]
000f0460: 0133	adds	r3, #1
000f0462: 2380	strh	r3, [r4]
000f0464: 0020	movs	r0, #0
000f0466: 10bd	pop	{r4, pc}
000f0468: 2388	ldrh	r3, [r4]
000f046a: 0020	movs	r0, #0
000f046c: 0133	adds	r3, #1
000f046e: 2380	strh	r3, [r4]
000f0470: f9e7	b	#0xf0466
000f0472: 0021	movs	r1, #0
000f0474: 0122	movs	r2, #1
000f0476: faf7d3fe	bl	#0xeb220
000f047a: 0028	cmp	r0, #0
000f047c: f3d1	bne	#0xf0466
000f047e: e3e7	b	#0xf0448
