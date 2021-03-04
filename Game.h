//
// Created by Wouter on 4/03/2019.
//

#ifndef OEFENING1_GAME_H
#define OEFENING1_GAME_H


#include "Factories/AFactory.h"
#include "LTimer.h"
#include "Event/EventHandler.h"
#include "Music/MusicPlayer.h"

class Game {
public:
    // Constructor & Destructor.
    Game();
    Game(AFactory* f, EventHandler* eh, MusicPlayer* mp);
    virtual ~Game();
    // Singleton-method.
    static Game* getInstance(AFactory* f, EventHandler* eh, MusicPlayer* mp);
    // Start de gameloop.
    void start();

private:
    // Singleton instance
    static Game* instance;

    // Abstract factory, Abstract eventhandler en Abstract muziekspeler.
    AFactory* f;
    EventHandler *eh;
    MusicPlayer* mp;

    // Frames per second timer.
    LTimer fpsTimer;
    // Frames per second cap timer.
    LTimer capTimer;
    // Timers voor powerups/blink.
    LTimer eventTimer;
    LTimer powerTimer;

    // Lijst met alle enemies/objecten.
    Entity* enemies[40];
    // Event voor userinput.
    Event inputEv;

    // Render de hele renderbuffer naar het scherm, maakt gebruik van de factory.
    void renderAll();
    // Creëer een nieuwe enemy van type ent, via factory.
    void addEnemy(int x, int y, Entity* ent);
    // Delete objecten buiten het spelveld.
    void deleteInactive();

    // Save en load configfile.
    void saveConfig();
    void loadConfig();

    // Wachtfunctie.
    void wait(int ms);
    // Activeer de pausemode.
    void pauseGame();
    // Returnt een x-positie van 1 van de 4 lanes.
    int getRandomLane();

    // FPS variabelen.
    const int SCREEN_FPS = 60;
    const int SCREEN_TICK_PER_FRAME = 1000 / SCREEN_FPS;
    //Logische screen dimensies.
    int SCREEN_WIDTH, SCREEN_HEIGHT;

    // Toont of de speler geraakt kan worden.
    bool playerVulnerable=true;
    // Wanneer de speler het venster wegklikt is quit true.
    bool quit = false;
    // Geluid
    bool mute=false;

    // Scores, levens, aantal enemies, aantal keer blinken.
    int blinks, lives, enemyCount, score, highScore, ammo;
    const int AMMO_CAP=3;


};



#endif //OEFENING1_GAME_H
