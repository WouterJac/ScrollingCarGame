// 
//  Created by jacob on 23/03/2019.
// 

#include "EneMissile.h"

EneMissile::EneMissile() : Entity() {

    // Initialize de velocity.
    mVelX = 0;
    mVelY = -4;
    ID = "EneMissile";
}

EneMissile::~EneMissile() {

}


void EneMissile::move() {
    mPosX += mVelX;         // De missile wordt verplaatst op basis van de velocity.

    if( ( mPosX < 0 ) || ( mPosX + (SPRITE_WIDTH) > SCREEN_WIDTH ))
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if( ( mPosY < 0 ) || ( mPosY > SCREEN_HEIGHT ) )
    {
        active=false;       // Indien de missile buiten de rand komt wordt hij inactief en verdwijnt deze.
    }

}

void EneMissile::handleEvent(Event inp) {
    // Enemy missile doet niets met user input.
}