#ifndef __GameScene_H__
#define __GameScene_H__
#include "Common.h"

class Poker;
class Player;
class DdzButton;
//
struct SuitPatterns
{
			CARD_TYPE type;
			Vector<Ref *> P_pokers;
};

struct tagOutCardResult;
struct tagAnalyseResult;

class GameScene :
			public Layer
{
public:
			GameScene();
			~GameScene();
			//GameScene ������
			static GameScene *create();
			//װ��ͼ��
			static Scene *scene();
			//��Ϸ��ʼ��
			bool init();
			//��Ϸ����ǰ��Ԥ����
			void onEnter();
			//��Ϸ�˳��󣬴���
			void onExit();
			//��ʼ�����汱��
			bool initBackGround(const char *fileName);
			//�˿˳�ʼ��
			bool initCards(const char *fileName);
			//��ť��ʼ��
			bool initButton(const char *buttonStrFileName);
			//����
			bool dealCards(); 
			//ϴ��
			bool shuffleCards();
			//�˿���ʾ������
			bool putCards();
			//�˿�����
			void swapCard(Vector<Ref *>&_type);
			//��Ϸ��ѭ��    :���ƣ��е����� ���ƣ�����
			void update(float delta);
			//��ҳ����ж�
			void showC();  
			//AI �����ж�
			void showCAI(Vector<Ref *> &_AICard,tagOutCardResult &cardResult);//���Գ���

			
			//���Գ���
			void AIputCard(Vector<Ref *> &_AICard);
			//�����ж��Ƿ���Գ���
			bool aiCanPutCard(Vector<Ref *> &_AICard, Vector<Ref *> &_turnCard, tagOutCardResult &outCard);

			//��ʾ����
			void showCallPoint(int point);
			//�е�������
			void callPointToGames();
			//���ƽ׶δ���
			void playCardInTable();
			//���������������
			void insertLoadCard();
			//���¿�ʼ
			void rePlay();
			//��Ϸ���������ж���Ӯ
			void gameEnding();
			//ɾ���˿�
			bool deleteCardsBak(Vector<Ref *> &_cards);
			//��ʾ������ũ��ͼ��
			void setLoadSign();
			//��ʾ����label
			void aiNoCalled(Vector<Ref *> &_type);
			//socket ����
			//�˿�ͼƬ���
			Poker *createCardSprite(const int suit, const int number);


			//����
			Sprite *_background;
			//����װ���˿���Ϣ
			Vector<Ref *> _pokers;
			//���ڴ�����⣬�˿��Ƿ�ѡ��
			int selectCards[20];
			//����߼���
			Player *m_player;

			//��ť��
			DdzButton *m_menu;
			//��ʼ��ť
			Menu *startGame;
			//��Ϸ��ť
			Menu *playm;
			//���ư�ť
			Menu *callm;
			//Ӯ
			Menu *winm;
			//��
			Menu *losem;
			//���Ʒ�����ʾ
			Label *callPoint;
			//��Ҳ�����ʾ
			Label *noCalled;
			//AI1������ʾ
			Label *ai1noCalled;
			//AI2������ʾ
			Label *ai2noCalled;
			//����ͼ��
			Sprite *loadSign;
			//ũ��ͼ��
			Sprite *farmerSign1;
			Sprite *farmerSign2;

			Sprite *turnSign;
			//����������ָ��
			EventListenerTouchOneByOne *m_eventListener;

			Menu *menusc;

			//static bool isCalled;
			//��Ϸ��ʼ��¼
			static bool isStarted;
			//�Ƿ���Ƽ�¼
			static bool isPutCards;
			//��Ϸ�׶ο��Ʋ���,0����,1�е���,2����,3����
			static int m_state;
			int isCalled; //˭�е���,0���,1���,2���
			int calledNumber;//�еķ���
			int calledTime;//�е�������
			int isLoad;//˭�ǵ���,0���,1���,2���
			int isHold;//��˭���� ,0���,1���,2���
			
			/*------------------------------------------------------------------------------------------------------------------------*/
			//����溯��
			void testSocket();

			bool initAndShuffleCards();
			
			bool dealWithCardsNet();
			
			void startServer(Ref *menuitem);

			void startClient(Ref *menuitem);

			void checkServer(float dt);

			void checkRecv(float dt);

			void checkRecvServer(float dt);

			bool dealSendBuf(const char *str,int len);

			void getNetBuf();

			bool getNetBuf(int tag);

			bool initMark();

			bool sendCards(int tag);

			bool dealSendCards(int *cards, const int cardsLen);

			bool initPokersNet();

			bool showCardsInTableNet();
			
			Poker *analyseNumForPoker(int num);
			
			Poker *createReverseCards();

			char *analyseCallNum(int calltag, int callscore, int calltime);

			int callTagForNext();

			void initLoadCard();

			void updateLoadCard();

			

			
			
			//���������
			//���ڴ洢���͵�����
			char sendBufbak[255];
			static char sendBuf[NET_BUF_SIZE];
			static char recvBuf[NET_BUF_SIZE];

			int pokersWithNet[54];
			int loadertag;//���� 
			int player1tag; //�����¼�
			int player2tag; //�����ϼ�
			int callSendTag;
			int callSendScore;
			int callSendTime;
			int handPorkers[17];
			int player1HandPokers[17];
			int player2HandPokers[17];
			int handPokersCount;
			int player1HandPokersCount;
			int player2HandPokersCount;
			int loadCards[3];
			int tagForInitCDT;
			int callBackTag[2];

			int holdtag;
			int holdnexttag;
			int holdupontag;

			int callCatchHold[2];



			//��ұ��
			CC_SYNTHESIZE(int, _userMark, UserMark);
};


#endif
