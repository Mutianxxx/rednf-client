
void FUN_004a0da0(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int in_ECX;
  int local_8;
  
  uVar1 = param_1;
  *(undefined4 *)(in_ECX + 0x868) = param_1;
  local_8 = in_ECX;
  FUN_00434310(&local_8,&param_1);
  if (local_8 != DAT_010be3ec) {
    if (*(uint *)(local_8 + 0x28) < 8) {
      local_8 = local_8 + 0x14;
    }
    else {
      local_8 = *(int *)(local_8 + 0x14);
    }
    if (local_8 != 0) {
      FUN_0049f4d0(local_8,param_2);
      return;
    }
  }
  (*(code *)PTR_FUN_00ff2ebc)(u_PASSIVEOBJECT_CREATE_FAIL__INDEX_00ccf148,uVar1);
  return;
}

