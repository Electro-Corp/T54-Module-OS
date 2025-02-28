#include "module.h"

void m_InitModuleManager(){
  // Initlize Filesystem
  initFS();
}

void m_LoadBasicModule(char* modPath, char* symPath){
  //kprintf("===== LOAD SYM PATH =====");
  //kprintf(symPath);

  CD_DirectoryEntry* symbolFile = getFile(symPath);

  Module_B module;
  strcpy(module.name, modPath);
  strcpy(module.path, symPath);
  int functionsInMod = 0;

  uint32_t sizeOfSymBuf = symbolFile->sizeOfExtent;
  uint16_t symbolBuffer[2049];

  //char wo[3];
  //itoa(sizeOfSymBuf, 10, wo);
  //kprintf(wo);

  if(readFileFromEntry(symbolFile, &symbolBuffer) == -1){
    kprintf("Reading SYM failed.");
  }

  int tmp = 0;
  while(symbolBuffer[tmp++]){}

  //itoa(tmp, 10, wo);
  //kprintf(wo);


  char fileData[sizeOfSymBuf];
  int symBufInt = 0;
  for(int i = 0; i < sizeOfSymBuf - 1; i+=2){
    fileData[i] = symbolBuffer[symBufInt] & 0xFF;
    fileData[i + 1] = symbolBuffer[symBufInt++] >> 8;
  }

  // Parse the line
  /*
    Count vals:
    0: addr
    1: size
    2: name
  */
  int count = 0;
  int addr = 0;
  int size = 0;

  int bufC = 0;
  char name[24];
  char numBuf[24];

  Function_B functionTmp = {};

  for(int l = 0; l < symbolFile->sizeOfExtent; l++){
    if((char)fileData[l] == ' '){
      bufC = 0;
      switch(count){
        case 0:
          addr = charToInt(numBuf);
          break;
        case 1:
          size = charToInt(numBuf);
          break;
        case 2:
          // Lamo
          break;
        default:
          break;
      }
      count++;
    }
    else if((char)fileData[l] == '.'){
      strncpy(functionTmp.name, name , bufC);
      functionTmp.addr = addr;
      functionTmp.size = size;
      // Create function from that
      module.functions[functionsInMod++] = functionTmp;
      // Reset everything
      count = 0;
      addr = 0; 
      size = 0;
      bufC = 0;
      strclr(name);
      strclr(numBuf);
      strclr(functionTmp.name);
      kprintf("Finished parsing 1 function.");
    }else{
      switch(count){
        case 0:
        case 1:
          numBuf[bufC++] = (char)fileData[l];
          break;
        case 2:
          name[bufC++] = (char)fileData[l];
          // We're done, move on!
          break;
        default:

          break;
      }
    }
      
    
  }

  module.functionCount = functionsInMod;
  
  m_baseModules[m_baseModCount++] = module;
}

void m_PrintAllModuleData(){
  kprintf("==== MODULE LISTING ====");
  if(m_baseModCount == 0){
    kprintf("No modules loaded.");
  }else{
    for(int i = 0; i < m_baseModCount; i++){
      Module_B mod = m_baseModules[i];
      kprintf(mod.name);
      kprintf("Functions:");
      for(int x = 0; x < mod.functionCount; x++){
        kprintf(mod.functions[x].name);
      }
    }
  }
}