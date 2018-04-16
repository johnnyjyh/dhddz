#ifndef __BarrierBlock_H__
#define __BarrierBlock_H__
#include "common.h"
#include "Barrier.h"

class BarrierBlock :public Barrier
{
public:
			BarrierBlock();
			~BarrierBlock();
			static BarrierBlock *create();
			virtual void bindBarrierSprite(Sprite *sp, CellsColor _color, int life);
			Sprite *getSprite();
			void loseLife();
			int getLife();
			int getColor();
			bool isCanSelected();



			Sprite *_barrierBlock;
			int _life;
			CellsColor _color;
			bool _isCanSelected{false};
			CC_SYNTHESIZE(int, row, Row);
			CC_SYNTHESIZE(int, column, Column);
};

#endif //__BarrierBlock_H__