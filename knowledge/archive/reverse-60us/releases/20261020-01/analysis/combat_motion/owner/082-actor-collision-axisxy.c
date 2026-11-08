
bool FUN_004b00f0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int *in_ECX;
  undefined4 uVar5;
  int *piVar6;
  uint uVar7;
  
  piVar6 = (int *)0x0;
  if (((in_ECX != (int *)0x0) && (cVar1 = (**(code **)(*in_ECX + 100))(), cVar1 != '\0')) &&
     (iVar3 = (**(code **)(*in_ECX + 0x3c4))(), iVar3 != 0)) {
    uVar7 = 0;
    while( true ) {
      iVar3 = (**(code **)(*in_ECX + 0x3c4))();
      if (*(int *)(iVar3 + 4) == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 8) - *(int *)(iVar3 + 4) >> 2;
      }
      if (iVar3 <= (int)uVar7) break;
      iVar4 = (**(code **)(*in_ECX + 0x3c4))();
      iVar3 = *(int *)(iVar4 + 4);
      if ((iVar3 == 0) || ((uint)(*(int *)(iVar4 + 8) - iVar3 >> 2) <= uVar7)) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + uVar7 * 4);
      }
      if (*(int **)(iVar3 + 4) == in_ECX) {
        iVar4 = (**(code **)(*in_ECX + 0x3c4))();
        iVar3 = *(int *)(iVar4 + 4);
        if ((iVar3 == 0) || ((uint)(*(int *)(iVar4 + 8) - iVar3 >> 2) <= uVar7)) {
          uVar5 = 0;
        }
        else {
          uVar5 = *(undefined4 *)(iVar3 + uVar7 * 4);
        }
        piVar6 = (int *)FUN_00c00d0b(uVar5,0,&PTR_PTR_00f551f4,&PTR_PTR_00f5963c,0);
        if ((piVar6 != (int *)0x0) && (cVar1 = (**(code **)(*piVar6 + 0x60))(), cVar1 != '\0'))
        break;
      }
      uVar7 = uVar7 + 1;
    }
  }
  cVar1 = (**(code **)(*in_ECX + 0x410))(0x10);
  if ((cVar1 != '\0') && (piVar6 == (int *)0x0)) {
    iVar3 = (**(code **)(*in_ECX + 0x230))();
    return iVar3 == 5;
  }
  uVar2 = FUN_004e7dd0(param_1,param_2,param_3);
  return (bool)uVar2;
}

