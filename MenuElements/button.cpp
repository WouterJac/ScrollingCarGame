// 
//  Created by jacob on 19/03/2019.
// 

#include "button.h"
#include "../Event/Event.h"
#include <iostream>
using namespace std;

// Parent van SDLbutton.

button::button() {

}

button::~button() {

}


void button::setDims(int x, int y, int w, int h) {      // Zet logische dimensies & locatie.
    width=w;
    heigth=h;
    xPos=x-w/2;
    yPos=y-h/2;         // trekt de helft van de sprite width ervanaf om makkelijk een button te kunnen centreren.
}

void button::setText(string text) {
    this->text=text;                    // Legacy.
}


bool button::clickedOn(Event e) {
    bool clickedOn = false;
    if(e.getType() == 'm' && e.getUpDown()==1) {
        int x, y;
        x = e.getMouseX();                      // Check of een muisklik op de button valt.
        y = e.getMouseY();

        if (x > xPos && x < (xPos + width)) {
            if (y > yPos && y < yPos + heigth) {        // Indien de x,y coordinaten binnen de button vallen -> true.
                clickedOn = true;
            }
        }
    }
    return clickedOn;
}
