000f5fd8: 0369	ldr	r3, [r0, #0x10]
000f5fda: 0022	movs	r2, #0
000f5fdc: 4a60	str	r2, [r1, #4]
000f5fde: 1879	ldrb	r0, [r3, #4]
000f5fe0: 5a79	ldrb	r2, [r3, #5]
000f5fe2: 0002	lsls	r0, r0, #8
000f5fe4: 031c	adds	r3, r0, #0
000f5fe6: 1343	orrs	r3, r2
000f5fe8: 1b04	lsls	r3, r3, #0x10
000f5fea: 1b0c	lsrs	r3, r3, #0x10
000f5fec: 0020	movs	r0, #0
000f5fee: 0b60	str	r3, [r1]
000f5ff0: 7047	bx	lr
