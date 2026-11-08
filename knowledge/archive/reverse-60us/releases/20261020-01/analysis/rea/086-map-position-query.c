
undefined4 FUN_0050b240(int *param_1)

{
  char cVar1;
  int iVar2;
  int in_ECX;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  
  if (*(int *)(in_ECX + 0x10) == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(in_ECX + 0x14) - *(int *)(in_ECX + 0x10) >> 2;
  }
  iVar3 = 0;
  if (0 < iVar2) {
    piVar4 = *(int **)(in_ECX + 0x10);
    do {
      if ((int *)*piVar4 == param_1) {
        iVar2 = (**(code **)(*param_1 + 0x1fc))();
        if ((iVar2 == 0) && (iVar2 = (**(code **)(*param_1 + 0x200))(), iVar2 == 0)) {
          return 0;
        }
        puVar5 = *(undefined4 **)(in_ECX + 0x90);
        if (puVar5 == *(undefined4 **)(in_ECX + 0x94)) {
          return 0;
        }
        while (((int *)*puVar5 == param_1 ||
               (cVar1 = (**(code **)(*param_1 + 0x244))((int *)*puVar5), cVar1 == '\0'))) {
          puVar5 = puVar5 + 1;
          if (puVar5 == *(undefined4 **)(in_ECX + 0x94)) {
            return 0;
          }
        }
        return *puVar5;
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < iVar2);
  }
  return 0;
}

