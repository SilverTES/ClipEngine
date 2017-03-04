//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#include "Framerate.h"

Framerate::Framerate(ALLEGRO_EVENT_QUEUE * eventQueue, int framerate)
{
    _prevTime = 0;
    _restTime = 0;
    _currentTime = 0;

    _framerate = framerate;
    _framerateTimer = al_create_timer(1.000/_framerate);

    al_register_event_source (eventQueue,al_get_timer_event_source(_framerateTimer));
    al_start_timer(_framerateTimer);
}

Framerate::~Framerate()
{
    if (_framerateTimer) al_destroy_timer(_framerateTimer);
}

//------------------------------------------------------------------------------ Framerate
void Framerate::pollFramerate()
{
    _gameTime = al_get_time();
    if (_gameTime - _oldTime >= 1.0)
    {
        _nbFps = _nbFrame / (_gameTime - _oldTime) ;
        _nbFrame = 1;
        _oldTime = _gameTime;
    }
    _nbFrame ++;
}
int Framerate::getFramerate() const
{
    return _nbFps;
}

