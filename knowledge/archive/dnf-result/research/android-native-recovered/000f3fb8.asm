000f3fb8: 70b5	push	{r4, r5, r6, lr}
000f3fba: 0378	ldrb	r3, [r0]
000f3fbc: 752b	cmp	r3, #0x75
000f3fbe: 13d0	beq	#0xf3fe8
000f3fc0: 002b	cmp	r3, #0
000f3fc2: 36d0	beq	#0xf4032
000f3fc4: 011c	adds	r1, r0, #0
000f3fc6: 0131	adds	r1, #1
000f3fc8: 0b78	ldrb	r3, [r1]
000f3fca: 002b	cmp	r3, #0
000f3fcc: 32d0	beq	#0xf4034
000f3fce: 8842	cmp	r0, r1
000f3fd0: f9d2	bhs	#0xf3fc6
000f3fd2: 2e2b	cmp	r3, #0x2e
000f3fd4: f7d1	bne	#0xf3fc6
000f3fd6: 0029	cmp	r1, #0
000f3fd8: 2cd0	beq	#0xf4034
000f3fda: fff74bff	bl	#0xf3e74
000f3fde: 8023	movs	r3, #0x80
000f3fe0: 1b06	lsls	r3, r3, #0x18
000f3fe2: 0343	orrs	r3, r0
000f3fe4: 181c	adds	r0, r3, #0
000f3fe6: 70bd	pop	{r4, r5, r6, pc}
000f3fe8: 4178	ldrb	r1, [r0, #1]
000f3fea: 6e29	cmp	r1, #0x6e
000f3fec: 26d0	beq	#0xf403c
000f3fee: 021c	adds	r2, r0, #0
000f3ff0: 851d	adds	r5, r0, #6
000f3ff2: 0024	movs	r4, #0
000f3ff4: 0b1c	adds	r3, r1, #0
000f3ff6: 303b	subs	r3, #0x30
000f3ff8: 092b	cmp	r3, #9
000f3ffa: 11d9	bls	#0xf4020
000f3ffc: 113b	subs	r3, #0x11
000f3ffe: 052b	cmp	r3, #5
000f4000: 0dd9	bls	#0xf401e
000f4002: 531c	adds	r3, r2, #1
000f4004: aa1a	subs	r2, r5, r2
000f4006: 022a	cmp	r2, #2
000f4008: dcdc	bgt	#0xf3fc4
000f400a: 1a78	ldrb	r2, [r3]
000f400c: 231c	adds	r3, r4, #0
000f400e: 002a	cmp	r2, #0
000f4010: e8d0	beq	#0xf3fe4
000f4012: 2e2a	cmp	r2, #0x2e
000f4014: d6d1	bne	#0xf3fc4
000f4016: 8023	movs	r3, #0x80
000f4018: 1b06	lsls	r3, r3, #0x18
000f401a: 2343	orrs	r3, r4
000f401c: e2e7	b	#0xf3fe4
000f401e: 0a33	adds	r3, #0xa
000f4020: 2401	lsls	r4, r4, #4
000f4022: 0132	adds	r2, #1
000f4024: 1c19	adds	r4, r3, r4
000f4026: aa42	cmp	r2, r5
000f4028: 01d0	beq	#0xf402e
000f402a: 5178	ldrb	r1, [r2, #1]
000f402c: e2e7	b	#0xf3ff4
000f402e: 531c	adds	r3, r2, #1
000f4030: ebe7	b	#0xf400a
000f4032: 011c	adds	r1, r0, #0
000f4034: fff71eff	bl	#0xf3e74
000f4038: 031c	adds	r3, r0, #0
000f403a: d3e7	b	#0xf3fe4
000f403c: 8378	ldrb	r3, [r0, #2]
000f403e: 692b	cmp	r3, #0x69
000f4040: d5d1	bne	#0xf3fee
000f4042: 061d	adds	r6, r0, #4
000f4044: 021c	adds	r2, r0, #0
000f4046: 0023	movs	r3, #0
000f4048: d578	ldrb	r5, [r2, #3]
000f404a: 2c1c	adds	r4, r5, #0
000f404c: 303c	subs	r4, #0x30
000f404e: 092c	cmp	r4, #9
000f4050: 03d9	bls	#0xf405a
000f4052: 113c	subs	r4, #0x11
000f4054: 052c	cmp	r4, #5
000f4056: cad8	bhi	#0xf3fee
000f4058: 0a34	adds	r4, #0xa
000f405a: 1b01	lsls	r3, r3, #4
000f405c: 0132	adds	r2, #1
000f405e: e318	adds	r3, r4, r3
000f4060: b242	cmp	r2, r6
000f4062: f1d1	bne	#0xf4048
000f4064: 551e	subs	r5, r2, #1
000f4066: c41c	adds	r4, r0, #3
000f4068: a542	cmp	r5, r4
000f406a: c0d1	bne	#0xf3fee
000f406c: d278	ldrb	r2, [r2, #3]
000f406e: 002a	cmp	r2, #0
000f4070: b8d0	beq	#0xf3fe4
000f4072: 2e2a	cmp	r2, #0x2e
000f4074: bbd1	bne	#0xf3fee
000f4076: 8022	movs	r2, #0x80
000f4078: 1206	lsls	r2, r2, #0x18
000f407a: 1343	orrs	r3, r2
000f407c: b2e7	b	#0xf3fe4
