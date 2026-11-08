
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_004c5730(int param_1,undefined4 param_2,undefined4 param_3,int param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int *in_ECX;
  undefined4 *unaff_FS_OFFSET;
  undefined4 local_10;
  undefined1 *puStack_c;
  undefined4 uStack_8;
  
  local_10 = *unaff_FS_OFFSET;
  uStack_8 = 0xffffffff;
  puStack_c = &LAB_00c57b9b;
  *unaff_FS_OFFSET = &local_10;
  iVar2 = (**(code **)(*in_ECX + 0x230))();
  cVar1 = (**(code **)(*in_ECX + 0x34))();
  if (cVar1 != '\0') {
    if ((iVar2 == 0x10) && (param_1 != 0x11)) goto LAB_004c5a80;
    FUN_00533830(param_1,param_2,param_3,param_4,iVar2);
  }
  FUN_004de370(param_1,param_2,param_3,param_4);
  cVar1 = (**(code **)(*in_ECX + 0x34))();
  if (cVar1 != '\0') {
    uVar3 = (**(code **)(*in_ECX + 0x230))();
    switch(uVar3) {
    case 0:
      if (iVar2 == 1) {
        (**(code **)(*in_ECX + 0x544))(0x1c,0xffffffff);
        (**(code **)(*in_ECX + 0x7cc))();
        *unaff_FS_OFFSET = local_10;
        return;
      }
      break;
    case 3:
      (**(code **)(*in_ECX + 0x544))(0x15,0xffffffff);
      *unaff_FS_OFFSET = local_10;
      return;
    case 5:
      (**(code **)(*in_ECX + 0x544))(0x16,0xffffffff);
      if (*(int *)(DAT_01002848 + 0x19a8) == 2) {
        in_ECX[0xa3b] = 100;
      }
      else {
        iVar2 = (**(code **)(*in_ECX + 0x238))();
        param_4 = (**(code **)(*in_ECX + 0x40))();
        param_4 = iVar2 * param_4;
        iVar2 = FUN_008ae0f0(&param_4,100);
        iVar2 = FUN_00473f20(100,0xfa,iVar2 % 0x65);
        in_ECX[0xa3b] = iVar2;
      }
      uVar3 = FUN_00534530(0);
      FUN_004c18d0(uVar3);
      if (*(int *)(in_ECX[0xa1d] + 0xaf8) != 0) {
        FUN_0052cee0(u_on_set_state_00cd1d4c);
        *unaff_FS_OFFSET = local_10;
        return;
      }
      break;
    case 8:
      iVar2 = in_ECX[0xa1d];
      if (iVar2 != 0) {
        uVar3 = *(undefined4 *)(iVar2 + 0xae0);
        *(undefined4 *)(iVar2 + 0xae0) = 0xffffffff;
        FUN_004c1310(in_ECX[0xa1d] + 0x8e4,uVar3,0xffffffff);
        *unaff_FS_OFFSET = local_10;
        return;
      }
      break;
    case 0x12:
      iVar2 = (**(code **)(*in_ECX + 0x370))();
      if (in_ECX[0x41] != iVar2) {
        iVar2 = *in_ECX;
        uVar3 = (**(code **)(iVar2 + 0x370))();
        (**(code **)(iVar2 + 0xf0))(uVar3);
      }
      (**(code **)(*in_ECX + 0x488))(0,0,0,0,0,0);
      (**(code **)(*in_ECX + 0x488))(1,0,0,0,0,0);
      (**(code **)(*in_ECX + 0x494))(0,0,1000,1000,0x3f800000,0x3f800000);
      (**(code **)(*in_ECX + 0x2d0))(0);
      (**(code **)(*in_ECX + 0x2d8))(0);
      (**(code **)(*in_ECX + 0x2e0))(1,2);
      if (in_ECX[0xa9b] == 0) {
        param_4 = FUN_00403c50(0x1e8);
        uStack_8 = 0;
        if (param_4 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = FUN_004936d0(u_Monster_Common_Animation_Unsummo_00cd1d00,1);
        }
        uStack_8 = 0xffffffff;
        in_ECX[0xa9b] = iVar2;
      }
      iVar2 = (**(code **)(*in_ECX + 0xe4))();
      FUN_00a25900((float)iVar2 * _DAT_00cd1cf8,(float)iVar2 * _DAT_00cd1cf8);
      (**(code **)(*in_ECX + 0xf8))(1,in_ECX[0xa9b],0,0,1,0,0,0,0,1);
      iVar2 = 0;
      do {
        cVar1 = (**(code **)(*in_ECX + 0x410))(iVar2);
        if (cVar1 != '\0') {
          piVar4 = (int *)(**(code **)(*in_ECX + 0x40c))(iVar2);
          (**(code **)(*piVar4 + 4))(0);
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x11);
    }
  }
LAB_004c5a80:
  *unaff_FS_OFFSET = local_10;
  return;
}

