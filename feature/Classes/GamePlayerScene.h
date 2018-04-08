#ifndef __GamePlayerScene_H__
#define __GamePlayerScene_H__
#include "Common.h"
#include "LayerMonster.h"
#include "LayerTower.h"
#include "LayerBullet.h"
#include "CellsLayer.h"

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
			//
			bool createCellsForPlant();
			
			//退出按钮

			bool initBackGround();


			
	



			void onEnter();  //预用于内存申请 相关域cocos类
			void onExit();//预用于内存清理 相关域cocos类
			void update(float dt);
			
						//以下四个继承来的虚函数用于来集成控制函数
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);
			

			LayerTower *_layerTower;
			LayerMonster *_layerMonster;
			CellsLayer *_layerCells;

			float _scalesizeX;
			float _scalesizeY;
		




			static int gamePath[7];

};

#endif
