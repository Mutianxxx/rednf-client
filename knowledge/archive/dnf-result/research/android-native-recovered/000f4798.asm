000f4798: f0b5	push	{r4, r5, r6, r7, lr}
000f479a: 446b	ldr	r4, [r0, #0x34]
000f479c: 9c46	mov	ip, r3
000f479e: 051c	adds	r5, r0, #0
000f47a0: 6368	ldr	r3, [r4, #4]
000f47a2: 201c	adds	r0, r4, #0
000f47a4: 0830	adds	r0, #8
000f47a6: 5b42	rsbs	r3, r3, #0
000f47a8: 6360	str	r3, [r4, #4]
000f47aa: 4368	ldr	r3, [r0, #4]
000f47ac: 83b0	sub	sp, #0xc
000f47ae: 5b42	rsbs	r3, r3, #0
000f47b0: 4360	str	r3, [r0, #4]
000f47b2: 0830	adds	r0, #8
000f47b4: 4368	ldr	r3, [r0, #4]
000f47b6: 5b42	rsbs	r3, r3, #0
000f47b8: 4360	str	r3, [r0, #4]
000f47ba: 0229	cmp	r1, #2
000f47bc: 04dd	ble	#0xf47c8
000f47be: 231c	adds	r3, r4, #0
000f47c0: 1833	adds	r3, #0x18
000f47c2: 5868	ldr	r0, [r3, #4]
000f47c4: 4042	rsbs	r0, r0, #0
000f47c6: 5860	str	r0, [r3, #4]
000f47c8: 5626	movs	r6, #0x56
000f47ca: 089b	ldr	r3, [sp, #0x20]
000f47cc: af5d	ldrb	r7, [r5, r6]
000f47ce: 6046	mov	r0, ip
000f47d0: 4042	rsbs	r0, r0, #0
000f47d2: 0090	str	r0, [sp]
000f47d4: 5b42	rsbs	r3, r3, #0
000f47d6: 281c	adds	r0, r5, #0
000f47d8: fff728ff	bl	#0xf462c
000f47dc: 002f	cmp	r7, #0
000f47de: 06d0	beq	#0xf47ee
000f47e0: ab5d	ldrb	r3, [r5, r6]
000f47e2: 002b	cmp	r3, #0
000f47e4: 03d1	bne	#0xf47ee
000f47e6: ab6d	ldr	r3, [r5, #0x58]
000f47e8: 5a69	ldr	r2, [r3, #0x14]
000f47ea: 5242	rsbs	r2, r2, #0
000f47ec: 5a61	str	r2, [r3, #0x14]
000f47ee: 6368	ldr	r3, [r4, #4]
000f47f0: 03b0	add	sp, #0xc
000f47f2: 5b42	rsbs	r3, r3, #0
000f47f4: 6360	str	r3, [r4, #4]
000f47f6: f0bd	pop	{r4, r5, r6, r7, pc}
