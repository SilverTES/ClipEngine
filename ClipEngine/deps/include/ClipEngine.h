//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------
#ifndef CLIPENGINE_H
#define CLIPENGINE_H

//------------------------------------------------------------------------------  Major dependances
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_physfs.h>
#include <physfs.h>
#include <allegro5/allegro_windows.h>
//#include <allegro5/allegro_direct3d.h>

#include <cstdio>
#include <memory>
#include <vector>
#include <deque>

#include <iostream>
#include <functional>
#include <fstream>
#include <cstdlib>
#include <ctime>

//------------------------------------------------------------------------------ Minor Dependances

#include "Window.h"
#include "Misc.h"
#include "Tween.h"
#include "FileData.h"
#include "Input.h"
#include "Controller.h"
#include "Player.h"
#include "Framerate.h"
#include "Message.h"
#include "Collision2D.h"

#include "Clip.h"
#include "BaseComponent.h"
#include "Animation.h"
#include "Asset.h"

class Window;

class ClipEngine
{
    public:
        ClipEngine();
        virtual ~ClipEngine();

        virtual int init() = 0;
        virtual int done() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        int run();

    protected:
        bool _quit;

        // Devices state
        ALLEGRO_MOUSE_STATE _mouseState;
        ALLEGRO_KEYBOARD_STATE _keyState;

        std::shared_ptr<Window> _window;

    private:
        int initEngine();
        int doneEngine();
        int loopEngine();
};
#endif // CLIPENGINE_H
