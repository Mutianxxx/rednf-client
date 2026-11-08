000f2a8c: f0b5	push	{r4, r5, r6, r7, lr}
000f2a8e: 4f46	mov	r7, sb
000f2a90: 4646	mov	r6, r8
000f2a92: c0b4	push	{r6, r7}
000f2a94: 4368	ldr	r3, [r0, #4]
000f2a96: 83b0	sub	sp, #0xc
000f2a98: 041c	adds	r4, r0, #0
000f2a9a: 161c	adds	r6, r2, #0
000f2a9c: 002b	cmp	r3, #0
000f2a9e: 0ad1	bne	#0xf2ab6
000f2aa0: 2268	ldr	r2, [r4]
000f2aa2: 2569	ldr	r5, [r4, #0x10]
000f2aa4: 676b	ldr	r7, [r4, #0x34]
000f2aa6: 9046	mov	r8, r2
000f2aa8: 3422	movs	r2, #0x34
000f2aaa: 1219	adds	r2, r2, r4
000f2aac: 9146	mov	sb, r2
000f2aae: 7a19	adds	r2, r7, r5
000f2ab0: 1030	adds	r0, #0x10
000f2ab2: 8a42	cmp	r2, r1
000f2ab4: 04d0	beq	#0xf2ac0
000f2ab6: 03b0	add	sp, #0xc
000f2ab8: 0cbc	pop	{r2, r3}
000f2aba: 9046	mov	r8, r2
000f2abc: 9946	mov	sb, r3
000f2abe: f0bd	pop	{r4, r5, r6, r7, pc}
000f2ac0: 0093	str	r3, [sp]
000f2ac2: 4346	mov	r3, r8
000f2ac4: 0193	str	r3, [sp, #4]
000f2ac6: 311c	adds	r1, r6, #0
000f2ac8: 0022	movs	r2, #0
000f2aca: 2b1c	adds	r3, r5, #0
000f2acc: fff77eff	bl	#0xf29cc
000f2ad0: 0028	cmp	r0, #0
000f2ad2: 01d0	beq	#0xf2ad8
000f2ad4: 6060	str	r0, [r4, #4]
000f2ad6: eee7	b	#0xf2ab6
000f2ad8: 4246	mov	r2, r8
000f2ada: 0090	str	r0, [sp]
000f2adc: 0192	str	r2, [sp, #4]
000f2ade: 4846	mov	r0, sb
000f2ae0: 311c	adds	r1, r6, #0
000f2ae2: 2a1c	adds	r2, r5, #0
000f2ae4: 3b1c	adds	r3, r7, #0
000f2ae6: fff771ff	bl	#0xf29cc
000f2aea: 0028	cmp	r0, #0
000f2aec: e3d0	beq	#0xf2ab6
000f2aee: 6060	str	r0, [r4, #4]
000f2af0: e1e7	b	#0xf2ab6
