#include "Cells.h"



Cells::Cells()
{
}


Cells::~Cells()
{
}

Cells * Cells::create()
{
			auto ret = new Cells();
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

void Cells::bindCellsSprite(Sprite * sp, CellsColor col, bool isSel)
{
			_instance = sp;
			_life = 1;
			_col = col;
			_isSelected = isSel;
			setRow(-1);
			setColumn(-1);
			addChild(sp,30);
}

Sprite *Cells::getSprite()
{
			return _instance;
}

Rect Cells::getBoundingBox()
{
			auto rectbak = _instance->getBoundingBox();
			auto pos = convertToWorldSpace(rectbak.origin);
			auto rect = Rect(pos.x+ rectbak.size.width /6, pos.y+ rectbak.size.height /6, rectbak.size.width/1.5, rectbak.size.height/1.5);
			return rect;
}

CellsColor Cells::getColor()
{
			return _col;
}

bool Cells::isSelected()
{
			return _isSelected;
}

void Cells::loseLife()
{
			--_life;
}

int Cells::getLife()
{
			return _life;
}
