//
// Created by 刘方瑞 on 2021-01-20.
//
#include <cstdio>
#include <exception>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <CaGE/CaGE.h>

CaGE::CaGE() {
    if (this->Init()!=0){
        throw std::exception();
    }
}

CaGE::~CaGE() {
    if(this->running){
        IMG_Quit();
        SDL_Quit();
    }
}

int CaGE::Init() {
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    // load support for the JPG and PNG image formats
    int initted = IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
    if((initted & IMG_INIT_JPG|IMG_INIT_PNG) != (IMG_INIT_JPG|IMG_INIT_PNG)) {
        printf("IMG_Init: Failed to init required jpg and png support!\n");
        printf("IMG_Init: %s\n", IMG_GetError());
        return 1;
    }
    this->running = true;
    return 0;
}