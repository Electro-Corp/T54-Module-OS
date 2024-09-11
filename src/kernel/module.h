/*
  Most important part of the OS honestly
*/
#ifndef MODULE_H
#define MODULE_H

#include "cd.h"
#include "fs.h"

#include "stdlib.h"

#define READLINEQUIT 256

/*
  These files are extremly simple

  They contain functions and thats it lamo
*/

typedef struct {
  char name[16];
  uint32_t* addr;
} Function_B;

// Base modules, all chars inside are fixed length
// since the Memory Managment System is a module 
typedef struct {
  char name[16];
  char path[16];
  char Function_B[16];
  CD_DirectoryEntry* entry;
} Module_B;

int m_baseModCount = 0;
Module_B* m_baseModules[16];


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

#endif