
<stdin>:	file format elf32-i386

Disassembly of section .text:

10005a8e <.text>:
10005a8e: 8b ff                        	mov	edi, edi
10005a90: 55                           	push	ebp
10005a91: 8b ec                        	mov	ebp, esp
10005a93: 83 7d 0c 01                  	cmp	dword ptr [ebp + 0xc], 0x1
10005a97: 75 05                        	jne	0x10005a9e <.text+0x10>
10005a99: e8 9b 46 00 00               	call	0x1000a139 <.text+0x46ab>
10005a9e: ff 75 08                     	push	dword ptr [ebp + 0x8]
10005aa1: 8b 4d 10                     	mov	ecx, dword ptr [ebp + 0x10]
10005aa4: 8b 55 0c                     	mov	edx, dword ptr [ebp + 0xc]
10005aa7: e8 ec fe ff ff               	call	0x10005998
10005aac: 59                           	pop	ecx
10005aad: 5d                           	pop	ebp
10005aae: c2                           	<unknown>
