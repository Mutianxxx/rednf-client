000f5f1c: 9c22	movs	r2, #0x9c
000f5f1e: 031c	adds	r3, r0, #0
000f5f20: 8058	ldr	r0, [r0, r2]
000f5f22: 9822	movs	r2, #0x98
000f5f24: 9a5a	ldrh	r2, [r3, r2]
000f5f26: 1201	lsls	r2, r2, #4
000f5f28: 8218	adds	r2, r0, r2
000f5f2a: 9042	cmp	r0, r2
000f5f2c: 08d2	bhs	#0xf5f40
000f5f2e: 0368	ldr	r3, [r0]
000f5f30: 8b42	cmp	r3, r1
000f5f32: 02d1	bne	#0xf5f3a
000f5f34: c368	ldr	r3, [r0, #0xc]
000f5f36: 002b	cmp	r3, #0
000f5f38: 03d1	bne	#0xf5f42
000f5f3a: 1030	adds	r0, #0x10
000f5f3c: 8242	cmp	r2, r0
000f5f3e: f6d8	bhi	#0xf5f2e
000f5f40: 0020	movs	r0, #0
000f5f42: 7047	bx	lr
