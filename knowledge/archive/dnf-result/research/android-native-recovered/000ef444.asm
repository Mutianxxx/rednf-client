000ef444: 0268	ldr	r2, [r0]
000ef446: f223	movs	r3, #0xf2
000ef448: 5b00	lsls	r3, r3, #1
000ef44a: d158	ldr	r1, [r2, r3]
000ef44c: d023	movs	r3, #0xd0
000ef44e: 5b00	lsls	r3, r3, #1
000ef450: d358	ldr	r3, [r2, r3]
000ef452: 8361	str	r3, [r0, #0x18]
000ef454: d223	movs	r3, #0xd2
000ef456: 5b00	lsls	r3, r3, #1
000ef458: d358	ldr	r3, [r2, r3]
000ef45a: c361	str	r3, [r0, #0x1c]
000ef45c: 4b69	ldr	r3, [r1, #0x14]
000ef45e: 4361	str	r3, [r0, #0x14]
000ef460: cb69	ldr	r3, [r1, #0x1c]
000ef462: 0361	str	r3, [r0, #0x10]
000ef464: 0020	movs	r0, #0
000ef466: 7047	bx	lr
