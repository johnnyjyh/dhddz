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
						//��ʼ������ģ��
						initCells();
						displayCells();
						
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

Cells * CellsLayer::createCells(int col)
{
			auto cel = Cells::create();
			if (col < redProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_red.png"), red, false);
			}
			else if (col < redProbability + pinkProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_pink.png"), pink, false);
			}
			else if (col < redProbability + pinkProbability + yellowProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_yellow.png"), yellow, false);
			}
			else if (col < redProbability + pinkProbability + yellowProbability + greenProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_ green.png"), green, false);
			}
			else if (col < redProbability + pinkProbability + yellowProbability + greenProbability + blueProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_blue.png"), blue, false);
			}
			else if (col < redProbability + pinkProbability + yellowProbability + greenProbability + blueProbability + blueandProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_blueand.png"), blueand, false);
			}
			else if (col < redProbability + pinkProbability + yellowProbability + greenProbability + blueProbability + blueandProbability + purpleProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_ purple.png"), purple, false);
			}
			else
			{
						
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
												auto randcol =(rand() % 100);											
												auto cel = createCells(randcol);
												cel->setRow(row);
												cel->setColumn(col);
												_supDisplayCell[row].push_back(cel);
									}
									_displayCell.push_back(_supDisplayCell[row]);
						}
						
						for (int col = 0; col < 7; ++col)
						{
									auto randcol =(rand() % 100);
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

		
			for (auto cells : _displayCell)
			{
						
						for (auto cell : cells)
						{
									
#ifdef _Test_

									cell->getSprite()->setScale(0.5);
									
#endif //_Test_
									//cell->getSprite()->setAnchorPoint(Vec2::ZERO);
									cell->setPosition(Vec2((getSingleTiledSize.x)*(cell->getColumn()+0.5), (getSingleTiledSize.y + (tileinterval - 95 *0.5))*(cell->getRow()+0.5)));
									
								
									addChild(cell,30);
									
						}
						
			}


}

bool CellsLayer::isCanDestroyCells()
{
			auto ret = false;
			do 
			{
						if (_touchMoveCells.size() > 2)
						{
									ret = true;
						}
			} while (0);
			return ret;
}

void CellsLayer::destroyCells()
{
			if (isCanDestroyCells())
			{
						for (auto desCells : _touchMoveCells)
						{
									/*for (auto cells : _displayCell)
									{
												int ret = 0;
												for (auto &cell : cells)
												{
															if (cell == desCells)
															{
																		cell = nullptr;
																		ret = 1;
																		break;
															}
												}
												if (ret == 1)
												{
															break;
												}
									}*/
									desCells->setVisible(false);
									desCells->loseLife();
									_desCell.push_back(desCells);
						}
						preCells();
			}

}

void CellsLayer::supplyCells()
{
			if (_supCell.size() >= 7)
			{
						return;
			}
			for (int col = _supCell.size(); col < 7; ++col)
			{
						auto randcol = (rand() % 100);
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

void CellsLayer::preCells()
{

			if (_desCell.size())
			{
						for (auto desCell : _desCell)
						{
									for (int i = desCell->getRow()+1; i < 5; ++i)
									{
												/*auto cell = std::find_if(_displayCell.at(desCell->getRow()).begin(), _displayCell.at(desCell->getRow().end()), 
															[&](Cells *cell) {
															if (desCell == cell)
															{
																		return true;
															}
															else
															{
																		return false;
															}
												});*/
												auto cell = findCell(desCell->getColumn(), i);
												if (cell->getLife()>0)
												{
															moveCell(cell,desCell->getColumn(), i, desCell->getColumn(), i-1);
															cell->swap(findCell(desCell->getColumn(), i-1));
															//desCell->removeAllChildren();
															//desCell->removeFromParentAndCleanup(true);
												}
												else 
												{
															log("2222222222222");
												}

									}
								
									auto cell = std::find_if(_displayCell.at(desCell->getRow()).begin(), _displayCell.at(desCell->getRow().end()),
												[&](Cells *cell) ->bool{
												if (desCell == cell)
												{
															return true;
												}
												else
												{
															return false;
												}
									});
									if ((*cell)->getLife()<1)
									{
												log("1111111111111111");

												*cell = getNewCellForSupCell();
												(*cell)->setColumn(desCell->getColumn());
												(*cell)->setRow(i);
												(*cell)->setPosition(coordinateToVec2(cell->getColumn(), cell->getRow()));
												addChild(*cell);
												moveCell(*cell, (*cell)->getColumn(), (*cell)->getRow(), (*cell)->getColumn(), i);
									}

									
									supplyCells();
									desCell->removeAllChildren();
									desCell->removeFromParentAndCleanup(true);
						}
						_desCell.clear();
			}

}

Cells * CellsLayer::findCell(int col, int row)
{

			return _displayCell[row][col];
}

Cells * CellsLayer::getNewCellForSupCell()
{
			auto cell = _supCell.back();
			_supCell.pop_back();
			return cell;
}



void CellsLayer::setCellsToScreen(int col, int row)
{
}

void CellsLayer::linkLineInGrid(int col1, int row1, int col2, int row2)
{
			Vec2 pos1, pos2;
			pos1.set(coordinateToVec2(col1, row1));
			pos2.set(coordinateToVec2(col2, row2));
			auto line = DrawNode::create();
			line->drawLine(pos1, pos2,Color4F::BLACK);
			_linkLineCache.push_back(line);
			addChild(line,10001);
}



void CellsLayer::checkCells()
{

}

Vec2 CellsLayer::coordinateToVec2(int col, int row)
{
			Vec2 vec(getSingleTiledSize.x*(col+0.5), (getSingleTiledSize.y + (tileinterval - 95 * 0.5))*(row+0.5));
			return vec;
}

int *CellsLayer::vec2ToCoordinate(Vec2 vec)
{		
			transformArr[0] = vec.x / getSingleTiledSize.x - 0.5;
			transformArr[1] = vec.y / (getSingleTiledSize.y + (tileinterval - 95 * 0.5))-0.5;
			return transformArr;
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
									else
									{
												if (!cell->isSelected())
												{														
															_touchCells.push_back(cell);
												}
												GLProgramCache::getInstance()->addGLProgram(cell->getSprite()->getGLProgram(), "dis_normal_effect");
												cell->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("light_effect"));
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
									else
									{
												cell->_isSelected = false;
												cell->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("dis_normal_effect"));
									}
						}
			}
}

void CellsLayer::moveCell(Cells * cell, int col1, int row1, int col2, int row2)
{
			if (cell != nullptr)
			{
						auto moveto = MoveTo::create(0.5, Vec2((getSingleTiledSize.x)*(col2 + 0.5), (getSingleTiledSize.y + (tileinterval - 95 * 0.5))*(row2 + 0.5)));
						cell->runAction(moveto);
						cell->setColumn(col2);
						cell->setRow(row2);
			}
}

bool CellsLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
			auto ret = false;
			do 
			{
						//���������ط�������Ǹ��ӣ�����
						{
									assert(_displayCell.size() > 0);
									for (auto cells : _displayCell)
									{
												for (auto cell : cells)
												{
															if (cell->getBoundingBox().containsPoint(touch->getLocation()))
															{
																		cell->_isSelected = true;
																		showLightCells(cell->getColor());
																		_touchCells.push_back(cell);
																		_touchMoveCells.push_back(cell);
																		return true;
															}
												}
									}

								

						}
						//��������ʾ��������ͬ��ɫ�ĸ��ӣ�����

						ret = true;
			} while (0);
			return ret;
}

void CellsLayer::onTouchMoved(Touch * touch, Event * unused_event)
{
			//�ƶ��У����û��ѡ����ӣ���ô�����κ�����
			//����Ǹ��ӣ��ж���ɫ�Ƿ���ͬ�������ͬ�����������������жϣ�����������
			for (auto touchlist : _touchCells)
			{ 
						if (touchlist->getBoundingBox().containsPoint(touch->getLocation()))
						{									
												if (touchlist ->isSelected() || pow(touchlist->getRow() - _touchMoveCells.back()->getRow(), 2) + pow(touchlist->getColumn() - _touchMoveCells.back()->getColumn(), 2) > 2)
												{
															return;
												}											
												touchlist->_isSelected = true;
												linkLineInGrid(touchlist->getColumn(), touchlist->getRow(), _touchMoveCells.back()->getColumn(), _touchMoveCells.back()->getRow());
												_touchMoveCells.push_back(touchlist);
												log("moveCellsVec:%d", _touchMoveCells.size());
												return;

						}
			}

}

void CellsLayer::onTouchEnded(Touch * touch, Event * unused_event)
{
			//���㣬�����ѡ���Ӷ�����ͬ��ɫ����ô�������ӣ���������������ӣ�Ȼ�󲹳���ӣ�Ȼ�󲹳䱸�ø���
			{
						if (_touchCells.size() > 0)
						{
									recoverLightCells(_touchCells.back()->getColor());
						}

						if (_linkLineCache.size())
						{
									for (auto line : _linkLineCache)
									{
												line->removeFromParentAndCleanup(true);
									}
									_linkLineCache.clear();
						}
						if (_touchCells.size())
						{
									_touchCells.clear();
						}
						if (_touchMoveCells.size())
						{
									destroyCells();
									_touchMoveCells.clear();
						}
			}
}

void CellsLayer::onTouchCancelled(Touch * touch, Event * unused_event)
{
			//ȡ������ô��������ָ�ѡ�����ΪFALSE��
}
