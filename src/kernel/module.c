#include "module.h"

void m_InitModuleManager(){
  // Initlize Filesystem
  initFS();
}

void m_LoadBasicModule(char* modPath, char* symPath){

  CD_DirectoryEntry* symbolFile = getFile(symPath);
  CD_DirectoryEntry* module = getFile(modPath);

  // Now we actually have to parse it...
  // uhghhghgh

  uint8_t symbolBuffer[symbolFile->sizeOfExtent];
  readFile(symPath, &symbolBuffer);

  uint8_t moduleDataBuffer[module->sizeOfExtent];
  readFile(modPath, &moduleDataBuffer);


  for(int i = 0; i < symbolFile->sizeOfExtent; i){
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
    char name[16];
    char numBuf[16];

    for(int l = 0; l < READLINEQUIT; l++){
      if(symbolBuffer[l] == ' '){
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
      else if(symbolBuffer[l] == '\n'){
        break;
      }else{
        switch(count){
          bufC++;
          case 0:
          case 1:
            numBuf[bufC] = symbolBuffer[l];
            break;
          case 2:
            name[bufC] = symbolBuffer[l];
            break;
          default:
            break;
        }
      }
      i++;
    }
    // Create function from that

  }




  /*m_baseModules[m_baseModCount++] = {
    
  }*/
}