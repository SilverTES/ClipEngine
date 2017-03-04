#include "BaseComponent.h"
#include "DrawBatch.h"

void BaseComponent::Animate::update()
{
    //mlog("--- Begin Animate Update ---\n");
    if (_isPlay)
    {
        if (nullptr != _sequence)
            _frameDelay = _sequence->frame(_currentFrame)->_delay;

        if (_countPlayDelay > _playDelay)
        {
            _atEnd = false;

            _currentFrame += _direction;
            _countPlayDelay = 0;

            // A to B
            if (_direction > 0 && _currentFrame > _rangeB)
            {
                _currentFrame = _rangeA;
                _atEnd = true;
            }

            // B to A
            if (_direction < 0 && _currentFrame < _rangeA)
            {
                _currentFrame = _rangeB;
                _atEnd = true;
            }


        }

        if (_countFrameDelay > _frameDelay)
        {
            ++_countPlayDelay;
            _countFrameDelay = 0;
        }

        ++_countFrameDelay;

        _animation->update();

    }
}

void BaseComponent::Animate::render()
{
    if (nullptr != _sequence)
        _animation->render
        (
            _sequence,
            _clip->absX() + _clip->_oX,
            _clip->absY() + _clip->_oY,
            _currentFrame
        );
}

void BaseComponent::Draggable::update()
{
    if (nullptr != _clip)
    {
        _rectDrag._x = _clip->_rect._x;
        _rectDrag._y = _clip->_rect._y;
        _rectDrag._w = _clip->_rect._w;
        _rectDrag._h = _clip->_rect._h;
        //_mouse.update(mouseX, mouseY, mouseButton);
        //if (Misc::inRect(_mouse->_x, _mouse->_y, _clip->_rect))
        //if (_mouse->_x > _rectDrag._x &&
        //	_mouse->_x < _rectDrag._x + _rectDrag._w &&
        //	_mouse->_y > _rectDrag._y &&
        //	_mouse->_y < _rectDrag._y + _rectDrag._h)

        if (Collision2D::pointRect(Vec2D {_mouse->_x , _mouse->_y}, _rectDrag))
            _clip->_isOver = true;
        else
            _clip->_isOver = false;

        if (_mouse->_move && _isDrag && _clip->_isFocus)
        {
            _clip->_x = _mouse->_x - _dragX;
            _clip->_y = _mouse->_y - _dragY;
        }

        if (_isWinLimit)
        {
            if (_clip->_rect._x < _limitRect._x)
            {
                _clip->_rect._x = _limitRect._x;
                //_mouse->_x = _rect.x + _dragX;
            }
            if (_clip->_rect._y < _limitRect._y)
            {
                _clip->_rect._y = _limitRect._y;
                //_mouse->_y = _rect.y + _dragY;
            }
            if (_clip->_rect._x > _limitRect._w - _clip->_rect._w - 2)
            {
                _clip->_rect._x = _limitRect._w - _clip->_rect._w - 2;
                //_mouse->_x = _rect.x + _dragX;
            }
            if (_clip->_rect._y > _limitRect._h - _clip->_rect._h - 2)
            {
                _clip->_rect._y = _limitRect._h - _clip->_rect._h - 2;
                //_mouse->_y = _rect.y + _dragY;
            }
        }

        if (_mouse->_down)
        {

            if (_clip->_isOver)
            {
                if (_isDrag) _clip->_isFocus = true;

                if (!_isDrag && (_mouse->_button & 1) &&
                    !_mouse->_drag && !_mouse->_reSize)
                {
                    _isDrag = true;
                    _mouse->_drag = true;
                    //log(0,"< Draggable is On >");
                }
            }
        }
        else
        {
            if (_isDrag)
                _isDrag = false;
        }


        if (_isDrag)
        {
            _dragX = _mouse->_x - _clip->_x;
            _dragY = _mouse->_y - _clip->_y;
        }
    }




}
void BaseComponent::Draggable::render()
{

    if (nullptr != _clip)
    {
        // Draw the rectDrag Zone !
        al_draw_filled_rectangle(.5+_rectDrag._x,
                                 .5+_rectDrag._y,
                                 .5+_rectDrag._x + _rectDrag._w,
                                 .5+_rectDrag._y + _rectDrag._h,
                                 al_map_rgba(25, 50, 80, 250));
        if (!_clip->_isFocus)
        {
            al_draw_rectangle(.5+_clip->_rect._x,
                              .5+_clip->_rect._y,
            				  .5+_clip->_rect._x + _clip->_rect._w,
            				  .5+_clip->_rect._y + _clip->_rect._h,
            				  al_map_rgba(155, 20, 50, 55), 0);


        }	else
        {
            al_draw_filled_rectangle(.5+_rectDrag._x,
                                     .5+_rectDrag._y,
                                     .5+_rectDrag._x + _rectDrag._w,
                                     .5+_rectDrag._y + _rectDrag._h,
                                     al_map_rgba(55, 100, 150, 250));
        }


        if (_clip->_isOver)
        {
            if (_isDrag)
            {
                al_draw_rectangle(.5+_clip->_rect._x,
                                  .5+_clip->_rect._y,
                				  .5+_clip->_rect._x + _clip->_rect._w,
                				  .5+_clip->_rect._y + _clip->_rect._h,
                				  al_map_rgb(255, 120, 0), 0);
            }
            else
            {
                al_draw_rectangle(.5+_clip->_rect._x,
                                  .5+_clip->_rect._y,
                				  .5+_clip->_rect._x + _clip->_rect._w,
                				  .5+_clip->_rect._y + _clip->_rect._h,
                				  al_map_rgb(55, 250, 180), 0);
            }
        }
    }


}


void BaseComponent::Camera::update()
{
    if (nullptr != _clip->_parent)
        for (unsigned i = 0; i < _clip->_parent->vecSize(); ++i)
        {
            _clip->_parent->index(i)->_x = -(_rectView._x * _clip->_parent->index(i)->_cameraMoveFactor);
            _clip->_parent->index(i)->_y = -(_rectView._y * _clip->_parent->index(i)->_cameraMoveFactor);
        }
}

void BaseComponent::Camera::render()
{

}

void BaseComponent::TileMap2D::update()
{
    _rect._x = _clip->absX();
    _rect._y = _clip->absY();
}

void BaseComponent::TileMap2D::render()
{
    DrawBatch drawBatch;

    for (unsigned x = 0; x < _map2D->_sizeW; ++x)
    {
        if (x*_tileW+_rect._x < _rectView._x - _tileW || x*_tileW+_rect._x > _rectView._w)
            continue;

        for (unsigned y = 0; y < _map2D->_sizeH; ++y)
        {

            if(y*_tileH+_rect._y < _rectView._y - _tileH || y*_tileH+_rect._y > _rectView._h)
                continue;

            Tile* tile = _map2D->get(x,y);

            if (nullptr != tile)
            {
                if (tile->_rect._w < 1 || tile->_rect._h < 1)
                    continue;

                drawBatch.insertQuad
                (
                    //Rect{0, 0, _tileW, _tileH}, // Tile selected !
                    tile->_rect,
                    Rect{x*_tileW+_rect._x, y*_tileH+_rect._y, _tileW, _tileH}
                );

//                if (tile->_type != 0)
//                    al_draw_filled_rectangle(
//                        .5 + x*_tileW + _rect._x,
//                        .5 + y*_tileH + _rect._y,
//                        .5 + x*_tileW + _rect._x + _tileW,
//                        .5 + y*_tileH + _rect._y + _tileH,
//                        al_map_rgb(150, 150, 150));
//
//                al_draw_rectangle(
//                    .5 + x*_tileW + _rect._x,
//                    .5 + y*_tileH + _rect._y,
//                    .5 + x*_tileW + _rect._x + _tileW,
//                    .5 + y*_tileH + _rect._y + _tileH,
//                    al_map_rgb(250, 150, 150), 0);
//
//                al_draw_filled_circle(
//                    .5 + x*_tileW + _tileW / 2 + _rect._x,
//                    .5 + y*_tileH + _tileH / 2 + _rect._y,
//                    1, al_map_rgba(0, 155, 100, 255));


//                    al_draw_textf(
//                        font,
//                        al_map_rgba(0, 155, 100, 255),
//                        x*_cellW + 2 + _rect._x,
//                        y*_cellH + 2 + _rect._y,
//                        0,
//                        "%i", _vec2D->get(x, y)->index);
            }


        }
    }

    drawBatch.drawAll(_atlas);
}
