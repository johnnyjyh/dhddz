#include "Monster.h"



Monster::Monster():_monster_instance(nullptr),_life(0),_speed(0)
{
			
}


Monster::~Monster()
{
}

Monster *Monster::create( )
{
			auto pRet = new Monster();
			pRet->autorelease();
			return pRet;
}

void Monster::BindMonsterSprite(Sprite * sp, int life, int speed,int pos)
{
			_monster_instance = sp;
			_life = life;
			_pos = pos;
			_speed = speed;

#ifdef _Test_

#endif //_Test_
			addChild(sp, MonsterZorder::monsterZ1);
}

Sprite * Monster::getSprite()
{
			return _monster_instance;
}

int Monster::getLife()
{
			return _life;
}

void Monster::loseLife()
{
			--_life;
}

int Monster::getPos()
{
			return _pos;
}

Rect Monster::getBoundingBox()
{
			auto rectBak = _monster_instance->getBoundingBox();
			Vec2 pos = convertToWorldSpace(rectBak.origin);
			Rect rect = Rect(pos.x, pos.y, rectBak.size.width, rectBak.size.height);
			return rect;
}








