#ifndef DRAWBATCH_H_INCLUDED
#define DRAWBATCH_H_INCLUDED

#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "World2D.h"

struct DrawBatch
{
    public:
        std::vector<ALLEGRO_VERTEX> drawList();
        void clearAll();
        void insertQuad(Rect rectSrc, Rect rectDest, ALLEGRO_COLOR col = al_map_rgba(255, 255, 255, 255));
        void drawAll(ALLEGRO_BITMAP *atlas);

    private:
        std::vector<ALLEGRO_VERTEX> _drawList;
};

#endif // DRAWBATCH_H_INCLUDED
