#ifndef IO_H
#define IO_H
// read from port
unsigned char inb(unsigned short _port)
{
  unsigned char rv;
  __asm__ __volatile__("inb %1, %0" : "=a" (rv) : "dN" (_port));
  return rv;
}
// write to port
void outb(unsigned short _port, unsigned char _data)
{
  __asm__ __volatile__("outb %1, %0" : : "dN" (_port), "a" (_data));
}
#endif