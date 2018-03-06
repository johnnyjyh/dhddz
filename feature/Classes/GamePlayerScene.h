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

			//��ʼ����Ϸ����
			bool init();
			//������̨
			bool createTower();
			//��������������� 
			bool createMonster();
			//���������ӵ�
			bool createAndBindBullet();
			//�˳���ť

			
	



			void onEnter();  //Ԥ�����ڴ����� �����cocos��
			void onExit();//Ԥ�����ڴ����� �����cocos��
			void update(float dt);

			LayerTower *_layerTower;
			LayerMonster *_layerMonster;
		




			static int gamePath[7];

};

#endif
