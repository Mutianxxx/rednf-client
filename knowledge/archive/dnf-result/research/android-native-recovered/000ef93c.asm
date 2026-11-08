000ef93c: f8b5	push	{r3, r4, r5, r6, r7, lr}
000ef93e: 144b	ldr	r3, [pc, #0x50]
000ef940: 041c	adds	r4, r0, #0
000ef942: c358	ldr	r3, [r0, r3]
000ef944: ff29	cmp	r1, #0xff
000ef946: 02d9	bls	#0xef94e
000ef948: 0120	movs	r0, #1
000ef94a: 4042	rsbs	r0, r0, #0
000ef94c: f8bd	pop	{r3, r4, r5, r6, r7, pc}
000ef94e: 9a69	ldr	r2, [r3, #0x18]
000ef950: 4900	lsls	r1, r1, #1
000ef952: 5b69	ldr	r3, [r3, #0x14]
000ef954: 885a	ldrh	r0, [r1, r2]
000ef956: 9847	blx	r3
000ef958: a923	movs	r3, #0xa9
000ef95a: db00	lsls	r3, r3, #3
000ef95c: e758	ldr	r7, [r4, r3]
000ef95e: 061c	adds	r6, r0, #0
000ef960: 002f	cmp	r7, #0
000ef962: f1d0	beq	#0xef948
000ef964: 0b4b	ldr	r3, [pc, #0x2c]
000ef966: e558	ldr	r5, [r4, r3]
000ef968: 0024	movs	r4, #0
000ef96a: 02e0	b	#0xef972
000ef96c: 0134	adds	r4, #1
000ef96e: bc42	cmp	r4, r7
000ef970: ead0	beq	#0xef948
000ef972: 01cd	ldm	r5!, {r0}
000ef974: 0028	cmp	r0, #0
000ef976: f9d0	beq	#0xef96c
000ef978: 0278	ldrb	r2, [r0]
000ef97a: 3378	ldrb	r3, [r6]
000ef97c: 9a42	cmp	r2, r3
000ef97e: f5d1	bne	#0xef96c
000ef980: 311c	adds	r1, r6, #0
000ef982: 45f78aed	blx	#0x35498
000ef986: 0028	cmp	r0, #0
000ef988: f0d1	bne	#0xef96c
000ef98a: 201c	adds	r0, r4, #0
000ef98c: dee7	b	#0xef94c
000ef98e: c046	mov	r8, r8
000ef990: 4405	lsls	r4, r0, #0x15
000ef992: 0000	movs	r0, r0
000ef994: 4c05	lsls	r4, r1, #0x15
000ef996: 0000	movs	r0, r0
