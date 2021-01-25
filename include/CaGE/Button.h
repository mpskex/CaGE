#ifndef Button_H
#define Button_H
#include "Vector2D.h"
#include "Texture.h"
#include "RenderObject.h"
#include "Message.h"
#include <vector>
#include <string>

#define MOUSE_BUTTON_UP 		0x2000
#define MOUSE_BUTTON_DOWN		0x2001


/*****************************
#	文件名：	Button.h 
#	日期：		2017-1-15
#	版本号：	0.3.2
#	功能：		按钮对象声明 
#	mpsk's game engine proj
#-----------------------------
#	Button类型有Texture方法类，Audio方法类，CtrlSys方法类
#	同时还可以具有Pullevent方法
***********************/
class Button: public RenderObject
{
	public:
		Button(int x, int y, int w, int h, SDL_RWops *src, SDL_Renderer *ren, Uint32 id);
		~Button();
		void setPos(int x, int y, int w, int h);
		void loadTexture(SDL_RWops *src, SDL_Renderer *ren);
		void render();
		//	用于处理鼠标消息（0代表位置判断，1代表鼠标摁下，2代表鼠标松开）
		void mouseMotionEvent(int Mouse_x, int Mouse_y);
		void mouseButtonEvent(int type);
		//	按钮id用于触发消息
		int id;
		bool is_pushed;

	private:
		int tex_w, tex_h;
		bool flag;
		SDL_Renderer *ren;
		//Texture方法类用于处理按钮纹理
		SDL_Rect clip[4];
};

#endif
