
void FUN_00a26220(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10)

{
  bool bVar1;
  int iVar2;
  int in_ECX;
  int *piVar3;
  
  FUN_00a24460();
  piVar3 = (int *)**(int **)(in_ECX + 0x180);
  bVar1 = true;
  if (piVar3 != *(int **)(in_ECX + 0x180)) {
    do {
      if (-1 < piVar3[2]) break;
      iVar2 = piVar3[3];
      if (iVar2 != 0) {
        if (((((char)param_10 == '\0') || (*(int *)(iVar2 + 0x98) == 0)) ||
            ((*(int *)(iVar2 + 0x9c) - *(int *)(iVar2 + 0x98)) / 0x7c == 0)) ||
           (iVar2 = FUN_00a25c90(0), *(int *)(iVar2 + 0x28) != 2)) {
          if (bVar1) {
            FUN_00a26220(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         param_10);
          }
        }
        else {
          bVar1 = false;
        }
      }
      piVar3 = (int *)*piVar3;
    } while (piVar3 != (int *)*(int *)(in_ECX + 0x180));
  }
  FUN_00a23e90(param_1,param_2,param_3,param_4,in_ECX + 0xa8,param_5,param_6,param_7,param_8,param_9
              );
  if (piVar3 != *(int **)(in_ECX + 0x180)) {
    do {
      iVar2 = piVar3[3];
      if (iVar2 != 0) {
        if ((((char)param_10 != '\0') && (*(int *)(iVar2 + 0x98) != 0)) &&
           ((*(int *)(iVar2 + 0x9c) - *(int *)(iVar2 + 0x98)) / 0x7c != 0)) {
          if ((*(int *)(iVar2 + 0x98) == 0) ||
             ((*(int *)(iVar2 + 0x9c) - *(int *)(iVar2 + 0x98)) / 0x7c < 1)) {
            iVar2 = 0;
          }
          else {
            iVar2 = *(int *)(iVar2 + 0x98);
          }
          if (*(int *)(iVar2 + 0x28) == 2) goto LAB_00a263c2;
        }
        FUN_00a26220(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     param_10);
      }
LAB_00a263c2:
      piVar3 = (int *)*piVar3;
    } while (piVar3 != *(int **)(in_ECX + 0x180));
  }
  if ((*(int *)(in_ECX + 0x188) == 0) && (*(char *)(in_ECX + 0x140) != '\0')) {
    FUN_00537890(*(undefined4 *)(in_ECX + 0x154),*(undefined4 *)(in_ECX + 0x158),
                 *(undefined4 *)(in_ECX + 0x15c),*(undefined4 *)(in_ECX + 0x160));
  }
  return;
}

