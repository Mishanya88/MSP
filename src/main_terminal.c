#include <myTerm.h>
#include <stdio.h>

int
main (void)
{
  mt_clrscr ();
  mt_setbgcolor (GREEN);
  int x, y;

  mt_getscreensize (&y, &x);
  mt_gotoXY (x / 2, y / 2);

  printf ("              ");
  mt_gotoXY (x / 2, y / 2 + 1);
  mt_setfgcolor (GREEN);
  printf (" ");
  mt_setbgcolor (BLACK);
  printf (" HELLO ");
  mt_setbgcolor (GREEN);
  mt_setfgcolor (WHITE);
  printf (" USER");
  // mt_setfgcolor(WHITE);
  // mt_setbgcolor(WHITE);
  printf (" ");
  mt_gotoXY (x / 2, y / 2 + 2);
  printf ("              ");
  mt_setbgcolor (RED);
  mt_gotoXY (0, y);
  printf ("Continue?[Enter symbol]: ");
  scanf ("%d", &x);
  // mt_clrscr();
  return 0;
}