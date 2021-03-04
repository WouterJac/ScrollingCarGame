// 
//  Created by jacob on 29/03/2019.
// 

#include <iostream>
#include "Event.h"

Event::Event() {

}

Event::~Event() {

}

// Getters en setters voor:
//    Type: Is dit een key, muis of windowevent?
//    UpDown: Wordt de key/muis ingedrukt of losgelaten?
//    MouseX/Y: Positie van muisklik.
//    WindowEvent: Een beschrijving van een windowevent (bv "Fullscreen" of "SizeChange").
//    Quit: Heeft de gebruiker het venster gesloten?
//

char Event::getType() {
    return type;
}

int Event::getUpDown() {
    return upDown;
}

int Event::getMouseX() {
    return mouseX;
}

int Event::getMouseY() {            // Voor documentatie: Zie bovenaan.
    return mouseY;
}

string Event::getKey() {
    // cout<<key<<endl;
    return key;
}

string Event::getWindowEvent() {
    return windowEvent;
}

void Event::setType(char t) {
    type = t;
}

void Event::setUpDown(int ud) {
    upDown = ud;
}

void Event::setMouseDims(int x, int y) {        // Voor documentatie: Zie bovenaan.
    mouseX = x;
    mouseY = y;
}

void Event::setKey(string k) {
    key = k;
}

void Event::setWindowEvent(string w) {
    windowEvent = w;
}

void Event::setQuit(bool q) {
    quit = q;
}

bool Event::getQuit(){
    return quit;
}

void Event::clear(){        // Maak event terug leeg om te hergebruiken.
    quit=false;
    type=' ';
    key="";
    upDown=0;

}

void Event::setWindowSize(int w, int h) {   // Legacy.
    screenW=w;
    screenH=h;

}

int Event::getScreenWidth() {   // Legacy.
    return screenW;
}

int Event::getScreenHeight() {  // Legacy.
    return screenH;
}
