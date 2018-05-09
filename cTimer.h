#ifndef CTIMER_H_INCLUDED
#define CTIMER_H_INCLUDED

#include <SDL.h>

class cTimer
{
    public:
        cTimer();

        void start();
        void stop();
        void pause();
        void unpause();

        int getTime();

        bool getIsStarted();
        bool getIsPaused();

    private:
        int startTime;
        int pausedTime;

        bool isPaused;
        bool isStarted;
};

#endif // CTIMER_H_INCLUDED
