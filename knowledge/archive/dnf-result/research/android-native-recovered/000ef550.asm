000ef550: c268	ldr	r2, [r0, #0xc]
000ef552: 3b23	movs	r3, #0x3b
000ef554: 002a	cmp	r2, #0
000ef556: 01dd	ble	#0xef55c
000ef558: 181c	adds	r0, r3, #0
000ef55a: 7047	bx	lr
000ef55c: 0268	ldr	r2, [r0]
000ef55e: 8168	ldr	r1, [r0, #8]
000ef560: 9142	cmp	r1, r2
000ef562: 0fd9	bls	#0xef584
000ef564: 1378	ldrb	r3, [r2]
000ef566: 0132	adds	r2, #1
000ef568: 0260	str	r2, [r0]
000ef56a: 092b	cmp	r3, #9
000ef56c: f8d0	beq	#0xef560
000ef56e: 202b	cmp	r3, #0x20
000ef570: f6d0	beq	#0xef560
000ef572: 0a2b	cmp	r3, #0xa
000ef574: 0bd0	beq	#0xef58e
000ef576: 0d2b	cmp	r3, #0xd
000ef578: 09d0	beq	#0xef58e
000ef57a: 3b2b	cmp	r3, #0x3b
000ef57c: 0ad1	bne	#0xef594
000ef57e: 0122	movs	r2, #1
000ef580: c260	str	r2, [r0, #0xc]
000ef582: e9e7	b	#0xef558
000ef584: 0123	movs	r3, #1
000ef586: 5b42	rsbs	r3, r3, #0
000ef588: 0322	movs	r2, #3
000ef58a: c260	str	r2, [r0, #0xc]
000ef58c: e4e7	b	#0xef558
000ef58e: 0222	movs	r2, #2
000ef590: c260	str	r2, [r0, #0xc]
000ef592: e1e7	b	#0xef558
000ef594: 1a2b	cmp	r3, #0x1a
000ef596: f7d0	beq	#0xef588
000ef598: 5a1c	adds	r2, r3, #1
000ef59a: ddd1	bne	#0xef558
000ef59c: f4e7	b	#0xef588
