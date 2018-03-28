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
			//按钮申请
			static DdzButton* create();
			//按钮初始化
			bool init();
			//按钮具体功能
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

