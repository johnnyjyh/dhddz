#ifndef __Bullet_H__
#define __Bullet_H__
#include "Common.h"

class Bullet:
		public Node
{
public:
			Bullet();
			~Bullet();
			static Bullet *create();
			void BindMonsterSprite(Sprite *sp, int life, int speed, int pos);
			Sprite *getSprite();
			int getLife();
			void loseLife();
			int getPos();
			Rect getBoundingBox();
			
			
			
			Sprite *_bullet_instance{nullptr};
			float _bullet_speed{0};
			float _bullet_damage{0};
			float _bullet_level{0};
			float _bullet_attack_time{ 0 };

			
};

#endif //__Bullet_H__
