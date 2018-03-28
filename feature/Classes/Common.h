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


//��ɫ
enum Suit
{
			Spade = 0,
			Heart,
			Club,
			Diamond,
			Joker,
			suitReverse=4,
};
//�˿˷�ֵ
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

//��������
enum CARD_TYPE
{
			SINGLE_CARD = 1,		//����-
			DOUBLE_CARD,			//����-
			THREE_CARD,				//3����-	
			THREE_ONE_CARD,			//3��1-
			THREE_TWO_CARD,			//3��2-		
			CONNECT_CARD,			//����-
			COMPANY_CARD,			//����-
			AIRCRAFT_CARD,			//�ɻ�����-
			AIRCRAFT_SINGLE_CARD,	//�ɻ�������-
			AIRCRAFT_DOBULE_CARD,	//�ɻ�������-
			BOMB_TWO_CARD,			//�ĸ���2�ŵ���
			BOMB_DOUBLE_TWO_CARD,		//�ĸ���2��
			BOMB_CARD,				//ը��
			MISSILE_CARD,            //��ը
			ERROR_CARD				//���������
};


#endif
