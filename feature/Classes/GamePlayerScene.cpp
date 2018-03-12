#include "GamePlayerScene.h"



int GamePlayerScene::gamePath[7] = {};

GamePlayerScene::GamePlayerScene()
{
			
}


GamePlayerScene::~GamePlayerScene()
{
}

Scene * GamePlayerScene::createScene()
{
			auto scene = Scene::create();
			auto layer = GamePlayerScene::create();
			scene->addChild(layer);
			return scene;
}

GamePlayerScene * GamePlayerScene::create()
{
			GamePlayerScene *pRet = new GamePlayerScene();
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

bool GamePlayerScene::init()
{
			Layer::init();	
			srand((unsigned int)(time(NULL)));
			//预加载动画
			loadAnimate();
			
			//添加background
			initBackGround();
			//初始化消消乐模块
			
			{
						auto cellLayer = CellsLayer::create();
						//cellLayer->setAnchorPoint(Vec2::ZERO);
						addChild(cellLayer);
			}

			/*for (int i = 0; i < 7; ++i)
			{
						for (int j = 0; j < 5; ++j)
						{
									auto spr2 = Sprite::createWithSpriteFrameName("operating_ purple.png");
									spr2->setAnchorPoint(Vec2(0, 0));
									spr2->setPosition(Vec2((getSingleTiledSize.x)*i, (getSingleTiledSize.y+(tileinterval-95 * _scalesizeX))*j));
									spr2->setScale(_scalesizeX);

									log("tiled:%lf ,%lf", spr2->getTextureRect().getMaxX(), spr2->getTextureRect().getMaxY());
									addChild(spr2, 20);

						}
			}*/

			
			
			
			
			
			
			////塔初始化-->子弹预加载	
			//createTower();
	
			////怪兽初始化
			//createMonster();
	
			////添加子弹
			//createAndBindBullet();
			//static int __i = 0;
			//schedule([&] (float dt){			
			//			++__i;
			//			_layerTower->moveTower(__i);
			//			if (__i == 4)
			//			{
			//						__i = -1;
			//			}
			//}, 2.0f,-1,2.0f,"moveTower");
			//
			////添加触摸
			//scheduleUpdate();

			auto menuitem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", [&](Ref *) {
						Director::getInstance()->end();
			});
			menuitem->setScale(1.0f);
			auto menu = Menu::create(menuitem, NULL);
			menu->setPosition(Vec2(winSize.width - menuitem->getBoundingBox().size.width / 2, winSize.height - menuitem->getBoundingBox().size.height / 2));

			addChild(menu);
			return true;
}

bool GamePlayerScene::createTower()
{
			auto ret = false;
			do
			{
						auto tower = LayerTower::create();
						tower->setTag(1100);
						addChild(tower, 20,"ToweLay");
						_layerTower = tower;
					
						ret = true;
			} while (0);
			return ret;
}





bool GamePlayerScene::createMonster()
{
			auto ret = false;
			do
			{
						auto mons = LayerMonster::create();
						addChild(mons, 10);
						_layerMonster = mons;
						ret = true;
			} while (0);
			return ret;
}

bool GamePlayerScene::createAndBindBullet()
{
			auto ret = false;
			do
			{
						
						ret = true;
			} while (0);

			return ret;
}

bool GamePlayerScene::initBackGround()
{
			auto ret = false;
			do
			{
						auto spr =  Sprite::create("operating_scenes.jpg");
						spr->setAnchorPoint(Vec2(0,0));
						auto dx = spr->getTextureRect().getMaxX();
						auto dy = spr->getTextureRect().getMaxY();
						auto wx = winSize.width;
						auto wy = winSize.height;
						_scalesizeX = wx / dx;
						_scalesizeY = wy / dy;
						spr->setScaleX((float)(wx / dx));
						spr->setScaleY((float)(wy / dy));
						//log("%lf ,%lf", spr->getTextureRect().getMaxX(), spr->getTextureRect().getMaxY());
						spr->setPosition(Vec2::ZERO);
						addChild(spr, 0,"backGround");
						ret = true;
			} while (0);
			return true;
}




bool GamePlayerScene::loadAnimate()
{
			auto ret = false;
			do
			{
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("battery_attack/tower_create.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/tower_bullet_attack.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tower/tower_bullet_burst.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_walk/pumpkin_walk.plist");
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_rest/pumpkin_reset.plist");						
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pumpkin_death/pumpkin_death.plist");			
						SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tiled/tiled.plist");
						
						ret = true;
			} while (0);
			
			return ret;
}



void GamePlayerScene::onEnter()
{
			Layer::onEnter();
			
}

void GamePlayerScene::onExit()
{
			Layer::onExit();
}

void GamePlayerScene::update(float dt)
{
			//实时检查炮台位置，调整子弹位置
			{
						auto layerbul = static_cast<LayerBullet *>(_layerTower->getChildByName("BulletLay"));
						if (_layerTower)
						{
									if (layerbul)
									{
												for (auto bul : layerbul->_bulletVec)
												{													
																		for (auto mons : _layerMonster->_monsterVec)
																		{
																					if (bul->getBoundingBox().intersectsRect(mons->getBoundingBox()) )
																					{
																								_layerMonster->monsterDeath(mons);
																								break;
																					}
																		}
												}
									}
						}
			}
			
}
