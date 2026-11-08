
int FUN_0049d960(void)

{
  int iVar1;
  int *piVar2;
  char cVar3;
  DWORD DVar4;
  int iVar5;
  undefined4 uVar6;
  int *in_ECX;
  uint uVar7;
  int iVar8;
  
  DVar4 = GetTickCount();
  in_ECX[0x171] = DVar4;
  if (in_ECX[0x157] == -1) {
    return -1;
  }
  if (((((in_ECX[0x157] != 0) ||
        (iVar5 = (**(code **)(*in_ECX + 0xf4))(), *(char *)(iVar5 + 0x13a) == '\0')) ||
       ((char)in_ECX[0x169] != '\0')) &&
      (((in_ECX[0x157] != 1 || (iVar5 = (**(code **)(*in_ECX + 0x9c))(), iVar5 != 0)) ||
       ((char)in_ECX[0x169] != '\0')))) &&
     ((((in_ECX[0x157] != 2 || (in_ECX[0x171] - in_ECX[0x170] <= in_ECX[0x16f])) ||
       ((char)in_ECX[0x169] != '\0')) &&
      (((in_ECX[0x157] != 3 || (iVar5 = (**(code **)(*in_ECX + 0x9c))(), iVar5 != 0)) ||
       ((char)in_ECX[0x169] != '\0')))))) goto LAB_0049db2d;
  cVar3 = FUN_0049c090();
  if ((cVar3 != '\0') && ((char)in_ECX[0x169] == '\0')) {
    if (in_ECX[0x158] == 1) {
      for (uVar7 = 0;
          (iVar5 = in_ECX[0x15a], iVar5 != 0 && (uVar7 < (uint)(in_ECX[0x15b] - iVar5 >> 2)));
          uVar7 = uVar7 + 1) {
        uVar6 = (**(code **)(*in_ECX + 0xc0))(0,0,0,0,0);
        uVar6 = (**(code **)(*in_ECX + 0x9c))(uVar6);
        uVar6 = (**(code **)(*in_ECX + 0x98))(uVar6);
        uVar6 = (**(code **)(*in_ECX + 0x94))(uVar6);
        FUN_004e9ea0(in_ECX[0x14c],*(undefined4 *)(iVar5 + uVar7 * 4),0,uVar6);
      }
    }
    else if (in_ECX[0x158] != 0) goto LAB_0049dac1;
    *(undefined1 *)(in_ECX + 0x169) = 1;
  }
LAB_0049dac1:
  if (in_ECX[0x166] == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = in_ECX[0x167] - in_ECX[0x166] >> 2;
  }
  iVar8 = 0;
  if (0 < iVar5) {
    do {
      if ((-1 < *(int *)(in_ECX[0x166] + iVar8 * 4)) &&
         (iVar1 = *(int *)(in_ECX[0x166] + iVar8 * 4), iVar1 != -1)) {
        (**(code **)(*in_ECX + 0x110))(iVar1);
      }
      iVar8 = iVar8 + 1;
    } while (iVar8 < iVar5);
  }
  if (in_ECX[0x157] != 3) {
    (**(code **)(*in_ECX + 0x164))(0);
  }
LAB_0049db2d:
  if ((((*(int *)in_ECX[0x16b] == 0) && (piVar2 = (int *)in_ECX[0x166], piVar2 != (int *)0x0)) &&
      (in_ECX[0x167] - (int)piVar2 >> 2 != 0)) && (*piVar2 != -2)) {
    if (*piVar2 == -1) {
      iVar5 = *in_ECX;
      uVar6 = FUN_00a530f0(0xffffffff,0,0);
      (**(code **)(iVar5 + 0x10c))(uVar6);
    }
    else {
      uVar6 = FUN_00a530f0();
      (**(code **)(*in_ECX + 0x10c))(uVar6,*piVar2,0,0);
    }
    *(undefined4 *)in_ECX[0x16b] = 1;
  }
  iVar5 = in_ECX[0x16b] + 4;
  if (((*(int *)(in_ECX[0x16b] + 4) == 0) && (iVar8 = in_ECX[0x166], iVar8 != 0)) &&
     ((iVar5 = 0, in_ECX[0x167] - iVar8 >> 2 != 0 && (iVar5 = iVar8 + 4, *(int *)(iVar8 + 4) != -2))
     )) {
    iVar5 = (**(code **)(*in_ECX + 0xf4))();
    iVar5 = *(int *)(iVar5 + 0x124);
    if (in_ECX[0x16e] < iVar5) {
      iVar5 = in_ECX[0x166];
      if (*(int *)(iVar5 + 4) != -1) {
        uVar6 = FUN_00a530f0();
        iVar5 = (**(code **)(*in_ECX + 0x10c))(uVar6,*(undefined4 *)(iVar5 + 4),0,0);
        *(undefined4 *)(in_ECX[0x16b] + 4) = 1;
        return iVar5;
      }
      iVar5 = *in_ECX;
      uVar6 = FUN_00a530f0(0xffffffff,0,0);
      iVar5 = (**(code **)(iVar5 + 0x10c))(uVar6);
      *(undefined4 *)(in_ECX[0x16b] + 4) = 1;
    }
  }
  return iVar5;
}

