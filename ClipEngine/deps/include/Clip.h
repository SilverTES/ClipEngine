#ifndef CLIP_H_INCLUDED
#define CLIP_H_INCLUDED

#include <map>

#include "Misc.h"
#include "Draw.h"
#include "Input.h"
#include "IContainer.h"
#include "IPlayable.h"

#include "Component.h"

#define _NUMBER(name) _THIS->_mapNumber[name]
#define _STRING(name) _THIS->_mapString[name]

struct Clip : public IPlayable<Clip>, public IContainer<Clip>
{
    static bool _showClipInfo;

    std::map<int, Component*> _mapComponent;

    // Dyamic additional variable for the Clip !
    std::map<std::string, int> _mapNumber;
    std::map<std::string, std::string> _mapString;

    std::map<std::string, Vec2D> _mapCollidePoint; // map of Collide Point of Clip
    std::map<std::string, Rect> _mapCollideRect; // map of Collide Rect of Clip

    static void showClipInfo()
    {
        Clip::_showClipInfo = true;
    }
    static void hideClipInfo()
    {
        Clip::_showClipInfo = false;
    }

    static Clip *cloneOf(Clip *original, std::string name = "")
    {

        if (nullptr != original)
        {
            Clip *clone = new Clip(*original);

            if (name == "")
                clone->_name = original->_name;
            else
                clone->_name = name;

            //mlog ("--- Begin deep copy ---\n");

            clone->_mapComponent.clear();

            if (!original->_mapComponent.empty())
            {
                std::map<int,Component*>::const_iterator it = original->_mapComponent.begin();

                while (it != original->_mapComponent.end())
                {
                    //clone->_mapComponent[it->first] = new Component(*(it->second));
                    clone->_mapComponent[it->first] = (*(it->second)).clone();
                    // Important Clone Component attached to Clone Clip
                    clone->_mapComponent[it->first]->_clip = clone;
                    ++it;
                }
            }
            else
            {
                mlog("Deep Copy Failed : "+original->_name+" -> "+clone->_name +" \n");
            }
            return clone;
        }
        else
        {
            mlog("cloneOf error : original don't exist ! \n");
            return nullptr;
        }


    }

//    Clip *setRect(Rect rect)
//    {
//        _rect = rect;
//        return this;
//    }

    Clip *setup(
        std::shared_ptr<Window> window,
        ALLEGRO_FONT *font,
        bool isPlay = true,
        bool isVisible = true)
    {
        _window = window;
        _font = font;
        _isPlay = isPlay;
        _isVisible = isVisible;

        return this;
    }

    Clip(std::string name = ""):
        IPlayable(name)
    {
        _mapComponent.clear();
        if (nullptr != _parent)
        {
            _window    = _parent->_window;
            _font      = _parent->_font;
            _isPlay    = _parent->_isPlay;
            _isVisible = _parent->_isVisible;
        }
        //mlog("- Clip created !\n");
    }

    virtual ~Clip()
    {
        std::map<int,Component*>::iterator it = _mapComponent.begin();

        if (!_mapComponent.empty())
        {
            while (it != _mapComponent.end())
            {
                if (it->second != nullptr)
                {
                    //mlog ("- Delete Component:"+ std::to_string(it->second->_type) + " of Clip: " + _name + "\n");
                    delete it->second;
                    it->second = nullptr;
                }

                ++it;
            }
            _mapComponent.clear();
        }

        _mapNumber.clear();
        _mapString.clear();

        //mlog("- Delete Clip: " + _name + "\n");
    }

    static void destroy(Clip** clip)
    {
        if (nullptr != *clip)
            delete *clip;
        *clip = nullptr;
    }

    Clip *setPosition(int x = 0, int y = 0, int z = 0)
    {
        _x = x;
        _y = y;
        _z = z;

        updateRect();

        return this;
    }

    Clip *parent()
    {
        return _parent;
    }

    Clip *setParent(Clip *parent)
    {
        _parent = parent;
        return this;
    }

    Clip *appendTo(Clip *parent)
    {
        if (nullptr != parent)
        {
            setParent(parent);
            _parent->add(this);

            this->setup
            (
                _parent->_window,
                _parent->_font,
                _parent->_isPlay,
                _parent->_isVisible
            );
        }
        return this;
    }

    Clip *moveTo(Clip *newParent)
    {
        if (nullptr != newParent)
        {
            Clip *oldParent = this->_parent;
            cloneOf(this,this->name())
            ->appendTo(newParent);
            oldParent->del(this->id());
        }
        return this;
    }

    Clip* attach(Component* component)
    {
        component->_clip = this;
        _mapComponent[component->_type] = component;
        return this;
    }

    Clip* detach(int type)
    {
        if (_mapComponent[type] != nullptr)
            delete _mapComponent[type];
        _mapComponent.erase(type);
        return this;
    }

    template <class COMPONENT>
    COMPONENT *get()
    {
        COMPONENT component;
        //return static_cast<COMPONENT*>(_mapComponent[component._type]);
        return static_cast<COMPONENT*>(_mapComponent[component._type]);
        //return new COMPONENT();
    }

    void updateRect()
    {
        // For determinate relative & absolute Clip position !
        if (nullptr != _parent)
        {
            _rect._x = _x - _oX + _parent->_rect._x;
            _rect._y = _y - _oY + _parent->_rect._y;
        }
        else
        {
            _rect._x = _x - _oX;
            _rect._y = _y - _oY;
        }
    }

    void update()
    {

        updateRect();

        // Oder is VERY IMPORTANT for avoid SEG FAULT

        // (1) update CLIP
        if (_update != nullptr)
            _update(this);
        else
            mlog("- " + _name + " update() not defined !\n");

        // Check if have SUB CLIP !
        if (numActiveObject() > 0)
        {
            // (2) update SUB CLIP
            if (!_vecObject.empty())
            {
                for (auto & it: _vecObject)
                {
                    if (it != nullptr)
                            it->update();

                }
            }
        }

        _message = nullptr;

    }

    void render()
    {

        if (_render != nullptr && _isVisible)
            _render(this);
        else
            mlog("- " + _name + " render() not defined !\n");


        // Check if have SUB CLIP !
        if (numActiveObject() > 0)
        {
            // (3) sort SUB CLIP by Z order
            sortZIndex(_vecObject, _vecZIndex);

            if (!_vecObject.empty())
            {
                for (unsigned index = 0; index < _vecObject.size(); ++index)
                {
                    if (index < _vecZIndex.size())
                        if (_vecObject[zIndex(index)] != nullptr)
                                _vecObject[zIndex(index)]->render();
                }
            }
        }

        // (2) render SUB CLIP
//        if (!_vecObject.empty())
//        {
//            for (auto & it: _vecObject)
//            {
//                if (it != nullptr)
//                        it->render();
//
//            }
//        }

    }

    Clip *setX(VAR x)
    {
        _x = x;
        updateRect();
        return this;
    }

    Clip *setY(VAR y)
    {
        _y = y;
        updateRect();
        return this;
    }

    Clip *setZ(VAR z)
    {
        _z = z;
        return this;
    }

    Clip *setPivotX(VAR x)
    {
        _oX = x;
        updateRect();
        return this;
    }

    Clip *setPivotY(VAR y)
    {
        _oY = y;
        updateRect();
        return this;
    }

    Clip *setPivot(VAR x, VAR y)
    {
        setPivotX(x);
        setPivotY(y);
        return this;
    }

    Clip *showRect(ALLEGRO_COLOR color)
    {
        if (Clip::_showClipInfo)
        // Draw the Clip rect
        al_draw_rectangle
        (
            .5+_rect._x, .5+_rect._y,
            .5+_rect._x+_rect._w-1, .5+_rect._y+_rect._h-1,
            color,0
        );
        return this;
    }

    Clip *showPivot(ALLEGRO_COLOR color, float r)
    {
        if (Clip::_showClipInfo)
         // Draw the Pivot
        al_draw_filled_circle
        (
            .5+_rect._x+_oX, .5+_rect._y+_oY, .5+r,
            color
        );
        return this;
    }

    Clip *showInfo(ALLEGRO_COLOR color)
    {
        if (Clip::_showClipInfo)
        // Draw the Name a Top Left of rect
        if (nullptr != _font)
            al_draw_textf
            (
                _font,
                color,
                _rect._x, _rect._y - 14,
                0,
                "%s : Abs = %f,%f : Rel = %f,%f : Frame = %i ",
                _name.c_str(),
                absX(), absY(),
                _x, _y,
                _currentFrame
            );
        return this;
    }

    Clip* setNumber(std::string name, float value)
    {
        _mapNumber[name] = value;
        return this;
    }
    Clip* setString(std::string name, std::string value)
    {
        _mapString[name] = value;
        return this;
    }

    Clip* setCollidePoint(std::string name, Vec2D point)
    {
        _mapCollidePoint[name] = point;
        return this;
    }
    Clip* setCollideRect(std::string name, Rect rect)
    {
        _mapCollideRect[name] = rect;
        return this;
    }


    int getNumber(std::string name)
    {
        return _mapNumber["name"];
    }

    std::string getString(std::string name)
    {
        return _mapString["name"];
    }

};

#endif // CLIP_H_INCLUDED
