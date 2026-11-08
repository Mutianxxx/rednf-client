00121b60: 023123e2	eor	r3, r3, #0x80000000
00121b64: 30402de9	push	{r4, r5, lr}
00121b68: 8140a0e1	lsl	r4, r1, #1
00121b6c: 8350a0e1	lsl	r5, r3, #1
00121b70: 050034e1	teq	r4, r5
00121b74: 02003001	teqeq	r0, r2
00121b78: 00c09411	orrsne	ip, r4, r0
00121b7c: 02c09511	orrsne	ip, r5, r2
00121b80: c4caf011	mvnsne	ip, r4, asr #21
00121b84: c5caf011	mvnsne	ip, r5, asr #21
00121b88: 7900000a	beq	#0x121d74
00121b8c: a44aa0e1	lsr	r4, r4, #0x15
00121b90: a55a74e0	rsbs	r5, r4, r5, lsr #21
00121b94: 005065b2	rsblt	r5, r5, #0
00121b98: 060000da	ble	#0x121bb8
00121b9c: 054084e0	add	r4, r4, r5
00121ba0: 022020e0	eor	r2, r0, r2
00121ba4: 033021e0	eor	r3, r1, r3
00121ba8: 000022e0	eor	r0, r2, r0
00121bac: 011023e0	eor	r1, r3, r1
00121bb0: 022020e0	eor	r2, r0, r2
00121bb4: 033021e0	eor	r3, r1, r3
00121bb8: 360055e3	cmp	r5, #0x36
00121bbc: 3080bd88	pophi	{r4, r5, pc}
00121bc0: 020111e3	tst	r1, #0x80000000
00121bc4: 0116a0e1	lsl	r1, r1, #0xc
00121bc8: 01c6a0e3	mov	ip, #0x100000
00121bcc: 21168ce1	orr	r1, ip, r1, lsr #12
00121bd0: 0100000a	beq	#0x121bdc
00121bd4: 000070e2	rsbs	r0, r0, #0
00121bd8: 0010e1e2	rsc	r1, r1, #0
00121bdc: 020113e3	tst	r3, #0x80000000
00121be0: 0336a0e1	lsl	r3, r3, #0xc
00121be4: 23368ce1	orr	r3, ip, r3, lsr #12
00121be8: 0100000a	beq	#0x121bf4
00121bec: 002072e2	rsbs	r2, r2, #0
00121bf0: 0030e3e2	rsc	r3, r3, #0
00121bf4: 050034e1	teq	r4, r5
00121bf8: 5700000a	beq	#0x121d5c
00121bfc: 014044e2	sub	r4, r4, #1
00121c00: 20e075e2	rsbs	lr, r5, #0x20
00121c04: 050000ba	blt	#0x121c20
00121c08: 12cea0e1	lsl	ip, r2, lr
00121c0c: 320590e0	adds	r0, r0, r2, lsr r5
00121c10: 0010a1e2	adc	r1, r1, #0
00121c14: 130e90e0	adds	r0, r0, r3, lsl lr
00121c18: 5315b1e0	adcs	r1, r1, r3, asr r5
00121c1c: 060000ea	b	#0x121c3c
00121c20: 205045e2	sub	r5, r5, #0x20
00121c24: 20e08ee2	add	lr, lr, #0x20
00121c28: 010052e3	cmp	r2, #1
00121c2c: 13cea0e1	lsl	ip, r3, lr
00121c30: 02c08c23	orrhs	ip, ip, #2
00121c34: 530590e0	adds	r0, r0, r3, asr r5
00121c38: c31fb1e0	adcs	r1, r1, r3, asr #31
00121c3c: 025101e2	and	r5, r1, #0x80000000
00121c40: 0200005a	bpl	#0x121c50
00121c44: 00c07ce2	rsbs	ip, ip, #0
00121c48: 0000f0e2	rscs	r0, r0, #0
00121c4c: 0010e1e2	rsc	r1, r1, #0
00121c50: 010651e3	cmp	r1, #0x100000
00121c54: 0e00003a	blo	#0x121c94
00121c58: 020651e3	cmp	r1, #0x200000
00121c5c: 0600003a	blo	#0x121c7c
00121c60: a110b0e1	lsrs	r1, r1, #1
00121c64: 6000b0e1	rrxs	r0, r0
00121c68: 6cc0a0e1	rrx	ip, ip
00121c6c: 014084e2	add	r4, r4, #1
00121c70: 842aa0e1	lsl	r2, r4, #0x15
00121c74: 010572e3	cmn	r2, #0x400000
00121c78: 5500002a	bhs	#0x121dd4
00121c7c: 02015ce3	cmp	ip, #0x80000000
00121c80: a0c0b001	lsrseq	ip, r0, #1
00121c84: 0000b0e2	adcs	r0, r0, #0
00121c88: 041aa1e0	adc	r1, r1, r4, lsl #20
00121c8c: 051081e1	orr	r1, r1, r5
00121c90: 3080bde8	pop	{r4, r5, pc}
00121c94: 8cc0b0e1	lsls	ip, ip, #1
00121c98: 0000b0e0	adcs	r0, r0, r0
00121c9c: 0110a1e0	adc	r1, r1, r1
00121ca0: 010611e3	tst	r1, #0x100000
00121ca4: 014044e2	sub	r4, r4, #1
00121ca8: f3ffff1a	bne	#0x121c7c
00121cac: 000031e3	teq	r1, #0
00121cb0: 0010a001	moveq	r1, r0
00121cb4: 0000a003	moveq	r0, #0
00121cb8: 113f6fe1	clz	r3, r1
00121cbc: 20308302	addeq	r3, r3, #0x20
00121cc0: 0b3043e2	sub	r3, r3, #0xb
00121cc4: 202053e2	subs	r2, r3, #0x20
00121cc8: 070000aa	bge	#0x121cec
00121ccc: 0c2092e2	adds	r2, r2, #0xc
00121cd0: 040000da	ble	#0x121ce8
00121cd4: 14c082e2	add	ip, r2, #0x14
00121cd8: 0c2062e2	rsb	r2, r2, #0xc
00121cdc: 110ca0e1	lsl	r0, r1, ip
00121ce0: 3112a0e1	lsr	r1, r1, r2
00121ce4: 040000ea	b	#0x121cfc
00121ce8: 142082e2	add	r2, r2, #0x14
00121cec: 20c062d2	rsble	ip, r2, #0x20
00121cf0: 1112a0e1	lsl	r1, r1, r2
00121cf4: 301c81d1	orrle	r1, r1, r0, lsr ip
00121cf8: 1002a0d1	lslle	r0, r0, r2
00121cfc: 034054e0	subs	r4, r4, r3
00121d00: 041a81a0	addge	r1, r1, r4, lsl #20
00121d04: 051081a1	orrge	r1, r1, r5
00121d08: 3080bda8	popge	{r4, r5, pc}
00121d0c: 0440e0e1	mvn	r4, r4
00121d10: 1f4054e2	subs	r4, r4, #0x1f
00121d14: 0d0000aa	bge	#0x121d50
00121d18: 0c4094e2	adds	r4, r4, #0xc
00121d1c: 050000ca	bgt	#0x121d38
00121d20: 144084e2	add	r4, r4, #0x14
00121d24: 202064e2	rsb	r2, r4, #0x20
00121d28: 3004a0e1	lsr	r0, r0, r4
00121d2c: 110280e1	orr	r0, r0, r1, lsl r2
00121d30: 311485e1	orr	r1, r5, r1, lsr r4
00121d34: 3080bde8	pop	{r4, r5, pc}
00121d38: 0c4064e2	rsb	r4, r4, #0xc
00121d3c: 202064e2	rsb	r2, r4, #0x20
00121d40: 3002a0e1	lsr	r0, r0, r2
00121d44: 110480e1	orr	r0, r0, r1, lsl r4
00121d48: 0510a0e1	mov	r1, r5
00121d4c: 3080bde8	pop	{r4, r5, pc}
00121d50: 3104a0e1	lsr	r0, r1, r4
00121d54: 0510a0e1	mov	r1, r5
00121d58: 3080bde8	pop	{r4, r5, pc}
00121d5c: 000034e3	teq	r4, #0
00121d60: 013623e2	eor	r3, r3, #0x100000
00121d64: 01162102	eoreq	r1, r1, #0x100000
00121d68: 01408402	addeq	r4, r4, #1
00121d6c: 01504512	subne	r5, r5, #1
00121d70: a1ffffea	b	#0x121bfc
00121d74: c4caf0e1	mvns	ip, r4, asr #21
00121d78: c5caf011	mvnsne	ip, r5, asr #21
00121d7c: 1800000a	beq	#0x121de4
00121d80: 050034e1	teq	r4, r5
00121d84: 02003001	teqeq	r0, r2
00121d88: 0300000a	beq	#0x121d9c
00121d8c: 00c094e1	orrs	ip, r4, r0
00121d90: 0310a001	moveq	r1, r3
00121d94: 0200a001	moveq	r0, r2
00121d98: 3080bde8	pop	{r4, r5, pc}
00121d9c: 030031e1	teq	r1, r3
00121da0: 0010a013	movne	r1, #0
00121da4: 0000a013	movne	r0, #0
00121da8: 3080bd18	popne	{r4, r5, pc}
00121dac: a4cab0e1	lsrs	ip, r4, #0x15
00121db0: 0300001a	bne	#0x121dc4
00121db4: 8000b0e1	lsls	r0, r0, #1
00121db8: 0110b1e0	adcs	r1, r1, r1
00121dbc: 02118123	orrhs	r1, r1, #0x80000000
00121dc0: 3080bde8	pop	{r4, r5, pc}
00121dc4: 014594e2	adds	r4, r4, #0x400000
00121dc8: 01168132	addlo	r1, r1, #0x100000
00121dcc: 3080bd38	poplo	{r4, r5, pc}
00121dd0: 025101e2	and	r5, r1, #0x80000000
00121dd4: 7f1485e3	orr	r1, r5, #0x7f000000
00121dd8: 0f1681e3	orr	r1, r1, #0xf00000
00121ddc: 0000a0e3	mov	r0, #0
00121de0: 3080bde8	pop	{r4, r5, pc}
00121de4: c4caf0e1	mvns	ip, r4, asr #21
00121de8: 0310a011	movne	r1, r3
00121dec: 0200a011	movne	r0, r2
00121df0: c5caf001	mvnseq	ip, r5, asr #21
00121df4: 0130a011	movne	r3, r1
00121df8: 0020a011	movne	r2, r0
00121dfc: 014690e1	orrs	r4, r0, r1, lsl #12
00121e00: 03569201	orrseq	r5, r2, r3, lsl #12
00121e04: 03003101	teqeq	r1, r3
00121e08: 02178113	orrne	r1, r1, #0x80000
00121e0c: 3080bde8	pop	{r4, r5, pc}
