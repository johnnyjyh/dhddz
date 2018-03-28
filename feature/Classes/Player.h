#ifndef __Player_H__
#define __Player_H__
#include "Common.h"

struct tagAnalyseResult
{
			int resultCount[4];
			int cardData[4][20]; //0单牌  1对牌  2三带 3炸弹
};

struct tagOutCardResult
{
			int							cbCardCount;						//扑克数目
			int							cbResultCard[20];			//结果扑克
};


class GameScene;
class Player
{
public:
			Player();
			~Player();		
			//检查手牌
			void  checkcard(Vector<Ref *> &_type, int type);
			//清理桌面
			void clearTable(Vector<Ref *> &_type);
			//出的牌显示到桌面
			void putCardInMiddle(Vector<Ref *> &_type);
			//更新手牌
			bool updatePkPosition();
			//获取逻辑值
			int getCardLogicValue(Ref *_card);
			//获取类型
			int getPokerType(Vector<Ref *> &_type);
			//分析扑克
			void analyseCards(Vector<Ref *> &_type,tagAnalyseResult &AnalysePoker);
			//比较大小
			bool compareCard(Vector<Ref *> &_first, Vector<Ref *> &_next);
			//分析牌力
			//void cardPower(Vector<Ref *>& _card);


			
			
			//装载游戏手牌
			Vector<Ref *> m_pokers;
			Vector<Ref *>AI1_pokers;
			Vector<Ref *>AI2_pokers;
			//本次出牌
			Vector<Ref *>m_showCardType;
			//AI本次出牌
			Vector<Ref *>m_showCardTypeAI;
			//AI1本次出牌
			Vector<Ref *>AI1_showCardType;
			//AI2本次出牌
			Vector<Ref *>AI2_showCardType;
			//最后一次未被压的桌面牌
			Vector<Ref *>lastPokers;
			//我最后一次出牌
			Vector<Ref *>m_lastPokers;
			//AI1最后一次出牌
			Vector<Ref *>AI1_lastPokers;
			//AI2最后一次出牌
			Vector<Ref *>AI2_lastPokers;


			Point playerPt;
			Point AIPt1;
			Point AIPt2;

			//网络版
			Vector<Ref *> load_Pokers;
		
};

#endif