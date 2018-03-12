#include "CellsLayer.h"

CellsLayer::CellsLayer()
{
}

CellsLayer::~CellsLayer()
{
}

bool CellsLayer::init()
{
			if (!Layer::init())
			{
						return false;
			}
			auto ret = false;
			do 
			{
#ifdef _Test_
						std::string shader1 = FileUtils::getInstance()->getStringFromFile("example_GreyScale.fsh");
						GLProgramCache::getInstance()->addGLProgram(GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, shader1.c_str()), "grey_effect");
						std::string shader2 = FileUtils::getInstance()->getStringFromFile("example_LightScale.fsh");
						GLProgramCache::getInstance()->addGLProgram(GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, shader2.c_str()), "light_effect");
#endif //_Test_
						//初始化格子模块
						initCells();
						displayCells();
						//添加动态数组
						//添加可变长十字链表
						//添加寻路算法
						
						//auto eventDispa = Director::getInstance()->getEventDispatcher();
						auto listen = EventListenerTouchOneByOne::create();
						listen->onTouchBegan = CC_CALLBACK_2(CellsLayer::onTouchBegan, this);
						listen->onTouchMoved = CC_CALLBACK_2(CellsLayer::onTouchMoved, this);
						listen->onTouchEnded = CC_CALLBACK_2(CellsLayer::onTouchEnded, this);
						listen->onTouchCancelled = CC_CALLBACK_2(CellsLayer::onTouchCancelled, this);
						_eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);
						listen->setSwallowTouches(false);
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
			if (_supCell.size() >= 7)
			{
						return;
			}
			for (int col = _supCell.size(); col < 7; ++col)
			{
						auto randcol = static_cast<CellsColor>(rand() % 7);
						auto cel = createCells(randcol);
						_supCell.push_back(cel);
			}
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

void CellsLayer::checkCells()
{
}

void CellsLayer::showLightCells(CellsColor col)
{
			for (auto cells : _displayCell)
			{
						for (auto cell : cells)
						{
									if (cell->getColor()!=col)
									{
												GLProgramCache::getInstance()->addGLProgram(cell->getSprite()->getGLProgram(), "normal_effect");
												cell->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("grey_effect"));																					
									}
						}
			}
}

void CellsLayer::recoverLightCells(CellsColor col)
{
			for (auto cells : _displayCell)
			{
						for (auto cell : cells)
						{
									if (cell->getColor() != col)
									{
												//GLProgramCache::getInstance()->addGLProgram(cell->getSprite()->getGLProgram(), "normal_effect");
												cell->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("normal_effect"));
									}
						}
			}
}

bool CellsLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
			auto ret = false;
			do 
			{
						//检索触摸地方，如果是格子，继续
						{
									for (auto cells : _displayCell)
									{
												for (auto cell : cells)
												{
															if (cell->getBoundingBox().containsPoint(touch->getLocation()))
															{
																		showLightCells(cell->getColor());
																		
																		return true;
															}
												}
									}
						}
						//检索出显示格子中相同颜色的格子，高亮

						ret = true;
			} while (0);
			return ret;
}

void CellsLayer::onTouchMoved(Touch * touch, Event * unused_event)
{
			//移动中，如果没有选择格子，那么不做任何事情
			//如果是格子，判断颜色是否相同，如果相同，加入链表，并继续判断，否则不作处理
}

void CellsLayer::onTouchEnded(Touch * touch, Event * unused_event)
{
			//结算，如果所选格子都是相同颜色，那么消除格子，清除链表，并检查格子，然后补充格子，然后补充备用格子
			{
						for (auto cells : _displayCell)
						{
									for (auto cell : cells)
									{
												if (cell->getBoundingBox().containsPoint(touch->getStartLocation()))
												{
															recoverLightCells(cell->getColor());														
												}
									}
						}
			}
}

void CellsLayer::onTouchCancelled(Touch * touch, Event * unused_event)
{
			//取消，那么清除链表，恢复选择格子为FALSE；
}
