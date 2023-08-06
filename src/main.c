#include <myBigChars.h>
#include <myReadkey.h>
#include <mySimpleComputer.h>
#include <myTerm.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
extern int bigChars[18][2];
int instructionCounter = 0;
int selectedCell = 0;
int Acum;
int lastResult = 0;
enum colors textColor = WHITE, textEditSelected = WHITE, textCounter = GREEN;
extern unsigned short int memory[MEMORYSIZE];
extern unsigned short int regs;
int sc_regInit ();
void
updateMemory (int address)
{
  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (textColor);
  int value, row, col, command, operand;
  char buf[6];
  if (sc_memoryGet (address, &value) < 0
      || sc_commandDecode (value & 0x3FFF, &command, &operand) < 0)
    return;

  if (address == selectedCell)
    {
      mt_setbgcolor (textEditSelected);
      mt_setfgcolor (BLACK);
    }
  if (address == instructionCounter)
    {
      mt_setbgcolor (textCounter);
    }

  row = address / 10;
  col = address % 10;

  snprintf (buf, 6, "%c%02X%02X", (value & 0x4000) ? '-' : '+', command,
            operand);

  mt_gotoXY (2 + row, 2 + col * 6);
  write (1, buf, 5);
  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (textColor);
  return;
}

void
UpdFlags ()
{
  int reg_p, reg_o, reg_m, reg_t, reg_e;
  char r_P = ' ', r_O = ' ', r_M = ' ', r_T = ' ', r_E = ' ';
  sc_regGet (REG_DIVIDEZERO, &reg_o);
  sc_regGet (REG_UNKNOWNCOMMAND, &reg_e);
  sc_regGet (REG_MEMOUTSIDE, &reg_m);
  sc_regGet (REG_OVERFLOW, &reg_p);
  sc_regGet (REG_CLOCKIGNORE, &reg_t);
  if (reg_p == 1)
    r_P = 'P';
  if (reg_o == 1)
    r_O = 'O';
  if (reg_m == 1)
    r_M = 'M';
  if (reg_t == 1)
    r_T = 'T';
  if (reg_e == 1)
    r_E = 'E';
  mt_gotoXY (11, 64);
  printf ("   %c %c %c %c %c\n", r_P, r_O, r_M, r_T, r_E);
  mt_gotoXY (11, 62);
  mt_gotoXY (23, 1);
}
int
updateAcum (int value)
{
  if (abs (value) > 0x7fff)
    {
      sc_regSet (REG_OVERFLOW, 1);
      UpdFlags ();
      return -1;
    }
  Acum = value;
  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (textColor);
  mt_gotoXY (2, 68);
  sprintf (temp, "%s%04X", (value < 0) ? "-" : "+", abs (Acum));
  write (1, temp, strlen (temp));
  return 0;
}
void
updateICounter ()
{

  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (textColor);
  mt_gotoXY (5, 68);
  sprintf (temp, "+%d", instructionCounter);
  write (1, temp, strlen (temp));
}
void
updOp ()
{
  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (textColor);
  mt_gotoXY (8, 67);
  int value, command, operand;
  sc_memoryGet (instructionCounter, &value);
  sc_commandDecode (value, &command, &operand);
  sprintf (temp, "%s%02X : %02X", (value < 0) ? "-" : "+", command, operand);
  write (1, temp, strlen (temp));
}

void
updateBigMemory ()
{
  int value, command, operand;
  char valueChar[5];
  // printf("%d\n",instructionCounter);
  sc_memoryGet (instructionCounter, &value);

  sc_commandDecode (value & 0x3FFF, &command, &operand);

  sprintf (valueChar, "%s%02X%02X", (value & 0x4000) ? "-" : "+", command,
           operand);
  for (int i = 0; i < 5; i++)

    switch (valueChar[i])
      {
      case '1':
        bc_printbigchar (bigChars[0], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '2':
        bc_printbigchar (bigChars[1], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '3':
        bc_printbigchar (bigChars[2], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '4':
        bc_printbigchar (bigChars[3], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '5':
        bc_printbigchar (bigChars[4], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '6':
        bc_printbigchar (bigChars[5], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '7':
        bc_printbigchar (bigChars[6], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '8':
        bc_printbigchar (bigChars[7], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '9':
        bc_printbigchar (bigChars[8], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '0':
        bc_printbigchar (bigChars[9], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case 'A':
        bc_printbigchar (bigChars[10], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case 'B':
        bc_printbigchar (bigChars[11], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case 'C':
        bc_printbigchar (bigChars[12], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case 'D':
        bc_printbigchar (bigChars[13], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case 'E':
        bc_printbigchar (bigChars[14], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case 'F':
        bc_printbigchar (bigChars[15], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '+':
        bc_printbigchar (bigChars[16], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      case '-':
        bc_printbigchar (bigChars[17], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      default:
        bc_printbigchar (bigChars[18], 14, 2 + 8 * i, textColor, CONSOLE);
        break;
      }
}
void
outputWrite (char *c)
{
  mt_gotoXY (23, 1);
  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (WHITE);
  write (1, c, strlen (c));
}
void
outputClear ()
{
  mt_gotoXY (23, 1);
  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (WHITE);
  write (1, "                                                         ",
         strlen ("                                                         "));
  mt_gotoXY (23, 1);
}
int ALU (int, int);
int
CU ()
{
  int command, operand;
  if (instructionCounter > 99)
    return instructionCounter;
  if (sc_commandDecode (memory[instructionCounter], &command, &operand) == -1)
    {
      sc_regSet (REG_UNKNOWNCOMMAND, 1);
      sc_regSet (REG_CLOCKIGNORE, 1);
      UpdFlags ();
      return instructionCounter;
    }

  // 1512 42
  // 1582 43
  // 1412 40
  // 1499 41
  // 1012 32
  // 1085 33 50
  // 842	10
  // 899 11
  // 882 20
  // printf ("%d   ", command);
  // printf ("%d", operand);
  switch (command)
    {
    case 0x10:
      {
        outputWrite ("Input value (IN HEX): ");
        int temp, result;
        scanf ("%x", &temp);
        result = sc_memorySet (operand, temp);
        updateMemory (operand);
        while (getchar () != '\n')
          ;
        outputClear ();
        if (result)
          {
            sc_regSet (REG_CLOCKIGNORE, 0);
            sc_regSet (REG_OVERFLOW, 1);
            UpdFlags ();
            alarm (0);
            return instructionCounter;
          }
        lastResult = temp;
      }
      break;
    case 0x11:
      {
        char temp[30];
        int temp2;
        if (!sc_memoryGet (operand, &temp2))
          {
            outputClear ();
            sprintf (temp, "Output value: %s%X",
                     ((temp2 >> 15) & 0x1) == 1 ? "-" : "",
                     ((temp2 >> 15) & 0x1) == 1 ? ~(temp2 - 1) : temp2);
            outputWrite (temp);
          }
        else
          {
            sc_regSet (REG_CLOCKIGNORE, 0);
            sc_regSet (REG_MEMOUTSIDE, 1);
            alarm (0);
            return instructionCounter;
          }
      }
      break;
    case 0x20:
      if (sc_memoryGet (operand, &command))
        {
          sc_regSet (REG_CLOCKIGNORE, 0);
          sc_regSet (REG_MEMOUTSIDE, 1);
          UpdFlags ();
          alarm (0);
          return instructionCounter;
        }
      if (updateAcum (command))
        {
          sc_regSet (REG_CLOCKIGNORE, 0);
          sc_regSet (REG_OVERFLOW, 1);
          UpdFlags ();
          alarm (0);
          return instructionCounter;
        }
      lastResult = command;
      break;
    case 0x21:
      if (sc_memorySet (operand, Acum))
        {
          sc_regSet (REG_CLOCKIGNORE, 0);
          sc_regSet (REG_OVERFLOW, 1);
          UpdFlags ();
          alarm (0);
          return instructionCounter;
        }
      lastResult = Acum;
      break;
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
      if (ALU (command, operand))
        {
          sc_regSet (REG_CLOCKIGNORE, 0);
          sc_regSet (REG_OVERFLOW, 1);
          UpdFlags ();
          alarm (0);
          return instructionCounter;
        }
      lastResult = Acum;
      break;
    case 0x40:
      if (operand > 99 || operand < 0)
        {
          sc_regSet (REG_MEMOUTSIDE, 1);
          sc_regSet (REG_CLOCKIGNORE, 0);
          UpdFlags ();
          alarm (0);
          return instructionCounter;
        }
      return operand;
      break;
    case 0x41:
      if (operand > 99 || operand < 0)
        {
          sc_regSet (REG_MEMOUTSIDE, 1);
          sc_regSet (REG_CLOCKIGNORE, 0);
          UpdFlags ();
          alarm (0);
          return instructionCounter;
        }
      if (Acum < 0)
        return operand;
      break;
    case 0x42:
      if (operand > 99 || operand < 0)
        {
          sc_regSet (REG_MEMOUTSIDE, 1);
          sc_regSet (REG_CLOCKIGNORE, 0);
          UpdFlags ();
          alarm (0);
          return instructionCounter;
        }
      if (Acum == 0)
        return operand;

      break;
    case 0x43:
      alarm (0);
      sc_regSet (REG_CLOCKIGNORE, 0);
      UpdFlags ();
      // outputClear ();
      // outputWrite ("Stop");
      return instructionCounter;
      break;
    case 0x59:
      {
        int value;
        sc_regGet (REG_OVERFLOW, &value);
        if (Acum & 1 == 0)
          {
            if (operand > 99 || operand < 0)
              {
                sc_regSet (REG_MEMOUTSIDE, 1);
                sc_regSet (REG_CLOCKIGNORE, 0);
                UpdFlags ();
                alarm (0);
                return instructionCounter;
              }
            return operand;
          }
      }
      break;
    default:
      sc_regSet (REG_UNKNOWNCOMMAND, 1);
      sc_regSet (REG_CLOCKIGNORE, 0);
      UpdFlags ();
      alarm (0);
      return instructionCounter;
    }
  return instructionCounter + 1;
}
int
ALU (int command, int operand)
{
  switch (command)
    {
    case 0x30:
      {
        int temp;
        if (!sc_memoryGet (operand, &temp))
          {
            return updateAcum (Acum + temp);
          }
        else
          return -1;
      }
      break;
    case 0x31:
      {
        int temp;
        if (!sc_memoryGet (operand, &temp))
          {
            return updateAcum (Acum - temp);
          }
        else
          return -1;
      }
      break;
    case 0x32:
      {
        int temp;
        if (!sc_memoryGet (operand, &temp))
          {
            if (temp == 0)
              {
                sc_regSet (REG_DIVIDEZERO, 1);
                UpdFlags ();
                return -1;
              }
            else
              return updateAcum (Acum / temp);
          }
        else
          return -1;
      }
      break;
    case 0x33:
      {
        int temp;
        if (!sc_memoryGet (operand, &temp))
          {
            return updateAcum (Acum * temp);
          }
        else
          return -1;
      }
      break;
    }
  return 0;
}
void
Initconsole ()
{

  bc_box (1, 1, 10, 59);

  mt_gotoXY (1, 27);
  write (1, "Memory", 6);

  mt_setbgcolor (CONSOLE);
  mt_setfgcolor (textColor);

  bc_box (13, 43, 8, 34);

  mt_gotoXY (13, 55);
  write (1, "Keys", 4);
  mt_gotoXY (14, 45);
  write (1, "L - load", strlen ("L - load"));
  mt_gotoXY (15, 45);
  write (1, "S - save", strlen ("S - save"));
  mt_gotoXY (16, 45);
  write (1, "R - run", strlen ("R - run"));
  mt_gotoXY (17, 45);
  write (1, "T - step", strlen ("T - step"));
  mt_gotoXY (18, 45);
  write (1, "I - reset", strlen ("I - reset"));
  mt_gotoXY (19, 45);
  write (1, "F5 - accumulator", strlen ("F5 - accumulator"));
  mt_gotoXY (20, 45);
  write (1, "F6 - instructionCounter", strlen ("F6 - instructionCounter"));
  bc_box (1, 62, 1, 15);
  bc_box (1 + 3, 62, 1, 15);
  bc_box (1 + 3 + 3, 62, 1, 15);
  bc_box (1 + 3 + 3 + 3, 62, 1, 15);

  mt_gotoXY (1, 66);
  write (1, "accumulator", strlen ("accumulator"));
  mt_gotoXY (4, 63);
  write (1, "instructionCounter", strlen ("instructionCounter"));
  mt_gotoXY (7, 67);
  write (1, "Operation", strlen ("Operation"));
  mt_gotoXY (10, 67);
  write (1, "Flags", strlen ("Flags"));

  mt_setbgcolor (CONSOLE);
  bc_box (13, 1, 8, 40);
  updateAcum (Acum);
  updateBigMemory ();
  updateICounter ();
  for (int i = 0; i < 100; i++)
    updateMemory (i);
  updOp ();
  UpdFlags ();
  mt_gotoXY (23, 1);
}

int tact = 1;

void
step ()
{
  int lastICounter = instructionCounter;
  int iCounter = CU ();
  if (iCounter > 99)
    return;
  instructionCounter = iCounter;
  updateBigMemory ();
  updateMemory (lastICounter);
  updateMemory (instructionCounter);
  updOp (instructionCounter);
  updateICounter ();
  mt_gotoXY (23, 1);
}
void
signalHandler (int sigNum)
{
  if (sigNum == SIGALRM)
    {
      int reg;
      sc_regGet (REG_CLOCKIGNORE, &reg);
      if (!reg)
        return;
      step ();
      if (instructionCounter == 99)
        {
          sc_regSet (REG_CLOCKIGNORE, 0);
          UpdFlags ();
          mt_gotoXY (23, 1);
          return;
        }
      alarm (tact);
    }
  else if (sigNum == SIGUSR1)
    {
      sc_memoryInit ();
      sc_regInit ();
      instructionCounter = 0;
      for (int i = 0; i < 100; i++)
        updateMemory (i);
      updateBigMemory ();
      updateAcum (0);
      UpdFlags ();
      updateICounter ();

      updOp ();
    }

  else if (sigNum == SIGINT)
    {
      int reg;
      sc_regGet (REG_CLOCKIGNORE, &reg);
      UpdFlags ();
      if (reg)
        {
          sc_regSet (REG_CLOCKIGNORE, 0);
          UpdFlags ();
          alarm (0);
          mt_gotoXY (23, 1);
          outputClear ();
          return;
        }
      else
        {
          rk_mytermrestore ();
          mt_gotoXY (24, 1);
          exit (0);
        }
    }
}
int
main (void)
{
  int r, c;
  int err;
  err = mt_getscreensize (&r, &c);
  if (err == -1)
    {
      fprintf (stderr, "Pls terminal\n");
    }

  if (r < 24 || c < 80)
    {
      printf ("No print\n");
      return 1;
    }
  mt_clrscr ();
  signal (SIGALRM, signalHandler);
  signal (SIGUSR1, signalHandler);
  signal (SIGINT, signalHandler);
  sc_memoryInit ();

  Initconsole ();

  // mt_gotoXY(23, 1);
  enum keys k;
  int registr;
  while (1)
    {
      sc_regGet (REG_CLOCKIGNORE, &registr);
      // UpdFlags ();
      if (registr)
        continue;
      rk_readkey (&k);
      if (k == KEY_DOWN)
        {
          if (selectedCell > 99)
            continue;
          int prevCounter = selectedCell;

          if (selectedCell + 10 > 99)
            selectedCell -= 90;
          else
            selectedCell += 10;

          updateMemory (prevCounter);
          updateMemory (selectedCell);
          updateICounter ();
        }

      else if (k == KEY_UP)
        {

          if (selectedCell > 99)
            continue;
          int prevCounter = selectedCell;

          if (selectedCell - 10 < 0)
            selectedCell += 90;
          else
            selectedCell -= 10;
          updateMemory (prevCounter);
          updateMemory (selectedCell);
          updateICounter ();
        }
      else if (k == KEY_LEFT)
        {
          int prevCounter = selectedCell;
          if (selectedCell > 99)
            {
              selectedCell--;
              UpdFlags ();
              if (selectedCell < 100)
                updateMemory (selectedCell);
            }
          else
            {
              if ((selectedCell % 10) - 1 < 0)
                selectedCell += 9;
              else
                selectedCell -= 1;
              updateMemory (prevCounter);
              updateMemory (selectedCell);
              updateICounter ();
            }
        }
      else if (k == KEY_RIGHT)
        {
          int prevCounter = selectedCell;

          if ((selectedCell % 10) + 1 > 9)
            selectedCell -= 9;
          else
            selectedCell += 1;
          updateMemory (prevCounter);
          updateMemory (selectedCell);
          updateICounter ();
        }

      else if (k == KEY_L)
        {
          char temp[50];
          outputWrite ("[LOAD FILE] INPUT FILE NAME: ");
          scanf ("%s", temp);
          while (getchar () != '\n')
            ;
          if (!sc_memoryLoad (temp))
            {
              instructionCounter = 0;
              sc_regInit ();
              mt_clrscr ();
              for (int i = 0; i < 100; i++)
                updateMemory (i);
              updOp ();
              updateICounter ();
              UpdFlags ();
              updateAcum (0);
              updateBigMemory ();
            }

          Initconsole ();
        }
      else if (k == KEY_S)
        {
          char temp[50];
          outputWrite ("[SAVE FILE] INPUT FILE NAME: ");
          scanf ("%s", temp);
          while (getchar () != '\n')
            ;
          sc_memorySave (temp);
        }
      else if (k == KEY_F5)
        {
          outputWrite ("[Accum] INPUT VALUE: ");
          int X;
          scanf ("%x", &X);
          while (getchar () != '\n')
            ;
          outputClear ();
          updateAcum (X);
        }
      else if (k == KEY_F6)
        {
          int temp;
          outputWrite ("[INSTRUCTION COUNTER] INPUT VALUE: ");
          scanf ("%d", &temp);
          while (getchar () != '\n')
            ;
          outputClear ();
          if (temp < 0 || temp > 99)
            {
              sc_regSet (REG_MEMOUTSIDE, 1);
              UpdFlags ();
              continue;
            }
          int prevICounter = instructionCounter;
          instructionCounter = temp;
          updateMemory (prevICounter);
          updateMemory (instructionCounter);
          updateBigMemory ();
          updateICounter ();
          updOp ();
        }
      else if (k == KEY_ENTER)
        {

          int value;
          outputWrite ("[CHANGE VALUE] INPUT Value : ");
          scanf ("%x", &value);
          while (getchar () != '\n')
            ;
          outputClear ();
          sc_memorySet (selectedCell, value);
          updateMemory (selectedCell);
          if (selectedCell == instructionCounter)
            updateBigMemory ();

          mt_clrscr ();
          Initconsole ();
        }
      else if (k == KEY_I)
        {
          raise (SIGUSR1);
        }
      else if (k == KEY_R)
        {

          sc_regSet (REG_CLOCKIGNORE, 1);
          alarm (tact);
          UpdFlags ();
        }
      else if (k == KEY_T)
        {
          step ();
        }
      mt_gotoXY (23, 1);
    }

  return 0;
}
