000eff7c: f0b5	push	{r4, r5, r6, r7, lr}
000eff7e: 5f46	mov	r7, fp
000eff80: 5646	mov	r6, sl
000eff82: 4d46	mov	r5, sb
000eff84: 4446	mov	r4, r8
000eff86: f0b4	push	{r4, r5, r6, r7}
000eff88: 83b0	sub	sp, #0xc
000eff8a: 051c	adds	r5, r0, #0
000eff8c: 0e1c	adds	r6, r1, #0
000eff8e: 9046	mov	r8, r2
000eff90: 1f1c	adds	r7, r3, #0
000eff92: 0029	cmp	r1, #0
000eff94: 5edb	blt	#0xf0054
000eff96: 0369	ldr	r3, [r0, #0x10]
000eff98: 9942	cmp	r1, r3
000eff9a: 5bda	bge	#0xf0054
000eff9c: 002f	cmp	r7, #0
000eff9e: 59db	blt	#0xf0054
000effa0: 4368	ldr	r3, [r0, #4]
000effa2: 8468	ldr	r4, [r0, #8]
000effa4: fa18	adds	r2, r7, r3
000effa6: a242	cmp	r2, r4
000effa8: 60d9	bls	#0xf006c
000effaa: 0168	ldr	r1, [r0]
000effac: 4346	mov	r3, r8
000effae: 8946	mov	sb, r1
000effb0: 5b1a	subs	r3, r3, r1
000effb2: 9a46	mov	sl, r3
000effb4: 01d4	bmi	#0xeffba
000effb6: 5445	cmp	r4, sl
000effb8: 02d8	bhi	#0xeffc0
000effba: 0121	movs	r1, #1
000effbc: 4b42	rsbs	r3, r1, #0
000effbe: 9a46	mov	sl, r3
000effc0: 8021	movs	r1, #0x80
000effc2: c900	lsls	r1, r1, #3
000effc4: 6318	adds	r3, r4, r1
000effc6: a408	lsrs	r4, r4, #2
000effc8: 1c19	adds	r4, r3, r4
000effca: a40a	lsrs	r4, r4, #0xa
000effcc: a402	lsls	r4, r4, #0xa
000effce: a242	cmp	r2, r4
000effd0: f6d8	bhi	#0xeffc0
000effd2: 2a6a	ldr	r2, [r5, #0x20]
000effd4: 211c	adds	r1, r4, #0
000effd6: 101c	adds	r0, r2, #0
000effd8: 9346	mov	fp, r2
000effda: 01aa	add	r2, sp, #4
000effdc: f8f7e4fe	bl	#0xe8da8
000effe0: 019b	ldr	r3, [sp, #4]
000effe2: 2860	str	r0, [r5]
000effe4: 002b	cmp	r3, #0
000effe6: 3dd1	bne	#0xf0064
000effe8: 4a46	mov	r2, sb
000effea: 002a	cmp	r2, #0
000effec: 18d0	beq	#0xf0020
000effee: 4946	mov	r1, sb
000efff0: aa68	ldr	r2, [r5, #8]
000efff2: 45f778e8	blx	#0x350e4
000efff6: 2868	ldr	r0, [r5]
000efff8: 4b46	mov	r3, sb
000efffa: 2969	ldr	r1, [r5, #0x10]
000efffc: c01a	subs	r0, r0, r3
000efffe: ab69	ldr	r3, [r5, #0x18]
000f0000: 8900	lsls	r1, r1, #2
000f0002: 5918	adds	r1, r3, r1
000f0004: 8b42	cmp	r3, r1
000f0006: 07d2	bhs	#0xf0018
000f0008: 1a68	ldr	r2, [r3]
000f000a: 002a	cmp	r2, #0
000f000c: 01d0	beq	#0xf0012
000f000e: 1218	adds	r2, r2, r0
000f0010: 1a60	str	r2, [r3]
000f0012: 0433	adds	r3, #4
000f0014: 9942	cmp	r1, r3
000f0016: f7d8	bhi	#0xf0008
000f0018: 5846	mov	r0, fp
000f001a: 4946	mov	r1, sb
000f001c: f8f744f8	bl	#0xe80a8
000f0020: 5146	mov	r1, sl
000f0022: ac60	str	r4, [r5, #8]
000f0024: 0131	adds	r1, #1
000f0026: 23d0	beq	#0xf0070
000f0028: 2a68	ldr	r2, [r5]
000f002a: 6b68	ldr	r3, [r5, #4]
000f002c: 9046	mov	r8, r2
000f002e: d044	add	r8, sl
000f0030: a969	ldr	r1, [r5, #0x18]
000f0032: d318	adds	r3, r2, r3
000f0034: b600	lsls	r6, r6, #2
000f0036: 8b51	str	r3, [r1, r6]
000f0038: eb69	ldr	r3, [r5, #0x1c]
000f003a: 3a1c	adds	r2, r7, #0
000f003c: 4146	mov	r1, r8
000f003e: 9f51	str	r7, [r3, r6]
000f0040: 6b68	ldr	r3, [r5, #4]
000f0042: 2868	ldr	r0, [r5]
000f0044: c018	adds	r0, r0, r3
000f0046: 45f74ee8	blx	#0x350e4
000f004a: 6b68	ldr	r3, [r5, #4]
000f004c: 0020	movs	r0, #0
000f004e: df19	adds	r7, r3, r7
000f0050: 6f60	str	r7, [r5, #4]
000f0052: 00e0	b	#0xf0056
000f0054: 0620	movs	r0, #6
000f0056: 03b0	add	sp, #0xc
000f0058: 3cbc	pop	{r2, r3, r4, r5}
000f005a: 9046	mov	r8, r2
000f005c: 9946	mov	sb, r3
000f005e: a246	mov	sl, r4
000f0060: ab46	mov	fp, r5
000f0062: f0bd	pop	{r4, r5, r6, r7, pc}
000f0064: 4946	mov	r1, sb
000f0066: 2960	str	r1, [r5]
000f0068: 181c	adds	r0, r3, #0
000f006a: f4e7	b	#0xf0056
000f006c: 0268	ldr	r2, [r0]
000f006e: dfe7	b	#0xf0030
000f0070: 2a68	ldr	r2, [r5]
000f0072: 6b68	ldr	r3, [r5, #4]
000f0074: dce7	b	#0xf0030
