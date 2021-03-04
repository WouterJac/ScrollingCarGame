// 
//  Created by jacob on 19/03/2019.
// 

#ifndef OEFENING1_SDLBUTTON_H
#define OEFENING1_SDLBUTTON_H


#include "../button.h"
#include "../../Factories/SDL/SDLFactory.h"

class SDLbutton : public button{
public:
    // Constructor en destructor.
    SDLbutton();
    SDLbutton(SDLFactory* a);
    SDLbutton(const SDLbutton& c);
    ~SDLbutton();
    // Steek de knop in de renderbuffer.
    void render();
    // Laadt de knop-media.
    void loadMedia(string path);

private:
    // Pointer naar de sdlfactory om te renderen.
    SDLFactory* f;

    // Surface en texture van de knop.
    SDL_Surface* surf;
    SDL_Texture* texture;

};


#endif // OEFENING1_SDLBUTTON_H
