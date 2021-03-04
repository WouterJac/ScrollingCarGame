// 
//  Created by jacob on 23/03/2019.
// 

#include "SDLMissile.h"
#include <iostream>
using namespace std;


SDLMissile::SDLMissile() : Missile() {

}

SDLMissile::SDLMissile(SDLFactory* a) {
    f = a;
    SPRITE_WIDTH=8;
    SPRITE_HEIGHT=32;
    SCREEN_WIDTH=f->SCREEN_WIDTH;   // Zet beginparameters klaar
    SCREEN_HEIGHT=f->SCREEN_HEIGHT;
    sprPath="resources/cars/Missile.png";
    loadMedia();        // Deze functie load de sprites

}

SDLMissile::~SDLMissile() {
    f = NULL;
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );  // Destructor.
        texture = NULL;
        SPRITE_WIDTH = 0;
        SPRITE_HEIGHT = 0;
    }

}

void SDLMissile::visualize() {
    SDL_Rect renderQuad = { mPosX, mPosY, SPRITE_WIDTH, SPRITE_HEIGHT };    // In dit vierkant wordt gevisualiseerd.

    // Render to screen.
    SDL_RenderCopy( f->renderer, texture,NULL,&renderQuad); // Render texture naar het scherm.
}

void SDLMissile::devisualize() {
    // SDL_FreeSurface(surf);
}

void SDLMissile::loadMedia() {
    // SDL_FreeSurface(surf);
    surf = IMG_Load(sprPath.c_str());       // Maakt surfaces aan voor missile.
    if( surf == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "boxCarPl2.jpg", IMG_GetError() );
    }
    SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xFF, 0xFF, 0xFF ) ); // Vervang wit door transparant.
    texture = SDL_CreateTextureFromSurface(f->renderer,surf);  // Maak de texture aan voor missile.
    SDL_FreeSurface(surf);
}


