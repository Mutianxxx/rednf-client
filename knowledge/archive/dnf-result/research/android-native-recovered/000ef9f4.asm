000ef9f4: f0b5	push	{r4, r5, r6, r7, lr}
000ef9f6: 5f46	mov	r7, fp
000ef9f8: 5646	mov	r6, sl
000ef9fa: 4d46	mov	r5, sb
000ef9fc: 4446	mov	r4, r8
000ef9fe: f0b4	push	{r4, r5, r6, r7}
000efa00: 0368	ldr	r3, [r0]
000efa02: 8846	mov	r8, r1
000efa04: 83b0	sub	sp, #0xc
000efa06: 8146	mov	sb, r0
000efa08: 141c	adds	r4, r2, #0
000efa0a: 4345	cmp	r3, r8
000efa0c: 00d1	bne	#0xefa10
000efa0e: bde0	b	#0xefb8c
000efa10: 0193	str	r3, [sp, #4]
000efa12: 1a78	ldrb	r2, [r3]
000efa14: 2b2a	cmp	r2, #0x2b
000efa16: 00d1	bne	#0xefa1a
000efa18: 9ae0	b	#0xefb50
000efa1a: 0020	movs	r0, #0
000efa1c: 8246	mov	sl, r0
000efa1e: 2d2a	cmp	r2, #0x2d
000efa20: 00d1	bne	#0xefa24
000efa22: 95e0	b	#0xefb50
000efa24: 0025	movs	r5, #0
000efa26: 2e2a	cmp	r2, #0x2e
000efa28: 05d0	beq	#0xefa36
000efa2a: 01a8	add	r0, sp, #4
000efa2c: 4146	mov	r1, r8
000efa2e: fff777fe	bl	#0xef720
000efa32: 019b	ldr	r3, [sp, #4]
000efa34: 0504	lsls	r5, r0, #0x10
000efa36: 4345	cmp	r3, r8
000efa38: 2ad3	blo	#0xefa90
000efa3a: 0127	movs	r7, #1
000efa3c: 0026	movs	r6, #0
000efa3e: 5a1c	adds	r2, r3, #1
000efa40: 9045	cmp	r8, r2
000efa42: 06d9	bls	#0xefa52
000efa44: 1b78	ldrb	r3, [r3]
000efa46: 452b	cmp	r3, #0x45
000efa48: 00d1	bne	#0xefa4c
000efa4a: 95e0	b	#0xefb78
000efa4c: 652b	cmp	r3, #0x65
000efa4e: 00d1	bne	#0xefa52
000efa50: 92e0	b	#0xefb78
000efa52: 002c	cmp	r4, #0
000efa54: 00dc	bgt	#0xefa58
000efa56: 9be0	b	#0xefb90
000efa58: ab00	lsls	r3, r5, #2
000efa5a: 5d19	adds	r5, r3, r5
000efa5c: b300	lsls	r3, r6, #2
000efa5e: 9e19	adds	r6, r3, r6
000efa60: 013c	subs	r4, #1
000efa62: 6d00	lsls	r5, r5, #1
000efa64: 7600	lsls	r6, r6, #1
000efa66: 002c	cmp	r4, #0
000efa68: f6d1	bne	#0xefa58
000efa6a: 002e	cmp	r6, #0
000efa6c: 00d0	beq	#0xefa70
000efa6e: 7de0	b	#0xefb6c
000efa70: 5146	mov	r1, sl
000efa72: 0029	cmp	r1, #0
000efa74: 0ad1	bne	#0xefa8c
000efa76: 019b	ldr	r3, [sp, #4]
000efa78: 4a46	mov	r2, sb
000efa7a: 1360	str	r3, [r2]
000efa7c: 03b0	add	sp, #0xc
000efa7e: 281c	adds	r0, r5, #0
000efa80: 3cbc	pop	{r2, r3, r4, r5}
000efa82: 9046	mov	r8, r2
000efa84: 9946	mov	sb, r3
000efa86: a246	mov	sl, r4
000efa88: ab46	mov	fp, r5
000efa8a: f0bd	pop	{r4, r5, r6, r7, pc}
000efa8c: 6d42	rsbs	r5, r5, #0
000efa8e: f2e7	b	#0xefa76
000efa90: 1a78	ldrb	r2, [r3]
000efa92: 2e2a	cmp	r2, #0x2e
000efa94: d1d1	bne	#0xefa3a
000efa96: 0133	adds	r3, #1
000efa98: 0193	str	r3, [sp, #4]
000efa9a: 9845	cmp	r8, r3
000efa9c: cdd9	bls	#0xefa3a
000efa9e: 1a78	ldrb	r2, [r3]
000efaa0: 202a	cmp	r2, #0x20
000efaa2: cad0	beq	#0xefa3a
000efaa4: 0a2a	cmp	r2, #0xa
000efaa6: c8d0	beq	#0xefa3a
000efaa8: 0d2a	cmp	r2, #0xd
000efaaa: c6d0	beq	#0xefa3a
000efaac: 092a	cmp	r2, #9
000efaae: c4d0	beq	#0xefa3a
000efab0: 0c2a	cmp	r2, #0xc
000efab2: c2d0	beq	#0xefa3a
000efab4: 002a	cmp	r2, #0
000efab6: c0d0	beq	#0xefa3a
000efab8: 1106	lsls	r1, r2, #0x18
000efaba: 0029	cmp	r1, #0
000efabc: bddb	blt	#0xefa3a
000efabe: 3c49	ldr	r1, [pc, #0xf0]
000efac0: 7f20	movs	r0, #0x7f
000efac2: 0240	ands	r2, r0
000efac4: 7944	add	r1, pc
000efac6: 8a5c	ldrb	r2, [r1, r2]
000efac8: 1206	lsls	r2, r2, #0x18
000efaca: 110e	lsrs	r1, r2, #0x18
000efacc: 0929	cmp	r1, #9
000eface: b4d8	bhi	#0xefa3a
000efad0: 6842	rsbs	r0, r5, #0
000efad2: 6841	adcs	r0, r5
000efad4: 3749	ldr	r1, [pc, #0xdc]
000efad6: 8446	mov	ip, r0
000efad8: 0127	movs	r7, #1
000efada: 7944	add	r1, pc
000efadc: 8b46	mov	fp, r1
000efade: 0026	movs	r6, #0
000efae0: 4146	mov	r1, r8
000efae2: a846	mov	r8, r5
000efae4: 5d46	mov	r5, fp
000efae6: 21e0	b	#0xefb2c
000efae8: b000	lsls	r0, r6, #2
000efaea: 8346	mov	fp, r0
000efaec: 5e44	add	r6, fp
000efaee: 7600	lsls	r6, r6, #1
000efaf0: 1216	asrs	r2, r2, #0x18
000efaf2: 013c	subs	r4, #1
000efaf4: 9619	adds	r6, r2, r6
000efaf6: 0133	adds	r3, #1
000efaf8: 0193	str	r3, [sp, #4]
000efafa: 8b42	cmp	r3, r1
000efafc: 43d0	beq	#0xefb86
000efafe: 1a78	ldrb	r2, [r3]
000efb00: 202a	cmp	r2, #0x20
000efb02: 40d0	beq	#0xefb86
000efb04: 0a2a	cmp	r2, #0xa
000efb06: 3ed0	beq	#0xefb86
000efb08: 0d2a	cmp	r2, #0xd
000efb0a: 3cd0	beq	#0xefb86
000efb0c: 092a	cmp	r2, #9
000efb0e: 3ad0	beq	#0xefb86
000efb10: 0c2a	cmp	r2, #0xc
000efb12: 38d0	beq	#0xefb86
000efb14: 002a	cmp	r2, #0
000efb16: 36d0	beq	#0xefb86
000efb18: 1006	lsls	r0, r2, #0x18
000efb1a: 0028	cmp	r0, #0
000efb1c: 33db	blt	#0xefb86
000efb1e: 7f20	movs	r0, #0x7f
000efb20: 0240	ands	r2, r0
000efb22: aa5c	ldrb	r2, [r5, r2]
000efb24: 1206	lsls	r2, r2, #0x18
000efb26: 100e	lsrs	r0, r2, #0x18
000efb28: 0928	cmp	r0, #9
000efb2a: 2cd8	bhi	#0xefb86
000efb2c: 002c	cmp	r4, #0
000efb2e: 02dd	ble	#0xefb36
000efb30: 6046	mov	r0, ip
000efb32: 0028	cmp	r0, #0
000efb34: d8d1	bne	#0xefae8
000efb36: 2048	ldr	r0, [pc, #0x80]
000efb38: 8742	cmp	r7, r0
000efb3a: dcdc	bgt	#0xefaf6
000efb3c: b000	lsls	r0, r6, #2
000efb3e: 8346	mov	fp, r0
000efb40: 5e44	add	r6, fp
000efb42: 1216	asrs	r2, r2, #0x18
000efb44: 7600	lsls	r6, r6, #1
000efb46: 9619	adds	r6, r2, r6
000efb48: ba00	lsls	r2, r7, #2
000efb4a: d719	adds	r7, r2, r7
000efb4c: 7f00	lsls	r7, r7, #1
000efb4e: d2e7	b	#0xefaf6
000efb50: 0133	adds	r3, #1
000efb52: 9845	cmp	r8, r3
000efb54: 1ad0	beq	#0xefb8c
000efb56: 2d3a	subs	r2, #0x2d
000efb58: 0193	str	r3, [sp, #4]
000efb5a: 5142	rsbs	r1, r2, #0
000efb5c: 5141	adcs	r1, r2
000efb5e: 1a78	ldrb	r2, [r3]
000efb60: 8a46	mov	sl, r1
000efb62: 0025	movs	r5, #0
000efb64: 2e2a	cmp	r2, #0x2e
000efb66: 00d0	beq	#0xefb6a
000efb68: 5fe7	b	#0xefa2a
000efb6a: 64e7	b	#0xefa36
000efb6c: 301c	adds	r0, r6, #0
000efb6e: 391c	adds	r1, r7, #0
000efb70: f6f75efa	bl	#0xe6030
000efb74: 2d18	adds	r5, r5, r0
000efb76: 7be7	b	#0xefa70
000efb78: 01a8	add	r0, sp, #4
000efb7a: 4146	mov	r1, r8
000efb7c: 0192	str	r2, [sp, #4]
000efb7e: fff7cffd	bl	#0xef720
000efb82: 2418	adds	r4, r4, r0
000efb84: 65e7	b	#0xefa52
000efb86: 4546	mov	r5, r8
000efb88: 8846	mov	r8, r1
000efb8a: 58e7	b	#0xefa3e
000efb8c: 0025	movs	r5, #0
000efb8e: 75e7	b	#0xefa7c
000efb90: 002c	cmp	r4, #0
000efb92: 00d1	bne	#0xefb96
000efb94: 69e7	b	#0xefa6a
000efb96: 281c	adds	r0, r5, #0
000efb98: 0a21	movs	r1, #0xa
000efb9a: 31f062ef	blx	#0x121a60
000efb9e: bb00	lsls	r3, r7, #2
000efba0: df19	adds	r7, r3, r7
000efba2: 0134	adds	r4, #1
000efba4: 7f00	lsls	r7, r7, #1
000efba6: 002c	cmp	r4, #0
000efba8: f6d1	bne	#0xefb98
000efbaa: 051c	adds	r5, r0, #0
000efbac: 5de7	b	#0xefa6a
000efbae: c046	mov	r8, r8
000efbb0: f88c	ldrh	r0, [r7, #0x26]
000efbb2: 0400	movs	r4, r0
000efbb4: e28c	ldrh	r2, [r4, #0x26]
000efbb6: 0400	movs	r4, r0
000efbb8: 7f96	str	r6, [sp, #0x1fc]
000efbba: 9800	lsls	r0, r3, #2
