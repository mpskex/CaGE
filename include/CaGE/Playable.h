#ifndef Playable_H
#define Playable_H

#include <vector>

#include "Particle.h"
#include "Button.h"
#include "Background.h"

#define NODE_NORM   0x0
#define NODE_END    0x2

class Playable
{
	protected:
		SDL_Renderer *renderer;
		SDL_Event event;

		//	Background (we only need one)
		Background *background;

		//	Sprites Vectors
		vector<Button*> buttons;
		vector<Button*>::iterator button_iter;
		vector<Texture*> layer;
		vector<Texture*>::iterator layer_iter;
		vector<ParticleSys*> particles;
		vector<ParticleSys*>::iterator particles_iter;
		//	Resource Vectors
		vector<SDL_RWops*> resources;
	public:
		int SCREEN_WIDTH;		//画面分辨率 
		int SCREEN_HEIGHT;
		bool is_quit = false;
		bool is_start = true;
		Playable *getNext();
        int Init();
        int Load();
		Uint32 Loop();
		int Quit();
};


#endif