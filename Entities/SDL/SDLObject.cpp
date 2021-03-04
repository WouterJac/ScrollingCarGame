// 
//  Created by Wouter on 25/03/2019.
// 

#include "SDLObject.h"
#include <iostream>
using namespace std;


SDLObject::SDLObject() : Object(){

}

SDLObject::SDLObject(SDLFactory* a, string ID) {
    this->ID=ID;
    f = a;
    SPRITE_WIDTH=32;
    SPRITE_HEIGHT=32;
    SCREEN_WIDTH=f->SCREEN_WIDTH;       // Zet beginparameters klaar.
    SCREEN_HEIGHT=f->SCREEN_HEIGHT;
    sprPath="resources/cars/"+ID+".png";    // Sprite path hangt af van het ID van het object.
    loadMedia();        // Deze functie load de sprites.

}

SDLObject::~SDLObject() {

}

void SDLObject::visualize() {
    SDL_Rect renderQuad = { mPosX, mPosY, SPRITE_WIDTH, SPRITE_HEIGHT };    // In dit vierkant wordt gevisualiseerd.

    // Render to screen
    SDL_RenderCopy( f->renderer, texture,NULL,&renderQuad); // Breng texture naar het scherm.
}

void SDLObject::devisualize() {
    // SDL_FreeSurface(surf);
}

void SDLObject::loadMedia() {
    surf = IMG_Load(sprPath.c_str());       // Maakt surfaces aan voor object.
    if( surf == NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", "boxCarPl2.jpg", IMG_GetError() );
    }
    // surf = SDL_LoadBMP( "resources/car.bmp" );
    SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xFF, 0xFF, 0xFF ) ); // Vervang wit door transparant.
    texture = SDL_CreateTextureFromSurface(f->renderer,surf); // Maak de texture aan voor object.
    SDL_FreeSurface(surf);
}

