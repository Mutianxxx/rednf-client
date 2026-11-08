000f2758: f0b5	push	{r4, r5, r6, r7, lr}
000f275a: 4368	ldr	r3, [r0, #4]
000f275c: 83b0	sub	sp, #0xc
000f275e: 041c	adds	r4, r0, #0
000f2760: 0d1c	adds	r5, r1, #0
000f2762: 002b	cmp	r3, #0
000f2764: 05d1	bne	#0xf2772
000f2766: c368	ldr	r3, [r0, #0xc]
000f2768: 0668	ldr	r6, [r0]
000f276a: 0620	movs	r0, #6
000f276c: 012b	cmp	r3, #1
000f276e: 02d0	beq	#0xf2776
000f2770: 6060	str	r0, [r4, #4]
000f2772: 03b0	add	sp, #0xc
000f2774: f0bd	pop	{r4, r5, r6, r7, pc}
000f2776: e369	ldr	r3, [r4, #0x1c]
000f2778: 002b	cmp	r3, #0
000f277a: 04d0	beq	#0xf2786
000f277c: 626a	ldr	r2, [r4, #0x24]
000f277e: 013b	subs	r3, #1
000f2780: 1b01	lsls	r3, r3, #4
000f2782: d318	adds	r3, r2, r3
000f2784: d960	str	r1, [r3, #0xc]
000f2786: 201c	adds	r0, r4, #0
000f2788: 01af	add	r7, sp, #4
000f278a: 1c30	adds	r0, #0x1c
000f278c: 311c	adds	r1, r6, #0
000f278e: 3a1c	adds	r2, r7, #0
000f2790: fff7b2ff	bl	#0xf26f8
000f2794: 0028	cmp	r0, #0
000f2796: ebd1	bne	#0xf2770
000f2798: 236c	ldr	r3, [r4, #0x40]
000f279a: 002b	cmp	r3, #0
000f279c: 04d0	beq	#0xf27a8
000f279e: a26c	ldr	r2, [r4, #0x48]
000f27a0: 013b	subs	r3, #1
000f27a2: 1b01	lsls	r3, r3, #4
000f27a4: d318	adds	r3, r2, r3
000f27a6: dd60	str	r5, [r3, #0xc]
000f27a8: 201c	adds	r0, r4, #0
000f27aa: 4030	adds	r0, #0x40
000f27ac: 311c	adds	r1, r6, #0
000f27ae: 3a1c	adds	r2, r7, #0
000f27b0: fff7a2ff	bl	#0xf26f8
000f27b4: 0028	cmp	r0, #0
000f27b6: dbd1	bne	#0xf2770
000f27b8: dbe7	b	#0xf2772
