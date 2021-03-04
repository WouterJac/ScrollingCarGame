// 
//  Created by jacob on 23/03/2019.
// 

#include "SDLEneMissile.h"
#include <iostream>
using namespace std;


SDLEneMissile::SDLEneMissile() : EneMissile() {

}

SDLEneMissile::SDLEneMissile(SDLFactory *a) {
    f = a;
    SPRITE_WIDTH=8;
    SPRITE_HEIGHT=32;
    SCREEN_WIDTH=f->SCREEN_WIDTH;        // Zet beginparameters klaar.
    SCREEN_HEIGHT=f->SCREEN_HEIGHT;
    sprPath="resources/cars/EneMissile.png";
    loadMedia();        // Deze functie load de sprites.

}

SDLEneMissile::~SDLEneMissile() {
    f = NULL;
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );  // Destructor.
        texture = NULL;
        SPRITE_WIDTH = 0;
        SPRITE_HEIGHT = 0;
    }
}

void SDLEneMissile::visualize() {
    SDL_Rect renderQuad = { mPosX, mPosY, SPRITE_WIDTH, SPRITE_HEIGHT };    // In dit vierkant wordt gevisualiseerd.

    // Render to screen
    SDL_RenderCopy( f->renderer, texture,NULL,&renderQuad); // Breng texture naar het scherm.
}

void SDLEneMissile::devisualize() {
    // SDL_FreeSurface(surf);
}

void SDLEneMissile::loadMedia() {
    surf = IMG_Load(sprPath.c_str());   // Maakt surfaces aan voor missile.
    if( surf == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "boxCarPl2.jpg", IMG_GetError() );
    }
    SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xFF, 0xFF, 0xFF ) ); // Vervang wit door transparant.
    texture = SDL_CreateTextureFromSurface(f->renderer,surf);   //  
    SDL_FreeSurface(surf);
}