#include "PlayerData.h"

PlayerData *PlayerData::s_sharedPlayerDate = nullptr;


PlayerData::PlayerData()
{
		
}


PlayerData::~PlayerData()
{
}

bool PlayerData::init()
{
			auto ret = false;
			do 
			{
						_playerLife = 3;
						this->setPlayerScore(10);
						initPlayerLife();
						//初始化血量控件
						ret = true;
			} while (0);
			return ret;
}

bool PlayerData::initPlayerLife()
{
			auto ret = false;
			do
			{
						//添加图标
						{
									auto lifeCarrier = Sprite::createWithSpriteFrameName("operating_starsbox.png");
									lifeCarrier->setPosition(Vec2(lifeCarrier->getContentSize().width/2, winSize.height - lifeCarrier->getContentSize().height/2));
									for (int i = 0; i < 3; ++i)
									{
												auto lifeStar = Sprite::createWithSpriteFrameName("operating_star.png");
												lifeCarrier->addChild(lifeStar,20);
												lifeStar->setPosition(Vec2((lifeStar->getContentSize().width+2 )*(i + 1.3), lifeStar->getContentSize().height/2));
												_starsVec.push_back(lifeStar);
									}									
									auto lifeSchUp = Sprite::createWithSpriteFrameName("operating_schedule2.png");
									
									auto lifeSchDown = Sprite::createWithSpriteFrameName("operating_schedule1.png");
									lifeCarrier->addChild(lifeSchDown, 10);
									
									auto posSch = lifeCarrier->getContentSize();
									lifeSchDown->setPosition(Vec2(lifeSchDown->getContentSize().width/2+2, posSch.height / 2.5));
									{
												
												auto lifeProgress = ProgressTimer::create(lifeSchUp);
												lifeCarrier->addChild(lifeProgress,11);
												//lifeProgress->setAnchorPoint(Point::ZERO);
												lifeProgress->setType(ProgressTimer::Type::BAR);
												auto posPro = lifeSchDown->getPosition();
												lifeProgress->setPosition(posPro);
												lifeProgress->setMidpoint(Vec2(0, 0));
												lifeProgress->setBarChangeRate(Vec2(1, 0));
												lifeProgress->setPercentage(100);
												_powerProgress = lifeProgress;
									}
									//lifeCarrier->setScale(0.5f);
									_mainCarrier = lifeCarrier;
									PlayerData::getInstancePlayerData()->addChild(lifeCarrier);
						}
						//绑定图标

						ret = true;
			} while (0);
			return ret;
}

void PlayerData::loseLife()
{
			--_playerLife;
}

void PlayerData::addLife()
{
			++_playerLife;
}

int PlayerData::getLife()
{
			return _playerLife;
}

void PlayerData::updatePlayerLife()
{
			switch (getLife())
			{
			case 0:
						break;
			case 1:
						break;
			case 2:
						break;
			case 3:
						break;
			default:
						break;
			}
}

PlayerData * PlayerData::getInstancePlayerData()
{	
			if (!(PlayerData::s_sharedPlayerDate))
			{
						PlayerData::s_sharedPlayerDate = new (std::nothrow) PlayerData;
						CCASSERT(PlayerData::s_sharedPlayerDate, "FATAL: Not enough memory");
						(PlayerData::s_sharedPlayerDate)->init();
			}
			return PlayerData::s_sharedPlayerDate;
}
