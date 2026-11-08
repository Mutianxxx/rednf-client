000eff48: f0b5	push	{r4, r5, r6, r7, lr}
000eff4a: 83b0	sub	sp, #0xc
000eff4c: 041c	adds	r4, r0, #0
000eff4e: 0d1c	adds	r5, r1, #0
000eff50: 081c	adds	r0, r1, #0
000eff52: 161c	adds	r6, r2, #0
000eff54: 1021	movs	r1, #0x10
000eff56: 01aa	add	r2, sp, #4
000eff58: 1f1c	adds	r7, r3, #0
000eff5a: f8f725ff	bl	#0xe8da8
000eff5e: 019b	ldr	r3, [sp, #4]
000eff60: 002b	cmp	r3, #0
000eff62: 08d1	bne	#0xeff76
000eff64: 0222	movs	r2, #2
000eff66: 4660	str	r6, [r0, #4]
000eff68: 0660	str	r6, [r0]
000eff6a: 8760	str	r7, [r0, #8]
000eff6c: c260	str	r2, [r0, #0xc]
000eff6e: 2560	str	r5, [r4]
000eff70: 6060	str	r0, [r4, #4]
000eff72: a360	str	r3, [r4, #8]
000eff74: e360	str	r3, [r4, #0xc]
000eff76: 03b0	add	sp, #0xc
000eff78: 181c	adds	r0, r3, #0
000eff7a: f0bd	pop	{r4, r5, r6, r7, pc}
