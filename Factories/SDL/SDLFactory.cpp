// 
//  Created by Wouter on 4/03/2019.
// 

#include "SDLFactory.h"
#include "../../Entities/SDL/SDLCar.h"
#include "SDL.h"
#include "../../Entities/ECar.h"
#include "../../Entities/SDL/SDLECar.h"
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include "../../Entities/Entity.h"
#include "../../MenuElements/SDL/SDLbutton.h"
#include "../../Music/MusicPlayer.h"
#include "../../Music/SDL/SDLMusicPlayer.h"
#include "../../Entities/SDL/SDLMissile.h"
#include "../../Entities/SDL/SDLEneMissile.h"
#include "../../Entities/Object.h"
#include "../../Entities/SDL/SDLObject.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

SDLFactory::SDLFactory() : AFactory(){

}

SDLFactory::~SDLFactory() {

}

Entity* SDLFactory::createCar(){        // Deze methods geven een Entity-pointer naar nieuwe specifieke SDL_objecten.
    return new SDLCar(this);
}

Entity* SDLFactory::createECar(){
    return new SDLECar(this);
}

button* SDLFactory::createButton() {
    return new SDLbutton(this);
}

Missile* SDLFactory::createMissile() {
    return new SDLMissile(this);
}

EneMissile* SDLFactory::createEneMissile() {
    return new SDLEneMissile(this);
}

Object* SDLFactory::createObject(string ID){
    return new SDLObject(this,ID);
}

void SDLFactory::pauseRender(int t) {        // Pauzeert het renderen.
    SDL_Delay(t);
}

void SDLFactory::renderAll(){
    SDL_RenderPresent(renderer );            // Rendert de renderbuffer naar het scherm.
}

void SDLFactory::renderClear(){              // Maakt de renderbuffer leeg.
    SDL_RenderClear(renderer);
}

int SDLFactory::initializeGraphics() {


    bool success=true;

    window = NULL;
    renderer = NULL;

    // Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );        // Zet SDL klaar om een window te renderen.

    // Zet window klaar
    window = SDL_CreateWindow( "Vroom Vroom Pew Pew", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Maak renderer die objecten naar het window zal renderen.      // Note to self: Moest dit kapot zijn, verander laatste param door 0
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF ); // Standaardkleur is wit.
    changeBG("resources/backgrounds/roadBG.jpg");   // De beginachtergrond is roadBG.jpg.

    int imgFlags = IMG_INIT_PNG;                    // Initiate het laden van PNG's, TTF-fonts en Audio.
    if( !( IMG_Init( imgFlags ) & imgFlags ) )
    {
        printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
        success = false;
    }
    TTF_Init();
    gFont = TTF_OpenFont( "resources/fonts/BebasNeue.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    string heartPath = "resources/cars/Heart.png";  // Laadt de heartsprite voor levens.
    heartSurf = IMG_Load(heartPath.c_str());
    if (heartSurf == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", heartPath.c_str(), IMG_GetError());
    }
    heartTexture = SDL_CreateTextureFromSurface(renderer, heartSurf);
    SDL_FreeSurface(heartSurf);


    // Om logische van visuele coördinaten te scheiden.
    SDL_RenderSetLogicalSize(renderer,SCREEN_WIDTH,SCREEN_HEIGHT);

    return success;
}


int SDLFactory::quit(){
    SDL_DestroyRenderer( renderer );    // Bij het sluiten van de game worden renderer, window, IMG, .. gesloten/verwijderd.
    SDL_DestroyWindow( window );
    window = NULL;
    renderer = NULL;
    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}

void SDLFactory::changeBG(string path) {        // Verandert het path naar de background.
    BGpath=path;
}

void SDLFactory::loadBG() {         // Laadt de background van het background-path en voegt deze toe aan de renderbuffer.

    BGSurf = IMG_Load(BGpath.c_str());
    if (BGSurf == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", BGpath.c_str(), IMG_GetError());
    }
    BGTexture = SDL_CreateTextureFromSurface(renderer, BGSurf);


    if (scrolling) {                                    // Indien scrolling aanstaat zal de achtergrond bewegen.
        scrollingOffset = scrollingOffset + scrollspeed;
        if (scrollingOffset > SCREEN_HEIGHT) {
            scrollingOffset = 0;
        }
        SDL_Rect renderQuad = {0, scrollingOffset, SCREEN_WIDTH, SCREEN_HEIGHT};        // Aan de hand van een offset wordt een tweede achtergrond "aangeplakt".
        SDL_RenderCopy(renderer, BGTexture, NULL, &renderQuad);
        renderQuad = {0, scrollingOffset - (SCREEN_HEIGHT), 600, 800};
        SDL_RenderCopy(renderer, BGTexture, NULL, &renderQuad);
    }
    else {
        SDL_Rect renderQuad = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, BGTexture, NULL, &renderQuad);     // Indien geen scrolling, render gewoon naar de buffer.
    }

    SDL_FreeSurface(BGSurf);
    SDL_DestroyTexture(BGTexture);      // Delete aangemaakte textures en surfaces.


}

void SDLFactory::setScrolling(bool activate) {
    scrolling = activate;   // Zet scroll-parameter op de doorgegeven waarde.
}

SDLFactory::SDLFactory(int w, int  h) {
    SCREEN_WIDTH = w;   // Beginwaardes van het window worden doorgegeven bij aanmaak van de factory.
    SCREEN_HEIGHT =h;
}

void SDLFactory::renderText(string textureText, string color, int x, int y){    // Functie voor het renderen van text.

    if(color=="black"){                     // Stelt de textkleur in.
        textColor = { 0, 0, 0 ,255};
    }
    else if(color=="white"){
        textColor = { 255, 255, 255 ,255};
    }
    else if(color=="red"){
        textColor = { 255, 0, 0 ,255};
    }
    else if(color=="green"){
        textColor = { 0, 255, 0 ,255};
    }
    else if(color=="blue"){
        textColor = { 0, 0, 255 ,255};
    }
    else{
        printf("Incorrecte kleur doorgegeven! '%s' bestaat niet.",color.c_str());
    }
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(),  textColor);   // Maakt surface van de text, met een vast font en ingegeven kleur.
    if( textSurface != NULL ){
        textTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( textTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }

        SDL_Rect renderQuad = { x, y, textSurface->w, textSurface->h };     // Render de text naar de renderbuffer.
        SDL_RenderCopy(renderer, textTexture,NULL,&renderQuad);

        // Get rid of old surface.
        SDL_FreeSurface( textSurface );
        SDL_DestroyTexture(textTexture);
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }


}



void SDLFactory::handleWindowEvent(Event event) {
    if(event.getType()=='w') {
        if (event.getWindowEvent() == "size") {
            // printf("Size changed");
        }
    }
    else if(event.getType()=='k' && event.getUpDown()==1){
        if (event.getKey()=="return"){                          // Zet op fullscreen indien op entertoets gedrukt wordt.
            if( mFullScreen )
            {
                SDL_SetWindowFullscreen( window, SDL_FALSE );   // Toggle fullscreen indien dit al aanstond.
                mFullScreen = false;
            }
            else
            {
                SDL_SetWindowFullscreen( window, SDL_TRUE );
                mFullScreen = true;
            }
        }
    }
}

void SDLFactory::renderLife(int lives) {

    for(int i=0;i<lives;i++) {
        SDL_Rect renderQuad = {440+(i*32), 16, 24, 22};             // Render de levens-hartjes.
        SDL_RenderCopy(renderer, heartTexture, NULL, &renderQuad);
    }

}





