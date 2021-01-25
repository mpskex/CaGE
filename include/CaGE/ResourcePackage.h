#ifndef ResourcePackage_H
#define ResourcePackage_H

#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <cstdlib>


#define NAME_LEN    256
#define TYPE_LEN    16

using namespace std;

typedef unsigned char BYTE;

/*  
    This part is to define how the file storage in an
    rpk file. All resource file have a head, which describe
    its name, type and size. Then following is the real
    content of the resource file.
*/
typedef struct BinContent
{
    //  Head of the Binary file
    char name[NAME_LEN];
    char type[TYPE_LEN];
    //  size of real content
    Sint64 size;
    //  ptr to the content
    SDL_RWops *content;
} BIN;

struct ResourcePackHeader
{
    BYTE MAGIC_DESC[2];     //  File Descriptor 'MP'
    BYTE PACK_NAME[16];     //  Package Name within length of 16
    BYTE CHECKSUM[32];      //  SHA-256 checksum
    BYTE REBUNDANT[64];     //  For future use
    BYTE NEXT_PTR[4];       //  uint32 ptr
};

struct ResourcePackNode
{
    BYTE NAME[16];      //  File name 
    BYTE CRYPT[2];      //  Crypto method 1 byte for method | 1 byte for crypto-bits descriptor
    BYTE TYPE[2];       //  Type Descriptor
    BYTE RAW_PTR[4];    //  Pointer to Content data
};

typedef ResourcePackHeader PACKHEADER;
typedef ResourcePackNode PACKNODE;

#endif