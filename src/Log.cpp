#include "CaGE/Log.h"
#include <SDL2/SDL.h>
 /*****************************
#	文件名：	Log.cpp 
#	日期：		2016-08-06 
#	版本号：	0.2.6
#	功能：		日志系统 
#	mpsk's game engine proj
*****************************/ 
void LogError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}
