000f13ac: f0b5	push	{r4, r5, r6, r7, lr}
000f13ae: 5f46	mov	r7, fp
000f13b0: 5646	mov	r6, sl
000f13b2: 4d46	mov	r5, sb
000f13b4: 4446	mov	r4, r8
000f13b6: f0b4	push	{r4, r5, r6, r7}
000f13b8: 0168	ldr	r1, [r0]
000f13ba: 8568	ldr	r5, [r0, #8]
000f13bc: a9b0	sub	sp, #0xa4
000f13be: 041c	adds	r4, r0, #0
000f13c0: 8a46	mov	sl, r1
000f13c2: 0627	movs	r7, #6
000f13c4: 002d	cmp	r5, #0
000f13c6: 0cd0	beq	#0xf13e2
000f13c8: 27aa	add	r2, sp, #0x9c
000f13ca: 0023	movs	r3, #0
000f13cc: 111c	adds	r1, r2, #0
000f13ce: 2693	str	r3, [sp, #0x98]
000f13d0: 9046	mov	r8, r2
000f13d2: fff7cbff	bl	#0xf136c
000f13d6: 0028	cmp	r0, #0
000f13d8: 02d0	beq	#0xf13e0
000f13da: 279b	ldr	r3, [sp, #0x9c]
000f13dc: 102b	cmp	r3, #0x10
000f13de: 08d0	beq	#0xf13f2
000f13e0: 0227	movs	r7, #2
000f13e2: 29b0	add	sp, #0xa4
000f13e4: 381c	adds	r0, r7, #0
000f13e6: 3cbc	pop	{r2, r3, r4, r5}
000f13e8: 9046	mov	r8, r2
000f13ea: 9946	mov	sb, r3
000f13ec: a246	mov	sl, r4
000f13ee: ab46	mov	fp, r5
000f13f0: f0bd	pop	{r4, r5, r6, r7, pc}
000f13f2: ca49	ldr	r1, [pc, #0x328]
000f13f4: 1022	movs	r2, #0x10
000f13f6: 7944	add	r1, pc
000f13f8: 43f7c2ee	blx	#0x35180
000f13fc: 0028	cmp	r0, #0
000f13fe: efd1	bne	#0xf13e0
000f1400: c74b	ldr	r3, [pc, #0x31c]
000f1402: 6946	mov	r1, sp
000f1404: 8c31	adds	r1, #0x8c
000f1406: 6a46	mov	r2, sp
000f1408: 9946	mov	sb, r3
000f140a: 0491	str	r1, [sp, #0x10]
000f140c: 9432	adds	r2, #0x94
000f140e: 0223	movs	r3, #2
000f1410: 0c31	adds	r1, #0xc
000f1412: a027	movs	r7, #0xa0
000f1414: f944	add	sb, pc
000f1416: 0392	str	r2, [sp, #0xc]
000f1418: 1bae	add	r6, sp, #0x6c
000f141a: 9b46	mov	fp, r3
000f141c: 0591	str	r1, [sp, #0x14]
000f141e: 201c	adds	r0, r4, #0
000f1420: 4146	mov	r1, r8
000f1422: fff7a3ff	bl	#0xf136c
000f1426: 0028	cmp	r0, #0
000f1428: 55d0	beq	#0xf14d6
000f142a: 2799	ldr	r1, [sp, #0x9c]
000f142c: fef7b4fa	bl	#0xef998
000f1430: 3128	cmp	r0, #0x31
000f1432: f4d8	bhi	#0xf141e
000f1434: 8000	lsls	r0, r0, #2
000f1436: 4a46	mov	r2, sb
000f1438: 8358	ldr	r3, [r0, r2]
000f143a: 4b44	add	r3, sb
000f143c: 9f46	mov	pc, r3
000f143e: 0027	movs	r7, #0
000f1440: cfe7	b	#0xf13e2
000f1442: 5b46	mov	r3, fp
000f1444: 3360	str	r3, [r6]
000f1446: 201c	adds	r0, r4, #0
000f1448: 311c	adds	r1, r6, #0
000f144a: 0122	movs	r2, #1
000f144c: fef7b6fb	bl	#0xefbbc
000f1450: 0128	cmp	r0, #1
000f1452: 40d1	bne	#0xf14d6
000f1454: 7368	ldr	r3, [r6, #4]
000f1456: ab61	str	r3, [r5, #0x18]
000f1458: e1e7	b	#0xf141e
000f145a: 5a46	mov	r2, fp
000f145c: 3260	str	r2, [r6]
000f145e: 201c	adds	r0, r4, #0
000f1460: 311c	adds	r1, r6, #0
000f1462: 0122	movs	r2, #1
000f1464: fef7aafb	bl	#0xefbbc
000f1468: 0128	cmp	r0, #1
000f146a: 34d1	bne	#0xf14d6
000f146c: 7368	ldr	r3, [r6, #4]
000f146e: 6b61	str	r3, [r5, #0x14]
000f1470: d5e7	b	#0xf141e
000f1472: 0021	movs	r1, #0
000f1474: 2391	str	r1, [sp, #0x8c]
000f1476: 201c	adds	r0, r4, #0
000f1478: 0499	ldr	r1, [sp, #0x10]
000f147a: fef71ffc	bl	#0xefcbc
000f147e: 0028	cmp	r0, #0
000f1480: 29d1	bne	#0xf14d6
000f1482: 239a	ldr	r2, [sp, #0x8c]
000f1484: 0027	movs	r7, #0
000f1486: 0292	str	r2, [sp, #8]
000f1488: 029b	ldr	r3, [sp, #8]
000f148a: 9f42	cmp	r7, r3
000f148c: 08d0	beq	#0xf14a0
000f148e: 201c	adds	r0, r4, #0
000f1490: 0021	movs	r1, #0
000f1492: fff76bff	bl	#0xf136c
000f1496: 0137	adds	r7, #1
000f1498: 0028	cmp	r0, #0
000f149a: f5d1	bne	#0xf1488
000f149c: a027	movs	r7, #0xa0
000f149e: a0e7	b	#0xf13e2
000f14a0: 201c	adds	r0, r4, #0
000f14a2: 0399	ldr	r1, [sp, #0xc]
000f14a4: fff762ff	bl	#0xf136c
000f14a8: 0028	cmp	r0, #0
000f14aa: f7d0	beq	#0xf149c
000f14ac: 2599	ldr	r1, [sp, #0x94]
000f14ae: fef773fa	bl	#0xef998
000f14b2: 1428	cmp	r0, #0x14
000f14b4: 01d0	beq	#0xf14ba
000f14b6: 1128	cmp	r0, #0x11
000f14b8: f2d1	bne	#0xf14a0
000f14ba: 0027	movs	r7, #0
000f14bc: afe7	b	#0xf141e
000f14be: 201c	adds	r0, r4, #0
000f14c0: 0599	ldr	r1, [sp, #0x14]
000f14c2: fef7fbfb	bl	#0xefcbc
000f14c6: 0028	cmp	r0, #0
000f14c8: 05d1	bne	#0xf14d6
000f14ca: 269b	ldr	r3, [sp, #0x98]
000f14cc: 022b	cmp	r3, #2
000f14ce: a6d0	beq	#0xf141e
000f14d0: 002b	cmp	r3, #0
000f14d2: a4d0	beq	#0xf141e
000f14d4: 0727	movs	r7, #7
000f14d6: 0024	movs	r4, #0
000f14d8: e969	ldr	r1, [r5, #0x1c]
000f14da: 5046	mov	r0, sl
000f14dc: f6f7e4fd	bl	#0xe80a8
000f14e0: ec61	str	r4, [r5, #0x1c]
000f14e2: 2c62	str	r4, [r5, #0x20]
000f14e4: 696a	ldr	r1, [r5, #0x24]
000f14e6: 5046	mov	r0, sl
000f14e8: f6f7defd	bl	#0xe80a8
000f14ec: 6c62	str	r4, [r5, #0x24]
000f14ee: ac62	str	r4, [r5, #0x28]
000f14f0: 2c70	strb	r4, [r5]
000f14f2: 76e7	b	#0xf13e2
000f14f4: 0423	movs	r3, #4
000f14f6: 3360	str	r3, [r6]
000f14f8: 201c	adds	r0, r4, #0
000f14fa: 311c	adds	r1, r6, #0
000f14fc: 0122	movs	r2, #1
000f14fe: fef75dfb	bl	#0xefbbc
000f1502: 0128	cmp	r0, #1
000f1504: e7d1	bne	#0xf14d6
000f1506: 3379	ldrb	r3, [r6, #4]
000f1508: 2b70	strb	r3, [r5]
000f150a: 88e7	b	#0xf141e
000f150c: 5946	mov	r1, fp
000f150e: 3160	str	r1, [r6]
000f1510: b160	str	r1, [r6, #8]
000f1512: 3161	str	r1, [r6, #0x10]
000f1514: b161	str	r1, [r6, #0x18]
000f1516: 201c	adds	r0, r4, #0
000f1518: 311c	adds	r1, r6, #0
000f151a: 0422	movs	r2, #4
000f151c: fef74efb	bl	#0xefbbc
000f1520: 0428	cmp	r0, #4
000f1522: d8d1	bne	#0xf14d6
000f1524: 7368	ldr	r3, [r6, #4]
000f1526: 6b60	str	r3, [r5, #4]
000f1528: f368	ldr	r3, [r6, #0xc]
000f152a: ab60	str	r3, [r5, #8]
000f152c: 7369	ldr	r3, [r6, #0x14]
000f152e: eb60	str	r3, [r5, #0xc]
000f1530: f369	ldr	r3, [r6, #0x1c]
000f1532: 2b61	str	r3, [r5, #0x10]
000f1534: 73e7	b	#0xf141e
000f1536: 25ab	add	r3, sp, #0x94
000f1538: 9b46	mov	fp, r3
000f153a: 7a4a	ldr	r2, [pc, #0x1e8]
000f153c: 7a4b	ldr	r3, [pc, #0x1e8]
000f153e: 7b4e	ldr	r6, [pc, #0x1ec]
000f1540: 6946	mov	r1, sp
000f1542: 8c31	adds	r1, #0x8c
000f1544: 9146	mov	sb, r2
000f1546: 7b44	add	r3, pc
000f1548: 7e44	add	r6, pc
000f154a: 0591	str	r1, [sp, #0x14]
000f154c: f944	add	sb, pc
000f154e: 0293	str	r3, [sp, #8]
000f1550: 5f46	mov	r7, fp
000f1552: 201c	adds	r0, r4, #0
000f1554: 391c	adds	r1, r7, #0
000f1556: fff709ff	bl	#0xf136c
000f155a: 0028	cmp	r0, #0
000f155c: 05d0	beq	#0xf156a
000f155e: 2599	ldr	r1, [sp, #0x94]
000f1560: fef71afa	bl	#0xef998
000f1564: 1438	subs	r0, #0x14
000f1566: 3728	cmp	r0, #0x37
000f1568: 01d9	bls	#0xf156e
000f156a: a027	movs	r7, #0xa0
000f156c: b3e7	b	#0xf14d6
000f156e: 8000	lsls	r0, r0, #2
000f1570: 8359	ldr	r3, [r0, r6]
000f1572: 9b19	adds	r3, r3, r6
000f1574: 9f46	mov	pc, r3
000f1576: a168	ldr	r1, [r4, #8]
000f1578: 201c	adds	r0, r4, #0
000f157a: 8b46	mov	fp, r1
000f157c: 2031	adds	r1, #0x20
000f157e: fef79dfb	bl	#0xefcbc
000f1582: 0028	cmp	r0, #0
000f1584: f1d1	bne	#0xf156a
000f1586: 5a46	mov	r2, fp
000f1588: 136a	ldr	r3, [r2, #0x20]
000f158a: 002b	cmp	r3, #0
000f158c: 00d0	beq	#0xf1590
000f158e: cfe0	b	#0xf1730
000f1590: 0023	movs	r3, #0
000f1592: 0121	movs	r1, #1
000f1594: 0493	str	r3, [sp, #0x10]
000f1596: 4942	rsbs	r1, r1, #0
000f1598: 331c	adds	r3, r6, #0
000f159a: 09aa	add	r2, sp, #0x24
000f159c: 2e1c	adds	r6, r5, #0
000f159e: b846	mov	r8, r7
000f15a0: 0391	str	r1, [sp, #0xc]
000f15a2: 151c	adds	r5, r2, #0
000f15a4: 1f1c	adds	r7, r3, #0
000f15a6: 201c	adds	r0, r4, #0
000f15a8: 0599	ldr	r1, [sp, #0x14]
000f15aa: fff7dffe	bl	#0xf136c
000f15ae: 0028	cmp	r0, #0
000f15b0: 00d1	bne	#0xf15b4
000f15b2: 81e0	b	#0xf16b8
000f15b4: 2399	ldr	r1, [sp, #0x8c]
000f15b6: fef7eff9	bl	#0xef998
000f15ba: 1728	cmp	r0, #0x17
000f15bc: 7fd0	beq	#0xf16be
000f15be: 1728	cmp	r0, #0x17
000f15c0: 75d8	bhi	#0xf16ae
000f15c2: 1438	subs	r0, #0x14
000f15c4: 351c	adds	r5, r6, #0
000f15c6: 3e1c	adds	r6, r7, #0
000f15c8: 4746	mov	r7, r8
000f15ca: 0128	cmp	r0, #1
000f15cc: cdd8	bhi	#0xf156a
000f15ce: 039b	ldr	r3, [sp, #0xc]
000f15d0: 5946	mov	r1, fp
000f15d2: 0133	adds	r3, #1
000f15d4: 0b62	str	r3, [r1, #0x20]
000f15d6: bce7	b	#0xf1552
000f15d8: a368	ldr	r3, [r4, #8]
000f15da: 201c	adds	r0, r4, #0
000f15dc: 191c	adds	r1, r3, #0
000f15de: 2831	adds	r1, #0x28
000f15e0: 9846	mov	r8, r3
000f15e2: fef76bfb	bl	#0xefcbc
000f15e6: 0028	cmp	r0, #0
000f15e8: bfd1	bne	#0xf156a
000f15ea: 4146	mov	r1, r8
000f15ec: 8b6a	ldr	r3, [r1, #0x28]
000f15ee: 002b	cmp	r3, #0
000f15f0: 00d0	beq	#0xf15f4
000f15f2: afe0	b	#0xf1754
000f15f4: 6b46	mov	r3, sp
000f15f6: 9033	adds	r3, #0x90
000f15f8: 0122	movs	r2, #1
000f15fa: 5242	rsbs	r2, r2, #0
000f15fc: 0693	str	r3, [sp, #0x18]
000f15fe: 13a9	add	r1, sp, #0x4c
000f1600: 4b46	mov	r3, sb
000f1602: bb46	mov	fp, r7
000f1604: b146	mov	sb, r6
000f1606: 0392	str	r2, [sp, #0xc]
000f1608: 261c	adds	r6, r4, #0
000f160a: 1f1c	adds	r7, r3, #0
000f160c: 0c1c	adds	r4, r1, #0
000f160e: 301c	adds	r0, r6, #0
000f1610: 0699	ldr	r1, [sp, #0x18]
000f1612: fff7abfe	bl	#0xf136c
000f1616: 0028	cmp	r0, #0
000f1618: a7d0	beq	#0xf156a
000f161a: 2499	ldr	r1, [sp, #0x90]
000f161c: fef7bcf9	bl	#0xef998
000f1620: 031c	adds	r3, r0, #0
000f1622: 143b	subs	r3, #0x14
000f1624: 0490	str	r0, [sp, #0x10]
000f1626: 372b	cmp	r3, #0x37
000f1628: 9fd8	bhi	#0xf156a
000f162a: 9b00	lsls	r3, r3, #2
000f162c: db59	ldr	r3, [r3, r7]
000f162e: db19	adds	r3, r3, r7
000f1630: 9f46	mov	pc, r3
000f1632: 039b	ldr	r3, [sp, #0xc]
000f1634: 4146	mov	r1, r8
000f1636: 0133	adds	r3, #1
000f1638: 0393	str	r3, [sp, #0xc]
000f163a: 8b6a	ldr	r3, [r1, #0x28]
000f163c: 039a	ldr	r2, [sp, #0xc]
000f163e: 9a42	cmp	r2, r3
000f1640: 93da	bge	#0xf156a
000f1642: 4b6a	ldr	r3, [r1, #0x24]
000f1644: 0322	movs	r2, #3
000f1646: 0521	movs	r1, #5
000f1648: 0793	str	r3, [sp, #0x1c]
000f164a: 301c	adds	r0, r6, #0
000f164c: 2160	str	r1, [r4]
000f164e: a160	str	r1, [r4, #8]
000f1650: 2261	str	r2, [r4, #0x10]
000f1652: a261	str	r2, [r4, #0x18]
000f1654: 211c	adds	r1, r4, #0
000f1656: 0422	movs	r2, #4
000f1658: fef7b0fa	bl	#0xefbbc
000f165c: 0228	cmp	r0, #2
000f165e: 84dd	ble	#0xf156a
000f1660: 0399	ldr	r1, [sp, #0xc]
000f1662: 079a	ldr	r2, [sp, #0x1c]
000f1664: 0b01	lsls	r3, r1, #4
000f1666: d318	adds	r3, r2, r3
000f1668: 6268	ldr	r2, [r4, #4]
000f166a: 1a60	str	r2, [r3]
000f166c: e268	ldr	r2, [r4, #0xc]
000f166e: 5a60	str	r2, [r3, #4]
000f1670: 0499	ldr	r1, [sp, #0x10]
000f1672: 2529	cmp	r1, #0x25
000f1674: 00d1	bne	#0xf1678
000f1676: 7ee0	b	#0xf1776
000f1678: 6269	ldr	r2, [r4, #0x14]
000f167a: 9a60	str	r2, [r3, #8]
000f167c: 0428	cmp	r0, #4
000f167e: 10d0	beq	#0xf16a2
000f1680: 0022	movs	r2, #0
000f1682: da60	str	r2, [r3, #0xc]
000f1684: c3e7	b	#0xf160e
000f1686: 0399	ldr	r1, [sp, #0xc]
000f1688: 4246	mov	r2, r8
000f168a: 506a	ldr	r0, [r2, #0x24]
000f168c: 0131	adds	r1, #1
000f168e: 9162	str	r1, [r2, #0x28]
000f1690: 029b	ldr	r3, [sp, #8]
000f1692: 1022	movs	r2, #0x10
000f1694: 341c	adds	r4, r6, #0
000f1696: 4e46	mov	r6, sb
000f1698: b946	mov	sb, r7
000f169a: 5f46	mov	r7, fp
000f169c: 43f790ee	blx	#0x353c0
000f16a0: 57e7	b	#0xf1552
000f16a2: 0499	ldr	r1, [sp, #0x10]
000f16a4: 2229	cmp	r1, #0x22
000f16a6: ebd1	bne	#0xf1680
000f16a8: e269	ldr	r2, [r4, #0x1c]
000f16aa: da60	str	r2, [r3, #0xc]
000f16ac: afe7	b	#0xf160e
000f16ae: 3828	cmp	r0, #0x38
000f16b0: 09d0	beq	#0xf16c6
000f16b2: 4b28	cmp	r0, #0x4b
000f16b4: 00d1	bne	#0xf16b8
000f16b6: 76e7	b	#0xf15a6
000f16b8: 351c	adds	r5, r6, #0
000f16ba: a027	movs	r7, #0xa0
000f16bc: 0be7	b	#0xf14d6
000f16be: 351c	adds	r5, r6, #0
000f16c0: 3e1c	adds	r6, r7, #0
000f16c2: 4746	mov	r7, r8
000f16c4: 83e7	b	#0xf15ce
000f16c6: 039b	ldr	r3, [sp, #0xc]
000f16c8: 5946	mov	r1, fp
000f16ca: 0133	adds	r3, #1
000f16cc: 0393	str	r3, [sp, #0xc]
000f16ce: 0b6a	ldr	r3, [r1, #0x20]
000f16d0: 039a	ldr	r2, [sp, #0xc]
000f16d2: 9a42	cmp	r2, r3
000f16d4: f0da	bge	#0xf16b8
000f16d6: cb69	ldr	r3, [r1, #0x1c]
000f16d8: 0222	movs	r2, #2
000f16da: 0321	movs	r1, #3
000f16dc: 0693	str	r3, [sp, #0x18]
000f16de: 201c	adds	r0, r4, #0
000f16e0: 2960	str	r1, [r5]
000f16e2: aa60	str	r2, [r5, #8]
000f16e4: 2a61	str	r2, [r5, #0x10]
000f16e6: aa61	str	r2, [r5, #0x18]
000f16e8: 2a62	str	r2, [r5, #0x20]
000f16ea: 291c	adds	r1, r5, #0
000f16ec: 0522	movs	r2, #5
000f16ee: fef765fa	bl	#0xefbbc
000f16f2: 0528	cmp	r0, #5
000f16f4: e0d1	bne	#0xf16b8
000f16f6: 0699	ldr	r1, [sp, #0x18]
000f16f8: 049a	ldr	r2, [sp, #0x10]
000f16fa: 8b18	adds	r3, r1, r2
000f16fc: 6a68	ldr	r2, [r5, #4]
000f16fe: 1a60	str	r2, [r3]
000f1700: e968	ldr	r1, [r5, #0xc]
000f1702: 5960	str	r1, [r3, #4]
000f1704: 6969	ldr	r1, [r5, #0x14]
000f1706: 9960	str	r1, [r3, #8]
000f1708: e869	ldr	r0, [r5, #0x1c]
000f170a: d860	str	r0, [r3, #0xc]
000f170c: 686a	ldr	r0, [r5, #0x24]
000f170e: 1861	str	r0, [r3, #0x10]
000f1710: 002a	cmp	r2, #0
000f1712: 35db	blt	#0xf1780
000f1714: 049a	ldr	r2, [sp, #0x10]
000f1716: 1432	adds	r2, #0x14
000f1718: 0492	str	r2, [sp, #0x10]
000f171a: 44e7	b	#0xf15a6
000f171c: ce74	strb	r6, [r1, #0x13]
000f171e: 0400	movs	r4, r0
000f1720: 2071	strb	r0, [r4, #4]
000f1722: 0400	movs	r4, r0
000f1724: 9071	strb	r0, [r2, #6]
000f1726: 0400	movs	r4, r0
000f1728: e7e0	b	#0xf18fa
000f172a: ffffb470	vshr.u64	d23, d20, #1
000f172e: 0400	movs	r4, r0
000f1730: 2268	ldr	r2, [r4]
000f1732: 6946	mov	r1, sp
000f1734: 9031	adds	r1, #0x90
000f1736: 0090	str	r0, [sp]
000f1738: 0191	str	r1, [sp, #4]
000f173a: 101c	adds	r0, r2, #0
000f173c: 1421	movs	r1, #0x14
000f173e: 0022	movs	r2, #0
000f1740: f7f7c2fd	bl	#0xe92c8
000f1744: 5a46	mov	r2, fp
000f1746: d061	str	r0, [r2, #0x1c]
000f1748: 249b	ldr	r3, [sp, #0x90]
000f174a: 002b	cmp	r3, #0
000f174c: 00d1	bne	#0xf1750
000f174e: 1fe7	b	#0xf1590
000f1750: 1f1c	adds	r7, r3, #0
000f1752: c0e6	b	#0xf14d6
000f1754: 2268	ldr	r2, [r4]
000f1756: 0599	ldr	r1, [sp, #0x14]
000f1758: 0090	str	r0, [sp]
000f175a: 101c	adds	r0, r2, #0
000f175c: 0191	str	r1, [sp, #4]
000f175e: 0022	movs	r2, #0
000f1760: 1021	movs	r1, #0x10
000f1762: f7f7b1fd	bl	#0xe92c8
000f1766: 4246	mov	r2, r8
000f1768: 5062	str	r0, [r2, #0x24]
000f176a: 239b	ldr	r3, [sp, #0x8c]
000f176c: 002b	cmp	r3, #0
000f176e: 00d1	bne	#0xf1772
000f1770: 40e7	b	#0xf15f4
000f1772: 1f1c	adds	r7, r3, #0
000f1774: afe6	b	#0xf14d6
000f1776: 0022	movs	r2, #0
000f1778: 9a60	str	r2, [r3, #8]
000f177a: 6269	ldr	r2, [r4, #0x14]
000f177c: da60	str	r2, [r3, #0xc]
000f177e: 46e7	b	#0xf160e
000f1780: 0029	cmp	r1, #0
000f1782: c7dd	ble	#0xf1714
000f1784: 4942	rsbs	r1, r1, #0
000f1786: 9960	str	r1, [r3, #8]
000f1788: c4e7	b	#0xf1714
