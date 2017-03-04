#include "DrawBatch.h"
#include "Draw.h"

//------------------------------------------------------------------------------ Primitives

void Draw::lineBegin(List& drawList)
{
    drawList.clear();
}

void Draw::lineEnd(List& drawList)
{
    if (!drawList.empty())
        al_draw_prim(&drawList[0], nullptr, nullptr, 0, drawList.size(), ALLEGRO_PRIM_LINE_LIST);
}

void Draw::line(List &drawList, VAR x1, VAR y1, VAR x2, VAR y2, Color color, VAR thickness)
{
    al_draw_line(.5+x1,.5+y1,.5+x2,.5+y2,color,thickness);
}

void Draw::lineBatch(List& drawList, VAR x1, VAR y1, VAR x2, VAR y2, Color color)
{
    drawList.push_back
    (
        ALLEGRO_VERTEX
        {
            0.5f+x1,0.5f+y1,0.0f,
            0,0,
            color
        }
    );
    drawList.push_back
    (
        ALLEGRO_VERTEX
        {
            0.5f+x2,0.5f+y2,0.0f,
            0,0,
            color
        }
    );

}

void Draw::sight(List& drawList, VAR x, VAR y, int screenW, int screenH, ALLEGRO_COLOR color)
{
    lineBatch(drawList,0,y,screenW,y,color);
    lineBatch(drawList,x,0,x,screenH,color);
}

void Draw::grid(VAR x, VAR y, VAR w, VAR h, int sizeX, int sizeY, ALLEGRO_COLOR color)
{
    List drawList;
    lineBegin(drawList);
    for (int i(0); i<(w/sizeX); i++)
    {
        lineBatch(drawList,i*sizeX+x, y, i*sizeX+x, h+y, color);
    }

    for (int i(0); i<(h/sizeY)+1; i++)
    {
        lineBatch(drawList,x, i*sizeY+y, w+x, i*sizeY+y, color);
    }
    lineEnd(drawList);
}
void Draw::gridBatch(List& drawList, VAR x, VAR y, VAR w, VAR h, int sizeX, int sizeY, ALLEGRO_COLOR color)
{
    for (int i(0); i<(w/sizeX); i++)
    {
        lineBatch(drawList,i*sizeX+x, y, i*sizeX+x, h+y, color);
    }

    for (int i(0); i<(h/sizeY)+1; i++)
    {
        lineBatch(drawList,x, i*sizeY+y, w+x, i*sizeY+y, color);
    }
}


void Draw::losange(List& drawList, VAR x, VAR y, VAR w, VAR h, ALLEGRO_COLOR color)
{
    lineBatch(drawList,x, y+h/2, x+w/2, y, color);
    lineBatch(drawList,x+w, y+h/2, x+w/2, y, color);
    lineBatch(drawList,x, y+h/2, x+w/2, y+h, color);
    lineBatch(drawList,x+w, y+h/2, x+w/2, y+h, color);
}


//------------------------------------------------------------------------------ Bitmap

void Draw::bitmapBegin(List& drawList)
{
    drawList.clear();
}

void Draw::bitmapEnd(List& drawList, Bitmap* atlas)
{
    if (!drawList.empty() && (atlas != nullptr))
        al_draw_prim(&drawList[0], nullptr, atlas, 0, drawList.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
}

void Draw::bitmapBatch(List& drawList, Rect rectSrc, Rect rectDest, Color col)
{
    VAR sx = rectSrc._x;
    VAR sy = rectSrc._y;
    VAR sw = rectSrc._w;
    VAR sh = rectSrc._h;

    VAR dx = rectDest._x;
    VAR dy = rectDest._y;
    VAR dw = rectDest._w;
    VAR dh = rectDest._h;

    VAR z = 0;

    /*
        A         B
          o-----o
          |    /|
          |  /  |
          |/    |
          o-----o
        C         D
    */

    drawList.push_back // A
    (
        ALLEGRO_VERTEX
        {
            dx    , dy    , z,
            sx    , sy    , col
        }
    );
    drawList.push_back // B
    (
        ALLEGRO_VERTEX
        {
            dx + dw, dy    , z,
            sx + sw, sy    , col
        }
    );
    drawList.push_back // C
    (
        ALLEGRO_VERTEX
        {
            dx    , dy + dh, z,
            sx    , sy + sh, col
        }
    );
    drawList.push_back // C
    (
        ALLEGRO_VERTEX
        {
            dx    , dy + dh, z,
            sx    , sy + sh, col
        }
    );
    drawList.push_back // D
    (
        ALLEGRO_VERTEX
        {
            dx + dw, dy + dh, z,
            sx + sw, sy + sh, col
        }
    );
    drawList.push_back // B
    (
        ALLEGRO_VERTEX
        {
            dx + dw, dy    , z,
            sx + sw, sy    , col
        }
    );
}


void Draw::mosaic(Rect rectView, VAR x, VAR y, int repX, int repY, ALLEGRO_BITMAP* bitmap, ALLEGRO_COLOR color)
{
    VAR tileW = al_get_bitmap_width(bitmap);
    VAR tileH = al_get_bitmap_height(bitmap);

    List drawList;
    bitmapBegin(drawList);

    for (int i = 0; i < repX; ++i)
    {
        if (x+i*tileW < rectView._x - tileW || x+i*tileW > rectView._w)
            continue;

        for (int j = 0; j < repY; ++j)
        {
            if(y+j*tileH < rectView._y - tileH || y+j*tileH > rectView._h)
                continue;
            bitmapBatch(drawList,Rect{0,0,tileW,tileH}, Rect{x+i*tileW,y+j*tileH,tileW,tileH}, color);
        }
    }
    bitmapEnd(drawList,bitmap);
}

void Draw::mosaicBatch(List& drawList, Rect rectView, VAR x, VAR y, int repX, int repY, ALLEGRO_BITMAP* bitmap, ALLEGRO_COLOR color)
{
    VAR tileW = al_get_bitmap_width(bitmap);
    VAR tileH = al_get_bitmap_height(bitmap);


    for (int i = 0; i < repX; ++i)
    {
        if (x+i*tileW < rectView._x - tileW || x+i*tileW > rectView._w)
            continue;

        for (int j = 0; j < repY; ++j)
        {
            if(y+j*tileH < rectView._y - tileH || y+j*tileH > rectView._h)
                continue;

            bitmapBatch(drawList,Rect{0,0,tileW,tileH}, Rect{x+i*tileW,y+j*tileH,tileW,tileH}, color);
        }
    }
}
