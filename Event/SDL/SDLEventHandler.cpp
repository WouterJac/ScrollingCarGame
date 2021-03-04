// 
//  Created by jacob on 18/03/2019.
// 

#include "SDLEventHandler.h"
#include <iostream>

using namespace std;

SDLEventHandler::SDLEventHandler() : EventHandler() {

}

SDLEventHandler::~SDLEventHandler() {

}


 // PollForEvent geeft een Event terug, met een type/updown/posities/.. (zie Event-documentatie).


Event SDLEventHandler::pollForEvent() {
    clearEvent();
    if (SDL_PollEvent(&e) != 0) {           // In e zit het SDL_Event waarvan we het type kunnen bepalen via ingebouwde SDL functies.
        if (e.type == SDL_QUIT) {           // We zouden deze SDL_Event rechtstreeks kunnen gebruiken, maar dat zou voor een slechte scheiding tussen SDL en logica zorgen.
            ev.setQuit(true);               // Dit is dus "better practice"!
        }
        else {
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                ev.setType('m');
                ev.setUpDown(1);    // Indrukken -> 1.
                int x,y;
                SDL_GetMouseState(&x, &y);              // Bij een muisklik, zet het type op 'm', en stel de x en y van de klik door.
                ev.setMouseDims(x-offsetX,y-offsetY);
            }
            else if (e.type == SDL_MOUSEBUTTONUP) {
                ev.setType('m');
                ev.setUpDown(0);    // Loslaten -> 0.
                int x,y;
                SDL_GetMouseState(&x, &y);              // Zelfde voor het loslaten van de muis.
                ev.setMouseDims(x-offsetX,y-offsetY);
            }
            else if (((e.type == SDL_KEYDOWN) || (e.type == SDL_KEYUP) )&& e.key.repeat == 0) {
                ev.setType('k');
                if(e.type == SDL_KEYDOWN) {         // Bij een toetsaanslag, zet het type op 'k' (van key).
                    ev.setUpDown(1);
                }
                else{
                    ev.setUpDown(0);    // Indrukken = 1, loslaten = 0.
                }
                switch( e.key.keysym.sym )
                {
                    case SDLK_UP : ev.setKey("up"); break;
                    case SDLK_DOWN : ev.setKey("down"); break;       // Key bevat een beschrijving van de ingedrukte toets.
                    case SDLK_LEFT : ev.setKey("left"); break;
                    case SDLK_RIGHT : ev.setKey("right"); break;
                    case SDLK_p : ev.setKey("p");break;
                    case SDLK_SPACE : ev.setKey("space");break;
                    case SDLK_RETURN : ev.setKey("return");break;
                    default : break;
                }
            }
            else if(e.type == SDL_WINDOWEVENT){
                ev.setType('w');                    // Window change event heeft als type 'w'.
                switch( e.window.event ) {
                    case SDL_WINDOWEVENT_SIZE_CHANGED : {
                        ev.setWindowEvent("size");
                        offsetX=(e.window.data1-600)/2;     // Huidige windowsize wordt doorgegeven aan event.
                        offsetY=(e.window.data2-800)/2;
                        // ev.setWindowSize(e.window.data1,e.window.data2);
                        break;
                    }
                    default :
                        ev.setWindowEvent("");
                        break;
                }
            }
        }
    }
    return ev;      // Return het event, dat nu voorzien is van de nodige parameters.
}

void SDLEventHandler::clearEvent() {
    ev.clear();     // Maakt het event leeg.
}



