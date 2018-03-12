#include "CellsLayer.h"

CellsLayer::CellsLayer()
{
}

CellsLayer::~CellsLayer()
{
}

bool CellsLayer::init()
{
			auto ret = false;
			do 
			{
						//初始化格子模块
						initCells();
						displayCells();
						//添加动态数组
						//添加可变长十字链表
						//添加寻路算法
						
						ret = true;
			} while (0);
			return ret;
}

Cells * CellsLayer::createCells(CellsColor col)
{
			auto cel = Cells::create();
			switch (col)
			{
			case red:
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_red.png"), col, false);
						break;
			case pink:
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_pink.png"), col, false);
						break;
			case yellow:
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_yellow.png"), col, false);
						break;
			case green:
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_ green.png"), col, false);
						break;
			case blue:
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_blue.png"), col, false);
						break;
			case blueand:
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_blueand.png"), col, false);
						break;
			case purple:
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_ purple.png"), col, false);
						break;
			default:
						break;
			}
			return cel;
}

bool CellsLayer::initCells()
{
			auto ret = false;
			do 
			{

						for (int row = 0; row < 5; ++row)
						{									
									for (int col = 0; col < 7; ++col)
									{
												auto randcol = static_cast<CellsColor>(rand() % 7);											
												auto cel = createCells(randcol);
												_supDisplayCell[row].push_back(cel);
									}
									_displayCell.push_back(_supDisplayCell[row]);
						}
						
						for (int col = 0; col < 7; ++col)
						{
									auto randcol = static_cast<CellsColor>(rand() % 7);
									auto cel = createCells(randcol);
									_supCell.push_back(cel);
						}

						ret = true;
			} while (0);
			return ret;
}

void CellsLayer::displayCells()
{
			if (!isPreCells())
			{
						
						return;
			}
			int i = 0, j = 0;
			for (auto cells : _displayCell)
			{
						j = 0;
						for (auto cell : cells)
						{
									
#ifdef _Test_

									cell->getSprite()->setScale(0.5);
									
#endif //_Test_
									cell->getSprite()->setAnchorPoint(Vec2::ZERO);
									cell->setPosition(Vec2((getSingleTiledSize.x)*j, (getSingleTiledSize.y + (tileinterval - 95 * 0.5))*i));
									
								
									addChild(cell,30);
									++j;
						}
						++i;
			}


}

bool CellsLayer::isCanDestroyCells()
{
			return false;
}

void CellsLayer::destroyCells()
{
}

void CellsLayer::supplyCells()
{
}

bool CellsLayer::isPreCells()
{
			auto ret = false;
			do 
			{
						for (auto cells : _displayCell)
						{
									for (auto cell : cells)
									{
												if (cell==nullptr)
												{
															return ret;
												}
									}
						}
						ret = true;
			} while (0);
			return ret;
}

void CellsLayer::setCellsToScreen(int col, int row)
{
}

bool CellsLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
			return false;
}

void CellsLayer::onTouchMoved(Touch * touch, Event * unused_event)
{
}

void CellsLayer::onTouchEnded(Touch * touch, Event * unused_event)
{
}

void CellsLayer::onTouchCancelled(Touch * touch, Event * unused_event)
{
}
