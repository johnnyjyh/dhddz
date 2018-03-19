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
<<<<<<< HEAD
			setRow(-1);
			setColumn(-1);
=======
>>>>>>> 1930810ec5c27a97ee53f9f502973a917eeed6c8
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
<<<<<<< HEAD
			auto rect = Rect(pos.x+ rectbak.size.width /6, pos.y+ rectbak.size.height /6, rectbak.size.width/1.5, rectbak.size.height/1.5);
=======
			auto rect = Rect(pos.x, pos.y, rectbak.size.width, rectbak.size.height);
>>>>>>> 1930810ec5c27a97ee53f9f502973a917eeed6c8
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
