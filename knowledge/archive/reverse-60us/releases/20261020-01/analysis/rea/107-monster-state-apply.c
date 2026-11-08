
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004fe290(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  undefined4 *puVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  uint *puVar5;
  int *piVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  uint *puVar11;
  int *in_ECX;
  uint uVar12;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar13;
  int iStack_20;
  int local_1c;
  float local_18;
  float local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_00c59d0b;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  iVar4 = FUN_00402060();
  local_1c = iVar4;
  FUN_00402060();
  if ((iVar4 == 0xb) && (param_1 != 0xc)) goto LAB_004fe50e;
  if ((in_ECX[0x8a8] != 0) && (in_ECX[0x8a9] - in_ECX[0x8a8] >> 4 != 0)) {
    for (local_14 = 0.0;
        (iVar4 = local_1c, in_ECX[0x8a8] != 0 &&
        ((uint)local_14 < (uint)(in_ECX[0x8a9] - in_ECX[0x8a8] >> 4)));
        local_14 = (float)((int)local_14 + 1)) {
      uVar12 = 0;
      iVar4 = (int)local_14 * 0x10;
      while( true ) {
        iVar8 = *(int *)(iVar4 + 4 + in_ECX[0x8a8]);
        if ((iVar8 == 0) || ((uint)(*(int *)(iVar4 + in_ECX[0x8a8] + 8) - iVar8 >> 2) <= uVar12))
        break;
        (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar8 + uVar12 * 4));
        uVar12 = uVar12 + 1;
      }
    }
  }
  switch(iVar4) {
  case 2:
    FUN_004b4500(0,0);
    break;
  case 4:
    if (param_1 == 1) {
      FUN_004f02e0(0x1c,0xffffffff);
      (**(code **)(*in_ECX + 0x5cc))();
    }
    break;
  case 5:
    (*(code *)PTR_FUN_00ff2ebc)
              (&DAT_00cd5d98,param_1,in_ECX[0x81],
               *(undefined4 *)(*(int *)(*(int *)(in_ECX[0x40] + 0x114) + 0x50) + 0x60));
    goto LAB_004fe50e;
  case 8:
    if (*(char *)((int)in_ECX + 0x1cdf) == '\x01') {
      FUN_004f0ce0();
    }
    local_14 = 0.0;
    for (uVar12 = 0;
        (in_ECX[0x8ba] != 0 && (uVar12 < (uint)((in_ECX[0x8bb] - in_ECX[0x8ba]) / 0x28)));
        uVar12 = uVar12 + 1) {
      iVar8 = in_ECX[0x8ba] + (int)local_14;
      iVar4 = FUN_00402060();
      if (iVar4 == *(int *)(iVar8 + 4)) {
        FUN_0074ce60();
      }
      local_14 = (float)((int)local_14 + 0x28);
    }
    local_18 = 0.0;
    iVar4 = DAT_012101d8;
    for (local_14 = 0.0;
        (in_ECX[0x6a2] != 0 && ((uint)local_14 < (uint)((in_ECX[0x6a3] - in_ECX[0x6a2]) / 0x18)));
        local_14 = (float)((int)local_14 + 1)) {
      piVar6 = in_ECX + 0x60a;
      if ((in_ECX[0x60a] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x60b]) {
        FUN_00b170b0(piVar6,0x3f);
        iVar4 = DAT_012101d8;
      }
      iVar8 = in_ECX[0x60b] * 4;
      uVar12 = *(uint *)(*(int *)(iVar4 + 0x44) + iVar8) ^ *(int *)(iVar4 + 0x44) + iVar8 ^
               DAT_012101dc;
      puVar5 = (uint *)(iVar8 + *(int *)(iVar4 + 0x48));
      if (uVar12 != (*puVar5 ^ (uint)puVar5 ^ DAT_012101dc)) {
        FUN_00b170b0(piVar6,0x40);
        iVar4 = DAT_012101d8;
      }
      if (uVar12 == *(uint *)(in_ECX[0x6a2] + 4 + (int)local_18)) {
        (**(code **)(**(int **)(in_ECX[0x692] + (int)local_14 * 4) + 0xc))(0);
        iVar4 = DAT_012101d8;
      }
      local_18 = (float)((int)local_18 + 0x18);
    }
    break;
  case 10:
    in_ECX[0x811] = -1;
  }
  switch(param_1) {
  case 3:
    iVar4 = FUN_008ae0f0(0);
    if (iVar4 % 100 < 0xf) {
      (**(code **)(*in_ECX + 0x544))(0x15,0xffffffff);
    }
    break;
  case 5:
    if (in_ECX[0x944] != 0) {
      FUN_004f5cc0(in_ECX[0x944]);
    }
    puVar1 = (undefined4 *)in_ECX[0x906];
    if ((puVar1 != (undefined4 *)0x0) && (in_ECX[0x907] - (int)puVar1 >> 2 != 0)) {
      (**(code **)(*in_ECX + 0xfc))(*puVar1);
      (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(in_ECX[0x906] + 4));
      (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(in_ECX[0x906] + 8));
      (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(in_ECX[0x906] + 0xc));
      (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(in_ECX[0x906] + 0x10));
    }
    if ((in_ECX[0x8a8] != 0) && (in_ECX[0x8a9] - in_ECX[0x8a8] >> 4 != 0)) {
      for (local_14 = 0.0;
          (in_ECX[0x8a8] != 0 && ((uint)local_14 < (uint)(in_ECX[0x8a9] - in_ECX[0x8a8] >> 4)));
          local_14 = (float)((int)local_14 + 1)) {
        uVar12 = 0;
        iVar4 = (int)local_14 * 0x10;
        while( true ) {
          iVar8 = *(int *)(in_ECX[0x8a8] + 4 + iVar4);
          if ((iVar8 == 0) || ((uint)(*(int *)(in_ECX[0x8a8] + iVar4 + 8) - iVar8 >> 2) <= uVar12))
          break;
          (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar8 + uVar12 * 4));
          uVar12 = uVar12 + 1;
        }
      }
    }
    iVar4 = FUN_008ae0f0(0);
    if (iVar4 % 100 < 0xf) {
      (**(code **)(*in_ECX + 0x544))(0x16,0xffffffff);
    }
    fVar2 = **(float **)(param_2 + 4);
    local_18 = fVar2;
    if (*(int *)(DAT_01002848 + 0x19a8) == 2) {
      in_ECX[0x786] = 100;
    }
    else {
      iVar4 = (**(code **)(*in_ECX + 0x238))();
      iStack_20 = (**(code **)(*in_ECX + 0x40))();
      iStack_20 = iVar4 * iStack_20;
      iVar4 = FUN_008ae0f0(&iStack_20);
      FUN_00b099b0(0x42c80000,0x437a0000,iVar4 % 0x65,100);
      iVar4 = FUN_00c01544();
      in_ECX[0x786] = iVar4;
    }
    if (fVar2 == 0.0) {
      (**(code **)(*in_ECX + 0x654))();
    }
    else {
      if ((*(int *)(DAT_01002848 + 0x19a8) == 2) && (in_ECX[0x6e8] < 1)) {
        FUN_00b06f60(0,0);
        if (in_ECX[0x6e8] == 0) {
          if (in_ECX[0x6e1] == 0) {
            uVar9 = 4;
          }
          else {
            uVar9 = (**(code **)(*in_ECX + 0x31c))(in_ECX[0x6e1]);
          }
          iVar4 = FUN_00403c50(0x228);
          uStack_8 = 2;
          if (iVar4 == 0) goto LAB_004feabe;
          iVar4 = in_ECX[0x786];
          iVar8 = in_ECX[0x6e9];
          uVar13 = 4;
          (**(code **)(*in_ECX + 0x344))(3,iVar8,iVar4,4,uVar9);
          uVar7 = FUN_004bddc0();
          piVar6 = (int *)FUN_00509a90(local_18,uVar7,iVar8,iVar4,uVar13,uVar9);
          goto LAB_004feac0;
        }
      }
      else {
        uVar12 = in_ECX[0x6ea];
        iVar4 = FUN_00403c50(0x228);
        uStack_8 = 1;
        if (iVar4 == 0) {
LAB_004feabe:
          piVar6 = (int *)0x0;
        }
        else {
          (**(code **)(*in_ECX + 0x344))(3);
          iVar4 = FUN_00402060();
          local_14 = (float)iVar4;
          FUN_004333b0();
          uVar9 = FUN_00c01544();
          piVar6 = (int *)FUN_00509a90(local_18,uVar9,in_ECX[0x6e9],in_ECX[0x786],~uVar12,4);
        }
LAB_004feac0:
        uStack_8 = 0xffffffff;
        FUN_0050dd70(in_ECX,2,0,piVar6,in_ECX,0,0);
        iVar4 = *piVar6;
        iVar8 = (**(code **)(*in_ECX + 0x9c))();
        uVar9 = (**(code **)(*in_ECX + 0x98))(iVar8 + in_ECX[0x62] / 2);
        uVar9 = (**(code **)(*in_ECX + 0x94))(uVar9);
        (**(code **)(iVar4 + 0x88))(uVar9);
      }
      if ((*(int *)(DAT_01002848 + 0x19a8) != 2) &&
         (cVar3 = (**(code **)(*in_ECX + 0x5a0))(), cVar3 == '\0')) {
        (**(code **)(*in_ECX + 0x134))(1,5,0xffffffff);
      }
      iVar4 = *(int *)(DAT_01002848 + 0x19a8);
      cVar3 = (**(code **)(*in_ECX + 0x5a0))();
      if ((cVar3 == '\0') && (*(int *)(DAT_01002848 + 0x19a8) == 2)) {
        (**(code **)(*in_ECX + 0x134))(1,5,((iVar4 != 2) - 1 & 0xff000001) - 1);
      }
    }
    break;
  case 8:
    if (*(char *)((int)in_ECX + 0x1cdf) == '\x01') {
      FUN_004f0c70();
    }
    uVar9 = **(undefined4 **)(param_2 + 4);
    iVar4 = FUN_008ae0f0(0);
    if (iVar4 % 100 < 0xf) {
      (**(code **)(*in_ECX + 0x544))(uVar9,0xffffffff);
    }
    for (uVar12 = 0;
        (in_ECX[0x89b] != 0 && (uVar12 < (uint)((in_ECX[0x89c] - in_ECX[0x89b]) / 0x2c)));
        uVar12 = uVar12 + 1) {
      puVar5 = (uint *)(in_ECX[0x8a0] + (uVar12 >> 5) * 4);
      *puVar5 = *puVar5 & ~(1 << ((byte)uVar12 & 0x1f));
    }
    uVar12 = 0;
    if (in_ECX[0x889] != 0) {
      do {
        puVar5 = (uint *)(in_ECX[0x88b] + (uVar12 >> 5) * 4);
        local_18 = 1.4013e-45;
        *puVar5 = *puVar5 & ~(1 << ((byte)uVar12 & 0x1f));
        uVar12 = uVar12 + 1;
      } while (uVar12 < (uint)in_ECX[0x889]);
    }
    *(undefined1 *)(in_ECX + 0x892) = 0;
    break;
  case 10:
    in_ECX[0x811] = **(int **)(param_2 + 4);
    break;
  case 0xd:
    iVar4 = (**(code **)(*in_ECX + 0x370))();
    if (in_ECX[0x41] == iVar4) {
      param_4 = param_4 & 0xffffff00;
    }
    else {
      iVar4 = *in_ECX;
      uVar9 = (**(code **)(iVar4 + 0x370))();
      (**(code **)(iVar4 + 0xf0))(uVar9);
    }
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    (**(code **)(*in_ECX + 0x2d0))(0);
    (**(code **)(*in_ECX + 0x2d8))(0);
    (**(code **)(*in_ECX + 0x2e0))(1,2);
    if (in_ECX[0x824] == 0) {
      iVar4 = FUN_00403c50(0x1e8);
      uStack_8 = 0;
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = FUN_004936d0(u_Monster_Common_Animation_Unsummo_00cd1d00,1);
      }
      uStack_8 = 0xffffffff;
      in_ECX[0x824] = iVar4;
    }
    iVar4 = (**(code **)(*in_ECX + 0xe4))();
    local_18 = (float)iVar4 * _DAT_00cd1cf8;
    FUN_00a25900(local_18,local_18);
    (**(code **)(*in_ECX + 0xf8))(1,in_ECX[0x824],0,0,1,0,0,0,0,1);
    iVar4 = 0;
    do {
      cVar3 = (**(code **)(*in_ECX + 0x410))(iVar4);
      if (cVar3 != '\0') {
        piVar6 = (int *)(**(code **)(*in_ECX + 0x40c))(iVar4);
        (**(code **)(*piVar6 + 4))(0);
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0x11);
  }
  FUN_004bad60(param_1,param_2,param_3,param_4);
  iVar4 = (**(code **)(*in_ECX + 0x45c))();
  if (iVar4 <= param_1) {
    iVar4 = *in_ECX;
    iVar8 = (**(code **)(iVar4 + 0x45c))();
    iVar4 = (**(code **)(iVar4 + 0x3b4))(param_1 - iVar8);
    if (iVar4 == 0) {
      (*(code *)PTR_FUN_00ff2ebc)(&LAB_00cd5d60,param_1);
    }
    else {
      iVar4 = *in_ECX;
      iVar8 = (**(code **)(iVar4 + 0x45c))();
      uVar9 = (**(code **)(iVar4 + 0x3b4))(param_1 - iVar8);
      (**(code **)(iVar4 + 0x100))(uVar9);
    }
  }
  if (local_1c == 3) {
    (**(code **)(*in_ECX + 0x690))();
  }
  else if (local_1c == 8) {
    if ((in_ECX[0x8a8] != 0) && (in_ECX[0x8a9] - in_ECX[0x8a8] >> 4 != 0)) {
      for (local_18 = 0.0;
          (in_ECX[0x8a8] != 0 && ((uint)local_18 < (uint)(in_ECX[0x8a9] - in_ECX[0x8a8] >> 4)));
          local_18 = (float)((int)local_18 + 1)) {
        iVar4 = (int)local_18 * 0x10;
        uVar12 = 0;
        while( true ) {
          iVar8 = *(int *)(in_ECX[0x8a8] + 4 + iVar4);
          iVar10 = in_ECX[0x8a8] + iVar4;
          if ((iVar8 == 0) || ((uint)(*(int *)(iVar10 + 8) - iVar8 >> 2) <= uVar12)) break;
          if (*(char *)(*(int *)(*(int *)(iVar10 + 4) + uVar12 * 4) + 0x13a) != '\0') {
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(*(int *)(iVar10 + 4) + uVar12 * 4));
          }
          uVar12 = uVar12 + 1;
        }
      }
    }
    *(undefined1 *)(in_ECX + 0x8d9) = 0;
  }
  if (param_1 == 8) {
    puVar5 = (uint *)(in_ECX + 0x60a);
    if ((in_ECX[0x60a] ^ DAT_012101dc) - (int)puVar5 != in_ECX[0x60b]) {
      FUN_00b170b0(puVar5,0x3f);
    }
    iVar4 = in_ECX[0x60b] * 4;
    uVar12 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar4) ^
             *(int *)(DAT_012101d8 + 0x44) + iVar4 ^ DAT_012101dc;
    puVar11 = (uint *)(iVar4 + *(int *)(DAT_012101d8 + 0x48));
    if (uVar12 != (*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
      FUN_00b170b0(puVar5,0x40);
    }
    FUN_004f3430(uVar12);
    local_18 = 0.0;
    iVar4 = DAT_012101d8;
    for (local_14 = 0.0;
        (in_ECX[0x8ba] != 0 && ((uint)local_14 < (uint)((in_ECX[0x8bb] - in_ECX[0x8ba]) / 0x28)));
        local_14 = (float)((int)local_14 + 1)) {
      if ((*puVar5 ^ DAT_012101dc) - (int)puVar5 != in_ECX[0x60b]) {
        FUN_00b170b0(puVar5,0x3f);
        iVar4 = DAT_012101d8;
      }
      iVar8 = in_ECX[0x60b] * 4;
      uVar12 = *(uint *)(*(int *)(iVar4 + 0x44) + iVar8) ^ *(int *)(iVar4 + 0x44) + iVar8 ^
               DAT_012101dc;
      puVar11 = (uint *)(iVar8 + *(int *)(iVar4 + 0x48));
      if (uVar12 != (*puVar11 ^ (uint)puVar11 ^ DAT_012101dc)) {
        FUN_00b170b0(puVar5,0x40);
        iVar4 = DAT_012101d8;
      }
      if (uVar12 == *(uint *)(in_ECX[0x8ba] + (int)local_18 + 4)) {
        FUN_0074ce70();
        iVar4 = DAT_012101d8;
      }
      local_18 = (float)((int)local_18 + 0x28);
    }
    local_18 = 0.0;
    for (local_14 = 0.0;
        (in_ECX[0x6a2] != 0 && ((uint)local_14 < (uint)((in_ECX[0x6a3] - in_ECX[0x6a2]) / 0x18)));
        local_14 = (float)((int)local_14 + 1)) {
      if ((*puVar5 ^ DAT_012101dc) - (int)puVar5 != in_ECX[0x60b]) {
        FUN_00b170b0(puVar5,0x3f);
        iVar4 = DAT_012101d8;
      }
      iVar8 = in_ECX[0x60b] * 4;
      uVar12 = *(uint *)(*(int *)(iVar4 + 0x44) + iVar8) ^ *(int *)(iVar4 + 0x44) + iVar8 ^
               DAT_012101dc;
      puVar11 = (uint *)(iVar8 + *(int *)(iVar4 + 0x48));
      if (uVar12 != ((uint)puVar11 ^ DAT_012101dc ^ *puVar11)) {
        FUN_00b170b0(puVar5,0x40);
        iVar4 = DAT_012101d8;
      }
      if (uVar12 == *(uint *)(in_ECX[0x6a2] + (int)local_18 + 4)) {
        (**(code **)(**(int **)(in_ECX[0x692] + (int)local_14 * 4) + 0xc))(1);
        iVar4 = DAT_012101d8;
      }
      local_18 = (float)((int)local_18 + 0x18);
    }
  }
  for (uVar12 = 0; (in_ECX[0x8c2] != 0 && (uVar12 < (uint)((in_ECX[0x8c3] - in_ECX[0x8c2]) / 0x24)))
      ; uVar12 = uVar12 + 1) {
    FUN_0074e9b0(param_1,param_2,param_3,param_4,local_1c);
  }
LAB_004fe50e:
  *unaff_FS_OFFSET = local_10;
  return;
}

