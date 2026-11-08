
void FUN_00a49220(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int in_ECX;
  undefined4 uVar6;
  undefined4 *unaff_FS_OFFSET;
  undefined *puVar7;
  undefined1 local_2c [4];
  void *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  iVar3 = param_2;
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c8f59a;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  local_18 = 1;
  local_14 = in_ECX;
  if (*(int *)(param_2 + 0x2c) - *(int *)(param_2 + 0x28) >> 2 == 0) {
    iVar5 = -1;
  }
  else {
    piVar2 = (int *)FUN_00a3e780(0);
    iVar5 = *piVar2;
  }
  uVar6 = 0xffffffff;
  if (iVar5 == 6) {
    uVar6 = FUN_00a2d1c0(iVar3,&local_18);
  }
  local_1c = FUN_00a2d1c0(iVar3,&local_18);
  iVar3 = param_3;
  local_28 = (void *)0x0;
  local_24 = 0;
  local_20 = 0;
  local_8 = 0;
  if (iVar5 == 0) {
    if (*(int *)(local_14 + 0x7c) != 0) {
      FUN_0048e4f0(local_14 + 0x7c);
    }
  }
  else if (iVar5 == 1) {
    piVar2 = *(int **)(param_3 + 4);
    if (piVar2 != *(int **)(param_3 + 8)) {
      do {
        piVar4 = (int *)*piVar2;
        if (piVar4 != (int *)0x0) {
          cVar1 = (**(code **)(*piVar4 + 0x2c))(0x211);
          if (cVar1 == '\0') {
            cVar1 = (**(code **)(*piVar4 + 0x34))();
            if (cVar1 == '\0') {
              puVar7 = &DAT_00e493e0;
LAB_00a493f3:
              (*(code *)PTR_FUN_00ff2ebc)(puVar7);
            }
            else {
              iVar3 = FUN_00c00d0b(piVar4,0,&PTR_PTR_00f40910,&PTR_PTR_00f42908,0);
              if ((iVar3 == 0) || (iVar3 = FUN_004be070(), iVar3 == 0)) goto LAB_00a493e7;
              param_2 = FUN_004be070();
              FUN_0048e4f0(&param_2);
            }
          }
          else {
            cVar1 = (**(code **)(*piVar4 + 0x38))();
            if (cVar1 == '\0') {
              piVar4 = (int *)FUN_00c00d0b(piVar4,0,&PTR_PTR_00f40910,&PTR_PTR_00f42928,0);
              if ((piVar4 == (int *)0x0) ||
                 (iVar3 = (**(code **)(*piVar4 + 0x5b0))(), *(int *)(iVar3 + 0x14) == 0))
              goto LAB_00a493e7;
              iVar3 = (**(code **)(*piVar4 + 0x5b0))();
              param_2 = *(int *)(iVar3 + 0x14);
              FUN_0048e4f0(&param_2);
            }
            else {
              iVar3 = FUN_00c00d0b(piVar4,0,&PTR_PTR_00f40910,&PTR_PTR_00f59df4,0);
              if ((iVar3 == 0) || (iVar3 = FUN_00748f90(), iVar3 == 0)) {
LAB_00a493e7:
                puVar7 = &DAT_00e49444;
                goto LAB_00a493f3;
              }
              param_2 = FUN_00748f90();
              FUN_0048e4f0(&param_2);
            }
          }
        }
        piVar2 = piVar2 + 1;
      } while (piVar2 != *(int **)(param_3 + 8));
    }
  }
  else if (iVar5 == 3) {
    if (*(int *)(local_14 + 0x80) == 0) {
      (*(code *)PTR_FUN_00ff2ebc)(&DAT_00e49390);
    }
    else {
      FUN_0048e4f0(local_14 + 0x80);
    }
  }
  else if (iVar5 == 4) {
    if (*(int *)(local_14 + 0x84) == 0) {
      (*(code *)PTR_FUN_00ff2ebc)(&DAT_00e49338);
    }
    else {
      FUN_0048e4f0(local_14 + 0x84);
    }
  }
  else if (iVar5 == 2) {
    piVar2 = *(int **)(param_3 + 4);
    if (piVar2 != *(int **)(param_3 + 8)) {
      do {
        piVar4 = (int *)*piVar2;
        if (piVar4 != (int *)0x0) {
          cVar1 = (**(code **)(*piVar4 + 0x2c))(0x211);
          if (cVar1 == '\0') {
            cVar1 = (**(code **)(*piVar4 + 0x34))();
            if (cVar1 == '\0') {
              cVar1 = (**(code **)(*piVar4 + 0x2c))(0x21);
              if (cVar1 == '\0') {
                (*(code *)PTR_FUN_00ff2ebc)(&DAT_00e492e0);
              }
              else {
                piVar4 = (int *)FUN_00c00d0b(piVar4,0,&PTR_PTR_00f40910,&PTR_PTR_00f428a0,0);
                if ((piVar4 != (int *)0x0) && (iVar5 = (**(code **)(*piVar4 + 0x18c))(), iVar5 != 0)
                   ) {
                  param_3 = (**(code **)(*piVar4 + 0x18c))();
                  FUN_0048e4f0(&param_3);
                }
              }
            }
            else {
              piVar4 = (int *)FUN_00c00d0b(piVar4,0,&PTR_PTR_00f40910,&PTR_PTR_00f42908,0);
              if ((piVar4 != (int *)0x0) && (iVar5 = (**(code **)(*piVar4 + 0x358))(), iVar5 != 0))
              {
                param_3 = (**(code **)(*piVar4 + 0x358))();
                FUN_0048e4f0(&param_3);
              }
            }
          }
          else {
            piVar4 = (int *)FUN_00c00d0b(piVar4,0,&PTR_PTR_00f40910,&PTR_PTR_00f42928,0);
            if ((piVar4 != (int *)0x0) && (iVar5 = (**(code **)(*piVar4 + 0x358))(), iVar5 != 0)) {
              param_3 = (**(code **)(*piVar4 + 0x358))();
              FUN_0048e4f0(&param_3);
            }
          }
        }
        piVar2 = piVar2 + 1;
      } while (piVar2 != *(int **)(iVar3 + 8));
    }
  }
  else if (iVar5 == 6) {
    piVar2 = *(int **)(param_3 + 4);
    if (piVar2 != *(int **)(param_3 + 8)) {
      do {
        if ((*piVar2 != 0) && (param_3 = FUN_0049b1c0(uVar6), param_3 != 0)) {
          FUN_0048e4f0(&param_3);
        }
        piVar2 = piVar2 + 1;
      } while (piVar2 != *(int **)(iVar3 + 8));
    }
  }
  else if (iVar5 == 5) {
    FUN_00a48c80(param_1,local_1c,param_3,param_4);
    FUN_00644d50();
    *unaff_FS_OFFSET = local_10;
    return;
  }
  FUN_00a48c80(param_1,local_1c,local_2c,param_4);
  if (local_28 != (void *)0x0) {
    _free(local_28);
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

