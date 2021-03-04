// 
//  Created by Wouter on 25/03/2019.
// 

#ifndef OEFENING1_OBJECT_H
#define OEFENING1_OBJECT_H

#include "Entity.h"

using namespace std;

class Object : public Entity{
public:
    // Constructor en destructor.
    Object();
    virtual ~Object();
    // Brengt de object-sprites naar de renderbuffer.
    virtual void visualize()=0;
    // Free de surface.
    virtual void devisualize()=0;
    // Handle de user input.
    void handleEvent(Event inp);
    // Load de sprite textures.
    virtual void loadMedia()=0;

    // Move het object.
    void move();
    // Geeft weer of deze entity actief is.
    bool isActive();
};


#endif // OEFENING1_OBJECT_H
