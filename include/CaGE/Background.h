#ifndef Background_H
#define Background_H

#include "Texture.h"
#include "RenderObject.h"

/*****************************
#	文件名：	Background.h
#	日期：		2017-1-17
#	版本号：	0.3.2
#	功能：		背景对象 
#	mpsk's game engine proj
*****************************/ 

//  拉伸  
#define BG_STITCH   0x1000
//  平铺
#define BG_FLAT     0x1001

class Background: public RenderObject
{
    public:
        Background();
        Background(Uint32 type);
        void render(int Screen_w, int Screen_h, SDL_Renderer *ren);
};

#endif