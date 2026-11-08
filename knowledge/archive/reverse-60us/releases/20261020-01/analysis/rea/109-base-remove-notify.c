
void FUN_0049bc20(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  char cVar4;
  int *in_ECX;
  undefined1 local_8 [4];
  
  piVar3 = param_1;
  if ((*(int **)(in_ECX[0x3e] + 0x90) == param_1) && (param_1 != (int *)0x0)) {
    FUN_00510e80(0);
    cVar4 = (**(code **)(*in_ECX + 0x2c))(2);
    if (cVar4 != '\0') {
      (**(code **)(*in_ECX + 0x60))(0);
    }
  }
  if ((int *)in_ECX[0x52] != (int *)0x0) {
    (**(code **)(*(int *)in_ECX[0x52] + 8))(piVar3);
  }
  if ((int *)in_ECX[0x55] != (int *)0x0) {
    (**(code **)(*(int *)in_ECX[0x55] + 8))(piVar3);
  }
  param_1 = *(int **)in_ECX[0x5f];
  if (param_1 != (int *)in_ECX[0x5f]) {
    do {
      if (*(int **)((int)param_1 + 0x10) == piVar3) {
        param_1 = (int *)FUN_00405850(local_8,param_1);
        param_1 = (int *)*param_1;
      }
      else {
        FUN_0044cee0();
      }
    } while (param_1 != (int *)in_ECX[0x5f]);
  }
  if (in_ECX == piVar3) {
    while ((iVar1 = in_ECX[0x4c], iVar1 != 0 && (in_ECX[0x4d] - iVar1 >> 2 != 0))) {
      uVar2 = *(undefined4 *)(in_ECX[0x4d] + -4);
      if ((iVar1 != 0) && (in_ECX[0x4d] - iVar1 >> 2 != 0)) {
        in_ECX[0x4d] = in_ECX[0x4d] + -4;
      }
      (**(code **)(*in_ECX + 0xfc))(uVar2);
    }
    iVar1 = in_ECX[0x51];
    while (iVar1 != 0) {
      iVar1 = *(int *)(*(int *)in_ECX[0x50] + 0xc);
      param_1 = (int *)iVar1;
      FUN_0049ca70(&param_1);
      (**(code **)(*in_ECX + 0xfc))(iVar1);
      if (iVar1 != 0) {
        FUN_004089d0();
        FUN_00401f50(iVar1);
      }
      iVar1 = in_ECX[0x51];
    }
  }
  return;
}

