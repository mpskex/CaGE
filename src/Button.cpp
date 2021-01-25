#include <SDL2/SDL.h>
#include <CaGE/Button.h>
#include <cstdio>
/*****************************
#	文件名：	Button.h 
#	日期：		2017-1-16 
#	版本号：	0.3.2 
#	功能：		按钮对象声明 
#	mpsk's game engine proj
#-----------------------------
#	Button类型有Texture方法类，Audio方法类，CtrlSys方法类
#	同时还可以具有Pullevent方法
***********************/

Button::Button(int x, int y, int w, int h, SDL_RWops *src, SDL_Renderer *ren)
{
    this->ren = ren;
    this->is_pushed = false;
    this->flag = false;
    this->loadTexture(src, ren);
    this->setPos(x, y, w, h);
}

Button::Button(int x, int y, int w, int h, SDL_RWops *src, SDL_Renderer *ren, Uint32 id)
{
    this->id = id;
    this->ren = ren;
    this->is_pushed = false;
    this->flag = false;
    this->loadTexture(src, ren);
    this->setPos(x, y, w, h);
}

Button::~Button()
{
    this->free();
}


void Button::setPos(int x, int y, int w, int h)
{
    this->dst.x = x;
    this->dst.y = y;
    this->dst.w = w;
    this->dst.h = h;
}

void Button::loadTexture(SDL_RWops *src, SDL_Renderer * ren)
{
    this->tex = new Texture();
    this->tex->load(src, ren);
    this->tex_w = this->tex->getWidth();
    this->tex_h = this->tex->getHeight();
    this->clip[0].x = 0;
    this->clip[0].y = 0;
    this->clip[0].w = this->tex_w/2;
    this->clip[0].h = this->tex_h/2;
    this->clip[1].x = this->tex_w/2;
    this->clip[1].y = 0;
    this->clip[1].w = this->tex_w;
    this->clip[1].h = this->tex_h/2;
    this->clip[2].x = 0;
    this->clip[2].y = this->tex_h/2;
    this->clip[2].w = this->tex_w/2;
    this->clip[2].h = this->tex_h;
    this->clip[3].x = this->tex_w/2;
    this->clip[3].y = this->tex_h/2;
    this->clip[3].w = this->tex_w;
    this->clip[3].h = this->tex_h;
}

void Button::render()
{
    if(this->is_pushed)
    {
        this->tex->renderClip(this->dst, this->clip[2], this->ren);
    }
    else if(!is_pushed && flag)
    {
        this->tex->renderClip(this->dst, this->clip[1], this->ren);
    }
    else
    {
        this->tex->renderClip(this->dst, this->clip[0], this->ren);
    }
}

void Button::mouseMotionEvent(int Mouse_x, int Mouse_y)
{
    if(Mouse_x>=this->dst.x&&Mouse_x<=this->dst.x+this->tex_w/2&&Mouse_y>=this->dst.y&&Mouse_y<=this->dst.y+this->tex_h/2)
    {
        this->flag = true;
    }
    else
    {
        this->flag = false;
    }
}

//用于处理鼠标消息（1代表鼠标摁下，2代表鼠标松开）
void Button::mouseButtonEvent(int type)
{
    switch(type)
    {
        case MOUSE_BUTTON_DOWN:
        {
			if(this->flag==1)
            {
				this->is_pushed = true;
			}
        }break;
        case MOUSE_BUTTON_UP:
        {
            if(this->is_pushed==1)
			{
				this->is_pushed = false;
			}
        }break;
    }
}
