//
// Created by Wouter on 4/03/2019.
//

#ifndef OEFENING1_SDLCAR_H
#define OEFENING1_SDLCAR_H


#include "../Car.h"
#include "SDL2/SDL.h"
#include "../../Factories/SDL/SDLFactory.h"

// SDL Child class van Car.

class SDLCar : public Car{
public:
    // Constructor en destructor.
    SDLCar();
    SDLCar(SDLFactory* a);
    SDLCar(const SDLCar& s);
    ~SDLCar();
    // Steek sprite in de renderbuffer of haal deze eruit.
    void visualize();
    void devisualize();
    // Laadt de sprite media en steek deze in een texture.
    void loadMedia();

private:
    // De SDL factory en surfaces/textures voor het renderen.
    SDLFactory* f;
    SDL_Surface* surf;
    SDL_Surface* shieldSurf;
    SDL_Texture* texture;
    SDL_Texture* shieldTexture;

    // De array voor RGB componenten van de sprites, voor het regenboogeffect.
    int rgbColour[3];
    int incColour=1;
    int decColour=0;
    // Oorspronkelijke RGB componenten worden hierin opgeslagen.
    Uint8 r=0;
    Uint8 g=0;
    Uint8 b=0;

};


#endif //OEFENING1_SDLCAR_H
