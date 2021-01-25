#ifndef PARTICLE_H
#define PARTICLE_H

#include <cstdlib>
#include <string>
#include <vector>
#include "Vector2D.h"
#include "Texture.h"
#include "RenderObject.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*****************************
#	文件名：	Particle.h
#	日期：		2016-12-28 
#	版本号：	0.3.1
#	功能：		粒子系统类型声明  
#	mpsk's game engine proj
*****************************/ 


typedef struct
{
	//定义粒子位置速度加速度
	Vector2D position;
	Vector2D acceleration;
	Vector2D speed;
	
	int t;
	int age;
	int life;
}Particle;


class ParticleSys: public RenderObject
{
	public:
		ParticleSys(int num, int life, int speed_x, int speed_y);
		~ParticleSys();
		//设定粒子生命值（生命值的设定是为了方便垃圾回收）
		//注意：合适的生命值设定有利于改善游戏内存的占用量和游戏运行效率
		void SetLife(int life);
		//设定粒子系统边界，设定散射率，设定抽象系统重力
		void SetKinematic(int _width, int _height, int _dispersion, Vector2D _gravity);
		//设定颜色
		void SetColor(Uint8 Red, Uint8 Green, Uint8 Blue);
		//设定透明度值
		void SetAlpha(Uint8 alpha);
		//中心渲染过程函数,坐标为粒子系统的中心点
		void Render_Central(int x, int y, SDL_Renderer *ren);
		//释放对象内容（包括栈，纹理等等..）
		void free();
	private: 
		Vector2D gravity;
		Vector2D init_speed;
		int ptnum, ptwidth, ptheight, ptlife, ptdispersion;
		//将指定数量指定状态的粒子压入栈内
		void Push(int num, int life, Vector2D speed);
		//粒子系统主要结构体容器
		std::vector<Particle> *particles;
		//粒子系统容器使用的迭代器
		std::vector<Particle>::iterator iter;
		
};



#endif
