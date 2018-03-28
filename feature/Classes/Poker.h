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
			//�˿�������
			static Poker *create(const char *fileName,const Rect rect);
			//�˿����ʼ��
			bool initWithFile(const char * fileName, const Rect rect);
			//��ʾ�˿˷���
			void setReverse();
			//��ʾ����
			void showCards();
			//�˿��ƶ�
			void pkSetPosition(Point pt);
			//��ȿ����˿�
			Poker *copy();
			//�ݻ��˿�
			bool destroyCard();
			//ѡ���˿�����
			void selectPokerUp();
			//ѡ���˿� ��������
			void selectPokerDown();
			//ԭ �����˿˴����������� ���볡��
			virtual void onEnter();
			//ԭ �����˿˴��������Ƴ� ���볡��
			virtual void onExit();
			//�˿�������: 0  ��� 1 AI1  2 AI2
			int owner;

			EventListenerTouchOneByOne *m_eventListener;

			//�˿˻�ɫ
			CC_SYNTHESIZE(int, m_suit, Suit);
			//�˿˷�ֵ
			CC_SYNTHESIZE(int, m_number, pkNumber);
			//������
			CC_SYNTHESIZE(GameScene *, m_gameMain, GameMain);
			//�Ƿ�ѡ��������˿�
			CC_SYNTHESIZE(bool, m_selected, SelectedPk);
			//�˿��Ƿ��ܱ�ѡ��
			CC_SYNTHESIZE(bool, m_canSelected, CanSelectdPk);
			//�˿��Ƿ��Ѿ�������
			CC_SYNTHESIZE(bool, m_isUsed, Used);

			
};

#endif

