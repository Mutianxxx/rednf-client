000f6974: 0369	ldr	r3, [r0, #0x10]
000f6976: 0422	movs	r2, #4
000f6978: 4a60	str	r2, [r1, #4]
000f697a: 1879	ldrb	r0, [r3, #4]
000f697c: 5a79	ldrb	r2, [r3, #5]
000f697e: 0002	lsls	r0, r0, #8
000f6980: 031c	adds	r3, r0, #0
000f6982: 1343	orrs	r3, r2
000f6984: 1b04	lsls	r3, r3, #0x10
000f6986: 1b0c	lsrs	r3, r3, #0x10
000f6988: 0020	movs	r0, #0
000f698a: 0b60	str	r3, [r1]
000f698c: 7047	bx	lr
