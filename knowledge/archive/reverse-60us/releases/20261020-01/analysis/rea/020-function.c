
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0049a1d0(void)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int *in_ECX;
  int iVar12;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  undefined4 extraout_EDX_01;
  undefined4 extraout_EDX_02;
  undefined4 uVar13;
  int *piVar14;
  float10 fVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int local_20;
  uint local_1c;
  uint local_18;
  uint local_a;
  byte local_5;
  
  if (in_ECX[0x40] != 0) {
    local_18 = in_ECX[0x71];
    local_1c = in_ECX[0x70];
    local_5 = *(byte *)((int)in_ECX + 0x1c3);
    if (in_ECX[0x41] != 0) {
      FUN_00a27f60();
      if ((*(int **)(in_ECX[0x3e] + 0x78) != (int *)0x0) &&
         (fVar15 = (float10)(**(code **)(**(int **)(in_ECX[0x3e] + 0x78) + 0x40))(),
         fVar15 < (float10)_DAT_00ccb9d8)) {
        (**(code **)(**(int **)(in_ECX[0x3e] + 0x78) + 0x40))();
        local_5 = FUN_00c01544();
        local_1c = (uint)local_5 << 0x18 | in_ECX[0x70] & 0xffffffU;
        local_18 = local_18 | 0xff000000;
        if (local_5 == 0) {
          return;
        }
      }
      cVar1 = (**(code **)(*in_ECX + 0x138))();
      if (cVar1 != '\0') {
        FUN_00a25830(in_ECX[0x73],in_ECX[0x74]);
      }
    }
    iVar3 = (**(code **)(*in_ECX + 0x28))();
    uVar13 = *(undefined4 *)(iVar3 + 0xc);
    uVar4 = (**(code **)(*in_ECX + 0x94))(uVar13);
    iVar5 = FUN_0050aa00(uVar4,uVar13);
    uVar17 = 0x3f800000;
    iVar3 = (**(code **)(*in_ECX + 0x28))(0x3f800000);
    uVar13 = *(undefined4 *)(iVar3 + 0xc);
    uVar4 = (**(code **)(*in_ECX + 0x9c))(uVar13);
    uVar6 = (**(code **)(*in_ECX + 0x98))(uVar4);
    iVar7 = FUN_0050aa40(uVar6,uVar4,uVar13,uVar17);
    iVar8 = (**(code **)(*in_ECX + 0xc0))();
    iVar3 = in_ECX[0x41];
    local_a = CONCAT31(local_a._1_3_,iVar8 != 1);
    if (iVar3 != 0) {
      if (*(int *)(iVar3 + 0x124) == -1) {
        FUN_00a27f60();
      }
      if (*(int *)(iVar3 + 0xcc) != 0) {
        local_a = CONCAT31(local_a._1_3_,1);
      }
    }
    (**(code **)(*in_ECX + 0x180))(0,iVar5,iVar7,local_a);
    piVar14 = *(int **)in_ECX[0x43];
    if (piVar14 != (int *)in_ECX[0x43]) {
      do {
        if (-1 < piVar14[2]) break;
        if (*(char *)((int)piVar14 + 0x19) == '\0') {
          FUN_00a27f60();
          uVar13 = extraout_EDX;
          if ((local_18 != 0) && (*(char *)((int)piVar14 + 0x1a) == '\x01')) {
            FUN_00a257d0(local_18,local_1c);
            uVar13 = extraout_EDX_00;
          }
          if ((char)local_a == '\0') {
            iVar3 = piVar14[4];
          }
          else {
            iVar3 = -piVar14[4];
          }
          FUN_00a26990(DAT_010da92c,iVar5 + iVar3,piVar14[5] + iVar7,
                       CONCAT31((int3)((uint)uVar13 >> 8),((char)piVar14[6] != '\0') + -1) & local_a
                      );
        }
        piVar14 = (int *)*piVar14;
      } while (piVar14 != (int *)in_ECX[0x43]);
    }
    iVar3 = (**(code **)(*in_ECX + 0xf4))();
    if (iVar3 != 0) {
      if ((char)in_ECX[0x76] != '\0') {
        if ((char)in_ECX[0x78] == '\0') {
          bVar2 = FUN_00c01544();
          local_20 = 0;
          do {
            if (local_20 != 4) {
              uVar16 = 0;
              uVar17 = 0;
              uVar11 = (uint)bVar2 << 0x18 | 0xffffff;
              iVar3 = in_ECX[0x77];
              uVar6 = 1;
              uVar4 = 0;
              iVar12 = (local_20 % 3 + -1) * in_ECX[0x79] + iVar7;
              iVar8 = (local_20 / 3 + -1) * in_ECX[0x79] + iVar5;
              uVar13 = DAT_010da92c;
              uVar9 = local_a;
              (**(code **)(*in_ECX + 0xf4))(DAT_010da92c,iVar8,iVar12,local_a,0,1,iVar3,uVar11,0,0);
              FUN_00a26220(uVar13,iVar8,iVar12,uVar9,uVar4,uVar6,iVar3,uVar11,uVar17,uVar16);
            }
            local_20 = local_20 + 1;
          } while (local_20 < 9);
        }
        else {
          iVar3 = FUN_008ae0f0(0);
          iVar3 = iVar3 % 3 + -1;
          if (iVar3 == 0) {
            uVar9 = FUN_008ae0f0(0);
            uVar9 = uVar9 & 0x80000001;
            if ((int)uVar9 < 0) {
              uVar9 = (uVar9 - 1 | 0xfffffffe) + 1;
            }
            uVar9 = -(uint)(uVar9 != 0) & 2;
          }
          else {
            iVar8 = FUN_008ae0f0(0);
            uVar9 = iVar8 % 3;
          }
          iVar8 = in_ECX[0x79];
          uVar16 = 0;
          uVar17 = 0;
          iVar10 = FUN_00c01544(0,0);
          iVar12 = in_ECX[0x77];
          uVar11 = iVar10 << 0x18 | 0xffffff;
          uVar6 = 1;
          uVar4 = 0;
          iVar10 = iVar8 * (uVar9 - 1) + iVar7;
          iVar3 = iVar8 * iVar3 + iVar5;
          uVar13 = DAT_010da92c;
          uVar9 = local_a;
          (**(code **)(*in_ECX + 0xf4))(DAT_010da92c,iVar3,iVar10,local_a,0,1,iVar12,uVar11);
          FUN_00a26220(uVar13,iVar3,iVar10,uVar9,uVar4,uVar6,iVar12,uVar11,uVar17,uVar16);
        }
      }
      if (local_5 != 0) {
        if (in_ECX[0x52] == 0) {
          iVar3 = in_ECX[0x7c] + iVar7;
          iVar8 = in_ECX[0x7b] + iVar5;
          uVar13 = DAT_010da92c;
          uVar9 = local_a;
          (**(code **)(*in_ECX + 0xf4))(DAT_010da92c,iVar8,iVar3,local_a);
          FUN_00a26990(uVar13,iVar8,iVar3,uVar9);
        }
        else {
          FUN_00a2d300(in_ECX[0x7b] + iVar5,in_ECX[0x7c] + iVar7,local_a);
        }
      }
    }
    if (piVar14 != (int *)in_ECX[0x43]) {
      do {
        if (*(char *)((int)piVar14 + 0x19) == '\0') {
          FUN_00a27f60();
          uVar13 = extraout_EDX_01;
          if ((local_18 != 0) && (*(char *)((int)piVar14 + 0x1a) == '\x01')) {
            FUN_00a257d0(local_18,local_1c);
            uVar13 = extraout_EDX_02;
          }
          if ((char)local_a == '\0') {
            iVar3 = piVar14[4];
          }
          else {
            iVar3 = -piVar14[4];
          }
          FUN_00a26990(DAT_010da92c,iVar5 + iVar3,piVar14[5] + iVar7,
                       CONCAT31((int3)((uint)uVar13 >> 8),((char)piVar14[6] != '\0') + -1) & local_a
                      );
        }
        piVar14 = (int *)*piVar14;
      } while (piVar14 != (int *)in_ECX[0x43]);
    }
    (**(code **)(*in_ECX + 0x180))(1,iVar5,iVar7,local_a);
    if (in_ECX[99] != 0) {
      FUN_00527d20(iVar5,iVar7,0xff);
    }
    if (in_ECX[100] != 0) {
      FUN_00527440(iVar5,iVar7);
    }
  }
  return;
}

