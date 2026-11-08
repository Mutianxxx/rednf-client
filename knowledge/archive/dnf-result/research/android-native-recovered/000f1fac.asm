000f1fac: f0b5	push	{r4, r5, r6, r7, lr}
000f1fae: 4746	mov	r7, r8
000f1fb0: 80b4	push	{r7}
000f1fb2: cc23	movs	r3, #0xcc
000f1fb4: 1e1c	adds	r6, r3, #0
000f1fb6: 4e43	muls	r6, r1, r6
000f1fb8: 8619	adds	r6, r0, r6
000f1fba: 7568	ldr	r5, [r6, #4]
000f1fbc: 331c	adds	r3, r6, #0
000f1fbe: c833	adds	r3, #0xc8
000f1fc0: 1f68	ldr	r7, [r3]
000f1fc2: 002d	cmp	r5, #0
000f1fc4: 02d1	bne	#0xf1fcc
000f1fc6: 04bc	pop	{r2}
000f1fc8: 9046	mov	r8, r2
000f1fca: f0bd	pop	{r4, r5, r6, r7, pc}
000f1fcc: b068	ldr	r0, [r6, #8]
000f1fce: 391c	adds	r1, r7, #0
000f1fd0: f3f7f8ff	bl	#0xe5fc4
000f1fd4: 3f23	movs	r3, #0x3f
000f1fd6: f060	str	r0, [r6, #0xc]
000f1fd8: 2030	adds	r0, #0x20
000f1fda: 9843	bics	r0, r3
000f1fdc: 013d	subs	r5, #1
000f1fde: 3061	str	r0, [r6, #0x10]
000f1fe0: 002d	cmp	r5, #0
000f1fe2: f0d0	beq	#0xf1fc6
000f1fe4: 341c	adds	r4, r6, #0
000f1fe6: 1434	adds	r4, #0x14
000f1fe8: 0c36	adds	r6, #0xc
000f1fea: 9846	mov	r8, r3
000f1fec: 00e0	b	#0xf1ff0
000f1fee: 0c34	adds	r4, #0xc
000f1ff0: 391c	adds	r1, r7, #0
000f1ff2: 2068	ldr	r0, [r4]
000f1ff4: f3f7e6ff	bl	#0xe5fc4
000f1ff8: 3368	ldr	r3, [r6]
000f1ffa: c21a	subs	r2, r0, r3
000f1ffc: d117	asrs	r1, r2, #0x1f
000f1ffe: 5218	adds	r2, r2, r1
000f2000: 4a40	eors	r2, r1
000f2002: 7f2a	cmp	r2, #0x7f
000f2004: 00dc	bgt	#0xf2008
000f2006: 181c	adds	r0, r3, #0
000f2008: 6060	str	r0, [r4, #4]
000f200a: 4346	mov	r3, r8
000f200c: 2030	adds	r0, #0x20
000f200e: 9843	bics	r0, r3
000f2010: 013d	subs	r5, #1
000f2012: a060	str	r0, [r4, #8]
000f2014: 002d	cmp	r5, #0
000f2016: ead1	bne	#0xf1fee
000f2018: d5e7	b	#0xf1fc6
