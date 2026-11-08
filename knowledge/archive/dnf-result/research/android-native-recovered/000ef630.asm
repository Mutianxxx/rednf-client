000ef630: 0268	ldr	r2, [r0]
000ef632: 4368	ldr	r3, [r0, #4]
000ef634: 0120	movs	r0, #1
000ef636: 1204	lsls	r2, r2, #0x10
000ef638: 1a43	orrs	r2, r3
000ef63a: 0b68	ldr	r3, [r1]
000ef63c: 4968	ldr	r1, [r1, #4]
000ef63e: 1b04	lsls	r3, r3, #0x10
000ef640: 0b43	orrs	r3, r1
000ef642: 9a42	cmp	r2, r3
000ef644: 00d9	bls	#0xef648
000ef646: 7047	bx	lr
000ef648: 9a42	cmp	r2, r3
000ef64a: 8041	sbcs	r0, r0
000ef64c: fbe7	b	#0xef646
