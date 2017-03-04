#ifndef FRAME_H_INCLUDED
#define FRAME_H_INCLUDED

#include "World2D.h"

struct Frame
{
    int _id;
    Rect _rect;
    int _delay;
    int _count;
    int _axeX;
    int _axeY;
    float _scaleX;
    float _scaleY;
    float _angle;

    Frame(int id, Rect rect, int delay = 0, int axeX = 0, int axeY = 0, float scaleX = 1, float scaleY = 1, float angle = 0)
    {
        _id = id;
        _rect = rect;

        _delay = delay;
        _count = 0;

        _axeX = axeX;
        _axeY = axeY;

        _scaleX = scaleX;
        _scaleY = scaleY;
        _angle = angle;
    }

};

#endif // FRAME_H_INCLUDED
