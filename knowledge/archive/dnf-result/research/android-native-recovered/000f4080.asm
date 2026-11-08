000f4080: 0068	ldr	r0, [r0]
000f4082: 0968	ldr	r1, [r1]
000f4084: 4200	lsls	r2, r0, #1
000f4086: 4b00	lsls	r3, r1, #1
000f4088: 5208	lsrs	r2, r2, #1
000f408a: 5b08	lsrs	r3, r3, #1
000f408c: 9a42	cmp	r2, r3
000f408e: 03d0	beq	#0xf4098
000f4090: 9a42	cmp	r2, r3
000f4092: 08d9	bls	#0xf40a6
000f4094: 0120	movs	r0, #1
000f4096: 7047	bx	lr
000f4098: 8842	cmp	r0, r1
000f409a: fbd8	bhi	#0xf4094
000f409c: 8842	cmp	r0, r1
000f409e: 04d2	bhs	#0xf40aa
000f40a0: 0120	movs	r0, #1
000f40a2: 4042	rsbs	r0, r0, #0
000f40a4: f7e7	b	#0xf4096
000f40a6: 9a42	cmp	r2, r3
000f40a8: fad3	blo	#0xf40a0
000f40aa: 0020	movs	r0, #0
000f40ac: f3e7	b	#0xf4096
