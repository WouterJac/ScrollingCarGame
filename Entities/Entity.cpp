// 
//  Created by jacob on 18/03/2019.
// 

#include "Entity.h"

Entity::Entity() {

}


Entity::~Entity() {

}


void Entity::setPos(int x, int y) {
    mPosY=y;        // Verplaats deze entity naar positie x,y.
    mPosX=x;
}

bool Entity::checkColl(Entity *en) {

    int leftA, leftB;
    int rightA, rightB;         // Deze functie handlet de collision detection.
    int topA, topB;             // Hierbij wordt gekeken of de entity een andere entity (en) aanraakt.
    int bottomA, bottomB;

    leftA = mPosX;
    rightA = mPosX + SPRITE_WIDTH;     // De hitbox van de eigen entity wordt hier ingesteld.
    topA = mPosY;
    bottomA = mPosY + SPRITE_HEIGHT;

    leftB = en->mPosX;
    rightB = en->mPosX + en->SPRITE_WIDTH;      // De hitbox van de doorgegeven enemy wordt ingesteld.
    topB = en->mPosY;
    bottomB = en->mPosY + en->SPRITE_HEIGHT;


    if( rightA <= leftB )   // Indien de rechterzijde van de entity, links van de linkerzijde van.
    {                       // de andere entity ligt, is er geen collision. -> return false.
        return false;
    }

    if( leftA >= rightB )   // Zelfde logica voor de 3 andere zijden.
    {
        return false;
    }

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }


    return true;        // Indien geen enkele van de zijden aan deze no-collisionlogica voldoet.
                        // Is er wel een collision? -> true.
}

void Entity::setActive(bool b) {
    active=b;   // Zet de active flag op de meegegeven paramater.
}

bool Entity::isActive() {
    return active;      // Return de active flag.
}

void Entity::setVel(int x,int y){
    mVelX=x;
    mVelY=y;    // Stel de velocity in op x,y.
}

string Entity::getId(){
    return ID;  // Return de ID.
}

void Entity::setId(string id){
    ID=id;      // Stel de ID in.
}

void Entity::setSpritePath(string path) {
    sprPath= path;
    loadMedia();    // Verander het spritepath, hierdoor moeten de textures opnieuw aangemaakt worden.
}

void Entity::setPower(string pow){
    power = pow;    // Stel de powerup in.
}

bool Entity::hasShot(){
    return shot;    // Return of de auto nog missiles heeft om te vuren.
}


void Entity::setAnimated(string path,int num) {
    if(num==-1){
        animated=false;     // Indien -1 wordt doorgeven als num, is deze entity niet langer geanimeerd.
        sprPath=path;
        numAnim=0;  // Het spritepath wordt dan vervangen door het doorgegeven path, en textures opnieuw geladen.
        loadMedia();
    }
    else {
        animated = true;
        sprPath = path;     // Het spritepath wordt dan vervangen door het doorgegeven path, en textures opnieuw geladen.
        numAnim = num;      // Het aantal animatie-sprites.
        loadMedia();
    }
}


