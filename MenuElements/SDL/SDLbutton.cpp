// 
//  Created by jacob on 19/03/2019.
// 

#include "SDLbutton.h"
#include "../../Factories/SDL/SDLFactory.h"
#include <iostream>
using namespace std;

SDLbutton::SDLbutton(SDLFactory* a) {
    f=a;
}

SDLbutton::~SDLbutton() {
    if( texture != NULL)
    {
        texture = NULL;     // Destructor.
        width = 0;
        heigth = 0;
        xPos=0;
        yPos=0;
    }
}

void SDLbutton::loadMedia(string path){     // Stelt texture in op basis van path.
    surf = IMG_Load(path.c_str());
    if( surf== NULL )
    {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
    }
    SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xFF, 0xFF, 0xFF ) );
    texture = SDL_CreateTextureFromSurface(f->renderer,surf);                       // Maak een texture van de image in path.
    SDL_FreeSurface(surf);
}


void SDLbutton::render() {
    /*SDL_Rect fillRect = { xPos, yPos, width, heigth };
    SDL_SetRenderDrawColor( f->renderer, 0x00, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( f->renderer, &fillRect );
    SDL_SetRenderDrawColor( f->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    f->renderText(text, "white", xPos,yPos);*/      // Using geometry + text

    // TODO: Render text according to its contents
    // TODO: Beslissen of geometry of image rendering best is voor buttons


    SDL_Rect renderQuad = { xPos, yPos, width, heigth };
    SDL_RenderCopy( f->renderer, texture,NULL,&renderQuad);     // Render de button sprite naar de renderbuffer.


}


