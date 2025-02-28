/*
  Kernel Entrypoint
*/
#include "cd.h"

#include "vga.h"

int kmain(){
  // Just for fun, the main design idea of this OS is that everything that can be a 
  // kernel module is a kernel module. However, certain things HAVE to be built into the kernel 
  // in order for modules to be loaded. These are:
  // > cd.c
  //   > Required to read modules from the CD-DRIVE
  // > fs.c
  //   > Required to read modules from the ISO-9660 FS
  // > module.c
  //  > Actually loads in the modules

  initTerminal();
  
  m_InitModuleManager();
  
  m_LoadBasicModule("/KMODS/BASE/VGA.KMOD", "/KMODS/BASE/VGA.SYM");

  m_PrintAllModuleData();
  
  asm("hlt");
}