000ef494: 0369	ldr	r3, [r0, #0x10]
000ef496: 8b42	cmp	r3, r1
000ef498: 07d8	bhi	#0xef4aa
000ef49a: 4269	ldr	r2, [r0, #0x14]
000ef49c: 9b18	adds	r3, r3, r2
000ef49e: 9942	cmp	r1, r3
000ef4a0: 03d2	bhs	#0xef4aa
000ef4a2: 8369	ldr	r3, [r0, #0x18]
000ef4a4: 4900	lsls	r1, r1, #1
000ef4a6: c85a	ldrh	r0, [r1, r3]
000ef4a8: 00e0	b	#0xef4ac
000ef4aa: 0020	movs	r0, #0
000ef4ac: 7047	bx	lr
