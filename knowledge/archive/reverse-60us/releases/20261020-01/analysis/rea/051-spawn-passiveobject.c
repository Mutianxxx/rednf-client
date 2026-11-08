
undefined4
FUN_004ea4d0(undefined4 param_1,undefined4 param_2,int *param_3,undefined4 param_4,int param_5,
            int param_6,int param_7,int param_8)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int *in_ECX;
  
  cVar5 = (**(code **)(*in_ECX + 0x168))();
  if (((cVar5 != '\0') || (cVar5 = (**(code **)(*in_ECX + 100))(), cVar5 == '\0')) ||
     (cVar5 = FUN_0049c090(), cVar5 == '\0')) {
    return 0xffff;
  }
  if (param_8 == 4) {
    param_8 = (**(code **)(*in_ECX + 0xc0))();
  }
  iVar6 = (**(code **)(*in_ECX + 0x94))();
  iVar7 = (**(code **)(*in_ECX + 0x98))();
  iVar8 = (**(code **)(*in_ECX + 0x9c))();
  if (param_8 != 1) {
    param_5 = -param_5;
  }
  if (param_3 == (int *)0x0) {
    uVar9 = FUN_004e9ea0();
    return uVar9;
  }
  iVar1 = *param_3;
  iVar2 = param_3[1];
  iVar3 = param_3[2];
  iVar4 = param_3[0x16];
  *param_3 = iVar6 + param_5;
  param_3[2] = iVar8 + param_7;
  *(bool *)(param_3 + 0x16) = param_8 != 1;
  param_3[1] = iVar7 + param_6;
  uVar9 = FUN_004ea100();
  *param_3 = iVar1;
  param_3[1] = iVar2;
  param_3[2] = iVar3;
  *(char *)(param_3 + 0x16) = (char)iVar4;
  return uVar9;
}

