//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#include "Controller.h"

std::vector<std::string> Controller::SNESButtonDico =
{
    "PAD_UNDEFINED",
    "PAD_START",
    "PAD_SELECT",
    "PAD_UP",
    "PAD_DOWN",
    "PAD_LEFT",
    "PAD_RIGHT",
    "PAD_A","PAD_B","PAD_X","PAD_Y",
    "PAD_L", "PAD_R",
    "MAX_BUTTONS"
};

std::string Controller::getSNESButtonDico(unsigned id)
{
    if (id >= 0 && id<MAX_BUTTONS)
        return SNESButtonDico[id];
    return "PAD_UNDEFINED";
}

int Controller::scanKey()
{
    for (int i(0); i<ALLEGRO_KEY_MAX; i++)
    {
        ALLEGRO_KEYBOARD_STATE keyState;
        al_get_keyboard_state(&keyState);
        if (al_key_down(&keyState ,i)) return i;
    }
    return 0;
}

std::shared_ptr<Button> Controller::getControllerButton(int id)
{
    ALLEGRO_KEYBOARD_STATE keyState;
    for (int i(0); i<ALLEGRO_KEY_MAX; i++)
    {
        al_get_keyboard_state(&keyState);
        if (al_key_down(&keyState,i)) return std::make_shared<Button>(id, i, 0, 0, 0, 0.0f, -1); // -1 evite le conflit avec le button0 du gamepad !
    }

    //ALLEGRO_JOYSTICK_STATE joyState;
    sf::Joystick::update();
    //for (unsigned i(0); i<al_get_num_joysticks(); i++) // All Joysticks
    for (unsigned i(0); i<sf::Joystick::Count; i++) // All Joysticks
    {

        //std::cout << "- Begin joystick get ";
        //al_get_joystick_state(al_get_joystick(i), &joyState);

        if (sf::Joystick::isConnected(i)) // if Joystick connected
        {

            //sf::Joystick::update();

            for (unsigned j(0); j<sf::Joystick::getButtonCount(i); j++) // All Buttons of the Joystick
            //for (unsigned j(0); j<al_get_joystick_num_buttons(al_get_joystick(i)); j++) // All Buttons of the Joystick
            {
                if (sf::Joystick::isButtonPressed(i,j))
                    return std::make_shared<Button>(id, 0, i, 0, 0, 0.0f, j);
                //if (joyState.button[j])
            }


    //        for (int k(0); k<al_get_joystick_num_sticks(al_get_joystick(i)); k++) // All Sticks of the Joystick
    //        {
    //            for (int l(0); l<al_get_joystick_num_axes(al_get_joystick(i),k); l++) // All Axis of the Joystick
    //            {
    //
    //                if (joyState.stick[k].axis[l])
    //                    return std::make_shared<Button>(id, 0, i, k, l, joyState.stick[k].axis[l], -1); // -1 evite le conflit avec le button0 du gamepad !
    //
    //
    //            }
    //        }
    //

            for (unsigned l(0); l<sf::Joystick::AxisCount; l++ )
            {
                if (sf::Joystick::hasAxis(i, sf::Joystick::Axis(l))) // if Axis l exist !
                {
                    //float direction(0)
                    if ( sf::Joystick::getAxisPosition(i,sf::Joystick::Axis(l)) > DEAD_ZONE ||
                         sf::Joystick::getAxisPosition(i,sf::Joystick::Axis(l)) < -DEAD_ZONE )
                    {
                            return std::make_shared<Button>(id, 0, i, 0, l, sf::Joystick::getAxisPosition(i,sf::Joystick::Axis(l)), -1); // -1 evite le conflit avec le button0 du gamepad !

                    }

                }
            }

        }




    }

    return 0;
}

void Controller::assignButton (PlayerManager &playerManager, int player, int id, std::function<void(int, int)> run) // Fonction bloquante , wait KEY or JOY inputs
{

    std::cout << " > Assign "<< SNESButtonDico[id]  << " Button < ";
    while (1)
    {
        std::shared_ptr<Button> button  = getControllerButton(id);
        if ( button != 0)
        {
            playerManager.index(player)->getController()->addButton(id, button);
            break;
        }

        run(player, id);

    }
    //al_rest(1.0);
    std::cout << " * OK * \n";
    while(playerManager.index(player)->getController()->getButton(id))
    {
        sf::Joystick::update();
    }

}

void Controller::mapButton(Player *mapPlayer, int idButton)
{
    mapPlayer->getController()->_isAssignButton = true;
    mapPlayer->getController()->_isAssignButtonOK = false;
    mapPlayer->getController()->_mapPlayer = mapPlayer;
    mapPlayer->getController()->_mapIdButton = idButton;
}

void Controller::pollButton()
{

    if (_mapPlayer != nullptr)
        if (_mapPlayer->getController()->_isAssignButton)
        {

            if (!_mapPlayer->getController()->_isAssignButtonOK)
            {
                std::shared_ptr<Button> buttonMap  = getControllerButton(_mapPlayer->getController()->_mapIdButton);
                if ( buttonMap != 0)
                {
                    _mapPlayer->getController()->addButton(_mapPlayer->getController()->_mapIdButton, buttonMap);
                    _mapPlayer->getController()->_isAssignButtonOK = true;
                }
            }
            else
            {
                sf::Joystick::update();
                if(!_mapPlayer->getController()->getButton(_mapPlayer->getController()->_mapIdButton))
                {
                    _mapPlayer->getController()->_isAssignButton = false;
                    _mapPlayer->getController()->_isAssignButtonOK = false;
                }
            }
        }
}

Player* Controller::mapPlayer()
{
    return _mapPlayer;
}

int Controller::mapIdButton()
{
    return _mapIdButton;
}

bool Controller::isAssignButton()
{
    return _isAssignButton;
}

bool Controller::isAssignButtonOK()
{
    return _isAssignButtonOK;
}

void Controller::showGamePadInfo (int index)
{
    std::cout << "-------------------------------------\n";
    std::cout << "- GamePad : " << index << " \n";
    std::cout << "-------------------------------------\n";
    std::cout << "- Num Stick   = " << al_get_joystick_num_sticks(al_get_joystick(index)) << " \n";
    std::cout << "- Num Buttons = " << al_get_joystick_num_buttons(al_get_joystick(index)) << " \n";

    for (int i(0); i<al_get_joystick_num_buttons(al_get_joystick(index)); i++)
    {
        std::cout << " Button [ " << i << "] = " << al_get_joystick_button_name(al_get_joystick(index),i) << " \n";
    }


    for (int i(0); i< al_get_joystick_num_sticks(al_get_joystick(index)); i++)
    {
        std::cout << " Stick [ " << i << "] = " << al_get_joystick_stick_name(al_get_joystick(index),i) << " \n";

        for (int j(0); j<  al_get_joystick_num_axes(al_get_joystick(index),i); j++)
        {
            std::cout << " Axis [ " << i << "] = " << al_get_joystick_axis_name(al_get_joystick(index),i,j) << " \n";
        }

    }

    std::cout << "-------------------------------------\n";
}
bool Controller::getKey(int keyCode)
{
    al_get_keyboard_state(&_keyState);
    if (al_key_down(&_keyState, keyCode))
        return true;
    return false;
}

Controller::Controller()
{
    for (unsigned i = 1; i< MAX_BUTTONS; i++)
    {
        _arrayButton[i] = std::make_shared<Button>(i,0,0,0,0,0.0f,-1);
    }

//    for (int i(0); i<al_get_num_joysticks(); i++)
//    {
//        _arrayJoystick[i] = al_get_joystick(i);
//    }
    sf::Joystick::update();

    _joystickCount = 0;
    for (unsigned i = 0; i<sf::Joystick::Count; i++)
    {
        if (sf::Joystick::isConnected(i))
            _joystickCount++;
    }
    mlog("+++ Controller \n");

}

Controller::~Controller()
{
//            for (auto & it: _arrayButton)
//            {
//                delete it;
//            }
//    for (int i(0); i<al_get_num_joysticks(); i++)
//    {
//        if (!_arrayButton)
//            delete _arrayJoystick[i];
//    }
//    _arrayJoystick.clear();
    //_arrayButton.empty();
    mlog("--- Controller \n");
}

void Controller::showController() // for Debug !
{
    mlog("*** show Controller *** \n");

    for (unsigned i(1); i< MAX_BUTTONS; i++)
    {
        if (_arrayButton[i]->_id != 0)
        {

            //std::cout << " -/*-+-/-*/ \n";
            std::cout << " id = " << _arrayButton[i]->_id << " :: " ;
            std::cout << " > " << getSNESButtonDico(_arrayButton[i]->_id) << " = "
            << _arrayButton[i]->_idKey << " "
            << _arrayButton[i]->_idJoy << " "
            << _arrayButton[i]->_idStick << " "
            << _arrayButton[i]->_idAxis << " "
            << _arrayButton[i]->_idDirection << " "
            << _arrayButton[i]->_idButton << "\n";

        }
    }
}

void Controller::showAll()
{
    for (int i = 0; i < sf::Joystick::Count; ++i)
    {

        if (sf::Joystick::isConnected(i))
        {
            sf::Joystick::Identification joyInfo = sf::Joystick::getIdentification(i);
            std::cout << "Joystick "<< i << " : " << sf::Joystick::isConnected(i);
            std::cout << " : " << static_cast<std::string>(joyInfo.name) << "\n";
        }

    }
}


void Controller::addButton(int id, int idKey, int idJoy, int id_stick, int idAxis, float idDirection, int idButton)
{
    _arrayButton[id] = std::make_shared<Button>(id, idKey, idJoy, id_stick, idAxis, idDirection, idButton);
}

void Controller::addButton(int id, std::shared_ptr<Button> button)
{
    _arrayButton[id] = button;
}

void Controller::setButton(int id, bool pressed)
{
    _arrayButton[id]->_isPressed = pressed;
}

int Controller::getButton(int id)
{

    if ( _arrayButton[id]->_isPressed )
    {
        _arrayButton[id]->_isPressed = false;
        return 1;
    }
    // Check Keyboard !

    //al_get_keyboard_state(&_keyState);
    if (getKey(_arrayButton[id]->_idKey))
        return 1;


    // Check Joystick Button !
//    if (al_get_num_joysticks()>0) // test si y a des manettes de branché si il y en as pas ça risque de planté si on utilise les fonction joystick allegro !!!
//    {

        //ALLEGRO_JOYSTICK_STATE joyState;
//        al_get_joystick_state(_arrayJoystick[_arrayButton[id]->_idJoy], &_joyState);
//
//        if (_arrayButton[id]->_idButton >= 0) // Evite conflit avec le bouton [-1] == bouton [0] ! Sinon tout les boutons (initialisé à -1) sont considéré comme bouton[0]
//            if (_joyState.button[_arrayButton[id]->_idButton])
//                return 1;


        // Check Joystick Stick !
//        if (_arrayButton[id]->_idDirection > 0)
//            if (_joyState.stick[_arrayButton[id]->_idStick].axis[_arrayButton[id]->_idAxis] > 0)
//                return 1;
//
//        if (_arrayButton[id]->_idDirection < 0)
//            if (_joyState.stick[_arrayButton[id]->_idStick].axis[_arrayButton[id]->_idAxis] < 0)
//                return 1;



        //SFML Joystick
        //sf::Joystick::update();
    if (getNumJoystick() > 0)
    {

        if (_arrayButton[id]->_idButton >= 0)
            if (sf::Joystick::isButtonPressed(_arrayButton[id]->_idJoy, _arrayButton[id]->_idButton))
                return 1;


        if (_arrayButton[id]->_idDirection > 0)
            if ( sf::Joystick::getAxisPosition(_arrayButton[id]->_idJoy, sf::Joystick::Axis(_arrayButton[id]->_idAxis)) > DEAD_ZONE )
                return 1;

        if (_arrayButton[id]->_idDirection < 0)
            if ( sf::Joystick::getAxisPosition(_arrayButton[id]->_idJoy, sf::Joystick::Axis(_arrayButton[id]->_idAxis)) < -DEAD_ZONE )
                return 1;


    }
//    }


    return 0;
}

void Controller::pollJoystick()
{
//    for (int i(0); i<al_get_num_joysticks()-1; i++)
//    {
//        al_get_joystick_state(_arrayJoystick[i], &_joyState);
//    }

    // GamePAD input SFML!
    if (getNumJoystick() > 0)
    {
        sf::Joystick::update();
    }

}

int Controller::getNumJoystick()
{
    return _joystickCount;
}







