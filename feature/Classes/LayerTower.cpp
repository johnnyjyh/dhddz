#include "LayerTower.h"
#include "LayerBullet.h"



LayerTower::LayerTower()
{
}


LayerTower::~LayerTower()
{
}



bool LayerTower::init()
{
			auto ret = false;
			do
			{
						char buf[255];
						for (int i = 0; i < 10; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "battery_attack_%03d.png", i + 1);
									SpriteFrame *frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(frame);
						}
						Animation *animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.1f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "CreateTower");
						scheduleOnce(SEL_SCHEDULE(&LayerTower::addTower),0.0f);
						ret = true;
			} while (0);
			return ret;
}

void LayerTower::addTower(float dt)
{
			auto tower = Tower::create();
			_tower = tower;
			tower->bindTowerSprite(Sprite::createWithSpriteFrameName("battery_attack_001.png"), TowerItem::TowerOrignal::life, TowerItem::TowerOrignal::damage, TowerItem::TowerOrignal::speed);
#ifdef _Test_
			DrawSpriteFrame::drawSpriteFrame(tower->getSprite());
#endif //_Test_		
			tower->getSprite()-> setScale(0.5f);
			log("%lf,%lf", tower->getSprite()->getBoundingBox().origin.x, tower->getSprite()->getBoundingBox().origin.y);
			auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("CreateTower"));
			Vec2 pos = Vec2(amendMonsterPositon(0),tower->getSprite ()->getBoundingBox ().size.height);		
			
			tower->getSprite()->setPosition(pos);	
			tower->getSprite()->runAction(RepeatForever::create(ani));
	
			addChild(tower,21,"TowerSpr");

			auto bullet = LayerBullet::create();
			addChild(bullet, 15, "BulletLay");
			
			schedule([&,bullet,tower](float dt) {
						if (bullet)
						{
									bullet->startShoot();		
									auto spr = bullet->getChildByName("BulletSpr");									
									spr->setPosition(Vec2(tower->getSprite()->getPosition().x, tower->getSprite()->getPosition().y+tower->getSprite()-> getBoundingBox().size.height));
									//spr->setPosition(Vec2(winSize.width/2, winSize.height/2));
									
#ifdef _Test_
									DrawSpriteFrame::drawSpriteFrame(static_cast<Sprite *>(spr));
#endif //_Test_			
									spr->setScale(0.5f);
						}
			},2.0f,"shootSch");

			
}

void LayerTower::moveTower(int index)
{
			auto spr = static_cast<Tower *>(getChildByName("TowerSpr"))->getSprite();
			auto moveby = MoveTo::create(0.5f,Vec2(amendMonsterPositon(index), spr->getBoundingBox().size.height));
			spr->runAction(moveby);
#ifdef _Test_
			
#endif //_Test_
}


