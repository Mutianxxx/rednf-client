
void FUN_004b9d80(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                 undefined1 param_6)

{
  int iVar1;
  int iVar2;
  int *in_ECX;
  
  iVar1 = param_1;
  if ((param_1 < 2) && (-1 < param_1)) {
    param_1 = param_2;
    FUN_00404560(&param_1);
    param_1 = param_3;
    FUN_00404560(&param_1);
    iVar2 = param_5;
    *(undefined1 *)(iVar1 + 0x1606 + (int)in_ECX) = (undefined1)param_4;
    param_4 = param_5;
    FUN_00404560(&param_4);
    *(undefined1 *)(iVar1 + 0x1604 + (int)in_ECX) = param_6;
    if (iVar2 != 0) {
      *(undefined1 *)(iVar1 + 0x1606 + (int)in_ECX) = 0;
    }
    param_4 = CONCAT31(param_4._1_3_,1);
    if ((in_ECX[0x582] == 4) || (in_ECX[0x583] == 4)) {
      param_4 = (uint)param_4._1_3_ << 8;
    }
    (**(code **)(*in_ECX + 0x498))(iVar1,in_ECX[iVar1 + 0x582],param_4,0);
  }
  return;
}

