000f60b8: f0b5	push	{r4, r5, r6, r7, lr}
000f60ba: 5f46	mov	r7, fp
000f60bc: 5646	mov	r6, sl
000f60be: 4d46	mov	r5, sb
000f60c0: 4446	mov	r4, r8
000f60c2: f0b4	push	{r4, r5, r6, r7}
000f60c4: 0069	ldr	r0, [r0, #0x10]
000f60c6: 83b0	sub	sp, #0xc
000f60c8: 324b	ldr	r3, [pc, #0xc8]
000f60ca: 0190	str	r0, [sp, #4]
000f60cc: 0c68	ldr	r4, [r1]
000f60ce: 0e1c	adds	r6, r1, #0
000f60d0: 0134	adds	r4, #1
000f60d2: 9c42	cmp	r4, r3
000f60d4: 4fd8	bhi	#0xf6176
000f60d6: ff25	movs	r5, #0xff
000f60d8: 9846	mov	r8, r3
000f60da: 0198	ldr	r0, [sp, #4]
000f60dc: 211c	adds	r1, r4, #0
000f60de: fff789ff	bl	#0xf5ff4
000f60e2: 0028	cmp	r0, #0
000f60e4: 42d0	beq	#0xf616c
000f60e6: 0378	ldrb	r3, [r0]
000f60e8: 821c	adds	r2, r0, #2
000f60ea: 9146	mov	sb, r2
000f60ec: 0227	movs	r7, #2
000f60ee: 9b46	mov	fp, r3
000f60f0: 8378	ldrb	r3, [r0, #2]
000f60f2: ba46	mov	sl, r7
000f60f4: 4f46	mov	r7, sb
000f60f6: bf78	ldrb	r7, [r7, #2]
000f60f8: 3f06	lsls	r7, r7, #0x18
000f60fa: 3f16	asrs	r7, r7, #0x18
000f60fc: 4278	ldrb	r2, [r0, #1]
000f60fe: 9c46	mov	ip, r3
000f6100: c378	ldrb	r3, [r0, #3]
000f6102: 4079	ldrb	r0, [r0, #5]
000f6104: 3f02	lsls	r7, r7, #8
000f6106: ca44	add	sl, sb
000f6108: 0743	orrs	r7, r0
000f610a: b946	mov	sb, r7
000f610c: 5746	mov	r7, sl
000f610e: b878	ldrb	r0, [r7, #2]
000f6110: 5146	mov	r1, sl
000f6112: 0231	adds	r1, #2
000f6114: 0002	lsls	r0, r0, #8
000f6116: 8246	mov	sl, r0
000f6118: 4878	ldrb	r0, [r1, #1]
000f611a: 5746	mov	r7, sl
000f611c: 0743	orrs	r7, r0
000f611e: ba46	mov	sl, r7
000f6120: 24d0	beq	#0xf616c
000f6122: 5f46	mov	r7, fp
000f6124: 3802	lsls	r0, r7, #8
000f6126: 0243	orrs	r2, r0
000f6128: 201c	adds	r0, r4, #0
000f612a: 2840	ands	r0, r5
000f612c: 8242	cmp	r2, r0
000f612e: 2cd9	bls	#0xf618a
000f6130: 101c	adds	r0, r2, #0
000f6132: 0022	movs	r2, #0
000f6134: 9346	mov	fp, r2
000f6136: 6746	mov	r7, ip
000f6138: 3f02	lsls	r7, r7, #8
000f613a: 1f43	orrs	r7, r3
000f613c: ac43	bics	r4, r5
000f613e: bc46	mov	ip, r7
000f6140: 0419	adds	r4, r0, r4
000f6142: 6245	cmp	r2, ip
000f6144: 12d2	bhs	#0xf616c
000f6146: 5b46	mov	r3, fp
000f6148: 5344	add	r3, sl
000f614a: cb18	adds	r3, r1, r3
000f614c: 1878	ldrb	r0, [r3]
000f614e: 5978	ldrb	r1, [r3, #1]
000f6150: 0002	lsls	r0, r0, #8
000f6152: 0143	orrs	r1, r0
000f6154: 05d0	beq	#0xf6162
000f6156: 4f46	mov	r7, sb
000f6158: 7818	adds	r0, r7, r1
000f615a: 0004	lsls	r0, r0, #0x10
000f615c: 000c	lsrs	r0, r0, #0x10
000f615e: 0028	cmp	r0, #0
000f6160: 0bd1	bne	#0xf617a
000f6162: 0132	adds	r2, #1
000f6164: 0134	adds	r4, #1
000f6166: 0233	adds	r3, #2
000f6168: 9445	cmp	ip, r2
000f616a: efd8	bhi	#0xf614c
000f616c: ac43	bics	r4, r5
000f616e: 0134	adds	r4, #1
000f6170: ff34	adds	r4, #0xff
000f6172: 4445	cmp	r4, r8
000f6174: b1d9	bls	#0xf60da
000f6176: 0024	movs	r4, #0
000f6178: 0020	movs	r0, #0
000f617a: 03b0	add	sp, #0xc
000f617c: 3460	str	r4, [r6]
000f617e: 3cbc	pop	{r2, r3, r4, r5}
000f6180: 9046	mov	r8, r2
000f6182: 9946	mov	sb, r3
000f6184: a246	mov	sl, r4
000f6186: ab46	mov	fp, r5
000f6188: f0bd	pop	{r4, r5, r6, r7, pc}
000f618a: 821a	subs	r2, r0, r2
000f618c: 5700	lsls	r7, r2, #1
000f618e: bb46	mov	fp, r7
000f6190: d1e7	b	#0xf6136
000f6192: c046	mov	r8, r8
000f6194: ffff	.byte	0xff, 0xff
000f6196: 0000	movs	r0, r0
