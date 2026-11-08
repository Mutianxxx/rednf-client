
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e8100 <.text>:
  4e8100: 55                           	push	ebp
  4e8101: 8b ec                        	mov	ebp, esp
  4e8103: 8b 45 08                     	mov	eax, dword ptr [ebp + 0x8]
  4e8106: 50                           	push	eax
  4e8107: e8 14 fe ff ff               	call	0x4e7f20
  4e810c: 85 c0                        	test	eax, eax
  4e810e: 74 06                        	je	0x4e8116 <.text+0x16>
  4e8110: 8b 00                        	mov	eax, dword ptr [eax]
  4e8112: 5d                           	pop	ebp
  4e8113: c2 04 00                     	ret	0x4
  4e8116: 33 c0                        	xor	eax, eax
  4e8118: 5d                           	pop	ebp
  4e8119: c2 04 00                     	ret	0x4
  4e811c: cc                           	int3
  4e811d: cc                           	int3
  4e811e: cc                           	int3
  4e811f: cc                           	int3
  4e8120: 55                           	push	ebp
  4e8121: 8b ec                        	mov	ebp, esp
  4e8123: 6a ff                        	push	-0x1
  4e8125: 68 9c 32 41 01               	push	0x141329c
  4e812a: 64 a1 00 00 00 00            	mov	eax, dword ptr fs:[0x0]
  4e8130: 50                           	push	eax
  4e8131: 53                           	push	ebx
  4e8132: 57                           	push	edi
  4e8133: a1 90 63 a4 01               	mov	eax, dword ptr [0x1a46390]
  4e8138: 33 c5                        	xor	eax, ebp
  4e813a: 50                           	push	eax
  4e813b: 8d 45 f4                     	lea	eax, [ebp - 0xc]
  4e813e: 64 a3 00 00 00 00            	mov	dword ptr fs:[0x0], eax
  4e8144: 8b f9                        	mov	edi, ecx
  4e8146: 83 7d 08 33                  	cmp	dword ptr [ebp + 0x8], 0x33
  4e814a: 0f 85 95 00 00 00            	jne	0x4e81e5 <.text+0xe5>
  4e8150: bb 01 00 00 00               	mov	ebx, 0x1
  4e8155: 84 1d 34 c7 a4 01            	test	byte ptr [0x1a4c734], bl
  4e815b: 75 2b                        	jne	0x4e8188 <.text+0x88>
  4e815d: 09 1d 34 c7 a4 01            	or	dword ptr [0x1a4c734], ebx
  4e8163: b9 e0 c4 a4 01               	mov	ecx, 0x1a4c4e0
  4e8168: c7 45 fc 00 00 00 00         	mov	dword ptr [ebp - 0x4], 0x0
  4e816f: e8 ac 8b 05 00               	call	0x540d20 <.text+0x58c20>
  4e8174: 68 20 4a 54 01               	push	0x1544a20
  4e8179: e8 8c f1 ee 00               	call	0x13d730a <.text+0xeef20a>
  4e817e: 83 c4 04                     	add	esp, 0x4
  4e8181: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  4e8188: b9 e0 c4 a4 01               	mov	ecx, 0x1a4c4e0
  4e818d: e8 5e 87 05 00               	call	0x5408f0 <.text+0x587f0>
  4e8192: 0f b6 c0                     	movzx	eax, al
  4e8195: 50                           	push	eax
  4e8196: 6a 19                        	push	0x19
  4e8198: 8b cf                        	mov	ecx, edi
  4e819a: e8 91 fe ff ff               	call	0x4e8030
  4e819f: 84 1d 34 c7 a4 01            	test	byte ptr [0x1a4c734], bl
  4e81a5: 75 27                        	jne	0x4e81ce <.text+0xce>
  4e81a7: 09 1d 34 c7 a4 01            	or	dword ptr [0x1a4c734], ebx
  4e81ad: b9 e0 c4 a4 01               	mov	ecx, 0x1a4c4e0
  4e81b2: 89 5d fc                     	mov	dword ptr [ebp - 0x4], ebx
  4e81b5: e8 66 8b 05 00               	call	0x540d20 <.text+0x58c20>
  4e81ba: 68 20 4a 54 01               	push	0x1544a20
  4e81bf: e8 46 f1 ee 00               	call	0x13d730a <.text+0xeef20a>
  4e81c4: 83 c4 04                     	add	esp, 0x4
  4e81c7: c7 45 fc ff ff ff ff         	mov	dword ptr [ebp - 0x4], 0xffffffff
  4e81ce: 6a 00                        	push	0x0
  4e81d0: b9 e0 c4 a4 01               	mov	ecx, 0x1a4c4e0
  4e81d5: e8 d6 87 05 00               	call	0x5409b0 <.text+0x588b0>
  4e81da: 6a 00                        	push	0x0
  4e81dc: 6a 19                        	push	0x19
  4e81de: 8b cf                        	mov	ecx, edi
  4e81e0: e8 4b fe ff ff               	call	0x4e8030
  4e81e5: 8b 4d f4                     	mov	ecx, dword ptr [ebp - 0xc]
  4e81e8: 64 89 0d 00 00 00 00         	mov	dword ptr fs:[0x0], ecx
  4e81ef: 59                           	pop	ecx
  4e81f0: 5f                           	pop	edi
  4e81f1: 5b                           	pop	ebx
  4e81f2: 8b e5                        	mov	esp, ebp
  4e81f4: 5d                           	pop	ebp
  4e81f5: c2 04 00                     	ret	0x4
  4e81f8: cc                           	int3
  4e81f9: cc                           	int3
  4e81fa: cc                           	int3
  4e81fb: cc                           	int3
  4e81fc: cc                           	int3
  4e81fd: cc                           	int3
  4e81fe: cc                           	int3
  4e81ff: cc                           	int3
