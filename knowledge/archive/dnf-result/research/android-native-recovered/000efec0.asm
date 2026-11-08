000efec0: f0b5	push	{r4, r5, r6, r7, lr}
000efec2: 85b0	sub	sp, #0x14
000efec4: 041c	adds	r4, r0, #0
000efec6: 0e1c	adds	r6, r1, #0
000efec8: 0023	movs	r3, #0
000efeca: 2262	str	r2, [r4, #0x20]
000efecc: 0093	str	r3, [sp]
000efece: 101c	adds	r0, r2, #0
000efed0: 0421	movs	r1, #4
000efed2: 331c	adds	r3, r6, #0
000efed4: 151c	adds	r5, r2, #0
000efed6: 03af	add	r7, sp, #0xc
000efed8: 0022	movs	r2, #0
000efeda: 0197	str	r7, [sp, #4]
000efedc: f9f7f4f9	bl	#0xe92c8
000efee0: 039b	ldr	r3, [sp, #0xc]
000efee2: 011c	adds	r1, r0, #0
000efee4: a061	str	r0, [r4, #0x18]
000efee6: 002b	cmp	r3, #0
000efee8: 07d0	beq	#0xefefa
000efeea: 281c	adds	r0, r5, #0
000efeec: f8f7dcf8	bl	#0xe80a8
000efef0: 0398	ldr	r0, [sp, #0xc]
000efef2: 0023	movs	r3, #0
000efef4: a361	str	r3, [r4, #0x18]
000efef6: 05b0	add	sp, #0x14
000efef8: f0bd	pop	{r4, r5, r6, r7, pc}
000efefa: 0093	str	r3, [sp]
000efefc: 281c	adds	r0, r5, #0
000efefe: 331c	adds	r3, r6, #0
000eff00: 0421	movs	r1, #4
000eff02: 0022	movs	r2, #0
000eff04: 0197	str	r7, [sp, #4]
000eff06: f9f7dff9	bl	#0xe92c8
000eff0a: 039b	ldr	r3, [sp, #0xc]
000eff0c: e061	str	r0, [r4, #0x1c]
000eff0e: 002b	cmp	r3, #0
000eff10: 01d0	beq	#0xeff16
000eff12: a169	ldr	r1, [r4, #0x18]
000eff14: e9e7	b	#0xefeea
000eff16: 6361	str	r3, [r4, #0x14]
000eff18: 2360	str	r3, [r4]
000eff1a: a360	str	r3, [r4, #8]
000eff1c: 6360	str	r3, [r4, #4]
000eff1e: 084b	ldr	r3, [pc, #0x20]
000eff20: 084a	ldr	r2, [pc, #0x20]
000eff22: 2661	str	r6, [r4, #0x10]
000eff24: 7b44	add	r3, pc
000eff26: e260	str	r2, [r4, #0xc]
000eff28: 1a68	ldr	r2, [r3]
000eff2a: 231c	adds	r3, r4, #0
000eff2c: 2433	adds	r3, #0x24
000eff2e: 43ca	ldm	r2!, {r0, r1, r6}
000eff30: 43c3	stm	r3!, {r0, r1, r6}
000eff32: 1268	ldr	r2, [r2]
000eff34: 0020	movs	r0, #0
000eff36: 1a60	str	r2, [r3]
000eff38: 039b	ldr	r3, [sp, #0xc]
000eff3a: 002b	cmp	r3, #0
000eff3c: dbd0	beq	#0xefef6
000eff3e: e8e7	b	#0xeff12
000eff40: 70b5	push	{r4, r5, r6, lr}
000eff42: 0600	movs	r6, r0
000eff44: efbe	bkpt	#0xef
000eff46: adde	udf	#0xad
