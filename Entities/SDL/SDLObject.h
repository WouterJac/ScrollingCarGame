//
// Created by Wouter on 25/03/2019.
//

#ifndef OEFENING1_SDLOBJECT_H
#define OEFENING1_SDLOBJECT_H


#include "../Object.h"
#include "../../Factories/SDL/SDLFactory.h"

// SDL child-class van Object.

class SDLObject : public Object {
public:
    // Constructor en destructor.
    SDLObject();
    SDLObject(SDLFactory* a, string ID);
    ~SDLObject();
    // Functies om de sprite in of uit de renderbuffer te steken/halen.
    void visualize();
    void devisualize();
    // Laadt de sprite-media ens teek deze in een texture.
    void loadMedia();

private:
    // De gebruikte SDLFactory om een SDLObject aan te maken.
    SDLFactory* f;
    // Sprite surface en texture.
    SDL_Surface* surf;
    SDL_Texture* texture;
};


#endif //OEFENING1_SDLOBJECT_H
