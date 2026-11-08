
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004bc7d0(void)

{
  float fVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  uint *puVar6;
  int *in_ECX;
  int *piVar7;
  uint uVar8;
  undefined4 *unaff_FS_OFFSET;
  float10 fVar9;
  undefined4 uVar10;
  wchar_t *pwVar11;
  undefined4 uVar12;
  undefined1 auStack_38 [16];
  undefined1 local_28 [4];
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c578ba;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_004edc00();
  iVar3 = FUN_00402060();
  if (iVar3 != 0) {
    local_14 = (float)FUN_00402060();
    iVar3 = FUN_00b06f00();
    if ((int)local_14 <= iVar3) {
      *(uint *)(in_ECX[0x656] * 4 + *(int *)(DAT_012101d8 + 0x44)) =
           in_ECX[0x656] * 4 + *(int *)(DAT_012101d8 + 0x44) ^ DAT_012101dc;
      *(uint *)(in_ECX[0x656] * 4 + *(int *)(DAT_012101d8 + 0x48)) =
           in_ECX[0x656] * 4 + *(int *)(DAT_012101d8 + 0x48) ^ DAT_012101dc;
      *(undefined1 *)((int)in_ECX + 0x193d) = 2;
    }
  }
  if (in_ECX[0x62] == -1) {
    iVar3 = (**(code **)(*in_ECX + 0x390))();
    if (iVar3 != 0) {
      (**(code **)(*in_ECX + 0x390))();
      iVar3 = FUN_00a2cf70();
      if (0 < iVar3) {
        (**(code **)(*in_ECX + 0x390))();
        iVar3 = FUN_00a2cf70();
        in_ECX[0x62] = iVar3;
        goto LAB_004bc905;
      }
    }
    iVar3 = (**(code **)(*in_ECX + 0x370))();
    if (iVar3 == 0) {
      uVar10 = FUN_00a530f0();
      (*(code *)PTR_FUN_00ff2ebc)(&DAT_00cd155c,uVar10);
      in_ECX[0x62] = 0;
    }
    else {
      uVar10 = 0;
      (**(code **)(*in_ECX + 0x370))(0,2,1);
      uVar10 = FUN_00a25c90(uVar10);
      iVar3 = FUN_00a242e0(uVar10);
      in_ECX[0x62] = iVar3;
    }
  }
LAB_004bc905:
  cVar2 = FUN_0049c090();
  if ((((((cVar2 != '\0') && (cVar2 = (**(code **)(*in_ECX + 0x3dc))(), cVar2 != '\0')) &&
        (iVar3 = FUN_00402060(), iVar3 != 4)) &&
       (((in_ECX[0x128] != 4 && (iVar3 = FUN_00402060(), iVar3 != 5)) &&
        ((in_ECX[0x128] != 5 && ((iVar3 = FUN_00402060(), iVar3 != 0xd && (in_ECX[0x128] != 0xd)))))
        ))) && (iVar3 = FUN_00402060(), iVar3 != 9)) && (in_ECX[0x128] != 9)) {
    local_24 = 0;
    local_20 = 0;
    local_1c = 0;
    local_8 = 0;
    iVar3 = (**(code **)(*in_ECX + 0x378))();
    if ((iVar3 == 0) && (iVar3 = (**(code **)(*in_ECX + 0x3a0))(), iVar3 == 0)) {
      cVar2 = (**(code **)(*in_ECX + 0x2c))(0x211);
      if (cVar2 == '\0') {
        cVar2 = (**(code **)(*in_ECX + 0x2c))(0x111);
        if (cVar2 != '\0') {
          local_14 = 0.0;
          goto LAB_004bca01;
        }
      }
      else {
        local_14 = 2.8026e-45;
LAB_004bca01:
        FUN_00407120(&local_14);
      }
      uVar10 = 5;
    }
    else {
      local_14 = 5.60519e-45;
      FUN_00407120(&local_14);
      local_14 = 0.0;
      FUN_00407120(&local_14);
      local_14 = 1.4013e-45;
      FUN_00407120(&local_14);
      FUN_00407120(&DAT_00cd1444);
      FUN_00407120(&DAT_00cd1448);
      uVar10 = 4;
    }
    (**(code **)(*in_ECX + 0x28c))(uVar10,local_28,3,0,0);
    local_8 = 0xffffffff;
    FUN_00644d50();
  }
  cVar2 = (**(code **)(*in_ECX + 0x3dc))();
  if (cVar2 != '\0') {
    (**(code **)(*in_ECX + 0x2d0))(0);
  }
  FUN_004ba120();
  (**(code **)(*in_ECX + 0x574))();
  iVar3 = FUN_00402060();
  if (iVar3 != -1) {
    iVar3 = FUN_00b06f00();
    iVar4 = FUN_00402060();
    if (iVar4 + 1000 < iVar3) {
      iVar3 = *in_ECX;
      uVar10 = FUN_00402060(1,0);
      (**(code **)(iVar3 + 1000))(uVar10);
    }
  }
  iVar3 = FUN_00402060();
  if (iVar3 != -1) {
    iVar3 = FUN_00b06f00();
    iVar4 = FUN_00402060();
    if (iVar4 + 1000 < iVar3) {
      iVar3 = *in_ECX;
      uVar10 = FUN_00402060(1);
      (**(code **)(iVar3 + 0x3f0))(uVar10);
    }
  }
  piVar7 = in_ECX + 0x4a5;
  iVar3 = 0x12;
  do {
    if (((int *)*piVar7 != (int *)0x0) &&
       (cVar2 = (**(code **)(*(int *)*piVar7 + 8))(), cVar2 != '\0')) {
      (**(code **)(*(int *)*piVar7 + 0x30))();
    }
    piVar7 = piVar7 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  FUN_00565cb0();
  (**(code **)(*in_ECX + 0x348))(2);
  uVar10 = FUN_00b06f00();
  cVar2 = FUN_00a51fb0(uVar10);
  if (cVar2 != '\0') {
    iVar3 = in_ECX[0x584];
    if (iVar3 != 0) {
      fVar9 = (float10)FUN_004333b0();
      local_18 = (float)fVar9;
      local_14 = (float)(**(code **)(*in_ECX + 0x584))(iVar3);
      iVar3 = FUN_00c01544();
      iVar4 = FUN_00402060();
      if (iVar3 != iVar4) {
        (**(code **)(*in_ECX + 0x588))(iVar3);
      }
    }
    iVar3 = in_ECX[0x585];
    if (iVar3 != 0) {
      fVar9 = (float10)FUN_004333b0();
      local_14 = (float)fVar9;
      local_18 = (float)(**(code **)(*in_ECX + 0x584))(iVar3);
      iVar3 = FUN_00c01544();
      iVar4 = FUN_00402060();
      if (iVar3 != iVar4) {
        (**(code **)(*in_ECX + 0x58c))(iVar3);
      }
    }
  }
  (**(code **)(*in_ECX + 0x580))();
  local_14 = (float)(**(code **)(*in_ECX + 0xdc))();
  local_18 = (float)(**(code **)(*in_ECX + 0xe0))();
  puVar6 = (uint *)(in_ECX + 0x557);
  if ((*puVar6 ^ DAT_012101dc) - (int)puVar6 != in_ECX[0x558]) {
    FUN_00b170b0(puVar6,0x3f);
  }
  iVar3 = in_ECX[0x558] * 4;
  uVar8 = *(int *)(DAT_012101d8 + 0x44) + iVar3 ^ *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3) ^
          DAT_012101dc;
  if (uVar8 != (*(int *)(DAT_012101d8 + 0x48) + iVar3 ^
                *(uint *)(*(int *)(DAT_012101d8 + 0x48) + iVar3) ^ DAT_012101dc)) {
    FUN_00b170b0(puVar6,0x40);
  }
  switch(uVar8) {
  case 0:
    if (in_ECX[0x6c] != 0) break;
    if ((local_14 == 5.60519e-45) && (local_18 == 5.60519e-45)) {
      iVar3 = FUN_00402060();
      if (iVar3 == 0) {
        local_18 = 1.4013e-45;
        FUN_00404560(&local_18);
        (**(code **)(*in_ECX + 0x494))(1,0,1000,1000,0x3f800000,0x3f800000);
        iVar3 = *in_ECX;
        uVar10 = (**(code **)(iVar3 + 0x390))();
        (**(code **)(iVar3 + 0x100))(uVar10);
        if (in_ECX[0x52] == 0) {
          iVar3 = (**(code **)(*in_ECX + 0x370))();
          if (iVar3 != 0) {
            iVar3 = *in_ECX;
            uVar10 = (**(code **)(iVar3 + 0x370))();
            (**(code **)(iVar3 + 0xf0))(uVar10);
            FUN_00a27360();
          }
          (**(code **)(*in_ECX + 0x110))(1);
        }
        else {
          FUN_00a319e0();
          (**(code **)(*in_ECX + 0x110))(1);
        }
      }
      break;
    }
    iVar3 = FUN_00402060();
    if (iVar3 != 0) {
      local_18 = 0.0;
      FUN_00404560(&local_18);
      (**(code **)(*in_ECX + 0x494))(1,1,1000,1000,0x3f800000,0x3f800000);
      iVar3 = (**(code **)(*in_ECX + 0x394))();
      if ((in_ECX[0x52] != iVar3) &&
         ((iVar3 = (**(code **)(*in_ECX + 0x394))(), iVar3 != 0 ||
          (iVar3 = (**(code **)(*in_ECX + 0x368))(), iVar3 != 0)))) {
        iVar3 = *in_ECX;
        uVar10 = (**(code **)(iVar3 + 0x394))();
        (**(code **)(iVar3 + 0x100))(uVar10);
      }
      if (in_ECX[0x52] == 0) {
        iVar3 = (**(code **)(*in_ECX + 0x368))();
        if ((iVar3 != 0) && (iVar3 = (**(code **)(*in_ECX + 0x370))(), iVar3 != 0)) {
          iVar3 = (**(code **)(*in_ECX + 0x370))();
          iVar4 = (**(code **)(*in_ECX + 0x368))();
          if (iVar4 != iVar3) {
            iVar3 = *in_ECX;
            uVar10 = (**(code **)(iVar3 + 0x368))();
            (**(code **)(iVar3 + 0xf0))(uVar10);
            FUN_00a27360();
          }
        }
      }
      else {
        FUN_00a319e0();
        (**(code **)(*in_ECX + 0xf0))(0);
      }
      cVar2 = (**(code **)(*in_ECX + 0x2c))(0x111);
      if (cVar2 != '\0') {
        if (DAT_010d3cc0 == 1) {
          pwVar11 = u_G_WALK_FLOOR_LOOP_00cd1538;
        }
        else {
          iVar3 = (**(code **)(*in_ECX + 0x5c))();
          uVar10 = *(undefined4 *)(*(int *)(*(int *)(iVar3 + 0x114) + 0xb4) + 0x34);
          iVar3 = (**(code **)(*in_ECX + 0x5c))();
          if (*(int *)(*(int *)(*(int *)(iVar3 + 0x114) + 0x50) + 0x60) == 0xc363) {
            uVar10 = 0x28;
          }
          switch(uVar10) {
          case 0xb:
          case 0xc:
          case 0xd:
          case 0xe:
          case 0xf:
          case 0x10:
          case 0x11:
          case 0x12:
          case 0x13:
          case 0x14:
          case 0x15:
          case 0x16:
          case 0x17:
          case 0x18:
          case 0x19:
          case 0x1a:
          case 0x1f:
          case 0x20:
          case 0x21:
          case 0x22:
          case 0x23:
          case 0x32:
          case 0x33:
            pwVar11 = u_WALK_STONE_LOOP_00cd0390;
            break;
          default:
            pwVar11 = u_WALK_SOIL_LOOP_00cd1518;
            break;
          case 0x28:
          case 0x29:
            (**(code **)(*in_ECX + 0x10c))(u_R_WALK_SNOW_LOOP_00cd036c,1,0,0);
            goto LAB_004bcf50;
          }
        }
        (**(code **)(*in_ECX + 0x10c))(pwVar11,1,0,0);
      }
    }
LAB_004bcf50:
    if (((in_ECX[0x617] == 7) && (in_ECX[0x40] != 0)) && (cVar2 = FUN_0043f700(), cVar2 != '\0')) {
      iVar3 = (**(code **)(*in_ECX + 0x4d0))(2);
      piVar7 = (int *)(&DAT_01002e78)[iVar3];
      iVar3 = (**(code **)(*in_ECX + 0xc0))();
      iVar4 = (**(code **)(*piVar7 + 0x1c))();
      *(char *)(iVar4 + 0x58) = '\x01' - (iVar3 != 0);
      iVar3 = *piVar7;
      uVar10 = (**(code **)(*in_ECX + 0x9c))();
      uVar10 = (**(code **)(*in_ECX + 0x98))(uVar10);
      uVar10 = (**(code **)(*in_ECX + 0x94))(uVar10);
      (**(code **)(iVar3 + 0x28))(uVar10);
      (**(code **)(*piVar7 + 0xc))(0);
      (**(code **)(*piVar7 + 0x5c))(auStack_38);
      local_8 = 1;
      FUN_0050e060(in_ECX,2,0,auStack_38,0);
      FUN_00404ef0();
      FUN_00b06f60(200,0);
      local_8 = 0xffffffff;
      FUN_00644d50();
    }
    break;
  case 1:
    if ((in_ECX[0x41] != 0) && (*(char *)(in_ECX[0x41] + 0x13a) != '\0')) {
      (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
    }
    break;
  case 3:
    iVar3 = FUN_00402060();
    iVar4 = FUN_00b06f00();
    if (iVar4 < iVar3) break;
    cVar2 = (**(code **)(*in_ECX + 0x410))(3);
    if (cVar2 != '\0') {
      (**(code **)(*in_ECX + 0x28c))(9,0,3);
      break;
    }
    goto LAB_004bd9f2;
  case 4:
    iVar3 = (**(code **)(*in_ECX + 0x9c))();
    iVar4 = FUN_00402060();
    if (iVar4 < iVar3) {
      local_18 = (float)(**(code **)(*in_ECX + 0x9c))();
      FUN_00404560(&local_18);
    }
    iVar3 = FUN_00402060();
    if (iVar3 == 0) {
      piVar7 = *(int **)in_ECX[0x3e];
      if (piVar7 == (int *)0x0) {
        piVar7 = (int *)in_ECX[0x3e] + 2;
      }
      fVar9 = (float10)(**(code **)(*piVar7 + 8))(2);
      if (((in_ECX[0x41] != 0) &&
          (iVar3 = *(int *)(in_ECX[0x41] + 0x124), fVar9 <= (float10)_DAT_00ccb260)) &&
         (iVar4 = FUN_00402060(), iVar3 == iVar4)) {
        iVar3 = FUN_00402060();
        iVar4 = FUN_00402060();
        if (iVar4 != iVar3) {
          iVar3 = (**(code **)(*in_ECX + 0x104))();
          if (iVar3 == 0) {
            iVar3 = FUN_00402060();
            FUN_004ba360(iVar3 + 1);
          }
          else {
            iVar3 = FUN_00402060();
            iVar3 = iVar3 + 1;
            (**(code **)(*in_ECX + 0x104))(iVar3);
            FUN_00a305b0(iVar3);
          }
        }
      }
      if (((*(int *)(in_ECX[0x3e] + 0xec) == 4) && (in_ECX[0x5c7] != -1)) &&
         (iVar3 = (**(code **)(*in_ECX + 0x94))(), in_ECX[0x5c7] != iVar3)) {
        iVar3 = FUN_00402060();
        iVar3 = (int)((ulonglong)((longlong)iVar3 * -0x66666667) >> 0x20);
        local_18 = (float)((iVar3 >> 1) - (iVar3 >> 0x1f));
        FUN_00404560(&local_18);
        local_18 = (float)FUN_00402060();
        FUN_00511040(0,(float)(int)local_18);
        in_ECX[0x5c7] = -1;
      }
      cVar2 = FUN_0049c090();
      if (cVar2 != '\0') {
        piVar7 = *(int **)in_ECX[0x3e];
        if (piVar7 == (int *)0x0) {
          piVar7 = (int *)in_ECX[0x3e] + 2;
        }
        fVar9 = (float10)(**(code **)(*piVar7 + 8))(2);
        if (((fVar9 < (float10)_DAT_00e9d7a4) && (*(int *)(in_ECX[0x3e] + 0xf4) == 4)) &&
           (in_ECX[0x6c] == 0)) {
          if (((in_ECX[0x59b] == -1) || (iVar3 = FUN_00b06f00(), iVar3 < in_ECX[0x59b])) ||
             (cVar2 = (**(code **)(*in_ECX + 0x3dc))(), cVar2 != '\0')) {
            local_1c = 0;
            local_20 = 0;
            local_24 = 0;
            if (in_ECX[0x5ca] == 2) {
              local_8 = 2;
              local_18 = 5.60519e-45;
              FUN_00407120(&local_18);
              local_18 = 0.0;
              FUN_00407120(&local_18);
              local_18 = 1.4013e-45;
              FUN_00407120(&local_18);
              local_18 = (float)FUN_00402060();
              FUN_00407120(&local_18);
              local_18 = (float)FUN_00402060();
            }
            else {
              local_8 = 3;
              local_18 = 5.60519e-45;
              FUN_00407120(&local_18);
              local_18 = 1.4013e-45;
              FUN_00407120(&local_18);
              local_18 = 0.0;
              FUN_00407120(&local_18);
              local_18 = (float)FUN_00402060();
              FUN_00407120(&local_18);
              iVar3 = FUN_00402060();
              local_18 = (float)(iVar3 / 5);
            }
            FUN_00407120(&local_18);
            (**(code **)(*in_ECX + 0x28c))(4,local_28,3,0,0);
            local_8 = 0xffffffff;
            FUN_00644d50();
          }
          else {
            FUN_004ba380();
          }
        }
      }
      break;
    }
    iVar3 = FUN_00402060();
    if (iVar3 == 1) {
      piVar7 = *(int **)in_ECX[0x3e];
      if (piVar7 == (int *)0x0) {
        piVar7 = (int *)in_ECX[0x3e] + 2;
      }
      fVar9 = (float10)(**(code **)(*piVar7 + 8))(2);
      if (((in_ECX[0x41] != 0) &&
          (iVar3 = *(int *)(in_ECX[0x41] + 0x124), fVar9 <= (float10)_DAT_00ccb260)) &&
         (iVar4 = FUN_00402060(), iVar3 == iVar4)) {
        iVar3 = FUN_00402060();
        iVar4 = FUN_00402060();
        if (iVar4 != iVar3) {
          iVar3 = (**(code **)(*in_ECX + 0x104))();
          if (iVar3 == 0) {
            iVar3 = FUN_00402060();
            FUN_004ba360(iVar3 + 1);
          }
          else {
            iVar3 = FUN_00402060();
            iVar3 = iVar3 + 1;
            (**(code **)(*in_ECX + 0x104))(iVar3);
            FUN_00a305b0(iVar3);
          }
        }
      }
      cVar2 = FUN_0049c090();
      if (cVar2 == '\0') break;
      piVar7 = *(int **)in_ECX[0x3e];
      if (piVar7 == (int *)0x0) {
        piVar7 = (int *)in_ECX[0x3e] + 2;
      }
      fVar9 = (float10)(**(code **)(*piVar7 + 8))(2);
      if ((((float10)_DAT_00e9d7a4 <= fVar9) || (*(int *)(in_ECX[0x3e] + 0xf4) != 4)) ||
         (in_ECX[0x6c] != 0)) break;
      if (((in_ECX[0x59b] != -1) && (iVar3 = FUN_00b06f00(), in_ECX[0x59b] <= iVar3)) &&
         (cVar2 = (**(code **)(*in_ECX + 0x3dc))(), cVar2 == '\0')) {
        FUN_004ba380();
        break;
      }
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      local_8 = 4;
      local_18 = 5.60519e-45;
      FUN_00407120(&local_18);
      local_18 = 2.8026e-45;
      FUN_00407120(&local_18);
      local_18 = 0.0;
      FUN_00407120(&local_18);
      local_18 = 0.0;
      FUN_00407120(&local_18);
      local_18 = 0.0;
      FUN_00407120(&local_18);
      uVar12 = 3;
      uVar10 = 4;
    }
    else {
      iVar3 = FUN_00402060();
      if ((iVar3 != 2) || (cVar2 = FUN_0049c090(), cVar2 == '\0')) break;
      cVar2 = (**(code **)(*in_ECX + 0x3dc))();
      if ((cVar2 == '\0') || (((in_ECX[0x128] == 5 || (in_ECX[0x128] == 4)) || (in_ECX[0x6c] != 0)))
         ) {
        iVar3 = (**(code **)(*in_ECX + 0xf4))();
        if (((iVar3 != 0) &&
            (iVar3 = (**(code **)(*in_ECX + 0xf4))(), *(char *)(iVar3 + 0x13a) != '\0')) ||
           ((in_ECX[0x59b] != -1 && (iVar3 = FUN_00b06f00(), in_ECX[0x59b] <= iVar3)))) {
          FUN_004ba380();
        }
        break;
      }
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      local_8 = 5;
      local_18 = 1.4013e-45;
      FUN_00407120(&local_18);
      uVar12 = 3;
      uVar10 = 5;
    }
    goto LAB_004bd8f7;
  case 5:
    cVar2 = (**(code **)(*in_ECX + 0x2c))(0x211);
    if (((cVar2 != '\0') && (cVar2 = (**(code **)(*in_ECX + 0x5a0))(), cVar2 == '\0')) &&
       (*(int *)(DAT_01002848 + 0x19a8) != 2)) {
      FUN_00511040(2,0);
    }
    break;
  case 6:
    iVar3 = FUN_00402060();
    if (iVar3 == 0) {
      iVar3 = (**(code **)(*in_ECX + 0xf4))();
      if (iVar3 == 0) break;
      iVar3 = (**(code **)(*in_ECX + 0xf4))();
      iVar3 = *(int *)(iVar3 + 0x124);
      iVar4 = (**(code **)(*in_ECX + 0x4b8))();
      if (iVar3 < iVar4) break;
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      local_8 = 6;
      local_18 = 1.4013e-45;
      FUN_00407120(&local_18);
      local_18 = 0.0;
      FUN_00407120(&local_18);
      (**(code **)(*in_ECX + 0x344))(3);
      local_18 = (float)FUN_004bdd80();
    }
    else {
      iVar3 = FUN_00402060();
      if (iVar3 != 1) {
        iVar3 = FUN_00402060();
        if (iVar3 != 2) break;
        iVar3 = FUN_00402060();
        if (iVar3 != 0) {
          iVar3 = FUN_00402060();
          iVar4 = FUN_00b06f00();
          if (iVar3 <= iVar4) {
            (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
          }
          break;
        }
        iVar3 = (**(code **)(*in_ECX + 0xf4))();
        if (iVar3 == 0) break;
        iVar3 = (**(code **)(*in_ECX + 0xf4))();
        goto LAB_004bd9e2;
      }
      iVar3 = FUN_00402060();
      fVar1 = local_14;
      if ((((iVar3 == 0) && (local_14 != 5.60519e-45)) &&
          (fVar5 = (float)(**(code **)(*in_ECX + 0xc0))(), fVar1 != fVar5)) &&
         ((iVar3 = FUN_00402060(), iVar3 == 0 && (iVar3 = FUN_00402060(), iVar3 == 0)))) {
        (**(code **)(*in_ECX + 0xbc))(fVar1);
        (**(code **)(*in_ECX + 0xb8))(fVar1);
      }
      iVar3 = (**(code **)(*in_ECX + 0xf4))();
      if (iVar3 != 0) {
        iVar3 = (**(code **)(*in_ECX + 0x380))();
        iVar4 = (**(code **)(*in_ECX + 0xf4))();
        if (iVar4 == iVar3) {
          piVar7 = *(int **)in_ECX[0x3e];
          if (piVar7 == (int *)0x0) {
            piVar7 = (int *)in_ECX[0x3e] + 2;
          }
          fVar9 = (float10)(**(code **)(*piVar7 + 8))(2);
          local_18 = (float)fVar9;
          iVar3 = (**(code **)(*in_ECX + 0xf4))();
          iVar3 = *(int *)(iVar3 + 0x124);
          if ((local_18 <= (float)_DAT_00ccb260) &&
             (iVar4 = (**(code **)(*in_ECX + 0x4bc))(), iVar3 < iVar4)) {
            iVar3 = (**(code **)(*in_ECX + 0x104))();
            if (iVar3 == 0) {
              uVar10 = (**(code **)(*in_ECX + 0x4bc))();
              FUN_004ba360(uVar10);
            }
            else {
              uVar10 = (**(code **)(*in_ECX + 0x4bc))();
              (**(code **)(*in_ECX + 0x104))(uVar10);
              FUN_00a305b0(uVar10);
            }
            uVar10 = (**(code **)(*in_ECX + 0x4bc))();
            FUN_004ba360(uVar10);
          }
        }
      }
      piVar7 = *(int **)in_ECX[0x3e];
      if (piVar7 == (int *)0x0) {
        piVar7 = (int *)in_ECX[0x3e] + 2;
      }
      fVar9 = (float10)(**(code **)(*piVar7 + 8))(2);
      if (((float10)_DAT_00e9d7a4 <= fVar9) || (*(int *)(in_ECX[0x3e] + 0xf4) != 4)) break;
      local_24 = 0;
      local_20 = 0;
      local_1c = 0;
      local_8 = 7;
      local_18 = 2.8026e-45;
      FUN_00407120(&local_18);
      iVar3 = FUN_00402060();
      local_18 = (float)(uint)(iVar3 != 0);
      FUN_00407120(&local_18);
      local_18 = 0.0;
    }
    FUN_00407120(&local_18);
    uVar12 = 0;
    uVar10 = 6;
LAB_004bd8f7:
    (**(code **)(*in_ECX + 0x28c))(uVar10,local_28,uVar12,0,0);
    local_8 = 0xffffffff;
    FUN_00644d50();
    break;
  case 7:
    iVar3 = (**(code **)(*in_ECX + 0xf4))();
    if ((iVar3 == 0) || (iVar3 = (**(code **)(*in_ECX + 0xf4))(), *(char *)(iVar3 + 0x13a) == '\0'))
    {
      if (*(int *)(in_ECX[0x3e] + 0xf4) == 4) {
        (**(code **)(*in_ECX + 0x468))(1);
      }
    }
    else {
      (**(code **)(*in_ECX + 0x468))(0);
    }
    break;
  case 8:
    iVar3 = in_ECX[0x41];
    if (iVar3 == 0) break;
LAB_004bd9e2:
    if (*(char *)(iVar3 + 0x13a) == '\0') break;
LAB_004bd9f2:
    (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
  }
  piVar7 = in_ECX + 0x643;
  if ((in_ECX[0x643] ^ DAT_012101dc) - (int)piVar7 != in_ECX[0x644]) {
    FUN_00b170b0(piVar7,0x3f);
  }
  iVar3 = in_ECX[0x644] * 4;
  puVar6 = (uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48));
  uVar8 = *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar3) ^ *(int *)(DAT_012101d8 + 0x44) + iVar3 ^
          DAT_012101dc;
  if (uVar8 != ((uint)puVar6 ^ DAT_012101dc ^ *puVar6)) {
    FUN_00b170b0(piVar7,0x40);
  }
  if (uVar8 != 0) {
    iVar3 = FUN_00402060();
    iVar4 = FUN_00b06f00();
    if (iVar3 <= iVar4) {
      puVar6 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x644] * 4);
      *puVar6 = (uint)puVar6 ^ DAT_012101dc;
      puVar6 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x644] * 4);
      *puVar6 = (uint)puVar6 ^ DAT_012101dc;
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

