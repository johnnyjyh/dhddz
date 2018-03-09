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
			_col = col;
			_isSelected = isSel;
}

Sprite *Cells::getSprite()
{
			return _instance;
}

Rect Cells::getBoundingBox()
{
			auto rectbak = _instance->getBoundingBox();
			auto pos = convertToWorldSpace(rectbak.origin);
			auto rect = Rect(pos.x, pos.y, rectbak.size.width, rectbak.size.height);
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
