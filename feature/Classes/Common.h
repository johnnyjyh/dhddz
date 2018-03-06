#ifndef __Common_H__
#define __Common_H__
#define _Test_
#include "cocos2d.h"
USING_NS_CC;

#define winSize (Director::getInstance()->getWinSize())
#define randPos (rand()%5)
#define amendMonsterPositon(index) (index*winSize.width/5+winSize.width/10)


enum MonsterZorder
{
			monsterZ1 = 1,
};

enum MonsterLife
{
			monsterL1 = 1,
};

enum MonsterSpeed
{
			monsterS1 = 1,
};

enum Score
{
			monsterScore1 = 1,
};



namespace TowerItem
{
			enum TowerOrignal
			{
						life = 1,
						damage = 1,
						speed = 1,
			};
};

class DrawSpriteFrame
{
public:
			static DrawNode * drawSpriteFrame(Sprite *sp)
			{

						auto draw = DrawNode::create();					
						draw->drawRect(Vec2(0,0), Vec2(sp->getBoundingBox().size), Color4F::GREEN);																		
						sp->addChild(draw);
						return draw;
			}
};


#endif