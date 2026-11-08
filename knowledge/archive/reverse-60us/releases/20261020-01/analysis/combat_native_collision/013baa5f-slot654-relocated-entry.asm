013baa5f 687e0e1008               push      0x8100e7e
013baa64 e9603df3ff               jmp       0x12ee7c9
013baa69 084201                   or        byte ptr [edx + 1], al
013baa6c 6453                     push      ebx
013baa6e ae                       scasb     al, byte ptr es:[edi]
013baa6f 68b84b4a10               push      0x104a4bb8
013baa74 0803                     or        byte ptr [ebx], al
013baa76 c5                       .byte     0xc5
013baa77 e98b410000               jmp       0x13bec07
013baa7c 6867871008               push      0x8108767
013baa81 e9433df3ff               jmp       0x12ee7c9
013baa86 68fd871008               push      0x81087fd
013baa8b e9393df3ff               jmp       0x12ee7c9
013baa90 99                       cdq       
013baa91 6837881008               push      0x8108837
013baa96 e92e3df3ff               jmp       0x12ee7c9
013baa9b 21919b6a5b20             and       dword ptr [ecx + 0x205b6a9b], edx
013baaa1 0ad9                     or        bl, cl
013baaa3 caaebc                   retf      0xbcae
013baaa6 47                       inc       edi
013baaa7 44                       inc       esp
013baaa8 3a34cf                   cmp       dh, byte ptr [edi + ecx*8]
013baaab cc                       int3      
013baaac e5d9                     in        eax, 0xd9
013baaae 9d                       popfd     
013baaaf 97                       xchg      edi, eax
013baab0 6e                       outsb     dx, byte ptr [esi]
013baab1 5f                       pop       edi
013baab2 1e                       push      ds
013baab3 08db                     or        bl, bl
013baab5 c8adb944                 enter     -0x4653, 0x44
013baab9 793a                     jns       0x13baaf5
013baabb 30b3f0c8a221             xor       byte ptr [ebx + 0x21a2c8f0], dh
013baac1 06                       push      es
013baac2 3e61                     popal     
013baac4 e6df                     out       0xdf, al
013baac6 9f                       lahf      
013baac7 5a                       pop       edx
013baac8 b3b0                     mov       bl, 0xb0
013baaca d7                       xlatb     
013baacb a6                       cmpsb     byte ptr [esi], byte ptr es:[edi]
013baacc 1b1a                     sbb       ebx, dword ptr [edx]
013baace 45                       inc       ebp
013baacf c229b0                   ret       0xb029
013baad2 6297402d763e             bound     edx, qword ptr [edi + 0x3e762d40]
013baad8 e42f                     in        al, 0x2f
013baada 2c29                     sub       al, 0x29
013baadc b062                     mov       al, 0x62
013baade 0922                     or        dword ptr [edx], esp
013baae0 4a                       dec       edx
013baae1 b9fc498adc               mov       ecx, 0xdc8a49fc
013baae6 02f5                     add       dh, ch
013baae8 bb9643c44c               mov       ebx, 0x4cc44396
013baaed bbfa6c3172               mov       ebx, 0x72316cfa
013baaf2 1a8ba5453a30             sbb       cl, byte ptr [ebx + 0x303a45a5]
013baaf8 75b2                     jne       0x13baaac
013baafa 0466                     add       al, 0x66
013baafc 3b87976a3914             cmp       eax, dword ptr [edi + 0x14396a97]
013bab02 004f2e                   add       byte ptr [edi + 0x2e], cl
013bab05 380d3e2e3e13             cmp       byte ptr [0x133e2e3e], cl
013bab0b 6257de                   bound     edx, qword ptr [edi - 0x22]
013bab0e 01                       .byte     0x01
