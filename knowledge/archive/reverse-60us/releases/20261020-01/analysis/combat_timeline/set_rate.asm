00a29c70 55                       push       ebp
00a29c71 8bec                     mov        ebp, esp
00a29c73 83ec0c                   sub        esp, 0xc
00a29c76 d94508                   fld        dword ptr [ebp + 8]
00a29c79 57                       push       edi
00a29c7a d9e1                     fabs       
00a29c7c 8bf9                     mov        edi, ecx
00a29c7e d94508                   fld        dword ptr [ebp + 8]
00a29c81 d9e1                     fabs       
00a29c83 dc0de8b8ca00             fmul       qword ptr [0xcab8e8]
00a29c89 ded9                     fcompp     
00a29c8b dfe0                     fnstsw     ax
00a29c8d f6c401                   test       ah, 1
