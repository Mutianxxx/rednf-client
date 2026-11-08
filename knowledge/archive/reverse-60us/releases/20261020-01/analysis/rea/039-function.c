
undefined4 FUN_00b084f0(short *param_1)

{
  short sVar1;
  int in_ECX;
  undefined4 uVar2;
  
  if (*(short *)(in_ECX + 0x50340) != *param_1) {
    switch(*param_1) {
    case 0:
      (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x13,5);
      uVar2 = 6;
      break;
    case 1:
      (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x13,9);
      uVar2 = 5;
      break;
    case 2:
      (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x13,5);
      uVar2 = 2;
      break;
    case 3:
      (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x13,4);
      uVar2 = 6;
      break;
    case 4:
      (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x13,10);
      uVar2 = 1;
      break;
    default:
      goto LAB_00b08585;
    }
    (**(code **)(**(int **)(in_ECX + 0x1c) + 200))(*(int **)(in_ECX + 0x1c),0x14,uVar2);
  }
LAB_00b08585:
  sVar1 = param_1[1];
  if (*(short *)(in_ECX + 0x50342) != sVar1) {
    if (sVar1 == 0) {
      (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,1,4);
      uVar2 = 0;
    }
    else {
      if (sVar1 != 1) goto LAB_00b085d7;
      (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,1,3);
      uVar2 = 3;
    }
    (**(code **)(**(int **)(in_ECX + 0x1c) + 0xfc))(*(int **)(in_ECX + 0x1c),0,3,uVar2);
  }
LAB_00b085d7:
  if (*(int *)(in_ECX + 0x50344) != *(int *)(param_1 + 2)) {
    (**(code **)(**(int **)(in_ECX + 0x1c) + 200))
              (*(int **)(in_ECX + 0x1c),0x3c,
               (*(uint *)(param_1 + 2) & 0xff) << 0x10 | (uint)*(byte *)(param_1 + 3) |
               *(uint *)(param_1 + 2) & 0xff00ff00);
  }
  *(undefined4 *)(in_ECX + 0x50340) = *(undefined4 *)param_1;
  *(undefined4 *)(in_ECX + 0x50344) = *(undefined4 *)(param_1 + 2);
  return 1;
}

