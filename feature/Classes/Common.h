#ifndef __Common_H__
#define __Common_H__

#include "cocos2d.h"
USING_NS_CC;
#define winSize (Director::getInstance()->getWinSize())
#define NET_BUF_SIZE 255

const int pkWidth = 71;
const int pkHeight = 96;
const int pkInterval = 22;
const char pokerFileName[255] = "poker.png";
const char bkFileName[255] = "bk.png";
const char buttonStrFileName[255] = "strings.xml";
const char signFileName[255] = "BANKER.png";
const char turnSignFileName[255] = "USER_TRUSTEE.png";


//花色
enum Suit
{
			Spade = 0,
			Heart,
			Club,
			Diamond,
			Joker,
			suitReverse=4,
};
//扑克分值
enum pkNumber
{
			three=0,
			four,
			five,
			six,
			seven,
			eight,
			nine,
			ten,
			jack,
			queen,
			king,
			ace,
			two,
			blackJoker,
			redJoker,
			numberReverse=2,
};

//出牌类型
enum CARD_TYPE
{
			SINGLE_CARD = 1,		//单牌-
			DOUBLE_CARD,			//对子-
			THREE_CARD,				//3不带-	
			THREE_ONE_CARD,			//3带1-
			THREE_TWO_CARD,			//3带2-		
			CONNECT_CARD,			//连牌-
			COMPANY_CARD,			//连队-
			AIRCRAFT_CARD,			//飞机不带-
			AIRCRAFT_SINGLE_CARD,	//飞机带单牌-
			AIRCRAFT_DOBULE_CARD,	//飞机带对子-
			BOMB_TWO_CARD,			//四个带2张单牌
			BOMB_DOUBLE_TWO_CARD,		//四个带2对
			BOMB_CARD,				//炸弹
			MISSILE_CARD,            //王炸
			ERROR_CARD				//错误的牌型
};


#endif
