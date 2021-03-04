//
// Created by Wouter on 4/03/2019.
// Majority of the code in this class is based on a tutorial by LazyFoo.
//

#include "LTimer.h"

LTimer::LTimer()
{
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}

LTimer::~LTimer() {

}

void LTimer::start()
{
    // Start de timer.
    mStarted = true;

    // Unpause de timer.
    mPaused = false;

    // Stel de huidige clock time in.
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    // Stop de timer.
    mStarted = false;

    // Unpause de timer.
    mPaused = false;

    // Maak ticks leeg.
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    // Als de timer runt en nog niet gepauzeerd is.
    if( mStarted && !mPaused )
    {
        // Pauzeer de timer.
        mPaused = true;

        // Bereken de gepauzeerde ticks.
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    // Als de timer runt en gepauzeerd is.
    if( mStarted && mPaused )
    {
        // Unpause de timer.
        mPaused = false;

        // Reset de starting ticks.
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        // Reset de paused ticks.
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    Uint32 time = 0;

    // Als de timer runt.
    if( mStarted )
    {
        // Indien de timer gepauzeerd is, return pausedticks.
        if( mPaused )
        {
            time = mPausedTicks;
        }
        else
        {
            // Anders return de runnende ticks.
            time = SDL_GetTicks() - mStartTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
    // Timer runt, zegt niets over gepauzeerd of niet.
    return mStarted;
}

bool LTimer::isPaused()
{
    // Timer runt en is gepauzeerd.
    return mPaused && mStarted;
}