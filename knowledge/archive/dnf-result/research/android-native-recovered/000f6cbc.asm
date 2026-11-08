000f6cbc: 10b5	push	{r4, lr}
000f6cbe: 0269	ldr	r2, [r0, #0x10]
000f6cc0: 0a20	movs	r0, #0xa
000f6cc2: 4860	str	r0, [r1, #4]
000f6cc4: 131c	adds	r3, r2, #0
000f6cc6: 0833	adds	r3, #8
000f6cc8: 107a	ldrb	r0, [r2, #8]
000f6cca: dc78	ldrb	r4, [r3, #3]
000f6ccc: 5a78	ldrb	r2, [r3, #1]
000f6cce: 0006	lsls	r0, r0, #0x18
000f6cd0: 2043	orrs	r0, r4
000f6cd2: 1204	lsls	r2, r2, #0x10
000f6cd4: 1043	orrs	r0, r2
000f6cd6: 9a78	ldrb	r2, [r3, #2]
000f6cd8: 031c	adds	r3, r0, #0
000f6cda: 1202	lsls	r2, r2, #8
000f6cdc: 1343	orrs	r3, r2
000f6cde: 0020	movs	r0, #0
000f6ce0: 0b60	str	r3, [r1]
000f6ce2: 10bd	pop	{r4, pc}
