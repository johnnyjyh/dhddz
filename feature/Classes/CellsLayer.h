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

			//����װ�����   �� �ǿ� 7*5   ֻ��ʾ5�㣬װ��10�㣬����5�㣬�����������Ǩ�ƣ�����������װ��
			//��ʾ����
			//�ж��Ƿ��������   T/F   �������������ģ�����û���ˣ����Ҹ��ӣ���������    ��ֱ���п���������Ϊֹ,3�����������·������
			//��������
			//�������   ������ʾ���Ӻ���Ҫ�Բ���������в���
			//���ƺ��� �� begin ���濪ʼ��move�����ж�  ��end�������   ������8�������ȡ���ӣ�3��������������ѡ��·��ǰ���󣬲��ܻ��ˣ������ظ�ѡ��
			//���������� ��ӵ�һ�������ڣ��������������
			//��Ϸ����Ϊ��  ��ʾ����->�ж����� ->�˹�����->��������->������� Ȼ��ѭ��
			Cells *createCells(int randnum);
			bool initCells();
			void displayCells();
			bool isCanDestroyCells();
			void destroyCells();
			void supplyCells();
			bool isPreCells();
			void preCells();

			int computeTheOneCell(std::vector<Cells *> &cells, Cells * cellCurrent,int count);

			void restoreAction();

			bool isStalemate();

			void restoreStalemate();

			Cells *findCell(int col, int row);

			Cells *getNewCellForSupCell();

			void setCellsToScreen(int col, int row);

			void linkLineInGrid(int col1,int row1,int col2,int row2);

			bool checkCells();

			Vec2 coordinateToVec2(int col, int row);
			
			int *vec2ToCoordinate(Vec2 vec);

			void showLightCells(CellsColor col);  //shader light
			
			void recoverLightCells(CellsColor col);//recover light

			void moveCell(Cells *cell,int col1, int row1, int col2, int row2);//�ƶ���ʾ�ṹ�����ı�洢λ��





			//�����ĸ��̳������麯�����������ɿ��ƺ���
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
			bool _isCanRunning{false};

			int transformArr[2];
};


#endif //__TIlesLayer_H__