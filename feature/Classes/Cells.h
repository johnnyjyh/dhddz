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
			//DEPRECATED_ATTRIBUTE
			virtual void bindCellsSprite(Sprite *sp, CellsColor col, bool isSel);
			virtual void bindNewCellsSprite(CellsColor color, int col, int row);
			virtual void addPlate();

			virtual Sprite *getSprite();
			virtual Rect getBoundingBox();
			virtual CellsColor getColor();
			virtual bool isSelected();
			virtual bool isCanSelected();

			virtual void loseLife();
			virtual int getLife();
			virtual void setLife(int life);

			virtual void pushCellsSprite(Cells *cell);
			virtual void pullCellsSprite();

			virtual void updateCell();

			virtual Sprite *catchColorForNewSprite();

			virtual void pushMoveVec(std::vector<Vec2> & moveVec);
			//block 标记量   用于交换block 时记录格子状态 


			//
			double transformArr[2];
			inline double *vec2ToCoordinate(Vec2 vec)
			{
						transformArr[0] = vec.x / getSingleTiledSize.x - 0.5;
						transformArr[1] = vec.y / (getSingleTiledSize.y + (tileinterval - 95 * 0.5)) - 0.5;
						return transformArr;
			}

			inline Vec2 coordinateToVec2(int col, int row)
			{
						Vec2 vec(getSingleTiledSize.x*(col + 0.5), (getSingleTiledSize.y + (tileinterval - 95 * 0.5))*(row + 0.5));
						return vec;
			}
			//


	
			int _life{1};
			bool _isSelected;
			CellsColor _color;
			Sprite* _instance{nullptr};
			bool _isCanSelected{ true };
			bool _isUsedLogic{ false };
			bool _isTouchBack{ false };
			bool _isMoving{ false };
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
			

			//cells 标记量   
			Sprite *_plate[4]{ {nullptr},{nullptr},{nullptr},{nullptr} };
			bool _usablePlate[4]{ {false},{false},{false},{false }};// 规定plate 0上，1右，2下，3左
			int _usablePlateHealth[4]{ {0},{0},{0},{0} };
			Vec2 _usablePlatePos[4];
			std::vector<Vec2> _moveVec;
			Vector<FiniteTimeAction *> _moveActionVec;

};
#endif //__Tiles_H__
