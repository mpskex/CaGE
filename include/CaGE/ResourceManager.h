#ifndef ResourceManager_H
#define ResourceManager_H

#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>

#include <SDL2/SDL.h>
#include <CaGE/jsonxx/json.hpp>

#include "RenderObject.h"
#include "EventManager.h"

/*

ResourceManager Manager
Copyright by mpsk @ 2018

This Module is to manage the json that the platform need to load
and map its external name to an internal name.

ResourceManager Map Script has the format of
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
    RenderObject *content;      //  SDL_RWops file object
    std::string name;           //  id [internal name]
    Uint32 type;                //  type of the json
    Uint32 eventId = 0;             //  0 for no event bounded
};

class ResourceManager
{
    private:
        SDL_Renderer *renderer;
        Uint32 event_id_count;
        EventManager *event_manager;
    public:
        std::map<std::string, Resource> res_dict;
        ResourceManager(SDL_Renderer* r);
        void linkEventManager(EventManager *e);
        void load(const std::string &filename);
        ~ResourceManager();

        Uint32 renderAll();
        RenderObject* getResource(const std::string &type, const std::string &name);
        std::string getEventName(const std::string &type, const Uint32& eventId);



};

#endif