
int FUN_0054fc40(int *param_1,int param_2,int param_3,int param_4,uint param_5)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint *puVar6;
  int *piVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  int local_14;
  uint local_c;
  
  if (param_1 != (int *)0x0) {
    local_14 = 0;
    do {
      piVar2 = (int *)(**(code **)(*param_1 + 0x428))(local_14);
      if (piVar2 != (int *)0x0) {
        iVar3 = (**(code **)(*piVar2 + 0xe4))();
        iVar4 = 0;
        for (local_c = 0;
            (*(int *)(iVar3 + 0x2a0) != 0 &&
            (local_c < (uint)((*(int *)(iVar3 + 0x2a4) - *(int *)(iVar3 + 0x2a0)) / 0x28)));
            local_c = local_c + 1) {
          iVar5 = iVar4 + *(int *)(iVar3 + 0x2a0);
          if (*(int *)(iVar5 + 0x20) == param_4) {
            iVar10 = iVar5 + 4;
            if ((*(uint *)(iVar5 + 4) ^ DAT_012101dc) - iVar10 != *(int *)(iVar5 + 8)) {
              FUN_00b170b0(iVar10,0x3f);
            }
            iVar5 = *(int *)(iVar5 + 8) * 4;
            puVar6 = (uint *)(*(int *)(DAT_012101d8 + 0x44) + iVar5);
            uVar8 = (uint)puVar6 ^ DAT_012101dc ^ *puVar6;
            puVar6 = (uint *)(iVar5 + *(int *)(DAT_012101d8 + 0x48));
            if (uVar8 != ((uint)puVar6 ^ DAT_012101dc ^ *puVar6)) {
              FUN_00b170b0(iVar10,0x40);
            }
            if ((uVar8 == param_5) &&
               ((((iVar5 = *(int *)(*(int *)(iVar3 + 0x2a0) + iVar4 + 0x24), iVar5 == 0 ||
                  (iVar5 != 2)) || (cVar1 = FUN_0043abf0(0xffffffff), cVar1 != '\0')) &&
                ((piVar9 = (int *)(iVar4 + *(int *)(iVar3 + 0x2a0)), piVar9[3] == param_3 &&
                 ((*piVar9 == 6 ||
                  (piVar7 = (int *)(**(code **)(*param_1 + 0x5b0))(), *piVar9 == *piVar7)))))))) {
              iVar5 = FUN_00402060();
              if (iVar5 == 0) {
                iVar5 = FUN_00402060();
                param_2 = param_2 + iVar5;
              }
              else {
                FUN_00402060();
                param_2 = FUN_00c01544();
              }
            }
          }
          iVar4 = iVar4 + 0x28;
        }
        iVar3 = (**(code **)(*piVar2 + 0x11c))();
        if (iVar3 != 0) {
          iVar4 = 0;
          local_c = 0;
          while ((*(int *)(iVar3 + 0x2a0) != 0 &&
                 (local_c < (uint)((*(int *)(iVar3 + 0x2a4) - *(int *)(iVar3 + 0x2a0)) / 0x28)))) {
            cVar1 = (**(code **)(*piVar2 + 300))();
            if (((cVar1 == '\0') ||
                ((((cVar1 = (**(code **)(*piVar2 + 0x118))(), cVar1 == '\0' ||
                   (*(int *)(*(int *)(iVar3 + 0x2a0) + 0x20 + iVar4) != param_4)) ||
                  (uVar8 = FUN_00402060(), uVar8 != param_5)) ||
                 (piVar9 = (int *)(iVar4 + *(int *)(iVar3 + 0x2a0)),
                 *(int *)(iVar4 + 0xc + *(int *)(iVar3 + 0x2a0)) != param_3)))) ||
               ((*piVar9 != 6 &&
                (piVar7 = (int *)(**(code **)(*param_1 + 0x5b0))(), *piVar9 != *piVar7)))) {
LAB_0054ff2b:
              local_c = local_c + 1;
              iVar4 = iVar4 + 0x28;
            }
            else {
              iVar5 = FUN_00402060();
              if (iVar5 == 0) {
                iVar5 = FUN_00402060();
                param_2 = param_2 + iVar5;
                goto LAB_0054ff2b;
              }
              FUN_00402060();
              param_2 = FUN_00c01544();
              local_c = local_c + 1;
              iVar4 = iVar4 + 0x28;
            }
          }
        }
      }
      local_14 = local_14 + 1;
    } while (local_14 < 0x17);
  }
  return param_2;
}

