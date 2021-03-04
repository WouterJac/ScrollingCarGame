// 
//  Created by Wouter on 4/03/2019.
// 

#ifndef OEFENING1_AFACTORY_H
#define OEFENING1_AFACTORY_H
#include "../Entities/Car.h"
#include "string"
#include "../Entities/ECar.h"
#include "../MenuElements/button.h"
#include "../Music/MusicPlayer.h"
#include "../Entities/Missile.h"
#include "../Entities/EneMissile.h"
#include "../Entities/Object.h"

// Parent van SDLFactory.

class AFactory {
public:
    // Constructor en destructor.
    AFactory();
    AFactory(const AFactory& a );
    virtual ~AFactory();
    // Maak een SDL versie aan van een klasse, en return deze als pointer van diens logische parent klasse.
    // Maakt gebruik van polymorfisme.
    virtual Entity* createCar()=0;
    virtual Entity* createECar()=0;
    virtual button* createButton()=0;
    virtual Missile* createMissile()=0;
    virtual EneMissile* createEneMissile()=0;
    virtual Object* createObject(string ID)=0;
    // Zet de modules voor het laden van images etc. klaar.
    virtual int initializeGraphics() =0;
    // Sluit het venster
    virtual int quit()=0;
    // Functies om de renderbuffer te renderen/clearen.
    virtual void renderAll() = 0;
    virtual void renderClear()=0;
    // Pauzeert het renderen.
    virtual void pauseRender(int t) = 0;
    // Laadt het de sprite van het huidige background-path in als backgroudn-texture.
    virtual void loadBG()=0;
    // Rendert text in een bepaalde kleur op positie x,y.
    virtual void renderText(string renderText,string color, int x, int y)=0;
    // Verandert het background-path
    virtual void changeBG(string path)=0;
    // Bepaalt of de achtergrond moet scrollen of niet (scrollen gebeurt enkel in gameview).
    virtual void setScrolling(bool activate)=0;

    int SCREEN_WIDTH;       // Bevat logische venster-dimensies.
    int SCREEN_HEIGHT;
    int scrollspeed=10;

    // Handle windowevents, om bijvoorbeeld te kunnen weergeven wanneer het scherm van grootte verandert.
    virtual void handleWindowEvent(Event event)=0;

    // Render het aantal levens in hartjes.
    virtual void renderLife(int i)=0;
};


#endif // OEFENING1_AFACTORY_H
