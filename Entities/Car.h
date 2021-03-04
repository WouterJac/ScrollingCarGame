// 
//  Created by Wouter on 4/03/2019.
// 

#ifndef OEFENING1_CAR_H
#define OEFENING1_CAR_H


#include "Entity.h"
#include "../Event/Event.h"
#include <string>
using namespace std;


class Car : public Entity {
public:
    // Constructor en destructor.
    Car();
    Car(const Car& c);
    virtual ~Car();
    // Steek de sprite in de renderbuffer of haal deze eruit.
    virtual void visualize()=0;
    virtual void devisualize()=0;
    // Handle de user input.
    void handleEvent(Event e);
    // Loadt de sprite-media in een texture.
    virtual void loadMedia()=0;

    // Beweeg de auto.
    void move();
private:
    bool pauseBug=false;    // Down moet komen voor een up, wanneer men uit pauze komt.

};


#endif // OEFENING1_CAR_H
