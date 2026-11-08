000ef998: f0b5	push	{r4, r5, r6, r7, lr}
000ef99a: 4746	mov	r7, r8
000ef99c: 80b4	push	{r7}
000ef99e: 144a	ldr	r2, [pc, #0x50]
000ef9a0: 071c	adds	r7, r0, #0
000ef9a2: 8846	mov	r8, r1
000ef9a4: 0678	ldrb	r6, [r0]
000ef9a6: 0024	movs	r4, #0
000ef9a8: 7a44	add	r2, pc
000ef9aa: 02e0	b	#0xef9b2
000ef9ac: 0134	adds	r4, #1
000ef9ae: 492c	cmp	r4, #0x49
000ef9b0: 19dc	bgt	#0xef9e6
000ef9b2: a300	lsls	r3, r4, #2
000ef9b4: 9858	ldr	r0, [r3, r2]
000ef9b6: 0378	ldrb	r3, [r0]
000ef9b8: b342	cmp	r3, r6
000ef9ba: f7d1	bne	#0xef9ac
000ef9bc: 492c	cmp	r4, #0x49
000ef9be: f5dc	bgt	#0xef9ac
000ef9c0: 651c	adds	r5, r4, #1
000ef9c2: ad00	lsls	r5, r5, #2
000ef9c4: 5519	adds	r5, r2, r5
000ef9c6: 06e0	b	#0xef9d6
000ef9c8: 0134	adds	r4, #1
000ef9ca: 4a2c	cmp	r4, #0x4a
000ef9cc: 0bd0	beq	#0xef9e6
000ef9ce: 01cd	ldm	r5!, {r0}
000ef9d0: 0378	ldrb	r3, [r0]
000ef9d2: b342	cmp	r3, r6
000ef9d4: 07d1	bne	#0xef9e6
000ef9d6: 391c	adds	r1, r7, #0
000ef9d8: 4246	mov	r2, r8
000ef9da: 45f7d2eb	blx	#0x35180
000ef9de: 0028	cmp	r0, #0
000ef9e0: f2d1	bne	#0xef9c8
000ef9e2: 201c	adds	r0, r4, #0
000ef9e4: 00e0	b	#0xef9e8
000ef9e6: 4b20	movs	r0, #0x4b
000ef9e8: 04bc	pop	{r2}
000ef9ea: 9046	mov	r8, r2
000ef9ec: f0bd	pop	{r4, r5, r6, r7, pc}
000ef9ee: c046	mov	r8, r8
000ef9f0: a487	strh	r4, [r4, #0x3c]
000ef9f2: 0600	movs	r6, r0
