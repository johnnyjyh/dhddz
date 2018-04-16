#ifndef __Barrier_H__
#define __Barrier_H__
#include "common.h"
class Barrier:public Node
{
public:
			Barrier();
			~Barrier();
			static Barrier *create();
			virtual void bindBarrierSprite(Sprite *sp, CellsColor _color, int life)=0;


			int _type;
			Sprite *_barrier;
			int _life;
};

#endif //__Barrier_H__

