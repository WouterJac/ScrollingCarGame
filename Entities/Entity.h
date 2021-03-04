// 
//  Created by jacob on 18/03/2019.
// 

#ifndef OEFENING1_ENTITY_H
#define OEFENING1_ENTITY_H


#include <SDL_events.h>
#include <string>
#include "../Event/Event.h"

using namespace std;

class Entity {
public:
    //Constructor en destructor
    Entity();
    Entity(const Entity& c);
    virtual ~Entity();
    // Brengt de sprites naar de renderbuffer.
    virtual void visualize()=0;
    // Free de surface.
    virtual void devisualize()=0;
    // Handle de user input.
    virtual void handleEvent(Event inp)=0;
    // Load de sprite textures.
    virtual void loadMedia()=0;
    // Set positie en snelheid van entity
    void setPos(int x,int y);
    void setVel(int x,int y);
    // Beweeg de entity.
    virtual void move()=0;
    // Setter en checker voor active-flag.
    bool isActive();
    void setActive(bool b);
    // Check of er collision is met Entity en.
    bool checkColl(Entity* en);
    // Get de ID.
    string getId();
    // Setters voor spritepath, id, power en animatie.
    void setSpritePath(string path);
    void setId(string id);
    void setPower(string pow);
    void setAnimated(string path, int num);

    // Dimensies, powerup, active flag.
    int SPRITE_WIDTH;
    int SPRITE_HEIGHT;
    bool active=true;
    string power;
    bool shot=false;
    bool hasShot();

    // Positie en snelheid.
    int mPosX, mPosY;
    int mVelX, mVelY;
    // Max snelheid.
    static const int CAR_VEL = 6;

    // Logische schermdimensies.
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;

protected:
    // Spritepath, ID en animatie-info.
    string sprPath;
    string animPath;
    string ID;
    bool animated=false;
    int numAnim =4;

};


#endif // OEFENING1_ENTITY_H
