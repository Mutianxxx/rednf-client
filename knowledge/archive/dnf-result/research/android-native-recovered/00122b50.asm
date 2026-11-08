00122b50: 01c0a0e3	mov	ip, #1
00122b54: 04c00de5	str	ip, [sp, #-4]
00122b58: 8020a0e1	lsl	r2, r0, #1
00122b5c: 8130a0e1	lsl	r3, r1, #1
00122b60: 42ccf0e1	mvns	ip, r2, asr #24
00122b64: 43ccf011	mvnsne	ip, r3, asr #24
00122b68: 0600000a	beq	#0x122b88
00122b6c: a3c092e1	orrs	ip, r2, r3, lsr #1
00122b70: 01003011	teqne	r0, r1
00122b74: 03005250	subspl	r0, r2, r3
00122b78: c10fa081	asrhi	r0, r1, #0x1f
00122b7c: c10fe031	mvnlo	r0, r1, asr #31
00122b80: 01008013	orrne	r0, r0, #1
00122b84: 1eff2fe1	bx	lr
00122b88: 42ccf0e1	mvns	ip, r2, asr #24
00122b8c: 0100001a	bne	#0x122b98
00122b90: 80c4b0e1	lsls	ip, r0, #9
00122b94: 0300001a	bne	#0x122ba8
00122b98: 43ccf0e1	mvns	ip, r3, asr #24
00122b9c: f2ffff1a	bne	#0x122b6c
00122ba0: 81c4b0e1	lsls	ip, r1, #9
00122ba4: f0ffff0a	beq	#0x122b6c
00122ba8: 04001de5	ldr	r0, [sp, #-4]
00122bac: 1eff2fe1	bx	lr
