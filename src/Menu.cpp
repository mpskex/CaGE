#include <SDL2/SDL.h>
#include "Menu.h"
#define DEBUG
using namespace std;
/*****************************
#	文件名：	Menu.cpp 
#	日期：		2017-08-17
#	版本号：	0.3.0
#	功能：		游戏对象 
#	mpsk's game engine proj
*****************************/ 

Menu::Menu(SDL_Renderer *renderer, int w, int h, float dpi)
{
    this->dpi = dpi;
    this->renderer = renderer;
    this->SCREEN_WIDTH = w;
    this->SCREEN_HEIGHT = h;
	this->res_manager = nullptr;
    this->event_manager = new EventManager(this->dpi);
    this->res_manager = new ResourceManager(this->renderer);
    this->res_manager->linkEventManager(this->event_manager);
}

Menu::~Menu()
{
	this->Quit();
}

int Menu::Load(const std::string& filename)
{
	//加载资源 
	//加载图像资源 	
	//****************************
	//纹理对象初始化
	//****************************
	this->res_manager->load(filename);

	this->background = new Background();
	this->background->loadTexture(SDL_RWFromFile("Resource/background.bmp", "rb"), this->renderer);
	//重设渲染器 
	SDL_RenderClear(this->renderer);
	return 0;
}


Uint32 Menu::Loop()
{
	// int fx = this->SCREEN_WIDTH/2, fy = this->SCREEN_HEIGHT/2;
	while(true)
	{ 
		//
		SDL_RenderClear(this->renderer);

		this->background->render(SCREEN_WIDTH, SCREEN_HEIGHT, this->renderer);
		/*
		int level = 2;
		for(this->plain_list->CursorReset();!this->plain_list->CursorEnd();this->plain_list->CursorNext())
		{
			RenderObject *ptr = this->plain_list->GetCursor();
            ptr->renderClip(
                    -MENU_MARGIN - 0.1 * (fx - this->SCREEN_WIDTH / 2) - 0.1 * level * (fx - this->SCREEN_WIDTH / 2),
                    this->SCREEN_HEIGHT - ptr->getHeight() - 0.5 * level * MENU_MARGIN -
                    level * 0.1 * (fy - this->SCREEN_HEIGHT / 2),
                    this->SCREEN_WIDTH + 2 * MENU_MARGIN,
                    ptr->getHeight(),
                    0, 0,
                    ptr->getWidth(), ptr->getHeight(),
                    this->renderer
            );
			level--;
		}
		for(this->button_list->CursorReset();!this->button_list->CursorEnd();this->button_list->CursorNext())
		{
            ((Button *) this->button_list->GetCursor())->render();
		}
         */
        auto event_id = this->res_manager->renderAll();
        if (event_id == QUIT_EVENT){
            return QUIT_EVENT;
        }
		//渲染器渲染 
		SDL_RenderPresent(this->renderer);
	}
}

int Menu::Quit()
{
	delete this->background;
	return 0;
}
