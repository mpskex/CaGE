#include <SDL2/SDL.h>
#include "Game.h"

#define DEBUG
using namespace std;
/*****************************
#	文件名：	Game.cpp 
#	日期：		2017-08-17
#	版本号：	0.3.0
#	功能：		游戏对象 
#	mpsk's game engine proj
*****************************/ 

Game::Game(SDL_Renderer *renderer, int w, int h, float dpi)
{
    this->dpi = dpi;
	this->renderer = renderer;
	this->SCREEN_WIDTH = w;
	this->SCREEN_HEIGHT = h;
}

int Game::Load()
{
	//	TODO:	This will be replaced by scripts
	//加载资源 
	//加载图像资源 	
	//****************************
	//纹理对象初始化
	//****************************
	buttons.push_back(new Button(this->SCREEN_WIDTH-200,this->SCREEN_HEIGHT-90,160,50,SDL_RWFromFile("Resource/start.png","rb"),renderer, GAME_BUTTON_START));
	buttons.push_back(new Button(this->SCREEN_WIDTH-200,this->SCREEN_HEIGHT-180,160,50,SDL_RWFromFile("Resource/option.png","rb"),renderer, GAME_BUTTON_OPTION));
	buttons.push_back(new Button(0,60,160,50,SDL_RWFromFile("Resource/quit.png","rb"),renderer, GAME_BUTTON_ESCAPE));
	
	background = new Background(BG_STITCH);
    background->loadTexture(SDL_RWFromFile("Resource/background.bmp", "rb"), renderer);
	//*****************************
	//粒子系统设置
	//*****************************	 
	cout << "initiating particlesys obj..." << endl; 
	//初始化重力与速度 
	Vector2D gravity;
	gravity.x = 0.0005;
	gravity.y = 0.0005;
	//初始化粒子系统 
	//	每次压入个数	粒子寿命	初始x速度	初始y速度
	particles = new ParticleSys(10, 150, 1, 0);
    particles->loadTexture(SDL_RWFromFile("Resource/atom.png", "rb"), renderer);
	//	设置边框	设置重力
	particles->SetKinematic(SCREEN_WIDTH, SCREEN_HEIGHT, 10, gravity);
	particles->SetAlpha(128);
	//重设渲染器 
	SDL_RenderClear(renderer);

	return 0; 
}


int Game::Loop()
{		 
	while(true)
	{
		//清理渲染器 
		SDL_RenderClear(renderer);
		
		//计算渲染顶点 
		//背景层渲染 
		background->render(SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
		
		for(button_iter=buttons.begin();button_iter!=buttons.end();button_iter++)
		{
            (*this->button_iter)->render();
		}
		//对象层渲染

		//粒子层渲染 
		particles->Render_Central(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, renderer);
		//渲染器渲染 
		SDL_RenderPresent(renderer);
	}
	return GAME_BUTTON_ESCAPE;
}

int Game::Quit()
{
	delete particles;
	delete background;

	for(button_iter=buttons.begin();button_iter!=buttons.end();button_iter++)
	{
		delete (*this->button_iter);
	}
	return 0;
}
