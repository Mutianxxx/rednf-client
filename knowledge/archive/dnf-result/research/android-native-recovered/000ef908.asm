000ef908: f8b5	push	{r3, r4, r5, r6, r7, lr}
000ef90a: 0c68	ldr	r4, [r1]
000ef90c: 061c	adds	r6, r0, #0
000ef90e: 0f1c	adds	r7, r1, #0
000ef910: 0134	adds	r4, #1
000ef912: ff2c	cmp	r4, #0xff
000ef914: 0fd8	bhi	#0xef936
000ef916: 8025	movs	r5, #0x80
000ef918: 6d00	lsls	r5, r5, #1
000ef91a: 02e0	b	#0xef922
000ef91c: 0134	adds	r4, #1
000ef91e: ac42	cmp	r4, r5
000ef920: 07d0	beq	#0xef932
000ef922: 301c	adds	r0, r6, #0
000ef924: 211c	adds	r1, r4, #0
000ef926: fff7cbff	bl	#0xef8c0
000ef92a: 0028	cmp	r0, #0
000ef92c: f6d0	beq	#0xef91c
000ef92e: 3c60	str	r4, [r7]
000ef930: f8bd	pop	{r3, r4, r5, r6, r7, pc}
000ef932: 0024	movs	r4, #0
000ef934: fbe7	b	#0xef92e
000ef936: 0024	movs	r4, #0
000ef938: 0020	movs	r0, #0
000ef93a: f8e7	b	#0xef92e
