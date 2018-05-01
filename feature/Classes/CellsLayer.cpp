#include "CellsLayer.h"

CellsLayer::CellsLayer()
{
}

CellsLayer::~CellsLayer()
{
}

CellsLayer * CellsLayer::create()
{
			auto cellsLay = new (std::nothrow) CellsLayer;
			if (cellsLay && cellsLay->init())
			{
						cellsLay->autorelease();
			}
			else
			{
						delete cellsLay;
						cellsLay = nullptr;
			}
			return cellsLay;
}

auto CellsLayer::checkSnowBlock(std::list<Cells *> &cells)
{
			auto ret = false;
			do
			{
						
						if (_snowBlock.size())
						{
									
									for (auto block : _snowBlock)
									{	
												for (auto cell : cells)
												{
															if (abs(cell->getRow() - block->getRow()) + abs(cell->getColumn() - block->getColumn()) == 1)
															{
																		block->loseLife();
																		break;
															}
												}
												
									}							
						}
						ret = true;
			} while (0);
			return ret;
}

auto  CellsLayer::checkBarrier(std::list<Cells *> &cells)
{
			auto ret = false;
			do
			{
						CC_BREAK_IF(!checkSnowBlock(cells));
						ret = true;
			} while (0);
			return ret;
}

void CellsLayer::destroyBarrier()
{
			if (_snowBlock.size())
			{
						for (auto block = _snowBlock.begin(); block != _snowBlock.end();)
						{
									if (!(*block))
									{
												continue;
									}
									auto iter = _displayCell.begin();
									if ((*block)->getLife() <= 0)
									{
												CCASSERT((*block)->getColumn() <= 7, "destroy block get wrong column!");
												/*for (int i = 0; i < (*block)->getColumn(); ++i)
												{
															++iter;
												}
												auto blockbak = *block;
												auto iterblock = std::find(iter->begin(), iter->end(), *block);
												*iterblock = nullptr;*/
												(*block)->getSprite()->setVisible(false);
												(*block)->_isCanSelected = false;
												block = _snowBlock.erase(block);
												
												/*(blockbak)->removeAllChildren();
												(blockbak)->removeFromParentAndCleanup(true);
												(blockbak) = nullptr;*/
									}
									else
									{
												++block;
									}

						}
			}
			
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
						initClippingNode();//����cells�����ڸǷ����ϲ���fight����
#ifdef _Test_
						
#endif //_Test_
						addGreyAndLightShader();
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

Cells * CellsLayer::createCells(int randnum)
{
			auto cel = Cells::create();
			if (randnum < redProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_red.png"), red, false);
			}
			else if (randnum < redProbability + pinkProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_pink.png"), pink, false);
			}
			else if (randnum < redProbability + pinkProbability + yellowProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_yellow.png"), yellow, false);
			}
			else if (randnum < redProbability + pinkProbability + yellowProbability + greenProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_ green.png"), green, false);
			}
			else if (randnum < redProbability + pinkProbability + yellowProbability + greenProbability + blueProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_blue.png"), blue, false);
			}
			else if (randnum < redProbability + pinkProbability + yellowProbability + greenProbability + blueProbability + blueandProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_blueand.png"), blueand, false);
			}
			else if (randnum < redProbability + pinkProbability + yellowProbability + greenProbability + blueProbability + blueandProbability + purpleProbability)
			{
						cel->bindCellsSprite(Sprite::createWithSpriteFrameName("operating_ purple.png"), purple, false);
			}
			else
			{
						static_assert((redProbability + pinkProbability + yellowProbability + greenProbability + blueProbability + blueandProbability + purpleProbability) == 100, " redProbability + pinkProbability + yellowProbability + greenProbability + blueProbability + blueandProbability + purpleProbability !=100");
			}

			return cel;
}

bool CellsLayer::initCells()
{
			auto ret = false;
			do 
			{

						for (int col = 0; col < 7; ++col)
						{
									std::list<Cells *> listtemp;
									for (int row = 0; row < 5; ++row)
									{		


												if ((col == 3 || col==2)&& (row == 2 || row ==3))
												{
															auto bar = BarrierBlock::create();
															bar->bindBarrierSprite(Sprite::createWithSpriteFrameName("operating_obstacle_004.png"),snowBlock,snowBlockHealth);																													
															bar->setRow(row);
															bar->setColumn(col);
															listtemp.push_back(bar);
															_snowBlock.push_back(bar);
												}
												else
												{
															auto randnum = rand() % 100;
															auto cell = createCells(randnum);

															if (cell == nullptr)
															{
																		--row;
																		continue;
															}
															cell->setRow(row);
															cell->setColumn(col);
															listtemp.push_back(cell);
												}
									}
									_displayCell.push_back(listtemp);
						}
						//for (int col = 0; col < 7; ++col)
						//{
						//			auto randcol =(rand() % 100);
						//			auto cel = createCells(randcol);
						//			_supCell.push_back(cel);
						//}

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
									//cell->getSprite()->setScale(0.5);								
#endif //_Test_
									//cell->getSprite()->setAnchorPoint(Vec2::ZERO);
									cell->setPosition(Vec2((getSingleTiledSize.x)*(cell->getColumn()+0.5), (getSingleTiledSize.y + (tileinterval - 95 *0.5))*(cell->getRow()+0.5)));
									
									if (cell->getColor() == snowBlock)
									{
												_clipNode->addChild(cell, 31);
												continue;
									}
									_clipNode->addChild(cell,30);
									
						}
						
			}
			restoreStalemate();
			_isCanRunning = true;
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
						_isCanRunning = false;
						//�������
						_cellScore += _touchMoveCells.size();
						//�����ڵ���
						checkBarrier(_touchMoveCells);										
						//����������
						for (auto desCells : _touchMoveCells)
						{

									desCells->getSprite()->setVisible(false);
									desCells->_isCanSelected = false;
									desCells->loseLife();
									_desCell.push_back(desCells);
						}
						destroyBarrier();
						//preCells1();
						preCellsForCol();
						//this->preCells2();

						/*if (_desCell.size())
						{
									for (auto &desCell  : _desCell)
									{
												auto iter = _displayCell.begin();
												for (int i = 0; i < desCell->getColumn(); ++i)
												{
															++iter;
												}
												auto iterfind = find(iter->begin(), iter->end(), desCell);
												*iterfind = nullptr;
												desCell->removeAllChildren();
												desCell->removeFromParentAndCleanup(true);
												desCell = nullptr;
									}
									_desCell.clear();
						}*/
						_isCanRunning = true;
						restoreStalemate();
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
			if (_displayCell.size() > 0)
			{
						auto colRecord = 0;
						for (auto &cells : _displayCell)
						{
									if (cells.size() == 5)
									{
												++colRecord;
												continue;
									}
									else if (cells.size() < 5 && cells.size() >= 0)
									{
												auto cell = cells.begin();
												for (int row = 0; row < 5; ++row)
												{
															if (static_cast<unsigned int>(row) < cells.size())
															{																	
																		if ((*cell)->getRow() == row )
																		{
																					++cell;
																					continue;
																		}																	
																		(*cell)->setRow(row);
																		moveCell((*cell), 0, 0, colRecord, row);
																		++cell;
															}
															else
															{
																		auto cel = getNewCellForSupCell();
																		cells.push_back(cel);
																		cel->setRow(row);
																		cel->setColumn(colRecord);
																		cel->setPosition(coordinateToVec2(colRecord, 5));
																		_clipNode->addChild(cel);
																		moveCell(cel, 0, 0, cel->getColumn(), cel->getRow());
															}

												}
									}
									else
									{
												assert(cells.size() > 5);
									}
									++colRecord;
						}

						restoreStalemate();
						_isCanRunning = true;
			}
}

void CellsLayer::preCells1()
{
			if (_displayCell.size() > 0)
			{
						auto colRecord = 0;
						auto row = 0;
						for (auto cells = _displayCell.begin(); cells != _displayCell.end();)
						{
									row = 0;

									for (auto cell = cells->begin(); cell != cells->end();)
									{

												if ((*cell) != nullptr && (*cell)->getLife() <= 0)
												{
															auto getcell = getUsableCell1(cell, (*cell)->getColumn(), (*cell)->getRow());
															if (getcell != nullptr)
															{
																		*cell = getcell;
																		moveCell((*cell), 0, 0, colRecord, row);
																		preCells1();
															}
												}

												++row;
												++cell;

									}
									++cells;
									++colRecord;
						}		
						_isCanRunning = true;
			}
}

void CellsLayer::preCells2()
{
			if (_displayCell.size() > 0)
			{
						auto colRecord = 0;
						auto row = 0;
						for (auto cells = _displayCell.begin(); cells != _displayCell.end();)
						{
									row = 0;

									for (auto cell = cells->begin(); cell != cells->end();)
									{

												if ((*cell) != nullptr && (*cell)->getLife() <= 0)
												{
															auto getcell = getUsableCell(cell, (*cell)->getColumn(), (*cell)->getRow());
															if (getcell != nullptr)
															{

																		*cell = getcell;
																		moveCell((*cell), 0, 0, colRecord, row);
																		preCells2();
															}
												}

												++row;
												++cell;

									}
									++cells;
									++colRecord;
						}
						

						_isCanRunning = true;
			}

}

void CellsLayer::preCellsForCol()
{
			if (_displayCell.size() > 0)
			{
						auto colRecord = 0;
						auto row = 0;
						for (auto cells = _displayCell.begin(); cells != _displayCell.end();)
						{
									row = 0;

									for (auto cell = cells->begin(); cell != cells->end();)
									{

												if ((*cell) != nullptr && (*cell)->getLife() <= 0)
												{
															auto getcell = getUsableCol(cell, (*cell)->getColumn(), (*cell)->getRow());
															if (getcell != nullptr)
															{
																		if (_cellRemoveQueue.size())
																		{

																					/*	for (auto removecell : _cellRemoveQueue)
																						{
																									log("revemo:%d,%d", removecell->getColumn(), removecell->getRow());
																						}
																						log("***************************************");*/
																					//�ƶ���Ҫ�ƶ��ĸ���
																					removeUsableCells();

																		}
																		
															}
															_cellRemoveQueue.clear();
												}

												++row;
												++cell;

									}
									++cells;
									++colRecord;
						}


						_isCanRunning = true;
			}

			
			for (auto cells : _displayCell)
			{
						for (auto cell : cells)
						{
									if (cell->_isMoving)
									{

												if (cell->_moveVec.size())
												{
															if (cell->getSprite() == nullptr)
															{
																		continue;
															}
															for (auto moveto = cell->_moveVec.begin(); moveto != cell->_moveVec.end(); ++moveto)
															{
																		cell->_moveActionVec.pushBack(MoveTo::create(1.0f,cell->convertToNodeSpace(*moveto)));
															}
															auto seq = Sequence::create(cell->_moveActionVec);
															cell->getSprite()->runAction(seq);
															cell->_moveVec.clear();
															cell->_moveActionVec.clear();
															cell->_isMoving = false;
												}
									}
						}
			}
}

Cells *CellsLayer::getUsableCol(std::list<Cells*>::iterator & souceCell, int col, int row)
{
			if (col < 0 || col>6 || row > 4 || row < 0)
			{
						return nullptr;
			}
			else
			{
						Cells *dest = nullptr;
						for (auto cells : _displayCell)
						{
									for (auto cell : cells)
									{
												if (cell == nullptr)
												{
															continue;
												}
												if (cell->getRow() == row && cell->getColumn() == col)
												{
															dest = cell;
												}
									}
									if (dest != nullptr)
									{
												break;
									}
						}

						if (dest == nullptr || ((dest->getColor() >= snowBlock)  && (dest->getLife() > 0)))
						{
									return nullptr;
						}
						else
						{
									_cellRemoveQueue.push_back(dest);
									if (dest->getRow() == 4)
									{
												return dest;
									}
									dest = getUsableCol(souceCell, col, row + 1);
									if (dest == nullptr)
									{
												if (abs(col - 1 - (*souceCell)->getColumn()) <= abs(col + 1 - (*souceCell)->getColumn()))
												{
															dest = getUsableCol(souceCell, col - 1, row + 1);
												}
												else
												{
															dest = getUsableCol(souceCell, col + 1, row + 1);
												}
									}

									if (dest == nullptr)
									{
												if (abs(col + 1 - (*souceCell)->getColumn()) <= abs(col - 1 - (*souceCell)->getColumn()))
												{
															dest = getUsableCol(souceCell, col + 1, row + 1);
												}
												else
												{
															dest = getUsableCol(souceCell, col - 1, row + 1);
												}
									}
									return dest;								
						}


			}

}

void CellsLayer::removeUsableCells()
{
			//�û����ӣ�����ȡ�����ַ����
			int recordTime = 0;
			for (auto cell : _cellRemoveQueue)
			{
						if (cell->getLife() > 0)
						{
									Cells *cellmoveto = nullptr;
									for (auto cellvec : _cellRemoveQueue)
									{
												if (cellvec == cell && cellvec->getLife()>0)
												{
															if (_cellVec2RemoveQueue.size())
															{
																	/*	if (cellvec->_isMoving)
																		{
																					_cellVec2RemoveQueue.clear();
																					continue;
																		}
																		Vector<FiniteTimeAction *> moves;

																		for (auto iter = _cellVec2RemoveQueue.rbegin(); iter != _cellVec2RemoveQueue.rend(); ++iter)
																		{
																					log("%f,%f", (*iter).x, (*iter).y);
																					auto movea = static_cast<FiniteTimeAction *>(MoveTo::create(1.0f, cellvec->convertToNodeSpace(*iter)));
																					moves.pushBack(movea);
																		}

																		auto seq = Sequence::create(moves);
																		auto func = CallFuncN::create([cellmoveto](Node *node)
																		{
																					Cells *par = static_cast<Cells *>(node->getParent());
																					par->_isMoving = false;

																		});
																		auto seq2=Sequence::create(seq,func,nullptr);
																		cellvec->_isMoving = true;
																		cellvec->getSprite()->runAction(seq2);
																		swapCells(cellvec, cellmoveto);*/
																		
																		cellvec->_isMoving = true;
																		cellvec->pushMoveVec(_cellVec2RemoveQueue);
																		swapCells(cellvec, cellmoveto);
																		
															}
															break;
												}
												else
												{
															
															if (cellvec->getLife() > 0)
															{
																		
																		continue;
															}
															else
															{
																		_cellVec2RemoveQueue.insert(_cellVec2RemoveQueue.begin(), (cellvec->convertToWorldSpace(cellvec->getSprite()->getPosition())));

																		if (cellmoveto == nullptr)
																		{
																					
																					cellmoveto = cellvec;
																		}
																		
															}
												}
									}
									_cellVec2RemoveQueue.clear();
									
						}					
			}
			
}

void CellsLayer::swapCells(Cells * sourceCell, Cells * destCell)
{
			log("**********************************");
			log("source:%d,%d,%d  dest:%d,%d,%d", sourceCell->getColumn(), sourceCell->getRow(), sourceCell->getLife(),destCell->getColumn(), destCell->getRow(),destCell->getLife());
			//����block ��������		
			auto lifebak = destCell->getLife();
			auto isSelectedbak = destCell->_isSelected;
			auto colorbak = destCell->getColor();
			auto isCanSelected = destCell->isCanSelected();
			auto isMovintBak = destCell->_isMoving;
			//sourceCell->pullCellsSprite();
			sourceCell->getSprite()->setVisible(false);

			destCell->pushMoveVec(sourceCell->_moveVec);
			sourceCell->_moveVec.clear();
		
			
			destCell->pullCellsSprite();
			destCell->setLife(sourceCell->getLife());	
			destCell->_isSelected = sourceCell->_isSelected;
			destCell->_color = sourceCell->getColor();
			destCell->_isCanSelected = sourceCell->isCanSelected();
			destCell->_isMoving = sourceCell->_isMoving;
			destCell->pushCellsSprite(sourceCell);
			

			sourceCell->setLife(lifebak);
			sourceCell->_isSelected = isSelectedbak;
			sourceCell->_color = colorbak;
			sourceCell->_isCanSelected= isCanSelected;
			sourceCell->_isMoving = isMovintBak;
			log("source:%d,%d,%d  dest:%d,%d,%d", sourceCell->getColumn(), sourceCell->getRow(), sourceCell->getLife(), destCell->getColumn(), destCell->getRow(), destCell->getLife());
			log("**********************************");
			
}

Cells * CellsLayer::getUsableCell1(std::list<Cells*>::iterator & souceCell, int col, int row)
{
			if (col < 0 || col>6 || row > 4 || row < 0)
			{
						return nullptr;
			}
			else
			{
						auto cells = _displayCell.begin();

						for (int i = 0; i < col; ++i)
						{

									++cells;
									if (cells == _displayCell.end())
									{
												return nullptr;
									}
						}

						auto cell = (*cells).begin();
						for (int i = 0; i < row; ++i)
						{
									++cell;
									if (cell == cells->end())
									{
												return nullptr;
									}
						}

						Cells *celltemp1 = nullptr;

						if ((*cell)->getLife() <= 0)
						{
									celltemp1 = getUsableCell1(souceCell, col, row + 1);
									return celltemp1;
						}
						else
						{
									if ((*cell)->getColor() >= snowBlock)
									{
												return nullptr;
									}
									else
									{
												Cells *cellbak = *cell;
												(*souceCell)->setRow(cellbak->getRow());
												*cell = *souceCell;
												return cellbak;
									}
						}


			}

}

Cells  *CellsLayer::getUsableCell(std::list<Cells *>::iterator  souceCell, std::list<Cells *>::iterator  &destCellRef, std::list<Cells *>::iterator  cellBak)
{
			/*if (((*souceCell)->getColor()>=snowBlock&& (*souceCell)->getLife()>0) && ((*destCellRef)->getColor()>=snowBlock&& (*souceCell)->getLife()>0))
			{
						return nullptr;
			}
			else if ( (*destCellRef)!=nullptr && ((*destCellRef)->getColor() < snowBlock && (*destCellRef)->getLife()>0))
			{
						Cells* cellb = *destCellRef;
						(*cellBak)->setColumn(cellb->getColumn());
						(*cellBak)->setRow(cellb->getRow());
						*destCellRef = *cellBak;
						return cellb;
			}
			else
			{
						std::list<Cells *>::iterator  destCell = destCellRef;
						auto col = (*destCell)->getColumn();
						auto row = (*destCell)->getRow();
						auto iters = _displayCell.begin();
						if ((*destCell)->getColor() >= snowBlock && (*destCell)->getLife() > 0)
						{
									if ((*destCell)->getColumn() > 0 && (*destCell)->getColumn() < 6)
									{

												for (int i = 0; i < col - 1; ++i)
												{
															++iters;
												}
												auto iter = (*iters).begin();
												for (int i = 0; i < row; ++i)
												{
															++iter;
												}
												
												auto getcell1=getUsableCell(destCell, iter,cellBak);
												if (getcell1 != nullptr )
												{
															return getcell1;
												}
												else
												{
															iters = _displayCell.begin();
															for (int i = 0; i < col + 1; ++i)
															{
																		++iters;
															}
															auto iter = (*iters).begin();
															for (int i = 0; i < row; ++i)
															{
																		++iter;
															}
															return getUsableCell(destCell, iter, cellBak);
												}
									}
									else if ((*destCell)->getColumn() == 0)
									{
												
												for (int i = 0; i < col + 1; ++i)
												{
															++iters;
												}
												auto iter = (*iters).begin();
												for (int i = 0; i < row; ++i)
												{
															++iter;
												}
												return getUsableCell(destCell, iter,cellBak);
									}
									else if ((*destCell)->getColumn() == 6)
									{
												for (int i = 0; i < col - 1; ++i)
												{
															++iters;
												}
												auto iter = (*iters).begin();
												for (int i = 0; i < row; ++i)
												{
															++iter;
												}

												return getUsableCell(destCell, iter, cellBak);
									}
									else
									{
												return nullptr;
									}
						}
						else
						{
									auto cellbak = destCell;
									if ((*cellbak)->getRow() >= 4)
									{
												return nullptr;
									}
									++cellbak;									
									return getUsableCell(destCell,cellbak,cellBak);
						}				
			}*/

			return nullptr;
}

Cells * CellsLayer::getUsableCell(std::list<Cells*>::iterator &souceCell, int col, int row)
{
			if (col < 0 || col>6 || row > 4 || row < 0)
			{
						return nullptr;
			}
			else
			{
						auto cells = _displayCell.begin();
						
						for (int i = 0; i < col ; ++i)
						{				
									
									++cells;
									if (cells == _displayCell.end())
									{
												return nullptr;
									}
						}
						
						auto cell = (*cells).begin();
						for (int i = 0; i < row; ++i)
						{
									++cell;
									if (cell == cells->end())
									{
												return nullptr;
									}
						}
						
						Cells *celltemp1 = nullptr;

						if ((*cell)->getLife() <= 0)
						{
									celltemp1 = getUsableCell(souceCell, col, row+1);
									if (celltemp1 == nullptr )
									{
												if (abs((col - 1) - (*souceCell)->getColumn()) <= abs((col + 1) - (*souceCell)->getColumn()))
												{
															celltemp1 = getUsableCell(souceCell, col - 1, row + 1);
												}
												else
												{
															celltemp1 = getUsableCell(souceCell, col + 1, row + 1);
												}
												
									}
									if (celltemp1 == nullptr)
									{
												if (abs((col + 1) - (*souceCell)->getColumn()) <= abs((col - 1) - (*souceCell)->getColumn()))
												{
															celltemp1 = getUsableCell(souceCell, col + 1, row + 1);														
												}
												else
												{
															celltemp1 = getUsableCell(souceCell, col - 1, row + 1);
												}
									}
									
									return celltemp1;
						}
						else
						{
									if ((*cell)->getColor() >= snowBlock)
									{
												return nullptr;
									}
									else
									{
												Cells *cellbak = *cell;
												(*souceCell)->setColumn(cellbak->getColumn());
												(*souceCell)->setRow(cellbak->getRow());
												*cell = *souceCell;
												//Cells *celltake= getUsableCell
												return cellbak;
									}
						}


			}
			
}

Cells *CellsLayer::getColRowCell(int col, int row)
{
			if (col < 0 || col>6 || row > 4 || row < 0)
			{
						return nullptr;
			}

			auto cells = _displayCell.begin();
			for (int i = 0; i < col; ++i)
			{

						++cells;
			}
			auto cell = (*cells).begin();
			for (int i = 0; i < row; ++i)
			{

						++cell;
			}
			return *cell;
}

DrawNode * CellsLayer::coverFabric(Vec2 pos)
{
			return nullptr;
}

//�ܷ�����
int CellsLayer::computeTheOneCell(std::vector<Cells *> &cells, Cells * cellCurrent, int count)
{
			if (cellCurrent == nullptr)
			{
						return count;
			}
			else
			{
						int num = 1;
						auto re = cellCurrent;
						re->_isUsedLogic = true;
						auto re2 = cells.begin();
						for (; re2 != cells.end(); ++re2)
						{
									if (((*re2)->getRow() == re->getRow() || (*re2)->getColumn() == re->getColumn()) && (*re2)->_isUsedLogic == false)
									{
												if (abs((*re2)->getColumn() - re->getColumn()) == 1 || abs((*re2)->getRow() - re->getRow()) == 1)
												{
															(*re2)->_isUsedLogic = true;
															num += computeTheOneCell(cells, *re2,count);														
												}
									}
									else if (((*re2)->getColumn() != re->getColumn() && (*re2)->getRow() != re->getRow()) && (*re2)->_isUsedLogic == false)
									{
												if (abs((*re2)->getColumn() - re->getColumn()) + abs((*re2)->getRow() - re->getRow()) == 2)
												{
															(*re2)->_isUsedLogic = true;
															num += computeTheOneCell(cells, *re2, count);															
											}
									}
									else
									{
												continue;
									}
						}


						if (num > count)
						{
									count = num;
						}
						return count;
			}
}

void CellsLayer::restoreAction()
{
			if (!_isCanRunning)
			{
						for (auto cells : _displayCell)
						{
									for (auto cell : cells)
									{
												cell->stopAllActions();
												auto moveto = MoveTo::create(0.5f, coordinateToVec2(3, 2));
												auto moveback = MoveTo::create(0.5f, coordinateToVec2(cell->getColumn(), cell->getRow()));
												auto sequence_moveTo_moveBack = Sequence::create(moveto,moveback,NULL);
												cell->runAction(sequence_moveTo_moveBack);
									}
						}
					
			}
}

bool CellsLayer::isStalemate()
{
			auto ret = false;
			do
			{
						//�������ܷ�����
						int reback = 0;
						for (int i = 0; i < 7; ++i)
						{
									std::vector<Cells *> calcColor;
									for (auto &cells : _displayCell)
									{
												for (auto &cell : cells)
												{
															if ( (cell != nullptr) && static_cast<int>(cell->getColor()) == i)
															{
																		calcColor.push_back(cell);
															}
												}
									}
									auto isCan = 0;
									auto isCanBak = 0;
									//std::vector<Cells *> recordCell;
									
									for (unsigned int i=0;i<calcColor.size();++i)
									{												
												isCanBak = computeTheOneCell(calcColor,calcColor[i], 0);
												if (isCanBak > isCan)
												{
															isCan = isCanBak;
												}												
									}


									for (auto &numtemp : calcColor)
									{
												numtemp->_isUsedLogic = false;
									}
									
									
									
									if (isCan >= 3)
									{
												ret = true;
												break;
									}
						}
					
			} while (0);
			return ret;
}

void CellsLayer::shffuleCellsforMenu()
{
			do 
			{
						_isCanRunning = false;
						std::vector<Cells *> mytestbak;
						for (auto cells : _displayCell)
						{
									for (auto cell : cells)
									{
												mytestbak.push_back(cell);
									}
						}
						std::default_random_engine defaultEngine;
						std::shuffle(mytestbak.begin(), mytestbak.end(), defaultEngine);
						auto iter = mytestbak.begin();
						int col = 0;
						int row = 0;
						for (auto itercol = _displayCell.begin(); itercol != _displayCell.end(); ++itercol)
						{
									row = 0;
									for (auto iterrow = (*itercol).begin(); iterrow != (*itercol).end(); ++iterrow)
									{
												*iterrow = *iter;
												(*iterrow)->setRow(row);
												(*iterrow)->setColumn(col);
												++iter;
												++row;
									}
									++col;
						}
						restoreAction();
						_isCanRunning = true;
			} while (!isStalemate());//!isStalemate()
}

void CellsLayer::restoreStalemate()
{
			//���Ҹ�������
			if (!isStalemate())
			{
						std::vector<Cells *> mytestbak;
						for (const auto &cells : _displayCell)
						{
									for (const auto &cell : cells)
									{
												mytestbak.push_back(cell);
									}
						}
						std::default_random_engine defaultEngine;
						std::shuffle(mytestbak.begin(), mytestbak.end(), defaultEngine);
						auto iter = mytestbak.begin();
						int col = 0;
						int row = 0;
						for (auto itercol = _displayCell.begin(); itercol != _displayCell.end(); ++itercol)
						{
									row = 0;
									for (auto iterrow = (*itercol).begin(); iterrow != (*itercol).end(); ++iterrow)
									{
												*iterrow = *iter;
												(*iterrow)->setRow(row);
												(*iterrow)->setColumn(col);
												++iter;
												++row;
									}
									++col;
						}
						restoreAction();
						restoreStalemate();
			}
			else
			{						
						return;
			}
}



Cells * CellsLayer::findCell(int col, int row)
{
			auto iter = _displayCell.begin();
			for (int i = 0; i < col; ++col)
			{
						++iter;
			}
			auto cell_iter = (*iter).begin();
			for (int i = 0; i < row; ++i)
			{
						++cell_iter;
			}
			return *cell_iter;

}

Cells * CellsLayer::getNewCellForSupCell()
{
			auto randcol = (rand() % 100);
			auto cel = createCells(randcol);			
			cel->getSprite()->setScale(0.5);
			return cel;
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

void CellsLayer::unLinkLineInGrid(int col1, int row1, int col2, int row2)
{
			if (!_linkLineCache.size())
			{
						return;
			}
			auto & line = _linkLineCache.back();
			if (line)
			{						
						line->removeFromParentAndCleanup(true);
			}
			_linkLineCache.pop_back();
}



bool CellsLayer::checkCells()
{
			auto ret = false;
			do 
			{
						int i = 0;
						for (auto cells : _displayCell)
						{
									for (auto cell : cells)
									{
												++i;
									}
						}
						if (i != 35)
						{
									return ret;
						}

						ret = true;
			} while (0);
			
			return ret;
}

Vec2 CellsLayer::coordinateToVec2(int col, int row)
{
			Vec2 vec(getSingleTiledSize.x*(col+0.5), (getSingleTiledSize.y + (tileinterval - 95 * 0.5))*(row+0.5));
			return vec;
}

double *CellsLayer::vec2ToCoordinate(Vec2 vec)
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
									if (cell == nullptr)
									{
												continue;
									}
									if (cell->getColor() >= snowBlock)
									{
												continue;
									}
									if (cell->getColor()!=col )
									{
												if (!(cell->isCanSelected()))
												{
															continue;
												}
												GLProgramCache::getInstance()->addGLProgram(cell->getSprite()->getGLProgram(), "normal_effect");
												cell->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("grey_effect"));														
									}
									else
									{
												if (!cell->isSelected())
												{														
															_touchCells.push_back(cell);
												}
												if (!(cell->isCanSelected()))
												{
															continue;
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
									if (cell == nullptr)
									{
												continue;
									}
									if (cell->getColor() >= snowBlock)
									{
												continue;
									}
									if (cell->getColor() != col)
									{
												if (!(cell->isCanSelected()))
												{
															continue;
												}
												//GLProgramCache::getInstance()->addGLProgram(cell->getSprite()->getGLProgram(), "normal_effect");
												cell->getSprite()->setGLProgram(GLProgramCache::getInstance()->getGLProgram("normal_effect"));
									}
									else
									{
												if (!(cell->isCanSelected()))
												{
															continue;
												}
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
						cell->stopAllActions();
						auto moveto = MoveTo::create(0.5f, Vec2((getSingleTiledSize.x)*(col2 + 0.5), (getSingleTiledSize.y + (tileinterval - 95 * 0.5))*(row2 + 0.5)));
						cell->runAction(moveto);
						cell->setColumn(col2);
						cell->setRow(row2);
			}
}

void CellsLayer::addGreyAndLightShader()
{
			std::string shader1 = FileUtils::getInstance()->getStringFromFile("example_GreyScale.fsh");
			GLProgramCache::getInstance()->addGLProgram(GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, shader1.c_str()), "grey_effect");
			std::string shader2 = FileUtils::getInstance()->getStringFromFile("example_LightScale.fsh");
			GLProgramCache::getInstance()->addGLProgram(GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, shader2.c_str()), "light_effect");
}



void CellsLayer::initClippingNode()
{
			_clipNode = ClippingNode::create();
			_clipNode->setInverted(false);
			_clipNode->setAlphaThreshold(1.0f);

			auto stencil = Node::create();

			auto drawnode = DrawNode::create();
			float coverY = towerArea-10;
			Vec2 point[4]{ Vec2(0,0),Vec2(0,coverY),Vec2(winSize.width,coverY),Vec2(winSize.width,0) };
			drawnode->drawPolygon(point, 4, Color4F(1,0,0,1),1,Color4F(0,1,0,1));
			stencil->addChild(drawnode,-1);
			_clipNode->setStencil(stencil);
			addChild(_clipNode,-1);

}





bool CellsLayer::onTouchBegan(Touch * touch, Event * unused_event)
{
			auto ret = false;
			do 
			{					
						//���������ط�������Ǹ��ӣ�����
						if (!checkCells() && !_isCanRunning)
						{
									return ret;
						}
						else
						{
									assert(_displayCell.size() > 0);
									for (auto cells : _displayCell)
									{
												for (auto cell : cells)
												{							
															
															if (cell->getLife()>0 &&( cell->getBoundingBox().containsPoint(touch->getLocation()) && cell->getColor()<snowBlock))
															{
																		//
																		log("touch  cell life :%d  col:%d,row:%d", cell->getLife(),cell->getColumn(),cell->getRow());
																		//
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
			if (!_isCanRunning)
			{
						return;
			}
			for (auto touchlist : _touchCells)
			{
						if (touchlist->getBoundingBox().containsPoint(touch->getLocation()))
						{
									if (touchlist->isSelected() || pow(touchlist->getRow() - _touchMoveCells.back()->getRow(), 2) + pow(touchlist->getColumn() - _touchMoveCells.back()->getColumn(), 2) > 2)
									{
												break;
									}
									touchlist->_isTouchBack = false;
									touchlist->_isSelected = true;
									linkLineInGrid(touchlist->getColumn(), touchlist->getRow(), _touchMoveCells.back()->getColumn(), _touchMoveCells.back()->getRow());
									_touchMoveCells.push_back(touchlist);
									break;
									
						}
			}
			if (_touchMoveCells.size() && !(_touchMoveCells.back()->getBoundingBox().containsPoint(touch->getLocation())))
			{
						_touchMoveCells.back()->_isTouchBack = !(_touchMoveCells.back()->_isTouchBack);
			}
			if (_touchMoveCells.size() >= 2)
			{
						auto cellEnd2 = ++_touchMoveCells.rbegin();
						if ( (*cellEnd2)->getBoundingBox().containsPoint(touch->getLocation()) && _touchMoveCells.back()->_isTouchBack)
						{

									_touchMoveCells.back()->_isSelected = false;
									unLinkLineInGrid(0, 0, 0, 0);
									_touchMoveCells.pop_back();								
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
									this->destroyCells();
									_touchMoveCells.clear();
						}
			}
}

void CellsLayer::onTouchCancelled(Touch * touch, Event * unused_event)
{
			//ȡ������ô��������ָ�ѡ�����ΪFALSE��
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
						_touchMoveCells.clear();
			}
}
