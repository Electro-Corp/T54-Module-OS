/*
  Most important part of the OS honestly
*/
#ifndef MODULE_H
#define MODULE_H

#include "cd.h"
#include "fs.h"

#include "stdlib.h"
#include "string.h"

#define READLINEQUIT 256

/*
  These files are extremly simple

  They contain functions and thats it lamo
*/

typedef struct {
  char name[16];
  uint32_t* addr;
  uint32_t* size;
} Function_B;

// Base modules, all chars inside are fixed length
// since the Memory Managment System is a module 
typedef struct {
  char name[32];
  char path[32];
  Function_B functions[16];
  int functionCount;
  CD_DirectoryEntry* entry;
} Module_B;

int m_baseModCount = 0;
Module_B m_baseModules[16];


// Normal Module
typedef struct {
  char* name;
  char* path;
  char** functions;
} Module_N;

/*
  Initilize Module Manager
*/
void m_InitModuleManager();

/*
  Load a module
*/
void m_LoadBasicModule(char* modPath, char* symPath);

/*
  Does this function exist?
*/
int m_DoesFunctionExist(char* moduleName, char* functionName);


/*
  Debug print all modules and functions
*/
void m_PrintAllModuleData();

#endif