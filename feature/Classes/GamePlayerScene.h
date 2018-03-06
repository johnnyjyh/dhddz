#ifndef __GamePlayerScene_H__
#define __GamePlayerScene_H__
#include "Common.h"
#include "LayerMonster.h"
#include "LayerTower.h"
#include "LayerBullet.h"

class GamePlayerScene :
			public Layer
{
public:
			GamePlayerScene();
			~GamePlayerScene();

			static Scene *createScene();
			static GamePlayerScene *create();		
			static bool loadAnimate();

			//初始化游戏内容
			bool init();
			//创建炮台
			bool createTower();
			//创建怪物，并处理动作 
			bool createMonster();
			//创建并绑定子弹
			bool createAndBindBullet();
			//退出按钮

			
	



			void onEnter();  //预用于内存申请 相关域cocos类
			void onExit();//预用于内存清理 相关域cocos类
			void update(float dt);

			LayerTower *_layerTower;
			LayerMonster *_layerMonster;
		




			static int gamePath[7];

};

#endif
