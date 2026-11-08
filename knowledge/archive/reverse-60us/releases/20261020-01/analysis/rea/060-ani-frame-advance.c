
void FUN_00a27dc0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int in_ECX;
  int local_8;
  
  if (*(int *)(in_ECX + 0x188) == 0) {
    iVar1 = *(int *)(in_ECX + 0x8c);
  }
  else {
    iVar1 = FUN_004caa00();
  }
  local_8 = *(int *)(in_ECX + 0x124);
  if (*(char *)(in_ECX + 0x13a) != '\x01') {
    iVar2 = FUN_00a24bb0(0);
    if (((*(int *)(in_ECX + 0x98) == 0) ||
        ((*(int *)(in_ECX + 0x9c) - *(int *)(in_ECX + 0x98)) / 0x7c == 0)) || (iVar2 < 0)) {
      (*(code *)PTR_FUN_00ff2ebc)
                (u_WARNING___s___abnormal_animation_00e44cc8,
                 u_CNRDAnimation__checkCurrentFrame_00e44d58);
      FUN_00a26040(0);
      FUN_00a27b60();
LAB_00a27f4d:
      *(undefined1 *)(in_ECX + 0x13a) = 1;
    }
    else {
      if ((iVar2 != 0) && (iVar3 = iVar1 - *(int *)(in_ECX + 300), iVar2 < iVar3)) {
        if (*(char *)(in_ECX + 0x130) == '\0') {
          *(int *)(in_ECX + 300) = iVar1;
          iVar1 = FUN_00493630();
          FUN_00a27870(iVar1 + -1);
          *(undefined1 *)(in_ECX + 0x13a) = 1;
          return;
        }
        *(int *)(in_ECX + 300) = iVar1 - iVar3 % iVar2;
      }
      if (*(char *)(in_ECX + 0x13a) == '\0') {
        while (*(int *)(in_ECX + 300) <= iVar1) {
          iVar2 = 0;
          if (*(int *)(in_ECX + 0x98) != 0) {
            iVar2 = (*(int *)(in_ECX + 0x9c) - *(int *)(in_ECX + 0x98)) / 0x7c;
          }
          if (local_8 == iVar2 + -1) {
            if (*(char *)(in_ECX + 0x130) == '\0') goto LAB_00a27f4d;
            if (*(int *)(in_ECX + 0x98) == 0) {
              return;
            }
            if ((uint)((*(int *)(in_ECX + 0x9c) - *(int *)(in_ECX + 0x98)) / 0x7c) < 2) {
              return;
            }
            local_8 = 0;
          }
          else {
            local_8 = local_8 + 1;
          }
          FUN_00a27870(local_8);
          if (*(char *)(in_ECX + 0x13a) != '\0') {
            return;
          }
        }
      }
    }
  }
  return;
}

