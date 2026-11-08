
int FUN_004ba620(int *param_1,int *param_2,int param_3,char param_4)

{
  int iVar1;
  int iVar2;
  int *in_ECX;
  int iVar3;
  
  if (param_3 == 1) {
    *param_1 = 800;
  }
  else {
    if (param_3 != 2) {
      if (param_4 == '\0') {
        if (param_3 == -1) {
          *param_1 = 0;
          iVar3 = 0x1e;
        }
        else {
          *param_1 = 400;
          iVar3 = 0x96;
        }
      }
      else {
        *param_1 = 0;
        iVar3 = 0;
      }
      (**(code **)(*in_ECX + 0x344))(3);
      FUN_00402060();
      FUN_004333b0();
      iVar1 = FUN_00c01544();
      if (-iVar1 != -2000 && -1 < -iVar1 + 2000) {
        (**(code **)(*in_ECX + 0x344))(3);
        FUN_004bdd40();
      }
      FUN_00c01544();
      iVar1 = FUN_00c01544();
      if (iVar1 < iVar3) {
        iVar3 = iVar1;
      }
      goto LAB_004ba716;
    }
    *param_1 = 400;
  }
  iVar1 = FUN_00c01544();
  iVar3 = iVar1;
LAB_004ba716:
  iVar2 = FUN_00402060();
  if (iVar2 == 0) {
    *param_1 = 0;
    *param_2 = 0;
    return iVar1;
  }
  if (iVar3 != 0) {
    *param_2 = (*param_1 * -1000) / iVar3;
    return iVar1;
  }
  *param_2 = 0;
  return iVar1;
}

