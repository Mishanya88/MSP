#include "myBigChars.h"
int bigChars[19][2] = {
  { 0x8081808, 0x3E080808 },  // 1
  { 0x7E02027E, 0x7E404040 }, // 2
  { 0x7E02027E, 0x7E020202 }, // 3
  { 0x7E424242, 0x2020202 },  // 4
  { 0x7E40407E, 0x7E020202 }, // 5
  { 0x7E40407E, 0x7E424242 }, // 6
  { 0x202027E, 0x2020202 },   // 7
  { 0x7E42427E, 0x7E424242 }, // 8
  { 0x7E42427E, 0x7E020202 }, // 9
  { 0x4242427E, 0x7E424242 }, // 0
  { 0x7E422418, 0x42424242 }, // A
  { 0x7C44427C, 0x7C424244 }, // B
  { 0x4040407E, 0x7E404040 }, // C
  { 0x4242427C, 0x7C424242 }, // D
  { 0x7E40407E, 0x7E404040 }, // E
  { 0x7E40407E, 0x40404040 }, // F
  { 0x7E181800, 0x18187E },   // +
  { 0x7E000000, 0x7E },       // -
  { 0, 0 }                    // Пустой символ
};
int
bc_printA (char *str)
{
  write (1, "\E(0", strlen ("\E(0"));
  write (1, str, strlen (str));
  write (1, "\E(B", strlen ("\E(B"));
  return 0;
}
int
bc_box (int x1, int y1, int x2, int y2)
{

  write (1, "\E(0", strlen ("\E(0"));
  mt_gotoXY (x1, y1);
  write (1, "l", strlen ("l"));
  mt_gotoXY (x1, y1 + y2 + 1);
  write (1, "k", strlen ("k"));
  mt_gotoXY (x1 + x2 + 1, y1);
  write (1, "m", strlen ("m"));
  mt_gotoXY (x1 + x2 + 1, y1 + y2 + 1);
  write (1, "j", strlen ("j"));

  for (int i = 1; i < x2 + 1; i++)
    {
      mt_gotoXY (x1 + i, y1);
      write (1, "x", strlen ("x"));
      mt_gotoXY (x1 + i, y1 + y2 + 1);
      write (1, "x", strlen ("x"));
    }
  for (int i = 1; i < y2 + 1; i++)
    {
      mt_gotoXY (x1, y1 + i);
      write (1, "q", strlen ("q"));
      mt_gotoXY (x1 + x2 + 1, y1 + i);
      write (1, "q", strlen ("q"));
    }
  write (1, "\E(B", strlen ("\E(B"));
  return 0;
}
int
bc_printbigchar (int *number, int x, int y, enum colors color1,
                 enum colors color2)
{
  y += 7;
  mt_setbgcolor (color2);
  mt_setfgcolor (color1);
  for (int j = 0; j < 2; j++)
    {
      for (int i = 0; i < 32; i++)
        {
          mt_gotoXY (x, y);
          bc_printA ((((number[j] >> i) & 1) == 1 ? "a" : " "));
          y--;
          if (((i + 1) % 8) == 0)
            {
              y += 8;
              x++;
            }
        }
    }
  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (WHITE);
  write (1, "\E[0m", strlen ("\E[0m"));

  return 0;
}
int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (x < 0 || x > 7 || y < 0 || y > 7)
    {
      return -1;
    }

  int ind = 0;
  if (x > 3)
    ind = 1;

  *value = ((big[ind] >> (x * 8)) >> y) & 1;

  return 0;
}
int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (x < 0 || x > 7 || y < 0 || y > 7)
    return -1;
  if (value < 0 || value > 1)
    return -1;
  if (y < 4)
    {
      if (value)
        big[0] |= (1 << (y * 8 + 7 - x));
      else
        big[0] &= ~(1 << (y * 8 + 7 - x));
    }
  else
    {
      if (value)
        big[1] |= (1 << ((y - 4) * 8 + 7 - x));
      else
        big[1] &= ~(1 << ((y - 4) * 8 + 7 - x));
    }
  return 0;
}
int
bc_bigcharwrite (int fd, int *big, int count)
{
  if (!big || fd < 0)
    {
      return -1;
    }

  while (count > 0)
    {
      int result;
      if ((result = write (fd, big, sizeof (int) * 2)) == -1)
        {
          return -1;
        }
      // printf("%d\n", result);
      count--;
    }

  return 0;
}

int
bc_bigcharread (int fd, int *big, int need_count, int *count)
{
  if (fd < 0)
    {
      return -1;
    }

  while (need_count > 0)
    {
      int result;
      if ((result = read (fd, big, sizeof (int) * 2)) == -1)
        {
          return -1;
        }
      need_count--;
      *count = *count + 1;
    }

  return 0;
}