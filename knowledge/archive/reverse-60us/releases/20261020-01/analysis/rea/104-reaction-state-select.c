
int FUN_004af540(int *param_1,undefined4 *param_2,int *param_3)

{
  int *piVar1;
  char cVar2;
  undefined1 uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int *in_ECX;
  int iVar8;
  undefined4 local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  cVar2 = (**(code **)(*in_ECX + 0x2c))(0x211);
  if (cVar2 != '\0') {
    local_c = FUN_00c00d0b();
  }
  local_8 = -1;
  local_10 = (**(code **)(*param_3 + 0x19c))();
  iVar8 = *(int *)(local_10 + 0xec);
  if (iVar8 == 3) {
    piVar1 = (int *)in_ECX[0x8a];
    piVar4 = (int *)in_ECX[0x89];
    if (piVar4 != piVar1) {
      do {
        if (*piVar4 == 0x12) break;
        piVar4 = piVar4 + 1;
      } while (piVar4 != piVar1);
      if (piVar4 != piVar1) {
        return local_8;
      }
    }
    iVar8 = 1;
  }
  else if (iVar8 == 0) {
    return local_8;
  }
  iVar5 = FUN_00402060();
  if (iVar5 == 0) {
    iVar5 = FUN_00499fe0();
  }
  else {
    iVar5 = FUN_00402060();
  }
  local_14 = 100;
  iVar6 = (**(code **)(*in_ECX + 0x310))(&local_14,param_3);
  if ((iVar5 != 2) && ((iVar6 == 1 || (iVar6 == 2)))) {
    iVar5 = 1;
  }
  cVar2 = (**(code **)(*in_ECX + 0x3dc))();
  if (cVar2 != '\0') {
    uVar3 = 0;
    cVar2 = (**(code **)(*in_ECX + 0x2c))(0x211);
    if (cVar2 != '\0') {
      uVar3 = (**(code **)(*in_ECX + 0x4f0))();
    }
    iVar8 = *in_ECX;
    uVar7 = (**(code **)(iVar8 + 0x230))(uVar3);
    local_8 = (**(code **)(iVar8 + 0x3e4))(uVar7);
    if (local_8 != 5) {
      return local_8;
    }
    iVar8 = FUN_00402060();
    if ((iVar8 < 0x96) && (iVar8 = FUN_00402060(), iVar8 != 1)) {
      iVar8 = FUN_00402060();
      *param_1 = ((iVar8 < 400) - 1 & 3) + 2;
      return local_8;
    }
    iVar8 = (**(code **)(*param_3 + 0x31c))();
    *param_1 = 4 - (uint)(iVar8 != 0);
    return local_8;
  }
  if (((iVar5 != 0) &&
      ((((char)in_ECX[0x142] == '\0' || (cVar2 = FUN_004e8970(0xe), cVar2 == '\0')) ||
       (cVar2 = (**(code **)(*param_3 + 0x1b8))(), cVar2 == '\0')))) &&
     ((((char)in_ECX[0x142] == '\0' || (cVar2 = FUN_004e8970(1), cVar2 == '\0')) ||
      (cVar2 = (**(code **)(*param_3 + 0x1b8))(), cVar2 == '\0')))) {
    if (local_c == 0) {
      return local_8;
    }
    if (*(char *)(*(int *)(local_c + 0x1aa4) + 0x3c) == '\0') {
      return local_8;
    }
    cVar2 = (**(code **)(*param_3 + 0x1b8))();
    if (cVar2 == '\0') {
      return local_8;
    }
  }
  cVar2 = (**(code **)(*in_ECX + 0x410))(1);
  if (cVar2 != '\0') {
    return -1;
  }
  cVar2 = (**(code **)(*in_ECX + 0x410))(7);
  if (cVar2 != '\0') {
    return -1;
  }
  if (iVar8 == 1) {
    iVar8 = (**(code **)(*in_ECX + 0x204))();
    if (((0 < iVar8) || (iVar8 = (**(code **)(*in_ECX + 0x9c))(), iVar8 < 1)) &&
       (iVar8 = FUN_00402060(), iVar8 != 4)) goto LAB_004af801;
  }
  else if (iVar8 != 2) {
    return local_8;
  }
  local_8 = 4;
  iVar8 = (**(code **)(*in_ECX + 0x378))();
  if ((iVar8 != 0) || (iVar8 = (**(code **)(*in_ECX + 0x3a0))(), iVar8 != 0)) {
    iVar8 = FUN_00402060();
    if (iVar8 != 4) {
      return local_8;
    }
    iVar8 = FUN_00402060();
    if (iVar8 < 1) {
      return local_8;
    }
    iVar8 = FUN_00402060();
    if (iVar8 != 0) {
      return local_8;
    }
    *param_2 = 1;
    return local_8;
  }
LAB_004af801:
  local_8 = 3;
  iVar8 = (**(code **)(*in_ECX + 0x374))(0);
  if ((iVar8 == 0) && (iVar8 = (**(code **)(*in_ECX + 0x374))(1), iVar8 == 0)) {
    return -1;
  }
  return local_8;
}

