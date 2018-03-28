#include "Player.h"
#include "Poker.h"


#define playMid(sizept) Point(((winSize.width - (sizept) * (float)pkInterval - pkWidth) / 2.0), (float)pkHeight)
#define AI1Mid(sizept) Point(winSize.width - (float)pkHeight / 2.0 - pkHeight, winSize.height - ((sizept)* (float)pkInterval + pkWidth))
#define AI2Mid(sizept) Point(pkHeight / 2.0,(winSize.height + pkHeight+((sizept))*pkInterval)/2)

Player::Player()
{
			playerPt = Point((winSize.width - 17* (float)pkInterval - pkWidth) / 2.0, pkHeight );
			AIPt1 = Point(winSize.width - (float)pkHeight / 2.0 - pkHeight, winSize.height - (17 * (float)pkInterval + pkWidth));
			AIPt2 = Point(pkHeight / 2.0, winSize.height - pkHeight); 
}


Player::~Player()
{
}



void Player::checkcard(Vector<Ref *> &_type,int type)
{
			Vector<Ref *>bak;
			for (int i = 0; i < _type.size(); ++i)
			{
						if ((static_cast<Poker *>(_type.at(i))->getUsed()))
						{
									bak.pushBack(static_cast<Poker *>(_type.at(i)));
						}
			}
			_type.clear();
			_type = bak;
			
			int pksize =_type.size();
			//log("%d", pksize);
			Point pkpoint;
			switch (type)
			{
						case 0:
						{
									pkpoint = playMid(pksize);
									int j = 0;
									for (int i = 0; i < pksize; ++i)
									{
												if (static_cast<Poker *>(_type.at(i))->getUsed())
												{
															static_cast<Poker *>(_type.at(i))->pkSetPosition(Point(pkpoint.x +j*pkInterval+ pkWidth, pkpoint.y));
															static_cast<Poker *>(_type.at(i))->setLocalZOrder(i+1);
															++j;
												}
												//log("%d : %d, %d", i, static_cast<Poker *>(m_pokers.at(i))->getSuit(), static_cast<Poker *>(m_pokers.at(i))->getpkNumber());								
									}
									break;
						}
								
						case 1:
						{
									pkpoint = AI1Mid(pksize);
									int j = 0;
									for (int i = 0; i < pksize; ++i)
									{
												if (static_cast<Poker *>(_type.at(i))->getUsed())
												{
															static_cast<Poker *>(_type.at(i))->pkSetPosition(Point(pkpoint.x, pkpoint.y + j*pkInterval));
															static_cast<Poker *>(_type.at(i))->setRotation(90);
															static_cast<Poker *>(_type.at(i))->setLocalZOrder(i+1);
															++j;
												}
												//log("%d : %d, %d", i, static_cast<Poker *>(m_pokers.at(i))->getSuit(), static_cast<Poker *>(m_pokers.at(i))->getpkNumber());								
									}
									break;
						}
								
						case 2:
						{
									pkpoint = AI2Mid(pksize);
									int j = 0;
									for (int i = 0; i < pksize; ++i)
									{
												if (static_cast<Poker *>(_type.at(i))->getUsed())
												{
															static_cast<Poker *>(_type.at(i))->pkSetPosition(Point(pkpoint.x, pkpoint.y - j*pkInterval));
															static_cast<Poker *>(_type.at(i))->setRotation(90);
															static_cast<Poker *>(_type.at(i))->setLocalZOrder(i+1);
															++j;
												}
												//log("%d : %d, %d", i, static_cast<Poker *>(m_pokers.at(i))->getSuit(), static_cast<Poker *>(m_pokers.at(i))->getpkNumber());								
									}
									break;
						}
								
			}
			
		
			
			
}

void Player::clearTable(Vector<Ref *> &_type)
{
			if (lastPokers.empty())
			{
						return;
			}

			if (static_cast<Poker *>(_type.at(0))->owner == 0 && m_lastPokers.size())
			{						
						for (auto pk : m_lastPokers)
						{
									static_cast<Poker *>(pk)->setUsed(false);
									static_cast<Poker *>(pk)->setVisible(false);
						}
			}
			else if (static_cast<Poker *>(_type.at(0))->owner == 1 && AI1_lastPokers.size())
			{
						for (auto pk : AI1_lastPokers)
						{
									static_cast<Poker *>(pk)->setUsed(false);
									static_cast<Poker *>(pk)->setVisible(false);

						}
			}
			else if (static_cast<Poker *>(_type.at(0))->owner == 2 && AI2_lastPokers.size())
			{
						for (auto pk : AI2_lastPokers)
						{
									static_cast<Poker *>(pk)->setUsed(false);
									static_cast<Poker *>(pk)->setVisible(false);
						}
			}


			
			//log("%d",m_pokers.size());
			//lastPokers.clear();
}

void Player::putCardInMiddle(Vector<Ref *> &_type)
{
			
			int pksize = _type.size();
			Point point;
			//Point point = Point(winSize.width / 2   - pksize*pkInterval/2, winSize.height / 2);
			lastPokers.clear();
			

						if (static_cast<Poker *>(_type.at(0))->owner == 1)
						{
									AI1_lastPokers.clear();
									point = Point(AIPt1.x-pkHeight-pkInterval, (winSize.height- (pksize - 1)*pkInterval -pkWidth)/2 + pkHeight);
									for (int i = 0; i < pksize; ++i)
									{

												//static_cast<Poker *>(_type.at(i))->setRotation(360);
												static_cast<Poker *>(_type.at(i))->pkSetPosition(Point(point.x , point.y+i*pkInterval));
												static_cast<Poker *>(_type.at(i))->setUsed(false);
												static_cast<Poker *>(_type.at(i))->setLocalZOrder(i);
												static_cast<Poker *>(_type.at(i))->showCards();
												lastPokers.pushBack(static_cast<Poker *>(_type.at(i)));
												AI1_lastPokers.pushBack(static_cast<Poker *>(_type.at(i)));
									}
						}
						else if (static_cast<Poker *>(_type.at(0))->owner == 2)
						{
									AI2_lastPokers.clear();
									point = Point(AIPt2.x + pkHeight +pkInterval, (winSize.height - (pksize -1)*pkInterval - pkWidth)/2+pkHeight );
									for (int i = 0; i < pksize; ++i)
									{

												//static_cast<Poker *>(_type.at(i))->setRotation(360);
												static_cast<Poker *>(_type.at(i))->pkSetPosition(Point(point.x, point.y+i*pkInterval));
												static_cast<Poker *>(_type.at(i))->setUsed(false);
												static_cast<Poker *>(_type.at(i))->setLocalZOrder(i);
												static_cast<Poker *>(_type.at(i))->showCards();
												lastPokers.pushBack(static_cast<Poker *>(_type.at(i)));
												AI2_lastPokers.pushBack(static_cast<Poker *>(_type.at(i)));
									}
						}
						else if (static_cast<Poker *>(_type.at(0))->owner == 0)
						{
									m_lastPokers.clear();
									point = Point(winSize.width / 2 - pkWidth / 2 - pksize*pkInterval / 2, winSize.height / 2);
									for (int i = 0; i < pksize; ++i)
									{
												static_cast<Poker *>(_type.at(i))->pkSetPosition(Point(point.x + i*pkInterval, point.y - pkHeight / 2));
												static_cast<Poker *>(_type.at(i))->setUsed(false);
												static_cast<Poker *>(_type.at(i))->setLocalZOrder(i);
												static_cast<Poker *>(_type.at(i))->setCanSelectdPk(false);
												lastPokers.pushBack(static_cast<Poker *>(_type.at(i)));
												m_lastPokers.pushBack(static_cast<Poker *>(_type.at(i)));
									}
						}
						
			
						
}




bool Player::updatePkPosition()
{
			bool isRet = false;
			do
			{
						
						for (int index = 0; index < m_pokers.size(); ++index)
						{
									static_cast<Poker *>(m_pokers.at(index))->pkSetPosition(Point(playerPt.x+pkInterval*index+ pkHeight / 2,playerPt.y));
						}
						for (int index = 0; index < AI1_pokers.size (); ++index)
						{									
									static_cast<Poker *>(AI1_pokers.at(index))->setRotation(90);
									//static_cast<Poker *>(AI1_pokers.at(index))->setReverse();
									static_cast<Poker *>(AI1_pokers.at(index))->pkSetPosition(Point(AIPt1.x+ pkHeight / 2, AIPt1.y + pkInterval*index+pkWidth/2));
						}
						for (int index = 0; index <AI2_pokers.size (); ++index)
						{							
									static_cast<Poker *>(AI2_pokers.at(index))->setRotation(90);
									//static_cast<Poker *>(AI2_pokers.at(index))->setReverse();
									static_cast<Poker *>(AI2_pokers.at(index))->pkSetPosition(Point(AIPt2.x+ pkHeight / 2, AIPt2.y - pkInterval*index+pkWidth/2));
						}
						//log("*****************");
						isRet = true;
			} while (0);
			return isRet;
}

int Player::getCardLogicValue(Ref * _card)
{			
			int num = static_cast<Poker *>(_card)->getpkNumber();
			return num;
}

int Player::getPokerType(Vector<Ref*>& _type)
{
			int cardsize = _type.size();
			switch (cardsize)
			{
						case 0: return ERROR_CARD;
						case 1:return SINGLE_CARD;
						case 2:
						{
									if (static_cast<Poker *>(_type.at(0))->getpkNumber() == redJoker &&static_cast<Poker *>(_type.at(1))->getpkNumber() == blackJoker) return MISSILE_CARD;
									if (static_cast<Poker *>(_type.at(0))->getpkNumber() == static_cast<Poker *>(_type.at(1))->getpkNumber()) return DOUBLE_CARD;
									return ERROR_CARD;
						}
			}

			tagAnalyseResult analyseRes;
			analyseCards(_type, analyseRes);
			//四张牌
			if (analyseRes.resultCount[3] > 0)
			{
						if ((analyseRes.resultCount[3] == 1) && (cardsize == 4)) return BOMB_CARD;
						if ((analyseRes.resultCount[3] == 1) && (cardsize == 6)) return BOMB_TWO_CARD;
						if ((analyseRes.resultCount[3] == 1) && (cardsize == 8)&& (analyseRes.resultCount[1]==2)) return BOMB_DOUBLE_TWO_CARD;

						return ERROR_CARD;
			}

			//三张牌判断
			if (analyseRes.resultCount[2] > 0)
			{
						if (analyseRes.resultCount[2] > 1)
						{
									int cardData = analyseRes.cardData[2][0];
									int firstLogicValue = cardData;

									if (firstLogicValue >= 12) return ERROR_CARD;

									for (int i = 1; i < analyseRes.resultCount[2]; ++i)
									{
												int cbCardData = analyseRes.cardData[2][i * 3];
												if (firstLogicValue != (cbCardData + i)) return ERROR_CARD;
									}
						}
						else if (cardsize == 3) return THREE_CARD;

						if (analyseRes.resultCount[2] * 3 == cardsize) return AIRCRAFT_CARD;
						if (analyseRes.resultCount[2] * 4 == cardsize) return AIRCRAFT_SINGLE_CARD;
						if (analyseRes.resultCount[2] * 5 == cardsize && analyseRes.resultCount[1] == analyseRes.resultCount[2]) return AIRCRAFT_DOBULE_CARD;

						return ERROR_CARD;
			}

			//两张判断
			if (analyseRes.resultCount[1] >= 3)
			{
						int cardData = analyseRes.cardData[1][0];
						int firstLogicValue = cardData;
						if (firstLogicValue >= 12) return ERROR_CARD;

						for (int i = 1; i < analyseRes.resultCount[1]; ++i)
						{
									int cbCardData = analyseRes.cardData[1][i * 2];
									if (firstLogicValue != (cbCardData + i)) return ERROR_CARD;

						}

						if (analyseRes.resultCount[1] * 2 == cardsize) return COMPANY_CARD;

						return ERROR_CARD;

			}

			if ((analyseRes.resultCount[0] >= 5) && (analyseRes.resultCount[0] == cardsize))
			{
						int cardData = analyseRes.cardData[0][0];
						int firstLogicValue = cardData;

						if (firstLogicValue >= 12) return ERROR_CARD;

						for (int i = 1; i < analyseRes.resultCount[0]; ++i)
						{
									int cbCardData = analyseRes.cardData[0][i];
									if (firstLogicValue != cbCardData + i) return ERROR_CARD;
						}
						return CONNECT_CARD;
			}




			return ERROR_CARD;
}

void Player::analyseCards(Vector<Ref *> &_type, tagAnalyseResult &AnalysePoker)
{
			//初始化扑克分析置0
			memset(AnalysePoker.resultCount, 0, sizeof(AnalysePoker.resultCount));
			memset(AnalysePoker.cardData, 0, sizeof(AnalysePoker.cardData));

			int size = _type.size();
			for (int i = 0; i < size; ++i)
			{
						int sameCount = 1, cardValueTemp = 0;
						int cardNumber = static_cast<Poker *>(_type.at(i))->getpkNumber();
						for (int j = i + 1; j < size; ++j)
						{									
									if (static_cast<Poker *>(_type.at(j))->getpkNumber() != cardNumber)
									{
												break;
									}
									++sameCount;
						}
						int index = AnalysePoker.resultCount[sameCount - 1]++;
						for (int j = 0; j < sameCount; ++j)  AnalysePoker.cardData[sameCount - 1][index*sameCount + j] = static_cast<Poker *>(_type.at(i + j))->getpkNumber ();
						i += sameCount - 1;
			}

			return;
}

bool Player::compareCard(Vector<Ref*>& _first, Vector<Ref*>& _next)
{
			CARD_TYPE firstType =static_cast<CARD_TYPE>( getPokerType(_first));
			CARD_TYPE nextType = static_cast<CARD_TYPE>(getPokerType(_next));

			if (nextType == ERROR_CARD) return false;
			if (nextType == MISSILE_CARD) return true;

			if ((firstType != BOMB_CARD) && (nextType == BOMB_CARD)) return true;
			if ((firstType == BOMB_CARD) && (nextType != BOMB_CARD)) return false;

			if ((firstType != nextType) || (_first.size() != _next.size())) return false;

			switch (nextType)
			{
						case SINGLE_CARD:
						case DOUBLE_CARD:
						case THREE_CARD:
						case CONNECT_CARD:
						case COMPANY_CARD:
						case AIRCRAFT_CARD:
						case BOMB_CARD:
						case THREE_ONE_CARD:
						case THREE_TWO_CARD:
						{
									int firstLogicValue = static_cast<Poker *>(_first.at(0))->getpkNumber();
									int nextLogicValue = static_cast<Poker *>(_next.at(0))->getpkNumber();

									return nextLogicValue > firstLogicValue;
						}
						case AIRCRAFT_SINGLE_CARD:
						case AIRCRAFT_DOBULE_CARD:
						{
									tagAnalyseResult firstRes;
									tagAnalyseResult nextRes;
									analyseCards(_first, firstRes);
									analyseCards(_next, nextRes);

									int firstValue = firstRes.cardData[2][0];
									int nextValue = nextRes.cardData[2][0];
									return nextValue > firstValue;
 						}
						case BOMB_TWO_CARD:
						case BOMB_DOUBLE_TWO_CARD:
						{
									tagAnalyseResult firstRes;
									tagAnalyseResult nextRes;
									analyseCards(_first, firstRes);
									analyseCards(_next, nextRes);
									int firstValue = firstRes.cardData[3][0];
									int nextValue = nextRes.cardData[3][0];

									return nextValue > firstValue;
						}

			}
			return false;
}


