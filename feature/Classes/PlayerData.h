#ifndef __PlayerData_H__
#define __PlayerData_H__
#include "Common.h"
#include "CellsLayer.h"
#include "ItemShuffleCells.h"

class PlayerData : public Node
{
public:
			PlayerData();
			~PlayerData();
			//CREATE_FUNC(PlayerData);
			virtual bool init();
			//初始化血量控件
			bool initPlayerLife();
			bool initScoreBoard();

			void loseLife();
			void addLife();
			int getLife();
			void addScore(int score);

			void updatePlayerLife();

			static PlayerData * getInstancePlayerData();

			
			///////////////////////////////////////////////
			//道具类
			void addShuffleCellMenu(CellsLayer * celllay);
			


			static PlayerData * s_sharedPlayerDate;
			int _playerLife;

			ItemShuffleCells *_itembase{ nullptr };

			std::vector<Sprite *> _starsVec;

			CC_SYNTHESIZE(int, _playerScore, PlayerScore);

			ProgressTimer *_powerProgress;
			Sprite * _mainCarrier;
			Label *_scoreLabal;
};

#endif // __PlayerData_H__

