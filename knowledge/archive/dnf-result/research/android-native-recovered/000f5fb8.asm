000f5fb8: 0b68	ldr	r3, [r1]
000f5fba: 0269	ldr	r2, [r0, #0x10]
000f5fbc: d218	adds	r2, r2, r3
000f5fbe: 0133	adds	r3, #1
000f5fc0: ff2b	cmp	r3, #0xff
000f5fc2: 05d8	bhi	#0xf5fd0
000f5fc4: d079	ldrb	r0, [r2, #7]
000f5fc6: 0132	adds	r2, #1
000f5fc8: 0028	cmp	r0, #0
000f5fca: f8d0	beq	#0xf5fbe
000f5fcc: 0b60	str	r3, [r1]
000f5fce: 7047	bx	lr
000f5fd0: 0020	movs	r0, #0
000f5fd2: 0023	movs	r3, #0
000f5fd4: fae7	b	#0xf5fcc
