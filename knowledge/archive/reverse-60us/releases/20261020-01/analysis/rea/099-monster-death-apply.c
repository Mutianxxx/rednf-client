
void FUN_004f4440(int *param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *in_ECX;
  uint uVar4;
  
  for (uVar4 = 0; (in_ECX[0x8c2] != 0 && (uVar4 < (uint)((in_ECX[0x8c3] - in_ECX[0x8c2]) / 0x24)));
      uVar4 = uVar4 + 1) {
    FUN_0074e960(param_1);
  }
  FUN_004b20d0(param_1);
  if (param_1 == in_ECX) {
    iVar2 = FUN_00402060();
    if (iVar2 != 3) {
      iVar2 = FUN_00402060();
      if (iVar2 != 10) goto LAB_004f44cf;
    }
    iVar2 = (**(code **)(*in_ECX + 0x4c))();
    *(undefined1 *)(iVar2 + 0x4c) = 0;
  }
LAB_004f44cf:
  if ((int *)in_ECX[0x6e0] == param_1) {
    in_ECX[0x6e0] = 0;
  }
  if ((int *)in_ECX[0x6df] == param_1) {
    in_ECX[0x6df] = 0;
  }
  if ((int *)in_ECX[0x6e1] == param_1) {
    in_ECX[0x6e1] = 0;
  }
  if ((int *)in_ECX[0x13c] == param_1) {
    (**(code **)(*in_ECX + 0x328))(0);
  }
  if ((int *)in_ECX[0x821] == param_1) {
    cVar1 = (**(code **)(*param_1 + 0x2c))(0x211);
    if (cVar1 != '\0') {
      iVar2 = *in_ECX;
      uVar3 = (**(code **)(*param_1 + 0x358))();
      (**(code **)(iVar2 + 0x354))(uVar3);
      return;
    }
    (**(code **)(*in_ECX + 0x354))(0);
  }
  return;
}

