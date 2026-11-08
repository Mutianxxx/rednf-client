000ef5f4: 10b5	push	{r4, lr}
000ef5f6: 041c	adds	r4, r0, #0
000ef5f8: fff7aaff	bl	#0xef550
000ef5fc: e368	ldr	r3, [r4, #0xc]
000ef5fe: 0020	movs	r0, #0
000ef600: 012b	cmp	r3, #1
000ef602: 00dd	ble	#0xef606
000ef604: 10bd	pop	{r4, pc}
000ef606: 2368	ldr	r3, [r4]
000ef608: a168	ldr	r1, [r4, #8]
000ef60a: 581e	subs	r0, r3, #1
000ef60c: 9942	cmp	r1, r3
000ef60e: 02d8	bhi	#0xef616
000ef610: 0323	movs	r3, #3
000ef612: e360	str	r3, [r4, #0xc]
000ef614: f6e7	b	#0xef604
000ef616: 1a78	ldrb	r2, [r3]
000ef618: 0133	adds	r3, #1
000ef61a: 2360	str	r3, [r4]
000ef61c: 0a2a	cmp	r2, #0xa
000ef61e: 04d0	beq	#0xef62a
000ef620: 0d2a	cmp	r2, #0xd
000ef622: 02d0	beq	#0xef62a
000ef624: 1a2a	cmp	r2, #0x1a
000ef626: f1d1	bne	#0xef60c
000ef628: f2e7	b	#0xef610
000ef62a: 0223	movs	r3, #2
000ef62c: e360	str	r3, [r4, #0xc]
000ef62e: e9e7	b	#0xef604
