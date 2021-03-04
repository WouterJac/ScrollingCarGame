//
// Created by jacob on 18/03/2019.
//

#ifndef OEFENING1_SDLEVENTHANDLER_H
#define OEFENING1_SDLEVENTHANDLER_H


#include "../EventHandler.h"
#include <string>
#include <SDL_events.h>

using namespace std;

class SDLEventHandler : public EventHandler{
public:
    // Constructor en destructor.
    SDLEventHandler();
    SDLEventHandler(const SDLEventHandler& c);
    virtual ~SDLEventHandler();
    // Return een event met de info over user input.
    Event pollForEvent();
    // Maakt het event leeg.
    void clearEvent();

private:
    // SDL event, waarin de userinput terecht komt.
    SDL_Event e;
    // Omzetting naar een niet-SDL logisch event.
    Event ev;
    // Muisoffset.
    int offsetX,offsetY;
};


#endif //OEFENING1_SDLEVENTHANDLER_H
