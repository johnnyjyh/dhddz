#ifndef __Monster_H__
#define __Monster_H__
#include "Common.h"

class Monster:
			public Node
{
public:
			Monster();
			~Monster();

			static Monster *create();
			void BindMonsterSprite(Sprite *sp,int life,int speed);
			Sprite *getSprite();
			int getLife();
			void loseLife();
			Rect getBoundingBox();



			Sprite *_monster_instance;
			int _life;
			int _speed;
			
	
};

#endif
