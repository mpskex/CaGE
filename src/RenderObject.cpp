#include <CaGE/RenderObject.h>

RenderObject::RenderObject()
{
    this->tex = new Texture();
}

RenderObject::RenderObject(SDL_RWops *src, SDL_Renderer *ren, std::string name)
{
    this->tex = new Texture();
    this->tex->load(src, ren);
    this->name = name;
}

RenderObject::~RenderObject()
{
    delete this->tex;
}

void RenderObject::loadTexture(SDL_RWops *src, SDL_Renderer *ren)
{
    this->tex->load(src, ren);
}

void RenderObject::free()
{
    this->tex->free();
    delete this->tex;
}

void RenderObject::setName(const std::string &s)
{
    this->name = s;
}

std::string RenderObject::getName()
{
    return this->name;
}

void RenderObject::setResourceName(const std::string &s)
{
    this->res_name = s;
}

void RenderObject::setLayer(int _layer){
    this->layer = _layer;
}

std::string RenderObject::getResourceName()
{
    return this->res_name;
}

void RenderObject::renderClip(SDL_Rect dest, SDL_Rect clip, SDL_Renderer *ren)
{
    this->tex->renderClip(dest, clip, ren);
}

void RenderObject::renderClip(int dstX, int dstY, int dstW, int dstH, int srcX, int srcY, int srcW, int srcH, SDL_Renderer *ren)
{
    this->tex->renderClip(dstX, dstY, dstW, dstH, srcX, srcY, srcW, srcH, ren);
}

int RenderObject::getHeight()
{
    return this->tex->getHeight();
}

int RenderObject::getWidth()
{
    return this->tex->getWidth();
}

void RenderObject::render() {
}


//=========================
//  RenderableList
//=========================

RenderableList::RenderableList(std::string name)
{
    this->name = name;
    this->vec_elem = new std::vector<RenderObject*>();
}

RenderableList::~RenderableList()
{
    for(this->iter=this->vec_elem->begin();this->iter!=this->vec_elem->end();this->iter++)
    {
        delete (*this->iter);
    }
    delete this->vec_elem;
}

bool RenderableList::IsInList(std::string s)
{
    bool ret = false;
    for(this->iter=this->vec_elem->begin();this->iter!=this->vec_elem->end();this->iter++)
    {
        if((*this->iter)->getName() == s)
        {
            ret = true;
        }
    }
    return ret;
}

RenderObject* RenderableList::GetElement(std::string s)
{
    for(this->iter=this->vec_elem->begin();this->iter!=this->vec_elem->end();this->iter++)
    {
        if((*this->iter)->getName() == s)
        {
            return (*this->iter);
        }
    }
    return nullptr;
}

bool RenderableList::Push(RenderObject *elem)
{
    for(this->iter=this->vec_elem->begin();this->iter!=this->vec_elem->end();this->iter++)
    {
        if((*this->iter)->getName() == elem->getName())
        {
            //  Name duplicated
            return false;
        }
    }
    this->vec_elem->push_back(elem);
    return true;
}

bool RenderableList::Push(RenderObject *elem, const std::string name)
{
    for(this->iter=this->vec_elem->begin();this->iter!=this->vec_elem->end();this->iter++)
    {
        if((*this->iter)->getName() == name)
        {
            //  Name duplicated
            return false;
        }
    }
    this->vec_elem->push_back(elem);
    return true;
}

bool RenderableList::Pop(std::string s)
{
    for(this->iter=this->vec_elem->begin();this->iter!=this->vec_elem->end();this->iter++)
    {
        if((*this->iter)->getName() == s)
        {
            //  if there is name match
            this->vec_elem->erase(this->iter);
            return true;
        }
    }
    return false;
}

void RenderableList::CursorReset()
{
    this->iter = this->vec_elem->begin();
    this->begin = this->vec_elem->begin();
    this->end = this->vec_elem->end();
}

bool RenderableList::CursorEnd()
{
    return this->iter==this->end;
}

void RenderableList::CursorNext()
{
    this->iter++;
}

RenderObject* RenderableList::GetCursor()
{
    return (*this->iter);
}