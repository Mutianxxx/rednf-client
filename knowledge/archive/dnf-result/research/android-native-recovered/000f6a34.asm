000f6a34: 0369	ldr	r3, [r0, #0x10]
000f6a36: 0622	movs	r2, #6
000f6a38: 4a60	str	r2, [r1, #4]
000f6a3a: 1879	ldrb	r0, [r3, #4]
000f6a3c: 5a79	ldrb	r2, [r3, #5]
000f6a3e: 0002	lsls	r0, r0, #8
000f6a40: 031c	adds	r3, r0, #0
000f6a42: 1343	orrs	r3, r2
000f6a44: 1b04	lsls	r3, r3, #0x10
000f6a46: 1b0c	lsrs	r3, r3, #0x10
000f6a48: 0020	movs	r0, #0
000f6a4a: 0b60	str	r3, [r1]
000f6a4c: 7047	bx	lr
