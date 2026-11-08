000f6f60: 0161	str	r1, [r0, #0x10]
000f6f62: 0b1c	adds	r3, r1, #0
000f6f64: 0c33	adds	r3, #0xc
000f6f66: 097b	ldrb	r1, [r1, #0xc]
000f6f68: da78	ldrb	r2, [r3, #3]
000f6f6a: 0906	lsls	r1, r1, #0x18
000f6f6c: 1143	orrs	r1, r2
000f6f6e: 5a78	ldrb	r2, [r3, #1]
000f6f70: 1204	lsls	r2, r2, #0x10
000f6f72: 1143	orrs	r1, r2
000f6f74: 9a78	ldrb	r2, [r3, #2]
000f6f76: 0b1c	adds	r3, r1, #0
000f6f78: 1202	lsls	r2, r2, #8
000f6f7a: 1343	orrs	r3, r2
000f6f7c: 8362	str	r3, [r0, #0x28]
000f6f7e: 0023	movs	r3, #0
000f6f80: 0376	strb	r3, [r0, #0x18]
000f6f82: 0020	movs	r0, #0
000f6f84: 7047	bx	lr
