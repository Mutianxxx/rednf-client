
void FUN_00a48c80(undefined4 param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  int in_ECX;
  int iVar3;
  undefined4 *puVar4;
  
  if ((((*(int *)(param_3 + 4) != 0) && (*(int *)(param_3 + 8) - *(int *)(param_3 + 4) >> 2 != 0))
      && (cVar1 = (**(code **)(**(int **)(in_ECX + 0x7c) + 100))(), cVar1 != '\0')) &&
     (cVar1 = FUN_0049c090(), cVar1 != '\0')) {
    (**(code **)(*DAT_01003164 + 8))(0x33,1);
    iVar3 = *DAT_01003164;
    uVar2 = (**(code **)(**(int **)(in_ECX + 0x7c) + 0x3c))();
    (**(code **)(iVar3 + 0x24))(uVar2);
    iVar3 = *DAT_01003164;
    uVar2 = (**(code **)(**(int **)(in_ECX + 0x7c) + 0x40))();
    (**(code **)(iVar3 + 0x24))(uVar2);
    (**(code **)(*DAT_01003164 + 0x24))(*(undefined2 *)(in_ECX + 0x2cc));
    (**(code **)(*DAT_01003164 + 0x24))(*(undefined2 *)(in_ECX + 0x2d0));
    (**(code **)(*DAT_01003164 + 0x24))(param_1);
    (**(code **)(*DAT_01003164 + 0x24))(param_2);
    if (*(int *)(param_3 + 4) == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(param_3 + 8) - *(int *)(param_3 + 4) >> 2;
    }
    (**(code **)(*DAT_01003164 + 0x24))(iVar3);
    puVar4 = *(undefined4 **)(param_3 + 4);
    if (puVar4 != *(undefined4 **)(param_3 + 8)) {
      do {
        cVar1 = FUN_0049c090();
        if (cVar1 != '\0') {
          iVar3 = *DAT_01003164;
          uVar2 = (**(code **)(*(int *)*puVar4 + 0x3c))();
          (**(code **)(iVar3 + 0x24))(uVar2);
          iVar3 = *DAT_01003164;
          uVar2 = (**(code **)(*(int *)*puVar4 + 0x40))();
          (**(code **)(iVar3 + 0x24))(uVar2);
        }
        puVar4 = puVar4 + 1;
      } while (puVar4 != *(undefined4 **)(param_3 + 8));
    }
    (**(code **)(*DAT_010c0790 + 0x44))(1,0xffffffff,0,3);
    (**(code **)(**(int **)(in_ECX + 0x7c) + 0x178))
              (param_2,param_3,*(undefined4 *)(in_ECX + 0x2cc),*(undefined4 *)(in_ECX + 0x2d0));
  }
  return;
}

