// 
//  Created by jacob on 29/03/2019.
// 

#ifndef OEFENING1_EVENT_H
#define OEFENING1_EVENT_H

#include <string>
using namespace std;


class Event {
public:
    // Constructor en destructor.
    Event();
    ~Event();
    // Returnt m, k or w voor mouse/key/window.
    char getType();
    // Returnt 1 voor toetsaanslag, 0 voor loslaten van een toets.
    int getUpDown();
    // Getters voor coördinaten, keyinfo, ..
    int getMouseX();
    int getMouseY();
    string getKey();
    string getWindowEvent();
    bool getQuit();
    int getScreenWidth();
    int getScreenHeight();

    // Setters voor type event, muisinfo en keyinfo.
    void setType(char t);
    void setUpDown(int ud);
    void setMouseDims(int x, int y);
    void setKey(string k);
    void setWindowEvent(string w);
    void setQuit(bool q);
    void setWindowSize(int w, int h);

    void clear();

private:
    char type;
    int upDown=0, mouseX=0, mouseY=0, screenW, screenH;
    bool quit;
    string key, windowEvent;



};


#endif // OEFENING1_EVENT_H
