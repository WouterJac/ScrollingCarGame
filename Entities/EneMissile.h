// 
//  Created by jacob on 23/03/2019.
// 

#ifndef OEFENING1_ENEMISSILE_H
#define OEFENING1_ENEMISSILE_H

#include <string>
#include "Entity.h"

using namespace std;

// De Enemy Missile class.

class EneMissile : public Entity {
public:
    // Constructor en destructor.
    EneMissile();
    EneMissile(const EneMissile& c);
    virtual ~EneMissile();
    // Sprite in de renderbuffer steken of eruithalen.
    virtual void visualize()=0;
    virtual void devisualize()=0;
    // Handle de user input.
    void handleEvent(Event inp);
    // Load de sprite media.
    virtual void loadMedia()=0;

    // Beweeg de enemy missile.
    void move();
    // Check of deze enemissile actief is.
    bool isActive();
};


#endif // OEFENING1_ENEMISSILE_H
