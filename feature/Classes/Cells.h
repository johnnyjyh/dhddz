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

			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
			
		

};
#endif //__Tiles_H__
