#ifndef ResourceManager_H
#define ResourceManager_H

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include <SDL2/SDL.h>

/*

Resource Manager
Copyright by mpsk @ 2018

This Module is to manage the resource that the platform need to load
and map its external name to an internal name.

Resource Map Script has the format of
<name>\t<type>\t<path>

every scene (with different resources) has their unique id (0-31)
and when 

TODO:
    *   external name will be replace with ResourcePack Offset in ther future
*/

#define NAME_BUFF   255


//  This structure will be moved to Global.h
typedef struct Resource
{
    SDL_RWops *content;     //  SDL_RWops file object
    std::string name;       //  id [internal name]
    std::string type;       //  type of the resource
    //Uint32  mask;           // mask for scene load
}RESUNIT;

class ResourceManager
{
    private:
        std::vector<RESUNIT> *res_list;
        std::vector<RESUNIT>::iterator iter;
        std::ifstream res_script;

    public:
        ResourceManager(const std::string &filename);
        ~ResourceManager();

        void Load(const std::string &filename);
        void Clear();
        SDL_RWops* GetResource(const std::string &type, const std::string &name);

        Uint32 flag;        //  This flag is a bitwise mask flag.
        Uint8 id;           //  This id is the bitwise used to do the masking

};

#endif