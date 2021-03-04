// 
//  Created by Wouter on 11/03/2019.
// 

#ifndef OEFENING1_SDLECAR_H
#define OEFENING1_SDLECAR_H


#include "../ECar.h"
#include "../../Factories/SDL/SDLFactory.h"

// SDL Child class van ECar.

class SDLECar : public ECar{
public:
    // Constructor en destructor.
    SDLECar();
    SDLECar(SDLFactory* a);
    SDLECar(const SDLECar& s);
    ~SDLECar();
    // Steek sprite in de renderbuffer of haal deze eruit.
    void visualize();
    void devisualize();
    // Laadt de sprite media en steek deze in een texture.
    void loadMedia();
private:
    // De SDL factory en surface/texture voor het renderen.
    SDLFactory* f;
    SDL_Surface* surf;
    SDL_Texture* texture;
    // Texture array voor geanimeerde textures (bijvoorbeeld de voetganger).
    SDL_Texture* animTextures[10];
    // Huidig animatie-frame en de animatie-load flag.
    int currentFrame=0;
    bool animLoad=false;

};


#endif // OEFENING1_SDLECAR_H
