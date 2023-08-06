#include <myTerm.h>
char temp[20];
int
mt_clrscr ()
{
  sprintf (temp, "\E[H\E[J");
  write (1, temp, strlen (temp));
  return 0;
}
int
mt_gotoXY (int x, int y)
{
  sprintf (temp, "\E[%d;%dH", x, y);
  write (1, temp, strlen (temp));
  return 0;
}
int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  if (!ioctl (1, TIOCGWINSZ, &ws))
    {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
    }
  else
    {
      fprintf (stderr, "Error.\n");
      return -1;
    }
  return 0;
}

int
mt_setfgcolor (enum colors color)
{
  sprintf (temp, "\E[3%dm", color);
  write (1, temp, strlen (temp));
  return 1;
}

int
mt_setbgcolor (enum colors color)
{
  sprintf (temp, "\E[4%dm", color);
  write (1, temp, strlen (temp));
  return 1;
}
