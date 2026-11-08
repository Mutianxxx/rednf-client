000efcbc: 30b5	push	{r4, r5, lr}
000efcbe: 83b0	sub	sp, #0xc
000efcc0: 0323	movs	r3, #3
000efcc2: 0d1c	adds	r5, r1, #0
000efcc4: 0122	movs	r2, #1
000efcc6: 6946	mov	r1, sp
000efcc8: 0093	str	r3, [sp]
000efcca: fff777ff	bl	#0xefbbc
000efcce: a023	movs	r3, #0xa0
000efcd0: 0128	cmp	r0, #1
000efcd2: 02d1	bne	#0xefcda
000efcd4: 019b	ldr	r3, [sp, #4]
000efcd6: 2b60	str	r3, [r5]
000efcd8: 0023	movs	r3, #0
000efcda: 03b0	add	sp, #0xc
000efcdc: 181c	adds	r0, r3, #0
000efcde: 30bd	pop	{r4, r5, pc}
