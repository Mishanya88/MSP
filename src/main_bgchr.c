#include <fcntl.h>
#include <myBigChars.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  mt_clrscr ();
  int a[2] = { 0x8081808, 0x3E080808 };
  int value;

  bc_box (9, 4, 8, 18);
  bc_printbigchar (a, 10, 5, PURPLE, CYAN);

  bc_setbigcharpos (a, 1, 4, 0);
  bc_setbigcharpos (a, 1, 3, 1);
  bc_printbigchar (a, 10, 15, PURPLE, CYAN);

  bc_getbigcharpos (a, 1, 3, &value);
  printf ("\n\nValue = %d\n", value);

  FILE *outFile;
  outFile = fopen ("BigChar.txt", "wb");
  fclose (outFile);

  int fd = open ("BigChar.txt", O_WRONLY);
  int count = 0;

  int *big = malloc (sizeof (int) * 1);
  big[0] = 0;
  big[1] = 0;

  bc_bigcharwrite (fd, a, 1);
  close (fd);

  fd = open ("BigChar.txt", O_RDONLY);
  bc_bigcharread (fd, big, 1, &count);
  printf ("%d\n", big[0]);
  printf ("%d\n", big[1]);
  printf ("%d\n", count);
  close (fd);

  free (big);

  return 0;
}