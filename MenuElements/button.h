// 
//  Created by jacob on 19/03/2019.
// 

#ifndef OEFENING1_BUTTON_H
#define OEFENING1_BUTTON_H
#include <string>
#include "../Event/Event.h"

using namespace std;

// Parent van SDLbutton.

class button {
public:
    // Constructor en destructor.
    button();
    button(const button& c);
    virtual ~button();
    // Zet positie en kies dimensies van de knop.
    void setDims(int x, int y, int w, int h);
    // Steek de knop in de renderbuffer.
    virtual void render()=0;
    // Laadt de knop-media.
    virtual void loadMedia(string path)=0;
    // Geeft true indien een muisklik-event plaatsvindt op de knoplocatie.
    bool clickedOn(Event e);

    void setText(string text);  // Legacy.
protected:
    // Dimensies.
    int xPos,yPos,width,heigth;

    string text;    // Legacy.
};


#endif // OEFENING1_BUTTON_H
