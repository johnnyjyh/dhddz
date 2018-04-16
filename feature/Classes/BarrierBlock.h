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
			void bindBarrierSprite(Sprite *sp, CellsColor _color, int life);

			bool isCanSelected();
			Rect getBoundingBox();




			bool _isCanSelected{false};
};

#endif //__BarrierBlock_H__