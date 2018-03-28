#include "DdzButton.h"
#include "GameScene.h"
#include "Poker.h"
#include "Player.h"
#include "Net.h"

GameScene *DdzButton::GameMain ;

DdzButton::DdzButton()
{}


DdzButton::~DdzButton()
{}

DdzButton * DdzButton::create()
{
			DdzButton *pRet = new DdzButton;
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

bool DdzButton::init()
{
			bool isRet = false;
			do
			{
						Menu::init();	
						
						isRet = true;
			} while (0);
		
			return isRet;
}

bool DdzButton::createMenu(const char * FileName)
{
			/*erfen : 2分
			dizhu: 地主
			yifen : 1分
			sanfen : 3分
			bujiao : 不叫
			youlost : 你输了!!点击重新开始!!
			youwin : 你赢了!!点击重新开始!!
			buchu : 不出
			chupai : 出牌

			static Menu *callMenu;
			static Menu *playMenu;
			static Menu *loseMenu;
			static Menu *winMenu;
			*/
			bool isRet = false;
			do {
						
						callMenu = Menu::create();
						playMenu = Menu::create();
						loseMenu = Menu::create();
						winMenu = Menu::create();
						reLoad = Menu::create();
						ValueMap buttonStr = FileUtils::getInstance()->getValueMapFromFile(FileName);
						MenuItem *menuItemCallBack = nullptr;

						for (auto &str : buttonStr)
						{
									//log("%s : %s", str.first.c_str(), str.second.asString().c_str());
									if (str.first == "yifen")
									{
												menuItemCallBack = MenuItemFont::create(str.second.asString(), [&](Ref *) {
															//叫一分
															//如果叫到地主添加牌
															if (Net::playertag == 0)
															{
																		callTagForServer(1);
															}
															else
															{
																		callTagForClient(1);
															}
														
												});
												menuItemCallBack->setColor(Color3B::BLUE);
												menuItemCallBack->setTag(1);
												callMenu->addChild(menuItemCallBack,3);
												
									}
									else if (str.first == "erfen")
									{
												menuItemCallBack = MenuItemFont::create(str.second.asString(), [&](Ref *) {
															//叫二分
															//如果叫到地主添加牌
															if (Net::playertag == 0)
															{
																		callTagForServer(2);
															}
															else
															{
																		callTagForClient(2);
															}
														
												});
												menuItemCallBack->setColor(Color3B::BLUE);
												menuItemCallBack->setTag(2);
												callMenu->addChild(menuItemCallBack, 3);
									}
									else if (str.first == "sanfen")
									{
												menuItemCallBack = MenuItemFont::create(str.second.asString(), [&](Ref *) {
															//叫三分
															//如果叫到地主添加牌
															if (Net::playertag == 0)
															{
																		callTagForServer(3);
															}
															else
															{
																		callTagForClient(3);
															}
														
												});
												menuItemCallBack->setColor(Color3B::BLUE);
												menuItemCallBack->setTag(3);
												callMenu->addChild(menuItemCallBack, 3);
									}
									else if (str.first == "bujiao")
									{
												menuItemCallBack = MenuItemFont::create(str.second.asString(), [&](Ref *) {
															//不叫
															//询问是否退出游戏
															if (Net::playertag == 0)
															{
																		callTagForServer(4);
															}
															else
															{
																		callTagForClient(4);
															}
															
												});
												menuItemCallBack->setColor(Color3B::BLUE);
												callMenu->addChild(menuItemCallBack);
									}
									else if (str.first == "youlost")
									{
												menuItemCallBack = MenuItemFont::create(str.second.asString(), [&](Ref *) {
															//lose button game restart
															GameMain->rePlay();
												});
												menuItemCallBack->setColor(Color3B::BLUE);
												loseMenu->addChild(menuItemCallBack);
									}
									else if (str.first == "youwin")
									{
												menuItemCallBack = MenuItemFont::create(str.second.asString(), [&](Ref *) {
															//win button game restart
															GameMain->rePlay();
												});
												menuItemCallBack->setColor(Color3B::BLUE);
												winMenu->addChild(menuItemCallBack);
									}
									else if (str.first == "buchu")
									{
												menuItemCallBack = MenuItemFont::create(str.second.asString(), [&](Ref *) {
															//pass button
															//GameMain->rePlay();
															GameMain->m_player->clearTable(GameMain->m_player->m_pokers);
															if (!GameMain->m_player->lastPokers.size())
															{
																		return;
															}

															++(GameMain->isHold);
												});
												menuItemCallBack->setColor(Color3B::BLUE);
												playMenu->addChild(menuItemCallBack);
									}
									else if (str.first == "chupai")
									{
												menuItemCallBack = MenuItemFont::create(str.second.asString(), [&](Ref *) {
															
															//把选择的牌，放到牌桌																
															GameMain->showC();
															//++(GameMain->isHold);
															//playbutton
												});
												menuItemCallBack->setColor(Color3B::BLUE);
												playMenu->addChild(menuItemCallBack);
									}
									
						}
						{
									menuItemCallBack = MenuItemImage::create("CloseNormal.png","CloseSelected.png", [&](Ref *)
									{
												//GameMain->rePlay();
												Director::getInstance()->end();
									});
									reLoad->addChild(menuItemCallBack);
						}
						//callMenu->getChildren().swap(0,1);
						callMenu->alignItemsHorizontallyWithPadding(30);						
						playMenu->alignItemsHorizontallyWithPadding(20);

						reLoad->setPosition(winSize.width-menuItemCallBack->getBoundingBox ().size.width/2, winSize.height-menuItemCallBack->getBoundingBox().size.height / 2);
						callMenu->setPosition(winSize.width / 2, winSize.height / 2 + 40);
						playMenu->setPosition(winSize.width / 2, pkHeight*2+40);
						loseMenu->setPosition(winSize.width / 2, winSize.height / 2);
						winMenu->setPosition(winSize.width / 2, winSize.height / 2 - 40);		


						/*	playMenu->setVisible(false);
							loseMenu->setVisible(false);
							winMenu->setVisible(false);*/
					
						isRet = true;
			} while (0);


			return isRet;
}

void DdzButton::callTagForClient(int score)
{
			int times = GameMain->callSendTime;
			++times;
			int callTag = GameMain->callTagForNext();
			char *sendCallTag = GameMain->analyseCallNum(callTag, score, times);
			if (score != 4)
			{
						GameMain->callSendTag = callTag;
						GameMain->callSendScore = score;
						GameMain->calledTime = times;
			}
			else
			{
						GameMain->callSendTag = callTag;						
						GameMain->calledTime = times;
			}
			
			Net::Send(0, sendCallTag, 4);
			GameMain->callm->setVisible(false);

}

void DdzButton::callTagForServer(int score)
{
			int times = GameMain->callSendTime;
			++times;
			int callTag = GameMain->callTagForNext();
			char *sendCallTag = GameMain->analyseCallNum(callTag, score, times);		
			if (score != 4)
			{
						GameMain->callSendTag = callTag;
						GameMain->callSendScore = score;
						GameMain->calledTime = times;
						GameMain->callCatchHold[0] = 0;
						GameMain->callCatchHold[1] = score;
			}
			else
			{
						GameMain->callSendTag = callTag;
						GameMain->calledTime = times;
			}

			if (score == 3 || times == 3)
			{
						char buf[4];
						buf[0] = '0';
						buf[1] = '3';
						buf[2] = GameMain->callCatchHold[0] + '0';
						buf[3] = GameMain->callCatchHold[1] + '0';
						Net::Send(1, buf, 4);
						Net::Send(2, buf, 4);
						//GameMain->initLoadCard();
						return;
			}
			Net::Send(1, sendCallTag, 4);
			Net::Send(2, sendCallTag, 4);	
			GameMain->callm->setVisible(false);

}
