000f6ce4: 0161	str	r1, [r0, #0x10]
000f6ce6: 0b1c	adds	r3, r1, #0
000f6ce8: 0c33	adds	r3, #0xc
000f6cea: 097b	ldrb	r1, [r1, #0xc]
000f6cec: da78	ldrb	r2, [r3, #3]
000f6cee: 0906	lsls	r1, r1, #0x18
000f6cf0: 1143	orrs	r1, r2
000f6cf2: 5a78	ldrb	r2, [r3, #1]
000f6cf4: 1204	lsls	r2, r2, #0x10
000f6cf6: 1143	orrs	r1, r2
000f6cf8: 9a78	ldrb	r2, [r3, #2]
000f6cfa: 0b1c	adds	r3, r1, #0
000f6cfc: 1202	lsls	r2, r2, #8
000f6cfe: 1343	orrs	r3, r2
000f6d00: 8362	str	r3, [r0, #0x28]
000f6d02: 0023	movs	r3, #0
000f6d04: 0376	strb	r3, [r0, #0x18]
000f6d06: 0020	movs	r0, #0
000f6d08: 7047	bx	lr
