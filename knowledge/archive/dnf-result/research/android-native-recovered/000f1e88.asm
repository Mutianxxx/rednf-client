000f1e88: 10b5	push	{r4, lr}
000f1e8a: 011e	subs	r1, r0, #0
000f1e8c: 11d0	beq	#0xf1eb2
000f1e8e: 0023	movs	r3, #0
000f1e90: d022	movs	r2, #0xd0
000f1e92: 0868	ldr	r0, [r1]
000f1e94: 4b60	str	r3, [r1, #4]
000f1e96: 8b50	str	r3, [r1, r2]
000f1e98: ce22	movs	r2, #0xce
000f1e9a: 5200	lsls	r2, r2, #1
000f1e9c: 8b50	str	r3, [r1, r2]
000f1e9e: e822	movs	r2, #0xe8
000f1ea0: 9200	lsls	r2, r2, #2
000f1ea2: 8b50	str	r3, [r1, r2]
000f1ea4: 034a	ldr	r2, [pc, #0xc]
000f1ea6: 8b50	str	r3, [r1, r2]
000f1ea8: f522	movs	r2, #0xf5
000f1eaa: d200	lsls	r2, r2, #3
000f1eac: 8b50	str	r3, [r1, r2]
000f1eae: f6f7fbf8	bl	#0xe80a8
000f1eb2: 10bd	pop	{r4, pc}
000f1eb4: a405	lsls	r4, r4, #0x16
000f1eb6: 0000	movs	r0, r0
