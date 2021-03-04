// 
//  Created by Wouter on 4/03/2019.
// 

#include "Car.h"
#include <string>
#include "Entity.h"

using namespace std;



Car::Car() : Entity() {

    // Initialize de velocity en ID.
    mVelX = 0;
    mVelY = 0;
    ID = "Car";

}

Car::~Car() {

}


void Car::handleEvent(Event e) {


    if(e.getUpDown()==1){               // De auto krijgt een user event door.
        pauseBug=false;
        string key=e.getKey();
        if(key=="up"){
            mVelY -= CAR_VEL;
        }
        else if(key=="down"){      // Afhankelijk van de gedrukte toets wordt de snelheid aangepast.
            mVelY += CAR_VEL;
        }
        else if(key=="left"){
            mVelX -= CAR_VEL;
        }
        else if(key=="right"){
            mVelX += CAR_VEL;
        }
        else if(key=="p"){
            pauseBug=true;
        }
    }
    else{
        string key=e.getKey();
        if(!pauseBug) {
            if (key == "up") {
                mVelY += CAR_VEL;
            }
            else if (key == "down" ) {      // Afhankelijk van de losgelaten toets wordt de snelheid aangepast.
                mVelY -= CAR_VEL;
            }
            else if (key == "left" ) {
                mVelX += CAR_VEL;
            }
            else if (key == "right") {     // Check voor velX/Y != 0, zo kan een losgelaten toets tijdens pauze de speed niet fout aanpassen.
                mVelX -= CAR_VEL;
            }
        }
    }

    /*// If a key was pressed
    if(inp.length()>4) {
        if (inp[1] == 'd') {    // Key down
            switch (inp[4]) {
                case 'p':
                    if (inp[3] == 'u') {
                        mVelY -= CAR_VEL;
                    }
                    break;
                case 'o': mVelY += CAR_VEL; break;      // Could have checked for the whole string
                case 'e': mVelX -= CAR_VEL; break;      // More efficiency when checking for a char
                case 'i': mVelX += CAR_VEL; break;      // Expects input "kd" or "ku" for key down or key up
                default: break;                         // Followed by a space and then "left", "right, "up", "down", ..
            }
        }
        else if (inp[1] == 'u'){
            switch (inp[4]) {
                case 'p':
                    if (inp[3] == 'u') {
                        mVelY += CAR_VEL;
                    }
                    break;
                case 'o': mVelY -= CAR_VEL; break;
                case 'e': mVelX += CAR_VEL; break;
                case 'i': mVelX -= CAR_VEL; break;
                default: break;
            }
        }
    }*/


}

void Car::move() {


    mPosX += mVelX;

    if( ( mPosX < 0 + 58 ) || ( mPosX + (SPRITE_WIDTH) > SCREEN_WIDTH - 58))  // De auto wordt verplaatst op basis van de velocity.
    {
        mPosX -= mVelX;
    }

    mPosY += mVelY;

    if( ( mPosY < 0 ) || ( mPosY + (SPRITE_HEIGHT) > SCREEN_HEIGHT ) )       // De auto wordt verplaatst op basis van de velocity.
    {                                                                        // Indien hij buiten de rand komt, wordt deze tegengehouden.
        mPosY -= mVelY;
    }

}




