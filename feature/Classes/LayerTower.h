#ifndef __LayerTower_H__
#define __LayerTower_H__
#include "Common.h"
#include "Tower.h"

class LayerTower:
			public Layer
{
public:
			LayerTower();
			~LayerTower();
			CREATE_FUNC(LayerTower);
					
			bool init();
			
			void addTower(float dt);

			void moveTower(int index);
			
			Tower *_tower;
			Vector<SpriteFrame *> _spriteFrameVec;

			
};

#endif //__LayerTower_H__