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
			virtual void bindBarrierSprite(Sprite *sp, int life, int typebar);


			int _type;
			Sprite *_barrierBlock;
			int _life;
			CC_SYNTHESIZE(int, row, Row);
			CC_SYNTHESIZE(int, column, Column);
};

#endif //__BarrierBlock_H__