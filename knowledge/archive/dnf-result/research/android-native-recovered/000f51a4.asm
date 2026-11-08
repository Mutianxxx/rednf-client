000f51a4: f0b5	push	{r4, r5, r6, r7, lr}
000f51a6: 5746	mov	r7, sl
000f51a8: 4e46	mov	r6, sb
000f51aa: 4546	mov	r5, r8
000f51ac: e0b4	push	{r5, r6, r7}
000f51ae: 0c1c	adds	r4, r1, #0
000f51b0: 0999	ldr	r1, [sp, #0x24]
000f51b2: 089d	ldr	r5, [sp, #0x20]
000f51b4: 061c	adds	r6, r0, #0
000f51b6: 8846	mov	r8, r1
000f51b8: 0a99	ldr	r1, [sp, #0x28]
000f51ba: af1a	subs	r7, r5, r2
000f51bc: 8946	mov	sb, r1
000f51be: 4545	cmp	r5, r8
000f51c0: 5edb	blt	#0xf5280
000f51c2: 002f	cmp	r7, #0
000f51c4: 5cdd	ble	#0xf5280
000f51c6: 4a45	cmp	r2, sb
000f51c8: 5adc	bgt	#0xf5280
000f51ca: 1b1b	subs	r3, r3, r4
000f51cc: 9a46	mov	sl, r3
000f51ce: 4245	cmp	r2, r8
000f51d0: 6cdb	blt	#0xf52ac
000f51d2: 0368	ldr	r3, [r0]
000f51d4: 111c	adds	r1, r2, #0
000f51d6: 1941	asrs	r1, r3
000f51d8: 8846	mov	r8, r1
000f51da: 4168	ldr	r1, [r0, #4]
000f51dc: 0139	subs	r1, #1
000f51de: 0a40	ands	r2, r1
000f51e0: 4d45	cmp	r5, sb
000f51e2: 53dc	bgt	#0xf528c
000f51e4: 291c	adds	r1, r5, #0
000f51e6: 1941	asrs	r1, r3
000f51e8: 7368	ldr	r3, [r6, #4]
000f51ea: 8946	mov	sb, r1
000f51ec: 013b	subs	r3, #1
000f51ee: 1d40	ands	r5, r3
000f51f0: 002a	cmp	r2, #0
000f51f2: 51dd	ble	#0xf5298
000f51f4: c845	cmp	r8, sb
000f51f6: 43d0	beq	#0xf5280
000f51f8: 7168	ldr	r1, [r6, #4]
000f51fa: 5046	mov	r0, sl
000f51fc: 891a	subs	r1, r1, r2
000f51fe: 3a1c	adds	r2, r7, #0
000f5200: f0f74afe	bl	#0xe5e98
000f5204: 0122	movs	r2, #1
000f5206: 2418	adds	r4, r4, r0
000f5208: 9044	add	r8, r2
000f520a: 6a42	rsbs	r2, r5, #0
000f520c: 6a41	adcs	r2, r5
000f520e: 5723	movs	r3, #0x57
000f5210: f254	strb	r2, [r6, r3]
000f5212: 5623	movs	r3, #0x56
000f5214: f25c	ldrb	r2, [r6, r3]
000f5216: 002a	cmp	r2, #0
000f5218: 04d0	beq	#0xf5224
000f521a: b26d	ldr	r2, [r6, #0x58]
000f521c: 4146	mov	r1, r8
000f521e: 5161	str	r1, [r2, #0x14]
000f5220: 0022	movs	r2, #0
000f5222: f254	strb	r2, [r6, r3]
000f5224: 4d46	mov	r5, sb
000f5226: 4246	mov	r2, r8
000f5228: 0135	adds	r5, #1
000f522a: ad1a	subs	r5, r5, r2
000f522c: ab00	lsls	r3, r5, #2
000f522e: 9946	mov	sb, r3
000f5230: b36a	ldr	r3, [r6, #0x28]
000f5232: 726a	ldr	r2, [r6, #0x24]
000f5234: 4b44	add	r3, sb
000f5236: 9a42	cmp	r2, r3
000f5238: 45d9	bls	#0xf52c6
000f523a: 5146	mov	r1, sl
000f523c: 0029	cmp	r1, #0
000f523e: 46dd	ble	#0xf52ce
000f5240: 3a1c	adds	r2, r7, #0
000f5242: 7068	ldr	r0, [r6, #4]
000f5244: f0f728fe	bl	#0xe5e98
000f5248: 7368	ldr	r3, [r6, #4]
000f524a: 8046	mov	r8, r0
000f524c: 391c	adds	r1, r7, #0
000f524e: 5046	mov	r0, sl
000f5250: 5843	muls	r0, r3, r0
000f5252: 2cf074ec	blx	#0x121b3c
000f5256: 0120	movs	r0, #1
000f5258: b36a	ldr	r3, [r6, #0x28]
000f525a: 9c46	mov	ip, r3
000f525c: 002d	cmp	r5, #0
000f525e: 0bdd	ble	#0xf5278
000f5260: 7b42	rsbs	r3, r7, #0
000f5262: 6246	mov	r2, ip
000f5264: 10c2	stm	r2!, {r4}
000f5266: 4444	add	r4, r8
000f5268: 5b18	adds	r3, r3, r1
000f526a: 01d4	bmi	#0xf5270
000f526c: db1b	subs	r3, r3, r7
000f526e: 2418	adds	r4, r4, r0
000f5270: 013d	subs	r5, #1
000f5272: 002d	cmp	r5, #0
000f5274: f6d1	bne	#0xf5264
000f5276: cc44	add	ip, sb
000f5278: 6146	mov	r1, ip
000f527a: b162	str	r1, [r6, #0x28]
000f527c: 0020	movs	r0, #0
000f527e: 00e0	b	#0xf5282
000f5280: 0020	movs	r0, #0
000f5282: 1cbc	pop	{r2, r3, r4}
000f5284: 9046	mov	r8, r2
000f5286: 9946	mov	sb, r3
000f5288: a246	mov	sl, r4
000f528a: f0bd	pop	{r4, r5, r6, r7, pc}
000f528c: 4946	mov	r1, sb
000f528e: 1941	asrs	r1, r3
000f5290: 8946	mov	sb, r1
000f5292: 0025	movs	r5, #0
000f5294: 002a	cmp	r2, #0
000f5296: addc	bgt	#0xf51f4
000f5298: 5723	movs	r3, #0x57
000f529a: f25c	ldrb	r2, [r6, r3]
000f529c: 002a	cmp	r2, #0
000f529e: b4d0	beq	#0xf520a
000f52a0: b26a	ldr	r2, [r6, #0x28]
000f52a2: 043a	subs	r2, #4
000f52a4: b262	str	r2, [r6, #0x28]
000f52a6: 0022	movs	r2, #0
000f52a8: f254	strb	r2, [r6, r3]
000f52aa: aee7	b	#0xf520a
000f52ac: 4346	mov	r3, r8
000f52ae: 991a	subs	r1, r3, r2
000f52b0: 5046	mov	r0, sl
000f52b2: 3a1c	adds	r2, r7, #0
000f52b4: f0f7f0fd	bl	#0xe5e98
000f52b8: 3368	ldr	r3, [r6]
000f52ba: 4146	mov	r1, r8
000f52bc: 2418	adds	r4, r4, r0
000f52be: 1941	asrs	r1, r3
000f52c0: 8846	mov	r8, r1
000f52c2: 0022	movs	r2, #0
000f52c4: 8ce7	b	#0xf51e0
000f52c6: 6223	movs	r3, #0x62
000f52c8: f362	str	r3, [r6, #0x2c]
000f52ca: 0120	movs	r0, #1
000f52cc: d9e7	b	#0xf5282
000f52ce: 5246	mov	r2, sl
000f52d0: 5242	rsbs	r2, r2, #0
000f52d2: 111c	adds	r1, r2, #0
000f52d4: 9246	mov	sl, r2
000f52d6: 7068	ldr	r0, [r6, #4]
000f52d8: 3a1c	adds	r2, r7, #0
000f52da: f0f7ddfd	bl	#0xe5e98
000f52de: 7368	ldr	r3, [r6, #4]
000f52e0: 4042	rsbs	r0, r0, #0
000f52e2: 8046	mov	r8, r0
000f52e4: 391c	adds	r1, r7, #0
000f52e6: 5046	mov	r0, sl
000f52e8: 5843	muls	r0, r3, r0
000f52ea: 2cf028ec	blx	#0x121b3c
000f52ee: 0120	movs	r0, #1
000f52f0: 4042	rsbs	r0, r0, #0
000f52f2: b1e7	b	#0xf5258
