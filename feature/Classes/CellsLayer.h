#ifndef __CellsLayer_H__
#define __CellsLayer_H__

#include "Common.h"
#include "Cells.h"

class CellsLayer:
			public Layer
{
public:
			CellsLayer();
			~CellsLayer();
			CREATE_FUNC(CellsLayer);
			bool init();

			//数组装入格子   空 非空 7*5   只显示5层，装载10层，其余5层，用于消除后的迁移，用两个数组装载
			//显示格子
			//判断是否可以消除   T/F   真则还有能消除的，假则没有了，打乱格子，重新排序    ，直到有可以消除的为止,3次排序则，重新分配格子
			//消除格子
			//补足格子   补足显示格子后，需要对补足数组进行补充
			//控制函数 在 begin 里面开始，move里面判断  ，end里面结算   ，可以8个方向获取格子，3连即消除，但是选择路线前进后，不能回退，不能重复选择
			//消除的内容 添加到一个链表内，处理完清除链表
			//游戏过程为，  显示格子->判断消除 ->人工触发->消除格子->补充格子 然后循环
			Cells *createCells(int randnum);
			bool initCells();
			void displayCells();
			bool isCanDestroyCells();
			void destroyCells();
			void supplyCells();
			bool isPreCells();
			void preCells();

			DrawNode *coverFabric(Vec2 pos);

			int computeTheOneCell(std::vector<Cells *> &cells, Cells * cellCurrent,int count);

			void restoreAction();

			bool isStalemate();

			void restoreStalemate();

			Cells *findCell(int col, int row);

			Cells *getNewCellForSupCell();

			void setCellsToScreen(int col, int row);

			void linkLineInGrid(int col1,int row1,int col2,int row2);
			
			void unLinkLineInGrid(int col1, int row1, int col2, int row2);

			bool checkCells();

			Vec2 coordinateToVec2(int col, int row);
			
			int *vec2ToCoordinate(Vec2 vec);

			void showLightCells(CellsColor col);  //shader light
			
			void recoverLightCells(CellsColor col);//recover light

			void moveCell(Cells *cell,int col1, int row1, int col2, int row2);//移动显示结构，并改变存储位置


			//遮盖技术
			//选择用clippingNode
			void initClippingNode();


			//以下四个继承来的虚函数用于来集成控制函数
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);



			std::list<std::list<Cells *>> _displayCell;
			std::list<Cells *> _supCell;
			//std::list<Cells *> _supDisplayCell[5];
			std::list<Cells *> _desCell;
			std::list<DrawNode *> _linkLineCache;
			std::list<Cells *> _touchCells;
			std::list<Cells *> _touchMoveCells;

			ClippingNode *_clipNode;
			bool _isCanRunning{false};
			
			int _cellScore{ 0 };

			int transformArr[2];
};


#endif //__TIlesLayer_H__