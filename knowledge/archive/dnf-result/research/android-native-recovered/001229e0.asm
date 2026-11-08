001229e0: ffc0a0e3	mov	ip, #0xff
001229e4: a02b1ce0	ands	r2, ip, r0, lsr #23
001229e8: a13b1c10	andsne	r3, ip, r1, lsr #23
001229ec: 0c003211	teqne	r2, ip
001229f0: 0c003311	teqne	r3, ip
001229f4: 3a00000a	beq	#0x122ae4
001229f8: 032042e0	sub	r2, r2, r3
001229fc: 01c020e0	eor	ip, r0, r1
00122a00: 8114b0e1	lsls	r1, r1, #9
00122a04: 8004a0e1	lsl	r0, r0, #9
00122a08: 1c00000a	beq	#0x122a80
00122a0c: 0132a0e3	mov	r3, #0x10000000
00122a10: 211283e1	orr	r1, r3, r1, lsr #4
00122a14: 203283e1	orr	r3, r3, r0, lsr #4
00122a18: 02010ce2	and	r0, ip, #0x80000000
00122a1c: 010053e1	cmp	r3, r1
00122a20: 8330a031	lsllo	r3, r3, #1
00122a24: 7d20a2e2	adc	r2, r2, #0x7d
00122a28: 02c5a0e3	mov	ip, #0x800000
00122a2c: 010053e1	cmp	r3, r1
00122a30: 01304320	subhs	r3, r3, r1
00122a34: 0c008021	orrhs	r0, r0, ip
00122a38: a10053e1	cmp	r3, r1, lsr #1
00122a3c: a1304320	subhs	r3, r3, r1, lsr #1
00122a40: ac008021	orrhs	r0, r0, ip, lsr #1
00122a44: 210153e1	cmp	r3, r1, lsr #2
00122a48: 21314320	subhs	r3, r3, r1, lsr #2
00122a4c: 2c018021	orrhs	r0, r0, ip, lsr #2
00122a50: a10153e1	cmp	r3, r1, lsr #3
00122a54: a1314320	subhs	r3, r3, r1, lsr #3
00122a58: ac018021	orrhs	r0, r0, ip, lsr #3
00122a5c: 0332b0e1	lsls	r3, r3, #4
00122a60: 2cc2b011	lsrsne	ip, ip, #4
00122a64: f0ffff1a	bne	#0x122a2c
00122a68: fd0052e3	cmp	r2, #0xfd
00122a6c: 9dffff8a	bhi	#0x1228e8
00122a70: 010053e1	cmp	r3, r1
00122a74: 820ba0e0	adc	r0, r0, r2, lsl #23
00122a78: 0100c003	biceq	r0, r0, #1
00122a7c: 1eff2fe1	bx	lr
00122a80: 02c10ce2	and	ip, ip, #0x80000000
00122a84: a0048ce1	orr	r0, ip, r0, lsr #9
00122a88: 7f2092e2	adds	r2, r2, #0x7f
00122a8c: ff3072c2	rsbsgt	r3, r2, #0xff
00122a90: 820b80c1	orrgt	r0, r0, r2, lsl #23
00122a94: 1eff2fc1	bxgt	lr
00122a98: 020580e3	orr	r0, r0, #0x800000
00122a9c: 0030a0e3	mov	r3, #0
00122aa0: 012052e2	subs	r2, r2, #1
00122aa4: 8fffffea	b	#0x1228e8
00122aa8: 000032e3	teq	r2, #0
00122aac: 02c100e2	and	ip, r0, #0x80000000
00122ab0: 8000a001	lsleq	r0, r0, #1
00122ab4: 02051003	tsteq	r0, #0x800000
00122ab8: 01204202	subeq	r2, r2, #1
00122abc: fbffff0a	beq	#0x122ab0
00122ac0: 0c0080e1	orr	r0, r0, ip
00122ac4: 000033e3	teq	r3, #0
00122ac8: 02c101e2	and	ip, r1, #0x80000000
00122acc: 8110a001	lsleq	r1, r1, #1
00122ad0: 02051103	tsteq	r1, #0x800000
00122ad4: 01304302	subeq	r3, r3, #1
00122ad8: fbffff0a	beq	#0x122acc
00122adc: 0c1081e1	orr	r1, r1, ip
00122ae0: c4ffffea	b	#0x1229f8
00122ae4: a13b0ce0	and	r3, ip, r1, lsr #23
00122ae8: 0c0032e1	teq	r2, ip
00122aec: 0500001a	bne	#0x122b08
00122af0: 8024b0e1	lsls	r2, r0, #9
00122af4: b6ffff1a	bne	#0x1229d4
00122af8: 0c0033e1	teq	r3, ip
00122afc: afffff1a	bne	#0x1229c0
00122b00: 0100a0e1	mov	r0, r1
00122b04: b2ffffea	b	#0x1229d4
00122b08: 0c0033e1	teq	r3, ip
00122b0c: 0300001a	bne	#0x122b20
00122b10: 8134b0e1	lsls	r3, r1, #9
00122b14: 97ffff0a	beq	#0x122978
00122b18: 0100a0e1	mov	r0, r1
00122b1c: acffffea	b	#0x1229d4
00122b20: 02c1d0e3	bics	ip, r0, #0x80000000
00122b24: 02c1d113	bicsne	ip, r1, #0x80000000
00122b28: deffff1a	bne	#0x122aa8
00122b2c: 0221d0e3	bics	r2, r0, #0x80000000
00122b30: a2ffff1a	bne	#0x1229c0
00122b34: 0231d1e3	bics	r3, r1, #0x80000000
00122b38: 8effff1a	bne	#0x122978
00122b3c: a4ffffea	b	#0x1229d4
