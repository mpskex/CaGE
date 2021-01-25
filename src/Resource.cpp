#include "CaGE/Resource.h"

void SplitString(const std::string &s, std::vector<std::string> &v, const std::string &c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while (std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2 - pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if (pos1 != s.length())
        v.push_back(s.substr(pos1));
    return;
}

void StringToMap(const std::string filename, std::vector<RESUNIT> *v)
{
    std::ifstream file;
    file.open(filename);
    while (file.eof())
    {
        std::vector<std::string> list;
        std::string s;
        getline(file, s);
        SplitString(s, list, "\t");
    }
    file.close();
    return;
}

void ResourceManager::Load(const std::string &filename)
{
    std::ifstream res_script;
    res_script.open(filename);
    while(!res_script.eof())
    {
        std::string s, path;
        RESUNIT tmp;
        getline(res_script, s);
        std::istringstream istr(s);
        istr >> tmp.name >> tmp.type >> path;
        std::cout << "Loaded\t" << tmp.name << "\ttype: " << tmp.type << "\tpath: " << path << std::endl;
        tmp.content = SDL_RWFromFile(path.c_str(), "rb");
        //  If there are same name in the same type 
        //  Then overload the previous resource
        for(this->iter=this->res_list->begin();iter!=this->res_list->end();iter++)
        {
            if(this->iter->name == tmp.name && this->iter->type == tmp.type)
            {
                this->iter->content = tmp.content;
                continue;
            }
        }
        this->res_list->push_back(tmp);
    }
    res_script.close();
}

void ResourceManager::Clear()
{
    this->res_list->clear();
}

ResourceManager::ResourceManager(const std::string &filename)
{
    this->res_list = new std::vector<RESUNIT>();
    this->Load(filename);
}

ResourceManager::~ResourceManager()
{
    delete this->res_list;
}

SDL_RWops* ResourceManager::GetResource(const std::string &type, const std::string &name)
{
    for(this->iter=this->res_list->begin();iter!=this->res_list->end();iter++)
    {
            if(this->iter->name == name && this->iter->type == type)
            {
                return this->iter->content;
            }
    }
    return nullptr;
}