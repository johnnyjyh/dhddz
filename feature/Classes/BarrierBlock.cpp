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

void BarrierBlock::bindBarrierSprite(Sprite *sp, CellsColor _color, int life)
{
			_barrierBlock = sp;
			_life = life;
			_color = _color;
			setRow(-1);
			setColumn(-1);
			addChild(_barrierBlock, 35);
}

Sprite * BarrierBlock::getSprite()
{
			return _barrierBlock;
}

void BarrierBlock::loseLife()
{
			--_life;
}

int BarrierBlock::getLife()
{
			return _life;
}

int BarrierBlock::getColor()
{
			return _color;
}

bool BarrierBlock::isCanSelected()
{
			return _isCanSelected;
}
