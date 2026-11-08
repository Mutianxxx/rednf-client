00121e9c: 012090e1	orrs	r2, r0, r1
00121ea0: 1eff2f01	bxeq	lr
00121ea4: 30402de9	push	{r4, r5, lr}
00121ea8: 0050a0e3	mov	r5, #0
00121eac: 060000ea	b	#0x121ecc
00121eb0: 012090e1	orrs	r2, r0, r1
00121eb4: 1eff2f01	bxeq	lr
00121eb8: 30402de9	push	{r4, r5, lr}
00121ebc: 025111e2	ands	r5, r1, #0x80000000
00121ec0: 0100005a	bpl	#0x121ecc
00121ec4: 000070e2	rsbs	r0, r0, #0
00121ec8: 0010e1e2	rsc	r1, r1, #0
00121ecc: 014ba0e3	mov	r4, #0x400
00121ed0: 324084e2	add	r4, r4, #0x32
00121ed4: 21cbb0e1	lsrs	ip, r1, #0x16
00121ed8: 5cffff0a	beq	#0x121c50
00121edc: 0320a0e3	mov	r2, #3
00121ee0: acc1b0e1	lsrs	ip, ip, #3
00121ee4: 03208212	addne	r2, r2, #3
00121ee8: acc1b0e1	lsrs	ip, ip, #3
00121eec: 03208212	addne	r2, r2, #3
00121ef0: ac2182e0	add	r2, r2, ip, lsr #3
00121ef4: 203062e2	rsb	r3, r2, #0x20
00121ef8: 10c3a0e1	lsl	ip, r0, r3
00121efc: 3002a0e1	lsr	r0, r0, r2
00121f00: 110380e1	orr	r0, r0, r1, lsl r3
00121f04: 3112a0e1	lsr	r1, r1, r2
00121f08: 024084e0	add	r4, r4, r2
00121f0c: 4fffffea	b	#0x121c50
