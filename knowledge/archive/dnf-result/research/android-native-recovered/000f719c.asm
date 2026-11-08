000f719c: 10b5	push	{r4, lr}
000f719e: 0269	ldr	r2, [r0, #0x10]
000f71a0: 0d20	movs	r0, #0xd
000f71a2: 4860	str	r0, [r1, #4]
000f71a4: 131c	adds	r3, r2, #0
000f71a6: 0833	adds	r3, #8
000f71a8: 107a	ldrb	r0, [r2, #8]
000f71aa: dc78	ldrb	r4, [r3, #3]
000f71ac: 5a78	ldrb	r2, [r3, #1]
000f71ae: 0006	lsls	r0, r0, #0x18
000f71b0: 2043	orrs	r0, r4
000f71b2: 1204	lsls	r2, r2, #0x10
000f71b4: 1043	orrs	r0, r2
000f71b6: 9a78	ldrb	r2, [r3, #2]
000f71b8: 031c	adds	r3, r0, #0
000f71ba: 1202	lsls	r2, r2, #8
000f71bc: 1343	orrs	r3, r2
000f71be: 0020	movs	r0, #0
000f71c0: 0b60	str	r3, [r1]
000f71c2: 10bd	pop	{r4, pc}
