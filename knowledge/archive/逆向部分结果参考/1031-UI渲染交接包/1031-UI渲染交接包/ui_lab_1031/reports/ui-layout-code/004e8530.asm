
<stdin>:	file format elf32-i386

Disassembly of section .text:

004e8530 <.text>:
  4e8530: 56                           	push	esi
  4e8531: 57                           	push	edi
  4e8532: 8b f9                        	mov	edi, ecx
  4e8534: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e8537: 8b 30                        	mov	esi, dword ptr [eax]
  4e8539: 89 00                        	mov	dword ptr [eax], eax
  4e853b: 8b 47 04                     	mov	eax, dword ptr [edi + 0x4]
  4e853e: 89 40 04                     	mov	dword ptr [eax + 0x4], eax
  4e8541: c7 47 08 00 00 00 00         	mov	dword ptr [edi + 0x8], 0x0
  4e8548: 3b 77 04                     	cmp	esi, dword ptr [edi + 0x4]
  4e854b: 74 4c                        	je	0x4e8599 <.text+0x69>
  4e854d: 53                           	push	ebx
  4e854e: 8b ff                        	mov	edi, edi
  4e8550: 83 7e 24 08                  	cmp	dword ptr [esi + 0x24], 0x8
  4e8554: 8b 1e                        	mov	ebx, dword ptr [esi]
  4e8556: 72 0c                        	jb	0x4e8564 <.text+0x34>
  4e8558: 8b 46 10                     	mov	eax, dword ptr [esi + 0x10]
  4e855b: 50                           	push	eax
  4e855c: e8 c6 d5 ee 00               	call	0x13d5b27 <.text+0xeed5f7>
  4e8561: 83 c4 04                     	add	esp, 0x4
  4e8564: 33 c9                        	xor	ecx, ecx
  4e8566: c7 46 24 07 00 00 00         	mov	dword ptr [esi + 0x24], 0x7
  4e856d: c7 46 20 00 00 00 00         	mov	dword ptr [esi + 0x20], 0x0
  4e8574: 66 89 4e 10                  	mov	word ptr [esi + 0x10], cx
  4e8578: 8b 56 0c                     	mov	edx, dword ptr [esi + 0xc]
  4e857b: 52                           	push	edx
  4e857c: e8 a6 d5 ee 00               	call	0x13d5b27 <.text+0xeed5f7>
  4e8581: 56                           	push	esi
  4e8582: c7 46 0c 00 00 00 00         	mov	dword ptr [esi + 0xc], 0x0
  4e8589: e8 99 d5 ee 00               	call	0x13d5b27 <.text+0xeed5f7>
  4e858e: 83 c4 08                     	add	esp, 0x8
  4e8591: 8b f3                        	mov	esi, ebx
  4e8593: 3b 5f 04                     	cmp	ebx, dword ptr [edi + 0x4]
  4e8596: 75 b8                        	jne	0x4e8550 <.text+0x20>
  4e8598: 5b                           	pop	ebx
  4e8599: 5f                           	pop	edi
  4e859a: 5e                           	pop	esi
  4e859b: c3                           	ret
  4e859c: cc                           	int3
  4e859d: cc                           	int3
  4e859e: cc                           	int3
  4e859f: cc                           	int3
  4e85a0: 56                           	push	esi
  4e85a1: 8b f1                        	mov	esi, ecx
  4e85a3: e8 88 ff ff ff               	call	0x4e8530 <.text>
  4e85a8: 8b 46 04                     	mov	eax, dword ptr [esi + 0x4]
  4e85ab: 50                           	push	eax
  4e85ac: e8                           	<unknown>
  4e85ad: 76 d5                        	jbe	0x4e8584 <.text+0x54>
  4e85af: ee                           	out	dx, al
