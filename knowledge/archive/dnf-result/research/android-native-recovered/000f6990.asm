000f6990: 10b5	push	{r4, lr}
000f6992: 0369	ldr	r3, [r0, #0x10]
000f6994: 9a79	ldrb	r2, [r3, #6]
000f6996: d879	ldrb	r0, [r3, #7]
000f6998: 1c1c	adds	r4, r3, #0
000f699a: 1202	lsls	r2, r2, #8
000f699c: 0243	orrs	r2, r0
000f699e: 187a	ldrb	r0, [r3, #8]
000f69a0: 891a	subs	r1, r1, r2
000f69a2: 5a7a	ldrb	r2, [r3, #9]
000f69a4: 0002	lsls	r0, r0, #8
000f69a6: 031c	adds	r3, r0, #0
000f69a8: 1343	orrs	r3, r2
000f69aa: 0a34	adds	r4, #0xa
000f69ac: 0020	movs	r0, #0
000f69ae: 8b42	cmp	r3, r1
000f69b0: 05d9	bls	#0xf69be
000f69b2: 4900	lsls	r1, r1, #1
000f69b4: 6118	adds	r1, r4, r1
000f69b6: 0878	ldrb	r0, [r1]
000f69b8: 4b78	ldrb	r3, [r1, #1]
000f69ba: 0002	lsls	r0, r0, #8
000f69bc: 1843	orrs	r0, r3
000f69be: 10bd	pop	{r4, pc}
