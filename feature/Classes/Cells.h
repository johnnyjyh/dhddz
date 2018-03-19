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
			void bindCellsSprite(Sprite *sp, CellsColor col,bool isSel);
			Sprite *getSprite();
			Rect getBoundingBox();
			CellsColor getColor();
			bool isSelected();


			bool _isSelected;
			CellsColor _col;
			Sprite* _instance;

<<<<<<< HEAD
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);

=======
>>>>>>> 1930810ec5c27a97ee53f9f502973a917eeed6c8

};
#endif //__Tiles_H__
