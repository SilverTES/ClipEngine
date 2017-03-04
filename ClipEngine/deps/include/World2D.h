#ifndef WORLD2D_H_INCLUDED
#define WORLD2D_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Misc.h"

template <class TYPE>
using Vector2D = std::vector<std::vector<TYPE>>;

enum
{
	NW = 0,
	NE,
	SW,
	SE
};

struct Vec2D
{
    VAR _x;
    VAR _y;
};

struct Line
{
    VAR _x1;
    VAR _y1;
    VAR _x2;
    VAR _y2;

};

struct Circle
{
	VAR _x;
	VAR _y;
	VAR _r;
};

struct Rect
{
    VAR _x;
    VAR _y;
    VAR _w;
    VAR _h;
};

struct Entity
{
    unsigned _index;
    Rect _rect;
};

struct Cell
{
    std::vector<Entity*> _vecIndex; // Contain all index of Entity in the Cell
};

struct Tile
{
    int _id;
    int _type;

    Rect _rect; // Tile Rect

    Tile (int id = 0, int type = 0, Rect rect = {0,0,0,0}):
        _id(id),
        _type(type),
        _rect(rect)
    {
    }
};

template <class OBJECT>
void resizeVec(std::vector<OBJECT*>& vecObject, unsigned newSize)
{
    if (newSize == vecObject.size()) // nothing to resize
        return;

    if (newSize < vecObject.size()) // reduce size
    {
        for (unsigned i=0; i<newSize -1; ++i)
        {
            delete vecObject.back();
            vecObject.pop_back();
        }

        vecObject.resize(newSize);
    }
    else  // extend size
    {
        vecObject.resize(newSize, new OBJECT());
    }

}

template <class OBJECT>
struct Map2D
{
    unsigned _sizeW;
    unsigned _sizeH;

    Vector2D<OBJECT*> _vecObject2D;

    Map2D(unsigned sizeW, unsigned sizeH, OBJECT* object=nullptr):
        _sizeW(sizeW),
        _sizeH(sizeH)
    {
        resizeVecObject2D(_sizeW, _sizeH);

        fillObject2D(object);
    }

    virtual ~Map2D()
    {
        killAll();
    }

    void resizeVecObject2D(unsigned sizeW, unsigned sizeH)
    {
        _sizeW = sizeW;
        _sizeH = sizeH;

        //resizeVec<OBJECT>(_vecObject2D,_sizeW);
        _vecObject2D.resize(_sizeW);
        for (unsigned x = 0; x < _sizeW; ++x)
        {
            resizeVec<OBJECT>(_vecObject2D[x],_sizeH);
            for (unsigned y = 0; y < _sizeH; ++y)
            {
                _vecObject2D[x][y] = nullptr;
            }
        }
    }

    void killAll()
    {
        for (unsigned x = 0; x < _sizeW; ++x)
        {
            for (unsigned y = 0; y < _sizeH; ++y)
            {
                if (_vecObject2D[x][y] != nullptr)
                {
                    //std::cout << "delete at : " << x << " , " << y << " address = "<< _vecOject2D[x][y]<<  " \n";
                    delete _vecObject2D[x][y];
                    _vecObject2D[x][y] = nullptr;

                }
            }
            _vecObject2D[x].clear();
        }
        _vecObject2D.clear();
    }

    void fillObject2D(OBJECT* object)
    {
        for (unsigned x = 0; x < _sizeW; ++x)
        {
            for (unsigned y = 0; y < _sizeH; ++y)
            {
                set(x, y, new OBJECT(*object));
            }
        }
    }

    OBJECT *get(unsigned x, unsigned y)
    {
        if (x >= 0 && x < _sizeW &&
            y >= 0 && y < _sizeH)
            return _vecObject2D[x][y];
        else
            return nullptr;
    }

    void set(unsigned x, unsigned y, OBJECT *object)
    {

//        OBJECT* tmp = new OBJECT(_vecObject2D[x][y])
        if (nullptr != _vecObject2D[x][y])
            delete _vecObject2D[x][y];

        _vecObject2D[x][y] = object;
        //_vecObject2D[x][y] = new OBJECT(*object);
    }


};


#endif // WORLD2D_H_INCLUDED
