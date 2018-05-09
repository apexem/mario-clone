#include "cTimer.h"

cTimer::cTimer()
{
    startTime = 0;
    pausedTime = 0;

    isPaused = false;
    isStarted = false;
}

void cTimer::start()
{
    isStarted = true;
    isPaused = false;

    startTime = SDL_GetTicks();
    pausedTime = 0;
}

void cTimer::stop()
{
    isStarted = false;
    isPaused = false;

    startTime = 0;
    pausedTime = 0;
}

void cTimer::pause()
{
    if(isStarted && !isPaused)
    {
        isPaused = true;

        pausedTime = SDL_GetTicks() - startTime;
        startTime = 0;
    }
}

void cTimer::unpause()
{
    if(isStarted && isPaused)
    {
        isPaused = false;
        startTime = SDL_GetTicks() - pausedTime;
        pausedTime = 0;
    }
}

int cTimer::getTime()
{
    int time = 0;

    if(isStarted)
    {
        if(isPaused)
        {
            time = pausedTime;
        }
        else
        {
            time = SDL_GetTicks() - startTime;
        }
    }

    return time;
}

bool cTimer::getIsPaused()
{
    return isPaused && isStarted;
}

bool cTimer::getIsStarted()
{
    return isStarted;
}
