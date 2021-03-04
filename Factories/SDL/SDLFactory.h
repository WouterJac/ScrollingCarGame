// 
//  Created by Wouter on 4/03/2019.
// 

#ifndef OEFENING1_SDLFACTORY_H
#define OEFENING1_SDLFACTORY_H


#include "../../Entities/Car.h"
#include "../AFactory.h"
#include "SDL.h"
#include <SDL_image.h>
#include "string"
#include "../../Entities/ECar.h"
#include "../../Music/MusicPlayer.h"
#include "../../Entities/Object.h"
#include <SDL_ttf.h>

class SDLFactory : public AFactory{
public:
    // Constructor en destructor.
    SDLFactory();
    SDLFactory(const SDLFactory& s);
    SDLFactory(int  w, int h);
    virtual ~SDLFactory();

    // Maak een SDL versie aan van een klasse, en return deze als pointer van diens logische parent klasse.
    // Maakt gebruik van polymorfisme.
    Entity* createCar();
    Entity* createECar();
    button* createButton();
    Missile* createMissile();
    EneMissile* createEneMissile();
    Object* createObject(string ID);

    // Zet de modules voor het laden van images etc. klaar.
    int initializeGraphics();
    // Sluit het venster.
    int quit();
    // Functies om de renderbuffer te renderen/clearen.
    void renderAll();
    void renderClear();
    // Pauzeert het renderen.
    void pauseRender(int t);

    // Laadt het de sprite van het huidige background-path in als backgroudn-texture.
    void loadBG();
    // Rendert text in een bepaalde kleur op positie x,y.
    void renderText(string renderText,string color, int x, int y);
    // Verandert het background-path
    void changeBG(string path);
    // Bepaalt of de achtergrond moet scrollen of niet (scrollen gebeurt enkel in gameview).
    void setScrolling(bool activate);
    // Handle windowevents, om bijvoorbeeld te kunnen weergeven wanneer het scherm van grootte verandert.
    void handleWindowEvent(Event event);
    // Render het aantal levens in hartjes.
    void renderLife(int i);

    // Scherm- en renderobject
    SDL_Window* window;
    SDL_Renderer* renderer;

private:
    // Textures en surfaces van background, hearts en text.
    SDL_Surface* BGSurf;
    SDL_Texture* BGTexture;
    SDL_Surface* heartSurf;
    SDL_Texture* heartTexture;
    SDL_Texture* textTexture;

    // Kleur en font voor text.
    TTF_Font* gFont;
    SDL_Color textColor = { 0, 0, 0 ,255};

    // Fullscreen en scroll-variabelen.
    bool mFullScreen = false;
    bool scrolling=false;
    int scrollingOffset=0;

    // Path van de achtergrond.
    string BGpath;

};


#endif // OEFENING1_SDLFACTORY_H
