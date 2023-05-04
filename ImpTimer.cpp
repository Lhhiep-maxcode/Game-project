#include "ImpTimer.h"
#include "Commonfunc.h"

ImpTimer::ImpTimer()
{
    start_tick = 0;
    paused_tick = 0;
    is_paused_ = false;
    is_started_ = false;

}

ImpTimer::~ImpTimer()
{
    //dtor
}

void ImpTimer::start()
{
    is_started_ = true;
    is_paused_ = false;
    start_tick = SDL_GetTicks64();
}

void ImpTimer::stop()
{
    is_paused_ = false;
    is_started_ = false;
}

void ImpTimer::paused()
{
    if(is_started_ == true && is_paused_ == false)
    {
        is_paused_ = true;
        paused_tick = SDL_GetTicks64() - start_tick; //-----------start_tick
                                                     //-----------|1000----------------|sdl_geticks64()1500----------------4500---------|5000
                                                     //  start(=0)|--------------------|paused = 500       ----------1000--------------3500------------
    }
}

void ImpTimer::unpaused()
{
    if(is_paused_ == true)
    {
        is_paused_ = false;
        start_tick = SDL_GetTicks64() - paused_tick; //start mới cách start cũ 1 khoảng (start_tick = start_tick + sdl_getticks1 - sdl_gettick0)
        paused_tick = 0;
    }
}

int ImpTimer::get_ticks()
{
    if(is_started_ == true)
    {
        if(is_paused_ == true)
            return paused_tick;
    }
    else
    {
        return SDL_GetTicks64() - start_tick;
    }
    return 0;
}

bool ImpTimer::is_started()
{
    return is_started_;
}

bool ImpTimer::is_paused()
{
    return is_paused_;
}
