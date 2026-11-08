
undefined8 * entry(undefined4 param_1)

{
  undefined8 *extraout_ECX;
  undefined4 unaff_retaddr;
  undefined8 uStack_1c;
  undefined4 uStack_14;
  
  FUN_00406df3();
  RtlExitUserProcess(0);
  FUN_00412dc5(unaff_retaddr,param_1);
  *(undefined4 *)(extraout_ECX + 1) = uStack_14;
  *extraout_ECX = uStack_1c;
  return extraout_ECX;
}

