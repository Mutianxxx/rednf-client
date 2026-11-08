
void FUN_00509a90(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  undefined4 *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c5a338;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_00407a00();
  local_8 = 0;
  *in_ECX = &PTR_FUN_00cd5b5c;
  FUN_0081cee0();
  FUN_0081cfa0(param_1,param_2,param_3,param_4,param_5,param_6);
  *unaff_FS_OFFSET = local_10;
  return;
}

