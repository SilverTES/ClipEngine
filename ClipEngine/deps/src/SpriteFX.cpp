#include "SpriteFX.h"

SpriteFX::SpriteFX(ALLEGRO_BITMAP *atlas):
    _atlas(atlas)
{
    //ctor
}

SpriteFX::~SpriteFX()
{
    if (!_vecFrame.empty())
    {
        for (auto & it: _vecFrame)
        {
            if (it != nullptr)
            {
                delete it;
                it = nullptr;
            }

        }
        _vecFrame.clear();
    }
    //dtor
}

void SpriteFX::render(unsigned index, int x, int y) const
{
    if (index >= 0 && index < _vecFrame.size())
    if (_vecFrame[index] != nullptr)
        al_draw_tinted_scaled_rotated_bitmap_region
        (
            // source bitmap region
            _atlas,

            // Source Position
            _vecFrame[index]->_rect._x,
            _vecFrame[index]->_rect._y,

            // Source Size
            _vecFrame[index]->_rect._w,
            _vecFrame[index]->_rect._h,

            // Tint
            al_map_rgb(255, 255, 255),

            // Center of Rotation/Scaling
            _vecFrame[index]->_axeX,
            _vecFrame[index]->_axeY,

            // Position of Frame on screen
            x,
            y,

            // scale
            _vecFrame[index]->_scaleX,
            _vecFrame[index]->_scaleY,

            // Angle of Rotation
            _vecFrame[index]->_angle,

             // flags
            0
        );

}

void SpriteFX::render(Frame* frame, int x, int y) const
{
    if (frame != nullptr)
        al_draw_tinted_scaled_rotated_bitmap_region
        (
            // source bitmap region
            _atlas,

            // Source Position
            frame->_rect._x,
            frame->_rect._y,

            // Source Size
            frame->_rect._w,
            frame->_rect._h,

            // Tint
            al_map_rgb(255, 255, 255),

            // Center of Rotation/Scaling
            frame->_axeX,
            frame->_axeY,

            // Position of Frame on screen
            x,
            y,

            // scale
            frame->_scaleX,
            frame->_scaleY,

            // Angle of Rotation
            frame->_angle,

             // flags
            0
        );
}


