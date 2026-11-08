
void FUN_004a0840(int *param_1)

{
  uint *puVar1;
  int iVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int *in_ECX;
  int *piVar7;
  uint uVar8;
  int iVar9;
  undefined4 *unaff_FS_OFFSET;
  int *piVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined1 local_24 [4];
  void *local_20;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  piVar6 = param_1;
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c56c03;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if (param_1 == in_ECX) {
    uVar4 = FUN_00bffdcd(&DAT_00cabae0);
    iVar5 = FUN_00403ff0(0,in_ECX[0x202],&DAT_00cabae0,uVar4);
    if (iVar5 != 0) {
      local_14 = FUN_00403c50(0x2e0);
      local_8 = 0;
      if (local_14 == 0) {
        iVar5 = 0;
      }
      else {
        if ((uint)in_ECX[0x203] < 8) {
          piVar7 = in_ECX + 0x1fe;
        }
        else {
          piVar7 = (int *)in_ECX[0x1fe];
        }
        if ((uint)in_ECX[0x97] < 8) {
          iVar5 = FUN_004a3900(in_ECX + 0x92,piVar7,0);
        }
        else {
          iVar5 = FUN_004a3900(in_ECX[0x92],piVar7,0);
        }
      }
      local_8 = 0xffffffff;
      FUN_00a2d020(in_ECX);
      if (iVar5 != 0) {
        local_14 = FUN_00403c50(0x870);
        local_8 = 1;
        if (local_14 == 0) {
          piVar6 = (int *)0x0;
        }
        else {
          piVar6 = (int *)FUN_004a3820(iVar5,1,0);
        }
        uVar12 = 0;
        uVar11 = 0;
        local_8 = 0xffffffff;
        piVar7 = piVar6;
        piVar10 = in_ECX;
        uVar4 = (**(code **)(*in_ECX + 0x40))(piVar6);
        FUN_0050dd70(in_ECX,0x21,uVar4,piVar7,piVar10,uVar11,uVar12);
        iVar5 = *piVar6;
        uVar4 = (**(code **)(*in_ECX + 0x9c))();
        uVar4 = (**(code **)(*in_ECX + 0x98))(uVar4);
        uVar4 = (**(code **)(*in_ECX + 0x94))(uVar4);
        (**(code **)(iVar5 + 0x88))(uVar4);
        iVar5 = *piVar6;
        uVar4 = (**(code **)(*in_ECX + 0xc0))();
        (**(code **)(iVar5 + 0xb8))(uVar4);
        piVar6 = param_1;
      }
    }
  }
  FUN_004edd10(piVar6);
  if (piVar6 == (int *)in_ECX[0x14c]) {
    cVar3 = (**(code **)(*piVar6 + 0x2c))(0x21);
    if (cVar3 == '\0') {
      (**(code **)(*in_ECX + 0x344))(0);
    }
    else {
      iVar5 = *in_ECX;
      uVar4 = (**(code **)(*piVar6 + 0x18c))();
      (**(code **)(iVar5 + 0x344))(uVar4);
    }
  }
  if (piVar6 == (int *)in_ECX[0x14d]) {
    in_ECX[0x14d] = 0;
  }
  if (piVar6 == in_ECX) {
    if ((int *)in_ECX[0x1e5] != (int *)0x0) {
      (**(code **)(*(int *)in_ECX[0x1e5] + 0xc))(0);
      iVar5 = *(int *)in_ECX[0x1e5];
      uVar4 = (**(code **)(*in_ECX + 0x9c))();
      uVar4 = (**(code **)(*in_ECX + 0x98))(uVar4);
      uVar4 = (**(code **)(*in_ECX + 0x94))(uVar4);
      (**(code **)(iVar5 + 0x28))(uVar4);
      (**(code **)(*(int *)in_ECX[0x1e5] + 0x5c))(local_24);
      local_8 = 2;
      FUN_0050e060(in_ECX,2,0,local_24,0);
      local_8 = 0xffffffff;
      if (local_20 != (void *)0x0) {
        _free(local_20);
      }
    }
    cVar3 = FUN_0049c090();
    if (((cVar3 != '\0') && ((char)in_ECX[0x169] == '\0')) && (in_ECX[0x158] == 1)) {
      for (uVar8 = 0;
          (iVar5 = in_ECX[0x15a], iVar5 != 0 && (uVar8 < (uint)(in_ECX[0x15b] - iVar5 >> 2)));
          uVar8 = uVar8 + 1) {
        uVar4 = (**(code **)(*in_ECX + 0xc0))(0,0,0,0,0);
        uVar4 = (**(code **)(*in_ECX + 0x9c))(uVar4);
        uVar4 = (**(code **)(*in_ECX + 0x98))(uVar4);
        uVar4 = (**(code **)(*in_ECX + 0x94))(uVar4);
        FUN_004e9ea0(in_ECX[0x14c],*(undefined4 *)(iVar5 + uVar8 * 4),0,uVar4);
      }
      *(undefined1 *)(in_ECX + 0x169) = 1;
    }
    if (in_ECX[0x166] == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = in_ECX[0x167] - in_ECX[0x166] >> 2;
    }
    iVar9 = 0;
    if (0 < iVar5) {
      do {
        iVar2 = *(int *)(in_ECX[0x166] + iVar9 * 4);
        if ((-1 < iVar2) && (iVar2 != -1)) {
          (**(code **)(*in_ECX + 0x110))(iVar2);
        }
        iVar9 = iVar9 + 1;
      } while (iVar9 < iVar5);
    }
    if (((*(int *)(in_ECX[0x16b] + 0x10) == 0) && (iVar5 = in_ECX[0x166], iVar5 != 0)) &&
       (in_ECX[0x167] - iVar5 >> 2 != 0)) {
      iVar5 = *(int *)(iVar5 + 0x10);
      if ((iVar5 != -2) && ((iVar5 == -1 || (iVar5 != -1)))) {
        iVar5 = *in_ECX;
        uVar4 = FUN_00a530f0(0xffffffff,0,0);
        (**(code **)(iVar5 + 0x10c))(uVar4);
      }
      *(undefined4 *)(in_ECX[0x16b] + 0x10) = 1;
    }
  }
  else {
    iVar5 = in_ECX[0x3e];
    if (((*(char *)(iVar5 + 0x100) != '\0') && (*(int **)(iVar5 + 0x118) != (int *)0x0)) &&
       (*(int **)(iVar5 + 0x118) == piVar6)) {
      *(undefined4 *)(iVar5 + 0x118) = 0;
    }
  }
  if ((DAT_012101dc ^ DAT_00ffe60c) - 0xffe60c != DAT_00ffe610) {
    FUN_00b170b0(&DAT_00ffe60c,0x3f);
  }
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + DAT_00ffe610 * 4);
  uVar8 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + DAT_00ffe610 * 4) ^
          *(int *)(DAT_012101d8 + 0x44) + DAT_00ffe610 * 4 ^ DAT_012101dc;
  if (uVar8 != (*puVar1 ^ (uint)puVar1 ^ DAT_012101dc)) {
    FUN_00b170b0(&DAT_00ffe60c,0x40);
  }
  if (uVar8 == 0) {
    iVar5 = FUN_00402060();
    if (iVar5 != 3) {
      iVar5 = FUN_00402060();
      if (iVar5 != 10) {
        iVar5 = FUN_00402060();
        if (iVar5 != 0x7ff9) goto LAB_004a0d82;
      }
    }
    iVar5 = FUN_00402060();
    if (iVar5 == 0x7ff9) {
      iVar5 = FUN_00402060();
      if (iVar5 == 0x7ff9) {
        (*(code *)PTR_FUN_00ff2ebc)(u_Activated_Expand_Clear_Condition_00ccf100);
      }
      uVar4 = FUN_00402060();
      (*(code *)PTR_FUN_00ff2ebc)(&DAT_00ccf0e0,uVar4);
      param_1 = (int *)0x1;
      FUN_004676b0(&param_1);
      iVar5 = FUN_00402060();
      if (iVar5 < 1) {
        FUN_0050adb0(1);
        FUN_00539c00(6000,0x1e,0);
        FUN_004479b0(u_R_STAGE_FINALE_00ccf0c0,0xffffffff,0,0);
        (**(code **)(*in_ECX + 0x2d8))(0);
        FUN_0053be70(4,0);
      }
    }
  }
LAB_004a0d82:
  *unaff_FS_OFFSET = local_10;
  return;
}

