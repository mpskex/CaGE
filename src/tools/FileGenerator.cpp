/*****************************
#	文件名：	FileGenerator.cpp 
#	日期：		2017-09-01
#	版本号：	0.0.01
#	功能：		文件生成程序
#	mpsk's game engine proj
*****************************/

#include <SDL2/SDL.h>
#include "CaGE/ResourcePackage.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#define NAME_LEN    256
#define TYPE_LEN    16

using namespace std;

void Usage(char *name)
{
    cout << name << "'s Usage:" <<endl;
    cout << "\t-i:\tfor image attribute" << endl;
    cout << "\t-s:\tfor image attribute" << endl;
}

//  ---------------------------------------------
//  This function returns the increase of the ptr
//  ---------------------------------------------
Uint64 WriteBin(BIN block, SDL_RWops *dst)
{
    //  measure the length of the writing binary
    if(block.content != NULL)
    {
        Sint64 length = SDL_RWsize(block.content);
        block.size = length;
        cout << "\tFind file with " << block.size << " bytes" << endl;
    }
    else
    {
        cout << "\n[Error]\tCan't access to file!\n" << endl;
        return -1;
    }

    if(dst != NULL) 
    {
        //  write name
        {
            Sint16 len = SDL_strlen(block.name);
            Sint16 b = SDL_RWwrite(dst, block.name, 1, NAME_LEN);
            if (b < len) {
                printf("\tCouldn't fully write string\n");
            } else 
            {
                printf("\tWrote %d 1-byte blocks\n", b);
            }
        }
        //  write type
        {
            Sint16 len = SDL_strlen(block.type);
            Sint16 b = SDL_RWwrite(dst, block.type, 1, TYPE_LEN);
            if (b < len) {
                printf("\tCouldn't fully write string\n");
            } else 
            {
                printf("\tWrote %d 1-byte blocks\n", b);
            }
        }
        //  write size
        {
            Sint16 len = sizeof(Sint64);
            Sint16 b = SDL_RWwrite(dst, block.type, 1, sizeof(Sint64));
            if (b < len) {
                printf("\tCouldn't fully write string\n");
            } else 
            {
                printf("\tWrote %d 1-byte blocks\n", b);
            }
        }
        //  write content
        {
            char *res = (char*)malloc(block.size + 1);
            Sint64 nb_read_total = 0, nb_read = 1;
            char *buf = res;
            while (nb_read_total < block.size && nb_read != 0) 
            {
                nb_read = SDL_RWread(block.content, buf, 1, (block.size - nb_read_total));
                nb_read_total += nb_read;
                buf += nb_read;
            }
            if (nb_read_total != block.size) 
            {
                cout << "\t[Error]\tCan't read complete file!" << endl;
                cout << "\t\tTotal read byte is:\t" << nb_read_total << endl;
                cout << "\t\tRead byte is:\t\t" << nb_read << endl;
                cout << "\t\tBlock size is:\t\t" << block.size << endl;
                free(res);
                return -1;
            }
            Sint64 b = SDL_RWwrite(dst, res, 1, block.size);
            if (b < block.size) {
                printf("\tCouldn't fully write string\n");
            } else 
            {
                printf("\tWrote %lld 1-byte blocks\n", b);
            }
        }
    }
    else
    {
        cout << "\n[Error]\tDestination file is unreadable!\n" << endl;
    }
    return NAME_LEN + TYPE_LEN + sizeof(Sint64) + Uint64(block.size);
}

int main(int argc, char **argv)
{
    SDL_RWops *dst;
    //  destination path
    char dst_path[NAME_LEN];
    //  file position counter
    Uint64 ptr = 0;

    if(argc<2)
    {
        cout << "\n[Error]\tNo enough parameters to execute!\n" << endl;
        Usage(argv[0]);
        return -1;
    }
    else
    {
        for(int i=1;i<=argc-2;i+=2)
        {
            if(strcmp(argv[i],"-o")==0)
            {
                //  set the output file
                strcpy(dst_path, argv[i+1]);
                dst = SDL_RWFromFile(dst_path, "w");
                cout << "[Info]\tDestination Path is: " << dst_path << endl;


                SDL_RWops *dst = SDL_RWFromFile(dst_path, "w");
            }
            else if(strcmp(argv[i], "-i")==0)
            {
                BIN block;
                //  get the name of file
                //  this will be finally define in the binary file
                //  when using a fileop, you can just call it name 
                //  to use this json
                char imagefile[NAME_LEN];
                char imagename[NAME_LEN];
                strcpy(imagefile, argv[i+1]);
                strcpy(imagename, strtok(imagefile, "."));
                
                //  read the content
                SDL_RWops *temp = SDL_RWFromFile(argv[i+1], "rb");
                if(temp == NULL)
                {
                    cout << "\n[Error]\tFailed to open file " << argv[i+1] << "!\n" << endl;
                    return -1;
                }
                //  set block attribute
                strcpy(block.name, imagename);
                strcpy(block.type, "image");
                block.content = temp;
                cout << "[Info]\tAdd Image File: " << argv[i+1] << endl;
                
                Sint64 incr = 0;
                if((incr = WriteBin(block, dst)) == -1)
                {
                    cout << "\n[Error]\tFailed to write file!\n" << endl;
                    return -1;
                }
                else
                {
                    cout << "[Info]\tWrirtten " << incr << " bytes block!" << endl;
                    ptr += Uint64(incr);
                }
            }
            else if(strcmp(argv[i], "-s")==0)
            {
                BIN block;
                //  get the name of file
                //  this will be finally define in the binary file
                //  when using a fileop, you can just call it name 
                //  to use this json
                char scriptfile[NAME_LEN];
                char scriptname[NAME_LEN];
                strcpy(scriptfile, argv[i+1]);
                strcpy(scriptname, strtok(scriptfile, "."));

                //  read the content
                SDL_RWops *temp = SDL_RWFromFile(argv[i+1], "rb");

                if(temp == NULL)
                {
                    cout << "\n[Error]\tFailed to open file " << argv[i+1] << "!\n" << endl;
                    return -1;
                }

                strcpy(block.name, scriptname);
                strcpy(block.type, "script");
                block.content = temp;
                cout << "[Info]\tAdd script File: " << argv[i+1] << endl;

                Sint64 incr = 0;
                if((incr = WriteBin(block, dst)) == -1)
                {
                    cout << "\n[Error]\tFailed to write file!\n" << endl;
                    return -1;
                }
                else
                {
                    cout << "[Info]\tWrirtten " << incr << " bytes block!" << endl;
                    ptr += Uint64(incr);
                }
            }
            else
            {
                cout << "\n[Error]\tUnacceptable parameter to execute!\n" << endl;
                Usage(argv[0]);
                return -1;
            }
        }
        cout << "\n[Finished]\tFile finished writing with size " << ptr << " bytes\n" << endl;
        if(dst != NULL)
            SDL_RWclose(dst);
    }
    return 0;
}