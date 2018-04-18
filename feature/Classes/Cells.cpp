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
			_color = col;
			_isSelected = isSel;
			setRow(-1);
			setColumn(-1);
			addChild(sp,30);
}

void Cells::addPlate()
{
			for (int i = 0; i < 4; ++i)
			{
						if (_usablePlate[i])
						{
									//根据血量选择精灵
									//初始化精灵
									//设置位置
									//添加精灵
						}
			}
}

Sprite *Cells::getSprite()
{
			return _instance;
}

Rect Cells::getBoundingBox()
{
			auto rectbak = _instance->getBoundingBox();
			auto pos = convertToWorldSpace(rectbak.origin);			
			return Rect(pos.x + rectbak.size.width / 6, pos.y + rectbak.size.height / 6, rectbak.size.width / 1.5, rectbak.size.height / 1.5);
}

CellsColor Cells::getColor()
{
			return _color;
}

bool Cells::isSelected()
{
			return _isSelected;
}

bool Cells::isCanSelected()
{
			return _isCanSelected;
}

void Cells::loseLife()
{
			--_life;
}

int Cells::getLife()
{
			return _life;
}

void Cells::updateCell()
{

			//更新格子主精灵状态
			//更新plate状态
}
