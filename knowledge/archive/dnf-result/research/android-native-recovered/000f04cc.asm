000f04cc: 70b5	push	{r4, r5, r6, lr}
000f04ce: 036c	ldr	r3, [r0, #0x40]
000f04d0: 041c	adds	r4, r0, #0
000f04d2: 0e1c	adds	r6, r1, #0
000f04d4: 151c	adds	r5, r2, #0
000f04d6: 0020	movs	r0, #0
000f04d8: 032b	cmp	r3, #3
000f04da: 06d0	beq	#0xf04ea
000f04dc: 0323	movs	r3, #3
000f04de: 2364	str	r3, [r4, #0x40]
000f04e0: 201c	adds	r0, r4, #0
000f04e2: fff79dff	bl	#0xf0420
000f04e6: 0028	cmp	r0, #0
000f04e8: 00d0	beq	#0xf04ec
000f04ea: 70bd	pop	{r4, r5, r6, pc}
000f04ec: 201c	adds	r0, r4, #0
000f04ee: 311c	adds	r1, r6, #0
000f04f0: 2a1c	adds	r2, r5, #0
000f04f2: fff7d9ff	bl	#0xf04a8
000f04f6: f8e7	b	#0xf04ea
