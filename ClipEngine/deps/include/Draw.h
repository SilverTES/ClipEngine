#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include <vector>
#include <memory>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

struct Rect;

namespace Draw
{
    using Color = ALLEGRO_COLOR;
    using Bitmap = ALLEGRO_BITMAP;
	using Font = ALLEGRO_FONT;
    using List = std::vector<ALLEGRO_VERTEX>;

    // Primitives
    void lineBegin(List& drawList);
    void lineEnd(List& drawList);
    void lineBatch(List& drawList, VAR x1, VAR y1, VAR x2, VAR y2, Color color);

    void line(List& drawList, VAR x1, VAR y1, VAR x2, VAR y2, Color color, VAR thickness);

    void sight(List& drawList, VAR x, VAR y, int screenW, int screenH, ALLEGRO_COLOR color);
    void grid(VAR x, VAR y, VAR w, VAR h, int sizeX, int sizeY, ALLEGRO_COLOR color);
    void gridBatch(List& drawList, VAR x, VAR y, VAR w, VAR h, int sizeX, int sizeY, ALLEGRO_COLOR color);
    void losange(List& drawList, VAR x, VAR y, VAR w, VAR h, ALLEGRO_COLOR color);

    // Bitmap

    void bitmapBegin(List& drawList);
    void bitmapEnd(List& drawList, Bitmap* atlas);
    void bitmapBatch(List& drawList, Rect rectSrc, Rect rectDest, Color col = al_map_rgba(255, 255, 255, 255));

    void mosaic(Rect rectView, VAR x, VAR y, int repX, int repY, ALLEGRO_BITMAP* bitmap, ALLEGRO_COLOR color);
    void mosaicBatch(List& drawList, Rect rectView, VAR x, VAR y, int repX, int repY, ALLEGRO_BITMAP* bitmap, ALLEGRO_COLOR color);

}
#endif // DRAW_H_INCLUDED
