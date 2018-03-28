#include "GameScene.h"
#include "Poker.h"
#include "DdzButton.h"
#include "Player.h"
#include "Net.h"

//bool GameScene::isCalled;
bool GameScene::isStarted=false;
int GameScene::m_state=-1;
bool GameScene::isPutCards=false;
char GameScene::sendBuf[NET_BUF_SIZE];
char GameScene::recvBuf[NET_BUF_SIZE];
//Vector<Ref *> GameScene::_pokers;

GameScene::GameScene()
{
			m_player = new Player();

}
GameScene::~GameScene()
{
			CC_SAFE_DELETE(m_player);
}




GameScene * GameScene::create()
{
			GameScene *pRet = new GameScene();
			if (pRet && pRet->init())
			{
						pRet->autorelease();
			}
			else
			{
						delete pRet;
						pRet = nullptr;
			}
			return pRet;
}

Scene * GameScene::scene()
{
			auto scene = Scene::create();
			auto layer = GameScene::create();
			scene->addChild(layer);
			return scene;
}

bool GameScene::init()
{
			Layer::init();

			bool isRet = false;
			do
			{
						
						m_state = 0;
						isCalled = -1;
						isStarted = false;
						isPutCards = false;
						calledNumber = -1;
						calledTime = 3;
						memset(selectCards, 0, sizeof(int) * 20);
						srand((unsigned)time(NULL));
						//添加背景
						CC_BREAK_IF(!initBackGround(bkFileName));
						
						////生成扑克数据
						//CC_BREAK_IF(!initCards(pokerFileName));
						////洗牌
						//CC_BREAK_IF(!shuffleCards());
						////发牌
						//CC_BREAK_IF(!dealCards());
						//生成按钮数据
						CC_BREAK_IF(!initButton(buttonStrFileName));
						//添加触摸反馈?

						
						//网络按钮添加
						//testSocket();

						ValueMap vMap = FileUtils::getInstance()->getValueMapFromFile(buttonStrFileName);
						std::string str;
						str = vMap.at("buchu").asString();
						noCalled = Label::createWithSystemFont(str, "Courier New", 25);
						addChild(noCalled);
						noCalled->setVisible(false);						
						ai1noCalled = Label::createWithSystemFont(str, "Courier New", 25);
						ai1noCalled->setRotation(270);
						addChild(ai1noCalled);
						ai1noCalled->setVisible(false);
						ai2noCalled = Label::createWithSystemFont(str, "Courier New", 25);
						ai2noCalled->setRotation(90);
						addChild(ai2noCalled);
						ai2noCalled->setVisible(false);											
						//网络数据初始化
						tagForInitCDT=-1;
						//scheduleUpdate();
						isRet = true;
			} while (0);

			return isRet;
}

void GameScene::onEnter()
{
			Layer::onEnter();
			m_eventListener = EventListenerTouchOneByOne::create();
			
			m_eventListener->onTouchBegan = [&,this](Touch * touch, Event *) {
						bool isRet = false;
						do
						{
									Point ptouch = touch->getLocation();
									
									for (int i = m_player->m_pokers.size()-1; i >=0; --i)
									{
												Size pkSize = static_cast<Poker *>(m_player->m_pokers.at(i))->getContentSize();
												Point pkPs =static_cast<Poker *>(m_player->m_pokers.at(i))->getPosition();
																					
												//log("content %f  :  %f", pkSize.width, pkSize.height);											
												Rect pkRect = Rect(pkPs.x,pkPs.y, pkSize.width, pkSize.height);
												
												if (pkRect.containsPoint(ptouch)&&isStarted&&static_cast<Poker *>(m_player->m_pokers.at(i))->getCanSelectdPk ())
												{
															isRet = true;
															if (selectCards[i] == 1)
															{
																		//selectCards[i] = 0;
																		break;
															}
															else
															{
																		selectCards[i] = 1;
																	
																		break;
															}
															
												}
									}
									
						} while (0);
						return isRet;
			};



			m_eventListener->onTouchMoved = [&](Touch *touch, Event *) {

						bool isRet = false;
						do
						{
									Point ptouch = touch->getLocation();
									Point ptouchStart = touch->getStartLocation();
									Rect touchRect;
									Point pkPosition;
									Rect pkRect;
									//memset(selectCards, 0, sizeof(selectCards));
									if (m_player->m_pokers.size())
									{
												pkPosition = static_cast<Poker *>(m_player->m_pokers.at (0))->getPosition();
									}
									else
									{
												return isRet;
									}
									if (ptouchStart.y > pkPosition.y + pkHeight || ptouchStart.y<pkPosition.y)
									{
												return true;
									}
									if (ptouch.x > ptouchStart.x)
									{
												touchRect = Rect(ptouchStart.x, ptouchStart.y, abs(ptouch.x - ptouchStart.x), 0);											
									}
									else
									{
												touchRect = Rect(ptouch.x, ptouchStart.y, abs(ptouchStart.x -ptouch.x ), 0);											
									}
									
									log("start %f : %f", ptouchStart.x, ptouchStart.y);
									log("touch %f : %f", ptouch.x, ptouch.y);
									
									for (int i = 0; i < m_player->m_pokers.size(); ++i)
									{
												Point pkpt = static_cast<Poker *>(m_player->m_pokers.at(i))->getPosition();
												if (i == m_player->m_pokers.size() - 1)
												{
															pkRect = Rect(pkpt.x, pkpt.y, pkWidth, pkHeight);
												}
												else
												{
															pkRect = Rect(pkpt.x, pkpt.y, pkInterval, pkHeight);
												}

												if (touchRect.intersectsRect(pkRect) && isStarted)
												{
															selectCards[i] = 1;
															static_cast<Poker *>(m_player->m_pokers.at(i))->setColor(Color3B(100,100,255));
												}
												else
												{
															selectCards[i] = 0;
															static_cast<Poker *>(m_player->m_pokers.at(i))->setColor(Color3B::WHITE);
												}
									}


									isRet = true;
						} while (0);
						return isRet;
			};
			m_eventListener->onTouchEnded = [&](Touch *touch, Event *) {
						bool isRet = false;
						do
						{
									for (int i = 0; i < m_player->m_pokers.size (); ++i)
									{
												if (selectCards[i] == 1)
												{
															if (!(static_cast<Poker *>(m_player->m_pokers.at(i))->getSelectedPk()))
															{
																		static_cast<Poker *>(this->m_player->m_pokers.at(i))->selectPokerUp();
																		static_cast<Poker *>(this->m_player->m_pokers.at(i))->setSelectedPk(!(static_cast<Poker *>(m_player->m_pokers.at(i))->getSelectedPk()));
																		
															}
															else
															{
																		static_cast<Poker *>(this->m_player->m_pokers.at(i))->selectPokerDown();
																		static_cast<Poker *>(this->m_player->m_pokers.at(i))->setSelectedPk(!(static_cast<Poker *>(m_player->m_pokers.at(i))->getSelectedPk()));
																	
															}
															static_cast<Poker *>(m_player->m_pokers.at(i))->setColor(Color3B::WHITE);
												}
									}
									memset(selectCards, 0, sizeof(int) * 20);
									isRet = true;
						} while (0);
						return isRet;
			};

			m_eventListener->setSwallowTouches(true);
			_eventDispatcher->addEventListenerWithSceneGraphPriority(m_eventListener, this);


}


void GameScene::onExit()
{
			Layer::onExit();
			for (auto s : _pokers)
			{
						static_cast<Poker *>(s)->release();
			}
			_eventDispatcher->removeEventListener(m_eventListener);
			
}

bool GameScene::initBackGround(const char * fileName)
{
			bool isRet = false;
			do {
						if (fileName)
						{
									_background = Sprite::create(fileName);
									_background->setAnchorPoint(Point(0, 0));
									addChild(_background);
									isRet = true;
						}
			} while (0);
			return isRet;
}

bool GameScene::initCards(const char * fileName)
{
			bool isRet = false;
			do
			{
						Poker *poke = nullptr;
						//生成扑克牌精灵,前52个
						for (int suit = 0; suit < 4; ++suit)
						{
									for (int number = 0; number < 13; ++number)
									{
												poke = createCardSprite(suit, number);
												poke->setPosition(winSize.width / 2, winSize.height / 2);
												poke->setReverse();
												poke->setAnchorPoint(Point(0.5, 0.5));
												poke->ignoreAnchorPointForPosition(false);
												//poke->showCards();
												//addChild(poke);
												
												_pokers.pushBack(poke);
									}
						}

						//生成black小丑
						poke = createCardSprite(Joker, blackJoker);
						poke->setPosition(winSize.width / 2, winSize.height / 2);
						poke->setReverse();
						//poke->showCards();
						//addChild(poke);
						_pokers.pushBack(poke);

						//生成redjoker
						poke = createCardSprite(Joker, redJoker);
						poke->setPosition(winSize.width / 2, winSize.height / 2);
						poke->setReverse();
						//poke->showCards();
						//addChild(poke);
						_pokers.pushBack(poke);

						isRet = true;
			} while (0);
			return isRet;
}

bool GameScene::initButton(const char * buttonStrFileName)
{
			bool isRet = false;
			do
			{
						m_menu = DdzButton::create();
						DdzButton::GameMain = this;

						if (!m_menu->createMenu(buttonStrFileName))
						{
									break;
						}

						addChild(m_menu->playMenu, 10, 1001);
						addChild(m_menu->callMenu, 10, 1002);
						addChild(m_menu->loseMenu, 10, 1003);
						addChild(m_menu->winMenu, 10, 1004);
						addChild(m_menu->reLoad, 10, 1005);
						//m_menu->playMenu->setVisible(false);

				/*		playm = static_cast<Menu *>(getChildByTag(1001));
						callm = static_cast<Menu *>(getChildByTag(1002));
						losem = static_cast<Menu *>(getChildByTag(1003));
						winm = static_cast<Menu *>(getChildByTag(1004));*/

						playm = m_menu->playMenu;
						callm = m_menu->callMenu;
						losem = m_menu->loseMenu;
						winm = m_menu->winMenu;

						playm->setVisible(false);
						callm->setVisible(false);
						losem->setVisible(false);
						winm->setVisible(false);

						//log("button menu : %p", m_menu->playMenu);
						ValueMap stgame= FileUtils::getInstance()->getValueMapFromFile(buttonStrFileName);
						startGame = Menu::create();
						MenuItem *item = MenuItemFont::create(stgame.at("startGame").asString(), [&](Ref *) {
									putCards();
									isPutCards = !isPutCards;									
						});
						startGame->addChild(item,5,1000);
						startGame->setPosition(winSize.width / 2, winSize.height / 2);
						startGame->setVisible(false);
						addChild(startGame);


						//******************************************************************************************网络按钮添加
						menusc = Menu::create();
						//服务器按钮
						MenuItem *serverMN = MenuItemFont::create("start server", CC_CALLBACK_1(GameScene::startServer,this));
						//客户端按钮
						MenuItem *clientMN = MenuItemFont::create("start client", std::bind(&GameScene::startClient, this,std::placeholders::_1));
						serverMN->setUserObject(clientMN);
						clientMN->setUserObject(serverMN);
						serverMN->setPosition(Point(-150, 0));
						clientMN->setPosition(Point(150, 0));
						menusc->addChild(serverMN, 1, 1101);
						menusc->addChild(clientMN, 1, 1102);

						addChild(menusc, 1, 1100);



						isRet = true;
			} while (0);
			return isRet;
}



bool GameScene::dealCards()
{
			bool isRet = false;
			do
			{
						int i = rand() % 3; //i, 0 服务器玩家先获取牌，1服务器下家先获取牌，2服务器上家先获取牌
						
						for (int dealtime = 0; dealtime < 51; dealtime += 3)
						{
									Poker *bak = (Poker *)_pokers.at(dealtime);
									Poker *bak1 = (Poker *)_pokers.at(dealtime + 1);
									Poker *bak2 = (Poker *)_pokers.at(dealtime + 2);
									if (i == 0)
									{
												//玩家先手
												m_player->m_pokers.pushBack(bak->copy());
												m_player->AI1_pokers.pushBack(bak1->copy());
												m_player->AI2_pokers.pushBack(bak2->copy());
									}
									else if (i == 1)
									{
												//电脑1先手

												m_player->AI1_pokers.pushBack(bak->copy());
												m_player->AI2_pokers.pushBack(bak1->copy());
												m_player->m_pokers.pushBack(bak2->copy());
									}
									else
									{
												//电脑2先手

												m_player->AI2_pokers.pushBack(bak->copy());
												m_player->m_pokers.pushBack(bak1->copy());
												m_player->AI1_pokers.pushBack(bak2->copy());
									}


						}

						for (int i = 0; i < 17; ++i)
						{
									static_cast<Poker *>(m_player->m_pokers.at(i))->owner = 0;
									static_cast<Poker *>(m_player->AI1_pokers.at(i))->owner = 1;
									static_cast<Poker *>(m_player->AI2_pokers.at(i))->owner =2;
						}

					

					
						
						isRet = true;
			} while (0);
			return isRet;
}

bool GameScene::shuffleCards()
{
			bool isRet = false;
			do
			{
						std::random_shuffle(_pokers.begin(), _pokers.end());
						isRet = true;
			} while (0);
			return isRet;
}

bool GameScene::putCards()
{
			bool isRet = false;
			do
			{
						//player来摆拍
						//log("Scene=%p", this);
						//给player手牌，排序，按spade,heart,club,diamond,joker,2,A,k-3从左往右依次排序
						swapCard(m_player->m_pokers);
						swapCard(m_player->AI1_pokers);
						swapCard(m_player->AI2_pokers);
						//log("%p", m_player->m_pokers);

						if (!(m_player->updatePkPosition()))
						{
									break;
						}
						//添加玩家和AI手牌
						for (int index = 0; index < 17; ++index)
						{
									addChild(static_cast<Poker *>(m_player->m_pokers.at(index)), 5);
									//static_cast<Poker *>(m_player->m_pokers.at(index))->setReverse();
									static_cast<Poker *>(m_player->m_pokers.at(index))->setCanSelectdPk(true);
									addChild(static_cast<Poker *>(m_player->AI1_pokers.at(index)), 5);
									static_cast<Poker *>(m_player->AI1_pokers.at(index))->setReverse();
									addChild(static_cast<Poker *>(m_player->AI2_pokers.at(index)), 5);
									static_cast<Poker *>(m_player->AI2_pokers.at(index))->setReverse();
						}

						//添加地主三张牌
						for (int i = 0; i < 3; ++i)
						{
									static_cast<Poker *>(_pokers.at(53 - i))->setPosition((winSize.width - pkWidth * 2) / 2 + i*pkWidth, winSize.height - pkHeight - pkHeight / 2);
									//static_cast<Poker *>(_pokers.at(53 - i))->showCards();
									static_cast<Poker *>(_pokers.at(53 - i))->setReverse();
									addChild(static_cast<Poker *>(_pokers.at(53 - i)), 999);
						}
						//设置 游戏逻辑进入叫地主阶段
						m_state = 1;
						//设置 叫地主初始位
						isCalled = rand() % 3;						
						
						
						
						isRet = true;
			} while (0);
			return isRet;
}

void GameScene::swapCard(Vector<Ref *>&_type)
{

			Poker *pk1 = nullptr;
			Poker *pk2 = nullptr;
			for (int i = 0; i < _type.size()-1 ; ++i)
			{
						
						for (int j = i + 1; j < _type.size(); ++j)
						{
									pk1 = static_cast<Poker *>(_type.at(i));
									pk2 = static_cast<Poker *>(_type.at(j));

									if (pk1->getpkNumber() < pk2->getpkNumber())
									{
												_type.swap(pk1, pk2);
									}
									else if (pk1->getpkNumber() == pk2->getpkNumber())
									{
												if (pk1->getSuit() > pk2->getSuit())
												{
															_type.swap(pk1, pk2);
												}
									}
						}
			}
}

void GameScene::update(float delta)
{

			static bool test = true;
			switch (m_state)
			{
						case 0: //发牌阶段
									callm->setVisible(false);
									playm->setVisible(false);
									winm->setVisible(false);
									losem->setVisible(false);
									break;
						case 1:
									callPointToGames();
									break;
						case 2:
									//出牌阶段								
									playCardInTable();
									break;
						case 3:
									//结束阶段
									gameEnding();
									break;
						default:break;
			}
}

void GameScene::showC()
{
			

			int pksize = m_player->m_pokers.size();
			m_player->m_showCardType.clear();
			m_player->clearTable(m_player->m_pokers);
			noCalled->setVisible(false);
			for (int i = 0; i < pksize; ++i)
			{
						Poker *pk = static_cast<Poker *>(m_player->m_pokers.at(i));
						if (pk->getSelectedPk()&& pk->getUsed ())
						{
									m_player->m_showCardType.pushBack(pk);												
						}
			}
	
			if (m_player->getPokerType (m_player->m_showCardType)==ERROR_CARD)
			{
						return;
			}
			//第一次出牌

			//for (int i = 0; i < m_player->m_showCardType.size(); ++i)
			//{
			//			log("%d  %d", i, static_cast<Poker *>(m_player->m_showCardType.at(i))->getpkNumber());

			//}
			if (!(m_player->lastPokers.size()))
			{
						//m_player->clearTable(m_player->m_pokers);
						m_player->putCardInMiddle(m_player->m_showCardType);
						m_player->checkcard(m_player->m_pokers,isHold);		
						++isHold;
						return;
			}



			if ( m_player->m_showCardType.size ())
			{
						if (static_cast<Poker *>(m_player->lastPokers.at(0))->owner != static_cast<Poker *>(m_player->m_showCardType.at(0))->owner)
						{
									// 要出的牌是否比比最后的牌大，如果大，可以出，否则返回
									if ((m_player->compareCard(m_player->lastPokers, m_player->m_showCardType)))
									{
												//m_player->clearTable(m_player->m_pokers);
												m_player->putCardInMiddle(m_player->m_showCardType);
												m_player->checkcard(m_player->m_pokers,isHold);
									}
									else
									{
												return;
									}
						}
						else //最后的牌，是否是自己出的如果是，继续出
						{							
									
												//m_player->clearTable(m_player->m_pokers);
												m_player->putCardInMiddle(m_player->m_showCardType);
												m_player->checkcard(m_player->m_pokers,isHold);
									
						}
						++isHold;
			}
				
}

void GameScene::showCAI(Vector<Ref *> &_AICard, tagOutCardResult &cardResult)
{

			int pksize = _AICard.size();		
			m_player->m_showCardTypeAI.clear();
			
			
			for (int i = 0; i < cardResult.cbCardCount; ++i)
			{
						int pkNum = cardResult.cbResultCard[i];
						
						for (int k=0; k < _AICard.size(); ++k)
						{
									if (pkNum == static_cast<Poker *>(_AICard.at(k))->getpkNumber()&& static_cast<Poker *>(_AICard.at(k))->getUsed ())
									{
												m_player->m_showCardTypeAI.pushBack(static_cast<Poker *>(_AICard.at(k)));	
												static_cast<Poker *>(_AICard.at(k))->setUsed(false);												
												break;												
									}
						}
						
			}

			if (m_player->getPokerType(m_player->m_showCardTypeAI) == ERROR_CARD)
			{
					
						for (int i = 0; i < m_player->m_showCardTypeAI.size(); ++i)
						{
									static_cast<Poker *>(m_player->m_showCardTypeAI.at(i))->setUsed(true);
						}
						
						return;
			}
			//第一次出牌

			//for (int i = 0; i < m_player->m_showCardType.size(); ++i)
			//{
			//			log("%d  %d", i, static_cast<Poker *>(m_player->m_showCardType.at(i))->getpkNumber());

			//}
			if (!(m_player->lastPokers.size()))
			{
						//m_player->clearTable(_AICard);
						m_player->putCardInMiddle(m_player->m_showCardTypeAI);
						m_player->checkcard(_AICard, isHold);
						
						return;
			}
			else {
						if (m_player->m_showCardTypeAI.size())
						{
									if (static_cast<Poker *>(m_player->lastPokers.at(0))->owner != static_cast<Poker *>(m_player->m_showCardTypeAI.at(0))->owner)
									{
												// 要出的牌是否比比最后的牌大，如果大，可以出，否则返回
												if ((m_player->compareCard(m_player->lastPokers, m_player->m_showCardTypeAI)))
												{
															//m_player->clearTable(_AICard);
															m_player->putCardInMiddle(m_player->m_showCardTypeAI);
															m_player->checkcard(_AICard, isHold);
												}
									}
									else //最后的牌，是否是自己出的如果是，继续出
									{

												//m_player->clearTable(_AICard);
												m_player->putCardInMiddle(m_player->m_showCardTypeAI);
												m_player->checkcard(_AICard, isHold);

									}
						}
			}




			
}

void GameScene::AIputCard(Vector<Ref*>& _AICard)
{
			m_player->checkcard(_AICard, isHold);
			//分析手牌
			m_player->clearTable(_AICard);
			if (static_cast<Poker *>(_AICard.at(0))->owner==1)
			{
						ai1noCalled->setVisible(false);
			}
			else
			{
						ai2noCalled->setVisible(false);
			}
			tagAnalyseResult tagResult;
		/*	for (int i = 0; i < _AICard.size(); ++i)
			{
						log("%d,%d", i, static_cast<Poker*>(_AICard.at(i))->getpkNumber());
			}*/
			m_player->analyseCards(_AICard,tagResult);
		/*	for (int i = 0; i < 4; ++i)
			{
						log("%d  ,  %d*************************** :" ,i,tagResult.resultCount[i]);
						for (int j = 0; j <(i+1)*tagResult.resultCount[i]; ++j)
						{																
									log(" %d", tagResult.cardData[i][j]);
						}
			}*/
			tagOutCardResult cardResult;
			memset(&cardResult, 0, sizeof(cardResult));
			
			if (!(m_player->lastPokers.size()))
			{
						if (aiCanPutCard(_AICard, m_player->lastPokers, cardResult))
						{
									//出牌 更新lastpokers
									showCAI(_AICard, cardResult);
						}
						else
						{
									aiNoCalled(_AICard);
						}
			}
			else 
			{
						if (static_cast<Poker *>(_AICard.at(0))->owner != static_cast<Poker *>(m_player->lastPokers.at(0))->owner)
						{
									if (aiCanPutCard(_AICard, m_player->lastPokers, cardResult))
									{
												showCAI(_AICard, cardResult);
									}
									else 
									{
												aiNoCalled(_AICard);
									}

						}
						else
						{
									//m_player->clearTable(_AICard);
									for (int i = 0; i < m_player->lastPokers.size(); ++i)
									{
												static_cast<Poker *>(m_player->lastPokers.at(i))->setUsed(false);
									}
									m_player->lastPokers.clear();
									m_player->checkcard(_AICard, isHold);
									if (aiCanPutCard(_AICard, m_player->lastPokers, cardResult))
									{
												showCAI(_AICard, cardResult);
									}
									else
									{
												aiNoCalled(_AICard);
									}
						}
			}					
			++isHold;
			if (isHold == 3)
			{
						isHold = 0;
			}
			
			//出牌


}

bool GameScene::aiCanPutCard(Vector<Ref*>& _AICard, Vector<Ref*>& _turnCard, tagOutCardResult & outCard)
{
			bool isRet = false;
			do
			{
				
						memset(&outCard, 0, sizeof(outCard));
						Vector<Ref *> tempPk;
						for (int i = 0; i < _AICard.size(); ++i)
						{
									tempPk.pushBack(static_cast<Poker *>(_AICard.at(i))->copy ());
						}
						CARD_TYPE turnType = static_cast<CARD_TYPE>(m_player->getPokerType(_turnCard));
						
						switch (turnType)
						{
									case ERROR_CARD:
									{												
												int pkLogicValue = static_cast<Poker *>(tempPk.back())->getpkNumber();
												int sameCount = 1;
												for (int i = 1; i < tempPk.size(); ++i)
												{
															if (static_cast<Poker *>(tempPk.at(tempPk.size() - i - 1))->getpkNumber() == pkLogicValue) ++sameCount;
															else break;
												}

												if (sameCount > 1)
												{
															outCard.cbCardCount = sameCount;
															for (int j = 0; j < sameCount; ++j) outCard.cbResultCard[j] = static_cast<Poker *>(tempPk.at(tempPk.size() - j - 1))->getpkNumber();
															return true;
												}

												outCard.cbCardCount = 1;
												outCard.cbResultCard[0] = static_cast<Poker *>(tempPk.back())->getpkNumber();
												return true;
									}
									case SINGLE_CARD:
									case DOUBLE_CARD:
									case THREE_CARD:
									{
												int pkLogicValue = static_cast<Poker *>(_turnCard.at(0))->getpkNumber();
												tagAnalyseResult analyseResult;
												m_player->analyseCards(tempPk, analyseResult);
												if (_turnCard.size() <= 1)
												{
															for (int i = 0; i < analyseResult.resultCount[0]; ++i)
															{
																		int index = analyseResult.resultCount[0] - i - 1;
																		if (analyseResult.cardData[0][index] > pkLogicValue)
																		{
																					outCard.cbCardCount = _turnCard.size();
																					outCard.cbResultCard[0] = analyseResult.cardData[0][index];
																					return true;
																		}
															}
												}

												if (_turnCard.size() <= 2)
												{
															for (int i = 0; i < analyseResult.resultCount[1]; ++i)
															{
																		int index = (analyseResult.resultCount[1] - i - 1) * 2;
																		if (analyseResult.cardData[1][index] > pkLogicValue)
																		{
																					outCard.cbCardCount = _turnCard.size();
																					for (int j = 0; j < _turnCard.size(); ++j)
																					{
																								outCard.cbResultCard[j] = analyseResult.cardData[1][index + j];
																					}
																					return true;
																		}
															}
												}
												if (_turnCard.size() <= 3)
												{
															for (int i = 0; i < analyseResult.resultCount[2]; ++i)
															{
																		int index = (analyseResult.resultCount[2] - i - 1) * 3;
																		if (analyseResult.cardData[2][index] > pkLogicValue)
																		{
																					outCard.cbCardCount = _turnCard.size();
																					for (int j = 0; j < _turnCard.size(); ++j)
																					{
																								outCard.cbResultCard[j] = analyseResult.cardData[2][index + j];
																					}
																					return true;
																		}
															}
												}
												break;
									}
									case CONNECT_CARD:
									{
												if (tempPk.size() < _turnCard.size()) break;

												int pkLogicValue = static_cast<Poker *>(_turnCard.at(0))->getpkNumber();

												for (int i = (_turnCard.size() - 1); i < tempPk.size(); ++i)
												{
															int handPkLogicValue = static_cast<Poker *>(tempPk.at(tempPk.size() - i - 1))->getpkNumber();
															
															if (handPkLogicValue >= 12) break;
															if (handPkLogicValue <= pkLogicValue) continue;

															int lineCount = 0;
															for (int j = (tempPk.size() - i - 1); j < tempPk.size(); ++j)
															{
																		if (static_cast<Poker *>(tempPk.at(j))->getpkNumber() + lineCount == handPkLogicValue)
																		{
																					outCard.cbResultCard[lineCount++] = static_cast<Poker *>(tempPk.at(j))->getpkNumber();
																					if (lineCount == _turnCard.size())
																					{
																								outCard.cbCardCount = _turnCard.size();
																								return true;
																					}
																		}

															}
												}
												break;
									}
									case COMPANY_CARD:
									{
												if (tempPk.size() < _turnCard.size()) break;

												int pkLogicValue = static_cast<Poker *>(_turnCard.at(0))->getpkNumber();

												for (int i = _turnCard.size() - 1; i < tempPk.size(); ++i)
												{
															int handPkLogicValue = static_cast<Poker *>(tempPk.at(tempPk.size() - i - 1))->getpkNumber ();

															if (handPkLogicValue <= pkLogicValue) continue;
															if ((_turnCard.size() > 1) && (handPkLogicValue >= 12)) break;

															int lineCount = 0;
															for (int j = tempPk.size() - i - 1; j < (tempPk.size() - 1); ++j)
															{
																		if ((static_cast<Poker *>(tempPk.at(j))->getpkNumber() + lineCount == handPkLogicValue)
																		   && (static_cast<Poker *>(tempPk.at(j + 1))->getpkNumber() + lineCount == handPkLogicValue))
																		{
																					outCard.cbResultCard[lineCount * 2] = static_cast<Poker *>(tempPk.at(j))->getpkNumber();
																					outCard.cbResultCard[(lineCount++)* 2+1] = static_cast<Poker *>(tempPk.at(j+1))->getpkNumber();
																					
																					if (lineCount * 2 == _turnCard.size())
																					{
																								outCard.cbCardCount = _turnCard.size();
																								return true;
																					}

																		}
															}
												}
												break;
									}
									case AIRCRAFT_CARD:
									case AIRCRAFT_SINGLE_CARD:
									case AIRCRAFT_DOBULE_CARD:
									{
												if (tempPk.size() < _turnCard.size()) break;

												int pkLogicValue = 0;
												for (int i = 0; i < _turnCard.size() - 2; ++i)
												{
															pkLogicValue = static_cast<Poker *>(_turnCard.at(i))->getpkNumber();
															if (static_cast<Poker *>(_turnCard.at(i + 1))->getpkNumber() != pkLogicValue) continue;
															if (static_cast<Poker *>(_turnCard.at(i + 2))->getpkNumber() != pkLogicValue) continue;
															break;
												}

												int turnLineCount = 0;
												if (turnType == AIRCRAFT_SINGLE_CARD) turnLineCount = _turnCard.size() / 4;
												else if (turnType == AIRCRAFT_DOBULE_CARD)turnLineCount = _turnCard.size() / 5;
												else turnLineCount = _turnCard.size() / 3;

												for (int i = turnLineCount * 3 - 1; i < tempPk.size(); ++i)
												{
															int handLogicValue = static_cast<Poker *>(tempPk.at(tempPk.size() - i - 1))->getpkNumber ();

															if (handLogicValue <= pkLogicValue) continue;
															if ((turnLineCount > 1) && (handLogicValue >= 12)) break;

															int lineCount = 0;
															for (int j = (tempPk.size() - i - 1); j < (tempPk.size() - 2); ++j)
															{
																		outCard.cbCardCount = 0;

																		if ((static_cast<Poker *>(tempPk.at(j))->getpkNumber() + lineCount) != handLogicValue) continue;
																		if ((static_cast<Poker *>(tempPk.at(j+1))->getpkNumber() + lineCount) != handLogicValue) continue;
																		if ((static_cast<Poker *>(tempPk.at(j+2))->getpkNumber() + lineCount) != handLogicValue) continue;

																		outCard.cbResultCard[lineCount * 3] = static_cast<Poker *>(tempPk.at(j))->getpkNumber();
																		outCard.cbResultCard[lineCount * 3+1] = static_cast<Poker *>(tempPk.at(j+1))->getpkNumber();
																		outCard.cbResultCard[(lineCount++) * 3+2] = static_cast<Poker *>(tempPk.at(j+2))->getpkNumber();

																		if (lineCount == turnLineCount)
																		{
																					outCard.cbCardCount = lineCount * 3;
																				
																					Vector<Ref *> leftCardData;
																					int tempCount = 0;
																					for (int i = 0; i < tempPk.size(); ++i)
																					{
																								if (outCard.cbResultCard[tempCount] == static_cast<Poker *>(tempPk.at(i))->getpkNumber())
																								{
																											++tempCount;
																											continue;
																								}
																								else
																								{
																											leftCardData.pushBack(static_cast<Poker *>(tempPk.at(i))->copy());
																								}
																					}

																					tagAnalyseResult analyseResultLeft;
																					m_player->analyseCards(leftCardData, analyseResultLeft);

																					if (turnType == AIRCRAFT_SINGLE_CARD)
																					{
																								for (int k = 0; k < analyseResultLeft.resultCount[0]; ++k)
																								{
																											if (outCard.cbCardCount == _turnCard.size()) break;

																											int index = analyseResultLeft.resultCount[0] - k - 1;
																											int signedCard = analyseResultLeft.cardData[0][index];
																											outCard.cbResultCard[outCard.cbCardCount++] = signedCard;
																								}

																								for (int k = 0; k < analyseResultLeft.resultCount[1] * 2; ++k)
																								{
																											if (outCard.cbCardCount == _turnCard.size())break;

																											int index = (analyseResultLeft.resultCount[1] * 2 - k - 1);
																											int signedCard = analyseResultLeft.cardData[1][index];
																											outCard.cbResultCard[outCard.cbCardCount++] = signedCard;
																								}

																								for (int k = 0; k < analyseResultLeft.resultCount[2] * 3; ++k)
																								{
																											if (outCard.cbCardCount == _turnCard.size()) break;

																											int index = (analyseResultLeft.resultCount[2] * 3 - k - 1);
																											int signedCard = analyseResultLeft.cardData[2][index];
																											outCard.cbResultCard[outCard.cbCardCount++] = signedCard;
																								}

																								for (int k = 0; k < analyseResultLeft.resultCount[3] * 4; ++k)
																								{
																											if (outCard.cbCardCount == _turnCard.size()) break;

																											int index = (analyseResultLeft.resultCount[3] * 4 - k - 1);
																											int signedCard = analyseResultLeft.cardData[3][index];
																											outCard.cbResultCard[outCard.cbCardCount++] = signedCard;
																								}
																					}
																					//对牌处理 
																					if (turnType == AIRCRAFT_DOBULE_CARD)
																					{
																								for (int k = 0; k < analyseResultLeft.resultCount[1]; ++k)
																								{
																											if (outCard.cbCardCount == _turnCard.size()) break;

																											int index = (analyseResultLeft.resultCount[1] - k - 1) * 2;
																											int cardData1 = analyseResultLeft.cardData[1][index];
																											int cardData2 = analyseResultLeft.cardData[1][index + 1];
																											outCard.cbResultCard[outCard.cbCardCount++] = cardData1;
																											outCard.cbResultCard[outCard.cbCardCount++] = cardData2;
																								}

																								for (int k = 0; k < analyseResultLeft.resultCount[2]; ++k)
																								{
																											if (outCard.cbCardCount == _turnCard.size()) break;

																											int index = (analyseResultLeft.resultCount[2] - k - 1) * 3;
																											int cardData1 = analyseResultLeft.cardData[2][index];
																											int cardData2 = analyseResultLeft.cardData[2][index + 1];
																											outCard.cbResultCard[outCard.cbCardCount++] = cardData1;
																											outCard.cbResultCard[outCard.cbCardCount++] = cardData2;
																								}

																								for (int k = 0; k < analyseResultLeft.resultCount[3]; ++k)
																								{
																											if (outCard.cbCardCount == _turnCard.size()) break;

																											int index = (analyseResultLeft.resultCount[3] - k - 1) * 4;
																											int cardData1 = analyseResultLeft.cardData[3][index];
																											int cardData2 = analyseResultLeft.cardData[3][index + 1];
																											outCard.cbResultCard[outCard.cbCardCount++] = cardData1;
																											outCard.cbResultCard[outCard.cbCardCount++] = cardData2;
																								}

																					}

																					if (outCard.cbCardCount == _turnCard.size()) return true;

																		}

															}
												}
												break;
									}

									
						}
						if ((tempPk.size() >= 4) && (turnType != MISSILE_CARD))
						{
									int pkLogicValue = 0;
									if (turnType == BOMB_CARD) pkLogicValue = static_cast<Poker *>(_turnCard.at(0))->getpkNumber();

									for (int i = 3; i < tempPk.size(); ++i)
									{
												int handLogicValue = static_cast<Poker *>(tempPk.at(tempPk.size() - i - 1))->getpkNumber();

												if (handLogicValue <= pkLogicValue) continue;

												int tempLogicValue= static_cast<Poker *>(tempPk.at(tempPk.size() - i - 1))->getpkNumber();
												int j=0;
												for ( j = 1; j < 4; ++j)
												{
															if (static_cast<Poker *>(tempPk.at(tempPk.size() + j - i - 1))->getpkNumber() != tempLogicValue)	break;
												}

												if (j != 4) continue;

												outCard.cbCardCount = 4;
												outCard.cbResultCard[0] = static_cast<Poker *>(tempPk.at(tempPk.size() - i - 1))->getpkNumber();
												outCard.cbResultCard[1] = static_cast<Poker *>(tempPk.at(tempPk.size() - i ))->getpkNumber();
												outCard.cbResultCard[2] = static_cast<Poker *>(tempPk.at(tempPk.size() - i + 1))->getpkNumber();
												outCard.cbResultCard[3] = static_cast<Poker *>(tempPk.at(tempPk.size() - i + 2))->getpkNumber();
												return true;

									}

						}

						if ((tempPk.size() >= 2) && (static_cast<Poker *>(tempPk.at(0))->getpkNumber() == 14) && (static_cast<Poker *>(tempPk.at(1))->getpkNumber() == 13))
						{
									outCard.cbCardCount = 2;
									outCard.cbResultCard[0] = static_cast<Poker *>(tempPk.at(0))->getpkNumber();
									outCard.cbResultCard[1] = static_cast<Poker *>(tempPk.at(1))->getpkNumber();
									return true;
						}						
			} while (0);
			return false;
}

void GameScene::showCallPoint(int point)
{
			ValueMap bstring= FileUtils::getInstance()->getValueMapFromFile(buttonStrFileName);
			std::string str;
			if (point == 1)
			{
						str = bstring.at("yifen").asString();
			}
			else if (point == 2)
			{
						str = bstring.at("erfen").asString();
			}
			else if (point == 3)
			{
						str = bstring.at("sanfen").asString().c_str();
			}
			 callPoint = Label::createWithSystemFont(str,"Courier New",40);
		
			
			 callPoint->setPosition(winSize.width / 2, winSize.height / 2);
			
			addChild(callPoint, 10, 11);
}

void GameScene::callPointToGames()
{
			if (getChildByTag(11) != nullptr)
			{
						getChildByTag(11)->removeFromParent();
			}
			startGame->setVisible(false);
			if (calledTime == 0 || calledNumber==3)
			{
						//isLoad = isHold;
						insertLoadCard();
						showCallPoint(calledNumber);
						setLoadSign();
						m_state = 2;
			}
			switch (isCalled)
			{
						case 0://玩家叫
						{
									callm->setVisible(true);
									playm->setVisible(false);
									winm->setVisible(false);
									losem->setVisible(false);
									if (calledNumber == -1)
									{
												//可以叫1,2,3,pass											
									}
									else if (calledNumber == 1)
									{
												//可以叫2,3,pass
												static_cast<MenuItem *>(callm->getChildByTag(1))->setEnabled(false);
									}
									else if(calledNumber==2)
									{
												//可以叫3,pass
												static_cast<MenuItem *>(callm->getChildByTag(1))->setEnabled(false);
												static_cast<MenuItem *>(callm->getChildByTag(2))->setEnabled(false);

									 }		
									break;
						}
								
						case 1://电脑1叫									
						case 2://电脑2叫
						{
									callm->setVisible(false);
									playm->setVisible(false);
									winm->setVisible(false);
									losem->setVisible(false);
									//分析牌力 
									//如果牌力大，增加分数									
									{
												if (calledNumber == -1)
												{
															//可以叫1,2,3,pass
															calledNumber = 1;
															 showCallPoint(1);
															
												}
												else if (calledNumber == 1)
												{
															//可以叫2,3,pass
															++calledNumber;
															showCallPoint(calledNumber);
												}
												else if (calledNumber == 2)
												{
															//可以叫3,pass
															++calledNumber;
															isLoad = isCalled;
															isStarted = true;
															showCallPoint(calledNumber);
												}
												isHold = isCalled;
												if (isCalled == 2 && calledTime!=0)
												{
															isCalled = 0;
												}
												else
												{
															++isCalled;
												}
												--calledTime;
									}
									break;
									//如果牌力小，不叫
						}
						
						default://出错break
									break;
			}
}

void GameScene::playCardInTable()
{

			//if (getChildByTag(11) != nullptr)
			//{
			//			getChildByTag(11)->removeFromParent();
			//}
			
			//log("myc:%d,AI1:%d,AI2:%d", m_player->m_pokers.size(), m_player->AI1_pokers.size(), m_player->AI2_pokers.size());
			if (!(m_player->m_pokers.size()) || !(m_player->AI1_pokers.size()) || !(m_player->AI2_pokers.size()))
			{
						m_state = 3;
						return;
			}
		
			//检测谁出牌
			switch (isHold)
			{
						case 0://玩家出牌
						{
									callm->setVisible(false);
									playm->setVisible(true);
									winm->setVisible(false);
									losem->setVisible(false);
						}
									break;
						case 1://电脑2出牌
						{
									callm->setVisible(false);
									playm->setVisible(false);
									winm->setVisible(false);
									losem->setVisible(false);
									AIputCard(m_player->AI1_pokers);

						}
									break;
						case 2://电脑1出牌
						{
									callm->setVisible(false);
									playm->setVisible(false);
									winm->setVisible(false);
									losem->setVisible(false);
									AIputCard(m_player->AI2_pokers);
						}
									break;
						default:
									break;
			}
			
			

}

void GameScene::insertLoadCard()
{

			
			//log("hold : %d load :%d called :%d", isHold, isLoad,isCalled);
			do
			{
						Vector<Ref *> *pk;
						switch (isLoad)
						{
									case 0:
									{
												pk = &(m_player->m_pokers);
												for (int i = 0; i < 3; ++i)
												{
															pk->pushBack(static_cast<Poker *>(_pokers.at(53 - i))->copy());
															static_cast<Poker *>(_pokers.at(53 - i))->setVisible(false);
															static_cast<Poker *>(pk->back())->owner = 0;
															static_cast<Poker *>(pk->back())->setCanSelectdPk(true);
															addChild(static_cast<Poker *>(pk->back()), 5);
												}
												isCalled = -1;
												break;
									}
									case 1:
									{
												pk = &(m_player->AI1_pokers);
												for (int i = 0; i < 3; ++i)
												{
															pk->pushBack(static_cast<Poker *>(_pokers.at(53 - i))->copy());
															static_cast<Poker *>(_pokers.at(53 - i))->setVisible(false);
															static_cast<Poker *>(pk->back())->owner = 1;
															static_cast<Poker *>(pk->back())->setReverse();
															addChild(static_cast<Poker *>(pk->back()), 5);
												}
												isCalled = -1;
												break;
									}
									case 2:
									{
												pk = &(m_player->AI2_pokers);
												for (int i = 0; i < 3; ++i)
												{
															pk->pushBack(static_cast<Poker *>(_pokers.at(53 - i))->copy());
															static_cast<Poker *>(_pokers.at(53 - i))->setVisible(false);
															static_cast<Poker *>(pk->back())->owner = 2;
															static_cast<Poker *>(pk->back())->setReverse();
															addChild(static_cast<Poker *>(pk->back()), 5);
												}
												isCalled = -1;
												break;
									}
									

						}
						if (!pk)
						{
									return;
						}
						swapCard(*pk);
						isLoad = isHold;
						m_player->checkcard(*pk, isLoad);
			}
			while (isCalled != -1);
}

void GameScene::rePlay()
{
			do {
						//Director::getInstance()->popScene();
					
						delete m_player;
						m_player = new Player();
						_pokers.clear();
						Director::getInstance()->replaceScene(GameScene::scene());
			} while (0);
	
}

void GameScene::gameEnding()
{
			playm->setVisible(false);
			if (isLoad == 0)
			{
						if (!(m_player->m_pokers.size()))
						{
									winm->setVisible(true);
						}
						else
						{
									losem->setVisible(true);
						}
			}
			else if (isLoad == 1)
			{
						if (!(m_player->AI1_pokers.size()))
						{
									losem->setVisible(true);
						}
						else
						{
									winm->setVisible(true);
						}
			}
			else if (isLoad == 2)
			{
						if (!(m_player->AI2_pokers.size()))
						{
									losem->setVisible(true);
						}
						else
						{
									winm->setVisible(true);
						}
			}
}



bool GameScene::deleteCardsBak(Vector<Ref*>& _cards)
{
			bool isRet = false;
			do
			{
						_cards.clear();
						isRet = true;
			} while (0);
			return isRet;
}

void GameScene::setLoadSign()
{
			if (getChildByTag(11) != nullptr)
			{
						getChildByTag(11)->removeFromParent();
			}
			Point ppt = Point(winSize.width / 2, pkHeight - 16 * 2 - 5);
			Point AI1pts = Point(winSize.width   - pkHeight  , winSize.height - pkHeight + 16 * 2 + 5);
			Point AI2pts = Point(pkHeight, pkHeight - 16 * 2 - 5);
			loadSign = Sprite::create(signFileName, Rect(0, 0, (float)16.6 * 3 + 1, 64));
			farmerSign1 = Sprite::create(signFileName, Rect((float)16.6 * 3 + 2, 0, (float)16.6 * 3 + 1, 64));
			farmerSign2 = Sprite::create(signFileName, Rect((float)16.6 * 3 + 2, 0, (float)16.6 * 3 + 1, 64));
			loadSign->setAnchorPoint(Point(0.5, 0.5));
			farmerSign1->setAnchorPoint(Point(0.5, 0.5));
			farmerSign2->setAnchorPoint(Point(0.5, 0.5));
			if (isLoad == 0)
			{
						loadSign->setPosition(ppt);
						farmerSign1->setPosition(AI1pts);
						farmerSign2->setPosition(AI2pts);
			}
			else if (isLoad == 1)
			{
						loadSign->setPosition(AI1pts);
						farmerSign1->setPosition(ppt);
						farmerSign2->setPosition(AI2pts);
			}
			else if (isLoad == 2)
			{
						loadSign->setPosition(AI2pts);
						farmerSign1->setPosition(ppt);
						farmerSign2->setPosition(AI1pts);
			}
			addChild(loadSign);
			addChild(farmerSign1);
			addChild(farmerSign2);
}

void GameScene::aiNoCalled(Vector<Ref *> &_type)
{
			
			if (static_cast<Poker *>(_type.at(0))->owner == 0)
			{
						noCalled->setVisible(true);
						noCalled->setPosition(Point(winSize.width / 2, winSize.height / 2));

			}
			else if (static_cast<Poker *>(_type.at(0))->owner == 1)
			{
						ai1noCalled->setVisible(true);
						Point point = Point(m_player->AIPt1.x - pkInterval, winSize.height/2);						
						ai1noCalled->setPosition(point);
			}
			else if (static_cast<Poker *>(_type.at(0))->owner == 2)
			{
						ai2noCalled->setVisible(true);
						Point point = Point(m_player->AIPt2.x + pkHeight + pkInterval, winSize.height/2);						
						ai2noCalled->setPosition(point);
			}
			

}

void GameScene::testSocket()
{
			//menusc = Menu::create();
			//MenuItem *startserver = MenuItemFont::create("start server", [&](Ref *sender)
			//{
			//			Net::Listen();
			//			schedule([&](float) {
			//						if (Net::isConnected() == 2)
			//						{
			//									unschedule("server");
			//									//memset(buf, 0, sizeof(buf));												
			//									schedule([&](float) {
			//												if (Net::isRecvComplete())
			//												{
			//															CCLOG("server isRecvComplete");
			//															char buf[26] = "hello cocos 11";
			//															Net::Send(1, buf, sizeof(buf));
			//															unschedule("serverRecv1");
			//															int len;
			//															char *data = Net::RecvData(len);
			//															log("server:%s", data);
			//												}
			//									}, "serverRecv1");
			//						}
			//			}, "server");

			//			schedule([&](float)
			//			{
			//						if (Net::isConnected() == 3)
			//						{
			//									unschedule("server2");
			//									int len;
			//									char *data = Net::RecvData(len);
			//									log("server:%s", data);
			//									//memset(buf, 0, sizeof(buf));											
			//									schedule([&](float) {
			//												if (Net::isRecvComplete())
			//												{
			//															char buf[26] = "hello cocos 22";
			//															Net::Send(2, buf, sizeof(buf));
			//															unschedule("serverRecv2");
			//															int len;
			//															char *data = Net::RecvData(len);
			//															log("server:%s", data);
			//												}
			//									}, "serverRecv2");
			//						}
			//			}, "server2");


			//			static_cast<MenuItem *>(sender)->setEnabled(false);
			//			static_cast<MenuItem *>(this->menusc->getChildByTag(1102))->setEnabled(false);
			//});


			//MenuItem *startclient = MenuItemFont::create("start client", [&](Ref *sender) {
			//			static_cast<MenuItem *>(this->menusc->getChildByTag(1101))->setEnabled(false);
			//			static_cast<MenuItem *>(this->menusc->getChildByTag(1102))->setEnabled(false);
			//			if (Net::Connect("127.0.0.1"))
			//			{
			//						log("client:client on connect");
			//						char buf[26] = "yes,got it";
			//						Net::Send(0, buf, sizeof(buf));
			//						Net::RecvStart();
			//						schedule([&](float) {
			//									if (Net::isRecvComplete())
			//									{
			//												char buf1[26] = "hello china!";
			//												Net::Send(0, buf1, sizeof(buf1));
			//												CCLOG("client isRecvComplete");
			//												unschedule("clientRecv");
			//												int len;
			//												char *data = Net::RecvData(len);
			//												log("client:%s", data);
			//									}
			//						}, "clientRecv");
			//			}
			//			else
			//			{
			//						log("client:connect failture....");
			//			}

			//});
			//startserver->setPosition(Point(-100, 0));
			//startclient->setPosition(Point(100, 0));
			//menusc->addChild(startserver, 1, 1101);
			//menusc->addChild(startclient, 1, 1102);

			//addChild(menusc, 1, 1100);
}

bool GameScene::initAndShuffleCards()
{
			bool ret = false;
			do
			{
						for (int i = 0; i < 54; ++i)
						{
									pokersWithNet[i] = i;
						}
						std::random_shuffle(pokersWithNet, &pokersWithNet[53]);
						ret = true;
			} while (0);
			return ret;
}

bool GameScene::dealWithCardsNet()
{
			bool ret = false;
			do
			{
						int load = rand() % 3;				
						if (load == 0)
						{
									loadertag = 0;
									player1tag = 1;
									player2tag = 2;
									for (int i = 0; i < 17; ++i)
									{
												handPorkers[i] = pokersWithNet[i*3];
												player1HandPokers[i] = pokersWithNet[i*3+1];
												player2HandPokers[i] = pokersWithNet[i*3+2];
									}
									
						}
						else if (load == 1)
						{
									loadertag = 1;
									player1tag = 2;
									player2tag = 0;
									for (int i = 0; i < 17; ++i)
									{
												
												player1HandPokers[i] = pokersWithNet[i * 3];
												player2HandPokers[i] = pokersWithNet[i*3 + 1];
												handPorkers[i] = pokersWithNet[i*3+2];
									}
						}
						else if (load == 2)
						{
									loadertag = 2;
									player1tag = 0;
									player2tag = 1;
									for (int i = 0; i < 17; ++i)
									{
												
												player2HandPokers[i] = pokersWithNet[i*3];
												handPorkers[i] = pokersWithNet[i*3+1];
												player1HandPokers[i] = pokersWithNet[i*3 + 2];
									}
						}
						for (int i = 0; i < 3; ++i)
						{
									loadCards[i] = pokersWithNet[i + 51];
						}
						ret = true;
			} while (0);
			return ret;
}



void GameScene::startServer(Ref * menuitem)
{
			do
			{
						static_cast<MenuItem *>(menuitem)->setEnabled(false);
						MenuItem *clientMN = static_cast<MenuItem *>(static_cast<MenuItem *>(menuitem)->getUserObject());
						clientMN->setEnabled(false);
						if (Net::Listen())
						{
									Net::playertag = 0;
									callSendScore = -1;
									callSendTime = -1;
									schedule(std::bind(&GameScene::checkServer,this,std::placeholders::_1) , 1.0f,"checkServer");
						}					
			} while (0);


}

void GameScene::startClient(Ref * menuitem)
{
			static_cast<MenuItem *>(menuitem)->setEnabled(false);
			MenuItem *serverMN = static_cast<MenuItem *>(static_cast<MenuItem *>(menuitem)->getUserObject());
			serverMN->setEnabled(false);
			if (Net::Connect("127.0.0.1"))
			{
						Net::RecvStart();
						Net::playertag = -1;
						callSendScore = -1;
						callSendTime = -1;
						schedule(std::bind(&GameScene::checkRecv, this, std::placeholders::_1), "checkRecv");
			}
}

void GameScene::checkServer(float dt)
{
			do
			{
						if (Net::isConnected() == 3)
						{
									//给Net playtag 打上标记
									//开始发牌，进入主游戏逻辑
									//初始化工作
									unschedule("checkServer");
									setUserMark(0);
									callBackTag[0] = -1;
									callBackTag[1] = -1;
									//洗牌
									CC_BREAK_IF(!initAndShuffleCards());
									//装牌
									CC_BREAK_IF(!dealWithCardsNet());
									//标签初始化
									CC_BREAK_IF(!initMark());
									//开启服务器接收循环
									schedule(std::bind(&GameScene::checkRecvServer, this, std::placeholders::_1), "checkRecvServer");									
									
						}
						else if(Net::isConnected ()>3)
						{							

						}
			} while (0);
}

void GameScene::checkRecv(float dt)
{
			do
			{
						if (Net::isRecvComplete())
						{
									unschedule("checkRecv");
									getNetBuf();
									if (recvBuf[0] == '0')
									{
												if (recvBuf[1] == '0')
												{
															Net::playertag = atoi(&recvBuf[2]);
															Net::Send(0, "01", 2);
															Net::RecvStart();
															schedule(std::bind(&GameScene::checkRecv, this, std::placeholders::_1), "checkRecv");
															return;
												}
												if (recvBuf[1] == '3')
												{
															callm->setVisible(false);
															//获取地主牌
															if (recvBuf[2] - '0' == Net::playertag)
															{
																		initLoadCard();
																	
															}
															/*else
															{
																		callCatchHold[0] = recvBuf[2] - '0';
																		callCatchHold[1] = recvBuf[3] - '0';
																		updateLoadCard();
															}*/
															isStarted = true;
															Net::Send(0, "30", 2);
															Net::RecvStart();
															schedule(std::bind(&GameScene::checkRecv, this, std::placeholders::_1), "checkRecv");
												}
									}
									if (recvBuf[0] == '1')
									{
												for (int i = 0; i < 17; ++i)
												{
															handPorkers[i] = recvBuf[1 + i] - '0';
												}
												for (int i = 0; i < 3; ++i)
												{
															loadCards[i] = recvBuf[18 + i] - '0';
												}
												Net::Send(0, "02", 2);
												//生成卡牌
												CC_BREAK_IF(!initPokersNet());
												//摆拍
												CC_BREAK_IF(!showCardsInTableNet());
												//移除联接按钮
												menusc->setVisible(false);
												Net::RecvStart();
												schedule(std::bind(&GameScene::checkRecv, this, std::placeholders::_1), "checkRecv");
												return;
									}
									if (recvBuf[0] == '2')
									{
												if (recvBuf[2] - '0' == 4)
												{
															callSendTag = recvBuf[1] - '0';
															callSendTime = recvBuf[3] - '0';
												}
												else
												{
															callSendTag = recvBuf[1] - '0';
															callSendScore = recvBuf[2] - '0';
															callSendTime = recvBuf[3] - '0';
												}
												if (callSendScore == 1)
												{
															static_cast<MenuItem *>(callm->getChildByTag(1))->setEnabled(false);
												}
												else if (callSendScore == 2)
												{
															static_cast<MenuItem *>(callm->getChildByTag(1))->setEnabled(false);
															static_cast<MenuItem *>(callm->getChildByTag(2))->setEnabled(false);
												}
												if (recvBuf[1] - '0' == Net::playertag)
												{
															callm->setVisible(true);
												}											
												Net::RecvStart();
												schedule(std::bind(&GameScene::checkRecv, this, std::placeholders::_1), "checkRecv");											
									}
								

						}
			} while (0);
			return;
}

void GameScene::checkRecvServer(float dt)
{
			do
			{
						if (getNetBuf(1))
						{
									if (strncmp("01", recvBuf, 2)==0)
									{
												//1号客户端 进入发牌阶段
												CC_BREAK_IF(!sendCards(1));

									}
									else if (strncmp("02", recvBuf, 2) == 0)
									{											
												//1号客户端接受扑克就绪 ，摆拍，进入叫分阶段
												//通知客户端进入叫牌阶段
												callBackTag[0] = 1;
												callSendTag = loadertag;
												callSendScore = 0;
												callSendTime = 0;
												char *call=analyseCallNum(callSendTag,callSendScore,callSendTime);
												Net::Send(1, call, 4);
									}
									else if (recvBuf[0]=='2')
									{

												if (recvBuf[2] - '0' == 4)
												{
															callSendTag = recvBuf[1] - '0';
															callSendTime = recvBuf[3] - '0';
												}
												else
												{
															callSendTag = recvBuf[1] - '0';
															callSendScore = recvBuf[2] - '0';
															callSendTime = recvBuf[3] - '0';
															callCatchHold[0] = 1;
															callCatchHold[1] = callSendScore;
												}

												if (callSendScore == 3 || callSendTime == 3)
												{
															char buf[4];
															buf[0] = '0';
															buf[1] = '3';
															buf[2] = callCatchHold[0] + '0';
															buf[3] = callCatchHold[1] + '0';
															Net::Send(1, buf, 4);
															Net::Send(2, buf, 4);
															if (callCatchHold[0] == 0)
															{
																		initLoadCard();
																		callm->setVisible(false);
															}
															else
															{
																		updateLoadCard();
															}
															break;
												}

												if (callSendScore==1)
												{
															static_cast<MenuItem *>(callm->getChildByTag(1))->setEnabled(false);
												}
												else if (callSendScore == 2)
												{
															static_cast<MenuItem *>(callm->getChildByTag(1))->setEnabled(false);
															static_cast<MenuItem *>(callm->getChildByTag(2))->setEnabled(false);
												}								

												if (callSendTag == 0)
												{
															callm->setVisible(true);
												}
												else if(callSendTag==2)
												{
															char *sendTagcheck = analyseCallNum(callSendTag, callSendScore, callSendTime);
															Net::Send(2, sendTagcheck, 4);
												}
									}
									else if (strncmp("30", recvBuf, 2) == 0)
									{
												//开始出牌
												callBackTag[0] = 2;
									}
						}
						if (getNetBuf(2))
						{
									if (strncmp("01", recvBuf, 2)==0)
									{
												//2号客户端进入发牌阶段									
												CC_BREAK_IF(!sendCards(2));
									}
									else if (strncmp("02", recvBuf, 2) == 0)
									{
												//通知客户端进入叫牌阶段
												callBackTag[1] = 1;
												callSendTag = loadertag;
												callSendScore = 0;
												callSendTime = 0;
												char *call = analyseCallNum(callSendTag,callSendScore,callSendTime);
												Net::Send(2, call, 4);
									}
									else if (recvBuf[0] == '2')
									{
												Net::Send(1, recvBuf, 4);
												if (recvBuf[2] - '0' == 4)
												{
															callSendTag = recvBuf[1] - '0';
															callSendTime = recvBuf[3] - '0';
												}
												else
												{
															callSendTag = recvBuf[1] - '0';
															callSendScore = recvBuf[2] - '0';
															callSendTime = recvBuf[3] - '0';
															callCatchHold[0] = 2;
															callCatchHold[1] = callSendScore;
												}
												
												if (callSendScore == 3 || callSendTime == 3)
												{
															char buf[4];
															buf[0] = '0';
															buf[1] = '3';
															buf[2] = callCatchHold[0] + '0';
															buf[3] = callCatchHold[1] + '0';
															Net::Send(1, buf, 4);
															Net::Send(2, buf, 4);
															if (callCatchHold[0] == 0)
															{
																		initLoadCard();
																		callm->setVisible(false);
															}
															else
															{
																		updateLoadCard();
															}
															break;
												}

												if (callSendScore == 1)
												{
															static_cast<MenuItem *>(callm->getChildByTag(1))->setEnabled(false);
												}
												else if (callSendScore == 2)
												{
															static_cast<MenuItem *>(callm->getChildByTag(1))->setEnabled(false);
															static_cast<MenuItem *>(callm->getChildByTag(2))->setEnabled(false);
												}



												if (callSendTag == 0)
												{
															callm->setVisible(true);
												}

									}
									else if (strncmp("30", recvBuf, 2) == 0)
									{
												//开始出牌
												callBackTag[1] = 2;
												
									}
						}
						if (callBackTag[0] == 1 && callBackTag[1] == 1)
						{
									//生成卡牌
									CC_BREAK_IF(!initPokersNet());
									//摆拍
									CC_BREAK_IF(!showCardsInTableNet());
									//移除联接按钮
									menusc->setVisible(false);
									//服务器添加叫牌按钮
									if (loadertag == 0)
									{
												callm->setVisible(true);
									}
									callBackTag[0] = -1;
									callBackTag[1] = -1;
						}
						else if (callBackTag[0] == 2 && callBackTag[1] == 2)
						{
									callm->setVisible(false);
									isStarted = true;
									callBackTag[0] = -1;
									callBackTag[1] = -1;
						}
						else if (callBackTag[0] == 3 && callBackTag[1] == 3)
						{
									
									callBackTag[0] = -1;
									callBackTag[1] = -1;
									
						}
			} while (0);
			
			return;
		
}

bool GameScene::dealSendBuf(const char * str, int len)
{
			bool ret = false;
			do
			{
						if (len > NET_BUF_SIZE)
						{
									return ret;
						}
						memset(sendBuf, 0, NET_BUF_SIZE);
						memcpy(sendBuf, str, len);
						ret = true;

			} while (0);
			return ret;
}

void GameScene::getNetBuf()
{
			if (Net::isRecvComplete())
			{
						memset(recvBuf, 0, NET_BUF_SIZE);
						int len;
						char *netBuf = Net::RecvData(len);
						memcpy(recvBuf, netBuf, strlen(netBuf)+1);
						memset(netBuf, 0, NET_BUF_SIZE);
			}
			return;
}

bool GameScene::getNetBuf(int tag)
{
			bool ret = false;
			do
			{
						if (Net::isRecvCompleteNet(tag))
						{
									memset(recvBuf, 0, NET_BUF_SIZE);
									int len;
									char *netBuf = Net::RecvData(len, tag);
									memcpy(recvBuf, netBuf, strlen(netBuf) + 1);
									memset(netBuf, 0, NET_BUF_SIZE);
									ret = true;
						}
			} while (0);
		
			return ret;
}

bool GameScene::initMark()
{
			bool ret = false;
			do
			{
						char buf1[5] = "001";
						char buf2[5] = "002";
						if (Net::Send(1, buf1, strlen(buf1)+1)!= 1)
						{
									break;
						}
						if (Net::Send(2, buf2, strlen(buf1)+1) != 2)
						{
									break;
						}
						ret = true;
			} while (0);
			return ret;
}

bool GameScene::sendCards(int tag)
{
			bool ret = false;
			do
			{
						char cardsBuf[21];
						memset(cardsBuf, 0, 21);
						if (tag == 1)
						{			
									cardsBuf[0] = '1';
									dealSendCards(player1HandPokers, 17);
									memcpy(&cardsBuf[1], sendBufbak, 17*sizeof(char));
									dealSendCards(loadCards, 3);
									memcpy(&cardsBuf[18], sendBufbak, 3 * sizeof(char));
									Net::Send(1, cardsBuf, 21);
									ret = true;
						}
						else if (tag == 2)
						{
									cardsBuf[0] = '1';
									dealSendCards(player2HandPokers, 17);
									memcpy(&cardsBuf[1], sendBufbak, 17 * sizeof(char));
									dealSendCards(loadCards, 3);
									memcpy(&cardsBuf[18], sendBufbak, 3 * sizeof(char));
									Net::Send(2, cardsBuf, 21);
									ret = true;
						}

			} while (0);
			
			return ret;
}

bool GameScene::dealSendCards(int * cards,const  int cardsLen)
{
			bool ret = false;
			do
			{
						memset(sendBufbak, 0, sizeof(sendBufbak));					
						char buf[20];
						memset(buf, 0, sizeof(buf));
						for (int i = 0; i < cardsLen; ++i)
						{
									buf[i] = '0' + cards[i];								
						}
						memcpy(sendBufbak , buf, cardsLen*sizeof(char));
						ret = true;
			} while (0);
			return ret;
}

bool GameScene::initPokersNet()
{
			bool ret = false;
			do
			{
						for (int i = 0; i < 17; ++i)
						{
									m_player->m_pokers.pushBack(analyseNumForPoker(handPorkers[i]));
						}
						for (int i = 0; i < 3; ++i)
						{
									m_player->load_Pokers.pushBack(analyseNumForPoker(loadCards[i]));
						}
						for (int i = 0; i < 17; ++i)
						{
									m_player->AI1_pokers.pushBack(analyseNumForPoker(54));
						}
						for (int i = 0; i < 17; ++i)
						{
									m_player->AI2_pokers.pushBack(analyseNumForPoker(54));
						}

						for (int i = 0; i < 17; ++i)
						{
									static_cast<Poker *>(m_player->m_pokers.at(i))->owner = 0;									
									static_cast<Poker *>(m_player->AI1_pokers.at(i))->owner = 1;
									static_cast<Poker *>(m_player->AI2_pokers.at(i))->owner = 2;
						}
						ret = true;
			} while (0);
			return ret;
}


bool GameScene::showCardsInTableNet()
{
			bool ret = false;
			do
			{
						handPokersCount = 17;
						player1HandPokersCount = 17;
						player2HandPokersCount = 17;					
						//player来摆拍
						//log("Scene=%p", this);
						//给player手牌，排序，按spade,heart,club,diamond,joker,2,A,k-3从左往右依次排序
						swapCard(m_player->m_pokers);
						//log("%p", m_player->m_pokers);
						if (!(m_player->updatePkPosition()))
						{
									break;
						}
						//添加玩家和AI手牌
						for (int index = 0; index < 17; ++index)
						{
									addChild(static_cast<Poker *>(m_player->m_pokers.at(index)), 5);
									//static_cast<Poker *>(m_player->m_pokers.at(index))->setReverse();
									static_cast<Poker *>(m_player->m_pokers.at(index))->setCanSelectdPk(true);
									
									addChild(static_cast<Poker *>(m_player->AI1_pokers.at(index)), 5);
									static_cast<Poker *>(m_player->AI1_pokers.at(index))->setCanSelectdPk(false);

									addChild(static_cast<Poker *>(m_player->AI2_pokers.at(index)), 5);
									static_cast<Poker *>(m_player->AI2_pokers.at(index))->setCanSelectdPk(false);
						}

						//添加地主三张牌
						for (int i = 0; i < 3; ++i)
						{
									static_cast<Poker *>(m_player->load_Pokers.at(i))->setPosition((winSize.width - pkWidth * 2) / 2 + i*pkWidth, winSize.height - pkHeight - pkHeight / 2);
									//static_cast<Poker *>(_pokers.at(53 - i))->showCards();
									static_cast<Poker *>(m_player->load_Pokers.at(i))->setReverse();
									addChild(static_cast<Poker *>(m_player->load_Pokers.at(i)), 999);
						}
						//isCalled = rand() % 3;
						ret = true;
			} while (0);
			return ret;
}



Poker * GameScene::analyseNumForPoker(int num)
{
			int pknum = num % 13;
			int pksuit = num / 13;
			if (pksuit == 4)
			{
						if (pknum == 0)
						{
									pknum = 13;
						}
						else if (pknum == 1)
						{
									pknum = 14;
						}
			}
			Poker *poke = createCardSprite(pksuit, pknum);
			poke->setAnchorPoint(Point(0.5, 0.5));
			poke->ignoreAnchorPointForPosition(false);
			return poke;
}

Poker * GameScene::createReverseCards()
{		
			int suit = suitReverse;
			int pknum = numberReverse;
			Poker *poke = createCardSprite(suit, pknum);
			poke->setAnchorPoint(Point(0.5, 0.5));
			poke->ignoreAnchorPointForPosition(false);
			return poke;
}

char * GameScene::analyseCallNum(int calltag,int callscore,int calltime)
{
			if (calltag > 2 || calltag < 0)
			{
						return nullptr;
			}
			memset(sendBuf, 0, NET_BUF_SIZE);
			sendBuf[0] = '2';
			sendBuf[1] = static_cast<char>(calltag + '0');
			sendBuf[2] = static_cast<char>(callscore + '0');
			sendBuf[3] = static_cast<char>(calltime + '0');
			return sendBuf;
}

int GameScene::callTagForNext()
{
			int ret = callSendTag;
			if (callSendTag >-1 && callSendTag<2)
			{
						++ret;
			}
			else if(callSendTag==2)
			{
						ret = 0;
			}
			else
			{
						ret = -1;
			}
			return ret;
}

void GameScene::initLoadCard()
{
			do
			{
						for (int i = 0; i < 3; ++i)
						{
									m_player->m_pokers.pushBack(static_cast<Poker *>(m_player->load_Pokers.at (i))->copy());
									static_cast<Poker *>(m_player->load_Pokers.at (i))->setVisible(false);
									static_cast<Poker *>(m_player->m_pokers.back ())->owner = 0;
									static_cast<Poker *>(m_player->m_pokers.back())->setCanSelectdPk(true);
									static_cast<Poker *>(m_player->m_pokers.back())->setAnchorPoint(Point(0.5, 0.5));
									static_cast<Poker *>(m_player->m_pokers.back())->ignoreAnchorPointForPosition(false);
									addChild(static_cast<Poker *>(m_player->m_pokers.back()), 5);
						}

						swapCard(m_player->m_pokers);
						//log("%p", m_player->m_pokers);
						m_player->checkcard(m_player->m_pokers, 0);
			} while (0);

}

void GameScene::updateLoadCard()
{

			if(callCatchHold[0]==1)
			{
						for (int i = 0; i < 3; ++i)
						{
									m_player->AI1_pokers.pushBack(analyseNumForPoker(54));
						}
						
						//log("%p", m_player->m_pokers);
						m_player->checkcard(m_player->AI1_pokers, 1);
			}
			else if(callCatchHold[0]==2)
			{
						for (int i = 0; i < 3; ++i)
						{
									m_player->AI2_pokers.pushBack(analyseNumForPoker(54));
						}
						m_player->checkcard(m_player->AI2_pokers, 2);
			}
}





Poker *GameScene::createCardSprite(const int suit, const int number)
{
			Poker *poke = nullptr;
			if (suit != Joker)
			{
						poke = Poker::create(pokerFileName, Rect(number*pkWidth, suit*pkHeight, pkWidth, pkHeight));

			}
			else
			{
						if (number - blackJoker < 0)
						{
									poke = Poker::create(pokerFileName, Rect((numberReverse)*pkWidth, suit*pkHeight, pkWidth, pkHeight));
						}
						else
						{
									poke = Poker::create(pokerFileName, Rect((number - blackJoker)*pkWidth, suit*pkHeight, pkWidth, pkHeight));
						}
			}
			poke->setSuit(suit);
			poke->setpkNumber(number);
			poke->setGameMain(this);

			return poke;
}
