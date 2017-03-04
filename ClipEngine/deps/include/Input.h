#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include "Misc.h"

namespace Input
{
    struct Mouse
    {
        ALLEGRO_SYSTEM_MOUSE_CURSOR _cursor;

        // Position
        VAR _x = 0;
        VAR _y = 0;
        VAR _prevX = 0;
        VAR _prevY = 0;

        // Button
        int _button = 0;
        bool _isPress = false;

        // Event
        bool _move = false; // mouse is move or not !

        bool _moveUP = false; // mouse is move UP or not !
        bool _moveDOWN = false; // mouse is move DOWN or not !
        bool _moveLEFT = false; // mouse is move LEFT or not !
        bool _moveRIGHT = false; // mouse is move RIGHT or not !

        bool _up = false;   // mouse is up or not !
        bool _down = false; // mouse is down or not !

        // Draggable
        bool _drag = false; // mouse is drag or not !
        bool _reSize = false; // mouse is drag or not !

        void update(VAR mouseX, VAR mouseY,
                    int mouseButton, ALLEGRO_DISPLAY *display)
        {
            _x = mouseX;
            _y = mouseY;
            _move = false;
            _button = mouseButton;

            if (_prevX != _x || _prevY != _y)
            {
                _move = true;

                if (_y < _prevY) _moveUP = true;
                if (_y > _prevY) _moveDOWN = true;
                if (_x < _prevX) _moveLEFT = true;
                if (_x > _prevX) _moveRIGHT = true;

                _prevX = _x;
                _prevY = _y;
            }
            else
            {
                _move = false;
                _moveUP = false;
                _moveDOWN = false;
                _moveLEFT = false;
                _moveRIGHT = false;
            }

            if (_button && !_down)
            {

                _down = true;
                //log("< Mouse DOWN >");
            }

            if (!_button && !_up)
            {

                _up = true;
                //log("< Mouse UP >");
            }

            if (!_button)
            {
                _drag = false;
                _reSize = false;
                _down = false;
                _isPress = false;
            }
            else
            {
                _isPress = true;
                _up = false;
                //log("< Mouse Pressed >");
            }

            al_set_system_mouse_cursor(display, _cursor);
        }
    };

}



#endif // INPUT_H_INCLUDED
