#ifndef ResourceManager_H
#define ResourceManager_H

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include <SDL2/SDL.h>
#include <CaGE/RenderObject.h>
#include <CaGE/jsonxx/json.hpp>

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

#define RES_BUTTON  0x01
#define RES_PLAIN   0x0f


//  This structure will be moved to Global.h
struct Resource
{
    RenderObject *content;     //  SDL_RWops file object
    std::string name;       //  id [internal name]
    Uint32 type;       //  type of the resource
};

class ResourceManager
{
    private:
        jsonxx::json resource;
        SDL_Renderer *renderer;
    public:
        std::map<std::string, Resource> res_dict;
        ResourceManager(const std::string &filename, SDL_Renderer* r);
        ~ResourceManager();

        void Load(const std::string &filename);
        void Clear();
        RenderObject* GetResource(const std::string &type, const std::string &name);


};

#endif