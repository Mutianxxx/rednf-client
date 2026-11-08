
float10 FUN_00b099b0(float param_1,float param_2,int param_3,int param_4)

{
  if (param_4 <= param_3) {
    return (float10)param_2;
  }
  if (param_3 < 1) {
    return (float10)param_1;
  }
  return (((float10)param_2 - (float10)param_1) * (float10)param_3) / (float10)param_4 +
         (float10)param_1;
}

