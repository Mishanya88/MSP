#ifndef mySimpleComputer
#define mySimpleComputer
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define MEMORYSIZE 100
#define REG_MEMOUTSIDE 0x0
#define REG_UNKNOWNCOMMAND 0x1
#define REG_DIVIDEZERO 0x2
#define REG_OVERFLOW 0x3
#define REG_CLOCKIGNORE 0x4
#define REG_MAX 0x4
extern unsigned short int memory[MEMORYSIZE];
extern unsigned short int regs;
int sc_memoryInit ();
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regSet (int reg, int value);
int sc_regGet (int reg, int *value);
int sc_regInit ();
int sc_commandEncode (int command, int operand, int *value);
int sc_commandDecode (int value, int *command, int *operand);
#endif
