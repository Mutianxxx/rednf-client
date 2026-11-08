000f6c00: 10b5	push	{r4, lr}
000f6c02: 0369	ldr	r3, [r0, #0x10]
000f6c04: 187b	ldrb	r0, [r3, #0xc]
000f6c06: 5a7b	ldrb	r2, [r3, #0xd]
000f6c08: 1c1c	adds	r4, r3, #0
000f6c0a: 0006	lsls	r0, r0, #0x18
000f6c0c: 1204	lsls	r2, r2, #0x10
000f6c0e: 0243	orrs	r2, r0
000f6c10: d87b	ldrb	r0, [r3, #0xf]
000f6c12: 1434	adds	r4, #0x14
000f6c14: 0243	orrs	r2, r0
000f6c16: 987b	ldrb	r0, [r3, #0xe]
000f6c18: 0002	lsls	r0, r0, #8
000f6c1a: 0243	orrs	r2, r0
000f6c1c: 891a	subs	r1, r1, r2
000f6c1e: 187c	ldrb	r0, [r3, #0x10]
000f6c20: 5a7c	ldrb	r2, [r3, #0x11]
000f6c22: 0006	lsls	r0, r0, #0x18
000f6c24: 1204	lsls	r2, r2, #0x10
000f6c26: 1043	orrs	r0, r2
000f6c28: da7c	ldrb	r2, [r3, #0x13]
000f6c2a: 1043	orrs	r0, r2
000f6c2c: 9a7c	ldrb	r2, [r3, #0x12]
000f6c2e: 031c	adds	r3, r0, #0
000f6c30: 0020	movs	r0, #0
000f6c32: 1202	lsls	r2, r2, #8
000f6c34: 1343	orrs	r3, r2
000f6c36: 8b42	cmp	r3, r1
000f6c38: 05d9	bls	#0xf6c46
000f6c3a: 4900	lsls	r1, r1, #1
000f6c3c: 6418	adds	r4, r4, r1
000f6c3e: 2078	ldrb	r0, [r4]
000f6c40: 6378	ldrb	r3, [r4, #1]
000f6c42: 0002	lsls	r0, r0, #8
000f6c44: 1843	orrs	r0, r3
000f6c46: 10bd	pop	{r4, pc}
