000f5ff4: 30b5	push	{r4, r5, lr}
000f5ff6: 124b	ldr	r3, [pc, #0x48]
000f5ff8: 9942	cmp	r1, r3
000f5ffa: 0cd8	bhi	#0xf6016
000f5ffc: 114d	ldr	r5, [pc, #0x44]
000f5ffe: 0b0a	lsrs	r3, r1, #8
000f6000: 841d	adds	r4, r0, #6
000f6002: 4219	adds	r2, r0, r5
000f6004: 002b	cmp	r3, #0
000f6006: 08d1	bne	#0xf601a
000f6008: ff23	movs	r3, #0xff
000f600a: 1940	ands	r1, r3
000f600c: 4900	lsls	r1, r1, #1
000f600e: 6418	adds	r4, r4, r1
000f6010: 2378	ldrb	r3, [r4]
000f6012: 002b	cmp	r3, #0
000f6014: 0ed0	beq	#0xf6034
000f6016: 0020	movs	r0, #0
000f6018: 30bd	pop	{r4, r5, pc}
000f601a: 5b00	lsls	r3, r3, #1
000f601c: e418	adds	r4, r4, r3
000f601e: 2378	ldrb	r3, [r4]
000f6020: 6178	ldrb	r1, [r4, #1]
000f6022: 1b02	lsls	r3, r3, #8
000f6024: 0b43	orrs	r3, r1
000f6026: 0721	movs	r1, #7
000f6028: 8b43	bics	r3, r1
000f602a: d318	adds	r3, r2, r3
000f602c: 181c	adds	r0, r3, #0
000f602e: 9342	cmp	r3, r2
000f6030: f2d1	bne	#0xf6018
000f6032: f0e7	b	#0xf6016
000f6034: 6378	ldrb	r3, [r4, #1]
000f6036: 101c	adds	r0, r2, #0
000f6038: 002b	cmp	r3, #0
000f603a: edd0	beq	#0xf6018
000f603c: ebe7	b	#0xf6016
000f603e: c046	mov	r8, r8
000f6040: ffff	.byte	0xff, 0xff
000f6042: 0000	movs	r0, r0
000f6044: 0602	lsls	r6, r0, #8
000f6046: 0000	movs	r0, r0
