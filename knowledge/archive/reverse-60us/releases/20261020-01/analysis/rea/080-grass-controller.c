
void FUN_005f3500(void)

{
  char cVar1;
  int iVar2;
  int *in_ECX;
  uint uVar3;
  int *piVar4;
  undefined4 *unaff_FS_OFFSET;
  undefined1 local_44 [48];
  int local_14;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00c6750a;
  local_10 = *unaff_FS_OFFSET;
  *unaff_FS_OFFSET = &local_10;
  FUN_0049dc70();
  if ((char)in_ECX[0x220] != '\0') {
    uVar3 = 0;
    if (in_ECX[0x221] != 0) {
      iVar2 = FUN_005f31a0(in_ECX[0x221]);
      if (iVar2 == 4) {
        in_ECX[0x221] = 0;
      }
      FUN_005f3300(iVar2);
    }
    if (in_ECX[0x221] == 0) {
      iVar2 = *(int *)(in_ECX[0x40] + 0x90);
      if (iVar2 == 0) {
        local_14 = 0;
      }
      else {
        local_14 = *(int *)(in_ECX[0x40] + 0x94) - iVar2 >> 2;
      }
      if (0 < local_14) {
        do {
          iVar2 = *(int *)(in_ECX[0x40] + 0x90);
          if ((iVar2 == 0) || ((uint)(*(int *)(in_ECX[0x40] + 0x94) - iVar2 >> 2) <= uVar3)) {
            piVar4 = (int *)0x0;
          }
          else {
            piVar4 = *(int **)(iVar2 + uVar3 * 4);
          }
          cVar1 = (**(code **)(*piVar4 + 0x2c))(0x11);
          if ((cVar1 != '\0') && (iVar2 = FUN_005f31a0(piVar4), iVar2 != 4)) {
            in_ECX[0x221] = (int)piVar4;
            FUN_005f3300(iVar2);
            break;
          }
          uVar3 = uVar3 + 1;
        } while ((int)uVar3 < local_14);
      }
    }
  }
  if ((char)in_ECX[0x21c] != '\0') {
    (**(code **)(*in_ECX + 0x2d8))(1);
    iVar2 = *(int *)(in_ECX[0x40] + 0x90);
    uVar3 = 0;
    if (iVar2 == 0) {
      local_14 = 0;
    }
    else {
      local_14 = *(int *)(in_ECX[0x40] + 0x94) - iVar2 >> 2;
    }
    if (0 < local_14) {
      do {
        iVar2 = *(int *)(in_ECX[0x40] + 0x90);
        if ((iVar2 == 0) || ((uint)(*(int *)(in_ECX[0x40] + 0x94) - iVar2 >> 2) <= uVar3)) {
          piVar4 = (int *)0x0;
        }
        else {
          piVar4 = *(int **)(iVar2 + uVar3 * 4);
        }
        if ((((char)in_ECX[0x223] == '\0') ||
            (iVar2 = (**(code **)(*piVar4 + 0x19c))(), *(char *)(iVar2 + 0x17c) != '\0')) &&
           (cVar1 = (**(code **)(*piVar4 + 0x1a8))(), cVar1 == '\0')) {
          FUN_004672b0();
          local_8 = 0;
          cVar1 = (**(code **)(*piVar4 + 0x240))();
          if (cVar1 != '\0') {
            (**(code **)(*piVar4 + 0x1a4))();
            (**(code **)(*in_ECX + 0x260))(piVar4,local_44,0);
          }
          local_8 = 0xffffffff;
          FUN_00404300();
        }
        uVar3 = uVar3 + 1;
      } while ((int)uVar3 < local_14);
    }
    (**(code **)(*in_ECX + 0x2d8))(0);
  }
  *unaff_FS_OFFSET = local_10;
  return;
}

