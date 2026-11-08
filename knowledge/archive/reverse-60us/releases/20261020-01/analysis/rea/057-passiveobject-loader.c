
void FUN_0049f4d0(undefined4 param_1,int param_2)

{
  uint *puVar1;
  undefined4 *puVar2;
  char cVar3;
  int *piVar4;
  wchar_t *pwVar5;
  int iVar6;
  int iVar7;
  DWORD DVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int *piVar11;
  int iVar12;
  int *in_ECX;
  uint uVar13;
  undefined4 *unaff_FS_OFFSET;
  wchar_t *pwVar14;
  int *local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined1 local_1c;
  int *local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c56bdb;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  piVar4 = (int *)FUN_00b7ce30();
  if (piVar4 == (int *)0x0) {
    (*(code *)PTR_FUN_00ff2ebc)();
    *unaff_FS_OFFSET = local_10;
    return;
  }
  if (((char)piVar4[0x5d] == '\0') || (cVar3 = FUN_0043a5d0(), cVar3 != '\0')) {
    FUN_00a530f0();
    FUN_00bffdcd();
    FUN_00402e80();
    in_ECX[0x151] = param_2;
    in_ECX[0x81] = *piVar4;
    FUN_00a53490();
    uVar13 = piVar4[2];
    *(uint *)(in_ECX[0x84] * 4 + *(int *)(DAT_012101d8 + 0x44)) =
         in_ECX[0x84] * 4 + *(int *)(DAT_012101d8 + 0x44) ^ DAT_012101dc ^ uVar13;
    *(uint *)(in_ECX[0x84] * 4 + *(int *)(DAT_012101d8 + 0x48)) =
         in_ECX[0x84] * 4 + *(int *)(DAT_012101d8 + 0x48) ^ DAT_012101dc ^ uVar13;
    uVar13 = piVar4[3];
    *(uint *)(in_ECX[0x86] * 4 + *(int *)(DAT_012101d8 + 0x44)) =
         in_ECX[0x86] * 4 + *(int *)(DAT_012101d8 + 0x44) ^ DAT_012101dc ^ uVar13;
    *(uint *)(in_ECX[0x86] * 4 + *(int *)(DAT_012101d8 + 0x48)) =
         in_ECX[0x86] * 4 + *(int *)(DAT_012101d8 + 0x48) ^ DAT_012101dc ^ uVar13;
    in_ECX[0x87] = piVar4[4];
    in_ECX[0x3d] = piVar4[5];
    in_ECX[0x14b] = piVar4[6];
    in_ECX[0x14e] = piVar4[7];
    in_ECX[0x14f] = piVar4[8];
    FUN_00507940();
    (**(code **)(*in_ECX + 0x21c))();
    pwVar14 = &DAT_00cabae0;
    pwVar5 = (wchar_t *)FUN_00a530f0();
    iVar6 = _wcscmp(pwVar5,pwVar14);
    if (iVar6 != 0) {
      iVar6 = FUN_00403c50();
      local_8 = 0;
      if (iVar6 != 0) {
        FUN_00a530f0();
        FUN_00a530f0();
        FUN_00472a60();
      }
      local_8 = 0xffffffff;
      (**(code **)(*in_ECX + 0x6c))();
    }
    param_1 = (int *)piVar4[0xf];
    if (param_1 != (int *)piVar4[0x10]) {
      do {
        pwVar14 = &DAT_00cabae0;
        pwVar5 = (wchar_t *)FUN_00a530f0();
        iVar6 = _wcscmp(pwVar5,pwVar14);
        if (iVar6 == 0) {
          iVar6 = in_ECX[0x48];
          if ((iVar6 == 0) ||
             ((uint)(in_ECX[0x4a] - iVar6 >> 2) <= (uint)(in_ECX[0x49] - iVar6 >> 2)))
          goto LAB_0049f7cf;
          puVar2 = (undefined4 *)in_ECX[0x49];
          *puVar2 = 0;
          in_ECX[0x49] = (int)(puVar2 + 1);
        }
        else {
          local_14 = FUN_00403c50();
          local_8 = 1;
          if (local_14 == 0) {
            param_2 = 0;
          }
          else {
            FUN_00a530f0();
            FUN_00a530f0();
            param_2 = FUN_00472a60();
          }
          iVar6 = in_ECX[0x48];
          local_8 = 0xffffffff;
          local_14 = param_2;
          if ((iVar6 == 0) ||
             ((uint)(in_ECX[0x4a] - iVar6 >> 2) <= (uint)(in_ECX[0x49] - iVar6 >> 2))) {
LAB_0049f7cf:
            FUN_00408160();
          }
          else {
            piVar11 = (int *)in_ECX[0x49];
            *piVar11 = param_2;
            in_ECX[0x49] = (int)(piVar11 + 1);
          }
        }
        param_1 = (int *)((int)param_1 + 4);
      } while (param_1 != (int *)piVar4[0x10]);
    }
    pwVar14 = &DAT_00cabae0;
    pwVar5 = (wchar_t *)FUN_00a530f0();
    iVar6 = _wcscmp(pwVar5,pwVar14);
    if (iVar6 != 0) {
      iVar6 = FUN_00403c50();
      local_8 = 2;
      if (iVar6 != 0) {
        FUN_00a530f0();
        FUN_00a530f0();
        FUN_004a3900();
      }
      local_8 = 0xffffffff;
      (**(code **)(*in_ECX + 0x70))();
      iVar6 = in_ECX[0x53];
      *(undefined4 *)(iVar6 + 0x2cc) = 0;
      *(undefined4 *)(iVar6 + 0x2d0) = 0;
    }
    param_1 = (int *)piVar4[0x14];
    param_2 = 0;
    if (param_1 != (int *)piVar4[0x15]) {
      do {
        pwVar14 = &DAT_00cabae0;
        pwVar5 = (wchar_t *)FUN_00a530f0();
        iVar6 = _wcscmp(pwVar5,pwVar14);
        if (iVar6 == 0) {
          iVar6 = in_ECX[0x57];
          local_14 = 0;
          if ((iVar6 == 0) ||
             ((uint)(in_ECX[0x59] - iVar6 >> 2) <= (uint)(in_ECX[0x58] - iVar6 >> 2)))
          goto LAB_0049f99a;
          puVar2 = (undefined4 *)in_ECX[0x58];
          *puVar2 = 0;
          in_ECX[0x58] = (int)(puVar2 + 1);
        }
        else {
          local_14 = FUN_00403c50();
          local_8 = 3;
          if (local_14 == 0) {
            local_14 = 0;
          }
          else {
            if ((uint)in_ECX[0x97] < 8) {
              local_18 = in_ECX + 0x92;
            }
            else {
              local_18 = (int *)in_ECX[0x92];
            }
            FUN_00a530f0();
            local_14 = FUN_004a3900();
          }
          *(undefined4 *)(local_14 + 0x2cc) = 10;
          *(int *)(local_14 + 0x2d0) = param_2;
          iVar6 = in_ECX[0x57];
          local_8 = 0xffffffff;
          if (iVar6 == 0) {
            local_18 = (int *)0x0;
          }
          else {
            local_18 = (int *)(in_ECX[0x58] - iVar6 >> 2);
            if (local_18 < (int *)(in_ECX[0x59] - iVar6 >> 2)) {
              piVar11 = (int *)in_ECX[0x58];
              *piVar11 = local_14;
              in_ECX[0x58] = (int)(piVar11 + 1);
              goto LAB_0049f9a7;
            }
          }
LAB_0049f99a:
          FUN_00405f60();
        }
LAB_0049f9a7:
        param_2 = param_2 + 1;
        param_1 = (int *)((int)param_1 + 4);
      } while (param_1 != (int *)piVar4[0x15]);
    }
    pwVar14 = &DAT_00cabae0;
    pwVar5 = (wchar_t *)FUN_00a530f0();
    iVar6 = _wcscmp(pwVar5,pwVar14);
    if (iVar6 != 0) {
      iVar6 = FUN_00403c50();
      local_8 = 4;
      if (iVar6 == 0) {
        iVar6 = 0;
      }
      else {
        FUN_00a530f0();
        FUN_00a530f0();
        iVar6 = FUN_004a3900();
      }
      local_8 = 0xffffffff;
      in_ECX[0x54] = iVar6;
      FUN_00a2d020();
      iVar6 = in_ECX[0x54];
      *(undefined4 *)(iVar6 + 0x2cc) = 0xb;
      *(undefined4 *)(iVar6 + 0x2d0) = 0;
      FUN_00a530f0();
      FUN_00bffdcd();
      FUN_00402e80();
    }
    if (in_ECX[0x46] != 0) {
      FUN_00a25c90();
      iVar6 = FUN_00a242e0();
      in_ECX[0x62] = iVar6;
    }
    if (in_ECX[0x53] != 0) {
      iVar6 = FUN_00a2cf70();
      in_ECX[0x62] = iVar6;
    }
    pwVar14 = &DAT_00cabae0;
    pwVar5 = (wchar_t *)FUN_00a530f0();
    iVar6 = _wcscmp(pwVar5,pwVar14);
    if (iVar6 != 0) {
      FUN_00a530f0();
      FUN_00a530f0();
      iVar6 = FUN_00b7d230();
      if (iVar6 == 0) {
        FUN_00a530f0();
        FUN_00a530f0();
        (*(code *)PTR_FUN_00ff2ebc)();
      }
      else {
        FUN_004a27e0();
      }
    }
    iVar6 = piVar4[0x1e];
    if (iVar6 != piVar4[0x1f]) {
      do {
        pwVar14 = &DAT_00cabae0;
        pwVar5 = (wchar_t *)FUN_00a530f0();
        iVar7 = _wcscmp(pwVar5,pwVar14);
        if (iVar7 == 0) {
          FUN_00437d30();
          local_8 = 6;
          FUN_004a3630();
          local_8 = 0xffffffff;
          FUN_00437760();
        }
        else {
          FUN_00a530f0();
          FUN_00a530f0();
          iVar7 = FUN_00b7d230();
          if (iVar7 == 0) {
            FUN_00437d30();
            local_8 = 5;
            FUN_004a3630();
            local_8 = 0xffffffff;
            FUN_00437760();
            FUN_00a530f0();
            FUN_00a530f0();
            (*(code *)PTR_FUN_00ff2ebc)();
          }
          else {
            FUN_004a3630();
          }
        }
        iVar6 = iVar6 + 4;
      } while (iVar6 != piVar4[0x1f]);
    }
    FUN_00507940();
    FUN_004392e0();
    if (piVar4[0x2a] != -1) {
      in_ECX[0x148] = piVar4[0x2a];
    }
    puVar1 = (uint *)(piVar4 + 0x2b);
    if ((piVar4[0x2b] ^ DAT_012101dc) - (int)puVar1 != piVar4[0x2c]) {
      FUN_00b170b0();
    }
    iVar6 = piVar4[0x2c] * 4;
    uVar13 = *(int *)(DAT_012101d8 + 0x44) + iVar6 ^
             *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar6) ^ DAT_012101dc;
    if (uVar13 != (*(int *)(DAT_012101d8 + 0x48) + iVar6 ^
                   *(uint *)(*(int *)(DAT_012101d8 + 0x48) + iVar6) ^ DAT_012101dc)) {
      FUN_00b170b0();
    }
    if (0 < (int)uVar13) {
      if ((*puVar1 ^ DAT_012101dc) - (int)puVar1 != piVar4[0x2c]) {
        FUN_00b170b0();
      }
      iVar6 = piVar4[0x2c] * 4;
      if ((*(int *)(DAT_012101d8 + 0x44) + iVar6 ^ *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar6)
          ^ DAT_012101dc) !=
          (*(int *)(DAT_012101d8 + 0x48) + iVar6 ^ *(uint *)(*(int *)(DAT_012101d8 + 0x48) + iVar6)
          ^ DAT_012101dc)) {
        FUN_00b170b0();
      }
      (**(code **)(*in_ECX + 0x360))();
      iVar6 = *in_ECX;
      (**(code **)(iVar6 + 0x238))();
      (**(code **)(iVar6 + 0x35c))();
    }
    if (*(char *)((int)piVar4 + 0x61) != '\0') {
      iVar6 = (**(code **)(*in_ECX + 0x33c))();
      *(undefined1 *)(iVar6 + 0x34) = 1;
    }
    pwVar14 = &DAT_00cabae0;
    pwVar5 = (wchar_t *)FUN_00a530f0();
    iVar6 = _wcscmp(pwVar5,pwVar14);
    if (iVar6 != 0) {
      iVar6 = FUN_00403c50();
      local_8 = 7;
      if (iVar6 == 0) {
        iVar6 = 0;
      }
      else {
        FUN_00a530f0();
        iVar6 = FUN_004a3440();
      }
      local_8 = 0xffffffff;
      in_ECX[0x1e5] = iVar6;
    }
    (**(code **)(*in_ECX + 0x22c))();
    if (in_ECX + 0x214 != in_ECX + 0x192) {
      iVar6 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(iVar6 + in_ECX[0x215] * 4) =
           iVar6 + in_ECX[0x215] * 4 ^
           iVar6 + in_ECX[0x193] * 4 ^ *(uint *)(iVar6 + in_ECX[0x193] * 4) ^ DAT_012101dc ^
           DAT_012101dc;
      iVar6 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(iVar6 + in_ECX[0x215] * 4) =
           iVar6 + in_ECX[0x215] * 4 ^
           iVar6 + in_ECX[0x193] * 4 ^ *(uint *)(iVar6 + in_ECX[0x193] * 4) ^ DAT_012101dc ^
           DAT_012101dc;
    }
    if (in_ECX + 0x216 != in_ECX + 0x194) {
      iVar6 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(iVar6 + in_ECX[0x217] * 4) =
           iVar6 + in_ECX[0x217] * 4 ^
           iVar6 + in_ECX[0x195] * 4 ^ *(uint *)(iVar6 + in_ECX[0x195] * 4) ^ DAT_012101dc ^
           DAT_012101dc;
      iVar6 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(iVar6 + in_ECX[0x217] * 4) =
           iVar6 + in_ECX[0x217] * 4 ^
           iVar6 + in_ECX[0x195] * 4 ^ *(uint *)(iVar6 + in_ECX[0x195] * 4) ^ DAT_012101dc ^
           DAT_012101dc;
    }
    if (in_ECX + 0x218 != in_ECX + 0x196) {
      iVar6 = *(int *)(DAT_012101d8 + 0x44);
      *(uint *)(iVar6 + in_ECX[0x219] * 4) =
           iVar6 + in_ECX[0x219] * 4 ^
           iVar6 + in_ECX[0x197] * 4 ^ *(uint *)(iVar6 + in_ECX[0x197] * 4) ^ DAT_012101dc ^
           DAT_012101dc;
      iVar6 = *(int *)(DAT_012101d8 + 0x48);
      *(uint *)(iVar6 + in_ECX[0x219] * 4) =
           iVar6 + in_ECX[0x219] * 4 ^
           iVar6 + in_ECX[0x197] * 4 ^ *(uint *)(iVar6 + in_ECX[0x197] * 4) ^ DAT_012101dc ^
           DAT_012101dc;
    }
    iVar6 = (**(code **)(*DAT_01003164 + 0x88))();
    if ((iVar6 == 0) || (iVar6 = (**(code **)(*DAT_01003164 + 0x88))(), *(int *)(iVar6 + 0xb4) == 0)
       ) {
      (*(code *)PTR_FUN_00ff2ebc)();
    }
    else {
      iVar6 = (**(code **)(*DAT_01003164 + 0x88))();
      iVar7 = *(int *)(iVar6 + 0xb4);
      iVar6 = iVar7 + 0x74;
      if ((*(uint *)(iVar7 + 0x74) ^ DAT_012101dc) - iVar6 != *(int *)(iVar7 + 0x78)) {
        FUN_00b170b0(iVar6);
      }
      iVar7 = *(int *)(iVar7 + 0x78) * 4;
      uVar13 = *(int *)(DAT_012101d8 + 0x44) + iVar7 ^
               *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar7) ^ DAT_012101dc;
      if (uVar13 != (*(int *)(DAT_012101d8 + 0x48) + iVar7 ^
                     *(uint *)(*(int *)(DAT_012101d8 + 0x48) + iVar7) ^ DAT_012101dc)) {
        FUN_00b170b0(iVar6);
      }
      in_ECX[0x1e6] = uVar13;
      param_1 = in_ECX + 0x189;
      piVar11 = in_ECX + 0x215;
      local_14 = 3;
      do {
        local_18 = piVar11;
        if (*param_1 != 0x12) {
          if (((piVar11[-1] ^ DAT_012101dc) - (int)piVar11) + 4 != *piVar11) {
            FUN_00b170b0(piVar11 + -1);
          }
          iVar6 = *piVar11 * 4;
          uVar13 = *(int *)(DAT_012101d8 + 0x44) + iVar6 ^
                   *(uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar6) ^ DAT_012101dc;
          if (uVar13 != (*(int *)(DAT_012101d8 + 0x48) + iVar6 ^
                         *(uint *)(*(int *)(DAT_012101d8 + 0x48) + iVar6) ^ DAT_012101dc)) {
            FUN_00b170b0(piVar11 + -1);
          }
          uVar13 = in_ECX[0x1e6] + uVar13;
          *(uint *)(*(int *)(DAT_012101d8 + 0x44) + piVar11[-0x82] * 4) =
               *(int *)(DAT_012101d8 + 0x44) + piVar11[-0x82] * 4 ^ uVar13 ^ DAT_012101dc;
          *(uint *)(*(int *)(DAT_012101d8 + 0x48) + local_18[-0x82] * 4) =
               *(int *)(DAT_012101d8 + 0x48) + local_18[-0x82] * 4 ^ uVar13 ^ DAT_012101dc;
        }
        param_1 = param_1 + 1;
        piVar11 = local_18 + 2;
        local_14 = local_14 + -1;
      } while (local_14 != 0);
      local_14 = 0;
      local_18 = piVar11;
    }
    in_ECX[0x157] = piVar4[0x38];
    in_ECX[0x158] = piVar4[0x39];
    if (piVar4[0x3b] == 0) {
      iVar6 = 0;
    }
    else {
      iVar6 = piVar4[0x3c] - piVar4[0x3b] >> 2;
    }
    FUN_004a2250(iVar6);
    iVar7 = 0;
    if (0 < iVar6) {
      do {
        *(undefined4 *)(in_ECX[0x15a] + iVar7 * 4) = *(undefined4 *)(piVar4[0x3b] + iVar7 * 4);
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar6);
    }
    in_ECX[0x172] = piVar4[0x4c];
    if (piVar4[0x4e] == 0) {
      iVar6 = 0;
    }
    else {
      iVar6 = piVar4[0x4f] - piVar4[0x4e] >> 2;
    }
    FUN_004a2250(iVar6);
    iVar7 = 0;
    if (0 < iVar6) {
      do {
        *(undefined4 *)(in_ECX[0x174] + iVar7 * 4) = *(undefined4 *)(piVar4[0x4e] + iVar7 * 4);
        iVar7 = iVar7 + 1;
      } while (iVar7 < iVar6);
    }
    if (piVar4[0x43] == 0) {
      param_1 = (int *)0x0;
    }
    else {
      param_1 = (int *)(piVar4[0x44] - piVar4[0x43] >> 2);
    }
    FUN_00a538a0(&DAT_00cabae0);
    FUN_004a1a00(param_1);
    FUN_004a2250(param_1);
    iVar6 = 0;
    if (0 < (int)param_1) {
      do {
        FUN_00a53490();
        *(undefined4 *)(in_ECX[0x166] + iVar6 * 4) = *(undefined4 *)(piVar4[0x47] + iVar6 * 4);
        iVar6 = iVar6 + 1;
      } while (iVar6 < (int)param_1);
    }
    in_ECX[0x16e] = piVar4[0x4a];
    in_ECX[0x16f] = piVar4[0x4b];
    DVar8 = GetTickCount();
    in_ECX[0x170] = DVar8;
    param_1 = (int *)piVar4[0x52];
    if (param_1 != (int *)piVar4[0x53]) {
      do {
        pwVar14 = &DAT_00cabae0;
        pwVar5 = (wchar_t *)FUN_00a530f0();
        iVar6 = _wcscmp(pwVar5,pwVar14);
        if (iVar6 == 0) {
          iVar6 = in_ECX[0x20d];
          if ((iVar6 == 0) ||
             ((uint)(in_ECX[0x20f] - iVar6 >> 2) <= (uint)(in_ECX[0x20e] - iVar6 >> 2)))
          goto LAB_004a03d0;
          puVar2 = (undefined4 *)in_ECX[0x20e];
          *puVar2 = 0;
          in_ECX[0x20e] = (int)(puVar2 + 1);
        }
        else {
          local_14 = FUN_00403c50();
          local_8 = 8;
          if (local_14 == 0) {
            param_2 = 0;
          }
          else {
            uVar9 = FUN_00a530f0();
            uVar10 = FUN_00a530f0();
            param_2 = FUN_00472a60(uVar9,uVar10);
          }
          iVar6 = in_ECX[0x20d];
          local_8 = 0xffffffff;
          local_14 = param_2;
          if ((iVar6 == 0) ||
             ((uint)(in_ECX[0x20f] - iVar6 >> 2) <= (uint)(in_ECX[0x20e] - iVar6 >> 2))) {
LAB_004a03d0:
            FUN_00408160(in_ECX[0x20e],1);
          }
          else {
            piVar11 = (int *)in_ECX[0x20e];
            *piVar11 = param_2;
            in_ECX[0x20e] = (int)(piVar11 + 1);
          }
        }
        param_1 = (int *)((int)param_1 + 4);
      } while (param_1 != (int *)piVar4[0x53]);
    }
    param_1 = (int *)0x0;
    while ((iVar6 = piVar4[0x56], iVar6 != 0 && (param_1 < (uint)(piVar4[0x57] - iVar6 >> 2)))) {
      iVar7 = in_ECX[0x211];
      if ((iVar7 == 0) || ((uint)(in_ECX[0x213] - iVar7 >> 2) <= (uint)(in_ECX[0x212] - iVar7 >> 2))
         ) {
        FUN_00405f60(in_ECX[0x212],1);
        param_1 = (int *)((int)param_1 + 1);
      }
      else {
        puVar2 = (undefined4 *)in_ECX[0x212];
        *puVar2 = *(undefined4 *)(iVar6 + (int)param_1 * 4);
        in_ECX[0x212] = (int)(puVar2 + 1);
        param_1 = (int *)((int)param_1 + 1);
      }
    }
    for (uVar13 = 0;
        (iVar6 = in_ECX[0x20d], iVar6 != 0 && (uVar13 < (uint)(in_ECX[0x20e] - iVar6 >> 2)));
        uVar13 = uVar13 + 1) {
      (**(code **)(*in_ECX + 0xf8))
                (*(undefined4 *)(in_ECX[0x211] + uVar13 * 4),*(undefined4 *)(iVar6 + uVar13 * 4),0,0
                 ,0,0,0,0,0);
    }
    param_1 = (int *)piVar4[0x5a];
    if (((param_1 != (int *)0x0) && (piVar4[0x5b] - (int)param_1 >> 2 != 0)) &&
       (param_1 != (int *)piVar4[0x5b])) {
      do {
        iVar6 = FUN_00403c50();
        local_8 = 9;
        if (iVar6 == 0) {
          piVar11 = (int *)0x0;
        }
        else {
          if ((uint)in_ECX[0x97] < 8) {
            piVar11 = in_ECX + 0x92;
          }
          else {
            piVar11 = (int *)in_ECX[0x92];
          }
          uVar9 = FUN_00a530f0();
          piVar11 = (int *)FUN_004a3440(piVar11,uVar9);
        }
        local_8 = 0xffffffff;
        if (piVar11 != (int *)0x0) {
          local_34 = 0;
          FUN_00a538a0();
          local_8 = 10;
          local_38 = (int *)0x0;
          FUN_00a538a0();
          local_30 = 0;
          local_2c = 0;
          local_28 = 0;
          local_24 = 0;
          local_20 = 0;
          local_1c = 0;
          local_8 = 0xb;
          (**(code **)(*piVar11 + 0xc))();
          local_38 = piVar11;
          FUN_00a53490();
          iVar6 = *param_1;
          local_2c = *(undefined4 *)(iVar6 + 0xc);
          local_28 = *(undefined4 *)(iVar6 + 0x10);
          local_24 = *(undefined4 *)(iVar6 + 0x14);
          local_20 = *(undefined4 *)(iVar6 + 0x18);
          pwVar14 = u__follow_parent__00cceff0;
          pwVar5 = (wchar_t *)FUN_00a530f0();
          iVar6 = _wcscmp(pwVar5,pwVar14);
          if (iVar6 == 0) {
            local_30 = 1;
          }
          iVar6 = in_ECX[0x208];
          if ((iVar6 == 0) ||
             ((uint)(in_ECX[0x20a] - iVar6 >> 5) <= (uint)(in_ECX[0x209] - iVar6 >> 5))) {
            FUN_004a1bb0(in_ECX[0x209],1);
          }
          else {
            iVar6 = in_ECX[0x209];
            FUN_004a14b0(iVar6,1,&local_38,in_ECX + 0x207);
            in_ECX[0x209] = iVar6 + 0x20;
          }
          local_8 = 0xffffffff;
          FUN_00a53450();
        }
        param_1 = param_1 + 1;
      } while (param_1 != (int *)piVar4[0x5b]);
    }
    if ((char)piVar4[0x18] != '\0') {
      piVar11 = *(int **)in_ECX[0x3e];
      if (piVar11 == (int *)0x0) {
        piVar11 = (int *)in_ECX[0x3e] + 2;
      }
      piVar11[9] = -0x5dc;
    }
    if (*(char *)((int)piVar4 + 0x69) != '\0') {
      *(char *)(in_ECX + 0x150) = (char)piVar4[0x1a];
    }
    if (*(char *)((int)piVar4 + 0x62) != '\0') {
      in_ECX[0x148] = 1;
      in_ECX[0x39] = 0x221;
    }
    if (*(char *)((int)piVar4 + 0x6a) != '\0') {
      *(undefined1 *)(in_ECX + 0x110) = 1;
    }
    for (uVar13 = 0; (in_ECX[0x89] != 0 && (uVar13 < (uint)(in_ECX[0x8a] - in_ECX[0x89] >> 2)));
        uVar13 = uVar13 + 1) {
      (**(code **)(*in_ECX + 0x224))();
    }
    if ((in_ECX[0x3e] != 0) && ((char)piVar4[0x2d] != '\0')) {
      FUN_00511ec0();
      *(int *)(in_ECX[0x3e] + 0x104) = piVar4[0x2e];
      iVar7 = FUN_00c01544();
      iVar6 = in_ECX[0x3e];
      iVar12 = FUN_00c01544();
      *(float *)(iVar6 + 0x108) = (float)iVar12;
      *(float *)(iVar6 + 0x10c) = (float)iVar7;
      *(int *)(in_ECX[0x3e] + 0x110) = piVar4[0x31];
      *(char *)(in_ECX[0x3e] + 0x11c) = (char)piVar4[0x32];
      *(int *)(in_ECX[0x3e] + 0x120) = piVar4[0x33];
      *(int *)(in_ECX[0x3e] + 0x130) = piVar4[0x34];
      *(int *)(in_ECX[0x3e] + 0x134) = piVar4[0x35];
      *(int *)(in_ECX[0x3e] + 0x138) = piVar4[0x36];
      *(int *)(in_ECX[0x3e] + 0x140) = piVar4[0x37];
      (**(code **)(*in_ECX + 0xc0))();
      FUN_00511e30();
    }
    if (piVar4[0x19] != -1) {
      (**(code **)(*in_ECX + 0x1c0))();
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

