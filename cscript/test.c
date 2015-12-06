#!/home/nixo/git/cscript/cscript/Debug/cscript

#include <stdio.h>

int main(int num, char *opts[])
  {
    printf("Hi from stu.\n");
    printf("These are the params I got:\n");
    int lp;
    for (lp = 0; lp < num; lp++)
      {
        printf ("param #%d: %s\n", lp, opts[lp]);
      }
    return 0;
  }

