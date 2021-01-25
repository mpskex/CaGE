#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <iostream> 
#include <thread>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "CaGE/Particle.h"
#include "CaGE/Button.h"
#include "CaGE/Background.h"
#include "CaGE/Log.h"
#include "CaGE/Vector2D.h"


#define GAME_BUTTON_START		0xF001
#define GAME_BUTTON_PAUSE		0xF002
#define GAME_BUTTON_OPTION		0xF003
#define GAME_BUTTON_SAVE		0xF004
#define GAME_BUTTON_ESCAPE		0xF005
#define	GAME_BUTTON_QUIT		0xFFFF
#define GAME_START				GAME_BUTTON_START
#define GAME_PAUSE				GAME_BUTTON_PAUSE
#define GAME_OPTION				GAME_BUTTON_OPTION
#define GAME_SAVE				GAME_BUTTON_SAVE
#define GAME_ESCAPE				GAME_BUTTON_ESCAPE
#define GAME_QUIT				GAME_BUTTON_QUIT
/*****************************
#	文件名：	Game.h
#	日期：		2017-1-15
#	版本号：	0.3.2
#	功能：		游戏对象 
#	mpsk's game engine proj
*****************************/ 

class Game
{
	private:
		SDL_Renderer *renderer;
		SDL_Window *window;
		SDL_Event event;
		int SCREEN_WIDTH;		//画面分辨率 
		int SCREEN_HEIGHT;
        float dpi=1;
		ParticleSys *particles;
		Background *background;
		vector<Button*> buttons;
		vector<Button*>::iterator button_iter;
		int Quit();
	public:
		bool quit = 0;
		Game(SDL_Renderer *ren, int w, int h, float dpi);
		int Load();
		int Loop();
};


#endif
