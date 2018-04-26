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
			_instance->setGlobalZOrder(getColor() + globalZorder::CellsZorder);
			_instance->setScale(0.5f);
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

void Cells::setLife(int life)
{
			_life = life;
}

void Cells::pushCellsSprite(Cells *cell)
{
			//int _life{ 1 };
			//bool _isSelected;
			//CellsColor _color;
			//Sprite* _instance;
			//bool _isCanSelected{ true };
			//bool _isUsedLogic{ false };
			//bool _isTouchBack{ false };

			_isSelected = cell->_isSelected;
			_color = cell->getColor();
			_isCanSelected = cell->_isCanSelected;
			_isUsedLogic = cell->_isUsedLogic;
			_isTouchBack = cell->_isTouchBack;

			if (_life > 0)
			{
						_instance = catchColorForNewSprite();					
						addChild(_instance,35);
						_instance->setGlobalZOrder(getColor() + globalZorder::CellsZorder);
						_instance->setScale(0.5f);
						//_instance->setPosition(cell->getPosition());
			}		

			//_instance->setPosition(getPosition());

}

void Cells::pullCellsSprite()
{		
			_isCanSelected = false;
			_instance->removeAllChildrenWithCleanup(true);
			this->removeChild(_instance, true);
			_instance = nullptr;
			setLife(0);
			
}

void Cells::updateCell()
{

			//更新格子主精灵状态
			//更新plate状态
}

Sprite *Cells::catchColorForNewSprite()
{
			Sprite *spr = nullptr;
			switch (this->getColor())
			{
			case CellsColor::red:
						spr =Sprite::createWithSpriteFrameName("operating_red.png");
						break;
			case CellsColor::pink:
						spr = Sprite::createWithSpriteFrameName("operating_pink.png");
						break;
			case CellsColor::yellow:
						spr = Sprite::createWithSpriteFrameName("operating_yellow.png");
						break;
			case CellsColor::green:
						spr = Sprite::createWithSpriteFrameName("operating_ green.png");
						break;
			case CellsColor::blue:
						spr = Sprite::createWithSpriteFrameName("operating_blue.png");
						break;
			case CellsColor::blueand:
						spr = Sprite::createWithSpriteFrameName("operating_blueand.png");
						break;
			case CellsColor::purple:
						spr = Sprite::createWithSpriteFrameName("operating_ purple.png");
						break;
			case CellsColor::snowBlock:
						spr = Sprite::createWithSpriteFrameName("operating_obstacle_004.png");
						break;
			}
			return spr;
}
