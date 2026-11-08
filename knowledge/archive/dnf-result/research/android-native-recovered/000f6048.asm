000f6048: f0b5	push	{r4, r5, r6, r7, lr}
000f604a: 4746	mov	r7, r8
000f604c: 80b4	push	{r7}
000f604e: 0069	ldr	r0, [r0, #0x10]
000f6050: 0c1c	adds	r4, r1, #0
000f6052: fff7cfff	bl	#0xf5ff4
000f6056: 0028	cmp	r0, #0
000f6058: 2ad0	beq	#0xf60b0
000f605a: 821c	adds	r2, r0, #2
000f605c: 9178	ldrb	r1, [r2, #2]
000f605e: ff23	movs	r3, #0xff
000f6060: 1c40	ands	r4, r3
000f6062: 931c	adds	r3, r2, #2
000f6064: 8846	mov	r8, r1
000f6066: 5978	ldrb	r1, [r3, #1]
000f6068: 0678	ldrb	r6, [r0]
000f606a: 9d1c	adds	r5, r3, #2
000f606c: 8c46	mov	ip, r1
000f606e: 4778	ldrb	r7, [r0, #1]
000f6070: 9978	ldrb	r1, [r3, #2]
000f6072: 6b78	ldrb	r3, [r5, #1]
000f6074: 3602	lsls	r6, r6, #8
000f6076: 3e43	orrs	r6, r7
000f6078: 0902	lsls	r1, r1, #8
000f607a: a41b	subs	r4, r4, r6
000f607c: 0b43	orrs	r3, r1
000f607e: 17d0	beq	#0xf60b0
000f6080: 8078	ldrb	r0, [r0, #2]
000f6082: 5178	ldrb	r1, [r2, #1]
000f6084: 0002	lsls	r0, r0, #8
000f6086: 021c	adds	r2, r0, #0
000f6088: 0a43	orrs	r2, r1
000f608a: 9442	cmp	r4, r2
000f608c: 10d2	bhs	#0xf60b0
000f608e: 6400	lsls	r4, r4, #1
000f6090: 1b19	adds	r3, r3, r4
000f6092: ed18	adds	r5, r5, r3
000f6094: 2878	ldrb	r0, [r5]
000f6096: 6b78	ldrb	r3, [r5, #1]
000f6098: 0002	lsls	r0, r0, #8
000f609a: 0343	orrs	r3, r0
000f609c: 08d0	beq	#0xf60b0
000f609e: 4246	mov	r2, r8
000f60a0: 1006	lsls	r0, r2, #0x18
000f60a2: 0014	asrs	r0, r0, #0x10
000f60a4: 6146	mov	r1, ip
000f60a6: 0843	orrs	r0, r1
000f60a8: 1818	adds	r0, r3, r0
000f60aa: 0004	lsls	r0, r0, #0x10
000f60ac: 000c	lsrs	r0, r0, #0x10
000f60ae: 00e0	b	#0xf60b2
000f60b0: 0020	movs	r0, #0
000f60b2: 04bc	pop	{r2}
000f60b4: 9046	mov	r8, r2
000f60b6: f0bd	pop	{r4, r5, r6, r7, pc}
