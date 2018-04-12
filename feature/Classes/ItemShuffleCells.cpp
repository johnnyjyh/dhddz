#include "ItemShuffleCells.h"




ItemShuffleCells::ItemShuffleCells()
{
}


ItemShuffleCells::~ItemShuffleCells()
{
}

ItemShuffleCells * ItemShuffleCells::create()
{
			auto ret = new (std::nothrow) ItemShuffleCells;
			if (ret)
			{
						ret->autorelease();
			}
			else
			{
						delete ret;
						ret = nullptr;
			}
			return ret;
}

bool ItemShuffleCells::init()
{
			auto ret = false;
			do 
			{
						setRecordTime(10);
						auto spr = Sprite::createWithSpriteFrameName("operating_skillbox.png");					
						auto menu = Menu::create();
						auto menuit = MenuItemImage::create("","",[&](Ref *target) {
									if (!(_layCells->_isCanRunning) || getRecordTime() <= 0)
									{
												return;
									}
									_layCells->shffuleCellsforMenu();
									setRecordTime(getRecordTime() - 1);
									updateRecordTimes();
									; });
						menuit->setNormalImage(Sprite::createWithSpriteFrameName("operating_skill1.png"));
						menuit->setSelectedImage(Sprite::createWithSpriteFrameName("operating_skill1.png"));
						auto label = Label::createWithSystemFont(StringUtils::toString(getRecordTime()), "Arial", 30);

						_recordTimeLabel = label;
						menu->addChild(menuit);
						spr->addChild(label);		
						
						spr->addChild(menu);
						auto menuitPos =spr->getBoundingBox().size;					
						label->setPosition(Vec2(menuitPos.width*0.75, menuitPos.height / 2));
						menu->setPosition(Vec2(menuitPos.width*0.25, menuitPos.height / 2));
						addChild(spr);
						spr->setAnchorPoint(Vec2::ZERO);
						
						spr->setScale(0.5f);
						
						
						ret = true;
			} while (0);
			return ret;
}

void ItemShuffleCells::bindLayerCell(CellsLayer * _lay)
{
			_layCells = _lay;
			this->init();
}

void ItemShuffleCells::updateRecordTimes()
{
			_recordTimeLabel->setString(StringUtils::toString(getRecordTime()));
}
