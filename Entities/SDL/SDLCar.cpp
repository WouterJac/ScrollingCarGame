// 
//  Created by Wouter on 4/03/2019.
// 

#include "SDLCar.h"
#include <iostream>

using namespace std;

SDLCar::SDLCar() : Car() {


}

SDLCar::SDLCar(SDLFactory* a) {
    f = a;
    SPRITE_WIDTH=64;
    SPRITE_HEIGHT=128;
    sprPath="resources/cars/F12.png";       // Zet beginparameters.
    SCREEN_WIDTH=f->SCREEN_WIDTH;
    SCREEN_HEIGHT=f->SCREEN_HEIGHT;
    rgbColour[0] = 255;     // Startkleur voor ster-powerup.
    rgbColour[1] = 100;
    rgbColour[2] = 0;

    loadMedia();    // Deze functie load de sprites.
}

SDLCar::~SDLCar() {
    f = NULL;
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );      // Destructor.
        texture = NULL;
        SPRITE_WIDTH = 0;
        SPRITE_HEIGHT = 0;
    }
}

void SDLCar::loadMedia(){
    surf = IMG_Load(sprPath.c_str());
    shieldSurf = IMG_Load("resources/cars/shieldPower.png");            // Maakt surfaces aan voor auto en shield.
    if( surf == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", sprPath.c_str(), IMG_GetError() );
    }
    if( shieldSurf == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "shieldPower.png", IMG_GetError() );
    }
    SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xFF, 0xFF, 0xFF ) );     // Verwijdert wit en vervangt dit door transparant.
    texture = SDL_CreateTextureFromSurface(f->renderer,surf);
    shieldTexture = SDL_CreateTextureFromSurface(f->renderer,shieldSurf);

    SDL_GetTextureColorMod(texture,&r,&g,&b);            // Behoudt oorspronkelijke kleuroffset om naar terug te keren bij ster-powerup.

    SDL_FreeSurface(surf);
    SDL_FreeSurface(shieldSurf);
}

void SDLCar::visualize() {

    SDL_Rect renderQuad = { mPosX, mPosY, SPRITE_WIDTH, SPRITE_HEIGHT };    // In dit vierkant wordt gevisualiseerd.
    if(power=="None") {
        SDL_SetTextureColorMod(texture, r, g, b);
    }
    // Render to screen
    if (power == "Star") {                  // Indien ster powerup actief is.
        if (rgbColour[decColour] < 5) {
            decColour = decColour == 2 ? 0 : decColour + 1;
            incColour = decColour == 2 ? 0 : decColour + 1;     // Verander de kleursamenstelling lichtjes.
        }
        rgbColour[decColour] -= 4;
        rgbColour[incColour] += 4;
        SDL_SetTextureColorMod(texture, rgbColour[0], rgbColour[1], rgbColour[2]);       // Verander de sprite kleur.
    }

    SDL_RenderCopy(f->renderer, texture, NULL, &renderQuad);        // Render de auto.


    if(power == "Shield"){
        SDL_RenderCopy(f->renderer,shieldTexture,NULL,&renderQuad); // Indien shield powerup -> Render shield bovenop de auto.
    }



}

void SDLCar::devisualize(){
    SDL_DestroyTexture(texture);
}


