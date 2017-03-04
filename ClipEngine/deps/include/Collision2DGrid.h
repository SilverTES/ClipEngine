#ifndef COLLISION2DGRID_H_INCLUDED
#define COLLISION2DGRID_H_INCLUDED

#include "World2D.h"

namespace Collision2D
{
    struct GridSpatialPart
    {
        VAR _originX;
        VAR _originY;
        int _gridW;
        int _gridH;
        int _cellSize;

        std::vector<std::vector<Cell*>> _vec2dCell;
        std::vector<Entity*> _vecEntity;

		GridSpatialPart(int gridW, int gridH, int cellSize);
		virtual ~GridSpatialPart();

		Cell *cell(unsigned x, unsigned y);
		void clearAll();
		void insert(unsigned index, Rect rect);

		std::vector<Entity*> findNear(std::vector<Entity*> &_vecIndexTemp, Rect rect);
		Entity* getNearest(Rect rect);
		void setPosition(int x, int y);

		void update();
		void render();

    };
}
#endif // COLLISION2DGRID_H_INCLUDED
