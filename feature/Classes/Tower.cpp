#include "Tower.h"



Tower::Tower()
{
			
}


Tower::~Tower()
{

}

Tower * Tower::create()
{
			auto pRet = new Tower();
			pRet->autorelease();
			return pRet;
}

void Tower::bindTowerSprite(Sprite *sp, int life, int damage, int speed)
{
			setIsDestroy(false);
			_instance = sp;
			_life = life;
			_damage = damage;;
			_speed = speed;
			setIsAttacked(false);
			addChild(_instance);
			initLifeSprite();
			bindLifeSprite();
			

#ifdef _Test_		
			
#endif //_Test_

			
}

void Tower::bindLifeSprite()
{
			int index = 1;

			for (auto lifeSpr : _lifeVec)
			{
						//lifeSpr->setScale();
						auto pos = convertToWorldSpace(_instance->getParent()->getPosition()) ;
					
						lifeSpr->setPosition(Vec2(pos.x + (lifeSpr->getContentSize().width + 8)*index, pos.y - lifeSpr->getContentSize().height / 2));
					
						++index;
			}
			index = 1;
			for (auto lifeSpr : _lifeEmptyVec)
			{
						//lifeSpr->setScale();
						auto pos = convertToWorldSpace(_instance->getParent()->getPosition());

						lifeSpr->setPosition(Vec2(pos.x + (lifeSpr->getContentSize().width + 8)*index, pos.y - lifeSpr->getContentSize().height / 2));

						++index;
			}

			
}

bool Tower::initLifeSprite()
{
			auto ret = false;
			do 
			{
						for (int i = 0; i < 3; ++i)
						{
									auto spr = Sprite::createWithSpriteFrameName("operating_love.png");	
									auto emptyspr = Sprite::createWithSpriteFrameName("operating_love2.png");
									_lifeEmptyVec.push_back(emptyspr);
									_lifeVec.push_back(spr);
									_instance->addChild(spr,2);
									_instance->addChild(emptyspr, 1);
						}		
						/*auto node = Sprite::createWithSpriteFrameName("operating_love.png");
						auto progress = ProgressTimer::create(node);
						for (int i = 0; i < 3; ++i)
						{
									auto spr = Sprite::createWithSpriteFrameName("operating_love2.png");
									_lifeVec.push_back(spr);
									_instance->addChild(spr);
									auto lifespr = Sprite::createWithSpriteFrameName("operating_love.png");

									lifespr->setPosition(Vec2( (lifespr->getContentSize().width + 8)*(i), 0));
						}


						_instance->addChild(progress);
						progress->setType(ProgressTimer::Type::BAR);
						progress->setMidpoint(Vec2(0, 0));
						progress->setBarChangeRate(Vec2(1, 0));
						progress->setPercentage(100.0f);

						progress->setPosition(Vec2(winSize.width/4,winSize.height/2));

						_lifeProgress = progress;

*/
						auto ret = true;
			} while (0);
			return ret;
}

void Tower::updateLife()
{
			switch (getLife())
			{
			case -1:
						_instance->setVisible(false);
						setIsDestroy(true);
						break;
			case 0:
						_lifeVec[0]->setVisible(false);
						_lifeVec[1]->setVisible(false);
						_lifeVec[2]->setVisible(false);
						//_lifeVec[0] = Sprite::createWithSpriteFrameName("operating_love2.png");
						//_instance->addChild(_lifeVec[0]);
						//bindLifeSprite();
						break;
			case 1:
						_lifeVec[0]->setVisible(true);
						_lifeVec[1]->setVisible(false);
						_lifeVec[2]->setVisible(false);
						//_lifeVec[1] = Sprite::createWithSpriteFrameName("operating_love2.png");
					//	_instance->addChild(_lifeVec[1]);
					//	bindLifeSprite();
						break;
			case 2:
						_lifeVec[0]->setVisible(true);
						_lifeVec[1]->setVisible(true);
						_lifeVec[2]->setVisible(false);
						//_lifeVec[2] = Sprite::createWithSpriteFrameName("operating_love2.png");
						//_instance->addChild(_lifeVec[2]);
						//bindLifeSprite();
						break;
			case 3:
						_lifeVec[0]->setVisible(true);
						_lifeVec[1]->setVisible(true);
						_lifeVec[2]->setVisible(true);						
						break;
			default:
						break;
			}

			/*switch (getLife())
			{
			case -1:
						_instance->setVisible(false);
						break;
			case 0:
						_lifeProgress->setPercentage(0.0f);
						break;
			case 1:

						_lifeProgress->setPercentage(33.0f);

						break;
			case 2:
						_lifeProgress->setPercentage(66.0f);
						break;
			case 3:
						initLifeSprite();
						bindLifeSprite();
						break;
			default:
						break;
			}*/
}

Sprite * Tower::getSprite()
{
			return _instance;
}

int Tower::getLife()
{
			return _life;
}

void Tower::loseLife()
{
			--_life;
			//血量减少状态更新
			updateLife();
}

void Tower::addLife()
{
			++_life;
			updateLife();
}


int Tower::getPos()
{
			return _pos;
}

Rect Tower::getBoundingBox()
{
			auto rectBak = _instance->getBoundingBox();
			Vec2 pos = convertToWorldSpace(rectBak.origin);
			Rect rect = Rect(pos.x+ rectBak.size.width/4, pos.y+ rectBak.size.height / 4, rectBak.size.width/2,rectBak.size.height/2);
			return rect;

}





