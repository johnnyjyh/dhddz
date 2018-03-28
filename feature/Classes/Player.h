#ifndef __Player_H__
#define __Player_H__
#include "Common.h"

struct tagAnalyseResult
{
			int resultCount[4];
			int cardData[4][20]; //0����  1����  2���� 3ը��
};

struct tagOutCardResult
{
			int							cbCardCount;						//�˿���Ŀ
			int							cbResultCard[20];			//����˿�
};


class GameScene;
class Player
{
public:
			Player();
			~Player();		
			//�������
			void  checkcard(Vector<Ref *> &_type, int type);
			//��������
			void clearTable(Vector<Ref *> &_type);
			//��������ʾ������
			void putCardInMiddle(Vector<Ref *> &_type);
			//��������
			bool updatePkPosition();
			//��ȡ�߼�ֵ
			int getCardLogicValue(Ref *_card);
			//��ȡ����
			int getPokerType(Vector<Ref *> &_type);
			//�����˿�
			void analyseCards(Vector<Ref *> &_type,tagAnalyseResult &AnalysePoker);
			//�Ƚϴ�С
			bool compareCard(Vector<Ref *> &_first, Vector<Ref *> &_next);
			//��������
			//void cardPower(Vector<Ref *>& _card);


			
			
			//װ����Ϸ����
			Vector<Ref *> m_pokers;
			Vector<Ref *>AI1_pokers;
			Vector<Ref *>AI2_pokers;
			//���γ���
			Vector<Ref *>m_showCardType;
			//AI���γ���
			Vector<Ref *>m_showCardTypeAI;
			//AI1���γ���
			Vector<Ref *>AI1_showCardType;
			//AI2���γ���
			Vector<Ref *>AI2_showCardType;
			//���һ��δ��ѹ��������
			Vector<Ref *>lastPokers;
			//�����һ�γ���
			Vector<Ref *>m_lastPokers;
			//AI1���һ�γ���
			Vector<Ref *>AI1_lastPokers;
			//AI2���һ�γ���
			Vector<Ref *>AI2_lastPokers;


			Point playerPt;
			Point AIPt1;
			Point AIPt2;

			//�����
			Vector<Ref *> load_Pokers;
		
};

#endif