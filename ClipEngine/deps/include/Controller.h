//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED

#include <memory>
#include <iostream>

#include <SFML/Window.hpp>

#include "Window.h"
#include "Misc.h"
#include "Player.h"

#define DEAD_ZONE 50

#define KEY_PRESS(key) (al_key_down(&_keyState, key))

int const MAX_JOYSTICK(16);

struct Player;
class PlayerManager;

enum SNESButton
{
    PAD_UNDEFINED = 0,
    PAD_START,
    PAD_SELECT,
    PAD_UP,
    PAD_DOWN,
    PAD_LEFT,
    PAD_RIGHT,
    PAD_A,PAD_B,PAD_X,PAD_Y,
    PAD_L,PAD_R,
    MAX_BUTTONS
};


struct Button
{
	int _id = 0;      // SNESButton enum !
	int _idKey = 0;     // Keyboard Id
	int _idJoy = 0;     // Gamepad Id
	int _idStick = 0;   // Stick of Gamepad Id
	int _idAxis = 0;   // Axis of Stick Id
	float _idDirection = 0; // Direction of the Axis Id
	int _idButton = 0;  // Button of Gamepad Id
	bool _isPressed = false; // if button is pressed !

	Button(int id, int idKey, int idJoy, int idStick, int idAxis, float idDirection, int idButton)
    {
		_id = id;
		_idKey = idKey;
		_idJoy = idJoy;
		_idStick = idStick;
		_idAxis = idAxis;
		_idDirection = idDirection;
		_idButton = idButton;
        //log("+++ Button \n");
    }
    virtual ~Button()
    {
        //log("--- Button \n");
    }



};

//extern std::vector<std::string> SNESButtonDico; // Extern variable return string "PAD_XXXX" by id
//std::string getSNESButtonDico(unsigned id);
//
//extern int scanKey();
//
//extern std::shared_ptr<Button> getControllerButton(int id);
//extern void assignButton (PlayerManager &playerManager, int player, int id, std::function<void(int, int)> run); // Fonction bloquante , wait KEY or JOY inputs
//
//extern void showGamePadInfo (int index);

class Controller
{
    public:
        Controller();

        virtual ~Controller();

        void showController();
        static void showAll();

        void addButton(int id, int idKey, int idJoy, int id_stick, int idAxis, float idDirection, int idButton);
        void addButton(int id, std::shared_ptr<Button> button);
        void setButton(int id, bool pressed);
        int  getButton(int id);

        bool getKey(int keyCode);
        int  getNumJoystick();

        void pollJoystick();

        static std::vector<std::string> SNESButtonDico; // Extern variable return string "PAD_XXXX" by id
        static std::string getSNESButtonDico(unsigned id);

        static int scanKey();
        static void showGamePadInfo (int index);

        static std::shared_ptr<Button> getControllerButton(int id);
        static void assignButton (PlayerManager &playerManager, int player, int id, std::function<void(int, int)> run); // Fonction bloquante , wait KEY or JOY inputs

        static void mapButton(Player *mapPlayer, int idButton);

        void pollButton();

        Player *mapPlayer();

        int mapIdButton();

        bool isAssignButton();
        bool isAssignButtonOK();


    protected:
    private:

        bool _isAssignButton = false;
        bool _isAssignButtonOK = false;
        int _mapIdButton = -1;
        Player *_mapPlayer = nullptr;

        ALLEGRO_KEYBOARD_STATE _keyState;
        std::shared_ptr<Button> _arrayButton[MAX_BUTTONS] = {};

        //ALLEGRO_JOYSTICK_STATE _joyState;
        //ALLEGRO_JOYSTICK * _arrayJoystick[MAX_JOYSTICK] = {NULL};
        int _joystickCount;



};


#endif // CONTROLLER_H_INCLUDED
