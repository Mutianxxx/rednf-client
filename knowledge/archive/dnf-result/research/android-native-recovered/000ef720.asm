000ef720: 70b5	push	{r4, r5, r6, lr}
000ef722: 0a22	movs	r2, #0xa
000ef724: 041c	adds	r4, r0, #0
000ef726: 0d1c	adds	r5, r1, #0
000ef728: fff792ff	bl	#0xef650
000ef72c: 2368	ldr	r3, [r4]
000ef72e: 021c	adds	r2, r0, #0
000ef730: 9d42	cmp	r5, r3
000ef732: 02d9	bls	#0xef73a
000ef734: 1978	ldrb	r1, [r3]
000ef736: 2329	cmp	r1, #0x23
000ef738: 01d0	beq	#0xef73e
000ef73a: 101c	adds	r0, r2, #0
000ef73c: 70bd	pop	{r4, r5, r6, pc}
000ef73e: 0133	adds	r3, #1
000ef740: 2360	str	r3, [r4]
000ef742: 201c	adds	r0, r4, #0
000ef744: 291c	adds	r1, r5, #0
000ef746: fff783ff	bl	#0xef650
000ef74a: 021c	adds	r2, r0, #0
000ef74c: f5e7	b	#0xef73a
