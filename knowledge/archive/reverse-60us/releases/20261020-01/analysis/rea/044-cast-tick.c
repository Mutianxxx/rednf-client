
void FUN_004dc220(void)

{
  bool bVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined1 *puVar11;
  uint *in_ECX;
  uint uVar12;
  undefined4 *unaff_FS_OFFSET;
  wchar_t *pwVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined1 *puVar17;
  undefined4 uVar18;
  undefined1 **ppuVar19;
  undefined1 auStack_324 [512];
  undefined1 local_124 [224];
  int local_44;
  undefined1 local_40 [4];
  void *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint *local_30;
  int *local_2c;
  uint local_28;
  undefined1 local_24 [4];
  undefined4 *local_20;
  uint *local_1c;
  int local_18;
  undefined1 *local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c58796;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  if ((char)in_ECX[0x8eb] != '\0') {
    if (in_ECX[0x8e2] != 0) {
      iVar3 = (**(code **)(*(int *)(in_ECX[0x8e2] + 0x520) + 0x20))();
      if (DAT_01015c94 - iVar3 <= DAT_01015c9c) goto LAB_004dc28c;
      uVar4 = FUN_00402060();
      FUN_004d4c40(uVar4);
    }
    *(undefined1 *)(in_ECX + 0x8eb) = 0;
  }
LAB_004dc28c:
  FUN_004bc7d0();
  if (((in_ECX[0x953] != 0) && (cVar2 = FUN_0043abf0(0xffffffff), cVar2 != '\0')) &&
     (iVar3 = FUN_00402060(), iVar3 != 9)) {
    if (in_ECX[0x953] == 1) {
      local_14 = (undefined1 *)FUN_00403c50(0x1e8);
      local_8 = 0;
      if (local_14 == (undefined1 *)0x0) {
        uVar4 = 0;
      }
      else {
        uVar4 = FUN_004936d0(u_Common_Etc_Animation_LevelNormal_00cd3ff8,1);
      }
      local_8 = 0xffffffff;
      local_14 = (undefined1 *)FUN_00403c50(0x1fc);
      local_8 = 1;
      if (local_14 == (undefined1 *)0x0) {
        piVar5 = (int *)0x0;
      }
      else {
        piVar5 = (int *)FUN_004abd20(uVar4,1);
      }
      uVar16 = 2;
      local_8 = 0xffffffff;
      local_2c = piVar5;
      (**(code **)(*piVar5 + 0x54))(2);
      FUN_0050dd70(in_ECX,2,0,piVar5,in_ECX,0,0);
      iVar3 = *piVar5;
      iVar6 = (**(code **)(*in_ECX + 0xe4))();
      iVar7 = (**(code **)(*in_ECX + 0x9c))();
      uVar4 = (**(code **)(*in_ECX + 0x98))(iVar6 + iVar7);
      uVar4 = (**(code **)(*in_ECX + 0x94))(uVar4);
      piVar5 = local_2c;
      (**(code **)(iVar3 + 0x88))(uVar4);
      (**(code **)(*piVar5 + 0x48))();
      FUN_00510e80(uVar16);
      if (in_ECX[0x952] == 0) {
        local_14 = (undefined1 *)FUN_00403c50(0x1b4);
        local_8 = 2;
        if (local_14 == (undefined1 *)0x0) {
          piVar5 = (int *)0x0;
        }
        else {
          piVar5 = (int *)FUN_00453320(u_Common_Etc_Particle_LevelNormali_00cd3fa8,in_ECX);
        }
        in_ECX[0x952] = (uint)piVar5;
        local_8 = 0xffffffff;
        (**(code **)(*piVar5 + 0x70))();
        (**(code **)(*(int *)in_ECX[0x952] + 0x3c))(1);
      }
      in_ECX[0x953] = 2;
      FUN_00404ef0();
      FUN_00b06f60(0,0);
    }
    else {
      iVar3 = FUN_00b06f00();
      if ((iVar3 < 300) || (in_ECX[0x953] != 2)) {
        iVar3 = FUN_00b06f00();
        if ((0x77f < iVar3) && (in_ECX[0x953] == 3)) {
          in_ECX[0x953] = 4;
          pwVar13 = u_LEVELING_FLASH_00cd3f68;
          goto LAB_004dc48f;
        }
      }
      else {
        in_ECX[0x953] = 3;
        pwVar13 = u_LEVELING_OFF_00cd3f88;
LAB_004dc48f:
        FUN_004479b0(pwVar13,0xffffffff,0,0);
      }
      iVar3 = FUN_00b06f00();
      if ((0x923 < iVar3) && ((int *)in_ECX[0x952] != (int *)0x0)) {
        (**(code **)(*(int *)in_ECX[0x952] + 0xc))(0);
        uVar4 = FUN_00a530f0();
        uVar4 = FUN_00a51240(0x352,uVar4);
        FUN_00401df0(local_124,0xde,uVar4);
        cVar2 = (**(code **)(*in_ECX + 0x34))();
        if (cVar2 == '\0') {
          FUN_009bc710(local_124,0xff9bc8e6,0x17,0,0);
        }
        in_ECX[0x953] = 0;
      }
    }
  }
  if (DAT_0104f1d4 == in_ECX) {
    (**(code **)(*in_ECX + 0x764))();
  }
  if (((char)in_ECX[0x8fb] != '\0') && (*(char *)(in_ECX[0x8fc] + 0x13a) != '\0')) {
    (**(code **)(*in_ECX + 0x6ec))(0);
  }
  if (((char)in_ECX[0x8ff] != '\0') && (*(char *)(in_ECX[0x900] + 0x13a) != '\0')) {
    (**(code **)(*in_ECX + 0x6f4))(0,0);
  }
  if ((char)in_ECX[0x902] != '\0') {
    if (*(int *)(in_ECX[0x903] + 0x188) == 0) {
      iVar3 = *(int *)(in_ECX[0x903] + 0x8c);
    }
    else {
      iVar3 = FUN_004caa00();
    }
    iVar6 = 0;
    if (iVar3 < 0x21c) {
      iVar6 = (**(code **)(*in_ECX + 0xe4))();
      local_28 = iVar6 + 100;
      iVar6 = (**(code **)(*in_ECX + 0xe4))();
      local_2c = (int *)(iVar6 + 0x1e);
      FUN_00b099e0((float)(int)local_2c,(float)(int)local_28,iVar3,0x21c,1);
      iVar6 = FUN_00c01544();
      iVar3 = *(int *)in_ECX[0x904];
      iVar7 = (**(code **)(*in_ECX + 0x98))(iVar6);
      uVar4 = (**(code **)(*in_ECX + 0x94))(iVar7 + -1);
      (**(code **)(iVar3 + 0x28))(uVar4);
      (**(code **)(*(int *)in_ECX[0x904] + 0x5c))(local_40);
      local_8 = 3;
      FUN_0050e060(in_ECX,2,0,local_40,0);
      local_8 = 0xffffffff;
      if (local_3c != (void *)0x0) {
        _free(local_3c);
      }
    }
    else if (iVar3 < 0x438) {
      iVar6 = (**(code **)(*in_ECX + 0xe4))();
      local_28 = iVar6 + 0x1e;
      iVar6 = (**(code **)(*in_ECX + 0xe4))();
      local_2c = (int *)(iVar6 + 100);
      FUN_00b099e0((float)(int)local_2c,(float)(int)local_28,iVar3 + -0x21c,0x21c,0);
      iVar6 = FUN_00c01544();
    }
    else {
      (**(code **)(*in_ECX + 0x6fc))(0);
    }
    if (in_ECX[0x905] != 0) {
      *(int *)(in_ECX[0x905] + 0xc) = -iVar6;
    }
  }
  piVar5 = (int *)0x0;
  if (in_ECX[0x40] != 0) {
    local_30 = (uint *)0x0;
    while ((local_2c = piVar5, in_ECX[0x8cf] != 0 &&
           (local_30 < (uint *)((int)(in_ECX[0x8d0] - in_ECX[0x8cf]) / 0x14)))) {
      uVar12 = in_ECX[0x8cf];
      if ((*(char *)((int)piVar5 + uVar12 + 0x10) == '\0') ||
         ((iVar3 = FUN_00402060(), iVar3 == 0 && (iVar3 = FUN_00402060(), iVar3 != 0)))) {
        local_14 = (undefined1 *)((int)piVar5 + uVar12 + 0x11);
        if (*(char *)((int)piVar5 + uVar12 + 0x11) == '\0') {
          (**(code **)(**(int **)((int)piVar5 + uVar12) + 0xc))(0);
        }
        iVar3 = (**(code **)(*in_ECX + 0xc0))();
        if (iVar3 == 0) {
          iVar3 = (**(code **)(*in_ECX + 0x94))();
          local_28 = iVar3 - *(int *)((int)piVar5 + uVar12 + 4);
        }
        else {
          iVar3 = (**(code **)(*in_ECX + 0x94))();
          local_28 = iVar3 + *(int *)((int)piVar5 + uVar12 + 4);
        }
        local_44 = **(int **)((int)piVar5 + uVar12);
        iVar3 = (**(code **)(*in_ECX + 0x9c))();
        iVar3 = (**(code **)(*in_ECX + 0x98))(iVar3 + *(int *)((int)local_2c + uVar12 + 0xc));
        piVar5 = local_2c;
        (**(code **)(local_44 + 0x28))(local_28,iVar3 + *(int *)((int)local_2c + uVar12 + 8));
        (**(code **)(**(int **)((int)piVar5 + uVar12) + 0x5c))(local_40);
        local_8 = 4;
        FUN_0050e060(in_ECX,2,0,local_40,0);
        *local_14 = 1;
        local_8 = 0xffffffff;
        if (local_3c != (void *)0x0) {
          _free(local_3c);
        }
        local_30 = (uint *)((int)local_30 + 1);
        local_3c = (void *)0x0;
        local_38 = 0;
        local_34 = 0;
        piVar5 = piVar5 + 5;
      }
      else {
        local_30 = (uint *)((int)local_30 + 1);
        *(undefined1 *)((int)piVar5 + uVar12 + 0x11) = 0;
        piVar5 = piVar5 + 5;
      }
    }
  }
  uVar4 = FUN_00b06f00();
  cVar2 = FUN_00a51fb0(uVar4);
  if (cVar2 != '\0') {
    FUN_004d25a0();
  }
  local_14 = (undefined1 *)(**(code **)(*in_ECX + 0xdc))();
  local_44 = (**(code **)(*in_ECX + 0xe0))();
  puVar8 = in_ECX + 0x544;
  iVar3 = 10;
  do {
    piVar5 = (int *)FUN_00c00d0b(*puVar8,0,&PTR_PTR_00f40968,&PTR_PTR_00f5ae58,0);
    if (piVar5 != (int *)0x0) {
      (**(code **)(*piVar5 + 0x1ac))();
    }
    puVar8 = puVar8 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  puVar8 = in_ECX + 0x557;
  if ((in_ECX[0x557] ^ DAT_012101dc) - (int)puVar8 != in_ECX[0x558]) {
    FUN_00b170b0(puVar8,0x3f);
  }
  iVar3 = in_ECX[0x558] * 4;
  uVar12 = iVar3 + *(int *)(DAT_012101d8 + 0x44) ^ *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x44))
           ^ DAT_012101dc;
  if (uVar12 != (iVar3 + *(int *)(DAT_012101d8 + 0x48) ^
                 *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48)) ^ DAT_012101dc)) {
    FUN_00b170b0(puVar8,0x40);
  }
  switch(uVar12) {
  case 0:
    cVar2 = FUN_0049c090();
    if (((cVar2 != '\0') && (iVar3 = (**(code **)(*in_ECX + 0x644))(0), iVar3 != 4)) &&
       (cVar2 = (**(code **)(*in_ECX + 0x34))(), cVar2 == '\0')) {
      uVar12 = *in_ECX;
      uVar4 = (**(code **)(uVar12 + 0x644))(0);
      (**(code **)(uVar12 + 0xb8))(uVar4);
    }
    iVar3 = FUN_00402060();
    if ((iVar3 != 0) && (iVar3 = (**(code **)(*in_ECX + 0x5dc))(), iVar3 != 0)) {
      iVar3 = (**(code **)(*in_ECX + 0x5dc))();
      iVar6 = (**(code **)(*in_ECX + 0x370))();
      if ((iVar3 != iVar6) && (in_ECX[0x6c] == 0)) {
        iVar3 = FUN_00402060();
        if (iVar3 == 4) {
          cVar2 = *(int *)(*(int *)(DAT_01002848 + 0x1058) + 0x28) == 0;
        }
        else {
          iVar3 = FUN_00402060();
          if (iVar3 == 6) {
            cVar2 = FUN_00abc770();
          }
          else {
            iVar3 = FUN_00402060();
            if (iVar3 == 7) {
              cVar2 = FUN_00a9c950();
            }
            else {
              cVar2 = FUN_004e2af0();
              cVar2 = '\x01' - (cVar2 != '\0');
            }
          }
        }
        if (cVar2 == '\0') {
          uVar12 = (**(code **)(*in_ECX + 0x5dc))();
          if (in_ECX[0x41] == uVar12) {
            uVar12 = *in_ECX;
            uVar4 = (**(code **)(uVar12 + 0x370))();
            (**(code **)(uVar12 + 0xf0))(uVar4);
            FUN_00a27360();
          }
        }
        else {
          uVar12 = (**(code **)(*in_ECX + 0x370))();
          if (in_ECX[0x41] == uVar12) {
            uVar12 = *in_ECX;
            uVar4 = (**(code **)(uVar12 + 0x5dc))();
            (**(code **)(uVar12 + 0xf0))(uVar4);
            FUN_00a27360();
          }
        }
      }
    }
    break;
  case 5:
    iVar3 = FUN_00b06f00();
    if ((iVar3 < 1000) && (uVar12 = FUN_00b06f00(), (uVar12 / 200 & 1) != 0)) {
      FUN_004aba10(0xff000000,0xffffff);
    }
    else {
      FUN_00498e60(0xff000000);
    }
    iVar3 = FUN_00b06f00();
    if ((999 < iVar3) && ((char)in_ECX[0x939] == '\0')) {
      (**(code **)(*in_ECX + 0x6e4))();
      *(undefined1 *)(in_ECX + 0x939) = 1;
      cVar2 = FUN_0043abf0(0xffffffff);
      if (cVar2 != '\0') {
        (**(code **)(*DAT_0104f1d4 + 0x1c4))();
        (**(code **)(*in_ECX + 0x1c4))();
        if (in_ECX[0x954] == 0x111) {
          if (in_ECX[0x95e] < 8) {
            puVar8 = in_ECX + 0x959;
          }
          else {
            puVar8 = (uint *)in_ECX[0x959];
          }
          uVar4 = FUN_00a530f0();
          uVar4 = FUN_00a51240(0x353,puVar8,uVar4);
          FUN_00401df0(auStack_324,0x200,uVar4);
          cVar2 = (**(code **)(*in_ECX + 0x34))();
          if (cVar2 == '\0') {
            FUN_009bc710(auStack_324,0xff9bc8e6,0x17,0,0);
          }
          uVar12 = (**(code **)(*DAT_0104f1d4 + 0x3c))();
          if ((in_ECX[0x955] == uVar12) &&
             (uVar12 = (**(code **)(*DAT_0104f1d4 + 0x40))(), in_ECX[0x956] == uVar12)) {
            uVar14 = 1;
            uVar16 = 8;
            uVar4 = (**(code **)(*DAT_0104f1d4 + 0x40))(8,1);
            FUN_0051c2d0(uVar4,uVar16,uVar14);
          }
        }
        else {
          if (in_ECX[0x95e] < 8) {
            puVar8 = in_ECX + 0x959;
          }
          else {
            puVar8 = (uint *)in_ECX[0x959];
          }
          uVar4 = FUN_00a530f0(puVar8);
          uVar4 = FUN_00a51240(0x354,uVar4);
          FUN_00401df0(auStack_324,0x200,uVar4);
          cVar2 = (**(code **)(*in_ECX + 0x34))();
          if (cVar2 == '\0') {
            FUN_009bc710(auStack_324,0xff9bc8e6,0x17,0,0);
          }
        }
        FUN_004479b0(&DAT_00cd3f58,0xffffffff,0,0);
      }
    }
    iVar3 = FUN_00402060();
    if (iVar3 == 9) {
      (**(code **)(*in_ECX + 0x10c))(u_TOWNFIGHT_KILL_00cd3f38,0xffffffff,0,0);
    }
    break;
  case 10:
    iVar3 = FUN_00402060();
    if (iVar3 == 0) {
      cVar2 = FUN_0049c090();
      if ((cVar2 != '\0') && (iVar3 = FUN_00402060(), iVar3 != -1)) {
        iVar3 = FUN_00b06f00();
        iVar6 = FUN_00402060();
        if (iVar6 <= iVar3) {
          iVar3 = FUN_00402060();
          if (iVar3 == -1) {
            (**(code **)(*in_ECX + 0x784))(1,0);
          }
          else {
            local_20 = (undefined4 *)0x0;
            local_1c = (uint *)0x0;
            local_18 = 0;
            puVar17 = local_24;
            local_8 = 5;
            uVar4 = FUN_00402060(puVar17);
            FUN_004d5eb0(uVar4,puVar17);
            cVar2 = FUN_004e2560();
            if (cVar2 == '\0') {
              if ((local_20 != (undefined4 *)0x0) && ((int)local_1c - (int)local_20 >> 2 == 1)) {
                (**(code **)(*in_ECX + 0x784))(1,*local_20);
                local_8 = 0xffffffff;
                FUN_00644d50();
                break;
              }
              uVar4 = 2;
            }
            else {
              uVar4 = 1;
            }
            (**(code **)(*in_ECX + 0x784))(uVar4,0);
            local_8 = 0xffffffff;
            FUN_00644d50();
          }
        }
      }
    }
    else {
      iVar3 = FUN_00402060();
      if (iVar3 == 1) {
        if ((((char)in_ECX[0x91b] == '\0') && (in_ECX[0x41] != 0)) &&
           ((in_ECX[0x90a] == 2 ||
            ((in_ECX[0x90a] == 1 && ((int)in_ECX[0x91e] <= *(int *)(in_ECX[0x41] + 0x124))))))) {
          if (((DAT_0104f1d4 == in_ECX) ||
              ((cVar2 = FUN_0049c090(), cVar2 != '\0' &&
               (cVar2 = (**(code **)(*in_ECX + 0x34))(), cVar2 != '\0')))) && (in_ECX[0x9d1] != 0))
          {
            uVar4 = FUN_00402060();
            iVar3 = FUN_0047d620(uVar4);
            if (iVar3 != -1) {
              piVar5 = (int *)FUN_004044b0(iVar3);
              uVar12 = (**(code **)(*piVar5 + 0x30))();
              uVar9 = FUN_0040fba0();
              if (uVar9 < uVar12) {
                cVar2 = FUN_00480010(iVar3,in_ECX[0x926]);
                if (cVar2 != '\0') goto LAB_004dcefa;
                (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
                goto LAB_004dcf0f;
              }
            }
            (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
          }
          else {
LAB_004dcefa:
            cVar2 = FUN_0049c090();
            if (cVar2 != '\0') {
              (**(code **)(*in_ECX + 0x718))();
            }
          }
LAB_004dcf0f:
          uVar4 = FUN_00402060();
          iVar3 = FUN_00a61520(uVar4);
          if ((iVar3 != 0) && (uVar12 = FUN_00466790(), 1 < uVar12)) {
            uVar12 = *in_ECX;
            uVar4 = FUN_00a530f0(0xffffffff,0,0);
            (**(code **)(uVar12 + 0x10c))(uVar4);
          }
          (**(code **)(*in_ECX + 0x670))();
          *(undefined1 *)(in_ECX + 0x91b) = 1;
        }
        if ((in_ECX[0x90a] == 2) || (in_ECX[0x90a] == 1)) {
          if (((char)in_ECX[0x91b] != '\0') && (iVar3 = FUN_00402060(), iVar3 != -1)) {
            iVar3 = FUN_00b06f00();
            iVar6 = FUN_00402060();
            if (iVar6 <= iVar3) {
              (**(code **)(*in_ECX + 0x784))(0xffffffff,0);
            }
          }
        }
        else {
          iVar3 = FUN_00402060();
          if (iVar3 != -1) {
            iVar3 = FUN_00b06f00();
            iVar6 = FUN_00402060();
            if (iVar6 <= iVar3) {
              (**(code **)(*in_ECX + 0x784))(0xffffffff,0);
            }
          }
        }
      }
      else {
        iVar3 = FUN_00402060();
        if ((iVar3 != 2) || (cVar2 = FUN_0049c090(), cVar2 == '\0')) break;
        iVar3 = 0;
        do {
          piVar5 = (int *)FUN_004e28a0(iVar3);
          if (*piVar5 != 0) {
            piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
            cVar2 = (**(code **)(*piVar5 + 0x2c))(*(undefined4 *)(&DAT_00cd3f28 + iVar3 * 4),1);
            if (cVar2 != '\0') {
              puVar10 = (undefined4 *)FUN_004e28a0(iVar3);
              local_14 = (undefined1 *)FUN_00402060();
              iVar6 = (**(code **)(*in_ECX + 8))(*puVar10,0);
              if (iVar6 < (int)local_14) {
                puVar10 = (undefined4 *)FUN_004e28a0(iVar3);
                (**(code **)(*in_ECX + 0x784))(1,*puVar10);
              }
              else {
                cVar2 = (**(code **)(*in_ECX + 0x34))();
                if (cVar2 == '\0') {
                  FUN_004e28a0(iVar3);
                  uVar18 = 0;
                  uVar15 = 0;
                  uVar14 = 0x10;
                  uVar16 = 0xff9bc8e6;
                  uVar4 = FUN_00a530f0(0xff9bc8e6,0x10,0,0);
                  uVar4 = FUN_00a51240(0xe02,uVar4);
                  uVar4 = FUN_00a52aa0(0,uVar4);
                  FUN_009bc710(uVar4,uVar16,uVar14,uVar15,uVar18);
                }
              }
              break;
            }
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < 4);
        bVar1 = false;
        iVar3 = FUN_00b06f00();
        if (iVar3 < 10000) {
          piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
          cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x68c,1);
          if (cVar2 != '\0') goto LAB_004dd196;
          piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
          cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x6c3,1);
          if (cVar2 != '\0') goto LAB_004dd196;
          if (in_ECX[0x90a] == 0) {
            uVar16 = 0;
            uVar4 = FUN_00402060(0);
            (**(code **)(*in_ECX + 0x73c))(uVar4);
            iVar3 = FUN_00559140(uVar4,uVar16);
            if (iVar3 != -1) goto LAB_004dd196;
          }
        }
        else {
LAB_004dd196:
          bVar1 = true;
        }
        cVar2 = (**(code **)(*in_ECX + 0x34))();
        if (cVar2 != '\0') {
          uVar12 = *in_ECX;
          uVar4 = FUN_004beb30();
          (**(code **)(uVar12 + 0x784))(1,uVar4);
        }
        if (bVar1) {
          (**(code **)(*in_ECX + 0x784))(1,0);
        }
      }
    }
    break;
  case 0xb:
    cVar2 = (**(code **)(*in_ECX + 0x34))();
    puVar17 = local_14;
    if (cVar2 == '\0') {
      if (local_14 == (undefined1 *)0x4) {
        if (local_44 == 4) {
          (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
        }
      }
      else {
        puVar11 = (undefined1 *)(**(code **)(*in_ECX + 0xc0))();
        if (puVar17 != puVar11) {
          (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
        }
      }
    }
    if ((in_ECX[0x617] == 7) && (in_ECX[0x40] != 0)) {
      iVar3 = FUN_00402060();
      iVar6 = FUN_00b06f00();
      if (iVar3 <= iVar6) {
        iVar3 = (**(code **)(*in_ECX + 0x4d0))(2);
        piVar5 = (int *)(&DAT_01002e78)[iVar3];
        iVar3 = (**(code **)(*in_ECX + 0xc0))();
        iVar6 = (**(code **)(*piVar5 + 0x1c))();
        *(char *)(iVar6 + 0x58) = '\x01' - (iVar3 != 0);
        iVar3 = *piVar5;
        uVar4 = (**(code **)(*in_ECX + 0x9c))();
        uVar4 = (**(code **)(*in_ECX + 0x98))(uVar4);
        uVar4 = (**(code **)(*in_ECX + 0x94))(uVar4);
        (**(code **)(iVar3 + 0x28))(uVar4);
        (**(code **)(*piVar5 + 0xc))(0);
        (**(code **)(*piVar5 + 0x5c))(local_40);
        local_8 = 6;
        FUN_0050e060(in_ECX,2,0,local_40,0);
        FUN_00404ef0();
        FUN_00b06f60(100,0);
        local_8 = 0xffffffff;
        FUN_00644d50();
      }
    }
    break;
  case 0xc:
    if (*(char *)(in_ECX[0x41] + 0x13a) != '\0') {
      (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
    }
    break;
  case 0xd:
    cVar2 = *(char *)(in_ECX[0x41] + 0x13a);
LAB_004dd419:
    if (cVar2 != '\0') {
      (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
    }
    break;
  case 0xe:
    if (in_ECX[0x41] != 0) {
      iVar3 = FUN_00b06f00();
      iVar6 = FUN_00a24bb0(0);
      if ((iVar3 < iVar6 + -300) && ((int *)in_ECX[0x93b] != (int *)0x0)) {
        iVar3 = *(int *)in_ECX[0x93b];
        iVar6 = (**(code **)(*in_ECX + 0xe4))();
        iVar7 = (**(code **)(*in_ECX + 0x9c))();
        uVar4 = (**(code **)(*in_ECX + 0x98))(iVar6 + 0x1e + iVar7);
        uVar4 = (**(code **)(*in_ECX + 0x94))(uVar4);
        (**(code **)(iVar3 + 0x28))(uVar4);
        (**(code **)(*(int *)in_ECX[0x93b] + 0x5c))(local_40);
        local_8 = 7;
        if (in_ECX[0x40] != 0) {
          FUN_0050e060(in_ECX,2,0,local_40,0);
        }
        local_8 = 0xffffffff;
        FUN_00644d50();
      }
      cVar2 = *(char *)(in_ECX[0x41] + 0x13a);
      goto LAB_004dd419;
    }
  }
  cVar2 = FUN_0049c090();
  if (cVar2 != '\0') {
    puVar8 = in_ECX + 0x557;
    if ((in_ECX[0x557] ^ DAT_012101dc) - (int)puVar8 != in_ECX[0x558]) {
      FUN_00b170b0(puVar8,0x3f);
    }
    iVar3 = in_ECX[0x558] * 4;
    uVar12 = iVar3 + *(int *)(DAT_012101d8 + 0x44) ^
             *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x44)) ^ DAT_012101dc;
    if (uVar12 != (iVar3 + *(int *)(DAT_012101d8 + 0x48) ^
                   *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48)) ^ DAT_012101dc)) {
      FUN_00b170b0(puVar8,0x40);
    }
    if (uVar12 == 8) {
      piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
      cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x697,1);
      if (cVar2 != '\0') {
        *(undefined1 *)(in_ECX + 0x696) = 0;
        (**(code **)(*in_ECX + 0x774))(0);
        *(undefined1 *)(in_ECX + 0x6a1) = 0;
      }
    }
  }
  cVar2 = FUN_0049c090();
  iVar3 = DAT_012101d8;
  if ((cVar2 == '\0') || (in_ECX[0x6c] == 2)) goto LAB_004de07a;
  (**(code **)(*in_ECX + 0x770))();
  cVar2 = (**(code **)(*in_ECX + 0x470))();
  if (cVar2 != '\0') {
    iVar3 = 0;
    do {
      piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
      cVar2 = (**(code **)(*piVar5 + 0x2c))(iVar3,1);
      if (cVar2 != '\0') break;
      iVar3 = iVar3 + 1;
    } while (iVar3 < 9);
    if (iVar3 != 9) {
      (**(code **)(*in_ECX + 0x478))();
    }
  }
  if ((in_ECX[0x557] ^ DAT_012101dc) - (int)(in_ECX + 0x557) != in_ECX[0x558]) {
    FUN_00b170b0(in_ECX + 0x557,0x3f);
  }
  iVar3 = in_ECX[0x558] * 4;
  uVar12 = iVar3 + *(int *)(DAT_012101d8 + 0x44) ^ *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x44))
           ^ DAT_012101dc;
  if (uVar12 != (iVar3 + *(int *)(DAT_012101d8 + 0x48) ^
                 *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48)) ^ DAT_012101dc)) {
    FUN_00b170b0(in_ECX + 0x557,0x40);
  }
  switch(uVar12) {
  case 0:
    piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
    cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x6a2,1);
    if (cVar2 == '\0') {
      piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
      cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x6ad,1);
      if (cVar2 != '\0') goto LAB_004dd60c;
    }
    else {
LAB_004dd60c:
      iVar3 = (**(code **)(*in_ECX + 0x5e8))();
      if (iVar3 != 0) {
        (**(code **)(*in_ECX + 0x28c))(0xb,0,1,0,0);
        goto LAB_004dd9f7;
      }
    }
    piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
    cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x697,1);
    if (cVar2 == '\0') {
      piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
      cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x68c,1);
      if ((cVar2 != '\0') && (in_ECX[0x6c] == 0)) {
        if ((in_ECX[0x927] == 0) ||
           ((*(short *)(DAT_01003180 + 4) != -1 ||
            (iVar3 = (**(code **)(*in_ECX + 0x5f0))(), iVar3 == 0)))) {
          iVar3 = (**(code **)(*in_ECX + 0x388))(0);
          if (iVar3 != 0) {
            local_3c = (void *)0x0;
            local_38 = 0;
            local_34 = 0;
            local_8 = 9;
            local_14 = (undefined1 *)0x0;
            FUN_00407120(&local_14);
            (**(code **)(*in_ECX + 0x28c))(8,local_40,1,0,0);
            local_8 = 0xffffffff;
            FUN_00644d50();
          }
        }
        else {
          (**(code **)(*in_ECX + 0x28c))(0xd,0,1,0,0);
        }
      }
    }
    else {
      local_20 = (undefined4 *)0x0;
      local_1c = (uint *)0x0;
      local_18 = 0;
      local_8 = 8;
      local_14 = (undefined1 *)0x0;
      FUN_00407120(&local_14);
      local_14 = (undefined1 *)0x0;
      FUN_00407120(&local_14);
      local_14 = (undefined1 *)0x0;
      FUN_00407120(&local_14);
      (**(code **)(*in_ECX + 0x28c))(6,local_24,1,0,0);
      local_8 = 0xffffffff;
      if (local_20 != (undefined4 *)0x0) {
        _free(local_20);
      }
    }
    goto LAB_004dd9f7;
  case 6:
    iVar3 = FUN_00402060();
    if (iVar3 == 1) {
      piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
      cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x68c,1);
      if (cVar2 != '\0') {
        iVar3 = FUN_00402060();
        iVar6 = FUN_00402060();
        if (iVar6 < iVar3) {
          (**(code **)(*in_ECX + 0x28c))(7,0,1,0,0);
          goto LAB_004dd9f7;
        }
      }
    }
    break;
  case 8:
    iVar3 = (**(code **)(*in_ECX + 0x674))();
    iVar6 = FUN_00402060();
    if (iVar6 < iVar3) {
      iVar3 = *(int *)(in_ECX[0x41] + 0x124);
      local_14 = (undefined1 *)*in_ECX;
      uVar4 = FUN_00402060();
      iVar6 = (**(code **)(local_14 + 0x678))(uVar4);
      if (iVar6 <= iVar3) {
        if (in_ECX[0x6c] == 0) {
          piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
          cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x68c,1);
          if ((cVar2 != '\0') || (iVar3 = FUN_00402060(), 0 < iVar3)) {
            local_20 = (undefined4 *)0x0;
            local_1c = (uint *)0x0;
            local_18 = 0;
            ppuVar19 = (undefined1 **)(in_ECX + 0x906);
            local_8 = 10;
            if (in_ECX[0x906] == 0xffffffff) {
              iVar3 = FUN_00402060();
              local_14 = (undefined1 *)(iVar3 + 1);
              ppuVar19 = &local_14;
            }
            FUN_00407120(ppuVar19);
            (**(code **)(*in_ECX + 0x28c))(8,local_24,1,0,0);
            (**(code **)(*in_ECX + 0x750))();
            goto LAB_004dd943;
          }
        }
        goto LAB_004dd9f7;
      }
    }
    break;
  case 0xb:
    piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
    cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x697,1);
    if (cVar2 == '\0') {
      piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
      cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x68c,1);
      if (cVar2 != '\0') {
        (**(code **)(*in_ECX + 0x28c))(0xc,0,1,0,0);
      }
    }
    else {
      local_20 = (undefined4 *)0x0;
      local_1c = (uint *)0x0;
      local_18 = 0;
      local_8 = 0xb;
      local_14 = (undefined1 *)0x0;
      FUN_00405f60(0,1,&local_14);
      local_14 = (undefined1 *)0x0;
      if ((local_20 == (undefined4 *)0x0) ||
         ((uint)(local_18 - (int)local_20 >> 2) <= (uint)((int)local_1c - (int)local_20 >> 2))) {
        FUN_00405f60(local_1c,1,&local_14);
      }
      else {
        *local_1c = 0;
        local_1c = local_1c + 1;
      }
      local_14 = (undefined1 *)0x0;
      if ((local_20 == (undefined4 *)0x0) ||
         ((uint)(local_18 - (int)local_20 >> 2) <= (uint)((int)local_1c - (int)local_20 >> 2))) {
        FUN_00405f60(local_1c,1,&local_14);
      }
      else {
        *local_1c = 0;
        local_1c = local_1c + 1;
      }
      (**(code **)(*in_ECX + 0x28c))(6,local_24,1,0,0);
LAB_004dd943:
      local_8 = 0xffffffff;
      if (local_20 != (undefined4 *)0x0) {
        _free(local_20);
      }
    }
    goto LAB_004dd9f7;
  }
LAB_004dd9f7:
  cVar2 = (**(code **)(*in_ECX + 0x778))();
  if (cVar2 != '\0') {
    uVar16 = 0;
    uVar4 = 0xa9;
    (**(code **)(*in_ECX + 0x73c))(0xa9,0);
    iVar3 = FUN_00559140(uVar4,uVar16);
    if ((iVar3 != -1) && (cVar2 = (**(code **)(*in_ECX + 0x768))(0xa9,1,1,1), cVar2 != '\0')) {
      local_20 = (undefined4 *)0x0;
      local_1c = (uint *)0x0;
      local_18 = 0;
      local_8 = 0xc;
      local_14 = (undefined1 *)0x1;
      FUN_00405f60(0,1,&local_14);
      local_14 = (undefined1 *)0x1;
      if ((local_20 == (undefined4 *)0x0) ||
         ((uint)(local_18 - (int)local_20 >> 2) <= (uint)((int)local_1c - (int)local_20 >> 2))) {
        FUN_00405f60(local_1c,1,&local_14);
      }
      else {
        *local_1c = 1;
        local_1c = local_1c + 1;
      }
      uVar16 = 0;
      uVar4 = 0xa9;
      (**(code **)(*in_ECX + 0x67c))(0xa9,0,0);
      local_28 = FUN_0054ff60(uVar4,uVar16);
      if ((local_20 == (undefined4 *)0x0) ||
         ((uint)(local_18 - (int)local_20 >> 2) <= (uint)((int)local_1c - (int)local_20 >> 2))) {
        FUN_00405f60(local_1c,1,&local_28);
      }
      else {
        *local_1c = local_28;
        local_1c = local_1c + 1;
      }
      (**(code **)(*in_ECX + 0x28c))(6,local_24,1,0,0);
      local_8 = 0xffffffff;
      if (local_20 != (undefined4 *)0x0) {
        _free(local_20);
      }
    }
  }
  if ((in_ECX[0x557] ^ DAT_012101dc) - (int)(in_ECX + 0x557) != in_ECX[0x558]) {
    FUN_00b170b0(in_ECX + 0x557,0x3f);
  }
  iVar3 = in_ECX[0x558] * 4;
  uVar12 = iVar3 + *(int *)(DAT_012101d8 + 0x44) ^ *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x44))
           ^ DAT_012101dc;
  if (uVar12 != (iVar3 + *(int *)(DAT_012101d8 + 0x48) ^
                 *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48)) ^ DAT_012101dc)) {
    FUN_00b170b0(in_ECX + 0x557,0x40);
  }
  if (uVar12 == 4) {
    puVar8 = in_ECX + 0x979;
    uVar4 = 0xbe;
    (**(code **)(*in_ECX + 0x73c))(0xbe,puVar8);
    iVar3 = FUN_00559140(uVar4,puVar8);
    if ((iVar3 != -1) && (cVar2 = (**(code **)(*in_ECX + 0x768))(0xbe,1,1,1), cVar2 != '\0')) {
      local_20 = (undefined4 *)0x0;
      local_1c = (uint *)0x0;
      local_18 = 0;
      local_8 = 0xd;
      (**(code **)(*in_ECX + 0x67c))(0xbe);
      local_14 = (undefined1 *)FUN_00402060();
      if ((local_20 == (undefined4 *)0x0) ||
         ((uint)(local_18 - (int)local_20 >> 2) <= (uint)((int)local_1c - (int)local_20 >> 2))) {
        FUN_00405f60(local_1c,1,&local_14);
      }
      else {
        *local_1c = (uint)local_14;
        local_1c = local_1c + 1;
      }
      (**(code **)(*in_ECX + 0x28c))(0xf,local_24,1,0,0);
      uVar12 = FUN_00b06f00();
      in_ECX[0x9a1] = uVar12;
      (**(code **)(*in_ECX + 0xf8))(1,in_ECX[0x9a0],0xffffffe2,0xffffffe2,0,0,0,0,0,1);
      local_8 = 0xffffffff;
      if (local_20 != (undefined4 *)0x0) {
        _free(local_20);
      }
    }
  }
  if ((in_ECX[0x557] ^ DAT_012101dc) - (int)(in_ECX + 0x557) != in_ECX[0x558]) {
    FUN_00b170b0(in_ECX + 0x557,0x3f);
  }
  iVar3 = in_ECX[0x558] * 4;
  uVar12 = iVar3 + *(int *)(DAT_012101d8 + 0x44) ^ *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x44))
           ^ DAT_012101dc;
  if (uVar12 != (iVar3 + *(int *)(DAT_012101d8 + 0x48) ^
                 *(uint *)(iVar3 + *(int *)(DAT_012101d8 + 0x48)) ^ DAT_012101dc)) {
    FUN_00b170b0(in_ECX + 0x557,0x40);
  }
  if (uVar12 == 0xf) {
    uVar16 = 0;
    uVar4 = 0;
    (**(code **)(*in_ECX + 0x67c))(0xbe,0,0);
    iVar3 = FUN_0054ff60(uVar4,uVar16);
    uVar12 = in_ECX[0x9a1];
    iVar6 = FUN_00b06f00();
    if ((int)(iVar3 + uVar12) <= iVar6) {
      piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
      cVar2 = (**(code **)(*piVar5 + 0x38))(in_ECX + 0x979);
      if ((cVar2 == '\0') || (iVar3 = FUN_00b06f00(), (int)(in_ECX[0x9a2] + in_ECX[0x9a1]) <= iVar3)
         ) {
        (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
      }
    }
    uVar12 = in_ECX[0x9a0];
    if ((uVar12 != 0) && (*(char *)(uVar12 + 0x13a) != '\0')) {
      (**(code **)(*in_ECX + 0xfc))(uVar12);
    }
  }
  local_30 = &DAT_00f5ae4c;
  iVar3 = DAT_012101d8;
  do {
    puVar8 = in_ECX + 0x557;
    if ((in_ECX[0x557] ^ DAT_012101dc) - (int)puVar8 != in_ECX[0x558]) {
      FUN_00b170b0(puVar8,0x3f);
      iVar3 = DAT_012101d8;
    }
    iVar6 = in_ECX[0x558] * 4;
    local_28 = iVar6 + *(int *)(iVar3 + 0x44) ^ *(uint *)(iVar6 + *(int *)(iVar3 + 0x44)) ^
               DAT_012101dc;
    if (local_28 !=
        (iVar6 + *(int *)(iVar3 + 0x48) ^ *(uint *)(iVar6 + *(int *)(iVar3 + 0x48)) ^ DAT_012101dc))
    {
      FUN_00b170b0(puVar8,0x40);
      iVar3 = DAT_012101d8;
    }
    if (local_28 == 0) {
LAB_004ddeb3:
      puVar8 = local_30;
      uVar12 = *local_30;
      uVar4 = 0;
      (**(code **)(*in_ECX + 0x73c))(uVar12,0);
      iVar6 = FUN_00559140(uVar12,uVar4);
      iVar3 = DAT_012101d8;
      if ((iVar6 != -1) &&
         (cVar2 = (**(code **)(*in_ECX + 0x768))(*puVar8,1,1,1), iVar3 = DAT_012101d8, cVar2 != '\0'
         )) {
        local_20 = (void *)0x0;
        local_1c = (uint *)0x0;
        local_18 = 0;
        local_14 = (undefined1 *)*puVar8;
        local_8 = 0xe;
        FUN_00405f60(0,1,&local_14);
        (**(code **)(*in_ECX + 0x28c))(0xe,local_24,1,0,0);
        local_8 = 0xffffffff;
        if (local_20 != (void *)0x0) {
          _free(local_20);
        }
        local_20 = (undefined4 *)0x0;
        local_1c = (uint *)0x0;
        local_18 = 0;
        iVar3 = DAT_012101d8;
      }
    }
    else {
      if ((*puVar8 ^ DAT_012101dc) - (int)puVar8 != in_ECX[0x558]) {
        FUN_00b170b0(puVar8,0x3f);
        iVar3 = DAT_012101d8;
      }
      iVar6 = in_ECX[0x558] * 4;
      uVar12 = iVar6 + *(int *)(iVar3 + 0x44) ^ *(uint *)(iVar6 + *(int *)(iVar3 + 0x44)) ^
               DAT_012101dc;
      if (uVar12 != (iVar6 + *(int *)(iVar3 + 0x48) ^ *(uint *)(iVar6 + *(int *)(iVar3 + 0x48)) ^
                    DAT_012101dc)) {
        FUN_00b170b0(in_ECX + 0x557,0x40);
        iVar3 = DAT_012101d8;
      }
      puVar8 = local_30;
      if (uVar12 == 0xb) goto LAB_004ddeb3;
    }
    local_30 = puVar8 + 1;
  } while ((int)local_30 < 0xf5ae58);
  if ((in_ECX[0x557] ^ DAT_012101dc) - (int)(in_ECX + 0x557) != in_ECX[0x558]) {
    FUN_00b170b0(in_ECX + 0x557,0x3f);
    iVar3 = DAT_012101d8;
  }
  iVar6 = in_ECX[0x558] * 4;
  uVar12 = iVar6 + *(int *)(iVar3 + 0x44) ^ *(uint *)(iVar6 + *(int *)(iVar3 + 0x44)) ^ DAT_012101dc
  ;
  if (uVar12 != (iVar6 + *(int *)(iVar3 + 0x48) ^ *(uint *)(iVar6 + *(int *)(iVar3 + 0x48)) ^
                DAT_012101dc)) {
    FUN_00b170b0(in_ECX + 0x557,0x40);
    iVar3 = DAT_012101d8;
  }
  if ((((uVar12 != 5) && ((int *)in_ECX[0x8e2] != (int *)0x0)) &&
      (iVar6 = (**(code **)(*(int *)in_ECX[0x8e2] + 0x230))(), iVar3 = DAT_012101d8, iVar6 != 4)) &&
     (iVar6 = (**(code **)(*(int *)in_ECX[0x8e2] + 0x230))(), iVar3 = DAT_012101d8, iVar6 != 5)) {
    piVar5 = (int *)(**(code **)(*in_ECX + 0x738))();
    cVar2 = (**(code **)(*piVar5 + 0x48))(in_ECX + 0x6b8,0);
    iVar3 = DAT_012101d8;
    if (cVar2 != '\0') {
      iVar3 = (**(code **)(*(int *)in_ECX[0x8e2] + 0x35c))();
      if (iVar3 == 0) {
        (**(code **)(*in_ECX + 0x66c))();
        (**(code **)(*(int *)in_ECX[0x8e2] + 0x368))(1);
        iVar3 = DAT_012101d8;
      }
      else {
        iVar6 = (**(code **)(*(int *)in_ECX[0x8e2] + 0x35c))();
        iVar3 = DAT_012101d8;
        if (iVar6 == 1) {
          (**(code **)(*in_ECX + 0x66c))();
          (**(code **)(*(int *)in_ECX[0x8e2] + 0x368))(0);
          iVar3 = DAT_012101d8;
        }
      }
    }
  }
LAB_004de07a:
  if (((int *)in_ECX[0x952] != (int *)0x0) &&
     (cVar2 = (**(code **)(*(int *)in_ECX[0x952] + 0x40))(), iVar3 = DAT_012101d8, cVar2 == '\0')) {
    FUN_004d47d0();
    iVar3 = DAT_012101d8;
  }
  puVar8 = in_ECX + 0x53b;
  iVar6 = 0x17;
  do {
    if (*puVar8 != 0) {
      FUN_00455df0();
      iVar3 = DAT_012101d8;
    }
    puVar8 = puVar8 + 1;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  if ((in_ECX[0x96d] ^ DAT_012101dc) - (int)(in_ECX + 0x96d) != in_ECX[0x96e]) {
    FUN_00b170b0(in_ECX + 0x96d,0x3f);
    iVar3 = DAT_012101d8;
  }
  iVar6 = in_ECX[0x96e] * 4;
  uVar12 = *(int *)(iVar3 + 0x44) + iVar6 ^ *(uint *)(*(int *)(iVar3 + 0x44) + iVar6) ^ DAT_012101dc
  ;
  if (uVar12 != (*(int *)(iVar3 + 0x48) + iVar6 ^ *(uint *)(*(int *)(iVar3 + 0x48) + iVar6) ^
                DAT_012101dc)) {
    FUN_00b170b0(in_ECX + 0x96d,0x40);
  }
  if (uVar12 != 0) {
    FUN_004d23b0();
  }
  FUN_004d1f90();
  iVar3 = FUN_00b06f00();
  if ((300000 < iVar3) && ((char)in_ECX[0x9cd] != '\0')) {
    FUN_004cb400();
    *(undefined1 *)(in_ECX + 0x9cd) = 0;
    *(uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x9c4] * 4) =
         *(int *)(DAT_012101d8 + 0x44) + in_ECX[0x9c4] * 4 ^ DAT_012101dc;
    *(uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x9c4] * 4) =
         *(int *)(DAT_012101d8 + 0x48) + in_ECX[0x9c4] * 4 ^ DAT_012101dc;
    *(uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x9c6] * 4) =
         *(int *)(DAT_012101d8 + 0x44) + in_ECX[0x9c6] * 4 ^ DAT_012101dc;
    *(uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x9c6] * 4) =
         *(int *)(DAT_012101d8 + 0x48) + in_ECX[0x9c6] * 4 ^ DAT_012101dc;
  }
  iVar3 = FUN_00402060();
  if (((iVar3 == 4) && (*(int *)(*(int *)(DAT_01002848 + 0x1058) + 0x28) == 8)) &&
     (cVar2 = FUN_0049c090(), cVar2 != '\0')) {
    iVar3 = (**(code **)(*in_ECX + 0x3fc))();
    iVar6 = (**(code **)(*in_ECX + 0x3f8))();
    if (iVar6 < iVar3 / 10) {
      local_14 = (undefined1 *)FUN_00403c50(0xa4);
      local_8 = 0xf;
      if (local_14 == (undefined1 *)0x0) {
        piVar5 = (int *)0x0;
      }
      else {
        uVar16 = 1;
        uVar4 = 1000;
        iVar3 = (**(code **)(*in_ECX + 0x3fc))(1000,1);
        iVar6 = (**(code **)(*in_ECX + 0x3f8))();
        piVar5 = (int *)FUN_00469db0(iVar3 - iVar6,uVar4,uVar16);
      }
      local_8 = 0xffffffff;
      (**(code **)(*piVar5 + 0x48))();
    }
  }
  FUN_004d8c00();
  FUN_004d1ab0();
  cVar2 = (**(code **)(*in_ECX + 0x34))();
  if (cVar2 == '\0') {
    iVar3 = FUN_00402060();
    iVar6 = FUN_00b06f00();
    if ((iVar3 <= iVar6) && (uVar12 = in_ECX[0xa10], uVar12 != 0)) {
      FUN_004089d0();
      FUN_00401f50(uVar12);
      in_ECX[0xa10] = 0;
      FUN_00404ef0();
    }
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

