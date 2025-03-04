//#include "M_Vga.h"

__attribute__((section(".text"))) void moduleInit(){
  // Do something]
  // outb(0x3f8, 'A');
  //static char* const fb = (char*)(0xb8000);
  char* fb = (char*)0xB8000;
  fb[(2 * 0 + 160 * 0)] = 'A';
  fb[1] = 0x7;
  return;
}

// void outb(unsigned short _port, unsigned char _data)
// {
//   __asm__ __volatile__("outb %1, %0" : : "dN" (_port), "a" (_data));
// }

// void charAt(char c, int x, int y, unsigned char color){
//   // Awesome
// }

// void clearScreen(){

// }

// void _start(){

// }