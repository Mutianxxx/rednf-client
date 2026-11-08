
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e9770 <.text>:
  4e9770: 55                           	push	ebp
  4e9771: 8b ec                        	mov	ebp, esp
  4e9773: 56                           	push	esi
  4e9774: 57                           	push	edi
  4e9775: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
  4e9778: 57                           	push	edi
  4e9779: 8b f1                        	mov	esi, ecx
  4e977b: e8 a0 e7 ff ff               	call	0x4e7f20
  4e9780: 85 c0                        	test	eax, eax
  4e9782: 74 06                        	je	0x4e978a <.text+0x1a>
  4e9784: 80 78 08 00                  	cmp	byte ptr [eax + 0x8], 0x0
  4e9788: 75 48                        	jne	0x4e97d2 <.text+0x62>
  4e978a: 66 83 ff 18                  	cmp	di, 0x18
  4e978e: 74 42                        	je	0x4e97d2 <.text+0x62>
  4e9790: 57                           	push	edi
  4e9791: 8b ce                        	mov	ecx, esi
  4e9793: e8 88 fd ff ff               	call	0x4e9520
  4e9798: 8b f8                        	mov	edi, eax
  4e979a: 85 ff                        	test	edi, edi
  4e979c: 74 34                        	je	0x4e97d2 <.text+0x62>
  4e979e: 8b 8e b4 00 00 00            	mov	ecx, dword ptr [esi + 0xb4]
  4e97a4: 53                           	push	ebx
  4e97a5: 8b 9e b8 00 00 00            	mov	ebx, dword ptr [esi + 0xb8]
  4e97ab: c6 47 08 01                  	mov	byte ptr [edi + 0x8], 0x1
  4e97af: 85 c9                        	test	ecx, ecx
  4e97b1: 74 08                        	je	0x4e97bb <.text+0x4b>
  4e97b3: 8b 07                        	mov	eax, dword ptr [edi]
  4e97b5: 50                           	push	eax
  4e97b6: e8 75 5b cd 00               	call	0x11bf330 <.text+0xcd5bc0>
  4e97bb: 85 db                        	test	ebx, ebx
  4e97bd: 74 0b                        	je	0x4e97ca <.text+0x5a>
  4e97bf: 8b 4f 04                     	mov	ecx, dword ptr [edi + 0x4]
  4e97c2: 51                           	push	ecx
  4e97c3: 8b cb                        	mov	ecx, ebx
  4e97c5: e8 66 5b cd 00               	call	0x11bf330 <.text+0xcd5bc0>
  4e97ca: 8b ce                        	mov	ecx, esi
  4e97cc: e8 bf df ff ff               	call	0x4e7790
  4e97d1: 5b                           	pop	ebx
  4e97d2: 5f                           	pop	edi
  4e97d3: 5e                           	pop	esi
  4e97d4: 5d                           	pop	ebp
  4e97d5: c2 04 00                     	ret	0x4
  4e97d8: cc                           	int3
  4e97d9: cc                           	int3
  4e97da: cc                           	int3
  4e97db: cc                           	int3
  4e97dc: cc                           	int3
  4e97dd: cc                           	int3
  4e97de: cc                           	int3
  4e97df: cc                           	int3
  4e97e0: 55                           	push	ebp
  4e97e1: 8b ec                        	mov	ebp, esp
  4e97e3: 6a ff                        	push	-0x1
  4e97e5: 68 28 34 41 01               	push	0x1413428
  4e97ea: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4e97f0: 50                           	push	eax
  4e97f1: 83 ec 34                     	sub	esp, 0x34
  4e97f4: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4e97f9: 33 c5                        	xor	eax, ebp
  4e97fb: 89 45 f0                     	mov	dword ptr [ebp - 0x10], eax
  4e97fe: 53                           	push	ebx
  4e97ff: 56                           	push	esi
  4e9800: 57                           	push	edi
  4e9801: 50                           	push	eax
  4e9802: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4e9805: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4e980b: 0f b7 7d 08                  	movzx	edi, word ptr [ebp + 0x8]
  4e980f: 8b 45 0c                     	mov	eax, dword ptr [ebp + 0xc]
  4e9812: 57                           	push	edi
  4e9813: 8b f1                        	mov	esi, ecx
  4e9815: 89 45 c4                     	mov	dword ptr [ebp - 0x3c], eax
  4e9818: e8 03 e7 ff ff               	call	0x4e7f20
  4e981d: 8b d8                        	mov	ebx, eax
  4e981f: 85 db                        	test	ebx, ebx
  4e9821: 75 25                        	jne	0x4e9848 <.text+0xd8>
  4e9823: 83 7d 10 02                  	cmp	dword ptr [ebp + 0x10], 0x2
  4e9827: 0f 85 10 01 00 00            	jne	0x4e993d <.text+0x1cd>
  4e982d: 57                           	push	edi
  4e982e: 8b ce                        	mov	ecx, esi
  4e9830: e8 3b ff ff ff               	call	0x4e9770 <.text>
  4e9835: 8b 4d c4                     	mov	ecx, dword ptr [ebp - 0x3c]
  4e9838: 6a 02                        	push	0x2
  4e983a: 51                           	push	ecx
  4e983b: 57                           	push	edi
  4e983c: 8b ce                        	mov	ecx, esi
  4e983e: e8 9d ff ff ff               	call	0x4e97e0 <.text+0x70>
  4e9843: e9 f5 00 00 00               	jmp	0x4e993d <.text+0x1cd>
  4e9848: 83 3b 00                     	cmp	dword ptr [ebx], 0x0
  4e984b: 0f 84 ec 00 00 00            	je	0x4e993d <.text+0x1cd>
  4e9851: 83 7d 10 02                  	cmp	dword ptr [ebp + 0x10], 0x2
  4e9855: 0f 85 8c 00 00 00            	jne	0x4e98e7 <.text+0x177>
  4e985b: 8d 4d c8                     	lea	ecx, [ebp - 0x38]
  4e985e: e8 5d dc ff ff               	call	0x4e74c0
  4e9863: 8b 45 c4                     	mov	eax, dword ptr [ebp - 0x3c]
  4e9866: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  4e986d: 85 c0                        	test	eax, eax
  4e986f: 75 0d                        	jne	0x4e987e <.text+0x10e>
  4e9871: 68 78 21 56 01               	push	0x1562178
  4e9876: e8 75 66 cb 00               	call	0x119fef0 <.text+0xcb6780>
  4e987b: 83 c4 04                     	add	esp, 0x4
  4e987e: 8b c8                        	mov	ecx, eax
  4e9880: 8d 51 02                     	lea	edx, [ecx + 0x2]
  4e9883: 89 55 c0                     	mov	dword ptr [ebp - 0x40], edx
  4e9886: 66 8b 11                     	mov	dx, word ptr [ecx]
  4e9889: 83 c1 02                     	add	ecx, 0x2
  4e988c: 66 85 d2                     	test	dx, dx
  4e988f: 75 f5                        	jne	0x4e9886 <.text+0x116>
  4e9891: 2b 4d c0                     	sub	ecx, dword ptr [ebp - 0x40]
  4e9894: d1 f9                        	sar	ecx
  4e9896: 51                           	push	ecx
  4e9897: 50                           	push	eax
  4e9898: 8d 4d c8                     	lea	ecx, [ebp - 0x38]
  4e989b: e8 90 67 f2 ff               	call	0x410030
  4e98a0: 8b 03                        	mov	eax, dword ptr [ebx]
  4e98a2: 8b 4e 74                     	mov	ecx, dword ptr [esi + 0x74]
  4e98a5: 57                           	push	edi
  4e98a6: 89 45 ec                     	mov	dword ptr [ebp - 0x14], eax
  4e98a9: c7 45 e8 98 3a 00 00         	mov	dword ptr [ebp - 0x18], 0x3a98
  4e98b0: e8 eb 5f 02 00               	call	0x50f8a0 <.text+0x26130>
  4e98b5: 8d 4d c8                     	lea	ecx, [ebp - 0x38]
  4e98b8: 51                           	push	ecx
  4e98b9: 8b 4e 74                     	mov	ecx, dword ptr [esi + 0x74]
  4e98bc: 57                           	push	edi
  4e98bd: e8 2e 68 02 00               	call	0x5100f0 <.text+0x26980>
  4e98c2: 8b 0b                        	mov	ecx, dword ptr [ebx]
  4e98c4: e8 f7 4d 98 00               	call	0xe6e6c0 <.text+0x984f50>
  4e98c9: 33 d2                        	xor	edx, edx
  4e98cb: 84 c0                        	test	al, al
  4e98cd: 8b 45 c4                     	mov	eax, dword ptr [ebp - 0x3c]
  4e98d0: 0f 95 c2                     	setne	dl
  4e98d3: 8b ce                        	mov	ecx, esi
  4e98d5: 52                           	push	edx
  4e98d6: 50                           	push	eax
  4e98d7: 57                           	push	edi
  4e98d8: e8 03 ff ff ff               	call	0x4e97e0 <.text+0x70>
  4e98dd: 8d 4d c8                     	lea	ecx, [ebp - 0x38]
  4e98e0: e8 0b ed f6 ff               	call	0x4585f0
  4e98e5: eb 56                        	jmp	0x4e993d <.text+0x1cd>
  4e98e7: 8b 4b 04                     	mov	ecx, dword ptr [ebx + 0x4]
  4e98ea: 85 c9                        	test	ecx, ecx
  4e98ec: 74 4f                        	je	0x4e993d <.text+0x1cd>
  4e98ee: 8b 75 c4                     	mov	esi, dword ptr [ebp - 0x3c]
  4e98f1: 85 f6                        	test	esi, esi
  4e98f3: 74 22                        	je	0x4e9917 <.text+0x1a7>
  4e98f5: 8b c6                        	mov	eax, esi
  4e98f7: 8d 78 02                     	lea	edi, [eax + 0x2]
  4e98fa: 8d 9b 00 00 00 00            	lea	ebx, [ebx]
  4e9900: 66 8b 10                     	mov	dx, word ptr [eax]
  4e9903: 83 c0 02                     	add	eax, 0x2
  4e9906: 66 85 d2                     	test	dx, dx
  4e9909: 75 f5                        	jne	0x4e9900 <.text+0x190>
  4e990b: 2b c7                        	sub	eax, edi
  4e990d: d1 f8                        	sar	eax
  4e990f: 74 06                        	je	0x4e9917 <.text+0x1a7>
  4e9911: 56                           	push	esi
  4e9912: e8 b9 77 ce 00               	call	0x11d10d0 <.text+0xce7960>
  4e9917: 8b 0b                        	mov	ecx, dword ptr [ebx]
  4e9919: 6a 01                        	push	0x1
  4e991b: e8 e0 49 cd 00               	call	0x11be300 <.text+0xcd4b90>
  4e9920: 8b 0b                        	mov	ecx, dword ptr [ebx]
  4e9922: 50                           	push	eax
  4e9923: e8 38 66 f4 ff               	call	0x42ff60
  4e9928: 8b 4b 04                     	mov	ecx, dword ptr [ebx + 0x4]
  4e992b: 50                           	push	eax
  4e992c: e8 9f 51 cd 00               	call	0x11bead0 <.text+0xcd5360>
  4e9931: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
  4e9934: 51                           	push	ecx
  4e9935: 8b 4b 04                     	mov	ecx, dword ptr [ebx + 0x4]
  4e9938: e8 63 74 ce 00               	call	0x11d0da0 <.text+0xce7630>
  4e993d: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4e9940: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4e9947: 59                           	pop	ecx
  4e9948: 5f                           	pop	edi
  4e9949: 5e                           	pop	esi
  4e994a: 5b                           	pop	ebx
  4e994b: 8b 4d f0                     	mov	ecx, dword ptr [ebp - 0x10]
  4e994e: 33 cd                        	xor	ecx, ebp
  4e9950: e8 83 d8 ee 00               	call	0x13d71d8 <.text+0xeeda68>
  4e9955: 8b e5                        	mov	esp, ebp
  4e9957: 5d                           	pop	ebp
  4e9958: c2 0c 00                     	ret	0xc
  4e995b: cc                           	int3
  4e995c: cc                           	int3
  4e995d: cc                           	int3
  4e995e: cc                           	int3
  4e995f: cc                           	int3
  4e9960: 55                           	push	ebp
  4e9961: 8b ec                        	mov	ebp, esp
  4e9963: 53                           	push	ebx
  4e9964: 8b 5d 0c                     	mov	ebx, dword ptr [ebp + 0xc]
  4e9967: 56                           	push	esi
  4e9968: 57                           	push	edi
  4e9969: 8b 7d 08                     	mov	edi, dword ptr [ebp + 0x8]
  4e996c: 8b f1                        	mov	esi, ecx
  4e996e: 85 db                        	test	ebx, ebx
  4e9970: 74 0c                        	je	0x4e997e <.text+0x20e>
  4e9972: 8b 45 14                     	mov	eax, dword ptr [ebp + 0x14]
  4e9975: 50                           	push	eax
  4e9976: 6a 00                        	push	0x0
  4e9978: 57                           	push	edi
  4e9979: e8 62 fe ff ff               	call	0x4e97e0 <.text+0x70>
  4e997e: 83 7d 14 02                  	cmp	dword ptr [ebp + 0x14], 0x2
  4e9982: 75 15                        	jne	0x4e9999 <.text+0x229>
  4e9984: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
  4e9987: 51                           	push	ecx
  4e9988: 8b 4e 74                     	mov	ecx, dword ptr [esi + 0x74]
  4e998b: 53                           	push	ebx
  4e998c: 57                           	push	edi
  4e998d: e8                           	<unknown>
  4e998e: 4e                           	dec	esi
  4e998f: 60                           	pushal
