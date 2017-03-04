#ifndef BASECOMPONENT_H_INCLUDED
#define BASECOMPONENT_H_INCLUDED

#include "Clip.h"
#include "Collision2D.h"

namespace BaseComponent
{
    //#define POS _THIS->get<Position>()
    //#define _POS get<Position>()

    //struct Position : public ComponentHelper<Position>
    //{
    //    VAR _x;
    //    VAR _y;
    //    VAR _z;
    //
    //    Position(VAR x = 0, VAR y = 0, VAR z = 0)
    //    {
    //        _type = componentType("POSITION", true);
    //
    //        _x = x;
    //        _y = y;
    //        _z = z;
    //    }
    //
    //    void update() override
    //    {
    //
    //    }
    //    void render() override
    //    {
    //
    //    }
    //
    //} __attribute__((packed));

    #define VELOCITY _THIS->get<BaseComponent::Velocity>()
    #define _VELOCITY get<BaseComponent::Velocity>()
    struct Velocity : public ComponentHelper<Velocity>
    {
        VAR _x;
        VAR _y;
        VAR _z;

        VAR _ax;
        VAR _ay;
        VAR _az;

        Velocity(VAR x = 0, VAR y = 0, VAR z = 0)
        {
            _type = componentType("VELOCITY", true);
            _x = x;
            _y = y;
            _z = z;
        }

        void update() override
        {

        }
        void render() override
        {

        }

    };

    #define TEMPO _THIS->get<BaseComponent::Tempo>()
    #define _TEMPO get<BaseComponent::Tempo>()
    struct Tempo : public ComponentHelper<Tempo>
    {
        int _tempo;
        int _duration;
        bool _tic;

        Tempo(int duration = 100)
        {
            _type = componentType("TEMPO", true);
            _tempo = 0;
            _duration = duration;
            _tic = false;
        }

        void update() override
        {
            ++_tempo;

            if (_tempo < _duration)
                _tic = false;

            if (_tempo >_duration)
            {
                _tic = true;
                _tempo = 0;
            }
        }

        void render() override
        {

        }
    };

    #define ANIMATE _THIS->get<BaseComponent::Animate>()
    #define _ANIMATE get<BaseComponent::Animate>()
    struct Animate : public ComponentHelper<Animate>
    {

        bool _atEnd = false;

        int _currentFrame;

        int _rangeA;
        int _rangeB;

        int _direction;

        int _countPlayDelay;
        int _playDelay;

        int _countFrameDelay;
        int _frameDelay;

        bool _isPlay;

        Animation* _animation = nullptr;
        Sequence* _sequence = nullptr;

        Animate()
        {
            _type = componentType("ANIMATE", true);
            _playDelay = 0;
            _currentFrame = 0;
            _rangeA = 0;
            _rangeB = 0;
            _direction = 0;

        }

        Clip* setAnimation(Animation* animation)
        {
            _animation = animation;
            return _clip;
        }

        Clip* setSequence(Sequence* sequence)
        {
            _sequence = sequence;
            return _clip;
        }


        Clip* startAt(int frame, int playDelay = 0, int direction = 1,int rangeA = 0, int rangeB = 0)
        {
            _isPlay = true;
            _playDelay = playDelay;
            _countPlayDelay = 0;
            _countFrameDelay = 0;

            _rangeA = rangeA;
            if (0 == rangeB)
                _rangeB = _sequence->nbFrame()-1;
            else
                _rangeB = rangeB;


            _currentFrame = frame;
            _direction = direction;

            return _clip;
        }

        void stop()
        {
            _isPlay = false;
        }

        void update();

        // draw Animation in specific position of indexed Sequence
        void render(unsigned index, int x, int y)
        {
            _animation->render(index, x, y, _currentFrame);
        }

        // draw Animation in specific position of current Sequance
        void render(int x, int y)
        {
            if (nullptr != _sequence)
                _animation->render(_sequence, x, y, _currentFrame);
        }

        // draw Animtion at Clip Axe Position  of current Sequence
        void render();



    };

    #define DRAGGABLE _THIS->get<BaseComponent::Draggable>()
    #define _DRAGGABLE get<BaseComponent::Draggable>()
    struct Draggable : public ComponentHelper<Draggable>
    {
        bool _isDrag = false;
        bool _isWinLimit = false;
        float _dragX = 0;
        float _dragY = 0;

        Rect _rectDrag;

        Rect _limitRect;
        Input::Mouse* _mouse = nullptr;

        Draggable()
        {
            _type = componentType("DRAGGABLE", true);
        }

        Draggable(Input::Mouse* mouse, Rect limitRect, bool isWinLimit = false)
        {
            _type = componentType("DRAGGABLE", true);

            _mouse = mouse;
            _limitRect = limitRect;
            _isWinLimit = isWinLimit;

            if (nullptr != _clip)
            {
                _rectDrag._x = _clip->_rect._x;
                _rectDrag._y = _clip->_rect._y;
                _rectDrag._w = _clip->_rect._w;
                _rectDrag._h = _clip->_rect._h;
            }
        }

        void update();
        void render();
    };

    #define CAMERA _THIS->get<BaseComponent::Camera>()
    #define _CAMERA get<BaseComponent::Camera>()
    struct Camera : public ComponentHelper<Camera>
    {
        bool _isMove = false;
        Rect _rectView;
        Rect _limitZone;

        Camera()
        {
            _type = componentType("CAMERA", true);
        }

        Camera(VAR w, VAR h, Rect limitZone)
        {
            _type = componentType("CAMERA", true);
            _rectView._w = w;
            _rectView._h = h;
            _limitZone = limitZone;
        }

        void setPosition(VAR x, VAR y)
        {
            _rectView._x = x;
            _rectView._y = y;

            limitViewZone();
        }

        void limitViewZone()
        {
            if (_rectView._x < _limitZone._x)
                _rectView._x = _limitZone._x;

            if (_rectView._y < _limitZone._y)
                _rectView._y = _limitZone._y;

            if (_rectView._x > _limitZone._w - _rectView._w)
                _rectView._x = _limitZone._w - _rectView._w;

            if (_rectView._y > _limitZone._h - _rectView._h)
                _rectView._y = _limitZone._h - _rectView._h;
        }

        void moveX(VAR vx)
        {
            _rectView._x += vx;
            limitViewZone();
        }
        void moveY(VAR vy)
        {
            _rectView._y += vy;
            limitViewZone();
        }


        void update();
        void render();

    };

    #define TILEMAP2D _THIS->get<BaseComponent::TileMap2D>()
    #define _TILEMAP2D get<BaseComponent::TileMap2D>()
    struct TileMap2D : public ComponentHelper<TileMap2D>
    {

        VAR _tileW;
        VAR _tileH;

        Rect _rect; // rect of the TileMap2D
        Rect _rectView;; // rect of the View

        Map2D<Tile>* _map2D = nullptr;
        ALLEGRO_BITMAP* _atlas = nullptr;

        TileMap2D()
        {
            _type = componentType("TILEMAP2D", true);
        }

        TileMap2D(Rect rectView, unsigned sizeW, unsigned sizeH, VAR tileW, VAR tileH, VAR x = 0, VAR y = 0)
        {
            _type = componentType("TILEMAP2D", true);

            _tileW = tileW;
            _tileH = tileH;

            _rect._x = x;
            _rect._y = y;
            _rect._w = sizeW*tileW;
            _rect._h = sizeH*tileH;

            _rectView._x = rectView._x;
            _rectView._y = rectView._y;
            _rectView._w = rectView._w;
            _rectView._h = rectView._h;

            _map2D = new Map2D<Tile>(sizeW, sizeH, new Tile());

        }

        Clip* setTileSize(unsigned tileW, unsigned tileH)
        {
            _tileW = tileW;
            _tileH = tileH;
            return _clip;
        }

        Clip* setAtlas(ALLEGRO_BITMAP* atlas)
        {
            _atlas = atlas;
            return _clip;
        }

        Clip* setPosition(VAR x, VAR y)
        {
            _rect._x = x;
            _rect._y = y;
            return _clip;
        }

        virtual ~TileMap2D()
        {
            if (nullptr != _map2D)
                delete _map2D;
        }

        void update();
        void render();

    };

}


#endif // BASECOMPONENT_H_INCLUDED
