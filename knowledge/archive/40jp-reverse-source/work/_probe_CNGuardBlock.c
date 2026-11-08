#include "include/arad/_fields/CNGuardBlock.h"
#include <stdio.h>
#include <stddef.h>
int main(){ struct CNGuardBlock_Fields s; (void)s;
  { volatile unsigned char *p = (unsigned char*)&s + 73; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 73; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 120; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 120; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 232; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 232; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 236; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 236; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 240; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 244; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 248; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 252; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 252; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 256; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 260; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 260; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 642; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 642; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 644; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 644; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 668; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 668; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 672; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7096; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7096; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7100; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7104; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7148; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7148; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7252; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7252; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7520; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7520; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7524; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7528; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7529; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7530; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7531; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7532; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7533; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7534; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7535; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7536; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7537; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7538; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7539; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7772; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 7772; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8352; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8352; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8356; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8360; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8669; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8669; p[0]=p[0]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8700; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8700; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8840; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8840; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8900; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8900; p[0]=p[3]=0; (void)p; }
  { volatile unsigned char *p = (unsigned char*)&s + 8904; p[0]=p[0]=0; (void)p; }
  printf("END\n"); return 0; }
