#ifndef Texture_H
#define Texture_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Vector2D.h"
#include <string>

/*****************************
#	文件名：	Texture.h
#	日期：		2016-12-28 
#	版本号：	0.3.1
#	mpsk's game engine proj
*****************************/ 

class Texture
{
	public:
		Texture(){};
		Texture(SDL_RWops *src, SDL_Renderer *ren);
		void load(SDL_RWops *src, SDL_Renderer *ren);

		void loadFromFile(const std::string &file, SDL_Renderer *ren);
		//释放SDL_Texture对象
		void free();
		//设定颜色模式
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		//设定混合模式
		void setBlendMode(SDL_BlendMode blending);
		//设定透明度alpha值
		void setAlpha(Uint8 alpha);
		//简单定比渲染函数
		void render(int x, int y, SDL_Renderer *ren);
		//切片渲染
		void renderClip(SDL_Rect dest, SDL_Rect clip, SDL_Renderer *ren);
		void renderClip(int dstX, int dstY, int dstW, int dstH, int srcX, int srcY, int srcW, int srcH, SDL_Renderer *ren);
		//标定渲染
		void renderDst(SDL_Rect dest, SDL_Renderer *ren);
		int getWidth();
		int getHeight();
	private:
		//纹理顶点位置
		SDL_Rect dst;
		SDL_Texture *texture;
};

#endif
