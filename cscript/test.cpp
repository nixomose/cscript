#!/home/nixo/git/cscript/cscript/Debug/cscript
#include <stdio.h>

class test
  {
    public:
      test(int Num, char **Opts)
        {
          num = Num;
          opts = Opts;
        }
      ~test(void)
        {
        }

      int go(void)
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
    private:
      int num;
      char **opts;
  };

int main(int num, char *opts[])
  {
    test me(num, opts);
    return me.go();
  }

