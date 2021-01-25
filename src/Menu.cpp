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
	this->plain_list = new RenderableList("plain");
	this->button_list = new RenderableList("button");
	this->res_manager = nullptr;
}

Menu::~Menu()
{
	this->Quit();
}

int Menu::Load(std::string filename)
{
	//加载资源 
	//加载图像资源 	
	//****************************
	//纹理对象初始化
	//****************************

	this->res_manager = new ResourceManager(filename, this->renderer);
	this->background = new Background();
	this->background->loadTexture(SDL_RWFromFile("Resource/background.bmp", "rb"), this->renderer);
	//重设渲染器 
	SDL_RenderClear(this->renderer);
	return 0;
}


Uint32 Menu::Loop()
{
	int fx = this->SCREEN_WIDTH/2, fy = this->SCREEN_HEIGHT/2;
	while(true)
	{ 
		//重设渲染器 
		SDL_RenderClear(this->renderer);
		while(SDL_PollEvent(&event))
		{	
			switch(event.type)
			{
				case SDL_QUIT: quit = true;
				case SDL_KEYDOWN:
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						quit = true;
						return MENU_QUIT;
					}
				} 
				case SDL_MOUSEBUTTONUP:
                {
                    //2代表鼠标按键释放
                    for(this->button_list->CursorReset();!this->button_list->CursorEnd();this->button_list->CursorNext())
                    {
                        if(((Button*)this->button_list->GetCursor())->is_pushed)
                        {
                            return ((Button*)this->button_list->GetCursor())->id;
                        }
                        ((Button *) this->button_list->GetCursor())->mouseButtonEvent(MOUSE_BUTTON_UP);
                    }
                }
				case SDL_MOUSEBUTTONDOWN:
				{
					//判断事件要使用合并的处理，否则将无法分开
                    //1代表摁下，后期会统一使用宏描述
                    for(this->button_list->CursorReset();!this->button_list->CursorEnd();this->button_list->CursorNext())
                    {
                        ((Button *) this->button_list->GetCursor())->mouseButtonEvent(MOUSE_BUTTON_DOWN);
                    }
				}
				case SDL_MOUSEMOTION:
				{
					for(this->button_list->CursorReset();!this->button_list->CursorEnd();this->button_list->CursorNext())
					{
                        ((Button *) this->button_list->GetCursor())->mouseMotionEvent((int)(event.motion.x * this->dpi),
                                                                                      (int)(event.motion.y * this->dpi));
					}
					fx = event.motion.x;
					fy = event.motion.y;
				}
			}
		}
		
		//计算渲染顶点 
		//背景层渲染 
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
		//对象层渲染
		for(auto a=this->res_manager->res_dict.begin();a!=this->res_manager->res_dict.end();a++){
            auto obj = a->second.content;
		    obj->render();
		}
		
		//渲染器渲染 
		SDL_RenderPresent(this->renderer);
	}
}

int Menu::Quit()
{
	delete this->background;
	delete this->button_list;
	delete this->plain_list;
	return 0;
}
