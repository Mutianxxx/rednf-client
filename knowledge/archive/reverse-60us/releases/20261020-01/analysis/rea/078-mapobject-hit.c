
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_005f5fb0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  float10 fVar4;
  undefined1 local_24 [4];
  void *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c675ba;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  (**(code **)(*param_1 + 0x19c))();
  iVar1 = FUN_00402060();
  if (((iVar1 != 0) || (fVar4 = (float10)FUN_004333b0(), (float10)_DAT_00e9d7a4 < fVar4)) ||
     (iVar1 = FUN_00402060(), 0 < iVar1)) {
    if ((int *)in_ECX[0x23a] != (int *)0x0) {
      iVar1 = *(int *)in_ECX[0x23a];
      iVar2 = (**(code **)(*in_ECX + 0x9c))();
      iVar2 = (**(code **)(*in_ECX + 0x98))(iVar2 + in_ECX[0x21e]);
      iVar2 = (**(code **)(*in_ECX + 0x94))(iVar2 + in_ECX[0x21d]);
      (**(code **)(iVar1 + 0x28))(iVar2 + in_ECX[0x21c]);
      (**(code **)(*(int *)in_ECX[0x23a] + 0xc))(0);
      (**(code **)(*(int *)in_ECX[0x23a] + 0x5c))(local_24);
      local_8 = 0;
      FUN_0050e060(in_ECX,2,0,local_24,0);
      local_8 = 0xffffffff;
      if (local_20 != (void *)0x0) {
        _free(local_20);
      }
      local_20 = (void *)0x0;
      local_1c = 0;
      local_18 = 0;
    }
    iVar1 = FUN_00a530f0();
    if (iVar1 != 0) {
      local_14 = *in_ECX;
      uVar3 = FUN_00a530f0(0xffffffff,0,0);
      (**(code **)(local_14 + 0x10c))(uVar3);
    }
  }
  FUN_0049f310(param_1,param_2,param_3);
  *unaff_FS_OFFSET = local_10;
  return;
}

