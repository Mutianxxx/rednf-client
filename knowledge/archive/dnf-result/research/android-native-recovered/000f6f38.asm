000f6f38: 10b5	push	{r4, lr}
000f6f3a: 0269	ldr	r2, [r0, #0x10]
000f6f3c: 0c20	movs	r0, #0xc
000f6f3e: 4860	str	r0, [r1, #4]
000f6f40: 131c	adds	r3, r2, #0
000f6f42: 0833	adds	r3, #8
000f6f44: 107a	ldrb	r0, [r2, #8]
000f6f46: dc78	ldrb	r4, [r3, #3]
000f6f48: 5a78	ldrb	r2, [r3, #1]
000f6f4a: 0006	lsls	r0, r0, #0x18
000f6f4c: 2043	orrs	r0, r4
000f6f4e: 1204	lsls	r2, r2, #0x10
000f6f50: 1043	orrs	r0, r2
000f6f52: 9a78	ldrb	r2, [r3, #2]
000f6f54: 031c	adds	r3, r0, #0
000f6f56: 1202	lsls	r2, r2, #8
000f6f58: 1343	orrs	r3, r2
000f6f5a: 0020	movs	r0, #0
000f6f5c: 0b60	str	r3, [r1]
000f6f5e: 10bd	pop	{r4, pc}
