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
			auto spr = Sprite::createWithSpriteFrameName("fort1_1.png");
			//auto spr = Sprite::create("fort1_1.png");
			_bulletVec.pushBack(spr);
			//spr->setScale(0.5f);
			auto ani = Animate::create(AnimationCache::getInstance ()->getAnimation ("CreateBullet"));
			auto func = CallFuncN::create([&](Node *node) {
						auto bul = static_cast<Sprite *>(node);
						if (node)
						{
									node->stopAllActions();
									node->removeFromParent();
									_bulletVec.eraseObject(bul);
						}
			});
			auto seq = Sequence::create(ani,func,NULL);			
			spr->runAction(seq);	
			addChild(spr,15,"BulletSpr");
#ifdef _Test_
			//DrawSpriteFrame::drawSpriteFrame(spr);
#endif //_Test_
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


