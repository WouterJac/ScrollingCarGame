//
// Created by jacob on 23/03/2019.
//

#ifndef OEFENING1_EMISSILE_H
#define OEFENING1_EMISSILE_H


#include "../Missile.h"
#include "../../Factories/SDL/SDLFactory.h"

// SDL child class van Missile.

class SDLMissile : public Missile{
public:
    // Constructor en destructor.
    SDLMissile();
    SDLMissile(SDLFactory* a);
    SDLMissile(const SDLMissile& s);
    ~SDLMissile();
    // Steek de sprite in de renderbuffer of haal deze eruit.
    void visualize();
    void devisualize();
    // Laadt de media en steek deze in een texture.
    void loadMedia();

private:
    // De SDL factory voor het aanmakken van dit object, en de surface/texture.
    SDLFactory* f;
    SDL_Surface* surf;
    SDL_Texture* texture;

};


#endif //OEFENING1_EMISSILE_H
