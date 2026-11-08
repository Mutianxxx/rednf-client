
void FUN_0081cfa0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6)

{
  uint *puVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  float *pfVar5;
  float fVar6;
  int in_ECX;
  undefined4 *puVar7;
  undefined4 *unaff_FS_OFFSET;
  float10 fVar8;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_10 = *unaff_FS_OFFSET;
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c7c947;
  *unaff_FS_OFFSET = &local_10;
  *(int *)(in_ECX + 0x1fc) = param_1;
  if (param_2 < 0x7531) {
    param_2 = 30000;
  }
  else if (169999 < param_2) {
    param_2 = 170000;
  }
  *(int *)(in_ECX + 0x200) = param_2;
  *(undefined4 *)(in_ECX + 0x204) = param_3;
  *(undefined4 *)(in_ECX + 0x208) = param_4;
  *(undefined1 *)(in_ECX + 0x20c) = 0;
  if (*(int *)(DAT_01002848 + 0x19a8) != 2) {
    iVar2 = FUN_00403c50(0x1b4);
    local_8 = 4;
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00453320(u_Monster_Common_Particle_MonsterD_00df71f0,0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(in_ECX + 0x210) = uVar3;
    goto LAB_0081d13f;
  }
  if (param_1 == 1) {
    iVar2 = FUN_00403c50(0x1b4);
    local_8 = 0;
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00453320(u_Monster_Common_Particle_Teen_Mon_00e0b228,0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(in_ECX + 0x214) = uVar3;
    iVar2 = FUN_00403c50(0x1b4);
    local_8 = 1;
    if (iVar2 == 0) {
LAB_0081d0e2:
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00453320(u_Monster_Common_Particle_Teen_Mon_00e0b1b8,0);
    }
  }
  else {
    iVar2 = FUN_00403c50(0x1b4);
    local_8 = 2;
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_00453320(u_Monster_Common_Particle_Teen_Mon_00e0b148,0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(in_ECX + 0x214) = uVar3;
    iVar2 = FUN_00403c50(0x1b4);
    local_8 = 3;
    if (iVar2 == 0) goto LAB_0081d0e2;
    uVar3 = FUN_00453320(u_Monster_Common_Particle_Teen_Mon_00e0b0d8,0);
  }
  puVar7 = (undefined4 *)(in_ECX + 0x214);
  local_8 = 0xffffffff;
  *(undefined4 *)(in_ECX + 0x218) = uVar3;
  iVar2 = 2;
  do {
    (**(code **)(*(int *)*puVar7 + 0x68))(param_6);
    puVar7 = puVar7 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
LAB_0081d13f:
  if (*(int *)(DAT_01002848 + 0x19a8) == 2) {
    puVar7 = (undefined4 *)(in_ECX + 0x214);
    param_1 = 2;
    do {
      (**(code **)(*(int *)*puVar7 + 0x1c))();
      iVar2 = (**(code **)(*(int *)*puVar7 + 0x24))();
      FUN_00b099b0(0x41200000,0x41f00000,*(int *)(in_ECX + 0x200) + -30000,140000);
      uVar4 = FUN_00c01544();
      puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(iVar2 + 8) * 4);
      puVar7 = puVar7 + 1;
      *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ uVar4;
      puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(iVar2 + 8) * 4);
      param_1 = param_1 + -1;
      *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ uVar4;
    } while (param_1 != 0);
  }
  else {
    (**(code **)(**(int **)(in_ECX + 0x210) + 0x1c))();
    pfVar5 = (float *)(**(code **)(**(int **)(in_ECX + 0x210) + 0x24))();
    fVar8 = (float10)FUN_00b099b0(0x41a00000,0x42700000,*(int *)(in_ECX + 0x200) + -30000,140000);
    *pfVar5 = (float)fVar8;
    FUN_00b099b0(0x42480000,0x43160000,*(int *)(in_ECX + 0x200) + -30000,140000);
    fVar6 = (float)FUN_00c01544();
    pfVar5[4] = fVar6;
    pfVar5[5] = (float)((int)fVar6 * 2);
    pfVar5[6] = fVar6;
  }
  FUN_00b099b0(0x447a0000,0x44fa0000,*(int *)(in_ECX + 0x200) + -30000,140000);
  uVar3 = FUN_00c01544();
  *(undefined4 *)(in_ECX + 0x21c) = uVar3;
  *(undefined4 *)(in_ECX + 0x220) = param_5;
  *unaff_FS_OFFSET = local_10;
  return;
}

