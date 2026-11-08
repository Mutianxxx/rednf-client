
int FUN_00a2d790(void)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  int in_ECX;
  
  piVar1 = (int *)FUN_00c00d0b(*(undefined4 *)(in_ECX + 0x7c),0,&PTR_PTR_00f40910,&PTR_PTR_00f5526c,
                               0);
  if ((*(int *)(in_ECX + 0x88) == 0) || (piVar1 == (int *)0x0)) {
    return in_ECX;
  }
  switch(*(undefined4 *)(in_ECX + 0x2cc)) {
  case 0:
    puVar2 = (undefined4 *)(**(code **)(*piVar1 + 0x3b8))();
    *puVar2 = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 1:
    iVar3 = (**(code **)(*piVar1 + 0x3b8))();
    *(undefined4 *)(iVar3 + 4) = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 2:
    iVar3 = (**(code **)(*piVar1 + 0x3b8))();
    *(undefined4 *)(iVar3 + 8) = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 3:
    iVar3 = (**(code **)(*piVar1 + 0x3b8))();
    *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 4:
    iVar3 = (**(code **)(*piVar1 + 0x3b8))();
    *(undefined4 *)(iVar3 + 0x10) = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 5:
    iVar3 = (**(code **)(*piVar1 + 0x3b8))();
    *(undefined4 *)(iVar3 + 0x14) = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 6:
    iVar3 = (**(code **)(*piVar1 + 0x3b8))();
    *(undefined4 *)(iVar3 + 0x18) = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 7:
    iVar3 = (**(code **)(*piVar1 + 0x3b8))();
    *(undefined4 *)(iVar3 + 0x1c) = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 8:
    iVar3 = (**(code **)(*piVar1 + 0x3b8))();
    *(undefined4 *)(iVar3 + 0x20) = *(undefined4 *)(in_ECX + 0x88);
    break;
  case 9:
    iVar3 = *(int *)(in_ECX + 0x2d0);
    iVar4 = (**(code **)(*piVar1 + 0x3b8))();
    iVar4 = iVar4 + 0x24;
    goto LAB_00a2d8d0;
  case 10:
    iVar3 = *(int *)(in_ECX + 0x2d0);
    iVar4 = (**(code **)(*piVar1 + 0x3b8))();
    iVar4 = iVar4 + 0x34;
LAB_00a2d8d0:
    *(undefined4 *)(*(int *)(iVar4 + 4) + iVar3 * 4) = *(undefined4 *)(in_ECX + 0x88);
  }
  (**(code **)(*piVar1 + 0x33c))();
  iVar3 = *(int *)(in_ECX + 0x88);
  *(undefined4 *)(in_ECX + 0x88) = 0;
  return iVar3;
}

