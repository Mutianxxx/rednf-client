
undefined4
FUN_004e9ea0(int *param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
            undefined4 param_6,undefined4 param_7,int *param_8,undefined4 param_9,
            undefined4 param_10,undefined4 param_11,int param_12)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  
  if (param_1 != (int *)0x0) {
    cVar1 = (**(code **)(*param_1 + 0x168))();
    if ((cVar1 != '\0') || (cVar1 = (**(code **)(*param_1 + 100))(), cVar1 == '\0')) {
      return 0xffff;
    }
    cVar1 = (**(code **)(*param_1 + 0x34))();
    if ((cVar1 != '\0') &&
       (iVar2 = FUN_00c00d0b(param_1,0,&PTR_PTR_00f40910,&PTR_PTR_00f42908,0), iVar2 != 0)) {
      for (piVar3 = *(int **)(*(int *)(iVar2 + 0x2874) + 0xb10);
          piVar3 != *(int **)(*(int *)(iVar2 + 0x2874) + 0xb14); piVar3 = piVar3 + 1) {
        if (param_2 == *piVar3) {
          return 0xffff;
        }
      }
    }
  }
  (**(code **)(*DAT_01003164 + 8))(0x15,2);
  if (param_1 == (int *)0x0) {
    (**(code **)(*DAT_01003164 + 0x24))(0xffff);
    (**(code **)(*DAT_01003164 + 0x24))(0);
  }
  else {
    iVar2 = *DAT_01003164;
    uVar4 = (**(code **)(*param_1 + 0x3c))();
    (**(code **)(iVar2 + 0x24))(uVar4);
    iVar2 = *DAT_01003164;
    uVar4 = (**(code **)(*param_1 + 0x40))();
    (**(code **)(iVar2 + 0x24))(uVar4);
  }
  if (param_8 == (int *)0x0) {
    (**(code **)(*DAT_01003164 + 0x24))(0xffff);
    (**(code **)(*DAT_01003164 + 0x24))(0);
  }
  else {
    iVar2 = *DAT_01003164;
    uVar4 = (**(code **)(*param_8 + 0x3c))();
    (**(code **)(iVar2 + 0x24))(uVar4);
    iVar2 = *DAT_01003164;
    uVar4 = (**(code **)(*param_8 + 0x40))();
    (**(code **)(iVar2 + 0x24))(uVar4);
  }
  (**(code **)(*DAT_01003164 + 0x24))(1);
  (**(code **)(*DAT_01003164 + 0x24))(param_2);
  (**(code **)(*DAT_01003164 + 0x2c))(param_3);
  iVar2 = *DAT_01003164;
  uVar4 = (**(code **)(*DAT_0104f1d4 + 0x6e0))();
  (**(code **)(iVar2 + 0x24))(uVar4);
  (**(code **)(*DAT_01003164 + 0x88))();
  uVar4 = FUN_0050d430();
  (**(code **)(*DAT_01003164 + 0x24))(uVar4);
  (**(code **)(*DAT_01003164 + 0x20))(0);
  (**(code **)(*DAT_01003164 + 0x20))(param_7);
  (**(code **)(*DAT_01003164 + 0x24))(param_4);
  (**(code **)(*DAT_01003164 + 0x24))(param_5);
  (**(code **)(*DAT_01003164 + 0x24))(param_6);
  (**(code **)(*DAT_01003164 + 0x38))(param_10,param_9);
  (**(code **)(*DAT_01003164 + 0x24))(param_11);
  if (param_12 == 0) {
    (**(code **)(*DAT_01003164 + 0x20))(0);
  }
  else {
    (**(code **)(*DAT_01003164 + 0x20))(1);
    (**(code **)(*DAT_01003164 + 0x34))(param_12,4);
  }
  (**(code **)(*DAT_010c0790 + 0x44))(1,0xffffffff,0,3);
  return uVar4;
}

