#ifndef __Bullet_H__
#define __Bullet_H__
#include "Common.h"

class Bullet:
		public Node
{
public:
			Bullet();
			~Bullet();
			static Sprite *create();
			Sprite *_bullet_instance;
			float _bullet_speed;
			float _bullet_damage;
			float _bullet_level;

			
};

#endif //__Bullet_H__
