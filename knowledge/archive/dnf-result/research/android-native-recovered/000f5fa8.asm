000f5fa8: 0369	ldr	r3, [r0, #0x10]
000f5faa: 0020	movs	r0, #0
000f5fac: ff29	cmp	r1, #0xff
000f5fae: 01d8	bhi	#0xf5fb4
000f5fb0: 5918	adds	r1, r3, r1
000f5fb2: 8879	ldrb	r0, [r1, #6]
000f5fb4: 7047	bx	lr
