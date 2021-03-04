//
// Created by Wouter on 4/03/2019.
//

#ifndef OEFENING1_LTIMER_H
#define OEFENING1_LTIMER_H

#include <stdio.h>
#include <SDL2/SDL.h>

class LTimer
{
    public:
		// Constructor en Destructor.
		LTimer();
		virtual ~LTimer();

		// Klokacties.
		void start();
		void stop();
		void pause();
		void unpause();

		// Geeft het aantal ms sinds de start terug (behalve de gepauseerde tijd).
		Uint32 getTicks();

		// Geeft status van de timer weer.
		bool isStarted();
		bool isPaused();

    private:
		// Tijdstip waarop gestart wordt.
		Uint32 mStartTicks;

		// De gepauseerde ticks.
		Uint32 mPausedTicks;

		// De timer-status.
		bool mPaused;
		bool mStarted;
};


#endif //OEFENING1_LTIMER_H
