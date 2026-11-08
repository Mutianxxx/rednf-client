00122380: 00c0e0e3	mvn	ip, #0
00122384: 020000ea	b	#0x122394
00122388: 01c0a0e3	mov	ip, #1
0012238c: 000000ea	b	#0x122394
00122390: 01c0a0e3	mov	ip, #1
00122394: 04c00de5	str	ip, [sp, #-4]
00122398: 81c0a0e1	lsl	ip, r1, #1
0012239c: cccaf0e1	mvns	ip, ip, asr #21
001223a0: 83c0a0e1	lsl	ip, r3, #1
001223a4: cccaf011	mvnsne	ip, ip, asr #21
001223a8: 0d00000a	beq	#0x1223e4
001223ac: 81c090e1	orrs	ip, r0, r1, lsl #1
001223b0: 83c09201	orrseq	ip, r2, r3, lsl #1
001223b4: 03003111	teqne	r1, r3
001223b8: 02003001	teqeq	r0, r2
001223bc: 0000a003	moveq	r0, #0
001223c0: 1eff2f01	bxeq	lr
001223c4: 000070e3	cmn	r0, #0
001223c8: 030031e1	teq	r1, r3
001223cc: 03005151	cmppl	r1, r3
001223d0: 02005001	cmpeq	r0, r2
001223d4: c30fa021	asrhs	r0, r3, #0x1f
001223d8: c30fe031	mvnlo	r0, r3, asr #31
001223dc: 010080e3	orr	r0, r0, #1
001223e0: 1eff2fe1	bx	lr
001223e4: 81c0a0e1	lsl	ip, r1, #1
001223e8: cccaf0e1	mvns	ip, ip, asr #21
001223ec: 0100001a	bne	#0x1223f8
001223f0: 01c690e1	orrs	ip, r0, r1, lsl #12
001223f4: 0400001a	bne	#0x12240c
001223f8: 83c0a0e1	lsl	ip, r3, #1
001223fc: cccaf0e1	mvns	ip, ip, asr #21
00122400: e9ffff1a	bne	#0x1223ac
00122404: 03c692e1	orrs	ip, r2, r3, lsl #12
00122408: e7ffff0a	beq	#0x1223ac
0012240c: 04001de5	ldr	r0, [sp, #-4]
00122410: 1eff2fe1	bx	lr
