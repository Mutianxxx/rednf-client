
void FUN_005f6640(void)

{
  int iVar1;
  undefined4 uVar2;
  int *in_ECX;
  int iVar3;
  int *piVar4;
  undefined4 *unaff_FS_OFFSET;
  int *piVar5;
  int *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c675f3;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if ((in_ECX[0x153] != 0) && (4 < (uint)(in_ECX[0x154] - in_ECX[0x153] >> 2))) {
    local_14 = in_ECX + 0x239;
    iVar3 = 0;
    do {
      local_8 = 0xffffffff;
      if ((*(int *)(iVar3 + in_ECX[0x153]) != 0) &&
         (*(int *)(*(int *)(iVar3 + in_ECX[0x153]) + 4) != 0)) {
        iVar1 = FUN_00403c50(0x1b4);
        local_8 = 0;
        if (iVar1 == 0) {
          iVar1 = 0;
        }
        else {
          if ((uint)in_ECX[0x97] < 8) {
            piVar4 = in_ECX + 0x92;
          }
          else {
            piVar4 = (int *)in_ECX[0x92];
          }
          piVar5 = in_ECX;
          uVar2 = FUN_00a530f0();
          iVar1 = FUN_004a3440(piVar4,uVar2,piVar5);
        }
        *local_14 = iVar1;
      }
      local_8 = 0xffffffff;
      iVar3 = iVar3 + 4;
      local_14 = local_14 + 1;
    } while (iVar3 < 0xc);
    if ((in_ECX[0x153] != 0) && (1 < (uint)(in_ECX[0x154] - in_ECX[0x153] >> 2))) {
      iVar3 = 0xc;
      do {
        iVar1 = *(int *)(iVar3 + in_ECX[0x153]);
        if ((iVar1 != 0) && (*(int *)(iVar1 + 4) != 0)) {
          FUN_00a53490(iVar3 + in_ECX[0x153]);
        }
        iVar3 = iVar3 + 4;
      } while (iVar3 < 0x18);
    }
  }
  piVar4 = (int *)in_ECX[0x8d];
  if ((piVar4 != (int *)0x0) && (5 < (uint)(in_ECX[0x8e] - (int)piVar4 >> 2))) {
    in_ECX[0x220] = *piVar4;
    in_ECX[0x221] = piVar4[1];
    *(bool *)(in_ECX + 0x222) = piVar4[2] != 0;
    in_ECX[0x21c] = piVar4[3];
    in_ECX[0x21d] = piVar4[4];
    in_ECX[0x21e] = piVar4[5];
    (**(code **)(*in_ECX + 0x35c))(piVar4[6]);
    (**(code **)(*in_ECX + 0x360))(*(undefined4 *)(in_ECX[0x8d] + 0x18));
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

