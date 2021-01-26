//
// Created by 刘方瑞 on 2021-01-25.
//

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <vector>

#include <SDL2/SDL.h>

#define EMPTY_EVENT 0
#define QUIT_EVENT  0xffffffff

class EventObject{
public:
    virtual void mouseMotionTrigger(int mouse_x, int mouse_y);
    virtual Uint32 mouseButtonTrigger(int type);
    virtual Uint32 keyboardTrigger(SDL_Keycode key);
    virtual void setEventId(Uint32 id);
protected:
    Uint32 event_id{};
};

class EventManager{
private:
    float dpi;
    std::vector<EventObject*> event_list;
public:
    EventManager(float dpi);
    ~EventManager();
    void registerHook(EventObject* obj);
    Uint32 pollEvent();
};

#endif //EVENTMANAGER_H
