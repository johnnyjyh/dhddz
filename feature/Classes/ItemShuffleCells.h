#ifndef __ItemShuffleCells_H__
#define __ItemShuffleCells_H__
#include "ItemBase.h"
#include "CellsLayer.h"

class ItemShuffleCells :public ItemBase
{
public:
			ItemShuffleCells();
			~ItemShuffleCells();
			static ItemBase *createItem();
			bool init();
			void bindLayerCell(CellsLayer* _lay);
			void updateRecordTimes();

			CellsLayer *_layerCells{nullptr};
			Label *_recordTimeLabel{nullptr};
			CC_SYNTHESIZE(int, _recordTimes, RecordTime);

};

#endif// __ItemShuffleCells_H__