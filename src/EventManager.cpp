//
// Created by 刘方瑞 on 2021-01-26.
//
#include <iostream>
#include <CaGE/EventManager.h>

void EventObject::mouseMotionTrigger(int mouse_x, int mouse_y){}
Uint32 EventObject::mouseButtonTrigger(int type){return EMPTY_EVENT;}
Uint32 EventObject::keyboardTrigger(SDL_Keycode key){return EMPTY_EVENT;}
void EventObject::setEventId(Uint32 id) {
    this->event_id = id;
}


EventManager::EventManager(float dpi) {
    this->dpi = dpi;
}

EventManager::~EventManager() = default;

void EventManager::registerHook(EventObject *obj) {
    this->event_list.push_back(obj);
}

Uint32 EventManager::pollEvent() {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_MOUSEMOTION:
            {
                for(auto a: this->event_list){
                    a->mouseMotionTrigger((int)(event.motion.x * this->dpi),
                                          (int)(event.motion.y * this->dpi));
                }
            }
            case SDL_KEYDOWN:
            {
                for(auto a: this->event_list){
                    Uint32 event_id = a->keyboardTrigger(event.key.keysym.sym);
                    if(event_id!=EMPTY_EVENT){
                        std::cout << "KeyDownTriggered: " << event_id << std::endl;
                        return event_id;
                    }
                }
                if(event.key.keysym.sym == SDLK_ESCAPE){
                    return QUIT_EVENT;
                }
            }
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
            {
                for(auto a: this->event_list){
                    Uint32 event_id = a->mouseButtonTrigger(event.type);
                    if(event_id!=EMPTY_EVENT){
                        std::cout << "MouseButtonTriggered: " << event_id << std::endl;
                        return event_id;
                    }
                }
            }
        }
    }
}
