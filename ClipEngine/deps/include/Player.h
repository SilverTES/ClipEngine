//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Controller.h"
#include "IContainer.h"


class Controller;  // Important declaration before include Controller ! avoid compilation error!

struct Player
{
    int _id;
    int _life;
    int _force;
    int _power;
    std::string _name;
    Controller  * _controller;

    Player(std::string name = "");
    virtual ~Player();
    void setId(int id);
    Player * getData();
    Controller * getController();
    std::string getName();

};

class PlayerManager : public IContainer<Player>
{
    public:
        PlayerManager();
        ~PlayerManager();

    protected:
    private:

};

#endif // PLAYER_H_INCLUDED
