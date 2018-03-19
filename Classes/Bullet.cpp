#include "Bullet.h"



Bullet::Bullet()
{
}


Bullet::~Bullet()
{
			
}

Bullet * Bullet::create()
{
			auto bullet = new Bullet();
			bullet->autorelease();
			return bullet;
}

void Bullet::BindMonsterSprite(Sprite * sp, int life, int speed, int pos)
{
			_bullet_instance = sp;
			_bullet_attack_time = life;
			_bullet_speed = speed;
			addChild(sp);
}

Sprite * Bullet::getSprite()
{
			return _bullet_instance;
}

int Bullet::getLife()
{
			return _bullet_attack_time;
}

void Bullet::loseLife()
{
			--_bullet_attack_time;
}

int Bullet::getPos()
{
			return 0;
}

Rect Bullet::getBoundingBox()
{
			auto rectBak = _bullet_instance->getBoundingBox();
			auto pos = convertToWorldSpace(rectBak.origin);
			auto rect = Rect(pos.x, pos.y, rectBak.size.width, rectBak.size.height);
			return rect;
}


