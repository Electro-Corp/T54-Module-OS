/*
    Filesystem handler
*/
#ifndef FS_H
#define FS_H
#include "cd.h"

#define MAX_READ_DIRECTORY 512

typedef struct {
    // Volume ID
    char CD_volID[32];

} CD_FS;


typedef struct {
    char fileID[512];
    uint32_t locOfExtent;
    uint32_t sizeOfExtent;

    int isDirectory;
} CD_DirectoryEntry;

// FS's
static CD_FS rootMedia;



void initFS();

void initCDFS();

int readFile(char* filePath, uint16_t* buffer);

int readFileFromEntry(CD_DirectoryEntry* entry, uint16_t* buffer);

CD_DirectoryEntry* getFile(char* filePath);

int getNumOfDirs();

CD_DirectoryEntry* getDirs();

#endif