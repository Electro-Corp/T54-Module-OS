#include "module.h"

void m_InitModuleManager(){
  // Initlize Filesystem
  initFS();
}

void m_LoadBasicModule(char* modName, char* modPath, char* symPath){
  CD_DirectoryEntry* symbolFile = getFile(symPath);

  Module_B module;
  strcpy(module.name, modName);
  strcpy(module.path, symPath);
  int functionsInMod = 0;

  uint32_t sizeOfSymBuf = symbolFile->sizeOfExtent;
  uint16_t symbolBuffer[2049];

  if(readFileFromEntry(symbolFile, &symbolBuffer) == -1){
    kprintf("Reading SYM failed.");
  }

  // Load Module into memory
  CD_DirectoryEntry* modFile = getFile(modPath);
  if(!modFile) kprintf("Module Data File not found");
  uint16_t moduleTotalSize = modFile->sizeOfExtent;
  uint16_t moduleData[5000];
  readFileFromEntry(modFile, &moduleData);

  module.rawData = &moduleData;


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

  for(int l = 0; l < sizeOfSymBuf; l++){
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
      uint16_t funcDataRaw[size];
      for(int g = 0; g < size; g++){
        funcDataRaw[g] = moduleData[addr + g];
      }
      //memcpy(funcDataRaw, moduleData[addr], size);
      functionTmp.funcData = &funcDataRaw;
      functionTmp.call = (void (*)())&funcDataRaw;
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

void m_RunFunctionFromModule(char* module, char* funcName){
  for(int i = 0; i < m_baseModCount; i++){
    Module_B mod = m_baseModules[i];
    if(strcmp(mod.name, module) == 0){
      for(int x = 0; x < mod.functionCount; x++){
        Function_B func = mod.functions[x];
        if(strcmp(func.name, funcName) == 0){
          func.call();
        }
      }
    }
  }
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