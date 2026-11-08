
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_004f8a30(int *param_1,int param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  int *piVar6;
  DWORD DVar7;
  int iVar8;
  undefined4 uVar9;
  int *in_ECX;
  int iVar10;
  uint uVar11;
  undefined4 *unaff_FS_OFFSET;
  float10 fVar12;
  undefined1 local_94 [104];
  undefined1 local_2c [4];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c;
  uint local_18;
  uint *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c59c1a;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if ((in_ECX[0x679] == 3) || (in_ECX[0x679] == 8)) {
    (**(code **)(*in_ECX + 0x5c8))();
  }
  iVar10 = 0;
  for (local_18 = 0;
      (in_ECX[0x897] != 0 && (local_18 < (uint)((in_ECX[0x898] - in_ECX[0x897]) / 0x14)));
      local_18 = local_18 + 1) {
    iVar3 = (**(code **)(*param_1 + 0x2a4))();
    if (((iVar3 != 0) &&
        (((iVar3 = (**(code **)(*in_ECX + 0x9c))(), iVar3 == 0 &&
          (iVar3 = FUN_00402060(), iVar3 != 4)) && (iVar3 = FUN_00402060(), iVar3 != 9)))) &&
       ((char)param_3 == '\0')) {
      iVar3 = FUN_00402060();
      if (iVar3 == 0) {
        iVar3 = FUN_00499fe0();
      }
      else {
        iVar3 = FUN_00402060();
      }
      if (iVar3 == 0) {
        (**(code **)(*param_1 + 0x19c))();
        iVar3 = (**(code **)(*param_1 + 0x19c))();
        if (((*(int *)(iVar3 + 0xec) != 0) && (cVar2 = FUN_0049c090(), cVar2 != '\0')) &&
           ((*(char *)(iVar10 + 0xc + in_ECX[0x897]) != '\0' &&
            (*(char *)(iVar10 + 0xd + in_ECX[0x897]) != '\0')))) {
          cVar2 = (**(code **)(*param_1 + 0x1b4))();
          if ((((cVar2 == '\0') || (*(int *)(iVar10 + 8 + in_ECX[0x897]) != 1)) &&
              ((cVar2 = (**(code **)(*param_1 + 0x1b4))(), cVar2 != '\0' ||
               (*(int *)(iVar10 + 8 + in_ECX[0x897]) != 0)))) &&
             (*(int *)(iVar10 + 8 + in_ECX[0x897]) != 2)) {
            param_3 = 0;
            goto LAB_004f9ac0;
          }
          iVar3 = FUN_008ae0f0(0);
          if (iVar3 % 100 < *(int *)(iVar10 + in_ECX[0x897])) {
            local_28 = 0;
            local_24 = 0;
            local_20 = 0;
            local_8 = 0;
            FUN_00407120(in_ECX[0x897] + local_18 * 0x14 + 4);
            (**(code **)(*in_ECX + 0x28c))(8,local_2c,0,0,0);
            (**(code **)(*in_ECX + 0x290))();
            FUN_00644d50();
            *unaff_FS_OFFSET = local_10;
            return 0;
          }
        }
      }
    }
    iVar10 = iVar10 + 0x14;
  }
  if ((in_ECX[0x8a8] != 0) && (in_ECX[0x8a9] - in_ECX[0x8a8] >> 4 != 0)) {
    for (local_14 = (uint *)0x0;
        (in_ECX[0x8a8] != 0 && (local_14 < (uint *)(in_ECX[0x8a9] - in_ECX[0x8a8] >> 4)));
        local_14 = (uint *)((int)local_14 + 1)) {
      local_1c = (int)local_14 << 4;
      local_18 = 0;
      while( true ) {
        iVar10 = *(int *)(local_1c + in_ECX[0x8a8] + 4);
        if ((iVar10 == 0) ||
           ((uint)(*(int *)(local_1c + in_ECX[0x8a8] + 8) - iVar10 >> 2) <= local_18)) break;
        iVar3 = local_18 * 4;
        if ((*(char *)(*(int *)(iVar10 + iVar3) + 0x138) != '\0') &&
           (iVar10 = (**(code **)(*in_ECX + 0xf4))(), iVar10 != 0)) {
          iVar10 = (**(code **)(*in_ECX + 0xf4))();
          if (*(int *)(iVar10 + 0x124) == -1) {
            FUN_00a27f60();
          }
          if (iVar10 != -0xa8) {
            iVar10 = (**(code **)(*in_ECX + 0xf4))();
            if (*(int *)(iVar10 + 0x124) == -1) {
              FUN_00a27f60();
            }
            if ((*(int *)(iVar10 + 0xdc) - (iVar10 + 0xdc) ^ DAT_010d3ef8) != 1) {
              (**(code **)(*in_ECX + 0xfc))
                        (*(undefined4 *)(*(int *)(in_ECX[0x8a8] + local_1c + 4) + iVar3));
            }
          }
        }
        local_18 = local_18 + 1;
      }
    }
  }
  cVar2 = (**(code **)(*param_1 + 0x1b4))();
  if (((cVar2 != '\0') && (cVar2 = (**(code **)(*in_ECX + 0x6c0))(param_1), cVar2 != '\0')) &&
     (cVar2 = FUN_0049c090(), cVar2 != '\0')) {
    (**(code **)(*param_1 + 0x164))(1);
    iVar10 = (**(code **)(*param_1 + 0x48))();
    piVar6 = *(int **)(iVar10 + 0x78);
    cVar2 = FUN_004e8800();
    iVar10 = param_1[0x81];
    (**(code **)(*piVar6 + 0x14))(local_94);
    uVar9 = (**(code **)(*piVar6 + 0x2c))();
    iVar3 = (**(code **)(*param_1 + 0x33c))(local_94,uVar9,0,0,0,0,0);
    FUN_004ea100((uint)in_ECX & ~-(uint)(cVar2 != '\0'),iVar10,*(undefined4 *)(iVar3 + 0x20));
LAB_004f8e27:
    *unaff_FS_OFFSET = local_10;
    return 0;
  }
  puVar4 = (uint *)(**(code **)(*param_1 + 0x19c))();
  puVar5 = puVar4 + 7;
  local_14 = puVar4;
  if ((*puVar5 ^ DAT_012101dc) - (int)puVar5 != puVar4[8]) {
    FUN_00b170b0(puVar5,0x3f);
  }
  iVar10 = puVar4[8] * 4;
  uVar11 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar10) ^
           *(int *)(DAT_012101d8 + 0x44) + iVar10 ^ DAT_012101dc;
  puVar4 = (uint *)(iVar10 + *(int *)(DAT_012101d8 + 0x48));
  if (uVar11 != (*puVar4 ^ (uint)puVar4 ^ DAT_012101dc)) {
    FUN_00b170b0(puVar5,0x40);
  }
  puVar5 = local_14;
  if ((uVar11 != 0) || (fVar12 = (float10)FUN_004333b0(), (float10)_DAT_00e9d7a4 < fVar12)) {
LAB_004f9025:
    if ((int)in_ECX + 0x1e1e != param_2) {
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)((int)in_ECX + 0x1e22) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_2 + 4) * 4);
      *puVar5 = (uint)puVar4 ^ (uint)puVar5 ^ *puVar4;
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)((int)in_ECX + 0x1e22) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_2 + 4) * 4);
      *puVar5 = (uint)puVar4 ^ (uint)puVar5 ^ *puVar4;
    }
    if ((int)in_ECX + 0x1e26 != param_2 + 8) {
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_2 + 0xc) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)((int)in_ECX + 0x1e2a) * 4);
      *puVar4 = *puVar5 ^ (uint)puVar5 ^ (uint)puVar4;
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_2 + 0xc) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)((int)in_ECX + 0x1e2a) * 4);
      *puVar4 = *puVar5 ^ (uint)puVar4 ^ (uint)puVar5;
    }
    if ((int)in_ECX + 0x1e2e != param_2 + 0x10) {
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_2 + 0x14) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)((int)in_ECX + 0x1e32) * 4);
      *puVar4 = *puVar5 ^ (uint)puVar4 ^ (uint)puVar5;
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_2 + 0x14) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)((int)in_ECX + 0x1e32) * 4);
      *puVar4 = *puVar5 ^ (uint)puVar4 ^ (uint)puVar5;
    }
    if ((int)in_ECX + 0x1e36 != param_2 + 0x18) {
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_2 + 0x1c) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)((int)in_ECX + 0x1e3a) * 4);
      *puVar4 = *puVar5 ^ (uint)puVar4 ^ (uint)puVar5;
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_2 + 0x1c) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)((int)in_ECX + 0x1e3a) * 4);
      *puVar4 = *puVar5 ^ (uint)puVar4 ^ (uint)puVar5;
    }
    if ((int)in_ECX + 0x1e3e != param_2 + 0x20) {
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_2 + 0x24) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)((int)in_ECX + 0x1e42) * 4);
      *puVar4 = (uint)puVar4 ^ (uint)puVar5 ^ *puVar5;
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_2 + 0x24) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)((int)in_ECX + 0x1e42) * 4);
      *puVar4 = (uint)puVar4 ^ (uint)puVar5 ^ *puVar5;
    }
    if ((int)in_ECX + 0x1e46 != param_2 + 0x28) {
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(param_2 + 0x2c) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)((int)in_ECX + 0x1e4a) * 4);
      *puVar4 = *puVar5 ^ (uint)puVar4 ^ (uint)puVar5;
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(param_2 + 0x2c) * 4);
      puVar4 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)((int)in_ECX + 0x1e4a) * 4);
      *puVar4 = *puVar5 ^ (uint)puVar4 ^ (uint)puVar5;
    }
    cVar2 = (**(code **)(*in_ECX + 0x3dc))();
    if (cVar2 == '\0') {
      piVar6 = (int *)(**(code **)(*param_1 + 0x2a4))();
      if (piVar6 == (int *)0x0) {
        piVar6 = (int *)(**(code **)(*param_1 + 0x2a0))();
      }
      in_ECX[0x6e1] = (int)piVar6;
      if (piVar6 != (int *)0x0) {
        iVar10 = (**(code **)(*piVar6 + 0x40))();
        in_ECX[0x92b] = iVar10;
      }
    }
    if (*(char *)((int)in_ECX + 0x1cc1) != '\0') {
      (**(code **)(*in_ECX + 0x68c))();
    }
    if (in_ECX[0x68c] == 0xb) {
      (**(code **)(*in_ECX + 0x5f0))(4);
    }
    iVar10 = (**(code **)(*param_1 + 0x2a4))();
    if ((iVar10 != 0) && (cVar2 = (**(code **)(*param_1 + 0x1b8))(), cVar2 == '\0')) {
      cVar2 = (**(code **)(*in_ECX + 0x618))(param_1);
      if ((cVar2 == '\x01') && (iVar10 = FUN_008ae0f0(0), iVar10 % 100 < 0x46)) {
        (**(code **)(*in_ECX + 0x6b0))(param_1);
      }
      cVar2 = FUN_0049c090();
      if (((cVar2 != '\0') && (iVar10 = FUN_008ae0f0(0), iVar10 % 100 < in_ECX[0x845])) &&
         (iVar10 = FUN_00b06f00(), in_ECX[0x846] < iVar10)) {
        (**(code **)(*in_ECX + 0x644))(param_1);
        FUN_00404ef0();
        FUN_00b06f60(0,0);
      }
    }
    iVar10 = (**(code **)(*param_1 + 0x19c))();
    if (*(int *)(iVar10 + 0x178) == 2) {
      FUN_008ae0f0(0);
    }
  }
  else {
    puVar4 = puVar5 + 2;
    if ((puVar5[2] ^ DAT_012101dc) - (int)puVar4 != puVar5[3]) {
      FUN_00b170b0(puVar4,0x3f);
    }
    iVar10 = puVar5[3] * 4;
    uVar11 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar10) ^
             *(int *)(DAT_012101d8 + 0x44) + iVar10 ^ DAT_012101dc;
    local_14 = (uint *)(iVar10 + *(int *)(DAT_012101d8 + 0x48));
    if (uVar11 != ((uint)local_14 ^ DAT_012101dc ^ *local_14)) {
      FUN_00b170b0(puVar4,0x40);
    }
    if (0 < (int)uVar11) goto LAB_004f9025;
  }
  local_1c = 0;
  iVar10 = DAT_012101d8;
  for (local_18 = 0;
      (in_ECX[0x8ba] != 0 && (local_18 < (uint)((in_ECX[0x8bb] - in_ECX[0x8ba]) / 0x28)));
      local_18 = local_18 + 1) {
    piVar6 = in_ECX + 0x60a;
    if ((in_ECX[0x60a] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x60b]) {
      FUN_00b170b0(piVar6,0x3f);
      iVar10 = DAT_012101d8;
    }
    iVar3 = in_ECX[0x60b] * 4;
    uVar11 = *(uint *)(*(int *)(iVar10 + 0x44) + iVar3) ^ *(int *)(iVar10 + 0x44) + iVar3 ^
             DAT_012101dc;
    puVar5 = (uint *)(iVar3 + *(int *)(iVar10 + 0x48));
    if (uVar11 != (*puVar5 ^ (uint)puVar5 ^ DAT_012101dc)) {
      FUN_00b170b0(piVar6,0x40);
      iVar10 = DAT_012101d8;
    }
    if ((uVar11 == ((int *)(in_ECX[0x8ba] + local_1c))[1]) &&
       (*(int *)(in_ECX[0x8ba] + local_1c) != 2)) {
      FUN_0074d290(10);
      iVar10 = DAT_012101d8;
    }
    local_1c = local_1c + 0x28;
  }
  for (uVar11 = 0; (in_ECX[0x8c2] != 0 && (uVar11 < (uint)((in_ECX[0x8c3] - in_ECX[0x8c2]) / 0x24)))
      ; uVar11 = uVar11 + 1) {
    iVar10 = FUN_0074dcb0(param_1,param_2,param_3);
    if (iVar10 == 0) goto LAB_004f8e27;
  }
  FUN_00b06f60(400,0);
  if ((((char)in_ECX[0x142] == '\0') && (*(char *)(in_ECX[0x6a9] + 0x3c) == '\0')) ||
     (((cVar2 = FUN_004e8970(0xf), cVar2 != '\0' || (cVar2 = FUN_004e8970(2), cVar2 != '\0')) &&
      (*(char *)(in_ECX[0x6a9] + 0x3c) == '\0')))) goto LAB_004f9ac0;
  cVar2 = (**(code **)(*param_1 + 0x1b8))();
  if (cVar2 == '\0') {
LAB_004f96c2:
    if ((in_ECX[0x928] ^ DAT_012101dc) - (int)(in_ECX + 0x928) != in_ECX[0x929]) {
      FUN_00b170b0(in_ECX + 0x928,0x3f);
    }
    puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x929] * 4);
    puVar4 = (uint *)(in_ECX[0x929] * 4 + *(int *)(DAT_012101d8 + 0x48));
    uVar11 = *puVar5 ^ (uint)puVar5 ^ DAT_012101dc;
    if (uVar11 != (*puVar4 ^ (uint)puVar4 ^ DAT_012101dc)) {
      FUN_00b170b0(in_ECX + 0x928,0x40);
    }
    iVar10 = FUN_00b06f00();
    if (iVar10 < (int)uVar11) {
      piVar6 = in_ECX + 0x920;
      if ((in_ECX[0x920] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x921]) {
        FUN_00b170b0(piVar6,0x3f);
      }
      iVar10 = in_ECX[0x921] * 4;
      uVar11 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar10) ^
               *(int *)(DAT_012101d8 + 0x44) + iVar10 ^ DAT_012101dc;
      puVar5 = (uint *)(iVar10 + *(int *)(DAT_012101d8 + 0x48));
      if (uVar11 != (*puVar5 ^ (uint)puVar5 ^ DAT_012101dc)) {
        FUN_00b170b0(piVar6,0x40);
      }
      if (uVar11 != 0) goto LAB_004f9ac0;
    }
    piVar6 = (int *)in_ECX[0x906];
    if ((((((piVar6 == (int *)0x0) || (in_ECX[0x907] - (int)piVar6 >> 2 == 0)) || (*piVar6 == 0)) ||
         ((in_ECX[0x41] == 0 && (in_ECX[0x52] == 0)))) ||
        (cVar2 = (**(code **)(*in_ECX + 0x3dc))(), cVar2 != '\0')) ||
       (((iVar10 = (**(code **)(*in_ECX + 0x378))(), in_ECX[0x41] == iVar10 &&
         (iVar10 = (**(code **)(*in_ECX + 0x3a0))(), in_ECX[0x52] == iVar10)) ||
        ((iVar10 = (**(code **)(*in_ECX + 0x37c))(), in_ECX[0x41] == iVar10 &&
         (iVar10 = (**(code **)(*in_ECX + 0x3a4))(), in_ECX[0x52] == iVar10)))))) goto LAB_004f9ac0;
    piVar6 = in_ECX + 0x920;
    if ((in_ECX[0x920] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x921]) {
      FUN_00b170b0(piVar6,0x3f);
    }
    puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x921] * 4);
    uVar11 = (uint)puVar5 ^ DAT_012101dc ^ *puVar5;
    puVar5 = (uint *)(in_ECX[0x921] * 4 + *(int *)(DAT_012101d8 + 0x48));
    if (uVar11 != (*puVar5 ^ (uint)puVar5 ^ DAT_012101dc)) {
      FUN_00b170b0(piVar6,0x40);
    }
    if (uVar11 != 0) {
      FUN_00404ef0();
    }
    FUN_00b06f60(200,0);
    DVar7 = timeGetTime();
    local_14 = (uint *)(DVar7 % 7);
    iVar10 = *in_ECX;
    uVar9 = (**(code **)(*param_1 + 0x94))();
    cVar2 = (**(code **)(iVar10 + 0xd4))(uVar9);
    if (cVar2 == '\0') {
      FUN_00a27360();
      FUN_00a27360();
      iVar10 = *in_ECX;
      iVar3 = in_ECX[0x906];
      iVar8 = (**(code **)(iVar10 + 0xe4))(0,0,1,0,0,1);
      (**(code **)(iVar10 + 0xf8))
                (1,*(undefined4 *)(iVar3 + 0xc),0,(int)(iVar8 + (iVar8 >> 0x1f & 7U)) >> 3);
      iVar10 = *in_ECX;
      iVar3 = in_ECX[0x906];
      iVar8 = (**(code **)(iVar10 + 0xe4))(0,0,1,0,0,1);
      (**(code **)(iVar10 + 0xf8))
                (2,*(undefined4 *)(iVar3 + 0x10),0,iVar8 / (int)((int)local_14 + 5U));
      iVar10 = (**(code **)(*in_ECX + 0xe4))();
      local_14 = (uint *)(float)iVar10;
      fVar12 = (float10)FUN_004333b0();
      puVar5 = (uint *)(float)((float10)(float)local_14 / fVar12);
      local_14 = puVar5;
      FUN_00a25900(puVar5,puVar5);
    }
    else {
      FUN_00a27360();
      FUN_00a27360();
      iVar10 = *in_ECX;
      iVar3 = in_ECX[0x906];
      iVar8 = (**(code **)(iVar10 + 0xe4))(0,0,1,0,0,1);
      (**(code **)(iVar10 + 0xf8))
                (1,*(undefined4 *)(iVar3 + 4),0,(int)(iVar8 + (iVar8 >> 0x1f & 7U)) >> 3);
      iVar10 = *in_ECX;
      iVar3 = in_ECX[0x906];
      iVar8 = (**(code **)(iVar10 + 0xe4))(0,0,1,0,0,1);
      (**(code **)(iVar10 + 0xf8))(2,*(undefined4 *)(iVar3 + 8),0,iVar8 / (int)((int)local_14 + 5U))
      ;
      iVar10 = (**(code **)(*in_ECX + 0xe4))();
      local_14 = (uint *)(float)iVar10;
      fVar12 = (float10)FUN_004333b0();
      puVar5 = (uint *)(float)((float10)(float)local_14 / fVar12);
      local_14 = puVar5;
      FUN_00a25900(puVar5,puVar5);
    }
  }
  else {
    piVar6 = in_ECX + 0x918;
    if ((in_ECX[0x918] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x919]) {
      FUN_00b170b0(piVar6,0x3f);
    }
    iVar10 = in_ECX[0x919] * 4;
    puVar5 = (uint *)(iVar10 + *(int *)(DAT_012101d8 + 0x48));
    uVar11 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar10) ^
             *(int *)(DAT_012101d8 + 0x44) + iVar10 ^ DAT_012101dc;
    if (uVar11 != (*puVar5 ^ (uint)puVar5 ^ DAT_012101dc)) {
      FUN_00b170b0(piVar6,0x40);
    }
    iVar10 = FUN_00b06f00();
    if (iVar10 < (int)uVar11) {
      if ((in_ECX[0x910] ^ DAT_012101dc) - (int)(in_ECX + 0x910) != in_ECX[0x911]) {
        FUN_00b170b0(in_ECX + 0x910,0x3f);
      }
      puVar5 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x911] * 4);
      puVar4 = (uint *)(in_ECX[0x911] * 4 + *(int *)(DAT_012101d8 + 0x48));
      uVar11 = *puVar5 ^ (uint)puVar5 ^ DAT_012101dc;
      if (uVar11 != (*puVar4 ^ (uint)puVar4 ^ DAT_012101dc)) {
        FUN_00b170b0(in_ECX + 0x910,0x40);
      }
      if (uVar11 != 0) goto LAB_004f96c2;
    }
    piVar6 = (int *)in_ECX[0x906];
    if (((((((piVar6 == (int *)0x0) || (in_ECX[0x907] - (int)piVar6 >> 2 == 0)) || (*piVar6 == 0))
          || ((in_ECX[0x41] == 0 && (in_ECX[0x52] == 0)))) ||
         ((cVar2 = (**(code **)(*in_ECX + 0x3dc))(), cVar2 != '\0' ||
          ((iVar10 = (**(code **)(*in_ECX + 0x378))(), in_ECX[0x41] == iVar10 &&
           (iVar10 = (**(code **)(*in_ECX + 0x3a0))(), in_ECX[0x52] == iVar10)))))) ||
        ((iVar10 = (**(code **)(*in_ECX + 0x37c))(), in_ECX[0x41] == iVar10 &&
         (iVar10 = (**(code **)(*in_ECX + 0x3a4))(), in_ECX[0x52] == iVar10)))) ||
       (((cVar2 = FUN_004e8970(0xe), cVar2 != '\0' || (cVar2 = FUN_004e8970(1), cVar2 != '\0')) ||
        (*(char *)(in_ECX[0x6a9] + 0x3c) != '\0')))) goto LAB_004f9ac0;
    iVar10 = FUN_00402060();
    if (iVar10 == 0) {
      FUN_00b06f60(400,0);
      iVar10 = *in_ECX;
      puVar1 = (undefined4 *)in_ECX[0x906];
      iVar3 = (**(code **)(iVar10 + 0xe4))(0,0,1,0,0,1);
      (**(code **)(iVar10 + 0xf8))(1,*puVar1,0,(int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3);
      iVar10 = (**(code **)(*in_ECX + 0xe4))();
      local_14 = (uint *)(float)iVar10;
      fVar12 = (float10)FUN_004333b0();
      puVar5 = (uint *)(float)((float10)(float)local_14 / fVar12);
      local_14 = puVar5;
    }
    else {
      FUN_00404ef0();
      FUN_00b06f60(400,0);
      FUN_00a27360();
      iVar10 = *in_ECX;
      puVar1 = (undefined4 *)in_ECX[0x906];
      iVar3 = (**(code **)(iVar10 + 0xe4))(0,0,1,0,0,1);
      (**(code **)(iVar10 + 0xf8))(1,*puVar1,0,(int)(iVar3 + (iVar3 >> 0x1f & 7U)) >> 3);
      iVar10 = (**(code **)(*in_ECX + 0xe4))();
      local_14 = (uint *)(float)iVar10;
      fVar12 = (float10)FUN_004333b0();
      puVar5 = (uint *)(float)((float10)(float)local_14 / fVar12);
      local_14 = puVar5;
    }
  }
  FUN_00a25900(puVar5,puVar5);
LAB_004f9ac0:
  uVar9 = FUN_004b28d0(param_1,param_2,param_3);
  *unaff_FS_OFFSET = local_10;
  return uVar9;
}

