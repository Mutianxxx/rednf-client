000f178c: 4b1e	subs	r3, r1, #1
000f178e: 012b	cmp	r3, #1
000f1790: 09d8	bhi	#0xf17a6
000f1792: 0023	movs	r3, #0
000f1794: 4360	str	r3, [r0, #4]
000f1796: c160	str	r1, [r0, #0xc]
000f1798: 0361	str	r3, [r0, #0x10]
000f179a: c361	str	r3, [r0, #0x1c]
000f179c: 8362	str	r3, [r0, #0x28]
000f179e: 4363	str	r3, [r0, #0x34]
000f17a0: 0364	str	r3, [r0, #0x40]
000f17a2: c364	str	r3, [r0, #0x4c]
000f17a4: 7047	bx	lr
000f17a6: 0623	movs	r3, #6
000f17a8: 4360	str	r3, [r0, #4]
000f17aa: c160	str	r1, [r0, #0xc]
000f17ac: fae7	b	#0xf17a4
