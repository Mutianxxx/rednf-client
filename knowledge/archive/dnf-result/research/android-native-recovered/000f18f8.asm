000f18f8: f0b5	push	{r4, r5, r6, r7, lr}
000f18fa: 5f46	mov	r7, fp
000f18fc: 5646	mov	r6, sl
000f18fe: 4d46	mov	r5, sb
000f1900: 4446	mov	r4, r8
000f1902: f0b4	push	{r4, r5, r6, r7}
000f1904: 83b0	sub	sp, #0xc
000f1906: 9946	mov	sb, r3
000f1908: 0e9b	ldr	r3, [sp, #0x38]
000f190a: 071c	adds	r7, r0, #0
000f190c: 8c46	mov	ip, r1
000f190e: 9046	mov	r8, r2
000f1910: 0d9c	ldr	r4, [sp, #0x34]
000f1912: 002b	cmp	r3, #0
000f1914: 00d1	bne	#0xf1918
000f1916: 9ce0	b	#0xf1a52
000f1918: 504a	ldr	r2, [pc, #0x140]
000f191a: 8121	movs	r1, #0x81
000f191c: c900	lsls	r1, r1, #3
000f191e: 4618	adds	r6, r0, r1
000f1920: 8518	adds	r5, r0, r2
000f1922: 0023	movs	r3, #0
000f1924: 3360	str	r3, [r6]
000f1926: 6246	mov	r2, ip
000f1928: 2b60	str	r3, [r5]
000f192a: 381c	adds	r0, r7, #0
000f192c: 0021	movs	r1, #0
000f192e: 4346	mov	r3, r8
000f1930: 0096	str	r6, [sp]
000f1932: 0195	str	r5, [sp, #4]
000f1934: fff748ff	bl	#0xf17c8
000f1938: 381c	adds	r0, r7, #0
000f193a: 371c	adds	r7, r6, #0
000f193c: 0121	movs	r1, #1
000f193e: 0437	adds	r7, #4
000f1940: 4a46	mov	r2, sb
000f1942: 0c9b	ldr	r3, [sp, #0x30]
000f1944: 0096	str	r6, [sp]
000f1946: 0195	str	r5, [sp, #4]
000f1948: fff73eff	bl	#0xf17c8
000f194c: bc46	mov	ip, r7
000f194e: 043f	subs	r7, #4
000f1950: 2968	ldr	r1, [r5]
000f1952: 01cf	ldm	r7!, {r0}
000f1954: 8b46	mov	fp, r1
000f1956: 0028	cmp	r0, #0
000f1958: 1cdd	ble	#0xf1994
000f195a: 2436	adds	r6, #0x24
000f195c: b046	mov	r8, r6
000f195e: 6346	mov	r3, ip
000f1960: 021c	adds	r2, r0, #0
000f1962: 12e0	b	#0xf198a
000f1964: 4746	mov	r7, r8
000f1966: 1968	ldr	r1, [r3]
000f1968: 3e68	ldr	r6, [r7]
000f196a: 761a	subs	r6, r6, r1
000f196c: b146	mov	sb, r6
000f196e: 5e68	ldr	r6, [r3, #4]
000f1970: b145	cmp	sb, r6
000f1972: 01da	bge	#0xf1978
000f1974: 4e46	mov	r6, sb
000f1976: 5e60	str	r6, [r3, #4]
000f1978: d960	str	r1, [r3, #0xc]
000f197a: 2027	movs	r7, #0x20
000f197c: 8919	adds	r1, r1, r6
000f197e: 013a	subs	r2, #1
000f1980: 9960	str	r1, [r3, #8]
000f1982: b844	add	r8, r7
000f1984: 2033	adds	r3, #0x20
000f1986: 002a	cmp	r2, #0
000f1988: 04d0	beq	#0xf1994
000f198a: 012a	cmp	r2, #1
000f198c: ead8	bhi	#0xf1964
000f198e: 1968	ldr	r1, [r3]
000f1990: 5e68	ldr	r6, [r3, #4]
000f1992: f1e7	b	#0xf1978
000f1994: 5946	mov	r1, fp
000f1996: 2e1d	adds	r6, r5, #4
000f1998: 0029	cmp	r1, #0
000f199a: 1cdd	ble	#0xf19d6
000f199c: 2435	adds	r5, #0x24
000f199e: a846	mov	r8, r5
000f19a0: 331c	adds	r3, r6, #0
000f19a2: 5a46	mov	r2, fp
000f19a4: 12e0	b	#0xf19cc
000f19a6: 4746	mov	r7, r8
000f19a8: 1968	ldr	r1, [r3]
000f19aa: 3d68	ldr	r5, [r7]
000f19ac: 4d1b	subs	r5, r1, r5
000f19ae: a946	mov	sb, r5
000f19b0: 5d68	ldr	r5, [r3, #4]
000f19b2: a945	cmp	sb, r5
000f19b4: 01dd	ble	#0xf19ba
000f19b6: 4d46	mov	r5, sb
000f19b8: 5d60	str	r5, [r3, #4]
000f19ba: 9960	str	r1, [r3, #8]
000f19bc: 2027	movs	r7, #0x20
000f19be: 4919	adds	r1, r1, r5
000f19c0: 013a	subs	r2, #1
000f19c2: d960	str	r1, [r3, #0xc]
000f19c4: b844	add	r8, r7
000f19c6: 2033	adds	r3, #0x20
000f19c8: 002a	cmp	r2, #0
000f19ca: 04d0	beq	#0xf19d6
000f19cc: 012a	cmp	r2, #1
000f19ce: ead8	bhi	#0xf19a6
000f19d0: 1968	ldr	r1, [r3]
000f19d2: 5d68	ldr	r5, [r3, #4]
000f19d4: f1e7	b	#0xf19ba
000f19d6: 6100	lsls	r1, r4, #1
000f19d8: 0122	movs	r2, #1
000f19da: 8846	mov	r8, r1
000f19dc: 9146	mov	sb, r2
000f19de: 0028	cmp	r0, #0
000f19e0: 29d0	beq	#0xf1a36
000f19e2: 6546	mov	r5, ip
000f19e4: eb68	ldr	r3, [r5, #0xc]
000f19e6: 0138	subs	r0, #1
000f19e8: aa68	ldr	r2, [r5, #8]
000f19ea: 1b1b	subs	r3, r3, r4
000f19ec: eb60	str	r3, [r5, #0xc]
000f19ee: 8246	mov	sl, r0
000f19f0: 011c	adds	r1, r0, #0
000f19f2: 0028	cmp	r0, #0
000f19f4: 1cd0	beq	#0xf1a30
000f19f6: 6346	mov	r3, ip
000f19f8: 0ae0	b	#0xf1a10
000f19fa: c50f	lsrs	r5, r0, #0x1f
000f19fc: 2818	adds	r0, r5, r0
000f19fe: 4010	asrs	r0, r0, #1
000f1a00: 8218	adds	r2, r0, r2
000f1a02: 0139	subs	r1, #1
000f1a04: da62	str	r2, [r3, #0x2c]
000f1a06: 9a60	str	r2, [r3, #8]
000f1a08: 9a6a	ldr	r2, [r3, #0x28]
000f1a0a: 2033	adds	r3, #0x20
000f1a0c: 0029	cmp	r1, #0
000f1a0e: 0cd0	beq	#0xf1a2a
000f1a10: dd6a	ldr	r5, [r3, #0x2c]
000f1a12: a81a	subs	r0, r5, r2
000f1a14: 8045	cmp	r8, r0
000f1a16: f0dc	bgt	#0xf19fa
000f1a18: 1219	adds	r2, r2, r4
000f1a1a: 2d1b	subs	r5, r5, r4
000f1a1c: 0139	subs	r1, #1
000f1a1e: 9a60	str	r2, [r3, #8]
000f1a20: dd62	str	r5, [r3, #0x2c]
000f1a22: 9a6a	ldr	r2, [r3, #0x28]
000f1a24: 2033	adds	r3, #0x20
000f1a26: 0029	cmp	r1, #0
000f1a28: f2d1	bne	#0xf1a10
000f1a2a: 5746	mov	r7, sl
000f1a2c: 7801	lsls	r0, r7, #5
000f1a2e: 8444	add	ip, r0
000f1a30: 1219	adds	r2, r2, r4
000f1a32: 6146	mov	r1, ip
000f1a34: 8a60	str	r2, [r1, #8]
000f1a36: 4a46	mov	r2, sb
000f1a38: 013a	subs	r2, #1
000f1a3a: 9146	mov	sb, r2
000f1a3c: 02d3	blo	#0xf1a44
000f1a3e: b446	mov	ip, r6
000f1a40: 5846	mov	r0, fp
000f1a42: cce7	b	#0xf19de
000f1a44: 03b0	add	sp, #0xc
000f1a46: 3cbc	pop	{r2, r3, r4, r5}
000f1a48: 9046	mov	r8, r2
000f1a4a: 9946	mov	sb, r3
000f1a4c: a246	mov	sl, r4
000f1a4e: ab46	mov	fp, r5
000f1a50: f0bd	pop	{r4, r5, r6, r7, pc}
000f1a52: 8123	movs	r3, #0x81
000f1a54: 9b00	lsls	r3, r3, #2
000f1a56: 061c	adds	r6, r0, #0
000f1a58: c518	adds	r5, r0, r3
000f1a5a: 62e7	b	#0xf1922
000f1a5c: 0c06	lsls	r4, r1, #0x18
000f1a5e: 0000	movs	r0, r0
