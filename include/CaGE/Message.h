#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <vector>
using namespace std;
/*****************************
#	文件名：	Message.h 
#	日期：		2016-08-06 
#	版本号：	0.2.6
#	功能：		消息队列的定义 
#	mpsk's game engine proj
*****************************/ 


//	TYPE of message
#define TYP_SCRPT	0x10
#define TYP_IMAGE	0x20
#define TYP_AUDIO	0x30
#define TYP_ANIMA	0x40
//	BEHAVIOR of message
#define BHR_LOAD	0x01
#define BHR_PLAY	0x02
#define BHR_PAUS	0x03
#define BHR_STOP	0x04


typedef struct
{
	int	property;
	string content;
}Message; 


class Messages
{
	public:
		void Push(int msgtype, std::string msg); 
		void Free(); 
		Message Pull();
	private:
		vector<Message> messages;
};

#endif
