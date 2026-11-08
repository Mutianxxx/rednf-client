
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004bad60(uint param_1,uint param_2,char param_3,float param_4)

{
  uint *puVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *in_ECX;
  undefined4 uVar8;
  undefined4 *unaff_FS_OFFSET;
  float10 fVar9;
  undefined4 uVar10;
  wchar_t *pwVar11;
  undefined1 auStack_48 [16];
  undefined1 auStack_38 [8];
  undefined8 uStack_30;
  float fStack_28;
  int iStack_24;
  int iStack_20;
  int local_1c;
  int iStack_18;
  int iStack_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_00c57870;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  iVar3 = FUN_00402060();
  local_1c = iVar3;
  cVar2 = (**(code **)(*in_ECX + 0x410))(0x10);
  iVar7 = param_2;
  if (((cVar2 != '\0') && (param_1 == 6)) && (**(int **)(param_2 + 4) == 0)) goto LAB_004bc783;
  if (iVar3 == 0) {
    (**(code **)(*in_ECX + 0x110))(1);
  }
  else if (iVar3 == 4) {
    (**(code **)(*in_ECX + 0x410))(3);
  }
  switch(param_1) {
  case 0:
    param_2 = 1;
    FUN_00404560(&param_2);
    iVar7 = *in_ECX;
    uVar10 = (**(code **)(iVar7 + 0x390))();
    (**(code **)(iVar7 + 0x100))(uVar10);
    if (in_ECX[0x52] == 0) {
      iVar7 = *in_ECX;
      uVar10 = (**(code **)(iVar7 + 0x370))();
      (**(code **)(iVar7 + 0xf0))(uVar10);
    }
    else {
      (**(code **)(*in_ECX + 0xf0))(0);
    }
    (**(code **)(*in_ECX + 0x488))(0,0x8f,0x77,1,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0x72,0x5f,1,0,0);
    (**(code **)(*in_ECX + 0x494))(1,0,1000,1000,0x3f800000,0x3f800000);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    iVar7 = (**(code **)(*in_ECX + 0x208))();
    if (iVar7 < 1) {
LAB_004baeac:
      FUN_00511040(2,0);
      goto LAB_004bafa9;
    }
    iVar7 = (**(code **)(*in_ECX + 0x204))();
    iVar5 = (**(code **)(*in_ECX + 0x9c))();
    iVar7 = iVar7 - iVar5;
    if (iVar7 == 0) goto LAB_004baeac;
    FUN_004ba0c0(0,((iVar7 < 1) - 1 & 0xfffff830) + 1000);
    FUN_00511d30(iVar7);
    FUN_00510d70(2);
    goto LAB_004bafb4;
  case 1:
    iVar7 = *in_ECX;
    uVar10 = (**(code **)(iVar7 + 0x36c))();
    (**(code **)(iVar7 + 0xf0))(uVar10);
    iVar7 = *in_ECX;
    uVar10 = (**(code **)(iVar7 + 0x398))();
    (**(code **)(iVar7 + 0x100))(uVar10);
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    FUN_00511040(2,0);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
LAB_004bafa9:
    FUN_004ba0c0(2,0);
LAB_004bafb4:
    if ((iVar3 == 4) && ((*(byte *)(in_ECX + 0x133) & 2) != 0)) {
      FUN_00a6ad50(0,1,0);
      FUN_00a6ad20(0,0,0,500);
    }
    break;
  case 2:
    iVar7 = *in_ECX;
    uVar10 = (**(code **)(iVar7 + 0x36c))();
    (**(code **)(iVar7 + 0xf0))(uVar10);
    iVar7 = *in_ECX;
    uVar10 = (**(code **)(iVar7 + 0x398))();
    (**(code **)(iVar7 + 0x100))(uVar10);
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    FUN_00511040(2,0);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    FUN_004ba0c0(2,0);
    break;
  case 3:
    piVar4 = *(int **)(iVar7 + 4);
    iVar3 = piVar4[1];
    iVar5 = *piVar4;
    in_ECX[0x5af] = piVar4[2];
    fStack_28 = (float)iVar3 * _DAT_00cc10ac;
    iVar3 = *(int *)(iVar7 + 4);
    param_2 = 0;
    if ((iVar3 != 0) && (3 < (uint)(*(int *)(iVar7 + 8) - iVar3 >> 2))) {
      param_2 = *(int *)(iVar3 + 0xc);
    }
    iStack_24 = 0;
    if ((iVar3 != 0) && (4 < (uint)(*(int *)(iVar7 + 8) - iVar3 >> 2))) {
      iStack_24 = *(int *)(iVar3 + 0x10);
    }
    iVar7 = FUN_00c00d0b();
    if ((iVar7 == 0) || (*(char *)(iVar7 + 0x2770) != '\0')) {
      if (iVar5 == 4) {
        iVar5 = (**(code **)(*in_ECX + 0xc0))();
      }
      else {
        (**(code **)(*in_ECX + 0xb8))(iVar5);
      }
    }
    local_1c = 0;
    iStack_20 = 0;
    param_2 = (**(code **)(*in_ECX + 0x518))(&local_1c,&iStack_20,iStack_24,param_2 == 2,fStack_28);
    FUN_00404560(&param_2);
    (**(code **)(*in_ECX + 0x488))(0,local_1c,local_1c,0,iStack_20,1);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    FUN_00511040(2,0);
    param_2 = *in_ECX;
    uVar10 = FUN_00447960(iVar5,4,0);
    (**(code **)(param_2 + 0x49c))(uVar10);
    FUN_004ba0c0(2,0);
    iVar7 = (**(code **)(*in_ECX + 0x374))(in_ECX[0x5af]);
    if (iVar7 != 0) {
      iVar7 = *in_ECX;
      uVar10 = (**(code **)(iVar7 + 0x39c))(in_ECX[0x5af]);
      (**(code **)(iVar7 + 0x100))(uVar10);
      iVar7 = (**(code **)(*in_ECX + 0x39c))(in_ECX[0x5af]);
      if (iVar7 == 0) {
        iVar7 = *in_ECX;
        uVar10 = (**(code **)(iVar7 + 0x374))(in_ECX[0x5af]);
        (**(code **)(iVar7 + 0xf0))(uVar10);
      }
    }
    break;
  case 4:
    iStack_20 = FUN_00402060();
    fStack_28 = (float)in_ECX[0x5ca];
    iStack_18 = (**(code **)(*in_ECX + 0xc0))();
    if (**(int **)(iVar7 + 4) != 4) {
      iStack_18 = **(int **)(iVar7 + 4);
    }
    param_2 = 0;
    FUN_00404560(&param_2);
    iVar3 = (**(code **)(*in_ECX + 0x94))();
    param_2 = 0;
    in_ECX[0x5c7] = iVar3;
    FUN_00404560(&param_2);
    iStack_14 = 0;
    (**(code **)(*in_ECX + 0x344))(3);
    iStack_24 = FUN_004bddc0();
    param_2 = *(uint *)(*(int *)(iVar7 + 4) + 4);
    FUN_00404560(&param_2);
    in_ECX[0x5ca] = *(int *)(*(int *)(iVar7 + 4) + 8);
    param_2 = param_2 & 0xffffff;
    if (((local_1c == 4) && (iVar3 = (**(code **)(*in_ECX + 0x9c))(), iVar3 == 0)) &&
       ((fStack_28 == 2.8026e-45 || (iVar3 = FUN_00402060(), iStack_20 < iVar3)))) {
      param_2 = CONCAT13(1,(undefined3)param_2);
    }
    iVar3 = in_ECX[0x5ca];
    if (iVar3 == 2) {
      *(undefined1 *)(in_ECX + 0x5cb) = 1;
    }
    else if (param_2._3_1_ == '\0') {
      *(undefined1 *)(in_ECX + 0x5cb) = 0;
    }
    if ((iVar3 == 1) || (iVar3 == 2)) {
      iStack_14 = *(int *)(*(int *)(iVar7 + 4) + 0xc);
      iVar7 = *(int *)(*(int *)(iVar7 + 4) + 0x10);
      if (iVar3 == 2) {
        if ((local_1c == 4) && (1 < iStack_20)) {
          iVar7 = iVar7 / 2;
        }
        uStack_30 = (double)CONCAT44(iVar7,(undefined4)uStack_30);
        FUN_00404560((int)&uStack_30 + 4);
        uStack_30 = (double)CONCAT44(iStack_14,(undefined4)uStack_30);
        FUN_00404560((int)&uStack_30 + 4);
        iVar7 = -400;
      }
      FUN_004b98f0(iStack_14,iStack_24,100);
      uVar10 = FUN_00c01544();
      uStack_30 = (double)CONCAT44(uVar10,(undefined4)uStack_30);
      FUN_00404560((int)&uStack_30 + 4);
      FUN_004b98f0(iVar7,iStack_24,100);
      iVar7 = FUN_00c01544();
      iVar3 = FUN_004b9fa0(1);
      iStack_14 = (iVar7 * iVar7) / (iVar3 * -2);
      if (iVar7 < 0) {
        iStack_14 = -iStack_14;
      }
      iVar3 = FUN_00402060();
      if (((iVar3 == 1) && (0 < iVar7)) && (iStack_14 < 1)) {
        iStack_14 = 1;
      }
    }
    else if (iVar3 == 0) {
      iStack_14 = *(int *)(*(int *)(iVar7 + 4) + 0xc);
      FUN_00404560(&iStack_14);
      iStack_14 = *(int *)(*(int *)(iVar7 + 4) + 0x10);
      iVar7 = FUN_00402060();
      if (((iVar7 == 1) && (iStack_14 < 1)) && (iVar7 = (**(code **)(*in_ECX + 0x9c))(), iVar7 < 1))
      {
        uStack_30 = (double)CONCAT44(2,(undefined4)uStack_30);
        FUN_00404560((int)&uStack_30 + 4);
        DAT_01005214 = 1;
      }
    }
    if (param_2._3_1_ == '\0') {
      iVar7 = FUN_00402060();
      if (iVar7 < 0) {
        iStack_18 = FUN_00447960(iStack_18);
        iVar7 = FUN_00402060();
        uStack_30 = (double)CONCAT44(-iVar7,(undefined4)uStack_30);
        FUN_00404560((int)&uStack_30 + 4);
      }
      iVar7 = FUN_00c00d0b();
      if ((iVar7 == 0) || (*(char *)(iVar7 + 0x2770) != '\0')) {
        (**(code **)(*in_ECX + 0xb8))(iStack_18);
      }
    }
    iVar7 = FUN_00402060();
    uStack_30 = (double)CONCAT44(iVar7 / 2,(undefined4)uStack_30);
    FUN_00404560((int)&uStack_30 + 4);
    iVar7 = (**(code **)(*in_ECX + 0x3a0))();
    if (iVar7 == 0) {
      iVar7 = (**(code **)(*in_ECX + 0x378))();
      if (iVar7 == 0) {
        iVar7 = (**(code **)(*in_ECX + 0x36c))();
        if (iVar7 == 0) goto LAB_004bb587;
        iVar7 = *in_ECX;
        uVar10 = (**(code **)(iVar7 + 0x36c))();
      }
      else {
        iVar7 = *in_ECX;
        uVar10 = (**(code **)(iVar7 + 0x378))();
      }
      (**(code **)(iVar7 + 0xf0))(uVar10);
    }
    else {
      iVar7 = *in_ECX;
      uVar10 = (**(code **)(iVar7 + 0x3a0))();
      (**(code **)(iVar7 + 0x100))(uVar10);
      (**(code **)(*in_ECX + 0xf0))(0);
    }
LAB_004bb587:
    iVar7 = FUN_00402060();
    if (iVar7 != 0) {
      iVar7 = FUN_00402060();
      if (iVar7 == 1) {
        if ((local_1c == 4) && (0 < iStack_20)) {
          iStack_14 = (int)(iStack_14 + (iStack_14 >> 0x1f & 3U)) >> 2;
        }
      }
      else {
        iVar7 = FUN_00402060();
        if (iVar7 == 2) {
          uStack_30 = (double)((ulonglong)uStack_30 & 0xffffffff);
          FUN_00404560((int)&uStack_30 + 4);
          iStack_14 = 0;
        }
      }
    }
    if (param_2._3_1_ != '\0') {
      iVar7 = FUN_00402060();
      if (iVar7 != 2) {
        if (iStack_24 < 0xea61) {
          pwVar11 = u_DOWN_LIGHT_00cd1500;
        }
        else {
          if (iStack_24 < 0x186a1) {
            (**(code **)(*in_ECX + 0x10c))(u_DOWN_MIDDLE_00cd14e8,0xffffffff,0,0);
            goto LAB_004bb63b;
          }
          pwVar11 = u_DOWN_HEAVY_00cd14d0;
        }
        (**(code **)(*in_ECX + 0x10c))(pwVar11);
      }
LAB_004bb63b:
      if (in_ECX[0x40] != 0) {
        iVar7 = FUN_00402060();
        if (iVar7 == 1) {
          iVar7 = (**(code **)(*in_ECX + 0x4d0))(0);
        }
        else {
          iVar7 = (**(code **)(*in_ECX + 0x4d0))(1);
        }
        piVar4 = (int *)(&DAT_01002e78)[iVar7];
        iVar7 = (**(code **)(*in_ECX + 0xc0))();
        iVar3 = (**(code **)(*piVar4 + 0x1c))();
        *(char *)(iVar3 + 0x58) = '\x01' - (iVar7 != 0);
        iVar7 = *piVar4;
        uVar10 = (**(code **)(*in_ECX + 0x9c))();
        uVar10 = (**(code **)(*in_ECX + 0x98))(uVar10);
        uVar10 = (**(code **)(*in_ECX + 0x94))(uVar10);
        (**(code **)(iVar7 + 0x28))(uVar10);
        (**(code **)(*piVar4 + 0xc))(0);
        (**(code **)(*piVar4 + 0x5c))(auStack_38);
        uStack_8 = 0;
        FUN_0050e060(in_ECX,2,0,auStack_38,0);
        uStack_8 = 0xffffffff;
        FUN_00644d50();
      }
    }
    iVar7 = FUN_008ae0f0(0,999);
    param_2 = FUN_00402060(iVar7 % 1000);
    uVar10 = FUN_00c01544();
    param_2 = FUN_00402060(uVar10);
    uVar10 = FUN_00c01544();
    param_2 = FUN_00473f20(uVar10);
    FUN_00404560(&param_2);
    uStack_30 = (double)iStack_14;
    iVar7 = FUN_008ae0f0(0,999);
    uVar10 = FUN_00c01544(iVar7 % 1000);
    uVar10 = FUN_00c01544(uVar10);
    iStack_14 = FUN_00473f20(uVar10);
    iVar7 = *in_ECX;
    uVar10 = FUN_00402060(0,0,0);
    uVar10 = FUN_00402060(uVar10);
    (**(code **)(iVar7 + 0x488))(0,uVar10);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    iVar7 = *in_ECX;
    uVar10 = FUN_00447960(iStack_18,4,0);
    (**(code **)(iVar7 + 0x49c))(uVar10);
    FUN_004ba0c0(1,0);
    cVar2 = (**(code **)(*in_ECX + 0x2c))(0x211);
    iVar7 = iStack_14;
    if ((cVar2 != '\0') && (cVar2 = FUN_004f0120(0x10012), iVar7 = iStack_14, cVar2 != '\0')) {
      iVar7 = 0;
    }
    FUN_00511d30(iVar7);
    iVar7 = FUN_00402060();
    if ((local_1c == 4) && (fStack_28 == 2.8026e-45)) {
      iVar7 = 1;
    }
    else if ((iVar7 != 1) && (iVar7 != 2)) break;
    iVar3 = (**(code **)(*in_ECX + 0x104))();
    if (iVar3 == 0) {
      iVar3 = (**(code **)(*in_ECX + 0xf4))();
      if (iVar3 != 0) {
        uVar10 = 0;
        (**(code **)(*in_ECX + 0xf4))(0);
        FUN_00a28110(uVar10);
        if (iVar7 == 1) {
          uVar10 = FUN_00402060();
          (**(code **)(*in_ECX + 0xf4))(uVar10);
          FUN_004ba360(uVar10);
          param_4 = (float)((uint)param_4 & 0xffffff00);
          break;
        }
        if (iVar7 == 2) {
          uVar10 = FUN_00402060();
          (**(code **)(*in_ECX + 0xf4))(uVar10);
          FUN_004ba360(uVar10);
        }
      }
LAB_004bb96d:
      param_4 = (float)((uint)param_4 & 0xffffff00);
    }
    else {
      uVar10 = 0;
      (**(code **)(*in_ECX + 0x104))(0);
      FUN_00a2d630(uVar10);
      if (iVar7 == 1) {
        uVar10 = FUN_00402060();
        (**(code **)(*in_ECX + 0x104))(uVar10);
        FUN_00a305b0(uVar10);
        param_4 = (float)((uint)param_4 & 0xffffff00);
      }
      else {
        if (iVar7 != 2) goto LAB_004bb96d;
        uVar10 = FUN_00402060();
        (**(code **)(*in_ECX + 0x104))(uVar10);
        FUN_00a305b0(uVar10);
        param_4 = (float)((uint)param_4 & 0xffffff00);
      }
    }
    break;
  case 5:
    piVar4 = (int *)FUN_004ac500();
    if ((piVar4 != (int *)0x0) &&
       (piVar4 = (int *)(**(code **)(*piVar4 + 0x2a4))(), piVar4 != (int *)0x0)) {
      iVar7 = *piVar4;
      FUN_00402060();
      (**(code **)(iVar7 + 0x4b0))();
    }
    FUN_004bdf40();
    if ((uint)in_ECX[0x5d6] < 8) {
      piVar4 = in_ECX + 0x5d1;
    }
    else {
      piVar4 = (int *)in_ECX[0x5d1];
    }
    (**(code **)(*in_ECX + 0x10c))(piVar4,0xffffffff,0,0);
    (**(code **)(*in_ECX + 0x110))(0);
    (**(code **)(*in_ECX + 0x2d0))(0);
    (**(code **)(*in_ECX + 0x2d8))(0);
    param_4 = (float)((uint)param_4 & 0xffffff00);
    iVar7 = (**(code **)(*in_ECX + 0xf4))();
    if (iVar7 != 0) {
      uVar10 = 1;
      (**(code **)(*in_ECX + 0xf4))(1);
      FUN_00a28110(uVar10);
    }
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    cVar2 = (**(code **)(*in_ECX + 0x2c))(0x211);
    if ((cVar2 != '\0') && (cVar2 = (**(code **)(*in_ECX + 0x5a0))(), cVar2 == '\0')) {
      FUN_00511040(2,0);
      FUN_004ba0c0(0,0);
    }
    break;
  case 6:
    if (iVar3 != 6) {
      FUN_004b9930(0);
    }
    param_2 = **(undefined4 **)(iVar7 + 4);
    FUN_00404560(&param_2);
    param_2 = (uint)(*(int *)(*(int *)(iVar7 + 4) + 4) != 0);
    FUN_00404560(&param_2);
    param_2 = *in_ECX;
    uVar10 = (**(code **)(param_2 + 0x380))();
    (**(code **)(param_2 + 0xf0))(uVar10);
    param_2 = *in_ECX;
    uVar10 = (**(code **)(param_2 + 0x3a8))();
    (**(code **)(param_2 + 0x100))(uVar10);
    iVar3 = FUN_00402060();
    if (iVar3 == 0) {
      param_2 = 0x8f;
      FUN_00404560(&param_2);
      param_2 = 0x77;
      FUN_00404560(&param_2);
      param_2 = 0x72;
      FUN_00404560(&param_2);
      param_2 = 0x5f;
      FUN_00404560(&param_2);
      (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
      (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
      (**(code **)(*in_ECX + 0x494))(1,0,1000,1000,0x3f800000,0x3f800000);
      (**(code **)(*in_ECX + 0x49c))(4,4,0);
      FUN_004ba0c0(2,0);
      param_2 = 0;
      FUN_00404560(&param_2);
      break;
    }
    iVar3 = FUN_00402060();
    if (iVar3 == 1) {
      iVar7 = *(int *)(*(int *)(iVar7 + 4) + 8);
      iVar3 = FUN_00402060();
      if (iVar3 == 0) {
        iVar3 = *in_ECX;
        uVar10 = FUN_00402060(1,0,0);
        uVar10 = FUN_00402060(uVar10);
        (**(code **)(iVar3 + 0x488))(0,uVar10);
        iVar3 = *in_ECX;
        iVar5 = FUN_00402060(1,0,0);
        iVar5 = FUN_00402060(iVar5 / 2);
        (**(code **)(iVar3 + 0x488))(1,iVar5 / 2);
        (**(code **)(*in_ECX + 0x494))(1,0,1000,1000,0x3f800000,0x3f800000);
        if (iVar7 == 0) {
          iVar3 = (**(code **)(*in_ECX + 0xf4))();
          if (iVar3 != 0) {
            uVar10 = 0;
            (**(code **)(*in_ECX + 0xf4))(0);
            FUN_00a28110(uVar10);
          }
          piVar4 = *(int **)in_ECX[0x3e];
          if (piVar4 == (int *)0x0) {
            piVar4 = (int *)in_ECX[0x3e] + 2;
          }
          fVar9 = (float10)(**(code **)(*piVar4 + 8))(2);
          if (fVar9 <= (float10)_DAT_00ccb260) {
            iVar3 = (**(code **)(*in_ECX + 0x4c0))();
            iVar5 = (**(code **)(*in_ECX + 0x4bc))();
            if (iVar5 <= iVar3 + -1) {
              iVar3 = (**(code **)(*in_ECX + 0x4c0))();
              goto LAB_004bbfe5;
            }
            iVar3 = (**(code **)(*in_ECX + 0x4bc))();
          }
          else {
            iVar3 = (**(code **)(*in_ECX + 0x4bc))();
            iVar5 = (**(code **)(*in_ECX + 0x4b8))();
            if (iVar3 + -1 < iVar5) {
              iVar3 = (**(code **)(*in_ECX + 0x4b8))();
            }
            else {
              iVar3 = (**(code **)(*in_ECX + 0x4bc))();
LAB_004bbfe5:
              iVar3 = iVar3 + -1;
            }
          }
          iVar5 = (**(code **)(*in_ECX + 0x104))();
          if (iVar5 != 0) goto LAB_004bbf02;
          if (in_ECX[0x41] != 0) goto LAB_004bc007;
        }
        else {
          (**(code **)(*in_ECX + 0x10c))(u_JUMP_START_00cd1494,0xffffffff,0,0);
          (**(code **)(*in_ECX + 0x4e4))();
          (**(code **)(*in_ECX + 0x344))(3);
          uVar10 = FUN_004ba2d0();
          (**(code **)(*in_ECX + 0x344))(3,uVar10);
          uVar10 = FUN_004bddc0();
          fVar9 = (float10)FUN_004b98f0(iVar7,uVar10);
          param_4 = (float)fVar9;
          FUN_00511040(2,param_4);
          iVar3 = (**(code **)(*in_ECX + 0x104))();
          if (iVar3 == 0) {
            if (in_ECX[0x41] != 0) {
              FUN_00a28110(0);
              iVar3 = (**(code **)(*in_ECX + 0x4b8))();
LAB_004bc007:
              FUN_004ba360(iVar3);
            }
          }
          else {
            uVar10 = 0;
            (**(code **)(*in_ECX + 0x104))(0);
            FUN_00a2d630(uVar10);
            iVar3 = (**(code **)(*in_ECX + 0x4b8))();
LAB_004bbf02:
            (**(code **)(*in_ECX + 0x104))(iVar3);
            FUN_00a305b0(iVar3);
          }
        }
        param_3 = '\0';
      }
      else {
        (**(code **)(*in_ECX + 0x10c))(u_JUMP_START_00cd1494,0xffffffff);
        (**(code **)(*in_ECX + 0x4ec))();
        (**(code **)(*in_ECX + 0x344))(3,100);
        uVar10 = FUN_004bddc0();
        fVar9 = (float10)FUN_004b98f0(iVar7,uVar10);
        param_4 = (float)fVar9;
        FUN_00511040(2,param_4);
        (**(code **)(*in_ECX + 0x488))(0,0x11e,0x11e,0,0,0);
        (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
        (**(code **)(*in_ECX + 0x494))(1,0,1000,1000,0x3f800000,0x3f800000);
        iVar3 = *in_ECX;
        uVar10 = (**(code **)(iVar3 + 0xc0))(4,0);
        uVar10 = FUN_00447960(uVar10);
        (**(code **)(iVar3 + 0x49c))(uVar10);
        iVar3 = *in_ECX;
        uVar10 = (**(code **)(iVar3 + 0x380))();
        (**(code **)(iVar3 + 0xf0))(uVar10);
        iVar3 = *in_ECX;
        uVar10 = (**(code **)(iVar3 + 0x3a8))();
        (**(code **)(iVar3 + 0x100))(uVar10);
        iVar3 = (**(code **)(*in_ECX + 0x104))();
        if (iVar3 == 0) {
          if (in_ECX[0x41] != 0) {
            FUN_00a28110(1);
          }
        }
        else {
          uVar10 = 1;
          (**(code **)(*in_ECX + 0x104))(1);
          FUN_00a2d630(uVar10);
        }
        iVar3 = (**(code **)(*in_ECX + 0x4c0))();
        iVar5 = (**(code **)(*in_ECX + 0x4bc))();
        if (iVar3 + -1 < iVar5) {
          iVar3 = (**(code **)(*in_ECX + 0x4bc))();
        }
        else {
          iVar3 = (**(code **)(*in_ECX + 0x4c0))();
          iVar3 = iVar3 + -1;
        }
        iVar5 = (**(code **)(*in_ECX + 0x104))();
        if (iVar5 == 0) {
          if (in_ECX[0x41] != 0) {
            FUN_004ba360(iVar3);
          }
        }
        else {
          (**(code **)(*in_ECX + 0x104))(iVar3);
          FUN_00a305b0(iVar3);
        }
      }
      param_4 = (float)((uint)param_4 & 0xffffff00);
      iVar3 = FUN_00402060();
      if (iVar3 == 0) {
        uVar10 = 2;
      }
      else {
        uVar10 = 1;
      }
      FUN_004ba0c0(uVar10,0);
      iVar3 = local_1c;
      if (((0 < iVar7) || (local_1c == 0)) ||
         ((cVar2 = (**(code **)(*in_ECX + 0x2c))(0x111), cVar2 != '\0' && (iVar3 == 0xb)))) {
        param_2 = 0;
        FUN_00404560(&param_2);
        param_2 = 1;
        FUN_00404560(&param_2);
      }
      break;
    }
    iVar7 = FUN_00402060();
    if (iVar7 != 2) break;
    (**(code **)(*in_ECX + 0x10c))(u_JUMP_END_00cd1480,0xffffffff,0,0);
    (**(code **)(*in_ECX + 0x4e8))();
    if (in_ECX[0x40] != 0) {
      iVar7 = (**(code **)(*in_ECX + 0x4d0))(1);
      piVar4 = (int *)(&DAT_01002e78)[iVar7];
      iVar7 = (**(code **)(*in_ECX + 0xc0))();
      iVar3 = (**(code **)(*piVar4 + 0x1c))();
      *(char *)(iVar3 + 0x58) = '\x01' - (iVar7 != 0);
      iVar7 = *piVar4;
      uVar10 = (**(code **)(*in_ECX + 0x9c))();
      uVar10 = (**(code **)(*in_ECX + 0x98))(uVar10);
      uVar10 = (**(code **)(*in_ECX + 0x94))(uVar10);
      (**(code **)(iVar7 + 0x28))(uVar10);
      (**(code **)(*piVar4 + 0xc))(0);
      (**(code **)(*piVar4 + 0x5c))(auStack_48);
      uStack_8 = 1;
      FUN_0050e060(in_ECX,2,0,auStack_48,0);
      uStack_8 = 0xffffffff;
      FUN_00644d50();
    }
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    FUN_004ba0c0(2,0);
    iVar7 = (**(code **)(*in_ECX + 0x104))();
    if (iVar7 == 0) {
      if (in_ECX[0x41] != 0) {
        FUN_00a28110(0);
        uVar10 = (**(code **)(*in_ECX + 0x4c0))();
        FUN_004ba360(uVar10);
      }
    }
    else {
      uVar10 = 0;
      (**(code **)(*in_ECX + 0x104))(0);
      FUN_00a2d630(uVar10);
      uVar10 = (**(code **)(*in_ECX + 0x4c0))();
      (**(code **)(*in_ECX + 0x104))(uVar10);
      FUN_00a305b0(uVar10);
    }
    goto LAB_004bc685;
  case 7:
    (**(code **)(*in_ECX + 0x4e0))();
    iVar7 = *in_ECX;
    uVar10 = (**(code **)(iVar7 + 900))();
    (**(code **)(iVar7 + 0xf0))(uVar10);
    iVar7 = *in_ECX;
    uVar10 = (**(code **)(iVar7 + 0x3ac))();
    (**(code **)(iVar7 + 0x100))(uVar10);
    iVar7 = *in_ECX;
    uVar10 = (**(code **)(iVar7 + 0x464))();
    (**(code **)(iVar7 + 0x198))(uVar10);
    (**(code **)(*in_ECX + 0x494))(1,3,1000,1000,0x3f800000,0x3f800000);
    FUN_0043f540(0);
    goto LAB_004bc664;
  case 8:
    if ((uint)in_ECX[0x612] < 8) {
      piVar4 = in_ECX + 0x60d;
    }
    else {
      piVar4 = (int *)in_ECX[0x60d];
    }
    (**(code **)(*in_ECX + 0x10c))(piVar4,0xffffffff,0,0);
    param_2 = **(undefined4 **)(iVar7 + 4);
    FUN_00404560(&param_2);
    iVar7 = *in_ECX;
    uVar10 = FUN_00402060();
    iVar7 = (**(code **)(iVar7 + 0x460))(uVar10);
    if (iVar7 != 0) {
      (**(code **)(*in_ECX + 0x198))(iVar7);
    }
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(2,2,1000,1000,0x3f800000,0x3f800000);
    FUN_00511040(2,0);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    FUN_004ba0c0(2,0);
    iVar7 = *in_ECX;
    uVar10 = FUN_00402060();
    iVar7 = (**(code **)(iVar7 + 0x3b0))(uVar10);
    param_2 = *in_ECX;
    uVar10 = FUN_00402060();
    iVar3 = (**(code **)(param_2 + 0x388))(uVar10);
    if (iVar7 == 0) {
      if (iVar3 != 0) {
        (**(code **)(*in_ECX + 0x100))(0);
        (**(code **)(*in_ECX + 0xf0))(iVar3);
      }
    }
    else {
      (**(code **)(*in_ECX + 0xf0))(0);
      (**(code **)(*in_ECX + 0x100))(iVar7);
    }
    break;
  case 9:
    if (((iVar7 == 0) || (uVar6 = FUN_00466790(), uVar6 < 3)) ||
       (*(int *)(*(int *)(iVar7 + 4) + 8) != 1)) {
      iVar3 = (**(code **)(*in_ECX + 0x39c))(0);
      if (iVar3 == 0) {
        iVar3 = (**(code **)(*in_ECX + 0x39c))(1);
        if (iVar3 == 0) {
          iVar3 = (**(code **)(*in_ECX + 0x374))(0);
          if (iVar3 == 0) {
            iVar3 = (**(code **)(*in_ECX + 0x374))(1);
            if (iVar3 == 0) {
              iVar3 = (**(code **)(*in_ECX + 0x390))();
              if (iVar3 == 0) {
                iVar3 = (**(code **)(*in_ECX + 0x370))();
                if (iVar3 != 0) {
                  iVar3 = *in_ECX;
                  uVar10 = (**(code **)(iVar3 + 0x370))();
                  goto LAB_004bc504;
                }
              }
              else {
                iVar3 = *in_ECX;
                uVar10 = (**(code **)(iVar3 + 0x390))();
                (**(code **)(iVar3 + 0x100))(uVar10);
              }
              goto LAB_004bc50d;
            }
            iVar3 = *in_ECX;
            uVar10 = (**(code **)(iVar3 + 0x374))(1);
          }
          else {
            iVar3 = *in_ECX;
            uVar10 = (**(code **)(iVar3 + 0x374))(0);
          }
LAB_004bc504:
          (**(code **)(iVar3 + 0xf0))(uVar10);
        }
        else {
          iVar3 = *in_ECX;
          uVar10 = (**(code **)(iVar3 + 0x39c))(1);
          (**(code **)(iVar3 + 0x100))(uVar10);
        }
      }
      else {
        iVar3 = *in_ECX;
        uVar10 = (**(code **)(iVar3 + 0x39c))(0);
        (**(code **)(iVar3 + 0x100))(uVar10);
      }
    }
    else {
      if (in_ECX[0x41] != 0) {
        FUN_00a28110(1);
      }
      if (in_ECX[0x52] != 0) {
        FUN_00a2d630(1);
      }
    }
LAB_004bc50d:
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    iVar3 = (**(code **)(*in_ECX + 0x104))();
    if (iVar3 == 0) {
      iVar3 = (**(code **)(*in_ECX + 0xf4))();
      if (iVar3 != 0) {
        (**(code **)(*in_ECX + 0xf4))();
        FUN_00a27360();
        uVar10 = 1;
        (**(code **)(*in_ECX + 0xf4))(1);
        FUN_00a28110(uVar10);
      }
    }
    else {
      (**(code **)(*in_ECX + 0x104))();
      FUN_00a319e0();
      uVar10 = 1;
      (**(code **)(*in_ECX + 0x104))(1);
      FUN_00a2d630(uVar10);
    }
    param_4 = (float)((uint)param_4 & 0xffffff00);
    if ((iVar7 == 0) || (iVar3 = FUN_00466790(), iVar3 == 0)) {
      uVar10 = 2;
    }
    else {
      uVar10 = **(undefined4 **)(iVar7 + 4);
    }
    if ((iVar7 == 0) || (uVar6 = FUN_00466790(), uVar6 < 2)) {
      uVar8 = 0;
    }
    else {
      uVar8 = *(undefined4 *)(*(int *)(iVar7 + 4) + 4);
    }
    FUN_004ba0c0(uVar10,uVar8);
    FUN_00511040(2,0);
    cVar2 = (**(code **)(*in_ECX + 0x410))(0x10);
    if (cVar2 != '\0') {
      (**(code **)(*in_ECX + 0x10c))(u_CONDITION_STUN_00cd1460,0xffffffff,0,0);
    }
  }
  if (param_3 != '\0') {
    FUN_00404ef0();
    FUN_00b06f60(0,0);
  }
LAB_004bc664:
  if ((param_4._0_1_ != '\0') && (in_ECX[0x41] != 0)) {
    FUN_00a27360();
    FUN_00a23c90();
  }
LAB_004bc685:
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x558] * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ param_1;
  puVar1 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x558] * 4);
  *puVar1 = (uint)puVar1 ^ DAT_012101dc ^ param_1;
  piVar4 = in_ECX + 0x53b;
  param_4 = 3.22299e-44;
  do {
    if ((int *)*piVar4 != (int *)0x0) {
      (**(code **)(*(int *)*piVar4 + 0xcc))(param_1);
    }
    piVar4 = piVar4 + 1;
    param_4 = (float)((int)param_4 + -1);
  } while (param_4 != 0.0);
  if (*(char *)((int)in_ECX + 0x1665) != '\0') {
    iVar7 = FUN_00402060();
    if (((iVar7 == 4) && (iVar7 = FUN_00402060(), iVar7 == 2)) &&
       (*(char *)((int)in_ECX + 0x1666) == '\0')) {
      in_ECX[0x59a] = 0;
      in_ECX[0x59b] = -1;
      *(undefined1 *)((int)in_ECX + 0x1666) = 1;
    }
    iVar7 = FUN_00402060();
    if (((iVar7 != 4) && (iVar7 = FUN_00402060(), iVar7 != 9)) &&
       (*(char *)((int)in_ECX + 0x1666) != '\0')) {
      in_ECX[0x59a] = 0;
      in_ECX[0x59b] = -1;
      *(undefined1 *)((int)in_ECX + 0x1666) = 0;
    }
  }
LAB_004bc783:
  *unaff_FS_OFFSET = local_10;
  return;
}

