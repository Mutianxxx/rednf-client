
void FUN_004b20d0(int *param_1)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int *in_ECX;
  int *piVar4;
  int *local_8;
  
  piVar1 = param_1;
  local_8 = in_ECX;
  FUN_004edd10(param_1);
  cVar2 = (**(code **)(*piVar1 + 0x2c))(0x21);
  if (cVar2 != '\0') {
    FUN_004b6a00(piVar1);
  }
  piVar4 = in_ECX + 0x4a5;
  param_1 = (int *)0x12;
  do {
    if ((int *)*piVar4 != (int *)0x0) {
      cVar2 = (**(code **)(*(int *)*piVar4 + 8))();
      if (cVar2 != '\0') {
        (**(code **)(*(int *)*piVar4 + 0x1c))(piVar1);
      }
    }
    piVar4 = piVar4 + 1;
    param_1 = (int *)((int)param_1 + -1);
  } while (param_1 != (int *)0x0);
  if (in_ECX[0x4b7] != 0) {
    FUN_005657c0(piVar1);
  }
  if (piVar1 == in_ECX) {
    (**(code **)(*in_ECX + 0x110))(0);
    (**(code **)(*in_ECX + 0x110))(1);
    (**(code **)(*in_ECX + 0x110))(2);
    (**(code **)(*in_ECX + 0x110))(4);
    (**(code **)(*in_ECX + 0x110))(5);
    (**(code **)(*in_ECX + 0x110))(6);
    (**(code **)(*in_ECX + 0x110))(7);
    (**(code **)(*in_ECX + 0x110))(8);
    (**(code **)(*in_ECX + 0x110))(9);
    if (*(int **)(*(int *)(DAT_0100316c + 0x58) + 0x670) == in_ECX) {
      iVar3 = (**(code **)(*in_ECX + 0x234))();
      if (iVar3 == 0) {
        FUN_009aacf0(1);
      }
      if (*(char *)(*(int *)(DAT_0100316c + 0x58) + 0x6d8) == '\0') {
        FUN_009af8a0(0);
      }
      else {
        *(undefined4 *)(*(int *)(DAT_0100316c + 0x58) + 0x670) = 0;
      }
    }
  }
  if ((int *)in_ECX[0x13c] == piVar1) {
    (**(code **)(*in_ECX + 0x328))(0);
  }
  param_1 = (int *)FUN_00c00d0b(piVar1,0,&PTR_PTR_00f40910,&PTR_PTR_00f4287c,0);
  if (param_1 != (int *)0x0) {
    FUN_00a64ce0(&local_8,&param_1);
    piVar1 = local_8;
    if (local_8 != (int *)in_ECX[0x671]) {
      piVar4 = local_8 + 3;
      local_8 = (int *)0x0;
      FUN_004b76c0(&local_8);
      FUN_00b16550(piVar4);
      FUN_006dbef0(&local_8,piVar1);
    }
    FUN_00a64ce0(&local_8,&param_1);
    piVar1 = local_8;
    if (local_8 != (int *)in_ECX[0x667]) {
      piVar4 = local_8 + 3;
      param_1 = (int *)0x0;
      FUN_004b76c0(&param_1);
      FUN_00b16550(piVar4);
      FUN_006dbef0(&param_1,piVar1);
    }
  }
  return;
}

