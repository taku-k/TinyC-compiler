#include <stdio.h>

chk(int x, int y)
{
  if (x == y) {
    printf("OK\n");
  }
  else {
    printf("NG\n");
    printf("Return:   %d\n", x);
    printf("Expected: %d\n", y);
  }
}

/* for ss.c */

int vv[10] = {3, 5, 1, 8, 7, 6, 2, 10, 4, 9};

int v(int i)
{
  return vv[i];
}

set_v(i, x)
{
  vv[i] = x;
}