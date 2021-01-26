#include "CaGE/ResourceManager.h"

#include <CaGE/Button.h>

void ResourceManager::load(const std::string &filename)
{
    jsonxx::json json;
    std::ifstream ifs(filename);
    ifs >> json;
    for (auto iter = json.begin(); iter != json.end(); iter++) {
        if(iter.key()=="buttons"){
            auto buttons = json["buttons"];
            for(auto biter = buttons.begin();biter!=buttons.end();biter++){
                // parse the configuration
                const std::string path = buttons[biter.key()]["path"].as_string();
                std::map<std::string, jsonxx::json> pos = buttons[biter.key()]["pos"];
                std::map<std::string, jsonxx::json> size = buttons[biter.key()]["size"];

                // create the object
                auto button = new Button(pos["x"],
                                         pos["y"],
                                         size["w"],
                                         size["h"],
                                         SDL_RWFromFile(path.c_str(), "rb"),
                                         this->renderer);
                button->setEventId(++this->event_id_count);

                // create json object
                Resource button_res;
                button_res.content = button;
                button_res.name = biter.key();
                button_res.type = RES_BUTTON;
                button_res.eventId = this->event_id_count;
                std::cout << "Button Added " << biter.key() << " : " << this->event_id_count <<std::endl;
                // Add to the json dictionary
                this->res_dict[biter.key()] = button_res;

                // Register hooks
                if(this->event_manager!=nullptr){
                    this->event_manager->registerHook(button);
                }
            }
        } else if (iter.key() == "plains") {
            auto plains = json["plains"];
            for(auto piter = plains.begin();piter!=plains.end();piter++) {
                const std::string path = plains[piter.key()]["path"].as_string();
                auto plain = new RenderObject(SDL_RWFromFile(path.c_str(), "rb"),
                                              this->renderer);

                Resource plain_res;
                plain_res.content = plain;
                plain_res.name = piter.key();
                plain_res.type = RES_PLAIN;
                this->res_dict[piter.key()] = plain_res;
            }
        }
    }
}


ResourceManager::ResourceManager(SDL_Renderer *r)
{
    this->renderer = r;
    this->event_id_count = 0;
    this->event_manager = nullptr;
}



ResourceManager::~ResourceManager(){
    //TODO: deconstruct all resources
}



RenderObject* ResourceManager::getResource(const std::string &type, const std::string &name)
{
    for(const auto& r: this->res_dict){
        if(r.first == type){
            if(r.second.name == name){
                return r.second.content;
            }
        }
    }
    return nullptr;
}

std::string ResourceManager::getEventName(const string &type, const Uint32& eventId) {
    if(eventId != 0){
        for(const auto& r: this->res_dict){
            if(r.first == type){
                if(r.second.eventId == eventId){
                    return r.second.name;
                }
            }
        }
    } else {
        return "";
    }
    return EMPTY_EVENT;
}

void ResourceManager::linkEventManager(EventManager *e) {
    this->event_manager = e;
}

Uint32 ResourceManager::renderAll() {
    Uint32 ret = EMPTY_EVENT;
    if(this->event_manager!= nullptr){
        ret = this->event_manager->pollEvent();
    }
    for(auto a: this->res_dict){
        a.second.content->render();
    }
    return ret;
}
