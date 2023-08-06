#include <myBigChars.h>
#include <myReadkey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
#include <time.h>

struct termios ws;
int vtime = 5;
int vmin = 1;
int regime;
int
main ()
{

  enum keys k;
  while (1)
    {
      // mt_clrscr();

      rk_readkey (&k);
      if (k == 0)
        printf ("pls\n");

      printf ("%d\n", k);
      if (k == KEY_F5)
        break;
    }

  return 0;
}
