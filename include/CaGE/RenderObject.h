#ifndef Element_H
#define Element_H
#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include <CaGE/Texture.h>

/*
RenderObject
Copyright by mpsk @ 2018

This is a base class for GRiNa Visual Elements
Currently have child:
    Background
    Button
    ParticleSys

*/

class RenderObject
{
    public:
        RenderObject();
        RenderObject(SDL_RWops *src, SDL_Renderer *ren);
        RenderObject(SDL_RWops *src, SDL_Renderer *ren, std::string name);
        ~RenderObject();
        virtual void loadTexture(SDL_RWops *src, SDL_Renderer *ren);
        //  void render() need to be implemented by yourself
        void setName(const std::string &s);
        void setLayer(int layer);
        void setResourceName(const std::string &s);

        virtual void render();
        void renderClip(SDL_Rect dest, SDL_Rect clip, SDL_Renderer *ren);
		void renderClip(int dstX, int dstY, int dstW, int dstH, int srcX, int srcY, int srcW, int srcH, SDL_Renderer *ren);

        int getHeight();
        int getWidth();
        std::string getResourceName();
        std::string getName();
        void free();
    protected:
        Texture *tex;
        std::string name;
        std::string res_name;
        Uint32 type;
        Uint32 layer;
        SDL_Rect dst;
};

class RenderableList
{
    public:
        RenderableList(std::string name);
        ~RenderableList();
        bool IsInList(std::string s);
        RenderObject* GetElement(std::string s);
        bool Push(RenderObject *elem);
        bool Push(RenderObject *elem, std::string name);
        bool Pop(std::string s);

        void CursorReset();
        bool CursorEnd();
        void CursorNext();
        RenderObject* GetCursor();
    private:
        std::vector<RenderObject*> *vec_elem;
        std::vector<RenderObject*>::iterator iter, begin, end;
        std::string name;
};

#endif