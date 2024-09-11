/*
  Most important part of the OS honestly
*/
#ifndef MODULE_H
#define MODULE_H

#include "cd.h"
#include "fs.h"

/*
  These files are extremly simple

  They contain functions and thats it lamo
*/

// Base modules, all chars inside are fixed length
// since the Memory Managment System is a module 
typedef struct {
  char name[16];
  char path[16];
  char functions[16][16];
} Module_B;

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
void m_LoadModule(char* path);

/*
  Does this function exist?
*/
int m_DoesFunctionExist(char* moduleName, char* functionName);

#endif