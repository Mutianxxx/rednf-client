
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00511400(void)

{
  int *piVar1;
  bool bVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  float fVar8;
  undefined4 uVar9;
  uint uVar10;
  int *piVar11;
  int *in_ECX;
  float fVar12;
  float10 fVar13;
  float afStack_20 [3];
  int *local_14;
  int local_10;
  float local_c;
  int local_8;
  
  if ((char)in_ECX[0x38] != '\0') {
    return;
  }
  local_8 = FUN_00b06f00();
  local_8 = local_8 - in_ECX[0x39];
  iVar5 = FUN_00b06f00();
  in_ECX[0x39] = iVar5;
  if ((int *)in_ECX[0x24] != (int *)0x0) {
    iVar5 = (**(code **)(*(int *)in_ECX[0x24] + 0x94))();
    FUN_00510f50(0,iVar5 + in_ECX[0x25]);
    iVar5 = (**(code **)(*(int *)in_ECX[0x24] + 0x98))();
    FUN_00510f50(1,iVar5 + in_ECX[0x26]);
    iVar5 = (**(code **)(*(int *)in_ECX[0x24] + 0x9c))();
    FUN_00510f50(2,iVar5 + in_ECX[0x27]);
  }
  iVar5 = 0;
  piVar11 = in_ECX + 0x3b;
  do {
    iVar6 = FUN_0050fde0(iVar5,local_8);
    *piVar11 = iVar6;
    iVar5 = iVar5 + 1;
    piVar11 = piVar11 + 1;
  } while (iVar5 < 3);
  if (((char)in_ECX[0x40] != '\0') && (in_ECX[0x46] != 0)) {
    if ((0 < in_ECX[0x4e]) && (iVar5 = FUN_00b06f00(), in_ECX[0x4f] + in_ECX[0x4e] < iVar5)) {
      *(undefined1 *)(in_ECX + 0x40) = 0;
    }
    if (in_ECX[0x1d] != 0) {
      iVar5 = FUN_00b06f00();
      if (in_ECX[0x45] < iVar5) {
        iVar5 = FUN_00b06f00();
        in_ECX[0x45] = iVar5 + in_ECX[0x44];
        (**(code **)(*(int *)in_ECX[0x1d] + 0xc))(in_ECX[0x46],0);
        iVar5 = FUN_00c01544();
        local_10 = (iVar5 + 0x168) % 0x168;
        if ((float)in_ECX[0x48] == _DAT_00e9d7a4) {
          FUN_00511310((float)local_10,local_8);
        }
        else {
          local_10 = (**(code **)(*(int *)in_ECX[0x46] + 0x94))();
          in_ECX[0x49] = (int)(float)local_10;
          local_10 = (**(code **)(*(int *)in_ECX[0x46] + 0x98))();
          in_ECX[0x4a] = (int)(float)local_10;
        }
        if ((char)in_ECX[0x47] == '\0') {
          piVar11 = (int *)in_ECX[0x46];
          iVar5 = (**(code **)(*(int *)in_ECX[0x1d] + 0x94))();
          iVar6 = (**(code **)(*piVar11 + 0x94))();
          if (iVar5 < iVar6) {
            (**(code **)(*(int *)in_ECX[0x1d] + 0xb8))(1);
          }
          else {
            piVar11 = (int *)in_ECX[0x46];
            iVar5 = (**(code **)(*(int *)in_ECX[0x1d] + 0x94))();
            iVar6 = (**(code **)(*piVar11 + 0x94))();
            if (iVar6 <= iVar5) {
              (**(code **)(*(int *)in_ECX[0x1d] + 0xb8))(0);
            }
          }
        }
      }
      if ((float)in_ECX[0x48] != _DAT_00e9d7a4) {
        piVar11 = (int *)in_ECX[0x1d];
        local_14 = piVar11;
        uVar7 = FUN_00c01544(0);
        uVar7 = FUN_00c01544(uVar7);
        uVar7 = (**(code **)(*piVar11 + 0x98))(uVar7);
        uVar7 = (**(code **)(*piVar11 + 0x94))(uVar7);
        FUN_00499420(uVar7);
        iVar5 = FUN_00c01544();
        iVar5 = (iVar5 + 0x168) % 0x168;
        local_10 = iVar5;
        if ((float)in_ECX[0x4b] < _DAT_00e9d7a4) {
          piVar11 = (int *)*in_ECX;
          if (piVar11 == (int *)0x0) {
            piVar11 = in_ECX + 2;
          }
          (**(code **)(*piVar11 + 8))(1,0);
          uVar7 = FUN_00c01544();
          (**(code **)(*piVar11 + 8))(0,uVar7);
          uVar7 = FUN_00c01544();
          fVar13 = (float10)FUN_00499420(0,0,uVar7);
          in_ECX[0x4b] = (int)(float)fVar13;
        }
        iVar6 = FUN_00c01544();
        fVar8 = _DAT_00cd693c;
        local_14 = (int *)((iVar6 + 0x168) % 0x168);
        iVar6 = local_10;
        if ((int *)iVar5 == local_14) {
LAB_0051180d:
          fVar8 = (float)iVar6;
        }
        else {
          fVar12 = (float)(iVar5 - (int)local_14);
          if ((int)fVar12 < 0xb5) {
            local_c = fVar12;
            if ((int)fVar12 < 1) {
              if ((int)fVar12 < -0xb3) {
                fVar12 = (float)((int)fVar12 + 0x168);
                local_c = fVar12;
              }
              else {
                local_c = (float)-(int)fVar12;
              }
            }
          }
          else {
            local_c = (float)(0x168 - (int)fVar12);
            fVar12 = (float)-(int)local_c;
          }
          fVar3 = (float)(int)local_c;
          iVar6 = (int)local_14;
          if (((float)in_ECX[0x4d] <= fVar3) ||
             (local_c = (float)local_8 * (float)in_ECX[0x48] * _DAT_00cc11f8, iVar6 = local_10,
             fVar3 < local_c)) goto LAB_0051180d;
          if ((int)fVar12 < 1) {
            fVar8 = (float)in_ECX[0x4b] - local_c;
            bVar2 = _DAT_00e9d7a4 <= fVar8;
            in_ECX[0x4b] = (int)fVar8;
            if (bVar2) {
              fVar8 = (float)in_ECX[0x4b];
            }
            else {
              in_ECX[0x4b] = (int)(fVar8 + _DAT_00cd693c);
              fVar8 = (float)in_ECX[0x4b];
            }
          }
          else {
            fVar12 = local_c + (float)in_ECX[0x4b];
            in_ECX[0x4b] = (int)fVar12;
            if (fVar12 <= fVar8) {
              fVar8 = (float)in_ECX[0x4b];
            }
            else {
              in_ECX[0x4b] = (int)(fVar12 - _DAT_00cd693c);
              fVar8 = (float)in_ECX[0x4b];
            }
          }
        }
        FUN_00511310(fVar8,local_8);
      }
    }
  }
  if ((in_ECX[0x1e] == 0) || ((char)in_ECX[0x1f] == '\0')) goto LAB_00511afe;
  if ((in_ECX[0x20] == 2) && ((char)in_ECX[0x21] != '\0')) {
    (**(code **)(*(int *)in_ECX[0x1d] + 0x274))(0xffffffff,0,in_ECX[0x22]);
    goto LAB_00511afe;
  }
  iVar5 = 0;
  do {
    if (((int *)in_ECX[0x1e] == (int *)0x0) || ((char)in_ECX[0x1f] == '\0')) {
      piVar11 = (int *)*in_ECX;
      if (piVar11 == (int *)0x0) {
        piVar11 = in_ECX + 2;
      }
      fVar13 = (float10)(**(code **)*piVar11)(iVar5);
      fVar8 = (float)FUN_00447ff0((float)fVar13);
    }
    else {
      fVar8 = (float)(**(code **)(*(int *)in_ECX[0x1e] + 0x28))(iVar5);
    }
    piVar11 = (int *)*in_ECX;
    afStack_20[iVar5] = fVar8;
    if (piVar11 == (int *)0x0) {
      piVar11 = in_ECX + 2;
    }
    piVar1 = (int *)in_ECX[0x1e];
    (**(code **)*piVar11)(iVar5);
    local_14 = (int *)FUN_00c01544();
    iVar6 = (**(code **)(*piVar1 + 0x10))();
    *(int **)(iVar6 + iVar5 * 4) = local_14;
    iVar5 = iVar5 + 1;
  } while (iVar5 < 3);
  (**(code **)(*(int *)in_ECX[0x1e] + 8))();
  if ((((int *)in_ECX[0x1d] != (int *)0x0) &&
      (cVar4 = (**(code **)(*(int *)in_ECX[0x1d] + 0x2c))(1), cVar4 != '\0')) &&
     (((char)in_ECX[0x21] == '\0' || (in_ECX[0x20] == 0)))) {
    iVar5 = *(int *)in_ECX[0x1d];
    uVar7 = FUN_004eee30(in_ECX + 0x22);
    uVar7 = FUN_004eee20(uVar7);
    cVar4 = (**(code **)(iVar5 + 0xac))(uVar7);
    if (cVar4 != '\0') {
      iVar5 = *(int *)in_ECX[0x1d];
      uVar7 = FUN_004eee40();
      cVar4 = (**(code **)(iVar5 + 0xa8))(uVar7);
      if (cVar4 != '\0') goto LAB_0051194a;
    }
    (**(code **)(*(int *)in_ECX[0x1d] + 0x274))(0xffffffff,0,in_ECX[0x22]);
    *(undefined1 *)(in_ECX + 0x21) = 1;
  }
LAB_0051194a:
  if ((((char)in_ECX[0x21] != '\0') && (in_ECX[0x20] == 1)) && ((char)in_ECX[0x23] == '\0')) {
    local_10 = 0;
    do {
      iVar5 = local_10;
      piVar11 = (int *)in_ECX[0x1e];
      if (*(char *)((int)in_ECX + local_10 + 0x85) == '\0') {
        if ((piVar11 == (int *)0x0) || ((char)in_ECX[0x1f] == '\0')) {
          piVar11 = (int *)*in_ECX;
          if (piVar11 == (int *)0x0) {
            piVar11 = in_ECX + 2;
          }
          fVar13 = (float10)(**(code **)*piVar11)(local_10);
          local_c = (float)FUN_00447ff0((float)fVar13);
        }
        else {
          local_c = (float)(**(code **)(*piVar11 + 0x28))(local_10);
        }
        if (afStack_20[iVar5] != local_c) {
          do {
            fVar8 = afStack_20[iVar5];
            if ((int)fVar8 < (int)local_c) {
              afStack_20[iVar5] = (float)((int)fVar8 + 1);
            }
            else {
              afStack_20[iVar5] = (float)((int)fVar8 + -1);
            }
            piVar11 = (int *)in_ECX[0x1e];
            if (iVar5 == 2) {
              if ((piVar11 == (int *)0x0) || ((char)in_ECX[0x1f] == '\0')) {
                piVar11 = (int *)*in_ECX;
                if (piVar11 == (int *)0x0) {
                  piVar11 = in_ECX + 2;
                }
                fVar13 = (float10)(**(code **)*piVar11)(2);
                uVar7 = FUN_00447ff0((float)fVar13);
                cVar4 = (**(code **)(*(int *)in_ECX[0x1d] + 0xa8))(uVar7);
              }
              else {
                uVar7 = (**(code **)(*piVar11 + 0x28))(2);
                cVar4 = (**(code **)(*(int *)in_ECX[0x1d] + 0xa8))(uVar7);
              }
            }
            else {
              if ((piVar11 == (int *)0x0) || ((char)in_ECX[0x1f] == '\0')) {
                piVar11 = (int *)*in_ECX;
                if (piVar11 == (int *)0x0) {
                  piVar11 = in_ECX + 2;
                }
                fVar13 = (float10)(**(code **)*piVar11)(1);
                uVar7 = FUN_00447ff0((float)fVar13);
              }
              else {
                uVar7 = (**(code **)(*piVar11 + 0x28))(1);
              }
              if (((int *)in_ECX[0x1e] == (int *)0x0) || ((char)in_ECX[0x1f] == '\0')) {
                piVar11 = (int *)*in_ECX;
                if (piVar11 == (int *)0x0) {
                  piVar11 = in_ECX + 2;
                }
                fVar13 = (float10)(**(code **)*piVar11)(0);
                uVar9 = FUN_00447ff0((float)fVar13);
              }
              else {
                uVar9 = (**(code **)(*(int *)in_ECX[0x1e] + 0x28))(0);
              }
              cVar4 = (**(code **)(*(int *)in_ECX[0x1d] + 0xac))(uVar9,uVar7,0);
              iVar5 = local_10;
            }
            if (cVar4 == '\0') {
              (**(code **)(*(int *)in_ECX[0x1e] + 0x24))(iVar5,fVar8);
              afStack_20[iVar5] = fVar8;
              *(undefined1 *)((int)in_ECX + iVar5 + 0x85) = 1;
              break;
            }
          } while (afStack_20[iVar5] != local_c);
        }
      }
      else {
        (**(code **)(*piVar11 + 0x24))(local_10,afStack_20[local_10]);
      }
      local_10 = iVar5 + 1;
    } while (iVar5 + 1 < 3);
  }
  *(undefined1 *)(in_ECX + 0x23) = 0;
LAB_00511afe:
  FUN_00512a20();
  iVar5 = in_ECX[0x3f];
  if (iVar5 != 0) {
    iVar6 = DAT_00f5be7c;
    if (iVar5 != -1) {
      iVar6 = iVar5;
    }
    uVar10 = FUN_00b06f00();
    if ((((uint)(in_ECX[0x3a] + iVar6) <= uVar10) && (DAT_0104f1d4 != (int *)0x0)) &&
       (piVar11 = (int *)(**(code **)(*DAT_0104f1d4 + 0x48))(), in_ECX == piVar11)) {
      piVar11 = (int *)*in_ECX;
      if (piVar11 == (int *)0x0) {
        piVar11 = in_ECX + 2;
      }
      (**(code **)(*piVar11 + 0x10))();
      iVar5 = FUN_00b06f00();
      in_ECX[0x3a] = iVar5;
    }
  }
  return;
}

