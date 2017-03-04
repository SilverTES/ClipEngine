//------------------------------------------------------------------------------
//--- MugenEngine
//------------------------------------------------------------------------------

#include "ClipEngine.h"

ClipEngine::ClipEngine()
{
    _quit = false;
    mlog("- MugenEgine Created !\n");
}
ClipEngine::~ClipEngine()
{
    mlog("- MugenEgine Deleted !\n");
}

int ClipEngine::initEngine()
{

    // Initialiaze Allegro5
    if(!al_init())
        return mlog("failed to initialize allegro!\n",1);

    // --- Install All devices
    if (!al_install_audio())
        return mlog("- Unable to install Audio ! \n",1);
    if (!al_install_keyboard())
        return mlog("- Unable to install Keyboard ! \n",1);
    if (!al_install_mouse())
        return mlog("- Unable to install Mouse ! \n",1);

//    if (!al_install_joystick())
//        return log(1,"- Unable to install Joystick ! \n");

    // --- Init All addons
    if (!al_init_primitives_addon())
        return mlog("- Unable to init Primitives Addon ! \n",1);
    if (!al_init_image_addon())
        return mlog("- Unable to init Image Addon ! \n",1);
    if (!al_init_font_addon())
        return mlog("- Unable to init Font Addon ! \n",1);
    if (!al_init_ttf_addon())
        return mlog("- Unable to init TTF Addon ! \n",1);
    if (!al_init_acodec_addon())
        return mlog("- Unable to init ACODEC Addon ! \n",1);


    if (!al_reserve_samples(32)) // nombre de son simultannée dans le "Voice" par défaut  [default mixer]
        return mlog("- Unable to reserve samples",1);


    al_set_new_display_flags(ALLEGRO_OPENGL);
    //al_set_new_display_flags(ALLEGRO_DIRECT3D);
    _window = std::make_shared<Window>();

#ifdef SHOW_LOG
    std::cout << "--- PHYSFS version : "<< PHYSFS_VER_MAJOR << "." << PHYSFS_VER_MINOR << "." << PHYSFS_VER_PATCH << "\n";
#endif // SHOW_LOG
    if (!PHYSFS_init(NULL))
        return mlog("- PHYSFS init error !\n",1);


    if(init())
        return mlog("- init Game error !\n",1);

    return mlog("- init MugenEngine OK !\n");
}
int ClipEngine::doneEngine()
{
    if (!PHYSFS_deinit())
        return mlog("- PHYSFS deinit error !\n",1);

    _window->done();

    if(done())
        return mlog("- done Game error !\n",1);

    return mlog("- done MugenEngine OK !\n");
}

int ClipEngine::loopEngine()
{
    while (!_quit)
    {
        update();
        render();
    }

    return mlog("- loop MugenEngine OK !\n");
}


int ClipEngine::run()
{
    if (initEngine())
        return mlog("- init MugenEngine error !\n",1);

    if (loopEngine())
        return mlog("- loop MugenEngine error !\n",2);

    if (doneEngine())
        return mlog("- done MugenEngine error !\n",3);

    return mlog("- run MugenEngine OK !\n");
}




