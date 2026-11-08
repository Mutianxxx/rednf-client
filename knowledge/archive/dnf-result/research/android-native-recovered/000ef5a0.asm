000ef5a0: 10b5	push	{r4, lr}
000ef5a2: 041c	adds	r4, r0, #0
000ef5a4: fff7d4ff	bl	#0xef550
000ef5a8: e368	ldr	r3, [r4, #0xc]
000ef5aa: 0020	movs	r0, #0
000ef5ac: 002b	cmp	r3, #0
000ef5ae: 00dd	ble	#0xef5b2
000ef5b0: 10bd	pop	{r4, pc}
000ef5b2: 2268	ldr	r2, [r4]
000ef5b4: a168	ldr	r1, [r4, #8]
000ef5b6: 501e	subs	r0, r2, #1
000ef5b8: 9142	cmp	r1, r2
000ef5ba: 02d8	bhi	#0xef5c2
000ef5bc: 0323	movs	r3, #3
000ef5be: e360	str	r3, [r4, #0xc]
000ef5c0: f6e7	b	#0xef5b0
000ef5c2: 1378	ldrb	r3, [r2]
000ef5c4: 0132	adds	r2, #1
000ef5c6: 2260	str	r2, [r4]
000ef5c8: 092b	cmp	r3, #9
000ef5ca: f1d0	beq	#0xef5b0
000ef5cc: 202b	cmp	r3, #0x20
000ef5ce: efd0	beq	#0xef5b0
000ef5d0: 0a2b	cmp	r3, #0xa
000ef5d2: 08d0	beq	#0xef5e6
000ef5d4: 0d2b	cmp	r3, #0xd
000ef5d6: 06d0	beq	#0xef5e6
000ef5d8: 3b2b	cmp	r3, #0x3b
000ef5da: 07d0	beq	#0xef5ec
000ef5dc: 1a2b	cmp	r3, #0x1a
000ef5de: edd0	beq	#0xef5bc
000ef5e0: 0133	adds	r3, #1
000ef5e2: e9d1	bne	#0xef5b8
000ef5e4: eae7	b	#0xef5bc
000ef5e6: 0223	movs	r3, #2
000ef5e8: e360	str	r3, [r4, #0xc]
000ef5ea: e1e7	b	#0xef5b0
000ef5ec: 0123	movs	r3, #1
000ef5ee: e360	str	r3, [r4, #0xc]
000ef5f0: dee7	b	#0xef5b0
