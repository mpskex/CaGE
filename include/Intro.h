#ifndef INTRO_H
#define INTRO_H

#include <cstdlib>
#include <iostream> 
#include <thread>

#include "CaGE/Texture.h"

#include "CaGE/Log.h"
#include "CaGE/Vector2D.h"

/*****************************
#	文件名：	Intro.h
#	日期：		2017-8-17
#	版本号：	0.3.2
#	功能：	    游戏logo
#	mpsk's game engine proj
*****************************/ 

class Intro
{
public:
    Intro(SDL_Renderer *ren, int Screen_w, int Screen_h, float dpi);
    ~Intro();
    //  载入对象
    void Load();
    //  渲染
    void Loop();
    //释放SDL_Texture对象
    void Quit();
private:
    //  Logo
    float dpi=1;
    int Screen_w, Screen_h;
    Texture *logo;
    SDL_Renderer *ren;
};


#endif