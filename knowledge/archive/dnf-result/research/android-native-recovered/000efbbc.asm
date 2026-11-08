000efbbc: f0b5	push	{r4, r5, r6, r7, lr}
000efbbe: 5f46	mov	r7, fp
000efbc0: 5646	mov	r6, sl
000efbc2: 4d46	mov	r5, sb
000efbc4: 4446	mov	r4, r8
000efbc6: f0b4	push	{r4, r5, r6, r7}
000efbc8: 071c	adds	r7, r0, #0
000efbca: 4668	ldr	r6, [r0, #4]
000efbcc: 87b0	sub	sp, #0x1c
000efbce: 9246	mov	sl, r2
000efbd0: 0020	movs	r0, #0
000efbd2: 052a	cmp	r2, #5
000efbd4: 2fd8	bhi	#0xefc36
000efbd6: 002a	cmp	r2, #0
000efbd8: 2dd0	beq	#0xefc36
000efbda: 0c1c	adds	r4, r1, #0
000efbdc: 3549	ldr	r1, [pc, #0xd4]
000efbde: 364b	ldr	r3, [pc, #0xd8]
000efbe0: 6a46	mov	r2, sp
000efbe2: 8b46	mov	fp, r1
000efbe4: 9946	mov	sb, r3
000efbe6: fb44	add	fp, pc
000efbe8: 6b46	mov	r3, sp
000efbea: 1432	adds	r2, #0x14
000efbec: 1033	adds	r3, #0x10
000efbee: 5946	mov	r1, fp
000efbf0: 0025	movs	r5, #0
000efbf2: f944	add	sb, pc
000efbf4: 0192	str	r2, [sp, #4]
000efbf6: 0293	str	r3, [sp, #8]
000efbf8: b846	mov	r8, r7
000efbfa: 0391	str	r1, [sp, #0xc]
000efbfc: 2368	ldr	r3, [r4]
000efbfe: 002b	cmp	r3, #0
000efc00: 49d1	bne	#0xefc96
000efc02: 301c	adds	r0, r6, #0
000efc04: fff7f6fc	bl	#0xef5f4
000efc08: 0590	str	r0, [sp, #0x14]
000efc0a: 0028	cmp	r0, #0
000efc0c: 12d0	beq	#0xefc34
000efc0e: 3768	ldr	r7, [r6]
000efc10: 2368	ldr	r3, [r4]
000efc12: 013f	subs	r7, #1
000efc14: 3f1a	subs	r7, r7, r0
000efc16: 052b	cmp	r3, #5
000efc18: 08d8	bhi	#0xefc2c
000efc1a: 9b00	lsls	r3, r3, #2
000efc1c: 4946	mov	r1, sb
000efc1e: 5b58	ldr	r3, [r3, r1]
000efc20: 4b44	add	r3, sb
000efc22: 9f46	mov	pc, r3
000efc24: 0023	movs	r3, #0
000efc26: 042f	cmp	r7, #4
000efc28: 3ad0	beq	#0xefca0
000efc2a: 2371	strb	r3, [r4, #4]
000efc2c: 0135	adds	r5, #1
000efc2e: 0834	adds	r4, #8
000efc30: 5545	cmp	r5, sl
000efc32: e3d1	bne	#0xefbfc
000efc34: 281c	adds	r0, r5, #0
000efc36: 07b0	add	sp, #0x1c
000efc38: 3cbc	pop	{r2, r3, r4, r5}
000efc3a: 9046	mov	r8, r2
000efc3c: 9946	mov	sb, r3
000efc3e: a246	mov	sl, r4
000efc40: ab46	mov	fp, r5
000efc42: f0bd	pop	{r4, r5, r6, r7, pc}
000efc44: c119	adds	r1, r0, r7
000efc46: 0198	ldr	r0, [sp, #4]
000efc48: fff76afd	bl	#0xef720
000efc4c: 6060	str	r0, [r4, #4]
000efc4e: ede7	b	#0xefc2c
000efc50: c119	adds	r1, r0, r7
000efc52: 0022	movs	r2, #0
000efc54: 0198	ldr	r0, [sp, #4]
000efc56: fff7cdfe	bl	#0xef9f4
000efc5a: 6060	str	r0, [r4, #4]
000efc5c: e6e7	b	#0xefc2c
000efc5e: 4246	mov	r2, r8
000efc60: 1068	ldr	r0, [r2]
000efc62: 791c	adds	r1, r7, #1
000efc64: 029a	ldr	r2, [sp, #8]
000efc66: f8f70bfa	bl	#0xe8080
000efc6a: 6060	str	r0, [r4, #4]
000efc6c: 049b	ldr	r3, [sp, #0x10]
000efc6e: 9b46	mov	fp, r3
000efc70: 002b	cmp	r3, #0
000efc72: dbd1	bne	#0xefc2c
000efc74: 0599	ldr	r1, [sp, #0x14]
000efc76: 3a1c	adds	r2, r7, #0
000efc78: 45f734ea	blx	#0x350e4
000efc7c: 6368	ldr	r3, [r4, #4]
000efc7e: 5946	mov	r1, fp
000efc80: d955	strb	r1, [r3, r7]
000efc82: d3e7	b	#0xefc2c
000efc84: 4246	mov	r2, r8
000efc86: d368	ldr	r3, [r2, #0xc]
000efc88: 002b	cmp	r3, #0
000efc8a: 10d0	beq	#0xefcae
000efc8c: 1269	ldr	r2, [r2, #0x10]
000efc8e: 391c	adds	r1, r7, #0
000efc90: 9847	blx	r3
000efc92: 6060	str	r0, [r4, #4]
000efc94: cae7	b	#0xefc2c
000efc96: 301c	adds	r0, r6, #0
000efc98: fff782fc	bl	#0xef5a0
000efc9c: 0590	str	r0, [sp, #0x14]
000efc9e: b4e7	b	#0xefc0a
000efca0: 0399	ldr	r1, [sp, #0xc]
000efca2: 0422	movs	r2, #4
000efca4: 45f76cea	blx	#0x35180
000efca8: 4342	rsbs	r3, r0, #0
000efcaa: 4341	adcs	r3, r0
000efcac: bde7	b	#0xefc2a
000efcae: 6360	str	r3, [r4, #4]
000efcb0: bce7	b	#0xefc2c
000efcb2: c046	mov	r8, r8
000efcb4: c28c	ldrh	r2, [r0, #0x26]
000efcb6: 0400	movs	r4, r0
000efcb8: a287	strh	r2, [r4, #0x3c]
000efcba: 0400	movs	r4, r0
