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
			bool initLifeSprite();
			void updateLife();
			Sprite *getSprite();
			int getLife();
			void loseLife();
			void addLife();
			int getPos();
			Rect getBoundingBox();
			

			std::vector<Sprite *> _lifeVec;
			Sprite *_instance{nullptr};
			int _life{0};
			int _damage{0};
			int _speed{0};
			int _pos{0};
			CC_SYNTHESIZE(bool, _runForAttack, IsAttacked);
			
			
};

#endif

