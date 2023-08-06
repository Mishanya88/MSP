#include "myReadkey.h"

struct termios termiosBuffer;

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  struct termios ws;
  tcgetattr (0, &ws);
  if (regime)
    ws.c_lflag |= ICANON;
  else
    {
      ws.c_lflag &= ~ICANON;
      ws.c_cc[VMIN] = vmin;
      ws.c_cc[VTIME] = vtime;
    }

  if (!echo)
    ws.c_lflag &= ~ECHO;
  else
    ws.c_lflag |= ECHO;
  if (!sigint)
    ws.c_lflag &= ~ISIG;
  else
    ws.c_lflag |= ISIG;
  tcsetattr (0, TCSANOW, &ws);
  return 0;
}
int
rk_mytermrestore (void)
{
  return tcsetattr (0, TCSANOW, &termiosBuffer);
}
int
rk_mytermsave (void)
{
  return tcgetattr (0, &termiosBuffer);
}
int
rk_readkey (enum keys *key)
{
  char temp[10];
  rk_mytermsave ();
  rk_mytermregime (0, 0, 1, 0, 1);
  read (0, temp, 10);
  // printf("%d",(int)temp[2]);
  if (temp[0] == '\E')
    {
      if ((int)temp[2] == 49)
        *key = (int)temp[3];
      else
        *key = (int)temp[2];
    }
  else
    *key = (int)temp[0];
  rk_mytermrestore ();
  return 0;
}