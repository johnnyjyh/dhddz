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
			_instance = sp;
			_life = life;
			_color = _color;
			setRow(-1);
			setColumn(-1);
			addChild(_instance, 35);
}

//Sprite * BarrierBlock::getSprite()
//{
//			return _barrierBlock;
//}
//
//void BarrierBlock::loseLife()
//{
//			--_life;
//}
//
//int BarrierBlock::getLife()
//{
//			return _life;
//}
//
//CellsColor BarrierBlock::getColor()
//{
//			return _color;
//}
//
bool BarrierBlock::isCanSelected()
{
			return _isCanSelected;
}

Rect BarrierBlock::getBoundingBox()
{
			auto rectbak = _instance->getBoundingBox();
			auto pos = convertToWorldSpace(rectbak.origin);
			return Rect(pos.x + rectbak.size.width / 6, pos.y + rectbak.size.height / 6, rectbak.size.width / 1.5, rectbak.size.height / 1.5);
}
