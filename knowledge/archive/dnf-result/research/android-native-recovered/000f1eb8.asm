000f1eb8: 70b5	push	{r4, r5, r6, lr}
000f1eba: 0e1c	adds	r6, r1, #0
000f1ebc: 041c	adds	r4, r0, #0
000f1ebe: 0025	movs	r5, #0
000f1ec0: 8169	ldr	r1, [r0, #0x18]
000f1ec2: 301c	adds	r0, r6, #0
000f1ec4: f6f7f0f8	bl	#0xe80a8
000f1ec8: 301c	adds	r0, r6, #0
000f1eca: a561	str	r5, [r4, #0x18]
000f1ecc: 6561	str	r5, [r4, #0x14]
000f1ece: e561	str	r5, [r4, #0x1c]
000f1ed0: e168	ldr	r1, [r4, #0xc]
000f1ed2: f6f7e9f8	bl	#0xe80a8
000f1ed6: e560	str	r5, [r4, #0xc]
000f1ed8: 301c	adds	r0, r6, #0
000f1eda: a168	ldr	r1, [r4, #8]
000f1edc: f6f7e4f8	bl	#0xe80a8
000f1ee0: a560	str	r5, [r4, #8]
000f1ee2: 6560	str	r5, [r4, #4]
000f1ee4: 2560	str	r5, [r4]
000f1ee6: 2561	str	r5, [r4, #0x10]
000f1ee8: 70bd	pop	{r4, r5, r6, pc}
