000ef504: 70b5	push	{r4, r5, r6, lr}
000ef506: 0468	ldr	r4, [r0]
000ef508: f223	movs	r3, #0xf2
000ef50a: 5b00	lsls	r3, r3, #1
000ef50c: e558	ldr	r5, [r4, r3]
000ef50e: d023	movs	r3, #0xd0
000ef510: 5b00	lsls	r3, r3, #1
000ef512: e258	ldr	r2, [r4, r3]
000ef514: 054b	ldr	r3, [pc, #0x14]
000ef516: 82b0	sub	sp, #8
000ef518: 0026	movs	r6, #0
000ef51a: 011c	adds	r1, r0, #0
000ef51c: 606e	ldr	r0, [r4, #0x64]
000ef51e: 0096	str	r6, [sp]
000ef520: 0194	str	r4, [sp, #4]
000ef522: 6c68	ldr	r4, [r5, #4]
000ef524: 7b44	add	r3, pc
000ef526: a047	blx	r4
000ef528: 02b0	add	sp, #8
000ef52a: 70bd	pop	{r4, r5, r6, pc}
000ef52c: d1ff	.byte	0xd1, 0xff
000ef52e: ffff	.byte	0xff, 0xff
