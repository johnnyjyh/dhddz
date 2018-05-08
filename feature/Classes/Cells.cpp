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

//deprecated_attribute
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

void Cells::bindNewCellsSprite(CellsColor color, int col, int row)
{
			if (_instance == nullptr)
			{
						_color = color;
						_instance = catchColorForNewSprite();
						//auto pos = coordinateToVec2(col, row);
						//_instance->setPosition(this->convertToNodeSpace(pos));	
						//_instance->setGlobalZOrder(getColor() + globalZorder::CellsZorder);
						_instance->setScale(0.5f);
						this->addChild(_instance, getColor() + globalZorder::CellsZorder);
						switch (getColor())
						{
						case CellsColor::red:
						case CellsColor::pink:
						case CellsColor::yellow:
						case CellsColor::green:
						case CellsColor::blue:
						case CellsColor::blueand:
						case CellsColor::purple:
									setLife(1);
									_isCanSelected = true;
									_isMoving = false;
									break;
						case CellsColor::snowBlock:
									_isSelected = false;
									setLife(1);
									_isCanSelected = false;
									break;
						}
			}
			else
			{

			}
			
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

		/*	_isSelected = cell->_isSelected;
			_color = cell->getColor();
			_isCanSelected = cell->_isCanSelected;
			_isUsedLogic = cell->_isUsedLogic;
			_isTouchBack = cell->_isTouchBack;*/

			if (_life > 0)
			{

						_instance = catchColorForNewSprite();	
						_instance->setPosition(convertToNodeSpace(cell->convertToWorldSpace(cell->getSprite()->getPosition())) );
						//_instance = cell->getSprite();
						addChild(_instance,35);
						_instance->setGlobalZOrder(getColor() + globalZorder::CellsZorder);
						_instance->setScale(0.5f);
						
						
					//	auto posbak = vec2ToCoordinate(cell->getPosition());
					//	log("source:%d,%d moveto: %0.0f,%0.0f",getColumn(),getRow(),posbak[0],posbak[1]);
						//_instance->setPosition(cell->getPosition());
			}		

			//_instance->setPosition(getPosition());

}

void Cells::pullCellsSprite()
{		
			if (_instance == nullptr)
			{
						return;
			}
			//_isCanSelected = false;
			_instance->removeAllChildrenWithCleanup(true);
			_instance = nullptr;
			//setLife(0);
			
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
			default:
						break;
			}
			return spr;
}

void Cells::pushMoveVec(std::vector<Vec2> & moveVec)
{
			//if (_mMoveVec.size())
			//{
			//			_mMoveVec.clear();
			//}
			if (moveVec.size())
			{
						for (auto vec : moveVec)
						{
									_moveVec.push_back(vec);
						}
			}
}
