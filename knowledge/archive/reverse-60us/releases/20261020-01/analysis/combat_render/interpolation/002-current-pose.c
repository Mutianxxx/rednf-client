
void FUN_00a24950(void)

{
  float fVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  int iVar6;
  undefined4 uVar7;
  int in_ECX;
  int iVar8;
  int iVar9;
  float10 fVar10;
  int local_8;
  
  if ((((*(char *)(in_ECX + 200) != '\0') && (*(char *)(in_ECX + 0x13a) != '\x01')) &&
      (*(int *)(in_ECX + 0x98) != 0)) &&
     ((*(int *)(in_ECX + 0x9c) - *(int *)(in_ECX + 0x98)) / 0x7c != 0)) {
    iVar8 = 0;
    if (*(int *)(in_ECX + 0x98) != 0) {
      iVar8 = (*(int *)(in_ECX + 0x9c) - *(int *)(in_ECX + 0x98)) / 0x7c;
    }
    iVar6 = *(int *)(in_ECX + 0x124);
    if (iVar6 == iVar8 + -1) {
      if (*(char *)(in_ECX + 0x130) == '\0') {
        return;
      }
      iVar8 = *(int *)(in_ECX + 0x98);
      local_8 = iVar8;
    }
    else {
      iVar8 = *(int *)(in_ECX + 0x98);
      local_8 = (iVar6 + 1) * 0x7c + iVar8;
    }
    iVar8 = iVar6 * 0x7c + iVar8;
    if (*(int *)(in_ECX + 0x188) == 0) {
      iVar6 = *(int *)(in_ECX + 0x8c);
    }
    else {
      iVar6 = FUN_004caa00();
    }
    iVar6 = iVar6 - *(int *)(in_ECX + 0x128);
    iVar9 = *(int *)(in_ECX + 300) - *(int *)(in_ECX + 0x128);
    uVar7 = FUN_00473f20(*(undefined4 *)(iVar8 + 8),*(undefined4 *)(local_8 + 8),iVar6,iVar9);
    *(undefined4 *)(in_ECX + 0xb0) = uVar7;
    uVar7 = FUN_00473f20(*(undefined4 *)(iVar8 + 0xc),*(undefined4 *)(local_8 + 0xc),iVar6,iVar9);
    *(undefined4 *)(in_ECX + 0xb4) = uVar7;
    fVar10 = (float10)FUN_00b099b0(*(int *)(iVar8 + 0x10) - (iVar8 + 0x10) ^ DAT_010d3efc,
                                   *(int *)(local_8 + 0x10) - (local_8 + 0x10) ^ DAT_010d3efc,iVar6,
                                   iVar9);
    *(uint *)(in_ECX + 0xb8) = ((uint)(float)fVar10 ^ DAT_010d3efc) + in_ECX + 0xb8;
    fVar10 = (float10)FUN_00b099b0(*(int *)(iVar8 + 0x14) - (iVar8 + 0x14) ^ DAT_010d3efc,
                                   *(int *)(local_8 + 0x14) - (local_8 + 0x14) ^ DAT_010d3efc,iVar6,
                                   iVar9);
    *(uint *)(in_ECX + 0xbc) = ((uint)(float)fVar10 ^ DAT_010d3efc) + in_ECX + 0xbc;
    fVar10 = (float10)FUN_00b099b0(*(undefined4 *)(iVar8 + 0x18),*(undefined4 *)(local_8 + 0x18),
                                   iVar6,iVar9);
    *(float *)(in_ECX + 0xc0) = (float)fVar10;
    uVar2 = FUN_00473f20(*(undefined1 *)(iVar8 + 0x1c),*(undefined1 *)(local_8 + 0x1c),iVar6,iVar9);
    uVar3 = FUN_00473f20(*(undefined1 *)(iVar8 + 0x1d),*(undefined1 *)(local_8 + 0x1d),iVar6,iVar9);
    uVar4 = FUN_00473f20(*(undefined1 *)(iVar8 + 0x1e),*(undefined1 *)(local_8 + 0x1e),iVar6,iVar9);
    uVar5 = FUN_00473f20(*(undefined1 *)(iVar8 + 0x1f),*(undefined1 *)(local_8 + 0x1f),iVar6,iVar9);
    *(uint *)(in_ECX + 0xc4) = CONCAT31(CONCAT21(CONCAT11(uVar5,uVar4),uVar3),uVar2);
    fVar1 = *(float *)(iVar8 + 0x18);
    *(undefined4 *)(in_ECX + 0x13c) = 0;
    *(float *)(in_ECX + 0x2c) = *(float *)(in_ECX + 0xc0) - fVar1;
  }
  return;
}

