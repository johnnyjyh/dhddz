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
			Cells *createCells(CellsColor col);
			bool initCells();
			void displayCells();
			bool isCanDestroyCells();
			void destroyCells();
			void supplyCells();
			bool isPreCells();
			void setCellsToScreen(int col, int row);

			void checkCells();


			void showLightCells(CellsColor col);  //shader light
			void recoverLightCells(CellsColor col);//recover light




			//�����ĸ��̳������麯�����������ɿ��ƺ���
			bool onTouchBegan(Touch *touch, Event *unused_event);

			void onTouchMoved(Touch *touch, Event *unused_event);

			void onTouchEnded(Touch *touch, Event *unused_event);

			void onTouchCancelled(Touch *touch, Event *unused_event);



			std::vector<std::vector<Cells *>> _displayCell;
			std::vector<Cells *> _supCell;
			std::vector<Cells *> _supDisplayCell[5];
			std::list<Cells *> _desCell;
};


#endif //__TIlesLayer_H__