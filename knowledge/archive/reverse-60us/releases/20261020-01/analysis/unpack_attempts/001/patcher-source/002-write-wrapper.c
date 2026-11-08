
short FUN_00407186(undefined4 param_1,uint param_2,undefined4 param_3,uint param_4)

{
  short sVar1;
  uint uVar2;
  undefined1 local_58 [72];
  
  uVar2 = param_4;
  if (param_4 < param_2) {
    uVar2 = param_2;
  }
  sVar1 = 0x10;
  if ((uVar2 < 0x41) && (sVar1 = FUN_0040747e(local_58,uVar2), sVar1 == 0)) {
    uVar2 = FUN_00407238(param_3,param_4);
    if ((uVar2 & 1) == 0) {
      uVar2 = FUN_00407238(param_1,param_2);
      sVar1 = 0x10;
      if ((uVar2 & 1) != 0) {
        sVar1 = FUN_00407205(param_3,param_4);
      }
    }
    else {
      sVar1 = 0;
    }
  }
  return sVar1;
}

