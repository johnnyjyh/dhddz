#ifndef __Poker_H__
#define __Poker_H__
#include "Common.h"

class GameScene;

class Poker :
			public Sprite
{
public:
			Poker();
			~Poker();
			//扑克类申请
			static Poker *create(const char *fileName,const Rect rect);
			//扑克类初始化
			bool initWithFile(const char * fileName, const Rect rect);
			//显示扑克反面
			void setReverse();
			//显示正面
			void showCards();
			//扑克移动
			void pkSetPosition(Point pt);
			//深度拷贝扑克
			Poker *copy();
			//摧毁扑克
			bool destroyCard();
			//选派扑克上移
			void selectPokerUp();
			//选派扑克 返回手牌
			void selectPokerDown();
			//原 处理扑克触摸函数添入 进入场景
			virtual void onEnter();
			//原 处理扑克触摸函数移除 进入场景
			virtual void onExit();
			//扑克所有者: 0  玩家 1 AI1  2 AI2
			int owner;

			EventListenerTouchOneByOne *m_eventListener;

			//扑克花色
			CC_SYNTHESIZE(int, m_suit, Suit);
			//扑克分值
			CC_SYNTHESIZE(int, m_number, pkNumber);
			//主场景
			CC_SYNTHESIZE(GameScene *, m_gameMain, GameMain);
			//是否选择了这个扑克
			CC_SYNTHESIZE(bool, m_selected, SelectedPk);
			//扑克是否能被选择
			CC_SYNTHESIZE(bool, m_canSelected, CanSelectdPk);
			//扑克是否已经出过了
			CC_SYNTHESIZE(bool, m_isUsed, Used);

			
};

#endif

