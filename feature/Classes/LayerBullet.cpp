#include "LayerBullet.h"
#include "LayerTower.h"



LayerBullet::LayerBullet()
{
}


LayerBullet::~LayerBullet()
{
}

bool LayerBullet::init()
{
			Layer::init();
			auto ret = false;
			do
			{
						char buf[255];
						for (int i = 0; i < 10; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "fort1_%d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);								
									_spriteFrameVec.pushBack(sf);
						}
						Animation *animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.18f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "CreateBullet");						
						ret = true;
			} while (0);
			
			return ret;
}

void LayerBullet::startShoot()
{
			_bullet = Bullet::create();
		
			_bullet->BindMonsterSprite(Sprite::createWithSpriteFrameName("fort1_1.png"), 1, 0, 0);
#ifdef _Test_
			//DrawSpriteFrame::drawSpriteFrame(_bullet->getSprite());
#endif //_Test_
	
			auto spr = _bullet->getSprite();
			
			_bulletVec.pushBack(_bullet);
			spr->setScaleX(0.5f);
			auto ani = Animate::create(AnimationCache::getInstance ()->getAnimation ("CreateBullet"));
			auto func = CallFuncN::create([&](Node *node) {			
						
						_bulletVec.eraseObject(_bullet);
						//node->stopAllActions();
						_bullet->removeAllChildren();
						_bullet->removeFromParent();
						_bullet = nullptr;
			});
			auto seq = Sequence::create(ani,func,NULL);			
			spr->runAction(seq);	
			addChild(_bullet,15,"BulletSpr");

}

void LayerBullet::stopShoot()
{
			
}

void LayerBullet::addBulletCallBack(float dt)
{
}

void LayerBullet::removeBullet()
{
}


