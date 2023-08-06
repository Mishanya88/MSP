#include <mySimpleComputer.h>
unsigned short int memory[MEMORYSIZE];
unsigned short int regs;
int
sc_memoryInit ()
{
  for (int i = 0; i < MEMORYSIZE; i++)
    {
      memory[i] = 0;
    }
  return 0;
}

int
sc_memorySet (int address, int value)
{
  if (address < 0 || address > 99)
    {
      sc_regSet (REG_MEMOUTSIDE, 1);
      return -1;
    }
  if (value > 0x7FFF)
    {
      sc_regSet (REG_OVERFLOW, 1);
      return -1;
    }
  memory[address] = value;
  return 0;
}
int
sc_memoryGet (int address, int *value)
{
  if (address < 0 || address > 99)
    {

      sc_regSet (REG_MEMOUTSIDE, 1);
      return -1;
    }

  *value = memory[address];
  return 0;
}

int
sc_memorySave (char *filename)
{

  int file = creat (filename, 0664);
  write (file, memory, 100 * sizeof (short int));
  close (file);
  return 0;
}

int
sc_memoryLoad (char *filename)
{

  int file = open (filename, O_RDONLY);

  if (file == -1)
    return -1;
  read (file, memory, 100 * sizeof (short int));
  close (file);

  return 0;
}
int
sc_regInit ()
{
  regs = 0;
  return 0;
}
int
sc_regSet (int reg, int value)
{
  if (reg < 0 || reg > REG_MAX || value < 0 || value > 1)
    {
      return -1;
    }
  if (value == 1)
    regs |= (1 << reg);
  else if (value == 0)
    regs &= (~(1 << reg));
  return 0;
}
int
sc_regGet (int reg, int *value)
{

  if (reg < 0 || reg > REG_MAX)
    {
      // printf ("NO:");
      return 1;
    }
  *value = (regs >> reg) & 0x1;
  // printf("%d\n", regs >> (reg - 1)& 0x1);
  return 0;
}
int
sc_commandEncode (int command, int operand, int *value)
{
  if (command < 0 || command > 0x7F || operand < 0 || operand > 0x7F)
    {
      return -1;
    }
  *value = operand;
  *value |= command << 7;
  return 0;
}
int
sc_commandDecode (int value, int *command, int *operand)
{
  if (value > 0x7FFF)
    {
      sc_regSet (REG_UNKNOWNCOMMAND, 1);
      return -1;
    }
  value = abs (value);
  *command = value >> 7;
  *operand = value & 0x7F;

  return 0;
}
