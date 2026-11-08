000f6bd8: 10b5	push	{r4, lr}
000f6bda: 0269	ldr	r2, [r0, #0x10]
000f6bdc: 0820	movs	r0, #8
000f6bde: 4860	str	r0, [r1, #4]
000f6be0: 131c	adds	r3, r2, #0
000f6be2: 0833	adds	r3, #8
000f6be4: 107a	ldrb	r0, [r2, #8]
000f6be6: dc78	ldrb	r4, [r3, #3]
000f6be8: 5a78	ldrb	r2, [r3, #1]
000f6bea: 0006	lsls	r0, r0, #0x18
000f6bec: 2043	orrs	r0, r4
000f6bee: 1204	lsls	r2, r2, #0x10
000f6bf0: 1043	orrs	r0, r2
000f6bf2: 9a78	ldrb	r2, [r3, #2]
000f6bf4: 031c	adds	r3, r0, #0
000f6bf6: 1202	lsls	r2, r2, #8
000f6bf8: 1343	orrs	r3, r2
000f6bfa: 0020	movs	r0, #0
000f6bfc: 0b60	str	r3, [r1]
000f6bfe: 10bd	pop	{r4, pc}
