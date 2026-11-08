000f45a8: f0b5	push	{r4, r5, r6, r7, lr}
000f45aa: 0169	ldr	r1, [r0, #0x10]
000f45ac: 8769	ldr	r7, [r0, #0x18]
000f45ae: 8568	ldr	r5, [r0, #8]
000f45b0: 0468	ldr	r4, [r0]
000f45b2: 0763	str	r7, [r0, #0x30]
000f45b4: cf19	adds	r7, r1, r7
000f45b6: 2c19	adds	r4, r5, r4
000f45b8: 6d18	adds	r5, r5, r1
000f45ba: 0134	adds	r4, #1
000f45bc: 0137	adds	r7, #1
000f45be: 0135	adds	r5, #1
000f45c0: 7f10	asrs	r7, r7, #1
000f45c2: 6d10	asrs	r5, r5, #1
000f45c4: 6410	asrs	r4, r4, #1
000f45c6: 8460	str	r4, [r0, #8]
000f45c8: 7919	adds	r1, r7, r5
000f45ca: 6419	adds	r4, r4, r5
000f45cc: 0134	adds	r4, #1
000f45ce: 0131	adds	r1, #1
000f45d0: 6410	asrs	r4, r4, #1
000f45d2: 4910	asrs	r1, r1, #1
000f45d4: 0162	str	r1, [r0, #0x20]
000f45d6: 6118	adds	r1, r4, r1
000f45d8: 0131	adds	r1, #1
000f45da: 031c	adds	r3, r0, #0
000f45dc: 4910	asrs	r1, r1, #1
000f45de: 8762	str	r7, [r0, #0x28]
000f45e0: 0461	str	r4, [r0, #0x10]
000f45e2: 8161	str	r1, [r0, #0x18]
000f45e4: 1833	adds	r3, #0x18
000f45e6: 5968	ldr	r1, [r3, #4]
000f45e8: 021c	adds	r2, r0, #0
000f45ea: 0832	adds	r2, #8
000f45ec: 4163	str	r1, [r0, #0x34]
000f45ee: 5468	ldr	r4, [r2, #4]
000f45f0: 4168	ldr	r1, [r0, #4]
000f45f2: 061c	adds	r6, r0, #0
000f45f4: 1036	adds	r6, #0x10
000f45f6: 6118	adds	r1, r4, r1
000f45f8: 0131	adds	r1, #1
000f45fa: 4910	asrs	r1, r1, #1
000f45fc: 7768	ldr	r7, [r6, #4]
000f45fe: 5160	str	r1, [r2, #4]
000f4600: 5d68	ldr	r5, [r3, #4]
000f4602: e419	adds	r4, r4, r7
000f4604: 0134	adds	r4, #1
000f4606: 7d19	adds	r5, r7, r5
000f4608: 0135	adds	r5, #1
000f460a: 6d10	asrs	r5, r5, #1
000f460c: 6410	asrs	r4, r4, #1
000f460e: 2a19	adds	r2, r5, r4
000f4610: 0919	adds	r1, r1, r4
000f4612: 0131	adds	r1, #1
000f4614: 0132	adds	r2, #1
000f4616: 4910	asrs	r1, r1, #1
000f4618: 5210	asrs	r2, r2, #1
000f461a: c562	str	r5, [r0, #0x2c]
000f461c: 7160	str	r1, [r6, #4]
000f461e: 4262	str	r2, [r0, #0x24]
000f4620: 8a18	adds	r2, r1, r2
000f4622: 0132	adds	r2, #1
000f4624: 5210	asrs	r2, r2, #1
000f4626: 5a60	str	r2, [r3, #4]
000f4628: f0bd	pop	{r4, r5, r6, r7, pc}
