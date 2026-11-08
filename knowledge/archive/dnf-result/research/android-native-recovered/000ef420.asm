000ef420: 0268	ldr	r2, [r0]
000ef422: f223	movs	r3, #0xf2
000ef424: 5b00	lsls	r3, r3, #1
000ef426: d158	ldr	r1, [r2, r3]
000ef428: d023	movs	r3, #0xd0
000ef42a: 5b00	lsls	r3, r3, #1
000ef42c: d358	ldr	r3, [r2, r3]
000ef42e: 8361	str	r3, [r0, #0x18]
000ef430: d223	movs	r3, #0xd2
000ef432: 5b00	lsls	r3, r3, #1
000ef434: d358	ldr	r3, [r2, r3]
000ef436: c361	str	r3, [r0, #0x1c]
000ef438: 4b69	ldr	r3, [r1, #0x14]
000ef43a: 4361	str	r3, [r0, #0x14]
000ef43c: 8b69	ldr	r3, [r1, #0x18]
000ef43e: 0361	str	r3, [r0, #0x10]
000ef440: 0020	movs	r0, #0
000ef442: 7047	bx	lr
