
void FUN_004b4a80(int param_1,int *param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  char cVar4;
  undefined1 uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 uVar10;
  int *piVar11;
  int *in_ECX;
  int iVar12;
  int *piVar13;
  uint uVar14;
  uint local_28;
  int local_24;
  int local_18;
  uint local_14;
  
  cVar4 = (**(code **)(*in_ECX + 0x2c))(0x111);
  uVar14 = (uint)param_2;
  if ((cVar4 != '\0') && (cVar4 = FUN_0045a5c0(param_2), cVar4 != '\0')) {
    iVar6 = (**(code **)(*in_ECX + 0x364))();
    uVar7 = FUN_004ae890(param_1);
    local_28 = local_28 & 0xffffff00;
    if (uVar7 != 0xffffffff) {
      uVar8 = (uVar14 == 0x13) - 1 & uVar14;
      if (uVar14 == 0x13) {
        local_18 = 10;
      }
      else {
        local_18 = uVar14 + 1;
      }
      for (; (int)uVar8 < local_18; uVar8 = uVar8 + 1) {
        piVar1 = (int *)in_ECX[uVar8 + 0x53b];
        if (piVar1 != (int *)0x0) {
          local_14 = 0;
          iVar9 = (**(code **)(*piVar1 + 0x138))();
          iVar12 = *(int *)(iVar9 + 8) - *(int *)(iVar9 + 4);
          iVar9 = iVar12 >> 0x1f;
          if (iVar12 / 0x8c + iVar9 != iVar9) {
            do {
              uVar14 = local_14;
              (**(code **)(*piVar1 + 0x138))(local_14);
              iVar9 = FUN_00466590(uVar14);
              if ((*(int *)(iVar9 + 0x3c) == 0) ||
                 ((uint)(*(int *)(iVar9 + 0x40) - *(int *)(iVar9 + 0x3c) >> 2) <= uVar7)) {
                if (*(int *)(iVar9 + 0x3c) == 0) {
                  iVar9 = 0;
                }
                else {
                  iVar9 = *(int *)(iVar9 + 0x40) - *(int *)(iVar9 + 0x3c) >> 2;
                }
                (*(code *)PTR_FUN_00ff2ebc)(u_ERROR___customAnimationIndex__d__00cd1128,uVar7,iVar9)
                ;
              }
              else {
                iVar12 = uVar7 * 4;
                uVar2 = *(undefined4 *)(*(int *)(iVar9 + 0x3c) + iVar12);
                cVar4 = FUN_004af8d0(uVar2);
                if (cVar4 != '\0') {
                  param_2 = (int *)((uint)param_2 & 0xffffff);
                  uVar10 = FUN_00a24dc0(uVar2,(int)&param_2 + 3);
                  if (param_2._3_1_ != '\0') {
                    FUN_00a277c0(uVar2);
                    cVar4 = FUN_004b2650(uVar7);
                    if (cVar4 == '\x01') {
                      iVar3 = *(int *)(*(int *)(iVar6 + 0x38) + iVar12);
                      iVar12 = *(int *)(*(int *)(iVar9 + 0x3c) + iVar12);
                      if ((iVar3 != 0) && (iVar12 != 0)) {
                        FUN_00a29d70(uVar10,iVar12);
                        FUN_004ccdb0(iVar3,iVar12);
                      }
                      local_28 = CONCAT31(local_28._1_3_,1);
                    }
                    if ((((uVar8 == 9) &&
                         (cVar4 = (**(code **)(*in_ECX + 0x2c))(0x111), cVar4 != '\0')) &&
                        (cVar4 = FUN_0043a670(), cVar4 == '\0')) &&
                       (cVar4 = (**(code **)(*in_ECX + 0x524))(uVar10), cVar4 == '\0')) {
                      (**(code **)(*piVar1 + 0xf4))();
                      uVar5 = FUN_00402060();
                      FUN_004b8da0(uVar5,iVar9 + 4);
                    }
                  }
                }
              }
              local_14 = local_14 + 1;
              iVar9 = (**(code **)(*piVar1 + 0x138))();
            } while (local_14 < (uint)((*(int *)(iVar9 + 8) - *(int *)(iVar9 + 4)) / 0x8c));
          }
        }
      }
    }
    param_2 = in_ECX + 0x53b;
    local_24 = 10;
    do {
      piVar1 = (int *)*param_2;
      if (((piVar1 != (int *)0x0) && ((char)piVar1[0x1e3] == '\0')) &&
         (iVar6 = (**(code **)(*piVar1 + 0x138))(), iVar6 != 0)) {
        param_1 = 0;
        piVar13 = in_ECX + 0x53b;
        do {
          iVar6 = *piVar13;
          if (((iVar6 != 0) && (*(char *)(iVar6 + 0x78d) != '\0')) &&
             ((iVar6 = *(int *)(iVar6 + 0x790), piVar11 = (int *)(**(code **)(*piVar1 + 0xe0))(),
              iVar6 == *piVar11 && (*(int *)(*piVar13 + 0x798) == 0)))) {
            FUN_004b4960(piVar1,uVar7,local_28);
            break;
          }
          param_1 = param_1 + 1;
          piVar13 = piVar13 + 1;
        } while (param_1 < 0x13);
      }
      param_2 = param_2 + 1;
      local_24 = local_24 + -1;
    } while (local_24 != 0);
  }
  return;
}

