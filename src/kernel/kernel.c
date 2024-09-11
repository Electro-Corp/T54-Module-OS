/*
  Kernel Entrypoint
*/
#include "cd.h"
#include "module.h"

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

  uint8_t pvd[2048];
  int c = read_cdrom(0x1F0, 0, 16, 1, &pvd);
  
  //m_InitModuleManager();
  
  //m_LoadModule("/modules/VGA/M_Vga.kmod");
  
  asm("hlt");
}