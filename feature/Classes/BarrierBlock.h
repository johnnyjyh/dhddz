#ifndef __BarrierBlock_H__
#define __BarrierBlock_H__
#include "common.h"
#include "Cells.h"

class BarrierBlock :public Cells
{
public:
			BarrierBlock();
			~BarrierBlock();
			static BarrierBlock *create();
			void bindBarrierSprite(Sprite *sp, CellsColor color, int life);

			bool isCanSelected();
			Rect getBoundingBox();




			bool _isCanSelected{false};

			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
};

#endif //__BarrierBlock_H__