//
// Created by jacob on 23/03/2019.
//

#ifndef OEFENING1_SDLENEMISSILE_H
#define OEFENING1_SDLENEMISSILE_H

#include "../../Factories/SDL/SDLFactory.h"
#include "../EneMissile.h"

// SDL Child class van EneMissile.

class SDLEneMissile : public EneMissile{
public:
    // Constructor en destructor.
    SDLEneMissile();
    SDLEneMissile(SDLFactory* a);
    SDLEneMissile(const SDLEneMissile& s);
    ~SDLEneMissile();
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

};


#endif //OEFENING1_SDLENEMISSILE_H
