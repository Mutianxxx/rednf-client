
int FUN_004b9fa0(char param_1)

{
  int iVar1;
  int iVar2;
  int *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  bool bVar3;
  uint local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c57849;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  bVar3 = param_1 != '\0';
  if (bVar3) {
    local_14 = 0xfffffa24;
    FUN_00402150(&local_14);
    local_8 = 0;
  }
  local_14 = (uint)bVar3;
  iVar1 = FUN_00402060();
  local_8 = 0xffffffff;
  if (bVar3) {
    FUN_00402010();
  }
  else if (iVar1 == 0) goto LAB_004ba055;
  if ((in_ECX[0x40] != 0) && (iVar2 = *(int *)(in_ECX[0x40] + 0x114), iVar2 != 0)) {
    iVar1 = iVar1 + *(int *)(iVar2 + 0x9dc) + in_ECX[0x598];
  }
  if (param_1 != '\0') {
    *unaff_FS_OFFSET = local_10;
    return iVar1;
  }
LAB_004ba055:
  (**(code **)(*in_ECX + 0x344))(3);
  FUN_00402060();
  FUN_004333b0();
  iVar2 = FUN_00c01544();
  *unaff_FS_OFFSET = local_10;
  return (iVar2 * iVar1) / 100;
}

