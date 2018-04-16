#ifndef __Cells_H__
#define __Cells_H__
#include "Common.h"
class Cells
			: public Node
{
public:
			Cells();
			~Cells();
			static Cells *create();
			virtual void bindCellsSprite(Sprite *sp, CellsColor col, bool isSel);
			virtual Sprite *getSprite();
			virtual Rect getBoundingBox();
			virtual CellsColor getColor();
			virtual bool isSelected();
			virtual bool isCanSelected();

			virtual void loseLife();
			virtual int getLife();


			int _life{1};
			bool _isSelected;
			CellsColor _color;
			Sprite* _instance;
			bool _isCanSelected{true};
			bool isUsedLogic{ false };
			bool _isTouchBack{ false };

			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);


};
#endif //__Tiles_H__
