
undefined4 FUN_004eb600(int *param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int *in_ECX;
  
  cVar1 = (**(code **)(*in_ECX + 0x2c))(0x21);
  if ((cVar1 != '\0') || (cVar1 = (**(code **)(*param_1 + 0x2c))(0x21), cVar1 != '\0')) {
    iVar2 = (**(code **)(*in_ECX + 0x1fc))();
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = (**(code **)(*in_ECX + 0x200))();
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = (**(code **)(*param_1 + 0x1fc))();
    if (iVar2 == 0) {
      return 0;
    }
    iVar2 = (**(code **)(*param_1 + 0x200))();
    if (iVar2 == 0) {
      return 0;
    }
    cVar1 = (**(code **)(*in_ECX + 0x248))(param_1);
    if (cVar1 == '\0') {
      return 0;
    }
    cVar1 = (**(code **)(*in_ECX + 0x2c))(0x21);
    if (cVar1 != '\0') {
      iVar2 = (**(code **)(*in_ECX + 0x33c))();
      switch(*(undefined4 *)(iVar2 + 8)) {
      case 1:
        cVar1 = FUN_00484670();
        if (cVar1 == '\0') {
          return 1;
        }
        break;
      case 2:
        cVar1 = FUN_004eb1d0(param_1);
        if (cVar1 == '\0') {
          return 1;
        }
        break;
      case 3:
      case 4:
        iVar2 = (**(code **)(*param_1 + 0x1c4))();
        iVar3 = (**(code **)(*in_ECX + 0x1c4))();
        if (iVar3 != iVar2) {
          return 1;
        }
      }
    }
    cVar1 = (**(code **)(*param_1 + 0x2c))(0x21);
    if (cVar1 != '\0') {
      iVar2 = (**(code **)(*param_1 + 0x33c))();
      switch(*(int *)(iVar2 + 8) + -1) {
      case 0:
        iVar2 = (**(code **)(*in_ECX + 0x204))();
        if (iVar2 < 1) {
          return 1;
        }
        break;
      case 1:
        cVar1 = FUN_004eb1d0(in_ECX);
        if (cVar1 == '\0') {
          return 1;
        }
        break;
      case 2:
      case 3:
        iVar2 = (**(code **)(*param_1 + 0x1c4))();
        iVar3 = (**(code **)(*in_ECX + 0x1c4))();
        if (iVar3 != iVar2) {
          return 1;
        }
      }
    }
  }
  return 0;
}

