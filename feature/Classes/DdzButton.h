#ifndef __DdzButton_H__
#define __DdzButton_H__
#include "Common.h"

class GameScene;
class Player;
class DdzButton 
:public
			Menu
{
public:
			DdzButton();
			~DdzButton();
			//��ť����
			static DdzButton* create();
			//��ť��ʼ��
			bool init();
			//��ť���幦��
			bool createMenu(const char *FileName);
			void callTagForClient(int score);
			void callTagForServer(int score);

			
			 Menu *callMenu;
			 Menu *playMenu;
			 Menu *loseMenu;
			 Menu *winMenu;
			 Menu *reLoad;

			 //GameScene * GameMain;
			 static GameScene *GameMain;
};

#endif

