#ifndef SPRITEFX_H
#define SPRITEFX_H

#include <vector>
#include <allegro5/allegro.h>

#include "Misc.h"
#include "Sequence.h"

class SpriteFX : public Sequence
{
    public:
        SpriteFX(ALLEGRO_BITMAP* atlas);
        virtual ~SpriteFX();

        void render(unsigned index, int x, int y) const;
        void render(Frame* frame, int x, int y) const;

    protected:

    private:

        ALLEGRO_BITMAP* _atlas = nullptr;
};

#endif // SPRITEFX_H
