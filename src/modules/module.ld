ENTRY(_start)

SECTIONS {
  . = 0x10000; /* Set the start address of the binary */
  
  .text : {
    *(.text)  /* Include all .text sections (code) */
  }
  
  .data : {
    *(.data)  /* This is optional. If no data, it won’t matter */
  }
  
  .bss : {
    *(.bss)   /* This is optional. If no uninitialized data, it won’t matter */
  }
  
  /* Remove any other sections to keep things minimal */
}
