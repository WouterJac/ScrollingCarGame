// 
//  Created by Wouter on 11/03/2019.
// 

#include "ECar.h"
#include <iostream>
#include <string>

using namespace std;

ECar::ECar() : Entity() {

    // Initialize de velocity.
    mVelX = 0;
    mVelY = 8;
    ID = "ECar";

}

ECar::~ECar() {

}

void ECar::handleEvent(Event inp) {
    // Enemies moeten niets doen met user input.
}




void ECar::move() {
    mPosX += mVelX;                 // De auto wordt verplaatst op basis van de velocity.

    if( ( mPosX < 0 ) || ( mPosX  > SCREEN_WIDTH ))
    {
        active = false;
    }

    mPosY += mVelY;

    if(  ( mPosY > SCREEN_HEIGHT ) )
    {
        active=false;   // Indien de enemy auto onderaan het beeld wegrijdt, zal deze inactief worden en verdwijnen.
    }
}

