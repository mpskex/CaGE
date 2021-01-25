#include "CaGE/Resource.h"

#include <CaGE/Button.h>

void ResourceManager::Load(const std::string &filename)
{
    for (auto iter = this->resource.begin(); iter != this->resource.end(); iter++) {
        if(iter.key()=="buttons"){
            auto buttons = this->resource["buttons"];
            for(auto biter = buttons.begin();biter!=buttons.end();biter++){
                const std::string path = buttons[biter.key()]["path"].as_string();
                std::map<std::string, jsonxx::json> pos = buttons[biter.key()]["pos"];
                std::map<std::string, jsonxx::json> size = buttons[biter.key()]["size"];
                auto button = new Button(pos["x"],
                                         pos["y"],
                                         size["w"],
                                         size["h"],
                                         SDL_RWFromFile(path.c_str(), "rb"),
                                         this->renderer);
                                         
                Resource button_res;
                button_res.content = button;
                button_res.name = biter.key();
                button_res.type = RES_BUTTON;
                this->res_dict[biter.key()] = button_res;
            }
        } else if (iter.key() == "plains") {
            auto plains = this->resource["plains"];
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


ResourceManager::ResourceManager(const std::string &filename,
                                 SDL_Renderer *r)
{
    std::ifstream ifs(filename);
    ifs >> this->resource;
    this->renderer = r;
    this->Load(filename);
}

ResourceManager::~ResourceManager()
{

}

RenderObject* ResourceManager::GetResource(const std::string &type, const std::string &name)
{
    for(auto iter = this->resource.begin(); iter != this->resource.end(); iter++){
        if(iter.key()==type){
            auto res_list = this->resource[type];
            for (auto iter = res_list.begin(); iter != res_list.end(); iter++) {
                if(iter.key()==name){
                    return nullptr;
                }
                std::cout << iter.key() << ":" << (*iter) << std::endl;
            }
        }
    }
    return nullptr;
}