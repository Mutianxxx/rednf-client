
void FUN_00a265d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 int param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10)

{
  int in_ECX;
  int iVar1;
  int *piVar2;
  
  FUN_00a24460();
  piVar2 = (int *)**(int **)(in_ECX + 0x180);
  if (piVar2 != *(int **)(in_ECX + 0x180)) {
    do {
      if (-1 < piVar2[2]) break;
      if (piVar2[3] != 0) {
        FUN_00a265d0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     param_10);
      }
      piVar2 = (int *)*piVar2;
    } while (piVar2 != (int *)*(int *)(in_ECX + 0x180));
  }
  if (*(int *)(in_ECX + 0x98) == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = (*(int *)(in_ECX + 0x9c) - *(int *)(in_ECX + 0x98)) / 0x7c;
  }
  if (param_5 < iVar1) {
    iVar1 = param_5 * 0x7c + *(int *)(in_ECX + 0x98);
  }
  else {
    iVar1 = 0;
  }
  FUN_00a23e90(param_1,param_2,param_3,param_4,iVar1,param_6,param_7,param_8,param_9,param_10);
  if (piVar2 != *(int **)(in_ECX + 0x180)) {
    do {
      if (piVar2[3] != 0) {
        FUN_00a265d0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     param_10);
      }
      piVar2 = (int *)*piVar2;
    } while (piVar2 != *(int **)(in_ECX + 0x180));
  }
  if ((*(int *)(in_ECX + 0x188) == 0) && (*(char *)(in_ECX + 0x140) != '\0')) {
    FUN_00537890(*(undefined4 *)(in_ECX + 0x154),*(undefined4 *)(in_ECX + 0x158),
                 *(undefined4 *)(in_ECX + 0x15c),*(undefined4 *)(in_ECX + 0x160));
  }
  return;
}

