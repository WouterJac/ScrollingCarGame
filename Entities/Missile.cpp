// 
//  Created by jacob on 23/03/2019.
// 

#include "Missile.h"

Missile::Missile() : Entity() {

    // Initialize de velocity en ID.
    mVelX = 0;
    mVelY = -6;
    ID = "Missile";
}

Missile::~Missile() {

}


void Missile::move() {
    mPosX += mVelX; // De missile wordt verplaatst op basis van de velocity.



    if( ( mPosX < 0 ) || ( mPosX + (SPRITE_WIDTH) > SCREEN_WIDTH ))
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if( ( mPosY < 0 ) || ( mPosY > SCREEN_HEIGHT ) )
    {
        active=false;   // Indien hij buiten de rand komt, wordt deze inactief.
    }

}

void Missile::handleEvent(Event inp) {
    // Missiles reageren niet op userinput, aangezien ze dan reeds gespawnd zijn.
}