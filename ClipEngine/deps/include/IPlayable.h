#ifndef IPLAYABLE_H
#define IPLAYABLE_H

#include <memory>
#include <set>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include "Window.h"
#include "Animation.h"

//#define MAKE_CLIP(name,...) (new Clip(name,##__VA_ARGS__))
#define MAKE_CLIP(name) (new Clip(name))
#define MAKE_CLONE(original,cloneName) (Clip::cloneOf(original,cloneName))->appendTo(original->_parent)
#define KILL_THIS() _PARENT->del(_ID);return

#define UPDATE(code) setUpdate([&](Clip * _THIS){code})
#define RENDER(code) setRender([&](Clip * _THIS){code})

#define GOTO_NEXT_FRAME() _THIS->nextFrame()
#define GOTO_PREV_FRAME() _THIS->prevFrame()
#define ON_FRAME(f) if(_THIS->onFrame(f))

#define ON_PLAY() if(_THIS->isPlay())
#define PLAY_AT(f) _THIS->playAt(f)
#define STOP_AT(f) _THIS->stopAt(f)

#define PLAY() _THIS->play()
#define STOP() _THIS->stop()
#define START() _THIS->start()
#define PAUSE() _THIS->pause()
#define RESUME() _THIS->resume()

#define SHOW() _THIS->show()
#define HIDE() _THIS->hide()

#define _ID _THIS->id()

#define _PARENT _THIS->parent()

#define _RECT _THIS->_rect

// Relative position
#define _X _THIS->_x
#define _Y _THIS->_y
#define _Z _THIS->_z

// Absolute Position
#define _ABSX _THIS->absX()
#define _ABSY _THIS->absY()
#define _OX _THIS->_oX
#define _OY _THIS->_oY

#define _WINDOW _THIS->window()
#define _FONT _THIS->_font
#define _NAME _THIS->_name.c_str()
#define _CURFRAME _THIS->_currentFrame

// Macro Message
#define KILL_MESSAGE() Message::kill(_THIS)
#define _MESSAGE _THIS->_message
#define ON_MESSAGE() if (nullptr != _THIS->_message)
#define ON_MESSAGE_TYPE(type) if (_THIS->_message->_type == type)

// Macro Collision

#define ON_COLLIDE() if (_THIS->_isCollide && !_THIS->_vecCollideBy.empty())
//#define ON_COLLIDE_NAME(name) if (_PARENT->index(_THIS->_indexCollideBy)->_name == name)
//#define ON_COLLIDE_INDEX(index) if (_PARENT->index(_THIS->_indexCollideBy)->_id == index)

#define _ID_COLLIDE_NAME _THIS->_idCollideName
#define _ID_COLLIDE_INDEX _THIS->_idCollideIndex

#define ON_COLLIDE_NAME(name) if (Collision2D::onCollideByName(_THIS,name) >= 0)
#define ON_COLLIDE_INDEX(index) if (Collision2D::onCollideByIndex(_THIS,index) >= 0)

#define DRAW_TEXTF(color,x,y,flag,text,...) if (_FONT!=nullptr) al_draw_textf(_FONT,color,x,y,flag,text,##__VA_ARGS__)

struct Message;

template <class PLAYABLE>
struct IPlayable
{
    PLAYABLE *_parent = nullptr;
    bool _isPlay = true;
    bool _isVisible = true;

    // Collision Check
    bool _isCollide = false;
    bool _isCollidable = false;
    std::set<int> _vecCollideBy; // std::set for avoid duplicate elements
    int _idCollideName = -1;
    int _idCollideIndex = -1;

    //Mouse
    bool _isOver;  // Mouse over the PLAYBLE
    bool _isOut;   // Mouse out of PLAYABLE
    bool _isFocus; // PLAYABLE is Focused

    //
    int _type = 0; // Type of Clip ex: Root = 0, Camera = 1, Player = 2, ...
    int _id = 0;   // Index of Clip
    int _currentFrame = 0;
    int _nbFrame = 0;

    // World Position
    VAR _x = 0;
    VAR _y = 0;
    VAR _z = 0;

    VAR _cameraMoveFactor = 0;

    // Rect of the PLAYABLE = Draw position
    Rect _rect;

    // Offset : _rect._x, _rect._y <-> _x, _y
    VAR _oX = 0;
    VAR _oY = 0;

    std::string _name;

    ALLEGRO_FONT *_font = nullptr;

    std::shared_ptr<Window> _window;

    std::function<void(PLAYABLE*)> _update = nullptr;
    std::function<void(PLAYABLE*)> _render = nullptr;

    Message* _message = nullptr;

    PLAYABLE* setUpdate(std::function<void(PLAYABLE*)> update)
    {
        _update = update;
        return (PLAYABLE*)this;
    }

    PLAYABLE* setRender(std::function<void(PLAYABLE*)> render)
    {
        _render = render;
        return (PLAYABLE*)this;
    }

    PLAYABLE* setCollidable(bool isCollidable)
    {
        _isCollidable = isCollidable;
        return (PLAYABLE*)this;
    }

    PLAYABLE* setCameraMoveFactor(float cameraMoveFactor)
    {
        _cameraMoveFactor = cameraMoveFactor;
        return (PLAYABLE*)this;
    }

    PLAYABLE* setSize(int w, int h)
    {
        _rect._w = w;
        _rect._h = h;
        return (PLAYABLE*)this;
    }


    IPlayable(std::string name):
        _name(name)
    {
        _rect = Rect{0,0,0,0};
        //ctor
    }

    virtual ~IPlayable()
    {
        _font = nullptr;
        //dtor
    }

    void hide()
    {
        _isVisible = false;
    }
    void show()
    {
        _isVisible = true;
    }

    // Player
    bool isPlay() const
    {
        return _isPlay;
    }

    void play()
    {
        _isPlay = true;
    }
    void stop()
    {
        _isPlay = false;
        _currentFrame = 0;
    }

    void pause()
    {
        _isPlay = false;
    }

    void resume()
    {
        play();
    }

    void start()
    {
        _currentFrame = 0;
        play();
    }

    void playAt(int frame)
    {
        _currentFrame = frame;
        _isPlay = true;
    }

    void stopAt(int frame)
    {
        _currentFrame = frame;
        _isPlay = false;
    }

    bool onFrame(int frame)
    {
        if (_currentFrame == frame)
            return true;
        else
            return false;
    }

    void prevFrame()
    {
        if (_isPlay)
            --_currentFrame;
    }

    void nextFrame()
    {
        if (_isPlay)
            ++_currentFrame;
    }


    void setFont(ALLEGRO_FONT *font)
    {
        _font = font;
    }
    ALLEGRO_FONT* font() const
    {
        return _font;
    }

    void setWindow(std::shared_ptr<Window> window)
    {
        _window = window;
    }
    std::shared_ptr<Window> window() const
    {
        return _window;
    }

    int id()
    {
        return _id;
    }

    void setId(int id)
    {
        _id = id;
    }

    std::string name() const
    {
        return _name;
    }


    VAR absX()
    {
        if (nullptr != _parent)
            return _parent->_rect._x + _x - _oX;
        else
            return _x;
    }
    VAR absY()
    {
        if (nullptr != _parent)
            return _parent->_rect._y + _y - _oY;
        else
            return _y;
    }

    VAR parentX()
    {
        if (nullptr != _parent)
            return _parent->_x;
        else
            return 0;
    }

    VAR parentY()
    {
        if (nullptr != _parent)
            return _parent->_y;
        else
            return 0;
    }

    VAR parentRectX()
    {
        if (nullptr != _parent)
            return _parent->_rect._x;
        else
            return 0;
    }

    VAR parentRectY()
    {
        if (nullptr != _parent)
            return _parent->_rect._y;
        else
            return 0;
    }

    VAR parentRectW()
    {
        if (nullptr != _parent)
            return _parent->_rect._w;
        else
            return 0;
    }

    VAR parentRectH()
    {
        if (nullptr != _parent)
            return _parent->_rect._h;
        else
            return 0;
    }

};

#endif // IPLAYABLE_H
