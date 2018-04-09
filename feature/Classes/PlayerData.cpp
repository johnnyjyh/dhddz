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
						this->setPlayerScore(0);
						initPlayerLife();
						initScoreBoard();
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
									
									for (int i = 0; i < 3; ++i)
									{
												auto lifeStar = Sprite::createWithSpriteFrameName("operating_star.png");
												lifeCarrier->addChild(lifeStar,20);
												_starsVec.push_back(lifeStar);
												
												
									}									
									auto lifeSchUp = Sprite::createWithSpriteFrameName("operating_schedule2.png");									
									auto lifeSchDown = Sprite::createWithSpriteFrameName("operating_schedule1.png");
									lifeCarrier->addChild(lifeSchDown, 10);									
									auto posSch = lifeCarrier->getContentSize();
									
									auto lifeProgress = ProgressTimer::create(lifeSchUp);
									lifeCarrier->addChild(lifeProgress, 11);
									lifeProgress->setType(ProgressTimer::Type::BAR);
									lifeProgress->setMidpoint(Vec2(0, 0));
									lifeProgress->setBarChangeRate(Vec2(1, 0));
									lifeProgress->setPercentage(100);
									//重要缩放，影响布局!
									lifeCarrier->setScale(0.5f);
									
									PlayerData::getInstancePlayerData()->addChild(lifeCarrier);
									lifeCarrier->setPosition(Vec2(lifeCarrier->getBoundingBox().size.width/ 2+5, winSize.height - lifeCarrier->getBoundingBox().size.height / 2));
									int i = 0;
									for (auto star : _starsVec)
									{
												star->setPosition(Vec2((star->getBoundingBox().size.width + 2)*(i + 1.3), star->getBoundingBox().size.height / 2));
												++i;
									}														
									lifeSchDown->setPosition(Vec2(lifeSchDown->getBoundingBox().size.width / 2 + 2, posSch.height / 2.5));
									auto posPro = lifeSchDown->getPosition();
									lifeProgress->setPosition(posPro);
									_powerProgress = lifeProgress;
									_mainCarrier = lifeCarrier;
						}
						//绑定图标

						ret = true;
			} while (0);
			return ret;
}

bool PlayerData::initScoreBoard()
{
			auto ret = false;
			do 
			{
						//TTFConfig ttf("fonts/arial.ttf");
						//ttf.fontSize = 25;						
						//_scoreLabal = Label::createWithTTF(ttf,std::to_string(getPlayerScore()));
						_scoreLabal = Label::createWithSystemFont(std::to_string(getPlayerScore()),"Arial",30);
						_mainCarrier->addChild(_scoreLabal,25);
						auto pos = convertToWorldSpace(_mainCarrier->getBoundingBox().size);
						_scoreLabal->setPosition(Vec2(_mainCarrier->getBoundingBox().size.width ,_mainCarrier->getBoundingBox().size.height+10));
						log("score :%f,%f", pos.x, pos.y);
						_scoreLabal->setColor(Color3B::YELLOW);
						
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

void PlayerData::addScore(int score)
{
			int scoreBak = getPlayerScore() + score;
			setPlayerScore(scoreBak);
			updatePlayerLife();
}

void PlayerData::updatePlayerLife()
{
			_scoreLabal->setString(std::to_string(getPlayerScore()));
			/*switch (getLife())
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
			}*/
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
