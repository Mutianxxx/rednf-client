
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_004b28d0(int *param_1,int *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int *in_ECX;
  int *piVar6;
  uint uVar7;
  undefined4 *unaff_FS_OFFSET;
  bool bVar8;
  float10 fVar9;
  undefined4 uVar10;
  undefined1 *puVar11;
  undefined4 uVar12;
  undefined1 local_5c [4];
  void *local_58;
  undefined1 local_4c [4];
  void *local_48;
  int *local_44;
  int local_40;
  int local_3c;
  float local_38;
  int *local_34;
  int local_30;
  uint local_2c;
  int local_28;
  uint local_24;
  float local_20;
  int local_1c;
  int local_18;
  char local_11;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c57589;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_004af440();
  piVar6 = in_ECX + 0x53b;
  local_28 = 0x17;
  do {
    if ((int *)*piVar6 != (int *)0x0) {
      (**(code **)(*(int *)*piVar6 + 0xbc))(param_1,param_2,param_3,1);
    }
    piVar6 = piVar6 + 1;
    local_28 = local_28 + -1;
  } while (local_28 != 0);
  iVar2 = (**(code **)(*param_1 + 0x19c))();
  local_28 = iVar2;
  if ((*(uint *)(iVar2 + 0x1c) ^ DAT_012101dc) - (iVar2 + 0x1c) != *(int *)(iVar2 + 0x20)) {
    FUN_00b170b0(iVar2 + 0x1c,0x3f);
  }
  iVar2 = *(int *)(iVar2 + 0x20) * 4;
  piVar6 = (int *)(iVar2 + *(int *)(DAT_012101d8 + 0x44) ^
                   *(uint *)(iVar2 + *(int *)(DAT_012101d8 + 0x44)) ^ DAT_012101dc);
  local_34 = piVar6;
  if (piVar6 != (int *)(iVar2 + *(int *)(DAT_012101d8 + 0x48) ^
                        *(uint *)(iVar2 + *(int *)(DAT_012101d8 + 0x48)) ^ DAT_012101dc)) {
    FUN_00b170b0(local_28 + 0x1c,0x40);
  }
  if (((piVar6 != (int *)0x0) || (fVar9 = (float10)FUN_004333b0(), (float10)_DAT_00e9d7a4 < fVar9))
     || (iVar2 = FUN_00402060(), 0 < iVar2)) {
    if (in_ECX + 0x67a != param_2) {
      iVar2 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(in_ECX[0x67b] * 4 + iVar2) =
           in_ECX[0x67b] * 4 + iVar2 ^
           param_2[1] * 4 + iVar2 ^ *(uint *)(param_2[1] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
      iVar2 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(in_ECX[0x67b] * 4 + iVar2) =
           in_ECX[0x67b] * 4 + iVar2 ^
           param_2[1] * 4 + iVar2 ^ *(uint *)(param_2[1] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
    }
    if (in_ECX + 0x67c != param_2 + 2) {
      iVar2 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(in_ECX[0x67d] * 4 + iVar2) =
           in_ECX[0x67d] * 4 + iVar2 ^
           param_2[3] * 4 + iVar2 ^ *(uint *)(param_2[3] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
      iVar2 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(in_ECX[0x67d] * 4 + iVar2) =
           in_ECX[0x67d] * 4 + iVar2 ^
           param_2[3] * 4 + iVar2 ^ *(uint *)(param_2[3] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
    }
    if (in_ECX + 0x67e != param_2 + 4) {
      iVar2 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(in_ECX[0x67f] * 4 + iVar2) =
           in_ECX[0x67f] * 4 + iVar2 ^
           param_2[5] * 4 + iVar2 ^ *(uint *)(param_2[5] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
      iVar2 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(in_ECX[0x67f] * 4 + iVar2) =
           in_ECX[0x67f] * 4 + iVar2 ^
           param_2[5] * 4 + iVar2 ^ *(uint *)(param_2[5] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
    }
    if (in_ECX + 0x680 != param_2 + 6) {
      iVar2 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(in_ECX[0x681] * 4 + iVar2) =
           in_ECX[0x681] * 4 + iVar2 ^
           param_2[7] * 4 + iVar2 ^ *(uint *)(param_2[7] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
      iVar2 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(in_ECX[0x681] * 4 + iVar2) =
           in_ECX[0x681] * 4 + iVar2 ^
           param_2[7] * 4 + iVar2 ^ *(uint *)(param_2[7] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
    }
    if (in_ECX + 0x682 != param_2 + 8) {
      iVar2 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(in_ECX[0x683] * 4 + iVar2) =
           in_ECX[0x683] * 4 + iVar2 ^
           param_2[9] * 4 + iVar2 ^ *(uint *)(param_2[9] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
      iVar2 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(in_ECX[0x683] * 4 + iVar2) =
           in_ECX[0x683] * 4 + iVar2 ^
           param_2[9] * 4 + iVar2 ^ *(uint *)(param_2[9] * 4 + iVar2) ^ DAT_012101dc ^ DAT_012101dc;
    }
    local_34 = in_ECX + 0x684;
    if (local_34 != param_2 + 10) {
      iVar2 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(in_ECX[0x685] * 4 + iVar2) =
           in_ECX[0x685] * 4 + iVar2 ^
           param_2[0xb] * 4 + iVar2 ^ *(uint *)(param_2[0xb] * 4 + iVar2) ^ DAT_012101dc ^
           DAT_012101dc;
      iVar2 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(in_ECX[0x685] * 4 + iVar2) =
           in_ECX[0x685] * 4 + iVar2 ^
           param_2[0xb] * 4 + iVar2 ^ *(uint *)(param_2[0xb] * 4 + iVar2) ^ DAT_012101dc ^
           DAT_012101dc;
    }
  }
  FUN_004eb3b0(param_1,param_2,param_3);
  local_18 = 0;
  local_11 = FUN_004e9160();
  if ((char)param_3 != '\0') {
    (**(code **)(*in_ECX + 0x284))(param_2);
    goto LAB_004b3640;
  }
  local_1c = (**(code **)(*param_1 + 0x19c))();
  cVar1 = FUN_004e8b10(local_1c);
  if (cVar1 != '\0') {
    iVar2 = (**(code **)(*in_ECX + 0xe4))();
    local_3c = FUN_00403c50(0x1e8);
    local_8 = 0;
    if (local_3c == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_004936d0(u_Common_HitEffect_Animation_weakn_00cd0d28,1);
    }
    local_8 = 0xffffffff;
    (**(code **)(*in_ECX + 0xf8))(100,uVar3,0,-iVar2,1,0,1,1,0,1);
    local_3c = FUN_00403c50(0x1e8);
    local_8 = 1;
    if (local_3c == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = FUN_004936d0(u_Common_HitEffect_Animation_weakn_00cd0cc8,1);
    }
    local_8 = 0xffffffff;
    (**(code **)(*in_ECX + 0xf8))(99,uVar3,0,-iVar2,1,0,1,1,0,1);
  }
  piVar6 = in_ECX + 0x53b;
  local_28 = 0x17;
  do {
    if ((int *)*piVar6 != (int *)0x0) {
      (**(code **)(*(int *)*piVar6 + 0x198))(1,param_1,0);
    }
    piVar6 = piVar6 + 1;
    local_28 = local_28 + -1;
  } while (local_28 != 0);
  cVar1 = FUN_0049c090();
  if ((cVar1 == '\0') || (iVar2 = (**(code **)(*in_ECX + 0xf4))(), iVar2 == 0)) {
    local_18 = -1;
    goto LAB_004b3640;
  }
  piVar6 = in_ECX + 0x12f;
  if ((in_ECX[0x12f] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x130]) {
    FUN_00b170b0(piVar6,0x3f);
  }
  iVar2 = in_ECX[0x130] * 4;
  uVar7 = iVar2 + *(int *)(DAT_012101d8 + 0x44) ^ *(uint *)(iVar2 + *(int *)(DAT_012101d8 + 0x44)) ^
          DAT_012101dc;
  if (uVar7 != (iVar2 + *(int *)(DAT_012101d8 + 0x48) ^
                *(uint *)(iVar2 + *(int *)(DAT_012101d8 + 0x48)) ^ DAT_012101dc)) {
    FUN_00b170b0(piVar6,0x40);
  }
  if (uVar7 == 0) {
    iVar2 = FUN_00499fe0();
  }
  else {
    iVar2 = FUN_00402060();
  }
  if ((iVar2 == 0) || (iVar2 == 1)) {
    (**(code **)(*in_ECX + 0x578))(param_1);
    local_2c = local_2c & 0xffffff00;
    local_24 = 100;
    local_20 = 0.0;
    local_3c = (**(code **)(*in_ECX + 0x310))(&local_24,param_1);
    local_18 = (**(code **)(*in_ECX + 0x2f8))(&local_2c,&local_20,local_24,param_1,param_2,0);
    cVar1 = FUN_004e8b10(local_1c);
    if (cVar1 != '\0') {
      iVar2 = (**(code **)(*in_ECX + 0xe4))();
      local_38 = (float)FUN_00403c50(0x1e8);
      local_8 = 2;
      if (local_38 == 0.0) {
        uVar3 = 0;
      }
      else {
        uVar3 = FUN_004936d0(u_Common_HitEffect_Animation_weakn_00cd0d28,1);
      }
      local_8 = 0xffffffff;
      (**(code **)(*in_ECX + 0xf8))(100,uVar3,0,-iVar2,1,0,1,1,0,1);
      local_38 = (float)FUN_00403c50(0x1e8);
      local_8 = 3;
      if (local_38 == 0.0) {
        uVar3 = 0;
      }
      else {
        uVar3 = FUN_004936d0(u_Common_HitEffect_Animation_weakn_00cd0cc8,1);
      }
      local_8 = 0xffffffff;
      (**(code **)(*in_ECX + 0xf8))(99,uVar3,0,-iVar2,1,0,1,1,0,1);
      fVar9 = (float10)FUN_004333b0();
      local_38 = (float)(fVar9 * (float10)_DAT_00cd0910);
      local_30 = (**(code **)(*in_ECX + 0x234))();
      iVar2 = FUN_00c01544();
      iVar4 = FUN_00c00d0b();
      if (iVar4 != 0) {
        iVar5 = *(int *)(iVar4 + 0x19e4);
        if (iVar5 == 1) {
          iVar2 = iVar2 / 3;
        }
        else if (iVar5 == 2) {
          iVar4 = 0x55555556;
LAB_004b3026:
          iVar2 = (int)((ulonglong)((longlong)iVar4 * (longlong)iVar2) >> 0x20);
          iVar2 = iVar2 - (iVar2 >> 0x1f);
        }
        else if (iVar5 == 3) {
          iVar2 = iVar2 / 6;
        }
        else if (*(char *)(iVar4 + 0x1e1c) != '\0') {
          iVar4 = 0x2aaaaaab;
          goto LAB_004b3026;
        }
      }
      local_18 = local_18 + iVar2;
    }
    if (in_ECX[0x4b7] != 0) {
      FUN_004b6c90(&local_18,param_1);
    }
    iVar2 = (**(code **)(*in_ECX + 0x234))();
    if (local_18 < iVar2) {
      local_30 = local_18;
    }
    else {
      local_30 = (**(code **)(*in_ECX + 0x234))();
    }
    iVar2 = (**(code **)(*param_1 + 0x19c))();
    if (*(int *)(iVar2 + 0x178) == 2) {
      local_3c = FUN_00403c50(0x100);
      local_8 = 4;
      if (local_3c == 0) {
LAB_004b30ba:
        piVar6 = (int *)0x0;
      }
      else {
        local_38 = (float)-local_18;
        piVar6 = (int *)FUN_00469bb0((float)(int)local_38,1000,0,1);
      }
    }
    else {
      iVar2 = (**(code **)(*param_1 + 0x19c))();
      if (*(int *)(iVar2 + 0x178) != 4) {
        iVar2 = *in_ECX;
        iVar4 = FUN_00402060(0,param_1);
        (**(code **)(iVar2 + 1000))(iVar4 - local_18);
        *(uint *)(in_ECX[0x572] * 4 + *(int *)(DAT_012101d8 + 0x44)) =
             ~(in_ECX[0x572] * 4 + *(int *)(DAT_012101d8 + 0x44)) ^ DAT_012101dc;
        *(uint *)(in_ECX[0x572] * 4 + *(int *)(DAT_012101d8 + 0x48)) =
             ~(in_ECX[0x572] * 4 + *(int *)(DAT_012101d8 + 0x48)) ^ DAT_012101dc;
        if ((((local_18 != 0) || (iVar2 = FUN_00402060(), iVar2 != 0)) ||
            (fVar9 = (float10)FUN_004333b0(), (float10)_DAT_00e9d7a4 < fVar9)) ||
           (iVar2 = FUN_00402060(), 0 < iVar2)) {
          FUN_004ad000(param_1);
        }
        goto LAB_004b31da;
      }
      local_3c = FUN_00403c50(0xa4);
      local_8 = 5;
      if (local_3c == 0) goto LAB_004b30ba;
      piVar6 = (int *)FUN_00469db0(-local_18,1000,1);
    }
    local_8 = 0xffffffff;
    (**(code **)(*piVar6 + 0x48))();
  }
LAB_004b31da:
  local_34 = (int *)0x0;
  local_28 = 0;
  iVar2 = (**(code **)(*in_ECX + 0x3e0))(&local_34,&local_28,param_1);
  if ((iVar2 != -1) && ((char)in_ECX[0x127] != '\0')) {
    iVar4 = (**(code **)(*param_1 + 0x19c))();
    if ((*(int *)(iVar4 + 0x178) == 2) && (iVar4 = FUN_008ae0f0(0), iVar4 % 100 < 0x14)) {
      (**(code **)(*in_ECX + 0x4dc))();
    }
    else {
      (**(code **)(*in_ECX + 0x4dc))();
    }
  }
  if (iVar2 == 3) {
    iVar2 = (**(code **)(*in_ECX + 0x374))(1);
    if ((iVar2 == 0) && (iVar2 = (**(code **)(*in_ECX + 0x39c))(1), iVar2 != 0)) {
      local_24 = 0;
    }
    else {
      iVar2 = (**(code **)(*in_ECX + 0x374))(0);
      if ((iVar2 == 0) && (iVar2 = (**(code **)(*in_ECX + 0x39c))(0), iVar2 != 0)) {
        local_24 = 1;
      }
      else {
        iVar2 = FUN_00402060();
        if (iVar2 == 3) {
          local_24 = 1 - in_ECX[0x5af];
        }
        else {
          local_24 = FUN_008ae0f0(0);
          local_24 = local_24 & 0x80000001;
          if ((int)local_24 < 0) {
            local_24 = (local_24 - 1 | 0xfffffffe) + 1;
          }
        }
      }
    }
    iVar2 = local_1c;
    fVar9 = (float10)FUN_004333b0();
    local_20 = (float)fVar9;
    if (ABS(fVar9 - (float10)_DAT_00cab8f0) <= ABS((float10)local_20) * (float10)_DAT_00cab8e8) {
      local_20 = 1.0;
    }
    if (*(int *)(iVar2 + 0x18) == 1) {
      local_20 = local_20 * _DAT_00ccb9dc;
    }
    if ((in_ECX[0x128] != 4) && (in_ECX[0x128] != 5)) {
      local_48 = (void *)0x0;
      local_44 = (int *)0x0;
      local_40 = 0;
      local_8 = 6;
      local_3c = (**(code **)(*param_1 + 0x31c))();
      FUN_00407120(&local_3c);
      FUN_004333b0();
      local_3c = FUN_00c01544();
      FUN_00407120(&local_3c);
      FUN_00407120(&local_24);
      iVar2 = (**(code **)(*param_1 + 0x19c))();
      local_3c = *(int *)(iVar2 + 0x178);
      FUN_00407120(&local_3c);
      iVar2 = FUN_00402060();
      if (iVar2 != 0) {
        local_3c = FUN_00402060();
        FUN_00407120(&local_3c);
      }
      (**(code **)(*in_ECX + 0x28c))(3,local_4c,3,0,0);
      local_8 = 0xffffffff;
      if (local_48 != (void *)0x0) {
        _free(local_48);
      }
    }
  }
  else if (iVar2 == 4) {
    local_30 = 1;
    iVar2 = FUN_00402060();
    if ((iVar2 != 0) && (local_28 == 0)) {
      local_30 = 2;
    }
    local_48 = (void *)0x0;
    local_44 = (int *)0x0;
    local_40 = 0;
    local_8 = 7;
    local_3c = (**(code **)(*param_1 + 0x31c))();
    if ((local_48 == (void *)0x0) ||
       ((uint)(local_40 - (int)local_48 >> 2) <= (uint)((int)local_44 - (int)local_48 >> 2))) {
      FUN_00405f60(local_44,1,&local_3c);
    }
    else {
      *local_44 = local_3c;
      local_44 = local_44 + 1;
    }
    if ((local_48 == (void *)0x0) ||
       ((uint)(local_40 - (int)local_48 >> 2) <= (uint)((int)local_44 - (int)local_48 >> 2))) {
      FUN_00405f60(local_44,1,&local_28);
    }
    else {
      *local_44 = local_28;
      local_44 = local_44 + 1;
    }
    local_3c = local_30;
    if ((local_48 == (void *)0x0) ||
       ((uint)(local_40 - (int)local_48 >> 2) <= (uint)((int)local_44 - (int)local_48 >> 2))) {
      FUN_00405f60(local_44,1,&local_3c);
    }
    else {
      *local_44 = local_30;
      local_44 = local_44 + 1;
    }
    local_3c = FUN_00402060();
    if ((local_48 == (void *)0x0) ||
       ((uint)(local_40 - (int)local_48 >> 2) <= (uint)((int)local_44 - (int)local_48 >> 2))) {
      FUN_00405f60(local_44,1,&local_3c);
    }
    else {
      *local_44 = local_3c;
      local_44 = local_44 + 1;
    }
    bVar8 = local_11 != '\0';
    local_3c = FUN_00402060();
    local_3c = local_3c + (-(uint)bVar8 & 0x32);
    if ((local_48 == (void *)0x0) ||
       ((uint)(local_40 - (int)local_48 >> 2) <= (uint)((int)local_44 - (int)local_48 >> 2))) {
      FUN_00405f60(local_44,1,&local_3c);
    }
    else {
      *local_44 = local_3c;
      local_44 = local_44 + 1;
    }
    (**(code **)(*in_ECX + 0x28c))(4,local_4c,3,0,0);
    local_8 = 0xffffffff;
    if (local_48 != (void *)0x0) {
      _free(local_48);
    }
  }
  else if (iVar2 == 5) {
    local_48 = (void *)0x0;
    local_44 = (int *)0x0;
    local_40 = 0;
    local_8 = 8;
    FUN_00407120(&local_34);
    (**(code **)(*in_ECX + 0x28c))(5,local_4c,3,0,0);
    local_8 = 0xffffffff;
    if (local_48 != (void *)0x0) {
      _free(local_48);
    }
  }
LAB_004b3640:
  iVar2 = 0;
  piVar6 = in_ECX + 0x4a5;
  do {
    cVar1 = (**(code **)(*in_ECX + 0x410))(iVar2);
    if (cVar1 != '\0') {
      (**(code **)(*(int *)*piVar6 + 0x48))(param_1,param_2,param_3);
    }
    iVar2 = iVar2 + 1;
    piVar6 = piVar6 + 1;
  } while (iVar2 < 0x12);
  if ((0 < local_18) && (DAT_0104f1d4 == in_ECX)) {
    FUN_0053be70(3,local_18);
    iVar2 = local_18;
    cVar1 = FUN_0043a830();
    if (cVar1 != '\0') {
      DAT_01004bfc = DAT_01004bfc + iVar2;
    }
  }
  cVar1 = FUN_004ad4a0();
  if (cVar1 != '\0') {
    piVar6 = in_ECX + 0x655;
    if ((in_ECX[0x655] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x656]) {
      FUN_00b170b0(piVar6,0x3f);
    }
    iVar2 = in_ECX[0x656] * 4;
    uVar7 = *(int *)(DAT_012101d8 + 0x44) + iVar2 ^ *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar2)
            ^ DAT_012101dc;
    if (uVar7 != (*(int *)(DAT_012101d8 + 0x48) + iVar2 ^
                  *(uint *)(*(int *)(DAT_012101d8 + 0x48) + iVar2) ^ DAT_012101dc)) {
      FUN_00b170b0(piVar6,0x40);
    }
    if (uVar7 == 0) {
      if (in_ECX[0x661] == 0) {
        iVar2 = FUN_00403c50(0x1e8);
        local_8 = 9;
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = FUN_004936d0(u_Common_CommonEffect_Animation_Su_00cd0c60,1);
        }
        in_ECX[0x661] = iVar2;
        local_8 = 0xffffffff;
        iVar4 = 0;
        if (*(int *)(iVar2 + 0x98) != 0) {
          iVar4 = (*(int *)(iVar2 + 0x9c) - *(int *)(iVar2 + 0x98)) / 0x7c;
        }
        FUN_00a27870(iVar4 + -1);
        iVar2 = FUN_00403c50(0x1b4);
        local_8 = 10;
        if (iVar2 == 0) {
          piVar6 = (int *)0x0;
        }
        else {
          piVar6 = (int *)FUN_00453320(u_Common_CommonEffect_Particle_sup_00cd0be8,in_ECX);
        }
        in_ECX[0x662] = (int)piVar6;
        local_8 = 0xffffffff;
        (**(code **)(*piVar6 + 0x70))();
      }
      *(uint *)(in_ECX[0x656] * 4 + *(int *)(DAT_012101d8 + 0x44)) =
           *(int *)(DAT_012101d8 + 0x44) + in_ECX[0x656] * 4 ^ DAT_012101dc ^ 1;
      *(uint *)(in_ECX[0x656] * 4 + *(int *)(DAT_012101d8 + 0x48)) =
           in_ECX[0x656] * 4 + *(int *)(DAT_012101d8 + 0x48) ^ DAT_012101dc ^ 1;
      *(uint *)(in_ECX[0x658] * 4 + *(int *)(DAT_012101d8 + 0x44)) =
           in_ECX[0x658] * 4 + *(int *)(DAT_012101d8 + 0x44) ^ DAT_012101dc;
      *(uint *)(in_ECX[0x658] * 4 + *(int *)(DAT_012101d8 + 0x48)) =
           in_ECX[0x658] * 4 + *(int *)(DAT_012101d8 + 0x48) ^ DAT_012101dc;
      *(uint *)(in_ECX[0x65a] * 4 + *(int *)(DAT_012101d8 + 0x44)) =
           in_ECX[0x65a] * 4 + *(int *)(DAT_012101d8 + 0x44) ^ DAT_012101dc;
      *(uint *)(in_ECX[0x65a] * 4 + *(int *)(DAT_012101d8 + 0x48)) =
           in_ECX[0x65a] * 4 + *(int *)(DAT_012101d8 + 0x48) ^ DAT_012101dc;
      FUN_00b06f60(600,0);
      *(undefined1 *)((int)in_ECX + 0x193d) = 5;
      FUN_00a27360();
      (**(code **)(*(int *)in_ECX[0x662] + 0xc))(0);
      iVar2 = *(int *)in_ECX[0x662];
      iVar4 = (**(code **)(*in_ECX + 0xe4))();
      iVar5 = (**(code **)(*in_ECX + 0x9c))();
      uVar3 = (**(code **)(*in_ECX + 0x98))(iVar4 / 2 + iVar5);
      uVar3 = (**(code **)(*in_ECX + 0x94))(uVar3);
      (**(code **)(iVar2 + 0x28))(uVar3);
      (**(code **)(*(int *)in_ECX[0x662] + 0x5c))(local_5c);
      uVar12 = 0;
      puVar11 = local_5c;
      uVar10 = 0;
      uVar3 = 2;
      local_8 = 0xb;
      (**(code **)(*in_ECX + 0x5c))();
      FUN_0050e060(in_ECX,uVar3,uVar10,puVar11,uVar12);
      if (local_58 != (void *)0x0) {
        _free(local_58);
      }
    }
  }
  *unaff_FS_OFFSET = local_10;
  return local_18;
}

