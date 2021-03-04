// 
//  Created by jacob on 23/03/2019.
// 

#ifndef OEFENING1_MISSILE_H
#define OEFENING1_MISSILE_H

#include <string>
#include "Entity.h"

using namespace std;


class Missile : public Entity {
public:
    // Constructor en destructor.
    Missile();
    Missile(const Missile& c);
    virtual ~Missile();

    // Brengt de missile-sprites naar de renderbuffer.
    virtual void visualize()=0;
    // Free de surface.
    virtual void devisualize()=0;
    // Handle de user input.
    void handleEvent(Event inp);
    // Load de sprite textures.
    virtual void loadMedia()=0;

    // Move de missile.
    void move();
};


#endif // OEFENING1_MISSILE_H
