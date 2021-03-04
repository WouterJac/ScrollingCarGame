// 
//  Created by Wouter on 25/03/2019.
// 

#include "Object.h"

Object::Object() : Entity(){
    // Init de velocity en ID.
    mVelX = 0;
    mVelY= 4;
    ID = "Obj";
}

Object::~Object(){

}

void Object::move() {
    mPosX += mVelX; // Het object wordt verplaatst op basis van de velocity.

    if( ( mPosX < 0 ) || ( mPosX + (SPRITE_WIDTH) > SCREEN_WIDTH ))
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if(  ( mPosY > SCREEN_HEIGHT ) )
    {
        active=false;   // Indien het object buiten de rand komt, wordt deze inactief.
    }

}

void Object::handleEvent(Event inp) {
    // Objecten reageren niet op userinput.
}

