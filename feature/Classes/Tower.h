#ifndef __Tower_H__
#define __Tower_H__
#include "Common.h"

class Tower :
			public Node
{
public:
			Tower();
			~Tower();

			static Tower *create();
			void bindTowerSprite(Sprite *sp,int life,int damage,int speed);
			void bindLifeSprite();
			Sprite *getSprite();
			int getLife();
			void loseLife();
			int getPos();
			Rect getBoundingBox();
			


			Sprite *_instance{nullptr};
			int _life{0};
			int _damage{0};
			int _speed{0};
			int _pos{0};
			
			
};

#endif

