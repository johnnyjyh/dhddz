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
			//GameScene 类申请
			static GameScene *create();
			//装入图层
			static Scene *scene();
			//游戏初始化
			bool init();
			//游戏进入前，预处理
			void onEnter();
			//游戏退出后，处理
			void onExit();
			//初始化桌面北京
			bool initBackGround(const char *fileName);
			//扑克初始化
			bool initCards(const char *fileName);
			//按钮初始化
			bool initButton(const char *buttonStrFileName);
			//发牌
			bool dealCards(); 
			//洗牌
			bool shuffleCards();
			//扑克显示到桌面
			bool putCards();
			//扑克排序
			void swapCard(Vector<Ref *>&_type);
			//游戏主循环    :发牌，叫地主， 出牌，结束
			void update(float delta);
			//玩家出牌判断
			void showC();  
			//AI 出牌判断
			void showCAI(Vector<Ref *> &_AICard,tagOutCardResult &cardResult);//电脑出牌

			
			//电脑出牌
			void AIputCard(Vector<Ref *> &_AICard);
			//电脑判断是否可以出牌
			bool aiCanPutCard(Vector<Ref *> &_AICard, Vector<Ref *> &_turnCard, tagOutCardResult &outCard);

			//显示分数
			void showCallPoint(int point);
			//叫地主处理
			void callPointToGames();
			//出牌阶段处理
			void playCardInTable();
			//地主牌添加入手牌
			void insertLoadCard();
			//重新开始
			void rePlay();
			//游戏结束处理，判断输赢
			void gameEnding();
			//删除扑克
			bool deleteCardsBak(Vector<Ref *> &_cards);
			//显示地主，农民图标
			void setLoadSign();
			//显示不出label
			void aiNoCalled(Vector<Ref *> &_type);
			//socket 测试
			//扑克图片添加
			Poker *createCardSprite(const int suit, const int number);


			//背景
			Sprite *_background;
			//用于装载扑克信息
			Vector<Ref *> _pokers;
			//用于触摸检测，扑克是否选择
			int selectCards[20];
			//玩家逻辑类
			Player *m_player;

			//按钮类
			DdzButton *m_menu;
			//开始按钮
			Menu *startGame;
			//游戏按钮
			Menu *playm;
			//叫牌按钮
			Menu *callm;
			//赢
			Menu *winm;
			//输
			Menu *losem;
			//叫牌分数显示
			Label *callPoint;
			//玩家不出显示
			Label *noCalled;
			//AI1不出显示
			Label *ai1noCalled;
			//AI2不出显示
			Label *ai2noCalled;
			//地主图标
			Sprite *loadSign;
			//农民图标
			Sprite *farmerSign1;
			Sprite *farmerSign2;

			Sprite *turnSign;
			//触摸控制类指针
			EventListenerTouchOneByOne *m_eventListener;

			Menu *menusc;

			//static bool isCalled;
			//游戏开始记录
			static bool isStarted;
			//是否出牌记录
			static bool isPutCards;
			//游戏阶段控制参数,0发牌,1叫地主,2出牌,3结束
			static int m_state;
			int isCalled; //谁叫地主,0玩家,1玩家,2玩家
			int calledNumber;//叫的分数
			int calledTime;//叫地主次数
			int isLoad;//谁是地主,0玩家,1玩家,2玩家
			int isHold;//该谁出牌 ,0玩家,1玩家,2玩家
			
			/*------------------------------------------------------------------------------------------------------------------------*/
			//网络版函数
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

			

			
			
			//网络版数据
			//用于存储发送的数据
			char sendBufbak[255];
			static char sendBuf[NET_BUF_SIZE];
			static char recvBuf[NET_BUF_SIZE];

			int pokersWithNet[54];
			int loadertag;//地主 
			int player1tag; //地主下家
			int player2tag; //地主上家
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



			//玩家标记
			CC_SYNTHESIZE(int, _userMark, UserMark);
};


#endif
