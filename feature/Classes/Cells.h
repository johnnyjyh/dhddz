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
			void bindCellsSprite(Sprite *sp, CellsColor col, bool isSel);
			Sprite *getSprite();
			Rect getBoundingBox();
			CellsColor getColor();
			bool isSelected();

			void loseLife();
			int getLife();


			int _life{1};
			bool _isSelected;
			CellsColor _col;
			Sprite* _instance;
			bool isUsedLogic{ false };
			bool _isTouchBack{ false };

			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);


};
#endif //__Tiles_H__
