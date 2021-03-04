// 
//  Created by Wouter on 11/03/2019.
// 

#ifndef OEFENING1_ECAR_H
#define OEFENING1_ECAR_H


#include "Car.h"
#include <string>
using namespace std;

// De Enemy Car class.

class ECar : public Entity{
public:
    // Constructor en destructor.
    ECar();
    ECar(const ECar& c);
    virtual ~ECar();
    // Sprite in de renderbuffer steken of eruit halen.
    virtual void visualize()=0;
    virtual void devisualize()=0;
    // Laadt de sprite media naar een texture.
    virtual void loadMedia()=0;
    // Handle de user input.
    void handleEvent(Event inp);
    // Check of de active flag aanstaat.
    bool isActive();


    // Beweeg de auto.
    void move();

};


#endif // OEFENING1_ECAR_H
