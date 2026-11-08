
undefined4 FUN_00485950(int *param_1)

{
  uint uVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int in_ECX;
  uint uVar8;
  bool bVar9;
  int local_c;
  int local_8;
  
  piVar2 = param_1;
  cVar3 = (**(code **)(*param_1 + 0x2c))(0x11);
  if (((cVar3 == '\0') && (cVar3 = (**(code **)(*param_1 + 0x2c))(0x81), cVar3 == '\0')) &&
     ((cVar3 = (**(code **)(*param_1 + 0x2c))(0x21), cVar3 == '\0' ||
      (iVar4 = (**(code **)(*param_1 + 0x33c))(), *(char *)(iVar4 + 0x1d) == '\0')))) {
LAB_00485a29:
    iVar4 = (**(code **)(*param_1 + 0x1fc))();
    if ((iVar4 != 0) || (iVar4 = (**(code **)(*param_1 + 0x200))(), iVar4 != 0)) {
      if ((*(int *)(in_ECX + 0x174) != 0) &&
         (iVar4 = *(int *)(in_ECX + 0x178) - *(int *)(in_ECX + 0x174) >> 4, 0 < iVar4)) {
        local_c = 0;
        local_8 = 0;
        do {
          uVar7 = (**(code **)(*param_1 + 0x98))(*(int *)(in_ECX + 0x174) + local_8);
          uVar7 = (**(code **)(*param_1 + 0x94))(uVar7);
          cVar3 = FUN_008adab0(uVar7);
          if (cVar3 != '\0') {
            return 1;
          }
          local_c = local_c + 1;
          local_8 = local_8 + 0x10;
        } while (local_c < iVar4);
        return 0;
      }
      iVar5 = (**(code **)(*param_1 + 0x214))();
      iVar4 = (**(code **)(*param_1 + 0x20c))();
      uVar8 = (int)(iVar4 + (iVar4 >> 0x1f & 0xfU)) >> 4;
      iVar4 = (**(code **)(*param_1 + 0x218))();
      iVar6 = (**(code **)(*param_1 + 0x210))();
      param_1 = (int *)(iVar4 / 0xc);
      local_c = (int)(iVar6 + (iVar6 >> 0x1f & 0xfU)) >> 4;
      uVar8 = ((int)uVar8 < 0) - 1 & uVar8;
      iVar4 = 0;
      if (*(int *)(in_ECX + 0x218) != 0) {
        iVar4 = (*(int *)(in_ECX + 0x21c) - *(int *)(in_ECX + 0x218)) / 0x24;
      }
      if (iVar4 * 0xe + -1 < local_c) {
        local_c = FUN_00486a70();
        local_c = local_c + -1;
      }
      iVar4 = FUN_00486c30();
      if (iVar4 + -1 < (int)param_1) {
        iVar4 = FUN_00486c30();
        param_1 = (int *)(iVar4 + -1);
      }
      for (; uVar1 = (iVar5 / 0xc < 0) - 1 & iVar5 / 0xc, (int)uVar8 <= local_c; uVar8 = uVar8 + 1)
      {
        for (; (int)uVar1 <= (int)param_1; uVar1 = uVar1 + 1) {
          iVar4 = FUN_00485580(uVar8,uVar1);
          switch(iVar4 + -1) {
          case 0:
            iVar4 = (**(code **)(*piVar2 + 0x208))();
            if (iVar4 < 1) {
              return 0;
            }
            break;
          case 1:
            goto LAB_004859b2;
          case 2:
            iVar4 = (**(code **)(*piVar2 + 0x1c4))();
            bVar9 = iVar4 == 0;
            goto code_r0x00485c08;
          case 3:
            iVar4 = (**(code **)(*piVar2 + 0x1c4))();
            bVar9 = iVar4 == 1;
code_r0x00485c08:
            if (!bVar9) {
              return 0;
            }
          }
        }
      }
    }
    return 1;
  }
  iVar4 = (**(code **)(*param_1 + 0x94))();
  if (-1 < iVar4) {
    if (*(int *)(in_ECX + 0x218) == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = (*(int *)(in_ECX + 0x21c) - *(int *)(in_ECX + 0x218)) / 0x24;
    }
    iVar5 = (**(code **)(*param_1 + 0x94))();
    if ((iVar5 < iVar4 * 0xe0) && (iVar4 = (**(code **)(*param_1 + 0x98))(), -1 < iVar4)) {
      iVar4 = FUN_004869d0();
      iVar5 = FUN_00486ca0();
      iVar6 = (**(code **)(*param_1 + 0x98))();
      if (iVar6 < iVar4 * 0x78 + iVar5) goto LAB_00485a29;
    }
  }
LAB_004859b2:
  return 0;
}

