
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0050fde0(int *param_1,float param_2)

{
  int iVar1;
  char cVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  int *in_ECX;
  int iVar7;
  float10 fVar8;
  int local_28 [3];
  undefined8 local_1c;
  int local_14;
  int local_10;
  int *local_c;
  int local_8;
  
  iVar1 = (int)param_1;
  piVar3 = (int *)*in_ECX;
  if (piVar3 == (int *)0x0) {
    piVar3 = in_ECX + 2;
  }
  fVar8 = (float10)(**(code **)(*piVar3 + 8))(param_1);
  local_1c = (double)ABS(fVar8);
  fVar8 = (float10)(**(code **)(*piVar3 + 8))(iVar1);
  if ((float10)local_1c <= ABS(fVar8) * (float10)_DAT_00cab8e8) {
    piVar3 = (int *)*in_ECX;
    if (piVar3 == (int *)0x0) {
      piVar3 = in_ECX + 2;
    }
    if (piVar3[iVar1 + 7] == 0) {
      return 0;
    }
  }
  piVar3 = (int *)*in_ECX;
  if (piVar3 == (int *)0x0) {
    piVar3 = in_ECX + 2;
  }
  fVar8 = (float10)(**(code **)(*piVar3 + 8))(iVar1);
  param_1 = (int *)(float)fVar8;
  piVar4 = (int *)*in_ECX;
  piVar3 = piVar4;
  if (piVar4 == (int *)0x0) {
    piVar3 = in_ECX + 2;
  }
  local_10 = piVar3[iVar1 + 7];
  piVar3 = piVar4;
  if (piVar4 == (int *)0x0) {
    piVar3 = in_ECX + 2;
  }
  local_8 = piVar3[iVar1 + 10];
  if (local_10 == 0) {
    fVar8 = (float10)(float)param_1;
  }
  else if ((local_8 == -1) || ((int)param_2 <= local_8)) {
    if (piVar4 == (int *)0x0) {
      piVar4 = in_ECX + 2;
    }
    local_1c = (double)CONCAT44(*piVar4,(undefined4)local_1c);
    local_c = piVar4;
    fVar8 = (float10)(**(code **)(*piVar4 + 8))(iVar1);
    iVar7 = (int)param_2;
    local_14 = local_10 * (int)param_2;
    (**(code **)(local_1c._4_4_ + 0xc))
              (iVar1,(float)((float10)local_14 * (float10)_DAT_00cc11f8 + fVar8));
    piVar3 = (int *)*in_ECX;
    if (piVar3 == (int *)0x0) {
      piVar3 = in_ECX + 2;
    }
    fVar8 = (float10)(**(code **)(*piVar3 + 8))(iVar1);
    fVar8 = (fVar8 + (float10)(float)param_1) * (float10)_DAT_00cd4bd0;
    if (local_8 != -1) {
      piVar3 = (int *)*in_ECX;
      if (piVar3 == (int *)0x0) {
        piVar3 = in_ECX + 2;
      }
      piVar3[iVar1 + 10] = piVar3[iVar1 + 10] - iVar7;
      piVar4 = (int *)*in_ECX;
      piVar3 = piVar4;
      if (piVar4 == (int *)0x0) {
        piVar3 = in_ECX + 2;
      }
      if (piVar3[iVar1 + 10] == 0) {
        if (piVar4 == (int *)0x0) {
          piVar4 = in_ECX + 2;
        }
        piVar4[iVar1 + 7] = 0;
      }
    }
  }
  else {
    if (piVar4 == (int *)0x0) {
      piVar4 = in_ECX + 2;
    }
    local_14 = *piVar4;
    local_c = piVar4;
    fVar8 = (float10)(**(code **)(*piVar4 + 8))(iVar1);
    iVar7 = local_8;
    local_10 = local_8 * local_10;
    (**(code **)(local_14 + 0xc))(iVar1,(float)((float10)local_10 * (float10)_DAT_00cc11f8 + fVar8))
    ;
    local_14 = (int)param_2 - iVar7;
    piVar3 = (int *)*in_ECX;
    if (piVar3 == (int *)0x0) {
      piVar3 = in_ECX + 2;
    }
    fVar8 = (float10)(**(code **)(*piVar3 + 8))(iVar1);
    piVar3 = (int *)*in_ECX;
    param_1 = (int *)(float)((fVar8 + (float10)(float)param_1) * (float10)_DAT_00cd4bd0);
    if (piVar3 == (int *)0x0) {
      piVar3 = in_ECX + 2;
    }
    fVar8 = (float10)(**(code **)(*piVar3 + 8))(iVar1);
    piVar3 = (int *)*in_ECX;
    fVar8 = ((float10)local_8 * (float10)(float)param_1 + fVar8 * (float10)local_14) /
            (float10)(int)param_2;
    if (piVar3 == (int *)0x0) {
      piVar3 = in_ECX + 2;
    }
    piVar3[iVar1 + 10] = 0;
    piVar3 = (int *)*in_ECX;
    if (piVar3 == (int *)0x0) {
      piVar3 = in_ECX + 2;
    }
    piVar3[iVar1 + 7] = 0;
  }
  param_2 = (float)((float10)(int)param_2 * fVar8 * (float10)_DAT_00cc11f8);
  if (param_2 <= _DAT_00cd682c) {
    if (param_2 < _DAT_00cd6828) {
      param_2 = -2000.0;
    }
  }
  else {
    param_2 = 2000.0;
  }
  iVar7 = 0;
  if (((in_ECX[0x1e] == 0) || ((char)in_ECX[0x1f] == '\0')) && (in_ECX[0x1d] != 0)) {
    local_28[0] = 0;
    local_28[1] = 0;
    local_28[2] = 0;
    do {
      piVar3 = (int *)*in_ECX;
      if (piVar3 == (int *)0x0) {
        piVar3 = in_ECX + 2;
      }
      fVar8 = (float10)(**(code **)*piVar3)(iVar7);
      iVar5 = FUN_00447ff0((float)fVar8);
      local_28[iVar7] = iVar5;
      iVar7 = iVar7 + 1;
    } while (iVar7 < 3);
    piVar3 = (int *)*in_ECX;
    if (piVar3 == (int *)0x0) {
      piVar3 = in_ECX + 2;
    }
    fVar8 = (float10)(**(code **)*piVar3)(iVar1);
    iVar5 = FUN_00447ff0((float)(fVar8 + (float10)param_2));
    iVar7 = local_28[iVar1];
    while (iVar7 != iVar5) {
      iVar7 = local_28[iVar1];
      local_1c = (double)CONCAT44(iVar7,(undefined4)local_1c);
      if (iVar7 < iVar5) {
        iVar7 = iVar7 + 1;
      }
      else {
        iVar7 = iVar7 + -1;
      }
      piVar3 = (int *)in_ECX[0x1d];
      local_28[iVar1] = iVar7;
      param_1 = (int *)0x0;
      if (iVar1 == 2) {
        cVar2 = (**(code **)(*piVar3 + 0xa8))(local_28[2]);
      }
      else {
        cVar2 = (**(code **)(*piVar3 + 0xac))(local_28[0],local_28[1],&param_1);
      }
      if (cVar2 == '\0') {
        piVar3 = (int *)*in_ECX;
        if (piVar3 == (int *)0x0) {
          piVar3 = in_ECX + 2;
        }
        (**(code **)(*piVar3 + 4))(iVar1,(float)local_1c._4_4_);
        cVar2 = (**(code **)(*(int *)in_ECX[0x1d] + 0x2c))(1);
        if (cVar2 != '\0') {
          piVar3 = (int *)*in_ECX;
          if (piVar3 == (int *)0x0) {
            piVar3 = in_ECX + 2;
          }
          iVar7 = *(int *)in_ECX[0x1d];
          fVar8 = (float10)(**(code **)(*piVar3 + 8))(iVar1,param_1);
          (**(code **)(iVar7 + 0x274))(iVar1,(float)fVar8);
        }
        return 4;
      }
      iVar7 = local_28[iVar1];
    }
  }
  param_1 = (int *)*in_ECX;
  if (param_1 == (int *)0x0) {
    param_1 = in_ECX + 2;
  }
  iVar7 = *param_1;
  fVar8 = (float10)(**(code **)*param_1)(iVar1);
  (**(code **)(iVar7 + 4))(iVar1,(float)(fVar8 + (float10)param_2));
  piVar4 = (int *)*in_ECX;
  piVar3 = piVar4;
  if (piVar4 == (int *)0x0) {
    piVar3 = in_ECX + 2;
  }
  if (piVar3[iVar1 + 7] == 0) {
    if (piVar4 == (int *)0x0) {
      piVar4 = in_ECX + 2;
    }
    fVar8 = (float10)(**(code **)(*piVar4 + 8))(iVar1);
    local_1c = (double)ABS(fVar8);
    fVar8 = (float10)(**(code **)(*piVar4 + 8))(iVar1);
    if ((float10)local_1c <= ABS(fVar8) * (float10)_DAT_00cab8e8) {
      return 0;
    }
    return 2;
  }
  if (piVar4 == (int *)0x0) {
    piVar4 = in_ECX + 2;
  }
  fVar8 = (float10)(**(code **)(*piVar4 + 8))(iVar1);
  uVar6 = 1;
  if ((float10)_DAT_00e9d7a4 <= fVar8 * (float10)piVar4[iVar1 + 7]) {
    uVar6 = 3;
  }
  return uVar6;
}

