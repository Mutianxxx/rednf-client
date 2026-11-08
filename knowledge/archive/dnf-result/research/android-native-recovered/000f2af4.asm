000f2af4: f0b5	push	{r4, r5, r6, r7, lr}
000f2af6: 4f46	mov	r7, sb
000f2af8: 4646	mov	r6, r8
000f2afa: c0b4	push	{r6, r7}
000f2afc: 1d1c	adds	r5, r3, #0
000f2afe: 4368	ldr	r3, [r0, #4]
000f2b00: 83b0	sub	sp, #0xc
000f2b02: 041c	adds	r4, r0, #0
000f2b04: 0e1c	adds	r6, r1, #0
000f2b06: 002b	cmp	r3, #0
000f2b08: 0ad1	bne	#0xf2b20
000f2b0a: 2168	ldr	r1, [r4]
000f2b0c: 2369	ldr	r3, [r4, #0x10]
000f2b0e: 676b	ldr	r7, [r4, #0x34]
000f2b10: 8846	mov	r8, r1
000f2b12: 3421	movs	r1, #0x34
000f2b14: 0919	adds	r1, r1, r4
000f2b16: 8946	mov	sb, r1
000f2b18: f918	adds	r1, r7, r3
000f2b1a: 1030	adds	r0, #0x10
000f2b1c: 9142	cmp	r1, r2
000f2b1e: 04d0	beq	#0xf2b2a
000f2b20: 03b0	add	sp, #0xc
000f2b22: 0cbc	pop	{r2, r3}
000f2b24: 9046	mov	r8, r2
000f2b26: 9946	mov	sb, r3
000f2b28: f0bd	pop	{r4, r5, r6, r7, pc}
000f2b2a: 4246	mov	r2, r8
000f2b2c: 0192	str	r2, [sp, #4]
000f2b2e: 291c	adds	r1, r5, #0
000f2b30: 3a1c	adds	r2, r7, #0
000f2b32: 0096	str	r6, [sp]
000f2b34: fff74aff	bl	#0xf29cc
000f2b38: 0028	cmp	r0, #0
000f2b3a: 01d0	beq	#0xf2b40
000f2b3c: 6060	str	r0, [r4, #4]
000f2b3e: efe7	b	#0xf2b20
000f2b40: 4346	mov	r3, r8
000f2b42: 0193	str	r3, [sp, #4]
000f2b44: 4846	mov	r0, sb
000f2b46: 291c	adds	r1, r5, #0
000f2b48: 0022	movs	r2, #0
000f2b4a: 3b1c	adds	r3, r7, #0
000f2b4c: 0096	str	r6, [sp]
000f2b4e: fff73dff	bl	#0xf29cc
000f2b52: 0028	cmp	r0, #0
000f2b54: e4d0	beq	#0xf2b20
000f2b56: 6060	str	r0, [r4, #4]
000f2b58: e2e7	b	#0xf2b20
