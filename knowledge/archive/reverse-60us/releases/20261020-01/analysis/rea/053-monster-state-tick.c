
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004fb720(void)

{
  undefined4 *puVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int *in_ECX;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  float10 fVar12;
  float fVar13;
  undefined1 local_34 [4];
  void *local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined1 local_24 [4];
  void *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint *local_14;
  float local_10;
  int *local_c;
  uint local_8;
  
  for (uVar10 = 0; (in_ECX[0x69e] != 0 && (uVar10 < (uint)((in_ECX[0x69f] - in_ECX[0x69e]) / 0x24)))
      ; uVar10 = uVar10 + 1) {
    FUN_0074f970();
  }
  for (uVar10 = 0; (in_ECX[0x6a2] != 0 && (uVar10 < (uint)((in_ECX[0x6a3] - in_ECX[0x6a2]) / 0x18)))
      ; uVar10 = uVar10 + 1) {
    FUN_0074f790();
  }
  if ((((in_ECX[0x69e] != 0) &&
       (local_14 = (uint *)((in_ECX[0x69f] - in_ECX[0x69e]) / 0x24), local_14 != (uint *)0x0)) &&
      (piVar6 = (int *)in_ECX[0x906], piVar6 != (int *)0x0)) &&
     (in_ECX[0x907] - (int)piVar6 >> 2 != 0)) {
    if ((piVar6 == (int *)0x0) || (in_ECX[0x907] - (int)piVar6 >> 2 == 0)) {
                    /* WARNING: Subroutine does not return */
      FUN_004e3aa0();
    }
    if (*piVar6 != 0) {
      piVar6 = (int *)in_ECX[0x906];
      if ((piVar6 == (int *)0x0) || (in_ECX[0x907] - (int)piVar6 >> 2 == 0)) {
                    /* WARNING: Subroutine does not return */
        FUN_004e3aa0();
      }
      if (*(char *)(*piVar6 + 0x13a) != '\0') {
        puVar1 = (undefined4 *)in_ECX[0x906];
        if ((puVar1 == (undefined4 *)0x0) || (in_ECX[0x907] - (int)puVar1 >> 2 == 0)) {
                    /* WARNING: Subroutine does not return */
          FUN_004e3aa0();
        }
        (**(code **)(*in_ECX + 0xfc))(*puVar1);
      }
    }
    iVar11 = in_ECX[0x906];
    if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 2)) {
                    /* WARNING: Subroutine does not return */
      FUN_004e3aa0();
    }
    if (*(int *)(iVar11 + 4) != 0) {
      iVar11 = in_ECX[0x906];
      if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 3)) {
                    /* WARNING: Subroutine does not return */
        FUN_004e3aa0();
      }
      if (*(int *)(iVar11 + 8) != 0) {
        iVar11 = in_ECX[0x906];
        if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 2)) {
                    /* WARNING: Subroutine does not return */
          FUN_004e3aa0();
        }
        if (*(char *)(*(int *)(iVar11 + 4) + 0x13a) != '\0') {
          iVar11 = in_ECX[0x906];
          if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 3)) {
                    /* WARNING: Subroutine does not return */
            FUN_004e3aa0();
          }
          if (*(char *)(*(int *)(iVar11 + 8) + 0x13a) != '\0') {
            iVar11 = in_ECX[0x906];
            if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 2)) {
                    /* WARNING: Subroutine does not return */
              FUN_004e3aa0();
            }
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar11 + 4));
            iVar11 = in_ECX[0x906];
            if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 3)) {
                    /* WARNING: Subroutine does not return */
              FUN_004e3aa0();
            }
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar11 + 8));
          }
        }
      }
    }
    iVar11 = in_ECX[0x906];
    if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 4)) {
                    /* WARNING: Subroutine does not return */
      FUN_004e3aa0();
    }
    if (*(int *)(iVar11 + 0xc) != 0) {
      iVar11 = in_ECX[0x906];
      if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 5)) {
                    /* WARNING: Subroutine does not return */
        FUN_004e3aa0();
      }
      if (*(int *)(iVar11 + 0x10) != 0) {
        iVar11 = in_ECX[0x906];
        if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 4)) {
                    /* WARNING: Subroutine does not return */
          FUN_004e3aa0();
        }
        if (*(char *)(*(int *)(iVar11 + 0xc) + 0x13a) != '\0') {
          iVar11 = in_ECX[0x906];
          if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 5)) {
                    /* WARNING: Subroutine does not return */
            FUN_004e3aa0();
          }
          if (*(char *)(*(int *)(iVar11 + 0x10) + 0x13a) != '\0') {
            iVar11 = in_ECX[0x906];
            if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 4)) {
                    /* WARNING: Subroutine does not return */
              FUN_004e3aa0();
            }
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar11 + 0xc));
            iVar11 = in_ECX[0x906];
            if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 5)) {
                    /* WARNING: Subroutine does not return */
              FUN_004e3aa0();
            }
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar11 + 0x10));
          }
        }
      }
    }
  }
  if (((in_ECX[0x6a9] != 0) && (piVar6 = (int *)in_ECX[0x906], piVar6 != (int *)0x0)) &&
     (in_ECX[0x907] - (int)piVar6 >> 2 != 0)) {
    if ((piVar6 == (int *)0x0) || (in_ECX[0x907] - (int)piVar6 >> 2 == 0)) {
                    /* WARNING: Subroutine does not return */
      FUN_004e3aa0();
    }
    if (*piVar6 != 0) {
      piVar6 = (int *)in_ECX[0x906];
      if ((piVar6 == (int *)0x0) || (in_ECX[0x907] - (int)piVar6 >> 2 == 0)) {
                    /* WARNING: Subroutine does not return */
        FUN_004e3aa0();
      }
      if (*(char *)(*piVar6 + 0x13a) != '\0') {
        puVar1 = (undefined4 *)in_ECX[0x906];
        if ((puVar1 == (undefined4 *)0x0) || (in_ECX[0x907] - (int)puVar1 >> 2 == 0)) {
                    /* WARNING: Subroutine does not return */
          FUN_004e3aa0();
        }
        (**(code **)(*in_ECX + 0xfc))(*puVar1);
      }
    }
    iVar11 = in_ECX[0x906];
    if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 2)) {
                    /* WARNING: Subroutine does not return */
      FUN_004e3aa0();
    }
    if (*(int *)(iVar11 + 4) != 0) {
      iVar11 = in_ECX[0x906];
      if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 3)) {
                    /* WARNING: Subroutine does not return */
        FUN_004e3aa0();
      }
      if (*(int *)(iVar11 + 8) != 0) {
        iVar11 = in_ECX[0x906];
        if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 2)) {
                    /* WARNING: Subroutine does not return */
          FUN_004e3aa0();
        }
        if (*(char *)(*(int *)(iVar11 + 4) + 0x13a) != '\0') {
          iVar11 = in_ECX[0x906];
          if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 3)) {
                    /* WARNING: Subroutine does not return */
            FUN_004e3aa0();
          }
          if (*(char *)(*(int *)(iVar11 + 8) + 0x13a) != '\0') {
            iVar11 = in_ECX[0x906];
            if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 2)) {
                    /* WARNING: Subroutine does not return */
              FUN_004e3aa0();
            }
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar11 + 4));
            iVar11 = in_ECX[0x906];
            if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 3)) {
                    /* WARNING: Subroutine does not return */
              FUN_004e3aa0();
            }
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar11 + 8));
          }
        }
      }
    }
    iVar11 = in_ECX[0x906];
    if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 4)) {
                    /* WARNING: Subroutine does not return */
      FUN_004e3aa0();
    }
    if (*(int *)(iVar11 + 0xc) != 0) {
      iVar11 = in_ECX[0x906];
      if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 5)) {
                    /* WARNING: Subroutine does not return */
        FUN_004e3aa0();
      }
      if (*(int *)(iVar11 + 0x10) != 0) {
        iVar11 = in_ECX[0x906];
        if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 4)) {
                    /* WARNING: Subroutine does not return */
          FUN_004e3aa0();
        }
        if (*(char *)(*(int *)(iVar11 + 0xc) + 0x13a) != '\0') {
          iVar11 = in_ECX[0x906];
          if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 5)) {
                    /* WARNING: Subroutine does not return */
            FUN_004e3aa0();
          }
          if (*(char *)(*(int *)(iVar11 + 0x10) + 0x13a) != '\0') {
            iVar11 = in_ECX[0x906];
            if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 4)) {
                    /* WARNING: Subroutine does not return */
              FUN_004e3aa0();
            }
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar11 + 0xc));
            iVar11 = in_ECX[0x906];
            if ((iVar11 == 0) || ((uint)(in_ECX[0x907] - iVar11 >> 2) < 5)) {
                    /* WARNING: Subroutine does not return */
              FUN_004e3aa0();
            }
            (**(code **)(*in_ECX + 0xfc))(*(undefined4 *)(iVar11 + 0x10));
          }
        }
      }
    }
  }
  iVar11 = 0;
  local_10 = 0.0;
  for (uVar10 = 0; (in_ECX[0x8fb] != 0 && (uVar10 < (uint)(in_ECX[0x8fc] - in_ECX[0x8fb] >> 6)));
      uVar10 = uVar10 + 1) {
    local_c = (int *)(in_ECX[0x8d6] + uVar10 * 4);
    iVar3 = FUN_00b06f00();
    if (*local_c < iVar3) {
      FUN_00b06f00();
      iVar3 = in_ECX[0x758];
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(iVar3 + 4 + (int)local_10) * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc ^ 1;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(iVar3 + (int)local_10 + 4) * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc ^ 1;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(in_ECX[0x8fb] + 0x1c + iVar11) * 4)
      ;
      iVar3 = in_ECX[0x8fb] + iVar11;
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(iVar3 + 0x1c) * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(iVar3 + 0x24) * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(iVar3 + 0x24) * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      puVar7 = (uint *)(in_ECX[0x902] + (uVar10 >> 5) * 4);
      local_c = (int *)0x1;
      *puVar7 = *puVar7 & ~(1 << ((byte)uVar10 & 0x1f));
    }
    local_10 = (float)((int)local_10 + 0x60);
    iVar11 = iVar11 + 0x40;
  }
  for (uVar10 = 0; (in_ECX[0x8c2] != 0 && (uVar10 < (uint)((in_ECX[0x8c3] - in_ECX[0x8c2]) / 0x24)))
      ; uVar10 = uVar10 + 1) {
    FUN_0074e360();
  }
  uVar10 = 0;
  local_10 = 0.0;
  local_c = (int *)0x0;
  while( true ) {
    if ((in_ECX[0x8be] == 0) || ((uint)((in_ECX[0x8bf] - in_ECX[0x8be]) / 0x24) <= uVar10))
    goto LAB_004fbf76;
    iVar3 = in_ECX[0x8be] + (int)local_c;
    iVar11 = FUN_00b06f00();
    if (*(int *)(iVar3 + 0x14) < iVar11) break;
    uVar10 = uVar10 + 1;
    local_c = (int *)((int)local_c + 0x24);
  }
  iVar11 = in_ECX[0x758];
  iVar3 = *(int *)(in_ECX[0x8be] + uVar10 * 0x24 + 4) * 0x60;
  puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(iVar3 + 4 + iVar11) * 4);
  *puVar7 = (uint)puVar7 ^ DAT_012101dc ^ 1;
  puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(iVar3 + iVar11 + 4) * 4);
  *puVar7 = (uint)puVar7 ^ DAT_012101dc ^ 1;
  puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x8f1] * 4);
  *puVar7 = (uint)puVar7 ^ DAT_012101dc;
  puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x8f1] * 4);
  *puVar7 = (uint)puVar7 ^ DAT_012101dc;
  puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x8f3] * 4);
  *puVar7 = (uint)puVar7 ^ DAT_012101dc;
  puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x8f3] * 4);
  *puVar7 = (uint)puVar7 ^ DAT_012101dc;
LAB_004fbf76:
  local_c = (int *)0x0;
  iVar11 = DAT_012101d8;
  for (local_8 = 0;
      (in_ECX[0x8be] != 0 && (local_8 < (uint)((in_ECX[0x8bf] - in_ECX[0x8be]) / 0x24)));
      local_8 = local_8 + 1) {
    if ((char)in_ECX[0x8fe] == '\0') {
      piVar6 = in_ECX + 0x60a;
      if ((in_ECX[0x60a] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x60b]) {
        FUN_00b170b0(piVar6,0x3f);
        iVar11 = DAT_012101d8;
      }
      iVar3 = in_ECX[0x60b] * 4;
      uVar10 = *(uint *)(*(int *)(iVar11 + 0x44) + iVar3) ^ *(int *)(iVar11 + 0x44) + iVar3 ^
               DAT_012101dc;
      local_14 = (uint *)(iVar3 + *(int *)(iVar11 + 0x48));
      if (uVar10 != ((uint)local_14 ^ DAT_012101dc ^ *local_14)) {
        FUN_00b170b0(piVar6,0x40);
        iVar11 = DAT_012101d8;
      }
      piVar6 = local_c;
      if (((uVar10 == *(uint *)(in_ECX[0x8be] + 4 + (int)local_c)) &&
          (iVar3 = (**(code **)(*in_ECX + 0xf4))(), iVar11 = DAT_012101d8,
          *(char *)(iVar3 + 0x13a) != '\0')) &&
         (iVar3 = (**(code **)(*in_ECX + 0x230))(), iVar11 = DAT_012101d8, iVar3 != 0xe)) {
        iVar11 = in_ECX[0x8be] + (int)piVar6;
        if (*(int *)(in_ECX[0x8be] + 8 + (int)piVar6) == 1) {
          local_10 = (float)FUN_007505c0(*(undefined4 *)(iVar11 + 0x18));
        }
        else if (*(int *)(iVar11 + 8) == 0) {
          local_10 = (float)FUN_007503a0(*(undefined4 *)(iVar11 + 0x18));
        }
        else if ((*(int *)(iVar11 + 8) == 2) && (*(char *)((int)in_ECX + 0x23f9) != '\0')) {
          if (in_ECX[0x8ff] != 0) {
            local_10 = (float)FUN_00750890(*(undefined4 *)(iVar11 + 0x18),in_ECX[0x8ff]);
          }
          in_ECX[0x8ff] = 0;
          *(undefined1 *)((int)in_ECX + 0x23f9) = 0;
        }
        iVar11 = *(int *)(in_ECX[0x8be] + 0x20 + (int)piVar6);
        iVar3 = in_ECX[0x8be] + (int)piVar6;
        if (iVar11 != -2) {
          if (iVar11 == -1) {
            FUN_0074fd70(local_34,local_10,*(undefined4 *)(iVar3 + 0x1c));
            if (local_30 != (void *)0x0) {
              _free(local_30);
            }
            local_30 = (void *)0x0;
            local_2c = 0;
            local_28 = 0;
          }
          else {
            FUN_00750050(local_24,local_10,*(undefined4 *)(iVar3 + 0x1c),
                         *(undefined4 *)(iVar3 + 0x20));
            if (local_20 != (void *)0x0) {
              _free(local_20);
            }
            local_20 = (void *)0x0;
            local_1c = 0;
            local_18 = 0;
          }
        }
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x8e1] * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x8e1] * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x8e3] * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x8e3] * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        FUN_00b06f60(0,0);
        *(undefined1 *)(in_ECX + 0x8fe) = 1;
        iVar11 = *(int *)(in_ECX[0x8be] + (int)piVar6 + 4) * 0x60 + in_ECX[0x758];
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(iVar11 + 4) * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(iVar11 + 4) * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x8f1] * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x8f1] * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x8f3] * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x8f3] * 4);
        *puVar7 = (uint)puVar7 ^ DAT_012101dc;
        FUN_00b06f60(0,0);
        iVar11 = DAT_012101d8;
      }
    }
    piVar6 = in_ECX + 0x60a;
    if ((in_ECX[0x60a] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x60b]) {
      FUN_00b170b0(piVar6,0x3f);
      iVar11 = DAT_012101d8;
    }
    puVar7 = (uint *)(*(int *)(iVar11 + 0x44) + in_ECX[0x60b] * 4);
    uVar10 = (uint)puVar7 ^ DAT_012101dc ^ *puVar7;
    puVar7 = (uint *)(in_ECX[0x60b] * 4 + *(int *)(iVar11 + 0x48));
    if (uVar10 != (*puVar7 ^ (uint)puVar7 ^ DAT_012101dc)) {
      FUN_00b170b0(piVar6,0x40);
      iVar11 = DAT_012101d8;
    }
    if (((uVar10 == *(uint *)(in_ECX[0x8be] + 4 + (int)local_c)) &&
        (iVar3 = (**(code **)(*in_ECX + 0x230))(), iVar11 = DAT_012101d8, iVar3 != 0xe)) &&
       ((iVar9 = in_ECX[0x8be] + (int)local_c, iVar3 = FUN_00b06f00(), iVar11 = DAT_012101d8,
        *(int *)(iVar9 + 0x10) < iVar3 && ((char)in_ECX[0x8fe] != '\0')))) {
      FUN_0074fcd0(8,*(undefined4 *)(in_ECX[0x8be] + (int)local_c + 0xc));
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x8e1] * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x8e1] * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x8e3] * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x8e3] * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      *(undefined1 *)(in_ECX + 0x8fe) = 0;
      iVar11 = DAT_012101d8;
    }
    local_c = (int *)((int)local_c + 0x24);
  }
  piVar6 = in_ECX + 0x557;
  if ((in_ECX[0x557] ^ DAT_012101dc) - (int)piVar6 != in_ECX[0x558]) {
    FUN_00b170b0(piVar6,0x3f);
    iVar11 = DAT_012101d8;
  }
  iVar3 = in_ECX[0x558] * 4;
  uVar10 = *(uint *)(*(int *)(iVar11 + 0x44) + iVar3) ^ *(int *)(iVar11 + 0x44) + iVar3 ^
           DAT_012101dc;
  puVar7 = (uint *)(iVar3 + *(int *)(iVar11 + 0x48));
  if (uVar10 != (*puVar7 ^ (uint)puVar7 ^ DAT_012101dc)) {
    FUN_00b170b0(piVar6,0x40);
  }
  if (uVar10 == 8) {
    local_10 = 0.0;
    for (uVar10 = 0;
        (in_ECX[0x8ba] != 0 && (uVar10 < (uint)((in_ECX[0x8bb] - in_ECX[0x8ba]) / 0x28)));
        uVar10 = uVar10 + 1) {
      iVar3 = in_ECX[0x8ba] + (int)local_10;
      iVar11 = FUN_00402060();
      if (iVar11 == *(int *)(iVar3 + 4)) {
        FUN_0074d120();
      }
      local_10 = (float)((int)local_10 + 0x28);
    }
  }
  FUN_004bc7d0();
  if ((in_ECX[0x6e0] == 0) && (cVar2 = (**(code **)(*in_ECX + 0x38))(), cVar2 == '\0')) {
    if (in_ECX[0x68c] == 0x1b) {
      iVar11 = (**(code **)(*in_ECX + 0x94))();
      if (iVar11 == in_ECX[0x746]) {
        (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
      }
      iVar11 = (**(code **)(*in_ECX + 0x98))();
      if (iVar11 == in_ECX[0x747]) {
        (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
      }
      if (in_ECX[0x745] == 1) {
        iVar3 = (**(code **)(*in_ECX + 0x94))();
        iVar11 = in_ECX[0x746];
        uVar10 = iVar3 - iVar11 >> 0x1f;
        iVar9 = (**(code **)(*in_ECX + 0x98))();
        uVar8 = iVar9 - in_ECX[0x747] >> 0x1f;
        if (((iVar3 - iVar11 ^ uVar10) == uVar10) && ((iVar9 - in_ECX[0x747] ^ uVar8) == uVar8)) {
          (**(code **)(*in_ECX + 0x5f0))(0xf);
        }
      }
    }
    else if (in_ECX[0x68c] == 0x1c) {
      cVar2 = FUN_004f2f60();
      if (cVar2 != '\0') {
        (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
      }
      cVar2 = FUN_004f3040();
      if (cVar2 != '\0') {
        (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
      }
      FUN_004f6180();
    }
  }
  else {
    (**(code **)(*in_ECX + 0x6a0))();
  }
  if ((*(byte *)(in_ECX + 0x133) & 1) != 0) {
    (**(code **)(*in_ECX + 0x67c))();
  }
  iVar11 = FUN_004fae00(0x111,0,0,0xffffffff);
  if (iVar11 == 0) {
    if ((char)in_ECX[0x813] == '\x01') {
      *(undefined1 *)(in_ECX + 0x813) = 0;
      iVar11 = FUN_008ae0f0(0);
      if (iVar11 % 100 < 0xf) {
        (**(code **)(*in_ECX + 0x544))(0x1a,0xffffffff);
      }
    }
  }
  else if ((0 < iVar11) && ((char)in_ECX[0x813] == '\0')) {
    iVar11 = FUN_008ae0f0(0);
    if (iVar11 % 100 < 0xf) {
      (**(code **)(*in_ECX + 0x544))(0x19,0xffffffff);
    }
    *(undefined1 *)(in_ECX + 0x813) = 1;
  }
  if (((int *)in_ECX[0x821] != (int *)0x0) &&
     (cVar2 = (**(code **)(*(int *)in_ECX[0x821] + 0x3dc))(), cVar2 != '\0')) {
    (**(code **)(*in_ECX + 0x354))(0);
  }
  if ((in_ECX[0x823] != 0) && (in_ECX[0x821] == 0)) {
    cVar2 = *(char *)(in_ECX[0x823] + 1);
    if (cVar2 == '\x01') {
      iVar11 = (**(code **)(*in_ECX + 0x1c4))();
      if (iVar11 != 0x65) {
        (**(code **)(*in_ECX + 0x1c0))(0x65);
      }
    }
    else if (((cVar2 == '\x02') && (iVar11 = FUN_00402060(), iVar11 != 0xd)) &&
            (cVar2 = FUN_0049c090(), cVar2 != '\0')) {
      if (in_ECX[0x944] != 0) {
        FUN_004f5cc0(in_ECX[0x944]);
      }
      (**(code **)(*in_ECX + 0x28c))(0xd,0,3,0,0);
    }
  }
  cVar2 = FUN_0049c090();
  if ((cVar2 != '\0') && (iVar11 = (**(code **)(*in_ECX + 0x640))(), iVar11 != 0)) {
    iVar11 = FUN_00b06f00();
    iVar3 = (**(code **)(*in_ECX + 0x640))();
    if ((iVar3 <= iVar11) &&
       (((iVar11 = FUN_00402060(), iVar11 == 0 || (iVar11 = FUN_00402060(), iVar11 == 1)) ||
        ((iVar11 = FUN_00402060(), iVar11 == 2 ||
         ((iVar11 = FUN_00402060(), iVar11 == 3 || (iVar11 = FUN_00402060(), iVar11 == 9)))))))) {
      (**(code **)(*in_ECX + 0x28c))(0xd,0,3,0,0);
    }
  }
  iVar11 = (**(code **)(*DAT_01003164 + 0x9c))();
  if ((DAT_0104f1d4 == iVar11) &&
     ((in_ECX[0x13c] == 0 ||
      ((iVar11 = FUN_00b06f00(), in_ECX[0x76d] <= iVar11 &&
       (cVar2 = (**(code **)(*in_ECX + 0x600))(), cVar2 != '\0')))))) {
    (**(code **)(*in_ECX + 0x698))();
  }
  cVar2 = (**(code **)(*in_ECX + 0x3dc))();
  if ((cVar2 == '\0') && (cVar2 = (**(code **)(*in_ECX + 0x4f0))(), cVar2 != '\0')) {
    puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + in_ECX[0x619] * 4);
    *puVar7 = (uint)puVar7 ^ DAT_012101dc;
    puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + in_ECX[0x619] * 4);
    *puVar7 = (uint)puVar7 ^ DAT_012101dc;
  }
  uVar4 = FUN_00402060();
  switch(uVar4) {
  case 0:
    FUN_004f2ec0();
    iVar11 = 0;
    for (uVar10 = 0;
        (in_ECX[0x886] != 0 && (uVar10 < (uint)((in_ECX[0x887] - in_ECX[0x886]) / 0x78)));
        uVar10 = uVar10 + 1) {
      *(undefined4 *)(in_ECX[0x886] + iVar11 + 0x58) =
           *(undefined4 *)(in_ECX[0x886] + 0x4c + iVar11);
      iVar11 = iVar11 + 0x78;
    }
    break;
  case 5:
    if (in_ECX[0x41] != 0) {
      cVar2 = (**(code **)(*in_ECX + 0x5a0))();
      if (cVar2 == '\0') {
        if (*(int *)(DAT_01002848 + 0x19a8) == 2) {
          iVar11 = FUN_00b06f00();
          if ((0x19 < iVar11) && (iVar11 = FUN_00b06f00(), iVar11 <= in_ECX[0x786])) {
            iVar11 = FUN_00b06f00(100);
            fVar12 = (float10)FUN_00b099b0(0x3f800000,0x3f866666,iVar11 + (100 - in_ECX[0x786]));
            fVar13 = (float)fVar12;
            fVar12 = fVar12 * (float10)(float)in_ECX[0x93e];
            in_ECX[0x93e] = (int)(float)fVar12;
            local_10 = fVar13;
            if (fVar12 < (float10)_DAT_00cd0928 != (fVar12 == (float10)_DAT_00cd0928)) {
              (**(code **)(*in_ECX + 0xf4))(fVar13);
              FUN_00a297b0(fVar13);
              piVar6 = in_ECX + 0x53b;
              iVar11 = 0x17;
              do {
                if (*piVar6 != 0) {
                  FUN_004577f0(local_10);
                }
                piVar6 = piVar6 + 1;
                iVar11 = iVar11 + -1;
              } while (iVar11 != 0);
            }
            FUN_00511040(0,0);
            FUN_00511040(1,0);
            FUN_00511040(2,0);
            FUN_00404ef0();
            FUN_00b06f60(0,0);
          }
        }
        else {
          iVar11 = FUN_00b06f00();
          FUN_00b099b0(0x437f0000,0,iVar11 + (100 - in_ECX[0x786]),100);
          iVar11 = FUN_00c01544();
          if (iVar11 * 0x1000000 != 0xff000000) {
            uVar10 = in_ECX[0x70] & 0xffffffU | iVar11 * 0x1000000;
            uVar8 = in_ECX[0x71] | 0xff000000;
            goto LAB_004fcd39;
          }
          FUN_00498e60(0xff000000);
        }
      }
      else {
        iVar11 = FUN_00b06f00();
        FUN_00b099b0(0x437f0000,0x42c80000,iVar11 + (100 - in_ECX[0x786]),100);
        uVar10 = FUN_00c01544();
        uVar10 = uVar10 & 0xff;
        uVar10 = (uVar10 << 8 | uVar10) << 8 | uVar10;
        if (uVar10 == 0xffffff) {
          FUN_00498e60(0xffffff);
        }
        else {
          uVar10 = in_ECX[0x70] & 0xff000000U | uVar10;
          uVar8 = in_ECX[0x71] | 0xffffff;
LAB_004fcd39:
          in_ECX[0x70] = uVar10;
          in_ECX[0x71] = uVar8;
        }
      }
    }
    iVar11 = FUN_00b06f00();
    if ((in_ECX[0x786] <= iVar11) && ((char)in_ECX[0x7a] == '\0')) {
      (**(code **)(*in_ECX + 0x654))();
    }
    break;
  case 8:
    FUN_004f8240(0);
    uVar4 = FUN_00402060();
    FUN_004f5da0(uVar4);
    uVar10 = (**(code **)(*in_ECX + 0x4b4))();
    if (((-1 < (int)uVar10) && (*(int *)(in_ECX[0x8d6] + uVar10 * 4) != 0)) &&
       ((*(uint *)(in_ECX[0x902] + (uVar10 >> 5) * 4) & 1 << ((byte)uVar10 & 0x1f)) == 0)) {
      iVar11 = uVar10 * 0x60 + in_ECX[0x758];
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + *(int *)(iVar11 + 4) * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      puVar7 = (uint *)(*(int *)(DAT_012101d8 + 0x48) + *(int *)(iVar11 + 4) * 4);
      *puVar7 = (uint)puVar7 ^ DAT_012101dc;
      FUN_00404ef0();
      FUN_00b06f60(0,0);
      puVar7 = (uint *)(in_ECX[0x902] + (uVar10 >> 5) * 4);
      *puVar7 = *puVar7 | 1 << ((byte)uVar10 & 0x1f);
    }
    break;
  case 10:
    iVar11 = (**(code **)(*in_ECX + 0xf4))();
    if (((iVar11 != 0) &&
        (iVar11 = (**(code **)(*in_ECX + 0xf4))(), *(char *)(iVar11 + 0x13a) != '\0')) &&
       (cVar2 = FUN_0049c090(), cVar2 != '\0')) {
      (**(code **)(*in_ECX + 0x28c))(0,0,0,0,0);
    }
    break;
  case 0xb:
    iVar11 = (**(code **)(*in_ECX + 0x9c))();
    if (iVar11 == 0) {
      FUN_00a6ad70(5,0,0);
    }
    break;
  case 0xd:
    cVar2 = FUN_0049c090();
    if ((cVar2 != '\0') && (iVar11 = FUN_00b06f00(), 0x351 < iVar11)) {
      (**(code **)(*in_ECX + 0x654))();
    }
    iVar11 = FUN_00b06f00();
    if (299 < iVar11) {
      iVar11 = FUN_00b06f00();
      FUN_00b099b0(0x437f0000,0,iVar11 + -300,0x226);
      iVar11 = FUN_00c01544();
      if (iVar11 * 0x1000000 == 0xff000000) {
        FUN_00498e60(0xff000000);
      }
      else {
        in_ECX[0x70] = in_ECX[0x70] & 0xffffffU | iVar11 * 0x1000000;
        in_ECX[0x71] = in_ECX[0x71] | 0xff000000;
      }
    }
  }
  iVar11 = 0;
  local_10 = 0.0;
  do {
    while( true ) {
      if ((in_ECX[0x897] == 0) || ((uint)((in_ECX[0x898] - in_ECX[0x897]) / 0x14) <= (uint)local_10)
         ) {
        iVar11 = (**(code **)(*in_ECX + 0x358))();
        if ((iVar11 != 0) && (iVar11 = (**(code **)(*in_ECX + 0x358))(), iVar11 != DAT_0104f1d4)) {
          piVar6 = (int *)(**(code **)(*in_ECX + 0x358))();
          cVar2 = (**(code **)(*piVar6 + 0x2c))(0x111);
          if (cVar2 != '\0') {
            *(undefined1 *)((int)in_ECX + 0x1c3) = 0x80;
            in_ECX[0x71] = in_ECX[0x71] | 0xff000000;
          }
        }
        return;
      }
      iVar3 = in_ECX[0x897] + iVar11;
      if (0 < *(int *)(in_ECX[0x897] + 0x10 + iVar11)) break;
      *(undefined1 *)(iVar3 + 0xc) = 1;
LAB_004fce02:
      local_10 = (float)((int)local_10 + 1);
      iVar11 = iVar11 + 0x14;
    }
    iVar3 = (int)(100 / (longlong)*(int *)(iVar3 + 0x10));
    if (iVar3 < 1) goto LAB_004fce02;
    iVar9 = (**(code **)(*in_ECX + 0x238))();
    iVar5 = (**(code **)(*in_ECX + 0x234))();
    if ((iVar9 / iVar3 <= iVar5) || (*(char *)(iVar11 + in_ECX[0x897] + 0xc) != '\0'))
    goto LAB_004fce02;
    local_10 = (float)((int)local_10 + 1);
    *(undefined1 *)(iVar11 + in_ECX[0x897] + 0xc) = 1;
    iVar11 = iVar11 + 0x14;
  } while( true );
}

