#include "BarrierBlock.h"



BarrierBlock::BarrierBlock()
{
}


BarrierBlock::~BarrierBlock()
{
}

BarrierBlock * BarrierBlock::create()
{
			BarrierBlock *ret = new (std::nothrow) BarrierBlock;
			if (ret)
			{
						ret->autorelease();
			}
			else
			{
						delete ret;
						ret = nullptr;
			}
			return ret;
}

void BarrierBlock::bindBarrierSprite(Sprite * sp, int life, int typebar)
{
			_barrierBlock = sp;
			_life = life;
			_type = typebar;
			setRow(-1);
			setColumn(-1);
			addChild(_barrierBlock, 35);
}
