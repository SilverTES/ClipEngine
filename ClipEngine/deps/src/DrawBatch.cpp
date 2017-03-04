#include "DrawBatch.h"

std::vector<ALLEGRO_VERTEX> DrawBatch::drawList()
{
    return _drawList;
}

void DrawBatch::clearAll()
{
    _drawList.clear();
}

void DrawBatch::insertQuad(Rect rectSrc, Rect rectDest, ALLEGRO_COLOR col)
{
    float sx = rectSrc._x;
    float sy = rectSrc._y;
    float sw = rectSrc._w;
    float sh = rectSrc._h;

    float dx = rectDest._x;
    float dy = rectDest._y;
    float dw = rectDest._w;
    float dh = rectDest._h;

    float z = 0;

    /*
        A         B
          o-----o
          |    /|
          |  /  |
          |/    |
          o-----o
        C         D
    */

    _drawList.push_back(ALLEGRO_VERTEX{
        dx    , dy    , z,
        sx    , sy    , col }); // A
    _drawList.push_back(ALLEGRO_VERTEX{
        dx + dw, dy    , z,
        sx + sw, sy    , col }); // B
    _drawList.push_back(ALLEGRO_VERTEX{
        dx    , dy + dh, z,
        sx    , sy + sh, col }); // C

    _drawList.push_back(ALLEGRO_VERTEX{
        dx    , dy + dh, z,
        sx    , sy + sh, col }); // C
    _drawList.push_back(ALLEGRO_VERTEX{
        dx + dw, dy + dh, z,
        sx + sw, sy + sh, col }); // D
    _drawList.push_back(ALLEGRO_VERTEX{
        dx + dw, dy    , z,
        sx + sw, sy    , col }); // B
}

void DrawBatch::drawAll(ALLEGRO_BITMAP *atlas)
{
    if (!_drawList.empty() && (atlas != nullptr))
        al_draw_prim(&_drawList[0], nullptr, atlas, 0, _drawList.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
}
