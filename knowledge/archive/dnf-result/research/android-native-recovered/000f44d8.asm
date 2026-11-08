000f44d8: 70b5	push	{r4, r5, r6, lr}
000f44da: 056b	ldr	r5, [r0, #0x30]
000f44dc: 031c	adds	r3, r0, #0
000f44de: 006a	ldr	r0, [r0, #0x20]
000f44e0: 6a1e	subs	r2, r5, #1
000f44e2: 0fd4	bmi	#0xf4504
000f44e4: ae00	lsls	r6, r5, #2
000f44e6: 861b	subs	r6, r0, r6
000f44e8: 9000	lsls	r0, r2, #2
000f44ea: 8459	ldr	r4, [r0, r6]
000f44ec: a142	cmp	r1, r4
000f44ee: 19da	bge	#0xf4524
000f44f0: a81e	subs	r0, r5, #2
000f44f2: 8000	lsls	r0, r0, #2
000f44f4: 3018	adds	r0, r6, r0
000f44f6: 03e0	b	#0xf4500
000f44f8: 0468	ldr	r4, [r0]
000f44fa: 0438	subs	r0, #4
000f44fc: 8c42	cmp	r4, r1
000f44fe: 11dd	ble	#0xf4524
000f4500: 013a	subs	r2, #1
000f4502: f9d2	bhs	#0xf44f8
000f4504: 5a6a	ldr	r2, [r3, #0x24]
000f4506: 0c1c	adds	r4, r1, #0
000f4508: 996a	ldr	r1, [r3, #0x28]
000f450a: 043a	subs	r2, #4
000f450c: 5a62	str	r2, [r3, #0x24]
000f450e: 8a42	cmp	r2, r1
000f4510: 1ad9	bls	#0xf4548
000f4512: 1a6b	ldr	r2, [r3, #0x30]
000f4514: 0020	movs	r0, #0
000f4516: 0132	adds	r2, #1
000f4518: 1a63	str	r2, [r3, #0x30]
000f451a: 1b6a	ldr	r3, [r3, #0x20]
000f451c: 9200	lsls	r2, r2, #2
000f451e: 5242	rsbs	r2, r2, #0
000f4520: d450	str	r4, [r2, r3]
000f4522: 70bd	pop	{r4, r5, r6, pc}
000f4524: 0020	movs	r0, #0
000f4526: 8c42	cmp	r4, r1
000f4528: fbda	bge	#0xf4522
000f452a: 9000	lsls	r0, r2, #2
000f452c: 3018	adds	r0, r6, r0
000f452e: 02e0	b	#0xf4536
000f4530: 0438	subs	r0, #4
000f4532: 211c	adds	r1, r4, #0
000f4534: 0468	ldr	r4, [r0]
000f4536: 0160	str	r1, [r0]
000f4538: 013a	subs	r2, #1
000f453a: f9d2	bhs	#0xf4530
000f453c: 5a6a	ldr	r2, [r3, #0x24]
000f453e: 996a	ldr	r1, [r3, #0x28]
000f4540: 043a	subs	r2, #4
000f4542: 5a62	str	r2, [r3, #0x24]
000f4544: 8a42	cmp	r2, r1
000f4546: e4d8	bhi	#0xf4512
000f4548: 6222	movs	r2, #0x62
000f454a: da62	str	r2, [r3, #0x2c]
000f454c: 0120	movs	r0, #1
000f454e: e8e7	b	#0xf4522
