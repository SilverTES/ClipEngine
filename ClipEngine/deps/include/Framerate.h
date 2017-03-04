//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef FRAMERATE_H
#define FRAMERATE_H

#include <allegro5/allegro.h>

class Framerate
{
    public:
        Framerate(ALLEGRO_EVENT_QUEUE * eventQueue, int framerate);
        virtual ~Framerate();

        // Framerate
        int getFramerate() const;
        void pollFramerate();
        ALLEGRO_EVENT_QUEUE * eventQueue();

    protected:

    private:
        float _prevTime;
        float _restTime;
        float _currentTime;
        float _deltaTime;

        // Framerate control
        float _framerate;
        int _nbFrame;
        int _nbFps;
        double _gameTime;
        double _oldTime;
        ALLEGRO_TIMER* _framerateTimer;
};

#endif // FRAMERATE_H
