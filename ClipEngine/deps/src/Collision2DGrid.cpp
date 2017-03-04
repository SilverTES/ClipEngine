#include "Collision2DGrid.h"

namespace Collision2D
{
	GridSpatialPart::GridSpatialPart(int gridW, int gridH, int cellSize)
	{
		_cellSize = cellSize;

		_gridW = gridW;
		_gridH = gridH;

		_vec2dCell.resize(_gridW);
		for (int x = 0; x < _gridW; ++x)
		{
			_vec2dCell[x].resize(_gridH);
			for (int y = 0; y < _gridH; ++y)
			{
				_vec2dCell[x][y] = new Cell();
			}
		}
	}
	GridSpatialPart::~GridSpatialPart()
	{
		clearAll();
	}

	Cell* GridSpatialPart::cell(unsigned x, unsigned y)
	{
		return _vec2dCell[x][y];
	}

	void GridSpatialPart::clearAll()
	{
		for (int x = 0; x < _gridW; ++x)
		{
			for (int y = 0; y < _gridH; ++y)
			{
				if (cell(x, y) != nullptr)
				{
					if (!cell(x, y)->_vecIndex.empty())
					{
						for (auto & it : cell(x, y)->_vecIndex)
							if (it != nullptr)
							{
								delete it;
								it = nullptr;
							}

						cell(x, y)->_vecIndex.clear();

					}
				}
			}
		}
	}

	void GridSpatialPart::insert(unsigned index, Rect rect)
	{
		int x = rect._x - _originX - _cellSize;
		int y = rect._y - _originY - _cellSize;

		int left = std::max(0, x / _cellSize);
		int top = std::max(0, y / _cellSize);
		int right = std::min((float)_gridW - 1, (x + rect._w - 1) / _cellSize);
		int bottom = std::min((float)_gridH - 1, (y + rect._h - 1) / _cellSize);

		for (int x = left; x <= right; ++x)
		{
			for (int y = top; y <= bottom; ++y)
			{
				cell(x, y)->_vecIndex.push_back(new Entity{ index, rect });
			}
		}

	}

	std::vector<Entity*> GridSpatialPart::findNear(std::vector<Entity*> &_vecIndexTemp, Rect rect)
	{
		int x = rect._x - _originX - _cellSize;
		int y = rect._y - _originY - _cellSize;

		int left = std::max(0, x / _cellSize);
		int top = std::max(0, y / _cellSize);
		int right = std::min((float)_gridW - 1, (x + rect._w - 1) / _cellSize);
		int bottom = std::min((float)_gridH - 1, (y + rect._h - 1) / _cellSize);

		for (int x = left; x <= right; ++x)
		{
			for (int y = top; y <= bottom; ++y)
			{
				for (unsigned i = 0; i < cell(x, y)->_vecIndex.size(); ++i)
				{
					Entity *entity = cell(x, y)->_vecIndex[i];

					//if (entity->_index != index)
					_vecIndexTemp.push_back(entity);
				}

			}
		}
		return _vecIndexTemp;
	}

	Entity* GridSpatialPart::getNearest(Rect rect)
	{
		//            Entity *nearest = nullptr;
		//            int distance = std::numeric_limits<int>::max();
		return nullptr;
	}

	void GridSpatialPart::setPosition(int x, int y)
	{
		_originX = x;
		_originY = y;
	}

	void GridSpatialPart::update()
	{

	}

	void GridSpatialPart::render()
	{
		for (int x = 0; x <= _gridW; ++x)
		{
			for (int y = 0; y <= _gridH; ++y)
			{

				VAR px = x*_cellSize + _originX;
				VAR py = y*_cellSize + _originY;


				al_draw_rectangle(
					.5 + px, .5 + py,
					.5 + px + _cellSize, .5 + py + _cellSize,
					al_map_rgba(55, 55, 55, 55), 0
				);

				//al_draw_textf(
				//	font,
				//	al_map_rgb(250,250,0),
				//	px + 2, py + 2, 0,
				//	"%i,%i = %i",
				//	x, y, cell(x, y)->_vecIndex.size()
				//);

				if (!(cell(x, y)->_vecIndex.empty()))
				{
					//log("not empty !\n");

					//for (unsigned i = 0; i < cell(x, y)->_vecIndex.size(); ++i)
					//{
					//	al_draw_textf(font, al_map_rgb(25, 205, 255),
					//				  px + 2, py+12 + (i * 12)  , 0,
					//				  "vec[%i]=%i", i, cell(x, y)->_vecIndex[i]->_index
					//	);
					//}
				}


			}
		}

	}

}