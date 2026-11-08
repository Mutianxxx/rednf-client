
void FUN_00a26990(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  uint3 uVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  char *in_ECX;
  uint uVar7;
  int iVar8;
  undefined4 uVar9;
  undefined1 *puVar10;
  bool bVar11;
  undefined4 uVar12;
  int *local_c;
  
  FUN_00a24460();
  local_c = (int *)**(int **)(in_ECX + 0x180);
  if (local_c != *(int **)(in_ECX + 0x180)) {
    do {
      if (-1 < local_c[2]) break;
      if (local_c[3] != 0) {
        FUN_00a26990(param_1,param_2,param_3,param_4);
      }
      local_c = (int *)*local_c;
    } while (local_c != (int *)*(int *)(in_ECX + 0x180));
  }
  if (*(int *)(in_ECX + 0x40) != 0) {
    for (uVar7 = *(uint *)(in_ECX + 0x44);
        uVar7 != *(int *)(in_ECX + 0x44) + *(int *)(in_ECX + 0x40); uVar7 = uVar7 + 1) {
      iVar5 = (uVar7 >> 8) * 4;
      iVar8 = (uVar7 & 0xff) * 0x20;
      if (*(int *)(iVar8 + *(int *)(iVar5 + *(int *)(in_ECX + 0x3c))) != 0) {
        bVar11 = *(int *)(*(int *)(iVar5 + *(int *)(in_ECX + 0x3c)) + 0x1c + iVar8) != 0;
        iVar5 = *(int *)(iVar5 + *(int *)(in_ECX + 0x3c));
        if (bVar11) {
          uVar9 = *(undefined4 *)(iVar5 + 0x18 + iVar8);
          bVar1 = *(byte *)(iVar5 + iVar8 + 0x17);
          uVar12 = *(undefined4 *)(iVar5 + iVar8 + 0x14);
        }
        else {
          uVar9 = *(undefined4 *)(iVar5 + 0x18 + iVar8);
          bVar1 = *(byte *)(iVar5 + iVar8 + 0x17);
          uVar12 = *(undefined4 *)(iVar5 + iVar8 + 0x14);
        }
        iVar5 = iVar5 + iVar8;
        FUN_00a265d0(DAT_010da92c,*(undefined4 *)(iVar5 + 4),*(undefined4 *)(iVar5 + 8),
                     *(undefined1 *)(iVar5 + 0xc),*(undefined4 *)(iVar5 + 0x10),
                     *(undefined4 *)(iVar5 + 0x1c),bVar11,uVar12,(uint)bVar1 << 0x18 | 0xffffff,
                     uVar9);
      }
    }
    if (*(int *)(in_ECX + 0x3c) != 0) {
      iVar5 = *(int *)(in_ECX + 0x44);
      iVar8 = *(int *)(in_ECX + 0x40) + iVar5;
      for (; iVar5 != iVar8; iVar5 = iVar5 + 1) {
      }
      uVar7 = 0;
      in_ECX[0x40] = '\0';
      in_ECX[0x41] = '\0';
      in_ECX[0x42] = '\0';
      in_ECX[0x43] = '\0';
      in_ECX[0x44] = '\0';
      in_ECX[0x45] = '\0';
      in_ECX[0x46] = '\0';
      in_ECX[0x47] = '\0';
      if (*(int *)(in_ECX + 0x38) != 0) {
        do {
          _free(*(void **)(*(int *)(in_ECX + 0x3c) + uVar7 * 4));
          uVar7 = uVar7 + 1;
        } while (uVar7 < *(uint *)(in_ECX + 0x38));
      }
      _free(*(void **)(in_ECX + 0x3c));
      in_ECX[0x3c] = '\0';
      in_ECX[0x3d] = '\0';
      in_ECX[0x3e] = '\0';
      in_ECX[0x3f] = '\0';
      in_ECX[0x38] = '\0';
      in_ECX[0x39] = '\0';
      in_ECX[0x3a] = '\0';
      in_ECX[0x3b] = '\0';
    }
  }
  if ((((DAT_010c0774 < 1) || (*in_ECX == '\0')) || (*(int *)(in_ECX + 8) == 0)) ||
     ((*(int *)(in_ECX + 0xc) - *(int *)(in_ECX + 8)) / 0x14 == 0)) {
    bVar11 = false;
  }
  else {
    puVar10 = *(undefined1 **)(in_ECX + 8);
    bVar11 = true;
    if (puVar10 != *(undefined1 **)(in_ECX + 0xc)) {
      do {
        if (puVar10[8] == '\0') {
          iVar5 = *(int *)(in_ECX + 0x14);
          if (iVar5 == 0) {
            uVar4 = puVar10[3];
          }
          else {
            iVar6 = FUN_00b06f00();
            iVar2 = *(int *)(puVar10 + 0xc);
            iVar6 = iVar6 % (iVar5 * 2);
            iVar8 = *(int *)(puVar10 + 0x10);
            if (iVar5 <= iVar6) {
              iVar6 = iVar6 - iVar5;
              iVar8 = iVar2;
              iVar2 = *(int *)(puVar10 + 0x10);
            }
            FUN_00b099b0((float)iVar8,(float)iVar2,iVar6,iVar5);
            uVar4 = FUN_00c01544();
          }
          uVar3 = CONCAT21(CONCAT11(uVar4,puVar10[2]),puVar10[1]);
          uVar9 = CONCAT31(uVar3,*puVar10);
          uVar7 = (uVar3 & 0xff0000) << 8 | 0xffffff;
          FUN_00a23e90(param_1,*(int *)(puVar10 + 4) + param_2,param_3,param_4,in_ECX + 0xa8,2,1,
                       uVar9,uVar7,0);
          FUN_00a23e90(param_1,param_2 - *(int *)(puVar10 + 4),param_3,param_4,in_ECX + 0xa8,2,1,
                       uVar9,uVar7,0);
          FUN_00a23e90(param_1,param_2,*(int *)(puVar10 + 4) + param_3,param_4,in_ECX + 0xa8,2,1,
                       uVar9,uVar7,0);
          FUN_00a23e90(param_1,param_2,param_3 - *(int *)(puVar10 + 4),param_4,in_ECX + 0xa8,2,1,
                       uVar9,uVar7,0);
        }
        puVar10 = puVar10 + 0x14;
      } while (puVar10 != *(undefined1 **)(in_ECX + 0xc));
    }
  }
  FUN_00a23d60(param_1,param_2,param_3,param_4,in_ECX + 0xa8);
  if ((in_ECX[0x164] != '\0') &&
     (FUN_00a23e90(param_1,param_2,param_3,param_4,in_ECX + 0xa8,*(undefined4 *)(in_ECX + 0x168),
                   in_ECX[0x16c],*(undefined4 *)(in_ECX + 0x170),*(undefined4 *)(in_ECX + 0x174),0),
     in_ECX[0x178] != '\0')) {
    in_ECX[0x164] = '\0';
  }
  if ((bVar11) &&
     (puVar10 = *(undefined1 **)(in_ECX + 8), puVar10 != *(undefined1 **)(in_ECX + 0xc))) {
    do {
      if (puVar10[8] == '\x01') {
        iVar5 = *(int *)(in_ECX + 0x14);
        if (iVar5 == 0) {
          uVar4 = puVar10[3];
        }
        else {
          iVar6 = FUN_00b06f00();
          iVar2 = *(int *)(puVar10 + 0xc);
          iVar6 = iVar6 % (iVar5 * 2);
          iVar8 = *(int *)(puVar10 + 0x10);
          if (iVar5 <= iVar6) {
            iVar6 = iVar6 - iVar5;
            iVar8 = iVar2;
            iVar2 = *(int *)(puVar10 + 0x10);
          }
          FUN_00b099b0((float)iVar8,(float)iVar2,iVar6,iVar5);
          uVar4 = FUN_00c01544();
        }
        uVar3 = CONCAT21(CONCAT11(uVar4,puVar10[2]),puVar10[1]);
        uVar9 = CONCAT31(uVar3,*puVar10);
        uVar7 = (uVar3 & 0xff0000) << 8 | 0xffffff;
        FUN_00a23e90(param_1,*(int *)(puVar10 + 4) + param_2,param_3,param_4,in_ECX + 0xa8,2,1,uVar9
                     ,uVar7,0);
        FUN_00a23e90(param_1,param_2 - *(int *)(puVar10 + 4),param_3,param_4,in_ECX + 0xa8,2,1,uVar9
                     ,uVar7,0);
        FUN_00a23e90(param_1,param_2,*(int *)(puVar10 + 4) + param_3,param_4,in_ECX + 0xa8,2,1,uVar9
                     ,uVar7,0);
        FUN_00a23e90(param_1,param_2,param_3 - *(int *)(puVar10 + 4),param_4,in_ECX + 0xa8,2,1,uVar9
                     ,uVar7,0);
      }
      puVar10 = puVar10 + 0x14;
    } while (puVar10 != *(undefined1 **)(in_ECX + 0xc));
  }
  if (local_c != *(int **)(in_ECX + 0x180)) {
    do {
      if (local_c[3] != 0) {
        FUN_00a26990(param_1,param_2,param_3,param_4);
      }
      local_c = (int *)*local_c;
    } while (local_c != *(int **)(in_ECX + 0x180));
  }
  if ((*(int *)(in_ECX + 0x188) == 0) && (in_ECX[0x140] != '\0')) {
    FUN_00537890(*(undefined4 *)(in_ECX + 0x154),*(undefined4 *)(in_ECX + 0x158),
                 *(undefined4 *)(in_ECX + 0x15c),*(undefined4 *)(in_ECX + 0x160));
  }
  return;
}

