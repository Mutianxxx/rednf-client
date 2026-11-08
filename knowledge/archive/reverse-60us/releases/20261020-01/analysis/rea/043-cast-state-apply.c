
void FUN_004de370(int param_1,int param_2,undefined4 param_3,uint param_4)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  wchar_t *pwVar13;
  undefined4 uVar14;
  undefined **ppuVar15;
  undefined4 uVar16;
  undefined **ppuVar17;
  undefined1 *puVar18;
  int aiStack_40 [4];
  undefined1 auStack_30 [4];
  int iStack_2c;
  int iStack_28;
  undefined4 uStack_24;
  float fStack_20;
  int iStack_1c;
  undefined4 uStack_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_00c587be;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_14 = FUN_00402060();
  switch(local_14) {
  case 10:
    iVar7 = FUN_00402060();
    if (iVar7 == 0) {
      (**(code **)(*in_ECX + 0x558))();
    }
    break;
  case 0xb:
    (**(code **)(*in_ECX + 0x110))(0x10);
    if (in_ECX == DAT_0104f1d4) {
      FUN_009cca00(0x21,0,1);
      FUN_009cd3e0(500);
    }
    break;
  case 0xe:
    if ((in_ECX[0x93a] != -1) && (iVar7 = (**(code **)(*in_ECX + 0x67c))(in_ECX[0x93a]), iVar7 != 0)
       ) {
      iVar4 = *in_ECX;
      if (param_1 == 0) {
        uVar2 = (**(code **)(iVar4 + 0x64c))(in_ECX[0x93a]);
        (**(code **)(iVar4 + 0x790))(iVar7,uVar2);
      }
      else {
        uVar2 = (**(code **)(iVar4 + 0x64c))(in_ECX[0x93a]);
        (**(code **)(iVar4 + 0x794))(iVar7,uVar2);
      }
    }
    (**(code **)(*in_ECX + 0xfc))(in_ECX[0x93c]);
    (**(code **)(*in_ECX + 0x558))();
    break;
  case 0xf:
    (**(code **)(*in_ECX + 0x2d8))(1);
    (**(code **)(*in_ECX + 0xfc))(in_ECX[0x9a0]);
  }
  iVar7 = param_2;
  switch(param_1) {
  case 5:
    *(undefined1 *)(in_ECX + 0x939) = 0;
    break;
  case 10:
    FUN_00402060();
    fStack_20 = **(float **)(iVar7 + 4);
    FUN_00404560(&fStack_20);
    iVar4 = FUN_00402060();
    if (iVar4 == 0) {
      in_ECX[0x90a] = *(int *)(*(int *)(iVar7 + 4) + 4);
      fStack_20 = *(float *)(*(int *)(iVar7 + 4) + 8);
      FUN_00404560(&fStack_20);
      fStack_20 = *(float *)(*(int *)(iVar7 + 4) + 0xc);
      FUN_00404560(&fStack_20);
      fStack_20 = *(float *)(*(int *)(iVar7 + 4) + 0x10);
      FUN_00404560(&fStack_20);
      in_ECX[0x911] = *(int *)(*(int *)(iVar7 + 4) + 0x14);
      fStack_20 = *(float *)(*(int *)(iVar7 + 4) + 0x18);
      in_ECX[0x912] = *(int *)(*(int *)(iVar7 + 4) + 0x1c);
      uVar3 = FUN_00466790();
      if (uVar3 < 9) {
        iStack_1c = 1000;
      }
      else {
        iStack_1c = *(int *)(*(int *)(iVar7 + 4) + 0x20);
      }
      uVar3 = FUN_00466790();
      if (uVar3 < 10) {
        iVar4 = 1000;
      }
      else {
        iVar4 = *(int *)(*(int *)(iVar7 + 4) + 0x24);
      }
      in_ECX[0x913] = iVar4;
      uVar3 = FUN_00466790();
      if (uVar3 < 0xb) {
        uStack_18 = 0xffffffff;
      }
      else {
        uStack_18 = *(undefined4 *)(*(int *)(iVar7 + 4) + 0x28);
      }
      FUN_00404560(&uStack_18);
      iVar7 = *in_ECX;
      if (in_ECX[0x90a] == 2) {
        uVar2 = (**(code **)(iVar7 + 0x36c))();
      }
      else {
        uVar2 = (**(code **)(iVar7 + 0x5e0))(in_ECX[0x911]);
      }
      (**(code **)(iVar7 + 0xf0))(uVar2);
      (**(code **)(*in_ECX + 0x494))(fStack_20,fStack_20,iStack_1c,iStack_1c,0x3f800000,0x3f800000);
      iVar7 = FUN_00402060();
      iVar4 = FUN_00402060();
      iStack_1c = (iVar4 * 1000) / iVar7;
      FUN_00404560(&iStack_1c);
      if (fStack_20 == 5.60519e-45) {
        iVar7 = *in_ECX;
        uVar2 = FUN_00402060(0);
        (**(code **)(iVar7 + 0x554))(uVar2);
      }
      iVar7 = FUN_00402060();
      if (iVar7 == 0) {
        iVar7 = FUN_00493660();
        FUN_004ba360(iVar7 + -1);
        fStack_20 = 9.80909e-44;
        FUN_00404560(&fStack_20);
      }
      if ((in_ECX[0x90a] == 1) || (iVar7 = param_2, in_ECX[0x90a] == 2)) {
        cVar1 = FUN_0049c090();
        if ((cVar1 != '\0') &&
           ((cVar1 = (**(code **)(*in_ECX + 0x34))(), cVar1 != '\0' && (in_ECX[0x9d1] != 0)))) {
          uVar2 = FUN_00402060();
          uVar2 = FUN_0047d620(uVar2);
          uVar2 = FUN_004044b0(uVar2);
          FUN_004c3280(uVar2);
        }
        if ((DAT_0104f1d4 == in_ECX) && (in_ECX[0x9d1] != 0)) {
          uVar2 = FUN_00402060();
          iVar7 = FUN_0047d620(uVar2);
          if (iVar7 != -1) {
            piVar5 = (int *)FUN_004044b0(iVar7);
            (**(code **)(*piVar5 + 0x68))();
          }
        }
        in_ECX[0x926] = (local_14 == 10) + 1;
        iVar7 = param_2;
      }
    }
    else {
      iVar4 = FUN_00402060();
      if (iVar4 == 1) {
        iVar4 = *in_ECX;
        if (in_ECX[0x90a] == 2) {
          uVar2 = (**(code **)(iVar4 + 0x36c))();
        }
        else {
          uVar2 = (**(code **)(iVar4 + 0x5e4))(in_ECX[0x911]);
        }
        (**(code **)(iVar4 + 0xf0))(uVar2);
        (**(code **)(*in_ECX + 0x494))
                  (in_ECX[0x912],in_ECX[0x912],in_ECX[0x913],in_ECX[0x913],0x3f800000,0x3f800000);
        iVar4 = FUN_00402060();
        if (iVar4 != -1) {
          param_2 = FUN_00402060();
          iVar4 = FUN_00402060();
          param_2 = (iVar4 * 1000) / param_2;
          FUN_00404560(&param_2);
        }
        iVar4 = FUN_00402060();
        if (iVar4 == -1) {
          in_ECX[0x916] = 0;
        }
        else {
          uVar3 = FUN_00466790();
          if (uVar3 < 2) {
            in_ECX[0x916] = (int)in_ECX;
          }
          else {
            uVar9 = 0;
            ppuVar17 = &PTR_PTR_00f5528c;
            ppuVar15 = &PTR_PTR_00f40910;
            uVar8 = 0;
            uVar2 = FUN_0050b8b0(*(undefined4 *)(*(int *)(iVar7 + 4) + 4));
            iVar4 = FUN_00c00d0b(uVar2,uVar8,ppuVar15,ppuVar17,uVar9);
            in_ECX[0x916] = iVar4;
          }
        }
      }
      else {
        iVar4 = FUN_00402060();
        if (iVar4 == 2) {
          uVar3 = 0;
          in_ECX[0x916] = 0;
          iStack_2c = 0;
          iStack_28 = 0;
          uStack_24 = 0;
          puVar18 = auStack_30;
          uStack_8 = 0;
          uVar2 = FUN_00402060(puVar18);
          FUN_004d5eb0(uVar2,puVar18);
          aiStack_40[0] = 2;
          aiStack_40[1] = 1;
          aiStack_40[2] = 3;
          aiStack_40[3] = 0;
          fStack_20 = (float)(iStack_2c - (int)aiStack_40);
          do {
            if ((iStack_2c == 0) || ((uint)(iStack_28 - iStack_2c >> 2) <= uVar3)) {
              param_2 = 0;
            }
            else {
              param_2 = *(int *)((int)aiStack_40 + (int)fStack_20 + uVar3 * 4);
            }
            piVar5 = (int *)FUN_004e28a0(aiStack_40[uVar3]);
            uVar3 = uVar3 + 1;
            *piVar5 = param_2;
          } while ((int)uVar3 < 4);
          param_4 = param_4 & 0xffffff00;
          uStack_8 = 0xffffffff;
          FUN_00644d50();
        }
      }
    }
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    FUN_004ba0c0(2,0);
    *(undefined1 *)(in_ECX + 0x91b) = 0;
    break;
  case 0xb:
    if ((char)in_ECX[0x930] == '\0') goto LAB_004dea32;
    iVar4 = (**(code **)(*in_ECX + 0x5c))();
    iVar4 = *(int *)(*(int *)(*(int *)(iVar4 + 0x114) + 0xb4) + 0x34);
    iVar6 = (**(code **)(*in_ECX + 0x5c))();
    if ((iVar4 == 0x28) || (*(int *)(*(int *)(*(int *)(iVar6 + 0x114) + 0x50) + 0x60) == 0xc363)) {
      pwVar13 = u_R_RUN_SNOW_LOOP_00cd4150;
LAB_004dea2a:
      (**(code **)(*in_ECX + 0x10c))(pwVar13,0x10,0,0);
    }
    else {
      (**(code **)(*in_ECX + 0x344))(3);
      iVar4 = FUN_004bddc0();
      if (DAT_010d3cc0 != 0) {
        pwVar13 = u_G_RUN_FLOOR_LOOP_00cd41cc;
        goto LAB_004dea2a;
      }
      if (iVar4 < 60000) {
        (**(code **)(*in_ECX + 0x10c))(u_RUN_STONE_LOOP_00cd41ac);
      }
      else {
        if (iVar4 < 100000) {
          pwVar13 = u_RUN_SOIL_LOOP_00cd4190;
          goto LAB_004dea2a;
        }
        (**(code **)(*in_ECX + 0x10c))(u_RUN_GRASS_LOOP_00cd4170,0x10,0,0);
      }
    }
LAB_004dea32:
    iVar4 = *in_ECX;
    uVar2 = (**(code **)(iVar4 + 0x5e8))();
    (**(code **)(iVar4 + 0xf0))(uVar2);
    (**(code **)(*in_ECX + 0x488))(0,0x11e,0xee,1,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0x88,0x72,1,0,0);
    (**(code **)(*in_ECX + 0x494))(1,1,1000,1000,0x3f800000,0x3f800000);
    FUN_004ba0c0(2,0);
    break;
  case 0xc:
    (**(code **)(*in_ECX + 0x660))();
    iVar4 = *in_ECX;
    uVar2 = (**(code **)(iVar4 + 0x77c))();
    (**(code **)(iVar4 + 0x198))(uVar2);
    iVar4 = *in_ECX;
    uVar2 = (**(code **)(iVar4 + 0x5ec))();
    (**(code **)(iVar4 + 0xf0))(uVar2);
    (**(code **)(*in_ECX + 0x494))(1,2,1000,1000,0x3f800000,0x3f800000);
    uVar2 = (**(code **)(*in_ECX + 0x780))();
    iVar4 = FUN_00a24ce0(uVar2);
    piVar5 = *(int **)in_ECX[0x3e];
    if (piVar5 == (int *)0x0) {
      piVar5 = (int *)in_ECX[0x3e] + 2;
    }
    (**(code **)(*piVar5 + 8))(0);
    param_2 = FUN_00c01544();
    (**(code **)(*in_ECX + 0x488))(0,param_2,param_2,0,(param_2 * -1000) / iVar4,1);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    iVar4 = *in_ECX;
    uVar2 = (**(code **)(iVar4 + 0xc0))(4,0);
    (**(code **)(iVar4 + 0x49c))(uVar2);
    break;
  case 0xd:
    iVar7 = *in_ECX;
    uVar2 = (**(code **)(iVar7 + 0x5f0))();
    (**(code **)(iVar7 + 0xf0))(uVar2);
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    FUN_004ba0c0(2,0);
    FUN_012ee7c9();
    return;
  case 0xe:
    iVar4 = *in_ECX;
    in_ECX[0x93a] = **(int **)(param_2 + 4);
    uVar2 = (**(code **)(iVar4 + 0x5f4))();
    (**(code **)(iVar4 + 0xf0))(uVar2);
    (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x49c))(4,4,0);
    FUN_004ba0c0(2,0);
    uVar2 = (**(code **)(*in_ECX + 0x64c))(in_ECX[0x93a]);
    iVar4 = in_ECX[0x93a];
    piVar5 = in_ECX;
    (**(code **)(*in_ECX + 0x67c))(iVar4);
    iVar4 = FUN_00468430(iVar4,piVar5);
    param_2 = *(int *)(in_ECX[0x41] + 0x90);
    fStack_20 = (float)param_2 / (float)iVar4;
    (**(code **)(*in_ECX + 0x494))(0,4,1000,1000,0x3f800000,fStack_20,uVar2);
    if (in_ECX[0x93b] == 0) {
      fStack_20 = (float)FUN_00403c50(0x1b4);
      uStack_8 = 1;
      if (fStack_20 == 0.0) {
        piVar5 = (int *)0x0;
      }
      else {
        piVar5 = (int *)FUN_00453320(u_Common_CommonEffect_Particle_Buf_00cd40e8,in_ECX);
      }
      in_ECX[0x93b] = (int)piVar5;
      uStack_8 = 0xffffffff;
      (**(code **)(*piVar5 + 0x70))();
    }
    if (in_ECX[0x93c] == 0) {
      fStack_20 = (float)FUN_00403c50(0x1e8);
      uStack_8 = 2;
      if (fStack_20 == 0.0) {
        iVar4 = 0;
      }
      else {
        iVar4 = FUN_004936d0(u_Common_CommonEffect_Animation_Bu_00cd4080,1);
      }
      uStack_8 = 0xffffffff;
      in_ECX[0x93c] = iVar4;
    }
    (**(code **)(*(int *)in_ECX[0x93b] + 0xc))(0);
    iVar4 = *in_ECX;
    iVar6 = (**(code **)(iVar4 + 0xe4))(1,0,0,0,0,1);
    (**(code **)(iVar4 + 0xf8))(1,in_ECX[0x93c],0,-0x1e - iVar6);
    (**(code **)(*in_ECX + 0x10c))(u_MOON_CURTAIN_LIGHT_00cd4054,0xffffffff,0,0);
    (**(code **)(*in_ECX + 0x554))(param_2,1);
    break;
  case 0xf:
    cVar1 = FUN_004e2560();
    if (cVar1 == '\0') {
      piVar5 = *(int **)(iVar7 + 4);
      (**(code **)(*in_ECX + 0x67c))(0xbe);
      iVar4 = FUN_00402060();
      if (*piVar5 == iVar4) {
        uVar16 = 0xc;
        uVar14 = 0xffffffff;
        uVar12 = 0xffffffff;
        uVar11 = 0;
        uVar10 = 0xbe;
        uVar2 = (**(code **)(*in_ECX + 0x64c))(0xbe,0,0xffffffff,0xffffffff,0xc,0,0);
        uVar9 = 0;
        uVar8 = 0xbe;
        (**(code **)(*in_ECX + 0x67c))(0xbe,0,uVar2);
        iVar4 = FUN_00550080(uVar8,uVar9,uVar2,uVar10,uVar11,uVar12,uVar14,uVar16);
        in_ECX[0x9a2] = iVar4;
        (**(code **)(*in_ECX + 0xf0))(in_ECX[0x492]);
        (**(code **)(*in_ECX + 0x2d8))(0);
      }
    }
  }
  FUN_004bad60(param_1,iVar7,param_3,param_4);
  switch(param_1) {
  case 0:
    if ((in_ECX[0x40] != 0) && (iVar7 = FUN_00402060(), iVar7 != 1)) {
      iVar7 = *in_ECX;
      uVar2 = (**(code **)(iVar7 + 0x5dc))();
      (**(code **)(iVar7 + 0xf0))(uVar2);
      FUN_00a27360();
    }
    break;
  case 4:
    cVar1 = FUN_0049c090();
    if (((cVar1 == '\0') || (local_14 != 4)) || (iVar7 = (**(code **)(*in_ECX + 0x9c))(), iVar7 < 1)
       ) break;
    iVar7 = 0;
    param_2 = 0;
    iVar4 = (**(code **)(*in_ECX + 0x644))(1);
    if (iVar4 != 4) {
      iVar7 = FUN_00402060();
      param_2 = iVar7;
    }
    iVar4 = (**(code **)(*in_ECX + 0x644))(0);
    if (iVar4 == 4) {
      iVar4 = *in_ECX;
      uVar2 = FUN_00402060(0,0,0);
      uVar2 = FUN_00402060(uVar2);
      (**(code **)(iVar4 + 0x488))(0,uVar2);
    }
    else {
      iVar4 = (**(code **)(*in_ECX + 0x644))();
      iVar6 = (**(code **)(*in_ECX + 0xc0))();
      if (iVar4 == iVar6) {
        iVar7 = *in_ECX;
        param_4 = FUN_00402060(0,0,0);
        iVar4 = FUN_00402060();
        iVar4 = FUN_00402060(iVar4 - param_4);
        iVar6 = FUN_00402060();
        (**(code **)(iVar7 + 0x488))(0,iVar6 - iVar4);
        iVar7 = param_2;
      }
      else {
        uVar2 = (**(code **)(*in_ECX + 0xc0))();
        iVar4 = FUN_00447960(uVar2);
        iVar6 = (**(code **)(*in_ECX + 0x644))(0);
        if (iVar6 == iVar4) {
          iVar7 = *in_ECX;
          param_4 = FUN_00402060(0,0,0);
          iVar4 = FUN_00402060();
          iVar4 = FUN_00402060(param_4 + iVar4);
          iVar6 = FUN_00402060();
          (**(code **)(iVar7 + 0x488))(0,iVar4 + iVar6);
          iVar7 = param_2;
        }
      }
    }
    if (iVar7 == 0) break;
    (**(code **)(*in_ECX + 0x488))(1,iVar7,iVar7,0,0,0);
    iVar7 = *in_ECX;
    uVar2 = (**(code **)(iVar7 + 0x644))(1,0);
    uVar2 = (**(code **)(*in_ECX + 0xc0))(uVar2);
    uVar2 = FUN_00447960(uVar2);
    goto LAB_004df22d;
  case 6:
    iVar7 = FUN_00402060();
    if ((iVar7 == 0) && (local_14 == 0xb)) {
      param_2 = 0x11e;
      FUN_00404560(&param_2);
      param_2 = 0xee;
      FUN_00404560(&param_2);
      param_2 = 0x88;
      FUN_00404560(&param_2);
      param_2 = 0x72;
      FUN_00404560(&param_2);
    }
    break;
  case 8:
    iVar7 = FUN_00402060();
    if ((iVar7 < 1) && (local_14 != 8)) break;
    iVar7 = 0;
    iVar4 = 0;
    cVar1 = FUN_0049c090();
    if (cVar1 != '\0') {
      param_2 = (**(code **)(*in_ECX + 0x644))(0);
      if (param_2 == 4) {
        iVar7 = in_ECX[0x92c];
        iVar4 = in_ECX[0x92d];
      }
      else {
        iVar6 = (**(code **)(*in_ECX + 0xc0))();
        if (param_2 == iVar6) {
          iVar7 = in_ECX[0x92e];
          iVar4 = in_ECX[0x92f];
        }
      }
    }
    (**(code **)(*in_ECX + 0x488))(0,iVar7,iVar7,0,iVar4,1);
    (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
    (**(code **)(*in_ECX + 0x494))(2,2,1000,1000,0x3f800000,0x3f800000);
    iVar7 = *in_ECX;
    uVar2 = (**(code **)(iVar7 + 0xc0))(4,0);
LAB_004df22d:
    (**(code **)(iVar7 + 0x49c))(uVar2);
  }
  (**(code **)(*in_ECX + 0x65c))();
  iVar7 = FUN_00402060();
  if (iVar7 == param_1) {
    piVar5 = in_ECX + 0x53b;
    iVar7 = 0x13;
    do {
      if ((int *)*piVar5 != (int *)0x0) {
        (**(code **)(*(int *)*piVar5 + 0x198))(4,0,0,0,0,0);
      }
      piVar5 = piVar5 + 1;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

