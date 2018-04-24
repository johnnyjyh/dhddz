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

			//block �����   ���ڽ���block ʱ��¼����״̬ 


			int _life{1};
			bool _isSelected;
			CellsColor _color;
			Sprite* _instance;
			bool _isCanSelected{ true };
			bool _isUsedLogic{ false };
			bool _isTouchBack{ false };
			CC_SYNTHESIZE(int, _row, Row);
			CC_SYNTHESIZE(int, _column, Column);
			

			//cells �����   
			Sprite *_plate[4]{ {nullptr},{nullptr},{nullptr},{nullptr} };
			bool _usablePlate[4]{ {false},{false},{false},{false }};// �涨plate 0�ϣ�1�ң�2�£�3��
			int _usablePlateHealth[4]{ {0},{0},{0},{0} };
			Vec2 _usablePlatePos[4];


			


};
#endif //__Tiles_H__
