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
			void BindMonsterSprite(Sprite *sp,int life,int speed,int pos);
			void bindLifeSprite();
			Sprite *getSprite();
			int getLife();
			void loseLife();
			int getPos();
			Rect getBoundingBox();



			Sprite *_monster_instance{nullptr};
			int _life{0};
			int _speed{0};
			int _pos{0};
	
};

#endif
