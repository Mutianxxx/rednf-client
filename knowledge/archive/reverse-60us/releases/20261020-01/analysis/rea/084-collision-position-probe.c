
undefined1 FUN_004e7dd0(undefined4 param_1,undefined4 param_2,int *param_3)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int *in_ECX;
  undefined1 uVar5;
  int iVar6;
  float10 fVar7;
  float local_10 [3];
  
  if (param_3 != (int *)0x0) {
    *param_3 = 0;
  }
  if (in_ECX[0x40] == 0) {
    return 1;
  }
  local_10[0] = 0.0;
  local_10[1] = 0.0;
  local_10[2] = 0.0;
  iVar6 = 0;
  do {
    piVar3 = *(int **)in_ECX[0x3e];
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)in_ECX[0x3e] + 2;
    }
    fVar7 = (float10)(**(code **)*piVar3)(iVar6);
    local_10[iVar6] = (float)fVar7;
    iVar6 = iVar6 + 1;
  } while (iVar6 < 3);
  iVar6 = *in_ECX;
  uVar2 = (**(code **)(iVar6 + 0x9c))();
  (**(code **)(iVar6 + 0x88))(param_1,param_2,uVar2);
  *(undefined1 *)(in_ECX[0x3e] + 0x7c) = 0;
  uVar5 = 1;
  iVar6 = FUN_0050b240(in_ECX);
  if (iVar6 == 0) {
    if ((*(int *)(in_ECX[0x40] + 0x114) != 0) &&
       (*(int *)(*(int *)(in_ECX[0x40] + 0x114) + 0x50) != 0)) {
      cVar1 = FUN_00485950(in_ECX);
      if (cVar1 == '\0') {
        uVar5 = 0;
      }
    }
  }
  else {
    piVar3 = (int *)FUN_00c00d0b(iVar6,0,&PTR_PTR_00f4287c,&PTR_PTR_00f428a0,0);
    if (piVar3 != (int *)0x0) {
      iVar4 = (**(code **)(*piVar3 + 0x33c))();
      if (*(int *)(iVar4 + 8) == 0) goto LAB_004e7ec7;
    }
    uVar5 = 0;
    if (param_3 != (int *)0x0) {
      *param_3 = iVar6;
    }
  }
LAB_004e7ec7:
  iVar6 = 0;
  do {
    piVar3 = *(int **)in_ECX[0x3e];
    if (piVar3 == (int *)0x0) {
      piVar3 = (int *)in_ECX[0x3e] + 2;
    }
    (**(code **)(*piVar3 + 4))(iVar6,local_10[iVar6]);
    iVar6 = iVar6 + 1;
  } while (iVar6 < 3);
  *(undefined1 *)(in_ECX[0x3e] + 0x7c) = 1;
  return uVar5;
}

