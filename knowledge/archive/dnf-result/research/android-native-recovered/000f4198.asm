000f4198: 084a	ldr	r2, [pc, #0x20]
000f419a: 0023	movs	r3, #0
000f419c: 8242	cmp	r2, r0
000f419e: 5b41	adcs	r3, r3
000f41a0: 5b42	rsbs	r3, r3, #0
000f41a2: 1840	ands	r0, r3
000f41a4: 064b	ldr	r3, [pc, #0x18]
000f41a6: 4000	lsls	r0, r0, #1
000f41a8: 7b44	add	r3, pc
000f41aa: 191c	adds	r1, r3, #0
000f41ac: 054b	ldr	r3, [pc, #0x14]
000f41ae: 4031	adds	r1, #0x40
000f41b0: 7b44	add	r3, pc
000f41b2: 1b18	adds	r3, r3, r0
000f41b4: 3020	movs	r0, #0x30
000f41b6: 1a5e	ldrsh	r2, [r3, r0]
000f41b8: 8818	adds	r0, r1, r2
000f41ba: 7047	bx	lr
000f41bc: 0101	lsls	r1, r0, #4
000f41be: 0000	movs	r0, r0
000f41c0: c824	movs	r4, #0xc8
000f41c2: 0500	movs	r5, r0
000f41c4: 4033	adds	r3, #0x40
000f41c6: 0500	movs	r5, r0
