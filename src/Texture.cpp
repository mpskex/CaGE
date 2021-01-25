#include <iostream>
#include <SDL2/SDL.h>
#include <CaGE/Texture.h>
#include <CaGE/Log.h>

/*****************************
#	文件名：	Texture.cpp
#	日期：		2017-09-01 
#	版本号：	0.4.1
#	功能：		纹理对象实现 
#	mpsk's game engine proj
*****************************/
Texture::Texture(SDL_RWops *src, SDL_Renderer *ren)
{
    this->load(src, ren);
}

void Texture::load(SDL_RWops *src, SDL_Renderer *ren)
{
    if(src == nullptr){
        LogError(std::cout, "Texture:Null SDL_RWops");
        throw std::exception();
    }

	SDL_Surface *image;
	image = IMG_Load_RW(src, 0);
	if(image == nullptr)
	{
		IMGLogError(std::cout, "Texture:IMG_Load_RW");
		throw std::exception();
	}
	else
	{
		this->texture = SDL_CreateTextureFromSurface(ren, image);
		if(this->texture == NULL)
		{
			LogError(std::cout, "Texture:SDL_CreateTextureFromSurface");
			return;
		}
		else
		{
			SDL_QueryTexture(this->texture, NULL, NULL, &dst.w, &dst.h);
		}
	}
}

void Texture::loadFromFile(const std::string &file, SDL_Renderer *ren)
{
	this->texture = IMG_LoadTexture(ren, file.c_str());
	if (this->texture == NULL){
		LogError(std::cout, "loadTexture");
	}
	//renderer = ren;
	SDL_QueryTexture(this->texture, NULL, NULL, &dst.w, &dst.h);
}


void Texture::free()
{
	//释放纹理
	SDL_DestroyTexture(texture);
}


void Texture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//设置颜色模式
	SDL_SetTextureColorMod(texture, red, green, blue);
}


void Texture::setBlendMode(SDL_BlendMode blending)
{
	//设置混合模式
	SDL_SetTextureBlendMode(texture, blending);
}


void Texture::setAlpha(Uint8 alpha)
{
	//设置不透明度
	SDL_SetTextureAlphaMod(texture, alpha);
}

//将来接入切片clip
//void Texture::render(int x, int y, SDL_Rect* clip)
void Texture::render(int x, int y, SDL_Renderer *ren)
{
	dst.x = x;
	dst.y = y;
	SDL_RenderCopy(ren, this->texture, NULL , &dst);
}

void Texture::renderClip(SDL_Rect dest, SDL_Rect clip, SDL_Renderer *ren)
{
	//SDL_Rect是由点坐标以及纹理宽高组成的结构
	SDL_RenderCopy(ren, this->texture, &clip , &dest);
}

void Texture::renderClip(int dstX, int dstY, int dstW, int dstH, int srcX, int srcY, int srcW, int srcH, SDL_Renderer *ren)
{
	SDL_Rect dst, src;
	dst.x = dstX;
	dst.y = dstY;
	dst.w = dstW;
	dst.h = dstH;
	src.x = srcX;
	src.y = srcY;
	src.w = srcW;
	src.h = srcH;
	//SDL_Rect是由点坐标以及纹理宽高组成的结构
	SDL_RenderCopy(ren, texture, &src , &dst);
}


void Texture::renderDst(SDL_Rect dest, SDL_Renderer *ren)
{
	//SDL_Rect是由点坐标以及纹理宽高组成的结构
	SDL_RenderCopy(ren, texture, NULL, &dest);
}


int Texture::getWidth()
{
	//printf("loaded texture width @%4d.\n", dst.w);
	return dst.w;
}
int Texture::getHeight()
{
	//printf("loaded texture height @%4d.\n", dst.h);
	return dst.h;
}
