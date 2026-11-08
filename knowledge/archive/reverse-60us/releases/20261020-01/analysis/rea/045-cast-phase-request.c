
void FUN_004d80f0(int param_1,int *param_2)

{
  char cVar1;
  int iVar2;
  int *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar3;
  undefined1 local_20 [4];
  void *local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c58546;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  cVar1 = FUN_0049c090();
  if (cVar1 != '\0') {
    if (param_1 == -1) {
      iVar2 = (**(code **)(*in_ECX + 0x9c))();
      if (iVar2 < 1) {
        (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
        *unaff_FS_OFFSET = local_10;
        return;
      }
      local_1c = (void *)0x0;
      local_18 = 0;
      local_14 = 0;
      local_8 = 0;
      param_1 = 1;
      FUN_00407120(&param_1);
      param_1 = 0;
      FUN_00407120(&param_1);
      param_1 = 0;
      FUN_00407120(&param_1);
      uVar3 = 6;
    }
    else {
      local_1c = (void *)0x0;
      local_18 = 0;
      local_14 = 0;
      local_8 = 1;
      FUN_00407120(&param_1);
      if (param_2 != (int *)0x0) {
        param_1 = (**(code **)(*param_2 + 0x44))();
        FUN_00407120(&param_1);
      }
      uVar3 = 10;
    }
    (**(code **)(*in_ECX + 0x28c))(uVar3,local_20,0,0,0);
    if (local_1c != (void *)0x0) {
      _free(local_1c);
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

