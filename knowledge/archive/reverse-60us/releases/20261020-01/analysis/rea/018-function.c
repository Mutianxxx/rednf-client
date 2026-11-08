
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4
FUN_004eb780(undefined4 param_1,undefined4 *param_2,uint *param_3,int *param_4,uint param_5,
            undefined4 *param_6)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int *in_ECX;
  uint *puVar10;
  uint *puVar11;
  uint uVar12;
  bool bVar13;
  float10 fVar14;
  undefined4 *puVar15;
  float local_1dc;
  undefined1 local_1d8;
  char local_1d7;
  float local_1d6;
  char acStack_1d2 [4];
  undefined1 local_1ce;
  float local_1cd;
  float local_1c9;
  float local_1c5;
  float local_1c1;
  uint auStack_1bd [3];
  float local_1b1;
  float local_1ad;
  float local_1a9;
  float local_1a5;
  float local_1a1;
  float local_19d;
  float local_199;
  float local_195;
  uint local_191;
  uint local_18d;
  uint local_189;
  uint local_185;
  float local_181;
  float local_17d;
  undefined4 local_179;
  undefined4 local_175;
  float local_171;
  float local_16d;
  float local_169;
  undefined4 auStack_165 [4];
  float local_155;
  undefined4 local_151;
  uint local_14d;
  float local_149;
  undefined4 local_145;
  uint local_141;
  float local_13d;
  float local_139;
  float local_135;
  float local_131;
  uint local_12d;
  undefined4 *local_129;
  undefined4 local_125;
  undefined4 local_121;
  float local_11d;
  undefined1 local_119;
  undefined1 local_118;
  char local_117;
  undefined4 auStack_116 [23];
  undefined4 auStack_ba [23];
  uint local_5e;
  double local_5a;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  undefined1 local_4f;
  undefined1 local_4e;
  undefined1 local_4d;
  undefined1 local_4c;
  undefined4 local_4b;
  undefined4 local_47;
  undefined4 local_43;
  undefined4 local_3f;
  undefined4 local_3b;
  char local_37;
  undefined1 local_36;
  undefined4 local_35;
  char local_31;
  int local_30;
  undefined4 local_2c;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  char local_25;
  int local_24;
  undefined1 local_20;
  undefined1 local_1b;
  int local_1a;
  undefined4 local_14;
  int local_10;
  int *local_c;
  float local_8;
  
  piVar1 = param_4;
  local_c = in_ECX;
  iVar3 = (**(code **)(*param_4 + 0x19c))();
  if (((iVar3 == 0) || ((int)param_3 < 1)) ||
     (local_10 = iVar3, cVar2 = FUN_00467480(), cVar2 == '\0')) {
    return 0;
  }
  param_4 = (int *)FUN_00c00d0b();
  FUN_00455a50();
  local_4b = (**(code **)(*piVar1 + 0x30))();
  local_47 = (**(code **)(*piVar1 + 0x2b0))();
  local_43 = (**(code **)(*in_ECX + 0x30))();
  local_3f = (**(code **)(*in_ECX + 0x2b0))();
  local_3b = (**(code **)(*in_ECX + 0x40))();
  local_37 = '\0';
  local_36 = 0;
  local_27 = FUN_004e90f0();
  local_26 = FUN_004e9160();
  local_35 = *param_2;
  local_31 = '\x01';
  local_25 = FUN_004e8b10(iVar3);
  if ((local_25 != '\0') && (param_4 != (int *)0x0)) {
    fVar14 = (float10)FUN_004333b0();
    local_8 = (float)(fVar14 * (float10)_DAT_00cc10ac);
    local_14 = (**(code **)(*param_4 + 0x234))();
    local_24 = FUN_00c01544();
    iVar4 = FUN_00c00d0b(param_4,0,&PTR_PTR_00f5526c,&PTR_PTR_00f42928,0);
    if (iVar4 != 0) {
      iVar5 = *(int *)(iVar4 + 0x19e4);
      if (iVar5 == 1) {
        local_24 = local_24 / 3;
      }
      else if (iVar5 == 2) {
        iVar4 = 0x55555556;
LAB_004eb90f:
        local_24 = (int)((ulonglong)((longlong)iVar4 * (longlong)local_24) >> 0x20);
        local_24 = local_24 - (local_24 >> 0x1f);
      }
      else if (iVar5 == 3) {
        local_24 = local_24 / 6;
      }
      else if (*(char *)(iVar4 + 0x1e1c) != '\0') {
        iVar4 = 0x2aaaaaab;
        goto LAB_004eb90f;
      }
    }
  }
  local_30 = (int)param_3;
  if (param_6 == (undefined4 *)0x0) {
    local_2c = FUN_008ae0f0(0);
  }
  else {
    local_2c = *param_6;
  }
  if (((in_ECX[0x40] != 0) && (iVar4 = *(int *)(in_ECX[0x40] + 0x114), iVar4 != 0)) &&
     (iVar4 = *(int *)(iVar4 + 0x50), iVar4 != 0)) {
    local_28 = *(undefined1 *)(iVar4 + 100);
  }
  iVar4 = (**(code **)(*piVar1 + 0x18c))();
  local_4f = iVar4 != 0;
  fVar14 = (float10)FUN_004333b0();
  local_1dc = (float)fVar14;
  local_1d8 = FUN_00402060();
  local_1d7 = *(char *)(iVar3 + 0x18);
  iVar4 = FUN_00402060();
  local_1d6 = (float)iVar4;
  param_3 = (uint *)**(int **)(iVar3 + 0x40);
  if (param_3 != (uint *)*(int **)(iVar3 + 0x40)) {
    do {
      if (*(int *)((int)param_3 + 0xc) != 4) {
        acStack_1d2[*(int *)((int)param_3 + 0xc)] = '\x01';
      }
      FUN_004332c0();
    } while (param_3 != (uint *)*(int *)(iVar3 + 0x40));
  }
  if (param_4 != (int *)0x0) {
    param_3 = (uint *)0x0;
    iVar4 = 0x88;
    do {
      if (acStack_1d2[(int)param_3] != '\0') {
        local_8 = (float)(**(code **)(*param_4 + 0x344))(3);
        iVar5 = FUN_00402060();
        param_6 = (undefined4 *)(float)iVar5;
        FUN_004333b0();
        uVar6 = FUN_00c01544();
        auStack_165[(int)param_3] = uVar6;
      }
      param_3 = (uint *)((int)param_3 + 1);
      iVar4 = iVar4 + 8;
    } while (iVar4 < 0xa8);
  }
  local_1ce = FUN_00402060();
  param_3 = (uint *)FUN_00402060();
  local_1cd = (float)(int)param_3;
  fVar14 = (float10)FUN_004333b0();
  local_1c9 = (float)fVar14;
  fVar14 = (float10)FUN_004333b0();
  local_1c5 = (float)fVar14;
  fVar14 = (float10)FUN_004333b0();
  local_1c1 = (float)fVar14;
  param_3 = (uint *)0x0;
  puVar11 = (uint *)(iVar3 + 0x140);
  iVar3 = DAT_012101d8;
  do {
    if ((*puVar11 ^ DAT_012101dc) - (int)puVar11 != puVar11[1]) {
      FUN_00b170b0(puVar11,0x3f);
      iVar3 = DAT_012101d8;
    }
    puVar10 = (uint *)(*(int *)(iVar3 + 0x44) + puVar11[1] * 4);
    uVar12 = (uint)puVar10 ^ DAT_012101dc ^ *puVar10;
    puVar10 = (uint *)(puVar11[1] * 4 + *(int *)(iVar3 + 0x48));
    if (uVar12 != (*puVar10 ^ (uint)puVar10 ^ DAT_012101dc)) {
      FUN_00b170b0(puVar11,0x40);
      iVar3 = DAT_012101d8;
    }
    auStack_1bd[(int)param_3] = uVar12;
    param_3 = (uint *)((int)param_3 + 1);
    puVar11 = puVar11 + 2;
  } while ((int)param_3 < 3);
  cVar2 = (**(code **)(*piVar1 + 0x1bc))();
  if (cVar2 != '\0') {
    local_4e = 1;
    iVar3 = (**(code **)(*piVar1 + 0x2ac))();
    if (iVar3 != 0) {
      piVar7 = (int *)(**(code **)(*piVar1 + 0x2ac))();
      local_4c = (**(code **)(*piVar7 + 0x1d0))();
      iVar3 = (int)local_1d7;
      (**(code **)(*piVar1 + 0x2ac))(iVar3);
      fVar14 = (float10)FUN_00521ff0(iVar3);
      local_181 = (float)fVar14;
      piVar7 = (int *)(**(code **)(*piVar1 + 0x2ac))();
      iVar3 = (**(code **)(*piVar7 + 0x18c))();
      if (iVar3 != 0) {
        piVar7 = (int *)(**(code **)(*piVar1 + 0x2ac))();
        piVar7 = (int *)(**(code **)(*piVar7 + 0x18c))();
        local_4d = (**(code **)(*piVar7 + 0x1d0))();
        piVar7 = (int *)(**(code **)(*piVar1 + 0x2ac))();
        uVar6 = (**(code **)(*piVar7 + 0x18c))(0);
        fVar14 = (float10)FUN_00448c10(uVar6);
        local_1b1 = (float)fVar14;
      }
      iVar3 = (**(code **)(*piVar1 + 0x2ac))();
      if (*(int *)(iVar3 + 0x70c) != 0) {
        if (*(int *)(local_10 + 0x18) == 1) {
          (**(code **)(*piVar1 + 0x2ac))();
          uVar6 = 2;
        }
        else {
          if (*(int *)(local_10 + 0x18) != 0) goto LAB_004ebc36;
          (**(code **)(*piVar1 + 0x2ac))();
          uVar6 = 1;
        }
        fVar14 = (float10)FUN_00455280(uVar6);
        local_5a = (double)fVar14;
      }
    }
  }
LAB_004ebc36:
  param_3 = (uint *)(**(code **)(*piVar1 + 0x1d8))();
  local_1ad = (float)(int)param_3;
  param_3 = (uint *)(**(code **)(*piVar1 + 0x1e8))();
  local_1a9 = (float)(int)param_3;
  param_3 = (uint *)(**(code **)(*piVar1 + 0x1dc))();
  local_1a5 = (float)(int)param_3;
  param_3 = (uint *)(**(code **)(*piVar1 + 0x1ec))();
  local_1a1 = (float)(int)param_3;
  param_3 = (uint *)(**(code **)(*piVar1 + 0x1d4))();
  local_19d = (float)(int)param_3;
  param_3 = (uint *)(**(code **)(*piVar1 + 0x1e4))();
  local_199 = (float)(int)param_3;
  fVar14 = (float10)(**(code **)(*piVar1 + 0x1f8))();
  local_195 = (float)fVar14;
  piVar7 = piVar1 + 0x146;
  if ((piVar1[0x146] ^ DAT_012101dc) - (int)piVar7 != piVar1[0x147]) {
    FUN_00b170b0(piVar7,0x3f);
  }
  iVar3 = piVar1[0x147] * 4;
  puVar10 = (uint *)(*(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3) ^
                     *(int *)(DAT_012101d8 + 0x44) + iVar3 ^ DAT_012101dc);
  puVar11 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
  if (puVar10 != (uint *)((uint)puVar11 ^ DAT_012101dc ^ *puVar11)) {
    FUN_00b170b0(piVar7,0x40);
  }
  param_3 = puVar10;
  if (_DAT_00e9d7a4 <= _DAT_00cc1f58 - (float)puVar10) {
    fVar14 = (float10)FUN_004333b0();
    local_17d = (float)((float10)_DAT_00cc1f58 - fVar14);
  }
  else {
    local_17d = 0.0;
  }
  local_179 = (**(code **)(*piVar1 + 0x1e0))();
  local_175 = (**(code **)(*piVar1 + 0x1f0))();
  iVar3 = (**(code **)(*piVar1 + 0x2a8))();
  if (iVar3 == 0) {
    local_171 = 0.0;
  }
  else {
    piVar7 = (int *)(**(code **)(*piVar1 + 0x2a8))();
    fVar14 = (float10)(**(code **)(*piVar7 + 0x5f8))();
    local_171 = (float)fVar14;
  }
  iVar3 = (**(code **)(*piVar1 + 0x2a4))();
  if (iVar3 == 0) {
    local_16d = 0.0;
  }
  else {
    piVar7 = (int *)(**(code **)(*piVar1 + 0x2a4))();
    fVar14 = (float10)(**(code **)(*piVar7 + 0x500))(piVar1,param_4);
    local_16d = (float)fVar14;
  }
  iVar3 = (**(code **)(*piVar1 + 0x2a4))();
  if (iVar3 == 0) {
    local_169 = 0.0;
  }
  else {
    piVar7 = (int *)(**(code **)(*piVar1 + 0x2a4))();
    (**(code **)(*piVar7 + 0x344))(3);
    fVar14 = (float10)FUN_004333b0();
    local_169 = (float)fVar14;
  }
  piVar7 = param_4;
  if (param_4 != (int *)0x0) {
    (**(code **)(*param_4 + 0x344))(3);
    local_151 = FUN_004b5680();
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    param_3 = (uint *)(iVar3 + 0x310);
    if ((*(uint *)(iVar3 + 0x310) ^ DAT_012101dc) - (int)param_3 != *(int *)(iVar3 + 0x314)) {
      FUN_00b170b0(param_3,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 0x314) * 4;
    puVar11 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3);
    uVar12 = (uint)puVar11 ^ DAT_012101dc ^ *puVar11;
    puVar11 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    if (uVar12 != (*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      FUN_00b170b0(param_3,0x40);
    }
    local_14d = uVar12;
    (**(code **)(*piVar7 + 0x344))(3);
    fVar14 = (float10)FUN_004333b0();
    local_149 = (float)fVar14;
    (**(code **)(*piVar7 + 0x344))(3);
    local_145 = FUN_004b5760();
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    iVar4 = iVar3 + 800;
    if ((*(uint *)(iVar3 + 800) ^ DAT_012101dc) - iVar4 != *(int *)(iVar3 + 0x324)) {
      FUN_00b170b0(iVar4,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 0x324) * 4;
    puVar11 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3);
    param_3 = (uint *)((uint)puVar11 ^ DAT_012101dc ^ *puVar11);
    puVar11 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    if (param_3 != (uint *)(*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      FUN_00b170b0(iVar4,0x40);
    }
    local_141 = (uint)param_3;
    (**(code **)(*piVar7 + 0x344))(3);
    fVar14 = (float10)FUN_004333b0();
    local_13d = (float)fVar14;
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    puVar11 = (uint *)(iVar3 + 0x38);
    param_6 = (undefined4 *)iVar3;
    if ((*puVar11 ^ DAT_012101dc) - (int)puVar11 != *(int *)(iVar3 + 0x3c)) {
      FUN_00b170b0(puVar11,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 0x3c) * 4;
    puVar10 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3);
    param_3 = (uint *)((uint)puVar10 ^ DAT_012101dc ^ *puVar10);
    puVar10 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    if (param_3 != (uint *)(*puVar10 ^ (uint)puVar10 ^ DAT_012101dc)) {
      FUN_00b170b0(puVar11,0x40);
    }
    param_6 = (undefined4 *)((int)param_6 + 0x40);
    FUN_004333b0();
    iVar3 = FUN_00c01544();
    if (iVar3 < -0x5dc) {
      param_3 = (uint *)0xfffffa24;
    }
    else {
      iVar3 = FUN_00402060();
      param_3 = (uint *)(float)iVar3;
      FUN_004333b0();
      param_3 = (uint *)FUN_00c01544();
    }
    local_139 = (float)(int)param_3;
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    puVar11 = (uint *)(iVar3 + 0x58);
    param_6 = (undefined4 *)iVar3;
    if ((*puVar11 ^ DAT_012101dc) - (int)puVar11 != *(int *)(iVar3 + 0x5c)) {
      FUN_00b170b0(puVar11,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 0x5c) * 4;
    puVar10 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3);
    param_3 = (uint *)((uint)puVar10 ^ DAT_012101dc ^ *puVar10);
    puVar10 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    if (param_3 != (uint *)(*puVar10 ^ (uint)puVar10 ^ DAT_012101dc)) {
      FUN_00b170b0(puVar11,0x40);
    }
    param_6 = (undefined4 *)((int)param_6 + 0x60);
    FUN_004333b0();
    iVar3 = FUN_00c01544();
    if (iVar3 < -0x5dc) {
      param_3 = (uint *)0xfffffa24;
    }
    else {
      iVar3 = FUN_00402060();
      param_3 = (uint *)(float)iVar3;
      FUN_004333b0();
      param_3 = (uint *)FUN_00c01544();
    }
    local_135 = (float)(int)param_3;
    fVar14 = (float10)FUN_004333b0();
    if ((float10)_DAT_00e9d7a4 <= (float10)_DAT_00cc1f58 - fVar14) {
      fVar14 = (float10)FUN_004333b0();
      local_131 = (float)((float10)_DAT_00cc1f58 - fVar14);
    }
    else {
      local_131 = 0.0;
    }
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    param_3 = (uint *)(iVar3 + 0x2a0);
    if ((*(uint *)(iVar3 + 0x2a0) ^ DAT_012101dc) - (int)param_3 != *(int *)(iVar3 + 0x2a4)) {
      FUN_00b170b0(param_3,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 0x2a4) * 4;
    puVar11 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    uVar12 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3) ^
             *(int *)(DAT_012101d8 + 0x44) + iVar3 ^ DAT_012101dc;
    if (uVar12 != (*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      FUN_00b170b0(param_3,0x40);
    }
    local_12d = uVar12;
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    iVar4 = iVar3 + 0x2b8;
    if ((*(uint *)(iVar3 + 0x2b8) ^ DAT_012101dc) - iVar4 != *(int *)(iVar3 + 700)) {
      FUN_00b170b0(iVar4,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 700) * 4;
    puVar11 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3);
    param_6 = (undefined4 *)(*puVar11 ^ (uint)puVar11 ^ DAT_012101dc);
    param_3 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    if (param_6 != (undefined4 *)((uint)param_3 ^ DAT_012101dc ^ *param_3)) {
      FUN_00b170b0(iVar4,0x40);
    }
    local_129 = param_6;
    (**(code **)(*piVar7 + 0x344))(3);
    fVar14 = (float10)FUN_004333b0();
    local_11d = (float)fVar14;
    piVar9 = (int *)piVar7[0x8a];
    piVar8 = (int *)piVar7[0x89];
    bVar13 = piVar8 == piVar9;
    if (!bVar13) {
      do {
        if (*piVar8 == 0x12) break;
        piVar8 = piVar8 + 1;
      } while (piVar8 != piVar9);
      bVar13 = piVar8 == piVar9;
    }
    local_119 = !bVar13;
    piVar9 = (int *)piVar7[0x8a];
    piVar8 = (int *)piVar7[0x89];
    bVar13 = piVar8 == piVar9;
    if (!bVar13) {
      do {
        if (*piVar8 == 0x13) break;
        piVar8 = piVar8 + 1;
      } while (piVar8 != piVar9);
      bVar13 = piVar8 == piVar9;
    }
    local_118 = !bVar13;
    iVar3 = FUN_004eb220();
    local_117 = '\x01' - (iVar3 != 0);
    iVar3 = (**(code **)(*piVar7 + 0x428))(9);
    if ((iVar3 != 0) && (piVar7 = (int *)(**(code **)(*piVar7 + 0x428))(9), piVar7 != (int *)0x0)) {
      iVar3 = FUN_008ae0f0(0);
      param_3 = (uint *)(float)(iVar3 % 100);
      (**(code **)(*piVar7 + 0xe4))();
      fVar14 = (float10)FUN_004333b0();
      if ((float10)(float)param_3 < fVar14) {
        iVar3 = (**(code **)(*piVar7 + 0xe4))();
        if (*(int *)(iVar3 + 0x274) == 2) {
          (**(code **)(*piVar7 + 0xe4))();
          local_125 = FUN_00402060();
        }
        else {
          iVar3 = (**(code **)(*piVar7 + 0xe4))();
          if (*(int *)(iVar3 + 0x274) == 3) {
            (**(code **)(*piVar7 + 0xe4))();
            local_121 = FUN_00402060();
          }
        }
      }
    }
    uVar6 = (**(code **)(*local_c + 0x2a4))(0,&PTR_PTR_00f5526c,&PTR_PTR_00f5528c,0);
    piVar7 = (int *)FUN_00c00d0b(uVar6);
    if (piVar7 != (int *)0x0) {
      iVar3 = 0;
      do {
        iVar4 = (**(code **)(*piVar7 + 0x428))(iVar3);
        if (iVar4 != 0) {
          param_3 = (uint *)0x3f800000;
          piVar9 = (int *)(**(code **)(*piVar7 + 0x428))(iVar3);
          (**(code **)(*piVar9 + 0xd8))(piVar1,param_5,1,&param_3);
          auStack_ba[iVar3] = param_3;
          param_3 = (uint *)0x3f800000;
          piVar9 = (int *)(**(code **)(*piVar7 + 0x428))(iVar3);
          (**(code **)(*piVar9 + 0xd8))(piVar1,param_5,0,&param_3);
          auStack_116[iVar3] = param_3;
        }
        iVar3 = iVar3 + 1;
      } while (iVar3 < 0x17);
    }
  }
  cVar2 = FUN_0043abf0(0xffffffff);
  if (cVar2 == '\0') {
    if ((DAT_010bfe60 ^ DAT_012101dc) + 0xfef401a0 != DAT_010bfe64) {
      FUN_00b170b0(&DAT_010bfe60,0x3f);
    }
    puVar11 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + DAT_010bfe64 * 4);
    puVar10 = (uint *)(*(uint *)(*(int *)(DAT_012101d8 + 0x44) + DAT_010bfe64 * 4) ^
                       *(int *)(DAT_012101d8 + 0x44) + DAT_010bfe64 * 4 ^ DAT_012101dc);
    if (puVar10 != (uint *)(*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      puVar15 = &DAT_010bfe60;
LAB_004ec5a5:
      FUN_00b170b0(puVar15,0x40);
    }
  }
  else {
    cVar2 = FUN_0043a5d0();
    if ((cVar2 == '\0') && (cVar2 = FUN_0043a650(), cVar2 == '\0')) {
      fVar14 = (float10)FUN_004333b0();
      goto LAB_004ec5b0;
    }
    if ((DAT_010bfe88 ^ DAT_012101dc) + 0xfef40178 != DAT_010bfe8c) {
      FUN_00b170b0(&DAT_010bfe88,0x3f);
    }
    puVar11 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + DAT_010bfe8c * 4);
    puVar10 = (uint *)(*(uint *)(*(int *)(DAT_012101d8 + 0x44) + DAT_010bfe8c * 4) ^
                       *(int *)(DAT_012101d8 + 0x44) + DAT_010bfe8c * 4 ^ DAT_012101dc);
    if (puVar10 != (uint *)(*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      puVar15 = &DAT_010bfe88;
      goto LAB_004ec5a5;
    }
  }
  fVar14 = (float10)(float)puVar10;
  param_3 = puVar10;
LAB_004ec5b0:
  local_155 = (float)fVar14;
  iVar3 = (**(code **)(*piVar1 + 0x2a4))();
  if (iVar3 == 0) {
    local_191 = 0;
    local_18d = 0;
    local_189 = 0;
    local_185 = 0;
  }
  else {
    piVar7 = (int *)(**(code **)(*piVar1 + 0x2a4))();
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    iVar4 = iVar3 + 0x2c8;
    if ((*(uint *)(iVar3 + 0x2c8) ^ DAT_012101dc) - iVar4 != *(int *)(iVar3 + 0x2cc)) {
      FUN_00b170b0(iVar4,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 0x2cc) * 4;
    puVar11 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    uVar12 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3) ^
             *(int *)(DAT_012101d8 + 0x44) + iVar3 ^ DAT_012101dc;
    if (uVar12 != (*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      FUN_00b170b0(iVar4,0x40);
    }
    local_191 = uVar12;
    piVar7 = (int *)(**(code **)(*piVar1 + 0x2a4))();
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    iVar4 = iVar3 + 0x2d0;
    if ((*(uint *)(iVar3 + 0x2d0) ^ DAT_012101dc) - iVar4 != *(int *)(iVar3 + 0x2d4)) {
      FUN_00b170b0(iVar4,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 0x2d4) * 4;
    puVar11 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    uVar12 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3) ^
             *(int *)(DAT_012101d8 + 0x44) + iVar3 ^ DAT_012101dc;
    if (uVar12 != (*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      FUN_00b170b0(iVar4,0x40);
    }
    local_18d = uVar12;
    piVar7 = (int *)(**(code **)(*piVar1 + 0x2a4))();
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    iVar4 = iVar3 + 0x2d8;
    if ((*(uint *)(iVar3 + 0x2d8) ^ DAT_012101dc) - iVar4 != *(int *)(iVar3 + 0x2dc)) {
      FUN_00b170b0(iVar4,0x3f);
    }
    iVar3 = *(int *)(iVar3 + 0x2dc) * 4;
    puVar11 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
    uVar12 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3) ^
             *(int *)(DAT_012101d8 + 0x44) + iVar3 ^ DAT_012101dc;
    if (uVar12 != (*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      FUN_00b170b0(iVar4,0x40);
    }
    local_189 = uVar12;
    piVar7 = (int *)(**(code **)(*piVar1 + 0x2a4))();
    iVar3 = (**(code **)(*piVar7 + 0x344))(3);
    iVar4 = iVar3 + 0x2e0;
    if ((*(uint *)(iVar3 + 0x2e0) ^ DAT_012101dc) - iVar4 != *(int *)(iVar3 + 0x2e4)) {
      FUN_00b170b0(iVar4,0x3f);
    }
    param_3 = (uint *)(*(int *)(iVar3 + 0x2e4) * 4);
    puVar11 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + (int)param_3);
    param_5 = *puVar11 ^ (uint)puVar11 ^ DAT_012101dc;
    puVar11 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + (int)param_3);
    local_185 = param_5;
    if (param_5 != (*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      FUN_00b170b0(iVar4,0x40);
    }
  }
  if ((piVar1[0x13d] ^ DAT_012101dc) - (int)(piVar1 + 0x13d) != piVar1[0x13e]) {
    FUN_00b170b0(piVar1 + 0x13d,0x3f);
  }
  puVar11 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + piVar1[0x13e] * 4);
  uVar12 = *puVar11 ^ DAT_012101dc ^ (uint)puVar11;
  puVar11 = (uint *)(piVar1[0x13e] * 4 + *(int *)(DAT_012101d8 + 0x48));
  if (uVar12 != (*puVar11 ^ DAT_012101dc ^ (uint)puVar11)) {
    FUN_00b170b0(piVar1 + 0x13d,0x40);
  }
  iVar3 = DAT_01002848;
  param_3 = (uint *)(DAT_01002848 + 0x1040);
  local_5e = uVar12;
  if ((*(uint *)(DAT_01002848 + 0x1040) ^ DAT_012101dc) - (int)param_3 !=
      *(int *)(DAT_01002848 + 0x1044)) {
    FUN_00b170b0(param_3,0x3f);
  }
  iVar3 = *(int *)(iVar3 + 0x1044) * 4;
  puVar11 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
  uVar12 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3) ^ *(int *)(DAT_012101d8 + 0x44) + iVar3
           ^ DAT_012101dc;
  if (uVar12 != ((uint)puVar11 ^ DAT_012101dc ^ *puVar11)) {
    FUN_00b170b0(param_3,0x40);
  }
  local_52 = (undefined1)uVar12;
  local_20 = FUN_0043abf0(0xffffffff);
  local_51 = (**(code **)(*piVar1 + 0x1d0))();
  uVar6 = (**(code **)(*piVar1 + 0x2a4))(0,&PTR_PTR_00f5526c,&PTR_PTR_00f5528c,0);
  piVar7 = (int *)FUN_00c00d0b(uVar6);
  if (piVar7 == (int *)0x0) {
    local_50 = 1;
  }
  else {
    iVar3 = (**(code **)(*piVar7 + 0x428))(9);
    if (iVar3 != 0) {
      (**(code **)(*piVar7 + 0x428))(9);
      local_50 = FUN_004564f0();
    }
  }
  iVar3 = (**(code **)(*local_c + 0x2fc))();
  if ((iVar3 < 0x32) && (iVar3 = (**(code **)(*piVar1 + 0x2a4))(), iVar3 != local_c[0x116])) {
    local_31 = local_31 + '\x01';
    local_36 = 1;
    if ('\x03' < local_31) {
      local_31 = '\x04';
    }
  }
  else {
    local_35 = 0;
    local_31 = '\x01';
  }
  if (param_4 != (int *)0x0) {
    local_1b = (**(code **)(*param_4 + 0x410))(6);
  }
  cVar2 = (**(code **)(*piVar1 + 0x2c))(0x21);
  if (cVar2 != '\0') {
    local_1a = piVar1[0x81];
  }
  uVar6 = FUN_008b8650(&local_1dc,local_c,piVar1);
  *(bool *)param_1 = local_37 != '\0';
  *param_2 = local_35;
  return uVar6;
}

