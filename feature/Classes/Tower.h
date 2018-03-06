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
			Sprite *getSprite();
			int getLife();
			void loseLife();
			Rect getBoundingBox();
			


			Sprite *_instance;
			int _life;
			int _damage;
			int _speed;
			
			
};

#endif

