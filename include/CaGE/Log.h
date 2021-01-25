#ifndef Log_H
#define Log_H
#include <iostream>
#include <string> 
#include <cstdlib>

 /*****************************
#	文件名：	Log.h
#	日期：		2016-08-06 
#	版本号：	0.2.6
#	功能：		日志系统 
#	mpsk's game engine proj
*****************************/ 

//std::ostream可以选择多种输出流，包括cout
void LogError(std::ostream &os, const std::string &msg);
void IMGLogError(std::ostream &os, const std::string &msg);

#endif
