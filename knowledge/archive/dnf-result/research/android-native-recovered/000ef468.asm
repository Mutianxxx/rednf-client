000ef468: 0268	ldr	r2, [r0]
000ef46a: bc23	movs	r3, #0xbc
000ef46c: 5b00	lsls	r3, r3, #1
000ef46e: d158	ldr	r1, [r2, r3]
000ef470: be23	movs	r3, #0xbe
000ef472: 5b00	lsls	r3, r3, #1
000ef474: 0161	str	r1, [r0, #0x10]
000ef476: d358	ldr	r3, [r2, r3]
000ef478: 591a	subs	r1, r3, r1
000ef47a: c023	movs	r3, #0xc0
000ef47c: 4161	str	r1, [r0, #0x14]
000ef47e: 5b00	lsls	r3, r3, #1
000ef480: d358	ldr	r3, [r2, r3]
000ef482: 8361	str	r3, [r0, #0x18]
000ef484: 0020	movs	r0, #0
000ef486: 7047	bx	lr
