//
// Created by 刘方瑞 on 2021-01-20.
//

#ifndef CAGE_CAGE_H
#define CAGE_CAGE_H

#include <vector>

#include "CaGE/Particle.h"
#include "CaGE/Button.h"
#include "CaGE/Background.h"
#include "CaGE/Resource.h"
#include "CaGE/Playable.h"
#include "CaGE/RenderObject.h"


class CaGE{
    /**
     *
     */
public:
    CaGE();
    int AddPlayable(Playable* playable);
    int Loop();
    ~CaGE();
private:
    std::vector<Playable*> *playable_list;
    std::vector<Playable*>::iterator playable_iter;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int SCREEN_WIDTH=1280, SCREEN_HEIGHT=720;
};

#endif //CAGE_CAGE_H
