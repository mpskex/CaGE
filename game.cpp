//
// Created by 刘方瑞 on 2021-01-20.
//
#include "Game.h"
#include "Intro.h"
#include "Menu.h"
#include "CaGE/Resource.h"
#include <iostream>
using namespace std;
//#define DEBUG

/*****************************
#	文件名：	GRiNa.cpp 
#	日期：		2017-07-20
#	版本号：	0.3.0
#	功能：		主程序 
#	mpsk's game engine proj
*****************************/

SDL_Window *window;
SDL_Renderer *renderer;
int SCREEN_WIDTH=1280, SCREEN_HEIGHT=720;
float dpi = 1;

int Init()
{
    //初始化 
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
    {
        LogError(cout, "main:SDL_Init");
        return 1;
    }

    //创建会话窗口 
    window = SDL_CreateWindow("GRiNa", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_OPENGL);
    if (window == NULL)
    {
        LogError(cout, "main:SDL_CreateWindow");
        SDL_Quit();
        return 1;
    }
    int w, h;
    SDL_GL_GetDrawableSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    SDL_GetWindowSize(window, &w, &h);
    dpi = (float)SCREEN_WIDTH / (float)w;

    cout << "Screen width is:" << SCREEN_WIDTH << endl;
    cout << "Screen height is:" << SCREEN_HEIGHT << endl;
    //创建渲染器 
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        SDL_DestroyWindow(window);
        LogError(cout, "main:SDL_CreateRenderer");
        SDL_Quit();
        return 1;
    }
    return 0;
}

int Quit()
{
    cout<<"Game Quit!\n"<<endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


int main(int argc, char *argv[] )
{
//测试代码	
#ifdef DEBUG
    /*
	Script script;
	if(script.load("Resource/script.grs")!=0)
	{
		cout << "Error Reading file!" << endl;
		return -1;
	}
	int i = 0;
	while(1)
	{
		string s;
		if(script.Docode(s)==-1)
		{
			break;
		}
		cout << i++ << " " << s << endl;
	}
	return 0;
	*/
	std::cout << "Here~" << std::endl;
	ResourceManager *res = new ResourceManager("Resource/menu.grconf");


#else
    //正式代码
    Init();

    auto *intro = new Intro(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, dpi);
    intro->Load();
    intro->Loop();
    intro->Quit();

    SDL_RenderClear(renderer);
    while(true)
    {
        Menu *menu = new Menu(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, dpi);
        //初始化游戏
        if(menu->Load("Resource/resource.json") != 0)
        {
            return 1;
        }
        Uint32 _return = menu->Loop();
        delete menu;
        cout << _return << endl;
        //执行游戏loop
        switch(_return)
        {
            case MENU_NEWGAME:
            {
                Game *game = new Game(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, dpi);
                game->Load();
                if(game->Loop()==GAME_QUIT)
                {
                    delete game;
                    Quit();
                    return 0;
                }
                delete game;
                break;
            }
            case MENU_QUIT:
            {
                Quit();
                return 0;
            }
            default:
            {
                break;
            }
        }
    }
    Quit();
    return 0;
#endif
}

