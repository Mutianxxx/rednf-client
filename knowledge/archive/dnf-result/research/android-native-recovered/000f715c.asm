000f715c: 70b5	push	{r4, r5, r6, lr}
000f715e: c369	ldr	r3, [r0, #0x1c]
000f7160: 041c	adds	r4, r0, #0
000f7162: 0d1c	adds	r5, r1, #0
000f7164: 0020	movs	r0, #0
000f7166: 5a1c	adds	r2, r3, #1
000f7168: 0ad0	beq	#0xf7180
000f716a: 227e	ldrb	r2, [r4, #0x18]
000f716c: 002a	cmp	r2, #0
000f716e: 02d0	beq	#0xf7176
000f7170: 0a68	ldr	r2, [r1]
000f7172: 9342	cmp	r3, r2
000f7174: 05d0	beq	#0xf7182
000f7176: 201c	adds	r0, r4, #0
000f7178: 291c	adds	r1, r5, #0
000f717a: 0122	movs	r2, #1
000f717c: fff750ff	bl	#0xf7020
000f7180: 70bd	pop	{r4, r5, r6, pc}
000f7182: 201c	adds	r0, r4, #0
000f7184: fff700ff	bl	#0xf6f88
000f7188: 237e	ldrb	r3, [r4, #0x18]
000f718a: 0020	movs	r0, #0
000f718c: 002b	cmp	r3, #0
000f718e: f7d0	beq	#0xf7180
000f7190: 206a	ldr	r0, [r4, #0x20]
000f7192: 0028	cmp	r0, #0
000f7194: f4d0	beq	#0xf7180
000f7196: e369	ldr	r3, [r4, #0x1c]
000f7198: 2b60	str	r3, [r5]
000f719a: f1e7	b	#0xf7180
