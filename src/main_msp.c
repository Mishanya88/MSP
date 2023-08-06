#include <mySimpleComputer.h>
#include <stdio.h>
#include <time.h>

int
main (void)
{
  sc_memoryInit ();
  int value = 0;

  printf ("Error = %d\n", sc_memorySet (101, 50));
  printf ("yes = %d\n\n", sc_memorySet (10, 10));
  sc_memorySet (1, 5);
  sc_memorySet (2, 4);
  sc_memorySet (3, 3);
  sc_memorySet (4, 7);
  sc_memorySet (5, 1);

  for (int i = 1; i < 6; i++)
    {
      sc_memoryGet (i, &value);
      printf ("%d\n", value);
    }
  /*
   */
  // sc_memorySet(4,3);
  sc_memorySet (5, 100);
  sc_memorySave ("test.bin");
  sc_memorySet (5, 30);
  sc_memoryLoad ("test.bin");
  printf ("Чтение файла\n");
  for (int i = 0; i < 5; i++)
    {
      sc_memoryGet (i + 1, &value);
      printf ("%d\n", value);
    }
  sc_regInit ();
  int vl = 1;
  // sc_regSet(REG_CLOCKIGNORE, 1);
  // sc_regGet (REG_MEMOUTSIDE, &vl);
  // printf ("%d\n", vl);
  sc_regGet (3, &vl);
  printf ("%d\n", vl);
  int f = 0, f_c = 0, f_o = 0;
  sc_commandEncode (0x33, 0x59, &f);
  printf ("Закодированная команда: %d\n", f);
  sc_commandDecode (f, &f_c, &f_o);
  printf ("Команда: %d\nоперанд: %d\n", f_c, f_o);
  return 0;
}
