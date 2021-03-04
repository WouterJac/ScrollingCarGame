// 
//  Created by jacob on 18/03/2019.
// 

#ifndef OEFENING1_EVENTHANDLER_H
#define OEFENING1_EVENTHANDLER_H
#include <string>
#include "Event.h"

using namespace std;

// Parent class voor SDLEventhandler.

class EventHandler {
public:
    // Constructor en destructor.
    EventHandler();
    EventHandler(const EventHandler& c);
    virtual ~EventHandler();
    // Return een event met de info over user input.
    virtual Event pollForEvent() = 0;
    // Maakt het event leeg.
    virtual void clearEvent()=0;

};


#endif // OEFENING1_EVENTHANDLER_H
