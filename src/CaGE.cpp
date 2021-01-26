//
// Created by 刘方瑞 on 2021-01-20.
//
#include <cstdio>
#include <exception>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <CaGE/CaGE.h>
#include "CaGe/Log.h"


CaGE::CaGE(){
//初始化
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
    {
        LogError(cout, "engine:SDL_Init");
        throw std::exception();
    }

    //创建会话窗口
    window = SDL_CreateWindow("GRiNa", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_FULLSCREEN_DESKTOP|SDL_WINDOW_ALLOW_HIGHDPI|SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        LogError(cout, "engine:SDL_CreateWindow");
        SDL_Quit();
        throw std::exception();
    }
    SDL_GL_GetDrawableSize(this->window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    cout << "Screen width is:" << SCREEN_WIDTH << endl;
    cout << "Screen height is:" << SCREEN_HEIGHT << endl;
    //创建渲染器
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (this->renderer == nullptr)
    {
        SDL_DestroyWindow(this->window);
        LogError(cout, "engine:SDL_CreateRenderer");
        SDL_Quit();
        throw std::exception();
    }
    this->playable_list = new vector<Playable*>;
}

int CaGE::Loop() {
    Playable* cur_playable = *this->playable_list->begin();

    // Find the start node
    for(this->playable_iter=this->playable_list->begin();this->playable_iter!=this->playable_list->end();this->playable_iter++){
        if((*this->playable_iter)->is_start){
            cur_playable = (*this->playable_iter);
        }
    }

    // Do the non-linear loop
    while(true){
        cur_playable->Load();
        cur_playable->Loop();
        cur_playable->Quit();
        cur_playable = cur_playable->getNext();
        if(cur_playable == nullptr){
            break;
        }
    }
    return 0;
}


CaGE::~CaGE(){
    cout<<"Game Quit!\n"<<endl;
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}