#include <SDL2/SDL.h>
#include "Intro.h"

Intro::Intro(SDL_Renderer *ren, int Screen_w, int Screen_h, float dpi)
{
    this->dpi = dpi;
	this->ren = ren;
	this->Screen_w = Screen_w;
	this->Screen_h = Screen_h;
}

Intro::~Intro()
{
	this->Quit();
}

//  载入对象
void Intro::Load()
{
	this->logo = new Texture();
	this->logo->load(SDL_RWFromFile("Resource/logo.jpg", "rb"), this->ren);
    this->logo->setBlendMode(SDL_BLENDMODE_BLEND);
}
//  渲染
void Intro::Loop()
{
	SDL_Event event;
	//this->logo->setAlpha(10);
    for(int alpha=0; alpha<255; alpha+=2)
    {
        //清理渲染器 
		SDL_RenderClear(this->ren);
		while (SDL_PollEvent(&event))
		{	
			switch(event.type)
			{
				case SDL_QUIT: return;
				case SDL_KEYDOWN:
				{
					if (event.key.keysym.sym == SDLK_SPACE)
					{
						return;
					}
				} 
			}
		}
        this->logo->setAlpha(alpha);
        this->logo->render(Screen_w / 2 - logo->getWidth() / 2, Screen_h / 2 - logo->getWidth() / 2, this->ren);
		SDL_RenderPresent(this->ren);
	}
	SDL_Delay(200);
	for(int alpha=255; alpha>0; alpha-=2)
    {
        //清理渲染器 
		SDL_RenderClear(this->ren);

		while (SDL_PollEvent(&event))
		{	
			switch(event.type)
			{
				case SDL_QUIT: return;
				case SDL_KEYDOWN:
				{
					if (event.key.keysym.sym == SDLK_SPACE)
					{
						return;
					}
				} 
			}
		}
        this->logo->setAlpha(alpha);
        this->logo->render(Screen_w / 2 - logo->getWidth() / 2, Screen_h / 2 - logo->getWidth() / 2, this->ren);
		SDL_RenderPresent(this->ren);
	}
	return;
	
}
//释放SDL_Texture对象
void Intro::Quit()
{
	delete this->logo;
}