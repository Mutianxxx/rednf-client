
undefined4 FUN_00b08200(void)

{
  int *piVar1;
  int *piVar2;
  short sVar3;
  int iVar4;
  int in_ECX;
  short sVar5;
  int local_8;
  
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0x5c))
            (*(int **)(in_ECX + 0x1c),0xdac00,0x200,0x144,0,in_ECX + 0x10);
  piVar1 = (int *)(in_ECX + 0x14);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0x60))
            (*(int **)(in_ECX + 0x1c),96000,0x200,0x65,0,piVar1);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0x60))
            (*(int **)(in_ECX + 0x1c),0xc4e0,0x200,0x65,0,in_ECX + 0x18);
  piVar2 = (int *)*piVar1;
  if (piVar2 != (int *)0x0) {
    iVar4 = (**(code **)(*piVar2 + 0x2c))(piVar2,0,0,&local_8,0x10);
    if (iVar4 != 0) {
      return 0;
    }
    sVar5 = 0;
    iVar4 = 0;
    do {
      sVar3 = sVar5 * 4;
      *(short *)(iVar4 + local_8) = sVar3 + 2;
      *(short *)(iVar4 + 2 + local_8) = sVar3;
      *(short *)(iVar4 + 4 + local_8) = sVar3 + 1;
      *(short *)(iVar4 + 6 + local_8) = sVar3 + 3;
      *(short *)(iVar4 + 8 + local_8) = sVar3 + 2;
      *(short *)(iVar4 + 10 + local_8) = sVar3 + 1;
      sVar5 = sVar5 + 1;
      iVar4 = iVar4 + 0xc;
    } while (iVar4 < 96000);
    (**(code **)(*(int *)*piVar1 + 0x30))((int *)*piVar1);
  }
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x1b,1);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x19,5);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x18,3);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0xf,1);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x16,1);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x14,6);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x89,0);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x13,5);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x34,0);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x97,0);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,5,2);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,6,0);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,4,4);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,1,4);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,3,0);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,0xd,3);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,0xe,3);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,0x10,3);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,0x11,2);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),7,0);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0xe,0);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x17,4);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0x130))(*(int **)(in_ECX + 0x1c),0x144);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0x154))(*(int **)(in_ECX + 0x1c),*piVar1,0);
  (**(code **)(**(int **)(in_ECX + 0x1c) + 0x14c))
            (*(int **)(in_ECX + 0x1c),0,*(undefined4 *)(in_ECX + 0x10),0x1c);
  *(undefined4 *)(in_ECX + 0x50348) = 0;
  *(undefined4 *)(in_ECX + 0x5034c) = 0;
  *(undefined4 *)(in_ECX + 0x50340) = 0;
  *(undefined4 *)(in_ECX + 0x50344) = 0;
  return 1;
}

