#include "Tower.h"



Tower::Tower()
{
			
}


Tower::~Tower()
{

}

Tower * Tower::create()
{
			auto pRet = new Tower();
			pRet->autorelease();
			return pRet;
}

void Tower::bindTowerSprite(Sprite *sp, int life, int damage, int speed)
{
			_instance = sp;
			_life = life;
			_damage = damage;;
			_speed = speed;

#ifdef _Test_		
			
#endif //_Test_

			addChild(_instance);
}

void Tower::bindLifeSprite()
{

}

Sprite * Tower::getSprite()
{
			return _instance;
}

int Tower::getLife()
{
			return _life;
}

void Tower::loseLife()
{
			--_life;
}

int Tower::getPos()
{
			return _pos;
}

Rect Tower::getBoundingBox()
{
			auto rectBak = _instance->getBoundingBox();
			Vec2 pos = convertToWorldSpace(rectBak.origin);
			Rect rect = Rect(pos.x, pos.y, rectBak.size.width ,rectBak.size.height);
			return rect;

}





