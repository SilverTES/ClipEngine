//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#include "Player.h"

Player::Player(std::string name):
_name(name)
{
   mlog("+++ Player "+_name+" \n");
    _life = 100;
    _force = 32;
    _power = 8;
    _controller = new Controller();
}
Player::~Player()
{
    mlog("--- Player "+_name+"\n");
    delete _controller;
}
void Player::setId(int id)
{
    _id = id;
}


Player * Player::getData()
{
    return this;
}
Controller * Player::getController()
{
    return _controller;
}
std::string Player::getName()
{
    return _name;
}


PlayerManager::PlayerManager()
{
    mlog("+++ PlayerManager  \n");
}

PlayerManager::~PlayerManager()
{
    mlog("--- PlayerManager \n");

}

