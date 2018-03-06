#include "LayerMonster.h"



LayerMonster::LayerMonster()
{
}


LayerMonster::~LayerMonster()
{
}

bool LayerMonster::init()
{
			auto ret = false;
			do
			{
						char buf[255];
						for (int i = 0; i < 14; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "pumpkin_rest_%03d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(sf);
						}
						Animation *animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.1f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "CreateMonster");
						_spriteFrameVec.clear();
						for (int i = 0; i < 11; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "pumpkin_walk_%03d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.1f, -1);
						AnimationCache::getInstance()->addAnimation(animation, "WalkMonster");
						_spriteFrameVec.clear();
						for (int i = 0; i < 9; ++i)
						{
									memset(buf, 0, sizeof(buf));
									sprintf(buf, "pumpkin_death_%03d.png", i + 1);
									SpriteFrame *sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(buf);
									_spriteFrameVec.pushBack(sf);
						}
						animation = Animation::createWithSpriteFrames(_spriteFrameVec, 0.1f, 1);
						AnimationCache::getInstance()->addAnimation(animation, "DeathMonster");
						schedule(SEL_SCHEDULE(&LayerMonster::addMonster), 2.0f);

						ret = true;

			} while (0);
			return ret;
}

void LayerMonster::addMonster(float dt)
{
			auto monster = Monster::create();
			_monsterVec.pushBack(monster);
			monster->BindMonsterSprite(Sprite::createWithSpriteFrameName("pumpkin_rest_001.png"), MonsterLife::monsterL1, MonsterSpeed::monsterS1);
#ifdef _Test_
			DrawSpriteFrame::drawSpriteFrame(monster->getSprite());
#endif  //_Test_
			monster->getSprite()->setScale(0.3f);
			monster->getSprite()->setPosition(Vec2(amendMonsterPositon(randPos), winSize.height - monster->getSprite()->getBoundingBox().size.height / 2));
			
			auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("CreateMonster"));
			auto ani2 = Animate::create(AnimationCache::getInstance()->getAnimation("WalkMonster"));
			auto moveto = MoveTo::create(5, Vec2(monster->getSprite ()->getPosition ().x,0));
			auto funcN = CallFuncN::create([&,monster](Node *node) {
						_monsterVec.eraseObject(monster);
						monster->removeFromParent();
			});
			auto seq1 = Sequence::create(moveto, funcN,NULL);
			auto moveandani = Spawn::create(ani2,seq1,NULL);			
			auto seq = Sequence::create(ani,static_cast<ActionInterval *>(moveandani),NULL);
			monster->getSprite()->runAction(seq);		
			
			addChild(monster);

}



int LayerMonster::monsterDeath(Monster *monster)
{
			if (monster)
			{					
						monster->getSprite()-> stopAllActions();
						_monsterVec.eraseObject(monster);
						auto ani = Animate::create(AnimationCache::getInstance()->getAnimation("DeathMonster"));
						auto funcNa = CallFuncN::create([&,monster](Node *node) {							
									monster->removeFromParent();
						});
						auto seq = Sequence::create(ani, funcNa, NULL);
						monster->getSprite ()->runAction(seq);				
						return Score::monsterScore1;
			}
			return 0;
}


