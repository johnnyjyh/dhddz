#ifndef __LayerTower_H__
#define __LayerTower_H__
#include "Common.h"
#include "Tower.h"
#include "LayerBullet.h"

class LayerTower:
			public Layer
{
public:
			LayerTower();
			~LayerTower();
			CREATE_FUNC(LayerTower);
					
			bool init();
			
			void addTower(int index);

			void moveTower(int index);

			void attack(Node *node);
			
			Tower *_tower;
			LayerBullet *_bulletLayer;
			Vector<SpriteFrame *> _spriteFrameVec;

			
};

#endif //__LayerTower_H__