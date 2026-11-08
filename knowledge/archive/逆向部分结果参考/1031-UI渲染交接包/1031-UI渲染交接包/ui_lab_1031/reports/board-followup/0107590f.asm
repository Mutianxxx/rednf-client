
<stdin>:	file format elf32-i386

Disassembly of section .text:

0107590f <.text>:
 107590f: 05 3e fe ff ff               	add	eax, 0xfffffe3e
 1075914: 3d 91 00 00 00               	cmp	eax, 0x91
 1075919: 0f 87 ad 08 00 00            	ja	0x10761cc <.text+0x8bd>
 107591f: 0f b6 90 1c 63 07 01         	movzx	edx, byte ptr [eax + 0x107631c]
 1075926: ff 24 95 60 62 07 01         	jmp	dword ptr [4*edx + 0x1076260]
