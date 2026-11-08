000f61b4: 0161	str	r1, [r0, #0x10]
000f61b6: 8b79	ldrb	r3, [r1, #6]
000f61b8: ca79	ldrb	r2, [r1, #7]
000f61ba: 1b02	lsls	r3, r3, #8
000f61bc: 1343	orrs	r3, r2
000f61be: 5b08	lsrs	r3, r3, #1
000f61c0: 0362	str	r3, [r0, #0x20]
000f61c2: 0123	movs	r3, #1
000f61c4: 5b42	rsbs	r3, r3, #0
000f61c6: 8361	str	r3, [r0, #0x18]
000f61c8: 0023	movs	r3, #0
000f61ca: c361	str	r3, [r0, #0x1c]
000f61cc: 0020	movs	r0, #0
000f61ce: 7047	bx	lr
