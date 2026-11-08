
<stdin>:	file format elf32-i386

Disassembly of section .text:

0111be40 <.text>:
 111be40: ec                           	in	al, dx
 111be41: 51                           	push	ecx
 111be42: 8b 4d e8                     	mov	ecx, dword ptr [ebp - 0x18]
 111be45: e8 16 74 55 ff               	call	0x673260
 111be4a: 6a 00                        	push	0x0
 111be4c: 6a 00                        	push	0x0
 111be4e: e8 47 ad 2b 00               	call	0x13d6b9a <.text+0x2bad5a>
 111be53: cc                           	int3
 111be54: cc                           	int3
 111be55: cc                           	int3
 111be56: cc                           	int3
 111be57: cc                           	int3
 111be58: cc                           	int3
 111be59: cc                           	int3
 111be5a: cc                           	int3
 111be5b: cc                           	int3
 111be5c: cc                           	int3
 111be5d: cc                           	int3
 111be5e: cc                           	int3
 111be5f: cc                           	int3
 111be60: 55                           	push	ebp
 111be61: 8b ec                        	mov	ebp, esp
 111be63: 83 ec 24                     	sub	esp, 0x24
 111be66: 56                           	push	esi
 111be67: 8b f1                        	mov	esi, ecx
 111be69: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111be6f: 85 c9                        	test	ecx, ecx
 111be71: 0f 84 cb 00 00 00            	je	0x111bf42 <.text+0x102>
 111be77: e8 34 6d f8 ff               	call	0x10a2bb0
 111be7c: 85 c0                        	test	eax, eax
 111be7e: 0f 84 be 00 00 00            	je	0x111bf42 <.text+0x102>
 111be84: 8b 8e b0 03 00 00            	mov	ecx, dword ptr [esi + 0x3b0]
 111be8a: 53                           	push	ebx
 111be8b: e8 20 6d f8 ff               	call	0x10a2bb0
 111be90: 8b c8                        	mov	ecx, eax
 111be92: e8 a9 b1 5d ff               	call	0x6f7040
 111be97: 8b d8                        	mov	ebx, eax
 111be99: 8d 45 f4                     	lea	eax, [ebp - 0xc]
 111be9c: 50                           	push	eax
 111be9d: 8b cb                        	mov	ecx, ebx
 111be9f: e8 6c 18 20 00               	call	0x131d710 <.text+0x2018d0>
 111bea4: 57                           	push	edi
 111bea5: 8d 4d e8                     	lea	ecx, [ebp - 0x18]
 111bea8: 51                           	push	ecx
 111bea9: 8b cb                        	mov	ecx, ebx
 111beab: e8 c0 a2 05 00               	call	0x1176170 <.text+0x5a330>
 111beb0: 8b 7d f4                     	mov	edi, dword ptr [ebp - 0xc]
 111beb3: 85 ff                        	test	edi, edi
 111beb5: 74 72                        	je	0x111bf29 <.text+0xe9>
 111beb7: 8b 17                        	mov	edx, dword ptr [edi]
 111beb9: 85 d2                        	test	edx, edx
 111bebb: 74 6c                        	je	0x111bf29 <.text+0xe9>
 111bebd: 8b 08                        	mov	ecx, dword ptr [eax]
 111bebf: 85                           	<unknown>
