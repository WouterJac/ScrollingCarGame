// 
//  Created by Wouter on 11/03/2019.
// 

#include "SDLECar.h"
#include <iostream>

using namespace std;


SDLECar::SDLECar() : ECar() {
}

// TODO: met if(ID = "man")

SDLECar::SDLECar(SDLFactory* a) {
    f = a;
    SPRITE_WIDTH=64;
    SPRITE_HEIGHT=128;
    SCREEN_WIDTH=f->SCREEN_WIDTH;
    SCREEN_HEIGHT=f->SCREEN_HEIGHT;
    sprPath="resources/cars/boxCarEn3.png"; // Zet beginparameters klaar.
    loadMedia();    // Deze functie load de sprites.
}

SDLECar::~SDLECar() {
    f = NULL;
    if( texture != NULL )
    {
        SDL_DestroyTexture( texture );  // Destructor.
        texture = NULL;
        SPRITE_WIDTH = 0;
        SPRITE_HEIGHT = 0;
    }
}

void SDLECar::visualize() {
    SDL_Rect renderQuad = { mPosX, mPosY, SPRITE_WIDTH, SPRITE_HEIGHT };

    // Render to screen
    if(animated && animLoad) {
        currentFrame++;
        if (currentFrame > numAnim*8-1) {
            currentFrame = 0;
        }
        SDL_RenderCopy(f->renderer, animTextures[currentFrame/8],NULL,&renderQuad);
    }
    else{
        SDL_RenderCopy(f->renderer, texture, NULL, &renderQuad);
    }


}

void SDLECar::devisualize() {
    // SDL_FreeSurface(surf);
}


void SDLECar::loadMedia() {

    if(animated && !animLoad){      // Indien de enemy geanimeerd is, laadt alle animeer-sprites.
        SPRITE_WIDTH=48;
        SPRITE_HEIGHT=96;
        // cout<<numAnim<<endl;
        for(int i=0;i<numAnim;i++){
            string p= sprPath+to_string(i)+".png";
            surf = IMG_Load(p.c_str());
            if (surf == NULL) {
                printf("Unable to load image %s! SDL_image Error: %s\n", p.c_str(), IMG_GetError());
            }
            SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xFF, 0xFF, 0xFF ) );
            animTextures[i] = SDL_CreateTextureFromSurface(f->renderer, surf);  // Maak de animeertextures aan.
            SDL_FreeSurface(surf);
        }
        animLoad=true;
    }
    else {
        surf = IMG_Load(sprPath.c_str());       // Maakt surfaces aan voor auto.
        if (surf == NULL) {
            printf("Unable to load image %s! SDL_image Error: %s\n", sprPath.c_str(), IMG_GetError());
        }
        if(ID=="Explode"){
            mPosY+=32;
            SPRITE_WIDTH=64;
            SPRITE_HEIGHT=64;
        }
        // SDL_SetColorKey( surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xFF, 0xFF, 0xFF ) );
        texture = SDL_CreateTextureFromSurface(f->renderer, surf);      // Maak de ECar texture aan.
        SDL_FreeSurface(surf);
    }
}

